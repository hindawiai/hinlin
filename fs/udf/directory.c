<शैली गुरु>
/*
 * directory.c
 *
 * PURPOSE
 *	Directory related functions
 *
 * COPYRIGHT
 *	This file is distributed under the terms of the GNU General Public
 *	License (GPL). Copies of the GPL can be obtained from:
 *		ftp://prep.ai.mit.edu/pub/gnu/GPL
 *	Each contributing author retains all rights to their own work.
 */

#समावेश "udfdecl.h"
#समावेश "udf_i.h"

#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/bपन.स>

काष्ठा fileIdentDesc *udf_fileident_पढ़ो(काष्ठा inode *dir, loff_t *nf_pos,
					 काष्ठा udf_fileident_bh *fibh,
					 काष्ठा fileIdentDesc *cfi,
					 काष्ठा extent_position *epos,
					 काष्ठा kernel_lb_addr *eloc, uपूर्णांक32_t *elen,
					 sector_t *offset)
अणु
	काष्ठा fileIdentDesc *fi;
	पूर्णांक i, num;
	udf_pblk_t block;
	काष्ठा buffer_head *पंचांगp, *bha[16];
	काष्ठा udf_inode_info *iinfo = UDF_I(dir);

	fibh->soffset = fibh->eoffset;

	अगर (iinfo->i_alloc_type == ICBTAG_FLAG_AD_IN_ICB) अणु
		fi = udf_get_fileident(iinfo->i_data -
				       (iinfo->i_efe ?
					माप(काष्ठा extendedFileEntry) :
					माप(काष्ठा fileEntry)),
				       dir->i_sb->s_blocksize,
				       &(fibh->eoffset));
		अगर (!fi)
			वापस शून्य;

		*nf_pos += fibh->eoffset - fibh->soffset;

		स_नकल((uपूर्णांक8_t *)cfi, (uपूर्णांक8_t *)fi,
		       माप(काष्ठा fileIdentDesc));

		वापस fi;
	पूर्ण

	अगर (fibh->eoffset == dir->i_sb->s_blocksize) अणु
		uपूर्णांक32_t lextoffset = epos->offset;
		अचिन्हित अक्षर blocksize_bits = dir->i_sb->s_blocksize_bits;

		अगर (udf_next_aext(dir, epos, eloc, elen, 1) !=
		    (EXT_RECORDED_ALLOCATED >> 30))
			वापस शून्य;

		block = udf_get_lb_pblock(dir->i_sb, eloc, *offset);

		(*offset)++;

		अगर ((*offset << blocksize_bits) >= *elen)
			*offset = 0;
		अन्यथा
			epos->offset = lextoffset;

		brअन्यथा(fibh->sbh);
		fibh->sbh = fibh->ebh = udf_tपढ़ो(dir->i_sb, block);
		अगर (!fibh->sbh)
			वापस शून्य;
		fibh->soffset = fibh->eoffset = 0;

		अगर (!(*offset & ((16 >> (blocksize_bits - 9)) - 1))) अणु
			i = 16 >> (blocksize_bits - 9);
			अगर (i + *offset > (*elen >> blocksize_bits))
				i = (*elen >> blocksize_bits)-*offset;
			क्रम (num = 0; i > 0; i--) अणु
				block = udf_get_lb_pblock(dir->i_sb, eloc,
							  *offset + i);
				पंचांगp = udf_tgetblk(dir->i_sb, block);
				अगर (पंचांगp && !buffer_uptodate(पंचांगp) &&
						!buffer_locked(पंचांगp))
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
	पूर्ण अन्यथा अगर (fibh->sbh != fibh->ebh) अणु
		brअन्यथा(fibh->sbh);
		fibh->sbh = fibh->ebh;
	पूर्ण

	fi = udf_get_fileident(fibh->sbh->b_data, dir->i_sb->s_blocksize,
			       &(fibh->eoffset));

	अगर (!fi)
		वापस शून्य;

	*nf_pos += fibh->eoffset - fibh->soffset;

	अगर (fibh->eoffset <= dir->i_sb->s_blocksize) अणु
		स_नकल((uपूर्णांक8_t *)cfi, (uपूर्णांक8_t *)fi,
		       माप(काष्ठा fileIdentDesc));
	पूर्ण अन्यथा अगर (fibh->eoffset > dir->i_sb->s_blocksize) अणु
		uपूर्णांक32_t lextoffset = epos->offset;

		अगर (udf_next_aext(dir, epos, eloc, elen, 1) !=
		    (EXT_RECORDED_ALLOCATED >> 30))
			वापस शून्य;

		block = udf_get_lb_pblock(dir->i_sb, eloc, *offset);

		(*offset)++;

		अगर ((*offset << dir->i_sb->s_blocksize_bits) >= *elen)
			*offset = 0;
		अन्यथा
			epos->offset = lextoffset;

		fibh->soffset -= dir->i_sb->s_blocksize;
		fibh->eoffset -= dir->i_sb->s_blocksize;

		fibh->ebh = udf_tपढ़ो(dir->i_sb, block);
		अगर (!fibh->ebh)
			वापस शून्य;

		अगर (माप(काष्ठा fileIdentDesc) > -fibh->soffset) अणु
			पूर्णांक fi_len;

			स_नकल((uपूर्णांक8_t *)cfi, (uपूर्णांक8_t *)fi, -fibh->soffset);
			स_नकल((uपूर्णांक8_t *)cfi - fibh->soffset,
			       fibh->ebh->b_data,
			       माप(काष्ठा fileIdentDesc) + fibh->soffset);

			fi_len = udf_dir_entry_len(cfi);
			*nf_pos += fi_len - (fibh->eoffset - fibh->soffset);
			fibh->eoffset = fibh->soffset + fi_len;
		पूर्ण अन्यथा अणु
			स_नकल((uपूर्णांक8_t *)cfi, (uपूर्णांक8_t *)fi,
			       माप(काष्ठा fileIdentDesc));
		पूर्ण
	पूर्ण
	/* Got last entry outside of dir size - fs is corrupted! */
	अगर (*nf_pos > dir->i_size)
		वापस शून्य;
	वापस fi;
पूर्ण

काष्ठा fileIdentDesc *udf_get_fileident(व्योम *buffer, पूर्णांक bufsize, पूर्णांक *offset)
अणु
	काष्ठा fileIdentDesc *fi;
	पूर्णांक lengthThisIdent;
	uपूर्णांक8_t *ptr;
	पूर्णांक padlen;

	अगर ((!buffer) || (!offset)) अणु
		udf_debug("invalidparms, buffer=%p, offset=%p\n",
			  buffer, offset);
		वापस शून्य;
	पूर्ण

	ptr = buffer;

	अगर ((*offset > 0) && (*offset < bufsize))
		ptr += *offset;
	fi = (काष्ठा fileIdentDesc *)ptr;
	अगर (fi->descTag.tagIdent != cpu_to_le16(TAG_IDENT_FID)) अणु
		udf_debug("0x%x != TAG_IDENT_FID\n",
			  le16_to_cpu(fi->descTag.tagIdent));
		udf_debug("offset: %d sizeof: %lu bufsize: %d\n",
			  *offset, (अचिन्हित दीर्घ)माप(काष्ठा fileIdentDesc),
			  bufsize);
		वापस शून्य;
	पूर्ण
	अगर ((*offset + माप(काष्ठा fileIdentDesc)) > bufsize)
		lengthThisIdent = माप(काष्ठा fileIdentDesc);
	अन्यथा
		lengthThisIdent = माप(काष्ठा fileIdentDesc) +
			fi->lengthFileIdent + le16_to_cpu(fi->lengthOfImpUse);

	/* we need to figure padding, too! */
	padlen = lengthThisIdent % UDF_NAME_PAD;
	अगर (padlen)
		lengthThisIdent += (UDF_NAME_PAD - padlen);
	*offset = *offset + lengthThisIdent;

	वापस fi;
पूर्ण

काष्ठा लघु_ad *udf_get_fileलघुad(uपूर्णांक8_t *ptr, पूर्णांक maxoffset, uपूर्णांक32_t *offset,
			      पूर्णांक inc)
अणु
	काष्ठा लघु_ad *sa;

	अगर ((!ptr) || (!offset)) अणु
		pr_err("%s: invalidparms\n", __func__);
		वापस शून्य;
	पूर्ण

	अगर ((*offset + माप(काष्ठा लघु_ad)) > maxoffset)
		वापस शून्य;
	अन्यथा अणु
		sa = (काष्ठा लघु_ad *)ptr;
		अगर (sa->extLength == 0)
			वापस शून्य;
	पूर्ण

	अगर (inc)
		*offset += माप(काष्ठा लघु_ad);
	वापस sa;
पूर्ण

काष्ठा दीर्घ_ad *udf_get_fileदीर्घad(uपूर्णांक8_t *ptr, पूर्णांक maxoffset, uपूर्णांक32_t *offset, पूर्णांक inc)
अणु
	काष्ठा दीर्घ_ad *la;

	अगर ((!ptr) || (!offset)) अणु
		pr_err("%s: invalidparms\n", __func__);
		वापस शून्य;
	पूर्ण

	अगर ((*offset + माप(काष्ठा दीर्घ_ad)) > maxoffset)
		वापस शून्य;
	अन्यथा अणु
		la = (काष्ठा दीर्घ_ad *)ptr;
		अगर (la->extLength == 0)
			वापस शून्य;
	पूर्ण

	अगर (inc)
		*offset += माप(काष्ठा दीर्घ_ad);
	वापस la;
पूर्ण
