<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: dswstate - Dispatcher parse tree walk management routines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acparser.h"
#समावेश "acdispat.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_DISPATCHER
ACPI_MODULE_NAME("dswstate")

  /* Local prototypes */
अटल acpi_status
acpi_ds_result_stack_push(काष्ठा acpi_walk_state *walk_state);
अटल acpi_status acpi_ds_result_stack_pop(काष्ठा acpi_walk_state *walk_state);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_result_pop
 *
 * PARAMETERS:  object              - Where to वापस the popped object
 *              walk_state          - Current Walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Pop an object off the top of this walk's result stack
 *
 ******************************************************************************/

acpi_status
acpi_ds_result_pop(जोड़ acpi_opeअक्रम_object **object,
		   काष्ठा acpi_walk_state *walk_state)
अणु
	u32 index;
	जोड़ acpi_generic_state *state;
	acpi_status status;

	ACPI_FUNCTION_NAME(ds_result_pop);

	state = walk_state->results;

	/* Incorrect state of result stack */

	अगर (state && !walk_state->result_count) अणु
		ACPI_ERROR((AE_INFO, "No results on result stack"));
		वापस (AE_AML_INTERNAL);
	पूर्ण

	अगर (!state && walk_state->result_count) अणु
		ACPI_ERROR((AE_INFO, "No result state for result stack"));
		वापस (AE_AML_INTERNAL);
	पूर्ण

	/* Empty result stack */

	अगर (!state) अणु
		ACPI_ERROR((AE_INFO, "Result stack is empty! State=%p",
			    walk_state));
		वापस (AE_AML_NO_RETURN_VALUE);
	पूर्ण

	/* Return object of the top element and clean that top element result stack */

	walk_state->result_count--;
	index = (u32)walk_state->result_count % ACPI_RESULTS_FRAME_OBJ_NUM;

	*object = state->results.obj_desc[index];
	अगर (!*object) अणु
		ACPI_ERROR((AE_INFO,
			    "No result objects on result stack, State=%p",
			    walk_state));
		वापस (AE_AML_NO_RETURN_VALUE);
	पूर्ण

	state->results.obj_desc[index] = शून्य;
	अगर (index == 0) अणु
		status = acpi_ds_result_stack_pop(walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Obj=%p [%s] Index=%X State=%p Num=%X\n", *object,
			  acpi_ut_get_object_type_name(*object),
			  index, walk_state, walk_state->result_count));

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_result_push
 *
 * PARAMETERS:  object              - Where to वापस the popped object
 *              walk_state          - Current Walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Push an object onto the current result stack
 *
 ******************************************************************************/

acpi_status
acpi_ds_result_push(जोड़ acpi_opeअक्रम_object *object,
		    काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_generic_state *state;
	acpi_status status;
	u32 index;

	ACPI_FUNCTION_NAME(ds_result_push);

	अगर (walk_state->result_count > walk_state->result_size) अणु
		ACPI_ERROR((AE_INFO, "Result stack is full"));
		वापस (AE_AML_INTERNAL);
	पूर्ण अन्यथा अगर (walk_state->result_count == walk_state->result_size) अणु

		/* Extend the result stack */

		status = acpi_ds_result_stack_push(walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			ACPI_ERROR((AE_INFO,
				    "Failed to extend the result stack"));
			वापस (status);
		पूर्ण
	पूर्ण

	अगर (!(walk_state->result_count < walk_state->result_size)) अणु
		ACPI_ERROR((AE_INFO, "No free elements in result stack"));
		वापस (AE_AML_INTERNAL);
	पूर्ण

	state = walk_state->results;
	अगर (!state) अणु
		ACPI_ERROR((AE_INFO, "No result stack frame during push"));
		वापस (AE_AML_INTERNAL);
	पूर्ण

	अगर (!object) अणु
		ACPI_ERROR((AE_INFO,
			    "Null Object! Obj=%p State=%p Num=%u",
			    object, walk_state, walk_state->result_count));
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/* Assign the address of object to the top मुक्त element of result stack */

	index = (u32)walk_state->result_count % ACPI_RESULTS_FRAME_OBJ_NUM;
	state->results.obj_desc[index] = object;
	walk_state->result_count++;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Obj=%p [%s] State=%p Num=%X Cur=%X\n",
			  object,
			  acpi_ut_get_object_type_name((जोड़
							acpi_opeअक्रम_object *)
						       object), walk_state,
			  walk_state->result_count,
			  walk_state->current_result));

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_result_stack_push
 *
 * PARAMETERS:  walk_state          - Current Walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Push an object onto the walk_state result stack
 *
 ******************************************************************************/

अटल acpi_status acpi_ds_result_stack_push(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_generic_state *state;

	ACPI_FUNCTION_NAME(ds_result_stack_push);

	/* Check क्रम stack overflow */

	अगर (((u32) walk_state->result_size + ACPI_RESULTS_FRAME_OBJ_NUM) >
	    ACPI_RESULTS_OBJ_NUM_MAX) अणु
		ACPI_ERROR((AE_INFO, "Result stack overflow: State=%p Num=%u",
			    walk_state, walk_state->result_size));
		वापस (AE_STACK_OVERFLOW);
	पूर्ण

	state = acpi_ut_create_generic_state();
	अगर (!state) अणु
		वापस (AE_NO_MEMORY);
	पूर्ण

	state->common.descriptor_type = ACPI_DESC_TYPE_STATE_RESULT;
	acpi_ut_push_generic_state(&walk_state->results, state);

	/* Increase the length of the result stack by the length of frame */

	walk_state->result_size += ACPI_RESULTS_FRAME_OBJ_NUM;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Results=%p State=%p\n",
			  state, walk_state));

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_result_stack_pop
 *
 * PARAMETERS:  walk_state          - Current Walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Pop an object off of the walk_state result stack
 *
 ******************************************************************************/

अटल acpi_status acpi_ds_result_stack_pop(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_generic_state *state;

	ACPI_FUNCTION_NAME(ds_result_stack_pop);

	/* Check क्रम stack underflow */

	अगर (walk_state->results == शून्य) अणु
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Result stack underflow - State=%p\n",
				  walk_state));
		वापस (AE_AML_NO_OPERAND);
	पूर्ण

	अगर (walk_state->result_size < ACPI_RESULTS_FRAME_OBJ_NUM) अणु
		ACPI_ERROR((AE_INFO, "Insufficient result stack size"));
		वापस (AE_AML_INTERNAL);
	पूर्ण

	state = acpi_ut_pop_generic_state(&walk_state->results);
	acpi_ut_delete_generic_state(state);

	/* Decrease the length of result stack by the length of frame */

	walk_state->result_size -= ACPI_RESULTS_FRAME_OBJ_NUM;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
			  "Result=%p RemainingResults=%X State=%p\n",
			  state, walk_state->result_count, walk_state));

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_obj_stack_push
 *
 * PARAMETERS:  object              - Object to push
 *              walk_state          - Current Walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Push an object onto this walk's object/opeअक्रम stack
 *
 ******************************************************************************/

acpi_status
acpi_ds_obj_stack_push(व्योम *object, काष्ठा acpi_walk_state *walk_state)
अणु
	ACPI_FUNCTION_NAME(ds_obj_stack_push);

	/* Check क्रम stack overflow */

	अगर (walk_state->num_opeअक्रमs >= ACPI_OBJ_NUM_OPERANDS) अणु
		ACPI_ERROR((AE_INFO,
			    "Object stack overflow! Obj=%p State=%p #Ops=%u",
			    object, walk_state, walk_state->num_opeअक्रमs));
		वापस (AE_STACK_OVERFLOW);
	पूर्ण

	/* Put the object onto the stack */

	walk_state->opeअक्रमs[walk_state->opeअक्रम_index] = object;
	walk_state->num_opeअक्रमs++;

	/* For the usual order of filling the opeअक्रम stack */

	walk_state->opeअक्रम_index++;

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Obj=%p [%s] State=%p #Ops=%X\n",
			  object,
			  acpi_ut_get_object_type_name((जोड़
							acpi_opeअक्रम_object *)
						       object), walk_state,
			  walk_state->num_opeअक्रमs));

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_obj_stack_pop
 *
 * PARAMETERS:  pop_count           - Number of objects/entries to pop
 *              walk_state          - Current Walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Pop this walk's object stack. Objects on the stack are NOT
 *              deleted by this routine.
 *
 ******************************************************************************/

acpi_status
acpi_ds_obj_stack_pop(u32 pop_count, काष्ठा acpi_walk_state *walk_state)
अणु
	u32 i;

	ACPI_FUNCTION_NAME(ds_obj_stack_pop);

	क्रम (i = 0; i < pop_count; i++) अणु

		/* Check क्रम stack underflow */

		अगर (walk_state->num_opeअक्रमs == 0) अणु
			ACPI_ERROR((AE_INFO,
				    "Object stack underflow! Count=%X State=%p #Ops=%u",
				    pop_count, walk_state,
				    walk_state->num_opeअक्रमs));
			वापस (AE_STACK_UNDERFLOW);
		पूर्ण

		/* Just set the stack entry to null */

		walk_state->num_opeअक्रमs--;
		walk_state->opeअक्रमs[walk_state->num_opeअक्रमs] = शून्य;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Count=%X State=%p #Ops=%u\n",
			  pop_count, walk_state, walk_state->num_opeअक्रमs));

	वापस (AE_OK);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_obj_stack_pop_and_delete
 *
 * PARAMETERS:  pop_count           - Number of objects/entries to pop
 *              walk_state          - Current Walk state
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Pop this walk's object stack and delete each object that is
 *              popped off.
 *
 ******************************************************************************/

व्योम
acpi_ds_obj_stack_pop_and_delete(u32 pop_count,
				 काष्ठा acpi_walk_state *walk_state)
अणु
	s32 i;
	जोड़ acpi_opeअक्रम_object *obj_desc;

	ACPI_FUNCTION_NAME(ds_obj_stack_pop_and_delete);

	अगर (pop_count == 0) अणु
		वापस;
	पूर्ण

	क्रम (i = (s32)pop_count - 1; i >= 0; i--) अणु
		अगर (walk_state->num_opeअक्रमs == 0) अणु
			वापस;
		पूर्ण

		/* Pop the stack and delete an object अगर present in this stack entry */

		walk_state->num_opeअक्रमs--;
		obj_desc = walk_state->opeअक्रमs[i];
		अगर (obj_desc) अणु
			acpi_ut_हटाओ_reference(walk_state->opeअक्रमs[i]);
			walk_state->opeअक्रमs[i] = शून्य;
		पूर्ण
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Count=%X State=%p #Ops=%X\n",
			  pop_count, walk_state, walk_state->num_opeअक्रमs));
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_get_current_walk_state
 *
 * PARAMETERS:  thपढ़ो          - Get current active state क्रम this Thपढ़ो
 *
 * RETURN:      Poपूर्णांकer to the current walk state
 *
 * DESCRIPTION: Get the walk state that is at the head of the list (the "current"
 *              walk state.)
 *
 ******************************************************************************/

काष्ठा acpi_walk_state *acpi_ds_get_current_walk_state(काष्ठा acpi_thपढ़ो_state
						       *thपढ़ो)
अणु
	ACPI_FUNCTION_NAME(ds_get_current_walk_state);

	अगर (!thपढ़ो) अणु
		वापस (शून्य);
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_PARSE, "Current WalkState %p\n",
			  thपढ़ो->walk_state_list));

	वापस (thपढ़ो->walk_state_list);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_push_walk_state
 *
 * PARAMETERS:  walk_state      - State to push
 *              thपढ़ो          - Thपढ़ो state object
 *
 * RETURN:      None
 *
 * DESCRIPTION: Place the Thपढ़ो state at the head of the state list
 *
 ******************************************************************************/

व्योम
acpi_ds_push_walk_state(काष्ठा acpi_walk_state *walk_state,
			काष्ठा acpi_thपढ़ो_state *thपढ़ो)
अणु
	ACPI_FUNCTION_TRACE(ds_push_walk_state);

	walk_state->next = thपढ़ो->walk_state_list;
	thपढ़ो->walk_state_list = walk_state;

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_pop_walk_state
 *
 * PARAMETERS:  thपढ़ो      - Current thपढ़ो state
 *
 * RETURN:      A walk_state object popped from the thपढ़ो's stack
 *
 * DESCRIPTION: Remove and वापस the walkstate object that is at the head of
 *              the walk stack क्रम the given walk list. शून्य indicates that
 *              the list is empty.
 *
 ******************************************************************************/

काष्ठा acpi_walk_state *acpi_ds_pop_walk_state(काष्ठा acpi_thपढ़ो_state *thपढ़ो)
अणु
	काष्ठा acpi_walk_state *walk_state;

	ACPI_FUNCTION_TRACE(ds_pop_walk_state);

	walk_state = thपढ़ो->walk_state_list;

	अगर (walk_state) अणु

		/* Next walk state becomes the current walk state */

		thपढ़ो->walk_state_list = walk_state->next;

		/*
		 * Don't clear the NEXT field, this serves as an indicator
		 * that there is a parent WALK STATE
		 * Do Not: walk_state->Next = शून्य;
		 */
	पूर्ण

	वापस_PTR(walk_state);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_create_walk_state
 *
 * PARAMETERS:  owner_id        - ID क्रम object creation
 *              origin          - Starting poपूर्णांक क्रम this walk
 *              method_desc     - Method object
 *              thपढ़ो          - Current thपढ़ो state
 *
 * RETURN:      Poपूर्णांकer to the new walk state.
 *
 * DESCRIPTION: Allocate and initialize a new walk state. The current walk
 *              state is set to this new state.
 *
 ******************************************************************************/

काष्ठा acpi_walk_state *acpi_ds_create_walk_state(acpi_owner_id owner_id,
						  जोड़ acpi_parse_object
						  *origin,
						  जोड़ acpi_opeअक्रम_object
						  *method_desc,
						  काष्ठा acpi_thपढ़ो_state
						  *thपढ़ो)
अणु
	काष्ठा acpi_walk_state *walk_state;

	ACPI_FUNCTION_TRACE(ds_create_walk_state);

	walk_state = ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_walk_state));
	अगर (!walk_state) अणु
		वापस_PTR(शून्य);
	पूर्ण

	walk_state->descriptor_type = ACPI_DESC_TYPE_WALK;
	walk_state->method_desc = method_desc;
	walk_state->owner_id = owner_id;
	walk_state->origin = origin;
	walk_state->thपढ़ो = thपढ़ो;

	walk_state->parser_state.start_op = origin;

	/* Init the method args/local */

#अगर_अघोषित ACPI_CONSTANT_EVAL_ONLY
	acpi_ds_method_data_init(walk_state);
#पूर्ण_अगर

	/* Put the new state at the head of the walk list */

	अगर (thपढ़ो) अणु
		acpi_ds_push_walk_state(walk_state, thपढ़ो);
	पूर्ण

	वापस_PTR(walk_state);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_init_aml_walk
 *
 * PARAMETERS:  walk_state      - New state to be initialized
 *              op              - Current parse op
 *              method_node     - Control method NS node, अगर any
 *              aml_start       - Start of AML
 *              aml_length      - Length of AML
 *              info            - Method info block (params, etc.)
 *              pass_number     - 1, 2, or 3
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Initialize a walk state क्रम a pass 1 or 2 parse tree walk
 *
 ******************************************************************************/

acpi_status
acpi_ds_init_aml_walk(काष्ठा acpi_walk_state *walk_state,
		      जोड़ acpi_parse_object *op,
		      काष्ठा acpi_namespace_node *method_node,
		      u8 * aml_start,
		      u32 aml_length,
		      काष्ठा acpi_evaluate_info *info, u8 pass_number)
अणु
	acpi_status status;
	काष्ठा acpi_parse_state *parser_state = &walk_state->parser_state;
	जोड़ acpi_parse_object *extra_op;

	ACPI_FUNCTION_TRACE(ds_init_aml_walk);

	walk_state->parser_state.aml =
	    walk_state->parser_state.aml_start = aml_start;
	walk_state->parser_state.aml_end =
	    walk_state->parser_state.pkg_end = aml_start + aml_length;

	/* The next_op of the next_walk will be the beginning of the method */

	walk_state->next_op = शून्य;
	walk_state->pass_number = pass_number;

	अगर (info) अणु
		walk_state->params = info->parameters;
		walk_state->caller_वापस_desc = &info->वापस_object;
	पूर्ण

	status = acpi_ps_init_scope(&walk_state->parser_state, op);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (method_node) अणु
		walk_state->parser_state.start_node = method_node;
		walk_state->walk_type = ACPI_WALK_METHOD;
		walk_state->method_node = method_node;
		walk_state->method_desc =
		    acpi_ns_get_attached_object(method_node);

		/* Push start scope on scope stack and make it current  */

		status =
		    acpi_ds_scope_stack_push(method_node, ACPI_TYPE_METHOD,
					     walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण

		/* Init the method arguments */

		status = acpi_ds_method_data_init_args(walk_state->params,
						       ACPI_METHOD_NUM_ARGS,
						       walk_state);
		अगर (ACPI_FAILURE(status)) अणु
			वापस_ACPI_STATUS(status);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Setup the current scope.
		 * Find a Named Op that has a namespace node associated with it.
		 * search upwards from this Op. Current scope is the first
		 * Op with a namespace node.
		 */
		extra_op = parser_state->start_op;
		जबतक (extra_op && !extra_op->common.node) अणु
			extra_op = extra_op->common.parent;
		पूर्ण

		अगर (!extra_op) अणु
			parser_state->start_node = शून्य;
		पूर्ण अन्यथा अणु
			parser_state->start_node = extra_op->common.node;
		पूर्ण

		अगर (parser_state->start_node) अणु

			/* Push start scope on scope stack and make it current  */

			status =
			    acpi_ds_scope_stack_push(parser_state->start_node,
						     parser_state->start_node->
						     type, walk_state);
			अगर (ACPI_FAILURE(status)) अणु
				वापस_ACPI_STATUS(status);
			पूर्ण
		पूर्ण
	पूर्ण

	status = acpi_ds_init_callbacks(walk_state, pass_number);
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ds_delete_walk_state
 *
 * PARAMETERS:  walk_state      - State to delete
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Delete a walk state including all पूर्णांकernal data काष्ठाures
 *
 ******************************************************************************/

व्योम acpi_ds_delete_walk_state(काष्ठा acpi_walk_state *walk_state)
अणु
	जोड़ acpi_generic_state *state;

	ACPI_FUNCTION_TRACE_PTR(ds_delete_walk_state, walk_state);

	अगर (!walk_state) अणु
		वापस_VOID;
	पूर्ण

	अगर (walk_state->descriptor_type != ACPI_DESC_TYPE_WALK) अणु
		ACPI_ERROR((AE_INFO, "%p is not a valid walk state",
			    walk_state));
		वापस_VOID;
	पूर्ण

	/* There should not be any खोलो scopes */

	अगर (walk_state->parser_state.scope) अणु
		ACPI_ERROR((AE_INFO, "%p walk still has a scope list",
			    walk_state));
		acpi_ps_cleanup_scope(&walk_state->parser_state);
	पूर्ण

	/* Always must मुक्त any linked control states */

	जबतक (walk_state->control_state) अणु
		state = walk_state->control_state;
		walk_state->control_state = state->common.next;

		acpi_ut_delete_generic_state(state);
	पूर्ण

	/* Always must मुक्त any linked parse states */

	जबतक (walk_state->scope_info) अणु
		state = walk_state->scope_info;
		walk_state->scope_info = state->common.next;

		acpi_ut_delete_generic_state(state);
	पूर्ण

	/* Always must मुक्त any stacked result states */

	जबतक (walk_state->results) अणु
		state = walk_state->results;
		walk_state->results = state->common.next;

		acpi_ut_delete_generic_state(state);
	पूर्ण

	ACPI_FREE(walk_state);
	वापस_VOID;
पूर्ण
