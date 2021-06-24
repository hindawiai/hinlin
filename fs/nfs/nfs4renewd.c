<शैली गुरु>
/*
 *  fs/nfs/nfs4renewd.c
 *
 *  Copyright (c) 2002 The Regents of the University of Michigan.
 *  All rights reserved.
 *
 *  Kendrick Smith <kmsmith@umich.edu>
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
 *
 * Implementation of the NFSv4 "renew daemon", which wakes up periodically to
 * send a RENEW, to keep state alive on the server.  The daemon is implemented
 * as an rpc_task, not a real kernel thपढ़ो, so it always runs in rpciod's
 * context.  There is one renewd per nfs_server.
 *
 */

#समावेश <linux/mm.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/sunrpc/sched.h>
#समावेश <linux/sunrpc/clnt.h>

#समावेश <linux/nfs.h>
#समावेश <linux/nfs4.h>
#समावेश <linux/nfs_fs.h>
#समावेश "nfs4_fs.h"
#समावेश "delegation.h"

#घोषणा NFSDBG_FACILITY		NFSDBG_STATE

व्योम
nfs4_renew_state(काष्ठा work_काष्ठा *work)
अणु
	स्थिर काष्ठा nfs4_state_मुख्यtenance_ops *ops;
	काष्ठा nfs_client *clp =
		container_of(work, काष्ठा nfs_client, cl_renewd.work);
	स्थिर काष्ठा cred *cred;
	दीर्घ lease;
	अचिन्हित दीर्घ last, now;
	अचिन्हित renew_flags = 0;

	ops = clp->cl_mvops->state_renewal_ops;
	dprपूर्णांकk("%s: start\n", __func__);

	अगर (test_bit(NFS_CS_STOP_RENEW, &clp->cl_res_state))
		जाओ out;

	lease = clp->cl_lease_समय;
	last = clp->cl_last_renewal;
	now = jअगरfies;
	/* Are we बंद to a lease समयout? */
	अगर (समय_after(now, last + lease/3))
		renew_flags |= NFS4_RENEW_TIMEOUT;
	अगर (nfs_delegations_present(clp))
		renew_flags |= NFS4_RENEW_DELEGATION_CB;

	अगर (renew_flags != 0) अणु
		cred = ops->get_state_renewal_cred(clp);
		अगर (cred == शून्य) अणु
			अगर (!(renew_flags & NFS4_RENEW_DELEGATION_CB)) अणु
				set_bit(NFS4CLNT_LEASE_EXPIRED, &clp->cl_state);
				जाओ out;
			पूर्ण
			nfs_expire_all_delegations(clp);
		पूर्ण अन्यथा अणु
			पूर्णांक ret;

			/* Queue an asynchronous RENEW. */
			ret = ops->sched_state_renewal(clp, cred, renew_flags);
			put_cred(cred);
			चयन (ret) अणु
			शेष:
				जाओ out_exp;
			हाल -EAGAIN:
			हाल -ENOMEM:
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		dprपूर्णांकk("%s: failed to call renewd. Reason: lease not expired \n",
				__func__);
	पूर्ण
	nfs4_schedule_state_renewal(clp);
out_exp:
	nfs_expire_unreferenced_delegations(clp);
out:
	dprपूर्णांकk("%s: done\n", __func__);
पूर्ण

व्योम
nfs4_schedule_state_renewal(काष्ठा nfs_client *clp)
अणु
	दीर्घ समयout;

	spin_lock(&clp->cl_lock);
	समयout = (2 * clp->cl_lease_समय) / 3 + (दीर्घ)clp->cl_last_renewal
		- (दीर्घ)jअगरfies;
	अगर (समयout < 5 * HZ)
		समयout = 5 * HZ;
	dprपूर्णांकk("%s: requeueing work. Lease period = %ld\n",
			__func__, (समयout + HZ - 1) / HZ);
	mod_delayed_work(प्रणाली_wq, &clp->cl_renewd, समयout);
	set_bit(NFS_CS_RENEWD, &clp->cl_res_state);
	spin_unlock(&clp->cl_lock);
पूर्ण

व्योम
nfs4_समाप्त_renewd(काष्ठा nfs_client *clp)
अणु
	cancel_delayed_work_sync(&clp->cl_renewd);
पूर्ण

/**
 * nfs4_set_lease_period - Sets the lease period on a nfs_client
 *
 * @clp: poपूर्णांकer to nfs_client
 * @lease: new value क्रम lease period
 */
व्योम nfs4_set_lease_period(काष्ठा nfs_client *clp,
		अचिन्हित दीर्घ lease)
अणु
	spin_lock(&clp->cl_lock);
	clp->cl_lease_समय = lease;
	spin_unlock(&clp->cl_lock);

	/* Cap maximum reconnect समयout at 1/2 lease period */
	rpc_set_connect_समयout(clp->cl_rpcclient, lease, lease >> 1);
पूर्ण
