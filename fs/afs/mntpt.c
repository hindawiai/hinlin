<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* mountpoपूर्णांक management
 *
 * Copyright (C) 2002 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/fs.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/gfp.h>
#समावेश <linux/fs_context.h>
#समावेश "internal.h"


अटल काष्ठा dentry *afs_mntpt_lookup(काष्ठा inode *dir,
				       काष्ठा dentry *dentry,
				       अचिन्हित पूर्णांक flags);
अटल पूर्णांक afs_mntpt_खोलो(काष्ठा inode *inode, काष्ठा file *file);
अटल व्योम afs_mntpt_expiry_समयd_out(काष्ठा work_काष्ठा *work);

स्थिर काष्ठा file_operations afs_mntpt_file_operations = अणु
	.खोलो		= afs_mntpt_खोलो,
	.llseek		= noop_llseek,
पूर्ण;

स्थिर काष्ठा inode_operations afs_mntpt_inode_operations = अणु
	.lookup		= afs_mntpt_lookup,
	.पढ़ोlink	= page_पढ़ोlink,
	.getattr	= afs_getattr,
पूर्ण;

स्थिर काष्ठा inode_operations afs_स्वतःcell_inode_operations = अणु
	.getattr	= afs_getattr,
पूर्ण;

अटल LIST_HEAD(afs_vfsmounts);
अटल DECLARE_DELAYED_WORK(afs_mntpt_expiry_समयr, afs_mntpt_expiry_समयd_out);

अटल अचिन्हित दीर्घ afs_mntpt_expiry_समयout = 10 * 60;

अटल स्थिर अक्षर afs_root_volume[] = "root.cell";

/*
 * no valid lookup procedure on this sort of dir
 */
अटल काष्ठा dentry *afs_mntpt_lookup(काष्ठा inode *dir,
				       काष्ठा dentry *dentry,
				       अचिन्हित पूर्णांक flags)
अणु
	_enter("%p,%p{%pd2}", dir, dentry, dentry);
	वापस ERR_PTR(-EREMOTE);
पूर्ण

/*
 * no valid खोलो procedure on this sort of dir
 */
अटल पूर्णांक afs_mntpt_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	_enter("%p,%p{%pD2}", inode, file, file);
	वापस -EREMOTE;
पूर्ण

/*
 * Set the parameters क्रम the proposed superblock.
 */
अटल पूर्णांक afs_mntpt_set_params(काष्ठा fs_context *fc, काष्ठा dentry *mntpt)
अणु
	काष्ठा afs_fs_context *ctx = fc->fs_निजी;
	काष्ठा afs_super_info *src_as = AFS_FS_S(mntpt->d_sb);
	काष्ठा afs_vnode *vnode = AFS_FS_I(d_inode(mntpt));
	काष्ठा afs_cell *cell;
	स्थिर अक्षर *p;
	पूर्णांक ret;

	अगर (fc->net_ns != src_as->net_ns) अणु
		put_net(fc->net_ns);
		fc->net_ns = get_net(src_as->net_ns);
	पूर्ण

	अगर (src_as->volume && src_as->volume->type == AFSVL_RWVOL) अणु
		ctx->type = AFSVL_RWVOL;
		ctx->क्रमce = true;
	पूर्ण
	अगर (ctx->cell) अणु
		afs_unuse_cell(ctx->net, ctx->cell, afs_cell_trace_unuse_mntpt);
		ctx->cell = शून्य;
	पूर्ण
	अगर (test_bit(AFS_VNODE_PSEUDOसूची, &vnode->flags)) अणु
		/* अगर the directory is a pseuकरो directory, use the d_name */
		अचिन्हित size = mntpt->d_name.len;

		अगर (size < 2)
			वापस -ENOENT;

		p = mntpt->d_name.name;
		अगर (mntpt->d_name.name[0] == '.') अणु
			size--;
			p++;
			ctx->type = AFSVL_RWVOL;
			ctx->क्रमce = true;
		पूर्ण
		अगर (size > AFS_MAXCELLNAME)
			वापस -ENAMETOOLONG;

		cell = afs_lookup_cell(ctx->net, p, size, शून्य, false);
		अगर (IS_ERR(cell)) अणु
			pr_err("kAFS: unable to lookup cell '%pd'\n", mntpt);
			वापस PTR_ERR(cell);
		पूर्ण
		ctx->cell = cell;

		ctx->volname = afs_root_volume;
		ctx->volnamesz = माप(afs_root_volume) - 1;
	पूर्ण अन्यथा अणु
		/* पढ़ो the contents of the AFS special symlink */
		काष्ठा page *page;
		loff_t size = i_size_पढ़ो(d_inode(mntpt));
		अक्षर *buf;

		अगर (src_as->cell)
			ctx->cell = afs_use_cell(src_as->cell, afs_cell_trace_use_mntpt);

		अगर (size < 2 || size > PAGE_SIZE - 1)
			वापस -EINVAL;

		page = पढ़ो_mapping_page(d_inode(mntpt)->i_mapping, 0, शून्य);
		अगर (IS_ERR(page))
			वापस PTR_ERR(page);

		अगर (PageError(page)) अणु
			ret = afs_bad(AFS_FS_I(d_inode(mntpt)), afs_file_error_mntpt);
			put_page(page);
			वापस ret;
		पूर्ण

		buf = kmap(page);
		ret = -EINVAL;
		अगर (buf[size - 1] == '.')
			ret = vfs_parse_fs_string(fc, "source", buf, size - 1);
		kunmap(page);
		put_page(page);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * create a vfsmount to be स्वतःmounted
 */
अटल काष्ठा vfsmount *afs_mntpt_करो_स्वतःmount(काष्ठा dentry *mntpt)
अणु
	काष्ठा fs_context *fc;
	काष्ठा vfsmount *mnt;
	पूर्णांक ret;

	BUG_ON(!d_inode(mntpt));

	fc = fs_context_क्रम_submount(&afs_fs_type, mntpt);
	अगर (IS_ERR(fc))
		वापस ERR_CAST(fc);

	ret = afs_mntpt_set_params(fc, mntpt);
	अगर (!ret)
		mnt = fc_mount(fc);
	अन्यथा
		mnt = ERR_PTR(ret);

	put_fs_context(fc);
	वापस mnt;
पूर्ण

/*
 * handle an स्वतःmount poपूर्णांक
 */
काष्ठा vfsmount *afs_d_स्वतःmount(काष्ठा path *path)
अणु
	काष्ठा vfsmount *newmnt;

	_enter("{%pd}", path->dentry);

	newmnt = afs_mntpt_करो_स्वतःmount(path->dentry);
	अगर (IS_ERR(newmnt))
		वापस newmnt;

	mntget(newmnt); /* prevent immediate expiration */
	mnt_set_expiry(newmnt, &afs_vfsmounts);
	queue_delayed_work(afs_wq, &afs_mntpt_expiry_समयr,
			   afs_mntpt_expiry_समयout * HZ);
	_leave(" = %p", newmnt);
	वापस newmnt;
पूर्ण

/*
 * handle mountpoपूर्णांक expiry समयr going off
 */
अटल व्योम afs_mntpt_expiry_समयd_out(काष्ठा work_काष्ठा *work)
अणु
	_enter("");

	अगर (!list_empty(&afs_vfsmounts)) अणु
		mark_mounts_क्रम_expiry(&afs_vfsmounts);
		queue_delayed_work(afs_wq, &afs_mntpt_expiry_समयr,
				   afs_mntpt_expiry_समयout * HZ);
	पूर्ण

	_leave("");
पूर्ण

/*
 * समाप्त the AFS mountpoपूर्णांक समयr अगर it's still running
 */
व्योम afs_mntpt_समाप्त_समयr(व्योम)
अणु
	_enter("");

	ASSERT(list_empty(&afs_vfsmounts));
	cancel_delayed_work_sync(&afs_mntpt_expiry_समयr);
पूर्ण
