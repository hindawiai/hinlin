<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * linux/include/linux/sunrpc/debug.h
 *
 * Debugging support क्रम sunrpc module
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */
#अगर_अघोषित _LINUX_SUNRPC_DEBUG_H_
#घोषणा _LINUX_SUNRPC_DEBUG_H_

#समावेश <uapi/linux/sunrpc/debug.h>

/*
 * Debugging macros etc
 */
#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
बाह्य अचिन्हित पूर्णांक		rpc_debug;
बाह्य अचिन्हित पूर्णांक		nfs_debug;
बाह्य अचिन्हित पूर्णांक		nfsd_debug;
बाह्य अचिन्हित पूर्णांक		nlm_debug;
#पूर्ण_अगर

#घोषणा dprपूर्णांकk(fmt, ...)						\
	dfprपूर्णांकk(FACILITY, fmt, ##__VA_ARGS__)
#घोषणा dprपूर्णांकk_cont(fmt, ...)						\
	dfprपूर्णांकk_cont(FACILITY, fmt, ##__VA_ARGS__)
#घोषणा dprपूर्णांकk_rcu(fmt, ...)						\
	dfprपूर्णांकk_rcu(FACILITY, fmt, ##__VA_ARGS__)
#घोषणा dprपूर्णांकk_rcu_cont(fmt, ...)					\
	dfprपूर्णांकk_rcu_cont(FACILITY, fmt, ##__VA_ARGS__)

#अघोषित अगरdebug
#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define अगरdebug(fac)		अगर (unlikely(rpc_debug & RPCDBG_##fac))

# define dfprपूर्णांकk(fac, fmt, ...)					\
करो अणु									\
	अगरdebug(fac)							\
		prपूर्णांकk(KERN_DEFAULT fmt, ##__VA_ARGS__);		\
पूर्ण जबतक (0)

# define dfprपूर्णांकk_cont(fac, fmt, ...)					\
करो अणु									\
	अगरdebug(fac)							\
		prपूर्णांकk(KERN_CONT fmt, ##__VA_ARGS__);			\
पूर्ण जबतक (0)

# define dfprपूर्णांकk_rcu(fac, fmt, ...)					\
करो अणु									\
	अगरdebug(fac) अणु							\
		rcu_पढ़ो_lock();					\
		prपूर्णांकk(KERN_DEFAULT fmt, ##__VA_ARGS__);		\
		rcu_पढ़ो_unlock();					\
	पूर्ण								\
पूर्ण जबतक (0)

# define dfprपूर्णांकk_rcu_cont(fac, fmt, ...)				\
करो अणु									\
	अगरdebug(fac) अणु							\
		rcu_पढ़ो_lock();					\
		prपूर्णांकk(KERN_CONT fmt, ##__VA_ARGS__);			\
		rcu_पढ़ो_unlock();					\
	पूर्ण								\
पूर्ण जबतक (0)

# define RPC_IFDEBUG(x)		x
#अन्यथा
# define अगरdebug(fac)		अगर (0)
# define dfprपूर्णांकk(fac, fmt, ...)	करो अणुपूर्ण जबतक (0)
# define dfprपूर्णांकk_cont(fac, fmt, ...)	करो अणुपूर्ण जबतक (0)
# define dfprपूर्णांकk_rcu(fac, fmt, ...)	करो अणुपूर्ण जबतक (0)
# define RPC_IFDEBUG(x)
#पूर्ण_अगर

/*
 * Sysctl पूर्णांकerface क्रम RPC debugging
 */

काष्ठा rpc_clnt;
काष्ठा rpc_xprt;

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
व्योम		rpc_रेजिस्टर_sysctl(व्योम);
व्योम		rpc_unरेजिस्टर_sysctl(व्योम);
व्योम		sunrpc_debugfs_init(व्योम);
व्योम		sunrpc_debugfs_निकास(व्योम);
व्योम		rpc_clnt_debugfs_रेजिस्टर(काष्ठा rpc_clnt *);
व्योम		rpc_clnt_debugfs_unरेजिस्टर(काष्ठा rpc_clnt *);
व्योम		rpc_xprt_debugfs_रेजिस्टर(काष्ठा rpc_xprt *);
व्योम		rpc_xprt_debugfs_unरेजिस्टर(काष्ठा rpc_xprt *);
#अन्यथा
अटल अंतरभूत व्योम
sunrpc_debugfs_init(व्योम)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम
sunrpc_debugfs_निकास(व्योम)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम
rpc_clnt_debugfs_रेजिस्टर(काष्ठा rpc_clnt *clnt)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम
rpc_clnt_debugfs_unरेजिस्टर(काष्ठा rpc_clnt *clnt)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम
rpc_xprt_debugfs_रेजिस्टर(काष्ठा rpc_xprt *xprt)
अणु
	वापस;
पूर्ण

अटल अंतरभूत व्योम
rpc_xprt_debugfs_unरेजिस्टर(काष्ठा rpc_xprt *xprt)
अणु
	वापस;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _LINUX_SUNRPC_DEBUG_H_ */
