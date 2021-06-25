<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Security server पूर्णांकerface.
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 *
 */

#अगर_अघोषित _SELINUX_SECURITY_H_
#घोषणा _SELINUX_SECURITY_H_

#समावेश <linux/compiler.h>
#समावेश <linux/dcache.h>
#समावेश <linux/magic.h>
#समावेश <linux/types.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/refcount.h>
#समावेश <linux/workqueue.h>
#समावेश "flask.h"
#समावेश "policycap.h"

#घोषणा SECSID_शून्य			0x00000000 /* unspecअगरied SID */
#घोषणा SECSID_WILD			0xffffffff /* wildcard SID */
#घोषणा SECCLASS_शून्य			0x0000 /* no class */

/* Identअगरy specअगरic policy version changes */
#घोषणा POLICYDB_VERSION_BASE		15
#घोषणा POLICYDB_VERSION_BOOL		16
#घोषणा POLICYDB_VERSION_IPV6		17
#घोषणा POLICYDB_VERSION_NLCLASS	18
#घोषणा POLICYDB_VERSION_VALIDATETRANS	19
#घोषणा POLICYDB_VERSION_MLS		19
#घोषणा POLICYDB_VERSION_AVTAB		20
#घोषणा POLICYDB_VERSION_RANGETRANS	21
#घोषणा POLICYDB_VERSION_POLCAP		22
#घोषणा POLICYDB_VERSION_PERMISSIVE	23
#घोषणा POLICYDB_VERSION_BOUNDARY	24
#घोषणा POLICYDB_VERSION_खाताNAME_TRANS	25
#घोषणा POLICYDB_VERSION_ROLETRANS	26
#घोषणा POLICYDB_VERSION_NEW_OBJECT_DEFAULTS	27
#घोषणा POLICYDB_VERSION_DEFAULT_TYPE	28
#घोषणा POLICYDB_VERSION_CONSTRAINT_NAMES	29
#घोषणा POLICYDB_VERSION_XPERMS_IOCTL	30
#घोषणा POLICYDB_VERSION_INFINIBAND		31
#घोषणा POLICYDB_VERSION_GLBLUB		32
#घोषणा POLICYDB_VERSION_COMP_FTRANS	33 /* compressed filename transitions */

/* Range of policy versions we understand*/
#घोषणा POLICYDB_VERSION_MIN   POLICYDB_VERSION_BASE
#घोषणा POLICYDB_VERSION_MAX   POLICYDB_VERSION_COMP_FTRANS

/* Mask क्रम just the mount related flags */
#घोषणा SE_MNTMASK	0x0f
/* Super block security काष्ठा flags क्रम mount options */
/* BE CAREFUL, these need to be the low order bits क्रम selinux_get_mnt_opts */
#घोषणा CONTEXT_MNT	0x01
#घोषणा FSCONTEXT_MNT	0x02
#घोषणा ROOTCONTEXT_MNT	0x04
#घोषणा DEFCONTEXT_MNT	0x08
#घोषणा SBLABEL_MNT	0x10
/* Non-mount related flags */
#घोषणा SE_SBINITIALIZED	0x0100
#घोषणा SE_SBPROC		0x0200
#घोषणा SE_SBGENFS		0x0400
#घोषणा SE_SBGENFS_XATTR	0x0800

#घोषणा CONTEXT_STR	"context"
#घोषणा FSCONTEXT_STR	"fscontext"
#घोषणा ROOTCONTEXT_STR	"rootcontext"
#घोषणा DEFCONTEXT_STR	"defcontext"
#घोषणा SECLABEL_STR "seclabel"

काष्ठा netlbl_lsm_secattr;

बाह्य पूर्णांक selinux_enabled_boot;

/*
 * type_datum properties
 * available at the kernel policy version >= POLICYDB_VERSION_BOUNDARY
 */
#घोषणा TYPEDATUM_PROPERTY_PRIMARY	0x0001
#घोषणा TYPEDATUM_PROPERTY_ATTRIBUTE	0x0002

/* limitation of boundary depth  */
#घोषणा POLICYDB_BOUNDS_MAXDEPTH	4

काष्ठा selinux_avc;
काष्ठा selinux_policy;

काष्ठा selinux_state अणु
#अगर_घोषित CONFIG_SECURITY_SELINUX_DISABLE
	bool disabled;
#पूर्ण_अगर
#अगर_घोषित CONFIG_SECURITY_SELINUX_DEVELOP
	bool enक्रमcing;
#पूर्ण_अगर
	bool checkreqprot;
	bool initialized;
	bool policycap[__POLICYDB_CAPABILITY_MAX];

	काष्ठा page *status_page;
	काष्ठा mutex status_lock;

	काष्ठा selinux_avc *avc;
	काष्ठा selinux_policy __rcu *policy;
	काष्ठा mutex policy_mutex;
पूर्ण __अक्रमomize_layout;

व्योम selinux_avc_init(काष्ठा selinux_avc **avc);

बाह्य काष्ठा selinux_state selinux_state;

अटल अंतरभूत bool selinux_initialized(स्थिर काष्ठा selinux_state *state)
अणु
	/* करो a synchronized load to aव्योम race conditions */
	वापस smp_load_acquire(&state->initialized);
पूर्ण

अटल अंतरभूत व्योम selinux_mark_initialized(काष्ठा selinux_state *state)
अणु
	/* करो a synchronized ग_लिखो to aव्योम race conditions */
	smp_store_release(&state->initialized, true);
पूर्ण

#अगर_घोषित CONFIG_SECURITY_SELINUX_DEVELOP
अटल अंतरभूत bool enक्रमcing_enabled(काष्ठा selinux_state *state)
अणु
	वापस READ_ONCE(state->enक्रमcing);
पूर्ण

अटल अंतरभूत व्योम enक्रमcing_set(काष्ठा selinux_state *state, bool value)
अणु
	WRITE_ONCE(state->enक्रमcing, value);
पूर्ण
#अन्यथा
अटल अंतरभूत bool enक्रमcing_enabled(काष्ठा selinux_state *state)
अणु
	वापस true;
पूर्ण

अटल अंतरभूत व्योम enक्रमcing_set(काष्ठा selinux_state *state, bool value)
अणु
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool checkreqprot_get(स्थिर काष्ठा selinux_state *state)
अणु
	वापस READ_ONCE(state->checkreqprot);
पूर्ण

अटल अंतरभूत व्योम checkreqprot_set(काष्ठा selinux_state *state, bool value)
अणु
	WRITE_ONCE(state->checkreqprot, value);
पूर्ण

#अगर_घोषित CONFIG_SECURITY_SELINUX_DISABLE
अटल अंतरभूत bool selinux_disabled(काष्ठा selinux_state *state)
अणु
	वापस READ_ONCE(state->disabled);
पूर्ण

अटल अंतरभूत व्योम selinux_mark_disabled(काष्ठा selinux_state *state)
अणु
	WRITE_ONCE(state->disabled, true);
पूर्ण
#अन्यथा
अटल अंतरभूत bool selinux_disabled(काष्ठा selinux_state *state)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत bool selinux_policycap_netpeer(व्योम)
अणु
	काष्ठा selinux_state *state = &selinux_state;

	वापस READ_ONCE(state->policycap[POLICYDB_CAPABILITY_NETPEER]);
पूर्ण

अटल अंतरभूत bool selinux_policycap_खोलोperm(व्योम)
अणु
	काष्ठा selinux_state *state = &selinux_state;

	वापस READ_ONCE(state->policycap[POLICYDB_CAPABILITY_OPENPERM]);
पूर्ण

अटल अंतरभूत bool selinux_policycap_extsockclass(व्योम)
अणु
	काष्ठा selinux_state *state = &selinux_state;

	वापस READ_ONCE(state->policycap[POLICYDB_CAPABILITY_EXTSOCKCLASS]);
पूर्ण

अटल अंतरभूत bool selinux_policycap_alwaysnetwork(व्योम)
अणु
	काष्ठा selinux_state *state = &selinux_state;

	वापस READ_ONCE(state->policycap[POLICYDB_CAPABILITY_ALWAYSNETWORK]);
पूर्ण

अटल अंतरभूत bool selinux_policycap_cgroupseclabel(व्योम)
अणु
	काष्ठा selinux_state *state = &selinux_state;

	वापस READ_ONCE(state->policycap[POLICYDB_CAPABILITY_CGROUPSECLABEL]);
पूर्ण

अटल अंतरभूत bool selinux_policycap_nnp_nosuid_transition(व्योम)
अणु
	काष्ठा selinux_state *state = &selinux_state;

	वापस READ_ONCE(state->policycap[POLICYDB_CAPABILITY_NNP_NOSUID_TRANSITION]);
पूर्ण

अटल अंतरभूत bool selinux_policycap_genfs_seclabel_symlinks(व्योम)
अणु
	काष्ठा selinux_state *state = &selinux_state;

	वापस READ_ONCE(state->policycap[POLICYDB_CAPABILITY_GENFS_SECLABEL_SYMLINKS]);
पूर्ण

काष्ठा selinux_policy_convert_data;

काष्ठा selinux_load_state अणु
	काष्ठा selinux_policy *policy;
	काष्ठा selinux_policy_convert_data *convert_data;
पूर्ण;

पूर्णांक security_mls_enabled(काष्ठा selinux_state *state);
पूर्णांक security_load_policy(काष्ठा selinux_state *state,
			 व्योम *data, माप_प्रकार len,
			 काष्ठा selinux_load_state *load_state);
व्योम selinux_policy_commit(काष्ठा selinux_state *state,
			   काष्ठा selinux_load_state *load_state);
व्योम selinux_policy_cancel(काष्ठा selinux_state *state,
			   काष्ठा selinux_load_state *load_state);
पूर्णांक security_पढ़ो_policy(काष्ठा selinux_state *state,
			 व्योम **data, माप_प्रकार *len);
पूर्णांक security_पढ़ो_state_kernel(काष्ठा selinux_state *state,
			       व्योम **data, माप_प्रकार *len);
पूर्णांक security_policycap_supported(काष्ठा selinux_state *state,
				 अचिन्हित पूर्णांक req_cap);

#घोषणा SEL_VEC_MAX 32
काष्ठा av_decision अणु
	u32 allowed;
	u32 auditallow;
	u32 auditdeny;
	u32 seqno;
	u32 flags;
पूर्ण;

#घोषणा XPERMS_ALLOWED 1
#घोषणा XPERMS_AUDITALLOW 2
#घोषणा XPERMS_DONTAUDIT 4

#घोषणा security_xperm_set(perms, x) (perms[x >> 5] |= 1 << (x & 0x1f))
#घोषणा security_xperm_test(perms, x) (1 & (perms[x >> 5] >> (x & 0x1f)))
काष्ठा extended_perms_data अणु
	u32 p[8];
पूर्ण;

काष्ठा extended_perms_decision अणु
	u8 used;
	u8 driver;
	काष्ठा extended_perms_data *allowed;
	काष्ठा extended_perms_data *auditallow;
	काष्ठा extended_perms_data *करोntaudit;
पूर्ण;

काष्ठा extended_perms अणु
	u16 len;	/* length associated decision chain */
	काष्ठा extended_perms_data drivers; /* flag drivers that are used */
पूर्ण;

/* definitions of av_decision.flags */
#घोषणा AVD_FLAGS_PERMISSIVE	0x0001

व्योम security_compute_av(काष्ठा selinux_state *state,
			 u32 ssid, u32 tsid,
			 u16 tclass, काष्ठा av_decision *avd,
			 काष्ठा extended_perms *xperms);

व्योम security_compute_xperms_decision(काष्ठा selinux_state *state,
				      u32 ssid, u32 tsid, u16 tclass,
				      u8 driver,
				      काष्ठा extended_perms_decision *xpermd);

व्योम security_compute_av_user(काष्ठा selinux_state *state,
			      u32 ssid, u32 tsid,
			      u16 tclass, काष्ठा av_decision *avd);

पूर्णांक security_transition_sid(काष्ठा selinux_state *state,
			    u32 ssid, u32 tsid, u16 tclass,
			    स्थिर काष्ठा qstr *qstr, u32 *out_sid);

पूर्णांक security_transition_sid_user(काष्ठा selinux_state *state,
				 u32 ssid, u32 tsid, u16 tclass,
				 स्थिर अक्षर *objname, u32 *out_sid);

पूर्णांक security_member_sid(काष्ठा selinux_state *state, u32 ssid, u32 tsid,
			u16 tclass, u32 *out_sid);

पूर्णांक security_change_sid(काष्ठा selinux_state *state, u32 ssid, u32 tsid,
			u16 tclass, u32 *out_sid);

पूर्णांक security_sid_to_context(काष्ठा selinux_state *state, u32 sid,
			    अक्षर **scontext, u32 *scontext_len);

पूर्णांक security_sid_to_context_क्रमce(काष्ठा selinux_state *state,
				  u32 sid, अक्षर **scontext, u32 *scontext_len);

पूर्णांक security_sid_to_context_inval(काष्ठा selinux_state *state,
				  u32 sid, अक्षर **scontext, u32 *scontext_len);

पूर्णांक security_context_to_sid(काष्ठा selinux_state *state,
			    स्थिर अक्षर *scontext, u32 scontext_len,
			    u32 *out_sid, gfp_t gfp);

पूर्णांक security_context_str_to_sid(काष्ठा selinux_state *state,
				स्थिर अक्षर *scontext, u32 *out_sid, gfp_t gfp);

पूर्णांक security_context_to_sid_शेष(काष्ठा selinux_state *state,
				    स्थिर अक्षर *scontext, u32 scontext_len,
				    u32 *out_sid, u32 def_sid, gfp_t gfp_flags);

पूर्णांक security_context_to_sid_क्रमce(काष्ठा selinux_state *state,
				  स्थिर अक्षर *scontext, u32 scontext_len,
				  u32 *sid);

पूर्णांक security_get_user_sids(काष्ठा selinux_state *state,
			   u32 callsid, अक्षर *username,
			   u32 **sids, u32 *nel);

पूर्णांक security_port_sid(काष्ठा selinux_state *state,
		      u8 protocol, u16 port, u32 *out_sid);

पूर्णांक security_ib_pkey_sid(काष्ठा selinux_state *state,
			 u64 subnet_prefix, u16 pkey_num, u32 *out_sid);

पूर्णांक security_ib_endport_sid(काष्ठा selinux_state *state,
			    स्थिर अक्षर *dev_name, u8 port_num, u32 *out_sid);

पूर्णांक security_netअगर_sid(काष्ठा selinux_state *state,
		       अक्षर *name, u32 *अगर_sid);

पूर्णांक security_node_sid(काष्ठा selinux_state *state,
		      u16 करोमुख्य, व्योम *addr, u32 addrlen,
		      u32 *out_sid);

पूर्णांक security_validate_transition(काष्ठा selinux_state *state,
				 u32 oldsid, u32 newsid, u32 tasksid,
				 u16 tclass);

पूर्णांक security_validate_transition_user(काष्ठा selinux_state *state,
				      u32 oldsid, u32 newsid, u32 tasksid,
				      u16 tclass);

पूर्णांक security_bounded_transition(काष्ठा selinux_state *state,
				u32 oldsid, u32 newsid);

पूर्णांक security_sid_mls_copy(काष्ठा selinux_state *state,
			  u32 sid, u32 mls_sid, u32 *new_sid);

पूर्णांक security_net_peersid_resolve(काष्ठा selinux_state *state,
				 u32 nlbl_sid, u32 nlbl_type,
				 u32 xfrm_sid,
				 u32 *peer_sid);

पूर्णांक security_get_classes(काष्ठा selinux_policy *policy,
			 अक्षर ***classes, पूर्णांक *nclasses);
पूर्णांक security_get_permissions(काष्ठा selinux_policy *policy,
			     अक्षर *class, अक्षर ***perms, पूर्णांक *nperms);
पूर्णांक security_get_reject_unknown(काष्ठा selinux_state *state);
पूर्णांक security_get_allow_unknown(काष्ठा selinux_state *state);

#घोषणा SECURITY_FS_USE_XATTR		1 /* use xattr */
#घोषणा SECURITY_FS_USE_TRANS		2 /* use transition SIDs, e.g. devpts/पंचांगpfs */
#घोषणा SECURITY_FS_USE_TASK		3 /* use task SIDs, e.g. pipefs/sockfs */
#घोषणा SECURITY_FS_USE_GENFS		4 /* use the genfs support */
#घोषणा SECURITY_FS_USE_NONE		5 /* no labeling support */
#घोषणा SECURITY_FS_USE_MNTPOINT	6 /* use mountpoपूर्णांक labeling */
#घोषणा SECURITY_FS_USE_NATIVE		7 /* use native label support */
#घोषणा SECURITY_FS_USE_MAX		7 /* Highest SECURITY_FS_USE_XXX */

पूर्णांक security_fs_use(काष्ठा selinux_state *state, काष्ठा super_block *sb);

पूर्णांक security_genfs_sid(काष्ठा selinux_state *state,
		       स्थिर अक्षर *fstype, अक्षर *name, u16 sclass,
		       u32 *sid);

पूर्णांक selinux_policy_genfs_sid(काष्ठा selinux_policy *policy,
		       स्थिर अक्षर *fstype, अक्षर *name, u16 sclass,
		       u32 *sid);

#अगर_घोषित CONFIG_NETLABEL
पूर्णांक security_netlbl_secattr_to_sid(काष्ठा selinux_state *state,
				   काष्ठा netlbl_lsm_secattr *secattr,
				   u32 *sid);

पूर्णांक security_netlbl_sid_to_secattr(काष्ठा selinux_state *state,
				   u32 sid,
				   काष्ठा netlbl_lsm_secattr *secattr);
#अन्यथा
अटल अंतरभूत पूर्णांक security_netlbl_secattr_to_sid(काष्ठा selinux_state *state,
					    काष्ठा netlbl_lsm_secattr *secattr,
					    u32 *sid)
अणु
	वापस -EIDRM;
पूर्ण

अटल अंतरभूत पूर्णांक security_netlbl_sid_to_secattr(काष्ठा selinux_state *state,
					 u32 sid,
					 काष्ठा netlbl_lsm_secattr *secattr)
अणु
	वापस -ENOENT;
पूर्ण
#पूर्ण_अगर /* CONFIG_NETLABEL */

स्थिर अक्षर *security_get_initial_sid_context(u32 sid);

/*
 * status notअगरier using mmap पूर्णांकerface
 */
बाह्य काष्ठा page *selinux_kernel_status_page(काष्ठा selinux_state *state);

#घोषणा SELINUX_KERNEL_STATUS_VERSION	1
काष्ठा selinux_kernel_status अणु
	u32	version;	/* version number of the काष्ठाure */
	u32	sequence;	/* sequence number of seqlock logic */
	u32	enक्रमcing;	/* current setting of enक्रमcing mode */
	u32	policyload;	/* बार of policy reloaded */
	u32	deny_unknown;	/* current setting of deny_unknown */
	/*
	 * The version > 0 supports above members.
	 */
पूर्ण __packed;

बाह्य व्योम selinux_status_update_setenक्रमce(काष्ठा selinux_state *state,
					     पूर्णांक enक्रमcing);
बाह्य व्योम selinux_status_update_policyload(काष्ठा selinux_state *state,
					     पूर्णांक seqno);
बाह्य व्योम selinux_complete_init(व्योम);
बाह्य पूर्णांक selinux_disable(काष्ठा selinux_state *state);
बाह्य व्योम निकास_sel_fs(व्योम);
बाह्य काष्ठा path selinux_null;
बाह्य व्योम selnl_notअगरy_setenक्रमce(पूर्णांक val);
बाह्य व्योम selnl_notअगरy_policyload(u32 seqno);
बाह्य पूर्णांक selinux_nlmsg_lookup(u16 sclass, u16 nlmsg_type, u32 *perm);

बाह्य व्योम avtab_cache_init(व्योम);
बाह्य व्योम ebiपंचांगap_cache_init(व्योम);
बाह्य व्योम hashtab_cache_init(व्योम);
बाह्य पूर्णांक security_sidtab_hash_stats(काष्ठा selinux_state *state, अक्षर *page);

#पूर्ण_अगर /* _SELINUX_SECURITY_H_ */
