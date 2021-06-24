<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __SPARC_STAT_H
#घोषणा __SPARC_STAT_H

#समावेश <linux/types.h>

#अगर defined(__sparc__) && defined(__arch64__)
/* 64 bit sparc */
काष्ठा stat अणु
	अचिन्हित पूर्णांक st_dev;
	ino_t   st_ino;
	mode_t  st_mode;
	लघु   st_nlink;
	uid_t   st_uid;
	gid_t   st_gid;
	अचिन्हित पूर्णांक st_rdev;
	दीर्घ    st_size;
	दीर्घ    st_aसमय;
	दीर्घ    st_mसमय;
	दीर्घ    st_स_समय;
	दीर्घ    st_blksize;
	दीर्घ    st_blocks;
	अचिन्हित दीर्घ  __unused4[2];
पूर्ण;

काष्ठा stat64 अणु
	अचिन्हित दीर्घ	st_dev;
	अचिन्हित दीर्घ	st_ino;
	अचिन्हित दीर्घ	st_nlink;

	अचिन्हित पूर्णांक	st_mode;
	अचिन्हित पूर्णांक	st_uid;
	अचिन्हित पूर्णांक	st_gid;
	अचिन्हित पूर्णांक	__pad0;

	अचिन्हित दीर्घ	st_rdev;
	दीर्घ		st_size;
	दीर्घ		st_blksize;
	दीर्घ		st_blocks;

	अचिन्हित दीर्घ	st_aसमय;
	अचिन्हित दीर्घ	st_aसमय_nsec;
	अचिन्हित दीर्घ	st_mसमय;
	अचिन्हित दीर्घ	st_mसमय_nsec;
	अचिन्हित दीर्घ	st_स_समय;
	अचिन्हित दीर्घ	st_स_समय_nsec;
	दीर्घ		__unused[3];
पूर्ण;

#अन्यथा
/* 32 bit sparc */
काष्ठा stat अणु
	अचिन्हित लघु	st_dev;
	ino_t		st_ino;
	mode_t		st_mode;
	लघु		st_nlink;
	अचिन्हित लघु	st_uid;
	अचिन्हित लघु	st_gid;
	अचिन्हित लघु	st_rdev;
	दीर्घ		st_size;
	दीर्घ		st_aसमय;
	अचिन्हित दीर्घ	st_aसमय_nsec;
	दीर्घ		st_mसमय;
	अचिन्हित दीर्घ	st_mसमय_nsec;
	दीर्घ		st_स_समय;
	अचिन्हित दीर्घ	st_स_समय_nsec;
	दीर्घ		st_blksize;
	दीर्घ		st_blocks;
	अचिन्हित दीर्घ	__unused4[2];
पूर्ण;

#घोषणा STAT_HAVE_NSEC 1

काष्ठा stat64 अणु
	अचिन्हित दीर्घ दीर्घ st_dev;

	अचिन्हित दीर्घ दीर्घ st_ino;

	अचिन्हित पूर्णांक	st_mode;
	अचिन्हित पूर्णांक	st_nlink;

	अचिन्हित पूर्णांक	st_uid;
	अचिन्हित पूर्णांक	st_gid;

	अचिन्हित दीर्घ दीर्घ st_rdev;

	अचिन्हित अक्षर	__pad3[8];

	दीर्घ दीर्घ	st_size;
	अचिन्हित पूर्णांक	st_blksize;

	अचिन्हित अक्षर	__pad4[8];
	अचिन्हित पूर्णांक	st_blocks;

	अचिन्हित पूर्णांक	st_aसमय;
	अचिन्हित पूर्णांक	st_aसमय_nsec;

	अचिन्हित पूर्णांक	st_mसमय;
	अचिन्हित पूर्णांक	st_mसमय_nsec;

	अचिन्हित पूर्णांक	st_स_समय;
	अचिन्हित पूर्णांक	st_स_समय_nsec;

	अचिन्हित पूर्णांक	__unused4;
	अचिन्हित पूर्णांक	__unused5;
पूर्ण;
#पूर्ण_अगर /* defined(__sparc__) && defined(__arch64__) */
#पूर्ण_अगर /* __SPARC_STAT_H */
