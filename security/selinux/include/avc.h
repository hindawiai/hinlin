<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Access vector cache पूर्णांकerface क्रम object managers.
 *
 * Author : Stephen Smalley, <sds@tycho.nsa.gov>
 */
#अगर_अघोषित _SELINUX_AVC_H_
#घोषणा _SELINUX_AVC_H_

#समावेश <linux/मानकघोष.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/init.h>
#समावेश <linux/audit.h>
#समावेश <linux/lsm_audit.h>
#समावेश <linux/in6.h>
#समावेश "flask.h"
#समावेश "av_permissions.h"
#समावेश "security.h"

/*
 * An entry in the AVC.
 */
काष्ठा avc_entry;

काष्ठा task_काष्ठा;
काष्ठा inode;
काष्ठा sock;
काष्ठा sk_buff;

/*
 * AVC statistics
 */
काष्ठा avc_cache_stats अणु
	अचिन्हित पूर्णांक lookups;
	अचिन्हित पूर्णांक misses;
	अचिन्हित पूर्णांक allocations;
	अचिन्हित पूर्णांक reclaims;
	अचिन्हित पूर्णांक मुक्तs;
पूर्ण;

/*
 * We only need this data after we have decided to send an audit message.
 */
काष्ठा selinux_audit_data अणु
	u32 ssid;
	u32 tsid;
	u16 tclass;
	u32 requested;
	u32 audited;
	u32 denied;
	पूर्णांक result;
	काष्ठा selinux_state *state;
पूर्ण;

/*
 * AVC operations
 */

व्योम __init avc_init(व्योम);

अटल अंतरभूत u32 avc_audit_required(u32 requested,
			      काष्ठा av_decision *avd,
			      पूर्णांक result,
			      u32 auditdeny,
			      u32 *deniedp)
अणु
	u32 denied, audited;
	denied = requested & ~avd->allowed;
	अगर (unlikely(denied)) अणु
		audited = denied & avd->auditdeny;
		/*
		 * auditdeny is TRICKY!  Setting a bit in
		 * this field means that ANY denials should NOT be audited अगर
		 * the policy contains an explicit करोntaudit rule क्रम that
		 * permission.  Take notice that this is unrelated to the
		 * actual permissions that were denied.  As an example lets
		 * assume:
		 *
		 * denied == READ
		 * avd.auditdeny & ACCESS == 0 (not set means explicit rule)
		 * auditdeny & ACCESS == 1
		 *
		 * We will NOT audit the denial even though the denied
		 * permission was READ and the auditdeny checks were क्रम
		 * ACCESS
		 */
		अगर (auditdeny && !(auditdeny & avd->auditdeny))
			audited = 0;
	पूर्ण अन्यथा अगर (result)
		audited = denied = requested;
	अन्यथा
		audited = requested & avd->auditallow;
	*deniedp = denied;
	वापस audited;
पूर्ण

पूर्णांक slow_avc_audit(काष्ठा selinux_state *state,
		   u32 ssid, u32 tsid, u16 tclass,
		   u32 requested, u32 audited, u32 denied, पूर्णांक result,
		   काष्ठा common_audit_data *a);

/**
 * avc_audit - Audit the granting or denial of permissions.
 * @ssid: source security identअगरier
 * @tsid: target security identअगरier
 * @tclass: target security class
 * @requested: requested permissions
 * @avd: access vector decisions
 * @result: result from avc_has_perm_noaudit
 * @a:  auxiliary audit data
 * @flags: VFS walk flags
 *
 * Audit the granting or denial of permissions in accordance
 * with the policy.  This function is typically called by
 * avc_has_perm() after a permission check, but can also be
 * called directly by callers who use avc_has_perm_noaudit()
 * in order to separate the permission check from the auditing.
 * For example, this separation is useful when the permission check must
 * be perक्रमmed under a lock, to allow the lock to be released
 * beक्रमe calling the auditing code.
 */
अटल अंतरभूत पूर्णांक avc_audit(काष्ठा selinux_state *state,
			    u32 ssid, u32 tsid,
			    u16 tclass, u32 requested,
			    काष्ठा av_decision *avd,
			    पूर्णांक result,
			    काष्ठा common_audit_data *a,
			    पूर्णांक flags)
अणु
	u32 audited, denied;
	audited = avc_audit_required(requested, avd, result, 0, &denied);
	अगर (likely(!audited))
		वापस 0;
	/* fall back to ref-walk अगर we have to generate audit */
	अगर (flags & MAY_NOT_BLOCK)
		वापस -ECHILD;
	वापस slow_avc_audit(state, ssid, tsid, tclass,
			      requested, audited, denied, result,
			      a);
पूर्ण

#घोषणा AVC_STRICT 1 /* Ignore permissive mode. */
#घोषणा AVC_EXTENDED_PERMS 2	/* update extended permissions */
#घोषणा AVC_NONBLOCKING    4	/* non blocking */
पूर्णांक avc_has_perm_noaudit(काष्ठा selinux_state *state,
			 u32 ssid, u32 tsid,
			 u16 tclass, u32 requested,
			 अचिन्हित flags,
			 काष्ठा av_decision *avd);

पूर्णांक avc_has_perm(काष्ठा selinux_state *state,
		 u32 ssid, u32 tsid,
		 u16 tclass, u32 requested,
		 काष्ठा common_audit_data *auditdata);
पूर्णांक avc_has_perm_flags(काष्ठा selinux_state *state,
		       u32 ssid, u32 tsid,
		       u16 tclass, u32 requested,
		       काष्ठा common_audit_data *auditdata,
		       पूर्णांक flags);

पूर्णांक avc_has_extended_perms(काष्ठा selinux_state *state,
			   u32 ssid, u32 tsid, u16 tclass, u32 requested,
			   u8 driver, u8 perm, काष्ठा common_audit_data *ad);


u32 avc_policy_seqno(काष्ठा selinux_state *state);

#घोषणा AVC_CALLBACK_GRANT		1
#घोषणा AVC_CALLBACK_TRY_REVOKE		2
#घोषणा AVC_CALLBACK_REVOKE		4
#घोषणा AVC_CALLBACK_RESET		8
#घोषणा AVC_CALLBACK_AUDITALLOW_ENABLE	16
#घोषणा AVC_CALLBACK_AUDITALLOW_DISABLE	32
#घोषणा AVC_CALLBACK_AUDITDENY_ENABLE	64
#घोषणा AVC_CALLBACK_AUDITDENY_DISABLE	128
#घोषणा AVC_CALLBACK_ADD_XPERMS		256

पूर्णांक avc_add_callback(पूर्णांक (*callback)(u32 event), u32 events);

/* Exported to selinuxfs */
काष्ठा selinux_avc;
पूर्णांक avc_get_hash_stats(काष्ठा selinux_avc *avc, अक्षर *page);
अचिन्हित पूर्णांक avc_get_cache_threshold(काष्ठा selinux_avc *avc);
व्योम avc_set_cache_threshold(काष्ठा selinux_avc *avc,
			     अचिन्हित पूर्णांक cache_threshold);

/* Attempt to मुक्त avc node cache */
व्योम avc_disable(व्योम);

#अगर_घोषित CONFIG_SECURITY_SELINUX_AVC_STATS
DECLARE_PER_CPU(काष्ठा avc_cache_stats, avc_cache_stats);
#पूर्ण_अगर

#पूर्ण_अगर /* _SELINUX_AVC_H_ */

