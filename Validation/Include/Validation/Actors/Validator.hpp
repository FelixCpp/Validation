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

#include "../Results/ValidationResult.hpp"
#include "../RuleBuilders/ValidationRuleBuilder.hpp"
#include "../RuleBuilders/StringValidationRuleBuilder.hpp"
#include "../RuleBuilders/NumericValidationRuleBuilder.hpp"
#include "../RuleBuilders/ValidatableValidationRuleBuilder.hpp"

#include <memory>
#include <list>

namespace Validation
{
	////////////////////////////////////////////////////////////
	/// \brief Define Validator class that is intended to be
	///		   used as a builder to rule-builders.
	///
	/// \tparam TObject The object to validate.
	///
	////////////////////////////////////////////////////////////
	template<typename TObject>
	class Validator
	{
	public:

		StringValidationRuleBuilder<TObject, char>& RuleFor(const std::string TObject::* attribute);
		StringValidationRuleBuilder<TObject, wchar_t>& RuleFor(const std::wstring TObject::* attribute);

		template <typename TValue>
		NumericValidationRuleBuilder<TObject, TValue>& RuleFor(const TValue TObject::* attribute);

		template <typename TValue>
		ValidatableValidationRuleBuilder<TObject, TValue>& Validated(const TValue TObject::* attribute);

		////////////////////////////////////////////////////////////
		/// \brief Validates each rule builder and packs the results
		///		   in a single ValidationResult object.
		///
		///	\return A packed ValidationResult that contains each
		///			error of each rule-builder.
		/// 
		////////////////////////////////////////////////////////////
		ValidationResult Validate(const TObject& object) const;

		////////////////////////////////////////////////////////////
		/// \brief Check the validation for success.
		/// 
		////////////////////////////////////////////////////////////
		bool IsValid() const;

	private:

		////////////////////////////////////////////////////////////
		/// Member data
		/// 
		////////////////////////////////////////////////////////////
		std::list<std::shared_ptr<ValidationRuleBuilder<TObject>>> ruleBuilders;

	};
}

#include "Validator.inl"