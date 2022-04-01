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

#include "../Results/RuleBuilderValidationResult.hpp"

namespace Validation
{
	////////////////////////////////////////////////////////////
	/// Forward declaration
	/// 
	////////////////////////////////////////////////////////////
	template<typename TObject>
	class Validator;

	////////////////////////////////////////////////////////////
	/// \brief Define interface for rule builders.
	/// 
	////////////////////////////////////////////////////////////
	template<typename TObject>
	class ValidationRuleBuilder
	{
	public:
		////////////////////////////////////////////////////////////
		/// \brief Construct a validation rule builder associated
		///		   to a validator in order to return to the
		///		   building-builder state
		/// 
		////////////////////////////////////////////////////////////
		explicit ValidationRuleBuilder(Validator<TObject>& validator);

		////////////////////////////////////////////////////////////
		/// \brief Default destructor
		/// 
		////////////////////////////////////////////////////////////
		virtual ~ValidationRuleBuilder() = default;

		////////////////////////////////////////////////////////////
		/// \brief Validates the rules of the rule builder and
		///		   returns a packed result type.
		/// 
		////////////////////////////////////////////////////////////
		virtual RuleBuilderValidationResult Validate(const TObject& object) const = 0;

		////////////////////////////////////////////////////////////
		/// \brief Return to the initial building state where
		///		   other attributes can be set-up for validation.
		/// 
		////////////////////////////////////////////////////////////
		Validator<TObject>& Done() const;

	private:

		////////////////////////////////////////////////////////////
		/// Member data
		/// 
		////////////////////////////////////////////////////////////
		Validator<TObject>& validator;

	};
}

#include "ValidationRuleBuilder.inl"