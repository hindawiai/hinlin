<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hpfs/namei.c
 *
 *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999
 *
 *  adding & removing files & directories
 */
#समावेश <linux/sched.h>
#समावेश "hpfs_fn.h"

अटल व्योम hpfs_update_directory_बार(काष्ठा inode *dir)
अणु
	समय64_t t = local_to_gmt(dir->i_sb, local_get_seconds(dir->i_sb));
	अगर (t == dir->i_mसमय.tv_sec &&
	    t == dir->i_स_समय.tv_sec)
		वापस;
	dir->i_mसमय.tv_sec = dir->i_स_समय.tv_sec = t;
	dir->i_mसमय.tv_nsec = dir->i_स_समय.tv_nsec = 0;
	hpfs_ग_लिखो_inode_nolock(dir);
पूर्ण

अटल पूर्णांक hpfs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode)
अणु
	स्थिर अचिन्हित अक्षर *name = dentry->d_name.name;
	अचिन्हित len = dentry->d_name.len;
	काष्ठा quad_buffer_head qbh0;
	काष्ठा buffer_head *bh;
	काष्ठा hpfs_dirent *de;
	काष्ठा fnode *fnode;
	काष्ठा dnode *dnode;
	काष्ठा inode *result;
	fnode_secno fno;
	dnode_secno dno;
	पूर्णांक r;
	काष्ठा hpfs_dirent dee;
	पूर्णांक err;
	अगर ((err = hpfs_chk_name(name, &len))) वापस err==-ENOENT ? -EINVAL : err;
	hpfs_lock(dir->i_sb);
	err = -ENOSPC;
	fnode = hpfs_alloc_fnode(dir->i_sb, hpfs_i(dir)->i_dno, &fno, &bh);
	अगर (!fnode)
		जाओ bail;
	dnode = hpfs_alloc_dnode(dir->i_sb, fno, &dno, &qbh0);
	अगर (!dnode)
		जाओ bail1;
	स_रखो(&dee, 0, माप dee);
	dee.directory = 1;
	अगर (!(mode & 0222)) dee.पढ़ो_only = 1;
	/*dee.archive = 0;*/
	dee.hidden = name[0] == '.';
	dee.fnode = cpu_to_le32(fno);
	dee.creation_date = dee.ग_लिखो_date = dee.पढ़ो_date = cpu_to_le32(local_get_seconds(dir->i_sb));
	result = new_inode(dir->i_sb);
	अगर (!result)
		जाओ bail2;
	hpfs_init_inode(result);
	result->i_ino = fno;
	hpfs_i(result)->i_parent_dir = dir->i_ino;
	hpfs_i(result)->i_dno = dno;
	result->i_स_समय.tv_sec = result->i_mसमय.tv_sec = result->i_aसमय.tv_sec = local_to_gmt(dir->i_sb, le32_to_cpu(dee.creation_date));
	result->i_स_समय.tv_nsec = 0; 
	result->i_mसमय.tv_nsec = 0; 
	result->i_aसमय.tv_nsec = 0; 
	hpfs_i(result)->i_ea_size = 0;
	result->i_mode |= S_IFसूची;
	result->i_op = &hpfs_dir_iops;
	result->i_fop = &hpfs_dir_ops;
	result->i_blocks = 4;
	result->i_size = 2048;
	set_nlink(result, 2);
	अगर (dee.पढ़ो_only)
		result->i_mode &= ~0222;

	r = hpfs_add_dirent(dir, name, len, &dee);
	अगर (r == 1)
		जाओ bail3;
	अगर (r == -1) अणु
		err = -EEXIST;
		जाओ bail3;
	पूर्ण
	fnode->len = len;
	स_नकल(fnode->name, name, len > 15 ? 15 : len);
	fnode->up = cpu_to_le32(dir->i_ino);
	fnode->flags |= FNODE_dir;
	fnode->btree.n_मुक्त_nodes = 7;
	fnode->btree.n_used_nodes = 1;
	fnode->btree.first_मुक्त = cpu_to_le16(0x14);
	fnode->u.बाह्यal[0].disk_secno = cpu_to_le32(dno);
	fnode->u.बाह्यal[0].file_secno = cpu_to_le32(-1);
	dnode->root_dnode = 1;
	dnode->up = cpu_to_le32(fno);
	de = hpfs_add_de(dir->i_sb, dnode, "\001\001", 2, 0);
	de->creation_date = de->ग_लिखो_date = de->पढ़ो_date = cpu_to_le32(local_get_seconds(dir->i_sb));
	अगर (!(mode & 0222)) de->पढ़ो_only = 1;
	de->first = de->directory = 1;
	/*de->hidden = de->प्रणाली = 0;*/
	de->fnode = cpu_to_le32(fno);
	mark_buffer_dirty(bh);
	brअन्यथा(bh);
	hpfs_mark_4buffers_dirty(&qbh0);
	hpfs_brअन्यथा4(&qbh0);
	inc_nlink(dir);
	insert_inode_hash(result);

	अगर (!uid_eq(result->i_uid, current_fsuid()) ||
	    !gid_eq(result->i_gid, current_fsgid()) ||
	    result->i_mode != (mode | S_IFसूची)) अणु
		result->i_uid = current_fsuid();
		result->i_gid = current_fsgid();
		result->i_mode = mode | S_IFसूची;
		hpfs_ग_लिखो_inode_nolock(result);
	पूर्ण
	hpfs_update_directory_बार(dir);
	d_instantiate(dentry, result);
	hpfs_unlock(dir->i_sb);
	वापस 0;
bail3:
	iput(result);
bail2:
	hpfs_brअन्यथा4(&qbh0);
	hpfs_मुक्त_dnode(dir->i_sb, dno);
bail1:
	brअन्यथा(bh);
	hpfs_मुक्त_sectors(dir->i_sb, fno, 1);
bail:
	hpfs_unlock(dir->i_sb);
	वापस err;
पूर्ण

अटल पूर्णांक hpfs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	स्थिर अचिन्हित अक्षर *name = dentry->d_name.name;
	अचिन्हित len = dentry->d_name.len;
	काष्ठा inode *result = शून्य;
	काष्ठा buffer_head *bh;
	काष्ठा fnode *fnode;
	fnode_secno fno;
	पूर्णांक r;
	काष्ठा hpfs_dirent dee;
	पूर्णांक err;
	अगर ((err = hpfs_chk_name(name, &len)))
		वापस err==-ENOENT ? -EINVAL : err;
	hpfs_lock(dir->i_sb);
	err = -ENOSPC;
	fnode = hpfs_alloc_fnode(dir->i_sb, hpfs_i(dir)->i_dno, &fno, &bh);
	अगर (!fnode)
		जाओ bail;
	स_रखो(&dee, 0, माप dee);
	अगर (!(mode & 0222)) dee.पढ़ो_only = 1;
	dee.archive = 1;
	dee.hidden = name[0] == '.';
	dee.fnode = cpu_to_le32(fno);
	dee.creation_date = dee.ग_लिखो_date = dee.पढ़ो_date = cpu_to_le32(local_get_seconds(dir->i_sb));

	result = new_inode(dir->i_sb);
	अगर (!result)
		जाओ bail1;
	
	hpfs_init_inode(result);
	result->i_ino = fno;
	result->i_mode |= S_IFREG;
	result->i_mode &= ~0111;
	result->i_op = &hpfs_file_iops;
	result->i_fop = &hpfs_file_ops;
	set_nlink(result, 1);
	hpfs_i(result)->i_parent_dir = dir->i_ino;
	result->i_स_समय.tv_sec = result->i_mसमय.tv_sec = result->i_aसमय.tv_sec = local_to_gmt(dir->i_sb, le32_to_cpu(dee.creation_date));
	result->i_स_समय.tv_nsec = 0;
	result->i_mसमय.tv_nsec = 0;
	result->i_aसमय.tv_nsec = 0;
	hpfs_i(result)->i_ea_size = 0;
	अगर (dee.पढ़ो_only)
		result->i_mode &= ~0222;
	result->i_blocks = 1;
	result->i_size = 0;
	result->i_data.a_ops = &hpfs_aops;
	hpfs_i(result)->mmu_निजी = 0;

	r = hpfs_add_dirent(dir, name, len, &dee);
	अगर (r == 1)
		जाओ bail2;
	अगर (r == -1) अणु
		err = -EEXIST;
		जाओ bail2;
	पूर्ण
	fnode->len = len;
	स_नकल(fnode->name, name, len > 15 ? 15 : len);
	fnode->up = cpu_to_le32(dir->i_ino);
	mark_buffer_dirty(bh);
	brअन्यथा(bh);

	insert_inode_hash(result);

	अगर (!uid_eq(result->i_uid, current_fsuid()) ||
	    !gid_eq(result->i_gid, current_fsgid()) ||
	    result->i_mode != (mode | S_IFREG)) अणु
		result->i_uid = current_fsuid();
		result->i_gid = current_fsgid();
		result->i_mode = mode | S_IFREG;
		hpfs_ग_लिखो_inode_nolock(result);
	पूर्ण
	hpfs_update_directory_बार(dir);
	d_instantiate(dentry, result);
	hpfs_unlock(dir->i_sb);
	वापस 0;

bail2:
	iput(result);
bail1:
	brअन्यथा(bh);
	hpfs_मुक्त_sectors(dir->i_sb, fno, 1);
bail:
	hpfs_unlock(dir->i_sb);
	वापस err;
पूर्ण

अटल पूर्णांक hpfs_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	स्थिर अचिन्हित अक्षर *name = dentry->d_name.name;
	अचिन्हित len = dentry->d_name.len;
	काष्ठा buffer_head *bh;
	काष्ठा fnode *fnode;
	fnode_secno fno;
	पूर्णांक r;
	काष्ठा hpfs_dirent dee;
	काष्ठा inode *result = शून्य;
	पूर्णांक err;
	अगर ((err = hpfs_chk_name(name, &len))) वापस err==-ENOENT ? -EINVAL : err;
	अगर (hpfs_sb(dir->i_sb)->sb_eas < 2) वापस -EPERM;
	hpfs_lock(dir->i_sb);
	err = -ENOSPC;
	fnode = hpfs_alloc_fnode(dir->i_sb, hpfs_i(dir)->i_dno, &fno, &bh);
	अगर (!fnode)
		जाओ bail;
	स_रखो(&dee, 0, माप dee);
	अगर (!(mode & 0222)) dee.पढ़ो_only = 1;
	dee.archive = 1;
	dee.hidden = name[0] == '.';
	dee.fnode = cpu_to_le32(fno);
	dee.creation_date = dee.ग_लिखो_date = dee.पढ़ो_date = cpu_to_le32(local_get_seconds(dir->i_sb));

	result = new_inode(dir->i_sb);
	अगर (!result)
		जाओ bail1;

	hpfs_init_inode(result);
	result->i_ino = fno;
	hpfs_i(result)->i_parent_dir = dir->i_ino;
	result->i_स_समय.tv_sec = result->i_mसमय.tv_sec = result->i_aसमय.tv_sec = local_to_gmt(dir->i_sb, le32_to_cpu(dee.creation_date));
	result->i_स_समय.tv_nsec = 0;
	result->i_mसमय.tv_nsec = 0;
	result->i_aसमय.tv_nsec = 0;
	hpfs_i(result)->i_ea_size = 0;
	result->i_uid = current_fsuid();
	result->i_gid = current_fsgid();
	set_nlink(result, 1);
	result->i_size = 0;
	result->i_blocks = 1;
	init_special_inode(result, mode, rdev);

	r = hpfs_add_dirent(dir, name, len, &dee);
	अगर (r == 1)
		जाओ bail2;
	अगर (r == -1) अणु
		err = -EEXIST;
		जाओ bail2;
	पूर्ण
	fnode->len = len;
	स_नकल(fnode->name, name, len > 15 ? 15 : len);
	fnode->up = cpu_to_le32(dir->i_ino);
	mark_buffer_dirty(bh);

	insert_inode_hash(result);

	hpfs_ग_लिखो_inode_nolock(result);
	hpfs_update_directory_बार(dir);
	d_instantiate(dentry, result);
	brअन्यथा(bh);
	hpfs_unlock(dir->i_sb);
	वापस 0;
bail2:
	iput(result);
bail1:
	brअन्यथा(bh);
	hpfs_मुक्त_sectors(dir->i_sb, fno, 1);
bail:
	hpfs_unlock(dir->i_sb);
	वापस err;
पूर्ण

अटल पूर्णांक hpfs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, स्थिर अक्षर *symlink)
अणु
	स्थिर अचिन्हित अक्षर *name = dentry->d_name.name;
	अचिन्हित len = dentry->d_name.len;
	काष्ठा buffer_head *bh;
	काष्ठा fnode *fnode;
	fnode_secno fno;
	पूर्णांक r;
	काष्ठा hpfs_dirent dee;
	काष्ठा inode *result;
	पूर्णांक err;
	अगर ((err = hpfs_chk_name(name, &len))) वापस err==-ENOENT ? -EINVAL : err;
	hpfs_lock(dir->i_sb);
	अगर (hpfs_sb(dir->i_sb)->sb_eas < 2) अणु
		hpfs_unlock(dir->i_sb);
		वापस -EPERM;
	पूर्ण
	err = -ENOSPC;
	fnode = hpfs_alloc_fnode(dir->i_sb, hpfs_i(dir)->i_dno, &fno, &bh);
	अगर (!fnode)
		जाओ bail;
	स_रखो(&dee, 0, माप dee);
	dee.archive = 1;
	dee.hidden = name[0] == '.';
	dee.fnode = cpu_to_le32(fno);
	dee.creation_date = dee.ग_लिखो_date = dee.पढ़ो_date = cpu_to_le32(local_get_seconds(dir->i_sb));

	result = new_inode(dir->i_sb);
	अगर (!result)
		जाओ bail1;
	result->i_ino = fno;
	hpfs_init_inode(result);
	hpfs_i(result)->i_parent_dir = dir->i_ino;
	result->i_स_समय.tv_sec = result->i_mसमय.tv_sec = result->i_aसमय.tv_sec = local_to_gmt(dir->i_sb, le32_to_cpu(dee.creation_date));
	result->i_स_समय.tv_nsec = 0;
	result->i_mसमय.tv_nsec = 0;
	result->i_aसमय.tv_nsec = 0;
	hpfs_i(result)->i_ea_size = 0;
	result->i_mode = S_IFLNK | 0777;
	result->i_uid = current_fsuid();
	result->i_gid = current_fsgid();
	result->i_blocks = 1;
	set_nlink(result, 1);
	result->i_size = म_माप(symlink);
	inode_nohighmem(result);
	result->i_op = &page_symlink_inode_operations;
	result->i_data.a_ops = &hpfs_symlink_aops;

	r = hpfs_add_dirent(dir, name, len, &dee);
	अगर (r == 1)
		जाओ bail2;
	अगर (r == -1) अणु
		err = -EEXIST;
		जाओ bail2;
	पूर्ण
	fnode->len = len;
	स_नकल(fnode->name, name, len > 15 ? 15 : len);
	fnode->up = cpu_to_le32(dir->i_ino);
	hpfs_set_ea(result, fnode, "SYMLINK", symlink, म_माप(symlink));
	mark_buffer_dirty(bh);
	brअन्यथा(bh);

	insert_inode_hash(result);

	hpfs_ग_लिखो_inode_nolock(result);
	hpfs_update_directory_बार(dir);
	d_instantiate(dentry, result);
	hpfs_unlock(dir->i_sb);
	वापस 0;
bail2:
	iput(result);
bail1:
	brअन्यथा(bh);
	hpfs_मुक्त_sectors(dir->i_sb, fno, 1);
bail:
	hpfs_unlock(dir->i_sb);
	वापस err;
पूर्ण

अटल पूर्णांक hpfs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	स्थिर अचिन्हित अक्षर *name = dentry->d_name.name;
	अचिन्हित len = dentry->d_name.len;
	काष्ठा quad_buffer_head qbh;
	काष्ठा hpfs_dirent *de;
	काष्ठा inode *inode = d_inode(dentry);
	dnode_secno dno;
	पूर्णांक r;
	पूर्णांक err;

	hpfs_lock(dir->i_sb);
	hpfs_adjust_length(name, &len);

	err = -ENOENT;
	de = map_dirent(dir, hpfs_i(dir)->i_dno, name, len, &dno, &qbh);
	अगर (!de)
		जाओ out;

	err = -EPERM;
	अगर (de->first)
		जाओ out1;

	err = -EISसूची;
	अगर (de->directory)
		जाओ out1;

	r = hpfs_हटाओ_dirent(dir, dno, de, &qbh, 1);
	चयन (r) अणु
	हाल 1:
		hpfs_error(dir->i_sb, "there was error when removing dirent");
		err = -EFSERROR;
		अवरोध;
	हाल 2:		/* no space क्रम deleting */
		err = -ENOSPC;
		अवरोध;
	शेष:
		drop_nlink(inode);
		err = 0;
	पूर्ण
	जाओ out;

out1:
	hpfs_brअन्यथा4(&qbh);
out:
	अगर (!err)
		hpfs_update_directory_बार(dir);
	hpfs_unlock(dir->i_sb);
	वापस err;
पूर्ण

अटल पूर्णांक hpfs_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	स्थिर अचिन्हित अक्षर *name = dentry->d_name.name;
	अचिन्हित len = dentry->d_name.len;
	काष्ठा quad_buffer_head qbh;
	काष्ठा hpfs_dirent *de;
	काष्ठा inode *inode = d_inode(dentry);
	dnode_secno dno;
	पूर्णांक n_items = 0;
	पूर्णांक err;
	पूर्णांक r;

	hpfs_adjust_length(name, &len);
	hpfs_lock(dir->i_sb);
	err = -ENOENT;
	de = map_dirent(dir, hpfs_i(dir)->i_dno, name, len, &dno, &qbh);
	अगर (!de)
		जाओ out;

	err = -EPERM;
	अगर (de->first)
		जाओ out1;

	err = -ENOTसूची;
	अगर (!de->directory)
		जाओ out1;

	hpfs_count_dnodes(dir->i_sb, hpfs_i(inode)->i_dno, शून्य, शून्य, &n_items);
	err = -ENOTEMPTY;
	अगर (n_items)
		जाओ out1;

	r = hpfs_हटाओ_dirent(dir, dno, de, &qbh, 1);
	चयन (r) अणु
	हाल 1:
		hpfs_error(dir->i_sb, "there was error when removing dirent");
		err = -EFSERROR;
		अवरोध;
	हाल 2:
		err = -ENOSPC;
		अवरोध;
	शेष:
		drop_nlink(dir);
		clear_nlink(inode);
		err = 0;
	पूर्ण
	जाओ out;
out1:
	hpfs_brअन्यथा4(&qbh);
out:
	अगर (!err)
		hpfs_update_directory_बार(dir);
	hpfs_unlock(dir->i_sb);
	वापस err;
पूर्ण

अटल पूर्णांक hpfs_symlink_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	अक्षर *link = page_address(page);
	काष्ठा inode *i = page->mapping->host;
	काष्ठा fnode *fnode;
	काष्ठा buffer_head *bh;
	पूर्णांक err;

	err = -EIO;
	hpfs_lock(i->i_sb);
	अगर (!(fnode = hpfs_map_fnode(i->i_sb, i->i_ino, &bh)))
		जाओ fail;
	err = hpfs_पढ़ो_ea(i->i_sb, fnode, "SYMLINK", link, PAGE_SIZE);
	brअन्यथा(bh);
	अगर (err)
		जाओ fail;
	hpfs_unlock(i->i_sb);
	SetPageUptodate(page);
	unlock_page(page);
	वापस 0;

fail:
	hpfs_unlock(i->i_sb);
	SetPageError(page);
	unlock_page(page);
	वापस err;
पूर्ण

स्थिर काष्ठा address_space_operations hpfs_symlink_aops = अणु
	.पढ़ोpage	= hpfs_symlink_पढ़ोpage
पूर्ण;

अटल पूर्णांक hpfs_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		       काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		       काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	स्थिर अचिन्हित अक्षर *old_name = old_dentry->d_name.name;
	अचिन्हित old_len = old_dentry->d_name.len;
	स्थिर अचिन्हित अक्षर *new_name = new_dentry->d_name.name;
	अचिन्हित new_len = new_dentry->d_name.len;
	काष्ठा inode *i = d_inode(old_dentry);
	काष्ठा inode *new_inode = d_inode(new_dentry);
	काष्ठा quad_buffer_head qbh, qbh1;
	काष्ठा hpfs_dirent *dep, *nde;
	काष्ठा hpfs_dirent de;
	dnode_secno dno;
	पूर्णांक r;
	काष्ठा buffer_head *bh;
	काष्ठा fnode *fnode;
	पूर्णांक err;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	अगर ((err = hpfs_chk_name(new_name, &new_len))) वापस err;
	err = 0;
	hpfs_adjust_length(old_name, &old_len);

	hpfs_lock(i->i_sb);
	/* order करोesn't matter, due to VFS exclusion */
	
	/* Erm? Moving over the empty non-busy directory is perfectly legal */
	अगर (new_inode && S_ISसूची(new_inode->i_mode)) अणु
		err = -EINVAL;
		जाओ end1;
	पूर्ण

	अगर (!(dep = map_dirent(old_dir, hpfs_i(old_dir)->i_dno, old_name, old_len, &dno, &qbh))) अणु
		hpfs_error(i->i_sb, "lookup succeeded but map dirent failed");
		err = -ENOENT;
		जाओ end1;
	पूर्ण
	copy_de(&de, dep);
	de.hidden = new_name[0] == '.';

	अगर (new_inode) अणु
		पूर्णांक r;
		अगर ((r = hpfs_हटाओ_dirent(old_dir, dno, dep, &qbh, 1)) != 2) अणु
			अगर ((nde = map_dirent(new_dir, hpfs_i(new_dir)->i_dno, new_name, new_len, शून्य, &qbh1))) अणु
				clear_nlink(new_inode);
				copy_de(nde, &de);
				स_नकल(nde->name, new_name, new_len);
				hpfs_mark_4buffers_dirty(&qbh1);
				hpfs_brअन्यथा4(&qbh1);
				जाओ end;
			पूर्ण
			hpfs_error(new_dir->i_sb, "hpfs_rename: could not find dirent");
			err = -EFSERROR;
			जाओ end1;
		पूर्ण
		err = -ENOSPC;
		जाओ end1;
	पूर्ण

	अगर (new_dir == old_dir) hpfs_brअन्यथा4(&qbh);

	अगर ((r = hpfs_add_dirent(new_dir, new_name, new_len, &de))) अणु
		अगर (r == -1) hpfs_error(new_dir->i_sb, "hpfs_rename: dirent already exists!");
		err = r == 1 ? -ENOSPC : -EFSERROR;
		अगर (new_dir != old_dir) hpfs_brअन्यथा4(&qbh);
		जाओ end1;
	पूर्ण
	
	अगर (new_dir == old_dir)
		अगर (!(dep = map_dirent(old_dir, hpfs_i(old_dir)->i_dno, old_name, old_len, &dno, &qbh))) अणु
			hpfs_error(i->i_sb, "lookup succeeded but map dirent failed at #2");
			err = -ENOENT;
			जाओ end1;
		पूर्ण

	अगर ((r = hpfs_हटाओ_dirent(old_dir, dno, dep, &qbh, 0))) अणु
		hpfs_error(i->i_sb, "hpfs_rename: could not remove dirent");
		err = r == 2 ? -ENOSPC : -EFSERROR;
		जाओ end1;
	पूर्ण

end:
	hpfs_i(i)->i_parent_dir = new_dir->i_ino;
	अगर (S_ISसूची(i->i_mode)) अणु
		inc_nlink(new_dir);
		drop_nlink(old_dir);
	पूर्ण
	अगर ((fnode = hpfs_map_fnode(i->i_sb, i->i_ino, &bh))) अणु
		fnode->up = cpu_to_le32(new_dir->i_ino);
		fnode->len = new_len;
		स_नकल(fnode->name, new_name, new_len>15?15:new_len);
		अगर (new_len < 15) स_रखो(&fnode->name[new_len], 0, 15 - new_len);
		mark_buffer_dirty(bh);
		brअन्यथा(bh);
	पूर्ण
end1:
	अगर (!err) अणु
		hpfs_update_directory_बार(old_dir);
		hpfs_update_directory_बार(new_dir);
	पूर्ण
	hpfs_unlock(i->i_sb);
	वापस err;
पूर्ण

स्थिर काष्ठा inode_operations hpfs_dir_iops =
अणु
	.create		= hpfs_create,
	.lookup		= hpfs_lookup,
	.unlink		= hpfs_unlink,
	.symlink	= hpfs_symlink,
	.सूची_गढ़ो		= hpfs_सूची_गढ़ो,
	.सूची_हटाओ		= hpfs_सूची_हटाओ,
	.mknod		= hpfs_mknod,
	.नाम		= hpfs_नाम,
	.setattr	= hpfs_setattr,
पूर्ण;
