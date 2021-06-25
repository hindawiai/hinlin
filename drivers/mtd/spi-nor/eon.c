<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

अटल स्थिर काष्ठा flash_info eon_parts[] = अणु
	/* EON -- en25xxx */
	अणु "en25f32",    INFO(0x1c3116, 0, 64 * 1024,   64, SECT_4K) पूर्ण,
	अणु "en25p32",    INFO(0x1c2016, 0, 64 * 1024,   64, 0) पूर्ण,
	अणु "en25q32b",   INFO(0x1c3016, 0, 64 * 1024,   64, 0) पूर्ण,
	अणु "en25p64",    INFO(0x1c2017, 0, 64 * 1024,  128, 0) पूर्ण,
	अणु "en25q64",    INFO(0x1c3017, 0, 64 * 1024,  128, SECT_4K) पूर्ण,
	अणु "en25q80a",   INFO(0x1c3014, 0, 64 * 1024,   16,
			     SECT_4K | SPI_NOR_DUAL_READ) पूर्ण,
	अणु "en25qh16",   INFO(0x1c7015, 0, 64 * 1024,   32,
			     SECT_4K | SPI_NOR_DUAL_READ) पूर्ण,
	अणु "en25qh32",   INFO(0x1c7016, 0, 64 * 1024,   64, 0) पूर्ण,
	अणु "en25qh64",   INFO(0x1c7017, 0, 64 * 1024,  128,
			     SECT_4K | SPI_NOR_DUAL_READ) पूर्ण,
	अणु "en25qh128",  INFO(0x1c7018, 0, 64 * 1024,  256, 0) पूर्ण,
	अणु "en25qh256",  INFO(0x1c7019, 0, 64 * 1024,  512, 0) पूर्ण,
	अणु "en25s64",	INFO(0x1c3817, 0, 64 * 1024,  128, SECT_4K) पूर्ण,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_eon = अणु
	.name = "eon",
	.parts = eon_parts,
	.nparts = ARRAY_SIZE(eon_parts),
पूर्ण;
