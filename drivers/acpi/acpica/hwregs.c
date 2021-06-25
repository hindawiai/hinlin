<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: hwregs - Read/ग_लिखो access functions क्रम the various ACPI
 *                       control and status रेजिस्टरs.
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acevents.h"

#घोषणा _COMPONENT          ACPI_HARDWARE
ACPI_MODULE_NAME("hwregs")

#अगर (!ACPI_REDUCED_HARDWARE)
/* Local Prototypes */
अटल u8
acpi_hw_get_access_bit_width(u64 address,
			     काष्ठा acpi_generic_address *reg,
			     u8 max_bit_width);

अटल acpi_status
acpi_hw_पढ़ो_multiple(u32 *value,
		      काष्ठा acpi_generic_address *रेजिस्टर_a,
		      काष्ठा acpi_generic_address *रेजिस्टर_b);

अटल acpi_status
acpi_hw_ग_लिखो_multiple(u32 value,
		       काष्ठा acpi_generic_address *रेजिस्टर_a,
		       काष्ठा acpi_generic_address *रेजिस्टर_b);

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_get_access_bit_width
 *
 * PARAMETERS:  address             - GAS रेजिस्टर address
 *              reg                 - GAS रेजिस्टर काष्ठाure
 *              max_bit_width       - Max bit_width supported (32 or 64)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Obtain optimal access bit width
 *
 ******************************************************************************/

अटल u8
acpi_hw_get_access_bit_width(u64 address,
			     काष्ठा acpi_generic_address *reg, u8 max_bit_width)
अणु
	u8 access_bit_width;

	/*
	 * GAS क्रमmat "register", used by FADT:
	 *  1. Detected अगर bit_offset is 0 and bit_width is 8/16/32/64;
	 *  2. access_size field is ignored and bit_width field is used क्रम
	 *     determining the boundary of the IO accesses.
	 * GAS क्रमmat "region", used by APEI रेजिस्टरs:
	 *  1. Detected अगर bit_offset is not 0 or bit_width is not 8/16/32/64;
	 *  2. access_size field is used क्रम determining the boundary of the
	 *     IO accesses;
	 *  3. bit_offset/bit_width fields are used to describe the "region".
	 *
	 * Note: This algorithm assumes that the "Address" fields should always
	 *       contain aligned values.
	 */
	अगर (!reg->bit_offset && reg->bit_width &&
	    ACPI_IS_POWER_OF_TWO(reg->bit_width) &&
	    ACPI_IS_ALIGNED(reg->bit_width, 8)) अणु
		access_bit_width = reg->bit_width;
	पूर्ण अन्यथा अगर (reg->access_width) अणु
		access_bit_width = ACPI_ACCESS_BIT_WIDTH(reg->access_width);
	पूर्ण अन्यथा अणु
		access_bit_width =
		    ACPI_ROUND_UP_POWER_OF_TWO_8(reg->bit_offset +
						 reg->bit_width);
		अगर (access_bit_width <= 8) अणु
			access_bit_width = 8;
		पूर्ण अन्यथा अणु
			जबतक (!ACPI_IS_ALIGNED(address, access_bit_width >> 3)) अणु
				access_bit_width >>= 1;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Maximum IO port access bit width is 32 */

	अगर (reg->space_id == ACPI_ADR_SPACE_SYSTEM_IO) अणु
		max_bit_width = 32;
	पूर्ण

	/*
	 * Return access width according to the requested maximum access bit width,
	 * as the caller should know the क्रमmat of the रेजिस्टर and may enक्रमce
	 * a 32-bit accesses.
	 */
	अगर (access_bit_width < max_bit_width) अणु
		वापस (access_bit_width);
	पूर्ण
	वापस (max_bit_width);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_validate_रेजिस्टर
 *
 * PARAMETERS:  reg                 - GAS रेजिस्टर काष्ठाure
 *              max_bit_width       - Max bit_width supported (32 or 64)
 *              address             - Poपूर्णांकer to where the gas->address
 *                                    is वापसed
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Validate the contents of a GAS रेजिस्टर. Checks the GAS
 *              poपूर्णांकer, Address, space_id, bit_width, and bit_offset.
 *
 ******************************************************************************/

acpi_status
acpi_hw_validate_रेजिस्टर(काष्ठा acpi_generic_address *reg,
			  u8 max_bit_width, u64 *address)
अणु
	u8 bit_width;
	u8 access_width;

	/* Must have a valid poपूर्णांकer to a GAS काष्ठाure */

	अगर (!reg) अणु
		वापस (AE_BAD_PARAMETER);
	पूर्ण

	/*
	 * Copy the target address. This handles possible alignment issues.
	 * Address must not be null. A null address also indicates an optional
	 * ACPI रेजिस्टर that is not supported, so no error message.
	 */
	ACPI_MOVE_64_TO_64(address, &reg->address);
	अगर (!(*address)) अणु
		वापस (AE_BAD_ADDRESS);
	पूर्ण

	/* Validate the space_ID */

	अगर ((reg->space_id != ACPI_ADR_SPACE_SYSTEM_MEMORY) &&
	    (reg->space_id != ACPI_ADR_SPACE_SYSTEM_IO)) अणु
		ACPI_ERROR((AE_INFO,
			    "Unsupported address space: 0x%X", reg->space_id));
		वापस (AE_SUPPORT);
	पूर्ण

	/* Validate the access_width */

	अगर (reg->access_width > 4) अणु
		ACPI_ERROR((AE_INFO,
			    "Unsupported register access width: 0x%X",
			    reg->access_width));
		वापस (AE_SUPPORT);
	पूर्ण

	/* Validate the bit_width, convert access_width पूर्णांकo number of bits */

	access_width =
	    acpi_hw_get_access_bit_width(*address, reg, max_bit_width);
	bit_width =
	    ACPI_ROUND_UP(reg->bit_offset + reg->bit_width, access_width);
	अगर (max_bit_width < bit_width) अणु
		ACPI_WARNING((AE_INFO,
			      "Requested bit width 0x%X is smaller than register bit width 0x%X",
			      max_bit_width, bit_width));
		वापस (AE_SUPPORT);
	पूर्ण

	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_पढ़ो
 *
 * PARAMETERS:  value               - Where the value is वापसed
 *              reg                 - GAS रेजिस्टर काष्ठाure
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Read from either memory or IO space. This is a 64-bit max
 *              version of acpi_पढ़ो.
 *
 * LIMITATIONS: <These limitations also apply to acpi_hw_ग_लिखो>
 *      space_ID must be प्रणाली_memory or प्रणाली_IO.
 *
 ******************************************************************************/

acpi_status acpi_hw_पढ़ो(u64 *value, काष्ठा acpi_generic_address *reg)
अणु
	u64 address;
	u8 access_width;
	u32 bit_width;
	u8 bit_offset;
	u64 value64;
	u32 value32;
	u8 index;
	acpi_status status;

	ACPI_FUNCTION_NAME(hw_पढ़ो);

	/* Validate contents of the GAS रेजिस्टर */

	status = acpi_hw_validate_रेजिस्टर(reg, 64, &address);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/*
	 * Initialize entire 64-bit वापस value to zero, convert access_width
	 * पूर्णांकo number of bits based
	 */
	*value = 0;
	access_width = acpi_hw_get_access_bit_width(address, reg, 64);
	bit_width = reg->bit_offset + reg->bit_width;
	bit_offset = reg->bit_offset;

	/*
	 * Two address spaces supported: Memory or IO. PCI_Config is
	 * not supported here because the GAS काष्ठाure is insufficient
	 */
	index = 0;
	जबतक (bit_width) अणु
		अगर (bit_offset >= access_width) अणु
			value64 = 0;
			bit_offset -= access_width;
		पूर्ण अन्यथा अणु
			अगर (reg->space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY) अणु
				status =
				    acpi_os_पढ़ो_memory((acpi_physical_address)
							address +
							index *
							ACPI_DIV_8
							(access_width),
							&value64, access_width);
			पूर्ण अन्यथा अणु	/* ACPI_ADR_SPACE_SYSTEM_IO, validated earlier */

				status = acpi_hw_पढ़ो_port((acpi_io_address)
							   address +
							   index *
							   ACPI_DIV_8
							   (access_width),
							   &value32,
							   access_width);
				value64 = (u64)value32;
			पूर्ण
		पूर्ण

		/*
		 * Use offset style bit ग_लिखोs because "Index * AccessWidth" is
		 * ensured to be less than 64-bits by acpi_hw_validate_रेजिस्टर().
		 */
		ACPI_SET_BITS(value, index * access_width,
			      ACPI_MASK_BITS_ABOVE_64(access_width), value64);

		bit_width -=
		    bit_width > access_width ? access_width : bit_width;
		index++;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_IO,
			  "Read:  %8.8X%8.8X width %2d from %8.8X%8.8X (%s)\n",
			  ACPI_FORMAT_UINT64(*value), access_width,
			  ACPI_FORMAT_UINT64(address),
			  acpi_ut_get_region_name(reg->space_id)));

	वापस (status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_ग_लिखो
 *
 * PARAMETERS:  value               - Value to be written
 *              reg                 - GAS रेजिस्टर काष्ठाure
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Write to either memory or IO space. This is a 64-bit max
 *              version of acpi_ग_लिखो.
 *
 ******************************************************************************/

acpi_status acpi_hw_ग_लिखो(u64 value, काष्ठा acpi_generic_address *reg)
अणु
	u64 address;
	u8 access_width;
	u32 bit_width;
	u8 bit_offset;
	u64 value64;
	u8 index;
	acpi_status status;

	ACPI_FUNCTION_NAME(hw_ग_लिखो);

	/* Validate contents of the GAS रेजिस्टर */

	status = acpi_hw_validate_रेजिस्टर(reg, 64, &address);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/* Convert access_width पूर्णांकo number of bits based */

	access_width = acpi_hw_get_access_bit_width(address, reg, 64);
	bit_width = reg->bit_offset + reg->bit_width;
	bit_offset = reg->bit_offset;

	/*
	 * Two address spaces supported: Memory or IO. PCI_Config is
	 * not supported here because the GAS काष्ठाure is insufficient
	 */
	index = 0;
	जबतक (bit_width) अणु
		/*
		 * Use offset style bit पढ़ोs because "Index * AccessWidth" is
		 * ensured to be less than 64-bits by acpi_hw_validate_रेजिस्टर().
		 */
		value64 = ACPI_GET_BITS(&value, index * access_width,
					ACPI_MASK_BITS_ABOVE_64(access_width));

		अगर (bit_offset >= access_width) अणु
			bit_offset -= access_width;
		पूर्ण अन्यथा अणु
			अगर (reg->space_id == ACPI_ADR_SPACE_SYSTEM_MEMORY) अणु
				status =
				    acpi_os_ग_लिखो_memory((acpi_physical_address)
							 address +
							 index *
							 ACPI_DIV_8
							 (access_width),
							 value64, access_width);
			पूर्ण अन्यथा अणु	/* ACPI_ADR_SPACE_SYSTEM_IO, validated earlier */

				status = acpi_hw_ग_लिखो_port((acpi_io_address)
							    address +
							    index *
							    ACPI_DIV_8
							    (access_width),
							    (u32)value64,
							    access_width);
			पूर्ण
		पूर्ण

		/*
		 * Index * access_width is ensured to be less than 32-bits by
		 * acpi_hw_validate_रेजिस्टर().
		 */
		bit_width -=
		    bit_width > access_width ? access_width : bit_width;
		index++;
	पूर्ण

	ACPI_DEBUG_PRINT((ACPI_DB_IO,
			  "Wrote: %8.8X%8.8X width %2d   to %8.8X%8.8X (%s)\n",
			  ACPI_FORMAT_UINT64(value), access_width,
			  ACPI_FORMAT_UINT64(address),
			  acpi_ut_get_region_name(reg->space_id)));

	वापस (status);
पूर्ण

#अगर (!ACPI_REDUCED_HARDWARE)
/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_clear_acpi_status
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Clears all fixed and general purpose status bits
 *
 ******************************************************************************/

acpi_status acpi_hw_clear_acpi_status(व्योम)
अणु
	acpi_status status;
	acpi_cpu_flags lock_flags = 0;

	ACPI_FUNCTION_TRACE(hw_clear_acpi_status);

	ACPI_DEBUG_PRINT((ACPI_DB_IO, "About to write %04X to %8.8X%8.8X\n",
			  ACPI_BITMASK_ALL_FIXED_STATUS,
			  ACPI_FORMAT_UINT64(acpi_gbl_xpm1a_status.address)));

	lock_flags = acpi_os_acquire_raw_lock(acpi_gbl_hardware_lock);

	/* Clear the fixed events in PM1 A/B */

	status = acpi_hw_रेजिस्टर_ग_लिखो(ACPI_REGISTER_PM1_STATUS,
					ACPI_BITMASK_ALL_FIXED_STATUS);

	acpi_os_release_raw_lock(acpi_gbl_hardware_lock, lock_flags);

	अगर (ACPI_FAILURE(status)) अणु
		जाओ निकास;
	पूर्ण

	/* Clear the GPE Bits in all GPE रेजिस्टरs in all GPE blocks */

	status = acpi_ev_walk_gpe_list(acpi_hw_clear_gpe_block, शून्य);

निकास:
	वापस_ACPI_STATUS(status);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_hw_get_bit_रेजिस्टर_info
 *
 * PARAMETERS:  रेजिस्टर_id         - Index of ACPI Register to access
 *
 * RETURN:      The biपंचांगask to be used when accessing the रेजिस्टर
 *
 * DESCRIPTION: Map रेजिस्टर_id पूर्णांकo a रेजिस्टर biपंचांगask.
 *
 ******************************************************************************/

काष्ठा acpi_bit_रेजिस्टर_info *acpi_hw_get_bit_रेजिस्टर_info(u32 रेजिस्टर_id)
अणु
	ACPI_FUNCTION_ENTRY();

	अगर (रेजिस्टर_id > ACPI_BITREG_MAX) अणु
		ACPI_ERROR((AE_INFO, "Invalid BitRegister ID: 0x%X",
			    रेजिस्टर_id));
		वापस (शून्य);
	पूर्ण

	वापस (&acpi_gbl_bit_रेजिस्टर_info[रेजिस्टर_id]);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_ग_लिखो_pm1_control
 *
 * PARAMETERS:  pm1a_control        - Value to be written to PM1A control
 *              pm1b_control        - Value to be written to PM1B control
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Write the PM1 A/B control रेजिस्टरs. These रेजिस्टरs are
 *              dअगरferent than than the PM1 A/B status and enable रेजिस्टरs
 *              in that dअगरferent values can be written to the A/B रेजिस्टरs.
 *              Most notably, the SLP_TYP bits can be dअगरferent, as per the
 *              values वापसed from the _Sx predefined methods.
 *
 ******************************************************************************/

acpi_status acpi_hw_ग_लिखो_pm1_control(u32 pm1a_control, u32 pm1b_control)
अणु
	acpi_status status;

	ACPI_FUNCTION_TRACE(hw_ग_लिखो_pm1_control);

	status =
	    acpi_hw_ग_लिखो(pm1a_control, &acpi_gbl_FADT.xpm1a_control_block);
	अगर (ACPI_FAILURE(status)) अणु
		वापस_ACPI_STATUS(status);
	पूर्ण

	अगर (acpi_gbl_FADT.xpm1b_control_block.address) अणु
		status =
		    acpi_hw_ग_लिखो(pm1b_control,
				  &acpi_gbl_FADT.xpm1b_control_block);
	पूर्ण
	वापस_ACPI_STATUS(status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_रेजिस्टर_पढ़ो
 *
 * PARAMETERS:  रेजिस्टर_id         - ACPI Register ID
 *              वापस_value        - Where the रेजिस्टर value is वापसed
 *
 * RETURN:      Status and the value पढ़ो.
 *
 * DESCRIPTION: Read from the specअगरied ACPI रेजिस्टर
 *
 ******************************************************************************/
acpi_status acpi_hw_रेजिस्टर_पढ़ो(u32 रेजिस्टर_id, u32 *वापस_value)
अणु
	u32 value = 0;
	u64 value64;
	acpi_status status;

	ACPI_FUNCTION_TRACE(hw_रेजिस्टर_पढ़ो);

	चयन (रेजिस्टर_id) अणु
	हाल ACPI_REGISTER_PM1_STATUS:	/* PM1 A/B: 16-bit access each */

		status = acpi_hw_पढ़ो_multiple(&value,
					       &acpi_gbl_xpm1a_status,
					       &acpi_gbl_xpm1b_status);
		अवरोध;

	हाल ACPI_REGISTER_PM1_ENABLE:	/* PM1 A/B: 16-bit access each */

		status = acpi_hw_पढ़ो_multiple(&value,
					       &acpi_gbl_xpm1a_enable,
					       &acpi_gbl_xpm1b_enable);
		अवरोध;

	हाल ACPI_REGISTER_PM1_CONTROL:	/* PM1 A/B: 16-bit access each */

		status = acpi_hw_पढ़ो_multiple(&value,
					       &acpi_gbl_FADT.
					       xpm1a_control_block,
					       &acpi_gbl_FADT.
					       xpm1b_control_block);

		/*
		 * Zero the ग_लिखो-only bits. From the ACPI specअगरication, "Hardware
		 * Write-Only Bits": "Upon पढ़ोs to रेजिस्टरs with ग_लिखो-only bits,
		 * software masks out all ग_लिखो-only bits."
		 */
		value &= ~ACPI_PM1_CONTROL_WRITEONLY_BITS;
		अवरोध;

	हाल ACPI_REGISTER_PM2_CONTROL:	/* 8-bit access */

		status =
		    acpi_hw_पढ़ो(&value64, &acpi_gbl_FADT.xpm2_control_block);
		अगर (ACPI_SUCCESS(status)) अणु
			value = (u32)value64;
		पूर्ण
		अवरोध;

	हाल ACPI_REGISTER_PM_TIMER:	/* 32-bit access */

		status = acpi_hw_पढ़ो(&value64, &acpi_gbl_FADT.xpm_समयr_block);
		अगर (ACPI_SUCCESS(status)) अणु
			value = (u32)value64;
		पूर्ण

		अवरोध;

	हाल ACPI_REGISTER_SMI_COMMAND_BLOCK:	/* 8-bit access */

		status =
		    acpi_hw_पढ़ो_port(acpi_gbl_FADT.smi_command, &value, 8);
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Unknown Register ID: 0x%X", रेजिस्टर_id));
		status = AE_BAD_PARAMETER;
		अवरोध;
	पूर्ण

	अगर (ACPI_SUCCESS(status)) अणु
		*वापस_value = (u32)value;
	पूर्ण

	वापस_ACPI_STATUS(status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_रेजिस्टर_ग_लिखो
 *
 * PARAMETERS:  रेजिस्टर_id         - ACPI Register ID
 *              value               - The value to ग_लिखो
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Write to the specअगरied ACPI रेजिस्टर
 *
 * NOTE: In accordance with the ACPI specअगरication, this function स्वतःmatically
 * preserves the value of the following bits, meaning that these bits cannot be
 * changed via this पूर्णांकerface:
 *
 * PM1_CONTROL[0] = SCI_EN
 * PM1_CONTROL[9]
 * PM1_STATUS[11]
 *
 * ACPI References:
 * 1) Hardware Ignored Bits: When software ग_लिखोs to a रेजिस्टर with ignored
 *      bit fields, it preserves the ignored bit fields
 * 2) SCI_EN: OSPM always preserves this bit position
 *
 ******************************************************************************/

acpi_status acpi_hw_रेजिस्टर_ग_लिखो(u32 रेजिस्टर_id, u32 value)
अणु
	acpi_status status;
	u32 पढ़ो_value;
	u64 पढ़ो_value64;

	ACPI_FUNCTION_TRACE(hw_रेजिस्टर_ग_लिखो);

	चयन (रेजिस्टर_id) अणु
	हाल ACPI_REGISTER_PM1_STATUS:	/* PM1 A/B: 16-bit access each */
		/*
		 * Handle the "ignored" bit in PM1 Status. According to the ACPI
		 * specअगरication, ignored bits are to be preserved when writing.
		 * Normally, this would mean a पढ़ो/modअगरy/ग_लिखो sequence. However,
		 * preserving a bit in the status रेजिस्टर is dअगरferent. Writing a
		 * one clears the status, and writing a zero preserves the status.
		 * Thereक्रमe, we must always ग_लिखो zero to the ignored bit.
		 *
		 * This behavior is clarअगरied in the ACPI 4.0 specअगरication.
		 */
		value &= ~ACPI_PM1_STATUS_PRESERVED_BITS;

		status = acpi_hw_ग_लिखो_multiple(value,
						&acpi_gbl_xpm1a_status,
						&acpi_gbl_xpm1b_status);
		अवरोध;

	हाल ACPI_REGISTER_PM1_ENABLE:	/* PM1 A/B: 16-bit access each */

		status = acpi_hw_ग_लिखो_multiple(value,
						&acpi_gbl_xpm1a_enable,
						&acpi_gbl_xpm1b_enable);
		अवरोध;

	हाल ACPI_REGISTER_PM1_CONTROL:	/* PM1 A/B: 16-bit access each */
		/*
		 * Perक्रमm a पढ़ो first to preserve certain bits (per ACPI spec)
		 * Note: This includes SCI_EN, we never want to change this bit
		 */
		status = acpi_hw_पढ़ो_multiple(&पढ़ो_value,
					       &acpi_gbl_FADT.
					       xpm1a_control_block,
					       &acpi_gbl_FADT.
					       xpm1b_control_block);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ निकास;
		पूर्ण

		/* Insert the bits to be preserved */

		ACPI_INSERT_BITS(value, ACPI_PM1_CONTROL_PRESERVED_BITS,
				 पढ़ो_value);

		/* Now we can ग_लिखो the data */

		status = acpi_hw_ग_लिखो_multiple(value,
						&acpi_gbl_FADT.
						xpm1a_control_block,
						&acpi_gbl_FADT.
						xpm1b_control_block);
		अवरोध;

	हाल ACPI_REGISTER_PM2_CONTROL:	/* 8-bit access */
		/*
		 * For control रेजिस्टरs, all reserved bits must be preserved,
		 * as per the ACPI spec.
		 */
		status =
		    acpi_hw_पढ़ो(&पढ़ो_value64,
				 &acpi_gbl_FADT.xpm2_control_block);
		अगर (ACPI_FAILURE(status)) अणु
			जाओ निकास;
		पूर्ण
		पढ़ो_value = (u32)पढ़ो_value64;

		/* Insert the bits to be preserved */

		ACPI_INSERT_BITS(value, ACPI_PM2_CONTROL_PRESERVED_BITS,
				 पढ़ो_value);

		status =
		    acpi_hw_ग_लिखो(value, &acpi_gbl_FADT.xpm2_control_block);
		अवरोध;

	हाल ACPI_REGISTER_PM_TIMER:	/* 32-bit access */

		status = acpi_hw_ग_लिखो(value, &acpi_gbl_FADT.xpm_समयr_block);
		अवरोध;

	हाल ACPI_REGISTER_SMI_COMMAND_BLOCK:	/* 8-bit access */

		/* SMI_CMD is currently always in IO space */

		status =
		    acpi_hw_ग_लिखो_port(acpi_gbl_FADT.smi_command, value, 8);
		अवरोध;

	शेष:

		ACPI_ERROR((AE_INFO, "Unknown Register ID: 0x%X", रेजिस्टर_id));
		status = AE_BAD_PARAMETER;
		अवरोध;
	पूर्ण

निकास:
	वापस_ACPI_STATUS(status);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_पढ़ो_multiple
 *
 * PARAMETERS:  value               - Where the रेजिस्टर value is वापसed
 *              रेजिस्टर_a           - First ACPI रेजिस्टर (required)
 *              रेजिस्टर_b           - Second ACPI रेजिस्टर (optional)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Read from the specअगरied two-part ACPI रेजिस्टर (such as PM1 A/B)
 *
 ******************************************************************************/

अटल acpi_status
acpi_hw_पढ़ो_multiple(u32 *value,
		      काष्ठा acpi_generic_address *रेजिस्टर_a,
		      काष्ठा acpi_generic_address *रेजिस्टर_b)
अणु
	u32 value_a = 0;
	u32 value_b = 0;
	u64 value64;
	acpi_status status;

	/* The first रेजिस्टर is always required */

	status = acpi_hw_पढ़ो(&value64, रेजिस्टर_a);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण
	value_a = (u32)value64;

	/* Second रेजिस्टर is optional */

	अगर (रेजिस्टर_b->address) अणु
		status = acpi_hw_पढ़ो(&value64, रेजिस्टर_b);
		अगर (ACPI_FAILURE(status)) अणु
			वापस (status);
		पूर्ण
		value_b = (u32)value64;
	पूर्ण

	/*
	 * OR the two वापस values together. No shअगरting or masking is necessary,
	 * because of how the PM1 रेजिस्टरs are defined in the ACPI specअगरication:
	 *
	 * "Although the bits can be split between the two रेजिस्टर blocks (each
	 * रेजिस्टर block has a unique poपूर्णांकer within the FADT), the bit positions
	 * are मुख्यtained. The रेजिस्टर block with unimplemented bits (that is,
	 * those implemented in the other रेजिस्टर block) always वापसs zeros,
	 * and ग_लिखोs have no side effects"
	 */
	*value = (value_a | value_b);
	वापस (AE_OK);
पूर्ण

/******************************************************************************
 *
 * FUNCTION:    acpi_hw_ग_लिखो_multiple
 *
 * PARAMETERS:  value               - The value to ग_लिखो
 *              रेजिस्टर_a           - First ACPI रेजिस्टर (required)
 *              रेजिस्टर_b           - Second ACPI रेजिस्टर (optional)
 *
 * RETURN:      Status
 *
 * DESCRIPTION: Write to the specअगरied two-part ACPI रेजिस्टर (such as PM1 A/B)
 *
 ******************************************************************************/

अटल acpi_status
acpi_hw_ग_लिखो_multiple(u32 value,
		       काष्ठा acpi_generic_address *रेजिस्टर_a,
		       काष्ठा acpi_generic_address *रेजिस्टर_b)
अणु
	acpi_status status;

	/* The first रेजिस्टर is always required */

	status = acpi_hw_ग_लिखो(value, रेजिस्टर_a);
	अगर (ACPI_FAILURE(status)) अणु
		वापस (status);
	पूर्ण

	/*
	 * Second रेजिस्टर is optional
	 *
	 * No bit shअगरting or clearing is necessary, because of how the PM1
	 * रेजिस्टरs are defined in the ACPI specअगरication:
	 *
	 * "Although the bits can be split between the two रेजिस्टर blocks (each
	 * रेजिस्टर block has a unique poपूर्णांकer within the FADT), the bit positions
	 * are मुख्यtained. The रेजिस्टर block with unimplemented bits (that is,
	 * those implemented in the other रेजिस्टर block) always वापसs zeros,
	 * and ग_लिखोs have no side effects"
	 */
	अगर (रेजिस्टर_b->address) अणु
		status = acpi_hw_ग_लिखो(value, रेजिस्टर_b);
	पूर्ण

	वापस (status);
पूर्ण

#पूर्ण_अगर				/* !ACPI_REDUCED_HARDWARE */
