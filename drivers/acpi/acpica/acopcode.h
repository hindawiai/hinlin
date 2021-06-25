<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acopcode.h - AML opcode inक्रमmation क्रम the AML parser and पूर्णांकerpreter
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACOPCODE_H__
#घोषणा __ACOPCODE_H__

#घोषणा MAX_EXTENDED_OPCODE         0x88
#घोषणा NUM_EXTENDED_OPCODE         (MAX_EXTENDED_OPCODE + 1)
#घोषणा MAX_INTERNAL_OPCODE
#घोषणा NUM_INTERNAL_OPCODE         (MAX_INTERNAL_OPCODE + 1)

/* Used क्रम non-asचिन्हित opcodes */

#घोषणा _UNK                        0x6B

/*
 * Reserved ASCII अक्षरacters. Do not use any of these क्रम
 * पूर्णांकernal opcodes, since they are used to dअगरferentiate
 * name strings from AML opcodes
 */
#घोषणा _ASC                        0x6C
#घोषणा _NAM                        0x6C
#घोषणा _PFX                        0x6D

/*
 * All AML opcodes and the parse-समय arguments क्रम each. Used by the AML
 * parser  Each list is compressed पूर्णांकo a 32-bit number and stored in the
 * master opcode table (in psopcode.c).
 */
#घोषणा ARGP_ACCESSFIELD_OP             ARGP_LIST1 (ARGP_NAMESTRING)
#घोषणा ARGP_ACQUIRE_OP                 ARGP_LIST2 (ARGP_SUPERNAME,  ARGP_WORDDATA)
#घोषणा ARGP_ADD_OP                     ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#घोषणा ARGP_ALIAS_OP                   ARGP_LIST2 (ARGP_NAMESTRING, ARGP_NAME)
#घोषणा ARGP_ARG0                       ARG_NONE
#घोषणा ARGP_ARG1                       ARG_NONE
#घोषणा ARGP_ARG2                       ARG_NONE
#घोषणा ARGP_ARG3                       ARG_NONE
#घोषणा ARGP_ARG4                       ARG_NONE
#घोषणा ARGP_ARG5                       ARG_NONE
#घोषणा ARGP_ARG6                       ARG_NONE
#घोषणा ARGP_BANK_FIELD_OP              ARGP_LIST6 (ARGP_PKGLENGTH,  ARGP_NAMESTRING,    ARGP_NAMESTRING,ARGP_TERMARG,   ARGP_BYTEDATA,  ARGP_FIELDLIST)
#घोषणा ARGP_BIT_AND_OP                 ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#घोषणा ARGP_BIT_न_अंकD_OP                ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#घोषणा ARGP_BIT_NOR_OP                 ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#घोषणा ARGP_BIT_NOT_OP                 ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
#घोषणा ARGP_BIT_OR_OP                  ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#घोषणा ARGP_BIT_XOR_OP                 ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#घोषणा ARGP_BREAK_OP                   ARG_NONE
#घोषणा ARGP_BREAK_POINT_OP             ARG_NONE
#घोषणा ARGP_BUFFER_OP                  ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_TERMARG,       ARGP_BYTELIST)
#घोषणा ARGP_BYTE_OP                    ARGP_LIST1 (ARGP_BYTEDATA)
#घोषणा ARGP_BYTELIST_OP                ARGP_LIST1 (ARGP_NAMESTRING)
#घोषणा ARGP_COMMENT_OP                 ARGP_LIST2 (ARGP_BYTEDATA,   ARGP_COMMENT)
#घोषणा ARGP_CONCAT_OP                  ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#घोषणा ARGP_CONCAT_RES_OP              ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#घोषणा ARGP_COND_REF_OF_OP             ARGP_LIST2 (ARGP_SIMPLENAME, ARGP_TARGET)
#घोषणा ARGP_CONNECTFIELD_OP            ARGP_LIST1 (ARGP_NAMESTRING)
#घोषणा ARGP_CONTINUE_OP                ARG_NONE
#घोषणा ARGP_COPY_OP                    ARGP_LIST2 (ARGP_TERMARG,    ARGP_SIMPLENAME)
#घोषणा ARGP_CREATE_BIT_FIELD_OP        ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_NAME)
#घोषणा ARGP_CREATE_BYTE_FIELD_OP       ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_NAME)
#घोषणा ARGP_CREATE_DWORD_FIELD_OP      ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_NAME)
#घोषणा ARGP_CREATE_FIELD_OP            ARGP_LIST4 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TERMARG,   ARGP_NAME)
#घोषणा ARGP_CREATE_QWORD_FIELD_OP      ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_NAME)
#घोषणा ARGP_CREATE_WORD_FIELD_OP       ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_NAME)
#घोषणा ARGP_DATA_REGION_OP             ARGP_LIST4 (ARGP_NAME,       ARGP_TERMARG,       ARGP_TERMARG,   ARGP_TERMARG)
#घोषणा ARGP_DEBUG_OP                   ARG_NONE
#घोषणा ARGP_DECREMENT_OP               ARGP_LIST1 (ARGP_SUPERNAME)
#घोषणा ARGP_DEREF_OF_OP                ARGP_LIST1 (ARGP_SUPERNAME)
#घोषणा ARGP_DEVICE_OP                  ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_OBJLIST)
#घोषणा ARGP_DIVIDE_OP                  ARGP_LIST4 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET,    ARGP_TARGET)
#घोषणा ARGP_DWORD_OP                   ARGP_LIST1 (ARGP_DWORDDATA)
#घोषणा ARGP_ELSE_OP                    ARGP_LIST2 (ARGP_PKGLENGTH,  ARGP_TERMLIST)
#घोषणा ARGP_EVENT_OP                   ARGP_LIST1 (ARGP_NAME)
#घोषणा ARGP_EXTERNAL_OP                ARGP_LIST3 (ARGP_NAME,       ARGP_BYTEDATA,      ARGP_BYTEDATA)
#घोषणा ARGP_FATAL_OP                   ARGP_LIST3 (ARGP_BYTEDATA,   ARGP_DWORDDATA,     ARGP_TERMARG)
#घोषणा ARGP_FIELD_OP                   ARGP_LIST4 (ARGP_PKGLENGTH,  ARGP_NAMESTRING,    ARGP_BYTEDATA,  ARGP_FIELDLIST)
#घोषणा ARGP_FIND_SET_LEFT_BIT_OP       ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
#घोषणा ARGP_FIND_SET_RIGHT_BIT_OP      ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
#घोषणा ARGP_FROM_BCD_OP                ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
#घोषणा ARGP_IF_OP                      ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_TERMARG,       ARGP_TERMLIST)
#घोषणा ARGP_INCREMENT_OP               ARGP_LIST1 (ARGP_SUPERNAME)
#घोषणा ARGP_INDEX_FIELD_OP             ARGP_LIST5 (ARGP_PKGLENGTH,  ARGP_NAMESTRING,    ARGP_NAMESTRING,ARGP_BYTEDATA,  ARGP_FIELDLIST)
#घोषणा ARGP_INDEX_OP                   ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#घोषणा ARGP_LAND_OP                    ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#घोषणा ARGP_LEQUAL_OP                  ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#घोषणा ARGP_LGREATER_OP                ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#घोषणा ARGP_LGREATEREQUAL_OP           ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#घोषणा ARGP_LLESS_OP                   ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#घोषणा ARGP_LLESSEQUAL_OP              ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#घोषणा ARGP_LNOT_OP                    ARGP_LIST1 (ARGP_TERMARG)
#घोषणा ARGP_LNOTEQUAL_OP               ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#घोषणा ARGP_LOAD_OP                    ARGP_LIST2 (ARGP_NAMESTRING, ARGP_SUPERNAME)
#घोषणा ARGP_LOAD_TABLE_OP              ARGP_LIST6 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TERMARG,   ARGP_TERMARG,  ARGP_TERMARG,   ARGP_TERMARG)
#घोषणा ARGP_LOCAL0                     ARG_NONE
#घोषणा ARGP_LOCAL1                     ARG_NONE
#घोषणा ARGP_LOCAL2                     ARG_NONE
#घोषणा ARGP_LOCAL3                     ARG_NONE
#घोषणा ARGP_LOCAL4                     ARG_NONE
#घोषणा ARGP_LOCAL5                     ARG_NONE
#घोषणा ARGP_LOCAL6                     ARG_NONE
#घोषणा ARGP_LOCAL7                     ARG_NONE
#घोषणा ARGP_LOR_OP                     ARGP_LIST2 (ARGP_TERMARG,    ARGP_TERMARG)
#घोषणा ARGP_MATCH_OP                   ARGP_LIST6 (ARGP_TERMARG,    ARGP_BYTEDATA,      ARGP_TERMARG,   ARGP_BYTEDATA,  ARGP_TERMARG,   ARGP_TERMARG)
#घोषणा ARGP_METHOD_OP                  ARGP_LIST4 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_BYTEDATA,  ARGP_TERMLIST)
#घोषणा ARGP_METHODCALL_OP              ARGP_LIST1 (ARGP_NAMESTRING)
#घोषणा ARGP_MID_OP                     ARGP_LIST4 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TERMARG,   ARGP_TARGET)
#घोषणा ARGP_MOD_OP                     ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#घोषणा ARGP_MULTIPLY_OP                ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#घोषणा ARGP_MUTEX_OP                   ARGP_LIST2 (ARGP_NAME,       ARGP_BYTEDATA)
#घोषणा ARGP_NAME_OP                    ARGP_LIST2 (ARGP_NAME,       ARGP_DATAOBJ)
#घोषणा ARGP_NAMEDFIELD_OP              ARGP_LIST1 (ARGP_NAMESTRING)
#घोषणा ARGP_NAMEPATH_OP                ARGP_LIST1 (ARGP_NAMESTRING)
#घोषणा ARGP_NOOP_OP                    ARG_NONE
#घोषणा ARGP_NOTIFY_OP                  ARGP_LIST2 (ARGP_SUPERNAME,  ARGP_TERMARG)
#घोषणा ARGP_OBJECT_TYPE_OP             ARGP_LIST1 (ARGP_SIMPLENAME)
#घोषणा ARGP_ONE_OP                     ARG_NONE
#घोषणा ARGP_ONES_OP                    ARG_NONE
#घोषणा ARGP_PACKAGE_OP                 ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_BYTEDATA,      ARGP_DATAOBJLIST)
#घोषणा ARGP_POWER_RES_OP               ARGP_LIST5 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_BYTEDATA,  ARGP_WORDDATA,  ARGP_OBJLIST)
#घोषणा ARGP_PROCESSOR_OP               ARGP_LIST6 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_BYTEDATA,  ARGP_DWORDDATA, ARGP_BYTEDATA,  ARGP_OBJLIST)
#घोषणा ARGP_QWORD_OP                   ARGP_LIST1 (ARGP_QWORDDATA)
#घोषणा ARGP_REF_OF_OP                  ARGP_LIST1 (ARGP_SIMPLENAME)
#घोषणा ARGP_REGION_OP                  ARGP_LIST4 (ARGP_NAME,       ARGP_BYTEDATA,      ARGP_TERMARG,   ARGP_TERMARG)
#घोषणा ARGP_RELEASE_OP                 ARGP_LIST1 (ARGP_SUPERNAME)
#घोषणा ARGP_RESERVEDFIELD_OP           ARGP_LIST1 (ARGP_NAMESTRING)
#घोषणा ARGP_RESET_OP                   ARGP_LIST1 (ARGP_SUPERNAME)
#घोषणा ARGP_RETURN_OP                  ARGP_LIST1 (ARGP_TERMARG)
#घोषणा ARGP_REVISION_OP                ARG_NONE
#घोषणा ARGP_SCOPE_OP                   ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_TERMLIST)
#घोषणा ARGP_SERIALFIELD_OP             ARGP_LIST1 (ARGP_NAMESTRING)
#घोषणा ARGP_SHIFT_LEFT_OP              ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#घोषणा ARGP_SHIFT_RIGHT_OP             ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#घोषणा ARGP_SIGNAL_OP                  ARGP_LIST1 (ARGP_SUPERNAME)
#घोषणा ARGP_SIZE_OF_OP                 ARGP_LIST1 (ARGP_SUPERNAME)
#घोषणा ARGP_SLEEP_OP                   ARGP_LIST1 (ARGP_TERMARG)
#घोषणा ARGP_STALL_OP                   ARGP_LIST1 (ARGP_TERMARG)
#घोषणा ARGP_STATICSTRING_OP            ARGP_LIST1 (ARGP_NAMESTRING)
#घोषणा ARGP_STORE_OP                   ARGP_LIST2 (ARGP_TERMARG,    ARGP_SUPERNAME)
#घोषणा ARGP_STRING_OP                  ARGP_LIST1 (ARGP_CHARLIST)
#घोषणा ARGP_SUBTRACT_OP                ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#घोषणा ARGP_THERMAL_ZONE_OP            ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_NAME,          ARGP_OBJLIST)
#घोषणा ARGP_TIMER_OP                   ARG_NONE
#घोषणा ARGP_TO_BCD_OP                  ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
#घोषणा ARGP_TO_BUFFER_OP               ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
#घोषणा ARGP_TO_DEC_STR_OP              ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
#घोषणा ARGP_TO_HEX_STR_OP              ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
#घोषणा ARGP_TO_INTEGER_OP              ARGP_LIST2 (ARGP_TERMARG,    ARGP_TARGET)
#घोषणा ARGP_TO_STRING_OP               ARGP_LIST3 (ARGP_TERMARG,    ARGP_TERMARG,       ARGP_TARGET)
#घोषणा ARGP_UNLOAD_OP                  ARGP_LIST1 (ARGP_SUPERNAME)
#घोषणा ARGP_VAR_PACKAGE_OP             ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_TERMARG,       ARGP_DATAOBJLIST)
#घोषणा ARGP_WAIT_OP                    ARGP_LIST2 (ARGP_SUPERNAME,  ARGP_TERMARG)
#घोषणा ARGP_WHILE_OP                   ARGP_LIST3 (ARGP_PKGLENGTH,  ARGP_TERMARG,       ARGP_TERMLIST)
#घोषणा ARGP_WORD_OP                    ARGP_LIST1 (ARGP_WORDDATA)
#घोषणा ARGP_ZERO_OP                    ARG_NONE

/*
 * All AML opcodes and the runसमय arguments क्रम each. Used by the AML
 * पूर्णांकerpreter  Each list is compressed पूर्णांकo a 32-bit number and stored
 * in the master opcode table (in psopcode.c).
 *
 * (Used by prep_opeअक्रमs procedure and the ASL Compiler)
 */
#घोषणा ARGI_ACCESSFIELD_OP             ARGI_INVALID_OPCODE
#घोषणा ARGI_ACQUIRE_OP                 ARGI_LIST2 (ARGI_MUTEX,      ARGI_INTEGER)
#घोषणा ARGI_ADD_OP                     ARGI_LIST3 (ARGI_INTEGER,    ARGI_INTEGER,       ARGI_TARGETREF)
#घोषणा ARGI_ALIAS_OP                   ARGI_INVALID_OPCODE
#घोषणा ARGI_ARG0                       ARG_NONE
#घोषणा ARGI_ARG1                       ARG_NONE
#घोषणा ARGI_ARG2                       ARG_NONE
#घोषणा ARGI_ARG3                       ARG_NONE
#घोषणा ARGI_ARG4                       ARG_NONE
#घोषणा ARGI_ARG5                       ARG_NONE
#घोषणा ARGI_ARG6                       ARG_NONE
#घोषणा ARGI_BANK_FIELD_OP              ARGI_LIST1 (ARGI_INTEGER)
#घोषणा ARGI_BIT_AND_OP                 ARGI_LIST3 (ARGI_INTEGER,    ARGI_INTEGER,       ARGI_TARGETREF)
#घोषणा ARGI_BIT_न_अंकD_OP                ARGI_LIST3 (ARGI_INTEGER,    ARGI_INTEGER,       ARGI_TARGETREF)
#घोषणा ARGI_BIT_NOR_OP                 ARGI_LIST3 (ARGI_INTEGER,    ARGI_INTEGER,       ARGI_TARGETREF)
#घोषणा ARGI_BIT_NOT_OP                 ARGI_LIST2 (ARGI_INTEGER,    ARGI_TARGETREF)
#घोषणा ARGI_BIT_OR_OP                  ARGI_LIST3 (ARGI_INTEGER,    ARGI_INTEGER,       ARGI_TARGETREF)
#घोषणा ARGI_BIT_XOR_OP                 ARGI_LIST3 (ARGI_INTEGER,    ARGI_INTEGER,       ARGI_TARGETREF)
#घोषणा ARGI_BREAK_OP                   ARG_NONE
#घोषणा ARGI_BREAK_POINT_OP             ARG_NONE
#घोषणा ARGI_BUFFER_OP                  ARGI_LIST1 (ARGI_INTEGER)
#घोषणा ARGI_BYTE_OP                    ARGI_INVALID_OPCODE
#घोषणा ARGI_BYTELIST_OP                ARGI_INVALID_OPCODE
#घोषणा ARGI_COMMENT_OP                 ARGI_INVALID_OPCODE
#घोषणा ARGI_CONCAT_OP                  ARGI_LIST3 (ARGI_ANYTYPE,    ARGI_ANYTYPE,       ARGI_TARGETREF)
#घोषणा ARGI_CONCAT_RES_OP              ARGI_LIST3 (ARGI_BUFFER,     ARGI_BUFFER,        ARGI_TARGETREF)
#घोषणा ARGI_COND_REF_OF_OP             ARGI_LIST2 (ARGI_OBJECT_REF, ARGI_TARGETREF)
#घोषणा ARGI_CONNECTFIELD_OP            ARGI_INVALID_OPCODE
#घोषणा ARGI_CONTINUE_OP                ARGI_INVALID_OPCODE
#घोषणा ARGI_COPY_OP                    ARGI_LIST2 (ARGI_ANYTYPE,    ARGI_SIMPLE_TARGET)
#घोषणा ARGI_CREATE_BIT_FIELD_OP        ARGI_LIST3 (ARGI_BUFFER,     ARGI_INTEGER,       ARGI_REFERENCE)
#घोषणा ARGI_CREATE_BYTE_FIELD_OP       ARGI_LIST3 (ARGI_BUFFER,     ARGI_INTEGER,       ARGI_REFERENCE)
#घोषणा ARGI_CREATE_DWORD_FIELD_OP      ARGI_LIST3 (ARGI_BUFFER,     ARGI_INTEGER,       ARGI_REFERENCE)
#घोषणा ARGI_CREATE_FIELD_OP            ARGI_LIST4 (ARGI_BUFFER,     ARGI_INTEGER,       ARGI_INTEGER,      ARGI_REFERENCE)
#घोषणा ARGI_CREATE_QWORD_FIELD_OP      ARGI_LIST3 (ARGI_BUFFER,     ARGI_INTEGER,       ARGI_REFERENCE)
#घोषणा ARGI_CREATE_WORD_FIELD_OP       ARGI_LIST3 (ARGI_BUFFER,     ARGI_INTEGER,       ARGI_REFERENCE)
#घोषणा ARGI_DATA_REGION_OP             ARGI_LIST3 (ARGI_STRING,     ARGI_STRING,        ARGI_STRING)
#घोषणा ARGI_DEBUG_OP                   ARG_NONE
#घोषणा ARGI_DECREMENT_OP               ARGI_LIST1 (ARGI_TARGETREF)
#घोषणा ARGI_DEREF_OF_OP                ARGI_LIST1 (ARGI_REF_OR_STRING)
#घोषणा ARGI_DEVICE_OP                  ARGI_INVALID_OPCODE
#घोषणा ARGI_DIVIDE_OP                  ARGI_LIST4 (ARGI_INTEGER,    ARGI_INTEGER,       ARGI_TARGETREF,    ARGI_TARGETREF)
#घोषणा ARGI_DWORD_OP                   ARGI_INVALID_OPCODE
#घोषणा ARGI_ELSE_OP                    ARGI_INVALID_OPCODE
#घोषणा ARGI_EVENT_OP                   ARGI_INVALID_OPCODE
#घोषणा ARGI_EXTERNAL_OP                ARGI_LIST3 (ARGI_STRING,     ARGI_INTEGER,       ARGI_INTEGER)
#घोषणा ARGI_FATAL_OP                   ARGI_LIST3 (ARGI_INTEGER,    ARGI_INTEGER,       ARGI_INTEGER)
#घोषणा ARGI_FIELD_OP                   ARGI_INVALID_OPCODE
#घोषणा ARGI_FIND_SET_LEFT_BIT_OP       ARGI_LIST2 (ARGI_INTEGER,    ARGI_TARGETREF)
#घोषणा ARGI_FIND_SET_RIGHT_BIT_OP      ARGI_LIST2 (ARGI_INTEGER,    ARGI_TARGETREF)
#घोषणा ARGI_FROM_BCD_OP                ARGI_LIST2 (ARGI_INTEGER,    ARGI_FIXED_TARGET)
#घोषणा ARGI_IF_OP                      ARGI_INVALID_OPCODE
#घोषणा ARGI_INCREMENT_OP               ARGI_LIST1 (ARGI_TARGETREF)
#घोषणा ARGI_INDEX_FIELD_OP             ARGI_INVALID_OPCODE
#घोषणा ARGI_INDEX_OP                   ARGI_LIST3 (ARGI_COMPLEXOBJ, ARGI_INTEGER,       ARGI_TARGETREF)
#घोषणा ARGI_LAND_OP                    ARGI_LIST2 (ARGI_INTEGER,    ARGI_INTEGER)
#घोषणा ARGI_LEQUAL_OP                  ARGI_LIST2 (ARGI_COMPUTEDATA,ARGI_COMPUTEDATA)
#घोषणा ARGI_LGREATER_OP                ARGI_LIST2 (ARGI_COMPUTEDATA,ARGI_COMPUTEDATA)
#घोषणा ARGI_LGREATEREQUAL_OP           ARGI_INVALID_OPCODE
#घोषणा ARGI_LLESS_OP                   ARGI_LIST2 (ARGI_COMPUTEDATA,ARGI_COMPUTEDATA)
#घोषणा ARGI_LLESSEQUAL_OP              ARGI_INVALID_OPCODE
#घोषणा ARGI_LNOT_OP                    ARGI_LIST1 (ARGI_INTEGER)
#घोषणा ARGI_LNOTEQUAL_OP               ARGI_INVALID_OPCODE
#घोषणा ARGI_LOAD_OP                    ARGI_LIST2 (ARGI_REGION_OR_BUFFER,ARGI_TARGETREF)
#घोषणा ARGI_LOAD_TABLE_OP              ARGI_LIST6 (ARGI_STRING,     ARGI_STRING,        ARGI_STRING,       ARGI_STRING,    ARGI_STRING, ARGI_ANYTYPE)
#घोषणा ARGI_LOCAL0                     ARG_NONE
#घोषणा ARGI_LOCAL1                     ARG_NONE
#घोषणा ARGI_LOCAL2                     ARG_NONE
#घोषणा ARGI_LOCAL3                     ARG_NONE
#घोषणा ARGI_LOCAL4                     ARG_NONE
#घोषणा ARGI_LOCAL5                     ARG_NONE
#घोषणा ARGI_LOCAL6                     ARG_NONE
#घोषणा ARGI_LOCAL7                     ARG_NONE
#घोषणा ARGI_LOR_OP                     ARGI_LIST2 (ARGI_INTEGER,    ARGI_INTEGER)
#घोषणा ARGI_MATCH_OP                   ARGI_LIST6 (ARGI_PACKAGE,    ARGI_INTEGER,   ARGI_COMPUTEDATA,      ARGI_INTEGER,ARGI_COMPUTEDATA,ARGI_INTEGER)
#घोषणा ARGI_METHOD_OP                  ARGI_INVALID_OPCODE
#घोषणा ARGI_METHODCALL_OP              ARGI_INVALID_OPCODE
#घोषणा ARGI_MID_OP                     ARGI_LIST4 (ARGI_BUFFER_OR_STRING,ARGI_INTEGER,  ARGI_INTEGER,      ARGI_TARGETREF)
#घोषणा ARGI_MOD_OP                     ARGI_LIST3 (ARGI_INTEGER,    ARGI_INTEGER,       ARGI_TARGETREF)
#घोषणा ARGI_MULTIPLY_OP                ARGI_LIST3 (ARGI_INTEGER,    ARGI_INTEGER,       ARGI_TARGETREF)
#घोषणा ARGI_MUTEX_OP                   ARGI_INVALID_OPCODE
#घोषणा ARGI_NAME_OP                    ARGI_INVALID_OPCODE
#घोषणा ARGI_NAMEDFIELD_OP              ARGI_INVALID_OPCODE
#घोषणा ARGI_NAMEPATH_OP                ARGI_INVALID_OPCODE
#घोषणा ARGI_NOOP_OP                    ARG_NONE
#घोषणा ARGI_NOTIFY_OP                  ARGI_LIST2 (ARGI_DEVICE_REF, ARGI_INTEGER)
#घोषणा ARGI_OBJECT_TYPE_OP             ARGI_LIST1 (ARGI_ANYTYPE)
#घोषणा ARGI_ONE_OP                     ARG_NONE
#घोषणा ARGI_ONES_OP                    ARG_NONE
#घोषणा ARGI_PACKAGE_OP                 ARGI_LIST1 (ARGI_INTEGER)
#घोषणा ARGI_POWER_RES_OP               ARGI_INVALID_OPCODE
#घोषणा ARGI_PROCESSOR_OP               ARGI_INVALID_OPCODE
#घोषणा ARGI_QWORD_OP                   ARGI_INVALID_OPCODE
#घोषणा ARGI_REF_OF_OP                  ARGI_LIST1 (ARGI_OBJECT_REF)
#घोषणा ARGI_REGION_OP                  ARGI_LIST2 (ARGI_INTEGER,    ARGI_INTEGER)
#घोषणा ARGI_RELEASE_OP                 ARGI_LIST1 (ARGI_MUTEX)
#घोषणा ARGI_RESERVEDFIELD_OP           ARGI_INVALID_OPCODE
#घोषणा ARGI_RESET_OP                   ARGI_LIST1 (ARGI_EVENT)
#घोषणा ARGI_RETURN_OP                  ARGI_INVALID_OPCODE
#घोषणा ARGI_REVISION_OP                ARG_NONE
#घोषणा ARGI_SCOPE_OP                   ARGI_INVALID_OPCODE
#घोषणा ARGI_SERIALFIELD_OP             ARGI_INVALID_OPCODE
#घोषणा ARGI_SHIFT_LEFT_OP              ARGI_LIST3 (ARGI_INTEGER,    ARGI_INTEGER,       ARGI_TARGETREF)
#घोषणा ARGI_SHIFT_RIGHT_OP             ARGI_LIST3 (ARGI_INTEGER,    ARGI_INTEGER,       ARGI_TARGETREF)
#घोषणा ARGI_SIGNAL_OP                  ARGI_LIST1 (ARGI_EVENT)
#घोषणा ARGI_SIZE_OF_OP                 ARGI_LIST1 (ARGI_DATAOBJECT)
#घोषणा ARGI_SLEEP_OP                   ARGI_LIST1 (ARGI_INTEGER)
#घोषणा ARGI_STALL_OP                   ARGI_LIST1 (ARGI_INTEGER)
#घोषणा ARGI_STATICSTRING_OP            ARGI_INVALID_OPCODE
#घोषणा ARGI_STORE_OP                   ARGI_LIST2 (ARGI_DATAREFOBJ, ARGI_STORE_TARGET)
#घोषणा ARGI_STRING_OP                  ARGI_INVALID_OPCODE
#घोषणा ARGI_SUBTRACT_OP                ARGI_LIST3 (ARGI_INTEGER,    ARGI_INTEGER,       ARGI_TARGETREF)
#घोषणा ARGI_THERMAL_ZONE_OP            ARGI_INVALID_OPCODE
#घोषणा ARGI_TIMER_OP                   ARG_NONE
#घोषणा ARGI_TO_BCD_OP                  ARGI_LIST2 (ARGI_INTEGER,    ARGI_FIXED_TARGET)
#घोषणा ARGI_TO_BUFFER_OP               ARGI_LIST2 (ARGI_COMPUTEDATA,ARGI_FIXED_TARGET)
#घोषणा ARGI_TO_DEC_STR_OP              ARGI_LIST2 (ARGI_COMPUTEDATA,ARGI_FIXED_TARGET)
#घोषणा ARGI_TO_HEX_STR_OP              ARGI_LIST2 (ARGI_COMPUTEDATA,ARGI_FIXED_TARGET)
#घोषणा ARGI_TO_INTEGER_OP              ARGI_LIST2 (ARGI_COMPUTEDATA,ARGI_FIXED_TARGET)
#घोषणा ARGI_TO_STRING_OP               ARGI_LIST3 (ARGI_BUFFER,     ARGI_INTEGER,       ARGI_FIXED_TARGET)
#घोषणा ARGI_UNLOAD_OP                  ARGI_LIST1 (ARGI_DDBHANDLE)
#घोषणा ARGI_VAR_PACKAGE_OP             ARGI_LIST1 (ARGI_INTEGER)
#घोषणा ARGI_WAIT_OP                    ARGI_LIST2 (ARGI_EVENT,      ARGI_INTEGER)
#घोषणा ARGI_WHILE_OP                   ARGI_INVALID_OPCODE
#घोषणा ARGI_WORD_OP                    ARGI_INVALID_OPCODE
#घोषणा ARGI_ZERO_OP                    ARG_NONE

#पूर्ण_अगर				/* __ACOPCODE_H__ */
