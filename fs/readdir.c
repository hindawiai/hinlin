<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/सूची_पढ़ो.c
 *
 *  Copyright (C) 1995  Linus Torvalds
 */

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/समय.स>
#समावेश <linux/mm.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/स्थिति.स>
#समावेश <linux/file.h>
#समावेश <linux/fs.h>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/dirent.h>
#समावेश <linux/security.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/unistd.h>
#समावेश <linux/compat.h>
#समावेश <linux/uaccess.h>

#समावेश <यंत्र/unaligned.h>

/*
 * Note the "unsafe_put_user() semantics: we जाओ a
 * label क्रम errors.
 */
#घोषणा unsafe_copy_dirent_name(_dst, _src, _len, label) करो अणु	\
	अक्षर __user *dst = (_dst);				\
	स्थिर अक्षर *src = (_src);				\
	माप_प्रकार len = (_len);					\
	unsafe_put_user(0, dst+len, label);			\
	unsafe_copy_to_user(dst, src, len, label);		\
पूर्ण जबतक (0)


पूर्णांक iterate_dir(काष्ठा file *file, काष्ठा dir_context *ctx)
अणु
	काष्ठा inode *inode = file_inode(file);
	bool shared = false;
	पूर्णांक res = -ENOTसूची;
	अगर (file->f_op->iterate_shared)
		shared = true;
	अन्यथा अगर (!file->f_op->iterate)
		जाओ out;

	res = security_file_permission(file, MAY_READ);
	अगर (res)
		जाओ out;

	अगर (shared)
		res = करोwn_पढ़ो_समाप्तable(&inode->i_rwsem);
	अन्यथा
		res = करोwn_ग_लिखो_समाप्तable(&inode->i_rwsem);
	अगर (res)
		जाओ out;

	res = -ENOENT;
	अगर (!IS_DEADसूची(inode)) अणु
		ctx->pos = file->f_pos;
		अगर (shared)
			res = file->f_op->iterate_shared(file, ctx);
		अन्यथा
			res = file->f_op->iterate(file, ctx);
		file->f_pos = ctx->pos;
		fsnotअगरy_access(file);
		file_accessed(file);
	पूर्ण
	अगर (shared)
		inode_unlock_shared(inode);
	अन्यथा
		inode_unlock(inode);
out:
	वापस res;
पूर्ण
EXPORT_SYMBOL(iterate_dir);

/*
 * POSIX says that a dirent name cannot contain शून्य or a '/'.
 *
 * It's not 100% clear what we should really करो in this हाल.
 * The fileप्रणाली is clearly corrupted, but वापसing a hard
 * error means that you now करोn't see any of the other names
 * either, so that isn't a perfect alternative.
 *
 * And अगर you वापस an error, what error करो you use? Several
 * fileप्रणालीs seem to have decided on EUCLEAN being the error
 * code क्रम EFSCORRUPTED, and that may be the error to use. Or
 * just EIO, which is perhaps more obvious to users.
 *
 * In order to see the other file names in the directory, the
 * caller might want to make this a "soft" error: skip the
 * entry, and वापस the error at the end instead.
 *
 * Note that this should likely करो a "memchr(name, 0, len)"
 * check too, since that would be fileप्रणाली corruption as
 * well. However, that हाल can't actually confuse user space,
 * which has to करो a म_माप() on the name anyway to find the
 * filename length, and the above "soft error" worry means
 * that it's probably better left alone until we have that
 * issue clarअगरied.
 *
 * Note the PATH_MAX check - it's arbitrary but the real
 * kernel limit on a possible path component, not NAME_MAX,
 * which is the technical standard limit.
 */
अटल पूर्णांक verअगरy_dirent_name(स्थिर अक्षर *name, पूर्णांक len)
अणु
	अगर (len <= 0 || len >= PATH_MAX)
		वापस -EIO;
	अगर (स_प्रथम(name, '/', len))
		वापस -EIO;
	वापस 0;
पूर्ण

/*
 * Traditional linux सूची_पढ़ो() handling..
 *
 * "count=1" is a special हाल, meaning that the buffer is one
 * dirent-काष्ठाure in size and that the code can't handle more
 * anyway. Thus the special "fillonedir()" function क्रम that
 * हाल (the low-level handlers करोn't need to care about this).
 */

#अगर_घोषित __ARCH_WANT_OLD_READसूची

काष्ठा old_linux_dirent अणु
	अचिन्हित दीर्घ	d_ino;
	अचिन्हित दीर्घ	d_offset;
	अचिन्हित लघु	d_namlen;
	अक्षर		d_name[1];
पूर्ण;

काष्ठा सूची_पढ़ो_callback अणु
	काष्ठा dir_context ctx;
	काष्ठा old_linux_dirent __user * dirent;
	पूर्णांक result;
पूर्ण;

अटल पूर्णांक fillonedir(काष्ठा dir_context *ctx, स्थिर अक्षर *name, पूर्णांक namlen,
		      loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा सूची_पढ़ो_callback *buf =
		container_of(ctx, काष्ठा सूची_पढ़ो_callback, ctx);
	काष्ठा old_linux_dirent __user * dirent;
	अचिन्हित दीर्घ d_ino;

	अगर (buf->result)
		वापस -EINVAL;
	buf->result = verअगरy_dirent_name(name, namlen);
	अगर (buf->result < 0)
		वापस buf->result;
	d_ino = ino;
	अगर (माप(d_ino) < माप(ino) && d_ino != ino) अणु
		buf->result = -EOVERFLOW;
		वापस -EOVERFLOW;
	पूर्ण
	buf->result++;
	dirent = buf->dirent;
	अगर (!user_ग_लिखो_access_begin(dirent,
			(अचिन्हित दीर्घ)(dirent->d_name + namlen + 1) -
				(अचिन्हित दीर्घ)dirent))
		जाओ efault;
	unsafe_put_user(d_ino, &dirent->d_ino, efault_end);
	unsafe_put_user(offset, &dirent->d_offset, efault_end);
	unsafe_put_user(namlen, &dirent->d_namlen, efault_end);
	unsafe_copy_dirent_name(dirent->d_name, name, namlen, efault_end);
	user_ग_लिखो_access_end();
	वापस 0;
efault_end:
	user_ग_लिखो_access_end();
efault:
	buf->result = -EFAULT;
	वापस -EFAULT;
पूर्ण

SYSCALL_DEFINE3(old_सूची_पढ़ो, अचिन्हित पूर्णांक, fd,
		काष्ठा old_linux_dirent __user *, dirent, अचिन्हित पूर्णांक, count)
अणु
	पूर्णांक error;
	काष्ठा fd f = fdget_pos(fd);
	काष्ठा सूची_पढ़ो_callback buf = अणु
		.ctx.actor = fillonedir,
		.dirent = dirent
	पूर्ण;

	अगर (!f.file)
		वापस -EBADF;

	error = iterate_dir(f.file, &buf.ctx);
	अगर (buf.result)
		error = buf.result;

	fdput_pos(f);
	वापस error;
पूर्ण

#पूर्ण_अगर /* __ARCH_WANT_OLD_READसूची */

/*
 * New, all-improved, singing, dancing, iBCS2-compliant getdents()
 * पूर्णांकerface. 
 */
काष्ठा linux_dirent अणु
	अचिन्हित दीर्घ	d_ino;
	अचिन्हित दीर्घ	d_off;
	अचिन्हित लघु	d_reclen;
	अक्षर		d_name[1];
पूर्ण;

काष्ठा getdents_callback अणु
	काष्ठा dir_context ctx;
	काष्ठा linux_dirent __user * current_dir;
	पूर्णांक prev_reclen;
	पूर्णांक count;
	पूर्णांक error;
पूर्ण;

अटल पूर्णांक filldir(काष्ठा dir_context *ctx, स्थिर अक्षर *name, पूर्णांक namlen,
		   loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा linux_dirent __user *dirent, *prev;
	काष्ठा getdents_callback *buf =
		container_of(ctx, काष्ठा getdents_callback, ctx);
	अचिन्हित दीर्घ d_ino;
	पूर्णांक reclen = ALIGN(दुरत्व(काष्ठा linux_dirent, d_name) + namlen + 2,
		माप(दीर्घ));
	पूर्णांक prev_reclen;

	buf->error = verअगरy_dirent_name(name, namlen);
	अगर (unlikely(buf->error))
		वापस buf->error;
	buf->error = -EINVAL;	/* only used अगर we fail.. */
	अगर (reclen > buf->count)
		वापस -EINVAL;
	d_ino = ino;
	अगर (माप(d_ino) < माप(ino) && d_ino != ino) अणु
		buf->error = -EOVERFLOW;
		वापस -EOVERFLOW;
	पूर्ण
	prev_reclen = buf->prev_reclen;
	अगर (prev_reclen && संकेत_pending(current))
		वापस -EINTR;
	dirent = buf->current_dir;
	prev = (व्योम __user *) dirent - prev_reclen;
	अगर (!user_ग_लिखो_access_begin(prev, reclen + prev_reclen))
		जाओ efault;

	/* This might be 'dirent->d_off', but अगर so it will get overwritten */
	unsafe_put_user(offset, &prev->d_off, efault_end);
	unsafe_put_user(d_ino, &dirent->d_ino, efault_end);
	unsafe_put_user(reclen, &dirent->d_reclen, efault_end);
	unsafe_put_user(d_type, (अक्षर __user *) dirent + reclen - 1, efault_end);
	unsafe_copy_dirent_name(dirent->d_name, name, namlen, efault_end);
	user_ग_लिखो_access_end();

	buf->current_dir = (व्योम __user *)dirent + reclen;
	buf->prev_reclen = reclen;
	buf->count -= reclen;
	वापस 0;
efault_end:
	user_ग_लिखो_access_end();
efault:
	buf->error = -EFAULT;
	वापस -EFAULT;
पूर्ण

SYSCALL_DEFINE3(getdents, अचिन्हित पूर्णांक, fd,
		काष्ठा linux_dirent __user *, dirent, अचिन्हित पूर्णांक, count)
अणु
	काष्ठा fd f;
	काष्ठा getdents_callback buf = अणु
		.ctx.actor = filldir,
		.count = count,
		.current_dir = dirent
	पूर्ण;
	पूर्णांक error;

	f = fdget_pos(fd);
	अगर (!f.file)
		वापस -EBADF;

	error = iterate_dir(f.file, &buf.ctx);
	अगर (error >= 0)
		error = buf.error;
	अगर (buf.prev_reclen) अणु
		काष्ठा linux_dirent __user * lastdirent;
		lastdirent = (व्योम __user *)buf.current_dir - buf.prev_reclen;

		अगर (put_user(buf.ctx.pos, &lastdirent->d_off))
			error = -EFAULT;
		अन्यथा
			error = count - buf.count;
	पूर्ण
	fdput_pos(f);
	वापस error;
पूर्ण

काष्ठा getdents_callback64 अणु
	काष्ठा dir_context ctx;
	काष्ठा linux_dirent64 __user * current_dir;
	पूर्णांक prev_reclen;
	पूर्णांक count;
	पूर्णांक error;
पूर्ण;

अटल पूर्णांक filldir64(काष्ठा dir_context *ctx, स्थिर अक्षर *name, पूर्णांक namlen,
		     loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा linux_dirent64 __user *dirent, *prev;
	काष्ठा getdents_callback64 *buf =
		container_of(ctx, काष्ठा getdents_callback64, ctx);
	पूर्णांक reclen = ALIGN(दुरत्व(काष्ठा linux_dirent64, d_name) + namlen + 1,
		माप(u64));
	पूर्णांक prev_reclen;

	buf->error = verअगरy_dirent_name(name, namlen);
	अगर (unlikely(buf->error))
		वापस buf->error;
	buf->error = -EINVAL;	/* only used अगर we fail.. */
	अगर (reclen > buf->count)
		वापस -EINVAL;
	prev_reclen = buf->prev_reclen;
	अगर (prev_reclen && संकेत_pending(current))
		वापस -EINTR;
	dirent = buf->current_dir;
	prev = (व्योम __user *)dirent - prev_reclen;
	अगर (!user_ग_लिखो_access_begin(prev, reclen + prev_reclen))
		जाओ efault;

	/* This might be 'dirent->d_off', but अगर so it will get overwritten */
	unsafe_put_user(offset, &prev->d_off, efault_end);
	unsafe_put_user(ino, &dirent->d_ino, efault_end);
	unsafe_put_user(reclen, &dirent->d_reclen, efault_end);
	unsafe_put_user(d_type, &dirent->d_type, efault_end);
	unsafe_copy_dirent_name(dirent->d_name, name, namlen, efault_end);
	user_ग_लिखो_access_end();

	buf->prev_reclen = reclen;
	buf->current_dir = (व्योम __user *)dirent + reclen;
	buf->count -= reclen;
	वापस 0;

efault_end:
	user_ग_लिखो_access_end();
efault:
	buf->error = -EFAULT;
	वापस -EFAULT;
पूर्ण

SYSCALL_DEFINE3(getdents64, अचिन्हित पूर्णांक, fd,
		काष्ठा linux_dirent64 __user *, dirent, अचिन्हित पूर्णांक, count)
अणु
	काष्ठा fd f;
	काष्ठा getdents_callback64 buf = अणु
		.ctx.actor = filldir64,
		.count = count,
		.current_dir = dirent
	पूर्ण;
	पूर्णांक error;

	f = fdget_pos(fd);
	अगर (!f.file)
		वापस -EBADF;

	error = iterate_dir(f.file, &buf.ctx);
	अगर (error >= 0)
		error = buf.error;
	अगर (buf.prev_reclen) अणु
		काष्ठा linux_dirent64 __user * lastdirent;
		typeof(lastdirent->d_off) d_off = buf.ctx.pos;

		lastdirent = (व्योम __user *) buf.current_dir - buf.prev_reclen;
		अगर (put_user(d_off, &lastdirent->d_off))
			error = -EFAULT;
		अन्यथा
			error = count - buf.count;
	पूर्ण
	fdput_pos(f);
	वापस error;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_old_linux_dirent अणु
	compat_uदीर्घ_t	d_ino;
	compat_uदीर्घ_t	d_offset;
	अचिन्हित लघु	d_namlen;
	अक्षर		d_name[1];
पूर्ण;

काष्ठा compat_सूची_पढ़ो_callback अणु
	काष्ठा dir_context ctx;
	काष्ठा compat_old_linux_dirent __user *dirent;
	पूर्णांक result;
पूर्ण;

अटल पूर्णांक compat_fillonedir(काष्ठा dir_context *ctx, स्थिर अक्षर *name,
			     पूर्णांक namlen, loff_t offset, u64 ino,
			     अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा compat_सूची_पढ़ो_callback *buf =
		container_of(ctx, काष्ठा compat_सूची_पढ़ो_callback, ctx);
	काष्ठा compat_old_linux_dirent __user *dirent;
	compat_uदीर्घ_t d_ino;

	अगर (buf->result)
		वापस -EINVAL;
	buf->result = verअगरy_dirent_name(name, namlen);
	अगर (buf->result < 0)
		वापस buf->result;
	d_ino = ino;
	अगर (माप(d_ino) < माप(ino) && d_ino != ino) अणु
		buf->result = -EOVERFLOW;
		वापस -EOVERFLOW;
	पूर्ण
	buf->result++;
	dirent = buf->dirent;
	अगर (!user_ग_लिखो_access_begin(dirent,
			(अचिन्हित दीर्घ)(dirent->d_name + namlen + 1) -
				(अचिन्हित दीर्घ)dirent))
		जाओ efault;
	unsafe_put_user(d_ino, &dirent->d_ino, efault_end);
	unsafe_put_user(offset, &dirent->d_offset, efault_end);
	unsafe_put_user(namlen, &dirent->d_namlen, efault_end);
	unsafe_copy_dirent_name(dirent->d_name, name, namlen, efault_end);
	user_ग_लिखो_access_end();
	वापस 0;
efault_end:
	user_ग_लिखो_access_end();
efault:
	buf->result = -EFAULT;
	वापस -EFAULT;
पूर्ण

COMPAT_SYSCALL_DEFINE3(old_सूची_पढ़ो, अचिन्हित पूर्णांक, fd,
		काष्ठा compat_old_linux_dirent __user *, dirent, अचिन्हित पूर्णांक, count)
अणु
	पूर्णांक error;
	काष्ठा fd f = fdget_pos(fd);
	काष्ठा compat_सूची_पढ़ो_callback buf = अणु
		.ctx.actor = compat_fillonedir,
		.dirent = dirent
	पूर्ण;

	अगर (!f.file)
		वापस -EBADF;

	error = iterate_dir(f.file, &buf.ctx);
	अगर (buf.result)
		error = buf.result;

	fdput_pos(f);
	वापस error;
पूर्ण

काष्ठा compat_linux_dirent अणु
	compat_uदीर्घ_t	d_ino;
	compat_uदीर्घ_t	d_off;
	अचिन्हित लघु	d_reclen;
	अक्षर		d_name[1];
पूर्ण;

काष्ठा compat_getdents_callback अणु
	काष्ठा dir_context ctx;
	काष्ठा compat_linux_dirent __user *current_dir;
	पूर्णांक prev_reclen;
	पूर्णांक count;
	पूर्णांक error;
पूर्ण;

अटल पूर्णांक compat_filldir(काष्ठा dir_context *ctx, स्थिर अक्षर *name, पूर्णांक namlen,
		loff_t offset, u64 ino, अचिन्हित पूर्णांक d_type)
अणु
	काष्ठा compat_linux_dirent __user *dirent, *prev;
	काष्ठा compat_getdents_callback *buf =
		container_of(ctx, काष्ठा compat_getdents_callback, ctx);
	compat_uदीर्घ_t d_ino;
	पूर्णांक reclen = ALIGN(दुरत्व(काष्ठा compat_linux_dirent, d_name) +
		namlen + 2, माप(compat_दीर्घ_t));
	पूर्णांक prev_reclen;

	buf->error = verअगरy_dirent_name(name, namlen);
	अगर (unlikely(buf->error))
		वापस buf->error;
	buf->error = -EINVAL;	/* only used अगर we fail.. */
	अगर (reclen > buf->count)
		वापस -EINVAL;
	d_ino = ino;
	अगर (माप(d_ino) < माप(ino) && d_ino != ino) अणु
		buf->error = -EOVERFLOW;
		वापस -EOVERFLOW;
	पूर्ण
	prev_reclen = buf->prev_reclen;
	अगर (prev_reclen && संकेत_pending(current))
		वापस -EINTR;
	dirent = buf->current_dir;
	prev = (व्योम __user *) dirent - prev_reclen;
	अगर (!user_ग_लिखो_access_begin(prev, reclen + prev_reclen))
		जाओ efault;

	unsafe_put_user(offset, &prev->d_off, efault_end);
	unsafe_put_user(d_ino, &dirent->d_ino, efault_end);
	unsafe_put_user(reclen, &dirent->d_reclen, efault_end);
	unsafe_put_user(d_type, (अक्षर __user *) dirent + reclen - 1, efault_end);
	unsafe_copy_dirent_name(dirent->d_name, name, namlen, efault_end);
	user_ग_लिखो_access_end();

	buf->prev_reclen = reclen;
	buf->current_dir = (व्योम __user *)dirent + reclen;
	buf->count -= reclen;
	वापस 0;
efault_end:
	user_ग_लिखो_access_end();
efault:
	buf->error = -EFAULT;
	वापस -EFAULT;
पूर्ण

COMPAT_SYSCALL_DEFINE3(getdents, अचिन्हित पूर्णांक, fd,
		काष्ठा compat_linux_dirent __user *, dirent, अचिन्हित पूर्णांक, count)
अणु
	काष्ठा fd f;
	काष्ठा compat_getdents_callback buf = अणु
		.ctx.actor = compat_filldir,
		.current_dir = dirent,
		.count = count
	पूर्ण;
	पूर्णांक error;

	f = fdget_pos(fd);
	अगर (!f.file)
		वापस -EBADF;

	error = iterate_dir(f.file, &buf.ctx);
	अगर (error >= 0)
		error = buf.error;
	अगर (buf.prev_reclen) अणु
		काष्ठा compat_linux_dirent __user * lastdirent;
		lastdirent = (व्योम __user *)buf.current_dir - buf.prev_reclen;

		अगर (put_user(buf.ctx.pos, &lastdirent->d_off))
			error = -EFAULT;
		अन्यथा
			error = count - buf.count;
	पूर्ण
	fdput_pos(f);
	वापस error;
पूर्ण
#पूर्ण_अगर
