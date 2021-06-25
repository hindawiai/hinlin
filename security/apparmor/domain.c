<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor policy attachment and करोमुख्य transitions
 *
 * Copyright (C) 2002-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fdtable.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/mount.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/tracehook.h>
#समावेश <linux/personality.h>
#समावेश <linux/xattr.h>
#समावेश <linux/user_namespace.h>

#समावेश "include/audit.h"
#समावेश "include/apparmorfs.h"
#समावेश "include/cred.h"
#समावेश "include/domain.h"
#समावेश "include/file.h"
#समावेश "include/ipc.h"
#समावेश "include/match.h"
#समावेश "include/path.h"
#समावेश "include/policy.h"
#समावेश "include/policy_ns.h"

/**
 * aa_मुक्त_करोमुख्य_entries - मुक्त entries in a करोमुख्य table
 * @करोमुख्य: the करोमुख्य table to मुक्त  (MAYBE शून्य)
 */
व्योम aa_मुक्त_करोमुख्य_entries(काष्ठा aa_करोमुख्य *करोमुख्य)
अणु
	पूर्णांक i;
	अगर (करोमुख्य) अणु
		अगर (!करोमुख्य->table)
			वापस;

		क्रम (i = 0; i < करोमुख्य->size; i++)
			kमुक्त_sensitive(करोमुख्य->table[i]);
		kमुक्त_sensitive(करोमुख्य->table);
		करोमुख्य->table = शून्य;
	पूर्ण
पूर्ण

/**
 * may_change_ptraced_करोमुख्य - check अगर can change profile on ptraced task
 * @to_label: profile to change to  (NOT शून्य)
 * @info: message अगर there is an error
 *
 * Check अगर current is ptraced and अगर so अगर the tracing task is allowed
 * to trace the new करोमुख्य
 *
 * Returns: %0 or error अगर change not allowed
 */
अटल पूर्णांक may_change_ptraced_करोमुख्य(काष्ठा aa_label *to_label,
				     स्थिर अक्षर **info)
अणु
	काष्ठा task_काष्ठा *tracer;
	काष्ठा aa_label *tracerl = शून्य;
	पूर्णांक error = 0;

	rcu_पढ़ो_lock();
	tracer = ptrace_parent(current);
	अगर (tracer)
		/* released below */
		tracerl = aa_get_task_label(tracer);

	/* not ptraced */
	अगर (!tracer || unconfined(tracerl))
		जाओ out;

	error = aa_may_ptrace(tracerl, to_label, PTRACE_MODE_ATTACH);

out:
	rcu_पढ़ो_unlock();
	aa_put_label(tracerl);

	अगर (error)
		*info = "ptrace prevents transition";
	वापस error;
पूर्ण

/**** TODO: dedup to aa_label_match - needs perm and dfa, merging
 * specअगरically this is an exact copy of aa_label_match except
 * aa_compute_perms is replaced with aa_compute_fperms
 * and policy.dfa with file.dfa
 ****/
/* match a profile and its associated ns component अगर needed
 * Assumes visibility test has alपढ़ोy been करोne.
 * If a subns profile is not to be matched should be prescreened with
 * visibility test.
 */
अटल अंतरभूत अचिन्हित पूर्णांक match_component(काष्ठा aa_profile *profile,
					   काष्ठा aa_profile *tp,
					   bool stack, अचिन्हित पूर्णांक state)
अणु
	स्थिर अक्षर *ns_name;

	अगर (stack)
		state = aa_dfa_match(profile->file.dfa, state, "&");
	अगर (profile->ns == tp->ns)
		वापस aa_dfa_match(profile->file.dfa, state, tp->base.hname);

	/* try matching with namespace name and then profile */
	ns_name = aa_ns_name(profile->ns, tp->ns, true);
	state = aa_dfa_match_len(profile->file.dfa, state, ":", 1);
	state = aa_dfa_match(profile->file.dfa, state, ns_name);
	state = aa_dfa_match_len(profile->file.dfa, state, ":", 1);
	वापस aa_dfa_match(profile->file.dfa, state, tp->base.hname);
पूर्ण

/**
 * label_compound_match - find perms क्रम full compound label
 * @profile: profile to find perms क्रम
 * @label: label to check access permissions क्रम
 * @stack: whether this is a stacking request
 * @start: state to start match in
 * @subns: whether to करो permission checks on components in a subns
 * @request: permissions to request
 * @perms: perms काष्ठा to set
 *
 * Returns: 0 on success अन्यथा ERROR
 *
 * For the label A//&B//&C this करोes the perm match क्रम A//&B//&C
 * @perms should be preinitialized with allperms OR a previous permission
 *        check to be stacked.
 */
अटल पूर्णांक label_compound_match(काष्ठा aa_profile *profile,
				काष्ठा aa_label *label, bool stack,
				अचिन्हित पूर्णांक state, bool subns, u32 request,
				काष्ठा aa_perms *perms)
अणु
	काष्ठा aa_profile *tp;
	काष्ठा label_it i;
	काष्ठा path_cond cond = अणु पूर्ण;

	/* find first subcomponent that is visible */
	label_क्रम_each(i, label, tp) अणु
		अगर (!aa_ns_visible(profile->ns, tp->ns, subns))
			जारी;
		state = match_component(profile, tp, stack, state);
		अगर (!state)
			जाओ fail;
		जाओ next;
	पूर्ण

	/* no component visible */
	*perms = allperms;
	वापस 0;

next:
	label_क्रम_each_cont(i, label, tp) अणु
		अगर (!aa_ns_visible(profile->ns, tp->ns, subns))
			जारी;
		state = aa_dfa_match(profile->file.dfa, state, "//&");
		state = match_component(profile, tp, false, state);
		अगर (!state)
			जाओ fail;
	पूर्ण
	*perms = aa_compute_fperms(profile->file.dfa, state, &cond);
	aa_apply_modes_to_perms(profile, perms);
	अगर ((perms->allow & request) != request)
		वापस -EACCES;

	वापस 0;

fail:
	*perms = nullperms;
	वापस -EACCES;
पूर्ण

/**
 * label_components_match - find perms क्रम all subcomponents of a label
 * @profile: profile to find perms क्रम
 * @label: label to check access permissions क्रम
 * @stack: whether this is a stacking request
 * @start: state to start match in
 * @subns: whether to करो permission checks on components in a subns
 * @request: permissions to request
 * @perms: an initialized perms काष्ठा to add accumulation to
 *
 * Returns: 0 on success अन्यथा ERROR
 *
 * For the label A//&B//&C this करोes the perm match क्रम each of A and B and C
 * @perms should be preinitialized with allperms OR a previous permission
 *        check to be stacked.
 */
अटल पूर्णांक label_components_match(काष्ठा aa_profile *profile,
				  काष्ठा aa_label *label, bool stack,
				  अचिन्हित पूर्णांक start, bool subns, u32 request,
				  काष्ठा aa_perms *perms)
अणु
	काष्ठा aa_profile *tp;
	काष्ठा label_it i;
	काष्ठा aa_perms पंचांगp;
	काष्ठा path_cond cond = अणु पूर्ण;
	अचिन्हित पूर्णांक state = 0;

	/* find first subcomponent to test */
	label_क्रम_each(i, label, tp) अणु
		अगर (!aa_ns_visible(profile->ns, tp->ns, subns))
			जारी;
		state = match_component(profile, tp, stack, start);
		अगर (!state)
			जाओ fail;
		जाओ next;
	पूर्ण

	/* no subcomponents visible - no change in perms */
	वापस 0;

next:
	पंचांगp = aa_compute_fperms(profile->file.dfa, state, &cond);
	aa_apply_modes_to_perms(profile, &पंचांगp);
	aa_perms_accum(perms, &पंचांगp);
	label_क्रम_each_cont(i, label, tp) अणु
		अगर (!aa_ns_visible(profile->ns, tp->ns, subns))
			जारी;
		state = match_component(profile, tp, stack, start);
		अगर (!state)
			जाओ fail;
		पंचांगp = aa_compute_fperms(profile->file.dfa, state, &cond);
		aa_apply_modes_to_perms(profile, &पंचांगp);
		aa_perms_accum(perms, &पंचांगp);
	पूर्ण

	अगर ((perms->allow & request) != request)
		वापस -EACCES;

	वापस 0;

fail:
	*perms = nullperms;
	वापस -EACCES;
पूर्ण

/**
 * label_match - करो a multi-component label match
 * @profile: profile to match against (NOT शून्य)
 * @label: label to match (NOT शून्य)
 * @stack: whether this is a stacking request
 * @state: state to start in
 * @subns: whether to match subns components
 * @request: permission request
 * @perms: Returns computed perms (NOT शून्य)
 *
 * Returns: the state the match finished in, may be the none matching state
 */
अटल पूर्णांक label_match(काष्ठा aa_profile *profile, काष्ठा aa_label *label,
		       bool stack, अचिन्हित पूर्णांक state, bool subns, u32 request,
		       काष्ठा aa_perms *perms)
अणु
	पूर्णांक error;

	*perms = nullperms;
	error = label_compound_match(profile, label, stack, state, subns,
				     request, perms);
	अगर (!error)
		वापस error;

	*perms = allperms;
	वापस label_components_match(profile, label, stack, state, subns,
				      request, perms);
पूर्ण

/******* end TODO: dedup *****/

/**
 * change_profile_perms - find permissions क्रम change_profile
 * @profile: the current profile  (NOT शून्य)
 * @target: label to transition to (NOT शून्य)
 * @stack: whether this is a stacking request
 * @request: requested perms
 * @start: state to start matching in
 *
 *
 * Returns: permission set
 *
 * currently only matches full label A//&B//&C or inभागidual components A, B, C
 * not arbitrary combinations. Eg. A//&B, C
 */
अटल पूर्णांक change_profile_perms(काष्ठा aa_profile *profile,
				काष्ठा aa_label *target, bool stack,
				u32 request, अचिन्हित पूर्णांक start,
				काष्ठा aa_perms *perms)
अणु
	अगर (profile_unconfined(profile)) अणु
		perms->allow = AA_MAY_CHANGE_PROखाता | AA_MAY_ONEXEC;
		perms->audit = perms->quiet = perms->समाप्त = 0;
		वापस 0;
	पूर्ण

	/* TODO: add profile in ns screening */
	वापस label_match(profile, target, stack, start, true, request, perms);
पूर्ण

/**
 * aa_xattrs_match - check whether a file matches the xattrs defined in profile
 * @bprm: binprm काष्ठा क्रम the process to validate
 * @profile: profile to match against (NOT शून्य)
 * @state: state to start match in
 *
 * Returns: number of extended attributes that matched, or < 0 on error
 */
अटल पूर्णांक aa_xattrs_match(स्थिर काष्ठा linux_binprm *bprm,
			   काष्ठा aa_profile *profile, अचिन्हित पूर्णांक state)
अणु
	पूर्णांक i;
	sमाप_प्रकार size;
	काष्ठा dentry *d;
	अक्षर *value = शून्य;
	पूर्णांक value_size = 0, ret = profile->xattr_count;

	अगर (!bprm || !profile->xattr_count)
		वापस 0;
	might_sleep();

	/* transition from exec match to xattr set */
	state = aa_dfa_outofband_transition(profile->xmatch, state);
	d = bprm->file->f_path.dentry;

	क्रम (i = 0; i < profile->xattr_count; i++) अणु
		size = vfs_getxattr_alloc(&init_user_ns, d, profile->xattrs[i],
					  &value, value_size, GFP_KERNEL);
		अगर (size >= 0) अणु
			u32 perm;

			/*
			 * Check the xattr presence beक्रमe value. This ensure
			 * that not present xattr can be distinguished from a 0
			 * length value or rule that matches any value
			 */
			state = aa_dfa_null_transition(profile->xmatch, state);
			/* Check xattr value */
			state = aa_dfa_match_len(profile->xmatch, state, value,
						 size);
			perm = dfa_user_allow(profile->xmatch, state);
			अगर (!(perm & MAY_EXEC)) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
		पूर्ण
		/* transition to next element */
		state = aa_dfa_outofband_transition(profile->xmatch, state);
		अगर (size < 0) अणु
			/*
			 * No xattr match, so verअगरy अगर transition to
			 * next element was valid. IFF so the xattr
			 * was optional.
			 */
			अगर (!state) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण
			/* करोn't count missing optional xattr as matched */
			ret--;
		पूर्ण
	पूर्ण

out:
	kमुक्त(value);
	वापस ret;
पूर्ण

/**
 * find_attach - करो attachment search क्रम unconfined processes
 * @bprm - binprm काष्ठाure of transitioning task
 * @ns: the current namespace  (NOT शून्य)
 * @head - profile list to walk  (NOT शून्य)
 * @name - to match against  (NOT शून्य)
 * @info - info message अगर there was an error (NOT शून्य)
 *
 * Do a linear search on the profiles in the list.  There is a matching
 * preference where an exact match is preferred over a name which uses
 * expressions to match, and matching expressions with the greatest
 * xmatch_len are preferred.
 *
 * Requires: @head not be shared or have appropriate locks held
 *
 * Returns: label or शून्य अगर no match found
 */
अटल काष्ठा aa_label *find_attach(स्थिर काष्ठा linux_binprm *bprm,
				    काष्ठा aa_ns *ns, काष्ठा list_head *head,
				    स्थिर अक्षर *name, स्थिर अक्षर **info)
अणु
	पूर्णांक candidate_len = 0, candidate_xattrs = 0;
	bool conflict = false;
	काष्ठा aa_profile *profile, *candidate = शून्य;

	AA_BUG(!name);
	AA_BUG(!head);

	rcu_पढ़ो_lock();
restart:
	list_क्रम_each_entry_rcu(profile, head, base.list) अणु
		अगर (profile->label.flags & FLAG_शून्य &&
		    &profile->label == ns_unconfined(profile->ns))
			जारी;

		/* Find the "best" matching profile. Profiles must
		 * match the path and extended attributes (अगर any)
		 * associated with the file. A more specअगरic path
		 * match will be preferred over a less specअगरic one,
		 * and a match with more matching extended attributes
		 * will be preferred over one with fewer. If the best
		 * match has both the same level of path specअगरicity
		 * and the same number of matching extended attributes
		 * as another profile, संकेत a conflict and refuse to
		 * match.
		 */
		अगर (profile->xmatch) अणु
			अचिन्हित पूर्णांक state, count;
			u32 perm;

			state = aa_dfa_lefपंचांगatch(profile->xmatch, DFA_START,
						 name, &count);
			perm = dfa_user_allow(profile->xmatch, state);
			/* any accepting state means a valid match. */
			अगर (perm & MAY_EXEC) अणु
				पूर्णांक ret = 0;

				अगर (count < candidate_len)
					जारी;

				अगर (bprm && profile->xattr_count) अणु
					दीर्घ rev = READ_ONCE(ns->revision);

					अगर (!aa_get_profile_not0(profile))
						जाओ restart;
					rcu_पढ़ो_unlock();
					ret = aa_xattrs_match(bprm, profile,
							      state);
					rcu_पढ़ो_lock();
					aa_put_profile(profile);
					अगर (rev !=
					    READ_ONCE(ns->revision))
						/* policy changed */
						जाओ restart;
					/*
					 * Fail matching अगर the xattrs करोn't
					 * match
					 */
					अगर (ret < 0)
						जारी;
				पूर्ण
				/*
				 * TODO: allow क्रम more flexible best match
				 *
				 * The new match isn't more specअगरic
				 * than the current best match
				 */
				अगर (count == candidate_len &&
				    ret <= candidate_xattrs) अणु
					/* Match is equivalent, so conflict */
					अगर (ret == candidate_xattrs)
						conflict = true;
					जारी;
				पूर्ण

				/* Either the same length with more matching
				 * xattrs, or a दीर्घer match
				 */
				candidate = profile;
				candidate_len = profile->xmatch_len;
				candidate_xattrs = ret;
				conflict = false;
			पूर्ण
		पूर्ण अन्यथा अगर (!म_भेद(profile->base.name, name)) अणु
			/*
			 * old exact non-re match, without conditionals such
			 * as xattrs. no more searching required
			 */
			candidate = profile;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!candidate || conflict) अणु
		अगर (conflict)
			*info = "conflicting profile attachments";
		rcu_पढ़ो_unlock();
		वापस शून्य;
	पूर्ण

out:
	candidate = aa_get_newest_profile(candidate);
	rcu_पढ़ो_unlock();

	वापस &candidate->label;
पूर्ण

अटल स्थिर अक्षर *next_name(पूर्णांक xtype, स्थिर अक्षर *name)
अणु
	वापस शून्य;
पूर्ण

/**
 * x_table_lookup - lookup an x transition name via transition table
 * @profile: current profile (NOT शून्य)
 * @xindex: index पूर्णांकo x transition table
 * @name: वापसs: name tested to find label (NOT शून्य)
 *
 * Returns: refcounted label, or शून्य on failure (MAYBE शून्य)
 */
काष्ठा aa_label *x_table_lookup(काष्ठा aa_profile *profile, u32 xindex,
				स्थिर अक्षर **name)
अणु
	काष्ठा aa_label *label = शून्य;
	u32 xtype = xindex & AA_X_TYPE_MASK;
	पूर्णांक index = xindex & AA_X_INDEX_MASK;

	AA_BUG(!name);

	/* index is guaranteed to be in range, validated at load समय */
	/* TODO: move lookup parsing to unpack समय so this is a straight
	 *       index पूर्णांकo the resultant label
	 */
	क्रम (*name = profile->file.trans.table[index]; !label && *name;
	     *name = next_name(xtype, *name)) अणु
		अगर (xindex & AA_X_CHILD) अणु
			काष्ठा aa_profile *new_profile;
			/* release by caller */
			new_profile = aa_find_child(profile, *name);
			अगर (new_profile)
				label = &new_profile->label;
			जारी;
		पूर्ण
		label = aa_label_parse(&profile->label, *name, GFP_KERNEL,
				       true, false);
		अगर (IS_ERR(label))
			label = शून्य;
	पूर्ण

	/* released by caller */

	वापस label;
पूर्ण

/**
 * x_to_label - get target label क्रम a given xindex
 * @profile: current profile  (NOT शून्य)
 * @bprm: binprm काष्ठाure of transitioning task
 * @name: name to lookup (NOT शून्य)
 * @xindex: index पूर्णांकo x transition table
 * @lookupname: वापसs: name used in lookup अगर one was specअगरied (NOT शून्य)
 *
 * find label क्रम a transition index
 *
 * Returns: refcounted label or शून्य अगर not found available
 */
अटल काष्ठा aa_label *x_to_label(काष्ठा aa_profile *profile,
				   स्थिर काष्ठा linux_binprm *bprm,
				   स्थिर अक्षर *name, u32 xindex,
				   स्थिर अक्षर **lookupname,
				   स्थिर अक्षर **info)
अणु
	काष्ठा aa_label *new = शून्य;
	काष्ठा aa_ns *ns = profile->ns;
	u32 xtype = xindex & AA_X_TYPE_MASK;
	स्थिर अक्षर *stack = शून्य;

	चयन (xtype) अणु
	हाल AA_X_NONE:
		/* fail exec unless ix || ux fallback - handled by caller */
		*lookupname = शून्य;
		अवरोध;
	हाल AA_X_TABLE:
		/* TODO: fix when perm mapping करोne at unload */
		stack = profile->file.trans.table[xindex & AA_X_INDEX_MASK];
		अगर (*stack != '&') अणु
			/* released by caller */
			new = x_table_lookup(profile, xindex, lookupname);
			stack = शून्य;
			अवरोध;
		पूर्ण
		fallthrough;	/* to X_NAME */
	हाल AA_X_NAME:
		अगर (xindex & AA_X_CHILD)
			/* released by caller */
			new = find_attach(bprm, ns, &profile->base.profiles,
					  name, info);
		अन्यथा
			/* released by caller */
			new = find_attach(bprm, ns, &ns->base.profiles,
					  name, info);
		*lookupname = name;
		अवरोध;
	पूर्ण

	अगर (!new) अणु
		अगर (xindex & AA_X_INHERIT) अणु
			/* (p|c|n)ix - करोn't change profile but करो
			 * use the newest version
			 */
			*info = "ix fallback";
			/* no profile && no error */
			new = aa_get_newest_label(&profile->label);
		पूर्ण अन्यथा अगर (xindex & AA_X_UNCONFINED) अणु
			new = aa_get_newest_label(ns_unconfined(profile->ns));
			*info = "ux fallback";
		पूर्ण
	पूर्ण

	अगर (new && stack) अणु
		/* base the stack on post करोमुख्य transition */
		काष्ठा aa_label *base = new;

		new = aa_label_parse(base, stack, GFP_KERNEL, true, false);
		अगर (IS_ERR(new))
			new = शून्य;
		aa_put_label(base);
	पूर्ण

	/* released by caller */
	वापस new;
पूर्ण

अटल काष्ठा aa_label *profile_transition(काष्ठा aa_profile *profile,
					   स्थिर काष्ठा linux_binprm *bprm,
					   अक्षर *buffer, काष्ठा path_cond *cond,
					   bool *secure_exec)
अणु
	काष्ठा aa_label *new = शून्य;
	स्थिर अक्षर *info = शून्य, *name = शून्य, *target = शून्य;
	अचिन्हित पूर्णांक state = profile->file.start;
	काष्ठा aa_perms perms = अणुपूर्ण;
	bool nonewprivs = false;
	पूर्णांक error = 0;

	AA_BUG(!profile);
	AA_BUG(!bprm);
	AA_BUG(!buffer);

	error = aa_path_name(&bprm->file->f_path, profile->path_flags, buffer,
			     &name, &info, profile->disconnected);
	अगर (error) अणु
		अगर (profile_unconfined(profile) ||
		    (profile->label.flags & FLAG_IX_ON_NAME_ERROR)) अणु
			AA_DEBUG("name lookup ix on error");
			error = 0;
			new = aa_get_newest_label(&profile->label);
		पूर्ण
		name = bprm->filename;
		जाओ audit;
	पूर्ण

	अगर (profile_unconfined(profile)) अणु
		new = find_attach(bprm, profile->ns,
				  &profile->ns->base.profiles, name, &info);
		अगर (new) अणु
			AA_DEBUG("unconfined attached to new label");
			वापस new;
		पूर्ण
		AA_DEBUG("unconfined exec no attachment");
		वापस aa_get_newest_label(&profile->label);
	पूर्ण

	/* find exec permissions क्रम name */
	state = aa_str_perms(profile->file.dfa, state, name, cond, &perms);
	अगर (perms.allow & MAY_EXEC) अणु
		/* exec permission determine how to transition */
		new = x_to_label(profile, bprm, name, perms.xindex, &target,
				 &info);
		अगर (new && new->proxy == profile->label.proxy && info) अणु
			/* hack ix fallback - improve how this is detected */
			जाओ audit;
		पूर्ण अन्यथा अगर (!new) अणु
			error = -EACCES;
			info = "profile transition not found";
			/* हटाओ MAY_EXEC to audit as failure */
			perms.allow &= ~MAY_EXEC;
		पूर्ण
	पूर्ण अन्यथा अगर (COMPLAIN_MODE(profile)) अणु
		/* no exec permission - learning mode */
		काष्ठा aa_profile *new_profile = शून्य;

		new_profile = aa_new_null_profile(profile, false, name,
						  GFP_KERNEL);
		अगर (!new_profile) अणु
			error = -ENOMEM;
			info = "could not create null profile";
		पूर्ण अन्यथा अणु
			error = -EACCES;
			new = &new_profile->label;
		पूर्ण
		perms.xindex |= AA_X_UNSAFE;
	पूर्ण अन्यथा
		/* fail exec */
		error = -EACCES;

	अगर (!new)
		जाओ audit;


	अगर (!(perms.xindex & AA_X_UNSAFE)) अणु
		अगर (DEBUG_ON) अणु
			dbg_prपूर्णांकk("apparmor: scrubbing environment variables"
				   " for %s profile=", name);
			aa_label_prपूर्णांकk(new, GFP_KERNEL);
			dbg_prपूर्णांकk("\n");
		पूर्ण
		*secure_exec = true;
	पूर्ण

audit:
	aa_audit_file(profile, &perms, OP_EXEC, MAY_EXEC, name, target, new,
		      cond->uid, info, error);
	अगर (!new || nonewprivs) अणु
		aa_put_label(new);
		वापस ERR_PTR(error);
	पूर्ण

	वापस new;
पूर्ण

अटल पूर्णांक profile_onexec(काष्ठा aa_profile *profile, काष्ठा aa_label *onexec,
			  bool stack, स्थिर काष्ठा linux_binprm *bprm,
			  अक्षर *buffer, काष्ठा path_cond *cond,
			  bool *secure_exec)
अणु
	अचिन्हित पूर्णांक state = profile->file.start;
	काष्ठा aa_perms perms = अणुपूर्ण;
	स्थिर अक्षर *xname = शून्य, *info = "change_profile onexec";
	पूर्णांक error = -EACCES;

	AA_BUG(!profile);
	AA_BUG(!onexec);
	AA_BUG(!bprm);
	AA_BUG(!buffer);

	अगर (profile_unconfined(profile)) अणु
		/* change_profile on exec alपढ़ोy granted */
		/*
		 * NOTE: Doमुख्य transitions from unconfined are allowed
		 * even when no_new_privs is set because this aways results
		 * in a further reduction of permissions.
		 */
		वापस 0;
	पूर्ण

	error = aa_path_name(&bprm->file->f_path, profile->path_flags, buffer,
			     &xname, &info, profile->disconnected);
	अगर (error) अणु
		अगर (profile_unconfined(profile) ||
		    (profile->label.flags & FLAG_IX_ON_NAME_ERROR)) अणु
			AA_DEBUG("name lookup ix on error");
			error = 0;
		पूर्ण
		xname = bprm->filename;
		जाओ audit;
	पूर्ण

	/* find exec permissions क्रम name */
	state = aa_str_perms(profile->file.dfa, state, xname, cond, &perms);
	अगर (!(perms.allow & AA_MAY_ONEXEC)) अणु
		info = "no change_onexec valid for executable";
		जाओ audit;
	पूर्ण
	/* test अगर this exec can be paired with change_profile onexec.
	 * onexec permission is linked to exec with a standard pairing
	 * exec\0change_profile
	 */
	state = aa_dfa_null_transition(profile->file.dfa, state);
	error = change_profile_perms(profile, onexec, stack, AA_MAY_ONEXEC,
				     state, &perms);
	अगर (error) अणु
		perms.allow &= ~AA_MAY_ONEXEC;
		जाओ audit;
	पूर्ण

	अगर (!(perms.xindex & AA_X_UNSAFE)) अणु
		अगर (DEBUG_ON) अणु
			dbg_prपूर्णांकk("apparmor: scrubbing environment "
				   "variables for %s label=", xname);
			aa_label_prपूर्णांकk(onexec, GFP_KERNEL);
			dbg_prपूर्णांकk("\n");
		पूर्ण
		*secure_exec = true;
	पूर्ण

audit:
	वापस aa_audit_file(profile, &perms, OP_EXEC, AA_MAY_ONEXEC, xname,
			     शून्य, onexec, cond->uid, info, error);
पूर्ण

/* ensure none ns करोमुख्य transitions are correctly applied with onexec */

अटल काष्ठा aa_label *handle_onexec(काष्ठा aa_label *label,
				      काष्ठा aa_label *onexec, bool stack,
				      स्थिर काष्ठा linux_binprm *bprm,
				      अक्षर *buffer, काष्ठा path_cond *cond,
				      bool *unsafe)
अणु
	काष्ठा aa_profile *profile;
	काष्ठा aa_label *new;
	पूर्णांक error;

	AA_BUG(!label);
	AA_BUG(!onexec);
	AA_BUG(!bprm);
	AA_BUG(!buffer);

	अगर (!stack) अणु
		error = fn_क्रम_each_in_ns(label, profile,
				profile_onexec(profile, onexec, stack,
					       bprm, buffer, cond, unsafe));
		अगर (error)
			वापस ERR_PTR(error);
		new = fn_label_build_in_ns(label, profile, GFP_KERNEL,
				aa_get_newest_label(onexec),
				profile_transition(profile, bprm, buffer,
						   cond, unsafe));

	पूर्ण अन्यथा अणु
		/* TODO: determine how much we want to loosen this */
		error = fn_क्रम_each_in_ns(label, profile,
				profile_onexec(profile, onexec, stack, bprm,
					       buffer, cond, unsafe));
		अगर (error)
			वापस ERR_PTR(error);
		new = fn_label_build_in_ns(label, profile, GFP_KERNEL,
				aa_label_merge(&profile->label, onexec,
					       GFP_KERNEL),
				profile_transition(profile, bprm, buffer,
						   cond, unsafe));
	पूर्ण

	अगर (new)
		वापस new;

	/* TODO: get rid of GLOBAL_ROOT_UID */
	error = fn_क्रम_each_in_ns(label, profile,
			aa_audit_file(profile, &nullperms, OP_CHANGE_ONEXEC,
				      AA_MAY_ONEXEC, bprm->filename, शून्य,
				      onexec, GLOBAL_ROOT_UID,
				      "failed to build target label", -ENOMEM));
	वापस ERR_PTR(error);
पूर्ण

/**
 * apparmor_bprm_creds_क्रम_exec - Update the new creds on the bprm काष्ठा
 * @bprm: binprm क्रम the exec  (NOT शून्य)
 *
 * Returns: %0 or error on failure
 *
 * TODO: once the other paths are करोne see अगर we can't refactor पूर्णांकo a fn
 */
पूर्णांक apparmor_bprm_creds_क्रम_exec(काष्ठा linux_binprm *bprm)
अणु
	काष्ठा aa_task_ctx *ctx;
	काष्ठा aa_label *label, *new = शून्य;
	काष्ठा aa_profile *profile;
	अक्षर *buffer = शून्य;
	स्थिर अक्षर *info = शून्य;
	पूर्णांक error = 0;
	bool unsafe = false;
	kuid_t i_uid = i_uid_पूर्णांकo_mnt(file_mnt_user_ns(bprm->file),
				      file_inode(bprm->file));
	काष्ठा path_cond cond = अणु
		i_uid,
		file_inode(bprm->file)->i_mode
	पूर्ण;

	ctx = task_ctx(current);
	AA_BUG(!cred_label(bprm->cred));
	AA_BUG(!ctx);

	label = aa_get_newest_label(cred_label(bprm->cred));

	/*
	 * Detect no new privs being set, and store the label it
	 * occurred under. Ideally this would happen when nnp
	 * is set but there isn't a good way to करो that yet.
	 *
	 * Testing क्रम unconfined must be करोne beक्रमe the subset test
	 */
	अगर ((bprm->unsafe & LSM_UNSAFE_NO_NEW_PRIVS) && !unconfined(label) &&
	    !ctx->nnp)
		ctx->nnp = aa_get_label(label);

	/* buffer मुक्तd below, name is poपूर्णांकer पूर्णांकo buffer */
	buffer = aa_get_buffer(false);
	अगर (!buffer) अणु
		error = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* Test क्रम onexec first as onexec override other x transitions. */
	अगर (ctx->onexec)
		new = handle_onexec(label, ctx->onexec, ctx->token,
				    bprm, buffer, &cond, &unsafe);
	अन्यथा
		new = fn_label_build(label, profile, GFP_KERNEL,
				profile_transition(profile, bprm, buffer,
						   &cond, &unsafe));

	AA_BUG(!new);
	अगर (IS_ERR(new)) अणु
		error = PTR_ERR(new);
		जाओ करोne;
	पूर्ण अन्यथा अगर (!new) अणु
		error = -ENOMEM;
		जाओ करोne;
	पूर्ण

	/* Policy has specअगरied a करोमुख्य transitions. If no_new_privs and
	 * confined ensure the transition is to confinement that is subset
	 * of the confinement when the task entered no new privs.
	 *
	 * NOTE: Doमुख्य transitions from unconfined and to stacked
	 * subsets are allowed even when no_new_privs is set because this
	 * aways results in a further reduction of permissions.
	 */
	अगर ((bprm->unsafe & LSM_UNSAFE_NO_NEW_PRIVS) &&
	    !unconfined(label) &&
	    !aa_label_is_unconfined_subset(new, ctx->nnp)) अणु
		error = -EPERM;
		info = "no new privs";
		जाओ audit;
	पूर्ण

	अगर (bprm->unsafe & LSM_UNSAFE_SHARE) अणु
		/* FIXME: currently करोn't mediate shared state */
		;
	पूर्ण

	अगर (bprm->unsafe & (LSM_UNSAFE_PTRACE)) अणु
		/* TODO: test needs to be profile of label to new */
		error = may_change_ptraced_करोमुख्य(new, &info);
		अगर (error)
			जाओ audit;
	पूर्ण

	अगर (unsafe) अणु
		अगर (DEBUG_ON) अणु
			dbg_prपूर्णांकk("scrubbing environment variables for %s "
				   "label=", bprm->filename);
			aa_label_prपूर्णांकk(new, GFP_KERNEL);
			dbg_prपूर्णांकk("\n");
		पूर्ण
		bprm->secureexec = 1;
	पूर्ण

	अगर (label->proxy != new->proxy) अणु
		/* when transitioning clear unsafe personality bits */
		अगर (DEBUG_ON) अणु
			dbg_prपूर्णांकk("apparmor: clearing unsafe personality "
				   "bits. %s label=", bprm->filename);
			aa_label_prपूर्णांकk(new, GFP_KERNEL);
			dbg_prपूर्णांकk("\n");
		पूर्ण
		bprm->per_clear |= PER_CLEAR_ON_SETID;
	पूर्ण
	aa_put_label(cred_label(bprm->cred));
	/* transfer reference, released when cred is मुक्तd */
	set_cred_label(bprm->cred, new);

करोne:
	aa_put_label(label);
	aa_put_buffer(buffer);

	वापस error;

audit:
	error = fn_क्रम_each(label, profile,
			aa_audit_file(profile, &nullperms, OP_EXEC, MAY_EXEC,
				      bprm->filename, शून्य, new,
				      i_uid, info, error));
	aa_put_label(new);
	जाओ करोne;
पूर्ण

/*
 * Functions क्रम self directed profile change
 */


/* helper fn क्रम change_hat
 *
 * Returns: label क्रम hat transition OR ERR_PTR.  Does NOT वापस शून्य
 */
अटल काष्ठा aa_label *build_change_hat(काष्ठा aa_profile *profile,
					 स्थिर अक्षर *name, bool sibling)
अणु
	काष्ठा aa_profile *root, *hat = शून्य;
	स्थिर अक्षर *info = शून्य;
	पूर्णांक error = 0;

	अगर (sibling && PROखाता_IS_HAT(profile)) अणु
		root = aa_get_profile_rcu(&profile->parent);
	पूर्ण अन्यथा अगर (!sibling && !PROखाता_IS_HAT(profile)) अणु
		root = aa_get_profile(profile);
	पूर्ण अन्यथा अणु
		info = "conflicting target types";
		error = -EPERM;
		जाओ audit;
	पूर्ण

	hat = aa_find_child(root, name);
	अगर (!hat) अणु
		error = -ENOENT;
		अगर (COMPLAIN_MODE(profile)) अणु
			hat = aa_new_null_profile(profile, true, name,
						  GFP_KERNEL);
			अगर (!hat) अणु
				info = "failed null profile create";
				error = -ENOMEM;
			पूर्ण
		पूर्ण
	पूर्ण
	aa_put_profile(root);

audit:
	aa_audit_file(profile, &nullperms, OP_CHANGE_HAT, AA_MAY_CHANGEHAT,
		      name, hat ? hat->base.hname : शून्य,
		      hat ? &hat->label : शून्य, GLOBAL_ROOT_UID, info,
		      error);
	अगर (!hat || (error && error != -ENOENT))
		वापस ERR_PTR(error);
	/* अगर hat && error - complain mode, alपढ़ोy audited and we adjust क्रम
	 * complain mode allow by वापसing hat->label
	 */
	वापस &hat->label;
पूर्ण

/* helper fn क्रम changing पूर्णांकo a hat
 *
 * Returns: label क्रम hat transition or ERR_PTR. Does not वापस शून्य
 */
अटल काष्ठा aa_label *change_hat(काष्ठा aa_label *label, स्थिर अक्षर *hats[],
				   पूर्णांक count, पूर्णांक flags)
अणु
	काष्ठा aa_profile *profile, *root, *hat = शून्य;
	काष्ठा aa_label *new;
	काष्ठा label_it it;
	bool sibling = false;
	स्थिर अक्षर *name, *info = शून्य;
	पूर्णांक i, error;

	AA_BUG(!label);
	AA_BUG(!hats);
	AA_BUG(count < 1);

	अगर (PROखाता_IS_HAT(labels_profile(label)))
		sibling = true;

	/*find first matching hat */
	क्रम (i = 0; i < count && !hat; i++) अणु
		name = hats[i];
		label_क्रम_each_in_ns(it, labels_ns(label), label, profile) अणु
			अगर (sibling && PROखाता_IS_HAT(profile)) अणु
				root = aa_get_profile_rcu(&profile->parent);
			पूर्ण अन्यथा अगर (!sibling && !PROखाता_IS_HAT(profile)) अणु
				root = aa_get_profile(profile);
			पूर्ण अन्यथा अणु	/* conflicting change type */
				info = "conflicting targets types";
				error = -EPERM;
				जाओ fail;
			पूर्ण
			hat = aa_find_child(root, name);
			aa_put_profile(root);
			अगर (!hat) अणु
				अगर (!COMPLAIN_MODE(profile))
					जाओ outer_जारी;
				/* complain mode succeed as अगर hat */
			पूर्ण अन्यथा अगर (!PROखाता_IS_HAT(hat)) अणु
				info = "target not hat";
				error = -EPERM;
				aa_put_profile(hat);
				जाओ fail;
			पूर्ण
			aa_put_profile(hat);
		पूर्ण
		/* found a hat क्रम all profiles in ns */
		जाओ build;
outer_जारी:
	;
	पूर्ण
	/* no hats that match, find appropriate error
	 *
	 * In complain mode audit of the failure is based off of the first
	 * hat supplied.  This is करोne due how userspace पूर्णांकeracts with
	 * change_hat.
	 */
	name = शून्य;
	label_क्रम_each_in_ns(it, labels_ns(label), label, profile) अणु
		अगर (!list_empty(&profile->base.profiles)) अणु
			info = "hat not found";
			error = -ENOENT;
			जाओ fail;
		पूर्ण
	पूर्ण
	info = "no hats defined";
	error = -ECHILD;

fail:
	label_क्रम_each_in_ns(it, labels_ns(label), label, profile) अणु
		/*
		 * no target as it has failed to be found or built
		 *
		 * change_hat uses probing and should not log failures
		 * related to missing hats
		 */
		/* TODO: get rid of GLOBAL_ROOT_UID */
		अगर (count > 1 || COMPLAIN_MODE(profile)) अणु
			aa_audit_file(profile, &nullperms, OP_CHANGE_HAT,
				      AA_MAY_CHANGEHAT, name, शून्य, शून्य,
				      GLOBAL_ROOT_UID, info, error);
		पूर्ण
	पूर्ण
	वापस ERR_PTR(error);

build:
	new = fn_label_build_in_ns(label, profile, GFP_KERNEL,
				   build_change_hat(profile, name, sibling),
				   aa_get_label(&profile->label));
	अगर (!new) अणु
		info = "label build failed";
		error = -ENOMEM;
		जाओ fail;
	पूर्ण /* अन्यथा अगर (IS_ERR) build_change_hat has logged error so वापस new */

	वापस new;
पूर्ण

/**
 * aa_change_hat - change hat to/from subprofile
 * @hats: vector of hat names to try changing पूर्णांकo (MAYBE शून्य अगर @count == 0)
 * @count: number of hat names in @hats
 * @token: magic value to validate the hat change
 * @flags: flags affecting behavior of the change
 *
 * Returns %0 on success, error otherwise.
 *
 * Change to the first profile specअगरied in @hats that exists, and store
 * the @hat_magic in the current task context.  If the count == 0 and the
 * @token matches that stored in the current task context, वापस to the
 * top level profile.
 *
 * change_hat only applies to profiles in the current ns, and each profile
 * in the ns must make the same transition otherwise change_hat will fail.
 */
पूर्णांक aa_change_hat(स्थिर अक्षर *hats[], पूर्णांक count, u64 token, पूर्णांक flags)
अणु
	स्थिर काष्ठा cred *cred;
	काष्ठा aa_task_ctx *ctx = task_ctx(current);
	काष्ठा aa_label *label, *previous, *new = शून्य, *target = शून्य;
	काष्ठा aa_profile *profile;
	काष्ठा aa_perms perms = अणुपूर्ण;
	स्थिर अक्षर *info = शून्य;
	पूर्णांक error = 0;

	/* released below */
	cred = get_current_cred();
	label = aa_get_newest_cred_label(cred);
	previous = aa_get_newest_label(ctx->previous);

	/*
	 * Detect no new privs being set, and store the label it
	 * occurred under. Ideally this would happen when nnp
	 * is set but there isn't a good way to करो that yet.
	 *
	 * Testing क्रम unconfined must be करोne beक्रमe the subset test
	 */
	अगर (task_no_new_privs(current) && !unconfined(label) && !ctx->nnp)
		ctx->nnp = aa_get_label(label);

	अगर (unconfined(label)) अणु
		info = "unconfined can not change_hat";
		error = -EPERM;
		जाओ fail;
	पूर्ण

	अगर (count) अणु
		new = change_hat(label, hats, count, flags);
		AA_BUG(!new);
		अगर (IS_ERR(new)) अणु
			error = PTR_ERR(new);
			new = शून्य;
			/* alपढ़ोy audited */
			जाओ out;
		पूर्ण

		error = may_change_ptraced_करोमुख्य(new, &info);
		अगर (error)
			जाओ fail;

		/*
		 * no new privs prevents करोमुख्य transitions that would
		 * reduce restrictions.
		 */
		अगर (task_no_new_privs(current) && !unconfined(label) &&
		    !aa_label_is_unconfined_subset(new, ctx->nnp)) अणु
			/* not an apparmor denial per se, so करोn't log it */
			AA_DEBUG("no_new_privs - change_hat denied");
			error = -EPERM;
			जाओ out;
		पूर्ण

		अगर (flags & AA_CHANGE_TEST)
			जाओ out;

		target = new;
		error = aa_set_current_hat(new, token);
		अगर (error == -EACCES)
			/* समाप्त task in हाल of brute क्रमce attacks */
			जाओ समाप्त;
	पूर्ण अन्यथा अगर (previous && !(flags & AA_CHANGE_TEST)) अणु
		/*
		 * no new privs prevents करोमुख्य transitions that would
		 * reduce restrictions.
		 */
		अगर (task_no_new_privs(current) && !unconfined(label) &&
		    !aa_label_is_unconfined_subset(previous, ctx->nnp)) अणु
			/* not an apparmor denial per se, so करोn't log it */
			AA_DEBUG("no_new_privs - change_hat denied");
			error = -EPERM;
			जाओ out;
		पूर्ण

		/* Return to saved label.  Kill task अगर restore fails
		 * to aव्योम brute क्रमce attacks
		 */
		target = previous;
		error = aa_restore_previous_label(token);
		अगर (error) अणु
			अगर (error == -EACCES)
				जाओ समाप्त;
			जाओ fail;
		पूर्ण
	पूर्ण /* अन्यथा ignore @flags && restores when there is no saved profile */

out:
	aa_put_label(new);
	aa_put_label(previous);
	aa_put_label(label);
	put_cred(cred);

	वापस error;

समाप्त:
	info = "failed token match";
	perms.समाप्त = AA_MAY_CHANGEHAT;

fail:
	fn_क्रम_each_in_ns(label, profile,
		aa_audit_file(profile, &perms, OP_CHANGE_HAT,
			      AA_MAY_CHANGEHAT, शून्य, शून्य, target,
			      GLOBAL_ROOT_UID, info, error));

	जाओ out;
पूर्ण


अटल पूर्णांक change_profile_perms_wrapper(स्थिर अक्षर *op, स्थिर अक्षर *name,
					काष्ठा aa_profile *profile,
					काष्ठा aa_label *target, bool stack,
					u32 request, काष्ठा aa_perms *perms)
अणु
	स्थिर अक्षर *info = शून्य;
	पूर्णांक error = 0;

	अगर (!error)
		error = change_profile_perms(profile, target, stack, request,
					     profile->file.start, perms);
	अगर (error)
		error = aa_audit_file(profile, perms, op, request, name,
				      शून्य, target, GLOBAL_ROOT_UID, info,
				      error);

	वापस error;
पूर्ण

/**
 * aa_change_profile - perक्रमm a one-way profile transition
 * @fqname: name of profile may include namespace (NOT शून्य)
 * @onexec: whether this transition is to take place immediately or at exec
 * @flags: flags affecting change behavior
 *
 * Change to new profile @name.  Unlike with hats, there is no way
 * to change back.  If @name isn't specअगरied the current profile name is
 * used.
 * If @onexec then the transition is delayed until
 * the next exec.
 *
 * Returns %0 on success, error otherwise.
 */
पूर्णांक aa_change_profile(स्थिर अक्षर *fqname, पूर्णांक flags)
अणु
	काष्ठा aa_label *label, *new = शून्य, *target = शून्य;
	काष्ठा aa_profile *profile;
	काष्ठा aa_perms perms = अणुपूर्ण;
	स्थिर अक्षर *info = शून्य;
	स्थिर अक्षर *auditname = fqname;		/* retain leading & अगर stack */
	bool stack = flags & AA_CHANGE_STACK;
	काष्ठा aa_task_ctx *ctx = task_ctx(current);
	पूर्णांक error = 0;
	अक्षर *op;
	u32 request;

	label = aa_get_current_label();

	/*
	 * Detect no new privs being set, and store the label it
	 * occurred under. Ideally this would happen when nnp
	 * is set but there isn't a good way to करो that yet.
	 *
	 * Testing क्रम unconfined must be करोne beक्रमe the subset test
	 */
	अगर (task_no_new_privs(current) && !unconfined(label) && !ctx->nnp)
		ctx->nnp = aa_get_label(label);

	अगर (!fqname || !*fqname) अणु
		aa_put_label(label);
		AA_DEBUG("no profile name");
		वापस -EINVAL;
	पूर्ण

	अगर (flags & AA_CHANGE_ONEXEC) अणु
		request = AA_MAY_ONEXEC;
		अगर (stack)
			op = OP_STACK_ONEXEC;
		अन्यथा
			op = OP_CHANGE_ONEXEC;
	पूर्ण अन्यथा अणु
		request = AA_MAY_CHANGE_PROखाता;
		अगर (stack)
			op = OP_STACK;
		अन्यथा
			op = OP_CHANGE_PROखाता;
	पूर्ण

	अगर (*fqname == '&') अणु
		stack = true;
		/* करोn't have label_parse() करो stacking */
		fqname++;
	पूर्ण
	target = aa_label_parse(label, fqname, GFP_KERNEL, true, false);
	अगर (IS_ERR(target)) अणु
		काष्ठा aa_profile *tprofile;

		info = "label not found";
		error = PTR_ERR(target);
		target = शून्य;
		/*
		 * TODO: fixme using labels_profile is not right - करो profile
		 * per complain profile
		 */
		अगर ((flags & AA_CHANGE_TEST) ||
		    !COMPLAIN_MODE(labels_profile(label)))
			जाओ audit;
		/* released below */
		tprofile = aa_new_null_profile(labels_profile(label), false,
					       fqname, GFP_KERNEL);
		अगर (!tprofile) अणु
			info = "failed null profile create";
			error = -ENOMEM;
			जाओ audit;
		पूर्ण
		target = &tprofile->label;
		जाओ check;
	पूर्ण

	/*
	 * self directed transitions only apply to current policy ns
	 * TODO: currently requiring perms क्रम stacking and straight change
	 *       stacking करोesn't strictly need this. Determine how much
	 *       we want to loosen this restriction क्रम stacking
	 *
	 * अगर (!stack) अणु
	 */
	error = fn_क्रम_each_in_ns(label, profile,
			change_profile_perms_wrapper(op, auditname,
						     profile, target, stack,
						     request, &perms));
	अगर (error)
		/* auditing करोne in change_profile_perms_wrapper */
		जाओ out;

	/* पूर्ण */

check:
	/* check अगर tracing task is allowed to trace target करोमुख्य */
	error = may_change_ptraced_करोमुख्य(target, &info);
	अगर (error && !fn_क्रम_each_in_ns(label, profile,
					COMPLAIN_MODE(profile)))
		जाओ audit;

	/* TODO: add permission check to allow this
	 * अगर ((flags & AA_CHANGE_ONEXEC) && !current_is_single_thपढ़ोed()) अणु
	 *      info = "not a single threaded task";
	 *      error = -EACCES;
	 *      जाओ audit;
	 * पूर्ण
	 */
	अगर (flags & AA_CHANGE_TEST)
		जाओ out;

	/* stacking is always a subset, so only check the nonstack हाल */
	अगर (!stack) अणु
		new = fn_label_build_in_ns(label, profile, GFP_KERNEL,
					   aa_get_label(target),
					   aa_get_label(&profile->label));
		/*
		 * no new privs prevents करोमुख्य transitions that would
		 * reduce restrictions.
		 */
		अगर (task_no_new_privs(current) && !unconfined(label) &&
		    !aa_label_is_unconfined_subset(new, ctx->nnp)) अणु
			/* not an apparmor denial per se, so करोn't log it */
			AA_DEBUG("no_new_privs - change_hat denied");
			error = -EPERM;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!(flags & AA_CHANGE_ONEXEC)) अणु
		/* only transition profiles in the current ns */
		अगर (stack)
			new = aa_label_merge(label, target, GFP_KERNEL);
		अगर (IS_ERR_OR_शून्य(new)) अणु
			info = "failed to build target label";
			अगर (!new)
				error = -ENOMEM;
			अन्यथा
				error = PTR_ERR(new);
			new = शून्य;
			perms.allow = 0;
			जाओ audit;
		पूर्ण
		error = aa_replace_current_label(new);
	पूर्ण अन्यथा अणु
		अगर (new) अणु
			aa_put_label(new);
			new = शून्य;
		पूर्ण

		/* full transition will be built in exec path */
		error = aa_set_current_onexec(target, stack);
	पूर्ण

audit:
	error = fn_क्रम_each_in_ns(label, profile,
			aa_audit_file(profile, &perms, op, request, auditname,
				      शून्य, new ? new : target,
				      GLOBAL_ROOT_UID, info, error));

out:
	aa_put_label(new);
	aa_put_label(target);
	aa_put_label(label);

	वापस error;
पूर्ण
