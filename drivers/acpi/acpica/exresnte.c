<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exresnte - AML Interpreter object resolution
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdispat.h"
#समावेश "acinterp.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exresnte")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_resolve_node_to_value
 *
 * PARAMETERS:  object_ptr      - Poपूर्णांकer to a location that contains
 *                                a poपूर्णांकer to a NS node, and will receive a
 *                                poपूर्णांकer to the resolved object.
 *              walk_state      - Current state. Valid only अगर executing AML
 *                                code. शून्य अगर simply resolving an object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Resolve a Namespace node to a valued object
 *
 * Note: क्रम some of the data types, the poपूर्णांकer attached to the Node
 * can be either a poपूर्णांकer to an actual पूर्णांकernal object or a poपूर्णांकer पूर्णांकo the
 * AML stream itself. These types are currently:
 *
 *      ACPI_TYPE_INTEGER
 *      ACPI_TYPE_STRING
 *      ACPI_TYPE_BUFFER
 *      ACPI_TYPE_MUTEX
 *      ACPI_TYPE_PACKAGE
 *
 ******************************************************************************/
acpi_status
acpi_ex_resolve_node_to_value(काष्ठा acpi_namespace_node **object_ptr,
			      काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_opeअक्रम_object *source_desc;
	जोड़ acpi_opeअक्रम_object *obj_desc = शून्य;
	काष्ठा acpi_namespace_node *node;
	acpi_object_type entry_type;

	ACPI_FUNCTION_TRACE(ex_resolve_node_to_value);

	/*
	 * The stack poपूर्णांकer poपूर्णांकs to a काष्ठा acpi_namespace_node (Node). Get the
	 * object that is attached to the Node.
	 */
	node = *object_ptr;
	source_desc = acpi_ns_get_attached_object(node);
	entry_type = acpi_ns_get_type((acpi_handle)node);

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Entry=%p SourceDesc=%p [%s]\n",
			  node, source_desc,
			  acpi_ut_get_type_name(entry_type)));

	अगर ((entry_type == ACPI_TYPE_LOCAL_ALIAS) ||
	    (entry_type == ACPI_TYPE_LOCAL_METHOD_ALIAS)) अणु

		/* There is always exactly one level of indirection */

		node = ACPI_CAST_PTR(काष्ठा acpi_namespace_node, node->object);
		source_desc = acpi_ns_get_attached_object(node);
		entry_type = acpi_ns_get_type((acpi_handle)node);
		*object_ptr = node;
	पूर्ण

	/*
	 * Several object types require no further processing:
	 * 1) Device/Thermal objects करोn't have a "real" subobject, वापस Node
	 * 2) Method locals and arguments have a pseuकरो-Node
	 * 3) 10/2007: Added method type to assist with Package स्थिरruction.
	 */
	अगर ((entry_type == ACPI_TYPE_DEVICE) ||
	    (entry_type == ACPI_TYPE_THERMAL) ||
	    (entry_type == ACPI_TYPE_METHOD) ||
	    (node->flags & (ANOBJ_METHOD_ARG | ANOBJ_METHOD_LOCAL))) अणु
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	अगर (!source_desc) अणु
		ACPI_ERROR((AE_INFO, "No object attached to node [%4.4s] %p",
			    node->name.ascii, node));
		वापस_ACPI_STATUS(AE_AML_UNINITIALIZED_NODE);
	पूर्ण

	/*
	 * Action is based on the type of the Node, which indicates the type
	 * of the attached object or poपूर्णांकer
	 */
	चयन (entry_type) अणु
	हाल ACPI_TYPE_PACKAGE:

		अगर (source_desc->common.type != ACPI_TYPE_PACKAGE) अणु
			ACPI_ERROR((AE_INFO, "Object not a Package, type %s",
				    acpi_ut_get_object_type_name(source_desc)));
			वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		पूर्ण

		status = acpi_ds_get_package_arguments(source_desc);
		अगर (ACPI_SUCCESS(status)) अणु

			/* Return an additional reference to the object */

			obj_desc = source_desc;
			acpi_ut_add_reference(obj_desc);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_BUFFER:

		अगर (source_desc->common.type != ACPI_TYPE_BUFFER) अणु
			ACPI_ERROR((AE_INFO, "Object not a Buffer, type %s",
				    acpi_ut_get_object_type_name(source_desc)));
			वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		पूर्ण

		status = acpi_ds_get_buffer_arguments(source_desc);
		अगर (ACPI_SUCCESS(status)) अणु

			/* Return an additional reference to the object */

			obj_desc = source_desc;
			acpi_ut_add_reference(obj_desc);
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_STRING:

		अगर (source_desc->common.type != ACPI_TYPE_STRING) अणु
			ACPI_ERROR((AE_INFO, "Object not a String, type %s",
				    acpi_ut_get_object_type_name(source_desc)));
			वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		पूर्ण

		/* Return an additional reference to the object */

		obj_desc = source_desc;
		acpi_ut_add_reference(obj_desc);
		अवरोध;

	हाल ACPI_TYPE_INTEGER:

		अगर (source_desc->common.type != ACPI_TYPE_INTEGER) अणु
			ACPI_ERROR((AE_INFO, "Object not a Integer, type %s",
				    acpi_ut_get_object_type_name(source_desc)));
			वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		पूर्ण

		/* Return an additional reference to the object */

		obj_desc = source_desc;
		acpi_ut_add_reference(obj_desc);
		अवरोध;

	हाल ACPI_TYPE_BUFFER_FIELD:
	हाल ACPI_TYPE_LOCAL_REGION_FIELD:
	हाल ACPI_TYPE_LOCAL_BANK_FIELD:
	हाल ACPI_TYPE_LOCAL_INDEX_FIELD:

		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "FieldRead Node=%p SourceDesc=%p Type=%X\n",
				  node, source_desc, entry_type));

		status =
		    acpi_ex_पढ़ो_data_from_field(walk_state, source_desc,
						 &obj_desc);
		अवरोध;

		/* For these objects, just वापस the object attached to the Node */

	हाल ACPI_TYPE_MUTEX:
	हाल ACPI_TYPE_POWER:
	हाल ACPI_TYPE_PROCESSOR:
	हाल ACPI_TYPE_EVENT:
	हाल ACPI_TYPE_REGION:

		/* Return an additional reference to the object */

		obj_desc = source_desc;
		acpi_ut_add_reference(obj_desc);
		अवरोध;

		/* TYPE_ANY is untyped, and thus there is no object associated with it */

	हाल ACPI_TYPE_ANY:

		ACPI_ERROR((AE_INFO,
			    "Untyped entry %p, no attached object!", node));

		वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);	/* Cannot be AE_TYPE */

	हाल ACPI_TYPE_LOCAL_REFERENCE:

		चयन (source_desc->reference.class) अणु
		हाल ACPI_REFCLASS_TABLE:	/* This is a ddb_handle */
		हाल ACPI_REFCLASS_REFOF:
		हाल ACPI_REFCLASS_INDEX:

			/* Return an additional reference to the object */

			obj_desc = source_desc;
			acpi_ut_add_reference(obj_desc);
			अवरोध;

		शेष:

			/* No named references are allowed here */

			ACPI_ERROR((AE_INFO,
				    "Unsupported Reference type 0x%X",
				    source_desc->reference.class));

			वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		पूर्ण
		अवरोध;

	शेष:

		/* Default हाल is क्रम unknown types */

		ACPI_ERROR((AE_INFO,
			    "Node %p - Unknown object type 0x%X",
			    node, entry_type));

		वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);

	पूर्ण			/* चयन (entry_type) */

	/* Return the object descriptor */

	*object_ptr = (व्योम *)obj_desc;
	वापस_ACPI_STATUS(status);
पूर्ण
