<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/isofs/rock.c
 *
 *  (C) 1992, 1993  Eric Youngdale
 *
 *  Rock Ridge Extensions to iso9660
 */

#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>

#समावेश "isofs.h"
#समावेश "rock.h"

/*
 * These functions are deचिन्हित to पढ़ो the प्रणाली areas of a directory record
 * and extract relevant inक्रमmation.  There are dअगरferent functions provided
 * depending upon what inक्रमmation we need at the समय.  One function fills
 * out an inode काष्ठाure, a second one extracts a filename, a third one
 * वापसs a symbolic link name, and a fourth one वापसs the extent number
 * क्रम the file.
 */

#घोषणा SIG(A,B) ((A) | ((B) << 8))	/* isonum_721() */

काष्ठा rock_state अणु
	व्योम *buffer;
	अचिन्हित अक्षर *chr;
	पूर्णांक len;
	पूर्णांक cont_size;
	पूर्णांक cont_extent;
	पूर्णांक cont_offset;
	पूर्णांक cont_loops;
	काष्ठा inode *inode;
पूर्ण;

/*
 * This is a way of ensuring that we have something in the प्रणाली
 * use fields that is compatible with Rock Ridge.  Return zero on success.
 */

अटल पूर्णांक check_sp(काष्ठा rock_ridge *rr, काष्ठा inode *inode)
अणु
	अगर (rr->u.SP.magic[0] != 0xbe)
		वापस -1;
	अगर (rr->u.SP.magic[1] != 0xef)
		वापस -1;
	ISOFS_SB(inode->i_sb)->s_rock_offset = rr->u.SP.skip;
	वापस 0;
पूर्ण

अटल व्योम setup_rock_ridge(काष्ठा iso_directory_record *de,
			काष्ठा inode *inode, काष्ठा rock_state *rs)
अणु
	rs->len = माप(काष्ठा iso_directory_record) + de->name_len[0];
	अगर (rs->len & 1)
		(rs->len)++;
	rs->chr = (अचिन्हित अक्षर *)de + rs->len;
	rs->len = *((अचिन्हित अक्षर *)de) - rs->len;
	अगर (rs->len < 0)
		rs->len = 0;

	अगर (ISOFS_SB(inode->i_sb)->s_rock_offset != -1) अणु
		rs->len -= ISOFS_SB(inode->i_sb)->s_rock_offset;
		rs->chr += ISOFS_SB(inode->i_sb)->s_rock_offset;
		अगर (rs->len < 0)
			rs->len = 0;
	पूर्ण
पूर्ण

अटल व्योम init_rock_state(काष्ठा rock_state *rs, काष्ठा inode *inode)
अणु
	स_रखो(rs, 0, माप(*rs));
	rs->inode = inode;
पूर्ण

/* Maximum number of Rock Ridge continuation entries */
#घोषणा RR_MAX_CE_ENTRIES 32

/*
 * Returns 0 अगर the caller should जारी scanning, 1 अगर the scan must end
 * and -ve on error.
 */
अटल पूर्णांक rock_जारी(काष्ठा rock_state *rs)
अणु
	पूर्णांक ret = 1;
	पूर्णांक blocksize = 1 << rs->inode->i_blkbits;
	स्थिर पूर्णांक min_de_size = दुरत्व(काष्ठा rock_ridge, u);

	kमुक्त(rs->buffer);
	rs->buffer = शून्य;

	अगर ((अचिन्हित)rs->cont_offset > blocksize - min_de_size ||
	    (अचिन्हित)rs->cont_size > blocksize ||
	    (अचिन्हित)(rs->cont_offset + rs->cont_size) > blocksize) अणु
		prपूर्णांकk(KERN_NOTICE "rock: corrupted directory entry. "
			"extent=%d, offset=%d, size=%d\n",
			rs->cont_extent, rs->cont_offset, rs->cont_size);
		ret = -EIO;
		जाओ out;
	पूर्ण

	अगर (rs->cont_extent) अणु
		काष्ठा buffer_head *bh;

		rs->buffer = kदो_स्मृति(rs->cont_size, GFP_KERNEL);
		अगर (!rs->buffer) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण
		ret = -EIO;
		अगर (++rs->cont_loops >= RR_MAX_CE_ENTRIES)
			जाओ out;
		bh = sb_bपढ़ो(rs->inode->i_sb, rs->cont_extent);
		अगर (bh) अणु
			स_नकल(rs->buffer, bh->b_data + rs->cont_offset,
					rs->cont_size);
			put_bh(bh);
			rs->chr = rs->buffer;
			rs->len = rs->cont_size;
			rs->cont_extent = 0;
			rs->cont_size = 0;
			rs->cont_offset = 0;
			वापस 0;
		पूर्ण
		prपूर्णांकk("Unable to read rock-ridge attributes\n");
	पूर्ण
out:
	kमुक्त(rs->buffer);
	rs->buffer = शून्य;
	वापस ret;
पूर्ण

/*
 * We think there's a record of type `sig' at rs->chr.  Parse the signature
 * and make sure that there's really room क्रम a record of that type.
 */
अटल पूर्णांक rock_check_overflow(काष्ठा rock_state *rs, पूर्णांक sig)
अणु
	पूर्णांक len;

	चयन (sig) अणु
	हाल SIG('S', 'P'):
		len = माप(काष्ठा SU_SP_s);
		अवरोध;
	हाल SIG('C', 'E'):
		len = माप(काष्ठा SU_CE_s);
		अवरोध;
	हाल SIG('E', 'R'):
		len = माप(काष्ठा SU_ER_s);
		अवरोध;
	हाल SIG('R', 'R'):
		len = माप(काष्ठा RR_RR_s);
		अवरोध;
	हाल SIG('P', 'X'):
		len = माप(काष्ठा RR_PX_s);
		अवरोध;
	हाल SIG('P', 'N'):
		len = माप(काष्ठा RR_PN_s);
		अवरोध;
	हाल SIG('S', 'L'):
		len = माप(काष्ठा RR_SL_s);
		अवरोध;
	हाल SIG('N', 'M'):
		len = माप(काष्ठा RR_NM_s);
		अवरोध;
	हाल SIG('C', 'L'):
		len = माप(काष्ठा RR_CL_s);
		अवरोध;
	हाल SIG('P', 'L'):
		len = माप(काष्ठा RR_PL_s);
		अवरोध;
	हाल SIG('T', 'F'):
		len = माप(काष्ठा RR_TF_s);
		अवरोध;
	हाल SIG('Z', 'F'):
		len = माप(काष्ठा RR_ZF_s);
		अवरोध;
	शेष:
		len = 0;
		अवरोध;
	पूर्ण
	len += दुरत्व(काष्ठा rock_ridge, u);
	अगर (len > rs->len) अणु
		prपूर्णांकk(KERN_NOTICE "rock: directory entry would overflow "
				"storage\n");
		prपूर्णांकk(KERN_NOTICE "rock: sig=0x%02x, size=%d, remaining=%d\n",
				sig, len, rs->len);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * वापस length of name field; 0: not found, -1: to be ignored
 */
पूर्णांक get_rock_ridge_filename(काष्ठा iso_directory_record *de,
			    अक्षर *retname, काष्ठा inode *inode)
अणु
	काष्ठा rock_state rs;
	काष्ठा rock_ridge *rr;
	पूर्णांक sig;
	पूर्णांक retnamlen = 0;
	पूर्णांक truncate = 0;
	पूर्णांक ret = 0;
	अक्षर *p;
	पूर्णांक len;

	अगर (!ISOFS_SB(inode->i_sb)->s_rock)
		वापस 0;
	*retname = 0;

	init_rock_state(&rs, inode);
	setup_rock_ridge(de, inode, &rs);
repeat:

	जबतक (rs.len > 2) अणु /* There may be one byte क्रम padding somewhere */
		rr = (काष्ठा rock_ridge *)rs.chr;
		/*
		 * Ignore rock ridge info अगर rr->len is out of range, but
		 * करोn't वापस -EIO because that would make the file
		 * invisible.
		 */
		अगर (rr->len < 3)
			जाओ out;	/* Something got screwed up here */
		sig = isonum_721(rs.chr);
		अगर (rock_check_overflow(&rs, sig))
			जाओ eio;
		rs.chr += rr->len;
		rs.len -= rr->len;
		/*
		 * As above, just ignore the rock ridge info अगर rr->len
		 * is bogus.
		 */
		अगर (rs.len < 0)
			जाओ out;	/* Something got screwed up here */

		चयन (sig) अणु
		हाल SIG('R', 'R'):
			अगर ((rr->u.RR.flags[0] & RR_NM) == 0)
				जाओ out;
			अवरोध;
		हाल SIG('S', 'P'):
			अगर (check_sp(rr, inode))
				जाओ out;
			अवरोध;
		हाल SIG('C', 'E'):
			rs.cont_extent = isonum_733(rr->u.CE.extent);
			rs.cont_offset = isonum_733(rr->u.CE.offset);
			rs.cont_size = isonum_733(rr->u.CE.size);
			अवरोध;
		हाल SIG('N', 'M'):
			अगर (truncate)
				अवरोध;
			अगर (rr->len < 5)
				अवरोध;
			/*
			 * If the flags are 2 or 4, this indicates '.' or '..'.
			 * We करोn't want to करो anything with this, because it
			 * screws up the code that calls us.  We करोn't really
			 * care anyways, since we can just use the non-RR
			 * name.
			 */
			अगर (rr->u.NM.flags & 6)
				अवरोध;

			अगर (rr->u.NM.flags & ~1) अणु
				prपूर्णांकk("Unsupported NM flag settings (%d)\n",
					rr->u.NM.flags);
				अवरोध;
			पूर्ण
			len = rr->len - 5;
			अगर (retnamlen + len >= 254) अणु
				truncate = 1;
				अवरोध;
			पूर्ण
			p = स_प्रथम(rr->u.NM.name, '\0', len);
			अगर (unlikely(p))
				len = p - rr->u.NM.name;
			स_नकल(retname + retnamlen, rr->u.NM.name, len);
			retnamlen += len;
			retname[retnamlen] = '\0';
			अवरोध;
		हाल SIG('R', 'E'):
			kमुक्त(rs.buffer);
			वापस -1;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	ret = rock_जारी(&rs);
	अगर (ret == 0)
		जाओ repeat;
	अगर (ret == 1)
		वापस retnamlen; /* If 0, this file did not have a NM field */
out:
	kमुक्त(rs.buffer);
	वापस ret;
eio:
	ret = -EIO;
	जाओ out;
पूर्ण

#घोषणा RR_REGARD_XA 1
#घोषणा RR_RELOC_DE 2

अटल पूर्णांक
parse_rock_ridge_inode_पूर्णांकernal(काष्ठा iso_directory_record *de,
				काष्ठा inode *inode, पूर्णांक flags)
अणु
	पूर्णांक symlink_len = 0;
	पूर्णांक cnt, sig;
	अचिन्हित पूर्णांक reloc_block;
	काष्ठा inode *reloc;
	काष्ठा rock_ridge *rr;
	पूर्णांक rootflag;
	काष्ठा rock_state rs;
	पूर्णांक ret = 0;

	अगर (!ISOFS_SB(inode->i_sb)->s_rock)
		वापस 0;

	init_rock_state(&rs, inode);
	setup_rock_ridge(de, inode, &rs);
	अगर (flags & RR_REGARD_XA) अणु
		rs.chr += 14;
		rs.len -= 14;
		अगर (rs.len < 0)
			rs.len = 0;
	पूर्ण

repeat:
	जबतक (rs.len > 2) अणु /* There may be one byte क्रम padding somewhere */
		rr = (काष्ठा rock_ridge *)rs.chr;
		/*
		 * Ignore rock ridge info अगर rr->len is out of range, but
		 * करोn't वापस -EIO because that would make the file
		 * invisible.
		 */
		अगर (rr->len < 3)
			जाओ out;	/* Something got screwed up here */
		sig = isonum_721(rs.chr);
		अगर (rock_check_overflow(&rs, sig))
			जाओ eio;
		rs.chr += rr->len;
		rs.len -= rr->len;
		/*
		 * As above, just ignore the rock ridge info अगर rr->len
		 * is bogus.
		 */
		अगर (rs.len < 0)
			जाओ out;	/* Something got screwed up here */

		चयन (sig) अणु
#अगर_अघोषित CONFIG_ZISOFS		/* No flag क्रम SF or ZF */
		हाल SIG('R', 'R'):
			अगर ((rr->u.RR.flags[0] &
			     (RR_PX | RR_TF | RR_SL | RR_CL)) == 0)
				जाओ out;
			अवरोध;
#पूर्ण_अगर
		हाल SIG('S', 'P'):
			अगर (check_sp(rr, inode))
				जाओ out;
			अवरोध;
		हाल SIG('C', 'E'):
			rs.cont_extent = isonum_733(rr->u.CE.extent);
			rs.cont_offset = isonum_733(rr->u.CE.offset);
			rs.cont_size = isonum_733(rr->u.CE.size);
			अवरोध;
		हाल SIG('E', 'R'):
			/* Invalid length of ER tag id? */
			अगर (rr->u.ER.len_id + दुरत्व(काष्ठा rock_ridge, u.ER.data) > rr->len)
				जाओ out;
			ISOFS_SB(inode->i_sb)->s_rock = 1;
			prपूर्णांकk(KERN_DEBUG "ISO 9660 Extensions: ");
			अणु
				पूर्णांक p;
				क्रम (p = 0; p < rr->u.ER.len_id; p++)
					prपूर्णांकk(KERN_CONT "%c", rr->u.ER.data[p]);
			पूर्ण
			prपूर्णांकk(KERN_CONT "\n");
			अवरोध;
		हाल SIG('P', 'X'):
			inode->i_mode = isonum_733(rr->u.PX.mode);
			set_nlink(inode, isonum_733(rr->u.PX.n_links));
			i_uid_ग_लिखो(inode, isonum_733(rr->u.PX.uid));
			i_gid_ग_लिखो(inode, isonum_733(rr->u.PX.gid));
			अवरोध;
		हाल SIG('P', 'N'):
			अणु
				पूर्णांक high, low;
				high = isonum_733(rr->u.PN.dev_high);
				low = isonum_733(rr->u.PN.dev_low);
				/*
				 * The Rock Ridge standard specअगरies that अगर
				 * माप(dev_t) <= 4, then the high field is
				 * unused, and the device number is completely
				 * stored in the low field.  Some ग_लिखोrs may
				 * ignore this subtlety,
				 * and as a result we test to see अगर the entire
				 * device number is
				 * stored in the low field, and use that.
				 */
				अगर ((low & ~0xff) && high == 0) अणु
					inode->i_rdev =
					    MKDEV(low >> 8, low & 0xff);
				पूर्ण अन्यथा अणु
					inode->i_rdev =
					    MKDEV(high, low);
				पूर्ण
			पूर्ण
			अवरोध;
		हाल SIG('T', 'F'):
			/*
			 * Some RRIP ग_लिखोrs incorrectly place स_समय in the
			 * TF_CREATE field. Try to handle this correctly क्रम
			 * either हाल.
			 */
			/* Rock ridge never appears on a High Sierra disk */
			cnt = 0;
			अगर (rr->u.TF.flags & TF_CREATE) अणु
				inode->i_स_समय.tv_sec =
				    iso_date(rr->u.TF.बार[cnt++].समय,
					     0);
				inode->i_स_समय.tv_nsec = 0;
			पूर्ण
			अगर (rr->u.TF.flags & TF_MODIFY) अणु
				inode->i_mसमय.tv_sec =
				    iso_date(rr->u.TF.बार[cnt++].समय,
					     0);
				inode->i_mसमय.tv_nsec = 0;
			पूर्ण
			अगर (rr->u.TF.flags & TF_ACCESS) अणु
				inode->i_aसमय.tv_sec =
				    iso_date(rr->u.TF.बार[cnt++].समय,
					     0);
				inode->i_aसमय.tv_nsec = 0;
			पूर्ण
			अगर (rr->u.TF.flags & TF_ATTRIBUTES) अणु
				inode->i_स_समय.tv_sec =
				    iso_date(rr->u.TF.बार[cnt++].समय,
					     0);
				inode->i_स_समय.tv_nsec = 0;
			पूर्ण
			अवरोध;
		हाल SIG('S', 'L'):
			अणु
				पूर्णांक slen;
				काष्ठा SL_component *slp;
				काष्ठा SL_component *oldslp;
				slen = rr->len - 5;
				slp = &rr->u.SL.link;
				inode->i_size = symlink_len;
				जबतक (slen > 1) अणु
					rootflag = 0;
					चयन (slp->flags & ~1) अणु
					हाल 0:
						inode->i_size +=
						    slp->len;
						अवरोध;
					हाल 2:
						inode->i_size += 1;
						अवरोध;
					हाल 4:
						inode->i_size += 2;
						अवरोध;
					हाल 8:
						rootflag = 1;
						inode->i_size += 1;
						अवरोध;
					शेष:
						prपूर्णांकk("Symlink component flag "
							"not implemented\n");
					पूर्ण
					slen -= slp->len + 2;
					oldslp = slp;
					slp = (काष्ठा SL_component *)
						(((अक्षर *)slp) + slp->len + 2);

					अगर (slen < 2) अणु
						अगर (((rr->u.SL.
						      flags & 1) != 0)
						    &&
						    ((oldslp->
						      flags & 1) == 0))
							inode->i_size +=
							    1;
						अवरोध;
					पूर्ण

					/*
					 * If this component record isn't
					 * जारीd, then append a '/'.
					 */
					अगर (!rootflag
					    && (oldslp->flags & 1) == 0)
						inode->i_size += 1;
				पूर्ण
			पूर्ण
			symlink_len = inode->i_size;
			अवरोध;
		हाल SIG('R', 'E'):
			prपूर्णांकk(KERN_WARNING "Attempt to read inode for "
					"relocated directory\n");
			जाओ out;
		हाल SIG('C', 'L'):
			अगर (flags & RR_RELOC_DE) अणु
				prपूर्णांकk(KERN_ERR
				       "ISOFS: Recursive directory relocation "
				       "is not supported\n");
				जाओ eio;
			पूर्ण
			reloc_block = isonum_733(rr->u.CL.location);
			अगर (reloc_block == ISOFS_I(inode)->i_iget5_block &&
			    ISOFS_I(inode)->i_iget5_offset == 0) अणु
				prपूर्णांकk(KERN_ERR
				       "ISOFS: Directory relocation points to "
				       "itself\n");
				जाओ eio;
			पूर्ण
			ISOFS_I(inode)->i_first_extent = reloc_block;
			reloc = isofs_iget_reloc(inode->i_sb, reloc_block, 0);
			अगर (IS_ERR(reloc)) अणु
				ret = PTR_ERR(reloc);
				जाओ out;
			पूर्ण
			inode->i_mode = reloc->i_mode;
			set_nlink(inode, reloc->i_nlink);
			inode->i_uid = reloc->i_uid;
			inode->i_gid = reloc->i_gid;
			inode->i_rdev = reloc->i_rdev;
			inode->i_size = reloc->i_size;
			inode->i_blocks = reloc->i_blocks;
			inode->i_aसमय = reloc->i_aसमय;
			inode->i_स_समय = reloc->i_स_समय;
			inode->i_mसमय = reloc->i_mसमय;
			iput(reloc);
			अवरोध;
#अगर_घोषित CONFIG_ZISOFS
		हाल SIG('Z', 'F'): अणु
			पूर्णांक algo;

			अगर (ISOFS_SB(inode->i_sb)->s_nocompress)
				अवरोध;
			algo = isonum_721(rr->u.ZF.algorithm);
			अगर (algo == SIG('p', 'z')) अणु
				पूर्णांक block_shअगरt =
					isonum_711(&rr->u.ZF.parms[1]);
				अगर (block_shअगरt > 17) अणु
					prपूर्णांकk(KERN_WARNING "isofs: "
						"Can't handle ZF block "
						"size of 2^%d\न",
						block_shअगरt);
				पूर्ण अन्यथा अणु
					/*
					 * Note: we करोn't change
					 * i_blocks here
					 */
					ISOFS_I(inode)->i_file_क्रमmat =
						isofs_file_compressed;
					/*
					 * Parameters to compression
					 * algorithm (header size,
					 * block size)
					 */
					ISOFS_I(inode)->i_क्रमmat_parm[0] =
						isonum_711(&rr->u.ZF.parms[0]);
					ISOFS_I(inode)->i_क्रमmat_parm[1] =
						isonum_711(&rr->u.ZF.parms[1]);
					inode->i_size =
					    isonum_733(rr->u.ZF.
						       real_size);
				पूर्ण
			पूर्ण अन्यथा अणु
				prपूर्णांकk(KERN_WARNING
				       "isofs: Unknown ZF compression "
						"algorithm: %c%c\n",
				       rr->u.ZF.algorithm[0],
				       rr->u.ZF.algorithm[1]);
			पूर्ण
			अवरोध;
		पूर्ण
#पूर्ण_अगर
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	ret = rock_जारी(&rs);
	अगर (ret == 0)
		जाओ repeat;
	अगर (ret == 1)
		ret = 0;
out:
	kमुक्त(rs.buffer);
	वापस ret;
eio:
	ret = -EIO;
	जाओ out;
पूर्ण

अटल अक्षर *get_symlink_chunk(अक्षर *rpnt, काष्ठा rock_ridge *rr, अक्षर *plimit)
अणु
	पूर्णांक slen;
	पूर्णांक rootflag;
	काष्ठा SL_component *oldslp;
	काष्ठा SL_component *slp;
	slen = rr->len - 5;
	slp = &rr->u.SL.link;
	जबतक (slen > 1) अणु
		rootflag = 0;
		चयन (slp->flags & ~1) अणु
		हाल 0:
			अगर (slp->len > plimit - rpnt)
				वापस शून्य;
			स_नकल(rpnt, slp->text, slp->len);
			rpnt += slp->len;
			अवरोध;
		हाल 2:
			अगर (rpnt >= plimit)
				वापस शून्य;
			*rpnt++ = '.';
			अवरोध;
		हाल 4:
			अगर (2 > plimit - rpnt)
				वापस शून्य;
			*rpnt++ = '.';
			*rpnt++ = '.';
			अवरोध;
		हाल 8:
			अगर (rpnt >= plimit)
				वापस शून्य;
			rootflag = 1;
			*rpnt++ = '/';
			अवरोध;
		शेष:
			prपूर्णांकk("Symlink component flag not implemented (%d)\n",
			       slp->flags);
		पूर्ण
		slen -= slp->len + 2;
		oldslp = slp;
		slp = (काष्ठा SL_component *)((अक्षर *)slp + slp->len + 2);

		अगर (slen < 2) अणु
			/*
			 * If there is another SL record, and this component
			 * record isn't जारीd, then add a slash.
			 */
			अगर ((!rootflag) && (rr->u.SL.flags & 1) &&
			    !(oldslp->flags & 1)) अणु
				अगर (rpnt >= plimit)
					वापस शून्य;
				*rpnt++ = '/';
			पूर्ण
			अवरोध;
		पूर्ण

		/*
		 * If this component record isn't continued, then append a '/'.
		 */
		अगर (!rootflag && !(oldslp->flags & 1)) अणु
			अगर (rpnt >= plimit)
				वापस शून्य;
			*rpnt++ = '/';
		पूर्ण
	पूर्ण
	वापस rpnt;
पूर्ण

पूर्णांक parse_rock_ridge_inode(काष्ठा iso_directory_record *de, काष्ठा inode *inode,
			   पूर्णांक relocated)
अणु
	पूर्णांक flags = relocated ? RR_RELOC_DE : 0;
	पूर्णांक result = parse_rock_ridge_inode_पूर्णांकernal(de, inode, flags);

	/*
	 * अगर rockridge flag was reset and we didn't look क्रम attributes
	 * behind eventual XA attributes, have a look there
	 */
	अगर ((ISOFS_SB(inode->i_sb)->s_rock_offset == -1)
	    && (ISOFS_SB(inode->i_sb)->s_rock == 2)) अणु
		result = parse_rock_ridge_inode_पूर्णांकernal(de, inode,
							 flags | RR_REGARD_XA);
	पूर्ण
	वापस result;
पूर्ण

/*
 * पढ़ोpage() क्रम symlinks: पढ़ोs symlink contents पूर्णांकo the page and either
 * makes it uptodate and वापसs 0 or वापसs error (-EIO)
 */
अटल पूर्णांक rock_ridge_symlink_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	काष्ठा inode *inode = page->mapping->host;
	काष्ठा iso_inode_info *ei = ISOFS_I(inode);
	काष्ठा isofs_sb_info *sbi = ISOFS_SB(inode->i_sb);
	अक्षर *link = page_address(page);
	अचिन्हित दीर्घ bufsize = ISOFS_BUFFER_SIZE(inode);
	काष्ठा buffer_head *bh;
	अक्षर *rpnt = link;
	अचिन्हित अक्षर *pnt;
	काष्ठा iso_directory_record *raw_de;
	अचिन्हित दीर्घ block, offset;
	पूर्णांक sig;
	काष्ठा rock_ridge *rr;
	काष्ठा rock_state rs;
	पूर्णांक ret;

	अगर (!sbi->s_rock)
		जाओ error;

	init_rock_state(&rs, inode);
	block = ei->i_iget5_block;
	bh = sb_bपढ़ो(inode->i_sb, block);
	अगर (!bh)
		जाओ out_noपढ़ो;

	offset = ei->i_iget5_offset;
	pnt = (अचिन्हित अक्षर *)bh->b_data + offset;

	raw_de = (काष्ठा iso_directory_record *)pnt;

	/*
	 * If we go past the end of the buffer, there is some sort of error.
	 */
	अगर (offset + *pnt > bufsize)
		जाओ out_bad_span;

	/*
	 * Now test क्रम possible Rock Ridge extensions which will override
	 * some of these numbers in the inode काष्ठाure.
	 */

	setup_rock_ridge(raw_de, inode, &rs);

repeat:
	जबतक (rs.len > 2) अणु /* There may be one byte क्रम padding somewhere */
		rr = (काष्ठा rock_ridge *)rs.chr;
		अगर (rr->len < 3)
			जाओ out;	/* Something got screwed up here */
		sig = isonum_721(rs.chr);
		अगर (rock_check_overflow(&rs, sig))
			जाओ out;
		rs.chr += rr->len;
		rs.len -= rr->len;
		अगर (rs.len < 0)
			जाओ out;	/* corrupted isofs */

		चयन (sig) अणु
		हाल SIG('R', 'R'):
			अगर ((rr->u.RR.flags[0] & RR_SL) == 0)
				जाओ out;
			अवरोध;
		हाल SIG('S', 'P'):
			अगर (check_sp(rr, inode))
				जाओ out;
			अवरोध;
		हाल SIG('S', 'L'):
			rpnt = get_symlink_chunk(rpnt, rr,
						 link + (PAGE_SIZE - 1));
			अगर (rpnt == शून्य)
				जाओ out;
			अवरोध;
		हाल SIG('C', 'E'):
			/* This tells is अगर there is a continuation record */
			rs.cont_extent = isonum_733(rr->u.CE.extent);
			rs.cont_offset = isonum_733(rr->u.CE.offset);
			rs.cont_size = isonum_733(rr->u.CE.size);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण
	ret = rock_जारी(&rs);
	अगर (ret == 0)
		जाओ repeat;
	अगर (ret < 0)
		जाओ fail;

	अगर (rpnt == link)
		जाओ fail;
	brअन्यथा(bh);
	*rpnt = '\0';
	SetPageUptodate(page);
	unlock_page(page);
	वापस 0;

	/* error निकास from macro */
out:
	kमुक्त(rs.buffer);
	जाओ fail;
out_noपढ़ो:
	prपूर्णांकk("unable to read i-node block");
	जाओ fail;
out_bad_span:
	prपूर्णांकk("symlink spans iso9660 blocks\n");
fail:
	brअन्यथा(bh);
error:
	SetPageError(page);
	unlock_page(page);
	वापस -EIO;
पूर्ण

स्थिर काष्ठा address_space_operations isofs_symlink_aops = अणु
	.पढ़ोpage = rock_ridge_symlink_पढ़ोpage
पूर्ण;
