<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2012-2013 Samsung Electronics Co., Ltd.
 */

#समावेश <linux/slab.h>
#समावेश <linux/compat.h>
#समावेश <linux/bपन.स>
#समावेश <linux/buffer_head.h>

#समावेश "exfat_raw.h"
#समावेश "exfat_fs.h"

अटल पूर्णांक exfat_extract_uni_name(काष्ठा exfat_dentry *ep,
		अचिन्हित लघु *uniname)
अणु
	पूर्णांक i, len = 0;

	क्रम (i = 0; i < EXFAT_खाता_NAME_LEN; i++) अणु
		*uniname = le16_to_cpu(ep->dentry.name.unicode_0_14[i]);
		अगर (*uniname == 0x0)
			वापस len;
		uniname++;
		len++;
	पूर्ण

	*uniname = 0x0;
	वापस len;

पूर्ण

अटल व्योम exfat_get_uniname_from_ext_entry(काष्ठा super_block *sb,
		काष्ठा exfat_chain *p_dir, पूर्णांक entry, अचिन्हित लघु *uniname)
अणु
	पूर्णांक i;
	काष्ठा exfat_entry_set_cache *es;

	es = exfat_get_dentry_set(sb, p_dir, entry, ES_ALL_ENTRIES);
	अगर (!es)
		वापस;

	/*
	 * First entry  : file entry
	 * Second entry : stream-extension entry
	 * Third entry  : first file-name entry
	 * So, the index of first file-name dentry should start from 2.
	 */
	क्रम (i = 2; i < es->num_entries; i++) अणु
		काष्ठा exfat_dentry *ep = exfat_get_dentry_cached(es, i);

		/* end of name entry */
		अगर (exfat_get_entry_type(ep) != TYPE_EXTEND)
			अवरोध;

		exfat_extract_uni_name(ep, uniname);
		uniname += EXFAT_खाता_NAME_LEN;
	पूर्ण

	exfat_मुक्त_dentry_set(es, false);
पूर्ण

/* पढ़ो a directory entry from the खोलोed directory */
अटल पूर्णांक exfat_सूची_पढ़ो(काष्ठा inode *inode, loff_t *cpos, काष्ठा exfat_dir_entry *dir_entry)
अणु
	पूर्णांक i, dentries_per_clu, dentries_per_clu_bits = 0, num_ext;
	अचिन्हित पूर्णांक type, clu_offset;
	sector_t sector;
	काष्ठा exfat_chain dir, clu;
	काष्ठा exfat_uni_name uni_name;
	काष्ठा exfat_dentry *ep;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	अचिन्हित पूर्णांक dentry = EXFAT_B_TO_DEN(*cpos) & 0xFFFFFFFF;
	काष्ठा buffer_head *bh;

	/* check अगर the given file ID is खोलोed */
	अगर (ei->type != TYPE_सूची)
		वापस -EPERM;

	अगर (ei->entry == -1)
		exfat_chain_set(&dir, sbi->root_dir, 0, ALLOC_FAT_CHAIN);
	अन्यथा
		exfat_chain_set(&dir, ei->start_clu,
			EXFAT_B_TO_CLU(i_size_पढ़ो(inode), sbi), ei->flags);

	dentries_per_clu = sbi->dentries_per_clu;
	dentries_per_clu_bits = ilog2(dentries_per_clu);

	clu_offset = dentry >> dentries_per_clu_bits;
	exfat_chain_dup(&clu, &dir);

	अगर (clu.flags == ALLOC_NO_FAT_CHAIN) अणु
		clu.dir += clu_offset;
		clu.size -= clu_offset;
	पूर्ण अन्यथा अणु
		/* hपूर्णांक_inक्रमmation */
		अगर (clu_offset > 0 && ei->hपूर्णांक_bmap.off != EXFAT_खातापूर्ण_CLUSTER &&
		    ei->hपूर्णांक_bmap.off > 0 && clu_offset >= ei->hपूर्णांक_bmap.off) अणु
			clu_offset -= ei->hपूर्णांक_bmap.off;
			clu.dir = ei->hपूर्णांक_bmap.clu;
		पूर्ण

		जबतक (clu_offset > 0) अणु
			अगर (exfat_get_next_cluster(sb, &(clu.dir)))
				वापस -EIO;

			clu_offset--;
		पूर्ण
	पूर्ण

	जबतक (clu.dir != EXFAT_खातापूर्ण_CLUSTER) अणु
		i = dentry & (dentries_per_clu - 1);

		क्रम ( ; i < dentries_per_clu; i++, dentry++) अणु
			ep = exfat_get_dentry(sb, &clu, i, &bh, &sector);
			अगर (!ep)
				वापस -EIO;

			type = exfat_get_entry_type(ep);
			अगर (type == TYPE_UNUSED) अणु
				brअन्यथा(bh);
				अवरोध;
			पूर्ण

			अगर (type != TYPE_खाता && type != TYPE_सूची) अणु
				brअन्यथा(bh);
				जारी;
			पूर्ण

			num_ext = ep->dentry.file.num_ext;
			dir_entry->attr = le16_to_cpu(ep->dentry.file.attr);
			exfat_get_entry_समय(sbi, &dir_entry->crसमय,
					ep->dentry.file.create_tz,
					ep->dentry.file.create_समय,
					ep->dentry.file.create_date,
					ep->dentry.file.create_समय_cs);
			exfat_get_entry_समय(sbi, &dir_entry->mसमय,
					ep->dentry.file.modअगरy_tz,
					ep->dentry.file.modअगरy_समय,
					ep->dentry.file.modअगरy_date,
					ep->dentry.file.modअगरy_समय_cs);
			exfat_get_entry_समय(sbi, &dir_entry->aसमय,
					ep->dentry.file.access_tz,
					ep->dentry.file.access_समय,
					ep->dentry.file.access_date,
					0);

			*uni_name.name = 0x0;
			exfat_get_uniname_from_ext_entry(sb, &clu, i,
				uni_name.name);
			exfat_utf16_to_nls(sb, &uni_name,
				dir_entry->namebuf.lfn,
				dir_entry->namebuf.lfnbuf_len);
			brअन्यथा(bh);

			ep = exfat_get_dentry(sb, &clu, i + 1, &bh, शून्य);
			अगर (!ep)
				वापस -EIO;
			dir_entry->size =
				le64_to_cpu(ep->dentry.stream.valid_size);
			dir_entry->entry = dentry;
			brअन्यथा(bh);

			ei->hपूर्णांक_bmap.off = dentry >> dentries_per_clu_bits;
			ei->hपूर्णांक_bmap.clu = clu.dir;

			*cpos = EXFAT_DEN_TO_B(dentry + 1 + num_ext);
			वापस 0;
		पूर्ण

		अगर (clu.flags == ALLOC_NO_FAT_CHAIN) अणु
			अगर (--clu.size > 0)
				clu.dir++;
			अन्यथा
				clu.dir = EXFAT_खातापूर्ण_CLUSTER;
		पूर्ण अन्यथा अणु
			अगर (exfat_get_next_cluster(sb, &(clu.dir)))
				वापस -EIO;
		पूर्ण
	पूर्ण

	dir_entry->namebuf.lfn[0] = '\0';
	*cpos = EXFAT_DEN_TO_B(dentry);
	वापस 0;
पूर्ण

अटल व्योम exfat_init_namebuf(काष्ठा exfat_dentry_namebuf *nb)
अणु
	nb->lfn = शून्य;
	nb->lfnbuf_len = 0;
पूर्ण

अटल पूर्णांक exfat_alloc_namebuf(काष्ठा exfat_dentry_namebuf *nb)
अणु
	nb->lfn = __getname();
	अगर (!nb->lfn)
		वापस -ENOMEM;
	nb->lfnbuf_len = MAX_VFSNAME_BUF_SIZE;
	वापस 0;
पूर्ण

अटल व्योम exfat_मुक्त_namebuf(काष्ठा exfat_dentry_namebuf *nb)
अणु
	अगर (!nb->lfn)
		वापस;

	__putname(nb->lfn);
	exfat_init_namebuf(nb);
पूर्ण

/* skip iterating emit_करोts when dir is empty */
#घोषणा ITER_POS_FILLED_DOTS    (2)
अटल पूर्णांक exfat_iterate(काष्ठा file *filp, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = filp->f_path.dentry->d_inode;
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा inode *पंचांगp;
	काष्ठा exfat_dir_entry de;
	काष्ठा exfat_dentry_namebuf *nb = &(de.namebuf);
	काष्ठा exfat_inode_info *ei = EXFAT_I(inode);
	अचिन्हित दीर्घ inum;
	loff_t cpos, i_pos;
	पूर्णांक err = 0, fake_offset = 0;

	exfat_init_namebuf(nb);
	mutex_lock(&EXFAT_SB(sb)->s_lock);

	cpos = ctx->pos;
	अगर (!dir_emit_करोts(filp, ctx))
		जाओ unlock;

	अगर (ctx->pos == ITER_POS_FILLED_DOTS) अणु
		cpos = 0;
		fake_offset = 1;
	पूर्ण

	अगर (cpos & (DENTRY_SIZE - 1)) अणु
		err = -ENOENT;
		जाओ unlock;
	पूर्ण

	/* name buffer should be allocated beक्रमe use */
	err = exfat_alloc_namebuf(nb);
	अगर (err)
		जाओ unlock;
get_new:
	अगर (cpos >= i_size_पढ़ो(inode))
		जाओ end_of_dir;

	err = exfat_सूची_पढ़ो(inode, &cpos, &de);
	अगर (err) अणु
		/*
		 * At least we tried to पढ़ो a sector.  Move cpos to next sector
		 * position (should be aligned).
		 */
		अगर (err == -EIO) अणु
			cpos += 1 << (sb->s_blocksize_bits);
			cpos &= ~(sb->s_blocksize - 1);
		पूर्ण

		err = -EIO;
		जाओ end_of_dir;
	पूर्ण

	अगर (!nb->lfn[0])
		जाओ end_of_dir;

	i_pos = ((loff_t)ei->start_clu << 32) |	(de.entry & 0xffffffff);
	पंचांगp = exfat_iget(sb, i_pos);
	अगर (पंचांगp) अणु
		inum = पंचांगp->i_ino;
		iput(पंचांगp);
	पूर्ण अन्यथा अणु
		inum = iunique(sb, EXFAT_ROOT_INO);
	पूर्ण

	/*
	 * Beक्रमe calling dir_emit(), sb_lock should be released.
	 * Because page fault can occur in dir_emit() when the size
	 * of buffer given from user is larger than one page size.
	 */
	mutex_unlock(&EXFAT_SB(sb)->s_lock);
	अगर (!dir_emit(ctx, nb->lfn, म_माप(nb->lfn), inum,
			(de.attr & ATTR_SUBसूची) ? DT_सूची : DT_REG))
		जाओ out_unlocked;
	mutex_lock(&EXFAT_SB(sb)->s_lock);
	ctx->pos = cpos;
	जाओ get_new;

end_of_dir:
	अगर (!cpos && fake_offset)
		cpos = ITER_POS_FILLED_DOTS;
	ctx->pos = cpos;
unlock:
	mutex_unlock(&EXFAT_SB(sb)->s_lock);
out_unlocked:
	/*
	 * To improve perक्रमmance, मुक्त namebuf after unlock sb_lock.
	 * If namebuf is not allocated, this function करो nothing
	 */
	exfat_मुक्त_namebuf(nb);
	वापस err;
पूर्ण

स्थिर काष्ठा file_operations exfat_dir_operations = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate	= exfat_iterate,
	.unlocked_ioctl = exfat_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl = exfat_compat_ioctl,
#पूर्ण_अगर
	.fsync		= exfat_file_fsync,
पूर्ण;

पूर्णांक exfat_alloc_new_dir(काष्ठा inode *inode, काष्ठा exfat_chain *clu)
अणु
	पूर्णांक ret;

	exfat_chain_set(clu, EXFAT_खातापूर्ण_CLUSTER, 0, ALLOC_NO_FAT_CHAIN);

	ret = exfat_alloc_cluster(inode, 1, clu, IS_सूचीSYNC(inode));
	अगर (ret)
		वापस ret;

	वापस exfat_zeroed_cluster(inode, clu->dir);
पूर्ण

पूर्णांक exfat_calc_num_entries(काष्ठा exfat_uni_name *p_uniname)
अणु
	पूर्णांक len;

	len = p_uniname->name_len;
	अगर (len == 0)
		वापस -EINVAL;

	/* 1 file entry + 1 stream entry + name entries */
	वापस ((len - 1) / EXFAT_खाता_NAME_LEN + 3);
पूर्ण

अचिन्हित पूर्णांक exfat_get_entry_type(काष्ठा exfat_dentry *ep)
अणु
	अगर (ep->type == EXFAT_UNUSED)
		वापस TYPE_UNUSED;
	अगर (IS_EXFAT_DELETED(ep->type))
		वापस TYPE_DELETED;
	अगर (ep->type == EXFAT_INVAL)
		वापस TYPE_INVALID;
	अगर (IS_EXFAT_CRITICAL_PRI(ep->type)) अणु
		अगर (ep->type == EXFAT_BITMAP)
			वापस TYPE_BITMAP;
		अगर (ep->type == EXFAT_UPCASE)
			वापस TYPE_UPCASE;
		अगर (ep->type == EXFAT_VOLUME)
			वापस TYPE_VOLUME;
		अगर (ep->type == EXFAT_खाता) अणु
			अगर (le16_to_cpu(ep->dentry.file.attr) & ATTR_SUBसूची)
				वापस TYPE_सूची;
			वापस TYPE_खाता;
		पूर्ण
		वापस TYPE_CRITICAL_PRI;
	पूर्ण
	अगर (IS_EXFAT_BENIGN_PRI(ep->type)) अणु
		अगर (ep->type == EXFAT_GUID)
			वापस TYPE_GUID;
		अगर (ep->type == EXFAT_PADDING)
			वापस TYPE_PADDING;
		अगर (ep->type == EXFAT_ACLTAB)
			वापस TYPE_ACLTAB;
		वापस TYPE_BENIGN_PRI;
	पूर्ण
	अगर (IS_EXFAT_CRITICAL_SEC(ep->type)) अणु
		अगर (ep->type == EXFAT_STREAM)
			वापस TYPE_STREAM;
		अगर (ep->type == EXFAT_NAME)
			वापस TYPE_EXTEND;
		अगर (ep->type == EXFAT_ACL)
			वापस TYPE_ACL;
		वापस TYPE_CRITICAL_SEC;
	पूर्ण
	वापस TYPE_BENIGN_SEC;
पूर्ण

अटल व्योम exfat_set_entry_type(काष्ठा exfat_dentry *ep, अचिन्हित पूर्णांक type)
अणु
	अगर (type == TYPE_UNUSED) अणु
		ep->type = EXFAT_UNUSED;
	पूर्ण अन्यथा अगर (type == TYPE_DELETED) अणु
		ep->type &= EXFAT_DELETE;
	पूर्ण अन्यथा अगर (type == TYPE_STREAM) अणु
		ep->type = EXFAT_STREAM;
	पूर्ण अन्यथा अगर (type == TYPE_EXTEND) अणु
		ep->type = EXFAT_NAME;
	पूर्ण अन्यथा अगर (type == TYPE_BITMAP) अणु
		ep->type = EXFAT_BITMAP;
	पूर्ण अन्यथा अगर (type == TYPE_UPCASE) अणु
		ep->type = EXFAT_UPCASE;
	पूर्ण अन्यथा अगर (type == TYPE_VOLUME) अणु
		ep->type = EXFAT_VOLUME;
	पूर्ण अन्यथा अगर (type == TYPE_सूची) अणु
		ep->type = EXFAT_खाता;
		ep->dentry.file.attr = cpu_to_le16(ATTR_SUBसूची);
	पूर्ण अन्यथा अगर (type == TYPE_खाता) अणु
		ep->type = EXFAT_खाता;
		ep->dentry.file.attr = cpu_to_le16(ATTR_ARCHIVE);
	पूर्ण
पूर्ण

अटल व्योम exfat_init_stream_entry(काष्ठा exfat_dentry *ep,
		अचिन्हित अक्षर flags, अचिन्हित पूर्णांक start_clu,
		अचिन्हित दीर्घ दीर्घ size)
अणु
	exfat_set_entry_type(ep, TYPE_STREAM);
	ep->dentry.stream.flags = flags;
	ep->dentry.stream.start_clu = cpu_to_le32(start_clu);
	ep->dentry.stream.valid_size = cpu_to_le64(size);
	ep->dentry.stream.size = cpu_to_le64(size);
पूर्ण

अटल व्योम exfat_init_name_entry(काष्ठा exfat_dentry *ep,
		अचिन्हित लघु *uniname)
अणु
	पूर्णांक i;

	exfat_set_entry_type(ep, TYPE_EXTEND);
	ep->dentry.name.flags = 0x0;

	क्रम (i = 0; i < EXFAT_खाता_NAME_LEN; i++) अणु
		अगर (*uniname != 0x0) अणु
			ep->dentry.name.unicode_0_14[i] = cpu_to_le16(*uniname);
			uniname++;
		पूर्ण अन्यथा अणु
			ep->dentry.name.unicode_0_14[i] = 0x0;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक exfat_init_dir_entry(काष्ठा inode *inode, काष्ठा exfat_chain *p_dir,
		पूर्णांक entry, अचिन्हित पूर्णांक type, अचिन्हित पूर्णांक start_clu,
		अचिन्हित दीर्घ दीर्घ size)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा बारpec64 ts = current_समय(inode);
	sector_t sector;
	काष्ठा exfat_dentry *ep;
	काष्ठा buffer_head *bh;

	/*
	 * We cannot use exfat_get_dentry_set here because file ep is not
	 * initialized yet.
	 */
	ep = exfat_get_dentry(sb, p_dir, entry, &bh, &sector);
	अगर (!ep)
		वापस -EIO;

	exfat_set_entry_type(ep, type);
	exfat_set_entry_समय(sbi, &ts,
			&ep->dentry.file.create_tz,
			&ep->dentry.file.create_समय,
			&ep->dentry.file.create_date,
			&ep->dentry.file.create_समय_cs);
	exfat_set_entry_समय(sbi, &ts,
			&ep->dentry.file.modअगरy_tz,
			&ep->dentry.file.modअगरy_समय,
			&ep->dentry.file.modअगरy_date,
			&ep->dentry.file.modअगरy_समय_cs);
	exfat_set_entry_समय(sbi, &ts,
			&ep->dentry.file.access_tz,
			&ep->dentry.file.access_समय,
			&ep->dentry.file.access_date,
			शून्य);

	exfat_update_bh(bh, IS_सूचीSYNC(inode));
	brअन्यथा(bh);

	ep = exfat_get_dentry(sb, p_dir, entry + 1, &bh, &sector);
	अगर (!ep)
		वापस -EIO;

	exfat_init_stream_entry(ep,
		(type == TYPE_खाता) ? ALLOC_FAT_CHAIN : ALLOC_NO_FAT_CHAIN,
		start_clu, size);
	exfat_update_bh(bh, IS_सूचीSYNC(inode));
	brअन्यथा(bh);

	वापस 0;
पूर्ण

पूर्णांक exfat_update_dir_chksum(काष्ठा inode *inode, काष्ठा exfat_chain *p_dir,
		पूर्णांक entry)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक ret = 0;
	पूर्णांक i, num_entries;
	sector_t sector;
	u16 chksum;
	काष्ठा exfat_dentry *ep, *fep;
	काष्ठा buffer_head *fbh, *bh;

	fep = exfat_get_dentry(sb, p_dir, entry, &fbh, &sector);
	अगर (!fep)
		वापस -EIO;

	num_entries = fep->dentry.file.num_ext + 1;
	chksum = exfat_calc_chksum16(fep, DENTRY_SIZE, 0, CS_सूची_ENTRY);

	क्रम (i = 1; i < num_entries; i++) अणु
		ep = exfat_get_dentry(sb, p_dir, entry + i, &bh, शून्य);
		अगर (!ep) अणु
			ret = -EIO;
			जाओ release_fbh;
		पूर्ण
		chksum = exfat_calc_chksum16(ep, DENTRY_SIZE, chksum,
				CS_DEFAULT);
		brअन्यथा(bh);
	पूर्ण

	fep->dentry.file.checksum = cpu_to_le16(chksum);
	exfat_update_bh(fbh, IS_सूचीSYNC(inode));
release_fbh:
	brअन्यथा(fbh);
	वापस ret;
पूर्ण

पूर्णांक exfat_init_ext_entry(काष्ठा inode *inode, काष्ठा exfat_chain *p_dir,
		पूर्णांक entry, पूर्णांक num_entries, काष्ठा exfat_uni_name *p_uniname)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक i;
	sector_t sector;
	अचिन्हित लघु *uniname = p_uniname->name;
	काष्ठा exfat_dentry *ep;
	काष्ठा buffer_head *bh;
	पूर्णांक sync = IS_सूचीSYNC(inode);

	ep = exfat_get_dentry(sb, p_dir, entry, &bh, &sector);
	अगर (!ep)
		वापस -EIO;

	ep->dentry.file.num_ext = (अचिन्हित अक्षर)(num_entries - 1);
	exfat_update_bh(bh, sync);
	brअन्यथा(bh);

	ep = exfat_get_dentry(sb, p_dir, entry + 1, &bh, &sector);
	अगर (!ep)
		वापस -EIO;

	ep->dentry.stream.name_len = p_uniname->name_len;
	ep->dentry.stream.name_hash = cpu_to_le16(p_uniname->name_hash);
	exfat_update_bh(bh, sync);
	brअन्यथा(bh);

	क्रम (i = EXFAT_FIRST_CLUSTER; i < num_entries; i++) अणु
		ep = exfat_get_dentry(sb, p_dir, entry + i, &bh, &sector);
		अगर (!ep)
			वापस -EIO;

		exfat_init_name_entry(ep, uniname);
		exfat_update_bh(bh, sync);
		brअन्यथा(bh);
		uniname += EXFAT_खाता_NAME_LEN;
	पूर्ण

	exfat_update_dir_chksum(inode, p_dir, entry);
	वापस 0;
पूर्ण

पूर्णांक exfat_हटाओ_entries(काष्ठा inode *inode, काष्ठा exfat_chain *p_dir,
		पूर्णांक entry, पूर्णांक order, पूर्णांक num_entries)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	पूर्णांक i;
	sector_t sector;
	काष्ठा exfat_dentry *ep;
	काष्ठा buffer_head *bh;

	क्रम (i = order; i < num_entries; i++) अणु
		ep = exfat_get_dentry(sb, p_dir, entry + i, &bh, &sector);
		अगर (!ep)
			वापस -EIO;

		exfat_set_entry_type(ep, TYPE_DELETED);
		exfat_update_bh(bh, IS_सूचीSYNC(inode));
		brअन्यथा(bh);
	पूर्ण

	वापस 0;
पूर्ण

व्योम exfat_update_dir_chksum_with_entry_set(काष्ठा exfat_entry_set_cache *es)
अणु
	पूर्णांक chksum_type = CS_सूची_ENTRY, i;
	अचिन्हित लघु chksum = 0;
	काष्ठा exfat_dentry *ep;

	क्रम (i = 0; i < es->num_entries; i++) अणु
		ep = exfat_get_dentry_cached(es, i);
		chksum = exfat_calc_chksum16(ep, DENTRY_SIZE, chksum,
					     chksum_type);
		chksum_type = CS_DEFAULT;
	पूर्ण
	ep = exfat_get_dentry_cached(es, 0);
	ep->dentry.file.checksum = cpu_to_le16(chksum);
	es->modअगरied = true;
पूर्ण

पूर्णांक exfat_मुक्त_dentry_set(काष्ठा exfat_entry_set_cache *es, पूर्णांक sync)
अणु
	पूर्णांक i, err = 0;

	अगर (es->modअगरied)
		err = exfat_update_bhs(es->bh, es->num_bh, sync);

	क्रम (i = 0; i < es->num_bh; i++)
		अगर (err)
			bक्रमget(es->bh[i]);
		अन्यथा
			brअन्यथा(es->bh[i]);
	kमुक्त(es);
	वापस err;
पूर्ण

अटल पूर्णांक exfat_walk_fat_chain(काष्ठा super_block *sb,
		काष्ठा exfat_chain *p_dir, अचिन्हित पूर्णांक byte_offset,
		अचिन्हित पूर्णांक *clu)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	अचिन्हित पूर्णांक clu_offset;
	अचिन्हित पूर्णांक cur_clu;

	clu_offset = EXFAT_B_TO_CLU(byte_offset, sbi);
	cur_clu = p_dir->dir;

	अगर (p_dir->flags == ALLOC_NO_FAT_CHAIN) अणु
		cur_clu += clu_offset;
	पूर्ण अन्यथा अणु
		जबतक (clu_offset > 0) अणु
			अगर (exfat_get_next_cluster(sb, &cur_clu))
				वापस -EIO;
			अगर (cur_clu == EXFAT_खातापूर्ण_CLUSTER) अणु
				exfat_fs_error(sb,
					"invalid dentry access beyond EOF (clu : %u, eidx : %d)",
					p_dir->dir,
					EXFAT_B_TO_DEN(byte_offset));
				वापस -EIO;
			पूर्ण
			clu_offset--;
		पूर्ण
	पूर्ण

	*clu = cur_clu;
	वापस 0;
पूर्ण

पूर्णांक exfat_find_location(काष्ठा super_block *sb, काष्ठा exfat_chain *p_dir,
		पूर्णांक entry, sector_t *sector, पूर्णांक *offset)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक off, clu = 0;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);

	off = EXFAT_DEN_TO_B(entry);

	ret = exfat_walk_fat_chain(sb, p_dir, off, &clu);
	अगर (ret)
		वापस ret;

	/* byte offset in cluster */
	off = EXFAT_CLU_OFFSET(off, sbi);

	/* byte offset in sector    */
	*offset = EXFAT_BLK_OFFSET(off, sb);

	/* sector offset in cluster */
	*sector = EXFAT_B_TO_BLK(off, sb);
	*sector += exfat_cluster_to_sector(sbi, clu);
	वापस 0;
पूर्ण

#घोषणा EXFAT_MAX_RA_SIZE     (128*1024)
अटल पूर्णांक exfat_dir_पढ़ोahead(काष्ठा super_block *sb, sector_t sec)
अणु
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा buffer_head *bh;
	अचिन्हित पूर्णांक max_ra_count = EXFAT_MAX_RA_SIZE >> sb->s_blocksize_bits;
	अचिन्हित पूर्णांक page_ra_count = PAGE_SIZE >> sb->s_blocksize_bits;
	अचिन्हित पूर्णांक adj_ra_count = max(sbi->sect_per_clus, page_ra_count);
	अचिन्हित पूर्णांक ra_count = min(adj_ra_count, max_ra_count);

	/* Read-ahead is not required */
	अगर (sbi->sect_per_clus == 1)
		वापस 0;

	अगर (sec < sbi->data_start_sector) अणु
		exfat_err(sb, "requested sector is invalid(sect:%llu, root:%llu)",
			  (अचिन्हित दीर्घ दीर्घ)sec, sbi->data_start_sector);
		वापस -EIO;
	पूर्ण

	/* Not sector aligned with ra_count, resize ra_count to page size */
	अगर ((sec - sbi->data_start_sector) & (ra_count - 1))
		ra_count = page_ra_count;

	bh = sb_find_get_block(sb, sec);
	अगर (!bh || !buffer_uptodate(bh)) अणु
		अचिन्हित पूर्णांक i;

		क्रम (i = 0; i < ra_count; i++)
			sb_bपढ़ोahead(sb, (sector_t)(sec + i));
	पूर्ण
	brअन्यथा(bh);
	वापस 0;
पूर्ण

काष्ठा exfat_dentry *exfat_get_dentry(काष्ठा super_block *sb,
		काष्ठा exfat_chain *p_dir, पूर्णांक entry, काष्ठा buffer_head **bh,
		sector_t *sector)
अणु
	अचिन्हित पूर्णांक dentries_per_page = EXFAT_B_TO_DEN(PAGE_SIZE);
	पूर्णांक off;
	sector_t sec;

	अगर (p_dir->dir == सूची_DELETED) अणु
		exfat_err(sb, "abnormal access to deleted dentry");
		वापस शून्य;
	पूर्ण

	अगर (exfat_find_location(sb, p_dir, entry, &sec, &off))
		वापस शून्य;

	अगर (p_dir->dir != EXFAT_FREE_CLUSTER &&
			!(entry & (dentries_per_page - 1)))
		exfat_dir_पढ़ोahead(sb, sec);

	*bh = sb_bपढ़ो(sb, sec);
	अगर (!*bh)
		वापस शून्य;

	अगर (sector)
		*sector = sec;
	वापस (काष्ठा exfat_dentry *)((*bh)->b_data + off);
पूर्ण

क्रमागत exfat_validate_dentry_mode अणु
	ES_MODE_STARTED,
	ES_MODE_GET_खाता_ENTRY,
	ES_MODE_GET_STRM_ENTRY,
	ES_MODE_GET_NAME_ENTRY,
	ES_MODE_GET_CRITICAL_SEC_ENTRY,
पूर्ण;

अटल bool exfat_validate_entry(अचिन्हित पूर्णांक type,
		क्रमागत exfat_validate_dentry_mode *mode)
अणु
	अगर (type == TYPE_UNUSED || type == TYPE_DELETED)
		वापस false;

	चयन (*mode) अणु
	हाल ES_MODE_STARTED:
		अगर  (type != TYPE_खाता && type != TYPE_सूची)
			वापस false;
		*mode = ES_MODE_GET_खाता_ENTRY;
		वापस true;
	हाल ES_MODE_GET_खाता_ENTRY:
		अगर (type != TYPE_STREAM)
			वापस false;
		*mode = ES_MODE_GET_STRM_ENTRY;
		वापस true;
	हाल ES_MODE_GET_STRM_ENTRY:
		अगर (type != TYPE_EXTEND)
			वापस false;
		*mode = ES_MODE_GET_NAME_ENTRY;
		वापस true;
	हाल ES_MODE_GET_NAME_ENTRY:
		अगर (type == TYPE_STREAM)
			वापस false;
		अगर (type != TYPE_EXTEND) अणु
			अगर (!(type & TYPE_CRITICAL_SEC))
				वापस false;
			*mode = ES_MODE_GET_CRITICAL_SEC_ENTRY;
		पूर्ण
		वापस true;
	हाल ES_MODE_GET_CRITICAL_SEC_ENTRY:
		अगर (type == TYPE_EXTEND || type == TYPE_STREAM)
			वापस false;
		अगर ((type & TYPE_CRITICAL_SEC) != TYPE_CRITICAL_SEC)
			वापस false;
		वापस true;
	शेष:
		WARN_ON_ONCE(1);
		वापस false;
	पूर्ण
पूर्ण

काष्ठा exfat_dentry *exfat_get_dentry_cached(
	काष्ठा exfat_entry_set_cache *es, पूर्णांक num)
अणु
	पूर्णांक off = es->start_off + num * DENTRY_SIZE;
	काष्ठा buffer_head *bh = es->bh[EXFAT_B_TO_BLK(off, es->sb)];
	अक्षर *p = bh->b_data + EXFAT_BLK_OFFSET(off, es->sb);

	वापस (काष्ठा exfat_dentry *)p;
पूर्ण

/*
 * Returns a set of dentries क्रम a file or dir.
 *
 * Note It provides a direct poपूर्णांकer to bh->data via exfat_get_dentry_cached().
 * User should call exfat_get_dentry_set() after setting 'modified' to apply
 * changes made in this entry set to the real device.
 *
 * in:
 *   sb+p_dir+entry: indicates a file/dir
 *   type:  specअगरies how many dentries should be included.
 * वापस:
 *   poपूर्णांकer of entry set on success,
 *   शून्य on failure.
 */
काष्ठा exfat_entry_set_cache *exfat_get_dentry_set(काष्ठा super_block *sb,
		काष्ठा exfat_chain *p_dir, पूर्णांक entry, अचिन्हित पूर्णांक type)
अणु
	पूर्णांक ret, i, num_bh;
	अचिन्हित पूर्णांक off, byte_offset, clu = 0;
	sector_t sec;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा exfat_entry_set_cache *es;
	काष्ठा exfat_dentry *ep;
	पूर्णांक num_entries;
	क्रमागत exfat_validate_dentry_mode mode = ES_MODE_STARTED;
	काष्ठा buffer_head *bh;

	अगर (p_dir->dir == सूची_DELETED) अणु
		exfat_err(sb, "access to deleted dentry");
		वापस शून्य;
	पूर्ण

	byte_offset = EXFAT_DEN_TO_B(entry);
	ret = exfat_walk_fat_chain(sb, p_dir, byte_offset, &clu);
	अगर (ret)
		वापस शून्य;

	es = kzalloc(माप(*es), GFP_KERNEL);
	अगर (!es)
		वापस शून्य;
	es->sb = sb;
	es->modअगरied = false;

	/* byte offset in cluster */
	byte_offset = EXFAT_CLU_OFFSET(byte_offset, sbi);

	/* byte offset in sector */
	off = EXFAT_BLK_OFFSET(byte_offset, sb);
	es->start_off = off;

	/* sector offset in cluster */
	sec = EXFAT_B_TO_BLK(byte_offset, sb);
	sec += exfat_cluster_to_sector(sbi, clu);

	bh = sb_bपढ़ो(sb, sec);
	अगर (!bh)
		जाओ मुक्त_es;
	es->bh[es->num_bh++] = bh;

	ep = exfat_get_dentry_cached(es, 0);
	अगर (!exfat_validate_entry(exfat_get_entry_type(ep), &mode))
		जाओ मुक्त_es;

	num_entries = type == ES_ALL_ENTRIES ?
		ep->dentry.file.num_ext + 1 : type;
	es->num_entries = num_entries;

	num_bh = EXFAT_B_TO_BLK_ROUND_UP(off + num_entries * DENTRY_SIZE, sb);
	क्रम (i = 1; i < num_bh; i++) अणु
		/* get the next sector */
		अगर (exfat_is_last_sector_in_cluster(sbi, sec)) अणु
			अगर (p_dir->flags == ALLOC_NO_FAT_CHAIN)
				clu++;
			अन्यथा अगर (exfat_get_next_cluster(sb, &clu))
				जाओ मुक्त_es;
			sec = exfat_cluster_to_sector(sbi, clu);
		पूर्ण अन्यथा अणु
			sec++;
		पूर्ण

		bh = sb_bपढ़ो(sb, sec);
		अगर (!bh)
			जाओ मुक्त_es;
		es->bh[es->num_bh++] = bh;
	पूर्ण

	/* validiate cached dentries */
	क्रम (i = 1; i < num_entries; i++) अणु
		ep = exfat_get_dentry_cached(es, i);
		अगर (!exfat_validate_entry(exfat_get_entry_type(ep), &mode))
			जाओ मुक्त_es;
	पूर्ण
	वापस es;

मुक्त_es:
	exfat_मुक्त_dentry_set(es, false);
	वापस शून्य;
पूर्ण

क्रमागत अणु
	सूचीENT_STEP_खाता,
	सूचीENT_STEP_STRM,
	सूचीENT_STEP_NAME,
	सूचीENT_STEP_SECD,
पूर्ण;

/*
 * @ei:         inode info of parent directory
 * @p_dir:      directory काष्ठाure of parent directory
 * @num_entries:entry size of p_uniname
 * @hपूर्णांक_opt:   If p_uniname is found, filled with optimized dir/entry
 *              क्रम traversing cluster chain.
 * @वापस:
 *   >= 0:      file directory entry position where the name exists
 *   -ENOENT:   entry with the name करोes not exist
 *   -EIO:      I/O error
 */
पूर्णांक exfat_find_dir_entry(काष्ठा super_block *sb, काष्ठा exfat_inode_info *ei,
		काष्ठा exfat_chain *p_dir, काष्ठा exfat_uni_name *p_uniname,
		पूर्णांक num_entries, अचिन्हित पूर्णांक type, काष्ठा exfat_hपूर्णांक *hपूर्णांक_opt)
अणु
	पूर्णांक i, शुरुआत = 0, dentry = 0, end_eidx = 0, num_ext = 0, len;
	पूर्णांक order, step, name_len = 0;
	पूर्णांक dentries_per_clu, num_empty = 0;
	अचिन्हित पूर्णांक entry_type;
	अचिन्हित लघु *uniname = शून्य;
	काष्ठा exfat_chain clu;
	काष्ठा exfat_hपूर्णांक *hपूर्णांक_stat = &ei->hपूर्णांक_stat;
	काष्ठा exfat_hपूर्णांक_femp candi_empty;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);

	dentries_per_clu = sbi->dentries_per_clu;

	exfat_chain_dup(&clu, p_dir);

	अगर (hपूर्णांक_stat->eidx) अणु
		clu.dir = hपूर्णांक_stat->clu;
		dentry = hपूर्णांक_stat->eidx;
		end_eidx = dentry;
	पूर्ण

	candi_empty.eidx = EXFAT_HINT_NONE;
शुरुआत:
	order = 0;
	step = सूचीENT_STEP_खाता;
	जबतक (clu.dir != EXFAT_खातापूर्ण_CLUSTER) अणु
		i = dentry & (dentries_per_clu - 1);
		क्रम (; i < dentries_per_clu; i++, dentry++) अणु
			काष्ठा exfat_dentry *ep;
			काष्ठा buffer_head *bh;

			अगर (शुरुआत && dentry == end_eidx)
				जाओ not_found;

			ep = exfat_get_dentry(sb, &clu, i, &bh, शून्य);
			अगर (!ep)
				वापस -EIO;

			entry_type = exfat_get_entry_type(ep);

			अगर (entry_type == TYPE_UNUSED ||
			    entry_type == TYPE_DELETED) अणु
				step = सूचीENT_STEP_खाता;

				num_empty++;
				अगर (candi_empty.eidx == EXFAT_HINT_NONE &&
						num_empty == 1) अणु
					exfat_chain_set(&candi_empty.cur,
						clu.dir, clu.size, clu.flags);
				पूर्ण

				अगर (candi_empty.eidx == EXFAT_HINT_NONE &&
						num_empty >= num_entries) अणु
					candi_empty.eidx =
						dentry - (num_empty - 1);
					WARN_ON(candi_empty.eidx < 0);
					candi_empty.count = num_empty;

					अगर (ei->hपूर्णांक_femp.eidx ==
							EXFAT_HINT_NONE ||
						candi_empty.eidx <=
							 ei->hपूर्णांक_femp.eidx)
						ei->hपूर्णांक_femp = candi_empty;
				पूर्ण

				brअन्यथा(bh);
				अगर (entry_type == TYPE_UNUSED)
					जाओ not_found;
				जारी;
			पूर्ण

			num_empty = 0;
			candi_empty.eidx = EXFAT_HINT_NONE;

			अगर (entry_type == TYPE_खाता || entry_type == TYPE_सूची) अणु
				step = सूचीENT_STEP_खाता;
				hपूर्णांक_opt->clu = clu.dir;
				hपूर्णांक_opt->eidx = i;
				अगर (type == TYPE_ALL || type == entry_type) अणु
					num_ext = ep->dentry.file.num_ext;
					step = सूचीENT_STEP_STRM;
				पूर्ण
				brअन्यथा(bh);
				जारी;
			पूर्ण

			अगर (entry_type == TYPE_STREAM) अणु
				u16 name_hash;

				अगर (step != सूचीENT_STEP_STRM) अणु
					step = सूचीENT_STEP_खाता;
					brअन्यथा(bh);
					जारी;
				पूर्ण
				step = सूचीENT_STEP_खाता;
				name_hash = le16_to_cpu(
						ep->dentry.stream.name_hash);
				अगर (p_uniname->name_hash == name_hash &&
				    p_uniname->name_len ==
						ep->dentry.stream.name_len) अणु
					step = सूचीENT_STEP_NAME;
					order = 1;
					name_len = 0;
				पूर्ण
				brअन्यथा(bh);
				जारी;
			पूर्ण

			brअन्यथा(bh);
			अगर (entry_type == TYPE_EXTEND) अणु
				अचिन्हित लघु entry_uniname[16], uniअक्षर;

				अगर (step != सूचीENT_STEP_NAME) अणु
					step = सूचीENT_STEP_खाता;
					जारी;
				पूर्ण

				अगर (++order == 2)
					uniname = p_uniname->name;
				अन्यथा
					uniname += EXFAT_खाता_NAME_LEN;

				len = exfat_extract_uni_name(ep, entry_uniname);
				name_len += len;

				uniअक्षर = *(uniname+len);
				*(uniname+len) = 0x0;

				अगर (exfat_uniname_ncmp(sb, uniname,
					entry_uniname, len)) अणु
					step = सूचीENT_STEP_खाता;
				पूर्ण अन्यथा अगर (p_uniname->name_len == name_len) अणु
					अगर (order == num_ext)
						जाओ found;
					step = सूचीENT_STEP_SECD;
				पूर्ण

				*(uniname+len) = uniअक्षर;
				जारी;
			पूर्ण

			अगर (entry_type &
					(TYPE_CRITICAL_SEC | TYPE_BENIGN_SEC)) अणु
				अगर (step == सूचीENT_STEP_SECD) अणु
					अगर (++order == num_ext)
						जाओ found;
					जारी;
				पूर्ण
			पूर्ण
			step = सूचीENT_STEP_खाता;
		पूर्ण

		अगर (clu.flags == ALLOC_NO_FAT_CHAIN) अणु
			अगर (--clu.size > 0)
				clu.dir++;
			अन्यथा
				clu.dir = EXFAT_खातापूर्ण_CLUSTER;
		पूर्ण अन्यथा अणु
			अगर (exfat_get_next_cluster(sb, &clu.dir))
				वापस -EIO;
		पूर्ण
	पूर्ण

not_found:
	/*
	 * We started at not 0 index,so we should try to find target
	 * from 0 index to the index we started at.
	 */
	अगर (!शुरुआत && end_eidx) अणु
		शुरुआत = 1;
		dentry = 0;
		clu.dir = p_dir->dir;
		/* reset empty hपूर्णांक */
		num_empty = 0;
		candi_empty.eidx = EXFAT_HINT_NONE;
		जाओ शुरुआत;
	पूर्ण

	/* initialized hपूर्णांक_stat */
	hपूर्णांक_stat->clu = p_dir->dir;
	hपूर्णांक_stat->eidx = 0;
	वापस -ENOENT;

found:
	/* next dentry we'll find is out of this cluster */
	अगर (!((dentry + 1) & (dentries_per_clu - 1))) अणु
		पूर्णांक ret = 0;

		अगर (clu.flags == ALLOC_NO_FAT_CHAIN) अणु
			अगर (--clu.size > 0)
				clu.dir++;
			अन्यथा
				clu.dir = EXFAT_खातापूर्ण_CLUSTER;
		पूर्ण अन्यथा अणु
			ret = exfat_get_next_cluster(sb, &clu.dir);
		पूर्ण

		अगर (ret || clu.dir == EXFAT_खातापूर्ण_CLUSTER) अणु
			/* just initialized hपूर्णांक_stat */
			hपूर्णांक_stat->clu = p_dir->dir;
			hपूर्णांक_stat->eidx = 0;
			वापस (dentry - num_ext);
		पूर्ण
	पूर्ण

	hपूर्णांक_stat->clu = clu.dir;
	hपूर्णांक_stat->eidx = dentry + 1;
	वापस dentry - num_ext;
पूर्ण

पूर्णांक exfat_count_ext_entries(काष्ठा super_block *sb, काष्ठा exfat_chain *p_dir,
		पूर्णांक entry, काष्ठा exfat_dentry *ep)
अणु
	पूर्णांक i, count = 0;
	अचिन्हित पूर्णांक type;
	काष्ठा exfat_dentry *ext_ep;
	काष्ठा buffer_head *bh;

	क्रम (i = 0, entry++; i < ep->dentry.file.num_ext; i++, entry++) अणु
		ext_ep = exfat_get_dentry(sb, p_dir, entry, &bh, शून्य);
		अगर (!ext_ep)
			वापस -EIO;

		type = exfat_get_entry_type(ext_ep);
		brअन्यथा(bh);
		अगर (type == TYPE_EXTEND || type == TYPE_STREAM)
			count++;
		अन्यथा
			अवरोध;
	पूर्ण
	वापस count;
पूर्ण

पूर्णांक exfat_count_dir_entries(काष्ठा super_block *sb, काष्ठा exfat_chain *p_dir)
अणु
	पूर्णांक i, count = 0;
	पूर्णांक dentries_per_clu;
	अचिन्हित पूर्णांक entry_type;
	काष्ठा exfat_chain clu;
	काष्ठा exfat_dentry *ep;
	काष्ठा exfat_sb_info *sbi = EXFAT_SB(sb);
	काष्ठा buffer_head *bh;

	dentries_per_clu = sbi->dentries_per_clu;

	exfat_chain_dup(&clu, p_dir);

	जबतक (clu.dir != EXFAT_खातापूर्ण_CLUSTER) अणु
		क्रम (i = 0; i < dentries_per_clu; i++) अणु
			ep = exfat_get_dentry(sb, &clu, i, &bh, शून्य);
			अगर (!ep)
				वापस -EIO;
			entry_type = exfat_get_entry_type(ep);
			brअन्यथा(bh);

			अगर (entry_type == TYPE_UNUSED)
				वापस count;
			अगर (entry_type != TYPE_सूची)
				जारी;
			count++;
		पूर्ण

		अगर (clu.flags == ALLOC_NO_FAT_CHAIN) अणु
			अगर (--clu.size > 0)
				clu.dir++;
			अन्यथा
				clu.dir = EXFAT_खातापूर्ण_CLUSTER;
		पूर्ण अन्यथा अणु
			अगर (exfat_get_next_cluster(sb, &(clu.dir)))
				वापस -EIO;
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण
