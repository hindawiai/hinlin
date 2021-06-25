<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * NFS-निजी data क्रम each "struct net".  Accessed with net_generic().
 */

#अगर_अघोषित __NFS_NETNS_H__
#घोषणा __NFS_NETNS_H__

#समावेश <linux/nfs4.h>
#समावेश <net/net_namespace.h>
#समावेश <net/netns/generic.h>

काष्ठा bl_dev_msg अणु
	पूर्णांक32_t status;
	uपूर्णांक32_t major, minor;
पूर्ण;

काष्ठा nfs_netns_client;

काष्ठा nfs_net अणु
	काष्ठा cache_detail *nfs_dns_resolve;
	काष्ठा rpc_pipe *bl_device_pipe;
	काष्ठा bl_dev_msg bl_mount_reply;
	रुको_queue_head_t bl_wq;
	काष्ठा mutex bl_mutex;
	काष्ठा list_head nfs_client_list;
	काष्ठा list_head nfs_volume_list;
#अगर IS_ENABLED(CONFIG_NFS_V4)
	काष्ठा idr cb_ident_idr; /* Protected by nfs_client_lock */
	अचिन्हित लघु nfs_callback_tcpport;
	अचिन्हित लघु nfs_callback_tcpport6;
	पूर्णांक cb_users[NFS4_MAX_MINOR_VERSION + 1];
#पूर्ण_अगर
	काष्ठा nfs_netns_client *nfs_client;
	spinlock_t nfs_client_lock;
	kसमय_प्रकार boot_समय;
#अगर_घोषित CONFIG_PROC_FS
	काष्ठा proc_dir_entry *proc_nfsfs;
#पूर्ण_अगर
पूर्ण;

बाह्य अचिन्हित पूर्णांक nfs_net_id;

#पूर्ण_अगर
