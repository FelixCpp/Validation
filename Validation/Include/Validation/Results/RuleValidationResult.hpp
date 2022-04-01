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

#include "ValidationState.hpp"

#include <string>
#include <optional>

namespace Validation
{
	////////////////////////////////////////////////////////////
	/// Types
	/// 
	////////////////////////////////////////////////////////////
	using OptionalErrorText = std::optional<std::string>;

	////////////////////////////////////////////////////////////
	/// \brief Define rule validation result type.
	/// 
	////////////////////////////////////////////////////////////
	class RuleValidationResult
	{
	public:
		
		////////////////////////////////////////////////////////////
		/// \brief Construct a result with an associated error text.
		///
		///	\param state		The state to store.
		///	\param errorText	The error text to store.
		/// 
		////////////////////////////////////////////////////////////
		RuleValidationResult(ValidationState state, OptionalErrorText errorText = std::nullopt);

		////////////////////////////////////////////////////////////
		/// \brief Get the validation state
		///
		///	\return The validation state
		/// 
		////////////////////////////////////////////////////////////
		ValidationState GetState() const;

		////////////////////////////////////////////////////////////
		/// \brief Get the error text or std::nullopt if its empty.
		///
		///	\return The actual error text if there is one,
		///			std::nullopt otherwise.
		/// 
		////////////////////////////////////////////////////////////
		const OptionalErrorText& GetErrorText() const;

		////////////////////////////////////////////////////////////
		/// \brief Checks if the state is equal to
		///		   ValidationState::Success.
		/// 
		////////////////////////////////////////////////////////////
		bool IsValid() const;

	private:

		////////////////////////////////////////////////////////////
		/// Member data
		/// 
		////////////////////////////////////////////////////////////
		ValidationState		state;
		OptionalErrorText	errorText;

	};
}

#include "RuleValidationResult.inl"