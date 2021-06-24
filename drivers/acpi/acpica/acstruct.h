<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acकाष्ठा.h - Internal काष्ठाs
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACSTRUCT_H__
#घोषणा __ACSTRUCT_H__

/* acpisrc:काष्ठा_defs -- क्रम acpisrc conversion */

/*****************************************************************************
 *
 * Tree walking प्रकारs and काष्ठाs
 *
 ****************************************************************************/

/*
 * Walk state - current state of a parse tree walk. Used क्रम both a leisurely
 * stroll through the tree (क्रम whatever reason), and क्रम control method
 * execution.
 */
#घोषणा ACPI_NEXT_OP_DOWNWARD       1
#घोषणा ACPI_NEXT_OP_UPWARD         2

/*
 * Groups of definitions क्रम walk_type used क्रम dअगरferent implementations of
 * walkers (never simultaneously) - flags क्रम पूर्णांकerpreter:
 */
#घोषणा ACPI_WALK_NON_METHOD        0
#घोषणा ACPI_WALK_METHOD            0x01
#घोषणा ACPI_WALK_METHOD_RESTART    0x02

काष्ठा acpi_walk_state अणु
	काष्ठा acpi_walk_state *next;	/* Next walk_state in list */
	u8 descriptor_type;	/* To dअगरferentiate various पूर्णांकernal objs */
	u8 walk_type;
	u16 opcode;		/* Current AML opcode */
	u8 next_op_info;	/* Info about next_op */
	u8 num_opeअक्रमs;	/* Stack poपूर्णांकer क्रम Opeअक्रमs[] array */
	u8 opeअक्रम_index;	/* Index पूर्णांकo opeअक्रम stack, to be used by acpi_ds_obj_stack_push */
	acpi_owner_id owner_id;	/* Owner of objects created during the walk */
	u8 last_predicate;	/* Result of last predicate */
	u8 current_result;
	u8 वापस_used;
	u8 scope_depth;
	u8 pass_number;		/* Parse pass during table load */
	u8 namespace_override;	/* Override existing objects */
	u8 result_size;		/* Total elements क्रम the result stack */
	u8 result_count;	/* Current number of occupied elements of result stack */
	u8 *aml;
	u32 arg_types;
	u32 method_अवरोधpoपूर्णांक;	/* For single stepping */
	u32 user_अवरोधpoपूर्णांक;	/* User AML अवरोधpoपूर्णांक */
	u32 parse_flags;

	काष्ठा acpi_parse_state parser_state;	/* Current state of parser */
	u32 prev_arg_types;
	u32 arg_count;		/* push क्रम fixed or var args */
	u16 method_nesting_depth;
	u8 method_is_nested;

	काष्ठा acpi_namespace_node arguments[ACPI_METHOD_NUM_ARGS];	/* Control method arguments */
	काष्ठा acpi_namespace_node local_variables[ACPI_METHOD_NUM_LOCALS];	/* Control method locals */
	जोड़ acpi_opeअक्रम_object *opeअक्रमs[ACPI_OBJ_NUM_OPERANDS + 1];	/* Opeअक्रमs passed to the पूर्णांकerpreter (+1 क्रम शून्य terminator) */
	जोड़ acpi_opeअक्रम_object **params;

	u8 *aml_last_जबतक;
	जोड़ acpi_opeअक्रम_object **caller_वापस_desc;
	जोड़ acpi_generic_state *control_state;	/* List of control states (nested IFs) */
	काष्ठा acpi_namespace_node *deferred_node;	/* Used when executing deferred opcodes */
	जोड़ acpi_opeअक्रम_object *implicit_वापस_obj;
	काष्ठा acpi_namespace_node *method_call_node;	/* Called method Node */
	जोड़ acpi_parse_object *method_call_op;	/* method_call Op अगर running a method */
	जोड़ acpi_opeअक्रम_object *method_desc;	/* Method descriptor अगर running a method */
	काष्ठा acpi_namespace_node *method_node;	/* Method node अगर running a method */
	अक्षर *method_pathname;	/* Full pathname of running method */
	जोड़ acpi_parse_object *op;	/* Current parser op */
	स्थिर काष्ठा acpi_opcode_info *op_info;	/* Info on current opcode */
	जोड़ acpi_parse_object *origin;	/* Start of walk [Obsolete] */
	जोड़ acpi_opeअक्रम_object *result_obj;
	जोड़ acpi_generic_state *results;	/* Stack of accumulated results */
	जोड़ acpi_opeअक्रम_object *वापस_desc;	/* Return object, अगर any */
	जोड़ acpi_generic_state *scope_info;	/* Stack of nested scopes */
	जोड़ acpi_parse_object *prev_op;	/* Last op that was processed */
	जोड़ acpi_parse_object *next_op;	/* next op to be processed */
	काष्ठा acpi_thपढ़ो_state *thपढ़ो;
	acpi_parse_करोwnwards descending_callback;
	acpi_parse_upwards ascending_callback;
पूर्ण;

/* Info used by acpi_ns_initialize_objects and acpi_ds_initialize_objects */

काष्ठा acpi_init_walk_info अणु
	u32 table_index;
	u32 object_count;
	u32 method_count;
	u32 serial_method_count;
	u32 non_serial_method_count;
	u32 serialized_method_count;
	u32 device_count;
	u32 op_region_count;
	u32 field_count;
	u32 buffer_count;
	u32 package_count;
	u32 op_region_init;
	u32 field_init;
	u32 buffer_init;
	u32 package_init;
	acpi_owner_id owner_id;
पूर्ण;

काष्ठा acpi_get_devices_info अणु
	acpi_walk_callback user_function;
	व्योम *context;
	स्थिर अक्षर *hid;
पूर्ण;

जोड़ acpi_aml_opeअक्रमs अणु
	जोड़ acpi_opeअक्रम_object *opeअक्रमs[7];

	काष्ठा अणु
		काष्ठा acpi_object_पूर्णांकeger *type;
		काष्ठा acpi_object_पूर्णांकeger *code;
		काष्ठा acpi_object_पूर्णांकeger *argument;

	पूर्ण fatal;

	काष्ठा अणु
		जोड़ acpi_opeअक्रम_object *source;
		काष्ठा acpi_object_पूर्णांकeger *index;
		जोड़ acpi_opeअक्रम_object *target;

	पूर्ण index;

	काष्ठा अणु
		जोड़ acpi_opeअक्रम_object *source;
		काष्ठा acpi_object_पूर्णांकeger *index;
		काष्ठा acpi_object_पूर्णांकeger *length;
		जोड़ acpi_opeअक्रम_object *target;

	पूर्ण mid;
पूर्ण;

/*
 * Structure used to pass object evaluation inक्रमmation and parameters.
 * Purpose is to reduce CPU stack use.
 */
काष्ठा acpi_evaluate_info अणु
	/* The first 3 elements are passed by the caller to acpi_ns_evaluate */

	काष्ठा acpi_namespace_node *prefix_node;	/* Input: starting node */
	स्थिर अक्षर *relative_pathname;	/* Input: path relative to prefix_node */
	जोड़ acpi_opeअक्रम_object **parameters;	/* Input: argument list */

	काष्ठा acpi_namespace_node *node;	/* Resolved node (prefix_node:relative_pathname) */
	जोड़ acpi_opeअक्रम_object *obj_desc;	/* Object attached to the resolved node */
	अक्षर *full_pathname;	/* Full pathname of the resolved node */

	स्थिर जोड़ acpi_predefined_info *predefined;	/* Used अगर Node is a predefined name */
	जोड़ acpi_opeअक्रम_object *वापस_object;	/* Object वापसed from the evaluation */
	जोड़ acpi_opeअक्रम_object *parent_package;	/* Used अगर वापस object is a Package */

	u32 वापस_flags;	/* Used क्रम वापस value analysis */
	u32 वापस_btype;	/* Biपंचांगapped type of the वापसed object */
	u16 param_count;	/* Count of the input argument list */
	u16 node_flags;		/* Same as Node->Flags */
	u8 pass_number;		/* Parser pass number */
	u8 वापस_object_type;	/* Object type of the वापसed object */
	u8 flags;		/* General flags */
पूर्ण;

/* Values क्रम Flags above */

#घोषणा ACPI_IGNORE_RETURN_VALUE    1

/* Defines क्रम वापस_flags field above */

#घोषणा ACPI_OBJECT_REPAIRED        1
#घोषणा ACPI_OBJECT_WRAPPED         2

/* Info used by acpi_ns_initialize_devices */

काष्ठा acpi_device_walk_info अणु
	काष्ठा acpi_table_desc *table_desc;
	काष्ठा acpi_evaluate_info *evaluate_info;
	u32 device_count;
	u32 num_STA;
	u32 num_INI;
पूर्ण;

/* Info used by Acpi  acpi_db_display_fields */

काष्ठा acpi_region_walk_info अणु
	u32 debug_level;
	u32 count;
	acpi_owner_id owner_id;
	u8 display_type;
	u32 address_space_id;
पूर्ण;

/* TBD: [Reकाष्ठाure] Merge with काष्ठा above */

काष्ठा acpi_walk_info अणु
	u32 debug_level;
	u32 count;
	acpi_owner_id owner_id;
	u8 display_type;
पूर्ण;

/* Display Types */

#घोषणा ACPI_DISPLAY_SUMMARY        (u8) 0
#घोषणा ACPI_DISPLAY_OBJECTS        (u8) 1
#घोषणा ACPI_DISPLAY_MASK           (u8) 1

#घोषणा ACPI_DISPLAY_SHORT          (u8) 2

#पूर्ण_अगर
