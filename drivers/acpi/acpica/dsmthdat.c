<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: dsmthdat - control method arguments and local variables
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acdispat.h"
#समावेश "acnamesp.h"
#समावेश "acinterp.h"

#घोषणा _COMPONENT          ACPI_DISPATCHER
ACPI_MODULE_NAME("dsmthdat")

/* Local prototypes */
अटल व्योम
acpi_ds_method_data_delete_value(u8 type,
				 u32 index, काष्ठा acpi_walk_state *walk_state);

अटल acpi_status
acpi_ds_method_data_set_value(u8 type,
			      u32 index,
			      जोड़ acpi_opeअक्रम_object *object,
			      काष्ठा acpi_walk_state *walk_state);

#अगर_घोषित ACPI_OBSOLETE_FUNCTIONS
acpi_object_type
acpi_ds_method_data_get_type(u16 opcode,
			     u32 index, काष्ठा acpi_walk_state *walk_state);
#पूर्ण_अगर

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_init
 *
 * PARAMETERS:  walk_state          - Current walk state object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize the data काष्ठाures that hold the method's arguments
 *              and locals. The data काष्ठा is an array of namespace nodes क्रम
 *              each - this allows ref_of and de_ref_of to work properly क्रम these
 *              special data types.
 *
 * NOTES:       walk_state fields are initialized to zero by the
 *              ACPI_ALLOCATE_ZEROED().
 *
 *              A pseuकरो-Namespace Node is asचिन्हित to each argument and local
 *              so that ref_of() can वापस a poपूर्णांकer to the Node.
 *
 ******************************************************************************/

व्योम acpi_ds_method_data_init(काष्ठा acpi_walk_state *walk_state)
अणु
	u32 i;

	ACPI_FUNCTION_TRACE(ds_method_data_init);

	/* Init the method arguments */

	क्रम (i = 0; i < ACPI_METHOD_NUM_ARGS; i++) अणु
		ACPI_MOVE_32_TO_32(&walk_state->arguments[i].name,
				   NAMखातापूर्ण_ARG_NTE);

		walk_state->arguments[i].name.पूर्णांकeger |= (i << 24);
		walk_state->arguments[i].descriptor_type = ACPI_DESC_TYPE_NAMED;
		walk_state->arguments[i].type = ACPI_TYPE_ANY;
		walk_state->arguments[i].flags = ANOBJ_METHOD_ARG;
	पूर्ण

	/* Init the method locals */

	क्रम (i = 0; i < ACPI_METHOD_NUM_LOCALS; i++) अणु
		ACPI_MOVE_32_TO_32(&walk_state->local_variables[i].name,
				   NAMखातापूर्ण_LOCAL_NTE);

		walk_state->local_variables[i].name.पूर्णांकeger |= (i << 24);
		walk_state->local_variables[i].descriptor_type =
		    ACPI_DESC_TYPE_NAMED;
		walk_state->local_variables[i].type = ACPI_TYPE_ANY;
		walk_state->local_variables[i].flags = ANOBJ_METHOD_LOCAL;
	पूर्ण

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_delete_all
 *
 * PARAMETERS:  walk_state          - Current walk state object
 *
 * RETURN:      None
 *
 * DESCRIPTION: Delete method locals and arguments. Arguments are only
 *              deleted अगर this method was called from another method.
 *
 ******************************************************************************/

व्योम acpi_ds_method_data_delete_all(काष्ठा acpi_walk_state *walk_state)
अणु
	u32 index;

	ACPI_FUNCTION_TRACE(ds_method_data_delete_all);

	/* Detach the locals */

	क्रम (index = 0; index < ACPI_METHOD_NUM_LOCALS; index++) अणु
		अगर (walk_state->local_variables[index].object) अणु
			ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Deleting Local%u=%p\n",
					  index,
					  walk_state->local_variables[index].
					  object));

			/* Detach object (अगर present) and हटाओ a reference */

			acpi_ns_detach_object(&walk_state->
					      local_variables[index]);
		पूर्ण
	पूर्ण

	/* Detach the arguments */

	क्रम (index = 0; index < ACPI_METHOD_NUM_ARGS; index++) अणु
		अगर (walk_state->arguments[index].object) अणु
			ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Deleting Arg%u=%p\n",
					  index,
					  walk_state->arguments[index].object));

			/* Detach object (अगर present) and हटाओ a reference */

			acpi_ns_detach_object(&walk_state->arguments[index]);
		पूर्ण
	पूर्ण

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_init_args
 *
 * PARAMETERS:  *params         - Poपूर्णांकer to a parameter list क्रम the method
 *              max_param_count - The arg count क्रम this method
 *              walk_state      - Current walk state object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize arguments क्रम a method. The parameter list is a list
 *              of ACPI opeअक्रम objects, either null terminated or whose length
 *              is defined by max_param_count.
 *
 ******************************************************************************/

acpi_status
acpi_ds_method_data_init_args(जोड़ acpi_opeअक्रम_object **params,
			      u32 max_param_count,
			      काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;
	u32 index = 0;

	ACPI_FUNCTION_TRACE_PTR(ds_method_data_init_args, params);

	अगर (!params) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "No parameter list passed to method\n"));
		वापस_ACPI_STATUS(AE_OK);
	पूर्ण

	/* Copy passed parameters पूर्णांकo the new method stack frame */

	जबतक ((index < ACPI_METHOD_NUM_ARGS) &&
	       (index < max_param_count) && params[index]) अणु
		/*
		 * A valid parameter.
		 * Store the argument in the method/walk descriptor.
		 * Do not copy the arg in order to implement call by reference
		 */
		status =
		    acpi_ds_method_data_set_value(ACPI_REFCLASS_ARG, index,
						  params[index], walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		index++;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "%u args passed to method\n", index));
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_get_node
 *
 * PARAMETERS:  type                - Either ACPI_REFCLASS_LOCAL or
 *                                    ACPI_REFCLASS_ARG
 *              index               - Which Local or Arg whose type to get
 *              walk_state          - Current walk state object
 *              node                - Where the node is वापसed.
 *
 * RETURN:      Status and node
 *
 * DESCRIPTION: Get the Node associated with a local or arg.
 *
 ******************************************************************************/

acpi_status
acpi_ds_method_data_get_node(u8 type,
			     u32 index,
			     काष्ठा acpi_walk_state *walk_state,
			     काष्ठा acpi_namespace_node **node)
अणु
	ACPI_FUNCTION_TRACE(ds_method_data_get_node);

	/*
	 * Method Locals and Arguments are supported
	 */
	चयन (type) अणु
	हाल ACPI_REFCLASS_LOCAL:

		अगर (index > ACPI_METHOD_MAX_LOCAL) अणु
			ACPI_ERROR((AE_INFO,
				    "Local index %u is invalid (max %u)",
				    index, ACPI_METHOD_MAX_LOCAL));
			वापस_ACPI_STATUS(AE_AML_INVALID_INDEX);
		पूर्ण

		/* Return a poपूर्णांकer to the pseuकरो-node */

		*node = &walk_state->local_variables[index];
		अवरोध;

	हाल ACPI_REFCLASS_ARG:

		अगर (index > ACPI_METHOD_MAX_ARG) अणु
			ACPI_ERROR((AE_INFO,
				    "Arg index %u is invalid (max %u)",
				    index, ACPI_METHOD_MAX_ARG));
			वापस_ACPI_STATUS(AE_AML_INVALID_INDEX);
		पूर्ण

		/* Return a poपूर्णांकer to the pseuकरो-node */

		*node = &walk_state->arguments[index];
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Type %u is invalid", type));
		वापस_ACPI_STATUS(AE_TYPE);
	पूर्ण

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_set_value
 *
 * PARAMETERS:  type                - Either ACPI_REFCLASS_LOCAL or
 *                                    ACPI_REFCLASS_ARG
 *              index               - Which Local or Arg to get
 *              object              - Object to be inserted पूर्णांकo the stack entry
 *              walk_state          - Current walk state object
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Insert an object onto the method stack at entry Opcode:Index.
 *              Note: There is no "implicit conversion" क्रम locals.
 *
 ******************************************************************************/

अटल acpi_status
acpi_ds_method_data_set_value(u8 type,
			      u32 index,
			      जोड़ acpi_opeअक्रम_object *object,
			      काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node;

	ACPI_FUNCTION_TRACE(ds_method_data_set_value);

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "NewObj %p Type %2.2X, Refs=%u [%s]\n", object,
			  type, object->common.reference_count,
			  acpi_ut_get_type_name(object->common.type)));

	/* Get the namespace node क्रम the arg/local */

	status = acpi_ds_method_data_get_node(type, index, walk_state, &node);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * Increment ref count so object can't be deleted जबतक installed.
	 * NOTE: We करो not copy the object in order to preserve the call by
	 * reference semantics of ACPI Control Method invocation.
	 * (See ACPI Specअगरication 2.0C)
	 */
	acpi_ut_add_reference(object);

	/* Install the object */

	node->object = object;
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_get_value
 *
 * PARAMETERS:  type                - Either ACPI_REFCLASS_LOCAL or
 *                                    ACPI_REFCLASS_ARG
 *              index               - Which localVar or argument to get
 *              walk_state          - Current walk state object
 *              dest_desc           - Where Arg or Local value is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Retrieve value of selected Arg or Local क्रम this method
 *              Used only in acpi_ex_resolve_to_value().
 *
 ******************************************************************************/

acpi_status
acpi_ds_method_data_get_value(u8 type,
			      u32 index,
			      काष्ठा acpi_walk_state *walk_state,
			      जोड़ acpi_opeअक्रम_object **dest_desc)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_opeअक्रम_object *object;

	ACPI_FUNCTION_TRACE(ds_method_data_get_value);

	/* Validate the object descriptor */

	अगर (!dest_desc) अणु
		ACPI_ERROR((AE_INFO, "Null object descriptor pointer"));
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Get the namespace node क्रम the arg/local */

	status = acpi_ds_method_data_get_node(type, index, walk_state, &node);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Get the object from the node */

	object = node->object;

	/* Examine the वापसed object, it must be valid. */

	अगर (!object) अणु
		/*
		 * Index poपूर्णांकs to uninitialized object.
		 * This means that either 1) The expected argument was
		 * not passed to the method, or 2) A local variable
		 * was referenced by the method (via the ASL)
		 * beक्रमe it was initialized. Either हाल is an error.
		 */

		/* If slack enabled, init the local_x/arg_x to an Integer of value zero */

		अगर (acpi_gbl_enable_पूर्णांकerpreter_slack) अणु
			object = acpi_ut_create_पूर्णांकeger_object((u64) 0);
			अगर (!object) अणु
				वापस_ACPI_STATUS(AE_NO_MEMORY);
			पूर्ण

			node->object = object;
		पूर्ण

		/* Otherwise, वापस the error */

		अन्यथा
			चयन (type) अणु
			हाल ACPI_REFCLASS_ARG:

				ACPI_ERROR((AE_INFO,
					    "Uninitialized Arg[%u] at node %p",
					    index, node));

				वापस_ACPI_STATUS(AE_AML_UNINITIALIZED_ARG);

			हाल ACPI_REFCLASS_LOCAL:
				/*
				 * No error message क्रम this हाल, will be trapped again later to
				 * detect and ignore हालs of Store(local_x,local_x)
				 */
				वापस_ACPI_STATUS(AE_AML_UNINITIALIZED_LOCAL);

			शेष:

				ACPI_ERROR((AE_INFO,
					    "Not a Arg/Local opcode: 0x%X",
					    type));
				वापस_ACPI_STATUS(AE_AML_INTERNAL);
			पूर्ण
	पूर्ण

	/*
	 * The Index poपूर्णांकs to an initialized and valid object.
	 * Return an additional reference to the object
	 */
	*dest_desc = object;
	acpi_ut_add_reference(object);

	वापस_ACPI_STATUS(AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_delete_value
 *
 * PARAMETERS:  type                - Either ACPI_REFCLASS_LOCAL or
 *                                    ACPI_REFCLASS_ARG
 *              index               - Which localVar or argument to delete
 *              walk_state          - Current walk state object
 *
 * RETURN:      None
 *
 * DESCRIPTION: Delete the entry at Opcode:Index. Inserts
 *              a null पूर्णांकo the stack slot after the object is deleted.
 *
 ******************************************************************************/

अटल व्योम
acpi_ds_method_data_delete_value(u8 type,
				 u32 index, काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_opeअक्रम_object *object;

	ACPI_FUNCTION_TRACE(ds_method_data_delete_value);

	/* Get the namespace node क्रम the arg/local */

	status = acpi_ds_method_data_get_node(type, index, walk_state, &node);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_VOID;
	पूर्ण

	/* Get the associated object */

	object = acpi_ns_get_attached_object(node);

	/*
	 * Undefine the Arg or Local by setting its descriptor
	 * poपूर्णांकer to शून्य. Locals/Args can contain both
	 * ACPI_OPERAND_OBJECTS and ACPI_NAMESPACE_NODEs
	 */
	node->object = शून्य;

	अगर ((object) &&
	    (ACPI_GET_DESCRIPTOR_TYPE(object) == ACPI_DESC_TYPE_OPERAND)) अणु
		/*
		 * There is a valid object.
		 * Decrement the reference count by one to balance the
		 * increment when the object was stored.
		 */
		acpi_ut_हटाओ_reference(object);
	पूर्ण

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_store_object_to_local
 *
 * PARAMETERS:  type                - Either ACPI_REFCLASS_LOCAL or
 *                                    ACPI_REFCLASS_ARG
 *              index               - Which Local or Arg to set
 *              obj_desc            - Value to be stored
 *              walk_state          - Current walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Store a value in an Arg or Local. The obj_desc is installed
 *              as the new value क्रम the Arg or Local and the reference count
 *              क्रम obj_desc is incremented.
 *
 ******************************************************************************/

acpi_status
acpi_ds_store_object_to_local(u8 type,
			      u32 index,
			      जोड़ acpi_opeअक्रम_object *obj_desc,
			      काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_opeअक्रम_object *current_obj_desc;
	जोड़ acpi_opeअक्रम_object *new_obj_desc;

	ACPI_FUNCTION_TRACE(ds_store_object_to_local);
	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Type=%2.2X Index=%u Obj=%p\n",
			  type, index, obj_desc));

	/* Parameter validation */

	अगर (!obj_desc) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Get the namespace node क्रम the arg/local */

	status = acpi_ds_method_data_get_node(type, index, walk_state, &node);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	current_obj_desc = acpi_ns_get_attached_object(node);
	अगर (current_obj_desc == obj_desc) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Obj=%p already installed!\n",
				  obj_desc));
		वापस_ACPI_STATUS(status);
	पूर्ण

	/*
	 * If the reference count on the object is more than one, we must
	 * take a copy of the object beक्रमe we store. A reference count
	 * of exactly 1 means that the object was just created during the
	 * evaluation of an expression, and we can safely use it since it
	 * is not used anywhere अन्यथा.
	 */
	new_obj_desc = obj_desc;
	अगर (obj_desc->common.reference_count > 1) अणु
		status =
		    acpi_ut_copy_iobject_to_iobject(obj_desc, &new_obj_desc,
						    walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण

	/*
	 * If there is an object alपढ़ोy in this slot, we either
	 * have to delete it, or अगर this is an argument and there
	 * is an object reference stored there, we have to करो
	 * an indirect store!
	 */
	अगर (current_obj_desc) अणु
		/*
		 * Check क्रम an indirect store अगर an argument
		 * contains an object reference (stored as an Node).
		 * We करोn't allow this स्वतःmatic dereferencing क्रम
		 * locals, since a store to a local should overग_लिखो
		 * anything there, including an object reference.
		 *
		 * If both Arg0 and Local0 contain ref_of (Local4):
		 *
		 * Store (1, Arg0)             - Causes indirect store to local4
		 * Store (1, Local0)           - Stores 1 in local0, overwriting
		 *                                  the reference to local4
		 * Store (1, de_refof (Local0)) - Causes indirect store to local4
		 *
		 * Weird, but true.
		 */
		अगर (type == ACPI_REFCLASS_ARG) अणु
			/*
			 * If we have a valid reference object that came from ref_of(),
			 * करो the indirect store
			 */
			अगर ((ACPI_GET_DESCRIPTOR_TYPE(current_obj_desc) ==
			     ACPI_DESC_TYPE_OPERAND) &&
			    (current_obj_desc->common.type ==
			     ACPI_TYPE_LOCAL_REFERENCE) &&
			    (current_obj_desc->reference.class ==
			     ACPI_REFCLASS_REFOF)) अणु
				ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
						  "Arg (%p) is an ObjRef(Node), storing in node %p\n",
						  new_obj_desc,
						  current_obj_desc));

				/*
				 * Store this object to the Node (perक्रमm the indirect store)
				 * NOTE: No implicit conversion is perक्रमmed, as per the ACPI
				 * specअगरication rules on storing to Locals/Args.
				 */
				status =
				    acpi_ex_store_object_to_node(new_obj_desc,
								 current_obj_desc->
								 reference.
								 object,
								 walk_state,
								 ACPI_NO_IMPLICIT_CONVERSION);

				/* Remove local reference अगर we copied the object above */

				अगर (new_obj_desc != obj_desc) अणु
					acpi_ut_हटाओ_reference(new_obj_desc);
				पूर्ण

				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण

		/* Delete the existing object beक्रमe storing the new one */

		acpi_ds_method_data_delete_value(type, index, walk_state);
	पूर्ण

	/*
	 * Install the Obj descriptor (*new_obj_desc) पूर्णांकo
	 * the descriptor क्रम the Arg or Local.
	 * (increments the object reference count by one)
	 */
	status =
	    acpi_ds_method_data_set_value(type, index, new_obj_desc,
					  walk_state);

	/* Remove local reference अगर we copied the object above */

	अगर (new_obj_desc != obj_desc) अणु
		acpi_ut_हटाओ_reference(new_obj_desc);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

#अगर_घोषित ACPI_OBSOLETE_FUNCTIONS
/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_method_data_get_type
 *
 * PARAMETERS:  opcode              - Either AML_FIRST LOCAL_OP or
 *                                    AML_FIRST_ARG_OP
 *              index               - Which Local or Arg whose type to get
 *              walk_state          - Current walk state object
 *
 * RETURN:      Data type of current value of the selected Arg or Local
 *
 * DESCRIPTION: Get the type of the object stored in the Local or Arg
 *
 ******************************************************************************/

acpi_object_type
acpi_ds_method_data_get_type(u16 opcode,
			     u32 index, काष्ठा acpi_walk_state *walk_state)
अणु
	acpi_status status;
	काष्ठा acpi_namespace_node *node;
	जोड़ acpi_opeअक्रम_object *object;

	ACPI_FUNCTION_TRACE(ds_method_data_get_type);

	/* Get the namespace node क्रम the arg/local */

	status = acpi_ds_method_data_get_node(opcode, index, walk_state, &node);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_VALUE((ACPI_TYPE_NOT_FOUND));
	पूर्ण

	/* Get the object */

	object = acpi_ns_get_attached_object(node);
	अगर (!object) अणु

		/* Uninitialized local/arg, वापस TYPE_ANY */

		वापस_VALUE(ACPI_TYPE_ANY);
	पूर्ण

	/* Get the object type */

	वापस_VALUE(object->type);
पूर्ण
#पूर्ण_अगर
