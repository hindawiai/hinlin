<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_MTIO_COMPAT_H
#घोषणा _LINUX_MTIO_COMPAT_H

#समावेश <linux/compat.h>
#समावेश <uapi/linux/mtपन.स>
#समावेश <linux/uaccess.h>

/*
 * helper functions क्रम implementing compat ioctls on the four tape
 * drivers: we define the 32-bit layout of each incompatible काष्ठाure,
 * plus a wrapper function to copy it to user space in either क्रमmat.
 */

काष्ठा	mtget32 अणु
	s32	mt_type;
	s32	mt_resid;
	s32	mt_dsreg;
	s32	mt_gstat;
	s32	mt_erreg;
	s32	mt_fileno;
	s32	mt_blkno;
पूर्ण;
#घोषणा	MTIOCGET32	_IOR('m', 2, काष्ठा mtget32)

काष्ठा	mtpos32 अणु
	s32 	mt_blkno;
पूर्ण;
#घोषणा	MTIOCPOS32	_IOR('m', 3, काष्ठा mtpos32)

अटल अंतरभूत पूर्णांक put_user_mtget(व्योम __user *u, काष्ठा mtget *k)
अणु
	काष्ठा mtget32 k32 = अणु
		.mt_type   = k->mt_type,
		.mt_resid  = k->mt_resid,
		.mt_dsreg  = k->mt_dsreg,
		.mt_gstat  = k->mt_gstat,
		.mt_erreg  = k->mt_erreg,
		.mt_fileno = k->mt_fileno,
		.mt_blkno  = k->mt_blkno,
	पूर्ण;
	पूर्णांक ret;

	अगर (in_compat_syscall())
		ret = copy_to_user(u, &k32, माप(k32));
	अन्यथा
		ret = copy_to_user(u, k, माप(*k));

	वापस ret ? -EFAULT : 0;
पूर्ण

अटल अंतरभूत पूर्णांक put_user_mtpos(व्योम __user *u, काष्ठा mtpos *k)
अणु
	अगर (in_compat_syscall())
		वापस put_user(k->mt_blkno, (u32 __user *)u);
	अन्यथा
		वापस put_user(k->mt_blkno, (दीर्घ __user *)u);
पूर्ण

#पूर्ण_अगर
