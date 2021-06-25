<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: utexcep - Exception code support
 *
 ******************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#घोषणा ACPI_DEFINE_EXCEPTION_TABLE
#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utexcep")

/*******************************************************************************
 *
 * FUNCTION:    acpi_क्रमmat_exception
 *
 * PARAMETERS:  status              - The acpi_status code to be क्रमmatted
 *
 * RETURN:      A string containing the exception text. A valid poपूर्णांकer is
 *              always वापसed.
 *
 * DESCRIPTION: This function translates an ACPI exception पूर्णांकo an ASCII
 *              string. Returns "unknown status" string क्रम invalid codes.
 *
 ******************************************************************************/
स्थिर अक्षर *acpi_क्रमmat_exception(acpi_status status)
अणु
	स्थिर काष्ठा acpi_exception_info *exception;

	ACPI_FUNCTION_ENTRY();

	exception = acpi_ut_validate_exception(status);
	अगर (!exception) अणु

		/* Exception code was not recognized */

		ACPI_ERROR((AE_INFO,
			    "Unknown exception code: 0x%8.8X", status));

		वापस ("UNKNOWN_STATUS_CODE");
	पूर्ण

	वापस (exception->name);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_क्रमmat_exception)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_validate_exception
 *
 * PARAMETERS:  status              - The acpi_status code to be क्रमmatted
 *
 * RETURN:      A string containing the exception text. शून्य अगर exception is
 *              not valid.
 *
 * DESCRIPTION: This function validates and translates an ACPI exception पूर्णांकo
 *              an ASCII string.
 *
 ******************************************************************************/
स्थिर काष्ठा acpi_exception_info *acpi_ut_validate_exception(acpi_status status)
अणु
	u32 sub_status;
	स्थिर काष्ठा acpi_exception_info *exception = शून्य;

	ACPI_FUNCTION_ENTRY();

	/*
	 * Status is composed of two parts, a "type" and an actual code
	 */
	sub_status = (status & ~AE_CODE_MASK);

	चयन (status & AE_CODE_MASK) अणु
	हाल AE_CODE_ENVIRONMENTAL:

		अगर (sub_status <= AE_CODE_ENV_MAX) अणु
			exception = &acpi_gbl_exception_names_env[sub_status];
		पूर्ण
		अवरोध;

	हाल AE_CODE_PROGRAMMER:

		अगर (sub_status <= AE_CODE_PGM_MAX) अणु
			exception = &acpi_gbl_exception_names_pgm[sub_status];
		पूर्ण
		अवरोध;

	हाल AE_CODE_ACPI_TABLES:

		अगर (sub_status <= AE_CODE_TBL_MAX) अणु
			exception = &acpi_gbl_exception_names_tbl[sub_status];
		पूर्ण
		अवरोध;

	हाल AE_CODE_AML:

		अगर (sub_status <= AE_CODE_AML_MAX) अणु
			exception = &acpi_gbl_exception_names_aml[sub_status];
		पूर्ण
		अवरोध;

	हाल AE_CODE_CONTROL:

		अगर (sub_status <= AE_CODE_CTRL_MAX) अणु
			exception = &acpi_gbl_exception_names_ctrl[sub_status];
		पूर्ण
		अवरोध;

	शेष:

		अवरोध;
	पूर्ण

	अगर (!exception || !exception->name) अणु
		वापस (शून्य);
	पूर्ण

	वापस (exception);
पूर्ण
