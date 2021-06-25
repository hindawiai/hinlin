<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Module Name: acapps - common include क्रम ACPI applications/tools
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित _ACCONVERT
#घोषणा _ACCONVERT

/* Definitions क्रम comment state */

#घोषणा ASL_COMMENT_STANDARD    1
#घोषणा ASLCOMMENT_INLINE       2
#घोषणा ASL_COMMENT_OPEN_PAREN  3
#घोषणा ASL_COMMENT_CLOSE_PAREN 4
#घोषणा ASL_COMMENT_CLOSE_BRACE 5

/* Definitions क्रम comment prपूर्णांक function*/

#घोषणा AML_COMMENT_STANDARD    1
#घोषणा AMLCOMMENT_INLINE       2
#घोषणा AML_COMMENT_END_NODE    3
#घोषणा AML_NAMECOMMENT         4
#घोषणा AML_COMMENT_CLOSE_BRACE 5
#घोषणा AML_COMMENT_ENDBLK      6
#घोषणा AML_COMMENT_INCLUDE     7

#अगर_घोषित ACPI_ASL_COMPILER
/*
 * cvcompiler
 */
व्योम
cv_process_comment(काष्ठा asl_comment_state current_state,
		   अक्षर *string_buffer, पूर्णांक c1);

व्योम
cv_process_comment_type2(काष्ठा asl_comment_state current_state,
			 अक्षर *string_buffer);

u32 cv_calculate_comment_lengths(जोड़ acpi_parse_object *op);

व्योम cv_process_comment_state(अक्षर input);

अक्षर *cv_append_अंतरभूत_comment(अक्षर *अंतरभूत_comment, अक्षर *to_add);

व्योम cv_add_to_comment_list(अक्षर *to_add);

व्योम cv_place_comment(u8 type, अक्षर *comment_string);

u32 cv_parse_op_block_type(जोड़ acpi_parse_object *op);

काष्ठा acpi_comment_node *cv_comment_node_सुस्मृति(व्योम);

व्योम cg_ग_लिखो_aml_def_block_comment(जोड़ acpi_parse_object *op);

व्योम
cg_ग_लिखो_one_aml_comment(जोड़ acpi_parse_object *op,
			 अक्षर *comment_to_prपूर्णांक, u8 input_option);

व्योम cg_ग_लिखो_aml_comment(जोड़ acpi_parse_object *op);

/*
 * cvparser
 */
व्योम cv_init_file_tree(काष्ठा acpi_table_header *table, खाता * root_file);

व्योम cv_clear_op_comments(जोड़ acpi_parse_object *op);

काष्ठा acpi_file_node *cv_filename_exists(अक्षर *filename,
					  काष्ठा acpi_file_node *head);

व्योम cv_label_file_node(जोड़ acpi_parse_object *op);

व्योम
cv_capture_list_comments(काष्ठा acpi_parse_state *parser_state,
			 काष्ठा acpi_comment_node *list_head,
			 काष्ठा acpi_comment_node *list_tail);

व्योम cv_capture_comments_only(काष्ठा acpi_parse_state *parser_state);

व्योम cv_capture_comments(काष्ठा acpi_walk_state *walk_state);

व्योम cv_transfer_comments(जोड़ acpi_parse_object *op);

/*
 * cvdisयंत्र
 */
व्योम cv_चयन_files(u32 level, जोड़ acpi_parse_object *op);

u8 cv_file_has_चयनed(जोड़ acpi_parse_object *op);

व्योम cv_बंद_paren_ग_लिखो_comment(जोड़ acpi_parse_object *op, u32 level);

व्योम cv_बंद_brace_ग_लिखो_comment(जोड़ acpi_parse_object *op, u32 level);

व्योम
cv_prपूर्णांक_one_comment_list(काष्ठा acpi_comment_node *comment_list, u32 level);

व्योम
cv_prपूर्णांक_one_comment_type(जोड़ acpi_parse_object *op,
			  u8 comment_type, अक्षर *end_str, u32 level);

#पूर्ण_अगर

#पूर्ण_अगर				/* _ACCONVERT */
