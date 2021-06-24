<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

पूर्णांक __init init_mount(स्थिर अक्षर *dev_name, स्थिर अक्षर *dir_name,
		स्थिर अक्षर *type_page, अचिन्हित दीर्घ flags, व्योम *data_page);
पूर्णांक __init init_umount(स्थिर अक्षर *name, पूर्णांक flags);
पूर्णांक __init init_स_बदलो(स्थिर अक्षर *filename);
पूर्णांक __init init_chroot(स्थिर अक्षर *filename);
पूर्णांक __init init_chown(स्थिर अक्षर *filename, uid_t user, gid_t group, पूर्णांक flags);
पूर्णांक __init init_chmod(स्थिर अक्षर *filename, umode_t mode);
पूर्णांक __init init_eaccess(स्थिर अक्षर *filename);
पूर्णांक __init init_stat(स्थिर अक्षर *filename, काष्ठा kstat *stat, पूर्णांक flags);
पूर्णांक __init init_mknod(स्थिर अक्षर *filename, umode_t mode, अचिन्हित पूर्णांक dev);
पूर्णांक __init init_link(स्थिर अक्षर *oldname, स्थिर अक्षर *newname);
पूर्णांक __init init_symlink(स्थिर अक्षर *oldname, स्थिर अक्षर *newname);
पूर्णांक __init init_unlink(स्थिर अक्षर *pathname);
पूर्णांक __init init_सूची_गढ़ो(स्थिर अक्षर *pathname, umode_t mode);
पूर्णांक __init init_सूची_हटाओ(स्थिर अक्षर *pathname);
पूर्णांक __init init_uबार(अक्षर *filename, काष्ठा बारpec64 *ts);
पूर्णांक __init init_dup(काष्ठा file *file);
