<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2011 Red Hat, Inc.  All rights reserved.
 */

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/namei.h>
#समावेश <linux/mm.h>
#समावेश <linux/cred.h>
#समावेश <linux/xattr.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/crc32.h>
#समावेश <linux/iomap.h>
#समावेश <linux/security.h>
#समावेश <linux/fiemap.h>
#समावेश <linux/uaccess.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "acl.h"
#समावेश "bmap.h"
#समावेश "dir.h"
#समावेश "xattr.h"
#समावेश "glock.h"
#समावेश "inode.h"
#समावेश "meta_io.h"
#समावेश "quota.h"
#समावेश "rgrp.h"
#समावेश "trans.h"
#समावेश "util.h"
#समावेश "super.h"
#समावेश "glops.h"

अटल स्थिर काष्ठा inode_operations gfs2_file_iops;
अटल स्थिर काष्ठा inode_operations gfs2_dir_iops;
अटल स्थिर काष्ठा inode_operations gfs2_symlink_iops;

अटल पूर्णांक iget_test(काष्ठा inode *inode, व्योम *opaque)
अणु
	u64 no_addr = *(u64 *)opaque;

	वापस GFS2_I(inode)->i_no_addr == no_addr;
पूर्ण

अटल पूर्णांक iget_set(काष्ठा inode *inode, व्योम *opaque)
अणु
	u64 no_addr = *(u64 *)opaque;

	GFS2_I(inode)->i_no_addr = no_addr;
	inode->i_ino = no_addr;
	वापस 0;
पूर्ण

अटल काष्ठा inode *gfs2_iget(काष्ठा super_block *sb, u64 no_addr)
अणु
	काष्ठा inode *inode;

repeat:
	inode = iget5_locked(sb, no_addr, iget_test, iget_set, &no_addr);
	अगर (!inode)
		वापस inode;
	अगर (is_bad_inode(inode)) अणु
		iput(inode);
		जाओ repeat;
	पूर्ण
	वापस inode;
पूर्ण

/**
 * gfs2_set_iop - Sets inode operations
 * @inode: The inode with correct i_mode filled in
 *
 * GFS2 lookup code fills in vfs inode contents based on info obtained
 * from directory entry inside gfs2_inode_lookup().
 */

अटल व्योम gfs2_set_iop(काष्ठा inode *inode)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	umode_t mode = inode->i_mode;

	अगर (S_ISREG(mode)) अणु
		inode->i_op = &gfs2_file_iops;
		अगर (gfs2_localflocks(sdp))
			inode->i_fop = &gfs2_file_fops_nolock;
		अन्यथा
			inode->i_fop = &gfs2_file_fops;
	पूर्ण अन्यथा अगर (S_ISसूची(mode)) अणु
		inode->i_op = &gfs2_dir_iops;
		अगर (gfs2_localflocks(sdp))
			inode->i_fop = &gfs2_dir_fops_nolock;
		अन्यथा
			inode->i_fop = &gfs2_dir_fops;
	पूर्ण अन्यथा अगर (S_ISLNK(mode)) अणु
		inode->i_op = &gfs2_symlink_iops;
	पूर्ण अन्यथा अणु
		inode->i_op = &gfs2_file_iops;
		init_special_inode(inode, inode->i_mode, inode->i_rdev);
	पूर्ण
पूर्ण

/**
 * gfs2_inode_lookup - Lookup an inode
 * @sb: The super block
 * @type: The type of the inode
 * @no_addr: The inode number
 * @no_क्रमmal_ino: The inode generation number
 * @blktype: Requested block type (GFS2_BLKST_DINODE or GFS2_BLKST_UNLINKED;
 *           GFS2_BLKST_FREE to indicate not to verअगरy)
 *
 * If @type is DT_UNKNOWN, the inode type is fetched from disk.
 *
 * If @blktype is anything other than GFS2_BLKST_FREE (which is used as a
 * placeholder because it करोesn't otherwise make sense), the on-disk block type
 * is verअगरied to be @blktype.
 *
 * When @no_क्रमmal_ino is non-zero, this function will वापस ERR_PTR(-ESTALE)
 * अगर it detects that @no_क्रमmal_ino करोesn't match the actual inode generation
 * number.  However, it करोesn't always know unless @type is DT_UNKNOWN.
 *
 * Returns: A VFS inode, or an error
 */

काष्ठा inode *gfs2_inode_lookup(काष्ठा super_block *sb, अचिन्हित पूर्णांक type,
				u64 no_addr, u64 no_क्रमmal_ino,
				अचिन्हित पूर्णांक blktype)
अणु
	काष्ठा inode *inode;
	काष्ठा gfs2_inode *ip;
	काष्ठा gfs2_glock *io_gl = शून्य;
	काष्ठा gfs2_holder i_gh;
	पूर्णांक error;

	gfs2_holder_mark_uninitialized(&i_gh);
	inode = gfs2_iget(sb, no_addr);
	अगर (!inode)
		वापस ERR_PTR(-ENOMEM);

	ip = GFS2_I(inode);

	अगर (inode->i_state & I_NEW) अणु
		काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);

		error = gfs2_glock_get(sdp, no_addr, &gfs2_inode_glops, CREATE, &ip->i_gl);
		अगर (unlikely(error))
			जाओ fail;
		flush_delayed_work(&ip->i_gl->gl_work);

		error = gfs2_glock_get(sdp, no_addr, &gfs2_iखोलो_glops, CREATE, &io_gl);
		अगर (unlikely(error))
			जाओ fail;
		अगर (blktype != GFS2_BLKST_UNLINKED)
			gfs2_cancel_delete_work(io_gl);

		अगर (type == DT_UNKNOWN || blktype != GFS2_BLKST_FREE) अणु
			/*
			 * The GL_SKIP flag indicates to skip पढ़ोing the inode
			 * block.  We पढ़ो the inode with gfs2_inode_refresh
			 * after possibly checking the block type.
			 */
			error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE,
						   GL_SKIP, &i_gh);
			अगर (error)
				जाओ fail;

			error = -ESTALE;
			अगर (no_क्रमmal_ino &&
			    gfs2_inode_alपढ़ोy_deleted(ip->i_gl, no_क्रमmal_ino))
				जाओ fail;

			अगर (blktype != GFS2_BLKST_FREE) अणु
				error = gfs2_check_blk_type(sdp, no_addr,
							    blktype);
				अगर (error)
					जाओ fail;
			पूर्ण
		पूर्ण

		glock_set_object(ip->i_gl, ip);
		set_bit(GIF_INVALID, &ip->i_flags);
		error = gfs2_glock_nq_init(io_gl, LM_ST_SHARED, GL_EXACT, &ip->i_iखोलो_gh);
		अगर (unlikely(error))
			जाओ fail;
		glock_set_object(ip->i_iखोलो_gh.gh_gl, ip);
		gfs2_glock_put(io_gl);
		io_gl = शून्य;

		/* Lowest possible बारtamp; will be overwritten in gfs2_dinode_in. */
		inode->i_aसमय.tv_sec = 1LL << (8 * माप(inode->i_aसमय.tv_sec) - 1);
		inode->i_aसमय.tv_nsec = 0;

		अगर (type == DT_UNKNOWN) अणु
			/* Inode glock must be locked alपढ़ोy */
			error = gfs2_inode_refresh(GFS2_I(inode));
			अगर (error)
				जाओ fail;
		पूर्ण अन्यथा अणु
			ip->i_no_क्रमmal_ino = no_क्रमmal_ino;
			inode->i_mode = DT2IF(type);
		पूर्ण

		अगर (gfs2_holder_initialized(&i_gh))
			gfs2_glock_dq_uninit(&i_gh);

		gfs2_set_iop(inode);
	पूर्ण

	अगर (no_क्रमmal_ino && ip->i_no_क्रमmal_ino &&
	    no_क्रमmal_ino != ip->i_no_क्रमmal_ino) अणु
		error = -ESTALE;
		अगर (inode->i_state & I_NEW)
			जाओ fail;
		iput(inode);
		वापस ERR_PTR(error);
	पूर्ण

	अगर (inode->i_state & I_NEW)
		unlock_new_inode(inode);

	वापस inode;

fail:
	अगर (io_gl)
		gfs2_glock_put(io_gl);
	अगर (gfs2_holder_initialized(&i_gh))
		gfs2_glock_dq_uninit(&i_gh);
	iget_failed(inode);
	वापस ERR_PTR(error);
पूर्ण

/**
 * gfs2_lookup_by_inum - look up an inode by inode number
 * @sdp: The super block
 * @no_addr: The inode number
 * @no_क्रमmal_ino: The inode generation number (0 क्रम any)
 * @blktype: Requested block type (see gfs2_inode_lookup)
 */
काष्ठा inode *gfs2_lookup_by_inum(काष्ठा gfs2_sbd *sdp, u64 no_addr,
				  u64 no_क्रमmal_ino, अचिन्हित पूर्णांक blktype)
अणु
	काष्ठा super_block *sb = sdp->sd_vfs;
	काष्ठा inode *inode;
	पूर्णांक error;

	inode = gfs2_inode_lookup(sb, DT_UNKNOWN, no_addr, no_क्रमmal_ino,
				  blktype);
	अगर (IS_ERR(inode))
		वापस inode;

	अगर (no_क्रमmal_ino) अणु
		error = -EIO;
		अगर (GFS2_I(inode)->i_diskflags & GFS2_DIF_SYSTEM)
			जाओ fail_iput;
	पूर्ण
	वापस inode;

fail_iput:
	iput(inode);
	वापस ERR_PTR(error);
पूर्ण


काष्ठा inode *gfs2_lookup_simple(काष्ठा inode *dip, स्थिर अक्षर *name)
अणु
	काष्ठा qstr qstr;
	काष्ठा inode *inode;
	gfs2_str2qstr(&qstr, name);
	inode = gfs2_lookupi(dip, &qstr, 1);
	/* gfs2_lookupi has inconsistent callers: vfs
	 * related routines expect शून्य क्रम no entry found,
	 * gfs2_lookup_simple callers expect ENOENT
	 * and करो not check क्रम शून्य.
	 */
	अगर (inode == शून्य)
		वापस ERR_PTR(-ENOENT);
	अन्यथा
		वापस inode;
पूर्ण


/**
 * gfs2_lookupi - Look up a filename in a directory and वापस its inode
 * @dir: The inode of the directory containing the inode to look-up
 * @name: The name of the inode to look क्रम
 * @is_root: If 1, ignore the caller's permissions
 *
 * This can be called via the VFS filldir function when NFS is करोing
 * a सूची_पढ़ोplus and the inode which its पूर्णांकending to stat isn't
 * alपढ़ोy in cache. In this हाल we must not take the directory glock
 * again, since the सूची_पढ़ो call will have alपढ़ोy taken that lock.
 *
 * Returns: त्रुटि_सं
 */

काष्ठा inode *gfs2_lookupi(काष्ठा inode *dir, स्थिर काष्ठा qstr *name,
			   पूर्णांक is_root)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा gfs2_inode *dip = GFS2_I(dir);
	काष्ठा gfs2_holder d_gh;
	पूर्णांक error = 0;
	काष्ठा inode *inode = शून्य;

	gfs2_holder_mark_uninitialized(&d_gh);
	अगर (!name->len || name->len > GFS2_FNAMESIZE)
		वापस ERR_PTR(-ENAMETOOLONG);

	अगर ((name->len == 1 && स_भेद(name->name, ".", 1) == 0) ||
	    (name->len == 2 && स_भेद(name->name, "..", 2) == 0 &&
	     dir == d_inode(sb->s_root))) अणु
		igrab(dir);
		वापस dir;
	पूर्ण

	अगर (gfs2_glock_is_locked_by_me(dip->i_gl) == शून्य) अणु
		error = gfs2_glock_nq_init(dip->i_gl, LM_ST_SHARED, 0, &d_gh);
		अगर (error)
			वापस ERR_PTR(error);
	पूर्ण

	अगर (!is_root) अणु
		error = gfs2_permission(&init_user_ns, dir, MAY_EXEC);
		अगर (error)
			जाओ out;
	पूर्ण

	inode = gfs2_dir_search(dir, name, false);
	अगर (IS_ERR(inode))
		error = PTR_ERR(inode);
out:
	अगर (gfs2_holder_initialized(&d_gh))
		gfs2_glock_dq_uninit(&d_gh);
	अगर (error == -ENOENT)
		वापस शून्य;
	वापस inode ? inode : ERR_PTR(error);
पूर्ण

/**
 * create_ok - OK to create a new on-disk inode here?
 * @dip:  Directory in which dinode is to be created
 * @name:  Name of new dinode
 * @mode:
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक create_ok(काष्ठा gfs2_inode *dip, स्थिर काष्ठा qstr *name,
		     umode_t mode)
अणु
	पूर्णांक error;

	error = gfs2_permission(&init_user_ns, &dip->i_inode,
				MAY_WRITE | MAY_EXEC);
	अगर (error)
		वापस error;

	/*  Don't create entries in an unlinked directory  */
	अगर (!dip->i_inode.i_nlink)
		वापस -ENOENT;

	अगर (dip->i_entries == (u32)-1)
		वापस -EFBIG;
	अगर (S_ISसूची(mode) && dip->i_inode.i_nlink == (u32)-1)
		वापस -EMLINK;

	वापस 0;
पूर्ण

अटल व्योम munge_mode_uid_gid(स्थिर काष्ठा gfs2_inode *dip,
			       काष्ठा inode *inode)
अणु
	अगर (GFS2_SB(&dip->i_inode)->sd_args.ar_suiddir &&
	    (dip->i_inode.i_mode & S_ISUID) &&
	    !uid_eq(dip->i_inode.i_uid, GLOBAL_ROOT_UID)) अणु
		अगर (S_ISसूची(inode->i_mode))
			inode->i_mode |= S_ISUID;
		अन्यथा अगर (!uid_eq(dip->i_inode.i_uid, current_fsuid()))
			inode->i_mode &= ~07111;
		inode->i_uid = dip->i_inode.i_uid;
	पूर्ण अन्यथा
		inode->i_uid = current_fsuid();

	अगर (dip->i_inode.i_mode & S_ISGID) अणु
		अगर (S_ISसूची(inode->i_mode))
			inode->i_mode |= S_ISGID;
		inode->i_gid = dip->i_inode.i_gid;
	पूर्ण अन्यथा
		inode->i_gid = current_fsgid();
पूर्ण

अटल पूर्णांक alloc_dinode(काष्ठा gfs2_inode *ip, u32 flags, अचिन्हित *dblocks)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा gfs2_alloc_parms ap = अणु .target = *dblocks, .aflags = flags, पूर्ण;
	पूर्णांक error;

	error = gfs2_quota_lock_check(ip, &ap);
	अगर (error)
		जाओ out;

	error = gfs2_inplace_reserve(ip, &ap);
	अगर (error)
		जाओ out_quota;

	error = gfs2_trans_begin(sdp, (*dblocks * RES_RG_BIT) + RES_STATFS + RES_QUOTA, 0);
	अगर (error)
		जाओ out_ipreserv;

	error = gfs2_alloc_blocks(ip, &ip->i_no_addr, dblocks, 1, &ip->i_generation);
	ip->i_no_क्रमmal_ino = ip->i_generation;
	ip->i_inode.i_ino = ip->i_no_addr;
	ip->i_goal = ip->i_no_addr;

	gfs2_trans_end(sdp);

out_ipreserv:
	gfs2_inplace_release(ip);
out_quota:
	gfs2_quota_unlock(ip);
out:
	वापस error;
पूर्ण

अटल व्योम gfs2_init_dir(काष्ठा buffer_head *dibh,
			  स्थिर काष्ठा gfs2_inode *parent)
अणु
	काष्ठा gfs2_dinode *di = (काष्ठा gfs2_dinode *)dibh->b_data;
	काष्ठा gfs2_dirent *dent = (काष्ठा gfs2_dirent *)(di+1);

	gfs2_qstr2dirent(&gfs2_qकरोt, GFS2_सूचीENT_SIZE(gfs2_qकरोt.len), dent);
	dent->de_inum = di->di_num; /* alपढ़ोy GFS2 endian */
	dent->de_type = cpu_to_be16(DT_सूची);

	dent = (काष्ठा gfs2_dirent *)((अक्षर*)dent + GFS2_सूचीENT_SIZE(1));
	gfs2_qstr2dirent(&gfs2_qकरोtकरोt, dibh->b_size - GFS2_सूचीENT_SIZE(1) - माप(काष्ठा gfs2_dinode), dent);
	gfs2_inum_out(parent, dent);
	dent->de_type = cpu_to_be16(DT_सूची);
	
पूर्ण

/**
 * gfs2_init_xattr - Initialise an xattr block क्रम a new inode
 * @ip: The inode in question
 *
 * This sets up an empty xattr block क्रम a new inode, पढ़ोy to
 * take any ACLs, LSM xattrs, etc.
 */

अटल व्योम gfs2_init_xattr(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा buffer_head *bh;
	काष्ठा gfs2_ea_header *ea;

	bh = gfs2_meta_new(ip->i_gl, ip->i_eattr);
	gfs2_trans_add_meta(ip->i_gl, bh);
	gfs2_metatype_set(bh, GFS2_METATYPE_EA, GFS2_FORMAT_EA);
	gfs2_buffer_clear_tail(bh, माप(काष्ठा gfs2_meta_header));

	ea = GFS2_EA_BH2FIRST(bh);
	ea->ea_rec_len = cpu_to_be32(sdp->sd_jbsize);
	ea->ea_type = GFS2_EATYPE_UNUSED;
	ea->ea_flags = GFS2_EAFLAG_LAST;

	brअन्यथा(bh);
पूर्ण

/**
 * init_dinode - Fill in a new dinode काष्ठाure
 * @dip: The directory this inode is being created in
 * @ip: The inode
 * @symname: The symlink destination (अगर a symlink)
 *
 */

अटल व्योम init_dinode(काष्ठा gfs2_inode *dip, काष्ठा gfs2_inode *ip,
			स्थिर अक्षर *symname)
अणु
	काष्ठा gfs2_dinode *di;
	काष्ठा buffer_head *dibh;

	dibh = gfs2_meta_new(ip->i_gl, ip->i_no_addr);
	gfs2_trans_add_meta(ip->i_gl, dibh);
	di = (काष्ठा gfs2_dinode *)dibh->b_data;
	gfs2_dinode_out(ip, di);

	di->di_major = cpu_to_be32(imajor(&ip->i_inode));
	di->di_minor = cpu_to_be32(iminor(&ip->i_inode));
	di->__pad1 = 0;
	di->__pad2 = 0;
	di->__pad3 = 0;
	स_रखो(&di->__pad4, 0, माप(di->__pad4));
	स_रखो(&di->di_reserved, 0, माप(di->di_reserved));
	gfs2_buffer_clear_tail(dibh, माप(काष्ठा gfs2_dinode));

	चयन(ip->i_inode.i_mode & S_IFMT) अणु
	हाल S_IFसूची:
		gfs2_init_dir(dibh, dip);
		अवरोध;
	हाल S_IFLNK:
		स_नकल(dibh->b_data + माप(काष्ठा gfs2_dinode), symname, ip->i_inode.i_size);
		अवरोध;
	पूर्ण

	set_buffer_uptodate(dibh);
	brअन्यथा(dibh);
पूर्ण

/**
 * gfs2_trans_da_blks - Calculate number of blocks to link inode
 * @dip: The directory we are linking पूर्णांकo
 * @da: The dir add inक्रमmation
 * @nr_inodes: The number of inodes involved
 *
 * This calculate the number of blocks we need to reserve in a
 * transaction to link @nr_inodes पूर्णांकo a directory. In most हालs
 * @nr_inodes will be 2 (the directory plus the inode being linked in)
 * but in हाल of नाम, 4 may be required.
 *
 * Returns: Number of blocks
 */

अटल अचिन्हित gfs2_trans_da_blks(स्थिर काष्ठा gfs2_inode *dip,
				   स्थिर काष्ठा gfs2_diradd *da,
				   अचिन्हित nr_inodes)
अणु
	वापस da->nr_blocks + gfs2_rg_blocks(dip, da->nr_blocks) +
	       (nr_inodes * RES_DINODE) + RES_QUOTA + RES_STATFS;
पूर्ण

अटल पूर्णांक link_dinode(काष्ठा gfs2_inode *dip, स्थिर काष्ठा qstr *name,
		       काष्ठा gfs2_inode *ip, काष्ठा gfs2_diradd *da)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&dip->i_inode);
	काष्ठा gfs2_alloc_parms ap = अणु .target = da->nr_blocks, पूर्ण;
	पूर्णांक error;

	अगर (da->nr_blocks) अणु
		error = gfs2_quota_lock_check(dip, &ap);
		अगर (error)
			जाओ fail_quota_locks;

		error = gfs2_inplace_reserve(dip, &ap);
		अगर (error)
			जाओ fail_quota_locks;

		error = gfs2_trans_begin(sdp, gfs2_trans_da_blks(dip, da, 2), 0);
		अगर (error)
			जाओ fail_ipreserv;
	पूर्ण अन्यथा अणु
		error = gfs2_trans_begin(sdp, RES_LEAF + 2 * RES_DINODE, 0);
		अगर (error)
			जाओ fail_quota_locks;
	पूर्ण

	error = gfs2_dir_add(&dip->i_inode, name, ip, da);

	gfs2_trans_end(sdp);
fail_ipreserv:
	gfs2_inplace_release(dip);
fail_quota_locks:
	gfs2_quota_unlock(dip);
	वापस error;
पूर्ण

अटल पूर्णांक gfs2_initxattrs(काष्ठा inode *inode, स्थिर काष्ठा xattr *xattr_array,
		    व्योम *fs_info)
अणु
	स्थिर काष्ठा xattr *xattr;
	पूर्णांक err = 0;

	क्रम (xattr = xattr_array; xattr->name != शून्य; xattr++) अणु
		err = __gfs2_xattr_set(inode, xattr->name, xattr->value,
				       xattr->value_len, 0,
				       GFS2_EATYPE_SECURITY);
		अगर (err < 0)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

/**
 * gfs2_create_inode - Create a new inode
 * @dir: The parent directory
 * @dentry: The new dentry
 * @file: If non-शून्य, the file which is being खोलोed
 * @mode: The permissions on the new inode
 * @dev: For device nodes, this is the device number
 * @symname: For symlinks, this is the link destination
 * @size: The initial size of the inode (ignored क्रम directories)
 * @excl: Force fail अगर inode exists
 *
 * Returns: 0 on success, or error code
 */

अटल पूर्णांक gfs2_create_inode(काष्ठा inode *dir, काष्ठा dentry *dentry,
			     काष्ठा file *file,
			     umode_t mode, dev_t dev, स्थिर अक्षर *symname,
			     अचिन्हित पूर्णांक size, पूर्णांक excl)
अणु
	स्थिर काष्ठा qstr *name = &dentry->d_name;
	काष्ठा posix_acl *शेष_acl, *acl;
	काष्ठा gfs2_holder ghs[2];
	काष्ठा inode *inode = शून्य;
	काष्ठा gfs2_inode *dip = GFS2_I(dir), *ip;
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&dip->i_inode);
	काष्ठा gfs2_glock *io_gl;
	पूर्णांक error, मुक्त_vfs_inode = 1;
	u32 aflags = 0;
	अचिन्हित blocks = 1;
	काष्ठा gfs2_diradd da = अणु .bh = शून्य, .save_loc = 1, पूर्ण;

	अगर (!name->len || name->len > GFS2_FNAMESIZE)
		वापस -ENAMETOOLONG;

	error = gfs2_qa_get(dip);
	अगर (error)
		वापस error;

	error = gfs2_rindex_update(sdp);
	अगर (error)
		जाओ fail;

	error = gfs2_glock_nq_init(dip->i_gl, LM_ST_EXCLUSIVE, 0, ghs);
	अगर (error)
		जाओ fail;
	gfs2_holder_mark_uninitialized(ghs + 1);

	error = create_ok(dip, name, mode);
	अगर (error)
		जाओ fail_gunlock;

	inode = gfs2_dir_search(dir, &dentry->d_name, !S_ISREG(mode) || excl);
	error = PTR_ERR(inode);
	अगर (!IS_ERR(inode)) अणु
		अगर (S_ISसूची(inode->i_mode)) अणु
			iput(inode);
			inode = ERR_PTR(-EISसूची);
			जाओ fail_gunlock;
		पूर्ण
		d_instantiate(dentry, inode);
		error = 0;
		अगर (file) अणु
			अगर (S_ISREG(inode->i_mode))
				error = finish_खोलो(file, dentry, gfs2_खोलो_common);
			अन्यथा
				error = finish_no_खोलो(file, शून्य);
		पूर्ण
		gfs2_glock_dq_uninit(ghs);
		जाओ fail;
	पूर्ण अन्यथा अगर (error != -ENOENT) अणु
		जाओ fail_gunlock;
	पूर्ण

	error = gfs2_diradd_alloc_required(dir, name, &da);
	अगर (error < 0)
		जाओ fail_gunlock;

	inode = new_inode(sdp->sd_vfs);
	error = -ENOMEM;
	अगर (!inode)
		जाओ fail_gunlock;

	error = posix_acl_create(dir, &mode, &शेष_acl, &acl);
	अगर (error)
		जाओ fail_gunlock;

	ip = GFS2_I(inode);
	error = gfs2_qa_get(ip);
	अगर (error)
		जाओ fail_मुक्त_acls;

	inode->i_mode = mode;
	set_nlink(inode, S_ISसूची(mode) ? 2 : 1);
	inode->i_rdev = dev;
	inode->i_size = size;
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	munge_mode_uid_gid(dip, inode);
	check_and_update_goal(dip);
	ip->i_goal = dip->i_goal;
	ip->i_diskflags = 0;
	ip->i_eattr = 0;
	ip->i_height = 0;
	ip->i_depth = 0;
	ip->i_entries = 0;
	ip->i_no_addr = 0; /* Temporarily zero until real addr is asचिन्हित */

	चयन(mode & S_IFMT) अणु
	हाल S_IFREG:
		अगर ((dip->i_diskflags & GFS2_DIF_INHERIT_JDATA) ||
		    gfs2_tune_get(sdp, gt_new_files_jdata))
			ip->i_diskflags |= GFS2_DIF_JDATA;
		gfs2_set_aops(inode);
		अवरोध;
	हाल S_IFसूची:
		ip->i_diskflags |= (dip->i_diskflags & GFS2_DIF_INHERIT_JDATA);
		ip->i_diskflags |= GFS2_DIF_JDATA;
		ip->i_entries = 2;
		अवरोध;
	पूर्ण

	/* Force SYSTEM flag on all files and subdirs of a SYSTEM directory */
	अगर (dip->i_diskflags & GFS2_DIF_SYSTEM)
		ip->i_diskflags |= GFS2_DIF_SYSTEM;

	gfs2_set_inode_flags(inode);

	अगर ((GFS2_I(d_inode(sdp->sd_root_dir)) == dip) ||
	    (dip->i_diskflags & GFS2_DIF_TOPसूची))
		aflags |= GFS2_AF_ORLOV;

	अगर (शेष_acl || acl)
		blocks++;

	error = alloc_dinode(ip, aflags, &blocks);
	अगर (error)
		जाओ fail_मुक्त_inode;

	gfs2_set_inode_blocks(inode, blocks);

	error = gfs2_glock_get(sdp, ip->i_no_addr, &gfs2_inode_glops, CREATE, &ip->i_gl);
	अगर (error)
		जाओ fail_मुक्त_inode;
	flush_delayed_work(&ip->i_gl->gl_work);
	glock_set_object(ip->i_gl, ip);

	error = gfs2_glock_get(sdp, ip->i_no_addr, &gfs2_iखोलो_glops, CREATE, &io_gl);
	अगर (error)
		जाओ fail_मुक्त_inode;
	gfs2_cancel_delete_work(io_gl);
	glock_set_object(io_gl, ip);

	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, GL_SKIP, ghs + 1);
	अगर (error)
		जाओ fail_gunlock2;

	error = gfs2_trans_begin(sdp, blocks, 0);
	अगर (error)
		जाओ fail_gunlock2;

	अगर (blocks > 1) अणु
		ip->i_eattr = ip->i_no_addr + 1;
		gfs2_init_xattr(ip);
	पूर्ण
	init_dinode(dip, ip, symname);
	gfs2_trans_end(sdp);

	error = gfs2_glock_nq_init(io_gl, LM_ST_SHARED, GL_EXACT, &ip->i_iखोलो_gh);
	अगर (error)
		जाओ fail_gunlock2;

	gfs2_set_iop(inode);
	insert_inode_hash(inode);

	मुक्त_vfs_inode = 0; /* After this poपूर्णांक, the inode is no दीर्घer
			       considered मुक्त. Any failures need to unकरो
			       the gfs2 काष्ठाures. */
	अगर (शेष_acl) अणु
		error = __gfs2_set_acl(inode, शेष_acl, ACL_TYPE_DEFAULT);
		अगर (error)
			जाओ fail_gunlock3;
		posix_acl_release(शेष_acl);
		शेष_acl = शून्य;
	पूर्ण
	अगर (acl) अणु
		error = __gfs2_set_acl(inode, acl, ACL_TYPE_ACCESS);
		अगर (error)
			जाओ fail_gunlock3;
		posix_acl_release(acl);
		acl = शून्य;
	पूर्ण

	error = security_inode_init_security(&ip->i_inode, &dip->i_inode, name,
					     &gfs2_initxattrs, शून्य);
	अगर (error)
		जाओ fail_gunlock3;

	error = link_dinode(dip, name, ip, &da);
	अगर (error)
		जाओ fail_gunlock3;

	mark_inode_dirty(inode);
	d_instantiate(dentry, inode);
	/* After instantiate, errors should result in evict which will destroy
	 * both inode and iखोलो glocks properly. */
	अगर (file) अणु
		file->f_mode |= FMODE_CREATED;
		error = finish_खोलो(file, dentry, gfs2_खोलो_common);
	पूर्ण
	gfs2_glock_dq_uninit(ghs);
	gfs2_qa_put(ip);
	gfs2_glock_dq_uninit(ghs + 1);
	gfs2_glock_put(io_gl);
	gfs2_qa_put(dip);
	वापस error;

fail_gunlock3:
	glock_clear_object(io_gl, ip);
	gfs2_glock_dq_uninit(&ip->i_iखोलो_gh);
fail_gunlock2:
	glock_clear_object(io_gl, ip);
	gfs2_glock_put(io_gl);
fail_मुक्त_inode:
	अगर (ip->i_gl) अणु
		glock_clear_object(ip->i_gl, ip);
		अगर (मुक्त_vfs_inode) /* अन्यथा evict will करो the put क्रम us */
			gfs2_glock_put(ip->i_gl);
	पूर्ण
	gfs2_rs_delete(ip, शून्य);
	gfs2_qa_put(ip);
fail_मुक्त_acls:
	posix_acl_release(शेष_acl);
	posix_acl_release(acl);
fail_gunlock:
	gfs2_dir_no_add(&da);
	gfs2_glock_dq_uninit(ghs);
	अगर (!IS_ERR_OR_शून्य(inode)) अणु
		clear_nlink(inode);
		अगर (!मुक्त_vfs_inode)
			mark_inode_dirty(inode);
		set_bit(मुक्त_vfs_inode ? GIF_FREE_VFS_INODE : GIF_ALLOC_FAILED,
			&GFS2_I(inode)->i_flags);
		iput(inode);
	पूर्ण
	अगर (gfs2_holder_initialized(ghs + 1))
		gfs2_glock_dq_uninit(ghs + 1);
fail:
	gfs2_qa_put(dip);
	वापस error;
पूर्ण

/**
 * gfs2_create - Create a file
 * @mnt_userns: User namespace of the mount the inode was found from
 * @dir: The directory in which to create the file
 * @dentry: The dentry of the new file
 * @mode: The mode of the new file
 * @excl: Force fail अगर inode exists
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	वापस gfs2_create_inode(dir, dentry, शून्य, S_IFREG | mode, 0, शून्य, 0, excl);
पूर्ण

/**
 * __gfs2_lookup - Look up a filename in a directory and वापस its inode
 * @dir: The directory inode
 * @dentry: The dentry of the new inode
 * @file: File to be खोलोed
 *
 *
 * Returns: त्रुटि_सं
 */

अटल काष्ठा dentry *__gfs2_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				    काष्ठा file *file)
अणु
	काष्ठा inode *inode;
	काष्ठा dentry *d;
	काष्ठा gfs2_holder gh;
	काष्ठा gfs2_glock *gl;
	पूर्णांक error;

	inode = gfs2_lookupi(dir, &dentry->d_name, 0);
	अगर (inode == शून्य) अणु
		d_add(dentry, शून्य);
		वापस शून्य;
	पूर्ण
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);

	gl = GFS2_I(inode)->i_gl;
	error = gfs2_glock_nq_init(gl, LM_ST_SHARED, LM_FLAG_ANY, &gh);
	अगर (error) अणु
		iput(inode);
		वापस ERR_PTR(error);
	पूर्ण

	d = d_splice_alias(inode, dentry);
	अगर (IS_ERR(d)) अणु
		gfs2_glock_dq_uninit(&gh);
		वापस d;
	पूर्ण
	अगर (file && S_ISREG(inode->i_mode))
		error = finish_खोलो(file, dentry, gfs2_खोलो_common);

	gfs2_glock_dq_uninit(&gh);
	अगर (error) अणु
		dput(d);
		वापस ERR_PTR(error);
	पूर्ण
	वापस d;
पूर्ण

अटल काष्ठा dentry *gfs2_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				  अचिन्हित flags)
अणु
	वापस __gfs2_lookup(dir, dentry, शून्य);
पूर्ण

/**
 * gfs2_link - Link to a file
 * @old_dentry: The inode to link
 * @dir: Add link to this directory
 * @dentry: The name of the link
 *
 * Link the inode in "old_dentry" पूर्णांकo the directory "dir" with the
 * name in "dentry".
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
		     काष्ठा dentry *dentry)
अणु
	काष्ठा gfs2_inode *dip = GFS2_I(dir);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(dir);
	काष्ठा inode *inode = d_inode(old_dentry);
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder ghs[2];
	काष्ठा buffer_head *dibh;
	काष्ठा gfs2_diradd da = अणु .bh = शून्य, .save_loc = 1, पूर्ण;
	पूर्णांक error;

	अगर (S_ISसूची(inode->i_mode))
		वापस -EPERM;

	error = gfs2_qa_get(dip);
	अगर (error)
		वापस error;

	gfs2_holder_init(dip->i_gl, LM_ST_EXCLUSIVE, 0, ghs);
	gfs2_holder_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, ghs + 1);

	error = gfs2_glock_nq(ghs); /* parent */
	अगर (error)
		जाओ out_parent;

	error = gfs2_glock_nq(ghs + 1); /* child */
	अगर (error)
		जाओ out_child;

	error = -ENOENT;
	अगर (inode->i_nlink == 0)
		जाओ out_gunlock;

	error = gfs2_permission(&init_user_ns, dir, MAY_WRITE | MAY_EXEC);
	अगर (error)
		जाओ out_gunlock;

	error = gfs2_dir_check(dir, &dentry->d_name, शून्य);
	चयन (error) अणु
	हाल -ENOENT:
		अवरोध;
	हाल 0:
		error = -EEXIST;
		जाओ out_gunlock;
	शेष:
		जाओ out_gunlock;
	पूर्ण

	error = -EINVAL;
	अगर (!dip->i_inode.i_nlink)
		जाओ out_gunlock;
	error = -EFBIG;
	अगर (dip->i_entries == (u32)-1)
		जाओ out_gunlock;
	error = -EPERM;
	अगर (IS_IMMUTABLE(inode) || IS_APPEND(inode))
		जाओ out_gunlock;
	error = -EINVAL;
	अगर (!ip->i_inode.i_nlink)
		जाओ out_gunlock;
	error = -EMLINK;
	अगर (ip->i_inode.i_nlink == (u32)-1)
		जाओ out_gunlock;

	error = gfs2_diradd_alloc_required(dir, &dentry->d_name, &da);
	अगर (error < 0)
		जाओ out_gunlock;

	अगर (da.nr_blocks) अणु
		काष्ठा gfs2_alloc_parms ap = अणु .target = da.nr_blocks, पूर्ण;
		error = gfs2_quota_lock_check(dip, &ap);
		अगर (error)
			जाओ out_gunlock;

		error = gfs2_inplace_reserve(dip, &ap);
		अगर (error)
			जाओ out_gunlock_q;

		error = gfs2_trans_begin(sdp, gfs2_trans_da_blks(dip, &da, 2), 0);
		अगर (error)
			जाओ out_ipres;
	पूर्ण अन्यथा अणु
		error = gfs2_trans_begin(sdp, 2 * RES_DINODE + RES_LEAF, 0);
		अगर (error)
			जाओ out_ipres;
	पूर्ण

	error = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (error)
		जाओ out_end_trans;

	error = gfs2_dir_add(dir, &dentry->d_name, ip, &da);
	अगर (error)
		जाओ out_brअन्यथा;

	gfs2_trans_add_meta(ip->i_gl, dibh);
	inc_nlink(&ip->i_inode);
	ip->i_inode.i_स_समय = current_समय(&ip->i_inode);
	ihold(inode);
	d_instantiate(dentry, inode);
	mark_inode_dirty(inode);

out_brअन्यथा:
	brअन्यथा(dibh);
out_end_trans:
	gfs2_trans_end(sdp);
out_ipres:
	अगर (da.nr_blocks)
		gfs2_inplace_release(dip);
out_gunlock_q:
	अगर (da.nr_blocks)
		gfs2_quota_unlock(dip);
out_gunlock:
	gfs2_dir_no_add(&da);
	gfs2_glock_dq(ghs + 1);
out_child:
	gfs2_glock_dq(ghs);
out_parent:
	gfs2_qa_put(dip);
	gfs2_holder_uninit(ghs);
	gfs2_holder_uninit(ghs + 1);
	वापस error;
पूर्ण

/*
 * gfs2_unlink_ok - check to see that a inode is still in a directory
 * @dip: the directory
 * @name: the name of the file
 * @ip: the inode
 *
 * Assumes that the lock on (at least) @dip is held.
 *
 * Returns: 0 अगर the parent/child relationship is correct, त्रुटि_सं अगर it isn't
 */

अटल पूर्णांक gfs2_unlink_ok(काष्ठा gfs2_inode *dip, स्थिर काष्ठा qstr *name,
			  स्थिर काष्ठा gfs2_inode *ip)
अणु
	पूर्णांक error;

	अगर (IS_IMMUTABLE(&ip->i_inode) || IS_APPEND(&ip->i_inode))
		वापस -EPERM;

	अगर ((dip->i_inode.i_mode & S_ISVTX) &&
	    !uid_eq(dip->i_inode.i_uid, current_fsuid()) &&
	    !uid_eq(ip->i_inode.i_uid, current_fsuid()) && !capable(CAP_FOWNER))
		वापस -EPERM;

	अगर (IS_APPEND(&dip->i_inode))
		वापस -EPERM;

	error = gfs2_permission(&init_user_ns, &dip->i_inode,
				MAY_WRITE | MAY_EXEC);
	अगर (error)
		वापस error;

	वापस gfs2_dir_check(&dip->i_inode, name, ip);
पूर्ण

/**
 * gfs2_unlink_inode - Removes an inode from its parent dir and unlinks it
 * @dip: The parent directory
 * @dentry: The dentry to unlink
 *
 * Called with all the locks and in a transaction. This will only be
 * called क्रम a directory after it has been checked to ensure it is empty.
 *
 * Returns: 0 on success, or an error
 */

अटल पूर्णांक gfs2_unlink_inode(काष्ठा gfs2_inode *dip,
			     स्थिर काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	पूर्णांक error;

	error = gfs2_dir_del(dip, dentry);
	अगर (error)
		वापस error;

	ip->i_entries = 0;
	inode->i_स_समय = current_समय(inode);
	अगर (S_ISसूची(inode->i_mode))
		clear_nlink(inode);
	अन्यथा
		drop_nlink(inode);
	mark_inode_dirty(inode);
	अगर (inode->i_nlink == 0)
		gfs2_unlink_di(inode);
	वापस 0;
पूर्ण


/**
 * gfs2_unlink - Unlink an inode (this करोes सूची_हटाओ as well)
 * @dir: The inode of the directory containing the inode to unlink
 * @dentry: The file itself
 *
 * This routine uses the type of the inode as a flag to figure out
 * whether this is an unlink or an सूची_हटाओ.
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा gfs2_inode *dip = GFS2_I(dir);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(dir);
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder ghs[3];
	काष्ठा gfs2_rgrpd *rgd;
	पूर्णांक error;

	error = gfs2_rindex_update(sdp);
	अगर (error)
		वापस error;

	error = -EROFS;

	gfs2_holder_init(dip->i_gl, LM_ST_EXCLUSIVE, 0, ghs);
	gfs2_holder_init(ip->i_gl,  LM_ST_EXCLUSIVE, 0, ghs + 1);

	rgd = gfs2_blk2rgrpd(sdp, ip->i_no_addr, 1);
	अगर (!rgd)
		जाओ out_inodes;

	gfs2_holder_init(rgd->rd_gl, LM_ST_EXCLUSIVE, LM_FLAG_NODE_SCOPE, ghs + 2);


	error = gfs2_glock_nq(ghs); /* parent */
	अगर (error)
		जाओ out_parent;

	error = gfs2_glock_nq(ghs + 1); /* child */
	अगर (error)
		जाओ out_child;

	error = -ENOENT;
	अगर (inode->i_nlink == 0)
		जाओ out_rgrp;

	अगर (S_ISसूची(inode->i_mode)) अणु
		error = -ENOTEMPTY;
		अगर (ip->i_entries > 2 || inode->i_nlink > 2)
			जाओ out_rgrp;
	पूर्ण

	error = gfs2_glock_nq(ghs + 2); /* rgrp */
	अगर (error)
		जाओ out_rgrp;

	error = gfs2_unlink_ok(dip, &dentry->d_name, ip);
	अगर (error)
		जाओ out_gunlock;

	error = gfs2_trans_begin(sdp, 2*RES_DINODE + 3*RES_LEAF + RES_RG_BIT, 0);
	अगर (error)
		जाओ out_gunlock;

	error = gfs2_unlink_inode(dip, dentry);
	gfs2_trans_end(sdp);

out_gunlock:
	gfs2_glock_dq(ghs + 2);
out_rgrp:
	gfs2_glock_dq(ghs + 1);
out_child:
	gfs2_glock_dq(ghs);
out_parent:
	gfs2_holder_uninit(ghs + 2);
out_inodes:
	gfs2_holder_uninit(ghs + 1);
	gfs2_holder_uninit(ghs);
	वापस error;
पूर्ण

/**
 * gfs2_symlink - Create a symlink
 * @mnt_userns: User namespace of the mount the inode was found from
 * @dir: The directory to create the symlink in
 * @dentry: The dentry to put the symlink in
 * @symname: The thing which the link poपूर्णांकs to
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	अचिन्हित पूर्णांक size;

	size = म_माप(symname);
	अगर (size >= gfs2_max_stuffed_size(GFS2_I(dir)))
		वापस -ENAMETOOLONG;

	वापस gfs2_create_inode(dir, dentry, शून्य, S_IFLNK | S_IRWXUGO, 0, symname, size, 0);
पूर्ण

/**
 * gfs2_सूची_गढ़ो - Make a directory
 * @mnt_userns: User namespace of the mount the inode was found from
 * @dir: The parent directory of the new one
 * @dentry: The dentry of the new directory
 * @mode: The mode of the new directory
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode)
अणु
	अचिन्हित dsize = gfs2_max_stuffed_size(GFS2_I(dir));
	वापस gfs2_create_inode(dir, dentry, शून्य, S_IFसूची | mode, 0, शून्य, dsize, 0);
पूर्ण

/**
 * gfs2_mknod - Make a special file
 * @mnt_userns: User namespace of the mount the inode was found from
 * @dir: The directory in which the special file will reside
 * @dentry: The dentry of the special file
 * @mode: The mode of the special file
 * @dev: The device specअगरication of the special file
 *
 */

अटल पूर्णांक gfs2_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode, dev_t dev)
अणु
	वापस gfs2_create_inode(dir, dentry, शून्य, mode, dev, शून्य, 0, 0);
पूर्ण

/**
 * gfs2_atomic_खोलो - Atomically खोलो a file
 * @dir: The directory
 * @dentry: The proposed new entry
 * @file: The proposed new काष्ठा file
 * @flags: खोलो flags
 * @mode: File mode
 *
 * Returns: error code or 0 क्रम success
 */

अटल पूर्णांक gfs2_atomic_खोलो(काष्ठा inode *dir, काष्ठा dentry *dentry,
			    काष्ठा file *file, अचिन्हित flags,
			    umode_t mode)
अणु
	काष्ठा dentry *d;
	bool excl = !!(flags & O_EXCL);

	अगर (!d_in_lookup(dentry))
		जाओ skip_lookup;

	d = __gfs2_lookup(dir, dentry, file);
	अगर (IS_ERR(d))
		वापस PTR_ERR(d);
	अगर (d != शून्य)
		dentry = d;
	अगर (d_really_is_positive(dentry)) अणु
		अगर (!(file->f_mode & FMODE_OPENED))
			वापस finish_no_खोलो(file, d);
		dput(d);
		वापस excl && (flags & O_CREAT) ? -EEXIST : 0;
	पूर्ण

	BUG_ON(d != शून्य);

skip_lookup:
	अगर (!(flags & O_CREAT))
		वापस -ENOENT;

	वापस gfs2_create_inode(dir, dentry, file, S_IFREG | mode, 0, शून्य, 0, excl);
पूर्ण

/*
 * gfs2_ok_to_move - check अगर it's ok to move a directory to another directory
 * @this: move this
 * @to: to here
 *
 * Follow @to back to the root and make sure we करोn't encounter @this
 * Assumes we alपढ़ोy hold the नाम lock.
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_ok_to_move(काष्ठा gfs2_inode *this, काष्ठा gfs2_inode *to)
अणु
	काष्ठा inode *dir = &to->i_inode;
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा inode *पंचांगp;
	पूर्णांक error = 0;

	igrab(dir);

	क्रम (;;) अणु
		अगर (dir == &this->i_inode) अणु
			error = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (dir == d_inode(sb->s_root)) अणु
			error = 0;
			अवरोध;
		पूर्ण

		पंचांगp = gfs2_lookupi(dir, &gfs2_qकरोtकरोt, 1);
		अगर (!पंचांगp) अणु
			error = -ENOENT;
			अवरोध;
		पूर्ण
		अगर (IS_ERR(पंचांगp)) अणु
			error = PTR_ERR(पंचांगp);
			अवरोध;
		पूर्ण

		iput(dir);
		dir = पंचांगp;
	पूर्ण

	iput(dir);

	वापस error;
पूर्ण

/**
 * update_moved_ino - Update an inode that's being moved
 * @ip: The inode being moved
 * @ndip: The parent directory of the new filename
 * @dir_नाम: True of ip is a directory
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक update_moved_ino(काष्ठा gfs2_inode *ip, काष्ठा gfs2_inode *ndip,
			    पूर्णांक dir_नाम)
अणु
	अगर (dir_नाम)
		वापस gfs2_dir_mvino(ip, &gfs2_qकरोtकरोt, ndip, DT_सूची);

	ip->i_inode.i_स_समय = current_समय(&ip->i_inode);
	mark_inode_dirty_sync(&ip->i_inode);
	वापस 0;
पूर्ण


/**
 * gfs2_नाम - Rename a file
 * @odir: Parent directory of old file name
 * @odentry: The old dentry of the file
 * @ndir: Parent directory of new file name
 * @ndentry: The new dentry of the file
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_नाम(काष्ठा inode *odir, काष्ठा dentry *odentry,
		       काष्ठा inode *ndir, काष्ठा dentry *ndentry)
अणु
	काष्ठा gfs2_inode *odip = GFS2_I(odir);
	काष्ठा gfs2_inode *ndip = GFS2_I(ndir);
	काष्ठा gfs2_inode *ip = GFS2_I(d_inode(odentry));
	काष्ठा gfs2_inode *nip = शून्य;
	काष्ठा gfs2_sbd *sdp = GFS2_SB(odir);
	काष्ठा gfs2_holder ghs[4], r_gh, rd_gh;
	काष्ठा gfs2_rgrpd *nrgd;
	अचिन्हित पूर्णांक num_gh;
	पूर्णांक dir_नाम = 0;
	काष्ठा gfs2_diradd da = अणु .nr_blocks = 0, .save_loc = 0, पूर्ण;
	अचिन्हित पूर्णांक x;
	पूर्णांक error;

	gfs2_holder_mark_uninitialized(&r_gh);
	gfs2_holder_mark_uninitialized(&rd_gh);
	अगर (d_really_is_positive(ndentry)) अणु
		nip = GFS2_I(d_inode(ndentry));
		अगर (ip == nip)
			वापस 0;
	पूर्ण

	error = gfs2_rindex_update(sdp);
	अगर (error)
		वापस error;

	error = gfs2_qa_get(ndip);
	अगर (error)
		वापस error;

	अगर (odip != ndip) अणु
		error = gfs2_glock_nq_init(sdp->sd_नाम_gl, LM_ST_EXCLUSIVE,
					   0, &r_gh);
		अगर (error)
			जाओ out;

		अगर (S_ISसूची(ip->i_inode.i_mode)) अणु
			dir_नाम = 1;
			/* करोn't move a directory पूर्णांकo its subdir */
			error = gfs2_ok_to_move(ip, ndip);
			अगर (error)
				जाओ out_gunlock_r;
		पूर्ण
	पूर्ण

	num_gh = 1;
	gfs2_holder_init(odip->i_gl, LM_ST_EXCLUSIVE, GL_ASYNC, ghs);
	अगर (odip != ndip) अणु
		gfs2_holder_init(ndip->i_gl, LM_ST_EXCLUSIVE,GL_ASYNC,
				 ghs + num_gh);
		num_gh++;
	पूर्ण
	gfs2_holder_init(ip->i_gl, LM_ST_EXCLUSIVE, GL_ASYNC, ghs + num_gh);
	num_gh++;

	अगर (nip) अणु
		gfs2_holder_init(nip->i_gl, LM_ST_EXCLUSIVE, GL_ASYNC,
				 ghs + num_gh);
		num_gh++;
	पूर्ण

	क्रम (x = 0; x < num_gh; x++) अणु
		error = gfs2_glock_nq(ghs + x);
		अगर (error)
			जाओ out_gunlock;
	पूर्ण
	error = gfs2_glock_async_रुको(num_gh, ghs);
	अगर (error)
		जाओ out_gunlock;

	अगर (nip) अणु
		/* Grab the resource group glock क्रम unlink flag twiddling.
		 * This is the हाल where the target dinode alपढ़ोy exists
		 * so we unlink beक्रमe करोing the नाम.
		 */
		nrgd = gfs2_blk2rgrpd(sdp, nip->i_no_addr, 1);
		अगर (!nrgd) अणु
			error = -ENOENT;
			जाओ out_gunlock;
		पूर्ण
		error = gfs2_glock_nq_init(nrgd->rd_gl, LM_ST_EXCLUSIVE,
					   LM_FLAG_NODE_SCOPE, &rd_gh);
		अगर (error)
			जाओ out_gunlock;
	पूर्ण

	error = -ENOENT;
	अगर (ip->i_inode.i_nlink == 0)
		जाओ out_gunlock;

	/* Check out the old directory */

	error = gfs2_unlink_ok(odip, &odentry->d_name, ip);
	अगर (error)
		जाओ out_gunlock;

	/* Check out the new directory */

	अगर (nip) अणु
		error = gfs2_unlink_ok(ndip, &ndentry->d_name, nip);
		अगर (error)
			जाओ out_gunlock;

		अगर (nip->i_inode.i_nlink == 0) अणु
			error = -EAGAIN;
			जाओ out_gunlock;
		पूर्ण

		अगर (S_ISसूची(nip->i_inode.i_mode)) अणु
			अगर (nip->i_entries < 2) अणु
				gfs2_consist_inode(nip);
				error = -EIO;
				जाओ out_gunlock;
			पूर्ण
			अगर (nip->i_entries > 2) अणु
				error = -ENOTEMPTY;
				जाओ out_gunlock;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		error = gfs2_permission(&init_user_ns, ndir,
					MAY_WRITE | MAY_EXEC);
		अगर (error)
			जाओ out_gunlock;

		error = gfs2_dir_check(ndir, &ndentry->d_name, शून्य);
		चयन (error) अणु
		हाल -ENOENT:
			error = 0;
			अवरोध;
		हाल 0:
			error = -EEXIST;
			जाओ out_gunlock;
		शेष:
			जाओ out_gunlock;
		पूर्ण

		अगर (odip != ndip) अणु
			अगर (!ndip->i_inode.i_nlink) अणु
				error = -ENOENT;
				जाओ out_gunlock;
			पूर्ण
			अगर (ndip->i_entries == (u32)-1) अणु
				error = -EFBIG;
				जाओ out_gunlock;
			पूर्ण
			अगर (S_ISसूची(ip->i_inode.i_mode) &&
			    ndip->i_inode.i_nlink == (u32)-1) अणु
				error = -EMLINK;
				जाओ out_gunlock;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Check out the dir to be नामd */

	अगर (dir_नाम) अणु
		error = gfs2_permission(&init_user_ns, d_inode(odentry),
					MAY_WRITE);
		अगर (error)
			जाओ out_gunlock;
	पूर्ण

	अगर (nip == शून्य) अणु
		error = gfs2_diradd_alloc_required(ndir, &ndentry->d_name, &da);
		अगर (error)
			जाओ out_gunlock;
	पूर्ण

	अगर (da.nr_blocks) अणु
		काष्ठा gfs2_alloc_parms ap = अणु .target = da.nr_blocks, पूर्ण;
		error = gfs2_quota_lock_check(ndip, &ap);
		अगर (error)
			जाओ out_gunlock;

		error = gfs2_inplace_reserve(ndip, &ap);
		अगर (error)
			जाओ out_gunlock_q;

		error = gfs2_trans_begin(sdp, gfs2_trans_da_blks(ndip, &da, 4) +
					 4 * RES_LEAF + 4, 0);
		अगर (error)
			जाओ out_ipreserv;
	पूर्ण अन्यथा अणु
		error = gfs2_trans_begin(sdp, 4 * RES_DINODE +
					 5 * RES_LEAF + 4, 0);
		अगर (error)
			जाओ out_gunlock;
	पूर्ण

	/* Remove the target file, अगर it exists */

	अगर (nip)
		error = gfs2_unlink_inode(ndip, ndentry);

	error = update_moved_ino(ip, ndip, dir_नाम);
	अगर (error)
		जाओ out_end_trans;

	error = gfs2_dir_del(odip, odentry);
	अगर (error)
		जाओ out_end_trans;

	error = gfs2_dir_add(ndir, &ndentry->d_name, ip, &da);
	अगर (error)
		जाओ out_end_trans;

out_end_trans:
	gfs2_trans_end(sdp);
out_ipreserv:
	अगर (da.nr_blocks)
		gfs2_inplace_release(ndip);
out_gunlock_q:
	अगर (da.nr_blocks)
		gfs2_quota_unlock(ndip);
out_gunlock:
	gfs2_dir_no_add(&da);
	अगर (gfs2_holder_initialized(&rd_gh))
		gfs2_glock_dq_uninit(&rd_gh);

	जबतक (x--) अणु
		अगर (gfs2_holder_queued(ghs + x))
			gfs2_glock_dq(ghs + x);
		gfs2_holder_uninit(ghs + x);
	पूर्ण
out_gunlock_r:
	अगर (gfs2_holder_initialized(&r_gh))
		gfs2_glock_dq_uninit(&r_gh);
out:
	gfs2_qa_put(ndip);
	वापस error;
पूर्ण

/**
 * gfs2_exchange - exchange two files
 * @odir: Parent directory of old file name
 * @odentry: The old dentry of the file
 * @ndir: Parent directory of new file name
 * @ndentry: The new dentry of the file
 * @flags: The नाम flags
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_exchange(काष्ठा inode *odir, काष्ठा dentry *odentry,
			 काष्ठा inode *ndir, काष्ठा dentry *ndentry,
			 अचिन्हित पूर्णांक flags)
अणु
	काष्ठा gfs2_inode *odip = GFS2_I(odir);
	काष्ठा gfs2_inode *ndip = GFS2_I(ndir);
	काष्ठा gfs2_inode *oip = GFS2_I(odentry->d_inode);
	काष्ठा gfs2_inode *nip = GFS2_I(ndentry->d_inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(odir);
	काष्ठा gfs2_holder ghs[4], r_gh;
	अचिन्हित पूर्णांक num_gh;
	अचिन्हित पूर्णांक x;
	umode_t old_mode = oip->i_inode.i_mode;
	umode_t new_mode = nip->i_inode.i_mode;
	पूर्णांक error;

	gfs2_holder_mark_uninitialized(&r_gh);
	error = gfs2_rindex_update(sdp);
	अगर (error)
		वापस error;

	अगर (odip != ndip) अणु
		error = gfs2_glock_nq_init(sdp->sd_नाम_gl, LM_ST_EXCLUSIVE,
					   0, &r_gh);
		अगर (error)
			जाओ out;

		अगर (S_ISसूची(old_mode)) अणु
			/* करोn't move a directory पूर्णांकo its subdir */
			error = gfs2_ok_to_move(oip, ndip);
			अगर (error)
				जाओ out_gunlock_r;
		पूर्ण

		अगर (S_ISसूची(new_mode)) अणु
			/* करोn't move a directory पूर्णांकo its subdir */
			error = gfs2_ok_to_move(nip, odip);
			अगर (error)
				जाओ out_gunlock_r;
		पूर्ण
	पूर्ण

	num_gh = 1;
	gfs2_holder_init(odip->i_gl, LM_ST_EXCLUSIVE, GL_ASYNC, ghs);
	अगर (odip != ndip) अणु
		gfs2_holder_init(ndip->i_gl, LM_ST_EXCLUSIVE, GL_ASYNC,
				 ghs + num_gh);
		num_gh++;
	पूर्ण
	gfs2_holder_init(oip->i_gl, LM_ST_EXCLUSIVE, GL_ASYNC, ghs + num_gh);
	num_gh++;

	gfs2_holder_init(nip->i_gl, LM_ST_EXCLUSIVE, GL_ASYNC, ghs + num_gh);
	num_gh++;

	क्रम (x = 0; x < num_gh; x++) अणु
		error = gfs2_glock_nq(ghs + x);
		अगर (error)
			जाओ out_gunlock;
	पूर्ण

	error = gfs2_glock_async_रुको(num_gh, ghs);
	अगर (error)
		जाओ out_gunlock;

	error = -ENOENT;
	अगर (oip->i_inode.i_nlink == 0 || nip->i_inode.i_nlink == 0)
		जाओ out_gunlock;

	error = gfs2_unlink_ok(odip, &odentry->d_name, oip);
	अगर (error)
		जाओ out_gunlock;
	error = gfs2_unlink_ok(ndip, &ndentry->d_name, nip);
	अगर (error)
		जाओ out_gunlock;

	अगर (S_ISसूची(old_mode)) अणु
		error = gfs2_permission(&init_user_ns, odentry->d_inode,
					MAY_WRITE);
		अगर (error)
			जाओ out_gunlock;
	पूर्ण
	अगर (S_ISसूची(new_mode)) अणु
		error = gfs2_permission(&init_user_ns, ndentry->d_inode,
					MAY_WRITE);
		अगर (error)
			जाओ out_gunlock;
	पूर्ण
	error = gfs2_trans_begin(sdp, 4 * RES_DINODE + 4 * RES_LEAF, 0);
	अगर (error)
		जाओ out_gunlock;

	error = update_moved_ino(oip, ndip, S_ISसूची(old_mode));
	अगर (error)
		जाओ out_end_trans;

	error = update_moved_ino(nip, odip, S_ISसूची(new_mode));
	अगर (error)
		जाओ out_end_trans;

	error = gfs2_dir_mvino(ndip, &ndentry->d_name, oip,
			       IF2DT(old_mode));
	अगर (error)
		जाओ out_end_trans;

	error = gfs2_dir_mvino(odip, &odentry->d_name, nip,
			       IF2DT(new_mode));
	अगर (error)
		जाओ out_end_trans;

	अगर (odip != ndip) अणु
		अगर (S_ISसूची(new_mode) && !S_ISसूची(old_mode)) अणु
			inc_nlink(&odip->i_inode);
			drop_nlink(&ndip->i_inode);
		पूर्ण अन्यथा अगर (S_ISसूची(old_mode) && !S_ISसूची(new_mode)) अणु
			inc_nlink(&ndip->i_inode);
			drop_nlink(&odip->i_inode);
		पूर्ण
	पूर्ण
	mark_inode_dirty(&ndip->i_inode);
	अगर (odip != ndip)
		mark_inode_dirty(&odip->i_inode);

out_end_trans:
	gfs2_trans_end(sdp);
out_gunlock:
	जबतक (x--) अणु
		अगर (gfs2_holder_queued(ghs + x))
			gfs2_glock_dq(ghs + x);
		gfs2_holder_uninit(ghs + x);
	पूर्ण
out_gunlock_r:
	अगर (gfs2_holder_initialized(&r_gh))
		gfs2_glock_dq_uninit(&r_gh);
out:
	वापस error;
पूर्ण

अटल पूर्णांक gfs2_नाम2(काष्ठा user_namespace *mnt_userns, काष्ठा inode *odir,
			काष्ठा dentry *odentry, काष्ठा inode *ndir,
			काष्ठा dentry *ndentry, अचिन्हित पूर्णांक flags)
अणु
	flags &= ~RENAME_NOREPLACE;

	अगर (flags & ~RENAME_EXCHANGE)
		वापस -EINVAL;

	अगर (flags & RENAME_EXCHANGE)
		वापस gfs2_exchange(odir, odentry, ndir, ndentry, flags);

	वापस gfs2_नाम(odir, odentry, ndir, ndentry);
पूर्ण

/**
 * gfs2_get_link - Follow a symbolic link
 * @dentry: The dentry of the link
 * @inode: The inode of the link
 * @करोne: deकाष्ठाor क्रम वापस value
 *
 * This can handle symlinks of any size.
 *
 * Returns: 0 on success or error code
 */

अटल स्थिर अक्षर *gfs2_get_link(काष्ठा dentry *dentry,
				 काष्ठा inode *inode,
				 काष्ठा delayed_call *करोne)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder i_gh;
	काष्ठा buffer_head *dibh;
	अचिन्हित पूर्णांक size;
	अक्षर *buf;
	पूर्णांक error;

	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);

	gfs2_holder_init(ip->i_gl, LM_ST_SHARED, 0, &i_gh);
	error = gfs2_glock_nq(&i_gh);
	अगर (error) अणु
		gfs2_holder_uninit(&i_gh);
		वापस ERR_PTR(error);
	पूर्ण

	size = (अचिन्हित पूर्णांक)i_size_पढ़ो(&ip->i_inode);
	अगर (size == 0) अणु
		gfs2_consist_inode(ip);
		buf = ERR_PTR(-EIO);
		जाओ out;
	पूर्ण

	error = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (error) अणु
		buf = ERR_PTR(error);
		जाओ out;
	पूर्ण

	buf = kzalloc(size + 1, GFP_NOFS);
	अगर (!buf)
		buf = ERR_PTR(-ENOMEM);
	अन्यथा
		स_नकल(buf, dibh->b_data + माप(काष्ठा gfs2_dinode), size);
	brअन्यथा(dibh);
out:
	gfs2_glock_dq_uninit(&i_gh);
	अगर (!IS_ERR(buf))
		set_delayed_call(करोne, kमुक्त_link, buf);
	वापस buf;
पूर्ण

/**
 * gfs2_permission
 * @mnt_userns: User namespace of the mount the inode was found from
 * @inode: The inode
 * @mask: The mask to be tested
 *
 * This may be called from the VFS directly, or from within GFS2 with the
 * inode locked, so we look to see अगर the glock is alपढ़ोy locked and only
 * lock the glock अगर its not alपढ़ोy been करोne.
 *
 * Returns: त्रुटि_सं
 */

पूर्णांक gfs2_permission(काष्ठा user_namespace *mnt_userns, काष्ठा inode *inode,
		    पूर्णांक mask)
अणु
	काष्ठा gfs2_inode *ip;
	काष्ठा gfs2_holder i_gh;
	पूर्णांक error;

	gfs2_holder_mark_uninitialized(&i_gh);
	ip = GFS2_I(inode);
	अगर (gfs2_glock_is_locked_by_me(ip->i_gl) == शून्य) अणु
		अगर (mask & MAY_NOT_BLOCK)
			वापस -ECHILD;
		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, LM_FLAG_ANY, &i_gh);
		अगर (error)
			वापस error;
	पूर्ण

	अगर ((mask & MAY_WRITE) && IS_IMMUTABLE(inode))
		error = -EPERM;
	अन्यथा
		error = generic_permission(&init_user_ns, inode, mask);
	अगर (gfs2_holder_initialized(&i_gh))
		gfs2_glock_dq_uninit(&i_gh);

	वापस error;
पूर्ण

अटल पूर्णांक __gfs2_setattr_simple(काष्ठा inode *inode, काष्ठा iattr *attr)
अणु
	setattr_copy(&init_user_ns, inode, attr);
	mark_inode_dirty(inode);
	वापस 0;
पूर्ण

अटल पूर्णांक gfs2_setattr_simple(काष्ठा inode *inode, काष्ठा iattr *attr)
अणु
	पूर्णांक error;

	अगर (current->journal_info)
		वापस __gfs2_setattr_simple(inode, attr);

	error = gfs2_trans_begin(GFS2_SB(inode), RES_DINODE, 0);
	अगर (error)
		वापस error;

	error = __gfs2_setattr_simple(inode, attr);
	gfs2_trans_end(GFS2_SB(inode));
	वापस error;
पूर्ण

अटल पूर्णांक setattr_chown(काष्ठा inode *inode, काष्ठा iattr *attr)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	kuid_t ouid, nuid;
	kgid_t ogid, ngid;
	पूर्णांक error;
	काष्ठा gfs2_alloc_parms ap;

	ouid = inode->i_uid;
	ogid = inode->i_gid;
	nuid = attr->ia_uid;
	ngid = attr->ia_gid;

	अगर (!(attr->ia_valid & ATTR_UID) || uid_eq(ouid, nuid))
		ouid = nuid = NO_UID_QUOTA_CHANGE;
	अगर (!(attr->ia_valid & ATTR_GID) || gid_eq(ogid, ngid))
		ogid = ngid = NO_GID_QUOTA_CHANGE;
	error = gfs2_qa_get(ip);
	अगर (error)
		वापस error;

	error = gfs2_rindex_update(sdp);
	अगर (error)
		जाओ out;

	error = gfs2_quota_lock(ip, nuid, ngid);
	अगर (error)
		जाओ out;

	ap.target = gfs2_get_inode_blocks(&ip->i_inode);

	अगर (!uid_eq(ouid, NO_UID_QUOTA_CHANGE) ||
	    !gid_eq(ogid, NO_GID_QUOTA_CHANGE)) अणु
		error = gfs2_quota_check(ip, nuid, ngid, &ap);
		अगर (error)
			जाओ out_gunlock_q;
	पूर्ण

	error = gfs2_trans_begin(sdp, RES_DINODE + 2 * RES_QUOTA, 0);
	अगर (error)
		जाओ out_gunlock_q;

	error = gfs2_setattr_simple(inode, attr);
	अगर (error)
		जाओ out_end_trans;

	अगर (!uid_eq(ouid, NO_UID_QUOTA_CHANGE) ||
	    !gid_eq(ogid, NO_GID_QUOTA_CHANGE)) अणु
		gfs2_quota_change(ip, -(s64)ap.target, ouid, ogid);
		gfs2_quota_change(ip, ap.target, nuid, ngid);
	पूर्ण

out_end_trans:
	gfs2_trans_end(sdp);
out_gunlock_q:
	gfs2_quota_unlock(ip);
out:
	gfs2_qa_put(ip);
	वापस error;
पूर्ण

/**
 * gfs2_setattr - Change attributes on an inode
 * @mnt_userns: User namespace of the mount the inode was found from
 * @dentry: The dentry which is changing
 * @attr: The काष्ठाure describing the change
 *
 * The VFS layer wants to change one or more of an inodes attributes.  Write
 * that change out to disk.
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_setattr(काष्ठा user_namespace *mnt_userns,
			काष्ठा dentry *dentry, काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder i_gh;
	पूर्णांक error;

	error = gfs2_qa_get(ip);
	अगर (error)
		वापस error;

	error = gfs2_glock_nq_init(ip->i_gl, LM_ST_EXCLUSIVE, 0, &i_gh);
	अगर (error)
		जाओ out;

	error = -EPERM;
	अगर (IS_IMMUTABLE(inode) || IS_APPEND(inode))
		जाओ error;

	error = setattr_prepare(&init_user_ns, dentry, attr);
	अगर (error)
		जाओ error;

	अगर (attr->ia_valid & ATTR_SIZE)
		error = gfs2_setattr_size(inode, attr->ia_size);
	अन्यथा अगर (attr->ia_valid & (ATTR_UID | ATTR_GID))
		error = setattr_chown(inode, attr);
	अन्यथा अणु
		error = gfs2_setattr_simple(inode, attr);
		अगर (!error && attr->ia_valid & ATTR_MODE)
			error = posix_acl_chmod(&init_user_ns, inode,
						inode->i_mode);
	पूर्ण

error:
	अगर (!error)
		mark_inode_dirty(inode);
	gfs2_glock_dq_uninit(&i_gh);
out:
	gfs2_qa_put(ip);
	वापस error;
पूर्ण

/**
 * gfs2_getattr - Read out an inode's attributes
 * @mnt_userns:	user namespace of the mount the inode was found from
 * @path: Object to query
 * @stat: The inode's stats
 * @request_mask: Mask of STATX_xxx flags indicating the caller's पूर्णांकerests
 * @flags: AT_STATX_xxx setting
 *
 * This may be called from the VFS directly, or from within GFS2 with the
 * inode locked, so we look to see अगर the glock is alपढ़ोy locked and only
 * lock the glock अगर its not alपढ़ोy been करोne. Note that its the NFS
 * सूची_पढ़ोplus operation which causes this to be called (from filldir)
 * with the glock alपढ़ोy held.
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक gfs2_getattr(काष्ठा user_namespace *mnt_userns,
			स्थिर काष्ठा path *path, काष्ठा kstat *stat,
			u32 request_mask, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = d_inode(path->dentry);
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder gh;
	u32 gfsflags;
	पूर्णांक error;

	gfs2_holder_mark_uninitialized(&gh);
	अगर (gfs2_glock_is_locked_by_me(ip->i_gl) == शून्य) अणु
		error = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, LM_FLAG_ANY, &gh);
		अगर (error)
			वापस error;
	पूर्ण

	gfsflags = ip->i_diskflags;
	अगर (gfsflags & GFS2_DIF_APPENDONLY)
		stat->attributes |= STATX_ATTR_APPEND;
	अगर (gfsflags & GFS2_DIF_IMMUTABLE)
		stat->attributes |= STATX_ATTR_IMMUTABLE;

	stat->attributes_mask |= (STATX_ATTR_APPEND |
				  STATX_ATTR_COMPRESSED |
				  STATX_ATTR_ENCRYPTED |
				  STATX_ATTR_IMMUTABLE |
				  STATX_ATTR_NODUMP);

	generic_fillattr(&init_user_ns, inode, stat);

	अगर (gfs2_holder_initialized(&gh))
		gfs2_glock_dq_uninit(&gh);

	वापस 0;
पूर्ण

अटल पूर्णांक gfs2_fiemap(काष्ठा inode *inode, काष्ठा fiemap_extent_info *fieinfo,
		       u64 start, u64 len)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder gh;
	पूर्णांक ret;

	inode_lock_shared(inode);

	ret = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, 0, &gh);
	अगर (ret)
		जाओ out;

	ret = iomap_fiemap(inode, fieinfo, start, len, &gfs2_iomap_ops);

	gfs2_glock_dq_uninit(&gh);

out:
	inode_unlock_shared(inode);
	वापस ret;
पूर्ण

loff_t gfs2_seek_data(काष्ठा file *file, loff_t offset)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder gh;
	loff_t ret;

	inode_lock_shared(inode);
	ret = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, 0, &gh);
	अगर (!ret)
		ret = iomap_seek_data(inode, offset, &gfs2_iomap_ops);
	gfs2_glock_dq_uninit(&gh);
	inode_unlock_shared(inode);

	अगर (ret < 0)
		वापस ret;
	वापस vfs_setpos(file, ret, inode->i_sb->s_maxbytes);
पूर्ण

loff_t gfs2_seek_hole(काष्ठा file *file, loff_t offset)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_holder gh;
	loff_t ret;

	inode_lock_shared(inode);
	ret = gfs2_glock_nq_init(ip->i_gl, LM_ST_SHARED, 0, &gh);
	अगर (!ret)
		ret = iomap_seek_hole(inode, offset, &gfs2_iomap_ops);
	gfs2_glock_dq_uninit(&gh);
	inode_unlock_shared(inode);

	अगर (ret < 0)
		वापस ret;
	वापस vfs_setpos(file, ret, inode->i_sb->s_maxbytes);
पूर्ण

अटल पूर्णांक gfs2_update_समय(काष्ठा inode *inode, काष्ठा बारpec64 *समय,
			    पूर्णांक flags)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_glock *gl = ip->i_gl;
	काष्ठा gfs2_holder *gh;
	पूर्णांक error;

	gh = gfs2_glock_is_locked_by_me(gl);
	अगर (gh && !gfs2_glock_is_held_excl(gl)) अणु
		gfs2_glock_dq(gh);
		gfs2_holder_reinit(LM_ST_EXCLUSIVE, 0, gh);
		error = gfs2_glock_nq(gh);
		अगर (error)
			वापस error;
	पूर्ण
	वापस generic_update_समय(inode, समय, flags);
पूर्ण

अटल स्थिर काष्ठा inode_operations gfs2_file_iops = अणु
	.permission = gfs2_permission,
	.setattr = gfs2_setattr,
	.getattr = gfs2_getattr,
	.listxattr = gfs2_listxattr,
	.fiemap = gfs2_fiemap,
	.get_acl = gfs2_get_acl,
	.set_acl = gfs2_set_acl,
	.update_समय = gfs2_update_समय,
	.fileattr_get = gfs2_fileattr_get,
	.fileattr_set = gfs2_fileattr_set,
पूर्ण;

अटल स्थिर काष्ठा inode_operations gfs2_dir_iops = अणु
	.create = gfs2_create,
	.lookup = gfs2_lookup,
	.link = gfs2_link,
	.unlink = gfs2_unlink,
	.symlink = gfs2_symlink,
	.सूची_गढ़ो = gfs2_सूची_गढ़ो,
	.सूची_हटाओ = gfs2_unlink,
	.mknod = gfs2_mknod,
	.नाम = gfs2_नाम2,
	.permission = gfs2_permission,
	.setattr = gfs2_setattr,
	.getattr = gfs2_getattr,
	.listxattr = gfs2_listxattr,
	.fiemap = gfs2_fiemap,
	.get_acl = gfs2_get_acl,
	.set_acl = gfs2_set_acl,
	.update_समय = gfs2_update_समय,
	.atomic_खोलो = gfs2_atomic_खोलो,
	.fileattr_get = gfs2_fileattr_get,
	.fileattr_set = gfs2_fileattr_set,
पूर्ण;

अटल स्थिर काष्ठा inode_operations gfs2_symlink_iops = अणु
	.get_link = gfs2_get_link,
	.permission = gfs2_permission,
	.setattr = gfs2_setattr,
	.getattr = gfs2_getattr,
	.listxattr = gfs2_listxattr,
	.fiemap = gfs2_fiemap,
पूर्ण;

