<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/msकरोs/namei.c
 *
 *  Written 1992,1993 by Werner Almesberger
 *  Hidden files 1995 by Albert Cahalan <albert@ccs.neu.edu> <adc@coe.neu.edu>
 *  Rewritten क्रम स्थिरant inumbers 1999 by Al Viro
 */

#समावेश <linux/module.h>
#समावेश <linux/iversion.h>
#समावेश "fat.h"

/* Characters that are undesirable in an MS-DOS file name */
अटल अचिन्हित अक्षर bad_अक्षरs[] = "*?<>|\"";
अटल अचिन्हित अक्षर bad_अगर_strict[] = "+=,; ";

/***** Formats an MS-DOS file name. Rejects invalid names. */
अटल पूर्णांक msकरोs_क्रमmat_name(स्थिर अचिन्हित अक्षर *name, पूर्णांक len,
			     अचिन्हित अक्षर *res, काष्ठा fat_mount_options *opts)
	/*
	 * name is the proposed name, len is its length, res is
	 * the resulting name, opts->name_check is either (r)elaxed,
	 * (n)ormal or (s)trict, opts->करोtsOK allows करोts at the
	 * beginning of name (क्रम hidden files)
	 */
अणु
	अचिन्हित अक्षर *walk;
	अचिन्हित अक्षर c;
	पूर्णांक space;

	अगर (name[0] == '.') अणु	/* करोtfile because . and .. alपढ़ोy करोne */
		अगर (opts->करोtsOK) अणु
			/* Get rid of करोt - test क्रम it अन्यथाwhere */
			name++;
			len--;
		पूर्ण अन्यथा
			वापस -EINVAL;
	पूर्ण
	/*
	 * disallow names that _really_ start with a करोt
	 */
	space = 1;
	c = 0;
	क्रम (walk = res; len && walk - res < 8; walk++) अणु
		c = *name++;
		len--;
		अगर (opts->name_check != 'r' && म_अक्षर(bad_अक्षरs, c))
			वापस -EINVAL;
		अगर (opts->name_check == 's' && म_अक्षर(bad_अगर_strict, c))
			वापस -EINVAL;
		अगर (c >= 'A' && c <= 'Z' && opts->name_check == 's')
			वापस -EINVAL;
		अगर (c < ' ' || c == ':' || c == '\\')
			वापस -EINVAL;
	/*
	 * 0xE5 is legal as a first अक्षरacter, but we must substitute
	 * 0x05 because 0xE5 marks deleted files.  Yes, DOS really
	 * करोes this.
	 * It seems that Microsoft hacked DOS to support non-US
	 * अक्षरacters after the 0xE5 अक्षरacter was alपढ़ोy in use to
	 * mark deleted files.
	 */
		अगर ((res == walk) && (c == 0xE5))
			c = 0x05;
		अगर (c == '.')
			अवरोध;
		space = (c == ' ');
		*walk = (!opts->noहाल && c >= 'a' && c <= 'z') ? c - 32 : c;
	पूर्ण
	अगर (space)
		वापस -EINVAL;
	अगर (opts->name_check == 's' && len && c != '.') अणु
		c = *name++;
		len--;
		अगर (c != '.')
			वापस -EINVAL;
	पूर्ण
	जबतक (c != '.' && len--)
		c = *name++;
	अगर (c == '.') अणु
		जबतक (walk - res < 8)
			*walk++ = ' ';
		जबतक (len > 0 && walk - res < MSDOS_NAME) अणु
			c = *name++;
			len--;
			अगर (opts->name_check != 'r' && म_अक्षर(bad_अक्षरs, c))
				वापस -EINVAL;
			अगर (opts->name_check == 's' &&
			    म_अक्षर(bad_अगर_strict, c))
				वापस -EINVAL;
			अगर (c < ' ' || c == ':' || c == '\\')
				वापस -EINVAL;
			अगर (c == '.') अणु
				अगर (opts->name_check == 's')
					वापस -EINVAL;
				अवरोध;
			पूर्ण
			अगर (c >= 'A' && c <= 'Z' && opts->name_check == 's')
				वापस -EINVAL;
			space = c == ' ';
			अगर (!opts->noहाल && c >= 'a' && c <= 'z')
				*walk++ = c - 32;
			अन्यथा
				*walk++ = c;
		पूर्ण
		अगर (space)
			वापस -EINVAL;
		अगर (opts->name_check == 's' && len)
			वापस -EINVAL;
	पूर्ण
	जबतक (walk - res < MSDOS_NAME)
		*walk++ = ' ';

	वापस 0;
पूर्ण

/***** Locates a directory entry.  Uses unक्रमmatted name. */
अटल पूर्णांक msकरोs_find(काष्ठा inode *dir, स्थिर अचिन्हित अक्षर *name, पूर्णांक len,
		      काष्ठा fat_slot_info *sinfo)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(dir->i_sb);
	अचिन्हित अक्षर msकरोs_name[MSDOS_NAME];
	पूर्णांक err;

	err = msकरोs_क्रमmat_name(name, len, msकरोs_name, &sbi->options);
	अगर (err)
		वापस -ENOENT;

	err = fat_scan(dir, msकरोs_name, sinfo);
	अगर (!err && sbi->options.करोtsOK) अणु
		अगर (name[0] == '.') अणु
			अगर (!(sinfo->de->attr & ATTR_HIDDEN))
				err = -ENOENT;
		पूर्ण अन्यथा अणु
			अगर (sinfo->de->attr & ATTR_HIDDEN)
				err = -ENOENT;
		पूर्ण
		अगर (err)
			brअन्यथा(sinfo->bh);
	पूर्ण
	वापस err;
पूर्ण

/*
 * Compute the hash क्रम the msकरोs name corresponding to the dentry.
 * Note: अगर the name is invalid, we leave the hash code unchanged so
 * that the existing dentry can be used. The msकरोs fs routines will
 * वापस ENOENT or EINVAL as appropriate.
 */
अटल पूर्णांक msकरोs_hash(स्थिर काष्ठा dentry *dentry, काष्ठा qstr *qstr)
अणु
	काष्ठा fat_mount_options *options = &MSDOS_SB(dentry->d_sb)->options;
	अचिन्हित अक्षर msकरोs_name[MSDOS_NAME];
	पूर्णांक error;

	error = msकरोs_क्रमmat_name(qstr->name, qstr->len, msकरोs_name, options);
	अगर (!error)
		qstr->hash = full_name_hash(dentry, msकरोs_name, MSDOS_NAME);
	वापस 0;
पूर्ण

/*
 * Compare two msकरोs names. If either of the names are invalid,
 * we fall back to करोing the standard name comparison.
 */
अटल पूर्णांक msकरोs_cmp(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु
	काष्ठा fat_mount_options *options = &MSDOS_SB(dentry->d_sb)->options;
	अचिन्हित अक्षर a_msकरोs_name[MSDOS_NAME], b_msकरोs_name[MSDOS_NAME];
	पूर्णांक error;

	error = msकरोs_क्रमmat_name(name->name, name->len, a_msकरोs_name, options);
	अगर (error)
		जाओ old_compare;
	error = msकरोs_क्रमmat_name(str, len, b_msकरोs_name, options);
	अगर (error)
		जाओ old_compare;
	error = स_भेद(a_msकरोs_name, b_msकरोs_name, MSDOS_NAME);
out:
	वापस error;

old_compare:
	error = 1;
	अगर (name->len == len)
		error = स_भेद(name->name, str, len);
	जाओ out;
पूर्ण

अटल स्थिर काष्ठा dentry_operations msकरोs_dentry_operations = अणु
	.d_hash		= msकरोs_hash,
	.d_compare	= msकरोs_cmp,
पूर्ण;

/*
 * AV. Wrappers क्रम FAT sb operations. Is it wise?
 */

/***** Get inode using directory and name */
अटल काष्ठा dentry *msकरोs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
				   अचिन्हित पूर्णांक flags)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा fat_slot_info sinfo;
	काष्ठा inode *inode;
	पूर्णांक err;

	mutex_lock(&MSDOS_SB(sb)->s_lock);
	err = msकरोs_find(dir, dentry->d_name.name, dentry->d_name.len, &sinfo);
	चयन (err) अणु
	हाल -ENOENT:
		inode = शून्य;
		अवरोध;
	हाल 0:
		inode = fat_build_inode(sb, sinfo.de, sinfo.i_pos);
		brअन्यथा(sinfo.bh);
		अवरोध;
	शेष:
		inode = ERR_PTR(err);
	पूर्ण
	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	वापस d_splice_alias(inode, dentry);
पूर्ण

/***** Creates a directory entry (name is alपढ़ोy क्रमmatted). */
अटल पूर्णांक msकरोs_add_entry(काष्ठा inode *dir, स्थिर अचिन्हित अक्षर *name,
			   पूर्णांक is_dir, पूर्णांक is_hid, पूर्णांक cluster,
			   काष्ठा बारpec64 *ts, काष्ठा fat_slot_info *sinfo)
अणु
	काष्ठा msकरोs_sb_info *sbi = MSDOS_SB(dir->i_sb);
	काष्ठा msकरोs_dir_entry de;
	__le16 समय, date;
	पूर्णांक err;

	स_नकल(de.name, name, MSDOS_NAME);
	de.attr = is_dir ? ATTR_सूची : ATTR_ARCH;
	अगर (is_hid)
		de.attr |= ATTR_HIDDEN;
	de.lहाल = 0;
	fat_समय_unix2fat(sbi, ts, &समय, &date, शून्य);
	de.cdate = de.adate = 0;
	de.स_समय = 0;
	de.स_समय_cs = 0;
	de.समय = समय;
	de.date = date;
	fat_set_start(&de, cluster);
	de.size = 0;

	err = fat_add_entries(dir, &de, 1, sinfo);
	अगर (err)
		वापस err;

	fat_truncate_समय(dir, ts, S_CTIME|S_MTIME);
	अगर (IS_सूचीSYNC(dir))
		(व्योम)fat_sync_inode(dir);
	अन्यथा
		mark_inode_dirty(dir);

	वापस 0;
पूर्ण

/***** Create a file */
अटल पूर्णांक msकरोs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा inode *inode = शून्य;
	काष्ठा fat_slot_info sinfo;
	काष्ठा बारpec64 ts;
	अचिन्हित अक्षर msकरोs_name[MSDOS_NAME];
	पूर्णांक err, is_hid;

	mutex_lock(&MSDOS_SB(sb)->s_lock);

	err = msकरोs_क्रमmat_name(dentry->d_name.name, dentry->d_name.len,
				msकरोs_name, &MSDOS_SB(sb)->options);
	अगर (err)
		जाओ out;
	is_hid = (dentry->d_name.name[0] == '.') && (msdos_name[0] != '.');
	/* Have to करो it due to foo vs. .foo conflicts */
	अगर (!fat_scan(dir, msकरोs_name, &sinfo)) अणु
		brअन्यथा(sinfo.bh);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	ts = current_समय(dir);
	err = msकरोs_add_entry(dir, msकरोs_name, 0, is_hid, 0, &ts, &sinfo);
	अगर (err)
		जाओ out;
	inode = fat_build_inode(sb, sinfo.de, sinfo.i_pos);
	brअन्यथा(sinfo.bh);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		जाओ out;
	पूर्ण
	fat_truncate_समय(inode, &ts, S_ATIME|S_CTIME|S_MTIME);
	/* बारtamp is alपढ़ोy written, so mark_inode_dirty() is unneeded. */

	d_instantiate(dentry, inode);
out:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	अगर (!err)
		err = fat_flush_inodes(sb, dir, inode);
	वापस err;
पूर्ण

/***** Remove a directory */
अटल पूर्णांक msकरोs_सूची_हटाओ(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा fat_slot_info sinfo;
	पूर्णांक err;

	mutex_lock(&MSDOS_SB(sb)->s_lock);
	err = fat_dir_empty(inode);
	अगर (err)
		जाओ out;
	err = msकरोs_find(dir, dentry->d_name.name, dentry->d_name.len, &sinfo);
	अगर (err)
		जाओ out;

	err = fat_हटाओ_entries(dir, &sinfo);	/* and releases bh */
	अगर (err)
		जाओ out;
	drop_nlink(dir);

	clear_nlink(inode);
	fat_truncate_समय(inode, शून्य, S_CTIME);
	fat_detach(inode);
out:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	अगर (!err)
		err = fat_flush_inodes(sb, dir, inode);

	वापस err;
पूर्ण

/***** Make a directory */
अटल पूर्णांक msकरोs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा super_block *sb = dir->i_sb;
	काष्ठा fat_slot_info sinfo;
	काष्ठा inode *inode;
	अचिन्हित अक्षर msकरोs_name[MSDOS_NAME];
	काष्ठा बारpec64 ts;
	पूर्णांक err, is_hid, cluster;

	mutex_lock(&MSDOS_SB(sb)->s_lock);

	err = msकरोs_क्रमmat_name(dentry->d_name.name, dentry->d_name.len,
				msकरोs_name, &MSDOS_SB(sb)->options);
	अगर (err)
		जाओ out;
	is_hid = (dentry->d_name.name[0] == '.') && (msdos_name[0] != '.');
	/* foo vs .foo situation */
	अगर (!fat_scan(dir, msकरोs_name, &sinfo)) अणु
		brअन्यथा(sinfo.bh);
		err = -EINVAL;
		जाओ out;
	पूर्ण

	ts = current_समय(dir);
	cluster = fat_alloc_new_dir(dir, &ts);
	अगर (cluster < 0) अणु
		err = cluster;
		जाओ out;
	पूर्ण
	err = msकरोs_add_entry(dir, msकरोs_name, 1, is_hid, cluster, &ts, &sinfo);
	अगर (err)
		जाओ out_मुक्त;
	inc_nlink(dir);

	inode = fat_build_inode(sb, sinfo.de, sinfo.i_pos);
	brअन्यथा(sinfo.bh);
	अगर (IS_ERR(inode)) अणु
		err = PTR_ERR(inode);
		/* the directory was completed, just वापस a error */
		जाओ out;
	पूर्ण
	set_nlink(inode, 2);
	fat_truncate_समय(inode, &ts, S_ATIME|S_CTIME|S_MTIME);
	/* बारtamp is alपढ़ोy written, so mark_inode_dirty() is unneeded. */

	d_instantiate(dentry, inode);

	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	fat_flush_inodes(sb, dir, inode);
	वापस 0;

out_मुक्त:
	fat_मुक्त_clusters(dir, cluster);
out:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	वापस err;
पूर्ण

/***** Unlink a file */
अटल पूर्णांक msकरोs_unlink(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा fat_slot_info sinfo;
	पूर्णांक err;

	mutex_lock(&MSDOS_SB(sb)->s_lock);
	err = msकरोs_find(dir, dentry->d_name.name, dentry->d_name.len, &sinfo);
	अगर (err)
		जाओ out;

	err = fat_हटाओ_entries(dir, &sinfo);	/* and releases bh */
	अगर (err)
		जाओ out;
	clear_nlink(inode);
	fat_truncate_समय(inode, शून्य, S_CTIME);
	fat_detach(inode);
out:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	अगर (!err)
		err = fat_flush_inodes(sb, dir, inode);

	वापस err;
पूर्ण

अटल पूर्णांक करो_msकरोs_नाम(काष्ठा inode *old_dir, अचिन्हित अक्षर *old_name,
			   काष्ठा dentry *old_dentry,
			   काष्ठा inode *new_dir, अचिन्हित अक्षर *new_name,
			   काष्ठा dentry *new_dentry, पूर्णांक is_hid)
अणु
	काष्ठा buffer_head *करोtकरोt_bh;
	काष्ठा msकरोs_dir_entry *करोtकरोt_de;
	काष्ठा inode *old_inode, *new_inode;
	काष्ठा fat_slot_info old_sinfo, sinfo;
	काष्ठा बारpec64 ts;
	loff_t new_i_pos;
	पूर्णांक err, old_attrs, is_dir, update_करोtकरोt, corrupt = 0;

	old_sinfo.bh = sinfo.bh = करोtकरोt_bh = शून्य;
	old_inode = d_inode(old_dentry);
	new_inode = d_inode(new_dentry);

	err = fat_scan(old_dir, old_name, &old_sinfo);
	अगर (err) अणु
		err = -EIO;
		जाओ out;
	पूर्ण

	is_dir = S_ISसूची(old_inode->i_mode);
	update_करोtकरोt = (is_dir && old_dir != new_dir);
	अगर (update_करोtकरोt) अणु
		अगर (fat_get_करोtकरोt_entry(old_inode, &करोtकरोt_bh, &करोtकरोt_de)) अणु
			err = -EIO;
			जाओ out;
		पूर्ण
	पूर्ण

	old_attrs = MSDOS_I(old_inode)->i_attrs;
	err = fat_scan(new_dir, new_name, &sinfo);
	अगर (!err) अणु
		अगर (!new_inode) अणु
			/* "foo" -> ".foo" हाल. just change the ATTR_HIDDEN */
			अगर (sinfo.de != old_sinfo.de) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण
			अगर (is_hid)
				MSDOS_I(old_inode)->i_attrs |= ATTR_HIDDEN;
			अन्यथा
				MSDOS_I(old_inode)->i_attrs &= ~ATTR_HIDDEN;
			अगर (IS_सूचीSYNC(old_dir)) अणु
				err = fat_sync_inode(old_inode);
				अगर (err) अणु
					MSDOS_I(old_inode)->i_attrs = old_attrs;
					जाओ out;
				पूर्ण
			पूर्ण अन्यथा
				mark_inode_dirty(old_inode);

			inode_inc_iversion(old_dir);
			fat_truncate_समय(old_dir, शून्य, S_CTIME|S_MTIME);
			अगर (IS_सूचीSYNC(old_dir))
				(व्योम)fat_sync_inode(old_dir);
			अन्यथा
				mark_inode_dirty(old_dir);
			जाओ out;
		पूर्ण
	पूर्ण

	ts = current_समय(old_inode);
	अगर (new_inode) अणु
		अगर (err)
			जाओ out;
		अगर (is_dir) अणु
			err = fat_dir_empty(new_inode);
			अगर (err)
				जाओ out;
		पूर्ण
		new_i_pos = MSDOS_I(new_inode)->i_pos;
		fat_detach(new_inode);
	पूर्ण अन्यथा अणु
		err = msकरोs_add_entry(new_dir, new_name, is_dir, is_hid, 0,
				      &ts, &sinfo);
		अगर (err)
			जाओ out;
		new_i_pos = sinfo.i_pos;
	पूर्ण
	inode_inc_iversion(new_dir);

	fat_detach(old_inode);
	fat_attach(old_inode, new_i_pos);
	अगर (is_hid)
		MSDOS_I(old_inode)->i_attrs |= ATTR_HIDDEN;
	अन्यथा
		MSDOS_I(old_inode)->i_attrs &= ~ATTR_HIDDEN;
	अगर (IS_सूचीSYNC(new_dir)) अणु
		err = fat_sync_inode(old_inode);
		अगर (err)
			जाओ error_inode;
	पूर्ण अन्यथा
		mark_inode_dirty(old_inode);

	अगर (update_करोtकरोt) अणु
		fat_set_start(करोtकरोt_de, MSDOS_I(new_dir)->i_logstart);
		mark_buffer_dirty_inode(करोtकरोt_bh, old_inode);
		अगर (IS_सूचीSYNC(new_dir)) अणु
			err = sync_dirty_buffer(करोtकरोt_bh);
			अगर (err)
				जाओ error_करोtकरोt;
		पूर्ण
		drop_nlink(old_dir);
		अगर (!new_inode)
			inc_nlink(new_dir);
	पूर्ण

	err = fat_हटाओ_entries(old_dir, &old_sinfo);	/* and releases bh */
	old_sinfo.bh = शून्य;
	अगर (err)
		जाओ error_करोtकरोt;
	inode_inc_iversion(old_dir);
	fat_truncate_समय(old_dir, &ts, S_CTIME|S_MTIME);
	अगर (IS_सूचीSYNC(old_dir))
		(व्योम)fat_sync_inode(old_dir);
	अन्यथा
		mark_inode_dirty(old_dir);

	अगर (new_inode) अणु
		drop_nlink(new_inode);
		अगर (is_dir)
			drop_nlink(new_inode);
		fat_truncate_समय(new_inode, &ts, S_CTIME);
	पूर्ण
out:
	brअन्यथा(sinfo.bh);
	brअन्यथा(करोtकरोt_bh);
	brअन्यथा(old_sinfo.bh);
	वापस err;

error_करोtकरोt:
	/* data cluster is shared, serious corruption */
	corrupt = 1;

	अगर (update_करोtकरोt) अणु
		fat_set_start(करोtकरोt_de, MSDOS_I(old_dir)->i_logstart);
		mark_buffer_dirty_inode(करोtकरोt_bh, old_inode);
		corrupt |= sync_dirty_buffer(करोtकरोt_bh);
	पूर्ण
error_inode:
	fat_detach(old_inode);
	fat_attach(old_inode, old_sinfo.i_pos);
	MSDOS_I(old_inode)->i_attrs = old_attrs;
	अगर (new_inode) अणु
		fat_attach(new_inode, new_i_pos);
		अगर (corrupt)
			corrupt |= fat_sync_inode(new_inode);
	पूर्ण अन्यथा अणु
		/*
		 * If new entry was not sharing the data cluster, it
		 * shouldn't be serious corruption.
		 */
		पूर्णांक err2 = fat_हटाओ_entries(new_dir, &sinfo);
		अगर (corrupt)
			corrupt |= err2;
		sinfo.bh = शून्य;
	पूर्ण
	अगर (corrupt < 0) अणु
		fat_fs_error(new_dir->i_sb,
			     "%s: Filesystem corrupted (i_pos %lld)",
			     __func__, sinfo.i_pos);
	पूर्ण
	जाओ out;
पूर्ण

/***** Rename, a wrapper क्रम नाम_same_dir & नाम_dअगरf_dir */
अटल पूर्णांक msकरोs_नाम(काष्ठा user_namespace *mnt_userns,
			काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			अचिन्हित पूर्णांक flags)
अणु
	काष्ठा super_block *sb = old_dir->i_sb;
	अचिन्हित अक्षर old_msकरोs_name[MSDOS_NAME], new_msकरोs_name[MSDOS_NAME];
	पूर्णांक err, is_hid;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	mutex_lock(&MSDOS_SB(sb)->s_lock);

	err = msकरोs_क्रमmat_name(old_dentry->d_name.name,
				old_dentry->d_name.len, old_msकरोs_name,
				&MSDOS_SB(old_dir->i_sb)->options);
	अगर (err)
		जाओ out;
	err = msकरोs_क्रमmat_name(new_dentry->d_name.name,
				new_dentry->d_name.len, new_msकरोs_name,
				&MSDOS_SB(new_dir->i_sb)->options);
	अगर (err)
		जाओ out;

	is_hid =
	     (new_dentry->d_name.name[0] == '.') && (new_msdos_name[0] != '.');

	err = करो_msकरोs_नाम(old_dir, old_msकरोs_name, old_dentry,
			      new_dir, new_msकरोs_name, new_dentry, is_hid);
out:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	अगर (!err)
		err = fat_flush_inodes(sb, old_dir, new_dir);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा inode_operations msकरोs_dir_inode_operations = अणु
	.create		= msकरोs_create,
	.lookup		= msकरोs_lookup,
	.unlink		= msकरोs_unlink,
	.सूची_गढ़ो		= msकरोs_सूची_गढ़ो,
	.सूची_हटाओ		= msकरोs_सूची_हटाओ,
	.नाम		= msकरोs_नाम,
	.setattr	= fat_setattr,
	.getattr	= fat_getattr,
	.update_समय	= fat_update_समय,
पूर्ण;

अटल व्योम setup(काष्ठा super_block *sb)
अणु
	MSDOS_SB(sb)->dir_ops = &msकरोs_dir_inode_operations;
	sb->s_d_op = &msकरोs_dentry_operations;
	sb->s_flags |= SB_NOATIME;
पूर्ण

अटल पूर्णांक msकरोs_fill_super(काष्ठा super_block *sb, व्योम *data, पूर्णांक silent)
अणु
	वापस fat_fill_super(sb, data, silent, 0, setup);
पूर्ण

अटल काष्ठा dentry *msकरोs_mount(काष्ठा file_प्रणाली_type *fs_type,
			पूर्णांक flags, स्थिर अक्षर *dev_name,
			व्योम *data)
अणु
	वापस mount_bdev(fs_type, flags, dev_name, data, msकरोs_fill_super);
पूर्ण

अटल काष्ठा file_प्रणाली_type msकरोs_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "msdos",
	.mount		= msकरोs_mount,
	.समाप्त_sb	= समाप्त_block_super,
	.fs_flags	= FS_REQUIRES_DEV | FS_ALLOW_IDMAP,
पूर्ण;
MODULE_ALIAS_FS("msdos");

अटल पूर्णांक __init init_msकरोs_fs(व्योम)
अणु
	वापस रेजिस्टर_fileप्रणाली(&msकरोs_fs_type);
पूर्ण

अटल व्योम __निकास निकास_msकरोs_fs(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&msकरोs_fs_type);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Werner Almesberger");
MODULE_DESCRIPTION("MS-DOS filesystem support");

module_init(init_msकरोs_fs)
module_निकास(निकास_msकरोs_fs)
