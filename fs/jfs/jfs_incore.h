<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   Copyright (C) International Business Machines Corp., 2000-2004
 *   Portions Copyright (C) Christoph Hellwig, 2001-2002
 */
#अगर_अघोषित _H_JFS_INCORE
#घोषणा _H_JFS_INCORE

#समावेश <linux/mutex.h>
#समावेश <linux/rwsem.h>
#समावेश <linux/slab.h>
#समावेश <linux/bitops.h>
#समावेश <linux/uuid.h>

#समावेश "jfs_types.h"
#समावेश "jfs_xtree.h"
#समावेश "jfs_dtree.h"

/*
 * JFS magic number
 */
#घोषणा JFS_SUPER_MAGIC 0x3153464a /* "JFS1" */

/*
 * JFS-निजी inode inक्रमmation
 */
काष्ठा jfs_inode_info अणु
	पूर्णांक	fileset;	/* fileset number (always 16)*/
	uपूर्णांक	mode2;		/* jfs-specअगरic mode		*/
	kuid_t	saved_uid;	/* saved क्रम uid mount option */
	kgid_t	saved_gid;	/* saved क्रम gid mount option */
	pxd_t	ixpxd;		/* inode extent descriptor	*/
	dxd_t	acl;		/* dxd describing acl	*/
	dxd_t	ea;		/* dxd describing ea	*/
	समय64_t oसमय;		/* समय created	*/
	uपूर्णांक	next_index;	/* next available directory entry index */
	पूर्णांक	acltype;	/* Type of ACL	*/
	लघु	btorder;	/* access order	*/
	लघु	btindex;	/* btpage entry index*/
	काष्ठा inode *ipimap;	/* inode map			*/
	अचिन्हित दीर्घ cflag;	/* commit flags		*/
	u64	agstart;	/* agstart of the containing IAG */
	u16	bxflag;		/* xflag of pseuकरो buffer?	*/
	unअक्षर	pad;
	चिन्हित अक्षर active_ag;	/* ag currently allocating from	*/
	lid_t	blid;		/* lid of pseuकरो buffer?	*/
	lid_t	atlhead;	/* anonymous tlock list head	*/
	lid_t	atltail;	/* anonymous tlock list tail	*/
	spinlock_t ag_lock;	/* protects active_ag		*/
	काष्ठा list_head anon_inode_list; /* inodes having anonymous txns */
	/*
	 * rdwrlock serializes xtree between पढ़ोs & ग_लिखोs and synchronizes
	 * changes to special inodes.  It's use would be redundant on
	 * directories since the i_mutex taken in the VFS is sufficient.
	 */
	काष्ठा rw_semaphore rdwrlock;
	/*
	 * commit_mutex serializes transaction processing on an inode.
	 * It must be taken after beginning a transaction (txBegin), since
	 * dirty inodes may be committed जबतक a new transaction on the
	 * inode is blocked in txBegin or TxBeginAnon
	 */
	काष्ठा mutex commit_mutex;
	/* xattr_sem allows us to access the xattrs without taking i_mutex */
	काष्ठा rw_semaphore xattr_sem;
	lid_t	xtlid;		/* lid of xtree lock on directory */
	जोड़ अणु
		काष्ठा अणु
			xtpage_t _xtroot;	/* 288: xtree root */
			काष्ठा inomap *_imap;	/* 4: inode map header	*/
		पूर्ण file;
		काष्ठा अणु
			काष्ठा dir_table_slot _table[12]; /* 96: dir index */
			dtroot_t _dtroot;	/* 288: dtree root */
		पूर्ण dir;
		काष्ठा अणु
			unअक्षर _unused[16];	/* 16: */
			dxd_t _dxd;		/* 16: */
			/* _अंतरभूत may overflow पूर्णांकo _अंतरभूत_ea when needed */
			unअक्षर _अंतरभूत[128];	/* 128: अंतरभूत symlink */
			/* _अंतरभूत_ea may overlay the last part of
			 * file._xtroot अगर maxentry = XTROOTINITSLOT
			 */
			unअक्षर _अंतरभूत_ea[128];	/* 128: अंतरभूत extended attr */
		पूर्ण link;
	पूर्ण u;
#अगर_घोषित CONFIG_QUOTA
	काष्ठा dquot *i_dquot[MAXQUOTAS];
#पूर्ण_अगर
	u32 dev;	/* will die when we get wide dev_t */
	काष्ठा inode	vfs_inode;
पूर्ण;
#घोषणा i_xtroot u.file._xtroot
#घोषणा i_imap u.file._imap
#घोषणा i_dirtable u.dir._table
#घोषणा i_dtroot u.dir._dtroot
#घोषणा i_अंतरभूत u.link._अंतरभूत
#घोषणा i_अंतरभूत_ea u.link._अंतरभूत_ea

#घोषणा IREAD_LOCK(ip, subclass) \
	करोwn_पढ़ो_nested(&JFS_IP(ip)->rdwrlock, subclass)
#घोषणा IREAD_UNLOCK(ip)	up_पढ़ो(&JFS_IP(ip)->rdwrlock)
#घोषणा IWRITE_LOCK(ip, subclass) \
	करोwn_ग_लिखो_nested(&JFS_IP(ip)->rdwrlock, subclass)
#घोषणा IWRITE_UNLOCK(ip)	up_ग_लिखो(&JFS_IP(ip)->rdwrlock)

/*
 * cflag
 */
क्रमागत cflags अणु
	COMMIT_Nolink,		/* inode committed with zero link count */
	COMMIT_Inlineea,	/* commit inode अंतरभूत EA */
	COMMIT_Freewmap,	/* मुक्त WMAP at iClose() */
	COMMIT_Dirty,		/* Inode is really dirty */
	COMMIT_Dirtable,	/* commit changes to di_dirtable */
	COMMIT_Stale,		/* data extent is no दीर्घer valid */
	COMMIT_Synclist,	/* metadata pages on group commit synclist */
पूर्ण;

/*
 * commit_mutex nesting subclasses:
 */
क्रमागत commit_mutex_class
अणु
	COMMIT_MUTEX_PARENT,
	COMMIT_MUTEX_CHILD,
	COMMIT_MUTEX_SECOND_PARENT,	/* Renaming */
	COMMIT_MUTEX_VICTIM		/* Inode being unlinked due to नाम */
पूर्ण;

/*
 * rdwrlock subclasses:
 * The dmap inode may be locked जबतक a normal inode or the imap inode are
 * locked.
 */
क्रमागत rdwrlock_class
अणु
	RDWRLOCK_NORMAL,
	RDWRLOCK_IMAP,
	RDWRLOCK_DMAP
पूर्ण;

#घोषणा set_cflag(flag, ip)	set_bit(flag, &(JFS_IP(ip)->cflag))
#घोषणा clear_cflag(flag, ip)	clear_bit(flag, &(JFS_IP(ip)->cflag))
#घोषणा test_cflag(flag, ip)	test_bit(flag, &(JFS_IP(ip)->cflag))
#घोषणा test_and_clear_cflag(flag, ip) \
	test_and_clear_bit(flag, &(JFS_IP(ip)->cflag))
/*
 * JFS-निजी superblock inक्रमmation.
 */
काष्ठा jfs_sb_info अणु
	काष्ठा super_block *sb;		/* Poपूर्णांक back to vfs super block */
	अचिन्हित दीर्घ	mntflag;	/* aggregate attributes	*/
	काष्ठा inode	*ipbmap;	/* block map inode		*/
	काष्ठा inode	*ipaimap;	/* aggregate inode map inode	*/
	काष्ठा inode	*ipaimap2;	/* secondary aimap inode	*/
	काष्ठा inode	*ipimap;	/* aggregate inode map inode	*/
	काष्ठा jfs_log	*log;		/* log			*/
	काष्ठा list_head log_list;	/* volumes associated with a journal */
	लघु		bsize;		/* logical block size	*/
	लघु		l2bsize;	/* log2 logical block size	*/
	लघु		nbperpage;	/* blocks per page		*/
	लघु		l2nbperpage;	/* log2 blocks per page	*/
	लघु		l2niperblk;	/* log2 inodes per page	*/
	dev_t		logdev;		/* बाह्यal log device	*/
	uपूर्णांक		aggregate;	/* volume identअगरier in log record */
	pxd_t		logpxd;		/* pxd describing log	*/
	pxd_t		fsckpxd;	/* pxd describing fsck wkspc */
	pxd_t		ait2;		/* pxd describing AIT copy	*/
	uuid_t		uuid;		/* 128-bit uuid क्रम volume	*/
	uuid_t		loguuid;	/* 128-bit uuid क्रम log	*/
	/*
	 * commit_state is used क्रम synchronization of the jfs_commit
	 * thपढ़ोs.  It is रक्षित by LAZY_LOCK().
	 */
	पूर्णांक		commit_state;	/* commit state */
	/* Formerly in ipimap */
	uपूर्णांक		gengen;		/* inode generation generator*/
	uपूर्णांक		inostamp;	/* shows inode beदीर्घs to fileset*/

	/* Formerly in ipbmap */
	काष्ठा bmap	*bmap;		/* incore bmap descriptor	*/
	काष्ठा nls_table *nls_tab;	/* current codepage		*/
	काष्ठा inode *direct_inode;	/* metadata inode */
	uपूर्णांक		state;		/* mount/recovery state	*/
	अचिन्हित दीर्घ	flag;		/* mount समय flags */
	uपूर्णांक		p_state;	/* state prior to going no पूर्णांकegrity */
	kuid_t		uid;		/* uid to override on-disk uid */
	kgid_t		gid;		/* gid to override on-disk gid */
	uपूर्णांक		umask;		/* umask to override on-disk umask */
	uपूर्णांक		minblks_trim;	/* minimum blocks, क्रम online trim */
पूर्ण;

/* jfs_sb_info commit_state */
#घोषणा IN_LAZYCOMMIT 1

अटल अंतरभूत काष्ठा jfs_inode_info *JFS_IP(काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा jfs_inode_info, vfs_inode);
पूर्ण

अटल अंतरभूत पूर्णांक jfs_dirtable_अंतरभूत(काष्ठा inode *inode)
अणु
	वापस (JFS_IP(inode)->next_index <= (MAX_INLINE_सूचीTABLE_ENTRY + 1));
पूर्ण

अटल अंतरभूत काष्ठा jfs_sb_info *JFS_SBI(काष्ठा super_block *sb)
अणु
	वापस sb->s_fs_info;
पूर्ण

अटल अंतरभूत पूर्णांक isReadOnly(काष्ठा inode *inode)
अणु
	अगर (JFS_SBI(inode->i_sb)->log)
		वापस 0;
	वापस 1;
पूर्ण
#पूर्ण_अगर /* _H_JFS_INCORE */
