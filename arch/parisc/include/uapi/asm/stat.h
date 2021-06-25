<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _PARISC_STAT_H
#घोषणा _PARISC_STAT_H

#समावेश <linux/types.h>

काष्ठा stat अणु
	अचिन्हित पूर्णांक	st_dev;		/* dev_t is 32 bits on parisc */
	अचिन्हित पूर्णांक	st_ino;		/* 32 bits */
	अचिन्हित लघु	st_mode;	/* 16 bits */
	अचिन्हित लघु	st_nlink;	/* 16 bits */
	अचिन्हित लघु	st_reserved1;	/* old st_uid */
	अचिन्हित लघु	st_reserved2;	/* old st_gid */
	अचिन्हित पूर्णांक	st_rdev;
	चिन्हित पूर्णांक	st_size;
	चिन्हित पूर्णांक	st_aसमय;
	अचिन्हित पूर्णांक	st_aसमय_nsec;
	चिन्हित पूर्णांक	st_mसमय;
	अचिन्हित पूर्णांक	st_mसमय_nsec;
	चिन्हित पूर्णांक	st_स_समय;
	अचिन्हित पूर्णांक	st_स_समय_nsec;
	पूर्णांक		st_blksize;
	पूर्णांक		st_blocks;
	अचिन्हित पूर्णांक	__unused1;	/* ACL stuff */
	अचिन्हित पूर्णांक	__unused2;	/* network */
	अचिन्हित पूर्णांक	__unused3;	/* network */
	अचिन्हित पूर्णांक	__unused4;	/* cnodes */
	अचिन्हित लघु	__unused5;	/* netsite */
	लघु		st_fstype;
	अचिन्हित पूर्णांक	st_realdev;
	अचिन्हित लघु	st_basemode;
	अचिन्हित लघु	st_spareलघु;
	अचिन्हित पूर्णांक	st_uid;
	अचिन्हित पूर्णांक	st_gid;
	अचिन्हित पूर्णांक	st_spare4[3];
पूर्ण;

#घोषणा STAT_HAVE_NSEC

/* This is the काष्ठा that 32-bit userspace applications are expecting.
 * How 64-bit apps are going to be compiled, I have no idea.  But at least
 * this way, we करोn't have a wrapper in the kernel.
 */
काष्ठा stat64 अणु
	अचिन्हित दीर्घ दीर्घ	st_dev;
	अचिन्हित पूर्णांक		__pad1;

	अचिन्हित पूर्णांक		__st_ino;	/* Not actually filled in */
	अचिन्हित पूर्णांक		st_mode;
	अचिन्हित पूर्णांक		st_nlink;
	अचिन्हित पूर्णांक		st_uid;
	अचिन्हित पूर्णांक		st_gid;
	अचिन्हित दीर्घ दीर्घ	st_rdev;
	अचिन्हित पूर्णांक		__pad2;
	चिन्हित दीर्घ दीर्घ	st_size;
	चिन्हित पूर्णांक		st_blksize;

	चिन्हित दीर्घ दीर्घ	st_blocks;
	चिन्हित पूर्णांक		st_aसमय;
	अचिन्हित पूर्णांक		st_aसमय_nsec;
	चिन्हित पूर्णांक		st_mसमय;
	अचिन्हित पूर्णांक		st_mसमय_nsec;
	चिन्हित पूर्णांक		st_स_समय;
	अचिन्हित पूर्णांक		st_स_समय_nsec;
	अचिन्हित दीर्घ दीर्घ	st_ino;
पूर्ण;

#पूर्ण_अगर
