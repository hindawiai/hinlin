<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exresolv - AML Interpreter object resolution
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "amlcode.h"
#समावेश "acdispat.h"
#समावेश "acinterp.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exresolv")

/* Local prototypes */
अटल acpi_status
acpi_ex_resolve_object_to_value(जोड़ acpi_opeअक्रम_object **stack_ptr,
				काष्ठा acpi_walk_state *walk_state);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_resolve_to_value
 *
 * PARAMETERS:  **stack_ptr         - Poपूर्णांकs to entry on obj_stack, which can
 *                                    be either an (जोड़ acpi_opeअक्रम_object *)
 *                                    or an acpi_handle.
 *              walk_state          - Current method state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Convert Reference objects to values
 *
 ******************************************************************************/

acpi_status
acpi_ex_resolve_to_value(जोड़ acpi_opeअक्रम_object **stack_ptr,
			 काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE_PTR(ex_resolve_to_value, stack_ptr);

	अगर (!stack_ptr || !*stack_ptr) अणु
		ACPI_ERROR((AE_INFO, "Internal - null pointer"));
		वापस_ACPI_STATUS(AE_AML_NO_OPERAND);
	पूर्ण

	/*
	 * The entity poपूर्णांकed to by the stack_ptr can be either
	 * 1) A valid जोड़ acpi_opeअक्रम_object, or
	 * 2) A काष्ठा acpi_namespace_node (named_obj)
	 */
	अगर (ACPI_GET_DESCRIPTOR_TYPE(*stack_ptr) == ACPI_DESC_TYPE_OPERAND) अणु
		status = acpi_ex_resolve_object_to_value(stack_ptr, walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		अगर (!*stack_ptr) अणु
			ACPI_ERROR((AE_INFO, "Internal - null pointer"));
			वापस_ACPI_STATUS(AE_AML_NO_OPERAND);
		पूर्ण
	पूर्ण

	/*
	 * Object on the stack may have changed अगर acpi_ex_resolve_object_to_value()
	 * was called (i.e., we can't use an _अन्यथा_ here.)
	 */
	अगर (ACPI_GET_DESCRIPTOR_TYPE(*stack_ptr) == ACPI_DESC_TYPE_NAMED) अणु
		status =
		    acpi_ex_resolve_node_to_value(ACPI_CAST_INसूचीECT_PTR
						  (काष्ठा acpi_namespace_node,
						   stack_ptr), walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Resolved object %p\n", *stack_ptr));
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_resolve_object_to_value
 *
 * PARAMETERS:  stack_ptr       - Poपूर्णांकer to an पूर्णांकernal object
 *              walk_state      - Current method state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieve the value from an पूर्णांकernal object. The Reference type
 *              uses the associated AML opcode to determine the value.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ex_resolve_object_to_value(जोड़ acpi_opeअक्रम_object **stack_ptr,
				काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_opeअक्रम_object *stack_desc;
	जोड़ acpi_opeअक्रम_object *obj_desc = शून्य;
	u8 ref_type;

	ACPI_FUNCTION_TRACE(ex_resolve_object_to_value);

	stack_desc = *stack_ptr;

	/* This is an object of type जोड़ acpi_opeअक्रम_object */

	चयन (stack_desc->common.type) अणु
	हाल ACPI_TYPE_LOCAL_REFERENCE:

		ref_type = stack_desc->reference.class;

		चयन (ref_type) अणु
		हाल ACPI_REFCLASS_LOCAL:
		हाल ACPI_REFCLASS_ARG:
			/*
			 * Get the local from the method's state info
			 * Note: this increments the local's object reference count
			 */
			status = acpi_ds_method_data_get_value(ref_type,
							       stack_desc->
							       reference.value,
							       walk_state,
							       &obj_desc);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण

			ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
					  "[Arg/Local %X] ValueObj is %p\n",
					  stack_desc->reference.value,
					  obj_desc));

			/*
			 * Now we can delete the original Reference Object and
			 * replace it with the resolved value
			 */
			acpi_ut_हटाओ_reference(stack_desc);
			*stack_ptr = obj_desc;
			अवरोध;

		हाल ACPI_REFCLASS_INDEX:

			चयन (stack_desc->reference.target_type) अणु
			हाल ACPI_TYPE_BUFFER_FIELD:

				/* Just वापस - करो not dereference */
				अवरोध;

			हाल ACPI_TYPE_PACKAGE:

				/* If method call or copy_object - करो not dereference */

				अगर ((walk_state->opcode ==
				     AML_INT_METHODCALL_OP)
				    || (walk_state->opcode ==
					AML_COPY_OBJECT_OP)) अणु
					अवरोध;
				पूर्ण

				/* Otherwise, dereference the package_index to a package element */

				obj_desc = *stack_desc->reference.where;
				अगर (obj_desc) अणु
					/*
					 * Valid object descriptor, copy poपूर्णांकer to वापस value
					 * (i.e., dereference the package index)
					 * Delete the ref object, increment the वापसed object
					 */
					acpi_ut_add_reference(obj_desc);
					*stack_ptr = obj_desc;
				पूर्ण अन्यथा अणु
					/*
					 * A शून्य object descriptor means an uninitialized element of
					 * the package, can't dereference it
					 */
					ACPI_ERROR((AE_INFO,
						    "Attempt to dereference an Index to "
						    "NULL package element Idx=%p",
						    stack_desc));
					status = AE_AML_UNINITIALIZED_ELEMENT;
				पूर्ण
				अवरोध;

			शेष:

				/* Invalid reference object */

				ACPI_ERROR((AE_INFO,
					    "Unknown TargetType 0x%X in Index/Reference object %p",
					    stack_desc->reference.target_type,
					    stack_desc));
				status = AE_AML_INTERNAL;
				अवरोध;
			पूर्ण
			अवरोध;

		हाल ACPI_REFCLASS_REFOF:
		हाल ACPI_REFCLASS_DEBUG:
		हाल ACPI_REFCLASS_TABLE:

			/* Just leave the object as-is, करो not dereference */

			अवरोध;

		हाल ACPI_REFCLASS_NAME:	/* Reference to a named object */

			/* Dereference the name */

			अगर ((stack_desc->reference.node->type ==
			     ACPI_TYPE_DEVICE)
			    || (stack_desc->reference.node->type ==
				ACPI_TYPE_THERMAL)) अणु

				/* These node types करो not have 'real' subobjects */

				*stack_ptr = (व्योम *)stack_desc->reference.node;
			पूर्ण अन्यथा अणु
				/* Get the object poपूर्णांकed to by the namespace node */

				*stack_ptr =
				    (stack_desc->reference.node)->object;
				acpi_ut_add_reference(*stack_ptr);
			पूर्ण

			acpi_ut_हटाओ_reference(stack_desc);
			अवरोध;

		शेष:

			ACPI_ERROR((AE_INFO,
				    "Unknown Reference type 0x%X in %p",
				    ref_type, stack_desc));
			status = AE_AML_INTERNAL;
			अवरोध;
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		status = acpi_ds_get_buffer_arguments(stack_desc);
		अवरोध;

	हाल ACPI_TYPE_PACKAGE:

		status = acpi_ds_get_package_arguments(stack_desc);
		अवरोध;

	हाल ACPI_TYPE_BUFFER_FIELD:
	हाल ACPI_TYPE_LOCAL_REGION_FIELD:
	हाल ACPI_TYPE_LOCAL_BANK_FIELD:
	हाल ACPI_TYPE_LOCAL_INDEX_FIELD:

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "FieldRead SourceDesc=%p Type=%X\n",
				  stack_desc, stack_desc->common.type));

		status =
		    acpi_ex_पढ़ो_data_from_field(walk_state, stack_desc,
						 &obj_desc);

		/* Remove a reference to the original opeअक्रम, then override */

		acpi_ut_हटाओ_reference(*stack_ptr);
		*stack_ptr = (व्योम *)obj_desc;
		अवरोध;

	शेष:

		अवरोध;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_resolve_multiple
 *
 * PARAMETERS:  walk_state          - Current state (contains AML opcode)
 *              opeअक्रम             - Starting poपूर्णांक क्रम resolution
 *              वापस_type         - Where the object type is वापसed
 *              वापस_desc         - Where the resolved object is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Return the base object and type. Traverse a reference list अगर
 *              necessary to get to the base object.
 *
 ******************************************************************************/

acpi_status
acpi_ex_resolve_multiple(काष्ठा acpi_walk_state *walk_state,
			 जोड़ acpi_opeअक्रम_object *opeअक्रम,
			 acpi_object_type *वापस_type,
			 जोड़ acpi_opeअक्रम_object **वापस_desc)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc = ACPI_CAST_PTR(व्योम, opeअक्रम);
	काष्ठा acpi_namespace_node *node =
	    ACPI_CAST_PTR(काष्ठा acpi_namespace_node, opeअक्रम);
	acpi_object_type type;
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_ex_resolve_multiple);

	/* Opeअक्रम can be either a namespace node or an opeअक्रम descriptor */

	चयन (ACPI_GET_DESCRIPTOR_TYPE(obj_desc)) अणु
	हाल ACPI_DESC_TYPE_OPERAND:

		type = obj_desc->common.type;
		अवरोध;

	हाल ACPI_DESC_TYPE_NAMED:

		type = ((काष्ठा acpi_namespace_node *)obj_desc)->type;
		obj_desc = acpi_ns_get_attached_object(node);

		/* If we had an Alias node, use the attached object क्रम type info */

		अगर (type == ACPI_TYPE_LOCAL_ALIAS) अणु
			type = ((काष्ठा acpi_namespace_node *)obj_desc)->type;
			obj_desc = acpi_ns_get_attached_object((काष्ठा
								acpi_namespace_node
								*)obj_desc);
		पूर्ण

		चयन (type) अणु
		हाल ACPI_TYPE_DEVICE:
		हाल ACPI_TYPE_THERMAL:

			/* These types have no attached subobject */
			अवरोध;

		शेष:

			/* All other types require a subobject */

			अगर (!obj_desc) अणु
				ACPI_ERROR((AE_INFO,
					    "[%4.4s] Node is unresolved or uninitialized",
					    acpi_ut_get_node_name(node)));
				वापस_ACPI_STATUS(AE_AML_UNINITIALIZED_NODE);
			पूर्ण
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
	पूर्ण

	/* If type is anything other than a reference, we are करोne */

	अगर (type != ACPI_TYPE_LOCAL_REFERENCE) अणु
		जाओ निकास;
	पूर्ण

	/*
	 * For reference objects created via the ref_of, Index, or Load/load_table
	 * चालकs, we need to get to the base object (as per the ACPI
	 * specअगरication of the object_type and size_of चालकs). This means
	 * traversing the list of possibly many nested references.
	 */
	जबतक (obj_desc->common.type == ACPI_TYPE_LOCAL_REFERENCE) अणु
		चयन (obj_desc->reference.class) अणु
		हाल ACPI_REFCLASS_REFOF:
		हाल ACPI_REFCLASS_NAME:

			/* Dereference the reference poपूर्णांकer */

			अगर (obj_desc->reference.class == ACPI_REFCLASS_REFOF) अणु
				node = obj_desc->reference.object;
			पूर्ण अन्यथा अणु	/* AML_INT_NAMEPATH_OP */

				node = obj_desc->reference.node;
			पूर्ण

			/* All "References" poपूर्णांक to a NS node */

			अगर (ACPI_GET_DESCRIPTOR_TYPE(node) !=
			    ACPI_DESC_TYPE_NAMED) अणु
				ACPI_ERROR((AE_INFO,
					    "Not a namespace node %p [%s]",
					    node,
					    acpi_ut_get_descriptor_name(node)));
				वापस_ACPI_STATUS(AE_AML_INTERNAL);
			पूर्ण

			/* Get the attached object */

			obj_desc = acpi_ns_get_attached_object(node);
			अगर (!obj_desc) अणु

				/* No object, use the NS node type */

				type = acpi_ns_get_type(node);
				जाओ निकास;
			पूर्ण

			/* Check क्रम circular references */

			अगर (obj_desc == opeअक्रम) अणु
				वापस_ACPI_STATUS(AE_AML_CIRCULAR_REFERENCE);
			पूर्ण
			अवरोध;

		हाल ACPI_REFCLASS_INDEX:

			/* Get the type of this reference (index पूर्णांकo another object) */

			type = obj_desc->reference.target_type;
			अगर (type != ACPI_TYPE_PACKAGE) अणु
				जाओ निकास;
			पूर्ण

			/*
			 * The मुख्य object is a package, we want to get the type
			 * of the inभागidual package element that is referenced by
			 * the index.
			 *
			 * This could of course in turn be another reference object.
			 */
			obj_desc = *(obj_desc->reference.where);
			अगर (!obj_desc) अणु

				/* शून्य package elements are allowed */

				type = 0;	/* Uninitialized */
				जाओ निकास;
			पूर्ण
			अवरोध;

		हाल ACPI_REFCLASS_TABLE:

			type = ACPI_TYPE_DDB_HANDLE;
			जाओ निकास;

		हाल ACPI_REFCLASS_LOCAL:
		हाल ACPI_REFCLASS_ARG:

			अगर (वापस_desc) अणु
				status =
				    acpi_ds_method_data_get_value(obj_desc->
								  reference.
								  class,
								  obj_desc->
								  reference.
								  value,
								  walk_state,
								  &obj_desc);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण
				acpi_ut_हटाओ_reference(obj_desc);
			पूर्ण अन्यथा अणु
				status =
				    acpi_ds_method_data_get_node(obj_desc->
								 reference.
								 class,
								 obj_desc->
								 reference.
								 value,
								 walk_state,
								 &node);
				अगर (ACPI_FAILURE(status)) अणु
					वापस_ACPI_STATUS(status);
				पूर्ण

				obj_desc = acpi_ns_get_attached_object(node);
				अगर (!obj_desc) अणु
					type = ACPI_TYPE_ANY;
					जाओ निकास;
				पूर्ण
			पूर्ण
			अवरोध;

		हाल ACPI_REFCLASS_DEBUG:

			/* The Debug Object is of type "DebugObject" */

			type = ACPI_TYPE_DEBUG_OBJECT;
			जाओ निकास;

		शेष:

			ACPI_ERROR((AE_INFO,
				    "Unknown Reference Class 0x%2.2X",
				    obj_desc->reference.class));
			वापस_ACPI_STATUS(AE_AML_INTERNAL);
		पूर्ण
	पूर्ण

	/*
	 * Now we are guaranteed to have an object that has not been created
	 * via the ref_of or Index चालकs.
	 */
	type = obj_desc->common.type;

निकास:
	/* Convert पूर्णांकernal types to बाह्यal types */

	चयन (type) अणु
	हाल ACPI_TYPE_LOCAL_REGION_FIELD:
	हाल ACPI_TYPE_LOCAL_BANK_FIELD:
	हाल ACPI_TYPE_LOCAL_INDEX_FIELD:

		type = ACPI_TYPE_FIELD_UNIT;
		अवरोध;

	हाल ACPI_TYPE_LOCAL_SCOPE:

		/* Per ACPI Specअगरication, Scope is untyped */

		type = ACPI_TYPE_ANY;
		अवरोध;

	शेष:

		/* No change to Type required */

		अवरोध;
	पूर्ण

	*वापस_type = type;
	अगर (वापस_desc) अणु
		*वापस_desc = obj_desc;
	पूर्ण
	वापस_ACPI_STATUS(AE_OK);
पूर्ण
