<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2009 - Maxim Levitsky
 * SmartMedia/xD translation layer
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/bitops.h>
#समावेश <linux/slab.h>
#समावेश <linux/mtd/nand-ecc-sw-hamming.h>
#समावेश "nand/raw/sm_common.h"
#समावेश "sm_ftl.h"



अटल काष्ठा workqueue_काष्ठा *cache_flush_workqueue;

अटल पूर्णांक cache_समयout = 1000;
module_param(cache_समयout, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(cache_समयout,
	"Timeout (in ms) for cache flush (1000 ms default");

अटल पूर्णांक debug;
module_param(debug, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Debug level (0-2)");


/* ------------------- sysfs attributes ---------------------------------- */
काष्ठा sm_sysfs_attribute अणु
	काष्ठा device_attribute dev_attr;
	अक्षर *data;
	पूर्णांक len;
पूर्ण;

अटल sमाप_प्रकार sm_attr_show(काष्ठा device *dev, काष्ठा device_attribute *attr,
		     अक्षर *buf)
अणु
	काष्ठा sm_sysfs_attribute *sm_attr =
		container_of(attr, काष्ठा sm_sysfs_attribute, dev_attr);

	म_नकलन(buf, sm_attr->data, sm_attr->len);
	वापस sm_attr->len;
पूर्ण


#घोषणा NUM_ATTRIBUTES 1
#घोषणा SM_CIS_VENDOR_OFFSET 0x59
अटल काष्ठा attribute_group *sm_create_sysfs_attributes(काष्ठा sm_ftl *ftl)
अणु
	काष्ठा attribute_group *attr_group;
	काष्ठा attribute **attributes;
	काष्ठा sm_sysfs_attribute *venकरोr_attribute;
	अक्षर *venकरोr;

	venकरोr = kstrndup(ftl->cis_buffer + SM_CIS_VENDOR_OFFSET,
			  SM_SMALL_PAGE - SM_CIS_VENDOR_OFFSET, GFP_KERNEL);
	अगर (!venकरोr)
		जाओ error1;

	/* Initialize sysfs attributes */
	venकरोr_attribute =
		kzalloc(माप(काष्ठा sm_sysfs_attribute), GFP_KERNEL);
	अगर (!venकरोr_attribute)
		जाओ error2;

	sysfs_attr_init(&venकरोr_attribute->dev_attr.attr);

	venकरोr_attribute->data = venकरोr;
	venकरोr_attribute->len = म_माप(venकरोr);
	venकरोr_attribute->dev_attr.attr.name = "vendor";
	venकरोr_attribute->dev_attr.attr.mode = S_IRUGO;
	venकरोr_attribute->dev_attr.show = sm_attr_show;


	/* Create array of poपूर्णांकers to the attributes */
	attributes = kसुस्मृति(NUM_ATTRIBUTES + 1, माप(काष्ठा attribute *),
								GFP_KERNEL);
	अगर (!attributes)
		जाओ error3;
	attributes[0] = &venकरोr_attribute->dev_attr.attr;

	/* Finally create the attribute group */
	attr_group = kzalloc(माप(काष्ठा attribute_group), GFP_KERNEL);
	अगर (!attr_group)
		जाओ error4;
	attr_group->attrs = attributes;
	वापस attr_group;
error4:
	kमुक्त(attributes);
error3:
	kमुक्त(venकरोr_attribute);
error2:
	kमुक्त(venकरोr);
error1:
	वापस शून्य;
पूर्ण

अटल व्योम sm_delete_sysfs_attributes(काष्ठा sm_ftl *ftl)
अणु
	काष्ठा attribute **attributes = ftl->disk_attributes->attrs;
	पूर्णांक i;

	क्रम (i = 0; attributes[i] ; i++) अणु

		काष्ठा device_attribute *dev_attr = container_of(attributes[i],
			काष्ठा device_attribute, attr);

		काष्ठा sm_sysfs_attribute *sm_attr =
			container_of(dev_attr,
				काष्ठा sm_sysfs_attribute, dev_attr);

		kमुक्त(sm_attr->data);
		kमुक्त(sm_attr);
	पूर्ण

	kमुक्त(ftl->disk_attributes->attrs);
	kमुक्त(ftl->disk_attributes);
पूर्ण


/* ----------------------- oob helpers -------------------------------------- */

अटल पूर्णांक sm_get_lba(uपूर्णांक8_t *lba)
अणु
	/* check fixed bits */
	अगर ((lba[0] & 0xF8) != 0x10)
		वापस -2;

	/* check parity - endianness करोesn't matter */
	अगर (hweight16(*(uपूर्णांक16_t *)lba) & 1)
		वापस -2;

	वापस (lba[1] >> 1) | ((lba[0] & 0x07) << 7);
पूर्ण


/*
 * Read LBA associated with block
 * वापसs -1, अगर block is erased
 * वापसs -2 अगर error happens
 */
अटल पूर्णांक sm_पढ़ो_lba(काष्ठा sm_oob *oob)
अणु
	अटल स्थिर uपूर्णांक32_t erased_pattern[4] = अणु
		0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF पूर्ण;

	uपूर्णांक16_t lba_test;
	पूर्णांक lba;

	/* First test क्रम erased block */
	अगर (!स_भेद(oob, erased_pattern, SM_OOB_SIZE))
		वापस -1;

	/* Now check is both copies of the LBA dअगरfer too much */
	lba_test = *(uपूर्णांक16_t *)oob->lba_copy1 ^ *(uपूर्णांक16_t*)oob->lba_copy2;
	अगर (lba_test && !is_घातer_of_2(lba_test))
		वापस -2;

	/* And पढ़ो it */
	lba = sm_get_lba(oob->lba_copy1);

	अगर (lba == -2)
		lba = sm_get_lba(oob->lba_copy2);

	वापस lba;
पूर्ण

अटल व्योम sm_ग_लिखो_lba(काष्ठा sm_oob *oob, uपूर्णांक16_t lba)
अणु
	uपूर्णांक8_t पंचांगp[2];

	WARN_ON(lba >= 1000);

	पंचांगp[0] = 0x10 | ((lba >> 7) & 0x07);
	पंचांगp[1] = (lba << 1) & 0xFF;

	अगर (hweight16(*(uपूर्णांक16_t *)पंचांगp) & 0x01)
		पंचांगp[1] |= 1;

	oob->lba_copy1[0] = oob->lba_copy2[0] = पंचांगp[0];
	oob->lba_copy1[1] = oob->lba_copy2[1] = पंचांगp[1];
पूर्ण


/* Make offset from parts */
अटल loff_t sm_mkoffset(काष्ठा sm_ftl *ftl, पूर्णांक zone, पूर्णांक block, पूर्णांक boffset)
अणु
	WARN_ON(boffset & (SM_SECTOR_SIZE - 1));
	WARN_ON(zone < 0 || zone >= ftl->zone_count);
	WARN_ON(block >= ftl->zone_size);
	WARN_ON(boffset >= ftl->block_size);

	अगर (block == -1)
		वापस -1;

	वापस (zone * SM_MAX_ZONE_SIZE + block) * ftl->block_size + boffset;
पूर्ण

/* Breaks offset पूर्णांकo parts */
अटल व्योम sm_अवरोध_offset(काष्ठा sm_ftl *ftl, loff_t loffset,
			    पूर्णांक *zone, पूर्णांक *block, पूर्णांक *boffset)
अणु
	u64 offset = loffset;
	*boffset = करो_भाग(offset, ftl->block_size);
	*block = करो_भाग(offset, ftl->max_lba);
	*zone = offset >= ftl->zone_count ? -1 : offset;
पूर्ण

/* ---------------------- low level IO ------------------------------------- */

अटल पूर्णांक sm_correct_sector(uपूर्णांक8_t *buffer, काष्ठा sm_oob *oob)
अणु
	bool sm_order = IS_ENABLED(CONFIG_MTD_न_अंकD_ECC_SW_HAMMING_SMC);
	uपूर्णांक8_t ecc[3];

	ecc_sw_hamming_calculate(buffer, SM_SMALL_PAGE, ecc, sm_order);
	अगर (ecc_sw_hamming_correct(buffer, ecc, oob->ecc1, SM_SMALL_PAGE,
				   sm_order) < 0)
		वापस -EIO;

	buffer += SM_SMALL_PAGE;

	ecc_sw_hamming_calculate(buffer, SM_SMALL_PAGE, ecc, sm_order);
	अगर (ecc_sw_hamming_correct(buffer, ecc, oob->ecc2, SM_SMALL_PAGE,
				   sm_order) < 0)
		वापस -EIO;
	वापस 0;
पूर्ण

/* Reads a sector + oob*/
अटल पूर्णांक sm_पढ़ो_sector(काष्ठा sm_ftl *ftl,
			  पूर्णांक zone, पूर्णांक block, पूर्णांक boffset,
			  uपूर्णांक8_t *buffer, काष्ठा sm_oob *oob)
अणु
	काष्ठा mtd_info *mtd = ftl->trans->mtd;
	काष्ठा mtd_oob_ops ops;
	काष्ठा sm_oob पंचांगp_oob;
	पूर्णांक ret = -EIO;
	पूर्णांक try = 0;

	/* FTL can contain -1 entries that are by शेष filled with bits */
	अगर (block == -1) अणु
		अगर (buffer)
			स_रखो(buffer, 0xFF, SM_SECTOR_SIZE);
		वापस 0;
	पूर्ण

	/* User might not need the oob, but we करो क्रम data verअगरication */
	अगर (!oob)
		oob = &पंचांगp_oob;

	ops.mode = ftl->smallpagenand ? MTD_OPS_RAW : MTD_OPS_PLACE_OOB;
	ops.ooboffs = 0;
	ops.ooblen = SM_OOB_SIZE;
	ops.oobbuf = (व्योम *)oob;
	ops.len = SM_SECTOR_SIZE;
	ops.datbuf = buffer;

again:
	अगर (try++) अणु
		/* Aव्योम infinite recursion on CIS पढ़ोs, sm_recheck_media
			won't help anyway */
		अगर (zone == 0 && block == ftl->cis_block && boffset ==
			ftl->cis_boffset)
			वापस ret;

		/* Test अगर media is stable */
		अगर (try == 3 || sm_recheck_media(ftl))
			वापस ret;
	पूर्ण

	/* Unक्रमtunately, oob पढ़ो will _always_ succeed,
		despite card removal..... */
	ret = mtd_पढ़ो_oob(mtd, sm_mkoffset(ftl, zone, block, boffset), &ops);

	/* Test क्रम unknown errors */
	अगर (ret != 0 && !mtd_is_bitflip_or_eccerr(ret)) अणु
		dbg("read of block %d at zone %d, failed due to error (%d)",
			block, zone, ret);
		जाओ again;
	पूर्ण

	/* Do a basic test on the oob, to guard against वापसed garbage */
	अगर (oob->reserved != 0xFFFFFFFF && !is_घातer_of_2(~oob->reserved))
		जाओ again;

	/* This should never happen, unless there is a bug in the mtd driver */
	WARN_ON(ops.oobretlen != SM_OOB_SIZE);
	WARN_ON(buffer && ops.retlen != SM_SECTOR_SIZE);

	अगर (!buffer)
		वापस 0;

	/* Test अगर sector marked as bad */
	अगर (!sm_sector_valid(oob)) अणु
		dbg("read of block %d at zone %d, failed because it is marked"
			" as bad" , block, zone);
		जाओ again;
	पूर्ण

	/* Test ECC*/
	अगर (mtd_is_eccerr(ret) ||
		(ftl->smallpagenand && sm_correct_sector(buffer, oob))) अणु

		dbg("read of block %d at zone %d, failed due to ECC error",
			block, zone);
		जाओ again;
	पूर्ण

	वापस 0;
पूर्ण

/* Writes a sector to media */
अटल पूर्णांक sm_ग_लिखो_sector(काष्ठा sm_ftl *ftl,
			   पूर्णांक zone, पूर्णांक block, पूर्णांक boffset,
			   uपूर्णांक8_t *buffer, काष्ठा sm_oob *oob)
अणु
	काष्ठा mtd_oob_ops ops;
	काष्ठा mtd_info *mtd = ftl->trans->mtd;
	पूर्णांक ret;

	BUG_ON(ftl->पढ़ोonly);

	अगर (zone == 0 && (block == ftl->cis_block || block == 0)) अणु
		dbg("attempted to write the CIS!");
		वापस -EIO;
	पूर्ण

	अगर (ftl->unstable)
		वापस -EIO;

	ops.mode = ftl->smallpagenand ? MTD_OPS_RAW : MTD_OPS_PLACE_OOB;
	ops.len = SM_SECTOR_SIZE;
	ops.datbuf = buffer;
	ops.ooboffs = 0;
	ops.ooblen = SM_OOB_SIZE;
	ops.oobbuf = (व्योम *)oob;

	ret = mtd_ग_लिखो_oob(mtd, sm_mkoffset(ftl, zone, block, boffset), &ops);

	/* Now we assume that hardware will catch ग_लिखो bitflip errors */

	अगर (ret) अणु
		dbg("write to block %d at zone %d, failed with error %d",
			block, zone, ret);

		sm_recheck_media(ftl);
		वापस ret;
	पूर्ण

	/* This should never happen, unless there is a bug in the driver */
	WARN_ON(ops.oobretlen != SM_OOB_SIZE);
	WARN_ON(buffer && ops.retlen != SM_SECTOR_SIZE);

	वापस 0;
पूर्ण

/* ------------------------ block IO ------------------------------------- */

/* Write a block using data and lba, and invalid sector biपंचांगap */
अटल पूर्णांक sm_ग_लिखो_block(काष्ठा sm_ftl *ftl, uपूर्णांक8_t *buf,
			  पूर्णांक zone, पूर्णांक block, पूर्णांक lba,
			  अचिन्हित दीर्घ invalid_biपंचांगap)
अणु
	bool sm_order = IS_ENABLED(CONFIG_MTD_न_अंकD_ECC_SW_HAMMING_SMC);
	काष्ठा sm_oob oob;
	पूर्णांक boffset;
	पूर्णांक retry = 0;

	/* Initialize the oob with requested values */
	स_रखो(&oob, 0xFF, SM_OOB_SIZE);
	sm_ग_लिखो_lba(&oob, lba);
restart:
	अगर (ftl->unstable)
		वापस -EIO;

	क्रम (boffset = 0; boffset < ftl->block_size;
				boffset += SM_SECTOR_SIZE) अणु

		oob.data_status = 0xFF;

		अगर (test_bit(boffset / SM_SECTOR_SIZE, &invalid_biपंचांगap)) अणु

			sm_prपूर्णांकk("sector %d of block at LBA %d of zone %d"
				" couldn't be read, marking it as invalid",
				boffset / SM_SECTOR_SIZE, lba, zone);

			oob.data_status = 0;
		पूर्ण

		अगर (ftl->smallpagenand) अणु
			ecc_sw_hamming_calculate(buf + boffset,
						 SM_SMALL_PAGE, oob.ecc1,
						 sm_order);

			ecc_sw_hamming_calculate(buf + boffset + SM_SMALL_PAGE,
						 SM_SMALL_PAGE, oob.ecc2,
						 sm_order);
		पूर्ण
		अगर (!sm_ग_लिखो_sector(ftl, zone, block, boffset,
							buf + boffset, &oob))
			जारी;

		अगर (!retry) अणु

			/* If ग_लिखो fails. try to erase the block */
			/* This is safe, because we never ग_लिखो in blocks
				that contain valuable data.
			This is पूर्णांकended to repair block that are marked
			as erased, but that isn't fully erased*/

			अगर (sm_erase_block(ftl, zone, block, 0))
				वापस -EIO;

			retry = 1;
			जाओ restart;
		पूर्ण अन्यथा अणु
			sm_mark_block_bad(ftl, zone, block);
			वापस -EIO;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


/* Mark whole block at offset 'offs' as bad. */
अटल व्योम sm_mark_block_bad(काष्ठा sm_ftl *ftl, पूर्णांक zone, पूर्णांक block)
अणु
	काष्ठा sm_oob oob;
	पूर्णांक boffset;

	स_रखो(&oob, 0xFF, SM_OOB_SIZE);
	oob.block_status = 0xF0;

	अगर (ftl->unstable)
		वापस;

	अगर (sm_recheck_media(ftl))
		वापस;

	sm_prपूर्णांकk("marking block %d of zone %d as bad", block, zone);

	/* We aren't checking the return value, because we don't care */
	/* This also fails on fake xD cards, but I guess these won't expose
		any bad blocks till fail completely */
	क्रम (boffset = 0; boffset < ftl->block_size; boffset += SM_SECTOR_SIZE)
		sm_ग_लिखो_sector(ftl, zone, block, boffset, शून्य, &oob);
पूर्ण

/*
 * Erase a block within a zone
 * If erase succeeds, it updates मुक्त block fअगरo, otherwise marks block as bad
 */
अटल पूर्णांक sm_erase_block(काष्ठा sm_ftl *ftl, पूर्णांक zone_num, uपूर्णांक16_t block,
			  पूर्णांक put_मुक्त)
अणु
	काष्ठा ftl_zone *zone = &ftl->zones[zone_num];
	काष्ठा mtd_info *mtd = ftl->trans->mtd;
	काष्ठा erase_info erase;

	erase.addr = sm_mkoffset(ftl, zone_num, block, 0);
	erase.len = ftl->block_size;

	अगर (ftl->unstable)
		वापस -EIO;

	BUG_ON(ftl->पढ़ोonly);

	अगर (zone_num == 0 && (block == ftl->cis_block || block == 0)) अणु
		sm_prपूर्णांकk("attempted to erase the CIS!");
		वापस -EIO;
	पूर्ण

	अगर (mtd_erase(mtd, &erase)) अणु
		sm_prपूर्णांकk("erase of block %d in zone %d failed",
							block, zone_num);
		जाओ error;
	पूर्ण

	अगर (put_मुक्त)
		kfअगरo_in(&zone->मुक्त_sectors,
			(स्थिर अचिन्हित अक्षर *)&block, माप(block));

	वापस 0;
error:
	sm_mark_block_bad(ftl, zone_num, block);
	वापस -EIO;
पूर्ण

/* Thoroughly test that block is valid. */
अटल पूर्णांक sm_check_block(काष्ठा sm_ftl *ftl, पूर्णांक zone, पूर्णांक block)
अणु
	पूर्णांक boffset;
	काष्ठा sm_oob oob;
	पूर्णांक lbas[] = अणु -3, 0, 0, 0 पूर्ण;
	पूर्णांक i = 0;
	पूर्णांक test_lba;


	/* First just check that block करोesn't look fishy */
	/* Only blocks that are valid or are sliced in two parts, are
		accepted */
	क्रम (boffset = 0; boffset < ftl->block_size;
					boffset += SM_SECTOR_SIZE) अणु

		/* This shouldn't happen anyway */
		अगर (sm_पढ़ो_sector(ftl, zone, block, boffset, शून्य, &oob))
			वापस -2;

		test_lba = sm_पढ़ो_lba(&oob);

		अगर (lbas[i] != test_lba)
			lbas[++i] = test_lba;

		/* If we found three dअगरferent LBAs, something is fishy */
		अगर (i == 3)
			वापस -EIO;
	पूर्ण

	/* If the block is sliced (partially erased usually) erase it */
	अगर (i == 2) अणु
		sm_erase_block(ftl, zone, block, 1);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

/* ----------------- media scanning --------------------------------- */
अटल स्थिर काष्ठा chs_entry chs_table[] = अणु
	अणु 1,    125,  4,  4  पूर्ण,
	अणु 2,    125,  4,  8  पूर्ण,
	अणु 4,    250,  4,  8  पूर्ण,
	अणु 8,    250,  4,  16 पूर्ण,
	अणु 16,   500,  4,  16 पूर्ण,
	अणु 32,   500,  8,  16 पूर्ण,
	अणु 64,   500,  8,  32 पूर्ण,
	अणु 128,  500,  16, 32 पूर्ण,
	अणु 256,  1000, 16, 32 पूर्ण,
	अणु 512,  1015, 32, 63 पूर्ण,
	अणु 1024, 985,  33, 63 पूर्ण,
	अणु 2048, 985,  33, 63 पूर्ण,
	अणु 0 पूर्ण,
पूर्ण;


अटल स्थिर uपूर्णांक8_t cis_signature[] = अणु
	0x01, 0x03, 0xD9, 0x01, 0xFF, 0x18, 0x02, 0xDF, 0x01, 0x20
पूर्ण;
/* Find out media parameters.
 * This ideally has to be based on nand id, but क्रम now device size is enough */
अटल पूर्णांक sm_get_media_info(काष्ठा sm_ftl *ftl, काष्ठा mtd_info *mtd)
अणु
	पूर्णांक i;
	पूर्णांक size_in_megs = mtd->size / (1024 * 1024);

	ftl->पढ़ोonly = mtd->type == MTD_ROM;

	/* Manual settings क्रम very old devices */
	ftl->zone_count = 1;
	ftl->smallpagenand = 0;

	चयन (size_in_megs) अणु
	हाल 1:
		/* 1 MiB flash/rom SmartMedia card (256 byte pages)*/
		ftl->zone_size = 256;
		ftl->max_lba = 250;
		ftl->block_size = 8 * SM_SECTOR_SIZE;
		ftl->smallpagenand = 1;

		अवरोध;
	हाल 2:
		/* 2 MiB flash SmartMedia (256 byte pages)*/
		अगर (mtd->ग_लिखोsize == SM_SMALL_PAGE) अणु
			ftl->zone_size = 512;
			ftl->max_lba = 500;
			ftl->block_size = 8 * SM_SECTOR_SIZE;
			ftl->smallpagenand = 1;
		/* 2 MiB rom SmartMedia */
		पूर्ण अन्यथा अणु

			अगर (!ftl->पढ़ोonly)
				वापस -ENODEV;

			ftl->zone_size = 256;
			ftl->max_lba = 250;
			ftl->block_size = 16 * SM_SECTOR_SIZE;
		पूर्ण
		अवरोध;
	हाल 4:
		/* 4 MiB flash/rom SmartMedia device */
		ftl->zone_size = 512;
		ftl->max_lba = 500;
		ftl->block_size = 16 * SM_SECTOR_SIZE;
		अवरोध;
	हाल 8:
		/* 8 MiB flash/rom SmartMedia device */
		ftl->zone_size = 1024;
		ftl->max_lba = 1000;
		ftl->block_size = 16 * SM_SECTOR_SIZE;
	पूर्ण

	/* Minimum xD size is 16MiB. Also, all xD cards have standard zone
	   sizes. SmartMedia cards exist up to 128 MiB and have same layout*/
	अगर (size_in_megs >= 16) अणु
		ftl->zone_count = size_in_megs / 16;
		ftl->zone_size = 1024;
		ftl->max_lba = 1000;
		ftl->block_size = 32 * SM_SECTOR_SIZE;
	पूर्ण

	/* Test क्रम proper ग_लिखो,erase and oob sizes */
	अगर (mtd->erasesize > ftl->block_size)
		वापस -ENODEV;

	अगर (mtd->ग_लिखोsize > SM_SECTOR_SIZE)
		वापस -ENODEV;

	अगर (ftl->smallpagenand && mtd->oobsize < SM_SMALL_OOB_SIZE)
		वापस -ENODEV;

	अगर (!ftl->smallpagenand && mtd->oobsize < SM_OOB_SIZE)
		वापस -ENODEV;

	/* We use OOB */
	अगर (!mtd_has_oob(mtd))
		वापस -ENODEV;

	/* Find geometry inक्रमmation */
	क्रम (i = 0 ; i < ARRAY_SIZE(chs_table) ; i++) अणु
		अगर (chs_table[i].size == size_in_megs) अणु
			ftl->cylinders = chs_table[i].cyl;
			ftl->heads = chs_table[i].head;
			ftl->sectors = chs_table[i].sec;
			वापस 0;
		पूर्ण
	पूर्ण

	sm_prपूर्णांकk("media has unknown size : %dMiB", size_in_megs);
	ftl->cylinders = 985;
	ftl->heads =  33;
	ftl->sectors = 63;
	वापस 0;
पूर्ण

/* Validate the CIS */
अटल पूर्णांक sm_पढ़ो_cis(काष्ठा sm_ftl *ftl)
अणु
	काष्ठा sm_oob oob;

	अगर (sm_पढ़ो_sector(ftl,
		0, ftl->cis_block, ftl->cis_boffset, ftl->cis_buffer, &oob))
			वापस -EIO;

	अगर (!sm_sector_valid(&oob) || !sm_block_valid(&oob))
		वापस -EIO;

	अगर (!स_भेद(ftl->cis_buffer + ftl->cis_page_offset,
			cis_signature, माप(cis_signature))) अणु
		वापस 0;
	पूर्ण

	वापस -EIO;
पूर्ण

/* Scan the media क्रम the CIS */
अटल पूर्णांक sm_find_cis(काष्ठा sm_ftl *ftl)
अणु
	काष्ठा sm_oob oob;
	पूर्णांक block, boffset;
	पूर्णांक block_found = 0;
	पूर्णांक cis_found = 0;

	/* Search क्रम first valid block */
	क्रम (block = 0 ; block < ftl->zone_size - ftl->max_lba ; block++) अणु

		अगर (sm_पढ़ो_sector(ftl, 0, block, 0, शून्य, &oob))
			जारी;

		अगर (!sm_block_valid(&oob))
			जारी;
		block_found = 1;
		अवरोध;
	पूर्ण

	अगर (!block_found)
		वापस -EIO;

	/* Search क्रम first valid sector in this block */
	क्रम (boffset = 0 ; boffset < ftl->block_size;
						boffset += SM_SECTOR_SIZE) अणु

		अगर (sm_पढ़ो_sector(ftl, 0, block, boffset, शून्य, &oob))
			जारी;

		अगर (!sm_sector_valid(&oob))
			जारी;
		अवरोध;
	पूर्ण

	अगर (boffset == ftl->block_size)
		वापस -EIO;

	ftl->cis_block = block;
	ftl->cis_boffset = boffset;
	ftl->cis_page_offset = 0;

	cis_found = !sm_पढ़ो_cis(ftl);

	अगर (!cis_found) अणु
		ftl->cis_page_offset = SM_SMALL_PAGE;
		cis_found = !sm_पढ़ो_cis(ftl);
	पूर्ण

	अगर (cis_found) अणु
		dbg("CIS block found at offset %x",
			block * ftl->block_size +
				boffset + ftl->cis_page_offset);
		वापस 0;
	पूर्ण
	वापस -EIO;
पूर्ण

/* Basic test to determine अगर underlying mtd device अगर functional */
अटल पूर्णांक sm_recheck_media(काष्ठा sm_ftl *ftl)
अणु
	अगर (sm_पढ़ो_cis(ftl)) अणु

		अगर (!ftl->unstable) अणु
			sm_prपूर्णांकk("media unstable, not allowing writes");
			ftl->unstable = 1;
		पूर्ण
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/* Initialize a FTL zone */
अटल पूर्णांक sm_init_zone(काष्ठा sm_ftl *ftl, पूर्णांक zone_num)
अणु
	काष्ठा ftl_zone *zone = &ftl->zones[zone_num];
	काष्ठा sm_oob oob;
	uपूर्णांक16_t block;
	पूर्णांक lba;
	पूर्णांक i = 0;
	पूर्णांक len;

	dbg("initializing zone %d", zone_num);

	/* Allocate memory क्रम FTL table */
	zone->lba_to_phys_table = kदो_स्मृति_array(ftl->max_lba, 2, GFP_KERNEL);

	अगर (!zone->lba_to_phys_table)
		वापस -ENOMEM;
	स_रखो(zone->lba_to_phys_table, -1, ftl->max_lba * 2);


	/* Allocate memory क्रम मुक्त sectors FIFO */
	अगर (kfअगरo_alloc(&zone->मुक्त_sectors, ftl->zone_size * 2, GFP_KERNEL)) अणु
		kमुक्त(zone->lba_to_phys_table);
		वापस -ENOMEM;
	पूर्ण

	/* Now scan the zone */
	क्रम (block = 0 ; block < ftl->zone_size ; block++) अणु

		/* Skip blocks till the CIS (including) */
		अगर (zone_num == 0 && block <= ftl->cis_block)
			जारी;

		/* Read the oob of first sector */
		अगर (sm_पढ़ो_sector(ftl, zone_num, block, 0, शून्य, &oob)) अणु
			kfअगरo_मुक्त(&zone->मुक्त_sectors);
			kमुक्त(zone->lba_to_phys_table);
			वापस -EIO;
		पूर्ण

		/* Test to see अगर block is erased. It is enough to test
			first sector, because erase happens in one shot */
		अगर (sm_block_erased(&oob)) अणु
			kfअगरo_in(&zone->मुक्त_sectors,
				(अचिन्हित अक्षर *)&block, 2);
			जारी;
		पूर्ण

		/* If block is marked as bad, skip it */
		/* This assumes we can trust first sector*/
		/* However the way the block valid status is defined, ensures
			very low probability of failure here */
		अगर (!sm_block_valid(&oob)) अणु
			dbg("PH %04d <-> <marked bad>", block);
			जारी;
		पूर्ण


		lba = sm_पढ़ो_lba(&oob);

		/* Invalid LBA means that block is damaged. */
		/* We can try to erase it, or mark it as bad, but
			lets leave that to recovery application */
		अगर (lba == -2 || lba >= ftl->max_lba) अणु
			dbg("PH %04d <-> LBA %04d(bad)", block, lba);
			जारी;
		पूर्ण


		/* If there is no collision,
			just put the sector in the FTL table */
		अगर (zone->lba_to_phys_table[lba] < 0) अणु
			dbg_verbose("PH %04d <-> LBA %04d", block, lba);
			zone->lba_to_phys_table[lba] = block;
			जारी;
		पूर्ण

		sm_prपूर्णांकk("collision"
			" of LBA %d between blocks %d and %d in zone %d",
			lba, zone->lba_to_phys_table[lba], block, zone_num);

		/* Test that this block is valid*/
		अगर (sm_check_block(ftl, zone_num, block))
			जारी;

		/* Test now the old block */
		अगर (sm_check_block(ftl, zone_num,
					zone->lba_to_phys_table[lba])) अणु
			zone->lba_to_phys_table[lba] = block;
			जारी;
		पूर्ण

		/* If both blocks are valid and share same LBA, it means that
			they hold dअगरferent versions of same data. It not
			known which is more recent, thus just erase one of them
		*/
		sm_prपूर्णांकk("both blocks are valid, erasing the later");
		sm_erase_block(ftl, zone_num, block, 1);
	पूर्ण

	dbg("zone initialized");
	zone->initialized = 1;

	/* No मुक्त sectors, means that the zone is heavily damaged, ग_लिखो won't
		work, but it can still can be (partially) पढ़ो */
	अगर (!kfअगरo_len(&zone->मुक्त_sectors)) अणु
		sm_prपूर्णांकk("no free blocks in zone %d", zone_num);
		वापस 0;
	पूर्ण

	/* Ranकरोmize first block we ग_लिखो to */
	get_अक्रमom_bytes(&i, 2);
	i %= (kfअगरo_len(&zone->मुक्त_sectors) / 2);

	जबतक (i--) अणु
		len = kfअगरo_out(&zone->मुक्त_sectors,
					(अचिन्हित अक्षर *)&block, 2);
		WARN_ON(len != 2);
		kfअगरo_in(&zone->मुक्त_sectors, (स्थिर अचिन्हित अक्षर *)&block, 2);
	पूर्ण
	वापस 0;
पूर्ण

/* Get and स्वतःmatically initialize an FTL mapping क्रम one zone */
अटल काष्ठा ftl_zone *sm_get_zone(काष्ठा sm_ftl *ftl, पूर्णांक zone_num)
अणु
	काष्ठा ftl_zone *zone;
	पूर्णांक error;

	BUG_ON(zone_num >= ftl->zone_count);
	zone = &ftl->zones[zone_num];

	अगर (!zone->initialized) अणु
		error = sm_init_zone(ftl, zone_num);

		अगर (error)
			वापस ERR_PTR(error);
	पूर्ण
	वापस zone;
पूर्ण


/* ----------------- cache handling ------------------------------------------*/

/* Initialize the one block cache */
अटल व्योम sm_cache_init(काष्ठा sm_ftl *ftl)
अणु
	ftl->cache_data_invalid_biपंचांगap = 0xFFFFFFFF;
	ftl->cache_clean = 1;
	ftl->cache_zone = -1;
	ftl->cache_block = -1;
	/*स_रखो(ftl->cache_data, 0xAA, ftl->block_size);*/
पूर्ण

/* Put sector in one block cache */
अटल व्योम sm_cache_put(काष्ठा sm_ftl *ftl, अक्षर *buffer, पूर्णांक boffset)
अणु
	स_नकल(ftl->cache_data + boffset, buffer, SM_SECTOR_SIZE);
	clear_bit(boffset / SM_SECTOR_SIZE, &ftl->cache_data_invalid_biपंचांगap);
	ftl->cache_clean = 0;
पूर्ण

/* Read a sector from the cache */
अटल पूर्णांक sm_cache_get(काष्ठा sm_ftl *ftl, अक्षर *buffer, पूर्णांक boffset)
अणु
	अगर (test_bit(boffset / SM_SECTOR_SIZE,
		&ftl->cache_data_invalid_biपंचांगap))
			वापस -1;

	स_नकल(buffer, ftl->cache_data + boffset, SM_SECTOR_SIZE);
	वापस 0;
पूर्ण

/* Write the cache to hardware */
अटल पूर्णांक sm_cache_flush(काष्ठा sm_ftl *ftl)
अणु
	काष्ठा ftl_zone *zone;

	पूर्णांक sector_num;
	uपूर्णांक16_t ग_लिखो_sector;
	पूर्णांक zone_num = ftl->cache_zone;
	पूर्णांक block_num;

	अगर (ftl->cache_clean)
		वापस 0;

	अगर (ftl->unstable)
		वापस -EIO;

	BUG_ON(zone_num < 0);
	zone = &ftl->zones[zone_num];
	block_num = zone->lba_to_phys_table[ftl->cache_block];


	/* Try to पढ़ो all unपढ़ो areas of the cache block*/
	क्रम_each_set_bit(sector_num, &ftl->cache_data_invalid_biपंचांगap,
		ftl->block_size / SM_SECTOR_SIZE) अणु

		अगर (!sm_पढ़ो_sector(ftl,
			zone_num, block_num, sector_num * SM_SECTOR_SIZE,
			ftl->cache_data + sector_num * SM_SECTOR_SIZE, शून्य))
				clear_bit(sector_num,
					&ftl->cache_data_invalid_biपंचांगap);
	पूर्ण
restart:

	अगर (ftl->unstable)
		वापस -EIO;

	/* If there are no spare blocks, */
	/* we could still जारी by erasing/writing the current block,
		but क्रम such worn out media it करोesn't worth the trouble,
			and the dangers */
	अगर (kfअगरo_out(&zone->मुक्त_sectors,
				(अचिन्हित अक्षर *)&ग_लिखो_sector, 2) != 2) अणु
		dbg("no free sectors for write!");
		वापस -EIO;
	पूर्ण


	अगर (sm_ग_लिखो_block(ftl, ftl->cache_data, zone_num, ग_लिखो_sector,
		ftl->cache_block, ftl->cache_data_invalid_biपंचांगap))
			जाओ restart;

	/* Update the FTL table */
	zone->lba_to_phys_table[ftl->cache_block] = ग_लिखो_sector;

	/* Write succesfull, so erase and मुक्त the old block */
	अगर (block_num > 0)
		sm_erase_block(ftl, zone_num, block_num, 1);

	sm_cache_init(ftl);
	वापस 0;
पूर्ण


/* flush समयr, runs a second after last ग_लिखो */
अटल व्योम sm_cache_flush_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा sm_ftl *ftl = from_समयr(ftl, t, समयr);
	queue_work(cache_flush_workqueue, &ftl->flush_work);
पूर्ण

/* cache flush work, kicked by समयr */
अटल व्योम sm_cache_flush_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sm_ftl *ftl = container_of(work, काष्ठा sm_ftl, flush_work);
	mutex_lock(&ftl->mutex);
	sm_cache_flush(ftl);
	mutex_unlock(&ftl->mutex);
	वापस;
पूर्ण

/* ---------------- outside पूर्णांकerface -------------------------------------- */

/* outside पूर्णांकerface: पढ़ो a sector */
अटल पूर्णांक sm_पढ़ो(काष्ठा mtd_blktrans_dev *dev,
		   अचिन्हित दीर्घ sect_no, अक्षर *buf)
अणु
	काष्ठा sm_ftl *ftl = dev->priv;
	काष्ठा ftl_zone *zone;
	पूर्णांक error = 0, in_cache = 0;
	पूर्णांक zone_num, block, boffset;

	sm_अवरोध_offset(ftl, sect_no << 9, &zone_num, &block, &boffset);
	mutex_lock(&ftl->mutex);


	zone = sm_get_zone(ftl, zone_num);
	अगर (IS_ERR(zone)) अणु
		error = PTR_ERR(zone);
		जाओ unlock;
	पूर्ण

	/* Have to look at cache first */
	अगर (ftl->cache_zone == zone_num && ftl->cache_block == block) अणु
		in_cache = 1;
		अगर (!sm_cache_get(ftl, buf, boffset))
			जाओ unlock;
	पूर्ण

	/* Translate the block and वापस अगर करोesn't exist in the table */
	block = zone->lba_to_phys_table[block];

	अगर (block == -1) अणु
		स_रखो(buf, 0xFF, SM_SECTOR_SIZE);
		जाओ unlock;
	पूर्ण

	अगर (sm_पढ़ो_sector(ftl, zone_num, block, boffset, buf, शून्य)) अणु
		error = -EIO;
		जाओ unlock;
	पूर्ण

	अगर (in_cache)
		sm_cache_put(ftl, buf, boffset);
unlock:
	mutex_unlock(&ftl->mutex);
	वापस error;
पूर्ण

/* outside पूर्णांकerface: ग_लिखो a sector */
अटल पूर्णांक sm_ग_लिखो(काष्ठा mtd_blktrans_dev *dev,
				अचिन्हित दीर्घ sec_no, अक्षर *buf)
अणु
	काष्ठा sm_ftl *ftl = dev->priv;
	काष्ठा ftl_zone *zone;
	पूर्णांक error = 0, zone_num, block, boffset;

	BUG_ON(ftl->पढ़ोonly);
	sm_अवरोध_offset(ftl, sec_no << 9, &zone_num, &block, &boffset);

	/* No need in flush thपढ़ो running now */
	del_समयr(&ftl->समयr);
	mutex_lock(&ftl->mutex);

	zone = sm_get_zone(ftl, zone_num);
	अगर (IS_ERR(zone)) अणु
		error = PTR_ERR(zone);
		जाओ unlock;
	पूर्ण

	/* If entry is not in cache, flush it */
	अगर (ftl->cache_block != block || ftl->cache_zone != zone_num) अणु

		error = sm_cache_flush(ftl);
		अगर (error)
			जाओ unlock;

		ftl->cache_block = block;
		ftl->cache_zone = zone_num;
	पूर्ण

	sm_cache_put(ftl, buf, boffset);
unlock:
	mod_समयr(&ftl->समयr, jअगरfies + msecs_to_jअगरfies(cache_समयout));
	mutex_unlock(&ftl->mutex);
	वापस error;
पूर्ण

/* outside पूर्णांकerface: flush everything */
अटल पूर्णांक sm_flush(काष्ठा mtd_blktrans_dev *dev)
अणु
	काष्ठा sm_ftl *ftl = dev->priv;
	पूर्णांक retval;

	mutex_lock(&ftl->mutex);
	retval =  sm_cache_flush(ftl);
	mutex_unlock(&ftl->mutex);
	वापस retval;
पूर्ण

/* outside पूर्णांकerface: device is released */
अटल व्योम sm_release(काष्ठा mtd_blktrans_dev *dev)
अणु
	काष्ठा sm_ftl *ftl = dev->priv;

	mutex_lock(&ftl->mutex);
	del_समयr_sync(&ftl->समयr);
	cancel_work_sync(&ftl->flush_work);
	sm_cache_flush(ftl);
	mutex_unlock(&ftl->mutex);
पूर्ण

/* outside पूर्णांकerface: get geometry */
अटल पूर्णांक sm_getgeo(काष्ठा mtd_blktrans_dev *dev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा sm_ftl *ftl = dev->priv;
	geo->heads = ftl->heads;
	geo->sectors = ftl->sectors;
	geo->cylinders = ftl->cylinders;
	वापस 0;
पूर्ण

/* बाह्यal पूर्णांकerface: मुख्य initialization function */
अटल व्योम sm_add_mtd(काष्ठा mtd_blktrans_ops *tr, काष्ठा mtd_info *mtd)
अणु
	काष्ठा mtd_blktrans_dev *trans;
	काष्ठा sm_ftl *ftl;

	/* Allocate & initialize our निजी काष्ठाure */
	ftl = kzalloc(माप(काष्ठा sm_ftl), GFP_KERNEL);
	अगर (!ftl)
		जाओ error1;


	mutex_init(&ftl->mutex);
	समयr_setup(&ftl->समयr, sm_cache_flush_समयr, 0);
	INIT_WORK(&ftl->flush_work, sm_cache_flush_work);

	/* Read media inक्रमmation */
	अगर (sm_get_media_info(ftl, mtd)) अणु
		dbg("found unsupported mtd device, aborting");
		जाओ error2;
	पूर्ण


	/* Allocate temporary CIS buffer क्रम पढ़ो retry support */
	ftl->cis_buffer = kzalloc(SM_SECTOR_SIZE, GFP_KERNEL);
	अगर (!ftl->cis_buffer)
		जाओ error2;

	/* Allocate zone array, it will be initialized on demand */
	ftl->zones = kसुस्मृति(ftl->zone_count, माप(काष्ठा ftl_zone),
								GFP_KERNEL);
	अगर (!ftl->zones)
		जाओ error3;

	/* Allocate the cache*/
	ftl->cache_data = kzalloc(ftl->block_size, GFP_KERNEL);

	अगर (!ftl->cache_data)
		जाओ error4;

	sm_cache_init(ftl);


	/* Allocate upper layer काष्ठाure and initialize it */
	trans = kzalloc(माप(काष्ठा mtd_blktrans_dev), GFP_KERNEL);
	अगर (!trans)
		जाओ error5;

	ftl->trans = trans;
	trans->priv = ftl;

	trans->tr = tr;
	trans->mtd = mtd;
	trans->devnum = -1;
	trans->size = (ftl->block_size * ftl->max_lba * ftl->zone_count) >> 9;
	trans->पढ़ोonly = ftl->पढ़ोonly;

	अगर (sm_find_cis(ftl)) अणु
		dbg("CIS not found on mtd device, aborting");
		जाओ error6;
	पूर्ण

	ftl->disk_attributes = sm_create_sysfs_attributes(ftl);
	अगर (!ftl->disk_attributes)
		जाओ error6;
	trans->disk_attributes = ftl->disk_attributes;

	sm_prपूर्णांकk("Found %d MiB xD/SmartMedia FTL on mtd%d",
		(पूर्णांक)(mtd->size / (1024 * 1024)), mtd->index);

	dbg("FTL layout:");
	dbg("%d zone(s), each consists of %d blocks (+%d spares)",
		ftl->zone_count, ftl->max_lba,
		ftl->zone_size - ftl->max_lba);
	dbg("each block consists of %d bytes",
		ftl->block_size);


	/* Register device*/
	अगर (add_mtd_blktrans_dev(trans)) अणु
		dbg("error in mtdblktrans layer");
		जाओ error6;
	पूर्ण
	वापस;
error6:
	kमुक्त(trans);
error5:
	kमुक्त(ftl->cache_data);
error4:
	kमुक्त(ftl->zones);
error3:
	kमुक्त(ftl->cis_buffer);
error2:
	kमुक्त(ftl);
error1:
	वापस;
पूर्ण

/* मुख्य पूर्णांकerface: device अणुsurprise,पूर्ण removal */
अटल व्योम sm_हटाओ_dev(काष्ठा mtd_blktrans_dev *dev)
अणु
	काष्ठा sm_ftl *ftl = dev->priv;
	पूर्णांक i;

	del_mtd_blktrans_dev(dev);
	ftl->trans = शून्य;

	क्रम (i = 0 ; i < ftl->zone_count; i++) अणु

		अगर (!ftl->zones[i].initialized)
			जारी;

		kमुक्त(ftl->zones[i].lba_to_phys_table);
		kfअगरo_मुक्त(&ftl->zones[i].मुक्त_sectors);
	पूर्ण

	sm_delete_sysfs_attributes(ftl);
	kमुक्त(ftl->cis_buffer);
	kमुक्त(ftl->zones);
	kमुक्त(ftl->cache_data);
	kमुक्त(ftl);
पूर्ण

अटल काष्ठा mtd_blktrans_ops sm_ftl_ops = अणु
	.name		= "smblk",
	.major		= 0,
	.part_bits	= SM_FTL_PARTN_BITS,
	.blksize	= SM_SECTOR_SIZE,
	.getgeo		= sm_getgeo,

	.add_mtd	= sm_add_mtd,
	.हटाओ_dev	= sm_हटाओ_dev,

	.पढ़ोsect	= sm_पढ़ो,
	.ग_लिखोsect	= sm_ग_लिखो,

	.flush		= sm_flush,
	.release	= sm_release,

	.owner		= THIS_MODULE,
पूर्ण;

अटल __init पूर्णांक sm_module_init(व्योम)
अणु
	पूर्णांक error = 0;

	cache_flush_workqueue = create_मुक्तzable_workqueue("smflush");
	अगर (!cache_flush_workqueue)
		वापस -ENOMEM;

	error = रेजिस्टर_mtd_blktrans(&sm_ftl_ops);
	अगर (error)
		destroy_workqueue(cache_flush_workqueue);
	वापस error;

पूर्ण

अटल व्योम __निकास sm_module_निकास(व्योम)
अणु
	destroy_workqueue(cache_flush_workqueue);
	deरेजिस्टर_mtd_blktrans(&sm_ftl_ops);
पूर्ण

module_init(sm_module_init);
module_निकास(sm_module_निकास);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Maxim Levitsky <maximlevitsky@gmail.com>");
MODULE_DESCRIPTION("Smartmedia/xD mtd translation layer");
