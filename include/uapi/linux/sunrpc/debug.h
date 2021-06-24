<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * linux/include/linux/sunrpc/debug.h
 *
 * Debugging support क्रम sunrpc module
 *
 * Copyright (C) 1996, Olaf Kirch <okir@monad.swb.de>
 */

#अगर_अघोषित _UAPI_LINUX_SUNRPC_DEBUG_H_
#घोषणा _UAPI_LINUX_SUNRPC_DEBUG_H_

/*
 * RPC debug facilities
 */
#घोषणा RPCDBG_XPRT		0x0001
#घोषणा RPCDBG_CALL		0x0002
#घोषणा RPCDBG_DEBUG		0x0004
#घोषणा RPCDBG_NFS		0x0008
#घोषणा RPCDBG_AUTH		0x0010
#घोषणा RPCDBG_BIND		0x0020
#घोषणा RPCDBG_SCHED		0x0040
#घोषणा RPCDBG_TRANS		0x0080
#घोषणा RPCDBG_SVCXPRT		0x0100
#घोषणा RPCDBG_SVCDSP		0x0200
#घोषणा RPCDBG_MISC		0x0400
#घोषणा RPCDBG_CACHE		0x0800
#घोषणा RPCDBG_ALL		0x7fff


/*
 * Declarations क्रम the sysctl debug पूर्णांकerface, which allows to पढ़ो or
 * change the debug flags क्रम rpc, nfs, nfsd, and lockd. Since the sunrpc
 * module currently रेजिस्टरs its sysctl table dynamically, the sysctl path
 * क्रम module FOO is <CTL_SUNRPC, CTL_FOODEBUG>.
 */

क्रमागत अणु
	CTL_RPCDEBUG = 1,
	CTL_NFSDEBUG,
	CTL_NFSDDEBUG,
	CTL_NLMDEBUG,
	CTL_SLOTTABLE_UDP,
	CTL_SLOTTABLE_TCP,
	CTL_MIN_RESVPORT,
	CTL_MAX_RESVPORT,
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_SUNRPC_DEBUG_H_ */
