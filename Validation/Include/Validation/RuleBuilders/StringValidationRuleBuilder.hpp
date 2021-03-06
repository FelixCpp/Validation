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
#include <string>
#include <vector>

namespace Validation
{

	template<typename TObject, typename TChar>
	class StringValidationRuleBuilder final : public ValidationRuleBuilder<TObject>
	{
	public:

		////////////////////////////////////////////////////////////
		/// Type definitions
		/// 
		////////////////////////////////////////////////////////////
		using String	= std::basic_string<TChar>;
		using Attribute = const String TObject::*;

	public:

		////////////////////////////////////////////////////////////
		/// \brief Construct StringValidationRuleBuilder object
		///		   associated to a validator with an attribute.
		///
		///	\param validator The validator that builds has this rule builder
		///	\param attribute The attribute to validate
		/// 
		////////////////////////////////////////////////////////////
		explicit StringValidationRuleBuilder(Validator<TObject>& validator, Attribute attribute);

		template<typename TPredicate>
		StringValidationRuleBuilder& Must(TPredicate predicate, OptionalErrorText errorText = std::nullopt);
		StringValidationRuleBuilder& NotEmpty(OptionalErrorText errorText = std::nullopt);
		StringValidationRuleBuilder& NotEmptyOrWhitespace(OptionalErrorText errorText = std::nullopt);
		StringValidationRuleBuilder& IsEmpty(OptionalErrorText errorText = std::nullopt);
		StringValidationRuleBuilder& Equals(const String& value, OptionalErrorText errorText = std::nullopt);
		StringValidationRuleBuilder& MinLength(size_t length, OptionalErrorText errorText = std::nullopt);
		StringValidationRuleBuilder& MaxLength(size_t length, OptionalErrorText errorText = std::nullopt);
		
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
		std::vector<std::unique_ptr<IValidationRule<String>>> rules;

	};

}

#include "StringValidationRuleBuilder.inl"