<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2008 Nokia Corporation
 *
 * Test OOB पढ़ो and ग_लिखो on MTD device.
 *
 * Author: Adrian Hunter <ext-adrian.hunter@nokia.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <यंत्र/भाग64.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/err.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/अक्रमom.h>

#समावेश "mtd_test.h"

अटल पूर्णांक dev = -EINVAL;
अटल पूर्णांक bitflip_limit;
module_param(dev, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(dev, "MTD device number to use");
module_param(bitflip_limit, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(bitflip_limit, "Max. allowed bitflips per page");

अटल काष्ठा mtd_info *mtd;
अटल अचिन्हित अक्षर *पढ़ोbuf;
अटल अचिन्हित अक्षर *ग_लिखोbuf;
अटल अचिन्हित अक्षर *bbt;

अटल पूर्णांक ebcnt;
अटल पूर्णांक pgcnt;
अटल पूर्णांक errcnt;
अटल पूर्णांक use_offset;
अटल पूर्णांक use_len;
अटल पूर्णांक use_len_max;
अटल पूर्णांक vary_offset;
अटल काष्ठा rnd_state rnd_state;

अटल व्योम करो_vary_offset(व्योम)
अणु
	use_len -= 1;
	अगर (use_len < 1) अणु
		use_offset += 1;
		अगर (use_offset >= use_len_max)
			use_offset = 0;
		use_len = use_len_max - use_offset;
	पूर्ण
पूर्ण

अटल पूर्णांक ग_लिखो_eraseblock(पूर्णांक ebnum)
अणु
	पूर्णांक i;
	काष्ठा mtd_oob_ops ops;
	पूर्णांक err = 0;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, use_len_max * pgcnt);
	क्रम (i = 0; i < pgcnt; ++i, addr += mtd->ग_लिखोsize) अणु
		ops.mode      = MTD_OPS_AUTO_OOB;
		ops.len       = 0;
		ops.retlen    = 0;
		ops.ooblen    = use_len;
		ops.oobretlen = 0;
		ops.ooboffs   = use_offset;
		ops.datbuf    = शून्य;
		ops.oobbuf    = ग_लिखोbuf + (use_len_max * i) + use_offset;
		err = mtd_ग_लिखो_oob(mtd, addr, &ops);
		अगर (err || ops.oobretlen != use_len) अणु
			pr_err("error: writeoob failed at %#llx\n",
			       (दीर्घ दीर्घ)addr);
			pr_err("error: use_len %d, use_offset %d\n",
			       use_len, use_offset);
			errcnt += 1;
			वापस err ? err : -1;
		पूर्ण
		अगर (vary_offset)
			करो_vary_offset();
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ग_लिखो_whole_device(व्योम)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i;

	pr_info("writing OOBs of whole device\n");
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = ग_लिखो_eraseblock(i);
		अगर (err)
			वापस err;
		अगर (i % 256 == 0)
			pr_info("written up to eraseblock %u\n", i);

		err = mtdtest_relax();
		अगर (err)
			वापस err;
	पूर्ण
	pr_info("written %u eraseblocks\n", i);
	वापस 0;
पूर्ण

/*
 * Display the address, offset and data bytes at comparison failure.
 * Return number of bitflips encountered.
 */
अटल माप_प्रकार स_भेदshowoffset(loff_t addr, loff_t offset, स्थिर व्योम *cs,
			       स्थिर व्योम *ct, माप_प्रकार count)
अणु
	स्थिर अचिन्हित अक्षर *su1, *su2;
	पूर्णांक res;
	माप_प्रकार i = 0;
	माप_प्रकार bitflips = 0;

	क्रम (su1 = cs, su2 = ct; 0 < count; ++su1, ++su2, count--, i++) अणु
		res = *su1 ^ *su2;
		अगर (res) अणु
			pr_info("error @addr[0x%lx:0x%lx] 0x%x -> 0x%x diff 0x%x\n",
				(अचिन्हित दीर्घ)addr, (अचिन्हित दीर्घ)offset + i,
				*su1, *su2, res);
			bitflips += hweight8(res);
		पूर्ण
	पूर्ण

	वापस bitflips;
पूर्ण

#घोषणा स_भेदshow(addr, cs, ct, count) स_भेदshowoffset((addr), 0, (cs), (ct),\
							 (count))

/*
 * Compare with 0xff and show the address, offset and data bytes at
 * comparison failure. Return number of bitflips encountered.
 */
अटल माप_प्रकार memffshow(loff_t addr, loff_t offset, स्थिर व्योम *cs,
			माप_प्रकार count)
अणु
	स्थिर अचिन्हित अक्षर *su1;
	पूर्णांक res;
	माप_प्रकार i = 0;
	माप_प्रकार bitflips = 0;

	क्रम (su1 = cs; 0 < count; ++su1, count--, i++) अणु
		res = *su1 ^ 0xff;
		अगर (res) अणु
			pr_info("error @addr[0x%lx:0x%lx] 0x%x -> 0xff diff 0x%x\n",
				(अचिन्हित दीर्घ)addr, (अचिन्हित दीर्घ)offset + i,
				*su1, res);
			bitflips += hweight8(res);
		पूर्ण
	पूर्ण

	वापस bitflips;
पूर्ण

अटल पूर्णांक verअगरy_eraseblock(पूर्णांक ebnum)
अणु
	पूर्णांक i;
	काष्ठा mtd_oob_ops ops;
	पूर्णांक err = 0;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;
	माप_प्रकार bitflips;

	pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, use_len_max * pgcnt);
	क्रम (i = 0; i < pgcnt; ++i, addr += mtd->ग_लिखोsize) अणु
		ops.mode      = MTD_OPS_AUTO_OOB;
		ops.len       = 0;
		ops.retlen    = 0;
		ops.ooblen    = use_len;
		ops.oobretlen = 0;
		ops.ooboffs   = use_offset;
		ops.datbuf    = शून्य;
		ops.oobbuf    = पढ़ोbuf;
		err = mtd_पढ़ो_oob(mtd, addr, &ops);
		अगर (mtd_is_bitflip(err))
			err = 0;

		अगर (err || ops.oobretlen != use_len) अणु
			pr_err("error: readoob failed at %#llx\n",
			       (दीर्घ दीर्घ)addr);
			errcnt += 1;
			वापस err ? err : -1;
		पूर्ण

		bitflips = स_भेदshow(addr, पढ़ोbuf,
				      ग_लिखोbuf + (use_len_max * i) + use_offset,
				      use_len);
		अगर (bitflips > bitflip_limit) अणु
			pr_err("error: verify failed at %#llx\n",
			       (दीर्घ दीर्घ)addr);
			errcnt += 1;
			अगर (errcnt > 1000) अणु
				pr_err("error: too many errors\n");
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अगर (bitflips) अणु
			pr_info("ignoring error as within bitflip_limit\n");
		पूर्ण

		अगर (use_offset != 0 || use_len < mtd->oobavail) अणु
			पूर्णांक k;

			ops.mode      = MTD_OPS_AUTO_OOB;
			ops.len       = 0;
			ops.retlen    = 0;
			ops.ooblen    = mtd->oobavail;
			ops.oobretlen = 0;
			ops.ooboffs   = 0;
			ops.datbuf    = शून्य;
			ops.oobbuf    = पढ़ोbuf;
			err = mtd_पढ़ो_oob(mtd, addr, &ops);
			अगर (mtd_is_bitflip(err))
				err = 0;

			अगर (err || ops.oobretlen != mtd->oobavail) अणु
				pr_err("error: readoob failed at %#llx\n",
						(दीर्घ दीर्घ)addr);
				errcnt += 1;
				वापस err ? err : -1;
			पूर्ण
			bitflips = स_भेदshowoffset(addr, use_offset,
						    पढ़ोbuf + use_offset,
						    ग_लिखोbuf + (use_len_max * i) + use_offset,
						    use_len);

			/* verअगरy pre-offset area क्रम 0xff */
			bitflips += memffshow(addr, 0, पढ़ोbuf, use_offset);

			/* verअगरy post-(use_offset + use_len) area क्रम 0xff */
			k = use_offset + use_len;
			bitflips += memffshow(addr, k, पढ़ोbuf + k,
					      mtd->oobavail - k);

			अगर (bitflips > bitflip_limit) अणु
				pr_err("error: verify failed at %#llx\n",
						(दीर्घ दीर्घ)addr);
				errcnt += 1;
				अगर (errcnt > 1000) अणु
					pr_err("error: too many errors\n");
					वापस -1;
				पूर्ण
			पूर्ण अन्यथा अगर (bitflips) अणु
				pr_info("ignoring errors as within bitflip limit\n");
			पूर्ण
		पूर्ण
		अगर (vary_offset)
			करो_vary_offset();
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक verअगरy_eraseblock_in_one_go(पूर्णांक ebnum)
अणु
	काष्ठा mtd_oob_ops ops;
	पूर्णांक err = 0;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;
	माप_प्रकार len = mtd->oobavail * pgcnt;
	माप_प्रकार oobavail = mtd->oobavail;
	माप_प्रकार bitflips;
	पूर्णांक i;

	pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, len);
	ops.mode      = MTD_OPS_AUTO_OOB;
	ops.len       = 0;
	ops.retlen    = 0;
	ops.ooblen    = len;
	ops.oobretlen = 0;
	ops.ooboffs   = 0;
	ops.datbuf    = शून्य;
	ops.oobbuf    = पढ़ोbuf;

	/* पढ़ो entire block's OOB at one go */
	err = mtd_पढ़ो_oob(mtd, addr, &ops);
	अगर (mtd_is_bitflip(err))
		err = 0;

	अगर (err || ops.oobretlen != len) अणु
		pr_err("error: readoob failed at %#llx\n",
		       (दीर्घ दीर्घ)addr);
		errcnt += 1;
		वापस err ? err : -1;
	पूर्ण

	/* verअगरy one page OOB at a समय क्रम bitflip per page limit check */
	क्रम (i = 0; i < pgcnt; ++i, addr += mtd->ग_लिखोsize) अणु
		bitflips = स_भेदshow(addr, पढ़ोbuf + (i * oobavail),
				      ग_लिखोbuf + (i * oobavail), oobavail);
		अगर (bitflips > bitflip_limit) अणु
			pr_err("error: verify failed at %#llx\n",
			       (दीर्घ दीर्घ)addr);
			errcnt += 1;
			अगर (errcnt > 1000) अणु
				pr_err("error: too many errors\n");
				वापस -1;
			पूर्ण
		पूर्ण अन्यथा अगर (bitflips) अणु
			pr_info("ignoring error as within bitflip_limit\n");
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक verअगरy_all_eraseblocks(व्योम)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i;

	pr_info("verifying all eraseblocks\n");
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = verअगरy_eraseblock(i);
		अगर (err)
			वापस err;
		अगर (i % 256 == 0)
			pr_info("verified up to eraseblock %u\n", i);

		err = mtdtest_relax();
		अगर (err)
			वापस err;
	पूर्ण
	pr_info("verified %u eraseblocks\n", i);
	वापस 0;
पूर्ण

अटल पूर्णांक __init mtd_oobtest_init(व्योम)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक i;
	uपूर्णांक64_t पंचांगp;
	काष्ठा mtd_oob_ops ops;
	loff_t addr = 0, addr0;

	prपूर्णांकk(KERN_INFO "\n");
	prपूर्णांकk(KERN_INFO "=================================================\n");

	अगर (dev < 0) अणु
		pr_info("Please specify a valid mtd-device via module parameter\n");
		pr_crit("CAREFUL: This test wipes all data on the specified MTD device!\n");
		वापस -EINVAL;
	पूर्ण

	pr_info("MTD device: %d\n", dev);

	mtd = get_mtd_device(शून्य, dev);
	अगर (IS_ERR(mtd)) अणु
		err = PTR_ERR(mtd);
		pr_err("error: cannot get MTD device\n");
		वापस err;
	पूर्ण

	अगर (!mtd_type_is_nand(mtd)) अणु
		pr_info("this test requires NAND flash\n");
		जाओ out;
	पूर्ण

	पंचांगp = mtd->size;
	करो_भाग(पंचांगp, mtd->erasesize);
	ebcnt = पंचांगp;
	pgcnt = mtd->erasesize / mtd->ग_लिखोsize;

	pr_info("MTD device size %llu, eraseblock size %u, "
	       "page size %u, count of eraseblocks %u, pages per "
	       "eraseblock %u, OOB size %u\n",
	       (अचिन्हित दीर्घ दीर्घ)mtd->size, mtd->erasesize,
	       mtd->ग_लिखोsize, ebcnt, pgcnt, mtd->oobsize);

	err = -ENOMEM;
	पढ़ोbuf = kदो_स्मृति(mtd->erasesize, GFP_KERNEL);
	अगर (!पढ़ोbuf)
		जाओ out;
	ग_लिखोbuf = kदो_स्मृति(mtd->erasesize, GFP_KERNEL);
	अगर (!ग_लिखोbuf)
		जाओ out;
	bbt = kzalloc(ebcnt, GFP_KERNEL);
	अगर (!bbt)
		जाओ out;

	err = mtdtest_scan_क्रम_bad_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	use_offset = 0;
	use_len = mtd->oobavail;
	use_len_max = mtd->oobavail;
	vary_offset = 0;

	/* First test: ग_लिखो all OOB, पढ़ो it back and verअगरy */
	pr_info("test 1 of 5\n");

	err = mtdtest_erase_good_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	pअक्रमom_seed_state(&rnd_state, 1);
	err = ग_लिखो_whole_device();
	अगर (err)
		जाओ out;

	pअक्रमom_seed_state(&rnd_state, 1);
	err = verअगरy_all_eraseblocks();
	अगर (err)
		जाओ out;

	/*
	 * Second test: ग_लिखो all OOB, a block at a समय, पढ़ो it back and
	 * verअगरy.
	 */
	pr_info("test 2 of 5\n");

	err = mtdtest_erase_good_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	pअक्रमom_seed_state(&rnd_state, 3);
	err = ग_लिखो_whole_device();
	अगर (err)
		जाओ out;

	/* Check all eraseblocks */
	pअक्रमom_seed_state(&rnd_state, 3);
	pr_info("verifying all eraseblocks\n");
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = verअगरy_eraseblock_in_one_go(i);
		अगर (err)
			जाओ out;
		अगर (i % 256 == 0)
			pr_info("verified up to eraseblock %u\n", i);

		err = mtdtest_relax();
		अगर (err)
			जाओ out;
	पूर्ण
	pr_info("verified %u eraseblocks\n", i);

	/*
	 * Third test: ग_लिखो OOB at varying offsets and lengths, पढ़ो it back
	 * and verअगरy.
	 */
	pr_info("test 3 of 5\n");

	err = mtdtest_erase_good_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	/* Write all eraseblocks */
	use_offset = 0;
	use_len = mtd->oobavail;
	use_len_max = mtd->oobavail;
	vary_offset = 1;
	pअक्रमom_seed_state(&rnd_state, 5);

	err = ग_लिखो_whole_device();
	अगर (err)
		जाओ out;

	/* Check all eraseblocks */
	use_offset = 0;
	use_len = mtd->oobavail;
	use_len_max = mtd->oobavail;
	vary_offset = 1;
	pअक्रमom_seed_state(&rnd_state, 5);
	err = verअगरy_all_eraseblocks();
	अगर (err)
		जाओ out;

	use_offset = 0;
	use_len = mtd->oobavail;
	use_len_max = mtd->oobavail;
	vary_offset = 0;

	/* Fourth test: try to ग_लिखो off end of device */
	pr_info("test 4 of 5\n");

	err = mtdtest_erase_good_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	addr0 = 0;
	क्रम (i = 0; i < ebcnt && bbt[i]; ++i)
		addr0 += mtd->erasesize;

	/* Attempt to ग_लिखो off end of OOB */
	ops.mode      = MTD_OPS_AUTO_OOB;
	ops.len       = 0;
	ops.retlen    = 0;
	ops.ooblen    = 1;
	ops.oobretlen = 0;
	ops.ooboffs   = mtd->oobavail;
	ops.datbuf    = शून्य;
	ops.oobbuf    = ग_लिखोbuf;
	pr_info("attempting to start write past end of OOB\n");
	pr_info("an error is expected...\n");
	err = mtd_ग_लिखो_oob(mtd, addr0, &ops);
	अगर (err) अणु
		pr_info("error occurred as expected\n");
		err = 0;
	पूर्ण अन्यथा अणु
		pr_err("error: can write past end of OOB\n");
		errcnt += 1;
	पूर्ण

	/* Attempt to पढ़ो off end of OOB */
	ops.mode      = MTD_OPS_AUTO_OOB;
	ops.len       = 0;
	ops.retlen    = 0;
	ops.ooblen    = 1;
	ops.oobretlen = 0;
	ops.ooboffs   = mtd->oobavail;
	ops.datbuf    = शून्य;
	ops.oobbuf    = पढ़ोbuf;
	pr_info("attempting to start read past end of OOB\n");
	pr_info("an error is expected...\n");
	err = mtd_पढ़ो_oob(mtd, addr0, &ops);
	अगर (mtd_is_bitflip(err))
		err = 0;

	अगर (err) अणु
		pr_info("error occurred as expected\n");
		err = 0;
	पूर्ण अन्यथा अणु
		pr_err("error: can read past end of OOB\n");
		errcnt += 1;
	पूर्ण

	अगर (bbt[ebcnt - 1])
		pr_info("skipping end of device tests because last "
		       "block is bad\n");
	अन्यथा अणु
		/* Attempt to ग_लिखो off end of device */
		ops.mode      = MTD_OPS_AUTO_OOB;
		ops.len       = 0;
		ops.retlen    = 0;
		ops.ooblen    = mtd->oobavail + 1;
		ops.oobretlen = 0;
		ops.ooboffs   = 0;
		ops.datbuf    = शून्य;
		ops.oobbuf    = ग_लिखोbuf;
		pr_info("attempting to write past end of device\n");
		pr_info("an error is expected...\n");
		err = mtd_ग_लिखो_oob(mtd, mtd->size - mtd->ग_लिखोsize, &ops);
		अगर (err) अणु
			pr_info("error occurred as expected\n");
			err = 0;
		पूर्ण अन्यथा अणु
			pr_err("error: wrote past end of device\n");
			errcnt += 1;
		पूर्ण

		/* Attempt to पढ़ो off end of device */
		ops.mode      = MTD_OPS_AUTO_OOB;
		ops.len       = 0;
		ops.retlen    = 0;
		ops.ooblen    = mtd->oobavail + 1;
		ops.oobretlen = 0;
		ops.ooboffs   = 0;
		ops.datbuf    = शून्य;
		ops.oobbuf    = पढ़ोbuf;
		pr_info("attempting to read past end of device\n");
		pr_info("an error is expected...\n");
		err = mtd_पढ़ो_oob(mtd, mtd->size - mtd->ग_लिखोsize, &ops);
		अगर (mtd_is_bitflip(err))
			err = 0;

		अगर (err) अणु
			pr_info("error occurred as expected\n");
			err = 0;
		पूर्ण अन्यथा अणु
			pr_err("error: read past end of device\n");
			errcnt += 1;
		पूर्ण

		err = mtdtest_erase_eraseblock(mtd, ebcnt - 1);
		अगर (err)
			जाओ out;

		/* Attempt to ग_लिखो off end of device */
		ops.mode      = MTD_OPS_AUTO_OOB;
		ops.len       = 0;
		ops.retlen    = 0;
		ops.ooblen    = mtd->oobavail;
		ops.oobretlen = 0;
		ops.ooboffs   = 1;
		ops.datbuf    = शून्य;
		ops.oobbuf    = ग_लिखोbuf;
		pr_info("attempting to write past end of device\n");
		pr_info("an error is expected...\n");
		err = mtd_ग_लिखो_oob(mtd, mtd->size - mtd->ग_लिखोsize, &ops);
		अगर (err) अणु
			pr_info("error occurred as expected\n");
			err = 0;
		पूर्ण अन्यथा अणु
			pr_err("error: wrote past end of device\n");
			errcnt += 1;
		पूर्ण

		/* Attempt to पढ़ो off end of device */
		ops.mode      = MTD_OPS_AUTO_OOB;
		ops.len       = 0;
		ops.retlen    = 0;
		ops.ooblen    = mtd->oobavail;
		ops.oobretlen = 0;
		ops.ooboffs   = 1;
		ops.datbuf    = शून्य;
		ops.oobbuf    = पढ़ोbuf;
		pr_info("attempting to read past end of device\n");
		pr_info("an error is expected...\n");
		err = mtd_पढ़ो_oob(mtd, mtd->size - mtd->ग_लिखोsize, &ops);
		अगर (mtd_is_bitflip(err))
			err = 0;

		अगर (err) अणु
			pr_info("error occurred as expected\n");
			err = 0;
		पूर्ण अन्यथा अणु
			pr_err("error: read past end of device\n");
			errcnt += 1;
		पूर्ण
	पूर्ण

	/* Fअगरth test: ग_लिखो / पढ़ो across block boundaries */
	pr_info("test 5 of 5\n");

	/* Erase all eraseblocks */
	err = mtdtest_erase_good_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	/* Write all eraseblocks */
	pअक्रमom_seed_state(&rnd_state, 11);
	pr_info("writing OOBs of whole device\n");
	क्रम (i = 0; i < ebcnt - 1; ++i) अणु
		पूर्णांक cnt = 2;
		पूर्णांक pg;
		माप_प्रकार sz = mtd->oobavail;
		अगर (bbt[i] || bbt[i + 1])
			जारी;
		addr = (loff_t)(i + 1) * mtd->erasesize - mtd->ग_लिखोsize;
		pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, sz * cnt);
		क्रम (pg = 0; pg < cnt; ++pg) अणु
			ops.mode      = MTD_OPS_AUTO_OOB;
			ops.len       = 0;
			ops.retlen    = 0;
			ops.ooblen    = sz;
			ops.oobretlen = 0;
			ops.ooboffs   = 0;
			ops.datbuf    = शून्य;
			ops.oobbuf    = ग_लिखोbuf + pg * sz;
			err = mtd_ग_लिखो_oob(mtd, addr, &ops);
			अगर (err)
				जाओ out;
			अगर (i % 256 == 0)
				pr_info("written up to eraseblock %u\n", i);

			err = mtdtest_relax();
			अगर (err)
				जाओ out;

			addr += mtd->ग_लिखोsize;
		पूर्ण
	पूर्ण
	pr_info("written %u eraseblocks\n", i);

	/* Check all eraseblocks */
	pअक्रमom_seed_state(&rnd_state, 11);
	pr_info("verifying all eraseblocks\n");
	क्रम (i = 0; i < ebcnt - 1; ++i) अणु
		अगर (bbt[i] || bbt[i + 1])
			जारी;
		pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, mtd->oobavail * 2);
		addr = (loff_t)(i + 1) * mtd->erasesize - mtd->ग_लिखोsize;
		ops.mode      = MTD_OPS_AUTO_OOB;
		ops.len       = 0;
		ops.retlen    = 0;
		ops.ooblen    = mtd->oobavail * 2;
		ops.oobretlen = 0;
		ops.ooboffs   = 0;
		ops.datbuf    = शून्य;
		ops.oobbuf    = पढ़ोbuf;
		err = mtd_पढ़ो_oob(mtd, addr, &ops);
		अगर (mtd_is_bitflip(err))
			err = 0;

		अगर (err)
			जाओ out;
		अगर (स_भेदshow(addr, पढ़ोbuf, ग_लिखोbuf,
			       mtd->oobavail * 2)) अणु
			pr_err("error: verify failed at %#llx\n",
			       (दीर्घ दीर्घ)addr);
			errcnt += 1;
			अगर (errcnt > 1000) अणु
				pr_err("error: too many errors\n");
				जाओ out;
			पूर्ण
		पूर्ण
		अगर (i % 256 == 0)
			pr_info("verified up to eraseblock %u\n", i);

		err = mtdtest_relax();
		अगर (err)
			जाओ out;
	पूर्ण
	pr_info("verified %u eraseblocks\n", i);

	pr_info("finished with %d errors\n", errcnt);
out:
	kमुक्त(bbt);
	kमुक्त(ग_लिखोbuf);
	kमुक्त(पढ़ोbuf);
	put_mtd_device(mtd);
	अगर (err)
		pr_info("error %d occurred\n", err);
	prपूर्णांकk(KERN_INFO "=================================================\n");
	वापस err;
पूर्ण
module_init(mtd_oobtest_init);

अटल व्योम __निकास mtd_oobtest_निकास(व्योम)
अणु
	वापस;
पूर्ण
module_निकास(mtd_oobtest_निकास);

MODULE_DESCRIPTION("Out-of-band test module");
MODULE_AUTHOR("Adrian Hunter");
MODULE_LICENSE("GPL");
