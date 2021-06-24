<शैली गुरु>
/*
 * truncate.c
 *
 * PURPOSE
 *	Truncate handling routines क्रम the OSTA-UDF(पंचांग) fileप्रणाली.
 *
 * COPYRIGHT
 *	This file is distributed under the terms of the GNU General Public
 *	License (GPL). Copies of the GPL can be obtained from:
 *		ftp://prep.ai.mit.edu/pub/gnu/GPL
 *	Each contributing author retains all rights to their own work.
 *
 *  (C) 1999-2004 Ben Fennema
 *  (C) 1999 Stelias Computing Inc
 *
 * HISTORY
 *
 *  02/24/99 blf  Created.
 *
 */

#समावेश "udfdecl.h"
#समावेश <linux/fs.h>
#समावेश <linux/mm.h>

#समावेश "udf_i.h"
#समावेश "udf_sb.h"

अटल व्योम extent_trunc(काष्ठा inode *inode, काष्ठा extent_position *epos,
			 काष्ठा kernel_lb_addr *eloc, पूर्णांक8_t etype, uपूर्णांक32_t elen,
			 uपूर्णांक32_t nelen)
अणु
	काष्ठा kernel_lb_addr neloc = अणुपूर्ण;
	पूर्णांक last_block = (elen + inode->i_sb->s_blocksize - 1) >>
		inode->i_sb->s_blocksize_bits;
	पूर्णांक first_block = (nelen + inode->i_sb->s_blocksize - 1) >>
		inode->i_sb->s_blocksize_bits;

	अगर (nelen) अणु
		अगर (etype == (EXT_NOT_RECORDED_ALLOCATED >> 30)) अणु
			udf_मुक्त_blocks(inode->i_sb, inode, eloc, 0,
					last_block);
			etype = (EXT_NOT_RECORDED_NOT_ALLOCATED >> 30);
		पूर्ण अन्यथा
			neloc = *eloc;
		nelen = (etype << 30) | nelen;
	पूर्ण

	अगर (elen != nelen) अणु
		udf_ग_लिखो_aext(inode, epos, &neloc, nelen, 0);
		अगर (last_block > first_block) अणु
			अगर (etype == (EXT_RECORDED_ALLOCATED >> 30))
				mark_inode_dirty(inode);

			अगर (etype != (EXT_NOT_RECORDED_NOT_ALLOCATED >> 30))
				udf_मुक्त_blocks(inode->i_sb, inode, eloc,
						first_block,
						last_block - first_block);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Truncate the last extent to match i_size. This function assumes
 * that pपुनः_स्मृतिation extent is alपढ़ोy truncated.
 */
व्योम udf_truncate_tail_extent(काष्ठा inode *inode)
अणु
	काष्ठा extent_position epos = अणुपूर्ण;
	काष्ठा kernel_lb_addr eloc;
	uपूर्णांक32_t elen, nelen;
	uपूर्णांक64_t lbcount = 0;
	पूर्णांक8_t etype = -1, netype;
	पूर्णांक adsize;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);

	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB ||
	    inode->i_size == iinfo->i_lenExtents)
		वापस;
	/* Are we going to delete the file anyway? */
	अगर (inode->i_nlink == 0)
		वापस;

	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = माप(काष्ठा लघु_ad);
	अन्यथा अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = माप(काष्ठा दीर्घ_ad);
	अन्यथा
		BUG();

	/* Find the last extent in the file */
	जबतक ((netype = udf_next_aext(inode, &epos, &eloc, &elen, 1)) != -1) अणु
		etype = netype;
		lbcount += elen;
		अगर (lbcount > inode->i_size) अणु
			अगर (lbcount - inode->i_size >= inode->i_sb->s_blocksize)
				udf_warn(inode->i_sb,
					 "Too long extent after EOF in inode %u: i_size: %lld lbcount: %lld extent %u+%u\n",
					 (अचिन्हित)inode->i_ino,
					 (दीर्घ दीर्घ)inode->i_size,
					 (दीर्घ दीर्घ)lbcount,
					 (अचिन्हित)eloc.logicalBlockNum,
					 (अचिन्हित)elen);
			nelen = elen - (lbcount - inode->i_size);
			epos.offset -= adsize;
			extent_trunc(inode, &epos, &eloc, etype, elen, nelen);
			epos.offset += adsize;
			अगर (udf_next_aext(inode, &epos, &eloc, &elen, 1) != -1)
				udf_err(inode->i_sb,
					"Extent after EOF in inode %u\n",
					(अचिन्हित)inode->i_ino);
			अवरोध;
		पूर्ण
	पूर्ण
	/* This inode entry is in-memory only and thus we करोn't have to mark
	 * the inode dirty */
	iinfo->i_lenExtents = inode->i_size;
	brअन्यथा(epos.bh);
पूर्ण

व्योम udf_discard_pपुनः_स्मृति(काष्ठा inode *inode)
अणु
	काष्ठा extent_position epos = अणु शून्य, 0, अणु0, 0पूर्ण पूर्ण;
	काष्ठा kernel_lb_addr eloc;
	uपूर्णांक32_t elen;
	uपूर्णांक64_t lbcount = 0;
	पूर्णांक8_t etype = -1, netype;
	पूर्णांक adsize;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);

	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB ||
	    inode->i_size == iinfo->i_lenExtents)
		वापस;

	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = माप(काष्ठा लघु_ad);
	अन्यथा अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = माप(काष्ठा दीर्घ_ad);
	अन्यथा
		adsize = 0;

	epos.block = iinfo->i_location;

	/* Find the last extent in the file */
	जबतक ((netype = udf_next_aext(inode, &epos, &eloc, &elen, 1)) != -1) अणु
		etype = netype;
		lbcount += elen;
	पूर्ण
	अगर (etype == (EXT_NOT_RECORDED_ALLOCATED >> 30)) अणु
		epos.offset -= adsize;
		lbcount -= elen;
		extent_trunc(inode, &epos, &eloc, etype, elen, 0);
		अगर (!epos.bh) अणु
			iinfo->i_lenAlloc =
				epos.offset -
				udf_file_entry_alloc_offset(inode);
			mark_inode_dirty(inode);
		पूर्ण अन्यथा अणु
			काष्ठा allocExtDesc *aed =
				(काष्ठा allocExtDesc *)(epos.bh->b_data);
			aed->lengthAllocDescs =
				cpu_to_le32(epos.offset -
					    माप(काष्ठा allocExtDesc));
			अगर (!UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT) ||
			    UDF_SB(inode->i_sb)->s_udfrev >= 0x0201)
				udf_update_tag(epos.bh->b_data, epos.offset);
			अन्यथा
				udf_update_tag(epos.bh->b_data,
					       माप(काष्ठा allocExtDesc));
			mark_buffer_dirty_inode(epos.bh, inode);
		पूर्ण
	पूर्ण
	/* This inode entry is in-memory only and thus we करोn't have to mark
	 * the inode dirty */
	iinfo->i_lenExtents = lbcount;
	brअन्यथा(epos.bh);
पूर्ण

अटल व्योम udf_update_alloc_ext_desc(काष्ठा inode *inode,
				      काष्ठा extent_position *epos,
				      u32 lenalloc)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा udf_sb_info *sbi = UDF_SB(sb);

	काष्ठा allocExtDesc *aed = (काष्ठा allocExtDesc *) (epos->bh->b_data);
	पूर्णांक len = माप(काष्ठा allocExtDesc);

	aed->lengthAllocDescs =	cpu_to_le32(lenalloc);
	अगर (!UDF_QUERY_FLAG(sb, UDF_FLAG_STRICT) || sbi->s_udfrev >= 0x0201)
		len += lenalloc;

	udf_update_tag(epos->bh->b_data, len);
	mark_buffer_dirty_inode(epos->bh, inode);
पूर्ण

/*
 * Truncate extents of inode to inode->i_size. This function can be used only
 * क्रम making file लघुer. For making file दीर्घer, udf_extend_file() has to
 * be used.
 */
पूर्णांक udf_truncate_extents(काष्ठा inode *inode)
अणु
	काष्ठा extent_position epos;
	काष्ठा kernel_lb_addr eloc, neloc = अणुपूर्ण;
	uपूर्णांक32_t elen, nelen = 0, indirect_ext_len = 0, lenalloc;
	पूर्णांक8_t etype;
	काष्ठा super_block *sb = inode->i_sb;
	sector_t first_block = inode->i_size >> sb->s_blocksize_bits, offset;
	loff_t byte_offset;
	पूर्णांक adsize;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);

	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
		adsize = माप(काष्ठा लघु_ad);
	अन्यथा अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
		adsize = माप(काष्ठा दीर्घ_ad);
	अन्यथा
		BUG();

	etype = inode_bmap(inode, first_block, &epos, &eloc, &elen, &offset);
	byte_offset = (offset << sb->s_blocksize_bits) +
		(inode->i_size & (sb->s_blocksize - 1));
	अगर (etype == -1) अणु
		/* We should extend the file? */
		WARN_ON(byte_offset);
		वापस 0;
	पूर्ण
	epos.offset -= adsize;
	extent_trunc(inode, &epos, &eloc, etype, elen, byte_offset);
	epos.offset += adsize;
	अगर (byte_offset)
		lenalloc = epos.offset;
	अन्यथा
		lenalloc = epos.offset - adsize;

	अगर (!epos.bh)
		lenalloc -= udf_file_entry_alloc_offset(inode);
	अन्यथा
		lenalloc -= माप(काष्ठा allocExtDesc);

	जबतक ((etype = udf_current_aext(inode, &epos, &eloc,
					 &elen, 0)) != -1) अणु
		अगर (etype == (EXT_NEXT_EXTENT_ALLOCDESCS >> 30)) अणु
			udf_ग_लिखो_aext(inode, &epos, &neloc, nelen, 0);
			अगर (indirect_ext_len) अणु
				/* We managed to मुक्त all extents in the
				 * indirect extent - मुक्त it too */
				BUG_ON(!epos.bh);
				udf_मुक्त_blocks(sb, शून्य, &epos.block,
						0, indirect_ext_len);
			पूर्ण अन्यथा अगर (!epos.bh) अणु
				iinfo->i_lenAlloc = lenalloc;
				mark_inode_dirty(inode);
			पूर्ण अन्यथा
				udf_update_alloc_ext_desc(inode,
						&epos, lenalloc);
			brअन्यथा(epos.bh);
			epos.offset = माप(काष्ठा allocExtDesc);
			epos.block = eloc;
			epos.bh = udf_tपढ़ो(sb,
					udf_get_lb_pblock(sb, &eloc, 0));
			/* Error पढ़ोing indirect block? */
			अगर (!epos.bh)
				वापस -EIO;
			अगर (elen)
				indirect_ext_len =
					(elen + sb->s_blocksize - 1) >>
					sb->s_blocksize_bits;
			अन्यथा
				indirect_ext_len = 1;
		पूर्ण अन्यथा अणु
			extent_trunc(inode, &epos, &eloc, etype, elen, 0);
			epos.offset += adsize;
		पूर्ण
	पूर्ण

	अगर (indirect_ext_len) अणु
		BUG_ON(!epos.bh);
		udf_मुक्त_blocks(sb, शून्य, &epos.block, 0, indirect_ext_len);
	पूर्ण अन्यथा अगर (!epos.bh) अणु
		iinfo->i_lenAlloc = lenalloc;
		mark_inode_dirty(inode);
	पूर्ण अन्यथा
		udf_update_alloc_ext_desc(inode, &epos, lenalloc);
	iinfo->i_lenExtents = inode->i_size;

	brअन्यथा(epos.bh);
	वापस 0;
पूर्ण
