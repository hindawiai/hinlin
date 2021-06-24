<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor mediation of files
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#समावेश <linux/tty.h>
#समावेश <linux/fdtable.h>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/mount.h>

#समावेश "include/apparmor.h"
#समावेश "include/audit.h"
#समावेश "include/cred.h"
#समावेश "include/file.h"
#समावेश "include/match.h"
#समावेश "include/net.h"
#समावेश "include/path.h"
#समावेश "include/policy.h"
#समावेश "include/label.h"

अटल u32 map_mask_to_chr_mask(u32 mask)
अणु
	u32 m = mask & PERMS_CHRS_MASK;

	अगर (mask & AA_MAY_GETATTR)
		m |= MAY_READ;
	अगर (mask & (AA_MAY_SETATTR | AA_MAY_CHMOD | AA_MAY_CHOWN))
		m |= MAY_WRITE;

	वापस m;
पूर्ण

/**
 * file_audit_cb - call back क्रम file specअगरic audit fields
 * @ab: audit_buffer  (NOT शून्य)
 * @va: audit काष्ठा to audit values of  (NOT शून्य)
 */
अटल व्योम file_audit_cb(काष्ठा audit_buffer *ab, व्योम *va)
अणु
	काष्ठा common_audit_data *sa = va;
	kuid_t fsuid = current_fsuid();
	अक्षर str[10];

	अगर (aad(sa)->request & AA_AUDIT_खाता_MASK) अणु
		aa_perm_mask_to_str(str, माप(str), aa_file_perm_chrs,
				    map_mask_to_chr_mask(aad(sa)->request));
		audit_log_क्रमmat(ab, " requested_mask=\"%s\"", str);
	पूर्ण
	अगर (aad(sa)->denied & AA_AUDIT_खाता_MASK) अणु
		aa_perm_mask_to_str(str, माप(str), aa_file_perm_chrs,
				    map_mask_to_chr_mask(aad(sa)->denied));
		audit_log_क्रमmat(ab, " denied_mask=\"%s\"", str);
	पूर्ण
	अगर (aad(sa)->request & AA_AUDIT_खाता_MASK) अणु
		audit_log_क्रमmat(ab, " fsuid=%d",
				 from_kuid(&init_user_ns, fsuid));
		audit_log_क्रमmat(ab, " ouid=%d",
				 from_kuid(&init_user_ns, aad(sa)->fs.ouid));
	पूर्ण

	अगर (aad(sa)->peer) अणु
		audit_log_क्रमmat(ab, " target=");
		aa_label_xaudit(ab, labels_ns(aad(sa)->label), aad(sa)->peer,
				FLAG_VIEW_SUBNS, GFP_KERNEL);
	पूर्ण अन्यथा अगर (aad(sa)->fs.target) अणु
		audit_log_क्रमmat(ab, " target=");
		audit_log_untrustedstring(ab, aad(sa)->fs.target);
	पूर्ण
पूर्ण

/**
 * aa_audit_file - handle the auditing of file operations
 * @profile: the profile being enक्रमced  (NOT शून्य)
 * @perms: the permissions computed क्रम the request (NOT शून्य)
 * @op: operation being mediated
 * @request: permissions requested
 * @name: name of object being mediated (MAYBE शून्य)
 * @target: name of target (MAYBE शून्य)
 * @tlabel: target label (MAY BE शून्य)
 * @ouid: object uid
 * @info: extra inक्रमmation message (MAYBE शून्य)
 * @error: 0 अगर operation allowed अन्यथा failure error code
 *
 * Returns: %0 or error on failure
 */
पूर्णांक aa_audit_file(काष्ठा aa_profile *profile, काष्ठा aa_perms *perms,
		  स्थिर अक्षर *op, u32 request, स्थिर अक्षर *name,
		  स्थिर अक्षर *target, काष्ठा aa_label *tlabel,
		  kuid_t ouid, स्थिर अक्षर *info, पूर्णांक error)
अणु
	पूर्णांक type = AUDIT_APPARMOR_AUTO;
	DEFINE_AUDIT_DATA(sa, LSM_AUDIT_DATA_TASK, op);

	sa.u.tsk = शून्य;
	aad(&sa)->request = request;
	aad(&sa)->name = name;
	aad(&sa)->fs.target = target;
	aad(&sa)->peer = tlabel;
	aad(&sa)->fs.ouid = ouid;
	aad(&sa)->info = info;
	aad(&sa)->error = error;
	sa.u.tsk = शून्य;

	अगर (likely(!aad(&sa)->error)) अणु
		u32 mask = perms->audit;

		अगर (unlikely(AUDIT_MODE(profile) == AUDIT_ALL))
			mask = 0xffff;

		/* mask off perms that are not being क्रमce audited */
		aad(&sa)->request &= mask;

		अगर (likely(!aad(&sa)->request))
			वापस 0;
		type = AUDIT_APPARMOR_AUDIT;
	पूर्ण अन्यथा अणु
		/* only report permissions that were denied */
		aad(&sa)->request = aad(&sa)->request & ~perms->allow;
		AA_BUG(!aad(&sa)->request);

		अगर (aad(&sa)->request & perms->समाप्त)
			type = AUDIT_APPARMOR_KILL;

		/* quiet known rejects, assumes quiet and समाप्त करो not overlap */
		अगर ((aad(&sa)->request & perms->quiet) &&
		    AUDIT_MODE(profile) != AUDIT_NOQUIET &&
		    AUDIT_MODE(profile) != AUDIT_ALL)
			aad(&sa)->request &= ~perms->quiet;

		अगर (!aad(&sa)->request)
			वापस aad(&sa)->error;
	पूर्ण

	aad(&sa)->denied = aad(&sa)->request & ~perms->allow;
	वापस aa_audit(type, profile, &sa, file_audit_cb);
पूर्ण

/**
 * is_deleted - test अगर a file has been completely unlinked
 * @dentry: dentry of file to test क्रम deletion  (NOT शून्य)
 *
 * Returns: true अगर deleted अन्यथा false
 */
अटल अंतरभूत bool is_deleted(काष्ठा dentry *dentry)
अणु
	अगर (d_unlinked(dentry) && d_backing_inode(dentry)->i_nlink == 0)
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक path_name(स्थिर अक्षर *op, काष्ठा aa_label *label,
		     स्थिर काष्ठा path *path, पूर्णांक flags, अक्षर *buffer,
		     स्थिर अक्षर **name, काष्ठा path_cond *cond, u32 request)
अणु
	काष्ठा aa_profile *profile;
	स्थिर अक्षर *info = शून्य;
	पूर्णांक error;

	error = aa_path_name(path, flags, buffer, name, &info,
			     labels_profile(label)->disconnected);
	अगर (error) अणु
		fn_क्रम_each_confined(label, profile,
			aa_audit_file(profile, &nullperms, op, request, *name,
				      शून्य, शून्य, cond->uid, info, error));
		वापस error;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * map_old_perms - map old file perms layout to the new layout
 * @old: permission set in old mapping
 *
 * Returns: new permission mapping
 */
अटल u32 map_old_perms(u32 old)
अणु
	u32 new = old & 0xf;
	अगर (old & MAY_READ)
		new |= AA_MAY_GETATTR | AA_MAY_OPEN;
	अगर (old & MAY_WRITE)
		new |= AA_MAY_SETATTR | AA_MAY_CREATE | AA_MAY_DELETE |
		       AA_MAY_CHMOD | AA_MAY_CHOWN | AA_MAY_OPEN;
	अगर (old & 0x10)
		new |= AA_MAY_LINK;
	/* the old mapping lock and link_subset flags where overlaid
	 * and use was determined by part of a pair that they were in
	 */
	अगर (old & 0x20)
		new |= AA_MAY_LOCK | AA_LINK_SUBSET;
	अगर (old & 0x40)	/* AA_EXEC_MMAP */
		new |= AA_EXEC_MMAP;

	वापस new;
पूर्ण

/**
 * aa_compute_fperms - convert dfa compressed perms to पूर्णांकernal perms
 * @dfa: dfa to compute perms क्रम   (NOT शून्य)
 * @state: state in dfa
 * @cond:  conditions to consider  (NOT शून्य)
 *
 * TODO: convert from dfa + state to permission entry, करो computation conversion
 *       at load समय.
 *
 * Returns: computed permission set
 */
काष्ठा aa_perms aa_compute_fperms(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक state,
				  काष्ठा path_cond *cond)
अणु
	/* FIXME: change over to new dfa क्रमmat
	 * currently file perms are encoded in the dfa, new क्रमmat
	 * splits the permissions from the dfa.  This mapping can be
	 * करोne at profile load
	 */
	काष्ठा aa_perms perms = अणु पूर्ण;

	अगर (uid_eq(current_fsuid(), cond->uid)) अणु
		perms.allow = map_old_perms(dfa_user_allow(dfa, state));
		perms.audit = map_old_perms(dfa_user_audit(dfa, state));
		perms.quiet = map_old_perms(dfa_user_quiet(dfa, state));
		perms.xindex = dfa_user_xindex(dfa, state);
	पूर्ण अन्यथा अणु
		perms.allow = map_old_perms(dfa_other_allow(dfa, state));
		perms.audit = map_old_perms(dfa_other_audit(dfa, state));
		perms.quiet = map_old_perms(dfa_other_quiet(dfa, state));
		perms.xindex = dfa_other_xindex(dfa, state);
	पूर्ण
	perms.allow |= AA_MAY_GETATTR;

	/* change_profile wasn't determined by ownership in old mapping */
	अगर (ACCEPT_TABLE(dfa)[state] & 0x80000000)
		perms.allow |= AA_MAY_CHANGE_PROखाता;
	अगर (ACCEPT_TABLE(dfa)[state] & 0x40000000)
		perms.allow |= AA_MAY_ONEXEC;

	वापस perms;
पूर्ण

/**
 * aa_str_perms - find permission that match @name
 * @dfa: to match against  (MAYBE शून्य)
 * @state: state to start matching in
 * @name: string to match against dfa  (NOT शून्य)
 * @cond: conditions to consider क्रम permission set computation  (NOT शून्य)
 * @perms: Returns - the permissions found when matching @name
 *
 * Returns: the final state in @dfa when beginning @start and walking @name
 */
अचिन्हित पूर्णांक aa_str_perms(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक start,
			  स्थिर अक्षर *name, काष्ठा path_cond *cond,
			  काष्ठा aa_perms *perms)
अणु
	अचिन्हित पूर्णांक state;
	state = aa_dfa_match(dfa, start, name);
	*perms = aa_compute_fperms(dfa, state, cond);

	वापस state;
पूर्ण

पूर्णांक __aa_path_perm(स्थिर अक्षर *op, काष्ठा aa_profile *profile, स्थिर अक्षर *name,
		   u32 request, काष्ठा path_cond *cond, पूर्णांक flags,
		   काष्ठा aa_perms *perms)
अणु
	पूर्णांक e = 0;

	अगर (profile_unconfined(profile))
		वापस 0;
	aa_str_perms(profile->file.dfa, profile->file.start, name, cond, perms);
	अगर (request & ~perms->allow)
		e = -EACCES;
	वापस aa_audit_file(profile, perms, op, request, name, शून्य, शून्य,
			     cond->uid, शून्य, e);
पूर्ण


अटल पूर्णांक profile_path_perm(स्थिर अक्षर *op, काष्ठा aa_profile *profile,
			     स्थिर काष्ठा path *path, अक्षर *buffer, u32 request,
			     काष्ठा path_cond *cond, पूर्णांक flags,
			     काष्ठा aa_perms *perms)
अणु
	स्थिर अक्षर *name;
	पूर्णांक error;

	अगर (profile_unconfined(profile))
		वापस 0;

	error = path_name(op, &profile->label, path,
			  flags | profile->path_flags, buffer, &name, cond,
			  request);
	अगर (error)
		वापस error;
	वापस __aa_path_perm(op, profile, name, request, cond, flags,
			      perms);
पूर्ण

/**
 * aa_path_perm - करो permissions check & audit क्रम @path
 * @op: operation being checked
 * @label: profile being enक्रमced  (NOT शून्य)
 * @path: path to check permissions of  (NOT शून्य)
 * @flags: any additional path flags beyond what the profile specअगरies
 * @request: requested permissions
 * @cond: conditional info क्रम this request  (NOT शून्य)
 *
 * Returns: %0 अन्यथा error अगर access denied or other error
 */
पूर्णांक aa_path_perm(स्थिर अक्षर *op, काष्ठा aa_label *label,
		 स्थिर काष्ठा path *path, पूर्णांक flags, u32 request,
		 काष्ठा path_cond *cond)
अणु
	काष्ठा aa_perms perms = अणुपूर्ण;
	काष्ठा aa_profile *profile;
	अक्षर *buffer = शून्य;
	पूर्णांक error;

	flags |= PATH_DELEGATE_DELETED | (S_ISसूची(cond->mode) ? PATH_IS_सूची :
								0);
	buffer = aa_get_buffer(false);
	अगर (!buffer)
		वापस -ENOMEM;
	error = fn_क्रम_each_confined(label, profile,
			profile_path_perm(op, profile, path, buffer, request,
					  cond, flags, &perms));

	aa_put_buffer(buffer);

	वापस error;
पूर्ण

/**
 * xindex_is_subset - helper क्रम aa_path_link
 * @link: link permission set
 * @target: target permission set
 *
 * test target x permissions are equal OR a subset of link x permissions
 * this is करोne as part of the subset test, where a hardlink must have
 * a subset of permissions that the target has.
 *
 * Returns: true अगर subset अन्यथा false
 */
अटल अंतरभूत bool xindex_is_subset(u32 link, u32 target)
अणु
	अगर (((link & ~AA_X_UNSAFE) != (target & ~AA_X_UNSAFE)) ||
	    ((link & AA_X_UNSAFE) && !(target & AA_X_UNSAFE)))
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक profile_path_link(काष्ठा aa_profile *profile,
			     स्थिर काष्ठा path *link, अक्षर *buffer,
			     स्थिर काष्ठा path *target, अक्षर *buffer2,
			     काष्ठा path_cond *cond)
अणु
	स्थिर अक्षर *lname, *tname = शून्य;
	काष्ठा aa_perms lperms = अणुपूर्ण, perms;
	स्थिर अक्षर *info = शून्य;
	u32 request = AA_MAY_LINK;
	अचिन्हित पूर्णांक state;
	पूर्णांक error;

	error = path_name(OP_LINK, &profile->label, link, profile->path_flags,
			  buffer, &lname, cond, AA_MAY_LINK);
	अगर (error)
		जाओ audit;

	/* buffer2 मुक्तd below, tname is poपूर्णांकer in buffer2 */
	error = path_name(OP_LINK, &profile->label, target, profile->path_flags,
			  buffer2, &tname, cond, AA_MAY_LINK);
	अगर (error)
		जाओ audit;

	error = -EACCES;
	/* aa_str_perms - handles the हाल of the dfa being शून्य */
	state = aa_str_perms(profile->file.dfa, profile->file.start, lname,
			     cond, &lperms);

	अगर (!(lperms.allow & AA_MAY_LINK))
		जाओ audit;

	/* test to see अगर target can be paired with link */
	state = aa_dfa_null_transition(profile->file.dfa, state);
	aa_str_perms(profile->file.dfa, state, tname, cond, &perms);

	/* क्रमce audit/quiet masks क्रम link are stored in the second entry
	 * in the link pair.
	 */
	lperms.audit = perms.audit;
	lperms.quiet = perms.quiet;
	lperms.समाप्त = perms.समाप्त;

	अगर (!(perms.allow & AA_MAY_LINK)) अणु
		info = "target restricted";
		lperms = perms;
		जाओ audit;
	पूर्ण

	/* करोne अगर link subset test is not required */
	अगर (!(perms.allow & AA_LINK_SUBSET))
		जाओ करोne_tests;

	/* Do link perm subset test requiring allowed permission on link are
	 * a subset of the allowed permissions on target.
	 */
	aa_str_perms(profile->file.dfa, profile->file.start, tname, cond,
		     &perms);

	/* AA_MAY_LINK is not considered in the subset test */
	request = lperms.allow & ~AA_MAY_LINK;
	lperms.allow &= perms.allow | AA_MAY_LINK;

	request |= AA_AUDIT_खाता_MASK & (lperms.allow & ~perms.allow);
	अगर (request & ~lperms.allow) अणु
		जाओ audit;
	पूर्ण अन्यथा अगर ((lperms.allow & MAY_EXEC) &&
		   !xindex_is_subset(lperms.xindex, perms.xindex)) अणु
		lperms.allow &= ~MAY_EXEC;
		request |= MAY_EXEC;
		info = "link not subset of target";
		जाओ audit;
	पूर्ण

करोne_tests:
	error = 0;

audit:
	वापस aa_audit_file(profile, &lperms, OP_LINK, request, lname, tname,
			     शून्य, cond->uid, info, error);
पूर्ण

/**
 * aa_path_link - Handle hard link permission check
 * @label: the label being enक्रमced  (NOT शून्य)
 * @old_dentry: the target dentry  (NOT शून्य)
 * @new_dir: directory the new link will be created in  (NOT शून्य)
 * @new_dentry: the link being created  (NOT शून्य)
 *
 * Handle the permission test क्रम a link & target pair.  Permission
 * is encoded as a pair where the link permission is determined
 * first, and अगर allowed, the target is tested.  The target test
 * is करोne from the poपूर्णांक of the link match (not start of DFA)
 * making the target permission dependent on the link permission match.
 *
 * The subset test अगर required क्रमces that permissions granted
 * on link are a subset of the permission granted to target.
 *
 * Returns: %0 अगर allowed अन्यथा error
 */
पूर्णांक aa_path_link(काष्ठा aa_label *label, काष्ठा dentry *old_dentry,
		 स्थिर काष्ठा path *new_dir, काष्ठा dentry *new_dentry)
अणु
	काष्ठा path link = अणु .mnt = new_dir->mnt, .dentry = new_dentry पूर्ण;
	काष्ठा path target = अणु .mnt = new_dir->mnt, .dentry = old_dentry पूर्ण;
	काष्ठा path_cond cond = अणु
		d_backing_inode(old_dentry)->i_uid,
		d_backing_inode(old_dentry)->i_mode
	पूर्ण;
	अक्षर *buffer = शून्य, *buffer2 = शून्य;
	काष्ठा aa_profile *profile;
	पूर्णांक error;

	/* buffer मुक्तd below, lname is poपूर्णांकer in buffer */
	buffer = aa_get_buffer(false);
	buffer2 = aa_get_buffer(false);
	error = -ENOMEM;
	अगर (!buffer || !buffer2)
		जाओ out;

	error = fn_क्रम_each_confined(label, profile,
			profile_path_link(profile, &link, buffer, &target,
					  buffer2, &cond));
out:
	aa_put_buffer(buffer);
	aa_put_buffer(buffer2);
	वापस error;
पूर्ण

अटल व्योम update_file_ctx(काष्ठा aa_file_ctx *fctx, काष्ठा aa_label *label,
			    u32 request)
अणु
	काष्ठा aa_label *l, *old;

	/* update caching of label on file_ctx */
	spin_lock(&fctx->lock);
	old = rcu_dereference_रक्षित(fctx->label,
					lockdep_is_held(&fctx->lock));
	l = aa_label_merge(old, label, GFP_ATOMIC);
	अगर (l) अणु
		अगर (l != old) अणु
			rcu_assign_poपूर्णांकer(fctx->label, l);
			aa_put_label(old);
		पूर्ण अन्यथा
			aa_put_label(l);
		fctx->allow |= request;
	पूर्ण
	spin_unlock(&fctx->lock);
पूर्ण

अटल पूर्णांक __file_path_perm(स्थिर अक्षर *op, काष्ठा aa_label *label,
			    काष्ठा aa_label *flabel, काष्ठा file *file,
			    u32 request, u32 denied, bool in_atomic)
अणु
	काष्ठा aa_profile *profile;
	काष्ठा aa_perms perms = अणुपूर्ण;
	काष्ठा path_cond cond = अणु
		.uid = i_uid_पूर्णांकo_mnt(file_mnt_user_ns(file), file_inode(file)),
		.mode = file_inode(file)->i_mode
	पूर्ण;
	अक्षर *buffer;
	पूर्णांक flags, error;

	/* revalidation due to label out of date. No revocation at this समय */
	अगर (!denied && aa_label_is_subset(flabel, label))
		/* TODO: check क्रम revocation on stale profiles */
		वापस 0;

	flags = PATH_DELEGATE_DELETED | (S_ISसूची(cond.mode) ? PATH_IS_सूची : 0);
	buffer = aa_get_buffer(in_atomic);
	अगर (!buffer)
		वापस -ENOMEM;

	/* check every profile in task label not in current cache */
	error = fn_क्रम_each_not_in_set(flabel, label, profile,
			profile_path_perm(op, profile, &file->f_path, buffer,
					  request, &cond, flags, &perms));
	अगर (denied && !error) अणु
		/*
		 * check every profile in file label that was not tested
		 * in the initial check above.
		 *
		 * TODO: cache full perms so this only happens because of
		 * conditionals
		 * TODO: करोn't audit here
		 */
		अगर (label == flabel)
			error = fn_क्रम_each(label, profile,
				profile_path_perm(op, profile, &file->f_path,
						  buffer, request, &cond, flags,
						  &perms));
		अन्यथा
			error = fn_क्रम_each_not_in_set(label, flabel, profile,
				profile_path_perm(op, profile, &file->f_path,
						  buffer, request, &cond, flags,
						  &perms));
	पूर्ण
	अगर (!error)
		update_file_ctx(file_ctx(file), label, request);

	aa_put_buffer(buffer);

	वापस error;
पूर्ण

अटल पूर्णांक __file_sock_perm(स्थिर अक्षर *op, काष्ठा aa_label *label,
			    काष्ठा aa_label *flabel, काष्ठा file *file,
			    u32 request, u32 denied)
अणु
	काष्ठा socket *sock = (काष्ठा socket *) file->निजी_data;
	पूर्णांक error;

	AA_BUG(!sock);

	/* revalidation due to label out of date. No revocation at this समय */
	अगर (!denied && aa_label_is_subset(flabel, label))
		वापस 0;

	/* TODO: improve to skip profiles cached in flabel */
	error = aa_sock_file_perm(label, op, request, sock);
	अगर (denied) अणु
		/* TODO: improve to skip profiles checked above */
		/* check every profile in file label to is cached */
		last_error(error, aa_sock_file_perm(flabel, op, request, sock));
	पूर्ण
	अगर (!error)
		update_file_ctx(file_ctx(file), label, request);

	वापस error;
पूर्ण

/**
 * aa_file_perm - करो permission revalidation check & audit क्रम @file
 * @op: operation being checked
 * @label: label being enक्रमced   (NOT शून्य)
 * @file: file to revalidate access permissions on  (NOT शून्य)
 * @request: requested permissions
 * @in_atomic: whether allocations need to be करोne in atomic context
 *
 * Returns: %0 अगर access allowed अन्यथा error
 */
पूर्णांक aa_file_perm(स्थिर अक्षर *op, काष्ठा aa_label *label, काष्ठा file *file,
		 u32 request, bool in_atomic)
अणु
	काष्ठा aa_file_ctx *fctx;
	काष्ठा aa_label *flabel;
	u32 denied;
	पूर्णांक error = 0;

	AA_BUG(!label);
	AA_BUG(!file);

	fctx = file_ctx(file);

	rcu_पढ़ो_lock();
	flabel  = rcu_dereference(fctx->label);
	AA_BUG(!flabel);

	/* revalidate access, अगर task is unconfined, or the cached cred
	 * करोesn't match or अगर the request is क्रम more permissions than
	 * was granted.
	 *
	 * Note: the test क्रम !unconfined(flabel) is to handle file
	 *       delegation from unconfined tasks
	 */
	denied = request & ~fctx->allow;
	अगर (unconfined(label) || unconfined(flabel) ||
	    (!denied && aa_label_is_subset(flabel, label))) अणु
		rcu_पढ़ो_unlock();
		जाओ करोne;
	पूर्ण

	flabel  = aa_get_newest_label(flabel);
	rcu_पढ़ो_unlock();
	/* TODO: label cross check */

	अगर (file->f_path.mnt && path_mediated_fs(file->f_path.dentry))
		error = __file_path_perm(op, label, flabel, file, request,
					 denied, in_atomic);

	अन्यथा अगर (S_ISSOCK(file_inode(file)->i_mode))
		error = __file_sock_perm(op, label, flabel, file, request,
					 denied);
	aa_put_label(flabel);

करोne:
	वापस error;
पूर्ण

अटल व्योम revalidate_tty(काष्ठा aa_label *label)
अणु
	काष्ठा tty_काष्ठा *tty;
	पूर्णांक drop_tty = 0;

	tty = get_current_tty();
	अगर (!tty)
		वापस;

	spin_lock(&tty->files_lock);
	अगर (!list_empty(&tty->tty_files)) अणु
		काष्ठा tty_file_निजी *file_priv;
		काष्ठा file *file;
		/* TODO: Revalidate access to controlling tty. */
		file_priv = list_first_entry(&tty->tty_files,
					     काष्ठा tty_file_निजी, list);
		file = file_priv->file;

		अगर (aa_file_perm(OP_INHERIT, label, file, MAY_READ | MAY_WRITE,
				 IN_ATOMIC))
			drop_tty = 1;
	पूर्ण
	spin_unlock(&tty->files_lock);
	tty_kref_put(tty);

	अगर (drop_tty)
		no_tty();
पूर्ण

अटल पूर्णांक match_file(स्थिर व्योम *p, काष्ठा file *file, अचिन्हित पूर्णांक fd)
अणु
	काष्ठा aa_label *label = (काष्ठा aa_label *)p;

	अगर (aa_file_perm(OP_INHERIT, label, file, aa_map_file_to_perms(file),
			 IN_ATOMIC))
		वापस fd + 1;
	वापस 0;
पूर्ण


/* based on selinux's flush_unauthorized_files */
व्योम aa_inherit_files(स्थिर काष्ठा cred *cred, काष्ठा files_काष्ठा *files)
अणु
	काष्ठा aa_label *label = aa_get_newest_cred_label(cred);
	काष्ठा file *devnull = शून्य;
	अचिन्हित पूर्णांक n;

	revalidate_tty(label);

	/* Revalidate access to inherited खोलो files. */
	n = iterate_fd(files, 0, match_file, label);
	अगर (!n) /* none found? */
		जाओ out;

	devnull = dentry_खोलो(&aa_null, O_RDWR, cred);
	अगर (IS_ERR(devnull))
		devnull = शून्य;
	/* replace all the matching ones with this */
	करो अणु
		replace_fd(n - 1, devnull, 0);
	पूर्ण जबतक ((n = iterate_fd(files, n, match_file, label)) != 0);
	अगर (devnull)
		fput(devnull);
out:
	aa_put_label(label);
पूर्ण
