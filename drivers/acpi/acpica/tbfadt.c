<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/******************************************************************************
 *
 * Module Name: tbfadt   - FADT table utilities
 *
 * Copyright (C) 2000 - 2021, Intel Corp.
 *
 *****************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "actables.h"

#घोषणा _COMPONENT          ACPI_TABLES
ACPI_MODULE_NAME("tbfadt")

/* Local prototypes */
अटल व्योम
acpi_tb_init_generic_address(काष्ठा acpi_generic_address *generic_address,
			     u8 space_id,
			     u8 byte_width,
			     u64 address, स्थिर अक्षर *रेजिस्टर_name, u8 flags);

अटल व्योम acpi_tb_convert_fadt(व्योम);

अटल व्योम acpi_tb_setup_fadt_रेजिस्टरs(व्योम);

अटल u64
acpi_tb_select_address(अक्षर *रेजिस्टर_name, u32 address32, u64 address64);

/* Table क्रम conversion of FADT to common पूर्णांकernal क्रमmat and FADT validation */

प्रकार काष्ठा acpi_fadt_info अणु
	स्थिर अक्षर *name;
	u16 address64;
	u16 address32;
	u16 length;
	u8 शेष_length;
	u8 flags;

पूर्ण acpi_fadt_info;

#घोषणा ACPI_FADT_OPTIONAL          0
#घोषणा ACPI_FADT_REQUIRED          1
#घोषणा ACPI_FADT_SEPARATE_LENGTH   2
#घोषणा ACPI_FADT_GPE_REGISTER      4

अटल काष्ठा acpi_fadt_info fadt_info_table[] = अणु
	अणु"Pm1aEventBlock",
	 ACPI_FADT_OFFSET(xpm1a_event_block),
	 ACPI_FADT_OFFSET(pm1a_event_block),
	 ACPI_FADT_OFFSET(pm1_event_length),
	 ACPI_PM1_REGISTER_WIDTH * 2,	/* Enable + Status रेजिस्टर */
	 ACPI_FADT_REQUIREDपूर्ण,

	अणु"Pm1bEventBlock",
	 ACPI_FADT_OFFSET(xpm1b_event_block),
	 ACPI_FADT_OFFSET(pm1b_event_block),
	 ACPI_FADT_OFFSET(pm1_event_length),
	 ACPI_PM1_REGISTER_WIDTH * 2,	/* Enable + Status रेजिस्टर */
	 ACPI_FADT_OPTIONALपूर्ण,

	अणु"Pm1aControlBlock",
	 ACPI_FADT_OFFSET(xpm1a_control_block),
	 ACPI_FADT_OFFSET(pm1a_control_block),
	 ACPI_FADT_OFFSET(pm1_control_length),
	 ACPI_PM1_REGISTER_WIDTH,
	 ACPI_FADT_REQUIREDपूर्ण,

	अणु"Pm1bControlBlock",
	 ACPI_FADT_OFFSET(xpm1b_control_block),
	 ACPI_FADT_OFFSET(pm1b_control_block),
	 ACPI_FADT_OFFSET(pm1_control_length),
	 ACPI_PM1_REGISTER_WIDTH,
	 ACPI_FADT_OPTIONALपूर्ण,

	अणु"Pm2ControlBlock",
	 ACPI_FADT_OFFSET(xpm2_control_block),
	 ACPI_FADT_OFFSET(pm2_control_block),
	 ACPI_FADT_OFFSET(pm2_control_length),
	 ACPI_PM2_REGISTER_WIDTH,
	 ACPI_FADT_SEPARATE_LENGTHपूर्ण,

	अणु"PmTimerBlock",
	 ACPI_FADT_OFFSET(xpm_समयr_block),
	 ACPI_FADT_OFFSET(pm_समयr_block),
	 ACPI_FADT_OFFSET(pm_समयr_length),
	 ACPI_PM_TIMER_WIDTH,
	 ACPI_FADT_SEPARATE_LENGTHपूर्ण,	/* ACPI 5.0A: Timer is optional */

	अणु"Gpe0Block",
	 ACPI_FADT_OFFSET(xgpe0_block),
	 ACPI_FADT_OFFSET(gpe0_block),
	 ACPI_FADT_OFFSET(gpe0_block_length),
	 0,
	 ACPI_FADT_SEPARATE_LENGTH | ACPI_FADT_GPE_REGISTERपूर्ण,

	अणु"Gpe1Block",
	 ACPI_FADT_OFFSET(xgpe1_block),
	 ACPI_FADT_OFFSET(gpe1_block),
	 ACPI_FADT_OFFSET(gpe1_block_length),
	 0,
	 ACPI_FADT_SEPARATE_LENGTH | ACPI_FADT_GPE_REGISTERपूर्ण
पूर्ण;

#घोषणा ACPI_FADT_INFO_ENTRIES \
			(माप (fadt_info_table) / माप (काष्ठा acpi_fadt_info))

/* Table used to split Event Blocks पूर्णांकo separate status/enable रेजिस्टरs */

प्रकार काष्ठा acpi_fadt_pm_info अणु
	काष्ठा acpi_generic_address *target;
	u16 source;
	u8 रेजिस्टर_num;

पूर्ण acpi_fadt_pm_info;

अटल काष्ठा acpi_fadt_pm_info fadt_pm_info_table[] = अणु
	अणु&acpi_gbl_xpm1a_status,
	 ACPI_FADT_OFFSET(xpm1a_event_block),
	 0पूर्ण,

	अणु&acpi_gbl_xpm1a_enable,
	 ACPI_FADT_OFFSET(xpm1a_event_block),
	 1पूर्ण,

	अणु&acpi_gbl_xpm1b_status,
	 ACPI_FADT_OFFSET(xpm1b_event_block),
	 0पूर्ण,

	अणु&acpi_gbl_xpm1b_enable,
	 ACPI_FADT_OFFSET(xpm1b_event_block),
	 1पूर्ण
पूर्ण;

#घोषणा ACPI_FADT_PM_INFO_ENTRIES \
			(माप (fadt_pm_info_table) / माप (काष्ठा acpi_fadt_pm_info))

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_init_generic_address
 *
 * PARAMETERS:  generic_address     - GAS काष्ठा to be initialized
 *              space_id            - ACPI Space ID क्रम this रेजिस्टर
 *              byte_width          - Width of this रेजिस्टर
 *              address             - Address of the रेजिस्टर
 *              रेजिस्टर_name       - ASCII name of the ACPI रेजिस्टर
 *
 * RETURN:      None
 *
 * DESCRIPTION: Initialize a Generic Address Structure (GAS)
 *              See the ACPI specअगरication क्रम a full description and
 *              definition of this काष्ठाure.
 *
 ******************************************************************************/

अटल व्योम
acpi_tb_init_generic_address(काष्ठा acpi_generic_address *generic_address,
			     u8 space_id,
			     u8 byte_width,
			     u64 address, स्थिर अक्षर *रेजिस्टर_name, u8 flags)
अणु
	u8 bit_width;

	/*
	 * Bit width field in the GAS is only one byte दीर्घ, 255 max.
	 * Check क्रम bit_width overflow in GAS.
	 */
	bit_width = (u8)(byte_width * 8);
	अगर (byte_width > 31) अणु	/* (31*8)=248, (32*8)=256 */
		/*
		 * No error क्रम GPE blocks, because we करो not use the bit_width
		 * क्रम GPEs, the legacy length (byte_width) is used instead to
		 * allow क्रम a large number of GPEs.
		 */
		अगर (!(flags & ACPI_FADT_GPE_REGISTER)) अणु
			ACPI_ERROR((AE_INFO,
				    "%s - 32-bit FADT register is too long (%u bytes, %u bits) "
				    "to convert to GAS struct - 255 bits max, truncating",
				    रेजिस्टर_name, byte_width,
				    (byte_width * 8)));
		पूर्ण

		bit_width = 255;
	पूर्ण

	/*
	 * The 64-bit Address field is non-aligned in the byte packed
	 * GAS काष्ठा.
	 */
	ACPI_MOVE_64_TO_64(&generic_address->address, &address);

	/* All other fields are byte-wide */

	generic_address->space_id = space_id;
	generic_address->bit_width = bit_width;
	generic_address->bit_offset = 0;
	generic_address->access_width = 0;	/* Access width ANY */
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_select_address
 *
 * PARAMETERS:  रेजिस्टर_name       - ASCII name of the ACPI रेजिस्टर
 *              address32           - 32-bit address of the रेजिस्टर
 *              address64           - 64-bit address of the रेजिस्टर
 *
 * RETURN:      The resolved 64-bit address
 *
 * DESCRIPTION: Select between 32-bit and 64-bit versions of addresses within
 *              the FADT. Used क्रम the FACS and DSDT addresses.
 *
 * NOTES:
 *
 * Check क्रम FACS and DSDT address mismatches. An address mismatch between
 * the 32-bit and 64-bit address fields (FIRMWARE_CTRL/X_FIRMWARE_CTRL and
 * DSDT/X_DSDT) could be a corrupted address field or it might indicate
 * the presence of two FACS or two DSDT tables.
 *
 * November 2013:
 * By शेष, as per the ACPICA specअगरication, a valid 64-bit address is
 * used regardless of the value of the 32-bit address. However, this
 * behavior can be overridden via the acpi_gbl_use32_bit_fadt_addresses flag.
 *
 ******************************************************************************/

अटल u64
acpi_tb_select_address(अक्षर *रेजिस्टर_name, u32 address32, u64 address64)
अणु

	अगर (!address64) अणु

		/* 64-bit address is zero, use 32-bit address */

		वापस ((u64)address32);
	पूर्ण

	अगर (address32 && (address64 != (u64)address32)) अणु

		/* Address mismatch between 32-bit and 64-bit versions */

		ACPI_BIOS_WARNING((AE_INFO,
				   "32/64X %s address mismatch in FADT: "
				   "0x%8.8X/0x%8.8X%8.8X, using %u-bit address",
				   रेजिस्टर_name, address32,
				   ACPI_FORMAT_UINT64(address64),
				   acpi_gbl_use32_bit_fadt_addresses ? 32 :
				   64));

		/* 32-bit address override */

		अगर (acpi_gbl_use32_bit_fadt_addresses) अणु
			वापस ((u64)address32);
		पूर्ण
	पूर्ण

	/* Default is to use the 64-bit address */

	वापस (address64);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_parse_fadt
 *
 * PARAMETERS:  None
 *
 * RETURN:      None
 *
 * DESCRIPTION: Initialize the FADT, DSDT and FACS tables
 *              (FADT contains the addresses of the DSDT and FACS)
 *
 ******************************************************************************/

व्योम acpi_tb_parse_fadt(व्योम)
अणु
	u32 length;
	काष्ठा acpi_table_header *table;
	काष्ठा acpi_table_desc *fadt_desc;
	acpi_status status;

	/*
	 * The FADT has multiple versions with dअगरferent lengths,
	 * and it contains poपूर्णांकers to both the DSDT and FACS tables.
	 *
	 * Get a local copy of the FADT and convert it to a common क्रमmat
	 * Map entire FADT, assumed to be smaller than one page.
	 */
	fadt_desc = &acpi_gbl_root_table_list.tables[acpi_gbl_fadt_index];
	status = acpi_tb_get_table(fadt_desc, &table);
	अगर (ACPI_FAILURE(status)) अणु
		वापस;
	पूर्ण
	length = fadt_desc->length;

	/*
	 * Validate the FADT checksum beक्रमe we copy the table. Ignore
	 * checksum error as we want to try to get the DSDT and FACS.
	 */
	(व्योम)acpi_tb_verअगरy_checksum(table, length);

	/* Create a local copy of the FADT in common ACPI 2.0+ क्रमmat */

	acpi_tb_create_local_fadt(table, length);

	/* All करोne with the real FADT, unmap it */

	acpi_tb_put_table(fadt_desc);

	/* Obtain the DSDT and FACS tables via their addresses within the FADT */

	acpi_tb_install_standard_table((acpi_physical_address)acpi_gbl_FADT.
				       Xdsdt,
				       ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL,
				       FALSE, TRUE, &acpi_gbl_dsdt_index);

	/* If Hardware Reduced flag is set, there is no FACS */

	अगर (!acpi_gbl_reduced_hardware) अणु
		अगर (acpi_gbl_FADT.facs) अणु
			acpi_tb_install_standard_table((acpi_physical_address)
						       acpi_gbl_FADT.facs,
						       ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL,
						       FALSE, TRUE,
						       &acpi_gbl_facs_index);
		पूर्ण
		अगर (acpi_gbl_FADT.Xfacs) अणु
			acpi_tb_install_standard_table((acpi_physical_address)
						       acpi_gbl_FADT.Xfacs,
						       ACPI_TABLE_ORIGIN_INTERNAL_PHYSICAL,
						       FALSE, TRUE,
						       &acpi_gbl_xfacs_index);
		पूर्ण
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_create_local_fadt
 *
 * PARAMETERS:  table               - Poपूर्णांकer to BIOS FADT
 *              length              - Length of the table
 *
 * RETURN:      None
 *
 * DESCRIPTION: Get a local copy of the FADT and convert it to a common क्रमmat.
 *              Perक्रमms validation on some important FADT fields.
 *
 * NOTE:        We create a local copy of the FADT regardless of the version.
 *
 ******************************************************************************/

व्योम acpi_tb_create_local_fadt(काष्ठा acpi_table_header *table, u32 length)
अणु
	/*
	 * Check अगर the FADT is larger than the largest table that we expect
	 * (typically the current ACPI specअगरication version). If so, truncate
	 * the table, and issue a warning.
	 */
	अगर (length > माप(काष्ठा acpi_table_fadt)) अणु
		ACPI_BIOS_WARNING((AE_INFO,
				   "FADT (revision %u) is longer than %s length, "
				   "truncating length %u to %u",
				   table->revision, ACPI_FADT_CONFORMANCE,
				   length,
				   (u32)माप(काष्ठा acpi_table_fadt)));
	पूर्ण

	/* Clear the entire local FADT */

	स_रखो(&acpi_gbl_FADT, 0, माप(काष्ठा acpi_table_fadt));

	/* Copy the original FADT, up to माप (काष्ठा acpi_table_fadt) */

	स_नकल(&acpi_gbl_FADT, table,
	       ACPI_MIN(length, माप(काष्ठा acpi_table_fadt)));

	/* Take a copy of the Hardware Reduced flag */

	acpi_gbl_reduced_hardware = FALSE;
	अगर (acpi_gbl_FADT.flags & ACPI_FADT_HW_REDUCED) अणु
		acpi_gbl_reduced_hardware = TRUE;
	पूर्ण

	/* Convert the local copy of the FADT to the common पूर्णांकernal क्रमmat */

	acpi_tb_convert_fadt();

	/* Initialize the global ACPI रेजिस्टर काष्ठाures */

	acpi_tb_setup_fadt_रेजिस्टरs();
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_convert_fadt
 *
 * PARAMETERS:  none - acpi_gbl_FADT is used.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Converts all versions of the FADT to a common पूर्णांकernal क्रमmat.
 *              Expand 32-bit addresses to 64-bit as necessary. Also validate
 *              important fields within the FADT.
 *
 * NOTE:        acpi_gbl_FADT must be of size (काष्ठा acpi_table_fadt), and must
 *              contain a copy of the actual BIOS-provided FADT.
 *
 * Notes on 64-bit रेजिस्टर addresses:
 *
 * After this FADT conversion, later ACPICA code will only use the 64-bit "X"
 * fields of the FADT क्रम all ACPI रेजिस्टर addresses.
 *
 * The 64-bit X fields are optional extensions to the original 32-bit FADT
 * V1.0 fields. Even अगर they are present in the FADT, they are optional and
 * are unused अगर the BIOS sets them to zero. Thereक्रमe, we must copy/expand
 * 32-bit V1.0 fields to the 64-bit X fields अगर the 64-bit X field is originally
 * zero.
 *
 * For ACPI 1.0 FADTs (that contain no 64-bit addresses), all 32-bit address
 * fields are expanded to the corresponding 64-bit X fields in the पूर्णांकernal
 * common FADT.
 *
 * For ACPI 2.0+ FADTs, all valid (non-zero) 32-bit address fields are expanded
 * to the corresponding 64-bit X fields, अगर the 64-bit field is originally
 * zero. Adhering to the ACPI specअगरication, we completely ignore the 32-bit
 * field अगर the 64-bit field is valid, regardless of whether the host OS is
 * 32-bit or 64-bit.
 *
 * Possible additional checks:
 *  (acpi_gbl_FADT.pm1_event_length >= 4)
 *  (acpi_gbl_FADT.pm1_control_length >= 2)
 *  (acpi_gbl_FADT.pm_समयr_length >= 4)
 *  Gpe block lengths must be multiple of 2
 *
 ******************************************************************************/

अटल व्योम acpi_tb_convert_fadt(व्योम)
अणु
	स्थिर अक्षर *name;
	काष्ठा acpi_generic_address *address64;
	u32 address32;
	u8 length;
	u8 flags;
	u32 i;

	/*
	 * For ACPI 1.0 FADTs (revision 1 or 2), ensure that reserved fields which
	 * should be zero are indeed zero. This will workaround BIOSs that
	 * inadvertently place values in these fields.
	 *
	 * The ACPI 1.0 reserved fields that will be zeroed are the bytes located
	 * at offset 45, 55, 95, and the word located at offset 109, 110.
	 *
	 * Note: The FADT revision value is unreliable. Only the length can be
	 * trusted.
	 */
	अगर (acpi_gbl_FADT.header.length <= ACPI_FADT_V2_SIZE) अणु
		acpi_gbl_FADT.preferred_profile = 0;
		acpi_gbl_FADT.pstate_control = 0;
		acpi_gbl_FADT.cst_control = 0;
		acpi_gbl_FADT.boot_flags = 0;
	पूर्ण

	/*
	 * Now we can update the local FADT length to the length of the
	 * current FADT version as defined by the ACPI specअगरication.
	 * Thus, we will have a common FADT पूर्णांकernally.
	 */
	acpi_gbl_FADT.header.length = माप(काष्ठा acpi_table_fadt);

	/*
	 * Expand the 32-bit DSDT addresses to 64-bit as necessary.
	 * Later ACPICA code will always use the X 64-bit field.
	 */
	acpi_gbl_FADT.Xdsdt = acpi_tb_select_address("DSDT",
						     acpi_gbl_FADT.dsdt,
						     acpi_gbl_FADT.Xdsdt);

	/* If Hardware Reduced flag is set, we are all करोne */

	अगर (acpi_gbl_reduced_hardware) अणु
		वापस;
	पूर्ण

	/* Examine all of the 64-bit extended address fields (X fields) */

	क्रम (i = 0; i < ACPI_FADT_INFO_ENTRIES; i++) अणु
		/*
		 * Get the 32-bit and 64-bit addresses, as well as the रेजिस्टर
		 * length and रेजिस्टर name.
		 */
		address32 = *ACPI_ADD_PTR(u32,
					  &acpi_gbl_FADT,
					  fadt_info_table[i].address32);

		address64 = ACPI_ADD_PTR(काष्ठा acpi_generic_address,
					 &acpi_gbl_FADT,
					 fadt_info_table[i].address64);

		length = *ACPI_ADD_PTR(u8,
				       &acpi_gbl_FADT,
				       fadt_info_table[i].length);

		name = fadt_info_table[i].name;
		flags = fadt_info_table[i].flags;

		/*
		 * Expand the ACPI 1.0 32-bit addresses to the ACPI 2.0 64-bit "X"
		 * generic address काष्ठाures as necessary. Later code will always use
		 * the 64-bit address काष्ठाures.
		 *
		 * November 2013:
		 * Now always use the 64-bit address अगर it is valid (non-zero), in
		 * accordance with the ACPI specअगरication which states that a 64-bit
		 * address supersedes the 32-bit version. This behavior can be
		 * overridden by the acpi_gbl_use32_bit_fadt_addresses flag.
		 *
		 * During 64-bit address स्थिरruction and verअगरication,
		 * these हालs are handled:
		 *
		 * Address32 zero, Address64 [करोn't care]   - Use Address64
		 *
		 * No override: अगर acpi_gbl_use32_bit_fadt_addresses is FALSE, and:
		 * Address32 non-zero, Address64 zero       - Copy/use Address32
		 * Address32 non-zero == Address64 non-zero - Use Address64
		 * Address32 non-zero != Address64 non-zero - Warning, use Address64
		 *
		 * Override: अगर acpi_gbl_use32_bit_fadt_addresses is TRUE, and:
		 * Address32 non-zero, Address64 zero       - Copy/use Address32
		 * Address32 non-zero == Address64 non-zero - Copy/use Address32
		 * Address32 non-zero != Address64 non-zero - Warning, copy/use Address32
		 *
		 * Note: space_id is always I/O क्रम 32-bit legacy address fields
		 */
		अगर (address32) अणु
			अगर (address64->address) अणु
				अगर (address64->address != (u64)address32) अणु

					/* Address mismatch */

					ACPI_BIOS_WARNING((AE_INFO,
							   "32/64X address mismatch in FADT/%s: "
							   "0x%8.8X/0x%8.8X%8.8X, using %u-bit address",
							   name, address32,
							   ACPI_FORMAT_UINT64
							   (address64->address),
							   acpi_gbl_use32_bit_fadt_addresses
							   ? 32 : 64));
				पूर्ण

				/*
				 * For each extended field, check क्रम length mismatch
				 * between the legacy length field and the corresponding
				 * 64-bit X length field.
				 * Note: If the legacy length field is > 0xFF bits, ignore
				 * this check. (GPE रेजिस्टरs can be larger than the
				 * 64-bit GAS काष्ठाure can accommodate, 0xFF bits).
				 */
				अगर ((ACPI_MUL_8(length) <= ACPI_UINT8_MAX) &&
				    (address64->bit_width !=
				     ACPI_MUL_8(length))) अणु
					ACPI_BIOS_WARNING((AE_INFO,
							   "32/64X length mismatch in FADT/%s: %u/%u",
							   name,
							   ACPI_MUL_8(length),
							   address64->
							   bit_width));
				पूर्ण
			पूर्ण

			/*
			 * Hardware रेजिस्टर access code always uses the 64-bit fields.
			 * So अगर the 64-bit field is zero or is to be overridden,
			 * initialize it with the 32-bit fields.
			 * Note that when the 32-bit address favor is specअगरied, the
			 * 64-bit fields are always re-initialized so that
			 * access_size/bit_width/bit_offset fields can be correctly
			 * configured to the values to trigger a 32-bit compatible
			 * access mode in the hardware रेजिस्टर access code.
			 */
			अगर (!address64->address
			    || acpi_gbl_use32_bit_fadt_addresses) अणु
				acpi_tb_init_generic_address(address64,
							     ACPI_ADR_SPACE_SYSTEM_IO,
							     length,
							     (u64)address32,
							     name, flags);
			पूर्ण
		पूर्ण

		अगर (fadt_info_table[i].flags & ACPI_FADT_REQUIRED) अणु
			/*
			 * Field is required (Pm1a_event, Pm1a_control).
			 * Both the address and length must be non-zero.
			 */
			अगर (!address64->address || !length) अणु
				ACPI_BIOS_ERROR((AE_INFO,
						 "Required FADT field %s has zero address and/or length: "
						 "0x%8.8X%8.8X/0x%X",
						 name,
						 ACPI_FORMAT_UINT64(address64->
								    address),
						 length));
			पूर्ण
		पूर्ण अन्यथा अगर (fadt_info_table[i].flags & ACPI_FADT_SEPARATE_LENGTH) अणु
			/*
			 * Field is optional (Pm2_control, GPE0, GPE1) AND has its own
			 * length field. If present, both the address and length must
			 * be valid.
			 */
			अगर ((address64->address && !length) ||
			    (!address64->address && length)) अणु
				ACPI_BIOS_WARNING((AE_INFO,
						   "Optional FADT field %s has valid %s but zero %s: "
						   "0x%8.8X%8.8X/0x%X", name,
						   (length ? "Length" :
						    "Address"),
						   (length ? "Address" :
						    "Length"),
						   ACPI_FORMAT_UINT64
						   (address64->address),
						   length));
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_tb_setup_fadt_रेजिस्टरs
 *
 * PARAMETERS:  None, uses acpi_gbl_FADT.
 *
 * RETURN:      None
 *
 * DESCRIPTION: Initialize global ACPI PM1 रेजिस्टर definitions. Optionally,
 *              क्रमce FADT रेजिस्टर definitions to their शेष lengths.
 *
 ******************************************************************************/

अटल व्योम acpi_tb_setup_fadt_रेजिस्टरs(व्योम)
अणु
	काष्ठा acpi_generic_address *target64;
	काष्ठा acpi_generic_address *source64;
	u8 pm1_रेजिस्टर_byte_width;
	u32 i;

	/*
	 * Optionally check all रेजिस्टर lengths against the शेष values and
	 * update them अगर they are incorrect.
	 */
	अगर (acpi_gbl_use_शेष_रेजिस्टर_widths) अणु
		क्रम (i = 0; i < ACPI_FADT_INFO_ENTRIES; i++) अणु
			target64 =
			    ACPI_ADD_PTR(काष्ठा acpi_generic_address,
					 &acpi_gbl_FADT,
					 fadt_info_table[i].address64);

			/*
			 * If a valid रेजिस्टर (Address != 0) and the (शेष_length > 0)
			 * (Not a GPE रेजिस्टर), then check the width against the शेष.
			 */
			अगर ((target64->address) &&
			    (fadt_info_table[i].शेष_length > 0) &&
			    (fadt_info_table[i].शेष_length !=
			     target64->bit_width)) अणु
				ACPI_BIOS_WARNING((AE_INFO,
						   "Invalid length for FADT/%s: %u, using default %u",
						   fadt_info_table[i].name,
						   target64->bit_width,
						   fadt_info_table[i].
						   शेष_length));

				/* Incorrect size, set width to the शेष */

				target64->bit_width =
				    fadt_info_table[i].शेष_length;
			पूर्ण
		पूर्ण
	पूर्ण

	/*
	 * Get the length of the inभागidual PM1 रेजिस्टरs (enable and status).
	 * Each रेजिस्टर is defined to be (event block length / 2). Extra भागide
	 * by 8 converts bits to bytes.
	 */
	pm1_रेजिस्टर_byte_width = (u8)
	    ACPI_DIV_16(acpi_gbl_FADT.xpm1a_event_block.bit_width);

	/*
	 * Calculate separate GAS काष्ठाs क्रम the PM1x (A/B) Status and Enable
	 * रेजिस्टरs. These addresses करो not appear (directly) in the FADT, so it
	 * is useful to pre-calculate them from the PM1 Event Block definitions.
	 *
	 * The PM event blocks are split पूर्णांकo two रेजिस्टर blocks, first is the
	 * PM Status Register block, followed immediately by the PM Enable
	 * Register block. Each is of length (pm1_event_length/2)
	 *
	 * Note: The PM1A event block is required by the ACPI specअगरication.
	 * However, the PM1B event block is optional and is rarely, अगर ever,
	 * used.
	 */

	क्रम (i = 0; i < ACPI_FADT_PM_INFO_ENTRIES; i++) अणु
		source64 =
		    ACPI_ADD_PTR(काष्ठा acpi_generic_address, &acpi_gbl_FADT,
				 fadt_pm_info_table[i].source);

		अगर (source64->address) अणु
			acpi_tb_init_generic_address(fadt_pm_info_table[i].
						     target, source64->space_id,
						     pm1_रेजिस्टर_byte_width,
						     source64->address +
						     (fadt_pm_info_table[i].
						      रेजिस्टर_num *
						      pm1_रेजिस्टर_byte_width),
						     "PmRegisters", 0);
		पूर्ण
	पूर्ण
पूर्ण
