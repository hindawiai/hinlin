<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/lockd/clnt4xdr.c
 *
 * XDR functions to encode/decode NLM version 4 RPC arguments and results.
 *
 * NLM client-side only.
 *
 * Copyright (C) 2010, Oracle.  All rights reserved.
 */

#समावेश <linux/types.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/stats.h>
#समावेश <linux/lockd/lockd.h>

#समावेश <uapi/linux/nfs3.h>

#घोषणा NLMDBG_FACILITY		NLMDBG_XDR

#अगर (NLMCLNT_OHSIZE > XDR_MAX_NETOBJ)
#  error "NLM host name cannot be larger than XDR_MAX_NETOBJ!"
#पूर्ण_अगर

#अगर (NLMCLNT_OHSIZE > NLM_MAXSTRLEN)
#  error "NLM host name cannot be larger than NLM's maximum string length!"
#पूर्ण_अगर

/*
 * Declare the space requirements क्रम NLM arguments and replies as
 * number of 32bit-words
 */
#घोषणा NLM4_व्योम_sz		(0)
#घोषणा NLM4_cookie_sz		(1+(NLM_MAXCOOKIELEN>>2))
#घोषणा NLM4_caller_sz		(1+(NLMCLNT_OHSIZE>>2))
#घोषणा NLM4_owner_sz		(1+(NLMCLNT_OHSIZE>>2))
#घोषणा NLM4_fhandle_sz		(1+(NFS3_FHSIZE>>2))
#घोषणा NLM4_lock_sz		(5+NLM4_caller_sz+NLM4_owner_sz+NLM4_fhandle_sz)
#घोषणा NLM4_holder_sz		(6+NLM4_owner_sz)

#घोषणा NLM4_testargs_sz	(NLM4_cookie_sz+1+NLM4_lock_sz)
#घोषणा NLM4_lockargs_sz	(NLM4_cookie_sz+4+NLM4_lock_sz)
#घोषणा NLM4_cancargs_sz	(NLM4_cookie_sz+2+NLM4_lock_sz)
#घोषणा NLM4_unlockargs_sz	(NLM4_cookie_sz+NLM4_lock_sz)

#घोषणा NLM4_testres_sz		(NLM4_cookie_sz+1+NLM4_holder_sz)
#घोषणा NLM4_res_sz		(NLM4_cookie_sz+1)
#घोषणा NLM4_norep_sz		(0)


अटल s64 loff_t_to_s64(loff_t offset)
अणु
	s64 res;

	अगर (offset >= NLM4_OFFSET_MAX)
		res = NLM4_OFFSET_MAX;
	अन्यथा अगर (offset <= -NLM4_OFFSET_MAX)
		res = -NLM4_OFFSET_MAX;
	अन्यथा
		res = offset;
	वापस res;
पूर्ण

अटल व्योम nlm4_compute_offsets(स्थिर काष्ठा nlm_lock *lock,
				 u64 *l_offset, u64 *l_len)
अणु
	स्थिर काष्ठा file_lock *fl = &lock->fl;

	*l_offset = loff_t_to_s64(fl->fl_start);
	अगर (fl->fl_end == OFFSET_MAX)
		*l_len = 0;
	अन्यथा
		*l_len = loff_t_to_s64(fl->fl_end - fl->fl_start + 1);
पूर्ण

/*
 * Encode/decode NLMv4 basic data types
 *
 * Basic NLMv4 data types are defined in Appendix II, section 6.1.4
 * of RFC 1813: "NFS Version 3 Protocol Specification" and in Chapter
 * 10 of X/Open's "Protocols for Interworking: XNFS, Version 3W".
 *
 * Not all basic data types have their own encoding and decoding
 * functions.  For run-समय efficiency, some data types are encoded
 * or decoded अंतरभूत.
 */

अटल व्योम encode_bool(काष्ठा xdr_stream *xdr, स्थिर पूर्णांक value)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	*p = value ? xdr_one : xdr_zero;
पूर्ण

अटल व्योम encode_पूर्णांक32(काष्ठा xdr_stream *xdr, स्थिर s32 value)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 4);
	*p = cpu_to_be32(value);
पूर्ण

/*
 *	प्रकार opaque netobj<MAXNETOBJ_SZ>
 */
अटल व्योम encode_netobj(काष्ठा xdr_stream *xdr,
			  स्थिर u8 *data, स्थिर अचिन्हित पूर्णांक length)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 4 + length);
	xdr_encode_opaque(p, data, length);
पूर्ण

अटल पूर्णांक decode_netobj(काष्ठा xdr_stream *xdr,
			 काष्ठा xdr_netobj *obj)
अणु
	sमाप_प्रकार ret;

	ret = xdr_stream_decode_opaque_अंतरभूत(xdr, (व्योम *)&obj->data,
						XDR_MAX_NETOBJ);
	अगर (unlikely(ret < 0))
		वापस -EIO;
	obj->len = ret;
	वापस 0;
पूर्ण

/*
 *	netobj cookie;
 */
अटल व्योम encode_cookie(काष्ठा xdr_stream *xdr,
			  स्थिर काष्ठा nlm_cookie *cookie)
अणु
	encode_netobj(xdr, (u8 *)&cookie->data, cookie->len);
पूर्ण

अटल पूर्णांक decode_cookie(काष्ठा xdr_stream *xdr,
			     काष्ठा nlm_cookie *cookie)
अणु
	u32 length;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		जाओ out_overflow;
	length = be32_to_cpup(p++);
	/* apparently HPUX can वापस empty cookies */
	अगर (length == 0)
		जाओ out_hpux;
	अगर (length > NLM_MAXCOOKIELEN)
		जाओ out_size;
	p = xdr_अंतरभूत_decode(xdr, length);
	अगर (unlikely(p == शून्य))
		जाओ out_overflow;
	cookie->len = length;
	स_नकल(cookie->data, p, length);
	वापस 0;
out_hpux:
	cookie->len = 4;
	स_रखो(cookie->data, 0, 4);
	वापस 0;
out_size:
	dprपूर्णांकk("NFS: returned cookie was too long: %u\n", length);
	वापस -EIO;
out_overflow:
	वापस -EIO;
पूर्ण

/*
 *	netobj fh;
 */
अटल व्योम encode_fh(काष्ठा xdr_stream *xdr, स्थिर काष्ठा nfs_fh *fh)
अणु
	encode_netobj(xdr, (u8 *)&fh->data, fh->size);
पूर्ण

/*
 *	क्रमागत nlm4_stats अणु
 *		NLM4_GRANTED = 0,
 *		NLM4_DENIED = 1,
 *		NLM4_DENIED_NOLOCKS = 2,
 *		NLM4_BLOCKED = 3,
 *		NLM4_DENIED_GRACE_PERIOD = 4,
 *		NLM4_DEADLCK = 5,
 *		NLM4_ROFS = 6,
 *		NLM4_STALE_FH = 7,
 *		NLM4_FBIG = 8,
 *		NLM4_FAILED = 9
 *	पूर्ण;
 *
 *	काष्ठा nlm4_stat अणु
 *		nlm4_stats stat;
 *	पूर्ण;
 *
 * NB: we करोn't swap bytes क्रम the NLM status values.  The upper
 * layers deal directly with the status value in network byte
 * order.
 */
अटल व्योम encode_nlm4_stat(काष्ठा xdr_stream *xdr,
			     स्थिर __be32 stat)
अणु
	__be32 *p;

	BUG_ON(be32_to_cpu(stat) > NLM_FAILED);
	p = xdr_reserve_space(xdr, 4);
	*p = stat;
पूर्ण

अटल पूर्णांक decode_nlm4_stat(काष्ठा xdr_stream *xdr, __be32 *stat)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4);
	अगर (unlikely(p == शून्य))
		जाओ out_overflow;
	अगर (unlikely(ntohl(*p) > ntohl(nlm4_failed)))
		जाओ out_bad_xdr;
	*stat = *p;
	वापस 0;
out_bad_xdr:
	dprपूर्णांकk("%s: server returned invalid nlm4_stats value: %u\n",
			__func__, be32_to_cpup(p));
	वापस -EIO;
out_overflow:
	वापस -EIO;
पूर्ण

/*
 *	काष्ठा nlm4_holder अणु
 *		bool	exclusive;
 *		पूर्णांक32	svid;
 *		netobj	oh;
 *		uपूर्णांक64	l_offset;
 *		uपूर्णांक64	l_len;
 *	पूर्ण;
 */
अटल व्योम encode_nlm4_holder(काष्ठा xdr_stream *xdr,
			       स्थिर काष्ठा nlm_res *result)
अणु
	स्थिर काष्ठा nlm_lock *lock = &result->lock;
	u64 l_offset, l_len;
	__be32 *p;

	encode_bool(xdr, lock->fl.fl_type == F_RDLCK);
	encode_पूर्णांक32(xdr, lock->svid);
	encode_netobj(xdr, lock->oh.data, lock->oh.len);

	p = xdr_reserve_space(xdr, 4 + 4);
	nlm4_compute_offsets(lock, &l_offset, &l_len);
	p = xdr_encode_hyper(p, l_offset);
	xdr_encode_hyper(p, l_len);
पूर्ण

अटल पूर्णांक decode_nlm4_holder(काष्ठा xdr_stream *xdr, काष्ठा nlm_res *result)
अणु
	काष्ठा nlm_lock *lock = &result->lock;
	काष्ठा file_lock *fl = &lock->fl;
	u64 l_offset, l_len;
	u32 exclusive;
	पूर्णांक error;
	__be32 *p;
	s32 end;

	स_रखो(lock, 0, माप(*lock));
	locks_init_lock(fl);

	p = xdr_अंतरभूत_decode(xdr, 4 + 4);
	अगर (unlikely(p == शून्य))
		जाओ out_overflow;
	exclusive = be32_to_cpup(p++);
	lock->svid = be32_to_cpup(p);
	fl->fl_pid = (pid_t)lock->svid;

	error = decode_netobj(xdr, &lock->oh);
	अगर (unlikely(error))
		जाओ out;

	p = xdr_अंतरभूत_decode(xdr, 8 + 8);
	अगर (unlikely(p == शून्य))
		जाओ out_overflow;

	fl->fl_flags = FL_POSIX;
	fl->fl_type  = exclusive != 0 ? F_WRLCK : F_RDLCK;
	p = xdr_decode_hyper(p, &l_offset);
	xdr_decode_hyper(p, &l_len);
	end = l_offset + l_len - 1;

	fl->fl_start = (loff_t)l_offset;
	अगर (l_len == 0 || end < 0)
		fl->fl_end = OFFSET_MAX;
	अन्यथा
		fl->fl_end = (loff_t)end;
	error = 0;
out:
	वापस error;
out_overflow:
	वापस -EIO;
पूर्ण

/*
 *	string caller_name<LM_MAXSTRLEN>;
 */
अटल व्योम encode_caller_name(काष्ठा xdr_stream *xdr, स्थिर अक्षर *name)
अणु
	/* NB: client-side करोes not set lock->len */
	u32 length = म_माप(name);
	__be32 *p;

	p = xdr_reserve_space(xdr, 4 + length);
	xdr_encode_opaque(p, name, length);
पूर्ण

/*
 *	काष्ठा nlm4_lock अणु
 *		string	caller_name<LM_MAXSTRLEN>;
 *		netobj	fh;
 *		netobj	oh;
 *		पूर्णांक32	svid;
 *		uपूर्णांक64	l_offset;
 *		uपूर्णांक64	l_len;
 *	पूर्ण;
 */
अटल व्योम encode_nlm4_lock(काष्ठा xdr_stream *xdr,
			     स्थिर काष्ठा nlm_lock *lock)
अणु
	u64 l_offset, l_len;
	__be32 *p;

	encode_caller_name(xdr, lock->caller);
	encode_fh(xdr, &lock->fh);
	encode_netobj(xdr, lock->oh.data, lock->oh.len);

	p = xdr_reserve_space(xdr, 4 + 8 + 8);
	*p++ = cpu_to_be32(lock->svid);

	nlm4_compute_offsets(lock, &l_offset, &l_len);
	p = xdr_encode_hyper(p, l_offset);
	xdr_encode_hyper(p, l_len);
पूर्ण


/*
 * NLMv4 XDR encode functions
 *
 * NLMv4 argument types are defined in Appendix II of RFC 1813:
 * "NFS Version 3 Protocol Specification" and Chapter 10 of X/Open's
 * "Protocols for Interworking: XNFS, Version 3W".
 */

/*
 *	काष्ठा nlm4_testargs अणु
 *		netobj cookie;
 *		bool exclusive;
 *		काष्ठा nlm4_lock alock;
 *	पूर्ण;
 */
अटल व्योम nlm4_xdr_enc_testargs(काष्ठा rpc_rqst *req,
				  काष्ठा xdr_stream *xdr,
				  स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nlm_args *args = data;
	स्थिर काष्ठा nlm_lock *lock = &args->lock;

	encode_cookie(xdr, &args->cookie);
	encode_bool(xdr, lock->fl.fl_type == F_WRLCK);
	encode_nlm4_lock(xdr, lock);
पूर्ण

/*
 *	काष्ठा nlm4_lockargs अणु
 *		netobj cookie;
 *		bool block;
 *		bool exclusive;
 *		काष्ठा nlm4_lock alock;
 *		bool reclaim;
 *		पूर्णांक state;
 *	पूर्ण;
 */
अटल व्योम nlm4_xdr_enc_lockargs(काष्ठा rpc_rqst *req,
				  काष्ठा xdr_stream *xdr,
				  स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nlm_args *args = data;
	स्थिर काष्ठा nlm_lock *lock = &args->lock;

	encode_cookie(xdr, &args->cookie);
	encode_bool(xdr, args->block);
	encode_bool(xdr, lock->fl.fl_type == F_WRLCK);
	encode_nlm4_lock(xdr, lock);
	encode_bool(xdr, args->reclaim);
	encode_पूर्णांक32(xdr, args->state);
पूर्ण

/*
 *	काष्ठा nlm4_cancargs अणु
 *		netobj cookie;
 *		bool block;
 *		bool exclusive;
 *		काष्ठा nlm4_lock alock;
 *	पूर्ण;
 */
अटल व्योम nlm4_xdr_enc_cancargs(काष्ठा rpc_rqst *req,
				  काष्ठा xdr_stream *xdr,
				  स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nlm_args *args = data;
	स्थिर काष्ठा nlm_lock *lock = &args->lock;

	encode_cookie(xdr, &args->cookie);
	encode_bool(xdr, args->block);
	encode_bool(xdr, lock->fl.fl_type == F_WRLCK);
	encode_nlm4_lock(xdr, lock);
पूर्ण

/*
 *	काष्ठा nlm4_unlockargs अणु
 *		netobj cookie;
 *		काष्ठा nlm4_lock alock;
 *	पूर्ण;
 */
अटल व्योम nlm4_xdr_enc_unlockargs(काष्ठा rpc_rqst *req,
				    काष्ठा xdr_stream *xdr,
				    स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nlm_args *args = data;
	स्थिर काष्ठा nlm_lock *lock = &args->lock;

	encode_cookie(xdr, &args->cookie);
	encode_nlm4_lock(xdr, lock);
पूर्ण

/*
 *	काष्ठा nlm4_res अणु
 *		netobj cookie;
 *		nlm4_stat stat;
 *	पूर्ण;
 */
अटल व्योम nlm4_xdr_enc_res(काष्ठा rpc_rqst *req,
			     काष्ठा xdr_stream *xdr,
			     स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nlm_res *result = data;

	encode_cookie(xdr, &result->cookie);
	encode_nlm4_stat(xdr, result->status);
पूर्ण

/*
 *	जोड़ nlm4_testrply चयन (nlm4_stats stat) अणु
 *	हाल NLM4_DENIED:
 *		काष्ठा nlm4_holder holder;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 *
 *	काष्ठा nlm4_testres अणु
 *		netobj cookie;
 *		nlm4_testrply test_stat;
 *	पूर्ण;
 */
अटल व्योम nlm4_xdr_enc_testres(काष्ठा rpc_rqst *req,
				 काष्ठा xdr_stream *xdr,
				 स्थिर व्योम *data)
अणु
	स्थिर काष्ठा nlm_res *result = data;

	encode_cookie(xdr, &result->cookie);
	encode_nlm4_stat(xdr, result->status);
	अगर (result->status == nlm_lck_denied)
		encode_nlm4_holder(xdr, result);
पूर्ण


/*
 * NLMv4 XDR decode functions
 *
 * NLMv4 argument types are defined in Appendix II of RFC 1813:
 * "NFS Version 3 Protocol Specification" and Chapter 10 of X/Open's
 * "Protocols for Interworking: XNFS, Version 3W".
 */

/*
 *	जोड़ nlm4_testrply चयन (nlm4_stats stat) अणु
 *	हाल NLM4_DENIED:
 *		काष्ठा nlm4_holder holder;
 *	शेष:
 *		व्योम;
 *	पूर्ण;
 *
 *	काष्ठा nlm4_testres अणु
 *		netobj cookie;
 *		nlm4_testrply test_stat;
 *	पूर्ण;
 */
अटल पूर्णांक decode_nlm4_testrply(काष्ठा xdr_stream *xdr,
				काष्ठा nlm_res *result)
अणु
	पूर्णांक error;

	error = decode_nlm4_stat(xdr, &result->status);
	अगर (unlikely(error))
		जाओ out;
	अगर (result->status == nlm_lck_denied)
		error = decode_nlm4_holder(xdr, result);
out:
	वापस error;
पूर्ण

अटल पूर्णांक nlm4_xdr_dec_testres(काष्ठा rpc_rqst *req,
				काष्ठा xdr_stream *xdr,
				व्योम *data)
अणु
	काष्ठा nlm_res *result = data;
	पूर्णांक error;

	error = decode_cookie(xdr, &result->cookie);
	अगर (unlikely(error))
		जाओ out;
	error = decode_nlm4_testrply(xdr, result);
out:
	वापस error;
पूर्ण

/*
 *	काष्ठा nlm4_res अणु
 *		netobj cookie;
 *		nlm4_stat stat;
 *	पूर्ण;
 */
अटल पूर्णांक nlm4_xdr_dec_res(काष्ठा rpc_rqst *req,
			    काष्ठा xdr_stream *xdr,
			    व्योम *data)
अणु
	काष्ठा nlm_res *result = data;
	पूर्णांक error;

	error = decode_cookie(xdr, &result->cookie);
	अगर (unlikely(error))
		जाओ out;
	error = decode_nlm4_stat(xdr, &result->status);
out:
	वापस error;
पूर्ण


/*
 * For NLM, a व्योम procedure really वापसs nothing
 */
#घोषणा nlm4_xdr_dec_norep	शून्य

#घोषणा PROC(proc, argtype, restype)					\
[NLMPROC_##proc] = अणु							\
	.p_proc      = NLMPROC_##proc,					\
	.p_encode    = nlm4_xdr_enc_##argtype,				\
	.p_decode    = nlm4_xdr_dec_##restype,				\
	.p_arglen    = NLM4_##argtype##_sz,				\
	.p_replen    = NLM4_##restype##_sz,				\
	.p_statidx   = NLMPROC_##proc,					\
	.p_name      = #proc,						\
	पूर्ण

अटल स्थिर काष्ठा rpc_procinfo nlm4_procedures[] = अणु
	PROC(TEST,		testargs,	testres),
	PROC(LOCK,		lockargs,	res),
	PROC(CANCEL,		cancargs,	res),
	PROC(UNLOCK,		unlockargs,	res),
	PROC(GRANTED,		testargs,	res),
	PROC(TEST_MSG,		testargs,	norep),
	PROC(LOCK_MSG,		lockargs,	norep),
	PROC(CANCEL_MSG,	cancargs,	norep),
	PROC(UNLOCK_MSG,	unlockargs,	norep),
	PROC(GRANTED_MSG,	testargs,	norep),
	PROC(TEST_RES,		testres,	norep),
	PROC(LOCK_RES,		res,		norep),
	PROC(CANCEL_RES,	res,		norep),
	PROC(UNLOCK_RES,	res,		norep),
	PROC(GRANTED_RES,	res,		norep),
पूर्ण;

अटल अचिन्हित पूर्णांक nlm_version4_counts[ARRAY_SIZE(nlm4_procedures)];
स्थिर काष्ठा rpc_version nlm_version4 = अणु
	.number		= 4,
	.nrprocs	= ARRAY_SIZE(nlm4_procedures),
	.procs		= nlm4_procedures,
	.counts		= nlm_version4_counts,
पूर्ण;
