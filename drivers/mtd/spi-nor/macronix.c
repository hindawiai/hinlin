<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

अटल पूर्णांक
mx25l25635_post_bfpt_fixups(काष्ठा spi_nor *nor,
			    स्थिर काष्ठा sfdp_parameter_header *bfpt_header,
			    स्थिर काष्ठा sfdp_bfpt *bfpt)
अणु
	/*
	 * MX25L25635F supports 4B opcodes but MX25L25635E करोes not.
	 * Unक्रमtunately, Macronix has re-used the same JEDEC ID क्रम both
	 * variants which prevents us from defining a new entry in the parts
	 * table.
	 * We need a way to dअगरferentiate MX25L25635E and MX25L25635F, and it
	 * seems that the F version advertises support क्रम Fast Read 4-4-4 in
	 * its BFPT table.
	 */
	अगर (bfpt->dwords[BFPT_DWORD(5)] & BFPT_DWORD5_FAST_READ_4_4_4)
		nor->flags |= SNOR_F_4B_OPCODES;

	वापस 0;
पूर्ण

अटल काष्ठा spi_nor_fixups mx25l25635_fixups = अणु
	.post_bfpt = mx25l25635_post_bfpt_fixups,
पूर्ण;

अटल स्थिर काष्ठा flash_info macronix_parts[] = अणु
	/* Macronix */
	अणु "mx25l512e",   INFO(0xc22010, 0, 64 * 1024,   1, SECT_4K) पूर्ण,
	अणु "mx25l2005a",  INFO(0xc22012, 0, 64 * 1024,   4, SECT_4K) पूर्ण,
	अणु "mx25l4005a",  INFO(0xc22013, 0, 64 * 1024,   8, SECT_4K) पूर्ण,
	अणु "mx25l8005",   INFO(0xc22014, 0, 64 * 1024,  16, 0) पूर्ण,
	अणु "mx25l1606e",  INFO(0xc22015, 0, 64 * 1024,  32, SECT_4K) पूर्ण,
	अणु "mx25l3205d",  INFO(0xc22016, 0, 64 * 1024,  64, SECT_4K) पूर्ण,
	अणु "mx25l3255e",  INFO(0xc29e16, 0, 64 * 1024,  64, SECT_4K) पूर्ण,
	अणु "mx25l6405d",  INFO(0xc22017, 0, 64 * 1024, 128, SECT_4K) पूर्ण,
	अणु "mx25u2033e",  INFO(0xc22532, 0, 64 * 1024,   4, SECT_4K) पूर्ण,
	अणु "mx25u3235f",	 INFO(0xc22536, 0, 64 * 1024,  64,
			      SECT_4K | SPI_NOR_DUAL_READ |
			      SPI_NOR_QUAD_READ) पूर्ण,
	अणु "mx25u4035",   INFO(0xc22533, 0, 64 * 1024,   8, SECT_4K) पूर्ण,
	अणु "mx25u8035",   INFO(0xc22534, 0, 64 * 1024,  16, SECT_4K) पूर्ण,
	अणु "mx25u6435f",  INFO(0xc22537, 0, 64 * 1024, 128, SECT_4K) पूर्ण,
	अणु "mx25l12805d", INFO(0xc22018, 0, 64 * 1024, 256, SECT_4K) पूर्ण,
	अणु "mx25l12855e", INFO(0xc22618, 0, 64 * 1024, 256, 0) पूर्ण,
	अणु "mx25r1635f",  INFO(0xc22815, 0, 64 * 1024,  32,
			      SECT_4K | SPI_NOR_DUAL_READ |
			      SPI_NOR_QUAD_READ) पूर्ण,
	अणु "mx25r3235f",  INFO(0xc22816, 0, 64 * 1024,  64,
			      SECT_4K | SPI_NOR_DUAL_READ |
			      SPI_NOR_QUAD_READ) पूर्ण,
	अणु "mx25u12835f", INFO(0xc22538, 0, 64 * 1024, 256,
			      SECT_4K | SPI_NOR_DUAL_READ |
			      SPI_NOR_QUAD_READ) पूर्ण,
	अणु "mx25l25635e", INFO(0xc22019, 0, 64 * 1024, 512,
			      SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ)
		.fixups = &mx25l25635_fixups पूर्ण,
	अणु "mx25u25635f", INFO(0xc22539, 0, 64 * 1024, 512,
			      SECT_4K | SPI_NOR_4B_OPCODES) पूर्ण,
	अणु "mx25u51245g", INFO(0xc2253a, 0, 64 * 1024, 1024,
			      SECT_4K | SPI_NOR_DUAL_READ |
			      SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES) पूर्ण,
	अणु "mx25v8035f",  INFO(0xc22314, 0, 64 * 1024,  16,
			      SECT_4K | SPI_NOR_DUAL_READ |
			      SPI_NOR_QUAD_READ) पूर्ण,
	अणु "mx25l25655e", INFO(0xc22619, 0, 64 * 1024, 512, 0) पूर्ण,
	अणु "mx66l51235l", INFO(0xc2201a, 0, 64 * 1024, 1024,
			      SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			      SPI_NOR_4B_OPCODES) पूर्ण,
	अणु "mx66u51235f", INFO(0xc2253a, 0, 64 * 1024, 1024,
			      SECT_4K | SPI_NOR_DUAL_READ |
			      SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES) पूर्ण,
	अणु "mx66l1g45g",  INFO(0xc2201b, 0, 64 * 1024, 2048,
			      SECT_4K | SPI_NOR_DUAL_READ |
			      SPI_NOR_QUAD_READ) पूर्ण,
	अणु "mx66l1g55g",  INFO(0xc2261b, 0, 64 * 1024, 2048,
			      SPI_NOR_QUAD_READ) पूर्ण,
	अणु "mx66u2g45g",	 INFO(0xc2253c, 0, 64 * 1024, 4096,
			      SECT_4K | SPI_NOR_DUAL_READ |
			      SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES) पूर्ण,
पूर्ण;

अटल व्योम macronix_शेष_init(काष्ठा spi_nor *nor)
अणु
	nor->params->quad_enable = spi_nor_sr1_bit6_quad_enable;
	nor->params->set_4byte_addr_mode = spi_nor_set_4byte_addr_mode;
पूर्ण

अटल स्थिर काष्ठा spi_nor_fixups macronix_fixups = अणु
	.शेष_init = macronix_शेष_init,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_macronix = अणु
	.name = "macronix",
	.parts = macronix_parts,
	.nparts = ARRAY_SIZE(macronix_parts),
	.fixups = &macronix_fixups,
पूर्ण;
