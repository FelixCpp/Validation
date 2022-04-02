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
	ValidatableValidationRuleBuilder<TObject, TValue>::ValidatableValidationRuleBuilder(Validator<TObject>& validator, Attribute attribute):
		ValidationRuleBuilder<TObject>(validator),
		attribute(attribute)
	{
	}
	
	template <typename TObject, typename TValue>
	RuleBuilderValidationResult ValidatableValidationRuleBuilder<TObject, TValue>::Validate(const TObject& object) const
	{
		const Value& value = object.*attribute;
		RuleBuilderValidationResult result;

		// "flatmap" the validation result of object
		const ValidationResult validationResult = value.Validate();
		for (const RuleBuilderValidationResult& builderResult : validationResult.GetRuleBuilderResults())
		{
			for (const RuleValidationResult& ruleResult : builderResult.GetRuleResults())
			{
				result.AddRuleResult(ruleResult);
			}
		}
		return result;
	}


}
