<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/lockd/bind.h
 *
 * This is the part of lockd visible to nfsd and the nfs client.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित LINUX_LOCKD_BIND_H
#घोषणा LINUX_LOCKD_BIND_H

#समावेश <linux/lockd/nlm.h>
/* need xdr-encoded error codes too, so... */
#समावेश <linux/lockd/xdr.h>
#अगर_घोषित CONFIG_LOCKD_V4
#समावेश <linux/lockd/xdr4.h>
#पूर्ण_अगर

/* Dummy declarations */
काष्ठा svc_rqst;
काष्ठा rpc_task;

/*
 * This is the set of functions क्रम lockd->nfsd communication
 */
काष्ठा nlmsvc_binding अणु
	__be32			(*ख_खोलो)(काष्ठा svc_rqst *,
						काष्ठा nfs_fh *,
						काष्ठा file **);
	व्योम			(*ख_बंद)(काष्ठा file *);
पूर्ण;

बाह्य स्थिर काष्ठा nlmsvc_binding *nlmsvc_ops;

/*
 * Similar to nfs_client_initdata, but without the NFS-specअगरic
 * rpc_ops field.
 */
काष्ठा nlmclnt_initdata अणु
	स्थिर अक्षर		*hostname;
	स्थिर काष्ठा sockaddr	*address;
	माप_प्रकार			addrlen;
	अचिन्हित लघु		protocol;
	u32			nfs_version;
	पूर्णांक			noresvport;
	काष्ठा net		*net;
	स्थिर काष्ठा nlmclnt_operations	*nlmclnt_ops;
	स्थिर काष्ठा cred	*cred;
पूर्ण;

/*
 * Functions exported by the lockd module
 */

बाह्य काष्ठा nlm_host *nlmclnt_init(स्थिर काष्ठा nlmclnt_initdata *nlm_init);
बाह्य व्योम	nlmclnt_करोne(काष्ठा nlm_host *host);

/*
 * NLM client operations provide a means to modअगरy RPC processing of NLM
 * requests.  Callbacks receive a poपूर्णांकer to data passed पूर्णांकo the call to
 * nlmclnt_proc().
 */
काष्ठा nlmclnt_operations अणु
	/* Called on successful allocation of nlm_rqst, use क्रम allocation or
	 * reference counting. */
	व्योम (*nlmclnt_alloc_call)(व्योम *);

	/* Called in rpc_task_prepare क्रम unlock.  A वापस value of true
	 * indicates the callback has put the task to sleep on a रुकोqueue
	 * and NLM should not call rpc_call_start(). */
	bool (*nlmclnt_unlock_prepare)(काष्ठा rpc_task*, व्योम *);

	/* Called when the nlm_rqst is मुक्तd, callbacks should clean up here */
	व्योम (*nlmclnt_release_call)(व्योम *);
पूर्ण;

बाह्य पूर्णांक	nlmclnt_proc(काष्ठा nlm_host *host, पूर्णांक cmd, काष्ठा file_lock *fl, व्योम *data);
बाह्य पूर्णांक	lockd_up(काष्ठा net *net, स्थिर काष्ठा cred *cred);
बाह्य व्योम	lockd_करोwn(काष्ठा net *net);

#पूर्ण_अगर /* LINUX_LOCKD_BIND_H */
