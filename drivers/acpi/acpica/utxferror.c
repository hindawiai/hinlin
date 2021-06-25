<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: utxख_त्रुटि - Various error/warning output functions
 *
 ******************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("utxferror")

/*
 * This module is used क्रम the in-kernel ACPICA as well as the ACPICA
 * tools/applications.
 */
#अगर_अघोषित ACPI_NO_ERROR_MESSAGES	/* Entire module */
/*******************************************************************************
 *
 * FUNCTION:    acpi_error
 *
 * PARAMETERS:  module_name         - Caller's module name (क्रम error output)
 *              line_number         - Caller's line number (क्रम error output)
 *              क्रमmat              - Prपूर्णांकf क्रमmat string + additional args
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक "ACPI Error" message with module/line/version info
 *
 ******************************************************************************/
व्योम ACPI_INTERNAL_VAR_XFACE
acpi_error(स्थिर अक्षर *module_name, u32 line_number, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची arg_list;

	ACPI_MSG_REसूचीECT_BEGIN;
	acpi_os_म_लिखो(ACPI_MSG_ERROR);

	बहु_शुरू(arg_list, क्रमmat);
	acpi_os_भ_लिखो(क्रमmat, arg_list);
	ACPI_MSG_SUFFIX;
	बहु_पूर्ण(arg_list);

	ACPI_MSG_REसूचीECT_END;
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_error)

/*******************************************************************************
 *
 * FUNCTION:    acpi_exception
 *
 * PARAMETERS:  module_name         - Caller's module name (क्रम error output)
 *              line_number         - Caller's line number (क्रम error output)
 *              status              - Status value to be decoded/क्रमmatted
 *              क्रमmat              - Prपूर्णांकf क्रमmat string + additional args
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक an "ACPI Error" message with module/line/version
 *              info as well as decoded acpi_status.
 *
 ******************************************************************************/
व्योम ACPI_INTERNAL_VAR_XFACE
acpi_exception(स्थिर अक्षर *module_name,
	       u32 line_number, acpi_status status, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची arg_list;

	ACPI_MSG_REसूचीECT_BEGIN;

	/* For AE_OK, just prपूर्णांक the message */

	अगर (ACPI_SUCCESS(status)) अणु
		acpi_os_म_लिखो(ACPI_MSG_ERROR);

	पूर्ण अन्यथा अणु
		acpi_os_म_लिखो(ACPI_MSG_ERROR "%s, ",
			       acpi_क्रमmat_exception(status));
	पूर्ण

	बहु_शुरू(arg_list, क्रमmat);
	acpi_os_भ_लिखो(क्रमmat, arg_list);
	ACPI_MSG_SUFFIX;
	बहु_पूर्ण(arg_list);

	ACPI_MSG_REसूचीECT_END;
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_exception)

/*******************************************************************************
 *
 * FUNCTION:    acpi_warning
 *
 * PARAMETERS:  module_name         - Caller's module name (क्रम warning output)
 *              line_number         - Caller's line number (क्रम warning output)
 *              क्रमmat              - Prपूर्णांकf क्रमmat string + additional args
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक "ACPI Warning" message with module/line/version info
 *
 ******************************************************************************/
व्योम ACPI_INTERNAL_VAR_XFACE
acpi_warning(स्थिर अक्षर *module_name, u32 line_number, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची arg_list;

	ACPI_MSG_REसूचीECT_BEGIN;
	acpi_os_म_लिखो(ACPI_MSG_WARNING);

	बहु_शुरू(arg_list, क्रमmat);
	acpi_os_भ_लिखो(क्रमmat, arg_list);
	ACPI_MSG_SUFFIX;
	बहु_पूर्ण(arg_list);

	ACPI_MSG_REसूचीECT_END;
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_warning)

/*******************************************************************************
 *
 * FUNCTION:    acpi_info
 *
 * PARAMETERS:  क्रमmat              - Prपूर्णांकf क्रमmat string + additional args
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक generic "ACPI:" inक्रमmation message. There is no
 *              module/line/version info in order to keep the message simple.
 *
 ******************************************************************************/
व्योम ACPI_INTERNAL_VAR_XFACE acpi_info(स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची arg_list;

	ACPI_MSG_REसूचीECT_BEGIN;
	acpi_os_म_लिखो(ACPI_MSG_INFO);

	बहु_शुरू(arg_list, क्रमmat);
	acpi_os_भ_लिखो(क्रमmat, arg_list);
	acpi_os_म_लिखो("\n");
	बहु_पूर्ण(arg_list);

	ACPI_MSG_REसूचीECT_END;
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_info)

/*******************************************************************************
 *
 * FUNCTION:    acpi_bios_error
 *
 * PARAMETERS:  module_name         - Caller's module name (क्रम error output)
 *              line_number         - Caller's line number (क्रम error output)
 *              क्रमmat              - Prपूर्णांकf क्रमmat string + additional args
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक "ACPI Firmware Error" message with module/line/version
 *              info
 *
 ******************************************************************************/
व्योम ACPI_INTERNAL_VAR_XFACE
acpi_bios_error(स्थिर अक्षर *module_name,
		u32 line_number, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची arg_list;

	ACPI_MSG_REसूचीECT_BEGIN;
	acpi_os_म_लिखो(ACPI_MSG_BIOS_ERROR);

	बहु_शुरू(arg_list, क्रमmat);
	acpi_os_भ_लिखो(क्रमmat, arg_list);
	ACPI_MSG_SUFFIX;
	बहु_पूर्ण(arg_list);

	ACPI_MSG_REसूचीECT_END;
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_bios_error)

/*******************************************************************************
 *
 * FUNCTION:    acpi_bios_exception
 *
 * PARAMETERS:  module_name         - Caller's module name (क्रम error output)
 *              line_number         - Caller's line number (क्रम error output)
 *              status              - Status value to be decoded/क्रमmatted
 *              क्रमmat              - Prपूर्णांकf क्रमmat string + additional args
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक an "ACPI Firmware Error" message with module/line/version
 *              info as well as decoded acpi_status.
 *
 ******************************************************************************/
व्योम ACPI_INTERNAL_VAR_XFACE
acpi_bios_exception(स्थिर अक्षर *module_name,
		    u32 line_number,
		    acpi_status status, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची arg_list;

	ACPI_MSG_REसूचीECT_BEGIN;

	/* For AE_OK, just prपूर्णांक the message */

	अगर (ACPI_SUCCESS(status)) अणु
		acpi_os_म_लिखो(ACPI_MSG_BIOS_ERROR);

	पूर्ण अन्यथा अणु
		acpi_os_म_लिखो(ACPI_MSG_BIOS_ERROR "%s, ",
			       acpi_क्रमmat_exception(status));
	पूर्ण

	बहु_शुरू(arg_list, क्रमmat);
	acpi_os_भ_लिखो(क्रमmat, arg_list);
	ACPI_MSG_SUFFIX;
	बहु_पूर्ण(arg_list);

	ACPI_MSG_REसूचीECT_END;
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_bios_exception)

/*******************************************************************************
 *
 * FUNCTION:    acpi_bios_warning
 *
 * PARAMETERS:  module_name         - Caller's module name (क्रम warning output)
 *              line_number         - Caller's line number (क्रम warning output)
 *              क्रमmat              - Prपूर्णांकf क्रमmat string + additional args
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक "ACPI Firmware Warning" message with module/line/version
 *              info
 *
 ******************************************************************************/
व्योम ACPI_INTERNAL_VAR_XFACE
acpi_bios_warning(स्थिर अक्षर *module_name,
		  u32 line_number, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची arg_list;

	ACPI_MSG_REसूचीECT_BEGIN;
	acpi_os_म_लिखो(ACPI_MSG_BIOS_WARNING);

	बहु_शुरू(arg_list, क्रमmat);
	acpi_os_भ_लिखो(क्रमmat, arg_list);
	ACPI_MSG_SUFFIX;
	बहु_पूर्ण(arg_list);

	ACPI_MSG_REसूचीECT_END;
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_bios_warning)
#पूर्ण_अगर				/* ACPI_NO_ERROR_MESSAGES */
