<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: nsobject - Utilities क्रम objects attached to namespace
 *                         table entries
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_NAMESPACE
ACPI_MODULE_NAME("nsobject")

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_attach_object
 *
 * PARAMETERS:  node                - Parent Node
 *              object              - Object to be attached
 *              type                - Type of object, or ACPI_TYPE_ANY अगर not
 *                                    known
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Record the given object as the value associated with the
 *              name whose acpi_handle is passed. If Object is शून्य
 *              and Type is ACPI_TYPE_ANY, set the name as having no value.
 *              Note: Future may require that the Node->Flags field be passed
 *              as a parameter.
 *
 * MUTEX:       Assumes namespace is locked
 *
 ******************************************************************************/
acpi_status
acpi_ns_attach_object(काष्ठा acpi_namespace_node *node,
		      जोड़ acpi_opeअक्रम_object *object, acpi_object_type type)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *last_obj_desc;
	acpi_object_type object_type = ACPI_TYPE_ANY;

	ACPI_FUNCTION_TRACE(ns_attach_object);

	/*
	 * Parameter validation
	 */
	अगर (!node) अणु

		/* Invalid handle */

		ACPI_ERROR((AE_INFO, "Null NamedObj handle"));
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	अगर (!object && (ACPI_TYPE_ANY != type)) अणु

		/* Null object */

		ACPI_ERROR((AE_INFO,
			    "Null object, but type not ACPI_TYPE_ANY"));
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	अगर (ACPI_GET_DESCRIPTOR_TYPE(node) != ACPI_DESC_TYPE_NAMED) अणु

		/* Not a name handle */

		ACPI_ERROR((AE_INFO, "Invalid handle %p [%s]",
			    node, acpi_ut_get_descriptor_name(node)));
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Check अगर this object is alपढ़ोy attached */

	अगर (node->object == object) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Obj %p already installed in NameObj %p\n",
				  object, node));

		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* If null object, we will just install it */

	अगर (!object) अणु
		obj_desc = शून्य;
		object_type = ACPI_TYPE_ANY;
	पूर्ण

	/*
	 * If the source object is a namespace Node with an attached object,
	 * we will use that (attached) object
	 */
	अन्यथा अगर ((ACPI_GET_DESCRIPTOR_TYPE(object) == ACPI_DESC_TYPE_NAMED) &&
		 ((काष्ठा acpi_namespace_node *)object)->object) अणु
		/*
		 * Value passed is a name handle and that name has a
		 * non-null value. Use that name's value and type.
		 */
		obj_desc = ((काष्ठा acpi_namespace_node *)object)->object;
		object_type = ((काष्ठा acpi_namespace_node *)object)->type;
	पूर्ण

	/*
	 * Otherwise, we will use the parameter object, but we must type
	 * it first
	 */
	अन्यथा अणु
		obj_desc = (जोड़ acpi_opeअक्रम_object *)object;

		/* Use the given type */

		object_type = type;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Installing %p into Node %p [%4.4s]\n",
			  obj_desc, node, acpi_ut_get_node_name(node)));

	/* Detach an existing attached object अगर present */

	अगर (node->object) अणु
		acpi_ns_detach_object(node);
	पूर्ण

	अगर (obj_desc) अणु
		/*
		 * Must increment the new value's reference count
		 * (अगर it is an पूर्णांकernal object)
		 */
		acpi_ut_add_reference(obj_desc);

		/*
		 * Handle objects with multiple descriptors - walk
		 * to the end of the descriptor list
		 */
		last_obj_desc = obj_desc;
		जबतक (last_obj_desc->common.next_object) अणु
			last_obj_desc = last_obj_desc->common.next_object;
		पूर्ण

		/* Install the object at the front of the object list */

		last_obj_desc->common.next_object = node->object;
	पूर्ण

	node->type = (u8) object_type;
	node->object = obj_desc;

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_detach_object
 *
 * PARAMETERS:  node           - A Namespace node whose object will be detached
 *
 * RETURN:      None.
 *
 * DESCRIPTION: Detach/delete an object associated with a namespace node.
 *              अगर the object is an allocated object, it is मुक्तd.
 *              Otherwise, the field is simply cleared.
 *
 ******************************************************************************/

व्योम acpi_ns_detach_object(काष्ठा acpi_namespace_node *node)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;

	ACPI_FUNCTION_TRACE(ns_detach_object);

	obj_desc = node->object;

	अगर (!obj_desc || (obj_desc->common.type == ACPI_TYPE_LOCAL_DATA)) अणु
		वापस_VOID;
	पूर्ण

	अगर (node->flags & ANOBJ_ALLOCATED_BUFFER) अणु

		/* Free the dynamic aml buffer */

		अगर (obj_desc->common.type == ACPI_TYPE_METHOD) अणु
			ACPI_FREE(obj_desc->method.aml_start);
		पूर्ण
	पूर्ण

	अगर (obj_desc->common.type == ACPI_TYPE_REGION) अणु
		acpi_ut_हटाओ_address_range(obj_desc->region.space_id, node);
	पूर्ण

	/* Clear the Node entry in all हालs */

	node->object = शून्य;
	अगर (ACPI_GET_DESCRIPTOR_TYPE(obj_desc) == ACPI_DESC_TYPE_OPERAND) अणु

		/* Unlink object from front of possible object list */

		node->object = obj_desc->common.next_object;

		/* Handle possible 2-descriptor object */

		अगर (node->object &&
		    (node->object->common.type != ACPI_TYPE_LOCAL_DATA)) अणु
			node->object = node->object->common.next_object;
		पूर्ण

		/*
		 * Detach the object from any data objects (which are still held by
		 * the namespace node)
		 */
		अगर (obj_desc->common.next_object &&
		    ((obj_desc->common.next_object)->common.type ==
		     ACPI_TYPE_LOCAL_DATA)) अणु
			obj_desc->common.next_object = शून्य;
		पूर्ण
	पूर्ण

	/* Reset the node type to untyped */

	node->type = ACPI_TYPE_ANY;

	ACPI_DEBUG_PRINT((ACPI_DB_NAMES, "Node %p [%4.4s] Object %p\n",
			  node, acpi_ut_get_node_name(node), obj_desc));

	/* Remove one reference on the object (and all subobjects) */

	acpi_ut_हटाओ_reference(obj_desc);
	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_attached_object
 *
 * PARAMETERS:  node             - Namespace node
 *
 * RETURN:      Current value of the object field from the Node whose
 *              handle is passed
 *
 * DESCRIPTION: Obtain the object attached to a namespace node.
 *
 ******************************************************************************/

जोड़ acpi_opeअक्रम_object *acpi_ns_get_attached_object(काष्ठा
						       acpi_namespace_node
						       *node)
अणु
	ACPI_FUNCTION_TRACE_PTR(ns_get_attached_object, node);

	अगर (!node) अणु
		ACPI_WARNING((AE_INFO, "Null Node ptr"));
		वापस_PTR(शून्य);
	पूर्ण

	अगर (!node->object ||
	    ((ACPI_GET_DESCRIPTOR_TYPE(node->object) != ACPI_DESC_TYPE_OPERAND)
	     && (ACPI_GET_DESCRIPTOR_TYPE(node->object) !=
		 ACPI_DESC_TYPE_NAMED))
	    || ((node->object)->common.type == ACPI_TYPE_LOCAL_DATA)) अणु
		वापस_PTR(शून्य);
	पूर्ण

	वापस_PTR(node->object);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_secondary_object
 *
 * PARAMETERS:  node             - Namespace node
 *
 * RETURN:      Current value of the object field from the Node whose
 *              handle is passed.
 *
 * DESCRIPTION: Obtain a secondary object associated with a namespace node.
 *
 ******************************************************************************/

जोड़ acpi_opeअक्रम_object *acpi_ns_get_secondary_object(जोड़
							acpi_opeअक्रम_object
							*obj_desc)
अणु
	ACPI_FUNCTION_TRACE_PTR(ns_get_secondary_object, obj_desc);

	अगर ((!obj_desc) ||
	    (obj_desc->common.type == ACPI_TYPE_LOCAL_DATA) ||
	    (!obj_desc->common.next_object) ||
	    ((obj_desc->common.next_object)->common.type ==
	     ACPI_TYPE_LOCAL_DATA)) अणु
		वापस_PTR(शून्य);
	पूर्ण

	वापस_PTR(obj_desc->common.next_object);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_attach_data
 *
 * PARAMETERS:  node            - Namespace node
 *              handler         - Handler to be associated with the data
 *              data            - Data to be attached
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Low-level attach data. Create and attach a Data object.
 *
 ******************************************************************************/

acpi_status
acpi_ns_attach_data(काष्ठा acpi_namespace_node *node,
		    acpi_object_handler handler, व्योम *data)
अणु
	जोड़ acpi_opeअक्रम_object *prev_obj_desc;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *data_desc;

	/* We only allow one attachment per handler */

	prev_obj_desc = शून्य;
	obj_desc = node->object;
	जबतक (obj_desc) अणु
		अगर ((obj_desc->common.type == ACPI_TYPE_LOCAL_DATA) &&
		    (obj_desc->data.handler == handler)) अणु
			वापस (AE_ALREADY_EXISTS);
		पूर्ण

		prev_obj_desc = obj_desc;
		obj_desc = obj_desc->common.next_object;
	पूर्ण

	/* Create an पूर्णांकernal object क्रम the data */

	data_desc = acpi_ut_create_पूर्णांकernal_object(ACPI_TYPE_LOCAL_DATA);
	अगर (!data_desc) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	data_desc->data.handler = handler;
	data_desc->data.poपूर्णांकer = data;

	/* Install the data object */

	अगर (prev_obj_desc) अणु
		prev_obj_desc->common.next_object = data_desc;
	पूर्ण अन्यथा अणु
		node->object = data_desc;
	पूर्ण

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_detach_data
 *
 * PARAMETERS:  node            - Namespace node
 *              handler         - Handler associated with the data
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Low-level detach data. Delete the data node, but the caller
 *              is responsible क्रम the actual data.
 *
 ******************************************************************************/

acpi_status
acpi_ns_detach_data(काष्ठा acpi_namespace_node *node,
		    acpi_object_handler handler)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *prev_obj_desc;

	prev_obj_desc = शून्य;
	obj_desc = node->object;
	जबतक (obj_desc) अणु
		अगर ((obj_desc->common.type == ACPI_TYPE_LOCAL_DATA) &&
		    (obj_desc->data.handler == handler)) अणु
			अगर (prev_obj_desc) अणु
				prev_obj_desc->common.next_object =
				    obj_desc->common.next_object;
			पूर्ण अन्यथा अणु
				node->object = obj_desc->common.next_object;
			पूर्ण

			acpi_ut_हटाओ_reference(obj_desc);
			वापस (AE_OK);
		पूर्ण

		prev_obj_desc = obj_desc;
		obj_desc = obj_desc->common.next_object;
	पूर्ण

	वापस (AE_NOT_FOUND);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ns_get_attached_data
 *
 * PARAMETERS:  node            - Namespace node
 *              handler         - Handler associated with the data
 *              data            - Where the data is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Low level पूर्णांकerface to obtain data previously associated with
 *              a namespace node.
 *
 ******************************************************************************/

acpi_status
acpi_ns_get_attached_data(काष्ठा acpi_namespace_node *node,
			  acpi_object_handler handler, व्योम **data)
अणु
	जोड़ acpi_opeअक्रम_object *obj_desc;

	obj_desc = node->object;
	जबतक (obj_desc) अणु
		अगर ((obj_desc->common.type == ACPI_TYPE_LOCAL_DATA) &&
		    (obj_desc->data.handler == handler)) अणु
			*data = obj_desc->data.poपूर्णांकer;
			वापस (AE_OK);
		पूर्ण

		obj_desc = obj_desc->common.next_object;
	पूर्ण

	वापस (AE_NOT_FOUND);
पूर्ण
