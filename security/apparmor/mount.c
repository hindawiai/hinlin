<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor mediation of files
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2017 Canonical Ltd.
 */

#समावेश <linux/fs.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <uapi/linux/mount.h>

#समावेश "include/apparmor.h"
#समावेश "include/audit.h"
#समावेश "include/cred.h"
#समावेश "include/domain.h"
#समावेश "include/file.h"
#समावेश "include/match.h"
#समावेश "include/mount.h"
#समावेश "include/path.h"
#समावेश "include/policy.h"


अटल व्योम audit_mnt_flags(काष्ठा audit_buffer *ab, अचिन्हित दीर्घ flags)
अणु
	अगर (flags & MS_RDONLY)
		audit_log_क्रमmat(ab, "ro");
	अन्यथा
		audit_log_क्रमmat(ab, "rw");
	अगर (flags & MS_NOSUID)
		audit_log_क्रमmat(ab, ", nosuid");
	अगर (flags & MS_NODEV)
		audit_log_क्रमmat(ab, ", nodev");
	अगर (flags & MS_NOEXEC)
		audit_log_क्रमmat(ab, ", noexec");
	अगर (flags & MS_SYNCHRONOUS)
		audit_log_क्रमmat(ab, ", sync");
	अगर (flags & MS_REMOUNT)
		audit_log_क्रमmat(ab, ", remount");
	अगर (flags & MS_MANDLOCK)
		audit_log_क्रमmat(ab, ", mand");
	अगर (flags & MS_सूचीSYNC)
		audit_log_क्रमmat(ab, ", dirsync");
	अगर (flags & MS_NOATIME)
		audit_log_क्रमmat(ab, ", noatime");
	अगर (flags & MS_NOसूचीATIME)
		audit_log_क्रमmat(ab, ", nodiratime");
	अगर (flags & MS_BIND)
		audit_log_क्रमmat(ab, flags & MS_REC ? ", rbind" : ", bind");
	अगर (flags & MS_MOVE)
		audit_log_क्रमmat(ab, ", move");
	अगर (flags & MS_SILENT)
		audit_log_क्रमmat(ab, ", silent");
	अगर (flags & MS_POSIXACL)
		audit_log_क्रमmat(ab, ", acl");
	अगर (flags & MS_UNBINDABLE)
		audit_log_क्रमmat(ab, flags & MS_REC ? ", runbindable" :
				 ", unbindable");
	अगर (flags & MS_PRIVATE)
		audit_log_क्रमmat(ab, flags & MS_REC ? ", rprivate" :
				 ", private");
	अगर (flags & MS_SLAVE)
		audit_log_क्रमmat(ab, flags & MS_REC ? ", rslave" :
				 ", slave");
	अगर (flags & MS_SHARED)
		audit_log_क्रमmat(ab, flags & MS_REC ? ", rshared" :
				 ", shared");
	अगर (flags & MS_RELATIME)
		audit_log_क्रमmat(ab, ", relatime");
	अगर (flags & MS_I_VERSION)
		audit_log_क्रमmat(ab, ", iversion");
	अगर (flags & MS_STRICTATIME)
		audit_log_क्रमmat(ab, ", strictatime");
	अगर (flags & MS_NOUSER)
		audit_log_क्रमmat(ab, ", nouser");
पूर्ण

/**
 * audit_cb - call back क्रम mount specअगरic audit fields
 * @ab: audit_buffer  (NOT शून्य)
 * @va: audit काष्ठा to audit values of  (NOT शून्य)
 */
अटल व्योम audit_cb(काष्ठा audit_buffer *ab, व्योम *va)
अणु
	काष्ठा common_audit_data *sa = va;

	अगर (aad(sa)->mnt.type) अणु
		audit_log_क्रमmat(ab, " fstype=");
		audit_log_untrustedstring(ab, aad(sa)->mnt.type);
	पूर्ण
	अगर (aad(sa)->mnt.src_name) अणु
		audit_log_क्रमmat(ab, " srcname=");
		audit_log_untrustedstring(ab, aad(sa)->mnt.src_name);
	पूर्ण
	अगर (aad(sa)->mnt.trans) अणु
		audit_log_क्रमmat(ab, " trans=");
		audit_log_untrustedstring(ab, aad(sa)->mnt.trans);
	पूर्ण
	अगर (aad(sa)->mnt.flags) अणु
		audit_log_क्रमmat(ab, " flags=\"");
		audit_mnt_flags(ab, aad(sa)->mnt.flags);
		audit_log_क्रमmat(ab, "\"");
	पूर्ण
	अगर (aad(sa)->mnt.data) अणु
		audit_log_क्रमmat(ab, " options=");
		audit_log_untrustedstring(ab, aad(sa)->mnt.data);
	पूर्ण
पूर्ण

/**
 * audit_mount - handle the auditing of mount operations
 * @profile: the profile being enक्रमced  (NOT शून्य)
 * @op: operation being mediated (NOT शून्य)
 * @name: name of object being mediated (MAYBE शून्य)
 * @src_name: src_name of object being mediated (MAYBE_शून्य)
 * @type: type of fileप्रणाली (MAYBE_शून्य)
 * @trans: name of trans (MAYBE शून्य)
 * @flags: fileप्रणाली independent mount flags
 * @data: fileप्रणाली mount flags
 * @request: permissions requested
 * @perms: the permissions computed क्रम the request (NOT शून्य)
 * @info: extra inक्रमmation message (MAYBE शून्य)
 * @error: 0 अगर operation allowed अन्यथा failure error code
 *
 * Returns: %0 or error on failure
 */
अटल पूर्णांक audit_mount(काष्ठा aa_profile *profile, स्थिर अक्षर *op,
		       स्थिर अक्षर *name, स्थिर अक्षर *src_name,
		       स्थिर अक्षर *type, स्थिर अक्षर *trans,
		       अचिन्हित दीर्घ flags, स्थिर व्योम *data, u32 request,
		       काष्ठा aa_perms *perms, स्थिर अक्षर *info, पूर्णांक error)
अणु
	पूर्णांक audit_type = AUDIT_APPARMOR_AUTO;
	DEFINE_AUDIT_DATA(sa, LSM_AUDIT_DATA_NONE, op);

	अगर (likely(!error)) अणु
		u32 mask = perms->audit;

		अगर (unlikely(AUDIT_MODE(profile) == AUDIT_ALL))
			mask = 0xffff;

		/* mask off perms that are not being क्रमce audited */
		request &= mask;

		अगर (likely(!request))
			वापस 0;
		audit_type = AUDIT_APPARMOR_AUDIT;
	पूर्ण अन्यथा अणु
		/* only report permissions that were denied */
		request = request & ~perms->allow;

		अगर (request & perms->समाप्त)
			audit_type = AUDIT_APPARMOR_KILL;

		/* quiet known rejects, assumes quiet and समाप्त करो not overlap */
		अगर ((request & perms->quiet) &&
		    AUDIT_MODE(profile) != AUDIT_NOQUIET &&
		    AUDIT_MODE(profile) != AUDIT_ALL)
			request &= ~perms->quiet;

		अगर (!request)
			वापस error;
	पूर्ण

	aad(&sa)->name = name;
	aad(&sa)->mnt.src_name = src_name;
	aad(&sa)->mnt.type = type;
	aad(&sa)->mnt.trans = trans;
	aad(&sa)->mnt.flags = flags;
	अगर (data && (perms->audit & AA_AUDIT_DATA))
		aad(&sa)->mnt.data = data;
	aad(&sa)->info = info;
	aad(&sa)->error = error;

	वापस aa_audit(audit_type, profile, &sa, audit_cb);
पूर्ण

/**
 * match_mnt_flags - Do an ordered match on mount flags
 * @dfa: dfa to match against
 * @state: state to start in
 * @flags: mount flags to match against
 *
 * Mount flags are encoded as an ordered match. This is करोne instead of
 * checking against a simple biपंचांगask, to allow क्रम logical operations
 * on the flags.
 *
 * Returns: next state after flags match
 */
अटल अचिन्हित पूर्णांक match_mnt_flags(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक state,
				    अचिन्हित दीर्घ flags)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i <= 31 ; ++i) अणु
		अगर ((1 << i) & flags)
			state = aa_dfa_next(dfa, state, i + 1);
	पूर्ण

	वापस state;
पूर्ण

/**
 * compute_mnt_perms - compute mount permission associated with @state
 * @dfa: dfa to match against (NOT शून्य)
 * @state: state match finished in
 *
 * Returns: mount permissions
 */
अटल काष्ठा aa_perms compute_mnt_perms(काष्ठा aa_dfa *dfa,
					   अचिन्हित पूर्णांक state)
अणु
	काष्ठा aa_perms perms = अणु
		.allow = dfa_user_allow(dfa, state),
		.audit = dfa_user_audit(dfa, state),
		.quiet = dfa_user_quiet(dfa, state),
		.xindex = dfa_user_xindex(dfa, state),
	पूर्ण;

	वापस perms;
पूर्ण

अटल स्थिर अक्षर * स्थिर mnt_info_table[] = अणु
	"match succeeded",
	"failed mntpnt match",
	"failed srcname match",
	"failed type match",
	"failed flags match",
	"failed data match"
पूर्ण;

/*
 * Returns 0 on success अन्यथा element that match failed in, this is the
 * index पूर्णांकo the mnt_info_table above
 */
अटल पूर्णांक करो_match_mnt(काष्ठा aa_dfa *dfa, अचिन्हित पूर्णांक start,
			स्थिर अक्षर *mntpnt, स्थिर अक्षर *devname,
			स्थिर अक्षर *type, अचिन्हित दीर्घ flags,
			व्योम *data, bool binary, काष्ठा aa_perms *perms)
अणु
	अचिन्हित पूर्णांक state;

	AA_BUG(!dfa);
	AA_BUG(!perms);

	state = aa_dfa_match(dfa, start, mntpnt);
	state = aa_dfa_null_transition(dfa, state);
	अगर (!state)
		वापस 1;

	अगर (devname)
		state = aa_dfa_match(dfa, state, devname);
	state = aa_dfa_null_transition(dfa, state);
	अगर (!state)
		वापस 2;

	अगर (type)
		state = aa_dfa_match(dfa, state, type);
	state = aa_dfa_null_transition(dfa, state);
	अगर (!state)
		वापस 3;

	state = match_mnt_flags(dfa, state, flags);
	अगर (!state)
		वापस 4;
	*perms = compute_mnt_perms(dfa, state);
	अगर (perms->allow & AA_MAY_MOUNT)
		वापस 0;

	/* only match data अगर not binary and the DFA flags data is expected */
	अगर (data && !binary && (perms->allow & AA_MNT_CONT_MATCH)) अणु
		state = aa_dfa_null_transition(dfa, state);
		अगर (!state)
			वापस 4;

		state = aa_dfa_match(dfa, state, data);
		अगर (!state)
			वापस 5;
		*perms = compute_mnt_perms(dfa, state);
		अगर (perms->allow & AA_MAY_MOUNT)
			वापस 0;
	पूर्ण

	/* failed at end of flags match */
	वापस 4;
पूर्ण


अटल पूर्णांक path_flags(काष्ठा aa_profile *profile, स्थिर काष्ठा path *path)
अणु
	AA_BUG(!profile);
	AA_BUG(!path);

	वापस profile->path_flags |
		(S_ISसूची(path->dentry->d_inode->i_mode) ? PATH_IS_सूची : 0);
पूर्ण

/**
 * match_mnt_path_str - handle path matching क्रम mount
 * @profile: the confining profile
 * @mntpath: क्रम the mntpnt (NOT शून्य)
 * @buffer: buffer to be used to lookup mntpath
 * @devnme: string क्रम the devname/src_name (MAY BE शून्य OR ERRPTR)
 * @type: string क्रम the dev type (MAYBE शून्य)
 * @flags: mount flags to match
 * @data: fs mount data (MAYBE शून्य)
 * @binary: whether @data is binary
 * @devinfo: error str अगर (IS_ERR(@devname))
 *
 * Returns: 0 on success अन्यथा error
 */
अटल पूर्णांक match_mnt_path_str(काष्ठा aa_profile *profile,
			      स्थिर काष्ठा path *mntpath, अक्षर *buffer,
			      स्थिर अक्षर *devname, स्थिर अक्षर *type,
			      अचिन्हित दीर्घ flags, व्योम *data, bool binary,
			      स्थिर अक्षर *devinfo)
अणु
	काष्ठा aa_perms perms = अणु पूर्ण;
	स्थिर अक्षर *mntpnt = शून्य, *info = शून्य;
	पूर्णांक pos, error;

	AA_BUG(!profile);
	AA_BUG(!mntpath);
	AA_BUG(!buffer);

	अगर (!PROखाता_MEDIATES(profile, AA_CLASS_MOUNT))
		वापस 0;

	error = aa_path_name(mntpath, path_flags(profile, mntpath), buffer,
			     &mntpnt, &info, profile->disconnected);
	अगर (error)
		जाओ audit;
	अगर (IS_ERR(devname)) अणु
		error = PTR_ERR(devname);
		devname = शून्य;
		info = devinfo;
		जाओ audit;
	पूर्ण

	error = -EACCES;
	pos = करो_match_mnt(profile->policy.dfa,
			   profile->policy.start[AA_CLASS_MOUNT],
			   mntpnt, devname, type, flags, data, binary, &perms);
	अगर (pos) अणु
		info = mnt_info_table[pos];
		जाओ audit;
	पूर्ण
	error = 0;

audit:
	वापस audit_mount(profile, OP_MOUNT, mntpnt, devname, type, शून्य,
			   flags, data, AA_MAY_MOUNT, &perms, info, error);
पूर्ण

/**
 * match_mnt - handle path matching क्रम mount
 * @profile: the confining profile
 * @mntpath: क्रम the mntpnt (NOT शून्य)
 * @buffer: buffer to be used to lookup mntpath
 * @devpath: path devname/src_name (MAYBE शून्य)
 * @devbuffer: buffer to be used to lookup devname/src_name
 * @type: string क्रम the dev type (MAYBE शून्य)
 * @flags: mount flags to match
 * @data: fs mount data (MAYBE शून्य)
 * @binary: whether @data is binary
 *
 * Returns: 0 on success अन्यथा error
 */
अटल पूर्णांक match_mnt(काष्ठा aa_profile *profile, स्थिर काष्ठा path *path,
		     अक्षर *buffer, स्थिर काष्ठा path *devpath, अक्षर *devbuffer,
		     स्थिर अक्षर *type, अचिन्हित दीर्घ flags, व्योम *data,
		     bool binary)
अणु
	स्थिर अक्षर *devname = शून्य, *info = शून्य;
	पूर्णांक error = -EACCES;

	AA_BUG(!profile);
	AA_BUG(devpath && !devbuffer);

	अगर (!PROखाता_MEDIATES(profile, AA_CLASS_MOUNT))
		वापस 0;

	अगर (devpath) अणु
		error = aa_path_name(devpath, path_flags(profile, devpath),
				     devbuffer, &devname, &info,
				     profile->disconnected);
		अगर (error)
			devname = ERR_PTR(error);
	पूर्ण

	वापस match_mnt_path_str(profile, path, buffer, devname, type, flags,
				  data, binary, info);
पूर्ण

पूर्णांक aa_remount(काष्ठा aa_label *label, स्थिर काष्ठा path *path,
	       अचिन्हित दीर्घ flags, व्योम *data)
अणु
	काष्ठा aa_profile *profile;
	अक्षर *buffer = शून्य;
	bool binary;
	पूर्णांक error;

	AA_BUG(!label);
	AA_BUG(!path);

	binary = path->dentry->d_sb->s_type->fs_flags & FS_BINARY_MOUNTDATA;

	buffer = aa_get_buffer(false);
	अगर (!buffer)
		वापस -ENOMEM;
	error = fn_क्रम_each_confined(label, profile,
			match_mnt(profile, path, buffer, शून्य, शून्य, शून्य,
				  flags, data, binary));
	aa_put_buffer(buffer);

	वापस error;
पूर्ण

पूर्णांक aa_bind_mount(काष्ठा aa_label *label, स्थिर काष्ठा path *path,
		  स्थिर अक्षर *dev_name, अचिन्हित दीर्घ flags)
अणु
	काष्ठा aa_profile *profile;
	अक्षर *buffer = शून्य, *old_buffer = शून्य;
	काष्ठा path old_path;
	पूर्णांक error;

	AA_BUG(!label);
	AA_BUG(!path);

	अगर (!dev_name || !*dev_name)
		वापस -EINVAL;

	flags &= MS_REC | MS_BIND;

	error = kern_path(dev_name, LOOKUP_FOLLOW|LOOKUP_AUTOMOUNT, &old_path);
	अगर (error)
		वापस error;

	buffer = aa_get_buffer(false);
	old_buffer = aa_get_buffer(false);
	error = -ENOMEM;
	अगर (!buffer || !old_buffer)
		जाओ out;

	error = fn_क्रम_each_confined(label, profile,
			match_mnt(profile, path, buffer, &old_path, old_buffer,
				  शून्य, flags, शून्य, false));
out:
	aa_put_buffer(buffer);
	aa_put_buffer(old_buffer);
	path_put(&old_path);

	वापस error;
पूर्ण

पूर्णांक aa_mount_change_type(काष्ठा aa_label *label, स्थिर काष्ठा path *path,
			 अचिन्हित दीर्घ flags)
अणु
	काष्ठा aa_profile *profile;
	अक्षर *buffer = शून्य;
	पूर्णांक error;

	AA_BUG(!label);
	AA_BUG(!path);

	/* These are the flags allowed by करो_change_type() */
	flags &= (MS_REC | MS_SILENT | MS_SHARED | MS_PRIVATE | MS_SLAVE |
		  MS_UNBINDABLE);

	buffer = aa_get_buffer(false);
	अगर (!buffer)
		वापस -ENOMEM;
	error = fn_क्रम_each_confined(label, profile,
			match_mnt(profile, path, buffer, शून्य, शून्य, शून्य,
				  flags, शून्य, false));
	aa_put_buffer(buffer);

	वापस error;
पूर्ण

पूर्णांक aa_move_mount(काष्ठा aa_label *label, स्थिर काष्ठा path *path,
		  स्थिर अक्षर *orig_name)
अणु
	काष्ठा aa_profile *profile;
	अक्षर *buffer = शून्य, *old_buffer = शून्य;
	काष्ठा path old_path;
	पूर्णांक error;

	AA_BUG(!label);
	AA_BUG(!path);

	अगर (!orig_name || !*orig_name)
		वापस -EINVAL;

	error = kern_path(orig_name, LOOKUP_FOLLOW, &old_path);
	अगर (error)
		वापस error;

	buffer = aa_get_buffer(false);
	old_buffer = aa_get_buffer(false);
	error = -ENOMEM;
	अगर (!buffer || !old_buffer)
		जाओ out;
	error = fn_क्रम_each_confined(label, profile,
			match_mnt(profile, path, buffer, &old_path, old_buffer,
				  शून्य, MS_MOVE, शून्य, false));
out:
	aa_put_buffer(buffer);
	aa_put_buffer(old_buffer);
	path_put(&old_path);

	वापस error;
पूर्ण

पूर्णांक aa_new_mount(काष्ठा aa_label *label, स्थिर अक्षर *dev_name,
		 स्थिर काष्ठा path *path, स्थिर अक्षर *type, अचिन्हित दीर्घ flags,
		 व्योम *data)
अणु
	काष्ठा aa_profile *profile;
	अक्षर *buffer = शून्य, *dev_buffer = शून्य;
	bool binary = true;
	पूर्णांक error;
	पूर्णांक requires_dev = 0;
	काष्ठा path पंचांगp_path, *dev_path = शून्य;

	AA_BUG(!label);
	AA_BUG(!path);

	अगर (type) अणु
		काष्ठा file_प्रणाली_type *fstype;

		fstype = get_fs_type(type);
		अगर (!fstype)
			वापस -ENODEV;
		binary = fstype->fs_flags & FS_BINARY_MOUNTDATA;
		requires_dev = fstype->fs_flags & FS_REQUIRES_DEV;
		put_fileप्रणाली(fstype);

		अगर (requires_dev) अणु
			अगर (!dev_name || !*dev_name)
				वापस -ENOENT;

			error = kern_path(dev_name, LOOKUP_FOLLOW, &पंचांगp_path);
			अगर (error)
				वापस error;
			dev_path = &पंचांगp_path;
		पूर्ण
	पूर्ण

	buffer = aa_get_buffer(false);
	अगर (!buffer) अणु
		error = -ENOMEM;
		जाओ out;
	पूर्ण
	अगर (dev_path) अणु
		dev_buffer = aa_get_buffer(false);
		अगर (!dev_buffer) अणु
			error = -ENOMEM;
			जाओ out;
		पूर्ण
		error = fn_क्रम_each_confined(label, profile,
			match_mnt(profile, path, buffer, dev_path, dev_buffer,
				  type, flags, data, binary));
	पूर्ण अन्यथा अणु
		error = fn_क्रम_each_confined(label, profile,
			match_mnt_path_str(profile, path, buffer, dev_name,
					   type, flags, data, binary, शून्य));
	पूर्ण

out:
	aa_put_buffer(buffer);
	aa_put_buffer(dev_buffer);
	अगर (dev_path)
		path_put(dev_path);

	वापस error;
पूर्ण

अटल पूर्णांक profile_umount(काष्ठा aa_profile *profile, स्थिर काष्ठा path *path,
			  अक्षर *buffer)
अणु
	काष्ठा aa_perms perms = अणु पूर्ण;
	स्थिर अक्षर *name = शून्य, *info = शून्य;
	अचिन्हित पूर्णांक state;
	पूर्णांक error;

	AA_BUG(!profile);
	AA_BUG(!path);

	अगर (!PROखाता_MEDIATES(profile, AA_CLASS_MOUNT))
		वापस 0;

	error = aa_path_name(path, path_flags(profile, path), buffer, &name,
			     &info, profile->disconnected);
	अगर (error)
		जाओ audit;

	state = aa_dfa_match(profile->policy.dfa,
			     profile->policy.start[AA_CLASS_MOUNT],
			     name);
	perms = compute_mnt_perms(profile->policy.dfa, state);
	अगर (AA_MAY_UMOUNT & ~perms.allow)
		error = -EACCES;

audit:
	वापस audit_mount(profile, OP_UMOUNT, name, शून्य, शून्य, शून्य, 0, शून्य,
			   AA_MAY_UMOUNT, &perms, info, error);
पूर्ण

पूर्णांक aa_umount(काष्ठा aa_label *label, काष्ठा vfsmount *mnt, पूर्णांक flags)
अणु
	काष्ठा aa_profile *profile;
	अक्षर *buffer = शून्य;
	पूर्णांक error;
	काष्ठा path path = अणु .mnt = mnt, .dentry = mnt->mnt_root पूर्ण;

	AA_BUG(!label);
	AA_BUG(!mnt);

	buffer = aa_get_buffer(false);
	अगर (!buffer)
		वापस -ENOMEM;

	error = fn_क्रम_each_confined(label, profile,
			profile_umount(profile, &path, buffer));
	aa_put_buffer(buffer);

	वापस error;
पूर्ण

/* helper fn क्रम transition on pivotroot
 *
 * Returns: label क्रम transition or ERR_PTR. Does not वापस शून्य
 */
अटल काष्ठा aa_label *build_pivotroot(काष्ठा aa_profile *profile,
					स्थिर काष्ठा path *new_path,
					अक्षर *new_buffer,
					स्थिर काष्ठा path *old_path,
					अक्षर *old_buffer)
अणु
	स्थिर अक्षर *old_name, *new_name = शून्य, *info = शून्य;
	स्थिर अक्षर *trans_name = शून्य;
	काष्ठा aa_perms perms = अणु पूर्ण;
	अचिन्हित पूर्णांक state;
	पूर्णांक error;

	AA_BUG(!profile);
	AA_BUG(!new_path);
	AA_BUG(!old_path);

	अगर (profile_unconfined(profile) ||
	    !PROखाता_MEDIATES(profile, AA_CLASS_MOUNT))
		वापस aa_get_newest_label(&profile->label);

	error = aa_path_name(old_path, path_flags(profile, old_path),
			     old_buffer, &old_name, &info,
			     profile->disconnected);
	अगर (error)
		जाओ audit;
	error = aa_path_name(new_path, path_flags(profile, new_path),
			     new_buffer, &new_name, &info,
			     profile->disconnected);
	अगर (error)
		जाओ audit;

	error = -EACCES;
	state = aa_dfa_match(profile->policy.dfa,
			     profile->policy.start[AA_CLASS_MOUNT],
			     new_name);
	state = aa_dfa_null_transition(profile->policy.dfa, state);
	state = aa_dfa_match(profile->policy.dfa, state, old_name);
	perms = compute_mnt_perms(profile->policy.dfa, state);

	अगर (AA_MAY_PIVOTROOT & perms.allow)
		error = 0;

audit:
	error = audit_mount(profile, OP_PIVOTROOT, new_name, old_name,
			    शून्य, trans_name, 0, शून्य, AA_MAY_PIVOTROOT,
			    &perms, info, error);
	अगर (error)
		वापस ERR_PTR(error);

	वापस aa_get_newest_label(&profile->label);
पूर्ण

पूर्णांक aa_pivotroot(काष्ठा aa_label *label, स्थिर काष्ठा path *old_path,
		 स्थिर काष्ठा path *new_path)
अणु
	काष्ठा aa_profile *profile;
	काष्ठा aa_label *target = शून्य;
	अक्षर *old_buffer = शून्य, *new_buffer = शून्य, *info = शून्य;
	पूर्णांक error;

	AA_BUG(!label);
	AA_BUG(!old_path);
	AA_BUG(!new_path);

	old_buffer = aa_get_buffer(false);
	new_buffer = aa_get_buffer(false);
	error = -ENOMEM;
	अगर (!old_buffer || !new_buffer)
		जाओ out;
	target = fn_label_build(label, profile, GFP_KERNEL,
			build_pivotroot(profile, new_path, new_buffer,
					old_path, old_buffer));
	अगर (!target) अणु
		info = "label build failed";
		error = -ENOMEM;
		जाओ fail;
	पूर्ण अन्यथा अगर (!IS_ERR(target)) अणु
		error = aa_replace_current_label(target);
		अगर (error) अणु
			/* TODO: audit target */
			aa_put_label(target);
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा
		/* alपढ़ोy audited error */
		error = PTR_ERR(target);
out:
	aa_put_buffer(old_buffer);
	aa_put_buffer(new_buffer);

	वापस error;

fail:
	/* TODO: add back in auditing of new_name and old_name */
	error = fn_क्रम_each(label, profile,
			audit_mount(profile, OP_PIVOTROOT, शून्य /*new_name */,
				    शून्य /* old_name */,
				    शून्य, शून्य,
				    0, शून्य, AA_MAY_PIVOTROOT, &nullperms, info,
				    error));
	जाओ out;
पूर्ण
