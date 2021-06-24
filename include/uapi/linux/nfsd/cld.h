<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 * Upcall description क्रम nfsdcld communication
 *
 * Copyright (c) 2012 Red Hat, Inc.
 * Author(s): Jeff Layton <jlayton@redhat.com>
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License क्रम more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 *  Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#अगर_अघोषित _NFSD_CLD_H
#घोषणा _NFSD_CLD_H

#समावेश <linux/types.h>

/* latest upcall version available */
#घोषणा CLD_UPCALL_VERSION 2

/* defined by RFC3530 */
#घोषणा NFS4_OPAQUE_LIMIT 1024

#अगर_अघोषित SHA256_DIGEST_SIZE
#घोषणा SHA256_DIGEST_SIZE      32
#पूर्ण_अगर

क्रमागत cld_command अणु
	Cld_Create,		/* create a record क्रम this cm_id */
	Cld_Remove,		/* हटाओ record of this cm_id */
	Cld_Check,		/* is this cm_id allowed? */
	Cld_GraceDone,		/* grace period is complete */
	Cld_GraceStart,		/* grace start (upload client records) */
	Cld_GetVersion,		/* query max supported upcall version */
पूर्ण;

/* representation of दीर्घ-क्रमm NFSv4 client ID */
काष्ठा cld_name अणु
	__u16		cn_len;				/* length of cm_id */
	अचिन्हित अक्षर	cn_id[NFS4_OPAQUE_LIMIT];	/* client-provided */
पूर्ण __attribute__((packed));

/* sha256 hash of the kerberos principal */
काष्ठा cld_princhash अणु
	__u8		cp_len;				/* length of cp_data */
	अचिन्हित अक्षर	cp_data[SHA256_DIGEST_SIZE];	/* hash of principal */
पूर्ण __attribute__((packed));

काष्ठा cld_clntinfo अणु
	काष्ठा cld_name		cc_name;
	काष्ठा cld_princhash	cc_princhash;
पूर्ण __attribute__((packed));

/* message काष्ठा क्रम communication with userspace */
काष्ठा cld_msg अणु
	__u8		cm_vers;		/* upcall version */
	__u8		cm_cmd;			/* upcall command */
	__s16		cm_status;		/* वापस code */
	__u32		cm_xid;			/* transaction id */
	जोड़ अणु
		__s64		cm_graceसमय;	/* grace period start समय */
		काष्ठा cld_name	cm_name;
		__u8		cm_version;	/* क्रम getting max version */
	पूर्ण __attribute__((packed)) cm_u;
पूर्ण __attribute__((packed));

/* version 2 message can include hash of kerberos principal */
काष्ठा cld_msg_v2 अणु
	__u8		cm_vers;		/* upcall version */
	__u8		cm_cmd;			/* upcall command */
	__s16		cm_status;		/* वापस code */
	__u32		cm_xid;			/* transaction id */
	जोड़ अणु
		काष्ठा cld_name	cm_name;
		__u8		cm_version;	/* क्रम getting max version */
		काष्ठा cld_clntinfo cm_clntinfo; /* name & princ hash */
	पूर्ण __attribute__((packed)) cm_u;
पूर्ण __attribute__((packed));

काष्ठा cld_msg_hdr अणु
	__u8		cm_vers;		/* upcall version */
	__u8		cm_cmd;			/* upcall command */
	__s16		cm_status;		/* वापस code */
	__u32		cm_xid;			/* transaction id */
पूर्ण __attribute__((packed));

#पूर्ण_अगर /* !_NFSD_CLD_H */
