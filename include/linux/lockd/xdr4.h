<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/lockd/xdr4.h
 *
 * XDR types क्रम the NLM protocol
 *
 * Copyright (C) 1996 Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित LOCKD_XDR4_H
#घोषणा LOCKD_XDR4_H

#समावेश <linux/fs.h>
#समावेश <linux/nfs.h>
#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/lockd/xdr.h>

/* error codes new to NLMv4 */
#घोषणा	nlm4_deadlock		cpu_to_be32(NLM_DEADLCK)
#घोषणा	nlm4_rofs		cpu_to_be32(NLM_ROFS)
#घोषणा	nlm4_stale_fh		cpu_to_be32(NLM_STALE_FH)
#घोषणा	nlm4_fbig		cpu_to_be32(NLM_FBIG)
#घोषणा	nlm4_failed		cpu_to_be32(NLM_FAILED)



पूर्णांक	nlm4svc_decode_testargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlm4svc_encode_testres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlm4svc_decode_lockargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlm4svc_decode_cancargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlm4svc_decode_unlockargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlm4svc_encode_res(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlm4svc_decode_res(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlm4svc_encode_व्योम(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlm4svc_decode_व्योम(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlm4svc_decode_shareargs(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlm4svc_encode_shareres(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlm4svc_decode_notअगरy(काष्ठा svc_rqst *, __be32 *);
पूर्णांक	nlm4svc_decode_reboot(काष्ठा svc_rqst *, __be32 *);
/*
पूर्णांक	nlmclt_encode_testargs(काष्ठा rpc_rqst *, u32 *, काष्ठा nlm_args *);
पूर्णांक	nlmclt_encode_lockargs(काष्ठा rpc_rqst *, u32 *, काष्ठा nlm_args *);
पूर्णांक	nlmclt_encode_cancargs(काष्ठा rpc_rqst *, u32 *, काष्ठा nlm_args *);
पूर्णांक	nlmclt_encode_unlockargs(काष्ठा rpc_rqst *, u32 *, काष्ठा nlm_args *);
 */
बाह्य स्थिर काष्ठा rpc_version nlm_version4;

#पूर्ण_अगर /* LOCKD_XDR4_H */
