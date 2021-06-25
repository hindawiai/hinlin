<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

#समावेश <linux/spinlock.h>
#समावेश <linux/completion.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/exportfs.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/crc32.h>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "dir.h"
#समावेश "glock.h"
#समावेश "glops.h"
#समावेश "inode.h"
#समावेश "super.h"
#समावेश "rgrp.h"
#समावेश "util.h"

#घोषणा GFS2_SMALL_FH_SIZE 4
#घोषणा GFS2_LARGE_FH_SIZE 8
#घोषणा GFS2_OLD_FH_SIZE 10

अटल पूर्णांक gfs2_encode_fh(काष्ठा inode *inode, __u32 *p, पूर्णांक *len,
			  काष्ठा inode *parent)
अणु
	__be32 *fh = (__क्रमce __be32 *)p;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);

	अगर (parent && (*len < GFS2_LARGE_FH_SIZE)) अणु
		*len = GFS2_LARGE_FH_SIZE;
		वापस खाताID_INVALID;
	पूर्ण अन्यथा अगर (*len < GFS2_SMALL_FH_SIZE) अणु
		*len = GFS2_SMALL_FH_SIZE;
		वापस खाताID_INVALID;
	पूर्ण

	fh[0] = cpu_to_be32(ip->i_no_क्रमmal_ino >> 32);
	fh[1] = cpu_to_be32(ip->i_no_क्रमmal_ino & 0xFFFFFFFF);
	fh[2] = cpu_to_be32(ip->i_no_addr >> 32);
	fh[3] = cpu_to_be32(ip->i_no_addr & 0xFFFFFFFF);
	*len = GFS2_SMALL_FH_SIZE;

	अगर (!parent || inode == d_inode(sb->s_root))
		वापस *len;

	ip = GFS2_I(parent);

	fh[4] = cpu_to_be32(ip->i_no_क्रमmal_ino >> 32);
	fh[5] = cpu_to_be32(ip->i_no_क्रमmal_ino & 0xFFFFFFFF);
	fh[6] = cpu_to_be32(ip->i_no_addr >> 32);
	fh[7] = cpu_to_be32(ip->i_no_addr & 0xFFFFFFFF);
	*len = GFS2_LARGE_FH_SIZE;

	वापस *len;
पूर्ण

काष्ठा get_name_filldir अणु
	काष्ठा dir_context ctx;
	काष्ठा gfs2_inum_host inum;
	अक्षर *name;
पूर्ण;

अटल पूर्णांक get_name_filldir(काष्ठा dir_context *ctx, स्थिर अक्षर *name,
			    पूर्णांक length, loff_t offset, u64 inum,
			    अचिन्हित पूर्णांक type)
अणु
	काष्ठा get_name_filldir *gnfd =
		container_of(ctx, काष्ठा get_name_filldir, ctx);

	अगर (inum != gnfd->inum.no_addr)
		वापस 0;

	स_नकल(gnfd->name, name, length);
	gnfd->name[length] = 0;

	वापस 1;
पूर्ण

अटल पूर्णांक gfs2_get_name(काष्ठा dentry *parent, अक्षर *name,
			 काष्ठा dentry *child)
अणु
	काष्ठा inode *dir = d_inode(parent);
	काष्ठा inode *inode = d_inode(child);
	काष्ठा gfs2_inode *dip, *ip;
	काष्ठा get_name_filldir gnfd = अणु
		.ctx.actor = get_name_filldir,
		.name = name
	पूर्ण;
	काष्ठा gfs2_holder gh;
	पूर्णांक error;
	काष्ठा file_ra_state f_ra = अणु .start = 0 पूर्ण;

	अगर (!dir)
		वापस -EINVAL;

	अगर (!S_ISसूची(dir->i_mode) || !inode)
		वापस -EINVAL;

	dip = GFS2_I(dir);
	ip = GFS2_I(inode);

	*name = 0;
	gnfd.inum.no_addr = ip->i_no_addr;
	gnfd.inum.no_क्रमmal_ino = ip->i_no_क्रमmal_ino;

	error = gfs2_glock_nq_init(dip->i_gl, LM_ST_SHARED, 0, &gh);
	अगर (error)
		वापस error;

	error = gfs2_dir_पढ़ो(dir, &gnfd.ctx, &f_ra);

	gfs2_glock_dq_uninit(&gh);

	अगर (!error && !*name)
		error = -ENOENT;

	वापस error;
पूर्ण

अटल काष्ठा dentry *gfs2_get_parent(काष्ठा dentry *child)
अणु
	वापस d_obtain_alias(gfs2_lookupi(d_inode(child), &gfs2_qकरोtकरोt, 1));
पूर्ण

अटल काष्ठा dentry *gfs2_get_dentry(काष्ठा super_block *sb,
				      काष्ठा gfs2_inum_host *inum)
अणु
	काष्ठा gfs2_sbd *sdp = sb->s_fs_info;
	काष्ठा inode *inode;

	अगर (!inum->no_क्रमmal_ino)
		वापस ERR_PTR(-ESTALE);
	inode = gfs2_lookup_by_inum(sdp, inum->no_addr, inum->no_क्रमmal_ino,
				    GFS2_BLKST_DINODE);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);
	वापस d_obtain_alias(inode);
पूर्ण

अटल काष्ठा dentry *gfs2_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा gfs2_inum_host this;
	__be32 *fh = (__क्रमce __be32 *)fid->raw;

	चयन (fh_type) अणु
	हाल GFS2_SMALL_FH_SIZE:
	हाल GFS2_LARGE_FH_SIZE:
	हाल GFS2_OLD_FH_SIZE:
		अगर (fh_len < GFS2_SMALL_FH_SIZE)
			वापस शून्य;
		this.no_क्रमmal_ino = ((u64)be32_to_cpu(fh[0])) << 32;
		this.no_क्रमmal_ino |= be32_to_cpu(fh[1]);
		this.no_addr = ((u64)be32_to_cpu(fh[2])) << 32;
		this.no_addr |= be32_to_cpu(fh[3]);
		वापस gfs2_get_dentry(sb, &this);
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा dentry *gfs2_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	काष्ठा gfs2_inum_host parent;
	__be32 *fh = (__क्रमce __be32 *)fid->raw;

	चयन (fh_type) अणु
	हाल GFS2_LARGE_FH_SIZE:
	हाल GFS2_OLD_FH_SIZE:
		अगर (fh_len < GFS2_LARGE_FH_SIZE)
			वापस शून्य;
		parent.no_क्रमmal_ino = ((u64)be32_to_cpu(fh[4])) << 32;
		parent.no_क्रमmal_ino |= be32_to_cpu(fh[5]);
		parent.no_addr = ((u64)be32_to_cpu(fh[6])) << 32;
		parent.no_addr |= be32_to_cpu(fh[7]);
		वापस gfs2_get_dentry(sb, &parent);
	शेष:
		वापस शून्य;
	पूर्ण
पूर्ण

स्थिर काष्ठा export_operations gfs2_export_ops = अणु
	.encode_fh = gfs2_encode_fh,
	.fh_to_dentry = gfs2_fh_to_dentry,
	.fh_to_parent = gfs2_fh_to_parent,
	.get_name = gfs2_get_name,
	.get_parent = gfs2_get_parent,
पूर्ण;

