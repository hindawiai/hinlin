<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor capability mediation functions
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#समावेश <linux/capability.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gfp.h>
#समावेश <linux/security.h>

#समावेश "include/apparmor.h"
#समावेश "include/capability.h"
#समावेश "include/cred.h"
#समावेश "include/policy.h"
#समावेश "include/audit.h"

/*
 * Table of capability names: we generate it from capabilities.h.
 */
#समावेश "capability_names.h"

काष्ठा aa_sfs_entry aa_sfs_entry_caps[] = अणु
	AA_SFS_खाता_STRING("mask", AA_SFS_CAPS_MASK),
	अणु पूर्ण
पूर्ण;

काष्ठा audit_cache अणु
	काष्ठा aa_profile *profile;
	kernel_cap_t caps;
पूर्ण;

अटल DEFINE_PER_CPU(काष्ठा audit_cache, audit_cache);

/**
 * audit_cb - call back क्रम capability components of audit काष्ठा
 * @ab - audit buffer   (NOT शून्य)
 * @va - audit काष्ठा to audit data from  (NOT शून्य)
 */
अटल व्योम audit_cb(काष्ठा audit_buffer *ab, व्योम *va)
अणु
	काष्ठा common_audit_data *sa = va;

	audit_log_क्रमmat(ab, " capname=");
	audit_log_untrustedstring(ab, capability_names[sa->u.cap]);
पूर्ण

/**
 * audit_caps - audit a capability
 * @sa: audit data
 * @profile: profile being tested क्रम confinement (NOT शून्य)
 * @cap: capability tested
 * @error: error code वापसed by test
 *
 * Do auditing of capability and handle, audit/complain/समाप्त modes चयनing
 * and duplicate message elimination.
 *
 * Returns: 0 or sa->error on success,  error code on failure
 */
अटल पूर्णांक audit_caps(काष्ठा common_audit_data *sa, काष्ठा aa_profile *profile,
		      पूर्णांक cap, पूर्णांक error)
अणु
	काष्ठा audit_cache *ent;
	पूर्णांक type = AUDIT_APPARMOR_AUTO;

	aad(sa)->error = error;

	अगर (likely(!error)) अणु
		/* test अगर auditing is being क्रमced */
		अगर (likely((AUDIT_MODE(profile) != AUDIT_ALL) &&
			   !cap_उठाओd(profile->caps.audit, cap)))
			वापस 0;
		type = AUDIT_APPARMOR_AUDIT;
	पूर्ण अन्यथा अगर (KILL_MODE(profile) ||
		   cap_उठाओd(profile->caps.समाप्त, cap)) अणु
		type = AUDIT_APPARMOR_KILL;
	पूर्ण अन्यथा अगर (cap_उठाओd(profile->caps.quiet, cap) &&
		   AUDIT_MODE(profile) != AUDIT_NOQUIET &&
		   AUDIT_MODE(profile) != AUDIT_ALL) अणु
		/* quiet auditing */
		वापस error;
	पूर्ण

	/* Do simple duplicate message elimination */
	ent = &get_cpu_var(audit_cache);
	अगर (profile == ent->profile && cap_उठाओd(ent->caps, cap)) अणु
		put_cpu_var(audit_cache);
		अगर (COMPLAIN_MODE(profile))
			वापस complain_error(error);
		वापस error;
	पूर्ण अन्यथा अणु
		aa_put_profile(ent->profile);
		ent->profile = aa_get_profile(profile);
		cap_उठाओ(ent->caps, cap);
	पूर्ण
	put_cpu_var(audit_cache);

	वापस aa_audit(type, profile, sa, audit_cb);
पूर्ण

/**
 * profile_capable - test अगर profile allows use of capability @cap
 * @profile: profile being enक्रमced    (NOT शून्य, NOT unconfined)
 * @cap: capability to test अगर allowed
 * @opts: CAP_OPT_NOAUDIT bit determines whether audit record is generated
 * @sa: audit data (MAY BE शून्य indicating no auditing)
 *
 * Returns: 0 अगर allowed अन्यथा -EPERM
 */
अटल पूर्णांक profile_capable(काष्ठा aa_profile *profile, पूर्णांक cap,
			   अचिन्हित पूर्णांक opts, काष्ठा common_audit_data *sa)
अणु
	पूर्णांक error;

	अगर (cap_उठाओd(profile->caps.allow, cap) &&
	    !cap_उठाओd(profile->caps.denied, cap))
		error = 0;
	अन्यथा
		error = -EPERM;

	अगर (opts & CAP_OPT_NOAUDIT) अणु
		अगर (!COMPLAIN_MODE(profile))
			वापस error;
		/* audit the cap request in complain mode but note that it
		 * should be optional.
		 */
		aad(sa)->info = "optional: no audit";
	पूर्ण

	वापस audit_caps(sa, profile, cap, error);
पूर्ण

/**
 * aa_capable - test permission to use capability
 * @label: label being tested क्रम capability (NOT शून्य)
 * @cap: capability to be tested
 * @opts: CAP_OPT_NOAUDIT bit determines whether audit record is generated
 *
 * Look up capability in profile capability set.
 *
 * Returns: 0 on success, or अन्यथा an error code.
 */
पूर्णांक aa_capable(काष्ठा aa_label *label, पूर्णांक cap, अचिन्हित पूर्णांक opts)
अणु
	काष्ठा aa_profile *profile;
	पूर्णांक error = 0;
	DEFINE_AUDIT_DATA(sa, LSM_AUDIT_DATA_CAP, OP_CAPABLE);

	sa.u.cap = cap;
	error = fn_क्रम_each_confined(label, profile,
			profile_capable(profile, cap, opts, &sa));

	वापस error;
पूर्ण
