<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exstore - AML Interpreter object store support
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdispat.h"
#समावेश "acinterp.h"
#समावेश "amlcode.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exstore")

/* Local prototypes */
अटल acpi_status
acpi_ex_store_object_to_index(जोड़ acpi_opeअक्रम_object *val_desc,
			      जोड़ acpi_opeअक्रम_object *dest_desc,
			      काष्ठा acpi_walk_state *walk_state);

अटल acpi_status
acpi_ex_store_direct_to_node(जोड़ acpi_opeअक्रम_object *source_desc,
			     काष्ठा acpi_namespace_node *node,
			     काष्ठा acpi_walk_state *walk_state);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_store
 *
 * PARAMETERS:  *source_desc        - Value to be stored
 *              *dest_desc          - Where to store it. Must be an NS node
 *                                    or जोड़ acpi_opeअक्रम_object of type
 *                                    Reference;
 *              walk_state          - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Store the value described by source_desc पूर्णांकo the location
 *              described by dest_desc. Called by various पूर्णांकerpreter
 *              functions to store the result of an operation पूर्णांकo
 *              the destination opeअक्रम -- not just simply the actual "Store"
 *              ASL चालक.
 *
 ******************************************************************************/

acpi_status
acpi_ex_store(जोड़ acpi_opeअक्रम_object *source_desc,
	      जोड़ acpi_opeअक्रम_object *dest_desc,
	      काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_opeअक्रम_object *ref_desc = dest_desc;

	ACPI_FUNCTION_TRACE_PTR(ex_store, dest_desc);

	/* Validate parameters */

	अगर (!source_desc || !dest_desc) अणु
		ACPI_ERROR((AE_INFO, "Null parameter"));
		वापस_ACPI_STATUS(AE_AML_NO_OPERAND);
	पूर्ण

	/* dest_desc can be either a namespace node or an ACPI object */

	अगर (ACPI_GET_DESCRIPTOR_TYPE(dest_desc) == ACPI_DESC_TYPE_NAMED) अणु
		/*
		 * Dest is a namespace node,
		 * Storing an object पूर्णांकo a Named node.
		 */
		status = acpi_ex_store_object_to_node(source_desc,
						      (काष्ठा
						       acpi_namespace_node *)
						      dest_desc, walk_state,
						      ACPI_IMPLICIT_CONVERSION);

		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Destination object must be a Reference or a Constant object */

	चयन (dest_desc->common.type) अणु
	हाल ACPI_TYPE_LOCAL_REFERENCE:

		अवरोध;

	हाल ACPI_TYPE_INTEGER:

		/* Allow stores to Constants -- a Noop as per ACPI spec */

		अगर (dest_desc->common.flags & AOPOBJ_AML_CONSTANT) अणु
			वापस_ACPI_STATUS(AE_OK);
		पूर्ण

		ACPI_FALLTHROUGH;

	शेष:

		/* Destination is not a Reference object */

		ACPI_ERROR((AE_INFO,
			    "Target is not a Reference or Constant object - [%s] %p",
			    acpi_ut_get_object_type_name(dest_desc),
			    dest_desc));

		वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
	पूर्ण

	/*
	 * Examine the Reference class. These हालs are handled:
	 *
	 * 1) Store to Name (Change the object associated with a name)
	 * 2) Store to an indexed area of a Buffer or Package
	 * 3) Store to a Method Local or Arg
	 * 4) Store to the debug object
	 */
	चयन (ref_desc->reference.class) अणु
	हाल ACPI_REFCLASS_REFOF:

		/* Storing an object पूर्णांकo a Name "container" */

		status = acpi_ex_store_object_to_node(source_desc,
						      ref_desc->reference.
						      object, walk_state,
						      ACPI_IMPLICIT_CONVERSION);
		अवरोध;

	हाल ACPI_REFCLASS_INDEX:

		/* Storing to an Index (poपूर्णांकer पूर्णांकo a packager or buffer) */

		status =
		    acpi_ex_store_object_to_index(source_desc, ref_desc,
						  walk_state);
		अवरोध;

	हाल ACPI_REFCLASS_LOCAL:
	हाल ACPI_REFCLASS_ARG:

		/* Store to a method local/arg  */

		status =
		    acpi_ds_store_object_to_local(ref_desc->reference.class,
						  ref_desc->reference.value,
						  source_desc, walk_state);
		अवरोध;

	हाल ACPI_REFCLASS_DEBUG:
		/*
		 * Storing to the Debug object causes the value stored to be
		 * displayed and otherwise has no effect -- see ACPI Specअगरication
		 */
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "**** Write to Debug Object: Object %p [%s] ****:\n\n",
				  source_desc,
				  acpi_ut_get_object_type_name(source_desc)));

		ACPI_DEBUG_OBJECT(source_desc, 0, 0);
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Unknown Reference Class 0x%2.2X",
			    ref_desc->reference.class));
		ACPI_DUMP_ENTRY(ref_desc, ACPI_LV_INFO);

		status = AE_AML_INTERNAL;
		अवरोध;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_store_object_to_index
 *
 * PARAMETERS:  *source_desc            - Value to be stored
 *              *dest_desc              - Named object to receive the value
 *              walk_state              - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Store the object to indexed Buffer or Package element
 *
 ******************************************************************************/

अटल acpi_status
acpi_ex_store_object_to_index(जोड़ acpi_opeअक्रम_object *source_desc,
			      जोड़ acpi_opeअक्रम_object *index_desc,
			      काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_opeअक्रम_object *obj_desc;
	जोड़ acpi_opeअक्रम_object *new_desc;
	u8 value = 0;
	u32 i;

	ACPI_FUNCTION_TRACE(ex_store_object_to_index);

	/*
	 * Destination must be a reference poपूर्णांकer, and
	 * must poपूर्णांक to either a buffer or a package
	 */
	चयन (index_desc->reference.target_type) अणु
	हाल ACPI_TYPE_PACKAGE:
		/*
		 * Storing to a package element. Copy the object and replace
		 * any existing object with the new object. No implicit
		 * conversion is perक्रमmed.
		 *
		 * The object at *(index_desc->Reference.Where) is the
		 * element within the package that is to be modअगरied.
		 * The parent package object is at index_desc->Reference.Object
		 */
		obj_desc = *(index_desc->reference.where);

		अगर (source_desc->common.type == ACPI_TYPE_LOCAL_REFERENCE &&
		    source_desc->reference.class == ACPI_REFCLASS_TABLE) अणु

			/* This is a DDBHandle, just add a reference to it */

			acpi_ut_add_reference(source_desc);
			new_desc = source_desc;
		पूर्ण अन्यथा अणु
			/* Normal object, copy it */

			status =
			    acpi_ut_copy_iobject_to_iobject(source_desc,
							    &new_desc,
							    walk_state);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण

		अगर (obj_desc) अणु

			/* Decrement reference count by the ref count of the parent package */

			क्रम (i = 0; i < ((जोड़ acpi_opeअक्रम_object *)
					 index_desc->reference.object)->common.
			     reference_count; i++) अणु
				acpi_ut_हटाओ_reference(obj_desc);
			पूर्ण
		पूर्ण

		*(index_desc->reference.where) = new_desc;

		/* Increment ref count by the ref count of the parent package-1 */

		क्रम (i = 1; i < ((जोड़ acpi_opeअक्रम_object *)
				 index_desc->reference.object)->common.
		     reference_count; i++) अणु
			acpi_ut_add_reference(new_desc);
		पूर्ण

		अवरोध;

	हाल ACPI_TYPE_BUFFER_FIELD:
		/*
		 * Store पूर्णांकo a Buffer or String (not actually a real buffer_field)
		 * at a location defined by an Index.
		 *
		 * The first 8-bit element of the source object is written to the
		 * 8-bit Buffer location defined by the Index destination object,
		 * according to the ACPI 2.0 specअगरication.
		 */

		/*
		 * Make sure the target is a Buffer or String. An error should
		 * not happen here, since the reference_object was स्थिरructed
		 * by the INDEX_OP code.
		 */
		obj_desc = index_desc->reference.object;
		अगर ((obj_desc->common.type != ACPI_TYPE_BUFFER) &&
		    (obj_desc->common.type != ACPI_TYPE_STRING)) अणु
			वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		पूर्ण

		/*
		 * The assignment of the inभागidual elements will be slightly
		 * dअगरferent क्रम each source type.
		 */
		चयन (source_desc->common.type) अणु
		हाल ACPI_TYPE_INTEGER:

			/* Use the least-signअगरicant byte of the पूर्णांकeger */

			value = (u8) (source_desc->पूर्णांकeger.value);
			अवरोध;

		हाल ACPI_TYPE_BUFFER:
		हाल ACPI_TYPE_STRING:

			/* Note: Takes advantage of common string/buffer fields */

			value = source_desc->buffer.poपूर्णांकer[0];
			अवरोध;

		शेष:

			/* All other types are invalid */

			ACPI_ERROR((AE_INFO,
				    "Source must be type [Integer/Buffer/String], found [%s]",
				    acpi_ut_get_object_type_name(source_desc)));
			वापस_ACPI_STATUS(AE_AML_OPERAND_TYPE);
		पूर्ण

		/* Store the source value पूर्णांकo the target buffer byte */

		obj_desc->buffer.poपूर्णांकer[index_desc->reference.value] = value;
		अवरोध;

	शेष:
		ACPI_ERROR((AE_INFO,
			    "Target is not of type [Package/BufferField]"));
		status = AE_AML_TARGET_TYPE;
		अवरोध;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_store_object_to_node
 *
 * PARAMETERS:  source_desc             - Value to be stored
 *              node                    - Named object to receive the value
 *              walk_state              - Current walk state
 *              implicit_conversion     - Perक्रमm implicit conversion (yes/no)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Store the object to the named object.
 *
 * The assignment of an object to a named object is handled here.
 * The value passed in will replace the current value (अगर any)
 * with the input value.
 *
 * When storing पूर्णांकo an object the data is converted to the
 * target object type then stored in the object. This means
 * that the target object type (क्रम an initialized target) will
 * not be changed by a store operation. A copy_object can change
 * the target type, however.
 *
 * The implicit_conversion flag is set to NO/FALSE only when
 * storing to an arg_x -- as per the rules of the ACPI spec.
 *
 * Assumes parameters are alपढ़ोy validated.
 *
 ******************************************************************************/

acpi_status
acpi_ex_store_object_to_node(जोड़ acpi_opeअक्रम_object *source_desc,
			     काष्ठा acpi_namespace_node *node,
			     काष्ठा acpi_walk_state *walk_state,
			     u8 implicit_conversion)
अणु
	acpi_status status = AE_OK;
	जोड़ acpi_opeअक्रम_object *target_desc;
	जोड़ acpi_opeअक्रम_object *new_desc;
	acpi_object_type target_type;

	ACPI_FUNCTION_TRACE_PTR(ex_store_object_to_node, source_desc);

	/* Get current type of the node, and object attached to Node */

	target_type = acpi_ns_get_type(node);
	target_desc = acpi_ns_get_attached_object(node);

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Storing %p [%s] to node %p [%s]\n",
			  source_desc,
			  acpi_ut_get_object_type_name(source_desc), node,
			  acpi_ut_get_type_name(target_type)));

	/* Only limited target types possible क्रम everything except copy_object */

	अगर (walk_state->opcode != AML_COPY_OBJECT_OP) अणु
		/*
		 * Only copy_object allows all object types to be overwritten. For
		 * target_ref(s), there are restrictions on the object types that
		 * are allowed.
		 *
		 * Allowable operations/typing क्रम Store:
		 *
		 * 1) Simple Store
		 *      Integer     --> Integer (Named/Local/Arg)
		 *      String      --> String  (Named/Local/Arg)
		 *      Buffer      --> Buffer  (Named/Local/Arg)
		 *      Package     --> Package (Named/Local/Arg)
		 *
		 * 2) Store with implicit conversion
		 *      Integer     --> String or Buffer  (Named)
		 *      String      --> Integer or Buffer (Named)
		 *      Buffer      --> Integer or String (Named)
		 */
		चयन (target_type) अणु
		हाल ACPI_TYPE_PACKAGE:
			/*
			 * Here, can only store a package to an existing package.
			 * Storing a package to a Local/Arg is OK, and handled
			 * अन्यथाwhere.
			 */
			अगर (walk_state->opcode == AML_STORE_OP) अणु
				अगर (source_desc->common.type !=
				    ACPI_TYPE_PACKAGE) अणु
					ACPI_ERROR((AE_INFO,
						    "Cannot assign type [%s] to [Package] "
						    "(source must be type Pkg)",
						    acpi_ut_get_object_type_name
						    (source_desc)));

					वापस_ACPI_STATUS(AE_AML_TARGET_TYPE);
				पूर्ण
				अवरोध;
			पूर्ण

			ACPI_FALLTHROUGH;

		हाल ACPI_TYPE_DEVICE:
		हाल ACPI_TYPE_EVENT:
		हाल ACPI_TYPE_MUTEX:
		हाल ACPI_TYPE_REGION:
		हाल ACPI_TYPE_POWER:
		हाल ACPI_TYPE_PROCESSOR:
		हाल ACPI_TYPE_THERMAL:

			ACPI_ERROR((AE_INFO,
				    "Target must be [Buffer/Integer/String/Reference]"
				    ", found [%s] (%4.4s)",
				    acpi_ut_get_type_name(node->type),
				    node->name.ascii));

			वापस_ACPI_STATUS(AE_AML_TARGET_TYPE);

		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Resolve the source object to an actual value
	 * (If it is a reference object)
	 */
	status = acpi_ex_resolve_object(&source_desc, target_type, walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Do the actual store operation */

	चयन (target_type) अणु
		/*
		 * The simple data types all support implicit source opeअक्रम
		 * conversion beक्रमe the store.
		 */
	हाल ACPI_TYPE_INTEGER:
	हाल ACPI_TYPE_STRING:
	हाल ACPI_TYPE_BUFFER:

		अगर ((walk_state->opcode == AML_COPY_OBJECT_OP) ||
		    !implicit_conversion) अणु
			/*
			 * However, copy_object and Stores to arg_x करो not perक्रमm
			 * an implicit conversion, as per the ACPI specअगरication.
			 * A direct store is perक्रमmed instead.
			 */
			status =
			    acpi_ex_store_direct_to_node(source_desc, node,
							 walk_state);
			अवरोध;
		पूर्ण

		/* Store with implicit source opeअक्रम conversion support */

		status =
		    acpi_ex_store_object_to_object(source_desc, target_desc,
						   &new_desc, walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		अगर (new_desc != target_desc) अणु
			/*
			 * Store the new new_desc as the new value of the Name, and set
			 * the Name's type to that of the value being stored in it.
			 * source_desc reference count is incremented by attach_object.
			 *
			 * Note: This may change the type of the node अगर an explicit
			 * store has been perक्रमmed such that the node/object type
			 * has been changed.
			 */
			status =
			    acpi_ns_attach_object(node, new_desc,
						  new_desc->common.type);

			ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
					  "Store type [%s] into [%s] via Convert/Attach\n",
					  acpi_ut_get_object_type_name
					  (source_desc),
					  acpi_ut_get_object_type_name
					  (new_desc)));
		पूर्ण
		अवरोध;

	हाल ACPI_TYPE_BUFFER_FIELD:
	हाल ACPI_TYPE_LOCAL_REGION_FIELD:
	हाल ACPI_TYPE_LOCAL_BANK_FIELD:
	हाल ACPI_TYPE_LOCAL_INDEX_FIELD:
		/*
		 * For all fields, always ग_लिखो the source data to the target
		 * field. Any required implicit source opeअक्रम conversion is
		 * perक्रमmed in the function below as necessary. Note, field
		 * objects must retain their original type permanently.
		 */
		status = acpi_ex_ग_लिखो_data_to_field(source_desc, target_desc,
						     &walk_state->result_obj);
		अवरोध;

	शेष:
		/*
		 * copy_object चालक: No conversions क्रम all other types.
		 * Instead, directly store a copy of the source object.
		 *
		 * This is the ACPI spec-defined behavior क्रम the copy_object
		 * चालक. (Note, क्रम this शेष हाल, all normal
		 * Store/Target operations निकासed above with an error).
		 */
		status =
		    acpi_ex_store_direct_to_node(source_desc, node, walk_state);
		अवरोध;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_store_direct_to_node
 *
 * PARAMETERS:  source_desc             - Value to be stored
 *              node                    - Named object to receive the value
 *              walk_state              - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: "Store" an object directly to a node. This involves a copy
 *              and an attach.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ex_store_direct_to_node(जोड़ acpi_opeअक्रम_object *source_desc,
			     काष्ठा acpi_namespace_node *node,
			     काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;
	जोड़ acpi_opeअक्रम_object *new_desc;

	ACPI_FUNCTION_TRACE(ex_store_direct_to_node);

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Storing [%s] (%p) directly into node [%s] (%p)"
			  " with no implicit conversion\n",
			  acpi_ut_get_object_type_name(source_desc),
			  source_desc, acpi_ut_get_type_name(node->type),
			  node));

	/* Copy the source object to a new object */

	status =
	    acpi_ut_copy_iobject_to_iobject(source_desc, &new_desc, walk_state);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Attach the new object to the node */

	status = acpi_ns_attach_object(node, new_desc, new_desc->common.type);
	acpi_ut_हटाओ_reference(new_desc);
	वापस_ACPI_STATUS(status);
पूर्ण
