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
 * Functions and macros used पूर्णांकernally by RPC
 */

#अगर_अघोषित _NET_SUNRPC_SUNRPC_H
#घोषणा _NET_SUNRPC_SUNRPC_H

#समावेश <linux/net.h>

/*
 * Header क्रम dynamically allocated rpc buffers.
 */
काष्ठा rpc_buffer अणु
	माप_प्रकार	len;
	अक्षर	data[];
पूर्ण;

अटल अंतरभूत पूर्णांक sock_is_loopback(काष्ठा sock *sk)
अणु
	काष्ठा dst_entry *dst;
	पूर्णांक loopback = 0;
	rcu_पढ़ो_lock();
	dst = rcu_dereference(sk->sk_dst_cache);
	अगर (dst && dst->dev &&
	    (dst->dev->features & NETIF_F_LOOPBACK))
		loopback = 1;
	rcu_पढ़ो_unlock();
	वापस loopback;
पूर्ण

पूर्णांक rpc_clients_notअगरier_रेजिस्टर(व्योम);
व्योम rpc_clients_notअगरier_unरेजिस्टर(व्योम);
व्योम auth_करोमुख्य_cleanup(व्योम);
#पूर्ण_अगर /* _NET_SUNRPC_SUNRPC_H */
