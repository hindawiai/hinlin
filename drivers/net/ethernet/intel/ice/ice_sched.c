<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Intel Corporation. */

#समावेश "ice_sched.h"

/**
 * ice_sched_add_root_node - Insert the Tx scheduler root node in SW DB
 * @pi: port inक्रमmation काष्ठाure
 * @info: Scheduler element inक्रमmation from firmware
 *
 * This function inserts the root node of the scheduling tree topology
 * to the SW DB.
 */
अटल क्रमागत ice_status
ice_sched_add_root_node(काष्ठा ice_port_info *pi,
			काष्ठा ice_aqc_txsched_elem_data *info)
अणु
	काष्ठा ice_sched_node *root;
	काष्ठा ice_hw *hw;

	अगर (!pi)
		वापस ICE_ERR_PARAM;

	hw = pi->hw;

	root = devm_kzalloc(ice_hw_to_dev(hw), माप(*root), GFP_KERNEL);
	अगर (!root)
		वापस ICE_ERR_NO_MEMORY;

	/* coverity[suspicious_माप] */
	root->children = devm_kसुस्मृति(ice_hw_to_dev(hw), hw->max_children[0],
				      माप(*root), GFP_KERNEL);
	अगर (!root->children) अणु
		devm_kमुक्त(ice_hw_to_dev(hw), root);
		वापस ICE_ERR_NO_MEMORY;
	पूर्ण

	स_नकल(&root->info, info, माप(*info));
	pi->root = root;
	वापस 0;
पूर्ण

/**
 * ice_sched_find_node_by_teid - Find the Tx scheduler node in SW DB
 * @start_node: poपूर्णांकer to the starting ice_sched_node काष्ठा in a sub-tree
 * @teid: node TEID to search
 *
 * This function searches क्रम a node matching the TEID in the scheduling tree
 * from the SW DB. The search is recursive and is restricted by the number of
 * layers it has searched through; stopping at the max supported layer.
 *
 * This function needs to be called when holding the port_info->sched_lock
 */
काष्ठा ice_sched_node *
ice_sched_find_node_by_teid(काष्ठा ice_sched_node *start_node, u32 teid)
अणु
	u16 i;

	/* The TEID is same as that of the start_node */
	अगर (ICE_TXSCHED_GET_NODE_TEID(start_node) == teid)
		वापस start_node;

	/* The node has no children or is at the max layer */
	अगर (!start_node->num_children ||
	    start_node->tx_sched_layer >= ICE_AQC_TOPO_MAX_LEVEL_NUM ||
	    start_node->info.data.elem_type == ICE_AQC_ELEM_TYPE_LEAF)
		वापस शून्य;

	/* Check अगर TEID matches to any of the children nodes */
	क्रम (i = 0; i < start_node->num_children; i++)
		अगर (ICE_TXSCHED_GET_NODE_TEID(start_node->children[i]) == teid)
			वापस start_node->children[i];

	/* Search within each child's sub-tree */
	क्रम (i = 0; i < start_node->num_children; i++) अणु
		काष्ठा ice_sched_node *पंचांगp;

		पंचांगp = ice_sched_find_node_by_teid(start_node->children[i],
						  teid);
		अगर (पंचांगp)
			वापस पंचांगp;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * ice_aqc_send_sched_elem_cmd - send scheduling elements cmd
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @cmd_opc: cmd opcode
 * @elems_req: number of elements to request
 * @buf: poपूर्णांकer to buffer
 * @buf_size: buffer size in bytes
 * @elems_resp: वापसs total number of elements response
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * This function sends a scheduling elements cmd (cmd_opc)
 */
अटल क्रमागत ice_status
ice_aqc_send_sched_elem_cmd(काष्ठा ice_hw *hw, क्रमागत ice_adminq_opc cmd_opc,
			    u16 elems_req, व्योम *buf, u16 buf_size,
			    u16 *elems_resp, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_sched_elem_cmd *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	cmd = &desc.params.sched_elem_cmd;
	ice_fill_dflt_direct_cmd_desc(&desc, cmd_opc);
	cmd->num_elem_req = cpu_to_le16(elems_req);
	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);
	status = ice_aq_send_cmd(hw, &desc, buf, buf_size, cd);
	अगर (!status && elems_resp)
		*elems_resp = le16_to_cpu(cmd->num_elem_resp);

	वापस status;
पूर्ण

/**
 * ice_aq_query_sched_elems - query scheduler elements
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @elems_req: number of elements to query
 * @buf: poपूर्णांकer to buffer
 * @buf_size: buffer size in bytes
 * @elems_ret: वापसs total number of elements वापसed
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Query scheduling elements (0x0404)
 */
क्रमागत ice_status
ice_aq_query_sched_elems(काष्ठा ice_hw *hw, u16 elems_req,
			 काष्ठा ice_aqc_txsched_elem_data *buf, u16 buf_size,
			 u16 *elems_ret, काष्ठा ice_sq_cd *cd)
अणु
	वापस ice_aqc_send_sched_elem_cmd(hw, ice_aqc_opc_get_sched_elems,
					   elems_req, (व्योम *)buf, buf_size,
					   elems_ret, cd);
पूर्ण

/**
 * ice_sched_add_node - Insert the Tx scheduler node in SW DB
 * @pi: port inक्रमmation काष्ठाure
 * @layer: Scheduler layer of the node
 * @info: Scheduler element inक्रमmation from firmware
 *
 * This function inserts a scheduler node to the SW DB.
 */
क्रमागत ice_status
ice_sched_add_node(काष्ठा ice_port_info *pi, u8 layer,
		   काष्ठा ice_aqc_txsched_elem_data *info)
अणु
	काष्ठा ice_aqc_txsched_elem_data elem;
	काष्ठा ice_sched_node *parent;
	काष्ठा ice_sched_node *node;
	क्रमागत ice_status status;
	काष्ठा ice_hw *hw;

	अगर (!pi)
		वापस ICE_ERR_PARAM;

	hw = pi->hw;

	/* A valid parent node should be there */
	parent = ice_sched_find_node_by_teid(pi->root,
					     le32_to_cpu(info->parent_teid));
	अगर (!parent) अणु
		ice_debug(hw, ICE_DBG_SCHED, "Parent Node not found for parent_teid=0x%x\n",
			  le32_to_cpu(info->parent_teid));
		वापस ICE_ERR_PARAM;
	पूर्ण

	/* query the current node inक्रमmation from FW beक्रमe adding it
	 * to the SW DB
	 */
	status = ice_sched_query_elem(hw, le32_to_cpu(info->node_teid), &elem);
	अगर (status)
		वापस status;

	node = devm_kzalloc(ice_hw_to_dev(hw), माप(*node), GFP_KERNEL);
	अगर (!node)
		वापस ICE_ERR_NO_MEMORY;
	अगर (hw->max_children[layer]) अणु
		/* coverity[suspicious_माप] */
		node->children = devm_kसुस्मृति(ice_hw_to_dev(hw),
					      hw->max_children[layer],
					      माप(*node), GFP_KERNEL);
		अगर (!node->children) अणु
			devm_kमुक्त(ice_hw_to_dev(hw), node);
			वापस ICE_ERR_NO_MEMORY;
		पूर्ण
	पूर्ण

	node->in_use = true;
	node->parent = parent;
	node->tx_sched_layer = layer;
	parent->children[parent->num_children++] = node;
	node->info = elem;
	वापस 0;
पूर्ण

/**
 * ice_aq_delete_sched_elems - delete scheduler elements
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @grps_req: number of groups to delete
 * @buf: poपूर्णांकer to buffer
 * @buf_size: buffer size in bytes
 * @grps_del: वापसs total number of elements deleted
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Delete scheduling elements (0x040F)
 */
अटल क्रमागत ice_status
ice_aq_delete_sched_elems(काष्ठा ice_hw *hw, u16 grps_req,
			  काष्ठा ice_aqc_delete_elem *buf, u16 buf_size,
			  u16 *grps_del, काष्ठा ice_sq_cd *cd)
अणु
	वापस ice_aqc_send_sched_elem_cmd(hw, ice_aqc_opc_delete_sched_elems,
					   grps_req, (व्योम *)buf, buf_size,
					   grps_del, cd);
पूर्ण

/**
 * ice_sched_हटाओ_elems - हटाओ nodes from HW
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @parent: poपूर्णांकer to the parent node
 * @num_nodes: number of nodes
 * @node_teids: array of node teids to be deleted
 *
 * This function हटाओ nodes from HW
 */
अटल क्रमागत ice_status
ice_sched_हटाओ_elems(काष्ठा ice_hw *hw, काष्ठा ice_sched_node *parent,
		       u16 num_nodes, u32 *node_teids)
अणु
	काष्ठा ice_aqc_delete_elem *buf;
	u16 i, num_groups_हटाओd = 0;
	क्रमागत ice_status status;
	u16 buf_size;

	buf_size = काष्ठा_size(buf, teid, num_nodes);
	buf = devm_kzalloc(ice_hw_to_dev(hw), buf_size, GFP_KERNEL);
	अगर (!buf)
		वापस ICE_ERR_NO_MEMORY;

	buf->hdr.parent_teid = parent->info.node_teid;
	buf->hdr.num_elems = cpu_to_le16(num_nodes);
	क्रम (i = 0; i < num_nodes; i++)
		buf->teid[i] = cpu_to_le32(node_teids[i]);

	status = ice_aq_delete_sched_elems(hw, 1, buf, buf_size,
					   &num_groups_हटाओd, शून्य);
	अगर (status || num_groups_हटाओd != 1)
		ice_debug(hw, ICE_DBG_SCHED, "remove node failed FW error %d\n",
			  hw->adminq.sq_last_status);

	devm_kमुक्त(ice_hw_to_dev(hw), buf);
	वापस status;
पूर्ण

/**
 * ice_sched_get_first_node - get the first node of the given layer
 * @pi: port inक्रमmation काष्ठाure
 * @parent: poपूर्णांकer the base node of the subtree
 * @layer: layer number
 *
 * This function retrieves the first node of the given layer from the subtree
 */
अटल काष्ठा ice_sched_node *
ice_sched_get_first_node(काष्ठा ice_port_info *pi,
			 काष्ठा ice_sched_node *parent, u8 layer)
अणु
	वापस pi->sib_head[parent->tc_num][layer];
पूर्ण

/**
 * ice_sched_get_tc_node - get poपूर्णांकer to TC node
 * @pi: port inक्रमmation काष्ठाure
 * @tc: TC number
 *
 * This function वापसs the TC node poपूर्णांकer
 */
काष्ठा ice_sched_node *ice_sched_get_tc_node(काष्ठा ice_port_info *pi, u8 tc)
अणु
	u8 i;

	अगर (!pi || !pi->root)
		वापस शून्य;
	क्रम (i = 0; i < pi->root->num_children; i++)
		अगर (pi->root->children[i]->tc_num == tc)
			वापस pi->root->children[i];
	वापस शून्य;
पूर्ण

/**
 * ice_मुक्त_sched_node - Free a Tx scheduler node from SW DB
 * @pi: port inक्रमmation काष्ठाure
 * @node: poपूर्णांकer to the ice_sched_node काष्ठा
 *
 * This function मुक्तs up a node from SW DB as well as from HW
 *
 * This function needs to be called with the port_info->sched_lock held
 */
व्योम ice_मुक्त_sched_node(काष्ठा ice_port_info *pi, काष्ठा ice_sched_node *node)
अणु
	काष्ठा ice_sched_node *parent;
	काष्ठा ice_hw *hw = pi->hw;
	u8 i, j;

	/* Free the children beक्रमe मुक्तing up the parent node
	 * The parent array is updated below and that shअगरts the nodes
	 * in the array. So always pick the first child अगर num children > 0
	 */
	जबतक (node->num_children)
		ice_मुक्त_sched_node(pi, node->children[0]);

	/* Leaf, TC and root nodes can't be deleted by SW */
	अगर (node->tx_sched_layer >= hw->sw_entry_poपूर्णांक_layer &&
	    node->info.data.elem_type != ICE_AQC_ELEM_TYPE_TC &&
	    node->info.data.elem_type != ICE_AQC_ELEM_TYPE_ROOT_PORT &&
	    node->info.data.elem_type != ICE_AQC_ELEM_TYPE_LEAF) अणु
		u32 teid = le32_to_cpu(node->info.node_teid);

		ice_sched_हटाओ_elems(hw, node->parent, 1, &teid);
	पूर्ण
	parent = node->parent;
	/* root has no parent */
	अगर (parent) अणु
		काष्ठा ice_sched_node *p;

		/* update the parent */
		क्रम (i = 0; i < parent->num_children; i++)
			अगर (parent->children[i] == node) अणु
				क्रम (j = i + 1; j < parent->num_children; j++)
					parent->children[j - 1] =
						parent->children[j];
				parent->num_children--;
				अवरोध;
			पूर्ण

		p = ice_sched_get_first_node(pi, node, node->tx_sched_layer);
		जबतक (p) अणु
			अगर (p->sibling == node) अणु
				p->sibling = node->sibling;
				अवरोध;
			पूर्ण
			p = p->sibling;
		पूर्ण

		/* update the sibling head अगर head is getting हटाओd */
		अगर (pi->sib_head[node->tc_num][node->tx_sched_layer] == node)
			pi->sib_head[node->tc_num][node->tx_sched_layer] =
				node->sibling;
	पूर्ण

	/* leaf nodes have no children */
	अगर (node->children)
		devm_kमुक्त(ice_hw_to_dev(hw), node->children);
	devm_kमुक्त(ice_hw_to_dev(hw), node);
पूर्ण

/**
 * ice_aq_get_dflt_topo - माला_लो शेष scheduler topology
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @lport: logical port number
 * @buf: poपूर्णांकer to buffer
 * @buf_size: buffer size in bytes
 * @num_branches: वापसs total number of queue to port branches
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Get शेष scheduler topology (0x400)
 */
अटल क्रमागत ice_status
ice_aq_get_dflt_topo(काष्ठा ice_hw *hw, u8 lport,
		     काष्ठा ice_aqc_get_topo_elem *buf, u16 buf_size,
		     u8 *num_branches, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_get_topo *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	cmd = &desc.params.get_topo;
	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_get_dflt_topo);
	cmd->port_num = lport;
	status = ice_aq_send_cmd(hw, &desc, buf, buf_size, cd);
	अगर (!status && num_branches)
		*num_branches = cmd->num_branches;

	वापस status;
पूर्ण

/**
 * ice_aq_add_sched_elems - adds scheduling element
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @grps_req: the number of groups that are requested to be added
 * @buf: poपूर्णांकer to buffer
 * @buf_size: buffer size in bytes
 * @grps_added: वापसs total number of groups added
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Add scheduling elements (0x0401)
 */
अटल क्रमागत ice_status
ice_aq_add_sched_elems(काष्ठा ice_hw *hw, u16 grps_req,
		       काष्ठा ice_aqc_add_elem *buf, u16 buf_size,
		       u16 *grps_added, काष्ठा ice_sq_cd *cd)
अणु
	वापस ice_aqc_send_sched_elem_cmd(hw, ice_aqc_opc_add_sched_elems,
					   grps_req, (व्योम *)buf, buf_size,
					   grps_added, cd);
पूर्ण

/**
 * ice_aq_cfg_sched_elems - configures scheduler elements
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @elems_req: number of elements to configure
 * @buf: poपूर्णांकer to buffer
 * @buf_size: buffer size in bytes
 * @elems_cfgd: वापसs total number of elements configured
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Configure scheduling elements (0x0403)
 */
अटल क्रमागत ice_status
ice_aq_cfg_sched_elems(काष्ठा ice_hw *hw, u16 elems_req,
		       काष्ठा ice_aqc_txsched_elem_data *buf, u16 buf_size,
		       u16 *elems_cfgd, काष्ठा ice_sq_cd *cd)
अणु
	वापस ice_aqc_send_sched_elem_cmd(hw, ice_aqc_opc_cfg_sched_elems,
					   elems_req, (व्योम *)buf, buf_size,
					   elems_cfgd, cd);
पूर्ण

/**
 * ice_aq_move_sched_elems - move scheduler elements
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @grps_req: number of groups to move
 * @buf: poपूर्णांकer to buffer
 * @buf_size: buffer size in bytes
 * @grps_movd: वापसs total number of groups moved
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Move scheduling elements (0x0408)
 */
अटल क्रमागत ice_status
ice_aq_move_sched_elems(काष्ठा ice_hw *hw, u16 grps_req,
			काष्ठा ice_aqc_move_elem *buf, u16 buf_size,
			u16 *grps_movd, काष्ठा ice_sq_cd *cd)
अणु
	वापस ice_aqc_send_sched_elem_cmd(hw, ice_aqc_opc_move_sched_elems,
					   grps_req, (व्योम *)buf, buf_size,
					   grps_movd, cd);
पूर्ण

/**
 * ice_aq_suspend_sched_elems - suspend scheduler elements
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @elems_req: number of elements to suspend
 * @buf: poपूर्णांकer to buffer
 * @buf_size: buffer size in bytes
 * @elems_ret: वापसs total number of elements suspended
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Suspend scheduling elements (0x0409)
 */
अटल क्रमागत ice_status
ice_aq_suspend_sched_elems(काष्ठा ice_hw *hw, u16 elems_req, __le32 *buf,
			   u16 buf_size, u16 *elems_ret, काष्ठा ice_sq_cd *cd)
अणु
	वापस ice_aqc_send_sched_elem_cmd(hw, ice_aqc_opc_suspend_sched_elems,
					   elems_req, (व्योम *)buf, buf_size,
					   elems_ret, cd);
पूर्ण

/**
 * ice_aq_resume_sched_elems - resume scheduler elements
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @elems_req: number of elements to resume
 * @buf: poपूर्णांकer to buffer
 * @buf_size: buffer size in bytes
 * @elems_ret: वापसs total number of elements resumed
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * resume scheduling elements (0x040A)
 */
अटल क्रमागत ice_status
ice_aq_resume_sched_elems(काष्ठा ice_hw *hw, u16 elems_req, __le32 *buf,
			  u16 buf_size, u16 *elems_ret, काष्ठा ice_sq_cd *cd)
अणु
	वापस ice_aqc_send_sched_elem_cmd(hw, ice_aqc_opc_resume_sched_elems,
					   elems_req, (व्योम *)buf, buf_size,
					   elems_ret, cd);
पूर्ण

/**
 * ice_aq_query_sched_res - query scheduler resource
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @buf_size: buffer size in bytes
 * @buf: poपूर्णांकer to buffer
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Query scheduler resource allocation (0x0412)
 */
अटल क्रमागत ice_status
ice_aq_query_sched_res(काष्ठा ice_hw *hw, u16 buf_size,
		       काष्ठा ice_aqc_query_txsched_res_resp *buf,
		       काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aq_desc desc;

	ice_fill_dflt_direct_cmd_desc(&desc, ice_aqc_opc_query_sched_res);
	वापस ice_aq_send_cmd(hw, &desc, buf, buf_size, cd);
पूर्ण

/**
 * ice_sched_suspend_resume_elems - suspend or resume HW nodes
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @num_nodes: number of nodes
 * @node_teids: array of node teids to be suspended or resumed
 * @suspend: true means suspend / false means resume
 *
 * This function suspends or resumes HW nodes
 */
अटल क्रमागत ice_status
ice_sched_suspend_resume_elems(काष्ठा ice_hw *hw, u8 num_nodes, u32 *node_teids,
			       bool suspend)
अणु
	u16 i, buf_size, num_elem_ret = 0;
	क्रमागत ice_status status;
	__le32 *buf;

	buf_size = माप(*buf) * num_nodes;
	buf = devm_kzalloc(ice_hw_to_dev(hw), buf_size, GFP_KERNEL);
	अगर (!buf)
		वापस ICE_ERR_NO_MEMORY;

	क्रम (i = 0; i < num_nodes; i++)
		buf[i] = cpu_to_le32(node_teids[i]);

	अगर (suspend)
		status = ice_aq_suspend_sched_elems(hw, num_nodes, buf,
						    buf_size, &num_elem_ret,
						    शून्य);
	अन्यथा
		status = ice_aq_resume_sched_elems(hw, num_nodes, buf,
						   buf_size, &num_elem_ret,
						   शून्य);
	अगर (status || num_elem_ret != num_nodes)
		ice_debug(hw, ICE_DBG_SCHED, "suspend/resume failed\n");

	devm_kमुक्त(ice_hw_to_dev(hw), buf);
	वापस status;
पूर्ण

/**
 * ice_alloc_lan_q_ctx - allocate LAN queue contexts क्रम the given VSI and TC
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: VSI handle
 * @tc: TC number
 * @new_numqs: number of queues
 */
अटल क्रमागत ice_status
ice_alloc_lan_q_ctx(काष्ठा ice_hw *hw, u16 vsi_handle, u8 tc, u16 new_numqs)
अणु
	काष्ठा ice_vsi_ctx *vsi_ctx;
	काष्ठा ice_q_ctx *q_ctx;

	vsi_ctx = ice_get_vsi_ctx(hw, vsi_handle);
	अगर (!vsi_ctx)
		वापस ICE_ERR_PARAM;
	/* allocate LAN queue contexts */
	अगर (!vsi_ctx->lan_q_ctx[tc]) अणु
		vsi_ctx->lan_q_ctx[tc] = devm_kसुस्मृति(ice_hw_to_dev(hw),
						      new_numqs,
						      माप(*q_ctx),
						      GFP_KERNEL);
		अगर (!vsi_ctx->lan_q_ctx[tc])
			वापस ICE_ERR_NO_MEMORY;
		vsi_ctx->num_lan_q_entries[tc] = new_numqs;
		वापस 0;
	पूर्ण
	/* num queues are increased, update the queue contexts */
	अगर (new_numqs > vsi_ctx->num_lan_q_entries[tc]) अणु
		u16 prev_num = vsi_ctx->num_lan_q_entries[tc];

		q_ctx = devm_kसुस्मृति(ice_hw_to_dev(hw), new_numqs,
				     माप(*q_ctx), GFP_KERNEL);
		अगर (!q_ctx)
			वापस ICE_ERR_NO_MEMORY;
		स_नकल(q_ctx, vsi_ctx->lan_q_ctx[tc],
		       prev_num * माप(*q_ctx));
		devm_kमुक्त(ice_hw_to_dev(hw), vsi_ctx->lan_q_ctx[tc]);
		vsi_ctx->lan_q_ctx[tc] = q_ctx;
		vsi_ctx->num_lan_q_entries[tc] = new_numqs;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_aq_rl_profile - perक्रमms a rate limiting task
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @opcode: opcode क्रम add, query, or हटाओ profile(s)
 * @num_profiles: the number of profiles
 * @buf: poपूर्णांकer to buffer
 * @buf_size: buffer size in bytes
 * @num_processed: number of processed add or हटाओ profile(s) to वापस
 * @cd: poपूर्णांकer to command details काष्ठाure
 *
 * RL profile function to add, query, or हटाओ profile(s)
 */
अटल क्रमागत ice_status
ice_aq_rl_profile(काष्ठा ice_hw *hw, क्रमागत ice_adminq_opc opcode,
		  u16 num_profiles, काष्ठा ice_aqc_rl_profile_elem *buf,
		  u16 buf_size, u16 *num_processed, काष्ठा ice_sq_cd *cd)
अणु
	काष्ठा ice_aqc_rl_profile *cmd;
	काष्ठा ice_aq_desc desc;
	क्रमागत ice_status status;

	cmd = &desc.params.rl_profile;

	ice_fill_dflt_direct_cmd_desc(&desc, opcode);
	desc.flags |= cpu_to_le16(ICE_AQ_FLAG_RD);
	cmd->num_profiles = cpu_to_le16(num_profiles);
	status = ice_aq_send_cmd(hw, &desc, buf, buf_size, cd);
	अगर (!status && num_processed)
		*num_processed = le16_to_cpu(cmd->num_processed);
	वापस status;
पूर्ण

/**
 * ice_aq_add_rl_profile - adds rate limiting profile(s)
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @num_profiles: the number of profile(s) to be add
 * @buf: poपूर्णांकer to buffer
 * @buf_size: buffer size in bytes
 * @num_profiles_added: total number of profiles added to वापस
 * @cd: poपूर्णांकer to command details काष्ठाure
 *
 * Add RL profile (0x0410)
 */
अटल क्रमागत ice_status
ice_aq_add_rl_profile(काष्ठा ice_hw *hw, u16 num_profiles,
		      काष्ठा ice_aqc_rl_profile_elem *buf, u16 buf_size,
		      u16 *num_profiles_added, काष्ठा ice_sq_cd *cd)
अणु
	वापस ice_aq_rl_profile(hw, ice_aqc_opc_add_rl_profiles, num_profiles,
				 buf, buf_size, num_profiles_added, cd);
पूर्ण

/**
 * ice_aq_हटाओ_rl_profile - हटाओs RL profile(s)
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @num_profiles: the number of profile(s) to हटाओ
 * @buf: poपूर्णांकer to buffer
 * @buf_size: buffer size in bytes
 * @num_profiles_हटाओd: total number of profiles हटाओd to वापस
 * @cd: poपूर्णांकer to command details काष्ठाure or शून्य
 *
 * Remove RL profile (0x0415)
 */
अटल क्रमागत ice_status
ice_aq_हटाओ_rl_profile(काष्ठा ice_hw *hw, u16 num_profiles,
			 काष्ठा ice_aqc_rl_profile_elem *buf, u16 buf_size,
			 u16 *num_profiles_हटाओd, काष्ठा ice_sq_cd *cd)
अणु
	वापस ice_aq_rl_profile(hw, ice_aqc_opc_हटाओ_rl_profiles,
				 num_profiles, buf, buf_size,
				 num_profiles_हटाओd, cd);
पूर्ण

/**
 * ice_sched_del_rl_profile - हटाओ RL profile
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @rl_info: rate limit profile inक्रमmation
 *
 * If the profile ID is not referenced anymore, it हटाओs profile ID with
 * its associated parameters from HW DB,and locally. The caller needs to
 * hold scheduler lock.
 */
अटल क्रमागत ice_status
ice_sched_del_rl_profile(काष्ठा ice_hw *hw,
			 काष्ठा ice_aqc_rl_profile_info *rl_info)
अणु
	काष्ठा ice_aqc_rl_profile_elem *buf;
	u16 num_profiles_हटाओd;
	क्रमागत ice_status status;
	u16 num_profiles = 1;

	अगर (rl_info->prof_id_ref != 0)
		वापस ICE_ERR_IN_USE;

	/* Safe to हटाओ profile ID */
	buf = &rl_info->profile;
	status = ice_aq_हटाओ_rl_profile(hw, num_profiles, buf, माप(*buf),
					  &num_profiles_हटाओd, शून्य);
	अगर (status || num_profiles_हटाओd != num_profiles)
		वापस ICE_ERR_CFG;

	/* Delete stale entry now */
	list_del(&rl_info->list_entry);
	devm_kमुक्त(ice_hw_to_dev(hw), rl_info);
	वापस status;
पूर्ण

/**
 * ice_sched_clear_rl_prof - clears RL prof entries
 * @pi: port inक्रमmation काष्ठाure
 *
 * This function हटाओs all RL profile from HW as well as from SW DB.
 */
अटल व्योम ice_sched_clear_rl_prof(काष्ठा ice_port_info *pi)
अणु
	u16 ln;

	क्रम (ln = 0; ln < pi->hw->num_tx_sched_layers; ln++) अणु
		काष्ठा ice_aqc_rl_profile_info *rl_prof_elem;
		काष्ठा ice_aqc_rl_profile_info *rl_prof_पंचांगp;

		list_क्रम_each_entry_safe(rl_prof_elem, rl_prof_पंचांगp,
					 &pi->rl_prof_list[ln], list_entry) अणु
			काष्ठा ice_hw *hw = pi->hw;
			क्रमागत ice_status status;

			rl_prof_elem->prof_id_ref = 0;
			status = ice_sched_del_rl_profile(hw, rl_prof_elem);
			अगर (status) अणु
				ice_debug(hw, ICE_DBG_SCHED, "Remove rl profile failed\n");
				/* On error, मुक्त mem required */
				list_del(&rl_prof_elem->list_entry);
				devm_kमुक्त(ice_hw_to_dev(hw), rl_prof_elem);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_sched_clear_agg - clears the aggregator related inक्रमmation
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 *
 * This function हटाओs aggregator list and मुक्त up aggregator related memory
 * previously allocated.
 */
व्योम ice_sched_clear_agg(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_sched_agg_info *agg_info;
	काष्ठा ice_sched_agg_info *aपंचांगp;

	list_क्रम_each_entry_safe(agg_info, aपंचांगp, &hw->agg_list, list_entry) अणु
		काष्ठा ice_sched_agg_vsi_info *agg_vsi_info;
		काष्ठा ice_sched_agg_vsi_info *vपंचांगp;

		list_क्रम_each_entry_safe(agg_vsi_info, vपंचांगp,
					 &agg_info->agg_vsi_list, list_entry) अणु
			list_del(&agg_vsi_info->list_entry);
			devm_kमुक्त(ice_hw_to_dev(hw), agg_vsi_info);
		पूर्ण
		list_del(&agg_info->list_entry);
		devm_kमुक्त(ice_hw_to_dev(hw), agg_info);
	पूर्ण
पूर्ण

/**
 * ice_sched_clear_tx_topo - clears the scheduler tree nodes
 * @pi: port inक्रमmation काष्ठाure
 *
 * This function हटाओs all the nodes from HW as well as from SW DB.
 */
अटल व्योम ice_sched_clear_tx_topo(काष्ठा ice_port_info *pi)
अणु
	अगर (!pi)
		वापस;
	/* हटाओ RL profiles related lists */
	ice_sched_clear_rl_prof(pi);
	अगर (pi->root) अणु
		ice_मुक्त_sched_node(pi, pi->root);
		pi->root = शून्य;
	पूर्ण
पूर्ण

/**
 * ice_sched_clear_port - clear the scheduler elements from SW DB क्रम a port
 * @pi: port inक्रमmation काष्ठाure
 *
 * Cleanup scheduling elements from SW DB
 */
व्योम ice_sched_clear_port(काष्ठा ice_port_info *pi)
अणु
	अगर (!pi || pi->port_state != ICE_SCHED_PORT_STATE_READY)
		वापस;

	pi->port_state = ICE_SCHED_PORT_STATE_INIT;
	mutex_lock(&pi->sched_lock);
	ice_sched_clear_tx_topo(pi);
	mutex_unlock(&pi->sched_lock);
	mutex_destroy(&pi->sched_lock);
पूर्ण

/**
 * ice_sched_cleanup_all - cleanup scheduler elements from SW DB क्रम all ports
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * Cleanup scheduling elements from SW DB क्रम all the ports
 */
व्योम ice_sched_cleanup_all(काष्ठा ice_hw *hw)
अणु
	अगर (!hw)
		वापस;

	अगर (hw->layer_info) अणु
		devm_kमुक्त(ice_hw_to_dev(hw), hw->layer_info);
		hw->layer_info = शून्य;
	पूर्ण

	ice_sched_clear_port(hw->port_info);

	hw->num_tx_sched_layers = 0;
	hw->num_tx_sched_phys_layers = 0;
	hw->flattened_layers = 0;
	hw->max_cgds = 0;
पूर्ण

/**
 * ice_sched_add_elems - add nodes to HW and SW DB
 * @pi: port inक्रमmation काष्ठाure
 * @tc_node: poपूर्णांकer to the branch node
 * @parent: poपूर्णांकer to the parent node
 * @layer: layer number to add nodes
 * @num_nodes: number of nodes
 * @num_nodes_added: poपूर्णांकer to num nodes added
 * @first_node_teid: अगर new nodes are added then वापस the TEID of first node
 *
 * This function add nodes to HW as well as to SW DB क्रम a given layer
 */
अटल क्रमागत ice_status
ice_sched_add_elems(काष्ठा ice_port_info *pi, काष्ठा ice_sched_node *tc_node,
		    काष्ठा ice_sched_node *parent, u8 layer, u16 num_nodes,
		    u16 *num_nodes_added, u32 *first_node_teid)
अणु
	काष्ठा ice_sched_node *prev, *new_node;
	काष्ठा ice_aqc_add_elem *buf;
	u16 i, num_groups_added = 0;
	क्रमागत ice_status status = 0;
	काष्ठा ice_hw *hw = pi->hw;
	माप_प्रकार buf_size;
	u32 teid;

	buf_size = काष्ठा_size(buf, generic, num_nodes);
	buf = devm_kzalloc(ice_hw_to_dev(hw), buf_size, GFP_KERNEL);
	अगर (!buf)
		वापस ICE_ERR_NO_MEMORY;

	buf->hdr.parent_teid = parent->info.node_teid;
	buf->hdr.num_elems = cpu_to_le16(num_nodes);
	क्रम (i = 0; i < num_nodes; i++) अणु
		buf->generic[i].parent_teid = parent->info.node_teid;
		buf->generic[i].data.elem_type = ICE_AQC_ELEM_TYPE_SE_GENERIC;
		buf->generic[i].data.valid_sections =
			ICE_AQC_ELEM_VALID_GENERIC | ICE_AQC_ELEM_VALID_CIR |
			ICE_AQC_ELEM_VALID_EIR;
		buf->generic[i].data.generic = 0;
		buf->generic[i].data.cir_bw.bw_profile_idx =
			cpu_to_le16(ICE_SCHED_DFLT_RL_PROF_ID);
		buf->generic[i].data.cir_bw.bw_alloc =
			cpu_to_le16(ICE_SCHED_DFLT_BW_WT);
		buf->generic[i].data.eir_bw.bw_profile_idx =
			cpu_to_le16(ICE_SCHED_DFLT_RL_PROF_ID);
		buf->generic[i].data.eir_bw.bw_alloc =
			cpu_to_le16(ICE_SCHED_DFLT_BW_WT);
	पूर्ण

	status = ice_aq_add_sched_elems(hw, 1, buf, buf_size,
					&num_groups_added, शून्य);
	अगर (status || num_groups_added != 1) अणु
		ice_debug(hw, ICE_DBG_SCHED, "add node failed FW Error %d\n",
			  hw->adminq.sq_last_status);
		devm_kमुक्त(ice_hw_to_dev(hw), buf);
		वापस ICE_ERR_CFG;
	पूर्ण

	*num_nodes_added = num_nodes;
	/* add nodes to the SW DB */
	क्रम (i = 0; i < num_nodes; i++) अणु
		status = ice_sched_add_node(pi, layer, &buf->generic[i]);
		अगर (status) अणु
			ice_debug(hw, ICE_DBG_SCHED, "add nodes in SW DB failed status =%d\n",
				  status);
			अवरोध;
		पूर्ण

		teid = le32_to_cpu(buf->generic[i].node_teid);
		new_node = ice_sched_find_node_by_teid(parent, teid);
		अगर (!new_node) अणु
			ice_debug(hw, ICE_DBG_SCHED, "Node is missing for teid =%d\n", teid);
			अवरोध;
		पूर्ण

		new_node->sibling = शून्य;
		new_node->tc_num = tc_node->tc_num;

		/* add it to previous node sibling poपूर्णांकer */
		/* Note: siblings are not linked across branches */
		prev = ice_sched_get_first_node(pi, tc_node, layer);
		अगर (prev && prev != new_node) अणु
			जबतक (prev->sibling)
				prev = prev->sibling;
			prev->sibling = new_node;
		पूर्ण

		/* initialize the sibling head */
		अगर (!pi->sib_head[tc_node->tc_num][layer])
			pi->sib_head[tc_node->tc_num][layer] = new_node;

		अगर (i == 0)
			*first_node_teid = teid;
	पूर्ण

	devm_kमुक्त(ice_hw_to_dev(hw), buf);
	वापस status;
पूर्ण

/**
 * ice_sched_add_nodes_to_hw_layer - Add nodes to HW layer
 * @pi: port inक्रमmation काष्ठाure
 * @tc_node: poपूर्णांकer to TC node
 * @parent: poपूर्णांकer to parent node
 * @layer: layer number to add nodes
 * @num_nodes: number of nodes to be added
 * @first_node_teid: poपूर्णांकer to the first node TEID
 * @num_nodes_added: poपूर्णांकer to number of nodes added
 *
 * Add nodes पूर्णांकo specअगरic HW layer.
 */
अटल क्रमागत ice_status
ice_sched_add_nodes_to_hw_layer(काष्ठा ice_port_info *pi,
				काष्ठा ice_sched_node *tc_node,
				काष्ठा ice_sched_node *parent, u8 layer,
				u16 num_nodes, u32 *first_node_teid,
				u16 *num_nodes_added)
अणु
	u16 max_child_nodes;

	*num_nodes_added = 0;

	अगर (!num_nodes)
		वापस 0;

	अगर (!parent || layer < pi->hw->sw_entry_poपूर्णांक_layer)
		वापस ICE_ERR_PARAM;

	/* max children per node per layer */
	max_child_nodes = pi->hw->max_children[parent->tx_sched_layer];

	/* current number of children + required nodes exceed max children */
	अगर ((parent->num_children + num_nodes) > max_child_nodes) अणु
		/* Fail अगर the parent is a TC node */
		अगर (parent == tc_node)
			वापस ICE_ERR_CFG;
		वापस ICE_ERR_MAX_LIMIT;
	पूर्ण

	वापस ice_sched_add_elems(pi, tc_node, parent, layer, num_nodes,
				   num_nodes_added, first_node_teid);
पूर्ण

/**
 * ice_sched_add_nodes_to_layer - Add nodes to a given layer
 * @pi: port inक्रमmation काष्ठाure
 * @tc_node: poपूर्णांकer to TC node
 * @parent: poपूर्णांकer to parent node
 * @layer: layer number to add nodes
 * @num_nodes: number of nodes to be added
 * @first_node_teid: poपूर्णांकer to the first node TEID
 * @num_nodes_added: poपूर्णांकer to number of nodes added
 *
 * This function add nodes to a given layer.
 */
अटल क्रमागत ice_status
ice_sched_add_nodes_to_layer(काष्ठा ice_port_info *pi,
			     काष्ठा ice_sched_node *tc_node,
			     काष्ठा ice_sched_node *parent, u8 layer,
			     u16 num_nodes, u32 *first_node_teid,
			     u16 *num_nodes_added)
अणु
	u32 *first_teid_ptr = first_node_teid;
	u16 new_num_nodes = num_nodes;
	क्रमागत ice_status status = 0;

	*num_nodes_added = 0;
	जबतक (*num_nodes_added < num_nodes) अणु
		u16 max_child_nodes, num_added = 0;
		/* cppcheck-suppress unusedVariable */
		u32 temp;

		status = ice_sched_add_nodes_to_hw_layer(pi, tc_node, parent,
							 layer,	new_num_nodes,
							 first_teid_ptr,
							 &num_added);
		अगर (!status)
			*num_nodes_added += num_added;
		/* added more nodes than requested ? */
		अगर (*num_nodes_added > num_nodes) अणु
			ice_debug(pi->hw, ICE_DBG_SCHED, "added extra nodes %d %d\n", num_nodes,
				  *num_nodes_added);
			status = ICE_ERR_CFG;
			अवरोध;
		पूर्ण
		/* अवरोध अगर all the nodes are added successfully */
		अगर (!status && (*num_nodes_added == num_nodes))
			अवरोध;
		/* अवरोध अगर the error is not max limit */
		अगर (status && status != ICE_ERR_MAX_LIMIT)
			अवरोध;
		/* Exceeded the max children */
		max_child_nodes = pi->hw->max_children[parent->tx_sched_layer];
		/* utilize all the spaces अगर the parent is not full */
		अगर (parent->num_children < max_child_nodes) अणु
			new_num_nodes = max_child_nodes - parent->num_children;
		पूर्ण अन्यथा अणु
			/* This parent is full, try the next sibling */
			parent = parent->sibling;
			/* Don't modअगरy the first node TEID memory अगर the
			 * first node was added alपढ़ोy in the above call.
			 * Instead send some temp memory क्रम all other
			 * recursive calls.
			 */
			अगर (num_added)
				first_teid_ptr = &temp;

			new_num_nodes = num_nodes - *num_nodes_added;
		पूर्ण
	पूर्ण
	वापस status;
पूर्ण

/**
 * ice_sched_get_qgrp_layer - get the current queue group layer number
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * This function वापसs the current queue group layer number
 */
अटल u8 ice_sched_get_qgrp_layer(काष्ठा ice_hw *hw)
अणु
	/* It's always total layers - 1, the array is 0 relative so -2 */
	वापस hw->num_tx_sched_layers - ICE_QGRP_LAYER_OFFSET;
पूर्ण

/**
 * ice_sched_get_vsi_layer - get the current VSI layer number
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * This function वापसs the current VSI layer number
 */
अटल u8 ice_sched_get_vsi_layer(काष्ठा ice_hw *hw)
अणु
	/* Num Layers       VSI layer
	 *     9               6
	 *     7               4
	 *     5 or less       sw_entry_poपूर्णांक_layer
	 */
	/* calculate the VSI layer based on number of layers. */
	अगर (hw->num_tx_sched_layers > ICE_VSI_LAYER_OFFSET + 1) अणु
		u8 layer = hw->num_tx_sched_layers - ICE_VSI_LAYER_OFFSET;

		अगर (layer > hw->sw_entry_poपूर्णांक_layer)
			वापस layer;
	पूर्ण
	वापस hw->sw_entry_poपूर्णांक_layer;
पूर्ण

/**
 * ice_sched_get_agg_layer - get the current aggregator layer number
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * This function वापसs the current aggregator layer number
 */
अटल u8 ice_sched_get_agg_layer(काष्ठा ice_hw *hw)
अणु
	/* Num Layers       aggregator layer
	 *     9               4
	 *     7 or less       sw_entry_poपूर्णांक_layer
	 */
	/* calculate the aggregator layer based on number of layers. */
	अगर (hw->num_tx_sched_layers > ICE_AGG_LAYER_OFFSET + 1) अणु
		u8 layer = hw->num_tx_sched_layers - ICE_AGG_LAYER_OFFSET;

		अगर (layer > hw->sw_entry_poपूर्णांक_layer)
			वापस layer;
	पूर्ण
	वापस hw->sw_entry_poपूर्णांक_layer;
पूर्ण

/**
 * ice_rm_dflt_leaf_node - हटाओ the शेष leaf node in the tree
 * @pi: port inक्रमmation काष्ठाure
 *
 * This function हटाओs the leaf node that was created by the FW
 * during initialization
 */
अटल व्योम ice_rm_dflt_leaf_node(काष्ठा ice_port_info *pi)
अणु
	काष्ठा ice_sched_node *node;

	node = pi->root;
	जबतक (node) अणु
		अगर (!node->num_children)
			अवरोध;
		node = node->children[0];
	पूर्ण
	अगर (node && node->info.data.elem_type == ICE_AQC_ELEM_TYPE_LEAF) अणु
		u32 teid = le32_to_cpu(node->info.node_teid);
		क्रमागत ice_status status;

		/* हटाओ the शेष leaf node */
		status = ice_sched_हटाओ_elems(pi->hw, node->parent, 1, &teid);
		अगर (!status)
			ice_मुक्त_sched_node(pi, node);
	पूर्ण
पूर्ण

/**
 * ice_sched_rm_dflt_nodes - मुक्त the शेष nodes in the tree
 * @pi: port inक्रमmation काष्ठाure
 *
 * This function मुक्तs all the nodes except root and TC that were created by
 * the FW during initialization
 */
अटल व्योम ice_sched_rm_dflt_nodes(काष्ठा ice_port_info *pi)
अणु
	काष्ठा ice_sched_node *node;

	ice_rm_dflt_leaf_node(pi);

	/* हटाओ the शेष nodes except TC and root nodes */
	node = pi->root;
	जबतक (node) अणु
		अगर (node->tx_sched_layer >= pi->hw->sw_entry_poपूर्णांक_layer &&
		    node->info.data.elem_type != ICE_AQC_ELEM_TYPE_TC &&
		    node->info.data.elem_type != ICE_AQC_ELEM_TYPE_ROOT_PORT) अणु
			ice_मुक्त_sched_node(pi, node);
			अवरोध;
		पूर्ण

		अगर (!node->num_children)
			अवरोध;
		node = node->children[0];
	पूर्ण
पूर्ण

/**
 * ice_sched_init_port - Initialize scheduler by querying inक्रमmation from FW
 * @pi: port info काष्ठाure क्रम the tree to cleanup
 *
 * This function is the initial call to find the total number of Tx scheduler
 * resources, शेष topology created by firmware and storing the inक्रमmation
 * in SW DB.
 */
क्रमागत ice_status ice_sched_init_port(काष्ठा ice_port_info *pi)
अणु
	काष्ठा ice_aqc_get_topo_elem *buf;
	क्रमागत ice_status status;
	काष्ठा ice_hw *hw;
	u8 num_branches;
	u16 num_elems;
	u8 i, j;

	अगर (!pi)
		वापस ICE_ERR_PARAM;
	hw = pi->hw;

	/* Query the Default Topology from FW */
	buf = devm_kzalloc(ice_hw_to_dev(hw), ICE_AQ_MAX_BUF_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस ICE_ERR_NO_MEMORY;

	/* Query शेष scheduling tree topology */
	status = ice_aq_get_dflt_topo(hw, pi->lport, buf, ICE_AQ_MAX_BUF_LEN,
				      &num_branches, शून्य);
	अगर (status)
		जाओ err_init_port;

	/* num_branches should be between 1-8 */
	अगर (num_branches < 1 || num_branches > ICE_TXSCHED_MAX_BRANCHES) अणु
		ice_debug(hw, ICE_DBG_SCHED, "num_branches unexpected %d\n",
			  num_branches);
		status = ICE_ERR_PARAM;
		जाओ err_init_port;
	पूर्ण

	/* get the number of elements on the शेष/first branch */
	num_elems = le16_to_cpu(buf[0].hdr.num_elems);

	/* num_elems should always be between 1-9 */
	अगर (num_elems < 1 || num_elems > ICE_AQC_TOPO_MAX_LEVEL_NUM) अणु
		ice_debug(hw, ICE_DBG_SCHED, "num_elems unexpected %d\n",
			  num_elems);
		status = ICE_ERR_PARAM;
		जाओ err_init_port;
	पूर्ण

	/* If the last node is a leaf node then the index of the queue group
	 * layer is two less than the number of elements.
	 */
	अगर (num_elems > 2 && buf[0].generic[num_elems - 1].data.elem_type ==
	    ICE_AQC_ELEM_TYPE_LEAF)
		pi->last_node_teid =
			le32_to_cpu(buf[0].generic[num_elems - 2].node_teid);
	अन्यथा
		pi->last_node_teid =
			le32_to_cpu(buf[0].generic[num_elems - 1].node_teid);

	/* Insert the Tx Sched root node */
	status = ice_sched_add_root_node(pi, &buf[0].generic[0]);
	अगर (status)
		जाओ err_init_port;

	/* Parse the शेष tree and cache the inक्रमmation */
	क्रम (i = 0; i < num_branches; i++) अणु
		num_elems = le16_to_cpu(buf[i].hdr.num_elems);

		/* Skip root element as alपढ़ोy inserted */
		क्रम (j = 1; j < num_elems; j++) अणु
			/* update the sw entry poपूर्णांक */
			अगर (buf[0].generic[j].data.elem_type ==
			    ICE_AQC_ELEM_TYPE_ENTRY_POINT)
				hw->sw_entry_poपूर्णांक_layer = j;

			status = ice_sched_add_node(pi, j, &buf[i].generic[j]);
			अगर (status)
				जाओ err_init_port;
		पूर्ण
	पूर्ण

	/* Remove the शेष nodes. */
	अगर (pi->root)
		ice_sched_rm_dflt_nodes(pi);

	/* initialize the port क्रम handling the scheduler tree */
	pi->port_state = ICE_SCHED_PORT_STATE_READY;
	mutex_init(&pi->sched_lock);
	क्रम (i = 0; i < ICE_AQC_TOPO_MAX_LEVEL_NUM; i++)
		INIT_LIST_HEAD(&pi->rl_prof_list[i]);

err_init_port:
	अगर (status && pi->root) अणु
		ice_मुक्त_sched_node(pi, pi->root);
		pi->root = शून्य;
	पूर्ण

	devm_kमुक्त(ice_hw_to_dev(hw), buf);
	वापस status;
पूर्ण

/**
 * ice_sched_query_res_alloc - query the FW क्रम num of logical sched layers
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * query FW क्रम allocated scheduler resources and store in HW काष्ठा
 */
क्रमागत ice_status ice_sched_query_res_alloc(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_aqc_query_txsched_res_resp *buf;
	क्रमागत ice_status status = 0;
	__le16 max_sibl;
	u16 i;

	अगर (hw->layer_info)
		वापस status;

	buf = devm_kzalloc(ice_hw_to_dev(hw), माप(*buf), GFP_KERNEL);
	अगर (!buf)
		वापस ICE_ERR_NO_MEMORY;

	status = ice_aq_query_sched_res(hw, माप(*buf), buf, शून्य);
	अगर (status)
		जाओ sched_query_out;

	hw->num_tx_sched_layers = le16_to_cpu(buf->sched_props.logical_levels);
	hw->num_tx_sched_phys_layers =
		le16_to_cpu(buf->sched_props.phys_levels);
	hw->flattened_layers = buf->sched_props.flattening_biपंचांगap;
	hw->max_cgds = buf->sched_props.max_pf_cgds;

	/* max sibling group size of current layer refers to the max children
	 * of the below layer node.
	 * layer 1 node max children will be layer 2 max sibling group size
	 * layer 2 node max children will be layer 3 max sibling group size
	 * and so on. This array will be populated from root (index 0) to
	 * qgroup layer 7. Leaf node has no children.
	 */
	क्रम (i = 0; i < hw->num_tx_sched_layers - 1; i++) अणु
		max_sibl = buf->layer_props[i + 1].max_sibl_grp_sz;
		hw->max_children[i] = le16_to_cpu(max_sibl);
	पूर्ण

	hw->layer_info = devm_kmemdup(ice_hw_to_dev(hw), buf->layer_props,
				      (hw->num_tx_sched_layers *
				       माप(*hw->layer_info)),
				      GFP_KERNEL);
	अगर (!hw->layer_info) अणु
		status = ICE_ERR_NO_MEMORY;
		जाओ sched_query_out;
	पूर्ण

sched_query_out:
	devm_kमुक्त(ice_hw_to_dev(hw), buf);
	वापस status;
पूर्ण

/**
 * ice_sched_get_psm_clk_freq - determine the PSM घड़ी frequency
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * Determine the PSM घड़ी frequency and store in HW काष्ठा
 */
व्योम ice_sched_get_psm_clk_freq(काष्ठा ice_hw *hw)
अणु
	u32 val, clk_src;

	val = rd32(hw, GLGEN_CLKSTAT_SRC);
	clk_src = (val & GLGEN_CLKSTAT_SRC_PSM_CLK_SRC_M) >>
		GLGEN_CLKSTAT_SRC_PSM_CLK_SRC_S;

#घोषणा PSM_CLK_SRC_367_MHZ 0x0
#घोषणा PSM_CLK_SRC_416_MHZ 0x1
#घोषणा PSM_CLK_SRC_446_MHZ 0x2
#घोषणा PSM_CLK_SRC_390_MHZ 0x3

	चयन (clk_src) अणु
	हाल PSM_CLK_SRC_367_MHZ:
		hw->psm_clk_freq = ICE_PSM_CLK_367MHZ_IN_HZ;
		अवरोध;
	हाल PSM_CLK_SRC_416_MHZ:
		hw->psm_clk_freq = ICE_PSM_CLK_416MHZ_IN_HZ;
		अवरोध;
	हाल PSM_CLK_SRC_446_MHZ:
		hw->psm_clk_freq = ICE_PSM_CLK_446MHZ_IN_HZ;
		अवरोध;
	हाल PSM_CLK_SRC_390_MHZ:
		hw->psm_clk_freq = ICE_PSM_CLK_390MHZ_IN_HZ;
		अवरोध;
	शेष:
		ice_debug(hw, ICE_DBG_SCHED, "PSM clk_src unexpected %u\n",
			  clk_src);
		/* fall back to a safe शेष */
		hw->psm_clk_freq = ICE_PSM_CLK_446MHZ_IN_HZ;
	पूर्ण
पूर्ण

/**
 * ice_sched_find_node_in_subtree - Find node in part of base node subtree
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @base: poपूर्णांकer to the base node
 * @node: poपूर्णांकer to the node to search
 *
 * This function checks whether a given node is part of the base node
 * subtree or not
 */
अटल bool
ice_sched_find_node_in_subtree(काष्ठा ice_hw *hw, काष्ठा ice_sched_node *base,
			       काष्ठा ice_sched_node *node)
अणु
	u8 i;

	क्रम (i = 0; i < base->num_children; i++) अणु
		काष्ठा ice_sched_node *child = base->children[i];

		अगर (node == child)
			वापस true;

		अगर (child->tx_sched_layer > node->tx_sched_layer)
			वापस false;

		/* this recursion is पूर्णांकentional, and wouldn't
		 * go more than 8 calls
		 */
		अगर (ice_sched_find_node_in_subtree(hw, child, node))
			वापस true;
	पूर्ण
	वापस false;
पूर्ण

/**
 * ice_sched_get_मुक्त_qgrp - Scan all queue group siblings and find a मुक्त node
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_node: software VSI handle
 * @qgrp_node: first queue group node identअगरied क्रम scanning
 * @owner: LAN or RDMA
 *
 * This function retrieves a मुक्त LAN or RDMA queue group node by scanning
 * qgrp_node and its siblings क्रम the queue group with the fewest number
 * of queues currently asचिन्हित.
 */
अटल काष्ठा ice_sched_node *
ice_sched_get_मुक्त_qgrp(काष्ठा ice_port_info *pi,
			काष्ठा ice_sched_node *vsi_node,
			काष्ठा ice_sched_node *qgrp_node, u8 owner)
अणु
	काष्ठा ice_sched_node *min_qgrp;
	u8 min_children;

	अगर (!qgrp_node)
		वापस qgrp_node;
	min_children = qgrp_node->num_children;
	अगर (!min_children)
		वापस qgrp_node;
	min_qgrp = qgrp_node;
	/* scan all queue groups until find a node which has less than the
	 * minimum number of children. This way all queue group nodes get
	 * equal number of shares and active. The bandwidth will be equally
	 * distributed across all queues.
	 */
	जबतक (qgrp_node) अणु
		/* make sure the qgroup node is part of the VSI subtree */
		अगर (ice_sched_find_node_in_subtree(pi->hw, vsi_node, qgrp_node))
			अगर (qgrp_node->num_children < min_children &&
			    qgrp_node->owner == owner) अणु
				/* replace the new min queue group node */
				min_qgrp = qgrp_node;
				min_children = min_qgrp->num_children;
				/* अवरोध अगर it has no children, */
				अगर (!min_children)
					अवरोध;
			पूर्ण
		qgrp_node = qgrp_node->sibling;
	पूर्ण
	वापस min_qgrp;
पूर्ण

/**
 * ice_sched_get_मुक्त_qparent - Get a मुक्त LAN or RDMA queue group node
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: software VSI handle
 * @tc: branch number
 * @owner: LAN or RDMA
 *
 * This function retrieves a मुक्त LAN or RDMA queue group node
 */
काष्ठा ice_sched_node *
ice_sched_get_मुक्त_qparent(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc,
			   u8 owner)
अणु
	काष्ठा ice_sched_node *vsi_node, *qgrp_node;
	काष्ठा ice_vsi_ctx *vsi_ctx;
	u16 max_children;
	u8 qgrp_layer;

	qgrp_layer = ice_sched_get_qgrp_layer(pi->hw);
	max_children = pi->hw->max_children[qgrp_layer];

	vsi_ctx = ice_get_vsi_ctx(pi->hw, vsi_handle);
	अगर (!vsi_ctx)
		वापस शून्य;
	vsi_node = vsi_ctx->sched.vsi_node[tc];
	/* validate invalid VSI ID */
	अगर (!vsi_node)
		वापस शून्य;

	/* get the first queue group node from VSI sub-tree */
	qgrp_node = ice_sched_get_first_node(pi, vsi_node, qgrp_layer);
	जबतक (qgrp_node) अणु
		/* make sure the qgroup node is part of the VSI subtree */
		अगर (ice_sched_find_node_in_subtree(pi->hw, vsi_node, qgrp_node))
			अगर (qgrp_node->num_children < max_children &&
			    qgrp_node->owner == owner)
				अवरोध;
		qgrp_node = qgrp_node->sibling;
	पूर्ण

	/* Select the best queue group */
	वापस ice_sched_get_मुक्त_qgrp(pi, vsi_node, qgrp_node, owner);
पूर्ण

/**
 * ice_sched_get_vsi_node - Get a VSI node based on VSI ID
 * @pi: poपूर्णांकer to the port inक्रमmation काष्ठाure
 * @tc_node: poपूर्णांकer to the TC node
 * @vsi_handle: software VSI handle
 *
 * This function retrieves a VSI node क्रम a given VSI ID from a given
 * TC branch
 */
अटल काष्ठा ice_sched_node *
ice_sched_get_vsi_node(काष्ठा ice_port_info *pi, काष्ठा ice_sched_node *tc_node,
		       u16 vsi_handle)
अणु
	काष्ठा ice_sched_node *node;
	u8 vsi_layer;

	vsi_layer = ice_sched_get_vsi_layer(pi->hw);
	node = ice_sched_get_first_node(pi, tc_node, vsi_layer);

	/* Check whether it alपढ़ोy exists */
	जबतक (node) अणु
		अगर (node->vsi_handle == vsi_handle)
			वापस node;
		node = node->sibling;
	पूर्ण

	वापस node;
पूर्ण

/**
 * ice_sched_get_agg_node - Get an aggregator node based on aggregator ID
 * @pi: poपूर्णांकer to the port inक्रमmation काष्ठाure
 * @tc_node: poपूर्णांकer to the TC node
 * @agg_id: aggregator ID
 *
 * This function retrieves an aggregator node क्रम a given aggregator ID from
 * a given TC branch
 */
अटल काष्ठा ice_sched_node *
ice_sched_get_agg_node(काष्ठा ice_port_info *pi, काष्ठा ice_sched_node *tc_node,
		       u32 agg_id)
अणु
	काष्ठा ice_sched_node *node;
	काष्ठा ice_hw *hw = pi->hw;
	u8 agg_layer;

	अगर (!hw)
		वापस शून्य;
	agg_layer = ice_sched_get_agg_layer(hw);
	node = ice_sched_get_first_node(pi, tc_node, agg_layer);

	/* Check whether it alपढ़ोy exists */
	जबतक (node) अणु
		अगर (node->agg_id == agg_id)
			वापस node;
		node = node->sibling;
	पूर्ण

	वापस node;
पूर्ण

/**
 * ice_sched_calc_vsi_child_nodes - calculate number of VSI child nodes
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @num_qs: number of queues
 * @num_nodes: num nodes array
 *
 * This function calculates the number of VSI child nodes based on the
 * number of queues.
 */
अटल व्योम
ice_sched_calc_vsi_child_nodes(काष्ठा ice_hw *hw, u16 num_qs, u16 *num_nodes)
अणु
	u16 num = num_qs;
	u8 i, qgl, vsil;

	qgl = ice_sched_get_qgrp_layer(hw);
	vsil = ice_sched_get_vsi_layer(hw);

	/* calculate num nodes from queue group to VSI layer */
	क्रम (i = qgl; i > vsil; i--) अणु
		/* round to the next पूर्णांकeger अगर there is a reमुख्यder */
		num = DIV_ROUND_UP(num, hw->max_children[i]);

		/* need at least one node */
		num_nodes[i] = num ? num : 1;
	पूर्ण
पूर्ण

/**
 * ice_sched_add_vsi_child_nodes - add VSI child nodes to tree
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: software VSI handle
 * @tc_node: poपूर्णांकer to the TC node
 * @num_nodes: poपूर्णांकer to the num nodes that needs to be added per layer
 * @owner: node owner (LAN or RDMA)
 *
 * This function adds the VSI child nodes to tree. It माला_लो called क्रम
 * LAN and RDMA separately.
 */
अटल क्रमागत ice_status
ice_sched_add_vsi_child_nodes(काष्ठा ice_port_info *pi, u16 vsi_handle,
			      काष्ठा ice_sched_node *tc_node, u16 *num_nodes,
			      u8 owner)
अणु
	काष्ठा ice_sched_node *parent, *node;
	काष्ठा ice_hw *hw = pi->hw;
	क्रमागत ice_status status;
	u32 first_node_teid;
	u16 num_added = 0;
	u8 i, qgl, vsil;

	qgl = ice_sched_get_qgrp_layer(hw);
	vsil = ice_sched_get_vsi_layer(hw);
	parent = ice_sched_get_vsi_node(pi, tc_node, vsi_handle);
	क्रम (i = vsil + 1; i <= qgl; i++) अणु
		अगर (!parent)
			वापस ICE_ERR_CFG;

		status = ice_sched_add_nodes_to_layer(pi, tc_node, parent, i,
						      num_nodes[i],
						      &first_node_teid,
						      &num_added);
		अगर (status || num_nodes[i] != num_added)
			वापस ICE_ERR_CFG;

		/* The newly added node can be a new parent क्रम the next
		 * layer nodes
		 */
		अगर (num_added) अणु
			parent = ice_sched_find_node_by_teid(tc_node,
							     first_node_teid);
			node = parent;
			जबतक (node) अणु
				node->owner = owner;
				node = node->sibling;
			पूर्ण
		पूर्ण अन्यथा अणु
			parent = parent->children[0];
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_sched_calc_vsi_support_nodes - calculate number of VSI support nodes
 * @pi: poपूर्णांकer to the port info काष्ठाure
 * @tc_node: poपूर्णांकer to TC node
 * @num_nodes: poपूर्णांकer to num nodes array
 *
 * This function calculates the number of supported nodes needed to add this
 * VSI पूर्णांकo Tx tree including the VSI, parent and पूर्णांकermediate nodes in below
 * layers
 */
अटल व्योम
ice_sched_calc_vsi_support_nodes(काष्ठा ice_port_info *pi,
				 काष्ठा ice_sched_node *tc_node, u16 *num_nodes)
अणु
	काष्ठा ice_sched_node *node;
	u8 vsil;
	पूर्णांक i;

	vsil = ice_sched_get_vsi_layer(pi->hw);
	क्रम (i = vsil; i >= pi->hw->sw_entry_poपूर्णांक_layer; i--)
		/* Add पूर्णांकermediate nodes अगर TC has no children and
		 * need at least one node क्रम VSI
		 */
		अगर (!tc_node->num_children || i == vsil) अणु
			num_nodes[i]++;
		पूर्ण अन्यथा अणु
			/* If पूर्णांकermediate nodes are reached max children
			 * then add a new one.
			 */
			node = ice_sched_get_first_node(pi, tc_node, (u8)i);
			/* scan all the siblings */
			जबतक (node) अणु
				अगर (node->num_children < pi->hw->max_children[i])
					अवरोध;
				node = node->sibling;
			पूर्ण

			/* tree has one पूर्णांकermediate node to add this new VSI.
			 * So no need to calculate supported nodes क्रम below
			 * layers.
			 */
			अगर (node)
				अवरोध;
			/* all the nodes are full, allocate a new one */
			num_nodes[i]++;
		पूर्ण
पूर्ण

/**
 * ice_sched_add_vsi_support_nodes - add VSI supported nodes पूर्णांकo Tx tree
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: software VSI handle
 * @tc_node: poपूर्णांकer to TC node
 * @num_nodes: poपूर्णांकer to num nodes array
 *
 * This function adds the VSI supported nodes पूर्णांकo Tx tree including the
 * VSI, its parent and पूर्णांकermediate nodes in below layers
 */
अटल क्रमागत ice_status
ice_sched_add_vsi_support_nodes(काष्ठा ice_port_info *pi, u16 vsi_handle,
				काष्ठा ice_sched_node *tc_node, u16 *num_nodes)
अणु
	काष्ठा ice_sched_node *parent = tc_node;
	क्रमागत ice_status status;
	u32 first_node_teid;
	u16 num_added = 0;
	u8 i, vsil;

	अगर (!pi)
		वापस ICE_ERR_PARAM;

	vsil = ice_sched_get_vsi_layer(pi->hw);
	क्रम (i = pi->hw->sw_entry_poपूर्णांक_layer; i <= vsil; i++) अणु
		status = ice_sched_add_nodes_to_layer(pi, tc_node, parent,
						      i, num_nodes[i],
						      &first_node_teid,
						      &num_added);
		अगर (status || num_nodes[i] != num_added)
			वापस ICE_ERR_CFG;

		/* The newly added node can be a new parent क्रम the next
		 * layer nodes
		 */
		अगर (num_added)
			parent = ice_sched_find_node_by_teid(tc_node,
							     first_node_teid);
		अन्यथा
			parent = parent->children[0];

		अगर (!parent)
			वापस ICE_ERR_CFG;

		अगर (i == vsil)
			parent->vsi_handle = vsi_handle;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_sched_add_vsi_to_topo - add a new VSI पूर्णांकo tree
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: software VSI handle
 * @tc: TC number
 *
 * This function adds a new VSI पूर्णांकo scheduler tree
 */
अटल क्रमागत ice_status
ice_sched_add_vsi_to_topo(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc)
अणु
	u16 num_nodes[ICE_AQC_TOPO_MAX_LEVEL_NUM] = अणु 0 पूर्ण;
	काष्ठा ice_sched_node *tc_node;

	tc_node = ice_sched_get_tc_node(pi, tc);
	अगर (!tc_node)
		वापस ICE_ERR_PARAM;

	/* calculate number of supported nodes needed क्रम this VSI */
	ice_sched_calc_vsi_support_nodes(pi, tc_node, num_nodes);

	/* add VSI supported nodes to TC subtree */
	वापस ice_sched_add_vsi_support_nodes(pi, vsi_handle, tc_node,
					       num_nodes);
पूर्ण

/**
 * ice_sched_update_vsi_child_nodes - update VSI child nodes
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: software VSI handle
 * @tc: TC number
 * @new_numqs: new number of max queues
 * @owner: owner of this subtree
 *
 * This function updates the VSI child nodes based on the number of queues
 */
अटल क्रमागत ice_status
ice_sched_update_vsi_child_nodes(काष्ठा ice_port_info *pi, u16 vsi_handle,
				 u8 tc, u16 new_numqs, u8 owner)
अणु
	u16 new_num_nodes[ICE_AQC_TOPO_MAX_LEVEL_NUM] = अणु 0 पूर्ण;
	काष्ठा ice_sched_node *vsi_node;
	काष्ठा ice_sched_node *tc_node;
	काष्ठा ice_vsi_ctx *vsi_ctx;
	क्रमागत ice_status status = 0;
	काष्ठा ice_hw *hw = pi->hw;
	u16 prev_numqs;

	tc_node = ice_sched_get_tc_node(pi, tc);
	अगर (!tc_node)
		वापस ICE_ERR_CFG;

	vsi_node = ice_sched_get_vsi_node(pi, tc_node, vsi_handle);
	अगर (!vsi_node)
		वापस ICE_ERR_CFG;

	vsi_ctx = ice_get_vsi_ctx(hw, vsi_handle);
	अगर (!vsi_ctx)
		वापस ICE_ERR_PARAM;

	prev_numqs = vsi_ctx->sched.max_lanq[tc];
	/* num queues are not changed or less than the previous number */
	अगर (new_numqs <= prev_numqs)
		वापस status;
	status = ice_alloc_lan_q_ctx(hw, vsi_handle, tc, new_numqs);
	अगर (status)
		वापस status;

	अगर (new_numqs)
		ice_sched_calc_vsi_child_nodes(hw, new_numqs, new_num_nodes);
	/* Keep the max number of queue configuration all the समय. Update the
	 * tree only अगर number of queues > previous number of queues. This may
	 * leave some extra nodes in the tree अगर number of queues < previous
	 * number but that wouldn't harm anything. Removing those extra nodes
	 * may complicate the code अगर those nodes are part of SRL or
	 * inभागidually rate limited.
	 */
	status = ice_sched_add_vsi_child_nodes(pi, vsi_handle, tc_node,
					       new_num_nodes, owner);
	अगर (status)
		वापस status;
	vsi_ctx->sched.max_lanq[tc] = new_numqs;

	वापस 0;
पूर्ण

/**
 * ice_sched_cfg_vsi - configure the new/existing VSI
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: software VSI handle
 * @tc: TC number
 * @maxqs: max number of queues
 * @owner: LAN or RDMA
 * @enable: TC enabled or disabled
 *
 * This function adds/updates VSI nodes based on the number of queues. If TC is
 * enabled and VSI is in suspended state then resume the VSI back. If TC is
 * disabled then suspend the VSI अगर it is not alपढ़ोy.
 */
क्रमागत ice_status
ice_sched_cfg_vsi(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc, u16 maxqs,
		  u8 owner, bool enable)
अणु
	काष्ठा ice_sched_node *vsi_node, *tc_node;
	काष्ठा ice_vsi_ctx *vsi_ctx;
	क्रमागत ice_status status = 0;
	काष्ठा ice_hw *hw = pi->hw;

	ice_debug(pi->hw, ICE_DBG_SCHED, "add/config VSI %d\n", vsi_handle);
	tc_node = ice_sched_get_tc_node(pi, tc);
	अगर (!tc_node)
		वापस ICE_ERR_PARAM;
	vsi_ctx = ice_get_vsi_ctx(hw, vsi_handle);
	अगर (!vsi_ctx)
		वापस ICE_ERR_PARAM;
	vsi_node = ice_sched_get_vsi_node(pi, tc_node, vsi_handle);

	/* suspend the VSI अगर TC is not enabled */
	अगर (!enable) अणु
		अगर (vsi_node && vsi_node->in_use) अणु
			u32 teid = le32_to_cpu(vsi_node->info.node_teid);

			status = ice_sched_suspend_resume_elems(hw, 1, &teid,
								true);
			अगर (!status)
				vsi_node->in_use = false;
		पूर्ण
		वापस status;
	पूर्ण

	/* TC is enabled, अगर it is a new VSI then add it to the tree */
	अगर (!vsi_node) अणु
		status = ice_sched_add_vsi_to_topo(pi, vsi_handle, tc);
		अगर (status)
			वापस status;

		vsi_node = ice_sched_get_vsi_node(pi, tc_node, vsi_handle);
		अगर (!vsi_node)
			वापस ICE_ERR_CFG;

		vsi_ctx->sched.vsi_node[tc] = vsi_node;
		vsi_node->in_use = true;
		/* invalidate the max queues whenever VSI माला_लो added first समय
		 * पूर्णांकo the scheduler tree (boot or after reset). We need to
		 * recreate the child nodes all the समय in these हालs.
		 */
		vsi_ctx->sched.max_lanq[tc] = 0;
	पूर्ण

	/* update the VSI child nodes */
	status = ice_sched_update_vsi_child_nodes(pi, vsi_handle, tc, maxqs,
						  owner);
	अगर (status)
		वापस status;

	/* TC is enabled, resume the VSI अगर it is in the suspend state */
	अगर (!vsi_node->in_use) अणु
		u32 teid = le32_to_cpu(vsi_node->info.node_teid);

		status = ice_sched_suspend_resume_elems(hw, 1, &teid, false);
		अगर (!status)
			vsi_node->in_use = true;
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_sched_rm_agg_vsi_info - हटाओ aggregator related VSI info entry
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: software VSI handle
 *
 * This function हटाओs single aggregator VSI info entry from
 * aggregator list.
 */
अटल व्योम ice_sched_rm_agg_vsi_info(काष्ठा ice_port_info *pi, u16 vsi_handle)
अणु
	काष्ठा ice_sched_agg_info *agg_info;
	काष्ठा ice_sched_agg_info *aपंचांगp;

	list_क्रम_each_entry_safe(agg_info, aपंचांगp, &pi->hw->agg_list,
				 list_entry) अणु
		काष्ठा ice_sched_agg_vsi_info *agg_vsi_info;
		काष्ठा ice_sched_agg_vsi_info *vपंचांगp;

		list_क्रम_each_entry_safe(agg_vsi_info, vपंचांगp,
					 &agg_info->agg_vsi_list, list_entry)
			अगर (agg_vsi_info->vsi_handle == vsi_handle) अणु
				list_del(&agg_vsi_info->list_entry);
				devm_kमुक्त(ice_hw_to_dev(pi->hw),
					   agg_vsi_info);
				वापस;
			पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_sched_is_leaf_node_present - check क्रम a leaf node in the sub-tree
 * @node: poपूर्णांकer to the sub-tree node
 *
 * This function checks क्रम a leaf node presence in a given sub-tree node.
 */
अटल bool ice_sched_is_leaf_node_present(काष्ठा ice_sched_node *node)
अणु
	u8 i;

	क्रम (i = 0; i < node->num_children; i++)
		अगर (ice_sched_is_leaf_node_present(node->children[i]))
			वापस true;
	/* check क्रम a leaf node */
	वापस (node->info.data.elem_type == ICE_AQC_ELEM_TYPE_LEAF);
पूर्ण

/**
 * ice_sched_rm_vsi_cfg - हटाओ the VSI and its children nodes
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: software VSI handle
 * @owner: LAN or RDMA
 *
 * This function हटाओs the VSI and its LAN or RDMA children nodes from the
 * scheduler tree.
 */
अटल क्रमागत ice_status
ice_sched_rm_vsi_cfg(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 owner)
अणु
	क्रमागत ice_status status = ICE_ERR_PARAM;
	काष्ठा ice_vsi_ctx *vsi_ctx;
	u8 i;

	ice_debug(pi->hw, ICE_DBG_SCHED, "removing VSI %d\n", vsi_handle);
	अगर (!ice_is_vsi_valid(pi->hw, vsi_handle))
		वापस status;
	mutex_lock(&pi->sched_lock);
	vsi_ctx = ice_get_vsi_ctx(pi->hw, vsi_handle);
	अगर (!vsi_ctx)
		जाओ निकास_sched_rm_vsi_cfg;

	ice_क्रम_each_traffic_class(i) अणु
		काष्ठा ice_sched_node *vsi_node, *tc_node;
		u8 j = 0;

		tc_node = ice_sched_get_tc_node(pi, i);
		अगर (!tc_node)
			जारी;

		vsi_node = ice_sched_get_vsi_node(pi, tc_node, vsi_handle);
		अगर (!vsi_node)
			जारी;

		अगर (ice_sched_is_leaf_node_present(vsi_node)) अणु
			ice_debug(pi->hw, ICE_DBG_SCHED, "VSI has leaf nodes in TC %d\n", i);
			status = ICE_ERR_IN_USE;
			जाओ निकास_sched_rm_vsi_cfg;
		पूर्ण
		जबतक (j < vsi_node->num_children) अणु
			अगर (vsi_node->children[j]->owner == owner) अणु
				ice_मुक्त_sched_node(pi, vsi_node->children[j]);

				/* reset the counter again since the num
				 * children will be updated after node removal
				 */
				j = 0;
			पूर्ण अन्यथा अणु
				j++;
			पूर्ण
		पूर्ण
		/* हटाओ the VSI अगर it has no children */
		अगर (!vsi_node->num_children) अणु
			ice_मुक्त_sched_node(pi, vsi_node);
			vsi_ctx->sched.vsi_node[i] = शून्य;

			/* clean up aggregator related VSI info अगर any */
			ice_sched_rm_agg_vsi_info(pi, vsi_handle);
		पूर्ण
		अगर (owner == ICE_SCHED_NODE_OWNER_LAN)
			vsi_ctx->sched.max_lanq[i] = 0;
	पूर्ण
	status = 0;

निकास_sched_rm_vsi_cfg:
	mutex_unlock(&pi->sched_lock);
	वापस status;
पूर्ण

/**
 * ice_rm_vsi_lan_cfg - हटाओ VSI and its LAN children nodes
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: software VSI handle
 *
 * This function clears the VSI and its LAN children nodes from scheduler tree
 * क्रम all TCs.
 */
क्रमागत ice_status ice_rm_vsi_lan_cfg(काष्ठा ice_port_info *pi, u16 vsi_handle)
अणु
	वापस ice_sched_rm_vsi_cfg(pi, vsi_handle, ICE_SCHED_NODE_OWNER_LAN);
पूर्ण

/**
 * ice_get_agg_info - get the aggregator ID
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @agg_id: aggregator ID
 *
 * This function validates aggregator ID. The function वापसs info अगर
 * aggregator ID is present in list otherwise it वापसs null.
 */
अटल काष्ठा ice_sched_agg_info *
ice_get_agg_info(काष्ठा ice_hw *hw, u32 agg_id)
अणु
	काष्ठा ice_sched_agg_info *agg_info;

	list_क्रम_each_entry(agg_info, &hw->agg_list, list_entry)
		अगर (agg_info->agg_id == agg_id)
			वापस agg_info;

	वापस शून्य;
पूर्ण

/**
 * ice_sched_get_मुक्त_vsi_parent - Find a मुक्त parent node in aggregator subtree
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @node: poपूर्णांकer to a child node
 * @num_nodes: num nodes count array
 *
 * This function walks through the aggregator subtree to find a मुक्त parent
 * node
 */
अटल काष्ठा ice_sched_node *
ice_sched_get_मुक्त_vsi_parent(काष्ठा ice_hw *hw, काष्ठा ice_sched_node *node,
			      u16 *num_nodes)
अणु
	u8 l = node->tx_sched_layer;
	u8 vsil, i;

	vsil = ice_sched_get_vsi_layer(hw);

	/* Is it VSI parent layer ? */
	अगर (l == vsil - 1)
		वापस (node->num_children < hw->max_children[l]) ? node : शून्य;

	/* We have पूर्णांकermediate nodes. Let's walk through the subtree. If the
	 * पूर्णांकermediate node has space to add a new node then clear the count
	 */
	अगर (node->num_children < hw->max_children[l])
		num_nodes[l] = 0;
	/* The below recursive call is पूर्णांकentional and wouldn't go more than
	 * 2 or 3 iterations.
	 */

	क्रम (i = 0; i < node->num_children; i++) अणु
		काष्ठा ice_sched_node *parent;

		parent = ice_sched_get_मुक्त_vsi_parent(hw, node->children[i],
						       num_nodes);
		अगर (parent)
			वापस parent;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * ice_sched_update_parent - update the new parent in SW DB
 * @new_parent: poपूर्णांकer to a new parent node
 * @node: poपूर्णांकer to a child node
 *
 * This function हटाओs the child from the old parent and adds it to a new
 * parent
 */
अटल व्योम
ice_sched_update_parent(काष्ठा ice_sched_node *new_parent,
			काष्ठा ice_sched_node *node)
अणु
	काष्ठा ice_sched_node *old_parent;
	u8 i, j;

	old_parent = node->parent;

	/* update the old parent children */
	क्रम (i = 0; i < old_parent->num_children; i++)
		अगर (old_parent->children[i] == node) अणु
			क्रम (j = i + 1; j < old_parent->num_children; j++)
				old_parent->children[j - 1] =
					old_parent->children[j];
			old_parent->num_children--;
			अवरोध;
		पूर्ण

	/* now move the node to a new parent */
	new_parent->children[new_parent->num_children++] = node;
	node->parent = new_parent;
	node->info.parent_teid = new_parent->info.node_teid;
पूर्ण

/**
 * ice_sched_move_nodes - move child nodes to a given parent
 * @pi: port inक्रमmation काष्ठाure
 * @parent: poपूर्णांकer to parent node
 * @num_items: number of child nodes to be moved
 * @list: poपूर्णांकer to child node teids
 *
 * This function move the child nodes to a given parent.
 */
अटल क्रमागत ice_status
ice_sched_move_nodes(काष्ठा ice_port_info *pi, काष्ठा ice_sched_node *parent,
		     u16 num_items, u32 *list)
अणु
	काष्ठा ice_aqc_move_elem *buf;
	काष्ठा ice_sched_node *node;
	क्रमागत ice_status status = 0;
	u16 i, grps_movd = 0;
	काष्ठा ice_hw *hw;
	u16 buf_len;

	hw = pi->hw;

	अगर (!parent || !num_items)
		वापस ICE_ERR_PARAM;

	/* Does parent have enough space */
	अगर (parent->num_children + num_items >
	    hw->max_children[parent->tx_sched_layer])
		वापस ICE_ERR_AQ_FULL;

	buf_len = काष्ठा_size(buf, teid, 1);
	buf = kzalloc(buf_len, GFP_KERNEL);
	अगर (!buf)
		वापस ICE_ERR_NO_MEMORY;

	क्रम (i = 0; i < num_items; i++) अणु
		node = ice_sched_find_node_by_teid(pi->root, list[i]);
		अगर (!node) अणु
			status = ICE_ERR_PARAM;
			जाओ move_err_निकास;
		पूर्ण

		buf->hdr.src_parent_teid = node->info.parent_teid;
		buf->hdr.dest_parent_teid = parent->info.node_teid;
		buf->teid[0] = node->info.node_teid;
		buf->hdr.num_elems = cpu_to_le16(1);
		status = ice_aq_move_sched_elems(hw, 1, buf, buf_len,
						 &grps_movd, शून्य);
		अगर (status && grps_movd != 1) अणु
			status = ICE_ERR_CFG;
			जाओ move_err_निकास;
		पूर्ण

		/* update the SW DB */
		ice_sched_update_parent(parent, node);
	पूर्ण

move_err_निकास:
	kमुक्त(buf);
	वापस status;
पूर्ण

/**
 * ice_sched_move_vsi_to_agg - move VSI to aggregator node
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: software VSI handle
 * @agg_id: aggregator ID
 * @tc: TC number
 *
 * This function moves a VSI to an aggregator node or its subtree.
 * Intermediate nodes may be created अगर required.
 */
अटल क्रमागत ice_status
ice_sched_move_vsi_to_agg(काष्ठा ice_port_info *pi, u16 vsi_handle, u32 agg_id,
			  u8 tc)
अणु
	काष्ठा ice_sched_node *vsi_node, *agg_node, *tc_node, *parent;
	u16 num_nodes[ICE_AQC_TOPO_MAX_LEVEL_NUM] = अणु 0 पूर्ण;
	u32 first_node_teid, vsi_teid;
	क्रमागत ice_status status;
	u16 num_nodes_added;
	u8 aggl, vsil, i;

	tc_node = ice_sched_get_tc_node(pi, tc);
	अगर (!tc_node)
		वापस ICE_ERR_CFG;

	agg_node = ice_sched_get_agg_node(pi, tc_node, agg_id);
	अगर (!agg_node)
		वापस ICE_ERR_DOES_NOT_EXIST;

	vsi_node = ice_sched_get_vsi_node(pi, tc_node, vsi_handle);
	अगर (!vsi_node)
		वापस ICE_ERR_DOES_NOT_EXIST;

	/* Is this VSI alपढ़ोy part of given aggregator? */
	अगर (ice_sched_find_node_in_subtree(pi->hw, agg_node, vsi_node))
		वापस 0;

	aggl = ice_sched_get_agg_layer(pi->hw);
	vsil = ice_sched_get_vsi_layer(pi->hw);

	/* set पूर्णांकermediate node count to 1 between aggregator and VSI layers */
	क्रम (i = aggl + 1; i < vsil; i++)
		num_nodes[i] = 1;

	/* Check अगर the aggregator subtree has any मुक्त node to add the VSI */
	क्रम (i = 0; i < agg_node->num_children; i++) अणु
		parent = ice_sched_get_मुक्त_vsi_parent(pi->hw,
						       agg_node->children[i],
						       num_nodes);
		अगर (parent)
			जाओ move_nodes;
	पूर्ण

	/* add new nodes */
	parent = agg_node;
	क्रम (i = aggl + 1; i < vsil; i++) अणु
		status = ice_sched_add_nodes_to_layer(pi, tc_node, parent, i,
						      num_nodes[i],
						      &first_node_teid,
						      &num_nodes_added);
		अगर (status || num_nodes[i] != num_nodes_added)
			वापस ICE_ERR_CFG;

		/* The newly added node can be a new parent क्रम the next
		 * layer nodes
		 */
		अगर (num_nodes_added)
			parent = ice_sched_find_node_by_teid(tc_node,
							     first_node_teid);
		अन्यथा
			parent = parent->children[0];

		अगर (!parent)
			वापस ICE_ERR_CFG;
	पूर्ण

move_nodes:
	vsi_teid = le32_to_cpu(vsi_node->info.node_teid);
	वापस ice_sched_move_nodes(pi, parent, 1, &vsi_teid);
पूर्ण

/**
 * ice_move_all_vsi_to_dflt_agg - move all VSI(s) to शेष aggregator
 * @pi: port inक्रमmation काष्ठाure
 * @agg_info: aggregator info
 * @tc: traffic class number
 * @rm_vsi_info: true or false
 *
 * This function move all the VSI(s) to the शेष aggregator and delete
 * aggregator VSI info based on passed in boolean parameter rm_vsi_info. The
 * caller holds the scheduler lock.
 */
अटल क्रमागत ice_status
ice_move_all_vsi_to_dflt_agg(काष्ठा ice_port_info *pi,
			     काष्ठा ice_sched_agg_info *agg_info, u8 tc,
			     bool rm_vsi_info)
अणु
	काष्ठा ice_sched_agg_vsi_info *agg_vsi_info;
	काष्ठा ice_sched_agg_vsi_info *पंचांगp;
	क्रमागत ice_status status = 0;

	list_क्रम_each_entry_safe(agg_vsi_info, पंचांगp, &agg_info->agg_vsi_list,
				 list_entry) अणु
		u16 vsi_handle = agg_vsi_info->vsi_handle;

		/* Move VSI to शेष aggregator */
		अगर (!ice_is_tc_ena(agg_vsi_info->tc_biपंचांगap[0], tc))
			जारी;

		status = ice_sched_move_vsi_to_agg(pi, vsi_handle,
						   ICE_DFLT_AGG_ID, tc);
		अगर (status)
			अवरोध;

		clear_bit(tc, agg_vsi_info->tc_biपंचांगap);
		अगर (rm_vsi_info && !agg_vsi_info->tc_biपंचांगap[0]) अणु
			list_del(&agg_vsi_info->list_entry);
			devm_kमुक्त(ice_hw_to_dev(pi->hw), agg_vsi_info);
		पूर्ण
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_sched_is_agg_inuse - check whether the aggregator is in use or not
 * @pi: port inक्रमmation काष्ठाure
 * @node: node poपूर्णांकer
 *
 * This function checks whether the aggregator is attached with any VSI or not.
 */
अटल bool
ice_sched_is_agg_inuse(काष्ठा ice_port_info *pi, काष्ठा ice_sched_node *node)
अणु
	u8 vsil, i;

	vsil = ice_sched_get_vsi_layer(pi->hw);
	अगर (node->tx_sched_layer < vsil - 1) अणु
		क्रम (i = 0; i < node->num_children; i++)
			अगर (ice_sched_is_agg_inuse(pi, node->children[i]))
				वापस true;
		वापस false;
	पूर्ण अन्यथा अणु
		वापस node->num_children ? true : false;
	पूर्ण
पूर्ण

/**
 * ice_sched_rm_agg_cfg - हटाओ the aggregator node
 * @pi: port inक्रमmation काष्ठाure
 * @agg_id: aggregator ID
 * @tc: TC number
 *
 * This function हटाओs the aggregator node and पूर्णांकermediate nodes अगर any
 * from the given TC
 */
अटल क्रमागत ice_status
ice_sched_rm_agg_cfg(काष्ठा ice_port_info *pi, u32 agg_id, u8 tc)
अणु
	काष्ठा ice_sched_node *tc_node, *agg_node;
	काष्ठा ice_hw *hw = pi->hw;

	tc_node = ice_sched_get_tc_node(pi, tc);
	अगर (!tc_node)
		वापस ICE_ERR_CFG;

	agg_node = ice_sched_get_agg_node(pi, tc_node, agg_id);
	अगर (!agg_node)
		वापस ICE_ERR_DOES_NOT_EXIST;

	/* Can't हटाओ the aggregator node अगर it has children */
	अगर (ice_sched_is_agg_inuse(pi, agg_node))
		वापस ICE_ERR_IN_USE;

	/* need to हटाओ the whole subtree अगर aggregator node is the
	 * only child.
	 */
	जबतक (agg_node->tx_sched_layer > hw->sw_entry_poपूर्णांक_layer) अणु
		काष्ठा ice_sched_node *parent = agg_node->parent;

		अगर (!parent)
			वापस ICE_ERR_CFG;

		अगर (parent->num_children > 1)
			अवरोध;

		agg_node = parent;
	पूर्ण

	ice_मुक्त_sched_node(pi, agg_node);
	वापस 0;
पूर्ण

/**
 * ice_rm_agg_cfg_tc - हटाओ aggregator configuration क्रम TC
 * @pi: port inक्रमmation काष्ठाure
 * @agg_info: aggregator ID
 * @tc: TC number
 * @rm_vsi_info: bool value true or false
 *
 * This function हटाओs aggregator reference to VSI of given TC. It हटाओs
 * the aggregator configuration completely क्रम requested TC. The caller needs
 * to hold the scheduler lock.
 */
अटल क्रमागत ice_status
ice_rm_agg_cfg_tc(काष्ठा ice_port_info *pi, काष्ठा ice_sched_agg_info *agg_info,
		  u8 tc, bool rm_vsi_info)
अणु
	क्रमागत ice_status status = 0;

	/* If nothing to हटाओ - वापस success */
	अगर (!ice_is_tc_ena(agg_info->tc_biपंचांगap[0], tc))
		जाओ निकास_rm_agg_cfg_tc;

	status = ice_move_all_vsi_to_dflt_agg(pi, agg_info, tc, rm_vsi_info);
	अगर (status)
		जाओ निकास_rm_agg_cfg_tc;

	/* Delete aggregator node(s) */
	status = ice_sched_rm_agg_cfg(pi, agg_info->agg_id, tc);
	अगर (status)
		जाओ निकास_rm_agg_cfg_tc;

	clear_bit(tc, agg_info->tc_biपंचांगap);
निकास_rm_agg_cfg_tc:
	वापस status;
पूर्ण

/**
 * ice_save_agg_tc_biपंचांगap - save aggregator TC biपंचांगap
 * @pi: port inक्रमmation काष्ठाure
 * @agg_id: aggregator ID
 * @tc_biपंचांगap: 8 bits TC biपंचांगap
 *
 * Save aggregator TC biपंचांगap. This function needs to be called with scheduler
 * lock held.
 */
अटल क्रमागत ice_status
ice_save_agg_tc_biपंचांगap(काष्ठा ice_port_info *pi, u32 agg_id,
		       अचिन्हित दीर्घ *tc_biपंचांगap)
अणु
	काष्ठा ice_sched_agg_info *agg_info;

	agg_info = ice_get_agg_info(pi->hw, agg_id);
	अगर (!agg_info)
		वापस ICE_ERR_PARAM;
	biपंचांगap_copy(agg_info->replay_tc_biपंचांगap, tc_biपंचांगap,
		    ICE_MAX_TRAFFIC_CLASS);
	वापस 0;
पूर्ण

/**
 * ice_sched_add_agg_cfg - create an aggregator node
 * @pi: port inक्रमmation काष्ठाure
 * @agg_id: aggregator ID
 * @tc: TC number
 *
 * This function creates an aggregator node and पूर्णांकermediate nodes अगर required
 * क्रम the given TC
 */
अटल क्रमागत ice_status
ice_sched_add_agg_cfg(काष्ठा ice_port_info *pi, u32 agg_id, u8 tc)
अणु
	काष्ठा ice_sched_node *parent, *agg_node, *tc_node;
	u16 num_nodes[ICE_AQC_TOPO_MAX_LEVEL_NUM] = अणु 0 पूर्ण;
	क्रमागत ice_status status = 0;
	काष्ठा ice_hw *hw = pi->hw;
	u32 first_node_teid;
	u16 num_nodes_added;
	u8 i, aggl;

	tc_node = ice_sched_get_tc_node(pi, tc);
	अगर (!tc_node)
		वापस ICE_ERR_CFG;

	agg_node = ice_sched_get_agg_node(pi, tc_node, agg_id);
	/* Does Agg node alपढ़ोy exist ? */
	अगर (agg_node)
		वापस status;

	aggl = ice_sched_get_agg_layer(hw);

	/* need one node in Agg layer */
	num_nodes[aggl] = 1;

	/* Check whether the पूर्णांकermediate nodes have space to add the
	 * new aggregator. If they are full, then SW needs to allocate a new
	 * पूर्णांकermediate node on those layers
	 */
	क्रम (i = hw->sw_entry_poपूर्णांक_layer; i < aggl; i++) अणु
		parent = ice_sched_get_first_node(pi, tc_node, i);

		/* scan all the siblings */
		जबतक (parent) अणु
			अगर (parent->num_children < hw->max_children[i])
				अवरोध;
			parent = parent->sibling;
		पूर्ण

		/* all the nodes are full, reserve one क्रम this layer */
		अगर (!parent)
			num_nodes[i]++;
	पूर्ण

	/* add the aggregator node */
	parent = tc_node;
	क्रम (i = hw->sw_entry_poपूर्णांक_layer; i <= aggl; i++) अणु
		अगर (!parent)
			वापस ICE_ERR_CFG;

		status = ice_sched_add_nodes_to_layer(pi, tc_node, parent, i,
						      num_nodes[i],
						      &first_node_teid,
						      &num_nodes_added);
		अगर (status || num_nodes[i] != num_nodes_added)
			वापस ICE_ERR_CFG;

		/* The newly added node can be a new parent क्रम the next
		 * layer nodes
		 */
		अगर (num_nodes_added) अणु
			parent = ice_sched_find_node_by_teid(tc_node,
							     first_node_teid);
			/* रेजिस्टर aggregator ID with the aggregator node */
			अगर (parent && i == aggl)
				parent->agg_id = agg_id;
		पूर्ण अन्यथा अणु
			parent = parent->children[0];
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_sched_cfg_agg - configure aggregator node
 * @pi: port inक्रमmation काष्ठाure
 * @agg_id: aggregator ID
 * @agg_type: aggregator type queue, VSI, or aggregator group
 * @tc_biपंचांगap: bits TC biपंचांगap
 *
 * It रेजिस्टरs a unique aggregator node पूर्णांकo scheduler services. It
 * allows a user to रेजिस्टर with a unique ID to track it's resources.
 * The aggregator type determines अगर this is a queue group, VSI group
 * or aggregator group. It then creates the aggregator node(s) क्रम requested
 * TC(s) or हटाओs an existing aggregator node including its configuration
 * अगर indicated via tc_biपंचांगap. Call ice_rm_agg_cfg to release aggregator
 * resources and हटाओ aggregator ID.
 * This function needs to be called with scheduler lock held.
 */
अटल क्रमागत ice_status
ice_sched_cfg_agg(काष्ठा ice_port_info *pi, u32 agg_id,
		  क्रमागत ice_agg_type agg_type, अचिन्हित दीर्घ *tc_biपंचांगap)
अणु
	काष्ठा ice_sched_agg_info *agg_info;
	क्रमागत ice_status status = 0;
	काष्ठा ice_hw *hw = pi->hw;
	u8 tc;

	agg_info = ice_get_agg_info(hw, agg_id);
	अगर (!agg_info) अणु
		/* Create new entry क्रम new aggregator ID */
		agg_info = devm_kzalloc(ice_hw_to_dev(hw), माप(*agg_info),
					GFP_KERNEL);
		अगर (!agg_info)
			वापस ICE_ERR_NO_MEMORY;

		agg_info->agg_id = agg_id;
		agg_info->agg_type = agg_type;
		agg_info->tc_biपंचांगap[0] = 0;

		/* Initialize the aggregator VSI list head */
		INIT_LIST_HEAD(&agg_info->agg_vsi_list);

		/* Add new entry in aggregator list */
		list_add(&agg_info->list_entry, &hw->agg_list);
	पूर्ण
	/* Create aggregator node(s) क्रम requested TC(s) */
	ice_क्रम_each_traffic_class(tc) अणु
		अगर (!ice_is_tc_ena(*tc_biपंचांगap, tc)) अणु
			/* Delete aggregator cfg TC अगर it exists previously */
			status = ice_rm_agg_cfg_tc(pi, agg_info, tc, false);
			अगर (status)
				अवरोध;
			जारी;
		पूर्ण

		/* Check अगर aggregator node क्रम TC alपढ़ोy exists */
		अगर (ice_is_tc_ena(agg_info->tc_biपंचांगap[0], tc))
			जारी;

		/* Create new aggregator node क्रम TC */
		status = ice_sched_add_agg_cfg(pi, agg_id, tc);
		अगर (status)
			अवरोध;

		/* Save aggregator node's TC inक्रमmation */
		set_bit(tc, agg_info->tc_biपंचांगap);
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_cfg_agg - config aggregator node
 * @pi: port inक्रमmation काष्ठाure
 * @agg_id: aggregator ID
 * @agg_type: aggregator type queue, VSI, or aggregator group
 * @tc_biपंचांगap: bits TC biपंचांगap
 *
 * This function configures aggregator node(s).
 */
क्रमागत ice_status
ice_cfg_agg(काष्ठा ice_port_info *pi, u32 agg_id, क्रमागत ice_agg_type agg_type,
	    u8 tc_biपंचांगap)
अणु
	अचिन्हित दीर्घ biपंचांगap = tc_biपंचांगap;
	क्रमागत ice_status status;

	mutex_lock(&pi->sched_lock);
	status = ice_sched_cfg_agg(pi, agg_id, agg_type,
				   (अचिन्हित दीर्घ *)&biपंचांगap);
	अगर (!status)
		status = ice_save_agg_tc_biपंचांगap(pi, agg_id,
						(अचिन्हित दीर्घ *)&biपंचांगap);
	mutex_unlock(&pi->sched_lock);
	वापस status;
पूर्ण

/**
 * ice_get_agg_vsi_info - get the aggregator ID
 * @agg_info: aggregator info
 * @vsi_handle: software VSI handle
 *
 * The function वापसs aggregator VSI info based on VSI handle. This function
 * needs to be called with scheduler lock held.
 */
अटल काष्ठा ice_sched_agg_vsi_info *
ice_get_agg_vsi_info(काष्ठा ice_sched_agg_info *agg_info, u16 vsi_handle)
अणु
	काष्ठा ice_sched_agg_vsi_info *agg_vsi_info;

	list_क्रम_each_entry(agg_vsi_info, &agg_info->agg_vsi_list, list_entry)
		अगर (agg_vsi_info->vsi_handle == vsi_handle)
			वापस agg_vsi_info;

	वापस शून्य;
पूर्ण

/**
 * ice_get_vsi_agg_info - get the aggregator info of VSI
 * @hw: poपूर्णांकer to the hardware काष्ठाure
 * @vsi_handle: Sw VSI handle
 *
 * The function वापसs aggregator info of VSI represented via vsi_handle. The
 * VSI has in this हाल a dअगरferent aggregator than the शेष one. This
 * function needs to be called with scheduler lock held.
 */
अटल काष्ठा ice_sched_agg_info *
ice_get_vsi_agg_info(काष्ठा ice_hw *hw, u16 vsi_handle)
अणु
	काष्ठा ice_sched_agg_info *agg_info;

	list_क्रम_each_entry(agg_info, &hw->agg_list, list_entry) अणु
		काष्ठा ice_sched_agg_vsi_info *agg_vsi_info;

		agg_vsi_info = ice_get_agg_vsi_info(agg_info, vsi_handle);
		अगर (agg_vsi_info)
			वापस agg_info;
	पूर्ण
	वापस शून्य;
पूर्ण

/**
 * ice_save_agg_vsi_tc_biपंचांगap - save aggregator VSI TC biपंचांगap
 * @pi: port inक्रमmation काष्ठाure
 * @agg_id: aggregator ID
 * @vsi_handle: software VSI handle
 * @tc_biपंचांगap: TC biपंचांगap of enabled TC(s)
 *
 * Save VSI to aggregator TC biपंचांगap. This function needs to call with scheduler
 * lock held.
 */
अटल क्रमागत ice_status
ice_save_agg_vsi_tc_biपंचांगap(काष्ठा ice_port_info *pi, u32 agg_id, u16 vsi_handle,
			   अचिन्हित दीर्घ *tc_biपंचांगap)
अणु
	काष्ठा ice_sched_agg_vsi_info *agg_vsi_info;
	काष्ठा ice_sched_agg_info *agg_info;

	agg_info = ice_get_agg_info(pi->hw, agg_id);
	अगर (!agg_info)
		वापस ICE_ERR_PARAM;
	/* check अगर entry alपढ़ोy exist */
	agg_vsi_info = ice_get_agg_vsi_info(agg_info, vsi_handle);
	अगर (!agg_vsi_info)
		वापस ICE_ERR_PARAM;
	biपंचांगap_copy(agg_vsi_info->replay_tc_biपंचांगap, tc_biपंचांगap,
		    ICE_MAX_TRAFFIC_CLASS);
	वापस 0;
पूर्ण

/**
 * ice_sched_assoc_vsi_to_agg - associate/move VSI to new/शेष aggregator
 * @pi: port inक्रमmation काष्ठाure
 * @agg_id: aggregator ID
 * @vsi_handle: software VSI handle
 * @tc_biपंचांगap: TC biपंचांगap of enabled TC(s)
 *
 * This function moves VSI to a new or शेष aggregator node. If VSI is
 * alपढ़ोy associated to the aggregator node then no operation is perक्रमmed on
 * the tree. This function needs to be called with scheduler lock held.
 */
अटल क्रमागत ice_status
ice_sched_assoc_vsi_to_agg(काष्ठा ice_port_info *pi, u32 agg_id,
			   u16 vsi_handle, अचिन्हित दीर्घ *tc_biपंचांगap)
अणु
	काष्ठा ice_sched_agg_vsi_info *agg_vsi_info;
	काष्ठा ice_sched_agg_info *agg_info;
	क्रमागत ice_status status = 0;
	काष्ठा ice_hw *hw = pi->hw;
	u8 tc;

	अगर (!ice_is_vsi_valid(pi->hw, vsi_handle))
		वापस ICE_ERR_PARAM;
	agg_info = ice_get_agg_info(hw, agg_id);
	अगर (!agg_info)
		वापस ICE_ERR_PARAM;
	/* check अगर entry alपढ़ोy exist */
	agg_vsi_info = ice_get_agg_vsi_info(agg_info, vsi_handle);
	अगर (!agg_vsi_info) अणु
		/* Create new entry क्रम VSI under aggregator list */
		agg_vsi_info = devm_kzalloc(ice_hw_to_dev(hw),
					    माप(*agg_vsi_info), GFP_KERNEL);
		अगर (!agg_vsi_info)
			वापस ICE_ERR_PARAM;

		/* add VSI ID पूर्णांकo the aggregator list */
		agg_vsi_info->vsi_handle = vsi_handle;
		list_add(&agg_vsi_info->list_entry, &agg_info->agg_vsi_list);
	पूर्ण
	/* Move VSI node to new aggregator node क्रम requested TC(s) */
	ice_क्रम_each_traffic_class(tc) अणु
		अगर (!ice_is_tc_ena(*tc_biपंचांगap, tc))
			जारी;

		/* Move VSI to new aggregator */
		status = ice_sched_move_vsi_to_agg(pi, vsi_handle, agg_id, tc);
		अगर (status)
			अवरोध;

		set_bit(tc, agg_vsi_info->tc_biपंचांगap);
	पूर्ण
	वापस status;
पूर्ण

/**
 * ice_sched_rm_unused_rl_prof - हटाओ unused RL profile
 * @pi: port inक्रमmation काष्ठाure
 *
 * This function हटाओs unused rate limit profiles from the HW and
 * SW DB. The caller needs to hold scheduler lock.
 */
अटल व्योम ice_sched_rm_unused_rl_prof(काष्ठा ice_port_info *pi)
अणु
	u16 ln;

	क्रम (ln = 0; ln < pi->hw->num_tx_sched_layers; ln++) अणु
		काष्ठा ice_aqc_rl_profile_info *rl_prof_elem;
		काष्ठा ice_aqc_rl_profile_info *rl_prof_पंचांगp;

		list_क्रम_each_entry_safe(rl_prof_elem, rl_prof_पंचांगp,
					 &pi->rl_prof_list[ln], list_entry) अणु
			अगर (!ice_sched_del_rl_profile(pi->hw, rl_prof_elem))
				ice_debug(pi->hw, ICE_DBG_SCHED, "Removed rl profile\n");
		पूर्ण
	पूर्ण
पूर्ण

/**
 * ice_sched_update_elem - update element
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @node: poपूर्णांकer to node
 * @info: node info to update
 *
 * Update the HW DB, and local SW DB of node. Update the scheduling
 * parameters of node from argument info data buffer (Info->data buf) and
 * वापसs success or error on config sched element failure. The caller
 * needs to hold scheduler lock.
 */
अटल क्रमागत ice_status
ice_sched_update_elem(काष्ठा ice_hw *hw, काष्ठा ice_sched_node *node,
		      काष्ठा ice_aqc_txsched_elem_data *info)
अणु
	काष्ठा ice_aqc_txsched_elem_data buf;
	क्रमागत ice_status status;
	u16 elem_cfgd = 0;
	u16 num_elems = 1;

	buf = *info;
	/* Parent TEID is reserved field in this aq call */
	buf.parent_teid = 0;
	/* Element type is reserved field in this aq call */
	buf.data.elem_type = 0;
	/* Flags is reserved field in this aq call */
	buf.data.flags = 0;

	/* Update HW DB */
	/* Configure element node */
	status = ice_aq_cfg_sched_elems(hw, num_elems, &buf, माप(buf),
					&elem_cfgd, शून्य);
	अगर (status || elem_cfgd != num_elems) अणु
		ice_debug(hw, ICE_DBG_SCHED, "Config sched elem error\n");
		वापस ICE_ERR_CFG;
	पूर्ण

	/* Config success हाल */
	/* Now update local SW DB */
	/* Only copy the data portion of info buffer */
	node->info.data = info->data;
	वापस status;
पूर्ण

/**
 * ice_sched_cfg_node_bw_alloc - configure node BW weight/alloc params
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @node: sched node to configure
 * @rl_type: rate limit type CIR, EIR, or shared
 * @bw_alloc: BW weight/allocation
 *
 * This function configures node element's BW allocation.
 */
अटल क्रमागत ice_status
ice_sched_cfg_node_bw_alloc(काष्ठा ice_hw *hw, काष्ठा ice_sched_node *node,
			    क्रमागत ice_rl_type rl_type, u16 bw_alloc)
अणु
	काष्ठा ice_aqc_txsched_elem_data buf;
	काष्ठा ice_aqc_txsched_elem *data;

	buf = node->info;
	data = &buf.data;
	अगर (rl_type == ICE_MIN_BW) अणु
		data->valid_sections |= ICE_AQC_ELEM_VALID_CIR;
		data->cir_bw.bw_alloc = cpu_to_le16(bw_alloc);
	पूर्ण अन्यथा अगर (rl_type == ICE_MAX_BW) अणु
		data->valid_sections |= ICE_AQC_ELEM_VALID_EIR;
		data->eir_bw.bw_alloc = cpu_to_le16(bw_alloc);
	पूर्ण अन्यथा अणु
		वापस ICE_ERR_PARAM;
	पूर्ण

	/* Configure element */
	वापस ice_sched_update_elem(hw, node, &buf);
पूर्ण

/**
 * ice_move_vsi_to_agg - moves VSI to new or शेष aggregator
 * @pi: port inक्रमmation काष्ठाure
 * @agg_id: aggregator ID
 * @vsi_handle: software VSI handle
 * @tc_biपंचांगap: TC biपंचांगap of enabled TC(s)
 *
 * Move or associate VSI to a new or शेष aggregator node.
 */
क्रमागत ice_status
ice_move_vsi_to_agg(काष्ठा ice_port_info *pi, u32 agg_id, u16 vsi_handle,
		    u8 tc_biपंचांगap)
अणु
	अचिन्हित दीर्घ biपंचांगap = tc_biपंचांगap;
	क्रमागत ice_status status;

	mutex_lock(&pi->sched_lock);
	status = ice_sched_assoc_vsi_to_agg(pi, agg_id, vsi_handle,
					    (अचिन्हित दीर्घ *)&biपंचांगap);
	अगर (!status)
		status = ice_save_agg_vsi_tc_biपंचांगap(pi, agg_id, vsi_handle,
						    (अचिन्हित दीर्घ *)&biपंचांगap);
	mutex_unlock(&pi->sched_lock);
	वापस status;
पूर्ण

/**
 * ice_set_clear_cir_bw - set or clear CIR BW
 * @bw_t_info: bandwidth type inक्रमmation काष्ठाure
 * @bw: bandwidth in Kbps - Kilo bits per sec
 *
 * Save or clear CIR bandwidth (BW) in the passed param bw_t_info.
 */
अटल व्योम ice_set_clear_cir_bw(काष्ठा ice_bw_type_info *bw_t_info, u32 bw)
अणु
	अगर (bw == ICE_SCHED_DFLT_BW) अणु
		clear_bit(ICE_BW_TYPE_CIR, bw_t_info->bw_t_biपंचांगap);
		bw_t_info->cir_bw.bw = 0;
	पूर्ण अन्यथा अणु
		/* Save type of BW inक्रमmation */
		set_bit(ICE_BW_TYPE_CIR, bw_t_info->bw_t_biपंचांगap);
		bw_t_info->cir_bw.bw = bw;
	पूर्ण
पूर्ण

/**
 * ice_set_clear_eir_bw - set or clear EIR BW
 * @bw_t_info: bandwidth type inक्रमmation काष्ठाure
 * @bw: bandwidth in Kbps - Kilo bits per sec
 *
 * Save or clear EIR bandwidth (BW) in the passed param bw_t_info.
 */
अटल व्योम ice_set_clear_eir_bw(काष्ठा ice_bw_type_info *bw_t_info, u32 bw)
अणु
	अगर (bw == ICE_SCHED_DFLT_BW) अणु
		clear_bit(ICE_BW_TYPE_EIR, bw_t_info->bw_t_biपंचांगap);
		bw_t_info->eir_bw.bw = 0;
	पूर्ण अन्यथा अणु
		/* EIR BW and Shared BW profiles are mutually exclusive and
		 * hence only one of them may be set क्रम any given element.
		 * First clear earlier saved shared BW inक्रमmation.
		 */
		clear_bit(ICE_BW_TYPE_SHARED, bw_t_info->bw_t_biपंचांगap);
		bw_t_info->shared_bw = 0;
		/* save EIR BW inक्रमmation */
		set_bit(ICE_BW_TYPE_EIR, bw_t_info->bw_t_biपंचांगap);
		bw_t_info->eir_bw.bw = bw;
	पूर्ण
पूर्ण

/**
 * ice_set_clear_shared_bw - set or clear shared BW
 * @bw_t_info: bandwidth type inक्रमmation काष्ठाure
 * @bw: bandwidth in Kbps - Kilo bits per sec
 *
 * Save or clear shared bandwidth (BW) in the passed param bw_t_info.
 */
अटल व्योम ice_set_clear_shared_bw(काष्ठा ice_bw_type_info *bw_t_info, u32 bw)
अणु
	अगर (bw == ICE_SCHED_DFLT_BW) अणु
		clear_bit(ICE_BW_TYPE_SHARED, bw_t_info->bw_t_biपंचांगap);
		bw_t_info->shared_bw = 0;
	पूर्ण अन्यथा अणु
		/* EIR BW and Shared BW profiles are mutually exclusive and
		 * hence only one of them may be set क्रम any given element.
		 * First clear earlier saved EIR BW inक्रमmation.
		 */
		clear_bit(ICE_BW_TYPE_EIR, bw_t_info->bw_t_biपंचांगap);
		bw_t_info->eir_bw.bw = 0;
		/* save shared BW inक्रमmation */
		set_bit(ICE_BW_TYPE_SHARED, bw_t_info->bw_t_biपंचांगap);
		bw_t_info->shared_bw = bw;
	पूर्ण
पूर्ण

/**
 * ice_sched_calc_wakeup - calculate RL profile wakeup parameter
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @bw: bandwidth in Kbps
 *
 * This function calculates the wakeup parameter of RL profile.
 */
अटल u16 ice_sched_calc_wakeup(काष्ठा ice_hw *hw, s32 bw)
अणु
	s64 bytes_per_sec, wakeup_पूर्णांक, wakeup_a, wakeup_b, wakeup_f;
	s32 wakeup_f_पूर्णांक;
	u16 wakeup = 0;

	/* Get the wakeup पूर्णांकeger value */
	bytes_per_sec = भाग64_दीर्घ(((s64)bw * 1000), BITS_PER_BYTE);
	wakeup_पूर्णांक = भाग64_दीर्घ(hw->psm_clk_freq, bytes_per_sec);
	अगर (wakeup_पूर्णांक > 63) अणु
		wakeup = (u16)((1 << 15) | wakeup_पूर्णांक);
	पूर्ण अन्यथा अणु
		/* Calculate fraction value up to 4 decimals
		 * Convert Integer value to a स्थिरant multiplier
		 */
		wakeup_b = (s64)ICE_RL_PROF_MULTIPLIER * wakeup_पूर्णांक;
		wakeup_a = भाग64_दीर्घ((s64)ICE_RL_PROF_MULTIPLIER *
					   hw->psm_clk_freq, bytes_per_sec);

		/* Get Fraction value */
		wakeup_f = wakeup_a - wakeup_b;

		/* Round up the Fractional value via Ceil(Fractional value) */
		अगर (wakeup_f > भाग64_दीर्घ(ICE_RL_PROF_MULTIPLIER, 2))
			wakeup_f += 1;

		wakeup_f_पूर्णांक = (s32)भाग64_दीर्घ(wakeup_f * ICE_RL_PROF_FRACTION,
					       ICE_RL_PROF_MULTIPLIER);
		wakeup |= (u16)(wakeup_पूर्णांक << 9);
		wakeup |= (u16)(0x1ff & wakeup_f_पूर्णांक);
	पूर्ण

	वापस wakeup;
पूर्ण

/**
 * ice_sched_bw_to_rl_profile - convert BW to profile parameters
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @bw: bandwidth in Kbps
 * @profile: profile parameters to वापस
 *
 * This function converts the BW to profile काष्ठाure क्रमmat.
 */
अटल क्रमागत ice_status
ice_sched_bw_to_rl_profile(काष्ठा ice_hw *hw, u32 bw,
			   काष्ठा ice_aqc_rl_profile_elem *profile)
अणु
	क्रमागत ice_status status = ICE_ERR_PARAM;
	s64 bytes_per_sec, ts_rate, mv_पंचांगp;
	bool found = false;
	s32 encode = 0;
	s64 mv = 0;
	s32 i;

	/* Bw settings range is from 0.5Mb/sec to 100Gb/sec */
	अगर (bw < ICE_SCHED_MIN_BW || bw > ICE_SCHED_MAX_BW)
		वापस status;

	/* Bytes per second from Kbps */
	bytes_per_sec = भाग64_दीर्घ(((s64)bw * 1000), BITS_PER_BYTE);

	/* encode is 6 bits but really useful are 5 bits */
	क्रम (i = 0; i < 64; i++) अणु
		u64 घात_result = BIT_ULL(i);

		ts_rate = भाग64_दीर्घ((s64)hw->psm_clk_freq,
				     घात_result * ICE_RL_PROF_TS_MULTIPLIER);
		अगर (ts_rate <= 0)
			जारी;

		/* Multiplier value */
		mv_पंचांगp = भाग64_दीर्घ(bytes_per_sec * ICE_RL_PROF_MULTIPLIER,
				    ts_rate);

		/* Round to the nearest ICE_RL_PROF_MULTIPLIER */
		mv = round_up_64bit(mv_पंचांगp, ICE_RL_PROF_MULTIPLIER);

		/* First multiplier value greater than the given
		 * accuracy bytes
		 */
		अगर (mv > ICE_RL_PROF_ACCURACY_BYTES) अणु
			encode = i;
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (found) अणु
		u16 wm;

		wm = ice_sched_calc_wakeup(hw, bw);
		profile->rl_multiply = cpu_to_le16(mv);
		profile->wake_up_calc = cpu_to_le16(wm);
		profile->rl_encode = cpu_to_le16(encode);
		status = 0;
	पूर्ण अन्यथा अणु
		status = ICE_ERR_DOES_NOT_EXIST;
	पूर्ण

	वापस status;
पूर्ण

/**
 * ice_sched_add_rl_profile - add RL profile
 * @pi: port inक्रमmation काष्ठाure
 * @rl_type: type of rate limit BW - min, max, or shared
 * @bw: bandwidth in Kbps - Kilo bits per sec
 * @layer_num: specअगरies in which layer to create profile
 *
 * This function first checks the existing list क्रम corresponding BW
 * parameter. If it exists, it वापसs the associated profile otherwise
 * it creates a new rate limit profile क्रम requested BW, and adds it to
 * the HW DB and local list. It वापसs the new profile or null on error.
 * The caller needs to hold the scheduler lock.
 */
अटल काष्ठा ice_aqc_rl_profile_info *
ice_sched_add_rl_profile(काष्ठा ice_port_info *pi,
			 क्रमागत ice_rl_type rl_type, u32 bw, u8 layer_num)
अणु
	काष्ठा ice_aqc_rl_profile_info *rl_prof_elem;
	u16 profiles_added = 0, num_profiles = 1;
	काष्ठा ice_aqc_rl_profile_elem *buf;
	क्रमागत ice_status status;
	काष्ठा ice_hw *hw;
	u8 profile_type;

	अगर (layer_num >= ICE_AQC_TOPO_MAX_LEVEL_NUM)
		वापस शून्य;
	चयन (rl_type) अणु
	हाल ICE_MIN_BW:
		profile_type = ICE_AQC_RL_PROखाता_TYPE_CIR;
		अवरोध;
	हाल ICE_MAX_BW:
		profile_type = ICE_AQC_RL_PROखाता_TYPE_EIR;
		अवरोध;
	हाल ICE_SHARED_BW:
		profile_type = ICE_AQC_RL_PROखाता_TYPE_SRL;
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण

	अगर (!pi)
		वापस शून्य;
	hw = pi->hw;
	list_क्रम_each_entry(rl_prof_elem, &pi->rl_prof_list[layer_num],
			    list_entry)
		अगर ((rl_prof_elem->profile.flags & ICE_AQC_RL_PROखाता_TYPE_M) ==
		    profile_type && rl_prof_elem->bw == bw)
			/* Return existing profile ID info */
			वापस rl_prof_elem;

	/* Create new profile ID */
	rl_prof_elem = devm_kzalloc(ice_hw_to_dev(hw), माप(*rl_prof_elem),
				    GFP_KERNEL);

	अगर (!rl_prof_elem)
		वापस शून्य;

	status = ice_sched_bw_to_rl_profile(hw, bw, &rl_prof_elem->profile);
	अगर (status)
		जाओ निकास_add_rl_prof;

	rl_prof_elem->bw = bw;
	/* layer_num is zero relative, and fw expects level from 1 to 9 */
	rl_prof_elem->profile.level = layer_num + 1;
	rl_prof_elem->profile.flags = profile_type;
	rl_prof_elem->profile.max_burst_size = cpu_to_le16(hw->max_burst_size);

	/* Create new entry in HW DB */
	buf = &rl_prof_elem->profile;
	status = ice_aq_add_rl_profile(hw, num_profiles, buf, माप(*buf),
				       &profiles_added, शून्य);
	अगर (status || profiles_added != num_profiles)
		जाओ निकास_add_rl_prof;

	/* Good entry - add in the list */
	rl_prof_elem->prof_id_ref = 0;
	list_add(&rl_prof_elem->list_entry, &pi->rl_prof_list[layer_num]);
	वापस rl_prof_elem;

निकास_add_rl_prof:
	devm_kमुक्त(ice_hw_to_dev(hw), rl_prof_elem);
	वापस शून्य;
पूर्ण

/**
 * ice_sched_cfg_node_bw_lmt - configure node sched params
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @node: sched node to configure
 * @rl_type: rate limit type CIR, EIR, or shared
 * @rl_prof_id: rate limit profile ID
 *
 * This function configures node element's BW limit.
 */
अटल क्रमागत ice_status
ice_sched_cfg_node_bw_lmt(काष्ठा ice_hw *hw, काष्ठा ice_sched_node *node,
			  क्रमागत ice_rl_type rl_type, u16 rl_prof_id)
अणु
	काष्ठा ice_aqc_txsched_elem_data buf;
	काष्ठा ice_aqc_txsched_elem *data;

	buf = node->info;
	data = &buf.data;
	चयन (rl_type) अणु
	हाल ICE_MIN_BW:
		data->valid_sections |= ICE_AQC_ELEM_VALID_CIR;
		data->cir_bw.bw_profile_idx = cpu_to_le16(rl_prof_id);
		अवरोध;
	हाल ICE_MAX_BW:
		/* EIR BW and Shared BW profiles are mutually exclusive and
		 * hence only one of them may be set क्रम any given element
		 */
		अगर (data->valid_sections & ICE_AQC_ELEM_VALID_SHARED)
			वापस ICE_ERR_CFG;
		data->valid_sections |= ICE_AQC_ELEM_VALID_EIR;
		data->eir_bw.bw_profile_idx = cpu_to_le16(rl_prof_id);
		अवरोध;
	हाल ICE_SHARED_BW:
		/* Check क्रम removing shared BW */
		अगर (rl_prof_id == ICE_SCHED_NO_SHARED_RL_PROF_ID) अणु
			/* हटाओ shared profile */
			data->valid_sections &= ~ICE_AQC_ELEM_VALID_SHARED;
			data->srl_id = 0; /* clear SRL field */

			/* enable back EIR to शेष profile */
			data->valid_sections |= ICE_AQC_ELEM_VALID_EIR;
			data->eir_bw.bw_profile_idx =
				cpu_to_le16(ICE_SCHED_DFLT_RL_PROF_ID);
			अवरोध;
		पूर्ण
		/* EIR BW and Shared BW profiles are mutually exclusive and
		 * hence only one of them may be set क्रम any given element
		 */
		अगर ((data->valid_sections & ICE_AQC_ELEM_VALID_EIR) &&
		    (le16_to_cpu(data->eir_bw.bw_profile_idx) !=
			    ICE_SCHED_DFLT_RL_PROF_ID))
			वापस ICE_ERR_CFG;
		/* EIR BW is set to शेष, disable it */
		data->valid_sections &= ~ICE_AQC_ELEM_VALID_EIR;
		/* Okay to enable shared BW now */
		data->valid_sections |= ICE_AQC_ELEM_VALID_SHARED;
		data->srl_id = cpu_to_le16(rl_prof_id);
		अवरोध;
	शेष:
		/* Unknown rate limit type */
		वापस ICE_ERR_PARAM;
	पूर्ण

	/* Configure element */
	वापस ice_sched_update_elem(hw, node, &buf);
पूर्ण

/**
 * ice_sched_get_node_rl_prof_id - get node's rate limit profile ID
 * @node: sched node
 * @rl_type: rate limit type
 *
 * If existing profile matches, it वापसs the corresponding rate
 * limit profile ID, otherwise it वापसs an invalid ID as error.
 */
अटल u16
ice_sched_get_node_rl_prof_id(काष्ठा ice_sched_node *node,
			      क्रमागत ice_rl_type rl_type)
अणु
	u16 rl_prof_id = ICE_SCHED_INVAL_PROF_ID;
	काष्ठा ice_aqc_txsched_elem *data;

	data = &node->info.data;
	चयन (rl_type) अणु
	हाल ICE_MIN_BW:
		अगर (data->valid_sections & ICE_AQC_ELEM_VALID_CIR)
			rl_prof_id = le16_to_cpu(data->cir_bw.bw_profile_idx);
		अवरोध;
	हाल ICE_MAX_BW:
		अगर (data->valid_sections & ICE_AQC_ELEM_VALID_EIR)
			rl_prof_id = le16_to_cpu(data->eir_bw.bw_profile_idx);
		अवरोध;
	हाल ICE_SHARED_BW:
		अगर (data->valid_sections & ICE_AQC_ELEM_VALID_SHARED)
			rl_prof_id = le16_to_cpu(data->srl_id);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस rl_prof_id;
पूर्ण

/**
 * ice_sched_get_rl_prof_layer - selects rate limit profile creation layer
 * @pi: port inक्रमmation काष्ठाure
 * @rl_type: type of rate limit BW - min, max, or shared
 * @layer_index: layer index
 *
 * This function वापसs requested profile creation layer.
 */
अटल u8
ice_sched_get_rl_prof_layer(काष्ठा ice_port_info *pi, क्रमागत ice_rl_type rl_type,
			    u8 layer_index)
अणु
	काष्ठा ice_hw *hw = pi->hw;

	अगर (layer_index >= hw->num_tx_sched_layers)
		वापस ICE_SCHED_INVAL_LAYER_NUM;
	चयन (rl_type) अणु
	हाल ICE_MIN_BW:
		अगर (hw->layer_info[layer_index].max_cir_rl_profiles)
			वापस layer_index;
		अवरोध;
	हाल ICE_MAX_BW:
		अगर (hw->layer_info[layer_index].max_eir_rl_profiles)
			वापस layer_index;
		अवरोध;
	हाल ICE_SHARED_BW:
		/* अगर current layer करोesn't support SRL profile creation
		 * then try a layer up or करोwn.
		 */
		अगर (hw->layer_info[layer_index].max_srl_profiles)
			वापस layer_index;
		अन्यथा अगर (layer_index < hw->num_tx_sched_layers - 1 &&
			 hw->layer_info[layer_index + 1].max_srl_profiles)
			वापस layer_index + 1;
		अन्यथा अगर (layer_index > 0 &&
			 hw->layer_info[layer_index - 1].max_srl_profiles)
			वापस layer_index - 1;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ICE_SCHED_INVAL_LAYER_NUM;
पूर्ण

/**
 * ice_sched_get_srl_node - get shared rate limit node
 * @node: tree node
 * @srl_layer: shared rate limit layer
 *
 * This function वापसs SRL node to be used क्रम shared rate limit purpose.
 * The caller needs to hold scheduler lock.
 */
अटल काष्ठा ice_sched_node *
ice_sched_get_srl_node(काष्ठा ice_sched_node *node, u8 srl_layer)
अणु
	अगर (srl_layer > node->tx_sched_layer)
		वापस node->children[0];
	अन्यथा अगर (srl_layer < node->tx_sched_layer)
		/* Node can't be created without a parent. It will always
		 * have a valid parent except root node.
		 */
		वापस node->parent;
	अन्यथा
		वापस node;
पूर्ण

/**
 * ice_sched_rm_rl_profile - हटाओ RL profile ID
 * @pi: port inक्रमmation काष्ठाure
 * @layer_num: layer number where profiles are saved
 * @profile_type: profile type like EIR, CIR, or SRL
 * @profile_id: profile ID to हटाओ
 *
 * This function हटाओs rate limit profile from layer 'layer_num' of type
 * 'profile_type' and profile ID as 'profile_id'. The caller needs to hold
 * scheduler lock.
 */
अटल क्रमागत ice_status
ice_sched_rm_rl_profile(काष्ठा ice_port_info *pi, u8 layer_num, u8 profile_type,
			u16 profile_id)
अणु
	काष्ठा ice_aqc_rl_profile_info *rl_prof_elem;
	क्रमागत ice_status status = 0;

	अगर (layer_num >= ICE_AQC_TOPO_MAX_LEVEL_NUM)
		वापस ICE_ERR_PARAM;
	/* Check the existing list क्रम RL profile */
	list_क्रम_each_entry(rl_prof_elem, &pi->rl_prof_list[layer_num],
			    list_entry)
		अगर ((rl_prof_elem->profile.flags & ICE_AQC_RL_PROखाता_TYPE_M) ==
		    profile_type &&
		    le16_to_cpu(rl_prof_elem->profile.profile_id) ==
		    profile_id) अणु
			अगर (rl_prof_elem->prof_id_ref)
				rl_prof_elem->prof_id_ref--;

			/* Remove old profile ID from database */
			status = ice_sched_del_rl_profile(pi->hw, rl_prof_elem);
			अगर (status && status != ICE_ERR_IN_USE)
				ice_debug(pi->hw, ICE_DBG_SCHED, "Remove rl profile failed\n");
			अवरोध;
		पूर्ण
	अगर (status == ICE_ERR_IN_USE)
		status = 0;
	वापस status;
पूर्ण

/**
 * ice_sched_set_node_bw_dflt - set node's bandwidth limit to शेष
 * @pi: port inक्रमmation काष्ठाure
 * @node: poपूर्णांकer to node काष्ठाure
 * @rl_type: rate limit type min, max, or shared
 * @layer_num: layer number where RL profiles are saved
 *
 * This function configures node element's BW rate limit profile ID of
 * type CIR, EIR, or SRL to शेष. This function needs to be called
 * with the scheduler lock held.
 */
अटल क्रमागत ice_status
ice_sched_set_node_bw_dflt(काष्ठा ice_port_info *pi,
			   काष्ठा ice_sched_node *node,
			   क्रमागत ice_rl_type rl_type, u8 layer_num)
अणु
	क्रमागत ice_status status;
	काष्ठा ice_hw *hw;
	u8 profile_type;
	u16 rl_prof_id;
	u16 old_id;

	hw = pi->hw;
	चयन (rl_type) अणु
	हाल ICE_MIN_BW:
		profile_type = ICE_AQC_RL_PROखाता_TYPE_CIR;
		rl_prof_id = ICE_SCHED_DFLT_RL_PROF_ID;
		अवरोध;
	हाल ICE_MAX_BW:
		profile_type = ICE_AQC_RL_PROखाता_TYPE_EIR;
		rl_prof_id = ICE_SCHED_DFLT_RL_PROF_ID;
		अवरोध;
	हाल ICE_SHARED_BW:
		profile_type = ICE_AQC_RL_PROखाता_TYPE_SRL;
		/* No SRL is configured क्रम शेष हाल */
		rl_prof_id = ICE_SCHED_NO_SHARED_RL_PROF_ID;
		अवरोध;
	शेष:
		वापस ICE_ERR_PARAM;
	पूर्ण
	/* Save existing RL prof ID क्रम later clean up */
	old_id = ice_sched_get_node_rl_prof_id(node, rl_type);
	/* Configure BW scheduling parameters */
	status = ice_sched_cfg_node_bw_lmt(hw, node, rl_type, rl_prof_id);
	अगर (status)
		वापस status;

	/* Remove stale RL profile ID */
	अगर (old_id == ICE_SCHED_DFLT_RL_PROF_ID ||
	    old_id == ICE_SCHED_INVAL_PROF_ID)
		वापस 0;

	वापस ice_sched_rm_rl_profile(pi, layer_num, profile_type, old_id);
पूर्ण

/**
 * ice_sched_set_eir_srl_excl - set EIR/SRL exclusiveness
 * @pi: port inक्रमmation काष्ठाure
 * @node: poपूर्णांकer to node काष्ठाure
 * @layer_num: layer number where rate limit profiles are saved
 * @rl_type: rate limit type min, max, or shared
 * @bw: bandwidth value
 *
 * This function prepares node element's bandwidth to SRL or EIR exclusively.
 * EIR BW and Shared BW profiles are mutually exclusive and hence only one of
 * them may be set क्रम any given element. This function needs to be called
 * with the scheduler lock held.
 */
अटल क्रमागत ice_status
ice_sched_set_eir_srl_excl(काष्ठा ice_port_info *pi,
			   काष्ठा ice_sched_node *node,
			   u8 layer_num, क्रमागत ice_rl_type rl_type, u32 bw)
अणु
	अगर (rl_type == ICE_SHARED_BW) अणु
		/* SRL node passed in this हाल, it may be dअगरferent node */
		अगर (bw == ICE_SCHED_DFLT_BW)
			/* SRL being हटाओd, ice_sched_cfg_node_bw_lmt()
			 * enables EIR to शेष. EIR is not set in this
			 * हाल, so no additional action is required.
			 */
			वापस 0;

		/* SRL being configured, set EIR to शेष here.
		 * ice_sched_cfg_node_bw_lmt() disables EIR when it
		 * configures SRL
		 */
		वापस ice_sched_set_node_bw_dflt(pi, node, ICE_MAX_BW,
						  layer_num);
	पूर्ण अन्यथा अगर (rl_type == ICE_MAX_BW &&
		   node->info.data.valid_sections & ICE_AQC_ELEM_VALID_SHARED) अणु
		/* Remove Shared profile. Set शेष shared BW call
		 * हटाओs shared profile क्रम a node.
		 */
		वापस ice_sched_set_node_bw_dflt(pi, node,
						  ICE_SHARED_BW,
						  layer_num);
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_sched_set_node_bw - set node's bandwidth
 * @pi: port inक्रमmation काष्ठाure
 * @node: tree node
 * @rl_type: rate limit type min, max, or shared
 * @bw: bandwidth in Kbps - Kilo bits per sec
 * @layer_num: layer number
 *
 * This function adds new profile corresponding to requested BW, configures
 * node's RL profile ID of type CIR, EIR, or SRL, and हटाओs old profile
 * ID from local database. The caller needs to hold scheduler lock.
 */
अटल क्रमागत ice_status
ice_sched_set_node_bw(काष्ठा ice_port_info *pi, काष्ठा ice_sched_node *node,
		      क्रमागत ice_rl_type rl_type, u32 bw, u8 layer_num)
अणु
	काष्ठा ice_aqc_rl_profile_info *rl_prof_info;
	क्रमागत ice_status status = ICE_ERR_PARAM;
	काष्ठा ice_hw *hw = pi->hw;
	u16 old_id, rl_prof_id;

	rl_prof_info = ice_sched_add_rl_profile(pi, rl_type, bw, layer_num);
	अगर (!rl_prof_info)
		वापस status;

	rl_prof_id = le16_to_cpu(rl_prof_info->profile.profile_id);

	/* Save existing RL prof ID क्रम later clean up */
	old_id = ice_sched_get_node_rl_prof_id(node, rl_type);
	/* Configure BW scheduling parameters */
	status = ice_sched_cfg_node_bw_lmt(hw, node, rl_type, rl_prof_id);
	अगर (status)
		वापस status;

	/* New changes has been applied */
	/* Increment the profile ID reference count */
	rl_prof_info->prof_id_ref++;

	/* Check क्रम old ID removal */
	अगर ((old_id == ICE_SCHED_DFLT_RL_PROF_ID && rl_type != ICE_SHARED_BW) ||
	    old_id == ICE_SCHED_INVAL_PROF_ID || old_id == rl_prof_id)
		वापस 0;

	वापस ice_sched_rm_rl_profile(pi, layer_num,
				       rl_prof_info->profile.flags &
				       ICE_AQC_RL_PROखाता_TYPE_M, old_id);
पूर्ण

/**
 * ice_sched_set_node_bw_lmt - set node's BW limit
 * @pi: port inक्रमmation काष्ठाure
 * @node: tree node
 * @rl_type: rate limit type min, max, or shared
 * @bw: bandwidth in Kbps - Kilo bits per sec
 *
 * It updates node's BW limit parameters like BW RL profile ID of type CIR,
 * EIR, or SRL. The caller needs to hold scheduler lock.
 */
अटल क्रमागत ice_status
ice_sched_set_node_bw_lmt(काष्ठा ice_port_info *pi, काष्ठा ice_sched_node *node,
			  क्रमागत ice_rl_type rl_type, u32 bw)
अणु
	काष्ठा ice_sched_node *cfg_node = node;
	क्रमागत ice_status status;

	काष्ठा ice_hw *hw;
	u8 layer_num;

	अगर (!pi)
		वापस ICE_ERR_PARAM;
	hw = pi->hw;
	/* Remove unused RL profile IDs from HW and SW DB */
	ice_sched_rm_unused_rl_prof(pi);
	layer_num = ice_sched_get_rl_prof_layer(pi, rl_type,
						node->tx_sched_layer);
	अगर (layer_num >= hw->num_tx_sched_layers)
		वापस ICE_ERR_PARAM;

	अगर (rl_type == ICE_SHARED_BW) अणु
		/* SRL node may be dअगरferent */
		cfg_node = ice_sched_get_srl_node(node, layer_num);
		अगर (!cfg_node)
			वापस ICE_ERR_CFG;
	पूर्ण
	/* EIR BW and Shared BW profiles are mutually exclusive and
	 * hence only one of them may be set क्रम any given element
	 */
	status = ice_sched_set_eir_srl_excl(pi, cfg_node, layer_num, rl_type,
					    bw);
	अगर (status)
		वापस status;
	अगर (bw == ICE_SCHED_DFLT_BW)
		वापस ice_sched_set_node_bw_dflt(pi, cfg_node, rl_type,
						  layer_num);
	वापस ice_sched_set_node_bw(pi, cfg_node, rl_type, bw, layer_num);
पूर्ण

/**
 * ice_sched_set_node_bw_dflt_lmt - set node's BW limit to शेष
 * @pi: port inक्रमmation काष्ठाure
 * @node: poपूर्णांकer to node काष्ठाure
 * @rl_type: rate limit type min, max, or shared
 *
 * This function configures node element's BW rate limit profile ID of
 * type CIR, EIR, or SRL to शेष. This function needs to be called
 * with the scheduler lock held.
 */
अटल क्रमागत ice_status
ice_sched_set_node_bw_dflt_lmt(काष्ठा ice_port_info *pi,
			       काष्ठा ice_sched_node *node,
			       क्रमागत ice_rl_type rl_type)
अणु
	वापस ice_sched_set_node_bw_lmt(pi, node, rl_type,
					 ICE_SCHED_DFLT_BW);
पूर्ण

/**
 * ice_sched_validate_srl_node - Check node क्रम SRL applicability
 * @node: sched node to configure
 * @sel_layer: selected SRL layer
 *
 * This function checks अगर the SRL can be applied to a selected layer node on
 * behalf of the requested node (first argument). This function needs to be
 * called with scheduler lock held.
 */
अटल क्रमागत ice_status
ice_sched_validate_srl_node(काष्ठा ice_sched_node *node, u8 sel_layer)
अणु
	/* SRL profiles are not available on all layers. Check अगर the
	 * SRL profile can be applied to a node above or below the
	 * requested node. SRL configuration is possible only अगर the
	 * selected layer's node has single child.
	 */
	अगर (sel_layer == node->tx_sched_layer ||
	    ((sel_layer == node->tx_sched_layer + 1) &&
	    node->num_children == 1) ||
	    ((sel_layer == node->tx_sched_layer - 1) &&
	    (node->parent && node->parent->num_children == 1)))
		वापस 0;

	वापस ICE_ERR_CFG;
पूर्ण

/**
 * ice_sched_save_q_bw - save queue node's BW inक्रमmation
 * @q_ctx: queue context काष्ठाure
 * @rl_type: rate limit type min, max, or shared
 * @bw: bandwidth in Kbps - Kilo bits per sec
 *
 * Save BW inक्रमmation of queue type node क्रम post replay use.
 */
अटल क्रमागत ice_status
ice_sched_save_q_bw(काष्ठा ice_q_ctx *q_ctx, क्रमागत ice_rl_type rl_type, u32 bw)
अणु
	चयन (rl_type) अणु
	हाल ICE_MIN_BW:
		ice_set_clear_cir_bw(&q_ctx->bw_t_info, bw);
		अवरोध;
	हाल ICE_MAX_BW:
		ice_set_clear_eir_bw(&q_ctx->bw_t_info, bw);
		अवरोध;
	हाल ICE_SHARED_BW:
		ice_set_clear_shared_bw(&q_ctx->bw_t_info, bw);
		अवरोध;
	शेष:
		वापस ICE_ERR_PARAM;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * ice_sched_set_q_bw_lmt - sets queue BW limit
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: sw VSI handle
 * @tc: traffic class
 * @q_handle: software queue handle
 * @rl_type: min, max, or shared
 * @bw: bandwidth in Kbps
 *
 * This function sets BW limit of queue scheduling node.
 */
अटल क्रमागत ice_status
ice_sched_set_q_bw_lmt(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc,
		       u16 q_handle, क्रमागत ice_rl_type rl_type, u32 bw)
अणु
	क्रमागत ice_status status = ICE_ERR_PARAM;
	काष्ठा ice_sched_node *node;
	काष्ठा ice_q_ctx *q_ctx;

	अगर (!ice_is_vsi_valid(pi->hw, vsi_handle))
		वापस ICE_ERR_PARAM;
	mutex_lock(&pi->sched_lock);
	q_ctx = ice_get_lan_q_ctx(pi->hw, vsi_handle, tc, q_handle);
	अगर (!q_ctx)
		जाओ निकास_q_bw_lmt;
	node = ice_sched_find_node_by_teid(pi->root, q_ctx->q_teid);
	अगर (!node) अणु
		ice_debug(pi->hw, ICE_DBG_SCHED, "Wrong q_teid\n");
		जाओ निकास_q_bw_lmt;
	पूर्ण

	/* Return error अगर it is not a leaf node */
	अगर (node->info.data.elem_type != ICE_AQC_ELEM_TYPE_LEAF)
		जाओ निकास_q_bw_lmt;

	/* SRL bandwidth layer selection */
	अगर (rl_type == ICE_SHARED_BW) अणु
		u8 sel_layer; /* selected layer */

		sel_layer = ice_sched_get_rl_prof_layer(pi, rl_type,
							node->tx_sched_layer);
		अगर (sel_layer >= pi->hw->num_tx_sched_layers) अणु
			status = ICE_ERR_PARAM;
			जाओ निकास_q_bw_lmt;
		पूर्ण
		status = ice_sched_validate_srl_node(node, sel_layer);
		अगर (status)
			जाओ निकास_q_bw_lmt;
	पूर्ण

	अगर (bw == ICE_SCHED_DFLT_BW)
		status = ice_sched_set_node_bw_dflt_lmt(pi, node, rl_type);
	अन्यथा
		status = ice_sched_set_node_bw_lmt(pi, node, rl_type, bw);

	अगर (!status)
		status = ice_sched_save_q_bw(q_ctx, rl_type, bw);

निकास_q_bw_lmt:
	mutex_unlock(&pi->sched_lock);
	वापस status;
पूर्ण

/**
 * ice_cfg_q_bw_lmt - configure queue BW limit
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: sw VSI handle
 * @tc: traffic class
 * @q_handle: software queue handle
 * @rl_type: min, max, or shared
 * @bw: bandwidth in Kbps
 *
 * This function configures BW limit of queue scheduling node.
 */
क्रमागत ice_status
ice_cfg_q_bw_lmt(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc,
		 u16 q_handle, क्रमागत ice_rl_type rl_type, u32 bw)
अणु
	वापस ice_sched_set_q_bw_lmt(pi, vsi_handle, tc, q_handle, rl_type,
				      bw);
पूर्ण

/**
 * ice_cfg_q_bw_dflt_lmt - configure queue BW शेष limit
 * @pi: port inक्रमmation काष्ठाure
 * @vsi_handle: sw VSI handle
 * @tc: traffic class
 * @q_handle: software queue handle
 * @rl_type: min, max, or shared
 *
 * This function configures BW शेष limit of queue scheduling node.
 */
क्रमागत ice_status
ice_cfg_q_bw_dflt_lmt(काष्ठा ice_port_info *pi, u16 vsi_handle, u8 tc,
		      u16 q_handle, क्रमागत ice_rl_type rl_type)
अणु
	वापस ice_sched_set_q_bw_lmt(pi, vsi_handle, tc, q_handle, rl_type,
				      ICE_SCHED_DFLT_BW);
पूर्ण

/**
 * ice_cfg_rl_burst_size - Set burst size value
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @bytes: burst size in bytes
 *
 * This function configures/set the burst size to requested new value. The new
 * burst size value is used क्रम future rate limit calls. It करोesn't change the
 * existing or previously created RL profiles.
 */
क्रमागत ice_status ice_cfg_rl_burst_size(काष्ठा ice_hw *hw, u32 bytes)
अणु
	u16 burst_माप_प्रकारo_prog;

	अगर (bytes < ICE_MIN_BURST_SIZE_ALLOWED ||
	    bytes > ICE_MAX_BURST_SIZE_ALLOWED)
		वापस ICE_ERR_PARAM;
	अगर (ice_round_to_num(bytes, 64) <=
	    ICE_MAX_BURST_SIZE_64_BYTE_GRANULARITY) अणु
		/* 64 byte granularity हाल */
		/* Disable MSB granularity bit */
		burst_माप_प्रकारo_prog = ICE_64_BYTE_GRANULARITY;
		/* round number to nearest 64 byte granularity */
		bytes = ice_round_to_num(bytes, 64);
		/* The value is in 64 byte chunks */
		burst_माप_प्रकारo_prog |= (u16)(bytes / 64);
	पूर्ण अन्यथा अणु
		/* k bytes granularity हाल */
		/* Enable MSB granularity bit */
		burst_माप_प्रकारo_prog = ICE_KBYTE_GRANULARITY;
		/* round number to nearest 1024 granularity */
		bytes = ice_round_to_num(bytes, 1024);
		/* check rounding करोesn't go beyond allowed */
		अगर (bytes > ICE_MAX_BURST_SIZE_KBYTE_GRANULARITY)
			bytes = ICE_MAX_BURST_SIZE_KBYTE_GRANULARITY;
		/* The value is in k bytes */
		burst_माप_प्रकारo_prog |= (u16)(bytes / 1024);
	पूर्ण
	hw->max_burst_size = burst_माप_प्रकारo_prog;
	वापस 0;
पूर्ण

/**
 * ice_sched_replay_node_prio - re-configure node priority
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @node: sched node to configure
 * @priority: priority value
 *
 * This function configures node element's priority value. It
 * needs to be called with scheduler lock held.
 */
अटल क्रमागत ice_status
ice_sched_replay_node_prio(काष्ठा ice_hw *hw, काष्ठा ice_sched_node *node,
			   u8 priority)
अणु
	काष्ठा ice_aqc_txsched_elem_data buf;
	काष्ठा ice_aqc_txsched_elem *data;
	क्रमागत ice_status status;

	buf = node->info;
	data = &buf.data;
	data->valid_sections |= ICE_AQC_ELEM_VALID_GENERIC;
	data->generic = priority;

	/* Configure element */
	status = ice_sched_update_elem(hw, node, &buf);
	वापस status;
पूर्ण

/**
 * ice_sched_replay_node_bw - replay node(s) BW
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @node: sched node to configure
 * @bw_t_info: BW type inक्रमmation
 *
 * This function restores node's BW from bw_t_info. The caller needs
 * to hold the scheduler lock.
 */
अटल क्रमागत ice_status
ice_sched_replay_node_bw(काष्ठा ice_hw *hw, काष्ठा ice_sched_node *node,
			 काष्ठा ice_bw_type_info *bw_t_info)
अणु
	काष्ठा ice_port_info *pi = hw->port_info;
	क्रमागत ice_status status = ICE_ERR_PARAM;
	u16 bw_alloc;

	अगर (!node)
		वापस status;
	अगर (biपंचांगap_empty(bw_t_info->bw_t_biपंचांगap, ICE_BW_TYPE_CNT))
		वापस 0;
	अगर (test_bit(ICE_BW_TYPE_PRIO, bw_t_info->bw_t_biपंचांगap)) अणु
		status = ice_sched_replay_node_prio(hw, node,
						    bw_t_info->generic);
		अगर (status)
			वापस status;
	पूर्ण
	अगर (test_bit(ICE_BW_TYPE_CIR, bw_t_info->bw_t_biपंचांगap)) अणु
		status = ice_sched_set_node_bw_lmt(pi, node, ICE_MIN_BW,
						   bw_t_info->cir_bw.bw);
		अगर (status)
			वापस status;
	पूर्ण
	अगर (test_bit(ICE_BW_TYPE_CIR_WT, bw_t_info->bw_t_biपंचांगap)) अणु
		bw_alloc = bw_t_info->cir_bw.bw_alloc;
		status = ice_sched_cfg_node_bw_alloc(hw, node, ICE_MIN_BW,
						     bw_alloc);
		अगर (status)
			वापस status;
	पूर्ण
	अगर (test_bit(ICE_BW_TYPE_EIR, bw_t_info->bw_t_biपंचांगap)) अणु
		status = ice_sched_set_node_bw_lmt(pi, node, ICE_MAX_BW,
						   bw_t_info->eir_bw.bw);
		अगर (status)
			वापस status;
	पूर्ण
	अगर (test_bit(ICE_BW_TYPE_EIR_WT, bw_t_info->bw_t_biपंचांगap)) अणु
		bw_alloc = bw_t_info->eir_bw.bw_alloc;
		status = ice_sched_cfg_node_bw_alloc(hw, node, ICE_MAX_BW,
						     bw_alloc);
		अगर (status)
			वापस status;
	पूर्ण
	अगर (test_bit(ICE_BW_TYPE_SHARED, bw_t_info->bw_t_biपंचांगap))
		status = ice_sched_set_node_bw_lmt(pi, node, ICE_SHARED_BW,
						   bw_t_info->shared_bw);
	वापस status;
पूर्ण

/**
 * ice_sched_get_ena_tc_biपंचांगap - get enabled TC biपंचांगap
 * @pi: port info काष्ठा
 * @tc_biपंचांगap: 8 bits TC biपंचांगap to check
 * @ena_tc_biपंचांगap: 8 bits enabled TC biपंचांगap to वापस
 *
 * This function वापसs enabled TC biपंचांगap in variable ena_tc_biपंचांगap. Some TCs
 * may be missing, it वापसs enabled TCs. This function needs to be called with
 * scheduler lock held.
 */
अटल व्योम
ice_sched_get_ena_tc_biपंचांगap(काष्ठा ice_port_info *pi,
			    अचिन्हित दीर्घ *tc_biपंचांगap,
			    अचिन्हित दीर्घ *ena_tc_biपंचांगap)
अणु
	u8 tc;

	/* Some TC(s) may be missing after reset, adjust क्रम replay */
	ice_क्रम_each_traffic_class(tc)
		अगर (ice_is_tc_ena(*tc_biपंचांगap, tc) &&
		    (ice_sched_get_tc_node(pi, tc)))
			set_bit(tc, ena_tc_biपंचांगap);
पूर्ण

/**
 * ice_sched_replay_agg - recreate aggregator node(s)
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * This function recreate aggregator type nodes which are not replayed earlier.
 * It also replay aggregator BW inक्रमmation. These aggregator nodes are not
 * associated with VSI type node yet.
 */
व्योम ice_sched_replay_agg(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_port_info *pi = hw->port_info;
	काष्ठा ice_sched_agg_info *agg_info;

	mutex_lock(&pi->sched_lock);
	list_क्रम_each_entry(agg_info, &hw->agg_list, list_entry)
		/* replay aggregator (re-create aggregator node) */
		अगर (!biपंचांगap_equal(agg_info->tc_biपंचांगap, agg_info->replay_tc_biपंचांगap,
				  ICE_MAX_TRAFFIC_CLASS)) अणु
			DECLARE_BITMAP(replay_biपंचांगap, ICE_MAX_TRAFFIC_CLASS);
			क्रमागत ice_status status;

			biपंचांगap_zero(replay_biपंचांगap, ICE_MAX_TRAFFIC_CLASS);
			ice_sched_get_ena_tc_biपंचांगap(pi,
						    agg_info->replay_tc_biपंचांगap,
						    replay_biपंचांगap);
			status = ice_sched_cfg_agg(hw->port_info,
						   agg_info->agg_id,
						   ICE_AGG_TYPE_AGG,
						   replay_biपंचांगap);
			अगर (status) अणु
				dev_info(ice_hw_to_dev(hw),
					 "Replay agg id[%d] failed\n",
					 agg_info->agg_id);
				/* Move on to next one */
				जारी;
			पूर्ण
		पूर्ण
	mutex_unlock(&pi->sched_lock);
पूर्ण

/**
 * ice_sched_replay_agg_vsi_preinit - Agg/VSI replay pre initialization
 * @hw: poपूर्णांकer to the HW काष्ठा
 *
 * This function initialize aggregator(s) TC biपंचांगap to zero. A required
 * preinit step क्रम replaying aggregators.
 */
व्योम ice_sched_replay_agg_vsi_preinit(काष्ठा ice_hw *hw)
अणु
	काष्ठा ice_port_info *pi = hw->port_info;
	काष्ठा ice_sched_agg_info *agg_info;

	mutex_lock(&pi->sched_lock);
	list_क्रम_each_entry(agg_info, &hw->agg_list, list_entry) अणु
		काष्ठा ice_sched_agg_vsi_info *agg_vsi_info;

		agg_info->tc_biपंचांगap[0] = 0;
		list_क्रम_each_entry(agg_vsi_info, &agg_info->agg_vsi_list,
				    list_entry)
			agg_vsi_info->tc_biपंचांगap[0] = 0;
	पूर्ण
	mutex_unlock(&pi->sched_lock);
पूर्ण

/**
 * ice_sched_replay_vsi_agg - replay aggregator & VSI to aggregator node(s)
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: software VSI handle
 *
 * This function replays aggregator node, VSI to aggregator type nodes, and
 * their node bandwidth inक्रमmation. This function needs to be called with
 * scheduler lock held.
 */
अटल क्रमागत ice_status
ice_sched_replay_vsi_agg(काष्ठा ice_hw *hw, u16 vsi_handle)
अणु
	DECLARE_BITMAP(replay_biपंचांगap, ICE_MAX_TRAFFIC_CLASS);
	काष्ठा ice_sched_agg_vsi_info *agg_vsi_info;
	काष्ठा ice_port_info *pi = hw->port_info;
	काष्ठा ice_sched_agg_info *agg_info;
	क्रमागत ice_status status;

	biपंचांगap_zero(replay_biपंचांगap, ICE_MAX_TRAFFIC_CLASS);
	अगर (!ice_is_vsi_valid(hw, vsi_handle))
		वापस ICE_ERR_PARAM;
	agg_info = ice_get_vsi_agg_info(hw, vsi_handle);
	अगर (!agg_info)
		वापस 0; /* Not present in list - शेष Agg हाल */
	agg_vsi_info = ice_get_agg_vsi_info(agg_info, vsi_handle);
	अगर (!agg_vsi_info)
		वापस 0; /* Not present in list - शेष Agg हाल */
	ice_sched_get_ena_tc_biपंचांगap(pi, agg_info->replay_tc_biपंचांगap,
				    replay_biपंचांगap);
	/* Replay aggregator node associated to vsi_handle */
	status = ice_sched_cfg_agg(hw->port_info, agg_info->agg_id,
				   ICE_AGG_TYPE_AGG, replay_biपंचांगap);
	अगर (status)
		वापस status;

	biपंचांगap_zero(replay_biपंचांगap, ICE_MAX_TRAFFIC_CLASS);
	ice_sched_get_ena_tc_biपंचांगap(pi, agg_vsi_info->replay_tc_biपंचांगap,
				    replay_biपंचांगap);
	/* Move this VSI (vsi_handle) to above aggregator */
	वापस ice_sched_assoc_vsi_to_agg(pi, agg_info->agg_id, vsi_handle,
					  replay_biपंचांगap);
पूर्ण

/**
 * ice_replay_vsi_agg - replay VSI to aggregator node
 * @hw: poपूर्णांकer to the HW काष्ठा
 * @vsi_handle: software VSI handle
 *
 * This function replays association of VSI to aggregator type nodes, and
 * node bandwidth inक्रमmation.
 */
क्रमागत ice_status ice_replay_vsi_agg(काष्ठा ice_hw *hw, u16 vsi_handle)
अणु
	काष्ठा ice_port_info *pi = hw->port_info;
	क्रमागत ice_status status;

	mutex_lock(&pi->sched_lock);
	status = ice_sched_replay_vsi_agg(hw, vsi_handle);
	mutex_unlock(&pi->sched_lock);
	वापस status;
पूर्ण

/**
 * ice_sched_replay_q_bw - replay queue type node BW
 * @pi: port inक्रमmation काष्ठाure
 * @q_ctx: queue context काष्ठाure
 *
 * This function replays queue type node bandwidth. This function needs to be
 * called with scheduler lock held.
 */
क्रमागत ice_status
ice_sched_replay_q_bw(काष्ठा ice_port_info *pi, काष्ठा ice_q_ctx *q_ctx)
अणु
	काष्ठा ice_sched_node *q_node;

	/* Following also checks the presence of node in tree */
	q_node = ice_sched_find_node_by_teid(pi->root, q_ctx->q_teid);
	अगर (!q_node)
		वापस ICE_ERR_PARAM;
	वापस ice_sched_replay_node_bw(pi->hw, q_node, &q_ctx->bw_t_info);
पूर्ण
