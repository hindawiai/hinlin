<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* YFS File Server client stubs
 *
 * Copyright (C) 2018 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/iversion.h>
#समावेश "internal.h"
#समावेश "afs_fs.h"
#समावेश "xdr_fs.h"
#समावेश "protocol_yfs.h"

#घोषणा xdr_size(x) (माप(*x) / माप(__be32))

अटल व्योम xdr_decode_YFSFid(स्थिर __be32 **_bp, काष्ठा afs_fid *fid)
अणु
	स्थिर काष्ठा yfs_xdr_YFSFid *x = (स्थिर व्योम *)*_bp;

	fid->vid	= xdr_to_u64(x->volume);
	fid->vnode	= xdr_to_u64(x->vnode.lo);
	fid->vnode_hi	= ntohl(x->vnode.hi);
	fid->unique	= ntohl(x->vnode.unique);
	*_bp += xdr_size(x);
पूर्ण

अटल __be32 *xdr_encode_u32(__be32 *bp, u32 n)
अणु
	*bp++ = htonl(n);
	वापस bp;
पूर्ण

अटल __be32 *xdr_encode_u64(__be32 *bp, u64 n)
अणु
	काष्ठा yfs_xdr_u64 *x = (व्योम *)bp;

	*x = u64_to_xdr(n);
	वापस bp + xdr_size(x);
पूर्ण

अटल __be32 *xdr_encode_YFSFid(__be32 *bp, काष्ठा afs_fid *fid)
अणु
	काष्ठा yfs_xdr_YFSFid *x = (व्योम *)bp;

	x->volume	= u64_to_xdr(fid->vid);
	x->vnode.lo	= u64_to_xdr(fid->vnode);
	x->vnode.hi	= htonl(fid->vnode_hi);
	x->vnode.unique	= htonl(fid->unique);
	वापस bp + xdr_size(x);
पूर्ण

अटल माप_प्रकार xdr_म_माप(अचिन्हित पूर्णांक len)
अणु
	वापस माप(__be32) + round_up(len, माप(__be32));
पूर्ण

अटल __be32 *xdr_encode_string(__be32 *bp, स्थिर अक्षर *p, अचिन्हित पूर्णांक len)
अणु
	bp = xdr_encode_u32(bp, len);
	bp = स_नकल(bp, p, len);
	अगर (len & 3) अणु
		अचिन्हित पूर्णांक pad = 4 - (len & 3);

		स_रखो((u8 *)bp + len, 0, pad);
		len += pad;
	पूर्ण

	वापस bp + len / माप(__be32);
पूर्ण

अटल __be32 *xdr_encode_name(__be32 *bp, स्थिर काष्ठा qstr *p)
अणु
	वापस xdr_encode_string(bp, p->name, p->len);
पूर्ण

अटल s64 linux_to_yfs_समय(स्थिर काष्ठा बारpec64 *t)
अणु
	/* Convert to 100ns पूर्णांकervals. */
	वापस (u64)t->tv_sec * 10000000 + t->tv_nsec/100;
पूर्ण

अटल __be32 *xdr_encode_YFSStoreStatus_mode(__be32 *bp, mode_t mode)
अणु
	काष्ठा yfs_xdr_YFSStoreStatus *x = (व्योम *)bp;

	x->mask		= htonl(AFS_SET_MODE);
	x->mode		= htonl(mode & S_IALLUGO);
	x->mसमय_client	= u64_to_xdr(0);
	x->owner	= u64_to_xdr(0);
	x->group	= u64_to_xdr(0);
	वापस bp + xdr_size(x);
पूर्ण

अटल __be32 *xdr_encode_YFSStoreStatus_mसमय(__be32 *bp, स्थिर काष्ठा बारpec64 *t)
अणु
	काष्ठा yfs_xdr_YFSStoreStatus *x = (व्योम *)bp;
	s64 mसमय = linux_to_yfs_समय(t);

	x->mask		= htonl(AFS_SET_MTIME);
	x->mode		= htonl(0);
	x->mसमय_client	= u64_to_xdr(mसमय);
	x->owner	= u64_to_xdr(0);
	x->group	= u64_to_xdr(0);
	वापस bp + xdr_size(x);
पूर्ण

/*
 * Convert a चिन्हित 100ns-resolution 64-bit समय पूर्णांकo a बारpec.
 */
अटल काष्ठा बारpec64 yfs_समय_प्रकारo_linux(s64 t)
अणु
	काष्ठा बारpec64 ts;
	u64 असल_t;

	/*
	 * Unक्रमtunately can not use normal 64 bit भागision on 32 bit arch, but
	 * the alternative, करो_भाग, करोes not work with negative numbers so have
	 * to special हाल them
	 */
	अगर (t < 0) अणु
		असल_t = -t;
		ts.tv_nsec = (समय64_t)(करो_भाग(असल_t, 10000000) * 100);
		ts.tv_nsec = -ts.tv_nsec;
		ts.tv_sec = -असल_t;
	पूर्ण अन्यथा अणु
		असल_t = t;
		ts.tv_nsec = (समय64_t)करो_भाग(असल_t, 10000000) * 100;
		ts.tv_sec = असल_t;
	पूर्ण

	वापस ts;
पूर्ण

अटल काष्ठा बारpec64 xdr_to_समय(स्थिर काष्ठा yfs_xdr_u64 xdr)
अणु
	s64 t = xdr_to_u64(xdr);

	वापस yfs_समय_प्रकारo_linux(t);
पूर्ण

अटल व्योम yfs_check_req(काष्ठा afs_call *call, __be32 *bp)
अणु
	माप_प्रकार len = (व्योम *)bp - call->request;

	अगर (len > call->request_size)
		pr_err("kAFS: %s: Request buffer overflow (%zu>%u)\n",
		       call->type->name, len, call->request_size);
	अन्यथा अगर (len < call->request_size)
		pr_warn("kAFS: %s: Request buffer underflow (%zu<%u)\n",
			call->type->name, len, call->request_size);
पूर्ण

/*
 * Dump a bad file status record.
 */
अटल व्योम xdr_dump_bad(स्थिर __be32 *bp)
अणु
	__be32 x[4];
	पूर्णांक i;

	pr_notice("YFS XDR: Bad status record\n");
	क्रम (i = 0; i < 6 * 4 * 4; i += 16) अणु
		स_नकल(x, bp, 16);
		bp += 4;
		pr_notice("%03x: %08x %08x %08x %08x\n",
			  i, ntohl(x[0]), ntohl(x[1]), ntohl(x[2]), ntohl(x[3]));
	पूर्ण

	स_नकल(x, bp, 8);
	pr_notice("0x60: %08x %08x\n", ntohl(x[0]), ntohl(x[1]));
पूर्ण

/*
 * Decode a YFSFetchStatus block
 */
अटल व्योम xdr_decode_YFSFetchStatus(स्थिर __be32 **_bp,
				      काष्ठा afs_call *call,
				      काष्ठा afs_status_cb *scb)
अणु
	स्थिर काष्ठा yfs_xdr_YFSFetchStatus *xdr = (स्थिर व्योम *)*_bp;
	काष्ठा afs_file_status *status = &scb->status;
	u32 type;

	status->पात_code = ntohl(xdr->पात_code);
	अगर (status->पात_code != 0) अणु
		अगर (status->पात_code == VNOVNODE)
			status->nlink = 0;
		scb->have_error = true;
		जाओ advance;
	पूर्ण

	type = ntohl(xdr->type);
	चयन (type) अणु
	हाल AFS_FTYPE_खाता:
	हाल AFS_FTYPE_सूची:
	हाल AFS_FTYPE_SYMLINK:
		status->type = type;
		अवरोध;
	शेष:
		जाओ bad;
	पूर्ण

	status->nlink		= ntohl(xdr->nlink);
	status->author		= xdr_to_u64(xdr->author);
	status->owner		= xdr_to_u64(xdr->owner);
	status->caller_access	= ntohl(xdr->caller_access); /* Ticket dependent */
	status->anon_access	= ntohl(xdr->anon_access);
	status->mode		= ntohl(xdr->mode) & S_IALLUGO;
	status->group		= xdr_to_u64(xdr->group);
	status->lock_count	= ntohl(xdr->lock_count);

	status->mसमय_client	= xdr_to_समय(xdr->mसमय_client);
	status->mसमय_server	= xdr_to_समय(xdr->mसमय_server);
	status->size		= xdr_to_u64(xdr->size);
	status->data_version	= xdr_to_u64(xdr->data_version);
	scb->have_status	= true;
advance:
	*_bp += xdr_size(xdr);
	वापस;

bad:
	xdr_dump_bad(*_bp);
	afs_protocol_error(call, afs_eproto_bad_status);
	जाओ advance;
पूर्ण

/*
 * Decode a YFSCallBack block
 */
अटल व्योम xdr_decode_YFSCallBack(स्थिर __be32 **_bp,
				   काष्ठा afs_call *call,
				   काष्ठा afs_status_cb *scb)
अणु
	काष्ठा yfs_xdr_YFSCallBack *x = (व्योम *)*_bp;
	काष्ठा afs_callback *cb = &scb->callback;
	kसमय_प्रकार cb_expiry;

	cb_expiry = call->reply_समय;
	cb_expiry = kसमय_add(cb_expiry, xdr_to_u64(x->expiration_समय) * 100);
	cb->expires_at	= kसमय_भागns(cb_expiry, NSEC_PER_SEC);
	scb->have_cb	= true;
	*_bp += xdr_size(x);
पूर्ण

/*
 * Decode a YFSVolSync block
 */
अटल व्योम xdr_decode_YFSVolSync(स्थिर __be32 **_bp,
				  काष्ठा afs_volsync *volsync)
अणु
	काष्ठा yfs_xdr_YFSVolSync *x = (व्योम *)*_bp;
	u64 creation;

	अगर (volsync) अणु
		creation = xdr_to_u64(x->vol_creation_date);
		करो_भाग(creation, 10 * 1000 * 1000);
		volsync->creation = creation;
	पूर्ण

	*_bp += xdr_size(x);
पूर्ण

/*
 * Encode the requested attributes पूर्णांकo a YFSStoreStatus block
 */
अटल __be32 *xdr_encode_YFS_StoreStatus(__be32 *bp, काष्ठा iattr *attr)
अणु
	काष्ठा yfs_xdr_YFSStoreStatus *x = (व्योम *)bp;
	s64 mसमय = 0, owner = 0, group = 0;
	u32 mask = 0, mode = 0;

	mask = 0;
	अगर (attr->ia_valid & ATTR_MTIME) अणु
		mask |= AFS_SET_MTIME;
		mसमय = linux_to_yfs_समय(&attr->ia_mसमय);
	पूर्ण

	अगर (attr->ia_valid & ATTR_UID) अणु
		mask |= AFS_SET_OWNER;
		owner = from_kuid(&init_user_ns, attr->ia_uid);
	पूर्ण

	अगर (attr->ia_valid & ATTR_GID) अणु
		mask |= AFS_SET_GROUP;
		group = from_kgid(&init_user_ns, attr->ia_gid);
	पूर्ण

	अगर (attr->ia_valid & ATTR_MODE) अणु
		mask |= AFS_SET_MODE;
		mode = attr->ia_mode & S_IALLUGO;
	पूर्ण

	x->mask		= htonl(mask);
	x->mode		= htonl(mode);
	x->mसमय_client	= u64_to_xdr(mसमय);
	x->owner	= u64_to_xdr(owner);
	x->group	= u64_to_xdr(group);
	वापस bp + xdr_size(x);
पूर्ण

/*
 * Decode a YFSFetchVolumeStatus block.
 */
अटल व्योम xdr_decode_YFSFetchVolumeStatus(स्थिर __be32 **_bp,
					    काष्ठा afs_volume_status *vs)
अणु
	स्थिर काष्ठा yfs_xdr_YFSFetchVolumeStatus *x = (स्थिर व्योम *)*_bp;
	u32 flags;

	vs->vid			= xdr_to_u64(x->vid);
	vs->parent_id		= xdr_to_u64(x->parent_id);
	flags			= ntohl(x->flags);
	vs->online		= flags & yfs_FVSOnline;
	vs->in_service		= flags & yfs_FVSInservice;
	vs->blessed		= flags & yfs_FVSBlessed;
	vs->needs_salvage	= flags & yfs_FVSNeedsSalvage;
	vs->type		= ntohl(x->type);
	vs->min_quota		= 0;
	vs->max_quota		= xdr_to_u64(x->max_quota);
	vs->blocks_in_use	= xdr_to_u64(x->blocks_in_use);
	vs->part_blocks_avail	= xdr_to_u64(x->part_blocks_avail);
	vs->part_max_blocks	= xdr_to_u64(x->part_max_blocks);
	vs->vol_copy_date	= xdr_to_u64(x->vol_copy_date);
	vs->vol_backup_date	= xdr_to_u64(x->vol_backup_date);
	*_bp += माप(*x) / माप(__be32);
पूर्ण

/*
 * Deliver reply data to operations that just वापस a file status and a volume
 * sync record.
 */
अटल पूर्णांक yfs_deliver_status_and_volsync(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	स्थिर __be32 *bp;
	पूर्णांक ret;

	ret = afs_transfer_reply(call);
	अगर (ret < 0)
		वापस ret;

	bp = call->buffer;
	xdr_decode_YFSFetchStatus(&bp, call, &op->file[0].scb);
	xdr_decode_YFSVolSync(&bp, &op->volsync);

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * Deliver reply data to an YFS.FetchData64.
 */
अटल पूर्णांक yfs_deliver_fs_fetch_data64(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_पढ़ो *req = op->fetch.req;
	स्थिर __be32 *bp;
	पूर्णांक ret;

	_enter("{%u,%zu, %zu/%llu}",
	       call->unmarshall, call->iov_len, iov_iter_count(call->iter),
	       req->actual_len);

	चयन (call->unmarshall) अणु
	हाल 0:
		req->actual_len = 0;
		afs_extract_to_पंचांगp64(call);
		call->unmarshall++;
		fallthrough;

		/* Extract the वापसed data length पूर्णांकo ->actual_len.  This
		 * may indicate more or less data than was requested will be
		 * वापसed.
		 */
	हाल 1:
		_debug("extract data length");
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		req->actual_len = be64_to_cpu(call->पंचांगp64);
		_debug("DATA length: %llu", req->actual_len);

		अगर (req->actual_len == 0)
			जाओ no_more_data;

		call->iter = req->iter;
		call->iov_len = min(req->actual_len, req->len);
		call->unmarshall++;
		fallthrough;

		/* extract the वापसed data */
	हाल 2:
		_debug("extract data %zu/%llu",
		       iov_iter_count(call->iter), req->actual_len);

		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		call->iter = &call->def_iter;
		अगर (req->actual_len <= req->len)
			जाओ no_more_data;

		/* Discard any excess data the server gave us */
		afs_extract_discard(call, req->actual_len - req->len);
		call->unmarshall = 3;
		fallthrough;

	हाल 3:
		_debug("extract discard %zu/%llu",
		       iov_iter_count(call->iter), req->actual_len - req->len);

		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

	no_more_data:
		call->unmarshall = 4;
		afs_extract_to_buf(call,
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSCallBack) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
		fallthrough;

		/* extract the metadata */
	हाल 4:
		ret = afs_extract_data(call, false);
		अगर (ret < 0)
			वापस ret;

		bp = call->buffer;
		xdr_decode_YFSFetchStatus(&bp, call, &vp->scb);
		xdr_decode_YFSCallBack(&bp, call, &vp->scb);
		xdr_decode_YFSVolSync(&bp, &op->volsync);

		req->data_version = vp->scb.status.data_version;
		req->file_size = vp->scb.status.size;

		call->unmarshall++;
		fallthrough;

	हाल 5:
		अवरोध;
	पूर्ण

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * YFS.FetchData64 operation type
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSFetchData64 = अणु
	.name		= "YFS.FetchData64",
	.op		= yfs_FS_FetchData64,
	.deliver	= yfs_deliver_fs_fetch_data64,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Fetch data from a file.
 */
व्योम yfs_fs_fetch_data(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_पढ़ो *req = op->fetch.req;
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter(",%x,{%llx:%llu},%llx,%llx",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode,
	       req->pos, req->len);

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSFetchData64,
				   माप(__be32) * 2 +
				   माप(काष्ठा yfs_xdr_YFSFid) +
				   माप(काष्ठा yfs_xdr_u64) * 2,
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSCallBack) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	req->call_debug_id = call->debug_id;

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSFETCHDATA64);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &vp->fid);
	bp = xdr_encode_u64(bp, req->pos);
	bp = xdr_encode_u64(bp, req->len);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * Deliver reply data क्रम YFS.CreateFile or YFS.MakeDir.
 */
अटल पूर्णांक yfs_deliver_fs_create_vnode(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_vnode_param *vp = &op->file[1];
	स्थिर __be32 *bp;
	पूर्णांक ret;

	_enter("{%u}", call->unmarshall);

	ret = afs_transfer_reply(call);
	अगर (ret < 0)
		वापस ret;

	/* unmarshall the reply once we've received all of it */
	bp = call->buffer;
	xdr_decode_YFSFid(&bp, &op->file[1].fid);
	xdr_decode_YFSFetchStatus(&bp, call, &vp->scb);
	xdr_decode_YFSFetchStatus(&bp, call, &dvp->scb);
	xdr_decode_YFSCallBack(&bp, call, &vp->scb);
	xdr_decode_YFSVolSync(&bp, &op->volsync);

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * FS.CreateFile and FS.MakeDir operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSCreateFile = अणु
	.name		= "YFS.CreateFile",
	.op		= yfs_FS_CreateFile,
	.deliver	= yfs_deliver_fs_create_vnode,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Create a file.
 */
व्योम yfs_fs_create_file(काष्ठा afs_operation *op)
अणु
	स्थिर काष्ठा qstr *name = &op->dentry->d_name;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_call *call;
	माप_प्रकार reqsz, rplsz;
	__be32 *bp;

	_enter("");

	reqsz = (माप(__be32) +
		 माप(__be32) +
		 माप(काष्ठा yfs_xdr_YFSFid) +
		 xdr_म_माप(name->len) +
		 माप(काष्ठा yfs_xdr_YFSStoreStatus) +
		 माप(__be32));
	rplsz = (माप(काष्ठा yfs_xdr_YFSFid) +
		 माप(काष्ठा yfs_xdr_YFSFetchStatus) +
		 माप(काष्ठा yfs_xdr_YFSFetchStatus) +
		 माप(काष्ठा yfs_xdr_YFSCallBack) +
		 माप(काष्ठा yfs_xdr_YFSVolSync));

	call = afs_alloc_flat_call(op->net, &afs_RXFSCreateFile, reqsz, rplsz);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSCREATEखाता);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &dvp->fid);
	bp = xdr_encode_name(bp, name);
	bp = xdr_encode_YFSStoreStatus_mode(bp, op->create.mode);
	bp = xdr_encode_u32(bp, yfs_LockNone); /* ViceLockType */
	yfs_check_req(call, bp);

	trace_afs_make_fs_call1(call, &dvp->fid, name);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

अटल स्थिर काष्ठा afs_call_type yfs_RXFSMakeDir = अणु
	.name		= "YFS.MakeDir",
	.op		= yfs_FS_MakeDir,
	.deliver	= yfs_deliver_fs_create_vnode,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Make a directory.
 */
व्योम yfs_fs_make_dir(काष्ठा afs_operation *op)
अणु
	स्थिर काष्ठा qstr *name = &op->dentry->d_name;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_call *call;
	माप_प्रकार reqsz, rplsz;
	__be32 *bp;

	_enter("");

	reqsz = (माप(__be32) +
		 माप(काष्ठा yfs_xdr_RPCFlags) +
		 माप(काष्ठा yfs_xdr_YFSFid) +
		 xdr_म_माप(name->len) +
		 माप(काष्ठा yfs_xdr_YFSStoreStatus));
	rplsz = (माप(काष्ठा yfs_xdr_YFSFid) +
		 माप(काष्ठा yfs_xdr_YFSFetchStatus) +
		 माप(काष्ठा yfs_xdr_YFSFetchStatus) +
		 माप(काष्ठा yfs_xdr_YFSCallBack) +
		 माप(काष्ठा yfs_xdr_YFSVolSync));

	call = afs_alloc_flat_call(op->net, &yfs_RXFSMakeDir, reqsz, rplsz);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSMAKEसूची);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &dvp->fid);
	bp = xdr_encode_name(bp, name);
	bp = xdr_encode_YFSStoreStatus_mode(bp, op->create.mode);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call1(call, &dvp->fid, name);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * Deliver reply data to a YFS.RemoveFile2 operation.
 */
अटल पूर्णांक yfs_deliver_fs_हटाओ_file2(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_vnode_param *vp = &op->file[1];
	काष्ठा afs_fid fid;
	स्थिर __be32 *bp;
	पूर्णांक ret;

	_enter("{%u}", call->unmarshall);

	ret = afs_transfer_reply(call);
	अगर (ret < 0)
		वापस ret;

	bp = call->buffer;
	xdr_decode_YFSFetchStatus(&bp, call, &dvp->scb);
	xdr_decode_YFSFid(&bp, &fid);
	xdr_decode_YFSFetchStatus(&bp, call, &vp->scb);
	/* Was deleted अगर vnode->status.पात_code == VNOVNODE. */

	xdr_decode_YFSVolSync(&bp, &op->volsync);
	वापस 0;
पूर्ण

अटल व्योम yfs_करोne_fs_हटाओ_file2(काष्ठा afs_call *call)
अणु
	अगर (call->error == -ECONNABORTED &&
	    call->पात_code == RX_INVALID_OPERATION) अणु
		set_bit(AFS_SERVER_FL_NO_RM2, &call->server->flags);
		call->op->flags |= AFS_OPERATION_DOWNGRADE;
	पूर्ण
पूर्ण

/*
 * YFS.RemoveFile2 operation type.
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSRemoveFile2 = अणु
	.name		= "YFS.RemoveFile2",
	.op		= yfs_FS_RemoveFile2,
	.deliver	= yfs_deliver_fs_हटाओ_file2,
	.करोne		= yfs_करोne_fs_हटाओ_file2,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Remove a file and retrieve new file status.
 */
व्योम yfs_fs_हटाओ_file2(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	स्थिर काष्ठा qstr *name = &op->dentry->d_name;
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSRemoveFile2,
				   माप(__be32) +
				   माप(काष्ठा yfs_xdr_RPCFlags) +
				   माप(काष्ठा yfs_xdr_YFSFid) +
				   xdr_म_माप(name->len),
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSFid) +
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSREMOVEखाता2);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &dvp->fid);
	bp = xdr_encode_name(bp, name);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call1(call, &dvp->fid, name);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * Deliver reply data to a YFS.RemoveFile or YFS.RemoveDir operation.
 */
अटल पूर्णांक yfs_deliver_fs_हटाओ(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	स्थिर __be32 *bp;
	पूर्णांक ret;

	_enter("{%u}", call->unmarshall);

	ret = afs_transfer_reply(call);
	अगर (ret < 0)
		वापस ret;

	bp = call->buffer;
	xdr_decode_YFSFetchStatus(&bp, call, &dvp->scb);
	xdr_decode_YFSVolSync(&bp, &op->volsync);
	वापस 0;
पूर्ण

/*
 * FS.RemoveDir and FS.RemoveFile operation types.
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSRemoveFile = अणु
	.name		= "YFS.RemoveFile",
	.op		= yfs_FS_RemoveFile,
	.deliver	= yfs_deliver_fs_हटाओ,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Remove a file.
 */
व्योम yfs_fs_हटाओ_file(काष्ठा afs_operation *op)
अणु
	स्थिर काष्ठा qstr *name = &op->dentry->d_name;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	अगर (!test_bit(AFS_SERVER_FL_NO_RM2, &op->server->flags))
		वापस yfs_fs_हटाओ_file2(op);

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSRemoveFile,
				   माप(__be32) +
				   माप(काष्ठा yfs_xdr_RPCFlags) +
				   माप(काष्ठा yfs_xdr_YFSFid) +
				   xdr_म_माप(name->len),
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSREMOVEखाता);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &dvp->fid);
	bp = xdr_encode_name(bp, name);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call1(call, &dvp->fid, name);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

अटल स्थिर काष्ठा afs_call_type yfs_RXYFSRemoveDir = अणु
	.name		= "YFS.RemoveDir",
	.op		= yfs_FS_RemoveDir,
	.deliver	= yfs_deliver_fs_हटाओ,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Remove a directory.
 */
व्योम yfs_fs_हटाओ_dir(काष्ठा afs_operation *op)
अणु
	स्थिर काष्ठा qstr *name = &op->dentry->d_name;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSRemoveDir,
				   माप(__be32) +
				   माप(काष्ठा yfs_xdr_RPCFlags) +
				   माप(काष्ठा yfs_xdr_YFSFid) +
				   xdr_म_माप(name->len),
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSREMOVEसूची);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &dvp->fid);
	bp = xdr_encode_name(bp, name);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call1(call, &dvp->fid, name);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * Deliver reply data to a YFS.Link operation.
 */
अटल पूर्णांक yfs_deliver_fs_link(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_vnode_param *vp = &op->file[1];
	स्थिर __be32 *bp;
	पूर्णांक ret;

	_enter("{%u}", call->unmarshall);

	ret = afs_transfer_reply(call);
	अगर (ret < 0)
		वापस ret;

	bp = call->buffer;
	xdr_decode_YFSFetchStatus(&bp, call, &vp->scb);
	xdr_decode_YFSFetchStatus(&bp, call, &dvp->scb);
	xdr_decode_YFSVolSync(&bp, &op->volsync);
	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * YFS.Link operation type.
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSLink = अणु
	.name		= "YFS.Link",
	.op		= yfs_FS_Link,
	.deliver	= yfs_deliver_fs_link,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Make a hard link.
 */
व्योम yfs_fs_link(काष्ठा afs_operation *op)
अणु
	स्थिर काष्ठा qstr *name = &op->dentry->d_name;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_vnode_param *vp = &op->file[1];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSLink,
				   माप(__be32) +
				   माप(काष्ठा yfs_xdr_RPCFlags) +
				   माप(काष्ठा yfs_xdr_YFSFid) +
				   xdr_म_माप(name->len) +
				   माप(काष्ठा yfs_xdr_YFSFid),
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSLINK);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &dvp->fid);
	bp = xdr_encode_name(bp, name);
	bp = xdr_encode_YFSFid(bp, &vp->fid);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call1(call, &vp->fid, name);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * Deliver reply data to a YFS.Symlink operation.
 */
अटल पूर्णांक yfs_deliver_fs_symlink(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_vnode_param *vp = &op->file[1];
	स्थिर __be32 *bp;
	पूर्णांक ret;

	_enter("{%u}", call->unmarshall);

	ret = afs_transfer_reply(call);
	अगर (ret < 0)
		वापस ret;

	/* unmarshall the reply once we've received all of it */
	bp = call->buffer;
	xdr_decode_YFSFid(&bp, &vp->fid);
	xdr_decode_YFSFetchStatus(&bp, call, &vp->scb);
	xdr_decode_YFSFetchStatus(&bp, call, &dvp->scb);
	xdr_decode_YFSVolSync(&bp, &op->volsync);

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * YFS.Symlink operation type
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSSymlink = अणु
	.name		= "YFS.Symlink",
	.op		= yfs_FS_Symlink,
	.deliver	= yfs_deliver_fs_symlink,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Create a symbolic link.
 */
व्योम yfs_fs_symlink(काष्ठा afs_operation *op)
अणु
	स्थिर काष्ठा qstr *name = &op->dentry->d_name;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_call *call;
	माप_प्रकार contents_sz;
	__be32 *bp;

	_enter("");

	contents_sz = म_माप(op->create.symlink);
	call = afs_alloc_flat_call(op->net, &yfs_RXYFSSymlink,
				   माप(__be32) +
				   माप(काष्ठा yfs_xdr_RPCFlags) +
				   माप(काष्ठा yfs_xdr_YFSFid) +
				   xdr_म_माप(name->len) +
				   xdr_म_माप(contents_sz) +
				   माप(काष्ठा yfs_xdr_YFSStoreStatus),
				   माप(काष्ठा yfs_xdr_YFSFid) +
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSSYMLINK);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &dvp->fid);
	bp = xdr_encode_name(bp, name);
	bp = xdr_encode_string(bp, op->create.symlink, contents_sz);
	bp = xdr_encode_YFSStoreStatus_mode(bp, S_IRWXUGO);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call1(call, &dvp->fid, name);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * Deliver reply data to a YFS.Rename operation.
 */
अटल पूर्णांक yfs_deliver_fs_नाम(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode_param *orig_dvp = &op->file[0];
	काष्ठा afs_vnode_param *new_dvp = &op->file[1];
	स्थिर __be32 *bp;
	पूर्णांक ret;

	_enter("{%u}", call->unmarshall);

	ret = afs_transfer_reply(call);
	अगर (ret < 0)
		वापस ret;

	bp = call->buffer;
	/* If the two dirs are the same, we have two copies of the same status
	 * report, so we just decode it twice.
	 */
	xdr_decode_YFSFetchStatus(&bp, call, &orig_dvp->scb);
	xdr_decode_YFSFetchStatus(&bp, call, &new_dvp->scb);
	xdr_decode_YFSVolSync(&bp, &op->volsync);
	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * YFS.Rename operation type
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSRename = अणु
	.name		= "FS.Rename",
	.op		= yfs_FS_Rename,
	.deliver	= yfs_deliver_fs_नाम,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Rename a file or directory.
 */
व्योम yfs_fs_नाम(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *orig_dvp = &op->file[0];
	काष्ठा afs_vnode_param *new_dvp = &op->file[1];
	स्थिर काष्ठा qstr *orig_name = &op->dentry->d_name;
	स्थिर काष्ठा qstr *new_name = &op->dentry_2->d_name;
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSRename,
				   माप(__be32) +
				   माप(काष्ठा yfs_xdr_RPCFlags) +
				   माप(काष्ठा yfs_xdr_YFSFid) +
				   xdr_म_माप(orig_name->len) +
				   माप(काष्ठा yfs_xdr_YFSFid) +
				   xdr_म_माप(new_name->len),
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSRENAME);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &orig_dvp->fid);
	bp = xdr_encode_name(bp, orig_name);
	bp = xdr_encode_YFSFid(bp, &new_dvp->fid);
	bp = xdr_encode_name(bp, new_name);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call2(call, &orig_dvp->fid, orig_name, new_name);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * YFS.StoreData64 operation type.
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSStoreData64 = अणु
	.name		= "YFS.StoreData64",
	.op		= yfs_FS_StoreData64,
	.deliver	= yfs_deliver_status_and_volsync,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Store a set of pages to a large file.
 */
व्योम yfs_fs_store_data(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter(",%x,{%llx:%llu},,",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode);

	_debug("size %llx, at %llx, i_size %llx",
	       (अचिन्हित दीर्घ दीर्घ)op->store.size,
	       (अचिन्हित दीर्घ दीर्घ)op->store.pos,
	       (अचिन्हित दीर्घ दीर्घ)op->store.i_size);

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSStoreData64,
				   माप(__be32) +
				   माप(__be32) +
				   माप(काष्ठा yfs_xdr_YFSFid) +
				   माप(काष्ठा yfs_xdr_YFSStoreStatus) +
				   माप(काष्ठा yfs_xdr_u64) * 3,
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	call->ग_लिखो_iter = op->store.ग_लिखो_iter;

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSSTOREDATA64);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &vp->fid);
	bp = xdr_encode_YFSStoreStatus_mसमय(bp, &op->mसमय);
	bp = xdr_encode_u64(bp, op->store.pos);
	bp = xdr_encode_u64(bp, op->store.size);
	bp = xdr_encode_u64(bp, op->store.i_size);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * YFS.StoreStatus operation type
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSStoreStatus = अणु
	.name		= "YFS.StoreStatus",
	.op		= yfs_FS_StoreStatus,
	.deliver	= yfs_deliver_status_and_volsync,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

अटल स्थिर काष्ठा afs_call_type yfs_RXYFSStoreData64_as_Status = अणु
	.name		= "YFS.StoreData64",
	.op		= yfs_FS_StoreData64,
	.deliver	= yfs_deliver_status_and_volsync,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Set the attributes on a file, using YFS.StoreData64 rather than
 * YFS.StoreStatus so as to alter the file size also.
 */
अटल व्योम yfs_fs_setattr_size(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	काष्ठा iattr *attr = op->setattr.attr;
	__be32 *bp;

	_enter(",%x,{%llx:%llu},,",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode);

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSStoreData64_as_Status,
				   माप(__be32) * 2 +
				   माप(काष्ठा yfs_xdr_YFSFid) +
				   माप(काष्ठा yfs_xdr_YFSStoreStatus) +
				   माप(काष्ठा yfs_xdr_u64) * 3,
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSSTOREDATA64);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &vp->fid);
	bp = xdr_encode_YFS_StoreStatus(bp, attr);
	bp = xdr_encode_u64(bp, attr->ia_size);	/* position of start of ग_लिखो */
	bp = xdr_encode_u64(bp, 0);		/* size of ग_लिखो */
	bp = xdr_encode_u64(bp, attr->ia_size);	/* new file length */
	yfs_check_req(call, bp);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * Set the attributes on a file, using YFS.StoreData64 अगर there's a change in
 * file size, and YFS.StoreStatus otherwise.
 */
व्योम yfs_fs_setattr(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	काष्ठा iattr *attr = op->setattr.attr;
	__be32 *bp;

	अगर (attr->ia_valid & ATTR_SIZE)
		वापस yfs_fs_setattr_size(op);

	_enter(",%x,{%llx:%llu},,",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode);

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSStoreStatus,
				   माप(__be32) * 2 +
				   माप(काष्ठा yfs_xdr_YFSFid) +
				   माप(काष्ठा yfs_xdr_YFSStoreStatus),
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSSTORESTATUS);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &vp->fid);
	bp = xdr_encode_YFS_StoreStatus(bp, attr);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * Deliver reply data to a YFS.GetVolumeStatus operation.
 */
अटल पूर्णांक yfs_deliver_fs_get_volume_status(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	स्थिर __be32 *bp;
	अक्षर *p;
	u32 size;
	पूर्णांक ret;

	_enter("{%u}", call->unmarshall);

	चयन (call->unmarshall) अणु
	हाल 0:
		call->unmarshall++;
		afs_extract_to_buf(call, माप(काष्ठा yfs_xdr_YFSFetchVolumeStatus));
		fallthrough;

		/* extract the वापसed status record */
	हाल 1:
		_debug("extract status");
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		bp = call->buffer;
		xdr_decode_YFSFetchVolumeStatus(&bp, &op->volstatus.vs);
		call->unmarshall++;
		afs_extract_to_पंचांगp(call);
		fallthrough;

		/* extract the volume name length */
	हाल 2:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		call->count = ntohl(call->पंचांगp);
		_debug("volname length: %u", call->count);
		अगर (call->count >= AFSNAMEMAX)
			वापस afs_protocol_error(call, afs_eproto_volname_len);
		size = (call->count + 3) & ~3; /* It's padded */
		afs_extract_to_buf(call, size);
		call->unmarshall++;
		fallthrough;

		/* extract the volume name */
	हाल 3:
		_debug("extract volname");
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		p = call->buffer;
		p[call->count] = 0;
		_debug("volname '%s'", p);
		afs_extract_to_पंचांगp(call);
		call->unmarshall++;
		fallthrough;

		/* extract the offline message length */
	हाल 4:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		call->count = ntohl(call->पंचांगp);
		_debug("offline msg length: %u", call->count);
		अगर (call->count >= AFSNAMEMAX)
			वापस afs_protocol_error(call, afs_eproto_offline_msg_len);
		size = (call->count + 3) & ~3; /* It's padded */
		afs_extract_to_buf(call, size);
		call->unmarshall++;
		fallthrough;

		/* extract the offline message */
	हाल 5:
		_debug("extract offline");
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		p = call->buffer;
		p[call->count] = 0;
		_debug("offline '%s'", p);

		afs_extract_to_पंचांगp(call);
		call->unmarshall++;
		fallthrough;

		/* extract the message of the day length */
	हाल 6:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		call->count = ntohl(call->पंचांगp);
		_debug("motd length: %u", call->count);
		अगर (call->count >= AFSNAMEMAX)
			वापस afs_protocol_error(call, afs_eproto_motd_len);
		size = (call->count + 3) & ~3; /* It's padded */
		afs_extract_to_buf(call, size);
		call->unmarshall++;
		fallthrough;

		/* extract the message of the day */
	हाल 7:
		_debug("extract motd");
		ret = afs_extract_data(call, false);
		अगर (ret < 0)
			वापस ret;

		p = call->buffer;
		p[call->count] = 0;
		_debug("motd '%s'", p);

		call->unmarshall++;
		fallthrough;

	हाल 8:
		अवरोध;
	पूर्ण

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * YFS.GetVolumeStatus operation type
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSGetVolumeStatus = अणु
	.name		= "YFS.GetVolumeStatus",
	.op		= yfs_FS_GetVolumeStatus,
	.deliver	= yfs_deliver_fs_get_volume_status,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * fetch the status of a volume
 */
व्योम yfs_fs_get_volume_status(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSGetVolumeStatus,
				   माप(__be32) * 2 +
				   माप(काष्ठा yfs_xdr_u64),
				   max_t(माप_प्रकार,
					 माप(काष्ठा yfs_xdr_YFSFetchVolumeStatus) +
					 माप(__be32),
					 AFSOPAQUEMAX + 1));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSGETVOLUMESTATUS);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_u64(bp, vp->fid.vid);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * YFS.SetLock operation type
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSSetLock = अणु
	.name		= "YFS.SetLock",
	.op		= yfs_FS_SetLock,
	.deliver	= yfs_deliver_status_and_volsync,
	.करोne		= afs_lock_op_करोne,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * YFS.ExtendLock operation type
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSExtendLock = अणु
	.name		= "YFS.ExtendLock",
	.op		= yfs_FS_ExtendLock,
	.deliver	= yfs_deliver_status_and_volsync,
	.करोne		= afs_lock_op_करोne,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * YFS.ReleaseLock operation type
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSReleaseLock = अणु
	.name		= "YFS.ReleaseLock",
	.op		= yfs_FS_ReleaseLock,
	.deliver	= yfs_deliver_status_and_volsync,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Set a lock on a file
 */
व्योम yfs_fs_set_lock(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSSetLock,
				   माप(__be32) * 2 +
				   माप(काष्ठा yfs_xdr_YFSFid) +
				   माप(__be32),
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSSETLOCK);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &vp->fid);
	bp = xdr_encode_u32(bp, op->lock.type);
	yfs_check_req(call, bp);

	trace_afs_make_fs_calli(call, &vp->fid, op->lock.type);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * extend a lock on a file
 */
व्योम yfs_fs_extend_lock(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSExtendLock,
				   माप(__be32) * 2 +
				   माप(काष्ठा yfs_xdr_YFSFid),
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSEXTENDLOCK);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &vp->fid);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * release a lock on a file
 */
व्योम yfs_fs_release_lock(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSReleaseLock,
				   माप(__be32) * 2 +
				   माप(काष्ठा yfs_xdr_YFSFid),
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSRELEASELOCK);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &vp->fid);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * Deliver a reply to YFS.FetchStatus
 */
अटल पूर्णांक yfs_deliver_fs_fetch_status(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode_param *vp = &op->file[op->fetch_status.which];
	स्थिर __be32 *bp;
	पूर्णांक ret;

	ret = afs_transfer_reply(call);
	अगर (ret < 0)
		वापस ret;

	/* unmarshall the reply once we've received all of it */
	bp = call->buffer;
	xdr_decode_YFSFetchStatus(&bp, call, &vp->scb);
	xdr_decode_YFSCallBack(&bp, call, &vp->scb);
	xdr_decode_YFSVolSync(&bp, &op->volsync);

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * YFS.FetchStatus operation type
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSFetchStatus = अणु
	.name		= "YFS.FetchStatus",
	.op		= yfs_FS_FetchStatus,
	.deliver	= yfs_deliver_fs_fetch_status,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Fetch the status inक्रमmation क्रम a fid without needing a vnode handle.
 */
व्योम yfs_fs_fetch_status(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[op->fetch_status.which];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter(",%x,{%llx:%llu},,",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode);

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSFetchStatus,
				   माप(__be32) * 2 +
				   माप(काष्ठा yfs_xdr_YFSFid),
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSCallBack) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSFETCHSTATUS);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &vp->fid);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * Deliver reply data to an YFS.InlineBulkStatus call
 */
अटल पूर्णांक yfs_deliver_fs_अंतरभूत_bulk_status(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_status_cb *scb;
	स्थिर __be32 *bp;
	u32 पंचांगp;
	पूर्णांक ret;

	_enter("{%u}", call->unmarshall);

	चयन (call->unmarshall) अणु
	हाल 0:
		afs_extract_to_पंचांगp(call);
		call->unmarshall++;
		fallthrough;

		/* Extract the file status count and array in two steps */
	हाल 1:
		_debug("extract status count");
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		पंचांगp = ntohl(call->पंचांगp);
		_debug("status count: %u/%u", पंचांगp, op->nr_files);
		अगर (पंचांगp != op->nr_files)
			वापस afs_protocol_error(call, afs_eproto_ibulkst_count);

		call->count = 0;
		call->unmarshall++;
	more_counts:
		afs_extract_to_buf(call, माप(काष्ठा yfs_xdr_YFSFetchStatus));
		fallthrough;

	हाल 2:
		_debug("extract status array %u", call->count);
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		चयन (call->count) अणु
		हाल 0:
			scb = &op->file[0].scb;
			अवरोध;
		हाल 1:
			scb = &op->file[1].scb;
			अवरोध;
		शेष:
			scb = &op->more_files[call->count - 2].scb;
			अवरोध;
		पूर्ण

		bp = call->buffer;
		xdr_decode_YFSFetchStatus(&bp, call, scb);

		call->count++;
		अगर (call->count < op->nr_files)
			जाओ more_counts;

		call->count = 0;
		call->unmarshall++;
		afs_extract_to_पंचांगp(call);
		fallthrough;

		/* Extract the callback count and array in two steps */
	हाल 3:
		_debug("extract CB count");
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		पंचांगp = ntohl(call->पंचांगp);
		_debug("CB count: %u", पंचांगp);
		अगर (पंचांगp != op->nr_files)
			वापस afs_protocol_error(call, afs_eproto_ibulkst_cb_count);
		call->count = 0;
		call->unmarshall++;
	more_cbs:
		afs_extract_to_buf(call, माप(काष्ठा yfs_xdr_YFSCallBack));
		fallthrough;

	हाल 4:
		_debug("extract CB array");
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		_debug("unmarshall CB array");
		चयन (call->count) अणु
		हाल 0:
			scb = &op->file[0].scb;
			अवरोध;
		हाल 1:
			scb = &op->file[1].scb;
			अवरोध;
		शेष:
			scb = &op->more_files[call->count - 2].scb;
			अवरोध;
		पूर्ण

		bp = call->buffer;
		xdr_decode_YFSCallBack(&bp, call, scb);
		call->count++;
		अगर (call->count < op->nr_files)
			जाओ more_cbs;

		afs_extract_to_buf(call, माप(काष्ठा yfs_xdr_YFSVolSync));
		call->unmarshall++;
		fallthrough;

	हाल 5:
		ret = afs_extract_data(call, false);
		अगर (ret < 0)
			वापस ret;

		bp = call->buffer;
		xdr_decode_YFSVolSync(&bp, &op->volsync);

		call->unmarshall++;
		fallthrough;

	हाल 6:
		अवरोध;
	पूर्ण

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * FS.InlineBulkStatus operation type
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSInlineBulkStatus = अणु
	.name		= "YFS.InlineBulkStatus",
	.op		= yfs_FS_InlineBulkStatus,
	.deliver	= yfs_deliver_fs_अंतरभूत_bulk_status,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Fetch the status inक्रमmation क्रम up to 1024 files
 */
व्योम yfs_fs_अंतरभूत_bulk_status(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_vnode_param *vp = &op->file[1];
	काष्ठा afs_call *call;
	__be32 *bp;
	पूर्णांक i;

	_enter(",%x,{%llx:%llu},%u",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode, op->nr_files);

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSInlineBulkStatus,
				   माप(__be32) +
				   माप(__be32) +
				   माप(__be32) +
				   माप(काष्ठा yfs_xdr_YFSFid) * op->nr_files,
				   माप(काष्ठा yfs_xdr_YFSFetchStatus));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSINLINEBULKSTATUS);
	bp = xdr_encode_u32(bp, 0); /* RPCFlags */
	bp = xdr_encode_u32(bp, op->nr_files);
	bp = xdr_encode_YFSFid(bp, &dvp->fid);
	bp = xdr_encode_YFSFid(bp, &vp->fid);
	क्रम (i = 0; i < op->nr_files - 2; i++)
		bp = xdr_encode_YFSFid(bp, &op->more_files[i].fid);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * Deliver reply data to an YFS.FetchOpaqueACL.
 */
अटल पूर्णांक yfs_deliver_fs_fetch_opaque_acl(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा yfs_acl *yacl = op->yacl;
	काष्ठा afs_acl *acl;
	स्थिर __be32 *bp;
	अचिन्हित पूर्णांक size;
	पूर्णांक ret;

	_enter("{%u}", call->unmarshall);

	चयन (call->unmarshall) अणु
	हाल 0:
		afs_extract_to_पंचांगp(call);
		call->unmarshall++;
		fallthrough;

		/* Extract the file ACL length */
	हाल 1:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		size = call->count2 = ntohl(call->पंचांगp);
		size = round_up(size, 4);

		अगर (yacl->flags & YFS_ACL_WANT_ACL) अणु
			acl = kदो_स्मृति(काष्ठा_size(acl, data, size), GFP_KERNEL);
			अगर (!acl)
				वापस -ENOMEM;
			yacl->acl = acl;
			acl->size = call->count2;
			afs_extract_begin(call, acl->data, size);
		पूर्ण अन्यथा अणु
			afs_extract_discard(call, size);
		पूर्ण
		call->unmarshall++;
		fallthrough;

		/* Extract the file ACL */
	हाल 2:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		afs_extract_to_पंचांगp(call);
		call->unmarshall++;
		fallthrough;

		/* Extract the volume ACL length */
	हाल 3:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		size = call->count2 = ntohl(call->पंचांगp);
		size = round_up(size, 4);

		अगर (yacl->flags & YFS_ACL_WANT_VOL_ACL) अणु
			acl = kदो_स्मृति(काष्ठा_size(acl, data, size), GFP_KERNEL);
			अगर (!acl)
				वापस -ENOMEM;
			yacl->vol_acl = acl;
			acl->size = call->count2;
			afs_extract_begin(call, acl->data, size);
		पूर्ण अन्यथा अणु
			afs_extract_discard(call, size);
		पूर्ण
		call->unmarshall++;
		fallthrough;

		/* Extract the volume ACL */
	हाल 4:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		afs_extract_to_buf(call,
				   माप(__be32) * 2 +
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
		call->unmarshall++;
		fallthrough;

		/* extract the metadata */
	हाल 5:
		ret = afs_extract_data(call, false);
		अगर (ret < 0)
			वापस ret;

		bp = call->buffer;
		yacl->inherit_flag = ntohl(*bp++);
		yacl->num_cleaned = ntohl(*bp++);
		xdr_decode_YFSFetchStatus(&bp, call, &vp->scb);
		xdr_decode_YFSVolSync(&bp, &op->volsync);

		call->unmarshall++;
		fallthrough;

	हाल 6:
		अवरोध;
	पूर्ण

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

व्योम yfs_मुक्त_opaque_acl(काष्ठा yfs_acl *yacl)
अणु
	अगर (yacl) अणु
		kमुक्त(yacl->acl);
		kमुक्त(yacl->vol_acl);
		kमुक्त(yacl);
	पूर्ण
पूर्ण

/*
 * YFS.FetchOpaqueACL operation type
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSFetchOpaqueACL = अणु
	.name		= "YFS.FetchOpaqueACL",
	.op		= yfs_FS_FetchOpaqueACL,
	.deliver	= yfs_deliver_fs_fetch_opaque_acl,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Fetch the YFS advanced ACLs क्रम a file.
 */
व्योम yfs_fs_fetch_opaque_acl(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter(",%x,{%llx:%llu},,",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode);

	call = afs_alloc_flat_call(op->net, &yfs_RXYFSFetchOpaqueACL,
				   माप(__be32) * 2 +
				   माप(काष्ठा yfs_xdr_YFSFid),
				   माप(__be32) * 2 +
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSFETCHOPAQUEACL);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &vp->fid);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_KERNEL);
पूर्ण

/*
 * YFS.StoreOpaqueACL2 operation type
 */
अटल स्थिर काष्ठा afs_call_type yfs_RXYFSStoreOpaqueACL2 = अणु
	.name		= "YFS.StoreOpaqueACL2",
	.op		= yfs_FS_StoreOpaqueACL2,
	.deliver	= yfs_deliver_status_and_volsync,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Fetch the YFS ACL क्रम a file.
 */
व्योम yfs_fs_store_opaque_acl2(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	काष्ठा afs_acl *acl = op->acl;
	माप_प्रकार size;
	__be32 *bp;

	_enter(",%x,{%llx:%llu},,",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode);

	size = round_up(acl->size, 4);
	call = afs_alloc_flat_call(op->net, &yfs_RXYFSStoreOpaqueACL2,
				   माप(__be32) * 2 +
				   माप(काष्ठा yfs_xdr_YFSFid) +
				   माप(__be32) + size,
				   माप(काष्ठा yfs_xdr_YFSFetchStatus) +
				   माप(काष्ठा yfs_xdr_YFSVolSync));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp = xdr_encode_u32(bp, YFSSTOREOPAQUEACL2);
	bp = xdr_encode_u32(bp, 0); /* RPC flags */
	bp = xdr_encode_YFSFid(bp, &vp->fid);
	bp = xdr_encode_u32(bp, acl->size);
	स_नकल(bp, acl->data, acl->size);
	अगर (acl->size != size)
		स_रखो((व्योम *)bp + acl->size, 0, size - acl->size);
	bp += size / माप(__be32);
	yfs_check_req(call, bp);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_KERNEL);
पूर्ण
