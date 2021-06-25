<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2008 Nokia Corporation
 *
 * Test page पढ़ो and ग_लिखो on MTD device.
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
module_param(dev, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(dev, "MTD device number to use");

अटल काष्ठा mtd_info *mtd;
अटल अचिन्हित अक्षर *twopages;
अटल अचिन्हित अक्षर *ग_लिखोbuf;
अटल अचिन्हित अक्षर *boundary;
अटल अचिन्हित अक्षर *bbt;

अटल पूर्णांक pgsize;
अटल पूर्णांक bufsize;
अटल पूर्णांक ebcnt;
अटल पूर्णांक pgcnt;
अटल पूर्णांक errcnt;
अटल काष्ठा rnd_state rnd_state;

अटल पूर्णांक ग_लिखो_eraseblock(पूर्णांक ebnum)
अणु
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, mtd->erasesize);
	cond_resched();
	वापस mtdtest_ग_लिखो(mtd, addr, mtd->erasesize, ग_लिखोbuf);
पूर्ण

अटल पूर्णांक verअगरy_eraseblock(पूर्णांक ebnum)
अणु
	uपूर्णांक32_t j;
	पूर्णांक err = 0, i;
	loff_t addr0, addrn;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	addr0 = 0;
	क्रम (i = 0; i < ebcnt && bbt[i]; ++i)
		addr0 += mtd->erasesize;

	addrn = mtd->size;
	क्रम (i = 0; i < ebcnt && bbt[ebcnt - i - 1]; ++i)
		addrn -= mtd->erasesize;

	pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, mtd->erasesize);
	क्रम (j = 0; j < pgcnt - 1; ++j, addr += pgsize) अणु
		/* Do a पढ़ो to set the पूर्णांकernal dataRAMs to dअगरferent data */
		err = mtdtest_पढ़ो(mtd, addr0, bufsize, twopages);
		अगर (err)
			वापस err;
		err = mtdtest_पढ़ो(mtd, addrn - bufsize, bufsize, twopages);
		अगर (err)
			वापस err;
		स_रखो(twopages, 0, bufsize);
		err = mtdtest_पढ़ो(mtd, addr, bufsize, twopages);
		अगर (err)
			अवरोध;
		अगर (स_भेद(twopages, ग_लिखोbuf + (j * pgsize), bufsize)) अणु
			pr_err("error: verify failed at %#llx\n",
			       (दीर्घ दीर्घ)addr);
			errcnt += 1;
		पूर्ण
	पूर्ण
	/* Check boundary between eraseblocks */
	अगर (addr <= addrn - pgsize - pgsize && !bbt[ebnum + 1]) अणु
		काष्ठा rnd_state old_state = rnd_state;

		/* Do a पढ़ो to set the पूर्णांकernal dataRAMs to dअगरferent data */
		err = mtdtest_पढ़ो(mtd, addr0, bufsize, twopages);
		अगर (err)
			वापस err;
		err = mtdtest_पढ़ो(mtd, addrn - bufsize, bufsize, twopages);
		अगर (err)
			वापस err;
		स_रखो(twopages, 0, bufsize);
		err = mtdtest_पढ़ो(mtd, addr, bufsize, twopages);
		अगर (err)
			वापस err;
		स_नकल(boundary, ग_लिखोbuf + mtd->erasesize - pgsize, pgsize);
		pअक्रमom_bytes_state(&rnd_state, boundary + pgsize, pgsize);
		अगर (स_भेद(twopages, boundary, bufsize)) अणु
			pr_err("error: verify failed at %#llx\n",
			       (दीर्घ दीर्घ)addr);
			errcnt += 1;
		पूर्ण
		rnd_state = old_state;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक crosstest(व्योम)
अणु
	पूर्णांक err = 0, i;
	loff_t addr, addr0, addrn;
	अचिन्हित अक्षर *pp1, *pp2, *pp3, *pp4;

	pr_info("crosstest\n");
	pp1 = kसुस्मृति(pgsize, 4, GFP_KERNEL);
	अगर (!pp1)
		वापस -ENOMEM;
	pp2 = pp1 + pgsize;
	pp3 = pp2 + pgsize;
	pp4 = pp3 + pgsize;

	addr0 = 0;
	क्रम (i = 0; i < ebcnt && bbt[i]; ++i)
		addr0 += mtd->erasesize;

	addrn = mtd->size;
	क्रम (i = 0; i < ebcnt && bbt[ebcnt - i - 1]; ++i)
		addrn -= mtd->erasesize;

	/* Read 2nd-to-last page to pp1 */
	addr = addrn - pgsize - pgsize;
	err = mtdtest_पढ़ो(mtd, addr, pgsize, pp1);
	अगर (err) अणु
		kमुक्त(pp1);
		वापस err;
	पूर्ण

	/* Read 3rd-to-last page to pp1 */
	addr = addrn - pgsize - pgsize - pgsize;
	err = mtdtest_पढ़ो(mtd, addr, pgsize, pp1);
	अगर (err) अणु
		kमुक्त(pp1);
		वापस err;
	पूर्ण

	/* Read first page to pp2 */
	addr = addr0;
	pr_info("reading page at %#llx\n", (दीर्घ दीर्घ)addr);
	err = mtdtest_पढ़ो(mtd, addr, pgsize, pp2);
	अगर (err) अणु
		kमुक्त(pp1);
		वापस err;
	पूर्ण

	/* Read last page to pp3 */
	addr = addrn - pgsize;
	pr_info("reading page at %#llx\n", (दीर्घ दीर्घ)addr);
	err = mtdtest_पढ़ो(mtd, addr, pgsize, pp3);
	अगर (err) अणु
		kमुक्त(pp1);
		वापस err;
	पूर्ण

	/* Read first page again to pp4 */
	addr = addr0;
	pr_info("reading page at %#llx\n", (दीर्घ दीर्घ)addr);
	err = mtdtest_पढ़ो(mtd, addr, pgsize, pp4);
	अगर (err) अणु
		kमुक्त(pp1);
		वापस err;
	पूर्ण

	/* pp2 and pp4 should be the same */
	pr_info("verifying pages read at %#llx match\n",
	       (दीर्घ दीर्घ)addr0);
	अगर (स_भेद(pp2, pp4, pgsize)) अणु
		pr_err("verify failed!\n");
		errcnt += 1;
	पूर्ण अन्यथा अगर (!err)
		pr_info("crosstest ok\n");
	kमुक्त(pp1);
	वापस err;
पूर्ण

अटल पूर्णांक erasecrosstest(व्योम)
अणु
	पूर्णांक err = 0, i, ebnum, ebnum2;
	loff_t addr0;
	अक्षर *पढ़ोbuf = twopages;

	pr_info("erasecrosstest\n");

	ebnum = 0;
	addr0 = 0;
	क्रम (i = 0; i < ebcnt && bbt[i]; ++i) अणु
		addr0 += mtd->erasesize;
		ebnum += 1;
	पूर्ण

	ebnum2 = ebcnt - 1;
	जबतक (ebnum2 && bbt[ebnum2])
		ebnum2 -= 1;

	pr_info("erasing block %d\n", ebnum);
	err = mtdtest_erase_eraseblock(mtd, ebnum);
	अगर (err)
		वापस err;

	pr_info("writing 1st page of block %d\n", ebnum);
	pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, pgsize);
	म_नकल(ग_लिखोbuf, "There is no data like this!");
	err = mtdtest_ग_लिखो(mtd, addr0, pgsize, ग_लिखोbuf);
	अगर (err)
		वापस err;

	pr_info("reading 1st page of block %d\n", ebnum);
	स_रखो(पढ़ोbuf, 0, pgsize);
	err = mtdtest_पढ़ो(mtd, addr0, pgsize, पढ़ोbuf);
	अगर (err)
		वापस err;

	pr_info("verifying 1st page of block %d\n", ebnum);
	अगर (स_भेद(ग_लिखोbuf, पढ़ोbuf, pgsize)) अणु
		pr_err("verify failed!\n");
		errcnt += 1;
		वापस -1;
	पूर्ण

	pr_info("erasing block %d\n", ebnum);
	err = mtdtest_erase_eraseblock(mtd, ebnum);
	अगर (err)
		वापस err;

	pr_info("writing 1st page of block %d\n", ebnum);
	pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, pgsize);
	म_नकल(ग_लिखोbuf, "There is no data like this!");
	err = mtdtest_ग_लिखो(mtd, addr0, pgsize, ग_लिखोbuf);
	अगर (err)
		वापस err;

	pr_info("erasing block %d\n", ebnum2);
	err = mtdtest_erase_eraseblock(mtd, ebnum2);
	अगर (err)
		वापस err;

	pr_info("reading 1st page of block %d\n", ebnum);
	स_रखो(पढ़ोbuf, 0, pgsize);
	err = mtdtest_पढ़ो(mtd, addr0, pgsize, पढ़ोbuf);
	अगर (err)
		वापस err;

	pr_info("verifying 1st page of block %d\n", ebnum);
	अगर (स_भेद(ग_लिखोbuf, पढ़ोbuf, pgsize)) अणु
		pr_err("verify failed!\n");
		errcnt += 1;
		वापस -1;
	पूर्ण

	अगर (!err)
		pr_info("erasecrosstest ok\n");
	वापस err;
पूर्ण

अटल पूर्णांक erasetest(व्योम)
अणु
	पूर्णांक err = 0, i, ebnum, ok = 1;
	loff_t addr0;

	pr_info("erasetest\n");

	ebnum = 0;
	addr0 = 0;
	क्रम (i = 0; i < ebcnt && bbt[i]; ++i) अणु
		addr0 += mtd->erasesize;
		ebnum += 1;
	पूर्ण

	pr_info("erasing block %d\n", ebnum);
	err = mtdtest_erase_eraseblock(mtd, ebnum);
	अगर (err)
		वापस err;

	pr_info("writing 1st page of block %d\n", ebnum);
	pअक्रमom_bytes_state(&rnd_state, ग_लिखोbuf, pgsize);
	err = mtdtest_ग_लिखो(mtd, addr0, pgsize, ग_लिखोbuf);
	अगर (err)
		वापस err;

	pr_info("erasing block %d\n", ebnum);
	err = mtdtest_erase_eraseblock(mtd, ebnum);
	अगर (err)
		वापस err;

	pr_info("reading 1st page of block %d\n", ebnum);
	err = mtdtest_पढ़ो(mtd, addr0, pgsize, twopages);
	अगर (err)
		वापस err;

	pr_info("verifying 1st page of block %d is all 0xff\n",
	       ebnum);
	क्रम (i = 0; i < pgsize; ++i)
		अगर (twopages[i] != 0xff) अणु
			pr_err("verifying all 0xff failed at %d\n",
			       i);
			errcnt += 1;
			ok = 0;
			अवरोध;
		पूर्ण

	अगर (ok && !err)
		pr_info("erasetest ok\n");

	वापस err;
पूर्ण

अटल पूर्णांक __init mtd_pagetest_init(व्योम)
अणु
	पूर्णांक err = 0;
	uपूर्णांक64_t पंचांगp;
	uपूर्णांक32_t i;

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
	pgsize = mtd->ग_लिखोsize;

	pr_info("MTD device size %llu, eraseblock size %u, "
	       "page size %u, count of eraseblocks %u, pages per "
	       "eraseblock %u, OOB size %u\n",
	       (अचिन्हित दीर्घ दीर्घ)mtd->size, mtd->erasesize,
	       pgsize, ebcnt, pgcnt, mtd->oobsize);

	err = -ENOMEM;
	bufsize = pgsize * 2;
	ग_लिखोbuf = kदो_स्मृति(mtd->erasesize, GFP_KERNEL);
	अगर (!ग_लिखोbuf)
		जाओ out;
	twopages = kदो_स्मृति(bufsize, GFP_KERNEL);
	अगर (!twopages)
		जाओ out;
	boundary = kदो_स्मृति(bufsize, GFP_KERNEL);
	अगर (!boundary)
		जाओ out;

	bbt = kzalloc(ebcnt, GFP_KERNEL);
	अगर (!bbt)
		जाओ out;
	err = mtdtest_scan_क्रम_bad_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	/* Erase all eraseblocks */
	pr_info("erasing whole device\n");
	err = mtdtest_erase_good_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;
	pr_info("erased %u eraseblocks\n", ebcnt);

	/* Write all eraseblocks */
	pअक्रमom_seed_state(&rnd_state, 1);
	pr_info("writing whole device\n");
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = ग_लिखो_eraseblock(i);
		अगर (err)
			जाओ out;
		अगर (i % 256 == 0)
			pr_info("written up to eraseblock %u\n", i);

		err = mtdtest_relax();
		अगर (err)
			जाओ out;
	पूर्ण
	pr_info("written %u eraseblocks\n", i);

	/* Check all eraseblocks */
	pअक्रमom_seed_state(&rnd_state, 1);
	pr_info("verifying all eraseblocks\n");
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = verअगरy_eraseblock(i);
		अगर (err)
			जाओ out;
		अगर (i % 256 == 0)
			pr_info("verified up to eraseblock %u\n", i);

		err = mtdtest_relax();
		अगर (err)
			जाओ out;
	पूर्ण
	pr_info("verified %u eraseblocks\n", i);

	err = crosstest();
	अगर (err)
		जाओ out;

	अगर (ebcnt > 1) अणु
		err = erasecrosstest();
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अणु
		pr_info("skipping erasecrosstest, 2 erase blocks needed\n");
	पूर्ण

	err = erasetest();
	अगर (err)
		जाओ out;

	pr_info("finished with %d errors\n", errcnt);
out:

	kमुक्त(bbt);
	kमुक्त(boundary);
	kमुक्त(twopages);
	kमुक्त(ग_लिखोbuf);
	put_mtd_device(mtd);
	अगर (err)
		pr_info("error %d occurred\n", err);
	prपूर्णांकk(KERN_INFO "=================================================\n");
	वापस err;
पूर्ण
module_init(mtd_pagetest_init);

अटल व्योम __निकास mtd_pagetest_निकास(व्योम)
अणु
	वापस;
पूर्ण
module_निकास(mtd_pagetest_निकास);

MODULE_DESCRIPTION("NAND page test");
MODULE_AUTHOR("Adrian Hunter");
MODULE_LICENSE("GPL");
