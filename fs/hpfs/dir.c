<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hpfs/dir.c
 *
 *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999
 *
 *  directory VFS functions
 */

#समावेश <linux/slab.h>
#समावेश "hpfs_fn.h"

अटल पूर्णांक hpfs_dir_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	hpfs_lock(inode->i_sb);
	hpfs_del_pos(inode, &filp->f_pos);
	/*hpfs_ग_लिखो_अगर_changed(inode);*/
	hpfs_unlock(inode->i_sb);
	वापस 0;
पूर्ण

/* This is slow, but it's not used often */

अटल loff_t hpfs_dir_lseek(काष्ठा file *filp, loff_t off, पूर्णांक whence)
अणु
	loff_t new_off = off + (whence == 1 ? filp->f_pos : 0);
	loff_t pos;
	काष्ठा quad_buffer_head qbh;
	काष्ठा inode *i = file_inode(filp);
	काष्ठा hpfs_inode_info *hpfs_inode = hpfs_i(i);
	काष्ठा super_block *s = i->i_sb;

	/* Somebody अन्यथा will have to figure out what to करो here */
	अगर (whence == SEEK_DATA || whence == SEEK_HOLE)
		वापस -EINVAL;

	inode_lock(i);
	hpfs_lock(s);

	/*pr_info("dir lseek\n");*/
	अगर (new_off == 0 || new_off == 1 || new_off == 11 || new_off == 12 || new_off == 13) जाओ ok;
	pos = ((loff_t) hpfs_de_as_करोwn_as_possible(s, hpfs_inode->i_dno) << 4) + 1;
	जबतक (pos != new_off) अणु
		अगर (map_pos_dirent(i, &pos, &qbh)) hpfs_brअन्यथा4(&qbh);
		अन्यथा जाओ fail;
		अगर (pos == 12) जाओ fail;
	पूर्ण
	अगर (unlikely(hpfs_add_pos(i, &filp->f_pos) < 0)) अणु
		hpfs_unlock(s);
		inode_unlock(i);
		वापस -ENOMEM;
	पूर्ण
ok:
	filp->f_pos = new_off;
	hpfs_unlock(s);
	inode_unlock(i);
	वापस new_off;
fail:
	/*pr_warn("illegal lseek: %016llx\n", new_off);*/
	hpfs_unlock(s);
	inode_unlock(i);
	वापस -ESPIPE;
पूर्ण

अटल पूर्णांक hpfs_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	काष्ठा hpfs_inode_info *hpfs_inode = hpfs_i(inode);
	काष्ठा quad_buffer_head qbh;
	काष्ठा hpfs_dirent *de;
	पूर्णांक lc;
	loff_t next_pos;
	अचिन्हित अक्षर *tempname;
	पूर्णांक c1, c2 = 0;
	पूर्णांक ret = 0;

	hpfs_lock(inode->i_sb);

	अगर (hpfs_sb(inode->i_sb)->sb_chk) अणु
		अगर (hpfs_chk_sectors(inode->i_sb, inode->i_ino, 1, "dir_fnode")) अणु
			ret = -EFSERROR;
			जाओ out;
		पूर्ण
		अगर (hpfs_chk_sectors(inode->i_sb, hpfs_inode->i_dno, 4, "dir_dnode")) अणु
			ret = -EFSERROR;
			जाओ out;
		पूर्ण
	पूर्ण
	अगर (hpfs_sb(inode->i_sb)->sb_chk >= 2) अणु
		काष्ठा buffer_head *bh;
		काष्ठा fnode *fno;
		पूर्णांक e = 0;
		अगर (!(fno = hpfs_map_fnode(inode->i_sb, inode->i_ino, &bh))) अणु
			ret = -EIOERROR;
			जाओ out;
		पूर्ण
		अगर (!fnode_is_dir(fno)) अणु
			e = 1;
			hpfs_error(inode->i_sb, "not a directory, fnode %08lx",
					(अचिन्हित दीर्घ)inode->i_ino);
		पूर्ण
		अगर (hpfs_inode->i_dno != le32_to_cpu(fno->u.बाह्यal[0].disk_secno)) अणु
			e = 1;
			hpfs_error(inode->i_sb, "corrupted inode: i_dno == %08x, fnode -> dnode == %08x", hpfs_inode->i_dno, le32_to_cpu(fno->u.बाह्यal[0].disk_secno));
		पूर्ण
		brअन्यथा(bh);
		अगर (e) अणु
			ret = -EFSERROR;
			जाओ out;
		पूर्ण
	पूर्ण
	lc = hpfs_sb(inode->i_sb)->sb_lowerहाल;
	अगर (ctx->pos == 12) अणु /* dअगरf -r requires this (note, that dअगरf -r */
		ctx->pos = 13; /* also fails on msकरोs fileप्रणाली in 2.0) */
		जाओ out;
	पूर्ण
	अगर (ctx->pos == 13) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण
	
	जबतक (1) अणु
		again:
		/* This won't work when cycle is दीर्घer than number of dirents
		   accepted by filldir, but what can I करो?
		   maybe समाप्तall -9 ls helps */
		अगर (hpfs_sb(inode->i_sb)->sb_chk)
			अगर (hpfs_stop_cycles(inode->i_sb, ctx->pos, &c1, &c2, "hpfs_readdir")) अणु
				ret = -EFSERROR;
				जाओ out;
			पूर्ण
		अगर (ctx->pos == 12)
			जाओ out;
		अगर (ctx->pos == 3 || ctx->pos == 4 || ctx->pos == 5) अणु
			pr_err("pos==%d\n", (पूर्णांक)ctx->pos);
			जाओ out;
		पूर्ण
		अगर (ctx->pos == 0) अणु
			अगर (!dir_emit_करोt(file, ctx))
				जाओ out;
			ctx->pos = 11;
		पूर्ण
		अगर (ctx->pos == 11) अणु
			अगर (!dir_emit(ctx, "..", 2, hpfs_inode->i_parent_dir, DT_सूची))
				जाओ out;
			ctx->pos = 1;
		पूर्ण
		अगर (ctx->pos == 1) अणु
			ret = hpfs_add_pos(inode, &file->f_pos);
			अगर (unlikely(ret < 0))
				जाओ out;
			ctx->pos = ((loff_t) hpfs_de_as_करोwn_as_possible(inode->i_sb, hpfs_inode->i_dno) << 4) + 1;
		पूर्ण
		next_pos = ctx->pos;
		अगर (!(de = map_pos_dirent(inode, &next_pos, &qbh))) अणु
			ctx->pos = next_pos;
			ret = -EIOERROR;
			जाओ out;
		पूर्ण
		अगर (de->first || de->last) अणु
			अगर (hpfs_sb(inode->i_sb)->sb_chk) अणु
				अगर (de->first && !de->last && (de->namelen != 2
				    || de ->name[0] != 1 || de->name[1] != 1))
					hpfs_error(inode->i_sb, "hpfs_सूची_पढ़ो: bad ^A^A entry; pos = %08lx", (अचिन्हित दीर्घ)ctx->pos);
				अगर (de->last && (de->namelen != 1 || de ->name[0] != 255))
					hpfs_error(inode->i_sb, "hpfs_readdir: bad \\377 entry; pos = %08lx", (अचिन्हित दीर्घ)ctx->pos);
			पूर्ण
			hpfs_brअन्यथा4(&qbh);
			ctx->pos = next_pos;
			जाओ again;
		पूर्ण
		tempname = hpfs_translate_name(inode->i_sb, de->name, de->namelen, lc, de->not_8x3);
		अगर (!dir_emit(ctx, tempname, de->namelen, le32_to_cpu(de->fnode), DT_UNKNOWN)) अणु
			अगर (tempname != de->name) kमुक्त(tempname);
			hpfs_brअन्यथा4(&qbh);
			जाओ out;
		पूर्ण
		ctx->pos = next_pos;
		अगर (tempname != de->name) kमुक्त(tempname);
		hpfs_brअन्यथा4(&qbh);
	पूर्ण
out:
	hpfs_unlock(inode->i_sb);
	वापस ret;
पूर्ण

/*
 * lookup.  Search the specअगरied directory क्रम the specअगरied name, set
 * *result to the corresponding inode.
 *
 * lookup uses the inode number to tell पढ़ो_inode whether it is पढ़ोing
 * the inode of a directory or a file -- file ino's are odd, directory
 * ino's are even.  पढ़ो_inode aव्योमs i/o क्रम file inodes; everything
 * needed is up here in the directory.  (And file fnodes are out in
 * the boonकरोcks.)
 *
 *    - M.P.: this is over, someबार we've got to read file's fnode क्रम eas
 *	      inode numbers are just fnode sector numbers; iget lock is used
 *	      to tell पढ़ो_inode to पढ़ो fnode or not.
 */

काष्ठा dentry *hpfs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	स्थिर अचिन्हित अक्षर *name = dentry->d_name.name;
	अचिन्हित len = dentry->d_name.len;
	काष्ठा quad_buffer_head qbh;
	काष्ठा hpfs_dirent *de;
	ino_t ino;
	पूर्णांक err;
	काष्ठा inode *result = शून्य;
	काष्ठा hpfs_inode_info *hpfs_result;

	hpfs_lock(dir->i_sb);
	अगर ((err = hpfs_chk_name(name, &len))) अणु
		अगर (err == -ENAMETOOLONG) अणु
			hpfs_unlock(dir->i_sb);
			वापस ERR_PTR(-ENAMETOOLONG);
		पूर्ण
		जाओ end_add;
	पूर्ण

	/*
	 * '.' and '..' will never be passed here.
	 */

	de = map_dirent(dir, hpfs_i(dir)->i_dno, name, len, शून्य, &qbh);

	/*
	 * This is not really a bailout, just means file not found.
	 */

	अगर (!de) जाओ end;

	/*
	 * Get inode number, what we're after.
	 */

	ino = le32_to_cpu(de->fnode);

	/*
	 * Go find or make an inode.
	 */

	result = iget_locked(dir->i_sb, ino);
	अगर (!result) अणु
		hpfs_error(dir->i_sb, "hpfs_lookup: can't get inode");
		result = ERR_PTR(-ENOMEM);
		जाओ bail1;
	पूर्ण
	अगर (result->i_state & I_NEW) अणु
		hpfs_init_inode(result);
		अगर (de->directory)
			hpfs_पढ़ो_inode(result);
		अन्यथा अगर (le32_to_cpu(de->ea_size) && hpfs_sb(dir->i_sb)->sb_eas)
			hpfs_पढ़ो_inode(result);
		अन्यथा अणु
			result->i_mode |= S_IFREG;
			result->i_mode &= ~0111;
			result->i_op = &hpfs_file_iops;
			result->i_fop = &hpfs_file_ops;
			set_nlink(result, 1);
		पूर्ण
		unlock_new_inode(result);
	पूर्ण
	hpfs_result = hpfs_i(result);
	अगर (!de->directory) hpfs_result->i_parent_dir = dir->i_ino;

	अगर (de->has_acl || de->has_xtd_perm) अगर (!sb_rकरोnly(dir->i_sb)) अणु
		hpfs_error(result->i_sb, "ACLs or XPERM found. This is probably HPFS386. This driver doesn't support it now. Send me some info on these structures");
		iput(result);
		result = ERR_PTR(-EINVAL);
		जाओ bail1;
	पूर्ण

	/*
	 * Fill in the info from the directory अगर this is a newly created
	 * inode.
	 */

	अगर (!result->i_स_समय.tv_sec) अणु
		अगर (!(result->i_स_समय.tv_sec = local_to_gmt(dir->i_sb, le32_to_cpu(de->creation_date))))
			result->i_स_समय.tv_sec = 1;
		result->i_स_समय.tv_nsec = 0;
		result->i_mसमय.tv_sec = local_to_gmt(dir->i_sb, le32_to_cpu(de->ग_लिखो_date));
		result->i_mसमय.tv_nsec = 0;
		result->i_aसमय.tv_sec = local_to_gmt(dir->i_sb, le32_to_cpu(de->पढ़ो_date));
		result->i_aसमय.tv_nsec = 0;
		hpfs_result->i_ea_size = le32_to_cpu(de->ea_size);
		अगर (!hpfs_result->i_ea_mode && de->पढ़ो_only)
			result->i_mode &= ~0222;
		अगर (!de->directory) अणु
			अगर (result->i_size == -1) अणु
				result->i_size = le32_to_cpu(de->file_size);
				result->i_data.a_ops = &hpfs_aops;
				hpfs_i(result)->mmu_निजी = result->i_size;
			/*
			 * i_blocks should count the fnode and any anodes.
			 * We count 1 क्रम the fnode and करोn't bother about
			 * anodes -- the disk heads are on the directory band
			 * and we want them to stay there.
			 */
				result->i_blocks = 1 + ((result->i_size + 511) >> 9);
			पूर्ण
		पूर्ण
	पूर्ण

bail1:
	hpfs_brअन्यथा4(&qbh);

	/*
	 * Made it.
	 */

end:
end_add:
	hpfs_unlock(dir->i_sb);
	वापस d_splice_alias(result, dentry);
पूर्ण

स्थिर काष्ठा file_operations hpfs_dir_ops =
अणु
	.llseek		= hpfs_dir_lseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= hpfs_सूची_पढ़ो,
	.release	= hpfs_dir_release,
	.fsync		= hpfs_file_fsync,
	.unlocked_ioctl	= hpfs_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
पूर्ण;
