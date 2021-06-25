<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/nfs/callback_xdr.c
 *
 * Copyright (C) 2004 Trond Myklebust
 *
 * NFSv4 callback encode/decode procedures
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/nfs4.h>
#समावेश <linux/nfs_fs.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>
#समावेश <linux/sunrpc/bc_xprt.h>
#समावेश "nfs4_fs.h"
#समावेश "callback.h"
#समावेश "internal.h"
#समावेश "nfs4session.h"
#समावेश "nfs4trace.h"

#घोषणा CB_OP_TAGLEN_MAXSZ		(512)
#घोषणा CB_OP_HDR_RES_MAXSZ		(2 * 4) // opcode, status
#घोषणा CB_OP_GETATTR_BITMAP_MAXSZ	(4 * 4) // biपंचांगap length, 3 biपंचांगaps
#घोषणा CB_OP_GETATTR_RES_MAXSZ		(CB_OP_HDR_RES_MAXSZ + \
					 CB_OP_GETATTR_BITMAP_MAXSZ + \
					 /* change, size, स_समय, mसमय */\
					 (2 + 2 + 3 + 3) * 4)
#घोषणा CB_OP_RECALL_RES_MAXSZ		(CB_OP_HDR_RES_MAXSZ)

#अगर defined(CONFIG_NFS_V4_1)
#घोषणा CB_OP_LAYOUTRECALL_RES_MAXSZ	(CB_OP_HDR_RES_MAXSZ)
#घोषणा CB_OP_DEVICENOTIFY_RES_MAXSZ	(CB_OP_HDR_RES_MAXSZ)
#घोषणा CB_OP_SEQUENCE_RES_MAXSZ	(CB_OP_HDR_RES_MAXSZ + \
					 NFS4_MAX_SESSIONID_LEN + \
					 (1 + 3) * 4) // seqid, 3 slotids
#घोषणा CB_OP_RECALLANY_RES_MAXSZ	(CB_OP_HDR_RES_MAXSZ)
#घोषणा CB_OP_RECALLSLOT_RES_MAXSZ	(CB_OP_HDR_RES_MAXSZ)
#घोषणा CB_OP_NOTIFY_LOCK_RES_MAXSZ	(CB_OP_HDR_RES_MAXSZ)
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */
#अगर_घोषित CONFIG_NFS_V4_2
#घोषणा CB_OP_OFFLOAD_RES_MAXSZ		(CB_OP_HDR_RES_MAXSZ)
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */

#घोषणा NFSDBG_FACILITY NFSDBG_CALLBACK

/* Internal error code */
#घोषणा NFS4ERR_RESOURCE_HDR	11050

काष्ठा callback_op अणु
	__be32 (*process_op)(व्योम *, व्योम *, काष्ठा cb_process_state *);
	__be32 (*decode_args)(काष्ठा svc_rqst *, काष्ठा xdr_stream *, व्योम *);
	__be32 (*encode_res)(काष्ठा svc_rqst *, काष्ठा xdr_stream *,
			स्थिर व्योम *);
	दीर्घ res_maxsize;
पूर्ण;

अटल काष्ठा callback_op callback_ops[];

अटल __be32 nfs4_callback_null(काष्ठा svc_rqst *rqstp)
अणु
	वापस htonl(NFS4_OK);
पूर्ण

अटल पूर्णांक nfs4_decode_व्योम(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	वापस xdr_argsize_check(rqstp, p);
पूर्ण

अटल पूर्णांक nfs4_encode_व्योम(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	वापस xdr_ressize_check(rqstp, p);
पूर्ण

अटल __be32 decode_string(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक *len,
		स्थिर अक्षर **str, माप_प्रकार maxlen)
अणु
	sमाप_प्रकार err;

	err = xdr_stream_decode_opaque_अंतरभूत(xdr, (व्योम **)str, maxlen);
	अगर (err < 0)
		वापस cpu_to_be32(NFS4ERR_RESOURCE);
	*len = err;
	वापस 0;
पूर्ण

अटल __be32 decode_fh(काष्ठा xdr_stream *xdr, काष्ठा nfs_fh *fh)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_RESOURCE);
	fh->size = ntohl(*p);
	अगर (fh->size > NFS4_FHSIZE)
		वापस htonl(NFS4ERR_BADHANDLE);
	p = xdr_अंतरभूत_decode(xdr, fh->size);
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_RESOURCE);
	स_नकल(&fh->data[0], p, fh->size);
	स_रखो(&fh->data[fh->size], 0, माप(fh->data) - fh->size);
	वापस 0;
पूर्ण

अटल __be32 decode_biपंचांगap(काष्ठा xdr_stream *xdr, uपूर्णांक32_t *biपंचांगap)
अणु
	__be32 *p;
	अचिन्हित पूर्णांक attrlen;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_RESOURCE);
	attrlen = ntohl(*p);
	p = xdr_अंतरभूत_decode(xdr, attrlen << 2);
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_RESOURCE);
	अगर (likely(attrlen > 0))
		biपंचांगap[0] = ntohl(*p++);
	अगर (attrlen > 1)
		biपंचांगap[1] = ntohl(*p);
	वापस 0;
पूर्ण

अटल __be32 decode_stateid(काष्ठा xdr_stream *xdr, nfs4_stateid *stateid)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, NFS4_STATEID_SIZE);
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_RESOURCE);
	स_नकल(stateid->data, p, NFS4_STATEID_SIZE);
	वापस 0;
पूर्ण

अटल __be32 decode_delegation_stateid(काष्ठा xdr_stream *xdr, nfs4_stateid *stateid)
अणु
	stateid->type = NFS4_DELEGATION_STATEID_TYPE;
	वापस decode_stateid(xdr, stateid);
पूर्ण

अटल __be32 decode_compound_hdr_arg(काष्ठा xdr_stream *xdr, काष्ठा cb_compound_hdr_arg *hdr)
अणु
	__be32 *p;
	__be32 status;

	status = decode_string(xdr, &hdr->taglen, &hdr->tag, CB_OP_TAGLEN_MAXSZ);
	अगर (unlikely(status != 0))
		वापस status;
	p = xdr_अंतरभूत_decode(xdr, 12);
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_RESOURCE);
	hdr->minorversion = ntohl(*p++);
	/* Check क्रम minor version support */
	अगर (hdr->minorversion <= NFS4_MAX_MINOR_VERSION) अणु
		hdr->cb_ident = ntohl(*p++); /* ignored by v4.1 and v4.2 */
	पूर्ण अन्यथा अणु
		pr_warn_ratelimited("NFS: %s: NFSv4 server callback with "
			"illegal minor version %u!\n",
			__func__, hdr->minorversion);
		वापस htonl(NFS4ERR_MINOR_VERS_MISMATCH);
	पूर्ण
	hdr->nops = ntohl(*p);
	वापस 0;
पूर्ण

अटल __be32 decode_op_hdr(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक *op)
अणु
	__be32 *p;
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_RESOURCE_HDR);
	*op = ntohl(*p);
	वापस 0;
पूर्ण

अटल __be32 decode_getattr_args(काष्ठा svc_rqst *rqstp,
		काष्ठा xdr_stream *xdr, व्योम *argp)
अणु
	काष्ठा cb_getattrargs *args = argp;
	__be32 status;

	status = decode_fh(xdr, &args->fh);
	अगर (unlikely(status != 0))
		वापस status;
	वापस decode_biपंचांगap(xdr, args->biपंचांगap);
पूर्ण

अटल __be32 decode_recall_args(काष्ठा svc_rqst *rqstp,
		काष्ठा xdr_stream *xdr, व्योम *argp)
अणु
	काष्ठा cb_recallargs *args = argp;
	__be32 *p;
	__be32 status;

	status = decode_delegation_stateid(xdr, &args->stateid);
	अगर (unlikely(status != 0))
		वापस status;
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_RESOURCE);
	args->truncate = ntohl(*p);
	वापस decode_fh(xdr, &args->fh);
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)
अटल __be32 decode_layout_stateid(काष्ठा xdr_stream *xdr, nfs4_stateid *stateid)
अणु
	stateid->type = NFS4_LAYOUT_STATEID_TYPE;
	वापस decode_stateid(xdr, stateid);
पूर्ण

अटल __be32 decode_layoutrecall_args(काष्ठा svc_rqst *rqstp,
				       काष्ठा xdr_stream *xdr, व्योम *argp)
अणु
	काष्ठा cb_layoutrecallargs *args = argp;
	__be32 *p;
	__be32 status = 0;
	uपूर्णांक32_t iomode;

	p = xdr_अंतरभूत_decode(xdr, 4 * माप(uपूर्णांक32_t));
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_BADXDR);

	args->cbl_layout_type = ntohl(*p++);
	/* Depite the spec's xdr, iomode really beदीर्घs in the खाता चयन,
	 * as it is unusable and ignored with the other types.
	 */
	iomode = ntohl(*p++);
	args->cbl_layoutchanged = ntohl(*p++);
	args->cbl_recall_type = ntohl(*p++);

	अगर (args->cbl_recall_type == RETURN_खाता) अणु
		args->cbl_range.iomode = iomode;
		status = decode_fh(xdr, &args->cbl_fh);
		अगर (unlikely(status != 0))
			वापस status;

		p = xdr_अंतरभूत_decode(xdr, 2 * माप(uपूर्णांक64_t));
		अगर (unlikely(p == शून्य))
			वापस htonl(NFS4ERR_BADXDR);
		p = xdr_decode_hyper(p, &args->cbl_range.offset);
		p = xdr_decode_hyper(p, &args->cbl_range.length);
		वापस decode_layout_stateid(xdr, &args->cbl_stateid);
	पूर्ण अन्यथा अगर (args->cbl_recall_type == RETURN_FSID) अणु
		p = xdr_अंतरभूत_decode(xdr, 2 * माप(uपूर्णांक64_t));
		अगर (unlikely(p == शून्य))
			वापस htonl(NFS4ERR_BADXDR);
		p = xdr_decode_hyper(p, &args->cbl_fsid.major);
		p = xdr_decode_hyper(p, &args->cbl_fsid.minor);
	पूर्ण अन्यथा अगर (args->cbl_recall_type != RETURN_ALL)
		वापस htonl(NFS4ERR_BADXDR);
	वापस 0;
पूर्ण

अटल
__be32 decode_devicenotअगरy_args(काष्ठा svc_rqst *rqstp,
				काष्ठा xdr_stream *xdr,
				व्योम *argp)
अणु
	काष्ठा cb_devicenotअगरyargs *args = argp;
	__be32 *p;
	__be32 status = 0;
	u32 पंचांगp;
	पूर्णांक n, i;
	args->ndevs = 0;

	/* Num of device notअगरications */
	p = xdr_अंतरभूत_decode(xdr, माप(uपूर्णांक32_t));
	अगर (unlikely(p == शून्य)) अणु
		status = htonl(NFS4ERR_BADXDR);
		जाओ out;
	पूर्ण
	n = ntohl(*p++);
	अगर (n <= 0)
		जाओ out;
	अगर (n > अच_दीर्घ_उच्च / माप(*args->devs)) अणु
		status = htonl(NFS4ERR_BADXDR);
		जाओ out;
	पूर्ण

	args->devs = kदो_स्मृति_array(n, माप(*args->devs), GFP_KERNEL);
	अगर (!args->devs) अणु
		status = htonl(NFS4ERR_DELAY);
		जाओ out;
	पूर्ण

	/* Decode each dev notअगरication */
	क्रम (i = 0; i < n; i++) अणु
		काष्ठा cb_devicenotअगरyitem *dev = &args->devs[i];

		p = xdr_अंतरभूत_decode(xdr, (4 * माप(uपूर्णांक32_t)) +
				      NFS4_DEVICEID4_SIZE);
		अगर (unlikely(p == शून्य)) अणु
			status = htonl(NFS4ERR_BADXDR);
			जाओ err;
		पूर्ण

		पंचांगp = ntohl(*p++);	/* biपंचांगap size */
		अगर (पंचांगp != 1) अणु
			status = htonl(NFS4ERR_INVAL);
			जाओ err;
		पूर्ण
		dev->cbd_notअगरy_type = ntohl(*p++);
		अगर (dev->cbd_notअगरy_type != NOTIFY_DEVICEID4_CHANGE &&
		    dev->cbd_notअगरy_type != NOTIFY_DEVICEID4_DELETE) अणु
			status = htonl(NFS4ERR_INVAL);
			जाओ err;
		पूर्ण

		पंचांगp = ntohl(*p++);	/* opaque size */
		अगर (((dev->cbd_notअगरy_type == NOTIFY_DEVICEID4_CHANGE) &&
		     (पंचांगp != NFS4_DEVICEID4_SIZE + 8)) ||
		    ((dev->cbd_notअगरy_type == NOTIFY_DEVICEID4_DELETE) &&
		     (पंचांगp != NFS4_DEVICEID4_SIZE + 4))) अणु
			status = htonl(NFS4ERR_INVAL);
			जाओ err;
		पूर्ण
		dev->cbd_layout_type = ntohl(*p++);
		स_नकल(dev->cbd_dev_id.data, p, NFS4_DEVICEID4_SIZE);
		p += XDR_QUADLEN(NFS4_DEVICEID4_SIZE);

		अगर (dev->cbd_layout_type == NOTIFY_DEVICEID4_CHANGE) अणु
			p = xdr_अंतरभूत_decode(xdr, माप(uपूर्णांक32_t));
			अगर (unlikely(p == शून्य)) अणु
				status = htonl(NFS4ERR_BADXDR);
				जाओ err;
			पूर्ण
			dev->cbd_immediate = ntohl(*p++);
		पूर्ण अन्यथा अणु
			dev->cbd_immediate = 0;
		पूर्ण

		args->ndevs++;

		dprपूर्णांकk("%s: type %d layout 0x%x immediate %d\n",
			__func__, dev->cbd_notअगरy_type, dev->cbd_layout_type,
			dev->cbd_immediate);
	पूर्ण
out:
	dprपूर्णांकk("%s: status %d ndevs %d\n",
		__func__, ntohl(status), args->ndevs);
	वापस status;
err:
	kमुक्त(args->devs);
	जाओ out;
पूर्ण

अटल __be32 decode_sessionid(काष्ठा xdr_stream *xdr,
				 काष्ठा nfs4_sessionid *sid)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, NFS4_MAX_SESSIONID_LEN);
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_RESOURCE);

	स_नकल(sid->data, p, NFS4_MAX_SESSIONID_LEN);
	वापस 0;
पूर्ण

अटल __be32 decode_rc_list(काष्ठा xdr_stream *xdr,
			       काष्ठा referring_call_list *rc_list)
अणु
	__be32 *p;
	पूर्णांक i;
	__be32 status;

	status = decode_sessionid(xdr, &rc_list->rcl_sessionid);
	अगर (status)
		जाओ out;

	status = htonl(NFS4ERR_RESOURCE);
	p = xdr_अंतरभूत_decode(xdr, माप(uपूर्णांक32_t));
	अगर (unlikely(p == शून्य))
		जाओ out;

	rc_list->rcl_nrefcalls = ntohl(*p++);
	अगर (rc_list->rcl_nrefcalls) अणु
		p = xdr_अंतरभूत_decode(xdr,
			     rc_list->rcl_nrefcalls * 2 * माप(uपूर्णांक32_t));
		अगर (unlikely(p == शून्य))
			जाओ out;
		rc_list->rcl_refcalls = kदो_स्मृति_array(rc_list->rcl_nrefcalls,
						माप(*rc_list->rcl_refcalls),
						GFP_KERNEL);
		अगर (unlikely(rc_list->rcl_refcalls == शून्य))
			जाओ out;
		क्रम (i = 0; i < rc_list->rcl_nrefcalls; i++) अणु
			rc_list->rcl_refcalls[i].rc_sequenceid = ntohl(*p++);
			rc_list->rcl_refcalls[i].rc_slotid = ntohl(*p++);
		पूर्ण
	पूर्ण
	status = 0;

out:
	वापस status;
पूर्ण

अटल __be32 decode_cb_sequence_args(काष्ठा svc_rqst *rqstp,
					काष्ठा xdr_stream *xdr,
					व्योम *argp)
अणु
	काष्ठा cb_sequenceargs *args = argp;
	__be32 *p;
	पूर्णांक i;
	__be32 status;

	status = decode_sessionid(xdr, &args->csa_sessionid);
	अगर (status)
		वापस status;

	p = xdr_अंतरभूत_decode(xdr, 5 * माप(uपूर्णांक32_t));
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_RESOURCE);

	args->csa_addr = svc_addr(rqstp);
	args->csa_sequenceid = ntohl(*p++);
	args->csa_slotid = ntohl(*p++);
	args->csa_highestslotid = ntohl(*p++);
	args->csa_cachethis = ntohl(*p++);
	args->csa_nrclists = ntohl(*p++);
	args->csa_rclists = शून्य;
	अगर (args->csa_nrclists) अणु
		args->csa_rclists = kदो_स्मृति_array(args->csa_nrclists,
						  माप(*args->csa_rclists),
						  GFP_KERNEL);
		अगर (unlikely(args->csa_rclists == शून्य))
			वापस htonl(NFS4ERR_RESOURCE);

		क्रम (i = 0; i < args->csa_nrclists; i++) अणु
			status = decode_rc_list(xdr, &args->csa_rclists[i]);
			अगर (status) अणु
				args->csa_nrclists = i;
				जाओ out_मुक्त;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस 0;

out_मुक्त:
	क्रम (i = 0; i < args->csa_nrclists; i++)
		kमुक्त(args->csa_rclists[i].rcl_refcalls);
	kमुक्त(args->csa_rclists);
	वापस status;
पूर्ण

अटल __be32 decode_recallany_args(काष्ठा svc_rqst *rqstp,
				      काष्ठा xdr_stream *xdr,
				      व्योम *argp)
अणु
	काष्ठा cb_recallanyargs *args = argp;
	uपूर्णांक32_t biपंचांगap[2];
	__be32 *p, status;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_BADXDR);
	args->craa_objs_to_keep = ntohl(*p++);
	status = decode_biपंचांगap(xdr, biपंचांगap);
	अगर (unlikely(status))
		वापस status;
	args->craa_type_mask = biपंचांगap[0];

	वापस 0;
पूर्ण

अटल __be32 decode_recallslot_args(काष्ठा svc_rqst *rqstp,
					काष्ठा xdr_stream *xdr,
					व्योम *argp)
अणु
	काष्ठा cb_recallslotargs *args = argp;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_BADXDR);
	args->crsa_target_highest_slotid = ntohl(*p++);
	वापस 0;
पूर्ण

अटल __be32 decode_lockowner(काष्ठा xdr_stream *xdr, काष्ठा cb_notअगरy_lock_args *args)
अणु
	__be32		*p;
	अचिन्हित पूर्णांक	len;

	p = xdr_अंतरभूत_decode(xdr, 12);
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_BADXDR);

	p = xdr_decode_hyper(p, &args->cbnl_owner.clientid);
	len = be32_to_cpu(*p);

	p = xdr_अंतरभूत_decode(xdr, len);
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_BADXDR);

	/* Only try to decode अगर the length is right */
	अगर (len == 20) अणु
		p += 2;	/* skip "lock id:" */
		args->cbnl_owner.s_dev = be32_to_cpu(*p++);
		xdr_decode_hyper(p, &args->cbnl_owner.id);
		args->cbnl_valid = true;
	पूर्ण अन्यथा अणु
		args->cbnl_owner.s_dev = 0;
		args->cbnl_owner.id = 0;
		args->cbnl_valid = false;
	पूर्ण
	वापस 0;
पूर्ण

अटल __be32 decode_notअगरy_lock_args(काष्ठा svc_rqst *rqstp,
		काष्ठा xdr_stream *xdr, व्योम *argp)
अणु
	काष्ठा cb_notअगरy_lock_args *args = argp;
	__be32 status;

	status = decode_fh(xdr, &args->cbnl_fh);
	अगर (unlikely(status != 0))
		वापस status;
	वापस decode_lockowner(xdr, args);
पूर्ण

#पूर्ण_अगर /* CONFIG_NFS_V4_1 */
#अगर_घोषित CONFIG_NFS_V4_2
अटल __be32 decode_ग_लिखो_response(काष्ठा xdr_stream *xdr,
					काष्ठा cb_offloadargs *args)
अणु
	__be32 *p;

	/* skip the always zero field */
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		जाओ out;
	p++;

	/* decode count, stable_how, verअगरier */
	p = xdr_अंतरभूत_decode(xdr, 8 + 4);
	अगर (unlikely(!p))
		जाओ out;
	p = xdr_decode_hyper(p, &args->wr_count);
	args->wr_ग_लिखोverf.committed = be32_to_cpup(p);
	p = xdr_अंतरभूत_decode(xdr, NFS4_VERIFIER_SIZE);
	अगर (likely(p)) अणु
		स_नकल(&args->wr_ग_लिखोverf.verअगरier.data[0], p,
			NFS4_VERIFIER_SIZE);
		वापस 0;
	पूर्ण
out:
	वापस htonl(NFS4ERR_RESOURCE);
पूर्ण

अटल __be32 decode_offload_args(काष्ठा svc_rqst *rqstp,
					काष्ठा xdr_stream *xdr,
					व्योम *data)
अणु
	काष्ठा cb_offloadargs *args = data;
	__be32 *p;
	__be32 status;

	/* decode fh */
	status = decode_fh(xdr, &args->coa_fh);
	अगर (unlikely(status != 0))
		वापस status;

	/* decode stateid */
	status = decode_stateid(xdr, &args->coa_stateid);
	अगर (unlikely(status != 0))
		वापस status;

	/* decode status */
	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(!p))
		जाओ out;
	args->error = ntohl(*p++);
	अगर (!args->error) अणु
		status = decode_ग_लिखो_response(xdr, args);
		अगर (unlikely(status != 0))
			वापस status;
	पूर्ण अन्यथा अणु
		p = xdr_अंतरभूत_decode(xdr, 8);
		अगर (unlikely(!p))
			जाओ out;
		p = xdr_decode_hyper(p, &args->wr_count);
	पूर्ण
	वापस 0;
out:
	वापस htonl(NFS4ERR_RESOURCE);
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */
अटल __be32 encode_string(काष्ठा xdr_stream *xdr, अचिन्हित पूर्णांक len, स्थिर अक्षर *str)
अणु
	अगर (unlikely(xdr_stream_encode_opaque(xdr, str, len) < 0))
		वापस cpu_to_be32(NFS4ERR_RESOURCE);
	वापस 0;
पूर्ण

अटल __be32 encode_attr_biपंचांगap(काष्ठा xdr_stream *xdr, स्थिर uपूर्णांक32_t *biपंचांगap, माप_प्रकार sz)
अणु
	अगर (xdr_stream_encode_uपूर्णांक32_array(xdr, biपंचांगap, sz) < 0)
		वापस cpu_to_be32(NFS4ERR_RESOURCE);
	वापस 0;
पूर्ण

अटल __be32 encode_attr_change(काष्ठा xdr_stream *xdr, स्थिर uपूर्णांक32_t *biपंचांगap, uपूर्णांक64_t change)
अणु
	__be32 *p;

	अगर (!(biपंचांगap[0] & FATTR4_WORD0_CHANGE))
		वापस 0;
	p = xdr_reserve_space(xdr, 8);
	अगर (unlikely(!p))
		वापस htonl(NFS4ERR_RESOURCE);
	p = xdr_encode_hyper(p, change);
	वापस 0;
पूर्ण

अटल __be32 encode_attr_size(काष्ठा xdr_stream *xdr, स्थिर uपूर्णांक32_t *biपंचांगap, uपूर्णांक64_t size)
अणु
	__be32 *p;

	अगर (!(biपंचांगap[0] & FATTR4_WORD0_SIZE))
		वापस 0;
	p = xdr_reserve_space(xdr, 8);
	अगर (unlikely(!p))
		वापस htonl(NFS4ERR_RESOURCE);
	p = xdr_encode_hyper(p, size);
	वापस 0;
पूर्ण

अटल __be32 encode_attr_समय(काष्ठा xdr_stream *xdr, स्थिर काष्ठा बारpec64 *समय)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 12);
	अगर (unlikely(!p))
		वापस htonl(NFS4ERR_RESOURCE);
	p = xdr_encode_hyper(p, समय->tv_sec);
	*p = htonl(समय->tv_nsec);
	वापस 0;
पूर्ण

अटल __be32 encode_attr_स_समय(काष्ठा xdr_stream *xdr, स्थिर uपूर्णांक32_t *biपंचांगap, स्थिर काष्ठा बारpec64 *समय)
अणु
	अगर (!(biपंचांगap[1] & FATTR4_WORD1_TIME_METADATA))
		वापस 0;
	वापस encode_attr_समय(xdr,समय);
पूर्ण

अटल __be32 encode_attr_mसमय(काष्ठा xdr_stream *xdr, स्थिर uपूर्णांक32_t *biपंचांगap, स्थिर काष्ठा बारpec64 *समय)
अणु
	अगर (!(biपंचांगap[1] & FATTR4_WORD1_TIME_MODIFY))
		वापस 0;
	वापस encode_attr_समय(xdr,समय);
पूर्ण

अटल __be32 encode_compound_hdr_res(काष्ठा xdr_stream *xdr, काष्ठा cb_compound_hdr_res *hdr)
अणु
	__be32 status;

	hdr->status = xdr_reserve_space(xdr, 4);
	अगर (unlikely(hdr->status == शून्य))
		वापस htonl(NFS4ERR_RESOURCE);
	status = encode_string(xdr, hdr->taglen, hdr->tag);
	अगर (unlikely(status != 0))
		वापस status;
	hdr->nops = xdr_reserve_space(xdr, 4);
	अगर (unlikely(hdr->nops == शून्य))
		वापस htonl(NFS4ERR_RESOURCE);
	वापस 0;
पूर्ण

अटल __be32 encode_op_hdr(काष्ठा xdr_stream *xdr, uपूर्णांक32_t op, __be32 res)
अणु
	__be32 *p;
	
	p = xdr_reserve_space(xdr, 8);
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_RESOURCE_HDR);
	*p++ = htonl(op);
	*p = res;
	वापस 0;
पूर्ण

अटल __be32 encode_getattr_res(काष्ठा svc_rqst *rqstp, काष्ठा xdr_stream *xdr,
		स्थिर व्योम *resp)
अणु
	स्थिर काष्ठा cb_getattrres *res = resp;
	__be32 *savep = शून्य;
	__be32 status = res->status;
	
	अगर (unlikely(status != 0))
		जाओ out;
	status = encode_attr_biपंचांगap(xdr, res->biपंचांगap, ARRAY_SIZE(res->biपंचांगap));
	अगर (unlikely(status != 0))
		जाओ out;
	status = cpu_to_be32(NFS4ERR_RESOURCE);
	savep = xdr_reserve_space(xdr, माप(*savep));
	अगर (unlikely(!savep))
		जाओ out;
	status = encode_attr_change(xdr, res->biपंचांगap, res->change_attr);
	अगर (unlikely(status != 0))
		जाओ out;
	status = encode_attr_size(xdr, res->biपंचांगap, res->size);
	अगर (unlikely(status != 0))
		जाओ out;
	status = encode_attr_स_समय(xdr, res->biपंचांगap, &res->स_समय);
	अगर (unlikely(status != 0))
		जाओ out;
	status = encode_attr_mसमय(xdr, res->biपंचांगap, &res->mसमय);
	*savep = htonl((अचिन्हित पूर्णांक)((अक्षर *)xdr->p - (अक्षर *)(savep+1)));
out:
	वापस status;
पूर्ण

#अगर defined(CONFIG_NFS_V4_1)

अटल __be32 encode_sessionid(काष्ठा xdr_stream *xdr,
				 स्थिर काष्ठा nfs4_sessionid *sid)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS4_MAX_SESSIONID_LEN);
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_RESOURCE);

	स_नकल(p, sid, NFS4_MAX_SESSIONID_LEN);
	वापस 0;
पूर्ण

अटल __be32 encode_cb_sequence_res(काष्ठा svc_rqst *rqstp,
				       काष्ठा xdr_stream *xdr,
				       स्थिर व्योम *resp)
अणु
	स्थिर काष्ठा cb_sequenceres *res = resp;
	__be32 *p;
	__be32 status = res->csr_status;

	अगर (unlikely(status != 0))
		वापस status;

	status = encode_sessionid(xdr, &res->csr_sessionid);
	अगर (status)
		वापस status;

	p = xdr_reserve_space(xdr, 4 * माप(uपूर्णांक32_t));
	अगर (unlikely(p == शून्य))
		वापस htonl(NFS4ERR_RESOURCE);

	*p++ = htonl(res->csr_sequenceid);
	*p++ = htonl(res->csr_slotid);
	*p++ = htonl(res->csr_highestslotid);
	*p++ = htonl(res->csr_target_highestslotid);
	वापस 0;
पूर्ण

अटल __be32
preprocess_nfs41_op(पूर्णांक nop, अचिन्हित पूर्णांक op_nr, काष्ठा callback_op **op)
अणु
	अगर (op_nr == OP_CB_SEQUENCE) अणु
		अगर (nop != 0)
			वापस htonl(NFS4ERR_SEQUENCE_POS);
	पूर्ण अन्यथा अणु
		अगर (nop == 0)
			वापस htonl(NFS4ERR_OP_NOT_IN_SESSION);
	पूर्ण

	चयन (op_nr) अणु
	हाल OP_CB_GETATTR:
	हाल OP_CB_RECALL:
	हाल OP_CB_SEQUENCE:
	हाल OP_CB_RECALL_ANY:
	हाल OP_CB_RECALL_SLOT:
	हाल OP_CB_LAYOUTRECALL:
	हाल OP_CB_NOTIFY_DEVICEID:
	हाल OP_CB_NOTIFY_LOCK:
		*op = &callback_ops[op_nr];
		अवरोध;

	हाल OP_CB_NOTIFY:
	हाल OP_CB_PUSH_DELEG:
	हाल OP_CB_RECALLABLE_OBJ_AVAIL:
	हाल OP_CB_WANTS_CANCELLED:
		वापस htonl(NFS4ERR_NOTSUPP);

	शेष:
		वापस htonl(NFS4ERR_OP_ILLEGAL);
	पूर्ण

	वापस htonl(NFS_OK);
पूर्ण

अटल व्योम nfs4_callback_मुक्त_slot(काष्ठा nfs4_session *session,
		काष्ठा nfs4_slot *slot)
अणु
	काष्ठा nfs4_slot_table *tbl = &session->bc_slot_table;

	spin_lock(&tbl->slot_tbl_lock);
	/*
	 * Let the state manager know callback processing करोne.
	 * A single slot, so highest used slotid is either 0 or -1
	 */
	nfs4_मुक्त_slot(tbl, slot);
	spin_unlock(&tbl->slot_tbl_lock);
पूर्ण

अटल व्योम nfs4_cb_मुक्त_slot(काष्ठा cb_process_state *cps)
अणु
	अगर (cps->slot) अणु
		nfs4_callback_मुक्त_slot(cps->clp->cl_session, cps->slot);
		cps->slot = शून्य;
	पूर्ण
पूर्ण

#अन्यथा /* CONFIG_NFS_V4_1 */

अटल __be32
preprocess_nfs41_op(पूर्णांक nop, अचिन्हित पूर्णांक op_nr, काष्ठा callback_op **op)
अणु
	वापस htonl(NFS4ERR_MINOR_VERS_MISMATCH);
पूर्ण

अटल व्योम nfs4_cb_मुक्त_slot(काष्ठा cb_process_state *cps)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */

#अगर_घोषित CONFIG_NFS_V4_2
अटल __be32
preprocess_nfs42_op(पूर्णांक nop, अचिन्हित पूर्णांक op_nr, काष्ठा callback_op **op)
अणु
	__be32 status = preprocess_nfs41_op(nop, op_nr, op);
	अगर (status != htonl(NFS4ERR_OP_ILLEGAL))
		वापस status;

	अगर (op_nr == OP_CB_OFFLOAD) अणु
		*op = &callback_ops[op_nr];
		वापस htonl(NFS_OK);
	पूर्ण अन्यथा
		वापस htonl(NFS4ERR_NOTSUPP);
	वापस htonl(NFS4ERR_OP_ILLEGAL);
पूर्ण
#अन्यथा /* CONFIG_NFS_V4_2 */
अटल __be32
preprocess_nfs42_op(पूर्णांक nop, अचिन्हित पूर्णांक op_nr, काष्ठा callback_op **op)
अणु
	वापस htonl(NFS4ERR_MINOR_VERS_MISMATCH);
पूर्ण
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */

अटल __be32
preprocess_nfs4_op(अचिन्हित पूर्णांक op_nr, काष्ठा callback_op **op)
अणु
	चयन (op_nr) अणु
	हाल OP_CB_GETATTR:
	हाल OP_CB_RECALL:
		*op = &callback_ops[op_nr];
		अवरोध;
	शेष:
		वापस htonl(NFS4ERR_OP_ILLEGAL);
	पूर्ण

	वापस htonl(NFS_OK);
पूर्ण

अटल __be32 process_op(पूर्णांक nop, काष्ठा svc_rqst *rqstp,
		काष्ठा xdr_stream *xdr_in, व्योम *argp,
		काष्ठा xdr_stream *xdr_out, व्योम *resp,
		काष्ठा cb_process_state *cps)
अणु
	काष्ठा callback_op *op = &callback_ops[0];
	अचिन्हित पूर्णांक op_nr;
	__be32 status;
	दीर्घ maxlen;
	__be32 res;

	status = decode_op_hdr(xdr_in, &op_nr);
	अगर (unlikely(status))
		वापस status;

	चयन (cps->minorversion) अणु
	हाल 0:
		status = preprocess_nfs4_op(op_nr, &op);
		अवरोध;
	हाल 1:
		status = preprocess_nfs41_op(nop, op_nr, &op);
		अवरोध;
	हाल 2:
		status = preprocess_nfs42_op(nop, op_nr, &op);
		अवरोध;
	शेष:
		status = htonl(NFS4ERR_MINOR_VERS_MISMATCH);
	पूर्ण

	अगर (status == htonl(NFS4ERR_OP_ILLEGAL))
		op_nr = OP_CB_ILLEGAL;
	अगर (status)
		जाओ encode_hdr;

	अगर (cps->drc_status) अणु
		status = cps->drc_status;
		जाओ encode_hdr;
	पूर्ण

	maxlen = xdr_out->end - xdr_out->p;
	अगर (maxlen > 0 && maxlen < PAGE_SIZE) अणु
		status = op->decode_args(rqstp, xdr_in, argp);
		अगर (likely(status == 0))
			status = op->process_op(argp, resp, cps);
	पूर्ण अन्यथा
		status = htonl(NFS4ERR_RESOURCE);

encode_hdr:
	res = encode_op_hdr(xdr_out, op_nr, status);
	अगर (unlikely(res))
		वापस res;
	अगर (op->encode_res != शून्य && status == 0)
		status = op->encode_res(rqstp, xdr_out, resp);
	वापस status;
पूर्ण

/*
 * Decode, process and encode a COMPOUND
 */
अटल __be32 nfs4_callback_compound(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा cb_compound_hdr_arg hdr_arg = अणु 0 पूर्ण;
	काष्ठा cb_compound_hdr_res hdr_res = अणु शून्य पूर्ण;
	काष्ठा xdr_stream xdr_in, xdr_out;
	__be32 *p, status;
	काष्ठा cb_process_state cps = अणु
		.drc_status = 0,
		.clp = शून्य,
		.net = SVC_NET(rqstp),
	पूर्ण;
	अचिन्हित पूर्णांक nops = 0;

	xdr_init_decode(&xdr_in, &rqstp->rq_arg,
			rqstp->rq_arg.head[0].iov_base, शून्य);

	p = (__be32*)((अक्षर *)rqstp->rq_res.head[0].iov_base + rqstp->rq_res.head[0].iov_len);
	xdr_init_encode(&xdr_out, &rqstp->rq_res, p, शून्य);

	status = decode_compound_hdr_arg(&xdr_in, &hdr_arg);
	अगर (status == htonl(NFS4ERR_RESOURCE))
		वापस rpc_garbage_args;

	अगर (hdr_arg.minorversion == 0) अणु
		cps.clp = nfs4_find_client_ident(SVC_NET(rqstp), hdr_arg.cb_ident);
		अगर (!cps.clp) अणु
			trace_nfs_cb_no_clp(rqstp->rq_xid, hdr_arg.cb_ident);
			जाओ out_invalidcred;
		पूर्ण
		अगर (!check_gss_callback_principal(cps.clp, rqstp)) अणु
			trace_nfs_cb_badprinc(rqstp->rq_xid, hdr_arg.cb_ident);
			nfs_put_client(cps.clp);
			जाओ out_invalidcred;
		पूर्ण
	पूर्ण

	cps.minorversion = hdr_arg.minorversion;
	hdr_res.taglen = hdr_arg.taglen;
	hdr_res.tag = hdr_arg.tag;
	अगर (encode_compound_hdr_res(&xdr_out, &hdr_res) != 0) अणु
		अगर (cps.clp)
			nfs_put_client(cps.clp);
		वापस rpc_प्रणाली_err;
	पूर्ण
	जबतक (status == 0 && nops != hdr_arg.nops) अणु
		status = process_op(nops, rqstp, &xdr_in,
				    rqstp->rq_argp, &xdr_out, rqstp->rq_resp,
				    &cps);
		nops++;
	पूर्ण

	/* Buffer overflow in decode_ops_hdr or encode_ops_hdr. Return
	* resource error in cb_compound status without वापसing op */
	अगर (unlikely(status == htonl(NFS4ERR_RESOURCE_HDR))) अणु
		status = htonl(NFS4ERR_RESOURCE);
		nops--;
	पूर्ण

	*hdr_res.status = status;
	*hdr_res.nops = htonl(nops);
	nfs4_cb_मुक्त_slot(&cps);
	nfs_put_client(cps.clp);
	वापस rpc_success;

out_invalidcred:
	pr_warn_ratelimited("NFS: NFSv4 callback contains invalid cred\n");
	वापस svc_वापस_autherr(rqstp, rpc_autherr_badcred);
पूर्ण

/*
 * Define NFS4 callback COMPOUND ops.
 */
अटल काष्ठा callback_op callback_ops[] = अणु
	[0] = अणु
		.res_maxsize = CB_OP_HDR_RES_MAXSZ,
	पूर्ण,
	[OP_CB_GETATTR] = अणु
		.process_op = nfs4_callback_getattr,
		.decode_args = decode_getattr_args,
		.encode_res = encode_getattr_res,
		.res_maxsize = CB_OP_GETATTR_RES_MAXSZ,
	पूर्ण,
	[OP_CB_RECALL] = अणु
		.process_op = nfs4_callback_recall,
		.decode_args = decode_recall_args,
		.res_maxsize = CB_OP_RECALL_RES_MAXSZ,
	पूर्ण,
#अगर defined(CONFIG_NFS_V4_1)
	[OP_CB_LAYOUTRECALL] = अणु
		.process_op = nfs4_callback_layoutrecall,
		.decode_args = decode_layoutrecall_args,
		.res_maxsize = CB_OP_LAYOUTRECALL_RES_MAXSZ,
	पूर्ण,
	[OP_CB_NOTIFY_DEVICEID] = अणु
		.process_op = nfs4_callback_devicenotअगरy,
		.decode_args = decode_devicenotअगरy_args,
		.res_maxsize = CB_OP_DEVICENOTIFY_RES_MAXSZ,
	पूर्ण,
	[OP_CB_SEQUENCE] = अणु
		.process_op = nfs4_callback_sequence,
		.decode_args = decode_cb_sequence_args,
		.encode_res = encode_cb_sequence_res,
		.res_maxsize = CB_OP_SEQUENCE_RES_MAXSZ,
	पूर्ण,
	[OP_CB_RECALL_ANY] = अणु
		.process_op = nfs4_callback_recallany,
		.decode_args = decode_recallany_args,
		.res_maxsize = CB_OP_RECALLANY_RES_MAXSZ,
	पूर्ण,
	[OP_CB_RECALL_SLOT] = अणु
		.process_op = nfs4_callback_recallslot,
		.decode_args = decode_recallslot_args,
		.res_maxsize = CB_OP_RECALLSLOT_RES_MAXSZ,
	पूर्ण,
	[OP_CB_NOTIFY_LOCK] = अणु
		.process_op = nfs4_callback_notअगरy_lock,
		.decode_args = decode_notअगरy_lock_args,
		.res_maxsize = CB_OP_NOTIFY_LOCK_RES_MAXSZ,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NFS_V4_1 */
#अगर_घोषित CONFIG_NFS_V4_2
	[OP_CB_OFFLOAD] = अणु
		.process_op = nfs4_callback_offload,
		.decode_args = decode_offload_args,
		.res_maxsize = CB_OP_OFFLOAD_RES_MAXSZ,
	पूर्ण,
#पूर्ण_अगर /* CONFIG_NFS_V4_2 */
पूर्ण;

/*
 * Define NFS4 callback procedures
 */
अटल स्थिर काष्ठा svc_procedure nfs4_callback_procedures1[] = अणु
	[CB_शून्य] = अणु
		.pc_func = nfs4_callback_null,
		.pc_decode = nfs4_decode_व्योम,
		.pc_encode = nfs4_encode_व्योम,
		.pc_xdrressize = 1,
		.pc_name = "NULL",
	पूर्ण,
	[CB_COMPOUND] = अणु
		.pc_func = nfs4_callback_compound,
		.pc_encode = nfs4_encode_व्योम,
		.pc_argsize = 256,
		.pc_ressize = 256,
		.pc_xdrressize = NFS4_CALLBACK_बफ_मानE,
		.pc_name = "COMPOUND",
	पूर्ण
पूर्ण;

अटल अचिन्हित पूर्णांक nfs4_callback_count1[ARRAY_SIZE(nfs4_callback_procedures1)];
स्थिर काष्ठा svc_version nfs4_callback_version1 = अणु
	.vs_vers = 1,
	.vs_nproc = ARRAY_SIZE(nfs4_callback_procedures1),
	.vs_proc = nfs4_callback_procedures1,
	.vs_count = nfs4_callback_count1,
	.vs_xdrsize = NFS4_CALLBACK_XDRSIZE,
	.vs_dispatch = शून्य,
	.vs_hidden = true,
	.vs_need_cong_ctrl = true,
पूर्ण;

अटल अचिन्हित पूर्णांक nfs4_callback_count4[ARRAY_SIZE(nfs4_callback_procedures1)];
स्थिर काष्ठा svc_version nfs4_callback_version4 = अणु
	.vs_vers = 4,
	.vs_nproc = ARRAY_SIZE(nfs4_callback_procedures1),
	.vs_proc = nfs4_callback_procedures1,
	.vs_count = nfs4_callback_count4,
	.vs_xdrsize = NFS4_CALLBACK_XDRSIZE,
	.vs_dispatch = शून्य,
	.vs_hidden = true,
	.vs_need_cong_ctrl = true,
पूर्ण;
