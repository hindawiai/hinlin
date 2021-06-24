<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/lockd/xdr.h
 *
 * XDR types क्रम the NLM protocol
 *
 * Copyright (C) 1996 Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित LOCKD_XDR_H
#घोषणा LOCKD_XDR_H

#समावेश <linux/fs.h>
#समावेश <linux/nfs.h>
#समावेश <linux/sunrpc/xdr.h>

#घोषणा SM_MAXSTRLEN		1024
#घोषणा SM_PRIV_SIZE		16

काष्ठा nsm_निजी अणु
	अचिन्हित अक्षर		data[SM_PRIV_SIZE];
पूर्ण;

काष्ठा svc_rqst;

#घोषणा NLM_MAXCOOKIELEN    	32
#घोषणा NLM_MAXSTRLEN		1024

#घोषणा	nlm_granted		cpu_to_be32(NLM_LCK_GRANTED)
#घोषणा	nlm_lck_denied		cpu_to_be32(NLM_LCK_DENIED)
#घोषणा	nlm_lck_denied_nolocks	cpu_to_be32(NLM_LCK_DENIED_NOLOCKS)
#घोषणा	nlm_lck_blocked		cpu_to_be32(NLM_LCK_BLOCKED)
#घोषणा	nlm_lck_denied_grace_period	cpu_to_be32(NLM_LCK_DENIED_GRACE_PERIOD)

#घोषणा nlm_drop_reply		cpu_to_be32(30000)

/* Lock info passed via NLM */
काष्ठा nlm_lock अणु
	अक्षर *			caller;
	अचिन्हित पूर्णांक		len; 	/* length of "caller" */
	काष्ठा nfs_fh		fh;
	काष्ठा xdr_netobj	oh;
	u32			svid;
	काष्ठा file_lock	fl;
पूर्ण;

/*
 *	NLM cookies. Technically they can be 1K, but Linux only uses 8 bytes.
 *	FreeBSD uses 16, Apple Mac OS X 10.3 uses 20. Thereक्रमe we set it to
 *	32 bytes.
 */
 
काष्ठा nlm_cookie
अणु
	अचिन्हित अक्षर data[NLM_MAXCOOKIELEN];
	अचिन्हित पूर्णांक len;
पूर्ण;

/*
 * Generic lockd arguments क्रम all but sm_notअगरy
 */
काष्ठा nlm_args अणु
	काष्ठा nlm_cookie	cookie;
	काष्ठा nlm_lock		lock;
	u32			block;
	u32			reclaim;
	u32			state;
	u32			monitor;
	u32			fsm_access;
	u32			fsm_mode;
पूर्ण;

प्रकार काष्ठा nlm_args nlm_args;

/*
 * Generic lockd result
 */
काष्ठा nlm_res अणु
	काष्ठा nlm_cookie	cookie;
	__be32			status;
	काष्ठा nlm_lock		lock;
पूर्ण;

/*
 * statd callback when client has rebooted
 */
काष्ठा nlm_reboot अणु
	अक्षर			*mon;
	अचिन्हित पूर्णांक		len;
	u32			state;
	काष्ठा nsm_निजी	priv;
पूर्ण;

/*
 * Contents of statd callback when monitored host rebooted
 */
#घोषणा NLMSVC_XDRSIZE		माप(काष्ठा nlm_args)

पूर्णांक	nlmsvc_decode_testargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlmsvc_encode_testres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlmsvc_decode_lockargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlmsvc_decode_cancargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlmsvc_decode_unlockargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlmsvc_encode_res(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlmsvc_decode_res(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlmsvc_encode_व्योम(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlmsvc_decode_व्योम(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlmsvc_decode_shareargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlmsvc_encode_shareres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlmsvc_decode_notअगरy(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlmsvc_decode_reboot(काष्ठा svc_rqst *, __be32 *);
/*
पूर्णांक	nlmclt_encode_testargs(काष्ठा rpc_rqst *, u32 *, काष्ठा nlm_args *);
पूर्णांक	nlmclt_encode_lockargs(काष्ठा rpc_rqst *, u32 *, काष्ठा nlm_args *);
पूर्णांक	nlmclt_encode_cancargs(काष्ठा rpc_rqst *, u32 *, काष्ठा nlm_args *);
पूर्णांक	nlmclt_encode_unlockargs(काष्ठा rpc_rqst *, u32 *, काष्ठा nlm_args *);
 */

#पूर्ण_अगर /* LOCKD_XDR_H */
