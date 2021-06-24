<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * अगर_alg: User-space algorithm पूर्णांकerface
 *
 * Copyright (c) 2010 Herbert Xu <herbert@gonकरोr.apana.org.au>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the Free
 * Software Foundation; either version 2 of the License, or (at your option)
 * any later version.
 *
 */

#अगर_अघोषित _LINUX_IF_ALG_H
#घोषणा _LINUX_IF_ALG_H

#समावेश <linux/types.h>

काष्ठा sockaddr_alg अणु
	__u16	salg_family;
	__u8	salg_type[14];
	__u32	salg_feat;
	__u32	salg_mask;
	__u8	salg_name[64];
पूर्ण;

/*
 * Linux v4.12 and later हटाओd the 64-byte limit on salg_name[]; it's now an
 * arbitrary-length field.  We had to keep the original काष्ठा above क्रम source
 * compatibility with existing userspace programs, though.  Use the new काष्ठा
 * below अगर support क्रम very दीर्घ algorithm names is needed.  To करो this,
 * allocate 'sizeof(struct sockaddr_alg_new) + strlen(algname) + 1' bytes, and
 * copy algname (including the null terminator) पूर्णांकo salg_name.
 */
काष्ठा sockaddr_alg_new अणु
	__u16	salg_family;
	__u8	salg_type[14];
	__u32	salg_feat;
	__u32	salg_mask;
	__u8	salg_name[];
पूर्ण;

काष्ठा af_alg_iv अणु
	__u32	ivlen;
	__u8	iv[0];
पूर्ण;

/* Socket options */
#घोषणा ALG_SET_KEY			1
#घोषणा ALG_SET_IV			2
#घोषणा ALG_SET_OP			3
#घोषणा ALG_SET_AEAD_ASSOCLEN		4
#घोषणा ALG_SET_AEAD_AUTHSIZE		5
#घोषणा ALG_SET_DRBG_ENTROPY		6

/* Operations */
#घोषणा ALG_OP_DECRYPT			0
#घोषणा ALG_OP_ENCRYPT			1

#पूर्ण_अगर	/* _LINUX_IF_ALG_H */
