<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2018 exceet electronics GmbH
 * Copyright (c) 2018 Kontron Electronics GmbH
 *
 * Author: Frieder Schrempf <frieder.schrempf@kontron.de>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mtd/spinand.h>

/* Kioxia is new name of Toshiba memory. */
#घोषणा SPIन_अंकD_MFR_TOSHIBA		0x98
#घोषणा TOSH_STATUS_ECC_HAS_BITFLIPS_T	(3 << 4)

अटल SPIन_अंकD_OP_VARIANTS(पढ़ो_cache_variants,
		SPIन_अंकD_PAGE_READ_FROM_CACHE_X4_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_X2_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_OP(true, 0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_OP(false, 0, 1, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(ग_लिखो_cache_x4_variants,
		SPIन_अंकD_PROG_LOAD_X4(true, 0, शून्य, 0),
		SPIन_अंकD_PROG_LOAD(true, 0, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(update_cache_x4_variants,
		SPIन_अंकD_PROG_LOAD_X4(false, 0, शून्य, 0),
		SPIन_अंकD_PROG_LOAD(false, 0, शून्य, 0));

/*
 * Backward compatibility क्रम 1st generation Serial न_अंकD devices
 * which करोn't support Quad Program Load operation.
 */
अटल SPIन_अंकD_OP_VARIANTS(ग_लिखो_cache_variants,
		SPIन_अंकD_PROG_LOAD(true, 0, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(update_cache_variants,
		SPIन_अंकD_PROG_LOAD(false, 0, शून्य, 0));

अटल पूर्णांक tx58cxgxsxraix_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
					काष्ठा mtd_oob_region *region)
अणु
	अगर (section > 0)
		वापस -दुस्फल;

	region->offset = mtd->oobsize / 2;
	region->length = mtd->oobsize / 2;

	वापस 0;
पूर्ण

अटल पूर्णांक tx58cxgxsxraix_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
					 काष्ठा mtd_oob_region *region)
अणु
	अगर (section > 0)
		वापस -दुस्फल;

	/* 2 bytes reserved क्रम BBM */
	region->offset = 2;
	region->length = (mtd->oobsize / 2) - 2;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops tx58cxgxsxraix_ooblayout = अणु
	.ecc = tx58cxgxsxraix_ooblayout_ecc,
	.मुक्त = tx58cxgxsxraix_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक tx58cxgxsxraix_ecc_get_status(काष्ठा spinand_device *spinand,
					 u8 status)
अणु
	काष्ठा nand_device *nand = spinand_to_nand(spinand);
	u8 mbf = 0;
	काष्ठा spi_mem_op op = SPIन_अंकD_GET_FEATURE_OP(0x30, &mbf);

	चयन (status & STATUS_ECC_MASK) अणु
	हाल STATUS_ECC_NO_BITFLIPS:
		वापस 0;

	हाल STATUS_ECC_UNCOR_ERROR:
		वापस -EBADMSG;

	हाल STATUS_ECC_HAS_BITFLIPS:
	हाल TOSH_STATUS_ECC_HAS_BITFLIPS_T:
		/*
		 * Let's try to retrieve the real maximum number of bitflips
		 * in order to aव्योम क्रमcing the wear-leveling layer to move
		 * data around अगर it's not necessary.
		 */
		अगर (spi_mem_exec_op(spinand->spimem, &op))
			वापस nanddev_get_ecc_conf(nand)->strength;

		mbf >>= 4;

		अगर (WARN_ON(mbf > nanddev_get_ecc_conf(nand)->strength || !mbf))
			वापस nanddev_get_ecc_conf(nand)->strength;

		वापस mbf;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा spinand_info toshiba_spinand_table[] = अणु
	/* 3.3V 1Gb (1st generation) */
	SPIन_अंकD_INFO("TC58CVG0S3HRAIG",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xC2),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&tx58cxgxsxraix_ooblayout,
				     tx58cxgxsxraix_ecc_get_status)),
	/* 3.3V 2Gb (1st generation) */
	SPIन_अंकD_INFO("TC58CVG1S3HRAIG",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xCB),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&tx58cxgxsxraix_ooblayout,
				     tx58cxgxsxraix_ecc_get_status)),
	/* 3.3V 4Gb (1st generation) */
	SPIन_अंकD_INFO("TC58CVG2S0HRAIG",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xCD),
		     न_अंकD_MEMORG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&tx58cxgxsxraix_ooblayout,
				     tx58cxgxsxraix_ecc_get_status)),
	/* 1.8V 1Gb (1st generation) */
	SPIन_अंकD_INFO("TC58CYG0S3HRAIG",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xB2),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&tx58cxgxsxraix_ooblayout,
				     tx58cxgxsxraix_ecc_get_status)),
	/* 1.8V 2Gb (1st generation) */
	SPIन_अंकD_INFO("TC58CYG1S3HRAIG",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xBB),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&tx58cxgxsxraix_ooblayout,
				     tx58cxgxsxraix_ecc_get_status)),
	/* 1.8V 4Gb (1st generation) */
	SPIन_अंकD_INFO("TC58CYG2S0HRAIG",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xBD),
		     न_अंकD_MEMORG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&tx58cxgxsxraix_ooblayout,
				     tx58cxgxsxraix_ecc_get_status)),

	/*
	 * 2nd generation serial nand has HOLD_D which is equivalent to
	 * QE_BIT.
	 */
	/* 3.3V 1Gb (2nd generation) */
	SPIन_अंकD_INFO("TC58CVG0S3HRAIJ",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xE2),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_x4_variants,
					      &update_cache_x4_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&tx58cxgxsxraix_ooblayout,
				     tx58cxgxsxraix_ecc_get_status)),
	/* 3.3V 2Gb (2nd generation) */
	SPIन_अंकD_INFO("TC58CVG1S3HRAIJ",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xEB),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_x4_variants,
					      &update_cache_x4_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&tx58cxgxsxraix_ooblayout,
				     tx58cxgxsxraix_ecc_get_status)),
	/* 3.3V 4Gb (2nd generation) */
	SPIन_अंकD_INFO("TC58CVG2S0HRAIJ",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xED),
		     न_अंकD_MEMORG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_x4_variants,
					      &update_cache_x4_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&tx58cxgxsxraix_ooblayout,
				     tx58cxgxsxraix_ecc_get_status)),
	/* 3.3V 8Gb (2nd generation) */
	SPIन_अंकD_INFO("TH58CVG3S0HRAIJ",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xE4),
		     न_अंकD_MEMORG(1, 4096, 256, 64, 4096, 80, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_x4_variants,
					      &update_cache_x4_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&tx58cxgxsxraix_ooblayout,
				     tx58cxgxsxraix_ecc_get_status)),
	/* 1.8V 1Gb (2nd generation) */
	SPIन_अंकD_INFO("TC58CYG0S3HRAIJ",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xD2),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_x4_variants,
					      &update_cache_x4_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&tx58cxgxsxraix_ooblayout,
				     tx58cxgxsxraix_ecc_get_status)),
	/* 1.8V 2Gb (2nd generation) */
	SPIन_अंकD_INFO("TC58CYG1S3HRAIJ",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xDB),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_x4_variants,
					      &update_cache_x4_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&tx58cxgxsxraix_ooblayout,
				     tx58cxgxsxraix_ecc_get_status)),
	/* 1.8V 4Gb (2nd generation) */
	SPIन_अंकD_INFO("TC58CYG2S0HRAIJ",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xDD),
		     न_अंकD_MEMORG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_x4_variants,
					      &update_cache_x4_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&tx58cxgxsxraix_ooblayout,
				     tx58cxgxsxraix_ecc_get_status)),
	/* 1.8V 8Gb (2nd generation) */
	SPIन_अंकD_INFO("TH58CYG3S0HRAIJ",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xD4),
		     न_अंकD_MEMORG(1, 4096, 256, 64, 4096, 80, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_x4_variants,
					      &update_cache_x4_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&tx58cxgxsxraix_ooblayout,
				     tx58cxgxsxraix_ecc_get_status)),
पूर्ण;

अटल स्थिर काष्ठा spinand_manufacturer_ops toshiba_spinand_manuf_ops = अणु
पूर्ण;

स्थिर काष्ठा spinand_manufacturer toshiba_spinand_manufacturer = अणु
	.id = SPIन_अंकD_MFR_TOSHIBA,
	.name = "Toshiba",
	.chips = toshiba_spinand_table,
	.nchips = ARRAY_SIZE(toshiba_spinand_table),
	.ops = &toshiba_spinand_manuf_ops,
पूर्ण;
