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

#include "Validator.hpp"
#include "../Results/ValidationResult.hpp"

namespace Validation
{
	////////////////////////////////////////////////////////////
	/// \brief Define Validatable base class that lets the
	///		   library create a validation for the object.
	///
	///	\tparam TObject The object type to validate.
	/// 
	////////////////////////////////////////////////////////////
	template<typename TObject>
	class Validatable
	{
	public:

		using Object = TObject;

		//static_assert(std::is_base_of_v<Validatable<TObject>, TObject>, "TObject must derive from Validatable<TObject>.");

		////////////////////////////////////////////////////////////
		/// \brief Default destructor
		/// 
		////////////////////////////////////////////////////////////
		virtual ~Validatable() = default;

		////////////////////////////////////////////////////////////
		/// \brief Constructs a validation for the main object.
		/// 
		////////////////////////////////////////////////////////////
		virtual Validator<TObject> CreateValidator() const = 0;

		////////////////////////////////////////////////////////////
		/// \brief Validates the validator.
		/// 
		////////////////////////////////////////////////////////////
		const ValidationResult& Validate(bool possibleDataChange = false) const;

		////////////////////////////////////////////////////////////
		/// \brief Ensures that the validation will be re-invoked
		///		   next time retrieving the validation result data.
		/// 
		////////////////////////////////////////////////////////////
		void NotifyDataChange() const;

	private:

		////////////////////////////////////////////////////////////
		/// \brief Cache
		/// 
		////////////////////////////////////////////////////////////
		mutable struct ValidationCache
		{
			ValidationResult Result	= {};
			bool Updated			= false;
		} cache;

	};
}

#include "Validatable.inl"