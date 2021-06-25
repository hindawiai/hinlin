<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/fat/dir.c
 *
 *  directory handling functions क्रम fat-based fileप्रणालीs
 *
 *  Written 1992,1993 by Werner Almesberger
 *
 *  Hidden files 1995 by Albert Cahalan <albert@ccs.neu.edu> <adc@coe.neu.edu>
 *
 *  VFAT extensions by Gorकरोn Chaffee <chaffee@plateau.cs.berkeley.edu>
 *  Merged with msकरोs fs by Henrik Storner <storner@osiris.ping.dk>
 *  Rewritten क्रम स्थिरant inumbers. Plugged buffer overrun in सूची_पढ़ो(). AV
 *  Short name translation 1999, 2001 by Wolfram Pienkoss <wp@bszh.de>
 */

#समावेश <linux/slab.h>
#समावेश <linux/compat.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/iversion.h>
#समावेश "fat.h"

/*
 * Maximum buffer size of लघु name.
 * [(MSDOS_NAME + '.') * max one अक्षर + nul]
 * For msकरोs style, ['.' (hidden) + MSDOS_NAME + '.' + nul]
 */
#घोषणा FAT_MAX_SHORT_SIZE	((MSDOS_NAME + 1) * NLS_MAX_CHARSET_SIZE + 1)
/*
 * Maximum buffer size of unicode अक्षरs from slots.
 * [(max दीर्घname slots * 13 (size in a slot) + nul) * माप(ब_अक्षर_प्रकार)]
 */
#घोषणा FAT_MAX_UNI_CHARS	((MSDOS_SLOTS - 1) * 13 + 1)
#घोषणा FAT_MAX_UNI_SIZE	(FAT_MAX_UNI_CHARS * माप(ब_अक्षर_प्रकार))

अटल अंतरभूत अचिन्हित अक्षर fat_छोटे(अचिन्हित अक्षर c)
अणु
	वापस ((c >= 'A') && (c <= 'Z')) ? c+32 : c;
पूर्ण

अटल अंतरभूत loff_t fat_make_i_pos(काष्ठा super_block *sb,
				    काष्ठा buffer_head *bh,
				    काष्ठा msकरोs_dir_entry *de)
अणु
	वापस ((loff_t)bh->b_blocknr << MSDOS_SB(sb)->dir_per_block_bits)
		| (de - (काष्ठा msकरोs_dir_entry *)bh->b_data);
पूर्ण

अटल अंतरभूत व्योम fat_dir_पढ़ोahead(काष्ठा inode *dir, sector_t iblock,
				     sector_t phys)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	काष्ठा buffer_head *bh;
	पूर्णांक sec;

	/* This is not a first sector of cluster, or sec_per_clus == 1 */
	अगर ((iblock & (sbi->sec_per_clus - 1)) || sbi->sec_per_clus == 1)
		वापस;
	/* root dir of FAT12/FAT16 */
	अगर (!is_fat32(sbi) && (dir->i_ino == MSDOS_ROOT_INO))
		वापस;

	bh = sb_find_get_block(sb, phys);
	अगर (bh == शून्य || !buffer_uptodate(bh)) अणु
		क्रम (sec = 0; sec < sbi->sec_per_clus; sec++)
			sb_bपढ़ोahead(sb, phys + sec);
	पूर्ण
	brअन्यथा(bh);
पूर्ण

/* Returns the inode number of the directory entry at offset pos. If bh is
   non-शून्य, it is brअन्यथा'd beक्रमe. Pos is incremented. The buffer header is
   वापसed in bh.
   AV. Most often we करो it item-by-item. Makes sense to optimize.
   AV. OK, there we go: अगर both bh and de are non-शून्य we assume that we just
   AV. want the next entry (took one explicit de=शून्य in vfat/namei.c).
   AV. It's करोne in fat_get_entry() (अंतरभूतd), here the slow हाल lives.
   AV. Additionally, when we वापस -1 (i.e. reached the end of directory)
   AV. we make bh शून्य.
 */
अटल पूर्णांक fat__get_entry(काष्ठा inode *dir, loff_t *pos,
			  काष्ठा buffer_head **bh, काष्ठा msकरोs_dir_entry **de)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	sector_t phys, iblock;
	अचिन्हित दीर्घ mapped_blocks;
	पूर्णांक err, offset;

next:
	brअन्यथा(*bh);
	*bh = शून्य;
	iblock = *pos >> sb->s_blocksize_bits;
	err = fat_bmap(dir, iblock, &phys, &mapped_blocks, 0, false);
	अगर (err || !phys)
		वापस -1;	/* beyond खातापूर्ण or error */

	fat_dir_पढ़ोahead(dir, iblock, phys);

	*bh = sb_bपढ़ो(sb, phys);
	अगर (*bh == शून्य) अणु
		fat_msg_ratelimit(sb, KERN_ERR,
			"Directory bread(block %llu) failed", (llu)phys);
		/* skip this block */
		*pos = (iblock + 1) << sb->s_blocksize_bits;
		जाओ next;
	पूर्ण

	offset = *pos & (sb->s_blocksize - 1);
	*pos += माप(काष्ठा msकरोs_dir_entry);
	*de = (काष्ठा msकरोs_dir_entry *)((*bh)->b_data + offset);

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक fat_get_entry(काष्ठा inode *dir, loff_t *pos,
				काष्ठा buffer_head **bh,
				काष्ठा msकरोs_dir_entry **de)
अणु
	/* Fast stuff first */
	अगर (*bh && *de &&
	   (*de - (काष्ठा msकरोs_dir_entry *)(*bh)->b_data) <
				MSDOS_SB(dir->i_sb)->dir_per_block - 1) अणु
		*pos += माप(काष्ठा msकरोs_dir_entry);
		(*de)++;
		वापस 0;
	पूर्ण
	वापस fat__get_entry(dir, pos, bh, de);
पूर्ण

/*
 * Convert Unicode 16 to UTF-8, translated Unicode, or ASCII.
 * If uni_xlate is enabled and we can't get a 1:1 conversion, use a
 * colon as an escape अक्षरacter since it is normally invalid on the vfat
 * fileप्रणाली. The following four अक्षरacters are the hexadecimal digits
 * of Unicode value. This lets us करो a full dump and restore of Unicode
 * filenames. We could get पूर्णांकo some trouble with दीर्घ Unicode names,
 * but ignore that right now.
 * Ahem... Stack smashing in ring 0 isn't fun. Fixed.
 */
अटल पूर्णांक uni16_to_x8(काष्ठा super_block *sb, अचिन्हित अक्षर *ascii,
		       स्थिर ब_अक्षर_प्रकार *uni, पूर्णांक len, काष्ठा nls_table *nls)
अणु
	पूर्णांक uni_xlate = MSDOS_SB(sb)->options.unicode_xlate;
	स्थिर ब_अक्षर_प्रकार *ip;
	ब_अक्षर_प्रकार ec;
	अचिन्हित अक्षर *op;
	पूर्णांक अक्षरlen;

	ip = uni;
	op = ascii;

	जबतक (*ip && ((len - NLS_MAX_CHARSET_SIZE) > 0)) अणु
		ec = *ip++;
		अक्षरlen = nls->uni2अक्षर(ec, op, NLS_MAX_CHARSET_SIZE);
		अगर (अक्षरlen > 0) अणु
			op += अक्षरlen;
			len -= अक्षरlen;
		पूर्ण अन्यथा अणु
			अगर (uni_xlate == 1) अणु
				*op++ = ':';
				op = hex_byte_pack(op, ec >> 8);
				op = hex_byte_pack(op, ec);
				len -= 5;
			पूर्ण अन्यथा अणु
				*op++ = '?';
				len--;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (unlikely(*ip)) अणु
		fat_msg(sb, KERN_WARNING,
			"filename was truncated while converting.");
	पूर्ण

	*op = 0;
	वापस op - ascii;
पूर्ण

अटल अंतरभूत पूर्णांक fat_uni_to_x8(काष्ठा super_block *sb, स्थिर ब_अक्षर_प्रकार *uni,
				अचिन्हित अक्षर *buf, पूर्णांक size)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	अगर (sbi->options.utf8)
		वापस utf16s_to_utf8s(uni, FAT_MAX_UNI_CHARS,
				UTF16_HOST_ENDIAN, buf, size);
	अन्यथा
		वापस uni16_to_x8(sb, buf, uni, size, sbi->nls_io);
पूर्ण

अटल अंतरभूत पूर्णांक
fat_लघु2uni(काष्ठा nls_table *t, अचिन्हित अक्षर *c, पूर्णांक clen, ब_अक्षर_प्रकार *uni)
अणु
	पूर्णांक अक्षरlen;

	अक्षरlen = t->अक्षर2uni(c, clen, uni);
	अगर (अक्षरlen < 0) अणु
		*uni = 0x003f;	/* a question mark */
		अक्षरlen = 1;
	पूर्ण
	वापस अक्षरlen;
पूर्ण

अटल अंतरभूत पूर्णांक
fat_लघु2lower_uni(काष्ठा nls_table *t, अचिन्हित अक्षर *c,
		    पूर्णांक clen, ब_अक्षर_प्रकार *uni)
अणु
	पूर्णांक अक्षरlen;
	ब_अक्षर_प्रकार wc;

	अक्षरlen = t->अक्षर2uni(c, clen, &wc);
	अगर (अक्षरlen < 0) अणु
		*uni = 0x003f;	/* a question mark */
		अक्षरlen = 1;
	पूर्ण अन्यथा अगर (अक्षरlen <= 1) अणु
		अचिन्हित अक्षर nc = t->अक्षरset2lower[*c];

		अगर (!nc)
			nc = *c;

		अक्षरlen = t->अक्षर2uni(&nc, 1, uni);
		अगर (अक्षरlen < 0) अणु
			*uni = 0x003f;	/* a question mark */
			अक्षरlen = 1;
		पूर्ण
	पूर्ण अन्यथा
		*uni = wc;

	वापस अक्षरlen;
पूर्ण

अटल अंतरभूत पूर्णांक
fat_लघुname2uni(काष्ठा nls_table *nls, अचिन्हित अक्षर *buf, पूर्णांक buf_size,
		  ब_अक्षर_प्रकार *uni_buf, अचिन्हित लघु opt, पूर्णांक lower)
अणु
	पूर्णांक len = 0;

	अगर (opt & VFAT_SFN_DISPLAY_LOWER)
		len =  fat_लघु2lower_uni(nls, buf, buf_size, uni_buf);
	अन्यथा अगर (opt & VFAT_SFN_DISPLAY_WIN95)
		len = fat_लघु2uni(nls, buf, buf_size, uni_buf);
	अन्यथा अगर (opt & VFAT_SFN_DISPLAY_WINNT) अणु
		अगर (lower)
			len = fat_लघु2lower_uni(nls, buf, buf_size, uni_buf);
		अन्यथा
			len = fat_लघु2uni(nls, buf, buf_size, uni_buf);
	पूर्ण अन्यथा
		len = fat_लघु2uni(nls, buf, buf_size, uni_buf);

	वापस len;
पूर्ण

अटल अंतरभूत पूर्णांक fat_name_match(काष्ठा msकरोs_sb_info *sbi,
				 स्थिर अचिन्हित अक्षर *a, पूर्णांक a_len,
				 स्थिर अचिन्हित अक्षर *b, पूर्णांक b_len)
अणु
	अगर (a_len != b_len)
		वापस 0;

	अगर (sbi->options.name_check != 's')
		वापस !nls_strnicmp(sbi->nls_io, a, b, a_len);
	अन्यथा
		वापस !स_भेद(a, b, a_len);
पूर्ण

क्रमागत अणु PARSE_INVALID = 1, PARSE_NOT_LONGNAME, PARSE_खातापूर्ण, पूर्ण;

/**
 * fat_parse_दीर्घ - Parse extended directory entry.
 *
 * This function वापसs zero on success, negative value on error, or one of
 * the following:
 *
 * %PARSE_INVALID - Directory entry is invalid.
 * %PARSE_NOT_LONGNAME - Directory entry करोes not contain दीर्घname.
 * %PARSE_खातापूर्ण - Directory has no more entries.
 */
अटल पूर्णांक fat_parse_दीर्घ(काष्ठा inode *dir, loff_t *pos,
			  काष्ठा buffer_head **bh, काष्ठा msकरोs_dir_entry **de,
			  ब_अक्षर_प्रकार **unicode, अचिन्हित अक्षर *nr_slots)
अणु
	काष्ठा msकरोs_dir_slot *ds;
	अचिन्हित अक्षर id, slot, slots, alias_checksum;

	अगर (!*unicode) अणु
		*unicode = __getname();
		अगर (!*unicode) अणु
			brअन्यथा(*bh);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
parse_दीर्घ:
	ds = (काष्ठा msकरोs_dir_slot *)*de;
	id = ds->id;
	अगर (!(id & 0x40))
		वापस PARSE_INVALID;
	slots = id & ~0x40;
	अगर (slots > 20 || !slots)	/* उच्चमान(256 * 2 / 26) */
		वापस PARSE_INVALID;
	*nr_slots = slots;
	alias_checksum = ds->alias_checksum;

	slot = slots;
	जबतक (1) अणु
		पूर्णांक offset;

		slot--;
		offset = slot * 13;
		fat16_towअक्षर(*unicode + offset, ds->name0_4, 5);
		fat16_towअक्षर(*unicode + offset + 5, ds->name5_10, 6);
		fat16_towअक्षर(*unicode + offset + 11, ds->name11_12, 2);

		अगर (ds->id & 0x40)
			(*unicode)[offset + 13] = 0;
		अगर (fat_get_entry(dir, pos, bh, de) < 0)
			वापस PARSE_खातापूर्ण;
		अगर (slot == 0)
			अवरोध;
		ds = (काष्ठा msकरोs_dir_slot *)*de;
		अगर (ds->attr != ATTR_EXT)
			वापस PARSE_NOT_LONGNAME;
		अगर ((ds->id & ~0x40) != slot)
			जाओ parse_दीर्घ;
		अगर (ds->alias_checksum != alias_checksum)
			जाओ parse_दीर्घ;
	पूर्ण
	अगर ((*de)->name[0] == DELETED_FLAG)
		वापस PARSE_INVALID;
	अगर ((*de)->attr == ATTR_EXT)
		जाओ parse_दीर्घ;
	अगर (IS_FREE((*de)->name) || ((*de)->attr & ATTR_VOLUME))
		वापस PARSE_INVALID;
	अगर (fat_checksum((*de)->name) != alias_checksum)
		*nr_slots = 0;

	वापस 0;
पूर्ण

/**
 * fat_parse_लघु - Parse MS-DOS (लघु) directory entry.
 * @sb:		superblock
 * @de:		directory entry to parse
 * @name:	FAT_MAX_SHORT_SIZE array in which to place extracted name
 * @करोt_hidden:	Nonzero == prepend '.' to names with ATTR_HIDDEN
 *
 * Returns the number of अक्षरacters extracted पूर्णांकo 'name'.
 */
अटल पूर्णांक fat_parse_लघु(काष्ठा super_block *sb,
			   स्थिर काष्ठा msकरोs_dir_entry *de,
			   अचिन्हित अक्षर *name, पूर्णांक करोt_hidden)
अणु
	स्थिर काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	पूर्णांक isvfat = sbi->options.isvfat;
	पूर्णांक noहाल = sbi->options.noहाल;
	अचिन्हित लघु opt_लघुname = sbi->options.लघुname;
	काष्ठा nls_table *nls_disk = sbi->nls_disk;
	ब_अक्षर_प्रकार uni_name[14];
	अचिन्हित अक्षर c, work[MSDOS_NAME];
	अचिन्हित अक्षर *ptname = name;
	पूर्णांक chi, chl, i, j, k;
	पूर्णांक करोtoffset = 0;
	पूर्णांक name_len = 0, uni_len = 0;

	अगर (!isvfat && करोt_hidden && (de->attr & ATTR_HIDDEN)) अणु
		*ptname++ = '.';
		करोtoffset = 1;
	पूर्ण

	स_नकल(work, de->name, माप(work));
	/* For an explanation of the special treaपंचांगent of 0x05 in
	 * filenames, see msकरोs_क्रमmat_name in namei_msकरोs.c
	 */
	अगर (work[0] == 0x05)
		work[0] = 0xE5;

	/* Filename */
	क्रम (i = 0, j = 0; i < 8;) अणु
		c = work[i];
		अगर (!c)
			अवरोध;
		chl = fat_लघुname2uni(nls_disk, &work[i], 8 - i,
					&uni_name[j++], opt_लघुname,
					de->lहाल & CASE_LOWER_BASE);
		अगर (chl <= 1) अणु
			अगर (!isvfat)
				ptname[i] = noहाल ? c : fat_छोटे(c);
			i++;
			अगर (c != ' ') अणु
				name_len = i;
				uni_len  = j;
			पूर्ण
		पूर्ण अन्यथा अणु
			uni_len = j;
			अगर (isvfat)
				i += min(chl, 8-i);
			अन्यथा अणु
				क्रम (chi = 0; chi < chl && i < 8; chi++, i++)
					ptname[i] = work[i];
			पूर्ण
			अगर (chl)
				name_len = i;
		पूर्ण
	पूर्ण

	i = name_len;
	j = uni_len;
	fat_लघु2uni(nls_disk, ".", 1, &uni_name[j++]);
	अगर (!isvfat)
		ptname[i] = '.';
	i++;

	/* Extension */
	क्रम (k = 8; k < MSDOS_NAME;) अणु
		c = work[k];
		अगर (!c)
			अवरोध;
		chl = fat_लघुname2uni(nls_disk, &work[k], MSDOS_NAME - k,
					&uni_name[j++], opt_लघुname,
					de->lहाल & CASE_LOWER_EXT);
		अगर (chl <= 1) अणु
			k++;
			अगर (!isvfat)
				ptname[i] = noहाल ? c : fat_छोटे(c);
			i++;
			अगर (c != ' ') अणु
				name_len = i;
				uni_len  = j;
			पूर्ण
		पूर्ण अन्यथा अणु
			uni_len = j;
			अगर (isvfat) अणु
				पूर्णांक offset = min(chl, MSDOS_NAME-k);
				k += offset;
				i += offset;
			पूर्ण अन्यथा अणु
				क्रम (chi = 0; chi < chl && k < MSDOS_NAME;
				     chi++, i++, k++) अणु
						ptname[i] = work[k];
				पूर्ण
			पूर्ण
			अगर (chl)
				name_len = i;
		पूर्ण
	पूर्ण

	अगर (name_len > 0) अणु
		name_len += करोtoffset;

		अगर (sbi->options.isvfat) अणु
			uni_name[uni_len] = 0x0000;
			name_len = fat_uni_to_x8(sb, uni_name, name,
						 FAT_MAX_SHORT_SIZE);
		पूर्ण
	पूर्ण

	वापस name_len;
पूर्ण

/*
 * Return values: negative -> error/not found, 0 -> found.
 */
पूर्णांक fat_search_दीर्घ(काष्ठा inode *inode, स्थिर अचिन्हित अक्षर *name,
		    पूर्णांक name_len, काष्ठा fat_slot_info *sinfo)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	काष्ठा buffer_head *bh = शून्य;
	काष्ठा msकरोs_dir_entry *de;
	अचिन्हित अक्षर nr_slots;
	ब_अक्षर_प्रकार *unicode = शून्य;
	अचिन्हित अक्षर bufname[FAT_MAX_SHORT_SIZE];
	loff_t cpos = 0;
	पूर्णांक err, len;

	err = -ENOENT;
	जबतक (1) अणु
		अगर (fat_get_entry(inode, &cpos, &bh, &de) == -1)
			जाओ end_of_dir;
parse_record:
		nr_slots = 0;
		अगर (de->name[0] == DELETED_FLAG)
			जारी;
		अगर (de->attr != ATTR_EXT && (de->attr & ATTR_VOLUME))
			जारी;
		अगर (de->attr != ATTR_EXT && IS_FREE(de->name))
			जारी;
		अगर (de->attr == ATTR_EXT) अणु
			पूर्णांक status = fat_parse_दीर्घ(inode, &cpos, &bh, &de,
						    &unicode, &nr_slots);
			अगर (status < 0) अणु
				err = status;
				जाओ end_of_dir;
			पूर्ण अन्यथा अगर (status == PARSE_INVALID)
				जारी;
			अन्यथा अगर (status == PARSE_NOT_LONGNAME)
				जाओ parse_record;
			अन्यथा अगर (status == PARSE_खातापूर्ण)
				जाओ end_of_dir;
		पूर्ण

		/* Never prepend '.' to hidden files here.
		 * That is करोne only क्रम msकरोs mounts (and only when
		 * 'dotsOK=yes'); अगर we are executing here, it is in the
		 * context of a vfat mount.
		 */
		len = fat_parse_लघु(sb, de, bufname, 0);
		अगर (len == 0)
			जारी;

		/* Compare लघुname */
		अगर (fat_name_match(sbi, name, name_len, bufname, len))
			जाओ found;

		अगर (nr_slots) अणु
			व्योम *दीर्घname = unicode + FAT_MAX_UNI_CHARS;
			पूर्णांक size = PATH_MAX - FAT_MAX_UNI_SIZE;

			/* Compare दीर्घname */
			len = fat_uni_to_x8(sb, unicode, दीर्घname, size);
			अगर (fat_name_match(sbi, name, name_len, दीर्घname, len))
				जाओ found;
		पूर्ण
	पूर्ण

found:
	nr_slots++;	/* include the de */
	sinfo->slot_off = cpos - nr_slots * माप(*de);
	sinfo->nr_slots = nr_slots;
	sinfo->de = de;
	sinfo->bh = bh;
	sinfo->i_pos = fat_make_i_pos(sb, sinfo->bh, sinfo->de);
	err = 0;
end_of_dir:
	अगर (unicode)
		__putname(unicode);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fat_search_दीर्घ);

काष्ठा fat_ioctl_filldir_callback अणु
	काष्ठा dir_context ctx;
	व्योम __user *dirent;
	पूर्णांक result;
	/* क्रम dir ioctl */
	स्थिर अक्षर *दीर्घname;
	पूर्णांक दीर्घ_len;
	स्थिर अक्षर *लघुname;
	पूर्णांक लघु_len;
पूर्ण;

अटल पूर्णांक __fat_सूची_पढ़ो(काष्ठा inode *inode, काष्ठा file *file,
			 काष्ठा dir_context *ctx, पूर्णांक लघु_only,
			 काष्ठा fat_ioctl_filldir_callback *both)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	काष्ठा buffer_head *bh;
	काष्ठा msकरोs_dir_entry *de;
	अचिन्हित अक्षर nr_slots;
	ब_अक्षर_प्रकार *unicode = शून्य;
	अचिन्हित अक्षर bufname[FAT_MAX_SHORT_SIZE];
	पूर्णांक isvfat = sbi->options.isvfat;
	स्थिर अक्षर *fill_name = शून्य;
	पूर्णांक fake_offset = 0;
	loff_t cpos;
	पूर्णांक लघु_len = 0, fill_len = 0;
	पूर्णांक ret = 0;

	mutex_lock(&sbi->s_lock);

	cpos = ctx->pos;
	/* Fake . and .. क्रम the root directory. */
	अगर (inode->i_ino == MSDOS_ROOT_INO) अणु
		अगर (!dir_emit_करोts(file, ctx))
			जाओ out;
		अगर (ctx->pos == 2) अणु
			fake_offset = 1;
			cpos = 0;
		पूर्ण
	पूर्ण
	अगर (cpos & (माप(काष्ठा msकरोs_dir_entry) - 1)) अणु
		ret = -ENOENT;
		जाओ out;
	पूर्ण

	bh = शून्य;
get_new:
	अगर (fat_get_entry(inode, &cpos, &bh, &de) == -1)
		जाओ end_of_dir;
parse_record:
	nr_slots = 0;
	/*
	 * Check क्रम दीर्घ filename entry, but अगर लघु_only, we करोn't
	 * need to parse दीर्घ filename.
	 */
	अगर (isvfat && !लघु_only) अणु
		अगर (de->name[0] == DELETED_FLAG)
			जाओ record_end;
		अगर (de->attr != ATTR_EXT && (de->attr & ATTR_VOLUME))
			जाओ record_end;
		अगर (de->attr != ATTR_EXT && IS_FREE(de->name))
			जाओ record_end;
	पूर्ण अन्यथा अणु
		अगर ((de->attr & ATTR_VOLUME) || IS_FREE(de->name))
			जाओ record_end;
	पूर्ण

	अगर (isvfat && de->attr == ATTR_EXT) अणु
		पूर्णांक status = fat_parse_दीर्घ(inode, &cpos, &bh, &de,
					    &unicode, &nr_slots);
		अगर (status < 0) अणु
			bh = शून्य;
			ret = status;
			जाओ end_of_dir;
		पूर्ण अन्यथा अगर (status == PARSE_INVALID)
			जाओ record_end;
		अन्यथा अगर (status == PARSE_NOT_LONGNAME)
			जाओ parse_record;
		अन्यथा अगर (status == PARSE_खातापूर्ण)
			जाओ end_of_dir;

		अगर (nr_slots) अणु
			व्योम *दीर्घname = unicode + FAT_MAX_UNI_CHARS;
			पूर्णांक size = PATH_MAX - FAT_MAX_UNI_SIZE;
			पूर्णांक len = fat_uni_to_x8(sb, unicode, दीर्घname, size);

			fill_name = दीर्घname;
			fill_len = len;
			/* !both && !लघु_only, so we करोn't need लघुname. */
			अगर (!both)
				जाओ start_filldir;

			लघु_len = fat_parse_लघु(sb, de, bufname,
						    sbi->options.करोtsOK);
			अगर (लघु_len == 0)
				जाओ record_end;
			/* hack क्रम fat_ioctl_filldir() */
			both->दीर्घname = fill_name;
			both->दीर्घ_len = fill_len;
			both->लघुname = bufname;
			both->लघु_len = लघु_len;
			fill_name = शून्य;
			fill_len = 0;
			जाओ start_filldir;
		पूर्ण
	पूर्ण

	लघु_len = fat_parse_लघु(sb, de, bufname, sbi->options.करोtsOK);
	अगर (लघु_len == 0)
		जाओ record_end;

	fill_name = bufname;
	fill_len = लघु_len;

start_filldir:
	ctx->pos = cpos - (nr_slots + 1) * माप(काष्ठा msकरोs_dir_entry);
	अगर (fake_offset && ctx->pos < 2)
		ctx->pos = 2;

	अगर (!स_भेद(de->name, MSDOS_DOT, MSDOS_NAME)) अणु
		अगर (!dir_emit_करोt(file, ctx))
			जाओ fill_failed;
	पूर्ण अन्यथा अगर (!स_भेद(de->name, MSDOS_DOTDOT, MSDOS_NAME)) अणु
		अगर (!dir_emit_करोtकरोt(file, ctx))
			जाओ fill_failed;
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ inum;
		loff_t i_pos = fat_make_i_pos(sb, bh, de);
		काष्ठा inode *पंचांगp = fat_iget(sb, i_pos);
		अगर (पंचांगp) अणु
			inum = पंचांगp->i_ino;
			iput(पंचांगp);
		पूर्ण अन्यथा
			inum = iunique(sb, MSDOS_ROOT_INO);
		अगर (!dir_emit(ctx, fill_name, fill_len, inum,
			    (de->attr & ATTR_सूची) ? DT_सूची : DT_REG))
			जाओ fill_failed;
	पूर्ण

record_end:
	fake_offset = 0;
	ctx->pos = cpos;
	जाओ get_new;

end_of_dir:
	अगर (fake_offset && cpos < 2)
		ctx->pos = 2;
	अन्यथा
		ctx->pos = cpos;
fill_failed:
	brअन्यथा(bh);
	अगर (unicode)
		__putname(unicode);
out:
	mutex_unlock(&sbi->s_lock);

	वापस ret;
पूर्ण

अटल पूर्णांक fat_सूची_पढ़ो(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	वापस __fat_सूची_पढ़ो(file_inode(file), file, ctx, 0, शून्य);
पूर्ण

#घोषणा FAT_IOCTL_FILLसूची_FUNC(func, dirent_type)			   \
अटल पूर्णांक func(काष्ठा dir_context *ctx, स्थिर अक्षर *name, पूर्णांक name_len,   \
			     loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type)  \
अणु									   \
	काष्ठा fat_ioctl_filldir_callback *buf =			   \
		container_of(ctx, काष्ठा fat_ioctl_filldir_callback, ctx); \
	काष्ठा dirent_type __user *d1 = buf->dirent;			   \
	काष्ठा dirent_type __user *d2 = d1 + 1;				   \
									   \
	अगर (buf->result)						   \
		वापस -EINVAL;						   \
	buf->result++;							   \
									   \
	अगर (name != शून्य) अणु						   \
		/* dirent has only लघु name */			   \
		अगर (name_len >= माप(d1->d_name))			   \
			name_len = माप(d1->d_name) - 1;		   \
									   \
		अगर (put_user(0, d2->d_name)			||	   \
		    put_user(0, &d2->d_reclen)			||	   \
		    copy_to_user(d1->d_name, name, name_len)	||	   \
		    put_user(0, d1->d_name + name_len)		||	   \
		    put_user(name_len, &d1->d_reclen))			   \
			जाओ efault;					   \
	पूर्ण अन्यथा अणु							   \
		/* dirent has लघु and दीर्घ name */			   \
		स्थिर अक्षर *दीर्घname = buf->दीर्घname;			   \
		पूर्णांक दीर्घ_len = buf->दीर्घ_len;				   \
		स्थिर अक्षर *लघुname = buf->लघुname;			   \
		पूर्णांक लघु_len = buf->लघु_len;				   \
									   \
		अगर (दीर्घ_len >= माप(d1->d_name))			   \
			दीर्घ_len = माप(d1->d_name) - 1;		   \
		अगर (लघु_len >= माप(d1->d_name))			   \
			लघु_len = माप(d1->d_name) - 1;		   \
									   \
		अगर (copy_to_user(d2->d_name, दीर्घname, दीर्घ_len)	|| \
		    put_user(0, d2->d_name + दीर्घ_len)			|| \
		    put_user(दीर्घ_len, &d2->d_reclen)			|| \
		    put_user(ino, &d2->d_ino)				|| \
		    put_user(offset, &d2->d_off)			|| \
		    copy_to_user(d1->d_name, लघुname, लघु_len)	|| \
		    put_user(0, d1->d_name + लघु_len)			|| \
		    put_user(लघु_len, &d1->d_reclen))			   \
			जाओ efault;					   \
	पूर्ण								   \
	वापस 0;							   \
efault:									   \
	buf->result = -EFAULT;						   \
	वापस -EFAULT;							   \
पूर्ण

FAT_IOCTL_FILLसूची_FUNC(fat_ioctl_filldir, __fat_dirent)

अटल पूर्णांक fat_ioctl_सूची_पढ़ो(काष्ठा inode *inode, काष्ठा file *file,
			     व्योम __user *dirent, filldir_t filldir,
			     पूर्णांक लघु_only, पूर्णांक both)
अणु
	काष्ठा fat_ioctl_filldir_callback buf = अणु
		.ctx.actor = filldir,
		.dirent = dirent
	पूर्ण;
	पूर्णांक ret;

	buf.dirent = dirent;
	buf.result = 0;
	inode_lock_shared(inode);
	buf.ctx.pos = file->f_pos;
	ret = -ENOENT;
	अगर (!IS_DEADसूची(inode)) अणु
		ret = __fat_सूची_पढ़ो(inode, file, &buf.ctx,
				    लघु_only, both ? &buf : शून्य);
		file->f_pos = buf.ctx.pos;
	पूर्ण
	inode_unlock_shared(inode);
	अगर (ret >= 0)
		ret = buf.result;
	वापस ret;
पूर्ण

अटल दीर्घ fat_dir_ioctl(काष्ठा file *filp, अचिन्हित पूर्णांक cmd,
			  अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा __fat_dirent __user *d1 = (काष्ठा __fat_dirent __user *)arg;
	पूर्णांक लघु_only, both;

	चयन (cmd) अणु
	हाल VFAT_IOCTL_READसूची_SHORT:
		लघु_only = 1;
		both = 0;
		अवरोध;
	हाल VFAT_IOCTL_READसूची_BOTH:
		लघु_only = 0;
		both = 1;
		अवरोध;
	शेष:
		वापस fat_generic_ioctl(filp, cmd, arg);
	पूर्ण

	/*
	 * Yes, we करोn't need this put_user() असलolutely. However old
	 * code didn't वापस the right value. So, app use this value,
	 * in order to check whether it is खातापूर्ण.
	 */
	अगर (put_user(0, &d1->d_reclen))
		वापस -EFAULT;

	वापस fat_ioctl_सूची_पढ़ो(inode, filp, d1, fat_ioctl_filldir,
				 लघु_only, both);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
#घोषणा	VFAT_IOCTL_READसूची_BOTH32	_IOR('r', 1, काष्ठा compat_dirent[2])
#घोषणा	VFAT_IOCTL_READसूची_SHORT32	_IOR('r', 2, काष्ठा compat_dirent[2])

FAT_IOCTL_FILLसूची_FUNC(fat_compat_ioctl_filldir, compat_dirent)

अटल दीर्घ fat_compat_dir_ioctl(काष्ठा file *filp, अचिन्हित cmd,
				 अचिन्हित दीर्घ arg)
अणु
	काष्ठा inode *inode = file_inode(filp);
	काष्ठा compat_dirent __user *d1 = compat_ptr(arg);
	पूर्णांक लघु_only, both;

	चयन (cmd) अणु
	हाल VFAT_IOCTL_READसूची_SHORT32:
		लघु_only = 1;
		both = 0;
		अवरोध;
	हाल VFAT_IOCTL_READसूची_BOTH32:
		लघु_only = 0;
		both = 1;
		अवरोध;
	शेष:
		वापस fat_generic_ioctl(filp, cmd, (अचिन्हित दीर्घ)arg);
	पूर्ण

	/*
	 * Yes, we करोn't need this put_user() असलolutely. However old
	 * code didn't वापस the right value. So, app use this value,
	 * in order to check whether it is खातापूर्ण.
	 */
	अगर (put_user(0, &d1->d_reclen))
		वापस -EFAULT;

	वापस fat_ioctl_सूची_पढ़ो(inode, filp, d1, fat_compat_ioctl_filldir,
				 लघु_only, both);
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

स्थिर काष्ठा file_operations fat_dir_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate_shared	= fat_सूची_पढ़ो,
	.unlocked_ioctl	= fat_dir_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= fat_compat_dir_ioctl,
#पूर्ण_अगर
	.fsync		= fat_file_fsync,
पूर्ण;

अटल पूर्णांक fat_get_लघु_entry(काष्ठा inode *dir, loff_t *pos,
			       काष्ठा buffer_head **bh,
			       काष्ठा msकरोs_dir_entry **de)
अणु
	जबतक (fat_get_entry(dir, pos, bh, de) >= 0) अणु
		/* मुक्त entry or दीर्घ name entry or volume label */
		अगर (!IS_FREE((*de)->name) && !((*de)->attr & ATTR_VOLUME))
			वापस 0;
	पूर्ण
	वापस -ENOENT;
पूर्ण

/*
 * The ".." entry can not provide the "struct fat_slot_info" inक्रमmation
 * क्रम inode, nor a usable i_pos. So, this function provides some inक्रमmation
 * only.
 *
 * Since this function walks through the on-disk inodes within a directory,
 * callers are responsible क्रम taking any locks necessary to prevent the
 * directory from changing.
 */
पूर्णांक fat_get_करोtकरोt_entry(काष्ठा inode *dir, काष्ठा buffer_head **bh,
			 काष्ठा msकरोs_dir_entry **de)
अणु
	loff_t offset = 0;

	*de = शून्य;
	जबतक (fat_get_लघु_entry(dir, &offset, bh, de) >= 0) अणु
		अगर (!म_भेदन((*de)->name, MSDOS_DOTDOT, MSDOS_NAME))
			वापस 0;
	पूर्ण
	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL_GPL(fat_get_करोtकरोt_entry);

/* See अगर directory is empty */
पूर्णांक fat_dir_empty(काष्ठा inode *dir)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा msकरोs_dir_entry *de;
	loff_t cpos;
	पूर्णांक result = 0;

	bh = शून्य;
	cpos = 0;
	जबतक (fat_get_लघु_entry(dir, &cpos, &bh, &de) >= 0) अणु
		अगर (म_भेदन(de->name, MSDOS_DOT   , MSDOS_NAME) &&
		    म_भेदन(de->name, MSDOS_DOTDOT, MSDOS_NAME)) अणु
			result = -ENOTEMPTY;
			अवरोध;
		पूर्ण
	पूर्ण
	brअन्यथा(bh);
	वापस result;
पूर्ण
EXPORT_SYMBOL_GPL(fat_dir_empty);

/*
 * fat_subdirs counts the number of sub-directories of dir. It can be run
 * on directories being created.
 */
पूर्णांक fat_subdirs(काष्ठा inode *dir)
अणु
	काष्ठा buffer_head *bh;
	काष्ठा msकरोs_dir_entry *de;
	loff_t cpos;
	पूर्णांक count = 0;

	bh = शून्य;
	cpos = 0;
	जबतक (fat_get_लघु_entry(dir, &cpos, &bh, &de) >= 0) अणु
		अगर (de->attr & ATTR_सूची)
			count++;
	पूर्ण
	brअन्यथा(bh);
	वापस count;
पूर्ण

/*
 * Scans a directory क्रम a given file (name poपूर्णांकs to its क्रमmatted name).
 * Returns an error code or zero.
 */
पूर्णांक fat_scan(काष्ठा inode *dir, स्थिर अचिन्हित अक्षर *name,
	     काष्ठा fat_slot_info *sinfo)
अणु
	काष्ठा super_block *sb = dir->i_sb;

	sinfo->slot_off = 0;
	sinfo->bh = शून्य;
	जबतक (fat_get_लघु_entry(dir, &sinfo->slot_off, &sinfo->bh,
				   &sinfo->de) >= 0) अणु
		अगर (!म_भेदन(sinfo->de->name, name, MSDOS_NAME)) अणु
			sinfo->slot_off -= माप(*sinfo->de);
			sinfo->nr_slots = 1;
			sinfo->i_pos = fat_make_i_pos(sb, sinfo->bh, sinfo->de);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण
EXPORT_SYMBOL_GPL(fat_scan);

/*
 * Scans a directory क्रम a given logstart.
 * Returns an error code or zero.
 */
पूर्णांक fat_scan_logstart(काष्ठा inode *dir, पूर्णांक i_logstart,
		      काष्ठा fat_slot_info *sinfo)
अणु
	काष्ठा super_block *sb = dir->i_sb;

	sinfo->slot_off = 0;
	sinfo->bh = शून्य;
	जबतक (fat_get_लघु_entry(dir, &sinfo->slot_off, &sinfo->bh,
				   &sinfo->de) >= 0) अणु
		अगर (fat_get_start(MSDOS_SB(sb), sinfo->de) == i_logstart) अणु
			sinfo->slot_off -= माप(*sinfo->de);
			sinfo->nr_slots = 1;
			sinfo->i_pos = fat_make_i_pos(sb, sinfo->bh, sinfo->de);
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक __fat_हटाओ_entries(काष्ठा inode *dir, loff_t pos, पूर्णांक nr_slots)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा buffer_head *bh;
	काष्ठा msकरोs_dir_entry *de, *endp;
	पूर्णांक err = 0, orig_slots;

	जबतक (nr_slots) अणु
		bh = शून्य;
		अगर (fat_get_entry(dir, &pos, &bh, &de) < 0) अणु
			err = -EIO;
			अवरोध;
		पूर्ण

		orig_slots = nr_slots;
		endp = (काष्ठा msकरोs_dir_entry *)(bh->b_data + sb->s_blocksize);
		जबतक (nr_slots && de < endp) अणु
			de->name[0] = DELETED_FLAG;
			de++;
			nr_slots--;
		पूर्ण
		mark_buffer_dirty_inode(bh, dir);
		अगर (IS_सूचीSYNC(dir))
			err = sync_dirty_buffer(bh);
		brअन्यथा(bh);
		अगर (err)
			अवरोध;

		/* pos is *next* de's position, so this does `- sizeof(de)' */
		pos += ((orig_slots - nr_slots) * माप(*de)) - माप(*de);
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक fat_हटाओ_entries(काष्ठा inode *dir, काष्ठा fat_slot_info *sinfo)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा msकरोs_dir_entry *de;
	काष्ठा buffer_head *bh;
	पूर्णांक err = 0, nr_slots;

	/*
	 * First stage: Remove the लघुname. By this, the directory
	 * entry is हटाओd.
	 */
	nr_slots = sinfo->nr_slots;
	de = sinfo->de;
	sinfo->de = शून्य;
	bh = sinfo->bh;
	sinfo->bh = शून्य;
	जबतक (nr_slots && de >= (काष्ठा msकरोs_dir_entry *)bh->b_data) अणु
		de->name[0] = DELETED_FLAG;
		de--;
		nr_slots--;
	पूर्ण
	mark_buffer_dirty_inode(bh, dir);
	अगर (IS_सूचीSYNC(dir))
		err = sync_dirty_buffer(bh);
	brअन्यथा(bh);
	अगर (err)
		वापस err;
	inode_inc_iversion(dir);

	अगर (nr_slots) अणु
		/*
		 * Second stage: हटाओ the reमुख्यing दीर्घname slots.
		 * (This directory entry is alपढ़ोy हटाओd, and so वापस
		 * the success)
		 */
		err = __fat_हटाओ_entries(dir, sinfo->slot_off, nr_slots);
		अगर (err) अणु
			fat_msg(sb, KERN_WARNING,
			       "Couldn't remove the long name slots");
		पूर्ण
	पूर्ण

	fat_truncate_समय(dir, शून्य, S_ATIME|S_MTIME);
	अगर (IS_सूचीSYNC(dir))
		(व्योम)fat_sync_inode(dir);
	अन्यथा
		mark_inode_dirty(dir);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(fat_हटाओ_entries);

अटल पूर्णांक fat_zeroed_cluster(काष्ठा inode *dir, sector_t blknr, पूर्णांक nr_used,
			      काष्ठा buffer_head **bhs, पूर्णांक nr_bhs)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	sector_t last_blknr = blknr + MSDOS_SB(sb)->sec_per_clus;
	पूर्णांक err, i, n;

	/* Zeroing the unused blocks on this cluster */
	blknr += nr_used;
	n = nr_used;
	जबतक (blknr < last_blknr) अणु
		bhs[n] = sb_getblk(sb, blknr);
		अगर (!bhs[n]) अणु
			err = -ENOMEM;
			जाओ error;
		पूर्ण
		/* Aव्योम race with userspace पढ़ो via bdev */
		lock_buffer(bhs[n]);
		स_रखो(bhs[n]->b_data, 0, sb->s_blocksize);
		set_buffer_uptodate(bhs[n]);
		unlock_buffer(bhs[n]);
		mark_buffer_dirty_inode(bhs[n], dir);

		n++;
		blknr++;
		अगर (n == nr_bhs) अणु
			अगर (IS_सूचीSYNC(dir)) अणु
				err = fat_sync_bhs(bhs, n);
				अगर (err)
					जाओ error;
			पूर्ण
			क्रम (i = 0; i < n; i++)
				brअन्यथा(bhs[i]);
			n = 0;
		पूर्ण
	पूर्ण
	अगर (IS_सूचीSYNC(dir)) अणु
		err = fat_sync_bhs(bhs, n);
		अगर (err)
			जाओ error;
	पूर्ण
	क्रम (i = 0; i < n; i++)
		brअन्यथा(bhs[i]);

	वापस 0;

error:
	क्रम (i = 0; i < n; i++)
		bक्रमget(bhs[i]);
	वापस err;
पूर्ण

पूर्णांक fat_alloc_new_dir(काष्ठा inode *dir, काष्ठा बारpec64 *ts)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	काष्ठा buffer_head *bhs[MAX_BUF_PER_PAGE];
	काष्ठा msकरोs_dir_entry *de;
	sector_t blknr;
	__le16 date, समय;
	u8 समय_cs;
	पूर्णांक err, cluster;

	err = fat_alloc_clusters(dir, &cluster, 1);
	अगर (err)
		जाओ error;

	blknr = fat_clus_to_blknr(sbi, cluster);
	bhs[0] = sb_getblk(sb, blknr);
	अगर (!bhs[0]) अणु
		err = -ENOMEM;
		जाओ error_मुक्त;
	पूर्ण

	fat_समय_unix2fat(sbi, ts, &समय, &date, &समय_cs);

	de = (काष्ठा msकरोs_dir_entry *)bhs[0]->b_data;
	/* Aव्योम race with userspace पढ़ो via bdev */
	lock_buffer(bhs[0]);
	/* filling the new directory slots ("." and ".." entries) */
	स_नकल(de[0].name, MSDOS_DOT, MSDOS_NAME);
	स_नकल(de[1].name, MSDOS_DOTDOT, MSDOS_NAME);
	de->attr = de[1].attr = ATTR_सूची;
	de[0].lहाल = de[1].lहाल = 0;
	de[0].समय = de[1].समय = समय;
	de[0].date = de[1].date = date;
	अगर (sbi->options.isvfat) अणु
		/* extra बारtamps */
		de[0].स_समय = de[1].स_समय = समय;
		de[0].स_समय_cs = de[1].स_समय_cs = समय_cs;
		de[0].adate = de[0].cdate = de[1].adate = de[1].cdate = date;
	पूर्ण अन्यथा अणु
		de[0].स_समय = de[1].स_समय = 0;
		de[0].स_समय_cs = de[1].स_समय_cs = 0;
		de[0].adate = de[0].cdate = de[1].adate = de[1].cdate = 0;
	पूर्ण
	fat_set_start(&de[0], cluster);
	fat_set_start(&de[1], MSDOS_I(dir)->i_logstart);
	de[0].size = de[1].size = 0;
	स_रखो(de + 2, 0, sb->s_blocksize - 2 * माप(*de));
	set_buffer_uptodate(bhs[0]);
	unlock_buffer(bhs[0]);
	mark_buffer_dirty_inode(bhs[0], dir);

	err = fat_zeroed_cluster(dir, blknr, 1, bhs, MAX_BUF_PER_PAGE);
	अगर (err)
		जाओ error_मुक्त;

	वापस cluster;

error_मुक्त:
	fat_मुक्त_clusters(dir, cluster);
error:
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fat_alloc_new_dir);

अटल पूर्णांक fat_add_new_entries(काष्ठा inode *dir, व्योम *slots, पूर्णांक nr_slots,
			       पूर्णांक *nr_cluster, काष्ठा msकरोs_dir_entry **de,
			       काष्ठा buffer_head **bh, loff_t *i_pos)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	काष्ठा buffer_head *bhs[MAX_BUF_PER_PAGE];
	sector_t blknr, start_blknr, last_blknr;
	अचिन्हित दीर्घ size, copy;
	पूर्णांक err, i, n, offset, cluster[2];

	/*
	 * The minimum cluster size is 512bytes, and maximum entry
	 * size is 32*slots (672bytes).  So, अगरf the cluster size is
	 * 512bytes, we may need two clusters.
	 */
	size = nr_slots * माप(काष्ठा msकरोs_dir_entry);
	*nr_cluster = (size + (sbi->cluster_size - 1)) >> sbi->cluster_bits;
	BUG_ON(*nr_cluster > 2);

	err = fat_alloc_clusters(dir, cluster, *nr_cluster);
	अगर (err)
		जाओ error;

	/*
	 * First stage: Fill the directory entry.  NOTE: This cluster
	 * is not referenced from any inode yet, so updates order is
	 * not important.
	 */
	i = n = copy = 0;
	करो अणु
		start_blknr = blknr = fat_clus_to_blknr(sbi, cluster[i]);
		last_blknr = start_blknr + sbi->sec_per_clus;
		जबतक (blknr < last_blknr) अणु
			bhs[n] = sb_getblk(sb, blknr);
			अगर (!bhs[n]) अणु
				err = -ENOMEM;
				जाओ error_nomem;
			पूर्ण

			/* fill the directory entry */
			copy = min(size, sb->s_blocksize);
			/* Aव्योम race with userspace पढ़ो via bdev */
			lock_buffer(bhs[n]);
			स_नकल(bhs[n]->b_data, slots, copy);
			set_buffer_uptodate(bhs[n]);
			unlock_buffer(bhs[n]);
			mark_buffer_dirty_inode(bhs[n], dir);
			slots += copy;
			size -= copy;
			अगर (!size)
				अवरोध;
			n++;
			blknr++;
		पूर्ण
	पूर्ण जबतक (++i < *nr_cluster);

	स_रखो(bhs[n]->b_data + copy, 0, sb->s_blocksize - copy);
	offset = copy - माप(काष्ठा msकरोs_dir_entry);
	get_bh(bhs[n]);
	*bh = bhs[n];
	*de = (काष्ठा msकरोs_dir_entry *)((*bh)->b_data + offset);
	*i_pos = fat_make_i_pos(sb, *bh, *de);

	/* Second stage: clear the rest of cluster, and ग_लिखो outs */
	err = fat_zeroed_cluster(dir, start_blknr, ++n, bhs, MAX_BUF_PER_PAGE);
	अगर (err)
		जाओ error_मुक्त;

	वापस cluster[0];

error_मुक्त:
	brअन्यथा(*bh);
	*bh = शून्य;
	n = 0;
error_nomem:
	क्रम (i = 0; i < n; i++)
		bक्रमget(bhs[i]);
	fat_मुक्त_clusters(dir, cluster[0]);
error:
	वापस err;
पूर्ण

पूर्णांक fat_add_entries(काष्ठा inode *dir, व्योम *slots, पूर्णांक nr_slots,
		    काष्ठा fat_slot_info *sinfo)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(sb);
	काष्ठा buffer_head *bh, *prev, *bhs[3]; /* 32*slots (672bytes) */
	काष्ठा msकरोs_dir_entry *de;
	पूर्णांक err, मुक्त_slots, i, nr_bhs;
	loff_t pos, i_pos;

	sinfo->nr_slots = nr_slots;

	/* First stage: search मुक्त directory entries */
	मुक्त_slots = nr_bhs = 0;
	bh = prev = शून्य;
	pos = 0;
	err = -ENOSPC;
	जबतक (fat_get_entry(dir, &pos, &bh, &de) > -1) अणु
		/* check the maximum size of directory */
		अगर (pos >= FAT_MAX_सूची_SIZE)
			जाओ error;

		अगर (IS_FREE(de->name)) अणु
			अगर (prev != bh) अणु
				get_bh(bh);
				bhs[nr_bhs] = prev = bh;
				nr_bhs++;
			पूर्ण
			मुक्त_slots++;
			अगर (मुक्त_slots == nr_slots)
				जाओ found;
		पूर्ण अन्यथा अणु
			क्रम (i = 0; i < nr_bhs; i++)
				brअन्यथा(bhs[i]);
			prev = शून्य;
			मुक्त_slots = nr_bhs = 0;
		पूर्ण
	पूर्ण
	अगर (dir->i_ino == MSDOS_ROOT_INO) अणु
		अगर (!is_fat32(sbi))
			जाओ error;
	पूर्ण अन्यथा अगर (MSDOS_I(dir)->i_start == 0) अणु
		fat_msg(sb, KERN_ERR, "Corrupted directory (i_pos %lld)",
		       MSDOS_I(dir)->i_pos);
		err = -EIO;
		जाओ error;
	पूर्ण

found:
	err = 0;
	pos -= मुक्त_slots * माप(*de);
	nr_slots -= मुक्त_slots;
	अगर (मुक्त_slots) अणु
		/*
		 * Second stage: filling the मुक्त entries with new entries.
		 * NOTE: If this slots has लघुname, first, we ग_लिखो
		 * the दीर्घ name slots, then ग_लिखो the लघु name.
		 */
		पूर्णांक size = मुक्त_slots * माप(*de);
		पूर्णांक offset = pos & (sb->s_blocksize - 1);
		पूर्णांक दीर्घ_bhs = nr_bhs - (nr_slots == 0);

		/* Fill the दीर्घ name slots. */
		क्रम (i = 0; i < दीर्घ_bhs; i++) अणु
			पूर्णांक copy = min_t(पूर्णांक, sb->s_blocksize - offset, size);
			स_नकल(bhs[i]->b_data + offset, slots, copy);
			mark_buffer_dirty_inode(bhs[i], dir);
			offset = 0;
			slots += copy;
			size -= copy;
		पूर्ण
		अगर (दीर्घ_bhs && IS_सूचीSYNC(dir))
			err = fat_sync_bhs(bhs, दीर्घ_bhs);
		अगर (!err && i < nr_bhs) अणु
			/* Fill the लघु name slot. */
			पूर्णांक copy = min_t(पूर्णांक, sb->s_blocksize - offset, size);
			स_नकल(bhs[i]->b_data + offset, slots, copy);
			mark_buffer_dirty_inode(bhs[i], dir);
			अगर (IS_सूचीSYNC(dir))
				err = sync_dirty_buffer(bhs[i]);
		पूर्ण
		क्रम (i = 0; i < nr_bhs; i++)
			brअन्यथा(bhs[i]);
		अगर (err)
			जाओ error_हटाओ;
	पूर्ण

	अगर (nr_slots) अणु
		पूर्णांक cluster, nr_cluster;

		/*
		 * Third stage: allocate the cluster क्रम new entries.
		 * And initialize the cluster with new entries, then
		 * add the cluster to dir.
		 */
		cluster = fat_add_new_entries(dir, slots, nr_slots, &nr_cluster,
					      &de, &bh, &i_pos);
		अगर (cluster < 0) अणु
			err = cluster;
			जाओ error_हटाओ;
		पूर्ण
		err = fat_chain_add(dir, cluster, nr_cluster);
		अगर (err) अणु
			fat_मुक्त_clusters(dir, cluster);
			जाओ error_हटाओ;
		पूर्ण
		अगर (dir->i_size & (sbi->cluster_size - 1)) अणु
			fat_fs_error(sb, "Odd directory size");
			dir->i_size = (dir->i_size + sbi->cluster_size - 1)
				& ~((loff_t)sbi->cluster_size - 1);
		पूर्ण
		dir->i_size += nr_cluster << sbi->cluster_bits;
		MSDOS_I(dir)->mmu_निजी += nr_cluster << sbi->cluster_bits;
	पूर्ण
	sinfo->slot_off = pos;
	sinfo->de = de;
	sinfo->bh = bh;
	sinfo->i_pos = fat_make_i_pos(sb, sinfo->bh, sinfo->de);

	वापस 0;

error:
	brअन्यथा(bh);
	क्रम (i = 0; i < nr_bhs; i++)
		brअन्यथा(bhs[i]);
	वापस err;

error_हटाओ:
	brअन्यथा(bh);
	अगर (मुक्त_slots)
		__fat_हटाओ_entries(dir, pos, मुक्त_slots);
	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(fat_add_entries);
