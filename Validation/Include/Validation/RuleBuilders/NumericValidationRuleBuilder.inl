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

namespace Validation
{

	template <typename TObject, typename TValue>
	NumericValidationRuleBuilder<TObject, TValue>::NumericValidationRuleBuilder(Validator<TObject>& validator, Attribute attribute):
		ValidationRuleBuilder<TObject>(validator), attribute(attribute)
	{
	}

	template <typename TObject, typename TValue>
	template <typename TPredicate>
	NumericValidationRuleBuilder<TObject, TValue>& NumericValidationRuleBuilder<TObject, TValue>::Must(TPredicate predicate, OptionalErrorText errorText)
	{
		rules.push_back(std::make_unique<MustValidationRule<TValue, TPredicate>>(std::move(predicate), std::move(errorText)));
		return *this;
	}

	template <typename TObject, typename TValue>
	NumericValidationRuleBuilder<TObject, TValue>& NumericValidationRuleBuilder<TObject, TValue>::Lower(Numeric value, OptionalErrorText errorText)
	{
		return Must([value](const Numeric& parameter)
		{
			return parameter < value;
		}, errorText);
	}

	template <typename TObject, typename TValue>
	NumericValidationRuleBuilder<TObject, TValue>& NumericValidationRuleBuilder<TObject, TValue>::Greater(Numeric value, OptionalErrorText errorText)
	{
		return Must([value](const Numeric& parameter)
		{
			return parameter > value;
		}, errorText);
	}

	template <typename TObject, typename TValue>
	NumericValidationRuleBuilder<TObject, TValue>& NumericValidationRuleBuilder<TObject, TValue>::Between(Numeric min, Numeric max, OptionalErrorText errorText)
	{
		return Must([min, max](const Numeric& value)
		{
			return value >= min && value <= max;
		}, errorText);
	}

	template <typename TObject, typename TValue>
	RuleBuilderValidationResult NumericValidationRuleBuilder<TObject, TValue>::Validate(const TObject& object) const
	{
		const Numeric& value = object.*attribute;

		RuleBuilderValidationResult result;
		for(const std::unique_ptr<IValidationRule<Numeric>>& rule : rules)
		{
			result.AddRuleResult(rule->Validate(value));
		}
		return result;
	}


}