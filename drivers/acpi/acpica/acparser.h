<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Module Name: acparser.h - AML Parser subcomponent prototypes and defines
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACPARSER_H__
#घोषणा __ACPARSER_H__

#घोषणा OP_HAS_RETURN_VALUE             1

/* Variable number of arguments. This field must be 32 bits */

#घोषणा ACPI_VAR_ARGS                   ACPI_UINT32_MAX

#घोषणा ACPI_PARSE_DELETE_TREE          0x0001
#घोषणा ACPI_PARSE_NO_TREE_DELETE       0x0000
#घोषणा ACPI_PARSE_TREE_MASK            0x0001

#घोषणा ACPI_PARSE_LOAD_PASS1           0x0010
#घोषणा ACPI_PARSE_LOAD_PASS2           0x0020
#घोषणा ACPI_PARSE_EXECUTE              0x0030
#घोषणा ACPI_PARSE_MODE_MASK            0x0030

#घोषणा ACPI_PARSE_DEFERRED_OP          0x0100
#घोषणा ACPI_PARSE_DISASSEMBLE          0x0200

#घोषणा ACPI_PARSE_MODULE_LEVEL         0x0400

/******************************************************************************
 *
 * Parser पूर्णांकerfaces
 *
 *****************************************************************************/

बाह्य स्थिर u8 acpi_gbl_लघु_op_index[];
बाह्य स्थिर u8 acpi_gbl_दीर्घ_op_index[];

/*
 * psxface - Parser बाह्यal पूर्णांकerfaces
 */
acpi_status acpi_ps_execute_method(काष्ठा acpi_evaluate_info *info);

acpi_status acpi_ps_execute_table(काष्ठा acpi_evaluate_info *info);

/*
 * psargs - Parse AML opcode arguments
 */
u8 *acpi_ps_get_next_package_end(काष्ठा acpi_parse_state *parser_state);

अक्षर *acpi_ps_get_next_namestring(काष्ठा acpi_parse_state *parser_state);

व्योम
acpi_ps_get_next_simple_arg(काष्ठा acpi_parse_state *parser_state,
			    u32 arg_type, जोड़ acpi_parse_object *arg);

acpi_status
acpi_ps_get_next_namepath(काष्ठा acpi_walk_state *walk_state,
			  काष्ठा acpi_parse_state *parser_state,
			  जोड़ acpi_parse_object *arg,
			  u8 possible_method_call);

/* Values क्रम u8 above */

#घोषणा ACPI_NOT_METHOD_CALL            FALSE
#घोषणा ACPI_POSSIBLE_METHOD_CALL       TRUE

acpi_status
acpi_ps_get_next_arg(काष्ठा acpi_walk_state *walk_state,
		     काष्ठा acpi_parse_state *parser_state,
		     u32 arg_type, जोड़ acpi_parse_object **वापस_arg);

/*
 * psfind
 */
जोड़ acpi_parse_object *acpi_ps_find_name(जोड़ acpi_parse_object *scope,
					   u32 name, u32 opcode);

जोड़ acpi_parse_object *acpi_ps_get_parent(जोड़ acpi_parse_object *op);

/*
 * psobject - support क्रम parse object processing
 */
acpi_status
acpi_ps_build_named_op(काष्ठा acpi_walk_state *walk_state,
		       u8 *aml_op_start,
		       जोड़ acpi_parse_object *unnamed_op,
		       जोड़ acpi_parse_object **op);

acpi_status
acpi_ps_create_op(काष्ठा acpi_walk_state *walk_state,
		  u8 *aml_op_start, जोड़ acpi_parse_object **new_op);

acpi_status
acpi_ps_complete_op(काष्ठा acpi_walk_state *walk_state,
		    जोड़ acpi_parse_object **op, acpi_status status);

acpi_status
acpi_ps_complete_final_op(काष्ठा acpi_walk_state *walk_state,
			  जोड़ acpi_parse_object *op, acpi_status status);

/*
 * psopinfo - AML Opcode inक्रमmation
 */
स्थिर काष्ठा acpi_opcode_info *acpi_ps_get_opcode_info(u16 opcode);

स्थिर अक्षर *acpi_ps_get_opcode_name(u16 opcode);

u8 acpi_ps_get_argument_count(u32 op_type);

/*
 * psparse - top level parsing routines
 */
acpi_status acpi_ps_parse_aml(काष्ठा acpi_walk_state *walk_state);

u32 acpi_ps_get_opcode_size(u32 opcode);

u16 acpi_ps_peek_opcode(काष्ठा acpi_parse_state *state);

acpi_status
acpi_ps_complete_this_op(काष्ठा acpi_walk_state *walk_state,
			 जोड़ acpi_parse_object *op);

acpi_status
acpi_ps_next_parse_state(काष्ठा acpi_walk_state *walk_state,
			 जोड़ acpi_parse_object *op,
			 acpi_status callback_status);

/*
 * psloop - मुख्य parse loop
 */
acpi_status acpi_ps_parse_loop(काष्ठा acpi_walk_state *walk_state);

/*
 * psscope - Scope stack management routines
 */
acpi_status
acpi_ps_init_scope(काष्ठा acpi_parse_state *parser_state,
		   जोड़ acpi_parse_object *root);

जोड़ acpi_parse_object *acpi_ps_get_parent_scope(काष्ठा acpi_parse_state
						  *state);

u8 acpi_ps_has_completed_scope(काष्ठा acpi_parse_state *parser_state);

व्योम
acpi_ps_pop_scope(काष्ठा acpi_parse_state *parser_state,
		  जोड़ acpi_parse_object **op, u32 *arg_list, u32 *arg_count);

acpi_status
acpi_ps_push_scope(काष्ठा acpi_parse_state *parser_state,
		   जोड़ acpi_parse_object *op,
		   u32 reमुख्यing_args, u32 arg_count);

व्योम acpi_ps_cleanup_scope(काष्ठा acpi_parse_state *state);

/*
 * pstree - parse tree manipulation routines
 */
व्योम
acpi_ps_append_arg(जोड़ acpi_parse_object *op, जोड़ acpi_parse_object *arg);

जोड़ acpi_parse_object *acpi_ps_find(जोड़ acpi_parse_object *scope,
				      अक्षर *path, u16 opcode, u32 create);

जोड़ acpi_parse_object *acpi_ps_get_arg(जोड़ acpi_parse_object *op, u32 argn);

जोड़ acpi_parse_object *acpi_ps_get_depth_next(जोड़ acpi_parse_object *origin,
						जोड़ acpi_parse_object *op);

/*
 * pswalk - parse tree walk routines
 */
acpi_status
acpi_ps_walk_parsed_aml(जोड़ acpi_parse_object *start_op,
			जोड़ acpi_parse_object *end_op,
			जोड़ acpi_opeअक्रम_object *mth_desc,
			काष्ठा acpi_namespace_node *start_node,
			जोड़ acpi_opeअक्रम_object **params,
			जोड़ acpi_opeअक्रम_object **caller_वापस_desc,
			acpi_owner_id owner_id,
			acpi_parse_करोwnwards descending_callback,
			acpi_parse_upwards ascending_callback);

acpi_status
acpi_ps_get_next_walk_op(काष्ठा acpi_walk_state *walk_state,
			 जोड़ acpi_parse_object *op,
			 acpi_parse_upwards ascending_callback);

acpi_status acpi_ps_delete_completed_op(काष्ठा acpi_walk_state *walk_state);

व्योम acpi_ps_delete_parse_tree(जोड़ acpi_parse_object *root);

/*
 * psutils - parser utilities
 */
जोड़ acpi_parse_object *acpi_ps_create_scope_op(u8 *aml);

व्योम acpi_ps_init_op(जोड़ acpi_parse_object *op, u16 opcode);

जोड़ acpi_parse_object *acpi_ps_alloc_op(u16 opcode, u8 *aml);

व्योम acpi_ps_मुक्त_op(जोड़ acpi_parse_object *op);

u8 acpi_ps_is_leading_अक्षर(u32 c);

u32 acpi_ps_get_name(जोड़ acpi_parse_object *op);

व्योम acpi_ps_set_name(जोड़ acpi_parse_object *op, u32 name);

/*
 * psdump - display parser tree
 */
u32
acpi_ps_sprपूर्णांक_path(अक्षर *buffer_start,
		    u32 buffer_size, जोड़ acpi_parse_object *op);

u32
acpi_ps_sprपूर्णांक_op(अक्षर *buffer_start,
		  u32 buffer_size, जोड़ acpi_parse_object *op);

व्योम acpi_ps_show(जोड़ acpi_parse_object *op);

#पूर्ण_अगर				/* __ACPARSER_H__ */
