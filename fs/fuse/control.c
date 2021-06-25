<शैली गुरु>
/*
  FUSE: Fileप्रणाली in Userspace
  Copyright (C) 2001-2008  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.
*/

#समावेश "fuse_i.h"

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/fs_context.h>

#घोषणा FUSE_CTL_SUPER_MAGIC 0x65735543

/*
 * This is non-शून्य when the single instance of the control fileप्रणाली
 * exists.  Protected by fuse_mutex
 */
अटल काष्ठा super_block *fuse_control_sb;

अटल काष्ठा fuse_conn *fuse_ctl_file_conn_get(काष्ठा file *file)
अणु
	काष्ठा fuse_conn *fc;
	mutex_lock(&fuse_mutex);
	fc = file_inode(file)->i_निजी;
	अगर (fc)
		fc = fuse_conn_get(fc);
	mutex_unlock(&fuse_mutex);
	वापस fc;
पूर्ण

अटल sमाप_प्रकार fuse_conn_पात_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा fuse_conn *fc = fuse_ctl_file_conn_get(file);
	अगर (fc) अणु
		अगर (fc->पात_err)
			fc->पातed = true;
		fuse_पात_conn(fc);
		fuse_conn_put(fc);
	पूर्ण
	वापस count;
पूर्ण

अटल sमाप_प्रकार fuse_conn_रुकोing_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				      माप_प्रकार len, loff_t *ppos)
अणु
	अक्षर पंचांगp[32];
	माप_प्रकार size;

	अगर (!*ppos) अणु
		दीर्घ value;
		काष्ठा fuse_conn *fc = fuse_ctl_file_conn_get(file);
		अगर (!fc)
			वापस 0;

		value = atomic_पढ़ो(&fc->num_रुकोing);
		file->निजी_data = (व्योम *)value;
		fuse_conn_put(fc);
	पूर्ण
	size = प्र_लिखो(पंचांगp, "%ld\n", (दीर्घ)file->निजी_data);
	वापस simple_पढ़ो_from_buffer(buf, len, ppos, पंचांगp, size);
पूर्ण

अटल sमाप_प्रकार fuse_conn_limit_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
				    माप_प्रकार len, loff_t *ppos, अचिन्हित val)
अणु
	अक्षर पंचांगp[32];
	माप_प्रकार size = प्र_लिखो(पंचांगp, "%u\n", val);

	वापस simple_पढ़ो_from_buffer(buf, len, ppos, पंचांगp, size);
पूर्ण

अटल sमाप_प्रकार fuse_conn_limit_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
				     माप_प्रकार count, loff_t *ppos, अचिन्हित *val,
				     अचिन्हित global_limit)
अणु
	अचिन्हित दीर्घ t;
	अचिन्हित limit = (1 << 16) - 1;
	पूर्णांक err;

	अगर (*ppos)
		वापस -EINVAL;

	err = kम_से_अदीर्घ_from_user(buf, count, 0, &t);
	अगर (err)
		वापस err;

	अगर (!capable(CAP_SYS_ADMIN))
		limit = min(limit, global_limit);

	अगर (t > limit)
		वापस -EINVAL;

	*val = t;

	वापस count;
पूर्ण

अटल sमाप_प्रकार fuse_conn_max_background_पढ़ो(काष्ठा file *file,
					     अक्षर __user *buf, माप_प्रकार len,
					     loff_t *ppos)
अणु
	काष्ठा fuse_conn *fc;
	अचिन्हित val;

	fc = fuse_ctl_file_conn_get(file);
	अगर (!fc)
		वापस 0;

	val = READ_ONCE(fc->max_background);
	fuse_conn_put(fc);

	वापस fuse_conn_limit_पढ़ो(file, buf, len, ppos, val);
पूर्ण

अटल sमाप_प्रकार fuse_conn_max_background_ग_लिखो(काष्ठा file *file,
					      स्थिर अक्षर __user *buf,
					      माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित val;
	sमाप_प्रकार ret;

	ret = fuse_conn_limit_ग_लिखो(file, buf, count, ppos, &val,
				    max_user_bgreq);
	अगर (ret > 0) अणु
		काष्ठा fuse_conn *fc = fuse_ctl_file_conn_get(file);
		अगर (fc) अणु
			spin_lock(&fc->bg_lock);
			fc->max_background = val;
			fc->blocked = fc->num_background >= fc->max_background;
			अगर (!fc->blocked)
				wake_up(&fc->blocked_रुकोq);
			spin_unlock(&fc->bg_lock);
			fuse_conn_put(fc);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल sमाप_प्रकार fuse_conn_congestion_threshold_पढ़ो(काष्ठा file *file,
						   अक्षर __user *buf, माप_प्रकार len,
						   loff_t *ppos)
अणु
	काष्ठा fuse_conn *fc;
	अचिन्हित val;

	fc = fuse_ctl_file_conn_get(file);
	अगर (!fc)
		वापस 0;

	val = READ_ONCE(fc->congestion_threshold);
	fuse_conn_put(fc);

	वापस fuse_conn_limit_पढ़ो(file, buf, len, ppos, val);
पूर्ण

अटल sमाप_प्रकार fuse_conn_congestion_threshold_ग_लिखो(काष्ठा file *file,
						    स्थिर अक्षर __user *buf,
						    माप_प्रकार count, loff_t *ppos)
अणु
	अचिन्हित val;
	काष्ठा fuse_conn *fc;
	काष्ठा fuse_mount *fm;
	sमाप_प्रकार ret;

	ret = fuse_conn_limit_ग_लिखो(file, buf, count, ppos, &val,
				    max_user_congthresh);
	अगर (ret <= 0)
		जाओ out;
	fc = fuse_ctl_file_conn_get(file);
	अगर (!fc)
		जाओ out;

	करोwn_पढ़ो(&fc->समाप्तsb);
	spin_lock(&fc->bg_lock);
	fc->congestion_threshold = val;

	/*
	 * Get any fuse_mount beदीर्घing to this fuse_conn; s_bdi is
	 * shared between all of them
	 */

	अगर (!list_empty(&fc->mounts)) अणु
		fm = list_first_entry(&fc->mounts, काष्ठा fuse_mount, fc_entry);
		अगर (fc->num_background < fc->congestion_threshold) अणु
			clear_bdi_congested(fm->sb->s_bdi, BLK_RW_SYNC);
			clear_bdi_congested(fm->sb->s_bdi, BLK_RW_ASYNC);
		पूर्ण अन्यथा अणु
			set_bdi_congested(fm->sb->s_bdi, BLK_RW_SYNC);
			set_bdi_congested(fm->sb->s_bdi, BLK_RW_ASYNC);
		पूर्ण
	पूर्ण
	spin_unlock(&fc->bg_lock);
	up_पढ़ो(&fc->समाप्तsb);
	fuse_conn_put(fc);
out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations fuse_ctl_पात_ops = अणु
	.खोलो = nonseekable_खोलो,
	.ग_लिखो = fuse_conn_पात_ग_लिखो,
	.llseek = no_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations fuse_ctl_रुकोing_ops = अणु
	.खोलो = nonseekable_खोलो,
	.पढ़ो = fuse_conn_रुकोing_पढ़ो,
	.llseek = no_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations fuse_conn_max_background_ops = अणु
	.खोलो = nonseekable_खोलो,
	.पढ़ो = fuse_conn_max_background_पढ़ो,
	.ग_लिखो = fuse_conn_max_background_ग_लिखो,
	.llseek = no_llseek,
पूर्ण;

अटल स्थिर काष्ठा file_operations fuse_conn_congestion_threshold_ops = अणु
	.खोलो = nonseekable_खोलो,
	.पढ़ो = fuse_conn_congestion_threshold_पढ़ो,
	.ग_लिखो = fuse_conn_congestion_threshold_ग_लिखो,
	.llseek = no_llseek,
पूर्ण;

अटल काष्ठा dentry *fuse_ctl_add_dentry(काष्ठा dentry *parent,
					  काष्ठा fuse_conn *fc,
					  स्थिर अक्षर *name,
					  पूर्णांक mode, पूर्णांक nlink,
					  स्थिर काष्ठा inode_operations *iop,
					  स्थिर काष्ठा file_operations *fop)
अणु
	काष्ठा dentry *dentry;
	काष्ठा inode *inode;

	BUG_ON(fc->ctl_ndents >= FUSE_CTL_NUM_DENTRIES);
	dentry = d_alloc_name(parent, name);
	अगर (!dentry)
		वापस शून्य;

	inode = new_inode(fuse_control_sb);
	अगर (!inode) अणु
		dput(dentry);
		वापस शून्य;
	पूर्ण

	inode->i_ino = get_next_ino();
	inode->i_mode = mode;
	inode->i_uid = fc->user_id;
	inode->i_gid = fc->group_id;
	inode->i_aसमय = inode->i_mसमय = inode->i_स_समय = current_समय(inode);
	/* setting ->i_op to शून्य is not allowed */
	अगर (iop)
		inode->i_op = iop;
	inode->i_fop = fop;
	set_nlink(inode, nlink);
	inode->i_निजी = fc;
	d_add(dentry, inode);

	fc->ctl_dentry[fc->ctl_ndents++] = dentry;

	वापस dentry;
पूर्ण

/*
 * Add a connection to the control fileप्रणाली (अगर it exists).  Caller
 * must hold fuse_mutex
 */
पूर्णांक fuse_ctl_add_conn(काष्ठा fuse_conn *fc)
अणु
	काष्ठा dentry *parent;
	अक्षर name[32];

	अगर (!fuse_control_sb)
		वापस 0;

	parent = fuse_control_sb->s_root;
	inc_nlink(d_inode(parent));
	प्र_लिखो(name, "%u", fc->dev);
	parent = fuse_ctl_add_dentry(parent, fc, name, S_IFसूची | 0500, 2,
				     &simple_dir_inode_operations,
				     &simple_dir_operations);
	अगर (!parent)
		जाओ err;

	अगर (!fuse_ctl_add_dentry(parent, fc, "waiting", S_IFREG | 0400, 1,
				 शून्य, &fuse_ctl_रुकोing_ops) ||
	    !fuse_ctl_add_dentry(parent, fc, "abort", S_IFREG | 0200, 1,
				 शून्य, &fuse_ctl_पात_ops) ||
	    !fuse_ctl_add_dentry(parent, fc, "max_background", S_IFREG | 0600,
				 1, शून्य, &fuse_conn_max_background_ops) ||
	    !fuse_ctl_add_dentry(parent, fc, "congestion_threshold",
				 S_IFREG | 0600, 1, शून्य,
				 &fuse_conn_congestion_threshold_ops))
		जाओ err;

	वापस 0;

 err:
	fuse_ctl_हटाओ_conn(fc);
	वापस -ENOMEM;
पूर्ण

/*
 * Remove a connection from the control fileप्रणाली (अगर it exists).
 * Caller must hold fuse_mutex
 */
व्योम fuse_ctl_हटाओ_conn(काष्ठा fuse_conn *fc)
अणु
	पूर्णांक i;

	अगर (!fuse_control_sb)
		वापस;

	क्रम (i = fc->ctl_ndents - 1; i >= 0; i--) अणु
		काष्ठा dentry *dentry = fc->ctl_dentry[i];
		d_inode(dentry)->i_निजी = शून्य;
		अगर (!i) अणु
			/* Get rid of submounts: */
			d_invalidate(dentry);
		पूर्ण
		dput(dentry);
	पूर्ण
	drop_nlink(d_inode(fuse_control_sb->s_root));
पूर्ण

अटल पूर्णांक fuse_ctl_fill_super(काष्ठा super_block *sb, काष्ठा fs_context *fctx)
अणु
	अटल स्थिर काष्ठा tree_descr empty_descr = अणु""पूर्ण;
	काष्ठा fuse_conn *fc;
	पूर्णांक err;

	err = simple_fill_super(sb, FUSE_CTL_SUPER_MAGIC, &empty_descr);
	अगर (err)
		वापस err;

	mutex_lock(&fuse_mutex);
	BUG_ON(fuse_control_sb);
	fuse_control_sb = sb;
	list_क्रम_each_entry(fc, &fuse_conn_list, entry) अणु
		err = fuse_ctl_add_conn(fc);
		अगर (err) अणु
			fuse_control_sb = शून्य;
			mutex_unlock(&fuse_mutex);
			वापस err;
		पूर्ण
	पूर्ण
	mutex_unlock(&fuse_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक fuse_ctl_get_tree(काष्ठा fs_context *fc)
अणु
	वापस get_tree_single(fc, fuse_ctl_fill_super);
पूर्ण

अटल स्थिर काष्ठा fs_context_operations fuse_ctl_context_ops = अणु
	.get_tree	= fuse_ctl_get_tree,
पूर्ण;

अटल पूर्णांक fuse_ctl_init_fs_context(काष्ठा fs_context *fc)
अणु
	fc->ops = &fuse_ctl_context_ops;
	वापस 0;
पूर्ण

अटल व्योम fuse_ctl_समाप्त_sb(काष्ठा super_block *sb)
अणु
	काष्ठा fuse_conn *fc;

	mutex_lock(&fuse_mutex);
	fuse_control_sb = शून्य;
	list_क्रम_each_entry(fc, &fuse_conn_list, entry)
		fc->ctl_ndents = 0;
	mutex_unlock(&fuse_mutex);

	समाप्त_litter_super(sb);
पूर्ण

अटल काष्ठा file_प्रणाली_type fuse_ctl_fs_type = अणु
	.owner		= THIS_MODULE,
	.name		= "fusectl",
	.init_fs_context = fuse_ctl_init_fs_context,
	.समाप्त_sb	= fuse_ctl_समाप्त_sb,
पूर्ण;
MODULE_ALIAS_FS("fusectl");

पूर्णांक __init fuse_ctl_init(व्योम)
अणु
	वापस रेजिस्टर_fileप्रणाली(&fuse_ctl_fs_type);
पूर्ण

व्योम __निकास fuse_ctl_cleanup(व्योम)
अणु
	unरेजिस्टर_fileप्रणाली(&fuse_ctl_fs_type);
पूर्ण
