<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

अटल स्थिर काष्ठा flash_info xmc_parts[] = अणु
	/* XMC (Wuhan Xinxin Semiconductor Manufacturing Corp.) */
	अणु "XM25QH64A", INFO(0x207017, 0, 64 * 1024, 128,
			    SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "XM25QH128A", INFO(0x207018, 0, 64 * 1024, 256,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_xmc = अणु
	.name = "xmc",
	.parts = xmc_parts,
	.nparts = ARRAY_SIZE(xmc_parts),
पूर्ण;
