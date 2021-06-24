<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: uteval - Object evaluation
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_UTILITIES
ACPI_MODULE_NAME("uteval")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_evaluate_object
 *
 * PARAMETERS:  prefix_node         - Starting node
 *              path                - Path to object from starting node
 *              expected_वापस_types - Biपंचांगap of allowed वापस types
 *              वापस_desc         - Where a वापस value is stored
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Evaluates a namespace object and verअगरies the type of the
 *              वापस object. Common code that simplअगरies accessing objects
 *              that have required वापस objects of fixed types.
 *
 *              NOTE: Internal function, no parameter validation
 *
 ******************************************************************************/

acpi_status
acpi_ut_evaluate_object(काष्ठा acpi_namespace_node *prefix_node,
			स्थिर अक्षर *path,
			u32 expected_वापस_btypes,
			जोड़ acpi_opeअक्रम_object **वापस_desc)
अणु
	काष्ठा acpi_evaluate_info *info;
	acpi_status status;
	u32 वापस_btype;

	ACPI_FUNCTION_TRACE(ut_evaluate_object);

	/* Allocate the evaluation inक्रमmation block */

	info = ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_evaluate_info));
	अगर (!info) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	info->prefix_node = prefix_node;
	info->relative_pathname = path;

	/* Evaluate the object/method */

	status = acpi_ns_evaluate(info);
	अगर (ACPI_FAILURE(status)) अणु
		अगर (status == AE_NOT_FOUND) अणु
			ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
					  "[%4.4s.%s] was not found\n",
					  acpi_ut_get_node_name(prefix_node),
					  path));
		पूर्ण अन्यथा अणु
			ACPI_ERROR_METHOD("Method execution failed",
					  prefix_node, path, status);
		पूर्ण

		जाओ cleanup;
	पूर्ण

	/* Did we get a वापस object? */

	अगर (!info->वापस_object) अणु
		अगर (expected_वापस_btypes) अणु
			ACPI_ERROR_METHOD("No object was returned from",
					  prefix_node, path, AE_NOT_EXIST);

			status = AE_NOT_EXIST;
		पूर्ण

		जाओ cleanup;
	पूर्ण

	/* Map the वापस object type to the biपंचांगapped type */

	चयन ((info->वापस_object)->common.type) अणु
	हाल ACPI_TYPE_INTEGER:

		वापस_btype = ACPI_BTYPE_INTEGER;
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		वापस_btype = ACPI_BTYPE_BUFFER;
		अवरोध;

	हाल ACPI_TYPE_STRING:

		वापस_btype = ACPI_BTYPE_STRING;
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:

		वापस_btype = ACPI_BTYPE_PACKAGE;
		अवरोध;

	शेष:

		वापस_btype = 0;
		अवरोध;
	पूर्ण

	अगर ((acpi_gbl_enable_पूर्णांकerpreter_slack) && (!expected_वापस_btypes)) अणु
		/*
		 * We received a वापस object, but one was not expected. This can
		 * happen frequently अगर the "implicit return" feature is enabled.
		 * Just delete the वापस object and वापस AE_OK.
		 */
		acpi_ut_हटाओ_reference(info->वापस_object);
		जाओ cleanup;
	पूर्ण

	/* Is the वापस object one of the expected types? */

	अगर (!(expected_वापस_btypes & वापस_btype)) अणु
		ACPI_ERROR_METHOD("Return object type is incorrect",
				  prefix_node, path, AE_TYPE);

		ACPI_ERROR((AE_INFO,
			    "Type returned from %s was incorrect: %s, expected Btypes: 0x%X",
			    path,
			    acpi_ut_get_object_type_name(info->वापस_object),
			    expected_वापस_btypes));

		/* On error निकास, we must delete the वापस object */

		acpi_ut_हटाओ_reference(info->वापस_object);
		status = AE_TYPE;
		जाओ cleanup;
	पूर्ण

	/* Object type is OK, वापस it */

	*वापस_desc = info->वापस_object;

cleanup:
	ACPI_FREE(info);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_evaluate_numeric_object
 *
 * PARAMETERS:  object_name         - Object name to be evaluated
 *              device_node         - Node क्रम the device
 *              value               - Where the value is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Evaluates a numeric namespace object क्रम a selected device
 *              and stores result in *Value.
 *
 *              NOTE: Internal function, no parameter validation
 *
 ******************************************************************************/

acpi_status
acpi_ut_evaluate_numeric_object(स्थिर अक्षर *object_name,
				काष्ठा acpi_namespace_node *device_node,
				u64 *value)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ut_evaluate_numeric_object);

	status = acpi_ut_evaluate_object(device_node, object_name,
					 ACPI_BTYPE_INTEGER, &obj_desc);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Get the वापसed Integer */

	*value = obj_desc->पूर्णांकeger.value;

	/* On निकास, we must delete the वापस object */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_execute_STA
 *
 * PARAMETERS:  device_node         - Node क्रम the device
 *              flags               - Where the status flags are वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Executes _STA क्रम selected device and stores results in
 *              *Flags. If _STA करोes not exist, then the device is assumed
 *              to be present/functional/enabled (as per the ACPI spec).
 *
 *              NOTE: Internal function, no parameter validation
 *
 ******************************************************************************/

acpi_status
acpi_ut_execute_STA(काष्ठा acpi_namespace_node *device_node, u32 * flags)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;

	ACPI_FUNCTION_TRACE(ut_execute_STA);

	status = acpi_ut_evaluate_object(device_node, METHOD_NAME__STA,
					 ACPI_BTYPE_INTEGER, &obj_desc);
	अगर (ACPI_FAILURE(status)) अणु
		अगर (AE_NOT_FOUND == status) अणु
			/*
			 * अगर _STA करोes not exist, then (as per the ACPI specअगरication),
			 * the वापसed flags will indicate that the device is present,
			 * functional, and enabled.
			 */
			ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
					  "_STA on %4.4s was not found, assuming device is present\n",
					  acpi_ut_get_node_name(device_node)));

			*flags = ACPI_UINT32_MAX;
			status = AE_OK;
		पूर्ण

		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Extract the status flags */

	*flags = (u32) obj_desc->पूर्णांकeger.value;

	/* On निकास, we must delete the वापस object */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ut_execute_घातer_methods
 *
 * PARAMETERS:  device_node         - Node क्रम the device
 *              method_names        - Array of घातer method names
 *              method_count        - Number of methods to execute
 *              out_values          - Where the घातer method values are वापसed
 *
 * RETURN:      Status, out_values
 *
 * DESCRIPTION: Executes the specअगरied घातer methods क्रम the device and वापसs
 *              the result(s).
 *
 *              NOTE: Internal function, no parameter validation
 *
******************************************************************************/

acpi_status
acpi_ut_execute_घातer_methods(काष्ठा acpi_namespace_node *device_node,
			      स्थिर अक्षर **method_names,
			      u8 method_count, u8 *out_values)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	acpi_status status;
	acpi_status final_status = AE_NOT_FOUND;
	u32 i;

	ACPI_FUNCTION_TRACE(ut_execute_घातer_methods);

	क्रम (i = 0; i < method_count; i++) अणु
		/*
		 * Execute the घातer method (_sx_d or _sx_w). The only allowable
		 * वापस type is an Integer.
		 */
		status = acpi_ut_evaluate_object(device_node,
						 ACPI_CAST_PTR(अक्षर,
							       method_names[i]),
						 ACPI_BTYPE_INTEGER, &obj_desc);
		अगर (ACPI_SUCCESS(status)) अणु
			out_values[i] = (u8)obj_desc->पूर्णांकeger.value;

			/* Delete the वापस object */

			acpi_ut_हटाओ_reference(obj_desc);
			final_status = AE_OK;	/* At least one value is valid */
			जारी;
		पूर्ण

		out_values[i] = ACPI_UINT8_MAX;
		अगर (status == AE_NOT_FOUND) अणु
			जारी;	/* Ignore अगर not found */
		पूर्ण

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Failed %s on Device %4.4s, %s\n",
				  ACPI_CAST_PTR(अक्षर, method_names[i]),
				  acpi_ut_get_node_name(device_node),
				  acpi_क्रमmat_exception(status)));
	पूर्ण

	वापस_ACPI_STATUS(final_status);
पूर्ण
