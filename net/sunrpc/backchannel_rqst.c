<शैली गुरु>
/******************************************************************************

(c) 2007 Network Appliance, Inc.  All Rights Reserved.
(c) 2009 NetApp.  All Rights Reserved.

NetApp provides this source code under the GPL v2 License.
The GPL v2 license is available at
https://खोलोsource.org/licenses/gpl-license.php.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

******************************************************************************/

#समावेश <linux/tcp.h>
#समावेश <linux/slab.h>
#समावेश <linux/sunrpc/xprt.h>
#समावेश <linux/export.h>
#समावेश <linux/sunrpc/bc_xprt.h>

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
#घोषणा RPCDBG_FACILITY	RPCDBG_TRANS
#पूर्ण_अगर

#घोषणा BC_MAX_SLOTS	64U

अचिन्हित पूर्णांक xprt_bc_max_slots(काष्ठा rpc_xprt *xprt)
अणु
	वापस BC_MAX_SLOTS;
पूर्ण

/*
 * Helper routines that track the number of pपुनः_स्मृतिation elements
 * on the transport.
 */
अटल अंतरभूत पूर्णांक xprt_need_to_requeue(काष्ठा rpc_xprt *xprt)
अणु
	वापस xprt->bc_alloc_count < xprt->bc_alloc_max;
पूर्ण

/*
 * Free the pपुनः_स्मृतिated rpc_rqst काष्ठाure and the memory
 * buffers hanging off of it.
 */
अटल व्योम xprt_मुक्त_allocation(काष्ठा rpc_rqst *req)
अणु
	काष्ठा xdr_buf *xbufp;

	dprपूर्णांकk("RPC:        free allocations for req= %p\n", req);
	WARN_ON_ONCE(test_bit(RPC_BC_PA_IN_USE, &req->rq_bc_pa_state));
	xbufp = &req->rq_rcv_buf;
	मुक्त_page((अचिन्हित दीर्घ)xbufp->head[0].iov_base);
	xbufp = &req->rq_snd_buf;
	मुक्त_page((अचिन्हित दीर्घ)xbufp->head[0].iov_base);
	kमुक्त(req);
पूर्ण

अटल पूर्णांक xprt_alloc_xdr_buf(काष्ठा xdr_buf *buf, gfp_t gfp_flags)
अणु
	काष्ठा page *page;
	/* Pपुनः_स्मृतिate one XDR receive buffer */
	page = alloc_page(gfp_flags);
	अगर (page == शून्य)
		वापस -ENOMEM;
	xdr_buf_init(buf, page_address(page), PAGE_SIZE);
	वापस 0;
पूर्ण

अटल
काष्ठा rpc_rqst *xprt_alloc_bc_req(काष्ठा rpc_xprt *xprt, gfp_t gfp_flags)
अणु
	काष्ठा rpc_rqst *req;

	/* Pre-allocate one backchannel rpc_rqst */
	req = kzalloc(माप(*req), gfp_flags);
	अगर (req == शून्य)
		वापस शून्य;

	req->rq_xprt = xprt;
	INIT_LIST_HEAD(&req->rq_bc_list);

	/* Pपुनः_स्मृतिate one XDR receive buffer */
	अगर (xprt_alloc_xdr_buf(&req->rq_rcv_buf, gfp_flags) < 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to create bc receive xbuf\n");
		जाओ out_मुक्त;
	पूर्ण
	req->rq_rcv_buf.len = PAGE_SIZE;

	/* Pपुनः_स्मृतिate one XDR send buffer */
	अगर (xprt_alloc_xdr_buf(&req->rq_snd_buf, gfp_flags) < 0) अणु
		prपूर्णांकk(KERN_ERR "Failed to create bc snd xbuf\n");
		जाओ out_मुक्त;
	पूर्ण
	वापस req;
out_मुक्त:
	xprt_मुक्त_allocation(req);
	वापस शून्य;
पूर्ण

/*
 * Pपुनः_स्मृतिate up to min_reqs काष्ठाures and related buffers क्रम use
 * by the backchannel.  This function can be called multiple बार
 * when creating new sessions that use the same rpc_xprt.  The
 * pपुनः_स्मृतिated buffers are added to the pool of resources used by
 * the rpc_xprt.  Any one of these resources may be used by an
 * incoming callback request.  It's up to the higher levels in the
 * stack to enक्रमce that the maximum number of session slots is not
 * being exceeded.
 *
 * Some callback arguments can be large.  For example, a pNFS server
 * using multiple deviceids.  The list can be unbound, but the client
 * has the ability to tell the server the maximum size of the callback
 * requests.  Each deviceID is 16 bytes, so allocate one page
 * क्रम the arguments to have enough room to receive a number of these
 * deviceIDs.  The NFS client indicates to the pNFS server that its
 * callback requests can be up to 4096 bytes in size.
 */
पूर्णांक xprt_setup_backchannel(काष्ठा rpc_xprt *xprt, अचिन्हित पूर्णांक min_reqs)
अणु
	अगर (!xprt->ops->bc_setup)
		वापस 0;
	वापस xprt->ops->bc_setup(xprt, min_reqs);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_setup_backchannel);

पूर्णांक xprt_setup_bc(काष्ठा rpc_xprt *xprt, अचिन्हित पूर्णांक min_reqs)
अणु
	काष्ठा rpc_rqst *req;
	काष्ठा list_head पंचांगp_list;
	पूर्णांक i;

	dprपूर्णांकk("RPC:       setup backchannel transport\n");

	अगर (min_reqs > BC_MAX_SLOTS)
		min_reqs = BC_MAX_SLOTS;

	/*
	 * We use a temporary list to keep track of the pपुनः_स्मृतिated
	 * buffers.  Once we're करोne building the list we splice it
	 * पूर्णांकo the backchannel pपुनः_स्मृतिation list off of the rpc_xprt
	 * काष्ठा.  This helps minimize the amount of समय the list
	 * lock is held on the rpc_xprt काष्ठा.  It also makes cleanup
	 * easier in हाल of memory allocation errors.
	 */
	INIT_LIST_HEAD(&पंचांगp_list);
	क्रम (i = 0; i < min_reqs; i++) अणु
		/* Pre-allocate one backchannel rpc_rqst */
		req = xprt_alloc_bc_req(xprt, GFP_KERNEL);
		अगर (req == शून्य) अणु
			prपूर्णांकk(KERN_ERR "Failed to create bc rpc_rqst\n");
			जाओ out_मुक्त;
		पूर्ण

		/* Add the allocated buffer to the पंचांगp list */
		dprपूर्णांकk("RPC:       adding req= %p\n", req);
		list_add(&req->rq_bc_pa_list, &पंचांगp_list);
	पूर्ण

	/*
	 * Add the temporary list to the backchannel pपुनः_स्मृतिation list
	 */
	spin_lock(&xprt->bc_pa_lock);
	list_splice(&पंचांगp_list, &xprt->bc_pa_list);
	xprt->bc_alloc_count += min_reqs;
	xprt->bc_alloc_max += min_reqs;
	atomic_add(min_reqs, &xprt->bc_slot_count);
	spin_unlock(&xprt->bc_pa_lock);

	dprपूर्णांकk("RPC:       setup backchannel transport done\n");
	वापस 0;

out_मुक्त:
	/*
	 * Memory allocation failed, मुक्त the temporary list
	 */
	जबतक (!list_empty(&पंचांगp_list)) अणु
		req = list_first_entry(&पंचांगp_list,
				काष्ठा rpc_rqst,
				rq_bc_pa_list);
		list_del(&req->rq_bc_pa_list);
		xprt_मुक्त_allocation(req);
	पूर्ण

	dprपूर्णांकk("RPC:       setup backchannel transport failed\n");
	वापस -ENOMEM;
पूर्ण

/**
 * xprt_destroy_backchannel - Destroys the backchannel pपुनः_स्मृतिated काष्ठाures.
 * @xprt:	the transport holding the pपुनः_स्मृतिated strucures
 * @max_reqs:	the maximum number of pपुनः_स्मृतिated काष्ठाures to destroy
 *
 * Since these काष्ठाures may have been allocated by multiple calls
 * to xprt_setup_backchannel, we only destroy up to the maximum number
 * of reqs specअगरied by the caller.
 */
व्योम xprt_destroy_backchannel(काष्ठा rpc_xprt *xprt, अचिन्हित पूर्णांक max_reqs)
अणु
	अगर (xprt->ops->bc_destroy)
		xprt->ops->bc_destroy(xprt, max_reqs);
पूर्ण
EXPORT_SYMBOL_GPL(xprt_destroy_backchannel);

व्योम xprt_destroy_bc(काष्ठा rpc_xprt *xprt, अचिन्हित पूर्णांक max_reqs)
अणु
	काष्ठा rpc_rqst *req = शून्य, *पंचांगp = शून्य;

	dprपूर्णांकk("RPC:        destroy backchannel transport\n");

	अगर (max_reqs == 0)
		जाओ out;

	spin_lock_bh(&xprt->bc_pa_lock);
	xprt->bc_alloc_max -= min(max_reqs, xprt->bc_alloc_max);
	list_क्रम_each_entry_safe(req, पंचांगp, &xprt->bc_pa_list, rq_bc_pa_list) अणु
		dprपूर्णांकk("RPC:        req=%p\n", req);
		list_del(&req->rq_bc_pa_list);
		xprt_मुक्त_allocation(req);
		xprt->bc_alloc_count--;
		atomic_dec(&xprt->bc_slot_count);
		अगर (--max_reqs == 0)
			अवरोध;
	पूर्ण
	spin_unlock_bh(&xprt->bc_pa_lock);

out:
	dprपूर्णांकk("RPC:        backchannel list empty= %s\n",
		list_empty(&xprt->bc_pa_list) ? "true" : "false");
पूर्ण

अटल काष्ठा rpc_rqst *xprt_get_bc_request(काष्ठा rpc_xprt *xprt, __be32 xid,
		काष्ठा rpc_rqst *new)
अणु
	काष्ठा rpc_rqst *req = शून्य;

	dprपूर्णांकk("RPC:       allocate a backchannel request\n");
	अगर (list_empty(&xprt->bc_pa_list)) अणु
		अगर (!new)
			जाओ not_found;
		अगर (atomic_पढ़ो(&xprt->bc_slot_count) >= BC_MAX_SLOTS)
			जाओ not_found;
		list_add_tail(&new->rq_bc_pa_list, &xprt->bc_pa_list);
		xprt->bc_alloc_count++;
		atomic_inc(&xprt->bc_slot_count);
	पूर्ण
	req = list_first_entry(&xprt->bc_pa_list, काष्ठा rpc_rqst,
				rq_bc_pa_list);
	req->rq_reply_bytes_recvd = 0;
	स_नकल(&req->rq_निजी_buf, &req->rq_rcv_buf,
			माप(req->rq_निजी_buf));
	req->rq_xid = xid;
	req->rq_connect_cookie = xprt->connect_cookie;
	dprपूर्णांकk("RPC:       backchannel req=%p\n", req);
not_found:
	वापस req;
पूर्ण

/*
 * Return the pपुनः_स्मृतिated rpc_rqst काष्ठाure and XDR buffers
 * associated with this rpc_task.
 */
व्योम xprt_मुक्त_bc_request(काष्ठा rpc_rqst *req)
अणु
	काष्ठा rpc_xprt *xprt = req->rq_xprt;

	xprt->ops->bc_मुक्त_rqst(req);
पूर्ण

व्योम xprt_मुक्त_bc_rqst(काष्ठा rpc_rqst *req)
अणु
	काष्ठा rpc_xprt *xprt = req->rq_xprt;

	dprपूर्णांकk("RPC:       free backchannel req=%p\n", req);

	req->rq_connect_cookie = xprt->connect_cookie - 1;
	smp_mb__beक्रमe_atomic();
	clear_bit(RPC_BC_PA_IN_USE, &req->rq_bc_pa_state);
	smp_mb__after_atomic();

	/*
	 * Return it to the list of pपुनः_स्मृतिations so that it
	 * may be reused by a new callback request.
	 */
	spin_lock_bh(&xprt->bc_pa_lock);
	अगर (xprt_need_to_requeue(xprt)) अणु
		list_add_tail(&req->rq_bc_pa_list, &xprt->bc_pa_list);
		xprt->bc_alloc_count++;
		atomic_inc(&xprt->bc_slot_count);
		req = शून्य;
	पूर्ण
	spin_unlock_bh(&xprt->bc_pa_lock);
	अगर (req != शून्य) अणु
		/*
		 * The last reमुख्यing session was destroyed जबतक this
		 * entry was in use.  Free the entry and करोn't attempt
		 * to add back to the list because there is no need to
		 * have anymore pपुनः_स्मृतिated entries.
		 */
		dprपूर्णांकk("RPC:       Last session removed req=%p\n", req);
		xprt_मुक्त_allocation(req);
	पूर्ण
	xprt_put(xprt);
पूर्ण

/*
 * One or more rpc_rqst काष्ठाure have been pपुनः_स्मृतिated during the
 * backchannel setup.  Buffer space क्रम the send and निजी XDR buffers
 * has been pपुनः_स्मृतिated as well.  Use xprt_alloc_bc_request to allocate
 * to this request.  Use xprt_मुक्त_bc_request to वापस it.
 *
 * We know that we're called in soft पूर्णांकerrupt context, grab the spin_lock
 * since there is no need to grab the bottom half spin_lock.
 *
 * Return an available rpc_rqst, otherwise शून्य अगर non are available.
 */
काष्ठा rpc_rqst *xprt_lookup_bc_request(काष्ठा rpc_xprt *xprt, __be32 xid)
अणु
	काष्ठा rpc_rqst *req, *new = शून्य;

	करो अणु
		spin_lock(&xprt->bc_pa_lock);
		list_क्रम_each_entry(req, &xprt->bc_pa_list, rq_bc_pa_list) अणु
			अगर (req->rq_connect_cookie != xprt->connect_cookie)
				जारी;
			अगर (req->rq_xid == xid)
				जाओ found;
		पूर्ण
		req = xprt_get_bc_request(xprt, xid, new);
found:
		spin_unlock(&xprt->bc_pa_lock);
		अगर (new) अणु
			अगर (req != new)
				xprt_मुक्त_allocation(new);
			अवरोध;
		पूर्ण अन्यथा अगर (req)
			अवरोध;
		new = xprt_alloc_bc_req(xprt, GFP_KERNEL);
	पूर्ण जबतक (new);
	वापस req;
पूर्ण

/*
 * Add callback request to callback list.  The callback
 * service sleeps on the sv_cb_रुकोq रुकोing क्रम new
 * requests.  Wake it up after adding enqueing the
 * request.
 */
व्योम xprt_complete_bc_request(काष्ठा rpc_rqst *req, uपूर्णांक32_t copied)
अणु
	काष्ठा rpc_xprt *xprt = req->rq_xprt;
	काष्ठा svc_serv *bc_serv = xprt->bc_serv;

	spin_lock(&xprt->bc_pa_lock);
	list_del(&req->rq_bc_pa_list);
	xprt->bc_alloc_count--;
	spin_unlock(&xprt->bc_pa_lock);

	req->rq_निजी_buf.len = copied;
	set_bit(RPC_BC_PA_IN_USE, &req->rq_bc_pa_state);

	dprपूर्णांकk("RPC:       add callback request to list\n");
	xprt_get(xprt);
	spin_lock(&bc_serv->sv_cb_lock);
	list_add(&req->rq_bc_list, &bc_serv->sv_cb_list);
	wake_up(&bc_serv->sv_cb_रुकोq);
	spin_unlock(&bc_serv->sv_cb_lock);
पूर्ण
