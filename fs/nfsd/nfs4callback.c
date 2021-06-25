<शैली गुरु>
/*
 *  Copyright (c) 2001 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Kendrick Smith <kmsmith@umich.edu>
 *  Andy Adamson <andros@umich.edu>
 *
 *  Redistribution and use in source and binary क्रमms, with or without
 *  modअगरication, are permitted provided that the following conditions
 *  are met:
 *
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in the
 *     करोcumentation and/or other materials provided with the distribution.
 *  3. Neither the name of the University nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED
 *  WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 *  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 *  FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 *  BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/xprt.h>
#समावेश <linux/sunrpc/svc_xprt.h>
#समावेश <linux/slab.h>
#समावेश "nfsd.h"
#समावेश "state.h"
#समावेश "netns.h"
#समावेश "trace.h"
#समावेश "xdr4cb.h"
#समावेश "xdr4.h"

#घोषणा NFSDDBG_FACILITY                NFSDDBG_PROC

अटल व्योम nfsd4_mark_cb_fault(काष्ठा nfs4_client *, पूर्णांक reason);

#घोषणा NFSPROC4_CB_शून्य 0
#घोषणा NFSPROC4_CB_COMPOUND 1

/* Index of predefined Linux callback client operations */

काष्ठा nfs4_cb_compound_hdr अणु
	/* args */
	u32		ident;	/* minorversion 0 only */
	u32		nops;
	__be32		*nops_p;
	u32		minorversion;
	/* res */
	पूर्णांक		status;
पूर्ण;

अटल __be32 *xdr_encode_empty_array(__be32 *p)
अणु
	*p++ = xdr_zero;
	वापस p;
पूर्ण

/*
 * Encode/decode NFSv4 CB basic data types
 *
 * Basic NFSv4 callback data types are defined in section 15 of RFC
 * 3530: "Network File System (NFS) version 4 Protocol" and section
 * 20 of RFC 5661: "Network File System (NFS) Version 4 Minor Version
 * 1 Protocol"
 */

/*
 *	nfs_cb_opnum4
 *
 *	क्रमागत nfs_cb_opnum4 अणु
 *		OP_CB_GETATTR		= 3,
 *		  ...
 *	पूर्ण;
 */
क्रमागत nfs_cb_opnum4 अणु
	OP_CB_GETATTR			= 3,
	OP_CB_RECALL			= 4,
	OP_CB_LAYOUTRECALL		= 5,
	OP_CB_NOTIFY			= 6,
	OP_CB_PUSH_DELEG		= 7,
	OP_CB_RECALL_ANY		= 8,
	OP_CB_RECALLABLE_OBJ_AVAIL	= 9,
	OP_CB_RECALL_SLOT		= 10,
	OP_CB_SEQUENCE			= 11,
	OP_CB_WANTS_CANCELLED		= 12,
	OP_CB_NOTIFY_LOCK		= 13,
	OP_CB_NOTIFY_DEVICEID		= 14,
	OP_CB_OFFLOAD			= 15,
	OP_CB_ILLEGAL			= 10044
पूर्ण;

अटल व्योम encode_nfs_cb_opnum4(काष्ठा xdr_stream *xdr, क्रमागत nfs_cb_opnum4 op)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	*p = cpu_to_be32(op);
पूर्ण

/*
 * nfs_fh4
 *
 *	प्रकार opaque nfs_fh4<NFS4_FHSIZE>;
 */
अटल व्योम encode_nfs_fh4(काष्ठा xdr_stream *xdr, स्थिर काष्ठा knfsd_fh *fh)
अणु
	u32 length = fh->fh_size;
	__be32 *p;

	BUG_ON(length > NFS4_FHSIZE);
	p = xdr_reserve_space(xdr, 4 + length);
	xdr_encode_opaque(p, &fh->fh_base, length);
पूर्ण

/*
 * stateid4
 *
 *	काष्ठा stateid4 अणु
 *		uपूर्णांक32_t	seqid;
 *		opaque		other[12];
 *	पूर्ण;
 */
अटल व्योम encode_stateid4(काष्ठा xdr_stream *xdr, स्थिर stateid_t *sid)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS4_STATEID_SIZE);
	*p++ = cpu_to_be32(sid->si_generation);
	xdr_encode_opaque_fixed(p, &sid->si_opaque, NFS4_STATEID_OTHER_SIZE);
पूर्ण

/*
 * sessionid4
 *
 *	प्रकार opaque sessionid4[NFS4_SESSIONID_SIZE];
 */
अटल व्योम encode_sessionid4(काष्ठा xdr_stream *xdr,
			      स्थिर काष्ठा nfsd4_session *session)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, NFS4_MAX_SESSIONID_LEN);
	xdr_encode_opaque_fixed(p, session->se_sessionid.data,
					NFS4_MAX_SESSIONID_LEN);
पूर्ण

/*
 * nfsstat4
 */
अटल स्थिर काष्ठा अणु
	पूर्णांक stat;
	पूर्णांक त्रुटि_सं;
पूर्ण nfs_cb_errtbl[] = अणु
	अणु NFS4_OK,		0		पूर्ण,
	अणु NFS4ERR_PERM,		-EPERM		पूर्ण,
	अणु NFS4ERR_NOENT,	-ENOENT		पूर्ण,
	अणु NFS4ERR_IO,		-EIO		पूर्ण,
	अणु NFS4ERR_NXIO,		-ENXIO		पूर्ण,
	अणु NFS4ERR_ACCESS,	-EACCES		पूर्ण,
	अणु NFS4ERR_EXIST,	-EEXIST		पूर्ण,
	अणु NFS4ERR_XDEV,		-EXDEV		पूर्ण,
	अणु NFS4ERR_NOTसूची,	-ENOTसूची	पूर्ण,
	अणु NFS4ERR_ISसूची,	-EISसूची		पूर्ण,
	अणु NFS4ERR_INVAL,	-EINVAL		पूर्ण,
	अणु NFS4ERR_FBIG,		-EFBIG		पूर्ण,
	अणु NFS4ERR_NOSPC,	-ENOSPC		पूर्ण,
	अणु NFS4ERR_ROFS,		-EROFS		पूर्ण,
	अणु NFS4ERR_MLINK,	-EMLINK		पूर्ण,
	अणु NFS4ERR_NAMETOOLONG,	-ENAMETOOLONG	पूर्ण,
	अणु NFS4ERR_NOTEMPTY,	-ENOTEMPTY	पूर्ण,
	अणु NFS4ERR_DQUOT,	-EDQUOT		पूर्ण,
	अणु NFS4ERR_STALE,	-ESTALE		पूर्ण,
	अणु NFS4ERR_BADHANDLE,	-EBADHANDLE	पूर्ण,
	अणु NFS4ERR_BAD_COOKIE,	-EBADCOOKIE	पूर्ण,
	अणु NFS4ERR_NOTSUPP,	-ENOTSUPP	पूर्ण,
	अणु NFS4ERR_TOOSMALL,	-ETOOSMALL	पूर्ण,
	अणु NFS4ERR_SERVERFAULT,	-ESERVERFAULT	पूर्ण,
	अणु NFS4ERR_BADTYPE,	-EBADTYPE	पूर्ण,
	अणु NFS4ERR_LOCKED,	-EAGAIN		पूर्ण,
	अणु NFS4ERR_RESOURCE,	-EREMOTEIO	पूर्ण,
	अणु NFS4ERR_SYMLINK,	-ELOOP		पूर्ण,
	अणु NFS4ERR_OP_ILLEGAL,	-EOPNOTSUPP	पूर्ण,
	अणु NFS4ERR_DEADLOCK,	-EDEADLK	पूर्ण,
	अणु -1,			-EIO		पूर्ण
पूर्ण;

/*
 * If we cannot translate the error, the recovery routines should
 * handle it.
 *
 * Note: reमुख्यing NFSv4 error codes have values > 10000, so should
 * not conflict with native Linux error codes.
 */
अटल पूर्णांक nfs_cb_stat_to_त्रुटि_सं(पूर्णांक status)
अणु
	पूर्णांक i;

	क्रम (i = 0; nfs_cb_errtbl[i].stat != -1; i++) अणु
		अगर (nfs_cb_errtbl[i].stat == status)
			वापस nfs_cb_errtbl[i].त्रुटि_सं;
	पूर्ण

	dprपूर्णांकk("NFSD: Unrecognized NFS CB status value: %u\n", status);
	वापस -status;
पूर्ण

अटल पूर्णांक decode_cb_op_status(काष्ठा xdr_stream *xdr,
			       क्रमागत nfs_cb_opnum4 expected, पूर्णांक *status)
अणु
	__be32 *p;
	u32 op;

	p = xdr_अंतरभूत_decode(xdr, 4 + 4);
	अगर (unlikely(p == शून्य))
		जाओ out_overflow;
	op = be32_to_cpup(p++);
	अगर (unlikely(op != expected))
		जाओ out_unexpected;
	*status = nfs_cb_stat_to_त्रुटि_सं(be32_to_cpup(p));
	वापस 0;
out_overflow:
	वापस -EIO;
out_unexpected:
	dprपूर्णांकk("NFSD: Callback server returned operation %d but "
		"we issued a request for %d\n", op, expected);
	वापस -EIO;
पूर्ण

/*
 * CB_COMPOUND4args
 *
 *	काष्ठा CB_COMPOUND4args अणु
 *		utf8str_cs	tag;
 *		uपूर्णांक32_t	minorversion;
 *		uपूर्णांक32_t	callback_ident;
 *		nfs_cb_argop4	argarray<>;
 *	पूर्ण;
*/
अटल व्योम encode_cb_compound4args(काष्ठा xdr_stream *xdr,
				    काष्ठा nfs4_cb_compound_hdr *hdr)
अणु
	__be32 * p;

	p = xdr_reserve_space(xdr, 4 + 4 + 4 + 4);
	p = xdr_encode_empty_array(p);		/* empty tag */
	*p++ = cpu_to_be32(hdr->minorversion);
	*p++ = cpu_to_be32(hdr->ident);

	hdr->nops_p = p;
	*p = cpu_to_be32(hdr->nops);		/* argarray element count */
पूर्ण

/*
 * Update argarray element count
 */
अटल व्योम encode_cb_nops(काष्ठा nfs4_cb_compound_hdr *hdr)
अणु
	BUG_ON(hdr->nops > NFS4_MAX_BACK_CHANNEL_OPS);
	*hdr->nops_p = cpu_to_be32(hdr->nops);
पूर्ण

/*
 * CB_COMPOUND4res
 *
 *	काष्ठा CB_COMPOUND4res अणु
 *		nfsstat4	status;
 *		utf8str_cs	tag;
 *		nfs_cb_resop4	resarray<>;
 *	पूर्ण;
 */
अटल पूर्णांक decode_cb_compound4res(काष्ठा xdr_stream *xdr,
				  काष्ठा nfs4_cb_compound_hdr *hdr)
अणु
	u32 length;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4 + 4);
	अगर (unlikely(p == शून्य))
		जाओ out_overflow;
	hdr->status = be32_to_cpup(p++);
	/* Ignore the tag */
	length = be32_to_cpup(p++);
	p = xdr_अंतरभूत_decode(xdr, length + 4);
	अगर (unlikely(p == शून्य))
		जाओ out_overflow;
	p += XDR_QUADLEN(length);
	hdr->nops = be32_to_cpup(p);
	वापस 0;
out_overflow:
	वापस -EIO;
पूर्ण

/*
 * CB_RECALL4args
 *
 *	काष्ठा CB_RECALL4args अणु
 *		stateid4	stateid;
 *		bool		truncate;
 *		nfs_fh4		fh;
 *	पूर्ण;
 */
अटल व्योम encode_cb_recall4args(काष्ठा xdr_stream *xdr,
				  स्थिर काष्ठा nfs4_delegation *dp,
				  काष्ठा nfs4_cb_compound_hdr *hdr)
अणु
	__be32 *p;

	encode_nfs_cb_opnum4(xdr, OP_CB_RECALL);
	encode_stateid4(xdr, &dp->dl_stid.sc_stateid);

	p = xdr_reserve_space(xdr, 4);
	*p++ = xdr_zero;			/* truncate */

	encode_nfs_fh4(xdr, &dp->dl_stid.sc_file->fi_fhandle);

	hdr->nops++;
पूर्ण

/*
 * CB_SEQUENCE4args
 *
 *	काष्ठा CB_SEQUENCE4args अणु
 *		sessionid4		csa_sessionid;
 *		sequenceid4		csa_sequenceid;
 *		slotid4			csa_slotid;
 *		slotid4			csa_highest_slotid;
 *		bool			csa_cachethis;
 *		referring_call_list4	csa_referring_call_lists<>;
 *	पूर्ण;
 */
अटल व्योम encode_cb_sequence4args(काष्ठा xdr_stream *xdr,
				    स्थिर काष्ठा nfsd4_callback *cb,
				    काष्ठा nfs4_cb_compound_hdr *hdr)
अणु
	काष्ठा nfsd4_session *session = cb->cb_clp->cl_cb_session;
	__be32 *p;

	अगर (hdr->minorversion == 0)
		वापस;

	encode_nfs_cb_opnum4(xdr, OP_CB_SEQUENCE);
	encode_sessionid4(xdr, session);

	p = xdr_reserve_space(xdr, 4 + 4 + 4 + 4 + 4);
	*p++ = cpu_to_be32(session->se_cb_seq_nr);	/* csa_sequenceid */
	*p++ = xdr_zero;			/* csa_slotid */
	*p++ = xdr_zero;			/* csa_highest_slotid */
	*p++ = xdr_zero;			/* csa_cachethis */
	xdr_encode_empty_array(p);		/* csa_referring_call_lists */

	hdr->nops++;
पूर्ण

/*
 * CB_SEQUENCE4resok
 *
 *	काष्ठा CB_SEQUENCE4resok अणु
 *		sessionid4	csr_sessionid;
 *		sequenceid4	csr_sequenceid;
 *		slotid4		csr_slotid;
 *		slotid4		csr_highest_slotid;
 *		slotid4		csr_target_highest_slotid;
 *	पूर्ण;
 *
 *	जोड़ CB_SEQUENCE4res चयन (nfsstat4 csr_status) अणु
 *	हाल NFS4_OK:
 *		CB_SEQUENCE4resok	csr_resok4;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 *
 * Our current back channel implmentation supports a single backchannel
 * with a single slot.
 */
अटल पूर्णांक decode_cb_sequence4resok(काष्ठा xdr_stream *xdr,
				    काष्ठा nfsd4_callback *cb)
अणु
	काष्ठा nfsd4_session *session = cb->cb_clp->cl_cb_session;
	पूर्णांक status = -ESERVERFAULT;
	__be32 *p;
	u32 dummy;

	/*
	 * If the server वापसs dअगरferent values क्रम sessionID, slotID or
	 * sequence number, the server is looney tunes.
	 */
	p = xdr_अंतरभूत_decode(xdr, NFS4_MAX_SESSIONID_LEN + 4 + 4 + 4 + 4);
	अगर (unlikely(p == शून्य))
		जाओ out_overflow;

	अगर (स_भेद(p, session->se_sessionid.data, NFS4_MAX_SESSIONID_LEN)) अणु
		dprपूर्णांकk("NFS: %s Invalid session id\n", __func__);
		जाओ out;
	पूर्ण
	p += XDR_QUADLEN(NFS4_MAX_SESSIONID_LEN);

	dummy = be32_to_cpup(p++);
	अगर (dummy != session->se_cb_seq_nr) अणु
		dprपूर्णांकk("NFS: %s Invalid sequence number\n", __func__);
		जाओ out;
	पूर्ण

	dummy = be32_to_cpup(p++);
	अगर (dummy != 0) अणु
		dprपूर्णांकk("NFS: %s Invalid slotid\n", __func__);
		जाओ out;
	पूर्ण

	/*
	 * FIXME: process highest slotid and target highest slotid
	 */
	status = 0;
out:
	cb->cb_seq_status = status;
	वापस status;
out_overflow:
	status = -EIO;
	जाओ out;
पूर्ण

अटल पूर्णांक decode_cb_sequence4res(काष्ठा xdr_stream *xdr,
				  काष्ठा nfsd4_callback *cb)
अणु
	पूर्णांक status;

	अगर (cb->cb_clp->cl_minorversion == 0)
		वापस 0;

	status = decode_cb_op_status(xdr, OP_CB_SEQUENCE, &cb->cb_seq_status);
	अगर (unlikely(status || cb->cb_seq_status))
		वापस status;

	वापस decode_cb_sequence4resok(xdr, cb);
पूर्ण

/*
 * NFSv4.0 and NFSv4.1 XDR encode functions
 *
 * NFSv4.0 callback argument types are defined in section 15 of RFC
 * 3530: "Network File System (NFS) version 4 Protocol" and section 20
 * of RFC 5661:  "Network File System (NFS) Version 4 Minor Version 1
 * Protocol".
 */

/*
 * NB: Without this zero space reservation, callbacks over krb5p fail
 */
अटल व्योम nfs4_xdr_enc_cb_null(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				 स्थिर व्योम *__unused)
अणु
	xdr_reserve_space(xdr, 0);
पूर्ण

/*
 * 20.2. Operation 4: CB_RECALL - Recall a Delegation
 */
अटल व्योम nfs4_xdr_enc_cb_recall(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				   स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfsd4_callback *cb = data;
	स्थिर काष्ठा nfs4_delegation *dp = cb_to_delegation(cb);
	काष्ठा nfs4_cb_compound_hdr hdr = अणु
		.ident = cb->cb_clp->cl_cb_ident,
		.minorversion = cb->cb_clp->cl_minorversion,
	पूर्ण;

	encode_cb_compound4args(xdr, &hdr);
	encode_cb_sequence4args(xdr, cb, &hdr);
	encode_cb_recall4args(xdr, dp, &hdr);
	encode_cb_nops(&hdr);
पूर्ण


/*
 * NFSv4.0 and NFSv4.1 XDR decode functions
 *
 * NFSv4.0 callback result types are defined in section 15 of RFC
 * 3530: "Network File System (NFS) version 4 Protocol" and section 20
 * of RFC 5661:  "Network File System (NFS) Version 4 Minor Version 1
 * Protocol".
 */

अटल पूर्णांक nfs4_xdr_dec_cb_null(काष्ठा rpc_rqst *req, काष्ठा xdr_stream *xdr,
				व्योम *__unused)
अणु
	वापस 0;
पूर्ण

/*
 * 20.2. Operation 4: CB_RECALL - Recall a Delegation
 */
अटल पूर्णांक nfs4_xdr_dec_cb_recall(काष्ठा rpc_rqst *rqstp,
				  काष्ठा xdr_stream *xdr,
				  व्योम *data)
अणु
	काष्ठा nfsd4_callback *cb = data;
	काष्ठा nfs4_cb_compound_hdr hdr;
	पूर्णांक status;

	status = decode_cb_compound4res(xdr, &hdr);
	अगर (unlikely(status))
		वापस status;

	status = decode_cb_sequence4res(xdr, cb);
	अगर (unlikely(status || cb->cb_seq_status))
		वापस status;

	वापस decode_cb_op_status(xdr, OP_CB_RECALL, &cb->cb_status);
पूर्ण

#अगर_घोषित CONFIG_NFSD_PNFS
/*
 * CB_LAYOUTRECALL4args
 *
 *	काष्ठा layoutrecall_file4 अणु
 *		nfs_fh4         lor_fh;
 *		offset4         lor_offset;
 *		length4         lor_length;
 *		stateid4        lor_stateid;
 *	पूर्ण;
 *
 *	जोड़ layoutrecall4 चयन(layoutrecall_type4 lor_recalltype) अणु
 *	हाल LAYOUTRECALL4_खाता:
 *		layoutrecall_file4 lor_layout;
 *	हाल LAYOUTRECALL4_FSID:
 *		fsid4              lor_fsid;
 *	हाल LAYOUTRECALL4_ALL:
 *		व्योम;
 *	पूर्ण;
 *
 *	काष्ठा CB_LAYOUTRECALL4args अणु
 *		layouttype4             clora_type;
 *		layoutiomode4           clora_iomode;
 *		bool                    clora_changed;
 *		layoutrecall4           clora_recall;
 *	पूर्ण;
 */
अटल व्योम encode_cb_layout4args(काष्ठा xdr_stream *xdr,
				  स्थिर काष्ठा nfs4_layout_stateid *ls,
				  काष्ठा nfs4_cb_compound_hdr *hdr)
अणु
	__be32 *p;

	BUG_ON(hdr->minorversion == 0);

	p = xdr_reserve_space(xdr, 5 * 4);
	*p++ = cpu_to_be32(OP_CB_LAYOUTRECALL);
	*p++ = cpu_to_be32(ls->ls_layout_type);
	*p++ = cpu_to_be32(IOMODE_ANY);
	*p++ = cpu_to_be32(1);
	*p = cpu_to_be32(RETURN_खाता);

	encode_nfs_fh4(xdr, &ls->ls_stid.sc_file->fi_fhandle);

	p = xdr_reserve_space(xdr, 2 * 8);
	p = xdr_encode_hyper(p, 0);
	xdr_encode_hyper(p, NFS4_MAX_UINT64);

	encode_stateid4(xdr, &ls->ls_recall_sid);

	hdr->nops++;
पूर्ण

अटल व्योम nfs4_xdr_enc_cb_layout(काष्ठा rpc_rqst *req,
				   काष्ठा xdr_stream *xdr,
				   स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfsd4_callback *cb = data;
	स्थिर काष्ठा nfs4_layout_stateid *ls =
		container_of(cb, काष्ठा nfs4_layout_stateid, ls_recall);
	काष्ठा nfs4_cb_compound_hdr hdr = अणु
		.ident = 0,
		.minorversion = cb->cb_clp->cl_minorversion,
	पूर्ण;

	encode_cb_compound4args(xdr, &hdr);
	encode_cb_sequence4args(xdr, cb, &hdr);
	encode_cb_layout4args(xdr, ls, &hdr);
	encode_cb_nops(&hdr);
पूर्ण

अटल पूर्णांक nfs4_xdr_dec_cb_layout(काष्ठा rpc_rqst *rqstp,
				  काष्ठा xdr_stream *xdr,
				  व्योम *data)
अणु
	काष्ठा nfsd4_callback *cb = data;
	काष्ठा nfs4_cb_compound_hdr hdr;
	पूर्णांक status;

	status = decode_cb_compound4res(xdr, &hdr);
	अगर (unlikely(status))
		वापस status;

	status = decode_cb_sequence4res(xdr, cb);
	अगर (unlikely(status || cb->cb_seq_status))
		वापस status;

	वापस decode_cb_op_status(xdr, OP_CB_LAYOUTRECALL, &cb->cb_status);
पूर्ण
#पूर्ण_अगर /* CONFIG_NFSD_PNFS */

अटल व्योम encode_stateowner(काष्ठा xdr_stream *xdr, काष्ठा nfs4_stateowner *so)
अणु
	__be32	*p;

	p = xdr_reserve_space(xdr, 8 + 4 + so->so_owner.len);
	p = xdr_encode_opaque_fixed(p, &so->so_client->cl_clientid, 8);
	xdr_encode_opaque(p, so->so_owner.data, so->so_owner.len);
पूर्ण

अटल व्योम nfs4_xdr_enc_cb_notअगरy_lock(काष्ठा rpc_rqst *req,
					काष्ठा xdr_stream *xdr,
					स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfsd4_callback *cb = data;
	स्थिर काष्ठा nfsd4_blocked_lock *nbl =
		container_of(cb, काष्ठा nfsd4_blocked_lock, nbl_cb);
	काष्ठा nfs4_lockowner *lo = (काष्ठा nfs4_lockowner *)nbl->nbl_lock.fl_owner;
	काष्ठा nfs4_cb_compound_hdr hdr = अणु
		.ident = 0,
		.minorversion = cb->cb_clp->cl_minorversion,
	पूर्ण;

	__be32 *p;

	BUG_ON(hdr.minorversion == 0);

	encode_cb_compound4args(xdr, &hdr);
	encode_cb_sequence4args(xdr, cb, &hdr);

	p = xdr_reserve_space(xdr, 4);
	*p = cpu_to_be32(OP_CB_NOTIFY_LOCK);
	encode_nfs_fh4(xdr, &nbl->nbl_fh);
	encode_stateowner(xdr, &lo->lo_owner);
	hdr.nops++;

	encode_cb_nops(&hdr);
पूर्ण

अटल पूर्णांक nfs4_xdr_dec_cb_notअगरy_lock(काष्ठा rpc_rqst *rqstp,
					काष्ठा xdr_stream *xdr,
					व्योम *data)
अणु
	काष्ठा nfsd4_callback *cb = data;
	काष्ठा nfs4_cb_compound_hdr hdr;
	पूर्णांक status;

	status = decode_cb_compound4res(xdr, &hdr);
	अगर (unlikely(status))
		वापस status;

	status = decode_cb_sequence4res(xdr, cb);
	अगर (unlikely(status || cb->cb_seq_status))
		वापस status;

	वापस decode_cb_op_status(xdr, OP_CB_NOTIFY_LOCK, &cb->cb_status);
पूर्ण

/*
 * काष्ठा ग_लिखो_response4 अणु
 *	stateid4	wr_callback_id<1>;
 *	length4		wr_count;
 *	stable_how4	wr_committed;
 *	verअगरier4	wr_ग_लिखोverf;
 * पूर्ण;
 * जोड़ offload_info4 चयन (nfsstat4 coa_status) अणु
 *	हाल NFS4_OK:
 *		ग_लिखो_response4	coa_resok4;
 *	शेष:
 *	length4		coa_bytes_copied;
 * पूर्ण;
 * काष्ठा CB_OFFLOAD4args अणु
 *	nfs_fh4		coa_fh;
 *	stateid4	coa_stateid;
 *	offload_info4	coa_offload_info;
 * पूर्ण;
 */
अटल व्योम encode_offload_info4(काष्ठा xdr_stream *xdr,
				 __be32 nfserr,
				 स्थिर काष्ठा nfsd4_copy *cp)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	*p++ = nfserr;
	अगर (!nfserr) अणु
		p = xdr_reserve_space(xdr, 4 + 8 + 4 + NFS4_VERIFIER_SIZE);
		p = xdr_encode_empty_array(p);
		p = xdr_encode_hyper(p, cp->cp_res.wr_bytes_written);
		*p++ = cpu_to_be32(cp->cp_res.wr_stable_how);
		p = xdr_encode_opaque_fixed(p, cp->cp_res.wr_verअगरier.data,
					    NFS4_VERIFIER_SIZE);
	पूर्ण अन्यथा अणु
		p = xdr_reserve_space(xdr, 8);
		/* We always वापस success अगर bytes were written */
		p = xdr_encode_hyper(p, 0);
	पूर्ण
पूर्ण

अटल व्योम encode_cb_offload4args(काष्ठा xdr_stream *xdr,
				   __be32 nfserr,
				   स्थिर काष्ठा knfsd_fh *fh,
				   स्थिर काष्ठा nfsd4_copy *cp,
				   काष्ठा nfs4_cb_compound_hdr *hdr)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	*p++ = cpu_to_be32(OP_CB_OFFLOAD);
	encode_nfs_fh4(xdr, fh);
	encode_stateid4(xdr, &cp->cp_res.cb_stateid);
	encode_offload_info4(xdr, nfserr, cp);

	hdr->nops++;
पूर्ण

अटल व्योम nfs4_xdr_enc_cb_offload(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr,
				    स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nfsd4_callback *cb = data;
	स्थिर काष्ठा nfsd4_copy *cp =
		container_of(cb, काष्ठा nfsd4_copy, cp_cb);
	काष्ठा nfs4_cb_compound_hdr hdr = अणु
		.ident = 0,
		.minorversion = cb->cb_clp->cl_minorversion,
	पूर्ण;

	encode_cb_compound4args(xdr, &hdr);
	encode_cb_sequence4args(xdr, cb, &hdr);
	encode_cb_offload4args(xdr, cp->nfserr, &cp->fh, cp, &hdr);
	encode_cb_nops(&hdr);
पूर्ण

अटल पूर्णांक nfs4_xdr_dec_cb_offload(काष्ठा rpc_rqst *rqstp,
				   काष्ठा xdr_stream *xdr,
				   व्योम *data)
अणु
	काष्ठा nfsd4_callback *cb = data;
	काष्ठा nfs4_cb_compound_hdr hdr;
	पूर्णांक status;

	status = decode_cb_compound4res(xdr, &hdr);
	अगर (unlikely(status))
		वापस status;

	status = decode_cb_sequence4res(xdr, cb);
	अगर (unlikely(status || cb->cb_seq_status))
		वापस status;

	वापस decode_cb_op_status(xdr, OP_CB_OFFLOAD, &cb->cb_status);
पूर्ण
/*
 * RPC procedure tables
 */
#घोषणा PROC(proc, call, argtype, restype)				\
[NFSPROC4_CLNT_##proc] = अणु						\
	.p_proc    = NFSPROC4_CB_##call,				\
	.p_encode  = nfs4_xdr_enc_##argtype,		\
	.p_decode  = nfs4_xdr_dec_##restype,				\
	.p_arglen  = NFS4_enc_##argtype##_sz,				\
	.p_replen  = NFS4_dec_##restype##_sz,				\
	.p_statidx = NFSPROC4_CB_##call,				\
	.p_name    = #proc,						\
पूर्ण

अटल स्थिर काष्ठा rpc_procinfo nfs4_cb_procedures[] = अणु
	PROC(CB_शून्य,	शून्य,		cb_null,	cb_null),
	PROC(CB_RECALL,	COMPOUND,	cb_recall,	cb_recall),
#अगर_घोषित CONFIG_NFSD_PNFS
	PROC(CB_LAYOUT,	COMPOUND,	cb_layout,	cb_layout),
#पूर्ण_अगर
	PROC(CB_NOTIFY_LOCK,	COMPOUND,	cb_notअगरy_lock,	cb_notअगरy_lock),
	PROC(CB_OFFLOAD,	COMPOUND,	cb_offload,	cb_offload),
पूर्ण;

अटल अचिन्हित पूर्णांक nfs4_cb_counts[ARRAY_SIZE(nfs4_cb_procedures)];
अटल स्थिर काष्ठा rpc_version nfs_cb_version4 = अणु
/*
 * Note on the callback rpc program version number: despite language in rfc
 * 5661 section 18.36.3 requiring servers to use 4 in this field, the
 * official xdr descriptions क्रम both 4.0 and 4.1 specअगरy version 1, and
 * in practice that appears to be what implementations use.  The section
 * 18.36.3 language is expected to be fixed in an erratum.
 */
	.number			= 1,
	.nrprocs		= ARRAY_SIZE(nfs4_cb_procedures),
	.procs			= nfs4_cb_procedures,
	.counts			= nfs4_cb_counts,
पूर्ण;

अटल स्थिर काष्ठा rpc_version *nfs_cb_version[2] = अणु
	[1] = &nfs_cb_version4,
पूर्ण;

अटल स्थिर काष्ठा rpc_program cb_program;

अटल काष्ठा rpc_stat cb_stats = अणु
	.program		= &cb_program
पूर्ण;

#घोषणा NFS4_CALLBACK 0x40000000
अटल स्थिर काष्ठा rpc_program cb_program = अणु
	.name			= "nfs4_cb",
	.number			= NFS4_CALLBACK,
	.nrvers			= ARRAY_SIZE(nfs_cb_version),
	.version		= nfs_cb_version,
	.stats			= &cb_stats,
	.pipe_dir_name		= "nfsd4_cb",
पूर्ण;

अटल पूर्णांक max_cb_समय(काष्ठा net *net)
अणु
	काष्ठा nfsd_net *nn = net_generic(net, nfsd_net_id);

	/*
	 * nfsd4_lease is set to at most one hour in __nfsd4_ग_लिखो_समय,
	 * so we can use 32-bit math on it. Warn अगर that assumption
	 * ever stops being true.
	 */
	अगर (WARN_ON_ONCE(nn->nfsd4_lease > 3600))
		वापस 360 * HZ;

	वापस max(((u32)nn->nfsd4_lease)/10, 1u) * HZ;
पूर्ण

अटल काष्ठा workqueue_काष्ठा *callback_wq;

अटल bool nfsd4_queue_cb(काष्ठा nfsd4_callback *cb)
अणु
	वापस queue_work(callback_wq, &cb->cb_work);
पूर्ण

अटल व्योम nfsd41_cb_inflight_begin(काष्ठा nfs4_client *clp)
अणु
	atomic_inc(&clp->cl_cb_inflight);
पूर्ण

अटल व्योम nfsd41_cb_inflight_end(काष्ठा nfs4_client *clp)
अणु

	अगर (atomic_dec_and_test(&clp->cl_cb_inflight))
		wake_up_var(&clp->cl_cb_inflight);
पूर्ण

अटल व्योम nfsd41_cb_inflight_रुको_complete(काष्ठा nfs4_client *clp)
अणु
	रुको_var_event(&clp->cl_cb_inflight,
			!atomic_पढ़ो(&clp->cl_cb_inflight));
पूर्ण

अटल स्थिर काष्ठा cred *get_backchannel_cred(काष्ठा nfs4_client *clp, काष्ठा rpc_clnt *client, काष्ठा nfsd4_session *ses)
अणु
	अगर (clp->cl_minorversion == 0) अणु
		client->cl_principal = clp->cl_cred.cr_targ_princ ?
			clp->cl_cred.cr_targ_princ : "nfs";

		वापस get_cred(rpc_machine_cred());
	पूर्ण अन्यथा अणु
		काष्ठा cred *kcred;

		kcred = prepare_kernel_cred(शून्य);
		अगर (!kcred)
			वापस शून्य;

		kcred->uid = ses->se_cb_sec.uid;
		kcred->gid = ses->se_cb_sec.gid;
		वापस kcred;
	पूर्ण
पूर्ण

अटल पूर्णांक setup_callback_client(काष्ठा nfs4_client *clp, काष्ठा nfs4_cb_conn *conn, काष्ठा nfsd4_session *ses)
अणु
	पूर्णांक maxसमय = max_cb_समय(clp->net);
	काष्ठा rpc_समयout	समयparms = अणु
		.to_initval	= maxसमय,
		.to_retries	= 0,
		.to_maxval	= maxसमय,
	पूर्ण;
	काष्ठा rpc_create_args args = अणु
		.net		= clp->net,
		.address	= (काष्ठा sockaddr *) &conn->cb_addr,
		.addrsize	= conn->cb_addrlen,
		.saddress	= (काष्ठा sockaddr *) &conn->cb_saddr,
		.समयout	= &समयparms,
		.program	= &cb_program,
		.version	= 1,
		.flags		= (RPC_CLNT_CREATE_NOPING | RPC_CLNT_CREATE_QUIET),
		.cred		= current_cred(),
	पूर्ण;
	काष्ठा rpc_clnt *client;
	स्थिर काष्ठा cred *cred;

	अगर (clp->cl_minorversion == 0) अणु
		अगर (!clp->cl_cred.cr_principal &&
		    (clp->cl_cred.cr_flavor >= RPC_AUTH_GSS_KRB5)) अणु
			trace_nfsd_cb_setup_err(clp, -EINVAL);
			वापस -EINVAL;
		पूर्ण
		args.client_name = clp->cl_cred.cr_principal;
		args.prognumber	= conn->cb_prog;
		args.protocol = XPRT_TRANSPORT_TCP;
		args.authflavor = clp->cl_cred.cr_flavor;
		clp->cl_cb_ident = conn->cb_ident;
	पूर्ण अन्यथा अणु
		अगर (!conn->cb_xprt) अणु
			trace_nfsd_cb_setup_err(clp, -EINVAL);
			वापस -EINVAL;
		पूर्ण
		clp->cl_cb_conn.cb_xprt = conn->cb_xprt;
		clp->cl_cb_session = ses;
		args.bc_xprt = conn->cb_xprt;
		args.prognumber = clp->cl_cb_session->se_cb_prog;
		args.protocol = conn->cb_xprt->xpt_class->xcl_ident |
				XPRT_TRANSPORT_BC;
		args.authflavor = ses->se_cb_sec.flavor;
	पूर्ण
	/* Create RPC client */
	client = rpc_create(&args);
	अगर (IS_ERR(client)) अणु
		trace_nfsd_cb_setup_err(clp, PTR_ERR(client));
		वापस PTR_ERR(client);
	पूर्ण
	cred = get_backchannel_cred(clp, client, ses);
	अगर (!cred) अणु
		trace_nfsd_cb_setup_err(clp, -ENOMEM);
		rpc_shutकरोwn_client(client);
		वापस -ENOMEM;
	पूर्ण
	clp->cl_cb_client = client;
	clp->cl_cb_cred = cred;
	trace_nfsd_cb_setup(clp);
	वापस 0;
पूर्ण

अटल व्योम nfsd4_mark_cb_करोwn(काष्ठा nfs4_client *clp, पूर्णांक reason)
अणु
	अगर (test_bit(NFSD4_CLIENT_CB_UPDATE, &clp->cl_flags))
		वापस;
	clp->cl_cb_state = NFSD4_CB_DOWN;
	trace_nfsd_cb_state(clp);
पूर्ण

अटल व्योम nfsd4_mark_cb_fault(काष्ठा nfs4_client *clp, पूर्णांक reason)
अणु
	अगर (test_bit(NFSD4_CLIENT_CB_UPDATE, &clp->cl_flags))
		वापस;
	clp->cl_cb_state = NFSD4_CB_FAULT;
	trace_nfsd_cb_state(clp);
पूर्ण

अटल व्योम nfsd4_cb_probe_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfs4_client *clp = container_of(calldata, काष्ठा nfs4_client, cl_cb_null);

	trace_nfsd_cb_करोne(clp, task->tk_status);
	अगर (task->tk_status)
		nfsd4_mark_cb_करोwn(clp, task->tk_status);
	अन्यथा अणु
		clp->cl_cb_state = NFSD4_CB_UP;
		trace_nfsd_cb_state(clp);
	पूर्ण
पूर्ण

अटल व्योम nfsd4_cb_probe_release(व्योम *calldata)
अणु
	काष्ठा nfs4_client *clp = container_of(calldata, काष्ठा nfs4_client, cl_cb_null);

	nfsd41_cb_inflight_end(clp);

पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfsd4_cb_probe_ops = अणु
	/* XXX: release method to ensure we set the cb channel करोwn अगर
	 * necessary on early failure? */
	.rpc_call_करोne = nfsd4_cb_probe_करोne,
	.rpc_release = nfsd4_cb_probe_release,
पूर्ण;

/*
 * Poke the callback thपढ़ो to process any updates to the callback
 * parameters, and send a null probe.
 */
व्योम nfsd4_probe_callback(काष्ठा nfs4_client *clp)
अणु
	clp->cl_cb_state = NFSD4_CB_UNKNOWN;
	trace_nfsd_cb_state(clp);
	set_bit(NFSD4_CLIENT_CB_UPDATE, &clp->cl_flags);
	nfsd4_run_cb(&clp->cl_cb_null);
पूर्ण

व्योम nfsd4_probe_callback_sync(काष्ठा nfs4_client *clp)
अणु
	nfsd4_probe_callback(clp);
	flush_workqueue(callback_wq);
पूर्ण

व्योम nfsd4_change_callback(काष्ठा nfs4_client *clp, काष्ठा nfs4_cb_conn *conn)
अणु
	clp->cl_cb_state = NFSD4_CB_UNKNOWN;
	spin_lock(&clp->cl_lock);
	स_नकल(&clp->cl_cb_conn, conn, माप(काष्ठा nfs4_cb_conn));
	spin_unlock(&clp->cl_lock);
	trace_nfsd_cb_state(clp);
पूर्ण

/*
 * There's currently a single callback channel slot.
 * If the slot is available, then mark it busy.  Otherwise, set the
 * thपढ़ो क्रम sleeping on the callback RPC रुको queue.
 */
अटल bool nfsd41_cb_get_slot(काष्ठा nfsd4_callback *cb, काष्ठा rpc_task *task)
अणु
	काष्ठा nfs4_client *clp = cb->cb_clp;

	अगर (!cb->cb_holds_slot &&
	    test_and_set_bit(0, &clp->cl_cb_slot_busy) != 0) अणु
		rpc_sleep_on(&clp->cl_cb_रुकोq, task, शून्य);
		/* Race अवरोधer */
		अगर (test_and_set_bit(0, &clp->cl_cb_slot_busy) != 0) अणु
			dprपूर्णांकk("%s slot is busy\n", __func__);
			वापस false;
		पूर्ण
		rpc_wake_up_queued_task(&clp->cl_cb_रुकोq, task);
	पूर्ण
	cb->cb_holds_slot = true;
	वापस true;
पूर्ण

अटल व्योम nfsd41_cb_release_slot(काष्ठा nfsd4_callback *cb)
अणु
	काष्ठा nfs4_client *clp = cb->cb_clp;

	अगर (cb->cb_holds_slot) अणु
		cb->cb_holds_slot = false;
		clear_bit(0, &clp->cl_cb_slot_busy);
		rpc_wake_up_next(&clp->cl_cb_रुकोq);
	पूर्ण
पूर्ण

अटल व्योम nfsd41_destroy_cb(काष्ठा nfsd4_callback *cb)
अणु
	काष्ठा nfs4_client *clp = cb->cb_clp;

	nfsd41_cb_release_slot(cb);
	अगर (cb->cb_ops && cb->cb_ops->release)
		cb->cb_ops->release(cb);
	nfsd41_cb_inflight_end(clp);
पूर्ण

/*
 * TODO: cb_sequence should support referring call lists, cachethis, multiple
 * slots, and mark callback channel करोwn on communication errors.
 */
अटल व्योम nfsd4_cb_prepare(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfsd4_callback *cb = calldata;
	काष्ठा nfs4_client *clp = cb->cb_clp;
	u32 minorversion = clp->cl_minorversion;

	/*
	 * cb_seq_status is only set in decode_cb_sequence4res,
	 * and so will reमुख्य 1 अगर an rpc level failure occurs.
	 */
	cb->cb_seq_status = 1;
	cb->cb_status = 0;
	अगर (minorversion && !nfsd41_cb_get_slot(cb, task))
		वापस;
	rpc_call_start(task);
पूर्ण

अटल bool nfsd4_cb_sequence_करोne(काष्ठा rpc_task *task, काष्ठा nfsd4_callback *cb)
अणु
	काष्ठा nfs4_client *clp = cb->cb_clp;
	काष्ठा nfsd4_session *session = clp->cl_cb_session;
	bool ret = true;

	अगर (!clp->cl_minorversion) अणु
		/*
		 * If the backchannel connection was shut करोwn जबतक this
		 * task was queued, we need to resubmit it after setting up
		 * a new backchannel connection.
		 *
		 * Note that अगर we lost our callback connection permanently
		 * the submission code will error out, so we करोn't need to
		 * handle that हाल here.
		 */
		अगर (RPC_SIGNALLED(task))
			जाओ need_restart;

		वापस true;
	पूर्ण

	अगर (!cb->cb_holds_slot)
		जाओ need_restart;

	चयन (cb->cb_seq_status) अणु
	हाल 0:
		/*
		 * No need क्रम lock, access serialized in nfsd4_cb_prepare
		 *
		 * RFC5661 20.9.3
		 * If CB_SEQUENCE वापसs an error, then the state of the slot
		 * (sequence ID, cached reply) MUST NOT change.
		 */
		++session->se_cb_seq_nr;
		अवरोध;
	हाल -ESERVERFAULT:
		++session->se_cb_seq_nr;
		fallthrough;
	हाल 1:
	हाल -NFS4ERR_BADSESSION:
		nfsd4_mark_cb_fault(cb->cb_clp, cb->cb_seq_status);
		ret = false;
		अवरोध;
	हाल -NFS4ERR_DELAY:
		अगर (!rpc_restart_call(task))
			जाओ out;

		rpc_delay(task, 2 * HZ);
		वापस false;
	हाल -NFS4ERR_BADSLOT:
		जाओ retry_noरुको;
	हाल -NFS4ERR_SEQ_MISORDERED:
		अगर (session->se_cb_seq_nr != 1) अणु
			session->se_cb_seq_nr = 1;
			जाओ retry_noरुको;
		पूर्ण
		अवरोध;
	शेष:
		nfsd4_mark_cb_fault(cb->cb_clp, cb->cb_seq_status);
		dprपूर्णांकk("%s: unprocessed error %d\n", __func__,
			cb->cb_seq_status);
	पूर्ण

	nfsd41_cb_release_slot(cb);
	dprपूर्णांकk("%s: freed slot, new seqid=%d\n", __func__,
		clp->cl_cb_session->se_cb_seq_nr);

	अगर (RPC_SIGNALLED(task))
		जाओ need_restart;
out:
	वापस ret;
retry_noरुको:
	अगर (rpc_restart_call_prepare(task))
		ret = false;
	जाओ out;
need_restart:
	अगर (!test_bit(NFSD4_CLIENT_CB_KILL, &clp->cl_flags)) अणु
		task->tk_status = 0;
		cb->cb_need_restart = true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम nfsd4_cb_करोne(काष्ठा rpc_task *task, व्योम *calldata)
अणु
	काष्ठा nfsd4_callback *cb = calldata;
	काष्ठा nfs4_client *clp = cb->cb_clp;

	trace_nfsd_cb_करोne(clp, task->tk_status);

	अगर (!nfsd4_cb_sequence_करोne(task, cb))
		वापस;

	अगर (cb->cb_status) अणु
		WARN_ON_ONCE(task->tk_status);
		task->tk_status = cb->cb_status;
	पूर्ण

	चयन (cb->cb_ops->करोne(cb, task)) अणु
	हाल 0:
		task->tk_status = 0;
		rpc_restart_call_prepare(task);
		वापस;
	हाल 1:
		चयन (task->tk_status) अणु
		हाल -EIO:
		हाल -ETIMEDOUT:
		हाल -EACCES:
			nfsd4_mark_cb_करोwn(clp, task->tk_status);
		पूर्ण
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण

अटल व्योम nfsd4_cb_release(व्योम *calldata)
अणु
	काष्ठा nfsd4_callback *cb = calldata;

	अगर (cb->cb_need_restart)
		nfsd4_queue_cb(cb);
	अन्यथा
		nfsd41_destroy_cb(cb);

पूर्ण

अटल स्थिर काष्ठा rpc_call_ops nfsd4_cb_ops = अणु
	.rpc_call_prepare = nfsd4_cb_prepare,
	.rpc_call_करोne = nfsd4_cb_करोne,
	.rpc_release = nfsd4_cb_release,
पूर्ण;

पूर्णांक nfsd4_create_callback_queue(व्योम)
अणु
	callback_wq = alloc_ordered_workqueue("nfsd4_callbacks", 0);
	अगर (!callback_wq)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम nfsd4_destroy_callback_queue(व्योम)
अणु
	destroy_workqueue(callback_wq);
पूर्ण

/* must be called under the state lock */
व्योम nfsd4_shutकरोwn_callback(काष्ठा nfs4_client *clp)
अणु
	set_bit(NFSD4_CLIENT_CB_KILL, &clp->cl_flags);
	/*
	 * Note this won't actually result in a null callback;
	 * instead, nfsd4_run_cb_null() will detect the समाप्तed
	 * client, destroy the rpc client, and stop:
	 */
	nfsd4_run_cb(&clp->cl_cb_null);
	flush_workqueue(callback_wq);
	nfsd41_cb_inflight_रुको_complete(clp);
पूर्ण

/* requires cl_lock: */
अटल काष्ठा nfsd4_conn * __nfsd4_find_backchannel(काष्ठा nfs4_client *clp)
अणु
	काष्ठा nfsd4_session *s;
	काष्ठा nfsd4_conn *c;

	list_क्रम_each_entry(s, &clp->cl_sessions, se_perclnt) अणु
		list_क्रम_each_entry(c, &s->se_conns, cn_persession) अणु
			अगर (c->cn_flags & NFS4_CDFC4_BACK)
				वापस c;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/*
 * Note there isn't a lot of locking in this code; instead we depend on
 * the fact that it is run from the callback_wq, which won't run two
 * work items at once.  So, क्रम example, callback_wq handles all access
 * of cl_cb_client and all calls to rpc_create or rpc_shutकरोwn_client.
 */
अटल व्योम nfsd4_process_cb_update(काष्ठा nfsd4_callback *cb)
अणु
	काष्ठा nfs4_cb_conn conn;
	काष्ठा nfs4_client *clp = cb->cb_clp;
	काष्ठा nfsd4_session *ses = शून्य;
	काष्ठा nfsd4_conn *c;
	पूर्णांक err;

	/*
	 * This is either an update, or the client dying; in either हाल,
	 * समाप्त the old client:
	 */
	अगर (clp->cl_cb_client) अणु
		trace_nfsd_cb_shutकरोwn(clp);
		rpc_shutकरोwn_client(clp->cl_cb_client);
		clp->cl_cb_client = शून्य;
		put_cred(clp->cl_cb_cred);
		clp->cl_cb_cred = शून्य;
	पूर्ण
	अगर (clp->cl_cb_conn.cb_xprt) अणु
		svc_xprt_put(clp->cl_cb_conn.cb_xprt);
		clp->cl_cb_conn.cb_xprt = शून्य;
	पूर्ण
	अगर (test_bit(NFSD4_CLIENT_CB_KILL, &clp->cl_flags))
		वापस;
	spin_lock(&clp->cl_lock);
	/*
	 * Only serialized callback code is allowed to clear these
	 * flags; मुख्य nfsd code can only set them:
	 */
	BUG_ON(!(clp->cl_flags & NFSD4_CLIENT_CB_FLAG_MASK));
	clear_bit(NFSD4_CLIENT_CB_UPDATE, &clp->cl_flags);
	स_नकल(&conn, &cb->cb_clp->cl_cb_conn, माप(काष्ठा nfs4_cb_conn));
	c = __nfsd4_find_backchannel(clp);
	अगर (c) अणु
		svc_xprt_get(c->cn_xprt);
		conn.cb_xprt = c->cn_xprt;
		ses = c->cn_session;
	पूर्ण
	spin_unlock(&clp->cl_lock);

	err = setup_callback_client(clp, &conn, ses);
	अगर (err) अणु
		nfsd4_mark_cb_करोwn(clp, err);
		अगर (c)
			svc_xprt_put(c->cn_xprt);
		वापस;
	पूर्ण
पूर्ण

अटल व्योम
nfsd4_run_cb_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा nfsd4_callback *cb =
		container_of(work, काष्ठा nfsd4_callback, cb_work);
	काष्ठा nfs4_client *clp = cb->cb_clp;
	काष्ठा rpc_clnt *clnt;
	पूर्णांक flags;

	trace_nfsd_cb_work(clp, cb->cb_msg.rpc_proc->p_name);

	अगर (cb->cb_need_restart) अणु
		cb->cb_need_restart = false;
	पूर्ण अन्यथा अणु
		अगर (cb->cb_ops && cb->cb_ops->prepare)
			cb->cb_ops->prepare(cb);
	पूर्ण

	अगर (clp->cl_flags & NFSD4_CLIENT_CB_FLAG_MASK)
		nfsd4_process_cb_update(cb);

	clnt = clp->cl_cb_client;
	अगर (!clnt) अणु
		/* Callback channel broken, or client समाप्तed; give up: */
		nfsd41_destroy_cb(cb);
		वापस;
	पूर्ण

	/*
	 * Don't send probe messages क्रम 4.1 or later.
	 */
	अगर (!cb->cb_ops && clp->cl_minorversion) अणु
		clp->cl_cb_state = NFSD4_CB_UP;
		nfsd41_destroy_cb(cb);
		वापस;
	पूर्ण

	cb->cb_msg.rpc_cred = clp->cl_cb_cred;
	flags = clp->cl_minorversion ? RPC_TASK_NOCONNECT : RPC_TASK_SOFTCONN;
	rpc_call_async(clnt, &cb->cb_msg, RPC_TASK_SOFT | flags,
			cb->cb_ops ? &nfsd4_cb_ops : &nfsd4_cb_probe_ops, cb);
पूर्ण

व्योम nfsd4_init_cb(काष्ठा nfsd4_callback *cb, काष्ठा nfs4_client *clp,
		स्थिर काष्ठा nfsd4_callback_ops *ops, क्रमागत nfsd4_cb_op op)
अणु
	cb->cb_clp = clp;
	cb->cb_msg.rpc_proc = &nfs4_cb_procedures[op];
	cb->cb_msg.rpc_argp = cb;
	cb->cb_msg.rpc_resp = cb;
	cb->cb_ops = ops;
	INIT_WORK(&cb->cb_work, nfsd4_run_cb_work);
	cb->cb_seq_status = 1;
	cb->cb_status = 0;
	cb->cb_need_restart = false;
	cb->cb_holds_slot = false;
पूर्ण

व्योम nfsd4_run_cb(काष्ठा nfsd4_callback *cb)
अणु
	काष्ठा nfs4_client *clp = cb->cb_clp;

	nfsd41_cb_inflight_begin(clp);
	अगर (!nfsd4_queue_cb(cb))
		nfsd41_cb_inflight_end(clp);
पूर्ण
