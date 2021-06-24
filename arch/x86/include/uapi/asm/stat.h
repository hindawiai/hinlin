<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _ASM_X86_STAT_H
#घोषणा _ASM_X86_STAT_H

#समावेश <यंत्र/posix_types.h>

#घोषणा STAT_HAVE_NSEC 1

#अगर_घोषित __i386__
काष्ठा stat अणु
	अचिन्हित दीर्घ  st_dev;
	अचिन्हित दीर्घ  st_ino;
	अचिन्हित लघु st_mode;
	अचिन्हित लघु st_nlink;
	अचिन्हित लघु st_uid;
	अचिन्हित लघु st_gid;
	अचिन्हित दीर्घ  st_rdev;
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

/* We करोn't need to स_रखो the whole thing just to initialize the padding */
#घोषणा INIT_STRUCT_STAT_PADDING(st) करो अणु	\
	st.__unused4 = 0;			\
	st.__unused5 = 0;			\
पूर्ण जबतक (0)

#घोषणा STAT64_HAS_BROKEN_ST_INO	1

/* This matches काष्ठा stat64 in glibc2.1, hence the असलolutely
 * insane amounts of padding around dev_t's.
 */
काष्ठा stat64 अणु
	अचिन्हित दीर्घ दीर्घ	st_dev;
	अचिन्हित अक्षर	__pad0[4];

	अचिन्हित दीर्घ	__st_ino;

	अचिन्हित पूर्णांक	st_mode;
	अचिन्हित पूर्णांक	st_nlink;

	अचिन्हित दीर्घ	st_uid;
	अचिन्हित दीर्घ	st_gid;

	अचिन्हित दीर्घ दीर्घ	st_rdev;
	अचिन्हित अक्षर	__pad3[4];

	दीर्घ दीर्घ	st_size;
	अचिन्हित दीर्घ	st_blksize;

	/* Number 512-byte blocks allocated. */
	अचिन्हित दीर्घ दीर्घ	st_blocks;

	अचिन्हित दीर्घ	st_aसमय;
	अचिन्हित दीर्घ	st_aसमय_nsec;

	अचिन्हित दीर्घ	st_mसमय;
	अचिन्हित पूर्णांक	st_mसमय_nsec;

	अचिन्हित दीर्घ	st_स_समय;
	अचिन्हित दीर्घ	st_स_समय_nsec;

	अचिन्हित दीर्घ दीर्घ	st_ino;
पूर्ण;

/* We करोn't need to स_रखो the whole thing just to initialize the padding */
#घोषणा INIT_STRUCT_STAT64_PADDING(st) करो अणु		\
	स_रखो(&st.__pad0, 0, माप(st.__pad0));	\
	स_रखो(&st.__pad3, 0, माप(st.__pad3));	\
पूर्ण जबतक (0)

#अन्यथा /* __i386__ */

काष्ठा stat अणु
	__kernel_uदीर्घ_t	st_dev;
	__kernel_uदीर्घ_t	st_ino;
	__kernel_uदीर्घ_t	st_nlink;

	अचिन्हित पूर्णांक		st_mode;
	अचिन्हित पूर्णांक		st_uid;
	अचिन्हित पूर्णांक		st_gid;
	अचिन्हित पूर्णांक		__pad0;
	__kernel_uदीर्घ_t	st_rdev;
	__kernel_दीर्घ_t		st_size;
	__kernel_दीर्घ_t		st_blksize;
	__kernel_दीर्घ_t		st_blocks;	/* Number 512-byte blocks allocated. */

	__kernel_uदीर्घ_t	st_aसमय;
	__kernel_uदीर्घ_t	st_aसमय_nsec;
	__kernel_uदीर्घ_t	st_mसमय;
	__kernel_uदीर्घ_t	st_mसमय_nsec;
	__kernel_uदीर्घ_t	st_स_समय;
	__kernel_uदीर्घ_t	st_स_समय_nsec;
	__kernel_दीर्घ_t		__unused[3];
पूर्ण;

/* We करोn't need to स_रखो the whole thing just to initialize the padding */
#घोषणा INIT_STRUCT_STAT_PADDING(st) करो अणु	\
	st.__pad0 = 0;				\
	st.__unused[0] = 0;			\
	st.__unused[1] = 0;			\
	st.__unused[2] = 0;			\
पूर्ण जबतक (0)

#पूर्ण_अगर

/* क्रम 32bit emulation and 32 bit kernels */
काष्ठा __old_kernel_stat अणु
	अचिन्हित लघु st_dev;
	अचिन्हित लघु st_ino;
	अचिन्हित लघु st_mode;
	अचिन्हित लघु st_nlink;
	अचिन्हित लघु st_uid;
	अचिन्हित लघु st_gid;
	अचिन्हित लघु st_rdev;
#अगर_घोषित __i386__
	अचिन्हित दीर्घ  st_size;
	अचिन्हित दीर्घ  st_aसमय;
	अचिन्हित दीर्घ  st_mसमय;
	अचिन्हित दीर्घ  st_स_समय;
#अन्यथा
	अचिन्हित पूर्णांक  st_size;
	अचिन्हित पूर्णांक  st_aसमय;
	अचिन्हित पूर्णांक  st_mसमय;
	अचिन्हित पूर्णांक  st_स_समय;
#पूर्ण_अगर
पूर्ण;

#पूर्ण_अगर /* _ASM_X86_STAT_H */
