/* -*- C++ -*-
 * Cppcheck - A tool for static C/C++ code analysis
 * Copyright (C) 2007-2025 Cppcheck team.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


//---------------------------------------------------------------------------
#ifndef checksizeofH
#define checksizeofH
//---------------------------------------------------------------------------

#include "check.h"
#include "config.h"

#include <string>

class ErrorLogger;
class Settings;
class Token;
class Tokenizer;

/// @addtogroup Checks
/// @{


/** @brief checks on usage of sizeof() operator */

class CPPCHECKLIB CheckSizeof : public Check {
public:
    /** @brief This constructor is used when registering the CheckClass */
    CheckSizeof() : Check(myName()) {}

private:
    /** @brief This constructor is used when running checks. */
    CheckSizeof(const Tokenizer* tokenizer, const Settings* settings, ErrorLogger* errorLogger)
        : Check(myName(), tokenizer, settings, errorLogger) {}

    /** @brief Run checks against the normal token list */
    void runChecks(const Tokenizer& tokenizer, ErrorLogger* errorLogger) override;

    /** @brief %Check for 'sizeof sizeof ..' */
    void sizeofsizeof();

    /** @brief %Check for calculations inside sizeof */
    void sizeofCalculation();

    /** @brief %Check for function call inside sizeof */
    void sizeofFunction();

    /** @brief %Check for suspicious calculations with sizeof results */
    void suspiciousSizeofCalculation();

    /** @brief %Check for using sizeof with array given as function argument */
    void checkSizeofForArrayParameter();

    /** @brief %Check for using sizeof of a variable when allocating it */
    void checkSizeofForPointerSize();

    /** @brief %Check for using sizeof with numeric given as function argument */
    void checkSizeofForNumericParameter();

    /** @brief %Check for using sizeof(void) */
    void sizeofVoid();

    // Error messages..
    void sizeofsizeofError(const Token* tok);
    void sizeofCalculationError(const Token* tok, bool inconclusive);
    void sizeofFunctionError(const Token* tok);
    void multiplySizeofError(const Token* tok);
    void divideSizeofError(const Token* tok);
    void sizeofForArrayParameterError(const Token* tok);
    void sizeofForPointerError(const Token* tok, const std::string &varname);
    void divideBySizeofError(const Token* tok, const std::string &memfunc);
    void sizeofForNumericParameterError(const Token* tok);
    void sizeofVoidError(const Token *tok);
    void sizeofDereferencedVoidPointerError(const Token *tok, const std::string &varname);
    void arithOperationsOnVoidPointerError(const Token* tok, const std::string &varname, const std::string &vartype);

    void getErrorMessages(ErrorLogger* errorLogger, const Settings* settings) const override;

    static std::string myName() {
        return "Sizeof";
    }

    std::string classInfo() const override {
        return "sizeof() usage checks\n"
               "- sizeof for array given as function argument\n"
               "- sizeof for numeric given as function argument\n"
               "- using sizeof(pointer) instead of the size of pointed data\n"
               "- look for 'sizeof sizeof ..'\n"
               "- look for calculations inside sizeof()\n"
               "- look for function calls inside sizeof()\n"
               "- look for suspicious calculations with sizeof()\n"
               "- using 'sizeof(void)' which is undefined\n";
    }
};
/// @}
//---------------------------------------------------------------------------
#endif // checksizeofH
