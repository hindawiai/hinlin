<शैली गुरु>
/*
 * namei.c
 *
 * PURPOSE
 *      Inode name handling routines क्रम the OSTA-UDF(पंचांग) fileप्रणाली.
 *
 * COPYRIGHT
 *      This file is distributed under the terms of the GNU General Public
 *      License (GPL). Copies of the GPL can be obtained from:
 *              ftp://prep.ai.mit.edu/pub/gnu/GPL
 *      Each contributing author retains all rights to their own work.
 *
 *  (C) 1998-2004 Ben Fennema
 *  (C) 1999-2000 Stelias Computing Inc
 *
 * HISTORY
 *
 *  12/12/98 blf  Created. Split out the lookup code from dir.c
 *  04/19/99 blf  link, mknod, symlink support
 */

#समावेश "udfdecl.h"

#समावेश "udf_i.h"
#समावेश "udf_sb.h"
#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/crc-itu-t.h>
#समावेश <linux/exportfs.h>

अटल अंतरभूत पूर्णांक udf_match(पूर्णांक len1, स्थिर अचिन्हित अक्षर *name1, पूर्णांक len2,
			    स्थिर अचिन्हित अक्षर *name2)
अणु
	अगर (len1 != len2)
		वापस 0;

	वापस !स_भेद(name1, name2, len1);
पूर्ण

पूर्णांक udf_ग_लिखो_fi(काष्ठा inode *inode, काष्ठा fileIdentDesc *cfi,
		 काष्ठा fileIdentDesc *sfi, काष्ठा udf_fileident_bh *fibh,
		 uपूर्णांक8_t *impuse, uपूर्णांक8_t *fileident)
अणु
	uपूर्णांक16_t crclen = fibh->eoffset - fibh->soffset - माप(काष्ठा tag);
	uपूर्णांक16_t crc;
	पूर्णांक offset;
	uपूर्णांक16_t liu = le16_to_cpu(cfi->lengthOfImpUse);
	uपूर्णांक8_t lfi = cfi->lengthFileIdent;
	पूर्णांक padlen = fibh->eoffset - fibh->soffset - liu - lfi -
		माप(काष्ठा fileIdentDesc);
	पूर्णांक adinicb = 0;

	अगर (UDF_I(inode)->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		adinicb = 1;

	offset = fibh->soffset + माप(काष्ठा fileIdentDesc);

	अगर (impuse) अणु
		अगर (adinicb || (offset + liu < 0)) अणु
			स_नकल((uपूर्णांक8_t *)sfi->impUse, impuse, liu);
		पूर्ण अन्यथा अगर (offset >= 0) अणु
			स_नकल(fibh->ebh->b_data + offset, impuse, liu);
		पूर्ण अन्यथा अणु
			स_नकल((uपूर्णांक8_t *)sfi->impUse, impuse, -offset);
			स_नकल(fibh->ebh->b_data, impuse - offset,
				liu + offset);
		पूर्ण
	पूर्ण

	offset += liu;

	अगर (fileident) अणु
		अगर (adinicb || (offset + lfi < 0)) अणु
			स_नकल((uपूर्णांक8_t *)sfi->fileIdent + liu, fileident, lfi);
		पूर्ण अन्यथा अगर (offset >= 0) अणु
			स_नकल(fibh->ebh->b_data + offset, fileident, lfi);
		पूर्ण अन्यथा अणु
			स_नकल((uपूर्णांक8_t *)sfi->fileIdent + liu, fileident,
				-offset);
			स_नकल(fibh->ebh->b_data, fileident - offset,
				lfi + offset);
		पूर्ण
	पूर्ण

	offset += lfi;

	अगर (adinicb || (offset + padlen < 0)) अणु
		स_रखो((uपूर्णांक8_t *)sfi->padding + liu + lfi, 0x00, padlen);
	पूर्ण अन्यथा अगर (offset >= 0) अणु
		स_रखो(fibh->ebh->b_data + offset, 0x00, padlen);
	पूर्ण अन्यथा अणु
		स_रखो((uपूर्णांक8_t *)sfi->padding + liu + lfi, 0x00, -offset);
		स_रखो(fibh->ebh->b_data, 0x00, padlen + offset);
	पूर्ण

	crc = crc_itu_t(0, (uपूर्णांक8_t *)cfi + माप(काष्ठा tag),
		      माप(काष्ठा fileIdentDesc) - माप(काष्ठा tag));

	अगर (fibh->sbh == fibh->ebh) अणु
		crc = crc_itu_t(crc, (uपूर्णांक8_t *)sfi->impUse,
			      crclen + माप(काष्ठा tag) -
			      माप(काष्ठा fileIdentDesc));
	पूर्ण अन्यथा अगर (माप(काष्ठा fileIdentDesc) >= -fibh->soffset) अणु
		crc = crc_itu_t(crc, fibh->ebh->b_data +
					माप(काष्ठा fileIdentDesc) +
					fibh->soffset,
			      crclen + माप(काष्ठा tag) -
					माप(काष्ठा fileIdentDesc));
	पूर्ण अन्यथा अणु
		crc = crc_itu_t(crc, (uपूर्णांक8_t *)sfi->impUse,
			      -fibh->soffset - माप(काष्ठा fileIdentDesc));
		crc = crc_itu_t(crc, fibh->ebh->b_data, fibh->eoffset);
	पूर्ण

	cfi->descTag.descCRC = cpu_to_le16(crc);
	cfi->descTag.descCRCLength = cpu_to_le16(crclen);
	cfi->descTag.tagChecksum = udf_tag_checksum(&cfi->descTag);

	अगर (adinicb || (माप(काष्ठा fileIdentDesc) <= -fibh->soffset)) अणु
		स_नकल((uपूर्णांक8_t *)sfi, (uपूर्णांक8_t *)cfi,
			माप(काष्ठा fileIdentDesc));
	पूर्ण अन्यथा अणु
		स_नकल((uपूर्णांक8_t *)sfi, (uपूर्णांक8_t *)cfi, -fibh->soffset);
		स_नकल(fibh->ebh->b_data, (uपूर्णांक8_t *)cfi - fibh->soffset,
		       माप(काष्ठा fileIdentDesc) + fibh->soffset);
	पूर्ण

	अगर (adinicb) अणु
		mark_inode_dirty(inode);
	पूर्ण अन्यथा अणु
		अगर (fibh->sbh != fibh->ebh)
			mark_buffer_dirty_inode(fibh->ebh, inode);
		mark_buffer_dirty_inode(fibh->sbh, inode);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * udf_find_entry - find entry in given directory.
 *
 * @dir:	directory inode to search in
 * @child:	qstr of the name
 * @fibh:	buffer head / inode with file identअगरier descriptor we found
 * @cfi:	found file identअगरier descriptor with given name
 *
 * This function searches in the directory @dir क्रम a file name @child. When
 * found, @fibh poपूर्णांकs to the buffer head(s) (bh is शून्य क्रम in ICB
 * directories) containing the file identअगरier descriptor (FID). In that हाल
 * the function वापसs poपूर्णांकer to the FID in the buffer or inode - but note
 * that FID may be split among two buffers (blocks) so accessing it via that
 * poपूर्णांकer isn't easily possible. This poपूर्णांकer can be used only as an iterator
 * क्रम other directory manipulation functions. For inspection of the FID @cfi
 * can be used - the found FID is copied there.
 *
 * Returns poपूर्णांकer to FID, शून्य when nothing found, or error code.
 */
अटल काष्ठा fileIdentDesc *udf_find_entry(काष्ठा inode *dir,
					    स्थिर काष्ठा qstr *child,
					    काष्ठा udf_fileident_bh *fibh,
					    काष्ठा fileIdentDesc *cfi)
अणु
	काष्ठा fileIdentDesc *fi = शून्य;
	loff_t f_pos;
	udf_pblk_t block;
	पूर्णांक flen;
	अचिन्हित अक्षर *fname = शून्य, *copy_name = शून्य;
	अचिन्हित अक्षर *nameptr;
	uपूर्णांक8_t lfi;
	uपूर्णांक16_t liu;
	loff_t size;
	काष्ठा kernel_lb_addr eloc;
	uपूर्णांक32_t elen;
	sector_t offset;
	काष्ठा extent_position epos = अणुपूर्ण;
	काष्ठा udf_inode_info *dinfo = UDF_I(dir);
	पूर्णांक isकरोtकरोt = child->len == 2 &&
		child->name[0] == '.' && child->name[1] == '.';
	काष्ठा super_block *sb = dir->i_sb;

	size = udf_ext0_offset(dir) + dir->i_size;
	f_pos = udf_ext0_offset(dir);

	fibh->sbh = fibh->ebh = शून्य;
	fibh->soffset = fibh->eoffset = f_pos & (sb->s_blocksize - 1);
	अगर (dinfo->i_alloc_type != ICBTAG_FLAG_AD_IN_ICB) अणु
		अगर (inode_bmap(dir, f_pos >> sb->s_blocksize_bits, &epos,
		    &eloc, &elen, &offset) != (EXT_RECORDED_ALLOCATED >> 30)) अणु
			fi = ERR_PTR(-EIO);
			जाओ out_err;
		पूर्ण

		block = udf_get_lb_pblock(sb, &eloc, offset);
		अगर ((++offset << sb->s_blocksize_bits) < elen) अणु
			अगर (dinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
				epos.offset -= माप(काष्ठा लघु_ad);
			अन्यथा अगर (dinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
				epos.offset -= माप(काष्ठा दीर्घ_ad);
		पूर्ण अन्यथा
			offset = 0;

		fibh->sbh = fibh->ebh = udf_tपढ़ो(sb, block);
		अगर (!fibh->sbh) अणु
			fi = ERR_PTR(-EIO);
			जाओ out_err;
		पूर्ण
	पूर्ण

	fname = kदो_स्मृति(UDF_NAME_LEN, GFP_NOFS);
	अगर (!fname) अणु
		fi = ERR_PTR(-ENOMEM);
		जाओ out_err;
	पूर्ण

	जबतक (f_pos < size) अणु
		fi = udf_fileident_पढ़ो(dir, &f_pos, fibh, cfi, &epos, &eloc,
					&elen, &offset);
		अगर (!fi) अणु
			fi = ERR_PTR(-EIO);
			जाओ out_err;
		पूर्ण

		liu = le16_to_cpu(cfi->lengthOfImpUse);
		lfi = cfi->lengthFileIdent;

		अगर (fibh->sbh == fibh->ebh) अणु
			nameptr = fi->fileIdent + liu;
		पूर्ण अन्यथा अणु
			पूर्णांक poffset;	/* Unpaded ending offset */

			poffset = fibh->soffset + माप(काष्ठा fileIdentDesc) +
					liu + lfi;

			अगर (poffset >= lfi)
				nameptr = (uपूर्णांक8_t *)(fibh->ebh->b_data +
						      poffset - lfi);
			अन्यथा अणु
				अगर (!copy_name) अणु
					copy_name = kदो_स्मृति(UDF_NAME_LEN,
							    GFP_NOFS);
					अगर (!copy_name) अणु
						fi = ERR_PTR(-ENOMEM);
						जाओ out_err;
					पूर्ण
				पूर्ण
				nameptr = copy_name;
				स_नकल(nameptr, fi->fileIdent + liu,
					lfi - poffset);
				स_नकल(nameptr + lfi - poffset,
					fibh->ebh->b_data, poffset);
			पूर्ण
		पूर्ण

		अगर ((cfi->fileCharacteristics & FID_खाता_CHAR_DELETED) != 0) अणु
			अगर (!UDF_QUERY_FLAG(sb, UDF_FLAG_UNDELETE))
				जारी;
		पूर्ण

		अगर ((cfi->fileCharacteristics & FID_खाता_CHAR_HIDDEN) != 0) अणु
			अगर (!UDF_QUERY_FLAG(sb, UDF_FLAG_UNHIDE))
				जारी;
		पूर्ण

		अगर ((cfi->fileCharacteristics & FID_खाता_CHAR_PARENT) &&
		    isकरोtकरोt)
			जाओ out_ok;

		अगर (!lfi)
			जारी;

		flen = udf_get_filename(sb, nameptr, lfi, fname, UDF_NAME_LEN);
		अगर (flen < 0) अणु
			fi = ERR_PTR(flen);
			जाओ out_err;
		पूर्ण

		अगर (udf_match(flen, fname, child->len, child->name))
			जाओ out_ok;
	पूर्ण

	fi = शून्य;
out_err:
	अगर (fibh->sbh != fibh->ebh)
		brअन्यथा(fibh->ebh);
	brअन्यथा(fibh->sbh);
out_ok:
	brअन्यथा(epos.bh);
	kमुक्त(fname);
	kमुक्त(copy_name);

	वापस fi;
पूर्ण

अटल काष्ठा dentry *udf_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				 अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode = शून्य;
	काष्ठा fileIdentDesc cfi;
	काष्ठा udf_fileident_bh fibh;
	काष्ठा fileIdentDesc *fi;

	अगर (dentry->d_name.len > UDF_NAME_LEN)
		वापस ERR_PTR(-ENAMETOOLONG);

	fi = udf_find_entry(dir, &dentry->d_name, &fibh, &cfi);
	अगर (IS_ERR(fi))
		वापस ERR_CAST(fi);

	अगर (fi) अणु
		काष्ठा kernel_lb_addr loc;

		अगर (fibh.sbh != fibh.ebh)
			brअन्यथा(fibh.ebh);
		brअन्यथा(fibh.sbh);

		loc = lelb_to_cpu(cfi.icb.extLocation);
		inode = udf_iget(dir->i_sb, &loc);
		अगर (IS_ERR(inode))
			वापस ERR_CAST(inode);
	पूर्ण

	वापस d_splice_alias(inode, dentry);
पूर्ण

अटल काष्ठा fileIdentDesc *udf_add_entry(काष्ठा inode *dir,
					   काष्ठा dentry *dentry,
					   काष्ठा udf_fileident_bh *fibh,
					   काष्ठा fileIdentDesc *cfi, पूर्णांक *err)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा fileIdentDesc *fi = शून्य;
	अचिन्हित अक्षर *name = शून्य;
	पूर्णांक namelen;
	loff_t f_pos;
	loff_t size = udf_ext0_offset(dir) + dir->i_size;
	पूर्णांक nfidlen;
	udf_pblk_t block;
	काष्ठा kernel_lb_addr eloc;
	uपूर्णांक32_t elen = 0;
	sector_t offset;
	काष्ठा extent_position epos = अणुपूर्ण;
	काष्ठा udf_inode_info *dinfo;

	fibh->sbh = fibh->ebh = शून्य;
	name = kदो_स्मृति(UDF_NAME_LEN_CS0, GFP_NOFS);
	अगर (!name) अणु
		*err = -ENOMEM;
		जाओ out_err;
	पूर्ण

	अगर (dentry) अणु
		अगर (!dentry->d_name.len) अणु
			*err = -EINVAL;
			जाओ out_err;
		पूर्ण
		namelen = udf_put_filename(sb, dentry->d_name.name,
					   dentry->d_name.len,
					   name, UDF_NAME_LEN_CS0);
		अगर (!namelen) अणु
			*err = -ENAMETOOLONG;
			जाओ out_err;
		पूर्ण
	पूर्ण अन्यथा अणु
		namelen = 0;
	पूर्ण

	nfidlen = ALIGN(माप(काष्ठा fileIdentDesc) + namelen, UDF_NAME_PAD);

	f_pos = udf_ext0_offset(dir);

	fibh->soffset = fibh->eoffset = f_pos & (dir->i_sb->s_blocksize - 1);
	dinfo = UDF_I(dir);
	अगर (dinfo->i_alloc_type != ICBTAG_FLAG_AD_IN_ICB) अणु
		अगर (inode_bmap(dir, f_pos >> dir->i_sb->s_blocksize_bits, &epos,
		    &eloc, &elen, &offset) != (EXT_RECORDED_ALLOCATED >> 30)) अणु
			block = udf_get_lb_pblock(dir->i_sb,
					&dinfo->i_location, 0);
			fibh->soffset = fibh->eoffset = sb->s_blocksize;
			जाओ add;
		पूर्ण
		block = udf_get_lb_pblock(dir->i_sb, &eloc, offset);
		अगर ((++offset << dir->i_sb->s_blocksize_bits) < elen) अणु
			अगर (dinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
				epos.offset -= माप(काष्ठा लघु_ad);
			अन्यथा अगर (dinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
				epos.offset -= माप(काष्ठा दीर्घ_ad);
		पूर्ण अन्यथा
			offset = 0;

		fibh->sbh = fibh->ebh = udf_tपढ़ो(dir->i_sb, block);
		अगर (!fibh->sbh) अणु
			*err = -EIO;
			जाओ out_err;
		पूर्ण

		block = dinfo->i_location.logicalBlockNum;
	पूर्ण

	जबतक (f_pos < size) अणु
		fi = udf_fileident_पढ़ो(dir, &f_pos, fibh, cfi, &epos, &eloc,
					&elen, &offset);

		अगर (!fi) अणु
			*err = -EIO;
			जाओ out_err;
		पूर्ण

		अगर ((cfi->fileCharacteristics & FID_खाता_CHAR_DELETED) != 0) अणु
			अगर (udf_dir_entry_len(cfi) == nfidlen) अणु
				cfi->descTag.tagSerialNum = cpu_to_le16(1);
				cfi->fileVersionNum = cpu_to_le16(1);
				cfi->fileCharacteristics = 0;
				cfi->lengthFileIdent = namelen;
				cfi->lengthOfImpUse = cpu_to_le16(0);
				अगर (!udf_ग_लिखो_fi(dir, cfi, fi, fibh, शून्य,
						  name))
					जाओ out_ok;
				अन्यथा अणु
					*err = -EIO;
					जाओ out_err;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

add:
	f_pos += nfidlen;

	अगर (dinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB &&
	    sb->s_blocksize - fibh->eoffset < nfidlen) अणु
		brअन्यथा(epos.bh);
		epos.bh = शून्य;
		fibh->soffset -= udf_ext0_offset(dir);
		fibh->eoffset -= udf_ext0_offset(dir);
		f_pos -= udf_ext0_offset(dir);
		अगर (fibh->sbh != fibh->ebh)
			brअन्यथा(fibh->ebh);
		brअन्यथा(fibh->sbh);
		fibh->sbh = fibh->ebh =
				udf_expand_dir_adinicb(dir, &block, err);
		अगर (!fibh->sbh)
			जाओ out_err;
		epos.block = dinfo->i_location;
		epos.offset = udf_file_entry_alloc_offset(dir);
		/* Load extent udf_expand_dir_adinicb() has created */
		udf_current_aext(dir, &epos, &eloc, &elen, 1);
	पूर्ण

	/* Entry fits पूर्णांकo current block? */
	अगर (sb->s_blocksize - fibh->eoffset >= nfidlen) अणु
		fibh->soffset = fibh->eoffset;
		fibh->eoffset += nfidlen;
		अगर (fibh->sbh != fibh->ebh) अणु
			brअन्यथा(fibh->sbh);
			fibh->sbh = fibh->ebh;
		पूर्ण

		अगर (dinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) अणु
			block = dinfo->i_location.logicalBlockNum;
			fi = (काष्ठा fileIdentDesc *)
					(dinfo->i_data + fibh->soffset -
					 udf_ext0_offset(dir) +
					 dinfo->i_lenEAttr);
		पूर्ण अन्यथा अणु
			block = eloc.logicalBlockNum +
					((elen - 1) >>
						dir->i_sb->s_blocksize_bits);
			fi = (काष्ठा fileIdentDesc *)
				(fibh->sbh->b_data + fibh->soffset);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Round up last extent in the file */
		elen = (elen + sb->s_blocksize - 1) & ~(sb->s_blocksize - 1);
		अगर (dinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
			epos.offset -= माप(काष्ठा लघु_ad);
		अन्यथा अगर (dinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
			epos.offset -= माप(काष्ठा दीर्घ_ad);
		udf_ग_लिखो_aext(dir, &epos, &eloc, elen, 1);
		dinfo->i_lenExtents = (dinfo->i_lenExtents + sb->s_blocksize
					- 1) & ~(sb->s_blocksize - 1);

		fibh->soffset = fibh->eoffset - sb->s_blocksize;
		fibh->eoffset += nfidlen - sb->s_blocksize;
		अगर (fibh->sbh != fibh->ebh) अणु
			brअन्यथा(fibh->sbh);
			fibh->sbh = fibh->ebh;
		पूर्ण

		block = eloc.logicalBlockNum + ((elen - 1) >>
						dir->i_sb->s_blocksize_bits);
		fibh->ebh = udf_bपढ़ो(dir,
				f_pos >> dir->i_sb->s_blocksize_bits, 1, err);
		अगर (!fibh->ebh)
			जाओ out_err;
		/* Extents could have been merged, invalidate our position */
		brअन्यथा(epos.bh);
		epos.bh = शून्य;
		epos.block = dinfo->i_location;
		epos.offset = udf_file_entry_alloc_offset(dir);

		अगर (!fibh->soffset) अणु
			/* Find the freshly allocated block */
			जबतक (udf_next_aext(dir, &epos, &eloc, &elen, 1) ==
				(EXT_RECORDED_ALLOCATED >> 30))
				;
			block = eloc.logicalBlockNum + ((elen - 1) >>
					dir->i_sb->s_blocksize_bits);
			brअन्यथा(fibh->sbh);
			fibh->sbh = fibh->ebh;
			fi = (काष्ठा fileIdentDesc *)(fibh->sbh->b_data);
		पूर्ण अन्यथा अणु
			fi = (काष्ठा fileIdentDesc *)
				(fibh->sbh->b_data + sb->s_blocksize +
					fibh->soffset);
		पूर्ण
	पूर्ण

	स_रखो(cfi, 0, माप(काष्ठा fileIdentDesc));
	अगर (UDF_SB(sb)->s_udfrev >= 0x0200)
		udf_new_tag((अक्षर *)cfi, TAG_IDENT_FID, 3, 1, block,
			    माप(काष्ठा tag));
	अन्यथा
		udf_new_tag((अक्षर *)cfi, TAG_IDENT_FID, 2, 1, block,
			    माप(काष्ठा tag));
	cfi->fileVersionNum = cpu_to_le16(1);
	cfi->lengthFileIdent = namelen;
	cfi->lengthOfImpUse = cpu_to_le16(0);
	अगर (!udf_ग_लिखो_fi(dir, cfi, fi, fibh, शून्य, name)) अणु
		dir->i_size += nfidlen;
		अगर (dinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
			dinfo->i_lenAlloc += nfidlen;
		अन्यथा अणु
			/* Find the last extent and truncate it to proper size */
			जबतक (udf_next_aext(dir, &epos, &eloc, &elen, 1) ==
				(EXT_RECORDED_ALLOCATED >> 30))
				;
			elen -= dinfo->i_lenExtents - dir->i_size;
			अगर (dinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
				epos.offset -= माप(काष्ठा लघु_ad);
			अन्यथा अगर (dinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
				epos.offset -= माप(काष्ठा दीर्घ_ad);
			udf_ग_लिखो_aext(dir, &epos, &eloc, elen, 1);
			dinfo->i_lenExtents = dir->i_size;
		पूर्ण

		mark_inode_dirty(dir);
		जाओ out_ok;
	पूर्ण अन्यथा अणु
		*err = -EIO;
		जाओ out_err;
	पूर्ण

out_err:
	fi = शून्य;
	अगर (fibh->sbh != fibh->ebh)
		brअन्यथा(fibh->ebh);
	brअन्यथा(fibh->sbh);
out_ok:
	brअन्यथा(epos.bh);
	kमुक्त(name);
	वापस fi;
पूर्ण

अटल पूर्णांक udf_delete_entry(काष्ठा inode *inode, काष्ठा fileIdentDesc *fi,
			    काष्ठा udf_fileident_bh *fibh,
			    काष्ठा fileIdentDesc *cfi)
अणु
	cfi->fileCharacteristics |= FID_खाता_CHAR_DELETED;

	अगर (UDF_QUERY_FLAG(inode->i_sb, UDF_FLAG_STRICT))
		स_रखो(&(cfi->icb), 0x00, माप(काष्ठा दीर्घ_ad));

	वापस udf_ग_लिखो_fi(inode, cfi, fi, fibh, शून्य, शून्य);
पूर्ण

अटल पूर्णांक udf_add_nondir(काष्ठा dentry *dentry, काष्ठा inode *inode)
अणु
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);
	काष्ठा inode *dir = d_inode(dentry->d_parent);
	काष्ठा udf_fileident_bh fibh;
	काष्ठा fileIdentDesc cfi, *fi;
	पूर्णांक err;

	fi = udf_add_entry(dir, dentry, &fibh, &cfi, &err);
	अगर (unlikely(!fi)) अणु
		inode_dec_link_count(inode);
		discard_new_inode(inode);
		वापस err;
	पूर्ण
	cfi.icb.extLength = cpu_to_le32(inode->i_sb->s_blocksize);
	cfi.icb.extLocation = cpu_to_lelb(iinfo->i_location);
	*(__le32 *)((काष्ठा allocDescImpUse *)cfi.icb.impUse)->impUse =
		cpu_to_le32(iinfo->i_unique & 0x00000000FFFFFFFFUL);
	udf_ग_लिखो_fi(dir, &cfi, fi, &fibh, शून्य, शून्य);
	dir->i_स_समय = dir->i_mसमय = current_समय(dir);
	mark_inode_dirty(dir);
	अगर (fibh.sbh != fibh.ebh)
		brअन्यथा(fibh.ebh);
	brअन्यथा(fibh.sbh);
	d_instantiate_new(dentry, inode);

	वापस 0;
पूर्ण

अटल पूर्णांक udf_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		      काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	काष्ठा inode *inode = udf_new_inode(dir, mode);

	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	अगर (UDF_I(inode)->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		inode->i_data.a_ops = &udf_adinicb_aops;
	अन्यथा
		inode->i_data.a_ops = &udf_aops;
	inode->i_op = &udf_file_inode_operations;
	inode->i_fop = &udf_file_operations;
	mark_inode_dirty(inode);

	वापस udf_add_nondir(dentry, inode);
पूर्ण

अटल पूर्णांक udf_क्षणिक_ख(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा inode *inode = udf_new_inode(dir, mode);

	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	अगर (UDF_I(inode)->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		inode->i_data.a_ops = &udf_adinicb_aops;
	अन्यथा
		inode->i_data.a_ops = &udf_aops;
	inode->i_op = &udf_file_inode_operations;
	inode->i_fop = &udf_file_operations;
	mark_inode_dirty(inode);
	d_क्षणिक_ख(dentry, inode);
	unlock_new_inode(inode);
	वापस 0;
पूर्ण

अटल पूर्णांक udf_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		     काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	काष्ठा inode *inode;

	अगर (!old_valid_dev(rdev))
		वापस -EINVAL;

	inode = udf_new_inode(dir, mode);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	init_special_inode(inode, mode, rdev);
	वापस udf_add_nondir(dentry, inode);
पूर्ण

अटल पूर्णांक udf_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		     काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा inode *inode;
	काष्ठा udf_fileident_bh fibh;
	काष्ठा fileIdentDesc cfi, *fi;
	पूर्णांक err;
	काष्ठा udf_inode_info *dinfo = UDF_I(dir);
	काष्ठा udf_inode_info *iinfo;

	inode = udf_new_inode(dir, S_IFसूची | mode);
	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	iinfo = UDF_I(inode);
	inode->i_op = &udf_dir_inode_operations;
	inode->i_fop = &udf_dir_operations;
	fi = udf_add_entry(inode, शून्य, &fibh, &cfi, &err);
	अगर (!fi) अणु
		inode_dec_link_count(inode);
		discard_new_inode(inode);
		जाओ out;
	पूर्ण
	set_nlink(inode, 2);
	cfi.icb.extLength = cpu_to_le32(inode->i_sb->s_blocksize);
	cfi.icb.extLocation = cpu_to_lelb(dinfo->i_location);
	*(__le32 *)((काष्ठा allocDescImpUse *)cfi.icb.impUse)->impUse =
		cpu_to_le32(dinfo->i_unique & 0x00000000FFFFFFFFUL);
	cfi.fileCharacteristics =
			FID_खाता_CHAR_सूचीECTORY | FID_खाता_CHAR_PARENT;
	udf_ग_लिखो_fi(inode, &cfi, fi, &fibh, शून्य, शून्य);
	brअन्यथा(fibh.sbh);
	mark_inode_dirty(inode);

	fi = udf_add_entry(dir, dentry, &fibh, &cfi, &err);
	अगर (!fi) अणु
		clear_nlink(inode);
		mark_inode_dirty(inode);
		discard_new_inode(inode);
		जाओ out;
	पूर्ण
	cfi.icb.extLength = cpu_to_le32(inode->i_sb->s_blocksize);
	cfi.icb.extLocation = cpu_to_lelb(iinfo->i_location);
	*(__le32 *)((काष्ठा allocDescImpUse *)cfi.icb.impUse)->impUse =
		cpu_to_le32(iinfo->i_unique & 0x00000000FFFFFFFFUL);
	cfi.fileCharacteristics |= FID_खाता_CHAR_सूचीECTORY;
	udf_ग_लिखो_fi(dir, &cfi, fi, &fibh, शून्य, शून्य);
	inc_nlink(dir);
	dir->i_स_समय = dir->i_mसमय = current_समय(dir);
	mark_inode_dirty(dir);
	d_instantiate_new(dentry, inode);
	अगर (fibh.sbh != fibh.ebh)
		brअन्यथा(fibh.ebh);
	brअन्यथा(fibh.sbh);
	err = 0;

out:
	वापस err;
पूर्ण

अटल पूर्णांक empty_dir(काष्ठा inode *dir)
अणु
	काष्ठा fileIdentDesc *fi, cfi;
	काष्ठा udf_fileident_bh fibh;
	loff_t f_pos;
	loff_t size = udf_ext0_offset(dir) + dir->i_size;
	udf_pblk_t block;
	काष्ठा kernel_lb_addr eloc;
	uपूर्णांक32_t elen;
	sector_t offset;
	काष्ठा extent_position epos = अणुपूर्ण;
	काष्ठा udf_inode_info *dinfo = UDF_I(dir);

	f_pos = udf_ext0_offset(dir);
	fibh.soffset = fibh.eoffset = f_pos & (dir->i_sb->s_blocksize - 1);

	अगर (dinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		fibh.sbh = fibh.ebh = शून्य;
	अन्यथा अगर (inode_bmap(dir, f_pos >> dir->i_sb->s_blocksize_bits,
			      &epos, &eloc, &elen, &offset) ==
					(EXT_RECORDED_ALLOCATED >> 30)) अणु
		block = udf_get_lb_pblock(dir->i_sb, &eloc, offset);
		अगर ((++offset << dir->i_sb->s_blocksize_bits) < elen) अणु
			अगर (dinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
				epos.offset -= माप(काष्ठा लघु_ad);
			अन्यथा अगर (dinfo->i_alloc_type == ICBTAG_FLAG_AD_LONG)
				epos.offset -= माप(काष्ठा दीर्घ_ad);
		पूर्ण अन्यथा
			offset = 0;

		fibh.sbh = fibh.ebh = udf_tपढ़ो(dir->i_sb, block);
		अगर (!fibh.sbh) अणु
			brअन्यथा(epos.bh);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		brअन्यथा(epos.bh);
		वापस 0;
	पूर्ण

	जबतक (f_pos < size) अणु
		fi = udf_fileident_पढ़ो(dir, &f_pos, &fibh, &cfi, &epos, &eloc,
					&elen, &offset);
		अगर (!fi) अणु
			अगर (fibh.sbh != fibh.ebh)
				brअन्यथा(fibh.ebh);
			brअन्यथा(fibh.sbh);
			brअन्यथा(epos.bh);
			वापस 0;
		पूर्ण

		अगर (cfi.lengthFileIdent &&
		    (cfi.fileCharacteristics & FID_खाता_CHAR_DELETED) == 0) अणु
			अगर (fibh.sbh != fibh.ebh)
				brअन्यथा(fibh.ebh);
			brअन्यथा(fibh.sbh);
			brअन्यथा(epos.bh);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (fibh.sbh != fibh.ebh)
		brअन्यथा(fibh.ebh);
	brअन्यथा(fibh.sbh);
	brअन्यथा(epos.bh);

	वापस 1;
पूर्ण

अटल पूर्णांक udf_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक retval;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा udf_fileident_bh fibh;
	काष्ठा fileIdentDesc *fi, cfi;
	काष्ठा kernel_lb_addr tloc;

	retval = -ENOENT;
	fi = udf_find_entry(dir, &dentry->d_name, &fibh, &cfi);
	अगर (IS_ERR_OR_शून्य(fi)) अणु
		अगर (fi)
			retval = PTR_ERR(fi);
		जाओ out;
	पूर्ण

	retval = -EIO;
	tloc = lelb_to_cpu(cfi.icb.extLocation);
	अगर (udf_get_lb_pblock(dir->i_sb, &tloc, 0) != inode->i_ino)
		जाओ end_सूची_हटाओ;
	retval = -ENOTEMPTY;
	अगर (!empty_dir(inode))
		जाओ end_सूची_हटाओ;
	retval = udf_delete_entry(dir, fi, &fibh, &cfi);
	अगर (retval)
		जाओ end_सूची_हटाओ;
	अगर (inode->i_nlink != 2)
		udf_warn(inode->i_sb, "empty directory has nlink != 2 (%u)\n",
			 inode->i_nlink);
	clear_nlink(inode);
	inode->i_size = 0;
	inode_dec_link_count(dir);
	inode->i_स_समय = dir->i_स_समय = dir->i_mसमय =
						current_समय(inode);
	mark_inode_dirty(dir);

end_सूची_हटाओ:
	अगर (fibh.sbh != fibh.ebh)
		brअन्यथा(fibh.ebh);
	brअन्यथा(fibh.sbh);

out:
	वापस retval;
पूर्ण

अटल पूर्णांक udf_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक retval;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा udf_fileident_bh fibh;
	काष्ठा fileIdentDesc *fi;
	काष्ठा fileIdentDesc cfi;
	काष्ठा kernel_lb_addr tloc;

	retval = -ENOENT;
	fi = udf_find_entry(dir, &dentry->d_name, &fibh, &cfi);

	अगर (IS_ERR_OR_शून्य(fi)) अणु
		अगर (fi)
			retval = PTR_ERR(fi);
		जाओ out;
	पूर्ण

	retval = -EIO;
	tloc = lelb_to_cpu(cfi.icb.extLocation);
	अगर (udf_get_lb_pblock(dir->i_sb, &tloc, 0) != inode->i_ino)
		जाओ end_unlink;

	अगर (!inode->i_nlink) अणु
		udf_debug("Deleting nonexistent file (%lu), %u\n",
			  inode->i_ino, inode->i_nlink);
		set_nlink(inode, 1);
	पूर्ण
	retval = udf_delete_entry(dir, fi, &fibh, &cfi);
	अगर (retval)
		जाओ end_unlink;
	dir->i_स_समय = dir->i_mसमय = current_समय(dir);
	mark_inode_dirty(dir);
	inode_dec_link_count(inode);
	inode->i_स_समय = dir->i_स_समय;
	retval = 0;

end_unlink:
	अगर (fibh.sbh != fibh.ebh)
		brअन्यथा(fibh.ebh);
	brअन्यथा(fibh.sbh);

out:
	वापस retval;
पूर्ण

अटल पूर्णांक udf_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	काष्ठा inode *inode = udf_new_inode(dir, S_IFLNK | 0777);
	काष्ठा pathComponent *pc;
	स्थिर अक्षर *compstart;
	काष्ठा extent_position epos = अणुपूर्ण;
	पूर्णांक eoffset, elen = 0;
	uपूर्णांक8_t *ea;
	पूर्णांक err;
	udf_pblk_t block;
	अचिन्हित अक्षर *name = शून्य;
	पूर्णांक namelen;
	काष्ठा udf_inode_info *iinfo;
	काष्ठा super_block *sb = dir->i_sb;

	अगर (IS_ERR(inode))
		वापस PTR_ERR(inode);

	iinfo = UDF_I(inode);
	करोwn_ग_लिखो(&iinfo->i_data_sem);
	name = kदो_स्मृति(UDF_NAME_LEN_CS0, GFP_NOFS);
	अगर (!name) अणु
		err = -ENOMEM;
		जाओ out_no_entry;
	पूर्ण

	inode->i_data.a_ops = &udf_symlink_aops;
	inode->i_op = &udf_symlink_inode_operations;
	inode_nohighmem(inode);

	अगर (iinfo->i_alloc_type != ICBTAG_FLAG_AD_IN_ICB) अणु
		काष्ठा kernel_lb_addr eloc;
		uपूर्णांक32_t bsize;

		block = udf_new_block(sb, inode,
				iinfo->i_location.partitionReferenceNum,
				iinfo->i_location.logicalBlockNum, &err);
		अगर (!block)
			जाओ out_no_entry;
		epos.block = iinfo->i_location;
		epos.offset = udf_file_entry_alloc_offset(inode);
		epos.bh = शून्य;
		eloc.logicalBlockNum = block;
		eloc.partitionReferenceNum =
				iinfo->i_location.partitionReferenceNum;
		bsize = sb->s_blocksize;
		iinfo->i_lenExtents = bsize;
		udf_add_aext(inode, &epos, &eloc, bsize, 0);
		brअन्यथा(epos.bh);

		block = udf_get_pblock(sb, block,
				iinfo->i_location.partitionReferenceNum,
				0);
		epos.bh = udf_tgetblk(sb, block);
		lock_buffer(epos.bh);
		स_रखो(epos.bh->b_data, 0x00, bsize);
		set_buffer_uptodate(epos.bh);
		unlock_buffer(epos.bh);
		mark_buffer_dirty_inode(epos.bh, inode);
		ea = epos.bh->b_data + udf_ext0_offset(inode);
	पूर्ण अन्यथा
		ea = iinfo->i_data + iinfo->i_lenEAttr;

	eoffset = sb->s_blocksize - udf_ext0_offset(inode);
	pc = (काष्ठा pathComponent *)ea;

	अगर (*symname == '/') अणु
		करो अणु
			symname++;
		पूर्ण जबतक (*symname == '/');

		pc->componentType = 1;
		pc->lengthComponentIdent = 0;
		pc->componentFileVersionNum = 0;
		elen += माप(काष्ठा pathComponent);
	पूर्ण

	err = -ENAMETOOLONG;

	जबतक (*symname) अणु
		अगर (elen + माप(काष्ठा pathComponent) > eoffset)
			जाओ out_no_entry;

		pc = (काष्ठा pathComponent *)(ea + elen);

		compstart = symname;

		करो अणु
			symname++;
		पूर्ण जबतक (*symname && *symname != '/');

		pc->componentType = 5;
		pc->lengthComponentIdent = 0;
		pc->componentFileVersionNum = 0;
		अगर (compstart[0] == '.') अणु
			अगर ((symname - compstart) == 1)
				pc->componentType = 4;
			अन्यथा अगर ((symname - compstart) == 2 &&
					compstart[1] == '.')
				pc->componentType = 3;
		पूर्ण

		अगर (pc->componentType == 5) अणु
			namelen = udf_put_filename(sb, compstart,
						   symname - compstart,
						   name, UDF_NAME_LEN_CS0);
			अगर (!namelen)
				जाओ out_no_entry;

			अगर (elen + माप(काष्ठा pathComponent) + namelen >
					eoffset)
				जाओ out_no_entry;
			अन्यथा
				pc->lengthComponentIdent = namelen;

			स_नकल(pc->componentIdent, name, namelen);
		पूर्ण

		elen += माप(काष्ठा pathComponent) + pc->lengthComponentIdent;

		अगर (*symname) अणु
			करो अणु
				symname++;
			पूर्ण जबतक (*symname == '/');
		पूर्ण
	पूर्ण

	brअन्यथा(epos.bh);
	inode->i_size = elen;
	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		iinfo->i_lenAlloc = inode->i_size;
	अन्यथा
		udf_truncate_tail_extent(inode);
	mark_inode_dirty(inode);
	up_ग_लिखो(&iinfo->i_data_sem);

	err = udf_add_nondir(dentry, inode);
out:
	kमुक्त(name);
	वापस err;

out_no_entry:
	up_ग_लिखो(&iinfo->i_data_sem);
	inode_dec_link_count(inode);
	discard_new_inode(inode);
	जाओ out;
पूर्ण

अटल पूर्णांक udf_link(काष्ठा dentry *old_dentry, काष्ठा inode *dir,
		    काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(old_dentry);
	काष्ठा udf_fileident_bh fibh;
	काष्ठा fileIdentDesc cfi, *fi;
	पूर्णांक err;

	fi = udf_add_entry(dir, dentry, &fibh, &cfi, &err);
	अगर (!fi) अणु
		वापस err;
	पूर्ण
	cfi.icb.extLength = cpu_to_le32(inode->i_sb->s_blocksize);
	cfi.icb.extLocation = cpu_to_lelb(UDF_I(inode)->i_location);
	अगर (UDF_SB(inode->i_sb)->s_lvid_bh) अणु
		*(__le32 *)((काष्ठा allocDescImpUse *)cfi.icb.impUse)->impUse =
			cpu_to_le32(lvid_get_unique_id(inode->i_sb));
	पूर्ण
	udf_ग_लिखो_fi(dir, &cfi, fi, &fibh, शून्य, शून्य);
	अगर (UDF_I(dir)->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
		mark_inode_dirty(dir);

	अगर (fibh.sbh != fibh.ebh)
		brअन्यथा(fibh.ebh);
	brअन्यथा(fibh.sbh);
	inc_nlink(inode);
	inode->i_स_समय = current_समय(inode);
	mark_inode_dirty(inode);
	dir->i_स_समय = dir->i_mसमय = current_समय(dir);
	mark_inode_dirty(dir);
	ihold(inode);
	d_instantiate(dentry, inode);

	वापस 0;
पूर्ण

/* Anybody can नाम anything with this: the permission checks are left to the
 * higher-level routines.
 */
अटल पूर्णांक udf_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		      काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		      काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *old_inode = d_inode(old_dentry);
	काष्ठा inode *new_inode = d_inode(new_dentry);
	काष्ठा udf_fileident_bh ofibh, nfibh;
	काष्ठा fileIdentDesc *ofi = शून्य, *nfi = शून्य, *dir_fi = शून्य;
	काष्ठा fileIdentDesc ocfi, ncfi;
	काष्ठा buffer_head *dir_bh = शून्य;
	पूर्णांक retval = -ENOENT;
	काष्ठा kernel_lb_addr tloc;
	काष्ठा udf_inode_info *old_iinfo = UDF_I(old_inode);

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	ofi = udf_find_entry(old_dir, &old_dentry->d_name, &ofibh, &ocfi);
	अगर (IS_ERR(ofi)) अणु
		retval = PTR_ERR(ofi);
		जाओ end_नाम;
	पूर्ण

	अगर (ofibh.sbh != ofibh.ebh)
		brअन्यथा(ofibh.ebh);

	brअन्यथा(ofibh.sbh);
	tloc = lelb_to_cpu(ocfi.icb.extLocation);
	अगर (!ofi || udf_get_lb_pblock(old_dir->i_sb, &tloc, 0)
	    != old_inode->i_ino)
		जाओ end_नाम;

	nfi = udf_find_entry(new_dir, &new_dentry->d_name, &nfibh, &ncfi);
	अगर (IS_ERR(nfi)) अणु
		retval = PTR_ERR(nfi);
		जाओ end_नाम;
	पूर्ण
	अगर (nfi && !new_inode) अणु
		अगर (nfibh.sbh != nfibh.ebh)
			brअन्यथा(nfibh.ebh);
		brअन्यथा(nfibh.sbh);
		nfi = शून्य;
	पूर्ण
	अगर (S_ISसूची(old_inode->i_mode)) अणु
		पूर्णांक offset = udf_ext0_offset(old_inode);

		अगर (new_inode) अणु
			retval = -ENOTEMPTY;
			अगर (!empty_dir(new_inode))
				जाओ end_नाम;
		पूर्ण
		retval = -EIO;
		अगर (old_iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) अणु
			dir_fi = udf_get_fileident(
					old_iinfo->i_data -
					  (old_iinfo->i_efe ?
					   माप(काष्ठा extendedFileEntry) :
					   माप(काष्ठा fileEntry)),
					old_inode->i_sb->s_blocksize, &offset);
		पूर्ण अन्यथा अणु
			dir_bh = udf_bपढ़ो(old_inode, 0, 0, &retval);
			अगर (!dir_bh)
				जाओ end_नाम;
			dir_fi = udf_get_fileident(dir_bh->b_data,
					old_inode->i_sb->s_blocksize, &offset);
		पूर्ण
		अगर (!dir_fi)
			जाओ end_नाम;
		tloc = lelb_to_cpu(dir_fi->icb.extLocation);
		अगर (udf_get_lb_pblock(old_inode->i_sb, &tloc, 0) !=
				old_dir->i_ino)
			जाओ end_नाम;
	पूर्ण
	अगर (!nfi) अणु
		nfi = udf_add_entry(new_dir, new_dentry, &nfibh, &ncfi,
				    &retval);
		अगर (!nfi)
			जाओ end_नाम;
	पूर्ण

	/*
	 * Like most other Unix प्रणालीs, set the स_समय क्रम inodes on a
	 * नाम.
	 */
	old_inode->i_स_समय = current_समय(old_inode);
	mark_inode_dirty(old_inode);

	/*
	 * ok, that's it
	 */
	ncfi.fileVersionNum = ocfi.fileVersionNum;
	ncfi.fileCharacteristics = ocfi.fileCharacteristics;
	स_नकल(&(ncfi.icb), &(ocfi.icb), माप(ocfi.icb));
	udf_ग_लिखो_fi(new_dir, &ncfi, nfi, &nfibh, शून्य, शून्य);

	/* The old fid may have moved - find it again */
	ofi = udf_find_entry(old_dir, &old_dentry->d_name, &ofibh, &ocfi);
	udf_delete_entry(old_dir, ofi, &ofibh, &ocfi);

	अगर (new_inode) अणु
		new_inode->i_स_समय = current_समय(new_inode);
		inode_dec_link_count(new_inode);
	पूर्ण
	old_dir->i_स_समय = old_dir->i_mसमय = current_समय(old_dir);
	new_dir->i_स_समय = new_dir->i_mसमय = current_समय(new_dir);
	mark_inode_dirty(old_dir);
	mark_inode_dirty(new_dir);

	अगर (dir_fi) अणु
		dir_fi->icb.extLocation = cpu_to_lelb(UDF_I(new_dir)->i_location);
		udf_update_tag((अक्षर *)dir_fi, udf_dir_entry_len(dir_fi));
		अगर (old_iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB)
			mark_inode_dirty(old_inode);
		अन्यथा
			mark_buffer_dirty_inode(dir_bh, old_inode);

		inode_dec_link_count(old_dir);
		अगर (new_inode)
			inode_dec_link_count(new_inode);
		अन्यथा अणु
			inc_nlink(new_dir);
			mark_inode_dirty(new_dir);
		पूर्ण
	पूर्ण

	अगर (ofi) अणु
		अगर (ofibh.sbh != ofibh.ebh)
			brअन्यथा(ofibh.ebh);
		brअन्यथा(ofibh.sbh);
	पूर्ण

	retval = 0;

end_नाम:
	brअन्यथा(dir_bh);
	अगर (nfi) अणु
		अगर (nfibh.sbh != nfibh.ebh)
			brअन्यथा(nfibh.ebh);
		brअन्यथा(nfibh.sbh);
	पूर्ण

	वापस retval;
पूर्ण

अटल काष्ठा dentry *udf_get_parent(काष्ठा dentry *child)
अणु
	काष्ठा kernel_lb_addr tloc;
	काष्ठा inode *inode = शून्य;
	काष्ठा fileIdentDesc cfi;
	काष्ठा udf_fileident_bh fibh;

	अगर (!udf_find_entry(d_inode(child), &करोtकरोt_name, &fibh, &cfi))
		वापस ERR_PTR(-EACCES);

	अगर (fibh.sbh != fibh.ebh)
		brअन्यथा(fibh.ebh);
	brअन्यथा(fibh.sbh);

	tloc = lelb_to_cpu(cfi.icb.extLocation);
	inode = udf_iget(child->d_sb, &tloc);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);

	वापस d_obtain_alias(inode);
पूर्ण


अटल काष्ठा dentry *udf_nfs_get_inode(काष्ठा super_block *sb, u32 block,
					u16 partref, __u32 generation)
अणु
	काष्ठा inode *inode;
	काष्ठा kernel_lb_addr loc;

	अगर (block == 0)
		वापस ERR_PTR(-ESTALE);

	loc.logicalBlockNum = block;
	loc.partitionReferenceNum = partref;
	inode = udf_iget(sb, &loc);

	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);

	अगर (generation && inode->i_generation != generation) अणु
		iput(inode);
		वापस ERR_PTR(-ESTALE);
	पूर्ण
	वापस d_obtain_alias(inode);
पूर्ण

अटल काष्ठा dentry *udf_fh_to_dentry(काष्ठा super_block *sb,
				       काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	अगर (fh_len < 3 ||
	    (fh_type != खाताID_UDF_WITH_PARENT &&
	     fh_type != खाताID_UDF_WITHOUT_PARENT))
		वापस शून्य;

	वापस udf_nfs_get_inode(sb, fid->udf.block, fid->udf.partref,
			fid->udf.generation);
पूर्ण

अटल काष्ठा dentry *udf_fh_to_parent(काष्ठा super_block *sb,
				       काष्ठा fid *fid, पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	अगर (fh_len < 5 || fh_type != खाताID_UDF_WITH_PARENT)
		वापस शून्य;

	वापस udf_nfs_get_inode(sb, fid->udf.parent_block,
				 fid->udf.parent_partref,
				 fid->udf.parent_generation);
पूर्ण
अटल पूर्णांक udf_encode_fh(काष्ठा inode *inode, __u32 *fh, पूर्णांक *lenp,
			 काष्ठा inode *parent)
अणु
	पूर्णांक len = *lenp;
	काष्ठा kernel_lb_addr location = UDF_I(inode)->i_location;
	काष्ठा fid *fid = (काष्ठा fid *)fh;
	पूर्णांक type = खाताID_UDF_WITHOUT_PARENT;

	अगर (parent && (len < 5)) अणु
		*lenp = 5;
		वापस खाताID_INVALID;
	पूर्ण अन्यथा अगर (len < 3) अणु
		*lenp = 3;
		वापस खाताID_INVALID;
	पूर्ण

	*lenp = 3;
	fid->udf.block = location.logicalBlockNum;
	fid->udf.partref = location.partitionReferenceNum;
	fid->udf.parent_partref = 0;
	fid->udf.generation = inode->i_generation;

	अगर (parent) अणु
		location = UDF_I(parent)->i_location;
		fid->udf.parent_block = location.logicalBlockNum;
		fid->udf.parent_partref = location.partitionReferenceNum;
		fid->udf.parent_generation = inode->i_generation;
		*lenp = 5;
		type = खाताID_UDF_WITH_PARENT;
	पूर्ण

	वापस type;
पूर्ण

स्थिर काष्ठा export_operations udf_export_ops = अणु
	.encode_fh	= udf_encode_fh,
	.fh_to_dentry   = udf_fh_to_dentry,
	.fh_to_parent   = udf_fh_to_parent,
	.get_parent     = udf_get_parent,
पूर्ण;

स्थिर काष्ठा inode_operations udf_dir_inode_operations = अणु
	.lookup				= udf_lookup,
	.create				= udf_create,
	.link				= udf_link,
	.unlink				= udf_unlink,
	.symlink			= udf_symlink,
	.सूची_गढ़ो				= udf_सूची_गढ़ो,
	.सूची_हटाओ				= udf_सूची_हटाओ,
	.mknod				= udf_mknod,
	.नाम				= udf_नाम,
	.क्षणिक_ख			= udf_क्षणिक_ख,
पूर्ण;
