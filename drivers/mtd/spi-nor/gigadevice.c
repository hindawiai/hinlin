<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

अटल व्योम gd25q256_शेष_init(काष्ठा spi_nor *nor)
अणु
	/*
	 * Some manufacturer like GigaDevice may use dअगरferent
	 * bit to set QE on dअगरferent memories, so the MFR can't
	 * indicate the quad_enable method क्रम this हाल, we need
	 * to set it in the शेष_init fixup hook.
	 */
	nor->params->quad_enable = spi_nor_sr1_bit6_quad_enable;
पूर्ण

अटल काष्ठा spi_nor_fixups gd25q256_fixups = अणु
	.शेष_init = gd25q256_शेष_init,
पूर्ण;

अटल स्थिर काष्ठा flash_info gigadevice_parts[] = अणु
	अणु "gd25q16", INFO(0xc84015, 0, 64 * 1024,  32,
			  SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			  SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) पूर्ण,
	अणु "gd25q32", INFO(0xc84016, 0, 64 * 1024,  64,
			  SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			  SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) पूर्ण,
	अणु "gd25lq32", INFO(0xc86016, 0, 64 * 1024, 64,
			   SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			   SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) पूर्ण,
	अणु "gd25q64", INFO(0xc84017, 0, 64 * 1024, 128,
			  SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			  SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) पूर्ण,
	अणु "gd25lq64c", INFO(0xc86017, 0, 64 * 1024, 128,
			    SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			    SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) पूर्ण,
	अणु "gd25lq128d", INFO(0xc86018, 0, 64 * 1024, 256,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			     SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) पूर्ण,
	अणु "gd25q128", INFO(0xc84018, 0, 64 * 1024, 256,
			   SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			   SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) पूर्ण,
	अणु "gd25q256", INFO(0xc84019, 0, 64 * 1024, 512,
			   SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			   SPI_NOR_4B_OPCODES | SPI_NOR_HAS_LOCK |
			   SPI_NOR_HAS_TB | SPI_NOR_TB_SR_BIT6)
		.fixups = &gd25q256_fixups पूर्ण,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_gigadevice = अणु
	.name = "gigadevice",
	.parts = gigadevice_parts,
	.nparts = ARRAY_SIZE(gigadevice_parts),
पूर्ण;
