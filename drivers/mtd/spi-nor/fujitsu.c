<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

अटल स्थिर काष्ठा flash_info fujitsu_parts[] = अणु
	/* Fujitsu */
	अणु "mb85rs1mt", INFO(0x047f27, 0, 128 * 1024, 1, SPI_NOR_NO_ERASE) पूर्ण,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_fujitsu = अणु
	.name = "fujitsu",
	.parts = fujitsu_parts,
	.nparts = ARRAY_SIZE(fujitsu_parts),
पूर्ण;
