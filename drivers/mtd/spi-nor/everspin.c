<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

अटल स्थिर काष्ठा flash_info everspin_parts[] = अणु
	/* Everspin */
	अणु "mr25h128", CAT25_INFO(16 * 1024, 1, 256, 2,
				 SPI_NOR_NO_ERASE | SPI_NOR_NO_FR) पूर्ण,
	अणु "mr25h256", CAT25_INFO(32 * 1024, 1, 256, 2,
				 SPI_NOR_NO_ERASE | SPI_NOR_NO_FR) पूर्ण,
	अणु "mr25h10",  CAT25_INFO(128 * 1024, 1, 256, 3,
				 SPI_NOR_NO_ERASE | SPI_NOR_NO_FR) पूर्ण,
	अणु "mr25h40",  CAT25_INFO(512 * 1024, 1, 256, 3,
				 SPI_NOR_NO_ERASE | SPI_NOR_NO_FR) पूर्ण,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_everspin = अणु
	.name = "everspin",
	.parts = everspin_parts,
	.nparts = ARRAY_SIZE(everspin_parts),
पूर्ण;
