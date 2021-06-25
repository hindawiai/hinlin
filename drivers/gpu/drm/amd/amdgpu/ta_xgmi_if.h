<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित _TA_XGMI_IF_H
#घोषणा _TA_XGMI_IF_H

/* Responses have bit 31 set */
#घोषणा RSP_ID_MASK (1U << 31)
#घोषणा RSP_ID(cmdId) (((uपूर्णांक32_t)(cmdId)) | RSP_ID_MASK)

क्रमागत ta_command_xgmi अणु
	TA_COMMAND_XGMI__INITIALIZE			= 0x00,
	TA_COMMAND_XGMI__GET_NODE_ID			= 0x01,
	TA_COMMAND_XGMI__GET_HIVE_ID			= 0x02,
	TA_COMMAND_XGMI__GET_GET_TOPOLOGY_INFO		= 0x03,
	TA_COMMAND_XGMI__SET_TOPOLOGY_INFO		= 0x04
पूर्ण;

/* XGMI related क्रमागतerations */
/**********************************************************/;
क्रमागत ta_xgmi_connected_nodes अणु
	TA_XGMI__MAX_CONNECTED_NODES			= 64
पूर्ण;

क्रमागत ta_xgmi_status अणु
	TA_XGMI_STATUS__SUCCESS				= 0x00,
	TA_XGMI_STATUS__GENERIC_FAILURE			= 0x01,
	TA_XGMI_STATUS__शून्य_POINTER			= 0x02,
	TA_XGMI_STATUS__INVALID_PARAMETER		= 0x03,
	TA_XGMI_STATUS__NOT_INITIALIZED			= 0x04,
	TA_XGMI_STATUS__INVALID_NODE_NUM		= 0x05,
	TA_XGMI_STATUS__INVALID_NODE_ID			= 0x06,
	TA_XGMI_STATUS__INVALID_TOPOLOGY		= 0x07,
	TA_XGMI_STATUS__FAILED_ID_GEN			= 0x08,
	TA_XGMI_STATUS__FAILED_TOPOLOGY_INIT		= 0x09,
	TA_XGMI_STATUS__SET_SHARING_ERROR		= 0x0A
पूर्ण;

क्रमागत ta_xgmi_asचिन्हित_sdma_engine अणु
	TA_XGMI_ASSIGNED_SDMA_ENGINE__NOT_ASSIGNED	= -1,
	TA_XGMI_ASSIGNED_SDMA_ENGINE__SDMA0		= 0,
	TA_XGMI_ASSIGNED_SDMA_ENGINE__SDMA1		= 1,
	TA_XGMI_ASSIGNED_SDMA_ENGINE__SDMA2		= 2,
	TA_XGMI_ASSIGNED_SDMA_ENGINE__SDMA3		= 3,
	TA_XGMI_ASSIGNED_SDMA_ENGINE__SDMA4		= 4,
	TA_XGMI_ASSIGNED_SDMA_ENGINE__SDMA5		= 5
पूर्ण;

/* input/output काष्ठाures क्रम XGMI commands */
/**********************************************************/
काष्ठा ta_xgmi_node_info अणु
	uपूर्णांक64_t				node_id;
	uपूर्णांक8_t					num_hops;
	uपूर्णांक8_t					is_sharing_enabled;
	क्रमागत ta_xgmi_asचिन्हित_sdma_engine	sdma_engine;
पूर्ण;

काष्ठा ta_xgmi_cmd_initialize_output अणु
	uपूर्णांक32_t	status;
पूर्ण;

काष्ठा ta_xgmi_cmd_get_node_id_output अणु
	uपूर्णांक64_t	node_id;
पूर्ण;

काष्ठा ta_xgmi_cmd_get_hive_id_output अणु
	uपूर्णांक64_t	hive_id;
पूर्ण;

काष्ठा ta_xgmi_cmd_get_topology_info_input अणु
	uपूर्णांक32_t			num_nodes;
	काष्ठा ta_xgmi_node_info	nodes[TA_XGMI__MAX_CONNECTED_NODES];
पूर्ण;

काष्ठा ta_xgmi_cmd_get_topology_info_output अणु
	uपूर्णांक32_t			num_nodes;
	काष्ठा ta_xgmi_node_info	nodes[TA_XGMI__MAX_CONNECTED_NODES];
पूर्ण;

काष्ठा ta_xgmi_cmd_set_topology_info_input अणु
	uपूर्णांक32_t			num_nodes;
	काष्ठा ta_xgmi_node_info	nodes[TA_XGMI__MAX_CONNECTED_NODES];
पूर्ण;

/**********************************************************/
/* Common input काष्ठाure क्रम XGMI callbacks */
जोड़ ta_xgmi_cmd_input अणु
	काष्ठा ta_xgmi_cmd_get_topology_info_input	get_topology_info;
	काष्ठा ta_xgmi_cmd_set_topology_info_input	set_topology_info;
पूर्ण;

/* Common output काष्ठाure क्रम XGMI callbacks */
जोड़ ta_xgmi_cmd_output अणु
	काष्ठा ta_xgmi_cmd_initialize_output		initialize;
	काष्ठा ta_xgmi_cmd_get_node_id_output		get_node_id;
	काष्ठा ta_xgmi_cmd_get_hive_id_output		get_hive_id;
	काष्ठा ta_xgmi_cmd_get_topology_info_output	get_topology_info;
पूर्ण;
/**********************************************************/

काष्ठा ta_xgmi_shared_memory अणु
	uपूर्णांक32_t			cmd_id;
	uपूर्णांक32_t			resp_id;
	क्रमागत ta_xgmi_status		xgmi_status;
	uपूर्णांक32_t			reserved;
	जोड़ ta_xgmi_cmd_input		xgmi_in_message;
	जोड़ ta_xgmi_cmd_output	xgmi_out_message;
पूर्ण;

#पूर्ण_अगर   //_TA_XGMI_IF_H
