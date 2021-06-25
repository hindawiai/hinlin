<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/fs/lockd/xdr.c
 *
 * XDR support क्रम lockd and the lock client.
 *
 * Copyright (C) 1995, 1996 Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/types.h>
#समावेश <linux/sched.h>
#समावेश <linux/nfs.h>

#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/clnt.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/sunrpc/stats.h>
#समावेश <linux/lockd/lockd.h>

#समावेश <uapi/linux/nfs2.h>

#घोषणा NLMDBG_FACILITY		NLMDBG_XDR


अटल अंतरभूत loff_t
s32_to_loff_t(__s32 offset)
अणु
	वापस (loff_t)offset;
पूर्ण

अटल अंतरभूत __s32
loff_t_to_s32(loff_t offset)
अणु
	__s32 res;
	अगर (offset >= NLM_OFFSET_MAX)
		res = NLM_OFFSET_MAX;
	अन्यथा अगर (offset <= -NLM_OFFSET_MAX)
		res = -NLM_OFFSET_MAX;
	अन्यथा
		res = offset;
	वापस res;
पूर्ण

/*
 * XDR functions क्रम basic NLM types
 */
अटल __be32 *nlm_decode_cookie(__be32 *p, काष्ठा nlm_cookie *c)
अणु
	अचिन्हित पूर्णांक	len;

	len = ntohl(*p++);
	
	अगर(len==0)
	अणु
		c->len=4;
		स_रखो(c->data, 0, 4);	/* hockeypux brain damage */
	पूर्ण
	अन्यथा अगर(len<=NLM_MAXCOOKIELEN)
	अणु
		c->len=len;
		स_नकल(c->data, p, len);
		p+=XDR_QUADLEN(len);
	पूर्ण
	अन्यथा 
	अणु
		dprपूर्णांकk("lockd: bad cookie size %d (only cookies under "
			"%d bytes are supported.)\n",
				len, NLM_MAXCOOKIELEN);
		वापस शून्य;
	पूर्ण
	वापस p;
पूर्ण

अटल अंतरभूत __be32 *
nlm_encode_cookie(__be32 *p, काष्ठा nlm_cookie *c)
अणु
	*p++ = htonl(c->len);
	स_नकल(p, c->data, c->len);
	p+=XDR_QUADLEN(c->len);
	वापस p;
पूर्ण

अटल __be32 *
nlm_decode_fh(__be32 *p, काष्ठा nfs_fh *f)
अणु
	अचिन्हित पूर्णांक	len;

	अगर ((len = ntohl(*p++)) != NFS2_FHSIZE) अणु
		dprपूर्णांकk("lockd: bad fhandle size %d (should be %d)\n",
			len, NFS2_FHSIZE);
		वापस शून्य;
	पूर्ण
	f->size = NFS2_FHSIZE;
	स_रखो(f->data, 0, माप(f->data));
	स_नकल(f->data, p, NFS2_FHSIZE);
	वापस p + XDR_QUADLEN(NFS2_FHSIZE);
पूर्ण

/*
 * Encode and decode owner handle
 */
अटल अंतरभूत __be32 *
nlm_decode_oh(__be32 *p, काष्ठा xdr_netobj *oh)
अणु
	वापस xdr_decode_netobj(p, oh);
पूर्ण

अटल अंतरभूत __be32 *
nlm_encode_oh(__be32 *p, काष्ठा xdr_netobj *oh)
अणु
	वापस xdr_encode_netobj(p, oh);
पूर्ण

अटल __be32 *
nlm_decode_lock(__be32 *p, काष्ठा nlm_lock *lock)
अणु
	काष्ठा file_lock	*fl = &lock->fl;
	s32			start, len, end;

	अगर (!(p = xdr_decode_string_inplace(p, &lock->caller,
					    &lock->len,
					    NLM_MAXSTRLEN))
	 || !(p = nlm_decode_fh(p, &lock->fh))
	 || !(p = nlm_decode_oh(p, &lock->oh)))
		वापस शून्य;
	lock->svid  = ntohl(*p++);

	locks_init_lock(fl);
	fl->fl_flags = FL_POSIX;
	fl->fl_type  = F_RDLCK;		/* as good as anything अन्यथा */
	start = ntohl(*p++);
	len = ntohl(*p++);
	end = start + len - 1;

	fl->fl_start = s32_to_loff_t(start);

	अगर (len == 0 || end < 0)
		fl->fl_end = OFFSET_MAX;
	अन्यथा
		fl->fl_end = s32_to_loff_t(end);
	वापस p;
पूर्ण

/*
 * Encode result of a TEST/TEST_MSG call
 */
अटल __be32 *
nlm_encode_testres(__be32 *p, काष्ठा nlm_res *resp)
अणु
	s32		start, len;

	अगर (!(p = nlm_encode_cookie(p, &resp->cookie)))
		वापस शून्य;
	*p++ = resp->status;

	अगर (resp->status == nlm_lck_denied) अणु
		काष्ठा file_lock	*fl = &resp->lock.fl;

		*p++ = (fl->fl_type == F_RDLCK)? xdr_zero : xdr_one;
		*p++ = htonl(resp->lock.svid);

		/* Encode owner handle. */
		अगर (!(p = xdr_encode_netobj(p, &resp->lock.oh)))
			वापस शून्य;

		start = loff_t_to_s32(fl->fl_start);
		अगर (fl->fl_end == OFFSET_MAX)
			len = 0;
		अन्यथा
			len = loff_t_to_s32(fl->fl_end - fl->fl_start + 1);

		*p++ = htonl(start);
		*p++ = htonl(len);
	पूर्ण

	वापस p;
पूर्ण


/*
 * First, the server side XDR functions
 */
पूर्णांक
nlmsvc_decode_testargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;
	u32	exclusive;

	अगर (!(p = nlm_decode_cookie(p, &argp->cookie)))
		वापस 0;

	exclusive = ntohl(*p++);
	अगर (!(p = nlm_decode_lock(p, &argp->lock)))
		वापस 0;
	अगर (exclusive)
		argp->lock.fl.fl_type = F_WRLCK;

	वापस xdr_argsize_check(rqstp, p);
पूर्ण

पूर्णांक
nlmsvc_encode_testres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा nlm_res *resp = rqstp->rq_resp;

	अगर (!(p = nlm_encode_testres(p, resp)))
		वापस 0;
	वापस xdr_ressize_check(rqstp, p);
पूर्ण

पूर्णांक
nlmsvc_decode_lockargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;
	u32	exclusive;

	अगर (!(p = nlm_decode_cookie(p, &argp->cookie)))
		वापस 0;
	argp->block  = ntohl(*p++);
	exclusive    = ntohl(*p++);
	अगर (!(p = nlm_decode_lock(p, &argp->lock)))
		वापस 0;
	अगर (exclusive)
		argp->lock.fl.fl_type = F_WRLCK;
	argp->reclaim = ntohl(*p++);
	argp->state   = ntohl(*p++);
	argp->monitor = 1;		/* monitor client by शेष */

	वापस xdr_argsize_check(rqstp, p);
पूर्ण

पूर्णांक
nlmsvc_decode_cancargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;
	u32	exclusive;

	अगर (!(p = nlm_decode_cookie(p, &argp->cookie)))
		वापस 0;
	argp->block = ntohl(*p++);
	exclusive = ntohl(*p++);
	अगर (!(p = nlm_decode_lock(p, &argp->lock)))
		वापस 0;
	अगर (exclusive)
		argp->lock.fl.fl_type = F_WRLCK;
	वापस xdr_argsize_check(rqstp, p);
पूर्ण

पूर्णांक
nlmsvc_decode_unlockargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;

	अगर (!(p = nlm_decode_cookie(p, &argp->cookie))
	 || !(p = nlm_decode_lock(p, &argp->lock)))
		वापस 0;
	argp->lock.fl.fl_type = F_UNLCK;
	वापस xdr_argsize_check(rqstp, p);
पूर्ण

पूर्णांक
nlmsvc_decode_shareargs(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;
	काष्ठा nlm_lock	*lock = &argp->lock;

	स_रखो(lock, 0, माप(*lock));
	locks_init_lock(&lock->fl);
	lock->svid = ~(u32) 0;

	अगर (!(p = nlm_decode_cookie(p, &argp->cookie))
	 || !(p = xdr_decode_string_inplace(p, &lock->caller,
					    &lock->len, NLM_MAXSTRLEN))
	 || !(p = nlm_decode_fh(p, &lock->fh))
	 || !(p = nlm_decode_oh(p, &lock->oh)))
		वापस 0;
	argp->fsm_mode = ntohl(*p++);
	argp->fsm_access = ntohl(*p++);
	वापस xdr_argsize_check(rqstp, p);
पूर्ण

पूर्णांक
nlmsvc_encode_shareres(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा nlm_res *resp = rqstp->rq_resp;

	अगर (!(p = nlm_encode_cookie(p, &resp->cookie)))
		वापस 0;
	*p++ = resp->status;
	*p++ = xdr_zero;		/* sequence argument */
	वापस xdr_ressize_check(rqstp, p);
पूर्ण

पूर्णांक
nlmsvc_encode_res(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा nlm_res *resp = rqstp->rq_resp;

	अगर (!(p = nlm_encode_cookie(p, &resp->cookie)))
		वापस 0;
	*p++ = resp->status;
	वापस xdr_ressize_check(rqstp, p);
पूर्ण

पूर्णांक
nlmsvc_decode_notअगरy(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा nlm_args *argp = rqstp->rq_argp;
	काष्ठा nlm_lock	*lock = &argp->lock;

	अगर (!(p = xdr_decode_string_inplace(p, &lock->caller,
					    &lock->len, NLM_MAXSTRLEN)))
		वापस 0;
	argp->state = ntohl(*p++);
	वापस xdr_argsize_check(rqstp, p);
पूर्ण

पूर्णांक
nlmsvc_decode_reboot(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा nlm_reboot *argp = rqstp->rq_argp;

	अगर (!(p = xdr_decode_string_inplace(p, &argp->mon, &argp->len, SM_MAXSTRLEN)))
		वापस 0;
	argp->state = ntohl(*p++);
	स_नकल(&argp->priv.data, p, माप(argp->priv.data));
	p += XDR_QUADLEN(SM_PRIV_SIZE);
	वापस xdr_argsize_check(rqstp, p);
पूर्ण

पूर्णांक
nlmsvc_decode_res(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	काष्ठा nlm_res *resp = rqstp->rq_argp;

	अगर (!(p = nlm_decode_cookie(p, &resp->cookie)))
		वापस 0;
	resp->status = *p++;
	वापस xdr_argsize_check(rqstp, p);
पूर्ण

पूर्णांक
nlmsvc_decode_व्योम(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	वापस xdr_argsize_check(rqstp, p);
पूर्ण

पूर्णांक
nlmsvc_encode_व्योम(काष्ठा svc_rqst *rqstp, __be32 *p)
अणु
	वापस xdr_ressize_check(rqstp, p);
पूर्ण
