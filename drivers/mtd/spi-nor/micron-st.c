<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

#घोषणा SPINOR_OP_MT_DTR_RD	0xfd	/* Fast Read opcode in DTR mode */
#घोषणा SPINOR_OP_MT_RD_ANY_REG	0x85	/* Read अस्थिर रेजिस्टर */
#घोषणा SPINOR_OP_MT_WR_ANY_REG	0x81	/* Write अस्थिर रेजिस्टर */
#घोषणा SPINOR_REG_MT_CFR0V	0x00	/* For setting octal DTR mode */
#घोषणा SPINOR_REG_MT_CFR1V	0x01	/* For setting dummy cycles */
#घोषणा SPINOR_MT_OCT_DTR	0xe7	/* Enable Octal DTR. */
#घोषणा SPINOR_MT_EXSPI		0xff	/* Enable Extended SPI (शेष) */

अटल पूर्णांक spi_nor_micron_octal_dtr_enable(काष्ठा spi_nor *nor, bool enable)
अणु
	काष्ठा spi_mem_op op;
	u8 *buf = nor->bouncebuf;
	पूर्णांक ret;

	अगर (enable) अणु
		/* Use 20 dummy cycles क्रम memory array पढ़ोs. */
		ret = spi_nor_ग_लिखो_enable(nor);
		अगर (ret)
			वापस ret;

		*buf = 20;
		op = (काष्ठा spi_mem_op)
			SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_MT_WR_ANY_REG, 1),
				   SPI_MEM_OP_ADDR(3, SPINOR_REG_MT_CFR1V, 1),
				   SPI_MEM_OP_NO_DUMMY,
				   SPI_MEM_OP_DATA_OUT(1, buf, 1));

		ret = spi_mem_exec_op(nor->spimem, &op);
		अगर (ret)
			वापस ret;

		ret = spi_nor_रुको_till_पढ़ोy(nor);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = spi_nor_ग_लिखो_enable(nor);
	अगर (ret)
		वापस ret;

	अगर (enable)
		*buf = SPINOR_MT_OCT_DTR;
	अन्यथा
		*buf = SPINOR_MT_EXSPI;

	op = (काष्ठा spi_mem_op)
		SPI_MEM_OP(SPI_MEM_OP_CMD(SPINOR_OP_MT_WR_ANY_REG, 1),
			   SPI_MEM_OP_ADDR(enable ? 3 : 4,
					   SPINOR_REG_MT_CFR0V, 1),
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
			   SPI_MEM_OP_NO_ADDR,
			   SPI_MEM_OP_DUMMY(enable ? 8 : 0, 1),
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

अटल व्योम mt35xu512aba_शेष_init(काष्ठा spi_nor *nor)
अणु
	nor->params->octal_dtr_enable = spi_nor_micron_octal_dtr_enable;
पूर्ण

अटल व्योम mt35xu512aba_post_sfdp_fixup(काष्ठा spi_nor *nor)
अणु
	/* Set the Fast Read settings. */
	nor->params->hwcaps.mask |= SNOR_HWCAPS_READ_8_8_8_DTR;
	spi_nor_set_पढ़ो_settings(&nor->params->पढ़ोs[SNOR_CMD_READ_8_8_8_DTR],
				  0, 20, SPINOR_OP_MT_DTR_RD,
				  SNOR_PROTO_8_8_8_DTR);

	nor->cmd_ext_type = SPI_NOR_EXT_REPEAT;
	nor->params->rdsr_dummy = 8;
	nor->params->rdsr_addr_nbytes = 0;

	/*
	 * The BFPT quad enable field is set to a reserved value so the quad
	 * enable function is ignored by spi_nor_parse_bfpt(). Make sure we
	 * disable it.
	 */
	nor->params->quad_enable = शून्य;
पूर्ण

अटल काष्ठा spi_nor_fixups mt35xu512aba_fixups = अणु
	.शेष_init = mt35xu512aba_शेष_init,
	.post_sfdp = mt35xu512aba_post_sfdp_fixup,
पूर्ण;

अटल स्थिर काष्ठा flash_info micron_parts[] = अणु
	अणु "mt35xu512aba", INFO(0x2c5b1a, 0, 128 * 1024, 512,
			       SECT_4K | USE_FSR | SPI_NOR_OCTAL_READ |
			       SPI_NOR_4B_OPCODES | SPI_NOR_OCTAL_DTR_READ |
			       SPI_NOR_OCTAL_DTR_PP |
			       SPI_NOR_IO_MODE_EN_VOLATILE)
	  .fixups = &mt35xu512aba_fixupsपूर्ण,
	अणु "mt35xu02g", INFO(0x2c5b1c, 0, 128 * 1024, 2048,
			    SECT_4K | USE_FSR | SPI_NOR_OCTAL_READ |
			    SPI_NOR_4B_OPCODES) पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा flash_info st_parts[] = अणु
	अणु "n25q016a",	 INFO(0x20bb15, 0, 64 * 1024,   32,
			      SECT_4K | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "n25q032",	 INFO(0x20ba16, 0, 64 * 1024,   64,
			      SPI_NOR_QUAD_READ) पूर्ण,
	अणु "n25q032a",	 INFO(0x20bb16, 0, 64 * 1024,   64,
			      SPI_NOR_QUAD_READ) पूर्ण,
	अणु "n25q064",     INFO(0x20ba17, 0, 64 * 1024,  128,
			      SECT_4K | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "n25q064a",    INFO(0x20bb17, 0, 64 * 1024,  128,
			      SECT_4K | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "n25q128a11",  INFO(0x20bb18, 0, 64 * 1024,  256,
			      SECT_4K | USE_FSR | SPI_NOR_QUAD_READ |
			      SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB |
			      SPI_NOR_4BIT_BP | SPI_NOR_BP3_SR_BIT6) पूर्ण,
	अणु "n25q128a13",  INFO(0x20ba18, 0, 64 * 1024,  256,
			      SECT_4K | USE_FSR | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "mt25ql256a",  INFO6(0x20ba19, 0x104400, 64 * 1024,  512,
			       SECT_4K | USE_FSR | SPI_NOR_DUAL_READ |
			       SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES) पूर्ण,
	अणु "n25q256a",    INFO(0x20ba19, 0, 64 * 1024,  512, SECT_4K |
			      USE_FSR | SPI_NOR_DUAL_READ |
			      SPI_NOR_QUAD_READ) पूर्ण,
	अणु "mt25qu256a",  INFO6(0x20bb19, 0x104400, 64 * 1024,  512,
			       SECT_4K | USE_FSR | SPI_NOR_DUAL_READ |
			       SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES) पूर्ण,
	अणु "n25q256ax1",  INFO(0x20bb19, 0, 64 * 1024,  512,
			      SECT_4K | USE_FSR | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "mt25ql512a",  INFO6(0x20ba20, 0x104400, 64 * 1024, 1024,
			       SECT_4K | USE_FSR | SPI_NOR_DUAL_READ |
			       SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES) पूर्ण,
	अणु "n25q512ax3",  INFO(0x20ba20, 0, 64 * 1024, 1024,
			      SECT_4K | USE_FSR | SPI_NOR_QUAD_READ |
			      SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB |
			      SPI_NOR_4BIT_BP | SPI_NOR_BP3_SR_BIT6) पूर्ण,
	अणु "mt25qu512a",  INFO6(0x20bb20, 0x104400, 64 * 1024, 1024,
			       SECT_4K | USE_FSR | SPI_NOR_DUAL_READ |
			       SPI_NOR_QUAD_READ | SPI_NOR_4B_OPCODES) पूर्ण,
	अणु "n25q512a",    INFO(0x20bb20, 0, 64 * 1024, 1024,
			      SECT_4K | USE_FSR | SPI_NOR_QUAD_READ |
			      SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB |
			      SPI_NOR_4BIT_BP | SPI_NOR_BP3_SR_BIT6) पूर्ण,
	अणु "n25q00",      INFO(0x20ba21, 0, 64 * 1024, 2048,
			      SECT_4K | USE_FSR | SPI_NOR_QUAD_READ |
			      SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB |
			      SPI_NOR_4BIT_BP | SPI_NOR_BP3_SR_BIT6 |
			      NO_CHIP_ERASE) पूर्ण,
	अणु "n25q00a",     INFO(0x20bb21, 0, 64 * 1024, 2048,
			      SECT_4K | USE_FSR | SPI_NOR_QUAD_READ |
			      NO_CHIP_ERASE) पूर्ण,
	अणु "mt25ql02g",   INFO(0x20ba22, 0, 64 * 1024, 4096,
			      SECT_4K | USE_FSR | SPI_NOR_QUAD_READ |
			      NO_CHIP_ERASE) पूर्ण,
	अणु "mt25qu02g",   INFO(0x20bb22, 0, 64 * 1024, 4096,
			      SECT_4K | USE_FSR | SPI_NOR_DUAL_READ |
			      SPI_NOR_QUAD_READ | NO_CHIP_ERASE) पूर्ण,

	अणु "m25p05",  INFO(0x202010,  0,  32 * 1024,   2, 0) पूर्ण,
	अणु "m25p10",  INFO(0x202011,  0,  32 * 1024,   4, 0) पूर्ण,
	अणु "m25p20",  INFO(0x202012,  0,  64 * 1024,   4, 0) पूर्ण,
	अणु "m25p40",  INFO(0x202013,  0,  64 * 1024,   8, 0) पूर्ण,
	अणु "m25p80",  INFO(0x202014,  0,  64 * 1024,  16, 0) पूर्ण,
	अणु "m25p16",  INFO(0x202015,  0,  64 * 1024,  32, 0) पूर्ण,
	अणु "m25p32",  INFO(0x202016,  0,  64 * 1024,  64, 0) पूर्ण,
	अणु "m25p64",  INFO(0x202017,  0,  64 * 1024, 128, 0) पूर्ण,
	अणु "m25p128", INFO(0x202018,  0, 256 * 1024,  64, 0) पूर्ण,

	अणु "m25p05-nonjedec",  INFO(0, 0,  32 * 1024,   2, 0) पूर्ण,
	अणु "m25p10-nonjedec",  INFO(0, 0,  32 * 1024,   4, 0) पूर्ण,
	अणु "m25p20-nonjedec",  INFO(0, 0,  64 * 1024,   4, 0) पूर्ण,
	अणु "m25p40-nonjedec",  INFO(0, 0,  64 * 1024,   8, 0) पूर्ण,
	अणु "m25p80-nonjedec",  INFO(0, 0,  64 * 1024,  16, 0) पूर्ण,
	अणु "m25p16-nonjedec",  INFO(0, 0,  64 * 1024,  32, 0) पूर्ण,
	अणु "m25p32-nonjedec",  INFO(0, 0,  64 * 1024,  64, 0) पूर्ण,
	अणु "m25p64-nonjedec",  INFO(0, 0,  64 * 1024, 128, 0) पूर्ण,
	अणु "m25p128-nonjedec", INFO(0, 0, 256 * 1024,  64, 0) पूर्ण,

	अणु "m45pe10", INFO(0x204011,  0, 64 * 1024,    2, 0) पूर्ण,
	अणु "m45pe80", INFO(0x204014,  0, 64 * 1024,   16, 0) पूर्ण,
	अणु "m45pe16", INFO(0x204015,  0, 64 * 1024,   32, 0) पूर्ण,

	अणु "m25pe20", INFO(0x208012,  0, 64 * 1024,  4,       0) पूर्ण,
	अणु "m25pe80", INFO(0x208014,  0, 64 * 1024, 16,       0) पूर्ण,
	अणु "m25pe16", INFO(0x208015,  0, 64 * 1024, 32, SECT_4K) पूर्ण,

	अणु "m25px16",    INFO(0x207115,  0, 64 * 1024, 32, SECT_4K) पूर्ण,
	अणु "m25px32",    INFO(0x207116,  0, 64 * 1024, 64, SECT_4K) पूर्ण,
	अणु "m25px32-s0", INFO(0x207316,  0, 64 * 1024, 64, SECT_4K) पूर्ण,
	अणु "m25px32-s1", INFO(0x206316,  0, 64 * 1024, 64, SECT_4K) पूर्ण,
	अणु "m25px64",    INFO(0x207117,  0, 64 * 1024, 128, 0) पूर्ण,
	अणु "m25px80",    INFO(0x207114,  0, 64 * 1024, 16, 0) पूर्ण,
पूर्ण;

/**
 * st_micron_set_4byte_addr_mode() - Set 4-byte address mode क्रम ST and Micron
 * flashes.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 * @enable:	true to enter the 4-byte address mode, false to निकास the 4-byte
 *		address mode.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक st_micron_set_4byte_addr_mode(काष्ठा spi_nor *nor, bool enable)
अणु
	पूर्णांक ret;

	ret = spi_nor_ग_लिखो_enable(nor);
	अगर (ret)
		वापस ret;

	ret = spi_nor_set_4byte_addr_mode(nor, enable);
	अगर (ret)
		वापस ret;

	वापस spi_nor_ग_लिखो_disable(nor);
पूर्ण

अटल व्योम micron_st_शेष_init(काष्ठा spi_nor *nor)
अणु
	nor->flags |= SNOR_F_HAS_LOCK;
	nor->flags &= ~SNOR_F_HAS_16BIT_SR;
	nor->params->quad_enable = शून्य;
	nor->params->set_4byte_addr_mode = st_micron_set_4byte_addr_mode;
पूर्ण

अटल स्थिर काष्ठा spi_nor_fixups micron_st_fixups = अणु
	.शेष_init = micron_st_शेष_init,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_micron = अणु
	.name = "micron",
	.parts = micron_parts,
	.nparts = ARRAY_SIZE(micron_parts),
	.fixups = &micron_st_fixups,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_st = अणु
	.name = "st",
	.parts = st_parts,
	.nparts = ARRAY_SIZE(st_parts),
	.fixups = &micron_st_fixups,
पूर्ण;
