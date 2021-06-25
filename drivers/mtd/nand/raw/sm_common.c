<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2009 - Maxim Levitsky
 * Common routines & support क्रम xD क्रमmat
 */
#समावेश <linux/kernel.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/module.h>
#समावेश <linux/sizes.h>
#समावेश "sm_common.h"

अटल पूर्णांक oob_sm_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section > 1)
		वापस -दुस्फल;

	oobregion->length = 3;
	oobregion->offset = ((section + 1) * 8) - 3;

	वापस 0;
पूर्ण

अटल पूर्णांक oob_sm_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				 काष्ठा mtd_oob_region *oobregion)
अणु
	चयन (section) अणु
	हाल 0:
		/* reserved */
		oobregion->offset = 0;
		oobregion->length = 4;
		अवरोध;
	हाल 1:
		/* LBA1 */
		oobregion->offset = 6;
		oobregion->length = 2;
		अवरोध;
	हाल 2:
		/* LBA2 */
		oobregion->offset = 11;
		oobregion->length = 2;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops oob_sm_ops = अणु
	.ecc = oob_sm_ooblayout_ecc,
	.मुक्त = oob_sm_ooblayout_मुक्त,
पूर्ण;

/* NOTE: This layout is is not compatabable with SmartMedia, */
/* because the 256 byte devices have page depenent oob layout */
/* However it करोes preserve the bad block markers */
/* If you use smftl, it will bypass this and work correctly */
/* If you not, then you अवरोध SmartMedia compliance anyway */

अटल पूर्णांक oob_sm_small_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
				      काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section)
		वापस -दुस्फल;

	oobregion->length = 3;
	oobregion->offset = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक oob_sm_small_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				       काष्ठा mtd_oob_region *oobregion)
अणु
	चयन (section) अणु
	हाल 0:
		/* reserved */
		oobregion->offset = 3;
		oobregion->length = 2;
		अवरोध;
	हाल 1:
		/* LBA1 */
		oobregion->offset = 6;
		oobregion->length = 2;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops oob_sm_small_ops = अणु
	.ecc = oob_sm_small_ooblayout_ecc,
	.मुक्त = oob_sm_small_ooblayout_मुक्त,
पूर्ण;

अटल पूर्णांक sm_block_markbad(काष्ठा nand_chip *chip, loff_t ofs)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);
	काष्ठा mtd_oob_ops ops;
	काष्ठा sm_oob oob;
	पूर्णांक ret;

	स_रखो(&oob, -1, SM_OOB_SIZE);
	oob.block_status = 0x0F;

	/* As दीर्घ as this function is called on erase block boundaries
		it will work correctly क्रम 256 byte nand */
	ops.mode = MTD_OPS_PLACE_OOB;
	ops.ooboffs = 0;
	ops.ooblen = mtd->oobsize;
	ops.oobbuf = (व्योम *)&oob;
	ops.datbuf = शून्य;


	ret = mtd_ग_लिखो_oob(mtd, ofs, &ops);
	अगर (ret < 0 || ops.oobretlen != SM_OOB_SIZE) अणु
		pr_notice("sm_common: can't mark sector at %i as bad\n",
			  (पूर्णांक)ofs);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा nand_flash_dev nand_smarपंचांगedia_flash_ids[] = अणु
	LEGACY_ID_न_अंकD("SmartMedia 2MiB 3,3V ROM",   0x5d, 2,   SZ_8K, न_अंकD_ROM),
	LEGACY_ID_न_अंकD("SmartMedia 4MiB 3,3V",       0xe3, 4,   SZ_8K, 0),
	LEGACY_ID_न_अंकD("SmartMedia 4MiB 3,3/5V",     0xe5, 4,   SZ_8K, 0),
	LEGACY_ID_न_अंकD("SmartMedia 4MiB 5V",         0x6b, 4,   SZ_8K, 0),
	LEGACY_ID_न_अंकD("SmartMedia 4MiB 3,3V ROM",   0xd5, 4,   SZ_8K, न_अंकD_ROM),
	LEGACY_ID_न_अंकD("SmartMedia 8MiB 3,3V",       0xe6, 8,   SZ_8K, 0),
	LEGACY_ID_न_अंकD("SmartMedia 8MiB 3,3V ROM",   0xd6, 8,   SZ_8K, न_अंकD_ROM),
	LEGACY_ID_न_अंकD("SmartMedia 16MiB 3,3V",      0x73, 16,  SZ_16K, 0),
	LEGACY_ID_न_अंकD("SmartMedia 16MiB 3,3V ROM",  0x57, 16,  SZ_16K, न_अंकD_ROM),
	LEGACY_ID_न_अंकD("SmartMedia 32MiB 3,3V",      0x75, 32,  SZ_16K, 0),
	LEGACY_ID_न_अंकD("SmartMedia 32MiB 3,3V ROM",  0x58, 32,  SZ_16K, न_अंकD_ROM),
	LEGACY_ID_न_अंकD("SmartMedia 64MiB 3,3V",      0x76, 64,  SZ_16K, 0),
	LEGACY_ID_न_अंकD("SmartMedia 64MiB 3,3V ROM",  0xd9, 64,  SZ_16K, न_अंकD_ROM),
	LEGACY_ID_न_अंकD("SmartMedia 128MiB 3,3V",     0x79, 128, SZ_16K, 0),
	LEGACY_ID_न_अंकD("SmartMedia 128MiB 3,3V ROM", 0xda, 128, SZ_16K, न_अंकD_ROM),
	LEGACY_ID_न_अंकD("SmartMedia 256MiB 3, 3V",    0x71, 256, SZ_16K, 0),
	LEGACY_ID_न_अंकD("SmartMedia 256MiB 3,3V ROM", 0x5b, 256, SZ_16K, न_अंकD_ROM),
	अणुशून्यपूर्ण
पूर्ण;

अटल काष्ठा nand_flash_dev nand_xd_flash_ids[] = अणु
	LEGACY_ID_न_अंकD("xD 16MiB 3,3V",  0x73, 16,   SZ_16K, 0),
	LEGACY_ID_न_अंकD("xD 32MiB 3,3V",  0x75, 32,   SZ_16K, 0),
	LEGACY_ID_न_अंकD("xD 64MiB 3,3V",  0x76, 64,   SZ_16K, 0),
	LEGACY_ID_न_अंकD("xD 128MiB 3,3V", 0x79, 128,  SZ_16K, 0),
	LEGACY_ID_न_अंकD("xD 256MiB 3,3V", 0x71, 256,  SZ_16K, न_अंकD_BROKEN_XD),
	LEGACY_ID_न_अंकD("xD 512MiB 3,3V", 0xdc, 512,  SZ_16K, न_अंकD_BROKEN_XD),
	LEGACY_ID_न_अंकD("xD 1GiB 3,3V",   0xd3, 1024, SZ_16K, न_अंकD_BROKEN_XD),
	LEGACY_ID_न_अंकD("xD 2GiB 3,3V",   0xd5, 2048, SZ_16K, न_अंकD_BROKEN_XD),
	अणुशून्यपूर्ण
पूर्ण;

अटल पूर्णांक sm_attach_chip(काष्ठा nand_chip *chip)
अणु
	काष्ठा mtd_info *mtd = nand_to_mtd(chip);

	/* Bad block marker position */
	chip->badblockpos = 0x05;
	chip->badblockbits = 7;
	chip->legacy.block_markbad = sm_block_markbad;

	/* ECC layout */
	अगर (mtd->ग_लिखोsize == SM_SECTOR_SIZE)
		mtd_set_ooblayout(mtd, &oob_sm_ops);
	अन्यथा अगर (mtd->ग_लिखोsize == SM_SMALL_PAGE)
		mtd_set_ooblayout(mtd, &oob_sm_small_ops);
	अन्यथा
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा nand_controller_ops sm_controller_ops = अणु
	.attach_chip = sm_attach_chip,
पूर्ण;

पूर्णांक sm_रेजिस्टर_device(काष्ठा mtd_info *mtd, पूर्णांक smarपंचांगedia)
अणु
	काष्ठा nand_chip *chip = mtd_to_nand(mtd);
	काष्ठा nand_flash_dev *flash_ids;
	पूर्णांक ret;

	chip->options |= न_अंकD_SKIP_BBTSCAN;

	/* Scan क्रम card properties */
	chip->legacy.dummy_controller.ops = &sm_controller_ops;
	flash_ids = smarपंचांगedia ? nand_smarपंचांगedia_flash_ids : nand_xd_flash_ids;
	ret = nand_scan_with_ids(chip, 1, flash_ids);
	अगर (ret)
		वापस ret;

	ret = mtd_device_रेजिस्टर(mtd, शून्य, 0);
	अगर (ret)
		nand_cleanup(chip);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(sm_रेजिस्टर_device);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Maxim Levitsky <maximlevitsky@gmail.com>");
MODULE_DESCRIPTION("Common SmartMedia/xD functions");
