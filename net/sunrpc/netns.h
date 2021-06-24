<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SUNRPC_NETNS_H__
#घोषणा __SUNRPC_NETNS_H__

#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

काष्ठा cache_detail;

काष्ठा sunrpc_net अणु
	काष्ठा proc_dir_entry *proc_net_rpc;
	काष्ठा cache_detail *ip_map_cache;
	काष्ठा cache_detail *unix_gid_cache;
	काष्ठा cache_detail *rsc_cache;
	काष्ठा cache_detail *rsi_cache;

	काष्ठा super_block *pipefs_sb;
	काष्ठा rpc_pipe *gssd_dummy;
	काष्ठा mutex pipefs_sb_lock;

	काष्ठा list_head all_clients;
	spinlock_t rpc_client_lock;

	काष्ठा rpc_clnt *rpcb_local_clnt;
	काष्ठा rpc_clnt *rpcb_local_clnt4;
	spinlock_t rpcb_clnt_lock;
	अचिन्हित पूर्णांक rpcb_users;
	अचिन्हित पूर्णांक rpcb_is_af_local : 1;

	काष्ठा mutex gssp_lock;
	काष्ठा rpc_clnt *gssp_clnt;
	पूर्णांक use_gss_proxy;
	पूर्णांक pipe_version;
	atomic_t pipe_users;
	काष्ठा proc_dir_entry *use_gssp_proc;
पूर्ण;

बाह्य अचिन्हित पूर्णांक sunrpc_net_id;

पूर्णांक ip_map_cache_create(काष्ठा net *);
व्योम ip_map_cache_destroy(काष्ठा net *);

#पूर्ण_अगर
