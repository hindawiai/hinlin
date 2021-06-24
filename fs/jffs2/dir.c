<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 * Copyright तऊ 2004-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/fs.h>
#समावेश <linux/crc32.h>
#समावेश <linux/jffs2.h>
#समावेश "jffs2_fs_i.h"
#समावेश "jffs2_fs_sb.h"
#समावेश <linux/समय.स>
#समावेश "nodelist.h"

अटल पूर्णांक jffs2_सूची_पढ़ो (काष्ठा file *, काष्ठा dir_context *);

अटल पूर्णांक jffs2_create (काष्ठा user_namespace *, काष्ठा inode *,
		         काष्ठा dentry *, umode_t, bool);
अटल काष्ठा dentry *jffs2_lookup (काष्ठा inode *,काष्ठा dentry *,
				    अचिन्हित पूर्णांक);
अटल पूर्णांक jffs2_link (काष्ठा dentry *,काष्ठा inode *,काष्ठा dentry *);
अटल पूर्णांक jffs2_unlink (काष्ठा inode *,काष्ठा dentry *);
अटल पूर्णांक jffs2_symlink (काष्ठा user_namespace *, काष्ठा inode *,
			  काष्ठा dentry *, स्थिर अक्षर *);
अटल पूर्णांक jffs2_सूची_गढ़ो (काष्ठा user_namespace *, काष्ठा inode *,काष्ठा dentry *,
			umode_t);
अटल पूर्णांक jffs2_सूची_हटाओ (काष्ठा inode *,काष्ठा dentry *);
अटल पूर्णांक jffs2_mknod (काष्ठा user_namespace *, काष्ठा inode *,काष्ठा dentry *,
			umode_t,dev_t);
अटल पूर्णांक jffs2_नाम (काष्ठा user_namespace *, काष्ठा inode *,
			 काष्ठा dentry *, काष्ठा inode *, काष्ठा dentry *,
			 अचिन्हित पूर्णांक);

स्थिर काष्ठा file_operations jffs2_dir_operations =
अणु
	.पढ़ो =		generic_पढ़ो_dir,
	.iterate_shared=jffs2_सूची_पढ़ो,
	.unlocked_ioctl=jffs2_ioctl,
	.fsync =	jffs2_fsync,
	.llseek =	generic_file_llseek,
पूर्ण;


स्थिर काष्ठा inode_operations jffs2_dir_inode_operations =
अणु
	.create =	jffs2_create,
	.lookup =	jffs2_lookup,
	.link =		jffs2_link,
	.unlink =	jffs2_unlink,
	.symlink =	jffs2_symlink,
	.सूची_गढ़ो =	jffs2_सूची_गढ़ो,
	.सूची_हटाओ =	jffs2_सूची_हटाओ,
	.mknod =	jffs2_mknod,
	.नाम =	jffs2_नाम,
	.get_acl =	jffs2_get_acl,
	.set_acl =	jffs2_set_acl,
	.setattr =	jffs2_setattr,
	.listxattr =	jffs2_listxattr,
पूर्ण;

/***********************************************************************/


/* We keep the dirent list sorted in increasing order of name hash,
   and we use the same hash function as the dentries. Makes this
   nice and simple
*/
अटल काष्ठा dentry *jffs2_lookup(काष्ठा inode *dir_i, काष्ठा dentry *target,
				   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा jffs2_inode_info *dir_f;
	काष्ठा jffs2_full_dirent *fd = शून्य, *fd_list;
	uपूर्णांक32_t ino = 0;
	काष्ठा inode *inode = शून्य;
	अचिन्हित पूर्णांक nhash;

	jffs2_dbg(1, "jffs2_lookup()\n");

	अगर (target->d_name.len > JFFS2_MAX_NAME_LEN)
		वापस ERR_PTR(-ENAMETOOLONG);

	dir_f = JFFS2_INODE_INFO(dir_i);

	/* The 'nhash' on the fd_list is not the same as the dentry hash */
	nhash = full_name_hash(शून्य, target->d_name.name, target->d_name.len);

	mutex_lock(&dir_f->sem);

	/* NB: The 2.2 backport will need to explicitly check क्रम '.' and '..' here */
	क्रम (fd_list = dir_f->dents; fd_list && fd_list->nhash <= nhash; fd_list = fd_list->next) अणु
		अगर (fd_list->nhash == nhash &&
		    (!fd || fd_list->version > fd->version) &&
		    म_माप(fd_list->name) == target->d_name.len &&
		    !म_भेदन(fd_list->name, target->d_name.name, target->d_name.len)) अणु
			fd = fd_list;
		पूर्ण
	पूर्ण
	अगर (fd)
		ino = fd->ino;
	mutex_unlock(&dir_f->sem);
	अगर (ino) अणु
		inode = jffs2_iget(dir_i->i_sb, ino);
		अगर (IS_ERR(inode))
			pr_warn("iget() failed for ino #%u\n", ino);
	पूर्ण

	वापस d_splice_alias(inode, target);
पूर्ण

/***********************************************************************/


अटल पूर्णांक jffs2_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	काष्ठा jffs2_full_dirent *fd;
	अचिन्हित दीर्घ curofs = 1;

	jffs2_dbg(1, "jffs2_readdir() for dir_i #%lu\n", inode->i_ino);

	अगर (!dir_emit_करोts(file, ctx))
		वापस 0;

	mutex_lock(&f->sem);
	क्रम (fd = f->dents; fd; fd = fd->next) अणु
		curofs++;
		/* First loop: curofs = 2; pos = 2 */
		अगर (curofs < ctx->pos) अणु
			jffs2_dbg(2, "Skipping dirent: \"%s\", ino #%u, type %d, because curofs %ld < offset %ld\n",
				  fd->name, fd->ino, fd->type, curofs, (अचिन्हित दीर्घ)ctx->pos);
			जारी;
		पूर्ण
		अगर (!fd->ino) अणु
			jffs2_dbg(2, "Skipping deletion dirent \"%s\"\n",
				  fd->name);
			ctx->pos++;
			जारी;
		पूर्ण
		jffs2_dbg(2, "Dirent %ld: \"%s\", ino #%u, type %d\n",
			  (अचिन्हित दीर्घ)ctx->pos, fd->name, fd->ino, fd->type);
		अगर (!dir_emit(ctx, fd->name, म_माप(fd->name), fd->ino, fd->type))
			अवरोध;
		ctx->pos++;
	पूर्ण
	mutex_unlock(&f->sem);
	वापस 0;
पूर्ण

/***********************************************************************/


अटल पूर्णांक jffs2_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir_i,
			काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	काष्ठा jffs2_raw_inode *ri;
	काष्ठा jffs2_inode_info *f, *dir_f;
	काष्ठा jffs2_sb_info *c;
	काष्ठा inode *inode;
	पूर्णांक ret;

	ri = jffs2_alloc_raw_inode();
	अगर (!ri)
		वापस -ENOMEM;

	c = JFFS2_SB_INFO(dir_i->i_sb);

	jffs2_dbg(1, "%s()\n", __func__);

	inode = jffs2_new_inode(dir_i, mode, ri);

	अगर (IS_ERR(inode)) अणु
		jffs2_dbg(1, "jffs2_new_inode() failed\n");
		jffs2_मुक्त_raw_inode(ri);
		वापस PTR_ERR(inode);
	पूर्ण

	inode->i_op = &jffs2_file_inode_operations;
	inode->i_fop = &jffs2_file_operations;
	inode->i_mapping->a_ops = &jffs2_file_address_operations;
	inode->i_mapping->nrpages = 0;

	f = JFFS2_INODE_INFO(inode);
	dir_f = JFFS2_INODE_INFO(dir_i);

	/* jffs2_करो_create() will want to lock it, _after_ reserving
	   space and taking c-alloc_sem. If we keep it locked here,
	   lockdep माला_लो unhappy (although it's a false positive;
	   nothing अन्यथा will be looking at this inode yet so there's
	   no chance of AB-BA deadlock involving its f->sem). */
	mutex_unlock(&f->sem);

	ret = jffs2_करो_create(c, dir_f, f, ri, &dentry->d_name);
	अगर (ret)
		जाओ fail;

	dir_i->i_mसमय = dir_i->i_स_समय = ITIME(je32_to_cpu(ri->स_समय));

	jffs2_मुक्त_raw_inode(ri);

	jffs2_dbg(1, "%s(): Created ino #%lu with mode %o, nlink %d(%d). nrpages %ld\n",
		  __func__, inode->i_ino, inode->i_mode, inode->i_nlink,
		  f->inocache->pino_nlink, inode->i_mapping->nrpages);

	d_instantiate_new(dentry, inode);
	वापस 0;

 fail:
	iget_failed(inode);
	jffs2_मुक्त_raw_inode(ri);
	वापस ret;
पूर्ण

/***********************************************************************/


अटल पूर्णांक jffs2_unlink(काष्ठा inode *dir_i, काष्ठा dentry *dentry)
अणु
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(dir_i->i_sb);
	काष्ठा jffs2_inode_info *dir_f = JFFS2_INODE_INFO(dir_i);
	काष्ठा jffs2_inode_info *dead_f = JFFS2_INODE_INFO(d_inode(dentry));
	पूर्णांक ret;
	uपूर्णांक32_t now = JFFS2_NOW();

	ret = jffs2_करो_unlink(c, dir_f, dentry->d_name.name,
			      dentry->d_name.len, dead_f, now);
	अगर (dead_f->inocache)
		set_nlink(d_inode(dentry), dead_f->inocache->pino_nlink);
	अगर (!ret)
		dir_i->i_mसमय = dir_i->i_स_समय = ITIME(now);
	वापस ret;
पूर्ण
/***********************************************************************/


अटल पूर्णांक jffs2_link (काष्ठा dentry *old_dentry, काष्ठा inode *dir_i, काष्ठा dentry *dentry)
अणु
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(old_dentry->d_sb);
	काष्ठा jffs2_inode_info *f = JFFS2_INODE_INFO(d_inode(old_dentry));
	काष्ठा jffs2_inode_info *dir_f = JFFS2_INODE_INFO(dir_i);
	पूर्णांक ret;
	uपूर्णांक8_t type;
	uपूर्णांक32_t now;

	/* Don't let people make hard links to bad inodes. */
	अगर (!f->inocache)
		वापस -EIO;

	अगर (d_is_dir(old_dentry))
		वापस -EPERM;

	/* XXX: This is ugly */
	type = (d_inode(old_dentry)->i_mode & S_IFMT) >> 12;
	अगर (!type) type = DT_REG;

	now = JFFS2_NOW();
	ret = jffs2_करो_link(c, dir_f, f->inocache->ino, type, dentry->d_name.name, dentry->d_name.len, now);

	अगर (!ret) अणु
		mutex_lock(&f->sem);
		set_nlink(d_inode(old_dentry), ++f->inocache->pino_nlink);
		mutex_unlock(&f->sem);
		d_instantiate(dentry, d_inode(old_dentry));
		dir_i->i_mसमय = dir_i->i_स_समय = ITIME(now);
		ihold(d_inode(old_dentry));
	पूर्ण
	वापस ret;
पूर्ण

/***********************************************************************/

अटल पूर्णांक jffs2_symlink (काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir_i,
			  काष्ठा dentry *dentry, स्थिर अक्षर *target)
अणु
	काष्ठा jffs2_inode_info *f, *dir_f;
	काष्ठा jffs2_sb_info *c;
	काष्ठा inode *inode;
	काष्ठा jffs2_raw_inode *ri;
	काष्ठा jffs2_raw_dirent *rd;
	काष्ठा jffs2_full_dnode *fn;
	काष्ठा jffs2_full_dirent *fd;
	पूर्णांक namelen;
	uपूर्णांक32_t alloclen;
	पूर्णांक ret, targetlen = म_माप(target);

	/* FIXME: If you care. We'd need to use frags क्रम the target
	   अगर it grows much more than this */
	अगर (targetlen > 254)
		वापस -ENAMETOOLONG;

	ri = jffs2_alloc_raw_inode();

	अगर (!ri)
		वापस -ENOMEM;

	c = JFFS2_SB_INFO(dir_i->i_sb);

	/* Try to reserve enough space क्रम both node and dirent.
	 * Just the node will करो क्रम now, though
	 */
	namelen = dentry->d_name.len;
	ret = jffs2_reserve_space(c, माप(*ri) + targetlen, &alloclen,
				  ALLOC_NORMAL, JFFS2_SUMMARY_INODE_SIZE);

	अगर (ret) अणु
		jffs2_मुक्त_raw_inode(ri);
		वापस ret;
	पूर्ण

	inode = jffs2_new_inode(dir_i, S_IFLNK | S_IRWXUGO, ri);

	अगर (IS_ERR(inode)) अणु
		jffs2_मुक्त_raw_inode(ri);
		jffs2_complete_reservation(c);
		वापस PTR_ERR(inode);
	पूर्ण

	inode->i_op = &jffs2_symlink_inode_operations;

	f = JFFS2_INODE_INFO(inode);

	inode->i_size = targetlen;
	ri->isize = ri->dsize = ri->csize = cpu_to_je32(inode->i_size);
	ri->totlen = cpu_to_je32(माप(*ri) + inode->i_size);
	ri->hdr_crc = cpu_to_je32(crc32(0, ri, माप(काष्ठा jffs2_unknown_node)-4));

	ri->compr = JFFS2_COMPR_NONE;
	ri->data_crc = cpu_to_je32(crc32(0, target, targetlen));
	ri->node_crc = cpu_to_je32(crc32(0, ri, माप(*ri)-8));

	fn = jffs2_ग_लिखो_dnode(c, f, ri, target, targetlen, ALLOC_NORMAL);

	jffs2_मुक्त_raw_inode(ri);

	अगर (IS_ERR(fn)) अणु
		/* Eeek. Wave bye bye */
		mutex_unlock(&f->sem);
		jffs2_complete_reservation(c);
		ret = PTR_ERR(fn);
		जाओ fail;
	पूर्ण

	/* We use f->target field to store the target path. */
	f->target = kmemdup(target, targetlen + 1, GFP_KERNEL);
	अगर (!f->target) अणु
		pr_warn("Can't allocate %d bytes of memory\n", targetlen + 1);
		mutex_unlock(&f->sem);
		jffs2_complete_reservation(c);
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण
	inode->i_link = f->target;

	jffs2_dbg(1, "%s(): symlink's target '%s' cached\n",
		  __func__, (अक्षर *)f->target);

	/* No data here. Only a metadata node, which will be
	   obsoleted by the first data ग_लिखो
	*/
	f->metadata = fn;
	mutex_unlock(&f->sem);

	jffs2_complete_reservation(c);

	ret = jffs2_init_security(inode, dir_i, &dentry->d_name);
	अगर (ret)
		जाओ fail;

	ret = jffs2_init_acl_post(inode);
	अगर (ret)
		जाओ fail;

	ret = jffs2_reserve_space(c, माप(*rd)+namelen, &alloclen,
				  ALLOC_NORMAL, JFFS2_SUMMARY_सूचीENT_SIZE(namelen));
	अगर (ret)
		जाओ fail;

	rd = jffs2_alloc_raw_dirent();
	अगर (!rd) अणु
		/* Argh. Now we treat it like a normal delete */
		jffs2_complete_reservation(c);
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	dir_f = JFFS2_INODE_INFO(dir_i);
	mutex_lock(&dir_f->sem);

	rd->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	rd->nodetype = cpu_to_je16(JFFS2_NODETYPE_सूचीENT);
	rd->totlen = cpu_to_je32(माप(*rd) + namelen);
	rd->hdr_crc = cpu_to_je32(crc32(0, rd, माप(काष्ठा jffs2_unknown_node)-4));

	rd->pino = cpu_to_je32(dir_i->i_ino);
	rd->version = cpu_to_je32(++dir_f->highest_version);
	rd->ino = cpu_to_je32(inode->i_ino);
	rd->mस_समय = cpu_to_je32(JFFS2_NOW());
	rd->nsize = namelen;
	rd->type = DT_LNK;
	rd->node_crc = cpu_to_je32(crc32(0, rd, माप(*rd)-8));
	rd->name_crc = cpu_to_je32(crc32(0, dentry->d_name.name, namelen));

	fd = jffs2_ग_लिखो_dirent(c, dir_f, rd, dentry->d_name.name, namelen, ALLOC_NORMAL);

	अगर (IS_ERR(fd)) अणु
		/* dirent failed to ग_लिखो. Delete the inode normally
		   as अगर it were the final unlink() */
		jffs2_complete_reservation(c);
		jffs2_मुक्त_raw_dirent(rd);
		mutex_unlock(&dir_f->sem);
		ret = PTR_ERR(fd);
		जाओ fail;
	पूर्ण

	dir_i->i_mसमय = dir_i->i_स_समय = ITIME(je32_to_cpu(rd->mस_समय));

	jffs2_मुक्त_raw_dirent(rd);

	/* Link the fd पूर्णांकo the inode's list, obsoleting an old
	   one अगर necessary. */
	jffs2_add_fd_to_list(c, fd, &dir_f->dents);

	mutex_unlock(&dir_f->sem);
	jffs2_complete_reservation(c);

	d_instantiate_new(dentry, inode);
	वापस 0;

 fail:
	iget_failed(inode);
	वापस ret;
पूर्ण


अटल पूर्णांक jffs2_सूची_गढ़ो (काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir_i,
		        काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा jffs2_inode_info *f, *dir_f;
	काष्ठा jffs2_sb_info *c;
	काष्ठा inode *inode;
	काष्ठा jffs2_raw_inode *ri;
	काष्ठा jffs2_raw_dirent *rd;
	काष्ठा jffs2_full_dnode *fn;
	काष्ठा jffs2_full_dirent *fd;
	पूर्णांक namelen;
	uपूर्णांक32_t alloclen;
	पूर्णांक ret;

	mode |= S_IFसूची;

	ri = jffs2_alloc_raw_inode();
	अगर (!ri)
		वापस -ENOMEM;

	c = JFFS2_SB_INFO(dir_i->i_sb);

	/* Try to reserve enough space क्रम both node and dirent.
	 * Just the node will करो क्रम now, though
	 */
	namelen = dentry->d_name.len;
	ret = jffs2_reserve_space(c, माप(*ri), &alloclen, ALLOC_NORMAL,
				  JFFS2_SUMMARY_INODE_SIZE);

	अगर (ret) अणु
		jffs2_मुक्त_raw_inode(ri);
		वापस ret;
	पूर्ण

	inode = jffs2_new_inode(dir_i, mode, ri);

	अगर (IS_ERR(inode)) अणु
		jffs2_मुक्त_raw_inode(ri);
		jffs2_complete_reservation(c);
		वापस PTR_ERR(inode);
	पूर्ण

	inode->i_op = &jffs2_dir_inode_operations;
	inode->i_fop = &jffs2_dir_operations;

	f = JFFS2_INODE_INFO(inode);

	/* Directories get nlink 2 at start */
	set_nlink(inode, 2);
	/* but ic->pino_nlink is the parent ino# */
	f->inocache->pino_nlink = dir_i->i_ino;

	ri->data_crc = cpu_to_je32(0);
	ri->node_crc = cpu_to_je32(crc32(0, ri, माप(*ri)-8));

	fn = jffs2_ग_लिखो_dnode(c, f, ri, शून्य, 0, ALLOC_NORMAL);

	jffs2_मुक्त_raw_inode(ri);

	अगर (IS_ERR(fn)) अणु
		/* Eeek. Wave bye bye */
		mutex_unlock(&f->sem);
		jffs2_complete_reservation(c);
		ret = PTR_ERR(fn);
		जाओ fail;
	पूर्ण
	/* No data here. Only a metadata node, which will be
	   obsoleted by the first data ग_लिखो
	*/
	f->metadata = fn;
	mutex_unlock(&f->sem);

	jffs2_complete_reservation(c);

	ret = jffs2_init_security(inode, dir_i, &dentry->d_name);
	अगर (ret)
		जाओ fail;

	ret = jffs2_init_acl_post(inode);
	अगर (ret)
		जाओ fail;

	ret = jffs2_reserve_space(c, माप(*rd)+namelen, &alloclen,
				  ALLOC_NORMAL, JFFS2_SUMMARY_सूचीENT_SIZE(namelen));
	अगर (ret)
		जाओ fail;

	rd = jffs2_alloc_raw_dirent();
	अगर (!rd) अणु
		/* Argh. Now we treat it like a normal delete */
		jffs2_complete_reservation(c);
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	dir_f = JFFS2_INODE_INFO(dir_i);
	mutex_lock(&dir_f->sem);

	rd->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	rd->nodetype = cpu_to_je16(JFFS2_NODETYPE_सूचीENT);
	rd->totlen = cpu_to_je32(माप(*rd) + namelen);
	rd->hdr_crc = cpu_to_je32(crc32(0, rd, माप(काष्ठा jffs2_unknown_node)-4));

	rd->pino = cpu_to_je32(dir_i->i_ino);
	rd->version = cpu_to_je32(++dir_f->highest_version);
	rd->ino = cpu_to_je32(inode->i_ino);
	rd->mस_समय = cpu_to_je32(JFFS2_NOW());
	rd->nsize = namelen;
	rd->type = DT_सूची;
	rd->node_crc = cpu_to_je32(crc32(0, rd, माप(*rd)-8));
	rd->name_crc = cpu_to_je32(crc32(0, dentry->d_name.name, namelen));

	fd = jffs2_ग_लिखो_dirent(c, dir_f, rd, dentry->d_name.name, namelen, ALLOC_NORMAL);

	अगर (IS_ERR(fd)) अणु
		/* dirent failed to ग_लिखो. Delete the inode normally
		   as अगर it were the final unlink() */
		jffs2_complete_reservation(c);
		jffs2_मुक्त_raw_dirent(rd);
		mutex_unlock(&dir_f->sem);
		ret = PTR_ERR(fd);
		जाओ fail;
	पूर्ण

	dir_i->i_mसमय = dir_i->i_स_समय = ITIME(je32_to_cpu(rd->mस_समय));
	inc_nlink(dir_i);

	jffs2_मुक्त_raw_dirent(rd);

	/* Link the fd पूर्णांकo the inode's list, obsoleting an old
	   one अगर necessary. */
	jffs2_add_fd_to_list(c, fd, &dir_f->dents);

	mutex_unlock(&dir_f->sem);
	jffs2_complete_reservation(c);

	d_instantiate_new(dentry, inode);
	वापस 0;

 fail:
	iget_failed(inode);
	वापस ret;
पूर्ण

अटल पूर्णांक jffs2_सूची_हटाओ (काष्ठा inode *dir_i, काष्ठा dentry *dentry)
अणु
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(dir_i->i_sb);
	काष्ठा jffs2_inode_info *dir_f = JFFS2_INODE_INFO(dir_i);
	काष्ठा jffs2_inode_info *f = JFFS2_INODE_INFO(d_inode(dentry));
	काष्ठा jffs2_full_dirent *fd;
	पूर्णांक ret;
	uपूर्णांक32_t now = JFFS2_NOW();

	mutex_lock(&f->sem);
	क्रम (fd = f->dents ; fd; fd = fd->next) अणु
		अगर (fd->ino) अणु
			mutex_unlock(&f->sem);
			वापस -ENOTEMPTY;
		पूर्ण
	पूर्ण
	mutex_unlock(&f->sem);

	ret = jffs2_करो_unlink(c, dir_f, dentry->d_name.name,
			      dentry->d_name.len, f, now);
	अगर (!ret) अणु
		dir_i->i_mसमय = dir_i->i_स_समय = ITIME(now);
		clear_nlink(d_inode(dentry));
		drop_nlink(dir_i);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक jffs2_mknod (काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir_i,
		        काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	काष्ठा jffs2_inode_info *f, *dir_f;
	काष्ठा jffs2_sb_info *c;
	काष्ठा inode *inode;
	काष्ठा jffs2_raw_inode *ri;
	काष्ठा jffs2_raw_dirent *rd;
	काष्ठा jffs2_full_dnode *fn;
	काष्ठा jffs2_full_dirent *fd;
	पूर्णांक namelen;
	जोड़ jffs2_device_node dev;
	पूर्णांक devlen = 0;
	uपूर्णांक32_t alloclen;
	पूर्णांक ret;

	ri = jffs2_alloc_raw_inode();
	अगर (!ri)
		वापस -ENOMEM;

	c = JFFS2_SB_INFO(dir_i->i_sb);

	अगर (S_ISBLK(mode) || S_ISCHR(mode))
		devlen = jffs2_encode_dev(&dev, rdev);

	/* Try to reserve enough space क्रम both node and dirent.
	 * Just the node will करो क्रम now, though
	 */
	namelen = dentry->d_name.len;
	ret = jffs2_reserve_space(c, माप(*ri) + devlen, &alloclen,
				  ALLOC_NORMAL, JFFS2_SUMMARY_INODE_SIZE);

	अगर (ret) अणु
		jffs2_मुक्त_raw_inode(ri);
		वापस ret;
	पूर्ण

	inode = jffs2_new_inode(dir_i, mode, ri);

	अगर (IS_ERR(inode)) अणु
		jffs2_मुक्त_raw_inode(ri);
		jffs2_complete_reservation(c);
		वापस PTR_ERR(inode);
	पूर्ण
	inode->i_op = &jffs2_file_inode_operations;
	init_special_inode(inode, inode->i_mode, rdev);

	f = JFFS2_INODE_INFO(inode);

	ri->dsize = ri->csize = cpu_to_je32(devlen);
	ri->totlen = cpu_to_je32(माप(*ri) + devlen);
	ri->hdr_crc = cpu_to_je32(crc32(0, ri, माप(काष्ठा jffs2_unknown_node)-4));

	ri->compr = JFFS2_COMPR_NONE;
	ri->data_crc = cpu_to_je32(crc32(0, &dev, devlen));
	ri->node_crc = cpu_to_je32(crc32(0, ri, माप(*ri)-8));

	fn = jffs2_ग_लिखो_dnode(c, f, ri, (अक्षर *)&dev, devlen, ALLOC_NORMAL);

	jffs2_मुक्त_raw_inode(ri);

	अगर (IS_ERR(fn)) अणु
		/* Eeek. Wave bye bye */
		mutex_unlock(&f->sem);
		jffs2_complete_reservation(c);
		ret = PTR_ERR(fn);
		जाओ fail;
	पूर्ण
	/* No data here. Only a metadata node, which will be
	   obsoleted by the first data ग_लिखो
	*/
	f->metadata = fn;
	mutex_unlock(&f->sem);

	jffs2_complete_reservation(c);

	ret = jffs2_init_security(inode, dir_i, &dentry->d_name);
	अगर (ret)
		जाओ fail;

	ret = jffs2_init_acl_post(inode);
	अगर (ret)
		जाओ fail;

	ret = jffs2_reserve_space(c, माप(*rd)+namelen, &alloclen,
				  ALLOC_NORMAL, JFFS2_SUMMARY_सूचीENT_SIZE(namelen));
	अगर (ret)
		जाओ fail;

	rd = jffs2_alloc_raw_dirent();
	अगर (!rd) अणु
		/* Argh. Now we treat it like a normal delete */
		jffs2_complete_reservation(c);
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	dir_f = JFFS2_INODE_INFO(dir_i);
	mutex_lock(&dir_f->sem);

	rd->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	rd->nodetype = cpu_to_je16(JFFS2_NODETYPE_सूचीENT);
	rd->totlen = cpu_to_je32(माप(*rd) + namelen);
	rd->hdr_crc = cpu_to_je32(crc32(0, rd, माप(काष्ठा jffs2_unknown_node)-4));

	rd->pino = cpu_to_je32(dir_i->i_ino);
	rd->version = cpu_to_je32(++dir_f->highest_version);
	rd->ino = cpu_to_je32(inode->i_ino);
	rd->mस_समय = cpu_to_je32(JFFS2_NOW());
	rd->nsize = namelen;

	/* XXX: This is ugly. */
	rd->type = (mode & S_IFMT) >> 12;

	rd->node_crc = cpu_to_je32(crc32(0, rd, माप(*rd)-8));
	rd->name_crc = cpu_to_je32(crc32(0, dentry->d_name.name, namelen));

	fd = jffs2_ग_लिखो_dirent(c, dir_f, rd, dentry->d_name.name, namelen, ALLOC_NORMAL);

	अगर (IS_ERR(fd)) अणु
		/* dirent failed to ग_लिखो. Delete the inode normally
		   as अगर it were the final unlink() */
		jffs2_complete_reservation(c);
		jffs2_मुक्त_raw_dirent(rd);
		mutex_unlock(&dir_f->sem);
		ret = PTR_ERR(fd);
		जाओ fail;
	पूर्ण

	dir_i->i_mसमय = dir_i->i_स_समय = ITIME(je32_to_cpu(rd->mस_समय));

	jffs2_मुक्त_raw_dirent(rd);

	/* Link the fd पूर्णांकo the inode's list, obsoleting an old
	   one अगर necessary. */
	jffs2_add_fd_to_list(c, fd, &dir_f->dents);

	mutex_unlock(&dir_f->sem);
	jffs2_complete_reservation(c);

	d_instantiate_new(dentry, inode);
	वापस 0;

 fail:
	iget_failed(inode);
	वापस ret;
पूर्ण

अटल पूर्णांक jffs2_नाम (काष्ठा user_namespace *mnt_userns,
			 काष्ठा inode *old_dir_i, काष्ठा dentry *old_dentry,
			 काष्ठा inode *new_dir_i, काष्ठा dentry *new_dentry,
			 अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक ret;
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(old_dir_i->i_sb);
	काष्ठा jffs2_inode_info *victim_f = शून्य;
	uपूर्णांक8_t type;
	uपूर्णांक32_t now;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	/* The VFS will check क्रम us and prevent trying to नाम a
	 * file over a directory and vice versa, but अगर it's a directory,
	 * the VFS can't check whether the victim is empty. The fileप्रणाली
	 * needs to करो that क्रम itself.
	 */
	अगर (d_really_is_positive(new_dentry)) अणु
		victim_f = JFFS2_INODE_INFO(d_inode(new_dentry));
		अगर (d_is_dir(new_dentry)) अणु
			काष्ठा jffs2_full_dirent *fd;

			mutex_lock(&victim_f->sem);
			क्रम (fd = victim_f->dents; fd; fd = fd->next) अणु
				अगर (fd->ino) अणु
					mutex_unlock(&victim_f->sem);
					वापस -ENOTEMPTY;
				पूर्ण
			पूर्ण
			mutex_unlock(&victim_f->sem);
		पूर्ण
	पूर्ण

	/* XXX: We probably ought to alloc enough space क्रम
	   both nodes at the same समय. Writing the new link,
	   then getting -ENOSPC, is quite bad :)
	*/

	/* Make a hard link */

	/* XXX: This is ugly */
	type = (d_inode(old_dentry)->i_mode & S_IFMT) >> 12;
	अगर (!type) type = DT_REG;

	now = JFFS2_NOW();
	ret = jffs2_करो_link(c, JFFS2_INODE_INFO(new_dir_i),
			    d_inode(old_dentry)->i_ino, type,
			    new_dentry->d_name.name, new_dentry->d_name.len, now);

	अगर (ret)
		वापस ret;

	अगर (victim_f) अणु
		/* There was a victim. Kill it off nicely */
		अगर (d_is_dir(new_dentry))
			clear_nlink(d_inode(new_dentry));
		अन्यथा
			drop_nlink(d_inode(new_dentry));
		/* Don't oops अगर the victim was a dirent poपूर्णांकing to an
		   inode which didn't exist. */
		अगर (victim_f->inocache) अणु
			mutex_lock(&victim_f->sem);
			अगर (d_is_dir(new_dentry))
				victim_f->inocache->pino_nlink = 0;
			अन्यथा
				victim_f->inocache->pino_nlink--;
			mutex_unlock(&victim_f->sem);
		पूर्ण
	पूर्ण

	/* If it was a directory we moved, and there was no victim,
	   increase i_nlink on its new parent */
	अगर (d_is_dir(old_dentry) && !victim_f)
		inc_nlink(new_dir_i);

	/* Unlink the original */
	ret = jffs2_करो_unlink(c, JFFS2_INODE_INFO(old_dir_i),
			      old_dentry->d_name.name, old_dentry->d_name.len, शून्य, now);

	/* We करोn't touch inode->i_nlink */

	अगर (ret) अणु
		/* Oh shit. We really ought to make a single node which can करो both atomically */
		काष्ठा jffs2_inode_info *f = JFFS2_INODE_INFO(d_inode(old_dentry));
		mutex_lock(&f->sem);
		inc_nlink(d_inode(old_dentry));
		अगर (f->inocache && !d_is_dir(old_dentry))
			f->inocache->pino_nlink++;
		mutex_unlock(&f->sem);

		pr_notice("%s(): Link succeeded, unlink failed (err %d). You now have a hard link\n",
			  __func__, ret);
		/*
		 * We can't keep the target in dcache after that.
		 * For one thing, we can't afक्रमd dentry aliases क्रम directories.
		 * For another, अगर there was a victim, we _can't_ set new inode
		 * क्रम that sucker and we have to trigger mount eviction - the
		 * caller won't करो it on its own since we are वापसing an error.
		 */
		d_invalidate(new_dentry);
		new_dir_i->i_mसमय = new_dir_i->i_स_समय = ITIME(now);
		वापस ret;
	पूर्ण

	अगर (d_is_dir(old_dentry))
		drop_nlink(old_dir_i);

	new_dir_i->i_mसमय = new_dir_i->i_स_समय = old_dir_i->i_mसमय = old_dir_i->i_स_समय = ITIME(now);

	वापस 0;
पूर्ण

