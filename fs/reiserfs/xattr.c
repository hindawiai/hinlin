<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/reiserfs/xattr.c
 *
 * Copyright (c) 2002 by Jeff Mahoney, <jeffm@suse.com>
 *
 */

/*
 * In order to implement EA/ACLs in a clean, backwards compatible manner,
 * they are implemented as files in a "private" directory.
 * Each EA is in it's own file, with the directory layout like so (/ is assumed
 * to be relative to fs root). Inside the /.reiserfs_priv/xattrs directory,
 * directories named using the capital-hex क्रमm of the objectid and
 * generation number are used. Inside each directory are inभागidual files
 * named with the name of the extended attribute.
 *
 * So, क्रम objectid 12648430, we could have:
 * /.reiserfs_priv/xattrs/C0FFEE.0/प्रणाली.posix_acl_access
 * /.reiserfs_priv/xattrs/C0FFEE.0/प्रणाली.posix_acl_शेष
 * /.reiserfs_priv/xattrs/C0FFEE.0/user.Content-Type
 * .. or similar.
 *
 * The file contents are the text of the EA. The size is known based on the
 * stat data describing the file.
 *
 * In the हाल of प्रणाली.posix_acl_access and प्रणाली.posix_acl_शेष, since
 * these are special हालs क्रम fileप्रणाली ACLs, they are पूर्णांकerpreted by the
 * kernel, in addition, they are negatively and positively cached and attached
 * to the inode so that unnecessary lookups are aव्योमed.
 *
 * Locking works like so:
 * Directory components (xattr root, xattr dir) are protectd by their i_mutex.
 * The xattrs themselves are रक्षित by the xattr_sem.
 */

#समावेश "reiserfs.h"
#समावेश <linux/capability.h>
#समावेश <linux/dcache.h>
#समावेश <linux/namei.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/gfp.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/xattr.h>
#समावेश "xattr.h"
#समावेश "acl.h"
#समावेश <linux/uaccess.h>
#समावेश <net/checksum.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/quotaops.h>
#समावेश <linux/security.h>
#समावेश <linux/posix_acl_xattr.h>

#घोषणा PRIVROOT_NAME ".reiserfs_priv"
#घोषणा XAROOT_NAME   "xattrs"


/*
 * Helpers क्रम inode ops. We करो this so that we करोn't have all the VFS
 * overhead and also क्रम proper i_mutex annotation.
 * dir->i_mutex must be held क्रम all of them.
 */
#अगर_घोषित CONFIG_REISERFS_FS_XATTR
अटल पूर्णांक xattr_create(काष्ठा inode *dir, काष्ठा dentry *dentry, पूर्णांक mode)
अणु
	BUG_ON(!inode_is_locked(dir));
	वापस dir->i_op->create(&init_user_ns, dir, dentry, mode, true);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक xattr_सूची_गढ़ो(काष्ठा inode *dir, काष्ठा dentry *dentry, umode_t mode)
अणु
	BUG_ON(!inode_is_locked(dir));
	वापस dir->i_op->सूची_गढ़ो(&init_user_ns, dir, dentry, mode);
पूर्ण

/*
 * We use I_MUTEX_CHILD here to silence lockdep. It's safe because xattr
 * mutation ops aren't called during नाम or splace, which are the
 * only other users of I_MUTEX_CHILD. It violates the ordering, but that's
 * better than allocating another subclass just क्रम this code.
 */
अटल पूर्णांक xattr_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक error;

	BUG_ON(!inode_is_locked(dir));

	inode_lock_nested(d_inode(dentry), I_MUTEX_CHILD);
	error = dir->i_op->unlink(dir, dentry);
	inode_unlock(d_inode(dentry));

	अगर (!error)
		d_delete(dentry);
	वापस error;
पूर्ण

अटल पूर्णांक xattr_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक error;

	BUG_ON(!inode_is_locked(dir));

	inode_lock_nested(d_inode(dentry), I_MUTEX_CHILD);
	error = dir->i_op->सूची_हटाओ(dir, dentry);
	अगर (!error)
		d_inode(dentry)->i_flags |= S_DEAD;
	inode_unlock(d_inode(dentry));
	अगर (!error)
		d_delete(dentry);

	वापस error;
पूर्ण

#घोषणा xattr_may_create(flags)	(!flags || flags & XATTR_CREATE)

अटल काष्ठा dentry *खोलो_xa_root(काष्ठा super_block *sb, पूर्णांक flags)
अणु
	काष्ठा dentry *privroot = REISERFS_SB(sb)->priv_root;
	काष्ठा dentry *xaroot;

	अगर (d_really_is_negative(privroot))
		वापस ERR_PTR(-EOPNOTSUPP);

	inode_lock_nested(d_inode(privroot), I_MUTEX_XATTR);

	xaroot = dget(REISERFS_SB(sb)->xattr_root);
	अगर (!xaroot)
		xaroot = ERR_PTR(-EOPNOTSUPP);
	अन्यथा अगर (d_really_is_negative(xaroot)) अणु
		पूर्णांक err = -ENODATA;

		अगर (xattr_may_create(flags))
			err = xattr_सूची_गढ़ो(d_inode(privroot), xaroot, 0700);
		अगर (err) अणु
			dput(xaroot);
			xaroot = ERR_PTR(err);
		पूर्ण
	पूर्ण

	inode_unlock(d_inode(privroot));
	वापस xaroot;
पूर्ण

अटल काष्ठा dentry *खोलो_xa_dir(स्थिर काष्ठा inode *inode, पूर्णांक flags)
अणु
	काष्ठा dentry *xaroot, *xadir;
	अक्षर namebuf[17];

	xaroot = खोलो_xa_root(inode->i_sb, flags);
	अगर (IS_ERR(xaroot))
		वापस xaroot;

	snम_लिखो(namebuf, माप(namebuf), "%X.%X",
		 le32_to_cpu(INODE_PKEY(inode)->k_objectid),
		 inode->i_generation);

	inode_lock_nested(d_inode(xaroot), I_MUTEX_XATTR);

	xadir = lookup_one_len(namebuf, xaroot, म_माप(namebuf));
	अगर (!IS_ERR(xadir) && d_really_is_negative(xadir)) अणु
		पूर्णांक err = -ENODATA;

		अगर (xattr_may_create(flags))
			err = xattr_सूची_गढ़ो(d_inode(xaroot), xadir, 0700);
		अगर (err) अणु
			dput(xadir);
			xadir = ERR_PTR(err);
		पूर्ण
	पूर्ण

	inode_unlock(d_inode(xaroot));
	dput(xaroot);
	वापस xadir;
पूर्ण

/*
 * The following are side effects of other operations that aren't explicitly
 * modअगरying extended attributes. This includes operations such as permissions
 * or ownership changes, object deletions, etc.
 */
काष्ठा reiserfs_dentry_buf अणु
	काष्ठा dir_context ctx;
	काष्ठा dentry *xadir;
	पूर्णांक count;
	पूर्णांक err;
	काष्ठा dentry *dentries[8];
पूर्ण;

अटल पूर्णांक
fill_with_dentries(काष्ठा dir_context *ctx, स्थिर अक्षर *name, पूर्णांक namelen,
		   loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा reiserfs_dentry_buf *dbuf =
		container_of(ctx, काष्ठा reiserfs_dentry_buf, ctx);
	काष्ठा dentry *dentry;

	WARN_ON_ONCE(!inode_is_locked(d_inode(dbuf->xadir)));

	अगर (dbuf->count == ARRAY_SIZE(dbuf->dentries))
		वापस -ENOSPC;

	अगर (name[0] == '.' && (namelen < 2 ||
			       (namelen == 2 && name[1] == '.')))
		वापस 0;

	dentry = lookup_one_len(name, dbuf->xadir, namelen);
	अगर (IS_ERR(dentry)) अणु
		dbuf->err = PTR_ERR(dentry);
		वापस PTR_ERR(dentry);
	पूर्ण अन्यथा अगर (d_really_is_negative(dentry)) अणु
		/* A directory entry exists, but no file? */
		reiserfs_error(dentry->d_sb, "xattr-20003",
			       "Corrupted directory: xattr %pd listed but "
			       "not found for file %pd.\n",
			       dentry, dbuf->xadir);
		dput(dentry);
		dbuf->err = -EIO;
		वापस -EIO;
	पूर्ण

	dbuf->dentries[dbuf->count++] = dentry;
	वापस 0;
पूर्ण

अटल व्योम
cleanup_dentry_buf(काष्ठा reiserfs_dentry_buf *buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < buf->count; i++)
		अगर (buf->dentries[i])
			dput(buf->dentries[i]);
पूर्ण

अटल पूर्णांक reiserfs_क्रम_each_xattr(काष्ठा inode *inode,
				   पूर्णांक (*action)(काष्ठा dentry *, व्योम *),
				   व्योम *data)
अणु
	काष्ठा dentry *dir;
	पूर्णांक i, err = 0;
	काष्ठा reiserfs_dentry_buf buf = अणु
		.ctx.actor = fill_with_dentries,
	पूर्ण;

	/* Skip out, an xattr has no xattrs associated with it */
	अगर (IS_PRIVATE(inode) || get_inode_sd_version(inode) == STAT_DATA_V1)
		वापस 0;

	dir = खोलो_xa_dir(inode, XATTR_REPLACE);
	अगर (IS_ERR(dir)) अणु
		err = PTR_ERR(dir);
		जाओ out;
	पूर्ण अन्यथा अगर (d_really_is_negative(dir)) अणु
		err = 0;
		जाओ out_dir;
	पूर्ण

	inode_lock_nested(d_inode(dir), I_MUTEX_XATTR);

	buf.xadir = dir;
	जबतक (1) अणु
		err = reiserfs_सूची_पढ़ो_inode(d_inode(dir), &buf.ctx);
		अगर (err)
			अवरोध;
		अगर (buf.err) अणु
			err = buf.err;
			अवरोध;
		पूर्ण
		अगर (!buf.count)
			अवरोध;
		क्रम (i = 0; !err && i < buf.count && buf.dentries[i]; i++) अणु
			काष्ठा dentry *dentry = buf.dentries[i];

			अगर (!d_is_dir(dentry))
				err = action(dentry, data);

			dput(dentry);
			buf.dentries[i] = शून्य;
		पूर्ण
		अगर (err)
			अवरोध;
		buf.count = 0;
	पूर्ण
	inode_unlock(d_inode(dir));

	cleanup_dentry_buf(&buf);

	अगर (!err) अणु
		/*
		 * We start a transaction here to aव्योम a ABBA situation
		 * between the xattr root's i_mutex and the journal lock.
		 * This करोesn't incur much additional overhead since the
		 * new transaction will just nest inside the
		 * outer transaction.
		 */
		पूर्णांक blocks = JOURNAL_PER_BALANCE_CNT * 2 + 2 +
			     4 * REISERFS_QUOTA_TRANS_BLOCKS(inode->i_sb);
		काष्ठा reiserfs_transaction_handle th;

		reiserfs_ग_लिखो_lock(inode->i_sb);
		err = journal_begin(&th, inode->i_sb, blocks);
		reiserfs_ग_लिखो_unlock(inode->i_sb);
		अगर (!err) अणु
			पूर्णांक jerror;

			inode_lock_nested(d_inode(dir->d_parent),
					  I_MUTEX_XATTR);
			err = action(dir, data);
			reiserfs_ग_लिखो_lock(inode->i_sb);
			jerror = journal_end(&th);
			reiserfs_ग_लिखो_unlock(inode->i_sb);
			inode_unlock(d_inode(dir->d_parent));
			err = jerror ?: err;
		पूर्ण
	पूर्ण
out_dir:
	dput(dir);
out:
	/*
	 * -ENODATA: this object करोesn't have any xattrs
	 * -EOPNOTSUPP: this file प्रणाली करोesn't have xattrs enabled on disk.
	 * Neither are errors
	 */
	अगर (err == -ENODATA || err == -EOPNOTSUPP)
		err = 0;
	वापस err;
पूर्ण

अटल पूर्णांक delete_one_xattr(काष्ठा dentry *dentry, व्योम *data)
अणु
	काष्ठा inode *dir = d_inode(dentry->d_parent);

	/* This is the xattr dir, handle specially. */
	अगर (d_is_dir(dentry))
		वापस xattr_सूची_हटाओ(dir, dentry);

	वापस xattr_unlink(dir, dentry);
पूर्ण

अटल पूर्णांक chown_one_xattr(काष्ठा dentry *dentry, व्योम *data)
अणु
	काष्ठा iattr *attrs = data;
	पूर्णांक ia_valid = attrs->ia_valid;
	पूर्णांक err;

	/*
	 * We only want the ownership bits. Otherwise, we'll करो
	 * things like change a directory to a regular file अगर
	 * ATTR_MODE is set.
	 */
	attrs->ia_valid &= (ATTR_UID|ATTR_GID);
	err = reiserfs_setattr(&init_user_ns, dentry, attrs);
	attrs->ia_valid = ia_valid;

	वापस err;
पूर्ण

/* No i_mutex, but the inode is unconnected. */
पूर्णांक reiserfs_delete_xattrs(काष्ठा inode *inode)
अणु
	पूर्णांक err = reiserfs_क्रम_each_xattr(inode, delete_one_xattr, शून्य);

	अगर (err)
		reiserfs_warning(inode->i_sb, "jdm-20004",
				 "Couldn't delete all xattrs (%d)\n", err);
	वापस err;
पूर्ण

/* inode->i_mutex: करोwn */
पूर्णांक reiserfs_chown_xattrs(काष्ठा inode *inode, काष्ठा iattr *attrs)
अणु
	पूर्णांक err = reiserfs_क्रम_each_xattr(inode, chown_one_xattr, attrs);

	अगर (err)
		reiserfs_warning(inode->i_sb, "jdm-20007",
				 "Couldn't chown all xattrs (%d)\n", err);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_REISERFS_FS_XATTR
/*
 * Returns a dentry corresponding to a specअगरic extended attribute file
 * क्रम the inode. If flags allow, the file is created. Otherwise, a
 * valid or negative dentry, or an error is वापसed.
 */
अटल काष्ठा dentry *xattr_lookup(काष्ठा inode *inode, स्थिर अक्षर *name,
				    पूर्णांक flags)
अणु
	काष्ठा dentry *xadir, *xafile;
	पूर्णांक err = 0;

	xadir = खोलो_xa_dir(inode, flags);
	अगर (IS_ERR(xadir))
		वापस ERR_CAST(xadir);

	inode_lock_nested(d_inode(xadir), I_MUTEX_XATTR);
	xafile = lookup_one_len(name, xadir, म_माप(name));
	अगर (IS_ERR(xafile)) अणु
		err = PTR_ERR(xafile);
		जाओ out;
	पूर्ण

	अगर (d_really_is_positive(xafile) && (flags & XATTR_CREATE))
		err = -EEXIST;

	अगर (d_really_is_negative(xafile)) अणु
		err = -ENODATA;
		अगर (xattr_may_create(flags))
			err = xattr_create(d_inode(xadir), xafile,
					      0700|S_IFREG);
	पूर्ण

	अगर (err)
		dput(xafile);
out:
	inode_unlock(d_inode(xadir));
	dput(xadir);
	अगर (err)
		वापस ERR_PTR(err);
	वापस xafile;
पूर्ण

/* Internal operations on file data */
अटल अंतरभूत व्योम reiserfs_put_page(काष्ठा page *page)
अणु
	kunmap(page);
	put_page(page);
पूर्ण

अटल काष्ठा page *reiserfs_get_page(काष्ठा inode *dir, माप_प्रकार n)
अणु
	काष्ठा address_space *mapping = dir->i_mapping;
	काष्ठा page *page;
	/*
	 * We can deadlock अगर we try to मुक्त dentries,
	 * and an unlink/सूची_हटाओ has just occurred - GFP_NOFS aव्योमs this
	 */
	mapping_set_gfp_mask(mapping, GFP_NOFS);
	page = पढ़ो_mapping_page(mapping, n >> PAGE_SHIFT, शून्य);
	अगर (!IS_ERR(page)) अणु
		kmap(page);
		अगर (PageError(page))
			जाओ fail;
	पूर्ण
	वापस page;

fail:
	reiserfs_put_page(page);
	वापस ERR_PTR(-EIO);
पूर्ण

अटल अंतरभूत __u32 xattr_hash(स्थिर अक्षर *msg, पूर्णांक len)
अणु
	/*
	 * csum_partial() gives dअगरferent results क्रम little-endian and
	 * big endian hosts. Images created on little-endian hosts and
	 * mounted on big-endian hosts(and vice versa) will see csum mismatches
	 * when trying to fetch xattrs. Treating the hash as __wsum_t would
	 * lower the frequency of mismatch.  This is an endianness bug in
	 * reiserfs.  The वापस statement would result in a sparse warning. Do
	 * not fix the sparse warning so as to not hide a reminder of the bug.
	 */
	वापस csum_partial(msg, len, 0);
पूर्ण

पूर्णांक reiserfs_commit_ग_लिखो(काष्ठा file *f, काष्ठा page *page,
			  अचिन्हित from, अचिन्हित to);

अटल व्योम update_स_समय(काष्ठा inode *inode)
अणु
	काष्ठा बारpec64 now = current_समय(inode);

	अगर (inode_unhashed(inode) || !inode->i_nlink ||
	    बारpec64_equal(&inode->i_स_समय, &now))
		वापस;

	inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);
पूर्ण

अटल पूर्णांक lookup_and_delete_xattr(काष्ठा inode *inode, स्थिर अक्षर *name)
अणु
	पूर्णांक err = 0;
	काष्ठा dentry *dentry, *xadir;

	xadir = खोलो_xa_dir(inode, XATTR_REPLACE);
	अगर (IS_ERR(xadir))
		वापस PTR_ERR(xadir);

	inode_lock_nested(d_inode(xadir), I_MUTEX_XATTR);
	dentry = lookup_one_len(name, xadir, म_माप(name));
	अगर (IS_ERR(dentry)) अणु
		err = PTR_ERR(dentry);
		जाओ out_dput;
	पूर्ण

	अगर (d_really_is_positive(dentry)) अणु
		err = xattr_unlink(d_inode(xadir), dentry);
		update_स_समय(inode);
	पूर्ण

	dput(dentry);
out_dput:
	inode_unlock(d_inode(xadir));
	dput(xadir);
	वापस err;
पूर्ण


/* Generic extended attribute operations that can be used by xa plugins */

/*
 * inode->i_mutex: करोwn
 */
पूर्णांक
reiserfs_xattr_set_handle(काष्ठा reiserfs_transaction_handle *th,
			  काष्ठा inode *inode, स्थिर अक्षर *name,
			  स्थिर व्योम *buffer, माप_प्रकार buffer_size, पूर्णांक flags)
अणु
	पूर्णांक err = 0;
	काष्ठा dentry *dentry;
	काष्ठा page *page;
	अक्षर *data;
	माप_प्रकार file_pos = 0;
	माप_प्रकार buffer_pos = 0;
	माप_प्रकार new_size;
	__u32 xahash = 0;

	अगर (get_inode_sd_version(inode) == STAT_DATA_V1)
		वापस -EOPNOTSUPP;

	अगर (!buffer) अणु
		err = lookup_and_delete_xattr(inode, name);
		वापस err;
	पूर्ण

	dentry = xattr_lookup(inode, name, flags);
	अगर (IS_ERR(dentry))
		वापस PTR_ERR(dentry);

	करोwn_ग_लिखो(&REISERFS_I(inode)->i_xattr_sem);

	xahash = xattr_hash(buffer, buffer_size);
	जबतक (buffer_pos < buffer_size || buffer_pos == 0) अणु
		माप_प्रकार chunk;
		माप_प्रकार skip = 0;
		माप_प्रकार page_offset = (file_pos & (PAGE_SIZE - 1));

		अगर (buffer_size - buffer_pos > PAGE_SIZE)
			chunk = PAGE_SIZE;
		अन्यथा
			chunk = buffer_size - buffer_pos;

		page = reiserfs_get_page(d_inode(dentry), file_pos);
		अगर (IS_ERR(page)) अणु
			err = PTR_ERR(page);
			जाओ out_unlock;
		पूर्ण

		lock_page(page);
		data = page_address(page);

		अगर (file_pos == 0) अणु
			काष्ठा reiserfs_xattr_header *rxh;

			skip = file_pos = माप(काष्ठा reiserfs_xattr_header);
			अगर (chunk + skip > PAGE_SIZE)
				chunk = PAGE_SIZE - skip;
			rxh = (काष्ठा reiserfs_xattr_header *)data;
			rxh->h_magic = cpu_to_le32(REISERFS_XATTR_MAGIC);
			rxh->h_hash = cpu_to_le32(xahash);
		पूर्ण

		reiserfs_ग_लिखो_lock(inode->i_sb);
		err = __reiserfs_ग_लिखो_begin(page, page_offset, chunk + skip);
		अगर (!err) अणु
			अगर (buffer)
				स_नकल(data + skip, buffer + buffer_pos, chunk);
			err = reiserfs_commit_ग_लिखो(शून्य, page, page_offset,
						    page_offset + chunk +
						    skip);
		पूर्ण
		reiserfs_ग_लिखो_unlock(inode->i_sb);
		unlock_page(page);
		reiserfs_put_page(page);
		buffer_pos += chunk;
		file_pos += chunk;
		skip = 0;
		अगर (err || buffer_size == 0 || !buffer)
			अवरोध;
	पूर्ण

	new_size = buffer_size + माप(काष्ठा reiserfs_xattr_header);
	अगर (!err && new_size < i_size_पढ़ो(d_inode(dentry))) अणु
		काष्ठा iattr newattrs = अणु
			.ia_स_समय = current_समय(inode),
			.ia_size = new_size,
			.ia_valid = ATTR_SIZE | ATTR_CTIME,
		पूर्ण;

		inode_lock_nested(d_inode(dentry), I_MUTEX_XATTR);
		inode_dio_रुको(d_inode(dentry));

		err = reiserfs_setattr(&init_user_ns, dentry, &newattrs);
		inode_unlock(d_inode(dentry));
	पूर्ण अन्यथा
		update_स_समय(inode);
out_unlock:
	up_ग_लिखो(&REISERFS_I(inode)->i_xattr_sem);
	dput(dentry);
	वापस err;
पूर्ण

/* We need to start a transaction to मुख्यtain lock ordering */
पूर्णांक reiserfs_xattr_set(काष्ठा inode *inode, स्थिर अक्षर *name,
		       स्थिर व्योम *buffer, माप_प्रकार buffer_size, पूर्णांक flags)
अणु

	काष्ठा reiserfs_transaction_handle th;
	पूर्णांक error, error2;
	माप_प्रकार jbegin_count = reiserfs_xattr_nblocks(inode, buffer_size);

	/* Check beक्रमe we start a transaction and then करो nothing. */
	अगर (!d_really_is_positive(REISERFS_SB(inode->i_sb)->priv_root))
		वापस -EOPNOTSUPP;

	अगर (!(flags & XATTR_REPLACE))
		jbegin_count += reiserfs_xattr_jcreate_nblocks(inode);

	reiserfs_ग_लिखो_lock(inode->i_sb);
	error = journal_begin(&th, inode->i_sb, jbegin_count);
	reiserfs_ग_लिखो_unlock(inode->i_sb);
	अगर (error) अणु
		वापस error;
	पूर्ण

	error = reiserfs_xattr_set_handle(&th, inode, name,
					  buffer, buffer_size, flags);

	reiserfs_ग_लिखो_lock(inode->i_sb);
	error2 = journal_end(&th);
	reiserfs_ग_लिखो_unlock(inode->i_sb);
	अगर (error == 0)
		error = error2;

	वापस error;
पूर्ण

/*
 * inode->i_mutex: करोwn
 */
पूर्णांक
reiserfs_xattr_get(काष्ठा inode *inode, स्थिर अक्षर *name, व्योम *buffer,
		   माप_प्रकार buffer_size)
अणु
	sमाप_प्रकार err = 0;
	काष्ठा dentry *dentry;
	माप_प्रकार isize;
	माप_प्रकार file_pos = 0;
	माप_प्रकार buffer_pos = 0;
	काष्ठा page *page;
	__u32 hash = 0;

	अगर (name == शून्य)
		वापस -EINVAL;

	/*
	 * We can't have xattrs attached to v1 items since they don't have
	 * generation numbers
	 */
	अगर (get_inode_sd_version(inode) == STAT_DATA_V1)
		वापस -EOPNOTSUPP;

	/*
	 * priv_root needn't be initialized during mount so allow initial
	 * lookups to succeed.
	 */
	अगर (!REISERFS_SB(inode->i_sb)->priv_root)
		वापस 0;

	dentry = xattr_lookup(inode, name, XATTR_REPLACE);
	अगर (IS_ERR(dentry)) अणु
		err = PTR_ERR(dentry);
		जाओ out;
	पूर्ण

	करोwn_पढ़ो(&REISERFS_I(inode)->i_xattr_sem);

	isize = i_size_पढ़ो(d_inode(dentry));

	/* Just वापस the size needed */
	अगर (buffer == शून्य) अणु
		err = isize - माप(काष्ठा reiserfs_xattr_header);
		जाओ out_unlock;
	पूर्ण

	अगर (buffer_size < isize - माप(काष्ठा reiserfs_xattr_header)) अणु
		err = -दुस्फल;
		जाओ out_unlock;
	पूर्ण

	जबतक (file_pos < isize) अणु
		माप_प्रकार chunk;
		अक्षर *data;
		माप_प्रकार skip = 0;

		अगर (isize - file_pos > PAGE_SIZE)
			chunk = PAGE_SIZE;
		अन्यथा
			chunk = isize - file_pos;

		page = reiserfs_get_page(d_inode(dentry), file_pos);
		अगर (IS_ERR(page)) अणु
			err = PTR_ERR(page);
			जाओ out_unlock;
		पूर्ण

		lock_page(page);
		data = page_address(page);
		अगर (file_pos == 0) अणु
			काष्ठा reiserfs_xattr_header *rxh =
			    (काष्ठा reiserfs_xattr_header *)data;
			skip = file_pos = माप(काष्ठा reiserfs_xattr_header);
			chunk -= skip;
			/* Magic करोesn't match up.. */
			अगर (rxh->h_magic != cpu_to_le32(REISERFS_XATTR_MAGIC)) अणु
				unlock_page(page);
				reiserfs_put_page(page);
				reiserfs_warning(inode->i_sb, "jdm-20001",
						 "Invalid magic for xattr (%s) "
						 "associated with %k", name,
						 INODE_PKEY(inode));
				err = -EIO;
				जाओ out_unlock;
			पूर्ण
			hash = le32_to_cpu(rxh->h_hash);
		पूर्ण
		स_नकल(buffer + buffer_pos, data + skip, chunk);
		unlock_page(page);
		reiserfs_put_page(page);
		file_pos += chunk;
		buffer_pos += chunk;
		skip = 0;
	पूर्ण
	err = isize - माप(काष्ठा reiserfs_xattr_header);

	अगर (xattr_hash(buffer, isize - माप(काष्ठा reiserfs_xattr_header)) !=
	    hash) अणु
		reiserfs_warning(inode->i_sb, "jdm-20002",
				 "Invalid hash for xattr (%s) associated "
				 "with %k", name, INODE_PKEY(inode));
		err = -EIO;
	पूर्ण

out_unlock:
	up_पढ़ो(&REISERFS_I(inode)->i_xattr_sem);
	dput(dentry);

out:
	वापस err;
पूर्ण

/*
 * In order to implement dअगरferent sets of xattr operations क्रम each xattr
 * prefix with the generic xattr API, a fileप्रणाली should create a
 * null-terminated array of काष्ठा xattr_handler (one क्रम each prefix) and
 * hang a poपूर्णांकer to it off of the s_xattr field of the superblock.
 *
 * The generic_fooxattr() functions will use this list to dispatch xattr
 * operations to the correct xattr_handler.
 */
#घोषणा क्रम_each_xattr_handler(handlers, handler)		\
		क्रम ((handler) = *(handlers)++;			\
			(handler) != शून्य;			\
			(handler) = *(handlers)++)

/* This is the implementation क्रम the xattr plugin infraकाष्ठाure */
अटल अंतरभूत स्थिर काष्ठा xattr_handler *
find_xattr_handler_prefix(स्थिर काष्ठा xattr_handler **handlers,
			   स्थिर अक्षर *name)
अणु
	स्थिर काष्ठा xattr_handler *xah;

	अगर (!handlers)
		वापस शून्य;

	क्रम_each_xattr_handler(handlers, xah) अणु
		स्थिर अक्षर *prefix = xattr_prefix(xah);
		अगर (म_भेदन(prefix, name, म_माप(prefix)) == 0)
			अवरोध;
	पूर्ण

	वापस xah;
पूर्ण

काष्ठा listxattr_buf अणु
	काष्ठा dir_context ctx;
	माप_प्रकार size;
	माप_प्रकार pos;
	अक्षर *buf;
	काष्ठा dentry *dentry;
पूर्ण;

अटल पूर्णांक listxattr_filler(काष्ठा dir_context *ctx, स्थिर अक्षर *name,
			    पूर्णांक namelen, loff_t offset, u64 ino,
			    अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा listxattr_buf *b =
		container_of(ctx, काष्ठा listxattr_buf, ctx);
	माप_प्रकार size;

	अगर (name[0] != '.' ||
	    (namelen != 1 && (name[1] != '.' || namelen != 2))) अणु
		स्थिर काष्ठा xattr_handler *handler;

		handler = find_xattr_handler_prefix(b->dentry->d_sb->s_xattr,
						    name);
		अगर (!handler /* Unsupported xattr name */ ||
		    (handler->list && !handler->list(b->dentry)))
			वापस 0;
		size = namelen + 1;
		अगर (b->buf) अणु
			अगर (b->pos + size > b->size) अणु
				b->pos = -दुस्फल;
				वापस -दुस्फल;
			पूर्ण
			स_नकल(b->buf + b->pos, name, namelen);
			b->buf[b->pos + namelen] = 0;
		पूर्ण
		b->pos += size;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Inode operation listxattr()
 *
 * We totally ignore the generic listxattr here because it would be stupid
 * not to. Since the xattrs are organized in a directory, we can just
 * सूची_पढ़ो to find them.
 */
sमाप_प्रकार reiserfs_listxattr(काष्ठा dentry * dentry, अक्षर *buffer, माप_प्रकार size)
अणु
	काष्ठा dentry *dir;
	पूर्णांक err = 0;
	काष्ठा listxattr_buf buf = अणु
		.ctx.actor = listxattr_filler,
		.dentry = dentry,
		.buf = buffer,
		.size = buffer ? size : 0,
	पूर्ण;

	अगर (d_really_is_negative(dentry))
		वापस -EINVAL;

	अगर (get_inode_sd_version(d_inode(dentry)) == STAT_DATA_V1)
		वापस -EOPNOTSUPP;

	dir = खोलो_xa_dir(d_inode(dentry), XATTR_REPLACE);
	अगर (IS_ERR(dir)) अणु
		err = PTR_ERR(dir);
		अगर (err == -ENODATA)
			err = 0;  /* Not an error अगर there aren't any xattrs */
		जाओ out;
	पूर्ण

	inode_lock_nested(d_inode(dir), I_MUTEX_XATTR);
	err = reiserfs_सूची_पढ़ो_inode(d_inode(dir), &buf.ctx);
	inode_unlock(d_inode(dir));

	अगर (!err)
		err = buf.pos;

	dput(dir);
out:
	वापस err;
पूर्ण

अटल पूर्णांक create_privroot(काष्ठा dentry *dentry)
अणु
	पूर्णांक err;
	काष्ठा inode *inode = d_inode(dentry->d_parent);

	WARN_ON_ONCE(!inode_is_locked(inode));

	err = xattr_सूची_गढ़ो(inode, dentry, 0700);
	अगर (err || d_really_is_negative(dentry)) अणु
		reiserfs_warning(dentry->d_sb, "jdm-20006",
				 "xattrs/ACLs enabled and couldn't "
				 "find/create .reiserfs_priv. "
				 "Failing mount.");
		वापस -EOPNOTSUPP;
	पूर्ण

	d_inode(dentry)->i_flags |= S_PRIVATE;
	d_inode(dentry)->i_opflags &= ~IOP_XATTR;
	reiserfs_info(dentry->d_sb, "Created %s - reserved for xattr "
		      "storage.\n", PRIVROOT_NAME);

	वापस 0;
पूर्ण

#अन्यथा
पूर्णांक __init reiserfs_xattr_रेजिस्टर_handlers(व्योम) अणु वापस 0; पूर्ण
व्योम reiserfs_xattr_unरेजिस्टर_handlers(व्योम) अणुपूर्ण
अटल पूर्णांक create_privroot(काष्ठा dentry *dentry) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/* Actual operations that are exported to VFS-land */
स्थिर काष्ठा xattr_handler *reiserfs_xattr_handlers[] = अणु
#अगर_घोषित CONFIG_REISERFS_FS_XATTR
	&reiserfs_xattr_user_handler,
	&reiserfs_xattr_trusted_handler,
#पूर्ण_अगर
#अगर_घोषित CONFIG_REISERFS_FS_SECURITY
	&reiserfs_xattr_security_handler,
#पूर्ण_अगर
#अगर_घोषित CONFIG_REISERFS_FS_POSIX_ACL
	&posix_acl_access_xattr_handler,
	&posix_acl_शेष_xattr_handler,
#पूर्ण_अगर
	शून्य
पूर्ण;

अटल पूर्णांक xattr_mount_check(काष्ठा super_block *s)
अणु
	/*
	 * We need generation numbers to ensure that the oid mapping is correct
	 * v3.5 fileप्रणालीs करोn't have them.
	 */
	अगर (old_क्रमmat_only(s)) अणु
		अगर (reiserfs_xattrs_optional(s)) अणु
			/*
			 * Old क्रमmat fileप्रणाली, but optional xattrs have
			 * been enabled. Error out.
			 */
			reiserfs_warning(s, "jdm-2005",
					 "xattrs/ACLs not supported "
					 "on pre-v3.6 format filesystems. "
					 "Failing mount.");
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक reiserfs_permission(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
			पूर्णांक mask)
अणु
	/*
	 * We करोn't करो permission checks on the पूर्णांकernal objects.
	 * Permissions are determined by the "owning" object.
	 */
	अगर (IS_PRIVATE(inode))
		वापस 0;

	वापस generic_permission(&init_user_ns, inode, mask);
पूर्ण

अटल पूर्णांक xattr_hide_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	वापस -EPERM;
पूर्ण

अटल स्थिर काष्ठा dentry_operations xattr_lookup_poison_ops = अणु
	.d_revalidate = xattr_hide_revalidate,
पूर्ण;

पूर्णांक reiserfs_lookup_privroot(काष्ठा super_block *s)
अणु
	काष्ठा dentry *dentry;
	पूर्णांक err = 0;

	/* If we करोn't have the privroot located yet - go find it */
	inode_lock(d_inode(s->s_root));
	dentry = lookup_one_len(PRIVROOT_NAME, s->s_root,
				म_माप(PRIVROOT_NAME));
	अगर (!IS_ERR(dentry)) अणु
		REISERFS_SB(s)->priv_root = dentry;
		d_set_d_op(dentry, &xattr_lookup_poison_ops);
		अगर (d_really_is_positive(dentry)) अणु
			d_inode(dentry)->i_flags |= S_PRIVATE;
			d_inode(dentry)->i_opflags &= ~IOP_XATTR;
		पूर्ण
	पूर्ण अन्यथा
		err = PTR_ERR(dentry);
	inode_unlock(d_inode(s->s_root));

	वापस err;
पूर्ण

/*
 * We need to take a copy of the mount flags since things like
 * SB_RDONLY करोn't get set until *after* we're called.
 * mount_flags != mount_options
 */
पूर्णांक reiserfs_xattr_init(काष्ठा super_block *s, पूर्णांक mount_flags)
अणु
	पूर्णांक err = 0;
	काष्ठा dentry *privroot = REISERFS_SB(s)->priv_root;

	err = xattr_mount_check(s);
	अगर (err)
		जाओ error;

	अगर (d_really_is_negative(privroot) && !(mount_flags & SB_RDONLY)) अणु
		inode_lock(d_inode(s->s_root));
		err = create_privroot(REISERFS_SB(s)->priv_root);
		inode_unlock(d_inode(s->s_root));
	पूर्ण

	अगर (d_really_is_positive(privroot)) अणु
		inode_lock(d_inode(privroot));
		अगर (!REISERFS_SB(s)->xattr_root) अणु
			काष्ठा dentry *dentry;

			dentry = lookup_one_len(XAROOT_NAME, privroot,
						म_माप(XAROOT_NAME));
			अगर (!IS_ERR(dentry))
				REISERFS_SB(s)->xattr_root = dentry;
			अन्यथा
				err = PTR_ERR(dentry);
		पूर्ण
		inode_unlock(d_inode(privroot));
	पूर्ण

error:
	अगर (err) अणु
		clear_bit(REISERFS_XATTRS_USER, &REISERFS_SB(s)->s_mount_opt);
		clear_bit(REISERFS_POSIXACL, &REISERFS_SB(s)->s_mount_opt);
	पूर्ण

	/* The super_block SB_POSIXACL must mirror the (no)acl mount option. */
	अगर (reiserfs_posixacl(s))
		s->s_flags |= SB_POSIXACL;
	अन्यथा
		s->s_flags &= ~SB_POSIXACL;

	वापस err;
पूर्ण
