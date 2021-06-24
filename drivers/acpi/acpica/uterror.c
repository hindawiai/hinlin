<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: uterror - Various पूर्णांकernal error/warning output functions
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("uterror")

/*
 * This module contains पूर्णांकernal error functions that may
 * be configured out.
 */
#अगर !defined (ACPI_NO_ERROR_MESSAGES)
/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_predefined_warning
 *
 * PARAMETERS:  module_name     - Caller's module name (क्रम error output)
 *              line_number     - Caller's line number (क्रम error output)
 *              pathname        - Full pathname to the node
 *              node_flags      - From Namespace node क्रम the method/object
 *              क्रमmat          - Prपूर्णांकf क्रमmat string + additional args
 *
 * RETURN:      None
 *
 * DESCRIPTION: Warnings क्रम the predefined validation module. Messages are
 *              only emitted the first समय a problem with a particular
 *              method/object is detected. This prevents a flood of error
 *              messages क्रम methods that are repeatedly evaluated.
 *
 ******************************************************************************/
व्योम ACPI_INTERNAL_VAR_XFACE
acpi_ut_predefined_warning(स्थिर अक्षर *module_name,
			   u32 line_number,
			   अक्षर *pathname,
			   u16 node_flags, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची arg_list;

	/*
	 * Warning messages क्रम this method/object will be disabled after the
	 * first समय a validation fails or an object is successfully repaired.
	 */
	अगर (node_flags & ANOBJ_EVALUATED) अणु
		वापस;
	पूर्ण

	acpi_os_म_लिखो(ACPI_MSG_WARNING "%s: ", pathname);

	बहु_शुरू(arg_list, क्रमmat);
	acpi_os_भ_लिखो(क्रमmat, arg_list);
	ACPI_MSG_SUFFIX;
	बहु_पूर्ण(arg_list);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_predefined_info
 *
 * PARAMETERS:  module_name     - Caller's module name (क्रम error output)
 *              line_number     - Caller's line number (क्रम error output)
 *              pathname        - Full pathname to the node
 *              node_flags      - From Namespace node क्रम the method/object
 *              क्रमmat          - Prपूर्णांकf क्रमmat string + additional args
 *
 * RETURN:      None
 *
 * DESCRIPTION: Info messages क्रम the predefined validation module. Messages
 *              are only emitted the first समय a problem with a particular
 *              method/object is detected. This prevents a flood of
 *              messages क्रम methods that are repeatedly evaluated.
 *
 ******************************************************************************/

व्योम ACPI_INTERNAL_VAR_XFACE
acpi_ut_predefined_info(स्थिर अक्षर *module_name,
			u32 line_number,
			अक्षर *pathname, u16 node_flags, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची arg_list;

	/*
	 * Warning messages क्रम this method/object will be disabled after the
	 * first समय a validation fails or an object is successfully repaired.
	 */
	अगर (node_flags & ANOBJ_EVALUATED) अणु
		वापस;
	पूर्ण

	acpi_os_म_लिखो(ACPI_MSG_INFO "%s: ", pathname);

	बहु_शुरू(arg_list, क्रमmat);
	acpi_os_भ_लिखो(क्रमmat, arg_list);
	ACPI_MSG_SUFFIX;
	बहु_पूर्ण(arg_list);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_predefined_bios_error
 *
 * PARAMETERS:  module_name     - Caller's module name (क्रम error output)
 *              line_number     - Caller's line number (क्रम error output)
 *              pathname        - Full pathname to the node
 *              node_flags      - From Namespace node क्रम the method/object
 *              क्रमmat          - Prपूर्णांकf क्रमmat string + additional args
 *
 * RETURN:      None
 *
 * DESCRIPTION: BIOS error message क्रम predefined names. Messages
 *              are only emitted the first समय a problem with a particular
 *              method/object is detected. This prevents a flood of
 *              messages क्रम methods that are repeatedly evaluated.
 *
 ******************************************************************************/

व्योम ACPI_INTERNAL_VAR_XFACE
acpi_ut_predefined_bios_error(स्थिर अक्षर *module_name,
			      u32 line_number,
			      अक्षर *pathname,
			      u16 node_flags, स्थिर अक्षर *क्रमmat, ...)
अणु
	बहु_सूची arg_list;

	/*
	 * Warning messages क्रम this method/object will be disabled after the
	 * first समय a validation fails or an object is successfully repaired.
	 */
	अगर (node_flags & ANOBJ_EVALUATED) अणु
		वापस;
	पूर्ण

	acpi_os_म_लिखो(ACPI_MSG_BIOS_ERROR "%s: ", pathname);

	बहु_शुरू(arg_list, क्रमmat);
	acpi_os_भ_लिखो(क्रमmat, arg_list);
	ACPI_MSG_SUFFIX;
	बहु_पूर्ण(arg_list);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_prefixed_namespace_error
 *
 * PARAMETERS:  module_name         - Caller's module name (क्रम error output)
 *              line_number         - Caller's line number (क्रम error output)
 *              prefix_scope        - Scope/Path that prefixes the पूर्णांकernal path
 *              पूर्णांकernal_path       - Name or path of the namespace node
 *              lookup_status       - Exception code from NS lookup
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक error message with the full pathname स्थिरructed this way:
 *
 *                  prefix_scope_node_full_path.बाह्यalized_पूर्णांकernal_path
 *
 * NOTE:        10/2017: Treat the major ns_lookup errors as firmware errors
 *
 ******************************************************************************/

व्योम
acpi_ut_prefixed_namespace_error(स्थिर अक्षर *module_name,
				 u32 line_number,
				 जोड़ acpi_generic_state *prefix_scope,
				 स्थिर अक्षर *पूर्णांकernal_path,
				 acpi_status lookup_status)
अणु
	अक्षर *full_path;
	स्थिर अक्षर *message;

	/*
	 * Main हालs:
	 * 1) Object creation, object must not alपढ़ोy exist
	 * 2) Object lookup, object must exist
	 */
	चयन (lookup_status) अणु
	हाल AE_ALREADY_EXISTS:

		acpi_os_म_लिखो(ACPI_MSG_BIOS_ERROR);
		message = "Failure creating named object";
		अवरोध;

	हाल AE_NOT_FOUND:

		acpi_os_म_लिखो(ACPI_MSG_BIOS_ERROR);
		message = "Could not resolve symbol";
		अवरोध;

	शेष:

		acpi_os_म_लिखो(ACPI_MSG_ERROR);
		message = "Failure resolving symbol";
		अवरोध;
	पूर्ण

	/* Concatenate the prefix path and the पूर्णांकernal path */

	full_path =
	    acpi_ns_build_prefixed_pathname(prefix_scope, पूर्णांकernal_path);

	acpi_os_म_लिखो("%s [%s], %s", message,
		       full_path ? full_path : "Could not get pathname",
		       acpi_क्रमmat_exception(lookup_status));

	अगर (full_path) अणु
		ACPI_FREE(full_path);
	पूर्ण

	ACPI_MSG_SUFFIX;
पूर्ण

#अगर_घोषित __OBSOLETE_FUNCTION
/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_namespace_error
 *
 * PARAMETERS:  module_name         - Caller's module name (क्रम error output)
 *              line_number         - Caller's line number (क्रम error output)
 *              पूर्णांकernal_name       - Name or path of the namespace node
 *              lookup_status       - Exception code from NS lookup
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक error message with the full pathname क्रम the NS node.
 *
 ******************************************************************************/

व्योम
acpi_ut_namespace_error(स्थिर अक्षर *module_name,
			u32 line_number,
			स्थिर अक्षर *पूर्णांकernal_name, acpi_status lookup_status)
अणु
	acpi_status status;
	u32 bad_name;
	अक्षर *name = शून्य;

	ACPI_MSG_REसूचीECT_BEGIN;
	acpi_os_म_लिखो(ACPI_MSG_ERROR);

	अगर (lookup_status == AE_BAD_CHARACTER) अणु

		/* There is a non-ascii अक्षरacter in the name */

		ACPI_MOVE_32_TO_32(&bad_name,
				   ACPI_CAST_PTR(u32, पूर्णांकernal_name));
		acpi_os_म_लिखो("[0x%.8X] (NON-ASCII)", bad_name);
	पूर्ण अन्यथा अणु
		/* Convert path to बाह्यal क्रमmat */

		status =
		    acpi_ns_बाह्यalize_name(ACPI_UINT32_MAX, पूर्णांकernal_name,
					     शून्य, &name);

		/* Prपूर्णांक target name */

		अगर (ACPI_SUCCESS(status)) अणु
			acpi_os_म_लिखो("[%s]", name);
		पूर्ण अन्यथा अणु
			acpi_os_म_लिखो("[COULD NOT EXTERNALIZE NAME]");
		पूर्ण

		अगर (name) अणु
			ACPI_FREE(name);
		पूर्ण
	पूर्ण

	acpi_os_म_लिखो(" Namespace lookup failure, %s",
		       acpi_क्रमmat_exception(lookup_status));

	ACPI_MSG_SUFFIX;
	ACPI_MSG_REसूचीECT_END;
पूर्ण
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_method_error
 *
 * PARAMETERS:  module_name         - Caller's module name (क्रम error output)
 *              line_number         - Caller's line number (क्रम error output)
 *              message             - Error message to use on failure
 *              prefix_node         - Prefix relative to the path
 *              path                - Path to the node (optional)
 *              method_status       - Execution status
 *
 * RETURN:      None
 *
 * DESCRIPTION: Prपूर्णांक error message with the full pathname क्रम the method.
 *
 ******************************************************************************/

व्योम
acpi_ut_method_error(स्थिर अक्षर *module_name,
		     u32 line_number,
		     स्थिर अक्षर *message,
		     काष्ठा acpi_namespace_node *prefix_node,
		     स्थिर अक्षर *path, acpi_status method_status)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node = prefix_node;

	ACPI_MSG_REसूचीECT_BEGIN;
	acpi_os_म_लिखो(ACPI_MSG_ERROR);

	अगर (path) अणु
		status = acpi_ns_get_node(prefix_node, path,
					  ACPI_NS_NO_UPSEARCH, &node);
		अगर (ACPI_FAILURE(status)) अणु
			acpi_os_म_लिखो("[Could not get node by pathname]");
		पूर्ण
	पूर्ण

	acpi_ns_prपूर्णांक_node_pathname(node, message);
	acpi_os_म_लिखो(" due to previous error (%s)",
		       acpi_क्रमmat_exception(method_status));

	ACPI_MSG_SUFFIX;
	ACPI_MSG_REसूचीECT_END;
पूर्ण

#पूर्ण_अगर				/* ACPI_NO_ERROR_MESSAGES */
