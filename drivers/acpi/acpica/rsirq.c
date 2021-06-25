<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/*******************************************************************************
 *
 * Module Name: rsirq - IRQ resource descriptors
 *
 ******************************************************************************/

#समावेश <acpi/acpi.h>
#समावेश "accommon.h"
#समावेश "acresrc.h"

#घोषणा _COMPONENT          ACPI_RESOURCES
ACPI_MODULE_NAME("rsirq")

/*******************************************************************************
 *
 * acpi_rs_get_irq
 *
 ******************************************************************************/
काष्ठा acpi_rsconvert_info acpi_rs_get_irq[9] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_IRQ,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_irq),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_get_irq)पूर्ण,

	/* Get the IRQ mask (bytes 1:2) */

	अणुACPI_RSC_BITMASK16, ACPI_RS_OFFSET(data.irq.पूर्णांकerrupts[0]),
	 AML_OFFSET(irq.irq_mask),
	 ACPI_RS_OFFSET(data.irq.पूर्णांकerrupt_count)पूर्ण,

	/* Set शेष flags (others are zero) */

	अणुACPI_RSC_SET8, ACPI_RS_OFFSET(data.irq.triggering),
	 ACPI_EDGE_SENSITIVE,
	 1पूर्ण,

	/* Get the descriptor length (2 or 3 क्रम IRQ descriptor) */

	अणुACPI_RSC_2BITFLAG, ACPI_RS_OFFSET(data.irq.descriptor_length),
	 AML_OFFSET(irq.descriptor_type),
	 0पूर्ण,

	/* All करोne अगर no flag byte present in descriptor */

	अणुACPI_RSC_EXIT_NE, ACPI_RSC_COMPARE_AML_LENGTH, 0, 3पूर्ण,

	/* Get flags: Triggering[0], Polarity[3], Sharing[4], Wake[5] */

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.irq.triggering),
	 AML_OFFSET(irq.flags),
	 0पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.irq.polarity),
	 AML_OFFSET(irq.flags),
	 3पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.irq.shareable),
	 AML_OFFSET(irq.flags),
	 4पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.irq.wake_capable),
	 AML_OFFSET(irq.flags),
	 5पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_set_irq
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_set_irq[14] = अणु
	/* Start with a शेष descriptor of length 3 */

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_IRQ,
	 माप(काष्ठा aml_resource_irq),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_set_irq)पूर्ण,

	/* Convert पूर्णांकerrupt list to 16-bit IRQ biपंचांगask */

	अणुACPI_RSC_BITMASK16, ACPI_RS_OFFSET(data.irq.पूर्णांकerrupts[0]),
	 AML_OFFSET(irq.irq_mask),
	 ACPI_RS_OFFSET(data.irq.पूर्णांकerrupt_count)पूर्ण,

	/* Set flags: Triggering[0], Polarity[3], Sharing[4], Wake[5] */

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.irq.triggering),
	 AML_OFFSET(irq.flags),
	 0पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.irq.polarity),
	 AML_OFFSET(irq.flags),
	 3पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.irq.shareable),
	 AML_OFFSET(irq.flags),
	 4पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.irq.wake_capable),
	 AML_OFFSET(irq.flags),
	 5पूर्ण,

	/*
	 * All करोne अगर the output descriptor length is required to be 3
	 * (i.e., optimization to 2 bytes cannot be attempted)
	 */
	अणुACPI_RSC_EXIT_EQ, ACPI_RSC_COMPARE_VALUE,
	 ACPI_RS_OFFSET(data.irq.descriptor_length),
	 3पूर्ण,

	/* Set length to 2 bytes (no flags byte) */

	अणुACPI_RSC_LENGTH, 0, 0, माप(काष्ठा aml_resource_irq_noflags)पूर्ण,

	/*
	 * All करोne अगर the output descriptor length is required to be 2.
	 *
	 * TBD: Perhaps we should check क्रम error अगर input flags are not
	 * compatible with a 2-byte descriptor.
	 */
	अणुACPI_RSC_EXIT_EQ, ACPI_RSC_COMPARE_VALUE,
	 ACPI_RS_OFFSET(data.irq.descriptor_length),
	 2पूर्ण,

	/* Reset length to 3 bytes (descriptor with flags byte) */

	अणुACPI_RSC_LENGTH, 0, 0, माप(काष्ठा aml_resource_irq)पूर्ण,

	/*
	 * Check अगर the flags byte is necessary. Not needed अगर the flags are:
	 * ACPI_EDGE_SENSITIVE, ACPI_ACTIVE_HIGH, ACPI_EXCLUSIVE
	 */
	अणुACPI_RSC_EXIT_NE, ACPI_RSC_COMPARE_VALUE,
	 ACPI_RS_OFFSET(data.irq.triggering),
	 ACPI_EDGE_SENSITIVEपूर्ण,

	अणुACPI_RSC_EXIT_NE, ACPI_RSC_COMPARE_VALUE,
	 ACPI_RS_OFFSET(data.irq.polarity),
	 ACPI_ACTIVE_HIGHपूर्ण,

	अणुACPI_RSC_EXIT_NE, ACPI_RSC_COMPARE_VALUE,
	 ACPI_RS_OFFSET(data.irq.shareable),
	 ACPI_EXCLUSIVEपूर्ण,

	/* We can optimize to a 2-byte irq_no_flags() descriptor */

	अणुACPI_RSC_LENGTH, 0, 0, माप(काष्ठा aml_resource_irq_noflags)पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_ext_irq
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_ext_irq[10] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_EXTENDED_IRQ,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_extended_irq),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_ext_irq)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_EXTENDED_IRQ,
	 माप(काष्ठा aml_resource_extended_irq),
	 0पूर्ण,

	/*
	 * Flags: Producer/Consumer[0], Triggering[1], Polarity[2],
	 *        Sharing[3], Wake[4]
	 */
	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.extended_irq.producer_consumer),
	 AML_OFFSET(extended_irq.flags),
	 0पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.extended_irq.triggering),
	 AML_OFFSET(extended_irq.flags),
	 1पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.extended_irq.polarity),
	 AML_OFFSET(extended_irq.flags),
	 2पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.extended_irq.shareable),
	 AML_OFFSET(extended_irq.flags),
	 3पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.extended_irq.wake_capable),
	 AML_OFFSET(extended_irq.flags),
	 4पूर्ण,

	/* IRQ Table length (Byte4) */

	अणुACPI_RSC_COUNT, ACPI_RS_OFFSET(data.extended_irq.पूर्णांकerrupt_count),
	 AML_OFFSET(extended_irq.पूर्णांकerrupt_count),
	 माप(u32)पूर्ण,

	/* Copy every IRQ in the table, each is 32 bits */

	अणुACPI_RSC_MOVE32, ACPI_RS_OFFSET(data.extended_irq.पूर्णांकerrupts[0]),
	 AML_OFFSET(extended_irq.पूर्णांकerrupts[0]),
	 0पूर्ण,

	/* Optional resource_source (Index and String) */

	अणुACPI_RSC_SOURCEX, ACPI_RS_OFFSET(data.extended_irq.resource_source),
	 ACPI_RS_OFFSET(data.extended_irq.पूर्णांकerrupts[0]),
	 माप(काष्ठा aml_resource_extended_irq)पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_dma
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_dma[6] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_DMA,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_dma),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_dma)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_DMA,
	 माप(काष्ठा aml_resource_dma),
	 0पूर्ण,

	/* Flags: transfer preference, bus mastering, channel speed */

	अणुACPI_RSC_2BITFLAG, ACPI_RS_OFFSET(data.dma.transfer),
	 AML_OFFSET(dma.flags),
	 0पूर्ण,

	अणुACPI_RSC_1BITFLAG, ACPI_RS_OFFSET(data.dma.bus_master),
	 AML_OFFSET(dma.flags),
	 2पूर्ण,

	अणुACPI_RSC_2BITFLAG, ACPI_RS_OFFSET(data.dma.type),
	 AML_OFFSET(dma.flags),
	 5पूर्ण,

	/* DMA channel mask bits */

	अणुACPI_RSC_BITMASK, ACPI_RS_OFFSET(data.dma.channels[0]),
	 AML_OFFSET(dma.dma_channel_mask),
	 ACPI_RS_OFFSET(data.dma.channel_count)पूर्ण
पूर्ण;

/*******************************************************************************
 *
 * acpi_rs_convert_fixed_dma
 *
 ******************************************************************************/

काष्ठा acpi_rsconvert_info acpi_rs_convert_fixed_dma[4] = अणु
	अणुACPI_RSC_INITGET, ACPI_RESOURCE_TYPE_FIXED_DMA,
	 ACPI_RS_SIZE(काष्ठा acpi_resource_fixed_dma),
	 ACPI_RSC_TABLE_SIZE(acpi_rs_convert_fixed_dma)पूर्ण,

	अणुACPI_RSC_INITSET, ACPI_RESOURCE_NAME_FIXED_DMA,
	 माप(काष्ठा aml_resource_fixed_dma),
	 0पूर्ण,

	/*
	 * These fields are contiguous in both the source and destination:
	 * request_lines
	 * Channels
	 */
	अणुACPI_RSC_MOVE16, ACPI_RS_OFFSET(data.fixed_dma.request_lines),
	 AML_OFFSET(fixed_dma.request_lines),
	 2पूर्ण,

	अणुACPI_RSC_MOVE8, ACPI_RS_OFFSET(data.fixed_dma.width),
	 AML_OFFSET(fixed_dma.width),
	 1पूर्ण,
पूर्ण;
