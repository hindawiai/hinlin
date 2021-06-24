<शैली गुरु>
/******************************************************************************

(c) 2008 NetApp.  All Rights Reserved.

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

/*
 * Functions to create and manage the backchannel
 */

#अगर_अघोषित _LINUX_SUNRPC_BC_XPRT_H
#घोषणा _LINUX_SUNRPC_BC_XPRT_H

#समावेश <linux/sunrpc/svcsock.h>
#समावेश <linux/sunrpc/xprt.h>
#समावेश <linux/sunrpc/sched.h>

#अगर_घोषित CONFIG_SUNRPC_BACKCHANNEL
काष्ठा rpc_rqst *xprt_lookup_bc_request(काष्ठा rpc_xprt *xprt, __be32 xid);
व्योम xprt_complete_bc_request(काष्ठा rpc_rqst *req, uपूर्णांक32_t copied);
व्योम xprt_init_bc_request(काष्ठा rpc_rqst *req, काष्ठा rpc_task *task);
व्योम xprt_मुक्त_bc_request(काष्ठा rpc_rqst *req);
पूर्णांक xprt_setup_backchannel(काष्ठा rpc_xprt *, अचिन्हित पूर्णांक min_reqs);
व्योम xprt_destroy_backchannel(काष्ठा rpc_xprt *, अचिन्हित पूर्णांक max_reqs);

/* Socket backchannel transport methods */
पूर्णांक xprt_setup_bc(काष्ठा rpc_xprt *xprt, अचिन्हित पूर्णांक min_reqs);
व्योम xprt_destroy_bc(काष्ठा rpc_xprt *xprt, अचिन्हित पूर्णांक max_reqs);
व्योम xprt_मुक्त_bc_rqst(काष्ठा rpc_rqst *req);
अचिन्हित पूर्णांक xprt_bc_max_slots(काष्ठा rpc_xprt *xprt);

/*
 * Determine अगर a shared backchannel is in use
 */
अटल अंतरभूत bool svc_is_backchannel(स्थिर काष्ठा svc_rqst *rqstp)
अणु
	वापस rqstp->rq_server->sv_bc_enabled;
पूर्ण

अटल अंतरभूत व्योम set_bc_enabled(काष्ठा svc_serv *serv)
अणु
	serv->sv_bc_enabled = true;
पूर्ण
#अन्यथा /* CONFIG_SUNRPC_BACKCHANNEL */
अटल अंतरभूत पूर्णांक xprt_setup_backchannel(काष्ठा rpc_xprt *xprt,
					 अचिन्हित पूर्णांक min_reqs)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम xprt_destroy_backchannel(काष्ठा rpc_xprt *xprt,
					    अचिन्हित पूर्णांक max_reqs)
अणु
पूर्ण

अटल अंतरभूत bool svc_is_backchannel(स्थिर काष्ठा svc_rqst *rqstp)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम set_bc_enabled(काष्ठा svc_serv *serv)
अणु
पूर्ण

अटल अंतरभूत व्योम xprt_मुक्त_bc_request(काष्ठा rpc_rqst *req)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_SUNRPC_BACKCHANNEL */
#पूर्ण_अगर /* _LINUX_SUNRPC_BC_XPRT_H */

