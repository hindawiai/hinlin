<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains basic common functions used in AppArmor
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/vदो_स्मृति.h>

#समावेश "include/audit.h"
#समावेश "include/apparmor.h"
#समावेश "include/lib.h"
#समावेश "include/perms.h"
#समावेश "include/policy.h"

काष्ठा aa_perms nullperms;
काष्ठा aa_perms allperms = अणु .allow = ALL_PERMS_MASK,
			     .quiet = ALL_PERMS_MASK,
			     .hide = ALL_PERMS_MASK पूर्ण;

/**
 * aa_split_fqname - split a fqname पूर्णांकo a profile and namespace name
 * @fqname: a full qualअगरied name in namespace profile क्रमmat (NOT शून्य)
 * @ns_name: poपूर्णांकer to portion of the string containing the ns name (NOT शून्य)
 *
 * Returns: profile name or शून्य अगर one is not specअगरied
 *
 * Split a namespace name from a profile name (see policy.c क्रम naming
 * description).  If a portion of the name is missing it वापसs शून्य क्रम
 * that portion.
 *
 * NOTE: may modअगरy the @fqname string.  The poपूर्णांकers वापसed poपूर्णांक
 *       पूर्णांकo the @fqname string.
 */
अक्षर *aa_split_fqname(अक्षर *fqname, अक्षर **ns_name)
अणु
	अक्षर *name = strim(fqname);

	*ns_name = शून्य;
	अगर (name[0] == ':') अणु
		अक्षर *split = म_अक्षर(&name[1], ':');
		*ns_name = skip_spaces(&name[1]);
		अगर (split) अणु
			/* overग_लिखो ':' with \0 */
			*split++ = 0;
			अगर (म_भेदन(split, "//", 2) == 0)
				split += 2;
			name = skip_spaces(split);
		पूर्ण अन्यथा
			/* a ns name without a following profile is allowed */
			name = शून्य;
	पूर्ण
	अगर (name && *name == 0)
		name = शून्य;

	वापस name;
पूर्ण

/**
 * skipn_spaces - Removes leading whitespace from @str.
 * @str: The string to be stripped.
 *
 * Returns a poपूर्णांकer to the first non-whitespace अक्षरacter in @str.
 * अगर all whitespace will वापस शून्य
 */

स्थिर अक्षर *skipn_spaces(स्थिर अक्षर *str, माप_प्रकार n)
अणु
	क्रम (; n && है_खाली(*str); --n)
		++str;
	अगर (n)
		वापस (अक्षर *)str;
	वापस शून्य;
पूर्ण

स्थिर अक्षर *aa_splitn_fqname(स्थिर अक्षर *fqname, माप_प्रकार n, स्थिर अक्षर **ns_name,
			     माप_प्रकार *ns_len)
अणु
	स्थिर अक्षर *end = fqname + n;
	स्थिर अक्षर *name = skipn_spaces(fqname, n);

	*ns_name = शून्य;
	*ns_len = 0;

	अगर (!name)
		वापस शून्य;

	अगर (name[0] == ':') अणु
		अक्षर *split = strnchr(&name[1], end - &name[1], ':');
		*ns_name = skipn_spaces(&name[1], end - &name[1]);
		अगर (!*ns_name)
			वापस शून्य;
		अगर (split) अणु
			*ns_len = split - *ns_name;
			अगर (*ns_len == 0)
				*ns_name = शून्य;
			split++;
			अगर (end - split > 1 && म_भेदन(split, "//", 2) == 0)
				split += 2;
			name = skipn_spaces(split, end - split);
		पूर्ण अन्यथा अणु
			/* a ns name without a following profile is allowed */
			name = शून्य;
			*ns_len = end - *ns_name;
		पूर्ण
	पूर्ण
	अगर (name && *name == 0)
		name = शून्य;

	वापस name;
पूर्ण

/**
 * aa_info_message - log a none profile related status message
 * @str: message to log
 */
व्योम aa_info_message(स्थिर अक्षर *str)
अणु
	अगर (audit_enabled) अणु
		DEFINE_AUDIT_DATA(sa, LSM_AUDIT_DATA_NONE, शून्य);

		aad(&sa)->info = str;
		aa_audit_msg(AUDIT_APPARMOR_STATUS, &sa, शून्य);
	पूर्ण
	prपूर्णांकk(KERN_INFO "AppArmor: %s\n", str);
पूर्ण

__counted अक्षर *aa_str_alloc(पूर्णांक size, gfp_t gfp)
अणु
	काष्ठा counted_str *str;

	str = kदो_स्मृति(माप(काष्ठा counted_str) + size, gfp);
	अगर (!str)
		वापस शून्य;

	kref_init(&str->count);
	वापस str->name;
पूर्ण

व्योम aa_str_kref(काष्ठा kref *kref)
अणु
	kमुक्त(container_of(kref, काष्ठा counted_str, count));
पूर्ण


स्थिर अक्षर aa_file_perm_chrs[] = "xwracd         km l     ";
स्थिर अक्षर *aa_file_perm_names[] = अणु
	"exec",
	"write",
	"read",
	"append",

	"create",
	"delete",
	"open",
	"rename",

	"setattr",
	"getattr",
	"setcred",
	"getcred",

	"chmod",
	"chown",
	"chgrp",
	"lock",

	"mmap",
	"mprot",
	"link",
	"snapshot",

	"unknown",
	"unknown",
	"unknown",
	"unknown",

	"unknown",
	"unknown",
	"unknown",
	"unknown",

	"stack",
	"change_onexec",
	"change_profile",
	"change_hat",
पूर्ण;

/**
 * aa_perm_mask_to_str - convert a perm mask to its लघु string
 * @str: अक्षरacter buffer to store string in (at least 10 अक्षरacters)
 * @str_size: size of the @str buffer
 * @chrs: NUL-terminated अक्षरacter buffer of permission अक्षरacters
 * @mask: permission mask to convert
 */
व्योम aa_perm_mask_to_str(अक्षर *str, माप_प्रकार str_size, स्थिर अक्षर *chrs, u32 mask)
अणु
	अचिन्हित पूर्णांक i, perm = 1;
	माप_प्रकार num_chrs = म_माप(chrs);

	क्रम (i = 0; i < num_chrs; perm <<= 1, i++) अणु
		अगर (mask & perm) अणु
			/* Ensure that one byte is left क्रम NUL-termination */
			अगर (WARN_ON_ONCE(str_size <= 1))
				अवरोध;

			*str++ = chrs[i];
			str_size--;
		पूर्ण
	पूर्ण
	*str = '\0';
पूर्ण

व्योम aa_audit_perm_names(काष्ठा audit_buffer *ab, स्थिर अक्षर * स्थिर *names,
			 u32 mask)
अणु
	स्थिर अक्षर *fmt = "%s";
	अचिन्हित पूर्णांक i, perm = 1;
	bool prev = false;

	क्रम (i = 0; i < 32; perm <<= 1, i++) अणु
		अगर (mask & perm) अणु
			audit_log_क्रमmat(ab, fmt, names[i]);
			अगर (!prev) अणु
				prev = true;
				fmt = " %s";
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

व्योम aa_audit_perm_mask(काष्ठा audit_buffer *ab, u32 mask, स्थिर अक्षर *chrs,
			u32 chrsmask, स्थिर अक्षर * स्थिर *names, u32 namesmask)
अणु
	अक्षर str[33];

	audit_log_क्रमmat(ab, "\"");
	अगर ((mask & chrsmask) && chrs) अणु
		aa_perm_mask_to_str(str, माप(str), chrs, mask & chrsmask);
		mask &= ~chrsmask;
		audit_log_क्रमmat(ab, "%s", str);
		अगर (mask & namesmask)
			audit_log_क्रमmat(ab, " ");
	पूर्ण
	अगर ((mask & namesmask) && names)
		aa_audit_perm_names(ab, names, mask & namesmask);
	audit_log_क्रमmat(ab, "\"");
पूर्ण

/**
 * aa_audit_perms_cb - generic callback fn क्रम auditing perms
 * @ab: audit buffer (NOT शून्य)
 * @va: audit काष्ठा to audit values of (NOT शून्य)
 */
अटल व्योम aa_audit_perms_cb(काष्ठा audit_buffer *ab, व्योम *va)
अणु
	काष्ठा common_audit_data *sa = va;

	अगर (aad(sa)->request) अणु
		audit_log_क्रमmat(ab, " requested_mask=");
		aa_audit_perm_mask(ab, aad(sa)->request, aa_file_perm_chrs,
				   PERMS_CHRS_MASK, aa_file_perm_names,
				   PERMS_NAMES_MASK);
	पूर्ण
	अगर (aad(sa)->denied) अणु
		audit_log_क्रमmat(ab, "denied_mask=");
		aa_audit_perm_mask(ab, aad(sa)->denied, aa_file_perm_chrs,
				   PERMS_CHRS_MASK, aa_file_perm_names,
				   PERMS_NAMES_MASK);
	पूर्ण
	audit_log_क्रमmat(ab, " peer=");
	aa_label_xaudit(ab, labels_ns(aad(sa)->label), aad(sa)->peer,
				      FLAGS_NONE, GFP_ATOMIC);
पूर्ण

/**
 * aa_apply_modes_to_perms - apply namespace and profile flags to perms
 * @profile: that perms where computed from
 * @perms: perms to apply mode modअगरiers to
 *
 * TODO: split पूर्णांकo profile and ns based flags क्रम when accumulating perms
 */
व्योम aa_apply_modes_to_perms(काष्ठा aa_profile *profile, काष्ठा aa_perms *perms)
अणु
	चयन (AUDIT_MODE(profile)) अणु
	हाल AUDIT_ALL:
		perms->audit = ALL_PERMS_MASK;
		fallthrough;
	हाल AUDIT_NOQUIET:
		perms->quiet = 0;
		अवरोध;
	हाल AUDIT_QUIET:
		perms->audit = 0;
		fallthrough;
	हाल AUDIT_QUIET_DENIED:
		perms->quiet = ALL_PERMS_MASK;
		अवरोध;
	पूर्ण

	अगर (KILL_MODE(profile))
		perms->समाप्त = ALL_PERMS_MASK;
	अन्यथा अगर (COMPLAIN_MODE(profile))
		perms->complain = ALL_PERMS_MASK;
/*
 *  TODO:
 *	अन्यथा अगर (PROMPT_MODE(profile))
 *		perms->prompt = ALL_PERMS_MASK;
 */
पूर्ण

अटल u32 map_other(u32 x)
अणु
	वापस ((x & 0x3) << 8) |	/* SETATTR/GETATTR */
		((x & 0x1c) << 18) |	/* ACCEPT/BIND/LISTEN */
		((x & 0x60) << 19);	/* SETOPT/GETOPT */
पूर्ण

व्योम aa_compute_perms(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक state,
		      काष्ठा aa_perms *perms)
अणु
	*perms = (काष्ठा aa_perms) अणु
		.allow = dfa_user_allow(dfa, state),
		.audit = dfa_user_audit(dfa, state),
		.quiet = dfa_user_quiet(dfa, state),
	पूर्ण;

	/* क्रम v5 perm mapping in the policydb, the other set is used
	 * to extend the general perm set
	 */
	perms->allow |= map_other(dfa_other_allow(dfa, state));
	perms->audit |= map_other(dfa_other_audit(dfa, state));
	perms->quiet |= map_other(dfa_other_quiet(dfa, state));
//	perms->xindex = dfa_user_xindex(dfa, state);
पूर्ण

/**
 * aa_perms_accum_raw - accumulate perms with out masking off overlapping perms
 * @accum - perms काष्ठा to accumulate पूर्णांकo
 * @addend - perms काष्ठा to add to @accum
 */
व्योम aa_perms_accum_raw(काष्ठा aa_perms *accum, काष्ठा aa_perms *addend)
अणु
	accum->deny |= addend->deny;
	accum->allow &= addend->allow & ~addend->deny;
	accum->audit |= addend->audit & addend->allow;
	accum->quiet &= addend->quiet & ~addend->allow;
	accum->समाप्त |= addend->समाप्त & ~addend->allow;
	accum->stop |= addend->stop & ~addend->allow;
	accum->complain |= addend->complain & ~addend->allow & ~addend->deny;
	accum->cond |= addend->cond & ~addend->allow & ~addend->deny;
	accum->hide &= addend->hide & ~addend->allow;
	accum->prompt |= addend->prompt & ~addend->allow & ~addend->deny;
पूर्ण

/**
 * aa_perms_accum - accumulate perms, masking off overlapping perms
 * @accum - perms काष्ठा to accumulate पूर्णांकo
 * @addend - perms काष्ठा to add to @accum
 */
व्योम aa_perms_accum(काष्ठा aa_perms *accum, काष्ठा aa_perms *addend)
अणु
	accum->deny |= addend->deny;
	accum->allow &= addend->allow & ~accum->deny;
	accum->audit |= addend->audit & accum->allow;
	accum->quiet &= addend->quiet & ~accum->allow;
	accum->समाप्त |= addend->समाप्त & ~accum->allow;
	accum->stop |= addend->stop & ~accum->allow;
	accum->complain |= addend->complain & ~accum->allow & ~accum->deny;
	accum->cond |= addend->cond & ~accum->allow & ~accum->deny;
	accum->hide &= addend->hide & ~accum->allow;
	accum->prompt |= addend->prompt & ~accum->allow & ~accum->deny;
पूर्ण

व्योम aa_profile_match_label(काष्ठा aa_profile *profile, काष्ठा aa_label *label,
			    पूर्णांक type, u32 request, काष्ठा aa_perms *perms)
अणु
	/* TODO: करोesn't yet handle extended types */
	अचिन्हित पूर्णांक state;

	state = aa_dfa_next(profile->policy.dfa,
			    profile->policy.start[AA_CLASS_LABEL],
			    type);
	aa_label_match(profile, label, state, false, request, perms);
पूर्ण


/* currently unused */
पूर्णांक aa_profile_label_perm(काष्ठा aa_profile *profile, काष्ठा aa_profile *target,
			  u32 request, पूर्णांक type, u32 *deny,
			  काष्ठा common_audit_data *sa)
अणु
	काष्ठा aa_perms perms;

	aad(sa)->label = &profile->label;
	aad(sa)->peer = &target->label;
	aad(sa)->request = request;

	aa_profile_match_label(profile, &target->label, type, request, &perms);
	aa_apply_modes_to_perms(profile, &perms);
	*deny |= request & perms.deny;
	वापस aa_check_perms(profile, &perms, request, sa, aa_audit_perms_cb);
पूर्ण

/**
 * aa_check_perms - करो audit mode selection based on perms set
 * @profile: profile being checked
 * @perms: perms computed क्रम the request
 * @request: requested perms
 * @deny: Returns: explicit deny set
 * @sa: initialized audit काष्ठाure (MAY BE शून्य अगर not auditing)
 * @cb: callback fn क्रम type specअगरic fields (MAY BE शून्य)
 *
 * Returns: 0 अगर permission अन्यथा error code
 *
 * Note: profile audit modes need to be set beक्रमe calling by setting the
 *       perm masks appropriately.
 *
 *       If not auditing then complain mode is not enabled and the
 *       error code will indicate whether there was an explicit deny
 *	 with a positive value.
 */
पूर्णांक aa_check_perms(काष्ठा aa_profile *profile, काष्ठा aa_perms *perms,
		   u32 request, काष्ठा common_audit_data *sa,
		   व्योम (*cb)(काष्ठा audit_buffer *, व्योम *))
अणु
	पूर्णांक type, error;
	u32 denied = request & (~perms->allow | perms->deny);

	अगर (likely(!denied)) अणु
		/* mask off perms that are not being क्रमce audited */
		request &= perms->audit;
		अगर (!request || !sa)
			वापस 0;

		type = AUDIT_APPARMOR_AUDIT;
		error = 0;
	पूर्ण अन्यथा अणु
		error = -EACCES;

		अगर (denied & perms->समाप्त)
			type = AUDIT_APPARMOR_KILL;
		अन्यथा अगर (denied == (denied & perms->complain))
			type = AUDIT_APPARMOR_ALLOWED;
		अन्यथा
			type = AUDIT_APPARMOR_DENIED;

		अगर (denied == (denied & perms->hide))
			error = -ENOENT;

		denied &= ~perms->quiet;
		अगर (!sa || !denied)
			वापस error;
	पूर्ण

	अगर (sa) अणु
		aad(sa)->label = &profile->label;
		aad(sa)->request = request;
		aad(sa)->denied = denied;
		aad(sa)->error = error;
		aa_audit_msg(type, sa, cb);
	पूर्ण

	अगर (type == AUDIT_APPARMOR_ALLOWED)
		error = 0;

	वापस error;
पूर्ण


/**
 * aa_policy_init - initialize a policy काष्ठाure
 * @policy: policy to initialize  (NOT शून्य)
 * @prefix: prefix name अगर any is required.  (MAYBE शून्य)
 * @name: name of the policy, init will make a copy of it  (NOT शून्य)
 * @gfp: allocation mode
 *
 * Note: this fn creates a copy of strings passed in
 *
 * Returns: true अगर policy init successful
 */
bool aa_policy_init(काष्ठा aa_policy *policy, स्थिर अक्षर *prefix,
		    स्थिर अक्षर *name, gfp_t gfp)
अणु
	अक्षर *hname;

	/* मुक्तd by policy_मुक्त */
	अगर (prefix) अणु
		hname = aa_str_alloc(म_माप(prefix) + म_माप(name) + 3, gfp);
		अगर (hname)
			प्र_लिखो(hname, "%s//%s", prefix, name);
	पूर्ण अन्यथा अणु
		hname = aa_str_alloc(म_माप(name) + 1, gfp);
		अगर (hname)
			म_नकल(hname, name);
	पूर्ण
	अगर (!hname)
		वापस false;
	policy->hname = hname;
	/* base.name is a substring of fqname */
	policy->name = basename(policy->hname);
	INIT_LIST_HEAD(&policy->list);
	INIT_LIST_HEAD(&policy->profiles);

	वापस true;
पूर्ण

/**
 * aa_policy_destroy - मुक्त the elements referenced by @policy
 * @policy: policy that is to have its elements मुक्तd  (NOT शून्य)
 */
व्योम aa_policy_destroy(काष्ठा aa_policy *policy)
अणु
	AA_BUG(on_list_rcu(&policy->profiles));
	AA_BUG(on_list_rcu(&policy->list));

	/* करोn't मुक्त name as its a subset of hname */
	aa_put_str(policy->hname);
पूर्ण
