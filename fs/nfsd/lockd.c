<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * This file contains all the stubs needed when communicating with lockd.
 * This level of indirection is necessary so we can run nfsd+lockd without
 * requiring the nfs client to be compiled in/loaded, and vice versa.
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#समावेश <linux/file.h>
#समावेश <linux/lockd/bind.h>
#समावेश "nfsd.h"
#समावेश "vfs.h"

#घोषणा NFSDDBG_FACILITY		NFSDDBG_LOCKD

#अगर_घोषित CONFIG_LOCKD_V4
#घोषणा nlm_stale_fh	nlm4_stale_fh
#घोषणा nlm_failed	nlm4_failed
#अन्यथा
#घोषणा nlm_stale_fh	nlm_lck_denied_nolocks
#घोषणा nlm_failed	nlm_lck_denied_nolocks
#पूर्ण_अगर
/*
 * Note: we hold the dentry use count जबतक the file is खोलो.
 */
अटल __be32
nlm_ख_खोलो(काष्ठा svc_rqst *rqstp, काष्ठा nfs_fh *f, काष्ठा file **filp)
अणु
	__be32		nfserr;
	काष्ठा svc_fh	fh;

	/* must initialize beक्रमe using! but maxsize करोesn't matter */
	fh_init(&fh,0);
	fh.fh_handle.fh_size = f->size;
	स_नकल((अक्षर*)&fh.fh_handle.fh_base, f->data, f->size);
	fh.fh_export = शून्य;

	nfserr = nfsd_खोलो(rqstp, &fh, S_IFREG, NFSD_MAY_LOCK, filp);
	fh_put(&fh);
 	/* We वापस nlm error codes as nlm करोesn't know
	 * about nfsd, but nfsd करोes know about nlm..
	 */
	चयन (nfserr) अणु
	हाल nfs_ok:
		वापस 0;
	हाल nfserr_dropit:
		वापस nlm_drop_reply;
	हाल nfserr_stale:
		वापस nlm_stale_fh;
	शेष:
		वापस nlm_failed;
	पूर्ण
पूर्ण

अटल व्योम
nlm_ख_बंद(काष्ठा file *filp)
अणु
	fput(filp);
पूर्ण

अटल स्थिर काष्ठा nlmsvc_binding nfsd_nlm_ops = अणु
	.ख_खोलो		= nlm_ख_खोलो,		/* खोलो file क्रम locking */
	.ख_बंद		= nlm_ख_बंद,		/* बंद file */
पूर्ण;

व्योम
nfsd_lockd_init(व्योम)
अणु
	dprपूर्णांकk("nfsd: initializing lockd\n");
	nlmsvc_ops = &nfsd_nlm_ops;
पूर्ण

व्योम
nfsd_lockd_shutकरोwn(व्योम)
अणु
	nlmsvc_ops = शून्य;
पूर्ण
