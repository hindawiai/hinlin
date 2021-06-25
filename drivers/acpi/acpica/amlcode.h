<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: amlcode.h - Definitions क्रम AML, as included in "definition blocks"
 *                   Declarations and definitions contained herein are derived
 *                   directly from the ACPI specअगरication.
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __AMLCODE_H__
#घोषणा __AMLCODE_H__

/* primary opcodes */

#घोषणा AML_ZERO_OP                 (u16) 0x00
#घोषणा AML_ONE_OP                  (u16) 0x01
#घोषणा AML_ALIAS_OP                (u16) 0x06
#घोषणा AML_NAME_OP                 (u16) 0x08
#घोषणा AML_BYTE_OP                 (u16) 0x0a
#घोषणा AML_WORD_OP                 (u16) 0x0b
#घोषणा AML_DWORD_OP                (u16) 0x0c
#घोषणा AML_STRING_OP               (u16) 0x0d
#घोषणा AML_QWORD_OP                (u16) 0x0e	/* ACPI 2.0 */
#घोषणा AML_SCOPE_OP                (u16) 0x10
#घोषणा AML_BUFFER_OP               (u16) 0x11
#घोषणा AML_PACKAGE_OP              (u16) 0x12
#घोषणा AML_VARIABLE_PACKAGE_OP     (u16) 0x13	/* ACPI 2.0 */
#घोषणा AML_METHOD_OP               (u16) 0x14
#घोषणा AML_EXTERNAL_OP             (u16) 0x15	/* ACPI 6.0 */
#घोषणा AML_DUAL_NAME_PREFIX        (u16) 0x2e
#घोषणा AML_MULTI_NAME_PREFIX       (u16) 0x2f
#घोषणा AML_EXTENDED_PREFIX         (u16) 0x5b
#घोषणा AML_ROOT_PREFIX             (u16) 0x5c
#घोषणा AML_PARENT_PREFIX           (u16) 0x5e
#घोषणा AML_FIRST_LOCAL_OP          (u16) 0x60	/* Used क्रम Local op # calculations */
#घोषणा AML_LOCAL0                  (u16) 0x60
#घोषणा AML_LOCAL1                  (u16) 0x61
#घोषणा AML_LOCAL2                  (u16) 0x62
#घोषणा AML_LOCAL3                  (u16) 0x63
#घोषणा AML_LOCAL4                  (u16) 0x64
#घोषणा AML_LOCAL5                  (u16) 0x65
#घोषणा AML_LOCAL6                  (u16) 0x66
#घोषणा AML_LOCAL7                  (u16) 0x67
#घोषणा AML_FIRST_ARG_OP            (u16) 0x68	/* Used क्रम Arg op # calculations */
#घोषणा AML_ARG0                    (u16) 0x68
#घोषणा AML_ARG1                    (u16) 0x69
#घोषणा AML_ARG2                    (u16) 0x6a
#घोषणा AML_ARG3                    (u16) 0x6b
#घोषणा AML_ARG4                    (u16) 0x6c
#घोषणा AML_ARG5                    (u16) 0x6d
#घोषणा AML_ARG6                    (u16) 0x6e
#घोषणा AML_STORE_OP                (u16) 0x70
#घोषणा AML_REF_OF_OP               (u16) 0x71
#घोषणा AML_ADD_OP                  (u16) 0x72
#घोषणा AML_CONCATENATE_OP          (u16) 0x73
#घोषणा AML_SUBTRACT_OP             (u16) 0x74
#घोषणा AML_INCREMENT_OP            (u16) 0x75
#घोषणा AML_DECREMENT_OP            (u16) 0x76
#घोषणा AML_MULTIPLY_OP             (u16) 0x77
#घोषणा AML_DIVIDE_OP               (u16) 0x78
#घोषणा AML_SHIFT_LEFT_OP           (u16) 0x79
#घोषणा AML_SHIFT_RIGHT_OP          (u16) 0x7a
#घोषणा AML_BIT_AND_OP              (u16) 0x7b
#घोषणा AML_BIT_न_अंकD_OP             (u16) 0x7c
#घोषणा AML_BIT_OR_OP               (u16) 0x7d
#घोषणा AML_BIT_NOR_OP              (u16) 0x7e
#घोषणा AML_BIT_XOR_OP              (u16) 0x7f
#घोषणा AML_BIT_NOT_OP              (u16) 0x80
#घोषणा AML_FIND_SET_LEFT_BIT_OP    (u16) 0x81
#घोषणा AML_FIND_SET_RIGHT_BIT_OP   (u16) 0x82
#घोषणा AML_DEREF_OF_OP             (u16) 0x83
#घोषणा AML_CONCATENATE_TEMPLATE_OP (u16) 0x84	/* ACPI 2.0 */
#घोषणा AML_MOD_OP                  (u16) 0x85	/* ACPI 2.0 */
#घोषणा AML_NOTIFY_OP               (u16) 0x86
#घोषणा AML_SIZE_OF_OP              (u16) 0x87
#घोषणा AML_INDEX_OP                (u16) 0x88
#घोषणा AML_MATCH_OP                (u16) 0x89
#घोषणा AML_CREATE_DWORD_FIELD_OP   (u16) 0x8a
#घोषणा AML_CREATE_WORD_FIELD_OP    (u16) 0x8b
#घोषणा AML_CREATE_BYTE_FIELD_OP    (u16) 0x8c
#घोषणा AML_CREATE_BIT_FIELD_OP     (u16) 0x8d
#घोषणा AML_OBJECT_TYPE_OP          (u16) 0x8e
#घोषणा AML_CREATE_QWORD_FIELD_OP   (u16) 0x8f	/* ACPI 2.0 */
#घोषणा AML_LOGICAL_AND_OP          (u16) 0x90
#घोषणा AML_LOGICAL_OR_OP           (u16) 0x91
#घोषणा AML_LOGICAL_NOT_OP          (u16) 0x92
#घोषणा AML_LOGICAL_EQUAL_OP        (u16) 0x93
#घोषणा AML_LOGICAL_GREATER_OP      (u16) 0x94
#घोषणा AML_LOGICAL_LESS_OP         (u16) 0x95
#घोषणा AML_TO_BUFFER_OP            (u16) 0x96	/* ACPI 2.0 */
#घोषणा AML_TO_DECIMAL_STRING_OP    (u16) 0x97	/* ACPI 2.0 */
#घोषणा AML_TO_HEX_STRING_OP        (u16) 0x98	/* ACPI 2.0 */
#घोषणा AML_TO_INTEGER_OP           (u16) 0x99	/* ACPI 2.0 */
#घोषणा AML_TO_STRING_OP            (u16) 0x9c	/* ACPI 2.0 */
#घोषणा AML_COPY_OBJECT_OP          (u16) 0x9d	/* ACPI 2.0 */
#घोषणा AML_MID_OP                  (u16) 0x9e	/* ACPI 2.0 */
#घोषणा AML_CONTINUE_OP             (u16) 0x9f	/* ACPI 2.0 */
#घोषणा AML_IF_OP                   (u16) 0xa0
#घोषणा AML_ELSE_OP                 (u16) 0xa1
#घोषणा AML_WHILE_OP                (u16) 0xa2
#घोषणा AML_NOOP_OP                 (u16) 0xa3
#घोषणा AML_RETURN_OP               (u16) 0xa4
#घोषणा AML_BREAK_OP                (u16) 0xa5
#घोषणा AML_COMMENT_OP              (u16) 0xa9
#घोषणा AML_BREAKPOINT_OP          (u16) 0xcc
#घोषणा AML_ONES_OP                 (u16) 0xff

/*
 * Combination opcodes (actually two one-byte opcodes)
 * Used by the disassembler and iASL compiler
 */
#घोषणा AML_LOGICAL_GREATER_EQUAL_OP (u16) 0x9295	/* LNot (LLess) */
#घोषणा AML_LOGICAL_LESS_EQUAL_OP    (u16) 0x9294	/* LNot (LGreater) */
#घोषणा AML_LOGICAL_NOT_EQUAL_OP     (u16) 0x9293	/* LNot (LEqual) */

/* Prefixed (2-byte) opcodes (with AML_EXTENDED_PREFIX) */

#घोषणा AML_EXTENDED_OPCODE         (u16) 0x5b00	/* Prefix क्रम 2-byte opcodes */

#घोषणा AML_MUTEX_OP                (u16) 0x5b01
#घोषणा AML_EVENT_OP                (u16) 0x5b02
#घोषणा AML_SHIFT_RIGHT_BIT_OP      (u16) 0x5b10	/* Obsolete, not in ACPI spec */
#घोषणा AML_SHIFT_LEFT_BIT_OP       (u16) 0x5b11	/* Obsolete, not in ACPI spec */
#घोषणा AML_CONDITIONAL_REF_OF_OP   (u16) 0x5b12
#घोषणा AML_CREATE_FIELD_OP         (u16) 0x5b13
#घोषणा AML_LOAD_TABLE_OP           (u16) 0x5b1f	/* ACPI 2.0 */
#घोषणा AML_LOAD_OP                 (u16) 0x5b20
#घोषणा AML_STALL_OP                (u16) 0x5b21
#घोषणा AML_SLEEP_OP                (u16) 0x5b22
#घोषणा AML_ACQUIRE_OP              (u16) 0x5b23
#घोषणा AML_SIGNAL_OP               (u16) 0x5b24
#घोषणा AML_WAIT_OP                 (u16) 0x5b25
#घोषणा AML_RESET_OP                (u16) 0x5b26
#घोषणा AML_RELEASE_OP              (u16) 0x5b27
#घोषणा AML_FROM_BCD_OP             (u16) 0x5b28
#घोषणा AML_TO_BCD_OP               (u16) 0x5b29
#घोषणा AML_UNLOAD_OP               (u16) 0x5b2a
#घोषणा AML_REVISION_OP             (u16) 0x5b30
#घोषणा AML_DEBUG_OP                (u16) 0x5b31
#घोषणा AML_FATAL_OP                (u16) 0x5b32
#घोषणा AML_TIMER_OP                (u16) 0x5b33	/* ACPI 3.0 */
#घोषणा AML_REGION_OP               (u16) 0x5b80
#घोषणा AML_FIELD_OP                (u16) 0x5b81
#घोषणा AML_DEVICE_OP               (u16) 0x5b82
#घोषणा AML_PROCESSOR_OP            (u16) 0x5b83
#घोषणा AML_POWER_RESOURCE_OP       (u16) 0x5b84
#घोषणा AML_THERMAL_ZONE_OP         (u16) 0x5b85
#घोषणा AML_INDEX_FIELD_OP          (u16) 0x5b86
#घोषणा AML_BANK_FIELD_OP           (u16) 0x5b87
#घोषणा AML_DATA_REGION_OP          (u16) 0x5b88	/* ACPI 2.0 */

/*
 * Opcodes क्रम "Field" चालकs
 */
#घोषणा AML_FIELD_OFFSET_OP         (u8) 0x00
#घोषणा AML_FIELD_ACCESS_OP         (u8) 0x01
#घोषणा AML_FIELD_CONNECTION_OP     (u8) 0x02	/* ACPI 5.0 */
#घोषणा AML_FIELD_EXT_ACCESS_OP     (u8) 0x03	/* ACPI 5.0 */

/*
 * Internal opcodes
 * Use only "Unknown" AML opcodes, करोn't attempt to use
 * any valid ACPI ASCII values (A-Z, 0-9, '-')
 */
#घोषणा AML_INT_NAMEPATH_OP         (u16) 0x002d
#घोषणा AML_INT_NAMEDFIELD_OP       (u16) 0x0030
#घोषणा AML_INT_RESERVEDFIELD_OP    (u16) 0x0031
#घोषणा AML_INT_ACCESSFIELD_OP      (u16) 0x0032
#घोषणा AML_INT_BYTELIST_OP         (u16) 0x0033
#घोषणा AML_INT_METHODCALL_OP       (u16) 0x0035
#घोषणा AML_INT_RETURN_VALUE_OP     (u16) 0x0036
#घोषणा AML_INT_EVAL_SUBTREE_OP     (u16) 0x0037
#घोषणा AML_INT_CONNECTION_OP       (u16) 0x0038
#घोषणा AML_INT_EXTACCESSFIELD_OP   (u16) 0x0039

#घोषणा ARG_NONE                    0x0

/*
 * Argument types क्रम the AML Parser
 * Each field in the arg_types u32 is 5 bits, allowing क्रम a maximum of 6 arguments.
 * There can be up to 31 unique argument types
 * Zero is reserved as end-of-list indicator
 */
#घोषणा ARGP_BYTEDATA               0x01
#घोषणा ARGP_BYTELIST               0x02
#घोषणा ARGP_CHARLIST               0x03
#घोषणा ARGP_DATAOBJ                0x04
#घोषणा ARGP_DATAOBJLIST            0x05
#घोषणा ARGP_DWORDDATA              0x06
#घोषणा ARGP_FIELDLIST              0x07
#घोषणा ARGP_NAME                   0x08
#घोषणा ARGP_NAMESTRING             0x09
#घोषणा ARGP_OBJLIST                0x0A
#घोषणा ARGP_PKGLENGTH              0x0B
#घोषणा ARGP_SUPERNAME              0x0C
#घोषणा ARGP_TARGET                 0x0D
#घोषणा ARGP_TERMARG                0x0E
#घोषणा ARGP_TERMLIST               0x0F
#घोषणा ARGP_WORDDATA               0x10
#घोषणा ARGP_QWORDDATA              0x11
#घोषणा ARGP_SIMPLENAME             0x12	/* name_string | local_term | arg_term */
#घोषणा ARGP_NAME_OR_REF            0x13	/* For object_type only */
#घोषणा ARGP_MAX                    0x13
#घोषणा ARGP_COMMENT                0x14

/*
 * Resolved argument types क्रम the AML Interpreter
 * Each field in the arg_types u32 is 5 bits, allowing क्रम a maximum of 6 arguments.
 * There can be up to 31 unique argument types (0 is end-of-arg-list indicator)
 *
 * Note1: These values are completely independent from the ACPI_TYPEs
 *        i.e., ARGI_INTEGER != ACPI_TYPE_INTEGER
 *
 * Note2: If and when 5 bits becomes insufficient, it would probably be best
 * to convert to a 6-byte array of argument types, allowing 8 bits per argument.
 */

/* Single, simple types */

#घोषणा ARGI_ANYTYPE                0x01	/* Don't care */
#घोषणा ARGI_PACKAGE                0x02
#घोषणा ARGI_EVENT                  0x03
#घोषणा ARGI_MUTEX                  0x04
#घोषणा ARGI_DDBHANDLE              0x05

/* Interchangeable types (via implicit conversion) */

#घोषणा ARGI_INTEGER                0x06
#घोषणा ARGI_STRING                 0x07
#घोषणा ARGI_BUFFER                 0x08
#घोषणा ARGI_BUFFER_OR_STRING       0x09	/* Used by MID op only */
#घोषणा ARGI_COMPUTEDATA            0x0A	/* Buffer, String, or Integer */

/* Reference objects */

#घोषणा ARGI_INTEGER_REF            0x0B
#घोषणा ARGI_OBJECT_REF             0x0C
#घोषणा ARGI_DEVICE_REF             0x0D
#घोषणा ARGI_REFERENCE              0x0E
#घोषणा ARGI_TARGETREF              0x0F	/* Target, subject to implicit conversion */
#घोषणा ARGI_FIXED_TARGET           0x10	/* Target, no implicit conversion */
#घोषणा ARGI_SIMPLE_TARGET          0x11	/* Name, Local, Arg -- no implicit conversion */
#घोषणा ARGI_STORE_TARGET           0x12	/* Target क्रम store is TARGETREF + package objects */

/* Multiple/complex types */

#घोषणा ARGI_DATAOBJECT             0x13	/* Buffer, String, package or reference to a node - Used only by size_of चालक */
#घोषणा ARGI_COMPLEXOBJ             0x14	/* Buffer, String, or package (Used by INDEX op only) */
#घोषणा ARGI_REF_OR_STRING          0x15	/* Reference or String (Used by DEREFOF op only) */
#घोषणा ARGI_REGION_OR_BUFFER       0x16	/* Used by LOAD op only */
#घोषणा ARGI_DATAREFOBJ             0x17

/* Note: types above can expand to 0x1F maximum */

#घोषणा ARGI_INVALID_OPCODE         0xFFFFFFFF

/*
 * Some of the flags and types below are of the क्रमm:
 *
 * AML_FLAGS_EXEC_#A_#T,#R, or
 * AML_TYPE_EXEC_#A_#T,#R where:
 *
 *      #A is the number of required arguments
 *      #T is the number of target opeअक्रमs
 *      #R indicates whether there is a वापस value
 *
 * These types are used क्रम the top-level dispatch of the AML
 * opcode. They group similar चालकs that can share common
 * front-end code beक्रमe dispatch to the final code that implements
 * the चालक.
 */

/*
 * Opcode inक्रमmation flags
 */
#घोषणा AML_LOGICAL                 0x0001
#घोषणा AML_LOGICAL_NUMERIC         0x0002
#घोषणा AML_MATH                    0x0004
#घोषणा AML_CREATE                  0x0008
#घोषणा AML_FIELD                   0x0010
#घोषणा AML_DEFER                   0x0020
#घोषणा AML_NAMED                   0x0040
#घोषणा AML_NSNODE                  0x0080
#घोषणा AML_NSOPCODE                0x0100
#घोषणा AML_NSOBJECT                0x0200
#घोषणा AML_HAS_RETVAL              0x0400
#घोषणा AML_HAS_TARGET              0x0800
#घोषणा AML_HAS_ARGS                0x1000
#घोषणा AML_CONSTANT                0x2000
#घोषणा AML_NO_OPERAND_RESOLVE      0x4000

/* Convenient flag groupings of the flags above */

#घोषणा AML_FLAGS_EXEC_0A_0T_1R                                     AML_HAS_RETVAL
#घोषणा AML_FLAGS_EXEC_1A_0T_0R     AML_HAS_ARGS	/* Monadic1  */
#घोषणा AML_FLAGS_EXEC_1A_0T_1R     AML_HAS_ARGS |                  AML_HAS_RETVAL	/* Monadic2  */
#घोषणा AML_FLAGS_EXEC_1A_1T_0R     AML_HAS_ARGS | AML_HAS_TARGET
#घोषणा AML_FLAGS_EXEC_1A_1T_1R     AML_HAS_ARGS | AML_HAS_TARGET | AML_HAS_RETVAL	/* monadic2_r */
#घोषणा AML_FLAGS_EXEC_2A_0T_0R     AML_HAS_ARGS	/* Dyadic1   */
#घोषणा AML_FLAGS_EXEC_2A_0T_1R     AML_HAS_ARGS |                  AML_HAS_RETVAL	/* Dyadic2   */
#घोषणा AML_FLAGS_EXEC_2A_1T_1R     AML_HAS_ARGS | AML_HAS_TARGET | AML_HAS_RETVAL	/* dyadic2_r  */
#घोषणा AML_FLAGS_EXEC_2A_2T_1R     AML_HAS_ARGS | AML_HAS_TARGET | AML_HAS_RETVAL
#घोषणा AML_FLAGS_EXEC_3A_0T_0R     AML_HAS_ARGS
#घोषणा AML_FLAGS_EXEC_3A_1T_1R     AML_HAS_ARGS | AML_HAS_TARGET | AML_HAS_RETVAL
#घोषणा AML_FLAGS_EXEC_6A_0T_1R     AML_HAS_ARGS |                  AML_HAS_RETVAL

/*
 * The opcode Type is used in a dispatch table, करो not change
 * or add anything new without updating the table.
 */
#घोषणा AML_TYPE_EXEC_0A_0T_1R      0x00	/* 0 Args, 0 Target, 1 ret_val */
#घोषणा AML_TYPE_EXEC_1A_0T_0R      0x01	/* 1 Args, 0 Target, 0 ret_val */
#घोषणा AML_TYPE_EXEC_1A_0T_1R      0x02	/* 1 Args, 0 Target, 1 ret_val */
#घोषणा AML_TYPE_EXEC_1A_1T_0R      0x03	/* 1 Args, 1 Target, 0 ret_val */
#घोषणा AML_TYPE_EXEC_1A_1T_1R      0x04	/* 1 Args, 1 Target, 1 ret_val */
#घोषणा AML_TYPE_EXEC_2A_0T_0R      0x05	/* 2 Args, 0 Target, 0 ret_val */
#घोषणा AML_TYPE_EXEC_2A_0T_1R      0x06	/* 2 Args, 0 Target, 1 ret_val */
#घोषणा AML_TYPE_EXEC_2A_1T_1R      0x07	/* 2 Args, 1 Target, 1 ret_val */
#घोषणा AML_TYPE_EXEC_2A_2T_1R      0x08	/* 2 Args, 2 Target, 1 ret_val */
#घोषणा AML_TYPE_EXEC_3A_0T_0R      0x09	/* 3 Args, 0 Target, 0 ret_val */
#घोषणा AML_TYPE_EXEC_3A_1T_1R      0x0A	/* 3 Args, 1 Target, 1 ret_val */
#घोषणा AML_TYPE_EXEC_6A_0T_1R      0x0B	/* 6 Args, 0 Target, 1 ret_val */
/* End of types used in dispatch table */

#घोषणा AML_TYPE_LITERAL            0x0C
#घोषणा AML_TYPE_CONSTANT           0x0D
#घोषणा AML_TYPE_METHOD_ARGUMENT    0x0E
#घोषणा AML_TYPE_LOCAL_VARIABLE     0x0F
#घोषणा AML_TYPE_DATA_TERM          0x10

/* Generic क्रम an op that वापसs a value */

#घोषणा AML_TYPE_METHOD_CALL        0x11

/* Miscellaneous types */

#घोषणा AML_TYPE_CREATE_FIELD       0x12
#घोषणा AML_TYPE_CREATE_OBJECT      0x13
#घोषणा AML_TYPE_CONTROL            0x14
#घोषणा AML_TYPE_NAMED_NO_OBJ       0x15
#घोषणा AML_TYPE_NAMED_FIELD        0x16
#घोषणा AML_TYPE_NAMED_SIMPLE       0x17
#घोषणा AML_TYPE_NAMED_COMPLEX      0x18
#घोषणा AML_TYPE_RETURN             0x19
#घोषणा AML_TYPE_UNDEFINED          0x1A
#घोषणा AML_TYPE_BOGUS              0x1B

/* AML Package Length encodings */

#घोषणा ACPI_AML_PACKAGE_TYPE1      0x40
#घोषणा ACPI_AML_PACKAGE_TYPE2      0x4000
#घोषणा ACPI_AML_PACKAGE_TYPE3      0x400000
#घोषणा ACPI_AML_PACKAGE_TYPE4      0x40000000

/*
 * Opcode classes
 */
#घोषणा AML_CLASS_EXECUTE           0x00
#घोषणा AML_CLASS_CREATE            0x01
#घोषणा AML_CLASS_ARGUMENT          0x02
#घोषणा AML_CLASS_NAMED_OBJECT      0x03
#घोषणा AML_CLASS_CONTROL           0x04
#घोषणा AML_CLASS_ASCII             0x05
#घोषणा AML_CLASS_PREFIX            0x06
#घोषणा AML_CLASS_INTERNAL          0x07
#घोषणा AML_CLASS_RETURN_VALUE      0x08
#घोषणा AML_CLASS_METHOD_CALL       0x09
#घोषणा AML_CLASS_UNKNOWN           0x0A

/* Comparison operation codes क्रम match_op चालक */

प्रकार क्रमागत अणु
	MATCH_MTR = 0,
	MATCH_MEQ = 1,
	MATCH_MLE = 2,
	MATCH_MLT = 3,
	MATCH_MGE = 4,
	MATCH_MGT = 5
पूर्ण AML_MATCH_OPERATOR;

#घोषणा MAX_MATCH_OPERATOR          5

/*
 * field_flags
 *
 * This byte is extracted from the AML and includes three separate
 * pieces of inक्रमmation about the field:
 * 1) The field access type
 * 2) The field update rule
 * 3) The lock rule क्रम the field
 *
 * Bits 00 - 03 : access_type (any_acc, byte_acc, etc.)
 *      04      : lock_rule (1 == Lock)
 *      05 - 06 : update_rule
 */
#घोषणा AML_FIELD_ACCESS_TYPE_MASK  0x0F
#घोषणा AML_FIELD_LOCK_RULE_MASK    0x10
#घोषणा AML_FIELD_UPDATE_RULE_MASK  0x60

/* 1) Field Access Types */

प्रकार क्रमागत अणु
	AML_FIELD_ACCESS_ANY = 0x00,
	AML_FIELD_ACCESS_BYTE = 0x01,
	AML_FIELD_ACCESS_WORD = 0x02,
	AML_FIELD_ACCESS_DWORD = 0x03,
	AML_FIELD_ACCESS_QWORD = 0x04,	/* ACPI 2.0 */
	AML_FIELD_ACCESS_BUFFER = 0x05	/* ACPI 2.0 */
पूर्ण AML_ACCESS_TYPE;

/* 2) Field Lock Rules */

प्रकार क्रमागत अणु
	AML_FIELD_LOCK_NEVER = 0x00,
	AML_FIELD_LOCK_ALWAYS = 0x10
पूर्ण AML_LOCK_RULE;

/* 3) Field Update Rules */

प्रकार क्रमागत अणु
	AML_FIELD_UPDATE_PRESERVE = 0x00,
	AML_FIELD_UPDATE_WRITE_AS_ONES = 0x20,
	AML_FIELD_UPDATE_WRITE_AS_ZEROS = 0x40
पूर्ण AML_UPDATE_RULE;

/*
 * Field Access Attributes.
 * This byte is extracted from the AML via the
 * access_as keyword
 */
प्रकार क्रमागत अणु
	AML_FIELD_ATTRIB_QUICK = 0x02,
	AML_FIELD_ATTRIB_SEND_RECEIVE = 0x04,
	AML_FIELD_ATTRIB_BYTE = 0x06,
	AML_FIELD_ATTRIB_WORD = 0x08,
	AML_FIELD_ATTRIB_BLOCK = 0x0A,
	AML_FIELD_ATTRIB_BYTES = 0x0B,
	AML_FIELD_ATTRIB_PROCESS_CALL = 0x0C,
	AML_FIELD_ATTRIB_BLOCK_PROCESS_CALL = 0x0D,
	AML_FIELD_ATTRIB_RAW_BYTES = 0x0E,
	AML_FIELD_ATTRIB_RAW_PROCESS_BYTES = 0x0F
पूर्ण AML_ACCESS_ATTRIBUTE;

/* Bit fields in the AML method_flags byte */

#घोषणा AML_METHOD_ARG_COUNT        0x07
#घोषणा AML_METHOD_SERIALIZED       0x08
#घोषणा AML_METHOD_SYNC_LEVEL       0xF0

#पूर्ण_अगर				/* __AMLCODE_H__ */
