<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: rsio - IO and DMA resource descriptors
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acresrc.h"

#घोषणा _COMPONENT          ACPI_RESOURCES
ACPI_MODULE_NAME("rsio")

/*******************************************************************************
 *
 * acpi_rs_convert_io
 *
 ******************************************************************************/
काष्ठा acpi_rsconvert_info acpi_rs_convert_io[5] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_IO,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_io),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_io)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_IO,
	 माप(काष्ठा aml_resource_io),
	 0पूर्ण,

	/* Decode flag */

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.io.io_decode),
	 AML_OFFSET(io.flags),
	 0पूर्ण,
	/*
	 * These fields are contiguous in both the source and destination:
	 * Address Alignment
	 * Length
	 * Minimum Base Address
	 * Maximum Base Address
	 */
	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.io.alignment),
	 AML_OFFSET(io.alignment),
	 2पूर्ण,

	अणुACPI_RSC_MOVE16, ACPI_RS_OFFSET(data.io.minimum),
	 AML_OFFSET(io.minimum),
	 2पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_fixed_io
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_fixed_io[4] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_FIXED_IO,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_fixed_io),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_fixed_io)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_FIXED_IO,
	 माप(काष्ठा aml_resource_fixed_io),
	 0पूर्ण,
	/*
	 * These fields are contiguous in both the source and destination:
	 * Base Address
	 * Length
	 */
	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.fixed_io.address_length),
	 AML_OFFSET(fixed_io.address_length),
	 1पूर्ण,

	अणुACPI_RSC_MOVE16, ACPI_RS_OFFSET(data.fixed_io.address),
	 AML_OFFSET(fixed_io.address),
	 1पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_generic_reg
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_generic_reg[4] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_GENERIC_REGISTER,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_generic_रेजिस्टर),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_generic_reg)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_GENERIC_REGISTER,
	 माप(काष्ठा aml_resource_generic_रेजिस्टर),
	 0पूर्ण,
	/*
	 * These fields are contiguous in both the source and destination:
	 * Address Space ID
	 * Register Bit Width
	 * Register Bit Offset
	 * Access Size
	 */
	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.generic_reg.space_id),
	 AML_OFFSET(generic_reg.address_space_id),
	 4पूर्ण,

	/* Get the Register Address */

	अणुACPI_RSC_MOVE64, ACPI_RS_OFFSET(data.generic_reg.address),
	 AML_OFFSET(generic_reg.address),
	 1पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_end_dpf
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_end_dpf[2] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_END_DEPENDENT,
	 ACPI_RS_SIZE_MIN,
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_end_dpf)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_END_DEPENDENT,
	 माप(काष्ठा aml_resource_end_dependent),
	 0पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_end_tag
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_end_tag[2] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_END_TAG,
	 ACPI_RS_SIZE_MIN,
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_end_tag)पूर्ण,

	/*
	 * Note: The checksum field is set to zero, meaning that the resource
	 * data is treated as अगर the checksum operation succeeded.
	 * (ACPI Spec 1.0b Section 6.4.2.8)
	 */
	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_END_TAG,
	 माप(काष्ठा aml_resource_end_tag),
	 0पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_get_start_dpf
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_get_start_dpf[6] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_START_DEPENDENT,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_start_dependent),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_get_start_dpf)पूर्ण,

	/* Defaults क्रम Compatibility and Perक्रमmance priorities */

	अणुACPI_RSC_SET8, ACPI_RS_OFFSET(data.start_dpf.compatibility_priority),
	 ACPI_ACCEPTABLE_CONFIGURATION,
	 2पूर्ण,

	/* Get the descriptor length (0 or 1 क्रम Start Dpf descriptor) */

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.start_dpf.descriptor_length),
	 AML_OFFSET(start_dpf.descriptor_type),
	 0पूर्ण,

	/* All करोne अगर there is no flag byte present in the descriptor */

	अणुACPI_RSC_EXIT_NE, ACPI_RSC_COMPARE_AML_LENGTH, 0, 1पूर्ण,

	/* Flag byte is present, get the flags */

	अणुACPI_RSC_2BITFLAG,
	 ACPI_RS_OFFSET(data.start_dpf.compatibility_priority),
	 AML_OFFSET(start_dpf.flags),
	 0पूर्ण,

	अणुACPI_RSC_2BITFLAG,
	 ACPI_RS_OFFSET(data.start_dpf.perक्रमmance_robustness),
	 AML_OFFSET(start_dpf.flags),
	 2पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_set_start_dpf
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_set_start_dpf[10] = अणु
	/* Start with a शेष descriptor of length 1 */

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_START_DEPENDENT,
	 माप(काष्ठा aml_resource_start_dependent),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_set_start_dpf)पूर्ण,

	/* Set the शेष flag values */

	अणुACPI_RSC_2BITFLAG,
	 ACPI_RS_OFFSET(data.start_dpf.compatibility_priority),
	 AML_OFFSET(start_dpf.flags),
	 0पूर्ण,

	अणुACPI_RSC_2BITFLAG,
	 ACPI_RS_OFFSET(data.start_dpf.perक्रमmance_robustness),
	 AML_OFFSET(start_dpf.flags),
	 2पूर्ण,
	/*
	 * All करोne अगर the output descriptor length is required to be 1
	 * (i.e., optimization to 0 bytes cannot be attempted)
	 */
	अणुACPI_RSC_EXIT_EQ, ACPI_RSC_COMPARE_VALUE,
	 ACPI_RS_OFFSET(data.start_dpf.descriptor_length),
	 1पूर्ण,

	/* Set length to 0 bytes (no flags byte) */

	अणुACPI_RSC_LENGTH, 0, 0,
	 माप(काष्ठा aml_resource_start_dependent_noprio)पूर्ण,

	/*
	 * All करोne अगर the output descriptor length is required to be 0.
	 *
	 * TBD: Perhaps we should check क्रम error अगर input flags are not
	 * compatible with a 0-byte descriptor.
	 */
	अणुACPI_RSC_EXIT_EQ, ACPI_RSC_COMPARE_VALUE,
	 ACPI_RS_OFFSET(data.start_dpf.descriptor_length),
	 0पूर्ण,

	/* Reset length to 1 byte (descriptor with flags byte) */

	अणुACPI_RSC_LENGTH, 0, 0, माप(काष्ठा aml_resource_start_dependent)पूर्ण,

	/*
	 * All करोne अगर flags byte is necessary -- अगर either priority value
	 * is not ACPI_ACCEPTABLE_CONFIGURATION
	 */
	अणुACPI_RSC_EXIT_NE, ACPI_RSC_COMPARE_VALUE,
	 ACPI_RS_OFFSET(data.start_dpf.compatibility_priority),
	 ACPI_ACCEPTABLE_CONFIGURATIONपूर्ण,

	अणुACPI_RSC_EXIT_NE, ACPI_RSC_COMPARE_VALUE,
	 ACPI_RS_OFFSET(data.start_dpf.perक्रमmance_robustness),
	 ACPI_ACCEPTABLE_CONFIGURATIONपूर्ण,

	/* Flag byte is not necessary */

	अणुACPI_RSC_LENGTH, 0, 0,
	 माप(काष्ठा aml_resource_start_dependent_noprio)पूर्ण
पूर्ण;
