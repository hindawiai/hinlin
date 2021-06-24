<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0
 *
 * Copyright 2016-2019 HabanaLअसल, Ltd.
 * All Rights Reserved.
 *
 */

#अगर_अघोषित GOYA_H
#घोषणा GOYA_H

#घोषणा SRAM_CFG_BAR_ID		0
#घोषणा MSIX_BAR_ID		2
#घोषणा DDR_BAR_ID		4

#घोषणा CFG_BAR_SIZE		0x10000000ull		/* 256MB */
#घोषणा MSIX_BAR_SIZE		0x1000ull		/* 4KB */

#घोषणा CFG_BASE		0x7FFC000000ull
#घोषणा CFG_SIZE		0x4000000		/* 32MB CFG + 32MB DBG*/

#घोषणा SRAM_BASE_ADDR		0x7FF0000000ull
#घोषणा SRAM_SIZE		0x32A0000		/* 50.625MB */

#घोषणा DRAM_PHYS_BASE		0x0ull

#घोषणा HOST_PHYS_BASE		0x8000000000ull		/* 0.5TB */
#घोषणा HOST_PHYS_SIZE		0x1000000000000ull	/* 0.25PB (48 bits) */

#घोषणा GOYA_MSIX_ENTRIES	8

#घोषणा QMAN_PQ_ENTRY_SIZE	16			/* Bytes */

#घोषणा MAX_ASID		2

#घोषणा PROT_BITS_OFFS		0xF80

#घोषणा DMA_MAX_NUM		5

#घोषणा TPC_MAX_NUM		8

#घोषणा MME_MAX_NUM		1

#पूर्ण_अगर /* GOYA_H */
