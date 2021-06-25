<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: exutils - पूर्णांकerpreter/scanner utilities
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

/*
 * DEFINE_AML_GLOBALS is tested in amlcode.h
 * to determine whether certain global names should be "defined" or only
 * "declared" in the current compilation. This enhances मुख्यtainability
 * by enabling a single header file to embody all knowledge of the names
 * in question.
 *
 * Exactly one module of any executable should #घोषणा DEFINE_GLOBALS
 * beक्रमe #including the header files which use this convention. The
 * names in question will be defined and initialized in that module,
 * and declared as बाह्य in all other modules which #समावेश those
 * header files.
 */

#घोषणा DEFINE_AML_GLOBALS

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acinterp.h"
#समावेश "amlcode.h"

#घोषणा _COMPONENT          ACPI_EXECUTER
ACPI_MODULE_NAME("exutils")

/* Local prototypes */
अटल u32 acpi_ex_digits_needed(u64 value, u32 base);

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_enter_पूर्णांकerpreter
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Enter the पूर्णांकerpreter execution region. Failure to enter
 *              the पूर्णांकerpreter region is a fatal प्रणाली error. Used in
 *              conjunction with निकास_पूर्णांकerpreter.
 *
 ******************************************************************************/

व्योम acpi_ex_enter_पूर्णांकerpreter(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ex_enter_पूर्णांकerpreter);

	status = acpi_ut_acquire_mutex(ACPI_MTX_INTERPRETER);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_ERROR((AE_INFO,
			    "Could not acquire AML Interpreter mutex"));
	पूर्ण
	status = acpi_ut_acquire_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_ERROR((AE_INFO, "Could not acquire AML Namespace mutex"));
	पूर्ण

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_निकास_पूर्णांकerpreter
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Exit the पूर्णांकerpreter execution region. This is the top level
 *              routine used to निकास the पूर्णांकerpreter when all processing has
 *              been completed, or when the method blocks.
 *
 * Cases where the पूर्णांकerpreter is unlocked पूर्णांकernally:
 *      1) Method will be blocked on a Sleep() AML opcode
 *      2) Method will be blocked on an Acquire() AML opcode
 *      3) Method will be blocked on a Wait() AML opcode
 *      4) Method will be blocked to acquire the global lock
 *      5) Method will be blocked रुकोing to execute a serialized control
 *          method that is currently executing
 *      6) About to invoke a user-installed opregion handler
 *
 ******************************************************************************/

व्योम acpi_ex_निकास_पूर्णांकerpreter(व्योम)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ex_निकास_पूर्णांकerpreter);

	status = acpi_ut_release_mutex(ACPI_MTX_NAMESPACE);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_ERROR((AE_INFO, "Could not release AML Namespace mutex"));
	पूर्ण
	status = acpi_ut_release_mutex(ACPI_MTX_INTERPRETER);
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_ERROR((AE_INFO,
			    "Could not release AML Interpreter mutex"));
	पूर्ण

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_truncate_क्रम32bit_table
 *
 * PARAMETERS:  obj_desc        - Object to be truncated
 *
 * RETURN:      TRUE अगर a truncation was perक्रमmed, FALSE otherwise.
 *
 * DESCRIPTION: Truncate an ACPI Integer to 32 bits अगर the execution mode is
 *              32-bit, as determined by the revision of the DSDT.
 *
 ******************************************************************************/

u8 acpi_ex_truncate_क्रम32bit_table(जोड़ acpi_opeअक्रम_object *obj_desc)
अणु

	ACPI_FUNCTION_ENTRY();

	/*
	 * Object must be a valid number and we must be executing
	 * a control method. Object could be NS node क्रम AML_INT_NAMEPATH_OP.
	 */
	अगर ((!obj_desc) ||
	    (ACPI_GET_DESCRIPTOR_TYPE(obj_desc) != ACPI_DESC_TYPE_OPERAND) ||
	    (obj_desc->common.type != ACPI_TYPE_INTEGER)) अणु
		वापस (FALSE);
	पूर्ण

	अगर ((acpi_gbl_पूर्णांकeger_byte_width == 4) &&
	    (obj_desc->पूर्णांकeger.value > (u64)ACPI_UINT32_MAX)) अणु
		/*
		 * We are executing in a 32-bit ACPI table. Truncate
		 * the value to 32 bits by zeroing out the upper 32-bit field
		 */
		obj_desc->पूर्णांकeger.value &= (u64)ACPI_UINT32_MAX;
		वापस (TRUE);
	पूर्ण

	वापस (FALSE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_acquire_global_lock
 *
 * PARAMETERS:  field_flags           - Flags with Lock rule:
 *                                      always_lock or never_lock
 *
 * RETURN:      None
 *
 * DESCRIPTION: Obtain the ACPI hardware Global Lock, only अगर the field
 *              flags specअगरy that it is to be obtained beक्रमe field access.
 *
 ******************************************************************************/

व्योम acpi_ex_acquire_global_lock(u32 field_flags)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ex_acquire_global_lock);

	/* Only use the lock अगर the always_lock bit is set */

	अगर (!(field_flags & AML_FIELD_LOCK_RULE_MASK)) अणु
		वापस_VOID;
	पूर्ण

	/* Attempt to get the global lock, रुको क्रमever */

	status = acpi_ex_acquire_mutex_object(ACPI_WAIT_FOREVER,
					      acpi_gbl_global_lock_mutex,
					      acpi_os_get_thपढ़ो_id());

	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"Could not acquire Global Lock"));
	पूर्ण

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_release_global_lock
 *
 * PARAMETERS:  field_flags           - Flags with Lock rule:
 *                                      always_lock or never_lock
 *
 * RETURN:      None
 *
 * DESCRIPTION: Release the ACPI hardware Global Lock
 *
 ******************************************************************************/

व्योम acpi_ex_release_global_lock(u32 field_flags)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(ex_release_global_lock);

	/* Only use the lock अगर the always_lock bit is set */

	अगर (!(field_flags & AML_FIELD_LOCK_RULE_MASK)) अणु
		वापस_VOID;
	पूर्ण

	/* Release the global lock */

	status = acpi_ex_release_mutex_object(acpi_gbl_global_lock_mutex);
	अगर (ACPI_FAILURE(status)) अणु

		/* Report the error, but there isn't much अन्यथा we can करो */

		ACPI_EXCEPTION((AE_INFO, status,
				"Could not release Global Lock"));
	पूर्ण

	वापस_VOID;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_digits_needed
 *
 * PARAMETERS:  value           - Value to be represented
 *              base            - Base of representation
 *
 * RETURN:      The number of digits.
 *
 * DESCRIPTION: Calculate the number of digits needed to represent the Value
 *              in the given Base (Radix)
 *
 ******************************************************************************/

अटल u32 acpi_ex_digits_needed(u64 value, u32 base)
अणु
	u32 num_digits;
	u64 current_value;

	ACPI_FUNCTION_TRACE(ex_digits_needed);

	/* u64 is अचिन्हित, so we करोn't worry about a '-' prefix */

	अगर (value == 0) अणु
		वापस_UINT32(1);
	पूर्ण

	current_value = value;
	num_digits = 0;

	/* Count the digits in the requested base */

	जबतक (current_value) अणु
		(व्योम)acpi_ut_लघु_भागide(current_value, base, &current_value,
					   शून्य);
		num_digits++;
	पूर्ण

	वापस_UINT32(num_digits);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_eisa_id_to_string
 *
 * PARAMETERS:  out_string      - Where to put the converted string (8 bytes)
 *              compressed_id   - EISAID to be converted
 *
 * RETURN:      None
 *
 * DESCRIPTION: Convert a numeric EISAID to string representation. Return
 *              buffer must be large enough to hold the string. The string
 *              वापसed is always exactly of length ACPI_EISAID_STRING_SIZE
 *              (includes null terminator). The EISAID is always 32 bits.
 *
 ******************************************************************************/

व्योम acpi_ex_eisa_id_to_string(अक्षर *out_string, u64 compressed_id)
अणु
	u32 swapped_id;

	ACPI_FUNCTION_ENTRY();

	/* The EISAID should be a 32-bit पूर्णांकeger */

	अगर (compressed_id > ACPI_UINT32_MAX) अणु
		ACPI_WARNING((AE_INFO,
			      "Expected EISAID is larger than 32 bits: "
			      "0x%8.8X%8.8X, truncating",
			      ACPI_FORMAT_UINT64(compressed_id)));
	पूर्ण

	/* Swap ID to big-endian to get contiguous bits */

	swapped_id = acpi_ut_dword_byte_swap((u32)compressed_id);

	/* First 3 bytes are upperहाल letters. Next 4 bytes are hexadecimal */

	out_string[0] =
	    (अक्षर)(0x40 + (((अचिन्हित दीर्घ)swapped_id >> 26) & 0x1F));
	out_string[1] = (अक्षर)(0x40 + ((swapped_id >> 21) & 0x1F));
	out_string[2] = (अक्षर)(0x40 + ((swapped_id >> 16) & 0x1F));
	out_string[3] = acpi_ut_hex_to_ascii_अक्षर((u64) swapped_id, 12);
	out_string[4] = acpi_ut_hex_to_ascii_अक्षर((u64) swapped_id, 8);
	out_string[5] = acpi_ut_hex_to_ascii_अक्षर((u64) swapped_id, 4);
	out_string[6] = acpi_ut_hex_to_ascii_अक्षर((u64) swapped_id, 0);
	out_string[7] = 0;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_पूर्णांकeger_to_string
 *
 * PARAMETERS:  out_string      - Where to put the converted string. At least
 *                                21 bytes are needed to hold the largest
 *                                possible 64-bit पूर्णांकeger.
 *              value           - Value to be converted
 *
 * RETURN:      Converted string in out_string
 *
 * DESCRIPTION: Convert a 64-bit पूर्णांकeger to decimal string representation.
 *              Assumes string buffer is large enough to hold the string. The
 *              largest string is (ACPI_MAX64_DECIMAL_DIGITS + 1).
 *
 ******************************************************************************/

व्योम acpi_ex_पूर्णांकeger_to_string(अक्षर *out_string, u64 value)
अणु
	u32 count;
	u32 digits_needed;
	u32 reमुख्यder;

	ACPI_FUNCTION_ENTRY();

	digits_needed = acpi_ex_digits_needed(value, 10);
	out_string[digits_needed] = 0;

	क्रम (count = digits_needed; count > 0; count--) अणु
		(व्योम)acpi_ut_लघु_भागide(value, 10, &value, &reमुख्यder);
		out_string[count - 1] = (अक्षर)('0' + reमुख्यder);
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_ex_pci_cls_to_string
 *
 * PARAMETERS:  out_string      - Where to put the converted string (7 bytes)
 *              class_code      - PCI class code to be converted (3 bytes)
 *
 * RETURN:      Converted string in out_string
 *
 * DESCRIPTION: Convert 3-bytes PCI class code to string representation.
 *              Return buffer must be large enough to hold the string. The
 *              string वापसed is always exactly of length
 *              ACPI_PCICLS_STRING_SIZE (includes null terminator).
 *
 ******************************************************************************/

व्योम acpi_ex_pci_cls_to_string(अक्षर *out_string, u8 class_code[3])
अणु

	ACPI_FUNCTION_ENTRY();

	/* All 3 bytes are hexadecimal */

	out_string[0] = acpi_ut_hex_to_ascii_अक्षर((u64)class_code[0], 4);
	out_string[1] = acpi_ut_hex_to_ascii_अक्षर((u64)class_code[0], 0);
	out_string[2] = acpi_ut_hex_to_ascii_अक्षर((u64)class_code[1], 4);
	out_string[3] = acpi_ut_hex_to_ascii_अक्षर((u64)class_code[1], 0);
	out_string[4] = acpi_ut_hex_to_ascii_अक्षर((u64)class_code[2], 4);
	out_string[5] = acpi_ut_hex_to_ascii_अक्षर((u64)class_code[2], 0);
	out_string[6] = 0;
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_is_valid_space_id
 *
 * PARAMETERS:  space_id            - ID to be validated
 *
 * RETURN:      TRUE अगर space_id is a valid/supported ID.
 *
 * DESCRIPTION: Validate an operation region space_ID.
 *
 ******************************************************************************/

u8 acpi_is_valid_space_id(u8 space_id)
अणु

	अगर ((space_id >= ACPI_NUM_PREDEFINED_REGIONS) &&
	    (space_id < ACPI_USER_REGION_BEGIN) &&
	    (space_id != ACPI_ADR_SPACE_DATA_TABLE) &&
	    (space_id != ACPI_ADR_SPACE_FIXED_HARDWARE)) अणु
		वापस (FALSE);
	पूर्ण

	वापस (TRUE);
पूर्ण
