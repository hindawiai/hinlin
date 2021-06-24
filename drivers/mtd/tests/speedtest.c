<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2007 Nokia Corporation
 *
 * Test पढ़ो and ग_लिखो speed of a MTD device.
 *
 * Author: Adrian Hunter <adrian.hunter@nokia.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/kसमय.स>
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

अटल पूर्णांक count;
module_param(count, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(count, "Maximum number of eraseblocks to use "
			"(0 means use all)");

अटल काष्ठा mtd_info *mtd;
अटल अचिन्हित अक्षर *iobuf;
अटल अचिन्हित अक्षर *bbt;

अटल पूर्णांक pgsize;
अटल पूर्णांक ebcnt;
अटल पूर्णांक pgcnt;
अटल पूर्णांक goodebcnt;
अटल kसमय_प्रकार start, finish;

अटल पूर्णांक multiblock_erase(पूर्णांक ebnum, पूर्णांक blocks)
अणु
	पूर्णांक err;
	काष्ठा erase_info ei;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	स_रखो(&ei, 0, माप(काष्ठा erase_info));
	ei.addr = addr;
	ei.len  = mtd->erasesize * blocks;

	err = mtd_erase(mtd, &ei);
	अगर (err) अणु
		pr_err("error %d while erasing EB %d, blocks %d\n",
		       err, ebnum, blocks);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ग_लिखो_eraseblock(पूर्णांक ebnum)
अणु
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	वापस mtdtest_ग_लिखो(mtd, addr, mtd->erasesize, iobuf);
पूर्ण

अटल पूर्णांक ग_लिखो_eraseblock_by_page(पूर्णांक ebnum)
अणु
	पूर्णांक i, err = 0;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;
	व्योम *buf = iobuf;

	क्रम (i = 0; i < pgcnt; i++) अणु
		err = mtdtest_ग_लिखो(mtd, addr, pgsize, buf);
		अगर (err)
			अवरोध;
		addr += pgsize;
		buf += pgsize;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक ग_लिखो_eraseblock_by_2pages(पूर्णांक ebnum)
अणु
	माप_प्रकार sz = pgsize * 2;
	पूर्णांक i, n = pgcnt / 2, err = 0;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;
	व्योम *buf = iobuf;

	क्रम (i = 0; i < n; i++) अणु
		err = mtdtest_ग_लिखो(mtd, addr, sz, buf);
		अगर (err)
			वापस err;
		addr += sz;
		buf += sz;
	पूर्ण
	अगर (pgcnt % 2)
		err = mtdtest_ग_लिखो(mtd, addr, pgsize, buf);

	वापस err;
पूर्ण

अटल पूर्णांक पढ़ो_eraseblock(पूर्णांक ebnum)
अणु
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	वापस mtdtest_पढ़ो(mtd, addr, mtd->erasesize, iobuf);
पूर्ण

अटल पूर्णांक पढ़ो_eraseblock_by_page(पूर्णांक ebnum)
अणु
	पूर्णांक i, err = 0;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;
	व्योम *buf = iobuf;

	क्रम (i = 0; i < pgcnt; i++) अणु
		err = mtdtest_पढ़ो(mtd, addr, pgsize, buf);
		अगर (err)
			अवरोध;
		addr += pgsize;
		buf += pgsize;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक पढ़ो_eraseblock_by_2pages(पूर्णांक ebnum)
अणु
	माप_प्रकार sz = pgsize * 2;
	पूर्णांक i, n = pgcnt / 2, err = 0;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;
	व्योम *buf = iobuf;

	क्रम (i = 0; i < n; i++) अणु
		err = mtdtest_पढ़ो(mtd, addr, sz, buf);
		अगर (err)
			वापस err;
		addr += sz;
		buf += sz;
	पूर्ण
	अगर (pgcnt % 2)
		err = mtdtest_पढ़ो(mtd, addr, pgsize, buf);

	वापस err;
पूर्ण

अटल अंतरभूत व्योम start_timing(व्योम)
अणु
	start = kसमय_get();
पूर्ण

अटल अंतरभूत व्योम stop_timing(व्योम)
अणु
	finish = kसमय_get();
पूर्ण

अटल दीर्घ calc_speed(व्योम)
अणु
	uपूर्णांक64_t k;
	दीर्घ ms;

	ms = kसमय_ms_delta(finish, start);
	अगर (ms == 0)
		वापस 0;
	k = (uपूर्णांक64_t)goodebcnt * (mtd->erasesize / 1024) * 1000;
	करो_भाग(k, ms);
	वापस k;
पूर्ण

अटल पूर्णांक __init mtd_speedtest_init(व्योम)
अणु
	पूर्णांक err, i, blocks, j, k;
	दीर्घ speed;
	uपूर्णांक64_t पंचांगp;

	prपूर्णांकk(KERN_INFO "\n");
	prपूर्णांकk(KERN_INFO "=================================================\n");

	अगर (dev < 0) अणु
		pr_info("Please specify a valid mtd-device via module parameter\n");
		pr_crit("CAREFUL: This test wipes all data on the specified MTD device!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (count)
		pr_info("MTD device: %d    count: %d\n", dev, count);
	अन्यथा
		pr_info("MTD device: %d\n", dev);

	mtd = get_mtd_device(शून्य, dev);
	अगर (IS_ERR(mtd)) अणु
		err = PTR_ERR(mtd);
		pr_err("error: cannot get MTD device\n");
		वापस err;
	पूर्ण

	अगर (mtd->ग_लिखोsize == 1) अणु
		pr_info("not NAND flash, assume page size is 512 "
		       "bytes.\n");
		pgsize = 512;
	पूर्ण अन्यथा
		pgsize = mtd->ग_लिखोsize;

	पंचांगp = mtd->size;
	करो_भाग(पंचांगp, mtd->erasesize);
	ebcnt = पंचांगp;
	pgcnt = mtd->erasesize / pgsize;

	pr_info("MTD device size %llu, eraseblock size %u, "
	       "page size %u, count of eraseblocks %u, pages per "
	       "eraseblock %u, OOB size %u\n",
	       (अचिन्हित दीर्घ दीर्घ)mtd->size, mtd->erasesize,
	       pgsize, ebcnt, pgcnt, mtd->oobsize);

	अगर (count > 0 && count < ebcnt)
		ebcnt = count;

	err = -ENOMEM;
	iobuf = kदो_स्मृति(mtd->erasesize, GFP_KERNEL);
	अगर (!iobuf)
		जाओ out;

	pअक्रमom_bytes(iobuf, mtd->erasesize);

	bbt = kzalloc(ebcnt, GFP_KERNEL);
	अगर (!bbt)
		जाओ out;
	err = mtdtest_scan_क्रम_bad_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;
	क्रम (i = 0; i < ebcnt; i++) अणु
		अगर (!bbt[i])
			goodebcnt++;
	पूर्ण

	err = mtdtest_erase_good_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	/* Write all eraseblocks, 1 eraseblock at a समय */
	pr_info("testing eraseblock write speed\n");
	start_timing();
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = ग_लिखो_eraseblock(i);
		अगर (err)
			जाओ out;

		err = mtdtest_relax();
		अगर (err)
			जाओ out;
	पूर्ण
	stop_timing();
	speed = calc_speed();
	pr_info("eraseblock write speed is %ld KiB/s\n", speed);

	/* Read all eraseblocks, 1 eraseblock at a समय */
	pr_info("testing eraseblock read speed\n");
	start_timing();
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = पढ़ो_eraseblock(i);
		अगर (err)
			जाओ out;

		err = mtdtest_relax();
		अगर (err)
			जाओ out;
	पूर्ण
	stop_timing();
	speed = calc_speed();
	pr_info("eraseblock read speed is %ld KiB/s\n", speed);

	err = mtdtest_erase_good_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	/* Write all eraseblocks, 1 page at a समय */
	pr_info("testing page write speed\n");
	start_timing();
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = ग_लिखो_eraseblock_by_page(i);
		अगर (err)
			जाओ out;

		err = mtdtest_relax();
		अगर (err)
			जाओ out;
	पूर्ण
	stop_timing();
	speed = calc_speed();
	pr_info("page write speed is %ld KiB/s\n", speed);

	/* Read all eraseblocks, 1 page at a समय */
	pr_info("testing page read speed\n");
	start_timing();
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = पढ़ो_eraseblock_by_page(i);
		अगर (err)
			जाओ out;

		err = mtdtest_relax();
		अगर (err)
			जाओ out;
	पूर्ण
	stop_timing();
	speed = calc_speed();
	pr_info("page read speed is %ld KiB/s\n", speed);

	err = mtdtest_erase_good_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	/* Write all eraseblocks, 2 pages at a समय */
	pr_info("testing 2 page write speed\n");
	start_timing();
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = ग_लिखो_eraseblock_by_2pages(i);
		अगर (err)
			जाओ out;

		err = mtdtest_relax();
		अगर (err)
			जाओ out;
	पूर्ण
	stop_timing();
	speed = calc_speed();
	pr_info("2 page write speed is %ld KiB/s\n", speed);

	/* Read all eraseblocks, 2 pages at a समय */
	pr_info("testing 2 page read speed\n");
	start_timing();
	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = पढ़ो_eraseblock_by_2pages(i);
		अगर (err)
			जाओ out;

		err = mtdtest_relax();
		अगर (err)
			जाओ out;
	पूर्ण
	stop_timing();
	speed = calc_speed();
	pr_info("2 page read speed is %ld KiB/s\n", speed);

	/* Erase all eraseblocks */
	pr_info("Testing erase speed\n");
	start_timing();
	err = mtdtest_erase_good_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;
	stop_timing();
	speed = calc_speed();
	pr_info("erase speed is %ld KiB/s\n", speed);

	/* Multi-block erase all eraseblocks */
	क्रम (k = 1; k < 7; k++) अणु
		blocks = 1 << k;
		pr_info("Testing %dx multi-block erase speed\n",
		       blocks);
		start_timing();
		क्रम (i = 0; i < ebcnt; ) अणु
			क्रम (j = 0; j < blocks && (i + j) < ebcnt; j++)
				अगर (bbt[i + j])
					अवरोध;
			अगर (j < 1) अणु
				i++;
				जारी;
			पूर्ण
			err = multiblock_erase(i, j);
			अगर (err)
				जाओ out;

			err = mtdtest_relax();
			अगर (err)
				जाओ out;

			i += j;
		पूर्ण
		stop_timing();
		speed = calc_speed();
		pr_info("%dx multi-block erase speed is %ld KiB/s\n",
		       blocks, speed);
	पूर्ण
	pr_info("finished\n");
out:
	kमुक्त(iobuf);
	kमुक्त(bbt);
	put_mtd_device(mtd);
	अगर (err)
		pr_info("error %d occurred\n", err);
	prपूर्णांकk(KERN_INFO "=================================================\n");
	वापस err;
पूर्ण
module_init(mtd_speedtest_init);

अटल व्योम __निकास mtd_speedtest_निकास(व्योम)
अणु
	वापस;
पूर्ण
module_निकास(mtd_speedtest_निकास);

MODULE_DESCRIPTION("Speed test module");
MODULE_AUTHOR("Adrian Hunter");
MODULE_LICENSE("GPL");
