<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/net/sunrpc/समयr.c
 *
 * Estimate RPC request round trip समय.
 *
 * Based on packet round-trip and variance estimator algorithms described
 * in appendix A of "Congestion Avoidance and Control" by Van Jacobson
 * and Michael J. Karels (ACM Computer Communication Review; Proceedings
 * of the Sigcomm '88 Symposium in Stanक्रमd, CA, August, 1988).
 *
 * This RTT estimator is used only क्रम RPC over datagram protocols.
 *
 * Copyright (C) 2002 Trond Myklebust <trond.myklebust@fys.uio.no>
 */

#समावेश <यंत्र/param.h>

#समावेश <linux/types.h>
#समावेश <linux/unistd.h>
#समावेश <linux/module.h>

#समावेश <linux/sunrpc/clnt.h>

#घोषणा RPC_RTO_MAX (60*HZ)
#घोषणा RPC_RTO_INIT (HZ/5)
#घोषणा RPC_RTO_MIN (HZ/10)

/**
 * rpc_init_rtt - Initialize an RPC RTT estimator context
 * @rt: context to initialize
 * @समयo: initial समयout value, in jअगरfies
 *
 */
व्योम rpc_init_rtt(काष्ठा rpc_rtt *rt, अचिन्हित दीर्घ समयo)
अणु
	अचिन्हित दीर्घ init = 0;
	अचिन्हित पूर्णांक i;

	rt->समयo = समयo;

	अगर (समयo > RPC_RTO_INIT)
		init = (समयo - RPC_RTO_INIT) << 3;
	क्रम (i = 0; i < 5; i++) अणु
		rt->srtt[i] = init;
		rt->sdrtt[i] = RPC_RTO_INIT;
		rt->nसमयouts[i] = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rpc_init_rtt);

/**
 * rpc_update_rtt - Update an RPC RTT estimator context
 * @rt: context to update
 * @समयr: समयr array index (request type)
 * @m: recent actual RTT, in jअगरfies
 *
 * NB: When computing the smoothed RTT and standard deviation,
 *     be careful not to produce negative पूर्णांकermediate results.
 */
व्योम rpc_update_rtt(काष्ठा rpc_rtt *rt, अचिन्हित पूर्णांक समयr, दीर्घ m)
अणु
	दीर्घ *srtt, *sdrtt;

	अगर (समयr-- == 0)
		वापस;

	/* jअगरfies wrapped; ignore this one */
	अगर (m < 0)
		वापस;

	अगर (m == 0)
		m = 1L;

	srtt = (दीर्घ *)&rt->srtt[समयr];
	m -= *srtt >> 3;
	*srtt += m;

	अगर (m < 0)
		m = -m;

	sdrtt = (दीर्घ *)&rt->sdrtt[समयr];
	m -= *sdrtt >> 2;
	*sdrtt += m;

	/* Set lower bound on the variance */
	अगर (*sdrtt < RPC_RTO_MIN)
		*sdrtt = RPC_RTO_MIN;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_update_rtt);

/**
 * rpc_calc_rto - Provide an estimated समयout value
 * @rt: context to use क्रम calculation
 * @समयr: समयr array index (request type)
 *
 * Estimate RTO क्रम an NFS RPC sent via an unreliable datagram.  Use
 * the mean and mean deviation of RTT क्रम the appropriate type of RPC
 * क्रम frequently issued RPCs, and a fixed शेष क्रम the others.
 *
 * The justअगरication क्रम करोing "other" this way is that these RPCs
 * happen so infrequently that समयr estimation would probably be
 * stale.  Also, since many of these RPCs are non-idempotent, a
 * conservative समयout is desired.
 *
 * getattr, lookup,
 * पढ़ो, ग_लिखो, commit     - A+4D
 * other                   - समयo
 */
अचिन्हित दीर्घ rpc_calc_rto(काष्ठा rpc_rtt *rt, अचिन्हित पूर्णांक समयr)
अणु
	अचिन्हित दीर्घ res;

	अगर (समयr-- == 0)
		वापस rt->समयo;

	res = ((rt->srtt[समयr] + 7) >> 3) + rt->sdrtt[समयr];
	अगर (res > RPC_RTO_MAX)
		res = RPC_RTO_MAX;

	वापस res;
पूर्ण
EXPORT_SYMBOL_GPL(rpc_calc_rto);
