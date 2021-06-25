<शैली गुरु>
/*
 * misc.c
 *
 * PURPOSE
 *	Miscellaneous routines क्रम the OSTA-UDF(पंचांग) fileप्रणाली.
 *
 * COPYRIGHT
 *	This file is distributed under the terms of the GNU General Public
 *	License (GPL). Copies of the GPL can be obtained from:
 *		ftp://prep.ai.mit.edu/pub/gnu/GPL
 *	Each contributing author retains all rights to their own work.
 *
 *  (C) 1998 Dave Boynton
 *  (C) 1998-2004 Ben Fennema
 *  (C) 1999-2000 Stelias Computing Inc
 *
 * HISTORY
 *
 *  04/19/99 blf  partial support क्रम पढ़ोing/writing specअगरic EA's
 */

#समावेश "udfdecl.h"

#समावेश <linux/fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/crc-itu-t.h>

#समावेश "udf_i.h"
#समावेश "udf_sb.h"

काष्ठा buffer_head *udf_tgetblk(काष्ठा super_block *sb, udf_pblk_t block)
अणु
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_VARCONV))
		वापस sb_getblk(sb, udf_fixed_to_variable(block));
	अन्यथा
		वापस sb_getblk(sb, block);
पूर्ण

काष्ठा buffer_head *udf_tपढ़ो(काष्ठा super_block *sb, udf_pblk_t block)
अणु
	अगर (UDF_QUERY_FLAG(sb, UDF_FLAG_VARCONV))
		वापस sb_bपढ़ो(sb, udf_fixed_to_variable(block));
	अन्यथा
		वापस sb_bपढ़ो(sb, block);
पूर्ण

काष्ठा genericFormat *udf_add_extendedattr(काष्ठा inode *inode, uपूर्णांक32_t size,
					   uपूर्णांक32_t type, uपूर्णांक8_t loc)
अणु
	uपूर्णांक8_t *ea = शून्य, *ad = शून्य;
	पूर्णांक offset;
	uपूर्णांक16_t crclen;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);

	ea = iinfo->i_data;
	अगर (iinfo->i_lenEAttr) अणु
		ad = iinfo->i_data + iinfo->i_lenEAttr;
	पूर्ण अन्यथा अणु
		ad = ea;
		size += माप(काष्ठा extendedAttrHeaderDesc);
	पूर्ण

	offset = inode->i_sb->s_blocksize - udf_file_entry_alloc_offset(inode) -
		iinfo->i_lenAlloc;

	/* TODO - Check क्रम FreeEASpace */

	अगर (loc & 0x01 && offset >= size) अणु
		काष्ठा extendedAttrHeaderDesc *eahd;
		eahd = (काष्ठा extendedAttrHeaderDesc *)ea;

		अगर (iinfo->i_lenAlloc)
			स_हटाओ(&ad[size], ad, iinfo->i_lenAlloc);

		अगर (iinfo->i_lenEAttr) अणु
			/* check checksum/crc */
			अगर (eahd->descTag.tagIdent !=
					cpu_to_le16(TAG_IDENT_EAHD) ||
			    le32_to_cpu(eahd->descTag.tagLocation) !=
					iinfo->i_location.logicalBlockNum)
				वापस शून्य;
		पूर्ण अन्यथा अणु
			काष्ठा udf_sb_info *sbi = UDF_SB(inode->i_sb);

			size -= माप(काष्ठा extendedAttrHeaderDesc);
			iinfo->i_lenEAttr +=
				माप(काष्ठा extendedAttrHeaderDesc);
			eahd->descTag.tagIdent = cpu_to_le16(TAG_IDENT_EAHD);
			अगर (sbi->s_udfrev >= 0x0200)
				eahd->descTag.descVersion = cpu_to_le16(3);
			अन्यथा
				eahd->descTag.descVersion = cpu_to_le16(2);
			eahd->descTag.tagSerialNum =
					cpu_to_le16(sbi->s_serial_number);
			eahd->descTag.tagLocation = cpu_to_le32(
					iinfo->i_location.logicalBlockNum);
			eahd->impAttrLocation = cpu_to_le32(0xFFFFFFFF);
			eahd->appAttrLocation = cpu_to_le32(0xFFFFFFFF);
		पूर्ण

		offset = iinfo->i_lenEAttr;
		अगर (type < 2048) अणु
			अगर (le32_to_cpu(eahd->appAttrLocation) <
					iinfo->i_lenEAttr) अणु
				uपूर्णांक32_t aal =
					le32_to_cpu(eahd->appAttrLocation);
				स_हटाओ(&ea[offset - aal + size],
					&ea[aal], offset - aal);
				offset -= aal;
				eahd->appAttrLocation =
						cpu_to_le32(aal + size);
			पूर्ण
			अगर (le32_to_cpu(eahd->impAttrLocation) <
					iinfo->i_lenEAttr) अणु
				uपूर्णांक32_t ial =
					le32_to_cpu(eahd->impAttrLocation);
				स_हटाओ(&ea[offset - ial + size],
					&ea[ial], offset - ial);
				offset -= ial;
				eahd->impAttrLocation =
						cpu_to_le32(ial + size);
			पूर्ण
		पूर्ण अन्यथा अगर (type < 65536) अणु
			अगर (le32_to_cpu(eahd->appAttrLocation) <
					iinfo->i_lenEAttr) अणु
				uपूर्णांक32_t aal =
					le32_to_cpu(eahd->appAttrLocation);
				स_हटाओ(&ea[offset - aal + size],
					&ea[aal], offset - aal);
				offset -= aal;
				eahd->appAttrLocation =
						cpu_to_le32(aal + size);
			पूर्ण
		पूर्ण
		/* reग_लिखो CRC + checksum of eahd */
		crclen = माप(काष्ठा extendedAttrHeaderDesc) - माप(काष्ठा tag);
		eahd->descTag.descCRCLength = cpu_to_le16(crclen);
		eahd->descTag.descCRC = cpu_to_le16(crc_itu_t(0, (अक्षर *)eahd +
						माप(काष्ठा tag), crclen));
		eahd->descTag.tagChecksum = udf_tag_checksum(&eahd->descTag);
		iinfo->i_lenEAttr += size;
		वापस (काष्ठा genericFormat *)&ea[offset];
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा genericFormat *udf_get_extendedattr(काष्ठा inode *inode, uपूर्णांक32_t type,
					   uपूर्णांक8_t subtype)
अणु
	काष्ठा genericFormat *gaf;
	uपूर्णांक8_t *ea = शून्य;
	uपूर्णांक32_t offset;
	काष्ठा udf_inode_info *iinfo = UDF_I(inode);

	ea = iinfo->i_data;

	अगर (iinfo->i_lenEAttr) अणु
		काष्ठा extendedAttrHeaderDesc *eahd;
		eahd = (काष्ठा extendedAttrHeaderDesc *)ea;

		/* check checksum/crc */
		अगर (eahd->descTag.tagIdent !=
				cpu_to_le16(TAG_IDENT_EAHD) ||
		    le32_to_cpu(eahd->descTag.tagLocation) !=
				iinfo->i_location.logicalBlockNum)
			वापस शून्य;

		अगर (type < 2048)
			offset = माप(काष्ठा extendedAttrHeaderDesc);
		अन्यथा अगर (type < 65536)
			offset = le32_to_cpu(eahd->impAttrLocation);
		अन्यथा
			offset = le32_to_cpu(eahd->appAttrLocation);

		जबतक (offset < iinfo->i_lenEAttr) अणु
			gaf = (काष्ठा genericFormat *)&ea[offset];
			अगर (le32_to_cpu(gaf->attrType) == type &&
					gaf->attrSubtype == subtype)
				वापस gaf;
			अन्यथा
				offset += le32_to_cpu(gaf->attrLength);
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

/*
 * udf_पढ़ो_tagged
 *
 * PURPOSE
 *	Read the first block of a tagged descriptor.
 *
 * HISTORY
 *	July 1, 1997 - Andrew E. Mileski
 *	Written, tested, and released.
 */
काष्ठा buffer_head *udf_पढ़ो_tagged(काष्ठा super_block *sb, uपूर्णांक32_t block,
				    uपूर्णांक32_t location, uपूर्णांक16_t *ident)
अणु
	काष्ठा tag *tag_p;
	काष्ठा buffer_head *bh = शून्य;
	u8 checksum;

	/* Read the block */
	अगर (block == 0xFFFFFFFF)
		वापस शून्य;

	bh = udf_tपढ़ो(sb, block);
	अगर (!bh) अणु
		udf_err(sb, "read failed, block=%u, location=%u\n",
			block, location);
		वापस शून्य;
	पूर्ण

	tag_p = (काष्ठा tag *)(bh->b_data);

	*ident = le16_to_cpu(tag_p->tagIdent);

	अगर (location != le32_to_cpu(tag_p->tagLocation)) अणु
		udf_debug("location mismatch block %u, tag %u != %u\n",
			  block, le32_to_cpu(tag_p->tagLocation), location);
		जाओ error_out;
	पूर्ण

	/* Verअगरy the tag checksum */
	checksum = udf_tag_checksum(tag_p);
	अगर (checksum != tag_p->tagChecksum) अणु
		udf_err(sb, "tag checksum failed, block %u: 0x%02x != 0x%02x\n",
			block, checksum, tag_p->tagChecksum);
		जाओ error_out;
	पूर्ण

	/* Verअगरy the tag version */
	अगर (tag_p->descVersion != cpu_to_le16(0x0002U) &&
	    tag_p->descVersion != cpu_to_le16(0x0003U)) अणु
		udf_err(sb, "tag version 0x%04x != 0x0002 || 0x0003, block %u\n",
			le16_to_cpu(tag_p->descVersion), block);
		जाओ error_out;
	पूर्ण

	/* Verअगरy the descriptor CRC */
	अगर (le16_to_cpu(tag_p->descCRCLength) + माप(काष्ठा tag) > sb->s_blocksize ||
	    le16_to_cpu(tag_p->descCRC) == crc_itu_t(0,
					bh->b_data + माप(काष्ठा tag),
					le16_to_cpu(tag_p->descCRCLength)))
		वापस bh;

	udf_debug("Crc failure block %u: crc = %u, crclen = %u\n", block,
		  le16_to_cpu(tag_p->descCRC),
		  le16_to_cpu(tag_p->descCRCLength));
error_out:
	brअन्यथा(bh);
	वापस शून्य;
पूर्ण

काष्ठा buffer_head *udf_पढ़ो_ptagged(काष्ठा super_block *sb,
				     काष्ठा kernel_lb_addr *loc,
				     uपूर्णांक32_t offset, uपूर्णांक16_t *ident)
अणु
	वापस udf_पढ़ो_tagged(sb, udf_get_lb_pblock(sb, loc, offset),
			       loc->logicalBlockNum + offset, ident);
पूर्ण

व्योम udf_update_tag(अक्षर *data, पूर्णांक length)
अणु
	काष्ठा tag *tptr = (काष्ठा tag *)data;
	length -= माप(काष्ठा tag);

	tptr->descCRCLength = cpu_to_le16(length);
	tptr->descCRC = cpu_to_le16(crc_itu_t(0, data + माप(काष्ठा tag), length));
	tptr->tagChecksum = udf_tag_checksum(tptr);
पूर्ण

व्योम udf_new_tag(अक्षर *data, uपूर्णांक16_t ident, uपूर्णांक16_t version, uपूर्णांक16_t snum,
		 uपूर्णांक32_t loc, पूर्णांक length)
अणु
	काष्ठा tag *tptr = (काष्ठा tag *)data;
	tptr->tagIdent = cpu_to_le16(ident);
	tptr->descVersion = cpu_to_le16(version);
	tptr->tagSerialNum = cpu_to_le16(snum);
	tptr->tagLocation = cpu_to_le32(loc);
	udf_update_tag(data, length);
पूर्ण

u8 udf_tag_checksum(स्थिर काष्ठा tag *t)
अणु
	u8 *data = (u8 *)t;
	u8 checksum = 0;
	पूर्णांक i;
	क्रम (i = 0; i < माप(काष्ठा tag); ++i)
		अगर (i != 4) /* position of checksum */
			checksum += data[i];
	वापस checksum;
पूर्ण
