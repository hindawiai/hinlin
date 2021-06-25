<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/fs/adfs/inode.c
 *
 *  Copyright (C) 1997-1999 Russell King
 */
#समावेश <linux/buffer_head.h>
#समावेश <linux/ग_लिखोback.h>
#समावेश "adfs.h"

/*
 * Lookup/Create a block at offset 'block' into 'inode'.  We currently करो
 * not support creation of new blocks, so we वापस -EIO क्रम this हाल.
 */
अटल पूर्णांक
adfs_get_block(काष्ठा inode *inode, sector_t block, काष्ठा buffer_head *bh,
	       पूर्णांक create)
अणु
	अगर (!create) अणु
		अगर (block >= inode->i_blocks)
			जाओ पात_toobig;

		block = __adfs_block_map(inode->i_sb, ADFS_I(inode)->indaddr,
					 block);
		अगर (block)
			map_bh(bh, inode->i_sb, block);
		वापस 0;
	पूर्ण
	/* करोn't support allocation of blocks yet */
	वापस -EIO;

पात_toobig:
	वापस 0;
पूर्ण

अटल पूर्णांक adfs_ग_लिखोpage(काष्ठा page *page, काष्ठा ग_लिखोback_control *wbc)
अणु
	वापस block_ग_लिखो_full_page(page, adfs_get_block, wbc);
पूर्ण

अटल पूर्णांक adfs_पढ़ोpage(काष्ठा file *file, काष्ठा page *page)
अणु
	वापस block_पढ़ो_full_page(page, adfs_get_block);
पूर्ण

अटल व्योम adfs_ग_लिखो_failed(काष्ठा address_space *mapping, loff_t to)
अणु
	काष्ठा inode *inode = mapping->host;

	अगर (to > inode->i_size)
		truncate_pagecache(inode, inode->i_size);
पूर्ण

अटल पूर्णांक adfs_ग_लिखो_begin(काष्ठा file *file, काष्ठा address_space *mapping,
			loff_t pos, अचिन्हित len, अचिन्हित flags,
			काष्ठा page **pagep, व्योम **fsdata)
अणु
	पूर्णांक ret;

	*pagep = शून्य;
	ret = cont_ग_लिखो_begin(file, mapping, pos, len, flags, pagep, fsdata,
				adfs_get_block,
				&ADFS_I(mapping->host)->mmu_निजी);
	अगर (unlikely(ret))
		adfs_ग_लिखो_failed(mapping, pos + len);

	वापस ret;
पूर्ण

अटल sector_t _adfs_bmap(काष्ठा address_space *mapping, sector_t block)
अणु
	वापस generic_block_bmap(mapping, block, adfs_get_block);
पूर्ण

अटल स्थिर काष्ठा address_space_operations adfs_aops = अणु
	.पढ़ोpage	= adfs_पढ़ोpage,
	.ग_लिखोpage	= adfs_ग_लिखोpage,
	.ग_लिखो_begin	= adfs_ग_लिखो_begin,
	.ग_लिखो_end	= generic_ग_लिखो_end,
	.bmap		= _adfs_bmap
पूर्ण;

/*
 * Convert ADFS attributes and filetype to Linux permission.
 */
अटल umode_t
adfs_atts2mode(काष्ठा super_block *sb, काष्ठा inode *inode)
अणु
	अचिन्हित पूर्णांक attr = ADFS_I(inode)->attr;
	umode_t mode, rmask;
	काष्ठा adfs_sb_info *asb = ADFS_SB(sb);

	अगर (attr & ADFS_NDA_सूचीECTORY) अणु
		mode = S_IRUGO & asb->s_owner_mask;
		वापस S_IFसूची | S_IXUGO | mode;
	पूर्ण

	चयन (adfs_filetype(ADFS_I(inode)->loadaddr)) अणु
	हाल 0xfc0:	/* LinkFS */
		वापस S_IFLNK|S_IRWXUGO;

	हाल 0xfe6:	/* UnixExec */
		rmask = S_IRUGO | S_IXUGO;
		अवरोध;

	शेष:
		rmask = S_IRUGO;
	पूर्ण

	mode = S_IFREG;

	अगर (attr & ADFS_NDA_OWNER_READ)
		mode |= rmask & asb->s_owner_mask;

	अगर (attr & ADFS_NDA_OWNER_WRITE)
		mode |= S_IWUGO & asb->s_owner_mask;

	अगर (attr & ADFS_NDA_PUBLIC_READ)
		mode |= rmask & asb->s_other_mask;

	अगर (attr & ADFS_NDA_PUBLIC_WRITE)
		mode |= S_IWUGO & asb->s_other_mask;
	वापस mode;
पूर्ण

/*
 * Convert Linux permission to ADFS attribute.  We try to करो the reverse
 * of atts2mode, but there is not a 1:1 translation.
 */
अटल पूर्णांक adfs_mode2atts(काष्ठा super_block *sb, काष्ठा inode *inode,
			  umode_t ia_mode)
अणु
	काष्ठा adfs_sb_info *asb = ADFS_SB(sb);
	umode_t mode;
	पूर्णांक attr;

	/* FIXME: should we be able to alter a link? */
	अगर (S_ISLNK(inode->i_mode))
		वापस ADFS_I(inode)->attr;

	/* Directories करो not have पढ़ो/ग_लिखो permissions on the media */
	अगर (S_ISसूची(inode->i_mode))
		वापस ADFS_NDA_सूचीECTORY;

	attr = 0;
	mode = ia_mode & asb->s_owner_mask;
	अगर (mode & S_IRUGO)
		attr |= ADFS_NDA_OWNER_READ;
	अगर (mode & S_IWUGO)
		attr |= ADFS_NDA_OWNER_WRITE;

	mode = ia_mode & asb->s_other_mask;
	mode &= ~asb->s_owner_mask;
	अगर (mode & S_IRUGO)
		attr |= ADFS_NDA_PUBLIC_READ;
	अगर (mode & S_IWUGO)
		attr |= ADFS_NDA_PUBLIC_WRITE;

	वापस attr;
पूर्ण

अटल स्थिर s64 nsec_unix_epoch_dअगरf_risc_os_epoch = 2208988800000000000LL;

/*
 * Convert an ADFS समय to Unix समय.  ADFS has a 40-bit centi-second समय
 * referenced to 1 Jan 1900 (til 2248) so we need to discard 2208988800 seconds
 * of समय to convert from RISC OS epoch to Unix epoch.
 */
अटल व्योम
adfs_adfs2unix_समय(काष्ठा बारpec64 *tv, काष्ठा inode *inode)
अणु
	अचिन्हित पूर्णांक high, low;
	/* 01 Jan 1970 00:00:00 (Unix epoch) as nanoseconds since
	 * 01 Jan 1900 00:00:00 (RISC OS epoch)
	 */
	s64 nsec;

	अगर (!adfs_inode_is_stamped(inode))
		जाओ cur_समय;

	high = ADFS_I(inode)->loadaddr & 0xFF; /* top 8 bits of बारtamp */
	low  = ADFS_I(inode)->execaddr;    /* bottom 32 bits of बारtamp */

	/* convert 40-bit centi-seconds to 32-bit seconds
	 * going via nanoseconds to retain precision
	 */
	nsec = (((s64) high << 32) | (s64) low) * 10000000; /* cs to ns */

	/* Files dated pre  01 Jan 1970 00:00:00. */
	अगर (nsec < nsec_unix_epoch_dअगरf_risc_os_epoch)
		जाओ too_early;

	/* convert from RISC OS to Unix epoch */
	nsec -= nsec_unix_epoch_dअगरf_risc_os_epoch;

	*tv = ns_to_बारpec64(nsec);
	वापस;

 cur_समय:
	*tv = current_समय(inode);
	वापस;

 too_early:
	tv->tv_sec = tv->tv_nsec = 0;
	वापस;
पूर्ण

/* Convert an Unix समय to ADFS समय क्रम an entry that is alपढ़ोy stamped. */
अटल व्योम adfs_unix2adfs_समय(काष्ठा inode *inode,
				स्थिर काष्ठा बारpec64 *ts)
अणु
	s64 cs, nsec = बारpec64_to_ns(ts);

	/* convert from Unix to RISC OS epoch */
	nsec += nsec_unix_epoch_dअगरf_risc_os_epoch;

	/* convert from nanoseconds to centiseconds */
	cs = भाग_s64(nsec, 10000000);

	cs = clamp_t(s64, cs, 0, 0xffffffffff);

	ADFS_I(inode)->loadaddr &= ~0xff;
	ADFS_I(inode)->loadaddr |= (cs >> 32) & 0xff;
	ADFS_I(inode)->execaddr = cs;
पूर्ण

/*
 * Fill in the inode inक्रमmation from the object inक्रमmation.
 *
 * Note that this is an inode-less fileप्रणाली, so we can't use the inode
 * number to reference the metadata on the media.  Instead, we use the
 * inode number to hold the object ID, which in turn will tell us where
 * the data is held.  We also save the parent object ID, and with these
 * two, we can locate the metadata.
 *
 * This करोes mean that we rely on an objects parent reमुख्यing the same at
 * all बार - we cannot cope with a cross-directory नाम (yet).
 */
काष्ठा inode *
adfs_iget(काष्ठा super_block *sb, काष्ठा object_info *obj)
अणु
	काष्ठा inode *inode;

	inode = new_inode(sb);
	अगर (!inode)
		जाओ out;

	inode->i_uid	 = ADFS_SB(sb)->s_uid;
	inode->i_gid	 = ADFS_SB(sb)->s_gid;
	inode->i_ino	 = obj->indaddr;
	inode->i_size	 = obj->size;
	set_nlink(inode, 2);
	inode->i_blocks	 = (inode->i_size + sb->s_blocksize - 1) >>
			    sb->s_blocksize_bits;

	/*
	 * we need to save the parent directory ID so that
	 * ग_लिखो_inode can update the directory inक्रमmation
	 * क्रम this file.  This will need special handling
	 * क्रम cross-directory नामs.
	 */
	ADFS_I(inode)->parent_id = obj->parent_id;
	ADFS_I(inode)->indaddr   = obj->indaddr;
	ADFS_I(inode)->loadaddr  = obj->loadaddr;
	ADFS_I(inode)->execaddr  = obj->execaddr;
	ADFS_I(inode)->attr      = obj->attr;

	inode->i_mode	 = adfs_atts2mode(sb, inode);
	adfs_adfs2unix_समय(&inode->i_mसमय, inode);
	inode->i_aसमय = inode->i_mसमय;
	inode->i_स_समय = inode->i_mसमय;

	अगर (S_ISसूची(inode->i_mode)) अणु
		inode->i_op	= &adfs_dir_inode_operations;
		inode->i_fop	= &adfs_dir_operations;
	पूर्ण अन्यथा अगर (S_ISREG(inode->i_mode)) अणु
		inode->i_op	= &adfs_file_inode_operations;
		inode->i_fop	= &adfs_file_operations;
		inode->i_mapping->a_ops = &adfs_aops;
		ADFS_I(inode)->mmu_निजी = inode->i_size;
	पूर्ण

	inode_fake_hash(inode);

out:
	वापस inode;
पूर्ण

/*
 * Validate and convert a changed access mode/समय to their ADFS equivalents.
 * adfs_ग_लिखो_inode will actually ग_लिखो the inक्रमmation back to the directory
 * later.
 */
पूर्णांक
adfs_notअगरy_change(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		   काष्ठा iattr *attr)
अणु
	काष्ठा inode *inode = d_inode(dentry);
	काष्ठा super_block *sb = inode->i_sb;
	अचिन्हित पूर्णांक ia_valid = attr->ia_valid;
	पूर्णांक error;
	
	error = setattr_prepare(&init_user_ns, dentry, attr);

	/*
	 * we can't change the UID or GID of any file -
	 * we have a global UID/GID in the superblock
	 */
	अगर ((ia_valid & ATTR_UID && !uid_eq(attr->ia_uid, ADFS_SB(sb)->s_uid)) ||
	    (ia_valid & ATTR_GID && !gid_eq(attr->ia_gid, ADFS_SB(sb)->s_gid)))
		error = -EPERM;

	अगर (error)
		जाओ out;

	/* XXX: this is missing some actual on-disk truncation.. */
	अगर (ia_valid & ATTR_SIZE)
		truncate_setsize(inode, attr->ia_size);

	अगर (ia_valid & ATTR_MTIME && adfs_inode_is_stamped(inode)) अणु
		adfs_unix2adfs_समय(inode, &attr->ia_mसमय);
		adfs_adfs2unix_समय(&inode->i_mसमय, inode);
	पूर्ण

	/*
	 * FIXME: should we make these == to i_mसमय since we करोn't
	 * have the ability to represent them in our fileप्रणाली?
	 */
	अगर (ia_valid & ATTR_ATIME)
		inode->i_aसमय = attr->ia_aसमय;
	अगर (ia_valid & ATTR_CTIME)
		inode->i_स_समय = attr->ia_स_समय;
	अगर (ia_valid & ATTR_MODE) अणु
		ADFS_I(inode)->attr = adfs_mode2atts(sb, inode, attr->ia_mode);
		inode->i_mode = adfs_atts2mode(sb, inode);
	पूर्ण

	/*
	 * FIXME: should we be marking this inode dirty even अगर
	 * we करोn't have any metadata to ग_लिखो back?
	 */
	अगर (ia_valid & (ATTR_SIZE | ATTR_MTIME | ATTR_MODE))
		mark_inode_dirty(inode);
out:
	वापस error;
पूर्ण

/*
 * ग_लिखो an existing inode back to the directory, and thereक्रमe the disk.
 * The adfs-specअगरic inode data has alपढ़ोy been updated by
 * adfs_notअगरy_change()
 */
पूर्णांक adfs_ग_लिखो_inode(काष्ठा inode *inode, काष्ठा ग_लिखोback_control *wbc)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा object_info obj;
	पूर्णांक ret;

	obj.indaddr	= ADFS_I(inode)->indaddr;
	obj.name_len	= 0;
	obj.parent_id	= ADFS_I(inode)->parent_id;
	obj.loadaddr	= ADFS_I(inode)->loadaddr;
	obj.execaddr	= ADFS_I(inode)->execaddr;
	obj.attr	= ADFS_I(inode)->attr;
	obj.size	= inode->i_size;

	ret = adfs_dir_update(sb, &obj, wbc->sync_mode == WB_SYNC_ALL);
	वापस ret;
पूर्ण
