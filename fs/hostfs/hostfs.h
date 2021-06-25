<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __UM_FS_HOSTFS
#घोषणा __UM_FS_HOSTFS

#समावेश <os.h>

/*
 * These are exactly the same definitions as in fs.h, but the names are
 * changed so that this file can be included in both kernel and user files.
 */

#घोषणा HOSTFS_ATTR_MODE	1
#घोषणा HOSTFS_ATTR_UID 	2
#घोषणा HOSTFS_ATTR_GID 	4
#घोषणा HOSTFS_ATTR_SIZE	8
#घोषणा HOSTFS_ATTR_ATIME	16
#घोषणा HOSTFS_ATTR_MTIME	32
#घोषणा HOSTFS_ATTR_CTIME	64
#घोषणा HOSTFS_ATTR_ATIME_SET	128
#घोषणा HOSTFS_ATTR_MTIME_SET	256

/* This one is unused by hostfs. */
#घोषणा HOSTFS_ATTR_FORCE	512	/* Not a change, but a change it */
#घोषणा HOSTFS_ATTR_ATTR_FLAG	1024

/*
 * If you are very careful, you'll notice that these two are missing:
 *
 * #घोषणा ATTR_KILL_SUID	2048
 * #घोषणा ATTR_KILL_SGID	4096
 *
 * and this is because they were added in 2.5 development.
 * Actually, they are not needed by most ->setattr() methods - they are set by
 * callers of notअगरy_change() to notअगरy that the setuid/setgid bits must be
 * dropped.
 * notअगरy_change() will delete those flags, make sure attr->ia_valid & ATTR_MODE
 * is on, and हटाओ the appropriate bits from attr->ia_mode (attr is a
 * "struct iattr *"). -BlaisorBlade
 */
काष्ठा hostfs_बारpec अणु
	दीर्घ दीर्घ tv_sec;
	दीर्घ दीर्घ tv_nsec;
पूर्ण;

काष्ठा hostfs_iattr अणु
	अचिन्हित पूर्णांक		ia_valid;
	अचिन्हित लघु		ia_mode;
	uid_t			ia_uid;
	gid_t			ia_gid;
	loff_t			ia_size;
	काष्ठा hostfs_बारpec	ia_aसमय;
	काष्ठा hostfs_बारpec	ia_mसमय;
	काष्ठा hostfs_बारpec	ia_स_समय;
पूर्ण;

काष्ठा hostfs_stat अणु
	अचिन्हित दीर्घ दीर्घ ino;
	अचिन्हित पूर्णांक mode;
	अचिन्हित पूर्णांक nlink;
	अचिन्हित पूर्णांक uid;
	अचिन्हित पूर्णांक gid;
	अचिन्हित दीर्घ दीर्घ size;
	काष्ठा hostfs_बारpec aसमय, mसमय, स_समय;
	अचिन्हित पूर्णांक blksize;
	अचिन्हित दीर्घ दीर्घ blocks;
	अचिन्हित पूर्णांक maj;
	अचिन्हित पूर्णांक min;
पूर्ण;

बाह्य पूर्णांक stat_file(स्थिर अक्षर *path, काष्ठा hostfs_stat *p, पूर्णांक fd);
बाह्य पूर्णांक access_file(अक्षर *path, पूर्णांक r, पूर्णांक w, पूर्णांक x);
बाह्य पूर्णांक खोलो_file(अक्षर *path, पूर्णांक r, पूर्णांक w, पूर्णांक append);
बाह्य व्योम *खोलो_dir(अक्षर *path, पूर्णांक *err_out);
बाह्य व्योम seek_dir(व्योम *stream, अचिन्हित दीर्घ दीर्घ pos);
बाह्य अक्षर *पढ़ो_dir(व्योम *stream, अचिन्हित दीर्घ दीर्घ *pos_out,
		      अचिन्हित दीर्घ दीर्घ *ino_out, पूर्णांक *len_out,
		      अचिन्हित पूर्णांक *type_out);
बाह्य व्योम बंद_file(व्योम *stream);
बाह्य पूर्णांक replace_file(पूर्णांक oldfd, पूर्णांक fd);
बाह्य व्योम बंद_dir(व्योम *stream);
बाह्य पूर्णांक पढ़ो_file(पूर्णांक fd, अचिन्हित दीर्घ दीर्घ *offset, अक्षर *buf, पूर्णांक len);
बाह्य पूर्णांक ग_लिखो_file(पूर्णांक fd, अचिन्हित दीर्घ दीर्घ *offset, स्थिर अक्षर *buf,
		      पूर्णांक len);
बाह्य पूर्णांक lseek_file(पूर्णांक fd, दीर्घ दीर्घ offset, पूर्णांक whence);
बाह्य पूर्णांक fsync_file(पूर्णांक fd, पूर्णांक datasync);
बाह्य पूर्णांक file_create(अक्षर *name, पूर्णांक mode);
बाह्य पूर्णांक set_attr(स्थिर अक्षर *file, काष्ठा hostfs_iattr *attrs, पूर्णांक fd);
बाह्य पूर्णांक make_symlink(स्थिर अक्षर *from, स्थिर अक्षर *to);
बाह्य पूर्णांक unlink_file(स्थिर अक्षर *file);
बाह्य पूर्णांक करो_सूची_गढ़ो(स्थिर अक्षर *file, पूर्णांक mode);
बाह्य पूर्णांक hostfs_करो_सूची_हटाओ(स्थिर अक्षर *file);
बाह्य पूर्णांक करो_mknod(स्थिर अक्षर *file, पूर्णांक mode, अचिन्हित पूर्णांक major,
		    अचिन्हित पूर्णांक minor);
बाह्य पूर्णांक link_file(स्थिर अक्षर *to, स्थिर अक्षर *from);
बाह्य पूर्णांक hostfs_करो_पढ़ोlink(अक्षर *file, अक्षर *buf, पूर्णांक size);
बाह्य पूर्णांक नाम_file(अक्षर *from, अक्षर *to);
बाह्य पूर्णांक नाम2_file(अक्षर *from, अक्षर *to, अचिन्हित पूर्णांक flags);
बाह्य पूर्णांक करो_statfs(अक्षर *root, दीर्घ *bsize_out, दीर्घ दीर्घ *blocks_out,
		     दीर्घ दीर्घ *bमुक्त_out, दीर्घ दीर्घ *bavail_out,
		     दीर्घ दीर्घ *files_out, दीर्घ दीर्घ *fमुक्त_out,
		     व्योम *fsid_out, पूर्णांक fsid_size, दीर्घ *namelen_out);

#पूर्ण_अगर
