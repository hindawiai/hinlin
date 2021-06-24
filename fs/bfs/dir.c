<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	fs/bfs/dir.c
 *	BFS directory operations.
 *	Copyright (C) 1999-2018  Tigran Aivazian <aivazian.tigran@gmail.com>
 *  Made endianness-clean by Andrew Stribblehill <ads@wompom.org> 2005
 */

#समावेश <linux/समय.स>
#समावेश <linux/माला.स>
#समावेश <linux/fs.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/sched.h>
#समावेश "bfs.h"

#अघोषित DEBUG

#अगर_घोषित DEBUG
#घोषणा dम_लिखो(x...)	म_लिखो(x)
#अन्यथा
#घोषणा dम_लिखो(x...)
#पूर्ण_अगर

अटल पूर्णांक bfs_add_entry(काष्ठा inode *dir, स्थिर काष्ठा qstr *child, पूर्णांक ino);
अटल काष्ठा buffer_head *bfs_find_entry(काष्ठा inode *dir,
				स्थिर काष्ठा qstr *child,
				काष्ठा bfs_dirent **res_dir);

अटल पूर्णांक bfs_सूची_पढ़ो(काष्ठा file *f, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *dir = file_inode(f);
	काष्ठा buffer_head *bh;
	काष्ठा bfs_dirent *de;
	अचिन्हित पूर्णांक offset;
	पूर्णांक block;

	अगर (ctx->pos & (BFS_सूचीENT_SIZE - 1)) अणु
		म_लिखो("Bad f_pos=%08lx for %s:%08lx\n",
					(अचिन्हित दीर्घ)ctx->pos,
					dir->i_sb->s_id, dir->i_ino);
		वापस -EINVAL;
	पूर्ण

	जबतक (ctx->pos < dir->i_size) अणु
		offset = ctx->pos & (BFS_BSIZE - 1);
		block = BFS_I(dir)->i_sblock + (ctx->pos >> BFS_BSIZE_BITS);
		bh = sb_bपढ़ो(dir->i_sb, block);
		अगर (!bh) अणु
			ctx->pos += BFS_BSIZE - offset;
			जारी;
		पूर्ण
		करो अणु
			de = (काष्ठा bfs_dirent *)(bh->b_data + offset);
			अगर (de->ino) अणु
				पूर्णांक size = strnlen(de->name, BFS_NAMELEN);
				अगर (!dir_emit(ctx, de->name, size,
						le16_to_cpu(de->ino),
						DT_UNKNOWN)) अणु
					brअन्यथा(bh);
					वापस 0;
				पूर्ण
			पूर्ण
			offset += BFS_सूचीENT_SIZE;
			ctx->pos += BFS_सूचीENT_SIZE;
		पूर्ण जबतक ((offset < BFS_BSIZE) && (ctx->pos < dir->i_size));
		brअन्यथा(bh);
	पूर्ण
	वापस 0;
पूर्ण

स्थिर काष्ठा file_operations bfs_dir_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= bfs_सूची_पढ़ो,
	.fsync		= generic_file_fsync,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल पूर्णांक bfs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	पूर्णांक err;
	काष्ठा inode *inode;
	काष्ठा super_block *s = dir->i_sb;
	काष्ठा bfs_sb_info *info = BFS_SB(s);
	अचिन्हित दीर्घ ino;

	inode = new_inode(s);
	अगर (!inode)
		वापस -ENOMEM;
	mutex_lock(&info->bfs_lock);
	ino = find_first_zero_bit(info->si_imap, info->si_lasti + 1);
	अगर (ino > info->si_lasti) अणु
		mutex_unlock(&info->bfs_lock);
		iput(inode);
		वापस -ENOSPC;
	पूर्ण
	set_bit(ino, info->si_imap);
	info->si_मुक्तi--;
	inode_init_owner(&init_user_ns, inode, dir, mode);
	inode->i_mसमय = inode->i_aसमय = inode->i_स_समय = current_समय(inode);
	inode->i_blocks = 0;
	inode->i_op = &bfs_file_inops;
	inode->i_fop = &bfs_file_operations;
	inode->i_mapping->a_ops = &bfs_aops;
	inode->i_ino = ino;
	BFS_I(inode)->i_dsk_ino = ino;
	BFS_I(inode)->i_sblock = 0;
	BFS_I(inode)->i_eblock = 0;
	insert_inode_hash(inode);
        mark_inode_dirty(inode);
	bfs_dump_imap("create", s);

	err = bfs_add_entry(dir, &dentry->d_name, inode->i_ino);
	अगर (err) अणु
		inode_dec_link_count(inode);
		mutex_unlock(&info->bfs_lock);
		iput(inode);
		वापस err;
	पूर्ण
	mutex_unlock(&info->bfs_lock);
	d_instantiate(dentry, inode);
	वापस 0;
पूर्ण

अटल काष्ठा dentry *bfs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
						अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = शून्य;
	काष्ठा buffer_head *bh;
	काष्ठा bfs_dirent *de;
	काष्ठा bfs_sb_info *info = BFS_SB(dir->i_sb);

	अगर (dentry->d_name.len > BFS_NAMELEN)
		वापस ERR_PTR(-ENAMETOOLONG);

	mutex_lock(&info->bfs_lock);
	bh = bfs_find_entry(dir, &dentry->d_name, &de);
	अगर (bh) अणु
		अचिन्हित दीर्घ ino = (अचिन्हित दीर्घ)le16_to_cpu(de->ino);
		brअन्यथा(bh);
		inode = bfs_iget(dir->i_sb, ino);
	पूर्ण
	mutex_unlock(&info->bfs_lock);
	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल पूर्णांक bfs_link(काष्ठा dentry *old, काष्ठा inode *dir,
						काष्ठा dentry *new)
अणु
	काष्ठा inode *inode = d_inode(old);
	काष्ठा bfs_sb_info *info = BFS_SB(inode->i_sb);
	पूर्णांक err;

	mutex_lock(&info->bfs_lock);
	err = bfs_add_entry(dir, &new->d_name, inode->i_ino);
	अगर (err) अणु
		mutex_unlock(&info->bfs_lock);
		वापस err;
	पूर्ण
	inc_nlink(inode);
	inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);
	ihold(inode);
	d_instantiate(new, inode);
	mutex_unlock(&info->bfs_lock);
	वापस 0;
पूर्ण

अटल पूर्णांक bfs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक error = -ENOENT;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा buffer_head *bh;
	काष्ठा bfs_dirent *de;
	काष्ठा bfs_sb_info *info = BFS_SB(inode->i_sb);

	mutex_lock(&info->bfs_lock);
	bh = bfs_find_entry(dir, &dentry->d_name, &de);
	अगर (!bh || (le16_to_cpu(de->ino) != inode->i_ino))
		जाओ out_brअन्यथा;

	अगर (!inode->i_nlink) अणु
		म_लिखो("unlinking non-existent file %s:%lu (nlink=%d)\n",
					inode->i_sb->s_id, inode->i_ino,
					inode->i_nlink);
		set_nlink(inode, 1);
	पूर्ण
	de->ino = 0;
	mark_buffer_dirty_inode(bh, dir);
	dir->i_स_समय = dir->i_mसमय = current_समय(dir);
	mark_inode_dirty(dir);
	inode->i_स_समय = dir->i_स_समय;
	inode_dec_link_count(inode);
	error = 0;

out_brअन्यथा:
	brअन्यथा(bh);
	mutex_unlock(&info->bfs_lock);
	वापस error;
पूर्ण

अटल पूर्णांक bfs_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		      काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		      काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *old_inode, *new_inode;
	काष्ठा buffer_head *old_bh, *new_bh;
	काष्ठा bfs_dirent *old_de, *new_de;
	काष्ठा bfs_sb_info *info;
	पूर्णांक error = -ENOENT;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	old_bh = new_bh = शून्य;
	old_inode = d_inode(old_dentry);
	अगर (S_ISसूची(old_inode->i_mode))
		वापस -EINVAL;

	info = BFS_SB(old_inode->i_sb);

	mutex_lock(&info->bfs_lock);
	old_bh = bfs_find_entry(old_dir, &old_dentry->d_name, &old_de);

	अगर (!old_bh || (le16_to_cpu(old_de->ino) != old_inode->i_ino))
		जाओ end_नाम;

	error = -EPERM;
	new_inode = d_inode(new_dentry);
	new_bh = bfs_find_entry(new_dir, &new_dentry->d_name, &new_de);

	अगर (new_bh && !new_inode) अणु
		brअन्यथा(new_bh);
		new_bh = शून्य;
	पूर्ण
	अगर (!new_bh) अणु
		error = bfs_add_entry(new_dir, &new_dentry->d_name,
					old_inode->i_ino);
		अगर (error)
			जाओ end_नाम;
	पूर्ण
	old_de->ino = 0;
	old_dir->i_स_समय = old_dir->i_mसमय = current_समय(old_dir);
	mark_inode_dirty(old_dir);
	अगर (new_inode) अणु
		new_inode->i_स_समय = current_समय(new_inode);
		inode_dec_link_count(new_inode);
	पूर्ण
	mark_buffer_dirty_inode(old_bh, old_dir);
	error = 0;

end_नाम:
	mutex_unlock(&info->bfs_lock);
	brअन्यथा(old_bh);
	brअन्यथा(new_bh);
	वापस error;
पूर्ण

स्थिर काष्ठा inode_operations bfs_dir_inops = अणु
	.create			= bfs_create,
	.lookup			= bfs_lookup,
	.link			= bfs_link,
	.unlink			= bfs_unlink,
	.नाम			= bfs_नाम,
पूर्ण;

अटल पूर्णांक bfs_add_entry(काष्ठा inode *dir, स्थिर काष्ठा qstr *child, पूर्णांक ino)
अणु
	स्थिर अचिन्हित अक्षर *name = child->name;
	पूर्णांक namelen = child->len;
	काष्ठा buffer_head *bh;
	काष्ठा bfs_dirent *de;
	पूर्णांक block, sblock, eblock, off, pos;
	पूर्णांक i;

	dम_लिखो("name=%s, namelen=%d\n", name, namelen);

	अगर (!namelen)
		वापस -ENOENT;
	अगर (namelen > BFS_NAMELEN)
		वापस -ENAMETOOLONG;

	sblock = BFS_I(dir)->i_sblock;
	eblock = BFS_I(dir)->i_eblock;
	क्रम (block = sblock; block <= eblock; block++) अणु
		bh = sb_bपढ़ो(dir->i_sb, block);
		अगर (!bh)
			वापस -EIO;
		क्रम (off = 0; off < BFS_BSIZE; off += BFS_सूचीENT_SIZE) अणु
			de = (काष्ठा bfs_dirent *)(bh->b_data + off);
			अगर (!de->ino) अणु
				pos = (block - sblock) * BFS_BSIZE + off;
				अगर (pos >= dir->i_size) अणु
					dir->i_size += BFS_सूचीENT_SIZE;
					dir->i_स_समय = current_समय(dir);
				पूर्ण
				dir->i_mसमय = current_समय(dir);
				mark_inode_dirty(dir);
				de->ino = cpu_to_le16((u16)ino);
				क्रम (i = 0; i < BFS_NAMELEN; i++)
					de->name[i] =
						(i < namelen) ? name[i] : 0;
				mark_buffer_dirty_inode(bh, dir);
				brअन्यथा(bh);
				वापस 0;
			पूर्ण
		पूर्ण
		brअन्यथा(bh);
	पूर्ण
	वापस -ENOSPC;
पूर्ण

अटल अंतरभूत पूर्णांक bfs_namecmp(पूर्णांक len, स्थिर अचिन्हित अक्षर *name,
							स्थिर अक्षर *buffer)
अणु
	अगर ((len < BFS_NAMELEN) && buffer[len])
		वापस 0;
	वापस !स_भेद(name, buffer, len);
पूर्ण

अटल काष्ठा buffer_head *bfs_find_entry(काष्ठा inode *dir,
			स्थिर काष्ठा qstr *child,
			काष्ठा bfs_dirent **res_dir)
अणु
	अचिन्हित दीर्घ block = 0, offset = 0;
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा bfs_dirent *de;
	स्थिर अचिन्हित अक्षर *name = child->name;
	पूर्णांक namelen = child->len;

	*res_dir = शून्य;
	अगर (namelen > BFS_NAMELEN)
		वापस शून्य;

	जबतक (block * BFS_BSIZE + offset < dir->i_size) अणु
		अगर (!bh) अणु
			bh = sb_bपढ़ो(dir->i_sb, BFS_I(dir)->i_sblock + block);
			अगर (!bh) अणु
				block++;
				जारी;
			पूर्ण
		पूर्ण
		de = (काष्ठा bfs_dirent *)(bh->b_data + offset);
		offset += BFS_सूचीENT_SIZE;
		अगर (le16_to_cpu(de->ino) &&
				bfs_namecmp(namelen, name, de->name)) अणु
			*res_dir = de;
			वापस bh;
		पूर्ण
		अगर (offset < bh->b_size)
			जारी;
		brअन्यथा(bh);
		bh = शून्य;
		offset = 0;
		block++;
	पूर्ण
	brअन्यथा(bh);
	वापस शून्य;
पूर्ण
