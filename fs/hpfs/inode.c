<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hpfs/inode.c
 *
 *  Mikulas Patocka (mikulas@artax.karlin.mff.cuni.cz), 1998-1999
 *
 *  inode VFS functions
 */

#समावेश <linux/slab.h>
#समावेश <linux/user_namespace.h>
#समावेश "hpfs_fn.h"

व्योम hpfs_init_inode(काष्ठा inode *i)
अणु
	काष्ठा super_block *sb = i->i_sb;
	काष्ठा hpfs_inode_info *hpfs_inode = hpfs_i(i);

	i->i_uid = hpfs_sb(sb)->sb_uid;
	i->i_gid = hpfs_sb(sb)->sb_gid;
	i->i_mode = hpfs_sb(sb)->sb_mode;
	i->i_size = -1;
	i->i_blocks = -1;
	
	hpfs_inode->i_dno = 0;
	hpfs_inode->i_n_secs = 0;
	hpfs_inode->i_file_sec = 0;
	hpfs_inode->i_disk_sec = 0;
	hpfs_inode->i_dpos = 0;
	hpfs_inode->i_dsubdno = 0;
	hpfs_inode->i_ea_mode = 0;
	hpfs_inode->i_ea_uid = 0;
	hpfs_inode->i_ea_gid = 0;
	hpfs_inode->i_ea_size = 0;

	hpfs_inode->i_rddir_off = शून्य;
	hpfs_inode->i_dirty = 0;

	i->i_स_समय.tv_sec = i->i_स_समय.tv_nsec = 0;
	i->i_mसमय.tv_sec = i->i_mसमय.tv_nsec = 0;
	i->i_aसमय.tv_sec = i->i_aसमय.tv_nsec = 0;
पूर्ण

व्योम hpfs_पढ़ो_inode(काष्ठा inode *i)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा fnode *fnode;
	काष्ठा super_block *sb = i->i_sb;
	काष्ठा hpfs_inode_info *hpfs_inode = hpfs_i(i);
	व्योम *ea;
	पूर्णांक ea_size;

	अगर (!(fnode = hpfs_map_fnode(sb, i->i_ino, &bh))) अणु
		/*i->i_mode |= S_IFREG;
		i->i_mode &= ~0111;
		i->i_op = &hpfs_file_iops;
		i->i_fop = &hpfs_file_ops;
		clear_nlink(i);*/
		make_bad_inode(i);
		वापस;
	पूर्ण
	अगर (hpfs_sb(i->i_sb)->sb_eas) अणु
		अगर ((ea = hpfs_get_ea(i->i_sb, fnode, "UID", &ea_size))) अणु
			अगर (ea_size == 2) अणु
				i_uid_ग_लिखो(i, le16_to_cpu(*(__le16*)ea));
				hpfs_inode->i_ea_uid = 1;
			पूर्ण
			kमुक्त(ea);
		पूर्ण
		अगर ((ea = hpfs_get_ea(i->i_sb, fnode, "GID", &ea_size))) अणु
			अगर (ea_size == 2) अणु
				i_gid_ग_लिखो(i, le16_to_cpu(*(__le16*)ea));
				hpfs_inode->i_ea_gid = 1;
			पूर्ण
			kमुक्त(ea);
		पूर्ण
		अगर ((ea = hpfs_get_ea(i->i_sb, fnode, "SYMLINK", &ea_size))) अणु
			kमुक्त(ea);
			i->i_mode = S_IFLNK | 0777;
			i->i_op = &page_symlink_inode_operations;
			inode_nohighmem(i);
			i->i_data.a_ops = &hpfs_symlink_aops;
			set_nlink(i, 1);
			i->i_size = ea_size;
			i->i_blocks = 1;
			brअन्यथा(bh);
			वापस;
		पूर्ण
		अगर ((ea = hpfs_get_ea(i->i_sb, fnode, "MODE", &ea_size))) अणु
			पूर्णांक rdev = 0;
			umode_t mode = hpfs_sb(sb)->sb_mode;
			अगर (ea_size == 2) अणु
				mode = le16_to_cpu(*(__le16*)ea);
				hpfs_inode->i_ea_mode = 1;
			पूर्ण
			kमुक्त(ea);
			i->i_mode = mode;
			अगर (S_ISBLK(mode) || S_ISCHR(mode)) अणु
				अगर ((ea = hpfs_get_ea(i->i_sb, fnode, "DEV", &ea_size))) अणु
					अगर (ea_size == 4)
						rdev = le32_to_cpu(*(__le32*)ea);
					kमुक्त(ea);
				पूर्ण
			पूर्ण
			अगर (S_ISBLK(mode) || S_ISCHR(mode) || S_ISFIFO(mode) || S_ISSOCK(mode)) अणु
				brअन्यथा(bh);
				set_nlink(i, 1);
				i->i_size = 0;
				i->i_blocks = 1;
				init_special_inode(i, mode,
					new_decode_dev(rdev));
				वापस;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (fnode_is_dir(fnode)) अणु
		पूर्णांक n_dnodes, n_subdirs;
		i->i_mode |= S_IFसूची;
		i->i_op = &hpfs_dir_iops;
		i->i_fop = &hpfs_dir_ops;
		hpfs_inode->i_parent_dir = le32_to_cpu(fnode->up);
		hpfs_inode->i_dno = le32_to_cpu(fnode->u.बाह्यal[0].disk_secno);
		अगर (hpfs_sb(sb)->sb_chk >= 2) अणु
			काष्ठा buffer_head *bh0;
			अगर (hpfs_map_fnode(sb, hpfs_inode->i_parent_dir, &bh0)) brअन्यथा(bh0);
		पूर्ण
		n_dnodes = 0; n_subdirs = 0;
		hpfs_count_dnodes(i->i_sb, hpfs_inode->i_dno, &n_dnodes, &n_subdirs, शून्य);
		i->i_blocks = 4 * n_dnodes;
		i->i_size = 2048 * n_dnodes;
		set_nlink(i, 2 + n_subdirs);
	पूर्ण अन्यथा अणु
		i->i_mode |= S_IFREG;
		अगर (!hpfs_inode->i_ea_mode) i->i_mode &= ~0111;
		i->i_op = &hpfs_file_iops;
		i->i_fop = &hpfs_file_ops;
		set_nlink(i, 1);
		i->i_size = le32_to_cpu(fnode->file_size);
		i->i_blocks = ((i->i_size + 511) >> 9) + 1;
		i->i_data.a_ops = &hpfs_aops;
		hpfs_i(i)->mmu_निजी = i->i_size;
	पूर्ण
	brअन्यथा(bh);
पूर्ण

अटल व्योम hpfs_ग_लिखो_inode_ea(काष्ठा inode *i, काष्ठा fnode *fnode)
अणु
	काष्ठा hpfs_inode_info *hpfs_inode = hpfs_i(i);
	/*अगर (le32_to_cpu(fnode->acl_size_l) || le16_to_cpu(fnode->acl_size_s)) अणु
		   Some unknown काष्ठाures like ACL may be in fnode,
		   we'd better not overग_लिखो them
		hpfs_error(i->i_sb, "fnode %08x has some unknown HPFS386 structures", i->i_ino);
	पूर्ण अन्यथा*/ अगर (hpfs_sb(i->i_sb)->sb_eas >= 2) अणु
		__le32 ea;
		अगर (!uid_eq(i->i_uid, hpfs_sb(i->i_sb)->sb_uid) || hpfs_inode->i_ea_uid) अणु
			ea = cpu_to_le32(i_uid_पढ़ो(i));
			hpfs_set_ea(i, fnode, "UID", (अक्षर*)&ea, 2);
			hpfs_inode->i_ea_uid = 1;
		पूर्ण
		अगर (!gid_eq(i->i_gid, hpfs_sb(i->i_sb)->sb_gid) || hpfs_inode->i_ea_gid) अणु
			ea = cpu_to_le32(i_gid_पढ़ो(i));
			hpfs_set_ea(i, fnode, "GID", (अक्षर *)&ea, 2);
			hpfs_inode->i_ea_gid = 1;
		पूर्ण
		अगर (!S_ISLNK(i->i_mode))
			अगर ((i->i_mode != ((hpfs_sb(i->i_sb)->sb_mode & ~(S_ISसूची(i->i_mode) ? 0 : 0111))
			  | (S_ISसूची(i->i_mode) ? S_IFसूची : S_IFREG))
			  && i->i_mode != ((hpfs_sb(i->i_sb)->sb_mode & ~(S_ISसूची(i->i_mode) ? 0222 : 0333))
			  | (S_ISसूची(i->i_mode) ? S_IFसूची : S_IFREG))) || hpfs_inode->i_ea_mode) अणु
				ea = cpu_to_le32(i->i_mode);
				/* sick, but legal */
				hpfs_set_ea(i, fnode, "MODE", (अक्षर *)&ea, 2);
				hpfs_inode->i_ea_mode = 1;
			पूर्ण
		अगर (S_ISBLK(i->i_mode) || S_ISCHR(i->i_mode)) अणु
			ea = cpu_to_le32(new_encode_dev(i->i_rdev));
			hpfs_set_ea(i, fnode, "DEV", (अक्षर *)&ea, 4);
		पूर्ण
	पूर्ण
पूर्ण

व्योम hpfs_ग_लिखो_inode(काष्ठा inode *i)
अणु
	काष्ठा hpfs_inode_info *hpfs_inode = hpfs_i(i);
	काष्ठा inode *parent;
	अगर (i->i_ino == hpfs_sb(i->i_sb)->sb_root) वापस;
	अगर (hpfs_inode->i_rddir_off && !atomic_पढ़ो(&i->i_count)) अणु
		अगर (*hpfs_inode->i_rddir_off)
			pr_err("write_inode: some position still there\n");
		kमुक्त(hpfs_inode->i_rddir_off);
		hpfs_inode->i_rddir_off = शून्य;
	पूर्ण
	अगर (!i->i_nlink) अणु
		वापस;
	पूर्ण
	parent = iget_locked(i->i_sb, hpfs_inode->i_parent_dir);
	अगर (parent) अणु
		hpfs_inode->i_dirty = 0;
		अगर (parent->i_state & I_NEW) अणु
			hpfs_init_inode(parent);
			hpfs_पढ़ो_inode(parent);
			unlock_new_inode(parent);
		पूर्ण
		hpfs_ग_लिखो_inode_nolock(i);
		iput(parent);
	पूर्ण
पूर्ण

व्योम hpfs_ग_लिखो_inode_nolock(काष्ठा inode *i)
अणु
	काष्ठा hpfs_inode_info *hpfs_inode = hpfs_i(i);
	काष्ठा buffer_head *bh;
	काष्ठा fnode *fnode;
	काष्ठा quad_buffer_head qbh;
	काष्ठा hpfs_dirent *de;
	अगर (i->i_ino == hpfs_sb(i->i_sb)->sb_root) वापस;
	अगर (!(fnode = hpfs_map_fnode(i->i_sb, i->i_ino, &bh))) वापस;
	अगर (i->i_ino != hpfs_sb(i->i_sb)->sb_root && i->i_nlink) अणु
		अगर (!(de = map_fnode_dirent(i->i_sb, i->i_ino, fnode, &qbh))) अणु
			brअन्यथा(bh);
			वापस;
		पूर्ण
	पूर्ण अन्यथा de = शून्य;
	अगर (S_ISREG(i->i_mode)) अणु
		fnode->file_size = cpu_to_le32(i->i_size);
		अगर (de) de->file_size = cpu_to_le32(i->i_size);
	पूर्ण अन्यथा अगर (S_ISसूची(i->i_mode)) अणु
		fnode->file_size = cpu_to_le32(0);
		अगर (de) de->file_size = cpu_to_le32(0);
	पूर्ण
	hpfs_ग_लिखो_inode_ea(i, fnode);
	अगर (de) अणु
		de->ग_लिखो_date = cpu_to_le32(gmt_to_local(i->i_sb, i->i_mसमय.tv_sec));
		de->पढ़ो_date = cpu_to_le32(gmt_to_local(i->i_sb, i->i_aसमय.tv_sec));
		de->creation_date = cpu_to_le32(gmt_to_local(i->i_sb, i->i_स_समय.tv_sec));
		de->पढ़ो_only = !(i->i_mode & 0222);
		de->ea_size = cpu_to_le32(hpfs_inode->i_ea_size);
		hpfs_mark_4buffers_dirty(&qbh);
		hpfs_brअन्यथा4(&qbh);
	पूर्ण
	अगर (S_ISसूची(i->i_mode)) अणु
		अगर ((de = map_dirent(i, hpfs_inode->i_dno, "\001\001", 2, शून्य, &qbh))) अणु
			de->ग_लिखो_date = cpu_to_le32(gmt_to_local(i->i_sb, i->i_mसमय.tv_sec));
			de->पढ़ो_date = cpu_to_le32(gmt_to_local(i->i_sb, i->i_aसमय.tv_sec));
			de->creation_date = cpu_to_le32(gmt_to_local(i->i_sb, i->i_स_समय.tv_sec));
			de->पढ़ो_only = !(i->i_mode & 0222);
			de->ea_size = cpu_to_le32(/*hpfs_inode->i_ea_size*/0);
			de->file_size = cpu_to_le32(0);
			hpfs_mark_4buffers_dirty(&qbh);
			hpfs_brअन्यथा4(&qbh);
		पूर्ण अन्यथा
			hpfs_error(i->i_sb,
				"directory %08lx doesn't have '.' entry",
				(अचिन्हित दीर्घ)i->i_ino);
	पूर्ण
	mark_buffer_dirty(bh);
	brअन्यथा(bh);
पूर्ण

पूर्णांक hpfs_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		 काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	पूर्णांक error = -EINVAL;

	hpfs_lock(inode->i_sb);
	अगर (inode->i_ino == hpfs_sb(inode->i_sb)->sb_root)
		जाओ out_unlock;
	अगर ((attr->ia_valid & ATTR_UID) &&
	    from_kuid(&init_user_ns, attr->ia_uid) >= 0x10000)
		जाओ out_unlock;
	अगर ((attr->ia_valid & ATTR_GID) &&
	    from_kgid(&init_user_ns, attr->ia_gid) >= 0x10000)
		जाओ out_unlock;
	अगर ((attr->ia_valid & ATTR_SIZE) && attr->ia_size > inode->i_size)
		जाओ out_unlock;

	error = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (error)
		जाओ out_unlock;

	अगर ((attr->ia_valid & ATTR_SIZE) &&
	    attr->ia_size != i_size_पढ़ो(inode)) अणु
		error = inode_newsize_ok(inode, attr->ia_size);
		अगर (error)
			जाओ out_unlock;

		truncate_setsize(inode, attr->ia_size);
		hpfs_truncate(inode);
	पूर्ण

	setattr_copy(&init_user_ns, inode, attr);

	hpfs_ग_लिखो_inode(inode);

 out_unlock:
	hpfs_unlock(inode->i_sb);
	वापस error;
पूर्ण

व्योम hpfs_ग_लिखो_अगर_changed(काष्ठा inode *inode)
अणु
	काष्ठा hpfs_inode_info *hpfs_inode = hpfs_i(inode);

	अगर (hpfs_inode->i_dirty)
		hpfs_ग_लिखो_inode(inode);
पूर्ण

व्योम hpfs_evict_inode(काष्ठा inode *inode)
अणु
	truncate_inode_pages_final(&inode->i_data);
	clear_inode(inode);
	अगर (!inode->i_nlink) अणु
		hpfs_lock(inode->i_sb);
		hpfs_हटाओ_fnode(inode->i_sb, inode->i_ino);
		hpfs_unlock(inode->i_sb);
	पूर्ण
पूर्ण
