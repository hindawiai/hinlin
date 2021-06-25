<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: rsmem24 - Memory resource descriptors
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acresrc.h"

#घोषणा _COMPONENT          ACPI_RESOURCES
ACPI_MODULE_NAME("rsmemory")

/*******************************************************************************
 *
 * acpi_rs_convert_memory24
 *
 ******************************************************************************/
काष्ठा acpi_rsconvert_info acpi_rs_convert_memory24[4] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_MEMORY24,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_memory24),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_memory24)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_MEMORY24,
	 माप(काष्ठा aml_resource_memory24),
	 0पूर्ण,

	/* Read/Write bit */

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.memory24.ग_लिखो_protect),
	 AML_OFFSET(memory24.flags),
	 0पूर्ण,
	/*
	 * These fields are contiguous in both the source and destination:
	 * Minimum Base Address
	 * Maximum Base Address
	 * Address Base Alignment
	 * Range Length
	 */
	अणुACPI_RSC_MOVE16, ACPI_RS_OFFSET(data.memory24.minimum),
	 AML_OFFSET(memory24.minimum),
	 4पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_memory32
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_memory32[4] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_MEMORY32,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_memory32),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_memory32)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_MEMORY32,
	 माप(काष्ठा aml_resource_memory32),
	 0पूर्ण,

	/* Read/Write bit */

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.memory32.ग_लिखो_protect),
	 AML_OFFSET(memory32.flags),
	 0पूर्ण,
	/*
	 * These fields are contiguous in both the source and destination:
	 * Minimum Base Address
	 * Maximum Base Address
	 * Address Base Alignment
	 * Range Length
	 */
	अणुACPI_RSC_MOVE32, ACPI_RS_OFFSET(data.memory32.minimum),
	 AML_OFFSET(memory32.minimum),
	 4पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_fixed_memory32
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_fixed_memory32[4] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_FIXED_MEMORY32,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_fixed_memory32),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_fixed_memory32)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_FIXED_MEMORY32,
	 माप(काष्ठा aml_resource_fixed_memory32),
	 0पूर्ण,

	/* Read/Write bit */

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.fixed_memory32.ग_लिखो_protect),
	 AML_OFFSET(fixed_memory32.flags),
	 0पूर्ण,
	/*
	 * These fields are contiguous in both the source and destination:
	 * Base Address
	 * Range Length
	 */
	अणुACPI_RSC_MOVE32, ACPI_RS_OFFSET(data.fixed_memory32.address),
	 AML_OFFSET(fixed_memory32.address),
	 2पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_get_venकरोr_small
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_get_venकरोr_small[3] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_VENDOR,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_venकरोr),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_get_venकरोr_small)पूर्ण,

	/* Length of the venकरोr data (byte count) */

	अणुACPI_RSC_COUNT16, ACPI_RS_OFFSET(data.venकरोr.byte_length),
	 0,
	 माप(u8)पूर्ण,

	/* Venकरोr data */

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.venकरोr.byte_data[0]),
	 माप(काष्ठा aml_resource_small_header),
	 0पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_get_venकरोr_large
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_get_venकरोr_large[3] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_VENDOR,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_venकरोr),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_get_venकरोr_large)पूर्ण,

	/* Length of the venकरोr data (byte count) */

	अणुACPI_RSC_COUNT16, ACPI_RS_OFFSET(data.venकरोr.byte_length),
	 0,
	 माप(u8)पूर्ण,

	/* Venकरोr data */

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.venकरोr.byte_data[0]),
	 माप(काष्ठा aml_resource_large_header),
	 0पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_set_venकरोr
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_set_venकरोr[7] = अणु
	/* Default is a small venकरोr descriptor */

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_VENDOR_SMALL,
	 माप(काष्ठा aml_resource_small_header),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_set_venकरोr)पूर्ण,

	/* Get the length and copy the data */

	अणुACPI_RSC_COUNT16, ACPI_RS_OFFSET(data.venकरोr.byte_length),
	 0,
	 0पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.venकरोr.byte_data[0]),
	 माप(काष्ठा aml_resource_small_header),
	 0पूर्ण,

	/*
	 * All करोne अगर the Venकरोr byte length is 7 or less, meaning that it will
	 * fit within a small descriptor
	 */
	अणुACPI_RSC_EXIT_LE, 0, 0, 7पूर्ण,

	/* Must create a large venकरोr descriptor */

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_VENDOR_LARGE,
	 माप(काष्ठा aml_resource_large_header),
	 0पूर्ण,

	अणुACPI_RSC_COUNT16, ACPI_RS_OFFSET(data.venकरोr.byte_length),
	 0,
	 0पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.venकरोr.byte_data[0]),
	 माप(काष्ठा aml_resource_large_header),
	 0पूर्ण
पूर्ण;
