<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/fs.h>
#समावेश <linux/fs_काष्ठा.h>
#समावेश <linux/kernel_पढ़ो_file.h>
#समावेश <linux/security.h>
#समावेश <linux/vदो_स्मृति.h>

/**
 * kernel_पढ़ो_file() - पढ़ो file contents पूर्णांकo a kernel buffer
 *
 * @file	file to पढ़ो from
 * @offset	where to start पढ़ोing from (see below).
 * @buf		poपूर्णांकer to a "void *" buffer क्रम पढ़ोing पूर्णांकo (अगर
 *		*@buf is शून्य, a buffer will be allocated, and
 *		@buf_size will be ignored)
 * @buf_size	size of buf, अगर alपढ़ोy allocated. If @buf not
 *		allocated, this is the largest size to allocate.
 * @file_size	अगर non-शून्य, the full size of @file will be
 *		written here.
 * @id		the kernel_पढ़ो_file_id identअगरying the type of
 *		file contents being पढ़ो (क्रम LSMs to examine)
 *
 * @offset must be 0 unless both @buf and @file_size are non-शून्य
 * (i.e. the caller must be expecting to पढ़ो partial file contents
 * via an alपढ़ोy-allocated @buf, in at most @buf_size chunks, and
 * will be able to determine when the entire file was पढ़ो by
 * checking @file_size). This isn't a recommended way to पढ़ो a
 * file, though, since it is possible that the contents might
 * change between calls to kernel_पढ़ो_file().
 *
 * Returns number of bytes पढ़ो (no single पढ़ो will be bigger
 * than पूर्णांक_उच्च), or negative on error.
 *
 */
पूर्णांक kernel_पढ़ो_file(काष्ठा file *file, loff_t offset, व्योम **buf,
		     माप_प्रकार buf_size, माप_प्रकार *file_size,
		     क्रमागत kernel_पढ़ो_file_id id)
अणु
	loff_t i_size, pos;
	माप_प्रकार copied;
	व्योम *allocated = शून्य;
	bool whole_file;
	पूर्णांक ret;

	अगर (offset != 0 && (!*buf || !file_size))
		वापस -EINVAL;

	अगर (!S_ISREG(file_inode(file)->i_mode))
		वापस -EINVAL;

	ret = deny_ग_लिखो_access(file);
	अगर (ret)
		वापस ret;

	i_size = i_size_पढ़ो(file_inode(file));
	अगर (i_size <= 0) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण
	/* The file is too big क्रम sane activities. */
	अगर (i_size > पूर्णांक_उच्च) अणु
		ret = -EFBIG;
		जाओ out;
	पूर्ण
	/* The entire file cannot be पढ़ो in one buffer. */
	अगर (!file_size && offset == 0 && i_size > buf_size) अणु
		ret = -EFBIG;
		जाओ out;
	पूर्ण

	whole_file = (offset == 0 && i_size <= buf_size);
	ret = security_kernel_पढ़ो_file(file, id, whole_file);
	अगर (ret)
		जाओ out;

	अगर (file_size)
		*file_size = i_size;

	अगर (!*buf)
		*buf = allocated = vदो_स्मृति(i_size);
	अगर (!*buf) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	pos = offset;
	copied = 0;
	जबतक (copied < buf_size) अणु
		sमाप_प्रकार bytes;
		माप_प्रकार wanted = min_t(माप_प्रकार, buf_size - copied,
					      i_size - pos);

		bytes = kernel_पढ़ो(file, *buf + copied, wanted, &pos);
		अगर (bytes < 0) अणु
			ret = bytes;
			जाओ out_मुक्त;
		पूर्ण

		अगर (bytes == 0)
			अवरोध;
		copied += bytes;
	पूर्ण

	अगर (whole_file) अणु
		अगर (pos != i_size) अणु
			ret = -EIO;
			जाओ out_मुक्त;
		पूर्ण

		ret = security_kernel_post_पढ़ो_file(file, *buf, i_size, id);
	पूर्ण

out_मुक्त:
	अगर (ret < 0) अणु
		अगर (allocated) अणु
			vमुक्त(*buf);
			*buf = शून्य;
		पूर्ण
	पूर्ण

out:
	allow_ग_लिखो_access(file);
	वापस ret == 0 ? copied : ret;
पूर्ण
EXPORT_SYMBOL_GPL(kernel_पढ़ो_file);

पूर्णांक kernel_पढ़ो_file_from_path(स्थिर अक्षर *path, loff_t offset, व्योम **buf,
			       माप_प्रकार buf_size, माप_प्रकार *file_size,
			       क्रमागत kernel_पढ़ो_file_id id)
अणु
	काष्ठा file *file;
	पूर्णांक ret;

	अगर (!path || !*path)
		वापस -EINVAL;

	file = filp_खोलो(path, O_RDONLY, 0);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	ret = kernel_पढ़ो_file(file, offset, buf, buf_size, file_size, id);
	fput(file);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kernel_पढ़ो_file_from_path);

पूर्णांक kernel_पढ़ो_file_from_path_initns(स्थिर अक्षर *path, loff_t offset,
				      व्योम **buf, माप_प्रकार buf_size,
				      माप_प्रकार *file_size,
				      क्रमागत kernel_पढ़ो_file_id id)
अणु
	काष्ठा file *file;
	काष्ठा path root;
	पूर्णांक ret;

	अगर (!path || !*path)
		वापस -EINVAL;

	task_lock(&init_task);
	get_fs_root(init_task.fs, &root);
	task_unlock(&init_task);

	file = file_खोलो_root(root.dentry, root.mnt, path, O_RDONLY, 0);
	path_put(&root);
	अगर (IS_ERR(file))
		वापस PTR_ERR(file);

	ret = kernel_पढ़ो_file(file, offset, buf, buf_size, file_size, id);
	fput(file);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kernel_पढ़ो_file_from_path_initns);

पूर्णांक kernel_पढ़ो_file_from_fd(पूर्णांक fd, loff_t offset, व्योम **buf,
			     माप_प्रकार buf_size, माप_प्रकार *file_size,
			     क्रमागत kernel_पढ़ो_file_id id)
अणु
	काष्ठा fd f = fdget(fd);
	पूर्णांक ret = -EBADF;

	अगर (!f.file)
		जाओ out;

	ret = kernel_पढ़ो_file(f.file, offset, buf, buf_size, file_size, id);
out:
	fdput(f);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(kernel_पढ़ो_file_from_fd);
