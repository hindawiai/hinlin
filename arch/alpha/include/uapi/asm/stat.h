<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ALPHA_STAT_H
#घोषणा _ALPHA_STAT_H

काष्ठा stat अणु
	अचिन्हित पूर्णांक	st_dev;
	अचिन्हित पूर्णांक	st_ino;
	अचिन्हित पूर्णांक	st_mode;
	अचिन्हित पूर्णांक	st_nlink;
	अचिन्हित पूर्णांक	st_uid;
	अचिन्हित पूर्णांक	st_gid;
	अचिन्हित पूर्णांक	st_rdev;
	दीर्घ		st_size;
	अचिन्हित दीर्घ	st_aसमय;
	अचिन्हित दीर्घ	st_mसमय;
	अचिन्हित दीर्घ	st_स_समय;
	अचिन्हित पूर्णांक	st_blksize;
	अचिन्हित पूर्णांक	st_blocks;
	अचिन्हित पूर्णांक	st_flags;
	अचिन्हित पूर्णांक	st_gen;
पूर्ण;

/* The stat64 काष्ठाure increases the size of dev_t, blkcnt_t, adds
   nanosecond resolution बार, and padding क्रम expansion.  */

काष्ठा stat64 अणु
	अचिन्हित दीर्घ	st_dev;
	अचिन्हित दीर्घ	st_ino;
	अचिन्हित दीर्घ	st_rdev;
	दीर्घ		st_size;
	अचिन्हित दीर्घ	st_blocks;

	अचिन्हित पूर्णांक	st_mode;
	अचिन्हित पूर्णांक	st_uid;
	अचिन्हित पूर्णांक	st_gid;
	अचिन्हित पूर्णांक	st_blksize;
	अचिन्हित पूर्णांक	st_nlink;
	अचिन्हित पूर्णांक	__pad0;

	अचिन्हित दीर्घ	st_aसमय;
	अचिन्हित दीर्घ 	st_aसमय_nsec; 
	अचिन्हित दीर्घ	st_mसमय;
	अचिन्हित दीर्घ	st_mसमय_nsec;
	अचिन्हित दीर्घ	st_स_समय;
	अचिन्हित दीर्घ   st_स_समय_nsec;
  	दीर्घ		__unused[3];
पूर्ण;

#पूर्ण_अगर
