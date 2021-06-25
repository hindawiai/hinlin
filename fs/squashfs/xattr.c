<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Squashfs - a compressed पढ़ो only fileप्रणाली क्रम Linux
 *
 * Copyright (c) 2010
 * Phillip Lougher <phillip@squashfs.org.uk>
 *
 * xattr.c
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/माला.स>
#समावेश <linux/fs.h>
#समावेश <linux/vfs.h>
#समावेश <linux/xattr.h>
#समावेश <linux/slab.h>

#समावेश "squashfs_fs.h"
#समावेश "squashfs_fs_sb.h"
#समावेश "squashfs_fs_i.h"
#समावेश "squashfs.h"

अटल स्थिर काष्ठा xattr_handler *squashfs_xattr_handler(पूर्णांक);

sमाप_प्रकार squashfs_listxattr(काष्ठा dentry *d, अक्षर *buffer,
	माप_प्रकार buffer_size)
अणु
	काष्ठा inode *inode = d_inode(d);
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	u64 start = SQUASHFS_XATTR_BLK(squashfs_i(inode)->xattr)
						 + msblk->xattr_table;
	पूर्णांक offset = SQUASHFS_XATTR_OFFSET(squashfs_i(inode)->xattr);
	पूर्णांक count = squashfs_i(inode)->xattr_count;
	माप_प्रकार rest = buffer_size;
	पूर्णांक err;

	/* check that the file प्रणाली has xattrs */
	अगर (msblk->xattr_id_table == शून्य)
		वापस -EOPNOTSUPP;

	/* loop पढ़ोing each xattr name */
	जबतक (count--) अणु
		काष्ठा squashfs_xattr_entry entry;
		काष्ठा squashfs_xattr_val val;
		स्थिर काष्ठा xattr_handler *handler;
		पूर्णांक name_size;

		err = squashfs_पढ़ो_metadata(sb, &entry, &start, &offset,
							माप(entry));
		अगर (err < 0)
			जाओ failed;

		name_size = le16_to_cpu(entry.size);
		handler = squashfs_xattr_handler(le16_to_cpu(entry.type));
		अगर (handler && (!handler->list || handler->list(d))) अणु
			स्थिर अक्षर *prefix = handler->prefix ?: handler->name;
			माप_प्रकार prefix_size = म_माप(prefix);

			अगर (buffer) अणु
				अगर (prefix_size + name_size + 1 > rest) अणु
					err = -दुस्फल;
					जाओ failed;
				पूर्ण
				स_नकल(buffer, prefix, prefix_size);
				buffer += prefix_size;
			पूर्ण
			err = squashfs_पढ़ो_metadata(sb, buffer, &start,
				&offset, name_size);
			अगर (err < 0)
				जाओ failed;
			अगर (buffer) अणु
				buffer[name_size] = '\0';
				buffer += name_size + 1;
			पूर्ण
			rest -= prefix_size + name_size + 1;
		पूर्ण अन्यथा  अणु
			/* no handler or insuffficient privileges, so skip */
			err = squashfs_पढ़ो_metadata(sb, शून्य, &start,
				&offset, name_size);
			अगर (err < 0)
				जाओ failed;
		पूर्ण


		/* skip reमुख्यing xattr entry */
		err = squashfs_पढ़ो_metadata(sb, &val, &start, &offset,
						माप(val));
		अगर (err < 0)
			जाओ failed;

		err = squashfs_पढ़ो_metadata(sb, शून्य, &start, &offset,
						le32_to_cpu(val.vsize));
		अगर (err < 0)
			जाओ failed;
	पूर्ण
	err = buffer_size - rest;

failed:
	वापस err;
पूर्ण


अटल पूर्णांक squashfs_xattr_get(काष्ठा inode *inode, पूर्णांक name_index,
	स्थिर अक्षर *name, व्योम *buffer, माप_प्रकार buffer_size)
अणु
	काष्ठा super_block *sb = inode->i_sb;
	काष्ठा squashfs_sb_info *msblk = sb->s_fs_info;
	u64 start = SQUASHFS_XATTR_BLK(squashfs_i(inode)->xattr)
						 + msblk->xattr_table;
	पूर्णांक offset = SQUASHFS_XATTR_OFFSET(squashfs_i(inode)->xattr);
	पूर्णांक count = squashfs_i(inode)->xattr_count;
	पूर्णांक name_len = म_माप(name);
	पूर्णांक err, vsize;
	अक्षर *target = kदो_स्मृति(name_len, GFP_KERNEL);

	अगर (target == शून्य)
		वापस  -ENOMEM;

	/* loop पढ़ोing each xattr name */
	क्रम (; count; count--) अणु
		काष्ठा squashfs_xattr_entry entry;
		काष्ठा squashfs_xattr_val val;
		पूर्णांक type, prefix, name_size;

		err = squashfs_पढ़ो_metadata(sb, &entry, &start, &offset,
							माप(entry));
		अगर (err < 0)
			जाओ failed;

		name_size = le16_to_cpu(entry.size);
		type = le16_to_cpu(entry.type);
		prefix = type & SQUASHFS_XATTR_PREFIX_MASK;

		अगर (prefix == name_index && name_size == name_len)
			err = squashfs_पढ़ो_metadata(sb, target, &start,
						&offset, name_size);
		अन्यथा
			err = squashfs_पढ़ो_metadata(sb, शून्य, &start,
						&offset, name_size);
		अगर (err < 0)
			जाओ failed;

		अगर (prefix == name_index && name_size == name_len &&
					म_भेदन(target, name, name_size) == 0) अणु
			/* found xattr */
			अगर (type & SQUASHFS_XATTR_VALUE_OOL) अणु
				__le64 xattr_val;
				u64 xattr;
				/* val is a reference to the real location */
				err = squashfs_पढ़ो_metadata(sb, &val, &start,
						&offset, माप(val));
				अगर (err < 0)
					जाओ failed;
				err = squashfs_पढ़ो_metadata(sb, &xattr_val,
					&start, &offset, माप(xattr_val));
				अगर (err < 0)
					जाओ failed;
				xattr = le64_to_cpu(xattr_val);
				start = SQUASHFS_XATTR_BLK(xattr) +
							msblk->xattr_table;
				offset = SQUASHFS_XATTR_OFFSET(xattr);
			पूर्ण
			/* पढ़ो xattr value */
			err = squashfs_पढ़ो_metadata(sb, &val, &start, &offset,
							माप(val));
			अगर (err < 0)
				जाओ failed;

			vsize = le32_to_cpu(val.vsize);
			अगर (buffer) अणु
				अगर (vsize > buffer_size) अणु
					err = -दुस्फल;
					जाओ failed;
				पूर्ण
				err = squashfs_पढ़ो_metadata(sb, buffer, &start,
					 &offset, vsize);
				अगर (err < 0)
					जाओ failed;
			पूर्ण
			अवरोध;
		पूर्ण

		/* no match, skip reमुख्यing xattr entry */
		err = squashfs_पढ़ो_metadata(sb, &val, &start, &offset,
							माप(val));
		अगर (err < 0)
			जाओ failed;
		err = squashfs_पढ़ो_metadata(sb, शून्य, &start, &offset,
						le32_to_cpu(val.vsize));
		अगर (err < 0)
			जाओ failed;
	पूर्ण
	err = count ? vsize : -ENODATA;

failed:
	kमुक्त(target);
	वापस err;
पूर्ण


अटल पूर्णांक squashfs_xattr_handler_get(स्थिर काष्ठा xattr_handler *handler,
				      काष्ठा dentry *unused,
				      काष्ठा inode *inode,
				      स्थिर अक्षर *name,
				      व्योम *buffer, माप_प्रकार size)
अणु
	वापस squashfs_xattr_get(inode, handler->flags, name,
		buffer, size);
पूर्ण

/*
 * User namespace support
 */
अटल स्थिर काष्ठा xattr_handler squashfs_xattr_user_handler = अणु
	.prefix	= XATTR_USER_PREFIX,
	.flags	= SQUASHFS_XATTR_USER,
	.get	= squashfs_xattr_handler_get
पूर्ण;

/*
 * Trusted namespace support
 */
अटल bool squashfs_trusted_xattr_handler_list(काष्ठा dentry *d)
अणु
	वापस capable(CAP_SYS_ADMIN);
पूर्ण

अटल स्थिर काष्ठा xattr_handler squashfs_xattr_trusted_handler = अणु
	.prefix	= XATTR_TRUSTED_PREFIX,
	.flags	= SQUASHFS_XATTR_TRUSTED,
	.list	= squashfs_trusted_xattr_handler_list,
	.get	= squashfs_xattr_handler_get
पूर्ण;

/*
 * Security namespace support
 */
अटल स्थिर काष्ठा xattr_handler squashfs_xattr_security_handler = अणु
	.prefix	= XATTR_SECURITY_PREFIX,
	.flags	= SQUASHFS_XATTR_SECURITY,
	.get	= squashfs_xattr_handler_get
पूर्ण;

अटल स्थिर काष्ठा xattr_handler *squashfs_xattr_handler(पूर्णांक type)
अणु
	अगर (type & ~(SQUASHFS_XATTR_PREFIX_MASK | SQUASHFS_XATTR_VALUE_OOL))
		/* ignore unrecognised type */
		वापस शून्य;

	चयन (type & SQUASHFS_XATTR_PREFIX_MASK) अणु
	हाल SQUASHFS_XATTR_USER:
		वापस &squashfs_xattr_user_handler;
	हाल SQUASHFS_XATTR_TRUSTED:
		वापस &squashfs_xattr_trusted_handler;
	हाल SQUASHFS_XATTR_SECURITY:
		वापस &squashfs_xattr_security_handler;
	शेष:
		/* ignore unrecognised type */
		वापस शून्य;
	पूर्ण
पूर्ण

स्थिर काष्ठा xattr_handler *squashfs_xattr_handlers[] = अणु
	&squashfs_xattr_user_handler,
	&squashfs_xattr_trusted_handler,
	&squashfs_xattr_security_handler,
	शून्य
पूर्ण;

