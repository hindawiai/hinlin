<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016-2017 Micron Technology, Inc.
 *
 * Authors:
 *	Peter Pan <peterpanकरोng@micron.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mtd/spinand.h>

#घोषणा SPIन_अंकD_MFR_MICRON		0x2c

#घोषणा MICRON_STATUS_ECC_MASK		GENMASK(7, 4)
#घोषणा MICRON_STATUS_ECC_NO_BITFLIPS	(0 << 4)
#घोषणा MICRON_STATUS_ECC_1TO3_BITFLIPS	(1 << 4)
#घोषणा MICRON_STATUS_ECC_4TO6_BITFLIPS	(3 << 4)
#घोषणा MICRON_STATUS_ECC_7TO8_BITFLIPS	(5 << 4)

#घोषणा MICRON_CFG_CR			BIT(0)

/*
 * As per datasheet, die selection is करोne by the 6th bit of Die
 * Select Register (Address 0xD0).
 */
#घोषणा MICRON_DIE_SELECT_REG	0xD0

#घोषणा MICRON_SELECT_DIE(x)	((x) << 6)

अटल SPIन_अंकD_OP_VARIANTS(quadio_पढ़ो_cache_variants,
		SPIन_अंकD_PAGE_READ_FROM_CACHE_QUADIO_OP(0, 2, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_X4_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_DUALIO_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_X2_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_OP(true, 0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_OP(false, 0, 1, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(x4_ग_लिखो_cache_variants,
		SPIन_अंकD_PROG_LOAD_X4(true, 0, शून्य, 0),
		SPIन_अंकD_PROG_LOAD(true, 0, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(x4_update_cache_variants,
		SPIन_अंकD_PROG_LOAD_X4(false, 0, शून्य, 0),
		SPIन_अंकD_PROG_LOAD(false, 0, शून्य, 0));

/* Micron  MT29F2G01AAAED Device */
अटल SPIन_अंकD_OP_VARIANTS(x4_पढ़ो_cache_variants,
			   SPIन_अंकD_PAGE_READ_FROM_CACHE_X4_OP(0, 1, शून्य, 0),
			   SPIन_अंकD_PAGE_READ_FROM_CACHE_X2_OP(0, 1, शून्य, 0),
			   SPIन_अंकD_PAGE_READ_FROM_CACHE_OP(true, 0, 1, शून्य, 0),
			   SPIन_अंकD_PAGE_READ_FROM_CACHE_OP(false, 0, 1, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(x1_ग_लिखो_cache_variants,
			   SPIन_अंकD_PROG_LOAD(true, 0, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(x1_update_cache_variants,
			   SPIन_अंकD_PROG_LOAD(false, 0, शून्य, 0));

अटल पूर्णांक micron_8_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *region)
अणु
	अगर (section)
		वापस -दुस्फल;

	region->offset = mtd->oobsize / 2;
	region->length = mtd->oobsize / 2;

	वापस 0;
पूर्ण

अटल पूर्णांक micron_8_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				   काष्ठा mtd_oob_region *region)
अणु
	अगर (section)
		वापस -दुस्फल;

	/* Reserve 2 bytes क्रम the BBM. */
	region->offset = 2;
	region->length = (mtd->oobsize / 2) - 2;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops micron_8_ooblayout = अणु
	.ecc = micron_8_ooblayout_ecc,
	.मुक्त = micron_8_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक micron_4_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *region)
अणु
	काष्ठा spinand_device *spinand = mtd_to_spinand(mtd);

	अगर (section >= spinand->base.memorg.pagesize /
			mtd->ecc_step_size)
		वापस -दुस्फल;

	region->offset = (section * 16) + 8;
	region->length = 8;

	वापस 0;
पूर्ण

अटल पूर्णांक micron_4_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				   काष्ठा mtd_oob_region *region)
अणु
	काष्ठा spinand_device *spinand = mtd_to_spinand(mtd);

	अगर (section >= spinand->base.memorg.pagesize /
			mtd->ecc_step_size)
		वापस -दुस्फल;

	अगर (section) अणु
		region->offset = 16 * section;
		region->length = 8;
	पूर्ण अन्यथा अणु
		/* section 0 has two bytes reserved क्रम the BBM */
		region->offset = 2;
		region->length = 6;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops micron_4_ooblayout = अणु
	.ecc = micron_4_ooblayout_ecc,
	.मुक्त = micron_4_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक micron_select_target(काष्ठा spinand_device *spinand,
				अचिन्हित पूर्णांक target)
अणु
	काष्ठा spi_mem_op op = SPIन_अंकD_SET_FEATURE_OP(MICRON_DIE_SELECT_REG,
						      spinand->scratchbuf);

	अगर (target > 1)
		वापस -EINVAL;

	*spinand->scratchbuf = MICRON_SELECT_DIE(target);

	वापस spi_mem_exec_op(spinand->spimem, &op);
पूर्ण

अटल पूर्णांक micron_8_ecc_get_status(काष्ठा spinand_device *spinand,
				   u8 status)
अणु
	चयन (status & MICRON_STATUS_ECC_MASK) अणु
	हाल STATUS_ECC_NO_BITFLIPS:
		वापस 0;

	हाल STATUS_ECC_UNCOR_ERROR:
		वापस -EBADMSG;

	हाल MICRON_STATUS_ECC_1TO3_BITFLIPS:
		वापस 3;

	हाल MICRON_STATUS_ECC_4TO6_BITFLIPS:
		वापस 6;

	हाल MICRON_STATUS_ECC_7TO8_BITFLIPS:
		वापस 8;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा spinand_info micron_spinand_table[] = अणु
	/* M79A 2Gb 3.3V */
	SPIन_अंकD_INFO("MT29F2G01ABAGD",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x24),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 2048, 40, 2, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&quadio_पढ़ो_cache_variants,
					      &x4_ग_लिखो_cache_variants,
					      &x4_update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&micron_8_ooblayout,
				     micron_8_ecc_get_status)),
	/* M79A 2Gb 1.8V */
	SPIन_अंकD_INFO("MT29F2G01ABBGD",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x25),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 2048, 40, 2, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&quadio_पढ़ो_cache_variants,
					      &x4_ग_लिखो_cache_variants,
					      &x4_update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&micron_8_ooblayout,
				     micron_8_ecc_get_status)),
	/* M78A 1Gb 3.3V */
	SPIन_अंकD_INFO("MT29F1G01ABAFD",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x14),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&quadio_पढ़ो_cache_variants,
					      &x4_ग_लिखो_cache_variants,
					      &x4_update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&micron_8_ooblayout,
				     micron_8_ecc_get_status)),
	/* M78A 1Gb 1.8V */
	SPIन_अंकD_INFO("MT29F1G01ABAFD",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x15),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&quadio_पढ़ो_cache_variants,
					      &x4_ग_लिखो_cache_variants,
					      &x4_update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&micron_8_ooblayout,
				     micron_8_ecc_get_status)),
	/* M79A 4Gb 3.3V */
	SPIन_अंकD_INFO("MT29F4G01ADAGD",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x36),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 2048, 80, 2, 1, 2),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&quadio_पढ़ो_cache_variants,
					      &x4_ग_लिखो_cache_variants,
					      &x4_update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&micron_8_ooblayout,
				     micron_8_ecc_get_status),
		     SPIन_अंकD_SELECT_TARGET(micron_select_target)),
	/* M70A 4Gb 3.3V */
	SPIन_अंकD_INFO("MT29F4G01ABAFD",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x34),
		     न_अंकD_MEMORG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&quadio_पढ़ो_cache_variants,
					      &x4_ग_लिखो_cache_variants,
					      &x4_update_cache_variants),
		     SPIन_अंकD_HAS_CR_FEAT_BIT,
		     SPIन_अंकD_ECCINFO(&micron_8_ooblayout,
				     micron_8_ecc_get_status)),
	/* M70A 4Gb 1.8V */
	SPIन_अंकD_INFO("MT29F4G01ABBFD",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x35),
		     न_अंकD_MEMORG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&quadio_पढ़ो_cache_variants,
					      &x4_ग_लिखो_cache_variants,
					      &x4_update_cache_variants),
		     SPIन_अंकD_HAS_CR_FEAT_BIT,
		     SPIन_अंकD_ECCINFO(&micron_8_ooblayout,
				     micron_8_ecc_get_status)),
	/* M70A 8Gb 3.3V */
	SPIन_अंकD_INFO("MT29F8G01ADAFD",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x46),
		     न_अंकD_MEMORG(1, 4096, 256, 64, 2048, 40, 1, 1, 2),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&quadio_पढ़ो_cache_variants,
					      &x4_ग_लिखो_cache_variants,
					      &x4_update_cache_variants),
		     SPIन_अंकD_HAS_CR_FEAT_BIT,
		     SPIन_अंकD_ECCINFO(&micron_8_ooblayout,
				     micron_8_ecc_get_status),
		     SPIन_अंकD_SELECT_TARGET(micron_select_target)),
	/* M70A 8Gb 1.8V */
	SPIन_अंकD_INFO("MT29F8G01ADBFD",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x47),
		     न_अंकD_MEMORG(1, 4096, 256, 64, 2048, 40, 1, 1, 2),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&quadio_पढ़ो_cache_variants,
					      &x4_ग_लिखो_cache_variants,
					      &x4_update_cache_variants),
		     SPIन_अंकD_HAS_CR_FEAT_BIT,
		     SPIन_अंकD_ECCINFO(&micron_8_ooblayout,
				     micron_8_ecc_get_status),
		     SPIन_अंकD_SELECT_TARGET(micron_select_target)),
	/* M69A 2Gb 3.3V */
	SPIन_अंकD_INFO("MT29F2G01AAAED",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x9F),
		     न_अंकD_MEMORG(1, 2048, 64, 64, 2048, 80, 2, 1, 1),
		     न_अंकD_ECCREQ(4, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&x4_पढ़ो_cache_variants,
					      &x1_ग_लिखो_cache_variants,
					      &x1_update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&micron_4_ooblayout, शून्य)),
पूर्ण;

अटल पूर्णांक micron_spinand_init(काष्ठा spinand_device *spinand)
अणु
	/*
	 * M70A device series enable Continuous Read feature at Power-up,
	 * which is not supported. Disable this bit to aव्योम any possible
	 * failure.
	 */
	अगर (spinand->flags & SPIन_अंकD_HAS_CR_FEAT_BIT)
		वापस spinand_upd_cfg(spinand, MICRON_CFG_CR, 0);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा spinand_manufacturer_ops micron_spinand_manuf_ops = अणु
	.init = micron_spinand_init,
पूर्ण;

स्थिर काष्ठा spinand_manufacturer micron_spinand_manufacturer = अणु
	.id = SPIन_अंकD_MFR_MICRON,
	.name = "Micron",
	.chips = micron_spinand_table,
	.nchips = ARRAY_SIZE(micron_spinand_table),
	.ops = &micron_spinand_manuf_ops,
पूर्ण;
