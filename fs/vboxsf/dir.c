<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * VirtualBox Guest Shared Folders support: Directory inode and file operations
 *
 * Copyright (C) 2006-2018 Oracle Corporation
 */

#समावेश <linux/namei.h>
#समावेश <linux/vbox_utils.h>
#समावेश "vfsmod.h"

अटल पूर्णांक vboxsf_dir_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(inode->i_sb);
	काष्ठा shfl_createparms params = अणुपूर्ण;
	काष्ठा vboxsf_dir_info *sf_d;
	पूर्णांक err;

	sf_d = vboxsf_dir_info_alloc();
	अगर (!sf_d)
		वापस -ENOMEM;

	params.handle = SHFL_HANDLE_NIL;
	params.create_flags = SHFL_CF_सूचीECTORY | SHFL_CF_ACT_OPEN_IF_EXISTS |
			      SHFL_CF_ACT_FAIL_IF_NEW | SHFL_CF_ACCESS_READ;

	err = vboxsf_create_at_dentry(file_dentry(file), &params);
	अगर (err)
		जाओ err_मुक्त_dir_info;

	अगर (params.result != SHFL_खाता_EXISTS) अणु
		err = -ENOENT;
		जाओ err_बंद;
	पूर्ण

	err = vboxsf_dir_पढ़ो_all(sbi, sf_d, params.handle);
	अगर (err)
		जाओ err_बंद;

	vboxsf_बंद(sbi->root, params.handle);
	file->निजी_data = sf_d;
	वापस 0;

err_बंद:
	vboxsf_बंद(sbi->root, params.handle);
err_मुक्त_dir_info:
	vboxsf_dir_info_मुक्त(sf_d);
	वापस err;
पूर्ण

अटल पूर्णांक vboxsf_dir_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (file->निजी_data)
		vboxsf_dir_info_मुक्त(file->निजी_data);

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक vboxsf_get_d_type(u32 mode)
अणु
	अचिन्हित पूर्णांक d_type;

	चयन (mode & SHFL_TYPE_MASK) अणु
	हाल SHFL_TYPE_FIFO:
		d_type = DT_FIFO;
		अवरोध;
	हाल SHFL_TYPE_DEV_CHAR:
		d_type = DT_CHR;
		अवरोध;
	हाल SHFL_TYPE_सूचीECTORY:
		d_type = DT_सूची;
		अवरोध;
	हाल SHFL_TYPE_DEV_BLOCK:
		d_type = DT_BLK;
		अवरोध;
	हाल SHFL_TYPE_खाता:
		d_type = DT_REG;
		अवरोध;
	हाल SHFL_TYPE_SYMLINK:
		d_type = DT_LNK;
		अवरोध;
	हाल SHFL_TYPE_SOCKET:
		d_type = DT_SOCK;
		अवरोध;
	हाल SHFL_TYPE_WHITEOUT:
		d_type = DT_WHT;
		अवरोध;
	शेष:
		d_type = DT_UNKNOWN;
		अवरोध;
	पूर्ण
	वापस d_type;
पूर्ण

अटल bool vboxsf_dir_emit(काष्ठा file *dir, काष्ठा dir_context *ctx)
अणु
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(file_inode(dir)->i_sb);
	काष्ठा vboxsf_dir_info *sf_d = dir->निजी_data;
	काष्ठा shfl_dirinfo *info;
	काष्ठा vboxsf_dir_buf *b;
	अचिन्हित पूर्णांक d_type;
	loff_t i, cur = 0;
	ino_t fake_ino;
	व्योम *end;
	पूर्णांक err;

	list_क्रम_each_entry(b, &sf_d->info_list, head) अणु
try_next_entry:
		अगर (ctx->pos >= cur + b->entries) अणु
			cur += b->entries;
			जारी;
		पूर्ण

		/*
		 * Note the vboxsf_dir_info objects we are iterating over here
		 * are variable sized, so the info poपूर्णांकer may end up being
		 * unaligned. This is how we get the data from the host.
		 * Since vboxsf is only supported on x86 machines this is not
		 * a problem.
		 */
		क्रम (i = 0, info = b->buf; i < ctx->pos - cur; i++) अणु
			end = &info->name.string.utf8[info->name.size];
			/* Only happens अगर the host gives us corrupt data */
			अगर (WARN_ON(end > (b->buf + b->used)))
				वापस false;
			info = end;
		पूर्ण

		end = &info->name.string.utf8[info->name.size];
		अगर (WARN_ON(end > (b->buf + b->used)))
			वापस false;

		/* Info now poपूर्णांकs to the right entry, emit it. */
		d_type = vboxsf_get_d_type(info->info.attr.mode);

		/*
		 * On 32-bit प्रणालीs pos is 64-bit चिन्हित, जबतक ino is 32-bit
		 * अचिन्हित so fake_ino may overflow, check क्रम this.
		 */
		अगर ((ino_t)(ctx->pos + 1) != (u64)(ctx->pos + 1)) अणु
			vbg_err("vboxsf: fake ino overflow, truncating dir\n");
			वापस false;
		पूर्ण
		fake_ino = ctx->pos + 1;

		अगर (sbi->nls) अणु
			अक्षर d_name[NAME_MAX];

			err = vboxsf_nlscpy(sbi, d_name, NAME_MAX,
					    info->name.string.utf8,
					    info->name.length);
			अगर (err) अणु
				/* skip erroneous entry and proceed */
				ctx->pos += 1;
				जाओ try_next_entry;
			पूर्ण

			वापस dir_emit(ctx, d_name, म_माप(d_name),
					fake_ino, d_type);
		पूर्ण

		वापस dir_emit(ctx, info->name.string.utf8, info->name.length,
				fake_ino, d_type);
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक vboxsf_dir_iterate(काष्ठा file *dir, काष्ठा dir_context *ctx)
अणु
	bool emitted;

	करो अणु
		emitted = vboxsf_dir_emit(dir, ctx);
		अगर (emitted)
			ctx->pos += 1;
	पूर्ण जबतक (emitted);

	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations vboxsf_dir_fops = अणु
	.खोलो = vboxsf_dir_खोलो,
	.iterate = vboxsf_dir_iterate,
	.release = vboxsf_dir_release,
	.पढ़ो = generic_पढ़ो_dir,
	.llseek = generic_file_llseek,
पूर्ण;

/*
 * This is called during name resolution/lookup to check अगर the @dentry in
 * the cache is still valid. the job is handled by vboxsf_inode_revalidate.
 */
अटल पूर्णांक vboxsf_dentry_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	अगर (flags & LOOKUP_RCU)
		वापस -ECHILD;

	अगर (d_really_is_positive(dentry))
		वापस vboxsf_inode_revalidate(dentry) == 0;
	अन्यथा
		वापस vboxsf_stat_dentry(dentry, शून्य) == -ENOENT;
पूर्ण

स्थिर काष्ठा dentry_operations vboxsf_dentry_ops = अणु
	.d_revalidate = vboxsf_dentry_revalidate
पूर्ण;

/* iops */

अटल काष्ठा dentry *vboxsf_dir_lookup(काष्ठा inode *parent,
					काष्ठा dentry *dentry,
					अचिन्हित पूर्णांक flags)
अणु
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(parent->i_sb);
	काष्ठा shfl_fsobjinfo fsinfo;
	काष्ठा inode *inode;
	पूर्णांक err;

	dentry->d_समय = jअगरfies;

	err = vboxsf_stat_dentry(dentry, &fsinfo);
	अगर (err) अणु
		inode = (err == -ENOENT) ? शून्य : ERR_PTR(err);
	पूर्ण अन्यथा अणु
		inode = vboxsf_new_inode(parent->i_sb);
		अगर (!IS_ERR(inode))
			vboxsf_init_inode(sbi, inode, &fsinfo, false);
	पूर्ण

	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल पूर्णांक vboxsf_dir_instantiate(काष्ठा inode *parent, काष्ठा dentry *dentry,
				  काष्ठा shfl_fsobjinfo *info)
अणु
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(parent->i_sb);
	काष्ठा vboxsf_inode *sf_i;
	काष्ठा inode *inode;

	inode = vboxsf_new_inode(parent->i_sb);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	sf_i = VBOXSF_I(inode);
	/* The host may have given us dअगरferent attr then requested */
	sf_i->क्रमce_restat = 1;
	vboxsf_init_inode(sbi, inode, info, false);

	d_instantiate(dentry, inode);

	वापस 0;
पूर्ण

अटल पूर्णांक vboxsf_dir_create(काष्ठा inode *parent, काष्ठा dentry *dentry,
			     umode_t mode, पूर्णांक is_dir)
अणु
	काष्ठा vboxsf_inode *sf_parent_i = VBOXSF_I(parent);
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(parent->i_sb);
	काष्ठा shfl_createparms params = अणुपूर्ण;
	पूर्णांक err;

	params.handle = SHFL_HANDLE_NIL;
	params.create_flags = SHFL_CF_ACT_CREATE_IF_NEW |
			      SHFL_CF_ACT_FAIL_IF_EXISTS |
			      SHFL_CF_ACCESS_READWRITE |
			      (is_dir ? SHFL_CF_सूचीECTORY : 0);
	params.info.attr.mode = (mode & 0777) |
				(is_dir ? SHFL_TYPE_सूचीECTORY : SHFL_TYPE_खाता);
	params.info.attr.additional = SHFLFSOBJATTRADD_NOTHING;

	err = vboxsf_create_at_dentry(dentry, &params);
	अगर (err)
		वापस err;

	अगर (params.result != SHFL_खाता_CREATED)
		वापस -EPERM;

	vboxsf_बंद(sbi->root, params.handle);

	err = vboxsf_dir_instantiate(parent, dentry, &params.info);
	अगर (err)
		वापस err;

	/* parent directory access/change समय changed */
	sf_parent_i->क्रमce_restat = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक vboxsf_dir_mkfile(काष्ठा user_namespace *mnt_userns,
			     काष्ठा inode *parent, काष्ठा dentry *dentry,
			     umode_t mode, bool excl)
अणु
	वापस vboxsf_dir_create(parent, dentry, mode, 0);
पूर्ण

अटल पूर्णांक vboxsf_dir_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns,
			    काष्ठा inode *parent, काष्ठा dentry *dentry,
			    umode_t mode)
अणु
	वापस vboxsf_dir_create(parent, dentry, mode, 1);
पूर्ण

अटल पूर्णांक vboxsf_dir_unlink(काष्ठा inode *parent, काष्ठा dentry *dentry)
अणु
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(parent->i_sb);
	काष्ठा vboxsf_inode *sf_parent_i = VBOXSF_I(parent);
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा shfl_string *path;
	u32 flags;
	पूर्णांक err;

	अगर (S_ISसूची(inode->i_mode))
		flags = SHFL_REMOVE_सूची;
	अन्यथा
		flags = SHFL_REMOVE_खाता;

	अगर (S_ISLNK(inode->i_mode))
		flags |= SHFL_REMOVE_SYMLINK;

	path = vboxsf_path_from_dentry(sbi, dentry);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);

	err = vboxsf_हटाओ(sbi->root, path, flags);
	__putname(path);
	अगर (err)
		वापस err;

	/* parent directory access/change समय changed */
	sf_parent_i->क्रमce_restat = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक vboxsf_dir_नाम(काष्ठा user_namespace *mnt_userns,
			     काष्ठा inode *old_parent,
			     काष्ठा dentry *old_dentry,
			     काष्ठा inode *new_parent,
			     काष्ठा dentry *new_dentry,
			     अचिन्हित पूर्णांक flags)
अणु
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(old_parent->i_sb);
	काष्ठा vboxsf_inode *sf_old_parent_i = VBOXSF_I(old_parent);
	काष्ठा vboxsf_inode *sf_new_parent_i = VBOXSF_I(new_parent);
	u32 shfl_flags = SHFL_RENAME_खाता | SHFL_RENAME_REPLACE_IF_EXISTS;
	काष्ठा shfl_string *old_path, *new_path;
	पूर्णांक err;

	अगर (flags)
		वापस -EINVAL;

	old_path = vboxsf_path_from_dentry(sbi, old_dentry);
	अगर (IS_ERR(old_path))
		वापस PTR_ERR(old_path);

	new_path = vboxsf_path_from_dentry(sbi, new_dentry);
	अगर (IS_ERR(new_path)) अणु
		err = PTR_ERR(new_path);
		जाओ err_put_old_path;
	पूर्ण

	अगर (d_inode(old_dentry)->i_mode & S_IFसूची)
		shfl_flags = 0;

	err = vboxsf_नाम(sbi->root, old_path, new_path, shfl_flags);
	अगर (err == 0) अणु
		/* parent directories access/change समय changed */
		sf_new_parent_i->क्रमce_restat = 1;
		sf_old_parent_i->क्रमce_restat = 1;
	पूर्ण

	__putname(new_path);
err_put_old_path:
	__putname(old_path);
	वापस err;
पूर्ण

अटल पूर्णांक vboxsf_dir_symlink(काष्ठा user_namespace *mnt_userns,
			      काष्ठा inode *parent, काष्ठा dentry *dentry,
			      स्थिर अक्षर *symname)
अणु
	काष्ठा vboxsf_inode *sf_parent_i = VBOXSF_I(parent);
	काष्ठा vboxsf_sbi *sbi = VBOXSF_SBI(parent->i_sb);
	पूर्णांक symname_size = म_माप(symname) + 1;
	काष्ठा shfl_string *path, *ssymname;
	काष्ठा shfl_fsobjinfo info;
	पूर्णांक err;

	path = vboxsf_path_from_dentry(sbi, dentry);
	अगर (IS_ERR(path))
		वापस PTR_ERR(path);

	ssymname = kदो_स्मृति(SHFLSTRING_HEADER_SIZE + symname_size, GFP_KERNEL);
	अगर (!ssymname) अणु
		__putname(path);
		वापस -ENOMEM;
	पूर्ण
	ssymname->length = symname_size - 1;
	ssymname->size = symname_size;
	स_नकल(ssymname->string.utf8, symname, symname_size);

	err = vboxsf_symlink(sbi->root, path, ssymname, &info);
	kमुक्त(ssymname);
	__putname(path);
	अगर (err) अणु
		/* -EROFS means symlinks are note support -> -EPERM */
		वापस (err == -EROFS) ? -EPERM : err;
	पूर्ण

	err = vboxsf_dir_instantiate(parent, dentry, &info);
	अगर (err)
		वापस err;

	/* parent directory access/change समय changed */
	sf_parent_i->क्रमce_restat = 1;
	वापस 0;
पूर्ण

स्थिर काष्ठा inode_operations vboxsf_dir_iops = अणु
	.lookup  = vboxsf_dir_lookup,
	.create  = vboxsf_dir_mkfile,
	.सूची_गढ़ो   = vboxsf_dir_सूची_गढ़ो,
	.सूची_हटाओ   = vboxsf_dir_unlink,
	.unlink  = vboxsf_dir_unlink,
	.नाम  = vboxsf_dir_नाम,
	.symlink = vboxsf_dir_symlink,
	.getattr = vboxsf_getattr,
	.setattr = vboxsf_setattr,
पूर्ण;
