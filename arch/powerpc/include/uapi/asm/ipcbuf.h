<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
#अगर_अघोषित _ASM_POWERPC_IPCBUF_H
#घोषणा _ASM_POWERPC_IPCBUF_H

/*
 * The ipc64_perm काष्ठाure क्रम the घातerpc is identical to
 * kern_ipc_perm as we have always had 32-bit UIDs and GIDs in the
 * kernel.  Note extra padding because this काष्ठाure is passed back
 * and क्रमth between kernel and user space.  Pad space is left क्रम:
 *	- 1 32-bit value to fill up क्रम 8-byte alignment
 *	- 2 miscellaneous 64-bit values
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version
 * 2 of the License, or (at your option) any later version.
 */

#समावेश <linux/types.h>

काष्ठा ipc64_perm
अणु
	__kernel_key_t	key;
	__kernel_uid_t	uid;
	__kernel_gid_t	gid;
	__kernel_uid_t	cuid;
	__kernel_gid_t	cgid;
	__kernel_mode_t	mode;
	अचिन्हित पूर्णांक	seq;
	अचिन्हित पूर्णांक	__pad1;
	अचिन्हित दीर्घ दीर्घ __unused1;
	अचिन्हित दीर्घ दीर्घ __unused2;
पूर्ण;

#पूर्ण_अगर /* _ASM_POWERPC_IPCBUF_H */
