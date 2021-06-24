<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright तऊ 2012 NetCommWireless
 * Iwo Mergler <Iwo.Mergler@netcommwireless.com.au>
 *
 * Test क्रम multi-bit error recovery on a न_अंकD page This mostly tests the
 * ECC controller / driver.
 *
 * There are two test modes:
 *
 *	0 - artअगरicially inserting bit errors until the ECC fails
 *	    This is the शेष method and fairly quick. It should
 *	    be independent of the quality of the FLASH.
 *
 *	1 - re-writing the same pattern repeatedly until the ECC fails.
 *	    This method relies on the physics of न_अंकD FLASH to eventually
 *	    generate '0' bits if '1' has been written sufficient बार.
 *	    Depending on the न_अंकD, the first bit errors will appear after
 *	    1000 or more ग_लिखोs and then will usually snowball, reaching the
 *	    limits of the ECC quickly.
 *
 *	    The test stops after 10000 cycles, should your FLASH be
 *	    exceptionally good and not generate bit errors beक्रमe that. Try
 *	    a dअगरferent page in that हाल.
 *
 * Please note that neither of these tests will signअगरicantly 'use up' any
 * FLASH endurance. Only a maximum of two erase operations will be perक्रमmed.
 */

#घोषणा pr_fmt(fmt)	KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/err.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/slab.h>
#समावेश "mtd_test.h"

अटल पूर्णांक dev;
module_param(dev, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(dev, "MTD device number to use");

अटल अचिन्हित page_offset;
module_param(page_offset, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(page_offset, "Page number relative to dev start");

अटल अचिन्हित seed;
module_param(seed, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(seed, "Random seed");

अटल पूर्णांक mode;
module_param(mode, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(mode, "0=incremental errors, 1=overwrite test");

अटल अचिन्हित max_overग_लिखो = 10000;

अटल loff_t   offset;     /* Offset of the page we're using. */
अटल अचिन्हित eraseblock; /* Eraseblock number क्रम our page. */

/* We assume that the ECC can correct up to a certain number
 * of biterrors per subpage. */
अटल अचिन्हित subsize;  /* Size of subpages */
अटल अचिन्हित subcount; /* Number of subpages per page */

अटल काष्ठा mtd_info *mtd;   /* MTD device */

अटल uपूर्णांक8_t *wbuffer; /* One page ग_लिखो / compare buffer */
अटल uपूर्णांक8_t *rbuffer; /* One page पढ़ो buffer */

/* 'random' bytes from known offsets */
अटल uपूर्णांक8_t hash(अचिन्हित offset)
अणु
	अचिन्हित v = offset;
	अचिन्हित अक्षर c;
	v ^= 0x7f7edfd3;
	v = v ^ (v >> 3);
	v = v ^ (v >> 5);
	v = v ^ (v >> 13);
	c = v & 0xFF;
	/* Reverse bits of result. */
	c = (c & 0x0F) << 4 | (c & 0xF0) >> 4;
	c = (c & 0x33) << 2 | (c & 0xCC) >> 2;
	c = (c & 0x55) << 1 | (c & 0xAA) >> 1;
	वापस c;
पूर्ण

/* Writes wbuffer to page */
अटल पूर्णांक ग_लिखो_page(पूर्णांक log)
अणु
	अगर (log)
		pr_info("write_page\n");

	वापस mtdtest_ग_लिखो(mtd, offset, mtd->ग_लिखोsize, wbuffer);
पूर्ण

/* Re-ग_लिखोs the data area जबतक leaving the OOB alone. */
अटल पूर्णांक reग_लिखो_page(पूर्णांक log)
अणु
	पूर्णांक err = 0;
	काष्ठा mtd_oob_ops ops;

	अगर (log)
		pr_info("rewrite page\n");

	ops.mode      = MTD_OPS_RAW; /* No ECC */
	ops.len       = mtd->ग_लिखोsize;
	ops.retlen    = 0;
	ops.ooblen    = 0;
	ops.oobretlen = 0;
	ops.ooboffs   = 0;
	ops.datbuf    = wbuffer;
	ops.oobbuf    = शून्य;

	err = mtd_ग_लिखो_oob(mtd, offset, &ops);
	अगर (err || ops.retlen != mtd->ग_लिखोsize) अणु
		pr_err("error: write_oob failed (%d)\n", err);
		अगर (!err)
			err = -EIO;
	पूर्ण

	वापस err;
पूर्ण

/* Reads page पूर्णांकo rbuffer. Returns number of corrected bit errors (>=0)
 * or error (<0) */
अटल पूर्णांक पढ़ो_page(पूर्णांक log)
अणु
	पूर्णांक err = 0;
	माप_प्रकार पढ़ो;
	काष्ठा mtd_ecc_stats oldstats;

	अगर (log)
		pr_info("read_page\n");

	/* Saving last mtd stats */
	स_नकल(&oldstats, &mtd->ecc_stats, माप(oldstats));

	err = mtd_पढ़ो(mtd, offset, mtd->ग_लिखोsize, &पढ़ो, rbuffer);
	अगर (!err || err == -EUCLEAN)
		err = mtd->ecc_stats.corrected - oldstats.corrected;

	अगर (err < 0 || पढ़ो != mtd->ग_लिखोsize) अणु
		pr_err("error: read failed at %#llx\n", (दीर्घ दीर्घ)offset);
		अगर (err >= 0)
			err = -EIO;
	पूर्ण

	वापस err;
पूर्ण

/* Verअगरies rbuffer against अक्रमom sequence */
अटल पूर्णांक verअगरy_page(पूर्णांक log)
अणु
	अचिन्हित i, errs = 0;

	अगर (log)
		pr_info("verify_page\n");

	क्रम (i = 0; i < mtd->ग_लिखोsize; i++) अणु
		अगर (rbuffer[i] != hash(i+seed)) अणु
			pr_err("Error: page offset %u, expected %02x, got %02x\n",
				i, hash(i+seed), rbuffer[i]);
			errs++;
		पूर्ण
	पूर्ण

	अगर (errs)
		वापस -EIO;
	अन्यथा
		वापस 0;
पूर्ण

#घोषणा CBIT(v, n) ((v) & (1 << (n)))
#घोषणा BCLR(v, n) ((v) = (v) & ~(1 << (n)))

/* Finds the first '1' bit in wbuffer starting at offset 'byte'
 * and sets it to '0'. */
अटल पूर्णांक insert_biterror(अचिन्हित byte)
अणु
	पूर्णांक bit;

	जबतक (byte < mtd->ग_लिखोsize) अणु
		क्रम (bit = 7; bit >= 0; bit--) अणु
			अगर (CBIT(wbuffer[byte], bit)) अणु
				BCLR(wbuffer[byte], bit);
				pr_info("Inserted biterror @ %u/%u\n", byte, bit);
				वापस 0;
			पूर्ण
		पूर्ण
		byte++;
	पूर्ण
	pr_err("biterror: Failed to find a '1' bit\n");
	वापस -EIO;
पूर्ण

/* Writes 'random' data to page and then पूर्णांकroduces deliberate bit
 * errors पूर्णांकo the page, जबतक verअगरying each step. */
अटल पूर्णांक incremental_errors_test(व्योम)
अणु
	पूर्णांक err = 0;
	अचिन्हित i;
	अचिन्हित errs_per_subpage = 0;

	pr_info("incremental biterrors test\n");

	क्रम (i = 0; i < mtd->ग_लिखोsize; i++)
		wbuffer[i] = hash(i+seed);

	err = ग_लिखो_page(1);
	अगर (err)
		जाओ निकास;

	जबतक (1) अणु

		err = reग_लिखो_page(1);
		अगर (err)
			जाओ निकास;

		err = पढ़ो_page(1);
		अगर (err > 0)
			pr_info("Read reported %d corrected bit errors\n", err);
		अगर (err < 0) अणु
			pr_err("After %d biterrors per subpage, read reported error %d\n",
				errs_per_subpage, err);
			err = 0;
			जाओ निकास;
		पूर्ण

		err = verअगरy_page(1);
		अगर (err) अणु
			pr_err("ECC failure, read data is incorrect despite read success\n");
			जाओ निकास;
		पूर्ण

		pr_info("Successfully corrected %d bit errors per subpage\n",
			errs_per_subpage);

		क्रम (i = 0; i < subcount; i++) अणु
			err = insert_biterror(i * subsize);
			अगर (err < 0)
				जाओ निकास;
		पूर्ण
		errs_per_subpage++;
	पूर्ण

निकास:
	वापस err;
पूर्ण


/* Writes 'random' data to page and then re-ग_लिखोs that same data repeatedly.
   This eventually develops bit errors (bits written as '1' will slowly become
   '0'), which are corrected as far as the ECC is capable of. */
अटल पूर्णांक overग_लिखो_test(व्योम)
अणु
	पूर्णांक err = 0;
	अचिन्हित i;
	अचिन्हित max_corrected = 0;
	अचिन्हित opno = 0;
	/* We करोn't expect more than this many correctable bit errors per
	 * page. */
	#घोषणा MAXBITS 512
	अटल अचिन्हित bitstats[MAXBITS]; /* bit error histogram. */

	स_रखो(bitstats, 0, माप(bitstats));

	pr_info("overwrite biterrors test\n");

	क्रम (i = 0; i < mtd->ग_लिखोsize; i++)
		wbuffer[i] = hash(i+seed);

	err = ग_लिखो_page(1);
	अगर (err)
		जाओ निकास;

	जबतक (opno < max_overग_लिखो) अणु

		err = ग_लिखो_page(0);
		अगर (err)
			अवरोध;

		err = पढ़ो_page(0);
		अगर (err >= 0) अणु
			अगर (err >= MAXBITS) अणु
				pr_info("Implausible number of bit errors corrected\n");
				err = -EIO;
				अवरोध;
			पूर्ण
			bitstats[err]++;
			अगर (err > max_corrected) अणु
				max_corrected = err;
				pr_info("Read reported %d corrected bit errors\n",
					err);
			पूर्ण
		पूर्ण अन्यथा अणु /* err < 0 */
			pr_info("Read reported error %d\n", err);
			err = 0;
			अवरोध;
		पूर्ण

		err = verअगरy_page(0);
		अगर (err) अणु
			bitstats[max_corrected] = opno;
			pr_info("ECC failure, read data is incorrect despite read success\n");
			अवरोध;
		पूर्ण

		err = mtdtest_relax();
		अगर (err)
			अवरोध;

		opno++;
	पूर्ण

	/* At this poपूर्णांक bitstats[0] contains the number of ops with no bit
	 * errors, bitstats[1] the number of ops with 1 bit error, etc. */
	pr_info("Bit error histogram (%d operations total):\n", opno);
	क्रम (i = 0; i < max_corrected; i++)
		pr_info("Page reads with %3d corrected bit errors: %d\n",
			i, bitstats[i]);

निकास:
	वापस err;
पूर्ण

अटल पूर्णांक __init mtd_nandbiterrs_init(व्योम)
अणु
	पूर्णांक err = 0;

	prपूर्णांकk("\n");
	prपूर्णांकk(KERN_INFO "==================================================\n");
	pr_info("MTD device: %d\n", dev);

	mtd = get_mtd_device(शून्य, dev);
	अगर (IS_ERR(mtd)) अणु
		err = PTR_ERR(mtd);
		pr_err("error: cannot get MTD device\n");
		जाओ निकास_mtddev;
	पूर्ण

	अगर (!mtd_type_is_nand(mtd)) अणु
		pr_info("this test requires NAND flash\n");
		err = -ENODEV;
		जाओ निकास_nand;
	पूर्ण

	pr_info("MTD device size %llu, eraseblock=%u, page=%u, oob=%u\n",
		(अचिन्हित दीर्घ दीर्घ)mtd->size, mtd->erasesize,
		mtd->ग_लिखोsize, mtd->oobsize);

	subsize  = mtd->ग_लिखोsize >> mtd->subpage_sft;
	subcount = mtd->ग_लिखोsize / subsize;

	pr_info("Device uses %d subpages of %d bytes\n", subcount, subsize);

	offset     = (loff_t)page_offset * mtd->ग_लिखोsize;
	eraseblock = mtd_भाग_by_eb(offset, mtd);

	pr_info("Using page=%u, offset=%llu, eraseblock=%u\n",
		page_offset, offset, eraseblock);

	wbuffer = kदो_स्मृति(mtd->ग_लिखोsize, GFP_KERNEL);
	अगर (!wbuffer) अणु
		err = -ENOMEM;
		जाओ निकास_wbuffer;
	पूर्ण

	rbuffer = kदो_स्मृति(mtd->ग_लिखोsize, GFP_KERNEL);
	अगर (!rbuffer) अणु
		err = -ENOMEM;
		जाओ निकास_rbuffer;
	पूर्ण

	err = mtdtest_erase_eraseblock(mtd, eraseblock);
	अगर (err)
		जाओ निकास_error;

	अगर (mode == 0)
		err = incremental_errors_test();
	अन्यथा
		err = overग_लिखो_test();

	अगर (err)
		जाओ निकास_error;

	/* We leave the block un-erased in हाल of test failure. */
	err = mtdtest_erase_eraseblock(mtd, eraseblock);
	अगर (err)
		जाओ निकास_error;

	err = -EIO;
	pr_info("finished successfully.\n");
	prपूर्णांकk(KERN_INFO "==================================================\n");

निकास_error:
	kमुक्त(rbuffer);
निकास_rbuffer:
	kमुक्त(wbuffer);
निकास_wbuffer:
	/* Nothing */
निकास_nand:
	put_mtd_device(mtd);
निकास_mtddev:
	वापस err;
पूर्ण

अटल व्योम __निकास mtd_nandbiterrs_निकास(व्योम)
अणु
	वापस;
पूर्ण

module_init(mtd_nandbiterrs_init);
module_निकास(mtd_nandbiterrs_निकास);

MODULE_DESCRIPTION("NAND bit error recovery test");
MODULE_AUTHOR("Iwo Mergler");
MODULE_LICENSE("GPL");
