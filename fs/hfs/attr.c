<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/hfs/attr.c
 *
 * (C) 2003 Ardis Technologies <roman@ardistech.com>
 *
 * Export hfs data via xattr
 */


#समावेश <linux/fs.h>
#समावेश <linux/xattr.h>

#समावेश "hfs_fs.h"
#समावेश "btree.h"

क्रमागत hfs_xattr_type अणु
	HFS_TYPE,
	HFS_CREATOR,
पूर्ण;

अटल पूर्णांक __hfs_setxattr(काष्ठा inode *inode, क्रमागत hfs_xattr_type type,
			  स्थिर व्योम *value, माप_प्रकार size, पूर्णांक flags)
अणु
	काष्ठा hfs_find_data fd;
	hfs_cat_rec rec;
	काष्ठा hfs_cat_file *file;
	पूर्णांक res;

	अगर (!S_ISREG(inode->i_mode) || HFS_IS_RSRC(inode))
		वापस -EOPNOTSUPP;

	res = hfs_find_init(HFS_SB(inode->i_sb)->cat_tree, &fd);
	अगर (res)
		वापस res;
	fd.search_key->cat = HFS_I(inode)->cat_key;
	res = hfs_brec_find(&fd);
	अगर (res)
		जाओ out;
	hfs_bnode_पढ़ो(fd.bnode, &rec, fd.entryoffset,
			माप(काष्ठा hfs_cat_file));
	file = &rec.file;

	चयन (type) अणु
	हाल HFS_TYPE:
		अगर (size == 4)
			स_नकल(&file->UsrWds.fdType, value, 4);
		अन्यथा
			res = -दुस्फल;
		अवरोध;

	हाल HFS_CREATOR:
		अगर (size == 4)
			स_नकल(&file->UsrWds.fdCreator, value, 4);
		अन्यथा
			res = -दुस्फल;
		अवरोध;
	पूर्ण

	अगर (!res)
		hfs_bnode_ग_लिखो(fd.bnode, &rec, fd.entryoffset,
				माप(काष्ठा hfs_cat_file));
out:
	hfs_find_निकास(&fd);
	वापस res;
पूर्ण

अटल sमाप_प्रकार __hfs_getxattr(काष्ठा inode *inode, क्रमागत hfs_xattr_type type,
			      व्योम *value, माप_प्रकार size)
अणु
	काष्ठा hfs_find_data fd;
	hfs_cat_rec rec;
	काष्ठा hfs_cat_file *file;
	sमाप_प्रकार res = 0;

	अगर (!S_ISREG(inode->i_mode) || HFS_IS_RSRC(inode))
		वापस -EOPNOTSUPP;

	अगर (size) अणु
		res = hfs_find_init(HFS_SB(inode->i_sb)->cat_tree, &fd);
		अगर (res)
			वापस res;
		fd.search_key->cat = HFS_I(inode)->cat_key;
		res = hfs_brec_find(&fd);
		अगर (res)
			जाओ out;
		hfs_bnode_पढ़ो(fd.bnode, &rec, fd.entryoffset,
				माप(काष्ठा hfs_cat_file));
	पूर्ण
	file = &rec.file;

	चयन (type) अणु
	हाल HFS_TYPE:
		अगर (size >= 4) अणु
			स_नकल(value, &file->UsrWds.fdType, 4);
			res = 4;
		पूर्ण अन्यथा
			res = size ? -दुस्फल : 4;
		अवरोध;

	हाल HFS_CREATOR:
		अगर (size >= 4) अणु
			स_नकल(value, &file->UsrWds.fdCreator, 4);
			res = 4;
		पूर्ण अन्यथा
			res = size ? -दुस्फल : 4;
		अवरोध;
	पूर्ण

out:
	अगर (size)
		hfs_find_निकास(&fd);
	वापस res;
पूर्ण

अटल पूर्णांक hfs_xattr_get(स्थिर काष्ठा xattr_handler *handler,
			 काष्ठा dentry *unused, काष्ठा inode *inode,
			 स्थिर अक्षर *name, व्योम *value, माप_प्रकार size)
अणु
	वापस __hfs_getxattr(inode, handler->flags, value, size);
पूर्ण

अटल पूर्णांक hfs_xattr_set(स्थिर काष्ठा xattr_handler *handler,
			 काष्ठा user_namespace *mnt_userns,
			 काष्ठा dentry *unused, काष्ठा inode *inode,
			 स्थिर अक्षर *name, स्थिर व्योम *value, माप_प्रकार size,
			 पूर्णांक flags)
अणु
	अगर (!value)
		वापस -EOPNOTSUPP;

	वापस __hfs_setxattr(inode, handler->flags, value, size, flags);
पूर्ण

अटल स्थिर काष्ठा xattr_handler hfs_creator_handler = अणु
	.name = "hfs.creator",
	.flags = HFS_CREATOR,
	.get = hfs_xattr_get,
	.set = hfs_xattr_set,
पूर्ण;

अटल स्थिर काष्ठा xattr_handler hfs_type_handler = अणु
	.name = "hfs.type",
	.flags = HFS_TYPE,
	.get = hfs_xattr_get,
	.set = hfs_xattr_set,
पूर्ण;

स्थिर काष्ठा xattr_handler *hfs_xattr_handlers[] = अणु
	&hfs_creator_handler,
	&hfs_type_handler,
	शून्य
पूर्ण;
