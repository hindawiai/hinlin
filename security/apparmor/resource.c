<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor resource mediation and attachment
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#समावेश <linux/audit.h>
#समावेश <linux/security.h>

#समावेश "include/audit.h"
#समावेश "include/cred.h"
#समावेश "include/resource.h"
#समावेश "include/policy.h"

/*
 * Table of rlimit names: we generate it from resource.h.
 */
#समावेश "rlim_names.h"

काष्ठा aa_sfs_entry aa_sfs_entry_rlimit[] = अणु
	AA_SFS_खाता_STRING("mask", AA_SFS_RLIMIT_MASK),
	अणु पूर्ण
पूर्ण;

/* audit callback क्रम resource specअगरic fields */
अटल व्योम audit_cb(काष्ठा audit_buffer *ab, व्योम *va)
अणु
	काष्ठा common_audit_data *sa = va;

	audit_log_क्रमmat(ab, " rlimit=%s value=%lu",
			 rlim_names[aad(sa)->rlim.rlim], aad(sa)->rlim.max);
	अगर (aad(sa)->peer) अणु
		audit_log_क्रमmat(ab, " peer=");
		aa_label_xaudit(ab, labels_ns(aad(sa)->label), aad(sa)->peer,
				FLAGS_NONE, GFP_ATOMIC);
	पूर्ण
पूर्ण

/**
 * audit_resource - audit setting resource limit
 * @profile: profile being enक्रमced  (NOT शून्य)
 * @resource: rlimit being auditing
 * @value: value being set
 * @error: error value
 *
 * Returns: 0 or sa->error अन्यथा other error code on failure
 */
अटल पूर्णांक audit_resource(काष्ठा aa_profile *profile, अचिन्हित पूर्णांक resource,
			  अचिन्हित दीर्घ value, काष्ठा aa_label *peer,
			  स्थिर अक्षर *info, पूर्णांक error)
अणु
	DEFINE_AUDIT_DATA(sa, LSM_AUDIT_DATA_NONE, OP_SETRLIMIT);

	aad(&sa)->rlim.rlim = resource;
	aad(&sa)->rlim.max = value;
	aad(&sa)->peer = peer;
	aad(&sa)->info = info;
	aad(&sa)->error = error;

	वापस aa_audit(AUDIT_APPARMOR_AUTO, profile, &sa, audit_cb);
पूर्ण

/**
 * aa_map_resouce - map compiled policy resource to पूर्णांकernal #
 * @resource: flattened policy resource number
 *
 * Returns: resource # क्रम the current architecture.
 *
 * rlimit resource can vary based on architecture, map the compiled policy
 * resource # to the पूर्णांकernal representation क्रम the architecture.
 */
पूर्णांक aa_map_resource(पूर्णांक resource)
अणु
	वापस rlim_map[resource];
पूर्ण

अटल पूर्णांक profile_setrlimit(काष्ठा aa_profile *profile, अचिन्हित पूर्णांक resource,
			     काष्ठा rlimit *new_rlim)
अणु
	पूर्णांक e = 0;

	अगर (profile->rlimits.mask & (1 << resource) && new_rlim->rlim_max >
	    profile->rlimits.limits[resource].rlim_max)
		e = -EACCES;
	वापस audit_resource(profile, resource, new_rlim->rlim_max, शून्य, शून्य,
			      e);
पूर्ण

/**
 * aa_task_setrlimit - test permission to set an rlimit
 * @label - label confining the task  (NOT शून्य)
 * @task - task the resource is being set on
 * @resource - the resource being set
 * @new_rlim - the new resource limit  (NOT शून्य)
 *
 * Control raising the processes hard limit.
 *
 * Returns: 0 or error code अगर setting resource failed
 */
पूर्णांक aa_task_setrlimit(काष्ठा aa_label *label, काष्ठा task_काष्ठा *task,
		      अचिन्हित पूर्णांक resource, काष्ठा rlimit *new_rlim)
अणु
	काष्ठा aa_profile *profile;
	काष्ठा aa_label *peer;
	पूर्णांक error = 0;

	rcu_पढ़ो_lock();
	peer = aa_get_newest_cred_label(__task_cred(task));
	rcu_पढ़ो_unlock();

	/* TODO: extend resource control to handle other (non current)
	 * profiles.  AppArmor rules currently have the implicit assumption
	 * that the task is setting the resource of a task confined with
	 * the same profile or that the task setting the resource of another
	 * task has CAP_SYS_RESOURCE.
	 */

	अगर (label != peer &&
	    aa_capable(label, CAP_SYS_RESOURCE, CAP_OPT_NOAUDIT) != 0)
		error = fn_क्रम_each(label, profile,
				audit_resource(profile, resource,
					       new_rlim->rlim_max, peer,
					       "cap_sys_resource", -EACCES));
	अन्यथा
		error = fn_क्रम_each_confined(label, profile,
				profile_setrlimit(profile, resource, new_rlim));
	aa_put_label(peer);

	वापस error;
पूर्ण

/**
 * __aa_transition_rlimits - apply new profile rlimits
 * @old_l: old label on task  (NOT शून्य)
 * @new_l: new label with rlimits to apply  (NOT शून्य)
 */
व्योम __aa_transition_rlimits(काष्ठा aa_label *old_l, काष्ठा aa_label *new_l)
अणु
	अचिन्हित पूर्णांक mask = 0;
	काष्ठा rlimit *rlim, *initrlim;
	काष्ठा aa_profile *old, *new;
	काष्ठा label_it i;

	old = labels_profile(old_l);
	new = labels_profile(new_l);

	/* क्रम any rlimits the profile controlled, reset the soft limit
	 * to the lesser of the tasks hard limit and the init tasks soft limit
	 */
	label_क्रम_each_confined(i, old_l, old) अणु
		अगर (old->rlimits.mask) अणु
			पूर्णांक j;

			क्रम (j = 0, mask = 1; j < RLIM_NLIMITS; j++,
				     mask <<= 1) अणु
				अगर (old->rlimits.mask & mask) अणु
					rlim = current->संकेत->rlim + j;
					initrlim = init_task.संकेत->rlim + j;
					rlim->rlim_cur = min(rlim->rlim_max,
							    initrlim->rlim_cur);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	/* set any new hard limits as dictated by the new profile */
	label_क्रम_each_confined(i, new_l, new) अणु
		पूर्णांक j;

		अगर (!new->rlimits.mask)
			जारी;
		क्रम (j = 0, mask = 1; j < RLIM_NLIMITS; j++, mask <<= 1) अणु
			अगर (!(new->rlimits.mask & mask))
				जारी;

			rlim = current->संकेत->rlim + j;
			rlim->rlim_max = min(rlim->rlim_max,
					     new->rlimits.limits[j].rlim_max);
			/* soft limit should not exceed hard limit */
			rlim->rlim_cur = min(rlim->rlim_cur, rlim->rlim_max);
		पूर्ण
	पूर्ण
पूर्ण
