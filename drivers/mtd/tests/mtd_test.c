<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#घोषणा pr_fmt(fmt) "mtd_test: " fmt

#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/prपूर्णांकk.h>

#समावेश "mtd_test.h"

पूर्णांक mtdtest_erase_eraseblock(काष्ठा mtd_info *mtd, अचिन्हित पूर्णांक ebnum)
अणु
	पूर्णांक err;
	काष्ठा erase_info ei;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	स_रखो(&ei, 0, माप(काष्ठा erase_info));
	ei.addr = addr;
	ei.len  = mtd->erasesize;

	err = mtd_erase(mtd, &ei);
	अगर (err) अणु
		pr_info("error %d while erasing EB %d\n", err, ebnum);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक is_block_bad(काष्ठा mtd_info *mtd, अचिन्हित पूर्णांक ebnum)
अणु
	पूर्णांक ret;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;

	ret = mtd_block_isbad(mtd, addr);
	अगर (ret)
		pr_info("block %d is bad\n", ebnum);

	वापस ret;
पूर्ण

पूर्णांक mtdtest_scan_क्रम_bad_eraseblocks(काष्ठा mtd_info *mtd, अचिन्हित अक्षर *bbt,
					अचिन्हित पूर्णांक eb, पूर्णांक ebcnt)
अणु
	पूर्णांक i, bad = 0;

	अगर (!mtd_can_have_bb(mtd))
		वापस 0;

	pr_info("scanning for bad eraseblocks\n");
	क्रम (i = 0; i < ebcnt; ++i) अणु
		bbt[i] = is_block_bad(mtd, eb + i) ? 1 : 0;
		अगर (bbt[i])
			bad += 1;
		cond_resched();
	पूर्ण
	pr_info("scanned %d eraseblocks, %d are bad\n", i, bad);

	वापस 0;
पूर्ण

पूर्णांक mtdtest_erase_good_eraseblocks(काष्ठा mtd_info *mtd, अचिन्हित अक्षर *bbt,
				अचिन्हित पूर्णांक eb, पूर्णांक ebcnt)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ebcnt; ++i) अणु
		अगर (bbt[i])
			जारी;
		err = mtdtest_erase_eraseblock(mtd, eb + i);
		अगर (err)
			वापस err;
		cond_resched();
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mtdtest_पढ़ो(काष्ठा mtd_info *mtd, loff_t addr, माप_प्रकार size, व्योम *buf)
अणु
	माप_प्रकार पढ़ो;
	पूर्णांक err;

	err = mtd_पढ़ो(mtd, addr, size, &पढ़ो, buf);
	/* Ignore corrected ECC errors */
	अगर (mtd_is_bitflip(err))
		err = 0;
	अगर (!err && पढ़ो != size)
		err = -EIO;
	अगर (err)
		pr_err("error: read failed at %#llx\n", addr);

	वापस err;
पूर्ण

पूर्णांक mtdtest_ग_लिखो(काष्ठा mtd_info *mtd, loff_t addr, माप_प्रकार size,
		स्थिर व्योम *buf)
अणु
	माप_प्रकार written;
	पूर्णांक err;

	err = mtd_ग_लिखो(mtd, addr, size, &written, buf);
	अगर (!err && written != size)
		err = -EIO;
	अगर (err)
		pr_err("error: write failed at %#llx\n", addr);

	वापस err;
पूर्ण
