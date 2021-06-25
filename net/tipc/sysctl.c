<शैली गुरु>
/*
 * net/tipc/sysctl.c: sysctl पूर्णांकerface to TIPC subप्रणाली
 *
 * Copyright (c) 2013, Wind River Systems
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the names of the copyright holders nor the names of its
 *    contributors may be used to enकरोrse or promote products derived from
 *    this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश "core.h"
#समावेश "trace.h"
#समावेश "crypto.h"
#समावेश "bcast.h"
#समावेश <linux/sysctl.h>

अटल काष्ठा ctl_table_header *tipc_ctl_hdr;

अटल काष्ठा ctl_table tipc_table[] = अणु
	अणु
		.procname	= "tipc_rmem",
		.data		= &sysctl_tipc_rmem,
		.maxlen		= माप(sysctl_tipc_rmem),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1         = SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "named_timeout",
		.data		= &sysctl_tipc_named_समयout,
		.maxlen		= माप(sysctl_tipc_named_समयout),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1         = SYSCTL_ZERO,
	पूर्ण,
	अणु
		.procname       = "sk_filter",
		.data           = &sysctl_tipc_sk_filter,
		.maxlen         = माप(sysctl_tipc_sk_filter),
		.mode           = 0644,
		.proc_handler   = proc_करोuदीर्घvec_minmax,
	पूर्ण,
#अगर_घोषित CONFIG_TIPC_CRYPTO
	अणु
		.procname	= "max_tfms",
		.data		= &sysctl_tipc_max_tfms,
		.maxlen		= माप(sysctl_tipc_max_tfms),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1         = SYSCTL_ONE,
	पूर्ण,
	अणु
		.procname	= "key_exchange_enabled",
		.data		= &sysctl_tipc_key_exchange_enabled,
		.maxlen		= माप(sysctl_tipc_key_exchange_enabled),
		.mode		= 0644,
		.proc_handler	= proc_करोपूर्णांकvec_minmax,
		.extra1         = SYSCTL_ZERO,
		.extra2         = SYSCTL_ONE,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.procname	= "bc_retruni",
		.data		= &sysctl_tipc_bc_retruni,
		.maxlen		= माप(sysctl_tipc_bc_retruni),
		.mode		= 0644,
		.proc_handler	= proc_करोuदीर्घvec_minmax,
	पूर्ण,
	अणुपूर्ण
पूर्ण;

पूर्णांक tipc_रेजिस्टर_sysctl(व्योम)
अणु
	tipc_ctl_hdr = रेजिस्टर_net_sysctl(&init_net, "net/tipc", tipc_table);
	अगर (tipc_ctl_hdr == शून्य)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

व्योम tipc_unरेजिस्टर_sysctl(व्योम)
अणु
	unरेजिस्टर_net_sysctl_table(tipc_ctl_hdr);
पूर्ण
