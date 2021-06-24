<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acdebug.h - ACPI/AML debugger
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACDEBUG_H__
#घोषणा __ACDEBUG_H__

/* The debugger is used in conjunction with the disassembler most of समय */

#अगर_घोषित ACPI_DISASSEMBLER
#समावेश "acdisasm.h"
#पूर्ण_अगर

#घोषणा ACPI_DEBUG_BUFFER_SIZE      0x4000	/* 16K buffer क्रम वापस objects */
#घोषणा ACPI_DEBUG_LENGTH_FORMAT    " (%.4X bits, %.3X bytes)"

काष्ठा acpi_db_command_info अणु
	स्थिर अक्षर *name;	/* Command Name */
	u8 min_args;		/* Minimum arguments required */
पूर्ण;

काष्ठा acpi_db_command_help अणु
	u8 line_count;		/* Number of help lines */
	अक्षर *invocation;	/* Command Invocation */
	अक्षर *description;	/* Command Description */
पूर्ण;

काष्ठा acpi_db_argument_info अणु
	स्थिर अक्षर *name;	/* Argument Name */
पूर्ण;

काष्ठा acpi_db_execute_walk अणु
	u32 count;
	u32 max_count;
	अक्षर name_seg[ACPI_NAMESEG_SIZE + 1];
पूर्ण;

#घोषणा PARAM_LIST(pl)                  pl

#घोषणा EX_NO_SINGLE_STEP               1
#घोषणा EX_SINGLE_STEP                  2
#घोषणा EX_ALL                          4

/*
 * dbxface - बाह्यal debugger पूर्णांकerfaces
 */
ACPI_DBR_DEPENDENT_RETURN_OK(acpi_status
			     acpi_db_single_step(काष्ठा acpi_walk_state
						 *walk_state,
						 जोड़ acpi_parse_object *op,
						 u32 op_type))
 ACPI_DBR_DEPENDENT_RETURN_VOID(व्योम
				acpi_db_संकेत_अवरोध_poपूर्णांक(काष्ठा
							   acpi_walk_state
							   *walk_state))

/*
 * dbcmds - debug commands and output routines
 */
काष्ठा acpi_namespace_node *acpi_db_convert_to_node(अक्षर *in_string);

व्योम acpi_db_display_table_info(अक्षर *table_arg);

व्योम acpi_db_display_ढाँचा(अक्षर *buffer_arg);

व्योम acpi_db_unload_acpi_table(अक्षर *name);

व्योम acpi_db_send_notअगरy(अक्षर *name, u32 value);

व्योम acpi_db_display_पूर्णांकerfaces(अक्षर *action_arg, अक्षर *पूर्णांकerface_name_arg);

acpi_status acpi_db_sleep(अक्षर *object_arg);

व्योम acpi_db_trace(अक्षर *enable_arg, अक्षर *method_arg, अक्षर *once_arg);

व्योम acpi_db_display_locks(व्योम);

व्योम acpi_db_display_resources(अक्षर *object_arg);

ACPI_HW_DEPENDENT_RETURN_VOID(व्योम acpi_db_display_gpes(व्योम))

व्योम acpi_db_display_handlers(व्योम);

ACPI_HW_DEPENDENT_RETURN_VOID(व्योम
			      acpi_db_generate_gpe(अक्षर *gpe_arg,
						   अक्षर *block_arg))
ACPI_HW_DEPENDENT_RETURN_VOID(व्योम acpi_db_generate_sci(व्योम))

व्योम acpi_db_execute_test(अक्षर *type_arg);

/*
 * dbconvert - miscellaneous conversion routines
 */
acpi_status acpi_db_hex_अक्षर_to_value(पूर्णांक hex_अक्षर, u8 *वापस_value);

acpi_status acpi_db_convert_to_package(अक्षर *string, जोड़ acpi_object *object);

acpi_status
acpi_db_convert_to_object(acpi_object_type type,
			  अक्षर *string, जोड़ acpi_object *object);

u8 *acpi_db_encode_pld_buffer(काष्ठा acpi_pld_info *pld_info);

व्योम acpi_db_dump_pld_buffer(जोड़ acpi_object *obj_desc);

/*
 * dbmethod - control method commands
 */
व्योम
acpi_db_set_method_अवरोधpoपूर्णांक(अक्षर *location,
			      काष्ठा acpi_walk_state *walk_state,
			      जोड़ acpi_parse_object *op);

व्योम acpi_db_set_method_call_अवरोधpoपूर्णांक(जोड़ acpi_parse_object *op);

व्योम acpi_db_set_method_data(अक्षर *type_arg, अक्षर *index_arg, अक्षर *value_arg);

acpi_status acpi_db_disassemble_method(अक्षर *name);

व्योम acpi_db_disassemble_aml(अक्षर *statements, जोड़ acpi_parse_object *op);

व्योम acpi_db_evaluate_predefined_names(व्योम);

व्योम acpi_db_evaluate_all(अक्षर *name_seg);

/*
 * dbnames - namespace commands
 */
व्योम acpi_db_set_scope(अक्षर *name);

व्योम acpi_db_dump_namespace(अक्षर *start_arg, अक्षर *depth_arg);

व्योम acpi_db_dump_namespace_paths(व्योम);

व्योम acpi_db_dump_namespace_by_owner(अक्षर *owner_arg, अक्षर *depth_arg);

acpi_status acpi_db_find_name_in_namespace(अक्षर *name_arg);

व्योम acpi_db_check_predefined_names(व्योम);

acpi_status
acpi_db_display_objects(अक्षर *obj_type_arg, अक्षर *display_count_arg);

व्योम acpi_db_check_पूर्णांकegrity(व्योम);

व्योम acpi_db_find_references(अक्षर *object_arg);

व्योम acpi_db_get_bus_info(व्योम);

acpi_status acpi_db_display_fields(u32 address_space_id);

/*
 * dbdisply - debug display commands
 */
व्योम acpi_db_display_method_info(जोड़ acpi_parse_object *op);

व्योम acpi_db_decode_and_display_object(अक्षर *target, अक्षर *output_type);

ACPI_DBR_DEPENDENT_RETURN_VOID(व्योम
			       acpi_db_display_result_object(जोड़
							     acpi_opeअक्रम_object
							     *obj_desc,
							     काष्ठा
							     acpi_walk_state
							     *walk_state))

acpi_status acpi_db_display_all_methods(अक्षर *display_count_arg);

व्योम acpi_db_display_arguments(व्योम);

व्योम acpi_db_display_locals(व्योम);

व्योम acpi_db_display_results(व्योम);

व्योम acpi_db_display_calling_tree(व्योम);

व्योम acpi_db_display_object_type(अक्षर *object_arg);

ACPI_DBR_DEPENDENT_RETURN_VOID(व्योम
			       acpi_db_display_argument_object(जोड़
							       acpi_opeअक्रम_object
							       *obj_desc,
							       काष्ठा
							       acpi_walk_state
							       *walk_state))

/*
 * dbexec - debugger control method execution
 */
व्योम
acpi_db_execute(अक्षर *name, अक्षर **args, acpi_object_type *types, u32 flags);

व्योम
acpi_db_create_execution_thपढ़ो(अक्षर *method_name_arg,
				अक्षर **arguments, acpi_object_type *types);

व्योम
acpi_db_create_execution_thपढ़ोs(अक्षर *num_thपढ़ोs_arg,
				 अक्षर *num_loops_arg, अक्षर *method_name_arg);

व्योम acpi_db_delete_objects(u32 count, जोड़ acpi_object *objects);

#अगर_घोषित ACPI_DBG_TRACK_ALLOCATIONS
u32 acpi_db_get_cache_info(काष्ठा acpi_memory_list *cache);
#पूर्ण_अगर

/*
 * dbfileio - Debugger file I/O commands
 */
acpi_object_type
acpi_db_match_argument(अक्षर *user_argument,
		       काष्ठा acpi_db_argument_info *arguments);

व्योम acpi_db_बंद_debug_file(व्योम);

व्योम acpi_db_खोलो_debug_file(अक्षर *name);

acpi_status acpi_db_load_acpi_table(अक्षर *filename);

acpi_status acpi_db_load_tables(काष्ठा acpi_new_table_desc *list_head);

/*
 * dbhistry - debugger HISTORY command
 */
व्योम acpi_db_add_to_history(अक्षर *command_line);

व्योम acpi_db_display_history(व्योम);

अक्षर *acpi_db_get_from_history(अक्षर *command_num_arg);

अक्षर *acpi_db_get_history_by_index(u32 commandd_num);

/*
 * dbinput - user front-end to the AML debugger
 */
acpi_status
acpi_db_command_dispatch(अक्षर *input_buffer,
			 काष्ठा acpi_walk_state *walk_state,
			 जोड़ acpi_parse_object *op);

व्योम ACPI_SYSTEM_XFACE acpi_db_execute_thपढ़ो(व्योम *context);

acpi_status acpi_db_user_commands(व्योम);

अक्षर *acpi_db_get_next_token(अक्षर *string,
			     अक्षर **next, acpi_object_type *वापस_type);

/*
 * dbobject
 */
व्योम acpi_db_decode_पूर्णांकernal_object(जोड़ acpi_opeअक्रम_object *obj_desc);

व्योम
acpi_db_display_पूर्णांकernal_object(जोड़ acpi_opeअक्रम_object *obj_desc,
				काष्ठा acpi_walk_state *walk_state);

व्योम acpi_db_decode_arguments(काष्ठा acpi_walk_state *walk_state);

व्योम acpi_db_decode_locals(काष्ठा acpi_walk_state *walk_state);

व्योम
acpi_db_dump_method_info(acpi_status status,
			 काष्ठा acpi_walk_state *walk_state);

/*
 * dbstats - Generation and display of ACPI table statistics
 */
व्योम acpi_db_generate_statistics(जोड़ acpi_parse_object *root, u8 is_method);

acpi_status acpi_db_display_statistics(अक्षर *type_arg);

/*
 * dbutils - AML debugger utilities
 */
व्योम acpi_db_set_output_destination(u32 where);

व्योम acpi_db_dump_बाह्यal_object(जोड़ acpi_object *obj_desc, u32 level);

व्योम acpi_db_prep_namestring(अक्षर *name);

काष्ठा acpi_namespace_node *acpi_db_local_ns_lookup(अक्षर *name);

व्योम acpi_db_uपूर्णांक32_to_hex_string(u32 value, अक्षर *buffer);

#पूर्ण_अगर				/* __ACDEBUG_H__ */
