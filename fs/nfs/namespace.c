<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/nfs/namespace.c
 *
 * Copyright (C) 2005 Trond Myklebust <Trond.Myklebust@netapp.com>
 * - Modअगरied by David Howells <dhowells@redhat.com>
 *
 * NFS namespace
 */

#समावेश <linux/module.h>
#समावेश <linux/dcache.h>
#समावेश <linux/gfp.h>
#समावेश <linux/mount.h>
#समावेश <linux/namei.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/vfs.h>
#समावेश <linux/sunrpc/gss_api.h>
#समावेश "internal.h"
#समावेश "nfs.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_VFS

अटल व्योम nfs_expire_स्वतःmounts(काष्ठा work_काष्ठा *work);

अटल LIST_HEAD(nfs_स्वतःmount_list);
अटल DECLARE_DELAYED_WORK(nfs_स्वतःmount_task, nfs_expire_स्वतःmounts);
पूर्णांक nfs_mountpoपूर्णांक_expiry_समयout = 500 * HZ;

/*
 * nfs_path - reस्थिरruct the path given an arbitrary dentry
 * @base - used to वापस poपूर्णांकer to the end of devname part of path
 * @dentry_in - poपूर्णांकer to dentry
 * @buffer - result buffer
 * @buflen_in - length of buffer
 * @flags - options (see below)
 *
 * Helper function क्रम स्थिरructing the server pathname
 * by arbitrary hashed dentry.
 *
 * This is मुख्यly क्रम use in figuring out the path on the
 * server side when स्वतःmounting on top of an existing partition
 * and in generating /proc/mounts and मित्रs.
 *
 * Supported flags:
 * NFS_PATH_CANONICAL: ensure there is exactly one slash after
 *		       the original device (export) name
 *		       (अगर unset, the original name is वापसed verbatim)
 */
अक्षर *nfs_path(अक्षर **p, काष्ठा dentry *dentry_in, अक्षर *buffer,
	       sमाप_प्रकार buflen_in, अचिन्हित flags)
अणु
	अक्षर *end;
	पूर्णांक namelen;
	अचिन्हित seq;
	स्थिर अक्षर *base;
	काष्ठा dentry *dentry;
	sमाप_प्रकार buflen;

नाम_retry:
	buflen = buflen_in;
	dentry = dentry_in;
	end = buffer+buflen;
	*--end = '\0';
	buflen--;

	seq = पढ़ो_seqbegin(&नाम_lock);
	rcu_पढ़ो_lock();
	जबतक (1) अणु
		spin_lock(&dentry->d_lock);
		अगर (IS_ROOT(dentry))
			अवरोध;
		namelen = dentry->d_name.len;
		buflen -= namelen + 1;
		अगर (buflen < 0)
			जाओ Eदीर्घ_unlock;
		end -= namelen;
		स_नकल(end, dentry->d_name.name, namelen);
		*--end = '/';
		spin_unlock(&dentry->d_lock);
		dentry = dentry->d_parent;
	पूर्ण
	अगर (पढ़ो_seqretry(&नाम_lock, seq)) अणु
		spin_unlock(&dentry->d_lock);
		rcu_पढ़ो_unlock();
		जाओ नाम_retry;
	पूर्ण
	अगर ((flags & NFS_PATH_CANONICAL) && *end != '/') अणु
		अगर (--buflen < 0) अणु
			spin_unlock(&dentry->d_lock);
			rcu_पढ़ो_unlock();
			जाओ Eदीर्घ;
		पूर्ण
		*--end = '/';
	पूर्ण
	*p = end;
	base = dentry->d_fsdata;
	अगर (!base) अणु
		spin_unlock(&dentry->d_lock);
		rcu_पढ़ो_unlock();
		WARN_ON(1);
		वापस end;
	पूर्ण
	namelen = म_माप(base);
	अगर (*end == '/') अणु
		/* Strip off excess slashes in base string */
		जबतक (namelen > 0 && base[namelen - 1] == '/')
			namelen--;
	पूर्ण
	buflen -= namelen;
	अगर (buflen < 0) अणु
		spin_unlock(&dentry->d_lock);
		rcu_पढ़ो_unlock();
		जाओ Eदीर्घ;
	पूर्ण
	end -= namelen;
	स_नकल(end, base, namelen);
	spin_unlock(&dentry->d_lock);
	rcu_पढ़ो_unlock();
	वापस end;
Eदीर्घ_unlock:
	spin_unlock(&dentry->d_lock);
	rcu_पढ़ो_unlock();
	अगर (पढ़ो_seqretry(&नाम_lock, seq))
		जाओ नाम_retry;
Eदीर्घ:
	वापस ERR_PTR(-ENAMETOOLONG);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_path);

/*
 * nfs_d_स्वतःmount - Handle crossing a mountpoपूर्णांक on the server
 * @path - The mountpoपूर्णांक
 *
 * When we encounter a mountpoपूर्णांक on the server, we want to set up
 * a mountpoपूर्णांक on the client too, to prevent inode numbers from
 * colliding, and to allow "df" to work properly.
 * On NFSv4, we also want to allow क्रम the fact that dअगरferent
 * fileप्रणालीs may be migrated to dअगरferent servers in a failover
 * situation, and that dअगरferent fileप्रणालीs may want to use
 * dअगरferent security flavours.
 */
काष्ठा vfsmount *nfs_d_स्वतःmount(काष्ठा path *path)
अणु
	काष्ठा nfs_fs_context *ctx;
	काष्ठा fs_context *fc;
	काष्ठा vfsmount *mnt = ERR_PTR(-ENOMEM);
	काष्ठा nfs_server *server = NFS_SERVER(d_inode(path->dentry));
	काष्ठा nfs_client *client = server->nfs_client;
	पूर्णांक समयout = READ_ONCE(nfs_mountpoपूर्णांक_expiry_समयout);
	पूर्णांक ret;

	अगर (IS_ROOT(path->dentry))
		वापस ERR_PTR(-ESTALE);

	/* Open a new fileप्रणाली context, transferring parameters from the
	 * parent superblock, including the network namespace.
	 */
	fc = fs_context_क्रम_submount(path->mnt->mnt_sb->s_type, path->dentry);
	अगर (IS_ERR(fc))
		वापस ERR_CAST(fc);

	ctx = nfs_fc2context(fc);
	ctx->clone_data.dentry	= path->dentry;
	ctx->clone_data.sb	= path->dentry->d_sb;
	ctx->clone_data.fattr	= nfs_alloc_fattr();
	अगर (!ctx->clone_data.fattr)
		जाओ out_fc;

	अगर (fc->net_ns != client->cl_net) अणु
		put_net(fc->net_ns);
		fc->net_ns = get_net(client->cl_net);
	पूर्ण

	/* क्रम submounts we want the same server; referrals will reassign */
	स_नकल(&ctx->nfs_server.address, &client->cl_addr, client->cl_addrlen);
	ctx->nfs_server.addrlen	= client->cl_addrlen;
	ctx->nfs_server.port	= server->port;

	ctx->version		= client->rpc_ops->version;
	ctx->minorversion	= client->cl_minorversion;
	ctx->nfs_mod		= client->cl_nfs_mod;
	__module_get(ctx->nfs_mod->owner);

	ret = client->rpc_ops->submount(fc, server);
	अगर (ret < 0) अणु
		mnt = ERR_PTR(ret);
		जाओ out_fc;
	पूर्ण

	up_ग_लिखो(&fc->root->d_sb->s_umount);
	mnt = vfs_create_mount(fc);
	अगर (IS_ERR(mnt))
		जाओ out_fc;

	mntget(mnt); /* prevent immediate expiration */
	अगर (समयout <= 0)
		जाओ out_fc;

	mnt_set_expiry(mnt, &nfs_स्वतःmount_list);
	schedule_delayed_work(&nfs_स्वतःmount_task, समयout);

out_fc:
	put_fs_context(fc);
	वापस mnt;
पूर्ण

अटल पूर्णांक
nfs_namespace_getattr(काष्ठा user_namespace *mnt_userns,
		      स्थिर काष्ठा path *path, काष्ठा kstat *stat,
		      u32 request_mask, अचिन्हित पूर्णांक query_flags)
अणु
	अगर (NFS_FH(d_inode(path->dentry))->size != 0)
		वापस nfs_getattr(mnt_userns, path, stat, request_mask,
				   query_flags);
	generic_fillattr(&init_user_ns, d_inode(path->dentry), stat);
	वापस 0;
पूर्ण

अटल पूर्णांक
nfs_namespace_setattr(काष्ठा user_namespace *mnt_userns, काष्ठा dentry *dentry,
		      काष्ठा iattr *attr)
अणु
	अगर (NFS_FH(d_inode(dentry))->size != 0)
		वापस nfs_setattr(mnt_userns, dentry, attr);
	वापस -EACCES;
पूर्ण

स्थिर काष्ठा inode_operations nfs_mountpoपूर्णांक_inode_operations = अणु
	.getattr	= nfs_getattr,
	.setattr	= nfs_setattr,
पूर्ण;

स्थिर काष्ठा inode_operations nfs_referral_inode_operations = अणु
	.getattr	= nfs_namespace_getattr,
	.setattr	= nfs_namespace_setattr,
पूर्ण;

अटल व्योम nfs_expire_स्वतःmounts(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा list_head *list = &nfs_स्वतःmount_list;
	पूर्णांक समयout = READ_ONCE(nfs_mountpoपूर्णांक_expiry_समयout);

	mark_mounts_क्रम_expiry(list);
	अगर (!list_empty(list) && समयout > 0)
		schedule_delayed_work(&nfs_स्वतःmount_task, समयout);
पूर्ण

व्योम nfs_release_स्वतःmount_समयr(व्योम)
अणु
	अगर (list_empty(&nfs_स्वतःmount_list))
		cancel_delayed_work(&nfs_स्वतःmount_task);
पूर्ण

/**
 * nfs_करो_submount - set up mountpoपूर्णांक when crossing a fileप्रणाली boundary
 * @fc: poपूर्णांकer to काष्ठा nfs_fs_context
 *
 */
पूर्णांक nfs_करो_submount(काष्ठा fs_context *fc)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा dentry *dentry = ctx->clone_data.dentry;
	काष्ठा nfs_server *server;
	अक्षर *buffer, *p;
	पूर्णांक ret;

	/* create a new volume representation */
	server = ctx->nfs_mod->rpc_ops->clone_server(NFS_SB(ctx->clone_data.sb),
						     ctx->mntfh,
						     ctx->clone_data.fattr,
						     ctx->selected_flavor);

	अगर (IS_ERR(server))
		वापस PTR_ERR(server);

	ctx->server = server;

	buffer = kदो_स्मृति(4096, GFP_USER);
	अगर (!buffer)
		वापस -ENOMEM;

	ctx->पूर्णांकernal		= true;
	ctx->clone_data.inherited_bsize = ctx->clone_data.sb->s_blocksize_bits;

	p = nfs_devname(dentry, buffer, 4096);
	अगर (IS_ERR(p)) अणु
		nfs_errorf(fc, "NFS: Couldn't determine submount pathname");
		ret = PTR_ERR(p);
	पूर्ण अन्यथा अणु
		ret = vfs_parse_fs_string(fc, "source", p, buffer + 4096 - p);
		अगर (!ret)
			ret = vfs_get_tree(fc);
	पूर्ण
	kमुक्त(buffer);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(nfs_करो_submount);

पूर्णांक nfs_submount(काष्ठा fs_context *fc, काष्ठा nfs_server *server)
अणु
	काष्ठा nfs_fs_context *ctx = nfs_fc2context(fc);
	काष्ठा dentry *dentry = ctx->clone_data.dentry;
	काष्ठा dentry *parent = dget_parent(dentry);
	पूर्णांक err;

	/* Look it up again to get its attributes */
	err = server->nfs_client->rpc_ops->lookup(d_inode(parent), dentry,
						  ctx->mntfh, ctx->clone_data.fattr,
						  शून्य);
	dput(parent);
	अगर (err != 0)
		वापस err;

	ctx->selected_flavor = server->client->cl_auth->au_flavor;
	वापस nfs_करो_submount(fc);
पूर्ण
EXPORT_SYMBOL_GPL(nfs_submount);

अटल पूर्णांक param_set_nfs_समयout(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	दीर्घ num;
	पूर्णांक ret;

	अगर (!val)
		वापस -EINVAL;
	ret = kम_से_दीर्घ(val, 0, &num);
	अगर (ret)
		वापस -EINVAL;
	अगर (num > 0) अणु
		अगर (num >= पूर्णांक_उच्च / HZ)
			num = पूर्णांक_उच्च;
		अन्यथा
			num *= HZ;
		*((पूर्णांक *)kp->arg) = num;
		अगर (!list_empty(&nfs_स्वतःmount_list))
			mod_delayed_work(प्रणाली_wq, &nfs_स्वतःmount_task, num);
	पूर्ण अन्यथा अणु
		*((पूर्णांक *)kp->arg) = -1*HZ;
		cancel_delayed_work(&nfs_स्वतःmount_task);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक param_get_nfs_समयout(अक्षर *buffer, स्थिर काष्ठा kernel_param *kp)
अणु
	दीर्घ num = *((पूर्णांक *)kp->arg);

	अगर (num > 0) अणु
		अगर (num >= पूर्णांक_उच्च - (HZ - 1))
			num = पूर्णांक_उच्च / HZ;
		अन्यथा
			num = (num + (HZ - 1)) / HZ;
	पूर्ण अन्यथा
		num = -1;
	वापस scnम_लिखो(buffer, PAGE_SIZE, "%li\n", num);
पूर्ण

अटल स्थिर काष्ठा kernel_param_ops param_ops_nfs_समयout = अणु
	.set = param_set_nfs_समयout,
	.get = param_get_nfs_समयout,
पूर्ण;
#घोषणा param_check_nfs_समयout(name, p) __param_check(name, p, पूर्णांक)

module_param(nfs_mountpoपूर्णांक_expiry_समयout, nfs_समयout, 0644);
MODULE_PARM_DESC(nfs_mountpoपूर्णांक_expiry_समयout,
		"Set the NFS automounted mountpoint timeout value (seconds)."
		"Values <= 0 turn expiration off.");
