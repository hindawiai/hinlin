<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * VirtualBox Guest Shared Folders support: Utility functions.
 * Mainly conversion from/to VirtualBox/Linux data काष्ठाures.
 *
 * Copyright (C) 2006-2018 Oracle Corporation
 */

#समावेश <linux/namei.h>
#समावेश <linux/nls.h>
#समावेश <linux/sizes.h>
#समावेश <linux/vfs.h>
#समावेश "vfsmod.h"

काष्ठा inode *vboxsf_new_inode(काष्ठा super_block *sb)
अणु
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(sb);
	काष्ठा inode *inode;
	अचिन्हित दीर्घ flags;
	पूर्णांक cursor, ret;
	u32 gen;

	inode = new_inode(sb);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	idr_preload(GFP_KERNEL);
	spin_lock_irqsave(&sbi->ino_idr_lock, flags);
	cursor = idr_get_cursor(&sbi->ino_idr);
	ret = idr_alloc_cyclic(&sbi->ino_idr, inode, 1, 0, GFP_ATOMIC);
	अगर (ret >= 0 && ret < cursor)
		sbi->next_generation++;
	gen = sbi->next_generation;
	spin_unlock_irqrestore(&sbi->ino_idr_lock, flags);
	idr_preload_end();

	अगर (ret < 0) अणु
		iput(inode);
		वापस ERR_PTR(ret);
	पूर्ण

	inode->i_ino = ret;
	inode->i_generation = gen;
	वापस inode;
पूर्ण

/* set [inode] attributes based on [info], uid/gid based on [sbi] */
पूर्णांक vboxsf_init_inode(काष्ठा vboxsf_sbi *sbi, काष्ठा inode *inode,
		       स्थिर काष्ठा shfl_fsobjinfo *info, bool reinit)
अणु
	स्थिर काष्ठा shfl_fsobjattr *attr;
	s64 allocated;
	umode_t mode;

	attr = &info->attr;

#घोषणा mode_set(r) ((attr->mode & (SHFL_UNIX_##r)) ? (S_##r) : 0)

	mode = mode_set(IRUSR);
	mode |= mode_set(IWUSR);
	mode |= mode_set(IXUSR);

	mode |= mode_set(IRGRP);
	mode |= mode_set(IWGRP);
	mode |= mode_set(IXGRP);

	mode |= mode_set(IROTH);
	mode |= mode_set(IWOTH);
	mode |= mode_set(IXOTH);

#अघोषित mode_set

	/* We use the host-side values क्रम these */
	inode->i_flags |= S_NOATIME | S_NOCMTIME;
	inode->i_mapping->a_ops = &vboxsf_reg_aops;

	अगर (SHFL_IS_सूचीECTORY(attr->mode)) अणु
		अगर (sbi->o.dmode_set)
			mode = sbi->o.dmode;
		mode &= ~sbi->o.dmask;
		mode |= S_IFसूची;
		अगर (!reinit) अणु
			inode->i_op = &vboxsf_dir_iops;
			inode->i_fop = &vboxsf_dir_fops;
			/*
			 * XXX: this probably should be set to the number of entries
			 * in the directory plus two (. ..)
			 */
			set_nlink(inode, 1);
		पूर्ण अन्यथा अगर (!S_ISसूची(inode->i_mode))
			वापस -ESTALE;
		inode->i_mode = mode;
	पूर्ण अन्यथा अगर (SHFL_IS_SYMLINK(attr->mode)) अणु
		अगर (sbi->o.भ_शेषe_set)
			mode = sbi->o.भ_शेषe;
		mode &= ~sbi->o.fmask;
		mode |= S_IFLNK;
		अगर (!reinit) अणु
			inode->i_op = &vboxsf_lnk_iops;
			set_nlink(inode, 1);
		पूर्ण अन्यथा अगर (!S_ISLNK(inode->i_mode))
			वापस -ESTALE;
		inode->i_mode = mode;
	पूर्ण अन्यथा अणु
		अगर (sbi->o.भ_शेषe_set)
			mode = sbi->o.भ_शेषe;
		mode &= ~sbi->o.fmask;
		mode |= S_IFREG;
		अगर (!reinit) अणु
			inode->i_op = &vboxsf_reg_iops;
			inode->i_fop = &vboxsf_reg_fops;
			set_nlink(inode, 1);
		पूर्ण अन्यथा अगर (!S_ISREG(inode->i_mode))
			वापस -ESTALE;
		inode->i_mode = mode;
	पूर्ण

	inode->i_uid = sbi->o.uid;
	inode->i_gid = sbi->o.gid;

	inode->i_size = info->size;
	inode->i_blkbits = 12;
	/* i_blocks always in units of 512 bytes! */
	allocated = info->allocated + 511;
	करो_भाग(allocated, 512);
	inode->i_blocks = allocated;

	inode->i_aसमय = ns_to_बारpec64(
				 info->access_समय.ns_relative_to_unix_epoch);
	inode->i_स_समय = ns_to_बारpec64(
				 info->change_समय.ns_relative_to_unix_epoch);
	inode->i_mसमय = ns_to_बारpec64(
			   info->modअगरication_समय.ns_relative_to_unix_epoch);
	वापस 0;
पूर्ण

पूर्णांक vboxsf_create_at_dentry(काष्ठा dentry *dentry,
			    काष्ठा shfl_createparms *params)
अणु
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(dentry->d_sb);
	काष्ठा shfl_string *path;
	पूर्णांक err;

	path = vboxsf_path_from_dentry(sbi, dentry);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);

	err = vboxsf_create(sbi->root, path, params);
	__putname(path);

	वापस err;
पूर्ण

पूर्णांक vboxsf_stat(काष्ठा vboxsf_sbi *sbi, काष्ठा shfl_string *path,
		काष्ठा shfl_fsobjinfo *info)
अणु
	काष्ठा shfl_createparms params = अणुपूर्ण;
	पूर्णांक err;

	params.handle = SHFL_HANDLE_NIL;
	params.create_flags = SHFL_CF_LOOKUP | SHFL_CF_ACT_FAIL_IF_NEW;

	err = vboxsf_create(sbi->root, path, &params);
	अगर (err)
		वापस err;

	अगर (params.result != SHFL_खाता_EXISTS)
		वापस -ENOENT;

	अगर (info)
		*info = params.info;

	वापस 0;
पूर्ण

पूर्णांक vboxsf_stat_dentry(काष्ठा dentry *dentry, काष्ठा shfl_fsobjinfo *info)
अणु
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(dentry->d_sb);
	काष्ठा shfl_string *path;
	पूर्णांक err;

	path = vboxsf_path_from_dentry(sbi, dentry);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);

	err = vboxsf_stat(sbi, path, info);
	__putname(path);
	वापस err;
पूर्ण

पूर्णांक vboxsf_inode_revalidate(काष्ठा dentry *dentry)
अणु
	काष्ठा vboxsf_sbi *sbi;
	काष्ठा vboxsf_inode *sf_i;
	काष्ठा shfl_fsobjinfo info;
	काष्ठा बारpec64 prev_mसमय;
	काष्ठा inode *inode;
	पूर्णांक err;

	अगर (!dentry || !d_really_is_positive(dentry))
		वापस -EINVAL;

	inode = d_inode(dentry);
	prev_mसमय = inode->i_mसमय;
	sf_i = VBOXSF_I(inode);
	sbi = VBOXSF_SBI(dentry->d_sb);
	अगर (!sf_i->क्रमce_restat) अणु
		अगर (समय_beक्रमe(jअगरfies, dentry->d_समय + sbi->o.ttl))
			वापस 0;
	पूर्ण

	err = vboxsf_stat_dentry(dentry, &info);
	अगर (err)
		वापस err;

	dentry->d_समय = jअगरfies;
	sf_i->क्रमce_restat = 0;
	err = vboxsf_init_inode(sbi, inode, &info, true);
	अगर (err)
		वापस err;

	/*
	 * If the file was changed on the host side we need to invalidate the
	 * page-cache क्रम it.  Note this also माला_लो triggered by our own ग_लिखोs,
	 * this is unaव्योमable.
	 */
	अगर (बारpec64_compare(&inode->i_mसमय, &prev_mसमय) > 0)
		invalidate_inode_pages2(inode->i_mapping);

	वापस 0;
पूर्ण

पूर्णांक vboxsf_getattr(काष्ठा user_namespace *mnt_userns, स्थिर काष्ठा path *path,
		   काष्ठा kstat *kstat, u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	पूर्णांक err;
	काष्ठा dentry *dentry = path->dentry;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा vboxsf_inode *sf_i = VBOXSF_I(inode);

	चयन (flags & AT_STATX_SYNC_TYPE) अणु
	हाल AT_STATX_DONT_SYNC:
		err = 0;
		अवरोध;
	हाल AT_STATX_FORCE_SYNC:
		sf_i->क्रमce_restat = 1;
		fallthrough;
	शेष:
		err = vboxsf_inode_revalidate(dentry);
	पूर्ण
	अगर (err)
		वापस err;

	generic_fillattr(&init_user_ns, d_inode(dentry), kstat);
	वापस 0;
पूर्ण

पूर्णांक vboxsf_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		   काष्ठा iattr *iattr)
अणु
	काष्ठा vboxsf_inode *sf_i = VBOXSF_I(d_inode(dentry));
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(dentry->d_sb);
	काष्ठा shfl_createparms params = अणुपूर्ण;
	काष्ठा shfl_fsobjinfo info = अणुपूर्ण;
	u32 buf_len;
	पूर्णांक err;

	params.handle = SHFL_HANDLE_NIL;
	params.create_flags = SHFL_CF_ACT_OPEN_IF_EXISTS |
			      SHFL_CF_ACT_FAIL_IF_NEW |
			      SHFL_CF_ACCESS_ATTR_WRITE;

	/* this is at least required क्रम Posix hosts */
	अगर (iattr->ia_valid & ATTR_SIZE)
		params.create_flags |= SHFL_CF_ACCESS_WRITE;

	err = vboxsf_create_at_dentry(dentry, &params);
	अगर (err || params.result != SHFL_खाता_EXISTS)
		वापस err ? err : -ENOENT;

#घोषणा mode_set(r) ((iattr->ia_mode & (S_##r)) ? SHFL_UNIX_##r : 0)

	/*
	 * Setting the file size and setting the other attributes has to
	 * be handled separately.
	 */
	अगर (iattr->ia_valid & (ATTR_MODE | ATTR_ATIME | ATTR_MTIME)) अणु
		अगर (iattr->ia_valid & ATTR_MODE) अणु
			info.attr.mode = mode_set(IRUSR);
			info.attr.mode |= mode_set(IWUSR);
			info.attr.mode |= mode_set(IXUSR);
			info.attr.mode |= mode_set(IRGRP);
			info.attr.mode |= mode_set(IWGRP);
			info.attr.mode |= mode_set(IXGRP);
			info.attr.mode |= mode_set(IROTH);
			info.attr.mode |= mode_set(IWOTH);
			info.attr.mode |= mode_set(IXOTH);

			अगर (iattr->ia_mode & S_IFसूची)
				info.attr.mode |= SHFL_TYPE_सूचीECTORY;
			अन्यथा
				info.attr.mode |= SHFL_TYPE_खाता;
		पूर्ण

		अगर (iattr->ia_valid & ATTR_ATIME)
			info.access_समय.ns_relative_to_unix_epoch =
					    बारpec64_to_ns(&iattr->ia_aसमय);

		अगर (iattr->ia_valid & ATTR_MTIME)
			info.modअगरication_समय.ns_relative_to_unix_epoch =
					    बारpec64_to_ns(&iattr->ia_mसमय);

		/*
		 * Ignore स_समय (inode change समय) as it can't be set
		 * from userland anyway.
		 */

		buf_len = माप(info);
		err = vboxsf_fsinfo(sbi->root, params.handle,
				    SHFL_INFO_SET | SHFL_INFO_खाता, &buf_len,
				    &info);
		अगर (err) अणु
			vboxsf_बंद(sbi->root, params.handle);
			वापस err;
		पूर्ण

		/* the host may have given us dअगरferent attr then requested */
		sf_i->क्रमce_restat = 1;
	पूर्ण

#अघोषित mode_set

	अगर (iattr->ia_valid & ATTR_SIZE) अणु
		स_रखो(&info, 0, माप(info));
		info.size = iattr->ia_size;
		buf_len = माप(info);
		err = vboxsf_fsinfo(sbi->root, params.handle,
				    SHFL_INFO_SET | SHFL_INFO_SIZE, &buf_len,
				    &info);
		अगर (err) अणु
			vboxsf_बंद(sbi->root, params.handle);
			वापस err;
		पूर्ण

		/* the host may have given us dअगरferent attr then requested */
		sf_i->क्रमce_restat = 1;
	पूर्ण

	vboxsf_बंद(sbi->root, params.handle);

	/* Update the inode with what the host has actually given us. */
	अगर (sf_i->क्रमce_restat)
		vboxsf_inode_revalidate(dentry);

	वापस 0;
पूर्ण

/*
 * [dentry] contains string encoded in coding प्रणाली that corresponds
 * to [sbi]->nls, we must convert it to UTF8 here.
 * Returns a shfl_string allocated through __getname (must be मुक्तd using
 * __putname), or an ERR_PTR on error.
 */
काष्ठा shfl_string *vboxsf_path_from_dentry(काष्ठा vboxsf_sbi *sbi,
					    काष्ठा dentry *dentry)
अणु
	काष्ठा shfl_string *shfl_path;
	पूर्णांक path_len, out_len, nb;
	अक्षर *buf, *path;
	ब_अक्षर_प्रकार uni;
	u8 *out;

	buf = __getname();
	अगर (!buf)
		वापस ERR_PTR(-ENOMEM);

	path = dentry_path_raw(dentry, buf, PATH_MAX);
	अगर (IS_ERR(path)) अणु
		__putname(buf);
		वापस ERR_CAST(path);
	पूर्ण
	path_len = म_माप(path);

	अगर (sbi->nls) अणु
		shfl_path = __getname();
		अगर (!shfl_path) अणु
			__putname(buf);
			वापस ERR_PTR(-ENOMEM);
		पूर्ण

		out = shfl_path->string.utf8;
		out_len = PATH_MAX - SHFLSTRING_HEADER_SIZE - 1;

		जबतक (path_len) अणु
			nb = sbi->nls->अक्षर2uni(path, path_len, &uni);
			अगर (nb < 0) अणु
				__putname(shfl_path);
				__putname(buf);
				वापस ERR_PTR(-EINVAL);
			पूर्ण
			path += nb;
			path_len -= nb;

			nb = utf32_to_utf8(uni, out, out_len);
			अगर (nb < 0) अणु
				__putname(shfl_path);
				__putname(buf);
				वापस ERR_PTR(-ENAMETOOLONG);
			पूर्ण
			out += nb;
			out_len -= nb;
		पूर्ण
		*out = 0;
		shfl_path->length = out - shfl_path->string.utf8;
		shfl_path->size = shfl_path->length + 1;
		__putname(buf);
	पूर्ण अन्यथा अणु
		अगर ((SHFLSTRING_HEADER_SIZE + path_len + 1) > PATH_MAX) अणु
			__putname(buf);
			वापस ERR_PTR(-ENAMETOOLONG);
		पूर्ण
		/*
		 * dentry_path stores the name at the end of buf, but the
		 * shfl_string string we वापस must be properly aligned.
		 */
		shfl_path = (काष्ठा shfl_string *)buf;
		स_हटाओ(shfl_path->string.utf8, path, path_len);
		shfl_path->string.utf8[path_len] = 0;
		shfl_path->length = path_len;
		shfl_path->size = path_len + 1;
	पूर्ण

	वापस shfl_path;
पूर्ण

पूर्णांक vboxsf_nlscpy(काष्ठा vboxsf_sbi *sbi, अक्षर *name, माप_प्रकार name_bound_len,
		  स्थिर अचिन्हित अक्षर *utf8_name, माप_प्रकार utf8_len)
अणु
	स्थिर अक्षर *in;
	अक्षर *out;
	माप_प्रकार out_len;
	माप_प्रकार out_bound_len;
	माप_प्रकार in_bound_len;

	in = utf8_name;
	in_bound_len = utf8_len;

	out = name;
	out_len = 0;
	/* Reserve space क्रम terminating 0 */
	out_bound_len = name_bound_len - 1;

	जबतक (in_bound_len) अणु
		पूर्णांक nb;
		unicode_t uni;

		nb = utf8_to_utf32(in, in_bound_len, &uni);
		अगर (nb < 0)
			वापस -EINVAL;

		in += nb;
		in_bound_len -= nb;

		nb = sbi->nls->uni2अक्षर(uni, out, out_bound_len);
		अगर (nb < 0)
			वापस nb;

		out += nb;
		out_bound_len -= nb;
		out_len += nb;
	पूर्ण

	*out = 0;

	वापस 0;
पूर्ण

अटल काष्ठा vboxsf_dir_buf *vboxsf_dir_buf_alloc(काष्ठा list_head *list)
अणु
	काष्ठा vboxsf_dir_buf *b;

	b = kदो_स्मृति(माप(*b), GFP_KERNEL);
	अगर (!b)
		वापस शून्य;

	b->buf = kदो_स्मृति(सूची_BUFFER_SIZE, GFP_KERNEL);
	अगर (!b->buf) अणु
		kमुक्त(b);
		वापस शून्य;
	पूर्ण

	b->entries = 0;
	b->used = 0;
	b->मुक्त = सूची_BUFFER_SIZE;
	list_add(&b->head, list);

	वापस b;
पूर्ण

अटल व्योम vboxsf_dir_buf_मुक्त(काष्ठा vboxsf_dir_buf *b)
अणु
	list_del(&b->head);
	kमुक्त(b->buf);
	kमुक्त(b);
पूर्ण

काष्ठा vboxsf_dir_info *vboxsf_dir_info_alloc(व्योम)
अणु
	काष्ठा vboxsf_dir_info *p;

	p = kदो_स्मृति(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस शून्य;

	INIT_LIST_HEAD(&p->info_list);
	वापस p;
पूर्ण

व्योम vboxsf_dir_info_मुक्त(काष्ठा vboxsf_dir_info *p)
अणु
	काष्ठा list_head *list, *pos, *पंचांगp;

	list = &p->info_list;
	list_क्रम_each_safe(pos, पंचांगp, list) अणु
		काष्ठा vboxsf_dir_buf *b;

		b = list_entry(pos, काष्ठा vboxsf_dir_buf, head);
		vboxsf_dir_buf_मुक्त(b);
	पूर्ण
	kमुक्त(p);
पूर्ण

पूर्णांक vboxsf_dir_पढ़ो_all(काष्ठा vboxsf_sbi *sbi, काष्ठा vboxsf_dir_info *sf_d,
			u64 handle)
अणु
	काष्ठा vboxsf_dir_buf *b;
	u32 entries, size;
	पूर्णांक err = 0;
	व्योम *buf;

	/* vboxsf_dirinfo वापसs 1 on end of dir */
	जबतक (err == 0) अणु
		b = vboxsf_dir_buf_alloc(&sf_d->info_list);
		अगर (!b) अणु
			err = -ENOMEM;
			अवरोध;
		पूर्ण

		buf = b->buf;
		size = b->मुक्त;

		err = vboxsf_dirinfo(sbi->root, handle, शून्य, 0, 0,
				     &size, buf, &entries);
		अगर (err < 0)
			अवरोध;

		b->entries += entries;
		b->मुक्त -= size;
		b->used += size;
	पूर्ण

	अगर (b && b->used == 0)
		vboxsf_dir_buf_मुक्त(b);

	/* -EILSEQ means the host could not translate a filename, ignore */
	अगर (err > 0 || err == -EILSEQ)
		err = 0;

	वापस err;
पूर्ण
