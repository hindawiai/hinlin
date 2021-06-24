<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

अटल स्थिर काष्ठा flash_info esmt_parts[] = अणु
	/* ESMT */
	अणु "f25l32pa", INFO(0x8c2016, 0, 64 * 1024, 64,
			   SECT_4K | SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE) पूर्ण,
	अणु "f25l32qa", INFO(0x8c4116, 0, 64 * 1024, 64,
			   SECT_4K | SPI_NOR_HAS_LOCK) पूर्ण,
	अणु "f25l64qa", INFO(0x8c4117, 0, 64 * 1024, 128,
			   SECT_4K | SPI_NOR_HAS_LOCK) पूर्ण,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_esmt = अणु
	.name = "esmt",
	.parts = esmt_parts,
	.nparts = ARRAY_SIZE(esmt_parts),
पूर्ण;
