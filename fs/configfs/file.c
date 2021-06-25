<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * file.c - operations क्रम regular (text) files.
 *
 * Based on sysfs:
 * 	sysfs is Copyright (C) 2001, 2002, 2003 Patrick Mochel
 *
 * configfs Copyright (C) 2005 Oracle.  All rights reserved.
 */

#समावेश <linux/fs.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/uaccess.h>

#समावेश <linux/configfs.h>
#समावेश "configfs_internal.h"

/*
 * A simple attribute can only be 4096 अक्षरacters.  Why 4k?  Because the
 * original code limited it to PAGE_SIZE.  That's a bad idea, though,
 * because an attribute of 16k on ia64 won't work on x86.  So we limit to
 * 4k, our minimum common page size.
 */
#घोषणा SIMPLE_ATTR_SIZE 4096

काष्ठा configfs_buffer अणु
	माप_प्रकार			count;
	loff_t			pos;
	अक्षर			* page;
	काष्ठा configfs_item_operations	* ops;
	काष्ठा mutex		mutex;
	पूर्णांक			needs_पढ़ो_fill;
	bool			पढ़ो_in_progress;
	bool			ग_लिखो_in_progress;
	अक्षर			*bin_buffer;
	पूर्णांक			bin_buffer_size;
	पूर्णांक			cb_max_size;
	काष्ठा config_item	*item;
	काष्ठा module		*owner;
	जोड़ अणु
		काष्ठा configfs_attribute	*attr;
		काष्ठा configfs_bin_attribute	*bin_attr;
	पूर्ण;
पूर्ण;

अटल अंतरभूत काष्ठा configfs_fragment *to_frag(काष्ठा file *file)
अणु
	काष्ठा configfs_dirent *sd = file->f_path.dentry->d_fsdata;

	वापस sd->s_frag;
पूर्ण

अटल पूर्णांक fill_पढ़ो_buffer(काष्ठा file *file, काष्ठा configfs_buffer *buffer)
अणु
	काष्ठा configfs_fragment *frag = to_frag(file);
	sमाप_प्रकार count = -ENOENT;

	अगर (!buffer->page)
		buffer->page = (अक्षर *) get_zeroed_page(GFP_KERNEL);
	अगर (!buffer->page)
		वापस -ENOMEM;

	करोwn_पढ़ो(&frag->frag_sem);
	अगर (!frag->frag_dead)
		count = buffer->attr->show(buffer->item, buffer->page);
	up_पढ़ो(&frag->frag_sem);

	अगर (count < 0)
		वापस count;
	अगर (WARN_ON_ONCE(count > (sमाप_प्रकार)SIMPLE_ATTR_SIZE))
		वापस -EIO;
	buffer->needs_पढ़ो_fill = 0;
	buffer->count = count;
	वापस 0;
पूर्ण

/**
 *	configfs_पढ़ो_file - पढ़ो an attribute.
 *	@file:	file poपूर्णांकer.
 *	@buf:	buffer to fill.
 *	@count:	number of bytes to पढ़ो.
 *	@ppos:	starting offset in file.
 *
 *	Userspace wants to पढ़ो an attribute file. The attribute descriptor
 *	is in the file's ->d_fsdata. The target item is in the directory's
 *	->d_fsdata.
 *
 *	We call fill_पढ़ो_buffer() to allocate and fill the buffer from the
 *	item's show() method exactly once (अगर the पढ़ो is happening from
 *	the beginning of the file). That should fill the entire buffer with
 *	all the data the item has to offer क्रम that attribute.
 *	We then call flush_पढ़ो_buffer() to copy the buffer to userspace
 *	in the increments specअगरied.
 */

अटल sमाप_प्रकार
configfs_पढ़ो_file(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा configfs_buffer *buffer = file->निजी_data;
	sमाप_प्रकार retval = 0;

	mutex_lock(&buffer->mutex);
	अगर (buffer->needs_पढ़ो_fill) अणु
		retval = fill_पढ़ो_buffer(file, buffer);
		अगर (retval)
			जाओ out;
	पूर्ण
	pr_debug("%s: count = %zd, ppos = %lld, buf = %s\n",
		 __func__, count, *ppos, buffer->page);
	retval = simple_पढ़ो_from_buffer(buf, count, ppos, buffer->page,
					 buffer->count);
out:
	mutex_unlock(&buffer->mutex);
	वापस retval;
पूर्ण

/**
 *	configfs_पढ़ो_bin_file - पढ़ो a binary attribute.
 *	@file:	file poपूर्णांकer.
 *	@buf:	buffer to fill.
 *	@count:	number of bytes to पढ़ो.
 *	@ppos:	starting offset in file.
 *
 *	Userspace wants to पढ़ो a binary attribute file. The attribute
 *	descriptor is in the file's ->d_fsdata. The target item is in the
 *	directory's ->d_fsdata.
 *
 *	We check whether we need to refill the buffer. If so we will
 *	call the attributes' attr->पढ़ो() twice. The first समय we
 *	will pass a शून्य as a buffer poपूर्णांकer, which the attributes' method
 *	will use to वापस the size of the buffer required. If no error
 *	occurs we will allocate the buffer using vदो_स्मृति and call
 *	attr->पढ़ो() again passing that buffer as an argument.
 *	Then we just copy to user-space using simple_पढ़ो_from_buffer.
 */

अटल sमाप_प्रकार
configfs_पढ़ो_bin_file(काष्ठा file *file, अक्षर __user *buf,
		       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा configfs_fragment *frag = to_frag(file);
	काष्ठा configfs_buffer *buffer = file->निजी_data;
	sमाप_प्रकार retval = 0;
	sमाप_प्रकार len = min_t(माप_प्रकार, count, PAGE_SIZE);

	mutex_lock(&buffer->mutex);

	/* we करोn't support चयनing पढ़ो/ग_लिखो modes */
	अगर (buffer->ग_लिखो_in_progress) अणु
		retval = -ETXTBSY;
		जाओ out;
	पूर्ण
	buffer->पढ़ो_in_progress = true;

	अगर (buffer->needs_पढ़ो_fill) अणु
		/* perक्रमm first पढ़ो with buf == शून्य to get extent */
		करोwn_पढ़ो(&frag->frag_sem);
		अगर (!frag->frag_dead)
			len = buffer->bin_attr->पढ़ो(buffer->item, शून्य, 0);
		अन्यथा
			len = -ENOENT;
		up_पढ़ो(&frag->frag_sem);
		अगर (len <= 0) अणु
			retval = len;
			जाओ out;
		पूर्ण

		/* करो not exceed the maximum value */
		अगर (buffer->cb_max_size && len > buffer->cb_max_size) अणु
			retval = -EFBIG;
			जाओ out;
		पूर्ण

		buffer->bin_buffer = vदो_स्मृति(len);
		अगर (buffer->bin_buffer == शून्य) अणु
			retval = -ENOMEM;
			जाओ out;
		पूर्ण
		buffer->bin_buffer_size = len;

		/* perक्रमm second पढ़ो to fill buffer */
		करोwn_पढ़ो(&frag->frag_sem);
		अगर (!frag->frag_dead)
			len = buffer->bin_attr->पढ़ो(buffer->item,
						     buffer->bin_buffer, len);
		अन्यथा
			len = -ENOENT;
		up_पढ़ो(&frag->frag_sem);
		अगर (len < 0) अणु
			retval = len;
			vमुक्त(buffer->bin_buffer);
			buffer->bin_buffer_size = 0;
			buffer->bin_buffer = शून्य;
			जाओ out;
		पूर्ण

		buffer->needs_पढ़ो_fill = 0;
	पूर्ण

	retval = simple_पढ़ो_from_buffer(buf, count, ppos, buffer->bin_buffer,
					buffer->bin_buffer_size);
out:
	mutex_unlock(&buffer->mutex);
	वापस retval;
पूर्ण


/**
 *	fill_ग_लिखो_buffer - copy buffer from userspace.
 *	@buffer:	data buffer क्रम file.
 *	@buf:		data from user.
 *	@count:		number of bytes in @userbuf.
 *
 *	Allocate @buffer->page अगर it hasn't been alपढ़ोy, then
 *	copy the user-supplied buffer पूर्णांकo it.
 */

अटल पूर्णांक
fill_ग_लिखो_buffer(काष्ठा configfs_buffer * buffer, स्थिर अक्षर __user * buf, माप_प्रकार count)
अणु
	पूर्णांक error;

	अगर (!buffer->page)
		buffer->page = (अक्षर *)__get_मुक्त_pages(GFP_KERNEL, 0);
	अगर (!buffer->page)
		वापस -ENOMEM;

	अगर (count >= SIMPLE_ATTR_SIZE)
		count = SIMPLE_ATTR_SIZE - 1;
	error = copy_from_user(buffer->page,buf,count);
	buffer->needs_पढ़ो_fill = 1;
	/* अगर buf is assumed to contain a string, terminate it by \0,
	 * so e.g. माला_पूछो() can scan the string easily */
	buffer->page[count] = 0;
	वापस error ? -EFAULT : count;
पूर्ण

अटल पूर्णांक
flush_ग_लिखो_buffer(काष्ठा file *file, काष्ठा configfs_buffer *buffer, माप_प्रकार count)
अणु
	काष्ठा configfs_fragment *frag = to_frag(file);
	पूर्णांक res = -ENOENT;

	करोwn_पढ़ो(&frag->frag_sem);
	अगर (!frag->frag_dead)
		res = buffer->attr->store(buffer->item, buffer->page, count);
	up_पढ़ो(&frag->frag_sem);
	वापस res;
पूर्ण


/**
 *	configfs_ग_लिखो_file - ग_लिखो an attribute.
 *	@file:	file poपूर्णांकer
 *	@buf:	data to ग_लिखो
 *	@count:	number of bytes
 *	@ppos:	starting offset
 *
 *	Similar to configfs_पढ़ो_file(), though working in the opposite direction.
 *	We allocate and fill the data from the user in fill_ग_लिखो_buffer(),
 *	then push it to the config_item in flush_ग_लिखो_buffer().
 *	There is no easy way क्रम us to know अगर userspace is only करोing a partial
 *	ग_लिखो, so we करोn't support them. We expect the entire buffer to come
 *	on the first ग_लिखो.
 *	Hपूर्णांक: अगर you're writing a value, first पढ़ो the file, modअगरy only
 *	the value you're changing, then ग_लिखो entire buffer back.
 */

अटल sमाप_प्रकार
configfs_ग_लिखो_file(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा configfs_buffer *buffer = file->निजी_data;
	sमाप_प्रकार len;

	mutex_lock(&buffer->mutex);
	len = fill_ग_लिखो_buffer(buffer, buf, count);
	अगर (len > 0)
		len = flush_ग_लिखो_buffer(file, buffer, len);
	अगर (len > 0)
		*ppos += len;
	mutex_unlock(&buffer->mutex);
	वापस len;
पूर्ण

/**
 *	configfs_ग_लिखो_bin_file - ग_लिखो a binary attribute.
 *	@file:	file poपूर्णांकer
 *	@buf:	data to ग_लिखो
 *	@count:	number of bytes
 *	@ppos:	starting offset
 *
 *	Writing to a binary attribute file is similar to a normal पढ़ो.
 *	We buffer the consecutive ग_लिखोs (binary attribute files करो not
 *	support lseek) in a continuously growing buffer, but we करोn't
 *	commit until the बंद of the file.
 */

अटल sमाप_प्रकार
configfs_ग_लिखो_bin_file(काष्ठा file *file, स्थिर अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा configfs_buffer *buffer = file->निजी_data;
	व्योम *tbuf = शून्य;
	sमाप_प्रकार len;

	mutex_lock(&buffer->mutex);

	/* we करोn't support चयनing पढ़ो/ग_लिखो modes */
	अगर (buffer->पढ़ो_in_progress) अणु
		len = -ETXTBSY;
		जाओ out;
	पूर्ण
	buffer->ग_लिखो_in_progress = true;

	/* buffer grows? */
	अगर (*ppos + count > buffer->bin_buffer_size) अणु

		अगर (buffer->cb_max_size &&
			*ppos + count > buffer->cb_max_size) अणु
			len = -EFBIG;
			जाओ out;
		पूर्ण

		tbuf = vदो_स्मृति(*ppos + count);
		अगर (tbuf == शून्य) अणु
			len = -ENOMEM;
			जाओ out;
		पूर्ण

		/* copy old contents */
		अगर (buffer->bin_buffer) अणु
			स_नकल(tbuf, buffer->bin_buffer,
				buffer->bin_buffer_size);
			vमुक्त(buffer->bin_buffer);
		पूर्ण

		/* clear the new area */
		स_रखो(tbuf + buffer->bin_buffer_size, 0,
			*ppos + count - buffer->bin_buffer_size);
		buffer->bin_buffer = tbuf;
		buffer->bin_buffer_size = *ppos + count;
	पूर्ण

	len = simple_ग_लिखो_to_buffer(buffer->bin_buffer,
			buffer->bin_buffer_size, ppos, buf, count);
out:
	mutex_unlock(&buffer->mutex);
	वापस len;
पूर्ण

अटल पूर्णांक __configfs_खोलो_file(काष्ठा inode *inode, काष्ठा file *file, पूर्णांक type)
अणु
	काष्ठा dentry *dentry = file->f_path.dentry;
	काष्ठा configfs_fragment *frag = to_frag(file);
	काष्ठा configfs_attribute *attr;
	काष्ठा configfs_buffer *buffer;
	पूर्णांक error;

	error = -ENOMEM;
	buffer = kzalloc(माप(काष्ठा configfs_buffer), GFP_KERNEL);
	अगर (!buffer)
		जाओ out;

	error = -ENOENT;
	करोwn_पढ़ो(&frag->frag_sem);
	अगर (unlikely(frag->frag_dead))
		जाओ out_मुक्त_buffer;

	error = -EINVAL;
	buffer->item = to_item(dentry->d_parent);
	अगर (!buffer->item)
		जाओ out_मुक्त_buffer;

	attr = to_attr(dentry);
	अगर (!attr)
		जाओ out_मुक्त_buffer;

	अगर (type & CONFIGFS_ITEM_BIN_ATTR) अणु
		buffer->bin_attr = to_bin_attr(dentry);
		buffer->cb_max_size = buffer->bin_attr->cb_max_size;
	पूर्ण अन्यथा अणु
		buffer->attr = attr;
	पूर्ण

	buffer->owner = attr->ca_owner;
	/* Grab the module reference क्रम this attribute अगर we have one */
	error = -ENODEV;
	अगर (!try_module_get(buffer->owner))
		जाओ out_मुक्त_buffer;

	error = -EACCES;
	अगर (!buffer->item->ci_type)
		जाओ out_put_module;

	buffer->ops = buffer->item->ci_type->ct_item_ops;

	/* File needs ग_लिखो support.
	 * The inode's perms must say it's ok,
	 * and we must have a store method.
	 */
	अगर (file->f_mode & FMODE_WRITE) अणु
		अगर (!(inode->i_mode & S_IWUGO))
			जाओ out_put_module;
		अगर ((type & CONFIGFS_ITEM_ATTR) && !attr->store)
			जाओ out_put_module;
		अगर ((type & CONFIGFS_ITEM_BIN_ATTR) && !buffer->bin_attr->ग_लिखो)
			जाओ out_put_module;
	पूर्ण

	/* File needs पढ़ो support.
	 * The inode's perms must say it's ok, and we there
	 * must be a show method क्रम it.
	 */
	अगर (file->f_mode & FMODE_READ) अणु
		अगर (!(inode->i_mode & S_IRUGO))
			जाओ out_put_module;
		अगर ((type & CONFIGFS_ITEM_ATTR) && !attr->show)
			जाओ out_put_module;
		अगर ((type & CONFIGFS_ITEM_BIN_ATTR) && !buffer->bin_attr->पढ़ो)
			जाओ out_put_module;
	पूर्ण

	mutex_init(&buffer->mutex);
	buffer->needs_पढ़ो_fill = 1;
	buffer->पढ़ो_in_progress = false;
	buffer->ग_लिखो_in_progress = false;
	file->निजी_data = buffer;
	up_पढ़ो(&frag->frag_sem);
	वापस 0;

out_put_module:
	module_put(buffer->owner);
out_मुक्त_buffer:
	up_पढ़ो(&frag->frag_sem);
	kमुक्त(buffer);
out:
	वापस error;
पूर्ण

अटल पूर्णांक configfs_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा configfs_buffer *buffer = filp->निजी_data;

	module_put(buffer->owner);
	अगर (buffer->page)
		मुक्त_page((अचिन्हित दीर्घ)buffer->page);
	mutex_destroy(&buffer->mutex);
	kमुक्त(buffer);
	वापस 0;
पूर्ण

अटल पूर्णांक configfs_खोलो_file(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस __configfs_खोलो_file(inode, filp, CONFIGFS_ITEM_ATTR);
पूर्ण

अटल पूर्णांक configfs_खोलो_bin_file(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	वापस __configfs_खोलो_file(inode, filp, CONFIGFS_ITEM_BIN_ATTR);
पूर्ण

अटल पूर्णांक configfs_release_bin_file(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा configfs_buffer *buffer = file->निजी_data;

	buffer->पढ़ो_in_progress = false;

	अगर (buffer->ग_लिखो_in_progress) अणु
		काष्ठा configfs_fragment *frag = to_frag(file);
		buffer->ग_लिखो_in_progress = false;

		करोwn_पढ़ो(&frag->frag_sem);
		अगर (!frag->frag_dead) अणु
			/* result of ->release() is ignored */
			buffer->bin_attr->ग_लिखो(buffer->item,
					buffer->bin_buffer,
					buffer->bin_buffer_size);
		पूर्ण
		up_पढ़ो(&frag->frag_sem);
		/* vमुक्त on शून्य is safe */
		vमुक्त(buffer->bin_buffer);
		buffer->bin_buffer = शून्य;
		buffer->bin_buffer_size = 0;
		buffer->needs_पढ़ो_fill = 1;
	पूर्ण

	configfs_release(inode, file);
	वापस 0;
पूर्ण


स्थिर काष्ठा file_operations configfs_file_operations = अणु
	.पढ़ो		= configfs_पढ़ो_file,
	.ग_लिखो		= configfs_ग_लिखो_file,
	.llseek		= generic_file_llseek,
	.खोलो		= configfs_खोलो_file,
	.release	= configfs_release,
पूर्ण;

स्थिर काष्ठा file_operations configfs_bin_file_operations = अणु
	.पढ़ो		= configfs_पढ़ो_bin_file,
	.ग_लिखो		= configfs_ग_लिखो_bin_file,
	.llseek		= शून्य,		/* bin file is not seekable */
	.खोलो		= configfs_खोलो_bin_file,
	.release	= configfs_release_bin_file,
पूर्ण;

/**
 *	configfs_create_file - create an attribute file क्रम an item.
 *	@item:	item we're creating क्रम.
 *	@attr:	atrribute descriptor.
 */

पूर्णांक configfs_create_file(काष्ठा config_item * item, स्थिर काष्ठा configfs_attribute * attr)
अणु
	काष्ठा dentry *dir = item->ci_dentry;
	काष्ठा configfs_dirent *parent_sd = dir->d_fsdata;
	umode_t mode = (attr->ca_mode & S_IALLUGO) | S_IFREG;
	पूर्णांक error = 0;

	inode_lock_nested(d_inode(dir), I_MUTEX_NORMAL);
	error = configfs_make_dirent(parent_sd, शून्य, (व्योम *) attr, mode,
				     CONFIGFS_ITEM_ATTR, parent_sd->s_frag);
	inode_unlock(d_inode(dir));

	वापस error;
पूर्ण

/**
 *	configfs_create_bin_file - create a binary attribute file क्रम an item.
 *	@item:	item we're creating क्रम.
 *	@attr:	atrribute descriptor.
 */

पूर्णांक configfs_create_bin_file(काष्ठा config_item *item,
		स्थिर काष्ठा configfs_bin_attribute *bin_attr)
अणु
	काष्ठा dentry *dir = item->ci_dentry;
	काष्ठा configfs_dirent *parent_sd = dir->d_fsdata;
	umode_t mode = (bin_attr->cb_attr.ca_mode & S_IALLUGO) | S_IFREG;
	पूर्णांक error = 0;

	inode_lock_nested(dir->d_inode, I_MUTEX_NORMAL);
	error = configfs_make_dirent(parent_sd, शून्य, (व्योम *) bin_attr, mode,
				     CONFIGFS_ITEM_BIN_ATTR, parent_sd->s_frag);
	inode_unlock(dir->d_inode);

	वापस error;
पूर्ण
