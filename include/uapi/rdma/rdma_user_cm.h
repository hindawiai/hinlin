<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR Linux-OpenIB) */
/*
 * Copyright (c) 2005-2006 Intel Corporation.  All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित RDMA_USER_CM_H
#घोषणा RDMA_USER_CM_H

#समावेश <linux/types.h>
#समावेश <linux/socket.h>
#समावेश <linux/in6.h>
#समावेश <rdma/ib_user_verbs.h>
#समावेश <rdma/ib_user_sa.h>

#घोषणा RDMA_USER_CM_ABI_VERSION	4

#घोषणा RDMA_MAX_PRIVATE_DATA		256

क्रमागत अणु
	RDMA_USER_CM_CMD_CREATE_ID,
	RDMA_USER_CM_CMD_DESTROY_ID,
	RDMA_USER_CM_CMD_BIND_IP,
	RDMA_USER_CM_CMD_RESOLVE_IP,
	RDMA_USER_CM_CMD_RESOLVE_ROUTE,
	RDMA_USER_CM_CMD_QUERY_ROUTE,
	RDMA_USER_CM_CMD_CONNECT,
	RDMA_USER_CM_CMD_LISTEN,
	RDMA_USER_CM_CMD_ACCEPT,
	RDMA_USER_CM_CMD_REJECT,
	RDMA_USER_CM_CMD_DISCONNECT,
	RDMA_USER_CM_CMD_INIT_QP_ATTR,
	RDMA_USER_CM_CMD_GET_EVENT,
	RDMA_USER_CM_CMD_GET_OPTION,
	RDMA_USER_CM_CMD_SET_OPTION,
	RDMA_USER_CM_CMD_NOTIFY,
	RDMA_USER_CM_CMD_JOIN_IP_MCAST,
	RDMA_USER_CM_CMD_LEAVE_MCAST,
	RDMA_USER_CM_CMD_MIGRATE_ID,
	RDMA_USER_CM_CMD_QUERY,
	RDMA_USER_CM_CMD_BIND,
	RDMA_USER_CM_CMD_RESOLVE_ADDR,
	RDMA_USER_CM_CMD_JOIN_MCAST
पूर्ण;

/* See IBTA Annex A11, servies ID bytes 4 & 5 */
क्रमागत rdma_ucm_port_space अणु
	RDMA_PS_IPOIB = 0x0002,
	RDMA_PS_IB    = 0x013F,
	RDMA_PS_TCP   = 0x0106,
	RDMA_PS_UDP   = 0x0111,
पूर्ण;

/*
 * command ABI काष्ठाures.
 */
काष्ठा rdma_ucm_cmd_hdr अणु
	__u32 cmd;
	__u16 in;
	__u16 out;
पूर्ण;

काष्ठा rdma_ucm_create_id अणु
	__aligned_u64 uid;
	__aligned_u64 response;
	__u16 ps;                  /* use क्रमागत rdma_ucm_port_space */
	__u8  qp_type;
	__u8  reserved[5];
पूर्ण;

काष्ठा rdma_ucm_create_id_resp अणु
	__u32 id;
पूर्ण;

काष्ठा rdma_ucm_destroy_id अणु
	__aligned_u64 response;
	__u32 id;
	__u32 reserved;
पूर्ण;

काष्ठा rdma_ucm_destroy_id_resp अणु
	__u32 events_reported;
पूर्ण;

काष्ठा rdma_ucm_bind_ip अणु
	__aligned_u64 response;
	काष्ठा sockaddr_in6 addr;
	__u32 id;
पूर्ण;

काष्ठा rdma_ucm_bind अणु
	__u32 id;
	__u16 addr_size;
	__u16 reserved;
	काष्ठा __kernel_sockaddr_storage addr;
पूर्ण;

काष्ठा rdma_ucm_resolve_ip अणु
	काष्ठा sockaddr_in6 src_addr;
	काष्ठा sockaddr_in6 dst_addr;
	__u32 id;
	__u32 समयout_ms;
पूर्ण;

काष्ठा rdma_ucm_resolve_addr अणु
	__u32 id;
	__u32 समयout_ms;
	__u16 src_size;
	__u16 dst_size;
	__u32 reserved;
	काष्ठा __kernel_sockaddr_storage src_addr;
	काष्ठा __kernel_sockaddr_storage dst_addr;
पूर्ण;

काष्ठा rdma_ucm_resolve_route अणु
	__u32 id;
	__u32 समयout_ms;
पूर्ण;

क्रमागत अणु
	RDMA_USER_CM_QUERY_ADDR,
	RDMA_USER_CM_QUERY_PATH,
	RDMA_USER_CM_QUERY_GID
पूर्ण;

काष्ठा rdma_ucm_query अणु
	__aligned_u64 response;
	__u32 id;
	__u32 option;
पूर्ण;

काष्ठा rdma_ucm_query_route_resp अणु
	__aligned_u64 node_guid;
	काष्ठा ib_user_path_rec ib_route[2];
	काष्ठा sockaddr_in6 src_addr;
	काष्ठा sockaddr_in6 dst_addr;
	__u32 num_paths;
	__u8 port_num;
	__u8 reserved[3];
	__u32 ibdev_index;
	__u32 reserved1;
पूर्ण;

काष्ठा rdma_ucm_query_addr_resp अणु
	__aligned_u64 node_guid;
	__u8  port_num;
	__u8  reserved;
	__u16 pkey;
	__u16 src_size;
	__u16 dst_size;
	काष्ठा __kernel_sockaddr_storage src_addr;
	काष्ठा __kernel_sockaddr_storage dst_addr;
	__u32 ibdev_index;
	__u32 reserved1;
पूर्ण;

काष्ठा rdma_ucm_query_path_resp अणु
	__u32 num_paths;
	__u32 reserved;
	काष्ठा ib_path_rec_data path_data[0];
पूर्ण;

काष्ठा rdma_ucm_conn_param अणु
	__u32 qp_num;
	__u32 qkey;
	__u8  निजी_data[RDMA_MAX_PRIVATE_DATA];
	__u8  निजी_data_len;
	__u8  srq;
	__u8  responder_resources;
	__u8  initiator_depth;
	__u8  flow_control;
	__u8  retry_count;
	__u8  rnr_retry_count;
	__u8  valid;
पूर्ण;

काष्ठा rdma_ucm_ud_param अणु
	__u32 qp_num;
	__u32 qkey;
	काष्ठा ib_uverbs_ah_attr ah_attr;
	__u8  निजी_data[RDMA_MAX_PRIVATE_DATA];
	__u8  निजी_data_len;
	__u8  reserved[7];
पूर्ण;

काष्ठा rdma_ucm_ece अणु
	__u32 venकरोr_id;
	__u32 attr_mod;
पूर्ण;

काष्ठा rdma_ucm_connect अणु
	काष्ठा rdma_ucm_conn_param conn_param;
	__u32 id;
	__u32 reserved;
	काष्ठा rdma_ucm_ece ece;
पूर्ण;

काष्ठा rdma_ucm_listen अणु
	__u32 id;
	__u32 backlog;
पूर्ण;

काष्ठा rdma_ucm_accept अणु
	__aligned_u64 uid;
	काष्ठा rdma_ucm_conn_param conn_param;
	__u32 id;
	__u32 reserved;
	काष्ठा rdma_ucm_ece ece;
पूर्ण;

काष्ठा rdma_ucm_reject अणु
	__u32 id;
	__u8  निजी_data_len;
	__u8  reason;
	__u8  reserved[2];
	__u8  निजी_data[RDMA_MAX_PRIVATE_DATA];
पूर्ण;

काष्ठा rdma_ucm_disconnect अणु
	__u32 id;
पूर्ण;

काष्ठा rdma_ucm_init_qp_attr अणु
	__aligned_u64 response;
	__u32 id;
	__u32 qp_state;
पूर्ण;

काष्ठा rdma_ucm_notअगरy अणु
	__u32 id;
	__u32 event;
पूर्ण;

काष्ठा rdma_ucm_join_ip_mcast अणु
	__aligned_u64 response;		/* rdma_ucm_create_id_resp */
	__aligned_u64 uid;
	काष्ठा sockaddr_in6 addr;
	__u32 id;
पूर्ण;

/* Multicast join flags */
क्रमागत अणु
	RDMA_MC_JOIN_FLAG_FULLMEMBER,
	RDMA_MC_JOIN_FLAG_SENDONLY_FULLMEMBER,
	RDMA_MC_JOIN_FLAG_RESERVED,
पूर्ण;

काष्ठा rdma_ucm_join_mcast अणु
	__aligned_u64 response;		/* rdma_ucma_create_id_resp */
	__aligned_u64 uid;
	__u32 id;
	__u16 addr_size;
	__u16 join_flags;
	काष्ठा __kernel_sockaddr_storage addr;
पूर्ण;

काष्ठा rdma_ucm_get_event अणु
	__aligned_u64 response;
पूर्ण;

काष्ठा rdma_ucm_event_resp अणु
	__aligned_u64 uid;
	__u32 id;
	__u32 event;
	__u32 status;
	/*
	 * NOTE: This जोड़ is not aligned to 8 bytes so none of the जोड़
	 * members may contain a u64 or anything with higher alignment than 4.
	 */
	जोड़ अणु
		काष्ठा rdma_ucm_conn_param conn;
		काष्ठा rdma_ucm_ud_param   ud;
	पूर्ण param;
	__u32 reserved;
	काष्ठा rdma_ucm_ece ece;
पूर्ण;

/* Option levels */
क्रमागत अणु
	RDMA_OPTION_ID		= 0,
	RDMA_OPTION_IB		= 1
पूर्ण;

/* Option details */
क्रमागत अणु
	RDMA_OPTION_ID_TOS	 = 0,
	RDMA_OPTION_ID_REUSEADDR = 1,
	RDMA_OPTION_ID_AFONLY	 = 2,
	RDMA_OPTION_ID_ACK_TIMEOUT = 3
पूर्ण;

क्रमागत अणु
	RDMA_OPTION_IB_PATH	 = 1
पूर्ण;

काष्ठा rdma_ucm_set_option अणु
	__aligned_u64 optval;
	__u32 id;
	__u32 level;
	__u32 optname;
	__u32 optlen;
पूर्ण;

काष्ठा rdma_ucm_migrate_id अणु
	__aligned_u64 response;
	__u32 id;
	__u32 fd;
पूर्ण;

काष्ठा rdma_ucm_migrate_resp अणु
	__u32 events_reported;
पूर्ण;

#पूर्ण_अगर /* RDMA_USER_CM_H */
