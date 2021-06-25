<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2005, Intec Automation Inc.
 * Copyright (C) 2014, Freescale Semiconductor, Inc.
 */

#समावेश <linux/mtd/spi-nor.h>

#समावेश "core.h"

अटल स्थिर काष्ठा flash_info xilinx_parts[] = अणु
	/* Xilinx S3AN Internal Flash */
	अणु "3S50AN", S3AN_INFO(0x1f2200, 64, 264) पूर्ण,
	अणु "3S200AN", S3AN_INFO(0x1f2400, 256, 264) पूर्ण,
	अणु "3S400AN", S3AN_INFO(0x1f2400, 256, 264) पूर्ण,
	अणु "3S700AN", S3AN_INFO(0x1f2500, 512, 264) पूर्ण,
	अणु "3S1400AN", S3AN_INFO(0x1f2600, 512, 528) पूर्ण,
पूर्ण;

/*
 * This code converts an address to the Default Address Mode, that has non
 * घातer of two page sizes. We must support this mode because it is the शेष
 * mode supported by Xilinx tools, it can access the whole flash area and
 * changing over to the Power-of-two mode is irreversible and corrupts the
 * original data.
 * Addr can safely be अचिन्हित पूर्णांक, the biggest S3AN device is smaller than
 * 4 MiB.
 */
अटल u32 s3an_convert_addr(काष्ठा spi_nor *nor, u32 addr)
अणु
	u32 offset, page;

	offset = addr % nor->page_size;
	page = addr / nor->page_size;
	page <<= (nor->page_size > 512) ? 10 : 9;

	वापस page | offset;
पूर्ण

अटल पूर्णांक xilinx_nor_setup(काष्ठा spi_nor *nor,
			    स्थिर काष्ठा spi_nor_hwcaps *hwcaps)
अणु
	पूर्णांक ret;

	ret = spi_nor_xपढ़ो_sr(nor, nor->bouncebuf);
	अगर (ret)
		वापस ret;

	nor->erase_opcode = SPINOR_OP_XSE;
	nor->program_opcode = SPINOR_OP_XPP;
	nor->पढ़ो_opcode = SPINOR_OP_READ;
	nor->flags |= SNOR_F_NO_OP_CHIP_ERASE;

	/*
	 * This flashes have a page size of 264 or 528 bytes (known as
	 * Default addressing mode). It can be changed to a more standard
	 * Power of two mode where the page size is 256/512. This comes
	 * with a price: there is 3% less of space, the data is corrupted
	 * and the page size cannot be changed back to शेष addressing
	 * mode.
	 *
	 * The current addressing mode can be पढ़ो from the XRDSR रेजिस्टर
	 * and should not be changed, because is a deकाष्ठाive operation.
	 */
	अगर (nor->bouncebuf[0] & XSR_PAGESIZE) अणु
		/* Flash in Power of 2 mode */
		nor->page_size = (nor->page_size == 264) ? 256 : 512;
		nor->mtd.ग_लिखोbufsize = nor->page_size;
		nor->mtd.size = 8 * nor->page_size * nor->info->n_sectors;
		nor->mtd.erasesize = 8 * nor->page_size;
	पूर्ण अन्यथा अणु
		/* Flash in Default addressing mode */
		nor->params->convert_addr = s3an_convert_addr;
		nor->mtd.erasesize = nor->info->sector_size;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xilinx_post_sfdp_fixups(काष्ठा spi_nor *nor)
अणु
	nor->params->setup = xilinx_nor_setup;
पूर्ण

अटल स्थिर काष्ठा spi_nor_fixups xilinx_fixups = अणु
	.post_sfdp = xilinx_post_sfdp_fixups,
पूर्ण;

स्थिर काष्ठा spi_nor_manufacturer spi_nor_xilinx = अणु
	.name = "xilinx",
	.parts = xilinx_parts,
	.nparts = ARRAY_SIZE(xilinx_parts),
	.fixups = &xilinx_fixups,
पूर्ण;
