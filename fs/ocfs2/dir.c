<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dir.c
 *
 * Creates, पढ़ोs, walks and deletes directory-nodes
 *
 * Copyright (C) 2002, 2004 Oracle.  All rights reserved.
 *
 *  Portions of this code from linux/fs/ext3/dir.c
 *
 *  Copyright (C) 1992, 1993, 1994, 1995
 *  Remy Card (card@masi.ibp.fr)
 *  Laborम_से_पre MASI - Institut Blaise pascal
 *  Universite Pierre et Marie Curie (Paris VI)
 *
 *   from
 *
 *   linux/fs/minix/dir.c
 *
 *   Copyright (C) 1991, 1992 Linus Torvalds
 */

#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/quotaops.h>
#समावेश <linux/sort.h>
#समावेश <linux/iversion.h>

#समावेश <cluster/masklog.h>

#समावेश "ocfs2.h"

#समावेश "alloc.h"
#समावेश "blockcheck.h"
#समावेश "dir.h"
#समावेश "dlmglue.h"
#समावेश "extent_map.h"
#समावेश "file.h"
#समावेश "inode.h"
#समावेश "journal.h"
#समावेश "namei.h"
#समावेश "suballoc.h"
#समावेश "super.h"
#समावेश "sysfile.h"
#समावेश "uptodate.h"
#समावेश "ocfs2_trace.h"

#समावेश "buffer_head_io.h"

#घोषणा NAMEI_RA_CHUNKS  2
#घोषणा NAMEI_RA_BLOCKS  4
#घोषणा NAMEI_RA_SIZE        (NAMEI_RA_CHUNKS * NAMEI_RA_BLOCKS)

अटल पूर्णांक ocfs2_करो_extend_dir(काष्ठा super_block *sb,
			       handle_t *handle,
			       काष्ठा inode *dir,
			       काष्ठा buffer_head *parent_fe_bh,
			       काष्ठा ocfs2_alloc_context *data_ac,
			       काष्ठा ocfs2_alloc_context *meta_ac,
			       काष्ठा buffer_head **new_bh);
अटल पूर्णांक ocfs2_dir_indexed(काष्ठा inode *inode);

/*
 * These are distinct checks because future versions of the file प्रणाली will
 * want to have a trailing dirent काष्ठाure independent of indexing.
 */
अटल पूर्णांक ocfs2_supports_dir_trailer(काष्ठा inode *dir)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);

	अगर (OCFS2_I(dir)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		वापस 0;

	वापस ocfs2_meta_ecc(osb) || ocfs2_dir_indexed(dir);
पूर्ण

/*
 * "new' here refers to the point at which we're creating a new
 * directory via "mkdir()", but also when we're expanding an अंतरभूत
 * directory. In either हाल, we करोn't yet have the indexing bit set
 * on the directory, so the standard checks will fail in when metaecc
 * is turned off. Only directory-initialization type functions should
 * use this then. Everything अन्यथा wants ocfs2_supports_dir_trailer()
 */
अटल पूर्णांक ocfs2_new_dir_wants_trailer(काष्ठा inode *dir)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);

	वापस ocfs2_meta_ecc(osb) ||
		ocfs2_supports_indexed_dirs(osb);
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_dir_trailer_blk_off(काष्ठा super_block *sb)
अणु
	वापस sb->s_blocksize - माप(काष्ठा ocfs2_dir_block_trailer);
पूर्ण

#घोषणा ocfs2_trailer_from_bh(_bh, _sb) ((काष्ठा ocfs2_dir_block_trailer *) ((_bh)->b_data + ocfs2_dir_trailer_blk_off((_sb))))

/* XXX ocfs2_block_dqtrailer() is similar but not quite - can we make
 * them more consistent? */
काष्ठा ocfs2_dir_block_trailer *ocfs2_dir_trailer_from_size(पूर्णांक blocksize,
							    व्योम *data)
अणु
	अक्षर *p = data;

	p += blocksize - माप(काष्ठा ocfs2_dir_block_trailer);
	वापस (काष्ठा ocfs2_dir_block_trailer *)p;
पूर्ण

/*
 * XXX: This is executed once on every dirent. We should consider optimizing
 * it.
 */
अटल पूर्णांक ocfs2_skip_dir_trailer(काष्ठा inode *dir,
				  काष्ठा ocfs2_dir_entry *de,
				  अचिन्हित दीर्घ offset,
				  अचिन्हित दीर्घ blklen)
अणु
	अचिन्हित दीर्घ toff = blklen - माप(काष्ठा ocfs2_dir_block_trailer);

	अगर (!ocfs2_supports_dir_trailer(dir))
		वापस 0;

	अगर (offset != toff)
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम ocfs2_init_dir_trailer(काष्ठा inode *inode,
				   काष्ठा buffer_head *bh, u16 rec_len)
अणु
	काष्ठा ocfs2_dir_block_trailer *trailer;

	trailer = ocfs2_trailer_from_bh(bh, inode->i_sb);
	म_नकल(trailer->db_signature, OCFS2_सूची_TRAILER_SIGNATURE);
	trailer->db_compat_rec_len =
			cpu_to_le16(माप(काष्ठा ocfs2_dir_block_trailer));
	trailer->db_parent_dinode = cpu_to_le64(OCFS2_I(inode)->ip_blkno);
	trailer->db_blkno = cpu_to_le64(bh->b_blocknr);
	trailer->db_मुक्त_rec_len = cpu_to_le16(rec_len);
पूर्ण
/*
 * Link an unindexed block with a dir trailer काष्ठाure पूर्णांकo the index मुक्त
 * list. This function will modअगरy dirdata_bh, but assumes you've alपढ़ोy
 * passed it to the journal.
 */
अटल पूर्णांक ocfs2_dx_dir_link_trailer(काष्ठा inode *dir, handle_t *handle,
				     काष्ठा buffer_head *dx_root_bh,
				     काष्ठा buffer_head *dirdata_bh)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_dx_root_block *dx_root;
	काष्ठा ocfs2_dir_block_trailer *trailer;

	ret = ocfs2_journal_access_dr(handle, INODE_CACHE(dir), dx_root_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	trailer = ocfs2_trailer_from_bh(dirdata_bh, dir->i_sb);
	dx_root = (काष्ठा ocfs2_dx_root_block *)dx_root_bh->b_data;

	trailer->db_मुक्त_next = dx_root->dr_मुक्त_blk;
	dx_root->dr_मुक्त_blk = cpu_to_le64(dirdata_bh->b_blocknr);

	ocfs2_journal_dirty(handle, dx_root_bh);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_मुक्त_list_at_root(काष्ठा ocfs2_dir_lookup_result *res)
अणु
	वापस res->dl_prev_leaf_bh == शून्य;
पूर्ण

व्योम ocfs2_मुक्त_dir_lookup_result(काष्ठा ocfs2_dir_lookup_result *res)
अणु
	brअन्यथा(res->dl_dx_root_bh);
	brअन्यथा(res->dl_leaf_bh);
	brअन्यथा(res->dl_dx_leaf_bh);
	brअन्यथा(res->dl_prev_leaf_bh);
पूर्ण

अटल पूर्णांक ocfs2_dir_indexed(काष्ठा inode *inode)
अणु
	अगर (OCFS2_I(inode)->ip_dyn_features & OCFS2_INDEXED_सूची_FL)
		वापस 1;
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_dx_root_अंतरभूत(काष्ठा ocfs2_dx_root_block *dx_root)
अणु
	वापस dx_root->dr_flags & OCFS2_DX_FLAG_INLINE;
पूर्ण

/*
 * Hashing code adapted from ext3
 */
#घोषणा DELTA 0x9E3779B9

अटल व्योम TEA_transक्रमm(__u32 buf[4], __u32 स्थिर in[])
अणु
	__u32	sum = 0;
	__u32	b0 = buf[0], b1 = buf[1];
	__u32	a = in[0], b = in[1], c = in[2], d = in[3];
	पूर्णांक	n = 16;

	करो अणु
		sum += DELTA;
		b0 += ((b1 << 4)+a) ^ (b1+sum) ^ ((b1 >> 5)+b);
		b1 += ((b0 << 4)+c) ^ (b0+sum) ^ ((b0 >> 5)+d);
	पूर्ण जबतक (--n);

	buf[0] += b0;
	buf[1] += b1;
पूर्ण

अटल व्योम str2hashbuf(स्थिर अक्षर *msg, पूर्णांक len, __u32 *buf, पूर्णांक num)
अणु
	__u32	pad, val;
	पूर्णांक	i;

	pad = (__u32)len | ((__u32)len << 8);
	pad |= pad << 16;

	val = pad;
	अगर (len > num*4)
		len = num * 4;
	क्रम (i = 0; i < len; i++) अणु
		अगर ((i % 4) == 0)
			val = pad;
		val = msg[i] + (val << 8);
		अगर ((i % 4) == 3) अणु
			*buf++ = val;
			val = pad;
			num--;
		पूर्ण
	पूर्ण
	अगर (--num >= 0)
		*buf++ = val;
	जबतक (--num >= 0)
		*buf++ = pad;
पूर्ण

अटल व्योम ocfs2_dx_dir_name_hash(काष्ठा inode *dir, स्थिर अक्षर *name, पूर्णांक len,
				   काष्ठा ocfs2_dx_hinfo *hinfo)
अणु
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	स्थिर अक्षर	*p;
	__u32		in[8], buf[4];

	/*
	 * XXX: Is this really necessary, अगर the index is never looked
	 * at by सूची_पढ़ो? Is a hash value of '0' a bad idea?
	 */
	अगर ((len == 1 && !म_भेदन(".", name, 1)) ||
	    (len == 2 && !म_भेदन("..", name, 2))) अणु
		buf[0] = buf[1] = 0;
		जाओ out;
	पूर्ण

#अगर_घोषित OCFS2_DEBUG_DX_सूचीS
	/*
	 * This makes it very easy to debug indexing problems. We
	 * should never allow this to be selected without hand editing
	 * this file though.
	 */
	buf[0] = buf[1] = len;
	जाओ out;
#पूर्ण_अगर

	स_नकल(buf, osb->osb_dx_seed, माप(buf));

	p = name;
	जबतक (len > 0) अणु
		str2hashbuf(p, len, in, 4);
		TEA_transक्रमm(buf, in);
		len -= 16;
		p += 16;
	पूर्ण

out:
	hinfo->major_hash = buf[0];
	hinfo->minor_hash = buf[1];
पूर्ण

/*
 * bh passed here can be an inode block or a dir data block, depending
 * on the inode अंतरभूत data flag.
 */
अटल पूर्णांक ocfs2_check_dir_entry(काष्ठा inode * dir,
				 काष्ठा ocfs2_dir_entry * de,
				 काष्ठा buffer_head * bh,
				 अचिन्हित दीर्घ offset)
अणु
	स्थिर अक्षर *error_msg = शून्य;
	स्थिर पूर्णांक rlen = le16_to_cpu(de->rec_len);

	अगर (unlikely(rlen < OCFS2_सूची_REC_LEN(1)))
		error_msg = "rec_len is smaller than minimal";
	अन्यथा अगर (unlikely(rlen % 4 != 0))
		error_msg = "rec_len % 4 != 0";
	अन्यथा अगर (unlikely(rlen < OCFS2_सूची_REC_LEN(de->name_len)))
		error_msg = "rec_len is too small for name_len";
	अन्यथा अगर (unlikely(
		 ((अक्षर *) de - bh->b_data) + rlen > dir->i_sb->s_blocksize))
		error_msg = "directory entry across blocks";

	अगर (unlikely(error_msg != शून्य))
		mlog(ML_ERROR, "bad entry in directory #%llu: %s - "
		     "offset=%lu, inode=%llu, rec_len=%d, name_len=%d\n",
		     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno, error_msg,
		     offset, (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(de->inode), rlen,
		     de->name_len);

	वापस error_msg == शून्य ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_match(पूर्णांक len,
			      स्थिर अक्षर * स्थिर name,
			      काष्ठा ocfs2_dir_entry *de)
अणु
	अगर (len != de->name_len)
		वापस 0;
	अगर (!de->inode)
		वापस 0;
	वापस !स_भेद(name, de->name, len);
पूर्ण

/*
 * Returns 0 अगर not found, -1 on failure, and 1 on success
 */
अटल अंतरभूत पूर्णांक ocfs2_search_dirblock(काष्ठा buffer_head *bh,
					काष्ठा inode *dir,
					स्थिर अक्षर *name, पूर्णांक namelen,
					अचिन्हित दीर्घ offset,
					अक्षर *first_de,
					अचिन्हित पूर्णांक bytes,
					काष्ठा ocfs2_dir_entry **res_dir)
अणु
	काष्ठा ocfs2_dir_entry *de;
	अक्षर *dlimit, *de_buf;
	पूर्णांक de_len;
	पूर्णांक ret = 0;

	de_buf = first_de;
	dlimit = de_buf + bytes;

	जबतक (de_buf < dlimit) अणु
		/* this code is executed quadratically often */
		/* करो minimal checking `by hand' */

		de = (काष्ठा ocfs2_dir_entry *) de_buf;

		अगर (de_buf + namelen <= dlimit &&
		    ocfs2_match(namelen, name, de)) अणु
			/* found a match - just to be sure, करो a full check */
			अगर (!ocfs2_check_dir_entry(dir, de, bh, offset)) अणु
				ret = -1;
				जाओ bail;
			पूर्ण
			*res_dir = de;
			ret = 1;
			जाओ bail;
		पूर्ण

		/* prevent looping on a bad block */
		de_len = le16_to_cpu(de->rec_len);
		अगर (de_len <= 0) अणु
			ret = -1;
			जाओ bail;
		पूर्ण

		de_buf += de_len;
		offset += de_len;
	पूर्ण

bail:
	trace_ocfs2_search_dirblock(ret);
	वापस ret;
पूर्ण

अटल काष्ठा buffer_head *ocfs2_find_entry_id(स्थिर अक्षर *name,
					       पूर्णांक namelen,
					       काष्ठा inode *dir,
					       काष्ठा ocfs2_dir_entry **res_dir)
अणु
	पूर्णांक ret, found;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_dinode *di;
	काष्ठा ocfs2_अंतरभूत_data *data;

	ret = ocfs2_पढ़ो_inode_block(dir, &di_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	data = &di->id2.i_data;

	found = ocfs2_search_dirblock(di_bh, dir, name, namelen, 0,
				      data->id_data, i_size_पढ़ो(dir), res_dir);
	अगर (found == 1)
		वापस di_bh;

	brअन्यथा(di_bh);
out:
	वापस शून्य;
पूर्ण

अटल पूर्णांक ocfs2_validate_dir_block(काष्ठा super_block *sb,
				    काष्ठा buffer_head *bh)
अणु
	पूर्णांक rc;
	काष्ठा ocfs2_dir_block_trailer *trailer =
		ocfs2_trailer_from_bh(bh, sb);


	/*
	 * We करोn't validate dirents here, that's handled
	 * in-place when the code walks them.
	 */
	trace_ocfs2_validate_dir_block((अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);

	BUG_ON(!buffer_uptodate(bh));

	/*
	 * If the ecc fails, we वापस the error but otherwise
	 * leave the fileप्रणाली running.  We know any error is
	 * local to this block.
	 *
	 * Note that we are safe to call this even अगर the directory
	 * करोesn't have a trailer.  Fileप्रणालीs without metaecc will करो
	 * nothing, and fileप्रणालीs with it will have one.
	 */
	rc = ocfs2_validate_meta_ecc(sb, bh->b_data, &trailer->db_check);
	अगर (rc)
		mlog(ML_ERROR, "Checksum failed for dinode %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);

	वापस rc;
पूर्ण

/*
 * Validate a directory trailer.
 *
 * We check the trailer here rather than in ocfs2_validate_dir_block()
 * because that function करोesn't have the inode to test.
 */
अटल पूर्णांक ocfs2_check_dir_trailer(काष्ठा inode *dir, काष्ठा buffer_head *bh)
अणु
	पूर्णांक rc = 0;
	काष्ठा ocfs2_dir_block_trailer *trailer;

	trailer = ocfs2_trailer_from_bh(bh, dir->i_sb);
	अगर (!OCFS2_IS_VALID_सूची_TRAILER(trailer)) अणु
		rc = ocfs2_error(dir->i_sb,
				 "Invalid dirblock #%llu: signature = %.*s\n",
				 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr, 7,
				 trailer->db_signature);
		जाओ out;
	पूर्ण
	अगर (le64_to_cpu(trailer->db_blkno) != bh->b_blocknr) अणु
		rc = ocfs2_error(dir->i_sb,
				 "Directory block #%llu has an invalid db_blkno of %llu\n",
				 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
				 (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(trailer->db_blkno));
		जाओ out;
	पूर्ण
	अगर (le64_to_cpu(trailer->db_parent_dinode) !=
	    OCFS2_I(dir)->ip_blkno) अणु
		rc = ocfs2_error(dir->i_sb,
				 "Directory block #%llu on dinode #%llu has an invalid parent_dinode of %llu\n",
				 (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
				 (अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno,
				 (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(trailer->db_blkno));
		जाओ out;
	पूर्ण
out:
	वापस rc;
पूर्ण

/*
 * This function क्रमces all errors to -EIO क्रम consistency with its
 * predecessor, ocfs2_bपढ़ो().  We haven't audited what वापसing the
 * real error codes would करो to callers.  We log the real codes with
 * mlog_त्रुटि_सं() beक्रमe we squash them.
 */
अटल पूर्णांक ocfs2_पढ़ो_dir_block(काष्ठा inode *inode, u64 v_block,
				काष्ठा buffer_head **bh, पूर्णांक flags)
अणु
	पूर्णांक rc = 0;
	काष्ठा buffer_head *पंचांगp = *bh;

	rc = ocfs2_पढ़ो_virt_blocks(inode, v_block, 1, &पंचांगp, flags,
				    ocfs2_validate_dir_block);
	अगर (rc) अणु
		mlog_त्रुटि_सं(rc);
		जाओ out;
	पूर्ण

	अगर (!(flags & OCFS2_BH_READAHEAD) &&
	    ocfs2_supports_dir_trailer(inode)) अणु
		rc = ocfs2_check_dir_trailer(inode, पंचांगp);
		अगर (rc) अणु
			अगर (!*bh)
				brअन्यथा(पंचांगp);
			mlog_त्रुटि_सं(rc);
			जाओ out;
		पूर्ण
	पूर्ण

	/* If ocfs2_पढ़ो_virt_blocks() got us a new bh, pass it up. */
	अगर (!*bh)
		*bh = पंचांगp;

out:
	वापस rc ? -EIO : 0;
पूर्ण

/*
 * Read the block at 'phys' which beदीर्घs to this directory
 * inode. This function करोes no भव->physical block translation -
 * what's passed in is assumed to be a valid directory block.
 */
अटल पूर्णांक ocfs2_पढ़ो_dir_block_direct(काष्ठा inode *dir, u64 phys,
				       काष्ठा buffer_head **bh)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *पंचांगp = *bh;

	ret = ocfs2_पढ़ो_block(INODE_CACHE(dir), phys, &पंचांगp,
			       ocfs2_validate_dir_block);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (ocfs2_supports_dir_trailer(dir)) अणु
		ret = ocfs2_check_dir_trailer(dir, पंचांगp);
		अगर (ret) अणु
			अगर (!*bh)
				brअन्यथा(पंचांगp);
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (!ret && !*bh)
		*bh = पंचांगp;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_validate_dx_root(काष्ठा super_block *sb,
				  काष्ठा buffer_head *bh)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_dx_root_block *dx_root;

	BUG_ON(!buffer_uptodate(bh));

	dx_root = (काष्ठा ocfs2_dx_root_block *) bh->b_data;

	ret = ocfs2_validate_meta_ecc(sb, bh->b_data, &dx_root->dr_check);
	अगर (ret) अणु
		mlog(ML_ERROR,
		     "Checksum failed for dir index root block %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
		वापस ret;
	पूर्ण

	अगर (!OCFS2_IS_VALID_DX_ROOT(dx_root)) अणु
		ret = ocfs2_error(sb,
				  "Dir Index Root # %llu has bad signature %.*s\n",
				  (अचिन्हित दीर्घ दीर्घ)le64_to_cpu(dx_root->dr_blkno),
				  7, dx_root->dr_signature);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_पढ़ो_dx_root(काष्ठा inode *dir, काष्ठा ocfs2_dinode *di,
			      काष्ठा buffer_head **dx_root_bh)
अणु
	पूर्णांक ret;
	u64 blkno = le64_to_cpu(di->i_dx_root);
	काष्ठा buffer_head *पंचांगp = *dx_root_bh;

	ret = ocfs2_पढ़ो_block(INODE_CACHE(dir), blkno, &पंचांगp,
			       ocfs2_validate_dx_root);

	/* If ocfs2_पढ़ो_block() got us a new bh, pass it up. */
	अगर (!ret && !*dx_root_bh)
		*dx_root_bh = पंचांगp;

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_validate_dx_leaf(काष्ठा super_block *sb,
				  काष्ठा buffer_head *bh)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_dx_leaf *dx_leaf = (काष्ठा ocfs2_dx_leaf *)bh->b_data;

	BUG_ON(!buffer_uptodate(bh));

	ret = ocfs2_validate_meta_ecc(sb, bh->b_data, &dx_leaf->dl_check);
	अगर (ret) अणु
		mlog(ML_ERROR,
		     "Checksum failed for dir index leaf block %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)bh->b_blocknr);
		वापस ret;
	पूर्ण

	अगर (!OCFS2_IS_VALID_DX_LEAF(dx_leaf)) अणु
		ret = ocfs2_error(sb, "Dir Index Leaf has bad signature %.*s\n",
				  7, dx_leaf->dl_signature);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_पढ़ो_dx_leaf(काष्ठा inode *dir, u64 blkno,
			      काष्ठा buffer_head **dx_leaf_bh)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *पंचांगp = *dx_leaf_bh;

	ret = ocfs2_पढ़ो_block(INODE_CACHE(dir), blkno, &पंचांगp,
			       ocfs2_validate_dx_leaf);

	/* If ocfs2_पढ़ो_block() got us a new bh, pass it up. */
	अगर (!ret && !*dx_leaf_bh)
		*dx_leaf_bh = पंचांगp;

	वापस ret;
पूर्ण

/*
 * Read a series of dx_leaf blocks. This expects all buffer_head
 * poपूर्णांकers to be शून्य on function entry.
 */
अटल पूर्णांक ocfs2_पढ़ो_dx_leaves(काष्ठा inode *dir, u64 start, पूर्णांक num,
				काष्ठा buffer_head **dx_leaf_bhs)
अणु
	पूर्णांक ret;

	ret = ocfs2_पढ़ो_blocks(INODE_CACHE(dir), start, num, dx_leaf_bhs, 0,
				ocfs2_validate_dx_leaf);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

	वापस ret;
पूर्ण

अटल काष्ठा buffer_head *ocfs2_find_entry_el(स्थिर अक्षर *name, पूर्णांक namelen,
					       काष्ठा inode *dir,
					       काष्ठा ocfs2_dir_entry **res_dir)
अणु
	काष्ठा super_block *sb;
	काष्ठा buffer_head *bh_use[NAMEI_RA_SIZE];
	काष्ठा buffer_head *bh, *ret = शून्य;
	अचिन्हित दीर्घ start, block, b;
	पूर्णांक ra_max = 0;		/* Number of bh's in the पढ़ोahead
				   buffer, bh_use[] */
	पूर्णांक ra_ptr = 0;		/* Current index पूर्णांकo पढ़ोahead
				   buffer */
	पूर्णांक num = 0;
	पूर्णांक nblocks, i;

	sb = dir->i_sb;

	nblocks = i_size_पढ़ो(dir) >> sb->s_blocksize_bits;
	start = OCFS2_I(dir)->ip_dir_start_lookup;
	अगर (start >= nblocks)
		start = 0;
	block = start;

restart:
	करो अणु
		/*
		 * We deal with the पढ़ो-ahead logic here.
		 */
		अगर (ra_ptr >= ra_max) अणु
			/* Refill the पढ़ोahead buffer */
			ra_ptr = 0;
			b = block;
			क्रम (ra_max = 0; ra_max < NAMEI_RA_SIZE; ra_max++) अणु
				/*
				 * Terminate अगर we reach the end of the
				 * directory and must wrap, or अगर our
				 * search has finished at this block.
				 */
				अगर (b >= nblocks || (num && block == start)) अणु
					bh_use[ra_max] = शून्य;
					अवरोध;
				पूर्ण
				num++;

				bh = शून्य;
				ocfs2_पढ़ो_dir_block(dir, b++, &bh,
							   OCFS2_BH_READAHEAD);
				bh_use[ra_max] = bh;
			पूर्ण
		पूर्ण
		अगर ((bh = bh_use[ra_ptr++]) == शून्य)
			जाओ next;
		अगर (ocfs2_पढ़ो_dir_block(dir, block, &bh, 0)) अणु
			/* पढ़ो error, skip block & hope क्रम the best.
			 * ocfs2_पढ़ो_dir_block() has released the bh. */
			mlog(ML_ERROR, "reading directory %llu, "
				    "offset %lu\n",
				    (अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno,
				    block);
			जाओ next;
		पूर्ण
		i = ocfs2_search_dirblock(bh, dir, name, namelen,
					  block << sb->s_blocksize_bits,
					  bh->b_data, sb->s_blocksize,
					  res_dir);
		अगर (i == 1) अणु
			OCFS2_I(dir)->ip_dir_start_lookup = block;
			ret = bh;
			जाओ cleanup_and_निकास;
		पूर्ण अन्यथा अणु
			brअन्यथा(bh);
			अगर (i < 0)
				जाओ cleanup_and_निकास;
		पूर्ण
	next:
		अगर (++block >= nblocks)
			block = 0;
	पूर्ण जबतक (block != start);

	/*
	 * If the directory has grown जबतक we were searching, then
	 * search the last part of the directory beक्रमe giving up.
	 */
	block = nblocks;
	nblocks = i_size_पढ़ो(dir) >> sb->s_blocksize_bits;
	अगर (block < nblocks) अणु
		start = 0;
		जाओ restart;
	पूर्ण

cleanup_and_निकास:
	/* Clean up the पढ़ो-ahead blocks */
	क्रम (; ra_ptr < ra_max; ra_ptr++)
		brअन्यथा(bh_use[ra_ptr]);

	trace_ocfs2_find_entry_el(ret);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_dx_dir_lookup_rec(काष्ठा inode *inode,
				   काष्ठा ocfs2_extent_list *el,
				   u32 major_hash,
				   u32 *ret_cpos,
				   u64 *ret_phys_blkno,
				   अचिन्हित पूर्णांक *ret_clen)
अणु
	पूर्णांक ret = 0, i, found;
	काष्ठा buffer_head *eb_bh = शून्य;
	काष्ठा ocfs2_extent_block *eb;
	काष्ठा ocfs2_extent_rec *rec = शून्य;

	अगर (el->l_tree_depth) अणु
		ret = ocfs2_find_leaf(INODE_CACHE(inode), el, major_hash,
				      &eb_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		eb = (काष्ठा ocfs2_extent_block *) eb_bh->b_data;
		el = &eb->h_list;

		अगर (el->l_tree_depth) अणु
			ret = ocfs2_error(inode->i_sb,
					  "Inode %lu has non zero tree depth in btree tree block %llu\n",
					  inode->i_ino,
					  (अचिन्हित दीर्घ दीर्घ)eb_bh->b_blocknr);
			जाओ out;
		पूर्ण
	पूर्ण

	found = 0;
	क्रम (i = le16_to_cpu(el->l_next_मुक्त_rec) - 1; i >= 0; i--) अणु
		rec = &el->l_recs[i];

		अगर (le32_to_cpu(rec->e_cpos) <= major_hash) अणु
			found = 1;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		ret = ocfs2_error(inode->i_sb,
				  "Inode %lu has bad extent record (%u, %u, 0) in btree\n",
				  inode->i_ino,
				  le32_to_cpu(rec->e_cpos),
				  ocfs2_rec_clusters(el, rec));
		जाओ out;
	पूर्ण

	अगर (ret_phys_blkno)
		*ret_phys_blkno = le64_to_cpu(rec->e_blkno);
	अगर (ret_cpos)
		*ret_cpos = le32_to_cpu(rec->e_cpos);
	अगर (ret_clen)
		*ret_clen = le16_to_cpu(rec->e_leaf_clusters);

out:
	brअन्यथा(eb_bh);
	वापस ret;
पूर्ण

/*
 * Returns the block index, from the start of the cluster which this
 * hash beदीर्घs too.
 */
अटल अंतरभूत अचिन्हित पूर्णांक __ocfs2_dx_dir_hash_idx(काष्ठा ocfs2_super *osb,
						   u32 minor_hash)
अणु
	वापस minor_hash & osb->osb_dx_mask;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ocfs2_dx_dir_hash_idx(काष्ठा ocfs2_super *osb,
					  काष्ठा ocfs2_dx_hinfo *hinfo)
अणु
	वापस __ocfs2_dx_dir_hash_idx(osb, hinfo->minor_hash);
पूर्ण

अटल पूर्णांक ocfs2_dx_dir_lookup(काष्ठा inode *inode,
			       काष्ठा ocfs2_extent_list *el,
			       काष्ठा ocfs2_dx_hinfo *hinfo,
			       u32 *ret_cpos,
			       u64 *ret_phys_blkno)
अणु
	पूर्णांक ret = 0;
	अचिन्हित पूर्णांक cend, clen;
	u32 cpos;
	u64 blkno;
	u32 name_hash = hinfo->major_hash;

	ret = ocfs2_dx_dir_lookup_rec(inode, el, name_hash, &cpos, &blkno,
				      &clen);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	cend = cpos + clen;
	अगर (name_hash >= cend) अणु
		/* We want the last cluster */
		blkno += ocfs2_clusters_to_blocks(inode->i_sb, clen - 1);
		cpos += clen - 1;
	पूर्ण अन्यथा अणु
		blkno += ocfs2_clusters_to_blocks(inode->i_sb,
						  name_hash - cpos);
		cpos = name_hash;
	पूर्ण

	/*
	 * We now have the cluster which should hold our entry. To
	 * find the exact block from the start of the cluster to
	 * search, we take the lower bits of the hash.
	 */
	blkno += ocfs2_dx_dir_hash_idx(OCFS2_SB(inode->i_sb), hinfo);

	अगर (ret_phys_blkno)
		*ret_phys_blkno = blkno;
	अगर (ret_cpos)
		*ret_cpos = cpos;

out:

	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_dx_dir_search(स्थिर अक्षर *name, पूर्णांक namelen,
			       काष्ठा inode *dir,
			       काष्ठा ocfs2_dx_root_block *dx_root,
			       काष्ठा ocfs2_dir_lookup_result *res)
अणु
	पूर्णांक ret, i, found;
	u64 phys;
	काष्ठा buffer_head *dx_leaf_bh = शून्य;
	काष्ठा ocfs2_dx_leaf *dx_leaf;
	काष्ठा ocfs2_dx_entry *dx_entry = शून्य;
	काष्ठा buffer_head *dir_ent_bh = शून्य;
	काष्ठा ocfs2_dir_entry *dir_ent = शून्य;
	काष्ठा ocfs2_dx_hinfo *hinfo = &res->dl_hinfo;
	काष्ठा ocfs2_extent_list *dr_el;
	काष्ठा ocfs2_dx_entry_list *entry_list;

	ocfs2_dx_dir_name_hash(dir, name, namelen, &res->dl_hinfo);

	अगर (ocfs2_dx_root_अंतरभूत(dx_root)) अणु
		entry_list = &dx_root->dr_entries;
		जाओ search;
	पूर्ण

	dr_el = &dx_root->dr_list;

	ret = ocfs2_dx_dir_lookup(dir, dr_el, hinfo, शून्य, &phys);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	trace_ocfs2_dx_dir_search((अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno,
				  namelen, name, hinfo->major_hash,
				  hinfo->minor_hash, (अचिन्हित दीर्घ दीर्घ)phys);

	ret = ocfs2_पढ़ो_dx_leaf(dir, phys, &dx_leaf_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	dx_leaf = (काष्ठा ocfs2_dx_leaf *) dx_leaf_bh->b_data;

	trace_ocfs2_dx_dir_search_leaf_info(
			le16_to_cpu(dx_leaf->dl_list.de_num_used),
			le16_to_cpu(dx_leaf->dl_list.de_count));

	entry_list = &dx_leaf->dl_list;

search:
	/*
	 * Empty leaf is legal, so no need to check क्रम that.
	 */
	found = 0;
	क्रम (i = 0; i < le16_to_cpu(entry_list->de_num_used); i++) अणु
		dx_entry = &entry_list->de_entries[i];

		अगर (hinfo->major_hash != le32_to_cpu(dx_entry->dx_major_hash)
		    || hinfo->minor_hash != le32_to_cpu(dx_entry->dx_minor_hash))
			जारी;

		/*
		 * Search unindexed leaf block now. We're not
		 * guaranteed to find anything.
		 */
		ret = ocfs2_पढ़ो_dir_block_direct(dir,
					  le64_to_cpu(dx_entry->dx_dirent_blk),
					  &dir_ent_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/*
		 * XXX: We should check the unindexed block here,
		 * beक्रमe using it.
		 */

		found = ocfs2_search_dirblock(dir_ent_bh, dir, name, namelen,
					      0, dir_ent_bh->b_data,
					      dir->i_sb->s_blocksize, &dir_ent);
		अगर (found == 1)
			अवरोध;

		अगर (found == -1) अणु
			/* This means we found a bad directory entry. */
			ret = -EIO;
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		brअन्यथा(dir_ent_bh);
		dir_ent_bh = शून्य;
	पूर्ण

	अगर (found <= 0) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	res->dl_leaf_bh = dir_ent_bh;
	res->dl_entry = dir_ent;
	res->dl_dx_leaf_bh = dx_leaf_bh;
	res->dl_dx_entry = dx_entry;

	ret = 0;
out:
	अगर (ret) अणु
		brअन्यथा(dx_leaf_bh);
		brअन्यथा(dir_ent_bh);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_find_entry_dx(स्थिर अक्षर *name, पूर्णांक namelen,
			       काष्ठा inode *dir,
			       काष्ठा ocfs2_dir_lookup_result *lookup)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_dinode *di;
	काष्ठा buffer_head *dx_root_bh = शून्य;
	काष्ठा ocfs2_dx_root_block *dx_root;

	ret = ocfs2_पढ़ो_inode_block(dir, &di_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;

	ret = ocfs2_पढ़ो_dx_root(dir, di, &dx_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	dx_root = (काष्ठा ocfs2_dx_root_block *) dx_root_bh->b_data;

	ret = ocfs2_dx_dir_search(name, namelen, dir, dx_root, lookup);
	अगर (ret) अणु
		अगर (ret != -ENOENT)
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	lookup->dl_dx_root_bh = dx_root_bh;
	dx_root_bh = शून्य;
out:
	brअन्यथा(di_bh);
	brअन्यथा(dx_root_bh);
	वापस ret;
पूर्ण

/*
 * Try to find an entry of the provided name within 'dir'.
 *
 * If nothing was found, -ENOENT is वापसed. Otherwise, zero is
 * वापसed and the काष्ठा 'res' will contain inक्रमmation useful to
 * other directory manipulation functions.
 *
 * Caller can NOT assume anything about the contents of the
 * buffer_heads - they are passed back only so that it can be passed
 * पूर्णांकo any one of the manipulation functions (add entry, delete
 * entry, etc). As an example, bh in the extent directory हाल is a
 * data block, in the अंतरभूत-data हाल it actually poपूर्णांकs to an inode,
 * in the indexed directory हाल, multiple buffers are involved.
 */
पूर्णांक ocfs2_find_entry(स्थिर अक्षर *name, पूर्णांक namelen,
		     काष्ठा inode *dir, काष्ठा ocfs2_dir_lookup_result *lookup)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा ocfs2_dir_entry *res_dir = शून्य;

	अगर (ocfs2_dir_indexed(dir))
		वापस ocfs2_find_entry_dx(name, namelen, dir, lookup);

	/*
	 * The unindexed dir code only uses part of the lookup
	 * काष्ठाure, so there's no reason to push it करोwn further
	 * than this.
	 */
	अगर (OCFS2_I(dir)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		bh = ocfs2_find_entry_id(name, namelen, dir, &res_dir);
	अन्यथा
		bh = ocfs2_find_entry_el(name, namelen, dir, &res_dir);

	अगर (bh == शून्य)
		वापस -ENOENT;

	lookup->dl_leaf_bh = bh;
	lookup->dl_entry = res_dir;
	वापस 0;
पूर्ण

/*
 * Update inode number and type of a previously found directory entry.
 */
पूर्णांक ocfs2_update_entry(काष्ठा inode *dir, handle_t *handle,
		       काष्ठा ocfs2_dir_lookup_result *res,
		       काष्ठा inode *new_entry_inode)
अणु
	पूर्णांक ret;
	ocfs2_journal_access_func access = ocfs2_journal_access_db;
	काष्ठा ocfs2_dir_entry *de = res->dl_entry;
	काष्ठा buffer_head *de_bh = res->dl_leaf_bh;

	/*
	 * The same code works fine क्रम both अंतरभूत-data and extent
	 * based directories, so no need to split this up.  The only
	 * dअगरference is the journal_access function.
	 */

	अगर (OCFS2_I(dir)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		access = ocfs2_journal_access_di;

	ret = access(handle, INODE_CACHE(dir), de_bh,
		     OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	de->inode = cpu_to_le64(OCFS2_I(new_entry_inode)->ip_blkno);
	ocfs2_set_de_type(de, new_entry_inode->i_mode);

	ocfs2_journal_dirty(handle, de_bh);

out:
	वापस ret;
पूर्ण

/*
 * __ocfs2_delete_entry deletes a directory entry by merging it with the
 * previous entry
 */
अटल पूर्णांक __ocfs2_delete_entry(handle_t *handle, काष्ठा inode *dir,
				काष्ठा ocfs2_dir_entry *de_del,
				काष्ठा buffer_head *bh, अक्षर *first_de,
				अचिन्हित पूर्णांक bytes)
अणु
	काष्ठा ocfs2_dir_entry *de, *pde;
	पूर्णांक i, status = -ENOENT;
	ocfs2_journal_access_func access = ocfs2_journal_access_db;

	अगर (OCFS2_I(dir)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		access = ocfs2_journal_access_di;

	i = 0;
	pde = शून्य;
	de = (काष्ठा ocfs2_dir_entry *) first_de;
	जबतक (i < bytes) अणु
		अगर (!ocfs2_check_dir_entry(dir, de, bh, i)) अणु
			status = -EIO;
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
		अगर (de == de_del)  अणु
			status = access(handle, INODE_CACHE(dir), bh,
					OCFS2_JOURNAL_ACCESS_WRITE);
			अगर (status < 0) अणु
				status = -EIO;
				mlog_त्रुटि_सं(status);
				जाओ bail;
			पूर्ण
			अगर (pde)
				le16_add_cpu(&pde->rec_len,
						le16_to_cpu(de->rec_len));
			de->inode = 0;
			inode_inc_iversion(dir);
			ocfs2_journal_dirty(handle, bh);
			जाओ bail;
		पूर्ण
		i += le16_to_cpu(de->rec_len);
		pde = de;
		de = (काष्ठा ocfs2_dir_entry *)((अक्षर *)de + le16_to_cpu(de->rec_len));
	पूर्ण
bail:
	वापस status;
पूर्ण

अटल अचिन्हित पूर्णांक ocfs2_figure_dirent_hole(काष्ठा ocfs2_dir_entry *de)
अणु
	अचिन्हित पूर्णांक hole;

	अगर (le64_to_cpu(de->inode) == 0)
		hole = le16_to_cpu(de->rec_len);
	अन्यथा
		hole = le16_to_cpu(de->rec_len) -
			OCFS2_सूची_REC_LEN(de->name_len);

	वापस hole;
पूर्ण

अटल पूर्णांक ocfs2_find_max_rec_len(काष्ठा super_block *sb,
				  काष्ठा buffer_head *dirblock_bh)
अणु
	पूर्णांक size, this_hole, largest_hole = 0;
	अक्षर *trailer, *de_buf, *limit, *start = dirblock_bh->b_data;
	काष्ठा ocfs2_dir_entry *de;

	trailer = (अक्षर *)ocfs2_trailer_from_bh(dirblock_bh, sb);
	size = ocfs2_dir_trailer_blk_off(sb);
	limit = start + size;
	de_buf = start;
	de = (काष्ठा ocfs2_dir_entry *)de_buf;
	करो अणु
		अगर (de_buf != trailer) अणु
			this_hole = ocfs2_figure_dirent_hole(de);
			अगर (this_hole > largest_hole)
				largest_hole = this_hole;
		पूर्ण

		de_buf += le16_to_cpu(de->rec_len);
		de = (काष्ठा ocfs2_dir_entry *)de_buf;
	पूर्ण जबतक (de_buf < limit);

	अगर (largest_hole >= OCFS2_सूची_MIN_REC_LEN)
		वापस largest_hole;
	वापस 0;
पूर्ण

अटल व्योम ocfs2_dx_list_हटाओ_entry(काष्ठा ocfs2_dx_entry_list *entry_list,
				       पूर्णांक index)
अणु
	पूर्णांक num_used = le16_to_cpu(entry_list->de_num_used);

	अगर (num_used == 1 || index == (num_used - 1))
		जाओ clear;

	स_हटाओ(&entry_list->de_entries[index],
		&entry_list->de_entries[index + 1],
		(num_used - index - 1)*माप(काष्ठा ocfs2_dx_entry));
clear:
	num_used--;
	स_रखो(&entry_list->de_entries[num_used], 0,
	       माप(काष्ठा ocfs2_dx_entry));
	entry_list->de_num_used = cpu_to_le16(num_used);
पूर्ण

अटल पूर्णांक ocfs2_delete_entry_dx(handle_t *handle, काष्ठा inode *dir,
				 काष्ठा ocfs2_dir_lookup_result *lookup)
अणु
	पूर्णांक ret, index, max_rec_len, add_to_मुक्त_list = 0;
	काष्ठा buffer_head *dx_root_bh = lookup->dl_dx_root_bh;
	काष्ठा buffer_head *leaf_bh = lookup->dl_leaf_bh;
	काष्ठा ocfs2_dx_leaf *dx_leaf;
	काष्ठा ocfs2_dx_entry *dx_entry = lookup->dl_dx_entry;
	काष्ठा ocfs2_dir_block_trailer *trailer;
	काष्ठा ocfs2_dx_root_block *dx_root;
	काष्ठा ocfs2_dx_entry_list *entry_list;

	/*
	 * This function माला_लो a bit messy because we might have to
	 * modअगरy the root block, regardless of whether the indexed
	 * entries are stored अंतरभूत.
	 */

	/*
	 * *Only* set 'entry_list' here, based on where we're looking
	 * क्रम the indexed entries. Later, we might still want to
	 * journal both blocks, based on मुक्त list state.
	 */
	dx_root = (काष्ठा ocfs2_dx_root_block *)dx_root_bh->b_data;
	अगर (ocfs2_dx_root_अंतरभूत(dx_root)) अणु
		entry_list = &dx_root->dr_entries;
	पूर्ण अन्यथा अणु
		dx_leaf = (काष्ठा ocfs2_dx_leaf *) lookup->dl_dx_leaf_bh->b_data;
		entry_list = &dx_leaf->dl_list;
	पूर्ण

	/* Neither of these are a disk corruption - that should have
	 * been caught by lookup, beक्रमe we got here. */
	BUG_ON(le16_to_cpu(entry_list->de_count) <= 0);
	BUG_ON(le16_to_cpu(entry_list->de_num_used) <= 0);

	index = (अक्षर *)dx_entry - (अक्षर *)entry_list->de_entries;
	index /= माप(*dx_entry);

	अगर (index >= le16_to_cpu(entry_list->de_num_used)) अणु
		mlog(ML_ERROR, "Dir %llu: Bad dx_entry ptr idx %d, (%p, %p)\n",
		     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno, index,
		     entry_list, dx_entry);
		वापस -EIO;
	पूर्ण

	/*
	 * We know that removal of this dirent will leave enough room
	 * क्रम a new one, so add this block to the मुक्त list अगर it
	 * isn't alपढ़ोy there.
	 */
	trailer = ocfs2_trailer_from_bh(leaf_bh, dir->i_sb);
	अगर (trailer->db_मुक्त_rec_len == 0)
		add_to_मुक्त_list = 1;

	/*
	 * Add the block holding our index पूर्णांकo the journal beक्रमe
	 * removing the unindexed entry. If we get an error वापस
	 * from __ocfs2_delete_entry(), then it hasn't हटाओd the
	 * entry yet. Likewise, successful वापस means we *must*
	 * हटाओ the indexed entry.
	 *
	 * We're also careful to journal the root tree block here as
	 * the entry count needs to be updated. Also, we might be
	 * adding to the start of the मुक्त list.
	 */
	ret = ocfs2_journal_access_dr(handle, INODE_CACHE(dir), dx_root_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (!ocfs2_dx_root_अंतरभूत(dx_root)) अणु
		ret = ocfs2_journal_access_dl(handle, INODE_CACHE(dir),
					      lookup->dl_dx_leaf_bh,
					      OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	trace_ocfs2_delete_entry_dx((अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno,
				    index);

	ret = __ocfs2_delete_entry(handle, dir, lookup->dl_entry,
				   leaf_bh, leaf_bh->b_data, leaf_bh->b_size);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	max_rec_len = ocfs2_find_max_rec_len(dir->i_sb, leaf_bh);
	trailer->db_मुक्त_rec_len = cpu_to_le16(max_rec_len);
	अगर (add_to_मुक्त_list) अणु
		trailer->db_मुक्त_next = dx_root->dr_मुक्त_blk;
		dx_root->dr_मुक्त_blk = cpu_to_le64(leaf_bh->b_blocknr);
		ocfs2_journal_dirty(handle, dx_root_bh);
	पूर्ण

	/* leaf_bh was journal_accessed क्रम us in __ocfs2_delete_entry */
	ocfs2_journal_dirty(handle, leaf_bh);

	le32_add_cpu(&dx_root->dr_num_entries, -1);
	ocfs2_journal_dirty(handle, dx_root_bh);

	ocfs2_dx_list_हटाओ_entry(entry_list, index);

	अगर (!ocfs2_dx_root_अंतरभूत(dx_root))
		ocfs2_journal_dirty(handle, lookup->dl_dx_leaf_bh);

out:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_delete_entry_id(handle_t *handle,
					काष्ठा inode *dir,
					काष्ठा ocfs2_dir_entry *de_del,
					काष्ठा buffer_head *bh)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_dinode *di;
	काष्ठा ocfs2_अंतरभूत_data *data;

	ret = ocfs2_पढ़ो_inode_block(dir, &di_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	data = &di->id2.i_data;

	ret = __ocfs2_delete_entry(handle, dir, de_del, bh, data->id_data,
				   i_size_पढ़ो(dir));

	brअन्यथा(di_bh);
out:
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक ocfs2_delete_entry_el(handle_t *handle,
					काष्ठा inode *dir,
					काष्ठा ocfs2_dir_entry *de_del,
					काष्ठा buffer_head *bh)
अणु
	वापस __ocfs2_delete_entry(handle, dir, de_del, bh, bh->b_data,
				    bh->b_size);
पूर्ण

/*
 * Delete a directory entry. Hide the details of directory
 * implementation from the caller.
 */
पूर्णांक ocfs2_delete_entry(handle_t *handle,
		       काष्ठा inode *dir,
		       काष्ठा ocfs2_dir_lookup_result *res)
अणु
	अगर (ocfs2_dir_indexed(dir))
		वापस ocfs2_delete_entry_dx(handle, dir, res);

	अगर (OCFS2_I(dir)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		वापस ocfs2_delete_entry_id(handle, dir, res->dl_entry,
					     res->dl_leaf_bh);

	वापस ocfs2_delete_entry_el(handle, dir, res->dl_entry,
				     res->dl_leaf_bh);
पूर्ण

/*
 * Check whether 'de' has enough room to hold an entry of
 * 'new_rec_len' bytes.
 */
अटल अंतरभूत पूर्णांक ocfs2_dirent_would_fit(काष्ठा ocfs2_dir_entry *de,
					 अचिन्हित पूर्णांक new_rec_len)
अणु
	अचिन्हित पूर्णांक de_really_used;

	/* Check whether this is an empty record with enough space */
	अगर (le64_to_cpu(de->inode) == 0 &&
	    le16_to_cpu(de->rec_len) >= new_rec_len)
		वापस 1;

	/*
	 * Record might have मुक्त space at the end which we can
	 * use.
	 */
	de_really_used = OCFS2_सूची_REC_LEN(de->name_len);
	अगर (le16_to_cpu(de->rec_len) >= (de_really_used + new_rec_len))
	    वापस 1;

	वापस 0;
पूर्ण

अटल व्योम ocfs2_dx_dir_leaf_insert_tail(काष्ठा ocfs2_dx_leaf *dx_leaf,
					  काष्ठा ocfs2_dx_entry *dx_new_entry)
अणु
	पूर्णांक i;

	i = le16_to_cpu(dx_leaf->dl_list.de_num_used);
	dx_leaf->dl_list.de_entries[i] = *dx_new_entry;

	le16_add_cpu(&dx_leaf->dl_list.de_num_used, 1);
पूर्ण

अटल व्योम ocfs2_dx_entry_list_insert(काष्ठा ocfs2_dx_entry_list *entry_list,
				       काष्ठा ocfs2_dx_hinfo *hinfo,
				       u64 dirent_blk)
अणु
	पूर्णांक i;
	काष्ठा ocfs2_dx_entry *dx_entry;

	i = le16_to_cpu(entry_list->de_num_used);
	dx_entry = &entry_list->de_entries[i];

	स_रखो(dx_entry, 0, माप(*dx_entry));
	dx_entry->dx_major_hash = cpu_to_le32(hinfo->major_hash);
	dx_entry->dx_minor_hash = cpu_to_le32(hinfo->minor_hash);
	dx_entry->dx_dirent_blk = cpu_to_le64(dirent_blk);

	le16_add_cpu(&entry_list->de_num_used, 1);
पूर्ण

अटल पूर्णांक __ocfs2_dx_dir_leaf_insert(काष्ठा inode *dir, handle_t *handle,
				      काष्ठा ocfs2_dx_hinfo *hinfo,
				      u64 dirent_blk,
				      काष्ठा buffer_head *dx_leaf_bh)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_dx_leaf *dx_leaf;

	ret = ocfs2_journal_access_dl(handle, INODE_CACHE(dir), dx_leaf_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	dx_leaf = (काष्ठा ocfs2_dx_leaf *)dx_leaf_bh->b_data;
	ocfs2_dx_entry_list_insert(&dx_leaf->dl_list, hinfo, dirent_blk);
	ocfs2_journal_dirty(handle, dx_leaf_bh);

out:
	वापस ret;
पूर्ण

अटल व्योम ocfs2_dx_अंतरभूत_root_insert(काष्ठा inode *dir, handle_t *handle,
					काष्ठा ocfs2_dx_hinfo *hinfo,
					u64 dirent_blk,
					काष्ठा ocfs2_dx_root_block *dx_root)
अणु
	ocfs2_dx_entry_list_insert(&dx_root->dr_entries, hinfo, dirent_blk);
पूर्ण

अटल पूर्णांक ocfs2_dx_dir_insert(काष्ठा inode *dir, handle_t *handle,
			       काष्ठा ocfs2_dir_lookup_result *lookup)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_dx_root_block *dx_root;
	काष्ठा buffer_head *dx_root_bh = lookup->dl_dx_root_bh;

	ret = ocfs2_journal_access_dr(handle, INODE_CACHE(dir), dx_root_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	dx_root = (काष्ठा ocfs2_dx_root_block *)lookup->dl_dx_root_bh->b_data;
	अगर (ocfs2_dx_root_अंतरभूत(dx_root)) अणु
		ocfs2_dx_अंतरभूत_root_insert(dir, handle,
					    &lookup->dl_hinfo,
					    lookup->dl_leaf_bh->b_blocknr,
					    dx_root);
	पूर्ण अन्यथा अणु
		ret = __ocfs2_dx_dir_leaf_insert(dir, handle, &lookup->dl_hinfo,
						 lookup->dl_leaf_bh->b_blocknr,
						 lookup->dl_dx_leaf_bh);
		अगर (ret)
			जाओ out;
	पूर्ण

	le32_add_cpu(&dx_root->dr_num_entries, 1);
	ocfs2_journal_dirty(handle, dx_root_bh);

out:
	वापस ret;
पूर्ण

अटल व्योम ocfs2_हटाओ_block_from_मुक्त_list(काष्ठा inode *dir,
				       handle_t *handle,
				       काष्ठा ocfs2_dir_lookup_result *lookup)
अणु
	काष्ठा ocfs2_dir_block_trailer *trailer, *prev;
	काष्ठा ocfs2_dx_root_block *dx_root;
	काष्ठा buffer_head *bh;

	trailer = ocfs2_trailer_from_bh(lookup->dl_leaf_bh, dir->i_sb);

	अगर (ocfs2_मुक्त_list_at_root(lookup)) अणु
		bh = lookup->dl_dx_root_bh;
		dx_root = (काष्ठा ocfs2_dx_root_block *)bh->b_data;
		dx_root->dr_मुक्त_blk = trailer->db_मुक्त_next;
	पूर्ण अन्यथा अणु
		bh = lookup->dl_prev_leaf_bh;
		prev = ocfs2_trailer_from_bh(bh, dir->i_sb);
		prev->db_मुक्त_next = trailer->db_मुक्त_next;
	पूर्ण

	trailer->db_मुक्त_rec_len = cpu_to_le16(0);
	trailer->db_मुक्त_next = cpu_to_le64(0);

	ocfs2_journal_dirty(handle, bh);
	ocfs2_journal_dirty(handle, lookup->dl_leaf_bh);
पूर्ण

/*
 * This expects that a journal ग_लिखो has been reserved on
 * lookup->dl_prev_leaf_bh or lookup->dl_dx_root_bh
 */
अटल व्योम ocfs2_recalc_मुक्त_list(काष्ठा inode *dir, handle_t *handle,
				   काष्ठा ocfs2_dir_lookup_result *lookup)
अणु
	पूर्णांक max_rec_len;
	काष्ठा ocfs2_dir_block_trailer *trailer;

	/* Walk dl_leaf_bh to figure out what the new मुक्त rec_len is. */
	max_rec_len = ocfs2_find_max_rec_len(dir->i_sb, lookup->dl_leaf_bh);
	अगर (max_rec_len) अणु
		/*
		 * There's still room in this block, so no need to हटाओ it
		 * from the मुक्त list. In this हाल, we just want to update
		 * the rec len accounting.
		 */
		trailer = ocfs2_trailer_from_bh(lookup->dl_leaf_bh, dir->i_sb);
		trailer->db_मुक्त_rec_len = cpu_to_le16(max_rec_len);
		ocfs2_journal_dirty(handle, lookup->dl_leaf_bh);
	पूर्ण अन्यथा अणु
		ocfs2_हटाओ_block_from_मुक्त_list(dir, handle, lookup);
	पूर्ण
पूर्ण

/* we करोn't always have a dentry क्रम what we want to add, so people
 * like orphan dir can call this instead.
 *
 * The lookup context must have been filled from
 * ocfs2_prepare_dir_क्रम_insert.
 */
पूर्णांक __ocfs2_add_entry(handle_t *handle,
		      काष्ठा inode *dir,
		      स्थिर अक्षर *name, पूर्णांक namelen,
		      काष्ठा inode *inode, u64 blkno,
		      काष्ठा buffer_head *parent_fe_bh,
		      काष्ठा ocfs2_dir_lookup_result *lookup)
अणु
	अचिन्हित दीर्घ offset;
	अचिन्हित लघु rec_len;
	काष्ठा ocfs2_dir_entry *de, *de1;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)parent_fe_bh->b_data;
	काष्ठा super_block *sb = dir->i_sb;
	पूर्णांक retval;
	अचिन्हित पूर्णांक size = sb->s_blocksize;
	काष्ठा buffer_head *insert_bh = lookup->dl_leaf_bh;
	अक्षर *data_start = insert_bh->b_data;

	अगर (!namelen)
		वापस -EINVAL;

	अगर (ocfs2_dir_indexed(dir)) अणु
		काष्ठा buffer_head *bh;

		/*
		 * An indexed dir may require that we update the मुक्त space
		 * list. Reserve a ग_लिखो to the previous node in the list so
		 * that we करोn't fail later.
		 *
		 * XXX: This can be either a dx_root_block, or an unindexed
		 * directory tree leaf block.
		 */
		अगर (ocfs2_मुक्त_list_at_root(lookup)) अणु
			bh = lookup->dl_dx_root_bh;
			retval = ocfs2_journal_access_dr(handle,
						 INODE_CACHE(dir), bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		पूर्ण अन्यथा अणु
			bh = lookup->dl_prev_leaf_bh;
			retval = ocfs2_journal_access_db(handle,
						 INODE_CACHE(dir), bh,
						 OCFS2_JOURNAL_ACCESS_WRITE);
		पूर्ण
		अगर (retval) अणु
			mlog_त्रुटि_सं(retval);
			वापस retval;
		पूर्ण
	पूर्ण अन्यथा अगर (OCFS2_I(dir)->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		data_start = di->id2.i_data.id_data;
		size = i_size_पढ़ो(dir);

		BUG_ON(insert_bh != parent_fe_bh);
	पूर्ण

	rec_len = OCFS2_सूची_REC_LEN(namelen);
	offset = 0;
	de = (काष्ठा ocfs2_dir_entry *) data_start;
	जबतक (1) अणु
		BUG_ON((अक्षर *)de >= (size + data_start));

		/* These checks should've alपढ़ोy been passed by the
		 * prepare function, but I guess we can leave them
		 * here anyway. */
		अगर (!ocfs2_check_dir_entry(dir, de, insert_bh, offset)) अणु
			retval = -ENOENT;
			जाओ bail;
		पूर्ण
		अगर (ocfs2_match(namelen, name, de)) अणु
			retval = -EEXIST;
			जाओ bail;
		पूर्ण

		/* We're guaranteed that we should have space, so we
		 * can't possibly have hit the trailer...right? */
		mlog_bug_on_msg(ocfs2_skip_dir_trailer(dir, de, offset, size),
				"Hit dir trailer trying to insert %.*s "
			        "(namelen %d) into directory %llu.  "
				"offset is %lu, trailer offset is %d\n",
				namelen, name, namelen,
				(अचिन्हित दीर्घ दीर्घ)parent_fe_bh->b_blocknr,
				offset, ocfs2_dir_trailer_blk_off(dir->i_sb));

		अगर (ocfs2_dirent_would_fit(de, rec_len)) अणु
			dir->i_mसमय = dir->i_स_समय = current_समय(dir);
			retval = ocfs2_mark_inode_dirty(handle, dir, parent_fe_bh);
			अगर (retval < 0) अणु
				mlog_त्रुटि_सं(retval);
				जाओ bail;
			पूर्ण

			अगर (insert_bh == parent_fe_bh)
				retval = ocfs2_journal_access_di(handle,
								 INODE_CACHE(dir),
								 insert_bh,
								 OCFS2_JOURNAL_ACCESS_WRITE);
			अन्यथा अणु
				retval = ocfs2_journal_access_db(handle,
								 INODE_CACHE(dir),
								 insert_bh,
					      OCFS2_JOURNAL_ACCESS_WRITE);

				अगर (!retval && ocfs2_dir_indexed(dir))
					retval = ocfs2_dx_dir_insert(dir,
								handle,
								lookup);
			पूर्ण

			अगर (retval) अणु
				mlog_त्रुटि_सं(retval);
				जाओ bail;
			पूर्ण

			/* By now the buffer is marked क्रम journaling */
			offset += le16_to_cpu(de->rec_len);
			अगर (le64_to_cpu(de->inode)) अणु
				de1 = (काष्ठा ocfs2_dir_entry *)((अक्षर *) de +
					OCFS2_सूची_REC_LEN(de->name_len));
				de1->rec_len =
					cpu_to_le16(le16_to_cpu(de->rec_len) -
					OCFS2_सूची_REC_LEN(de->name_len));
				de->rec_len = cpu_to_le16(OCFS2_सूची_REC_LEN(de->name_len));
				de = de1;
			पूर्ण
			de->file_type = FT_UNKNOWN;
			अगर (blkno) अणु
				de->inode = cpu_to_le64(blkno);
				ocfs2_set_de_type(de, inode->i_mode);
			पूर्ण अन्यथा
				de->inode = 0;
			de->name_len = namelen;
			स_नकल(de->name, name, namelen);

			अगर (ocfs2_dir_indexed(dir))
				ocfs2_recalc_मुक्त_list(dir, handle, lookup);

			inode_inc_iversion(dir);
			ocfs2_journal_dirty(handle, insert_bh);
			retval = 0;
			जाओ bail;
		पूर्ण

		offset += le16_to_cpu(de->rec_len);
		de = (काष्ठा ocfs2_dir_entry *) ((अक्षर *) de + le16_to_cpu(de->rec_len));
	पूर्ण

	/* when you think about it, the निश्चित above should prevent us
	 * from ever getting here. */
	retval = -ENOSPC;
bail:
	अगर (retval)
		mlog_त्रुटि_सं(retval);

	वापस retval;
पूर्ण

अटल पूर्णांक ocfs2_dir_क्रमeach_blk_id(काष्ठा inode *inode,
				    u64 *f_version,
				    काष्ठा dir_context *ctx)
अणु
	पूर्णांक ret, i;
	अचिन्हित दीर्घ offset = ctx->pos;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा ocfs2_dinode *di;
	काष्ठा ocfs2_अंतरभूत_data *data;
	काष्ठा ocfs2_dir_entry *de;

	ret = ocfs2_पढ़ो_inode_block(inode, &di_bh);
	अगर (ret) अणु
		mlog(ML_ERROR, "Unable to read inode block for dir %llu\n",
		     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);
		जाओ out;
	पूर्ण

	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	data = &di->id2.i_data;

	जबतक (ctx->pos < i_size_पढ़ो(inode)) अणु
		/* If the dir block has changed since the last call to
		 * सूची_पढ़ो(2), then we might be poपूर्णांकing to an invalid
		 * dirent right now.  Scan from the start of the block
		 * to make sure. */
		अगर (!inode_eq_iversion(inode, *f_version)) अणु
			क्रम (i = 0; i < i_size_पढ़ो(inode) && i < offset; ) अणु
				de = (काष्ठा ocfs2_dir_entry *)
					(data->id_data + i);
				/* It's too expensive to करो a full
				 * dirent test each समय round this
				 * loop, but we करो have to test at
				 * least that it is non-zero.  A
				 * failure will be detected in the
				 * dirent test below. */
				अगर (le16_to_cpu(de->rec_len) <
				    OCFS2_सूची_REC_LEN(1))
					अवरोध;
				i += le16_to_cpu(de->rec_len);
			पूर्ण
			ctx->pos = offset = i;
			*f_version = inode_query_iversion(inode);
		पूर्ण

		de = (काष्ठा ocfs2_dir_entry *) (data->id_data + ctx->pos);
		अगर (!ocfs2_check_dir_entry(inode, de, di_bh, ctx->pos)) अणु
			/* On error, skip the f_pos to the end. */
			ctx->pos = i_size_पढ़ो(inode);
			अवरोध;
		पूर्ण
		offset += le16_to_cpu(de->rec_len);
		अगर (le64_to_cpu(de->inode)) अणु
			अगर (!dir_emit(ctx, de->name, de->name_len,
				      le64_to_cpu(de->inode),
				      fs_ftype_to_dtype(de->file_type)))
				जाओ out;
		पूर्ण
		ctx->pos += le16_to_cpu(de->rec_len);
	पूर्ण
out:
	brअन्यथा(di_bh);
	वापस 0;
पूर्ण

/*
 * NOTE: This function can be called against unindexed directories,
 * and indexed ones.
 */
अटल पूर्णांक ocfs2_dir_क्रमeach_blk_el(काष्ठा inode *inode,
				    u64 *f_version,
				    काष्ठा dir_context *ctx,
				    bool persist)
अणु
	अचिन्हित दीर्घ offset, blk, last_ra_blk = 0;
	पूर्णांक i;
	काष्ठा buffer_head * bh, * पंचांगp;
	काष्ठा ocfs2_dir_entry * de;
	काष्ठा super_block * sb = inode->i_sb;
	अचिन्हित पूर्णांक ra_sectors = 16;
	पूर्णांक stored = 0;

	bh = शून्य;

	offset = ctx->pos & (sb->s_blocksize - 1);

	जबतक (ctx->pos < i_size_पढ़ो(inode)) अणु
		blk = ctx->pos >> sb->s_blocksize_bits;
		अगर (ocfs2_पढ़ो_dir_block(inode, blk, &bh, 0)) अणु
			/* Skip the corrupt dirblock and keep trying */
			ctx->pos += sb->s_blocksize - offset;
			जारी;
		पूर्ण

		/* The idea here is to begin with 8k पढ़ो-ahead and to stay
		 * 4k ahead of our current position.
		 *
		 * TODO: Use the pagecache क्रम this. We just need to
		 * make sure it's cluster-safe... */
		अगर (!last_ra_blk
		    || (((last_ra_blk - blk) << 9) <= (ra_sectors / 2))) अणु
			क्रम (i = ra_sectors >> (sb->s_blocksize_bits - 9);
			     i > 0; i--) अणु
				पंचांगp = शून्य;
				अगर (!ocfs2_पढ़ो_dir_block(inode, ++blk, &पंचांगp,
							  OCFS2_BH_READAHEAD))
					brअन्यथा(पंचांगp);
			पूर्ण
			last_ra_blk = blk;
			ra_sectors = 8;
		पूर्ण

		/* If the dir block has changed since the last call to
		 * सूची_पढ़ो(2), then we might be poपूर्णांकing to an invalid
		 * dirent right now.  Scan from the start of the block
		 * to make sure. */
		अगर (!inode_eq_iversion(inode, *f_version)) अणु
			क्रम (i = 0; i < sb->s_blocksize && i < offset; ) अणु
				de = (काष्ठा ocfs2_dir_entry *) (bh->b_data + i);
				/* It's too expensive to करो a full
				 * dirent test each समय round this
				 * loop, but we करो have to test at
				 * least that it is non-zero.  A
				 * failure will be detected in the
				 * dirent test below. */
				अगर (le16_to_cpu(de->rec_len) <
				    OCFS2_सूची_REC_LEN(1))
					अवरोध;
				i += le16_to_cpu(de->rec_len);
			पूर्ण
			offset = i;
			ctx->pos = (ctx->pos & ~(sb->s_blocksize - 1))
				| offset;
			*f_version = inode_query_iversion(inode);
		पूर्ण

		जबतक (ctx->pos < i_size_पढ़ो(inode)
		       && offset < sb->s_blocksize) अणु
			de = (काष्ठा ocfs2_dir_entry *) (bh->b_data + offset);
			अगर (!ocfs2_check_dir_entry(inode, de, bh, offset)) अणु
				/* On error, skip the f_pos to the
				   next block. */
				ctx->pos = (ctx->pos | (sb->s_blocksize - 1)) + 1;
				अवरोध;
			पूर्ण
			अगर (le64_to_cpu(de->inode)) अणु
				अगर (!dir_emit(ctx, de->name,
						de->name_len,
						le64_to_cpu(de->inode),
					fs_ftype_to_dtype(de->file_type))) अणु
					brअन्यथा(bh);
					वापस 0;
				पूर्ण
				stored++;
			पूर्ण
			offset += le16_to_cpu(de->rec_len);
			ctx->pos += le16_to_cpu(de->rec_len);
		पूर्ण
		offset = 0;
		brअन्यथा(bh);
		bh = शून्य;
		अगर (!persist && stored)
			अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_dir_क्रमeach_blk(काष्ठा inode *inode, u64 *f_version,
				 काष्ठा dir_context *ctx,
				 bool persist)
अणु
	अगर (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		वापस ocfs2_dir_क्रमeach_blk_id(inode, f_version, ctx);
	वापस ocfs2_dir_क्रमeach_blk_el(inode, f_version, ctx, persist);
पूर्ण

/*
 * This is पूर्णांकended to be called from inside other kernel functions,
 * so we fake some arguments.
 */
पूर्णांक ocfs2_dir_क्रमeach(काष्ठा inode *inode, काष्ठा dir_context *ctx)
अणु
	u64 version = inode_query_iversion(inode);
	ocfs2_dir_क्रमeach_blk(inode, &version, ctx, true);
	वापस 0;
पूर्ण

/*
 * ocfs2_सूची_पढ़ो()
 *
 */
पूर्णांक ocfs2_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	पूर्णांक error = 0;
	काष्ठा inode *inode = file_inode(file);
	पूर्णांक lock_level = 0;

	trace_ocfs2_सूची_पढ़ो((अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);

	error = ocfs2_inode_lock_aसमय(inode, file->f_path.mnt, &lock_level, 1);
	अगर (lock_level && error >= 0) अणु
		/* We release EX lock which used to update aसमय
		 * and get PR lock again to reduce contention
		 * on commonly accessed directories. */
		ocfs2_inode_unlock(inode, 1);
		lock_level = 0;
		error = ocfs2_inode_lock(inode, शून्य, 0);
	पूर्ण
	अगर (error < 0) अणु
		अगर (error != -ENOENT)
			mlog_त्रुटि_सं(error);
		/* we haven't got any yet, so propagate the error. */
		जाओ bail_nolock;
	पूर्ण

	error = ocfs2_dir_क्रमeach_blk(inode, &file->f_version, ctx, false);

	ocfs2_inode_unlock(inode, lock_level);
	अगर (error)
		mlog_त्रुटि_सं(error);

bail_nolock:

	वापस error;
पूर्ण

/*
 * NOTE: this should always be called with parent dir i_mutex taken.
 */
पूर्णांक ocfs2_find_files_on_disk(स्थिर अक्षर *name,
			     पूर्णांक namelen,
			     u64 *blkno,
			     काष्ठा inode *inode,
			     काष्ठा ocfs2_dir_lookup_result *lookup)
अणु
	पूर्णांक status = -ENOENT;

	trace_ocfs2_find_files_on_disk(namelen, name, blkno,
				(अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);

	status = ocfs2_find_entry(name, namelen, inode, lookup);
	अगर (status)
		जाओ leave;

	*blkno = le64_to_cpu(lookup->dl_entry->inode);

	status = 0;
leave:

	वापस status;
पूर्ण

/*
 * Convenience function क्रम callers which just want the block number
 * mapped to a name and करोn't require the full dirent info, etc.
 */
पूर्णांक ocfs2_lookup_ino_from_name(काष्ठा inode *dir, स्थिर अक्षर *name,
			       पूर्णांक namelen, u64 *blkno)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_dir_lookup_result lookup = अणु शून्य, पूर्ण;

	ret = ocfs2_find_files_on_disk(name, namelen, blkno, dir, &lookup);
	ocfs2_मुक्त_dir_lookup_result(&lookup);

	वापस ret;
पूर्ण

/* Check क्रम a name within a directory.
 *
 * Return 0 अगर the name करोes not exist
 * Return -EEXIST अगर the directory contains the name
 *
 * Callers should have i_mutex + a cluster lock on dir
 */
पूर्णांक ocfs2_check_dir_क्रम_entry(काष्ठा inode *dir,
			      स्थिर अक्षर *name,
			      पूर्णांक namelen)
अणु
	पूर्णांक ret = 0;
	काष्ठा ocfs2_dir_lookup_result lookup = अणु शून्य, पूर्ण;

	trace_ocfs2_check_dir_क्रम_entry(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno, namelen, name);

	अगर (ocfs2_find_entry(name, namelen, dir, &lookup) == 0) अणु
		ret = -EEXIST;
		mlog_त्रुटि_सं(ret);
	पूर्ण

	ocfs2_मुक्त_dir_lookup_result(&lookup);

	वापस ret;
पूर्ण

काष्ठा ocfs2_empty_dir_priv अणु
	काष्ठा dir_context ctx;
	अचिन्हित seen_करोt;
	अचिन्हित seen_करोt_करोt;
	अचिन्हित seen_other;
	अचिन्हित dx_dir;
पूर्ण;
अटल पूर्णांक ocfs2_empty_dir_filldir(काष्ठा dir_context *ctx, स्थिर अक्षर *name,
				   पूर्णांक name_len, loff_t pos, u64 ino,
				   अचिन्हित type)
अणु
	काष्ठा ocfs2_empty_dir_priv *p =
		container_of(ctx, काष्ठा ocfs2_empty_dir_priv, ctx);

	/*
	 * Check the positions of "." and ".." records to be sure
	 * they're in the correct place.
	 *
	 * Indexed directories करोn't need to proceed past the first
	 * two entries, so we end the scan after seeing '..'. Despite
	 * that, we allow the scan to proceed In the event that we
	 * have a corrupted indexed directory (no करोt or करोt करोt
	 * entries). This allows us to द्विगुन check क्रम existing
	 * entries which might not have been found in the index.
	 */
	अगर (name_len == 1 && !म_भेदन(".", name, 1) && pos == 0) अणु
		p->seen_करोt = 1;
		वापस 0;
	पूर्ण

	अगर (name_len == 2 && !म_भेदन("..", name, 2) &&
	    pos == OCFS2_सूची_REC_LEN(1)) अणु
		p->seen_करोt_करोt = 1;

		अगर (p->dx_dir && p->seen_करोt)
			वापस 1;

		वापस 0;
	पूर्ण

	p->seen_other = 1;
	वापस 1;
पूर्ण

अटल पूर्णांक ocfs2_empty_dir_dx(काष्ठा inode *inode,
			      काष्ठा ocfs2_empty_dir_priv *priv)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *di_bh = शून्य;
	काष्ठा buffer_head *dx_root_bh = शून्य;
	काष्ठा ocfs2_dinode *di;
	काष्ठा ocfs2_dx_root_block *dx_root;

	priv->dx_dir = 1;

	ret = ocfs2_पढ़ो_inode_block(inode, &di_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	di = (काष्ठा ocfs2_dinode *)di_bh->b_data;

	ret = ocfs2_पढ़ो_dx_root(inode, di, &dx_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	dx_root = (काष्ठा ocfs2_dx_root_block *)dx_root_bh->b_data;

	अगर (le32_to_cpu(dx_root->dr_num_entries) != 2)
		priv->seen_other = 1;

out:
	brअन्यथा(di_bh);
	brअन्यथा(dx_root_bh);
	वापस ret;
पूर्ण

/*
 * routine to check that the specअगरied directory is empty (क्रम सूची_हटाओ)
 *
 * Returns 1 अगर dir is empty, zero otherwise.
 *
 * XXX: This is a perक्रमmance problem क्रम unindexed directories.
 */
पूर्णांक ocfs2_empty_dir(काष्ठा inode *inode)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_empty_dir_priv priv = अणु
		.ctx.actor = ocfs2_empty_dir_filldir,
	पूर्ण;

	अगर (ocfs2_dir_indexed(inode)) अणु
		ret = ocfs2_empty_dir_dx(inode, &priv);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
		/*
		 * We still run ocfs2_dir_क्रमeach to get the checks
		 * क्रम "." and "..".
		 */
	पूर्ण

	ret = ocfs2_dir_क्रमeach(inode, &priv.ctx);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

	अगर (!priv.seen_करोt || !priv.seen_करोt_करोt) अणु
		mlog(ML_ERROR, "bad directory (dir #%llu) - no `.' or `..'\n",
		     (अचिन्हित दीर्घ दीर्घ)OCFS2_I(inode)->ip_blkno);
		/*
		 * XXX: Is it really safe to allow an unlink to जारी?
		 */
		वापस 1;
	पूर्ण

	वापस !priv.seen_other;
पूर्ण

/*
 * Fills "." and ".." dirents in a new directory block. Returns dirent क्रम
 * "..", which might be used during creation of a directory with a trailing
 * header. It is otherwise safe to ignore the वापस code.
 */
अटल काष्ठा ocfs2_dir_entry *ocfs2_fill_initial_dirents(काष्ठा inode *inode,
							  काष्ठा inode *parent,
							  अक्षर *start,
							  अचिन्हित पूर्णांक size)
अणु
	काष्ठा ocfs2_dir_entry *de = (काष्ठा ocfs2_dir_entry *)start;

	de->inode = cpu_to_le64(OCFS2_I(inode)->ip_blkno);
	de->name_len = 1;
	de->rec_len =
		cpu_to_le16(OCFS2_सूची_REC_LEN(de->name_len));
	म_नकल(de->name, ".");
	ocfs2_set_de_type(de, S_IFसूची);

	de = (काष्ठा ocfs2_dir_entry *) ((अक्षर *)de + le16_to_cpu(de->rec_len));
	de->inode = cpu_to_le64(OCFS2_I(parent)->ip_blkno);
	de->rec_len = cpu_to_le16(size - OCFS2_सूची_REC_LEN(1));
	de->name_len = 2;
	म_नकल(de->name, "..");
	ocfs2_set_de_type(de, S_IFसूची);

	वापस de;
पूर्ण

/*
 * This works together with code in ocfs2_mknod_locked() which sets
 * the अंतरभूत-data flag and initializes the अंतरभूत-data section.
 */
अटल पूर्णांक ocfs2_fill_new_dir_id(काष्ठा ocfs2_super *osb,
				 handle_t *handle,
				 काष्ठा inode *parent,
				 काष्ठा inode *inode,
				 काष्ठा buffer_head *di_bh)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_अंतरभूत_data *data = &di->id2.i_data;
	अचिन्हित पूर्णांक size = le16_to_cpu(data->id_count);

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(inode), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ocfs2_fill_initial_dirents(inode, parent, data->id_data, size);
	ocfs2_journal_dirty(handle, di_bh);

	i_size_ग_लिखो(inode, size);
	set_nlink(inode, 2);
	inode->i_blocks = ocfs2_inode_sector_count(inode);

	ret = ocfs2_mark_inode_dirty(handle, inode, di_bh);
	अगर (ret < 0)
		mlog_त्रुटि_सं(ret);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_fill_new_dir_el(काष्ठा ocfs2_super *osb,
				 handle_t *handle,
				 काष्ठा inode *parent,
				 काष्ठा inode *inode,
				 काष्ठा buffer_head *fe_bh,
				 काष्ठा ocfs2_alloc_context *data_ac,
				 काष्ठा buffer_head **ret_new_bh)
अणु
	पूर्णांक status;
	अचिन्हित पूर्णांक size = osb->sb->s_blocksize;
	काष्ठा buffer_head *new_bh = शून्य;
	काष्ठा ocfs2_dir_entry *de;

	अगर (ocfs2_new_dir_wants_trailer(inode))
		size = ocfs2_dir_trailer_blk_off(parent->i_sb);

	status = ocfs2_करो_extend_dir(osb->sb, handle, inode, fe_bh,
				     data_ac, शून्य, &new_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	ocfs2_set_new_buffer_uptodate(INODE_CACHE(inode), new_bh);

	status = ocfs2_journal_access_db(handle, INODE_CACHE(inode), new_bh,
					 OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	स_रखो(new_bh->b_data, 0, osb->sb->s_blocksize);

	de = ocfs2_fill_initial_dirents(inode, parent, new_bh->b_data, size);
	अगर (ocfs2_new_dir_wants_trailer(inode)) अणु
		पूर्णांक size = le16_to_cpu(de->rec_len);

		/*
		 * Figure out the size of the hole left over after
		 * insertion of '.' and '..'. The trailer wants this
		 * inक्रमmation.
		 */
		size -= OCFS2_सूची_REC_LEN(2);
		size -= माप(काष्ठा ocfs2_dir_block_trailer);

		ocfs2_init_dir_trailer(inode, new_bh, size);
	पूर्ण

	ocfs2_journal_dirty(handle, new_bh);

	i_size_ग_लिखो(inode, inode->i_sb->s_blocksize);
	set_nlink(inode, 2);
	inode->i_blocks = ocfs2_inode_sector_count(inode);
	status = ocfs2_mark_inode_dirty(handle, inode, fe_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = 0;
	अगर (ret_new_bh) अणु
		*ret_new_bh = new_bh;
		new_bh = शून्य;
	पूर्ण
bail:
	brअन्यथा(new_bh);

	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_dx_dir_attach_index(काष्ठा ocfs2_super *osb,
				     handle_t *handle, काष्ठा inode *dir,
				     काष्ठा buffer_head *di_bh,
				     काष्ठा buffer_head *dirdata_bh,
				     काष्ठा ocfs2_alloc_context *meta_ac,
				     पूर्णांक dx_अंतरभूत, u32 num_entries,
				     काष्ठा buffer_head **ret_dx_root_bh)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *) di_bh->b_data;
	u16 dr_suballoc_bit;
	u64 suballoc_loc, dr_blkno;
	अचिन्हित पूर्णांक num_bits;
	काष्ठा buffer_head *dx_root_bh = शून्य;
	काष्ठा ocfs2_dx_root_block *dx_root;
	काष्ठा ocfs2_dir_block_trailer *trailer =
		ocfs2_trailer_from_bh(dirdata_bh, dir->i_sb);

	ret = ocfs2_claim_metadata(handle, meta_ac, 1, &suballoc_loc,
				   &dr_suballoc_bit, &num_bits, &dr_blkno);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	trace_ocfs2_dx_dir_attach_index(
				(अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno,
				(अचिन्हित दीर्घ दीर्घ)dr_blkno);

	dx_root_bh = sb_getblk(osb->sb, dr_blkno);
	अगर (dx_root_bh == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	ocfs2_set_new_buffer_uptodate(INODE_CACHE(dir), dx_root_bh);

	ret = ocfs2_journal_access_dr(handle, INODE_CACHE(dir), dx_root_bh,
				      OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (ret < 0) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	dx_root = (काष्ठा ocfs2_dx_root_block *)dx_root_bh->b_data;
	स_रखो(dx_root, 0, osb->sb->s_blocksize);
	म_नकल(dx_root->dr_signature, OCFS2_DX_ROOT_SIGNATURE);
	dx_root->dr_suballoc_slot = cpu_to_le16(meta_ac->ac_alloc_slot);
	dx_root->dr_suballoc_loc = cpu_to_le64(suballoc_loc);
	dx_root->dr_suballoc_bit = cpu_to_le16(dr_suballoc_bit);
	dx_root->dr_fs_generation = cpu_to_le32(osb->fs_generation);
	dx_root->dr_blkno = cpu_to_le64(dr_blkno);
	dx_root->dr_dir_blkno = cpu_to_le64(OCFS2_I(dir)->ip_blkno);
	dx_root->dr_num_entries = cpu_to_le32(num_entries);
	अगर (le16_to_cpu(trailer->db_मुक्त_rec_len))
		dx_root->dr_मुक्त_blk = cpu_to_le64(dirdata_bh->b_blocknr);
	अन्यथा
		dx_root->dr_मुक्त_blk = cpu_to_le64(0);

	अगर (dx_अंतरभूत) अणु
		dx_root->dr_flags |= OCFS2_DX_FLAG_INLINE;
		dx_root->dr_entries.de_count =
			cpu_to_le16(ocfs2_dx_entries_per_root(osb->sb));
	पूर्ण अन्यथा अणु
		dx_root->dr_list.l_count =
			cpu_to_le16(ocfs2_extent_recs_per_dx_root(osb->sb));
	पूर्ण
	ocfs2_journal_dirty(handle, dx_root_bh);

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(dir), di_bh,
				      OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	di->i_dx_root = cpu_to_le64(dr_blkno);

	spin_lock(&OCFS2_I(dir)->ip_lock);
	OCFS2_I(dir)->ip_dyn_features |= OCFS2_INDEXED_सूची_FL;
	di->i_dyn_features = cpu_to_le16(OCFS2_I(dir)->ip_dyn_features);
	spin_unlock(&OCFS2_I(dir)->ip_lock);

	ocfs2_journal_dirty(handle, di_bh);

	*ret_dx_root_bh = dx_root_bh;
	dx_root_bh = शून्य;

out:
	brअन्यथा(dx_root_bh);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_dx_dir_क्रमmat_cluster(काष्ठा ocfs2_super *osb,
				       handle_t *handle, काष्ठा inode *dir,
				       काष्ठा buffer_head **dx_leaves,
				       पूर्णांक num_dx_leaves, u64 start_blk)
अणु
	पूर्णांक ret, i;
	काष्ठा ocfs2_dx_leaf *dx_leaf;
	काष्ठा buffer_head *bh;

	क्रम (i = 0; i < num_dx_leaves; i++) अणु
		bh = sb_getblk(osb->sb, start_blk + i);
		अगर (bh == शून्य) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		dx_leaves[i] = bh;

		ocfs2_set_new_buffer_uptodate(INODE_CACHE(dir), bh);

		ret = ocfs2_journal_access_dl(handle, INODE_CACHE(dir), bh,
					      OCFS2_JOURNAL_ACCESS_CREATE);
		अगर (ret < 0) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		dx_leaf = (काष्ठा ocfs2_dx_leaf *) bh->b_data;

		स_रखो(dx_leaf, 0, osb->sb->s_blocksize);
		म_नकल(dx_leaf->dl_signature, OCFS2_DX_LEAF_SIGNATURE);
		dx_leaf->dl_fs_generation = cpu_to_le32(osb->fs_generation);
		dx_leaf->dl_blkno = cpu_to_le64(bh->b_blocknr);
		dx_leaf->dl_list.de_count =
			cpu_to_le16(ocfs2_dx_entries_per_leaf(osb->sb));

		trace_ocfs2_dx_dir_क्रमmat_cluster(
				(अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno,
				(अचिन्हित दीर्घ दीर्घ)bh->b_blocknr,
				le16_to_cpu(dx_leaf->dl_list.de_count));

		ocfs2_journal_dirty(handle, bh);
	पूर्ण

	ret = 0;
out:
	वापस ret;
पूर्ण

/*
 * Allocates and क्रमmats a new cluster क्रम use in an indexed dir
 * leaf. This version will not करो the extent insert, so that it can be
 * used by operations which need careful ordering.
 */
अटल पूर्णांक __ocfs2_dx_dir_new_cluster(काष्ठा inode *dir,
				      u32 cpos, handle_t *handle,
				      काष्ठा ocfs2_alloc_context *data_ac,
				      काष्ठा buffer_head **dx_leaves,
				      पूर्णांक num_dx_leaves, u64 *ret_phys_blkno)
अणु
	पूर्णांक ret;
	u32 phys, num;
	u64 phys_blkno;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);

	/*
	 * XXX: For create, this should claim cluster क्रम the index
	 * *beक्रमe* the unindexed insert so that we have a better
	 * chance of contiguousness as the directory grows in number
	 * of entries.
	 */
	ret = __ocfs2_claim_clusters(handle, data_ac, 1, 1, &phys, &num);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * Format the new cluster first. That way, we're inserting
	 * valid data.
	 */
	phys_blkno = ocfs2_clusters_to_blocks(osb->sb, phys);
	ret = ocfs2_dx_dir_क्रमmat_cluster(osb, handle, dir, dx_leaves,
					  num_dx_leaves, phys_blkno);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	*ret_phys_blkno = phys_blkno;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_dx_dir_new_cluster(काष्ठा inode *dir,
				    काष्ठा ocfs2_extent_tree *et,
				    u32 cpos, handle_t *handle,
				    काष्ठा ocfs2_alloc_context *data_ac,
				    काष्ठा ocfs2_alloc_context *meta_ac,
				    काष्ठा buffer_head **dx_leaves,
				    पूर्णांक num_dx_leaves)
अणु
	पूर्णांक ret;
	u64 phys_blkno;

	ret = __ocfs2_dx_dir_new_cluster(dir, cpos, handle, data_ac, dx_leaves,
					 num_dx_leaves, &phys_blkno);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_insert_extent(handle, et, cpos, phys_blkno, 1, 0,
				  meta_ac);
	अगर (ret)
		mlog_त्रुटि_सं(ret);
out:
	वापस ret;
पूर्ण

अटल काष्ठा buffer_head **ocfs2_dx_dir_kदो_स्मृति_leaves(काष्ठा super_block *sb,
							पूर्णांक *ret_num_leaves)
अणु
	पूर्णांक num_dx_leaves = ocfs2_clusters_to_blocks(sb, 1);
	काष्ठा buffer_head **dx_leaves;

	dx_leaves = kसुस्मृति(num_dx_leaves, माप(काष्ठा buffer_head *),
			    GFP_NOFS);
	अगर (dx_leaves && ret_num_leaves)
		*ret_num_leaves = num_dx_leaves;

	वापस dx_leaves;
पूर्ण

अटल पूर्णांक ocfs2_fill_new_dir_dx(काष्ठा ocfs2_super *osb,
				 handle_t *handle,
				 काष्ठा inode *parent,
				 काष्ठा inode *inode,
				 काष्ठा buffer_head *di_bh,
				 काष्ठा ocfs2_alloc_context *data_ac,
				 काष्ठा ocfs2_alloc_context *meta_ac)
अणु
	पूर्णांक ret;
	काष्ठा buffer_head *leaf_bh = शून्य;
	काष्ठा buffer_head *dx_root_bh = शून्य;
	काष्ठा ocfs2_dx_hinfo hinfo;
	काष्ठा ocfs2_dx_root_block *dx_root;
	काष्ठा ocfs2_dx_entry_list *entry_list;

	/*
	 * Our strategy is to create the directory as though it were
	 * unindexed, then add the index block. This works with very
	 * little complication since the state of a new directory is a
	 * very well known quantity.
	 *
	 * Essentially, we have two dirents ("." and ".."), in the 1st
	 * block which need indexing. These are easily inserted पूर्णांकo
	 * the index block.
	 */

	ret = ocfs2_fill_new_dir_el(osb, handle, parent, inode, di_bh,
				    data_ac, &leaf_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_dx_dir_attach_index(osb, handle, inode, di_bh, leaf_bh,
					meta_ac, 1, 2, &dx_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	dx_root = (काष्ठा ocfs2_dx_root_block *)dx_root_bh->b_data;
	entry_list = &dx_root->dr_entries;

	/* Buffer has been journaled क्रम us by ocfs2_dx_dir_attach_index */
	ocfs2_dx_dir_name_hash(inode, ".", 1, &hinfo);
	ocfs2_dx_entry_list_insert(entry_list, &hinfo, leaf_bh->b_blocknr);

	ocfs2_dx_dir_name_hash(inode, "..", 2, &hinfo);
	ocfs2_dx_entry_list_insert(entry_list, &hinfo, leaf_bh->b_blocknr);

out:
	brअन्यथा(dx_root_bh);
	brअन्यथा(leaf_bh);
	वापस ret;
पूर्ण

पूर्णांक ocfs2_fill_new_dir(काष्ठा ocfs2_super *osb,
		       handle_t *handle,
		       काष्ठा inode *parent,
		       काष्ठा inode *inode,
		       काष्ठा buffer_head *fe_bh,
		       काष्ठा ocfs2_alloc_context *data_ac,
		       काष्ठा ocfs2_alloc_context *meta_ac)

अणु
	BUG_ON(!ocfs2_supports_अंतरभूत_data(osb) && data_ac == शून्य);

	अगर (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		वापस ocfs2_fill_new_dir_id(osb, handle, parent, inode, fe_bh);

	अगर (ocfs2_supports_indexed_dirs(osb))
		वापस ocfs2_fill_new_dir_dx(osb, handle, parent, inode, fe_bh,
					     data_ac, meta_ac);

	वापस ocfs2_fill_new_dir_el(osb, handle, parent, inode, fe_bh,
				     data_ac, शून्य);
पूर्ण

अटल पूर्णांक ocfs2_dx_dir_index_block(काष्ठा inode *dir,
				    handle_t *handle,
				    काष्ठा buffer_head **dx_leaves,
				    पूर्णांक num_dx_leaves,
				    u32 *num_dx_entries,
				    काष्ठा buffer_head *dirent_bh)
अणु
	पूर्णांक ret = 0, namelen, i;
	अक्षर *de_buf, *limit;
	काष्ठा ocfs2_dir_entry *de;
	काष्ठा buffer_head *dx_leaf_bh;
	काष्ठा ocfs2_dx_hinfo hinfo;
	u64 dirent_blk = dirent_bh->b_blocknr;

	de_buf = dirent_bh->b_data;
	limit = de_buf + dir->i_sb->s_blocksize;

	जबतक (de_buf < limit) अणु
		de = (काष्ठा ocfs2_dir_entry *)de_buf;

		namelen = de->name_len;
		अगर (!namelen || !de->inode)
			जाओ inc;

		ocfs2_dx_dir_name_hash(dir, de->name, namelen, &hinfo);

		i = ocfs2_dx_dir_hash_idx(OCFS2_SB(dir->i_sb), &hinfo);
		dx_leaf_bh = dx_leaves[i];

		ret = __ocfs2_dx_dir_leaf_insert(dir, handle, &hinfo,
						 dirent_blk, dx_leaf_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		*num_dx_entries = *num_dx_entries + 1;

inc:
		de_buf += le16_to_cpu(de->rec_len);
	पूर्ण

out:
	वापस ret;
पूर्ण

/*
 * XXX: This expects dx_root_bh to alपढ़ोy be part of the transaction.
 */
अटल व्योम ocfs2_dx_dir_index_root_block(काष्ठा inode *dir,
					 काष्ठा buffer_head *dx_root_bh,
					 काष्ठा buffer_head *dirent_bh)
अणु
	अक्षर *de_buf, *limit;
	काष्ठा ocfs2_dx_root_block *dx_root;
	काष्ठा ocfs2_dir_entry *de;
	काष्ठा ocfs2_dx_hinfo hinfo;
	u64 dirent_blk = dirent_bh->b_blocknr;

	dx_root = (काष्ठा ocfs2_dx_root_block *)dx_root_bh->b_data;

	de_buf = dirent_bh->b_data;
	limit = de_buf + dir->i_sb->s_blocksize;

	जबतक (de_buf < limit) अणु
		de = (काष्ठा ocfs2_dir_entry *)de_buf;

		अगर (!de->name_len || !de->inode)
			जाओ inc;

		ocfs2_dx_dir_name_hash(dir, de->name, de->name_len, &hinfo);

		trace_ocfs2_dx_dir_index_root_block(
				(अचिन्हित दीर्घ दीर्घ)dir->i_ino,
				hinfo.major_hash, hinfo.minor_hash,
				de->name_len, de->name,
				le16_to_cpu(dx_root->dr_entries.de_num_used));

		ocfs2_dx_entry_list_insert(&dx_root->dr_entries, &hinfo,
					   dirent_blk);

		le32_add_cpu(&dx_root->dr_num_entries, 1);
inc:
		de_buf += le16_to_cpu(de->rec_len);
	पूर्ण
पूर्ण

/*
 * Count the number of अंतरभूत directory entries in di_bh and compare
 * them against the number of entries we can hold in an अंतरभूत dx root
 * block.
 */
अटल पूर्णांक ocfs2_new_dx_should_be_अंतरभूत(काष्ठा inode *dir,
					 काष्ठा buffer_head *di_bh)
अणु
	पूर्णांक dirent_count = 0;
	अक्षर *de_buf, *limit;
	काष्ठा ocfs2_dir_entry *de;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;

	de_buf = di->id2.i_data.id_data;
	limit = de_buf + i_size_पढ़ो(dir);

	जबतक (de_buf < limit) अणु
		de = (काष्ठा ocfs2_dir_entry *)de_buf;

		अगर (de->name_len && de->inode)
			dirent_count++;

		de_buf += le16_to_cpu(de->rec_len);
	पूर्ण

	/* We are careful to leave room क्रम one extra record. */
	वापस dirent_count < ocfs2_dx_entries_per_root(dir->i_sb);
पूर्ण

/*
 * Expand rec_len of the righपंचांगost dirent in a directory block so that it
 * contains the end of our valid space क्रम dirents. We करो this during
 * expansion from an अंतरभूत directory to one with extents. The first dir block
 * in that हाल is taken from the अंतरभूत data portion of the inode block.
 *
 * This will also वापस the largest amount of contiguous space क्रम a dirent
 * in the block. That value is *not* necessarily the last dirent, even after
 * expansion. The directory indexing code wants this value क्रम मुक्त space
 * accounting. We करो this here since we're alपढ़ोy walking the entire dir
 * block.
 *
 * We add the dir trailer अगर this fileप्रणाली wants it.
 */
अटल अचिन्हित पूर्णांक ocfs2_expand_last_dirent(अक्षर *start, अचिन्हित पूर्णांक old_size,
					     काष्ठा inode *dir)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा ocfs2_dir_entry *de;
	काष्ठा ocfs2_dir_entry *prev_de;
	अक्षर *de_buf, *limit;
	अचिन्हित पूर्णांक new_size = sb->s_blocksize;
	अचिन्हित पूर्णांक bytes, this_hole;
	अचिन्हित पूर्णांक largest_hole = 0;

	अगर (ocfs2_new_dir_wants_trailer(dir))
		new_size = ocfs2_dir_trailer_blk_off(sb);

	bytes = new_size - old_size;

	limit = start + old_size;
	de_buf = start;
	de = (काष्ठा ocfs2_dir_entry *)de_buf;
	करो अणु
		this_hole = ocfs2_figure_dirent_hole(de);
		अगर (this_hole > largest_hole)
			largest_hole = this_hole;

		prev_de = de;
		de_buf += le16_to_cpu(de->rec_len);
		de = (काष्ठा ocfs2_dir_entry *)de_buf;
	पूर्ण जबतक (de_buf < limit);

	le16_add_cpu(&prev_de->rec_len, bytes);

	/* We need to द्विगुन check this after modअगरication of the final
	 * dirent. */
	this_hole = ocfs2_figure_dirent_hole(prev_de);
	अगर (this_hole > largest_hole)
		largest_hole = this_hole;

	अगर (largest_hole >= OCFS2_सूची_MIN_REC_LEN)
		वापस largest_hole;
	वापस 0;
पूर्ण

/*
 * We allocate enough clusters to fulfill "blocks_wanted", but set
 * i_size to exactly one block. Ocfs2_extend_dir() will handle the
 * rest स्वतःmatically क्रम us.
 *
 * *first_block_bh is a poपूर्णांकer to the 1st data block allocated to the
 *  directory.
 */
अटल पूर्णांक ocfs2_expand_अंतरभूत_dir(काष्ठा inode *dir, काष्ठा buffer_head *di_bh,
				   अचिन्हित पूर्णांक blocks_wanted,
				   काष्ठा ocfs2_dir_lookup_result *lookup,
				   काष्ठा buffer_head **first_block_bh)
अणु
	u32 alloc, dx_alloc, bit_off, len, num_dx_entries = 0;
	काष्ठा super_block *sb = dir->i_sb;
	पूर्णांक ret, i, num_dx_leaves = 0, dx_अंतरभूत = 0,
		credits = ocfs2_अंतरभूत_to_extents_credits(sb);
	u64 dx_insert_blkno, blkno,
		bytes = blocks_wanted << sb->s_blocksize_bits;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	काष्ठा ocfs2_inode_info *oi = OCFS2_I(dir);
	काष्ठा ocfs2_alloc_context *data_ac = शून्य;
	काष्ठा ocfs2_alloc_context *meta_ac = शून्य;
	काष्ठा buffer_head *dirdata_bh = शून्य;
	काष्ठा buffer_head *dx_root_bh = शून्य;
	काष्ठा buffer_head **dx_leaves = शून्य;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	handle_t *handle;
	काष्ठा ocfs2_extent_tree et;
	काष्ठा ocfs2_extent_tree dx_et;
	पूर्णांक did_quota = 0, bytes_allocated = 0;

	ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(dir), di_bh);

	alloc = ocfs2_clusters_क्रम_bytes(sb, bytes);
	dx_alloc = 0;

	करोwn_ग_लिखो(&oi->ip_alloc_sem);

	अगर (ocfs2_supports_indexed_dirs(osb)) अणु
		credits += ocfs2_add_dir_index_credits(sb);

		dx_अंतरभूत = ocfs2_new_dx_should_be_अंतरभूत(dir, di_bh);
		अगर (!dx_अंतरभूत) अणु
			/* Add one more cluster क्रम an index leaf */
			dx_alloc++;
			dx_leaves = ocfs2_dx_dir_kदो_स्मृति_leaves(sb,
								&num_dx_leaves);
			अगर (!dx_leaves) अणु
				ret = -ENOMEM;
				mlog_त्रुटि_सं(ret);
				जाओ out;
			पूर्ण
		पूर्ण

		/* This माला_लो us the dx_root */
		ret = ocfs2_reserve_new_metadata_blocks(osb, 1, &meta_ac);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * We should never need more than 2 clusters क्रम the unindexed
	 * tree - maximum dirent size is far less than one block. In
	 * fact, the only समय we'd need more than one cluster is अगर
	 * blocksize == clustersize and the dirent won't fit in the
	 * extra space that the expansion to a single block gives. As
	 * of today, that only happens on 4k/4k file प्रणालीs.
	 */
	BUG_ON(alloc > 2);

	ret = ocfs2_reserve_clusters(osb, alloc + dx_alloc, &data_ac);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * Prepare क्रम worst हाल allocation scenario of two separate
	 * extents in the unindexed tree.
	 */
	अगर (alloc == 2)
		credits += OCFS2_SUBALLOC_ALLOC;

	handle = ocfs2_start_trans(osb, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = dquot_alloc_space_nodirty(dir,
		ocfs2_clusters_to_bytes(osb->sb, alloc + dx_alloc));
	अगर (ret)
		जाओ out_commit;
	did_quota = 1;

	अगर (ocfs2_supports_indexed_dirs(osb) && !dx_अंतरभूत) अणु
		/*
		 * Allocate our index cluster first, to maximize the
		 * possibility that unindexed leaves grow
		 * contiguously.
		 */
		ret = __ocfs2_dx_dir_new_cluster(dir, 0, handle, data_ac,
						 dx_leaves, num_dx_leaves,
						 &dx_insert_blkno);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_commit;
		पूर्ण
		bytes_allocated += ocfs2_clusters_to_bytes(dir->i_sb, 1);
	पूर्ण

	/*
	 * Try to claim as many clusters as the biपंचांगap can give though
	 * अगर we only get one now, that's enough to जारी. The rest
	 * will be claimed after the conversion to extents.
	 */
	अगर (ocfs2_dir_resv_allowed(osb))
		data_ac->ac_resv = &oi->ip_la_data_resv;
	ret = ocfs2_claim_clusters(handle, data_ac, 1, &bit_off, &len);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण
	bytes_allocated += ocfs2_clusters_to_bytes(dir->i_sb, 1);

	/*
	 * Operations are carefully ordered so that we set up the new
	 * data block first. The conversion from अंतरभूत data to
	 * extents follows.
	 */
	blkno = ocfs2_clusters_to_blocks(dir->i_sb, bit_off);
	dirdata_bh = sb_getblk(sb, blkno);
	अगर (!dirdata_bh) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	ocfs2_set_new_buffer_uptodate(INODE_CACHE(dir), dirdata_bh);

	ret = ocfs2_journal_access_db(handle, INODE_CACHE(dir), dirdata_bh,
				      OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	स_नकल(dirdata_bh->b_data, di->id2.i_data.id_data, i_size_पढ़ो(dir));
	स_रखो(dirdata_bh->b_data + i_size_पढ़ो(dir), 0,
	       sb->s_blocksize - i_size_पढ़ो(dir));
	i = ocfs2_expand_last_dirent(dirdata_bh->b_data, i_size_पढ़ो(dir), dir);
	अगर (ocfs2_new_dir_wants_trailer(dir)) अणु
		/*
		 * Prepare the dir trailer up front. It will otherwise look
		 * like a valid dirent. Even अगर inserting the index fails
		 * (unlikely), then all we'll have करोne is given first dir
		 * block a small amount of fragmentation.
		 */
		ocfs2_init_dir_trailer(dir, dirdata_bh, i);
	पूर्ण

	ocfs2_update_inode_fsync_trans(handle, dir, 1);
	ocfs2_journal_dirty(handle, dirdata_bh);

	अगर (ocfs2_supports_indexed_dirs(osb) && !dx_अंतरभूत) अणु
		/*
		 * Dx dirs with an बाह्यal cluster need to करो this up
		 * front. Inline dx root's get handled later, after
		 * we've allocated our root block. We get passed back
		 * a total number of items so that dr_num_entries can
		 * be correctly set once the dx_root has been
		 * allocated.
		 */
		ret = ocfs2_dx_dir_index_block(dir, handle, dx_leaves,
					       num_dx_leaves, &num_dx_entries,
					       dirdata_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_commit;
		पूर्ण
	पूर्ण

	/*
	 * Set extent, i_size, etc on the directory. After this, the
	 * inode should contain the same exact dirents as beक्रमe and
	 * be fully accessible from प्रणाली calls.
	 *
	 * We let the later dirent insert modअगरy c/mसमय - to the user
	 * the data hasn't changed.
	 */
	ret = ocfs2_journal_access_di(handle, INODE_CACHE(dir), di_bh,
				      OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	spin_lock(&oi->ip_lock);
	oi->ip_dyn_features &= ~OCFS2_INLINE_DATA_FL;
	di->i_dyn_features = cpu_to_le16(oi->ip_dyn_features);
	spin_unlock(&oi->ip_lock);

	ocfs2_dinode_new_extent_list(dir, di);

	i_size_ग_लिखो(dir, sb->s_blocksize);
	dir->i_mसमय = dir->i_स_समय = current_समय(dir);

	di->i_size = cpu_to_le64(sb->s_blocksize);
	di->i_स_समय = di->i_mसमय = cpu_to_le64(dir->i_स_समय.tv_sec);
	di->i_स_समय_nsec = di->i_mसमय_nsec = cpu_to_le32(dir->i_स_समय.tv_nsec);
	ocfs2_update_inode_fsync_trans(handle, dir, 1);

	/*
	 * This should never fail as our extent list is empty and all
	 * related blocks have been journaled alपढ़ोy.
	 */
	ret = ocfs2_insert_extent(handle, &et, 0, blkno, len,
				  0, शून्य);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	/*
	 * Set i_blocks after the extent insert क्रम the most up to
	 * date ip_clusters value.
	 */
	dir->i_blocks = ocfs2_inode_sector_count(dir);

	ocfs2_journal_dirty(handle, di_bh);

	अगर (ocfs2_supports_indexed_dirs(osb)) अणु
		ret = ocfs2_dx_dir_attach_index(osb, handle, dir, di_bh,
						dirdata_bh, meta_ac, dx_अंतरभूत,
						num_dx_entries, &dx_root_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_commit;
		पूर्ण

		अगर (dx_अंतरभूत) अणु
			ocfs2_dx_dir_index_root_block(dir, dx_root_bh,
						      dirdata_bh);
		पूर्ण अन्यथा अणु
			ocfs2_init_dx_root_extent_tree(&dx_et,
						       INODE_CACHE(dir),
						       dx_root_bh);
			ret = ocfs2_insert_extent(handle, &dx_et, 0,
						  dx_insert_blkno, 1, 0, शून्य);
			अगर (ret)
				mlog_त्रुटि_सं(ret);
		पूर्ण
	पूर्ण

	/*
	 * We asked क्रम two clusters, but only got one in the 1st
	 * pass. Claim the 2nd cluster as a separate extent.
	 */
	अगर (alloc > len) अणु
		ret = ocfs2_claim_clusters(handle, data_ac, 1, &bit_off,
					   &len);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_commit;
		पूर्ण
		blkno = ocfs2_clusters_to_blocks(dir->i_sb, bit_off);

		ret = ocfs2_insert_extent(handle, &et, 1,
					  blkno, len, 0, शून्य);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_commit;
		पूर्ण
		bytes_allocated += ocfs2_clusters_to_bytes(dir->i_sb, 1);
	पूर्ण

	*first_block_bh = dirdata_bh;
	dirdata_bh = शून्य;
	अगर (ocfs2_supports_indexed_dirs(osb)) अणु
		अचिन्हित पूर्णांक off;

		अगर (!dx_अंतरभूत) अणु
			/*
			 * We need to वापस the correct block within the
			 * cluster which should hold our entry.
			 */
			off = ocfs2_dx_dir_hash_idx(osb,
						    &lookup->dl_hinfo);
			get_bh(dx_leaves[off]);
			lookup->dl_dx_leaf_bh = dx_leaves[off];
		पूर्ण
		lookup->dl_dx_root_bh = dx_root_bh;
		dx_root_bh = शून्य;
	पूर्ण

out_commit:
	अगर (ret < 0 && did_quota)
		dquot_मुक्त_space_nodirty(dir, bytes_allocated);

	ocfs2_commit_trans(osb, handle);

out:
	up_ग_लिखो(&oi->ip_alloc_sem);
	अगर (data_ac)
		ocfs2_मुक्त_alloc_context(data_ac);
	अगर (meta_ac)
		ocfs2_मुक्त_alloc_context(meta_ac);

	अगर (dx_leaves) अणु
		क्रम (i = 0; i < num_dx_leaves; i++)
			brअन्यथा(dx_leaves[i]);
		kमुक्त(dx_leaves);
	पूर्ण

	brअन्यथा(dirdata_bh);
	brअन्यथा(dx_root_bh);

	वापस ret;
पूर्ण

/* वापसs a bh of the 1st new block in the allocation. */
अटल पूर्णांक ocfs2_करो_extend_dir(काष्ठा super_block *sb,
			       handle_t *handle,
			       काष्ठा inode *dir,
			       काष्ठा buffer_head *parent_fe_bh,
			       काष्ठा ocfs2_alloc_context *data_ac,
			       काष्ठा ocfs2_alloc_context *meta_ac,
			       काष्ठा buffer_head **new_bh)
अणु
	पूर्णांक status;
	पूर्णांक extend, did_quota = 0;
	u64 p_blkno, v_blkno;

	spin_lock(&OCFS2_I(dir)->ip_lock);
	extend = (i_size_पढ़ो(dir) == ocfs2_clusters_to_bytes(sb, OCFS2_I(dir)->ip_clusters));
	spin_unlock(&OCFS2_I(dir)->ip_lock);

	अगर (extend) अणु
		u32 offset = OCFS2_I(dir)->ip_clusters;

		status = dquot_alloc_space_nodirty(dir,
					ocfs2_clusters_to_bytes(sb, 1));
		अगर (status)
			जाओ bail;
		did_quota = 1;

		status = ocfs2_add_inode_data(OCFS2_SB(sb), dir, &offset,
					      1, 0, parent_fe_bh, handle,
					      data_ac, meta_ac, शून्य);
		BUG_ON(status == -EAGAIN);
		अगर (status < 0) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण
	पूर्ण

	v_blkno = ocfs2_blocks_क्रम_bytes(sb, i_size_पढ़ो(dir));
	status = ocfs2_extent_map_get_blocks(dir, v_blkno, &p_blkno, शून्य, शून्य);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	*new_bh = sb_getblk(sb, p_blkno);
	अगर (!*new_bh) अणु
		status = -ENOMEM;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	status = 0;
bail:
	अगर (did_quota && status < 0)
		dquot_मुक्त_space_nodirty(dir, ocfs2_clusters_to_bytes(sb, 1));
	वापस status;
पूर्ण

/*
 * Assumes you alपढ़ोy have a cluster lock on the directory.
 *
 * 'blocks_wanted' is only used अगर we have an अंतरभूत directory which
 * is to be turned पूर्णांकo an extent based one. The size of the dirent to
 * insert might be larger than the space gained by growing to just one
 * block, so we may have to grow the inode by two blocks in that हाल.
 *
 * If the directory is alपढ़ोy indexed, dx_root_bh must be provided.
 */
अटल पूर्णांक ocfs2_extend_dir(काष्ठा ocfs2_super *osb,
			    काष्ठा inode *dir,
			    काष्ठा buffer_head *parent_fe_bh,
			    अचिन्हित पूर्णांक blocks_wanted,
			    काष्ठा ocfs2_dir_lookup_result *lookup,
			    काष्ठा buffer_head **new_de_bh)
अणु
	पूर्णांक status = 0;
	पूर्णांक credits, num_मुक्त_extents, drop_alloc_sem = 0;
	loff_t dir_i_size;
	काष्ठा ocfs2_dinode *fe = (काष्ठा ocfs2_dinode *) parent_fe_bh->b_data;
	काष्ठा ocfs2_extent_list *el = &fe->id2.i_list;
	काष्ठा ocfs2_alloc_context *data_ac = शून्य;
	काष्ठा ocfs2_alloc_context *meta_ac = शून्य;
	handle_t *handle = शून्य;
	काष्ठा buffer_head *new_bh = शून्य;
	काष्ठा ocfs2_dir_entry * de;
	काष्ठा super_block *sb = osb->sb;
	काष्ठा ocfs2_extent_tree et;
	काष्ठा buffer_head *dx_root_bh = lookup->dl_dx_root_bh;

	अगर (OCFS2_I(dir)->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		/*
		 * This would be a code error as an अंतरभूत directory should
		 * never have an index root.
		 */
		BUG_ON(dx_root_bh);

		status = ocfs2_expand_अंतरभूत_dir(dir, parent_fe_bh,
						 blocks_wanted, lookup,
						 &new_bh);
		अगर (status) अणु
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		/* Expansion from अंतरभूत to an indexed directory will
		 * have given us this. */
		dx_root_bh = lookup->dl_dx_root_bh;

		अगर (blocks_wanted == 1) अणु
			/*
			 * If the new dirent will fit inside the space
			 * created by pushing out to one block, then
			 * we can complete the operation
			 * here. Otherwise we have to expand i_size
			 * and क्रमmat the 2nd block below.
			 */
			BUG_ON(new_bh == शून्य);
			जाओ bail_bh;
		पूर्ण

		/*
		 * Get rid of 'new_bh' - we want to क्रमmat the 2nd
		 * data block and वापस that instead.
		 */
		brअन्यथा(new_bh);
		new_bh = शून्य;

		करोwn_ग_लिखो(&OCFS2_I(dir)->ip_alloc_sem);
		drop_alloc_sem = 1;
		dir_i_size = i_size_पढ़ो(dir);
		credits = OCFS2_SIMPLE_सूची_EXTEND_CREDITS;
		जाओ करो_extend;
	पूर्ण

	करोwn_ग_लिखो(&OCFS2_I(dir)->ip_alloc_sem);
	drop_alloc_sem = 1;
	dir_i_size = i_size_पढ़ो(dir);
	trace_ocfs2_extend_dir((अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno,
			       dir_i_size);

	/* dir->i_size is always block aligned. */
	spin_lock(&OCFS2_I(dir)->ip_lock);
	अगर (dir_i_size == ocfs2_clusters_to_bytes(sb, OCFS2_I(dir)->ip_clusters)) अणु
		spin_unlock(&OCFS2_I(dir)->ip_lock);
		ocfs2_init_dinode_extent_tree(&et, INODE_CACHE(dir),
					      parent_fe_bh);
		num_मुक्त_extents = ocfs2_num_मुक्त_extents(&et);
		अगर (num_मुक्त_extents < 0) अणु
			status = num_मुक्त_extents;
			mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		अगर (!num_मुक्त_extents) अणु
			status = ocfs2_reserve_new_metadata(osb, el, &meta_ac);
			अगर (status < 0) अणु
				अगर (status != -ENOSPC)
					mlog_त्रुटि_सं(status);
				जाओ bail;
			पूर्ण
		पूर्ण

		status = ocfs2_reserve_clusters(osb, 1, &data_ac);
		अगर (status < 0) अणु
			अगर (status != -ENOSPC)
				mlog_त्रुटि_सं(status);
			जाओ bail;
		पूर्ण

		अगर (ocfs2_dir_resv_allowed(osb))
			data_ac->ac_resv = &OCFS2_I(dir)->ip_la_data_resv;

		credits = ocfs2_calc_extend_credits(sb, el);
	पूर्ण अन्यथा अणु
		spin_unlock(&OCFS2_I(dir)->ip_lock);
		credits = OCFS2_SIMPLE_सूची_EXTEND_CREDITS;
	पूर्ण

करो_extend:
	अगर (ocfs2_dir_indexed(dir))
		credits++; /* For attaching the new dirent block to the
			    * dx_root */

	handle = ocfs2_start_trans(osb, credits);
	अगर (IS_ERR(handle)) अणु
		status = PTR_ERR(handle);
		handle = शून्य;
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	status = ocfs2_करो_extend_dir(osb->sb, handle, dir, parent_fe_bh,
				     data_ac, meta_ac, &new_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

	ocfs2_set_new_buffer_uptodate(INODE_CACHE(dir), new_bh);

	status = ocfs2_journal_access_db(handle, INODE_CACHE(dir), new_bh,
					 OCFS2_JOURNAL_ACCESS_CREATE);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण
	स_रखो(new_bh->b_data, 0, sb->s_blocksize);

	de = (काष्ठा ocfs2_dir_entry *) new_bh->b_data;
	de->inode = 0;
	अगर (ocfs2_supports_dir_trailer(dir)) अणु
		de->rec_len = cpu_to_le16(ocfs2_dir_trailer_blk_off(sb));

		ocfs2_init_dir_trailer(dir, new_bh, le16_to_cpu(de->rec_len));

		अगर (ocfs2_dir_indexed(dir)) अणु
			status = ocfs2_dx_dir_link_trailer(dir, handle,
							   dx_root_bh, new_bh);
			अगर (status) अणु
				mlog_त्रुटि_सं(status);
				जाओ bail;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		de->rec_len = cpu_to_le16(sb->s_blocksize);
	पूर्ण
	ocfs2_update_inode_fsync_trans(handle, dir, 1);
	ocfs2_journal_dirty(handle, new_bh);

	dir_i_size += dir->i_sb->s_blocksize;
	i_size_ग_लिखो(dir, dir_i_size);
	dir->i_blocks = ocfs2_inode_sector_count(dir);
	status = ocfs2_mark_inode_dirty(handle, dir, parent_fe_bh);
	अगर (status < 0) अणु
		mlog_त्रुटि_सं(status);
		जाओ bail;
	पूर्ण

bail_bh:
	*new_de_bh = new_bh;
	get_bh(*new_de_bh);
bail:
	अगर (handle)
		ocfs2_commit_trans(osb, handle);
	अगर (drop_alloc_sem)
		up_ग_लिखो(&OCFS2_I(dir)->ip_alloc_sem);

	अगर (data_ac)
		ocfs2_मुक्त_alloc_context(data_ac);
	अगर (meta_ac)
		ocfs2_मुक्त_alloc_context(meta_ac);

	brअन्यथा(new_bh);

	वापस status;
पूर्ण

अटल पूर्णांक ocfs2_find_dir_space_id(काष्ठा inode *dir, काष्ठा buffer_head *di_bh,
				   स्थिर अक्षर *name, पूर्णांक namelen,
				   काष्ठा buffer_head **ret_de_bh,
				   अचिन्हित पूर्णांक *blocks_wanted)
अणु
	पूर्णांक ret;
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_dir_entry *de, *last_de = शून्य;
	अक्षर *de_buf, *limit;
	अचिन्हित दीर्घ offset = 0;
	अचिन्हित पूर्णांक rec_len, new_rec_len, मुक्त_space = dir->i_sb->s_blocksize;

	/*
	 * This calculates how many मुक्त bytes we'd have in block zero, should
	 * this function क्रमce expansion to an extent tree.
	 */
	अगर (ocfs2_new_dir_wants_trailer(dir))
		मुक्त_space = ocfs2_dir_trailer_blk_off(sb) - i_size_पढ़ो(dir);
	अन्यथा
		मुक्त_space = dir->i_sb->s_blocksize - i_size_पढ़ो(dir);

	de_buf = di->id2.i_data.id_data;
	limit = de_buf + i_size_पढ़ो(dir);
	rec_len = OCFS2_सूची_REC_LEN(namelen);

	जबतक (de_buf < limit) अणु
		de = (काष्ठा ocfs2_dir_entry *)de_buf;

		अगर (!ocfs2_check_dir_entry(dir, de, di_bh, offset)) अणु
			ret = -ENOENT;
			जाओ out;
		पूर्ण
		अगर (ocfs2_match(namelen, name, de)) अणु
			ret = -EEXIST;
			जाओ out;
		पूर्ण
		/*
		 * No need to check क्रम a trailing dirent record here as
		 * they're not used क्रम अंतरभूत dirs.
		 */

		अगर (ocfs2_dirent_would_fit(de, rec_len)) अणु
			/* Ok, we found a spot. Return this bh and let
			 * the caller actually fill it in. */
			*ret_de_bh = di_bh;
			get_bh(*ret_de_bh);
			ret = 0;
			जाओ out;
		पूर्ण

		last_de = de;
		de_buf += le16_to_cpu(de->rec_len);
		offset += le16_to_cpu(de->rec_len);
	पूर्ण

	/*
	 * We're going to require expansion of the directory - figure
	 * out how many blocks we'll need so that a place क्रम the
	 * dirent can be found.
	 */
	*blocks_wanted = 1;
	new_rec_len = le16_to_cpu(last_de->rec_len) + मुक्त_space;
	अगर (new_rec_len < (rec_len + OCFS2_सूची_REC_LEN(last_de->name_len)))
		*blocks_wanted = 2;

	ret = -ENOSPC;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_find_dir_space_el(काष्ठा inode *dir, स्थिर अक्षर *name,
				   पूर्णांक namelen, काष्ठा buffer_head **ret_de_bh)
अणु
	अचिन्हित दीर्घ offset;
	काष्ठा buffer_head *bh = शून्य;
	अचिन्हित लघु rec_len;
	काष्ठा ocfs2_dir_entry *de;
	काष्ठा super_block *sb = dir->i_sb;
	पूर्णांक status;
	पूर्णांक blocksize = dir->i_sb->s_blocksize;

	status = ocfs2_पढ़ो_dir_block(dir, 0, &bh, 0);
	अगर (status)
		जाओ bail;

	rec_len = OCFS2_सूची_REC_LEN(namelen);
	offset = 0;
	de = (काष्ठा ocfs2_dir_entry *) bh->b_data;
	जबतक (1) अणु
		अगर ((अक्षर *)de >= sb->s_blocksize + bh->b_data) अणु
			brअन्यथा(bh);
			bh = शून्य;

			अगर (i_size_पढ़ो(dir) <= offset) अणु
				/*
				 * Caller will have to expand this
				 * directory.
				 */
				status = -ENOSPC;
				जाओ bail;
			पूर्ण
			status = ocfs2_पढ़ो_dir_block(dir,
					     offset >> sb->s_blocksize_bits,
					     &bh, 0);
			अगर (status)
				जाओ bail;

			/* move to next block */
			de = (काष्ठा ocfs2_dir_entry *) bh->b_data;
		पूर्ण
		अगर (!ocfs2_check_dir_entry(dir, de, bh, offset)) अणु
			status = -ENOENT;
			जाओ bail;
		पूर्ण
		अगर (ocfs2_match(namelen, name, de)) अणु
			status = -EEXIST;
			जाओ bail;
		पूर्ण

		अगर (ocfs2_skip_dir_trailer(dir, de, offset % blocksize,
					   blocksize))
			जाओ next;

		अगर (ocfs2_dirent_would_fit(de, rec_len)) अणु
			/* Ok, we found a spot. Return this bh and let
			 * the caller actually fill it in. */
			*ret_de_bh = bh;
			get_bh(*ret_de_bh);
			status = 0;
			जाओ bail;
		पूर्ण
next:
		offset += le16_to_cpu(de->rec_len);
		de = (काष्ठा ocfs2_dir_entry *)((अक्षर *) de + le16_to_cpu(de->rec_len));
	पूर्ण

bail:
	brअन्यथा(bh);
	अगर (status)
		mlog_त्रुटि_सं(status);

	वापस status;
पूर्ण

अटल पूर्णांक dx_leaf_sort_cmp(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा ocfs2_dx_entry *entry1 = a;
	स्थिर काष्ठा ocfs2_dx_entry *entry2 = b;
	u32 major_hash1 = le32_to_cpu(entry1->dx_major_hash);
	u32 major_hash2 = le32_to_cpu(entry2->dx_major_hash);
	u32 minor_hash1 = le32_to_cpu(entry1->dx_minor_hash);
	u32 minor_hash2 = le32_to_cpu(entry2->dx_minor_hash);

	अगर (major_hash1 > major_hash2)
		वापस 1;
	अगर (major_hash1 < major_hash2)
		वापस -1;

	/*
	 * It is not strictly necessary to sort by minor
	 */
	अगर (minor_hash1 > minor_hash2)
		वापस 1;
	अगर (minor_hash1 < minor_hash2)
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम dx_leaf_sort_swap(व्योम *a, व्योम *b, पूर्णांक size)
अणु
	काष्ठा ocfs2_dx_entry *entry1 = a;
	काष्ठा ocfs2_dx_entry *entry2 = b;

	BUG_ON(size != माप(*entry1));

	swap(*entry1, *entry2);
पूर्ण

अटल पूर्णांक ocfs2_dx_leaf_same_major(काष्ठा ocfs2_dx_leaf *dx_leaf)
अणु
	काष्ठा ocfs2_dx_entry_list *dl_list = &dx_leaf->dl_list;
	पूर्णांक i, num = le16_to_cpu(dl_list->de_num_used);

	क्रम (i = 0; i < (num - 1); i++) अणु
		अगर (le32_to_cpu(dl_list->de_entries[i].dx_major_hash) !=
		    le32_to_cpu(dl_list->de_entries[i + 1].dx_major_hash))
			वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

/*
 * Find the optimal value to split this leaf on. This expects the leaf
 * entries to be in sorted order.
 *
 * leaf_cpos is the cpos of the leaf we're splitting. insert_hash is
 * the hash we want to insert.
 *
 * This function is only concerned with the major hash - that which
 * determines which cluster an item beदीर्घs to.
 */
अटल पूर्णांक ocfs2_dx_dir_find_leaf_split(काष्ठा ocfs2_dx_leaf *dx_leaf,
					u32 leaf_cpos, u32 insert_hash,
					u32 *split_hash)
अणु
	काष्ठा ocfs2_dx_entry_list *dl_list = &dx_leaf->dl_list;
	पूर्णांक i, num_used = le16_to_cpu(dl_list->de_num_used);
	पूर्णांक allsame;

	/*
	 * There's a couple rare, but nasty corner हालs we have to
	 * check क्रम here. All of them involve a leaf where all value
	 * have the same hash, which is what we look क्रम first.
	 *
	 * Most of the समय, all of the above is false, and we simply
	 * pick the median value क्रम a split.
	 */
	allsame = ocfs2_dx_leaf_same_major(dx_leaf);
	अगर (allsame) अणु
		u32 val = le32_to_cpu(dl_list->de_entries[0].dx_major_hash);

		अगर (val == insert_hash) अणु
			/*
			 * No matter where we would choose to split,
			 * the new entry would want to occupy the same
			 * block as these. Since there's no space left
			 * in their existing block, we know there
			 * won't be space after the split.
			 */
			वापस -ENOSPC;
		पूर्ण

		अगर (val == leaf_cpos) अणु
			/*
			 * Because val is the same as leaf_cpos (which
			 * is the smallest value this leaf can have),
			 * yet is not equal to insert_hash, then we
			 * know that insert_hash *must* be larger than
			 * val (and leaf_cpos). At least cpos+1 in value.
			 *
			 * We also know then, that there cannot be an
			 * adjacent extent (otherwise we'd be looking
			 * at it). Choosing this value gives us a
			 * chance to get some contiguousness.
			 */
			*split_hash = leaf_cpos + 1;
			वापस 0;
		पूर्ण

		अगर (val > insert_hash) अणु
			/*
			 * val can not be the same as insert hash, and
			 * also must be larger than leaf_cpos. Also,
			 * we know that there can't be a leaf between
			 * cpos and val, otherwise the entries with
			 * hash 'val' would be there.
			 */
			*split_hash = val;
			वापस 0;
		पूर्ण

		*split_hash = insert_hash;
		वापस 0;
	पूर्ण

	/*
	 * Since the records are sorted and the checks above
	 * guaranteed that not all records in this block are the same,
	 * we simple travel क्रमward, from the median, and pick the 1st
	 * record whose value is larger than leaf_cpos.
	 */
	क्रम (i = (num_used / 2); i < num_used; i++)
		अगर (le32_to_cpu(dl_list->de_entries[i].dx_major_hash) >
		    leaf_cpos)
			अवरोध;

	BUG_ON(i == num_used); /* Should be impossible */
	*split_hash = le32_to_cpu(dl_list->de_entries[i].dx_major_hash);
	वापस 0;
पूर्ण

/*
 * Transfer all entries in orig_dx_leaves whose major hash is equal to or
 * larger than split_hash पूर्णांकo new_dx_leaves. We use a temporary
 * buffer (पंचांगp_dx_leaf) to make the changes to the original leaf blocks.
 *
 * Since the block offset inside a leaf (cluster) is a स्थिरant mask
 * of minor_hash, we can optimize - an item at block offset X within
 * the original cluster, will be at offset X within the new cluster.
 */
अटल व्योम ocfs2_dx_dir_transfer_leaf(काष्ठा inode *dir, u32 split_hash,
				       handle_t *handle,
				       काष्ठा ocfs2_dx_leaf *पंचांगp_dx_leaf,
				       काष्ठा buffer_head **orig_dx_leaves,
				       काष्ठा buffer_head **new_dx_leaves,
				       पूर्णांक num_dx_leaves)
अणु
	पूर्णांक i, j, num_used;
	u32 major_hash;
	काष्ठा ocfs2_dx_leaf *orig_dx_leaf, *new_dx_leaf;
	काष्ठा ocfs2_dx_entry_list *orig_list, *पंचांगp_list;
	काष्ठा ocfs2_dx_entry *dx_entry;

	पंचांगp_list = &पंचांगp_dx_leaf->dl_list;

	क्रम (i = 0; i < num_dx_leaves; i++) अणु
		orig_dx_leaf = (काष्ठा ocfs2_dx_leaf *) orig_dx_leaves[i]->b_data;
		orig_list = &orig_dx_leaf->dl_list;
		new_dx_leaf = (काष्ठा ocfs2_dx_leaf *) new_dx_leaves[i]->b_data;

		num_used = le16_to_cpu(orig_list->de_num_used);

		स_नकल(पंचांगp_dx_leaf, orig_dx_leaf, dir->i_sb->s_blocksize);
		पंचांगp_list->de_num_used = cpu_to_le16(0);
		स_रखो(&पंचांगp_list->de_entries, 0, माप(*dx_entry)*num_used);

		क्रम (j = 0; j < num_used; j++) अणु
			dx_entry = &orig_list->de_entries[j];
			major_hash = le32_to_cpu(dx_entry->dx_major_hash);
			अगर (major_hash >= split_hash)
				ocfs2_dx_dir_leaf_insert_tail(new_dx_leaf,
							      dx_entry);
			अन्यथा
				ocfs2_dx_dir_leaf_insert_tail(पंचांगp_dx_leaf,
							      dx_entry);
		पूर्ण
		स_नकल(orig_dx_leaf, पंचांगp_dx_leaf, dir->i_sb->s_blocksize);

		ocfs2_journal_dirty(handle, orig_dx_leaves[i]);
		ocfs2_journal_dirty(handle, new_dx_leaves[i]);
	पूर्ण
पूर्ण

अटल पूर्णांक ocfs2_dx_dir_rebalance_credits(काष्ठा ocfs2_super *osb,
					  काष्ठा ocfs2_dx_root_block *dx_root)
अणु
	पूर्णांक credits = ocfs2_clusters_to_blocks(osb->sb, 3);

	credits += ocfs2_calc_extend_credits(osb->sb, &dx_root->dr_list);
	credits += ocfs2_quota_trans_credits(osb->sb);
	वापस credits;
पूर्ण

/*
 * Find the median value in dx_leaf_bh and allocate a new leaf to move
 * half our entries पूर्णांकo.
 */
अटल पूर्णांक ocfs2_dx_dir_rebalance(काष्ठा ocfs2_super *osb, काष्ठा inode *dir,
				  काष्ठा buffer_head *dx_root_bh,
				  काष्ठा buffer_head *dx_leaf_bh,
				  काष्ठा ocfs2_dx_hinfo *hinfo, u32 leaf_cpos,
				  u64 leaf_blkno)
अणु
	काष्ठा ocfs2_dx_leaf *dx_leaf = (काष्ठा ocfs2_dx_leaf *)dx_leaf_bh->b_data;
	पूर्णांक credits, ret, i, num_used, did_quota = 0;
	u32 cpos, split_hash, insert_hash = hinfo->major_hash;
	u64 orig_leaves_start;
	पूर्णांक num_dx_leaves;
	काष्ठा buffer_head **orig_dx_leaves = शून्य;
	काष्ठा buffer_head **new_dx_leaves = शून्य;
	काष्ठा ocfs2_alloc_context *data_ac = शून्य, *meta_ac = शून्य;
	काष्ठा ocfs2_extent_tree et;
	handle_t *handle = शून्य;
	काष्ठा ocfs2_dx_root_block *dx_root;
	काष्ठा ocfs2_dx_leaf *पंचांगp_dx_leaf = शून्य;

	trace_ocfs2_dx_dir_rebalance((अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno,
				     (अचिन्हित दीर्घ दीर्घ)leaf_blkno,
				     insert_hash);

	ocfs2_init_dx_root_extent_tree(&et, INODE_CACHE(dir), dx_root_bh);

	dx_root = (काष्ठा ocfs2_dx_root_block *)dx_root_bh->b_data;
	/*
	 * XXX: This is a rather large limit. We should use a more
	 * realistic value.
	 */
	अगर (le32_to_cpu(dx_root->dr_clusters) == अच_पूर्णांक_उच्च)
		वापस -ENOSPC;

	num_used = le16_to_cpu(dx_leaf->dl_list.de_num_used);
	अगर (num_used < le16_to_cpu(dx_leaf->dl_list.de_count)) अणु
		mlog(ML_ERROR, "DX Dir: %llu, Asked to rebalance empty leaf: "
		     "%llu, %d\n", (अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno,
		     (अचिन्हित दीर्घ दीर्घ)leaf_blkno, num_used);
		ret = -EIO;
		जाओ out;
	पूर्ण

	orig_dx_leaves = ocfs2_dx_dir_kदो_स्मृति_leaves(osb->sb, &num_dx_leaves);
	अगर (!orig_dx_leaves) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	new_dx_leaves = ocfs2_dx_dir_kदो_स्मृति_leaves(osb->sb, शून्य);
	अगर (!new_dx_leaves) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_lock_allocators(dir, &et, 1, 0, &data_ac, &meta_ac);
	अगर (ret) अणु
		अगर (ret != -ENOSPC)
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	credits = ocfs2_dx_dir_rebalance_credits(osb, dx_root);
	handle = ocfs2_start_trans(osb, credits);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		handle = शून्य;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = dquot_alloc_space_nodirty(dir,
				       ocfs2_clusters_to_bytes(dir->i_sb, 1));
	अगर (ret)
		जाओ out_commit;
	did_quota = 1;

	ret = ocfs2_journal_access_dl(handle, INODE_CACHE(dir), dx_leaf_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	/*
	 * This block is changing anyway, so we can sort it in place.
	 */
	sort(dx_leaf->dl_list.de_entries, num_used,
	     माप(काष्ठा ocfs2_dx_entry), dx_leaf_sort_cmp,
	     dx_leaf_sort_swap);

	ocfs2_journal_dirty(handle, dx_leaf_bh);

	ret = ocfs2_dx_dir_find_leaf_split(dx_leaf, leaf_cpos, insert_hash,
					   &split_hash);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ  out_commit;
	पूर्ण

	trace_ocfs2_dx_dir_rebalance_split(leaf_cpos, split_hash, insert_hash);

	/*
	 * We have to carefully order operations here. There are items
	 * which want to be in the new cluster beक्रमe insert, but in
	 * order to put those items in the new cluster, we alter the
	 * old cluster. A failure to insert माला_लो nasty.
	 *
	 * So, start by reserving ग_लिखोs to the old
	 * cluster. ocfs2_dx_dir_new_cluster will reserve ग_लिखोs on
	 * the new cluster क्रम us, beक्रमe inserting it. The insert
	 * won't happen if there's an error beक्रमe that. Once the
	 * insert is करोne then, we can transfer from one leaf पूर्णांकo the
	 * other without fear of hitting any error.
	 */

	/*
	 * The leaf transfer wants some scratch space so that we करोn't
	 * wind up करोing a bunch of expensive स_हटाओ().
	 */
	पंचांगp_dx_leaf = kदो_स्मृति(osb->sb->s_blocksize, GFP_NOFS);
	अगर (!पंचांगp_dx_leaf) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	orig_leaves_start = ocfs2_block_to_cluster_start(dir->i_sb, leaf_blkno);
	ret = ocfs2_पढ़ो_dx_leaves(dir, orig_leaves_start, num_dx_leaves,
				   orig_dx_leaves);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	cpos = split_hash;
	ret = ocfs2_dx_dir_new_cluster(dir, &et, cpos, handle,
				       data_ac, meta_ac, new_dx_leaves,
				       num_dx_leaves);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	क्रम (i = 0; i < num_dx_leaves; i++) अणु
		ret = ocfs2_journal_access_dl(handle, INODE_CACHE(dir),
					      orig_dx_leaves[i],
					      OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_commit;
		पूर्ण

		ret = ocfs2_journal_access_dl(handle, INODE_CACHE(dir),
					      new_dx_leaves[i],
					      OCFS2_JOURNAL_ACCESS_WRITE);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out_commit;
		पूर्ण
	पूर्ण

	ocfs2_dx_dir_transfer_leaf(dir, split_hash, handle, पंचांगp_dx_leaf,
				   orig_dx_leaves, new_dx_leaves, num_dx_leaves);

out_commit:
	अगर (ret < 0 && did_quota)
		dquot_मुक्त_space_nodirty(dir,
				ocfs2_clusters_to_bytes(dir->i_sb, 1));

	ocfs2_update_inode_fsync_trans(handle, dir, 1);
	ocfs2_commit_trans(osb, handle);

out:
	अगर (orig_dx_leaves || new_dx_leaves) अणु
		क्रम (i = 0; i < num_dx_leaves; i++) अणु
			अगर (orig_dx_leaves)
				brअन्यथा(orig_dx_leaves[i]);
			अगर (new_dx_leaves)
				brअन्यथा(new_dx_leaves[i]);
		पूर्ण
		kमुक्त(orig_dx_leaves);
		kमुक्त(new_dx_leaves);
	पूर्ण

	अगर (meta_ac)
		ocfs2_मुक्त_alloc_context(meta_ac);
	अगर (data_ac)
		ocfs2_मुक्त_alloc_context(data_ac);

	kमुक्त(पंचांगp_dx_leaf);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_find_dir_space_dx(काष्ठा ocfs2_super *osb, काष्ठा inode *dir,
				   काष्ठा buffer_head *di_bh,
				   काष्ठा buffer_head *dx_root_bh,
				   स्थिर अक्षर *name, पूर्णांक namelen,
				   काष्ठा ocfs2_dir_lookup_result *lookup)
अणु
	पूर्णांक ret, rebalanced = 0;
	काष्ठा ocfs2_dx_root_block *dx_root;
	काष्ठा buffer_head *dx_leaf_bh = शून्य;
	काष्ठा ocfs2_dx_leaf *dx_leaf;
	u64 blkno;
	u32 leaf_cpos;

	dx_root = (काष्ठा ocfs2_dx_root_block *)dx_root_bh->b_data;

restart_search:
	ret = ocfs2_dx_dir_lookup(dir, &dx_root->dr_list, &lookup->dl_hinfo,
				  &leaf_cpos, &blkno);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = ocfs2_पढ़ो_dx_leaf(dir, blkno, &dx_leaf_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	dx_leaf = (काष्ठा ocfs2_dx_leaf *)dx_leaf_bh->b_data;

	अगर (le16_to_cpu(dx_leaf->dl_list.de_num_used) >=
	    le16_to_cpu(dx_leaf->dl_list.de_count)) अणु
		अगर (rebalanced) अणु
			/*
			 * Rebalancing should have provided us with
			 * space in an appropriate leaf.
			 *
			 * XXX: Is this an abnormal condition then?
			 * Should we prपूर्णांक a message here?
			 */
			ret = -ENOSPC;
			जाओ out;
		पूर्ण

		ret = ocfs2_dx_dir_rebalance(osb, dir, dx_root_bh, dx_leaf_bh,
					     &lookup->dl_hinfo, leaf_cpos,
					     blkno);
		अगर (ret) अणु
			अगर (ret != -ENOSPC)
				mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/*
		 * Restart the lookup. The rebalance might have
		 * changed which block our item fits पूर्णांकo. Mark our
		 * progress, so we only execute this once.
		 */
		brअन्यथा(dx_leaf_bh);
		dx_leaf_bh = शून्य;
		rebalanced = 1;
		जाओ restart_search;
	पूर्ण

	lookup->dl_dx_leaf_bh = dx_leaf_bh;
	dx_leaf_bh = शून्य;

out:
	brअन्यथा(dx_leaf_bh);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_search_dx_मुक्त_list(काष्ठा inode *dir,
				     काष्ठा buffer_head *dx_root_bh,
				     पूर्णांक namelen,
				     काष्ठा ocfs2_dir_lookup_result *lookup)
अणु
	पूर्णांक ret = -ENOSPC;
	काष्ठा buffer_head *leaf_bh = शून्य, *prev_leaf_bh = शून्य;
	काष्ठा ocfs2_dir_block_trailer *db;
	u64 next_block;
	पूर्णांक rec_len = OCFS2_सूची_REC_LEN(namelen);
	काष्ठा ocfs2_dx_root_block *dx_root;

	dx_root = (काष्ठा ocfs2_dx_root_block *)dx_root_bh->b_data;
	next_block = le64_to_cpu(dx_root->dr_मुक्त_blk);

	जबतक (next_block) अणु
		brअन्यथा(prev_leaf_bh);
		prev_leaf_bh = leaf_bh;
		leaf_bh = शून्य;

		ret = ocfs2_पढ़ो_dir_block_direct(dir, next_block, &leaf_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		db = ocfs2_trailer_from_bh(leaf_bh, dir->i_sb);
		अगर (rec_len <= le16_to_cpu(db->db_मुक्त_rec_len)) अणु
			lookup->dl_leaf_bh = leaf_bh;
			lookup->dl_prev_leaf_bh = prev_leaf_bh;
			leaf_bh = शून्य;
			prev_leaf_bh = शून्य;
			अवरोध;
		पूर्ण

		next_block = le64_to_cpu(db->db_मुक्त_next);
	पूर्ण

	अगर (!next_block)
		ret = -ENOSPC;

out:

	brअन्यथा(leaf_bh);
	brअन्यथा(prev_leaf_bh);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_expand_अंतरभूत_dx_root(काष्ठा inode *dir,
				       काष्ठा buffer_head *dx_root_bh)
अणु
	पूर्णांक ret, num_dx_leaves, i, j, did_quota = 0;
	काष्ठा buffer_head **dx_leaves = शून्य;
	काष्ठा ocfs2_extent_tree et;
	u64 insert_blkno;
	काष्ठा ocfs2_alloc_context *data_ac = शून्य;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	handle_t *handle = शून्य;
	काष्ठा ocfs2_dx_root_block *dx_root;
	काष्ठा ocfs2_dx_entry_list *entry_list;
	काष्ठा ocfs2_dx_entry *dx_entry;
	काष्ठा ocfs2_dx_leaf *target_leaf;

	ret = ocfs2_reserve_clusters(osb, 1, &data_ac);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	dx_leaves = ocfs2_dx_dir_kदो_स्मृति_leaves(osb->sb, &num_dx_leaves);
	अगर (!dx_leaves) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	handle = ocfs2_start_trans(osb, ocfs2_calc_dxi_expand_credits(osb->sb));
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ret = dquot_alloc_space_nodirty(dir,
				       ocfs2_clusters_to_bytes(osb->sb, 1));
	अगर (ret)
		जाओ out_commit;
	did_quota = 1;

	/*
	 * We करो this up front, beक्रमe the allocation, so that a
	 * failure to add the dx_root_bh to the journal won't result
	 * us losing clusters.
	 */
	ret = ocfs2_journal_access_dr(handle, INODE_CACHE(dir), dx_root_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	ret = __ocfs2_dx_dir_new_cluster(dir, 0, handle, data_ac, dx_leaves,
					 num_dx_leaves, &insert_blkno);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	/*
	 * Transfer the entries from our dx_root पूर्णांकo the appropriate
	 * block
	 */
	dx_root = (काष्ठा ocfs2_dx_root_block *) dx_root_bh->b_data;
	entry_list = &dx_root->dr_entries;

	क्रम (i = 0; i < le16_to_cpu(entry_list->de_num_used); i++) अणु
		dx_entry = &entry_list->de_entries[i];

		j = __ocfs2_dx_dir_hash_idx(osb,
					    le32_to_cpu(dx_entry->dx_minor_hash));
		target_leaf = (काष्ठा ocfs2_dx_leaf *)dx_leaves[j]->b_data;

		ocfs2_dx_dir_leaf_insert_tail(target_leaf, dx_entry);

		/* Each leaf has been passed to the journal alपढ़ोy
		 * via __ocfs2_dx_dir_new_cluster() */
	पूर्ण

	dx_root->dr_flags &= ~OCFS2_DX_FLAG_INLINE;
	स_रखो(&dx_root->dr_list, 0, osb->sb->s_blocksize -
	       दुरत्व(काष्ठा ocfs2_dx_root_block, dr_list));
	dx_root->dr_list.l_count =
		cpu_to_le16(ocfs2_extent_recs_per_dx_root(osb->sb));

	/* This should never fail considering we start with an empty
	 * dx_root. */
	ocfs2_init_dx_root_extent_tree(&et, INODE_CACHE(dir), dx_root_bh);
	ret = ocfs2_insert_extent(handle, &et, 0, insert_blkno, 1, 0, शून्य);
	अगर (ret)
		mlog_त्रुटि_सं(ret);
	did_quota = 0;

	ocfs2_update_inode_fsync_trans(handle, dir, 1);
	ocfs2_journal_dirty(handle, dx_root_bh);

out_commit:
	अगर (ret < 0 && did_quota)
		dquot_मुक्त_space_nodirty(dir,
					  ocfs2_clusters_to_bytes(dir->i_sb, 1));

	ocfs2_commit_trans(osb, handle);

out:
	अगर (data_ac)
		ocfs2_मुक्त_alloc_context(data_ac);

	अगर (dx_leaves) अणु
		क्रम (i = 0; i < num_dx_leaves; i++)
			brअन्यथा(dx_leaves[i]);
		kमुक्त(dx_leaves);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_अंतरभूत_dx_has_space(काष्ठा buffer_head *dx_root_bh)
अणु
	काष्ठा ocfs2_dx_root_block *dx_root;
	काष्ठा ocfs2_dx_entry_list *entry_list;

	dx_root = (काष्ठा ocfs2_dx_root_block *) dx_root_bh->b_data;
	entry_list = &dx_root->dr_entries;

	अगर (le16_to_cpu(entry_list->de_num_used) >=
	    le16_to_cpu(entry_list->de_count))
		वापस -ENOSPC;

	वापस 0;
पूर्ण

अटल पूर्णांक ocfs2_prepare_dx_dir_क्रम_insert(काष्ठा inode *dir,
					   काष्ठा buffer_head *di_bh,
					   स्थिर अक्षर *name,
					   पूर्णांक namelen,
					   काष्ठा ocfs2_dir_lookup_result *lookup)
अणु
	पूर्णांक ret, मुक्त_dx_root = 1;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	काष्ठा buffer_head *dx_root_bh = शून्य;
	काष्ठा buffer_head *leaf_bh = शून्य;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_dx_root_block *dx_root;

	ret = ocfs2_पढ़ो_dx_root(dir, di, &dx_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	dx_root = (काष्ठा ocfs2_dx_root_block *)dx_root_bh->b_data;
	अगर (le32_to_cpu(dx_root->dr_num_entries) == OCFS2_DX_ENTRIES_MAX) अणु
		ret = -ENOSPC;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (ocfs2_dx_root_अंतरभूत(dx_root)) अणु
		ret = ocfs2_अंतरभूत_dx_has_space(dx_root_bh);

		अगर (ret == 0)
			जाओ search_el;

		/*
		 * We ran out of room in the root block. Expand it to
		 * an extent, then allow ocfs2_find_dir_space_dx to करो
		 * the rest.
		 */
		ret = ocfs2_expand_अंतरभूत_dx_root(dir, dx_root_bh);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Insert preparation क्रम an indexed directory is split पूर्णांकo two
	 * steps. The call to find_dir_space_dx reserves room in the index क्रम
	 * an additional item. If we run out of space there, it's a real error
	 * we can't जारी on.
	 */
	ret = ocfs2_find_dir_space_dx(osb, dir, di_bh, dx_root_bh, name,
				      namelen, lookup);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

search_el:
	/*
	 * Next, we need to find space in the unindexed tree. This call
	 * searches using the मुक्त space linked list. If the unindexed tree
	 * lacks sufficient space, we'll expand it below. The expansion code
	 * is smart enough to add any new blocks to the मुक्त space list.
	 */
	ret = ocfs2_search_dx_मुक्त_list(dir, dx_root_bh, namelen, lookup);
	अगर (ret && ret != -ENOSPC) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/* Do this up here - ocfs2_extend_dir might need the dx_root */
	lookup->dl_dx_root_bh = dx_root_bh;
	मुक्त_dx_root = 0;

	अगर (ret == -ENOSPC) अणु
		ret = ocfs2_extend_dir(osb, dir, di_bh, 1, lookup, &leaf_bh);

		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		/*
		 * We make the assumption here that new leaf blocks are added
		 * to the front of our मुक्त list.
		 */
		lookup->dl_prev_leaf_bh = शून्य;
		lookup->dl_leaf_bh = leaf_bh;
	पूर्ण

out:
	अगर (मुक्त_dx_root)
		brअन्यथा(dx_root_bh);
	वापस ret;
पूर्ण

/*
 * Get a directory पढ़ोy क्रम insert. Any directory allocation required
 * happens here. Success वापसs zero, and enough context in the dir
 * lookup result that ocfs2_add_entry() will be able complete the task
 * with minimal perक्रमmance impact.
 */
पूर्णांक ocfs2_prepare_dir_क्रम_insert(काष्ठा ocfs2_super *osb,
				 काष्ठा inode *dir,
				 काष्ठा buffer_head *parent_fe_bh,
				 स्थिर अक्षर *name,
				 पूर्णांक namelen,
				 काष्ठा ocfs2_dir_lookup_result *lookup)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक blocks_wanted = 1;
	काष्ठा buffer_head *bh = शून्य;

	trace_ocfs2_prepare_dir_क्रम_insert(
		(अचिन्हित दीर्घ दीर्घ)OCFS2_I(dir)->ip_blkno, namelen);

	अगर (!namelen) अणु
		ret = -EINVAL;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	/*
	 * Do this up front to reduce confusion.
	 *
	 * The directory might start अंतरभूत, then be turned पूर्णांकo an
	 * indexed one, in which हाल we'd need to hash deep inside
	 * ocfs2_find_dir_space_id(). Since
	 * ocfs2_prepare_dx_dir_क्रम_insert() also needs this hash
	 * करोne, there seems no poपूर्णांक in spपढ़ोing out the calls. We
	 * can optimize away the हाल where the file प्रणाली करोesn't
	 * support indexing.
	 */
	अगर (ocfs2_supports_indexed_dirs(osb))
		ocfs2_dx_dir_name_hash(dir, name, namelen, &lookup->dl_hinfo);

	अगर (ocfs2_dir_indexed(dir)) अणु
		ret = ocfs2_prepare_dx_dir_क्रम_insert(dir, parent_fe_bh,
						      name, namelen, lookup);
		अगर (ret)
			mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (OCFS2_I(dir)->ip_dyn_features & OCFS2_INLINE_DATA_FL) अणु
		ret = ocfs2_find_dir_space_id(dir, parent_fe_bh, name,
					      namelen, &bh, &blocks_wanted);
	पूर्ण अन्यथा
		ret = ocfs2_find_dir_space_el(dir, name, namelen, &bh);

	अगर (ret && ret != -ENOSPC) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	अगर (ret == -ENOSPC) अणु
		/*
		 * We have to expand the directory to add this name.
		 */
		BUG_ON(bh);

		ret = ocfs2_extend_dir(osb, dir, parent_fe_bh, blocks_wanted,
				       lookup, &bh);
		अगर (ret) अणु
			अगर (ret != -ENOSPC)
				mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		BUG_ON(!bh);
	पूर्ण

	lookup->dl_leaf_bh = bh;
	bh = शून्य;
out:
	brअन्यथा(bh);
	वापस ret;
पूर्ण

अटल पूर्णांक ocfs2_dx_dir_हटाओ_index(काष्ठा inode *dir,
				     काष्ठा buffer_head *di_bh,
				     काष्ठा buffer_head *dx_root_bh)
अणु
	पूर्णांक ret;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_dx_root_block *dx_root;
	काष्ठा inode *dx_alloc_inode = शून्य;
	काष्ठा buffer_head *dx_alloc_bh = शून्य;
	handle_t *handle;
	u64 blk;
	u16 bit;
	u64 bg_blkno;

	dx_root = (काष्ठा ocfs2_dx_root_block *) dx_root_bh->b_data;

	dx_alloc_inode = ocfs2_get_प्रणाली_file_inode(osb,
					EXTENT_ALLOC_SYSTEM_INODE,
					le16_to_cpu(dx_root->dr_suballoc_slot));
	अगर (!dx_alloc_inode) अणु
		ret = -ENOMEM;
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	inode_lock(dx_alloc_inode);

	ret = ocfs2_inode_lock(dx_alloc_inode, &dx_alloc_bh, 1);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_mutex;
	पूर्ण

	handle = ocfs2_start_trans(osb, OCFS2_DX_ROOT_REMOVE_CREDITS);
	अगर (IS_ERR(handle)) अणु
		ret = PTR_ERR(handle);
		mlog_त्रुटि_सं(ret);
		जाओ out_unlock;
	पूर्ण

	ret = ocfs2_journal_access_di(handle, INODE_CACHE(dir), di_bh,
				      OCFS2_JOURNAL_ACCESS_WRITE);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out_commit;
	पूर्ण

	spin_lock(&OCFS2_I(dir)->ip_lock);
	OCFS2_I(dir)->ip_dyn_features &= ~OCFS2_INDEXED_सूची_FL;
	di->i_dyn_features = cpu_to_le16(OCFS2_I(dir)->ip_dyn_features);
	spin_unlock(&OCFS2_I(dir)->ip_lock);
	di->i_dx_root = cpu_to_le64(0ULL);
	ocfs2_update_inode_fsync_trans(handle, dir, 1);

	ocfs2_journal_dirty(handle, di_bh);

	blk = le64_to_cpu(dx_root->dr_blkno);
	bit = le16_to_cpu(dx_root->dr_suballoc_bit);
	अगर (dx_root->dr_suballoc_loc)
		bg_blkno = le64_to_cpu(dx_root->dr_suballoc_loc);
	अन्यथा
		bg_blkno = ocfs2_which_suballoc_group(blk, bit);
	ret = ocfs2_मुक्त_suballoc_bits(handle, dx_alloc_inode, dx_alloc_bh,
				       bit, bg_blkno, 1);
	अगर (ret)
		mlog_त्रुटि_सं(ret);

out_commit:
	ocfs2_commit_trans(osb, handle);

out_unlock:
	ocfs2_inode_unlock(dx_alloc_inode, 1);

out_mutex:
	inode_unlock(dx_alloc_inode);
	brअन्यथा(dx_alloc_bh);
out:
	iput(dx_alloc_inode);
	वापस ret;
पूर्ण

पूर्णांक ocfs2_dx_dir_truncate(काष्ठा inode *dir, काष्ठा buffer_head *di_bh)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक clen;
	u32 major_hash = अच_पूर्णांक_उच्च, p_cpos, cpos;
	u64 blkno;
	काष्ठा ocfs2_super *osb = OCFS2_SB(dir->i_sb);
	काष्ठा buffer_head *dx_root_bh = शून्य;
	काष्ठा ocfs2_dx_root_block *dx_root;
	काष्ठा ocfs2_dinode *di = (काष्ठा ocfs2_dinode *)di_bh->b_data;
	काष्ठा ocfs2_cached_dealloc_ctxt dealloc;
	काष्ठा ocfs2_extent_tree et;

	ocfs2_init_dealloc_ctxt(&dealloc);

	अगर (!ocfs2_dir_indexed(dir))
		वापस 0;

	ret = ocfs2_पढ़ो_dx_root(dir, di, &dx_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण
	dx_root = (काष्ठा ocfs2_dx_root_block *)dx_root_bh->b_data;

	अगर (ocfs2_dx_root_अंतरभूत(dx_root))
		जाओ हटाओ_index;

	ocfs2_init_dx_root_extent_tree(&et, INODE_CACHE(dir), dx_root_bh);

	/* XXX: What अगर dr_clusters is too large? */
	जबतक (le32_to_cpu(dx_root->dr_clusters)) अणु
		ret = ocfs2_dx_dir_lookup_rec(dir, &dx_root->dr_list,
					      major_hash, &cpos, &blkno, &clen);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		p_cpos = ocfs2_blocks_to_clusters(dir->i_sb, blkno);

		ret = ocfs2_हटाओ_btree_range(dir, &et, cpos, p_cpos, clen, 0,
					       &dealloc, 0, false);
		अगर (ret) अणु
			mlog_त्रुटि_सं(ret);
			जाओ out;
		पूर्ण

		अगर (cpos == 0)
			अवरोध;

		major_hash = cpos - 1;
	पूर्ण

हटाओ_index:
	ret = ocfs2_dx_dir_हटाओ_index(dir, di_bh, dx_root_bh);
	अगर (ret) अणु
		mlog_त्रुटि_सं(ret);
		जाओ out;
	पूर्ण

	ocfs2_हटाओ_from_cache(INODE_CACHE(dir), dx_root_bh);
out:
	ocfs2_schedule_truncate_log_flush(osb, 1);
	ocfs2_run_deallocs(osb, &dealloc);

	brअन्यथा(dx_root_bh);
	वापस ret;
पूर्ण
