<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2008 Nokia Corporation
 *
 * Check MTD device पढ़ो.
 *
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

#समावेश "mtd_test.h"

अटल पूर्णांक dev = -EINVAL;
module_param(dev, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(dev, "MTD device number to use");

अटल काष्ठा mtd_info *mtd;
अटल अचिन्हित अक्षर *iobuf;
अटल अचिन्हित अक्षर *iobuf1;
अटल अचिन्हित अक्षर *bbt;

अटल पूर्णांक pgsize;
अटल पूर्णांक ebcnt;
अटल पूर्णांक pgcnt;

अटल पूर्णांक पढ़ो_eraseblock_by_page(पूर्णांक ebnum)
अणु
	पूर्णांक i, ret, err = 0;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;
	व्योम *buf = iobuf;
	व्योम *oobbuf = iobuf1;

	क्रम (i = 0; i < pgcnt; i++) अणु
		स_रखो(buf, 0 , pgsize);
		ret = mtdtest_पढ़ो(mtd, addr, pgsize, buf);
		अगर (ret) अणु
			अगर (!err)
				err = ret;
		पूर्ण
		अगर (mtd->oobsize) अणु
			काष्ठा mtd_oob_ops ops;

			ops.mode      = MTD_OPS_PLACE_OOB;
			ops.len       = 0;
			ops.retlen    = 0;
			ops.ooblen    = mtd->oobsize;
			ops.oobretlen = 0;
			ops.ooboffs   = 0;
			ops.datbuf    = शून्य;
			ops.oobbuf    = oobbuf;
			ret = mtd_पढ़ो_oob(mtd, addr, &ops);
			अगर ((ret && !mtd_is_bitflip(ret)) ||
					ops.oobretlen != mtd->oobsize) अणु
				pr_err("error: read oob failed at "
						  "%#llx\n", (दीर्घ दीर्घ)addr);
				अगर (!err)
					err = ret;
				अगर (!err)
					err = -EINVAL;
			पूर्ण
			oobbuf += mtd->oobsize;
		पूर्ण
		addr += pgsize;
		buf += pgsize;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम dump_eraseblock(पूर्णांक ebnum)
अणु
	पूर्णांक i, j, n;
	अक्षर line[128];
	पूर्णांक pg, oob;

	pr_info("dumping eraseblock %d\n", ebnum);
	n = mtd->erasesize;
	क्रम (i = 0; i < n;) अणु
		अक्षर *p = line;

		p += प्र_लिखो(p, "%05x: ", i);
		क्रम (j = 0; j < 32 && i < n; j++, i++)
			p += प्र_लिखो(p, "%02x", (अचिन्हित पूर्णांक)iobuf[i]);
		prपूर्णांकk(KERN_CRIT "%s\n", line);
		cond_resched();
	पूर्ण
	अगर (!mtd->oobsize)
		वापस;
	pr_info("dumping oob from eraseblock %d\n", ebnum);
	n = mtd->oobsize;
	क्रम (pg = 0, i = 0; pg < pgcnt; pg++)
		क्रम (oob = 0; oob < n;) अणु
			अक्षर *p = line;

			p += प्र_लिखो(p, "%05x: ", i);
			क्रम (j = 0; j < 32 && oob < n; j++, oob++, i++)
				p += प्र_लिखो(p, "%02x",
					     (अचिन्हित पूर्णांक)iobuf1[i]);
			prपूर्णांकk(KERN_CRIT "%s\n", line);
			cond_resched();
		पूर्ण
पूर्ण

अटल पूर्णांक __init mtd_पढ़ोtest_init(व्योम)
अणु
	uपूर्णांक64_t पंचांगp;
	पूर्णांक err, i;

	prपूर्णांकk(KERN_INFO "\n");
	prपूर्णांकk(KERN_INFO "=================================================\n");

	अगर (dev < 0) अणु
		pr_info("Please specify a valid mtd-device via module parameter\n");
		वापस -EINVAL;
	पूर्ण

	pr_info("MTD device: %d\n", dev);

	mtd = get_mtd_device(शून्य, dev);
	अगर (IS_ERR(mtd)) अणु
		err = PTR_ERR(mtd);
		pr_err("error: Cannot get MTD device\n");
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

	err = -ENOMEM;
	iobuf = kदो_स्मृति(mtd->erasesize, GFP_KERNEL);
	अगर (!iobuf)
		जाओ out;
	iobuf1 = kदो_स्मृति(mtd->erasesize, GFP_KERNEL);
	अगर (!iobuf1)
		जाओ out;

	bbt = kzalloc(ebcnt, GFP_KERNEL);
	अगर (!bbt)
		जाओ out;
	err = mtdtest_scan_क्रम_bad_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	/* Read all eraseblocks 1 page at a समय */
	pr_info("testing page read\n");
	क्रम (i = 0; i < ebcnt; ++i) अणु
		पूर्णांक ret;

		अगर (bbt[i])
			जारी;
		ret = पढ़ो_eraseblock_by_page(i);
		अगर (ret) अणु
			dump_eraseblock(i);
			अगर (!err)
				err = ret;
		पूर्ण

		ret = mtdtest_relax();
		अगर (ret) अणु
			err = ret;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (err)
		pr_info("finished with errors\n");
	अन्यथा
		pr_info("finished\n");

out:

	kमुक्त(iobuf);
	kमुक्त(iobuf1);
	kमुक्त(bbt);
	put_mtd_device(mtd);
	अगर (err)
		pr_info("error %d occurred\n", err);
	prपूर्णांकk(KERN_INFO "=================================================\n");
	वापस err;
पूर्ण
module_init(mtd_पढ़ोtest_init);

अटल व्योम __निकास mtd_पढ़ोtest_निकास(व्योम)
अणु
	वापस;
पूर्ण
module_निकास(mtd_पढ़ोtest_निकास);

MODULE_DESCRIPTION("Read test module");
MODULE_AUTHOR("Adrian Hunter");
MODULE_LICENSE("GPL");
