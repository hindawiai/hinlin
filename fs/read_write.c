<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  linux/fs/पढ़ो_ग_लिखो.c
 *
 *  Copyright (C) 1991, 1992  Linus Torvalds
 */

#समावेश <linux/slab.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/sched/xacct.h>
#समावेश <linux/fcntl.h>
#समावेश <linux/file.h>
#समावेश <linux/uपन.स>
#समावेश <linux/fsnotअगरy.h>
#समावेश <linux/security.h>
#समावेश <linux/export.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/splice.h>
#समावेश <linux/compat.h>
#समावेश <linux/mount.h>
#समावेश <linux/fs.h>
#समावेश "internal.h"

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unistd.h>

स्थिर काष्ठा file_operations generic_ro_fops = अणु
	.llseek		= generic_file_llseek,
	.पढ़ो_iter	= generic_file_पढ़ो_iter,
	.mmap		= generic_file_पढ़ोonly_mmap,
	.splice_पढ़ो	= generic_file_splice_पढ़ो,
पूर्ण;

EXPORT_SYMBOL(generic_ro_fops);

अटल अंतरभूत bool अचिन्हित_offsets(काष्ठा file *file)
अणु
	वापस file->f_mode & FMODE_UNSIGNED_OFFSET;
पूर्ण

/**
 * vfs_setpos - update the file offset क्रम lseek
 * @file:	file काष्ठाure in question
 * @offset:	file offset to seek to
 * @maxsize:	maximum file size
 *
 * This is a low-level fileप्रणाली helper क्रम updating the file offset to
 * the value specअगरied by @offset अगर the given offset is valid and it is
 * not equal to the current file offset.
 *
 * Return the specअगरied offset on success and -EINVAL on invalid offset.
 */
loff_t vfs_setpos(काष्ठा file *file, loff_t offset, loff_t maxsize)
अणु
	अगर (offset < 0 && !अचिन्हित_offsets(file))
		वापस -EINVAL;
	अगर (offset > maxsize)
		वापस -EINVAL;

	अगर (offset != file->f_pos) अणु
		file->f_pos = offset;
		file->f_version = 0;
	पूर्ण
	वापस offset;
पूर्ण
EXPORT_SYMBOL(vfs_setpos);

/**
 * generic_file_llseek_size - generic llseek implementation क्रम regular files
 * @file:	file काष्ठाure to seek on
 * @offset:	file offset to seek to
 * @whence:	type of seek
 * @size:	max size of this file in file प्रणाली
 * @eof:	offset used क्रम अंत_से position
 *
 * This is a variant of generic_file_llseek that allows passing in a custom
 * maximum file size and a custom खातापूर्ण position, क्रम e.g. hashed directories
 *
 * Synchronization:
 * शुरू_से and अंत_से are unsynchronized (but atomic on 64bit platक्रमms)
 * प्रस्तुत_से is synchronized against other प्रस्तुत_सेs, but not पढ़ो/ग_लिखोs.
 * पढ़ो/ग_लिखोs behave like शुरू_से against seeks.
 */
loff_t
generic_file_llseek_size(काष्ठा file *file, loff_t offset, पूर्णांक whence,
		loff_t maxsize, loff_t eof)
अणु
	चयन (whence) अणु
	हाल अंत_से:
		offset += eof;
		अवरोध;
	हाल प्रस्तुत_से:
		/*
		 * Here we special-हाल the lseek(fd, 0, प्रस्तुत_से)
		 * position-querying operation.  Aव्योम rewriting the "same"
		 * f_pos value back to the file because a concurrent पढ़ो(),
		 * ग_लिखो() or lseek() might have altered it
		 */
		अगर (offset == 0)
			वापस file->f_pos;
		/*
		 * f_lock protects against पढ़ो/modअगरy/ग_लिखो race with other
		 * प्रस्तुत_सेs. Note that parallel ग_लिखोs and पढ़ोs behave
		 * like शुरू_से.
		 */
		spin_lock(&file->f_lock);
		offset = vfs_setpos(file, file->f_pos + offset, maxsize);
		spin_unlock(&file->f_lock);
		वापस offset;
	हाल SEEK_DATA:
		/*
		 * In the generic हाल the entire file is data, so as दीर्घ as
		 * offset isn't at the end of the file then the offset is data.
		 */
		अगर ((अचिन्हित दीर्घ दीर्घ)offset >= eof)
			वापस -ENXIO;
		अवरोध;
	हाल SEEK_HOLE:
		/*
		 * There is a भव hole at the end of the file, so as दीर्घ as
		 * offset isn't i_size or larger, वापस i_size.
		 */
		अगर ((अचिन्हित दीर्घ दीर्घ)offset >= eof)
			वापस -ENXIO;
		offset = eof;
		अवरोध;
	पूर्ण

	वापस vfs_setpos(file, offset, maxsize);
पूर्ण
EXPORT_SYMBOL(generic_file_llseek_size);

/**
 * generic_file_llseek - generic llseek implementation क्रम regular files
 * @file:	file काष्ठाure to seek on
 * @offset:	file offset to seek to
 * @whence:	type of seek
 *
 * This is a generic implemenation of ->llseek useable क्रम all normal local
 * fileप्रणालीs.  It just updates the file offset to the value specअगरied by
 * @offset and @whence.
 */
loff_t generic_file_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा inode *inode = file->f_mapping->host;

	वापस generic_file_llseek_size(file, offset, whence,
					inode->i_sb->s_maxbytes,
					i_size_पढ़ो(inode));
पूर्ण
EXPORT_SYMBOL(generic_file_llseek);

/**
 * fixed_size_llseek - llseek implementation क्रम fixed-sized devices
 * @file:	file काष्ठाure to seek on
 * @offset:	file offset to seek to
 * @whence:	type of seek
 * @size:	size of the file
 *
 */
loff_t fixed_size_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence, loff_t size)
अणु
	चयन (whence) अणु
	हाल शुरू_से: हाल प्रस्तुत_से: हाल अंत_से:
		वापस generic_file_llseek_size(file, offset, whence,
						size, size);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(fixed_size_llseek);

/**
 * no_seek_end_llseek - llseek implementation क्रम fixed-sized devices
 * @file:	file काष्ठाure to seek on
 * @offset:	file offset to seek to
 * @whence:	type of seek
 *
 */
loff_t no_seek_end_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	चयन (whence) अणु
	हाल शुरू_से: हाल प्रस्तुत_से:
		वापस generic_file_llseek_size(file, offset, whence,
						OFFSET_MAX, 0);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(no_seek_end_llseek);

/**
 * no_seek_end_llseek_size - llseek implementation क्रम fixed-sized devices
 * @file:	file काष्ठाure to seek on
 * @offset:	file offset to seek to
 * @whence:	type of seek
 * @size:	maximal offset allowed
 *
 */
loff_t no_seek_end_llseek_size(काष्ठा file *file, loff_t offset, पूर्णांक whence, loff_t size)
अणु
	चयन (whence) अणु
	हाल शुरू_से: हाल प्रस्तुत_से:
		वापस generic_file_llseek_size(file, offset, whence,
						size, 0);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(no_seek_end_llseek_size);

/**
 * noop_llseek - No Operation Perक्रमmed llseek implementation
 * @file:	file काष्ठाure to seek on
 * @offset:	file offset to seek to
 * @whence:	type of seek
 *
 * This is an implementation of ->llseek useable क्रम the rare special हाल when
 * userspace expects the seek to succeed but the (device) file is actually not
 * able to perक्रमm the seek. In this हाल you use noop_llseek() instead of
 * falling back to the शेष implementation of ->llseek.
 */
loff_t noop_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	वापस file->f_pos;
पूर्ण
EXPORT_SYMBOL(noop_llseek);

loff_t no_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	वापस -ESPIPE;
पूर्ण
EXPORT_SYMBOL(no_llseek);

loff_t शेष_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा inode *inode = file_inode(file);
	loff_t retval;

	inode_lock(inode);
	चयन (whence) अणु
		हाल अंत_से:
			offset += i_size_पढ़ो(inode);
			अवरोध;
		हाल प्रस्तुत_से:
			अगर (offset == 0) अणु
				retval = file->f_pos;
				जाओ out;
			पूर्ण
			offset += file->f_pos;
			अवरोध;
		हाल SEEK_DATA:
			/*
			 * In the generic हाल the entire file is data, so as
			 * दीर्घ as offset isn't at the end of the file then the
			 * offset is data.
			 */
			अगर (offset >= inode->i_size) अणु
				retval = -ENXIO;
				जाओ out;
			पूर्ण
			अवरोध;
		हाल SEEK_HOLE:
			/*
			 * There is a भव hole at the end of the file, so
			 * as दीर्घ as offset isn't i_size or larger, वापस
			 * i_size.
			 */
			अगर (offset >= inode->i_size) अणु
				retval = -ENXIO;
				जाओ out;
			पूर्ण
			offset = inode->i_size;
			अवरोध;
	पूर्ण
	retval = -EINVAL;
	अगर (offset >= 0 || अचिन्हित_offsets(file)) अणु
		अगर (offset != file->f_pos) अणु
			file->f_pos = offset;
			file->f_version = 0;
		पूर्ण
		retval = offset;
	पूर्ण
out:
	inode_unlock(inode);
	वापस retval;
पूर्ण
EXPORT_SYMBOL(शेष_llseek);

loff_t vfs_llseek(काष्ठा file *file, loff_t offset, पूर्णांक whence)
अणु
	loff_t (*fn)(काष्ठा file *, loff_t, पूर्णांक);

	fn = no_llseek;
	अगर (file->f_mode & FMODE_LSEEK) अणु
		अगर (file->f_op->llseek)
			fn = file->f_op->llseek;
	पूर्ण
	वापस fn(file, offset, whence);
पूर्ण
EXPORT_SYMBOL(vfs_llseek);

अटल off_t ksys_lseek(अचिन्हित पूर्णांक fd, off_t offset, अचिन्हित पूर्णांक whence)
अणु
	off_t retval;
	काष्ठा fd f = fdget_pos(fd);
	अगर (!f.file)
		वापस -EBADF;

	retval = -EINVAL;
	अगर (whence <= SEEK_MAX) अणु
		loff_t res = vfs_llseek(f.file, offset, whence);
		retval = res;
		अगर (res != (loff_t)retval)
			retval = -EOVERFLOW;	/* LFS: should only happen on 32 bit platक्रमms */
	पूर्ण
	fdput_pos(f);
	वापस retval;
पूर्ण

SYSCALL_DEFINE3(lseek, अचिन्हित पूर्णांक, fd, off_t, offset, अचिन्हित पूर्णांक, whence)
अणु
	वापस ksys_lseek(fd, offset, whence);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE3(lseek, अचिन्हित पूर्णांक, fd, compat_off_t, offset, अचिन्हित पूर्णांक, whence)
अणु
	वापस ksys_lseek(fd, offset, whence);
पूर्ण
#पूर्ण_अगर

#अगर !defined(CONFIG_64BIT) || defined(CONFIG_COMPAT) || \
	defined(__ARCH_WANT_SYS_LLSEEK)
SYSCALL_DEFINE5(llseek, अचिन्हित पूर्णांक, fd, अचिन्हित दीर्घ, offset_high,
		अचिन्हित दीर्घ, offset_low, loff_t __user *, result,
		अचिन्हित पूर्णांक, whence)
अणु
	पूर्णांक retval;
	काष्ठा fd f = fdget_pos(fd);
	loff_t offset;

	अगर (!f.file)
		वापस -EBADF;

	retval = -EINVAL;
	अगर (whence > SEEK_MAX)
		जाओ out_putf;

	offset = vfs_llseek(f.file, ((loff_t) offset_high << 32) | offset_low,
			whence);

	retval = (पूर्णांक)offset;
	अगर (offset >= 0) अणु
		retval = -EFAULT;
		अगर (!copy_to_user(result, &offset, माप(offset)))
			retval = 0;
	पूर्ण
out_putf:
	fdput_pos(f);
	वापस retval;
पूर्ण
#पूर्ण_अगर

पूर्णांक rw_verअगरy_area(पूर्णांक पढ़ो_ग_लिखो, काष्ठा file *file, स्थिर loff_t *ppos, माप_प्रकार count)
अणु
	काष्ठा inode *inode;
	पूर्णांक retval = -EINVAL;

	inode = file_inode(file);
	अगर (unlikely((sमाप_प्रकार) count < 0))
		वापस retval;

	/*
	 * ranged mandatory locking करोes not apply to streams - it makes sense
	 * only क्रम files where position has a meaning.
	 */
	अगर (ppos) अणु
		loff_t pos = *ppos;

		अगर (unlikely(pos < 0)) अणु
			अगर (!अचिन्हित_offsets(file))
				वापस retval;
			अगर (count >= -pos) /* both values are in 0..Lदीर्घ_उच्च */
				वापस -EOVERFLOW;
		पूर्ण अन्यथा अगर (unlikely((loff_t) (pos + count) < 0)) अणु
			अगर (!अचिन्हित_offsets(file))
				वापस retval;
		पूर्ण

		अगर (unlikely(inode->i_flctx && mandatory_lock(inode))) अणु
			retval = locks_mandatory_area(inode, file, pos, pos + count - 1,
					पढ़ो_ग_लिखो == READ ? F_RDLCK : F_WRLCK);
			अगर (retval < 0)
				वापस retval;
		पूर्ण
	पूर्ण

	वापस security_file_permission(file,
				पढ़ो_ग_लिखो == READ ? MAY_READ : MAY_WRITE);
पूर्ण

अटल sमाप_प्रकार new_sync_पढ़ो(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा iovec iov = अणु .iov_base = buf, .iov_len = len पूर्ण;
	काष्ठा kiocb kiocb;
	काष्ठा iov_iter iter;
	sमाप_प्रकार ret;

	init_sync_kiocb(&kiocb, filp);
	kiocb.ki_pos = (ppos ? *ppos : 0);
	iov_iter_init(&iter, READ, &iov, 1, len);

	ret = call_पढ़ो_iter(filp, &kiocb, &iter);
	BUG_ON(ret == -EIOCBQUEUED);
	अगर (ppos)
		*ppos = kiocb.ki_pos;
	वापस ret;
पूर्ण

अटल पूर्णांक warn_unsupported(काष्ठा file *file, स्थिर अक्षर *op)
अणु
	pr_warn_ratelimited(
		"kernel %s not supported for file %pD4 (pid: %d comm: %.20s)\n",
		op, file, current->pid, current->comm);
	वापस -EINVAL;
पूर्ण

sमाप_प्रकार __kernel_पढ़ो(काष्ठा file *file, व्योम *buf, माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा kvec iov = अणु
		.iov_base	= buf,
		.iov_len	= min_t(माप_प्रकार, count, MAX_RW_COUNT),
	पूर्ण;
	काष्ठा kiocb kiocb;
	काष्ठा iov_iter iter;
	sमाप_प्रकार ret;

	अगर (WARN_ON_ONCE(!(file->f_mode & FMODE_READ)))
		वापस -EINVAL;
	अगर (!(file->f_mode & FMODE_CAN_READ))
		वापस -EINVAL;
	/*
	 * Also fail अगर ->पढ़ो_iter and ->पढ़ो are both wired up as that
	 * implies very convoluted semantics.
	 */
	अगर (unlikely(!file->f_op->पढ़ो_iter || file->f_op->पढ़ो))
		वापस warn_unsupported(file, "read");

	init_sync_kiocb(&kiocb, file);
	kiocb.ki_pos = pos ? *pos : 0;
	iov_iter_kvec(&iter, READ, &iov, 1, iov.iov_len);
	ret = file->f_op->पढ़ो_iter(&kiocb, &iter);
	अगर (ret > 0) अणु
		अगर (pos)
			*pos = kiocb.ki_pos;
		fsnotअगरy_access(file);
		add_rअक्षर(current, ret);
	पूर्ण
	inc_syscr(current);
	वापस ret;
पूर्ण

sमाप_प्रकार kernel_पढ़ो(काष्ठा file *file, व्योम *buf, माप_प्रकार count, loff_t *pos)
अणु
	sमाप_प्रकार ret;

	ret = rw_verअगरy_area(READ, file, pos, count);
	अगर (ret)
		वापस ret;
	वापस __kernel_पढ़ो(file, buf, count, pos);
पूर्ण
EXPORT_SYMBOL(kernel_पढ़ो);

sमाप_प्रकार vfs_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार count, loff_t *pos)
अणु
	sमाप_प्रकार ret;

	अगर (!(file->f_mode & FMODE_READ))
		वापस -EBADF;
	अगर (!(file->f_mode & FMODE_CAN_READ))
		वापस -EINVAL;
	अगर (unlikely(!access_ok(buf, count)))
		वापस -EFAULT;

	ret = rw_verअगरy_area(READ, file, pos, count);
	अगर (ret)
		वापस ret;
	अगर (count > MAX_RW_COUNT)
		count =  MAX_RW_COUNT;

	अगर (file->f_op->पढ़ो)
		ret = file->f_op->पढ़ो(file, buf, count, pos);
	अन्यथा अगर (file->f_op->पढ़ो_iter)
		ret = new_sync_पढ़ो(file, buf, count, pos);
	अन्यथा
		ret = -EINVAL;
	अगर (ret > 0) अणु
		fsnotअगरy_access(file);
		add_rअक्षर(current, ret);
	पूर्ण
	inc_syscr(current);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार new_sync_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buf, माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा iovec iov = अणु .iov_base = (व्योम __user *)buf, .iov_len = len पूर्ण;
	काष्ठा kiocb kiocb;
	काष्ठा iov_iter iter;
	sमाप_प्रकार ret;

	init_sync_kiocb(&kiocb, filp);
	kiocb.ki_pos = (ppos ? *ppos : 0);
	iov_iter_init(&iter, WRITE, &iov, 1, len);

	ret = call_ग_लिखो_iter(filp, &kiocb, &iter);
	BUG_ON(ret == -EIOCBQUEUED);
	अगर (ret > 0 && ppos)
		*ppos = kiocb.ki_pos;
	वापस ret;
पूर्ण

/* caller is responsible क्रम file_start_ग_लिखो/file_end_ग_लिखो */
sमाप_प्रकार __kernel_ग_लिखो(काष्ठा file *file, स्थिर व्योम *buf, माप_प्रकार count, loff_t *pos)
अणु
	काष्ठा kvec iov = अणु
		.iov_base	= (व्योम *)buf,
		.iov_len	= min_t(माप_प्रकार, count, MAX_RW_COUNT),
	पूर्ण;
	काष्ठा kiocb kiocb;
	काष्ठा iov_iter iter;
	sमाप_प्रकार ret;

	अगर (WARN_ON_ONCE(!(file->f_mode & FMODE_WRITE)))
		वापस -EBADF;
	अगर (!(file->f_mode & FMODE_CAN_WRITE))
		वापस -EINVAL;
	/*
	 * Also fail अगर ->ग_लिखो_iter and ->ग_लिखो are both wired up as that
	 * implies very convoluted semantics.
	 */
	अगर (unlikely(!file->f_op->ग_लिखो_iter || file->f_op->ग_लिखो))
		वापस warn_unsupported(file, "write");

	init_sync_kiocb(&kiocb, file);
	kiocb.ki_pos = pos ? *pos : 0;
	iov_iter_kvec(&iter, WRITE, &iov, 1, iov.iov_len);
	ret = file->f_op->ग_लिखो_iter(&kiocb, &iter);
	अगर (ret > 0) अणु
		अगर (pos)
			*pos = kiocb.ki_pos;
		fsnotअगरy_modअगरy(file);
		add_wअक्षर(current, ret);
	पूर्ण
	inc_syscw(current);
	वापस ret;
पूर्ण
/*
 * This "EXPORT_SYMBOL_GPL()" is more of a "EXPORT_SYMBOL_DONTUSE()",
 * but स्वतःfs is one of the few पूर्णांकernal kernel users that actually
 * wants this _and_ can be built as a module. So we need to export
 * this symbol क्रम स्वतःfs, even though it really isn't appropriate
 * क्रम any other kernel modules.
 */
EXPORT_SYMBOL_GPL(__kernel_ग_लिखो);

sमाप_प्रकार kernel_ग_लिखो(काष्ठा file *file, स्थिर व्योम *buf, माप_प्रकार count,
			    loff_t *pos)
अणु
	sमाप_प्रकार ret;

	ret = rw_verअगरy_area(WRITE, file, pos, count);
	अगर (ret)
		वापस ret;

	file_start_ग_लिखो(file);
	ret =  __kernel_ग_लिखो(file, buf, count, pos);
	file_end_ग_लिखो(file);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(kernel_ग_लिखो);

sमाप_प्रकार vfs_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf, माप_प्रकार count, loff_t *pos)
अणु
	sमाप_प्रकार ret;

	अगर (!(file->f_mode & FMODE_WRITE))
		वापस -EBADF;
	अगर (!(file->f_mode & FMODE_CAN_WRITE))
		वापस -EINVAL;
	अगर (unlikely(!access_ok(buf, count)))
		वापस -EFAULT;

	ret = rw_verअगरy_area(WRITE, file, pos, count);
	अगर (ret)
		वापस ret;
	अगर (count > MAX_RW_COUNT)
		count =  MAX_RW_COUNT;
	file_start_ग_लिखो(file);
	अगर (file->f_op->ग_लिखो)
		ret = file->f_op->ग_लिखो(file, buf, count, pos);
	अन्यथा अगर (file->f_op->ग_लिखो_iter)
		ret = new_sync_ग_लिखो(file, buf, count, pos);
	अन्यथा
		ret = -EINVAL;
	अगर (ret > 0) अणु
		fsnotअगरy_modअगरy(file);
		add_wअक्षर(current, ret);
	पूर्ण
	inc_syscw(current);
	file_end_ग_लिखो(file);
	वापस ret;
पूर्ण

/* file_ppos वापसs &file->f_pos or शून्य अगर file is stream */
अटल अंतरभूत loff_t *file_ppos(काष्ठा file *file)
अणु
	वापस file->f_mode & FMODE_STREAM ? शून्य : &file->f_pos;
पूर्ण

sमाप_प्रकार ksys_पढ़ो(अचिन्हित पूर्णांक fd, अक्षर __user *buf, माप_प्रकार count)
अणु
	काष्ठा fd f = fdget_pos(fd);
	sमाप_प्रकार ret = -EBADF;

	अगर (f.file) अणु
		loff_t pos, *ppos = file_ppos(f.file);
		अगर (ppos) अणु
			pos = *ppos;
			ppos = &pos;
		पूर्ण
		ret = vfs_पढ़ो(f.file, buf, count, ppos);
		अगर (ret >= 0 && ppos)
			f.file->f_pos = pos;
		fdput_pos(f);
	पूर्ण
	वापस ret;
पूर्ण

SYSCALL_DEFINE3(पढ़ो, अचिन्हित पूर्णांक, fd, अक्षर __user *, buf, माप_प्रकार, count)
अणु
	वापस ksys_पढ़ो(fd, buf, count);
पूर्ण

sमाप_प्रकार ksys_ग_लिखो(अचिन्हित पूर्णांक fd, स्थिर अक्षर __user *buf, माप_प्रकार count)
अणु
	काष्ठा fd f = fdget_pos(fd);
	sमाप_प्रकार ret = -EBADF;

	अगर (f.file) अणु
		loff_t pos, *ppos = file_ppos(f.file);
		अगर (ppos) अणु
			pos = *ppos;
			ppos = &pos;
		पूर्ण
		ret = vfs_ग_लिखो(f.file, buf, count, ppos);
		अगर (ret >= 0 && ppos)
			f.file->f_pos = pos;
		fdput_pos(f);
	पूर्ण

	वापस ret;
पूर्ण

SYSCALL_DEFINE3(ग_लिखो, अचिन्हित पूर्णांक, fd, स्थिर अक्षर __user *, buf,
		माप_प्रकार, count)
अणु
	वापस ksys_ग_लिखो(fd, buf, count);
पूर्ण

sमाप_प्रकार ksys_pपढ़ो64(अचिन्हित पूर्णांक fd, अक्षर __user *buf, माप_प्रकार count,
		     loff_t pos)
अणु
	काष्ठा fd f;
	sमाप_प्रकार ret = -EBADF;

	अगर (pos < 0)
		वापस -EINVAL;

	f = fdget(fd);
	अगर (f.file) अणु
		ret = -ESPIPE;
		अगर (f.file->f_mode & FMODE_PREAD)
			ret = vfs_पढ़ो(f.file, buf, count, &pos);
		fdput(f);
	पूर्ण

	वापस ret;
पूर्ण

SYSCALL_DEFINE4(pपढ़ो64, अचिन्हित पूर्णांक, fd, अक्षर __user *, buf,
			माप_प्रकार, count, loff_t, pos)
अणु
	वापस ksys_pपढ़ो64(fd, buf, count, pos);
पूर्ण

sमाप_प्रकार ksys_pग_लिखो64(अचिन्हित पूर्णांक fd, स्थिर अक्षर __user *buf,
		      माप_प्रकार count, loff_t pos)
अणु
	काष्ठा fd f;
	sमाप_प्रकार ret = -EBADF;

	अगर (pos < 0)
		वापस -EINVAL;

	f = fdget(fd);
	अगर (f.file) अणु
		ret = -ESPIPE;
		अगर (f.file->f_mode & FMODE_PWRITE)  
			ret = vfs_ग_लिखो(f.file, buf, count, &pos);
		fdput(f);
	पूर्ण

	वापस ret;
पूर्ण

SYSCALL_DEFINE4(pग_लिखो64, अचिन्हित पूर्णांक, fd, स्थिर अक्षर __user *, buf,
			 माप_प्रकार, count, loff_t, pos)
अणु
	वापस ksys_pग_लिखो64(fd, buf, count, pos);
पूर्ण

अटल sमाप_प्रकार करो_iter_पढ़ोv_ग_लिखोv(काष्ठा file *filp, काष्ठा iov_iter *iter,
		loff_t *ppos, पूर्णांक type, rwf_t flags)
अणु
	काष्ठा kiocb kiocb;
	sमाप_प्रकार ret;

	init_sync_kiocb(&kiocb, filp);
	ret = kiocb_set_rw_flags(&kiocb, flags);
	अगर (ret)
		वापस ret;
	kiocb.ki_pos = (ppos ? *ppos : 0);

	अगर (type == READ)
		ret = call_पढ़ो_iter(filp, &kiocb, iter);
	अन्यथा
		ret = call_ग_लिखो_iter(filp, &kiocb, iter);
	BUG_ON(ret == -EIOCBQUEUED);
	अगर (ppos)
		*ppos = kiocb.ki_pos;
	वापस ret;
पूर्ण

/* Do it by hand, with file-ops */
अटल sमाप_प्रकार करो_loop_पढ़ोv_ग_लिखोv(काष्ठा file *filp, काष्ठा iov_iter *iter,
		loff_t *ppos, पूर्णांक type, rwf_t flags)
अणु
	sमाप_प्रकार ret = 0;

	अगर (flags & ~RWF_HIPRI)
		वापस -EOPNOTSUPP;

	जबतक (iov_iter_count(iter)) अणु
		काष्ठा iovec iovec = iov_iter_iovec(iter);
		sमाप_प्रकार nr;

		अगर (type == READ) अणु
			nr = filp->f_op->पढ़ो(filp, iovec.iov_base,
					      iovec.iov_len, ppos);
		पूर्ण अन्यथा अणु
			nr = filp->f_op->ग_लिखो(filp, iovec.iov_base,
					       iovec.iov_len, ppos);
		पूर्ण

		अगर (nr < 0) अणु
			अगर (!ret)
				ret = nr;
			अवरोध;
		पूर्ण
		ret += nr;
		अगर (nr != iovec.iov_len)
			अवरोध;
		iov_iter_advance(iter, nr);
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार करो_iter_पढ़ो(काष्ठा file *file, काष्ठा iov_iter *iter,
		loff_t *pos, rwf_t flags)
अणु
	माप_प्रकार tot_len;
	sमाप_प्रकार ret = 0;

	अगर (!(file->f_mode & FMODE_READ))
		वापस -EBADF;
	अगर (!(file->f_mode & FMODE_CAN_READ))
		वापस -EINVAL;

	tot_len = iov_iter_count(iter);
	अगर (!tot_len)
		जाओ out;
	ret = rw_verअगरy_area(READ, file, pos, tot_len);
	अगर (ret < 0)
		वापस ret;

	अगर (file->f_op->पढ़ो_iter)
		ret = करो_iter_पढ़ोv_ग_लिखोv(file, iter, pos, READ, flags);
	अन्यथा
		ret = करो_loop_पढ़ोv_ग_लिखोv(file, iter, pos, READ, flags);
out:
	अगर (ret >= 0)
		fsnotअगरy_access(file);
	वापस ret;
पूर्ण

sमाप_प्रकार vfs_iocb_iter_पढ़ो(काष्ठा file *file, काष्ठा kiocb *iocb,
			   काष्ठा iov_iter *iter)
अणु
	माप_प्रकार tot_len;
	sमाप_प्रकार ret = 0;

	अगर (!file->f_op->पढ़ो_iter)
		वापस -EINVAL;
	अगर (!(file->f_mode & FMODE_READ))
		वापस -EBADF;
	अगर (!(file->f_mode & FMODE_CAN_READ))
		वापस -EINVAL;

	tot_len = iov_iter_count(iter);
	अगर (!tot_len)
		जाओ out;
	ret = rw_verअगरy_area(READ, file, &iocb->ki_pos, tot_len);
	अगर (ret < 0)
		वापस ret;

	ret = call_पढ़ो_iter(file, iocb, iter);
out:
	अगर (ret >= 0)
		fsnotअगरy_access(file);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(vfs_iocb_iter_पढ़ो);

sमाप_प्रकार vfs_iter_पढ़ो(काष्ठा file *file, काष्ठा iov_iter *iter, loff_t *ppos,
		rwf_t flags)
अणु
	अगर (!file->f_op->पढ़ो_iter)
		वापस -EINVAL;
	वापस करो_iter_पढ़ो(file, iter, ppos, flags);
पूर्ण
EXPORT_SYMBOL(vfs_iter_पढ़ो);

अटल sमाप_प्रकार करो_iter_ग_लिखो(काष्ठा file *file, काष्ठा iov_iter *iter,
		loff_t *pos, rwf_t flags)
अणु
	माप_प्रकार tot_len;
	sमाप_प्रकार ret = 0;

	अगर (!(file->f_mode & FMODE_WRITE))
		वापस -EBADF;
	अगर (!(file->f_mode & FMODE_CAN_WRITE))
		वापस -EINVAL;

	tot_len = iov_iter_count(iter);
	अगर (!tot_len)
		वापस 0;
	ret = rw_verअगरy_area(WRITE, file, pos, tot_len);
	अगर (ret < 0)
		वापस ret;

	अगर (file->f_op->ग_लिखो_iter)
		ret = करो_iter_पढ़ोv_ग_लिखोv(file, iter, pos, WRITE, flags);
	अन्यथा
		ret = करो_loop_पढ़ोv_ग_लिखोv(file, iter, pos, WRITE, flags);
	अगर (ret > 0)
		fsnotअगरy_modअगरy(file);
	वापस ret;
पूर्ण

sमाप_प्रकार vfs_iocb_iter_ग_लिखो(काष्ठा file *file, काष्ठा kiocb *iocb,
			    काष्ठा iov_iter *iter)
अणु
	माप_प्रकार tot_len;
	sमाप_प्रकार ret = 0;

	अगर (!file->f_op->ग_लिखो_iter)
		वापस -EINVAL;
	अगर (!(file->f_mode & FMODE_WRITE))
		वापस -EBADF;
	अगर (!(file->f_mode & FMODE_CAN_WRITE))
		वापस -EINVAL;

	tot_len = iov_iter_count(iter);
	अगर (!tot_len)
		वापस 0;
	ret = rw_verअगरy_area(WRITE, file, &iocb->ki_pos, tot_len);
	अगर (ret < 0)
		वापस ret;

	ret = call_ग_लिखो_iter(file, iocb, iter);
	अगर (ret > 0)
		fsnotअगरy_modअगरy(file);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(vfs_iocb_iter_ग_लिखो);

sमाप_प्रकार vfs_iter_ग_लिखो(काष्ठा file *file, काष्ठा iov_iter *iter, loff_t *ppos,
		rwf_t flags)
अणु
	अगर (!file->f_op->ग_लिखो_iter)
		वापस -EINVAL;
	वापस करो_iter_ग_लिखो(file, iter, ppos, flags);
पूर्ण
EXPORT_SYMBOL(vfs_iter_ग_लिखो);

अटल sमाप_प्रकार vfs_पढ़ोv(काष्ठा file *file, स्थिर काष्ठा iovec __user *vec,
		  अचिन्हित दीर्घ vlen, loff_t *pos, rwf_t flags)
अणु
	काष्ठा iovec iovstack[UIO_FASTIOV];
	काष्ठा iovec *iov = iovstack;
	काष्ठा iov_iter iter;
	sमाप_प्रकार ret;

	ret = import_iovec(READ, vec, vlen, ARRAY_SIZE(iovstack), &iov, &iter);
	अगर (ret >= 0) अणु
		ret = करो_iter_पढ़ो(file, &iter, pos, flags);
		kमुक्त(iov);
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार vfs_ग_लिखोv(काष्ठा file *file, स्थिर काष्ठा iovec __user *vec,
		   अचिन्हित दीर्घ vlen, loff_t *pos, rwf_t flags)
अणु
	काष्ठा iovec iovstack[UIO_FASTIOV];
	काष्ठा iovec *iov = iovstack;
	काष्ठा iov_iter iter;
	sमाप_प्रकार ret;

	ret = import_iovec(WRITE, vec, vlen, ARRAY_SIZE(iovstack), &iov, &iter);
	अगर (ret >= 0) अणु
		file_start_ग_लिखो(file);
		ret = करो_iter_ग_लिखो(file, &iter, pos, flags);
		file_end_ग_लिखो(file);
		kमुक्त(iov);
	पूर्ण
	वापस ret;
पूर्ण

अटल sमाप_प्रकार करो_पढ़ोv(अचिन्हित दीर्घ fd, स्थिर काष्ठा iovec __user *vec,
			अचिन्हित दीर्घ vlen, rwf_t flags)
अणु
	काष्ठा fd f = fdget_pos(fd);
	sमाप_प्रकार ret = -EBADF;

	अगर (f.file) अणु
		loff_t pos, *ppos = file_ppos(f.file);
		अगर (ppos) अणु
			pos = *ppos;
			ppos = &pos;
		पूर्ण
		ret = vfs_पढ़ोv(f.file, vec, vlen, ppos, flags);
		अगर (ret >= 0 && ppos)
			f.file->f_pos = pos;
		fdput_pos(f);
	पूर्ण

	अगर (ret > 0)
		add_rअक्षर(current, ret);
	inc_syscr(current);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार करो_ग_लिखोv(अचिन्हित दीर्घ fd, स्थिर काष्ठा iovec __user *vec,
			 अचिन्हित दीर्घ vlen, rwf_t flags)
अणु
	काष्ठा fd f = fdget_pos(fd);
	sमाप_प्रकार ret = -EBADF;

	अगर (f.file) अणु
		loff_t pos, *ppos = file_ppos(f.file);
		अगर (ppos) अणु
			pos = *ppos;
			ppos = &pos;
		पूर्ण
		ret = vfs_ग_लिखोv(f.file, vec, vlen, ppos, flags);
		अगर (ret >= 0 && ppos)
			f.file->f_pos = pos;
		fdput_pos(f);
	पूर्ण

	अगर (ret > 0)
		add_wअक्षर(current, ret);
	inc_syscw(current);
	वापस ret;
पूर्ण

अटल अंतरभूत loff_t pos_from_hilo(अचिन्हित दीर्घ high, अचिन्हित दीर्घ low)
अणु
#घोषणा HALF_LONG_BITS (BITS_PER_LONG / 2)
	वापस (((loff_t)high << HALF_LONG_BITS) << HALF_LONG_BITS) | low;
पूर्ण

अटल sमाप_प्रकार करो_pपढ़ोv(अचिन्हित दीर्घ fd, स्थिर काष्ठा iovec __user *vec,
			 अचिन्हित दीर्घ vlen, loff_t pos, rwf_t flags)
अणु
	काष्ठा fd f;
	sमाप_प्रकार ret = -EBADF;

	अगर (pos < 0)
		वापस -EINVAL;

	f = fdget(fd);
	अगर (f.file) अणु
		ret = -ESPIPE;
		अगर (f.file->f_mode & FMODE_PREAD)
			ret = vfs_पढ़ोv(f.file, vec, vlen, &pos, flags);
		fdput(f);
	पूर्ण

	अगर (ret > 0)
		add_rअक्षर(current, ret);
	inc_syscr(current);
	वापस ret;
पूर्ण

अटल sमाप_प्रकार करो_pग_लिखोv(अचिन्हित दीर्घ fd, स्थिर काष्ठा iovec __user *vec,
			  अचिन्हित दीर्घ vlen, loff_t pos, rwf_t flags)
अणु
	काष्ठा fd f;
	sमाप_प्रकार ret = -EBADF;

	अगर (pos < 0)
		वापस -EINVAL;

	f = fdget(fd);
	अगर (f.file) अणु
		ret = -ESPIPE;
		अगर (f.file->f_mode & FMODE_PWRITE)
			ret = vfs_ग_लिखोv(f.file, vec, vlen, &pos, flags);
		fdput(f);
	पूर्ण

	अगर (ret > 0)
		add_wअक्षर(current, ret);
	inc_syscw(current);
	वापस ret;
पूर्ण

SYSCALL_DEFINE3(पढ़ोv, अचिन्हित दीर्घ, fd, स्थिर काष्ठा iovec __user *, vec,
		अचिन्हित दीर्घ, vlen)
अणु
	वापस करो_पढ़ोv(fd, vec, vlen, 0);
पूर्ण

SYSCALL_DEFINE3(ग_लिखोv, अचिन्हित दीर्घ, fd, स्थिर काष्ठा iovec __user *, vec,
		अचिन्हित दीर्घ, vlen)
अणु
	वापस करो_ग_लिखोv(fd, vec, vlen, 0);
पूर्ण

SYSCALL_DEFINE5(pपढ़ोv, अचिन्हित दीर्घ, fd, स्थिर काष्ठा iovec __user *, vec,
		अचिन्हित दीर्घ, vlen, अचिन्हित दीर्घ, pos_l, अचिन्हित दीर्घ, pos_h)
अणु
	loff_t pos = pos_from_hilo(pos_h, pos_l);

	वापस करो_pपढ़ोv(fd, vec, vlen, pos, 0);
पूर्ण

SYSCALL_DEFINE6(pपढ़ोv2, अचिन्हित दीर्घ, fd, स्थिर काष्ठा iovec __user *, vec,
		अचिन्हित दीर्घ, vlen, अचिन्हित दीर्घ, pos_l, अचिन्हित दीर्घ, pos_h,
		rwf_t, flags)
अणु
	loff_t pos = pos_from_hilo(pos_h, pos_l);

	अगर (pos == -1)
		वापस करो_पढ़ोv(fd, vec, vlen, flags);

	वापस करो_pपढ़ोv(fd, vec, vlen, pos, flags);
पूर्ण

SYSCALL_DEFINE5(pग_लिखोv, अचिन्हित दीर्घ, fd, स्थिर काष्ठा iovec __user *, vec,
		अचिन्हित दीर्घ, vlen, अचिन्हित दीर्घ, pos_l, अचिन्हित दीर्घ, pos_h)
अणु
	loff_t pos = pos_from_hilo(pos_h, pos_l);

	वापस करो_pग_लिखोv(fd, vec, vlen, pos, 0);
पूर्ण

SYSCALL_DEFINE6(pग_लिखोv2, अचिन्हित दीर्घ, fd, स्थिर काष्ठा iovec __user *, vec,
		अचिन्हित दीर्घ, vlen, अचिन्हित दीर्घ, pos_l, अचिन्हित दीर्घ, pos_h,
		rwf_t, flags)
अणु
	loff_t pos = pos_from_hilo(pos_h, pos_l);

	अगर (pos == -1)
		वापस करो_ग_लिखोv(fd, vec, vlen, flags);

	वापस करो_pग_लिखोv(fd, vec, vlen, pos, flags);
पूर्ण

/*
 * Various compat syscalls.  Note that they all pretend to take a native
 * iovec - import_iovec will properly treat those as compat_iovecs based on
 * in_compat_syscall().
 */
#अगर_घोषित CONFIG_COMPAT
#अगर_घोषित __ARCH_WANT_COMPAT_SYS_PREADV64
COMPAT_SYSCALL_DEFINE4(pपढ़ोv64, अचिन्हित दीर्घ, fd,
		स्थिर काष्ठा iovec __user *, vec,
		अचिन्हित दीर्घ, vlen, loff_t, pos)
अणु
	वापस करो_pपढ़ोv(fd, vec, vlen, pos, 0);
पूर्ण
#पूर्ण_अगर

COMPAT_SYSCALL_DEFINE5(pपढ़ोv, compat_uदीर्घ_t, fd,
		स्थिर काष्ठा iovec __user *, vec,
		compat_uदीर्घ_t, vlen, u32, pos_low, u32, pos_high)
अणु
	loff_t pos = ((loff_t)pos_high << 32) | pos_low;

	वापस करो_pपढ़ोv(fd, vec, vlen, pos, 0);
पूर्ण

#अगर_घोषित __ARCH_WANT_COMPAT_SYS_PREADV64V2
COMPAT_SYSCALL_DEFINE5(pपढ़ोv64v2, अचिन्हित दीर्घ, fd,
		स्थिर काष्ठा iovec __user *, vec,
		अचिन्हित दीर्घ, vlen, loff_t, pos, rwf_t, flags)
अणु
	अगर (pos == -1)
		वापस करो_पढ़ोv(fd, vec, vlen, flags);
	वापस करो_pपढ़ोv(fd, vec, vlen, pos, flags);
पूर्ण
#पूर्ण_अगर

COMPAT_SYSCALL_DEFINE6(pपढ़ोv2, compat_uदीर्घ_t, fd,
		स्थिर काष्ठा iovec __user *, vec,
		compat_uदीर्घ_t, vlen, u32, pos_low, u32, pos_high,
		rwf_t, flags)
अणु
	loff_t pos = ((loff_t)pos_high << 32) | pos_low;

	अगर (pos == -1)
		वापस करो_पढ़ोv(fd, vec, vlen, flags);
	वापस करो_pपढ़ोv(fd, vec, vlen, pos, flags);
पूर्ण

#अगर_घोषित __ARCH_WANT_COMPAT_SYS_PWRITEV64
COMPAT_SYSCALL_DEFINE4(pग_लिखोv64, अचिन्हित दीर्घ, fd,
		स्थिर काष्ठा iovec __user *, vec,
		अचिन्हित दीर्घ, vlen, loff_t, pos)
अणु
	वापस करो_pग_लिखोv(fd, vec, vlen, pos, 0);
पूर्ण
#पूर्ण_अगर

COMPAT_SYSCALL_DEFINE5(pग_लिखोv, compat_uदीर्घ_t, fd,
		स्थिर काष्ठा iovec __user *,vec,
		compat_uदीर्घ_t, vlen, u32, pos_low, u32, pos_high)
अणु
	loff_t pos = ((loff_t)pos_high << 32) | pos_low;

	वापस करो_pग_लिखोv(fd, vec, vlen, pos, 0);
पूर्ण

#अगर_घोषित __ARCH_WANT_COMPAT_SYS_PWRITEV64V2
COMPAT_SYSCALL_DEFINE5(pग_लिखोv64v2, अचिन्हित दीर्घ, fd,
		स्थिर काष्ठा iovec __user *, vec,
		अचिन्हित दीर्घ, vlen, loff_t, pos, rwf_t, flags)
अणु
	अगर (pos == -1)
		वापस करो_ग_लिखोv(fd, vec, vlen, flags);
	वापस करो_pग_लिखोv(fd, vec, vlen, pos, flags);
पूर्ण
#पूर्ण_अगर

COMPAT_SYSCALL_DEFINE6(pग_लिखोv2, compat_uदीर्घ_t, fd,
		स्थिर काष्ठा iovec __user *,vec,
		compat_uदीर्घ_t, vlen, u32, pos_low, u32, pos_high, rwf_t, flags)
अणु
	loff_t pos = ((loff_t)pos_high << 32) | pos_low;

	अगर (pos == -1)
		वापस करो_ग_लिखोv(fd, vec, vlen, flags);
	वापस करो_pग_लिखोv(fd, vec, vlen, pos, flags);
पूर्ण
#पूर्ण_अगर /* CONFIG_COMPAT */

अटल sमाप_प्रकार करो_sendfile(पूर्णांक out_fd, पूर्णांक in_fd, loff_t *ppos,
		  	   माप_प्रकार count, loff_t max)
अणु
	काष्ठा fd in, out;
	काष्ठा inode *in_inode, *out_inode;
	काष्ठा pipe_inode_info *opipe;
	loff_t pos;
	loff_t out_pos;
	sमाप_प्रकार retval;
	पूर्णांक fl;

	/*
	 * Get input file, and verअगरy that it is ok..
	 */
	retval = -EBADF;
	in = fdget(in_fd);
	अगर (!in.file)
		जाओ out;
	अगर (!(in.file->f_mode & FMODE_READ))
		जाओ fput_in;
	retval = -ESPIPE;
	अगर (!ppos) अणु
		pos = in.file->f_pos;
	पूर्ण अन्यथा अणु
		pos = *ppos;
		अगर (!(in.file->f_mode & FMODE_PREAD))
			जाओ fput_in;
	पूर्ण
	retval = rw_verअगरy_area(READ, in.file, &pos, count);
	अगर (retval < 0)
		जाओ fput_in;
	अगर (count > MAX_RW_COUNT)
		count =  MAX_RW_COUNT;

	/*
	 * Get output file, and verअगरy that it is ok..
	 */
	retval = -EBADF;
	out = fdget(out_fd);
	अगर (!out.file)
		जाओ fput_in;
	अगर (!(out.file->f_mode & FMODE_WRITE))
		जाओ fput_out;
	in_inode = file_inode(in.file);
	out_inode = file_inode(out.file);
	out_pos = out.file->f_pos;

	अगर (!max)
		max = min(in_inode->i_sb->s_maxbytes, out_inode->i_sb->s_maxbytes);

	अगर (unlikely(pos + count > max)) अणु
		retval = -EOVERFLOW;
		अगर (pos >= max)
			जाओ fput_out;
		count = max - pos;
	पूर्ण

	fl = 0;
#अगर 0
	/*
	 * We need to debate whether we can enable this or not. The
	 * man page करोcuments EAGAIN वापस क्रम the output at least,
	 * and the application is arguably buggy अगर it करोesn't expect
	 * EAGAIN on a non-blocking file descriptor.
	 */
	अगर (in.file->f_flags & O_NONBLOCK)
		fl = SPLICE_F_NONBLOCK;
#पूर्ण_अगर
	opipe = get_pipe_info(out.file, true);
	अगर (!opipe) अणु
		retval = rw_verअगरy_area(WRITE, out.file, &out_pos, count);
		अगर (retval < 0)
			जाओ fput_out;
		file_start_ग_लिखो(out.file);
		retval = करो_splice_direct(in.file, &pos, out.file, &out_pos,
					  count, fl);
		file_end_ग_लिखो(out.file);
	पूर्ण अन्यथा अणु
		retval = splice_file_to_pipe(in.file, opipe, &pos, count, fl);
	पूर्ण

	अगर (retval > 0) अणु
		add_rअक्षर(current, retval);
		add_wअक्षर(current, retval);
		fsnotअगरy_access(in.file);
		fsnotअगरy_modअगरy(out.file);
		out.file->f_pos = out_pos;
		अगर (ppos)
			*ppos = pos;
		अन्यथा
			in.file->f_pos = pos;
	पूर्ण

	inc_syscr(current);
	inc_syscw(current);
	अगर (pos > max)
		retval = -EOVERFLOW;

fput_out:
	fdput(out);
fput_in:
	fdput(in);
out:
	वापस retval;
पूर्ण

SYSCALL_DEFINE4(sendfile, पूर्णांक, out_fd, पूर्णांक, in_fd, off_t __user *, offset, माप_प्रकार, count)
अणु
	loff_t pos;
	off_t off;
	sमाप_प्रकार ret;

	अगर (offset) अणु
		अगर (unlikely(get_user(off, offset)))
			वापस -EFAULT;
		pos = off;
		ret = करो_sendfile(out_fd, in_fd, &pos, count, MAX_NON_LFS);
		अगर (unlikely(put_user(pos, offset)))
			वापस -EFAULT;
		वापस ret;
	पूर्ण

	वापस करो_sendfile(out_fd, in_fd, शून्य, count, 0);
पूर्ण

SYSCALL_DEFINE4(sendfile64, पूर्णांक, out_fd, पूर्णांक, in_fd, loff_t __user *, offset, माप_प्रकार, count)
अणु
	loff_t pos;
	sमाप_प्रकार ret;

	अगर (offset) अणु
		अगर (unlikely(copy_from_user(&pos, offset, माप(loff_t))))
			वापस -EFAULT;
		ret = करो_sendfile(out_fd, in_fd, &pos, count, 0);
		अगर (unlikely(put_user(pos, offset)))
			वापस -EFAULT;
		वापस ret;
	पूर्ण

	वापस करो_sendfile(out_fd, in_fd, शून्य, count, 0);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
COMPAT_SYSCALL_DEFINE4(sendfile, पूर्णांक, out_fd, पूर्णांक, in_fd,
		compat_off_t __user *, offset, compat_माप_प्रकार, count)
अणु
	loff_t pos;
	off_t off;
	sमाप_प्रकार ret;

	अगर (offset) अणु
		अगर (unlikely(get_user(off, offset)))
			वापस -EFAULT;
		pos = off;
		ret = करो_sendfile(out_fd, in_fd, &pos, count, MAX_NON_LFS);
		अगर (unlikely(put_user(pos, offset)))
			वापस -EFAULT;
		वापस ret;
	पूर्ण

	वापस करो_sendfile(out_fd, in_fd, शून्य, count, 0);
पूर्ण

COMPAT_SYSCALL_DEFINE4(sendfile64, पूर्णांक, out_fd, पूर्णांक, in_fd,
		compat_loff_t __user *, offset, compat_माप_प्रकार, count)
अणु
	loff_t pos;
	sमाप_प्रकार ret;

	अगर (offset) अणु
		अगर (unlikely(copy_from_user(&pos, offset, माप(loff_t))))
			वापस -EFAULT;
		ret = करो_sendfile(out_fd, in_fd, &pos, count, 0);
		अगर (unlikely(put_user(pos, offset)))
			वापस -EFAULT;
		वापस ret;
	पूर्ण

	वापस करो_sendfile(out_fd, in_fd, शून्य, count, 0);
पूर्ण
#पूर्ण_अगर

/**
 * generic_copy_file_range - copy data between two files
 * @file_in:	file काष्ठाure to पढ़ो from
 * @pos_in:	file offset to पढ़ो from
 * @file_out:	file काष्ठाure to ग_लिखो data to
 * @pos_out:	file offset to ग_लिखो data to
 * @len:	amount of data to copy
 * @flags:	copy flags
 *
 * This is a generic fileप्रणाली helper to copy data from one file to another.
 * It has no स्थिरraपूर्णांकs on the source or destination file owners - the files
 * can beदीर्घ to dअगरferent superblocks and dअगरferent fileप्रणाली types. Short
 * copies are allowed.
 *
 * This should be called from the @file_out fileप्रणाली, as per the
 * ->copy_file_range() method.
 *
 * Returns the number of bytes copied or a negative error indicating the
 * failure.
 */

sमाप_प्रकार generic_copy_file_range(काष्ठा file *file_in, loff_t pos_in,
				काष्ठा file *file_out, loff_t pos_out,
				माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	वापस करो_splice_direct(file_in, &pos_in, file_out, &pos_out,
				len > MAX_RW_COUNT ? MAX_RW_COUNT : len, 0);
पूर्ण
EXPORT_SYMBOL(generic_copy_file_range);

अटल sमाप_प्रकार करो_copy_file_range(काष्ठा file *file_in, loff_t pos_in,
				  काष्ठा file *file_out, loff_t pos_out,
				  माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	/*
	 * Although we now allow fileप्रणालीs to handle cross sb copy, passing
	 * a file of the wrong fileप्रणाली type to fileप्रणाली driver can result
	 * in an attempt to dereference the wrong type of ->निजी_data, so
	 * aव्योम करोing that until we really have a good reason.  NFS defines
	 * several dअगरferent file_प्रणाली_type काष्ठाures, but they all end up
	 * using the same ->copy_file_range() function poपूर्णांकer.
	 */
	अगर (file_out->f_op->copy_file_range &&
	    file_out->f_op->copy_file_range == file_in->f_op->copy_file_range)
		वापस file_out->f_op->copy_file_range(file_in, pos_in,
						       file_out, pos_out,
						       len, flags);

	वापस generic_copy_file_range(file_in, pos_in, file_out, pos_out, len,
				       flags);
पूर्ण

/*
 * Perक्रमms necessary checks beक्रमe करोing a file copy
 *
 * Can adjust amount of bytes to copy via @req_count argument.
 * Returns appropriate error code that caller should वापस or
 * zero in हाल the copy should be allowed.
 */
अटल पूर्णांक generic_copy_file_checks(काष्ठा file *file_in, loff_t pos_in,
				    काष्ठा file *file_out, loff_t pos_out,
				    माप_प्रकार *req_count, अचिन्हित पूर्णांक flags)
अणु
	काष्ठा inode *inode_in = file_inode(file_in);
	काष्ठा inode *inode_out = file_inode(file_out);
	uपूर्णांक64_t count = *req_count;
	loff_t size_in;
	पूर्णांक ret;

	ret = generic_file_rw_checks(file_in, file_out);
	अगर (ret)
		वापस ret;

	/* Don't touch certain kinds of inodes */
	अगर (IS_IMMUTABLE(inode_out))
		वापस -EPERM;

	अगर (IS_SWAPखाता(inode_in) || IS_SWAPखाता(inode_out))
		वापस -ETXTBSY;

	/* Ensure offsets करोn't wrap. */
	अगर (pos_in + count < pos_in || pos_out + count < pos_out)
		वापस -EOVERFLOW;

	/* Shorten the copy to खातापूर्ण */
	size_in = i_size_पढ़ो(inode_in);
	अगर (pos_in >= size_in)
		count = 0;
	अन्यथा
		count = min(count, size_in - (uपूर्णांक64_t)pos_in);

	ret = generic_ग_लिखो_check_limits(file_out, pos_out, &count);
	अगर (ret)
		वापस ret;

	/* Don't allow overlapped copying within the same file. */
	अगर (inode_in == inode_out &&
	    pos_out + count > pos_in &&
	    pos_out < pos_in + count)
		वापस -EINVAL;

	*req_count = count;
	वापस 0;
पूर्ण

/*
 * copy_file_range() dअगरfers from regular file पढ़ो and ग_लिखो in that it
 * specअगरically allows वापस partial success.  When it करोes so is up to
 * the copy_file_range method.
 */
sमाप_प्रकार vfs_copy_file_range(काष्ठा file *file_in, loff_t pos_in,
			    काष्ठा file *file_out, loff_t pos_out,
			    माप_प्रकार len, अचिन्हित पूर्णांक flags)
अणु
	sमाप_प्रकार ret;

	अगर (flags != 0)
		वापस -EINVAL;

	ret = generic_copy_file_checks(file_in, pos_in, file_out, pos_out, &len,
				       flags);
	अगर (unlikely(ret))
		वापस ret;

	ret = rw_verअगरy_area(READ, file_in, &pos_in, len);
	अगर (unlikely(ret))
		वापस ret;

	ret = rw_verअगरy_area(WRITE, file_out, &pos_out, len);
	अगर (unlikely(ret))
		वापस ret;

	अगर (len == 0)
		वापस 0;

	file_start_ग_लिखो(file_out);

	/*
	 * Try cloning first, this is supported by more file प्रणालीs, and
	 * more efficient अगर both clone and copy are supported (e.g. NFS).
	 */
	अगर (file_in->f_op->remap_file_range &&
	    file_inode(file_in)->i_sb == file_inode(file_out)->i_sb) अणु
		loff_t cloned;

		cloned = file_in->f_op->remap_file_range(file_in, pos_in,
				file_out, pos_out,
				min_t(loff_t, MAX_RW_COUNT, len),
				REMAP_खाता_CAN_SHORTEN);
		अगर (cloned > 0) अणु
			ret = cloned;
			जाओ करोne;
		पूर्ण
	पूर्ण

	ret = करो_copy_file_range(file_in, pos_in, file_out, pos_out, len,
				flags);
	WARN_ON_ONCE(ret == -EOPNOTSUPP);
करोne:
	अगर (ret > 0) अणु
		fsnotअगरy_access(file_in);
		add_rअक्षर(current, ret);
		fsnotअगरy_modअगरy(file_out);
		add_wअक्षर(current, ret);
	पूर्ण

	inc_syscr(current);
	inc_syscw(current);

	file_end_ग_लिखो(file_out);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(vfs_copy_file_range);

SYSCALL_DEFINE6(copy_file_range, पूर्णांक, fd_in, loff_t __user *, off_in,
		पूर्णांक, fd_out, loff_t __user *, off_out,
		माप_प्रकार, len, अचिन्हित पूर्णांक, flags)
अणु
	loff_t pos_in;
	loff_t pos_out;
	काष्ठा fd f_in;
	काष्ठा fd f_out;
	sमाप_प्रकार ret = -EBADF;

	f_in = fdget(fd_in);
	अगर (!f_in.file)
		जाओ out2;

	f_out = fdget(fd_out);
	अगर (!f_out.file)
		जाओ out1;

	ret = -EFAULT;
	अगर (off_in) अणु
		अगर (copy_from_user(&pos_in, off_in, माप(loff_t)))
			जाओ out;
	पूर्ण अन्यथा अणु
		pos_in = f_in.file->f_pos;
	पूर्ण

	अगर (off_out) अणु
		अगर (copy_from_user(&pos_out, off_out, माप(loff_t)))
			जाओ out;
	पूर्ण अन्यथा अणु
		pos_out = f_out.file->f_pos;
	पूर्ण

	ret = vfs_copy_file_range(f_in.file, pos_in, f_out.file, pos_out, len,
				  flags);
	अगर (ret > 0) अणु
		pos_in += ret;
		pos_out += ret;

		अगर (off_in) अणु
			अगर (copy_to_user(off_in, &pos_in, माप(loff_t)))
				ret = -EFAULT;
		पूर्ण अन्यथा अणु
			f_in.file->f_pos = pos_in;
		पूर्ण

		अगर (off_out) अणु
			अगर (copy_to_user(off_out, &pos_out, माप(loff_t)))
				ret = -EFAULT;
		पूर्ण अन्यथा अणु
			f_out.file->f_pos = pos_out;
		पूर्ण
	पूर्ण

out:
	fdput(f_out);
out1:
	fdput(f_in);
out2:
	वापस ret;
पूर्ण

/*
 * Don't operate on ranges the page cache doesn't support, and don't exceed the
 * LFS limits.  If pos is under the limit it becomes a लघु access.  If it
 * exceeds the limit we वापस -EFBIG.
 */
पूर्णांक generic_ग_लिखो_check_limits(काष्ठा file *file, loff_t pos, loff_t *count)
अणु
	काष्ठा inode *inode = file->f_mapping->host;
	loff_t max_size = inode->i_sb->s_maxbytes;
	loff_t limit = rlimit(RLIMIT_FSIZE);

	अगर (limit != RLIM_अनन्त) अणु
		अगर (pos >= limit) अणु
			send_sig(SIGXFSZ, current, 0);
			वापस -EFBIG;
		पूर्ण
		*count = min(*count, limit - pos);
	पूर्ण

	अगर (!(file->f_flags & O_LARGEखाता))
		max_size = MAX_NON_LFS;

	अगर (unlikely(pos >= max_size))
		वापस -EFBIG;

	*count = min(*count, max_size - pos);

	वापस 0;
पूर्ण

/*
 * Perक्रमms necessary checks beक्रमe करोing a ग_लिखो
 *
 * Can adjust writing position or amount of bytes to ग_लिखो.
 * Returns appropriate error code that caller should वापस or
 * zero in हाल that ग_लिखो should be allowed.
 */
sमाप_प्रकार generic_ग_लिखो_checks(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	काष्ठा file *file = iocb->ki_filp;
	काष्ठा inode *inode = file->f_mapping->host;
	loff_t count;
	पूर्णांक ret;

	अगर (IS_SWAPखाता(inode))
		वापस -ETXTBSY;

	अगर (!iov_iter_count(from))
		वापस 0;

	/* FIXME: this is क्रम backwards compatibility with 2.4 */
	अगर (iocb->ki_flags & IOCB_APPEND)
		iocb->ki_pos = i_size_पढ़ो(inode);

	अगर ((iocb->ki_flags & IOCB_NOWAIT) && !(iocb->ki_flags & IOCB_सूचीECT))
		वापस -EINVAL;

	count = iov_iter_count(from);
	ret = generic_ग_लिखो_check_limits(file, iocb->ki_pos, &count);
	अगर (ret)
		वापस ret;

	iov_iter_truncate(from, count);
	वापस iov_iter_count(from);
पूर्ण
EXPORT_SYMBOL(generic_ग_लिखो_checks);

/*
 * Perक्रमms common checks beक्रमe करोing a file copy/clone
 * from @file_in to @file_out.
 */
पूर्णांक generic_file_rw_checks(काष्ठा file *file_in, काष्ठा file *file_out)
अणु
	काष्ठा inode *inode_in = file_inode(file_in);
	काष्ठा inode *inode_out = file_inode(file_out);

	/* Don't copy dirs, pipes, sockets... */
	अगर (S_ISसूची(inode_in->i_mode) || S_ISसूची(inode_out->i_mode))
		वापस -EISसूची;
	अगर (!S_ISREG(inode_in->i_mode) || !S_ISREG(inode_out->i_mode))
		वापस -EINVAL;

	अगर (!(file_in->f_mode & FMODE_READ) ||
	    !(file_out->f_mode & FMODE_WRITE) ||
	    (file_out->f_flags & O_APPEND))
		वापस -EBADF;

	वापस 0;
पूर्ण
