<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2007 Casey Schaufler <हालy@schaufler-ca.com>
 *
 * Author:
 *      Casey Schaufler <हालy@schaufler-ca.com>
 */

#अगर_अघोषित _SECURITY_SMACK_H
#घोषणा _SECURITY_SMACK_H

#समावेश <linux/capability.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/lsm_hooks.h>
#समावेश <linux/in.h>
#अगर IS_ENABLED(CONFIG_IPV6)
#समावेश <linux/in6.h>
#पूर्ण_अगर /* CONFIG_IPV6 */
#समावेश <net/netlabel.h>
#समावेश <linux/list.h>
#समावेश <linux/rculist.h>
#समावेश <linux/lsm_audit.h>
#समावेश <linux/msg.h>

/*
 * Use IPv6 port labeling अगर IPv6 is enabled and secmarks
 * are not being used.
 */
#अगर IS_ENABLED(CONFIG_IPV6) && !defined(CONFIG_SECURITY_SMACK_NETFILTER)
#घोषणा SMACK_IPV6_PORT_LABELING 1
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6) && defined(CONFIG_SECURITY_SMACK_NETFILTER)
#घोषणा SMACK_IPV6_SECMARK_LABELING 1
#पूर्ण_अगर

/*
 * Smack labels were limited to 23 अक्षरacters क्रम a दीर्घ समय.
 */
#घोषणा SMK_LABELLEN	24
#घोषणा SMK_LONGLABEL	256

/*
 * This is the repository क्रम labels seen so that it is
 * not necessary to keep allocating tiny chuncks of memory
 * and so that they can be shared.
 *
 * Labels are never modअगरied in place. Anyसमय a label
 * is imported (e.g. xattrset on a file) the list is checked
 * क्रम it and it is added अगर it करोesn't exist. The address
 * is passed out in either हाल. Entries are added, but
 * never deleted.
 *
 * Since labels are hanging around anyway it करोesn't
 * hurt to मुख्यtain a secid क्रम those awkward situations
 * where kernel components that ought to use LSM independent
 * पूर्णांकerfaces करोn't. The secid should go away when all of
 * these components have been repaired.
 *
 * The cipso value associated with the label माला_लो stored here, too.
 *
 * Keep the access rules क्रम this subject label here so that
 * the entire set of rules करोes not need to be examined every
 * समय.
 */
काष्ठा smack_known अणु
	काष्ठा list_head		list;
	काष्ठा hlist_node		smk_hashed;
	अक्षर				*smk_known;
	u32				smk_secid;
	काष्ठा netlbl_lsm_secattr	smk_netlabel;	/* on wire labels */
	काष्ठा list_head		smk_rules;	/* access rules */
	काष्ठा mutex			smk_rules_lock;	/* lock क्रम rules */
पूर्ण;

/*
 * Maximum number of bytes क्रम the levels in a CIPSO IP option.
 * Why 23? CIPSO is स्थिरrained to 30, so a 32 byte buffer is
 * bigger than can be used, and 24 is the next lower multiple
 * of 8, and there are too many issues अगर there isn't space set
 * aside क्रम the terminating null byte.
 */
#घोषणा SMK_CIPSOLEN	24

काष्ठा superblock_smack अणु
	काष्ठा smack_known	*smk_root;
	काष्ठा smack_known	*smk_न्यूनमान;
	काष्ठा smack_known	*smk_hat;
	काष्ठा smack_known	*smk_शेष;
	पूर्णांक			smk_flags;
पूर्ण;

/*
 * Superblock flags
 */
#घोषणा SMK_SB_INITIALIZED	0x01
#घोषणा SMK_SB_UNTRUSTED	0x02

काष्ठा socket_smack अणु
	काष्ठा smack_known	*smk_out;	/* outbound label */
	काष्ठा smack_known	*smk_in;	/* inbound label */
	काष्ठा smack_known	*smk_packet;	/* TCP peer label */
	पूर्णांक			smk_state;	/* netlabel socket states */
पूर्ण;
#घोषणा	SMK_NETLBL_UNSET	0
#घोषणा	SMK_NETLBL_UNLABELED	1
#घोषणा	SMK_NETLBL_LABELED	2
#घोषणा	SMK_NETLBL_REQSKB	3

/*
 * Inode smack data
 */
काष्ठा inode_smack अणु
	काष्ठा smack_known	*smk_inode;	/* label of the fso */
	काष्ठा smack_known	*smk_task;	/* label of the task */
	काष्ठा smack_known	*smk_mmap;	/* label of the mmap करोमुख्य */
	पूर्णांक			smk_flags;	/* smack inode flags */
पूर्ण;

काष्ठा task_smack अणु
	काष्ठा smack_known	*smk_task;	/* label क्रम access control */
	काष्ठा smack_known	*smk_विभाजनed;	/* label when विभाजनed */
	काष्ठा list_head	smk_rules;	/* per task access rules */
	काष्ठा mutex		smk_rules_lock;	/* lock क्रम the rules */
	काष्ठा list_head	smk_relabel;	/* transit allowed labels */
पूर्ण;

#घोषणा	SMK_INODE_INSTANT	0x01	/* inode is instantiated */
#घोषणा	SMK_INODE_TRANSMUTE	0x02	/* directory is transmuting */
#घोषणा	SMK_INODE_CHANGED	0x04	/* smack was transmuted */
#घोषणा	SMK_INODE_IMPURE	0x08	/* involved in an impure transaction */

/*
 * A label access rule.
 */
काष्ठा smack_rule अणु
	काष्ठा list_head	list;
	काष्ठा smack_known	*smk_subject;
	काष्ठा smack_known	*smk_object;
	पूर्णांक			smk_access;
पूर्ण;

/*
 * An entry in the table identअगरying IPv4 hosts.
 */
काष्ठा smk_net4addr अणु
	काष्ठा list_head	list;
	काष्ठा in_addr		smk_host;	/* network address */
	काष्ठा in_addr		smk_mask;	/* network mask */
	पूर्णांक			smk_masks;	/* mask size */
	काष्ठा smack_known	*smk_label;	/* label */
पूर्ण;

/*
 * An entry in the table identअगरying IPv6 hosts.
 */
काष्ठा smk_net6addr अणु
	काष्ठा list_head	list;
	काष्ठा in6_addr		smk_host;	/* network address */
	काष्ठा in6_addr		smk_mask;	/* network mask */
	पूर्णांक			smk_masks;	/* mask size */
	काष्ठा smack_known	*smk_label;	/* label */
पूर्ण;

/*
 * An entry in the table identअगरying ports.
 */
काष्ठा smk_port_label अणु
	काष्ठा list_head	list;
	काष्ठा sock		*smk_sock;	/* socket initialized on */
	अचिन्हित लघु		smk_port;	/* the port number */
	काष्ठा smack_known	*smk_in;	/* inbound label */
	काष्ठा smack_known	*smk_out;	/* outgoing label */
	लघु			smk_sock_type;	/* Socket type */
	लघु			smk_can_reuse;
पूर्ण;

काष्ठा smack_known_list_elem अणु
	काष्ठा list_head	list;
	काष्ठा smack_known	*smk_label;
पूर्ण;

/* Super block security काष्ठा flags क्रम mount options */
#घोषणा FSDEFAULT_MNT	0x01
#घोषणा FSFLOOR_MNT	0x02
#घोषणा FSHAT_MNT	0x04
#घोषणा FSROOT_MNT	0x08
#घोषणा FSTRANS_MNT	0x10

#घोषणा NUM_SMK_MNT_OPTS	5

क्रमागत अणु
	Opt_error = -1,
	Opt_fsशेष = 0,
	Opt_fsन्यूनमान = 1,
	Opt_fshat = 2,
	Opt_fsroot = 3,
	Opt_fstransmute = 4,
पूर्ण;

#घोषणा SMACK_DELETE_OPTION	"-DELETE"
#घोषणा SMACK_CIPSO_OPTION 	"-CIPSO"

/*
 * CIPSO शेषs.
 */
#घोषणा SMACK_CIPSO_DOI_DEFAULT		3	/* Historical */
#घोषणा SMACK_CIPSO_DOI_INVALID		-1	/* Not a DOI */
#घोषणा SMACK_CIPSO_सूचीECT_DEFAULT	250	/* Arbitrary */
#घोषणा SMACK_CIPSO_MAPPED_DEFAULT	251	/* Also arbitrary */
#घोषणा SMACK_CIPSO_MAXLEVEL            255     /* CIPSO 2.2 standard */
/*
 * CIPSO 2.2 standard is 239, but Smack wants to use the
 * categories in a काष्ठाured way that limits the value to
 * the bits in 23 bytes, hence the unusual number.
 */
#घोषणा SMACK_CIPSO_MAXCATNUM           184     /* 23 * 8 */

/*
 * Ptrace rules
 */
#घोषणा SMACK_PTRACE_DEFAULT	0
#घोषणा SMACK_PTRACE_EXACT	1
#घोषणा SMACK_PTRACE_DRACONIAN	2
#घोषणा SMACK_PTRACE_MAX	SMACK_PTRACE_DRACONIAN

/*
 * Flags क्रम untraditional access modes.
 * It shouldn't be necessary to aव्योम conflicts with definitions
 * in fs.h, but करो so anyway.
 */
#घोषणा MAY_TRANSMUTE	0x00001000	/* Controls directory labeling */
#घोषणा MAY_LOCK	0x00002000	/* Locks should be ग_लिखोs, but ... */
#घोषणा MAY_BRINGUP	0x00004000	/* Report use of this rule */

/*
 * The policy क्रम delivering संकेतs is configurable.
 * It is usually "write", but can be "append".
 */
#अगर_घोषित CONFIG_SECURITY_SMACK_APPEND_SIGNALS
#घोषणा MAY_DELIVER	MAY_APPEND	/* Signal delivery requires append */
#अन्यथा
#घोषणा MAY_DELIVER	MAY_WRITE	/* Signal delivery requires ग_लिखो */
#पूर्ण_अगर

#घोषणा SMACK_BRINGUP_ALLOW		1	/* Allow bringup mode */
#घोषणा SMACK_UNCONFINED_SUBJECT	2	/* Allow unconfined label */
#घोषणा SMACK_UNCONFINED_OBJECT		3	/* Allow unconfined label */

/*
 * Just to make the common हालs easier to deal with
 */
#घोषणा MAY_ANYREAD	(MAY_READ | MAY_EXEC)
#घोषणा MAY_READWRITE	(MAY_READ | MAY_WRITE)
#घोषणा MAY_NOT		0

/*
 * Number of access types used by Smack (rwxatlb)
 */
#घोषणा SMK_NUM_ACCESS_TYPE 7

/* SMACK data */
काष्ठा smack_audit_data अणु
	स्थिर अक्षर *function;
	अक्षर *subject;
	अक्षर *object;
	अक्षर *request;
	पूर्णांक result;
पूर्ण;

/*
 * Smack audit data; is empty अगर CONFIG_AUDIT not set
 * to save some stack
 */
काष्ठा smk_audit_info अणु
#अगर_घोषित CONFIG_AUDIT
	काष्ठा common_audit_data a;
	काष्ठा smack_audit_data sad;
#पूर्ण_अगर
पूर्ण;

/*
 * These functions are in smack_access.c
 */
पूर्णांक smk_access_entry(अक्षर *, अक्षर *, काष्ठा list_head *);
पूर्णांक smk_access(काष्ठा smack_known *, काष्ठा smack_known *,
	       पूर्णांक, काष्ठा smk_audit_info *);
पूर्णांक smk_tskacc(काष्ठा task_smack *, काष्ठा smack_known *,
	       u32, काष्ठा smk_audit_info *);
पूर्णांक smk_curacc(काष्ठा smack_known *, u32, काष्ठा smk_audit_info *);
काष्ठा smack_known *smack_from_secid(स्थिर u32);
अक्षर *smk_parse_smack(स्थिर अक्षर *string, पूर्णांक len);
पूर्णांक smk_netlbl_mls(पूर्णांक, अक्षर *, काष्ठा netlbl_lsm_secattr *, पूर्णांक);
काष्ठा smack_known *smk_import_entry(स्थिर अक्षर *, पूर्णांक);
व्योम smk_insert_entry(काष्ठा smack_known *skp);
काष्ठा smack_known *smk_find_entry(स्थिर अक्षर *);
bool smack_privileged(पूर्णांक cap);
bool smack_privileged_cred(पूर्णांक cap, स्थिर काष्ठा cred *cred);
व्योम smk_destroy_label_list(काष्ठा list_head *list);
पूर्णांक smack_populate_secattr(काष्ठा smack_known *skp);

/*
 * Shared data.
 */
बाह्य पूर्णांक smack_enabled;
बाह्य पूर्णांक smack_cipso_direct;
बाह्य पूर्णांक smack_cipso_mapped;
बाह्य काष्ठा smack_known *smack_net_ambient;
बाह्य काष्ठा smack_known *smack_syslog_label;
#अगर_घोषित CONFIG_SECURITY_SMACK_BRINGUP
बाह्य काष्ठा smack_known *smack_unconfined;
#पूर्ण_अगर
बाह्य पूर्णांक smack_ptrace_rule;
बाह्य काष्ठा lsm_blob_sizes smack_blob_sizes;

बाह्य काष्ठा smack_known smack_known_न्यूनमान;
बाह्य काष्ठा smack_known smack_known_hat;
बाह्य काष्ठा smack_known smack_known_huh;
बाह्य काष्ठा smack_known smack_known_star;
बाह्य काष्ठा smack_known smack_known_web;

बाह्य काष्ठा mutex	smack_known_lock;
बाह्य काष्ठा list_head smack_known_list;
बाह्य काष्ठा list_head smk_net4addr_list;
बाह्य काष्ठा list_head smk_net6addr_list;

बाह्य काष्ठा mutex     smack_onlycap_lock;
बाह्य काष्ठा list_head smack_onlycap_list;

#घोषणा SMACK_HASH_SLOTS 16
बाह्य काष्ठा hlist_head smack_known_hash[SMACK_HASH_SLOTS];
बाह्य काष्ठा kmem_cache *smack_rule_cache;

अटल अंतरभूत काष्ठा task_smack *smack_cred(स्थिर काष्ठा cred *cred)
अणु
	वापस cred->security + smack_blob_sizes.lbs_cred;
पूर्ण

अटल अंतरभूत काष्ठा smack_known **smack_file(स्थिर काष्ठा file *file)
अणु
	वापस (काष्ठा smack_known **)(file->f_security +
				       smack_blob_sizes.lbs_file);
पूर्ण

अटल अंतरभूत काष्ठा inode_smack *smack_inode(स्थिर काष्ठा inode *inode)
अणु
	वापस inode->i_security + smack_blob_sizes.lbs_inode;
पूर्ण

अटल अंतरभूत काष्ठा smack_known **smack_msg_msg(स्थिर काष्ठा msg_msg *msg)
अणु
	वापस msg->security + smack_blob_sizes.lbs_msg_msg;
पूर्ण

अटल अंतरभूत काष्ठा smack_known **smack_ipc(स्थिर काष्ठा kern_ipc_perm *ipc)
अणु
	वापस ipc->security + smack_blob_sizes.lbs_ipc;
पूर्ण

अटल अंतरभूत काष्ठा superblock_smack *smack_superblock(
					स्थिर काष्ठा super_block *superblock)
अणु
	वापस superblock->s_security + smack_blob_sizes.lbs_superblock;
पूर्ण

/*
 * Is the directory transmuting?
 */
अटल अंतरभूत पूर्णांक smk_inode_transmutable(स्थिर काष्ठा inode *isp)
अणु
	काष्ठा inode_smack *sip = smack_inode(isp);
	वापस (sip->smk_flags & SMK_INODE_TRANSMUTE) != 0;
पूर्ण

/*
 * Present a poपूर्णांकer to the smack label entry in an inode blob.
 */
अटल अंतरभूत काष्ठा smack_known *smk_of_inode(स्थिर काष्ठा inode *isp)
अणु
	काष्ठा inode_smack *sip = smack_inode(isp);
	वापस sip->smk_inode;
पूर्ण

/*
 * Present a poपूर्णांकer to the smack label entry in an task blob.
 */
अटल अंतरभूत काष्ठा smack_known *smk_of_task(स्थिर काष्ठा task_smack *tsp)
अणु
	वापस tsp->smk_task;
पूर्ण

अटल अंतरभूत काष्ठा smack_known *smk_of_task_काष्ठा_subj(
						स्थिर काष्ठा task_काष्ठा *t)
अणु
	काष्ठा smack_known *skp;
	स्थिर काष्ठा cred *cred;

	rcu_पढ़ो_lock();

	cred = rcu_dereference(t->cred);
	skp = smk_of_task(smack_cred(cred));

	rcu_पढ़ो_unlock();

	वापस skp;
पूर्ण

अटल अंतरभूत काष्ठा smack_known *smk_of_task_काष्ठा_obj(
						स्थिर काष्ठा task_काष्ठा *t)
अणु
	काष्ठा smack_known *skp;
	स्थिर काष्ठा cred *cred;

	rcu_पढ़ो_lock();

	cred = __task_cred(t);
	skp = smk_of_task(smack_cred(cred));

	rcu_पढ़ो_unlock();

	वापस skp;
पूर्ण

/*
 * Present a poपूर्णांकer to the विभाजनed smack label entry in an task blob.
 */
अटल अंतरभूत काष्ठा smack_known *smk_of_विभाजनed(स्थिर काष्ठा task_smack *tsp)
अणु
	वापस tsp->smk_विभाजनed;
पूर्ण

/*
 * Present a poपूर्णांकer to the smack label in the current task blob.
 */
अटल अंतरभूत काष्ठा smack_known *smk_of_current(व्योम)
अणु
	वापस smk_of_task(smack_cred(current_cred()));
पूर्ण

/*
 * logging functions
 */
#घोषणा SMACK_AUDIT_DENIED 0x1
#घोषणा SMACK_AUDIT_ACCEPT 0x2
बाह्य पूर्णांक log_policy;

व्योम smack_log(अक्षर *subject_label, अक्षर *object_label,
		पूर्णांक request,
		पूर्णांक result, काष्ठा smk_audit_info *auditdata);

#अगर_घोषित CONFIG_AUDIT

/*
 * some अंतरभूत functions to set up audit data
 * they करो nothing अगर CONFIG_AUDIT is not set
 *
 */
अटल अंतरभूत व्योम smk_ad_init(काष्ठा smk_audit_info *a, स्थिर अक्षर *func,
			       अक्षर type)
अणु
	स_रखो(&a->sad, 0, माप(a->sad));
	a->a.type = type;
	a->a.smack_audit_data = &a->sad;
	a->a.smack_audit_data->function = func;
पूर्ण

अटल अंतरभूत व्योम smk_ad_init_net(काष्ठा smk_audit_info *a, स्थिर अक्षर *func,
				   अक्षर type, काष्ठा lsm_network_audit *net)
अणु
	smk_ad_init(a, func, type);
	स_रखो(net, 0, माप(*net));
	a->a.u.net = net;
पूर्ण

अटल अंतरभूत व्योम smk_ad_setfield_u_tsk(काष्ठा smk_audit_info *a,
					 काष्ठा task_काष्ठा *t)
अणु
	a->a.u.tsk = t;
पूर्ण
अटल अंतरभूत व्योम smk_ad_setfield_u_fs_path_dentry(काष्ठा smk_audit_info *a,
						    काष्ठा dentry *d)
अणु
	a->a.u.dentry = d;
पूर्ण
अटल अंतरभूत व्योम smk_ad_setfield_u_fs_inode(काष्ठा smk_audit_info *a,
					      काष्ठा inode *i)
अणु
	a->a.u.inode = i;
पूर्ण
अटल अंतरभूत व्योम smk_ad_setfield_u_fs_path(काष्ठा smk_audit_info *a,
					     काष्ठा path p)
अणु
	a->a.u.path = p;
पूर्ण
अटल अंतरभूत व्योम smk_ad_setfield_u_net_sk(काष्ठा smk_audit_info *a,
					    काष्ठा sock *sk)
अणु
	a->a.u.net->sk = sk;
पूर्ण

#अन्यथा /* no AUDIT */

अटल अंतरभूत व्योम smk_ad_init(काष्ठा smk_audit_info *a, स्थिर अक्षर *func,
			       अक्षर type)
अणु
पूर्ण
अटल अंतरभूत व्योम smk_ad_setfield_u_tsk(काष्ठा smk_audit_info *a,
					 काष्ठा task_काष्ठा *t)
अणु
पूर्ण
अटल अंतरभूत व्योम smk_ad_setfield_u_fs_path_dentry(काष्ठा smk_audit_info *a,
						    काष्ठा dentry *d)
अणु
पूर्ण
अटल अंतरभूत व्योम smk_ad_setfield_u_fs_inode(काष्ठा smk_audit_info *a,
					      काष्ठा inode *i)
अणु
पूर्ण
अटल अंतरभूत व्योम smk_ad_setfield_u_fs_path(काष्ठा smk_audit_info *a,
					     काष्ठा path p)
अणु
पूर्ण
अटल अंतरभूत व्योम smk_ad_setfield_u_net_sk(काष्ठा smk_audit_info *a,
					    काष्ठा sock *sk)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर  /* _SECURITY_SMACK_H */
