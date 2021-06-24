<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) Sistina Software, Inc.  1997-2003 All rights reserved.
 * Copyright (C) 2004-2006 Red Hat, Inc.  All rights reserved.
 */

/*
 * Implements Extendible Hashing as described in:
 *   "Extendible Hashing" by Fagin, et al in
 *     __ACM Trans. on Database Systems__, Sept 1979.
 *
 *
 * Here's the layout of dirents which is essentially the same as that of ext2
 * within a single block. The field de_name_len is the number of bytes
 * actually required क्रम the name (no null terminator). The field de_rec_len
 * is the number of bytes allocated to the dirent. The offset of the next
 * dirent in the block is (dirent + dirent->de_rec_len). When a dirent is
 * deleted, the preceding dirent inherits its allocated space, ie
 * prev->de_rec_len += deleted->de_rec_len. Since the next dirent is obtained
 * by adding de_rec_len to the current dirent, this essentially causes the
 * deleted dirent to get jumped over when iterating through all the dirents.
 *
 * When deleting the first dirent in a block, there is no previous dirent so
 * the field de_ino is set to zero to designate it as deleted. When allocating
 * a dirent, gfs2_dirent_alloc iterates through the dirents in a block. If the
 * first dirent has (de_ino == 0) and de_rec_len is large enough, this first
 * dirent is allocated. Otherwise it must go through all the 'used' dirents
 * searching क्रम one in which the amount of total space minus the amount of
 * used space will provide enough space क्रम the new dirent.
 *
 * There are two types of blocks in which dirents reside. In a stuffed dinode,
 * the dirents begin at offset माप(काष्ठा gfs2_dinode) from the beginning of
 * the block.  In leaves, they begin at offset माप(काष्ठा gfs2_leaf) from the
 * beginning of the leaf block. The dirents reside in leaves when
 *
 * dip->i_diskflags & GFS2_DIF_EXHASH is true
 *
 * Otherwise, the dirents are "linear", within a single stuffed dinode block.
 *
 * When the dirents are in leaves, the actual contents of the directory file are
 * used as an array of 64-bit block poपूर्णांकers poपूर्णांकing to the leaf blocks. The
 * dirents are NOT in the directory file itself. There can be more than one
 * block poपूर्णांकer in the array that poपूर्णांकs to the same leaf. In fact, when a
 * directory is first converted from linear to exhash, all of the poपूर्णांकers
 * poपूर्णांक to the same leaf.
 *
 * When a leaf is completely full, the size of the hash table can be
 * द्विगुनd unless it is alपढ़ोy at the maximum size which is hard coded पूर्णांकo
 * GFS2_सूची_MAX_DEPTH. After that, leaves are chained together in a linked list,
 * but never beक्रमe the maximum hash table size has been reached.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/buffer_head.h>
#समावेश <linux/sort.h>
#समावेश <linux/gfs2_ondisk.h>
#समावेश <linux/crc32.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/bपन.स>

#समावेश "gfs2.h"
#समावेश "incore.h"
#समावेश "dir.h"
#समावेश "glock.h"
#समावेश "inode.h"
#समावेश "meta_io.h"
#समावेश "quota.h"
#समावेश "rgrp.h"
#समावेश "trans.h"
#समावेश "bmap.h"
#समावेश "util.h"

#घोषणा MAX_RA_BLOCKS 32 /* max पढ़ो-ahead blocks */

#घोषणा gfs2_disk_hash2offset(h) (((u64)(h)) >> 1)
#घोषणा gfs2_dir_offset2hash(p) ((u32)(((u64)(p)) << 1))
#घोषणा GFS2_HASH_INDEX_MASK 0xffffc000
#घोषणा GFS2_USE_HASH_FLAG 0x2000

काष्ठा qstr gfs2_qकरोt __पढ़ो_mostly;
काष्ठा qstr gfs2_qकरोtकरोt __पढ़ो_mostly;

प्रकार पूर्णांक (*gfs2_dscan_t)(स्थिर काष्ठा gfs2_dirent *dent,
			    स्थिर काष्ठा qstr *name, व्योम *opaque);

पूर्णांक gfs2_dir_get_new_buffer(काष्ठा gfs2_inode *ip, u64 block,
			    काष्ठा buffer_head **bhp)
अणु
	काष्ठा buffer_head *bh;

	bh = gfs2_meta_new(ip->i_gl, block);
	gfs2_trans_add_meta(ip->i_gl, bh);
	gfs2_metatype_set(bh, GFS2_METATYPE_JD, GFS2_FORMAT_JD);
	gfs2_buffer_clear_tail(bh, माप(काष्ठा gfs2_meta_header));
	*bhp = bh;
	वापस 0;
पूर्ण

अटल पूर्णांक gfs2_dir_get_existing_buffer(काष्ठा gfs2_inode *ip, u64 block,
					काष्ठा buffer_head **bhp)
अणु
	काष्ठा buffer_head *bh;
	पूर्णांक error;

	error = gfs2_meta_पढ़ो(ip->i_gl, block, DIO_WAIT, 0, &bh);
	अगर (error)
		वापस error;
	अगर (gfs2_metatype_check(GFS2_SB(&ip->i_inode), bh, GFS2_METATYPE_JD)) अणु
		brअन्यथा(bh);
		वापस -EIO;
	पूर्ण
	*bhp = bh;
	वापस 0;
पूर्ण

अटल पूर्णांक gfs2_dir_ग_लिखो_stuffed(काष्ठा gfs2_inode *ip, स्थिर अक्षर *buf,
				  अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक size)
अणु
	काष्ठा buffer_head *dibh;
	पूर्णांक error;

	error = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (error)
		वापस error;

	gfs2_trans_add_meta(ip->i_gl, dibh);
	स_नकल(dibh->b_data + offset + माप(काष्ठा gfs2_dinode), buf, size);
	अगर (ip->i_inode.i_size < offset + size)
		i_size_ग_लिखो(&ip->i_inode, offset + size);
	ip->i_inode.i_mसमय = ip->i_inode.i_स_समय = current_समय(&ip->i_inode);
	gfs2_dinode_out(ip, dibh->b_data);

	brअन्यथा(dibh);

	वापस size;
पूर्ण



/**
 * gfs2_dir_ग_लिखो_data - Write directory inक्रमmation to the inode
 * @ip: The GFS2 inode
 * @buf: The buffer containing inक्रमmation to be written
 * @offset: The file offset to start writing at
 * @size: The amount of data to ग_लिखो
 *
 * Returns: The number of bytes correctly written or error code
 */
अटल पूर्णांक gfs2_dir_ग_लिखो_data(काष्ठा gfs2_inode *ip, स्थिर अक्षर *buf,
			       u64 offset, अचिन्हित पूर्णांक size)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	काष्ठा buffer_head *dibh;
	u64 lblock, dblock;
	u32 extlen = 0;
	अचिन्हित पूर्णांक o;
	पूर्णांक copied = 0;
	पूर्णांक error = 0;
	bool new = false;

	अगर (!size)
		वापस 0;

	अगर (gfs2_is_stuffed(ip) && offset + size <= gfs2_max_stuffed_size(ip))
		वापस gfs2_dir_ग_लिखो_stuffed(ip, buf, (अचिन्हित पूर्णांक)offset,
					      size);

	अगर (gfs2_निश्चित_warn(sdp, gfs2_is_jdata(ip)))
		वापस -EINVAL;

	अगर (gfs2_is_stuffed(ip)) अणु
		error = gfs2_unstuff_dinode(ip, शून्य);
		अगर (error)
			वापस error;
	पूर्ण

	lblock = offset;
	o = करो_भाग(lblock, sdp->sd_jbsize) + माप(काष्ठा gfs2_meta_header);

	जबतक (copied < size) अणु
		अचिन्हित पूर्णांक amount;
		काष्ठा buffer_head *bh;

		amount = size - copied;
		अगर (amount > sdp->sd_sb.sb_bsize - o)
			amount = sdp->sd_sb.sb_bsize - o;

		अगर (!extlen) अणु
			extlen = 1;
			error = gfs2_alloc_extent(&ip->i_inode, lblock, &dblock,
						  &extlen, &new);
			अगर (error)
				जाओ fail;
			error = -EIO;
			अगर (gfs2_निश्चित_withdraw(sdp, dblock))
				जाओ fail;
		पूर्ण

		अगर (amount == sdp->sd_jbsize || new)
			error = gfs2_dir_get_new_buffer(ip, dblock, &bh);
		अन्यथा
			error = gfs2_dir_get_existing_buffer(ip, dblock, &bh);

		अगर (error)
			जाओ fail;

		gfs2_trans_add_meta(ip->i_gl, bh);
		स_नकल(bh->b_data + o, buf, amount);
		brअन्यथा(bh);

		buf += amount;
		copied += amount;
		lblock++;
		dblock++;
		extlen--;

		o = माप(काष्ठा gfs2_meta_header);
	पूर्ण

out:
	error = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (error)
		वापस error;

	अगर (ip->i_inode.i_size < offset + copied)
		i_size_ग_लिखो(&ip->i_inode, offset + copied);
	ip->i_inode.i_mसमय = ip->i_inode.i_स_समय = current_समय(&ip->i_inode);

	gfs2_trans_add_meta(ip->i_gl, dibh);
	gfs2_dinode_out(ip, dibh->b_data);
	brअन्यथा(dibh);

	वापस copied;
fail:
	अगर (copied)
		जाओ out;
	वापस error;
पूर्ण

अटल पूर्णांक gfs2_dir_पढ़ो_stuffed(काष्ठा gfs2_inode *ip, __be64 *buf,
				 अचिन्हित पूर्णांक size)
अणु
	काष्ठा buffer_head *dibh;
	पूर्णांक error;

	error = gfs2_meta_inode_buffer(ip, &dibh);
	अगर (!error) अणु
		स_नकल(buf, dibh->b_data + माप(काष्ठा gfs2_dinode), size);
		brअन्यथा(dibh);
	पूर्ण

	वापस (error) ? error : size;
पूर्ण


/**
 * gfs2_dir_पढ़ो_data - Read a data from a directory inode
 * @ip: The GFS2 Inode
 * @buf: The buffer to place result पूर्णांकo
 * @size: Amount of data to transfer
 *
 * Returns: The amount of data actually copied or the error
 */
अटल पूर्णांक gfs2_dir_पढ़ो_data(काष्ठा gfs2_inode *ip, __be64 *buf,
			      अचिन्हित पूर्णांक size)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&ip->i_inode);
	u64 lblock, dblock;
	u32 extlen = 0;
	अचिन्हित पूर्णांक o;
	पूर्णांक copied = 0;
	पूर्णांक error = 0;

	अगर (gfs2_is_stuffed(ip))
		वापस gfs2_dir_पढ़ो_stuffed(ip, buf, size);

	अगर (gfs2_निश्चित_warn(sdp, gfs2_is_jdata(ip)))
		वापस -EINVAL;

	lblock = 0;
	o = करो_भाग(lblock, sdp->sd_jbsize) + माप(काष्ठा gfs2_meta_header);

	जबतक (copied < size) अणु
		अचिन्हित पूर्णांक amount;
		काष्ठा buffer_head *bh;

		amount = size - copied;
		अगर (amount > sdp->sd_sb.sb_bsize - o)
			amount = sdp->sd_sb.sb_bsize - o;

		अगर (!extlen) अणु
			extlen = 32;
			error = gfs2_get_extent(&ip->i_inode, lblock,
						&dblock, &extlen);
			अगर (error || !dblock)
				जाओ fail;
			BUG_ON(extlen < 1);
			bh = gfs2_meta_ra(ip->i_gl, dblock, extlen);
		पूर्ण अन्यथा अणु
			error = gfs2_meta_पढ़ो(ip->i_gl, dblock, DIO_WAIT, 0, &bh);
			अगर (error)
				जाओ fail;
		पूर्ण
		error = gfs2_metatype_check(sdp, bh, GFS2_METATYPE_JD);
		अगर (error) अणु
			brअन्यथा(bh);
			जाओ fail;
		पूर्ण
		dblock++;
		extlen--;
		स_नकल(buf, bh->b_data + o, amount);
		brअन्यथा(bh);
		buf += (amount/माप(__be64));
		copied += amount;
		lblock++;
		o = माप(काष्ठा gfs2_meta_header);
	पूर्ण

	वापस copied;
fail:
	वापस (copied) ? copied : error;
पूर्ण

/**
 * gfs2_dir_get_hash_table - Get poपूर्णांकer to the dir hash table
 * @ip: The inode in question
 *
 * Returns: The hash table or an error
 */

अटल __be64 *gfs2_dir_get_hash_table(काष्ठा gfs2_inode *ip)
अणु
	काष्ठा inode *inode = &ip->i_inode;
	पूर्णांक ret;
	u32 hsize;
	__be64 *hc;

	BUG_ON(!(ip->i_diskflags & GFS2_DIF_EXHASH));

	hc = ip->i_hash_cache;
	अगर (hc)
		वापस hc;

	hsize = BIT(ip->i_depth);
	hsize *= माप(__be64);
	अगर (hsize != i_size_पढ़ो(&ip->i_inode)) अणु
		gfs2_consist_inode(ip);
		वापस ERR_PTR(-EIO);
	पूर्ण

	hc = kदो_स्मृति(hsize, GFP_NOFS | __GFP_NOWARN);
	अगर (hc == शून्य)
		hc = __vदो_स्मृति(hsize, GFP_NOFS);

	अगर (hc == शून्य)
		वापस ERR_PTR(-ENOMEM);

	ret = gfs2_dir_पढ़ो_data(ip, hc, hsize);
	अगर (ret < 0) अणु
		kvमुक्त(hc);
		वापस ERR_PTR(ret);
	पूर्ण

	spin_lock(&inode->i_lock);
	अगर (likely(!ip->i_hash_cache)) अणु
		ip->i_hash_cache = hc;
		hc = शून्य;
	पूर्ण
	spin_unlock(&inode->i_lock);
	kvमुक्त(hc);

	वापस ip->i_hash_cache;
पूर्ण

/**
 * gfs2_dir_hash_inval - Invalidate dir hash
 * @ip: The directory inode
 *
 * Must be called with an exclusive glock, or during glock invalidation.
 */
व्योम gfs2_dir_hash_inval(काष्ठा gfs2_inode *ip)
अणु
	__be64 *hc;

	spin_lock(&ip->i_inode.i_lock);
	hc = ip->i_hash_cache;
	ip->i_hash_cache = शून्य;
	spin_unlock(&ip->i_inode.i_lock);

	kvमुक्त(hc);
पूर्ण

अटल अंतरभूत पूर्णांक gfs2_dirent_sentinel(स्थिर काष्ठा gfs2_dirent *dent)
अणु
	वापस dent->de_inum.no_addr == 0 || dent->de_inum.no_क्रमmal_ino == 0;
पूर्ण

अटल अंतरभूत पूर्णांक __gfs2_dirent_find(स्थिर काष्ठा gfs2_dirent *dent,
				     स्थिर काष्ठा qstr *name, पूर्णांक ret)
अणु
	अगर (!gfs2_dirent_sentinel(dent) &&
	    be32_to_cpu(dent->de_hash) == name->hash &&
	    be16_to_cpu(dent->de_name_len) == name->len &&
	    स_भेद(dent+1, name->name, name->len) == 0)
		वापस ret;
	वापस 0;
पूर्ण

अटल पूर्णांक gfs2_dirent_find(स्थिर काष्ठा gfs2_dirent *dent,
			    स्थिर काष्ठा qstr *name,
			    व्योम *opaque)
अणु
	वापस __gfs2_dirent_find(dent, name, 1);
पूर्ण

अटल पूर्णांक gfs2_dirent_prev(स्थिर काष्ठा gfs2_dirent *dent,
			    स्थिर काष्ठा qstr *name,
			    व्योम *opaque)
अणु
	वापस __gfs2_dirent_find(dent, name, 2);
पूर्ण

/*
 * name->name holds ptr to start of block.
 * name->len holds size of block.
 */
अटल पूर्णांक gfs2_dirent_last(स्थिर काष्ठा gfs2_dirent *dent,
			    स्थिर काष्ठा qstr *name,
			    व्योम *opaque)
अणु
	स्थिर अक्षर *start = name->name;
	स्थिर अक्षर *end = (स्थिर अक्षर *)dent + be16_to_cpu(dent->de_rec_len);
	अगर (name->len == (end - start))
		वापस 1;
	वापस 0;
पूर्ण

/* Look क्रम the dirent that contains the offset specअगरied in data. Once we
 * find that dirent, there must be space available there क्रम the new dirent */
अटल पूर्णांक gfs2_dirent_find_offset(स्थिर काष्ठा gfs2_dirent *dent,
				  स्थिर काष्ठा qstr *name,
				  व्योम *ptr)
अणु
	अचिन्हित required = GFS2_सूचीENT_SIZE(name->len);
	अचिन्हित actual = GFS2_सूचीENT_SIZE(be16_to_cpu(dent->de_name_len));
	अचिन्हित totlen = be16_to_cpu(dent->de_rec_len);

	अगर (ptr < (व्योम *)dent || ptr >= (व्योम *)dent + totlen)
		वापस 0;
	अगर (gfs2_dirent_sentinel(dent))
		actual = 0;
	अगर (ptr < (व्योम *)dent + actual)
		वापस -1;
	अगर ((व्योम *)dent + totlen >= ptr + required)
		वापस 1;
	वापस -1;
पूर्ण

अटल पूर्णांक gfs2_dirent_find_space(स्थिर काष्ठा gfs2_dirent *dent,
				  स्थिर काष्ठा qstr *name,
				  व्योम *opaque)
अणु
	अचिन्हित required = GFS2_सूचीENT_SIZE(name->len);
	अचिन्हित actual = GFS2_सूचीENT_SIZE(be16_to_cpu(dent->de_name_len));
	अचिन्हित totlen = be16_to_cpu(dent->de_rec_len);

	अगर (gfs2_dirent_sentinel(dent))
		actual = 0;
	अगर (totlen - actual >= required)
		वापस 1;
	वापस 0;
पूर्ण

काष्ठा dirent_gather अणु
	स्थिर काष्ठा gfs2_dirent **pdent;
	अचिन्हित offset;
पूर्ण;

अटल पूर्णांक gfs2_dirent_gather(स्थिर काष्ठा gfs2_dirent *dent,
			      स्थिर काष्ठा qstr *name,
			      व्योम *opaque)
अणु
	काष्ठा dirent_gather *g = opaque;
	अगर (!gfs2_dirent_sentinel(dent)) अणु
		g->pdent[g->offset++] = dent;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Other possible things to check:
 * - Inode located within fileप्रणाली size (and on valid block)
 * - Valid directory entry type
 * Not sure how heavy-weight we want to make this... could also check
 * hash is correct क्रम example, but that would take a lot of extra समय.
 * For now the most important thing is to check that the various sizes
 * are correct.
 */
अटल पूर्णांक gfs2_check_dirent(काष्ठा gfs2_sbd *sdp,
			     काष्ठा gfs2_dirent *dent, अचिन्हित पूर्णांक offset,
			     अचिन्हित पूर्णांक size, अचिन्हित पूर्णांक len, पूर्णांक first)
अणु
	स्थिर अक्षर *msg = "gfs2_dirent too small";
	अगर (unlikely(size < माप(काष्ठा gfs2_dirent)))
		जाओ error;
	msg = "gfs2_dirent misaligned";
	अगर (unlikely(offset & 0x7))
		जाओ error;
	msg = "gfs2_dirent points beyond end of block";
	अगर (unlikely(offset + size > len))
		जाओ error;
	msg = "zero inode number";
	अगर (unlikely(!first && gfs2_dirent_sentinel(dent)))
		जाओ error;
	msg = "name length is greater than space in dirent";
	अगर (!gfs2_dirent_sentinel(dent) &&
	    unlikely(माप(काष्ठा gfs2_dirent)+be16_to_cpu(dent->de_name_len) >
		     size))
		जाओ error;
	वापस 0;
error:
	fs_warn(sdp, "%s: %s (%s)\n",
		__func__, msg, first ? "first in block" : "not first in block");
	वापस -EIO;
पूर्ण

अटल पूर्णांक gfs2_dirent_offset(काष्ठा gfs2_sbd *sdp, स्थिर व्योम *buf)
अणु
	स्थिर काष्ठा gfs2_meta_header *h = buf;
	पूर्णांक offset;

	BUG_ON(buf == शून्य);

	चयन(be32_to_cpu(h->mh_type)) अणु
	हाल GFS2_METATYPE_LF:
		offset = माप(काष्ठा gfs2_leaf);
		अवरोध;
	हाल GFS2_METATYPE_DI:
		offset = माप(काष्ठा gfs2_dinode);
		अवरोध;
	शेष:
		जाओ wrong_type;
	पूर्ण
	वापस offset;
wrong_type:
	fs_warn(sdp, "%s: wrong block type %u\n", __func__,
		be32_to_cpu(h->mh_type));
	वापस -1;
पूर्ण

अटल काष्ठा gfs2_dirent *gfs2_dirent_scan(काष्ठा inode *inode, व्योम *buf,
					    अचिन्हित पूर्णांक len, gfs2_dscan_t scan,
					    स्थिर काष्ठा qstr *name,
					    व्योम *opaque)
अणु
	काष्ठा gfs2_dirent *dent, *prev;
	अचिन्हित offset;
	अचिन्हित size;
	पूर्णांक ret = 0;

	ret = gfs2_dirent_offset(GFS2_SB(inode), buf);
	अगर (ret < 0)
		जाओ consist_inode;

	offset = ret;
	prev = शून्य;
	dent = buf + offset;
	size = be16_to_cpu(dent->de_rec_len);
	अगर (gfs2_check_dirent(GFS2_SB(inode), dent, offset, size, len, 1))
		जाओ consist_inode;
	करो अणु
		ret = scan(dent, name, opaque);
		अगर (ret)
			अवरोध;
		offset += size;
		अगर (offset == len)
			अवरोध;
		prev = dent;
		dent = buf + offset;
		size = be16_to_cpu(dent->de_rec_len);
		अगर (gfs2_check_dirent(GFS2_SB(inode), dent, offset, size,
				      len, 0))
			जाओ consist_inode;
	पूर्ण जबतक(1);

	चयन(ret) अणु
	हाल 0:
		वापस शून्य;
	हाल 1:
		वापस dent;
	हाल 2:
		वापस prev ? prev : dent;
	शेष:
		BUG_ON(ret > 0);
		वापस ERR_PTR(ret);
	पूर्ण

consist_inode:
	gfs2_consist_inode(GFS2_I(inode));
	वापस ERR_PTR(-EIO);
पूर्ण

अटल पूर्णांक dirent_check_reclen(काष्ठा gfs2_inode *dip,
			       स्थिर काष्ठा gfs2_dirent *d, स्थिर व्योम *end_p)
अणु
	स्थिर व्योम *ptr = d;
	u16 rec_len = be16_to_cpu(d->de_rec_len);

	अगर (unlikely(rec_len < माप(काष्ठा gfs2_dirent)))
		जाओ broken;
	ptr += rec_len;
	अगर (ptr < end_p)
		वापस rec_len;
	अगर (ptr == end_p)
		वापस -ENOENT;
broken:
	gfs2_consist_inode(dip);
	वापस -EIO;
पूर्ण

/**
 * dirent_next - Next dirent
 * @dip: the directory
 * @bh: The buffer
 * @dent: Poपूर्णांकer to list of dirents
 *
 * Returns: 0 on success, error code otherwise
 */

अटल पूर्णांक dirent_next(काष्ठा gfs2_inode *dip, काष्ठा buffer_head *bh,
		       काष्ठा gfs2_dirent **dent)
अणु
	काष्ठा gfs2_dirent *cur = *dent, *पंचांगp;
	अक्षर *bh_end = bh->b_data + bh->b_size;
	पूर्णांक ret;

	ret = dirent_check_reclen(dip, cur, bh_end);
	अगर (ret < 0)
		वापस ret;

	पंचांगp = (व्योम *)cur + ret;
	ret = dirent_check_reclen(dip, पंचांगp, bh_end);
	अगर (ret == -EIO)
		वापस ret;

        /* Only the first dent could ever have de_inum.no_addr == 0 */
	अगर (gfs2_dirent_sentinel(पंचांगp)) अणु
		gfs2_consist_inode(dip);
		वापस -EIO;
	पूर्ण

	*dent = पंचांगp;
	वापस 0;
पूर्ण

/**
 * dirent_del - Delete a dirent
 * @dip: The GFS2 inode
 * @bh: The buffer
 * @prev: The previous dirent
 * @cur: The current dirent
 *
 */

अटल व्योम dirent_del(काष्ठा gfs2_inode *dip, काष्ठा buffer_head *bh,
		       काष्ठा gfs2_dirent *prev, काष्ठा gfs2_dirent *cur)
अणु
	u16 cur_rec_len, prev_rec_len;

	अगर (gfs2_dirent_sentinel(cur)) अणु
		gfs2_consist_inode(dip);
		वापस;
	पूर्ण

	gfs2_trans_add_meta(dip->i_gl, bh);

	/* If there is no prev entry, this is the first entry in the block.
	   The de_rec_len is alपढ़ोy as big as it needs to be.  Just zero
	   out the inode number and वापस.  */

	अगर (!prev) अणु
		cur->de_inum.no_addr = 0;
		cur->de_inum.no_क्रमmal_ino = 0;
		वापस;
	पूर्ण

	/*  Combine this dentry with the previous one.  */

	prev_rec_len = be16_to_cpu(prev->de_rec_len);
	cur_rec_len = be16_to_cpu(cur->de_rec_len);

	अगर ((अक्षर *)prev + prev_rec_len != (अक्षर *)cur)
		gfs2_consist_inode(dip);
	अगर ((अक्षर *)cur + cur_rec_len > bh->b_data + bh->b_size)
		gfs2_consist_inode(dip);

	prev_rec_len += cur_rec_len;
	prev->de_rec_len = cpu_to_be16(prev_rec_len);
पूर्ण


अटल काष्ठा gfs2_dirent *करो_init_dirent(काष्ठा inode *inode,
					  काष्ठा gfs2_dirent *dent,
					  स्थिर काष्ठा qstr *name,
					  काष्ठा buffer_head *bh,
					  अचिन्हित offset)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_dirent *ndent;
	अचिन्हित totlen;

	totlen = be16_to_cpu(dent->de_rec_len);
	BUG_ON(offset + name->len > totlen);
	gfs2_trans_add_meta(ip->i_gl, bh);
	ndent = (काष्ठा gfs2_dirent *)((अक्षर *)dent + offset);
	dent->de_rec_len = cpu_to_be16(offset);
	gfs2_qstr2dirent(name, totlen - offset, ndent);
	वापस ndent;
पूर्ण


/*
 * Takes a dent from which to grab space as an argument. Returns the
 * newly created dent.
 */
अटल काष्ठा gfs2_dirent *gfs2_init_dirent(काष्ठा inode *inode,
					    काष्ठा gfs2_dirent *dent,
					    स्थिर काष्ठा qstr *name,
					    काष्ठा buffer_head *bh)
अणु
	अचिन्हित offset = 0;

	अगर (!gfs2_dirent_sentinel(dent))
		offset = GFS2_सूचीENT_SIZE(be16_to_cpu(dent->de_name_len));
	वापस करो_init_dirent(inode, dent, name, bh, offset);
पूर्ण

अटल काष्ठा gfs2_dirent *gfs2_dirent_split_alloc(काष्ठा inode *inode,
						   काष्ठा buffer_head *bh,
						   स्थिर काष्ठा qstr *name,
						   व्योम *ptr)
अणु
	काष्ठा gfs2_dirent *dent;
	dent = gfs2_dirent_scan(inode, bh->b_data, bh->b_size,
				gfs2_dirent_find_offset, name, ptr);
	अगर (IS_ERR_OR_शून्य(dent))
		वापस dent;
	वापस करो_init_dirent(inode, dent, name, bh,
			      (अचिन्हित)(ptr - (व्योम *)dent));
पूर्ण

अटल पूर्णांक get_leaf(काष्ठा gfs2_inode *dip, u64 leaf_no,
		    काष्ठा buffer_head **bhp)
अणु
	पूर्णांक error;

	error = gfs2_meta_पढ़ो(dip->i_gl, leaf_no, DIO_WAIT, 0, bhp);
	अगर (!error && gfs2_metatype_check(GFS2_SB(&dip->i_inode), *bhp, GFS2_METATYPE_LF)) अणु
		/* pr_info("block num=%llu\n", leaf_no); */
		error = -EIO;
	पूर्ण

	वापस error;
पूर्ण

/**
 * get_leaf_nr - Get a leaf number associated with the index
 * @dip: The GFS2 inode
 * @index: hash table index of the targeted leaf
 * @leaf_out: Resulting leaf block number
 *
 * Returns: 0 on success, error code otherwise
 */

अटल पूर्णांक get_leaf_nr(काष्ठा gfs2_inode *dip, u32 index, u64 *leaf_out)
अणु
	__be64 *hash;
	पूर्णांक error;

	hash = gfs2_dir_get_hash_table(dip);
	error = PTR_ERR_OR_ZERO(hash);

	अगर (!error)
		*leaf_out = be64_to_cpu(*(hash + index));

	वापस error;
पूर्ण

अटल पूर्णांक get_first_leaf(काष्ठा gfs2_inode *dip, u32 index,
			  काष्ठा buffer_head **bh_out)
अणु
	u64 leaf_no;
	पूर्णांक error;

	error = get_leaf_nr(dip, index, &leaf_no);
	अगर (!error)
		error = get_leaf(dip, leaf_no, bh_out);

	वापस error;
पूर्ण

अटल काष्ठा gfs2_dirent *gfs2_dirent_search(काष्ठा inode *inode,
					      स्थिर काष्ठा qstr *name,
					      gfs2_dscan_t scan,
					      काष्ठा buffer_head **pbh)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा gfs2_dirent *dent;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	पूर्णांक error;

	अगर (ip->i_diskflags & GFS2_DIF_EXHASH) अणु
		काष्ठा gfs2_leaf *leaf;
		अचिन्हित पूर्णांक hsize = BIT(ip->i_depth);
		अचिन्हित पूर्णांक index;
		u64 ln;
		अगर (hsize * माप(u64) != i_size_पढ़ो(inode)) अणु
			gfs2_consist_inode(ip);
			वापस ERR_PTR(-EIO);
		पूर्ण

		index = name->hash >> (32 - ip->i_depth);
		error = get_first_leaf(ip, index, &bh);
		अगर (error)
			वापस ERR_PTR(error);
		करो अणु
			dent = gfs2_dirent_scan(inode, bh->b_data, bh->b_size,
						scan, name, शून्य);
			अगर (dent)
				जाओ got_dent;
			leaf = (काष्ठा gfs2_leaf *)bh->b_data;
			ln = be64_to_cpu(leaf->lf_next);
			brअन्यथा(bh);
			अगर (!ln)
				अवरोध;

			error = get_leaf(ip, ln, &bh);
		पूर्ण जबतक(!error);

		वापस error ? ERR_PTR(error) : शून्य;
	पूर्ण


	error = gfs2_meta_inode_buffer(ip, &bh);
	अगर (error)
		वापस ERR_PTR(error);
	dent = gfs2_dirent_scan(inode, bh->b_data, bh->b_size, scan, name, शून्य);
got_dent:
	अगर (IS_ERR_OR_शून्य(dent)) अणु
		brअन्यथा(bh);
		bh = शून्य;
	पूर्ण
	*pbh = bh;
	वापस dent;
पूर्ण

अटल काष्ठा gfs2_leaf *new_leaf(काष्ठा inode *inode, काष्ठा buffer_head **pbh, u16 depth)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	अचिन्हित पूर्णांक n = 1;
	u64 bn;
	पूर्णांक error;
	काष्ठा buffer_head *bh;
	काष्ठा gfs2_leaf *leaf;
	काष्ठा gfs2_dirent *dent;
	काष्ठा बारpec64 tv = current_समय(inode);

	error = gfs2_alloc_blocks(ip, &bn, &n, 0, शून्य);
	अगर (error)
		वापस शून्य;
	bh = gfs2_meta_new(ip->i_gl, bn);
	अगर (!bh)
		वापस शून्य;

	gfs2_trans_हटाओ_revoke(GFS2_SB(inode), bn, 1);
	gfs2_trans_add_meta(ip->i_gl, bh);
	gfs2_metatype_set(bh, GFS2_METATYPE_LF, GFS2_FORMAT_LF);
	leaf = (काष्ठा gfs2_leaf *)bh->b_data;
	leaf->lf_depth = cpu_to_be16(depth);
	leaf->lf_entries = 0;
	leaf->lf_dirent_क्रमmat = cpu_to_be32(GFS2_FORMAT_DE);
	leaf->lf_next = 0;
	leaf->lf_inode = cpu_to_be64(ip->i_no_addr);
	leaf->lf_dist = cpu_to_be32(1);
	leaf->lf_nsec = cpu_to_be32(tv.tv_nsec);
	leaf->lf_sec = cpu_to_be64(tv.tv_sec);
	स_रखो(leaf->lf_reserved2, 0, माप(leaf->lf_reserved2));
	dent = (काष्ठा gfs2_dirent *)(leaf+1);
	gfs2_qstr2dirent(&empty_name, bh->b_size - माप(काष्ठा gfs2_leaf), dent);
	*pbh = bh;
	वापस leaf;
पूर्ण

/**
 * dir_make_exhash - Convert a stuffed directory पूर्णांकo an ExHash directory
 * @inode: The directory inode to be converted to exhash
 *
 * Returns: 0 on success, error code otherwise
 */

अटल पूर्णांक dir_make_exhash(काष्ठा inode *inode)
अणु
	काष्ठा gfs2_inode *dip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा gfs2_dirent *dent;
	काष्ठा qstr args;
	काष्ठा buffer_head *bh, *dibh;
	काष्ठा gfs2_leaf *leaf;
	पूर्णांक y;
	u32 x;
	__be64 *lp;
	u64 bn;
	पूर्णांक error;

	error = gfs2_meta_inode_buffer(dip, &dibh);
	अगर (error)
		वापस error;

	/*  Turn over a new leaf  */

	leaf = new_leaf(inode, &bh, 0);
	अगर (!leaf)
		वापस -ENOSPC;
	bn = bh->b_blocknr;

	gfs2_निश्चित(sdp, dip->i_entries < BIT(16));
	leaf->lf_entries = cpu_to_be16(dip->i_entries);

	/*  Copy dirents  */

	gfs2_buffer_copy_tail(bh, माप(काष्ठा gfs2_leaf), dibh,
			     माप(काष्ठा gfs2_dinode));

	/*  Find last entry  */

	x = 0;
	args.len = bh->b_size - माप(काष्ठा gfs2_dinode) +
		   माप(काष्ठा gfs2_leaf);
	args.name = bh->b_data;
	dent = gfs2_dirent_scan(&dip->i_inode, bh->b_data, bh->b_size,
				gfs2_dirent_last, &args, शून्य);
	अगर (!dent) अणु
		brअन्यथा(bh);
		brअन्यथा(dibh);
		वापस -EIO;
	पूर्ण
	अगर (IS_ERR(dent)) अणु
		brअन्यथा(bh);
		brअन्यथा(dibh);
		वापस PTR_ERR(dent);
	पूर्ण

	/*  Adjust the last dirent's record length
	   (Remember that dent still poपूर्णांकs to the last entry.)  */

	dent->de_rec_len = cpu_to_be16(be16_to_cpu(dent->de_rec_len) +
		माप(काष्ठा gfs2_dinode) -
		माप(काष्ठा gfs2_leaf));

	brअन्यथा(bh);

	/*  We're करोne with the new leaf block, now setup the new
	    hash table.  */

	gfs2_trans_add_meta(dip->i_gl, dibh);
	gfs2_buffer_clear_tail(dibh, माप(काष्ठा gfs2_dinode));

	lp = (__be64 *)(dibh->b_data + माप(काष्ठा gfs2_dinode));

	क्रम (x = sdp->sd_hash_ptrs; x--; lp++)
		*lp = cpu_to_be64(bn);

	i_size_ग_लिखो(inode, sdp->sd_sb.sb_bsize / 2);
	gfs2_add_inode_blocks(&dip->i_inode, 1);
	dip->i_diskflags |= GFS2_DIF_EXHASH;

	क्रम (x = sdp->sd_hash_ptrs, y = -1; x; x >>= 1, y++) ;
	dip->i_depth = y;

	gfs2_dinode_out(dip, dibh->b_data);

	brअन्यथा(dibh);

	वापस 0;
पूर्ण

/**
 * dir_split_leaf - Split a leaf block पूर्णांकo two
 * @inode: The directory inode to be split
 * @name: name of the dirent we're trying to insert
 *
 * Returns: 0 on success, error code on failure
 */

अटल पूर्णांक dir_split_leaf(काष्ठा inode *inode, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा gfs2_inode *dip = GFS2_I(inode);
	काष्ठा buffer_head *nbh, *obh, *dibh;
	काष्ठा gfs2_leaf *nleaf, *oleaf;
	काष्ठा gfs2_dirent *dent = शून्य, *prev = शून्य, *next = शून्य, *new;
	u32 start, len, half_len, भागider;
	u64 bn, leaf_no;
	__be64 *lp;
	u32 index;
	पूर्णांक x;
	पूर्णांक error;

	index = name->hash >> (32 - dip->i_depth);
	error = get_leaf_nr(dip, index, &leaf_no);
	अगर (error)
		वापस error;

	/*  Get the old leaf block  */
	error = get_leaf(dip, leaf_no, &obh);
	अगर (error)
		वापस error;

	oleaf = (काष्ठा gfs2_leaf *)obh->b_data;
	अगर (dip->i_depth == be16_to_cpu(oleaf->lf_depth)) अणु
		brअन्यथा(obh);
		वापस 1; /* can't split */
	पूर्ण

	gfs2_trans_add_meta(dip->i_gl, obh);

	nleaf = new_leaf(inode, &nbh, be16_to_cpu(oleaf->lf_depth) + 1);
	अगर (!nleaf) अणु
		brअन्यथा(obh);
		वापस -ENOSPC;
	पूर्ण
	bn = nbh->b_blocknr;

	/*  Compute the start and len of leaf poपूर्णांकers in the hash table.  */
	len = BIT(dip->i_depth - be16_to_cpu(oleaf->lf_depth));
	half_len = len >> 1;
	अगर (!half_len) अणु
		fs_warn(GFS2_SB(inode), "i_depth %u lf_depth %u index %u\n",
			dip->i_depth, be16_to_cpu(oleaf->lf_depth), index);
		gfs2_consist_inode(dip);
		error = -EIO;
		जाओ fail_brअन्यथा;
	पूर्ण

	start = (index & ~(len - 1));

	/* Change the poपूर्णांकers.
	   Don't bother distinguishing stuffed from non-stuffed.
	   This code is complicated enough alपढ़ोy. */
	lp = kदो_स्मृति_array(half_len, माप(__be64), GFP_NOFS);
	अगर (!lp) अणु
		error = -ENOMEM;
		जाओ fail_brअन्यथा;
	पूर्ण

	/*  Change the poपूर्णांकers  */
	क्रम (x = 0; x < half_len; x++)
		lp[x] = cpu_to_be64(bn);

	gfs2_dir_hash_inval(dip);

	error = gfs2_dir_ग_लिखो_data(dip, (अक्षर *)lp, start * माप(u64),
				    half_len * माप(u64));
	अगर (error != half_len * माप(u64)) अणु
		अगर (error >= 0)
			error = -EIO;
		जाओ fail_lpमुक्त;
	पूर्ण

	kमुक्त(lp);

	/*  Compute the भागider  */
	भागider = (start + half_len) << (32 - dip->i_depth);

	/*  Copy the entries  */
	dent = (काष्ठा gfs2_dirent *)(obh->b_data + माप(काष्ठा gfs2_leaf));

	करो अणु
		next = dent;
		अगर (dirent_next(dip, obh, &next))
			next = शून्य;

		अगर (!gfs2_dirent_sentinel(dent) &&
		    be32_to_cpu(dent->de_hash) < भागider) अणु
			काष्ठा qstr str;
			व्योम *ptr = ((अक्षर *)dent - obh->b_data) + nbh->b_data;
			str.name = (अक्षर*)(dent+1);
			str.len = be16_to_cpu(dent->de_name_len);
			str.hash = be32_to_cpu(dent->de_hash);
			new = gfs2_dirent_split_alloc(inode, nbh, &str, ptr);
			अगर (IS_ERR(new)) अणु
				error = PTR_ERR(new);
				अवरोध;
			पूर्ण

			new->de_inum = dent->de_inum; /* No endian worries */
			new->de_type = dent->de_type; /* No endian worries */
			be16_add_cpu(&nleaf->lf_entries, 1);

			dirent_del(dip, obh, prev, dent);

			अगर (!oleaf->lf_entries)
				gfs2_consist_inode(dip);
			be16_add_cpu(&oleaf->lf_entries, -1);

			अगर (!prev)
				prev = dent;
		पूर्ण अन्यथा अणु
			prev = dent;
		पूर्ण
		dent = next;
	पूर्ण जबतक (dent);

	oleaf->lf_depth = nleaf->lf_depth;

	error = gfs2_meta_inode_buffer(dip, &dibh);
	अगर (!gfs2_निश्चित_withdraw(GFS2_SB(&dip->i_inode), !error)) अणु
		gfs2_trans_add_meta(dip->i_gl, dibh);
		gfs2_add_inode_blocks(&dip->i_inode, 1);
		gfs2_dinode_out(dip, dibh->b_data);
		brअन्यथा(dibh);
	पूर्ण

	brअन्यथा(obh);
	brअन्यथा(nbh);

	वापस error;

fail_lpमुक्त:
	kमुक्त(lp);

fail_brअन्यथा:
	brअन्यथा(obh);
	brअन्यथा(nbh);
	वापस error;
पूर्ण

/**
 * dir_द्विगुन_exhash - Double size of ExHash table
 * @dip: The GFS2 dinode
 *
 * Returns: 0 on success, error code on failure
 */

अटल पूर्णांक dir_द्विगुन_exhash(काष्ठा gfs2_inode *dip)
अणु
	काष्ठा buffer_head *dibh;
	u32 hsize;
	u32 hsize_bytes;
	__be64 *hc;
	__be64 *hc2, *h;
	पूर्णांक x;
	पूर्णांक error = 0;

	hsize = BIT(dip->i_depth);
	hsize_bytes = hsize * माप(__be64);

	hc = gfs2_dir_get_hash_table(dip);
	अगर (IS_ERR(hc))
		वापस PTR_ERR(hc);

	hc2 = kदो_स्मृति_array(hsize_bytes, 2, GFP_NOFS | __GFP_NOWARN);
	अगर (hc2 == शून्य)
		hc2 = __vदो_स्मृति(hsize_bytes * 2, GFP_NOFS);

	अगर (!hc2)
		वापस -ENOMEM;

	h = hc2;
	error = gfs2_meta_inode_buffer(dip, &dibh);
	अगर (error)
		जाओ out_kमुक्त;

	क्रम (x = 0; x < hsize; x++) अणु
		*h++ = *hc;
		*h++ = *hc;
		hc++;
	पूर्ण

	error = gfs2_dir_ग_लिखो_data(dip, (अक्षर *)hc2, 0, hsize_bytes * 2);
	अगर (error != (hsize_bytes * 2))
		जाओ fail;

	gfs2_dir_hash_inval(dip);
	dip->i_hash_cache = hc2;
	dip->i_depth++;
	gfs2_dinode_out(dip, dibh->b_data);
	brअन्यथा(dibh);
	वापस 0;

fail:
	/* Replace original hash table & size */
	gfs2_dir_ग_लिखो_data(dip, (अक्षर *)hc, 0, hsize_bytes);
	i_size_ग_लिखो(&dip->i_inode, hsize_bytes);
	gfs2_dinode_out(dip, dibh->b_data);
	brअन्यथा(dibh);
out_kमुक्त:
	kvमुक्त(hc2);
	वापस error;
पूर्ण

/**
 * compare_dents - compare directory entries by hash value
 * @a: first dent
 * @b: second dent
 *
 * When comparing the hash entries of @a to @b:
 *   gt: वापसs 1
 *   lt: वापसs -1
 *   eq: वापसs 0
 */

अटल पूर्णांक compare_dents(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा gfs2_dirent *dent_a, *dent_b;
	u32 hash_a, hash_b;
	पूर्णांक ret = 0;

	dent_a = *(स्थिर काष्ठा gfs2_dirent **)a;
	hash_a = dent_a->de_cookie;

	dent_b = *(स्थिर काष्ठा gfs2_dirent **)b;
	hash_b = dent_b->de_cookie;

	अगर (hash_a > hash_b)
		ret = 1;
	अन्यथा अगर (hash_a < hash_b)
		ret = -1;
	अन्यथा अणु
		अचिन्हित पूर्णांक len_a = be16_to_cpu(dent_a->de_name_len);
		अचिन्हित पूर्णांक len_b = be16_to_cpu(dent_b->de_name_len);

		अगर (len_a > len_b)
			ret = 1;
		अन्यथा अगर (len_a < len_b)
			ret = -1;
		अन्यथा
			ret = स_भेद(dent_a + 1, dent_b + 1, len_a);
	पूर्ण

	वापस ret;
पूर्ण

/**
 * करो_filldir_मुख्य - पढ़ो out directory entries
 * @dip: The GFS2 inode
 * @ctx: what to feed the entries to
 * @darr: an array of काष्ठा gfs2_dirent poपूर्णांकers to पढ़ो
 * @entries: the number of entries in darr
 * @sort_start: index of the directory array to start our sort
 * @copied: poपूर्णांकer to पूर्णांक that's non-zero अगर a entry has been copied out
 *
 * Jump through some hoops to make sure that अगर there are hash collsions,
 * they are पढ़ो out at the beginning of a buffer.  We want to minimize
 * the possibility that they will fall पूर्णांकo dअगरferent सूची_पढ़ो buffers or
 * that someone will want to seek to that location.
 *
 * Returns: त्रुटि_सं, >0 अगर the actor tells you to stop
 */

अटल पूर्णांक करो_filldir_मुख्य(काष्ठा gfs2_inode *dip, काष्ठा dir_context *ctx,
			   काष्ठा gfs2_dirent **darr, u32 entries,
			   u32 sort_start, पूर्णांक *copied)
अणु
	स्थिर काष्ठा gfs2_dirent *dent, *dent_next;
	u64 off, off_next;
	अचिन्हित पूर्णांक x, y;
	पूर्णांक run = 0;

	अगर (sort_start < entries)
		sort(&darr[sort_start], entries - sort_start,
		     माप(काष्ठा gfs2_dirent *), compare_dents, शून्य);

	dent_next = darr[0];
	off_next = dent_next->de_cookie;

	क्रम (x = 0, y = 1; x < entries; x++, y++) अणु
		dent = dent_next;
		off = off_next;

		अगर (y < entries) अणु
			dent_next = darr[y];
			off_next = dent_next->de_cookie;

			अगर (off < ctx->pos)
				जारी;
			ctx->pos = off;

			अगर (off_next == off) अणु
				अगर (*copied && !run)
					वापस 1;
				run = 1;
			पूर्ण अन्यथा
				run = 0;
		पूर्ण अन्यथा अणु
			अगर (off < ctx->pos)
				जारी;
			ctx->pos = off;
		पूर्ण

		अगर (!dir_emit(ctx, (स्थिर अक्षर *)(dent + 1),
				be16_to_cpu(dent->de_name_len),
				be64_to_cpu(dent->de_inum.no_addr),
				be16_to_cpu(dent->de_type)))
			वापस 1;

		*copied = 1;
	पूर्ण

	/* Increment the ctx->pos by one, so the next समय we come पूर्णांकo the
	   करो_filldir fxn, we get the next entry instead of the last one in the
	   current leaf */

	ctx->pos++;

	वापस 0;
पूर्ण

अटल व्योम *gfs2_alloc_sort_buffer(अचिन्हित size)
अणु
	व्योम *ptr = शून्य;

	अगर (size < KMALLOC_MAX_SIZE)
		ptr = kदो_स्मृति(size, GFP_NOFS | __GFP_NOWARN);
	अगर (!ptr)
		ptr = __vदो_स्मृति(size, GFP_NOFS);
	वापस ptr;
पूर्ण


अटल पूर्णांक gfs2_set_cookies(काष्ठा gfs2_sbd *sdp, काष्ठा buffer_head *bh,
			    अचिन्हित leaf_nr, काष्ठा gfs2_dirent **darr,
			    अचिन्हित entries)
अणु
	पूर्णांक sort_id = -1;
	पूर्णांक i;
	
	क्रम (i = 0; i < entries; i++) अणु
		अचिन्हित offset;

		darr[i]->de_cookie = be32_to_cpu(darr[i]->de_hash);
		darr[i]->de_cookie = gfs2_disk_hash2offset(darr[i]->de_cookie);

		अगर (!sdp->sd_args.ar_loccookie)
			जारी;
		offset = (अक्षर *)(darr[i]) -
			(bh->b_data + gfs2_dirent_offset(sdp, bh->b_data));
		offset /= GFS2_MIN_सूचीENT_SIZE;
		offset += leaf_nr * sdp->sd_max_dents_per_leaf;
		अगर (offset >= GFS2_USE_HASH_FLAG ||
		    leaf_nr >= GFS2_USE_HASH_FLAG) अणु
			darr[i]->de_cookie |= GFS2_USE_HASH_FLAG;
			अगर (sort_id < 0)
				sort_id = i;
			जारी;
		पूर्ण
		darr[i]->de_cookie &= GFS2_HASH_INDEX_MASK;
		darr[i]->de_cookie |= offset;
	पूर्ण
	वापस sort_id;
पूर्ण	


अटल पूर्णांक gfs2_dir_पढ़ो_leaf(काष्ठा inode *inode, काष्ठा dir_context *ctx,
			      पूर्णांक *copied, अचिन्हित *depth,
			      u64 leaf_no)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा buffer_head *bh;
	काष्ठा gfs2_leaf *lf;
	अचिन्हित entries = 0, entries2 = 0;
	अचिन्हित leaves = 0, leaf = 0, offset, sort_offset;
	काष्ठा gfs2_dirent **darr, *dent;
	काष्ठा dirent_gather g;
	काष्ठा buffer_head **larr;
	पूर्णांक error, i, need_sort = 0, sort_id;
	u64 lfn = leaf_no;

	करो अणु
		error = get_leaf(ip, lfn, &bh);
		अगर (error)
			जाओ out;
		lf = (काष्ठा gfs2_leaf *)bh->b_data;
		अगर (leaves == 0)
			*depth = be16_to_cpu(lf->lf_depth);
		entries += be16_to_cpu(lf->lf_entries);
		leaves++;
		lfn = be64_to_cpu(lf->lf_next);
		brअन्यथा(bh);
	पूर्ण जबतक(lfn);

	अगर (*depth < GFS2_सूची_MAX_DEPTH || !sdp->sd_args.ar_loccookie) अणु
		need_sort = 1;
		sort_offset = 0;
	पूर्ण

	अगर (!entries)
		वापस 0;

	error = -ENOMEM;
	/*
	 * The extra 99 entries are not normally used, but are a buffer
	 * zone in हाल the number of entries in the leaf is corrupt.
	 * 99 is the maximum number of entries that can fit in a single
	 * leaf block.
	 */
	larr = gfs2_alloc_sort_buffer((leaves + entries + 99) * माप(व्योम *));
	अगर (!larr)
		जाओ out;
	darr = (काष्ठा gfs2_dirent **)(larr + leaves);
	g.pdent = (स्थिर काष्ठा gfs2_dirent **)darr;
	g.offset = 0;
	lfn = leaf_no;

	करो अणु
		error = get_leaf(ip, lfn, &bh);
		अगर (error)
			जाओ out_मुक्त;
		lf = (काष्ठा gfs2_leaf *)bh->b_data;
		lfn = be64_to_cpu(lf->lf_next);
		अगर (lf->lf_entries) अणु
			offset = g.offset;
			entries2 += be16_to_cpu(lf->lf_entries);
			dent = gfs2_dirent_scan(inode, bh->b_data, bh->b_size,
						gfs2_dirent_gather, शून्य, &g);
			error = PTR_ERR(dent);
			अगर (IS_ERR(dent))
				जाओ out_मुक्त;
			अगर (entries2 != g.offset) अणु
				fs_warn(sdp, "Number of entries corrupt in dir "
						"leaf %llu, entries2 (%u) != "
						"g.offset (%u)\n",
					(अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
					entries2, g.offset);
				gfs2_consist_inode(ip);
				error = -EIO;
				जाओ out_मुक्त;
			पूर्ण
			error = 0;
			sort_id = gfs2_set_cookies(sdp, bh, leaf, &darr[offset],
						   be16_to_cpu(lf->lf_entries));
			अगर (!need_sort && sort_id >= 0) अणु
				need_sort = 1;
				sort_offset = offset + sort_id;
			पूर्ण
			larr[leaf++] = bh;
		पूर्ण अन्यथा अणु
			larr[leaf++] = शून्य;
			brअन्यथा(bh);
		पूर्ण
	पूर्ण जबतक(lfn);

	BUG_ON(entries2 != entries);
	error = करो_filldir_मुख्य(ip, ctx, darr, entries, need_sort ?
				sort_offset : entries, copied);
out_मुक्त:
	क्रम(i = 0; i < leaf; i++)
		brअन्यथा(larr[i]);
	kvमुक्त(larr);
out:
	वापस error;
पूर्ण

/**
 * gfs2_dir_पढ़ोahead - Issue पढ़ो-ahead requests क्रम leaf blocks.
 * @inode: the directory inode
 * @hsize: hash table size
 * @index: index पूर्णांकo the hash table
 * @f_ra: पढ़ो-ahead parameters
 *
 * Note: we can't calculate each index like dir_e_read can because we don't
 * have the leaf, and thereक्रमe we करोn't have the depth, and thereक्रमe we
 * करोn't have the length. So we have to just पढ़ो enough ahead to make up
 * क्रम the loss of inक्रमmation.
 */
अटल व्योम gfs2_dir_पढ़ोahead(काष्ठा inode *inode, अचिन्हित hsize, u32 index,
			       काष्ठा file_ra_state *f_ra)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_glock *gl = ip->i_gl;
	काष्ठा buffer_head *bh;
	u64 blocknr = 0, last;
	अचिन्हित count;

	/* First check अगर we've alपढ़ोy पढ़ो-ahead क्रम the whole range. */
	अगर (index + MAX_RA_BLOCKS < f_ra->start)
		वापस;

	f_ra->start = max((pgoff_t)index, f_ra->start);
	क्रम (count = 0; count < MAX_RA_BLOCKS; count++) अणु
		अगर (f_ra->start >= hsize) /* अगर exceeded the hash table */
			अवरोध;

		last = blocknr;
		blocknr = be64_to_cpu(ip->i_hash_cache[f_ra->start]);
		f_ra->start++;
		अगर (blocknr == last)
			जारी;

		bh = gfs2_getbuf(gl, blocknr, 1);
		अगर (trylock_buffer(bh)) अणु
			अगर (buffer_uptodate(bh)) अणु
				unlock_buffer(bh);
				brअन्यथा(bh);
				जारी;
			पूर्ण
			bh->b_end_io = end_buffer_पढ़ो_sync;
			submit_bh(REQ_OP_READ,
				  REQ_RAHEAD | REQ_META | REQ_PRIO,
				  bh);
			जारी;
		पूर्ण
		brअन्यथा(bh);
	पूर्ण
पूर्ण

/**
 * dir_e_पढ़ो - Reads the entries from a directory पूर्णांकo a filldir buffer
 * @inode: the directory inode
 * @ctx: actor to feed the entries to
 * @f_ra: पढ़ो-ahead parameters
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक dir_e_पढ़ो(काष्ठा inode *inode, काष्ठा dir_context *ctx,
		      काष्ठा file_ra_state *f_ra)
अणु
	काष्ठा gfs2_inode *dip = GFS2_I(inode);
	u32 hsize, len = 0;
	u32 hash, index;
	__be64 *lp;
	पूर्णांक copied = 0;
	पूर्णांक error = 0;
	अचिन्हित depth = 0;

	hsize = BIT(dip->i_depth);
	hash = gfs2_dir_offset2hash(ctx->pos);
	index = hash >> (32 - dip->i_depth);

	अगर (dip->i_hash_cache == शून्य)
		f_ra->start = 0;
	lp = gfs2_dir_get_hash_table(dip);
	अगर (IS_ERR(lp))
		वापस PTR_ERR(lp);

	gfs2_dir_पढ़ोahead(inode, hsize, index, f_ra);

	जबतक (index < hsize) अणु
		error = gfs2_dir_पढ़ो_leaf(inode, ctx,
					   &copied, &depth,
					   be64_to_cpu(lp[index]));
		अगर (error)
			अवरोध;

		len = BIT(dip->i_depth - depth);
		index = (index & ~(len - 1)) + len;
	पूर्ण

	अगर (error > 0)
		error = 0;
	वापस error;
पूर्ण

पूर्णांक gfs2_dir_पढ़ो(काष्ठा inode *inode, काष्ठा dir_context *ctx,
		  काष्ठा file_ra_state *f_ra)
अणु
	काष्ठा gfs2_inode *dip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	काष्ठा dirent_gather g;
	काष्ठा gfs2_dirent **darr, *dent;
	काष्ठा buffer_head *dibh;
	पूर्णांक copied = 0;
	पूर्णांक error;

	अगर (!dip->i_entries)
		वापस 0;

	अगर (dip->i_diskflags & GFS2_DIF_EXHASH)
		वापस dir_e_पढ़ो(inode, ctx, f_ra);

	अगर (!gfs2_is_stuffed(dip)) अणु
		gfs2_consist_inode(dip);
		वापस -EIO;
	पूर्ण

	error = gfs2_meta_inode_buffer(dip, &dibh);
	अगर (error)
		वापस error;

	error = -ENOMEM;
	/* 96 is max number of dirents which can be stuffed पूर्णांकo an inode */
	darr = kदो_स्मृति_array(96, माप(काष्ठा gfs2_dirent *), GFP_NOFS);
	अगर (darr) अणु
		g.pdent = (स्थिर काष्ठा gfs2_dirent **)darr;
		g.offset = 0;
		dent = gfs2_dirent_scan(inode, dibh->b_data, dibh->b_size,
					gfs2_dirent_gather, शून्य, &g);
		अगर (IS_ERR(dent)) अणु
			error = PTR_ERR(dent);
			जाओ out;
		पूर्ण
		अगर (dip->i_entries != g.offset) अणु
			fs_warn(sdp, "Number of entries corrupt in dir %llu, "
				"ip->i_entries (%u) != g.offset (%u)\n",
				(अचिन्हित दीर्घ दीर्घ)dip->i_no_addr,
				dip->i_entries,
				g.offset);
			gfs2_consist_inode(dip);
			error = -EIO;
			जाओ out;
		पूर्ण
		gfs2_set_cookies(sdp, dibh, 0, darr, dip->i_entries);
		error = करो_filldir_मुख्य(dip, ctx, darr,
					dip->i_entries, 0, &copied);
out:
		kमुक्त(darr);
	पूर्ण

	अगर (error > 0)
		error = 0;

	brअन्यथा(dibh);

	वापस error;
पूर्ण

/**
 * gfs2_dir_search - Search a directory
 * @dir: The GFS2 directory inode
 * @name: The name we are looking up
 * @fail_on_exist: Fail अगर the name exists rather than looking it up
 *
 * This routine searches a directory क्रम a file or another directory.
 * Assumes a glock is held on dip.
 *
 * Returns: त्रुटि_सं
 */

काष्ठा inode *gfs2_dir_search(काष्ठा inode *dir, स्थिर काष्ठा qstr *name,
			      bool fail_on_exist)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा gfs2_dirent *dent;
	u64 addr, क्रमmal_ino;
	u16 dtype;

	dent = gfs2_dirent_search(dir, name, gfs2_dirent_find, &bh);
	अगर (dent) अणु
		काष्ठा inode *inode;
		u16 rahead;

		अगर (IS_ERR(dent))
			वापस ERR_CAST(dent);
		dtype = be16_to_cpu(dent->de_type);
		rahead = be16_to_cpu(dent->de_rahead);
		addr = be64_to_cpu(dent->de_inum.no_addr);
		क्रमmal_ino = be64_to_cpu(dent->de_inum.no_क्रमmal_ino);
		brअन्यथा(bh);
		अगर (fail_on_exist)
			वापस ERR_PTR(-EEXIST);
		inode = gfs2_inode_lookup(dir->i_sb, dtype, addr, क्रमmal_ino,
					  GFS2_BLKST_FREE /* ignore */);
		अगर (!IS_ERR(inode))
			GFS2_I(inode)->i_rahead = rahead;
		वापस inode;
	पूर्ण
	वापस ERR_PTR(-ENOENT);
पूर्ण

पूर्णांक gfs2_dir_check(काष्ठा inode *dir, स्थिर काष्ठा qstr *name,
		   स्थिर काष्ठा gfs2_inode *ip)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा gfs2_dirent *dent;
	पूर्णांक ret = -ENOENT;

	dent = gfs2_dirent_search(dir, name, gfs2_dirent_find, &bh);
	अगर (dent) अणु
		अगर (IS_ERR(dent))
			वापस PTR_ERR(dent);
		अगर (ip) अणु
			अगर (be64_to_cpu(dent->de_inum.no_addr) != ip->i_no_addr)
				जाओ out;
			अगर (be64_to_cpu(dent->de_inum.no_क्रमmal_ino) !=
			    ip->i_no_क्रमmal_ino)
				जाओ out;
			अगर (unlikely(IF2DT(ip->i_inode.i_mode) !=
			    be16_to_cpu(dent->de_type))) अणु
				gfs2_consist_inode(GFS2_I(dir));
				ret = -EIO;
				जाओ out;
			पूर्ण
		पूर्ण
		ret = 0;
out:
		brअन्यथा(bh);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * dir_new_leaf - Add a new leaf onto hash chain
 * @inode: The directory
 * @name: The name we are adding
 *
 * This adds a new dir leaf onto an existing leaf when there is not
 * enough space to add a new dir entry. This is a last resort after
 * we've expanded the hash table to max size and also split existing
 * leaf blocks, so it will only occur क्रम very large directories.
 *
 * The dist parameter is set to 1 क्रम leaf blocks directly attached
 * to the hash table, 2 क्रम one layer of indirection, 3 क्रम two layers
 * etc. We are thus able to tell the dअगरference between an old leaf
 * with dist set to zero (i.e. "don't know") and a new one where we
 * set this inक्रमmation क्रम debug/fsck purposes.
 *
 * Returns: 0 on success, or -ve on error
 */

अटल पूर्णांक dir_new_leaf(काष्ठा inode *inode, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा buffer_head *bh, *obh;
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_leaf *leaf, *oleaf;
	u32 dist = 1;
	पूर्णांक error;
	u32 index;
	u64 bn;

	index = name->hash >> (32 - ip->i_depth);
	error = get_first_leaf(ip, index, &obh);
	अगर (error)
		वापस error;
	करो अणु
		dist++;
		oleaf = (काष्ठा gfs2_leaf *)obh->b_data;
		bn = be64_to_cpu(oleaf->lf_next);
		अगर (!bn)
			अवरोध;
		brअन्यथा(obh);
		error = get_leaf(ip, bn, &obh);
		अगर (error)
			वापस error;
	पूर्ण जबतक(1);

	gfs2_trans_add_meta(ip->i_gl, obh);

	leaf = new_leaf(inode, &bh, be16_to_cpu(oleaf->lf_depth));
	अगर (!leaf) अणु
		brअन्यथा(obh);
		वापस -ENOSPC;
	पूर्ण
	leaf->lf_dist = cpu_to_be32(dist);
	oleaf->lf_next = cpu_to_be64(bh->b_blocknr);
	brअन्यथा(bh);
	brअन्यथा(obh);

	error = gfs2_meta_inode_buffer(ip, &bh);
	अगर (error)
		वापस error;
	gfs2_trans_add_meta(ip->i_gl, bh);
	gfs2_add_inode_blocks(&ip->i_inode, 1);
	gfs2_dinode_out(ip, bh->b_data);
	brअन्यथा(bh);
	वापस 0;
पूर्ण

अटल u16 gfs2_inode_ra_len(स्थिर काष्ठा gfs2_inode *ip)
अणु
	u64 where = ip->i_no_addr + 1;
	अगर (ip->i_eattr == where)
		वापस 1;
	वापस 0;
पूर्ण

/**
 * gfs2_dir_add - Add new filename पूर्णांकo directory
 * @inode: The directory inode
 * @name: The new name
 * @nip: The GFS2 inode to be linked in to the directory
 * @da: The directory addition info
 *
 * If the call to gfs2_diradd_alloc_required resulted in there being
 * no need to allocate any new directory blocks, then it will contain
 * a poपूर्णांकer to the directory entry and the bh in which it resides. We
 * can use that without having to repeat the search. If there was no
 * मुक्त space, then we must now create more space.
 *
 * Returns: 0 on success, error code on failure
 */

पूर्णांक gfs2_dir_add(काष्ठा inode *inode, स्थिर काष्ठा qstr *name,
		 स्थिर काष्ठा gfs2_inode *nip, काष्ठा gfs2_diradd *da)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा buffer_head *bh = da->bh;
	काष्ठा gfs2_dirent *dent = da->dent;
	काष्ठा बारpec64 tv;
	काष्ठा gfs2_leaf *leaf;
	पूर्णांक error;

	जबतक(1) अणु
		अगर (da->bh == शून्य) अणु
			dent = gfs2_dirent_search(inode, name,
						  gfs2_dirent_find_space, &bh);
		पूर्ण
		अगर (dent) अणु
			अगर (IS_ERR(dent))
				वापस PTR_ERR(dent);
			dent = gfs2_init_dirent(inode, dent, name, bh);
			gfs2_inum_out(nip, dent);
			dent->de_type = cpu_to_be16(IF2DT(nip->i_inode.i_mode));
			dent->de_rahead = cpu_to_be16(gfs2_inode_ra_len(nip));
			tv = current_समय(&ip->i_inode);
			अगर (ip->i_diskflags & GFS2_DIF_EXHASH) अणु
				leaf = (काष्ठा gfs2_leaf *)bh->b_data;
				be16_add_cpu(&leaf->lf_entries, 1);
				leaf->lf_nsec = cpu_to_be32(tv.tv_nsec);
				leaf->lf_sec = cpu_to_be64(tv.tv_sec);
			पूर्ण
			da->dent = शून्य;
			da->bh = शून्य;
			brअन्यथा(bh);
			ip->i_entries++;
			ip->i_inode.i_mसमय = ip->i_inode.i_स_समय = tv;
			अगर (S_ISसूची(nip->i_inode.i_mode))
				inc_nlink(&ip->i_inode);
			mark_inode_dirty(inode);
			error = 0;
			अवरोध;
		पूर्ण
		अगर (!(ip->i_diskflags & GFS2_DIF_EXHASH)) अणु
			error = dir_make_exhash(inode);
			अगर (error)
				अवरोध;
			जारी;
		पूर्ण
		error = dir_split_leaf(inode, name);
		अगर (error == 0)
			जारी;
		अगर (error < 0)
			अवरोध;
		अगर (ip->i_depth < GFS2_सूची_MAX_DEPTH) अणु
			error = dir_द्विगुन_exhash(ip);
			अगर (error)
				अवरोध;
			error = dir_split_leaf(inode, name);
			अगर (error < 0)
				अवरोध;
			अगर (error == 0)
				जारी;
		पूर्ण
		error = dir_new_leaf(inode, name);
		अगर (!error)
			जारी;
		error = -ENOSPC;
		अवरोध;
	पूर्ण
	वापस error;
पूर्ण


/**
 * gfs2_dir_del - Delete a directory entry
 * @dip: The GFS2 inode
 * @dentry: The directory entry we want to delete
 *
 * Returns: 0 on success, error code on failure
 */

पूर्णांक gfs2_dir_del(काष्ठा gfs2_inode *dip, स्थिर काष्ठा dentry *dentry)
अणु
	स्थिर काष्ठा qstr *name = &dentry->d_name;
	काष्ठा gfs2_dirent *dent, *prev = शून्य;
	काष्ठा buffer_head *bh;
	काष्ठा बारpec64 tv = current_समय(&dip->i_inode);

	/* Returns _either_ the entry (अगर its first in block) or the
	   previous entry otherwise */
	dent = gfs2_dirent_search(&dip->i_inode, name, gfs2_dirent_prev, &bh);
	अगर (!dent) अणु
		gfs2_consist_inode(dip);
		वापस -EIO;
	पूर्ण
	अगर (IS_ERR(dent)) अणु
		gfs2_consist_inode(dip);
		वापस PTR_ERR(dent);
	पूर्ण
	/* If not first in block, adjust poपूर्णांकers accordingly */
	अगर (gfs2_dirent_find(dent, name, शून्य) == 0) अणु
		prev = dent;
		dent = (काष्ठा gfs2_dirent *)((अक्षर *)dent + be16_to_cpu(prev->de_rec_len));
	पूर्ण

	dirent_del(dip, bh, prev, dent);
	अगर (dip->i_diskflags & GFS2_DIF_EXHASH) अणु
		काष्ठा gfs2_leaf *leaf = (काष्ठा gfs2_leaf *)bh->b_data;
		u16 entries = be16_to_cpu(leaf->lf_entries);
		अगर (!entries)
			gfs2_consist_inode(dip);
		leaf->lf_entries = cpu_to_be16(--entries);
		leaf->lf_nsec = cpu_to_be32(tv.tv_nsec);
		leaf->lf_sec = cpu_to_be64(tv.tv_sec);
	पूर्ण
	brअन्यथा(bh);

	अगर (!dip->i_entries)
		gfs2_consist_inode(dip);
	dip->i_entries--;
	dip->i_inode.i_mसमय = dip->i_inode.i_स_समय = tv;
	अगर (d_is_dir(dentry))
		drop_nlink(&dip->i_inode);
	mark_inode_dirty(&dip->i_inode);

	वापस 0;
पूर्ण

/**
 * gfs2_dir_mvino - Change inode number of directory entry
 * @dip: The GFS2 directory inode
 * @filename: the filename to be moved
 * @nip: the new GFS2 inode
 * @new_type: the de_type of the new dirent
 *
 * This routine changes the inode number of a directory entry.  It's used
 * by नाम to change ".." when a directory is moved.
 * Assumes a glock is held on dvp.
 *
 * Returns: त्रुटि_सं
 */

पूर्णांक gfs2_dir_mvino(काष्ठा gfs2_inode *dip, स्थिर काष्ठा qstr *filename,
		   स्थिर काष्ठा gfs2_inode *nip, अचिन्हित पूर्णांक new_type)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा gfs2_dirent *dent;

	dent = gfs2_dirent_search(&dip->i_inode, filename, gfs2_dirent_find, &bh);
	अगर (!dent) अणु
		gfs2_consist_inode(dip);
		वापस -EIO;
	पूर्ण
	अगर (IS_ERR(dent))
		वापस PTR_ERR(dent);

	gfs2_trans_add_meta(dip->i_gl, bh);
	gfs2_inum_out(nip, dent);
	dent->de_type = cpu_to_be16(new_type);
	brअन्यथा(bh);

	dip->i_inode.i_mसमय = dip->i_inode.i_स_समय = current_समय(&dip->i_inode);
	mark_inode_dirty_sync(&dip->i_inode);
	वापस 0;
पूर्ण

/**
 * leaf_dealloc - Deallocate a directory leaf
 * @dip: the directory
 * @index: the hash table offset in the directory
 * @len: the number of poपूर्णांकers to this leaf
 * @leaf_no: the leaf number
 * @leaf_bh: buffer_head क्रम the starting leaf
 * @last_dealloc: 1 अगर this is the final dealloc क्रम the leaf, अन्यथा 0
 *
 * Returns: त्रुटि_सं
 */

अटल पूर्णांक leaf_dealloc(काष्ठा gfs2_inode *dip, u32 index, u32 len,
			u64 leaf_no, काष्ठा buffer_head *leaf_bh,
			पूर्णांक last_dealloc)
अणु
	काष्ठा gfs2_sbd *sdp = GFS2_SB(&dip->i_inode);
	काष्ठा gfs2_leaf *पंचांगp_leaf;
	काष्ठा gfs2_rgrp_list rlist;
	काष्ठा buffer_head *bh, *dibh;
	u64 blk, nblk;
	अचिन्हित पूर्णांक rg_blocks = 0, l_blocks = 0;
	अक्षर *ht;
	अचिन्हित पूर्णांक x, size = len * माप(u64);
	पूर्णांक error;

	error = gfs2_rindex_update(sdp);
	अगर (error)
		वापस error;

	स_रखो(&rlist, 0, माप(काष्ठा gfs2_rgrp_list));

	ht = kzalloc(size, GFP_NOFS | __GFP_NOWARN);
	अगर (ht == शून्य)
		ht = __vदो_स्मृति(size, GFP_NOFS | __GFP_NOWARN | __GFP_ZERO);
	अगर (!ht)
		वापस -ENOMEM;

	error = gfs2_quota_hold(dip, NO_UID_QUOTA_CHANGE, NO_GID_QUOTA_CHANGE);
	अगर (error)
		जाओ out;

	/*  Count the number of leaves  */
	bh = leaf_bh;

	क्रम (blk = leaf_no; blk; blk = nblk) अणु
		अगर (blk != leaf_no) अणु
			error = get_leaf(dip, blk, &bh);
			अगर (error)
				जाओ out_rlist;
		पूर्ण
		पंचांगp_leaf = (काष्ठा gfs2_leaf *)bh->b_data;
		nblk = be64_to_cpu(पंचांगp_leaf->lf_next);
		अगर (blk != leaf_no)
			brअन्यथा(bh);

		gfs2_rlist_add(dip, &rlist, blk);
		l_blocks++;
	पूर्ण

	gfs2_rlist_alloc(&rlist);

	क्रम (x = 0; x < rlist.rl_rgrps; x++) अणु
		काष्ठा gfs2_rgrpd *rgd = gfs2_glock2rgrp(rlist.rl_ghs[x].gh_gl);

		rg_blocks += rgd->rd_length;
	पूर्ण

	error = gfs2_glock_nq_m(rlist.rl_rgrps, rlist.rl_ghs);
	अगर (error)
		जाओ out_rlist;

	error = gfs2_trans_begin(sdp,
			rg_blocks + (DIV_ROUND_UP(size, sdp->sd_jbsize) + 1) +
			RES_DINODE + RES_STATFS + RES_QUOTA, RES_DINODE +
				 l_blocks);
	अगर (error)
		जाओ out_rg_gunlock;

	bh = leaf_bh;

	क्रम (blk = leaf_no; blk; blk = nblk) अणु
		काष्ठा gfs2_rgrpd *rgd;

		अगर (blk != leaf_no) अणु
			error = get_leaf(dip, blk, &bh);
			अगर (error)
				जाओ out_end_trans;
		पूर्ण
		पंचांगp_leaf = (काष्ठा gfs2_leaf *)bh->b_data;
		nblk = be64_to_cpu(पंचांगp_leaf->lf_next);
		अगर (blk != leaf_no)
			brअन्यथा(bh);

		rgd = gfs2_blk2rgrpd(sdp, blk, true);
		gfs2_मुक्त_meta(dip, rgd, blk, 1);
		gfs2_add_inode_blocks(&dip->i_inode, -1);
	पूर्ण

	error = gfs2_dir_ग_लिखो_data(dip, ht, index * माप(u64), size);
	अगर (error != size) अणु
		अगर (error >= 0)
			error = -EIO;
		जाओ out_end_trans;
	पूर्ण

	error = gfs2_meta_inode_buffer(dip, &dibh);
	अगर (error)
		जाओ out_end_trans;

	gfs2_trans_add_meta(dip->i_gl, dibh);
	/* On the last dealloc, make this a regular file in हाल we crash.
	   (We करोn't want to मुक्त these blocks a second समय.)  */
	अगर (last_dealloc)
		dip->i_inode.i_mode = S_IFREG;
	gfs2_dinode_out(dip, dibh->b_data);
	brअन्यथा(dibh);

out_end_trans:
	gfs2_trans_end(sdp);
out_rg_gunlock:
	gfs2_glock_dq_m(rlist.rl_rgrps, rlist.rl_ghs);
out_rlist:
	gfs2_rlist_मुक्त(&rlist);
	gfs2_quota_unhold(dip);
out:
	kvमुक्त(ht);
	वापस error;
पूर्ण

/**
 * gfs2_dir_exhash_dealloc - मुक्त all the leaf blocks in a directory
 * @dip: the directory
 *
 * Dealloc all on-disk directory leaves to FREEMETA state
 * Change on-disk inode type to "regular file"
 *
 * Returns: त्रुटि_सं
 */

पूर्णांक gfs2_dir_exhash_dealloc(काष्ठा gfs2_inode *dip)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा gfs2_leaf *leaf;
	u32 hsize, len;
	u32 index = 0, next_index;
	__be64 *lp;
	u64 leaf_no;
	पूर्णांक error = 0, last;

	hsize = BIT(dip->i_depth);

	lp = gfs2_dir_get_hash_table(dip);
	अगर (IS_ERR(lp))
		वापस PTR_ERR(lp);

	जबतक (index < hsize) अणु
		leaf_no = be64_to_cpu(lp[index]);
		अगर (leaf_no) अणु
			error = get_leaf(dip, leaf_no, &bh);
			अगर (error)
				जाओ out;
			leaf = (काष्ठा gfs2_leaf *)bh->b_data;
			len = BIT(dip->i_depth - be16_to_cpu(leaf->lf_depth));

			next_index = (index & ~(len - 1)) + len;
			last = ((next_index >= hsize) ? 1 : 0);
			error = leaf_dealloc(dip, index, len, leaf_no, bh,
					     last);
			brअन्यथा(bh);
			अगर (error)
				जाओ out;
			index = next_index;
		पूर्ण अन्यथा
			index++;
	पूर्ण

	अगर (index != hsize) अणु
		gfs2_consist_inode(dip);
		error = -EIO;
	पूर्ण

out:

	वापस error;
पूर्ण

/**
 * gfs2_diradd_alloc_required - find अगर adding entry will require an allocation
 * @inode: the directory inode being written to
 * @name: the filename that's going to be added
 * @da: The काष्ठाure to वापस dir alloc info
 *
 * Returns: 0 अगर ok, -ve on error
 */

पूर्णांक gfs2_diradd_alloc_required(काष्ठा inode *inode, स्थिर काष्ठा qstr *name,
			       काष्ठा gfs2_diradd *da)
अणु
	काष्ठा gfs2_inode *ip = GFS2_I(inode);
	काष्ठा gfs2_sbd *sdp = GFS2_SB(inode);
	स्थिर अचिन्हित पूर्णांक extra = माप(काष्ठा gfs2_dinode) - माप(काष्ठा gfs2_leaf);
	काष्ठा gfs2_dirent *dent;
	काष्ठा buffer_head *bh;

	da->nr_blocks = 0;
	da->bh = शून्य;
	da->dent = शून्य;

	dent = gfs2_dirent_search(inode, name, gfs2_dirent_find_space, &bh);
	अगर (!dent) अणु
		da->nr_blocks = sdp->sd_max_dirres;
		अगर (!(ip->i_diskflags & GFS2_DIF_EXHASH) &&
		    (GFS2_सूचीENT_SIZE(name->len) < extra))
			da->nr_blocks = 1;
		वापस 0;
	पूर्ण
	अगर (IS_ERR(dent))
		वापस PTR_ERR(dent);

	अगर (da->save_loc) अणु
		da->bh = bh;
		da->dent = dent;
	पूर्ण अन्यथा अणु
		brअन्यथा(bh);
	पूर्ण
	वापस 0;
पूर्ण

