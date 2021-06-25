<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2006-2008 Artem Bityutskiy
 * Copyright (C) 2006-2008 Jarkko Lavinen
 * Copyright (C) 2006-2008 Adrian Hunter
 *
 * Authors: Artem Bityutskiy, Jarkko Lavinen, Adria Hunter
 *
 * WARNING: this test program may समाप्त your flash and your device. Do not
 * use it unless you know what you करो. Authors are not responsible क्रम any
 * damage caused by this program.
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
#समावेश "mtd_test.h"

#घोषणा RETRIES 3

अटल पूर्णांक eb = 8;
module_param(eb, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(eb, "eraseblock number within the selected MTD device");

अटल पूर्णांक ebcnt = 32;
module_param(ebcnt, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(ebcnt, "number of consecutive eraseblocks to torture");

अटल पूर्णांक pgcnt;
module_param(pgcnt, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(pgcnt, "number of pages per eraseblock to torture (0 => all)");

अटल पूर्णांक dev = -EINVAL;
module_param(dev, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(dev, "MTD device number to use");

अटल पूर्णांक gran = 512;
module_param(gran, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(gran, "how often the status information should be printed");

अटल पूर्णांक check = 1;
module_param(check, पूर्णांक, S_IRUGO);
MODULE_PARM_DESC(check, "if the written data should be checked");

अटल अचिन्हित पूर्णांक cycles_count;
module_param(cycles_count, uपूर्णांक, S_IRUGO);
MODULE_PARM_DESC(cycles_count, "how many erase cycles to do "
			       "(infinite by default)");

अटल काष्ठा mtd_info *mtd;

/* This buffer contains 0x555555...0xAAAAAA... pattern */
अटल अचिन्हित अक्षर *patt_5A5;
/* This buffer contains 0xAAAAAA...0x555555... pattern */
अटल अचिन्हित अक्षर *patt_A5A;
/* This buffer contains all 0xFF bytes */
अटल अचिन्हित अक्षर *patt_FF;
/* This a temporary buffer is use when checking data */
अटल अचिन्हित अक्षर *check_buf;
/* How many erase cycles were करोne */
अटल अचिन्हित पूर्णांक erase_cycles;

अटल पूर्णांक pgsize;
अटल kसमय_प्रकार start, finish;

अटल व्योम report_corrupt(अचिन्हित अक्षर *पढ़ो, अचिन्हित अक्षर *written);

अटल अंतरभूत व्योम start_timing(व्योम)
अणु
	start = kसमय_get();
पूर्ण

अटल अंतरभूत व्योम stop_timing(व्योम)
अणु
	finish = kसमय_get();
पूर्ण

/*
 * Check that the contents of eraseblock number @enbum is equivalent to the
 * @buf buffer.
 */
अटल अंतरभूत पूर्णांक check_eraseblock(पूर्णांक ebnum, अचिन्हित अक्षर *buf)
अणु
	पूर्णांक err, retries = 0;
	माप_प्रकार पढ़ो;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;
	माप_प्रकार len = mtd->erasesize;

	अगर (pgcnt) अणु
		addr = (loff_t)(ebnum + 1) * mtd->erasesize - pgcnt * pgsize;
		len = pgcnt * pgsize;
	पूर्ण

retry:
	err = mtd_पढ़ो(mtd, addr, len, &पढ़ो, check_buf);
	अगर (mtd_is_bitflip(err))
		pr_err("single bit flip occurred at EB %d "
		       "MTD reported that it was fixed.\n", ebnum);
	अन्यथा अगर (err) अणु
		pr_err("error %d while reading EB %d, "
		       "read %zd\n", err, ebnum, पढ़ो);
		वापस err;
	पूर्ण

	अगर (पढ़ो != len) अणु
		pr_err("failed to read %zd bytes from EB %d, "
		       "read only %zd, but no error reported\n",
		       len, ebnum, पढ़ो);
		वापस -EIO;
	पूर्ण

	अगर (स_भेद(buf, check_buf, len)) अणु
		pr_err("read wrong data from EB %d\n", ebnum);
		report_corrupt(check_buf, buf);

		अगर (retries++ < RETRIES) अणु
			/* Try पढ़ो again */
			yield();
			pr_info("re-try reading data from EB %d\n",
			       ebnum);
			जाओ retry;
		पूर्ण अन्यथा अणु
			pr_info("retried %d times, still errors, "
			       "give-up\n", RETRIES);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (retries != 0)
		pr_info("only attempt number %d was OK (!!!)\n",
		       retries);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ग_लिखो_pattern(पूर्णांक ebnum, व्योम *buf)
अणु
	पूर्णांक err;
	माप_प्रकार written;
	loff_t addr = (loff_t)ebnum * mtd->erasesize;
	माप_प्रकार len = mtd->erasesize;

	अगर (pgcnt) अणु
		addr = (loff_t)(ebnum + 1) * mtd->erasesize - pgcnt * pgsize;
		len = pgcnt * pgsize;
	पूर्ण
	err = mtd_ग_लिखो(mtd, addr, len, &written, buf);
	अगर (err) अणु
		pr_err("error %d while writing EB %d, written %zd"
		      " bytes\n", err, ebnum, written);
		वापस err;
	पूर्ण
	अगर (written != len) अणु
		pr_info("written only %zd bytes of %zd, but no error"
		       " reported\n", written, len);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init tort_init(व्योम)
अणु
	पूर्णांक err = 0, i, infinite = !cycles_count;
	अचिन्हित अक्षर *bad_ebs;

	prपूर्णांकk(KERN_INFO "\n");
	prपूर्णांकk(KERN_INFO "=================================================\n");
	pr_info("Warning: this program is trying to wear out your "
	       "flash, stop it if this is not wanted.\n");

	अगर (dev < 0) अणु
		pr_info("Please specify a valid mtd-device via module parameter\n");
		pr_crit("CAREFUL: This test wipes all data on the specified MTD device!\n");
		वापस -EINVAL;
	पूर्ण

	pr_info("MTD device: %d\n", dev);
	pr_info("torture %d eraseblocks (%d-%d) of mtd%d\n",
	       ebcnt, eb, eb + ebcnt - 1, dev);
	अगर (pgcnt)
		pr_info("torturing just %d pages per eraseblock\n",
			pgcnt);
	pr_info("write verify %s\n", check ? "enabled" : "disabled");

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

	अगर (pgcnt && (pgcnt > mtd->erasesize / pgsize || pgcnt < 0)) अणु
		pr_err("error: invalid pgcnt value %d\n", pgcnt);
		जाओ out_mtd;
	पूर्ण

	err = -ENOMEM;
	patt_5A5 = kदो_स्मृति(mtd->erasesize, GFP_KERNEL);
	अगर (!patt_5A5)
		जाओ out_mtd;

	patt_A5A = kदो_स्मृति(mtd->erasesize, GFP_KERNEL);
	अगर (!patt_A5A)
		जाओ out_patt_5A5;

	patt_FF = kदो_स्मृति(mtd->erasesize, GFP_KERNEL);
	अगर (!patt_FF)
		जाओ out_patt_A5A;

	check_buf = kदो_स्मृति(mtd->erasesize, GFP_KERNEL);
	अगर (!check_buf)
		जाओ out_patt_FF;

	bad_ebs = kzalloc(ebcnt, GFP_KERNEL);
	अगर (!bad_ebs)
		जाओ out_check_buf;

	err = 0;

	/* Initialize patterns */
	स_रखो(patt_FF, 0xFF, mtd->erasesize);
	क्रम (i = 0; i < mtd->erasesize / pgsize; i++) अणु
		अगर (!(i & 1)) अणु
			स_रखो(patt_5A5 + i * pgsize, 0x55, pgsize);
			स_रखो(patt_A5A + i * pgsize, 0xAA, pgsize);
		पूर्ण अन्यथा अणु
			स_रखो(patt_5A5 + i * pgsize, 0xAA, pgsize);
			स_रखो(patt_A5A + i * pgsize, 0x55, pgsize);
		पूर्ण
	पूर्ण

	err = mtdtest_scan_क्रम_bad_eraseblocks(mtd, bad_ebs, eb, ebcnt);
	अगर (err)
		जाओ out;

	start_timing();
	जबतक (1) अणु
		पूर्णांक i;
		व्योम *patt;

		err = mtdtest_erase_good_eraseblocks(mtd, bad_ebs, eb, ebcnt);
		अगर (err)
			जाओ out;

		/* Check अगर the eraseblocks contain only 0xFF bytes */
		अगर (check) अणु
			क्रम (i = eb; i < eb + ebcnt; i++) अणु
				अगर (bad_ebs[i - eb])
					जारी;
				err = check_eraseblock(i, patt_FF);
				अगर (err) अणु
					pr_info("verify failed"
					       " for 0xFF... pattern\n");
					जाओ out;
				पूर्ण

				err = mtdtest_relax();
				अगर (err)
					जाओ out;
			पूर्ण
		पूर्ण

		/* Write the pattern */
		क्रम (i = eb; i < eb + ebcnt; i++) अणु
			अगर (bad_ebs[i - eb])
				जारी;
			अगर ((eb + erase_cycles) & 1)
				patt = patt_5A5;
			अन्यथा
				patt = patt_A5A;
			err = ग_लिखो_pattern(i, patt);
			अगर (err)
				जाओ out;

			err = mtdtest_relax();
			अगर (err)
				जाओ out;
		पूर्ण

		/* Verअगरy what we wrote */
		अगर (check) अणु
			क्रम (i = eb; i < eb + ebcnt; i++) अणु
				अगर (bad_ebs[i - eb])
					जारी;
				अगर ((eb + erase_cycles) & 1)
					patt = patt_5A5;
				अन्यथा
					patt = patt_A5A;
				err = check_eraseblock(i, patt);
				अगर (err) अणु
					pr_info("verify failed for %s"
					       " pattern\n",
					       ((eb + erase_cycles) & 1) ?
					       "0x55AA55..." : "0xAA55AA...");
					जाओ out;
				पूर्ण

				err = mtdtest_relax();
				अगर (err)
					जाओ out;
			पूर्ण
		पूर्ण

		erase_cycles += 1;

		अगर (erase_cycles % gran == 0) अणु
			दीर्घ ms;

			stop_timing();
			ms = kसमय_ms_delta(finish, start);
			pr_info("%08u erase cycles done, took %lu "
			       "milliseconds (%lu seconds)\n",
			       erase_cycles, ms, ms / 1000);
			start_timing();
		पूर्ण

		अगर (!infinite && --cycles_count == 0)
			अवरोध;
	पूर्ण
out:

	pr_info("finished after %u erase cycles\n",
	       erase_cycles);
	kमुक्त(bad_ebs);
out_check_buf:
	kमुक्त(check_buf);
out_patt_FF:
	kमुक्त(patt_FF);
out_patt_A5A:
	kमुक्त(patt_A5A);
out_patt_5A5:
	kमुक्त(patt_5A5);
out_mtd:
	put_mtd_device(mtd);
	अगर (err)
		pr_info("error %d occurred during torturing\n", err);
	prपूर्णांकk(KERN_INFO "=================================================\n");
	वापस err;
पूर्ण
module_init(tort_init);

अटल व्योम __निकास tort_निकास(व्योम)
अणु
	वापस;
पूर्ण
module_निकास(tort_निकास);

अटल पूर्णांक countdअगरfs(अचिन्हित अक्षर *buf, अचिन्हित अक्षर *check_buf,
		      अचिन्हित offset, अचिन्हित len, अचिन्हित *bytesp,
		      अचिन्हित *bitsp);
अटल व्योम prपूर्णांक_bufs(अचिन्हित अक्षर *पढ़ो, अचिन्हित अक्षर *written, पूर्णांक start,
		       पूर्णांक len);

/*
 * Report the detailed inक्रमmation about how the पढ़ो EB dअगरfers from what was
 * written.
 */
अटल व्योम report_corrupt(अचिन्हित अक्षर *पढ़ो, अचिन्हित अक्षर *written)
अणु
	पूर्णांक i;
	पूर्णांक bytes, bits, pages, first;
	पूर्णांक offset, len;
	माप_प्रकार check_len = mtd->erasesize;

	अगर (pgcnt)
		check_len = pgcnt * pgsize;

	bytes = bits = pages = 0;
	क्रम (i = 0; i < check_len; i += pgsize)
		अगर (countdअगरfs(written, पढ़ो, i, pgsize, &bytes,
			       &bits) >= 0)
			pages++;

	pr_info("verify fails on %d pages, %d bytes/%d bits\n",
	       pages, bytes, bits);
	pr_info("The following is a list of all differences between"
	       " what was read from flash and what was expected\n");

	क्रम (i = 0; i < check_len; i += pgsize) अणु
		cond_resched();
		bytes = bits = 0;
		first = countdअगरfs(written, पढ़ो, i, pgsize, &bytes,
				   &bits);
		अगर (first < 0)
			जारी;

		prपूर्णांकk("-------------------------------------------------------"
		       "----------------------------------\n");

		pr_info("Page %zd has %d bytes/%d bits failing verify,"
		       " starting at offset 0x%x\n",
		       (mtd->erasesize - check_len + i) / pgsize,
		       bytes, bits, first);

		offset = first & ~0x7;
		len = ((first + bytes) | 0x7) + 1 - offset;

		prपूर्णांक_bufs(पढ़ो, written, offset, len);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_bufs(अचिन्हित अक्षर *पढ़ो, अचिन्हित अक्षर *written, पूर्णांक start,
		       पूर्णांक len)
अणु
	पूर्णांक i = 0, j1, j2;
	अक्षर *dअगरf;

	prपूर्णांकk("Offset       Read                          Written\n");
	जबतक (i < len) अणु
		prपूर्णांकk("0x%08x: ", start + i);
		dअगरf = "   ";
		क्रम (j1 = 0; j1 < 8 && i + j1 < len; j1++) अणु
			prपूर्णांकk(" %02x", पढ़ो[start + i + j1]);
			अगर (पढ़ो[start + i + j1] != written[start + i + j1])
				dअगरf = "***";
		पूर्ण

		जबतक (j1 < 8) अणु
			prपूर्णांकk(" ");
			j1 += 1;
		पूर्ण

		prपूर्णांकk("  %s ", dअगरf);

		क्रम (j2 = 0; j2 < 8 && i + j2 < len; j2++)
			prपूर्णांकk(" %02x", written[start + i + j2]);
		prपूर्णांकk("\n");
		i += 8;
	पूर्ण
पूर्ण

/*
 * Count the number of dअगरfering bytes and bits and वापस the first dअगरfering
 * offset.
 */
अटल पूर्णांक countdअगरfs(अचिन्हित अक्षर *buf, अचिन्हित अक्षर *check_buf,
		      अचिन्हित offset, अचिन्हित len, अचिन्हित *bytesp,
		      अचिन्हित *bitsp)
अणु
	अचिन्हित i, bit;
	पूर्णांक first = -1;

	क्रम (i = offset; i < offset + len; i++)
		अगर (buf[i] != check_buf[i]) अणु
			first = i;
			अवरोध;
		पूर्ण

	जबतक (i < offset + len) अणु
		अगर (buf[i] != check_buf[i]) अणु
			(*bytesp)++;
			bit = 1;
			जबतक (bit < 256) अणु
				अगर ((buf[i] & bit) != (check_buf[i] & bit))
					(*bitsp)++;
				bit <<= 1;
			पूर्ण
		पूर्ण
		i++;
	पूर्ण

	वापस first;
पूर्ण

MODULE_DESCRIPTION("Eraseblock torturing module");
MODULE_AUTHOR("Artem Bityutskiy, Jarkko Lavinen, Adrian Hunter");
MODULE_LICENSE("GPL");
