<शैली गुरु>
/*
 * net/tipc/core.c: TIPC module code
 *
 * Copyright (c) 2003-2006, 2013, Ericsson AB
 * Copyright (c) 2005-2006, 2010-2013, Wind River Systems
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
#समावेश "name_table.h"
#समावेश "subscr.h"
#समावेश "bearer.h"
#समावेश "net.h"
#समावेश "socket.h"
#समावेश "bcast.h"
#समावेश "node.h"
#समावेश "crypto.h"

#समावेश <linux/module.h>

/* configurable TIPC parameters */
अचिन्हित पूर्णांक tipc_net_id __पढ़ो_mostly;
पूर्णांक sysctl_tipc_rmem[3] __पढ़ो_mostly;	/* min/शेष/max */

अटल पूर्णांक __net_init tipc_init_net(काष्ठा net *net)
अणु
	काष्ठा tipc_net *tn = net_generic(net, tipc_net_id);
	पूर्णांक err;

	tn->net_id = 4711;
	tn->node_addr = 0;
	tn->trial_addr = 0;
	tn->addr_trial_end = 0;
	tn->capabilities = TIPC_NODE_CAPABILITIES;
	INIT_WORK(&tn->work, tipc_net_finalize_work);
	स_रखो(tn->node_id, 0, माप(tn->node_id));
	स_रखो(tn->node_id_string, 0, माप(tn->node_id_string));
	tn->mon_threshold = TIPC_DEF_MON_THRESHOLD;
	get_अक्रमom_bytes(&tn->अक्रमom, माप(पूर्णांक));
	INIT_LIST_HEAD(&tn->node_list);
	spin_lock_init(&tn->node_list_lock);

#अगर_घोषित CONFIG_TIPC_CRYPTO
	err = tipc_crypto_start(&tn->crypto_tx, net, शून्य);
	अगर (err)
		जाओ out_crypto;
#पूर्ण_अगर
	err = tipc_sk_rht_init(net);
	अगर (err)
		जाओ out_sk_rht;

	err = tipc_nametbl_init(net);
	अगर (err)
		जाओ out_nametbl;

	err = tipc_bcast_init(net);
	अगर (err)
		जाओ out_bclink;

	err = tipc_attach_loopback(net);
	अगर (err)
		जाओ out_bclink;

	वापस 0;

out_bclink:
	tipc_nametbl_stop(net);
out_nametbl:
	tipc_sk_rht_destroy(net);
out_sk_rht:

#अगर_घोषित CONFIG_TIPC_CRYPTO
	tipc_crypto_stop(&tn->crypto_tx);
out_crypto:
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल व्योम __net_निकास tipc_निकास_net(काष्ठा net *net)
अणु
	काष्ठा tipc_net *tn = tipc_net(net);

	tipc_detach_loopback(net);
	/* Make sure the tipc_net_finalize_work() finished */
	cancel_work_sync(&tn->work);
	tipc_net_stop(net);

	tipc_bcast_stop(net);
	tipc_nametbl_stop(net);
	tipc_sk_rht_destroy(net);
#अगर_घोषित CONFIG_TIPC_CRYPTO
	tipc_crypto_stop(&tipc_net(net)->crypto_tx);
#पूर्ण_अगर
	जबतक (atomic_पढ़ो(&tn->wq_count))
		cond_resched();
पूर्ण

अटल व्योम __net_निकास tipc_pernet_pre_निकास(काष्ठा net *net)
अणु
	tipc_node_pre_cleanup_net(net);
पूर्ण

अटल काष्ठा pernet_operations tipc_pernet_pre_निकास_ops = अणु
	.pre_निकास = tipc_pernet_pre_निकास,
पूर्ण;

अटल काष्ठा pernet_operations tipc_net_ops = अणु
	.init = tipc_init_net,
	.निकास = tipc_निकास_net,
	.id   = &tipc_net_id,
	.size = माप(काष्ठा tipc_net),
पूर्ण;

अटल काष्ठा pernet_operations tipc_topsrv_net_ops = अणु
	.init = tipc_topsrv_init_net,
	.निकास = tipc_topsrv_निकास_net,
पूर्ण;

अटल पूर्णांक __init tipc_init(व्योम)
अणु
	पूर्णांक err;

	pr_info("Activated (version " TIPC_MOD_VER ")\n");

	sysctl_tipc_rmem[0] = RCVBUF_MIN;
	sysctl_tipc_rmem[1] = RCVBUF_DEF;
	sysctl_tipc_rmem[2] = RCVBUF_MAX;

	err = tipc_रेजिस्टर_sysctl();
	अगर (err)
		जाओ out_sysctl;

	err = रेजिस्टर_pernet_device(&tipc_net_ops);
	अगर (err)
		जाओ out_pernet;

	err = tipc_socket_init();
	अगर (err)
		जाओ out_socket;

	err = रेजिस्टर_pernet_device(&tipc_topsrv_net_ops);
	अगर (err)
		जाओ out_pernet_topsrv;

	err = रेजिस्टर_pernet_subsys(&tipc_pernet_pre_निकास_ops);
	अगर (err)
		जाओ out_रेजिस्टर_pernet_subsys;

	err = tipc_bearer_setup();
	अगर (err)
		जाओ out_bearer;

	err = tipc_netlink_start();
	अगर (err)
		जाओ out_netlink;

	err = tipc_netlink_compat_start();
	अगर (err)
		जाओ out_netlink_compat;

	pr_info("Started in single node mode\n");
	वापस 0;

out_netlink_compat:
	tipc_netlink_stop();
out_netlink:
	tipc_bearer_cleanup();
out_bearer:
	unरेजिस्टर_pernet_subsys(&tipc_pernet_pre_निकास_ops);
out_रेजिस्टर_pernet_subsys:
	unरेजिस्टर_pernet_device(&tipc_topsrv_net_ops);
out_pernet_topsrv:
	tipc_socket_stop();
out_socket:
	unरेजिस्टर_pernet_device(&tipc_net_ops);
out_pernet:
	tipc_unरेजिस्टर_sysctl();
out_sysctl:
	pr_err("Unable to start in single node mode\n");
	वापस err;
पूर्ण

अटल व्योम __निकास tipc_निकास(व्योम)
अणु
	tipc_netlink_compat_stop();
	tipc_netlink_stop();
	tipc_bearer_cleanup();
	unरेजिस्टर_pernet_subsys(&tipc_pernet_pre_निकास_ops);
	unरेजिस्टर_pernet_device(&tipc_topsrv_net_ops);
	tipc_socket_stop();
	unरेजिस्टर_pernet_device(&tipc_net_ops);
	tipc_unरेजिस्टर_sysctl();

	pr_info("Deactivated\n");
पूर्ण

module_init(tipc_init);
module_निकास(tipc_निकास);

MODULE_DESCRIPTION("TIPC: Transparent Inter Process Communication");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_VERSION(TIPC_MOD_VER);
