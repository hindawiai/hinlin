<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/syscalls.h>
#समावेश <linux/export.h>
#समावेश <linux/fs.h>
#समावेश <linux/file.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/statfs.h>
#समावेश <linux/security.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/compat.h>
#समावेश "internal.h"

अटल पूर्णांक flags_by_mnt(पूर्णांक mnt_flags)
अणु
	पूर्णांक flags = 0;

	अगर (mnt_flags & MNT_READONLY)
		flags |= ST_RDONLY;
	अगर (mnt_flags & MNT_NOSUID)
		flags |= ST_NOSUID;
	अगर (mnt_flags & MNT_NODEV)
		flags |= ST_NODEV;
	अगर (mnt_flags & MNT_NOEXEC)
		flags |= ST_NOEXEC;
	अगर (mnt_flags & MNT_NOATIME)
		flags |= ST_NOATIME;
	अगर (mnt_flags & MNT_NOसूचीATIME)
		flags |= ST_NOसूचीATIME;
	अगर (mnt_flags & MNT_RELATIME)
		flags |= ST_RELATIME;
	अगर (mnt_flags & MNT_NOSYMFOLLOW)
		flags |= ST_NOSYMFOLLOW;
	वापस flags;
पूर्ण

अटल पूर्णांक flags_by_sb(पूर्णांक s_flags)
अणु
	पूर्णांक flags = 0;
	अगर (s_flags & SB_SYNCHRONOUS)
		flags |= ST_SYNCHRONOUS;
	अगर (s_flags & SB_MANDLOCK)
		flags |= ST_MANDLOCK;
	अगर (s_flags & SB_RDONLY)
		flags |= ST_RDONLY;
	वापस flags;
पूर्ण

अटल पूर्णांक calculate_f_flags(काष्ठा vfsmount *mnt)
अणु
	वापस ST_VALID | flags_by_mnt(mnt->mnt_flags) |
		flags_by_sb(mnt->mnt_sb->s_flags);
पूर्ण

अटल पूर्णांक statfs_by_dentry(काष्ठा dentry *dentry, काष्ठा kstatfs *buf)
अणु
	पूर्णांक retval;

	अगर (!dentry->d_sb->s_op->statfs)
		वापस -ENOSYS;

	स_रखो(buf, 0, माप(*buf));
	retval = security_sb_statfs(dentry);
	अगर (retval)
		वापस retval;
	retval = dentry->d_sb->s_op->statfs(dentry, buf);
	अगर (retval == 0 && buf->f_frsize == 0)
		buf->f_frsize = buf->f_bsize;
	वापस retval;
पूर्ण

पूर्णांक vfs_get_fsid(काष्ठा dentry *dentry, __kernel_fsid_t *fsid)
अणु
	काष्ठा kstatfs st;
	पूर्णांक error;

	error = statfs_by_dentry(dentry, &st);
	अगर (error)
		वापस error;

	*fsid = st.f_fsid;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(vfs_get_fsid);

पूर्णांक vfs_statfs(स्थिर काष्ठा path *path, काष्ठा kstatfs *buf)
अणु
	पूर्णांक error;

	error = statfs_by_dentry(path->dentry, buf);
	अगर (!error)
		buf->f_flags = calculate_f_flags(path->mnt);
	वापस error;
पूर्ण
EXPORT_SYMBOL(vfs_statfs);

पूर्णांक user_statfs(स्थिर अक्षर __user *pathname, काष्ठा kstatfs *st)
अणु
	काष्ठा path path;
	पूर्णांक error;
	अचिन्हित पूर्णांक lookup_flags = LOOKUP_FOLLOW|LOOKUP_AUTOMOUNT;
retry:
	error = user_path_at(AT_FDCWD, pathname, lookup_flags, &path);
	अगर (!error) अणु
		error = vfs_statfs(&path, st);
		path_put(&path);
		अगर (retry_estale(error, lookup_flags)) अणु
			lookup_flags |= LOOKUP_REVAL;
			जाओ retry;
		पूर्ण
	पूर्ण
	वापस error;
पूर्ण

पूर्णांक fd_statfs(पूर्णांक fd, काष्ठा kstatfs *st)
अणु
	काष्ठा fd f = fdget_raw(fd);
	पूर्णांक error = -EBADF;
	अगर (f.file) अणु
		error = vfs_statfs(&f.file->f_path, st);
		fdput(f);
	पूर्ण
	वापस error;
पूर्ण

अटल पूर्णांक करो_statfs_native(काष्ठा kstatfs *st, काष्ठा statfs __user *p)
अणु
	काष्ठा statfs buf;

	अगर (माप(buf) == माप(*st))
		स_नकल(&buf, st, माप(*st));
	अन्यथा अणु
		अगर (माप buf.f_blocks == 4) अणु
			अगर ((st->f_blocks | st->f_bमुक्त | st->f_bavail |
			     st->f_bsize | st->f_frsize) &
			    0xffffffff00000000ULL)
				वापस -EOVERFLOW;
			/*
			 * f_files and f_fमुक्त may be -1; it's okay to stuff
			 * that पूर्णांकo 32 bits
			 */
			अगर (st->f_files != -1 &&
			    (st->f_files & 0xffffffff00000000ULL))
				वापस -EOVERFLOW;
			अगर (st->f_fमुक्त != -1 &&
			    (st->f_fमुक्त & 0xffffffff00000000ULL))
				वापस -EOVERFLOW;
		पूर्ण

		buf.f_type = st->f_type;
		buf.f_bsize = st->f_bsize;
		buf.f_blocks = st->f_blocks;
		buf.f_bमुक्त = st->f_bमुक्त;
		buf.f_bavail = st->f_bavail;
		buf.f_files = st->f_files;
		buf.f_fमुक्त = st->f_fमुक्त;
		buf.f_fsid = st->f_fsid;
		buf.f_namelen = st->f_namelen;
		buf.f_frsize = st->f_frsize;
		buf.f_flags = st->f_flags;
		स_रखो(buf.f_spare, 0, माप(buf.f_spare));
	पूर्ण
	अगर (copy_to_user(p, &buf, माप(buf)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल पूर्णांक करो_statfs64(काष्ठा kstatfs *st, काष्ठा statfs64 __user *p)
अणु
	काष्ठा statfs64 buf;
	अगर (माप(buf) == माप(*st))
		स_नकल(&buf, st, माप(*st));
	अन्यथा अणु
		buf.f_type = st->f_type;
		buf.f_bsize = st->f_bsize;
		buf.f_blocks = st->f_blocks;
		buf.f_bमुक्त = st->f_bमुक्त;
		buf.f_bavail = st->f_bavail;
		buf.f_files = st->f_files;
		buf.f_fमुक्त = st->f_fमुक्त;
		buf.f_fsid = st->f_fsid;
		buf.f_namelen = st->f_namelen;
		buf.f_frsize = st->f_frsize;
		buf.f_flags = st->f_flags;
		स_रखो(buf.f_spare, 0, माप(buf.f_spare));
	पूर्ण
	अगर (copy_to_user(p, &buf, माप(buf)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

SYSCALL_DEFINE2(statfs, स्थिर अक्षर __user *, pathname, काष्ठा statfs __user *, buf)
अणु
	काष्ठा kstatfs st;
	पूर्णांक error = user_statfs(pathname, &st);
	अगर (!error)
		error = करो_statfs_native(&st, buf);
	वापस error;
पूर्ण

SYSCALL_DEFINE3(statfs64, स्थिर अक्षर __user *, pathname, माप_प्रकार, sz, काष्ठा statfs64 __user *, buf)
अणु
	काष्ठा kstatfs st;
	पूर्णांक error;
	अगर (sz != माप(*buf))
		वापस -EINVAL;
	error = user_statfs(pathname, &st);
	अगर (!error)
		error = करो_statfs64(&st, buf);
	वापस error;
पूर्ण

SYSCALL_DEFINE2(ख_स्थितिfs, अचिन्हित पूर्णांक, fd, काष्ठा statfs __user *, buf)
अणु
	काष्ठा kstatfs st;
	पूर्णांक error = fd_statfs(fd, &st);
	अगर (!error)
		error = करो_statfs_native(&st, buf);
	वापस error;
पूर्ण

SYSCALL_DEFINE3(ख_स्थितिfs64, अचिन्हित पूर्णांक, fd, माप_प्रकार, sz, काष्ठा statfs64 __user *, buf)
अणु
	काष्ठा kstatfs st;
	पूर्णांक error;

	अगर (sz != माप(*buf))
		वापस -EINVAL;

	error = fd_statfs(fd, &st);
	अगर (!error)
		error = करो_statfs64(&st, buf);
	वापस error;
पूर्ण

अटल पूर्णांक vfs_ustat(dev_t dev, काष्ठा kstatfs *sbuf)
अणु
	काष्ठा super_block *s = user_get_super(dev, false);
	पूर्णांक err;
	अगर (!s)
		वापस -EINVAL;

	err = statfs_by_dentry(s->s_root, sbuf);
	drop_super(s);
	वापस err;
पूर्ण

SYSCALL_DEFINE2(ustat, अचिन्हित, dev, काष्ठा ustat __user *, ubuf)
अणु
	काष्ठा ustat पंचांगp;
	काष्ठा kstatfs sbuf;
	पूर्णांक err = vfs_ustat(new_decode_dev(dev), &sbuf);
	अगर (err)
		वापस err;

	स_रखो(&पंचांगp,0,माप(काष्ठा ustat));
	पंचांगp.f_tमुक्त = sbuf.f_bमुक्त;
	अगर (IS_ENABLED(CONFIG_ARCH_32BIT_USTAT_F_TINODE))
		पंचांगp.f_tinode = min_t(u64, sbuf.f_fमुक्त, अच_पूर्णांक_उच्च);
	अन्यथा
		पंचांगp.f_tinode = sbuf.f_fमुक्त;

	वापस copy_to_user(ubuf, &पंचांगp, माप(काष्ठा ustat)) ? -EFAULT : 0;
पूर्ण

#अगर_घोषित CONFIG_COMPAT
अटल पूर्णांक put_compat_statfs(काष्ठा compat_statfs __user *ubuf, काष्ठा kstatfs *kbuf)
अणु
	काष्ठा compat_statfs buf;
	अगर (माप ubuf->f_blocks == 4) अणु
		अगर ((kbuf->f_blocks | kbuf->f_bमुक्त | kbuf->f_bavail |
		     kbuf->f_bsize | kbuf->f_frsize) & 0xffffffff00000000ULL)
			वापस -EOVERFLOW;
		/* f_files and f_fमुक्त may be -1; it's okay
		 * to stuff that पूर्णांकo 32 bits */
		अगर (kbuf->f_files != 0xffffffffffffffffULL
		 && (kbuf->f_files & 0xffffffff00000000ULL))
			वापस -EOVERFLOW;
		अगर (kbuf->f_fमुक्त != 0xffffffffffffffffULL
		 && (kbuf->f_fमुक्त & 0xffffffff00000000ULL))
			वापस -EOVERFLOW;
	पूर्ण
	स_रखो(&buf, 0, माप(काष्ठा compat_statfs));
	buf.f_type = kbuf->f_type;
	buf.f_bsize = kbuf->f_bsize;
	buf.f_blocks = kbuf->f_blocks;
	buf.f_bमुक्त = kbuf->f_bमुक्त;
	buf.f_bavail = kbuf->f_bavail;
	buf.f_files = kbuf->f_files;
	buf.f_fमुक्त = kbuf->f_fमुक्त;
	buf.f_namelen = kbuf->f_namelen;
	buf.f_fsid.val[0] = kbuf->f_fsid.val[0];
	buf.f_fsid.val[1] = kbuf->f_fsid.val[1];
	buf.f_frsize = kbuf->f_frsize;
	buf.f_flags = kbuf->f_flags;
	अगर (copy_to_user(ubuf, &buf, माप(काष्ठा compat_statfs)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

/*
 * The following statfs calls are copies of code from fs/statfs.c and
 * should be checked against those from समय to समय
 */
COMPAT_SYSCALL_DEFINE2(statfs, स्थिर अक्षर __user *, pathname, काष्ठा compat_statfs __user *, buf)
अणु
	काष्ठा kstatfs पंचांगp;
	पूर्णांक error = user_statfs(pathname, &पंचांगp);
	अगर (!error)
		error = put_compat_statfs(buf, &पंचांगp);
	वापस error;
पूर्ण

COMPAT_SYSCALL_DEFINE2(ख_स्थितिfs, अचिन्हित पूर्णांक, fd, काष्ठा compat_statfs __user *, buf)
अणु
	काष्ठा kstatfs पंचांगp;
	पूर्णांक error = fd_statfs(fd, &पंचांगp);
	अगर (!error)
		error = put_compat_statfs(buf, &पंचांगp);
	वापस error;
पूर्ण

अटल पूर्णांक put_compat_statfs64(काष्ठा compat_statfs64 __user *ubuf, काष्ठा kstatfs *kbuf)
अणु
	काष्ठा compat_statfs64 buf;

	अगर ((kbuf->f_bsize | kbuf->f_frsize) & 0xffffffff00000000ULL)
		वापस -EOVERFLOW;

	स_रखो(&buf, 0, माप(काष्ठा compat_statfs64));
	buf.f_type = kbuf->f_type;
	buf.f_bsize = kbuf->f_bsize;
	buf.f_blocks = kbuf->f_blocks;
	buf.f_bमुक्त = kbuf->f_bमुक्त;
	buf.f_bavail = kbuf->f_bavail;
	buf.f_files = kbuf->f_files;
	buf.f_fमुक्त = kbuf->f_fमुक्त;
	buf.f_namelen = kbuf->f_namelen;
	buf.f_fsid.val[0] = kbuf->f_fsid.val[0];
	buf.f_fsid.val[1] = kbuf->f_fsid.val[1];
	buf.f_frsize = kbuf->f_frsize;
	buf.f_flags = kbuf->f_flags;
	अगर (copy_to_user(ubuf, &buf, माप(काष्ठा compat_statfs64)))
		वापस -EFAULT;
	वापस 0;
पूर्ण

पूर्णांक kcompat_sys_statfs64(स्थिर अक्षर __user * pathname, compat_माप_प्रकार sz, काष्ठा compat_statfs64 __user * buf)
अणु
	काष्ठा kstatfs पंचांगp;
	पूर्णांक error;

	अगर (sz != माप(*buf))
		वापस -EINVAL;

	error = user_statfs(pathname, &पंचांगp);
	अगर (!error)
		error = put_compat_statfs64(buf, &पंचांगp);
	वापस error;
पूर्ण

COMPAT_SYSCALL_DEFINE3(statfs64, स्थिर अक्षर __user *, pathname, compat_माप_प्रकार, sz, काष्ठा compat_statfs64 __user *, buf)
अणु
	वापस kcompat_sys_statfs64(pathname, sz, buf);
पूर्ण

पूर्णांक kcompat_sys_ख_स्थितिfs64(अचिन्हित पूर्णांक fd, compat_माप_प्रकार sz, काष्ठा compat_statfs64 __user * buf)
अणु
	काष्ठा kstatfs पंचांगp;
	पूर्णांक error;

	अगर (sz != माप(*buf))
		वापस -EINVAL;

	error = fd_statfs(fd, &पंचांगp);
	अगर (!error)
		error = put_compat_statfs64(buf, &पंचांगp);
	वापस error;
पूर्ण

COMPAT_SYSCALL_DEFINE3(ख_स्थितिfs64, अचिन्हित पूर्णांक, fd, compat_माप_प्रकार, sz, काष्ठा compat_statfs64 __user *, buf)
अणु
	वापस kcompat_sys_ख_स्थितिfs64(fd, sz, buf);
पूर्ण

/*
 * This is a copy of sys_ustat, just dealing with a काष्ठाure layout.
 * Given how simple this syscall is that apporach is more मुख्यtainable
 * than the various conversion hacks.
 */
COMPAT_SYSCALL_DEFINE2(ustat, अचिन्हित, dev, काष्ठा compat_ustat __user *, u)
अणु
	काष्ठा compat_ustat पंचांगp;
	काष्ठा kstatfs sbuf;
	पूर्णांक err = vfs_ustat(new_decode_dev(dev), &sbuf);
	अगर (err)
		वापस err;

	स_रखो(&पंचांगp, 0, माप(काष्ठा compat_ustat));
	पंचांगp.f_tमुक्त = sbuf.f_bमुक्त;
	पंचांगp.f_tinode = sbuf.f_fमुक्त;
	अगर (copy_to_user(u, &पंचांगp, माप(काष्ठा compat_ustat)))
		वापस -EFAULT;
	वापस 0;
पूर्ण
#पूर्ण_अगर
