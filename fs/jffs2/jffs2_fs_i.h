<शैली गुरु>
/*
 * JFFS2 -- Journalling Flash File System, Version 2.
 *
 * Copyright तऊ 2001-2007 Red Hat, Inc.
 * Copyright तऊ 2004-2010 David Woodhouse <dwmw2@infradead.org>
 *
 * Created by David Woodhouse <dwmw2@infradead.org>
 *
 * For licensing inक्रमmation, see the file 'LICENCE' in this directory.
 *
 */

#अगर_अघोषित _JFFS2_FS_I
#घोषणा _JFFS2_FS_I

#समावेश <linux/rbtree.h>
#समावेश <linux/posix_acl.h>
#समावेश <linux/mutex.h>

काष्ठा jffs2_inode_info अणु
	/* We need an पूर्णांकernal mutex similar to inode->i_mutex.
	   Unक्रमtunately, we can't used the existing one, because
	   either the GC would deadlock, or we'd have to release it
	   beक्रमe letting GC proceed. Or we'd have to put ugliness
	   पूर्णांकo the GC code so it didn't attempt to obtain the i_mutex
	   क्रम the inode(s) which are alपढ़ोy locked */
	काष्ठा mutex sem;

	/* The highest (datanode) version number used क्रम this ino */
	uपूर्णांक32_t highest_version;

	/* List of data fragments which make up the file */
	काष्ठा rb_root fragtree;

	/* There may be one datanode which isn't referenced by any of the
	   above fragments, अगर it contains a metadata update but no actual
	   data - or अगर this is a directory inode */
	/* This also holds the _only_ dnode क्रम symlinks/device nodes,
	   etc. */
	काष्ठा jffs2_full_dnode *metadata;

	/* Directory entries */
	काष्ठा jffs2_full_dirent *dents;

	/* The target path अगर this is the inode of a symlink */
	अचिन्हित अक्षर *target;

	/* Some stuff we just have to keep in-core at all बार, क्रम each inode. */
	काष्ठा jffs2_inode_cache *inocache;

	uपूर्णांक16_t flags;
	uपूर्णांक8_t usercompr;
	काष्ठा inode vfs_inode;
पूर्ण;

#पूर्ण_अगर /* _JFFS2_FS_I */
