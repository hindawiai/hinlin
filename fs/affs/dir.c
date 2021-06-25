<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/affs/dir.c
 *
 *  (c) 1996  Hans-Joachim Widmaier - Rewritten
 *
 *  (C) 1993  Ray Burr - Modअगरied क्रम Amiga FFS fileप्रणाली.
 *
 *  (C) 1992  Eric Youngdale Modअगरied क्रम ISO 9660 fileप्रणाली.
 *
 *  (C) 1991  Linus Torvalds - minix fileप्रणाली
 *
 *  affs directory handling functions
 *
 */

#समावेश <linux/iversion.h>
#समावेश "affs.h"

अटल पूर्णांक affs_सूची_पढ़ो(काष्ठा file *, काष्ठा dir_context *);

स्थिर काष्ठा file_operations affs_dir_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.llseek		= generic_file_llseek,
	.iterate_shared	= affs_सूची_पढ़ो,
	.fsync		= affs_file_fsync,
पूर्ण;

/*
 * directories can handle most operations...
 */
स्थिर काष्ठा inode_operations affs_dir_inode_operations = अणु
	.create		= affs_create,
	.lookup		= affs_lookup,
	.link		= affs_link,
	.unlink		= affs_unlink,
	.symlink	= affs_symlink,
	.सूची_गढ़ो		= affs_सूची_गढ़ो,
	.सूची_हटाओ		= affs_सूची_हटाओ,
	.नाम		= affs_नाम2,
	.setattr	= affs_notअगरy_change,
पूर्ण;

अटल पूर्णांक
affs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode		*inode = file_inode(file);
	काष्ठा super_block	*sb = inode->i_sb;
	काष्ठा buffer_head	*dir_bh = शून्य;
	काष्ठा buffer_head	*fh_bh = शून्य;
	अचिन्हित अक्षर		*name;
	पूर्णांक			 namelen;
	u32			 i;
	पूर्णांक			 hash_pos;
	पूर्णांक			 chain_pos;
	u32			 ino;
	पूर्णांक			 error = 0;

	pr_debug("%s(ino=%lu,f_pos=%llx)\n", __func__, inode->i_ino, ctx->pos);

	अगर (ctx->pos < 2) अणु
		file->निजी_data = (व्योम *)0;
		अगर (!dir_emit_करोts(file, ctx))
			वापस 0;
	पूर्ण

	affs_lock_dir(inode);
	chain_pos = (ctx->pos - 2) & 0xffff;
	hash_pos  = (ctx->pos - 2) >> 16;
	अगर (chain_pos == 0xffff) अणु
		affs_warning(sb, "readdir", "More than 65535 entries in chain");
		chain_pos = 0;
		hash_pos++;
		ctx->pos = ((hash_pos << 16) | chain_pos) + 2;
	पूर्ण
	dir_bh = affs_bपढ़ो(sb, inode->i_ino);
	अगर (!dir_bh)
		जाओ out_unlock_dir;

	/* If the directory hasn't changed since the last call to सूची_पढ़ो(),
	 * we can jump directly to where we left off.
	 */
	ino = (u32)(दीर्घ)file->निजी_data;
	अगर (ino && inode_eq_iversion(inode, file->f_version)) अणु
		pr_debug("readdir() left off=%d\n", ino);
		जाओ inside;
	पूर्ण

	ino = be32_to_cpu(AFFS_HEAD(dir_bh)->table[hash_pos]);
	क्रम (i = 0; ino && i < chain_pos; i++) अणु
		fh_bh = affs_bपढ़ो(sb, ino);
		अगर (!fh_bh) अणु
			affs_error(sb, "readdir","Cannot read block %d", i);
			error = -EIO;
			जाओ out_brअन्यथा_dir;
		पूर्ण
		ino = be32_to_cpu(AFFS_TAIL(sb, fh_bh)->hash_chain);
		affs_brअन्यथा(fh_bh);
		fh_bh = शून्य;
	पूर्ण
	अगर (ino)
		जाओ inside;
	hash_pos++;

	क्रम (; hash_pos < AFFS_SB(sb)->s_hashsize; hash_pos++) अणु
		ino = be32_to_cpu(AFFS_HEAD(dir_bh)->table[hash_pos]);
		अगर (!ino)
			जारी;
		ctx->pos = (hash_pos << 16) + 2;
inside:
		करो अणु
			fh_bh = affs_bपढ़ो(sb, ino);
			अगर (!fh_bh) अणु
				affs_error(sb, "readdir",
					   "Cannot read block %d", ino);
				अवरोध;
			पूर्ण

			namelen = min(AFFS_TAIL(sb, fh_bh)->name[0],
				      (u8)AFFSNAMEMAX);
			name = AFFS_TAIL(sb, fh_bh)->name + 1;
			pr_debug("readdir(): dir_emit(\"%.*s\", ino=%u), hash=%d, f_pos=%llx\n",
				 namelen, name, ino, hash_pos, ctx->pos);

			अगर (!dir_emit(ctx, name, namelen, ino, DT_UNKNOWN))
				जाओ करोne;
			ctx->pos++;
			ino = be32_to_cpu(AFFS_TAIL(sb, fh_bh)->hash_chain);
			affs_brअन्यथा(fh_bh);
			fh_bh = शून्य;
		पूर्ण जबतक (ino);
	पूर्ण
करोne:
	file->f_version = inode_query_iversion(inode);
	file->निजी_data = (व्योम *)(दीर्घ)ino;
	affs_brअन्यथा(fh_bh);

out_brअन्यथा_dir:
	affs_brअन्यथा(dir_bh);

out_unlock_dir:
	affs_unlock_dir(inode);
	वापस error;
पूर्ण
