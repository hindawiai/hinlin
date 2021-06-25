<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: rsaddr - Address resource descriptors (16/32/64)
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acresrc.h"

#घोषणा _COMPONENT          ACPI_RESOURCES
ACPI_MODULE_NAME("rsaddr")

/*******************************************************************************
 *
 * acpi_rs_convert_address16 - All WORD (16-bit) address resources
 *
 ******************************************************************************/
काष्ठा acpi_rsconvert_info acpi_rs_convert_address16[5] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_ADDRESS16,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_address16),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_address16)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_ADDRESS16,
	 माप(काष्ठा aml_resource_address16),
	 0पूर्ण,

	/* Resource Type, General Flags, and Type-Specअगरic Flags */

	अणुACPI_RSC_ADDRESS, 0, 0, 0पूर्ण,

	/*
	 * These fields are contiguous in both the source and destination:
	 * Address Granularity
	 * Address Range Minimum
	 * Address Range Maximum
	 * Address Translation Offset
	 * Address Length
	 */
	अणुACPI_RSC_MOVE16, ACPI_RS_OFFSET(data.address16.address.granularity),
	 AML_OFFSET(address16.granularity),
	 5पूर्ण,

	/* Optional resource_source (Index and String) */

	अणुACPI_RSC_SOURCE, ACPI_RS_OFFSET(data.address16.resource_source),
	 0,
	 माप(काष्ठा aml_resource_address16)पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_address32 - All DWORD (32-bit) address resources
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_address32[5] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_ADDRESS32,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_address32),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_address32)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_ADDRESS32,
	 माप(काष्ठा aml_resource_address32),
	 0पूर्ण,

	/* Resource Type, General Flags, and Type-Specअगरic Flags */

	अणुACPI_RSC_ADDRESS, 0, 0, 0पूर्ण,

	/*
	 * These fields are contiguous in both the source and destination:
	 * Address Granularity
	 * Address Range Minimum
	 * Address Range Maximum
	 * Address Translation Offset
	 * Address Length
	 */
	अणुACPI_RSC_MOVE32, ACPI_RS_OFFSET(data.address32.address.granularity),
	 AML_OFFSET(address32.granularity),
	 5पूर्ण,

	/* Optional resource_source (Index and String) */

	अणुACPI_RSC_SOURCE, ACPI_RS_OFFSET(data.address32.resource_source),
	 0,
	 माप(काष्ठा aml_resource_address32)पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_address64 - All QWORD (64-bit) address resources
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_address64[5] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_ADDRESS64,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_address64),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_address64)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_ADDRESS64,
	 माप(काष्ठा aml_resource_address64),
	 0पूर्ण,

	/* Resource Type, General Flags, and Type-Specअगरic Flags */

	अणुACPI_RSC_ADDRESS, 0, 0, 0पूर्ण,

	/*
	 * These fields are contiguous in both the source and destination:
	 * Address Granularity
	 * Address Range Minimum
	 * Address Range Maximum
	 * Address Translation Offset
	 * Address Length
	 */
	अणुACPI_RSC_MOVE64, ACPI_RS_OFFSET(data.address64.address.granularity),
	 AML_OFFSET(address64.granularity),
	 5पूर्ण,

	/* Optional resource_source (Index and String) */

	अणुACPI_RSC_SOURCE, ACPI_RS_OFFSET(data.address64.resource_source),
	 0,
	 माप(काष्ठा aml_resource_address64)पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_ext_address64 - All Extended (64-bit) address resources
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_ext_address64[5] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_EXTENDED_ADDRESS64,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_extended_address64),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_ext_address64)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_EXTENDED_ADDRESS64,
	 माप(काष्ठा aml_resource_extended_address64),
	 0पूर्ण,

	/* Resource Type, General Flags, and Type-Specअगरic Flags */

	अणुACPI_RSC_ADDRESS, 0, 0, 0पूर्ण,

	/* Revision ID */

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.ext_address64.revision_ID),
	 AML_OFFSET(ext_address64.revision_ID),
	 1पूर्ण,
	/*
	 * These fields are contiguous in both the source and destination:
	 * Address Granularity
	 * Address Range Minimum
	 * Address Range Maximum
	 * Address Translation Offset
	 * Address Length
	 * Type-Specअगरic Attribute
	 */
	अणुACPI_RSC_MOVE64,
	 ACPI_RS_OFFSET(data.ext_address64.address.granularity),
	 AML_OFFSET(ext_address64.granularity),
	 6पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_general_flags - Flags common to all address descriptors
 *
 ******************************************************************************/

अटल काष्ठा acpi_rsconvert_info acpi_rs_convert_general_flags[6] = अणु
	अणुACPI_RSC_FLAGINIT, 0, AML_OFFSET(address.flags),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_general_flags)पूर्ण,

	/* Resource Type (Memory, Io, bus_number, etc.) */

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.address.resource_type),
	 AML_OFFSET(address.resource_type),
	 1पूर्ण,

	/* General flags - Consume, Decode, min_fixed, max_fixed */

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.address.producer_consumer),
	 AML_OFFSET(address.flags),
	 0पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.address.decode),
	 AML_OFFSET(address.flags),
	 1पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.address.min_address_fixed),
	 AML_OFFSET(address.flags),
	 2पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.address.max_address_fixed),
	 AML_OFFSET(address.flags),
	 3पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_mem_flags - Flags common to Memory address descriptors
 *
 ******************************************************************************/

अटल काष्ठा acpi_rsconvert_info acpi_rs_convert_mem_flags[5] = अणु
	अणुACPI_RSC_FLAGINIT, 0, AML_OFFSET(address.specअगरic_flags),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_mem_flags)पूर्ण,

	/* Memory-specअगरic flags */

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.address.info.mem.ग_लिखो_protect),
	 AML_OFFSET(address.specअगरic_flags),
	 0पूर्ण,

	अणुACPI_RSC_2BITFLAG, ACPI_RS_OFFSET(data.address.info.mem.caching),
	 AML_OFFSET(address.specअगरic_flags),
	 1पूर्ण,

	अणुACPI_RSC_2BITFLAG, ACPI_RS_OFFSET(data.address.info.mem.range_type),
	 AML_OFFSET(address.specअगरic_flags),
	 3पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.address.info.mem.translation),
	 AML_OFFSET(address.specअगरic_flags),
	 5पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_io_flags - Flags common to I/O address descriptors
 *
 ******************************************************************************/

अटल काष्ठा acpi_rsconvert_info acpi_rs_convert_io_flags[4] = अणु
	अणुACPI_RSC_FLAGINIT, 0, AML_OFFSET(address.specअगरic_flags),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_io_flags)पूर्ण,

	/* I/O-specअगरic flags */

	अणुACPI_RSC_2BITFLAG, ACPI_RS_OFFSET(data.address.info.io.range_type),
	 AML_OFFSET(address.specअगरic_flags),
	 0पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.address.info.io.translation),
	 AML_OFFSET(address.specअगरic_flags),
	 4पूर्ण,

	अणुACPI_RSC_1BITFLAG,
	 ACPI_RS_OFFSET(data.address.info.io.translation_type),
	 AML_OFFSET(address.specअगरic_flags),
	 5पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_get_address_common
 *
 * PARAMETERS:  resource            - Poपूर्णांकer to the पूर्णांकernal resource काष्ठा
 *              aml                 - Poपूर्णांकer to the AML resource descriptor
 *
 * RETURN:      TRUE अगर the resource_type field is OK, FALSE otherwise
 *
 * DESCRIPTION: Convert common flag fields from a raw AML resource descriptor
 *              to an पूर्णांकernal resource descriptor
 *
 ******************************************************************************/

u8
acpi_rs_get_address_common(काष्ठा acpi_resource *resource,
			   जोड़ aml_resource *aml)
अणु
	ACPI_FUNCTION_ENTRY();

	/* Validate the Resource Type */

	अगर ((aml->address.resource_type > 2) &&
	    (aml->address.resource_type < 0xC0)) अणु
		वापस (FALSE);
	पूर्ण

	/* Get the Resource Type and General Flags */

	(व्योम)acpi_rs_convert_aml_to_resource(resource, aml,
					      acpi_rs_convert_general_flags);

	/* Get the Type-Specअगरic Flags (Memory and I/O descriptors only) */

	अगर (resource->data.address.resource_type == ACPI_MEMORY_RANGE) अणु
		(व्योम)acpi_rs_convert_aml_to_resource(resource, aml,
						      acpi_rs_convert_mem_flags);
	पूर्ण अन्यथा अगर (resource->data.address.resource_type == ACPI_IO_RANGE) अणु
		(व्योम)acpi_rs_convert_aml_to_resource(resource, aml,
						      acpi_rs_convert_io_flags);
	पूर्ण अन्यथा अणु
		/* Generic resource type, just grab the type_specअगरic byte */

		resource->data.address.info.type_specअगरic =
		    aml->address.specअगरic_flags;
	पूर्ण

	वापस (TRUE);
पूर्ण

/*******************************************************************************
 *
 * FUNCTION:    acpi_rs_set_address_common
 *
 * PARAMETERS:  aml                 - Poपूर्णांकer to the AML resource descriptor
 *              resource            - Poपूर्णांकer to the पूर्णांकernal resource काष्ठा
 *
 * RETURN:      None
 *
 * DESCRIPTION: Convert common flag fields from a resource descriptor to an
 *              AML descriptor
 *
 ******************************************************************************/

व्योम
acpi_rs_set_address_common(जोड़ aml_resource *aml,
			   काष्ठा acpi_resource *resource)
अणु
	ACPI_FUNCTION_ENTRY();

	/* Set the Resource Type and General Flags */

	(व्योम)acpi_rs_convert_resource_to_aml(resource, aml,
					      acpi_rs_convert_general_flags);

	/* Set the Type-Specअगरic Flags (Memory and I/O descriptors only) */

	अगर (resource->data.address.resource_type == ACPI_MEMORY_RANGE) अणु
		(व्योम)acpi_rs_convert_resource_to_aml(resource, aml,
						      acpi_rs_convert_mem_flags);
	पूर्ण अन्यथा अगर (resource->data.address.resource_type == ACPI_IO_RANGE) अणु
		(व्योम)acpi_rs_convert_resource_to_aml(resource, aml,
						      acpi_rs_convert_io_flags);
	पूर्ण अन्यथा अणु
		/* Generic resource type, just copy the type_specअगरic byte */

		aml->address.specअगरic_flags =
		    resource->data.address.info.type_specअगरic;
	पूर्ण
पूर्ण
