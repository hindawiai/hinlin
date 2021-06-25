<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor auditing functions
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#समावेश <linux/audit.h>
#समावेश <linux/socket.h>

#समावेश "include/apparmor.h"
#समावेश "include/audit.h"
#समावेश "include/policy.h"
#समावेश "include/policy_ns.h"
#समावेश "include/secid.h"

स्थिर अक्षर *स्थिर audit_mode_names[] = अणु
	"normal",
	"quiet_denied",
	"quiet",
	"noquiet",
	"all"
पूर्ण;

अटल स्थिर अक्षर *स्थिर aa_audit_type[] = अणु
	"AUDIT",
	"ALLOWED",
	"DENIED",
	"HINT",
	"STATUS",
	"ERROR",
	"KILLED",
	"AUTO"
पूर्ण;

/*
 * Currently AppArmor auditing is fed straight पूर्णांकo the audit framework.
 *
 * TODO:
 * netlink पूर्णांकerface क्रम complain mode
 * user auditing, - send user auditing to netlink पूर्णांकerface
 * प्रणाली control of whether user audit messages go to प्रणाली log
 */

/**
 * audit_base - core AppArmor function.
 * @ab: audit buffer to fill (NOT शून्य)
 * @ca: audit काष्ठाure containing data to audit (NOT शून्य)
 *
 * Record common AppArmor audit data from @sa
 */
अटल व्योम audit_pre(काष्ठा audit_buffer *ab, व्योम *ca)
अणु
	काष्ठा common_audit_data *sa = ca;

	अगर (aa_g_audit_header) अणु
		audit_log_क्रमmat(ab, "apparmor=\"%s\"",
				 aa_audit_type[aad(sa)->type]);
	पूर्ण

	अगर (aad(sa)->op) अणु
		audit_log_क्रमmat(ab, " operation=\"%s\"", aad(sa)->op);
	पूर्ण

	अगर (aad(sa)->info) अणु
		audit_log_क्रमmat(ab, " info=\"%s\"", aad(sa)->info);
		अगर (aad(sa)->error)
			audit_log_क्रमmat(ab, " error=%d", aad(sa)->error);
	पूर्ण

	अगर (aad(sa)->label) अणु
		काष्ठा aa_label *label = aad(sa)->label;

		अगर (label_isprofile(label)) अणु
			काष्ठा aa_profile *profile = labels_profile(label);

			अगर (profile->ns != root_ns) अणु
				audit_log_क्रमmat(ab, " namespace=");
				audit_log_untrustedstring(ab,
						       profile->ns->base.hname);
			पूर्ण
			audit_log_क्रमmat(ab, " profile=");
			audit_log_untrustedstring(ab, profile->base.hname);
		पूर्ण अन्यथा अणु
			audit_log_क्रमmat(ab, " label=");
			aa_label_xaudit(ab, root_ns, label, FLAG_VIEW_SUBNS,
					GFP_ATOMIC);
		पूर्ण
	पूर्ण

	अगर (aad(sa)->name) अणु
		audit_log_क्रमmat(ab, " name=");
		audit_log_untrustedstring(ab, aad(sa)->name);
	पूर्ण
पूर्ण

/**
 * aa_audit_msg - Log a message to the audit subप्रणाली
 * @sa: audit event काष्ठाure (NOT शून्य)
 * @cb: optional callback fn क्रम type specअगरic fields (MAYBE शून्य)
 */
व्योम aa_audit_msg(पूर्णांक type, काष्ठा common_audit_data *sa,
		  व्योम (*cb) (काष्ठा audit_buffer *, व्योम *))
अणु
	aad(sa)->type = type;
	common_lsm_audit(sa, audit_pre, cb);
पूर्ण

/**
 * aa_audit - Log a profile based audit event to the audit subप्रणाली
 * @type: audit type क्रम the message
 * @profile: profile to check against (NOT शून्य)
 * @sa: audit event (NOT शून्य)
 * @cb: optional callback fn क्रम type specअगरic fields (MAYBE शून्य)
 *
 * Handle शेष message चयनing based off of audit mode flags
 *
 * Returns: error on failure
 */
पूर्णांक aa_audit(पूर्णांक type, काष्ठा aa_profile *profile, काष्ठा common_audit_data *sa,
	     व्योम (*cb) (काष्ठा audit_buffer *, व्योम *))
अणु
	AA_BUG(!profile);

	अगर (type == AUDIT_APPARMOR_AUTO) अणु
		अगर (likely(!aad(sa)->error)) अणु
			अगर (AUDIT_MODE(profile) != AUDIT_ALL)
				वापस 0;
			type = AUDIT_APPARMOR_AUDIT;
		पूर्ण अन्यथा अगर (COMPLAIN_MODE(profile))
			type = AUDIT_APPARMOR_ALLOWED;
		अन्यथा
			type = AUDIT_APPARMOR_DENIED;
	पूर्ण
	अगर (AUDIT_MODE(profile) == AUDIT_QUIET ||
	    (type == AUDIT_APPARMOR_DENIED &&
	     AUDIT_MODE(profile) == AUDIT_QUIET))
		वापस aad(sa)->error;

	अगर (KILL_MODE(profile) && type == AUDIT_APPARMOR_DENIED)
		type = AUDIT_APPARMOR_KILL;

	aad(sa)->label = &profile->label;

	aa_audit_msg(type, sa, cb);

	अगर (aad(sa)->type == AUDIT_APPARMOR_KILL)
		(व्योम)send_sig_info(SIGKILL, शून्य,
			sa->type == LSM_AUDIT_DATA_TASK && sa->u.tsk ?
				    sa->u.tsk : current);

	अगर (aad(sa)->type == AUDIT_APPARMOR_ALLOWED)
		वापस complain_error(aad(sa)->error);

	वापस aad(sa)->error;
पूर्ण

काष्ठा aa_audit_rule अणु
	काष्ठा aa_label *label;
पूर्ण;

व्योम aa_audit_rule_मुक्त(व्योम *vrule)
अणु
	काष्ठा aa_audit_rule *rule = vrule;

	अगर (rule) अणु
		अगर (!IS_ERR(rule->label))
			aa_put_label(rule->label);
		kमुक्त(rule);
	पूर्ण
पूर्ण

पूर्णांक aa_audit_rule_init(u32 field, u32 op, अक्षर *rulestr, व्योम **vrule)
अणु
	काष्ठा aa_audit_rule *rule;

	चयन (field) अणु
	हाल AUDIT_SUBJ_ROLE:
		अगर (op != Audit_equal && op != Audit_not_equal)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	rule = kzalloc(माप(काष्ठा aa_audit_rule), GFP_KERNEL);

	अगर (!rule)
		वापस -ENOMEM;

	/* Currently rules are treated as coming from the root ns */
	rule->label = aa_label_parse(&root_ns->unconfined->label, rulestr,
				     GFP_KERNEL, true, false);
	अगर (IS_ERR(rule->label)) अणु
		पूर्णांक err = PTR_ERR(rule->label);
		aa_audit_rule_मुक्त(rule);
		वापस err;
	पूर्ण

	*vrule = rule;
	वापस 0;
पूर्ण

पूर्णांक aa_audit_rule_known(काष्ठा audit_krule *rule)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < rule->field_count; i++) अणु
		काष्ठा audit_field *f = &rule->fields[i];

		चयन (f->type) अणु
		हाल AUDIT_SUBJ_ROLE:
			वापस 1;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक aa_audit_rule_match(u32 sid, u32 field, u32 op, व्योम *vrule)
अणु
	काष्ठा aa_audit_rule *rule = vrule;
	काष्ठा aa_label *label;
	पूर्णांक found = 0;

	label = aa_secid_to_label(sid);

	अगर (!label)
		वापस -ENOENT;

	अगर (aa_label_is_subset(label, rule->label))
		found = 1;

	चयन (field) अणु
	हाल AUDIT_SUBJ_ROLE:
		चयन (op) अणु
		हाल Audit_equal:
			वापस found;
		हाल Audit_not_equal:
			वापस !found;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
