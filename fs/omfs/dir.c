<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OMFS (as used by RIO Karma) directory operations.
 * Copyright (C) 2005 Bob Copeland <me@bobcopeland.com>
 */

#समावेश <linux/fs.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/buffer_head.h>
#समावेश "omfs.h"

अटल पूर्णांक omfs_hash(स्थिर अक्षर *name, पूर्णांक namelen, पूर्णांक mod)
अणु
	पूर्णांक i, hash = 0;
	क्रम (i = 0; i < namelen; i++)
		hash ^= छोटे(name[i]) << (i % 24);
	वापस hash % mod;
पूर्ण

/*
 * Finds the bucket क्रम a given name and पढ़ोs the containing block;
 * *ofs is set to the offset of the first list entry.
 */
अटल काष्ठा buffer_head *omfs_get_bucket(काष्ठा inode *dir,
		स्थिर अक्षर *name, पूर्णांक namelen, पूर्णांक *ofs)
अणु
	पूर्णांक nbuckets = (dir->i_size - OMFS_सूची_START)/8;
	पूर्णांक bucket = omfs_hash(name, namelen, nbuckets);

	*ofs = OMFS_सूची_START + bucket * 8;
	वापस omfs_bपढ़ो(dir->i_sb, dir->i_ino);
पूर्ण

अटल काष्ठा buffer_head *omfs_scan_list(काष्ठा inode *dir, u64 block,
				स्थिर अक्षर *name, पूर्णांक namelen,
				u64 *prev_block)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा omfs_inode *oi;
	पूर्णांक err = -ENOENT;
	*prev_block = ~0;

	जबतक (block != ~0) अणु
		bh = omfs_bपढ़ो(dir->i_sb, block);
		अगर (!bh) अणु
			err = -EIO;
			जाओ err;
		पूर्ण

		oi = (काष्ठा omfs_inode *) bh->b_data;
		अगर (omfs_is_bad(OMFS_SB(dir->i_sb), &oi->i_head, block)) अणु
			brअन्यथा(bh);
			जाओ err;
		पूर्ण

		अगर (म_भेदन(oi->i_name, name, namelen) == 0)
			वापस bh;

		*prev_block = block;
		block = be64_to_cpu(oi->i_sibling);
		brअन्यथा(bh);
	पूर्ण
err:
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा buffer_head *omfs_find_entry(काष्ठा inode *dir,
					   स्थिर अक्षर *name, पूर्णांक namelen)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक ofs;
	u64 block, dummy;

	bh = omfs_get_bucket(dir, name, namelen, &ofs);
	अगर (!bh)
		वापस ERR_PTR(-EIO);

	block = be64_to_cpu(*((__be64 *) &bh->b_data[ofs]));
	brअन्यथा(bh);

	वापस omfs_scan_list(dir, block, name, namelen, &dummy);
पूर्ण

पूर्णांक omfs_make_empty(काष्ठा inode *inode, काष्ठा super_block *sb)
अणु
	काष्ठा omfs_sb_info *sbi = OMFS_SB(sb);
	काष्ठा buffer_head *bh;
	काष्ठा omfs_inode *oi;

	bh = omfs_bपढ़ो(sb, inode->i_ino);
	अगर (!bh)
		वापस -ENOMEM;

	स_रखो(bh->b_data, 0, माप(काष्ठा omfs_inode));

	अगर (S_ISसूची(inode->i_mode)) अणु
		स_रखो(&bh->b_data[OMFS_सूची_START], 0xff,
			sbi->s_sys_blocksize - OMFS_सूची_START);
	पूर्ण अन्यथा
		omfs_make_empty_table(bh, OMFS_EXTENT_START);

	oi = (काष्ठा omfs_inode *) bh->b_data;
	oi->i_head.h_self = cpu_to_be64(inode->i_ino);
	oi->i_sibling = ~cpu_to_be64(0ULL);

	mark_buffer_dirty(bh);
	brअन्यथा(bh);
	वापस 0;
पूर्ण

अटल पूर्णांक omfs_add_link(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	काष्ठा inode *dir = d_inode(dentry->d_parent);
	स्थिर अक्षर *name = dentry->d_name.name;
	पूर्णांक namelen = dentry->d_name.len;
	काष्ठा omfs_inode *oi;
	काष्ठा buffer_head *bh;
	u64 block;
	__be64 *entry;
	पूर्णांक ofs;

	/* just prepend to head of queue in proper bucket */
	bh = omfs_get_bucket(dir, name, namelen, &ofs);
	अगर (!bh)
		जाओ out;

	entry = (__be64 *) &bh->b_data[ofs];
	block = be64_to_cpu(*entry);
	*entry = cpu_to_be64(inode->i_ino);
	mark_buffer_dirty(bh);
	brअन्यथा(bh);

	/* now set the sibling and parent poपूर्णांकers on the new inode */
	bh = omfs_bपढ़ो(dir->i_sb, inode->i_ino);
	अगर (!bh)
		जाओ out;

	oi = (काष्ठा omfs_inode *) bh->b_data;
	स_नकल(oi->i_name, name, namelen);
	स_रखो(oi->i_name + namelen, 0, OMFS_NAMELEN - namelen);
	oi->i_sibling = cpu_to_be64(block);
	oi->i_parent = cpu_to_be64(dir->i_ino);
	mark_buffer_dirty(bh);
	brअन्यथा(bh);

	dir->i_स_समय = current_समय(dir);

	/* mark affected inodes dirty to rebuild checksums */
	mark_inode_dirty(dir);
	mark_inode_dirty(inode);
	वापस 0;
out:
	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक omfs_delete_entry(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *dir = d_inode(dentry->d_parent);
	काष्ठा inode *dirty;
	स्थिर अक्षर *name = dentry->d_name.name;
	पूर्णांक namelen = dentry->d_name.len;
	काष्ठा omfs_inode *oi;
	काष्ठा buffer_head *bh, *bh2;
	__be64 *entry, next;
	u64 block, prev;
	पूर्णांक ofs;
	पूर्णांक err = -ENOMEM;

	/* delete the proper node in the bucket's linked list */
	bh = omfs_get_bucket(dir, name, namelen, &ofs);
	अगर (!bh)
		जाओ out;

	entry = (__be64 *) &bh->b_data[ofs];
	block = be64_to_cpu(*entry);

	bh2 = omfs_scan_list(dir, block, name, namelen, &prev);
	अगर (IS_ERR(bh2)) अणु
		err = PTR_ERR(bh2);
		जाओ out_मुक्त_bh;
	पूर्ण

	oi = (काष्ठा omfs_inode *) bh2->b_data;
	next = oi->i_sibling;
	brअन्यथा(bh2);

	अगर (prev != ~0) अणु
		/* found in middle of list, get list ptr */
		brअन्यथा(bh);
		bh = omfs_bपढ़ो(dir->i_sb, prev);
		अगर (!bh)
			जाओ out;

		oi = (काष्ठा omfs_inode *) bh->b_data;
		entry = &oi->i_sibling;
	पूर्ण

	*entry = next;
	mark_buffer_dirty(bh);

	अगर (prev != ~0) अणु
		dirty = omfs_iget(dir->i_sb, prev);
		अगर (!IS_ERR(dirty)) अणु
			mark_inode_dirty(dirty);
			iput(dirty);
		पूर्ण
	पूर्ण

	err = 0;
out_मुक्त_bh:
	brअन्यथा(bh);
out:
	वापस err;
पूर्ण

अटल पूर्णांक omfs_dir_is_empty(काष्ठा inode *inode)
अणु
	पूर्णांक nbuckets = (inode->i_size - OMFS_सूची_START) / 8;
	काष्ठा buffer_head *bh;
	u64 *ptr;
	पूर्णांक i;

	bh = omfs_bपढ़ो(inode->i_sb, inode->i_ino);

	अगर (!bh)
		वापस 0;

	ptr = (u64 *) &bh->b_data[OMFS_सूची_START];

	क्रम (i = 0; i < nbuckets; i++, ptr++)
		अगर (*ptr != ~0)
			अवरोध;

	brअन्यथा(bh);
	वापस *ptr != ~0;
पूर्ण

अटल पूर्णांक omfs_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक ret;


	अगर (S_ISसूची(inode->i_mode) &&
	    !omfs_dir_is_empty(inode))
		वापस -ENOTEMPTY;

	ret = omfs_delete_entry(dentry);
	अगर (ret)
		वापस ret;
	
	clear_nlink(inode);
	mark_inode_dirty(inode);
	mark_inode_dirty(dir);
	वापस 0;
पूर्ण

अटल पूर्णांक omfs_add_node(काष्ठा inode *dir, काष्ठा dentry *dentry, umode_t mode)
अणु
	पूर्णांक err;
	काष्ठा inode *inode = omfs_new_inode(dir, mode);

	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	err = omfs_make_empty(inode, dir->i_sb);
	अगर (err)
		जाओ out_मुक्त_inode;

	err = omfs_add_link(dentry, inode);
	अगर (err)
		जाओ out_मुक्त_inode;

	d_instantiate(dentry, inode);
	वापस 0;

out_मुक्त_inode:
	iput(inode);
	वापस err;
पूर्ण

अटल पूर्णांक omfs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode)
अणु
	वापस omfs_add_node(dir, dentry, mode | S_IFसूची);
पूर्ण

अटल पूर्णांक omfs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	वापस omfs_add_node(dir, dentry, mode | S_IFREG);
पूर्ण

अटल काष्ठा dentry *omfs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				  अचिन्हित पूर्णांक flags)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा inode *inode = शून्य;

	अगर (dentry->d_name.len > OMFS_NAMELEN)
		वापस ERR_PTR(-ENAMETOOLONG);

	bh = omfs_find_entry(dir, dentry->d_name.name, dentry->d_name.len);
	अगर (!IS_ERR(bh)) अणु
		काष्ठा omfs_inode *oi = (काष्ठा omfs_inode *)bh->b_data;
		ino_t ino = be64_to_cpu(oi->i_head.h_self);
		brअन्यथा(bh);
		inode = omfs_iget(dir->i_sb, ino);
	पूर्ण अन्यथा अगर (bh != ERR_PTR(-ENOENT)) अणु
		inode = ERR_CAST(bh);
	पूर्ण
	वापस d_splice_alias(inode, dentry);
पूर्ण

/* sanity check block's self poपूर्णांकer */
पूर्णांक omfs_is_bad(काष्ठा omfs_sb_info *sbi, काष्ठा omfs_header *header,
	u64 fsblock)
अणु
	पूर्णांक is_bad;
	u64 ino = be64_to_cpu(header->h_self);
	is_bad = ((ino != fsblock) || (ino < sbi->s_root_ino) ||
		(ino > sbi->s_num_blocks));

	अगर (is_bad)
		prपूर्णांकk(KERN_WARNING "omfs: bad hash chain detected\n");

	वापस is_bad;
पूर्ण

अटल bool omfs_fill_chain(काष्ठा inode *dir, काष्ठा dir_context *ctx,
		u64 fsblock, पूर्णांक hindex)
अणु
	/* follow chain in this bucket */
	जबतक (fsblock != ~0) अणु
		काष्ठा buffer_head *bh = omfs_bपढ़ो(dir->i_sb, fsblock);
		काष्ठा omfs_inode *oi;
		u64 self;
		अचिन्हित अक्षर d_type;

		अगर (!bh)
			वापस true;

		oi = (काष्ठा omfs_inode *) bh->b_data;
		अगर (omfs_is_bad(OMFS_SB(dir->i_sb), &oi->i_head, fsblock)) अणु
			brअन्यथा(bh);
			वापस true;
		पूर्ण

		self = fsblock;
		fsblock = be64_to_cpu(oi->i_sibling);

		/* skip visited nodes */
		अगर (hindex) अणु
			hindex--;
			brअन्यथा(bh);
			जारी;
		पूर्ण

		d_type = (oi->i_type == OMFS_सूची) ? DT_सूची : DT_REG;

		अगर (!dir_emit(ctx, oi->i_name,
			      strnlen(oi->i_name, OMFS_NAMELEN),
			      self, d_type)) अणु
			brअन्यथा(bh);
			वापस false;
		पूर्ण
		brअन्यथा(bh);
		ctx->pos++;
	पूर्ण
	वापस true;
पूर्ण

अटल पूर्णांक omfs_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		       काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		       काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *new_inode = d_inode(new_dentry);
	काष्ठा inode *old_inode = d_inode(old_dentry);
	पूर्णांक err;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	अगर (new_inode) अणु
		/* overwriting existing file/dir */
		err = omfs_हटाओ(new_dir, new_dentry);
		अगर (err)
			जाओ out;
	पूर्ण

	/* since omfs locates files by name, we need to unlink _beक्रमe_
	 * adding the new link or we won't find the old one */
	err = omfs_delete_entry(old_dentry);
	अगर (err)
		जाओ out;

	mark_inode_dirty(old_dir);
	err = omfs_add_link(new_dentry, old_inode);
	अगर (err)
		जाओ out;

	old_inode->i_स_समय = current_समय(old_inode);
	mark_inode_dirty(old_inode);
out:
	वापस err;
पूर्ण

अटल पूर्णांक omfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *dir = file_inode(file);
	काष्ठा buffer_head *bh;
	__be64 *p;
	अचिन्हित पूर्णांक hchain, hindex;
	पूर्णांक nbuckets;

	अगर (ctx->pos >> 32)
		वापस -EINVAL;

	अगर (ctx->pos < 1 << 20) अणु
		अगर (!dir_emit_करोts(file, ctx))
			वापस 0;
		ctx->pos = 1 << 20;
	पूर्ण

	nbuckets = (dir->i_size - OMFS_सूची_START) / 8;

	/* high 12 bits store bucket + 1 and low 20 bits store hash index */
	hchain = (ctx->pos >> 20) - 1;
	hindex = ctx->pos & 0xfffff;

	bh = omfs_bपढ़ो(dir->i_sb, dir->i_ino);
	अगर (!bh)
		वापस -EINVAL;

	p = (__be64 *)(bh->b_data + OMFS_सूची_START) + hchain;

	क्रम (; hchain < nbuckets; hchain++) अणु
		__u64 fsblock = be64_to_cpu(*p++);
		अगर (!omfs_fill_chain(dir, ctx, fsblock, hindex))
			अवरोध;
		hindex = 0;
		ctx->pos = (hchain+2) << 20;
	पूर्ण
	brअन्यथा(bh);
	वापस 0;
पूर्ण

स्थिर काष्ठा inode_operations omfs_dir_inops = अणु
	.lookup = omfs_lookup,
	.सूची_गढ़ो = omfs_सूची_गढ़ो,
	.नाम = omfs_नाम,
	.create = omfs_create,
	.unlink = omfs_हटाओ,
	.सूची_हटाओ = omfs_हटाओ,
पूर्ण;

स्थिर काष्ठा file_operations omfs_dir_operations = अणु
	.पढ़ो = generic_पढ़ो_dir,
	.iterate_shared = omfs_सूची_पढ़ो,
	.llseek = generic_file_llseek,
पूर्ण;
