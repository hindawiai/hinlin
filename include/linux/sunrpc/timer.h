<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  linux/include/linux/sunrpc/समयr.h
 *
 *  Declarations क्रम the RPC transport समयr.
 *
 *  Copyright (C) 2002 Trond Myklebust <trond.myklebust@fys.uio.no>
 */

#अगर_अघोषित _LINUX_SUNRPC_TIMER_H
#घोषणा _LINUX_SUNRPC_TIMER_H

#समावेश <linux/atomic.h>

काष्ठा rpc_rtt अणु
	अचिन्हित दीर्घ समयo;	/* शेष समयout value */
	अचिन्हित दीर्घ srtt[5];	/* smoothed round trip समय << 3 */
	अचिन्हित दीर्घ sdrtt[5];	/* smoothed medium deviation of RTT */
	पूर्णांक nसमयouts[5];	/* Number of समयouts क्रम the last request */
पूर्ण;


बाह्य व्योम rpc_init_rtt(काष्ठा rpc_rtt *rt, अचिन्हित दीर्घ समयo);
बाह्य व्योम rpc_update_rtt(काष्ठा rpc_rtt *rt, अचिन्हित समयr, दीर्घ m);
बाह्य अचिन्हित दीर्घ rpc_calc_rto(काष्ठा rpc_rtt *rt, अचिन्हित समयr);

अटल अंतरभूत व्योम rpc_set_समयo(काष्ठा rpc_rtt *rt, पूर्णांक समयr, पूर्णांक nसमयo)
अणु
	पूर्णांक *t;
	अगर (!समयr)
		वापस;
	t = &rt->nसमयouts[समयr-1];
	अगर (nसमयo < *t) अणु
		अगर (*t > 0)
			(*t)--;
	पूर्ण अन्यथा अणु
		अगर (nसमयo > 8)
			nसमयo = 8;
		*t = nसमयo;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक rpc_nसमयo(काष्ठा rpc_rtt *rt, पूर्णांक समयr)
अणु
	अगर (!समयr)
		वापस 0;
	वापस rt->nसमयouts[समयr-1];
पूर्ण

#पूर्ण_अगर /* _LINUX_SUNRPC_TIMER_H */
