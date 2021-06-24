<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2018-2020 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#अगर_अघोषित GAUDI_H
#घोषणा GAUDI_H

#घोषणा SRAM_BAR_ID		0
#घोषणा CFG_BAR_ID		2
#घोषणा HBM_BAR_ID		4

#घोषणा SRAM_BAR_SIZE		0x4000000ull		/* 64MB */
#घोषणा CFG_BAR_SIZE		0x8000000ull		/* 128MB */

#घोषणा CFG_BASE		0x7FFC000000ull
#घोषणा CFG_SIZE		0x4000000		/* 32MB CFG + 32MB DBG*/

#घोषणा SRAM_BASE_ADDR		0x7FF0000000ull
#घोषणा SRAM_SIZE		0x1400000		/* 20MB */

#घोषणा SPI_FLASH_BASE_ADDR	0x7FF8000000ull

#घोषणा PSOC_SCRATCHPAD_ADDR	0x7FFBFE0000ull
#घोषणा PSOC_SCRATCHPAD_SIZE	0x10000			/* 64KB */

#घोषणा PCIE_FW_SRAM_ADDR	0x7FFBFF0000ull
#घोषणा PCIE_FW_SRAM_SIZE	0x8000			/* 32KB */

#घोषणा DRAM_PHYS_BASE		0x0ull

#घोषणा HOST_PHYS_BASE		0x8000000000ull		/* 0.5TB */
#घोषणा HOST_PHYS_SIZE		0x1000000000000ull	/* 0.25PB (48 bits) */

#घोषणा GAUDI_MSI_ENTRIES	32

#घोषणा QMAN_PQ_ENTRY_SIZE	16			/* Bytes */

#घोषणा MAX_ASID		2

#घोषणा PROT_BITS_OFFS		0xF80

#घोषणा MME_NUMBER_OF_MASTER_ENGINES	2

#घोषणा MME_NUMBER_OF_SLAVE_ENGINES	2

#घोषणा TPC_NUMBER_OF_ENGINES	8

#घोषणा DMA_NUMBER_OF_CHANNELS	8

#घोषणा NIC_NUMBER_OF_MACROS	5

#घोषणा NIC_NUMBER_OF_ENGINES	(NIC_NUMBER_OF_MACROS * 2)

#घोषणा NUMBER_OF_IF		8

#घोषणा DEVICE_CACHE_LINE_SIZE	128

#पूर्ण_अगर /* GAUDI_H */
