<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * security/tomoyo/realpath.c
 *
 * Copyright (C) 2005-2011  NTT DATA CORPORATION
 */

#समावेश "common.h"
#समावेश <linux/magic.h>
#समावेश <linux/proc_fs.h>

/**
 * tomoyo_encode2 - Encode binary string to ascii string.
 *
 * @str:     String in binary क्रमmat.
 * @str_len: Size of @str in byte.
 *
 * Returns poपूर्णांकer to @str in ascii क्रमmat on success, शून्य otherwise.
 *
 * This function uses kzalloc(), so caller must kमुक्त() अगर this function
 * didn't वापस शून्य.
 */
अक्षर *tomoyo_encode2(स्थिर अक्षर *str, पूर्णांक str_len)
अणु
	पूर्णांक i;
	पूर्णांक len = 0;
	स्थिर अक्षर *p = str;
	अक्षर *cp;
	अक्षर *cp0;

	अगर (!p)
		वापस शून्य;
	क्रम (i = 0; i < str_len; i++) अणु
		स्थिर अचिन्हित अक्षर c = p[i];

		अगर (c == '\\')
			len += 2;
		अन्यथा अगर (c > ' ' && c < 127)
			len++;
		अन्यथा
			len += 4;
	पूर्ण
	len++;
	/* Reserve space क्रम appending "/". */
	cp = kzalloc(len + 10, GFP_NOFS);
	अगर (!cp)
		वापस शून्य;
	cp0 = cp;
	p = str;
	क्रम (i = 0; i < str_len; i++) अणु
		स्थिर अचिन्हित अक्षर c = p[i];

		अगर (c == '\\') अणु
			*cp++ = '\\';
			*cp++ = '\\';
		पूर्ण अन्यथा अगर (c > ' ' && c < 127) अणु
			*cp++ = c;
		पूर्ण अन्यथा अणु
			*cp++ = '\\';
			*cp++ = (c >> 6) + '0';
			*cp++ = ((c >> 3) & 7) + '0';
			*cp++ = (c & 7) + '0';
		पूर्ण
	पूर्ण
	वापस cp0;
पूर्ण

/**
 * tomoyo_encode - Encode binary string to ascii string.
 *
 * @str: String in binary क्रमmat.
 *
 * Returns poपूर्णांकer to @str in ascii क्रमmat on success, शून्य otherwise.
 *
 * This function uses kzalloc(), so caller must kमुक्त() अगर this function
 * didn't वापस शून्य.
 */
अक्षर *tomoyo_encode(स्थिर अक्षर *str)
अणु
	वापस str ? tomoyo_encode2(str, म_माप(str)) : शून्य;
पूर्ण

/**
 * tomoyo_get_असलolute_path - Get the path of a dentry but ignores chroot'ed root.
 *
 * @path:   Poपूर्णांकer to "struct path".
 * @buffer: Poपूर्णांकer to buffer to वापस value in.
 * @buflen: Sizeof @buffer.
 *
 * Returns the buffer on success, an error code otherwise.
 *
 * If dentry is a directory, trailing '/' is appended.
 */
अटल अक्षर *tomoyo_get_असलolute_path(स्थिर काष्ठा path *path, अक्षर * स्थिर buffer,
				      स्थिर पूर्णांक buflen)
अणु
	अक्षर *pos = ERR_PTR(-ENOMEM);

	अगर (buflen >= 256) अणु
		/* go to whatever namespace root we are under */
		pos = d_असलolute_path(path, buffer, buflen - 1);
		अगर (!IS_ERR(pos) && *pos == '/' && pos[1]) अणु
			काष्ठा inode *inode = d_backing_inode(path->dentry);

			अगर (inode && S_ISसूची(inode->i_mode)) अणु
				buffer[buflen - 2] = '/';
				buffer[buflen - 1] = '\0';
			पूर्ण
		पूर्ण
	पूर्ण
	वापस pos;
पूर्ण

/**
 * tomoyo_get_dentry_path - Get the path of a dentry.
 *
 * @dentry: Poपूर्णांकer to "struct dentry".
 * @buffer: Poपूर्णांकer to buffer to वापस value in.
 * @buflen: Sizeof @buffer.
 *
 * Returns the buffer on success, an error code otherwise.
 *
 * If dentry is a directory, trailing '/' is appended.
 */
अटल अक्षर *tomoyo_get_dentry_path(काष्ठा dentry *dentry, अक्षर * स्थिर buffer,
				    स्थिर पूर्णांक buflen)
अणु
	अक्षर *pos = ERR_PTR(-ENOMEM);

	अगर (buflen >= 256) अणु
		pos = dentry_path_raw(dentry, buffer, buflen - 1);
		अगर (!IS_ERR(pos) && *pos == '/' && pos[1]) अणु
			काष्ठा inode *inode = d_backing_inode(dentry);

			अगर (inode && S_ISसूची(inode->i_mode)) अणु
				buffer[buflen - 2] = '/';
				buffer[buflen - 1] = '\0';
			पूर्ण
		पूर्ण
	पूर्ण
	वापस pos;
पूर्ण

/**
 * tomoyo_get_local_path - Get the path of a dentry.
 *
 * @dentry: Poपूर्णांकer to "struct dentry".
 * @buffer: Poपूर्णांकer to buffer to वापस value in.
 * @buflen: Sizeof @buffer.
 *
 * Returns the buffer on success, an error code otherwise.
 */
अटल अक्षर *tomoyo_get_local_path(काष्ठा dentry *dentry, अक्षर * स्थिर buffer,
				   स्थिर पूर्णांक buflen)
अणु
	काष्ठा super_block *sb = dentry->d_sb;
	अक्षर *pos = tomoyo_get_dentry_path(dentry, buffer, buflen);

	अगर (IS_ERR(pos))
		वापस pos;
	/* Convert from $PID to self अगर $PID is current thपढ़ो. */
	अगर (sb->s_magic == PROC_SUPER_MAGIC && *pos == '/') अणु
		अक्षर *ep;
		स्थिर pid_t pid = (pid_t) simple_म_से_अदीर्घ(pos + 1, &ep, 10);
		काष्ठा pid_namespace *proc_pidns = proc_pid_ns(sb);

		अगर (*ep == '/' && pid && pid ==
		    task_tgid_nr_ns(current, proc_pidns)) अणु
			pos = ep - 5;
			अगर (pos < buffer)
				जाओ out;
			स_हटाओ(pos, "/self", 5);
		पूर्ण
		जाओ prepend_fileप्रणाली_name;
	पूर्ण
	/* Use fileप्रणाली name क्रम unnamed devices. */
	अगर (!MAJOR(sb->s_dev))
		जाओ prepend_fileप्रणाली_name;
	अणु
		काष्ठा inode *inode = d_backing_inode(sb->s_root);

		/*
		 * Use fileप्रणाली name अगर fileप्रणाली करोes not support नाम()
		 * operation.
		 */
		अगर (!inode->i_op->नाम)
			जाओ prepend_fileप्रणाली_name;
	पूर्ण
	/* Prepend device name. */
	अणु
		अक्षर name[64];
		पूर्णांक name_len;
		स्थिर dev_t dev = sb->s_dev;

		name[माप(name) - 1] = '\0';
		snम_लिखो(name, माप(name) - 1, "dev(%u,%u):", MAJOR(dev),
			 MINOR(dev));
		name_len = म_माप(name);
		pos -= name_len;
		अगर (pos < buffer)
			जाओ out;
		स_हटाओ(pos, name, name_len);
		वापस pos;
	पूर्ण
	/* Prepend fileप्रणाली name. */
prepend_fileप्रणाली_name:
	अणु
		स्थिर अक्षर *name = sb->s_type->name;
		स्थिर पूर्णांक name_len = म_माप(name);

		pos -= name_len + 1;
		अगर (pos < buffer)
			जाओ out;
		स_हटाओ(pos, name, name_len);
		pos[name_len] = ':';
	पूर्ण
	वापस pos;
out:
	वापस ERR_PTR(-ENOMEM);
पूर्ण

/**
 * tomoyo_realpath_from_path - Returns realpath(3) of the given pathname but ignores chroot'ed root.
 *
 * @path: Poपूर्णांकer to "struct path".
 *
 * Returns the realpath of the given @path on success, शून्य otherwise.
 *
 * If dentry is a directory, trailing '/' is appended.
 * Characters out of 0x20 < c < 0x7F range are converted to
 * \ooo style octal string.
 * Character \ is converted to \\ string.
 *
 * These functions use kzalloc(), so the caller must call kमुक्त()
 * अगर these functions didn't वापस शून्य.
 */
अक्षर *tomoyo_realpath_from_path(स्थिर काष्ठा path *path)
अणु
	अक्षर *buf = शून्य;
	अक्षर *name = शून्य;
	अचिन्हित पूर्णांक buf_len = PAGE_SIZE / 2;
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा super_block *sb;

	अगर (!dentry)
		वापस शून्य;
	sb = dentry->d_sb;
	जबतक (1) अणु
		अक्षर *pos;
		काष्ठा inode *inode;

		buf_len <<= 1;
		kमुक्त(buf);
		buf = kदो_स्मृति(buf_len, GFP_NOFS);
		अगर (!buf)
			अवरोध;
		/* To make sure that pos is '\0' terminated. */
		buf[buf_len - 1] = '\0';
		/* For "pipe:[\$]" and "socket:[\$]". */
		अगर (dentry->d_op && dentry->d_op->d_dname) अणु
			pos = dentry->d_op->d_dname(dentry, buf, buf_len - 1);
			जाओ encode;
		पूर्ण
		inode = d_backing_inode(sb->s_root);
		/*
		 * Get local name क्रम fileप्रणालीs without नाम() operation
		 * or dentry without vfsmount.
		 */
		अगर (!path->mnt ||
		    (!inode->i_op->नाम &&
		     !(sb->s_type->fs_flags & FS_REQUIRES_DEV)))
			pos = tomoyo_get_local_path(path->dentry, buf,
						    buf_len - 1);
		/* Get असलolute name क्रम the rest. */
		अन्यथा अणु
			pos = tomoyo_get_असलolute_path(path, buf, buf_len - 1);
			/*
			 * Fall back to local name अगर असलolute name is not
			 * available.
			 */
			अगर (pos == ERR_PTR(-EINVAL))
				pos = tomoyo_get_local_path(path->dentry, buf,
							    buf_len - 1);
		पूर्ण
encode:
		अगर (IS_ERR(pos))
			जारी;
		name = tomoyo_encode(pos);
		अवरोध;
	पूर्ण
	kमुक्त(buf);
	अगर (!name)
		tomoyo_warn_oom(__func__);
	वापस name;
पूर्ण

/**
 * tomoyo_realpath_nofollow - Get realpath of a pathname.
 *
 * @pathname: The pathname to solve.
 *
 * Returns the realpath of @pathname on success, शून्य otherwise.
 */
अक्षर *tomoyo_realpath_nofollow(स्थिर अक्षर *pathname)
अणु
	काष्ठा path path;

	अगर (pathname && kern_path(pathname, 0, &path) == 0) अणु
		अक्षर *buf = tomoyo_realpath_from_path(&path);

		path_put(&path);
		वापस buf;
	पूर्ण
	वापस शून्य;
पूर्ण
