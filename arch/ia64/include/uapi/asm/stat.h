<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_IA64_STAT_H
#घोषणा _ASM_IA64_STAT_H

/*
 * Modअगरied 1998, 1999
 *	David Mosberger-Tang <davidm@hpl.hp.com>, Hewlett-Packard Co
 */

काष्ठा stat अणु
	अचिन्हित दीर्घ	st_dev;
	अचिन्हित दीर्घ	st_ino;
	अचिन्हित दीर्घ	st_nlink;
	अचिन्हित पूर्णांक	st_mode;
	अचिन्हित पूर्णांक	st_uid;
	अचिन्हित पूर्णांक	st_gid;
	अचिन्हित पूर्णांक	__pad0;
	अचिन्हित दीर्घ	st_rdev;
	अचिन्हित दीर्घ	st_size;
	अचिन्हित दीर्घ	st_aसमय;
	अचिन्हित दीर्घ	st_aसमय_nsec;
	अचिन्हित दीर्घ	st_mसमय;
	अचिन्हित दीर्घ	st_mसमय_nsec;
	अचिन्हित दीर्घ	st_स_समय;
	अचिन्हित दीर्घ	st_स_समय_nsec;
	अचिन्हित दीर्घ	st_blksize;
	दीर्घ		st_blocks;
	अचिन्हित दीर्घ	__unused[3];
पूर्ण;

#घोषणा STAT_HAVE_NSEC 1

काष्ठा ia64_oldstat अणु
	अचिन्हित पूर्णांक	st_dev;
	अचिन्हित पूर्णांक	st_ino;
	अचिन्हित पूर्णांक	st_mode;
	अचिन्हित पूर्णांक	st_nlink;
	अचिन्हित पूर्णांक	st_uid;
	अचिन्हित पूर्णांक	st_gid;
	अचिन्हित पूर्णांक	st_rdev;
	अचिन्हित पूर्णांक	__pad1;
	अचिन्हित दीर्घ	st_size;
	अचिन्हित दीर्घ	st_aसमय;
	अचिन्हित दीर्घ	st_mसमय;
	अचिन्हित दीर्घ	st_स_समय;
	अचिन्हित पूर्णांक	st_blksize;
	पूर्णांक		st_blocks;
	अचिन्हित पूर्णांक	__unused1;
	अचिन्हित पूर्णांक	__unused2;
पूर्ण;

#पूर्ण_अगर /* _ASM_IA64_STAT_H */
