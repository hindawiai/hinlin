<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

अटल पूर्णांक
w25q256_post_bfpt_fixups(काष्ठा spi_nor *nor,
			 स्थिर काष्ठा sfdp_parameter_header *bfpt_header,
			 स्थिर काष्ठा sfdp_bfpt *bfpt)
अणु
	/*
	 * W25Q256JV supports 4B opcodes but W25Q256FV करोes not.
	 * Unक्रमtunately, Winbond has re-used the same JEDEC ID क्रम both
	 * variants which prevents us from defining a new entry in the parts
	 * table.
	 * To dअगरferentiate between W25Q256JV and W25Q256FV check SFDP header
	 * version: only JV has JESD216A compliant काष्ठाure (version 5).
	 */
	अगर (bfpt_header->major == SFDP_JESD216_MAJOR &&
	    bfpt_header->minor == SFDP_JESD216A_MINOR)
		nor->flags |= SNOR_F_4B_OPCODES;

	वापस 0;
पूर्ण

अटल काष्ठा spi_nor_fixups w25q256_fixups = अणु
	.post_bfpt = w25q256_post_bfpt_fixups,
पूर्ण;

अटल स्थिर काष्ठा flash_info winbond_parts[] = अणु
	/* Winbond -- w25x "blocks" are 64K, "sectors" are 4KiB */
	अणु "w25x05", INFO(0xef3010, 0, 64 * 1024,  1,  SECT_4K) पूर्ण,
	अणु "w25x10", INFO(0xef3011, 0, 64 * 1024,  2,  SECT_4K) पूर्ण,
	अणु "w25x20", INFO(0xef3012, 0, 64 * 1024,  4,  SECT_4K) पूर्ण,
	अणु "w25x40", INFO(0xef3013, 0, 64 * 1024,  8,  SECT_4K) पूर्ण,
	अणु "w25x80", INFO(0xef3014, 0, 64 * 1024,  16, SECT_4K) पूर्ण,
	अणु "w25x16", INFO(0xef3015, 0, 64 * 1024,  32, SECT_4K) पूर्ण,
	अणु "w25q16dw", INFO(0xef6015, 0, 64 * 1024,  32,
			   SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			   SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) पूर्ण,
	अणु "w25x32", INFO(0xef3016, 0, 64 * 1024,  64, SECT_4K) पूर्ण,
	अणु "w25q16jv-im/jm", INFO(0xef7015, 0, 64 * 1024,  32,
				 SECT_4K | SPI_NOR_DUAL_READ |
				 SPI_NOR_QUAD_READ | SPI_NOR_HAS_LOCK |
				 SPI_NOR_HAS_TB) पूर्ण,
	अणु "w25q20cl", INFO(0xef4012, 0, 64 * 1024,  4, SECT_4K) पूर्ण,
	अणु "w25q20bw", INFO(0xef5012, 0, 64 * 1024,  4, SECT_4K) पूर्ण,
	अणु "w25q20ew", INFO(0xef6012, 0, 64 * 1024,  4, SECT_4K) पूर्ण,
	अणु "w25q32", INFO(0xef4016, 0, 64 * 1024,  64, SECT_4K) पूर्ण,
	अणु "w25q32dw", INFO(0xef6016, 0, 64 * 1024,  64,
			   SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			   SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
			   OTP_INFO(256, 3, 0x1000, 0x1000)
	पूर्ण,

	अणु "w25q32jv", INFO(0xef7016, 0, 64 * 1024,  64,
			   SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			   SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
	पूर्ण,
	अणु "w25q32jwm", INFO(0xef8016, 0, 64 * 1024,  64,
			    SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			    SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB)
			    OTP_INFO(256, 3, 0x1000, 0x1000) पूर्ण,
	अणु "w25q64jwm", INFO(0xef8017, 0, 64 * 1024, 128,
			    SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			    SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) पूर्ण,
	अणु "w25q128jwm", INFO(0xef8018, 0, 64 * 1024, 256,
			    SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			    SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) पूर्ण,
	अणु "w25q256jwm", INFO(0xef8019, 0, 64 * 1024, 512,
			    SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			    SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) पूर्ण,
	अणु "w25x64", INFO(0xef3017, 0, 64 * 1024, 128, SECT_4K) पूर्ण,
	अणु "w25q64", INFO(0xef4017, 0, 64 * 1024, 128,
			 SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "w25q64dw", INFO(0xef6017, 0, 64 * 1024, 128,
			   SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			   SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) पूर्ण,
	अणु "w25q64jvm", INFO(0xef7017, 0, 64 * 1024, 128, SECT_4K) पूर्ण,
	अणु "w25q128fw", INFO(0xef6018, 0, 64 * 1024, 256,
			    SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			    SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) पूर्ण,
	अणु "w25q128jv", INFO(0xef7018, 0, 64 * 1024, 256,
			    SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ |
			    SPI_NOR_HAS_LOCK | SPI_NOR_HAS_TB) पूर्ण,
	अणु "w25q80", INFO(0xef5014, 0, 64 * 1024,  16, SECT_4K) पूर्ण,
	अणु "w25q80bl", INFO(0xef4014, 0, 64 * 1024,  16, SECT_4K) पूर्ण,
	अणु "w25q128", INFO(0xef4018, 0, 64 * 1024, 256, SECT_4K) पूर्ण,
	अणु "w25q256", INFO(0xef4019, 0, 64 * 1024, 512,
			  SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ)
	  .fixups = &w25q256_fixups पूर्ण,
	अणु "w25q256jvm", INFO(0xef7019, 0, 64 * 1024, 512,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "w25q256jw", INFO(0xef6019, 0, 64 * 1024, 512,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
	अणु "w25m512jv", INFO(0xef7119, 0, 64 * 1024, 1024,
			    SECT_4K | SPI_NOR_QUAD_READ | SPI_NOR_DUAL_READ) पूर्ण,
	अणु "w25q512jvq", INFO(0xef4020, 0, 64 * 1024, 1024,
			     SECT_4K | SPI_NOR_DUAL_READ | SPI_NOR_QUAD_READ) पूर्ण,
पूर्ण;

/**
 * winbond_set_4byte_addr_mode() - Set 4-byte address mode क्रम Winbond flashes.
 * @nor:	poपूर्णांकer to 'struct spi_nor'.
 * @enable:	true to enter the 4-byte address mode, false to निकास the 4-byte
 *		address mode.
 *
 * Return: 0 on success, -त्रुटि_सं otherwise.
 */
अटल पूर्णांक winbond_set_4byte_addr_mode(काष्ठा spi_nor *nor, bool enable)
अणु
	पूर्णांक ret;

	ret = spi_nor_set_4byte_addr_mode(nor, enable);
	अगर (ret || enable)
		वापस ret;

	/*
	 * On Winbond W25Q256FV, leaving 4byte mode causes the Extended Address
	 * Register to be set to 1, so all 3-byte-address पढ़ोs come from the
	 * second 16M. We must clear the रेजिस्टर to enable normal behavior.
	 */
	ret = spi_nor_ग_लिखो_enable(nor);
	अगर (ret)
		वापस ret;

	ret = spi_nor_ग_लिखो_ear(nor, 0);
	अगर (ret)
		वापस ret;

	वापस spi_nor_ग_लिखो_disable(nor);
पूर्ण

अटल स्थिर काष्ठा spi_nor_otp_ops winbond_otp_ops = अणु
	.पढ़ो = spi_nor_otp_पढ़ो_secr,
	.ग_लिखो = spi_nor_otp_ग_लिखो_secr,
	.lock = spi_nor_otp_lock_sr2,
	.is_locked = spi_nor_otp_is_locked_sr2,
पूर्ण;

अटल व्योम winbond_शेष_init(काष्ठा spi_nor *nor)
अणु
	nor->params->set_4byte_addr_mode = winbond_set_4byte_addr_mode;
	अगर (nor->params->otp.org->n_regions)
		nor->params->otp.ops = &winbond_otp_ops;
पूर्ण

अटल स्थिर काष्ठा spi_nor_fixups winbond_fixups = अणु
	.शेष_init = winbond_शेष_init,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_winbond = अणु
	.name = "winbond",
	.parts = winbond_parts,
	.nparts = ARRAY_SIZE(winbond_parts),
	.fixups = &winbond_fixups,
पूर्ण;
