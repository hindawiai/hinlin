<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASMARM_STAT_H
#घोषणा _ASMARM_STAT_H

काष्ठा __old_kernel_stat अणु
	अचिन्हित लघु st_dev;
	अचिन्हित लघु st_ino;
	अचिन्हित लघु st_mode;
	अचिन्हित लघु st_nlink;
	अचिन्हित लघु st_uid;
	अचिन्हित लघु st_gid;
	अचिन्हित लघु st_rdev;
	अचिन्हित दीर्घ  st_size;
	अचिन्हित दीर्घ  st_aसमय;
	अचिन्हित दीर्घ  st_mसमय;
	अचिन्हित दीर्घ  st_स_समय;
पूर्ण;

#घोषणा STAT_HAVE_NSEC 

काष्ठा stat अणु
#अगर defined(__ARMEB__)
	अचिन्हित लघु st_dev;
	अचिन्हित लघु __pad1;
#अन्यथा
	अचिन्हित दीर्घ  st_dev;
#पूर्ण_अगर
	अचिन्हित दीर्घ  st_ino;
	अचिन्हित लघु st_mode;
	अचिन्हित लघु st_nlink;
	अचिन्हित लघु st_uid;
	अचिन्हित लघु st_gid;
#अगर defined(__ARMEB__)
	अचिन्हित लघु st_rdev;
	अचिन्हित लघु __pad2;
#अन्यथा
	अचिन्हित दीर्घ  st_rdev;
#पूर्ण_अगर
	अचिन्हित दीर्घ  st_size;
	अचिन्हित दीर्घ  st_blksize;
	अचिन्हित दीर्घ  st_blocks;
	अचिन्हित दीर्घ  st_aसमय;
	अचिन्हित दीर्घ  st_aसमय_nsec;
	अचिन्हित दीर्घ  st_mसमय;
	अचिन्हित दीर्घ  st_mसमय_nsec;
	अचिन्हित दीर्घ  st_स_समय;
	अचिन्हित दीर्घ  st_स_समय_nsec;
	अचिन्हित दीर्घ  __unused4;
	अचिन्हित दीर्घ  __unused5;
पूर्ण;

/* This matches काष्ठा stat64 in glibc2.1, hence the असलolutely
 * insane amounts of padding around dev_t's.
 * Note: The kernel zero's the padded region because glibc might पढ़ो them
 * in the hope that the kernel has stretched to using larger sizes.
 */
काष्ठा stat64 अणु
	अचिन्हित दीर्घ दीर्घ	st_dev;
	अचिन्हित अक्षर   __pad0[4];

#घोषणा STAT64_HAS_BROKEN_ST_INO	1
	अचिन्हित दीर्घ	__st_ino;
	अचिन्हित पूर्णांक	st_mode;
	अचिन्हित पूर्णांक	st_nlink;

	अचिन्हित दीर्घ	st_uid;
	अचिन्हित दीर्घ	st_gid;

	अचिन्हित दीर्घ दीर्घ	st_rdev;
	अचिन्हित अक्षर   __pad3[4];

	दीर्घ दीर्घ	st_size;
	अचिन्हित दीर्घ	st_blksize;
	अचिन्हित दीर्घ दीर्घ st_blocks;	/* Number 512-byte blocks allocated. */

	अचिन्हित दीर्घ	st_aसमय;
	अचिन्हित दीर्घ	st_aसमय_nsec;

	अचिन्हित दीर्घ	st_mसमय;
	अचिन्हित दीर्घ	st_mसमय_nsec;

	अचिन्हित दीर्घ	st_स_समय;
	अचिन्हित दीर्घ	st_स_समय_nsec;

	अचिन्हित दीर्घ दीर्घ	st_ino;
पूर्ण;

#पूर्ण_अगर
