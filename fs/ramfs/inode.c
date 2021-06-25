<शैली गुरु>
/*
 * Resizable simple ram fileप्रणाली क्रम Linux.
 *
 * Copyright (C) 2000 Linus Torvalds.
 *               2000 Transmeta Corp.
 *
 * Usage limits added by David Gibson, Linuxcare Australia.
 * This file is released under the GPL.
 */

/*
 * NOTE! This fileप्रणाली is probably most useful
 * not as a real fileप्रणाली, but as an example of
 * how भव fileप्रणालीs can be written.
 *
 * It करोesn't get much simpler than this. Consider
 * that this file implements the full semantics of
 * a POSIX-compliant पढ़ो-ग_लिखो fileप्रणाली.
 *
 * Note in particular how the fileप्रणाली करोes not
 * need to implement any data काष्ठाures of its own
 * to keep track of the भव data: using the VFS
 * caches is sufficient.
 */

#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/backing-dev.h>
#समावेश <linux/ramfs.h>
#समावेश <linux/sched.h>
#समावेश <linux/parser.h>
#समावेश <linux/magic.h>
#समावेश <linux/slab.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/fs_context.h>
#समावेश <linux/fs_parser.h>
#समावेश "internal.h"

काष्ठा ramfs_mount_opts अणु
	umode_t mode;
पूर्ण;

काष्ठा ramfs_fs_info अणु
	काष्ठा ramfs_mount_opts mount_opts;
पूर्ण;

#घोषणा RAMFS_DEFAULT_MODE	0755

अटल स्थिर काष्ठा super_operations ramfs_ops;
अटल स्थिर काष्ठा inode_operations ramfs_dir_inode_operations;

अटल स्थिर काष्ठा address_space_operations ramfs_aops = अणु
	.पढ़ोpage	= simple_पढ़ोpage,
	.ग_लिखो_begin	= simple_ग_लिखो_begin,
	.ग_लिखो_end	= simple_ग_लिखो_end,
	.set_page_dirty	= __set_page_dirty_no_ग_लिखोback,
पूर्ण;

काष्ठा inode *ramfs_get_inode(काष्ठा super_block *sb,
				स्थिर काष्ठा inode *dir, umode_t mode, dev_t dev)
अणु
	काष्ठा inode * inode = new_inode(sb);

	अगर (inode) अणु
		inode->i_ino = get_next_ino();
		inode_init_owner(&init_user_ns, inode, dir, mode);
		inode->i_mapping->a_ops = &ramfs_aops;
		mapping_set_gfp_mask(inode->i_mapping, GFP_HIGHUSER);
		mapping_set_unevictable(inode->i_mapping);
		inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
		चयन (mode & S_IFMT) अणु
		शेष:
			init_special_inode(inode, mode, dev);
			अवरोध;
		हाल S_IFREG:
			inode->i_op = &ramfs_file_inode_operations;
			inode->i_fop = &ramfs_file_operations;
			अवरोध;
		हाल S_IFसूची:
			inode->i_op = &ramfs_dir_inode_operations;
			inode->i_fop = &simple_dir_operations;

			/* directory inodes start off with i_nlink == 2 (क्रम "." entry) */
			inc_nlink(inode);
			अवरोध;
		हाल S_IFLNK:
			inode->i_op = &page_symlink_inode_operations;
			inode_nohighmem(inode);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस inode;
पूर्ण

/*
 * File creation. Allocate an inode, and we're करोne..
 */
/* SMP-safe */
अटल पूर्णांक
ramfs_mknod(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
	    काष्ठा dentry *dentry, umode_t mode, dev_t dev)
अणु
	काष्ठा inode * inode = ramfs_get_inode(dir->i_sb, dir, mode, dev);
	पूर्णांक error = -ENOSPC;

	अगर (inode) अणु
		d_instantiate(dentry, inode);
		dget(dentry);	/* Extra count - pin the dentry in core */
		error = 0;
		dir->i_mसमय = dir->i_स_समय = current_समय(dir);
	पूर्ण
	वापस error;
पूर्ण

अटल पूर्णांक ramfs_सूची_गढ़ो(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
		       काष्ठा dentry *dentry, umode_t mode)
अणु
	पूर्णांक retval = ramfs_mknod(&init_user_ns, dir, dentry, mode | S_IFसूची, 0);
	अगर (!retval)
		inc_nlink(dir);
	वापस retval;
पूर्ण

अटल पूर्णांक ramfs_create(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			काष्ठा dentry *dentry, umode_t mode, bool excl)
अणु
	वापस ramfs_mknod(&init_user_ns, dir, dentry, mode | S_IFREG, 0);
पूर्ण

अटल पूर्णांक ramfs_symlink(काष्ठा user_namespace *mnt_userns, काष्ठा inode *dir,
			 काष्ठा dentry *dentry, स्थिर अक्षर *symname)
अणु
	काष्ठा inode *inode;
	पूर्णांक error = -ENOSPC;

	inode = ramfs_get_inode(dir->i_sb, dir, S_IFLNK|S_IRWXUGO, 0);
	अगर (inode) अणु
		पूर्णांक l = म_माप(symname)+1;
		error = page_symlink(inode, symname, l);
		अगर (!error) अणु
			d_instantiate(dentry, inode);
			dget(dentry);
			dir->i_mसमय = dir->i_स_समय = current_समय(dir);
		पूर्ण अन्यथा
			iput(inode);
	पूर्ण
	वापस error;
पूर्ण

अटल पूर्णांक ramfs_क्षणिक_ख(काष्ठा user_namespace *mnt_userns,
			 काष्ठा inode *dir, काष्ठा dentry *dentry, umode_t mode)
अणु
	काष्ठा inode *inode;

	inode = ramfs_get_inode(dir->i_sb, dir, mode, 0);
	अगर (!inode)
		वापस -ENOSPC;
	d_क्षणिक_ख(dentry, inode);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा inode_operations ramfs_dir_inode_operations = अणु
	.create		= ramfs_create,
	.lookup		= simple_lookup,
	.link		= simple_link,
	.unlink		= simple_unlink,
	.symlink	= ramfs_symlink,
	.सूची_गढ़ो		= ramfs_सूची_गढ़ो,
	.सूची_हटाओ		= simple_सूची_हटाओ,
	.mknod		= ramfs_mknod,
	.नाम		= simple_नाम,
	.क्षणिक_ख	= ramfs_क्षणिक_ख,
पूर्ण;

/*
 * Display the mount options in /proc/mounts.
 */
अटल पूर्णांक ramfs_show_options(काष्ठा seq_file *m, काष्ठा dentry *root)
अणु
	काष्ठा ramfs_fs_info *fsi = root->d_sb->s_fs_info;

	अगर (fsi->mount_opts.mode != RAMFS_DEFAULT_MODE)
		seq_म_लिखो(m, ",mode=%o", fsi->mount_opts.mode);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा super_operations ramfs_ops = अणु
	.statfs		= simple_statfs,
	.drop_inode	= generic_delete_inode,
	.show_options	= ramfs_show_options,
पूर्ण;

क्रमागत ramfs_param अणु
	Opt_mode,
पूर्ण;

स्थिर काष्ठा fs_parameter_spec ramfs_fs_parameters[] = अणु
	fsparam_u32oct("mode",	Opt_mode),
	अणुपूर्ण
पूर्ण;

अटल पूर्णांक ramfs_parse_param(काष्ठा fs_context *fc, काष्ठा fs_parameter *param)
अणु
	काष्ठा fs_parse_result result;
	काष्ठा ramfs_fs_info *fsi = fc->s_fs_info;
	पूर्णांक opt;

	opt = fs_parse(fc, ramfs_fs_parameters, param, &result);
	अगर (opt < 0) अणु
		/*
		 * We might like to report bad mount options here;
		 * but traditionally ramfs has ignored all mount options,
		 * and as it is used as a !CONFIG_SHMEM simple substitute
		 * क्रम पंचांगpfs, better जारी to ignore other mount options.
		 */
		अगर (opt == -ENOPARAM)
			opt = 0;
		वापस opt;
	पूर्ण

	चयन (opt) अणु
	हाल Opt_mode:
		fsi->mount_opts.mode = result.uपूर्णांक_32 & S_IALLUGO;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ramfs_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fc)
अणु
	काष्ठा ramfs_fs_info *fsi = sb->s_fs_info;
	काष्ठा inode *inode;

	sb->s_maxbytes		= MAX_LFS_खाताSIZE;
	sb->s_blocksize		= PAGE_SIZE;
	sb->s_blocksize_bits	= PAGE_SHIFT;
	sb->s_magic		= RAMFS_MAGIC;
	sb->s_op		= &ramfs_ops;
	sb->s_समय_gran		= 1;

	inode = ramfs_get_inode(sb, शून्य, S_IFसूची | fsi->mount_opts.mode, 0);
	sb->s_root = d_make_root(inode);
	अगर (!sb->s_root)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक ramfs_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_nodev(fc, ramfs_fill_super);
पूर्ण

अटल व्योम ramfs_मुक्त_fc(काष्ठा fs_context *fc)
अणु
	kमुक्त(fc->s_fs_info);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations ramfs_context_ops = अणु
	.मुक्त		= ramfs_मुक्त_fc,
	.parse_param	= ramfs_parse_param,
	.get_tree	= ramfs_get_tree,
पूर्ण;

पूर्णांक ramfs_init_fs_context(काष्ठा fs_context *fc)
अणु
	काष्ठा ramfs_fs_info *fsi;

	fsi = kzalloc(माप(*fsi), GFP_KERNEL);
	अगर (!fsi)
		वापस -ENOMEM;

	fsi->mount_opts.mode = RAMFS_DEFAULT_MODE;
	fc->s_fs_info = fsi;
	fc->ops = &ramfs_context_ops;
	वापस 0;
पूर्ण

अटल व्योम ramfs_समाप्त_sb(काष्ठा super_block *sb)
अणु
	kमुक्त(sb->s_fs_info);
	समाप्त_litter_super(sb);
पूर्ण

अटल काष्ठा file_प्रणाली_type ramfs_fs_type = अणु
	.name		= "ramfs",
	.init_fs_context = ramfs_init_fs_context,
	.parameters	= ramfs_fs_parameters,
	.समाप्त_sb	= ramfs_समाप्त_sb,
	.fs_flags	= FS_USERNS_MOUNT,
पूर्ण;

अटल पूर्णांक __init init_ramfs_fs(व्योम)
अणु
	वापस रेजिस्टर_fileप्रणाली(&ramfs_fs_type);
पूर्ण
fs_initcall(init_ramfs_fs);
