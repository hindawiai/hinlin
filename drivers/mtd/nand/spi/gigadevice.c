<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Author:
 *	Chuanhong Guo <gch981213@gmail.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mtd/spinand.h>

#घोषणा SPIन_अंकD_MFR_GIGADEVICE			0xC8

#घोषणा GD5FXGQ4XA_STATUS_ECC_1_7_BITFLIPS	(1 << 4)
#घोषणा GD5FXGQ4XA_STATUS_ECC_8_BITFLIPS	(3 << 4)

#घोषणा GD5FXGQ5XE_STATUS_ECC_1_4_BITFLIPS	(1 << 4)
#घोषणा GD5FXGQ5XE_STATUS_ECC_4_BITFLIPS	(3 << 4)

#घोषणा GD5FXGQXXEXXG_REG_STATUS2		0xf0

#घोषणा GD5FXGQ4UXFXXG_STATUS_ECC_MASK		(7 << 4)
#घोषणा GD5FXGQ4UXFXXG_STATUS_ECC_NO_BITFLIPS	(0 << 4)
#घोषणा GD5FXGQ4UXFXXG_STATUS_ECC_1_3_BITFLIPS	(1 << 4)
#घोषणा GD5FXGQ4UXFXXG_STATUS_ECC_UNCOR_ERROR	(7 << 4)

अटल SPIन_अंकD_OP_VARIANTS(पढ़ो_cache_variants,
		SPIन_अंकD_PAGE_READ_FROM_CACHE_QUADIO_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_X4_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_DUALIO_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_X2_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_OP(true, 0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_OP(false, 0, 1, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(पढ़ो_cache_variants_f,
		SPIन_अंकD_PAGE_READ_FROM_CACHE_QUADIO_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_X4_OP_3A(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_DUALIO_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_X2_OP_3A(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_OP_3A(true, 0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_OP_3A(false, 0, 0, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(ग_लिखो_cache_variants,
		SPIन_अंकD_PROG_LOAD_X4(true, 0, शून्य, 0),
		SPIन_अंकD_PROG_LOAD(true, 0, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(update_cache_variants,
		SPIन_अंकD_PROG_LOAD_X4(false, 0, शून्य, 0),
		SPIन_अंकD_PROG_LOAD(false, 0, शून्य, 0));

अटल पूर्णांक gd5fxgq4xa_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				  काष्ठा mtd_oob_region *region)
अणु
	अगर (section > 3)
		वापस -दुस्फल;

	region->offset = (16 * section) + 8;
	region->length = 8;

	वापस 0;
पूर्ण

अटल पूर्णांक gd5fxgq4xa_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				   काष्ठा mtd_oob_region *region)
अणु
	अगर (section > 3)
		वापस -दुस्फल;

	अगर (section) अणु
		region->offset = 16 * section;
		region->length = 8;
	पूर्ण अन्यथा अणु
		/* section 0 has one byte reserved क्रम bad block mark */
		region->offset = 1;
		region->length = 7;
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops gd5fxgq4xa_ooblayout = अणु
	.ecc = gd5fxgq4xa_ooblayout_ecc,
	.मुक्त = gd5fxgq4xa_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक gd5fxgq4xa_ecc_get_status(काष्ठा spinand_device *spinand,
					 u8 status)
अणु
	चयन (status & STATUS_ECC_MASK) अणु
	हाल STATUS_ECC_NO_BITFLIPS:
		वापस 0;

	हाल GD5FXGQ4XA_STATUS_ECC_1_7_BITFLIPS:
		/* 1-7 bits are flipped. वापस the maximum. */
		वापस 7;

	हाल GD5FXGQ4XA_STATUS_ECC_8_BITFLIPS:
		वापस 8;

	हाल STATUS_ECC_UNCOR_ERROR:
		वापस -EBADMSG;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gd5fxgqx_variant2_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				       काष्ठा mtd_oob_region *region)
अणु
	अगर (section)
		वापस -दुस्फल;

	region->offset = 64;
	region->length = 64;

	वापस 0;
पूर्ण

अटल पूर्णांक gd5fxgqx_variant2_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
					काष्ठा mtd_oob_region *region)
अणु
	अगर (section)
		वापस -दुस्फल;

	/* Reserve 1 bytes क्रम the BBM. */
	region->offset = 1;
	region->length = 63;

	वापस 0;
पूर्ण

/* Valid क्रम Q4/Q5 and Q6 (untested) devices */
अटल स्थिर काष्ठा mtd_ooblayout_ops gd5fxgqx_variant2_ooblayout = अणु
	.ecc = gd5fxgqx_variant2_ooblayout_ecc,
	.मुक्त = gd5fxgqx_variant2_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक gd5fxgq4xc_ooblayout_256_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
					काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = 128;
	oobregion->length = 128;

	वापस 0;
पूर्ण

अटल पूर्णांक gd5fxgq4xc_ooblayout_256_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
					 काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = 1;
	oobregion->length = 127;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops gd5fxgq4xc_oob_256_ops = अणु
	.ecc = gd5fxgq4xc_ooblayout_256_ecc,
	.मुक्त = gd5fxgq4xc_ooblayout_256_मुक्त,
पूर्ण;

अटल पूर्णांक gd5fxgq4uexxg_ecc_get_status(काष्ठा spinand_device *spinand,
					u8 status)
अणु
	u8 status2;
	काष्ठा spi_mem_op op = SPIन_अंकD_GET_FEATURE_OP(GD5FXGQXXEXXG_REG_STATUS2,
						      &status2);
	पूर्णांक ret;

	चयन (status & STATUS_ECC_MASK) अणु
	हाल STATUS_ECC_NO_BITFLIPS:
		वापस 0;

	हाल GD5FXGQ4XA_STATUS_ECC_1_7_BITFLIPS:
		/*
		 * Read status2 रेजिस्टर to determine a more fine grained
		 * bit error status
		 */
		ret = spi_mem_exec_op(spinand->spimem, &op);
		अगर (ret)
			वापस ret;

		/*
		 * 4 ... 7 bits are flipped (1..4 can't be detected, so
		 * report the maximum of 4 in this हाल
		 */
		/* bits sorted this way (3...0): ECCS1,ECCS0,ECCSE1,ECCSE0 */
		वापस ((status & STATUS_ECC_MASK) >> 2) |
			((status2 & STATUS_ECC_MASK) >> 4);

	हाल GD5FXGQ4XA_STATUS_ECC_8_BITFLIPS:
		वापस 8;

	हाल STATUS_ECC_UNCOR_ERROR:
		वापस -EBADMSG;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gd5fxgq5xexxg_ecc_get_status(काष्ठा spinand_device *spinand,
					u8 status)
अणु
	u8 status2;
	काष्ठा spi_mem_op op = SPIन_अंकD_GET_FEATURE_OP(GD5FXGQXXEXXG_REG_STATUS2,
						      &status2);
	पूर्णांक ret;

	चयन (status & STATUS_ECC_MASK) अणु
	हाल STATUS_ECC_NO_BITFLIPS:
		वापस 0;

	हाल GD5FXGQ5XE_STATUS_ECC_1_4_BITFLIPS:
		/*
		 * Read status2 रेजिस्टर to determine a more fine grained
		 * bit error status
		 */
		ret = spi_mem_exec_op(spinand->spimem, &op);
		अगर (ret)
			वापस ret;

		/*
		 * 1 ... 4 bits are flipped (and corrected)
		 */
		/* bits sorted this way (1...0): ECCSE1, ECCSE0 */
		वापस ((status2 & STATUS_ECC_MASK) >> 4) + 1;

	हाल STATUS_ECC_UNCOR_ERROR:
		वापस -EBADMSG;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक gd5fxgq4ufxxg_ecc_get_status(काष्ठा spinand_device *spinand,
					u8 status)
अणु
	चयन (status & GD5FXGQ4UXFXXG_STATUS_ECC_MASK) अणु
	हाल GD5FXGQ4UXFXXG_STATUS_ECC_NO_BITFLIPS:
		वापस 0;

	हाल GD5FXGQ4UXFXXG_STATUS_ECC_1_3_BITFLIPS:
		वापस 3;

	हाल GD5FXGQ4UXFXXG_STATUS_ECC_UNCOR_ERROR:
		वापस -EBADMSG;

	शेष: /* (2 << 4) through (6 << 4) are 4-8 corrected errors */
		वापस ((status & GD5FXGQ4UXFXXG_STATUS_ECC_MASK) >> 4) + 2;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा spinand_info gigadevice_spinand_table[] = अणु
	SPIन_अंकD_INFO("GD5F1GQ4xA",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_ADDR, 0xf1),
		     न_अंकD_MEMORG(1, 2048, 64, 64, 1024, 20, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&gd5fxgq4xa_ooblayout,
				     gd5fxgq4xa_ecc_get_status)),
	SPIन_अंकD_INFO("GD5F2GQ4xA",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_ADDR, 0xf2),
		     न_अंकD_MEMORG(1, 2048, 64, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&gd5fxgq4xa_ooblayout,
				     gd5fxgq4xa_ecc_get_status)),
	SPIन_अंकD_INFO("GD5F4GQ4xA",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_ADDR, 0xf4),
		     न_अंकD_MEMORG(1, 2048, 64, 64, 4096, 80, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&gd5fxgq4xa_ooblayout,
				     gd5fxgq4xa_ecc_get_status)),
	SPIन_अंकD_INFO("GD5F4GQ4RC",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE, 0xa4, 0x68),
		     न_अंकD_MEMORG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants_f,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&gd5fxgq4xc_oob_256_ops,
				     gd5fxgq4ufxxg_ecc_get_status)),
	SPIन_अंकD_INFO("GD5F4GQ4UC",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE, 0xb4, 0x68),
		     न_अंकD_MEMORG(1, 4096, 256, 64, 2048, 40, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants_f,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&gd5fxgq4xc_oob_256_ops,
				     gd5fxgq4ufxxg_ecc_get_status)),
	SPIन_अंकD_INFO("GD5F1GQ4UExxG",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_ADDR, 0xd1),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&gd5fxgqx_variant2_ooblayout,
				     gd5fxgq4uexxg_ecc_get_status)),
	SPIन_अंकD_INFO("GD5F1GQ4UFxxG",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE, 0xb1, 0x48),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants_f,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&gd5fxgqx_variant2_ooblayout,
				     gd5fxgq4ufxxg_ecc_get_status)),
	SPIन_अंकD_INFO("GD5F1GQ5UExxG",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0x51),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 1024, 20, 1, 1, 1),
		     न_अंकD_ECCREQ(4, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     SPIन_अंकD_HAS_QE_BIT,
		     SPIन_अंकD_ECCINFO(&gd5fxgqx_variant2_ooblayout,
				     gd5fxgq5xexxg_ecc_get_status)),
पूर्ण;

अटल स्थिर काष्ठा spinand_manufacturer_ops gigadevice_spinand_manuf_ops = अणु
पूर्ण;

स्थिर काष्ठा spinand_manufacturer gigadevice_spinand_manufacturer = अणु
	.id = SPIन_अंकD_MFR_GIGADEVICE,
	.name = "GigaDevice",
	.chips = gigadevice_spinand_table,
	.nchips = ARRAY_SIZE(gigadevice_spinand_table),
	.ops = &gigadevice_spinand_manuf_ops,
पूर्ण;
