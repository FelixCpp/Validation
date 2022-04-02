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

#include "ValidationRuleBuilder.hpp"
#include "../Rules/IValidationRule.hpp"

#include <memory>
#include <vector>

namespace Validation
{

	template<typename TObject, typename TValue>
	class NumericValidationRuleBuilder final : public ValidationRuleBuilder<TObject>
	{
	public:

		////////////////////////////////////////////////////////////
		/// Type definitions
		/// 
		////////////////////////////////////////////////////////////
		using Numeric	= TValue;
		using Attribute = const Numeric TObject::*;

	public:

		////////////////////////////////////////////////////////////
		/// \brief Construct a numeric validation rule builder
		///		   with associated validator.
		/// 
		////////////////////////////////////////////////////////////
		explicit NumericValidationRuleBuilder(Validator<TObject>& validator, Attribute attribute);

		template<typename TPredicate>
		NumericValidationRuleBuilder& Must(TPredicate predicate, OptionalErrorText errorText = std::nullopt);
		NumericValidationRuleBuilder& Lower(Numeric value, OptionalErrorText errorText = std::nullopt);
		NumericValidationRuleBuilder& Greater(Numeric value, OptionalErrorText errorText = std::nullopt);
		NumericValidationRuleBuilder& Between(Numeric min, Numeric max, OptionalErrorText errorText = std::nullopt);

		////////////////////////////////////////////////////////////
		/// \brief Validates the rules of the rule builder and
		///		   returns a packed result type.
		/// 
		////////////////////////////////////////////////////////////
		virtual RuleBuilderValidationResult Validate(const TObject& object) const override;

	private:

		////////////////////////////////////////////////////////////
		/// Member data
		/// 
		////////////////////////////////////////////////////////////
		Attribute attribute;
		std::vector<std::unique_ptr<IValidationRule<Numeric>>> rules;

	};
}

#include "NumericValidationRuleBuilder.inl"