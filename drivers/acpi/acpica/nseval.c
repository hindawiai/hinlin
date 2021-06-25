<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: nseval - Object evaluation, includes control method execution
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acparser.h"
#समावेश "acinterp.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nseval")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_evaluate
 *
 * PARAMETERS:  info            - Evaluation info block, contains these fields
 *                                and more:
 *                  prefix_node     - Prefix or Method/Object Node to execute
 *                  relative_path   - Name of method to execute, If शून्य, the
 *                                    Node is the object to execute
 *                  parameters      - List of parameters to pass to the method,
 *                                    terminated by शून्य. Params itself may be
 *                                    शून्य अगर no parameters are being passed.
 *                  parameter_type  - Type of Parameter list
 *                  वापस_object   - Where to put method's वापस value (अगर
 *                                    any). If शून्य, no value is वापसed.
 *                  flags           - ACPI_IGNORE_RETURN_VALUE to delete वापस
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Execute a control method or वापस the current value of an
 *              ACPI namespace object.
 *
 * MUTEX:       Locks पूर्णांकerpreter
 *
 ******************************************************************************/
acpi_status acpi_ns_evaluate(काष्ठा acpi_evaluate_info *info)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ns_evaluate);

	अगर (!info) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	अगर (!info->node) अणु
		/*
		 * Get the actual namespace node क्रम the target object अगर we
		 * need to. Handles these हालs:
		 *
		 * 1) Null node, valid pathname from root (असलolute path)
		 * 2) Node and valid pathname (path relative to Node)
		 * 3) Node, Null pathname
		 */
		status =
		    acpi_ns_get_node(info->prefix_node, info->relative_pathname,
				     ACPI_NS_NO_UPSEARCH, &info->node);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	/*
	 * For a method alias, we must grab the actual method node so that
	 * proper scoping context will be established beक्रमe execution.
	 */
	अगर (acpi_ns_get_type(info->node) == ACPI_TYPE_LOCAL_METHOD_ALIAS) अणु
		info->node =
		    ACPI_CAST_PTR(काष्ठा acpi_namespace_node,
				  info->node->object);
	पूर्ण

	/* Complete the info block initialization */

	info->वापस_object = शून्य;
	info->node_flags = info->node->flags;
	info->obj_desc = acpi_ns_get_attached_object(info->node);

	ACPI_DEBUG_PRINT((ACPI_DB_NAMES, "%s [%p] Value %p\n",
			  info->relative_pathname, info->node,
			  acpi_ns_get_attached_object(info->node)));

	/* Get info अगर we have a predefined name (_HID, etc.) */

	info->predefined =
	    acpi_ut_match_predefined_method(info->node->name.ascii);

	/* Get the full pathname to the object, क्रम use in warning messages */

	info->full_pathname = acpi_ns_get_normalized_pathname(info->node, TRUE);
	अगर (!info->full_pathname) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/* Optional object evaluation log */

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_EVALUATION,
			      "%-26s:  %s (%s)\n", "   Enter evaluation",
			      &info->full_pathname[1],
			      acpi_ut_get_type_name(info->node->type)));

	/* Count the number of arguments being passed in */

	info->param_count = 0;
	अगर (info->parameters) अणु
		जबतक (info->parameters[info->param_count]) अणु
			info->param_count++;
		पूर्ण

		/* Warn on impossible argument count */

		अगर (info->param_count > ACPI_METHOD_NUM_ARGS) अणु
			ACPI_WARN_PREDEFINED((AE_INFO, info->full_pathname,
					      ACPI_WARN_ALWAYS,
					      "Excess arguments (%u) - using only %u",
					      info->param_count,
					      ACPI_METHOD_NUM_ARGS));

			info->param_count = ACPI_METHOD_NUM_ARGS;
		पूर्ण
	पूर्ण

	/*
	 * For predefined names: Check that the declared argument count
	 * matches the ACPI spec -- otherwise this is a BIOS error.
	 */
	acpi_ns_check_acpi_compliance(info->full_pathname, info->node,
				      info->predefined);

	/*
	 * For all names: Check that the incoming argument count क्रम
	 * this method/object matches the actual ASL/AML definition.
	 */
	acpi_ns_check_argument_count(info->full_pathname, info->node,
				     info->param_count, info->predefined);

	/* For predefined names: Typecheck all incoming arguments */

	acpi_ns_check_argument_types(info);

	/*
	 * Three major evaluation हालs:
	 *
	 * 1) Object types that cannot be evaluated by definition
	 * 2) The object is a control method -- execute it
	 * 3) The object is not a method -- just वापस it's current value
	 */
	चयन (acpi_ns_get_type(info->node)) अणु
	हाल ACPI_TYPE_ANY:
	हाल ACPI_TYPE_DEVICE:
	हाल ACPI_TYPE_EVENT:
	हाल ACPI_TYPE_MUTEX:
	हाल ACPI_TYPE_REGION:
	हाल ACPI_TYPE_THERMAL:
	हाल ACPI_TYPE_LOCAL_SCOPE:
		/*
		 * 1) Disallow evaluation of these object types. For these,
		 *    object evaluation is undefined.
		 */
		ACPI_ERROR((AE_INFO,
			    "%s: This object type [%s] "
			    "never contains data and cannot be evaluated",
			    info->full_pathname,
			    acpi_ut_get_type_name(info->node->type)));

		status = AE_TYPE;
		जाओ cleanup;

	हाल ACPI_TYPE_METHOD:
		/*
		 * 2) Object is a control method - execute it
		 */

		/* Verअगरy that there is a method object associated with this node */

		अगर (!info->obj_desc) अणु
			ACPI_ERROR((AE_INFO,
				    "%s: Method has no attached sub-object",
				    info->full_pathname));
			status = AE_शून्य_OBJECT;
			जाओ cleanup;
		पूर्ण

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "**** Execute method [%s] at AML address %p length %X\n",
				  info->full_pathname,
				  info->obj_desc->method.aml_start + 1,
				  info->obj_desc->method.aml_length - 1));

		/*
		 * Any namespace deletion must acquire both the namespace and
		 * पूर्णांकerpreter locks to ensure that no thपढ़ो is using the portion of
		 * the namespace that is being deleted.
		 *
		 * Execute the method via the पूर्णांकerpreter. The पूर्णांकerpreter is locked
		 * here beक्रमe calling पूर्णांकo the AML parser
		 */
		acpi_ex_enter_पूर्णांकerpreter();
		status = acpi_ps_execute_method(info);
		acpi_ex_निकास_पूर्णांकerpreter();
		अवरोध;

	शेष:
		/*
		 * 3) All other non-method objects -- get the current object value
		 */

		/*
		 * Some objects require additional resolution steps (e.g., the Node
		 * may be a field that must be पढ़ो, etc.) -- we can't just grab
		 * the object out of the node.
		 *
		 * Use resolve_node_to_value() to get the associated value.
		 *
		 * NOTE: we can get away with passing in शून्य क्रम a walk state because
		 * the Node is guaranteed to not be a reference to either a method
		 * local or a method argument (because this पूर्णांकerface is never called
		 * from a running method.)
		 *
		 * Even though we करो not directly invoke the पूर्णांकerpreter क्रम object
		 * resolution, we must lock it because we could access an op_region.
		 * The op_region access code assumes that the पूर्णांकerpreter is locked.
		 */
		acpi_ex_enter_पूर्णांकerpreter();

		/* TBD: resolve_node_to_value has a strange पूर्णांकerface, fix */

		info->वापस_object =
		    ACPI_CAST_PTR(जोड़ acpi_opeअक्रम_object, info->node);

		status =
		    acpi_ex_resolve_node_to_value(ACPI_CAST_INसूचीECT_PTR
						  (काष्ठा acpi_namespace_node,
						   &info->वापस_object), शून्य);
		acpi_ex_निकास_पूर्णांकerpreter();

		अगर (ACPI_FAILURE(status)) अणु
			info->वापस_object = शून्य;
			जाओ cleanup;
		पूर्ण

		ACPI_DEBUG_PRINT((ACPI_DB_NAMES, "Returned object %p [%s]\n",
				  info->वापस_object,
				  acpi_ut_get_object_type_name(info->
							       वापस_object)));

		status = AE_CTRL_RETURN_VALUE;	/* Always has a "return value" */
		अवरोध;
	पूर्ण

	/*
	 * For predefined names, check the वापस value against the ACPI
	 * specअगरication. Some incorrect वापस value types are repaired.
	 */
	(व्योम)acpi_ns_check_वापस_value(info->node, info, info->param_count,
					 status, &info->वापस_object);

	/* Check अगर there is a वापस value that must be dealt with */

	अगर (status == AE_CTRL_RETURN_VALUE) अणु

		/* If caller करोes not want the वापस value, delete it */

		अगर (info->flags & ACPI_IGNORE_RETURN_VALUE) अणु
			acpi_ut_हटाओ_reference(info->वापस_object);
			info->वापस_object = शून्य;
		पूर्ण

		/* Map AE_CTRL_RETURN_VALUE to AE_OK, we are करोne with it */

		status = AE_OK;
	पूर्ण अन्यथा अगर (ACPI_FAILURE(status)) अणु

		/* If वापस_object exists, delete it */

		अगर (info->वापस_object) अणु
			acpi_ut_हटाओ_reference(info->वापस_object);
			info->वापस_object = शून्य;
		पूर्ण
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_NAMES,
			  "*** Completed evaluation of object %s ***\n",
			  info->relative_pathname));

cleanup:
	/* Optional object evaluation log */

	ACPI_DEBUG_PRINT_RAW((ACPI_DB_EVALUATION,
			      "%-26s:  %s\n", "   Exit evaluation",
			      &info->full_pathname[1]));

	/*
	 * Namespace was unlocked by the handling acpi_ns* function, so we
	 * just मुक्त the pathname and वापस
	 */
	ACPI_FREE(info->full_pathname);
	info->full_pathname = शून्य;
	वापस_ACPI_STATUS(status);
पूर्ण
