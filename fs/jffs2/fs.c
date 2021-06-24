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

#समावेश <linux/capability.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/cred.h>
#समावेश <linux/fs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/list.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/vfs.h>
#समावेश <linux/crc32.h>
#समावेश "nodelist.h"

अटल पूर्णांक jffs2_flash_setup(काष्ठा jffs2_sb_info *c);

पूर्णांक jffs2_करो_setattr (काष्ठा inode *inode, काष्ठा iattr *iattr)
अणु
	काष्ठा jffs2_full_dnode *old_metadata, *new_metadata;
	काष्ठा jffs2_inode_info *f = JFFS2_INODE_INFO(inode);
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	काष्ठा jffs2_raw_inode *ri;
	जोड़ jffs2_device_node dev;
	अचिन्हित अक्षर *mdata = शून्य;
	पूर्णांक mdatalen = 0;
	अचिन्हित पूर्णांक ivalid;
	uपूर्णांक32_t alloclen;
	पूर्णांक ret;
	पूर्णांक alloc_type = ALLOC_NORMAL;

	jffs2_dbg(1, "%s(): ino #%lu\n", __func__, inode->i_ino);

	/* Special हालs - we करोn't want more than one data node
	   क्रम these types on the medium at any समय. So setattr
	   must पढ़ो the original data associated with the node
	   (i.e. the device numbers or the target name) and ग_लिखो
	   it out again with the appropriate data attached */
	अगर (S_ISBLK(inode->i_mode) || S_ISCHR(inode->i_mode)) अणु
		/* For these, we करोn't actually need to पढ़ो the old node */
		mdatalen = jffs2_encode_dev(&dev, inode->i_rdev);
		mdata = (अक्षर *)&dev;
		jffs2_dbg(1, "%s(): Writing %d bytes of kdev_t\n",
			  __func__, mdatalen);
	पूर्ण अन्यथा अगर (S_ISLNK(inode->i_mode)) अणु
		mutex_lock(&f->sem);
		mdatalen = f->metadata->size;
		mdata = kदो_स्मृति(f->metadata->size, GFP_USER);
		अगर (!mdata) अणु
			mutex_unlock(&f->sem);
			वापस -ENOMEM;
		पूर्ण
		ret = jffs2_पढ़ो_dnode(c, f, f->metadata, mdata, 0, mdatalen);
		अगर (ret) अणु
			mutex_unlock(&f->sem);
			kमुक्त(mdata);
			वापस ret;
		पूर्ण
		mutex_unlock(&f->sem);
		jffs2_dbg(1, "%s(): Writing %d bytes of symlink target\n",
			  __func__, mdatalen);
	पूर्ण

	ri = jffs2_alloc_raw_inode();
	अगर (!ri) अणु
		अगर (S_ISLNK(inode->i_mode))
			kमुक्त(mdata);
		वापस -ENOMEM;
	पूर्ण

	ret = jffs2_reserve_space(c, माप(*ri) + mdatalen, &alloclen,
				  ALLOC_NORMAL, JFFS2_SUMMARY_INODE_SIZE);
	अगर (ret) अणु
		jffs2_मुक्त_raw_inode(ri);
		अगर (S_ISLNK(inode->i_mode))
			 kमुक्त(mdata);
		वापस ret;
	पूर्ण
	mutex_lock(&f->sem);
	ivalid = iattr->ia_valid;

	ri->magic = cpu_to_je16(JFFS2_MAGIC_BITMASK);
	ri->nodetype = cpu_to_je16(JFFS2_NODETYPE_INODE);
	ri->totlen = cpu_to_je32(माप(*ri) + mdatalen);
	ri->hdr_crc = cpu_to_je32(crc32(0, ri, माप(काष्ठा jffs2_unknown_node)-4));

	ri->ino = cpu_to_je32(inode->i_ino);
	ri->version = cpu_to_je32(++f->highest_version);

	ri->uid = cpu_to_je16((ivalid & ATTR_UID)?
		from_kuid(&init_user_ns, iattr->ia_uid):i_uid_पढ़ो(inode));
	ri->gid = cpu_to_je16((ivalid & ATTR_GID)?
		from_kgid(&init_user_ns, iattr->ia_gid):i_gid_पढ़ो(inode));

	अगर (ivalid & ATTR_MODE)
		ri->mode = cpu_to_jemode(iattr->ia_mode);
	अन्यथा
		ri->mode = cpu_to_jemode(inode->i_mode);


	ri->isize = cpu_to_je32((ivalid & ATTR_SIZE)?iattr->ia_size:inode->i_size);
	ri->aसमय = cpu_to_je32(I_SEC((ivalid & ATTR_ATIME)?iattr->ia_aसमय:inode->i_aसमय));
	ri->mसमय = cpu_to_je32(I_SEC((ivalid & ATTR_MTIME)?iattr->ia_mसमय:inode->i_mसमय));
	ri->स_समय = cpu_to_je32(I_SEC((ivalid & ATTR_CTIME)?iattr->ia_स_समय:inode->i_स_समय));

	ri->offset = cpu_to_je32(0);
	ri->csize = ri->dsize = cpu_to_je32(mdatalen);
	ri->compr = JFFS2_COMPR_NONE;
	अगर (ivalid & ATTR_SIZE && inode->i_size < iattr->ia_size) अणु
		/* It's an extension. Make it a hole node */
		ri->compr = JFFS2_COMPR_ZERO;
		ri->dsize = cpu_to_je32(iattr->ia_size - inode->i_size);
		ri->offset = cpu_to_je32(inode->i_size);
	पूर्ण अन्यथा अगर (ivalid & ATTR_SIZE && !iattr->ia_size) अणु
		/* For truncate-to-zero, treat it as deletion because
		   it'll always be obsoleting all previous nodes */
		alloc_type = ALLOC_DELETION;
	पूर्ण
	ri->node_crc = cpu_to_je32(crc32(0, ri, माप(*ri)-8));
	अगर (mdatalen)
		ri->data_crc = cpu_to_je32(crc32(0, mdata, mdatalen));
	अन्यथा
		ri->data_crc = cpu_to_je32(0);

	new_metadata = jffs2_ग_लिखो_dnode(c, f, ri, mdata, mdatalen, alloc_type);
	अगर (S_ISLNK(inode->i_mode))
		kमुक्त(mdata);

	अगर (IS_ERR(new_metadata)) अणु
		jffs2_complete_reservation(c);
		jffs2_मुक्त_raw_inode(ri);
		mutex_unlock(&f->sem);
		वापस PTR_ERR(new_metadata);
	पूर्ण
	/* It worked. Update the inode */
	inode->i_aसमय = ITIME(je32_to_cpu(ri->aसमय));
	inode->i_स_समय = ITIME(je32_to_cpu(ri->स_समय));
	inode->i_mसमय = ITIME(je32_to_cpu(ri->mसमय));
	inode->i_mode = jemode_to_cpu(ri->mode);
	i_uid_ग_लिखो(inode, je16_to_cpu(ri->uid));
	i_gid_ग_लिखो(inode, je16_to_cpu(ri->gid));


	old_metadata = f->metadata;

	अगर (ivalid & ATTR_SIZE && inode->i_size > iattr->ia_size)
		jffs2_truncate_fragtree (c, &f->fragtree, iattr->ia_size);

	अगर (ivalid & ATTR_SIZE && inode->i_size < iattr->ia_size) अणु
		jffs2_add_full_dnode_to_inode(c, f, new_metadata);
		inode->i_size = iattr->ia_size;
		inode->i_blocks = (inode->i_size + 511) >> 9;
		f->metadata = शून्य;
	पूर्ण अन्यथा अणु
		f->metadata = new_metadata;
	पूर्ण
	अगर (old_metadata) अणु
		jffs2_mark_node_obsolete(c, old_metadata->raw);
		jffs2_मुक्त_full_dnode(old_metadata);
	पूर्ण
	jffs2_मुक्त_raw_inode(ri);

	mutex_unlock(&f->sem);
	jffs2_complete_reservation(c);

	/* We have to करो the truncate_setsize() without f->sem held, since
	   some pages may be locked and रुकोing क्रम it in पढ़ोpage().
	   We are रक्षित from a simultaneous ग_लिखो() extending i_size
	   back past iattr->ia_size, because करो_truncate() holds the
	   generic inode semaphore. */
	अगर (ivalid & ATTR_SIZE && inode->i_size > iattr->ia_size) अणु
		truncate_setsize(inode, iattr->ia_size);
		inode->i_blocks = (inode->i_size + 511) >> 9;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक jffs2_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		  काष्ठा iattr *iattr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक rc;

	rc = setattr_prepare(&init_user_ns, dentry, iattr);
	अगर (rc)
		वापस rc;

	rc = jffs2_करो_setattr(inode, iattr);
	अगर (!rc && (iattr->ia_valid & ATTR_MODE))
		rc = posix_acl_chmod(&init_user_ns, inode, inode->i_mode);

	वापस rc;
पूर्ण

पूर्णांक jffs2_statfs(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(dentry->d_sb);
	अचिन्हित दीर्घ avail;

	buf->f_type = JFFS2_SUPER_MAGIC;
	buf->f_bsize = 1 << PAGE_SHIFT;
	buf->f_blocks = c->flash_size >> PAGE_SHIFT;
	buf->f_files = 0;
	buf->f_fमुक्त = 0;
	buf->f_namelen = JFFS2_MAX_NAME_LEN;
	buf->f_fsid.val[0] = JFFS2_SUPER_MAGIC;
	buf->f_fsid.val[1] = c->mtd->index;

	spin_lock(&c->erase_completion_lock);
	avail = c->dirty_size + c->मुक्त_size;
	अगर (avail > c->sector_size * c->resv_blocks_ग_लिखो)
		avail -= c->sector_size * c->resv_blocks_ग_लिखो;
	अन्यथा
		avail = 0;
	spin_unlock(&c->erase_completion_lock);

	buf->f_bavail = buf->f_bमुक्त = avail >> PAGE_SHIFT;

	वापस 0;
पूर्ण


व्योम jffs2_evict_inode (काष्ठा inode *inode)
अणु
	/* We can क्रमget about this inode क्रम now - drop all
	 *  the nodelists associated with it, etc.
	 */
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(inode->i_sb);
	काष्ठा jffs2_inode_info *f = JFFS2_INODE_INFO(inode);

	jffs2_dbg(1, "%s(): ino #%lu mode %o\n",
		  __func__, inode->i_ino, inode->i_mode);
	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	jffs2_करो_clear_inode(c, f);
पूर्ण

काष्ठा inode *jffs2_iget(काष्ठा super_block *sb, अचिन्हित दीर्घ ino)
अणु
	काष्ठा jffs2_inode_info *f;
	काष्ठा jffs2_sb_info *c;
	काष्ठा jffs2_raw_inode latest_node;
	जोड़ jffs2_device_node jdev;
	काष्ठा inode *inode;
	dev_t rdev = 0;
	पूर्णांक ret;

	jffs2_dbg(1, "%s(): ino == %lu\n", __func__, ino);

	inode = iget_locked(sb, ino);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);
	अगर (!(inode->i_state & I_NEW))
		वापस inode;

	f = JFFS2_INODE_INFO(inode);
	c = JFFS2_SB_INFO(inode->i_sb);

	jffs2_init_inode_info(f);
	mutex_lock(&f->sem);

	ret = jffs2_करो_पढ़ो_inode(c, f, inode->i_ino, &latest_node);
	अगर (ret)
		जाओ error;

	inode->i_mode = jemode_to_cpu(latest_node.mode);
	i_uid_ग_लिखो(inode, je16_to_cpu(latest_node.uid));
	i_gid_ग_लिखो(inode, je16_to_cpu(latest_node.gid));
	inode->i_size = je32_to_cpu(latest_node.isize);
	inode->i_aसमय = ITIME(je32_to_cpu(latest_node.aसमय));
	inode->i_mसमय = ITIME(je32_to_cpu(latest_node.mसमय));
	inode->i_स_समय = ITIME(je32_to_cpu(latest_node.स_समय));

	set_nlink(inode, f->inocache->pino_nlink);

	inode->i_blocks = (inode->i_size + 511) >> 9;

	चयन (inode->i_mode & S_IFMT) अणु

	हाल S_IFLNK:
		inode->i_op = &jffs2_symlink_inode_operations;
		inode->i_link = f->target;
		अवरोध;

	हाल S_IFसूची:
	अणु
		काष्ठा jffs2_full_dirent *fd;
		set_nlink(inode, 2); /* parent and '.' */

		क्रम (fd=f->dents; fd; fd = fd->next) अणु
			अगर (fd->type == DT_सूची && fd->ino)
				inc_nlink(inode);
		पूर्ण
		/* Root dir माला_लो i_nlink 3 क्रम some reason */
		अगर (inode->i_ino == 1)
			inc_nlink(inode);

		inode->i_op = &jffs2_dir_inode_operations;
		inode->i_fop = &jffs2_dir_operations;
		अवरोध;
	पूर्ण
	हाल S_IFREG:
		inode->i_op = &jffs2_file_inode_operations;
		inode->i_fop = &jffs2_file_operations;
		inode->i_mapping->a_ops = &jffs2_file_address_operations;
		inode->i_mapping->nrpages = 0;
		अवरोध;

	हाल S_IFBLK:
	हाल S_IFCHR:
		/* Read the device numbers from the media */
		अगर (f->metadata->size != माप(jdev.old_id) &&
		    f->metadata->size != माप(jdev.new_id)) अणु
			pr_notice("Device node has strange size %d\n",
				  f->metadata->size);
			जाओ error_io;
		पूर्ण
		jffs2_dbg(1, "Reading device numbers from flash\n");
		ret = jffs2_पढ़ो_dnode(c, f, f->metadata, (अक्षर *)&jdev, 0, f->metadata->size);
		अगर (ret < 0) अणु
			/* Eep */
			pr_notice("Read device numbers for inode %lu failed\n",
				  (अचिन्हित दीर्घ)inode->i_ino);
			जाओ error;
		पूर्ण
		अगर (f->metadata->size == माप(jdev.old_id))
			rdev = old_decode_dev(je16_to_cpu(jdev.old_id));
		अन्यथा
			rdev = new_decode_dev(je32_to_cpu(jdev.new_id));
		fallthrough;

	हाल S_IFSOCK:
	हाल S_IFIFO:
		inode->i_op = &jffs2_file_inode_operations;
		init_special_inode(inode, inode->i_mode, rdev);
		अवरोध;

	शेष:
		pr_warn("%s(): Bogus i_mode %o for ino %lu\n",
			__func__, inode->i_mode, (अचिन्हित दीर्घ)inode->i_ino);
	पूर्ण

	mutex_unlock(&f->sem);

	jffs2_dbg(1, "jffs2_read_inode() returning\n");
	unlock_new_inode(inode);
	वापस inode;

error_io:
	ret = -EIO;
error:
	mutex_unlock(&f->sem);
	iget_failed(inode);
	वापस ERR_PTR(ret);
पूर्ण

व्योम jffs2_dirty_inode(काष्ठा inode *inode, पूर्णांक flags)
अणु
	काष्ठा iattr iattr;

	अगर (!(inode->i_state & I_सूचीTY_DATASYNC)) अणु
		jffs2_dbg(2, "%s(): not calling setattr() for ino #%lu\n",
			  __func__, inode->i_ino);
		वापस;
	पूर्ण

	jffs2_dbg(1, "%s(): calling setattr() for ino #%lu\n",
		  __func__, inode->i_ino);

	iattr.ia_valid = ATTR_MODE|ATTR_UID|ATTR_GID|ATTR_ATIME|ATTR_MTIME|ATTR_CTIME;
	iattr.ia_mode = inode->i_mode;
	iattr.ia_uid = inode->i_uid;
	iattr.ia_gid = inode->i_gid;
	iattr.ia_aसमय = inode->i_aसमय;
	iattr.ia_mसमय = inode->i_mसमय;
	iattr.ia_स_समय = inode->i_स_समय;

	jffs2_करो_setattr(inode, &iattr);
पूर्ण

पूर्णांक jffs2_करो_remount_fs(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा jffs2_sb_info *c = JFFS2_SB_INFO(sb);

	अगर (c->flags & JFFS2_SB_FLAG_RO && !sb_rकरोnly(sb))
		वापस -EROFS;

	/* We stop अगर it was running, then restart अगर it needs to.
	   This also catches the हाल where it was stopped and this
	   is just a remount to restart it.
	   Flush the ग_लिखोbuffer, अगर neccecary, अन्यथा we loose it */
	अगर (!sb_rकरोnly(sb)) अणु
		jffs2_stop_garbage_collect_thपढ़ो(c);
		mutex_lock(&c->alloc_sem);
		jffs2_flush_wbuf_pad(c);
		mutex_unlock(&c->alloc_sem);
	पूर्ण

	अगर (!(fc->sb_flags & SB_RDONLY))
		jffs2_start_garbage_collect_thपढ़ो(c);

	fc->sb_flags |= SB_NOATIME;
	वापस 0;
पूर्ण

/* jffs2_new_inode: allocate a new inode and inocache, add it to the hash,
   fill in the raw_inode जबतक you're at it. */
काष्ठा inode *jffs2_new_inode (काष्ठा inode *dir_i, umode_t mode, काष्ठा jffs2_raw_inode *ri)
अणु
	काष्ठा inode *inode;
	काष्ठा super_block *sb = dir_i->i_sb;
	काष्ठा jffs2_sb_info *c;
	काष्ठा jffs2_inode_info *f;
	पूर्णांक ret;

	jffs2_dbg(1, "%s(): dir_i %ld, mode 0x%x\n",
		  __func__, dir_i->i_ino, mode);

	c = JFFS2_SB_INFO(sb);

	inode = new_inode(sb);

	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	f = JFFS2_INODE_INFO(inode);
	jffs2_init_inode_info(f);
	mutex_lock(&f->sem);

	स_रखो(ri, 0, माप(*ri));
	/* Set OS-specअगरic शेषs क्रम new inodes */
	ri->uid = cpu_to_je16(from_kuid(&init_user_ns, current_fsuid()));

	अगर (dir_i->i_mode & S_ISGID) अणु
		ri->gid = cpu_to_je16(i_gid_पढ़ो(dir_i));
		अगर (S_ISसूची(mode))
			mode |= S_ISGID;
	पूर्ण अन्यथा अणु
		ri->gid = cpu_to_je16(from_kgid(&init_user_ns, current_fsgid()));
	पूर्ण

	/* POSIX ACLs have to be processed now, at least partly.
	   The umask is only applied अगर there's no शेष ACL */
	ret = jffs2_init_acl_pre(dir_i, inode, &mode);
	अगर (ret) अणु
		mutex_unlock(&f->sem);
		make_bad_inode(inode);
		iput(inode);
		वापस ERR_PTR(ret);
	पूर्ण
	ret = jffs2_करो_new_inode (c, f, mode, ri);
	अगर (ret) अणु
		mutex_unlock(&f->sem);
		make_bad_inode(inode);
		iput(inode);
		वापस ERR_PTR(ret);
	पूर्ण
	set_nlink(inode, 1);
	inode->i_ino = je32_to_cpu(ri->ino);
	inode->i_mode = jemode_to_cpu(ri->mode);
	i_gid_ग_लिखो(inode, je16_to_cpu(ri->gid));
	i_uid_ग_लिखो(inode, je16_to_cpu(ri->uid));
	inode->i_aसमय = inode->i_स_समय = inode->i_mसमय = current_समय(inode);
	ri->aसमय = ri->mसमय = ri->स_समय = cpu_to_je32(I_SEC(inode->i_mसमय));

	inode->i_blocks = 0;
	inode->i_size = 0;

	अगर (insert_inode_locked(inode) < 0) अणु
		mutex_unlock(&f->sem);
		make_bad_inode(inode);
		iput(inode);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	वापस inode;
पूर्ण

अटल पूर्णांक calculate_inocache_hashsize(uपूर्णांक32_t flash_size)
अणु
	/*
	 * Pick a inocache hash size based on the size of the medium.
	 * Count how many megabytes we're dealing with, apply a hashsize twice
	 * that size, but rounding करोwn to the usual big घातers of 2. And keep
	 * to sensible bounds.
	 */

	पूर्णांक size_mb = flash_size / 1024 / 1024;
	पूर्णांक hashsize = (size_mb * 2) & ~0x3f;

	अगर (hashsize < INOCACHE_HASHSIZE_MIN)
		वापस INOCACHE_HASHSIZE_MIN;
	अगर (hashsize > INOCACHE_HASHSIZE_MAX)
		वापस INOCACHE_HASHSIZE_MAX;

	वापस hashsize;
पूर्ण

पूर्णांक jffs2_करो_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा jffs2_sb_info *c;
	काष्ठा inode *root_i;
	पूर्णांक ret;
	माप_प्रकार blocks;

	c = JFFS2_SB_INFO(sb);

	/* Do not support the MLC nand */
	अगर (c->mtd->type == MTD_MLCन_अंकDFLASH)
		वापस -EINVAL;

#अगर_अघोषित CONFIG_JFFS2_FS_WRITEBUFFER
	अगर (c->mtd->type == MTD_न_अंकDFLASH) अणु
		errorf(fc, "Cannot operate on NAND flash unless jffs2 NAND support is compiled in");
		वापस -EINVAL;
	पूर्ण
	अगर (c->mtd->type == MTD_DATAFLASH) अणु
		errorf(fc, "Cannot operate on DataFlash unless jffs2 DataFlash support is compiled in");
		वापस -EINVAL;
	पूर्ण
#पूर्ण_अगर

	c->flash_size = c->mtd->size;
	c->sector_size = c->mtd->erasesize;
	blocks = c->flash_size / c->sector_size;

	/*
	 * Size alignment check
	 */
	अगर ((c->sector_size * blocks) != c->flash_size) अणु
		c->flash_size = c->sector_size * blocks;
		infof(fc, "Flash size not aligned to erasesize, reducing to %dKiB",
		      c->flash_size / 1024);
	पूर्ण

	अगर (c->flash_size < 5*c->sector_size) अणु
		errorf(fc, "Too few erase blocks (%d)",
		       c->flash_size / c->sector_size);
		वापस -EINVAL;
	पूर्ण

	c->cleanmarker_size = माप(काष्ठा jffs2_unknown_node);

	/* न_अंकD (or other bizarre) flash... करो setup accordingly */
	ret = jffs2_flash_setup(c);
	अगर (ret)
		वापस ret;

	c->inocache_hashsize = calculate_inocache_hashsize(c->flash_size);
	c->inocache_list = kसुस्मृति(c->inocache_hashsize, माप(काष्ठा jffs2_inode_cache *), GFP_KERNEL);
	अगर (!c->inocache_list) अणु
		ret = -ENOMEM;
		जाओ out_wbuf;
	पूर्ण

	jffs2_init_xattr_subप्रणाली(c);

	अगर ((ret = jffs2_करो_mount_fs(c)))
		जाओ out_inohash;

	jffs2_dbg(1, "%s(): Getting root inode\n", __func__);
	root_i = jffs2_iget(sb, 1);
	अगर (IS_ERR(root_i)) अणु
		jffs2_dbg(1, "get root inode failed\n");
		ret = PTR_ERR(root_i);
		जाओ out_root;
	पूर्ण

	ret = -ENOMEM;

	jffs2_dbg(1, "%s(): d_make_root()\n", __func__);
	sb->s_root = d_make_root(root_i);
	अगर (!sb->s_root)
		जाओ out_root;

	sb->s_maxbytes = 0xFFFFFFFF;
	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = JFFS2_SUPER_MAGIC;
	sb->s_समय_min = 0;
	sb->s_समय_max = U32_MAX;

	अगर (!sb_rकरोnly(sb))
		jffs2_start_garbage_collect_thपढ़ो(c);
	वापस 0;

out_root:
	jffs2_मुक्त_ino_caches(c);
	jffs2_मुक्त_raw_node_refs(c);
	kvमुक्त(c->blocks);
 out_inohash:
	jffs2_clear_xattr_subप्रणाली(c);
	kमुक्त(c->inocache_list);
 out_wbuf:
	jffs2_flash_cleanup(c);

	वापस ret;
पूर्ण

व्योम jffs2_gc_release_inode(काष्ठा jffs2_sb_info *c,
				   काष्ठा jffs2_inode_info *f)
अणु
	iput(OFNI_EDONI_2SFFJ(f));
पूर्ण

काष्ठा jffs2_inode_info *jffs2_gc_fetch_inode(काष्ठा jffs2_sb_info *c,
					      पूर्णांक inum, पूर्णांक unlinked)
अणु
	काष्ठा inode *inode;
	काष्ठा jffs2_inode_cache *ic;

	अगर (unlinked) अणु
		/* The inode has zero nlink but its nodes weren't yet marked
		   obsolete. This has to be because we're still रुकोing क्रम
		   the final (बंद() and) iput() to happen.

		   There's a possibility that the final iput() could have
		   happened जबतक we were contemplating. In order to ensure
		   that we करोn't cause a new पढ़ो_inode() (which would fail)
		   क्रम the inode in question, we use ilookup() in this हाल
		   instead of iget().

		   The nlink can't _become_ zero at this point because we're
		   holding the alloc_sem, and jffs2_करो_unlink() would also
		   need that जबतक decrementing nlink on any inode.
		*/
		inode = ilookup(OFNI_BS_2SFFJ(c), inum);
		अगर (!inode) अणु
			jffs2_dbg(1, "ilookup() failed for ino #%u; inode is probably deleted.\n",
				  inum);

			spin_lock(&c->inocache_lock);
			ic = jffs2_get_ino_cache(c, inum);
			अगर (!ic) अणु
				jffs2_dbg(1, "Inode cache for ino #%u is gone\n",
					  inum);
				spin_unlock(&c->inocache_lock);
				वापस शून्य;
			पूर्ण
			अगर (ic->state != INO_STATE_CHECKEDABSENT) अणु
				/* Wait क्रम progress. Don't just loop */
				jffs2_dbg(1, "Waiting for ino #%u in state %d\n",
					  ic->ino, ic->state);
				sleep_on_spinunlock(&c->inocache_wq, &c->inocache_lock);
			पूर्ण अन्यथा अणु
				spin_unlock(&c->inocache_lock);
			पूर्ण

			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Inode has links to it still; they're not going away because
		   jffs2_करो_unlink() would need the alloc_sem and we have it.
		   Just iget() it, and अगर पढ़ो_inode() is necessary that's OK.
		*/
		inode = jffs2_iget(OFNI_BS_2SFFJ(c), inum);
		अगर (IS_ERR(inode))
			वापस ERR_CAST(inode);
	पूर्ण
	अगर (is_bad_inode(inode)) अणु
		pr_notice("Eep. read_inode() failed for ino #%u. unlinked %d\n",
			  inum, unlinked);
		/* NB. This will happen again. We need to करो something appropriate here. */
		iput(inode);
		वापस ERR_PTR(-EIO);
	पूर्ण

	वापस JFFS2_INODE_INFO(inode);
पूर्ण

अटल पूर्णांक jffs2_flash_setup(काष्ठा jffs2_sb_info *c) अणु
	पूर्णांक ret = 0;

	अगर (jffs2_cleanmarker_oob(c)) अणु
		/* न_अंकD flash... करो setup accordingly */
		ret = jffs2_nand_flash_setup(c);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* and Dataflash */
	अगर (jffs2_dataflash(c)) अणु
		ret = jffs2_dataflash_setup(c);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* and Intel "Sibley" flash */
	अगर (jffs2_nor_wbuf_flash(c)) अणु
		ret = jffs2_nor_wbuf_flash_setup(c);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* and an UBI volume */
	अगर (jffs2_ubivol(c)) अणु
		ret = jffs2_ubivol_setup(c);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

व्योम jffs2_flash_cleanup(काष्ठा jffs2_sb_info *c) अणु

	अगर (jffs2_cleanmarker_oob(c)) अणु
		jffs2_nand_flash_cleanup(c);
	पूर्ण

	/* and DataFlash */
	अगर (jffs2_dataflash(c)) अणु
		jffs2_dataflash_cleanup(c);
	पूर्ण

	/* and Intel "Sibley" flash */
	अगर (jffs2_nor_wbuf_flash(c)) अणु
		jffs2_nor_wbuf_flash_cleanup(c);
	पूर्ण

	/* and an UBI volume */
	अगर (jffs2_ubivol(c)) अणु
		jffs2_ubivol_cleanup(c);
	पूर्ण
पूर्ण
