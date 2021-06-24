<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2019 Jeff Kletsky
 *
 * Author: Jeff Kletsky <git-commits@allycomm.com>
 */

#समावेश <linux/device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mtd/spinand.h>


#घोषणा SPIन_अंकD_MFR_PARAGON	0xa1


#घोषणा PN26G0XA_STATUS_ECC_BITMASK		(3 << 4)

#घोषणा PN26G0XA_STATUS_ECC_NONE_DETECTED	(0 << 4)
#घोषणा PN26G0XA_STATUS_ECC_1_7_CORRECTED	(1 << 4)
#घोषणा PN26G0XA_STATUS_ECC_ERRORED		(2 << 4)
#घोषणा PN26G0XA_STATUS_ECC_8_CORRECTED		(3 << 4)


अटल SPIन_अंकD_OP_VARIANTS(पढ़ो_cache_variants,
		SPIन_अंकD_PAGE_READ_FROM_CACHE_QUADIO_OP(0, 2, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_X4_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_DUALIO_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_X2_OP(0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_OP(true, 0, 1, शून्य, 0),
		SPIन_अंकD_PAGE_READ_FROM_CACHE_OP(false, 0, 1, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(ग_लिखो_cache_variants,
		SPIन_अंकD_PROG_LOAD_X4(true, 0, शून्य, 0),
		SPIन_अंकD_PROG_LOAD(true, 0, शून्य, 0));

अटल SPIन_अंकD_OP_VARIANTS(update_cache_variants,
		SPIन_अंकD_PROG_LOAD_X4(false, 0, शून्य, 0),
		SPIन_अंकD_PROG_LOAD(false, 0, शून्य, 0));


अटल पूर्णांक pn26g0xa_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				   काष्ठा mtd_oob_region *region)
अणु
	अगर (section > 3)
		वापस -दुस्फल;

	region->offset = 6 + (15 * section); /* 4 BBM + 2 user bytes */
	region->length = 13;

	वापस 0;
पूर्ण

अटल पूर्णांक pn26g0xa_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				   काष्ठा mtd_oob_region *region)
अणु
	अगर (section > 4)
		वापस -दुस्फल;

	अगर (section == 4) अणु
		region->offset = 64;
		region->length = 64;
	पूर्ण अन्यथा अणु
		region->offset = 4 + (15 * section);
		region->length = 2;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक pn26g0xa_ecc_get_status(काष्ठा spinand_device *spinand,
				   u8 status)
अणु
	चयन (status & PN26G0XA_STATUS_ECC_BITMASK) अणु
	हाल PN26G0XA_STATUS_ECC_NONE_DETECTED:
		वापस 0;

	हाल PN26G0XA_STATUS_ECC_1_7_CORRECTED:
		वापस 7;	/* Return upper limit by convention */

	हाल PN26G0XA_STATUS_ECC_8_CORRECTED:
		वापस 8;

	हाल PN26G0XA_STATUS_ECC_ERRORED:
		वापस -EBADMSG;

	शेष:
		अवरोध;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops pn26g0xa_ooblayout = अणु
	.ecc = pn26g0xa_ooblayout_ecc,
	.मुक्त = pn26g0xa_ooblayout_मुक्त,
पूर्ण;


अटल स्थिर काष्ठा spinand_info paragon_spinand_table[] = अणु
	SPIन_अंकD_INFO("PN26G01A",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xe1),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 1024, 21, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&pn26g0xa_ooblayout,
				     pn26g0xa_ecc_get_status)),
	SPIन_अंकD_INFO("PN26G02A",
		     SPIन_अंकD_ID(SPIन_अंकD_READID_METHOD_OPCODE_DUMMY, 0xe2),
		     न_अंकD_MEMORG(1, 2048, 128, 64, 2048, 41, 1, 1, 1),
		     न_अंकD_ECCREQ(8, 512),
		     SPIन_अंकD_INFO_OP_VARIANTS(&पढ़ो_cache_variants,
					      &ग_लिखो_cache_variants,
					      &update_cache_variants),
		     0,
		     SPIन_अंकD_ECCINFO(&pn26g0xa_ooblayout,
				     pn26g0xa_ecc_get_status)),
पूर्ण;

अटल स्थिर काष्ठा spinand_manufacturer_ops paragon_spinand_manuf_ops = अणु
पूर्ण;

स्थिर काष्ठा spinand_manufacturer paragon_spinand_manufacturer = अणु
	.id = SPIन_अंकD_MFR_PARAGON,
	.name = "Paragon",
	.chips = paragon_spinand_table,
	.nchips = ARRAY_SIZE(paragon_spinand_table),
	.ops = &paragon_spinand_manuf_ops,
पूर्ण;
