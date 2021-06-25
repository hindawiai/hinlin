<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __ASM_GENERIC_STAT_H
#घोषणा __ASM_GENERIC_STAT_H

/*
 * Everybody माला_लो this wrong and has to stick with it क्रम all
 * eternity. Hopefully, this version माला_लो used by new architectures
 * so they करोn't fall पूर्णांकo the same traps.
 *
 * stat64 is copied from घातerpc64, with explicit padding added.
 * stat is the same काष्ठाure layout on 64-bit, without the 'long long'
 * types.
 *
 * By convention, 64 bit architectures use the stat पूर्णांकerface, जबतक
 * 32 bit architectures use the stat64 पूर्णांकerface. Note that we करोn't
 * provide an __old_kernel_stat here, which new architecture should
 * not have to start with.
 */

#समावेश <यंत्र/bitsperदीर्घ.h>

#घोषणा STAT_HAVE_NSEC 1

काष्ठा stat अणु
	अचिन्हित दीर्घ	st_dev;		/* Device.  */
	अचिन्हित दीर्घ	st_ino;		/* File serial number.  */
	अचिन्हित पूर्णांक	st_mode;	/* File mode.  */
	अचिन्हित पूर्णांक	st_nlink;	/* Link count.  */
	अचिन्हित पूर्णांक	st_uid;		/* User ID of the file's owner.  */
	अचिन्हित पूर्णांक	st_gid;		/* Group ID of the file's group. */
	अचिन्हित दीर्घ	st_rdev;	/* Device number, अगर device.  */
	अचिन्हित दीर्घ	__pad1;
	दीर्घ		st_size;	/* Size of file, in bytes.  */
	पूर्णांक		st_blksize;	/* Optimal block size क्रम I/O.  */
	पूर्णांक		__pad2;
	दीर्घ		st_blocks;	/* Number 512-byte blocks allocated. */
	दीर्घ		st_aसमय;	/* Time of last access.  */
	अचिन्हित दीर्घ	st_aसमय_nsec;
	दीर्घ		st_mसमय;	/* Time of last modअगरication.  */
	अचिन्हित दीर्घ	st_mसमय_nsec;
	दीर्घ		st_स_समय;	/* Time of last status change.  */
	अचिन्हित दीर्घ	st_स_समय_nsec;
	अचिन्हित पूर्णांक	__unused4;
	अचिन्हित पूर्णांक	__unused5;
पूर्ण;

/* This matches काष्ठा stat64 in glibc2.1. Only used क्रम 32 bit. */
#अगर __BITS_PER_LONG != 64 || defined(__ARCH_WANT_STAT64)
काष्ठा stat64 अणु
	अचिन्हित दीर्घ दीर्घ st_dev;	/* Device.  */
	अचिन्हित दीर्घ दीर्घ st_ino;	/* File serial number.  */
	अचिन्हित पूर्णांक	st_mode;	/* File mode.  */
	अचिन्हित पूर्णांक	st_nlink;	/* Link count.  */
	अचिन्हित पूर्णांक	st_uid;		/* User ID of the file's owner.  */
	अचिन्हित पूर्णांक	st_gid;		/* Group ID of the file's group. */
	अचिन्हित दीर्घ दीर्घ st_rdev;	/* Device number, अगर device.  */
	अचिन्हित दीर्घ दीर्घ __pad1;
	दीर्घ दीर्घ	st_size;	/* Size of file, in bytes.  */
	पूर्णांक		st_blksize;	/* Optimal block size क्रम I/O.  */
	पूर्णांक		__pad2;
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
#पूर्ण_अगर

#पूर्ण_अगर /* __ASM_GENERIC_STAT_H */
