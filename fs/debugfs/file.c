<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  file.c - part of debugfs, a tiny little debug file प्रणाली
 *
 *  Copyright (C) 2004 Greg Kroah-Harपंचांगan <greg@kroah.com>
 *  Copyright (C) 2004 IBM Inc.
 *
 *  debugfs is क्रम people to use instead of /proc or /sys.
 *  See Documentation/fileप्रणालीs/ क्रम more details.
 */

#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/atomic.h>
#समावेश <linux/device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/poll.h>
#समावेश <linux/security.h>

#समावेश "internal.h"

काष्ठा poll_table_काष्ठा;

अटल sमाप_प्रकार शेष_पढ़ो_file(काष्ठा file *file, अक्षर __user *buf,
				 माप_प्रकार count, loff_t *ppos)
अणु
	वापस 0;
पूर्ण

अटल sमाप_प्रकार शेष_ग_लिखो_file(काष्ठा file *file, स्थिर अक्षर __user *buf,
				   माप_प्रकार count, loff_t *ppos)
अणु
	वापस count;
पूर्ण

स्थिर काष्ठा file_operations debugfs_noop_file_operations = अणु
	.पढ़ो =		शेष_पढ़ो_file,
	.ग_लिखो =	शेष_ग_लिखो_file,
	.खोलो =		simple_खोलो,
	.llseek =	noop_llseek,
पूर्ण;

#घोषणा F_DENTRY(filp) ((filp)->f_path.dentry)

स्थिर काष्ठा file_operations *debugfs_real_fops(स्थिर काष्ठा file *filp)
अणु
	काष्ठा debugfs_fsdata *fsd = F_DENTRY(filp)->d_fsdata;

	अगर ((अचिन्हित दीर्घ)fsd & DEBUGFS_FSDATA_IS_REAL_FOPS_BIT) अणु
		/*
		 * Urgh, we've been called w/o a protecting
		 * debugfs_file_get().
		 */
		WARN_ON(1);
		वापस शून्य;
	पूर्ण

	वापस fsd->real_fops;
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_real_fops);

/**
 * debugfs_file_get - mark the beginning of file data access
 * @dentry: the dentry object whose data is being accessed.
 *
 * Up to a matching call to debugfs_file_put(), any successive call
 * पूर्णांकo the file removing functions debugfs_हटाओ() and
 * debugfs_हटाओ_recursive() will block. Since associated निजी
 * file data may only get मुक्तd after a successful वापस of any of
 * the removal functions, you may safely access it after a successful
 * call to debugfs_file_get() without worrying about lअगरeसमय issues.
 *
 * If -%EIO is वापसed, the file has alपढ़ोy been हटाओd and thus,
 * it is not safe to access any of its data. If, on the other hand,
 * it is allowed to access the file data, zero is वापसed.
 */
पूर्णांक debugfs_file_get(काष्ठा dentry *dentry)
अणु
	काष्ठा debugfs_fsdata *fsd;
	व्योम *d_fsd;

	d_fsd = READ_ONCE(dentry->d_fsdata);
	अगर (!((अचिन्हित दीर्घ)d_fsd & DEBUGFS_FSDATA_IS_REAL_FOPS_BIT)) अणु
		fsd = d_fsd;
	पूर्ण अन्यथा अणु
		fsd = kदो_स्मृति(माप(*fsd), GFP_KERNEL);
		अगर (!fsd)
			वापस -ENOMEM;

		fsd->real_fops = (व्योम *)((अचिन्हित दीर्घ)d_fsd &
					~DEBUGFS_FSDATA_IS_REAL_FOPS_BIT);
		refcount_set(&fsd->active_users, 1);
		init_completion(&fsd->active_users_drained);
		अगर (cmpxchg(&dentry->d_fsdata, d_fsd, fsd) != d_fsd) अणु
			kमुक्त(fsd);
			fsd = READ_ONCE(dentry->d_fsdata);
		पूर्ण
	पूर्ण

	/*
	 * In हाल of a successful cmpxchg() above, this check is
	 * strictly necessary and must follow it, see the comment in
	 * __debugfs_हटाओ_file().
	 * OTOH, अगर the cmpxchg() hasn't been executed or wasn't
	 * successful, this serves the purpose of not starving
	 * हटाओrs.
	 */
	अगर (d_unlinked(dentry))
		वापस -EIO;

	अगर (!refcount_inc_not_zero(&fsd->active_users))
		वापस -EIO;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_file_get);

/**
 * debugfs_file_put - mark the end of file data access
 * @dentry: the dentry object क्रमmerly passed to
 *          debugfs_file_get().
 *
 * Allow any ongoing concurrent call पूर्णांकo debugfs_हटाओ() or
 * debugfs_हटाओ_recursive() blocked by a क्रमmer call to
 * debugfs_file_get() to proceed and वापस to its caller.
 */
व्योम debugfs_file_put(काष्ठा dentry *dentry)
अणु
	काष्ठा debugfs_fsdata *fsd = READ_ONCE(dentry->d_fsdata);

	अगर (refcount_dec_and_test(&fsd->active_users))
		complete(&fsd->active_users_drained);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_file_put);

/*
 * Only permit access to world-पढ़ोable files when the kernel is locked करोwn.
 * We also need to exclude any file that has ways to ग_लिखो or alter it as root
 * can bypass the permissions check.
 */
अटल पूर्णांक debugfs_locked_करोwn(काष्ठा inode *inode,
			       काष्ठा file *filp,
			       स्थिर काष्ठा file_operations *real_fops)
अणु
	अगर ((inode->i_mode & 07777) == 0444 &&
	    !(filp->f_mode & FMODE_WRITE) &&
	    !real_fops->unlocked_ioctl &&
	    !real_fops->compat_ioctl &&
	    !real_fops->mmap)
		वापस 0;

	अगर (security_locked_करोwn(LOCKDOWN_DEBUGFS))
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल पूर्णांक खोलो_proxy_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा dentry *dentry = F_DENTRY(filp);
	स्थिर काष्ठा file_operations *real_fops = शून्य;
	पूर्णांक r;

	r = debugfs_file_get(dentry);
	अगर (r)
		वापस r == -EIO ? -ENOENT : r;

	real_fops = debugfs_real_fops(filp);

	r = debugfs_locked_करोwn(inode, filp, real_fops);
	अगर (r)
		जाओ out;

	अगर (!fops_get(real_fops)) अणु
#अगर_घोषित CONFIG_MODULES
		अगर (real_fops->owner &&
		    real_fops->owner->state == MODULE_STATE_GOING)
			जाओ out;
#पूर्ण_अगर

		/* Huh? Module did not clean up after itself at निकास? */
		WARN(1, "debugfs file owner did not clean up at exit: %pd",
			dentry);
		r = -ENXIO;
		जाओ out;
	पूर्ण
	replace_fops(filp, real_fops);

	अगर (real_fops->खोलो)
		r = real_fops->खोलो(inode, filp);

out:
	debugfs_file_put(dentry);
	वापस r;
पूर्ण

स्थिर काष्ठा file_operations debugfs_खोलो_proxy_file_operations = अणु
	.खोलो = खोलो_proxy_खोलो,
पूर्ण;

#घोषणा PROTO(args...) args
#घोषणा ARGS(args...) args

#घोषणा FULL_PROXY_FUNC(name, ret_type, filp, proto, args)		\
अटल ret_type full_proxy_ ## name(proto)				\
अणु									\
	काष्ठा dentry *dentry = F_DENTRY(filp);			\
	स्थिर काष्ठा file_operations *real_fops;			\
	ret_type r;							\
									\
	r = debugfs_file_get(dentry);					\
	अगर (unlikely(r))						\
		वापस r;						\
	real_fops = debugfs_real_fops(filp);				\
	r = real_fops->name(args);					\
	debugfs_file_put(dentry);					\
	वापस r;							\
पूर्ण

FULL_PROXY_FUNC(llseek, loff_t, filp,
		PROTO(काष्ठा file *filp, loff_t offset, पूर्णांक whence),
		ARGS(filp, offset, whence));

FULL_PROXY_FUNC(पढ़ो, sमाप_प्रकार, filp,
		PROTO(काष्ठा file *filp, अक्षर __user *buf, माप_प्रकार size,
			loff_t *ppos),
		ARGS(filp, buf, size, ppos));

FULL_PROXY_FUNC(ग_लिखो, sमाप_प्रकार, filp,
		PROTO(काष्ठा file *filp, स्थिर अक्षर __user *buf, माप_प्रकार size,
			loff_t *ppos),
		ARGS(filp, buf, size, ppos));

FULL_PROXY_FUNC(unlocked_ioctl, दीर्घ, filp,
		PROTO(काष्ठा file *filp, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg),
		ARGS(filp, cmd, arg));

अटल __poll_t full_proxy_poll(काष्ठा file *filp,
				काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा dentry *dentry = F_DENTRY(filp);
	__poll_t r = 0;
	स्थिर काष्ठा file_operations *real_fops;

	अगर (debugfs_file_get(dentry))
		वापस EPOLLHUP;

	real_fops = debugfs_real_fops(filp);
	r = real_fops->poll(filp, रुको);
	debugfs_file_put(dentry);
	वापस r;
पूर्ण

अटल पूर्णांक full_proxy_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	स्थिर काष्ठा dentry *dentry = F_DENTRY(filp);
	स्थिर काष्ठा file_operations *real_fops = debugfs_real_fops(filp);
	स्थिर काष्ठा file_operations *proxy_fops = filp->f_op;
	पूर्णांक r = 0;

	/*
	 * We must not protect this against removal races here: the
	 * original releaser should be called unconditionally in order
	 * not to leak any resources. Releasers must not assume that
	 * ->i_निजी is still being meaningful here.
	 */
	अगर (real_fops->release)
		r = real_fops->release(inode, filp);

	replace_fops(filp, d_inode(dentry)->i_fop);
	kमुक्त(proxy_fops);
	fops_put(real_fops);
	वापस r;
पूर्ण

अटल व्योम __full_proxy_fops_init(काष्ठा file_operations *proxy_fops,
				स्थिर काष्ठा file_operations *real_fops)
अणु
	proxy_fops->release = full_proxy_release;
	अगर (real_fops->llseek)
		proxy_fops->llseek = full_proxy_llseek;
	अगर (real_fops->पढ़ो)
		proxy_fops->पढ़ो = full_proxy_पढ़ो;
	अगर (real_fops->ग_लिखो)
		proxy_fops->ग_लिखो = full_proxy_ग_लिखो;
	अगर (real_fops->poll)
		proxy_fops->poll = full_proxy_poll;
	अगर (real_fops->unlocked_ioctl)
		proxy_fops->unlocked_ioctl = full_proxy_unlocked_ioctl;
पूर्ण

अटल पूर्णांक full_proxy_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	काष्ठा dentry *dentry = F_DENTRY(filp);
	स्थिर काष्ठा file_operations *real_fops = शून्य;
	काष्ठा file_operations *proxy_fops = शून्य;
	पूर्णांक r;

	r = debugfs_file_get(dentry);
	अगर (r)
		वापस r == -EIO ? -ENOENT : r;

	real_fops = debugfs_real_fops(filp);

	r = debugfs_locked_करोwn(inode, filp, real_fops);
	अगर (r)
		जाओ out;

	अगर (!fops_get(real_fops)) अणु
#अगर_घोषित CONFIG_MODULES
		अगर (real_fops->owner &&
		    real_fops->owner->state == MODULE_STATE_GOING)
			जाओ out;
#पूर्ण_अगर

		/* Huh? Module did not cleanup after itself at निकास? */
		WARN(1, "debugfs file owner did not clean up at exit: %pd",
			dentry);
		r = -ENXIO;
		जाओ out;
	पूर्ण

	proxy_fops = kzalloc(माप(*proxy_fops), GFP_KERNEL);
	अगर (!proxy_fops) अणु
		r = -ENOMEM;
		जाओ मुक्त_proxy;
	पूर्ण
	__full_proxy_fops_init(proxy_fops, real_fops);
	replace_fops(filp, proxy_fops);

	अगर (real_fops->खोलो) अणु
		r = real_fops->खोलो(inode, filp);
		अगर (r) अणु
			replace_fops(filp, d_inode(dentry)->i_fop);
			जाओ मुक्त_proxy;
		पूर्ण अन्यथा अगर (filp->f_op != proxy_fops) अणु
			/* No protection against file removal anymore. */
			WARN(1, "debugfs file owner replaced proxy fops: %pd",
				dentry);
			जाओ मुक्त_proxy;
		पूर्ण
	पूर्ण

	जाओ out;
मुक्त_proxy:
	kमुक्त(proxy_fops);
	fops_put(real_fops);
out:
	debugfs_file_put(dentry);
	वापस r;
पूर्ण

स्थिर काष्ठा file_operations debugfs_full_proxy_file_operations = अणु
	.खोलो = full_proxy_खोलो,
पूर्ण;

sमाप_प्रकार debugfs_attr_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा dentry *dentry = F_DENTRY(file);
	sमाप_प्रकार ret;

	ret = debugfs_file_get(dentry);
	अगर (unlikely(ret))
		वापस ret;
	ret = simple_attr_पढ़ो(file, buf, len, ppos);
	debugfs_file_put(dentry);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_attr_पढ़ो);

sमाप_प्रकार debugfs_attr_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार len, loff_t *ppos)
अणु
	काष्ठा dentry *dentry = F_DENTRY(file);
	sमाप_प्रकार ret;

	ret = debugfs_file_get(dentry);
	अगर (unlikely(ret))
		वापस ret;
	ret = simple_attr_ग_लिखो(file, buf, len, ppos);
	debugfs_file_put(dentry);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_attr_ग_लिखो);

अटल काष्ठा dentry *debugfs_create_mode_unsafe(स्थिर अक्षर *name, umode_t mode,
					काष्ठा dentry *parent, व्योम *value,
					स्थिर काष्ठा file_operations *fops,
					स्थिर काष्ठा file_operations *fops_ro,
					स्थिर काष्ठा file_operations *fops_wo)
अणु
	/* अगर there are no ग_लिखो bits set, make पढ़ो only */
	अगर (!(mode & S_IWUGO))
		वापस debugfs_create_file_unsafe(name, mode, parent, value,
						fops_ro);
	/* अगर there are no पढ़ो bits set, make ग_लिखो only */
	अगर (!(mode & S_IRUGO))
		वापस debugfs_create_file_unsafe(name, mode, parent, value,
						fops_wo);

	वापस debugfs_create_file_unsafe(name, mode, parent, value, fops);
पूर्ण

अटल पूर्णांक debugfs_u8_set(व्योम *data, u64 val)
अणु
	*(u8 *)data = val;
	वापस 0;
पूर्ण
अटल पूर्णांक debugfs_u8_get(व्योम *data, u64 *val)
अणु
	*val = *(u8 *)data;
	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fops_u8, debugfs_u8_get, debugfs_u8_set, "%llu\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_u8_ro, debugfs_u8_get, शून्य, "%llu\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_u8_wo, शून्य, debugfs_u8_set, "%llu\n");

/**
 * debugfs_create_u8 - create a debugfs file that is used to पढ़ो and ग_लिखो an अचिन्हित 8-bit value
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @value: a poपूर्णांकer to the variable that the file should पढ़ो to and ग_लिखो
 *         from.
 *
 * This function creates a file in debugfs with the given name that
 * contains the value of the variable @value.  If the @mode variable is so
 * set, it can be पढ़ो from, and written to.
 */
व्योम debugfs_create_u8(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
		       u8 *value)
अणु
	debugfs_create_mode_unsafe(name, mode, parent, value, &fops_u8,
				   &fops_u8_ro, &fops_u8_wo);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_u8);

अटल पूर्णांक debugfs_u16_set(व्योम *data, u64 val)
अणु
	*(u16 *)data = val;
	वापस 0;
पूर्ण
अटल पूर्णांक debugfs_u16_get(व्योम *data, u64 *val)
अणु
	*val = *(u16 *)data;
	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fops_u16, debugfs_u16_get, debugfs_u16_set, "%llu\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_u16_ro, debugfs_u16_get, शून्य, "%llu\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_u16_wo, शून्य, debugfs_u16_set, "%llu\n");

/**
 * debugfs_create_u16 - create a debugfs file that is used to पढ़ो and ग_लिखो an अचिन्हित 16-bit value
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @value: a poपूर्णांकer to the variable that the file should पढ़ो to and ग_लिखो
 *         from.
 *
 * This function creates a file in debugfs with the given name that
 * contains the value of the variable @value.  If the @mode variable is so
 * set, it can be पढ़ो from, and written to.
 */
व्योम debugfs_create_u16(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
			u16 *value)
अणु
	debugfs_create_mode_unsafe(name, mode, parent, value, &fops_u16,
				   &fops_u16_ro, &fops_u16_wo);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_u16);

अटल पूर्णांक debugfs_u32_set(व्योम *data, u64 val)
अणु
	*(u32 *)data = val;
	वापस 0;
पूर्ण
अटल पूर्णांक debugfs_u32_get(व्योम *data, u64 *val)
अणु
	*val = *(u32 *)data;
	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fops_u32, debugfs_u32_get, debugfs_u32_set, "%llu\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_u32_ro, debugfs_u32_get, शून्य, "%llu\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_u32_wo, शून्य, debugfs_u32_set, "%llu\n");

/**
 * debugfs_create_u32 - create a debugfs file that is used to पढ़ो and ग_लिखो an अचिन्हित 32-bit value
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @value: a poपूर्णांकer to the variable that the file should पढ़ो to and ग_लिखो
 *         from.
 *
 * This function creates a file in debugfs with the given name that
 * contains the value of the variable @value.  If the @mode variable is so
 * set, it can be पढ़ो from, and written to.
 */
व्योम debugfs_create_u32(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
			u32 *value)
अणु
	debugfs_create_mode_unsafe(name, mode, parent, value, &fops_u32,
				   &fops_u32_ro, &fops_u32_wo);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_u32);

अटल पूर्णांक debugfs_u64_set(व्योम *data, u64 val)
अणु
	*(u64 *)data = val;
	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_u64_get(व्योम *data, u64 *val)
अणु
	*val = *(u64 *)data;
	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fops_u64, debugfs_u64_get, debugfs_u64_set, "%llu\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_u64_ro, debugfs_u64_get, शून्य, "%llu\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_u64_wo, शून्य, debugfs_u64_set, "%llu\n");

/**
 * debugfs_create_u64 - create a debugfs file that is used to पढ़ो and ग_लिखो an अचिन्हित 64-bit value
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @value: a poपूर्णांकer to the variable that the file should पढ़ो to and ग_लिखो
 *         from.
 *
 * This function creates a file in debugfs with the given name that
 * contains the value of the variable @value.  If the @mode variable is so
 * set, it can be पढ़ो from, and written to.
 */
व्योम debugfs_create_u64(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
			u64 *value)
अणु
	debugfs_create_mode_unsafe(name, mode, parent, value, &fops_u64,
				   &fops_u64_ro, &fops_u64_wo);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_u64);

अटल पूर्णांक debugfs_uदीर्घ_set(व्योम *data, u64 val)
अणु
	*(अचिन्हित दीर्घ *)data = val;
	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_uदीर्घ_get(व्योम *data, u64 *val)
अणु
	*val = *(अचिन्हित दीर्घ *)data;
	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fops_uदीर्घ, debugfs_uदीर्घ_get, debugfs_uदीर्घ_set,
			"%llu\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_uदीर्घ_ro, debugfs_uदीर्घ_get, शून्य, "%llu\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_uदीर्घ_wo, शून्य, debugfs_uदीर्घ_set, "%llu\n");

/**
 * debugfs_create_uदीर्घ - create a debugfs file that is used to पढ़ो and ग_लिखो
 * an अचिन्हित दीर्घ value.
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @value: a poपूर्णांकer to the variable that the file should पढ़ो to and ग_लिखो
 *         from.
 *
 * This function creates a file in debugfs with the given name that
 * contains the value of the variable @value.  If the @mode variable is so
 * set, it can be पढ़ो from, and written to.
 *
 * This function will वापस a poपूर्णांकer to a dentry अगर it succeeds.  This
 * poपूर्णांकer must be passed to the debugfs_हटाओ() function when the file is
 * to be हटाओd (no स्वतःmatic cleanup happens अगर your module is unloaded,
 * you are responsible here.)  If an error occurs, ERR_PTR(-ERROR) will be
 * वापसed.
 *
 * If debugfs is not enabled in the kernel, the value ERR_PTR(-ENODEV) will
 * be वापसed.
 */
काष्ठा dentry *debugfs_create_uदीर्घ(स्थिर अक्षर *name, umode_t mode,
				    काष्ठा dentry *parent, अचिन्हित दीर्घ *value)
अणु
	वापस debugfs_create_mode_unsafe(name, mode, parent, value,
					&fops_uदीर्घ, &fops_uदीर्घ_ro,
					&fops_uदीर्घ_wo);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_uदीर्घ);

DEFINE_DEBUGFS_ATTRIBUTE(fops_x8, debugfs_u8_get, debugfs_u8_set, "0x%02llx\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_x8_ro, debugfs_u8_get, शून्य, "0x%02llx\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_x8_wo, शून्य, debugfs_u8_set, "0x%02llx\n");

DEFINE_DEBUGFS_ATTRIBUTE(fops_x16, debugfs_u16_get, debugfs_u16_set,
			"0x%04llx\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_x16_ro, debugfs_u16_get, शून्य, "0x%04llx\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_x16_wo, शून्य, debugfs_u16_set, "0x%04llx\n");

DEFINE_DEBUGFS_ATTRIBUTE(fops_x32, debugfs_u32_get, debugfs_u32_set,
			"0x%08llx\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_x32_ro, debugfs_u32_get, शून्य, "0x%08llx\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_x32_wo, शून्य, debugfs_u32_set, "0x%08llx\n");

DEFINE_DEBUGFS_ATTRIBUTE(fops_x64, debugfs_u64_get, debugfs_u64_set,
			"0x%016llx\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_x64_ro, debugfs_u64_get, शून्य, "0x%016llx\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_x64_wo, शून्य, debugfs_u64_set, "0x%016llx\n");

/*
 * debugfs_create_xअणु8,16,32,64पूर्ण - create a debugfs file that is used to पढ़ो and ग_लिखो an अचिन्हित अणु8,16,32,64पूर्ण-bit value
 *
 * These functions are exactly the same as the above functions (but use a hex
 * output क्रम the decimal challenged). For details look at the above अचिन्हित
 * decimal functions.
 */

/**
 * debugfs_create_x8 - create a debugfs file that is used to पढ़ो and ग_लिखो an अचिन्हित 8-bit value
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @value: a poपूर्णांकer to the variable that the file should पढ़ो to and ग_लिखो
 *         from.
 */
व्योम debugfs_create_x8(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
		       u8 *value)
अणु
	debugfs_create_mode_unsafe(name, mode, parent, value, &fops_x8,
				   &fops_x8_ro, &fops_x8_wo);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_x8);

/**
 * debugfs_create_x16 - create a debugfs file that is used to पढ़ो and ग_लिखो an अचिन्हित 16-bit value
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @value: a poपूर्णांकer to the variable that the file should पढ़ो to and ग_लिखो
 *         from.
 */
व्योम debugfs_create_x16(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
			u16 *value)
अणु
	debugfs_create_mode_unsafe(name, mode, parent, value, &fops_x16,
				   &fops_x16_ro, &fops_x16_wo);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_x16);

/**
 * debugfs_create_x32 - create a debugfs file that is used to पढ़ो and ग_लिखो an अचिन्हित 32-bit value
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @value: a poपूर्णांकer to the variable that the file should पढ़ो to and ग_लिखो
 *         from.
 */
व्योम debugfs_create_x32(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
			u32 *value)
अणु
	debugfs_create_mode_unsafe(name, mode, parent, value, &fops_x32,
				   &fops_x32_ro, &fops_x32_wo);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_x32);

/**
 * debugfs_create_x64 - create a debugfs file that is used to पढ़ो and ग_लिखो an अचिन्हित 64-bit value
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @value: a poपूर्णांकer to the variable that the file should पढ़ो to and ग_लिखो
 *         from.
 */
व्योम debugfs_create_x64(स्थिर अक्षर *name, umode_t mode, काष्ठा dentry *parent,
			u64 *value)
अणु
	debugfs_create_mode_unsafe(name, mode, parent, value, &fops_x64,
				   &fops_x64_ro, &fops_x64_wo);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_x64);


अटल पूर्णांक debugfs_माप_प्रकार_set(व्योम *data, u64 val)
अणु
	*(माप_प्रकार *)data = val;
	वापस 0;
पूर्ण
अटल पूर्णांक debugfs_माप_प्रकार_get(व्योम *data, u64 *val)
अणु
	*val = *(माप_प्रकार *)data;
	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fops_माप_प्रकार, debugfs_माप_प्रकार_get, debugfs_माप_प्रकार_set,
			"%llu\n"); /* %llu and %zu are more or less the same */
DEFINE_DEBUGFS_ATTRIBUTE(fops_माप_प्रकार_ro, debugfs_माप_प्रकार_get, शून्य, "%llu\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_माप_प्रकार_wo, शून्य, debugfs_माप_प्रकार_set, "%llu\n");

/**
 * debugfs_create_माप_प्रकार - create a debugfs file that is used to पढ़ो and ग_लिखो an माप_प्रकार value
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @value: a poपूर्णांकer to the variable that the file should पढ़ो to and ग_लिखो
 *         from.
 */
व्योम debugfs_create_माप_प्रकार(स्थिर अक्षर *name, umode_t mode,
			   काष्ठा dentry *parent, माप_प्रकार *value)
अणु
	debugfs_create_mode_unsafe(name, mode, parent, value, &fops_माप_प्रकार,
				   &fops_माप_प्रकार_ro, &fops_माप_प्रकार_wo);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_माप_प्रकार);

अटल पूर्णांक debugfs_atomic_t_set(व्योम *data, u64 val)
अणु
	atomic_set((atomic_t *)data, val);
	वापस 0;
पूर्ण
अटल पूर्णांक debugfs_atomic_t_get(व्योम *data, u64 *val)
अणु
	*val = atomic_पढ़ो((atomic_t *)data);
	वापस 0;
पूर्ण
DEFINE_DEBUGFS_ATTRIBUTE(fops_atomic_t, debugfs_atomic_t_get,
			debugfs_atomic_t_set, "%lld\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_atomic_t_ro, debugfs_atomic_t_get, शून्य,
			"%lld\n");
DEFINE_DEBUGFS_ATTRIBUTE(fops_atomic_t_wo, शून्य, debugfs_atomic_t_set,
			"%lld\n");

/**
 * debugfs_create_atomic_t - create a debugfs file that is used to पढ़ो and
 * ग_लिखो an atomic_t value
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @value: a poपूर्णांकer to the variable that the file should पढ़ो to and ग_लिखो
 *         from.
 */
व्योम debugfs_create_atomic_t(स्थिर अक्षर *name, umode_t mode,
			     काष्ठा dentry *parent, atomic_t *value)
अणु
	debugfs_create_mode_unsafe(name, mode, parent, value, &fops_atomic_t,
				   &fops_atomic_t_ro, &fops_atomic_t_wo);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_atomic_t);

sमाप_प्रकार debugfs_पढ़ो_file_bool(काष्ठा file *file, अक्षर __user *user_buf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	अक्षर buf[2];
	bool val;
	पूर्णांक r;
	काष्ठा dentry *dentry = F_DENTRY(file);

	r = debugfs_file_get(dentry);
	अगर (unlikely(r))
		वापस r;
	val = *(bool *)file->निजी_data;
	debugfs_file_put(dentry);

	अगर (val)
		buf[0] = 'Y';
	अन्यथा
		buf[0] = 'N';
	buf[1] = '\n';
	वापस simple_पढ़ो_from_buffer(user_buf, count, ppos, buf, 2);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_पढ़ो_file_bool);

sमाप_प्रकार debugfs_ग_लिखो_file_bool(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				माप_प्रकार count, loff_t *ppos)
अणु
	bool bv;
	पूर्णांक r;
	bool *val = file->निजी_data;
	काष्ठा dentry *dentry = F_DENTRY(file);

	r = kstrtobool_from_user(user_buf, count, &bv);
	अगर (!r) अणु
		r = debugfs_file_get(dentry);
		अगर (unlikely(r))
			वापस r;
		*val = bv;
		debugfs_file_put(dentry);
	पूर्ण

	वापस count;
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_ग_लिखो_file_bool);

अटल स्थिर काष्ठा file_operations fops_bool = अणु
	.पढ़ो =		debugfs_पढ़ो_file_bool,
	.ग_लिखो =	debugfs_ग_लिखो_file_bool,
	.खोलो =		simple_खोलो,
	.llseek =	शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations fops_bool_ro = अणु
	.पढ़ो =		debugfs_पढ़ो_file_bool,
	.खोलो =		simple_खोलो,
	.llseek =	शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations fops_bool_wo = अणु
	.ग_लिखो =	debugfs_ग_लिखो_file_bool,
	.खोलो =		simple_खोलो,
	.llseek =	शेष_llseek,
पूर्ण;

/**
 * debugfs_create_bool - create a debugfs file that is used to पढ़ो and ग_लिखो a boolean value
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @value: a poपूर्णांकer to the variable that the file should पढ़ो to and ग_लिखो
 *         from.
 *
 * This function creates a file in debugfs with the given name that
 * contains the value of the variable @value.  If the @mode variable is so
 * set, it can be पढ़ो from, and written to.
 *
 * This function will वापस a poपूर्णांकer to a dentry अगर it succeeds.  This
 * poपूर्णांकer must be passed to the debugfs_हटाओ() function when the file is
 * to be हटाओd (no स्वतःmatic cleanup happens अगर your module is unloaded,
 * you are responsible here.)  If an error occurs, ERR_PTR(-ERROR) will be
 * वापसed.
 *
 * If debugfs is not enabled in the kernel, the value ERR_PTR(-ENODEV) will
 * be वापसed.
 */
काष्ठा dentry *debugfs_create_bool(स्थिर अक्षर *name, umode_t mode,
				   काष्ठा dentry *parent, bool *value)
अणु
	वापस debugfs_create_mode_unsafe(name, mode, parent, value, &fops_bool,
				   &fops_bool_ro, &fops_bool_wo);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_bool);

sमाप_प्रकार debugfs_पढ़ो_file_str(काष्ठा file *file, अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा dentry *dentry = F_DENTRY(file);
	अक्षर *str, *copy = शून्य;
	पूर्णांक copy_len, len;
	sमाप_प्रकार ret;

	ret = debugfs_file_get(dentry);
	अगर (unlikely(ret))
		वापस ret;

	str = *(अक्षर **)file->निजी_data;
	len = म_माप(str) + 1;
	copy = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!copy) अणु
		debugfs_file_put(dentry);
		वापस -ENOMEM;
	पूर्ण

	copy_len = strscpy(copy, str, len);
	debugfs_file_put(dentry);
	अगर (copy_len < 0) अणु
		kमुक्त(copy);
		वापस copy_len;
	पूर्ण

	copy[copy_len] = '\n';

	ret = simple_पढ़ो_from_buffer(user_buf, count, ppos, copy, len);
	kमुक्त(copy);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार debugfs_ग_लिखो_file_str(काष्ठा file *file, स्थिर अक्षर __user *user_buf,
				      माप_प्रकार count, loff_t *ppos)
अणु
	/* This is really only क्रम पढ़ो-only strings */
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_str = अणु
	.पढ़ो =		debugfs_पढ़ो_file_str,
	.ग_लिखो =	debugfs_ग_लिखो_file_str,
	.खोलो =		simple_खोलो,
	.llseek =	शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations fops_str_ro = अणु
	.पढ़ो =		debugfs_पढ़ो_file_str,
	.खोलो =		simple_खोलो,
	.llseek =	शेष_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations fops_str_wo = अणु
	.ग_लिखो =	debugfs_ग_लिखो_file_str,
	.खोलो =		simple_खोलो,
	.llseek =	शेष_llseek,
पूर्ण;

/**
 * debugfs_create_str - create a debugfs file that is used to पढ़ो and ग_लिखो a string value
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @value: a poपूर्णांकer to the variable that the file should पढ़ो to and ग_लिखो
 *         from.
 *
 * This function creates a file in debugfs with the given name that
 * contains the value of the variable @value.  If the @mode variable is so
 * set, it can be पढ़ो from, and written to.
 *
 * This function will वापस a poपूर्णांकer to a dentry अगर it succeeds.  This
 * poपूर्णांकer must be passed to the debugfs_हटाओ() function when the file is
 * to be हटाओd (no स्वतःmatic cleanup happens अगर your module is unloaded,
 * you are responsible here.)  If an error occurs, ERR_PTR(-ERROR) will be
 * वापसed.
 *
 * If debugfs is not enabled in the kernel, the value ERR_PTR(-ENODEV) will
 * be वापसed.
 */
व्योम debugfs_create_str(स्थिर अक्षर *name, umode_t mode,
			काष्ठा dentry *parent, अक्षर **value)
अणु
	debugfs_create_mode_unsafe(name, mode, parent, value, &fops_str,
				   &fops_str_ro, &fops_str_wo);
पूर्ण

अटल sमाप_प्रकार पढ़ो_file_blob(काष्ठा file *file, अक्षर __user *user_buf,
			      माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा debugfs_blob_wrapper *blob = file->निजी_data;
	काष्ठा dentry *dentry = F_DENTRY(file);
	sमाप_प्रकार r;

	r = debugfs_file_get(dentry);
	अगर (unlikely(r))
		वापस r;
	r = simple_पढ़ो_from_buffer(user_buf, count, ppos, blob->data,
				blob->size);
	debugfs_file_put(dentry);
	वापस r;
पूर्ण

अटल स्थिर काष्ठा file_operations fops_blob = अणु
	.पढ़ो =		पढ़ो_file_blob,
	.खोलो =		simple_खोलो,
	.llseek =	शेष_llseek,
पूर्ण;

/**
 * debugfs_create_blob - create a debugfs file that is used to पढ़ो a binary blob
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @blob: a poपूर्णांकer to a काष्ठा debugfs_blob_wrapper which contains a poपूर्णांकer
 *        to the blob data and the size of the data.
 *
 * This function creates a file in debugfs with the given name that exports
 * @blob->data as a binary blob. If the @mode variable is so set it can be
 * पढ़ो from. Writing is not supported.
 *
 * This function will वापस a poपूर्णांकer to a dentry अगर it succeeds.  This
 * poपूर्णांकer must be passed to the debugfs_हटाओ() function when the file is
 * to be हटाओd (no स्वतःmatic cleanup happens अगर your module is unloaded,
 * you are responsible here.)  If an error occurs, ERR_PTR(-ERROR) will be
 * वापसed.
 *
 * If debugfs is not enabled in the kernel, the value ERR_PTR(-ENODEV) will
 * be वापसed.
 */
काष्ठा dentry *debugfs_create_blob(स्थिर अक्षर *name, umode_t mode,
				   काष्ठा dentry *parent,
				   काष्ठा debugfs_blob_wrapper *blob)
अणु
	वापस debugfs_create_file_unsafe(name, mode, parent, blob, &fops_blob);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_blob);

अटल माप_प्रकार u32_क्रमmat_array(अक्षर *buf, माप_प्रकार bufsize,
			       u32 *array, पूर्णांक array_size)
अणु
	माप_प्रकार ret = 0;

	जबतक (--array_size >= 0) अणु
		माप_प्रकार len;
		अक्षर term = array_size ? ' ' : '\n';

		len = snम_लिखो(buf, bufsize, "%u%c", *array++, term);
		ret += len;

		buf += len;
		bufsize -= len;
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक u32_array_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा debugfs_u32_array *data = inode->i_निजी;
	पूर्णांक size, elements = data->n_elements;
	अक्षर *buf;

	/*
	 * Max size:
	 *  - 10 digits + ' '/'\n' = 11 bytes per number
	 *  - terminating NUL अक्षरacter
	 */
	size = elements*11;
	buf = kदो_स्मृति(size+1, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	buf[size] = 0;

	file->निजी_data = buf;
	u32_क्रमmat_array(buf, size, data->array, data->n_elements);

	वापस nonseekable_खोलो(inode, file);
पूर्ण

अटल sमाप_प्रकार u32_array_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार len,
			      loff_t *ppos)
अणु
	माप_प्रकार size = म_माप(file->निजी_data);

	वापस simple_पढ़ो_from_buffer(buf, len, ppos,
					file->निजी_data, size);
पूर्ण

अटल पूर्णांक u32_array_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	kमुक्त(file->निजी_data);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा file_operations u32_array_fops = अणु
	.owner	 = THIS_MODULE,
	.खोलो	 = u32_array_खोलो,
	.release = u32_array_release,
	.पढ़ो	 = u32_array_पढ़ो,
	.llseek  = no_llseek,
पूर्ण;

/**
 * debugfs_create_u32_array - create a debugfs file that is used to पढ़ो u32
 * array.
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have.
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @array: wrapper काष्ठा containing data poपूर्णांकer and size of the array.
 *
 * This function creates a file in debugfs with the given name that exports
 * @array as data. If the @mode variable is so set it can be पढ़ो from.
 * Writing is not supported. Seek within the file is also not supported.
 * Once array is created its size can not be changed.
 */
व्योम debugfs_create_u32_array(स्थिर अक्षर *name, umode_t mode,
			      काष्ठा dentry *parent,
			      काष्ठा debugfs_u32_array *array)
अणु
	debugfs_create_file_unsafe(name, mode, parent, array, &u32_array_fops);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_u32_array);

#अगर_घोषित CONFIG_HAS_IOMEM

/*
 * The regset32 stuff is used to prपूर्णांक 32-bit रेजिस्टरs using the
 * seq_file utilities. We offer prपूर्णांकing a रेजिस्टर set in an alपढ़ोy-खोलोed
 * sequential file or create a debugfs file that only prपूर्णांकs a regset32.
 */

/**
 * debugfs_prपूर्णांक_regs32 - use seq_prपूर्णांक to describe a set of रेजिस्टरs
 * @s: the seq_file काष्ठाure being used to generate output
 * @regs: an array अगर काष्ठा debugfs_reg32 काष्ठाures
 * @nregs: the length of the above array
 * @base: the base address to be used in पढ़ोing the रेजिस्टरs
 * @prefix: a string to be prefixed to every output line
 *
 * This function outमाला_दो a text block describing the current values of
 * some 32-bit hardware रेजिस्टरs. It is meant to be used within debugfs
 * files based on seq_file that need to show रेजिस्टरs, पूर्णांकermixed with other
 * inक्रमmation. The prefix argument may be used to specअगरy a leading string,
 * because some peripherals have several blocks of identical रेजिस्टरs,
 * क्रम example configuration of dma channels
 */
व्योम debugfs_prपूर्णांक_regs32(काष्ठा seq_file *s, स्थिर काष्ठा debugfs_reg32 *regs,
			  पूर्णांक nregs, व्योम __iomem *base, अक्षर *prefix)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nregs; i++, regs++) अणु
		अगर (prefix)
			seq_म_लिखो(s, "%s", prefix);
		seq_म_लिखो(s, "%s = 0x%08x\n", regs->name,
			   पढ़ोl(base + regs->offset));
		अगर (seq_has_overflowed(s))
			अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_prपूर्णांक_regs32);

अटल पूर्णांक debugfs_show_regset32(काष्ठा seq_file *s, व्योम *data)
अणु
	काष्ठा debugfs_regset32 *regset = s->निजी;

	अगर (regset->dev)
		pm_runसमय_get_sync(regset->dev);

	debugfs_prपूर्णांक_regs32(s, regset->regs, regset->nregs, regset->base, "");

	अगर (regset->dev)
		pm_runसमय_put(regset->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक debugfs_खोलो_regset32(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, debugfs_show_regset32, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations fops_regset32 = अणु
	.खोलो =		debugfs_खोलो_regset32,
	.पढ़ो =		seq_पढ़ो,
	.llseek =	seq_lseek,
	.release =	single_release,
पूर्ण;

/**
 * debugfs_create_regset32 - create a debugfs file that वापसs रेजिस्टर values
 * @name: a poपूर्णांकer to a string containing the name of the file to create.
 * @mode: the permission that the file should have
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *          directory dentry अगर set.  If this parameter is %शून्य, then the
 *          file will be created in the root of the debugfs fileप्रणाली.
 * @regset: a poपूर्णांकer to a काष्ठा debugfs_regset32, which contains a poपूर्णांकer
 *          to an array of रेजिस्टर definitions, the array size and the base
 *          address where the रेजिस्टर bank is to be found.
 *
 * This function creates a file in debugfs with the given name that reports
 * the names and values of a set of 32-bit रेजिस्टरs. If the @mode variable
 * is so set it can be पढ़ो from. Writing is not supported.
 */
व्योम debugfs_create_regset32(स्थिर अक्षर *name, umode_t mode,
			     काष्ठा dentry *parent,
			     काष्ठा debugfs_regset32 *regset)
अणु
	debugfs_create_file(name, mode, parent, regset, &fops_regset32);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_regset32);

#पूर्ण_अगर /* CONFIG_HAS_IOMEM */

काष्ठा debugfs_devm_entry अणु
	पूर्णांक (*पढ़ो)(काष्ठा seq_file *seq, व्योम *data);
	काष्ठा device *dev;
पूर्ण;

अटल पूर्णांक debugfs_devm_entry_खोलो(काष्ठा inode *inode, काष्ठा file *f)
अणु
	काष्ठा debugfs_devm_entry *entry = inode->i_निजी;

	वापस single_खोलो(f, entry->पढ़ो, entry->dev);
पूर्ण

अटल स्थिर काष्ठा file_operations debugfs_devm_entry_ops = अणु
	.owner = THIS_MODULE,
	.खोलो = debugfs_devm_entry_खोलो,
	.release = single_release,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek
पूर्ण;

/**
 * debugfs_create_devm_seqfile - create a debugfs file that is bound to device.
 *
 * @dev: device related to this debugfs file.
 * @name: name of the debugfs file.
 * @parent: a poपूर्णांकer to the parent dentry क्रम this file.  This should be a
 *	directory dentry अगर set.  If this parameter is %शून्य, then the
 *	file will be created in the root of the debugfs fileप्रणाली.
 * @पढ़ो_fn: function poपूर्णांकer called to prपूर्णांक the seq_file content.
 */
व्योम debugfs_create_devm_seqfile(काष्ठा device *dev, स्थिर अक्षर *name,
				 काष्ठा dentry *parent,
				 पूर्णांक (*पढ़ो_fn)(काष्ठा seq_file *s, व्योम *data))
अणु
	काष्ठा debugfs_devm_entry *entry;

	अगर (IS_ERR(parent))
		वापस;

	entry = devm_kzalloc(dev, माप(*entry), GFP_KERNEL);
	अगर (!entry)
		वापस;

	entry->पढ़ो = पढ़ो_fn;
	entry->dev = dev;

	debugfs_create_file(name, S_IRUGO, parent, entry,
			    &debugfs_devm_entry_ops);
पूर्ण
EXPORT_SYMBOL_GPL(debugfs_create_devm_seqfile);
