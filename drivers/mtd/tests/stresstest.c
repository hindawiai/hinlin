<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2008 Nokia Corporation
 *
 * Test अक्रमom पढ़ोs, ग_लिखोs and erases on MTD device.
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
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/अक्रमom.h>

#समावेश "mtd_test.h"

अटल पूर्णांक dev = -EINVAL;
module_param(dev, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(dev, "MTD device number to use");

अटल पूर्णांक count = 10000;
module_param(count, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(count, "Number of operations to do (default is 10000)");

अटल काष्ठा mtd_info *mtd;
अटल अचिन्हित अक्षर *ग_लिखोbuf;
अटल अचिन्हित अक्षर *पढ़ोbuf;
अटल अचिन्हित अक्षर *bbt;
अटल पूर्णांक *offsets;

अटल पूर्णांक pgsize;
अटल पूर्णांक bufsize;
अटल पूर्णांक ebcnt;
अटल पूर्णांक pgcnt;

अटल पूर्णांक अक्रम_eb(व्योम)
अणु
	अचिन्हित पूर्णांक eb;

again:
	eb = pअक्रमom_u32();
	/* Read or ग_लिखो up 2 eraseblocks at a समय - hence 'ebcnt - 1' */
	eb %= (ebcnt - 1);
	अगर (bbt[eb])
		जाओ again;
	वापस eb;
पूर्ण

अटल पूर्णांक अक्रम_offs(व्योम)
अणु
	अचिन्हित पूर्णांक offs;

	offs = pअक्रमom_u32();
	offs %= bufsize;
	वापस offs;
पूर्ण

अटल पूर्णांक अक्रम_len(पूर्णांक offs)
अणु
	अचिन्हित पूर्णांक len;

	len = pअक्रमom_u32();
	len %= (bufsize - offs);
	वापस len;
पूर्ण

अटल पूर्णांक करो_पढ़ो(व्योम)
अणु
	पूर्णांक eb = अक्रम_eb();
	पूर्णांक offs = अक्रम_offs();
	पूर्णांक len = अक्रम_len(offs);
	loff_t addr;

	अगर (bbt[eb + 1]) अणु
		अगर (offs >= mtd->erasesize)
			offs -= mtd->erasesize;
		अगर (offs + len > mtd->erasesize)
			len = mtd->erasesize - offs;
	पूर्ण
	addr = (loff_t)eb * mtd->erasesize + offs;
	वापस mtdtest_पढ़ो(mtd, addr, len, पढ़ोbuf);
पूर्ण

अटल पूर्णांक करो_ग_लिखो(व्योम)
अणु
	पूर्णांक eb = अक्रम_eb(), offs, err, len;
	loff_t addr;

	offs = offsets[eb];
	अगर (offs >= mtd->erasesize) अणु
		err = mtdtest_erase_eraseblock(mtd, eb);
		अगर (err)
			वापस err;
		offs = offsets[eb] = 0;
	पूर्ण
	len = अक्रम_len(offs);
	len = ((len + pgsize - 1) / pgsize) * pgsize;
	अगर (offs + len > mtd->erasesize) अणु
		अगर (bbt[eb + 1])
			len = mtd->erasesize - offs;
		अन्यथा अणु
			err = mtdtest_erase_eraseblock(mtd, eb + 1);
			अगर (err)
				वापस err;
			offsets[eb + 1] = 0;
		पूर्ण
	पूर्ण
	addr = (loff_t)eb * mtd->erasesize + offs;
	err = mtdtest_ग_लिखो(mtd, addr, len, ग_लिखोbuf);
	अगर (unlikely(err))
		वापस err;
	offs += len;
	जबतक (offs > mtd->erasesize) अणु
		offsets[eb++] = mtd->erasesize;
		offs -= mtd->erasesize;
	पूर्ण
	offsets[eb] = offs;
	वापस 0;
पूर्ण

अटल पूर्णांक करो_operation(व्योम)
अणु
	अगर (pअक्रमom_u32() & 1)
		वापस करो_पढ़ो();
	अन्यथा
		वापस करो_ग_लिखो();
पूर्ण

अटल पूर्णांक __init mtd_stresstest_init(व्योम)
अणु
	पूर्णांक err;
	पूर्णांक i, op;
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

	अगर (ebcnt < 2) अणु
		pr_err("error: need at least 2 eraseblocks\n");
		err = -ENOSPC;
		जाओ out_put_mtd;
	पूर्ण

	/* Read or ग_लिखो up 2 eraseblocks at a समय */
	bufsize = mtd->erasesize * 2;

	err = -ENOMEM;
	पढ़ोbuf = vदो_स्मृति(bufsize);
	ग_लिखोbuf = vदो_स्मृति(bufsize);
	offsets = kदो_स्मृति_array(ebcnt, माप(पूर्णांक), GFP_KERNEL);
	अगर (!पढ़ोbuf || !ग_लिखोbuf || !offsets)
		जाओ out;
	क्रम (i = 0; i < ebcnt; i++)
		offsets[i] = mtd->erasesize;
	pअक्रमom_bytes(ग_लिखोbuf, bufsize);

	bbt = kzalloc(ebcnt, GFP_KERNEL);
	अगर (!bbt)
		जाओ out;
	err = mtdtest_scan_क्रम_bad_eraseblocks(mtd, bbt, 0, ebcnt);
	अगर (err)
		जाओ out;

	/* Do operations */
	pr_info("doing operations\n");
	क्रम (op = 0; op < count; op++) अणु
		अगर ((op & 1023) == 0)
			pr_info("%d operations done\n", op);
		err = करो_operation();
		अगर (err)
			जाओ out;

		err = mtdtest_relax();
		अगर (err)
			जाओ out;
	पूर्ण
	pr_info("finished, %d operations done\n", op);

out:
	kमुक्त(offsets);
	kमुक्त(bbt);
	vमुक्त(ग_लिखोbuf);
	vमुक्त(पढ़ोbuf);
out_put_mtd:
	put_mtd_device(mtd);
	अगर (err)
		pr_info("error %d occurred\n", err);
	prपूर्णांकk(KERN_INFO "=================================================\n");
	वापस err;
पूर्ण
module_init(mtd_stresstest_init);

अटल व्योम __निकास mtd_stresstest_निकास(व्योम)
अणु
	वापस;
पूर्ण
module_निकास(mtd_stresstest_निकास);

MODULE_DESCRIPTION("Stress test module");
MODULE_AUTHOR("Adrian Hunter");
MODULE_LICENSE("GPL");
