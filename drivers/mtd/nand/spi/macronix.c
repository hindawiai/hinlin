<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 Macronix
 *
 * Author: Boris Brezillon <boris.brezillon@bootlin.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mtd/spinand.h>

#घोषणा SPIन_अंकD_MFR_MACRONIX		0xC2
#घोषणा MACRONIX_ECCSR_MASK		0x0F

अटल SPIन_अंकD_OP_VARIANTS(पढ़ो_cache_variants,
		SPIन_अंकD_PAGE_READ_FROM_CACHE_X4_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_X2_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_OP(true, 0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_OP(false, 0, 1, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(ग_लिखो_cache_variants,
		SPIन_अंकD_PROG_LOAD_X4(true, 0, शून्य, 0),
		SPIन_अंकD_PROG_LOAD(true, 0, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(update_cache_variants,
		SPIन_अंकD_PROG_LOAD_X4(false, 0, शून्य, 0),
		SPIन_अंकD_PROG_LOAD(false, 0, शून्य, 0));

अटल पूर्णांक mx35lfxge4ab_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				      काष्ठा mtd_oob_region *region)
अणु
	वापस -दुस्फल;
पूर्ण

अटल पूर्णांक mx35lfxge4ab_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				       काष्ठा mtd_oob_region *region)
अणु
	अगर (section)
		वापस -दुस्फल;

	region->offset = 2;
	region->length = mtd->oobsize - 2;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops mx35lfxge4ab_ooblayout = अणु
	.ecc = mx35lfxge4ab_ooblayout_ecc,
	.मुक्त = mx35lfxge4ab_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक mx35lf1ge4ab_get_eccsr(काष्ठा spinand_device *spinand, u8 *eccsr)
अणु
	काष्ठा spi_mem_op op = SPI_MEM_OP(SPI_MEM_OP_CMD(0x7c, 1),
					  SPI_MEM_OP_NO_ADDR,
					  SPI_MEM_OP_DUMMY(1, 1),
					  SPI_MEM_OP_DATA_IN(1, eccsr, 1));

	पूर्णांक ret = spi_mem_exec_op(spinand->spimem, &op);
	अगर (ret)
		वापस ret;

	*eccsr &= MACRONIX_ECCSR_MASK;
	वापस 0;
पूर्ण

अटल पूर्णांक mx35lf1ge4ab_ecc_get_status(काष्ठा spinand_device *spinand,
				       u8 status)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	u8 eccsr;

	चयन (status & STATUS_ECC_MASK) अणु
	हाल STATUS_ECC_NO_BITFLIPS:
		वापस 0;

	हाल STATUS_ECC_UNCOR_ERROR:
		वापस -EBADMSG;

	हाल STATUS_ECC_HAS_BITFLIPS:
		/*
		 * Let's try to retrieve the real maximum number of bitflips
		 * in order to aव्योम क्रमcing the wear-leveling layer to move
		 * data around अगर it's not necessary.
		 */
		अगर (mx35lf1ge4ab_get_eccsr(spinand, &eccsr))
			वापस nanddev_get_ecc_conf(nand)->strength;

		अगर (WARN_ON(eccsr > nanddev_get_ecc_conf(nand)->strength ||
			    !eccsr))
			वापस nanddev_get_ecc_conf(nand)->strength;

		वापस eccsr;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा spinand_info macronix_spinand_table[] = अणु
	SPIन_अंकD_INFO("MX35LF1GE4AB",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x12),
		     न_अंकD_MEMORG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     न_अंकD_ECCREQ(4, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&mx35lfxge4ab_ooblayout,
				     mx35lf1ge4ab_ecc_get_status)),
	SPIन_अंकD_INFO("MX35LF2GE4AB",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x22),
		     न_अंकD_MEMORG(1, 2048, 64, 64, 2048, 40, 2, 1, 1),
		     न_अंकD_ECCREQ(4, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&mx35lfxge4ab_ooblayout, शून्य)),
	SPIन_अंकD_INFO("MX35LF2GE4AD",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x26),
		     न_अंकD_MEMORG(1, 2048, 64, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&mx35lfxge4ab_ooblayout,
				     mx35lf1ge4ab_ecc_get_status)),
	SPIन_अंकD_INFO("MX35LF4GE4AD",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x37),
		     न_अंकD_MEMORG(1, 4096, 128, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&mx35lfxge4ab_ooblayout,
				     mx35lf1ge4ab_ecc_get_status)),
	SPIन_अंकD_INFO("MX35LF1G24AD",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x14),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&mx35lfxge4ab_ooblayout, शून्य)),
	SPIन_अंकD_INFO("MX35LF2G24AD",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x24),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&mx35lfxge4ab_ooblayout, शून्य)),
	SPIन_अंकD_INFO("MX35LF4G24AD",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x35),
		     न_अंकD_MEMORG(1, 4096, 256, 64, 2048, 40, 2, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&mx35lfxge4ab_ooblayout, शून्य)),
	SPIन_अंकD_INFO("MX31LF1GE4BC",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x1e),
		     न_अंकD_MEMORG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0 /*SPIन_अंकD_HAS_QE_BIT*/,
		     SPIन_अंकD_ECCINFO(&mx35lfxge4ab_ooblayout,
				     mx35lf1ge4ab_ecc_get_status)),
	SPIन_अंकD_INFO("MX31UF1GE4BC",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x9e),
		     न_अंकD_MEMORG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0 /*SPIन_अंकD_HAS_QE_BIT*/,
		     SPIन_अंकD_ECCINFO(&mx35lfxge4ab_ooblayout,
				     mx35lf1ge4ab_ecc_get_status)),
पूर्ण;

अटल स्थिर काष्ठा spinand_manufacturer_ops macronix_spinand_manuf_ops = अणु
पूर्ण;

स्थिर काष्ठा spinand_manufacturer macronix_spinand_manufacturer = अणु
	.id = SPIन_अंकD_MFR_MACRONIX,
	.name = "Macronix",
	.chips = macronix_spinand_table,
	.nchips = ARRAY_SIZE(macronix_spinand_table),
	.ops = &macronix_spinand_manuf_ops,
पूर्ण;
