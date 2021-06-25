<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  NSA Security-Enhanced Linux (SELinux) security module
 *
 *  This file contains the SELinux security data काष्ठाures क्रम kernel objects.
 *
 *  Author(s):  Stephen Smalley, <sds@tycho.nsa.gov>
 *		Chris Vance, <cvance@nai.com>
 *		Wayne Salamon, <wsalamon@nai.com>
 *		James Morris <jmorris@redhat.com>
 *
 *  Copyright (C) 2001,2002 Networks Associates Technology, Inc.
 *  Copyright (C) 2003 Red Hat, Inc., James Morris <jmorris@redhat.com>
 *  Copyright (C) 2016 Mellanox Technologies
 */
#अगर_अघोषित _SELINUX_OBJSEC_H_
#घोषणा _SELINUX_OBJSEC_H_

#समावेश <linux/list.h>
#समावेश <linux/sched.h>
#समावेश <linux/fs.h>
#समावेश <linux/binfmts.h>
#समावेश <linux/in.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/lsm_hooks.h>
#समावेश <linux/msg.h>
#समावेश <net/net_namespace.h>
#समावेश "flask.h"
#समावेश "avc.h"

काष्ठा task_security_काष्ठा अणु
	u32 osid;		/* SID prior to last execve */
	u32 sid;		/* current SID */
	u32 exec_sid;		/* exec SID */
	u32 create_sid;		/* fscreate SID */
	u32 keycreate_sid;	/* keycreate SID */
	u32 sockcreate_sid;	/* fscreate SID */
पूर्ण __अक्रमomize_layout;

क्रमागत label_initialized अणु
	LABEL_INVALID,		/* invalid or not initialized */
	LABEL_INITIALIZED,	/* initialized */
	LABEL_PENDING
पूर्ण;

काष्ठा inode_security_काष्ठा अणु
	काष्ठा inode *inode;	/* back poपूर्णांकer to inode object */
	काष्ठा list_head list;	/* list of inode_security_काष्ठा */
	u32 task_sid;		/* SID of creating task */
	u32 sid;		/* SID of this object */
	u16 sclass;		/* security class of this object */
	अचिन्हित अक्षर initialized;	/* initialization flag */
	spinlock_t lock;
पूर्ण;

काष्ठा file_security_काष्ठा अणु
	u32 sid;		/* SID of खोलो file description */
	u32 fown_sid;		/* SID of file owner (क्रम SIGIO) */
	u32 isid;		/* SID of inode at the समय of file खोलो */
	u32 pseqno;		/* Policy seqno at the समय of file खोलो */
पूर्ण;

काष्ठा superblock_security_काष्ठा अणु
	u32 sid;			/* SID of file प्रणाली superblock */
	u32 def_sid;			/* शेष SID क्रम labeling */
	u32 mntpoपूर्णांक_sid;		/* SECURITY_FS_USE_MNTPOINT context क्रम files */
	अचिन्हित लघु behavior;	/* labeling behavior */
	अचिन्हित लघु flags;		/* which mount options were specअगरied */
	काष्ठा mutex lock;
	काष्ठा list_head isec_head;
	spinlock_t isec_lock;
पूर्ण;

काष्ठा msg_security_काष्ठा अणु
	u32 sid;	/* SID of message */
पूर्ण;

काष्ठा ipc_security_काष्ठा अणु
	u16 sclass;	/* security class of this object */
	u32 sid;	/* SID of IPC resource */
पूर्ण;

काष्ठा netअगर_security_काष्ठा अणु
	काष्ठा net *ns;			/* network namespace */
	पूर्णांक अगरindex;			/* device index */
	u32 sid;			/* SID क्रम this पूर्णांकerface */
पूर्ण;

काष्ठा netnode_security_काष्ठा अणु
	जोड़ अणु
		__be32 ipv4;		/* IPv4 node address */
		काष्ठा in6_addr ipv6;	/* IPv6 node address */
	पूर्ण addr;
	u32 sid;			/* SID क्रम this node */
	u16 family;			/* address family */
पूर्ण;

काष्ठा netport_security_काष्ठा अणु
	u32 sid;			/* SID क्रम this node */
	u16 port;			/* port number */
	u8 protocol;			/* transport protocol */
पूर्ण;

काष्ठा sk_security_काष्ठा अणु
#अगर_घोषित CONFIG_NETLABEL
	क्रमागत अणु				/* NetLabel state */
		NLBL_UNSET = 0,
		NLBL_REQUIRE,
		NLBL_LABELED,
		NLBL_REQSKB,
		NLBL_CONNLABELED,
	पूर्ण nlbl_state;
	काष्ठा netlbl_lsm_secattr *nlbl_secattr; /* NetLabel sec attributes */
#पूर्ण_अगर
	u32 sid;			/* SID of this object */
	u32 peer_sid;			/* SID of peer */
	u16 sclass;			/* sock security class */
	क्रमागत अणु				/* SCTP association state */
		SCTP_ASSOC_UNSET = 0,
		SCTP_ASSOC_SET,
	पूर्ण sctp_assoc_state;
पूर्ण;

काष्ठा tun_security_काष्ठा अणु
	u32 sid;			/* SID क्रम the tun device sockets */
पूर्ण;

काष्ठा key_security_काष्ठा अणु
	u32 sid;	/* SID of key */
पूर्ण;

काष्ठा ib_security_काष्ठा अणु
	u32 sid;        /* SID of the queue pair or MAD agent */
पूर्ण;

काष्ठा pkey_security_काष्ठा अणु
	u64	subnet_prefix; /* Port subnet prefix */
	u16	pkey;	/* PKey number */
	u32	sid;	/* SID of pkey */
पूर्ण;

काष्ठा bpf_security_काष्ठा अणु
	u32 sid;  /* SID of bpf obj creator */
पूर्ण;

काष्ठा perf_event_security_काष्ठा अणु
	u32 sid;  /* SID of perf_event obj creator */
पूर्ण;

बाह्य काष्ठा lsm_blob_sizes selinux_blob_sizes;
अटल अंतरभूत काष्ठा task_security_काष्ठा *selinux_cred(स्थिर काष्ठा cred *cred)
अणु
	वापस cred->security + selinux_blob_sizes.lbs_cred;
पूर्ण

अटल अंतरभूत काष्ठा file_security_काष्ठा *selinux_file(स्थिर काष्ठा file *file)
अणु
	वापस file->f_security + selinux_blob_sizes.lbs_file;
पूर्ण

अटल अंतरभूत काष्ठा inode_security_काष्ठा *selinux_inode(
						स्थिर काष्ठा inode *inode)
अणु
	अगर (unlikely(!inode->i_security))
		वापस शून्य;
	वापस inode->i_security + selinux_blob_sizes.lbs_inode;
पूर्ण

अटल अंतरभूत काष्ठा msg_security_काष्ठा *selinux_msg_msg(
						स्थिर काष्ठा msg_msg *msg_msg)
अणु
	वापस msg_msg->security + selinux_blob_sizes.lbs_msg_msg;
पूर्ण

अटल अंतरभूत काष्ठा ipc_security_काष्ठा *selinux_ipc(
						स्थिर काष्ठा kern_ipc_perm *ipc)
अणु
	वापस ipc->security + selinux_blob_sizes.lbs_ipc;
पूर्ण

/*
 * get the subjective security ID of the current task
 */
अटल अंतरभूत u32 current_sid(व्योम)
अणु
	स्थिर काष्ठा task_security_काष्ठा *tsec = selinux_cred(current_cred());

	वापस tsec->sid;
पूर्ण

अटल अंतरभूत काष्ठा superblock_security_काष्ठा *selinux_superblock(
					स्थिर काष्ठा super_block *superblock)
अणु
	वापस superblock->s_security + selinux_blob_sizes.lbs_superblock;
पूर्ण

#पूर्ण_अगर /* _SELINUX_OBJSEC_H_ */
