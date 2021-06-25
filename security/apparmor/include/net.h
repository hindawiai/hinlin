<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * AppArmor security module
 *
 * This file contains AppArmor network mediation definitions.
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2017 Canonical Ltd.
 */

#अगर_अघोषित __AA_NET_H
#घोषणा __AA_NET_H

#समावेश <net/sock.h>
#समावेश <linux/path.h>

#समावेश "apparmorfs.h"
#समावेश "label.h"
#समावेश "perms.h"
#समावेश "policy.h"

#घोषणा AA_MAY_SEND		AA_MAY_WRITE
#घोषणा AA_MAY_RECEIVE		AA_MAY_READ

#घोषणा AA_MAY_SHUTDOWN		AA_MAY_DELETE

#घोषणा AA_MAY_CONNECT		AA_MAY_OPEN
#घोषणा AA_MAY_ACCEPT		0x00100000

#घोषणा AA_MAY_BIND		0x00200000
#घोषणा AA_MAY_LISTEN		0x00400000

#घोषणा AA_MAY_SETOPT		0x01000000
#घोषणा AA_MAY_GETOPT		0x02000000

#घोषणा NET_PERMS_MASK (AA_MAY_SEND | AA_MAY_RECEIVE | AA_MAY_CREATE |    \
			AA_MAY_SHUTDOWN | AA_MAY_BIND | AA_MAY_LISTEN |	  \
			AA_MAY_CONNECT | AA_MAY_ACCEPT | AA_MAY_SETATTR | \
			AA_MAY_GETATTR | AA_MAY_SETOPT | AA_MAY_GETOPT)

#घोषणा NET_FS_PERMS (AA_MAY_SEND | AA_MAY_RECEIVE | AA_MAY_CREATE |	\
		      AA_MAY_SHUTDOWN | AA_MAY_CONNECT | AA_MAY_RENAME |\
		      AA_MAY_SETATTR | AA_MAY_GETATTR | AA_MAY_CHMOD |	\
		      AA_MAY_CHOWN | AA_MAY_CHGRP | AA_MAY_LOCK |	\
		      AA_MAY_MPROT)

#घोषणा NET_PEER_MASK (AA_MAY_SEND | AA_MAY_RECEIVE | AA_MAY_CONNECT |	\
		       AA_MAY_ACCEPT)
काष्ठा aa_sk_ctx अणु
	काष्ठा aa_label *label;
	काष्ठा aa_label *peer;
पूर्ण;

#घोषणा SK_CTX(X) ((X)->sk_security)
#घोषणा SOCK_ctx(X) SOCK_INODE(X)->i_security
#घोषणा DEFINE_AUDIT_NET(NAME, OP, SK, F, T, P)				  \
	काष्ठा lsm_network_audit NAME ## _net = अणु .sk = (SK),		  \
						  .family = (F)पूर्ण;	  \
	DEFINE_AUDIT_DATA(NAME,						  \
			  ((SK) && (F) != AF_UNIX) ? LSM_AUDIT_DATA_NET : \
						     LSM_AUDIT_DATA_NONE, \
			  OP);						  \
	NAME.u.net = &(NAME ## _net);					  \
	aad(&NAME)->net.type = (T);					  \
	aad(&NAME)->net.protocol = (P)

#घोषणा DEFINE_AUDIT_SK(NAME, OP, SK)					\
	DEFINE_AUDIT_NET(NAME, OP, SK, (SK)->sk_family, (SK)->sk_type,	\
			 (SK)->sk_protocol)


#घोषणा af_select(FAMILY, FN, DEF_FN)		\
(अणु						\
	पूर्णांक __e;				\
	चयन ((FAMILY)) अणु			\
	शेष:				\
		__e = DEF_FN;			\
	पूर्ण					\
	__e;					\
पूर्ण)

काष्ठा aa_secmark अणु
	u8 audit;
	u8 deny;
	u32 secid;
	अक्षर *label;
पूर्ण;

बाह्य काष्ठा aa_sfs_entry aa_sfs_entry_network[];

व्योम audit_net_cb(काष्ठा audit_buffer *ab, व्योम *va);
पूर्णांक aa_profile_af_perm(काष्ठा aa_profile *profile, काष्ठा common_audit_data *sa,
		       u32 request, u16 family, पूर्णांक type);
पूर्णांक aa_af_perm(काष्ठा aa_label *label, स्थिर अक्षर *op, u32 request, u16 family,
	       पूर्णांक type, पूर्णांक protocol);
अटल अंतरभूत पूर्णांक aa_profile_af_sk_perm(काष्ठा aa_profile *profile,
					काष्ठा common_audit_data *sa,
					u32 request,
					काष्ठा sock *sk)
अणु
	वापस aa_profile_af_perm(profile, sa, request, sk->sk_family,
				  sk->sk_type);
पूर्ण
पूर्णांक aa_sk_perm(स्थिर अक्षर *op, u32 request, काष्ठा sock *sk);

पूर्णांक aa_sock_file_perm(काष्ठा aa_label *label, स्थिर अक्षर *op, u32 request,
		      काष्ठा socket *sock);

पूर्णांक apparmor_secmark_check(काष्ठा aa_label *label, अक्षर *op, u32 request,
			   u32 secid, स्थिर काष्ठा sock *sk);

#पूर्ण_अगर /* __AA_NET_H */
