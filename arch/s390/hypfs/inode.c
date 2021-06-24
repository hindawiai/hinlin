<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 *    Hypervisor fileप्रणाली क्रम Linux on s390.
 *
 *    Copyright IBM Corp. 2006, 2008
 *    Author(s): Michael Holzheu <holzheu@de.ibm.com>
 */

#घोषणा KMSG_COMPONENT "hypfs"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fs.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश <linux/namei.h>
#समावेश <linux/vfs.h>
#समावेश <linux/slab.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/समय.स>
#समावेश <linux/sysfs.h>
#समावेश <linux/init.h>
#समावेश <linux/kobject.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/uपन.स>
#समावेश <यंत्र/ebcdic.h>
#समावेश "hypfs.h"

#घोषणा HYPFS_MAGIC 0x687970	/* ASCII 'hyp' */
#घोषणा TMP_SIZE 64		/* size of temporary buffers */

अटल काष्ठा dentry *hypfs_create_update_file(काष्ठा dentry *dir);

काष्ठा hypfs_sb_info अणु
	kuid_t uid;			/* uid used क्रम files and dirs */
	kgid_t gid;			/* gid used क्रम files and dirs */
	काष्ठा dentry *update_file;	/* file to trigger update */
	समय64_t last_update;		/* last update, CLOCK_MONOTONIC समय */
	काष्ठा mutex lock;		/* lock to protect update process */
पूर्ण;

अटल स्थिर काष्ठा file_operations hypfs_file_ops;
अटल काष्ठा file_प्रणाली_type hypfs_type;
अटल स्थिर काष्ठा super_operations hypfs_s_ops;

/* start of list of all dentries, which have to be deleted on update */
अटल काष्ठा dentry *hypfs_last_dentry;

अटल व्योम hypfs_update_update(काष्ठा super_block *sb)
अणु
	काष्ठा hypfs_sb_info *sb_info = sb->s_fs_info;
	काष्ठा inode *inode = d_inode(sb_info->update_file);

	sb_info->last_update = kसमय_get_seconds();
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
पूर्ण

/* directory tree removal functions */

अटल व्योम hypfs_add_dentry(काष्ठा dentry *dentry)
अणु
	dentry->d_fsdata = hypfs_last_dentry;
	hypfs_last_dentry = dentry;
पूर्ण

अटल व्योम hypfs_हटाओ(काष्ठा dentry *dentry)
अणु
	काष्ठा dentry *parent;

	parent = dentry->d_parent;
	inode_lock(d_inode(parent));
	अगर (simple_positive(dentry)) अणु
		अगर (d_is_dir(dentry))
			simple_सूची_हटाओ(d_inode(parent), dentry);
		अन्यथा
			simple_unlink(d_inode(parent), dentry);
	पूर्ण
	d_drop(dentry);
	dput(dentry);
	inode_unlock(d_inode(parent));
पूर्ण

अटल व्योम hypfs_delete_tree(काष्ठा dentry *root)
अणु
	जबतक (hypfs_last_dentry) अणु
		काष्ठा dentry *next_dentry;
		next_dentry = hypfs_last_dentry->d_fsdata;
		hypfs_हटाओ(hypfs_last_dentry);
		hypfs_last_dentry = next_dentry;
	पूर्ण
पूर्ण

अटल काष्ठा inode *hypfs_make_inode(काष्ठा super_block *sb, umode_t mode)
अणु
	काष्ठा inode *ret = new_inode(sb);

	अगर (ret) अणु
		काष्ठा hypfs_sb_info *hypfs_info = sb->s_fs_info;
		ret->i_ino = get_next_ino();
		ret->i_mode = mode;
		ret->i_uid = hypfs_info->uid;
		ret->i_gid = hypfs_info->gid;
		ret->i_aसमय = ret->i_mसमय = ret->i_स_समय = current_समय(ret);
		अगर (S_ISसूची(mode))
			set_nlink(ret, 2);
	पूर्ण
	वापस ret;
पूर्ण

अटल व्योम hypfs_evict_inode(काष्ठा inode *inode)
अणु
	clear_inode(inode);
	kमुक्त(inode->i_निजी);
पूर्ण

अटल पूर्णांक hypfs_खोलो(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	अक्षर *data = file_inode(filp)->i_निजी;
	काष्ठा hypfs_sb_info *fs_info;

	अगर (filp->f_mode & FMODE_WRITE) अणु
		अगर (!(inode->i_mode & S_IWUGO))
			वापस -EACCES;
	पूर्ण
	अगर (filp->f_mode & FMODE_READ) अणु
		अगर (!(inode->i_mode & S_IRUGO))
			वापस -EACCES;
	पूर्ण

	fs_info = inode->i_sb->s_fs_info;
	अगर(data) अणु
		mutex_lock(&fs_info->lock);
		filp->निजी_data = kstrdup(data, GFP_KERNEL);
		अगर (!filp->निजी_data) अणु
			mutex_unlock(&fs_info->lock);
			वापस -ENOMEM;
		पूर्ण
		mutex_unlock(&fs_info->lock);
	पूर्ण
	वापस nonseekable_खोलो(inode, filp);
पूर्ण

अटल sमाप_प्रकार hypfs_पढ़ो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *to)
अणु
	काष्ठा file *file = iocb->ki_filp;
	अक्षर *data = file->निजी_data;
	माप_प्रकार available = म_माप(data);
	loff_t pos = iocb->ki_pos;
	माप_प्रकार count;

	अगर (pos < 0)
		वापस -EINVAL;
	अगर (pos >= available || !iov_iter_count(to))
		वापस 0;
	count = copy_to_iter(data + pos, available - pos, to);
	अगर (!count)
		वापस -EFAULT;
	iocb->ki_pos = pos + count;
	file_accessed(file);
	वापस count;
पूर्ण

अटल sमाप_प्रकार hypfs_ग_लिखो_iter(काष्ठा kiocb *iocb, काष्ठा iov_iter *from)
अणु
	पूर्णांक rc;
	काष्ठा super_block *sb = file_inode(iocb->ki_filp)->i_sb;
	काष्ठा hypfs_sb_info *fs_info = sb->s_fs_info;
	माप_प्रकार count = iov_iter_count(from);

	/*
	 * Currently we only allow one update per second क्रम two reasons:
	 * 1. diag 204 is VERY expensive
	 * 2. If several processes करो updates in parallel and then पढ़ो the
	 *    hypfs data, the likelihood of collisions is reduced, अगर we restrict
	 *    the minimum update पूर्णांकerval. A collision occurs, अगर during the
	 *    data gathering of one process another process triggers an update
	 *    If the first process wants to ensure consistent data, it has
	 *    to restart data collection in this हाल.
	 */
	mutex_lock(&fs_info->lock);
	अगर (fs_info->last_update == kसमय_get_seconds()) अणु
		rc = -EBUSY;
		जाओ out;
	पूर्ण
	hypfs_delete_tree(sb->s_root);
	अगर (MACHINE_IS_VM)
		rc = hypfs_vm_create_files(sb->s_root);
	अन्यथा
		rc = hypfs_diag_create_files(sb->s_root);
	अगर (rc) अणु
		pr_err("Updating the hypfs tree failed\n");
		hypfs_delete_tree(sb->s_root);
		जाओ out;
	पूर्ण
	hypfs_update_update(sb);
	rc = count;
	iov_iter_advance(from, count);
out:
	mutex_unlock(&fs_info->lock);
	वापस rc;
पूर्ण

अटल पूर्णांक hypfs_release(काष्ठा inode *inode, काष्ठा file *filp)
अणु
	kमुक्त(filp->निजी_data);
	वापस 0;
पूर्ण

क्रमागत अणु Opt_uid, Opt_gid, पूर्ण;

अटल स्थिर काष्ठा fs_parameter_spec hypfs_fs_parameters[] = अणु
	fsparam_u32("gid", Opt_gid),
	fsparam_u32("uid", Opt_uid),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक hypfs_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा hypfs_sb_info *hypfs_info = fc->s_fs_info;
	काष्ठा fs_parse_result result;
	kuid_t uid;
	kgid_t gid;
	पूर्णांक opt;

	opt = fs_parse(fc, hypfs_fs_parameters, param, &result);
	अगर (opt < 0)
		वापस opt;

	चयन (opt) अणु
	हाल Opt_uid:
		uid = make_kuid(current_user_ns(), result.uपूर्णांक_32);
		अगर (!uid_valid(uid))
			वापस invalf(fc, "Unknown uid");
		hypfs_info->uid = uid;
		अवरोध;
	हाल Opt_gid:
		gid = make_kgid(current_user_ns(), result.uपूर्णांक_32);
		अगर (!gid_valid(gid))
			वापस invalf(fc, "Unknown gid");
		hypfs_info->gid = gid;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक hypfs_show_options(काष्ठा seq_file *s, काष्ठा dentry *root)
अणु
	काष्ठा hypfs_sb_info *hypfs_info = root->d_sb->s_fs_info;

	seq_म_लिखो(s, ",uid=%u", from_kuid_munged(&init_user_ns, hypfs_info->uid));
	seq_म_लिखो(s, ",gid=%u", from_kgid_munged(&init_user_ns, hypfs_info->gid));
	वापस 0;
पूर्ण

अटल पूर्णांक hypfs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा hypfs_sb_info *sbi = sb->s_fs_info;
	काष्ठा inode *root_inode;
	काष्ठा dentry *root_dentry, *update_file;
	पूर्णांक rc;

	sb->s_blocksize = PAGE_SIZE;
	sb->s_blocksize_bits = PAGE_SHIFT;
	sb->s_magic = HYPFS_MAGIC;
	sb->s_op = &hypfs_s_ops;

	root_inode = hypfs_make_inode(sb, S_IFसूची | 0755);
	अगर (!root_inode)
		वापस -ENOMEM;
	root_inode->i_op = &simple_dir_inode_operations;
	root_inode->i_fop = &simple_dir_operations;
	sb->s_root = root_dentry = d_make_root(root_inode);
	अगर (!root_dentry)
		वापस -ENOMEM;
	अगर (MACHINE_IS_VM)
		rc = hypfs_vm_create_files(root_dentry);
	अन्यथा
		rc = hypfs_diag_create_files(root_dentry);
	अगर (rc)
		वापस rc;
	update_file = hypfs_create_update_file(root_dentry);
	अगर (IS_ERR(update_file))
		वापस PTR_ERR(update_file);
	sbi->update_file = update_file;
	hypfs_update_update(sb);
	pr_info("Hypervisor filesystem mounted\n");
	वापस 0;
पूर्ण

अटल पूर्णांक hypfs_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_single(fc, hypfs_fill_super);
पूर्ण

अटल व्योम hypfs_मुक्त_fc(काष्ठा fs_context *fc)
अणु
	kमुक्त(fc->s_fs_info);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations hypfs_context_ops = अणु
	.मुक्त		= hypfs_मुक्त_fc,
	.parse_param	= hypfs_parse_param,
	.get_tree	= hypfs_get_tree,
पूर्ण;

अटल पूर्णांक hypfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा hypfs_sb_info *sbi;

	sbi = kzalloc(माप(काष्ठा hypfs_sb_info), GFP_KERNEL);
	अगर (!sbi)
		वापस -ENOMEM;

	mutex_init(&sbi->lock);
	sbi->uid = current_uid();
	sbi->gid = current_gid();

	fc->s_fs_info = sbi;
	fc->ops = &hypfs_context_ops;
	वापस 0;
पूर्ण

अटल व्योम hypfs_समाप्त_super(काष्ठा super_block *sb)
अणु
	काष्ठा hypfs_sb_info *sb_info = sb->s_fs_info;

	अगर (sb->s_root)
		hypfs_delete_tree(sb->s_root);
	अगर (sb_info && sb_info->update_file)
		hypfs_हटाओ(sb_info->update_file);
	kमुक्त(sb->s_fs_info);
	sb->s_fs_info = शून्य;
	समाप्त_litter_super(sb);
पूर्ण

अटल काष्ठा dentry *hypfs_create_file(काष्ठा dentry *parent, स्थिर अक्षर *name,
					अक्षर *data, umode_t mode)
अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;

	inode_lock(d_inode(parent));
	dentry = lookup_one_len(name, parent, म_माप(name));
	अगर (IS_ERR(dentry)) अणु
		dentry = ERR_PTR(-ENOMEM);
		जाओ fail;
	पूर्ण
	inode = hypfs_make_inode(parent->d_sb, mode);
	अगर (!inode) अणु
		dput(dentry);
		dentry = ERR_PTR(-ENOMEM);
		जाओ fail;
	पूर्ण
	अगर (S_ISREG(mode)) अणु
		inode->i_fop = &hypfs_file_ops;
		अगर (data)
			inode->i_size = म_माप(data);
		अन्यथा
			inode->i_size = 0;
	पूर्ण अन्यथा अगर (S_ISसूची(mode)) अणु
		inode->i_op = &simple_dir_inode_operations;
		inode->i_fop = &simple_dir_operations;
		inc_nlink(d_inode(parent));
	पूर्ण अन्यथा
		BUG();
	inode->i_निजी = data;
	d_instantiate(dentry, inode);
	dget(dentry);
fail:
	inode_unlock(d_inode(parent));
	वापस dentry;
पूर्ण

काष्ठा dentry *hypfs_सूची_गढ़ो(काष्ठा dentry *parent, स्थिर अक्षर *name)
अणु
	काष्ठा dentry *dentry;

	dentry = hypfs_create_file(parent, name, शून्य, S_IFसूची | सूची_MODE);
	अगर (IS_ERR(dentry))
		वापस dentry;
	hypfs_add_dentry(dentry);
	वापस dentry;
पूर्ण

अटल काष्ठा dentry *hypfs_create_update_file(काष्ठा dentry *dir)
अणु
	काष्ठा dentry *dentry;

	dentry = hypfs_create_file(dir, "update", शून्य,
				   S_IFREG | UPDATE_खाता_MODE);
	/*
	 * We करो not put the update file on the 'delete' list with
	 * hypfs_add_dentry(), since it should not be हटाओd when the tree
	 * is updated.
	 */
	वापस dentry;
पूर्ण

काष्ठा dentry *hypfs_create_u64(काष्ठा dentry *dir,
				स्थिर अक्षर *name, __u64 value)
अणु
	अक्षर *buffer;
	अक्षर पंचांगp[TMP_SIZE];
	काष्ठा dentry *dentry;

	snम_लिखो(पंचांगp, TMP_SIZE, "%llu\n", (अचिन्हित दीर्घ दीर्घ पूर्णांक)value);
	buffer = kstrdup(पंचांगp, GFP_KERNEL);
	अगर (!buffer)
		वापस ERR_PTR(-ENOMEM);
	dentry =
	    hypfs_create_file(dir, name, buffer, S_IFREG | REG_खाता_MODE);
	अगर (IS_ERR(dentry)) अणु
		kमुक्त(buffer);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	hypfs_add_dentry(dentry);
	वापस dentry;
पूर्ण

काष्ठा dentry *hypfs_create_str(काष्ठा dentry *dir,
				स्थिर अक्षर *name, अक्षर *string)
अणु
	अक्षर *buffer;
	काष्ठा dentry *dentry;

	buffer = kदो_स्मृति(म_माप(string) + 2, GFP_KERNEL);
	अगर (!buffer)
		वापस ERR_PTR(-ENOMEM);
	प्र_लिखो(buffer, "%s\n", string);
	dentry =
	    hypfs_create_file(dir, name, buffer, S_IFREG | REG_खाता_MODE);
	अगर (IS_ERR(dentry)) अणु
		kमुक्त(buffer);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण
	hypfs_add_dentry(dentry);
	वापस dentry;
पूर्ण

अटल स्थिर काष्ठा file_operations hypfs_file_ops = अणु
	.खोलो		= hypfs_खोलो,
	.release	= hypfs_release,
	.पढ़ो_iter	= hypfs_पढ़ो_iter,
	.ग_लिखो_iter	= hypfs_ग_लिखो_iter,
	.llseek		= no_llseek,
पूर्ण;

अटल काष्ठा file_प्रणाली_type hypfs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "s390_hypfs",
	.init_fs_context = hypfs_init_fs_context,
	.parameters	= hypfs_fs_parameters,
	.समाप्त_sb	= hypfs_समाप्त_super
पूर्ण;

अटल स्थिर काष्ठा super_operations hypfs_s_ops = अणु
	.statfs		= simple_statfs,
	.evict_inode	= hypfs_evict_inode,
	.show_options	= hypfs_show_options,
पूर्ण;

अटल पूर्णांक __init hypfs_init(व्योम)
अणु
	पूर्णांक rc;

	hypfs_dbfs_init();

	अगर (hypfs_diag_init()) अणु
		rc = -ENODATA;
		जाओ fail_dbfs_निकास;
	पूर्ण
	अगर (hypfs_vm_init()) अणु
		rc = -ENODATA;
		जाओ fail_hypfs_diag_निकास;
	पूर्ण
	hypfs_sprp_init();
	अगर (hypfs_diag0c_init()) अणु
		rc = -ENODATA;
		जाओ fail_hypfs_sprp_निकास;
	पूर्ण
	rc = sysfs_create_mount_poपूर्णांक(hypervisor_kobj, "s390");
	अगर (rc)
		जाओ fail_hypfs_diag0c_निकास;
	rc = रेजिस्टर_fileप्रणाली(&hypfs_type);
	अगर (rc)
		जाओ fail_fileप्रणाली;
	वापस 0;

fail_fileप्रणाली:
	sysfs_हटाओ_mount_poपूर्णांक(hypervisor_kobj, "s390");
fail_hypfs_diag0c_निकास:
	hypfs_diag0c_निकास();
fail_hypfs_sprp_निकास:
	hypfs_sprp_निकास();
	hypfs_vm_निकास();
fail_hypfs_diag_निकास:
	hypfs_diag_निकास();
fail_dbfs_निकास:
	hypfs_dbfs_निकास();
	pr_err("Initialization of hypfs failed with rc=%i\n", rc);
	वापस rc;
पूर्ण
device_initcall(hypfs_init)
