<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright तऊ 1999-2010 David Woodhouse <dwmw2@infradead.org>
 */

#समावेश <linux/device.h>
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>
#समावेश <linux/err.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/mutex.h>
#समावेश <linux/backing-dev.h>
#समावेश <linux/compat.h>
#समावेश <linux/mount.h>
#समावेश <linux/blkpg.h>
#समावेश <linux/magic.h>
#समावेश <linux/major.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/map.h>

#समावेश <linux/uaccess.h>

#समावेश "mtdcore.h"

/*
 * Data काष्ठाure to hold the poपूर्णांकer to the mtd device as well
 * as mode inक्रमmation of various use हालs.
 */
काष्ठा mtd_file_info अणु
	काष्ठा mtd_info *mtd;
	क्रमागत mtd_file_modes mode;
पूर्ण;

अटल loff_t mtdअक्षर_lseek(काष्ठा file *file, loff_t offset, पूर्णांक orig)
अणु
	काष्ठा mtd_file_info *mfi = file->निजी_data;
	वापस fixed_size_llseek(file, offset, orig, mfi->mtd->size);
पूर्ण

अटल पूर्णांक mtdअक्षर_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक minor = iminor(inode);
	पूर्णांक devnum = minor >> 1;
	पूर्णांक ret = 0;
	काष्ठा mtd_info *mtd;
	काष्ठा mtd_file_info *mfi;

	pr_debug("MTD_open\n");

	/* You can't खोलो the RO devices RW */
	अगर ((file->f_mode & FMODE_WRITE) && (minor & 1))
		वापस -EACCES;

	mtd = get_mtd_device(शून्य, devnum);

	अगर (IS_ERR(mtd))
		वापस PTR_ERR(mtd);

	अगर (mtd->type == MTD_ABSENT) अणु
		ret = -ENODEV;
		जाओ out1;
	पूर्ण

	/* You can't open it RW if it's not a ग_लिखोable device */
	अगर ((file->f_mode & FMODE_WRITE) && !(mtd->flags & MTD_WRITEABLE)) अणु
		ret = -EACCES;
		जाओ out1;
	पूर्ण

	mfi = kzalloc(माप(*mfi), GFP_KERNEL);
	अगर (!mfi) अणु
		ret = -ENOMEM;
		जाओ out1;
	पूर्ण
	mfi->mtd = mtd;
	file->निजी_data = mfi;
	वापस 0;

out1:
	put_mtd_device(mtd);
	वापस ret;
पूर्ण /* mtdअक्षर_खोलो */

/*====================================================================*/

अटल पूर्णांक mtdअक्षर_बंद(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा mtd_file_info *mfi = file->निजी_data;
	काष्ठा mtd_info *mtd = mfi->mtd;

	pr_debug("MTD_close\n");

	/* Only sync अगर खोलोed RW */
	अगर ((file->f_mode & FMODE_WRITE))
		mtd_sync(mtd);

	put_mtd_device(mtd);
	file->निजी_data = शून्य;
	kमुक्त(mfi);

	वापस 0;
पूर्ण /* mtdअक्षर_बंद */

/* Back in June 2001, dwmw2 wrote:
 *
 *   FIXME: This _really_ needs to die. In 2.5, we should lock the
 *   userspace buffer करोwn and use it directly with पढ़ोv/ग_लिखोv.
 *
 * The implementation below, using mtd_kदो_स्मृति_up_to, mitigates
 * allocation failures when the प्रणाली is under low-memory situations
 * or अगर memory is highly fragmented at the cost of reducing the
 * perक्रमmance of the requested transfer due to a smaller buffer size.
 *
 * A more complex but more memory-efficient implementation based on
 * get_user_pages and iovecs to cover extents of those pages is a
 * दीर्घer-term goal, as पूर्णांकimated by dwmw2 above. However, क्रम the
 * ग_लिखो हाल, this requires yet more complex head and tail transfer
 * handling when those head and tail offsets and sizes are such that
 * alignment requirements are not met in the न_अंकD subdriver.
 */

अटल sमाप_प्रकार mtdअक्षर_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count,
			loff_t *ppos)
अणु
	काष्ठा mtd_file_info *mfi = file->निजी_data;
	काष्ठा mtd_info *mtd = mfi->mtd;
	माप_प्रकार retlen;
	माप_प्रकार total_retlen=0;
	पूर्णांक ret=0;
	पूर्णांक len;
	माप_प्रकार size = count;
	अक्षर *kbuf;

	pr_debug("MTD_read\n");

	अगर (*ppos + count > mtd->size) अणु
		अगर (*ppos < mtd->size)
			count = mtd->size - *ppos;
		अन्यथा
			count = 0;
	पूर्ण

	अगर (!count)
		वापस 0;

	kbuf = mtd_kदो_स्मृति_up_to(mtd, &size);
	अगर (!kbuf)
		वापस -ENOMEM;

	जबतक (count) अणु
		len = min_t(माप_प्रकार, count, size);

		चयन (mfi->mode) अणु
		हाल MTD_खाता_MODE_OTP_FACTORY:
			ret = mtd_पढ़ो_fact_prot_reg(mtd, *ppos, len,
						     &retlen, kbuf);
			अवरोध;
		हाल MTD_खाता_MODE_OTP_USER:
			ret = mtd_पढ़ो_user_prot_reg(mtd, *ppos, len,
						     &retlen, kbuf);
			अवरोध;
		हाल MTD_खाता_MODE_RAW:
		अणु
			काष्ठा mtd_oob_ops ops = अणुपूर्ण;

			ops.mode = MTD_OPS_RAW;
			ops.datbuf = kbuf;
			ops.oobbuf = शून्य;
			ops.len = len;

			ret = mtd_पढ़ो_oob(mtd, *ppos, &ops);
			retlen = ops.retlen;
			अवरोध;
		पूर्ण
		शेष:
			ret = mtd_पढ़ो(mtd, *ppos, len, &retlen, kbuf);
		पूर्ण
		/* Nand वापसs -EBADMSG on ECC errors, but it वापसs
		 * the data. For our userspace tools it is important
		 * to dump areas with ECC errors!
		 * For kernel पूर्णांकernal usage it also might वापस -EUCLEAN
		 * to संकेत the caller that a bitflip has occurred and has
		 * been corrected by the ECC algorithm.
		 * Userspace software which accesses न_अंकD this way
		 * must be aware of the fact that it deals with न_अंकD
		 */
		अगर (!ret || mtd_is_bitflip_or_eccerr(ret)) अणु
			*ppos += retlen;
			अगर (copy_to_user(buf, kbuf, retlen)) अणु
				kमुक्त(kbuf);
				वापस -EFAULT;
			पूर्ण
			अन्यथा
				total_retlen += retlen;

			count -= retlen;
			buf += retlen;
			अगर (retlen == 0)
				count = 0;
		पूर्ण
		अन्यथा अणु
			kमुक्त(kbuf);
			वापस ret;
		पूर्ण

	पूर्ण

	kमुक्त(kbuf);
	वापस total_retlen;
पूर्ण /* mtdअक्षर_पढ़ो */

अटल sमाप_प्रकार mtdअक्षर_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count,
			loff_t *ppos)
अणु
	काष्ठा mtd_file_info *mfi = file->निजी_data;
	काष्ठा mtd_info *mtd = mfi->mtd;
	माप_प्रकार size = count;
	अक्षर *kbuf;
	माप_प्रकार retlen;
	माप_प्रकार total_retlen=0;
	पूर्णांक ret=0;
	पूर्णांक len;

	pr_debug("MTD_write\n");

	अगर (*ppos >= mtd->size)
		वापस -ENOSPC;

	अगर (*ppos + count > mtd->size)
		count = mtd->size - *ppos;

	अगर (!count)
		वापस 0;

	kbuf = mtd_kदो_स्मृति_up_to(mtd, &size);
	अगर (!kbuf)
		वापस -ENOMEM;

	जबतक (count) अणु
		len = min_t(माप_प्रकार, count, size);

		अगर (copy_from_user(kbuf, buf, len)) अणु
			kमुक्त(kbuf);
			वापस -EFAULT;
		पूर्ण

		चयन (mfi->mode) अणु
		हाल MTD_खाता_MODE_OTP_FACTORY:
			ret = -EROFS;
			अवरोध;
		हाल MTD_खाता_MODE_OTP_USER:
			ret = mtd_ग_लिखो_user_prot_reg(mtd, *ppos, len,
						      &retlen, kbuf);
			अवरोध;

		हाल MTD_खाता_MODE_RAW:
		अणु
			काष्ठा mtd_oob_ops ops = अणुपूर्ण;

			ops.mode = MTD_OPS_RAW;
			ops.datbuf = kbuf;
			ops.oobbuf = शून्य;
			ops.ooboffs = 0;
			ops.len = len;

			ret = mtd_ग_लिखो_oob(mtd, *ppos, &ops);
			retlen = ops.retlen;
			अवरोध;
		पूर्ण

		शेष:
			ret = mtd_ग_लिखो(mtd, *ppos, len, &retlen, kbuf);
		पूर्ण

		/*
		 * Return -ENOSPC only अगर no data could be written at all.
		 * Otherwise just वापस the number of bytes that actually
		 * have been written.
		 */
		अगर ((ret == -ENOSPC) && (total_retlen))
			अवरोध;

		अगर (!ret) अणु
			*ppos += retlen;
			total_retlen += retlen;
			count -= retlen;
			buf += retlen;
		पूर्ण
		अन्यथा अणु
			kमुक्त(kbuf);
			वापस ret;
		पूर्ण
	पूर्ण

	kमुक्त(kbuf);
	वापस total_retlen;
पूर्ण /* mtdअक्षर_ग_लिखो */

/*======================================================================

    IOCTL calls क्रम getting device parameters.

======================================================================*/

अटल पूर्णांक otp_select_filemode(काष्ठा mtd_file_info *mfi, पूर्णांक mode)
अणु
	काष्ठा mtd_info *mtd = mfi->mtd;
	माप_प्रकार retlen;

	चयन (mode) अणु
	हाल MTD_OTP_FACTORY:
		अगर (mtd_पढ़ो_fact_prot_reg(mtd, -1, 0, &retlen, शून्य) ==
				-EOPNOTSUPP)
			वापस -EOPNOTSUPP;

		mfi->mode = MTD_खाता_MODE_OTP_FACTORY;
		अवरोध;
	हाल MTD_OTP_USER:
		अगर (mtd_पढ़ो_user_prot_reg(mtd, -1, 0, &retlen, शून्य) ==
				-EOPNOTSUPP)
			वापस -EOPNOTSUPP;

		mfi->mode = MTD_खाता_MODE_OTP_USER;
		अवरोध;
	हाल MTD_OTP_OFF:
		mfi->mode = MTD_खाता_MODE_NORMAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mtdअक्षर_ग_लिखोoob(काष्ठा file *file, काष्ठा mtd_info *mtd,
	uपूर्णांक64_t start, uपूर्णांक32_t length, व्योम __user *ptr,
	uपूर्णांक32_t __user *retp)
अणु
	काष्ठा mtd_info *master  = mtd_get_master(mtd);
	काष्ठा mtd_file_info *mfi = file->निजी_data;
	काष्ठा mtd_oob_ops ops = अणुपूर्ण;
	uपूर्णांक32_t retlen;
	पूर्णांक ret = 0;

	अगर (length > 4096)
		वापस -EINVAL;

	अगर (!master->_ग_लिखो_oob)
		वापस -EOPNOTSUPP;

	ops.ooblen = length;
	ops.ooboffs = start & (mtd->ग_लिखोsize - 1);
	ops.datbuf = शून्य;
	ops.mode = (mfi->mode == MTD_खाता_MODE_RAW) ? MTD_OPS_RAW :
		MTD_OPS_PLACE_OOB;

	अगर (ops.ooboffs && ops.ooblen > (mtd->oobsize - ops.ooboffs))
		वापस -EINVAL;

	ops.oobbuf = memdup_user(ptr, length);
	अगर (IS_ERR(ops.oobbuf))
		वापस PTR_ERR(ops.oobbuf);

	start &= ~((uपूर्णांक64_t)mtd->ग_लिखोsize - 1);
	ret = mtd_ग_लिखो_oob(mtd, start, &ops);

	अगर (ops.oobretlen > 0xFFFFFFFFU)
		ret = -EOVERFLOW;
	retlen = ops.oobretlen;
	अगर (copy_to_user(retp, &retlen, माप(length)))
		ret = -EFAULT;

	kमुक्त(ops.oobbuf);
	वापस ret;
पूर्ण

अटल पूर्णांक mtdअक्षर_पढ़ोoob(काष्ठा file *file, काष्ठा mtd_info *mtd,
	uपूर्णांक64_t start, uपूर्णांक32_t length, व्योम __user *ptr,
	uपूर्णांक32_t __user *retp)
अणु
	काष्ठा mtd_file_info *mfi = file->निजी_data;
	काष्ठा mtd_oob_ops ops = अणुपूर्ण;
	पूर्णांक ret = 0;

	अगर (length > 4096)
		वापस -EINVAL;

	ops.ooblen = length;
	ops.ooboffs = start & (mtd->ग_लिखोsize - 1);
	ops.datbuf = शून्य;
	ops.mode = (mfi->mode == MTD_खाता_MODE_RAW) ? MTD_OPS_RAW :
		MTD_OPS_PLACE_OOB;

	अगर (ops.ooboffs && ops.ooblen > (mtd->oobsize - ops.ooboffs))
		वापस -EINVAL;

	ops.oobbuf = kदो_स्मृति(length, GFP_KERNEL);
	अगर (!ops.oobbuf)
		वापस -ENOMEM;

	start &= ~((uपूर्णांक64_t)mtd->ग_लिखोsize - 1);
	ret = mtd_पढ़ो_oob(mtd, start, &ops);

	अगर (put_user(ops.oobretlen, retp))
		ret = -EFAULT;
	अन्यथा अगर (ops.oobretlen && copy_to_user(ptr, ops.oobbuf,
					    ops.oobretlen))
		ret = -EFAULT;

	kमुक्त(ops.oobbuf);

	/*
	 * न_अंकD वापसs -EBADMSG on ECC errors, but it वापसs the OOB
	 * data. For our userspace tools it is important to dump areas
	 * with ECC errors!
	 * For kernel पूर्णांकernal usage it also might वापस -EUCLEAN
	 * to संकेत the caller that a bitflip has occurred and has
	 * been corrected by the ECC algorithm.
	 *
	 * Note: currently the standard न_अंकD function, nand_पढ़ो_oob_std,
	 * करोes not calculate ECC क्रम the OOB area, so करो not rely on
	 * this behavior unless you have replaced it with your own.
	 */
	अगर (mtd_is_bitflip_or_eccerr(ret))
		वापस 0;

	वापस ret;
पूर्ण

/*
 * Copies (and truncates, अगर necessary) OOB layout inक्रमmation to the
 * deprecated layout काष्ठा, nand_ecclayout_user. This is necessary only to
 * support the deprecated API ioctl ECCGETLAYOUT जबतक allowing all new
 * functionality to use mtd_ooblayout_ops flexibly (i.e. mtd_ooblayout_ops
 * can describe any kind of OOB layout with almost zero overhead from a
 * memory usage poपूर्णांक of view).
 */
अटल पूर्णांक shrink_ecclayout(काष्ठा mtd_info *mtd,
			    काष्ठा nand_ecclayout_user *to)
अणु
	काष्ठा mtd_oob_region oobregion;
	पूर्णांक i, section = 0, ret;

	अगर (!mtd || !to)
		वापस -EINVAL;

	स_रखो(to, 0, माप(*to));

	to->eccbytes = 0;
	क्रम (i = 0; i < MTD_MAX_ECCPOS_ENTRIES;) अणु
		u32 eccpos;

		ret = mtd_ooblayout_ecc(mtd, section++, &oobregion);
		अगर (ret < 0) अणु
			अगर (ret != -दुस्फल)
				वापस ret;

			अवरोध;
		पूर्ण

		eccpos = oobregion.offset;
		क्रम (; i < MTD_MAX_ECCPOS_ENTRIES &&
		       eccpos < oobregion.offset + oobregion.length; i++) अणु
			to->eccpos[i] = eccpos++;
			to->eccbytes++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < MTD_MAX_OOBFREE_ENTRIES; i++) अणु
		ret = mtd_ooblayout_मुक्त(mtd, i, &oobregion);
		अगर (ret < 0) अणु
			अगर (ret != -दुस्फल)
				वापस ret;

			अवरोध;
		पूर्ण

		to->oobमुक्त[i].offset = oobregion.offset;
		to->oobमुक्त[i].length = oobregion.length;
		to->oobavail += to->oobमुक्त[i].length;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक get_oobinfo(काष्ठा mtd_info *mtd, काष्ठा nand_oobinfo *to)
अणु
	काष्ठा mtd_oob_region oobregion;
	पूर्णांक i, section = 0, ret;

	अगर (!mtd || !to)
		वापस -EINVAL;

	स_रखो(to, 0, माप(*to));

	to->eccbytes = 0;
	क्रम (i = 0; i < ARRAY_SIZE(to->eccpos);) अणु
		u32 eccpos;

		ret = mtd_ooblayout_ecc(mtd, section++, &oobregion);
		अगर (ret < 0) अणु
			अगर (ret != -दुस्फल)
				वापस ret;

			अवरोध;
		पूर्ण

		अगर (oobregion.length + i > ARRAY_SIZE(to->eccpos))
			वापस -EINVAL;

		eccpos = oobregion.offset;
		क्रम (; eccpos < oobregion.offset + oobregion.length; i++) अणु
			to->eccpos[i] = eccpos++;
			to->eccbytes++;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < 8; i++) अणु
		ret = mtd_ooblayout_मुक्त(mtd, i, &oobregion);
		अगर (ret < 0) अणु
			अगर (ret != -दुस्फल)
				वापस ret;

			अवरोध;
		पूर्ण

		to->oobमुक्त[i][0] = oobregion.offset;
		to->oobमुक्त[i][1] = oobregion.length;
	पूर्ण

	to->useecc = MTD_न_अंकDECC_AUTOPLACE;

	वापस 0;
पूर्ण

अटल पूर्णांक mtdअक्षर_blkpg_ioctl(काष्ठा mtd_info *mtd,
			       काष्ठा blkpg_ioctl_arg *arg)
अणु
	काष्ठा blkpg_partition p;

	अगर (!capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (copy_from_user(&p, arg->data, माप(p)))
		वापस -EFAULT;

	चयन (arg->op) अणु
	हाल BLKPG_ADD_PARTITION:

		/* Only master mtd device must be used to add partitions */
		अगर (mtd_is_partition(mtd))
			वापस -EINVAL;

		/* Sanitize user input */
		p.devname[BLKPG_DEVNAMELTH - 1] = '\0';

		वापस mtd_add_partition(mtd, p.devname, p.start, p.length);

	हाल BLKPG_DEL_PARTITION:

		अगर (p.pno < 0)
			वापस -EINVAL;

		वापस mtd_del_partition(mtd, p.pno);

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mtdअक्षर_ग_लिखो_ioctl(काष्ठा mtd_info *mtd,
		काष्ठा mtd_ग_लिखो_req __user *argp)
अणु
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	काष्ठा mtd_ग_लिखो_req req;
	काष्ठा mtd_oob_ops ops = अणुपूर्ण;
	स्थिर व्योम __user *usr_data, *usr_oob;
	पूर्णांक ret;

	अगर (copy_from_user(&req, argp, माप(req)))
		वापस -EFAULT;

	usr_data = (स्थिर व्योम __user *)(uपूर्णांकptr_t)req.usr_data;
	usr_oob = (स्थिर व्योम __user *)(uपूर्णांकptr_t)req.usr_oob;

	अगर (!master->_ग_लिखो_oob)
		वापस -EOPNOTSUPP;
	ops.mode = req.mode;
	ops.len = (माप_प्रकार)req.len;
	ops.ooblen = (माप_प्रकार)req.ooblen;
	ops.ooboffs = 0;

	अगर (usr_data) अणु
		ops.datbuf = memdup_user(usr_data, ops.len);
		अगर (IS_ERR(ops.datbuf))
			वापस PTR_ERR(ops.datbuf);
	पूर्ण अन्यथा अणु
		ops.datbuf = शून्य;
	पूर्ण

	अगर (usr_oob) अणु
		ops.oobbuf = memdup_user(usr_oob, ops.ooblen);
		अगर (IS_ERR(ops.oobbuf)) अणु
			kमुक्त(ops.datbuf);
			वापस PTR_ERR(ops.oobbuf);
		पूर्ण
	पूर्ण अन्यथा अणु
		ops.oobbuf = शून्य;
	पूर्ण

	ret = mtd_ग_लिखो_oob(mtd, (loff_t)req.start, &ops);

	kमुक्त(ops.datbuf);
	kमुक्त(ops.oobbuf);

	वापस ret;
पूर्ण

अटल पूर्णांक mtdअक्षर_ioctl(काष्ठा file *file, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	काष्ठा mtd_file_info *mfi = file->निजी_data;
	काष्ठा mtd_info *mtd = mfi->mtd;
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	व्योम __user *argp = (व्योम __user *)arg;
	पूर्णांक ret = 0;
	काष्ठा mtd_info_user info;

	pr_debug("MTD_ioctl\n");

	/*
	 * Check the file mode to require "dangerous" commands to have ग_लिखो
	 * permissions.
	 */
	चयन (cmd) अणु
	/* "safe" commands */
	हाल MEMGETREGIONCOUNT:
	हाल MEMGETREGIONINFO:
	हाल MEMGETINFO:
	हाल MEMREADOOB:
	हाल MEMREADOOB64:
	हाल MEMISLOCKED:
	हाल MEMGETOOBSEL:
	हाल MEMGETBADBLOCK:
	हाल OTPSELECT:
	हाल OTPGETREGIONCOUNT:
	हाल OTPGETREGIONINFO:
	हाल ECCGETLAYOUT:
	हाल ECCGETSTATS:
	हाल MTDखाताMODE:
	हाल BLKPG:
	हाल BLKRRPART:
		अवरोध;

	/* "dangerous" commands */
	हाल MEMERASE:
	हाल MEMERASE64:
	हाल MEMLOCK:
	हाल MEMUNLOCK:
	हाल MEMSETBADBLOCK:
	हाल MEMWRITEOOB:
	हाल MEMWRITEOOB64:
	हाल MEMWRITE:
	हाल OTPLOCK:
	हाल OTPERASE:
		अगर (!(file->f_mode & FMODE_WRITE))
			वापस -EPERM;
		अवरोध;

	शेष:
		वापस -ENOTTY;
	पूर्ण

	चयन (cmd) अणु
	हाल MEMGETREGIONCOUNT:
		अगर (copy_to_user(argp, &(mtd->numeraseregions), माप(पूर्णांक)))
			वापस -EFAULT;
		अवरोध;

	हाल MEMGETREGIONINFO:
	अणु
		uपूर्णांक32_t ur_idx;
		काष्ठा mtd_erase_region_info *kr;
		काष्ठा region_info_user __user *ur = argp;

		अगर (get_user(ur_idx, &(ur->regionindex)))
			वापस -EFAULT;

		अगर (ur_idx >= mtd->numeraseregions)
			वापस -EINVAL;

		kr = &(mtd->eraseregions[ur_idx]);

		अगर (put_user(kr->offset, &(ur->offset))
		    || put_user(kr->erasesize, &(ur->erasesize))
		    || put_user(kr->numblocks, &(ur->numblocks)))
			वापस -EFAULT;

		अवरोध;
	पूर्ण

	हाल MEMGETINFO:
		स_रखो(&info, 0, माप(info));
		info.type	= mtd->type;
		info.flags	= mtd->flags;
		info.size	= mtd->size;
		info.erasesize	= mtd->erasesize;
		info.ग_लिखोsize	= mtd->ग_लिखोsize;
		info.oobsize	= mtd->oobsize;
		/* The below field is obsolete */
		info.padding	= 0;
		अगर (copy_to_user(argp, &info, माप(काष्ठा mtd_info_user)))
			वापस -EFAULT;
		अवरोध;

	हाल MEMERASE:
	हाल MEMERASE64:
	अणु
		काष्ठा erase_info *erase;

		erase=kzalloc(माप(काष्ठा erase_info),GFP_KERNEL);
		अगर (!erase)
			ret = -ENOMEM;
		अन्यथा अणु
			अगर (cmd == MEMERASE64) अणु
				काष्ठा erase_info_user64 einfo64;

				अगर (copy_from_user(&einfo64, argp,
					    माप(काष्ठा erase_info_user64))) अणु
					kमुक्त(erase);
					वापस -EFAULT;
				पूर्ण
				erase->addr = einfo64.start;
				erase->len = einfo64.length;
			पूर्ण अन्यथा अणु
				काष्ठा erase_info_user einfo32;

				अगर (copy_from_user(&einfo32, argp,
					    माप(काष्ठा erase_info_user))) अणु
					kमुक्त(erase);
					वापस -EFAULT;
				पूर्ण
				erase->addr = einfo32.start;
				erase->len = einfo32.length;
			पूर्ण

			ret = mtd_erase(mtd, erase);
			kमुक्त(erase);
		पूर्ण
		अवरोध;
	पूर्ण

	हाल MEMWRITEOOB:
	अणु
		काष्ठा mtd_oob_buf buf;
		काष्ठा mtd_oob_buf __user *buf_user = argp;

		/* NOTE: ग_लिखोs वापस length to buf_user->length */
		अगर (copy_from_user(&buf, argp, माप(buf)))
			ret = -EFAULT;
		अन्यथा
			ret = mtdअक्षर_ग_लिखोoob(file, mtd, buf.start, buf.length,
				buf.ptr, &buf_user->length);
		अवरोध;
	पूर्ण

	हाल MEMREADOOB:
	अणु
		काष्ठा mtd_oob_buf buf;
		काष्ठा mtd_oob_buf __user *buf_user = argp;

		/* NOTE: ग_लिखोs वापस length to buf_user->start */
		अगर (copy_from_user(&buf, argp, माप(buf)))
			ret = -EFAULT;
		अन्यथा
			ret = mtdअक्षर_पढ़ोoob(file, mtd, buf.start, buf.length,
				buf.ptr, &buf_user->start);
		अवरोध;
	पूर्ण

	हाल MEMWRITEOOB64:
	अणु
		काष्ठा mtd_oob_buf64 buf;
		काष्ठा mtd_oob_buf64 __user *buf_user = argp;

		अगर (copy_from_user(&buf, argp, माप(buf)))
			ret = -EFAULT;
		अन्यथा
			ret = mtdअक्षर_ग_लिखोoob(file, mtd, buf.start, buf.length,
				(व्योम __user *)(uपूर्णांकptr_t)buf.usr_ptr,
				&buf_user->length);
		अवरोध;
	पूर्ण

	हाल MEMREADOOB64:
	अणु
		काष्ठा mtd_oob_buf64 buf;
		काष्ठा mtd_oob_buf64 __user *buf_user = argp;

		अगर (copy_from_user(&buf, argp, माप(buf)))
			ret = -EFAULT;
		अन्यथा
			ret = mtdअक्षर_पढ़ोoob(file, mtd, buf.start, buf.length,
				(व्योम __user *)(uपूर्णांकptr_t)buf.usr_ptr,
				&buf_user->length);
		अवरोध;
	पूर्ण

	हाल MEMWRITE:
	अणु
		ret = mtdअक्षर_ग_लिखो_ioctl(mtd,
		      (काष्ठा mtd_ग_लिखो_req __user *)arg);
		अवरोध;
	पूर्ण

	हाल MEMLOCK:
	अणु
		काष्ठा erase_info_user einfo;

		अगर (copy_from_user(&einfo, argp, माप(einfo)))
			वापस -EFAULT;

		ret = mtd_lock(mtd, einfo.start, einfo.length);
		अवरोध;
	पूर्ण

	हाल MEMUNLOCK:
	अणु
		काष्ठा erase_info_user einfo;

		अगर (copy_from_user(&einfo, argp, माप(einfo)))
			वापस -EFAULT;

		ret = mtd_unlock(mtd, einfo.start, einfo.length);
		अवरोध;
	पूर्ण

	हाल MEMISLOCKED:
	अणु
		काष्ठा erase_info_user einfo;

		अगर (copy_from_user(&einfo, argp, माप(einfo)))
			वापस -EFAULT;

		ret = mtd_is_locked(mtd, einfo.start, einfo.length);
		अवरोध;
	पूर्ण

	/* Legacy पूर्णांकerface */
	हाल MEMGETOOBSEL:
	अणु
		काष्ठा nand_oobinfo oi;

		अगर (!master->ooblayout)
			वापस -EOPNOTSUPP;

		ret = get_oobinfo(mtd, &oi);
		अगर (ret)
			वापस ret;

		अगर (copy_to_user(argp, &oi, माप(काष्ठा nand_oobinfo)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण

	हाल MEMGETBADBLOCK:
	अणु
		loff_t offs;

		अगर (copy_from_user(&offs, argp, माप(loff_t)))
			वापस -EFAULT;
		वापस mtd_block_isbad(mtd, offs);
	पूर्ण

	हाल MEMSETBADBLOCK:
	अणु
		loff_t offs;

		अगर (copy_from_user(&offs, argp, माप(loff_t)))
			वापस -EFAULT;
		वापस mtd_block_markbad(mtd, offs);
	पूर्ण

	हाल OTPSELECT:
	अणु
		पूर्णांक mode;
		अगर (copy_from_user(&mode, argp, माप(पूर्णांक)))
			वापस -EFAULT;

		mfi->mode = MTD_खाता_MODE_NORMAL;

		ret = otp_select_filemode(mfi, mode);

		file->f_pos = 0;
		अवरोध;
	पूर्ण

	हाल OTPGETREGIONCOUNT:
	हाल OTPGETREGIONINFO:
	अणु
		काष्ठा otp_info *buf = kदो_स्मृति(4096, GFP_KERNEL);
		माप_प्रकार retlen;
		अगर (!buf)
			वापस -ENOMEM;
		चयन (mfi->mode) अणु
		हाल MTD_खाता_MODE_OTP_FACTORY:
			ret = mtd_get_fact_prot_info(mtd, 4096, &retlen, buf);
			अवरोध;
		हाल MTD_खाता_MODE_OTP_USER:
			ret = mtd_get_user_prot_info(mtd, 4096, &retlen, buf);
			अवरोध;
		शेष:
			ret = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (!ret) अणु
			अगर (cmd == OTPGETREGIONCOUNT) अणु
				पूर्णांक nbr = retlen / माप(काष्ठा otp_info);
				ret = copy_to_user(argp, &nbr, माप(पूर्णांक));
			पूर्ण अन्यथा
				ret = copy_to_user(argp, buf, retlen);
			अगर (ret)
				ret = -EFAULT;
		पूर्ण
		kमुक्त(buf);
		अवरोध;
	पूर्ण

	हाल OTPLOCK:
	हाल OTPERASE:
	अणु
		काष्ठा otp_info oinfo;

		अगर (mfi->mode != MTD_खाता_MODE_OTP_USER)
			वापस -EINVAL;
		अगर (copy_from_user(&oinfo, argp, माप(oinfo)))
			वापस -EFAULT;
		अगर (cmd == OTPLOCK)
			ret = mtd_lock_user_prot_reg(mtd, oinfo.start, oinfo.length);
		अन्यथा
			ret = mtd_erase_user_prot_reg(mtd, oinfo.start, oinfo.length);
		अवरोध;
	पूर्ण

	/* This ioctl is being deprecated - it truncates the ECC layout */
	हाल ECCGETLAYOUT:
	अणु
		काष्ठा nand_ecclayout_user *usrlay;

		अगर (!master->ooblayout)
			वापस -EOPNOTSUPP;

		usrlay = kदो_स्मृति(माप(*usrlay), GFP_KERNEL);
		अगर (!usrlay)
			वापस -ENOMEM;

		shrink_ecclayout(mtd, usrlay);

		अगर (copy_to_user(argp, usrlay, माप(*usrlay)))
			ret = -EFAULT;
		kमुक्त(usrlay);
		अवरोध;
	पूर्ण

	हाल ECCGETSTATS:
	अणु
		अगर (copy_to_user(argp, &mtd->ecc_stats,
				 माप(काष्ठा mtd_ecc_stats)))
			वापस -EFAULT;
		अवरोध;
	पूर्ण

	हाल MTDखाताMODE:
	अणु
		mfi->mode = 0;

		चयन(arg) अणु
		हाल MTD_खाता_MODE_OTP_FACTORY:
		हाल MTD_खाता_MODE_OTP_USER:
			ret = otp_select_filemode(mfi, arg);
			अवरोध;

		हाल MTD_खाता_MODE_RAW:
			अगर (!mtd_has_oob(mtd))
				वापस -EOPNOTSUPP;
			mfi->mode = arg;
			अवरोध;

		हाल MTD_खाता_MODE_NORMAL:
			अवरोध;
		शेष:
			ret = -EINVAL;
		पूर्ण
		file->f_pos = 0;
		अवरोध;
	पूर्ण

	हाल BLKPG:
	अणु
		काष्ठा blkpg_ioctl_arg __user *blk_arg = argp;
		काष्ठा blkpg_ioctl_arg a;

		अगर (copy_from_user(&a, blk_arg, माप(a)))
			ret = -EFAULT;
		अन्यथा
			ret = mtdअक्षर_blkpg_ioctl(mtd, &a);
		अवरोध;
	पूर्ण

	हाल BLKRRPART:
	अणु
		/* No reपढ़ो partition feature. Just वापस ok */
		ret = 0;
		अवरोध;
	पूर्ण
	पूर्ण

	वापस ret;
पूर्ण /* memory_ioctl */

अटल दीर्घ mtdअक्षर_unlocked_ioctl(काष्ठा file *file, u_पूर्णांक cmd, u_दीर्घ arg)
अणु
	काष्ठा mtd_file_info *mfi = file->निजी_data;
	काष्ठा mtd_info *mtd = mfi->mtd;
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	पूर्णांक ret;

	mutex_lock(&master->master.chrdev_lock);
	ret = mtdअक्षर_ioctl(file, cmd, arg);
	mutex_unlock(&master->master.chrdev_lock);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_COMPAT

काष्ठा mtd_oob_buf32 अणु
	u_पूर्णांक32_t start;
	u_पूर्णांक32_t length;
	compat_caddr_t ptr;	/* अचिन्हित अक्षर* */
पूर्ण;

#घोषणा MEMWRITEOOB32		_IOWR('M', 3, काष्ठा mtd_oob_buf32)
#घोषणा MEMREADOOB32		_IOWR('M', 4, काष्ठा mtd_oob_buf32)

अटल दीर्घ mtdअक्षर_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
	अचिन्हित दीर्घ arg)
अणु
	काष्ठा mtd_file_info *mfi = file->निजी_data;
	काष्ठा mtd_info *mtd = mfi->mtd;
	काष्ठा mtd_info *master = mtd_get_master(mtd);
	व्योम __user *argp = compat_ptr(arg);
	पूर्णांक ret = 0;

	mutex_lock(&master->master.chrdev_lock);

	चयन (cmd) अणु
	हाल MEMWRITEOOB32:
	अणु
		काष्ठा mtd_oob_buf32 buf;
		काष्ठा mtd_oob_buf32 __user *buf_user = argp;

		अगर (!(file->f_mode & FMODE_WRITE)) अणु
			ret = -EPERM;
			अवरोध;
		पूर्ण

		अगर (copy_from_user(&buf, argp, माप(buf)))
			ret = -EFAULT;
		अन्यथा
			ret = mtdअक्षर_ग_लिखोoob(file, mtd, buf.start,
				buf.length, compat_ptr(buf.ptr),
				&buf_user->length);
		अवरोध;
	पूर्ण

	हाल MEMREADOOB32:
	अणु
		काष्ठा mtd_oob_buf32 buf;
		काष्ठा mtd_oob_buf32 __user *buf_user = argp;

		/* NOTE: ग_लिखोs वापस length to buf->start */
		अगर (copy_from_user(&buf, argp, माप(buf)))
			ret = -EFAULT;
		अन्यथा
			ret = mtdअक्षर_पढ़ोoob(file, mtd, buf.start,
				buf.length, compat_ptr(buf.ptr),
				&buf_user->start);
		अवरोध;
	पूर्ण

	हाल BLKPG:
	अणु
		/* Convert from blkpg_compat_ioctl_arg to blkpg_ioctl_arg */
		काष्ठा blkpg_compat_ioctl_arg __user *uarg = argp;
		काष्ठा blkpg_compat_ioctl_arg compat_arg;
		काष्ठा blkpg_ioctl_arg a;

		अगर (copy_from_user(&compat_arg, uarg, माप(compat_arg))) अणु
			ret = -EFAULT;
			अवरोध;
		पूर्ण

		स_रखो(&a, 0, माप(a));
		a.op = compat_arg.op;
		a.flags = compat_arg.flags;
		a.datalen = compat_arg.datalen;
		a.data = compat_ptr(compat_arg.data);

		ret = mtdअक्षर_blkpg_ioctl(mtd, &a);
		अवरोध;
	पूर्ण

	शेष:
		ret = mtdअक्षर_ioctl(file, cmd, (अचिन्हित दीर्घ)argp);
	पूर्ण

	mutex_unlock(&master->master.chrdev_lock);

	वापस ret;
पूर्ण

#पूर्ण_अगर /* CONFIG_COMPAT */

/*
 * try to determine where a shared mapping can be made
 * - only supported क्रम NOMMU at the moment (MMU can't doesn't copy निजी
 *   mappings)
 */
#अगर_अघोषित CONFIG_MMU
अटल अचिन्हित दीर्घ mtdअक्षर_get_unmapped_area(काष्ठा file *file,
					   अचिन्हित दीर्घ addr,
					   अचिन्हित दीर्घ len,
					   अचिन्हित दीर्घ pgoff,
					   अचिन्हित दीर्घ flags)
अणु
	काष्ठा mtd_file_info *mfi = file->निजी_data;
	काष्ठा mtd_info *mtd = mfi->mtd;
	अचिन्हित दीर्घ offset;
	पूर्णांक ret;

	अगर (addr != 0)
		वापस (अचिन्हित दीर्घ) -EINVAL;

	अगर (len > mtd->size || pgoff >= (mtd->size >> PAGE_SHIFT))
		वापस (अचिन्हित दीर्घ) -EINVAL;

	offset = pgoff << PAGE_SHIFT;
	अगर (offset > mtd->size - len)
		वापस (अचिन्हित दीर्घ) -EINVAL;

	ret = mtd_get_unmapped_area(mtd, len, offset, flags);
	वापस ret == -EOPNOTSUPP ? -ENODEV : ret;
पूर्ण

अटल अचिन्हित mtdअक्षर_mmap_capabilities(काष्ठा file *file)
अणु
	काष्ठा mtd_file_info *mfi = file->निजी_data;

	वापस mtd_mmap_capabilities(mfi->mtd);
पूर्ण
#पूर्ण_अगर

/*
 * set up a mapping क्रम shared memory segments
 */
अटल पूर्णांक mtdअक्षर_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
#अगर_घोषित CONFIG_MMU
	काष्ठा mtd_file_info *mfi = file->निजी_data;
	काष्ठा mtd_info *mtd = mfi->mtd;
	काष्ठा map_info *map = mtd->priv;

        /* This is broken because it assumes the MTD device is map-based
	   and that mtd->priv is a valid काष्ठा map_info.  It should be
	   replaced with something that uses the mtd_get_unmapped_area()
	   operation properly. */
	अगर (0 /*mtd->type == MTD_RAM || mtd->type == MTD_ROM*/) अणु
#अगर_घोषित pgprot_noncached
		अगर (file->f_flags & O_DSYNC || map->phys >= __pa(high_memory))
			vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
#पूर्ण_अगर
		वापस vm_iomap_memory(vma, map->phys, map->size);
	पूर्ण
	वापस -ENODEV;
#अन्यथा
	वापस vma->vm_flags & VM_SHARED ? 0 : -EACCES;
#पूर्ण_अगर
पूर्ण

अटल स्थिर काष्ठा file_operations mtd_fops = अणु
	.owner		= THIS_MODULE,
	.llseek		= mtdअक्षर_lseek,
	.पढ़ो		= mtdअक्षर_पढ़ो,
	.ग_लिखो		= mtdअक्षर_ग_लिखो,
	.unlocked_ioctl	= mtdअक्षर_unlocked_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= mtdअक्षर_compat_ioctl,
#पूर्ण_अगर
	.खोलो		= mtdअक्षर_खोलो,
	.release	= mtdअक्षर_बंद,
	.mmap		= mtdअक्षर_mmap,
#अगर_अघोषित CONFIG_MMU
	.get_unmapped_area = mtdअक्षर_get_unmapped_area,
	.mmap_capabilities = mtdअक्षर_mmap_capabilities,
#पूर्ण_अगर
पूर्ण;

पूर्णांक __init init_mtdअक्षर(व्योम)
अणु
	पूर्णांक ret;

	ret = __रेजिस्टर_chrdev(MTD_CHAR_MAJOR, 0, 1 << MINORBITS,
				   "mtd", &mtd_fops);
	अगर (ret < 0) अणु
		pr_err("Can't allocate major number %d for MTD\n",
		       MTD_CHAR_MAJOR);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

व्योम __निकास cleanup_mtdअक्षर(व्योम)
अणु
	__unरेजिस्टर_chrdev(MTD_CHAR_MAJOR, 0, 1 << MINORBITS, "mtd");
पूर्ण

MODULE_ALIAS_CHARDEV_MAJOR(MTD_CHAR_MAJOR);
