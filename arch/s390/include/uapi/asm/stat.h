<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  S390 version
 *
 *  Derived from "include/asm-i386/stat.h"
 */

#अगर_अघोषित _S390_STAT_H
#घोषणा _S390_STAT_H

#अगर_अघोषित __s390x__
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

काष्ठा stat अणु
        अचिन्हित लघु st_dev;
        अचिन्हित लघु __pad1;
        अचिन्हित दीर्घ  st_ino;
        अचिन्हित लघु st_mode;
        अचिन्हित लघु st_nlink;
        अचिन्हित लघु st_uid;
        अचिन्हित लघु st_gid;
        अचिन्हित लघु st_rdev;
        अचिन्हित लघु __pad2;
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
 */
काष्ठा stat64 अणु
        अचिन्हित दीर्घ दीर्घ	st_dev;
        अचिन्हित पूर्णांक    __pad1;
#घोषणा STAT64_HAS_BROKEN_ST_INO        1
        अचिन्हित दीर्घ   __st_ino;
        अचिन्हित पूर्णांक    st_mode;
        अचिन्हित पूर्णांक    st_nlink;
        अचिन्हित दीर्घ   st_uid;
        अचिन्हित दीर्घ   st_gid;
        अचिन्हित दीर्घ दीर्घ	st_rdev;
        अचिन्हित पूर्णांक    __pad3;
        दीर्घ दीर्घ	st_size;
        अचिन्हित दीर्घ   st_blksize;
        अचिन्हित अक्षर   __pad4[4];
        अचिन्हित दीर्घ   __pad5;     /* future possible st_blocks high bits */
        अचिन्हित दीर्घ   st_blocks;  /* Number 512-byte blocks allocated. */
        अचिन्हित दीर्घ   st_aसमय;
        अचिन्हित दीर्घ   st_aसमय_nsec;
        अचिन्हित दीर्घ   st_mसमय;
        अचिन्हित दीर्घ   st_mसमय_nsec;
        अचिन्हित दीर्घ   st_स_समय;
        अचिन्हित दीर्घ   st_स_समय_nsec;  /* will be high 32 bits of स_समय someday */
        अचिन्हित दीर्घ दीर्घ	st_ino;
पूर्ण;

#अन्यथा /* __s390x__ */

काष्ठा stat अणु
        अचिन्हित दीर्घ  st_dev;
        अचिन्हित दीर्घ  st_ino;
        अचिन्हित दीर्घ  st_nlink;
        अचिन्हित पूर्णांक   st_mode;
        अचिन्हित पूर्णांक   st_uid;
        अचिन्हित पूर्णांक   st_gid;
        अचिन्हित पूर्णांक   __pad1;
        अचिन्हित दीर्घ  st_rdev;
        अचिन्हित दीर्घ  st_size;
        अचिन्हित दीर्घ  st_aसमय;
	अचिन्हित दीर्घ  st_aसमय_nsec;
        अचिन्हित दीर्घ  st_mसमय;
	अचिन्हित दीर्घ  st_mसमय_nsec;
        अचिन्हित दीर्घ  st_स_समय;
	अचिन्हित दीर्घ  st_स_समय_nsec;
        अचिन्हित दीर्घ  st_blksize;
        दीर्घ           st_blocks;
        अचिन्हित दीर्घ  __unused[3];
पूर्ण;

#पूर्ण_अगर /* __s390x__ */

#घोषणा STAT_HAVE_NSEC 1

#पूर्ण_अगर
