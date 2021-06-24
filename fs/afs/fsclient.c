<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* AFS File Server client stubs
 *
 * Copyright (C) 2002, 2007 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched.h>
#समावेश <linux/circ_buf.h>
#समावेश <linux/iversion.h>
#समावेश <linux/netfs.h>
#समावेश "internal.h"
#समावेश "afs_fs.h"
#समावेश "xdr_fs.h"

/*
 * decode an AFSFid block
 */
अटल व्योम xdr_decode_AFSFid(स्थिर __be32 **_bp, काष्ठा afs_fid *fid)
अणु
	स्थिर __be32 *bp = *_bp;

	fid->vid		= ntohl(*bp++);
	fid->vnode		= ntohl(*bp++);
	fid->unique		= ntohl(*bp++);
	*_bp = bp;
पूर्ण

/*
 * Dump a bad file status record.
 */
अटल व्योम xdr_dump_bad(स्थिर __be32 *bp)
अणु
	__be32 x[4];
	पूर्णांक i;

	pr_notice("AFS XDR: Bad status record\n");
	क्रम (i = 0; i < 5 * 4 * 4; i += 16) अणु
		स_नकल(x, bp, 16);
		bp += 4;
		pr_notice("%03x: %08x %08x %08x %08x\n",
			  i, ntohl(x[0]), ntohl(x[1]), ntohl(x[2]), ntohl(x[3]));
	पूर्ण

	स_नकल(x, bp, 4);
	pr_notice("0x50: %08x\n", ntohl(x[0]));
पूर्ण

/*
 * decode an AFSFetchStatus block
 */
अटल व्योम xdr_decode_AFSFetchStatus(स्थिर __be32 **_bp,
				      काष्ठा afs_call *call,
				      काष्ठा afs_status_cb *scb)
अणु
	स्थिर काष्ठा afs_xdr_AFSFetchStatus *xdr = (स्थिर व्योम *)*_bp;
	काष्ठा afs_file_status *status = &scb->status;
	bool अंतरभूत_error = (call->operation_ID == afs_FS_InlineBulkStatus);
	u64 data_version, size;
	u32 type, पात_code;

	पात_code = ntohl(xdr->पात_code);

	अगर (xdr->अगर_version != htonl(AFS_FSTATUS_VERSION)) अणु
		अगर (xdr->अगर_version == htonl(0) &&
		    पात_code != 0 &&
		    अंतरभूत_error) अणु
			/* The OpenAFS fileserver has a bug in FS.InlineBulkStatus
			 * whereby it करोesn't set the पूर्णांकerface version in the error
			 * हाल.
			 */
			status->पात_code = पात_code;
			scb->have_error = true;
			जाओ advance;
		पूर्ण

		pr_warn("Unknown AFSFetchStatus version %u\n", ntohl(xdr->अगर_version));
		जाओ bad;
	पूर्ण

	अगर (पात_code != 0 && अंतरभूत_error) अणु
		status->पात_code = पात_code;
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
	status->author		= ntohl(xdr->author);
	status->owner		= ntohl(xdr->owner);
	status->caller_access	= ntohl(xdr->caller_access); /* Ticket dependent */
	status->anon_access	= ntohl(xdr->anon_access);
	status->mode		= ntohl(xdr->mode) & S_IALLUGO;
	status->group		= ntohl(xdr->group);
	status->lock_count	= ntohl(xdr->lock_count);

	status->mसमय_client.tv_sec = ntohl(xdr->mसमय_client);
	status->mसमय_client.tv_nsec = 0;
	status->mसमय_server.tv_sec = ntohl(xdr->mसमय_server);
	status->mसमय_server.tv_nsec = 0;

	size  = (u64)ntohl(xdr->size_lo);
	size |= (u64)ntohl(xdr->size_hi) << 32;
	status->size = size;

	data_version  = (u64)ntohl(xdr->data_version_lo);
	data_version |= (u64)ntohl(xdr->data_version_hi) << 32;
	status->data_version = data_version;
	scb->have_status = true;
advance:
	*_bp = (स्थिर व्योम *)*_bp + माप(*xdr);
	वापस;

bad:
	xdr_dump_bad(*_bp);
	afs_protocol_error(call, afs_eproto_bad_status);
	जाओ advance;
पूर्ण

अटल समय64_t xdr_decode_expiry(काष्ठा afs_call *call, u32 expiry)
अणु
	वापस kसमय_भागns(call->reply_समय, NSEC_PER_SEC) + expiry;
पूर्ण

अटल व्योम xdr_decode_AFSCallBack(स्थिर __be32 **_bp,
				   काष्ठा afs_call *call,
				   काष्ठा afs_status_cb *scb)
अणु
	काष्ठा afs_callback *cb = &scb->callback;
	स्थिर __be32 *bp = *_bp;

	bp++; /* version */
	cb->expires_at	= xdr_decode_expiry(call, ntohl(*bp++));
	bp++; /* type */
	scb->have_cb	= true;
	*_bp = bp;
पूर्ण

/*
 * decode an AFSVolSync block
 */
अटल व्योम xdr_decode_AFSVolSync(स्थिर __be32 **_bp,
				  काष्ठा afs_volsync *volsync)
अणु
	स्थिर __be32 *bp = *_bp;
	u32 creation;

	creation = ntohl(*bp++);
	bp++; /* spare2 */
	bp++; /* spare3 */
	bp++; /* spare4 */
	bp++; /* spare5 */
	bp++; /* spare6 */
	*_bp = bp;

	अगर (volsync)
		volsync->creation = creation;
पूर्ण

/*
 * encode the requested attributes पूर्णांकo an AFSStoreStatus block
 */
अटल व्योम xdr_encode_AFS_StoreStatus(__be32 **_bp, काष्ठा iattr *attr)
अणु
	__be32 *bp = *_bp;
	u32 mask = 0, mसमय = 0, owner = 0, group = 0, mode = 0;

	mask = 0;
	अगर (attr->ia_valid & ATTR_MTIME) अणु
		mask |= AFS_SET_MTIME;
		mसमय = attr->ia_mसमय.tv_sec;
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

	*bp++ = htonl(mask);
	*bp++ = htonl(mसमय);
	*bp++ = htonl(owner);
	*bp++ = htonl(group);
	*bp++ = htonl(mode);
	*bp++ = 0;		/* segment size */
	*_bp = bp;
पूर्ण

/*
 * decode an AFSFetchVolumeStatus block
 */
अटल व्योम xdr_decode_AFSFetchVolumeStatus(स्थिर __be32 **_bp,
					    काष्ठा afs_volume_status *vs)
अणु
	स्थिर __be32 *bp = *_bp;

	vs->vid			= ntohl(*bp++);
	vs->parent_id		= ntohl(*bp++);
	vs->online		= ntohl(*bp++);
	vs->in_service		= ntohl(*bp++);
	vs->blessed		= ntohl(*bp++);
	vs->needs_salvage	= ntohl(*bp++);
	vs->type		= ntohl(*bp++);
	vs->min_quota		= ntohl(*bp++);
	vs->max_quota		= ntohl(*bp++);
	vs->blocks_in_use	= ntohl(*bp++);
	vs->part_blocks_avail	= ntohl(*bp++);
	vs->part_max_blocks	= ntohl(*bp++);
	vs->vol_copy_date	= 0;
	vs->vol_backup_date	= 0;
	*_bp = bp;
पूर्ण

/*
 * deliver reply data to an FS.FetchStatus
 */
अटल पूर्णांक afs_deliver_fs_fetch_status(काष्ठा afs_call *call)
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
	xdr_decode_AFSFetchStatus(&bp, call, &vp->scb);
	xdr_decode_AFSCallBack(&bp, call, &vp->scb);
	xdr_decode_AFSVolSync(&bp, &op->volsync);

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * FS.FetchStatus operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSFetchStatus = अणु
	.name		= "FS.FetchStatus",
	.op		= afs_FS_FetchStatus,
	.deliver	= afs_deliver_fs_fetch_status,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * fetch the status inक्रमmation क्रम a file
 */
व्योम afs_fs_fetch_status(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[op->fetch_status.which];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter(",%x,{%llx:%llu},,",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode);

	call = afs_alloc_flat_call(op->net, &afs_RXFSFetchStatus,
				   16, (21 + 3 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp[0] = htonl(FSFETCHSTATUS);
	bp[1] = htonl(vp->fid.vid);
	bp[2] = htonl(vp->fid.vnode);
	bp[3] = htonl(vp->fid.unique);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * deliver reply data to an FS.FetchData
 */
अटल पूर्णांक afs_deliver_fs_fetch_data(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_पढ़ो *req = op->fetch.req;
	स्थिर __be32 *bp;
	पूर्णांक ret;

	_enter("{%u,%zu,%zu/%llu}",
	       call->unmarshall, call->iov_len, iov_iter_count(call->iter),
	       req->actual_len);

	चयन (call->unmarshall) अणु
	हाल 0:
		req->actual_len = 0;
		call->unmarshall++;
		अगर (call->operation_ID == FSFETCHDATA64) अणु
			afs_extract_to_पंचांगp64(call);
		पूर्ण अन्यथा अणु
			call->पंचांगp_u = htonl(0);
			afs_extract_to_पंचांगp(call);
		पूर्ण
		fallthrough;

		/* Extract the वापसed data length पूर्णांकo
		 * ->actual_len.  This may indicate more or less data than was
		 * requested will be वापसed.
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
		afs_extract_to_buf(call, (21 + 3 + 6) * 4);
		fallthrough;

		/* extract the metadata */
	हाल 4:
		ret = afs_extract_data(call, false);
		अगर (ret < 0)
			वापस ret;

		bp = call->buffer;
		xdr_decode_AFSFetchStatus(&bp, call, &vp->scb);
		xdr_decode_AFSCallBack(&bp, call, &vp->scb);
		xdr_decode_AFSVolSync(&bp, &op->volsync);

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
 * FS.FetchData operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSFetchData = अणु
	.name		= "FS.FetchData",
	.op		= afs_FS_FetchData,
	.deliver	= afs_deliver_fs_fetch_data,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

अटल स्थिर काष्ठा afs_call_type afs_RXFSFetchData64 = अणु
	.name		= "FS.FetchData64",
	.op		= afs_FS_FetchData64,
	.deliver	= afs_deliver_fs_fetch_data,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * fetch data from a very large file
 */
अटल व्योम afs_fs_fetch_data64(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_पढ़ो *req = op->fetch.req;
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(op->net, &afs_RXFSFetchData64, 32, (21 + 3 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp[0] = htonl(FSFETCHDATA64);
	bp[1] = htonl(vp->fid.vid);
	bp[2] = htonl(vp->fid.vnode);
	bp[3] = htonl(vp->fid.unique);
	bp[4] = htonl(upper_32_bits(req->pos));
	bp[5] = htonl(lower_32_bits(req->pos));
	bp[6] = 0;
	bp[7] = htonl(lower_32_bits(req->len));

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * fetch data from a file
 */
व्योम afs_fs_fetch_data(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	काष्ठा afs_पढ़ो *req = op->fetch.req;
	__be32 *bp;

	अगर (upper_32_bits(req->pos) ||
	    upper_32_bits(req->len) ||
	    upper_32_bits(req->pos + req->len))
		वापस afs_fs_fetch_data64(op);

	_enter("");

	call = afs_alloc_flat_call(op->net, &afs_RXFSFetchData, 24, (21 + 3 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	req->call_debug_id = call->debug_id;

	/* marshall the parameters */
	bp = call->request;
	bp[0] = htonl(FSFETCHDATA);
	bp[1] = htonl(vp->fid.vid);
	bp[2] = htonl(vp->fid.vnode);
	bp[3] = htonl(vp->fid.unique);
	bp[4] = htonl(lower_32_bits(req->pos));
	bp[5] = htonl(lower_32_bits(req->len));

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * deliver reply data to an FS.CreateFile or an FS.MakeDir
 */
अटल पूर्णांक afs_deliver_fs_create_vnode(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_vnode_param *vp = &op->file[1];
	स्थिर __be32 *bp;
	पूर्णांक ret;

	ret = afs_transfer_reply(call);
	अगर (ret < 0)
		वापस ret;

	/* unmarshall the reply once we've received all of it */
	bp = call->buffer;
	xdr_decode_AFSFid(&bp, &op->file[1].fid);
	xdr_decode_AFSFetchStatus(&bp, call, &vp->scb);
	xdr_decode_AFSFetchStatus(&bp, call, &dvp->scb);
	xdr_decode_AFSCallBack(&bp, call, &vp->scb);
	xdr_decode_AFSVolSync(&bp, &op->volsync);

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * FS.CreateFile and FS.MakeDir operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSCreateFile = अणु
	.name		= "FS.CreateFile",
	.op		= afs_FS_CreateFile,
	.deliver	= afs_deliver_fs_create_vnode,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Create a file.
 */
व्योम afs_fs_create_file(काष्ठा afs_operation *op)
अणु
	स्थिर काष्ठा qstr *name = &op->dentry->d_name;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_call *call;
	माप_प्रकार namesz, reqsz, padsz;
	__be32 *bp;

	_enter("");

	namesz = name->len;
	padsz = (4 - (namesz & 3)) & 3;
	reqsz = (5 * 4) + namesz + padsz + (6 * 4);

	call = afs_alloc_flat_call(op->net, &afs_RXFSCreateFile,
				   reqsz, (3 + 21 + 21 + 3 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSCREATEखाता);
	*bp++ = htonl(dvp->fid.vid);
	*bp++ = htonl(dvp->fid.vnode);
	*bp++ = htonl(dvp->fid.unique);
	*bp++ = htonl(namesz);
	स_नकल(bp, name->name, namesz);
	bp = (व्योम *) bp + namesz;
	अगर (padsz > 0) अणु
		स_रखो(bp, 0, padsz);
		bp = (व्योम *) bp + padsz;
	पूर्ण
	*bp++ = htonl(AFS_SET_MODE | AFS_SET_MTIME);
	*bp++ = htonl(op->mसमय.tv_sec); /* mसमय */
	*bp++ = 0; /* owner */
	*bp++ = 0; /* group */
	*bp++ = htonl(op->create.mode & S_IALLUGO); /* unix mode */
	*bp++ = 0; /* segment size */

	trace_afs_make_fs_call1(call, &dvp->fid, name);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

अटल स्थिर काष्ठा afs_call_type afs_RXFSMakeDir = अणु
	.name		= "FS.MakeDir",
	.op		= afs_FS_MakeDir,
	.deliver	= afs_deliver_fs_create_vnode,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Create a new directory
 */
व्योम afs_fs_make_dir(काष्ठा afs_operation *op)
अणु
	स्थिर काष्ठा qstr *name = &op->dentry->d_name;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_call *call;
	माप_प्रकार namesz, reqsz, padsz;
	__be32 *bp;

	_enter("");

	namesz = name->len;
	padsz = (4 - (namesz & 3)) & 3;
	reqsz = (5 * 4) + namesz + padsz + (6 * 4);

	call = afs_alloc_flat_call(op->net, &afs_RXFSMakeDir,
				   reqsz, (3 + 21 + 21 + 3 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSMAKEसूची);
	*bp++ = htonl(dvp->fid.vid);
	*bp++ = htonl(dvp->fid.vnode);
	*bp++ = htonl(dvp->fid.unique);
	*bp++ = htonl(namesz);
	स_नकल(bp, name->name, namesz);
	bp = (व्योम *) bp + namesz;
	अगर (padsz > 0) अणु
		स_रखो(bp, 0, padsz);
		bp = (व्योम *) bp + padsz;
	पूर्ण
	*bp++ = htonl(AFS_SET_MODE | AFS_SET_MTIME);
	*bp++ = htonl(op->mसमय.tv_sec); /* mसमय */
	*bp++ = 0; /* owner */
	*bp++ = 0; /* group */
	*bp++ = htonl(op->create.mode & S_IALLUGO); /* unix mode */
	*bp++ = 0; /* segment size */

	trace_afs_make_fs_call1(call, &dvp->fid, name);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * Deliver reply data to any operation that वापसs status and volume sync.
 */
अटल पूर्णांक afs_deliver_fs_file_status_and_vol(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode_param *vp = &op->file[0];
	स्थिर __be32 *bp;
	पूर्णांक ret;

	ret = afs_transfer_reply(call);
	अगर (ret < 0)
		वापस ret;

	/* unmarshall the reply once we've received all of it */
	bp = call->buffer;
	xdr_decode_AFSFetchStatus(&bp, call, &vp->scb);
	xdr_decode_AFSVolSync(&bp, &op->volsync);

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * FS.RemoveFile operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSRemoveFile = अणु
	.name		= "FS.RemoveFile",
	.op		= afs_FS_RemoveFile,
	.deliver	= afs_deliver_fs_file_status_and_vol,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Remove a file.
 */
व्योम afs_fs_हटाओ_file(काष्ठा afs_operation *op)
अणु
	स्थिर काष्ठा qstr *name = &op->dentry->d_name;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_call *call;
	माप_प्रकार namesz, reqsz, padsz;
	__be32 *bp;

	_enter("");

	namesz = name->len;
	padsz = (4 - (namesz & 3)) & 3;
	reqsz = (5 * 4) + namesz + padsz;

	call = afs_alloc_flat_call(op->net, &afs_RXFSRemoveFile,
				   reqsz, (21 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSREMOVEखाता);
	*bp++ = htonl(dvp->fid.vid);
	*bp++ = htonl(dvp->fid.vnode);
	*bp++ = htonl(dvp->fid.unique);
	*bp++ = htonl(namesz);
	स_नकल(bp, name->name, namesz);
	bp = (व्योम *) bp + namesz;
	अगर (padsz > 0) अणु
		स_रखो(bp, 0, padsz);
		bp = (व्योम *) bp + padsz;
	पूर्ण

	trace_afs_make_fs_call1(call, &dvp->fid, name);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

अटल स्थिर काष्ठा afs_call_type afs_RXFSRemoveDir = अणु
	.name		= "FS.RemoveDir",
	.op		= afs_FS_RemoveDir,
	.deliver	= afs_deliver_fs_file_status_and_vol,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Remove a directory.
 */
व्योम afs_fs_हटाओ_dir(काष्ठा afs_operation *op)
अणु
	स्थिर काष्ठा qstr *name = &op->dentry->d_name;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_call *call;
	माप_प्रकार namesz, reqsz, padsz;
	__be32 *bp;

	_enter("");

	namesz = name->len;
	padsz = (4 - (namesz & 3)) & 3;
	reqsz = (5 * 4) + namesz + padsz;

	call = afs_alloc_flat_call(op->net, &afs_RXFSRemoveDir,
				   reqsz, (21 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSREMOVEसूची);
	*bp++ = htonl(dvp->fid.vid);
	*bp++ = htonl(dvp->fid.vnode);
	*bp++ = htonl(dvp->fid.unique);
	*bp++ = htonl(namesz);
	स_नकल(bp, name->name, namesz);
	bp = (व्योम *) bp + namesz;
	अगर (padsz > 0) अणु
		स_रखो(bp, 0, padsz);
		bp = (व्योम *) bp + padsz;
	पूर्ण

	trace_afs_make_fs_call1(call, &dvp->fid, name);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * deliver reply data to an FS.Link
 */
अटल पूर्णांक afs_deliver_fs_link(काष्ठा afs_call *call)
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
	xdr_decode_AFSFetchStatus(&bp, call, &vp->scb);
	xdr_decode_AFSFetchStatus(&bp, call, &dvp->scb);
	xdr_decode_AFSVolSync(&bp, &op->volsync);

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * FS.Link operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSLink = अणु
	.name		= "FS.Link",
	.op		= afs_FS_Link,
	.deliver	= afs_deliver_fs_link,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * make a hard link
 */
व्योम afs_fs_link(काष्ठा afs_operation *op)
अणु
	स्थिर काष्ठा qstr *name = &op->dentry->d_name;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_vnode_param *vp = &op->file[1];
	काष्ठा afs_call *call;
	माप_प्रकार namesz, reqsz, padsz;
	__be32 *bp;

	_enter("");

	namesz = name->len;
	padsz = (4 - (namesz & 3)) & 3;
	reqsz = (5 * 4) + namesz + padsz + (3 * 4);

	call = afs_alloc_flat_call(op->net, &afs_RXFSLink, reqsz, (21 + 21 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSLINK);
	*bp++ = htonl(dvp->fid.vid);
	*bp++ = htonl(dvp->fid.vnode);
	*bp++ = htonl(dvp->fid.unique);
	*bp++ = htonl(namesz);
	स_नकल(bp, name->name, namesz);
	bp = (व्योम *) bp + namesz;
	अगर (padsz > 0) अणु
		स_रखो(bp, 0, padsz);
		bp = (व्योम *) bp + padsz;
	पूर्ण
	*bp++ = htonl(vp->fid.vid);
	*bp++ = htonl(vp->fid.vnode);
	*bp++ = htonl(vp->fid.unique);

	trace_afs_make_fs_call1(call, &vp->fid, name);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * deliver reply data to an FS.Symlink
 */
अटल पूर्णांक afs_deliver_fs_symlink(काष्ठा afs_call *call)
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
	xdr_decode_AFSFid(&bp, &vp->fid);
	xdr_decode_AFSFetchStatus(&bp, call, &vp->scb);
	xdr_decode_AFSFetchStatus(&bp, call, &dvp->scb);
	xdr_decode_AFSVolSync(&bp, &op->volsync);

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * FS.Symlink operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSSymlink = अणु
	.name		= "FS.Symlink",
	.op		= afs_FS_Symlink,
	.deliver	= afs_deliver_fs_symlink,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * create a symbolic link
 */
व्योम afs_fs_symlink(काष्ठा afs_operation *op)
अणु
	स्थिर काष्ठा qstr *name = &op->dentry->d_name;
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_call *call;
	माप_प्रकार namesz, reqsz, padsz, c_namesz, c_padsz;
	__be32 *bp;

	_enter("");

	namesz = name->len;
	padsz = (4 - (namesz & 3)) & 3;

	c_namesz = म_माप(op->create.symlink);
	c_padsz = (4 - (c_namesz & 3)) & 3;

	reqsz = (6 * 4) + namesz + padsz + c_namesz + c_padsz + (6 * 4);

	call = afs_alloc_flat_call(op->net, &afs_RXFSSymlink, reqsz,
				   (3 + 21 + 21 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSSYMLINK);
	*bp++ = htonl(dvp->fid.vid);
	*bp++ = htonl(dvp->fid.vnode);
	*bp++ = htonl(dvp->fid.unique);
	*bp++ = htonl(namesz);
	स_नकल(bp, name->name, namesz);
	bp = (व्योम *) bp + namesz;
	अगर (padsz > 0) अणु
		स_रखो(bp, 0, padsz);
		bp = (व्योम *) bp + padsz;
	पूर्ण
	*bp++ = htonl(c_namesz);
	स_नकल(bp, op->create.symlink, c_namesz);
	bp = (व्योम *) bp + c_namesz;
	अगर (c_padsz > 0) अणु
		स_रखो(bp, 0, c_padsz);
		bp = (व्योम *) bp + c_padsz;
	पूर्ण
	*bp++ = htonl(AFS_SET_MODE | AFS_SET_MTIME);
	*bp++ = htonl(op->mसमय.tv_sec); /* mसमय */
	*bp++ = 0; /* owner */
	*bp++ = 0; /* group */
	*bp++ = htonl(S_IRWXUGO); /* unix mode */
	*bp++ = 0; /* segment size */

	trace_afs_make_fs_call1(call, &dvp->fid, name);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * deliver reply data to an FS.Rename
 */
अटल पूर्णांक afs_deliver_fs_नाम(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode_param *orig_dvp = &op->file[0];
	काष्ठा afs_vnode_param *new_dvp = &op->file[1];
	स्थिर __be32 *bp;
	पूर्णांक ret;

	ret = afs_transfer_reply(call);
	अगर (ret < 0)
		वापस ret;

	bp = call->buffer;
	/* If the two dirs are the same, we have two copies of the same status
	 * report, so we just decode it twice.
	 */
	xdr_decode_AFSFetchStatus(&bp, call, &orig_dvp->scb);
	xdr_decode_AFSFetchStatus(&bp, call, &new_dvp->scb);
	xdr_decode_AFSVolSync(&bp, &op->volsync);

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * FS.Rename operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSRename = अणु
	.name		= "FS.Rename",
	.op		= afs_FS_Rename,
	.deliver	= afs_deliver_fs_नाम,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Rename/move a file or directory.
 */
व्योम afs_fs_नाम(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *orig_dvp = &op->file[0];
	काष्ठा afs_vnode_param *new_dvp = &op->file[1];
	स्थिर काष्ठा qstr *orig_name = &op->dentry->d_name;
	स्थिर काष्ठा qstr *new_name = &op->dentry_2->d_name;
	काष्ठा afs_call *call;
	माप_प्रकार reqsz, o_namesz, o_padsz, n_namesz, n_padsz;
	__be32 *bp;

	_enter("");

	o_namesz = orig_name->len;
	o_padsz = (4 - (o_namesz & 3)) & 3;

	n_namesz = new_name->len;
	n_padsz = (4 - (n_namesz & 3)) & 3;

	reqsz = (4 * 4) +
		4 + o_namesz + o_padsz +
		(3 * 4) +
		4 + n_namesz + n_padsz;

	call = afs_alloc_flat_call(op->net, &afs_RXFSRename, reqsz, (21 + 21 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSRENAME);
	*bp++ = htonl(orig_dvp->fid.vid);
	*bp++ = htonl(orig_dvp->fid.vnode);
	*bp++ = htonl(orig_dvp->fid.unique);
	*bp++ = htonl(o_namesz);
	स_नकल(bp, orig_name->name, o_namesz);
	bp = (व्योम *) bp + o_namesz;
	अगर (o_padsz > 0) अणु
		स_रखो(bp, 0, o_padsz);
		bp = (व्योम *) bp + o_padsz;
	पूर्ण

	*bp++ = htonl(new_dvp->fid.vid);
	*bp++ = htonl(new_dvp->fid.vnode);
	*bp++ = htonl(new_dvp->fid.unique);
	*bp++ = htonl(n_namesz);
	स_नकल(bp, new_name->name, n_namesz);
	bp = (व्योम *) bp + n_namesz;
	अगर (n_padsz > 0) अणु
		स_रखो(bp, 0, n_padsz);
		bp = (व्योम *) bp + n_padsz;
	पूर्ण

	trace_afs_make_fs_call2(call, &orig_dvp->fid, orig_name, new_name);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * Deliver reply data to FS.StoreData or FS.StoreStatus
 */
अटल पूर्णांक afs_deliver_fs_store_data(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode_param *vp = &op->file[0];
	स्थिर __be32 *bp;
	पूर्णांक ret;

	_enter("");

	ret = afs_transfer_reply(call);
	अगर (ret < 0)
		वापस ret;

	/* unmarshall the reply once we've received all of it */
	bp = call->buffer;
	xdr_decode_AFSFetchStatus(&bp, call, &vp->scb);
	xdr_decode_AFSVolSync(&bp, &op->volsync);

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * FS.StoreData operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSStoreData = अणु
	.name		= "FS.StoreData",
	.op		= afs_FS_StoreData,
	.deliver	= afs_deliver_fs_store_data,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

अटल स्थिर काष्ठा afs_call_type afs_RXFSStoreData64 = अणु
	.name		= "FS.StoreData64",
	.op		= afs_FS_StoreData64,
	.deliver	= afs_deliver_fs_store_data,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * store a set of pages to a very large file
 */
अटल व्योम afs_fs_store_data64(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter(",%x,{%llx:%llu},,",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode);

	call = afs_alloc_flat_call(op->net, &afs_RXFSStoreData64,
				   (4 + 6 + 3 * 2) * 4,
				   (21 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	call->ग_लिखो_iter = op->store.ग_लिखो_iter;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSSTOREDATA64);
	*bp++ = htonl(vp->fid.vid);
	*bp++ = htonl(vp->fid.vnode);
	*bp++ = htonl(vp->fid.unique);

	*bp++ = htonl(AFS_SET_MTIME); /* mask */
	*bp++ = htonl(op->mसमय.tv_sec); /* mसमय */
	*bp++ = 0; /* owner */
	*bp++ = 0; /* group */
	*bp++ = 0; /* unix mode */
	*bp++ = 0; /* segment size */

	*bp++ = htonl(upper_32_bits(op->store.pos));
	*bp++ = htonl(lower_32_bits(op->store.pos));
	*bp++ = htonl(upper_32_bits(op->store.size));
	*bp++ = htonl(lower_32_bits(op->store.size));
	*bp++ = htonl(upper_32_bits(op->store.i_size));
	*bp++ = htonl(lower_32_bits(op->store.i_size));

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * Write data to a file on the server.
 */
व्योम afs_fs_store_data(काष्ठा afs_operation *op)
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

	अगर (upper_32_bits(op->store.pos) ||
	    upper_32_bits(op->store.size) ||
	    upper_32_bits(op->store.i_size))
		वापस afs_fs_store_data64(op);

	call = afs_alloc_flat_call(op->net, &afs_RXFSStoreData,
				   (4 + 6 + 3) * 4,
				   (21 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	call->ग_लिखो_iter = op->store.ग_लिखो_iter;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSSTOREDATA);
	*bp++ = htonl(vp->fid.vid);
	*bp++ = htonl(vp->fid.vnode);
	*bp++ = htonl(vp->fid.unique);

	*bp++ = htonl(AFS_SET_MTIME); /* mask */
	*bp++ = htonl(op->mसमय.tv_sec); /* mसमय */
	*bp++ = 0; /* owner */
	*bp++ = 0; /* group */
	*bp++ = 0; /* unix mode */
	*bp++ = 0; /* segment size */

	*bp++ = htonl(lower_32_bits(op->store.pos));
	*bp++ = htonl(lower_32_bits(op->store.size));
	*bp++ = htonl(lower_32_bits(op->store.i_size));

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * FS.StoreStatus operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSStoreStatus = अणु
	.name		= "FS.StoreStatus",
	.op		= afs_FS_StoreStatus,
	.deliver	= afs_deliver_fs_store_data,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

अटल स्थिर काष्ठा afs_call_type afs_RXFSStoreData_as_Status = अणु
	.name		= "FS.StoreData",
	.op		= afs_FS_StoreData,
	.deliver	= afs_deliver_fs_store_data,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

अटल स्थिर काष्ठा afs_call_type afs_RXFSStoreData64_as_Status = अणु
	.name		= "FS.StoreData64",
	.op		= afs_FS_StoreData64,
	.deliver	= afs_deliver_fs_store_data,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * set the attributes on a very large file, using FS.StoreData rather than
 * FS.StoreStatus so as to alter the file size also
 */
अटल व्योम afs_fs_setattr_size64(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	काष्ठा iattr *attr = op->setattr.attr;
	__be32 *bp;

	_enter(",%x,{%llx:%llu},,",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode);

	ASSERT(attr->ia_valid & ATTR_SIZE);

	call = afs_alloc_flat_call(op->net, &afs_RXFSStoreData64_as_Status,
				   (4 + 6 + 3 * 2) * 4,
				   (21 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSSTOREDATA64);
	*bp++ = htonl(vp->fid.vid);
	*bp++ = htonl(vp->fid.vnode);
	*bp++ = htonl(vp->fid.unique);

	xdr_encode_AFS_StoreStatus(&bp, attr);

	*bp++ = htonl(upper_32_bits(attr->ia_size));	/* position of start of ग_लिखो */
	*bp++ = htonl(lower_32_bits(attr->ia_size));
	*bp++ = 0;					/* size of ग_लिखो */
	*bp++ = 0;
	*bp++ = htonl(upper_32_bits(attr->ia_size));	/* new file length */
	*bp++ = htonl(lower_32_bits(attr->ia_size));

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * set the attributes on a file, using FS.StoreData rather than FS.StoreStatus
 * so as to alter the file size also
 */
अटल व्योम afs_fs_setattr_size(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	काष्ठा iattr *attr = op->setattr.attr;
	__be32 *bp;

	_enter(",%x,{%llx:%llu},,",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode);

	ASSERT(attr->ia_valid & ATTR_SIZE);
	अगर (upper_32_bits(attr->ia_size))
		वापस afs_fs_setattr_size64(op);

	call = afs_alloc_flat_call(op->net, &afs_RXFSStoreData_as_Status,
				   (4 + 6 + 3) * 4,
				   (21 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSSTOREDATA);
	*bp++ = htonl(vp->fid.vid);
	*bp++ = htonl(vp->fid.vnode);
	*bp++ = htonl(vp->fid.unique);

	xdr_encode_AFS_StoreStatus(&bp, attr);

	*bp++ = htonl(attr->ia_size);		/* position of start of ग_लिखो */
	*bp++ = 0;				/* size of ग_लिखो */
	*bp++ = htonl(attr->ia_size);		/* new file length */

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * set the attributes on a file, using FS.StoreData अगर there's a change in file
 * size, and FS.StoreStatus otherwise
 */
व्योम afs_fs_setattr(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	काष्ठा iattr *attr = op->setattr.attr;
	__be32 *bp;

	अगर (attr->ia_valid & ATTR_SIZE)
		वापस afs_fs_setattr_size(op);

	_enter(",%x,{%llx:%llu},,",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode);

	call = afs_alloc_flat_call(op->net, &afs_RXFSStoreStatus,
				   (4 + 6) * 4,
				   (21 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSSTORESTATUS);
	*bp++ = htonl(vp->fid.vid);
	*bp++ = htonl(vp->fid.vnode);
	*bp++ = htonl(vp->fid.unique);

	xdr_encode_AFS_StoreStatus(&bp, op->setattr.attr);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * deliver reply data to an FS.GetVolumeStatus
 */
अटल पूर्णांक afs_deliver_fs_get_volume_status(काष्ठा afs_call *call)
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
		afs_extract_to_buf(call, 12 * 4);
		fallthrough;

		/* extract the वापसed status record */
	हाल 1:
		_debug("extract status");
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		bp = call->buffer;
		xdr_decode_AFSFetchVolumeStatus(&bp, &op->volstatus.vs);
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
 * FS.GetVolumeStatus operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSGetVolumeStatus = अणु
	.name		= "FS.GetVolumeStatus",
	.op		= afs_FS_GetVolumeStatus,
	.deliver	= afs_deliver_fs_get_volume_status,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * fetch the status of a volume
 */
व्योम afs_fs_get_volume_status(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(op->net, &afs_RXFSGetVolumeStatus, 2 * 4,
				   max(12 * 4, AFSOPAQUEMAX + 1));
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp[0] = htonl(FSGETVOLUMESTATUS);
	bp[1] = htonl(vp->fid.vid);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * deliver reply data to an FS.SetLock, FS.ExtendLock or FS.ReleaseLock
 */
अटल पूर्णांक afs_deliver_fs_xxxx_lock(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	स्थिर __be32 *bp;
	पूर्णांक ret;

	_enter("{%u}", call->unmarshall);

	ret = afs_transfer_reply(call);
	अगर (ret < 0)
		वापस ret;

	/* unmarshall the reply once we've received all of it */
	bp = call->buffer;
	xdr_decode_AFSVolSync(&bp, &op->volsync);

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * FS.SetLock operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSSetLock = अणु
	.name		= "FS.SetLock",
	.op		= afs_FS_SetLock,
	.deliver	= afs_deliver_fs_xxxx_lock,
	.करोne		= afs_lock_op_करोne,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * FS.ExtendLock operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSExtendLock = अणु
	.name		= "FS.ExtendLock",
	.op		= afs_FS_ExtendLock,
	.deliver	= afs_deliver_fs_xxxx_lock,
	.करोne		= afs_lock_op_करोne,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * FS.ReleaseLock operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSReleaseLock = अणु
	.name		= "FS.ReleaseLock",
	.op		= afs_FS_ReleaseLock,
	.deliver	= afs_deliver_fs_xxxx_lock,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Set a lock on a file
 */
व्योम afs_fs_set_lock(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(op->net, &afs_RXFSSetLock, 5 * 4, 6 * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSSETLOCK);
	*bp++ = htonl(vp->fid.vid);
	*bp++ = htonl(vp->fid.vnode);
	*bp++ = htonl(vp->fid.unique);
	*bp++ = htonl(op->lock.type);

	trace_afs_make_fs_calli(call, &vp->fid, op->lock.type);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * extend a lock on a file
 */
व्योम afs_fs_extend_lock(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(op->net, &afs_RXFSExtendLock, 4 * 4, 6 * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSEXTENDLOCK);
	*bp++ = htonl(vp->fid.vid);
	*bp++ = htonl(vp->fid.vnode);
	*bp++ = htonl(vp->fid.unique);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * release a lock on a file
 */
व्योम afs_fs_release_lock(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(op->net, &afs_RXFSReleaseLock, 4 * 4, 6 * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSRELEASELOCK);
	*bp++ = htonl(vp->fid.vid);
	*bp++ = htonl(vp->fid.vnode);
	*bp++ = htonl(vp->fid.unique);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * Deliver reply data to an FS.GiveUpAllCallBacks operation.
 */
अटल पूर्णांक afs_deliver_fs_give_up_all_callbacks(काष्ठा afs_call *call)
अणु
	वापस afs_transfer_reply(call);
पूर्ण

/*
 * FS.GiveUpAllCallBacks operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSGiveUpAllCallBacks = अणु
	.name		= "FS.GiveUpAllCallBacks",
	.op		= afs_FS_GiveUpAllCallBacks,
	.deliver	= afs_deliver_fs_give_up_all_callbacks,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Flush all the callbacks we have on a server.
 */
पूर्णांक afs_fs_give_up_all_callbacks(काष्ठा afs_net *net,
				 काष्ठा afs_server *server,
				 काष्ठा afs_addr_cursor *ac,
				 काष्ठा key *key)
अणु
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(net, &afs_RXFSGiveUpAllCallBacks, 1 * 4, 0);
	अगर (!call)
		वापस -ENOMEM;

	call->key = key;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSGIVEUPALLCALLBACKS);

	call->server = afs_use_server(server, afs_server_trace_give_up_cb);
	afs_make_call(ac, call, GFP_NOFS);
	वापस afs_रुको_क्रम_call_to_complete(call, ac);
पूर्ण

/*
 * Deliver reply data to an FS.GetCapabilities operation.
 */
अटल पूर्णांक afs_deliver_fs_get_capabilities(काष्ठा afs_call *call)
अणु
	u32 count;
	पूर्णांक ret;

	_enter("{%u,%zu}", call->unmarshall, iov_iter_count(call->iter));

	चयन (call->unmarshall) अणु
	हाल 0:
		afs_extract_to_पंचांगp(call);
		call->unmarshall++;
		fallthrough;

		/* Extract the capabilities word count */
	हाल 1:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		count = ntohl(call->पंचांगp);

		call->count = count;
		call->count2 = count;
		afs_extract_discard(call, count * माप(__be32));
		call->unmarshall++;
		fallthrough;

		/* Extract capabilities words */
	हाल 2:
		ret = afs_extract_data(call, false);
		अगर (ret < 0)
			वापस ret;

		/* TODO: Examine capabilities */

		call->unmarshall++;
		अवरोध;
	पूर्ण

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * FS.GetCapabilities operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSGetCapabilities = अणु
	.name		= "FS.GetCapabilities",
	.op		= afs_FS_GetCapabilities,
	.deliver	= afs_deliver_fs_get_capabilities,
	.करोne		= afs_fileserver_probe_result,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Probe a fileserver क्रम the capabilities that it supports.  This RPC can
 * reply with up to 196 words.  The operation is asynchronous and अगर we managed
 * to allocate a call, true is वापसed the result is delivered through the
 * ->करोne() - otherwise we वापस false to indicate we didn't even try.
 */
bool afs_fs_get_capabilities(काष्ठा afs_net *net, काष्ठा afs_server *server,
			     काष्ठा afs_addr_cursor *ac, काष्ठा key *key)
अणु
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter("");

	call = afs_alloc_flat_call(net, &afs_RXFSGetCapabilities, 1 * 4, 16 * 4);
	अगर (!call)
		वापस false;

	call->key = key;
	call->server = afs_use_server(server, afs_server_trace_get_caps);
	call->upgrade = true;
	call->async = true;
	call->max_lअगरespan = AFS_PROBE_MAX_LIFESPAN;

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSGETCAPABILITIES);

	trace_afs_make_fs_call(call, शून्य);
	afs_make_call(ac, call, GFP_NOFS);
	afs_put_call(call);
	वापस true;
पूर्ण

/*
 * Deliver reply data to an FS.InlineBulkStatus call
 */
अटल पूर्णांक afs_deliver_fs_अंतरभूत_bulk_status(काष्ठा afs_call *call)
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
		afs_extract_to_buf(call, 21 * माप(__be32));
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
		xdr_decode_AFSFetchStatus(&bp, call, scb);

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
		afs_extract_to_buf(call, 3 * माप(__be32));
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
		xdr_decode_AFSCallBack(&bp, call, scb);
		call->count++;
		अगर (call->count < op->nr_files)
			जाओ more_cbs;

		afs_extract_to_buf(call, 6 * माप(__be32));
		call->unmarshall++;
		fallthrough;

	हाल 5:
		ret = afs_extract_data(call, false);
		अगर (ret < 0)
			वापस ret;

		bp = call->buffer;
		xdr_decode_AFSVolSync(&bp, &op->volsync);

		call->unmarshall++;
		fallthrough;

	हाल 6:
		अवरोध;
	पूर्ण

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

अटल व्योम afs_करोne_fs_अंतरभूत_bulk_status(काष्ठा afs_call *call)
अणु
	अगर (call->error == -ECONNABORTED &&
	    call->पात_code == RX_INVALID_OPERATION) अणु
		set_bit(AFS_SERVER_FL_NO_IBULK, &call->server->flags);
		अगर (call->op)
			set_bit(AFS_VOLUME_MAYBE_NO_IBULK, &call->op->volume->flags);
	पूर्ण
पूर्ण

/*
 * FS.InlineBulkStatus operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSInlineBulkStatus = अणु
	.name		= "FS.InlineBulkStatus",
	.op		= afs_FS_InlineBulkStatus,
	.deliver	= afs_deliver_fs_अंतरभूत_bulk_status,
	.करोne		= afs_करोne_fs_अंतरभूत_bulk_status,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Fetch the status inक्रमmation क्रम up to 50 files
 */
व्योम afs_fs_अंतरभूत_bulk_status(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *dvp = &op->file[0];
	काष्ठा afs_vnode_param *vp = &op->file[1];
	काष्ठा afs_call *call;
	__be32 *bp;
	पूर्णांक i;

	अगर (test_bit(AFS_SERVER_FL_NO_IBULK, &op->server->flags)) अणु
		op->error = -ENOTSUPP;
		वापस;
	पूर्ण

	_enter(",%x,{%llx:%llu},%u",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode, op->nr_files);

	call = afs_alloc_flat_call(op->net, &afs_RXFSInlineBulkStatus,
				   (2 + op->nr_files * 3) * 4,
				   21 * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	*bp++ = htonl(FSINLINEBULKSTATUS);
	*bp++ = htonl(op->nr_files);
	*bp++ = htonl(dvp->fid.vid);
	*bp++ = htonl(dvp->fid.vnode);
	*bp++ = htonl(dvp->fid.unique);
	*bp++ = htonl(vp->fid.vid);
	*bp++ = htonl(vp->fid.vnode);
	*bp++ = htonl(vp->fid.unique);
	क्रम (i = 0; i < op->nr_files - 2; i++) अणु
		*bp++ = htonl(op->more_files[i].fid.vid);
		*bp++ = htonl(op->more_files[i].fid.vnode);
		*bp++ = htonl(op->more_files[i].fid.unique);
	पूर्ण

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_NOFS);
पूर्ण

/*
 * deliver reply data to an FS.FetchACL
 */
अटल पूर्णांक afs_deliver_fs_fetch_acl(काष्ठा afs_call *call)
अणु
	काष्ठा afs_operation *op = call->op;
	काष्ठा afs_vnode_param *vp = &op->file[0];
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

		/* extract the वापसed data length */
	हाल 1:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		size = call->count2 = ntohl(call->पंचांगp);
		size = round_up(size, 4);

		acl = kदो_स्मृति(काष्ठा_size(acl, data, size), GFP_KERNEL);
		अगर (!acl)
			वापस -ENOMEM;
		op->acl = acl;
		acl->size = call->count2;
		afs_extract_begin(call, acl->data, size);
		call->unmarshall++;
		fallthrough;

		/* extract the वापसed data */
	हाल 2:
		ret = afs_extract_data(call, true);
		अगर (ret < 0)
			वापस ret;

		afs_extract_to_buf(call, (21 + 6) * 4);
		call->unmarshall++;
		fallthrough;

		/* extract the metadata */
	हाल 3:
		ret = afs_extract_data(call, false);
		अगर (ret < 0)
			वापस ret;

		bp = call->buffer;
		xdr_decode_AFSFetchStatus(&bp, call, &vp->scb);
		xdr_decode_AFSVolSync(&bp, &op->volsync);

		call->unmarshall++;
		fallthrough;

	हाल 4:
		अवरोध;
	पूर्ण

	_leave(" = 0 [done]");
	वापस 0;
पूर्ण

/*
 * FS.FetchACL operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSFetchACL = अणु
	.name		= "FS.FetchACL",
	.op		= afs_FS_FetchACL,
	.deliver	= afs_deliver_fs_fetch_acl,
पूर्ण;

/*
 * Fetch the ACL क्रम a file.
 */
व्योम afs_fs_fetch_acl(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	__be32 *bp;

	_enter(",%x,{%llx:%llu},,",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode);

	call = afs_alloc_flat_call(op->net, &afs_RXFSFetchACL, 16, (21 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp[0] = htonl(FSFETCHACL);
	bp[1] = htonl(vp->fid.vid);
	bp[2] = htonl(vp->fid.vnode);
	bp[3] = htonl(vp->fid.unique);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_KERNEL);
पूर्ण

/*
 * FS.StoreACL operation type
 */
अटल स्थिर काष्ठा afs_call_type afs_RXFSStoreACL = अणु
	.name		= "FS.StoreACL",
	.op		= afs_FS_StoreACL,
	.deliver	= afs_deliver_fs_file_status_and_vol,
	.deकाष्ठाor	= afs_flat_call_deकाष्ठाor,
पूर्ण;

/*
 * Fetch the ACL क्रम a file.
 */
व्योम afs_fs_store_acl(काष्ठा afs_operation *op)
अणु
	काष्ठा afs_vnode_param *vp = &op->file[0];
	काष्ठा afs_call *call;
	स्थिर काष्ठा afs_acl *acl = op->acl;
	माप_प्रकार size;
	__be32 *bp;

	_enter(",%x,{%llx:%llu},,",
	       key_serial(op->key), vp->fid.vid, vp->fid.vnode);

	size = round_up(acl->size, 4);
	call = afs_alloc_flat_call(op->net, &afs_RXFSStoreACL,
				   5 * 4 + size, (21 + 6) * 4);
	अगर (!call)
		वापस afs_op_nomem(op);

	/* marshall the parameters */
	bp = call->request;
	bp[0] = htonl(FSSTOREACL);
	bp[1] = htonl(vp->fid.vid);
	bp[2] = htonl(vp->fid.vnode);
	bp[3] = htonl(vp->fid.unique);
	bp[4] = htonl(acl->size);
	स_नकल(&bp[5], acl->data, acl->size);
	अगर (acl->size != size)
		स_रखो((व्योम *)&bp[5] + acl->size, 0, size - acl->size);

	trace_afs_make_fs_call(call, &vp->fid);
	afs_make_op_call(op, call, GFP_KERNEL);
पूर्ण
