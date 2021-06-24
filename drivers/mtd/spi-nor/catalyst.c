<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

अटल स्थिर काष्ठा flash_info catalyst_parts[] = अणु
	/* Catalyst / On Semiconductor -- non-JEDEC */
	अणु "cat25c11", CAT25_INFO(16, 8, 16, 1,
				 SPI_NOR_NO_ERASE | SPI_NOR_NO_FR) पूर्ण,
	अणु "cat25c03", CAT25_INFO(32, 8, 16, 2,
				 SPI_NOR_NO_ERASE | SPI_NOR_NO_FR) पूर्ण,
	अणु "cat25c09", CAT25_INFO(128, 8, 32, 2,
				 SPI_NOR_NO_ERASE | SPI_NOR_NO_FR) पूर्ण,
	अणु "cat25c17", CAT25_INFO(256, 8, 32, 2,
				 SPI_NOR_NO_ERASE | SPI_NOR_NO_FR) पूर्ण,
	अणु "cat25128", CAT25_INFO(2048, 8, 64, 2,
				 SPI_NOR_NO_ERASE | SPI_NOR_NO_FR) पूर्ण,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_catalyst = अणु
	.name = "catalyst",
	.parts = catalyst_parts,
	.nparts = ARRAY_SIZE(catalyst_parts),
पूर्ण;
