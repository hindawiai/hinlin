<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * V9FS definitions.
 *
 *  Copyright (C) 2004-2008 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 2002 by Ron Minnich <rminnich@lanl.gov>
 */
#अगर_अघोषित FS_9P_V9FS_H
#घोषणा FS_9P_V9FS_H

#समावेश <linux/backing-dev.h>

/**
 * क्रमागत p9_session_flags - option flags क्रम each 9P session
 * @V9FS_PROTO_2000U: whether or not to use 9P2000.u extensions
 * @V9FS_PROTO_2000L: whether or not to use 9P2000.l extensions
 * @V9FS_ACCESS_SINGLE: only the mounting user can access the hierarchy
 * @V9FS_ACCESS_USER: a new attach will be issued क्रम every user (शेष)
 * @V9FS_ACCESS_CLIENT: Just like user, but access check is perक्रमmed on client.
 * @V9FS_ACCESS_ANY: use a single attach क्रम all users
 * @V9FS_ACCESS_MASK: bit mask of dअगरferent ACCESS options
 * @V9FS_POSIX_ACL: POSIX ACLs are enक्रमced
 *
 * Session flags reflect options selected by users at mount समय
 */
#घोषणा	V9FS_ACCESS_ANY (V9FS_ACCESS_SINGLE | \
			 V9FS_ACCESS_USER |   \
			 V9FS_ACCESS_CLIENT)
#घोषणा V9FS_ACCESS_MASK V9FS_ACCESS_ANY
#घोषणा V9FS_ACL_MASK V9FS_POSIX_ACL

क्रमागत p9_session_flags अणु
	V9FS_PROTO_2000U	= 0x01,
	V9FS_PROTO_2000L	= 0x02,
	V9FS_ACCESS_SINGLE	= 0x04,
	V9FS_ACCESS_USER	= 0x08,
	V9FS_ACCESS_CLIENT	= 0x10,
	V9FS_POSIX_ACL		= 0x20
पूर्ण;

/* possible values of ->cache */
/**
 * क्रमागत p9_cache_modes - user specअगरied cache preferences
 * @CACHE_NONE: करो not cache data, dentries, or directory contents (शेष)
 * @CACHE_LOOSE: cache data, dentries, and directory contents w/no consistency
 *
 * eventually support loose, tight, समय, session, शेष always none
 */

क्रमागत p9_cache_modes अणु
	CACHE_NONE,
	CACHE_MMAP,
	CACHE_LOOSE,
	CACHE_FSCACHE,
	nr__p9_cache_modes
पूर्ण;

/**
 * काष्ठा v9fs_session_info - per-instance session inक्रमmation
 * @flags: session options of type &p9_session_flags
 * @nodev: set to 1 to disable device mapping
 * @debug: debug level
 * @afid: authentication handle
 * @cache: cache mode of type &p9_cache_modes
 * @cachetag: the tag of the cache associated with this session
 * @fscache: session cookie associated with FS-Cache
 * @uname: string user name to mount hierarchy as
 * @aname: mount specअगरier क्रम remote hierarchy
 * @maxdata: maximum data to be sent/recvd per protocol message
 * @dfltuid: शेष numeric userid to mount hierarchy as
 * @dfltgid: शेष numeric groupid to mount hierarchy as
 * @uid: अगर %V9FS_ACCESS_SINGLE, the numeric uid which mounted the hierarchy
 * @clnt: reference to 9P network client instantiated क्रम this session
 * @slist: reference to list of रेजिस्टरed 9p sessions
 *
 * This काष्ठाure holds state क्रम each session instance established during
 * a sys_mount() .
 *
 * Bugs: there seems to be a lot of state which could be condensed and/or
 * हटाओd.
 */

काष्ठा v9fs_session_info अणु
	/* options */
	अचिन्हित अक्षर flags;
	अचिन्हित अक्षर nodev;
	अचिन्हित लघु debug;
	अचिन्हित पूर्णांक afid;
	अचिन्हित पूर्णांक cache;
#अगर_घोषित CONFIG_9P_FSCACHE
	अक्षर *cachetag;
	काष्ठा fscache_cookie *fscache;
#पूर्ण_अगर

	अक्षर *uname;		/* user name to mount as */
	अक्षर *aname;		/* name of remote hierarchy being mounted */
	अचिन्हित पूर्णांक maxdata;	/* max data क्रम client पूर्णांकerface */
	kuid_t dfltuid;		/* शेष uid/muid क्रम legacy support */
	kgid_t dfltgid;		/* शेष gid क्रम legacy support */
	kuid_t uid;		/* अगर ACCESS_SINGLE, the uid that has access */
	काष्ठा p9_client *clnt;	/* 9p client */
	काष्ठा list_head slist; /* list of sessions रेजिस्टरed with v9fs */
	काष्ठा rw_semaphore नाम_sem;
	दीर्घ session_lock_समयout; /* retry पूर्णांकerval क्रम blocking locks */
पूर्ण;

/* cache_validity flags */
#घोषणा V9FS_INO_INVALID_ATTR 0x01

काष्ठा v9fs_inode अणु
#अगर_घोषित CONFIG_9P_FSCACHE
	काष्ठा mutex fscache_lock;
	काष्ठा fscache_cookie *fscache;
#पूर्ण_अगर
	काष्ठा p9_qid qid;
	अचिन्हित पूर्णांक cache_validity;
	काष्ठा p9_fid *ग_लिखोback_fid;
	काष्ठा mutex v_mutex;
	काष्ठा inode vfs_inode;
पूर्ण;

अटल अंतरभूत काष्ठा v9fs_inode *V9FS_I(स्थिर काष्ठा inode *inode)
अणु
	वापस container_of(inode, काष्ठा v9fs_inode, vfs_inode);
पूर्ण

बाह्य पूर्णांक v9fs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root);

काष्ठा p9_fid *v9fs_session_init(काष्ठा v9fs_session_info *, स्थिर अक्षर *,
									अक्षर *);
बाह्य व्योम v9fs_session_बंद(काष्ठा v9fs_session_info *v9ses);
बाह्य व्योम v9fs_session_cancel(काष्ठा v9fs_session_info *v9ses);
बाह्य व्योम v9fs_session_begin_cancel(काष्ठा v9fs_session_info *v9ses);
बाह्य काष्ठा dentry *v9fs_vfs_lookup(काष्ठा inode *dir, काष्ठा dentry *dentry,
			अचिन्हित पूर्णांक flags);
बाह्य पूर्णांक v9fs_vfs_unlink(काष्ठा inode *i, काष्ठा dentry *d);
बाह्य पूर्णांक v9fs_vfs_सूची_हटाओ(काष्ठा inode *i, काष्ठा dentry *d);
बाह्य पूर्णांक v9fs_vfs_नाम(काष्ठा user_namespace *mnt_userns,
			   काष्ठा inode *old_dir, काष्ठा dentry *old_dentry,
			   काष्ठा inode *new_dir, काष्ठा dentry *new_dentry,
			   अचिन्हित पूर्णांक flags);
बाह्य काष्ठा inode *v9fs_inode_from_fid(काष्ठा v9fs_session_info *v9ses,
					 काष्ठा p9_fid *fid,
					 काष्ठा super_block *sb, पूर्णांक new);
बाह्य स्थिर काष्ठा inode_operations v9fs_dir_inode_operations_करोtl;
बाह्य स्थिर काष्ठा inode_operations v9fs_file_inode_operations_करोtl;
बाह्य स्थिर काष्ठा inode_operations v9fs_symlink_inode_operations_करोtl;
बाह्य काष्ठा inode *v9fs_inode_from_fid_करोtl(काष्ठा v9fs_session_info *v9ses,
					      काष्ठा p9_fid *fid,
					      काष्ठा super_block *sb, पूर्णांक new);

/* other शेष globals */
#घोषणा V9FS_PORT	564
#घोषणा V9FS_DEFUSER	"nobody"
#घोषणा V9FS_DEFANAME	""
#घोषणा V9FS_DEFUID	KUIDT_INIT(-2)
#घोषणा V9FS_DEFGID	KGIDT_INIT(-2)

अटल अंतरभूत काष्ठा v9fs_session_info *v9fs_inode2v9ses(काष्ठा inode *inode)
अणु
	वापस (inode->i_sb->s_fs_info);
पूर्ण

अटल अंतरभूत काष्ठा v9fs_session_info *v9fs_dentry2v9ses(काष्ठा dentry *dentry)
अणु
	वापस dentry->d_sb->s_fs_info;
पूर्ण

अटल अंतरभूत पूर्णांक v9fs_proto_करोtu(काष्ठा v9fs_session_info *v9ses)
अणु
	वापस v9ses->flags & V9FS_PROTO_2000U;
पूर्ण

अटल अंतरभूत पूर्णांक v9fs_proto_करोtl(काष्ठा v9fs_session_info *v9ses)
अणु
	वापस v9ses->flags & V9FS_PROTO_2000L;
पूर्ण

/**
 * v9fs_get_inode_from_fid - Helper routine to populate an inode by
 * issuing a attribute request
 * @v9ses: session inक्रमmation
 * @fid: fid to issue attribute request क्रम
 * @sb: superblock on which to create inode
 *
 */
अटल अंतरभूत काष्ठा inode *
v9fs_get_inode_from_fid(काष्ठा v9fs_session_info *v9ses, काष्ठा p9_fid *fid,
			काष्ठा super_block *sb)
अणु
	अगर (v9fs_proto_करोtl(v9ses))
		वापस v9fs_inode_from_fid_करोtl(v9ses, fid, sb, 0);
	अन्यथा
		वापस v9fs_inode_from_fid(v9ses, fid, sb, 0);
पूर्ण

/**
 * v9fs_get_new_inode_from_fid - Helper routine to populate an inode by
 * issuing a attribute request
 * @v9ses: session inक्रमmation
 * @fid: fid to issue attribute request क्रम
 * @sb: superblock on which to create inode
 *
 */
अटल अंतरभूत काष्ठा inode *
v9fs_get_new_inode_from_fid(काष्ठा v9fs_session_info *v9ses, काष्ठा p9_fid *fid,
			    काष्ठा super_block *sb)
अणु
	अगर (v9fs_proto_करोtl(v9ses))
		वापस v9fs_inode_from_fid_करोtl(v9ses, fid, sb, 1);
	अन्यथा
		वापस v9fs_inode_from_fid(v9ses, fid, sb, 1);
पूर्ण

#पूर्ण_अगर
