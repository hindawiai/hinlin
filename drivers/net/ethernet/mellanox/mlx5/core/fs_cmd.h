<शैली गुरु>
/*
 * Copyright (c) 2015, Mellanox Technologies. All rights reserved.
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

#अगर_अघोषित _MLX5_FS_CMD_
#घोषणा _MLX5_FS_CMD_

#समावेश "fs_core.h"

काष्ठा mlx5_flow_cmds अणु
	पूर्णांक (*create_flow_table)(काष्ठा mlx5_flow_root_namespace *ns,
				 काष्ठा mlx5_flow_table *ft,
				 अचिन्हित पूर्णांक log_size,
				 काष्ठा mlx5_flow_table *next_ft);
	पूर्णांक (*destroy_flow_table)(काष्ठा mlx5_flow_root_namespace *ns,
				  काष्ठा mlx5_flow_table *ft);

	पूर्णांक (*modअगरy_flow_table)(काष्ठा mlx5_flow_root_namespace *ns,
				 काष्ठा mlx5_flow_table *ft,
				 काष्ठा mlx5_flow_table *next_ft);

	पूर्णांक (*create_flow_group)(काष्ठा mlx5_flow_root_namespace *ns,
				 काष्ठा mlx5_flow_table *ft,
				 u32 *in,
				 काष्ठा mlx5_flow_group *fg);

	पूर्णांक (*destroy_flow_group)(काष्ठा mlx5_flow_root_namespace *ns,
				  काष्ठा mlx5_flow_table *ft,
				  काष्ठा mlx5_flow_group *fg);

	पूर्णांक (*create_fte)(काष्ठा mlx5_flow_root_namespace *ns,
			  काष्ठा mlx5_flow_table *ft,
			  काष्ठा mlx5_flow_group *fg,
			  काष्ठा fs_fte *fte);

	पूर्णांक (*update_fte)(काष्ठा mlx5_flow_root_namespace *ns,
			  काष्ठा mlx5_flow_table *ft,
			  काष्ठा mlx5_flow_group *fg,
			  पूर्णांक modअगरy_mask,
			  काष्ठा fs_fte *fte);

	पूर्णांक (*delete_fte)(काष्ठा mlx5_flow_root_namespace *ns,
			  काष्ठा mlx5_flow_table *ft,
			  काष्ठा fs_fte *fte);

	पूर्णांक (*update_root_ft)(काष्ठा mlx5_flow_root_namespace *ns,
			      काष्ठा mlx5_flow_table *ft,
			      u32 underlay_qpn,
			      bool disconnect);

	पूर्णांक (*packet_reक्रमmat_alloc)(काष्ठा mlx5_flow_root_namespace *ns,
				     पूर्णांक reक्रमmat_type,
				     माप_प्रकार size,
				     व्योम *reक्रमmat_data,
				     क्रमागत mlx5_flow_namespace_type namespace,
				     काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat);

	व्योम (*packet_reक्रमmat_dealloc)(काष्ठा mlx5_flow_root_namespace *ns,
					काष्ठा mlx5_pkt_reक्रमmat *pkt_reक्रमmat);

	पूर्णांक (*modअगरy_header_alloc)(काष्ठा mlx5_flow_root_namespace *ns,
				   u8 namespace, u8 num_actions,
				   व्योम *modअगरy_actions,
				   काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr);

	व्योम (*modअगरy_header_dealloc)(काष्ठा mlx5_flow_root_namespace *ns,
				      काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr);

	पूर्णांक (*set_peer)(काष्ठा mlx5_flow_root_namespace *ns,
			काष्ठा mlx5_flow_root_namespace *peer_ns);

	पूर्णांक (*create_ns)(काष्ठा mlx5_flow_root_namespace *ns);
	पूर्णांक (*destroy_ns)(काष्ठा mlx5_flow_root_namespace *ns);
पूर्ण;

पूर्णांक mlx5_cmd_fc_alloc(काष्ठा mlx5_core_dev *dev, u32 *id);
पूर्णांक mlx5_cmd_fc_bulk_alloc(काष्ठा mlx5_core_dev *dev,
			   क्रमागत mlx5_fc_bulk_alloc_biपंचांगask alloc_biपंचांगask,
			   u32 *id);
पूर्णांक mlx5_cmd_fc_मुक्त(काष्ठा mlx5_core_dev *dev, u32 id);
पूर्णांक mlx5_cmd_fc_query(काष्ठा mlx5_core_dev *dev, u32 id,
		      u64 *packets, u64 *bytes);

पूर्णांक mlx5_cmd_fc_get_bulk_query_out_len(पूर्णांक bulk_len);
पूर्णांक mlx5_cmd_fc_bulk_query(काष्ठा mlx5_core_dev *dev, u32 base_id, पूर्णांक bulk_len,
			   u32 *out);

स्थिर काष्ठा mlx5_flow_cmds *mlx5_fs_cmd_get_शेष(क्रमागत fs_flow_table_type type);
स्थिर काष्ठा mlx5_flow_cmds *mlx5_fs_cmd_get_fw_cmds(व्योम);

#पूर्ण_अगर
