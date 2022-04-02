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

	////////////////////////////////////////////////////////////
	template <typename TObject>
	StringValidationRuleBuilder<TObject, char>& Validator<TObject>::RuleFor(const std::string TObject::* attribute)
	{
		auto* ruleBuilder = new StringValidationRuleBuilder<TObject, char>(*this, attribute);
		ruleBuilders.emplace_back(ruleBuilder);
		return *ruleBuilder;
	}

	////////////////////////////////////////////////////////////
	template <typename TObject>
	StringValidationRuleBuilder<TObject, wchar_t>& Validator<TObject>::RuleFor(const std::wstring TObject::* attribute)
	{
		auto* ruleBuilder = new StringValidationRuleBuilder<TObject, wchar_t>(*this, attribute);
		ruleBuilders.emplace_back(ruleBuilder);
		return *ruleBuilder;
	}

	////////////////////////////////////////////////////////////
	template <typename TObject>
	template <typename TValue>
	NumericValidationRuleBuilder<TObject, TValue>& Validator<TObject>::RuleFor(const TValue TObject::* attribute)
	{
		auto* ruleBuilder = new NumericValidationRuleBuilder<TObject, TValue>(*this, attribute);
		ruleBuilders.emplace_back(ruleBuilder);
		return *ruleBuilder;
	}

	template <typename TObject>
	template <typename TValue>
	ValidatableValidationRuleBuilder<TObject, TValue>& Validator<TObject>::Validated(const TValue TObject::* attribute)
	{
		using ValidatedObjectType = typename TValue::Object;
		auto* ruleBuilder = new ValidatableValidationRuleBuilder<TObject, ValidatedObjectType>(*this, attribute);
		ruleBuilders.emplace_back(ruleBuilder);
		return *ruleBuilder;
	}

	////////////////////////////////////////////////////////////
	template <typename TObject>
	ValidationResult Validator<TObject>::Validate(const TObject& object) const
	{
		ValidationResult result;

		for(const std::shared_ptr<ValidationRuleBuilder<TObject>>& ruleBuilder : ruleBuilders)
		{
			result.AddRuleBuilderResult(ruleBuilder->Validate(object));
		}

		return result;
	}

	////////////////////////////////////////////////////////////
	template <typename TObject>
	bool Validator<TObject>::IsValid() const
	{
		return Validate().IsValid();
	}

}