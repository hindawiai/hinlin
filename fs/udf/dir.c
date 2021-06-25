<शैली गुरु>
/*
 * dir.c
 *
 * PURPOSE
 *  Directory handling routines क्रम the OSTA-UDF(पंचांग) fileप्रणाली.
 *
 * COPYRIGHT
 *	This file is distributed under the terms of the GNU General Public
 *	License (GPL). Copies of the GPL can be obtained from:
 *		ftp://prep.ai.mit.edu/pub/gnu/GPL
 *	Each contributing author retains all rights to their own work.
 *
 *  (C) 1998-2004 Ben Fennema
 *
 * HISTORY
 *
 *  10/05/98 dgb  Split directory operations पूर्णांकo its own file
 *                Implemented directory पढ़ोs via करो_udf_सूची_पढ़ो
 *  10/06/98      Made directory operations work!
 *  11/17/98      Rewrote directory to support ICBTAG_FLAG_AD_LONG
 *  11/25/98 blf  Rewrote directory handling (सूची_पढ़ो+lookup) to support पढ़ोing
 *                across blocks.
 *  12/12/98      Split out the lookup code to namei.c. bulk of directory
 *                code now in directory.c:udf_fileident_पढ़ो.
 */

#समावेश "udfdecl.h"

#समावेश <linux/माला.स>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/bपन.स>

#समावेश "udf_i.h"
#समावेश "udf_sb.h"


अटल पूर्णांक udf_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *dir = file_inode(file);
	काष्ठा udf_inode_info *iinfo = UDF_I(dir);
	काष्ठा udf_fileident_bh fibh = अणु .sbh = शून्य, .ebh = शून्यपूर्ण;
	काष्ठा fileIdentDesc *fi = शून्य;
	काष्ठा fileIdentDesc cfi;
	udf_pblk_t block, iblock;
	loff_t nf_pos;
	पूर्णांक flen;
	अचिन्हित अक्षर *fname = शून्य, *copy_name = शून्य;
	अचिन्हित अक्षर *nameptr;
	uपूर्णांक16_t liu;
	uपूर्णांक8_t lfi;
	loff_t size = udf_ext0_offset(dir) + dir->i_size;
	काष्ठा buffer_head *पंचांगp, *bha[16];
	काष्ठा kernel_lb_addr eloc;
	uपूर्णांक32_t elen;
	sector_t offset;
	पूर्णांक i, num, ret = 0;
	काष्ठा extent_position epos = अणु शून्य, 0, अणु0, 0पूर्ण पूर्ण;
	काष्ठा super_block *sb = dir->i_sb;

	अगर (ctx->pos == 0) अणु
		अगर (!dir_emit_करोt(file, ctx))
			वापस 0;
		ctx->pos = 1;
	पूर्ण
	nf_pos = (ctx->pos - 1) << 2;
	अगर (nf_pos >= size)
		जाओ out;

	fname = kदो_स्मृति(UDF_NAME_LEN, GFP_NOFS);
	अगर (!fname) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	अगर (nf_pos == 0)
		nf_pos = udf_ext0_offset(dir);

	fibh.soffset = fibh.eoffset = nf_pos & (sb->s_blocksize - 1);
	अगर (iinfo->i_alloc_type != ICBTAG_FLAG_AD_IN_ICB) अणु
		अगर (inode_bmap(dir, nf_pos >> sb->s_blocksize_bits,
		    &epos, &eloc, &elen, &offset)
		    != (EXT_RECORDED_ALLOCATED >> 30)) अणु
			ret = -ENOENT;
			जाओ out;
		पूर्ण
		block = udf_get_lb_pblock(sb, &eloc, offset);
		अगर ((++offset << sb->s_blocksize_bits) < elen) अणु
			अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_SHORT)
				epos.offset -= माप(काष्ठा लघु_ad);
			अन्यथा अगर (iinfo->i_alloc_type ==
					ICBTAG_FLAG_AD_LONG)
				epos.offset -= माप(काष्ठा दीर्घ_ad);
		पूर्ण अन्यथा अणु
			offset = 0;
		पूर्ण

		अगर (!(fibh.sbh = fibh.ebh = udf_tपढ़ो(sb, block))) अणु
			ret = -EIO;
			जाओ out;
		पूर्ण

		अगर (!(offset & ((16 >> (sb->s_blocksize_bits - 9)) - 1))) अणु
			i = 16 >> (sb->s_blocksize_bits - 9);
			अगर (i + offset > (elen >> sb->s_blocksize_bits))
				i = (elen >> sb->s_blocksize_bits) - offset;
			क्रम (num = 0; i > 0; i--) अणु
				block = udf_get_lb_pblock(sb, &eloc, offset + i);
				पंचांगp = udf_tgetblk(sb, block);
				अगर (पंचांगp && !buffer_uptodate(पंचांगp) && !buffer_locked(पंचांगp))
					bha[num++] = पंचांगp;
				अन्यथा
					brअन्यथा(पंचांगp);
			पूर्ण
			अगर (num) अणु
				ll_rw_block(REQ_OP_READ, REQ_RAHEAD, num, bha);
				क्रम (i = 0; i < num; i++)
					brअन्यथा(bha[i]);
			पूर्ण
		पूर्ण
	पूर्ण

	जबतक (nf_pos < size) अणु
		काष्ठा kernel_lb_addr tloc;

		ctx->pos = (nf_pos >> 2) + 1;

		fi = udf_fileident_पढ़ो(dir, &nf_pos, &fibh, &cfi, &epos, &eloc,
					&elen, &offset);
		अगर (!fi)
			जाओ out;

		liu = le16_to_cpu(cfi.lengthOfImpUse);
		lfi = cfi.lengthFileIdent;

		अगर (fibh.sbh == fibh.ebh) अणु
			nameptr = fi->fileIdent + liu;
		पूर्ण अन्यथा अणु
			पूर्णांक poffset;	/* Unpaded ending offset */

			poffset = fibh.soffset + माप(काष्ठा fileIdentDesc) + liu + lfi;

			अगर (poffset >= lfi) अणु
				nameptr = (अक्षर *)(fibh.ebh->b_data + poffset - lfi);
			पूर्ण अन्यथा अणु
				अगर (!copy_name) अणु
					copy_name = kदो_स्मृति(UDF_NAME_LEN,
							    GFP_NOFS);
					अगर (!copy_name) अणु
						ret = -ENOMEM;
						जाओ out;
					पूर्ण
				पूर्ण
				nameptr = copy_name;
				स_नकल(nameptr, fi->fileIdent + liu,
				       lfi - poffset);
				स_नकल(nameptr + lfi - poffset,
				       fibh.ebh->b_data, poffset);
			पूर्ण
		पूर्ण

		अगर ((cfi.fileCharacteristics & FID_खाता_CHAR_DELETED) != 0) अणु
			अगर (!UDF_QUERY_FLAG(sb, UDF_FLAG_UNDELETE))
				जारी;
		पूर्ण

		अगर ((cfi.fileCharacteristics & FID_खाता_CHAR_HIDDEN) != 0) अणु
			अगर (!UDF_QUERY_FLAG(sb, UDF_FLAG_UNHIDE))
				जारी;
		पूर्ण

		अगर (cfi.fileCharacteristics & FID_खाता_CHAR_PARENT) अणु
			अगर (!dir_emit_करोtकरोt(file, ctx))
				जाओ out;
			जारी;
		पूर्ण

		flen = udf_get_filename(sb, nameptr, lfi, fname, UDF_NAME_LEN);
		अगर (flen < 0)
			जारी;

		tloc = lelb_to_cpu(cfi.icb.extLocation);
		iblock = udf_get_lb_pblock(sb, &tloc, 0);
		अगर (!dir_emit(ctx, fname, flen, iblock, DT_UNKNOWN))
			जाओ out;
	पूर्ण /* end जबतक */

	ctx->pos = (nf_pos >> 2) + 1;

out:
	अगर (fibh.sbh != fibh.ebh)
		brअन्यथा(fibh.ebh);
	brअन्यथा(fibh.sbh);
	brअन्यथा(epos.bh);
	kमुक्त(fname);
	kमुक्त(copy_name);

	वापस ret;
पूर्ण

/* सूची_पढ़ो and lookup functions */
स्थिर काष्ठा file_operations udf_dir_operations = अणु
	.llseek			= generic_file_llseek,
	.पढ़ो			= generic_पढ़ो_dir,
	.iterate_shared		= udf_सूची_पढ़ो,
	.unlocked_ioctl		= udf_ioctl,
	.fsync			= generic_file_fsync,
पूर्ण;
