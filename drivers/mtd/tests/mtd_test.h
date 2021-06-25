<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/sched/संकेत.स>

अटल अंतरभूत पूर्णांक mtdtest_relax(व्योम)
अणु
	cond_resched();
	अगर (संकेत_pending(current)) अणु
		pr_info("aborting test due to pending signal!\n");
		वापस -EINTR;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mtdtest_erase_eraseblock(काष्ठा mtd_info *mtd, अचिन्हित पूर्णांक ebnum);
पूर्णांक mtdtest_scan_क्रम_bad_eraseblocks(काष्ठा mtd_info *mtd, अचिन्हित अक्षर *bbt,
					अचिन्हित पूर्णांक eb, पूर्णांक ebcnt);
पूर्णांक mtdtest_erase_good_eraseblocks(काष्ठा mtd_info *mtd, अचिन्हित अक्षर *bbt,
				अचिन्हित पूर्णांक eb, पूर्णांक ebcnt);

पूर्णांक mtdtest_पढ़ो(काष्ठा mtd_info *mtd, loff_t addr, माप_प्रकार size, व्योम *buf);
पूर्णांक mtdtest_ग_लिखो(काष्ठा mtd_info *mtd, loff_t addr, माप_प्रकार size,
		स्थिर व्योम *buf);
