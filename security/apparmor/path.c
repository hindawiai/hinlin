<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor function क्रम pathnames
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#समावेश <linux/magic.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/nsproxy.h>
#समावेश <linux/path.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs_काष्ठा.h>

#समावेश "include/apparmor.h"
#समावेश "include/path.h"
#समावेश "include/policy.h"

/* modअगरied from dcache.c */
अटल पूर्णांक prepend(अक्षर **buffer, पूर्णांक buflen, स्थिर अक्षर *str, पूर्णांक namelen)
अणु
	buflen -= namelen;
	अगर (buflen < 0)
		वापस -ENAMETOOLONG;
	*buffer -= namelen;
	स_नकल(*buffer, str, namelen);
	वापस 0;
पूर्ण

#घोषणा CHROOT_NSCONNECT (PATH_CHROOT_REL | PATH_CHROOT_NSCONNECT)

/* If the path is not connected to the expected root,
 * check अगर it is a sysctl and handle specially अन्यथा हटाओ any
 * leading / that __d_path may have वापसed.
 * Unless
 *     specअगरically directed to connect the path,
 * OR
 *     अगर in a chroot and करोing chroot relative paths and the path
 *     resolves to the namespace root (would be connected outside
 *     of chroot) and specअगरically directed to connect paths to
 *     namespace root.
 */
अटल पूर्णांक disconnect(स्थिर काष्ठा path *path, अक्षर *buf, अक्षर **name,
		      पूर्णांक flags, स्थिर अक्षर *disconnected)
अणु
	पूर्णांक error = 0;

	अगर (!(flags & PATH_CONNECT_PATH) &&
	    !(((flags & CHROOT_NSCONNECT) == CHROOT_NSCONNECT) &&
	      our_mnt(path->mnt))) अणु
		/* disconnected path, करोn't वापस pathname starting
		 * with '/'
		 */
		error = -EACCES;
		अगर (**name == '/')
			*name = *name + 1;
	पूर्ण अन्यथा अणु
		अगर (**name != '/')
			/* CONNECT_PATH with missing root */
			error = prepend(name, *name - buf, "/", 1);
		अगर (!error && disconnected)
			error = prepend(name, *name - buf, disconnected,
					म_माप(disconnected));
	पूर्ण

	वापस error;
पूर्ण

/**
 * d_namespace_path - lookup a name associated with a given path
 * @path: path to lookup  (NOT शून्य)
 * @buf:  buffer to store path to  (NOT शून्य)
 * @name: Returns - poपूर्णांकer क्रम start of path name with in @buf (NOT शून्य)
 * @flags: flags controlling path lookup
 * @disconnected: string to prefix to disconnected paths
 *
 * Handle path name lookup.
 *
 * Returns: %0 अन्यथा error code अगर path lookup fails
 *          When no error the path name is वापसed in @name which poपूर्णांकs to
 *          to a position in @buf
 */
अटल पूर्णांक d_namespace_path(स्थिर काष्ठा path *path, अक्षर *buf, अक्षर **name,
			    पूर्णांक flags, स्थिर अक्षर *disconnected)
अणु
	अक्षर *res;
	पूर्णांक error = 0;
	पूर्णांक connected = 1;
	पूर्णांक isdir = (flags & PATH_IS_सूची) ? 1 : 0;
	पूर्णांक buflen = aa_g_path_max - isdir;

	अगर (path->mnt->mnt_flags & MNT_INTERNAL) अणु
		/* it's not mounted anywhere */
		res = dentry_path(path->dentry, buf, buflen);
		*name = res;
		अगर (IS_ERR(res)) अणु
			*name = buf;
			वापस PTR_ERR(res);
		पूर्ण
		अगर (path->dentry->d_sb->s_magic == PROC_SUPER_MAGIC &&
		    म_भेदन(*name, "/sys/", 5) == 0) अणु
			/* TODO: convert over to using a per namespace
			 * control instead of hard coded /proc
			 */
			error = prepend(name, *name - buf, "/proc", 5);
			जाओ out;
		पूर्ण अन्यथा
			error = disconnect(path, buf, name, flags,
					   disconnected);
		जाओ out;
	पूर्ण

	/* resolve paths relative to chroot?*/
	अगर (flags & PATH_CHROOT_REL) अणु
		काष्ठा path root;
		get_fs_root(current->fs, &root);
		res = __d_path(path, &root, buf, buflen);
		path_put(&root);
	पूर्ण अन्यथा अणु
		res = d_असलolute_path(path, buf, buflen);
		अगर (!our_mnt(path->mnt))
			connected = 0;
	पूर्ण

	/* handle error conditions - and still allow a partial path to
	 * be वापसed.
	 */
	अगर (!res || IS_ERR(res)) अणु
		अगर (PTR_ERR(res) == -ENAMETOOLONG) अणु
			error = -ENAMETOOLONG;
			*name = buf;
			जाओ out;
		पूर्ण
		connected = 0;
		res = dentry_path_raw(path->dentry, buf, buflen);
		अगर (IS_ERR(res)) अणु
			error = PTR_ERR(res);
			*name = buf;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अगर (!our_mnt(path->mnt))
		connected = 0;

	*name = res;

	अगर (!connected)
		error = disconnect(path, buf, name, flags, disconnected);

	/* Handle two हालs:
	 * 1. A deleted dentry && profile is not allowing mediation of deleted
	 * 2. On some fileप्रणालीs, newly allocated dentries appear to the
	 *    security_path hooks as a deleted dentry except without an inode
	 *    allocated.
	 */
	अगर (d_unlinked(path->dentry) && d_is_positive(path->dentry) &&
	    !(flags & (PATH_MEDIATE_DELETED | PATH_DELEGATE_DELETED))) अणु
			error = -ENOENT;
			जाओ out;
	पूर्ण

out:
	/*
	 * Append "/" to the pathname.  The root directory is a special
	 * हाल; it alपढ़ोy ends in slash.
	 */
	अगर (!error && isdir && ((*name)[1] != '\0' || (*name)[0] != '/'))
		म_नकल(&buf[aa_g_path_max - 2], "/");

	वापस error;
पूर्ण

/**
 * aa_path_name - get the pathname to a buffer ensure dir / is appended
 * @path: path the file  (NOT शून्य)
 * @flags: flags controlling path name generation
 * @buffer: buffer to put name in (NOT शून्य)
 * @name: Returns - the generated path name अगर !error (NOT शून्य)
 * @info: Returns - inक्रमmation on why the path lookup failed (MAYBE शून्य)
 * @disconnected: string to prepend to disconnected paths
 *
 * @name is a poपूर्णांकer to the beginning of the pathname (which usually dअगरfers
 * from the beginning of the buffer), or शून्य.  If there is an error @name
 * may contain a partial or invalid name that can be used क्रम audit purposes,
 * but it can not be used क्रम mediation.
 *
 * We need PATH_IS_सूची to indicate whether the file is a directory or not
 * because the file may not yet exist, and so we cannot check the inode's
 * file type.
 *
 * Returns: %0 अन्यथा error code अगर could retrieve name
 */
पूर्णांक aa_path_name(स्थिर काष्ठा path *path, पूर्णांक flags, अक्षर *buffer,
		 स्थिर अक्षर **name, स्थिर अक्षर **info, स्थिर अक्षर *disconnected)
अणु
	अक्षर *str = शून्य;
	पूर्णांक error = d_namespace_path(path, buffer, &str, flags, disconnected);

	अगर (info && error) अणु
		अगर (error == -ENOENT)
			*info = "Failed name lookup - deleted entry";
		अन्यथा अगर (error == -EACCES)
			*info = "Failed name lookup - disconnected path";
		अन्यथा अगर (error == -ENAMETOOLONG)
			*info = "Failed name lookup - name too long";
		अन्यथा
			*info = "Failed name lookup";
	पूर्ण

	*name = str;

	वापस error;
पूर्ण
