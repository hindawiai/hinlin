<शैली गुरु>
/* SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0 */
/******************************************************************************
 *
 * Name: acexcep.h - Exception codes वापसed by the ACPI subप्रणाली
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#अगर_अघोषित __ACEXCEP_H__
#घोषणा __ACEXCEP_H__

/* This module contains all possible exception codes क्रम acpi_status */

/*
 * Exception code classes
 */
#घोषणा AE_CODE_ENVIRONMENTAL           0x0000	/* General ACPICA environment */
#घोषणा AE_CODE_PROGRAMMER              0x1000	/* External ACPICA पूर्णांकerface caller */
#घोषणा AE_CODE_ACPI_TABLES             0x2000	/* ACPI tables */
#घोषणा AE_CODE_AML                     0x3000	/* From executing AML code */
#घोषणा AE_CODE_CONTROL                 0x4000	/* Internal control codes */

#घोषणा AE_CODE_MAX                     0x4000
#घोषणा AE_CODE_MASK                    0xF000

/*
 * Macros to insert the exception code classes
 */
#घोषणा EXCEP_ENV(code)                 ((acpi_status) (code | AE_CODE_ENVIRONMENTAL))
#घोषणा EXCEP_PGM(code)                 ((acpi_status) (code | AE_CODE_PROGRAMMER))
#घोषणा EXCEP_TBL(code)                 ((acpi_status) (code | AE_CODE_ACPI_TABLES))
#घोषणा EXCEP_AML(code)                 ((acpi_status) (code | AE_CODE_AML))
#घोषणा EXCEP_CTL(code)                 ((acpi_status) (code | AE_CODE_CONTROL))

/*
 * Exception info table. The "Description" field is used only by the
 * ACPICA help application (acpihelp).
 */
काष्ठा acpi_exception_info अणु
	अक्षर *name;

#अगर defined (ACPI_HELP_APP) || defined (ACPI_ASL_COMPILER)
	अक्षर *description;
#पूर्ण_अगर
पूर्ण;

#अगर defined (ACPI_HELP_APP) || defined (ACPI_ASL_COMPILER)
#घोषणा EXCEP_TXT(name,description)     अणुname, descriptionपूर्ण
#अन्यथा
#घोषणा EXCEP_TXT(name,description)     अणुnameपूर्ण
#पूर्ण_अगर

/*
 * Success is always zero, failure is non-zero
 */
#घोषणा ACPI_SUCCESS(a)                 (!(a))
#घोषणा ACPI_FAILURE(a)                 (a)

#घोषणा AE_OK                           (acpi_status) 0x0000

#घोषणा ACPI_ENV_EXCEPTION(status)      (((status) & AE_CODE_MASK) == AE_CODE_ENVIRONMENTAL)
#घोषणा ACPI_AML_EXCEPTION(status)      (((status) & AE_CODE_MASK) == AE_CODE_AML)
#घोषणा ACPI_PROG_EXCEPTION(status)     (((status) & AE_CODE_MASK) == AE_CODE_PROGRAMMER)
#घोषणा ACPI_TABLE_EXCEPTION(status)    (((status) & AE_CODE_MASK) == AE_CODE_ACPI_TABLES)
#घोषणा ACPI_CNTL_EXCEPTION(status)     (((status) & AE_CODE_MASK) == AE_CODE_CONTROL)

/*
 * Environmental exceptions
 */
#घोषणा AE_ERROR                        EXCEP_ENV (0x0001)
#घोषणा AE_NO_ACPI_TABLES               EXCEP_ENV (0x0002)
#घोषणा AE_NO_NAMESPACE                 EXCEP_ENV (0x0003)
#घोषणा AE_NO_MEMORY                    EXCEP_ENV (0x0004)
#घोषणा AE_NOT_FOUND                    EXCEP_ENV (0x0005)
#घोषणा AE_NOT_EXIST                    EXCEP_ENV (0x0006)
#घोषणा AE_ALREADY_EXISTS               EXCEP_ENV (0x0007)
#घोषणा AE_TYPE                         EXCEP_ENV (0x0008)
#घोषणा AE_शून्य_OBJECT                  EXCEP_ENV (0x0009)
#घोषणा AE_शून्य_ENTRY                   EXCEP_ENV (0x000A)
#घोषणा AE_BUFFER_OVERFLOW              EXCEP_ENV (0x000B)
#घोषणा AE_STACK_OVERFLOW               EXCEP_ENV (0x000C)
#घोषणा AE_STACK_UNDERFLOW              EXCEP_ENV (0x000D)
#घोषणा AE_NOT_IMPLEMENTED              EXCEP_ENV (0x000E)
#घोषणा AE_SUPPORT                      EXCEP_ENV (0x000F)
#घोषणा AE_LIMIT                        EXCEP_ENV (0x0010)
#घोषणा AE_TIME                         EXCEP_ENV (0x0011)
#घोषणा AE_ACQUIRE_DEADLOCK             EXCEP_ENV (0x0012)
#घोषणा AE_RELEASE_DEADLOCK             EXCEP_ENV (0x0013)
#घोषणा AE_NOT_ACQUIRED                 EXCEP_ENV (0x0014)
#घोषणा AE_ALREADY_ACQUIRED             EXCEP_ENV (0x0015)
#घोषणा AE_NO_HARDWARE_RESPONSE         EXCEP_ENV (0x0016)
#घोषणा AE_NO_GLOBAL_LOCK               EXCEP_ENV (0x0017)
#घोषणा AE_ABORT_METHOD                 EXCEP_ENV (0x0018)
#घोषणा AE_SAME_HANDLER                 EXCEP_ENV (0x0019)
#घोषणा AE_NO_HANDLER                   EXCEP_ENV (0x001A)
#घोषणा AE_OWNER_ID_LIMIT               EXCEP_ENV (0x001B)
#घोषणा AE_NOT_CONFIGURED               EXCEP_ENV (0x001C)
#घोषणा AE_ACCESS                       EXCEP_ENV (0x001D)
#घोषणा AE_IO_ERROR                     EXCEP_ENV (0x001E)
#घोषणा AE_NUMERIC_OVERFLOW             EXCEP_ENV (0x001F)
#घोषणा AE_HEX_OVERFLOW                 EXCEP_ENV (0x0020)
#घोषणा AE_DECIMAL_OVERFLOW             EXCEP_ENV (0x0021)
#घोषणा AE_OCTAL_OVERFLOW               EXCEP_ENV (0x0022)
#घोषणा AE_END_OF_TABLE                 EXCEP_ENV (0x0023)

#घोषणा AE_CODE_ENV_MAX                 0x0023

/*
 * Programmer exceptions
 */
#घोषणा AE_BAD_PARAMETER                EXCEP_PGM (0x0001)
#घोषणा AE_BAD_CHARACTER                EXCEP_PGM (0x0002)
#घोषणा AE_BAD_PATHNAME                 EXCEP_PGM (0x0003)
#घोषणा AE_BAD_DATA                     EXCEP_PGM (0x0004)
#घोषणा AE_BAD_HEX_CONSTANT             EXCEP_PGM (0x0005)
#घोषणा AE_BAD_OCTAL_CONSTANT           EXCEP_PGM (0x0006)
#घोषणा AE_BAD_DECIMAL_CONSTANT         EXCEP_PGM (0x0007)
#घोषणा AE_MISSING_ARGUMENTS            EXCEP_PGM (0x0008)
#घोषणा AE_BAD_ADDRESS                  EXCEP_PGM (0x0009)

#घोषणा AE_CODE_PGM_MAX                 0x0009

/*
 * Acpi table exceptions
 */
#घोषणा AE_BAD_SIGNATURE                EXCEP_TBL (0x0001)
#घोषणा AE_BAD_HEADER                   EXCEP_TBL (0x0002)
#घोषणा AE_BAD_CHECKSUM                 EXCEP_TBL (0x0003)
#घोषणा AE_BAD_VALUE                    EXCEP_TBL (0x0004)
#घोषणा AE_INVALID_TABLE_LENGTH         EXCEP_TBL (0x0005)

#घोषणा AE_CODE_TBL_MAX                 0x0005

/*
 * AML exceptions. These are caused by problems with
 * the actual AML byte stream
 */
#घोषणा AE_AML_BAD_OPCODE               EXCEP_AML (0x0001)
#घोषणा AE_AML_NO_OPERAND               EXCEP_AML (0x0002)
#घोषणा AE_AML_OPERAND_TYPE             EXCEP_AML (0x0003)
#घोषणा AE_AML_OPERAND_VALUE            EXCEP_AML (0x0004)
#घोषणा AE_AML_UNINITIALIZED_LOCAL      EXCEP_AML (0x0005)
#घोषणा AE_AML_UNINITIALIZED_ARG        EXCEP_AML (0x0006)
#घोषणा AE_AML_UNINITIALIZED_ELEMENT    EXCEP_AML (0x0007)
#घोषणा AE_AML_NUMERIC_OVERFLOW         EXCEP_AML (0x0008)
#घोषणा AE_AML_REGION_LIMIT             EXCEP_AML (0x0009)
#घोषणा AE_AML_BUFFER_LIMIT             EXCEP_AML (0x000A)
#घोषणा AE_AML_PACKAGE_LIMIT            EXCEP_AML (0x000B)
#घोषणा AE_AML_DIVIDE_BY_ZERO           EXCEP_AML (0x000C)
#घोषणा AE_AML_BAD_NAME                 EXCEP_AML (0x000D)
#घोषणा AE_AML_NAME_NOT_FOUND           EXCEP_AML (0x000E)
#घोषणा AE_AML_INTERNAL                 EXCEP_AML (0x000F)
#घोषणा AE_AML_INVALID_SPACE_ID         EXCEP_AML (0x0010)
#घोषणा AE_AML_STRING_LIMIT             EXCEP_AML (0x0011)
#घोषणा AE_AML_NO_RETURN_VALUE          EXCEP_AML (0x0012)
#घोषणा AE_AML_METHOD_LIMIT             EXCEP_AML (0x0013)
#घोषणा AE_AML_NOT_OWNER                EXCEP_AML (0x0014)
#घोषणा AE_AML_MUTEX_ORDER              EXCEP_AML (0x0015)
#घोषणा AE_AML_MUTEX_NOT_ACQUIRED       EXCEP_AML (0x0016)
#घोषणा AE_AML_INVALID_RESOURCE_TYPE    EXCEP_AML (0x0017)
#घोषणा AE_AML_INVALID_INDEX            EXCEP_AML (0x0018)
#घोषणा AE_AML_REGISTER_LIMIT           EXCEP_AML (0x0019)
#घोषणा AE_AML_NO_WHILE                 EXCEP_AML (0x001A)
#घोषणा AE_AML_ALIGNMENT                EXCEP_AML (0x001B)
#घोषणा AE_AML_NO_RESOURCE_END_TAG      EXCEP_AML (0x001C)
#घोषणा AE_AML_BAD_RESOURCE_VALUE       EXCEP_AML (0x001D)
#घोषणा AE_AML_CIRCULAR_REFERENCE       EXCEP_AML (0x001E)
#घोषणा AE_AML_BAD_RESOURCE_LENGTH      EXCEP_AML (0x001F)
#घोषणा AE_AML_ILLEGAL_ADDRESS          EXCEP_AML (0x0020)
#घोषणा AE_AML_LOOP_TIMEOUT             EXCEP_AML (0x0021)
#घोषणा AE_AML_UNINITIALIZED_NODE       EXCEP_AML (0x0022)
#घोषणा AE_AML_TARGET_TYPE              EXCEP_AML (0x0023)
#घोषणा AE_AML_PROTOCOL                 EXCEP_AML (0x0024)
#घोषणा AE_AML_BUFFER_LENGTH            EXCEP_AML (0x0025)

#घोषणा AE_CODE_AML_MAX                 0x0025

/*
 * Internal exceptions used क्रम control
 */
#घोषणा AE_CTRL_RETURN_VALUE            EXCEP_CTL (0x0001)
#घोषणा AE_CTRL_PENDING                 EXCEP_CTL (0x0002)
#घोषणा AE_CTRL_TERMINATE               EXCEP_CTL (0x0003)
#घोषणा AE_CTRL_TRUE                    EXCEP_CTL (0x0004)
#घोषणा AE_CTRL_FALSE                   EXCEP_CTL (0x0005)
#घोषणा AE_CTRL_DEPTH                   EXCEP_CTL (0x0006)
#घोषणा AE_CTRL_END                     EXCEP_CTL (0x0007)
#घोषणा AE_CTRL_TRANSFER                EXCEP_CTL (0x0008)
#घोषणा AE_CTRL_BREAK                   EXCEP_CTL (0x0009)
#घोषणा AE_CTRL_CONTINUE                EXCEP_CTL (0x000A)
#घोषणा AE_CTRL_PARSE_CONTINUE          EXCEP_CTL (0x000B)
#घोषणा AE_CTRL_PARSE_PENDING           EXCEP_CTL (0x000C)

#घोषणा AE_CODE_CTRL_MAX                0x000C

/* Exception strings क्रम acpi_क्रमmat_exception */

#अगर_घोषित ACPI_DEFINE_EXCEPTION_TABLE

/*
 * String versions of the exception codes above
 * These strings must match the corresponding defines exactly
 */
अटल स्थिर काष्ठा acpi_exception_info acpi_gbl_exception_names_env[] = अणु
	EXCEP_TXT("AE_OK", "No error"),
	EXCEP_TXT("AE_ERROR", "Unspecified error"),
	EXCEP_TXT("AE_NO_ACPI_TABLES", "ACPI tables could not be found"),
	EXCEP_TXT("AE_NO_NAMESPACE", "A namespace has not been loaded"),
	EXCEP_TXT("AE_NO_MEMORY", "Insufficient dynamic memory"),
	EXCEP_TXT("AE_NOT_FOUND", "A requested entity is not found"),
	EXCEP_TXT("AE_NOT_EXIST", "A required entity does not exist"),
	EXCEP_TXT("AE_ALREADY_EXISTS", "An entity already exists"),
	EXCEP_TXT("AE_TYPE", "The object type is incorrect"),
	EXCEP_TXT("AE_NULL_OBJECT", "A required object was missing"),
	EXCEP_TXT("AE_NULL_ENTRY", "The requested object does not exist"),
	EXCEP_TXT("AE_BUFFER_OVERFLOW", "The buffer provided is too small"),
	EXCEP_TXT("AE_STACK_OVERFLOW", "An internal stack overflowed"),
	EXCEP_TXT("AE_STACK_UNDERFLOW", "An internal stack underflowed"),
	EXCEP_TXT("AE_NOT_IMPLEMENTED", "The feature is not implemented"),
	EXCEP_TXT("AE_SUPPORT", "The feature is not supported"),
	EXCEP_TXT("AE_LIMIT", "A predefined limit was exceeded"),
	EXCEP_TXT("AE_TIME", "A time limit or timeout expired"),
	EXCEP_TXT("AE_ACQUIRE_DEADLOCK",
		  "Internal error, attempt was made to acquire a mutex in improper order"),
	EXCEP_TXT("AE_RELEASE_DEADLOCK",
		  "Internal error, attempt was made to release a mutex in improper order"),
	EXCEP_TXT("AE_NOT_ACQUIRED",
		  "An attempt to release a mutex or Global Lock without a previous acquire"),
	EXCEP_TXT("AE_ALREADY_ACQUIRED",
		  "Internal error, attempt was made to acquire a mutex twice"),
	EXCEP_TXT("AE_NO_HARDWARE_RESPONSE",
		  "Hardware did not respond after an I/O operation"),
	EXCEP_TXT("AE_NO_GLOBAL_LOCK", "There is no FACS Global Lock"),
	EXCEP_TXT("AE_ABORT_METHOD", "A control method was aborted"),
	EXCEP_TXT("AE_SAME_HANDLER",
		  "Attempt was made to install the same handler that is already installed"),
	EXCEP_TXT("AE_NO_HANDLER",
		  "A handler for the operation is not installed"),
	EXCEP_TXT("AE_OWNER_ID_LIMIT",
		  "There are no more Owner IDs available for ACPI tables or control methods"),
	EXCEP_TXT("AE_NOT_CONFIGURED",
		  "The interface is not part of the current subsystem configuration"),
	EXCEP_TXT("AE_ACCESS", "Permission denied for the requested operation"),
	EXCEP_TXT("AE_IO_ERROR", "An I/O error occurred"),
	EXCEP_TXT("AE_NUMERIC_OVERFLOW",
		  "Overflow during string-to-integer conversion"),
	EXCEP_TXT("AE_HEX_OVERFLOW",
		  "Overflow during ASCII hex-to-binary conversion"),
	EXCEP_TXT("AE_DECIMAL_OVERFLOW",
		  "Overflow during ASCII decimal-to-binary conversion"),
	EXCEP_TXT("AE_OCTAL_OVERFLOW",
		  "Overflow during ASCII octal-to-binary conversion"),
	EXCEP_TXT("AE_END_OF_TABLE", "Reached the end of table")
पूर्ण;

अटल स्थिर काष्ठा acpi_exception_info acpi_gbl_exception_names_pgm[] = अणु
	EXCEP_TXT(शून्य, शून्य),
	EXCEP_TXT("AE_BAD_PARAMETER", "A parameter is out of range or invalid"),
	EXCEP_TXT("AE_BAD_CHARACTER",
		  "An invalid character was found in a name"),
	EXCEP_TXT("AE_BAD_PATHNAME",
		  "An invalid character was found in a pathname"),
	EXCEP_TXT("AE_BAD_DATA",
		  "A package or buffer contained incorrect data"),
	EXCEP_TXT("AE_BAD_HEX_CONSTANT", "Invalid character in a Hex constant"),
	EXCEP_TXT("AE_BAD_OCTAL_CONSTANT",
		  "Invalid character in an Octal constant"),
	EXCEP_TXT("AE_BAD_DECIMAL_CONSTANT",
		  "Invalid character in a Decimal constant"),
	EXCEP_TXT("AE_MISSING_ARGUMENTS",
		  "Too few arguments were passed to a control method"),
	EXCEP_TXT("AE_BAD_ADDRESS", "An illegal null I/O address")
पूर्ण;

अटल स्थिर काष्ठा acpi_exception_info acpi_gbl_exception_names_tbl[] = अणु
	EXCEP_TXT(शून्य, शून्य),
	EXCEP_TXT("AE_BAD_SIGNATURE", "An ACPI table has an invalid signature"),
	EXCEP_TXT("AE_BAD_HEADER", "Invalid field in an ACPI table header"),
	EXCEP_TXT("AE_BAD_CHECKSUM", "An ACPI table checksum is not correct"),
	EXCEP_TXT("AE_BAD_VALUE", "An invalid value was found in a table"),
	EXCEP_TXT("AE_INVALID_TABLE_LENGTH",
		  "The FADT or FACS has improper length")
पूर्ण;

अटल स्थिर काष्ठा acpi_exception_info acpi_gbl_exception_names_aml[] = अणु
	EXCEP_TXT(शून्य, शून्य),
	EXCEP_TXT("AE_AML_BAD_OPCODE", "Invalid AML opcode encountered"),
	EXCEP_TXT("AE_AML_NO_OPERAND", "A required operand is missing"),
	EXCEP_TXT("AE_AML_OPERAND_TYPE",
		  "An operand of an incorrect type was encountered"),
	EXCEP_TXT("AE_AML_OPERAND_VALUE",
		  "The operand had an inappropriate or invalid value"),
	EXCEP_TXT("AE_AML_UNINITIALIZED_LOCAL",
		  "Method tried to use an uninitialized local variable"),
	EXCEP_TXT("AE_AML_UNINITIALIZED_ARG",
		  "Method tried to use an uninitialized argument"),
	EXCEP_TXT("AE_AML_UNINITIALIZED_ELEMENT",
		  "Method tried to use an empty package element"),
	EXCEP_TXT("AE_AML_NUMERIC_OVERFLOW",
		  "Overflow during BCD conversion or other"),
	EXCEP_TXT("AE_AML_REGION_LIMIT",
		  "Tried to access beyond the end of an Operation Region"),
	EXCEP_TXT("AE_AML_BUFFER_LIMIT",
		  "Tried to access beyond the end of a buffer"),
	EXCEP_TXT("AE_AML_PACKAGE_LIMIT",
		  "Tried to access beyond the end of a package"),
	EXCEP_TXT("AE_AML_DIVIDE_BY_ZERO",
		  "During execution of AML Divide operator"),
	EXCEP_TXT("AE_AML_BAD_NAME",
		  "An ACPI name contains invalid character(s)"),
	EXCEP_TXT("AE_AML_NAME_NOT_FOUND",
		  "Could not resolve a named reference"),
	EXCEP_TXT("AE_AML_INTERNAL",
		  "An internal error within the interpreter"),
	EXCEP_TXT("AE_AML_INVALID_SPACE_ID",
		  "An Operation Region SpaceID is invalid"),
	EXCEP_TXT("AE_AML_STRING_LIMIT",
		  "String is longer than 200 characters"),
	EXCEP_TXT("AE_AML_NO_RETURN_VALUE",
		  "A method did not return a required value"),
	EXCEP_TXT("AE_AML_METHOD_LIMIT",
		  "A control method reached the maximum reentrancy limit of 255"),
	EXCEP_TXT("AE_AML_NOT_OWNER",
		  "A thread tried to release a mutex that it does not own"),
	EXCEP_TXT("AE_AML_MUTEX_ORDER", "Mutex SyncLevel release mismatch"),
	EXCEP_TXT("AE_AML_MUTEX_NOT_ACQUIRED",
		  "Attempt to release a mutex that was not previously acquired"),
	EXCEP_TXT("AE_AML_INVALID_RESOURCE_TYPE",
		  "Invalid resource type in resource list"),
	EXCEP_TXT("AE_AML_INVALID_INDEX",
		  "Invalid Argx or Localx (x too large)"),
	EXCEP_TXT("AE_AML_REGISTER_LIMIT",
		  "Bank value or Index value beyond range of register"),
	EXCEP_TXT("AE_AML_NO_WHILE", "Break or Continue without a While"),
	EXCEP_TXT("AE_AML_ALIGNMENT",
		  "Non-aligned memory transfer on platform that does not support this"),
	EXCEP_TXT("AE_AML_NO_RESOURCE_END_TAG",
		  "No End Tag in a resource list"),
	EXCEP_TXT("AE_AML_BAD_RESOURCE_VALUE",
		  "Invalid value of a resource element"),
	EXCEP_TXT("AE_AML_CIRCULAR_REFERENCE",
		  "Two references refer to each other"),
	EXCEP_TXT("AE_AML_BAD_RESOURCE_LENGTH",
		  "The length of a Resource Descriptor in the AML is incorrect"),
	EXCEP_TXT("AE_AML_ILLEGAL_ADDRESS",
		  "A memory, I/O, or PCI configuration address is invalid"),
	EXCEP_TXT("AE_AML_LOOP_TIMEOUT",
		  "An AML While loop exceeded the maximum execution time"),
	EXCEP_TXT("AE_AML_UNINITIALIZED_NODE",
		  "A namespace node is uninitialized or unresolved"),
	EXCEP_TXT("AE_AML_TARGET_TYPE",
		  "A target operand of an incorrect type was encountered"),
	EXCEP_TXT("AE_AML_PROTOCOL", "Violation of a fixed ACPI protocol"),
	EXCEP_TXT("AE_AML_BUFFER_LENGTH",
		  "The length of the buffer is invalid/incorrect")
पूर्ण;

अटल स्थिर काष्ठा acpi_exception_info acpi_gbl_exception_names_ctrl[] = अणु
	EXCEP_TXT(शून्य, शून्य),
	EXCEP_TXT("AE_CTRL_RETURN_VALUE", "A Method returned a value"),
	EXCEP_TXT("AE_CTRL_PENDING", "Method is calling another method"),
	EXCEP_TXT("AE_CTRL_TERMINATE", "Terminate the executing method"),
	EXCEP_TXT("AE_CTRL_TRUE", "An If or While predicate result"),
	EXCEP_TXT("AE_CTRL_FALSE", "An If or While predicate result"),
	EXCEP_TXT("AE_CTRL_DEPTH", "Maximum search depth has been reached"),
	EXCEP_TXT("AE_CTRL_END", "An If or While predicate is false"),
	EXCEP_TXT("AE_CTRL_TRANSFER", "Transfer control to called method"),
	EXCEP_TXT("AE_CTRL_BREAK", "A Break has been executed"),
	EXCEP_TXT("AE_CTRL_CONTINUE", "A Continue has been executed"),
	EXCEP_TXT("AE_CTRL_PARSE_CONTINUE", "Used to skip over bad opcodes"),
	EXCEP_TXT("AE_CTRL_PARSE_PENDING", "Used to implement AML While loops")
पूर्ण;

#पूर्ण_अगर				/* EXCEPTION_TABLE */

#पूर्ण_अगर				/* __ACEXCEP_H__ */
