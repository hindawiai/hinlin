<शैली गुरु>
/*
 * Copyright (c) 2018, Mellanox Technologies inc.  All rights reserved.
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

#अगर_अघोषित MLX5_USER_IOCTL_CMDS_H
#घोषणा MLX5_USER_IOCTL_CMDS_H

#समावेश <linux/types.h>
#समावेश <rdma/ib_user_ioctl_cmds.h>

क्रमागत mlx5_ib_create_flow_action_attrs अणु
	/* This attribute beदीर्घ to the driver namespace */
	MLX5_IB_ATTR_CREATE_FLOW_ACTION_FLAGS = (1U << UVERBS_ID_NS_SHIFT),
पूर्ण;

क्रमागत mlx5_ib_dm_methods अणु
	MLX5_IB_METHOD_DM_MAP_OP_ADDR  = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_METHOD_DM_QUERY,
पूर्ण;

क्रमागत mlx5_ib_dm_map_op_addr_attrs अणु
	MLX5_IB_ATTR_DM_MAP_OP_ADDR_REQ_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_DM_MAP_OP_ADDR_REQ_OP,
	MLX5_IB_ATTR_DM_MAP_OP_ADDR_RESP_START_OFFSET,
	MLX5_IB_ATTR_DM_MAP_OP_ADDR_RESP_PAGE_INDEX,
पूर्ण;

क्रमागत mlx5_ib_query_dm_attrs अणु
	MLX5_IB_ATTR_QUERY_DM_REQ_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_QUERY_DM_RESP_START_OFFSET,
	MLX5_IB_ATTR_QUERY_DM_RESP_PAGE_INDEX,
	MLX5_IB_ATTR_QUERY_DM_RESP_LENGTH,
पूर्ण;

क्रमागत mlx5_ib_alloc_dm_attrs अणु
	MLX5_IB_ATTR_ALLOC_DM_RESP_START_OFFSET = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_ALLOC_DM_RESP_PAGE_INDEX,
	MLX5_IB_ATTR_ALLOC_DM_REQ_TYPE,
पूर्ण;

क्रमागत mlx5_ib_devx_methods अणु
	MLX5_IB_METHOD_DEVX_OTHER  = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_METHOD_DEVX_QUERY_UAR,
	MLX5_IB_METHOD_DEVX_QUERY_EQN,
	MLX5_IB_METHOD_DEVX_SUBSCRIBE_EVENT,
पूर्ण;

क्रमागत  mlx5_ib_devx_other_attrs अणु
	MLX5_IB_ATTR_DEVX_OTHER_CMD_IN = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_DEVX_OTHER_CMD_OUT,
पूर्ण;

क्रमागत mlx5_ib_devx_obj_create_attrs अणु
	MLX5_IB_ATTR_DEVX_OBJ_CREATE_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_DEVX_OBJ_CREATE_CMD_IN,
	MLX5_IB_ATTR_DEVX_OBJ_CREATE_CMD_OUT,
पूर्ण;

क्रमागत  mlx5_ib_devx_query_uar_attrs अणु
	MLX5_IB_ATTR_DEVX_QUERY_UAR_USER_IDX = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_DEVX_QUERY_UAR_DEV_IDX,
पूर्ण;

क्रमागत mlx5_ib_devx_obj_destroy_attrs अणु
	MLX5_IB_ATTR_DEVX_OBJ_DESTROY_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
पूर्ण;

क्रमागत mlx5_ib_devx_obj_modअगरy_attrs अणु
	MLX5_IB_ATTR_DEVX_OBJ_MODIFY_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_DEVX_OBJ_MODIFY_CMD_IN,
	MLX5_IB_ATTR_DEVX_OBJ_MODIFY_CMD_OUT,
पूर्ण;

क्रमागत mlx5_ib_devx_obj_query_attrs अणु
	MLX5_IB_ATTR_DEVX_OBJ_QUERY_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_DEVX_OBJ_QUERY_CMD_IN,
	MLX5_IB_ATTR_DEVX_OBJ_QUERY_CMD_OUT,
पूर्ण;

क्रमागत mlx5_ib_devx_obj_query_async_attrs अणु
	MLX5_IB_ATTR_DEVX_OBJ_QUERY_ASYNC_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_DEVX_OBJ_QUERY_ASYNC_CMD_IN,
	MLX5_IB_ATTR_DEVX_OBJ_QUERY_ASYNC_FD,
	MLX5_IB_ATTR_DEVX_OBJ_QUERY_ASYNC_WR_ID,
	MLX5_IB_ATTR_DEVX_OBJ_QUERY_ASYNC_OUT_LEN,
पूर्ण;

क्रमागत mlx5_ib_devx_subscribe_event_attrs अणु
	MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_FD_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_OBJ_HANDLE,
	MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_TYPE_NUM_LIST,
	MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_FD_NUM,
	MLX5_IB_ATTR_DEVX_SUBSCRIBE_EVENT_COOKIE,
पूर्ण;

क्रमागत  mlx5_ib_devx_query_eqn_attrs अणु
	MLX5_IB_ATTR_DEVX_QUERY_EQN_USER_VEC = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_DEVX_QUERY_EQN_DEV_EQN,
पूर्ण;

क्रमागत mlx5_ib_devx_obj_methods अणु
	MLX5_IB_METHOD_DEVX_OBJ_CREATE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_METHOD_DEVX_OBJ_DESTROY,
	MLX5_IB_METHOD_DEVX_OBJ_MODIFY,
	MLX5_IB_METHOD_DEVX_OBJ_QUERY,
	MLX5_IB_METHOD_DEVX_OBJ_ASYNC_QUERY,
पूर्ण;

क्रमागत mlx5_ib_var_alloc_attrs अणु
	MLX5_IB_ATTR_VAR_OBJ_ALLOC_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_VAR_OBJ_ALLOC_MMAP_OFFSET,
	MLX5_IB_ATTR_VAR_OBJ_ALLOC_MMAP_LENGTH,
	MLX5_IB_ATTR_VAR_OBJ_ALLOC_PAGE_ID,
पूर्ण;

क्रमागत mlx5_ib_var_obj_destroy_attrs अणु
	MLX5_IB_ATTR_VAR_OBJ_DESTROY_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
पूर्ण;

क्रमागत mlx5_ib_var_obj_methods अणु
	MLX5_IB_METHOD_VAR_OBJ_ALLOC = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_METHOD_VAR_OBJ_DESTROY,
पूर्ण;

क्रमागत mlx5_ib_uar_alloc_attrs अणु
	MLX5_IB_ATTR_UAR_OBJ_ALLOC_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_UAR_OBJ_ALLOC_TYPE,
	MLX5_IB_ATTR_UAR_OBJ_ALLOC_MMAP_OFFSET,
	MLX5_IB_ATTR_UAR_OBJ_ALLOC_MMAP_LENGTH,
	MLX5_IB_ATTR_UAR_OBJ_ALLOC_PAGE_ID,
पूर्ण;

क्रमागत mlx5_ib_uar_obj_destroy_attrs अणु
	MLX5_IB_ATTR_UAR_OBJ_DESTROY_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
पूर्ण;

क्रमागत mlx5_ib_uar_obj_methods अणु
	MLX5_IB_METHOD_UAR_OBJ_ALLOC = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_METHOD_UAR_OBJ_DESTROY,
पूर्ण;

क्रमागत mlx5_ib_devx_umem_reg_attrs अणु
	MLX5_IB_ATTR_DEVX_UMEM_REG_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_DEVX_UMEM_REG_ADDR,
	MLX5_IB_ATTR_DEVX_UMEM_REG_LEN,
	MLX5_IB_ATTR_DEVX_UMEM_REG_ACCESS,
	MLX5_IB_ATTR_DEVX_UMEM_REG_OUT_ID,
	MLX5_IB_ATTR_DEVX_UMEM_REG_PGSZ_BITMAP,
पूर्ण;

क्रमागत mlx5_ib_devx_umem_dereg_attrs अणु
	MLX5_IB_ATTR_DEVX_UMEM_DEREG_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
पूर्ण;

क्रमागत mlx5_ib_pp_obj_methods अणु
	MLX5_IB_METHOD_PP_OBJ_ALLOC = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_METHOD_PP_OBJ_DESTROY,
पूर्ण;

क्रमागत mlx5_ib_pp_alloc_attrs अणु
	MLX5_IB_ATTR_PP_OBJ_ALLOC_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_PP_OBJ_ALLOC_CTX,
	MLX5_IB_ATTR_PP_OBJ_ALLOC_FLAGS,
	MLX5_IB_ATTR_PP_OBJ_ALLOC_INDEX,
पूर्ण;

क्रमागत mlx5_ib_pp_obj_destroy_attrs अणु
	MLX5_IB_ATTR_PP_OBJ_DESTROY_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
पूर्ण;

क्रमागत mlx5_ib_devx_umem_methods अणु
	MLX5_IB_METHOD_DEVX_UMEM_REG = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_METHOD_DEVX_UMEM_DEREG,
पूर्ण;

क्रमागत mlx5_ib_devx_async_cmd_fd_alloc_attrs अणु
	MLX5_IB_ATTR_DEVX_ASYNC_CMD_FD_ALLOC_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
पूर्ण;

क्रमागत mlx5_ib_devx_async_event_fd_alloc_attrs अणु
	MLX5_IB_ATTR_DEVX_ASYNC_EVENT_FD_ALLOC_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_DEVX_ASYNC_EVENT_FD_ALLOC_FLAGS,
पूर्ण;

क्रमागत mlx5_ib_devx_async_cmd_fd_methods अणु
	MLX5_IB_METHOD_DEVX_ASYNC_CMD_FD_ALLOC = (1U << UVERBS_ID_NS_SHIFT),
पूर्ण;

क्रमागत mlx5_ib_devx_async_event_fd_methods अणु
	MLX5_IB_METHOD_DEVX_ASYNC_EVENT_FD_ALLOC = (1U << UVERBS_ID_NS_SHIFT),
पूर्ण;

क्रमागत mlx5_ib_objects अणु
	MLX5_IB_OBJECT_DEVX = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_OBJECT_DEVX_OBJ,
	MLX5_IB_OBJECT_DEVX_UMEM,
	MLX5_IB_OBJECT_FLOW_MATCHER,
	MLX5_IB_OBJECT_DEVX_ASYNC_CMD_FD,
	MLX5_IB_OBJECT_DEVX_ASYNC_EVENT_FD,
	MLX5_IB_OBJECT_VAR,
	MLX5_IB_OBJECT_PP,
	MLX5_IB_OBJECT_UAR,
पूर्ण;

क्रमागत mlx5_ib_flow_matcher_create_attrs अणु
	MLX5_IB_ATTR_FLOW_MATCHER_CREATE_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_FLOW_MATCHER_MATCH_MASK,
	MLX5_IB_ATTR_FLOW_MATCHER_FLOW_TYPE,
	MLX5_IB_ATTR_FLOW_MATCHER_MATCH_CRITERIA,
	MLX5_IB_ATTR_FLOW_MATCHER_FLOW_FLAGS,
	MLX5_IB_ATTR_FLOW_MATCHER_FT_TYPE,
पूर्ण;

क्रमागत mlx5_ib_flow_matcher_destroy_attrs अणु
	MLX5_IB_ATTR_FLOW_MATCHER_DESTROY_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
पूर्ण;

क्रमागत mlx5_ib_flow_matcher_methods अणु
	MLX5_IB_METHOD_FLOW_MATCHER_CREATE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_METHOD_FLOW_MATCHER_DESTROY,
पूर्ण;

क्रमागत mlx5_ib_device_query_context_attrs अणु
	MLX5_IB_ATTR_QUERY_CONTEXT_RESP_UCTX = (1U << UVERBS_ID_NS_SHIFT),
पूर्ण;

#घोषणा MLX5_IB_DW_MATCH_PARAM 0x90

काष्ठा mlx5_ib_match_params अणु
	__u32	match_params[MLX5_IB_DW_MATCH_PARAM];
पूर्ण;

क्रमागत mlx5_ib_flow_type अणु
	MLX5_IB_FLOW_TYPE_NORMAL,
	MLX5_IB_FLOW_TYPE_SNIFFER,
	MLX5_IB_FLOW_TYPE_ALL_DEFAULT,
	MLX5_IB_FLOW_TYPE_MC_DEFAULT,
पूर्ण;

क्रमागत mlx5_ib_create_flow_flags अणु
	MLX5_IB_ATTR_CREATE_FLOW_FLAGS_DEFAULT_MISS = 1 << 0,
	MLX5_IB_ATTR_CREATE_FLOW_FLAGS_DROP = 1 << 1,
पूर्ण;

क्रमागत mlx5_ib_create_flow_attrs अणु
	MLX5_IB_ATTR_CREATE_FLOW_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_CREATE_FLOW_MATCH_VALUE,
	MLX5_IB_ATTR_CREATE_FLOW_DEST_QP,
	MLX5_IB_ATTR_CREATE_FLOW_DEST_DEVX,
	MLX5_IB_ATTR_CREATE_FLOW_MATCHER,
	MLX5_IB_ATTR_CREATE_FLOW_ARR_FLOW_ACTIONS,
	MLX5_IB_ATTR_CREATE_FLOW_TAG,
	MLX5_IB_ATTR_CREATE_FLOW_ARR_COUNTERS_DEVX,
	MLX5_IB_ATTR_CREATE_FLOW_ARR_COUNTERS_DEVX_OFFSET,
	MLX5_IB_ATTR_CREATE_FLOW_FLAGS,
पूर्ण;

क्रमागत mlx5_ib_destroy_flow_attrs अणु
	MLX5_IB_ATTR_DESTROY_FLOW_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
पूर्ण;

क्रमागत mlx5_ib_flow_methods अणु
	MLX5_IB_METHOD_CREATE_FLOW = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_METHOD_DESTROY_FLOW,
पूर्ण;

क्रमागत mlx5_ib_flow_action_methods अणु
	MLX5_IB_METHOD_FLOW_ACTION_CREATE_MODIFY_HEADER = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_METHOD_FLOW_ACTION_CREATE_PACKET_REFORMAT,
पूर्ण;

क्रमागत mlx5_ib_create_flow_action_create_modअगरy_header_attrs अणु
	MLX5_IB_ATTR_CREATE_MODIFY_HEADER_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_CREATE_MODIFY_HEADER_ACTIONS_PRM,
	MLX5_IB_ATTR_CREATE_MODIFY_HEADER_FT_TYPE,
पूर्ण;

क्रमागत mlx5_ib_create_flow_action_create_packet_reक्रमmat_attrs अणु
	MLX5_IB_ATTR_CREATE_PACKET_REFORMAT_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_CREATE_PACKET_REFORMAT_TYPE,
	MLX5_IB_ATTR_CREATE_PACKET_REFORMAT_FT_TYPE,
	MLX5_IB_ATTR_CREATE_PACKET_REFORMAT_DATA_BUF,
पूर्ण;

क्रमागत mlx5_ib_query_pd_attrs अणु
	MLX5_IB_ATTR_QUERY_PD_HANDLE = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_QUERY_PD_RESP_PDN,
पूर्ण;

क्रमागत mlx5_ib_pd_methods अणु
	MLX5_IB_METHOD_PD_QUERY = (1U << UVERBS_ID_NS_SHIFT),

पूर्ण;

क्रमागत mlx5_ib_device_methods अणु
	MLX5_IB_METHOD_QUERY_PORT = (1U << UVERBS_ID_NS_SHIFT),
पूर्ण;

क्रमागत mlx5_ib_query_port_attrs अणु
	MLX5_IB_ATTR_QUERY_PORT_PORT_NUM = (1U << UVERBS_ID_NS_SHIFT),
	MLX5_IB_ATTR_QUERY_PORT,
पूर्ण;

#पूर्ण_अगर
