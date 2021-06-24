<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

#घोषणा SPINOR_OP_RD_ANY_REG			0x65	/* Read any रेजिस्टर */
#घोषणा SPINOR_OP_WR_ANY_REG			0x71	/* Write any रेजिस्टर */
#घोषणा SPINOR_REG_CYPRESS_CFR2V		0x00800003
#घोषणा SPINOR_REG_CYPRESS_CFR2V_MEMLAT_11_24	0xb
#घोषणा SPINOR_REG_CYPRESS_CFR3V		0x00800004
#घोषणा SPINOR_REG_CYPRESS_CFR3V_PGSZ		BIT(4) /* Page size. */
#घोषणा SPINOR_REG_CYPRESS_CFR5V		0x00800006
#घोषणा SPINOR_REG_CYPRESS_CFR5V_OCT_DTR_EN	0x3
#घोषणा SPINOR_REG_CYPRESS_CFR5V_OCT_DTR_DS	0
#घोषणा SPINOR_OP_CYPRESS_RD_FAST		0xee

/**
 * spi_nor_cypress_octal_dtr_enable() - Enable octal DTR on Cypress flashes.
 * @nor:		poपूर्णांकer to a 'struct spi_nor'
 * @enable:              whether to enable or disable Octal DTR
 *
 * This also sets the memory access latency cycles to 24 to allow the flash to
 * run at up to 200MHz.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक spi_nor_cypress_octal_dtr_enable(काष्ठा spi_nor *nor, bool enable)
अणु
	काष्ठा spi_mem_op op;
	u8 *buf = nor->bouncebuf;
	पूर्णांक ret;

	अगर (enable) अणु
		/* Use 24 dummy cycles क्रम memory array पढ़ोs. */
		ret = spi_nor_ग_लिखो_enable(nor);
		अगर (ret)
			वापस ret;

		*buf = SPINOR_REG_CYPRESS_CFR2V_MEMLAT_11_24;
		op = (काष्ठा spi_mem_op)
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_WR_ANY_REG, 1),
				   SPI_MEM_OP_ADDR(3, SPINOR_REG_CYPRESS_CFR2V,
						   1),
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_DATA_OUT(1, buf, 1));

		ret = spi_mem_exec_op(nor->spimem, &op);
		अगर (ret)
			वापस ret;

		ret = spi_nor_रुको_till_पढ़ोy(nor);
		अगर (ret)
			वापस ret;

		nor->पढ़ो_dummy = 24;
	पूर्ण

	/* Set/unset the octal and DTR enable bits. */
	ret = spi_nor_ग_लिखो_enable(nor);
	अगर (ret)
		वापस ret;

	अगर (enable)
		*buf = SPINOR_REG_CYPRESS_CFR5V_OCT_DTR_EN;
	अन्यथा
		*buf = SPINOR_REG_CYPRESS_CFR5V_OCT_DTR_DS;

	op = (काष्ठा spi_mem_op)
		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_WR_ANY_REG, 1),
			   SPI_MEM_OP_ADDR(enable ? 3 : 4,
					   SPINOR_REG_CYPRESS_CFR5V,
					   1),
			   SPI_MEM_OP_NO_DUMMY,
			   SPI_MEM_OP_DATA_OUT(1, buf, 1));

	अगर (!enable)
		spi_nor_spimem_setup_op(nor, &op, SNOR_PROTO_8_8_8_DTR);

	ret = spi_mem_exec_op(nor->spimem, &op);
	अगर (ret)
		वापस ret;

	/* Read flash ID to make sure the चयन was successful. */
	op = (काष्ठा spi_mem_op)
		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_RDID, 1),
			   SPI_MEM_OP_ADDR(enable ? 4 : 0, 0, 1),
			   SPI_MEM_OP_DUMMY(enable ? 3 : 0, 1),
			   SPI_MEM_OP_DATA_IN(round_up(nor->info->id_len, 2),
					      buf, 1));

	अगर (enable)
		spi_nor_spimem_setup_op(nor, &op, SNOR_PROTO_8_8_8_DTR);

	ret = spi_mem_exec_op(nor->spimem, &op);
	अगर (ret)
		वापस ret;

	अगर (स_भेद(buf, nor->info->id, nor->info->id_len))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल व्योम s28hs512t_शेष_init(काष्ठा spi_nor *nor)
अणु
	nor->params->octal_dtr_enable = spi_nor_cypress_octal_dtr_enable;
	nor->params->ग_लिखोsize = 16;
पूर्ण

अटल व्योम s28hs512t_post_sfdp_fixup(काष्ठा spi_nor *nor)
अणु
	/*
	 * On older versions of the flash the xSPI Profile 1.0 table has the
	 * 8D-8D-8D Fast Read opcode as 0x00. But it actually should be 0xEE.
	 */
	अगर (nor->params->पढ़ोs[SNOR_CMD_READ_8_8_8_DTR].opcode == 0)
		nor->params->पढ़ोs[SNOR_CMD_READ_8_8_8_DTR].opcode =
			SPINOR_OP_CYPRESS_RD_FAST;

	/* This flash is also missing the 4-byte Page Program opcode bit. */
	spi_nor_set_pp_settings(&nor->params->page_programs[SNOR_CMD_PP],
				SPINOR_OP_PP_4B, SNOR_PROTO_1_1_1);
	/*
	 * Since xSPI Page Program opcode is backward compatible with
	 * Legacy SPI, use Legacy SPI opcode there as well.
	 */
	spi_nor_set_pp_settings(&nor->params->page_programs[SNOR_CMD_PP_8_8_8_DTR],
				SPINOR_OP_PP_4B, SNOR_PROTO_8_8_8_DTR);

	/*
	 * The xSPI Profile 1.0 table advertises the number of additional
	 * address bytes needed क्रम Read Status Register command as 0 but the
	 * actual value क्रम that is 4.
	 */
	nor->params->rdsr_addr_nbytes = 4;
पूर्ण

अटल पूर्णांक s28hs512t_post_bfpt_fixup(काष्ठा spi_nor *nor,
				     स्थिर काष्ठा sfdp_parameter_header *bfpt_header,
				     स्थिर काष्ठा sfdp_bfpt *bfpt)
अणु
	/*
	 * The BFPT table advertises a 512B page size but the page size is
	 * actually configurable (with the शेष being 256B). Read from
	 * CFR3V[4] and set the correct size.
	 */
	काष्ठा spi_mem_op op =
		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_RD_ANY_REG, 1),
			   SPI_MEM_OP_ADDR(3, SPINOR_REG_CYPRESS_CFR3V, 1),
			   SPI_MEM_OP_NO_DUMMY,
			   SPI_MEM_OP_DATA_IN(1, nor->bouncebuf, 1));
	पूर्णांक ret;

	ret = spi_mem_exec_op(nor->spimem, &op);
	अगर (ret)
		वापस ret;

	अगर (nor->bouncebuf[0] & SPINOR_REG_CYPRESS_CFR3V_PGSZ)
		nor->params->page_size = 512;
	अन्यथा
		nor->params->page_size = 256;

	वापस 0;
पूर्ण

अटल काष्ठा spi_nor_fixups s28hs512t_fixups = अणु
	.शेष_init = s28hs512t_शेष_init,
	.post_sfdp = s28hs512t_post_sfdp_fixup,
	.post_bfpt = s28hs512t_post_bfpt_fixup,
पूर्ण;

अटल पूर्णांक
s25fs_s_post_bfpt_fixups(काष्ठा spi_nor *nor,
			 स्थिर काष्ठा sfdp_parameter_header *bfpt_header,
			 स्थिर काष्ठा sfdp_bfpt *bfpt)
अणु
	/*
	 * The S25FS-S chip family reports 512-byte pages in BFPT but
	 * in reality the ग_लिखो buffer still wraps at the safe शेष
	 * of 256 bytes.  Overग_लिखो the page size advertised by BFPT
	 * to get the ग_लिखोs working.
	 */
	nor->params->page_size = 256;

	वापस 0;
पूर्ण

अटल काष्ठा spi_nor_fixups s25fs_s_fixups = अणु
	.post_bfpt = s25fs_s_post_bfpt_fixups,
पूर्ण;

अटल स्थिर काष्ठा flash_info spansion_parts[] = अणु
	/* Spansion/Cypress -- single (large) sector size only, at least
	 * क्रम the chips listed here (without boot sectors).
	 */
	अणु "s25sl032p",  INFO(0x010215, 0x4d00,  64 * 1024,  64,
			     SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "s25sl064p",  INFO(0x010216, 0x4d00,  64 * 1024, 128,
			     SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "s25fl128s0", INFO6(0x012018, 0x4d0080, 256 * 1024, 64,
			      SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			      USE_CLSR) पूर्ण,
	अणु "s25fl128s1", INFO6(0x012018, 0x4d0180, 64 * 1024, 256,
			      SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			      USE_CLSR) पूर्ण,
	अणु "s25fl256s0", INFO6(0x010219, 0x4d0080, 256 * 1024, 128,
			      SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			      USE_CLSR) पूर्ण,
	अणु "s25fl256s1", INFO6(0x010219, 0x4d0180, 64 * 1024, 512,
			      SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			      USE_CLSR) पूर्ण,
	अणु "s25fl512s",  INFO6(0x010220, 0x4d0080, 256 * 1024, 256,
			      SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			      SPI_NOR_HAS_LOCK | USE_CLSR) पूर्ण,
	अणु "s25fs128s1", INFO6(0x012018, 0x4d0181, 64 * 1024, 256,
			      SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | USE_CLSR)
	  .fixups = &s25fs_s_fixups, पूर्ण,
	अणु "s25fs256s0", INFO6(0x010219, 0x4d0081, 256 * 1024, 128,
			      SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			      USE_CLSR) पूर्ण,
	अणु "s25fs256s1", INFO6(0x010219, 0x4d0181, 64 * 1024, 512,
			      SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			      USE_CLSR) पूर्ण,
	अणु "s25fs512s",  INFO6(0x010220, 0x4d0081, 256 * 1024, 256,
			      SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ | USE_CLSR)
	  .fixups = &s25fs_s_fixups, पूर्ण,
	अणु "s25sl12800", INFO(0x012018, 0x0300, 256 * 1024,  64, 0) पूर्ण,
	अणु "s25sl12801", INFO(0x012018, 0x0301,  64 * 1024, 256, 0) पूर्ण,
	अणु "s25fl129p0", INFO(0x012018, 0x4d00, 256 * 1024,  64,
			     SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			     USE_CLSR) पूर्ण,
	अणु "s25fl129p1", INFO(0x012018, 0x4d01,  64 * 1024, 256,
			     SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			     USE_CLSR) पूर्ण,
	अणु "s25sl004a",  INFO(0x010212,      0,  64 * 1024,   8, 0) पूर्ण,
	अणु "s25sl008a",  INFO(0x010213,      0,  64 * 1024,  16, 0) पूर्ण,
	अणु "s25sl016a",  INFO(0x010214,      0,  64 * 1024,  32, 0) पूर्ण,
	अणु "s25sl032a",  INFO(0x010215,      0,  64 * 1024,  64, 0) पूर्ण,
	अणु "s25sl064a",  INFO(0x010216,      0,  64 * 1024, 128, 0) पूर्ण,
	अणु "s25fl004k",  INFO(0xef4013,      0,  64 * 1024,   8,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "s25fl008k",  INFO(0xef4014,      0,  64 * 1024,  16,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "s25fl016k",  INFO(0xef4015,      0,  64 * 1024,  32,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "s25fl064k",  INFO(0xef4017,      0,  64 * 1024, 128,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "s25fl116k",  INFO(0x014015,      0,  64 * 1024,  32,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "s25fl132k",  INFO(0x014016,      0,  64 * 1024,  64, SECT_4K) पूर्ण,
	अणु "s25fl164k",  INFO(0x014017,      0,  64 * 1024, 128, SECT_4K) पूर्ण,
	अणु "s25fl204k",  INFO(0x014013,      0,  64 * 1024,   8,
			     SECT_4K | SPI_NOR_DUAL_READ) पूर्ण,
	अणु "s25fl208k",  INFO(0x014014,      0,  64 * 1024,  16,
			     SECT_4K | SPI_NOR_DUAL_READ) पूर्ण,
	अणु "s25fl064l",  INFO(0x016017,      0,  64 * 1024, 128,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			     SPI_NOR_4B_OPCODES) पूर्ण,
	अणु "s25fl128l",  INFO(0x016018,      0,  64 * 1024, 256,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			     SPI_NOR_4B_OPCODES) पूर्ण,
	अणु "s25fl256l",  INFO(0x016019,      0,  64 * 1024, 512,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			     SPI_NOR_4B_OPCODES) पूर्ण,
	अणु "cy15x104q",  INFO6(0x042cc2, 0x7f7f7f, 512 * 1024, 1,
			      SPI_NOR_NO_ERASE) पूर्ण,
	अणु "s28hs512t",   INFO(0x345b1a,      0, 256 * 1024, 256,
			     SECT_4K | SPI_NOR_OCTAL_DTR_READ |
			      SPI_NOR_OCTAL_DTR_PP)
	  .fixups = &s28hs512t_fixups,
	पूर्ण,
पूर्ण;

अटल व्योम spansion_post_sfdp_fixups(काष्ठा spi_nor *nor)
अणु
	अगर (nor->params->size <= SZ_16M)
		वापस;

	nor->flags |= SNOR_F_4B_OPCODES;
	/* No small sector erase क्रम 4-byte command set */
	nor->erase_opcode = SPINOR_OP_SE;
	nor->mtd.erasesize = nor->info->sector_size;
पूर्ण

अटल स्थिर काष्ठा spi_nor_fixups spansion_fixups = अणु
	.post_sfdp = spansion_post_sfdp_fixups,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_spansion = अणु
	.name = "spansion",
	.parts = spansion_parts,
	.nparts = ARRAY_SIZE(spansion_parts),
	.fixups = &spansion_fixups,
पूर्ण;
