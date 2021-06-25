<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * include/यंत्र-xtensa/ipcbuf.h
 *
 * The ipc64_perm काष्ठाure क्रम the Xtensa architecture.
 * Note extra padding because this काष्ठाure is passed back and क्रमth
 * between kernel and user space.
 *
 * Copyright (C) 2001 - 2005 Tensilica Inc.
 */

#अगर_अघोषित _XTENSA_IPCBUF_H
#घोषणा _XTENSA_IPCBUF_H

#समावेश <linux/posix_types.h>

/*
 * Pad space is left क्रम:
 * - 32-bit mode_t and seq
 * - 2 miscellaneous 32-bit values
 *
 * This file is subject to the terms and conditions of the GNU General
 * Public License.  See the file "COPYING" in the मुख्य directory of
 * this archive क्रम more details.
 */

काष्ठा ipc64_perm
अणु
	__kernel_key_t		key;
	__kernel_uid32_t	uid;
	__kernel_gid32_t	gid;
	__kernel_uid32_t	cuid;
	__kernel_gid32_t	cgid;
	__kernel_mode_t		mode;
	अचिन्हित दीर्घ		seq;
	अचिन्हित दीर्घ		__unused1;
	अचिन्हित दीर्घ		__unused2;
पूर्ण;

#पूर्ण_अगर /* _XTENSA_IPCBUF_H */
