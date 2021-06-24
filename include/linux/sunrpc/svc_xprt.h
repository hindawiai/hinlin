<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/sunrpc/svc_xprt.h
 *
 * RPC server transport I/O
 */

#अगर_अघोषित SUNRPC_SVC_XPRT_H
#घोषणा SUNRPC_SVC_XPRT_H

#समावेश <linux/sunrpc/svc.h>

काष्ठा module;

काष्ठा svc_xprt_ops अणु
	काष्ठा svc_xprt	*(*xpo_create)(काष्ठा svc_serv *,
				       काष्ठा net *net,
				       काष्ठा sockaddr *, पूर्णांक,
				       पूर्णांक);
	काष्ठा svc_xprt	*(*xpo_accept)(काष्ठा svc_xprt *);
	पूर्णांक		(*xpo_has_wspace)(काष्ठा svc_xprt *);
	पूर्णांक		(*xpo_recvfrom)(काष्ठा svc_rqst *);
	पूर्णांक		(*xpo_sendto)(काष्ठा svc_rqst *);
	पूर्णांक		(*xpo_result_payload)(काष्ठा svc_rqst *, अचिन्हित पूर्णांक,
					      अचिन्हित पूर्णांक);
	व्योम		(*xpo_release_rqst)(काष्ठा svc_rqst *);
	व्योम		(*xpo_detach)(काष्ठा svc_xprt *);
	व्योम		(*xpo_मुक्त)(काष्ठा svc_xprt *);
	व्योम		(*xpo_secure_port)(काष्ठा svc_rqst *rqstp);
	व्योम		(*xpo_समाप्त_temp_xprt)(काष्ठा svc_xprt *);
पूर्ण;

काष्ठा svc_xprt_class अणु
	स्थिर अक्षर		*xcl_name;
	काष्ठा module		*xcl_owner;
	स्थिर काष्ठा svc_xprt_ops *xcl_ops;
	काष्ठा list_head	xcl_list;
	u32			xcl_max_payload;
	पूर्णांक			xcl_ident;
पूर्ण;

/*
 * This is embedded in an object that wants a callback beक्रमe deleting
 * an xprt; पूर्णांकended क्रम use by NFSv4.1, which needs to know when a
 * client's tcp connection (and hence possibly a backchannel) goes away.
 */
काष्ठा svc_xpt_user अणु
	काष्ठा list_head list;
	व्योम (*callback)(काष्ठा svc_xpt_user *);
पूर्ण;

काष्ठा svc_xprt अणु
	काष्ठा svc_xprt_class	*xpt_class;
	स्थिर काष्ठा svc_xprt_ops *xpt_ops;
	काष्ठा kref		xpt_ref;
	काष्ठा list_head	xpt_list;
	काष्ठा list_head	xpt_पढ़ोy;
	अचिन्हित दीर्घ		xpt_flags;
#घोषणा	XPT_BUSY	0		/* enqueued/receiving */
#घोषणा	XPT_CONN	1		/* conn pending */
#घोषणा	XPT_CLOSE	2		/* dead or dying */
#घोषणा	XPT_DATA	3		/* data pending */
#घोषणा	XPT_TEMP	4		/* connected transport */
#घोषणा	XPT_DEAD	6		/* transport बंदd */
#घोषणा	XPT_CHNGBUF	7		/* need to change snd/rcv buf sizes */
#घोषणा	XPT_DEFERRED	8		/* deferred request pending */
#घोषणा	XPT_OLD		9		/* used क्रम xprt aging mark+sweep */
#घोषणा XPT_LISTENER	10		/* listening endpoपूर्णांक */
#घोषणा XPT_CACHE_AUTH	11		/* cache auth info */
#घोषणा XPT_LOCAL	12		/* connection from loopback पूर्णांकerface */
#घोषणा XPT_KILL_TEMP   13		/* call xpo_समाप्त_temp_xprt beक्रमe closing */
#घोषणा XPT_CONG_CTRL	14		/* has congestion control */

	काष्ठा svc_serv		*xpt_server;	/* service क्रम transport */
	atomic_t    	    	xpt_reserved;	/* space on outq that is rsvd */
	atomic_t		xpt_nr_rqsts;	/* Number of requests */
	काष्ठा mutex		xpt_mutex;	/* to serialize sending data */
	spinlock_t		xpt_lock;	/* protects sk_deferred
						 * and xpt_auth_cache */
	व्योम			*xpt_auth_cache;/* auth cache */
	काष्ठा list_head	xpt_deferred;	/* deferred requests that need
						 * to be revisted */
	काष्ठा sockaddr_storage	xpt_local;	/* local address */
	माप_प्रकार			xpt_locallen;	/* length of address */
	काष्ठा sockaddr_storage	xpt_remote;	/* remote peer's address */
	माप_प्रकार			xpt_remotelen;	/* length of address */
	अक्षर			xpt_remotebuf[INET6_ADDRSTRLEN + 10];
	काष्ठा list_head	xpt_users;	/* callbacks on मुक्त */

	काष्ठा net		*xpt_net;
	स्थिर काष्ठा cred	*xpt_cred;
	काष्ठा rpc_xprt		*xpt_bc_xprt;	/* NFSv4.1 backchannel */
	काष्ठा rpc_xprt_चयन	*xpt_bc_xps;	/* NFSv4.1 backchannel */
पूर्ण;

अटल अंतरभूत व्योम unरेजिस्टर_xpt_user(काष्ठा svc_xprt *xpt, काष्ठा svc_xpt_user *u)
अणु
	spin_lock(&xpt->xpt_lock);
	list_del_init(&u->list);
	spin_unlock(&xpt->xpt_lock);
पूर्ण

अटल अंतरभूत पूर्णांक रेजिस्टर_xpt_user(काष्ठा svc_xprt *xpt, काष्ठा svc_xpt_user *u)
अणु
	spin_lock(&xpt->xpt_lock);
	अगर (test_bit(XPT_CLOSE, &xpt->xpt_flags)) अणु
		/*
		 * The connection is about to be deleted soon (or,
		 * worse, may alपढ़ोy be deleted--in which हाल we've
		 * alपढ़ोy notअगरied the xpt_users).
		 */
		spin_unlock(&xpt->xpt_lock);
		वापस -ENOTCONN;
	पूर्ण
	list_add(&u->list, &xpt->xpt_users);
	spin_unlock(&xpt->xpt_lock);
	वापस 0;
पूर्ण

अटल अंतरभूत bool svc_xprt_is_dead(स्थिर काष्ठा svc_xprt *xprt)
अणु
	वापस (test_bit(XPT_DEAD, &xprt->xpt_flags) != 0) ||
		(test_bit(XPT_CLOSE, &xprt->xpt_flags) != 0);
पूर्ण

पूर्णांक	svc_reg_xprt_class(काष्ठा svc_xprt_class *);
व्योम	svc_unreg_xprt_class(काष्ठा svc_xprt_class *);
व्योम	svc_xprt_init(काष्ठा net *, काष्ठा svc_xprt_class *, काष्ठा svc_xprt *,
		      काष्ठा svc_serv *);
पूर्णांक	svc_create_xprt(काष्ठा svc_serv *, स्थिर अक्षर *, काष्ठा net *,
			स्थिर पूर्णांक, स्थिर अचिन्हित लघु, पूर्णांक,
			स्थिर काष्ठा cred *);
व्योम	svc_xprt_received(काष्ठा svc_xprt *xprt);
व्योम	svc_xprt_करो_enqueue(काष्ठा svc_xprt *xprt);
व्योम	svc_xprt_enqueue(काष्ठा svc_xprt *xprt);
व्योम	svc_xprt_put(काष्ठा svc_xprt *xprt);
व्योम	svc_xprt_copy_addrs(काष्ठा svc_rqst *rqstp, काष्ठा svc_xprt *xprt);
व्योम	svc_बंद_xprt(काष्ठा svc_xprt *xprt);
पूर्णांक	svc_port_is_privileged(काष्ठा sockaddr *sin);
पूर्णांक	svc_prपूर्णांक_xprts(अक्षर *buf, पूर्णांक maxlen);
काष्ठा	svc_xprt *svc_find_xprt(काष्ठा svc_serv *serv, स्थिर अक्षर *xcl_name,
			काष्ठा net *net, स्थिर sa_family_t af,
			स्थिर अचिन्हित लघु port);
पूर्णांक	svc_xprt_names(काष्ठा svc_serv *serv, अक्षर *buf, स्थिर पूर्णांक buflen);
व्योम	svc_add_new_perm_xprt(काष्ठा svc_serv *serv, काष्ठा svc_xprt *xprt);
व्योम	svc_age_temp_xprts_now(काष्ठा svc_serv *, काष्ठा sockaddr *);
व्योम	svc_xprt_deferred_बंद(काष्ठा svc_xprt *xprt);

अटल अंतरभूत व्योम svc_xprt_get(काष्ठा svc_xprt *xprt)
अणु
	kref_get(&xprt->xpt_ref);
पूर्ण
अटल अंतरभूत व्योम svc_xprt_set_local(काष्ठा svc_xprt *xprt,
				      स्थिर काष्ठा sockaddr *sa,
				      स्थिर माप_प्रकार salen)
अणु
	स_नकल(&xprt->xpt_local, sa, salen);
	xprt->xpt_locallen = salen;
पूर्ण
अटल अंतरभूत व्योम svc_xprt_set_remote(काष्ठा svc_xprt *xprt,
				       स्थिर काष्ठा sockaddr *sa,
				       स्थिर माप_प्रकार salen)
अणु
	स_नकल(&xprt->xpt_remote, sa, salen);
	xprt->xpt_remotelen = salen;
	snम_लिखो(xprt->xpt_remotebuf, माप(xprt->xpt_remotebuf) - 1,
		 "%pISpc", sa);
पूर्ण

अटल अंतरभूत अचिन्हित लघु svc_addr_port(स्थिर काष्ठा sockaddr *sa)
अणु
	स्थिर काष्ठा sockaddr_in *sin = (स्थिर काष्ठा sockaddr_in *)sa;
	स्थिर काष्ठा sockaddr_in6 *sin6 = (स्थिर काष्ठा sockaddr_in6 *)sa;

	चयन (sa->sa_family) अणु
	हाल AF_INET:
		वापस ntohs(sin->sin_port);
	हाल AF_INET6:
		वापस ntohs(sin6->sin6_port);
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत माप_प्रकार svc_addr_len(स्थिर काष्ठा sockaddr *sa)
अणु
	चयन (sa->sa_family) अणु
	हाल AF_INET:
		वापस माप(काष्ठा sockaddr_in);
	हाल AF_INET6:
		वापस माप(काष्ठा sockaddr_in6);
	पूर्ण
	BUG();
पूर्ण

अटल अंतरभूत अचिन्हित लघु svc_xprt_local_port(स्थिर काष्ठा svc_xprt *xprt)
अणु
	वापस svc_addr_port((स्थिर काष्ठा sockaddr *)&xprt->xpt_local);
पूर्ण

अटल अंतरभूत अचिन्हित लघु svc_xprt_remote_port(स्थिर काष्ठा svc_xprt *xprt)
अणु
	वापस svc_addr_port((स्थिर काष्ठा sockaddr *)&xprt->xpt_remote);
पूर्ण

अटल अंतरभूत अक्षर *__svc_prपूर्णांक_addr(स्थिर काष्ठा sockaddr *addr,
				     अक्षर *buf, स्थिर माप_प्रकार len)
अणु
	स्थिर काष्ठा sockaddr_in *sin = (स्थिर काष्ठा sockaddr_in *)addr;
	स्थिर काष्ठा sockaddr_in6 *sin6 = (स्थिर काष्ठा sockaddr_in6 *)addr;

	चयन (addr->sa_family) अणु
	हाल AF_INET:
		snम_लिखो(buf, len, "%pI4, port=%u", &sin->sin_addr,
			ntohs(sin->sin_port));
		अवरोध;

	हाल AF_INET6:
		snम_लिखो(buf, len, "%pI6, port=%u",
			 &sin6->sin6_addr,
			ntohs(sin6->sin6_port));
		अवरोध;

	शेष:
		snम_लिखो(buf, len, "unknown address type: %d", addr->sa_family);
		अवरोध;
	पूर्ण

	वापस buf;
पूर्ण
#पूर्ण_अगर /* SUNRPC_SVC_XPRT_H */
