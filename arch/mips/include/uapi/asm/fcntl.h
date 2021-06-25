<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 96, 97, 98, 99, 2003, 05 Ralf Baechle
 */
#अगर_अघोषित _UAPI_ASM_FCNTL_H
#घोषणा _UAPI_ASM_FCNTL_H

#समावेश <यंत्र/sgidefs.h>

#घोषणा O_APPEND	0x0008
#घोषणा O_DSYNC		0x0010	/* used to be O_SYNC, see below */
#घोषणा O_NONBLOCK	0x0080
#घोषणा O_CREAT		0x0100	/* not fcntl */
#घोषणा O_TRUNC		0x0200	/* not fcntl */
#घोषणा O_EXCL		0x0400	/* not fcntl */
#घोषणा O_NOCTTY	0x0800	/* not fcntl */
#घोषणा FASYNC		0x1000	/* fcntl, क्रम BSD compatibility */
#घोषणा O_LARGEखाता	0x2000	/* allow large file खोलोs */
/*
 * Beक्रमe Linux 2.6.33 only O_DSYNC semantics were implemented, but using
 * the O_SYNC flag.  We जारी to use the existing numerical value
 * क्रम O_DSYNC semantics now, but using the correct symbolic name क्रम it.
 * This new value is used to request true Posix O_SYNC semantics.  It is
 * defined in this strange way to make sure applications compiled against
 * new headers get at least O_DSYNC semantics on older kernels.
 *
 * This has the nice side-effect that we can simply test क्रम O_DSYNC
 * wherever we करो not care अगर O_DSYNC or O_SYNC is used.
 *
 * Note: __O_SYNC must never be used directly.
 */
#घोषणा __O_SYNC	0x4000
#घोषणा O_SYNC		(__O_SYNC|O_DSYNC)
#घोषणा O_सूचीECT	0x8000	/* direct disk access hपूर्णांक */

#घोषणा F_GETLK		14
#घोषणा F_SETLK		6
#घोषणा F_SETLKW	7

#घोषणा F_SETOWN	24	/*  क्रम sockets. */
#घोषणा F_GETOWN	23	/*  क्रम sockets. */

#अगर_अघोषित __mips64
#घोषणा F_GETLK64	33	/*  using 'struct flock64' */
#घोषणा F_SETLK64	34
#घोषणा F_SETLKW64	35
#पूर्ण_अगर

/*
 * The flavours of काष्ठा flock.  "struct flock" is the ABI compliant
 * variant.  Finally काष्ठा flock64 is the LFS variant of काष्ठा flock.	 As
 * a historic accident and inconsistence with the ABI definition it करोesn't
 * contain all the same fields as काष्ठा flock.
 */

#अगर _MIPS_SIM != _MIPS_SIM_ABI64

#समावेश <linux/types.h>

काष्ठा flock अणु
	लघु	l_type;
	लघु	l_whence;
	__kernel_off_t	l_start;
	__kernel_off_t	l_len;
	दीर्घ	l_sysid;
	__kernel_pid_t l_pid;
	दीर्घ	pad[4];
पूर्ण;

#घोषणा HAVE_ARCH_STRUCT_FLOCK

#पूर्ण_अगर /* _MIPS_SIM == _MIPS_SIM_ABI32 */

#समावेश <यंत्र-generic/fcntl.h>

#पूर्ण_अगर /* _UAPI_ASM_FCNTL_H */
