<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * AppArmor security module
 *
 * This file contains AppArmor /sys/kernel/security/apparmor पूर्णांकerface functions
 *
 * Copyright (C) 1998-2008 Novell/SUSE
 * Copyright 2009-2010 Canonical Ltd.
 */

#समावेश <linux/प्रकार.स>
#समावेश <linux/security.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/init.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/capability.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/fs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/poll.h>
#समावेश <linux/zlib.h>
#समावेश <uapi/linux/major.h>
#समावेश <uapi/linux/magic.h>

#समावेश "include/apparmor.h"
#समावेश "include/apparmorfs.h"
#समावेश "include/audit.h"
#समावेश "include/cred.h"
#समावेश "include/crypto.h"
#समावेश "include/ipc.h"
#समावेश "include/label.h"
#समावेश "include/policy.h"
#समावेश "include/policy_ns.h"
#समावेश "include/resource.h"
#समावेश "include/policy_unpack.h"

/*
 * The apparmor fileप्रणाली पूर्णांकerface used क्रम policy load and पूर्णांकrospection
 * The पूर्णांकerface is split पूर्णांकo two मुख्य components based on their function
 * a securityfs component:
 *   used क्रम अटल files that are always available, and which allows
 *   userspace to specअगरicy the location of the security fileप्रणाली.
 *
 *   fns and data are prefixed with
 *      aa_sfs_
 *
 * an apparmorfs component:
 *   used loaded policy content and पूर्णांकrospection. It is not part of  a
 *   regular mounted fileप्रणाली and is available only through the magic
 *   policy symlink in the root of the securityfs apparmor/ directory.
 *   Tasks queries will be magically redirected to the correct portion
 *   of the policy tree based on their confinement.
 *
 *   fns and data are prefixed with
 *      aafs_
 *
 * The aa_fs_ prefix is used to indicate the fn is used by both the
 * securityfs and apparmorfs fileप्रणालीs.
 */


/*
 * support fns
 */

काष्ठा rawdata_f_data अणु
	काष्ठा aa_loaddata *loaddata;
पूर्ण;

#घोषणा RAWDATA_F_DATA_BUF(p) (अक्षर *)(p + 1)

अटल व्योम rawdata_f_data_मुक्त(काष्ठा rawdata_f_data *निजी)
अणु
	अगर (!निजी)
		वापस;

	aa_put_loaddata(निजी->loaddata);
	kvमुक्त(निजी);
पूर्ण

अटल काष्ठा rawdata_f_data *rawdata_f_data_alloc(माप_प्रकार size)
अणु
	काष्ठा rawdata_f_data *ret;

	अगर (size > SIZE_MAX - माप(*ret))
		वापस ERR_PTR(-EINVAL);

	ret = kvzalloc(माप(*ret) + size, GFP_KERNEL);
	अगर (!ret)
		वापस ERR_PTR(-ENOMEM);

	वापस ret;
पूर्ण

/**
 * aa_mangle_name - mangle a profile name to std profile layout क्रमm
 * @name: profile name to mangle  (NOT शून्य)
 * @target: buffer to store mangled name, same length as @name (MAYBE शून्य)
 *
 * Returns: length of mangled name
 */
अटल पूर्णांक mangle_name(स्थिर अक्षर *name, अक्षर *target)
अणु
	अक्षर *t = target;

	जबतक (*name == '/' || *name == '.')
		name++;

	अगर (target) अणु
		क्रम (; *name; name++) अणु
			अगर (*name == '/')
				*(t)++ = '.';
			अन्यथा अगर (है_खाली(*name))
				*(t)++ = '_';
			अन्यथा अगर (है_अक्षर_अंक(*name) || म_अक्षर("._-", *name))
				*(t)++ = *name;
		पूर्ण

		*t = 0;
	पूर्ण अन्यथा अणु
		पूर्णांक len = 0;
		क्रम (; *name; name++) अणु
			अगर (है_अक्षर_अंक(*name) || है_खाली(*name) ||
			    म_अक्षर("/._-", *name))
				len++;
		पूर्ण

		वापस len;
	पूर्ण

	वापस t - target;
पूर्ण


/*
 * aafs - core fns and data क्रम the policy tree
 */

#घोषणा AAFS_NAME		"apparmorfs"
अटल काष्ठा vfsmount *aafs_mnt;
अटल पूर्णांक aafs_count;


अटल पूर्णांक aafs_show_path(काष्ठा seq_file *seq, काष्ठा dentry *dentry)
अणु
	seq_म_लिखो(seq, "%s:[%lu]", AAFS_NAME, d_inode(dentry)->i_ino);
	वापस 0;
पूर्ण

अटल व्योम aafs_मुक्त_inode(काष्ठा inode *inode)
अणु
	अगर (S_ISLNK(inode->i_mode))
		kमुक्त(inode->i_link);
	मुक्त_inode_nonrcu(inode);
पूर्ण

अटल स्थिर काष्ठा super_operations aafs_super_ops = अणु
	.statfs = simple_statfs,
	.मुक्त_inode = aafs_मुक्त_inode,
	.show_path = aafs_show_path,
पूर्ण;

अटल पूर्णांक apparmorfs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	अटल काष्ठा tree_descr files[] = अणु अणु""पूर्ण पूर्ण;
	पूर्णांक error;

	error = simple_fill_super(sb, AAFS_MAGIC, files);
	अगर (error)
		वापस error;
	sb->s_op = &aafs_super_ops;

	वापस 0;
पूर्ण

अटल पूर्णांक apparmorfs_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_single(fc, apparmorfs_fill_super);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations apparmorfs_context_ops = अणु
	.get_tree	= apparmorfs_get_tree,
पूर्ण;

अटल पूर्णांक apparmorfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &apparmorfs_context_ops;
	वापस 0;
पूर्ण

अटल काष्ठा file_प्रणाली_type aafs_ops = अणु
	.owner = THIS_MODULE,
	.name = AAFS_NAME,
	.init_fs_context = apparmorfs_init_fs_context,
	.समाप्त_sb = समाप्त_anon_super,
पूर्ण;

/**
 * __aafs_setup_d_inode - basic inode setup क्रम apparmorfs
 * @dir: parent directory क्रम the dentry
 * @dentry: dentry we are seting the inode up क्रम
 * @mode: permissions the file should have
 * @data: data to store on inode.i_निजी, available in खोलो()
 * @link: अगर symlink, symlink target string
 * @fops: काष्ठा file_operations that should be used
 * @iops: काष्ठा of inode_operations that should be used
 */
अटल पूर्णांक __aafs_setup_d_inode(काष्ठा inode *dir, काष्ठा dentry *dentry,
			       umode_t mode, व्योम *data, अक्षर *link,
			       स्थिर काष्ठा file_operations *fops,
			       स्थिर काष्ठा inode_operations *iops)
अणु
	काष्ठा inode *inode = new_inode(dir->i_sb);

	AA_BUG(!dir);
	AA_BUG(!dentry);

	अगर (!inode)
		वापस -ENOMEM;

	inode->i_ino = get_next_ino();
	inode->i_mode = mode;
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	inode->i_निजी = data;
	अगर (S_ISसूची(mode)) अणु
		inode->i_op = iops ? iops : &simple_dir_inode_operations;
		inode->i_fop = &simple_dir_operations;
		inc_nlink(inode);
		inc_nlink(dir);
	पूर्ण अन्यथा अगर (S_ISLNK(mode)) अणु
		inode->i_op = iops ? iops : &simple_symlink_inode_operations;
		inode->i_link = link;
	पूर्ण अन्यथा अणु
		inode->i_fop = fops;
	पूर्ण
	d_instantiate(dentry, inode);
	dget(dentry);

	वापस 0;
पूर्ण

/**
 * aafs_create - create a dentry in the apparmorfs fileप्रणाली
 *
 * @name: name of dentry to create
 * @mode: permissions the file should have
 * @parent: parent directory क्रम this dentry
 * @data: data to store on inode.i_निजी, available in खोलो()
 * @link: अगर symlink, symlink target string
 * @fops: काष्ठा file_operations that should be used क्रम
 * @iops: काष्ठा of inode_operations that should be used
 *
 * This is the basic "create a xxx" function क्रम apparmorfs.
 *
 * Returns a poपूर्णांकer to a dentry अगर it succeeds, that must be मुक्त with
 * aafs_हटाओ(). Will वापस ERR_PTR on failure.
 */
अटल काष्ठा dentry *aafs_create(स्थिर अक्षर *name, umode_t mode,
				  काष्ठा dentry *parent, व्योम *data, व्योम *link,
				  स्थिर काष्ठा file_operations *fops,
				  स्थिर काष्ठा inode_operations *iops)
अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *dir;
	पूर्णांक error;

	AA_BUG(!name);
	AA_BUG(!parent);

	अगर (!(mode & S_IFMT))
		mode = (mode & S_IALLUGO) | S_IFREG;

	error = simple_pin_fs(&aafs_ops, &aafs_mnt, &aafs_count);
	अगर (error)
		वापस ERR_PTR(error);

	dir = d_inode(parent);

	inode_lock(dir);
	dentry = lookup_one_len(name, parent, म_माप(name));
	अगर (IS_ERR(dentry)) अणु
		error = PTR_ERR(dentry);
		जाओ fail_lock;
	पूर्ण

	अगर (d_really_is_positive(dentry)) अणु
		error = -EEXIST;
		जाओ fail_dentry;
	पूर्ण

	error = __aafs_setup_d_inode(dir, dentry, mode, data, link, fops, iops);
	अगर (error)
		जाओ fail_dentry;
	inode_unlock(dir);

	वापस dentry;

fail_dentry:
	dput(dentry);

fail_lock:
	inode_unlock(dir);
	simple_release_fs(&aafs_mnt, &aafs_count);

	वापस ERR_PTR(error);
पूर्ण

/**
 * aafs_create_file - create a file in the apparmorfs fileप्रणाली
 *
 * @name: name of dentry to create
 * @mode: permissions the file should have
 * @parent: parent directory क्रम this dentry
 * @data: data to store on inode.i_निजी, available in खोलो()
 * @fops: काष्ठा file_operations that should be used क्रम
 *
 * see aafs_create
 */
अटल काष्ठा dentry *aafs_create_file(स्थिर अक्षर *name, umode_t mode,
				       काष्ठा dentry *parent, व्योम *data,
				       स्थिर काष्ठा file_operations *fops)
अणु
	वापस aafs_create(name, mode, parent, data, शून्य, fops, शून्य);
पूर्ण

/**
 * aafs_create_dir - create a directory in the apparmorfs fileप्रणाली
 *
 * @name: name of dentry to create
 * @parent: parent directory क्रम this dentry
 *
 * see aafs_create
 */
अटल काष्ठा dentry *aafs_create_dir(स्थिर अक्षर *name, काष्ठा dentry *parent)
अणु
	वापस aafs_create(name, S_IFसूची | 0755, parent, शून्य, शून्य, शून्य,
			   शून्य);
पूर्ण

/**
 * aafs_हटाओ - हटाओs a file or directory from the apparmorfs fileप्रणाली
 *
 * @dentry: dentry of the file/directory/symlink to हटाओd.
 */
अटल व्योम aafs_हटाओ(काष्ठा dentry *dentry)
अणु
	काष्ठा inode *dir;

	अगर (!dentry || IS_ERR(dentry))
		वापस;

	dir = d_inode(dentry->d_parent);
	inode_lock(dir);
	अगर (simple_positive(dentry)) अणु
		अगर (d_is_dir(dentry))
			simple_सूची_हटाओ(dir, dentry);
		अन्यथा
			simple_unlink(dir, dentry);
		d_delete(dentry);
		dput(dentry);
	पूर्ण
	inode_unlock(dir);
	simple_release_fs(&aafs_mnt, &aafs_count);
पूर्ण


/*
 * aa_fs - policy load/replace/हटाओ
 */

/**
 * aa_simple_ग_लिखो_to_buffer - common routine क्रम getting policy from user
 * @userbuf: user buffer to copy data from  (NOT शून्य)
 * @alloc_size: size of user buffer (REQUIRES: @alloc_size >= @copy_size)
 * @copy_size: size of data to copy from user buffer
 * @pos: position ग_लिखो is at in the file (NOT शून्य)
 *
 * Returns: kernel buffer containing copy of user buffer data or an
 *          ERR_PTR on failure.
 */
अटल काष्ठा aa_loaddata *aa_simple_ग_लिखो_to_buffer(स्थिर अक्षर __user *userbuf,
						     माप_प्रकार alloc_size,
						     माप_प्रकार copy_size,
						     loff_t *pos)
अणु
	काष्ठा aa_loaddata *data;

	AA_BUG(copy_size > alloc_size);

	अगर (*pos != 0)
		/* only ग_लिखोs from pos 0, that is complete ग_लिखोs */
		वापस ERR_PTR(-ESPIPE);

	/* मुक्तd by caller to simple_ग_लिखो_to_buffer */
	data = aa_loaddata_alloc(alloc_size);
	अगर (IS_ERR(data))
		वापस data;

	data->size = copy_size;
	अगर (copy_from_user(data->data, userbuf, copy_size)) अणु
		kvमुक्त(data);
		वापस ERR_PTR(-EFAULT);
	पूर्ण

	वापस data;
पूर्ण

अटल sमाप_प्रकार policy_update(u32 mask, स्थिर अक्षर __user *buf, माप_प्रकार size,
			     loff_t *pos, काष्ठा aa_ns *ns)
अणु
	काष्ठा aa_loaddata *data;
	काष्ठा aa_label *label;
	sमाप_प्रकार error;

	label = begin_current_label_crit_section();

	/* high level check about policy management - fine grained in
	 * below after unpack
	 */
	error = aa_may_manage_policy(label, ns, mask);
	अगर (error)
		जाओ end_section;

	data = aa_simple_ग_लिखो_to_buffer(buf, size, size, pos);
	error = PTR_ERR(data);
	अगर (!IS_ERR(data)) अणु
		error = aa_replace_profiles(ns, label, mask, data);
		aa_put_loaddata(data);
	पूर्ण
end_section:
	end_current_label_crit_section(label);

	वापस error;
पूर्ण

/* .load file hook fn to load policy */
अटल sमाप_प्रकार profile_load(काष्ठा file *f, स्थिर अक्षर __user *buf, माप_प्रकार size,
			    loff_t *pos)
अणु
	काष्ठा aa_ns *ns = aa_get_ns(f->f_inode->i_निजी);
	पूर्णांक error = policy_update(AA_MAY_LOAD_POLICY, buf, size, pos, ns);

	aa_put_ns(ns);

	वापस error;
पूर्ण

अटल स्थिर काष्ठा file_operations aa_fs_profile_load = अणु
	.ग_लिखो = profile_load,
	.llseek = शेष_llseek,
पूर्ण;

/* .replace file hook fn to load and/or replace policy */
अटल sमाप_प्रकार profile_replace(काष्ठा file *f, स्थिर अक्षर __user *buf,
			       माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा aa_ns *ns = aa_get_ns(f->f_inode->i_निजी);
	पूर्णांक error = policy_update(AA_MAY_LOAD_POLICY | AA_MAY_REPLACE_POLICY,
				  buf, size, pos, ns);
	aa_put_ns(ns);

	वापस error;
पूर्ण

अटल स्थिर काष्ठा file_operations aa_fs_profile_replace = अणु
	.ग_लिखो = profile_replace,
	.llseek = शेष_llseek,
पूर्ण;

/* .हटाओ file hook fn to हटाओ loaded policy */
अटल sमाप_प्रकार profile_हटाओ(काष्ठा file *f, स्थिर अक्षर __user *buf,
			      माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा aa_loaddata *data;
	काष्ठा aa_label *label;
	sमाप_प्रकार error;
	काष्ठा aa_ns *ns = aa_get_ns(f->f_inode->i_निजी);

	label = begin_current_label_crit_section();
	/* high level check about policy management - fine grained in
	 * below after unpack
	 */
	error = aa_may_manage_policy(label, ns, AA_MAY_REMOVE_POLICY);
	अगर (error)
		जाओ out;

	/*
	 * aa_हटाओ_profile needs a null terminated string so 1 extra
	 * byte is allocated and the copied data is null terminated.
	 */
	data = aa_simple_ग_लिखो_to_buffer(buf, size + 1, size, pos);

	error = PTR_ERR(data);
	अगर (!IS_ERR(data)) अणु
		data->data[size] = 0;
		error = aa_हटाओ_profiles(ns, label, data->data, size);
		aa_put_loaddata(data);
	पूर्ण
 out:
	end_current_label_crit_section(label);
	aa_put_ns(ns);
	वापस error;
पूर्ण

अटल स्थिर काष्ठा file_operations aa_fs_profile_हटाओ = अणु
	.ग_लिखो = profile_हटाओ,
	.llseek = शेष_llseek,
पूर्ण;

काष्ठा aa_revision अणु
	काष्ठा aa_ns *ns;
	दीर्घ last_पढ़ो;
पूर्ण;

/* revision file hook fn क्रम policy loads */
अटल पूर्णांक ns_revision_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा aa_revision *rev = file->निजी_data;

	अगर (rev) अणु
		aa_put_ns(rev->ns);
		kमुक्त(rev);
	पूर्ण

	वापस 0;
पूर्ण

अटल sमाप_प्रकार ns_revision_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				माप_प्रकार size, loff_t *ppos)
अणु
	काष्ठा aa_revision *rev = file->निजी_data;
	अक्षर buffer[32];
	दीर्घ last_पढ़ो;
	पूर्णांक avail;

	mutex_lock_nested(&rev->ns->lock, rev->ns->level);
	last_पढ़ो = rev->last_पढ़ो;
	अगर (last_पढ़ो == rev->ns->revision) अणु
		mutex_unlock(&rev->ns->lock);
		अगर (file->f_flags & O_NONBLOCK)
			वापस -EAGAIN;
		अगर (रुको_event_पूर्णांकerruptible(rev->ns->रुको,
					     last_पढ़ो !=
					     READ_ONCE(rev->ns->revision)))
			वापस -ERESTARTSYS;
		mutex_lock_nested(&rev->ns->lock, rev->ns->level);
	पूर्ण

	avail = प्र_लिखो(buffer, "%ld\n", rev->ns->revision);
	अगर (*ppos + size > avail) अणु
		rev->last_पढ़ो = rev->ns->revision;
		*ppos = 0;
	पूर्ण
	mutex_unlock(&rev->ns->lock);

	वापस simple_पढ़ो_from_buffer(buf, size, ppos, buffer, avail);
पूर्ण

अटल पूर्णांक ns_revision_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा aa_revision *rev = kzalloc(माप(*rev), GFP_KERNEL);

	अगर (!rev)
		वापस -ENOMEM;

	rev->ns = aa_get_ns(inode->i_निजी);
	अगर (!rev->ns)
		rev->ns = aa_get_current_ns();
	file->निजी_data = rev;

	वापस 0;
पूर्ण

अटल __poll_t ns_revision_poll(काष्ठा file *file, poll_table *pt)
अणु
	काष्ठा aa_revision *rev = file->निजी_data;
	__poll_t mask = 0;

	अगर (rev) अणु
		mutex_lock_nested(&rev->ns->lock, rev->ns->level);
		poll_रुको(file, &rev->ns->रुको, pt);
		अगर (rev->last_पढ़ो < rev->ns->revision)
			mask |= EPOLLIN | EPOLLRDNORM;
		mutex_unlock(&rev->ns->lock);
	पूर्ण

	वापस mask;
पूर्ण

व्योम __aa_bump_ns_revision(काष्ठा aa_ns *ns)
अणु
	WRITE_ONCE(ns->revision, READ_ONCE(ns->revision) + 1);
	wake_up_पूर्णांकerruptible(&ns->रुको);
पूर्ण

अटल स्थिर काष्ठा file_operations aa_fs_ns_revision_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= ns_revision_खोलो,
	.poll		= ns_revision_poll,
	.पढ़ो		= ns_revision_पढ़ो,
	.llseek		= generic_file_llseek,
	.release	= ns_revision_release,
पूर्ण;

अटल व्योम profile_query_cb(काष्ठा aa_profile *profile, काष्ठा aa_perms *perms,
			     स्थिर अक्षर *match_str, माप_प्रकार match_len)
अणु
	काष्ठा aa_perms पंचांगp = अणु पूर्ण;
	काष्ठा aa_dfa *dfa;
	अचिन्हित पूर्णांक state = 0;

	अगर (profile_unconfined(profile))
		वापस;
	अगर (profile->file.dfa && *match_str == AA_CLASS_खाता) अणु
		dfa = profile->file.dfa;
		state = aa_dfa_match_len(dfa, profile->file.start,
					 match_str + 1, match_len - 1);
		अगर (state) अणु
			काष्ठा path_cond cond = अणु पूर्ण;

			पंचांगp = aa_compute_fperms(dfa, state, &cond);
		पूर्ण
	पूर्ण अन्यथा अगर (profile->policy.dfa) अणु
		अगर (!PROखाता_MEDIATES(profile, *match_str))
			वापस;	/* no change to current perms */
		dfa = profile->policy.dfa;
		state = aa_dfa_match_len(dfa, profile->policy.start[0],
					 match_str, match_len);
		अगर (state)
			aa_compute_perms(dfa, state, &पंचांगp);
	पूर्ण
	aa_apply_modes_to_perms(profile, &पंचांगp);
	aa_perms_accum_raw(perms, &पंचांगp);
पूर्ण


/**
 * query_data - queries a policy and ग_लिखोs its data to buf
 * @buf: the resulting data is stored here (NOT शून्य)
 * @buf_len: size of buf
 * @query: query string used to retrieve data
 * @query_len: size of query including second NUL byte
 *
 * The buffers poपूर्णांकed to by buf and query may overlap. The query buffer is
 * parsed beक्रमe buf is written to.
 *
 * The query should look like "<LABEL>\0<KEY>\0", where <LABEL> is the name of
 * the security confinement context and <KEY> is the name of the data to
 * retrieve. <LABEL> and <KEY> must not be NUL-terminated.
 *
 * Don't expect the contents of buf to be preserved on failure.
 *
 * Returns: number of अक्षरacters written to buf or -त्रुटि_सं on failure
 */
अटल sमाप_प्रकार query_data(अक्षर *buf, माप_प्रकार buf_len,
			  अक्षर *query, माप_प्रकार query_len)
अणु
	अक्षर *out;
	स्थिर अक्षर *key;
	काष्ठा label_it i;
	काष्ठा aa_label *label, *curr;
	काष्ठा aa_profile *profile;
	काष्ठा aa_data *data;
	u32 bytes, blocks;
	__le32 outle32;

	अगर (!query_len)
		वापस -EINVAL; /* need a query */

	key = query + strnlen(query, query_len) + 1;
	अगर (key + 1 >= query + query_len)
		वापस -EINVAL; /* not enough space क्रम a non-empty key */
	अगर (key + strnlen(key, query + query_len - key) >= query + query_len)
		वापस -EINVAL; /* must end with NUL */

	अगर (buf_len < माप(bytes) + माप(blocks))
		वापस -EINVAL; /* not enough space */

	curr = begin_current_label_crit_section();
	label = aa_label_parse(curr, query, GFP_KERNEL, false, false);
	end_current_label_crit_section(curr);
	अगर (IS_ERR(label))
		वापस PTR_ERR(label);

	/* We are going to leave space क्रम two numbers. The first is the total
	 * number of bytes we are writing after the first number. This is so
	 * users can पढ़ो the full output without पुनः_स्मृतिation.
	 *
	 * The second number is the number of data blocks we're writing. An
	 * application might be confined by multiple policies having data in
	 * the same key.
	 */
	स_रखो(buf, 0, माप(bytes) + माप(blocks));
	out = buf + माप(bytes) + माप(blocks);

	blocks = 0;
	label_क्रम_each_confined(i, label, profile) अणु
		अगर (!profile->data)
			जारी;

		data = rhashtable_lookup_fast(profile->data, &key,
					      profile->data->p);

		अगर (data) अणु
			अगर (out + माप(outle32) + data->size > buf +
			    buf_len) अणु
				aa_put_label(label);
				वापस -EINVAL; /* not enough space */
			पूर्ण
			outle32 = __cpu_to_le32(data->size);
			स_नकल(out, &outle32, माप(outle32));
			out += माप(outle32);
			स_नकल(out, data->data, data->size);
			out += data->size;
			blocks++;
		पूर्ण
	पूर्ण
	aa_put_label(label);

	outle32 = __cpu_to_le32(out - buf - माप(bytes));
	स_नकल(buf, &outle32, माप(outle32));
	outle32 = __cpu_to_le32(blocks);
	स_नकल(buf + माप(bytes), &outle32, माप(outle32));

	वापस out - buf;
पूर्ण

/**
 * query_label - queries a label and ग_लिखोs permissions to buf
 * @buf: the resulting permissions string is stored here (NOT शून्य)
 * @buf_len: size of buf
 * @query: binary query string to match against the dfa
 * @query_len: size of query
 * @view_only: only compute क्रम querier's view
 *
 * The buffers poपूर्णांकed to by buf and query may overlap. The query buffer is
 * parsed beक्रमe buf is written to.
 *
 * The query should look like "LABEL_NAME\0DFA_STRING" where LABEL_NAME is
 * the name of the label, in the current namespace, that is to be queried and
 * DFA_STRING is a binary string to match against the label(s)'s DFA.
 *
 * LABEL_NAME must be NUL terminated. DFA_STRING may contain NUL अक्षरacters
 * but must *not* be NUL terminated.
 *
 * Returns: number of अक्षरacters written to buf or -त्रुटि_सं on failure
 */
अटल sमाप_प्रकार query_label(अक्षर *buf, माप_प्रकार buf_len,
			   अक्षर *query, माप_प्रकार query_len, bool view_only)
अणु
	काष्ठा aa_profile *profile;
	काष्ठा aa_label *label, *curr;
	अक्षर *label_name, *match_str;
	माप_प्रकार label_name_len, match_len;
	काष्ठा aa_perms perms;
	काष्ठा label_it i;

	अगर (!query_len)
		वापस -EINVAL;

	label_name = query;
	label_name_len = strnlen(query, query_len);
	अगर (!label_name_len || label_name_len == query_len)
		वापस -EINVAL;

	/**
	 * The extra byte is to account क्रम the null byte between the
	 * profile name and dfa string. profile_name_len is greater
	 * than zero and less than query_len, so a byte can be safely
	 * added or subtracted.
	 */
	match_str = label_name + label_name_len + 1;
	match_len = query_len - label_name_len - 1;

	curr = begin_current_label_crit_section();
	label = aa_label_parse(curr, label_name, GFP_KERNEL, false, false);
	end_current_label_crit_section(curr);
	अगर (IS_ERR(label))
		वापस PTR_ERR(label);

	perms = allperms;
	अगर (view_only) अणु
		label_क्रम_each_in_ns(i, labels_ns(label), label, profile) अणु
			profile_query_cb(profile, &perms, match_str, match_len);
		पूर्ण
	पूर्ण अन्यथा अणु
		label_क्रम_each(i, label, profile) अणु
			profile_query_cb(profile, &perms, match_str, match_len);
		पूर्ण
	पूर्ण
	aa_put_label(label);

	वापस scnम_लिखो(buf, buf_len,
		      "allow 0x%08x\ndeny 0x%08x\naudit 0x%08x\nquiet 0x%08x\n",
		      perms.allow, perms.deny, perms.audit, perms.quiet);
पूर्ण

/*
 * Transaction based IO.
 * The file expects a ग_लिखो which triggers the transaction, and then
 * possibly a पढ़ो(s) which collects the result - which is stored in a
 * file-local buffer. Once a new ग_लिखो is perक्रमmed, a new set of results
 * are stored in the file-local buffer.
 */
काष्ठा multi_transaction अणु
	काष्ठा kref count;
	sमाप_प्रकार size;
	अक्षर data[];
पूर्ण;

#घोषणा MULTI_TRANSACTION_LIMIT (PAGE_SIZE - माप(काष्ठा multi_transaction))
/* TODO: replace with per file lock */
अटल DEFINE_SPINLOCK(multi_transaction_lock);

अटल व्योम multi_transaction_kref(काष्ठा kref *kref)
अणु
	काष्ठा multi_transaction *t;

	t = container_of(kref, काष्ठा multi_transaction, count);
	मुक्त_page((अचिन्हित दीर्घ) t);
पूर्ण

अटल काष्ठा multi_transaction *
get_multi_transaction(काष्ठा multi_transaction *t)
अणु
	अगर  (t)
		kref_get(&(t->count));

	वापस t;
पूर्ण

अटल व्योम put_multi_transaction(काष्ठा multi_transaction *t)
अणु
	अगर (t)
		kref_put(&(t->count), multi_transaction_kref);
पूर्ण

/* करोes not increment @new's count */
अटल व्योम multi_transaction_set(काष्ठा file *file,
				  काष्ठा multi_transaction *new, माप_प्रकार n)
अणु
	काष्ठा multi_transaction *old;

	AA_BUG(n > MULTI_TRANSACTION_LIMIT);

	new->size = n;
	spin_lock(&multi_transaction_lock);
	old = (काष्ठा multi_transaction *) file->निजी_data;
	file->निजी_data = new;
	spin_unlock(&multi_transaction_lock);
	put_multi_transaction(old);
पूर्ण

अटल काष्ठा multi_transaction *multi_transaction_new(काष्ठा file *file,
						       स्थिर अक्षर __user *buf,
						       माप_प्रकार size)
अणु
	काष्ठा multi_transaction *t;

	अगर (size > MULTI_TRANSACTION_LIMIT - 1)
		वापस ERR_PTR(-EFBIG);

	t = (काष्ठा multi_transaction *)get_zeroed_page(GFP_KERNEL);
	अगर (!t)
		वापस ERR_PTR(-ENOMEM);
	kref_init(&t->count);
	अगर (copy_from_user(t->data, buf, size))
		वापस ERR_PTR(-EFAULT);

	वापस t;
पूर्ण

अटल sमाप_प्रकार multi_transaction_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				       माप_प्रकार size, loff_t *pos)
अणु
	काष्ठा multi_transaction *t;
	sमाप_प्रकार ret;

	spin_lock(&multi_transaction_lock);
	t = get_multi_transaction(file->निजी_data);
	spin_unlock(&multi_transaction_lock);
	अगर (!t)
		वापस 0;

	ret = simple_पढ़ो_from_buffer(buf, size, pos, t->data, t->size);
	put_multi_transaction(t);

	वापस ret;
पूर्ण

अटल पूर्णांक multi_transaction_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	put_multi_transaction(file->निजी_data);

	वापस 0;
पूर्ण

#घोषणा QUERY_CMD_LABEL		"label\0"
#घोषणा QUERY_CMD_LABEL_LEN	6
#घोषणा QUERY_CMD_PROखाता	"profile\0"
#घोषणा QUERY_CMD_PROखाता_LEN	8
#घोषणा QUERY_CMD_LABELALL	"labelall\0"
#घोषणा QUERY_CMD_LABELALL_LEN	9
#घोषणा QUERY_CMD_DATA		"data\0"
#घोषणा QUERY_CMD_DATA_LEN	5

/**
 * aa_ग_लिखो_access - generic permissions and data query
 * @file: poपूर्णांकer to खोलो apparmorfs/access file
 * @ubuf: user buffer containing the complete query string (NOT शून्य)
 * @count: size of ubuf
 * @ppos: position in the file (MUST BE ZERO)
 *
 * Allows क्रम one permissions or data query per खोलो(), ग_लिखो(), and पढ़ो()
 * sequence. The only queries currently supported are label-based queries क्रम
 * permissions or data.
 *
 * For permissions queries, ubuf must begin with "label\0", followed by the
 * profile query specअगरic क्रमmat described in the query_label() function
 * करोcumentation.
 *
 * For data queries, ubuf must have the क्रमm "data\0<LABEL>\0<KEY>\0", where
 * <LABEL> is the name of the security confinement context and <KEY> is the
 * name of the data to retrieve.
 *
 * Returns: number of bytes written or -त्रुटि_सं on failure
 */
अटल sमाप_प्रकार aa_ग_लिखो_access(काष्ठा file *file, स्थिर अक्षर __user *ubuf,
			       माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा multi_transaction *t;
	sमाप_प्रकार len;

	अगर (*ppos)
		वापस -ESPIPE;

	t = multi_transaction_new(file, ubuf, count);
	अगर (IS_ERR(t))
		वापस PTR_ERR(t);

	अगर (count > QUERY_CMD_PROखाता_LEN &&
	    !स_भेद(t->data, QUERY_CMD_PROखाता, QUERY_CMD_PROखाता_LEN)) अणु
		len = query_label(t->data, MULTI_TRANSACTION_LIMIT,
				  t->data + QUERY_CMD_PROखाता_LEN,
				  count - QUERY_CMD_PROखाता_LEN, true);
	पूर्ण अन्यथा अगर (count > QUERY_CMD_LABEL_LEN &&
		   !स_भेद(t->data, QUERY_CMD_LABEL, QUERY_CMD_LABEL_LEN)) अणु
		len = query_label(t->data, MULTI_TRANSACTION_LIMIT,
				  t->data + QUERY_CMD_LABEL_LEN,
				  count - QUERY_CMD_LABEL_LEN, true);
	पूर्ण अन्यथा अगर (count > QUERY_CMD_LABELALL_LEN &&
		   !स_भेद(t->data, QUERY_CMD_LABELALL,
			   QUERY_CMD_LABELALL_LEN)) अणु
		len = query_label(t->data, MULTI_TRANSACTION_LIMIT,
				  t->data + QUERY_CMD_LABELALL_LEN,
				  count - QUERY_CMD_LABELALL_LEN, false);
	पूर्ण अन्यथा अगर (count > QUERY_CMD_DATA_LEN &&
		   !स_भेद(t->data, QUERY_CMD_DATA, QUERY_CMD_DATA_LEN)) अणु
		len = query_data(t->data, MULTI_TRANSACTION_LIMIT,
				 t->data + QUERY_CMD_DATA_LEN,
				 count - QUERY_CMD_DATA_LEN);
	पूर्ण अन्यथा
		len = -EINVAL;

	अगर (len < 0) अणु
		put_multi_transaction(t);
		वापस len;
	पूर्ण

	multi_transaction_set(file, t, len);

	वापस count;
पूर्ण

अटल स्थिर काष्ठा file_operations aa_sfs_access = अणु
	.ग_लिखो		= aa_ग_लिखो_access,
	.पढ़ो		= multi_transaction_पढ़ो,
	.release	= multi_transaction_release,
	.llseek		= generic_file_llseek,
पूर्ण;

अटल पूर्णांक aa_sfs_seq_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा aa_sfs_entry *fs_file = seq->निजी;

	अगर (!fs_file)
		वापस 0;

	चयन (fs_file->v_type) अणु
	हाल AA_SFS_TYPE_BOOLEAN:
		seq_म_लिखो(seq, "%s\n", fs_file->v.boolean ? "yes" : "no");
		अवरोध;
	हाल AA_SFS_TYPE_STRING:
		seq_म_लिखो(seq, "%s\n", fs_file->v.string);
		अवरोध;
	हाल AA_SFS_TYPE_U64:
		seq_म_लिखो(seq, "%#08lx\n", fs_file->v.u64);
		अवरोध;
	शेष:
		/* Ignore unpritable entry types. */
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aa_sfs_seq_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, aa_sfs_seq_show, inode->i_निजी);
पूर्ण

स्थिर काष्ठा file_operations aa_sfs_seq_file_ops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= aa_sfs_seq_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

/*
 * profile based file operations
 *     policy/profiles/XXXX/profiles/ *
 */

#घोषणा SEQ_PROखाता_FOPS(NAME)						      \
अटल पूर्णांक seq_profile_ ##NAME ##_खोलो(काष्ठा inode *inode, काष्ठा file *file)\
अणु									      \
	वापस seq_profile_खोलो(inode, file, seq_profile_ ##NAME ##_show);    \
पूर्ण									      \
									      \
अटल स्थिर काष्ठा file_operations seq_profile_ ##NAME ##_fops = अणु	      \
	.owner		= THIS_MODULE,					      \
	.खोलो		= seq_profile_ ##NAME ##_खोलो,			      \
	.पढ़ो		= seq_पढ़ो,					      \
	.llseek		= seq_lseek,					      \
	.release	= seq_profile_release,				      \
पूर्ण									      \

अटल पूर्णांक seq_profile_खोलो(काष्ठा inode *inode, काष्ठा file *file,
			    पूर्णांक (*show)(काष्ठा seq_file *, व्योम *))
अणु
	काष्ठा aa_proxy *proxy = aa_get_proxy(inode->i_निजी);
	पूर्णांक error = single_खोलो(file, show, proxy);

	अगर (error) अणु
		file->निजी_data = शून्य;
		aa_put_proxy(proxy);
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक seq_profile_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = (काष्ठा seq_file *) file->निजी_data;
	अगर (seq)
		aa_put_proxy(seq->निजी);
	वापस single_release(inode, file);
पूर्ण

अटल पूर्णांक seq_profile_name_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा aa_proxy *proxy = seq->निजी;
	काष्ठा aa_label *label = aa_get_label_rcu(&proxy->label);
	काष्ठा aa_profile *profile = labels_profile(label);
	seq_म_लिखो(seq, "%s\n", profile->base.name);
	aa_put_label(label);

	वापस 0;
पूर्ण

अटल पूर्णांक seq_profile_mode_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा aa_proxy *proxy = seq->निजी;
	काष्ठा aa_label *label = aa_get_label_rcu(&proxy->label);
	काष्ठा aa_profile *profile = labels_profile(label);
	seq_म_लिखो(seq, "%s\n", aa_profile_mode_names[profile->mode]);
	aa_put_label(label);

	वापस 0;
पूर्ण

अटल पूर्णांक seq_profile_attach_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा aa_proxy *proxy = seq->निजी;
	काष्ठा aa_label *label = aa_get_label_rcu(&proxy->label);
	काष्ठा aa_profile *profile = labels_profile(label);
	अगर (profile->attach)
		seq_म_लिखो(seq, "%s\n", profile->attach);
	अन्यथा अगर (profile->xmatch)
		seq_माला_दो(seq, "<unknown>\n");
	अन्यथा
		seq_म_लिखो(seq, "%s\n", profile->base.name);
	aa_put_label(label);

	वापस 0;
पूर्ण

अटल पूर्णांक seq_profile_hash_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा aa_proxy *proxy = seq->निजी;
	काष्ठा aa_label *label = aa_get_label_rcu(&proxy->label);
	काष्ठा aa_profile *profile = labels_profile(label);
	अचिन्हित पूर्णांक i, size = aa_hash_size();

	अगर (profile->hash) अणु
		क्रम (i = 0; i < size; i++)
			seq_म_लिखो(seq, "%.2x", profile->hash[i]);
		seq_अ_दो(seq, '\n');
	पूर्ण
	aa_put_label(label);

	वापस 0;
पूर्ण

SEQ_PROखाता_FOPS(name);
SEQ_PROखाता_FOPS(mode);
SEQ_PROखाता_FOPS(attach);
SEQ_PROखाता_FOPS(hash);

/*
 * namespace based files
 *     several root files and
 *     policy/ *
 */

#घोषणा SEQ_NS_FOPS(NAME)						      \
अटल पूर्णांक seq_ns_ ##NAME ##_खोलो(काष्ठा inode *inode, काष्ठा file *file)     \
अणु									      \
	वापस single_खोलो(file, seq_ns_ ##NAME ##_show, inode->i_निजी);   \
पूर्ण									      \
									      \
अटल स्थिर काष्ठा file_operations seq_ns_ ##NAME ##_fops = अणु	      \
	.owner		= THIS_MODULE,					      \
	.खोलो		= seq_ns_ ##NAME ##_खोलो,			      \
	.पढ़ो		= seq_पढ़ो,					      \
	.llseek		= seq_lseek,					      \
	.release	= single_release,				      \
पूर्ण									      \

अटल पूर्णांक seq_ns_stacked_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा aa_label *label;

	label = begin_current_label_crit_section();
	seq_म_लिखो(seq, "%s\n", label->size > 1 ? "yes" : "no");
	end_current_label_crit_section(label);

	वापस 0;
पूर्ण

अटल पूर्णांक seq_ns_nsstacked_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा aa_label *label;
	काष्ठा aa_profile *profile;
	काष्ठा label_it it;
	पूर्णांक count = 1;

	label = begin_current_label_crit_section();

	अगर (label->size > 1) अणु
		label_क्रम_each(it, label, profile)
			अगर (profile->ns != labels_ns(label)) अणु
				count++;
				अवरोध;
			पूर्ण
	पूर्ण

	seq_म_लिखो(seq, "%s\n", count > 1 ? "yes" : "no");
	end_current_label_crit_section(label);

	वापस 0;
पूर्ण

अटल पूर्णांक seq_ns_level_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा aa_label *label;

	label = begin_current_label_crit_section();
	seq_म_लिखो(seq, "%d\n", labels_ns(label)->level);
	end_current_label_crit_section(label);

	वापस 0;
पूर्ण

अटल पूर्णांक seq_ns_name_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा aa_label *label = begin_current_label_crit_section();
	seq_म_लिखो(seq, "%s\n", labels_ns(label)->base.name);
	end_current_label_crit_section(label);

	वापस 0;
पूर्ण

SEQ_NS_FOPS(stacked);
SEQ_NS_FOPS(nsstacked);
SEQ_NS_FOPS(level);
SEQ_NS_FOPS(name);


/* policy/raw_data/ * file ops */

#घोषणा SEQ_RAWDATA_FOPS(NAME)						      \
अटल पूर्णांक seq_rawdata_ ##NAME ##_खोलो(काष्ठा inode *inode, काष्ठा file *file)\
अणु									      \
	वापस seq_rawdata_खोलो(inode, file, seq_rawdata_ ##NAME ##_show);    \
पूर्ण									      \
									      \
अटल स्थिर काष्ठा file_operations seq_rawdata_ ##NAME ##_fops = अणु	      \
	.owner		= THIS_MODULE,					      \
	.खोलो		= seq_rawdata_ ##NAME ##_खोलो,			      \
	.पढ़ो		= seq_पढ़ो,					      \
	.llseek		= seq_lseek,					      \
	.release	= seq_rawdata_release,				      \
पूर्ण									      \

अटल पूर्णांक seq_rawdata_खोलो(काष्ठा inode *inode, काष्ठा file *file,
			    पूर्णांक (*show)(काष्ठा seq_file *, व्योम *))
अणु
	काष्ठा aa_loaddata *data = __aa_get_loaddata(inode->i_निजी);
	पूर्णांक error;

	अगर (!data)
		/* lost race this ent is being reaped */
		वापस -ENOENT;

	error = single_खोलो(file, show, data);
	अगर (error) अणु
		AA_BUG(file->निजी_data &&
		       ((काष्ठा seq_file *)file->निजी_data)->निजी);
		aa_put_loaddata(data);
	पूर्ण

	वापस error;
पूर्ण

अटल पूर्णांक seq_rawdata_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा seq_file *seq = (काष्ठा seq_file *) file->निजी_data;

	अगर (seq)
		aa_put_loaddata(seq->निजी);

	वापस single_release(inode, file);
पूर्ण

अटल पूर्णांक seq_rawdata_abi_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा aa_loaddata *data = seq->निजी;

	seq_म_लिखो(seq, "v%d\n", data->abi);

	वापस 0;
पूर्ण

अटल पूर्णांक seq_rawdata_revision_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा aa_loaddata *data = seq->निजी;

	seq_म_लिखो(seq, "%ld\n", data->revision);

	वापस 0;
पूर्ण

अटल पूर्णांक seq_rawdata_hash_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा aa_loaddata *data = seq->निजी;
	अचिन्हित पूर्णांक i, size = aa_hash_size();

	अगर (data->hash) अणु
		क्रम (i = 0; i < size; i++)
			seq_म_लिखो(seq, "%.2x", data->hash[i]);
		seq_अ_दो(seq, '\n');
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक seq_rawdata_compressed_size_show(काष्ठा seq_file *seq, व्योम *v)
अणु
	काष्ठा aa_loaddata *data = seq->निजी;

	seq_म_लिखो(seq, "%zu\n", data->compressed_size);

	वापस 0;
पूर्ण

SEQ_RAWDATA_FOPS(abi);
SEQ_RAWDATA_FOPS(revision);
SEQ_RAWDATA_FOPS(hash);
SEQ_RAWDATA_FOPS(compressed_size);

अटल पूर्णांक deflate_decompress(अक्षर *src, माप_प्रकार slen, अक्षर *dst, माप_प्रकार dlen)
अणु
	पूर्णांक error;
	काष्ठा z_stream_s strm;

	अगर (aa_g_rawdata_compression_level == 0) अणु
		अगर (dlen < slen)
			वापस -EINVAL;
		स_नकल(dst, src, slen);
		वापस 0;
	पूर्ण

	स_रखो(&strm, 0, माप(strm));

	strm.workspace = kvzalloc(zlib_inflate_workspacesize(), GFP_KERNEL);
	अगर (!strm.workspace)
		वापस -ENOMEM;

	strm.next_in = src;
	strm.avail_in = slen;

	error = zlib_inflateInit(&strm);
	अगर (error != Z_OK) अणु
		error = -ENOMEM;
		जाओ fail_inflate_init;
	पूर्ण

	strm.next_out = dst;
	strm.avail_out = dlen;

	error = zlib_inflate(&strm, Z_FINISH);
	अगर (error != Z_STREAM_END)
		error = -EINVAL;
	अन्यथा
		error = 0;

	zlib_inflateEnd(&strm);
fail_inflate_init:
	kvमुक्त(strm.workspace);
	वापस error;
पूर्ण

अटल sमाप_प्रकार rawdata_पढ़ो(काष्ठा file *file, अक्षर __user *buf, माप_प्रकार size,
			    loff_t *ppos)
अणु
	काष्ठा rawdata_f_data *निजी = file->निजी_data;

	वापस simple_पढ़ो_from_buffer(buf, size, ppos,
				       RAWDATA_F_DATA_BUF(निजी),
				       निजी->loaddata->size);
पूर्ण

अटल पूर्णांक rawdata_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	rawdata_f_data_मुक्त(file->निजी_data);

	वापस 0;
पूर्ण

अटल पूर्णांक rawdata_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	पूर्णांक error;
	काष्ठा aa_loaddata *loaddata;
	काष्ठा rawdata_f_data *निजी;

	अगर (!policy_view_capable(शून्य))
		वापस -EACCES;

	loaddata = __aa_get_loaddata(inode->i_निजी);
	अगर (!loaddata)
		/* lost race: this entry is being reaped */
		वापस -ENOENT;

	निजी = rawdata_f_data_alloc(loaddata->size);
	अगर (IS_ERR(निजी)) अणु
		error = PTR_ERR(निजी);
		जाओ fail_निजी_alloc;
	पूर्ण

	निजी->loaddata = loaddata;

	error = deflate_decompress(loaddata->data, loaddata->compressed_size,
				   RAWDATA_F_DATA_BUF(निजी),
				   loaddata->size);
	अगर (error)
		जाओ fail_decompress;

	file->निजी_data = निजी;
	वापस 0;

fail_decompress:
	rawdata_f_data_मुक्त(निजी);
	वापस error;

fail_निजी_alloc:
	aa_put_loaddata(loaddata);
	वापस error;
पूर्ण

अटल स्थिर काष्ठा file_operations rawdata_fops = अणु
	.खोलो = rawdata_खोलो,
	.पढ़ो = rawdata_पढ़ो,
	.llseek = generic_file_llseek,
	.release = rawdata_release,
पूर्ण;

अटल व्योम हटाओ_rawdata_dents(काष्ठा aa_loaddata *rawdata)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < AAFS_LOADDATA_NDENTS; i++) अणु
		अगर (!IS_ERR_OR_शून्य(rawdata->dents[i])) अणु
			/* no refcounts on i_निजी */
			aafs_हटाओ(rawdata->dents[i]);
			rawdata->dents[i] = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

व्योम __aa_fs_हटाओ_rawdata(काष्ठा aa_loaddata *rawdata)
अणु
	AA_BUG(rawdata->ns && !mutex_is_locked(&rawdata->ns->lock));

	अगर (rawdata->ns) अणु
		हटाओ_rawdata_dents(rawdata);
		list_del_init(&rawdata->list);
		aa_put_ns(rawdata->ns);
		rawdata->ns = शून्य;
	पूर्ण
पूर्ण

पूर्णांक __aa_fs_create_rawdata(काष्ठा aa_ns *ns, काष्ठा aa_loaddata *rawdata)
अणु
	काष्ठा dentry *dent, *dir;

	AA_BUG(!ns);
	AA_BUG(!rawdata);
	AA_BUG(!mutex_is_locked(&ns->lock));
	AA_BUG(!ns_subdata_dir(ns));

	/*
	 * just use ns revision dir was originally created at. This is
	 * under ns->lock and अगर load is successful revision will be
	 * bumped and is guaranteed to be unique
	 */
	rawdata->name = kaप्र_लिखो(GFP_KERNEL, "%ld", ns->revision);
	अगर (!rawdata->name)
		वापस -ENOMEM;

	dir = aafs_create_dir(rawdata->name, ns_subdata_dir(ns));
	अगर (IS_ERR(dir))
		/* ->name मुक्तd when rawdata मुक्तd */
		वापस PTR_ERR(dir);
	rawdata->dents[AAFS_LOADDATA_सूची] = dir;

	dent = aafs_create_file("abi", S_IFREG | 0444, dir, rawdata,
				      &seq_rawdata_abi_fops);
	अगर (IS_ERR(dent))
		जाओ fail;
	rawdata->dents[AAFS_LOADDATA_ABI] = dent;

	dent = aafs_create_file("revision", S_IFREG | 0444, dir, rawdata,
				      &seq_rawdata_revision_fops);
	अगर (IS_ERR(dent))
		जाओ fail;
	rawdata->dents[AAFS_LOADDATA_REVISION] = dent;

	अगर (aa_g_hash_policy) अणु
		dent = aafs_create_file("sha1", S_IFREG | 0444, dir,
					      rawdata, &seq_rawdata_hash_fops);
		अगर (IS_ERR(dent))
			जाओ fail;
		rawdata->dents[AAFS_LOADDATA_HASH] = dent;
	पूर्ण

	dent = aafs_create_file("compressed_size", S_IFREG | 0444, dir,
				rawdata,
				&seq_rawdata_compressed_size_fops);
	अगर (IS_ERR(dent))
		जाओ fail;
	rawdata->dents[AAFS_LOADDATA_COMPRESSED_SIZE] = dent;

	dent = aafs_create_file("raw_data", S_IFREG | 0444,
				      dir, rawdata, &rawdata_fops);
	अगर (IS_ERR(dent))
		जाओ fail;
	rawdata->dents[AAFS_LOADDATA_DATA] = dent;
	d_inode(dent)->i_size = rawdata->size;

	rawdata->ns = aa_get_ns(ns);
	list_add(&rawdata->list, &ns->rawdata_list);
	/* no refcount on inode rawdata */

	वापस 0;

fail:
	हटाओ_rawdata_dents(rawdata);

	वापस PTR_ERR(dent);
पूर्ण

/** fns to setup dynamic per profile/namespace files **/

/**
 *
 * Requires: @profile->ns->lock held
 */
व्योम __aafs_profile_सूची_हटाओ(काष्ठा aa_profile *profile)
अणु
	काष्ठा aa_profile *child;
	पूर्णांक i;

	अगर (!profile)
		वापस;

	list_क्रम_each_entry(child, &profile->base.profiles, base.list)
		__aafs_profile_सूची_हटाओ(child);

	क्रम (i = AAFS_PROF_SIZखातापूर्ण - 1; i >= 0; --i) अणु
		काष्ठा aa_proxy *proxy;
		अगर (!profile->dents[i])
			जारी;

		proxy = d_inode(profile->dents[i])->i_निजी;
		aafs_हटाओ(profile->dents[i]);
		aa_put_proxy(proxy);
		profile->dents[i] = शून्य;
	पूर्ण
पूर्ण

/**
 *
 * Requires: @old->ns->lock held
 */
व्योम __aafs_profile_migrate_dents(काष्ठा aa_profile *old,
				  काष्ठा aa_profile *new)
अणु
	पूर्णांक i;

	AA_BUG(!old);
	AA_BUG(!new);
	AA_BUG(!mutex_is_locked(&profiles_ns(old)->lock));

	क्रम (i = 0; i < AAFS_PROF_SIZखातापूर्ण; i++) अणु
		new->dents[i] = old->dents[i];
		अगर (new->dents[i])
			new->dents[i]->d_inode->i_mसमय = current_समय(new->dents[i]->d_inode);
		old->dents[i] = शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा dentry *create_profile_file(काष्ठा dentry *dir, स्थिर अक्षर *name,
					  काष्ठा aa_profile *profile,
					  स्थिर काष्ठा file_operations *fops)
अणु
	काष्ठा aa_proxy *proxy = aa_get_proxy(profile->label.proxy);
	काष्ठा dentry *dent;

	dent = aafs_create_file(name, S_IFREG | 0444, dir, proxy, fops);
	अगर (IS_ERR(dent))
		aa_put_proxy(proxy);

	वापस dent;
पूर्ण

अटल पूर्णांक profile_depth(काष्ठा aa_profile *profile)
अणु
	पूर्णांक depth = 0;

	rcu_पढ़ो_lock();
	क्रम (depth = 0; profile; profile = rcu_access_poपूर्णांकer(profile->parent))
		depth++;
	rcu_पढ़ो_unlock();

	वापस depth;
पूर्ण

अटल अक्षर *gen_symlink_name(पूर्णांक depth, स्थिर अक्षर *स_नाम, स्थिर अक्षर *fname)
अणु
	अक्षर *buffer, *s;
	पूर्णांक error;
	पूर्णांक size = depth * 6 + म_माप(स_नाम) + म_माप(fname) + 11;

	s = buffer = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!buffer)
		वापस ERR_PTR(-ENOMEM);

	क्रम (; depth > 0; depth--) अणु
		म_नकल(s, "../../");
		s += 6;
		size -= 6;
	पूर्ण

	error = snम_लिखो(s, size, "raw_data/%s/%s", स_नाम, fname);
	अगर (error >= size || error < 0) अणु
		kमुक्त(buffer);
		वापस ERR_PTR(-ENAMETOOLONG);
	पूर्ण

	वापस buffer;
पूर्ण

अटल व्योम rawdata_link_cb(व्योम *arg)
अणु
	kमुक्त(arg);
पूर्ण

अटल स्थिर अक्षर *rawdata_get_link_base(काष्ठा dentry *dentry,
					 काष्ठा inode *inode,
					 काष्ठा delayed_call *करोne,
					 स्थिर अक्षर *name)
अणु
	काष्ठा aa_proxy *proxy = inode->i_निजी;
	काष्ठा aa_label *label;
	काष्ठा aa_profile *profile;
	अक्षर *target;
	पूर्णांक depth;

	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);

	label = aa_get_label_rcu(&proxy->label);
	profile = labels_profile(label);
	depth = profile_depth(profile);
	target = gen_symlink_name(depth, profile->rawdata->name, name);
	aa_put_label(label);

	अगर (IS_ERR(target))
		वापस target;

	set_delayed_call(करोne, rawdata_link_cb, target);

	वापस target;
पूर्ण

अटल स्थिर अक्षर *rawdata_get_link_sha1(काष्ठा dentry *dentry,
					 काष्ठा inode *inode,
					 काष्ठा delayed_call *करोne)
अणु
	वापस rawdata_get_link_base(dentry, inode, करोne, "sha1");
पूर्ण

अटल स्थिर अक्षर *rawdata_get_link_abi(काष्ठा dentry *dentry,
					काष्ठा inode *inode,
					काष्ठा delayed_call *करोne)
अणु
	वापस rawdata_get_link_base(dentry, inode, करोne, "abi");
पूर्ण

अटल स्थिर अक्षर *rawdata_get_link_data(काष्ठा dentry *dentry,
					 काष्ठा inode *inode,
					 काष्ठा delayed_call *करोne)
अणु
	वापस rawdata_get_link_base(dentry, inode, करोne, "raw_data");
पूर्ण

अटल स्थिर काष्ठा inode_operations rawdata_link_sha1_iops = अणु
	.get_link	= rawdata_get_link_sha1,
पूर्ण;

अटल स्थिर काष्ठा inode_operations rawdata_link_abi_iops = अणु
	.get_link	= rawdata_get_link_abi,
पूर्ण;
अटल स्थिर काष्ठा inode_operations rawdata_link_data_iops = अणु
	.get_link	= rawdata_get_link_data,
पूर्ण;


/*
 * Requires: @profile->ns->lock held
 */
पूर्णांक __aafs_profile_सूची_गढ़ो(काष्ठा aa_profile *profile, काष्ठा dentry *parent)
अणु
	काष्ठा aa_profile *child;
	काष्ठा dentry *dent = शून्य, *dir;
	पूर्णांक error;

	AA_BUG(!profile);
	AA_BUG(!mutex_is_locked(&profiles_ns(profile)->lock));

	अगर (!parent) अणु
		काष्ठा aa_profile *p;
		p = aa_deref_parent(profile);
		dent = prof_dir(p);
		/* adding to parent that previously didn't have children */
		dent = aafs_create_dir("profiles", dent);
		अगर (IS_ERR(dent))
			जाओ fail;
		prof_child_dir(p) = parent = dent;
	पूर्ण

	अगर (!profile->स_नाम) अणु
		पूर्णांक len, id_len;
		len = mangle_name(profile->base.name, शून्य);
		id_len = snम_लिखो(शून्य, 0, ".%ld", profile->ns->uniq_id);

		profile->स_नाम = kदो_स्मृति(len + id_len + 1, GFP_KERNEL);
		अगर (!profile->स_नाम) अणु
			error = -ENOMEM;
			जाओ fail2;
		पूर्ण

		mangle_name(profile->base.name, profile->स_नाम);
		प्र_लिखो(profile->स_नाम + len, ".%ld", profile->ns->uniq_id++);
	पूर्ण

	dent = aafs_create_dir(profile->स_नाम, parent);
	अगर (IS_ERR(dent))
		जाओ fail;
	prof_dir(profile) = dir = dent;

	dent = create_profile_file(dir, "name", profile,
				   &seq_profile_name_fops);
	अगर (IS_ERR(dent))
		जाओ fail;
	profile->dents[AAFS_PROF_NAME] = dent;

	dent = create_profile_file(dir, "mode", profile,
				   &seq_profile_mode_fops);
	अगर (IS_ERR(dent))
		जाओ fail;
	profile->dents[AAFS_PROF_MODE] = dent;

	dent = create_profile_file(dir, "attach", profile,
				   &seq_profile_attach_fops);
	अगर (IS_ERR(dent))
		जाओ fail;
	profile->dents[AAFS_PROF_ATTACH] = dent;

	अगर (profile->hash) अणु
		dent = create_profile_file(dir, "sha1", profile,
					   &seq_profile_hash_fops);
		अगर (IS_ERR(dent))
			जाओ fail;
		profile->dents[AAFS_PROF_HASH] = dent;
	पूर्ण

	अगर (profile->rawdata) अणु
		dent = aafs_create("raw_sha1", S_IFLNK | 0444, dir,
				   profile->label.proxy, शून्य, शून्य,
				   &rawdata_link_sha1_iops);
		अगर (IS_ERR(dent))
			जाओ fail;
		aa_get_proxy(profile->label.proxy);
		profile->dents[AAFS_PROF_RAW_HASH] = dent;

		dent = aafs_create("raw_abi", S_IFLNK | 0444, dir,
				   profile->label.proxy, शून्य, शून्य,
				   &rawdata_link_abi_iops);
		अगर (IS_ERR(dent))
			जाओ fail;
		aa_get_proxy(profile->label.proxy);
		profile->dents[AAFS_PROF_RAW_ABI] = dent;

		dent = aafs_create("raw_data", S_IFLNK | 0444, dir,
				   profile->label.proxy, शून्य, शून्य,
				   &rawdata_link_data_iops);
		अगर (IS_ERR(dent))
			जाओ fail;
		aa_get_proxy(profile->label.proxy);
		profile->dents[AAFS_PROF_RAW_DATA] = dent;
	पूर्ण

	list_क्रम_each_entry(child, &profile->base.profiles, base.list) अणु
		error = __aafs_profile_सूची_गढ़ो(child, prof_child_dir(profile));
		अगर (error)
			जाओ fail2;
	पूर्ण

	वापस 0;

fail:
	error = PTR_ERR(dent);

fail2:
	__aafs_profile_सूची_हटाओ(profile);

	वापस error;
पूर्ण

अटल पूर्णांक ns_सूची_गढ़ो_op(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा aa_ns *ns, *parent;
	/* TODO: improve permission check */
	काष्ठा aa_label *label;
	पूर्णांक error;

	label = begin_current_label_crit_section();
	error = aa_may_manage_policy(label, शून्य, AA_MAY_LOAD_POLICY);
	end_current_label_crit_section(label);
	अगर (error)
		वापस error;

	parent = aa_get_ns(dir->i_निजी);
	AA_BUG(d_inode(ns_subns_dir(parent)) != dir);

	/* we have to unlock and then relock to get locking order right
	 * क्रम pin_fs
	 */
	inode_unlock(dir);
	error = simple_pin_fs(&aafs_ops, &aafs_mnt, &aafs_count);
	mutex_lock_nested(&parent->lock, parent->level);
	inode_lock_nested(dir, I_MUTEX_PARENT);
	अगर (error)
		जाओ out;

	error = __aafs_setup_d_inode(dir, dentry, mode | S_IFसूची,  शून्य,
				     शून्य, शून्य, शून्य);
	अगर (error)
		जाओ out_pin;

	ns = __aa_find_or_create_ns(parent, READ_ONCE(dentry->d_name.name),
				    dentry);
	अगर (IS_ERR(ns)) अणु
		error = PTR_ERR(ns);
		ns = शून्य;
	पूर्ण

	aa_put_ns(ns);		/* list ref reमुख्यs */
out_pin:
	अगर (error)
		simple_release_fs(&aafs_mnt, &aafs_count);
out:
	mutex_unlock(&parent->lock);
	aa_put_ns(parent);

	वापस error;
पूर्ण

अटल पूर्णांक ns_सूची_हटाओ_op(काष्ठा inode *dir, काष्ठा dentry *dentry)
अणु
	काष्ठा aa_ns *ns, *parent;
	/* TODO: improve permission check */
	काष्ठा aa_label *label;
	पूर्णांक error;

	label = begin_current_label_crit_section();
	error = aa_may_manage_policy(label, शून्य, AA_MAY_LOAD_POLICY);
	end_current_label_crit_section(label);
	अगर (error)
		वापस error;

	parent = aa_get_ns(dir->i_निजी);
	/* सूची_हटाओ calls the generic securityfs functions to हटाओ files
	 * from the apparmor dir. It is up to the apparmor ns locking
	 * to aव्योम races.
	 */
	inode_unlock(dir);
	inode_unlock(dentry->d_inode);

	mutex_lock_nested(&parent->lock, parent->level);
	ns = aa_get_ns(__aa_findn_ns(&parent->sub_ns, dentry->d_name.name,
				     dentry->d_name.len));
	अगर (!ns) अणु
		error = -ENOENT;
		जाओ out;
	पूर्ण
	AA_BUG(ns_dir(ns) != dentry);

	__aa_हटाओ_ns(ns);
	aa_put_ns(ns);

out:
	mutex_unlock(&parent->lock);
	inode_lock_nested(dir, I_MUTEX_PARENT);
	inode_lock(dentry->d_inode);
	aa_put_ns(parent);

	वापस error;
पूर्ण

अटल स्थिर काष्ठा inode_operations ns_dir_inode_operations = अणु
	.lookup		= simple_lookup,
	.सूची_गढ़ो		= ns_सूची_गढ़ो_op,
	.सूची_हटाओ		= ns_सूची_हटाओ_op,
पूर्ण;

अटल व्योम __aa_fs_list_हटाओ_rawdata(काष्ठा aa_ns *ns)
अणु
	काष्ठा aa_loaddata *ent, *पंचांगp;

	AA_BUG(!mutex_is_locked(&ns->lock));

	list_क्रम_each_entry_safe(ent, पंचांगp, &ns->rawdata_list, list)
		__aa_fs_हटाओ_rawdata(ent);
पूर्ण

/**
 *
 * Requires: @ns->lock held
 */
व्योम __aafs_ns_सूची_हटाओ(काष्ठा aa_ns *ns)
अणु
	काष्ठा aa_ns *sub;
	काष्ठा aa_profile *child;
	पूर्णांक i;

	अगर (!ns)
		वापस;
	AA_BUG(!mutex_is_locked(&ns->lock));

	list_क्रम_each_entry(child, &ns->base.profiles, base.list)
		__aafs_profile_सूची_हटाओ(child);

	list_क्रम_each_entry(sub, &ns->sub_ns, base.list) अणु
		mutex_lock_nested(&sub->lock, sub->level);
		__aafs_ns_सूची_हटाओ(sub);
		mutex_unlock(&sub->lock);
	पूर्ण

	__aa_fs_list_हटाओ_rawdata(ns);

	अगर (ns_subns_dir(ns)) अणु
		sub = d_inode(ns_subns_dir(ns))->i_निजी;
		aa_put_ns(sub);
	पूर्ण
	अगर (ns_subload(ns)) अणु
		sub = d_inode(ns_subload(ns))->i_निजी;
		aa_put_ns(sub);
	पूर्ण
	अगर (ns_subreplace(ns)) अणु
		sub = d_inode(ns_subreplace(ns))->i_निजी;
		aa_put_ns(sub);
	पूर्ण
	अगर (ns_subहटाओ(ns)) अणु
		sub = d_inode(ns_subहटाओ(ns))->i_निजी;
		aa_put_ns(sub);
	पूर्ण
	अगर (ns_subrevision(ns)) अणु
		sub = d_inode(ns_subrevision(ns))->i_निजी;
		aa_put_ns(sub);
	पूर्ण

	क्रम (i = AAFS_NS_SIZखातापूर्ण - 1; i >= 0; --i) अणु
		aafs_हटाओ(ns->dents[i]);
		ns->dents[i] = शून्य;
	पूर्ण
पूर्ण

/* assumes cleanup in caller */
अटल पूर्णांक __aafs_ns_सूची_गढ़ो_entries(काष्ठा aa_ns *ns, काष्ठा dentry *dir)
अणु
	काष्ठा dentry *dent;

	AA_BUG(!ns);
	AA_BUG(!dir);

	dent = aafs_create_dir("profiles", dir);
	अगर (IS_ERR(dent))
		वापस PTR_ERR(dent);
	ns_subprofs_dir(ns) = dent;

	dent = aafs_create_dir("raw_data", dir);
	अगर (IS_ERR(dent))
		वापस PTR_ERR(dent);
	ns_subdata_dir(ns) = dent;

	dent = aafs_create_file("revision", 0444, dir, ns,
				&aa_fs_ns_revision_fops);
	अगर (IS_ERR(dent))
		वापस PTR_ERR(dent);
	aa_get_ns(ns);
	ns_subrevision(ns) = dent;

	dent = aafs_create_file(".load", 0640, dir, ns,
				      &aa_fs_profile_load);
	अगर (IS_ERR(dent))
		वापस PTR_ERR(dent);
	aa_get_ns(ns);
	ns_subload(ns) = dent;

	dent = aafs_create_file(".replace", 0640, dir, ns,
				      &aa_fs_profile_replace);
	अगर (IS_ERR(dent))
		वापस PTR_ERR(dent);
	aa_get_ns(ns);
	ns_subreplace(ns) = dent;

	dent = aafs_create_file(".remove", 0640, dir, ns,
				      &aa_fs_profile_हटाओ);
	अगर (IS_ERR(dent))
		वापस PTR_ERR(dent);
	aa_get_ns(ns);
	ns_subहटाओ(ns) = dent;

	  /* use create_dentry so we can supply निजी data */
	dent = aafs_create("namespaces", S_IFसूची | 0755, dir, ns, शून्य, शून्य,
			   &ns_dir_inode_operations);
	अगर (IS_ERR(dent))
		वापस PTR_ERR(dent);
	aa_get_ns(ns);
	ns_subns_dir(ns) = dent;

	वापस 0;
पूर्ण

/*
 * Requires: @ns->lock held
 */
पूर्णांक __aafs_ns_सूची_गढ़ो(काष्ठा aa_ns *ns, काष्ठा dentry *parent, स्थिर अक्षर *name,
		    काष्ठा dentry *dent)
अणु
	काष्ठा aa_ns *sub;
	काष्ठा aa_profile *child;
	काष्ठा dentry *dir;
	पूर्णांक error;

	AA_BUG(!ns);
	AA_BUG(!parent);
	AA_BUG(!mutex_is_locked(&ns->lock));

	अगर (!name)
		name = ns->base.name;

	अगर (!dent) अणु
		/* create ns dir अगर it करोesn't alपढ़ोy exist */
		dent = aafs_create_dir(name, parent);
		अगर (IS_ERR(dent))
			जाओ fail;
	पूर्ण अन्यथा
		dget(dent);
	ns_dir(ns) = dir = dent;
	error = __aafs_ns_सूची_गढ़ो_entries(ns, dir);
	अगर (error)
		जाओ fail2;

	/* profiles */
	list_क्रम_each_entry(child, &ns->base.profiles, base.list) अणु
		error = __aafs_profile_सूची_गढ़ो(child, ns_subprofs_dir(ns));
		अगर (error)
			जाओ fail2;
	पूर्ण

	/* subnamespaces */
	list_क्रम_each_entry(sub, &ns->sub_ns, base.list) अणु
		mutex_lock_nested(&sub->lock, sub->level);
		error = __aafs_ns_सूची_गढ़ो(sub, ns_subns_dir(ns), शून्य, शून्य);
		mutex_unlock(&sub->lock);
		अगर (error)
			जाओ fail2;
	पूर्ण

	वापस 0;

fail:
	error = PTR_ERR(dent);

fail2:
	__aafs_ns_सूची_हटाओ(ns);

	वापस error;
पूर्ण

/**
 * __next_ns - find the next namespace to list
 * @root: root namespace to stop search at (NOT शून्य)
 * @ns: current ns position (NOT शून्य)
 *
 * Find the next namespace from @ns under @root and handle all locking needed
 * जबतक चयनing current namespace.
 *
 * Returns: next namespace or शून्य अगर at last namespace under @root
 * Requires: ns->parent->lock to be held
 * NOTE: will not unlock root->lock
 */
अटल काष्ठा aa_ns *__next_ns(काष्ठा aa_ns *root, काष्ठा aa_ns *ns)
अणु
	काष्ठा aa_ns *parent, *next;

	AA_BUG(!root);
	AA_BUG(!ns);
	AA_BUG(ns != root && !mutex_is_locked(&ns->parent->lock));

	/* is next namespace a child */
	अगर (!list_empty(&ns->sub_ns)) अणु
		next = list_first_entry(&ns->sub_ns, typeof(*ns), base.list);
		mutex_lock_nested(&next->lock, next->level);
		वापस next;
	पूर्ण

	/* check अगर the next ns is a sibling, parent, gp, .. */
	parent = ns->parent;
	जबतक (ns != root) अणु
		mutex_unlock(&ns->lock);
		next = list_next_entry(ns, base.list);
		अगर (!list_entry_is_head(next, &parent->sub_ns, base.list)) अणु
			mutex_lock_nested(&next->lock, next->level);
			वापस next;
		पूर्ण
		ns = parent;
		parent = parent->parent;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * __first_profile - find the first profile in a namespace
 * @root: namespace that is root of profiles being displayed (NOT शून्य)
 * @ns: namespace to start in   (NOT शून्य)
 *
 * Returns: unrefcounted profile or शून्य अगर no profile
 * Requires: profile->ns.lock to be held
 */
अटल काष्ठा aa_profile *__first_profile(काष्ठा aa_ns *root,
					  काष्ठा aa_ns *ns)
अणु
	AA_BUG(!root);
	AA_BUG(ns && !mutex_is_locked(&ns->lock));

	क्रम (; ns; ns = __next_ns(root, ns)) अणु
		अगर (!list_empty(&ns->base.profiles))
			वापस list_first_entry(&ns->base.profiles,
						काष्ठा aa_profile, base.list);
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * __next_profile - step to the next profile in a profile tree
 * @profile: current profile in tree (NOT शून्य)
 *
 * Perक्रमm a depth first traversal on the profile tree in a namespace
 *
 * Returns: next profile or शून्य अगर करोne
 * Requires: profile->ns.lock to be held
 */
अटल काष्ठा aa_profile *__next_profile(काष्ठा aa_profile *p)
अणु
	काष्ठा aa_profile *parent;
	काष्ठा aa_ns *ns = p->ns;

	AA_BUG(!mutex_is_locked(&profiles_ns(p)->lock));

	/* is next profile a child */
	अगर (!list_empty(&p->base.profiles))
		वापस list_first_entry(&p->base.profiles, typeof(*p),
					base.list);

	/* is next profile a sibling, parent sibling, gp, sibling, .. */
	parent = rcu_dereference_रक्षित(p->parent,
					   mutex_is_locked(&p->ns->lock));
	जबतक (parent) अणु
		p = list_next_entry(p, base.list);
		अगर (!list_entry_is_head(p, &parent->base.profiles, base.list))
			वापस p;
		p = parent;
		parent = rcu_dereference_रक्षित(parent->parent,
					    mutex_is_locked(&parent->ns->lock));
	पूर्ण

	/* is next another profile in the namespace */
	p = list_next_entry(p, base.list);
	अगर (!list_entry_is_head(p, &ns->base.profiles, base.list))
		वापस p;

	वापस शून्य;
पूर्ण

/**
 * next_profile - step to the next profile in where ever it may be
 * @root: root namespace  (NOT शून्य)
 * @profile: current profile  (NOT शून्य)
 *
 * Returns: next profile or शून्य अगर there isn't one
 */
अटल काष्ठा aa_profile *next_profile(काष्ठा aa_ns *root,
				       काष्ठा aa_profile *profile)
अणु
	काष्ठा aa_profile *next = __next_profile(profile);
	अगर (next)
		वापस next;

	/* finished all profiles in namespace move to next namespace */
	वापस __first_profile(root, __next_ns(root, profile->ns));
पूर्ण

/**
 * p_start - start a depth first traversal of profile tree
 * @f: seq_file to fill
 * @pos: current position
 *
 * Returns: first profile under current namespace or शून्य अगर none found
 *
 * acquires first ns->lock
 */
अटल व्योम *p_start(काष्ठा seq_file *f, loff_t *pos)
अणु
	काष्ठा aa_profile *profile = शून्य;
	काष्ठा aa_ns *root = aa_get_current_ns();
	loff_t l = *pos;
	f->निजी = root;

	/* find the first profile */
	mutex_lock_nested(&root->lock, root->level);
	profile = __first_profile(root, root);

	/* skip to position */
	क्रम (; profile && l > 0; l--)
		profile = next_profile(root, profile);

	वापस profile;
पूर्ण

/**
 * p_next - पढ़ो the next profile entry
 * @f: seq_file to fill
 * @p: profile previously वापसed
 * @pos: current position
 *
 * Returns: next profile after @p or शून्य अगर none
 *
 * may acquire/release locks in namespace tree as necessary
 */
अटल व्योम *p_next(काष्ठा seq_file *f, व्योम *p, loff_t *pos)
अणु
	काष्ठा aa_profile *profile = p;
	काष्ठा aa_ns *ns = f->निजी;
	(*pos)++;

	वापस next_profile(ns, profile);
पूर्ण

/**
 * p_stop - stop depth first traversal
 * @f: seq_file we are filling
 * @p: the last profile ग_लिखोn
 *
 * Release all locking करोne by p_start/p_next on namespace tree
 */
अटल व्योम p_stop(काष्ठा seq_file *f, व्योम *p)
अणु
	काष्ठा aa_profile *profile = p;
	काष्ठा aa_ns *root = f->निजी, *ns;

	अगर (profile) अणु
		क्रम (ns = profile->ns; ns && ns != root; ns = ns->parent)
			mutex_unlock(&ns->lock);
	पूर्ण
	mutex_unlock(&root->lock);
	aa_put_ns(root);
पूर्ण

/**
 * seq_show_profile - show a profile entry
 * @f: seq_file to file
 * @p: current position (profile)    (NOT शून्य)
 *
 * Returns: error on failure
 */
अटल पूर्णांक seq_show_profile(काष्ठा seq_file *f, व्योम *p)
अणु
	काष्ठा aa_profile *profile = (काष्ठा aa_profile *)p;
	काष्ठा aa_ns *root = f->निजी;

	aa_label_seq_xprपूर्णांक(f, root, &profile->label,
			    FLAG_SHOW_MODE | FLAG_VIEW_SUBNS, GFP_KERNEL);
	seq_अ_दो(f, '\n');

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा seq_operations aa_sfs_profiles_op = अणु
	.start = p_start,
	.next = p_next,
	.stop = p_stop,
	.show = seq_show_profile,
पूर्ण;

अटल पूर्णांक profiles_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	अगर (!policy_view_capable(शून्य))
		वापस -EACCES;

	वापस seq_खोलो(file, &aa_sfs_profiles_op);
पूर्ण

अटल पूर्णांक profiles_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस seq_release(inode, file);
पूर्ण

अटल स्थिर काष्ठा file_operations aa_sfs_profiles_fops = अणु
	.खोलो = profiles_खोलो,
	.पढ़ो = seq_पढ़ो,
	.llseek = seq_lseek,
	.release = profiles_release,
पूर्ण;


/** Base file प्रणाली setup **/
अटल काष्ठा aa_sfs_entry aa_sfs_entry_file[] = अणु
	AA_SFS_खाता_STRING("mask",
			   "create read write exec append mmap_exec link lock"),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा aa_sfs_entry aa_sfs_entry_ptrace[] = अणु
	AA_SFS_खाता_STRING("mask", "read trace"),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा aa_sfs_entry aa_sfs_entry_संकेत[] = अणु
	AA_SFS_खाता_STRING("mask", AA_SFS_SIG_MASK),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा aa_sfs_entry aa_sfs_entry_attach[] = अणु
	AA_SFS_खाता_BOOLEAN("xattr", 1),
	अणु पूर्ण
पूर्ण;
अटल काष्ठा aa_sfs_entry aa_sfs_entry_करोमुख्य[] = अणु
	AA_SFS_खाता_BOOLEAN("change_hat",	1),
	AA_SFS_खाता_BOOLEAN("change_hatv",	1),
	AA_SFS_खाता_BOOLEAN("change_onexec",	1),
	AA_SFS_खाता_BOOLEAN("change_profile",	1),
	AA_SFS_खाता_BOOLEAN("stack",		1),
	AA_SFS_खाता_BOOLEAN("fix_binfmt_elf_mmap",	1),
	AA_SFS_खाता_BOOLEAN("post_nnp_subset",	1),
	AA_SFS_खाता_BOOLEAN("computed_longest_left",	1),
	AA_SFS_सूची("attach_conditions",		aa_sfs_entry_attach),
	AA_SFS_खाता_STRING("version", "1.2"),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा aa_sfs_entry aa_sfs_entry_versions[] = अणु
	AA_SFS_खाता_BOOLEAN("v5",	1),
	AA_SFS_खाता_BOOLEAN("v6",	1),
	AA_SFS_खाता_BOOLEAN("v7",	1),
	AA_SFS_खाता_BOOLEAN("v8",	1),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा aa_sfs_entry aa_sfs_entry_policy[] = अणु
	AA_SFS_सूची("versions",			aa_sfs_entry_versions),
	AA_SFS_खाता_BOOLEAN("set_load",		1),
	/* number of out of band transitions supported */
	AA_SFS_खाता_U64("outofband",		MAX_OOB_SUPPORTED),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा aa_sfs_entry aa_sfs_entry_mount[] = अणु
	AA_SFS_खाता_STRING("mask", "mount umount pivot_root"),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा aa_sfs_entry aa_sfs_entry_ns[] = अणु
	AA_SFS_खाता_BOOLEAN("profile",		1),
	AA_SFS_खाता_BOOLEAN("pivot_root",	0),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा aa_sfs_entry aa_sfs_entry_query_label[] = अणु
	AA_SFS_खाता_STRING("perms", "allow deny audit quiet"),
	AA_SFS_खाता_BOOLEAN("data",		1),
	AA_SFS_खाता_BOOLEAN("multi_transaction",	1),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा aa_sfs_entry aa_sfs_entry_query[] = अणु
	AA_SFS_सूची("label",			aa_sfs_entry_query_label),
	अणु पूर्ण
पूर्ण;
अटल काष्ठा aa_sfs_entry aa_sfs_entry_features[] = अणु
	AA_SFS_सूची("policy",			aa_sfs_entry_policy),
	AA_SFS_सूची("domain",			aa_sfs_entry_करोमुख्य),
	AA_SFS_सूची("file",			aa_sfs_entry_file),
	AA_SFS_सूची("network_v8",		aa_sfs_entry_network),
	AA_SFS_सूची("mount",			aa_sfs_entry_mount),
	AA_SFS_सूची("namespaces",		aa_sfs_entry_ns),
	AA_SFS_खाता_U64("capability",		VFS_CAP_FLAGS_MASK),
	AA_SFS_सूची("rlimit",			aa_sfs_entry_rlimit),
	AA_SFS_सूची("caps",			aa_sfs_entry_caps),
	AA_SFS_सूची("ptrace",			aa_sfs_entry_ptrace),
	AA_SFS_सूची("signal",			aa_sfs_entry_संकेत),
	AA_SFS_सूची("query",			aa_sfs_entry_query),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा aa_sfs_entry aa_sfs_entry_apparmor[] = अणु
	AA_SFS_खाता_FOPS(".access", 0666, &aa_sfs_access),
	AA_SFS_खाता_FOPS(".stacked", 0444, &seq_ns_stacked_fops),
	AA_SFS_खाता_FOPS(".ns_stacked", 0444, &seq_ns_nsstacked_fops),
	AA_SFS_खाता_FOPS(".ns_level", 0444, &seq_ns_level_fops),
	AA_SFS_खाता_FOPS(".ns_name", 0444, &seq_ns_name_fops),
	AA_SFS_खाता_FOPS("profiles", 0444, &aa_sfs_profiles_fops),
	AA_SFS_सूची("features", aa_sfs_entry_features),
	अणु पूर्ण
पूर्ण;

अटल काष्ठा aa_sfs_entry aa_sfs_entry =
	AA_SFS_सूची("apparmor", aa_sfs_entry_apparmor);

/**
 * entry_create_file - create a file entry in the apparmor securityfs
 * @fs_file: aa_sfs_entry to build an entry क्रम (NOT शून्य)
 * @parent: the parent dentry in the securityfs
 *
 * Use entry_हटाओ_file to हटाओ entries created with this fn.
 */
अटल पूर्णांक __init entry_create_file(काष्ठा aa_sfs_entry *fs_file,
				    काष्ठा dentry *parent)
अणु
	पूर्णांक error = 0;

	fs_file->dentry = securityfs_create_file(fs_file->name,
						 S_IFREG | fs_file->mode,
						 parent, fs_file,
						 fs_file->file_ops);
	अगर (IS_ERR(fs_file->dentry)) अणु
		error = PTR_ERR(fs_file->dentry);
		fs_file->dentry = शून्य;
	पूर्ण
	वापस error;
पूर्ण

अटल व्योम __init entry_हटाओ_dir(काष्ठा aa_sfs_entry *fs_dir);
/**
 * entry_create_dir - recursively create a directory entry in the securityfs
 * @fs_dir: aa_sfs_entry (and all child entries) to build (NOT शून्य)
 * @parent: the parent dentry in the securityfs
 *
 * Use entry_हटाओ_dir to हटाओ entries created with this fn.
 */
अटल पूर्णांक __init entry_create_dir(काष्ठा aa_sfs_entry *fs_dir,
				   काष्ठा dentry *parent)
अणु
	काष्ठा aa_sfs_entry *fs_file;
	काष्ठा dentry *dir;
	पूर्णांक error;

	dir = securityfs_create_dir(fs_dir->name, parent);
	अगर (IS_ERR(dir))
		वापस PTR_ERR(dir);
	fs_dir->dentry = dir;

	क्रम (fs_file = fs_dir->v.files; fs_file && fs_file->name; ++fs_file) अणु
		अगर (fs_file->v_type == AA_SFS_TYPE_सूची)
			error = entry_create_dir(fs_file, fs_dir->dentry);
		अन्यथा
			error = entry_create_file(fs_file, fs_dir->dentry);
		अगर (error)
			जाओ failed;
	पूर्ण

	वापस 0;

failed:
	entry_हटाओ_dir(fs_dir);

	वापस error;
पूर्ण

/**
 * entry_हटाओ_file - drop a single file entry in the apparmor securityfs
 * @fs_file: aa_sfs_entry to detach from the securityfs (NOT शून्य)
 */
अटल व्योम __init entry_हटाओ_file(काष्ठा aa_sfs_entry *fs_file)
अणु
	अगर (!fs_file->dentry)
		वापस;

	securityfs_हटाओ(fs_file->dentry);
	fs_file->dentry = शून्य;
पूर्ण

/**
 * entry_हटाओ_dir - recursively drop a directory entry from the securityfs
 * @fs_dir: aa_sfs_entry (and all child entries) to detach (NOT शून्य)
 */
अटल व्योम __init entry_हटाओ_dir(काष्ठा aa_sfs_entry *fs_dir)
अणु
	काष्ठा aa_sfs_entry *fs_file;

	क्रम (fs_file = fs_dir->v.files; fs_file && fs_file->name; ++fs_file) अणु
		अगर (fs_file->v_type == AA_SFS_TYPE_सूची)
			entry_हटाओ_dir(fs_file);
		अन्यथा
			entry_हटाओ_file(fs_file);
	पूर्ण

	entry_हटाओ_file(fs_dir);
पूर्ण

/**
 * aa_destroy_aafs - cleanup and मुक्त aafs
 *
 * releases dentries allocated by aa_create_aafs
 */
व्योम __init aa_destroy_aafs(व्योम)
अणु
	entry_हटाओ_dir(&aa_sfs_entry);
पूर्ण


#घोषणा शून्य_खाता_NAME ".null"
काष्ठा path aa_null;

अटल पूर्णांक aa_mk_null_file(काष्ठा dentry *parent)
अणु
	काष्ठा vfsmount *mount = शून्य;
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;
	पूर्णांक count = 0;
	पूर्णांक error = simple_pin_fs(parent->d_sb->s_type, &mount, &count);

	अगर (error)
		वापस error;

	inode_lock(d_inode(parent));
	dentry = lookup_one_len(शून्य_खाता_NAME, parent, म_माप(शून्य_खाता_NAME));
	अगर (IS_ERR(dentry)) अणु
		error = PTR_ERR(dentry);
		जाओ out;
	पूर्ण
	inode = new_inode(parent->d_inode->i_sb);
	अगर (!inode) अणु
		error = -ENOMEM;
		जाओ out1;
	पूर्ण

	inode->i_ino = get_next_ino();
	inode->i_mode = S_IFCHR | S_IRUGO | S_IWUGO;
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	init_special_inode(inode, S_IFCHR | S_IRUGO | S_IWUGO,
			   MKDEV(MEM_MAJOR, 3));
	d_instantiate(dentry, inode);
	aa_null.dentry = dget(dentry);
	aa_null.mnt = mntget(mount);

	error = 0;

out1:
	dput(dentry);
out:
	inode_unlock(d_inode(parent));
	simple_release_fs(&mount, &count);
	वापस error;
पूर्ण



अटल स्थिर अक्षर *policy_get_link(काष्ठा dentry *dentry,
				   काष्ठा inode *inode,
				   काष्ठा delayed_call *करोne)
अणु
	काष्ठा aa_ns *ns;
	काष्ठा path path;
	पूर्णांक error;

	अगर (!dentry)
		वापस ERR_PTR(-ECHILD);

	ns = aa_get_current_ns();
	path.mnt = mntget(aafs_mnt);
	path.dentry = dget(ns_dir(ns));
	error = nd_jump_link(&path);
	aa_put_ns(ns);

	वापस ERR_PTR(error);
पूर्ण

अटल पूर्णांक policy_पढ़ोlink(काष्ठा dentry *dentry, अक्षर __user *buffer,
			   पूर्णांक buflen)
अणु
	अक्षर name[32];
	पूर्णांक res;

	res = snम_लिखो(name, माप(name), "%s:[%lu]", AAFS_NAME,
		       d_inode(dentry)->i_ino);
	अगर (res > 0 && res < माप(name))
		res = पढ़ोlink_copy(buffer, buflen, name);
	अन्यथा
		res = -ENOENT;

	वापस res;
पूर्ण

अटल स्थिर काष्ठा inode_operations policy_link_iops = अणु
	.पढ़ोlink	= policy_पढ़ोlink,
	.get_link	= policy_get_link,
पूर्ण;


/**
 * aa_create_aafs - create the apparmor security fileप्रणाली
 *
 * dentries created here are released by aa_destroy_aafs
 *
 * Returns: error on failure
 */
अटल पूर्णांक __init aa_create_aafs(व्योम)
अणु
	काष्ठा dentry *dent;
	पूर्णांक error;

	अगर (!apparmor_initialized)
		वापस 0;

	अगर (aa_sfs_entry.dentry) अणु
		AA_ERROR("%s: AppArmor securityfs already exists\n", __func__);
		वापस -EEXIST;
	पूर्ण

	/* setup apparmorfs used to भवize policy/ */
	aafs_mnt = kern_mount(&aafs_ops);
	अगर (IS_ERR(aafs_mnt))
		panic("can't set apparmorfs up\n");
	aafs_mnt->mnt_sb->s_flags &= ~SB_NOUSER;

	/* Populate fs tree. */
	error = entry_create_dir(&aa_sfs_entry, शून्य);
	अगर (error)
		जाओ error;

	dent = securityfs_create_file(".load", 0666, aa_sfs_entry.dentry,
				      शून्य, &aa_fs_profile_load);
	अगर (IS_ERR(dent))
		जाओ dent_error;
	ns_subload(root_ns) = dent;

	dent = securityfs_create_file(".replace", 0666, aa_sfs_entry.dentry,
				      शून्य, &aa_fs_profile_replace);
	अगर (IS_ERR(dent))
		जाओ dent_error;
	ns_subreplace(root_ns) = dent;

	dent = securityfs_create_file(".remove", 0666, aa_sfs_entry.dentry,
				      शून्य, &aa_fs_profile_हटाओ);
	अगर (IS_ERR(dent))
		जाओ dent_error;
	ns_subहटाओ(root_ns) = dent;

	dent = securityfs_create_file("revision", 0444, aa_sfs_entry.dentry,
				      शून्य, &aa_fs_ns_revision_fops);
	अगर (IS_ERR(dent))
		जाओ dent_error;
	ns_subrevision(root_ns) = dent;

	/* policy tree referenced by magic policy symlink */
	mutex_lock_nested(&root_ns->lock, root_ns->level);
	error = __aafs_ns_सूची_गढ़ो(root_ns, aafs_mnt->mnt_root, ".policy",
				aafs_mnt->mnt_root);
	mutex_unlock(&root_ns->lock);
	अगर (error)
		जाओ error;

	/* magic symlink similar to nsfs redirects based on task policy */
	dent = securityfs_create_symlink("policy", aa_sfs_entry.dentry,
					 शून्य, &policy_link_iops);
	अगर (IS_ERR(dent))
		जाओ dent_error;

	error = aa_mk_null_file(aa_sfs_entry.dentry);
	अगर (error)
		जाओ error;

	/* TODO: add शेष profile to apparmorfs */

	/* Report that AppArmor fs is enabled */
	aa_info_message("AppArmor Filesystem Enabled");
	वापस 0;

dent_error:
	error = PTR_ERR(dent);
error:
	aa_destroy_aafs();
	AA_ERROR("Error creating AppArmor securityfs\n");
	वापस error;
पूर्ण

fs_initcall(aa_create_aafs);
