<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/adfs/dir.c
 *
 *  Copyright (C) 1999-2000 Russell King
 *
 *  Common directory handling क्रम ADFS
 */
#समावेश <linux/slab.h>
#समावेश "adfs.h"

/*
 * For future.  This should probably be per-directory.
 */
अटल DECLARE_RWSEM(adfs_dir_rwsem);

पूर्णांक adfs_dir_copyfrom(व्योम *dst, काष्ठा adfs_dir *dir, अचिन्हित पूर्णांक offset,
		      माप_प्रकार len)
अणु
	काष्ठा super_block *sb = dir->sb;
	अचिन्हित पूर्णांक index, reमुख्य;

	index = offset >> sb->s_blocksize_bits;
	offset &= sb->s_blocksize - 1;
	reमुख्य = sb->s_blocksize - offset;
	अगर (index + (reमुख्य < len) >= dir->nr_buffers)
		वापस -EINVAL;

	अगर (reमुख्य < len) अणु
		स_नकल(dst, dir->bhs[index]->b_data + offset, reमुख्य);
		dst += reमुख्य;
		len -= reमुख्य;
		index += 1;
		offset = 0;
	पूर्ण

	स_नकल(dst, dir->bhs[index]->b_data + offset, len);

	वापस 0;
पूर्ण

पूर्णांक adfs_dir_copyto(काष्ठा adfs_dir *dir, अचिन्हित पूर्णांक offset, स्थिर व्योम *src,
		    माप_प्रकार len)
अणु
	काष्ठा super_block *sb = dir->sb;
	अचिन्हित पूर्णांक index, reमुख्य;

	index = offset >> sb->s_blocksize_bits;
	offset &= sb->s_blocksize - 1;
	reमुख्य = sb->s_blocksize - offset;
	अगर (index + (reमुख्य < len) >= dir->nr_buffers)
		वापस -EINVAL;

	अगर (reमुख्य < len) अणु
		स_नकल(dir->bhs[index]->b_data + offset, src, reमुख्य);
		src += reमुख्य;
		len -= reमुख्य;
		index += 1;
		offset = 0;
	पूर्ण

	स_नकल(dir->bhs[index]->b_data + offset, src, len);

	वापस 0;
पूर्ण

अटल व्योम __adfs_dir_cleanup(काष्ठा adfs_dir *dir)
अणु
	dir->nr_buffers = 0;

	अगर (dir->bhs != dir->bh)
		kमुक्त(dir->bhs);
	dir->bhs = शून्य;
	dir->sb = शून्य;
पूर्ण

व्योम adfs_dir_rअन्यथा(काष्ठा adfs_dir *dir)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dir->nr_buffers; i++)
		brअन्यथा(dir->bhs[i]);

	__adfs_dir_cleanup(dir);
पूर्ण

अटल व्योम adfs_dir_क्रमget(काष्ठा adfs_dir *dir)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < dir->nr_buffers; i++)
		bक्रमget(dir->bhs[i]);

	__adfs_dir_cleanup(dir);
पूर्ण

पूर्णांक adfs_dir_पढ़ो_buffers(काष्ठा super_block *sb, u32 indaddr,
			  अचिन्हित पूर्णांक size, काष्ठा adfs_dir *dir)
अणु
	काष्ठा buffer_head **bhs;
	अचिन्हित पूर्णांक i, num;
	पूर्णांक block;

	num = ALIGN(size, sb->s_blocksize) >> sb->s_blocksize_bits;
	अगर (num > ARRAY_SIZE(dir->bh)) अणु
		/* We only allow one extension */
		अगर (dir->bhs != dir->bh)
			वापस -EINVAL;

		bhs = kसुस्मृति(num, माप(*bhs), GFP_KERNEL);
		अगर (!bhs)
			वापस -ENOMEM;

		अगर (dir->nr_buffers)
			स_नकल(bhs, dir->bhs, dir->nr_buffers * माप(*bhs));

		dir->bhs = bhs;
	पूर्ण

	क्रम (i = dir->nr_buffers; i < num; i++) अणु
		block = __adfs_block_map(sb, indaddr, i);
		अगर (!block) अणु
			adfs_error(sb, "dir %06x has a hole at offset %u",
				   indaddr, i);
			जाओ error;
		पूर्ण

		dir->bhs[i] = sb_bपढ़ो(sb, block);
		अगर (!dir->bhs[i]) अणु
			adfs_error(sb,
				   "dir %06x failed read at offset %u, mapped block 0x%08x",
				   indaddr, i, block);
			जाओ error;
		पूर्ण

		dir->nr_buffers++;
	पूर्ण
	वापस 0;

error:
	adfs_dir_rअन्यथा(dir);

	वापस -EIO;
पूर्ण

अटल पूर्णांक adfs_dir_पढ़ो(काष्ठा super_block *sb, u32 indaddr,
			 अचिन्हित पूर्णांक size, काष्ठा adfs_dir *dir)
अणु
	dir->sb = sb;
	dir->bhs = dir->bh;
	dir->nr_buffers = 0;

	वापस ADFS_SB(sb)->s_dir->पढ़ो(sb, indaddr, size, dir);
पूर्ण

अटल पूर्णांक adfs_dir_पढ़ो_inode(काष्ठा super_block *sb, काष्ठा inode *inode,
			       काष्ठा adfs_dir *dir)
अणु
	पूर्णांक ret;

	ret = adfs_dir_पढ़ो(sb, ADFS_I(inode)->indaddr, inode->i_size, dir);
	अगर (ret)
		वापस ret;

	अगर (ADFS_I(inode)->parent_id != dir->parent_id) अणु
		adfs_error(sb,
			   "parent directory id changed under me! (%06x but got %06x)\n",
			   ADFS_I(inode)->parent_id, dir->parent_id);
		adfs_dir_rअन्यथा(dir);
		ret = -EIO;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम adfs_dir_mark_dirty(काष्ठा adfs_dir *dir)
अणु
	अचिन्हित पूर्णांक i;

	/* Mark the buffers dirty */
	क्रम (i = 0; i < dir->nr_buffers; i++)
		mark_buffer_dirty(dir->bhs[i]);
पूर्ण

अटल पूर्णांक adfs_dir_sync(काष्ठा adfs_dir *dir)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	क्रम (i = dir->nr_buffers - 1; i >= 0; i--) अणु
		काष्ठा buffer_head *bh = dir->bhs[i];
		sync_dirty_buffer(bh);
		अगर (buffer_req(bh) && !buffer_uptodate(bh))
			err = -EIO;
	पूर्ण

	वापस err;
पूर्ण

व्योम adfs_object_fixup(काष्ठा adfs_dir *dir, काष्ठा object_info *obj)
अणु
	अचिन्हित पूर्णांक करोts, i;

	/*
	 * RISC OS allows the use of '/' in directory entry names, so we need
	 * to fix these up.  '/' is typically used क्रम FAT compatibility to
	 * represent '.', so do the same conversion here.  In any case, '.'
	 * will never be in a RISC OS name since it is used as the pathname
	 * separator.  Handle the हाल where we may generate a '.' or '..'
	 * name, replacing the first अक्षरacter with '^' (the RISC OS "parent
	 * directory" अक्षरacter.)
	 */
	क्रम (i = करोts = 0; i < obj->name_len; i++)
		अगर (obj->name[i] == '/') अणु
			obj->name[i] = '.';
			करोts++;
		पूर्ण

	अगर (obj->name_len <= 2 && करोts == obj->name_len)
		obj->name[0] = '^';

	/*
	 * If the object is a file, and the user requested the ,xyz hex
	 * filetype suffix to the name, check the filetype and append.
	 */
	अगर (!(obj->attr & ADFS_NDA_सूचीECTORY) && ADFS_SB(dir->sb)->s_ftsuffix) अणु
		u16 filetype = adfs_filetype(obj->loadaddr);

		अगर (filetype != ADFS_खाताTYPE_NONE) अणु
			obj->name[obj->name_len++] = ',';
			obj->name[obj->name_len++] = hex_asc_lo(filetype >> 8);
			obj->name[obj->name_len++] = hex_asc_lo(filetype >> 4);
			obj->name[obj->name_len++] = hex_asc_lo(filetype >> 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक adfs_iterate(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा super_block *sb = inode->i_sb;
	स्थिर काष्ठा adfs_dir_ops *ops = ADFS_SB(sb)->s_dir;
	काष्ठा adfs_dir dir;
	पूर्णांक ret;

	करोwn_पढ़ो(&adfs_dir_rwsem);
	ret = adfs_dir_पढ़ो_inode(sb, inode, &dir);
	अगर (ret)
		जाओ unlock;

	अगर (ctx->pos == 0) अणु
		अगर (!dir_emit_करोt(file, ctx))
			जाओ unlock_rअन्यथा;
		ctx->pos = 1;
	पूर्ण
	अगर (ctx->pos == 1) अणु
		अगर (!dir_emit(ctx, "..", 2, dir.parent_id, DT_सूची))
			जाओ unlock_rअन्यथा;
		ctx->pos = 2;
	पूर्ण

	ret = ops->iterate(&dir, ctx);

unlock_rअन्यथा:
	up_पढ़ो(&adfs_dir_rwsem);
	adfs_dir_rअन्यथा(&dir);
	वापस ret;

unlock:
	up_पढ़ो(&adfs_dir_rwsem);
	वापस ret;
पूर्ण

पूर्णांक
adfs_dir_update(काष्ठा super_block *sb, काष्ठा object_info *obj, पूर्णांक रुको)
अणु
	स्थिर काष्ठा adfs_dir_ops *ops = ADFS_SB(sb)->s_dir;
	काष्ठा adfs_dir dir;
	पूर्णांक ret;

	अगर (!IS_ENABLED(CONFIG_ADFS_FS_RW))
		वापस -EINVAL;

	अगर (!ops->update)
		वापस -EINVAL;

	करोwn_ग_लिखो(&adfs_dir_rwsem);
	ret = adfs_dir_पढ़ो(sb, obj->parent_id, 0, &dir);
	अगर (ret)
		जाओ unlock;

	ret = ops->update(&dir, obj);
	अगर (ret)
		जाओ क्रमget;

	ret = ops->commit(&dir);
	अगर (ret)
		जाओ क्रमget;
	up_ग_लिखो(&adfs_dir_rwsem);

	adfs_dir_mark_dirty(&dir);

	अगर (रुको)
		ret = adfs_dir_sync(&dir);

	adfs_dir_rअन्यथा(&dir);
	वापस ret;

	/*
	 * If the updated failed because the entry wasn't found, we can
	 * just release the buffers. If it was any other error, क्रमget
	 * the dirtied buffers so they aren't written back to the media.
	 */
क्रमget:
	अगर (ret == -ENOENT)
		adfs_dir_rअन्यथा(&dir);
	अन्यथा
		adfs_dir_क्रमget(&dir);
unlock:
	up_ग_लिखो(&adfs_dir_rwsem);

	वापस ret;
पूर्ण

अटल अचिन्हित अक्षर adfs_छोटे(अचिन्हित अक्षर c)
अणु
	अगर (c >= 'A' && c <= 'Z')
		c += 'a' - 'A';
	वापस c;
पूर्ण

अटल पूर्णांक __adfs_compare(स्थिर अचिन्हित अक्षर *qstr, u32 qlen,
			  स्थिर अक्षर *str, u32 len)
अणु
	u32 i;

	अगर (qlen != len)
		वापस 1;

	क्रम (i = 0; i < qlen; i++)
		अगर (adfs_छोटे(qstr[i]) != adfs_छोटे(str[i]))
			वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक adfs_dir_lookup_byname(काष्ठा inode *inode, स्थिर काष्ठा qstr *qstr,
				  काष्ठा object_info *obj)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	स्थिर काष्ठा adfs_dir_ops *ops = ADFS_SB(sb)->s_dir;
	स्थिर अचिन्हित अक्षर *name;
	काष्ठा adfs_dir dir;
	u32 name_len;
	पूर्णांक ret;

	करोwn_पढ़ो(&adfs_dir_rwsem);
	ret = adfs_dir_पढ़ो_inode(sb, inode, &dir);
	अगर (ret)
		जाओ unlock;

	ret = ops->setpos(&dir, 0);
	अगर (ret)
		जाओ unlock_rअन्यथा;

	ret = -ENOENT;
	name = qstr->name;
	name_len = qstr->len;
	जबतक (ops->getnext(&dir, obj) == 0) अणु
		अगर (!__adfs_compare(name, name_len, obj->name, obj->name_len)) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	obj->parent_id = ADFS_I(inode)->indaddr;

unlock_rअन्यथा:
	up_पढ़ो(&adfs_dir_rwsem);
	adfs_dir_rअन्यथा(&dir);
	वापस ret;

unlock:
	up_पढ़ो(&adfs_dir_rwsem);
	वापस ret;
पूर्ण

स्थिर काष्ठा file_operations adfs_dir_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.llseek		= generic_file_llseek,
	.iterate_shared	= adfs_iterate,
	.fsync		= generic_file_fsync,
पूर्ण;

अटल पूर्णांक
adfs_hash(स्थिर काष्ठा dentry *parent, काष्ठा qstr *qstr)
अणु
	स्थिर अचिन्हित अक्षर *name;
	अचिन्हित दीर्घ hash;
	u32 len;

	अगर (qstr->len > ADFS_SB(parent->d_sb)->s_namelen)
		वापस -ENAMETOOLONG;

	len = qstr->len;
	name = qstr->name;
	hash = init_name_hash(parent);
	जबतक (len--)
		hash = partial_name_hash(adfs_छोटे(*name++), hash);
	qstr->hash = end_name_hash(hash);

	वापस 0;
पूर्ण

/*
 * Compare two names, taking note of the name length
 * requirements of the underlying fileप्रणाली.
 */
अटल पूर्णांक adfs_compare(स्थिर काष्ठा dentry *dentry, अचिन्हित पूर्णांक len,
			स्थिर अक्षर *str, स्थिर काष्ठा qstr *qstr)
अणु
	वापस __adfs_compare(qstr->name, qstr->len, str, len);
पूर्ण

स्थिर काष्ठा dentry_operations adfs_dentry_operations = अणु
	.d_hash		= adfs_hash,
	.d_compare	= adfs_compare,
पूर्ण;

अटल काष्ठा dentry *
adfs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = शून्य;
	काष्ठा object_info obj;
	पूर्णांक error;

	error = adfs_dir_lookup_byname(dir, &dentry->d_name, &obj);
	अगर (error == 0) अणु
		/*
		 * This only वापसs शून्य अगर get_empty_inode
		 * fails.
		 */
		inode = adfs_iget(dir->i_sb, &obj);
		अगर (!inode)
			inode = ERR_PTR(-EACCES);
	पूर्ण अन्यथा अगर (error != -ENOENT) अणु
		inode = ERR_PTR(error);
	पूर्ण
	वापस d_splice_alias(inode, dentry);
पूर्ण

/*
 * directories can handle most operations...
 */
स्थिर काष्ठा inode_operations adfs_dir_inode_operations = अणु
	.lookup		= adfs_lookup,
	.setattr	= adfs_notअगरy_change,
पूर्ण;
