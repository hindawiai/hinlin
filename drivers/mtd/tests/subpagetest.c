<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2007 Nokia Corporation
 *
 * Test sub-page पढ़ो and ग_लिखो on MTD device.
 * Author: Adrian Hunter <ext-adrian.hunter@nokia.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

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
module_param(dev, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(dev, "MTD device number to use");

अटल काष्ठा mtd_info *mtd;
अटल अचिन्हित अक्षर *ग_लिखोbuf;
अटल अचिन्हित अक्षर *पढ़ोbuf;
अटल अचिन्हित अक्षर *bbt;

अटल पूर्णांक subpgsize;
अटल पूर्णांक bufsize;
अटल पूर्णांक ebcnt;
अटल पूर्णांक pgcnt;
अटल पूर्णांक errcnt;
अटल काष्ठा rnd_state rnd_state;

अटल अंतरभूत व्योम clear_data(अचिन्हित अक्षर *buf, माप_प्रकार len)
अणु
	स_रखो(buf, 0, len);
पूर्ण

अटल पूर्णांक ग_लिखो_eraseblock(पूर्णांक ebnum)
अणु
	माप_प्रकार written;
	पूर्णांक err = 0;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, subpgsize);
	err = mtd_ग_लिखो(mtd, addr, subpgsize, &written, ग_लिखोbuf);
	अगर (unlikely(err || written != subpgsize)) अणु
		pr_err("error: write failed at %#llx\n",
		       (दीर्घ दीर्घ)addr);
		अगर (written != subpgsize) अणु
			pr_err("  write size: %#x\n", subpgsize);
			pr_err("  written: %#zx\n", written);
		पूर्ण
		वापस err ? err : -1;
	पूर्ण

	addr += subpgsize;

	pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, subpgsize);
	err = mtd_ग_लिखो(mtd, addr, subpgsize, &written, ग_लिखोbuf);
	अगर (unlikely(err || written != subpgsize)) अणु
		pr_err("error: write failed at %#llx\n",
		       (दीर्घ दीर्घ)addr);
		अगर (written != subpgsize) अणु
			pr_err("  write size: %#x\n", subpgsize);
			pr_err("  written: %#zx\n", written);
		पूर्ण
		वापस err ? err : -1;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ग_लिखो_eraseblock2(पूर्णांक ebnum)
अणु
	माप_प्रकार written;
	पूर्णांक err = 0, k;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	क्रम (k = 1; k < 33; ++k) अणु
		अगर (addr + (subpgsize * k) > (loff_t)(ebnum + 1) * mtd->erasesize)
			अवरोध;
		pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, subpgsize * k);
		err = mtd_ग_लिखो(mtd, addr, subpgsize * k, &written, ग_लिखोbuf);
		अगर (unlikely(err || written != subpgsize * k)) अणु
			pr_err("error: write failed at %#llx\n",
			       (दीर्घ दीर्घ)addr);
			अगर (written != subpgsize * k) अणु
				pr_err("  write size: %#x\n",
				       subpgsize * k);
				pr_err("  written: %#08zx\n",
				       written);
			पूर्ण
			वापस err ? err : -1;
		पूर्ण
		addr += subpgsize * k;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम prपूर्णांक_subpage(अचिन्हित अक्षर *p)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < subpgsize; ) अणु
		क्रम (j = 0; i < subpgsize && j < 32; ++i, ++j)
			prपूर्णांकk("%02x", *p++);
		prपूर्णांकk("\n");
	पूर्ण
पूर्ण

अटल पूर्णांक verअगरy_eraseblock(पूर्णांक ebnum)
अणु
	माप_प्रकार पढ़ो;
	पूर्णांक err = 0;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, subpgsize);
	clear_data(पढ़ोbuf, subpgsize);
	err = mtd_पढ़ो(mtd, addr, subpgsize, &पढ़ो, पढ़ोbuf);
	अगर (unlikely(err || पढ़ो != subpgsize)) अणु
		अगर (mtd_is_bitflip(err) && पढ़ो == subpgsize) अणु
			pr_info("ECC correction at %#llx\n",
			       (दीर्घ दीर्घ)addr);
			err = 0;
		पूर्ण अन्यथा अणु
			pr_err("error: read failed at %#llx\n",
			       (दीर्घ दीर्घ)addr);
			वापस err ? err : -1;
		पूर्ण
	पूर्ण
	अगर (unlikely(स_भेद(पढ़ोbuf, ग_लिखोbuf, subpgsize))) अणु
		pr_err("error: verify failed at %#llx\n",
		       (दीर्घ दीर्घ)addr);
		pr_info("------------- written----------------\n");
		prपूर्णांक_subpage(ग_लिखोbuf);
		pr_info("------------- read ------------------\n");
		prपूर्णांक_subpage(पढ़ोbuf);
		pr_info("-------------------------------------\n");
		errcnt += 1;
	पूर्ण

	addr += subpgsize;

	pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, subpgsize);
	clear_data(पढ़ोbuf, subpgsize);
	err = mtd_पढ़ो(mtd, addr, subpgsize, &पढ़ो, पढ़ोbuf);
	अगर (unlikely(err || पढ़ो != subpgsize)) अणु
		अगर (mtd_is_bitflip(err) && पढ़ो == subpgsize) अणु
			pr_info("ECC correction at %#llx\n",
			       (दीर्घ दीर्घ)addr);
			err = 0;
		पूर्ण अन्यथा अणु
			pr_err("error: read failed at %#llx\n",
			       (दीर्घ दीर्घ)addr);
			वापस err ? err : -1;
		पूर्ण
	पूर्ण
	अगर (unlikely(स_भेद(पढ़ोbuf, ग_लिखोbuf, subpgsize))) अणु
		pr_info("error: verify failed at %#llx\n",
		       (दीर्घ दीर्घ)addr);
		pr_info("------------- written----------------\n");
		prपूर्णांक_subpage(ग_लिखोbuf);
		pr_info("------------- read ------------------\n");
		prपूर्णांक_subpage(पढ़ोbuf);
		pr_info("-------------------------------------\n");
		errcnt += 1;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक verअगरy_eraseblock2(पूर्णांक ebnum)
अणु
	माप_प्रकार पढ़ो;
	पूर्णांक err = 0, k;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	क्रम (k = 1; k < 33; ++k) अणु
		अगर (addr + (subpgsize * k) > (loff_t)(ebnum + 1) * mtd->erasesize)
			अवरोध;
		pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, subpgsize * k);
		clear_data(पढ़ोbuf, subpgsize * k);
		err = mtd_पढ़ो(mtd, addr, subpgsize * k, &पढ़ो, पढ़ोbuf);
		अगर (unlikely(err || पढ़ो != subpgsize * k)) अणु
			अगर (mtd_is_bitflip(err) && पढ़ो == subpgsize * k) अणु
				pr_info("ECC correction at %#llx\n",
				       (दीर्घ दीर्घ)addr);
				err = 0;
			पूर्ण अन्यथा अणु
				pr_err("error: read failed at "
				       "%#llx\n", (दीर्घ दीर्घ)addr);
				वापस err ? err : -1;
			पूर्ण
		पूर्ण
		अगर (unlikely(स_भेद(पढ़ोbuf, ग_लिखोbuf, subpgsize * k))) अणु
			pr_err("error: verify failed at %#llx\n",
			       (दीर्घ दीर्घ)addr);
			errcnt += 1;
		पूर्ण
		addr += subpgsize * k;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक verअगरy_eraseblock_ff(पूर्णांक ebnum)
अणु
	uपूर्णांक32_t j;
	माप_प्रकार पढ़ो;
	पूर्णांक err = 0;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	स_रखो(ग_लिखोbuf, 0xff, subpgsize);
	क्रम (j = 0; j < mtd->erasesize / subpgsize; ++j) अणु
		clear_data(पढ़ोbuf, subpgsize);
		err = mtd_पढ़ो(mtd, addr, subpgsize, &पढ़ो, पढ़ोbuf);
		अगर (unlikely(err || पढ़ो != subpgsize)) अणु
			अगर (mtd_is_bitflip(err) && पढ़ो == subpgsize) अणु
				pr_info("ECC correction at %#llx\n",
				       (दीर्घ दीर्घ)addr);
				err = 0;
			पूर्ण अन्यथा अणु
				pr_err("error: read failed at "
				       "%#llx\n", (दीर्घ दीर्घ)addr);
				वापस err ? err : -1;
			पूर्ण
		पूर्ण
		अगर (unlikely(स_भेद(पढ़ोbuf, ग_लिखोbuf, subpgsize))) अणु
			pr_err("error: verify 0xff failed at "
			       "%#llx\n", (दीर्घ दीर्घ)addr);
			errcnt += 1;
		पूर्ण
		addr += subpgsize;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक verअगरy_all_eraseblocks_ff(व्योम)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i;

	pr_info("verifying all eraseblocks for 0xff\n");
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = verअगरy_eraseblock_ff(i);
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

अटल पूर्णांक __init mtd_subpagetest_init(व्योम)
अणु
	पूर्णांक err = 0;
	uपूर्णांक32_t i;
	uपूर्णांक64_t पंचांगp;

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

	subpgsize = mtd->ग_लिखोsize >> mtd->subpage_sft;
	पंचांगp = mtd->size;
	करो_भाग(पंचांगp, mtd->erasesize);
	ebcnt = पंचांगp;
	pgcnt = mtd->erasesize / mtd->ग_लिखोsize;

	pr_info("MTD device size %llu, eraseblock size %u, "
	       "page size %u, subpage size %u, count of eraseblocks %u, "
	       "pages per eraseblock %u, OOB size %u\n",
	       (अचिन्हित दीर्घ दीर्घ)mtd->size, mtd->erasesize,
	       mtd->ग_लिखोsize, subpgsize, ebcnt, pgcnt, mtd->oobsize);

	err = -ENOMEM;
	bufsize = subpgsize * 32;
	ग_लिखोbuf = kदो_स्मृति(bufsize, GFP_KERNEL);
	अगर (!ग_लिखोbuf)
		जाओ out;
	पढ़ोbuf = kदो_स्मृति(bufsize, GFP_KERNEL);
	अगर (!पढ़ोbuf)
		जाओ out;
	bbt = kzalloc(ebcnt, GFP_KERNEL);
	अगर (!bbt)
		जाओ out;

	err = mtdtest_scan_क्रम_bad_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	err = mtdtest_erase_good_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	pr_info("writing whole device\n");
	pअक्रमom_seed_state(&rnd_state, 1);
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = ग_लिखो_eraseblock(i);
		अगर (unlikely(err))
			जाओ out;
		अगर (i % 256 == 0)
			pr_info("written up to eraseblock %u\n", i);

		err = mtdtest_relax();
		अगर (err)
			जाओ out;
	पूर्ण
	pr_info("written %u eraseblocks\n", i);

	pअक्रमom_seed_state(&rnd_state, 1);
	pr_info("verifying all eraseblocks\n");
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = verअगरy_eraseblock(i);
		अगर (unlikely(err))
			जाओ out;
		अगर (i % 256 == 0)
			pr_info("verified up to eraseblock %u\n", i);

		err = mtdtest_relax();
		अगर (err)
			जाओ out;
	पूर्ण
	pr_info("verified %u eraseblocks\n", i);

	err = mtdtest_erase_good_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	err = verअगरy_all_eraseblocks_ff();
	अगर (err)
		जाओ out;

	/* Write all eraseblocks */
	pअक्रमom_seed_state(&rnd_state, 3);
	pr_info("writing whole device\n");
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = ग_लिखो_eraseblock2(i);
		अगर (unlikely(err))
			जाओ out;
		अगर (i % 256 == 0)
			pr_info("written up to eraseblock %u\n", i);

		err = mtdtest_relax();
		अगर (err)
			जाओ out;
	पूर्ण
	pr_info("written %u eraseblocks\n", i);

	/* Check all eraseblocks */
	pअक्रमom_seed_state(&rnd_state, 3);
	pr_info("verifying all eraseblocks\n");
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = verअगरy_eraseblock2(i);
		अगर (unlikely(err))
			जाओ out;
		अगर (i % 256 == 0)
			pr_info("verified up to eraseblock %u\n", i);

		err = mtdtest_relax();
		अगर (err)
			जाओ out;
	पूर्ण
	pr_info("verified %u eraseblocks\n", i);

	err = mtdtest_erase_good_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	err = verअगरy_all_eraseblocks_ff();
	अगर (err)
		जाओ out;

	pr_info("finished with %d errors\n", errcnt);

out:
	kमुक्त(bbt);
	kमुक्त(पढ़ोbuf);
	kमुक्त(ग_लिखोbuf);
	put_mtd_device(mtd);
	अगर (err)
		pr_info("error %d occurred\n", err);
	prपूर्णांकk(KERN_INFO "=================================================\n");
	वापस err;
पूर्ण
module_init(mtd_subpagetest_init);

अटल व्योम __निकास mtd_subpagetest_निकास(व्योम)
अणु
	वापस;
पूर्ण
module_निकास(mtd_subpagetest_निकास);

MODULE_DESCRIPTION("Subpage test module");
MODULE_AUTHOR("Adrian Hunter");
MODULE_LICENSE("GPL");
