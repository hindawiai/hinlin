<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acdispat.h - dispatcher (parser to पूर्णांकerpreter पूर्णांकerface)
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित _ACDISPAT_H_
#घोषणा _ACDISPAT_H_

#घोषणा NAMखातापूर्ण_LOCAL_NTE    "__L0"
#घोषणा NAMखातापूर्ण_ARG_NTE      "__A0"

/*
 * dsargs - execution of dynamic arguments क्रम अटल objects
 */
acpi_status
acpi_ds_get_buffer_field_arguments(जोड़ acpi_opeअक्रम_object *obj_desc);

acpi_status
acpi_ds_get_bank_field_arguments(जोड़ acpi_opeअक्रम_object *obj_desc);

acpi_status acpi_ds_get_region_arguments(जोड़ acpi_opeअक्रम_object *rgn_desc);

acpi_status acpi_ds_get_buffer_arguments(जोड़ acpi_opeअक्रम_object *obj_desc);

acpi_status acpi_ds_get_package_arguments(जोड़ acpi_opeअक्रम_object *obj_desc);

/*
 * dscontrol - support क्रम execution control opcodes
 */
acpi_status
acpi_ds_exec_begin_control_op(काष्ठा acpi_walk_state *walk_state,
			      जोड़ acpi_parse_object *op);

acpi_status
acpi_ds_exec_end_control_op(काष्ठा acpi_walk_state *walk_state,
			    जोड़ acpi_parse_object *op);

/*
 * dsopcode - support क्रम late opeअक्रम evaluation
 */
acpi_status
acpi_ds_eval_buffer_field_opeअक्रमs(काष्ठा acpi_walk_state *walk_state,
				   जोड़ acpi_parse_object *op);

acpi_status
acpi_ds_eval_region_opeअक्रमs(काष्ठा acpi_walk_state *walk_state,
			     जोड़ acpi_parse_object *op);

acpi_status
acpi_ds_eval_table_region_opeअक्रमs(काष्ठा acpi_walk_state *walk_state,
				   जोड़ acpi_parse_object *op);

acpi_status
acpi_ds_eval_data_object_opeअक्रमs(काष्ठा acpi_walk_state *walk_state,
				  जोड़ acpi_parse_object *op,
				  जोड़ acpi_opeअक्रम_object *obj_desc);

acpi_status
acpi_ds_eval_bank_field_opeअक्रमs(काष्ठा acpi_walk_state *walk_state,
				 जोड़ acpi_parse_object *op);

acpi_status acpi_ds_initialize_region(acpi_handle obj_handle);

/*
 * dsexec - Parser/Interpreter पूर्णांकerface, method execution callbacks
 */
acpi_status
acpi_ds_get_predicate_value(काष्ठा acpi_walk_state *walk_state,
			    जोड़ acpi_opeअक्रम_object *result_obj);

acpi_status
acpi_ds_exec_begin_op(काष्ठा acpi_walk_state *walk_state,
		      जोड़ acpi_parse_object **out_op);

acpi_status acpi_ds_exec_end_op(काष्ठा acpi_walk_state *state);

/*
 * dsfield - Parser/Interpreter पूर्णांकerface क्रम AML fields
 */
acpi_status
acpi_ds_create_field(जोड़ acpi_parse_object *op,
		     काष्ठा acpi_namespace_node *region_node,
		     काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ds_create_bank_field(जोड़ acpi_parse_object *op,
			  काष्ठा acpi_namespace_node *region_node,
			  काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ds_create_index_field(जोड़ acpi_parse_object *op,
			   काष्ठा acpi_namespace_node *region_node,
			   काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ds_create_buffer_field(जोड़ acpi_parse_object *op,
			    काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ds_init_field_objects(जोड़ acpi_parse_object *op,
			   काष्ठा acpi_walk_state *walk_state);

/*
 * dsload - Parser/Interpreter पूर्णांकerface
 */
acpi_status
acpi_ds_init_callbacks(काष्ठा acpi_walk_state *walk_state, u32 pass_number);

/* dsload - pass 1 namespace load callbacks */

acpi_status
acpi_ds_load1_begin_op(काष्ठा acpi_walk_state *walk_state,
		       जोड़ acpi_parse_object **out_op);

acpi_status acpi_ds_load1_end_op(काष्ठा acpi_walk_state *walk_state);

/* dsload - pass 2 namespace load callbacks */

acpi_status
acpi_ds_load2_begin_op(काष्ठा acpi_walk_state *walk_state,
		       जोड़ acpi_parse_object **out_op);

acpi_status acpi_ds_load2_end_op(काष्ठा acpi_walk_state *walk_state);

/*
 * dsmthdat - method data (locals/args)
 */
acpi_status
acpi_ds_store_object_to_local(u8 type,
			      u32 index,
			      जोड़ acpi_opeअक्रम_object *src_desc,
			      काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ds_method_data_get_entry(u16 opcode,
			      u32 index,
			      काष्ठा acpi_walk_state *walk_state,
			      जोड़ acpi_opeअक्रम_object ***node);

व्योम acpi_ds_method_data_delete_all(काष्ठा acpi_walk_state *walk_state);

u8 acpi_ds_is_method_value(जोड़ acpi_opeअक्रम_object *obj_desc);

acpi_status
acpi_ds_method_data_get_value(u8 type,
			      u32 index,
			      काष्ठा acpi_walk_state *walk_state,
			      जोड़ acpi_opeअक्रम_object **dest_desc);

acpi_status
acpi_ds_method_data_init_args(जोड़ acpi_opeअक्रम_object **params,
			      u32 max_param_count,
			      काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ds_method_data_get_node(u8 type,
			     u32 index,
			     काष्ठा acpi_walk_state *walk_state,
			     काष्ठा acpi_namespace_node **node);

व्योम acpi_ds_method_data_init(काष्ठा acpi_walk_state *walk_state);

/*
 * dsmethod - Parser/Interpreter पूर्णांकerface - control method parsing
 */
acpi_status
acpi_ds_स्वतः_serialize_method(काष्ठा acpi_namespace_node *node,
			      जोड़ acpi_opeअक्रम_object *obj_desc);

acpi_status
acpi_ds_call_control_method(काष्ठा acpi_thपढ़ो_state *thपढ़ो,
			    काष्ठा acpi_walk_state *walk_state,
			    जोड़ acpi_parse_object *op);

acpi_status
acpi_ds_restart_control_method(काष्ठा acpi_walk_state *walk_state,
			       जोड़ acpi_opeअक्रम_object *वापस_desc);

व्योम
acpi_ds_terminate_control_method(जोड़ acpi_opeअक्रम_object *method_desc,
				 काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ds_begin_method_execution(काष्ठा acpi_namespace_node *method_node,
			       जोड़ acpi_opeअक्रम_object *obj_desc,
			       काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ds_method_error(acpi_status status, काष्ठा acpi_walk_state *walk_state);

/*
 * dsinit
 */
acpi_status
acpi_ds_initialize_objects(u32 table_index,
			   काष्ठा acpi_namespace_node *start_node);

/*
 * dsobject - Parser/Interpreter पूर्णांकerface - object initialization and conversion
 */
acpi_status
acpi_ds_build_पूर्णांकernal_object(काष्ठा acpi_walk_state *walk_state,
			      जोड़ acpi_parse_object *op,
			      जोड़ acpi_opeअक्रम_object **obj_desc_ptr);

acpi_status
acpi_ds_build_पूर्णांकernal_buffer_obj(काष्ठा acpi_walk_state *walk_state,
				  जोड़ acpi_parse_object *op,
				  u32 buffer_length,
				  जोड़ acpi_opeअक्रम_object **obj_desc_ptr);

acpi_status
acpi_ds_build_पूर्णांकernal_package_obj(काष्ठा acpi_walk_state *walk_state,
				   जोड़ acpi_parse_object *op,
				   u32 package_length,
				   जोड़ acpi_opeअक्रम_object **obj_desc);

acpi_status
acpi_ds_init_object_from_op(काष्ठा acpi_walk_state *walk_state,
			    जोड़ acpi_parse_object *op,
			    u16 opcode, जोड़ acpi_opeअक्रम_object **obj_desc);

acpi_status
acpi_ds_create_node(काष्ठा acpi_walk_state *walk_state,
		    काष्ठा acpi_namespace_node *node,
		    जोड़ acpi_parse_object *op);

/*
 * dspkginit - Package object initialization
 */
acpi_status
acpi_ds_init_package_element(u8 object_type,
			     जोड़ acpi_opeअक्रम_object *source_object,
			     जोड़ acpi_generic_state *state, व्योम *context);

/*
 * dsutils - Parser/Interpreter पूर्णांकerface utility routines
 */
व्योम acpi_ds_clear_implicit_वापस(काष्ठा acpi_walk_state *walk_state);

u8
acpi_ds_करो_implicit_वापस(जोड़ acpi_opeअक्रम_object *वापस_desc,
			   काष्ठा acpi_walk_state *walk_state,
			   u8 add_reference);

u8
acpi_ds_is_result_used(जोड़ acpi_parse_object *op,
		       काष्ठा acpi_walk_state *walk_state);

व्योम
acpi_ds_delete_result_अगर_not_used(जोड़ acpi_parse_object *op,
				  जोड़ acpi_opeअक्रम_object *result_obj,
				  काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ds_create_opeअक्रम(काष्ठा acpi_walk_state *walk_state,
		       जोड़ acpi_parse_object *arg, u32 args_reमुख्यing);

acpi_status
acpi_ds_create_opeअक्रमs(काष्ठा acpi_walk_state *walk_state,
			जोड़ acpi_parse_object *first_arg);

acpi_status acpi_ds_resolve_opeअक्रमs(काष्ठा acpi_walk_state *walk_state);

व्योम acpi_ds_clear_opeअक्रमs(काष्ठा acpi_walk_state *walk_state);

acpi_status acpi_ds_evaluate_name_path(काष्ठा acpi_walk_state *walk_state);

/*
 * dswscope - Scope Stack manipulation
 */
acpi_status
acpi_ds_scope_stack_push(काष्ठा acpi_namespace_node *node,
			 acpi_object_type type,
			 काष्ठा acpi_walk_state *walk_state);

acpi_status acpi_ds_scope_stack_pop(काष्ठा acpi_walk_state *walk_state);

व्योम acpi_ds_scope_stack_clear(काष्ठा acpi_walk_state *walk_state);

/*
 * dswstate - parser WALK_STATE management routines
 */
acpi_status
acpi_ds_obj_stack_push(व्योम *object, काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ds_obj_stack_pop(u32 pop_count, काष्ठा acpi_walk_state *walk_state);

काष्ठा acpi_walk_state * acpi_ds_create_walk_state(acpi_owner_id owner_id,
						   जोड़ acpi_parse_object
						   *origin,
						   जोड़ acpi_opeअक्रम_object
						   *mth_desc,
						   काष्ठा acpi_thपढ़ो_state
						   *thपढ़ो);

acpi_status
acpi_ds_init_aml_walk(काष्ठा acpi_walk_state *walk_state,
		      जोड़ acpi_parse_object *op,
		      काष्ठा acpi_namespace_node *method_node,
		      u8 * aml_start,
		      u32 aml_length,
		      काष्ठा acpi_evaluate_info *info, u8 pass_number);

व्योम
acpi_ds_obj_stack_pop_and_delete(u32 pop_count,
				 काष्ठा acpi_walk_state *walk_state);

व्योम acpi_ds_delete_walk_state(काष्ठा acpi_walk_state *walk_state);

काष्ठा acpi_walk_state *acpi_ds_pop_walk_state(काष्ठा acpi_thपढ़ो_state
					       *thपढ़ो);

व्योम
acpi_ds_push_walk_state(काष्ठा acpi_walk_state *walk_state,
			काष्ठा acpi_thपढ़ो_state *thपढ़ो);

acpi_status acpi_ds_result_stack_clear(काष्ठा acpi_walk_state *walk_state);

काष्ठा acpi_walk_state *acpi_ds_get_current_walk_state(काष्ठा acpi_thपढ़ो_state
						       *thपढ़ो);

acpi_status
acpi_ds_result_pop(जोड़ acpi_opeअक्रम_object **object,
		   काष्ठा acpi_walk_state *walk_state);

acpi_status
acpi_ds_result_push(जोड़ acpi_opeअक्रम_object *object,
		    काष्ठा acpi_walk_state *walk_state);

/*
 * dsdebug - parser debugging routines
 */
व्योम
acpi_ds_dump_method_stack(acpi_status status,
			  काष्ठा acpi_walk_state *walk_state,
			  जोड़ acpi_parse_object *op);

#पूर्ण_अगर				/* _ACDISPAT_H_ */
