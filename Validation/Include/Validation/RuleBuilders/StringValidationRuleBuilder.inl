////////////////////////////////////////////////////////////
/// MIT License
/// 
/// Copyright(c) 2022 FelixCpp
/// 
/// Permission is hereby granted, free of charge, to any person obtaining a copy
/// of this softwareand associated documentation files(the "Software"), to deal
/// in the Software without restriction, including without limitation the rights
/// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
/// copies of the Software, and to permit persons to whom the Software is
/// furnished to do so, subject to the following conditions :
/// 
/// The above copyright notice and this permission notice shall be included in all
/// copies or substantial portions of the Software.
/// 
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
/// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
/// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
/// SOFTWARE.
/// 
////////////////////////////////////////////////////////////

#pragma once

#include "../Rules/MustValidationRule.hpp"

namespace Validation
{
	////////////////////////////////////////////////////////////
	template<typename TObject, typename TChar>
	StringValidationRuleBuilder<TObject, TChar>::StringValidationRuleBuilder(Validator<TObject>& validator, Attribute attribute):
		ValidationRuleBuilder<TObject>(validator),
		attribute(attribute)
	{
	}


	template<typename TObject, typename TChar>
	template<typename TPredicate>
	StringValidationRuleBuilder<TObject, TChar>& StringValidationRuleBuilder<TObject, TChar>::Must(TPredicate predicate, OptionalErrorText errorText)
	{
		rules.push_back(std::make_unique<MustValidationRule<String, TPredicate>>(std::move(predicate), std::move(errorText)));
		return *this;
	}

	template <typename TObject, typename TChar>
	StringValidationRuleBuilder<TObject, TChar>& StringValidationRuleBuilder<TObject, TChar>::NotEmpty(OptionalErrorText errorText)
	{
		return Must([](const String& value)
		{
			return !value.empty();
		}, errorText);
	}

	template <typename TObject, typename TChar>
	StringValidationRuleBuilder<TObject, TChar>& StringValidationRuleBuilder<TObject, TChar>::NotEmptyOrWhitespace(OptionalErrorText errorText)
	{
		return Must([](const String& value)
		{
			return !(value.empty() || std::ranges::all_of(value, std::isspace));
		}, errorText);
	}

	template <typename TObject, typename TChar>
	StringValidationRuleBuilder<TObject, TChar>& StringValidationRuleBuilder<TObject, TChar>::IsEmpty(OptionalErrorText errorText)
	{
		return Must([](const String& value)
		{
			return value.empty();
		}, errorText);
	}

	template <typename TObject, typename TChar>
	StringValidationRuleBuilder<TObject, TChar>& StringValidationRuleBuilder<TObject, TChar>::Equals(const String& value, OptionalErrorText errorText)
	{
		return Must([value](const String& parameter)
		{
			return parameter == value;
		}, errorText);
	}

	template <typename TObject, typename TChar>
	StringValidationRuleBuilder<TObject, TChar>& StringValidationRuleBuilder<TObject, TChar>::MinLength(size_t length, OptionalErrorText errorText)
	{
		return Must([length](const String& parameter)
		{
			return parameter.length() >= length;
		}, errorText);
	}

	template <typename TObject, typename TChar>
	StringValidationRuleBuilder<TObject, TChar>& StringValidationRuleBuilder<TObject, TChar>::MaxLength(size_t length, OptionalErrorText errorText)
	{
		return Must([length](const String& parameter)
		{
			return parameter.length() <= length;
		}, errorText);
	}


	template <typename TObject, typename TChar>
	RuleBuilderValidationResult StringValidationRuleBuilder<TObject, TChar>::Validate(const TObject& object) const
	{
		const String& value = object.*attribute;

		RuleBuilderValidationResult result;

		for(const std::unique_ptr<IValidationRule<String>>& rule : rules)
		{
			result.AddRuleResult(rule->Validate(value));
		}

		return result;
	}

}