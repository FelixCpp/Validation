## Validation

Validates objects by checking customized set of rules for its attributes.

This library is currently in early-stage development and will be more flexible soon.



## Example to get started using the validation library.



### Validatable definition

```C++
#include <Validation/Actors/Validator.hpp>
#include <Validation/Actors/Validatable.hpp>

#include <string>

class Person final : public Validation::Validatable<Person>
{
public:

	std::wstring Name;
	int Age;

	explicit Person(std::wstring name, int age):
		Name(std::move(name)), Age(age)
	{}

	virtual Validation::Validator<Person> CreateValidator() const override
	{
		return Validation::Validator<Person>()
			.RuleFor(&Person::Name).NotEmpty().Must([](const std::wstring& name) { return name.length() > 5; }, "The name must be at least 6 characters long.").Done();
	}

};
```



### How to validate an object

```C++
const Person person(L"Jack Jober", 29);

	const Validation::ValidationResult result = person.Validate();

	if(result.IsValid())
	{
		std::cout << "Person is valid" << std::endl;
	} else
	{
		for(const Validation::RuleBuilderValidationResult& builderResults : result.GetRuleBuilderResults())
		{
			for(const Validation::RuleValidationResult& ruleResult : builderResults.GetRuleResults())
			{
				if(!ruleResult.IsValid())
				{
					std::cout << ruleResult.GetErrorText().value_or("Rule failed without error text") << std::endl;
				}
			}
		}
	}
```

