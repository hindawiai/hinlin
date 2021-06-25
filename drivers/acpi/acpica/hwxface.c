<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: hwxface - Public ACPICA hardware पूर्णांकerfaces
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#घोषणा EXPORT_ACPI_INTERFACES

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acnamesp.h"

#घोषणा _COMPONENT          ACPI_HARDWARE
ACPI_MODULE_NAME("hwxface")

/******************************************************************************
 *
 * FUNCTION:    acpi_reset
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Set reset रेजिस्टर in memory or IO space. Note: Does not
 *              support reset रेजिस्टर in PCI config space, this must be
 *              handled separately.
 *
 ******************************************************************************/
acpi_status acpi_reset(व्योम)
अणु
	काष्ठा acpi_generic_address *reset_reg;
	acpi_status status;

	ACPI_FUNCTION_TRACE(acpi_reset);

	reset_reg = &acpi_gbl_FADT.reset_रेजिस्टर;

	/* Check अगर the reset रेजिस्टर is supported */

	अगर (!(acpi_gbl_FADT.flags & ACPI_FADT_RESET_REGISTER) ||
	    !reset_reg->address) अणु
		वापस_ACPI_STATUS(AE_NOT_EXIST);
	पूर्ण

	अगर (reset_reg->space_id == ACPI_ADR_SPACE_SYSTEM_IO) अणु
		/*
		 * For I/O space, ग_लिखो directly to the OSL. This bypasses the port
		 * validation mechanism, which may block a valid ग_लिखो to the reset
		 * रेजिस्टर.
		 *
		 * NOTE:
		 * The ACPI spec requires the reset रेजिस्टर width to be 8, so we
		 * hardcode it here and ignore the FADT value. This मुख्यtains
		 * compatibility with other ACPI implementations that have allowed
		 * BIOS code with bad रेजिस्टर width values to go unnoticed.
		 */
		status = acpi_os_ग_लिखो_port((acpi_io_address)reset_reg->address,
					    acpi_gbl_FADT.reset_value,
					    ACPI_RESET_REGISTER_WIDTH);
	पूर्ण अन्यथा अणु
		/* Write the reset value to the reset रेजिस्टर */

		status = acpi_hw_ग_लिखो(acpi_gbl_FADT.reset_value, reset_reg);
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_reset)

/******************************************************************************
 *
 * FUNCTION:    acpi_पढ़ो
 *
 * PARAMETERS:  value               - Where the value is वापसed
 *              reg                 - GAS रेजिस्टर काष्ठाure
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Read from either memory or IO space.
 *
 * LIMITATIONS: <These limitations also apply to acpi_ग_लिखो>
 *      bit_width must be exactly 8, 16, 32, or 64.
 *      space_ID must be प्रणाली_memory or प्रणाली_IO.
 *      bit_offset and access_width are currently ignored, as there has
 *          not been a need to implement these.
 *
 ******************************************************************************/
acpi_status acpi_पढ़ो(u64 *वापस_value, काष्ठा acpi_generic_address *reg)
अणु
	acpi_status status;

	ACPI_FUNCTION_NAME(acpi_पढ़ो);

	status = acpi_hw_पढ़ो(वापस_value, reg);
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_पढ़ो)

/******************************************************************************
 *
 * FUNCTION:    acpi_ग_लिखो
 *
 * PARAMETERS:  value               - Value to be written
 *              reg                 - GAS रेजिस्टर काष्ठाure
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Write to either memory or IO space.
 *
 ******************************************************************************/
acpi_status acpi_ग_लिखो(u64 value, काष्ठा acpi_generic_address *reg)
अणु
	acpi_status status;

	ACPI_FUNCTION_NAME(acpi_ग_लिखो);

	status = acpi_hw_ग_लिखो(value, reg);
	वापस (status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_ग_लिखो)

#अगर (!ACPI_REDUCED_HARDWARE)
/*******************************************************************************
 *
 * FUNCTION:    acpi_पढ़ो_bit_रेजिस्टर
 *
 * PARAMETERS:  रेजिस्टर_id     - ID of ACPI Bit Register to access
 *              वापस_value    - Value that was पढ़ो from the रेजिस्टर,
 *                                normalized to bit position zero.
 *
 * RETURN:      Status and the value पढ़ो from the specअगरied Register. Value
 *              वापसed is normalized to bit0 (is shअगरted all the way right)
 *
 * DESCRIPTION: ACPI bit_रेजिस्टर पढ़ो function. Does not acquire the HW lock.
 *
 * SUPPORTS:    Bit fields in PM1 Status, PM1 Enable, PM1 Control, and
 *              PM2 Control.
 *
 * Note: The hardware lock is not required when पढ़ोing the ACPI bit रेजिस्टरs
 *       since almost all of them are single bit and it करोes not matter that
 *       the parent hardware रेजिस्टर can be split across two physical
 *       रेजिस्टरs. The only multi-bit field is SLP_TYP in the PM1 control
 *       रेजिस्टर, but this field करोes not cross an 8-bit boundary (nor करोes
 *       it make much sense to actually पढ़ो this field.)
 *
 ******************************************************************************/
acpi_status acpi_पढ़ो_bit_रेजिस्टर(u32 रेजिस्टर_id, u32 *वापस_value)
अणु
	काष्ठा acpi_bit_रेजिस्टर_info *bit_reg_info;
	u32 रेजिस्टर_value;
	u32 value;
	acpi_status status;

	ACPI_FUNCTION_TRACE_U32(acpi_पढ़ो_bit_रेजिस्टर, रेजिस्टर_id);

	/* Get the info काष्ठाure corresponding to the requested ACPI Register */

	bit_reg_info = acpi_hw_get_bit_रेजिस्टर_info(रेजिस्टर_id);
	अगर (!bit_reg_info) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Read the entire parent रेजिस्टर */

	status = acpi_hw_रेजिस्टर_पढ़ो(bit_reg_info->parent_रेजिस्टर,
				       &रेजिस्टर_value);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	/* Normalize the value that was पढ़ो, mask off other bits */

	value = ((रेजिस्टर_value & bit_reg_info->access_bit_mask)
		 >> bit_reg_info->bit_position);

	ACPI_DEBUG_PRINT((ACPI_DB_IO,
			  "BitReg %X, ParentReg %X, Actual %8.8X, ReturnValue %8.8X\n",
			  रेजिस्टर_id, bit_reg_info->parent_रेजिस्टर,
			  रेजिस्टर_value, value));

	*वापस_value = value;
	वापस_ACPI_STATUS(AE_OK);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_पढ़ो_bit_रेजिस्टर)

/*******************************************************************************
 *
 * FUNCTION:    acpi_ग_लिखो_bit_रेजिस्टर
 *
 * PARAMETERS:  रेजिस्टर_id     - ID of ACPI Bit Register to access
 *              value           - Value to ग_लिखो to the रेजिस्टर, in bit
 *                                position zero. The bit is स्वतःmatically
 *                                shअगरted to the correct position.
 *
 * RETURN:      Status
 *
 * DESCRIPTION: ACPI Bit Register ग_लिखो function. Acquires the hardware lock
 *              since most operations require a पढ़ो/modअगरy/ग_लिखो sequence.
 *
 * SUPPORTS:    Bit fields in PM1 Status, PM1 Enable, PM1 Control, and
 *              PM2 Control.
 *
 * Note that at this level, the fact that there may be actually two
 * hardware रेजिस्टरs (A and B - and B may not exist) is असलtracted.
 *
 ******************************************************************************/
acpi_status acpi_ग_लिखो_bit_रेजिस्टर(u32 रेजिस्टर_id, u32 value)
अणु
	काष्ठा acpi_bit_रेजिस्टर_info *bit_reg_info;
	acpi_cpu_flags lock_flags;
	u32 रेजिस्टर_value;
	acpi_status status = AE_OK;

	ACPI_FUNCTION_TRACE_U32(acpi_ग_लिखो_bit_रेजिस्टर, रेजिस्टर_id);

	/* Get the info काष्ठाure corresponding to the requested ACPI Register */

	bit_reg_info = acpi_hw_get_bit_रेजिस्टर_info(रेजिस्टर_id);
	अगर (!bit_reg_info) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	lock_flags = acpi_os_acquire_raw_lock(acpi_gbl_hardware_lock);

	/*
	 * At this poपूर्णांक, we know that the parent रेजिस्टर is one of the
	 * following: PM1 Status, PM1 Enable, PM1 Control, or PM2 Control
	 */
	अगर (bit_reg_info->parent_रेजिस्टर != ACPI_REGISTER_PM1_STATUS) अणु
		/*
		 * 1) Case क्रम PM1 Enable, PM1 Control, and PM2 Control
		 *
		 * Perक्रमm a रेजिस्टर पढ़ो to preserve the bits that we are not
		 * पूर्णांकerested in
		 */
		status = acpi_hw_रेजिस्टर_पढ़ो(bit_reg_info->parent_रेजिस्टर,
					       &रेजिस्टर_value);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ unlock_and_निकास;
		पूर्ण

		/*
		 * Insert the input bit पूर्णांकo the value that was just पढ़ो
		 * and ग_लिखो the रेजिस्टर
		 */
		ACPI_REGISTER_INSERT_VALUE(रेजिस्टर_value,
					   bit_reg_info->bit_position,
					   bit_reg_info->access_bit_mask,
					   value);

		status = acpi_hw_रेजिस्टर_ग_लिखो(bit_reg_info->parent_रेजिस्टर,
						रेजिस्टर_value);
	पूर्ण अन्यथा अणु
		/*
		 * 2) Case क्रम PM1 Status
		 *
		 * The Status रेजिस्टर is dअगरferent from the rest. Clear an event
		 * by writing 1, writing 0 has no effect. So, the only relevant
		 * inक्रमmation is the single bit we're पूर्णांकerested in, all others
		 * should be written as 0 so they will be left unchanged.
		 */
		रेजिस्टर_value = ACPI_REGISTER_PREPARE_BITS(value,
							    bit_reg_info->
							    bit_position,
							    bit_reg_info->
							    access_bit_mask);

		/* No need to ग_लिखो the रेजिस्टर अगर value is all zeros */

		अगर (रेजिस्टर_value) अणु
			status =
			    acpi_hw_रेजिस्टर_ग_लिखो(ACPI_REGISTER_PM1_STATUS,
						   रेजिस्टर_value);
		पूर्ण
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_IO,
			  "BitReg %X, ParentReg %X, Value %8.8X, Actual %8.8X\n",
			  रेजिस्टर_id, bit_reg_info->parent_रेजिस्टर, value,
			  रेजिस्टर_value));

unlock_and_निकास:

	acpi_os_release_raw_lock(acpi_gbl_hardware_lock, lock_flags);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_ग_लिखो_bit_रेजिस्टर)
#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
/*******************************************************************************
 *
 * FUNCTION:    acpi_get_sleep_type_data
 *
 * PARAMETERS:  sleep_state         - Numeric sleep state
 *              *sleep_type_a        - Where SLP_TYPa is वापसed
 *              *sleep_type_b        - Where SLP_TYPb is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Obtain the SLP_TYPa and SLP_TYPb values क्रम the requested
 *              sleep state via the appropriate \_Sx object.
 *
 *  The sleep state package वापसed from the corresponding \_Sx_ object
 *  must contain at least one पूर्णांकeger.
 *
 *  March 2005:
 *  Added support क्रम a package that contains two पूर्णांकegers. This
 *  goes against the ACPI specअगरication which defines this object as a
 *  package with one encoded DWORD पूर्णांकeger. However, existing practice
 *  by many BIOS venकरोrs is to वापस a package with 2 or more पूर्णांकeger
 *  elements, at least one per sleep type (A/B).
 *
 *  January 2013:
 *  Thereक्रमe, we must be prepared to accept a package with either a
 *  single पूर्णांकeger or multiple पूर्णांकegers.
 *
 *  The single पूर्णांकeger DWORD क्रमmat is as follows:
 *      BYTE 0 - Value क्रम the PM1A SLP_TYP रेजिस्टर
 *      BYTE 1 - Value क्रम the PM1B SLP_TYP रेजिस्टर
 *      BYTE 2-3 - Reserved
 *
 *  The dual पूर्णांकeger क्रमmat is as follows:
 *      Integer 0 - Value क्रम the PM1A SLP_TYP रेजिस्टर
 *      Integer 1 - Value क्रम the PM1A SLP_TYP रेजिस्टर
 *
 ******************************************************************************/
acpi_status
acpi_get_sleep_type_data(u8 sleep_state, u8 *sleep_type_a, u8 *sleep_type_b)
अणु
	acpi_status status;
	काष्ठा acpi_evaluate_info *info;
	जोड़ acpi_opeअक्रम_object **elements;

	ACPI_FUNCTION_TRACE(acpi_get_sleep_type_data);

	/* Validate parameters */

	अगर ((sleep_state > ACPI_S_STATES_MAX) || !sleep_type_a || !sleep_type_b) अणु
		वापस_ACPI_STATUS(AE_BAD_PARAMETER);
	पूर्ण

	/* Allocate the evaluation inक्रमmation block */

	info = ACPI_ALLOCATE_ZEROED(माप(काष्ठा acpi_evaluate_info));
	अगर (!info) अणु
		वापस_ACPI_STATUS(AE_NO_MEMORY);
	पूर्ण

	/*
	 * Evaluate the \_Sx namespace object containing the रेजिस्टर values
	 * क्रम this state
	 */
	info->relative_pathname = acpi_gbl_sleep_state_names[sleep_state];

	status = acpi_ns_evaluate(info);
	अगर (ACPI_FAILURE(status)) अणु
		अगर (status == AE_NOT_FOUND) अणु

			/* The _Sx states are optional, ignore NOT_FOUND */

			जाओ final_cleanup;
		पूर्ण

		जाओ warning_cleanup;
	पूर्ण

	/* Must have a वापस object */

	अगर (!info->वापस_object) अणु
		ACPI_ERROR((AE_INFO, "No Sleep State object returned from [%s]",
			    info->relative_pathname));
		status = AE_AML_NO_RETURN_VALUE;
		जाओ warning_cleanup;
	पूर्ण

	/* Return object must be of type Package */

	अगर (info->वापस_object->common.type != ACPI_TYPE_PACKAGE) अणु
		ACPI_ERROR((AE_INFO,
			    "Sleep State return object is not a Package"));
		status = AE_AML_OPERAND_TYPE;
		जाओ वापस_value_cleanup;
	पूर्ण

	/*
	 * Any warnings about the package length or the object types have
	 * alपढ़ोy been issued by the predefined name module -- there is no
	 * need to repeat them here.
	 */
	elements = info->वापस_object->package.elements;
	चयन (info->वापस_object->package.count) अणु
	हाल 0:

		status = AE_AML_PACKAGE_LIMIT;
		अवरोध;

	हाल 1:

		अगर (elements[0]->common.type != ACPI_TYPE_INTEGER) अणु
			status = AE_AML_OPERAND_TYPE;
			अवरोध;
		पूर्ण

		/* A valid _Sx_ package with one पूर्णांकeger */

		*sleep_type_a = (u8)elements[0]->पूर्णांकeger.value;
		*sleep_type_b = (u8)(elements[0]->पूर्णांकeger.value >> 8);
		अवरोध;

	हाल 2:
	शेष:

		अगर ((elements[0]->common.type != ACPI_TYPE_INTEGER) ||
		    (elements[1]->common.type != ACPI_TYPE_INTEGER)) अणु
			status = AE_AML_OPERAND_TYPE;
			अवरोध;
		पूर्ण

		/* A valid _Sx_ package with two पूर्णांकegers */

		*sleep_type_a = (u8)elements[0]->पूर्णांकeger.value;
		*sleep_type_b = (u8)elements[1]->पूर्णांकeger.value;
		अवरोध;
	पूर्ण

वापस_value_cleanup:
	acpi_ut_हटाओ_reference(info->वापस_object);

warning_cleanup:
	अगर (ACPI_FAILURE(status)) अणु
		ACPI_EXCEPTION((AE_INFO, status,
				"While evaluating Sleep State [%s]",
				info->relative_pathname));
	पूर्ण

final_cleanup:
	ACPI_FREE(info);
	वापस_ACPI_STATUS(status);
पूर्ण

ACPI_EXPORT_SYMBOL(acpi_get_sleep_type_data)
