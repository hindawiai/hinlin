<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 *   Portions Copyright (C) Christoph Hellwig, 2001-2002
 */

#समावेश <linux/fs.h>
#समावेश <linux/namei.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/quotaops.h>
#समावेश <linux/exportfs.h>
#समावेश "jfs_incore.h"
#समावेश "jfs_superblock.h"
#समावेश "jfs_inode.h"
#समावेश "jfs_dinode.h"
#समावेश "jfs_dmap.h"
#समावेश "jfs_unicode.h"
#समावेश "jfs_metapage.h"
#समावेश "jfs_xattr.h"
#समावेश "jfs_acl.h"
#समावेश "jfs_debug.h"

/*
 * क्रमward references
 */
स्थिर काष्ठा dentry_operations jfs_ci_dentry_operations;

अटल s64 commitZeroLink(tid_t, काष्ठा inode *);

/*
 * NAME:	मुक्त_ea_wmap(inode)
 *
 * FUNCTION:	मुक्त uncommitted extended attributes from working map
 *
 */
अटल अंतरभूत व्योम मुक्त_ea_wmap(काष्ठा inode *inode)
अणु
	dxd_t *ea = &JFS_IP(inode)->ea;

	अगर (ea->flag & DXD_EXTENT) अणु
		/* मुक्त EA pages from cache */
		invalidate_dxd_metapages(inode, *ea);
		dbFree(inode, addressDXD(ea), lengthDXD(ea));
	पूर्ण
	ea->flag = 0;
पूर्ण

/*
 * NAME:	jfs_create(dip, dentry, mode)
 *
 * FUNCTION:	create a regular file in the parent directory <dip>
 *		with name = <from dentry> and mode = <mode>
 *
 * PARAMETER:	dip	- parent directory vnode
 *		dentry	- dentry of new file
 *		mode	- create mode (rwxrwxrwx).
 *		nd- nd काष्ठा
 *
 * RETURN:	Errors from subroutines
 *
 */
अटल पूर्णांक jfs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dip,
		      काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	पूर्णांक rc = 0;
	tid_t tid;		/* transaction id */
	काष्ठा inode *ip = शून्य;	/* child directory inode */
	ino_t ino;
	काष्ठा component_name dname;	/* child directory name */
	काष्ठा btstack btstack;
	काष्ठा inode *iplist[2];
	काष्ठा tblock *tblk;

	jfs_info("jfs_create: dip:0x%p name:%pd", dip, dentry);

	rc = dquot_initialize(dip);
	अगर (rc)
		जाओ out1;

	/*
	 * search parent directory क्रम entry/मुक्तspace
	 * (dtSearch() वापसs parent directory page pinned)
	 */
	अगर ((rc = get_UCSname(&dname, dentry)))
		जाओ out1;

	/*
	 * Either iAlloc() or txBegin() may block.  Deadlock can occur अगर we
	 * block there जबतक holding dtree page, so we allocate the inode &
	 * begin the transaction beक्रमe we search the directory.
	 */
	ip = ialloc(dip, mode);
	अगर (IS_ERR(ip)) अणु
		rc = PTR_ERR(ip);
		जाओ out2;
	पूर्ण

	tid = txBegin(dip->i_sb, 0);

	mutex_lock_nested(&JFS_IP(dip)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHILD);

	rc = jfs_init_acl(tid, ip, dip);
	अगर (rc)
		जाओ out3;

	rc = jfs_init_security(tid, ip, dip, &dentry->d_name);
	अगर (rc) अणु
		txAbort(tid, 0);
		जाओ out3;
	पूर्ण

	अगर ((rc = dtSearch(dip, &dname, &ino, &btstack, JFS_CREATE))) अणु
		jfs_err("jfs_create: dtSearch returned %d", rc);
		txAbort(tid, 0);
		जाओ out3;
	पूर्ण

	tblk = tid_to_tblock(tid);
	tblk->xflag |= COMMIT_CREATE;
	tblk->ino = ip->i_ino;
	tblk->u.ixpxd = JFS_IP(ip)->ixpxd;

	iplist[0] = dip;
	iplist[1] = ip;

	/*
	 * initialize the child XAD tree root in-line in inode
	 */
	xtInitRoot(tid, ip);

	/*
	 * create entry in parent directory क्रम child directory
	 * (dtInsert() releases parent directory page)
	 */
	ino = ip->i_ino;
	अगर ((rc = dtInsert(tid, dip, &dname, &ino, &btstack))) अणु
		अगर (rc == -EIO) अणु
			jfs_err("jfs_create: dtInsert returned -EIO");
			txAbort(tid, 1);	/* Marks Fileप्रणाली dirty */
		पूर्ण अन्यथा
			txAbort(tid, 0);	/* Fileप्रणाली full */
		जाओ out3;
	पूर्ण

	ip->i_op = &jfs_file_inode_operations;
	ip->i_fop = &jfs_file_operations;
	ip->i_mapping->a_ops = &jfs_aops;

	mark_inode_dirty(ip);

	dip->i_स_समय = dip->i_mसमय = current_समय(dip);

	mark_inode_dirty(dip);

	rc = txCommit(tid, 2, &iplist[0], 0);

      out3:
	txEnd(tid);
	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	mutex_unlock(&JFS_IP(dip)->commit_mutex);
	अगर (rc) अणु
		मुक्त_ea_wmap(ip);
		clear_nlink(ip);
		discard_new_inode(ip);
	पूर्ण अन्यथा अणु
		d_instantiate_new(dentry, ip);
	पूर्ण

      out2:
	मुक्त_UCSname(&dname);

      out1:

	jfs_info("jfs_create: rc:%d", rc);
	वापस rc;
पूर्ण


/*
 * NAME:	jfs_सूची_गढ़ो(dip, dentry, mode)
 *
 * FUNCTION:	create a child directory in the parent directory <dip>
 *		with name = <from dentry> and mode = <mode>
 *
 * PARAMETER:	dip	- parent directory vnode
 *		dentry	- dentry of child directory
 *		mode	- create mode (rwxrwxrwx).
 *
 * RETURN:	Errors from subroutines
 *
 * note:
 * EACCES: user needs search+ग_लिखो permission on the parent directory
 */
अटल पूर्णांक jfs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dip,
		     काष्ठा dentry *dentry, umode_t mode)
अणु
	पूर्णांक rc = 0;
	tid_t tid;		/* transaction id */
	काष्ठा inode *ip = शून्य;	/* child directory inode */
	ino_t ino;
	काष्ठा component_name dname;	/* child directory name */
	काष्ठा btstack btstack;
	काष्ठा inode *iplist[2];
	काष्ठा tblock *tblk;

	jfs_info("jfs_mkdir: dip:0x%p name:%pd", dip, dentry);

	rc = dquot_initialize(dip);
	अगर (rc)
		जाओ out1;

	/*
	 * search parent directory क्रम entry/मुक्तspace
	 * (dtSearch() वापसs parent directory page pinned)
	 */
	अगर ((rc = get_UCSname(&dname, dentry)))
		जाओ out1;

	/*
	 * Either iAlloc() or txBegin() may block.  Deadlock can occur अगर we
	 * block there जबतक holding dtree page, so we allocate the inode &
	 * begin the transaction beक्रमe we search the directory.
	 */
	ip = ialloc(dip, S_IFसूची | mode);
	अगर (IS_ERR(ip)) अणु
		rc = PTR_ERR(ip);
		जाओ out2;
	पूर्ण

	tid = txBegin(dip->i_sb, 0);

	mutex_lock_nested(&JFS_IP(dip)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHILD);

	rc = jfs_init_acl(tid, ip, dip);
	अगर (rc)
		जाओ out3;

	rc = jfs_init_security(tid, ip, dip, &dentry->d_name);
	अगर (rc) अणु
		txAbort(tid, 0);
		जाओ out3;
	पूर्ण

	अगर ((rc = dtSearch(dip, &dname, &ino, &btstack, JFS_CREATE))) अणु
		jfs_err("jfs_mkdir: dtSearch returned %d", rc);
		txAbort(tid, 0);
		जाओ out3;
	पूर्ण

	tblk = tid_to_tblock(tid);
	tblk->xflag |= COMMIT_CREATE;
	tblk->ino = ip->i_ino;
	tblk->u.ixpxd = JFS_IP(ip)->ixpxd;

	iplist[0] = dip;
	iplist[1] = ip;

	/*
	 * initialize the child directory in-line in inode
	 */
	dtInitRoot(tid, ip, dip->i_ino);

	/*
	 * create entry in parent directory क्रम child directory
	 * (dtInsert() releases parent directory page)
	 */
	ino = ip->i_ino;
	अगर ((rc = dtInsert(tid, dip, &dname, &ino, &btstack))) अणु
		अगर (rc == -EIO) अणु
			jfs_err("jfs_mkdir: dtInsert returned -EIO");
			txAbort(tid, 1);	/* Marks Fileप्रणाली dirty */
		पूर्ण अन्यथा
			txAbort(tid, 0);	/* Fileप्रणाली full */
		जाओ out3;
	पूर्ण

	set_nlink(ip, 2);	/* क्रम '.' */
	ip->i_op = &jfs_dir_inode_operations;
	ip->i_fop = &jfs_dir_operations;

	mark_inode_dirty(ip);

	/* update parent directory inode */
	inc_nlink(dip);		/* क्रम '..' from child directory */
	dip->i_स_समय = dip->i_mसमय = current_समय(dip);
	mark_inode_dirty(dip);

	rc = txCommit(tid, 2, &iplist[0], 0);

      out3:
	txEnd(tid);
	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	mutex_unlock(&JFS_IP(dip)->commit_mutex);
	अगर (rc) अणु
		मुक्त_ea_wmap(ip);
		clear_nlink(ip);
		discard_new_inode(ip);
	पूर्ण अन्यथा अणु
		d_instantiate_new(dentry, ip);
	पूर्ण

      out2:
	मुक्त_UCSname(&dname);


      out1:

	jfs_info("jfs_mkdir: rc:%d", rc);
	वापस rc;
पूर्ण

/*
 * NAME:	jfs_सूची_हटाओ(dip, dentry)
 *
 * FUNCTION:	हटाओ a link to child directory
 *
 * PARAMETER:	dip	- parent inode
 *		dentry	- child directory dentry
 *
 * RETURN:	-EINVAL	- अगर name is . or ..
 *		-EINVAL - अगर . or .. exist but are invalid.
 *		errors from subroutines
 *
 * note:
 * अगर other thपढ़ोs have the directory खोलो when the last link
 * is हटाओd, the "." and ".." entries, अगर present, are हटाओd beक्रमe
 * सूची_हटाओ() वापसs and no new entries may be created in the directory,
 * but the directory is not हटाओd until the last reference to
 * the directory is released (cf.unlink() of regular file).
 */
अटल पूर्णांक jfs_सूची_हटाओ(काष्ठा inode *dip, काष्ठा dentry *dentry)
अणु
	पूर्णांक rc;
	tid_t tid;		/* transaction id */
	काष्ठा inode *ip = d_inode(dentry);
	ino_t ino;
	काष्ठा component_name dname;
	काष्ठा inode *iplist[2];
	काष्ठा tblock *tblk;

	jfs_info("jfs_rmdir: dip:0x%p name:%pd", dip, dentry);

	/* Init inode क्रम quota operations. */
	rc = dquot_initialize(dip);
	अगर (rc)
		जाओ out;
	rc = dquot_initialize(ip);
	अगर (rc)
		जाओ out;

	/* directory must be empty to be हटाओd */
	अगर (!dtEmpty(ip)) अणु
		rc = -ENOTEMPTY;
		जाओ out;
	पूर्ण

	अगर ((rc = get_UCSname(&dname, dentry))) अणु
		जाओ out;
	पूर्ण

	tid = txBegin(dip->i_sb, 0);

	mutex_lock_nested(&JFS_IP(dip)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHILD);

	iplist[0] = dip;
	iplist[1] = ip;

	tblk = tid_to_tblock(tid);
	tblk->xflag |= COMMIT_DELETE;
	tblk->u.ip = ip;

	/*
	 * delete the entry of target directory from parent directory
	 */
	ino = ip->i_ino;
	अगर ((rc = dtDelete(tid, dip, &dname, &ino, JFS_REMOVE))) अणु
		jfs_err("jfs_rmdir: dtDelete returned %d", rc);
		अगर (rc == -EIO)
			txAbort(tid, 1);
		txEnd(tid);
		mutex_unlock(&JFS_IP(ip)->commit_mutex);
		mutex_unlock(&JFS_IP(dip)->commit_mutex);

		जाओ out2;
	पूर्ण

	/* update parent directory's link count corresponding
	 * to ".." entry of the target directory deleted
	 */
	dip->i_स_समय = dip->i_mसमय = current_समय(dip);
	inode_dec_link_count(dip);

	/*
	 * OS/2 could have created EA and/or ACL
	 */
	/* मुक्त EA from both persistent and working map */
	अगर (JFS_IP(ip)->ea.flag & DXD_EXTENT) अणु
		/* मुक्त EA pages */
		txEA(tid, ip, &JFS_IP(ip)->ea, शून्य);
	पूर्ण
	JFS_IP(ip)->ea.flag = 0;

	/* मुक्त ACL from both persistent and working map */
	अगर (JFS_IP(ip)->acl.flag & DXD_EXTENT) अणु
		/* मुक्त ACL pages */
		txEA(tid, ip, &JFS_IP(ip)->acl, शून्य);
	पूर्ण
	JFS_IP(ip)->acl.flag = 0;

	/* mark the target directory as deleted */
	clear_nlink(ip);
	mark_inode_dirty(ip);

	rc = txCommit(tid, 2, &iplist[0], 0);

	txEnd(tid);

	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	mutex_unlock(&JFS_IP(dip)->commit_mutex);

	/*
	 * Truncating the directory index table is not guaranteed.  It
	 * may need to be करोne iteratively
	 */
	अगर (test_cflag(COMMIT_Stale, dip)) अणु
		अगर (dip->i_size > 1)
			jfs_truncate_nolock(dip, 0);

		clear_cflag(COMMIT_Stale, dip);
	पूर्ण

      out2:
	मुक्त_UCSname(&dname);

      out:
	jfs_info("jfs_rmdir: rc:%d", rc);
	वापस rc;
पूर्ण

/*
 * NAME:	jfs_unlink(dip, dentry)
 *
 * FUNCTION:	हटाओ a link to object <vp> named by <name>
 *		from parent directory <dvp>
 *
 * PARAMETER:	dip	- inode of parent directory
 *		dentry	- dentry of object to be हटाओd
 *
 * RETURN:	errors from subroutines
 *
 * note:
 * temporary file: अगर one or more processes have the file खोलो
 * when the last link is हटाओd, the link will be हटाओd beक्रमe
 * unlink() वापसs, but the removal of the file contents will be
 * postponed until all references to the files are बंदd.
 *
 * JFS करोes NOT support unlink() on directories.
 *
 */
अटल पूर्णांक jfs_unlink(काष्ठा inode *dip, काष्ठा dentry *dentry)
अणु
	पूर्णांक rc;
	tid_t tid;		/* transaction id */
	काष्ठा inode *ip = d_inode(dentry);
	ino_t ino;
	काष्ठा component_name dname;	/* object name */
	काष्ठा inode *iplist[2];
	काष्ठा tblock *tblk;
	s64 new_size = 0;
	पूर्णांक commit_flag;

	jfs_info("jfs_unlink: dip:0x%p name:%pd", dip, dentry);

	/* Init inode क्रम quota operations. */
	rc = dquot_initialize(dip);
	अगर (rc)
		जाओ out;
	rc = dquot_initialize(ip);
	अगर (rc)
		जाओ out;

	अगर ((rc = get_UCSname(&dname, dentry)))
		जाओ out;

	IWRITE_LOCK(ip, RDWRLOCK_NORMAL);

	tid = txBegin(dip->i_sb, 0);

	mutex_lock_nested(&JFS_IP(dip)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHILD);

	iplist[0] = dip;
	iplist[1] = ip;

	/*
	 * delete the entry of target file from parent directory
	 */
	ino = ip->i_ino;
	अगर ((rc = dtDelete(tid, dip, &dname, &ino, JFS_REMOVE))) अणु
		jfs_err("jfs_unlink: dtDelete returned %d", rc);
		अगर (rc == -EIO)
			txAbort(tid, 1);	/* Marks FS Dirty */
		txEnd(tid);
		mutex_unlock(&JFS_IP(ip)->commit_mutex);
		mutex_unlock(&JFS_IP(dip)->commit_mutex);
		IWRITE_UNLOCK(ip);
		जाओ out1;
	पूर्ण

	ASSERT(ip->i_nlink);

	ip->i_स_समय = dip->i_स_समय = dip->i_mसमय = current_समय(ip);
	mark_inode_dirty(dip);

	/* update target's inode */
	inode_dec_link_count(ip);

	/*
	 *	commit zero link count object
	 */
	अगर (ip->i_nlink == 0) अणु
		निश्चित(!test_cflag(COMMIT_Nolink, ip));
		/* मुक्त block resources */
		अगर ((new_size = commitZeroLink(tid, ip)) < 0) अणु
			txAbort(tid, 1);	/* Marks FS Dirty */
			txEnd(tid);
			mutex_unlock(&JFS_IP(ip)->commit_mutex);
			mutex_unlock(&JFS_IP(dip)->commit_mutex);
			IWRITE_UNLOCK(ip);
			rc = new_size;
			जाओ out1;
		पूर्ण
		tblk = tid_to_tblock(tid);
		tblk->xflag |= COMMIT_DELETE;
		tblk->u.ip = ip;
	पूर्ण

	/*
	 * Incomplete truncate of file data can
	 * result in timing problems unless we synchronously commit the
	 * transaction.
	 */
	अगर (new_size)
		commit_flag = COMMIT_SYNC;
	अन्यथा
		commit_flag = 0;

	/*
	 * If xtTruncate was incomplete, commit synchronously to aव्योम
	 * timing complications
	 */
	rc = txCommit(tid, 2, &iplist[0], commit_flag);

	txEnd(tid);

	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	mutex_unlock(&JFS_IP(dip)->commit_mutex);

	जबतक (new_size && (rc == 0)) अणु
		tid = txBegin(dip->i_sb, 0);
		mutex_lock(&JFS_IP(ip)->commit_mutex);
		new_size = xtTruncate_pmap(tid, ip, new_size);
		अगर (new_size < 0) अणु
			txAbort(tid, 1);	/* Marks FS Dirty */
			rc = new_size;
		पूर्ण अन्यथा
			rc = txCommit(tid, 2, &iplist[0], COMMIT_SYNC);
		txEnd(tid);
		mutex_unlock(&JFS_IP(ip)->commit_mutex);
	पूर्ण

	अगर (ip->i_nlink == 0)
		set_cflag(COMMIT_Nolink, ip);

	IWRITE_UNLOCK(ip);

	/*
	 * Truncating the directory index table is not guaranteed.  It
	 * may need to be करोne iteratively
	 */
	अगर (test_cflag(COMMIT_Stale, dip)) अणु
		अगर (dip->i_size > 1)
			jfs_truncate_nolock(dip, 0);

		clear_cflag(COMMIT_Stale, dip);
	पूर्ण

      out1:
	मुक्त_UCSname(&dname);
      out:
	jfs_info("jfs_unlink: rc:%d", rc);
	वापस rc;
पूर्ण

/*
 * NAME:	commitZeroLink()
 *
 * FUNCTION:	क्रम non-directory, called by jfs_हटाओ(),
 *		truncate a regular file, directory or symbolic
 *		link to zero length. वापस 0 अगर type is not
 *		one of these.
 *
 *		अगर the file is currently associated with a VM segment
 *		only permanent disk and inode map resources are मुक्तd,
 *		and neither the inode nor indirect blocks are modअगरied
 *		so that the resources can be later मुक्तd in the work
 *		map by ctrunc1.
 *		अगर there is no VM segment on entry, the resources are
 *		मुक्तd in both work and permanent map.
 *		(? क्रम temporary file - memory object is cached even
 *		after no reference:
 *		reference count > 0 -   )
 *
 * PARAMETERS:	cd	- poपूर्णांकer to commit data काष्ठाure.
 *			  current inode is the one to truncate.
 *
 * RETURN:	Errors from subroutines
 */
अटल s64 commitZeroLink(tid_t tid, काष्ठा inode *ip)
अणु
	पूर्णांक filetype;
	काष्ठा tblock *tblk;

	jfs_info("commitZeroLink: tid = %d, ip = 0x%p", tid, ip);

	filetype = ip->i_mode & S_IFMT;
	चयन (filetype) अणु
	हाल S_IFREG:
		अवरोध;
	हाल S_IFLNK:
		/* fast symbolic link */
		अगर (ip->i_size < IDATASIZE) अणु
			ip->i_size = 0;
			वापस 0;
		पूर्ण
		अवरोध;
	शेष:
		निश्चित(filetype != S_IFसूची);
		वापस 0;
	पूर्ण

	set_cflag(COMMIT_Freewmap, ip);

	/* mark transaction of block map update type */
	tblk = tid_to_tblock(tid);
	tblk->xflag |= COMMIT_PMAP;

	/*
	 * मुक्त EA
	 */
	अगर (JFS_IP(ip)->ea.flag & DXD_EXTENT)
		/* acquire maplock on EA to be मुक्तd from block map */
		txEA(tid, ip, &JFS_IP(ip)->ea, शून्य);

	/*
	 * मुक्त ACL
	 */
	अगर (JFS_IP(ip)->acl.flag & DXD_EXTENT)
		/* acquire maplock on EA to be मुक्तd from block map */
		txEA(tid, ip, &JFS_IP(ip)->acl, शून्य);

	/*
	 * मुक्त xtree/data (truncate to zero length):
	 * मुक्त xtree/data pages from cache अगर COMMIT_PWMAP,
	 * मुक्त xtree/data blocks from persistent block map, and
	 * मुक्त xtree/data blocks from working block map अगर COMMIT_PWMAP;
	 */
	अगर (ip->i_size)
		वापस xtTruncate_pmap(tid, ip, 0);

	वापस 0;
पूर्ण


/*
 * NAME:	jfs_मुक्त_zero_link()
 *
 * FUNCTION:	क्रम non-directory, called by iClose(),
 *		मुक्त resources of a file from cache and WORKING map
 *		क्रम a file previously committed with zero link count
 *		जबतक associated with a pager object,
 *
 * PARAMETER:	ip	- poपूर्णांकer to inode of file.
 */
व्योम jfs_मुक्त_zero_link(काष्ठा inode *ip)
अणु
	पूर्णांक type;

	jfs_info("jfs_free_zero_link: ip = 0x%p", ip);

	/* वापस अगर not reg or symbolic link or अगर size is
	 * alपढ़ोy ok.
	 */
	type = ip->i_mode & S_IFMT;

	चयन (type) अणु
	हाल S_IFREG:
		अवरोध;
	हाल S_IFLNK:
		/* अगर its contained in inode nothing to करो */
		अगर (ip->i_size < IDATASIZE)
			वापस;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/*
	 * मुक्त EA
	 */
	अगर (JFS_IP(ip)->ea.flag & DXD_EXTENT) अणु
		s64 xaddr = addressDXD(&JFS_IP(ip)->ea);
		पूर्णांक xlen = lengthDXD(&JFS_IP(ip)->ea);
		काष्ठा maplock maplock;	/* maplock क्रम COMMIT_WMAP */
		काष्ठा pxd_lock *pxdlock;	/* maplock क्रम COMMIT_WMAP */

		/* मुक्त EA pages from cache */
		invalidate_dxd_metapages(ip, JFS_IP(ip)->ea);

		/* मुक्त EA extent from working block map */
		maplock.index = 1;
		pxdlock = (काष्ठा pxd_lock *) & maplock;
		pxdlock->flag = mlckFREEPXD;
		PXDaddress(&pxdlock->pxd, xaddr);
		PXDlength(&pxdlock->pxd, xlen);
		txFreeMap(ip, pxdlock, शून्य, COMMIT_WMAP);
	पूर्ण

	/*
	 * मुक्त ACL
	 */
	अगर (JFS_IP(ip)->acl.flag & DXD_EXTENT) अणु
		s64 xaddr = addressDXD(&JFS_IP(ip)->acl);
		पूर्णांक xlen = lengthDXD(&JFS_IP(ip)->acl);
		काष्ठा maplock maplock;	/* maplock क्रम COMMIT_WMAP */
		काष्ठा pxd_lock *pxdlock;	/* maplock क्रम COMMIT_WMAP */

		invalidate_dxd_metapages(ip, JFS_IP(ip)->acl);

		/* मुक्त ACL extent from working block map */
		maplock.index = 1;
		pxdlock = (काष्ठा pxd_lock *) & maplock;
		pxdlock->flag = mlckFREEPXD;
		PXDaddress(&pxdlock->pxd, xaddr);
		PXDlength(&pxdlock->pxd, xlen);
		txFreeMap(ip, pxdlock, शून्य, COMMIT_WMAP);
	पूर्ण

	/*
	 * मुक्त xtree/data (truncate to zero length):
	 * मुक्त xtree/data pages from cache, and
	 * मुक्त xtree/data blocks from working block map;
	 */
	अगर (ip->i_size)
		xtTruncate(0, ip, 0, COMMIT_WMAP);
पूर्ण

/*
 * NAME:	jfs_link(vp, dvp, name, crp)
 *
 * FUNCTION:	create a link to <vp> by the name = <name>
 *		in the parent directory <dvp>
 *
 * PARAMETER:	vp	- target object
 *		dvp	- parent directory of new link
 *		name	- name of new link to target object
 *		crp	- credential
 *
 * RETURN:	Errors from subroutines
 *
 * note:
 * JFS करोes NOT support link() on directories (to prevent circular
 * path in the directory hierarchy);
 * EPERM: the target object is a directory, and either the caller
 * करोes not have appropriate privileges or the implementation prohibits
 * using link() on directories [XPG4.2].
 *
 * JFS करोes NOT support links between file प्रणालीs:
 * EXDEV: target object and new link are on dअगरferent file प्रणालीs and
 * implementation करोes not support links between file प्रणालीs [XPG4.2].
 */
अटल पूर्णांक jfs_link(काष्ठा dentry *old_dentry,
	     काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	पूर्णांक rc;
	tid_t tid;
	काष्ठा inode *ip = d_inode(old_dentry);
	ino_t ino;
	काष्ठा component_name dname;
	काष्ठा btstack btstack;
	काष्ठा inode *iplist[2];

	jfs_info("jfs_link: %pd %pd", old_dentry, dentry);

	rc = dquot_initialize(dir);
	अगर (rc)
		जाओ out;

	tid = txBegin(ip->i_sb, 0);

	mutex_lock_nested(&JFS_IP(dir)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHILD);

	/*
	 * scan parent directory क्रम entry/मुक्तspace
	 */
	अगर ((rc = get_UCSname(&dname, dentry)))
		जाओ out_tx;

	अगर ((rc = dtSearch(dir, &dname, &ino, &btstack, JFS_CREATE)))
		जाओ मुक्त_dname;

	/*
	 * create entry क्रम new link in parent directory
	 */
	ino = ip->i_ino;
	अगर ((rc = dtInsert(tid, dir, &dname, &ino, &btstack)))
		जाओ मुक्त_dname;

	/* update object inode */
	inc_nlink(ip);		/* क्रम new link */
	ip->i_स_समय = current_समय(ip);
	dir->i_स_समय = dir->i_mसमय = current_समय(dir);
	mark_inode_dirty(dir);
	ihold(ip);

	iplist[0] = ip;
	iplist[1] = dir;
	rc = txCommit(tid, 2, &iplist[0], 0);

	अगर (rc) अणु
		drop_nlink(ip); /* never instantiated */
		iput(ip);
	पूर्ण अन्यथा
		d_instantiate(dentry, ip);

      मुक्त_dname:
	मुक्त_UCSname(&dname);

      out_tx:
	txEnd(tid);

	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	mutex_unlock(&JFS_IP(dir)->commit_mutex);

      out:
	jfs_info("jfs_link: rc:%d", rc);
	वापस rc;
पूर्ण

/*
 * NAME:	jfs_symlink(dip, dentry, name)
 *
 * FUNCTION:	creates a symbolic link to <symlink> by name <name>
 *			in directory <dip>
 *
 * PARAMETER:	dip	- parent directory vnode
 *		dentry	- dentry of symbolic link
 *		name	- the path name of the existing object
 *			  that will be the source of the link
 *
 * RETURN:	errors from subroutines
 *
 * note:
 * ENAMETOOLONG: pathname resolution of a symbolic link produced
 * an पूर्णांकermediate result whose length exceeds PATH_MAX [XPG4.2]
*/

अटल पूर्णांक jfs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dip,
		       काष्ठा dentry *dentry, स्थिर अक्षर *name)
अणु
	पूर्णांक rc;
	tid_t tid;
	ino_t ino = 0;
	काष्ठा component_name dname;
	पूर्णांक ssize;		/* source pathname size */
	काष्ठा btstack btstack;
	काष्ठा inode *ip = d_inode(dentry);
	s64 xlen = 0;
	पूर्णांक bmask = 0, xsize;
	s64 xaddr;
	काष्ठा metapage *mp;
	काष्ठा super_block *sb;
	काष्ठा tblock *tblk;

	काष्ठा inode *iplist[2];

	jfs_info("jfs_symlink: dip:0x%p name:%s", dip, name);

	rc = dquot_initialize(dip);
	अगर (rc)
		जाओ out1;

	ssize = म_माप(name) + 1;

	/*
	 * search parent directory क्रम entry/मुक्तspace
	 * (dtSearch() वापसs parent directory page pinned)
	 */

	अगर ((rc = get_UCSname(&dname, dentry)))
		जाओ out1;

	/*
	 * allocate on-disk/in-memory inode क्रम symbolic link:
	 * (iAlloc() वापसs new, locked inode)
	 */
	ip = ialloc(dip, S_IFLNK | 0777);
	अगर (IS_ERR(ip)) अणु
		rc = PTR_ERR(ip);
		जाओ out2;
	पूर्ण

	tid = txBegin(dip->i_sb, 0);

	mutex_lock_nested(&JFS_IP(dip)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHILD);

	rc = jfs_init_security(tid, ip, dip, &dentry->d_name);
	अगर (rc)
		जाओ out3;

	tblk = tid_to_tblock(tid);
	tblk->xflag |= COMMIT_CREATE;
	tblk->ino = ip->i_ino;
	tblk->u.ixpxd = JFS_IP(ip)->ixpxd;

	/* fix symlink access permission
	 * (dir_create() ANDs in the u.u_cmask,
	 * but symlinks really need to be 777 access)
	 */
	ip->i_mode |= 0777;

	/*
	 * ग_लिखो symbolic link target path name
	 */
	xtInitRoot(tid, ip);

	/*
	 * ग_लिखो source path name अंतरभूत in on-disk inode (fast symbolic link)
	 */

	अगर (ssize <= IDATASIZE) अणु
		ip->i_op = &jfs_fast_symlink_inode_operations;

		ip->i_link = JFS_IP(ip)->i_अंतरभूत;
		स_नकल(ip->i_link, name, ssize);
		ip->i_size = ssize - 1;

		/*
		 * अगर symlink is > 128 bytes, we करोn't have the space to
		 * store अंतरभूत extended attributes
		 */
		अगर (ssize > माप (JFS_IP(ip)->i_अंतरभूत))
			JFS_IP(ip)->mode2 &= ~INLINEEA;

		jfs_info("jfs_symlink: fast symlink added  ssize:%d name:%s ",
			 ssize, name);
	पूर्ण
	/*
	 * ग_लिखो source path name in a single extent
	 */
	अन्यथा अणु
		jfs_info("jfs_symlink: allocate extent ip:0x%p", ip);

		ip->i_op = &jfs_symlink_inode_operations;
		inode_nohighmem(ip);
		ip->i_mapping->a_ops = &jfs_aops;

		/*
		 * even though the data of symlink object (source
		 * path name) is treated as non-journaled user data,
		 * it is पढ़ो/written thru buffer cache क्रम perक्रमmance.
		 */
		sb = ip->i_sb;
		bmask = JFS_SBI(sb)->bsize - 1;
		xsize = (ssize + bmask) & ~bmask;
		xaddr = 0;
		xlen = xsize >> JFS_SBI(sb)->l2bsize;
		अगर ((rc = xtInsert(tid, ip, 0, 0, xlen, &xaddr, 0))) अणु
			txAbort(tid, 0);
			जाओ out3;
		पूर्ण
		ip->i_size = ssize - 1;
		जबतक (ssize) अणु
			/* This is kind of silly since PATH_MAX == 4K */
			पूर्णांक copy_size = min(ssize, PSIZE);

			mp = get_metapage(ip, xaddr, PSIZE, 1);

			अगर (mp == शून्य) अणु
				xtTruncate(tid, ip, 0, COMMIT_PWMAP);
				rc = -EIO;
				txAbort(tid, 0);
				जाओ out3;
			पूर्ण
			स_नकल(mp->data, name, copy_size);
			flush_metapage(mp);
			ssize -= copy_size;
			name += copy_size;
			xaddr += JFS_SBI(sb)->nbperpage;
		पूर्ण
	पूर्ण

	/*
	 * create entry क्रम symbolic link in parent directory
	 */
	rc = dtSearch(dip, &dname, &ino, &btstack, JFS_CREATE);
	अगर (rc == 0) अणु
		ino = ip->i_ino;
		rc = dtInsert(tid, dip, &dname, &ino, &btstack);
	पूर्ण
	अगर (rc) अणु
		अगर (xlen)
			xtTruncate(tid, ip, 0, COMMIT_PWMAP);
		txAbort(tid, 0);
		/* discard new inode */
		जाओ out3;
	पूर्ण

	mark_inode_dirty(ip);

	dip->i_स_समय = dip->i_mसमय = current_समय(dip);
	mark_inode_dirty(dip);
	/*
	 * commit update of parent directory and link object
	 */

	iplist[0] = dip;
	iplist[1] = ip;
	rc = txCommit(tid, 2, &iplist[0], 0);

      out3:
	txEnd(tid);
	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	mutex_unlock(&JFS_IP(dip)->commit_mutex);
	अगर (rc) अणु
		मुक्त_ea_wmap(ip);
		clear_nlink(ip);
		discard_new_inode(ip);
	पूर्ण अन्यथा अणु
		d_instantiate_new(dentry, ip);
	पूर्ण

      out2:
	मुक्त_UCSname(&dname);

      out1:
	jfs_info("jfs_symlink: rc:%d", rc);
	वापस rc;
पूर्ण


/*
 * NAME:	jfs_नाम
 *
 * FUNCTION:	नाम a file or directory
 */
अटल पूर्णांक jfs_नाम(काष्ठा user_namespace *mnt_userns, काष्ठा inode *old_dir,
		      काष्ठा dentry *old_dentry, काष्ठा inode *new_dir,
		      काष्ठा dentry *new_dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा btstack btstack;
	ino_t ino;
	काष्ठा component_name new_dname;
	काष्ठा inode *new_ip;
	काष्ठा component_name old_dname;
	काष्ठा inode *old_ip;
	पूर्णांक rc;
	tid_t tid;
	काष्ठा tlock *tlck;
	काष्ठा dt_lock *dtlck;
	काष्ठा lv *lv;
	पूर्णांक ipcount;
	काष्ठा inode *iplist[4];
	काष्ठा tblock *tblk;
	s64 new_size = 0;
	पूर्णांक commit_flag;

	अगर (flags & ~RENAME_NOREPLACE)
		वापस -EINVAL;

	jfs_info("jfs_rename: %pd %pd", old_dentry, new_dentry);

	rc = dquot_initialize(old_dir);
	अगर (rc)
		जाओ out1;
	rc = dquot_initialize(new_dir);
	अगर (rc)
		जाओ out1;

	old_ip = d_inode(old_dentry);
	new_ip = d_inode(new_dentry);

	अगर ((rc = get_UCSname(&old_dname, old_dentry)))
		जाओ out1;

	अगर ((rc = get_UCSname(&new_dname, new_dentry)))
		जाओ out2;

	/*
	 * Make sure source inode number is what we think it is
	 */
	rc = dtSearch(old_dir, &old_dname, &ino, &btstack, JFS_LOOKUP);
	अगर (rc || (ino != old_ip->i_ino)) अणु
		rc = -ENOENT;
		जाओ out3;
	पूर्ण

	/*
	 * Make sure dest inode number (अगर any) is what we think it is
	 */
	rc = dtSearch(new_dir, &new_dname, &ino, &btstack, JFS_LOOKUP);
	अगर (!rc) अणु
		अगर ((!new_ip) || (ino != new_ip->i_ino)) अणु
			rc = -ESTALE;
			जाओ out3;
		पूर्ण
	पूर्ण अन्यथा अगर (rc != -ENOENT)
		जाओ out3;
	अन्यथा अगर (new_ip) अणु
		/* no entry exists, but one was expected */
		rc = -ESTALE;
		जाओ out3;
	पूर्ण

	अगर (S_ISसूची(old_ip->i_mode)) अणु
		अगर (new_ip) अणु
			अगर (!dtEmpty(new_ip)) अणु
				rc = -ENOTEMPTY;
				जाओ out3;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (new_ip) अणु
		IWRITE_LOCK(new_ip, RDWRLOCK_NORMAL);
		/* Init inode क्रम quota operations. */
		rc = dquot_initialize(new_ip);
		अगर (rc)
			जाओ out_unlock;
	पूर्ण

	/*
	 * The real work starts here
	 */
	tid = txBegin(new_dir->i_sb, 0);

	/*
	 * How करो we know the locking is safe from deadlocks?
	 * The vfs करोes the hard part क्रम us.  Any समय we are taking nested
	 * commit_mutexes, the vfs alपढ़ोy has i_mutex held on the parent.
	 * Here, the vfs has alपढ़ोy taken i_mutex on both old_dir and new_dir.
	 */
	mutex_lock_nested(&JFS_IP(new_dir)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(old_ip)->commit_mutex, COMMIT_MUTEX_CHILD);
	अगर (old_dir != new_dir)
		mutex_lock_nested(&JFS_IP(old_dir)->commit_mutex,
				  COMMIT_MUTEX_SECOND_PARENT);

	अगर (new_ip) अणु
		mutex_lock_nested(&JFS_IP(new_ip)->commit_mutex,
				  COMMIT_MUTEX_VICTIM);
		/*
		 * Change existing directory entry to new inode number
		 */
		ino = new_ip->i_ino;
		rc = dtModअगरy(tid, new_dir, &new_dname, &ino,
			      old_ip->i_ino, JFS_RENAME);
		अगर (rc)
			जाओ out_tx;
		drop_nlink(new_ip);
		अगर (S_ISसूची(new_ip->i_mode)) अणु
			drop_nlink(new_ip);
			अगर (new_ip->i_nlink) अणु
				mutex_unlock(&JFS_IP(new_ip)->commit_mutex);
				अगर (old_dir != new_dir)
					mutex_unlock(&JFS_IP(old_dir)->commit_mutex);
				mutex_unlock(&JFS_IP(old_ip)->commit_mutex);
				mutex_unlock(&JFS_IP(new_dir)->commit_mutex);
				अगर (!S_ISसूची(old_ip->i_mode) && new_ip)
					IWRITE_UNLOCK(new_ip);
				jfs_error(new_ip->i_sb,
					  "new_ip->i_nlink != 0\n");
				वापस -EIO;
			पूर्ण
			tblk = tid_to_tblock(tid);
			tblk->xflag |= COMMIT_DELETE;
			tblk->u.ip = new_ip;
		पूर्ण अन्यथा अगर (new_ip->i_nlink == 0) अणु
			निश्चित(!test_cflag(COMMIT_Nolink, new_ip));
			/* मुक्त block resources */
			अगर ((new_size = commitZeroLink(tid, new_ip)) < 0) अणु
				txAbort(tid, 1);	/* Marks FS Dirty */
				rc = new_size;
				जाओ out_tx;
			पूर्ण
			tblk = tid_to_tblock(tid);
			tblk->xflag |= COMMIT_DELETE;
			tblk->u.ip = new_ip;
		पूर्ण अन्यथा अणु
			new_ip->i_स_समय = current_समय(new_ip);
			mark_inode_dirty(new_ip);
		पूर्ण
	पूर्ण अन्यथा अणु
		/*
		 * Add new directory entry
		 */
		rc = dtSearch(new_dir, &new_dname, &ino, &btstack,
			      JFS_CREATE);
		अगर (rc) अणु
			jfs_err("jfs_rename didn't expect dtSearch to fail w/rc = %d",
				rc);
			जाओ out_tx;
		पूर्ण

		ino = old_ip->i_ino;
		rc = dtInsert(tid, new_dir, &new_dname, &ino, &btstack);
		अगर (rc) अणु
			अगर (rc == -EIO)
				jfs_err("jfs_rename: dtInsert returned -EIO");
			जाओ out_tx;
		पूर्ण
		अगर (S_ISसूची(old_ip->i_mode))
			inc_nlink(new_dir);
	पूर्ण
	/*
	 * Remove old directory entry
	 */

	ino = old_ip->i_ino;
	rc = dtDelete(tid, old_dir, &old_dname, &ino, JFS_REMOVE);
	अगर (rc) अणु
		jfs_err("jfs_rename did not expect dtDelete to return rc = %d",
			rc);
		txAbort(tid, 1);	/* Marks Fileप्रणाली dirty */
		जाओ out_tx;
	पूर्ण
	अगर (S_ISसूची(old_ip->i_mode)) अणु
		drop_nlink(old_dir);
		अगर (old_dir != new_dir) अणु
			/*
			 * Change inode number of parent क्रम moved directory
			 */

			JFS_IP(old_ip)->i_dtroot.header.iकरोtकरोt =
				cpu_to_le32(new_dir->i_ino);

			/* Linelock header of dtree */
			tlck = txLock(tid, old_ip,
				    (काष्ठा metapage *) &JFS_IP(old_ip)->bxflag,
				      tlckDTREE | tlckBTROOT | tlckRELINK);
			dtlck = (काष्ठा dt_lock *) & tlck->lock;
			ASSERT(dtlck->index == 0);
			lv = & dtlck->lv[0];
			lv->offset = 0;
			lv->length = 1;
			dtlck->index++;
		पूर्ण
	पूर्ण

	/*
	 * Update स_समय on changed/moved inodes & mark dirty
	 */
	old_ip->i_स_समय = current_समय(old_ip);
	mark_inode_dirty(old_ip);

	new_dir->i_स_समय = new_dir->i_mसमय = current_समय(new_dir);
	mark_inode_dirty(new_dir);

	/* Build list of inodes modअगरied by this transaction */
	ipcount = 0;
	iplist[ipcount++] = old_ip;
	अगर (new_ip)
		iplist[ipcount++] = new_ip;
	iplist[ipcount++] = old_dir;

	अगर (old_dir != new_dir) अणु
		iplist[ipcount++] = new_dir;
		old_dir->i_स_समय = old_dir->i_mसमय = current_समय(old_dir);
		mark_inode_dirty(old_dir);
	पूर्ण

	/*
	 * Incomplete truncate of file data can
	 * result in timing problems unless we synchronously commit the
	 * transaction.
	 */
	अगर (new_size)
		commit_flag = COMMIT_SYNC;
	अन्यथा
		commit_flag = 0;

	rc = txCommit(tid, ipcount, iplist, commit_flag);

      out_tx:
	txEnd(tid);
	अगर (new_ip)
		mutex_unlock(&JFS_IP(new_ip)->commit_mutex);
	अगर (old_dir != new_dir)
		mutex_unlock(&JFS_IP(old_dir)->commit_mutex);
	mutex_unlock(&JFS_IP(old_ip)->commit_mutex);
	mutex_unlock(&JFS_IP(new_dir)->commit_mutex);

	जबतक (new_size && (rc == 0)) अणु
		tid = txBegin(new_ip->i_sb, 0);
		mutex_lock(&JFS_IP(new_ip)->commit_mutex);
		new_size = xtTruncate_pmap(tid, new_ip, new_size);
		अगर (new_size < 0) अणु
			txAbort(tid, 1);
			rc = new_size;
		पूर्ण अन्यथा
			rc = txCommit(tid, 1, &new_ip, COMMIT_SYNC);
		txEnd(tid);
		mutex_unlock(&JFS_IP(new_ip)->commit_mutex);
	पूर्ण
	अगर (new_ip && (new_ip->i_nlink == 0))
		set_cflag(COMMIT_Nolink, new_ip);
	/*
	 * Truncating the directory index table is not guaranteed.  It
	 * may need to be करोne iteratively
	 */
	अगर (test_cflag(COMMIT_Stale, old_dir)) अणु
		अगर (old_dir->i_size > 1)
			jfs_truncate_nolock(old_dir, 0);

		clear_cflag(COMMIT_Stale, old_dir);
	पूर्ण
      out_unlock:
	अगर (new_ip && !S_ISसूची(new_ip->i_mode))
		IWRITE_UNLOCK(new_ip);
      out3:
	मुक्त_UCSname(&new_dname);
      out2:
	मुक्त_UCSname(&old_dname);
      out1:
	jfs_info("jfs_rename: returning %d", rc);
	वापस rc;
पूर्ण


/*
 * NAME:	jfs_mknod
 *
 * FUNCTION:	Create a special file (device)
 */
अटल पूर्णांक jfs_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		     काष्ठा dentry *dentry, umode_t mode, dev_t rdev)
अणु
	काष्ठा jfs_inode_info *jfs_ip;
	काष्ठा btstack btstack;
	काष्ठा component_name dname;
	ino_t ino;
	काष्ठा inode *ip;
	काष्ठा inode *iplist[2];
	पूर्णांक rc;
	tid_t tid;
	काष्ठा tblock *tblk;

	jfs_info("jfs_mknod: %pd", dentry);

	rc = dquot_initialize(dir);
	अगर (rc)
		जाओ out;

	अगर ((rc = get_UCSname(&dname, dentry)))
		जाओ out;

	ip = ialloc(dir, mode);
	अगर (IS_ERR(ip)) अणु
		rc = PTR_ERR(ip);
		जाओ out1;
	पूर्ण
	jfs_ip = JFS_IP(ip);

	tid = txBegin(dir->i_sb, 0);

	mutex_lock_nested(&JFS_IP(dir)->commit_mutex, COMMIT_MUTEX_PARENT);
	mutex_lock_nested(&JFS_IP(ip)->commit_mutex, COMMIT_MUTEX_CHILD);

	rc = jfs_init_acl(tid, ip, dir);
	अगर (rc)
		जाओ out3;

	rc = jfs_init_security(tid, ip, dir, &dentry->d_name);
	अगर (rc) अणु
		txAbort(tid, 0);
		जाओ out3;
	पूर्ण

	अगर ((rc = dtSearch(dir, &dname, &ino, &btstack, JFS_CREATE))) अणु
		txAbort(tid, 0);
		जाओ out3;
	पूर्ण

	tblk = tid_to_tblock(tid);
	tblk->xflag |= COMMIT_CREATE;
	tblk->ino = ip->i_ino;
	tblk->u.ixpxd = JFS_IP(ip)->ixpxd;

	ino = ip->i_ino;
	अगर ((rc = dtInsert(tid, dir, &dname, &ino, &btstack))) अणु
		txAbort(tid, 0);
		जाओ out3;
	पूर्ण

	ip->i_op = &jfs_file_inode_operations;
	jfs_ip->dev = new_encode_dev(rdev);
	init_special_inode(ip, ip->i_mode, rdev);

	mark_inode_dirty(ip);

	dir->i_स_समय = dir->i_mसमय = current_समय(dir);

	mark_inode_dirty(dir);

	iplist[0] = dir;
	iplist[1] = ip;
	rc = txCommit(tid, 2, iplist, 0);

      out3:
	txEnd(tid);
	mutex_unlock(&JFS_IP(ip)->commit_mutex);
	mutex_unlock(&JFS_IP(dir)->commit_mutex);
	अगर (rc) अणु
		मुक्त_ea_wmap(ip);
		clear_nlink(ip);
		discard_new_inode(ip);
	पूर्ण अन्यथा अणु
		d_instantiate_new(dentry, ip);
	पूर्ण

      out1:
	मुक्त_UCSname(&dname);

      out:
	jfs_info("jfs_mknod: returning %d", rc);
	वापस rc;
पूर्ण

अटल काष्ठा dentry *jfs_lookup(काष्ठा inode *dip, काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा btstack btstack;
	ino_t inum;
	काष्ठा inode *ip;
	काष्ठा component_name key;
	पूर्णांक rc;

	jfs_info("jfs_lookup: name = %pd", dentry);

	अगर ((rc = get_UCSname(&key, dentry)))
		वापस ERR_PTR(rc);
	rc = dtSearch(dip, &key, &inum, &btstack, JFS_LOOKUP);
	मुक्त_UCSname(&key);
	अगर (rc == -ENOENT) अणु
		ip = शून्य;
	पूर्ण अन्यथा अगर (rc) अणु
		jfs_err("jfs_lookup: dtSearch returned %d", rc);
		ip = ERR_PTR(rc);
	पूर्ण अन्यथा अणु
		ip = jfs_iget(dip->i_sb, inum);
		अगर (IS_ERR(ip))
			jfs_err("jfs_lookup: iget failed on inum %d", (uपूर्णांक)inum);
	पूर्ण

	वापस d_splice_alias(ip, dentry);
पूर्ण

अटल काष्ठा inode *jfs_nfs_get_inode(काष्ठा super_block *sb,
		u64 ino, u32 generation)
अणु
	काष्ठा inode *inode;

	अगर (ino == 0)
		वापस ERR_PTR(-ESTALE);
	inode = jfs_iget(sb, ino);
	अगर (IS_ERR(inode))
		वापस ERR_CAST(inode);

	अगर (generation && inode->i_generation != generation) अणु
		iput(inode);
		वापस ERR_PTR(-ESTALE);
	पूर्ण

	वापस inode;
पूर्ण

काष्ठा dentry *jfs_fh_to_dentry(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_dentry(sb, fid, fh_len, fh_type,
				    jfs_nfs_get_inode);
पूर्ण

काष्ठा dentry *jfs_fh_to_parent(काष्ठा super_block *sb, काष्ठा fid *fid,
		पूर्णांक fh_len, पूर्णांक fh_type)
अणु
	वापस generic_fh_to_parent(sb, fid, fh_len, fh_type,
				    jfs_nfs_get_inode);
पूर्ण

काष्ठा dentry *jfs_get_parent(काष्ठा dentry *dentry)
अणु
	अचिन्हित दीर्घ parent_ino;

	parent_ino =
		le32_to_cpu(JFS_IP(d_inode(dentry))->i_dtroot.header.iकरोtकरोt);

	वापस d_obtain_alias(jfs_iget(dentry->d_sb, parent_ino));
पूर्ण

स्थिर काष्ठा inode_operations jfs_dir_inode_operations = अणु
	.create		= jfs_create,
	.lookup		= jfs_lookup,
	.link		= jfs_link,
	.unlink		= jfs_unlink,
	.symlink	= jfs_symlink,
	.सूची_गढ़ो		= jfs_सूची_गढ़ो,
	.सूची_हटाओ		= jfs_सूची_हटाओ,
	.mknod		= jfs_mknod,
	.नाम		= jfs_नाम,
	.listxattr	= jfs_listxattr,
	.setattr	= jfs_setattr,
	.fileattr_get	= jfs_fileattr_get,
	.fileattr_set	= jfs_fileattr_set,
#अगर_घोषित CONFIG_JFS_POSIX_ACL
	.get_acl	= jfs_get_acl,
	.set_acl	= jfs_set_acl,
#पूर्ण_अगर
पूर्ण;

स्थिर काष्ठा file_operations jfs_dir_operations = अणु
	.पढ़ो		= generic_पढ़ो_dir,
	.iterate	= jfs_सूची_पढ़ो,
	.fsync		= jfs_fsync,
	.unlocked_ioctl = jfs_ioctl,
	.compat_ioctl	= compat_ptr_ioctl,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल पूर्णांक jfs_ci_hash(स्थिर काष्ठा dentry *dir, काष्ठा qstr *this)
अणु
	अचिन्हित दीर्घ hash;
	पूर्णांक i;

	hash = init_name_hash(dir);
	क्रम (i=0; i < this->len; i++)
		hash = partial_name_hash(छोटे(this->name[i]), hash);
	this->hash = end_name_hash(hash);

	वापस 0;
पूर्ण

अटल पूर्णांक jfs_ci_compare(स्थिर काष्ठा dentry *dentry,
		अचिन्हित पूर्णांक len, स्थिर अक्षर *str, स्थिर काष्ठा qstr *name)
अणु
	पूर्णांक i, result = 1;

	अगर (len != name->len)
		जाओ out;
	क्रम (i=0; i < len; i++) अणु
		अगर (छोटे(str[i]) != छोटे(name->name[i]))
			जाओ out;
	पूर्ण
	result = 0;
out:
	वापस result;
पूर्ण

अटल पूर्णांक jfs_ci_revalidate(काष्ठा dentry *dentry, अचिन्हित पूर्णांक flags)
अणु
	/*
	 * This is not negative dentry. Always valid.
	 *
	 * Note, नाम() to existing directory entry will have ->d_inode,
	 * and will use existing name which isn't specअगरied name by user.
	 *
	 * We may be able to drop this positive dentry here. But dropping
	 * positive dentry isn't good idea. So it's unsupported like
	 * नाम("filename", "FILENAME") क्रम now.
	 */
	अगर (d_really_is_positive(dentry))
		वापस 1;

	/*
	 * This may be nfsd (or something), anyway, we can't see the
	 * पूर्णांकent of this. So, since this can be क्रम creation, drop it.
	 */
	अगर (!flags)
		वापस 0;

	/*
	 * Drop the negative dentry, in order to make sure to use the
	 * हाल sensitive name which is specअगरied by user अगर this is
	 * क्रम creation.
	 */
	अगर (flags & (LOOKUP_CREATE | LOOKUP_RENAME_TARGET))
		वापस 0;
	वापस 1;
पूर्ण

स्थिर काष्ठा dentry_operations jfs_ci_dentry_operations =
अणु
	.d_hash = jfs_ci_hash,
	.d_compare = jfs_ci_compare,
	.d_revalidate = jfs_ci_revalidate,
पूर्ण;
