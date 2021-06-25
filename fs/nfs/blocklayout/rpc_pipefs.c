<शैली गुरु>
/*
 *  Copyright (c) 2006,2007 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Andy Adamson <andros@citi.umich.edu>
 *  Fred Isaman <iisaman@umich.edu>
 *
 * permission is granted to use, copy, create derivative works and
 * redistribute this software and such derivative works क्रम any purpose,
 * so दीर्घ as the name of the university of michigan is not used in
 * any advertising or खुलाity pertaining to the use or distribution
 * of this software without specअगरic, written prior authorization.  अगर
 * the above copyright notice or any other identअगरication of the
 * university of michigan is included in any copy of any portion of
 * this software, then the disclaimer below must also be included.
 *
 * this software is provided as is, without representation from the
 * university of michigan as to its fitness क्रम any purpose, and without
 * warranty by the university of michigan of any kind, either express
 * or implied, including without limitation the implied warranties of
 * merchantability and fitness क्रम a particular purpose.  the regents
 * of the university of michigan shall not be liable क्रम any damages,
 * including special, indirect, incidental, or consequential damages,
 * with respect to any claim arising out or in connection with the use
 * of the software, even अगर it has been or is hereafter advised of the
 * possibility of such damages.
 */

#समावेश <linux/module.h>
#समावेश <linux/genhd.h>
#समावेश <linux/blkdev.h>

#समावेश "blocklayout.h"

#घोषणा NFSDBG_FACILITY         NFSDBG_PNFS_LD

अटल व्योम
nfs4_encode_simple(__be32 *p, काष्ठा pnfs_block_volume *b)
अणु
	पूर्णांक i;

	*p++ = cpu_to_be32(1);
	*p++ = cpu_to_be32(b->type);
	*p++ = cpu_to_be32(b->simple.nr_sigs);
	क्रम (i = 0; i < b->simple.nr_sigs; i++) अणु
		p = xdr_encode_hyper(p, b->simple.sigs[i].offset);
		p = xdr_encode_opaque(p, b->simple.sigs[i].sig,
					 b->simple.sigs[i].sig_len);
	पूर्ण
पूर्ण

dev_t
bl_resolve_deviceid(काष्ठा nfs_server *server, काष्ठा pnfs_block_volume *b,
		gfp_t gfp_mask)
अणु
	काष्ठा net *net = server->nfs_client->cl_net;
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);
	काष्ठा bl_dev_msg *reply = &nn->bl_mount_reply;
	काष्ठा bl_pipe_msg bl_pipe_msg;
	काष्ठा rpc_pipe_msg *msg = &bl_pipe_msg.msg;
	काष्ठा bl_msg_hdr *bl_msg;
	DECLARE_WAITQUEUE(wq, current);
	dev_t dev = 0;
	पूर्णांक rc;

	dprपूर्णांकk("%s CREATING PIPEFS MESSAGE\n", __func__);

	mutex_lock(&nn->bl_mutex);
	bl_pipe_msg.bl_wq = &nn->bl_wq;

	b->simple.len += 4;	/* single volume */
	अगर (b->simple.len > PAGE_SIZE)
		जाओ out_unlock;

	स_रखो(msg, 0, माप(*msg));
	msg->len = माप(*bl_msg) + b->simple.len;
	msg->data = kzalloc(msg->len, gfp_mask);
	अगर (!msg->data)
		जाओ out_मुक्त_data;

	bl_msg = msg->data;
	bl_msg->type = BL_DEVICE_MOUNT;
	bl_msg->totallen = b->simple.len;
	nfs4_encode_simple(msg->data + माप(*bl_msg), b);

	dprपूर्णांकk("%s CALLING USERSPACE DAEMON\n", __func__);
	add_रुको_queue(&nn->bl_wq, &wq);
	rc = rpc_queue_upcall(nn->bl_device_pipe, msg);
	अगर (rc < 0) अणु
		हटाओ_रुको_queue(&nn->bl_wq, &wq);
		जाओ out_मुक्त_data;
	पूर्ण

	set_current_state(TASK_UNINTERRUPTIBLE);
	schedule();
	हटाओ_रुको_queue(&nn->bl_wq, &wq);

	अगर (reply->status != BL_DEVICE_REQUEST_PROC) अणु
		prपूर्णांकk(KERN_WARNING "%s failed to decode device: %d\n",
			__func__, reply->status);
		जाओ out_मुक्त_data;
	पूर्ण

	dev = MKDEV(reply->major, reply->minor);
out_मुक्त_data:
	kमुक्त(msg->data);
out_unlock:
	mutex_unlock(&nn->bl_mutex);
	वापस dev;
पूर्ण

अटल sमाप_प्रकार bl_pipe_करोwncall(काष्ठा file *filp, स्थिर अक्षर __user *src,
			 माप_प्रकार mlen)
अणु
	काष्ठा nfs_net *nn = net_generic(file_inode(filp)->i_sb->s_fs_info,
					 nfs_net_id);

	अगर (mlen != माप (काष्ठा bl_dev_msg))
		वापस -EINVAL;

	अगर (copy_from_user(&nn->bl_mount_reply, src, mlen) != 0)
		वापस -EFAULT;

	wake_up(&nn->bl_wq);

	वापस mlen;
पूर्ण

अटल व्योम bl_pipe_destroy_msg(काष्ठा rpc_pipe_msg *msg)
अणु
	काष्ठा bl_pipe_msg *bl_pipe_msg =
		container_of(msg, काष्ठा bl_pipe_msg, msg);

	अगर (msg->त्रुटि_सं >= 0)
		वापस;
	wake_up(bl_pipe_msg->bl_wq);
पूर्ण

अटल स्थिर काष्ठा rpc_pipe_ops bl_upcall_ops = अणु
	.upcall		= rpc_pipe_generic_upcall,
	.करोwncall	= bl_pipe_करोwncall,
	.destroy_msg	= bl_pipe_destroy_msg,
पूर्ण;

अटल काष्ठा dentry *nfs4blocklayout_रेजिस्टर_sb(काष्ठा super_block *sb,
					    काष्ठा rpc_pipe *pipe)
अणु
	काष्ठा dentry *dir, *dentry;

	dir = rpc_d_lookup_sb(sb, NFS_PIPE_सूचीNAME);
	अगर (dir == शून्य)
		वापस ERR_PTR(-ENOENT);
	dentry = rpc_mkpipe_dentry(dir, "blocklayout", शून्य, pipe);
	dput(dir);
	वापस dentry;
पूर्ण

अटल व्योम nfs4blocklayout_unरेजिस्टर_sb(काष्ठा super_block *sb,
					  काष्ठा rpc_pipe *pipe)
अणु
	अगर (pipe->dentry)
		rpc_unlink(pipe->dentry);
पूर्ण

अटल पूर्णांक rpc_pipefs_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			   व्योम *ptr)
अणु
	काष्ठा super_block *sb = ptr;
	काष्ठा net *net = sb->s_fs_info;
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);
	काष्ठा dentry *dentry;
	पूर्णांक ret = 0;

	अगर (!try_module_get(THIS_MODULE))
		वापस 0;

	अगर (nn->bl_device_pipe == शून्य) अणु
		module_put(THIS_MODULE);
		वापस 0;
	पूर्ण

	चयन (event) अणु
	हाल RPC_PIPEFS_MOUNT:
		dentry = nfs4blocklayout_रेजिस्टर_sb(sb, nn->bl_device_pipe);
		अगर (IS_ERR(dentry)) अणु
			ret = PTR_ERR(dentry);
			अवरोध;
		पूर्ण
		nn->bl_device_pipe->dentry = dentry;
		अवरोध;
	हाल RPC_PIPEFS_UMOUNT:
		अगर (nn->bl_device_pipe->dentry)
			nfs4blocklayout_unरेजिस्टर_sb(sb, nn->bl_device_pipe);
		अवरोध;
	शेष:
		ret = -ENOTSUPP;
		अवरोध;
	पूर्ण
	module_put(THIS_MODULE);
	वापस ret;
पूर्ण

अटल काष्ठा notअगरier_block nfs4blocklayout_block = अणु
	.notअगरier_call = rpc_pipefs_event,
पूर्ण;

अटल काष्ठा dentry *nfs4blocklayout_रेजिस्टर_net(काष्ठा net *net,
						   काष्ठा rpc_pipe *pipe)
अणु
	काष्ठा super_block *pipefs_sb;
	काष्ठा dentry *dentry;

	pipefs_sb = rpc_get_sb_net(net);
	अगर (!pipefs_sb)
		वापस शून्य;
	dentry = nfs4blocklayout_रेजिस्टर_sb(pipefs_sb, pipe);
	rpc_put_sb_net(net);
	वापस dentry;
पूर्ण

अटल व्योम nfs4blocklayout_unरेजिस्टर_net(काष्ठा net *net,
					   काष्ठा rpc_pipe *pipe)
अणु
	काष्ठा super_block *pipefs_sb;

	pipefs_sb = rpc_get_sb_net(net);
	अगर (pipefs_sb) अणु
		nfs4blocklayout_unरेजिस्टर_sb(pipefs_sb, pipe);
		rpc_put_sb_net(net);
	पूर्ण
पूर्ण

अटल पूर्णांक nfs4blocklayout_net_init(काष्ठा net *net)
अणु
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);
	काष्ठा dentry *dentry;

	mutex_init(&nn->bl_mutex);
	init_रुकोqueue_head(&nn->bl_wq);
	nn->bl_device_pipe = rpc_mkpipe_data(&bl_upcall_ops, 0);
	अगर (IS_ERR(nn->bl_device_pipe))
		वापस PTR_ERR(nn->bl_device_pipe);
	dentry = nfs4blocklayout_रेजिस्टर_net(net, nn->bl_device_pipe);
	अगर (IS_ERR(dentry)) अणु
		rpc_destroy_pipe_data(nn->bl_device_pipe);
		वापस PTR_ERR(dentry);
	पूर्ण
	nn->bl_device_pipe->dentry = dentry;
	वापस 0;
पूर्ण

अटल व्योम nfs4blocklayout_net_निकास(काष्ठा net *net)
अणु
	काष्ठा nfs_net *nn = net_generic(net, nfs_net_id);

	nfs4blocklayout_unरेजिस्टर_net(net, nn->bl_device_pipe);
	rpc_destroy_pipe_data(nn->bl_device_pipe);
	nn->bl_device_pipe = शून्य;
पूर्ण

अटल काष्ठा pernet_operations nfs4blocklayout_net_ops = अणु
	.init = nfs4blocklayout_net_init,
	.निकास = nfs4blocklayout_net_निकास,
पूर्ण;

पूर्णांक __init bl_init_pipefs(व्योम)
अणु
	पूर्णांक ret;

	ret = rpc_pipefs_notअगरier_रेजिस्टर(&nfs4blocklayout_block);
	अगर (ret)
		जाओ out;
	ret = रेजिस्टर_pernet_subsys(&nfs4blocklayout_net_ops);
	अगर (ret)
		जाओ out_unरेजिस्टर_notअगरier;
	वापस 0;

out_unरेजिस्टर_notअगरier:
	rpc_pipefs_notअगरier_unरेजिस्टर(&nfs4blocklayout_block);
out:
	वापस ret;
पूर्ण

व्योम bl_cleanup_pipefs(व्योम)
अणु
	rpc_pipefs_notअगरier_unरेजिस्टर(&nfs4blocklayout_block);
	unरेजिस्टर_pernet_subsys(&nfs4blocklayout_net_ops);
पूर्ण
