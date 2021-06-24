<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

अटल पूर्णांक
is25lp256_post_bfpt_fixups(काष्ठा spi_nor *nor,
			   स्थिर काष्ठा sfdp_parameter_header *bfpt_header,
			   स्थिर काष्ठा sfdp_bfpt *bfpt)
अणु
	/*
	 * IS25LP256 supports 4B opcodes, but the BFPT advertises a
	 * BFPT_DWORD1_ADDRESS_BYTES_3_ONLY address width.
	 * Overग_लिखो the address width advertised by the BFPT.
	 */
	अगर ((bfpt->dwords[BFPT_DWORD(1)] & BFPT_DWORD1_ADDRESS_BYTES_MASK) ==
		BFPT_DWORD1_ADDRESS_BYTES_3_ONLY)
		nor->addr_width = 4;

	वापस 0;
पूर्ण

अटल काष्ठा spi_nor_fixups is25lp256_fixups = अणु
	.post_bfpt = is25lp256_post_bfpt_fixups,
पूर्ण;

अटल स्थिर काष्ठा flash_info issi_parts[] = अणु
	/* ISSI */
	अणु "is25cd512",  INFO(0x7f9d20, 0, 32 * 1024,   2, SECT_4K) पूर्ण,
	अणु "is25lq040b", INFO(0x9d4013, 0, 64 * 1024,   8,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "is25lp016d", INFO(0x9d6015, 0, 64 * 1024,  32,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "is25lp080d", INFO(0x9d6014, 0, 64 * 1024,  16,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "is25lp032",  INFO(0x9d6016, 0, 64 * 1024,  64,
			     SECT_4K | SPI_NOR_DUAL_READ) पूर्ण,
	अणु "is25lp064",  INFO(0x9d6017, 0, 64 * 1024, 128,
			     SECT_4K | SPI_NOR_DUAL_READ) पूर्ण,
	अणु "is25lp128",  INFO(0x9d6018, 0, 64 * 1024, 256,
			     SECT_4K | SPI_NOR_DUAL_READ) पूर्ण,
	अणु "is25lp256",  INFO(0x9d6019, 0, 64 * 1024, 512,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			     SPI_NOR_4B_OPCODES)
		.fixups = &is25lp256_fixups पूर्ण,
	अणु "is25wp032",  INFO(0x9d7016, 0, 64 * 1024,  64,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "is25wp064",  INFO(0x9d7017, 0, 64 * 1024, 128,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "is25wp128",  INFO(0x9d7018, 0, 64 * 1024, 256,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "is25wp256", INFO(0x9d7019, 0, 64 * 1024, 512,
			    SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			    SPI_NOR_4B_OPCODES)
		.fixups = &is25lp256_fixups पूर्ण,

	/* PMC */
	अणु "pm25lv512",   INFO(0,        0, 32 * 1024,    2, SECT_4K_PMC) पूर्ण,
	अणु "pm25lv010",   INFO(0,        0, 32 * 1024,    4, SECT_4K_PMC) पूर्ण,
	अणु "pm25lq032",   INFO(0x7f9d46, 0, 64 * 1024,   64, SECT_4K) पूर्ण,
पूर्ण;

अटल व्योम issi_शेष_init(काष्ठा spi_nor *nor)
अणु
	nor->params->quad_enable = spi_nor_sr1_bit6_quad_enable;
पूर्ण

अटल स्थिर काष्ठा spi_nor_fixups issi_fixups = अणु
	.शेष_init = issi_शेष_init,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_issi = अणु
	.name = "issi",
	.parts = issi_parts,
	.nparts = ARRAY_SIZE(issi_parts),
	.fixups = &issi_fixups,
पूर्ण;
