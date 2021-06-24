<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * tcp.h
 *
 * Function prototypes
 *
 * Copyright (C) 2004 Oracle.  All rights reserved.
 */

#अगर_अघोषित O2CLUSTER_TCP_H
#घोषणा O2CLUSTER_TCP_H

#समावेश <linux/socket.h>
#अगर_घोषित __KERNEL__
#समावेश <net/sock.h>
#समावेश <linux/tcp.h>
#अन्यथा
#समावेश <sys/socket.h>
#पूर्ण_अगर
#समावेश <linux/inet.h>
#समावेश <linux/in.h>

काष्ठा o2net_msg
अणु
	__be16 magic;
	__be16 data_len;
	__be16 msg_type;
	__be16 pad1;
	__be32 sys_status;
	__be32 status;
	__be32 key;
	__be32 msg_num;
	__u8  buf[];
पूर्ण;

प्रकार पूर्णांक (o2net_msg_handler_func)(काष्ठा o2net_msg *msg, u32 len, व्योम *data,
				     व्योम **ret_data);
प्रकार व्योम (o2net_post_msg_handler_func)(पूर्णांक status, व्योम *data,
					   व्योम *ret_data);

#घोषणा O2NET_MAX_PAYLOAD_BYTES  (4096 - माप(काष्ठा o2net_msg))

/* same as hb delay, we're रुकोing क्रम another node to recognize our hb */
#घोषणा O2NET_RECONNECT_DELAY_MS_DEFAULT	2000

#घोषणा O2NET_KEEPALIVE_DELAY_MS_DEFAULT	2000
#घोषणा O2NET_IDLE_TIMEOUT_MS_DEFAULT		30000

#घोषणा O2NET_TCP_USER_TIMEOUT			0x7fffffff

/* TODO: figure this out.... */
अटल अंतरभूत पूर्णांक o2net_link_करोwn(पूर्णांक err, काष्ठा socket *sock)
अणु
	अगर (sock) अणु
		अगर (sock->sk->sk_state != TCP_ESTABLISHED &&
	    	    sock->sk->sk_state != TCP_CLOSE_WAIT)
			वापस 1;
	पूर्ण

	अगर (err >= 0)
		वापस 0;
	चयन (err) अणु
		/* ????????????????????????? */
		हाल -ERESTARTSYS:
		हाल -EBADF:
		/* When the server has died, an ICMP port unreachable
		 * message prompts ECONNREFUSED. */
		हाल -ECONNREFUSED:
		हाल -ENOTCONN:
		हाल -ECONNRESET:
		हाल -EPIPE:
			वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

क्रमागत अणु
	O2NET_DRIVER_UNINITED,
	O2NET_DRIVER_READY,
पूर्ण;

पूर्णांक o2net_send_message(u32 msg_type, u32 key, व्योम *data, u32 len,
		       u8 target_node, पूर्णांक *status);
पूर्णांक o2net_send_message_vec(u32 msg_type, u32 key, काष्ठा kvec *vec,
			   माप_प्रकार veclen, u8 target_node, पूर्णांक *status);

पूर्णांक o2net_रेजिस्टर_handler(u32 msg_type, u32 key, u32 max_len,
			   o2net_msg_handler_func *func, व्योम *data,
			   o2net_post_msg_handler_func *post_func,
			   काष्ठा list_head *unreg_list);
व्योम o2net_unरेजिस्टर_handler_list(काष्ठा list_head *list);

व्योम o2net_fill_node_map(अचिन्हित दीर्घ *map, अचिन्हित bytes);

काष्ठा o2nm_node;
पूर्णांक o2net_रेजिस्टर_hb_callbacks(व्योम);
व्योम o2net_unरेजिस्टर_hb_callbacks(व्योम);
पूर्णांक o2net_start_listening(काष्ठा o2nm_node *node);
व्योम o2net_stop_listening(काष्ठा o2nm_node *node);
व्योम o2net_disconnect_node(काष्ठा o2nm_node *node);
पूर्णांक o2net_num_connected_peers(व्योम);

पूर्णांक o2net_init(व्योम);
व्योम o2net_निकास(व्योम);

काष्ठा o2net_send_tracking;
काष्ठा o2net_sock_container;

#अगर_घोषित CONFIG_DEBUG_FS
व्योम o2net_debugfs_init(व्योम);
व्योम o2net_debugfs_निकास(व्योम);
व्योम o2net_debug_add_nst(काष्ठा o2net_send_tracking *nst);
व्योम o2net_debug_del_nst(काष्ठा o2net_send_tracking *nst);
व्योम o2net_debug_add_sc(काष्ठा o2net_sock_container *sc);
व्योम o2net_debug_del_sc(काष्ठा o2net_sock_container *sc);
#अन्यथा
अटल अंतरभूत व्योम o2net_debugfs_init(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम o2net_debugfs_निकास(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम o2net_debug_add_nst(काष्ठा o2net_send_tracking *nst)
अणु
पूर्ण
अटल अंतरभूत व्योम o2net_debug_del_nst(काष्ठा o2net_send_tracking *nst)
अणु
पूर्ण
अटल अंतरभूत व्योम o2net_debug_add_sc(काष्ठा o2net_sock_container *sc)
अणु
पूर्ण
अटल अंतरभूत व्योम o2net_debug_del_sc(काष्ठा o2net_sock_container *sc)
अणु
पूर्ण
#पूर्ण_अगर	/* CONFIG_DEBUG_FS */

#पूर्ण_अगर /* O2CLUSTER_TCP_H */
