<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित _ASM_POWERPC_STAT_H
#घोषणा _ASM_POWERPC_STAT_H
/*
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */
#समावेश <linux/types.h>

#घोषणा STAT_HAVE_NSEC 1

#अगर_अघोषित __घातerpc64__
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
#पूर्ण_अगर /* !__घातerpc64__ */

काष्ठा stat अणु
	अचिन्हित दीर्घ	st_dev;
	ino_t		st_ino;
#अगर_घोषित __घातerpc64__
	अचिन्हित दीर्घ	st_nlink;
	mode_t		st_mode;
#अन्यथा
	mode_t		st_mode;
	अचिन्हित लघु	st_nlink;
#पूर्ण_अगर
	uid_t		st_uid;
	gid_t		st_gid;
	अचिन्हित दीर्घ	st_rdev;
	दीर्घ		st_size;
	अचिन्हित दीर्घ	st_blksize;
	अचिन्हित दीर्घ	st_blocks;
	अचिन्हित दीर्घ	st_aसमय;
	अचिन्हित दीर्घ	st_aसमय_nsec;
	अचिन्हित दीर्घ	st_mसमय;
	अचिन्हित दीर्घ	st_mसमय_nsec;
	अचिन्हित दीर्घ	st_स_समय;
	अचिन्हित दीर्घ	st_स_समय_nsec;
	अचिन्हित दीर्घ	__unused4;
	अचिन्हित दीर्घ	__unused5;
#अगर_घोषित __घातerpc64__
	अचिन्हित दीर्घ	__unused6;
#पूर्ण_अगर
पूर्ण;

/* This matches काष्ठा stat64 in glibc2.1. Only used क्रम 32 bit. */
काष्ठा stat64 अणु
	अचिन्हित दीर्घ दीर्घ st_dev;		/* Device.  */
	अचिन्हित दीर्घ दीर्घ st_ino;		/* File serial number.  */
	अचिन्हित पूर्णांक	st_mode;	/* File mode.  */
	अचिन्हित पूर्णांक	st_nlink;	/* Link count.  */
	अचिन्हित पूर्णांक	st_uid;		/* User ID of the file's owner.  */
	अचिन्हित पूर्णांक	st_gid;		/* Group ID of the file's group. */
	अचिन्हित दीर्घ दीर्घ st_rdev;	/* Device number, अगर device.  */
	अचिन्हित लघु	__pad2;
	दीर्घ दीर्घ	st_size;	/* Size of file, in bytes.  */
	पूर्णांक		st_blksize;	/* Optimal block size क्रम I/O.  */
	दीर्घ दीर्घ	st_blocks;	/* Number 512-byte blocks allocated. */
	पूर्णांक		st_aसमय;	/* Time of last access.  */
	अचिन्हित पूर्णांक	st_aसमय_nsec;
	पूर्णांक		st_mसमय;	/* Time of last modअगरication.  */
	अचिन्हित पूर्णांक	st_mसमय_nsec;
	पूर्णांक		st_स_समय;	/* Time of last status change.  */
	अचिन्हित पूर्णांक	st_स_समय_nsec;
	अचिन्हित पूर्णांक	__unused4;
	अचिन्हित पूर्णांक	__unused5;
पूर्ण;

#पूर्ण_अगर /* _ASM_POWERPC_STAT_H */
