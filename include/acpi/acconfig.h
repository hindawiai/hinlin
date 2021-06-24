<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acconfig.h - Global configuration स्थिरants
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित _ACCONFIG_H
#घोषणा _ACCONFIG_H

/******************************************************************************
 *
 * Configuration options
 *
 *****************************************************************************/

/*
 * ACPI_DEBUG_OUTPUT    - This चयन enables all the debug facilities of the
 *                        ACPI subप्रणाली.  This includes the DEBUG_PRINT output
 *                        statements.  When disabled, all DEBUG_PRINT
 *                        statements are compiled out.
 *
 * ACPI_APPLICATION     - Use this चयन अगर the subप्रणाली is going to be run
 *                        at the application level.
 *
 */

/*
 * OS name, used क्रम the _OS object.  The _OS object is essentially obsolete,
 * but there is a large base of ASL/AML code in existing machines that check
 * क्रम the string below.  The use of this string usually guarantees that
 * the ASL will execute करोwn the most tested code path.  Also, there is some
 * code that will not execute the _OSI method unless _OS matches the string
 * below.  Thereक्रमe, change this string at your own risk.
 */
#घोषणा ACPI_OS_NAME                    "Microsoft Windows NT"

/* Maximum objects in the various object caches */

#घोषणा ACPI_MAX_STATE_CACHE_DEPTH      96	/* State objects */
#घोषणा ACPI_MAX_PARSE_CACHE_DEPTH      96	/* Parse tree objects */
#घोषणा ACPI_MAX_EXTPARSE_CACHE_DEPTH   96	/* Parse tree objects */
#घोषणा ACPI_MAX_OBJECT_CACHE_DEPTH     96	/* Interpreter opeअक्रम objects */
#घोषणा ACPI_MAX_NAMESPACE_CACHE_DEPTH  96	/* Namespace objects */
#घोषणा ACPI_MAX_COMMENT_CACHE_DEPTH    96	/* Comments क्रम the -ca option */

/*
 * Should the subप्रणाली पात the loading of an ACPI table अगर the
 * table checksum is incorrect?
 */
#अगर_अघोषित ACPI_CHECKSUM_ABORT
#घोषणा ACPI_CHECKSUM_ABORT             FALSE
#पूर्ण_अगर

/*
 * Generate a version of ACPICA that only supports "reduced hardware"
 * platक्रमms (as defined in ACPI 5.0). Set to TRUE to generate a specialized
 * version of ACPICA that ONLY supports the ACPI 5.0 "reduced hardware"
 * model. In other words, no ACPI hardware is supported.
 *
 * If TRUE, this means no support क्रम the following:
 *      PM Event and Control रेजिस्टरs
 *      SCI पूर्णांकerrupt (and handler)
 *      Fixed Events
 *      General Purpose Events (GPEs)
 *      Global Lock
 *      ACPI PM समयr
 *      FACS table (Waking vectors and Global Lock)
 */
#अगर_अघोषित ACPI_REDUCED_HARDWARE
#घोषणा ACPI_REDUCED_HARDWARE           FALSE
#पूर्ण_अगर

/******************************************************************************
 *
 * Subप्रणाली Constants
 *
 *****************************************************************************/

/* Version of ACPI supported */

#घोषणा ACPI_CA_SUPPORT_LEVEL           5

/* Maximum count क्रम a semaphore object */

#घोषणा ACPI_MAX_SEMAPHORE_COUNT        256

/* Maximum object reference count (detects object deletion issues) */

#घोषणा ACPI_MAX_REFERENCE_COUNT        0x4000

/* Default page size क्रम use in mapping memory क्रम operation regions */

#घोषणा ACPI_DEFAULT_PAGE_SIZE          4096	/* Must be घातer of 2 */

/* owner_id tracking. 128 entries allows क्रम 4095 owner_ids */

#घोषणा ACPI_NUM_OWNERID_MASKS          128

/* Size of the root table array is increased by this increment */

#घोषणा ACPI_ROOT_TABLE_SIZE_INCREMENT  4

/* Maximum sleep allowed via Sleep() चालक */

#घोषणा ACPI_MAX_SLEEP                  2000	/* 2000 millisec == two seconds */

/* Address Range lists are per-space_id (Memory and I/O only) */

#घोषणा ACPI_ADDRESS_RANGE_MAX          2

/* Maximum समय (शेष 30s) of While() loops beक्रमe पात */

#घोषणा ACPI_MAX_LOOP_TIMEOUT           30

/******************************************************************************
 *
 * ACPI Specअगरication स्थिरants (Do not change unless the specअगरication changes)
 *
 *****************************************************************************/

/* Method info (in WALK_STATE), containing local variables and arguments */

#घोषणा ACPI_METHOD_NUM_LOCALS          8
#घोषणा ACPI_METHOD_MAX_LOCAL           7

#घोषणा ACPI_METHOD_NUM_ARGS            7
#घोषणा ACPI_METHOD_MAX_ARG             6

/*
 * Opeअक्रम Stack (in WALK_STATE), Must be large enough to contain METHOD_MAX_ARG
 */
#घोषणा ACPI_OBJ_NUM_OPERANDS           8
#घोषणा ACPI_OBJ_MAX_OPERAND            7

/* Number of elements in the Result Stack frame, can be an arbitrary value */

#घोषणा ACPI_RESULTS_FRAME_OBJ_NUM      8

/*
 * Maximal number of elements the Result Stack can contain,
 * it may be an arbitrary value not exceeding the types of
 * result_size and result_count (now u8).
 */
#घोषणा ACPI_RESULTS_OBJ_NUM_MAX        255

/* Constants used in searching क्रम the RSDP in low memory */

#घोषणा ACPI_EBDA_PTR_LOCATION          0x0000040E	/* Physical Address */
#घोषणा ACPI_EBDA_PTR_LENGTH            2
#घोषणा ACPI_EBDA_WINDOW_SIZE           1024
#घोषणा ACPI_HI_RSDP_WINDOW_BASE        0x000E0000	/* Physical Address */
#घोषणा ACPI_HI_RSDP_WINDOW_SIZE        0x00020000
#घोषणा ACPI_RSDP_SCAN_STEP             16

/* Operation regions */

#घोषणा ACPI_USER_REGION_BEGIN          0x80

/* Maximum space_ids क्रम Operation Regions */

#घोषणा ACPI_MAX_ADDRESS_SPACE          255
#घोषणा ACPI_NUM_DEFAULT_SPACES         4

/* Array sizes.  Used क्रम range checking also */

#घोषणा ACPI_MAX_MATCH_OPCODE           5

/* RSDP checksums */

#घोषणा ACPI_RSDP_CHECKSUM_LENGTH       20
#घोषणा ACPI_RSDP_XCHECKSUM_LENGTH      36

/*
 * SMBus, GSBus and IPMI buffer sizes. All have a 2-byte header,
 * containing both Status and Length.
 */
#घोषणा ACPI_SERIAL_HEADER_SIZE         2	/* Common क्रम below. Status and Length fields */

#घोषणा ACPI_SMBUS_DATA_SIZE            32
#घोषणा ACPI_SMBUS_BUFFER_SIZE          ACPI_SERIAL_HEADER_SIZE + ACPI_SMBUS_DATA_SIZE

#घोषणा ACPI_IPMI_DATA_SIZE             64
#घोषणा ACPI_IPMI_BUFFER_SIZE           ACPI_SERIAL_HEADER_SIZE + ACPI_IPMI_DATA_SIZE

#घोषणा ACPI_MAX_GSBUS_DATA_SIZE        255
#घोषणा ACPI_MAX_GSBUS_BUFFER_SIZE      ACPI_SERIAL_HEADER_SIZE + ACPI_MAX_GSBUS_DATA_SIZE

/* _sx_d and _sx_w control methods */

#घोषणा ACPI_NUM_sx_d_METHODS           4
#घोषणा ACPI_NUM_sx_w_METHODS           5

/******************************************************************************
 *
 * Miscellaneous स्थिरants
 *
 *****************************************************************************/

/* UUID स्थिरants */

#घोषणा UUID_BUFFER_LENGTH          16	/* Length of UUID in memory */
#घोषणा UUID_STRING_LENGTH          36	/* Total length of a UUID string */

/* Positions क्रम required hyphens (dashes) in UUID strings */

#घोषणा UUID_HYPHEN1_OFFSET         8
#घोषणा UUID_HYPHEN2_OFFSET         13
#घोषणा UUID_HYPHEN3_OFFSET         18
#घोषणा UUID_HYPHEN4_OFFSET         23

/******************************************************************************
 *
 * ACPI AML Debugger
 *
 *****************************************************************************/

#घोषणा ACPI_DEBUGGER_MAX_ARGS          ACPI_METHOD_NUM_ARGS + 4	/* Max command line arguments */
#घोषणा ACPI_DB_LINE_BUFFER_SIZE        512

#घोषणा ACPI_DEBUGGER_COMMAND_PROMPT    '-'
#घोषणा ACPI_DEBUGGER_EXECUTE_PROMPT    '%'

#पूर्ण_अगर				/* _ACCONFIG_H */
