<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Common LSM logging functions
 * Heavily borrowed from selinux/avc.h
 *
 * Author : Etienne BASSET  <etienne.basset@ensta.org>
 *
 * All credits to : Stephen Smalley, <sds@tycho.nsa.gov>
 * All BUGS to : Etienne BASSET  <etienne.basset@ensta.org>
 */
#अगर_अघोषित _LSM_COMMON_LOGGING_
#घोषणा _LSM_COMMON_LOGGING_

#समावेश <linux/मानकघोष.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/init.h>
#समावेश <linux/audit.h>
#समावेश <linux/in6.h>
#समावेश <linux/path.h>
#समावेश <linux/key.h>
#समावेश <linux/skbuff.h>
#समावेश <rdma/ib_verbs.h>

काष्ठा lsm_network_audit अणु
	पूर्णांक netअगर;
	स्थिर काष्ठा sock *sk;
	u16 family;
	__be16 dport;
	__be16 sport;
	जोड़ अणु
		काष्ठा अणु
			__be32 daddr;
			__be32 saddr;
		पूर्ण v4;
		काष्ठा अणु
			काष्ठा in6_addr daddr;
			काष्ठा in6_addr saddr;
		पूर्ण v6;
	पूर्ण fam;
पूर्ण;

काष्ठा lsm_ioctlop_audit अणु
	काष्ठा path path;
	u16 cmd;
पूर्ण;

काष्ठा lsm_ibpkey_audit अणु
	u64	subnet_prefix;
	u16	pkey;
पूर्ण;

काष्ठा lsm_ibendport_audit अणु
	अक्षर	dev_name[IB_DEVICE_NAME_MAX];
	u8	port;
पूर्ण;

/* Auxiliary data to use in generating the audit record. */
काष्ठा common_audit_data अणु
	अक्षर type;
#घोषणा LSM_AUDIT_DATA_PATH	1
#घोषणा LSM_AUDIT_DATA_NET	2
#घोषणा LSM_AUDIT_DATA_CAP	3
#घोषणा LSM_AUDIT_DATA_IPC	4
#घोषणा LSM_AUDIT_DATA_TASK	5
#घोषणा LSM_AUDIT_DATA_KEY	6
#घोषणा LSM_AUDIT_DATA_NONE	7
#घोषणा LSM_AUDIT_DATA_KMOD	8
#घोषणा LSM_AUDIT_DATA_INODE	9
#घोषणा LSM_AUDIT_DATA_DENTRY	10
#घोषणा LSM_AUDIT_DATA_IOCTL_OP	11
#घोषणा LSM_AUDIT_DATA_खाता	12
#घोषणा LSM_AUDIT_DATA_IBPKEY	13
#घोषणा LSM_AUDIT_DATA_IBENDPORT 14
#घोषणा LSM_AUDIT_DATA_LOCKDOWN 15
#घोषणा LSM_AUDIT_DATA_NOTIFICATION 16
	जोड़ 	अणु
		काष्ठा path path;
		काष्ठा dentry *dentry;
		काष्ठा inode *inode;
		काष्ठा lsm_network_audit *net;
		पूर्णांक cap;
		पूर्णांक ipc_id;
		काष्ठा task_काष्ठा *tsk;
#अगर_घोषित CONFIG_KEYS
		काष्ठा अणु
			key_serial_t key;
			अक्षर *key_desc;
		पूर्ण key_काष्ठा;
#पूर्ण_अगर
		अक्षर *kmod_name;
		काष्ठा lsm_ioctlop_audit *op;
		काष्ठा file *file;
		काष्ठा lsm_ibpkey_audit *ibpkey;
		काष्ठा lsm_ibendport_audit *ibendport;
		पूर्णांक reason;
	पूर्ण u;
	/* this जोड़ contains LSM specअगरic data */
	जोड़ अणु
#अगर_घोषित CONFIG_SECURITY_SMACK
		काष्ठा smack_audit_data *smack_audit_data;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECURITY_SELINUX
		काष्ठा selinux_audit_data *selinux_audit_data;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECURITY_APPARMOR
		काष्ठा apparmor_audit_data *apparmor_audit_data;
#पूर्ण_अगर
	पूर्ण; /* per LSM data poपूर्णांकer जोड़ */
पूर्ण;

#घोषणा v4info fam.v4
#घोषणा v6info fam.v6

पूर्णांक ipv4_skb_to_auditdata(काष्ठा sk_buff *skb,
		काष्ठा common_audit_data *ad, u8 *proto);

पूर्णांक ipv6_skb_to_auditdata(काष्ठा sk_buff *skb,
		काष्ठा common_audit_data *ad, u8 *proto);

व्योम common_lsm_audit(काष्ठा common_audit_data *a,
	व्योम (*pre_audit)(काष्ठा audit_buffer *, व्योम *),
	व्योम (*post_audit)(काष्ठा audit_buffer *, व्योम *));

#पूर्ण_अगर
