<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2014 Anna Schumaker <Anna.Schumaker@Netapp.com>
 */
#समावेश <linux/fs.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/nfs.h>
#समावेश <linux/nfs3.h>
#समावेश <linux/nfs4.h>
#समावेश <linux/nfs_xdr.h>
#समावेश <linux/nfs_fs.h>
#समावेश "nfs4_fs.h"
#समावेश "nfs42.h"
#समावेश "iostat.h"
#समावेश "pnfs.h"
#समावेश "nfs4session.h"
#समावेश "internal.h"
#समावेश "delegation.h"
#समावेश "nfs4trace.h"

#घोषणा NFSDBG_FACILITY NFSDBG_PROC
अटल पूर्णांक nfs42_करो_offload_cancel_async(काष्ठा file *dst, nfs4_stateid *std);

अटल व्योम nfs42_set_netaddr(काष्ठा file *filep, काष्ठा nfs42_netaddr *naddr)
अणु
	काष्ठा nfs_client *clp = (NFS_SERVER(file_inode(filep)))->nfs_client;
	अचिन्हित लघु port = 2049;

	rcu_पढ़ो_lock();
	naddr->netid_len = scnम_लिखो(naddr->netid,
					माप(naddr->netid), "%s",
					rpc_peeraddr2str(clp->cl_rpcclient,
					RPC_DISPLAY_NETID));
	naddr->addr_len = scnम_लिखो(naddr->addr,
					माप(naddr->addr),
					"%s.%u.%u",
					rpc_peeraddr2str(clp->cl_rpcclient,
					RPC_DISPLAY_ADDR),
					port >> 8, port & 255);
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक _nfs42_proc_fallocate(काष्ठा rpc_message *msg, काष्ठा file *filep,
		काष्ठा nfs_lock_context *lock, loff_t offset, loff_t len)
अणु
	काष्ठा inode *inode = file_inode(filep);
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	u32 biपंचांगask[3];
	काष्ठा nfs42_falloc_args args = अणु
		.falloc_fh	= NFS_FH(inode),
		.falloc_offset	= offset,
		.falloc_length	= len,
		.falloc_biपंचांगask	= biपंचांगask,
	पूर्ण;
	काष्ठा nfs42_falloc_res res = अणु
		.falloc_server	= server,
	पूर्ण;
	पूर्णांक status;

	msg->rpc_argp = &args;
	msg->rpc_resp = &res;

	status = nfs4_set_rw_stateid(&args.falloc_stateid, lock->खोलो_context,
			lock, FMODE_WRITE);
	अगर (status) अणु
		अगर (status == -EAGAIN)
			status = -NFS4ERR_BAD_STATEID;
		वापस status;
	पूर्ण

	स_नकल(biपंचांगask, server->cache_consistency_biपंचांगask, माप(biपंचांगask));
	अगर (server->attr_biपंचांगask[1] & FATTR4_WORD1_SPACE_USED)
		biपंचांगask[1] |= FATTR4_WORD1_SPACE_USED;

	res.falloc_fattr = nfs_alloc_fattr();
	अगर (!res.falloc_fattr)
		वापस -ENOMEM;

	status = nfs4_call_sync(server->client, server, msg,
				&args.seq_args, &res.seq_res, 0);
	अगर (status == 0)
		status = nfs_post_op_update_inode_क्रमce_wcc(inode,
							    res.falloc_fattr);

	kमुक्त(res.falloc_fattr);
	वापस status;
पूर्ण

अटल पूर्णांक nfs42_proc_fallocate(काष्ठा rpc_message *msg, काष्ठा file *filep,
				loff_t offset, loff_t len)
अणु
	काष्ठा inode *inode = file_inode(filep);
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs4_exception exception = अणु पूर्ण;
	काष्ठा nfs_lock_context *lock;
	पूर्णांक err;

	lock = nfs_get_lock_context(nfs_file_खोलो_context(filep));
	अगर (IS_ERR(lock))
		वापस PTR_ERR(lock);

	exception.inode = inode;
	exception.state = lock->खोलो_context->state;

	err = nfs_sync_inode(inode);
	अगर (err)
		जाओ out;

	करो अणु
		err = _nfs42_proc_fallocate(msg, filep, lock, offset, len);
		अगर (err == -ENOTSUPP) अणु
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		err = nfs4_handle_exception(server, err, &exception);
	पूर्ण जबतक (exception.retry);
out:
	nfs_put_lock_context(lock);
	वापस err;
पूर्ण

पूर्णांक nfs42_proc_allocate(काष्ठा file *filep, loff_t offset, loff_t len)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_ALLOCATE],
	पूर्ण;
	काष्ठा inode *inode = file_inode(filep);
	पूर्णांक err;

	अगर (!nfs_server_capable(inode, NFS_CAP_ALLOCATE))
		वापस -EOPNOTSUPP;

	inode_lock(inode);

	err = nfs42_proc_fallocate(&msg, filep, offset, len);
	अगर (err == -EOPNOTSUPP)
		NFS_SERVER(inode)->caps &= ~NFS_CAP_ALLOCATE;

	inode_unlock(inode);
	वापस err;
पूर्ण

पूर्णांक nfs42_proc_deallocate(काष्ठा file *filep, loff_t offset, loff_t len)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_DEALLOCATE],
	पूर्ण;
	काष्ठा inode *inode = file_inode(filep);
	पूर्णांक err;

	अगर (!nfs_server_capable(inode, NFS_CAP_DEALLOCATE))
		वापस -EOPNOTSUPP;

	inode_lock(inode);

	err = nfs42_proc_fallocate(&msg, filep, offset, len);
	अगर (err == 0)
		truncate_pagecache_range(inode, offset, (offset + len) -1);
	अगर (err == -EOPNOTSUPP)
		NFS_SERVER(inode)->caps &= ~NFS_CAP_DEALLOCATE;

	inode_unlock(inode);
	वापस err;
पूर्ण

अटल पूर्णांक handle_async_copy(काष्ठा nfs42_copy_res *res,
			     काष्ठा nfs_server *dst_server,
			     काष्ठा nfs_server *src_server,
			     काष्ठा file *src,
			     काष्ठा file *dst,
			     nfs4_stateid *src_stateid,
			     bool *restart)
अणु
	काष्ठा nfs4_copy_state *copy, *पंचांगp_copy;
	पूर्णांक status = NFS4_OK;
	bool found_pending = false;
	काष्ठा nfs_खोलो_context *dst_ctx = nfs_file_खोलो_context(dst);
	काष्ठा nfs_खोलो_context *src_ctx = nfs_file_खोलो_context(src);

	copy = kzalloc(माप(काष्ठा nfs4_copy_state), GFP_NOFS);
	अगर (!copy)
		वापस -ENOMEM;

	spin_lock(&dst_server->nfs_client->cl_lock);
	list_क्रम_each_entry(पंचांगp_copy,
				&dst_server->nfs_client->pending_cb_stateids,
				copies) अणु
		अगर (स_भेद(&res->ग_लिखो_res.stateid, &पंचांगp_copy->stateid,
				NFS4_STATEID_SIZE))
			जारी;
		found_pending = true;
		list_del(&पंचांगp_copy->copies);
		अवरोध;
	पूर्ण
	अगर (found_pending) अणु
		spin_unlock(&dst_server->nfs_client->cl_lock);
		kमुक्त(copy);
		copy = पंचांगp_copy;
		जाओ out;
	पूर्ण

	स_नकल(&copy->stateid, &res->ग_लिखो_res.stateid, NFS4_STATEID_SIZE);
	init_completion(&copy->completion);
	copy->parent_dst_state = dst_ctx->state;
	copy->parent_src_state = src_ctx->state;

	list_add_tail(&copy->copies, &dst_server->ss_copies);
	spin_unlock(&dst_server->nfs_client->cl_lock);

	अगर (dst_server != src_server) अणु
		spin_lock(&src_server->nfs_client->cl_lock);
		list_add_tail(&copy->src_copies, &src_server->ss_copies);
		spin_unlock(&src_server->nfs_client->cl_lock);
	पूर्ण

	status = रुको_क्रम_completion_पूर्णांकerruptible(&copy->completion);
	spin_lock(&dst_server->nfs_client->cl_lock);
	list_del_init(&copy->copies);
	spin_unlock(&dst_server->nfs_client->cl_lock);
	अगर (dst_server != src_server) अणु
		spin_lock(&src_server->nfs_client->cl_lock);
		list_del_init(&copy->src_copies);
		spin_unlock(&src_server->nfs_client->cl_lock);
	पूर्ण
	अगर (status == -ERESTARTSYS) अणु
		जाओ out_cancel;
	पूर्ण अन्यथा अगर (copy->flags || copy->error == NFS4ERR_PARTNER_NO_AUTH) अणु
		status = -EAGAIN;
		*restart = true;
		जाओ out_cancel;
	पूर्ण
out:
	res->ग_लिखो_res.count = copy->count;
	स_नकल(&res->ग_लिखो_res.verअगरier, &copy->verf, माप(copy->verf));
	status = -copy->error;

out_मुक्त:
	kमुक्त(copy);
	वापस status;
out_cancel:
	nfs42_करो_offload_cancel_async(dst, &copy->stateid);
	अगर (!nfs42_files_from_same_server(src, dst))
		nfs42_करो_offload_cancel_async(src, src_stateid);
	जाओ out_मुक्त;
पूर्ण

अटल पूर्णांक process_copy_commit(काष्ठा file *dst, loff_t pos_dst,
			       काष्ठा nfs42_copy_res *res)
अणु
	काष्ठा nfs_commitres cres;
	पूर्णांक status = -ENOMEM;

	cres.verf = kzalloc(माप(काष्ठा nfs_ग_लिखोverf), GFP_NOFS);
	अगर (!cres.verf)
		जाओ out;

	status = nfs4_proc_commit(dst, pos_dst, res->ग_लिखो_res.count, &cres);
	अगर (status)
		जाओ out_मुक्त;
	अगर (nfs_ग_लिखो_verअगरier_cmp(&res->ग_लिखो_res.verअगरier.verअगरier,
				    &cres.verf->verअगरier)) अणु
		dprपूर्णांकk("commit verf differs from copy verf\n");
		status = -EAGAIN;
	पूर्ण
out_मुक्त:
	kमुक्त(cres.verf);
out:
	वापस status;
पूर्ण

/**
 * nfs42_copy_dest_करोne - perक्रमm inode cache updates after clone/copy offload
 * @inode: poपूर्णांकer to destination inode
 * @pos: destination offset
 * @len: copy length
 *
 * Punch a hole in the inode page cache, so that the NFS client will
 * know to retrieve new data.
 * Update the file size अगर necessary, and then mark the inode as having
 * invalid cached values क्रम change attribute, स_समय, mसमय and space used.
 */
अटल व्योम nfs42_copy_dest_करोne(काष्ठा inode *inode, loff_t pos, loff_t len)
अणु
	loff_t newsize = pos + len;
	loff_t end = newsize - 1;

	truncate_pagecache_range(inode, pos, end);
	spin_lock(&inode->i_lock);
	अगर (newsize > i_size_पढ़ो(inode))
		i_size_ग_लिखो(inode, newsize);
	nfs_set_cache_invalid(inode, NFS_INO_INVALID_CHANGE |
					     NFS_INO_INVALID_CTIME |
					     NFS_INO_INVALID_MTIME |
					     NFS_INO_INVALID_BLOCKS);
	spin_unlock(&inode->i_lock);
पूर्ण

अटल sमाप_प्रकार _nfs42_proc_copy(काष्ठा file *src,
				काष्ठा nfs_lock_context *src_lock,
				काष्ठा file *dst,
				काष्ठा nfs_lock_context *dst_lock,
				काष्ठा nfs42_copy_args *args,
				काष्ठा nfs42_copy_res *res,
				काष्ठा nl4_server *nss,
				nfs4_stateid *cnr_stateid,
				bool *restart)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_COPY],
		.rpc_argp = args,
		.rpc_resp = res,
	पूर्ण;
	काष्ठा inode *dst_inode = file_inode(dst);
	काष्ठा inode *src_inode = file_inode(src);
	काष्ठा nfs_server *dst_server = NFS_SERVER(dst_inode);
	काष्ठा nfs_server *src_server = NFS_SERVER(src_inode);
	loff_t pos_src = args->src_pos;
	loff_t pos_dst = args->dst_pos;
	माप_प्रकार count = args->count;
	sमाप_प्रकार status;

	अगर (nss) अणु
		args->cp_src = nss;
		nfs4_stateid_copy(&args->src_stateid, cnr_stateid);
	पूर्ण अन्यथा अणु
		status = nfs4_set_rw_stateid(&args->src_stateid,
				src_lock->खोलो_context, src_lock, FMODE_READ);
		अगर (status) अणु
			अगर (status == -EAGAIN)
				status = -NFS4ERR_BAD_STATEID;
			वापस status;
		पूर्ण
	पूर्ण
	status = nfs_filemap_ग_लिखो_and_रुको_range(file_inode(src)->i_mapping,
			pos_src, pos_src + (loff_t)count - 1);
	अगर (status)
		वापस status;

	status = nfs4_set_rw_stateid(&args->dst_stateid, dst_lock->खोलो_context,
				     dst_lock, FMODE_WRITE);
	अगर (status) अणु
		अगर (status == -EAGAIN)
			status = -NFS4ERR_BAD_STATEID;
		वापस status;
	पूर्ण

	status = nfs_sync_inode(dst_inode);
	अगर (status)
		वापस status;

	res->commit_res.verf = शून्य;
	अगर (args->sync) अणु
		res->commit_res.verf =
			kzalloc(माप(काष्ठा nfs_ग_लिखोverf), GFP_NOFS);
		अगर (!res->commit_res.verf)
			वापस -ENOMEM;
	पूर्ण
	set_bit(NFS_CLNT_SRC_SSC_COPY_STATE,
		&src_lock->खोलो_context->state->flags);
	set_bit(NFS_CLNT_DST_SSC_COPY_STATE,
		&dst_lock->खोलो_context->state->flags);

	status = nfs4_call_sync(dst_server->client, dst_server, &msg,
				&args->seq_args, &res->seq_res, 0);
	अगर (status == -ENOTSUPP)
		dst_server->caps &= ~NFS_CAP_COPY;
	अगर (status)
		जाओ out;

	अगर (args->sync &&
		nfs_ग_लिखो_verअगरier_cmp(&res->ग_लिखो_res.verअगरier.verअगरier,
				    &res->commit_res.verf->verअगरier)) अणु
		status = -EAGAIN;
		जाओ out;
	पूर्ण

	अगर (!res->synchronous) अणु
		status = handle_async_copy(res, dst_server, src_server, src,
				dst, &args->src_stateid, restart);
		अगर (status)
			जाओ out;
	पूर्ण

	अगर ((!res->synchronous || !args->sync) &&
			res->ग_लिखो_res.verअगरier.committed != NFS_खाता_SYNC) अणु
		status = process_copy_commit(dst, pos_dst, res);
		अगर (status)
			जाओ out;
	पूर्ण

	nfs42_copy_dest_करोne(dst_inode, pos_dst, res->ग_लिखो_res.count);
	nfs_invalidate_aसमय(src_inode);
	status = res->ग_लिखो_res.count;
out:
	अगर (args->sync)
		kमुक्त(res->commit_res.verf);
	वापस status;
पूर्ण

sमाप_प्रकार nfs42_proc_copy(काष्ठा file *src, loff_t pos_src,
			काष्ठा file *dst, loff_t pos_dst, माप_प्रकार count,
			काष्ठा nl4_server *nss,
			nfs4_stateid *cnr_stateid, bool sync)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(file_inode(dst));
	काष्ठा nfs_lock_context *src_lock;
	काष्ठा nfs_lock_context *dst_lock;
	काष्ठा nfs42_copy_args args = अणु
		.src_fh		= NFS_FH(file_inode(src)),
		.src_pos	= pos_src,
		.dst_fh		= NFS_FH(file_inode(dst)),
		.dst_pos	= pos_dst,
		.count		= count,
		.sync		= sync,
	पूर्ण;
	काष्ठा nfs42_copy_res res;
	काष्ठा nfs4_exception src_exception = अणु
		.inode		= file_inode(src),
		.stateid	= &args.src_stateid,
	पूर्ण;
	काष्ठा nfs4_exception dst_exception = अणु
		.inode		= file_inode(dst),
		.stateid	= &args.dst_stateid,
	पूर्ण;
	sमाप_प्रकार err, err2;
	bool restart = false;

	src_lock = nfs_get_lock_context(nfs_file_खोलो_context(src));
	अगर (IS_ERR(src_lock))
		वापस PTR_ERR(src_lock);

	src_exception.state = src_lock->खोलो_context->state;

	dst_lock = nfs_get_lock_context(nfs_file_खोलो_context(dst));
	अगर (IS_ERR(dst_lock)) अणु
		err = PTR_ERR(dst_lock);
		जाओ out_put_src_lock;
	पूर्ण

	dst_exception.state = dst_lock->खोलो_context->state;

	करो अणु
		inode_lock(file_inode(dst));
		err = _nfs42_proc_copy(src, src_lock,
				dst, dst_lock,
				&args, &res,
				nss, cnr_stateid, &restart);
		inode_unlock(file_inode(dst));

		अगर (err >= 0)
			अवरोध;
		अगर (err == -ENOTSUPP &&
				nfs42_files_from_same_server(src, dst)) अणु
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण अन्यथा अगर (err == -EAGAIN) अणु
			अगर (!restart) अणु
				dst_exception.retry = 1;
				जारी;
			पूर्ण
			अवरोध;
		पूर्ण अन्यथा अगर (err == -NFS4ERR_OFFLOAD_NO_REQS && !args.sync) अणु
			args.sync = true;
			dst_exception.retry = 1;
			जारी;
		पूर्ण अन्यथा अगर ((err == -ESTALE ||
				err == -NFS4ERR_OFFLOAD_DENIED ||
				err == -ENOTSUPP) &&
				!nfs42_files_from_same_server(src, dst)) अणु
			nfs42_करो_offload_cancel_async(src, &args.src_stateid);
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		err2 = nfs4_handle_exception(server, err, &src_exception);
		err  = nfs4_handle_exception(server, err, &dst_exception);
		अगर (!err)
			err = err2;
	पूर्ण जबतक (src_exception.retry || dst_exception.retry);

	nfs_put_lock_context(dst_lock);
out_put_src_lock:
	nfs_put_lock_context(src_lock);
	वापस err;
पूर्ण

काष्ठा nfs42_offloadcancel_data अणु
	काष्ठा nfs_server *seq_server;
	काष्ठा nfs42_offload_status_args args;
	काष्ठा nfs42_offload_status_res res;
पूर्ण;

अटल व्योम nfs42_offload_cancel_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs42_offloadcancel_data *data = calldata;

	nfs4_setup_sequence(data->seq_server->nfs_client,
				&data->args.osa_seq_args,
				&data->res.osr_seq_res, task);
पूर्ण

अटल व्योम nfs42_offload_cancel_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs42_offloadcancel_data *data = calldata;

	nfs41_sequence_करोne(task, &data->res.osr_seq_res);
	अगर (task->tk_status &&
		nfs4_async_handle_error(task, data->seq_server, शून्य,
			शून्य) == -EAGAIN)
		rpc_restart_call_prepare(task);
पूर्ण

अटल व्योम nfs42_मुक्त_offloadcancel_data(व्योम *data)
अणु
	kमुक्त(data);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs42_offload_cancel_ops = अणु
	.rpc_call_prepare = nfs42_offload_cancel_prepare,
	.rpc_call_करोne = nfs42_offload_cancel_करोne,
	.rpc_release = nfs42_मुक्त_offloadcancel_data,
पूर्ण;

अटल पूर्णांक nfs42_करो_offload_cancel_async(काष्ठा file *dst,
					 nfs4_stateid *stateid)
अणु
	काष्ठा nfs_server *dst_server = NFS_SERVER(file_inode(dst));
	काष्ठा nfs42_offloadcancel_data *data = शून्य;
	काष्ठा nfs_खोलो_context *ctx = nfs_file_खोलो_context(dst);
	काष्ठा rpc_task *task;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_OFFLOAD_CANCEL],
		.rpc_cred = ctx->cred,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup_data = अणु
		.rpc_client = dst_server->client,
		.rpc_message = &msg,
		.callback_ops = &nfs42_offload_cancel_ops,
		.workqueue = nfsiod_workqueue,
		.flags = RPC_TASK_ASYNC,
	पूर्ण;
	पूर्णांक status;

	अगर (!(dst_server->caps & NFS_CAP_OFFLOAD_CANCEL))
		वापस -EOPNOTSUPP;

	data = kzalloc(माप(काष्ठा nfs42_offloadcancel_data), GFP_NOFS);
	अगर (data == शून्य)
		वापस -ENOMEM;

	data->seq_server = dst_server;
	data->args.osa_src_fh = NFS_FH(file_inode(dst));
	स_नकल(&data->args.osa_stateid, stateid,
		माप(data->args.osa_stateid));
	msg.rpc_argp = &data->args;
	msg.rpc_resp = &data->res;
	task_setup_data.callback_data = data;
	nfs4_init_sequence(&data->args.osa_seq_args, &data->res.osr_seq_res,
			   1, 0);
	task = rpc_run_task(&task_setup_data);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	status = rpc_रुको_क्रम_completion_task(task);
	अगर (status == -ENOTSUPP)
		dst_server->caps &= ~NFS_CAP_OFFLOAD_CANCEL;
	rpc_put_task(task);
	वापस status;
पूर्ण

अटल पूर्णांक _nfs42_proc_copy_notअगरy(काष्ठा file *src, काष्ठा file *dst,
				   काष्ठा nfs42_copy_notअगरy_args *args,
				   काष्ठा nfs42_copy_notअगरy_res *res)
अणु
	काष्ठा nfs_server *src_server = NFS_SERVER(file_inode(src));
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_COPY_NOTIFY],
		.rpc_argp = args,
		.rpc_resp = res,
	पूर्ण;
	पूर्णांक status;
	काष्ठा nfs_खोलो_context *ctx;
	काष्ठा nfs_lock_context *l_ctx;

	ctx = get_nfs_खोलो_context(nfs_file_खोलो_context(src));
	l_ctx = nfs_get_lock_context(ctx);
	अगर (IS_ERR(l_ctx))
		वापस PTR_ERR(l_ctx);

	status = nfs4_set_rw_stateid(&args->cna_src_stateid, ctx, l_ctx,
				     FMODE_READ);
	nfs_put_lock_context(l_ctx);
	अगर (status) अणु
		अगर (status == -EAGAIN)
			status = -NFS4ERR_BAD_STATEID;
		वापस status;
	पूर्ण

	status = nfs4_call_sync(src_server->client, src_server, &msg,
				&args->cna_seq_args, &res->cnr_seq_res, 0);
	अगर (status == -ENOTSUPP)
		src_server->caps &= ~NFS_CAP_COPY_NOTIFY;

	put_nfs_खोलो_context(nfs_file_खोलो_context(src));
	वापस status;
पूर्ण

पूर्णांक nfs42_proc_copy_notअगरy(काष्ठा file *src, काष्ठा file *dst,
				काष्ठा nfs42_copy_notअगरy_res *res)
अणु
	काष्ठा nfs_server *src_server = NFS_SERVER(file_inode(src));
	काष्ठा nfs42_copy_notअगरy_args *args;
	काष्ठा nfs4_exception exception = अणु
		.inode = file_inode(src),
	पूर्ण;
	पूर्णांक status;

	अगर (!(src_server->caps & NFS_CAP_COPY_NOTIFY))
		वापस -EOPNOTSUPP;

	args = kzalloc(माप(काष्ठा nfs42_copy_notअगरy_args), GFP_NOFS);
	अगर (args == शून्य)
		वापस -ENOMEM;

	args->cna_src_fh  = NFS_FH(file_inode(src)),
	args->cna_dst.nl4_type = NL4_NETADDR;
	nfs42_set_netaddr(dst, &args->cna_dst.u.nl4_addr);
	exception.stateid = &args->cna_src_stateid;

	करो अणु
		status = _nfs42_proc_copy_notअगरy(src, dst, args, res);
		अगर (status == -ENOTSUPP) अणु
			status = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
		status = nfs4_handle_exception(src_server, status, &exception);
	पूर्ण जबतक (exception.retry);

out:
	kमुक्त(args);
	वापस status;
पूर्ण

अटल loff_t _nfs42_proc_llseek(काष्ठा file *filep,
		काष्ठा nfs_lock_context *lock, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा inode *inode = file_inode(filep);
	काष्ठा nfs42_seek_args args = अणु
		.sa_fh		= NFS_FH(inode),
		.sa_offset	= offset,
		.sa_what	= (whence == SEEK_HOLE) ?
					NFS4_CONTENT_HOLE : NFS4_CONTENT_DATA,
	पूर्ण;
	काष्ठा nfs42_seek_res res;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_SEEK],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	पूर्णांक status;

	अगर (!nfs_server_capable(inode, NFS_CAP_SEEK))
		वापस -ENOTSUPP;

	status = nfs4_set_rw_stateid(&args.sa_stateid, lock->खोलो_context,
			lock, FMODE_READ);
	अगर (status) अणु
		अगर (status == -EAGAIN)
			status = -NFS4ERR_BAD_STATEID;
		वापस status;
	पूर्ण

	status = nfs_filemap_ग_लिखो_and_रुको_range(inode->i_mapping,
			offset, Lदीर्घ_उच्च);
	अगर (status)
		वापस status;

	status = nfs4_call_sync(server->client, server, &msg,
				&args.seq_args, &res.seq_res, 0);
	अगर (status == -ENOTSUPP)
		server->caps &= ~NFS_CAP_SEEK;
	अगर (status)
		वापस status;

	अगर (whence == SEEK_DATA && res.sr_eof)
		वापस -NFS4ERR_NXIO;
	अन्यथा
		वापस vfs_setpos(filep, res.sr_offset, inode->i_sb->s_maxbytes);
पूर्ण

loff_t nfs42_proc_llseek(काष्ठा file *filep, loff_t offset, पूर्णांक whence)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(file_inode(filep));
	काष्ठा nfs4_exception exception = अणु पूर्ण;
	काष्ठा nfs_lock_context *lock;
	loff_t err;

	lock = nfs_get_lock_context(nfs_file_खोलो_context(filep));
	अगर (IS_ERR(lock))
		वापस PTR_ERR(lock);

	exception.inode = file_inode(filep);
	exception.state = lock->खोलो_context->state;

	करो अणु
		err = _nfs42_proc_llseek(filep, lock, offset, whence);
		अगर (err >= 0)
			अवरोध;
		अगर (err == -ENOTSUPP) अणु
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		err = nfs4_handle_exception(server, err, &exception);
	पूर्ण जबतक (exception.retry);

	nfs_put_lock_context(lock);
	वापस err;
पूर्ण


अटल व्योम
nfs42_layoutstat_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs42_layoutstat_data *data = calldata;
	काष्ठा inode *inode = data->inode;
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा pnfs_layout_hdr *lo;

	spin_lock(&inode->i_lock);
	lo = NFS_I(inode)->layout;
	अगर (!pnfs_layout_is_valid(lo)) अणु
		spin_unlock(&inode->i_lock);
		rpc_निकास(task, 0);
		वापस;
	पूर्ण
	nfs4_stateid_copy(&data->args.stateid, &lo->plh_stateid);
	spin_unlock(&inode->i_lock);
	nfs4_setup_sequence(server->nfs_client, &data->args.seq_args,
			    &data->res.seq_res, task);
पूर्ण

अटल व्योम
nfs42_layoutstat_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs42_layoutstat_data *data = calldata;
	काष्ठा inode *inode = data->inode;
	काष्ठा pnfs_layout_hdr *lo;

	अगर (!nfs4_sequence_करोne(task, &data->res.seq_res))
		वापस;

	चयन (task->tk_status) अणु
	हाल 0:
		वापस;
	हाल -NFS4ERR_BADHANDLE:
	हाल -ESTALE:
		pnfs_destroy_layout(NFS_I(inode));
		अवरोध;
	हाल -NFS4ERR_EXPIRED:
	हाल -NFS4ERR_ADMIN_REVOKED:
	हाल -NFS4ERR_DELEG_REVOKED:
	हाल -NFS4ERR_STALE_STATEID:
	हाल -NFS4ERR_BAD_STATEID:
		spin_lock(&inode->i_lock);
		lo = NFS_I(inode)->layout;
		अगर (pnfs_layout_is_valid(lo) &&
		    nfs4_stateid_match(&data->args.stateid,
					     &lo->plh_stateid)) अणु
			LIST_HEAD(head);

			/*
			 * Mark the bad layout state as invalid, then retry
			 * with the current stateid.
			 */
			pnfs_mark_layout_stateid_invalid(lo, &head);
			spin_unlock(&inode->i_lock);
			pnfs_मुक्त_lseg_list(&head);
			nfs_commit_inode(inode, 0);
		पूर्ण अन्यथा
			spin_unlock(&inode->i_lock);
		अवरोध;
	हाल -NFS4ERR_OLD_STATEID:
		spin_lock(&inode->i_lock);
		lo = NFS_I(inode)->layout;
		अगर (pnfs_layout_is_valid(lo) &&
		    nfs4_stateid_match_other(&data->args.stateid,
					&lo->plh_stateid)) अणु
			/* Do we need to delay beक्रमe resending? */
			अगर (!nfs4_stateid_is_newer(&lo->plh_stateid,
						&data->args.stateid))
				rpc_delay(task, HZ);
			rpc_restart_call_prepare(task);
		पूर्ण
		spin_unlock(&inode->i_lock);
		अवरोध;
	हाल -ENOTSUPP:
	हाल -EOPNOTSUPP:
		NFS_SERVER(inode)->caps &= ~NFS_CAP_LAYOUTSTATS;
	पूर्ण

	trace_nfs4_layoutstats(inode, &data->args.stateid, task->tk_status);
पूर्ण

अटल व्योम
nfs42_layoutstat_release(व्योम *calldata)
अणु
	काष्ठा nfs42_layoutstat_data *data = calldata;
	काष्ठा nfs42_layoutstat_devinfo *devinfo = data->args.devinfo;
	पूर्णांक i;

	क्रम (i = 0; i < data->args.num_dev; i++) अणु
		अगर (devinfo[i].ld_निजी.ops && devinfo[i].ld_निजी.ops->मुक्त)
			devinfo[i].ld_निजी.ops->मुक्त(&devinfo[i].ld_निजी);
	पूर्ण

	pnfs_put_layout_hdr(NFS_I(data->args.inode)->layout);
	smp_mb__beक्रमe_atomic();
	clear_bit(NFS_INO_LAYOUTSTATS, &NFS_I(data->args.inode)->flags);
	smp_mb__after_atomic();
	nfs_iput_and_deactive(data->inode);
	kमुक्त(data->args.devinfo);
	kमुक्त(data);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs42_layoutstat_ops = अणु
	.rpc_call_prepare = nfs42_layoutstat_prepare,
	.rpc_call_करोne = nfs42_layoutstat_करोne,
	.rpc_release = nfs42_layoutstat_release,
पूर्ण;

पूर्णांक nfs42_proc_layoutstats_generic(काष्ठा nfs_server *server,
				   काष्ठा nfs42_layoutstat_data *data)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_LAYOUTSTATS],
		.rpc_argp = &data->args,
		.rpc_resp = &data->res,
	पूर्ण;
	काष्ठा rpc_task_setup task_setup = अणु
		.rpc_client = server->client,
		.rpc_message = &msg,
		.callback_ops = &nfs42_layoutstat_ops,
		.callback_data = data,
		.flags = RPC_TASK_ASYNC,
	पूर्ण;
	काष्ठा rpc_task *task;

	data->inode = nfs_igrab_and_active(data->args.inode);
	अगर (!data->inode) अणु
		nfs42_layoutstat_release(data);
		वापस -EAGAIN;
	पूर्ण
	nfs4_init_sequence(&data->args.seq_args, &data->res.seq_res, 0, 0);
	task = rpc_run_task(&task_setup);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	rpc_put_task(task);
	वापस 0;
पूर्ण

अटल काष्ठा nfs42_layouterror_data *
nfs42_alloc_layouterror_data(काष्ठा pnfs_layout_segment *lseg, gfp_t gfp_flags)
अणु
	काष्ठा nfs42_layouterror_data *data;
	काष्ठा inode *inode = lseg->pls_layout->plh_inode;

	data = kzalloc(माप(*data), gfp_flags);
	अगर (data) अणु
		data->args.inode = data->inode = nfs_igrab_and_active(inode);
		अगर (data->inode) अणु
			data->lseg = pnfs_get_lseg(lseg);
			अगर (data->lseg)
				वापस data;
			nfs_iput_and_deactive(data->inode);
		पूर्ण
		kमुक्त(data);
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम
nfs42_मुक्त_layouterror_data(काष्ठा nfs42_layouterror_data *data)
अणु
	pnfs_put_lseg(data->lseg);
	nfs_iput_and_deactive(data->inode);
	kमुक्त(data);
पूर्ण

अटल व्योम
nfs42_layouterror_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs42_layouterror_data *data = calldata;
	काष्ठा inode *inode = data->inode;
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा pnfs_layout_hdr *lo = data->lseg->pls_layout;
	अचिन्हित i;

	spin_lock(&inode->i_lock);
	अगर (!pnfs_layout_is_valid(lo)) अणु
		spin_unlock(&inode->i_lock);
		rpc_निकास(task, 0);
		वापस;
	पूर्ण
	क्रम (i = 0; i < data->args.num_errors; i++)
		nfs4_stateid_copy(&data->args.errors[i].stateid,
				&lo->plh_stateid);
	spin_unlock(&inode->i_lock);
	nfs4_setup_sequence(server->nfs_client, &data->args.seq_args,
			    &data->res.seq_res, task);
पूर्ण

अटल व्योम
nfs42_layouterror_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs42_layouterror_data *data = calldata;
	काष्ठा inode *inode = data->inode;
	काष्ठा pnfs_layout_hdr *lo = data->lseg->pls_layout;

	अगर (!nfs4_sequence_करोne(task, &data->res.seq_res))
		वापस;

	चयन (task->tk_status) अणु
	हाल 0:
		वापस;
	हाल -NFS4ERR_BADHANDLE:
	हाल -ESTALE:
		pnfs_destroy_layout(NFS_I(inode));
		अवरोध;
	हाल -NFS4ERR_EXPIRED:
	हाल -NFS4ERR_ADMIN_REVOKED:
	हाल -NFS4ERR_DELEG_REVOKED:
	हाल -NFS4ERR_STALE_STATEID:
	हाल -NFS4ERR_BAD_STATEID:
		spin_lock(&inode->i_lock);
		अगर (pnfs_layout_is_valid(lo) &&
		    nfs4_stateid_match(&data->args.errors[0].stateid,
					     &lo->plh_stateid)) अणु
			LIST_HEAD(head);

			/*
			 * Mark the bad layout state as invalid, then retry
			 * with the current stateid.
			 */
			pnfs_mark_layout_stateid_invalid(lo, &head);
			spin_unlock(&inode->i_lock);
			pnfs_मुक्त_lseg_list(&head);
			nfs_commit_inode(inode, 0);
		पूर्ण अन्यथा
			spin_unlock(&inode->i_lock);
		अवरोध;
	हाल -NFS4ERR_OLD_STATEID:
		spin_lock(&inode->i_lock);
		अगर (pnfs_layout_is_valid(lo) &&
		    nfs4_stateid_match_other(&data->args.errors[0].stateid,
					&lo->plh_stateid)) अणु
			/* Do we need to delay beक्रमe resending? */
			अगर (!nfs4_stateid_is_newer(&lo->plh_stateid,
						&data->args.errors[0].stateid))
				rpc_delay(task, HZ);
			rpc_restart_call_prepare(task);
		पूर्ण
		spin_unlock(&inode->i_lock);
		अवरोध;
	हाल -ENOTSUPP:
	हाल -EOPNOTSUPP:
		NFS_SERVER(inode)->caps &= ~NFS_CAP_LAYOUTERROR;
	पूर्ण

	trace_nfs4_layouterror(inode, &data->args.errors[0].stateid,
			       task->tk_status);
पूर्ण

अटल व्योम
nfs42_layouterror_release(व्योम *calldata)
अणु
	काष्ठा nfs42_layouterror_data *data = calldata;

	nfs42_मुक्त_layouterror_data(data);
पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfs42_layouterror_ops = अणु
	.rpc_call_prepare = nfs42_layouterror_prepare,
	.rpc_call_करोne = nfs42_layouterror_करोne,
	.rpc_release = nfs42_layouterror_release,
पूर्ण;

पूर्णांक nfs42_proc_layouterror(काष्ठा pnfs_layout_segment *lseg,
		स्थिर काष्ठा nfs42_layout_error *errors, माप_प्रकार n)
अणु
	काष्ठा inode *inode = lseg->pls_layout->plh_inode;
	काष्ठा nfs42_layouterror_data *data;
	काष्ठा rpc_task *task;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_LAYOUTERROR],
	पूर्ण;
	काष्ठा rpc_task_setup task_setup = अणु
		.rpc_message = &msg,
		.callback_ops = &nfs42_layouterror_ops,
		.flags = RPC_TASK_ASYNC,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	अगर (!nfs_server_capable(inode, NFS_CAP_LAYOUTERROR))
		वापस -EOPNOTSUPP;
	अगर (n > NFS42_LAYOUTERROR_MAX)
		वापस -EINVAL;
	data = nfs42_alloc_layouterror_data(lseg, GFP_NOFS);
	अगर (!data)
		वापस -ENOMEM;
	क्रम (i = 0; i < n; i++) अणु
		data->args.errors[i] = errors[i];
		data->args.num_errors++;
		data->res.num_errors++;
	पूर्ण
	msg.rpc_argp = &data->args;
	msg.rpc_resp = &data->res;
	task_setup.callback_data = data;
	task_setup.rpc_client = NFS_SERVER(inode)->client;
	nfs4_init_sequence(&data->args.seq_args, &data->res.seq_res, 0, 0);
	task = rpc_run_task(&task_setup);
	अगर (IS_ERR(task))
		वापस PTR_ERR(task);
	rpc_put_task(task);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(nfs42_proc_layouterror);

अटल पूर्णांक _nfs42_proc_clone(काष्ठा rpc_message *msg, काष्ठा file *src_f,
		काष्ठा file *dst_f, काष्ठा nfs_lock_context *src_lock,
		काष्ठा nfs_lock_context *dst_lock, loff_t src_offset,
		loff_t dst_offset, loff_t count)
अणु
	काष्ठा inode *src_inode = file_inode(src_f);
	काष्ठा inode *dst_inode = file_inode(dst_f);
	काष्ठा nfs_server *server = NFS_SERVER(dst_inode);
	काष्ठा nfs42_clone_args args = अणु
		.src_fh = NFS_FH(src_inode),
		.dst_fh = NFS_FH(dst_inode),
		.src_offset = src_offset,
		.dst_offset = dst_offset,
		.count = count,
		.dst_biपंचांगask = server->cache_consistency_biपंचांगask,
	पूर्ण;
	काष्ठा nfs42_clone_res res = अणु
		.server	= server,
	पूर्ण;
	पूर्णांक status;

	msg->rpc_argp = &args;
	msg->rpc_resp = &res;

	status = nfs4_set_rw_stateid(&args.src_stateid, src_lock->खोलो_context,
			src_lock, FMODE_READ);
	अगर (status) अणु
		अगर (status == -EAGAIN)
			status = -NFS4ERR_BAD_STATEID;
		वापस status;
	पूर्ण
	status = nfs4_set_rw_stateid(&args.dst_stateid, dst_lock->खोलो_context,
			dst_lock, FMODE_WRITE);
	अगर (status) अणु
		अगर (status == -EAGAIN)
			status = -NFS4ERR_BAD_STATEID;
		वापस status;
	पूर्ण

	res.dst_fattr = nfs_alloc_fattr();
	अगर (!res.dst_fattr)
		वापस -ENOMEM;

	status = nfs4_call_sync(server->client, server, msg,
				&args.seq_args, &res.seq_res, 0);
	अगर (status == 0) अणु
		nfs42_copy_dest_करोne(dst_inode, dst_offset, count);
		status = nfs_post_op_update_inode(dst_inode, res.dst_fattr);
	पूर्ण

	kमुक्त(res.dst_fattr);
	वापस status;
पूर्ण

पूर्णांक nfs42_proc_clone(काष्ठा file *src_f, काष्ठा file *dst_f,
		     loff_t src_offset, loff_t dst_offset, loff_t count)
अणु
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_CLONE],
	पूर्ण;
	काष्ठा inode *inode = file_inode(src_f);
	काष्ठा nfs_server *server = NFS_SERVER(file_inode(src_f));
	काष्ठा nfs_lock_context *src_lock;
	काष्ठा nfs_lock_context *dst_lock;
	काष्ठा nfs4_exception src_exception = अणु पूर्ण;
	काष्ठा nfs4_exception dst_exception = अणु पूर्ण;
	पूर्णांक err, err2;

	अगर (!nfs_server_capable(inode, NFS_CAP_CLONE))
		वापस -EOPNOTSUPP;

	src_lock = nfs_get_lock_context(nfs_file_खोलो_context(src_f));
	अगर (IS_ERR(src_lock))
		वापस PTR_ERR(src_lock);

	src_exception.inode = file_inode(src_f);
	src_exception.state = src_lock->खोलो_context->state;

	dst_lock = nfs_get_lock_context(nfs_file_खोलो_context(dst_f));
	अगर (IS_ERR(dst_lock)) अणु
		err = PTR_ERR(dst_lock);
		जाओ out_put_src_lock;
	पूर्ण

	dst_exception.inode = file_inode(dst_f);
	dst_exception.state = dst_lock->खोलो_context->state;

	करो अणु
		err = _nfs42_proc_clone(&msg, src_f, dst_f, src_lock, dst_lock,
					src_offset, dst_offset, count);
		अगर (err == -ENOTSUPP || err == -EOPNOTSUPP) अणु
			NFS_SERVER(inode)->caps &= ~NFS_CAP_CLONE;
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण

		err2 = nfs4_handle_exception(server, err, &src_exception);
		err = nfs4_handle_exception(server, err, &dst_exception);
		अगर (!err)
			err = err2;
	पूर्ण जबतक (src_exception.retry || dst_exception.retry);

	nfs_put_lock_context(dst_lock);
out_put_src_lock:
	nfs_put_lock_context(src_lock);
	वापस err;
पूर्ण

#घोषणा NFS4XATTR_MAXPAGES DIV_ROUND_UP(XATTR_SIZE_MAX, PAGE_SIZE)

अटल पूर्णांक _nfs42_proc_हटाओxattr(काष्ठा inode *inode, स्थिर अक्षर *name)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs42_हटाओxattrargs args = अणु
		.fh = NFS_FH(inode),
		.xattr_name = name,
	पूर्ण;
	काष्ठा nfs42_हटाओxattrres res;
	काष्ठा rpc_message msg = अणु
		.rpc_proc = &nfs4_procedures[NFSPROC4_CLNT_REMOVEXATTR],
		.rpc_argp = &args,
		.rpc_resp = &res,
	पूर्ण;
	पूर्णांक ret;
	अचिन्हित दीर्घ बारtamp = jअगरfies;

	ret = nfs4_call_sync(server->client, server, &msg, &args.seq_args,
	    &res.seq_res, 1);
	अगर (!ret)
		nfs4_update_changeattr(inode, &res.cinfo, बारtamp, 0);

	वापस ret;
पूर्ण

अटल पूर्णांक _nfs42_proc_setxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
				स्थिर व्योम *buf, माप_प्रकार buflen, पूर्णांक flags)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा page *pages[NFS4XATTR_MAXPAGES];
	काष्ठा nfs42_setxattrargs arg = अणु
		.fh		= NFS_FH(inode),
		.xattr_pages	= pages,
		.xattr_len	= buflen,
		.xattr_name	= name,
		.xattr_flags	= flags,
	पूर्ण;
	काष्ठा nfs42_setxattrres res;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_SETXATTR],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
	पूर्ण;
	पूर्णांक ret, np;
	अचिन्हित दीर्घ बारtamp = jअगरfies;

	अगर (buflen > server->sxasize)
		वापस -दुस्फल;

	अगर (buflen > 0) अणु
		np = nfs4_buf_to_pages_noslab(buf, buflen, arg.xattr_pages);
		अगर (np < 0)
			वापस np;
	पूर्ण अन्यथा
		np = 0;

	ret = nfs4_call_sync(server->client, server, &msg, &arg.seq_args,
	    &res.seq_res, 1);

	क्रम (; np > 0; np--)
		put_page(pages[np - 1]);

	अगर (!ret)
		nfs4_update_changeattr(inode, &res.cinfo, बारtamp, 0);

	वापस ret;
पूर्ण

अटल sमाप_प्रकार _nfs42_proc_getxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
				व्योम *buf, माप_प्रकार buflen, काष्ठा page **pages,
				माप_प्रकार plen)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा nfs42_getxattrargs arg = अणु
		.fh		= NFS_FH(inode),
		.xattr_name	= name,
	पूर्ण;
	काष्ठा nfs42_getxattrres res;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_GETXATTR],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
	पूर्ण;
	sमाप_प्रकार ret;

	arg.xattr_len = plen;
	arg.xattr_pages = pages;

	ret = nfs4_call_sync(server->client, server, &msg, &arg.seq_args,
	    &res.seq_res, 0);
	अगर (ret < 0)
		वापस ret;

	/*
	 * Normally, the caching is करोne one layer up, but क्रम successful
	 * RPCS, always cache the result here, even अगर the caller was
	 * just querying the length, or अगर the reply was too big क्रम
	 * the caller. This aव्योमs a second RPC in the हाल of the
	 * common query-alloc-retrieve cycle क्रम xattrs.
	 *
	 * Note that xattr_len is always capped to XATTR_SIZE_MAX.
	 */

	nfs4_xattr_cache_add(inode, name, शून्य, pages, res.xattr_len);

	अगर (buflen) अणु
		अगर (res.xattr_len > buflen)
			वापस -दुस्फल;
		_copy_from_pages(buf, pages, 0, res.xattr_len);
	पूर्ण

	वापस res.xattr_len;
पूर्ण

अटल sमाप_प्रकार _nfs42_proc_listxattrs(काष्ठा inode *inode, व्योम *buf,
				 माप_प्रकार buflen, u64 *cookiep, bool *eofp)
अणु
	काष्ठा nfs_server *server = NFS_SERVER(inode);
	काष्ठा page **pages;
	काष्ठा nfs42_listxattrsargs arg = अणु
		.fh		= NFS_FH(inode),
		.cookie		= *cookiep,
	पूर्ण;
	काष्ठा nfs42_listxattrsres res = अणु
		.eof = false,
		.xattr_buf = buf,
		.xattr_len = buflen,
	पूर्ण;
	काष्ठा rpc_message msg = अणु
		.rpc_proc	= &nfs4_procedures[NFSPROC4_CLNT_LISTXATTRS],
		.rpc_argp	= &arg,
		.rpc_resp	= &res,
	पूर्ण;
	u32 xdrlen;
	पूर्णांक ret, np, i;


	ret = -ENOMEM;
	res.scratch = alloc_page(GFP_KERNEL);
	अगर (!res.scratch)
		जाओ out;

	xdrlen = nfs42_listxattr_xdrsize(buflen);
	अगर (xdrlen > server->lxasize)
		xdrlen = server->lxasize;
	np = xdrlen / PAGE_SIZE + 1;

	pages = kसुस्मृति(np, माप(काष्ठा page *), GFP_KERNEL);
	अगर (!pages)
		जाओ out_मुक्त_scratch;
	क्रम (i = 0; i < np; i++) अणु
		pages[i] = alloc_page(GFP_KERNEL);
		अगर (!pages[i])
			जाओ out_मुक्त_pages;
	पूर्ण

	arg.xattr_pages = pages;
	arg.count = xdrlen;

	ret = nfs4_call_sync(server->client, server, &msg, &arg.seq_args,
	    &res.seq_res, 0);

	अगर (ret >= 0) अणु
		ret = res.copied;
		*cookiep = res.cookie;
		*eofp = res.eof;
	पूर्ण

out_मुक्त_pages:
	जबतक (--np >= 0) अणु
		अगर (pages[np])
			__मुक्त_page(pages[np]);
	पूर्ण
	kमुक्त(pages);
out_मुक्त_scratch:
	__मुक्त_page(res.scratch);
out:
	वापस ret;

पूर्ण

sमाप_प्रकार nfs42_proc_getxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
			      व्योम *buf, माप_प्रकार buflen)
अणु
	काष्ठा nfs4_exception exception = अणु पूर्ण;
	sमाप_प्रकार err, np, i;
	काष्ठा page **pages;

	np = nfs_page_array_len(0, buflen ?: XATTR_SIZE_MAX);
	pages = kदो_स्मृति_array(np, माप(*pages), GFP_KERNEL);
	अगर (!pages)
		वापस -ENOMEM;

	क्रम (i = 0; i < np; i++) अणु
		pages[i] = alloc_page(GFP_KERNEL);
		अगर (!pages[i]) अणु
			np = i + 1;
			err = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * The GETXATTR op has no length field in the call, and the
	 * xattr data is at the end of the reply.
	 *
	 * There is no करोwnside in using the page-aligned length. It will
	 * allow receiving and caching xattrs that are too large क्रम the
	 * caller but still fit in the page-rounded value.
	 */
	करो अणु
		err = _nfs42_proc_getxattr(inode, name, buf, buflen,
			pages, np * PAGE_SIZE);
		अगर (err >= 0)
			अवरोध;
		err = nfs4_handle_exception(NFS_SERVER(inode), err,
				&exception);
	पूर्ण जबतक (exception.retry);

out:
	जबतक (--np >= 0)
		__मुक्त_page(pages[np]);
	kमुक्त(pages);

	वापस err;
पूर्ण

पूर्णांक nfs42_proc_setxattr(काष्ठा inode *inode, स्थिर अक्षर *name,
			      स्थिर व्योम *buf, माप_प्रकार buflen, पूर्णांक flags)
अणु
	काष्ठा nfs4_exception exception = अणु पूर्ण;
	पूर्णांक err;

	करो अणु
		err = _nfs42_proc_setxattr(inode, name, buf, buflen, flags);
		अगर (!err)
			अवरोध;
		err = nfs4_handle_exception(NFS_SERVER(inode), err,
				&exception);
	पूर्ण जबतक (exception.retry);

	वापस err;
पूर्ण

sमाप_प्रकार nfs42_proc_listxattrs(काष्ठा inode *inode, व्योम *buf,
			      माप_प्रकार buflen, u64 *cookiep, bool *eofp)
अणु
	काष्ठा nfs4_exception exception = अणु पूर्ण;
	sमाप_प्रकार err;

	करो अणु
		err = _nfs42_proc_listxattrs(inode, buf, buflen,
		    cookiep, eofp);
		अगर (err >= 0)
			अवरोध;
		err = nfs4_handle_exception(NFS_SERVER(inode), err,
				&exception);
	पूर्ण जबतक (exception.retry);

	वापस err;
पूर्ण

पूर्णांक nfs42_proc_हटाओxattr(काष्ठा inode *inode, स्थिर अक्षर *name)
अणु
	काष्ठा nfs4_exception exception = अणु पूर्ण;
	पूर्णांक err;

	करो अणु
		err = _nfs42_proc_हटाओxattr(inode, name);
		अगर (!err)
			अवरोध;
		err = nfs4_handle_exception(NFS_SERVER(inode), err,
				&exception);
	पूर्ण जबतक (exception.retry);

	वापस err;
पूर्ण
