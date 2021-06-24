<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

/*
 * Directory operations क्रम Coda fileप्रणाली
 * Original version: (C) 1996 P. Braam and M. Callahan
 * Rewritten क्रम Linux 2.1. (C) 1997 Carnegie Mellon University
 * 
 * Carnegie Mellon encourages users to contribute improvements to
 * the Coda project. Contact Peter Braam (coda@cs.cmu.edu).
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/समय.स>
#समावेश <linux/fs.h>
#समावेश <linux/slab.h>
#समावेश <linux/file.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/spinlock.h>
#समावेश <linux/namei.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/coda.h>
#समावेश "coda_psdev.h"
#समावेश "coda_linux.h"
#समावेश "coda_cache.h"

#समावेश "coda_int.h"

/* same as fs/bad_inode.c */
अटल पूर्णांक coda_वापस_EIO(व्योम)
अणु
	वापस -EIO;
पूर्ण
#घोषणा CODA_EIO_ERROR ((व्योम *) (coda_वापस_EIO))

/* inode operations क्रम directories */
/* access routines: lookup, पढ़ोlink, permission */
अटल काष्ठा dentry *coda_lookup(काष्ठा inode *dir, काष्ठा dentry *entry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	स्थिर अक्षर *name = entry->d_name.name;
	माप_प्रकार length = entry->d_name.len;
	काष्ठा inode *inode;
	पूर्णांक type = 0;

	अगर (length > CODA_MAXNAMLEN) अणु
		pr_err("name too long: lookup, %s %zu\n",
		       coda_i2s(dir), length);
		वापस ERR_PTR(-ENAMETOOLONG);
	पूर्ण

	/* control object, create inode on the fly */
	अगर (is_root_inode(dir) && coda_iscontrol(name, length)) अणु
		inode = coda_cnode_makectl(sb);
		type = CODA_NOCACHE;
	पूर्ण अन्यथा अणु
		काष्ठा CodaFid fid = अणु अणु 0, पूर्ण पूर्ण;
		पूर्णांक error = venus_lookup(sb, coda_i2f(dir), name, length,
				     &type, &fid);
		inode = !error ? coda_cnode_make(&fid, sb) : ERR_PTR(error);
	पूर्ण

	अगर (!IS_ERR(inode) && (type & CODA_NOCACHE))
		coda_flag_inode(inode, C_VATTR | C_PURGE);

	अगर (inode == ERR_PTR(-ENOENT))
		inode = शून्य;

	वापस d_splice_alias(inode, entry);
पूर्ण


पूर्णांक coda_permission(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		    पूर्णांक mask)
अणु
	पूर्णांक error;

	अगर (mask & MAY_NOT_BLOCK)
		वापस -ECHILD;

	mask &= MAY_READ | MAY_WRITE | MAY_EXEC;
 
	अगर (!mask)
		वापस 0;

	अगर ((mask & MAY_EXEC) && !execute_ok(inode))
		वापस -EACCES;

	अगर (coda_cache_check(inode, mask))
		वापस 0;

	error = venus_access(inode->i_sb, coda_i2f(inode), mask);
    
	अगर (!error)
		coda_cache_enter(inode, mask);

	वापस error;
पूर्ण


अटल अंतरभूत व्योम coda_dir_update_mसमय(काष्ठा inode *dir)
अणु
#अगर_घोषित REQUERY_VENUS_FOR_MTIME
	/* invalidate the directory cnode's attributes so we refetch the
	 * attributes from venus next समय the inode is referenced */
	coda_flag_inode(dir, C_VATTR);
#अन्यथा
	/* optimistically we can also act as अगर our nose bleeds. The
	 * granularity of the mसमय is coarse anyways so we might actually be
	 * right most of the समय. Note: we only करो this क्रम directories. */
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);
#पूर्ण_अगर
पूर्ण

/* we have to wrap inc_nlink/drop_nlink because someबार userspace uses a
 * trick to fool GNU find's optimizations. If we can't be sure of the link
 * (because of volume mount poपूर्णांकs) we set i_nlink to 1 which क्रमces find
 * to consider every child as a possible directory. We should also never
 * see an increment or decrement क्रम deleted directories where i_nlink == 0 */
अटल अंतरभूत व्योम coda_dir_inc_nlink(काष्ठा inode *dir)
अणु
	अगर (dir->i_nlink >= 2)
		inc_nlink(dir);
पूर्ण

अटल अंतरभूत व्योम coda_dir_drop_nlink(काष्ठा inode *dir)
अणु
	अगर (dir->i_nlink > 2)
		drop_nlink(dir);
पूर्ण

/* creation routines: create, mknod, सूची_गढ़ो, link, symlink */
अटल पूर्णांक coda_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *de, umode_t mode, bool excl)
अणु
	पूर्णांक error;
	स्थिर अक्षर *name=de->d_name.name;
	पूर्णांक length=de->d_name.len;
	काष्ठा inode *inode;
	काष्ठा CodaFid newfid;
	काष्ठा coda_vattr attrs;

	अगर (is_root_inode(dir) && coda_iscontrol(name, length))
		वापस -EPERM;

	error = venus_create(dir->i_sb, coda_i2f(dir), name, length, 
				0, mode, &newfid, &attrs);
	अगर (error)
		जाओ err_out;

	inode = coda_iget(dir->i_sb, &newfid, &attrs);
	अगर (IS_ERR(inode)) अणु
		error = PTR_ERR(inode);
		जाओ err_out;
	पूर्ण

	/* invalidate the directory cnode's attributes */
	coda_dir_update_mसमय(dir);
	d_instantiate(de, inode);
	वापस 0;
err_out:
	d_drop(de);
	वापस error;
पूर्ण

अटल पूर्णांक coda_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *de, umode_t mode)
अणु
	काष्ठा inode *inode;
	काष्ठा coda_vattr attrs;
	स्थिर अक्षर *name = de->d_name.name;
	पूर्णांक len = de->d_name.len;
	पूर्णांक error;
	काष्ठा CodaFid newfid;

	अगर (is_root_inode(dir) && coda_iscontrol(name, len))
		वापस -EPERM;

	attrs.va_mode = mode;
	error = venus_सूची_गढ़ो(dir->i_sb, coda_i2f(dir), 
			       name, len, &newfid, &attrs);
	अगर (error)
		जाओ err_out;
         
	inode = coda_iget(dir->i_sb, &newfid, &attrs);
	अगर (IS_ERR(inode)) अणु
		error = PTR_ERR(inode);
		जाओ err_out;
	पूर्ण

	/* invalidate the directory cnode's attributes */
	coda_dir_inc_nlink(dir);
	coda_dir_update_mसमय(dir);
	d_instantiate(de, inode);
	वापस 0;
err_out:
	d_drop(de);
	वापस error;
पूर्ण

/* try to make de an entry in dir_inodde linked to source_de */ 
अटल पूर्णांक coda_link(काष्ठा dentry *source_de, काष्ठा inode *dir_inode, 
	  काष्ठा dentry *de)
अणु
	काष्ठा inode *inode = d_inode(source_de);
        स्थिर अक्षर * name = de->d_name.name;
	पूर्णांक len = de->d_name.len;
	पूर्णांक error;

	अगर (is_root_inode(dir_inode) && coda_iscontrol(name, len))
		वापस -EPERM;

	error = venus_link(dir_inode->i_sb, coda_i2f(inode),
			   coda_i2f(dir_inode), (स्थिर अक्षर *)name, len);
	अगर (error) अणु
		d_drop(de);
		वापस error;
	पूर्ण

	coda_dir_update_mसमय(dir_inode);
	ihold(inode);
	d_instantiate(de, inode);
	inc_nlink(inode);
	वापस 0;
पूर्ण


अटल पूर्णांक coda_symlink(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *dir_inode, काष्ठा dentry *de,
			स्थिर अक्षर *symname)
अणु
	स्थिर अक्षर *name = de->d_name.name;
	पूर्णांक len = de->d_name.len;
	पूर्णांक symlen;
	पूर्णांक error;

	अगर (is_root_inode(dir_inode) && coda_iscontrol(name, len))
		वापस -EPERM;

	symlen = म_माप(symname);
	अगर (symlen > CODA_MAXPATHLEN)
		वापस -ENAMETOOLONG;

	/*
	 * This entry is now negative. Since we करो not create
	 * an inode क्रम the entry we have to drop it.
	 */
	d_drop(de);
	error = venus_symlink(dir_inode->i_sb, coda_i2f(dir_inode), name, len,
			      symname, symlen);

	/* mसमय is no good anymore */
	अगर (!error)
		coda_dir_update_mसमय(dir_inode);

	वापस error;
पूर्ण

/* deकाष्ठाion routines: unlink, सूची_हटाओ */
अटल पूर्णांक coda_unlink(काष्ठा inode *dir, काष्ठा dentry *de)
अणु
        पूर्णांक error;
	स्थिर अक्षर *name = de->d_name.name;
	पूर्णांक len = de->d_name.len;

	error = venus_हटाओ(dir->i_sb, coda_i2f(dir), name, len);
	अगर (error)
		वापस error;

	coda_dir_update_mसमय(dir);
	drop_nlink(d_inode(de));
	वापस 0;
पूर्ण

अटल पूर्णांक coda_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *de)
अणु
	स्थिर अक्षर *name = de->d_name.name;
	पूर्णांक len = de->d_name.len;
	पूर्णांक error;

	error = venus_सूची_हटाओ(dir->i_sb, coda_i2f(dir), name, len);
	अगर (!error) अणु
		/* VFS may delete the child */
		अगर (d_really_is_positive(de))
			clear_nlink(d_inode(de));

		/* fix the link count of the parent */
		coda_dir_drop_nlink(dir);
		coda_dir_update_mसमय(dir);
	पूर्ण
	वापस error;
पूर्ण

/* नाम */
अटल पूर्णांक coda_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		       काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		       काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	स्थिर अक्षर *old_name = old_dentry->d_name.name;
	स्थिर अक्षर *new_name = new_dentry->d_name.name;
	पूर्णांक old_length = old_dentry->d_name.len;
	पूर्णांक new_length = new_dentry->d_name.len;
	पूर्णांक error;

	अगर (flags)
		वापस -EINVAL;

	error = venus_नाम(old_dir->i_sb, coda_i2f(old_dir),
			     coda_i2f(new_dir), old_length, new_length,
			     (स्थिर अक्षर *) old_name, (स्थिर अक्षर *)new_name);
	अगर (!error) अणु
		अगर (d_really_is_positive(new_dentry)) अणु
			अगर (d_is_dir(new_dentry)) अणु
				coda_dir_drop_nlink(old_dir);
				coda_dir_inc_nlink(new_dir);
			पूर्ण
			coda_dir_update_mसमय(old_dir);
			coda_dir_update_mसमय(new_dir);
			coda_flag_inode(d_inode(new_dentry), C_VATTR);
		पूर्ण अन्यथा अणु
			coda_flag_inode(old_dir, C_VATTR);
			coda_flag_inode(new_dir, C_VATTR);
		पूर्ण
	पूर्ण
	वापस error;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक CDT2DT(अचिन्हित अक्षर cdt)
अणु
	अचिन्हित पूर्णांक dt;

	चयन(cdt) अणु
	हाल CDT_UNKNOWN: dt = DT_UNKNOWN; अवरोध;
	हाल CDT_FIFO:	  dt = DT_FIFO;    अवरोध;
	हाल CDT_CHR:	  dt = DT_CHR;     अवरोध;
	हाल CDT_सूची:	  dt = DT_सूची;     अवरोध;
	हाल CDT_BLK:	  dt = DT_BLK;     अवरोध;
	हाल CDT_REG:	  dt = DT_REG;     अवरोध;
	हाल CDT_LNK:	  dt = DT_LNK;     अवरोध;
	हाल CDT_SOCK:	  dt = DT_SOCK;    अवरोध;
	हाल CDT_WHT:	  dt = DT_WHT;     अवरोध;
	शेष:	  dt = DT_UNKNOWN; अवरोध;
	पूर्ण
	वापस dt;
पूर्ण

/* support routines */
अटल पूर्णांक coda_venus_सूची_पढ़ो(काष्ठा file *coda_file, काष्ठा dir_context *ctx)
अणु
	काष्ठा coda_file_info *cfi;
	काष्ठा coda_inode_info *cii;
	काष्ठा file *host_file;
	काष्ठा venus_dirent *vdir;
	अचिन्हित दीर्घ vdir_size = दुरत्व(काष्ठा venus_dirent, d_name);
	अचिन्हित पूर्णांक type;
	काष्ठा qstr name;
	ino_t ino;
	पूर्णांक ret;

	cfi = coda_ftoc(coda_file);
	host_file = cfi->cfi_container;

	cii = ITOC(file_inode(coda_file));

	vdir = kदो_स्मृति(माप(*vdir), GFP_KERNEL);
	अगर (!vdir) वापस -ENOMEM;

	अगर (!dir_emit_करोts(coda_file, ctx))
		जाओ out;

	जबतक (1) अणु
		loff_t pos = ctx->pos - 2;

		/* पढ़ो entries from the directory file */
		ret = kernel_पढ़ो(host_file, vdir, माप(*vdir), &pos);
		अगर (ret < 0) अणु
			pr_err("%s: read dir %s failed %d\n",
			       __func__, coda_f2s(&cii->c_fid), ret);
			अवरोध;
		पूर्ण
		अगर (ret == 0) अवरोध; /* end of directory file reached */

		/* catch truncated पढ़ोs */
		अगर (ret < vdir_size || ret < vdir_size + vdir->d_namlen) अणु
			pr_err("%s: short read on %s\n",
			       __func__, coda_f2s(&cii->c_fid));
			ret = -EBADF;
			अवरोध;
		पूर्ण
		/* validate whether the directory file actually makes sense */
		अगर (vdir->d_reclen < vdir_size + vdir->d_namlen) अणु
			pr_err("%s: invalid dir %s\n",
			       __func__, coda_f2s(&cii->c_fid));
			ret = -EBADF;
			अवरोध;
		पूर्ण

		name.len = vdir->d_namlen;
		name.name = vdir->d_name;

		/* Make sure we skip '.' and '..', we alपढ़ोy got those */
		अगर (name.name[0] == '.' && (name.len == 1 ||
		    (name.name[1] == '.' && name.len == 2)))
			vdir->d_fileno = name.len = 0;

		/* skip null entries */
		अगर (vdir->d_fileno && name.len) अणु
			ino = vdir->d_fileno;
			type = CDT2DT(vdir->d_type);
			अगर (!dir_emit(ctx, name.name, name.len, ino, type))
				अवरोध;
		पूर्ण
		/* we'll always have progress because d_reclen is अचिन्हित and
		 * we've alपढ़ोy established it is non-zero. */
		ctx->pos += vdir->d_reclen;
	पूर्ण
out:
	kमुक्त(vdir);
	वापस 0;
पूर्ण

/* file operations क्रम directories */
अटल पूर्णांक coda_सूची_पढ़ो(काष्ठा file *coda_file, काष्ठा dir_context *ctx)
अणु
	काष्ठा coda_file_info *cfi;
	काष्ठा file *host_file;
	पूर्णांक ret;

	cfi = coda_ftoc(coda_file);
	host_file = cfi->cfi_container;

	अगर (host_file->f_op->iterate || host_file->f_op->iterate_shared) अणु
		काष्ठा inode *host_inode = file_inode(host_file);
		ret = -ENOENT;
		अगर (!IS_DEADसूची(host_inode)) अणु
			अगर (host_file->f_op->iterate_shared) अणु
				inode_lock_shared(host_inode);
				ret = host_file->f_op->iterate_shared(host_file, ctx);
				file_accessed(host_file);
				inode_unlock_shared(host_inode);
			पूर्ण अन्यथा अणु
				inode_lock(host_inode);
				ret = host_file->f_op->iterate(host_file, ctx);
				file_accessed(host_file);
				inode_unlock(host_inode);
			पूर्ण
		पूर्ण
		वापस ret;
	पूर्ण
	/* Venus: we must पढ़ो Venus dirents from a file */
	वापस coda_venus_सूची_पढ़ो(coda_file, ctx);
पूर्ण

/* called when a cache lookup succeeds */
अटल पूर्णांक coda_dentry_revalidate(काष्ठा dentry *de, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode;
	काष्ठा coda_inode_info *cii;

	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	inode = d_inode(de);
	अगर (!inode || is_root_inode(inode))
		जाओ out;
	अगर (is_bad_inode(inode))
		जाओ bad;

	cii = ITOC(d_inode(de));
	अगर (!(cii->c_flags & (C_PURGE | C_FLUSH)))
		जाओ out;

	shrink_dcache_parent(de);

	/* propagate क्रम a flush */
	अगर (cii->c_flags & C_FLUSH) 
		coda_flag_inode_children(inode, C_FLUSH);

	अगर (d_count(de) > 1)
		/* pretend it's valid, but don't change the flags */
		जाओ out;

	/* clear the flags. */
	spin_lock(&cii->c_lock);
	cii->c_flags &= ~(C_VATTR | C_PURGE | C_FLUSH);
	spin_unlock(&cii->c_lock);
bad:
	वापस 0;
out:
	वापस 1;
पूर्ण

/*
 * This is the callback from dput() when d_count is going to 0.
 * We use this to unhash dentries with bad inodes.
 */
अटल पूर्णांक coda_dentry_delete(स्थिर काष्ठा dentry * dentry)
अणु
	पूर्णांक flags;

	अगर (d_really_is_negative(dentry)) 
		वापस 0;

	flags = (ITOC(d_inode(dentry))->c_flags) & C_PURGE;
	अगर (is_bad_inode(d_inode(dentry)) || flags) अणु
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण



/*
 * This is called when we want to check अगर the inode has
 * changed on the server.  Coda makes this easy since the
 * cache manager Venus issues a करोwncall to the kernel when this 
 * happens 
 */
पूर्णांक coda_revalidate_inode(काष्ठा inode *inode)
अणु
	काष्ठा coda_vattr attr;
	पूर्णांक error;
	पूर्णांक old_mode;
	ino_t old_ino;
	काष्ठा coda_inode_info *cii = ITOC(inode);

	अगर (!cii->c_flags)
		वापस 0;

	अगर (cii->c_flags & (C_VATTR | C_PURGE | C_FLUSH)) अणु
		error = venus_getattr(inode->i_sb, &(cii->c_fid), &attr);
		अगर (error)
			वापस -EIO;

		/* this inode may be lost अगर:
		   - it's ino changed 
		   - type changes must be permitted क्रम repair and
		   missing mount poपूर्णांकs.
		*/
		old_mode = inode->i_mode;
		old_ino = inode->i_ino;
		coda_vattr_to_iattr(inode, &attr);

		अगर ((old_mode & S_IFMT) != (inode->i_mode & S_IFMT)) अणु
			pr_warn("inode %ld, fid %s changed type!\n",
				inode->i_ino, coda_f2s(&(cii->c_fid)));
		पूर्ण

		/* the following can happen when a local fid is replaced 
		   with a global one, here we lose and declare the inode bad */
		अगर (inode->i_ino != old_ino)
			वापस -EIO;
		
		coda_flag_inode_children(inode, C_FLUSH);

		spin_lock(&cii->c_lock);
		cii->c_flags &= ~(C_VATTR | C_PURGE | C_FLUSH);
		spin_unlock(&cii->c_lock);
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा dentry_operations coda_dentry_operations = अणु
	.d_revalidate	= coda_dentry_revalidate,
	.d_delete	= coda_dentry_delete,
पूर्ण;

स्थिर काष्ठा inode_operations coda_dir_inode_operations = अणु
	.create		= coda_create,
	.lookup		= coda_lookup,
	.link		= coda_link,
	.unlink		= coda_unlink,
	.symlink	= coda_symlink,
	.सूची_गढ़ो		= coda_सूची_गढ़ो,
	.सूची_हटाओ		= coda_सूची_हटाओ,
	.mknod		= CODA_EIO_ERROR,
	.नाम		= coda_नाम,
	.permission	= coda_permission,
	.getattr	= coda_getattr,
	.setattr	= coda_setattr,
पूर्ण;

स्थिर काष्ठा file_operations coda_dir_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate	= coda_सूची_पढ़ो,
	.खोलो		= coda_खोलो,
	.release	= coda_release,
	.fsync		= coda_fsync,
पूर्ण;
