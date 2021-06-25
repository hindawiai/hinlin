<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

अटल स्थिर काष्ठा flash_info पूर्णांकel_parts[] = अणु
	/* Intel/Numonyx -- xxxs33b */
	अणु "160s33b",  INFO(0x898911, 0, 64 * 1024,  32,
			   SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE) पूर्ण,
	अणु "320s33b",  INFO(0x898912, 0, 64 * 1024,  64,
			   SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE) पूर्ण,
	अणु "640s33b",  INFO(0x898913, 0, 64 * 1024, 128,
			   SPI_NOR_HAS_LOCK | SPI_NOR_SWP_IS_VOLATILE) पूर्ण,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_पूर्णांकel = अणु
	.name = "intel",
	.parts = पूर्णांकel_parts,
	.nparts = ARRAY_SIZE(पूर्णांकel_parts),
पूर्ण;
