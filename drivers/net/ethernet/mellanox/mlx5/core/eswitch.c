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

#समावेश <linux/etherdevice.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/mlx5_अगरc.h>
#समावेश <linux/mlx5/vport.h>
#समावेश <linux/mlx5/fs.h>
#समावेश <linux/mlx5/mpfs.h>
#समावेश "esw/acl/lgcy.h"
#समावेश "esw/legacy.h"
#समावेश "mlx5_core.h"
#समावेश "lib/eq.h"
#समावेश "eswitch.h"
#समावेश "fs_core.h"
#समावेश "devlink.h"
#समावेश "ecpf.h"
#समावेश "en/mod_hdr.h"

क्रमागत अणु
	MLX5_ACTION_NONE = 0,
	MLX5_ACTION_ADD  = 1,
	MLX5_ACTION_DEL  = 2,
पूर्ण;

/* Vport UC/MC hash node */
काष्ठा vport_addr अणु
	काष्ठा l2addr_node     node;
	u8                     action;
	u16                    vport;
	काष्ठा mlx5_flow_handle *flow_rule;
	bool mpfs; /* UC MAC was added to MPFs */
	/* A flag indicating that mac was added due to mc promiscuous vport */
	bool mc_promisc;
पूर्ण;

अटल पूर्णांक mlx5_eचयन_check(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	अगर (MLX5_CAP_GEN(dev, port_type) != MLX5_CAP_PORT_TYPE_ETH)
		वापस -EOPNOTSUPP;

	अगर (!MLX5_ESWITCH_MANAGER(dev))
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

काष्ठा mlx5_eचयन *mlx5_devlink_eचयन_get(काष्ठा devlink *devlink)
अणु
	काष्ठा mlx5_core_dev *dev = devlink_priv(devlink);
	पूर्णांक err;

	err = mlx5_eचयन_check(dev);
	अगर (err)
		वापस ERR_PTR(err);

	वापस dev->priv.eचयन;
पूर्ण

काष्ठा mlx5_vport *__must_check
mlx5_eचयन_get_vport(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	काष्ठा mlx5_vport *vport;

	अगर (!esw || !MLX5_CAP_GEN(esw->dev, vport_group_manager))
		वापस ERR_PTR(-EPERM);

	vport = xa_load(&esw->vports, vport_num);
	अगर (!vport) अणु
		esw_debug(esw->dev, "vport out of range: num(0x%x)\n", vport_num);
		वापस ERR_PTR(-EINVAL);
	पूर्ण
	वापस vport;
पूर्ण

अटल पूर्णांक arm_vport_context_events_cmd(काष्ठा mlx5_core_dev *dev, u16 vport,
					u32 events_mask)
अणु
	u32 in[MLX5_ST_SZ_DW(modअगरy_nic_vport_context_in)] = अणुपूर्ण;
	व्योम *nic_vport_ctx;

	MLX5_SET(modअगरy_nic_vport_context_in, in,
		 opcode, MLX5_CMD_OP_MODIFY_NIC_VPORT_CONTEXT);
	MLX5_SET(modअगरy_nic_vport_context_in, in, field_select.change_event, 1);
	MLX5_SET(modअगरy_nic_vport_context_in, in, vport_number, vport);
	MLX5_SET(modअगरy_nic_vport_context_in, in, other_vport, 1);
	nic_vport_ctx = MLX5_ADDR_OF(modअगरy_nic_vport_context_in,
				     in, nic_vport_context);

	MLX5_SET(nic_vport_context, nic_vport_ctx, arm_change_event, 1);

	अगर (events_mask & MLX5_VPORT_UC_ADDR_CHANGE)
		MLX5_SET(nic_vport_context, nic_vport_ctx,
			 event_on_uc_address_change, 1);
	अगर (events_mask & MLX5_VPORT_MC_ADDR_CHANGE)
		MLX5_SET(nic_vport_context, nic_vport_ctx,
			 event_on_mc_address_change, 1);
	अगर (events_mask & MLX5_VPORT_PROMISC_CHANGE)
		MLX5_SET(nic_vport_context, nic_vport_ctx,
			 event_on_promisc_change, 1);

	वापस mlx5_cmd_exec_in(dev, modअगरy_nic_vport_context, in);
पूर्ण

/* E-Switch vport context HW commands */
पूर्णांक mlx5_eचयन_modअगरy_esw_vport_context(काष्ठा mlx5_core_dev *dev, u16 vport,
					  bool other_vport, व्योम *in)
अणु
	MLX5_SET(modअगरy_esw_vport_context_in, in, opcode,
		 MLX5_CMD_OP_MODIFY_ESW_VPORT_CONTEXT);
	MLX5_SET(modअगरy_esw_vport_context_in, in, vport_number, vport);
	MLX5_SET(modअगरy_esw_vport_context_in, in, other_vport, other_vport);
	वापस mlx5_cmd_exec_in(dev, modअगरy_esw_vport_context, in);
पूर्ण

अटल पूर्णांक modअगरy_esw_vport_cvlan(काष्ठा mlx5_core_dev *dev, u16 vport,
				  u16 vlan, u8 qos, u8 set_flags)
अणु
	u32 in[MLX5_ST_SZ_DW(modअगरy_esw_vport_context_in)] = अणुपूर्ण;

	अगर (!MLX5_CAP_ESW(dev, vport_cvlan_strip) ||
	    !MLX5_CAP_ESW(dev, vport_cvlan_insert_अगर_not_exist))
		वापस -EOPNOTSUPP;

	esw_debug(dev, "Set Vport[%d] VLAN %d qos %d set=%x\n",
		  vport, vlan, qos, set_flags);

	अगर (set_flags & SET_VLAN_STRIP)
		MLX5_SET(modअगरy_esw_vport_context_in, in,
			 esw_vport_context.vport_cvlan_strip, 1);

	अगर (set_flags & SET_VLAN_INSERT) अणु
		/* insert only अगर no vlan in packet */
		MLX5_SET(modअगरy_esw_vport_context_in, in,
			 esw_vport_context.vport_cvlan_insert, 1);

		MLX5_SET(modअगरy_esw_vport_context_in, in,
			 esw_vport_context.cvlan_pcp, qos);
		MLX5_SET(modअगरy_esw_vport_context_in, in,
			 esw_vport_context.cvlan_id, vlan);
	पूर्ण

	MLX5_SET(modअगरy_esw_vport_context_in, in,
		 field_select.vport_cvlan_strip, 1);
	MLX5_SET(modअगरy_esw_vport_context_in, in,
		 field_select.vport_cvlan_insert, 1);

	वापस mlx5_eचयन_modअगरy_esw_vport_context(dev, vport, true, in);
पूर्ण

/* E-Switch FDB */
अटल काष्ठा mlx5_flow_handle *
__esw_fdb_set_vport_rule(काष्ठा mlx5_eचयन *esw, u16 vport, bool rx_rule,
			 u8 mac_c[ETH_ALEN], u8 mac_v[ETH_ALEN])
अणु
	पूर्णांक match_header = (is_zero_ether_addr(mac_c) ? 0 :
			    MLX5_MATCH_OUTER_HEADERS);
	काष्ठा mlx5_flow_handle *flow_rule = शून्य;
	काष्ठा mlx5_flow_act flow_act = अणु0पूर्ण;
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_spec *spec;
	व्योम *mv_misc = शून्य;
	व्योम *mc_misc = शून्य;
	u8 *dmac_v = शून्य;
	u8 *dmac_c = शून्य;

	अगर (rx_rule)
		match_header |= MLX5_MATCH_MISC_PARAMETERS;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस शून्य;

	dmac_v = MLX5_ADDR_OF(fte_match_param, spec->match_value,
			      outer_headers.dmac_47_16);
	dmac_c = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
			      outer_headers.dmac_47_16);

	अगर (match_header & MLX5_MATCH_OUTER_HEADERS) अणु
		ether_addr_copy(dmac_v, mac_v);
		ether_addr_copy(dmac_c, mac_c);
	पूर्ण

	अगर (match_header & MLX5_MATCH_MISC_PARAMETERS) अणु
		mv_misc  = MLX5_ADDR_OF(fte_match_param, spec->match_value,
					misc_parameters);
		mc_misc  = MLX5_ADDR_OF(fte_match_param, spec->match_criteria,
					misc_parameters);
		MLX5_SET(fte_match_set_misc, mv_misc, source_port, MLX5_VPORT_UPLINK);
		MLX5_SET_TO_ONES(fte_match_set_misc, mc_misc, source_port);
	पूर्ण

	dest.type = MLX5_FLOW_DESTINATION_TYPE_VPORT;
	dest.vport.num = vport;

	esw_debug(esw->dev,
		  "\tFDB add rule dmac_v(%pM) dmac_c(%pM) -> vport(%d)\n",
		  dmac_v, dmac_c, vport);
	spec->match_criteria_enable = match_header;
	flow_act.action =  MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	flow_rule =
		mlx5_add_flow_rules(esw->fdb_table.legacy.fdb, spec,
				    &flow_act, &dest, 1);
	अगर (IS_ERR(flow_rule)) अणु
		esw_warn(esw->dev,
			 "FDB: Failed to add flow rule: dmac_v(%pM) dmac_c(%pM) -> vport(%d), err(%ld)\n",
			 dmac_v, dmac_c, vport, PTR_ERR(flow_rule));
		flow_rule = शून्य;
	पूर्ण

	kvमुक्त(spec);
	वापस flow_rule;
पूर्ण

अटल काष्ठा mlx5_flow_handle *
esw_fdb_set_vport_rule(काष्ठा mlx5_eचयन *esw, u8 mac[ETH_ALEN], u16 vport)
अणु
	u8 mac_c[ETH_ALEN];

	eth_broadcast_addr(mac_c);
	वापस __esw_fdb_set_vport_rule(esw, vport, false, mac_c, mac);
पूर्ण

अटल काष्ठा mlx5_flow_handle *
esw_fdb_set_vport_allmulti_rule(काष्ठा mlx5_eचयन *esw, u16 vport)
अणु
	u8 mac_c[ETH_ALEN];
	u8 mac_v[ETH_ALEN];

	eth_zero_addr(mac_c);
	eth_zero_addr(mac_v);
	mac_c[0] = 0x01;
	mac_v[0] = 0x01;
	वापस __esw_fdb_set_vport_rule(esw, vport, false, mac_c, mac_v);
पूर्ण

अटल काष्ठा mlx5_flow_handle *
esw_fdb_set_vport_promisc_rule(काष्ठा mlx5_eचयन *esw, u16 vport)
अणु
	u8 mac_c[ETH_ALEN];
	u8 mac_v[ETH_ALEN];

	eth_zero_addr(mac_c);
	eth_zero_addr(mac_v);
	वापस __esw_fdb_set_vport_rule(esw, vport, true, mac_c, mac_v);
पूर्ण

/* E-Switch vport UC/MC lists management */
प्रकार पूर्णांक (*vport_addr_action)(काष्ठा mlx5_eचयन *esw,
				 काष्ठा vport_addr *vaddr);

अटल पूर्णांक esw_add_uc_addr(काष्ठा mlx5_eचयन *esw, काष्ठा vport_addr *vaddr)
अणु
	u8 *mac = vaddr->node.addr;
	u16 vport = vaddr->vport;
	पूर्णांक err;

	/* Skip mlx5_mpfs_add_mac क्रम eचयन_managers,
	 * it is alपढ़ोy करोne by its netdev in mlx5e_execute_l2_action
	 */
	अगर (mlx5_esw_is_manager_vport(esw, vport))
		जाओ fdb_add;

	err = mlx5_mpfs_add_mac(esw->dev, mac);
	अगर (err) अणु
		esw_warn(esw->dev,
			 "Failed to add L2 table mac(%pM) for vport(0x%x), err(%d)\n",
			 mac, vport, err);
		वापस err;
	पूर्ण
	vaddr->mpfs = true;

fdb_add:
	/* SRIOV is enabled: Forward UC MAC to vport */
	अगर (esw->fdb_table.legacy.fdb && esw->mode == MLX5_ESWITCH_LEGACY)
		vaddr->flow_rule = esw_fdb_set_vport_rule(esw, mac, vport);

	esw_debug(esw->dev, "\tADDED UC MAC: vport[%d] %pM fr(%p)\n",
		  vport, mac, vaddr->flow_rule);

	वापस 0;
पूर्ण

अटल पूर्णांक esw_del_uc_addr(काष्ठा mlx5_eचयन *esw, काष्ठा vport_addr *vaddr)
अणु
	u8 *mac = vaddr->node.addr;
	u16 vport = vaddr->vport;
	पूर्णांक err = 0;

	/* Skip mlx5_mpfs_del_mac क्रम eचयन managers,
	 * it is alपढ़ोy करोne by its netdev in mlx5e_execute_l2_action
	 */
	अगर (!vaddr->mpfs || mlx5_esw_is_manager_vport(esw, vport))
		जाओ fdb_del;

	err = mlx5_mpfs_del_mac(esw->dev, mac);
	अगर (err)
		esw_warn(esw->dev,
			 "Failed to del L2 table mac(%pM) for vport(%d), err(%d)\n",
			 mac, vport, err);
	vaddr->mpfs = false;

fdb_del:
	अगर (vaddr->flow_rule)
		mlx5_del_flow_rules(vaddr->flow_rule);
	vaddr->flow_rule = शून्य;

	वापस 0;
पूर्ण

अटल व्योम update_allmulti_vports(काष्ठा mlx5_eचयन *esw,
				   काष्ठा vport_addr *vaddr,
				   काष्ठा esw_mc_addr *esw_mc)
अणु
	u8 *mac = vaddr->node.addr;
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;
	u16 vport_num;

	mlx5_esw_क्रम_each_vport(esw, i, vport) अणु
		काष्ठा hlist_head *vport_hash = vport->mc_list;
		काष्ठा vport_addr *iter_vaddr =
					l2addr_hash_find(vport_hash,
							 mac,
							 काष्ठा vport_addr);
		vport_num = vport->vport;
		अगर (IS_ERR_OR_शून्य(vport->allmulti_rule) ||
		    vaddr->vport == vport_num)
			जारी;
		चयन (vaddr->action) अणु
		हाल MLX5_ACTION_ADD:
			अगर (iter_vaddr)
				जारी;
			iter_vaddr = l2addr_hash_add(vport_hash, mac,
						     काष्ठा vport_addr,
						     GFP_KERNEL);
			अगर (!iter_vaddr) अणु
				esw_warn(esw->dev,
					 "ALL-MULTI: Failed to add MAC(%pM) to vport[%d] DB\n",
					 mac, vport_num);
				जारी;
			पूर्ण
			iter_vaddr->vport = vport_num;
			iter_vaddr->flow_rule =
					esw_fdb_set_vport_rule(esw,
							       mac,
							       vport_num);
			iter_vaddr->mc_promisc = true;
			अवरोध;
		हाल MLX5_ACTION_DEL:
			अगर (!iter_vaddr)
				जारी;
			mlx5_del_flow_rules(iter_vaddr->flow_rule);
			l2addr_hash_del(iter_vaddr);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक esw_add_mc_addr(काष्ठा mlx5_eचयन *esw, काष्ठा vport_addr *vaddr)
अणु
	काष्ठा hlist_head *hash = esw->mc_table;
	काष्ठा esw_mc_addr *esw_mc;
	u8 *mac = vaddr->node.addr;
	u16 vport = vaddr->vport;

	अगर (!esw->fdb_table.legacy.fdb)
		वापस 0;

	esw_mc = l2addr_hash_find(hash, mac, काष्ठा esw_mc_addr);
	अगर (esw_mc)
		जाओ add;

	esw_mc = l2addr_hash_add(hash, mac, काष्ठा esw_mc_addr, GFP_KERNEL);
	अगर (!esw_mc)
		वापस -ENOMEM;

	esw_mc->uplink_rule = /* Forward MC MAC to Uplink */
		esw_fdb_set_vport_rule(esw, mac, MLX5_VPORT_UPLINK);

	/* Add this multicast mac to all the mc promiscuous vports */
	update_allmulti_vports(esw, vaddr, esw_mc);

add:
	/* If the multicast mac is added as a result of mc promiscuous vport,
	 * करोn't increment the multicast ref count
	 */
	अगर (!vaddr->mc_promisc)
		esw_mc->refcnt++;

	/* Forward MC MAC to vport */
	vaddr->flow_rule = esw_fdb_set_vport_rule(esw, mac, vport);
	esw_debug(esw->dev,
		  "\tADDED MC MAC: vport[%d] %pM fr(%p) refcnt(%d) uplinkfr(%p)\n",
		  vport, mac, vaddr->flow_rule,
		  esw_mc->refcnt, esw_mc->uplink_rule);
	वापस 0;
पूर्ण

अटल पूर्णांक esw_del_mc_addr(काष्ठा mlx5_eचयन *esw, काष्ठा vport_addr *vaddr)
अणु
	काष्ठा hlist_head *hash = esw->mc_table;
	काष्ठा esw_mc_addr *esw_mc;
	u8 *mac = vaddr->node.addr;
	u16 vport = vaddr->vport;

	अगर (!esw->fdb_table.legacy.fdb)
		वापस 0;

	esw_mc = l2addr_hash_find(hash, mac, काष्ठा esw_mc_addr);
	अगर (!esw_mc) अणु
		esw_warn(esw->dev,
			 "Failed to find eswitch MC addr for MAC(%pM) vport(%d)",
			 mac, vport);
		वापस -EINVAL;
	पूर्ण
	esw_debug(esw->dev,
		  "\tDELETE MC MAC: vport[%d] %pM fr(%p) refcnt(%d) uplinkfr(%p)\n",
		  vport, mac, vaddr->flow_rule, esw_mc->refcnt,
		  esw_mc->uplink_rule);

	अगर (vaddr->flow_rule)
		mlx5_del_flow_rules(vaddr->flow_rule);
	vaddr->flow_rule = शून्य;

	/* If the multicast mac is added as a result of mc promiscuous vport,
	 * करोn't decrement the multicast ref count.
	 */
	अगर (vaddr->mc_promisc || (--esw_mc->refcnt > 0))
		वापस 0;

	/* Remove this multicast mac from all the mc promiscuous vports */
	update_allmulti_vports(esw, vaddr, esw_mc);

	अगर (esw_mc->uplink_rule)
		mlx5_del_flow_rules(esw_mc->uplink_rule);

	l2addr_hash_del(esw_mc);
	वापस 0;
पूर्ण

/* Apply vport UC/MC list to HW l2 table and FDB table */
अटल व्योम esw_apply_vport_addr_list(काष्ठा mlx5_eचयन *esw,
				      काष्ठा mlx5_vport *vport, पूर्णांक list_type)
अणु
	bool is_uc = list_type == MLX5_NVPRT_LIST_TYPE_UC;
	vport_addr_action vport_addr_add;
	vport_addr_action vport_addr_del;
	काष्ठा vport_addr *addr;
	काष्ठा l2addr_node *node;
	काष्ठा hlist_head *hash;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक hi;

	vport_addr_add = is_uc ? esw_add_uc_addr :
				 esw_add_mc_addr;
	vport_addr_del = is_uc ? esw_del_uc_addr :
				 esw_del_mc_addr;

	hash = is_uc ? vport->uc_list : vport->mc_list;
	क्रम_each_l2hash_node(node, पंचांगp, hash, hi) अणु
		addr = container_of(node, काष्ठा vport_addr, node);
		चयन (addr->action) अणु
		हाल MLX5_ACTION_ADD:
			vport_addr_add(esw, addr);
			addr->action = MLX5_ACTION_NONE;
			अवरोध;
		हाल MLX5_ACTION_DEL:
			vport_addr_del(esw, addr);
			l2addr_hash_del(addr);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

/* Sync vport UC/MC list from vport context */
अटल व्योम esw_update_vport_addr_list(काष्ठा mlx5_eचयन *esw,
				       काष्ठा mlx5_vport *vport, पूर्णांक list_type)
अणु
	bool is_uc = list_type == MLX5_NVPRT_LIST_TYPE_UC;
	u8 (*mac_list)[ETH_ALEN];
	काष्ठा l2addr_node *node;
	काष्ठा vport_addr *addr;
	काष्ठा hlist_head *hash;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक size;
	पूर्णांक err;
	पूर्णांक hi;
	पूर्णांक i;

	size = is_uc ? MLX5_MAX_UC_PER_VPORT(esw->dev) :
		       MLX5_MAX_MC_PER_VPORT(esw->dev);

	mac_list = kसुस्मृति(size, ETH_ALEN, GFP_KERNEL);
	अगर (!mac_list)
		वापस;

	hash = is_uc ? vport->uc_list : vport->mc_list;

	क्रम_each_l2hash_node(node, पंचांगp, hash, hi) अणु
		addr = container_of(node, काष्ठा vport_addr, node);
		addr->action = MLX5_ACTION_DEL;
	पूर्ण

	अगर (!vport->enabled)
		जाओ out;

	err = mlx5_query_nic_vport_mac_list(esw->dev, vport->vport, list_type,
					    mac_list, &size);
	अगर (err)
		जाओ out;
	esw_debug(esw->dev, "vport[%d] context update %s list size (%d)\n",
		  vport->vport, is_uc ? "UC" : "MC", size);

	क्रम (i = 0; i < size; i++) अणु
		अगर (is_uc && !is_valid_ether_addr(mac_list[i]))
			जारी;

		अगर (!is_uc && !is_multicast_ether_addr(mac_list[i]))
			जारी;

		addr = l2addr_hash_find(hash, mac_list[i], काष्ठा vport_addr);
		अगर (addr) अणु
			addr->action = MLX5_ACTION_NONE;
			/* If this mac was previously added because of allmulti
			 * promiscuous rx mode, its now converted to be original
			 * vport mac.
			 */
			अगर (addr->mc_promisc) अणु
				काष्ठा esw_mc_addr *esw_mc =
					l2addr_hash_find(esw->mc_table,
							 mac_list[i],
							 काष्ठा esw_mc_addr);
				अगर (!esw_mc) अणु
					esw_warn(esw->dev,
						 "Failed to MAC(%pM) in mcast DB\n",
						 mac_list[i]);
					जारी;
				पूर्ण
				esw_mc->refcnt++;
				addr->mc_promisc = false;
			पूर्ण
			जारी;
		पूर्ण

		addr = l2addr_hash_add(hash, mac_list[i], काष्ठा vport_addr,
				       GFP_KERNEL);
		अगर (!addr) अणु
			esw_warn(esw->dev,
				 "Failed to add MAC(%pM) to vport[%d] DB\n",
				 mac_list[i], vport->vport);
			जारी;
		पूर्ण
		addr->vport = vport->vport;
		addr->action = MLX5_ACTION_ADD;
	पूर्ण
out:
	kमुक्त(mac_list);
पूर्ण

/* Sync vport UC/MC list from vport context
 * Must be called after esw_update_vport_addr_list
 */
अटल व्योम esw_update_vport_mc_promisc(काष्ठा mlx5_eचयन *esw,
					काष्ठा mlx5_vport *vport)
अणु
	काष्ठा l2addr_node *node;
	काष्ठा vport_addr *addr;
	काष्ठा hlist_head *hash;
	काष्ठा hlist_node *पंचांगp;
	पूर्णांक hi;

	hash = vport->mc_list;

	क्रम_each_l2hash_node(node, पंचांगp, esw->mc_table, hi) अणु
		u8 *mac = node->addr;

		addr = l2addr_hash_find(hash, mac, काष्ठा vport_addr);
		अगर (addr) अणु
			अगर (addr->action == MLX5_ACTION_DEL)
				addr->action = MLX5_ACTION_NONE;
			जारी;
		पूर्ण
		addr = l2addr_hash_add(hash, mac, काष्ठा vport_addr,
				       GFP_KERNEL);
		अगर (!addr) अणु
			esw_warn(esw->dev,
				 "Failed to add allmulti MAC(%pM) to vport[%d] DB\n",
				 mac, vport->vport);
			जारी;
		पूर्ण
		addr->vport = vport->vport;
		addr->action = MLX5_ACTION_ADD;
		addr->mc_promisc = true;
	पूर्ण
पूर्ण

/* Apply vport rx mode to HW FDB table */
अटल व्योम esw_apply_vport_rx_mode(काष्ठा mlx5_eचयन *esw,
				    काष्ठा mlx5_vport *vport,
				    bool promisc, bool mc_promisc)
अणु
	काष्ठा esw_mc_addr *allmulti_addr = &esw->mc_promisc;

	अगर (IS_ERR_OR_शून्य(vport->allmulti_rule) != mc_promisc)
		जाओ promisc;

	अगर (mc_promisc) अणु
		vport->allmulti_rule =
			esw_fdb_set_vport_allmulti_rule(esw, vport->vport);
		अगर (!allmulti_addr->uplink_rule)
			allmulti_addr->uplink_rule =
				esw_fdb_set_vport_allmulti_rule(esw,
								MLX5_VPORT_UPLINK);
		allmulti_addr->refcnt++;
	पूर्ण अन्यथा अगर (vport->allmulti_rule) अणु
		mlx5_del_flow_rules(vport->allmulti_rule);
		vport->allmulti_rule = शून्य;

		अगर (--allmulti_addr->refcnt > 0)
			जाओ promisc;

		अगर (allmulti_addr->uplink_rule)
			mlx5_del_flow_rules(allmulti_addr->uplink_rule);
		allmulti_addr->uplink_rule = शून्य;
	पूर्ण

promisc:
	अगर (IS_ERR_OR_शून्य(vport->promisc_rule) != promisc)
		वापस;

	अगर (promisc) अणु
		vport->promisc_rule =
			esw_fdb_set_vport_promisc_rule(esw, vport->vport);
	पूर्ण अन्यथा अगर (vport->promisc_rule) अणु
		mlx5_del_flow_rules(vport->promisc_rule);
		vport->promisc_rule = शून्य;
	पूर्ण
पूर्ण

/* Sync vport rx mode from vport context */
अटल व्योम esw_update_vport_rx_mode(काष्ठा mlx5_eचयन *esw,
				     काष्ठा mlx5_vport *vport)
अणु
	पूर्णांक promisc_all = 0;
	पूर्णांक promisc_uc = 0;
	पूर्णांक promisc_mc = 0;
	पूर्णांक err;

	err = mlx5_query_nic_vport_promisc(esw->dev,
					   vport->vport,
					   &promisc_uc,
					   &promisc_mc,
					   &promisc_all);
	अगर (err)
		वापस;
	esw_debug(esw->dev, "vport[%d] context update rx mode promisc_all=%d, all_multi=%d\n",
		  vport->vport, promisc_all, promisc_mc);

	अगर (!vport->info.trusted || !vport->enabled) अणु
		promisc_uc = 0;
		promisc_mc = 0;
		promisc_all = 0;
	पूर्ण

	esw_apply_vport_rx_mode(esw, vport, promisc_all,
				(promisc_all || promisc_mc));
पूर्ण

व्योम esw_vport_change_handle_locked(काष्ठा mlx5_vport *vport)
अणु
	काष्ठा mlx5_core_dev *dev = vport->dev;
	काष्ठा mlx5_eचयन *esw = dev->priv.eचयन;
	u8 mac[ETH_ALEN];

	mlx5_query_nic_vport_mac_address(dev, vport->vport, true, mac);
	esw_debug(dev, "vport[%d] Context Changed: perm mac: %pM\n",
		  vport->vport, mac);

	अगर (vport->enabled_events & MLX5_VPORT_UC_ADDR_CHANGE) अणु
		esw_update_vport_addr_list(esw, vport, MLX5_NVPRT_LIST_TYPE_UC);
		esw_apply_vport_addr_list(esw, vport, MLX5_NVPRT_LIST_TYPE_UC);
	पूर्ण

	अगर (vport->enabled_events & MLX5_VPORT_MC_ADDR_CHANGE)
		esw_update_vport_addr_list(esw, vport, MLX5_NVPRT_LIST_TYPE_MC);

	अगर (vport->enabled_events & MLX5_VPORT_PROMISC_CHANGE) अणु
		esw_update_vport_rx_mode(esw, vport);
		अगर (!IS_ERR_OR_शून्य(vport->allmulti_rule))
			esw_update_vport_mc_promisc(esw, vport);
	पूर्ण

	अगर (vport->enabled_events & (MLX5_VPORT_PROMISC_CHANGE | MLX5_VPORT_MC_ADDR_CHANGE))
		esw_apply_vport_addr_list(esw, vport, MLX5_NVPRT_LIST_TYPE_MC);

	esw_debug(esw->dev, "vport[%d] Context Changed: Done\n", vport->vport);
	अगर (vport->enabled)
		arm_vport_context_events_cmd(dev, vport->vport,
					     vport->enabled_events);
पूर्ण

अटल व्योम esw_vport_change_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx5_vport *vport =
		container_of(work, काष्ठा mlx5_vport, vport_change_handler);
	काष्ठा mlx5_eचयन *esw = vport->dev->priv.eचयन;

	mutex_lock(&esw->state_lock);
	esw_vport_change_handle_locked(vport);
	mutex_unlock(&esw->state_lock);
पूर्ण

अटल bool element_type_supported(काष्ठा mlx5_eचयन *esw, पूर्णांक type)
अणु
	स्थिर काष्ठा mlx5_core_dev *dev = esw->dev;

	चयन (type) अणु
	हाल SCHEDULING_CONTEXT_ELEMENT_TYPE_TSAR:
		वापस MLX5_CAP_QOS(dev, esw_element_type) &
		       ELEMENT_TYPE_CAP_MASK_TASR;
	हाल SCHEDULING_CONTEXT_ELEMENT_TYPE_VPORT:
		वापस MLX5_CAP_QOS(dev, esw_element_type) &
		       ELEMENT_TYPE_CAP_MASK_VPORT;
	हाल SCHEDULING_CONTEXT_ELEMENT_TYPE_VPORT_TC:
		वापस MLX5_CAP_QOS(dev, esw_element_type) &
		       ELEMENT_TYPE_CAP_MASK_VPORT_TC;
	हाल SCHEDULING_CONTEXT_ELEMENT_TYPE_PARA_VPORT_TC:
		वापस MLX5_CAP_QOS(dev, esw_element_type) &
		       ELEMENT_TYPE_CAP_MASK_PARA_VPORT_TC;
	पूर्ण
	वापस false;
पूर्ण

/* Vport QoS management */
अटल व्योम esw_create_tsar(काष्ठा mlx5_eचयन *esw)
अणु
	u32 tsar_ctx[MLX5_ST_SZ_DW(scheduling_context)] = अणु0पूर्ण;
	काष्ठा mlx5_core_dev *dev = esw->dev;
	__be32 *attr;
	पूर्णांक err;

	अगर (!MLX5_CAP_GEN(dev, qos) || !MLX5_CAP_QOS(dev, esw_scheduling))
		वापस;

	अगर (!element_type_supported(esw, SCHEDULING_CONTEXT_ELEMENT_TYPE_TSAR))
		वापस;

	अगर (esw->qos.enabled)
		वापस;

	MLX5_SET(scheduling_context, tsar_ctx, element_type,
		 SCHEDULING_CONTEXT_ELEMENT_TYPE_TSAR);

	attr = MLX5_ADDR_OF(scheduling_context, tsar_ctx, element_attributes);
	*attr = cpu_to_be32(TSAR_ELEMENT_TSAR_TYPE_DWRR << 16);

	err = mlx5_create_scheduling_element_cmd(dev,
						 SCHEDULING_HIERARCHY_E_SWITCH,
						 tsar_ctx,
						 &esw->qos.root_tsar_id);
	अगर (err) अणु
		esw_warn(esw->dev, "E-Switch create TSAR failed (%d)\n", err);
		वापस;
	पूर्ण

	esw->qos.enabled = true;
पूर्ण

अटल व्योम esw_destroy_tsar(काष्ठा mlx5_eचयन *esw)
अणु
	पूर्णांक err;

	अगर (!esw->qos.enabled)
		वापस;

	err = mlx5_destroy_scheduling_element_cmd(esw->dev,
						  SCHEDULING_HIERARCHY_E_SWITCH,
						  esw->qos.root_tsar_id);
	अगर (err)
		esw_warn(esw->dev, "E-Switch destroy TSAR failed (%d)\n", err);

	esw->qos.enabled = false;
पूर्ण

अटल पूर्णांक esw_vport_enable_qos(काष्ठा mlx5_eचयन *esw,
				काष्ठा mlx5_vport *vport,
				u32 initial_max_rate, u32 initial_bw_share)
अणु
	u32 sched_ctx[MLX5_ST_SZ_DW(scheduling_context)] = अणु0पूर्ण;
	काष्ठा mlx5_core_dev *dev = esw->dev;
	व्योम *vport_elem;
	पूर्णांक err = 0;

	अगर (!esw->qos.enabled)
		वापस 0;

	अगर (vport->qos.enabled)
		वापस -EEXIST;

	MLX5_SET(scheduling_context, sched_ctx, element_type,
		 SCHEDULING_CONTEXT_ELEMENT_TYPE_VPORT);
	vport_elem = MLX5_ADDR_OF(scheduling_context, sched_ctx,
				  element_attributes);
	MLX5_SET(vport_element, vport_elem, vport_number, vport->vport);
	MLX5_SET(scheduling_context, sched_ctx, parent_element_id,
		 esw->qos.root_tsar_id);
	MLX5_SET(scheduling_context, sched_ctx, max_average_bw,
		 initial_max_rate);
	MLX5_SET(scheduling_context, sched_ctx, bw_share, initial_bw_share);

	err = mlx5_create_scheduling_element_cmd(dev,
						 SCHEDULING_HIERARCHY_E_SWITCH,
						 sched_ctx,
						 &vport->qos.esw_tsar_ix);
	अगर (err) अणु
		esw_warn(esw->dev, "E-Switch create TSAR vport element failed (vport=%d,err=%d)\n",
			 vport->vport, err);
		वापस err;
	पूर्ण

	vport->qos.enabled = true;
	वापस 0;
पूर्ण

अटल व्योम esw_vport_disable_qos(काष्ठा mlx5_eचयन *esw,
				  काष्ठा mlx5_vport *vport)
अणु
	पूर्णांक err;

	अगर (!vport->qos.enabled)
		वापस;

	err = mlx5_destroy_scheduling_element_cmd(esw->dev,
						  SCHEDULING_HIERARCHY_E_SWITCH,
						  vport->qos.esw_tsar_ix);
	अगर (err)
		esw_warn(esw->dev, "E-Switch destroy TSAR vport element failed (vport=%d,err=%d)\n",
			 vport->vport, err);

	vport->qos.enabled = false;
पूर्ण

अटल पूर्णांक esw_vport_qos_config(काष्ठा mlx5_eचयन *esw,
				काष्ठा mlx5_vport *vport,
				u32 max_rate, u32 bw_share)
अणु
	u32 sched_ctx[MLX5_ST_SZ_DW(scheduling_context)] = अणु0पूर्ण;
	काष्ठा mlx5_core_dev *dev = esw->dev;
	व्योम *vport_elem;
	u32 biपंचांगask = 0;
	पूर्णांक err = 0;

	अगर (!MLX5_CAP_GEN(dev, qos) || !MLX5_CAP_QOS(dev, esw_scheduling))
		वापस -EOPNOTSUPP;

	अगर (!vport->qos.enabled)
		वापस -EIO;

	MLX5_SET(scheduling_context, sched_ctx, element_type,
		 SCHEDULING_CONTEXT_ELEMENT_TYPE_VPORT);
	vport_elem = MLX5_ADDR_OF(scheduling_context, sched_ctx,
				  element_attributes);
	MLX5_SET(vport_element, vport_elem, vport_number, vport->vport);
	MLX5_SET(scheduling_context, sched_ctx, parent_element_id,
		 esw->qos.root_tsar_id);
	MLX5_SET(scheduling_context, sched_ctx, max_average_bw,
		 max_rate);
	MLX5_SET(scheduling_context, sched_ctx, bw_share, bw_share);
	biपंचांगask |= MODIFY_SCHEDULING_ELEMENT_IN_MODIFY_BITMASK_MAX_AVERAGE_BW;
	biपंचांगask |= MODIFY_SCHEDULING_ELEMENT_IN_MODIFY_BITMASK_BW_SHARE;

	err = mlx5_modअगरy_scheduling_element_cmd(dev,
						 SCHEDULING_HIERARCHY_E_SWITCH,
						 sched_ctx,
						 vport->qos.esw_tsar_ix,
						 biपंचांगask);
	अगर (err) अणु
		esw_warn(esw->dev, "E-Switch modify TSAR vport element failed (vport=%d,err=%d)\n",
			 vport->vport, err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx5_esw_modअगरy_vport_rate(काष्ठा mlx5_eचयन *esw, u16 vport_num,
			       u32 rate_mbps)
अणु
	u32 ctx[MLX5_ST_SZ_DW(scheduling_context)] = अणुपूर्ण;
	काष्ठा mlx5_vport *vport;

	vport = mlx5_eचयन_get_vport(esw, vport_num);
	अगर (IS_ERR(vport))
		वापस PTR_ERR(vport);

	अगर (!vport->qos.enabled)
		वापस -EOPNOTSUPP;

	MLX5_SET(scheduling_context, ctx, max_average_bw, rate_mbps);

	वापस mlx5_modअगरy_scheduling_element_cmd(esw->dev,
						  SCHEDULING_HIERARCHY_E_SWITCH,
						  ctx,
						  vport->qos.esw_tsar_ix,
						  MODIFY_SCHEDULING_ELEMENT_IN_MODIFY_BITMASK_MAX_AVERAGE_BW);
पूर्ण

अटल व्योम node_guid_gen_from_mac(u64 *node_guid, स्थिर u8 *mac)
अणु
	((u8 *)node_guid)[7] = mac[0];
	((u8 *)node_guid)[6] = mac[1];
	((u8 *)node_guid)[5] = mac[2];
	((u8 *)node_guid)[4] = 0xff;
	((u8 *)node_guid)[3] = 0xfe;
	((u8 *)node_guid)[2] = mac[3];
	((u8 *)node_guid)[1] = mac[4];
	((u8 *)node_guid)[0] = mac[5];
पूर्ण

अटल पूर्णांक esw_vport_setup_acl(काष्ठा mlx5_eचयन *esw,
			       काष्ठा mlx5_vport *vport)
अणु
	अगर (esw->mode == MLX5_ESWITCH_LEGACY)
		वापस esw_legacy_vport_acl_setup(esw, vport);
	अन्यथा
		वापस esw_vport_create_offloads_acl_tables(esw, vport);
पूर्ण

अटल व्योम esw_vport_cleanup_acl(काष्ठा mlx5_eचयन *esw,
				  काष्ठा mlx5_vport *vport)
अणु
	अगर (esw->mode == MLX5_ESWITCH_LEGACY)
		esw_legacy_vport_acl_cleanup(esw, vport);
	अन्यथा
		esw_vport_destroy_offloads_acl_tables(esw, vport);
पूर्ण

अटल पूर्णांक esw_vport_setup(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport)
अणु
	u16 vport_num = vport->vport;
	पूर्णांक flags;
	पूर्णांक err;

	err = esw_vport_setup_acl(esw, vport);
	अगर (err)
		वापस err;

	/* Attach vport to the eचयन rate limiter */
	esw_vport_enable_qos(esw, vport, vport->qos.max_rate, vport->qos.bw_share);

	अगर (mlx5_esw_is_manager_vport(esw, vport_num))
		वापस 0;

	mlx5_modअगरy_vport_admin_state(esw->dev,
				      MLX5_VPORT_STATE_OP_MOD_ESW_VPORT,
				      vport_num, 1,
				      vport->info.link_state);

	/* Host PF has its own mac/guid. */
	अगर (vport_num) अणु
		mlx5_modअगरy_nic_vport_mac_address(esw->dev, vport_num,
						  vport->info.mac);
		mlx5_modअगरy_nic_vport_node_guid(esw->dev, vport_num,
						vport->info.node_guid);
	पूर्ण

	flags = (vport->info.vlan || vport->info.qos) ?
		SET_VLAN_STRIP | SET_VLAN_INSERT : 0;
	modअगरy_esw_vport_cvlan(esw->dev, vport_num, vport->info.vlan,
			       vport->info.qos, flags);

	वापस 0;
पूर्ण

/* Don't cleanup vport->info, it's needed to restore vport configuration */
अटल व्योम esw_vport_cleanup(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport)
अणु
	u16 vport_num = vport->vport;

	अगर (!mlx5_esw_is_manager_vport(esw, vport_num))
		mlx5_modअगरy_vport_admin_state(esw->dev,
					      MLX5_VPORT_STATE_OP_MOD_ESW_VPORT,
					      vport_num, 1,
					      MLX5_VPORT_ADMIN_STATE_DOWN);

	esw_vport_disable_qos(esw, vport);
	esw_vport_cleanup_acl(esw, vport);
पूर्ण

पूर्णांक mlx5_esw_vport_enable(काष्ठा mlx5_eचयन *esw, u16 vport_num,
			  क्रमागत mlx5_eचयन_vport_event enabled_events)
अणु
	काष्ठा mlx5_vport *vport;
	पूर्णांक ret;

	vport = mlx5_eचयन_get_vport(esw, vport_num);
	अगर (IS_ERR(vport))
		वापस PTR_ERR(vport);

	mutex_lock(&esw->state_lock);
	WARN_ON(vport->enabled);

	esw_debug(esw->dev, "Enabling VPORT(%d)\n", vport_num);

	ret = esw_vport_setup(esw, vport);
	अगर (ret)
		जाओ करोne;

	/* Sync with current vport context */
	vport->enabled_events = enabled_events;
	vport->enabled = true;

	/* Esw manager is trusted by शेष. Host PF (vport 0) is trusted as well
	 * in smartNIC as it's a vport group manager.
	 */
	अगर (mlx5_esw_is_manager_vport(esw, vport_num) ||
	    (!vport_num && mlx5_core_is_ecpf(esw->dev)))
		vport->info.trusted = true;

	अगर (!mlx5_esw_is_manager_vport(esw, vport->vport) &&
	    MLX5_CAP_GEN(esw->dev, vhca_resource_manager)) अणु
		ret = mlx5_esw_vport_vhca_id_set(esw, vport_num);
		अगर (ret)
			जाओ err_vhca_mapping;
	पूर्ण

	/* External controller host PF has factory programmed MAC.
	 * Read it from the device.
	 */
	अगर (mlx5_core_is_ecpf(esw->dev) && vport_num == MLX5_VPORT_PF)
		mlx5_query_nic_vport_mac_address(esw->dev, vport_num, true, vport->info.mac);

	esw_vport_change_handle_locked(vport);

	esw->enabled_vports++;
	esw_debug(esw->dev, "Enabled VPORT(%d)\n", vport_num);
करोne:
	mutex_unlock(&esw->state_lock);
	वापस ret;

err_vhca_mapping:
	esw_vport_cleanup(esw, vport);
	mutex_unlock(&esw->state_lock);
	वापस ret;
पूर्ण

व्योम mlx5_esw_vport_disable(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	काष्ठा mlx5_vport *vport;

	vport = mlx5_eचयन_get_vport(esw, vport_num);
	अगर (IS_ERR(vport))
		वापस;

	mutex_lock(&esw->state_lock);
	अगर (!vport->enabled)
		जाओ करोne;

	esw_debug(esw->dev, "Disabling vport(%d)\n", vport_num);
	/* Mark this vport as disabled to discard new events */
	vport->enabled = false;

	/* Disable events from this vport */
	arm_vport_context_events_cmd(esw->dev, vport->vport, 0);

	अगर (!mlx5_esw_is_manager_vport(esw, vport->vport) &&
	    MLX5_CAP_GEN(esw->dev, vhca_resource_manager))
		mlx5_esw_vport_vhca_id_clear(esw, vport_num);

	/* We करोn't assume VFs will cleanup after themselves.
	 * Calling vport change handler जबतक vport is disabled will cleanup
	 * the vport resources.
	 */
	esw_vport_change_handle_locked(vport);
	vport->enabled_events = 0;
	esw_vport_cleanup(esw, vport);
	esw->enabled_vports--;

करोne:
	mutex_unlock(&esw->state_lock);
पूर्ण

अटल पूर्णांक eचयन_vport_event(काष्ठा notअगरier_block *nb,
			       अचिन्हित दीर्घ type, व्योम *data)
अणु
	काष्ठा mlx5_eचयन *esw = mlx5_nb_cof(nb, काष्ठा mlx5_eचयन, nb);
	काष्ठा mlx5_eqe *eqe = data;
	काष्ठा mlx5_vport *vport;
	u16 vport_num;

	vport_num = be16_to_cpu(eqe->data.vport_change.vport_num);
	vport = mlx5_eचयन_get_vport(esw, vport_num);
	अगर (!IS_ERR(vport))
		queue_work(esw->work_queue, &vport->vport_change_handler);
	वापस NOTIFY_OK;
पूर्ण

/**
 * mlx5_esw_query_functions - Returns raw output about functions state
 * @dev:	Poपूर्णांकer to device to query
 *
 * mlx5_esw_query_functions() allocates and वापसs functions changed
 * raw output memory poपूर्णांकer from device on success. Otherwise वापसs ERR_PTR.
 * Caller must मुक्त the memory using kvमुक्त() when valid poपूर्णांकer is वापसed.
 */
स्थिर u32 *mlx5_esw_query_functions(काष्ठा mlx5_core_dev *dev)
अणु
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_esw_functions_out);
	u32 in[MLX5_ST_SZ_DW(query_esw_functions_in)] = अणुपूर्ण;
	u32 *out;
	पूर्णांक err;

	out = kvzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस ERR_PTR(-ENOMEM);

	MLX5_SET(query_esw_functions_in, in, opcode,
		 MLX5_CMD_OP_QUERY_ESW_FUNCTIONS);

	err = mlx5_cmd_exec(dev, in, माप(in), out, outlen);
	अगर (!err)
		वापस out;

	kvमुक्त(out);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlx5_eचयन_event_handlers_रेजिस्टर(काष्ठा mlx5_eचयन *esw)
अणु
	MLX5_NB_INIT(&esw->nb, eचयन_vport_event, NIC_VPORT_CHANGE);
	mlx5_eq_notअगरier_रेजिस्टर(esw->dev, &esw->nb);

	अगर (esw->mode == MLX5_ESWITCH_OFFLOADS && mlx5_eचयन_is_funcs_handler(esw->dev)) अणु
		MLX5_NB_INIT(&esw->esw_funcs.nb, mlx5_esw_funcs_changed_handler,
			     ESW_FUNCTIONS_CHANGED);
		mlx5_eq_notअगरier_रेजिस्टर(esw->dev, &esw->esw_funcs.nb);
	पूर्ण
पूर्ण

अटल व्योम mlx5_eचयन_event_handlers_unरेजिस्टर(काष्ठा mlx5_eचयन *esw)
अणु
	अगर (esw->mode == MLX5_ESWITCH_OFFLOADS && mlx5_eचयन_is_funcs_handler(esw->dev))
		mlx5_eq_notअगरier_unरेजिस्टर(esw->dev, &esw->esw_funcs.nb);

	mlx5_eq_notअगरier_unरेजिस्टर(esw->dev, &esw->nb);

	flush_workqueue(esw->work_queue);
पूर्ण

अटल व्योम mlx5_eचयन_clear_vf_vports_info(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;

	mlx5_esw_क्रम_each_vf_vport(esw, i, vport, esw->esw_funcs.num_vfs) अणु
		स_रखो(&vport->qos, 0, माप(vport->qos));
		स_रखो(&vport->info, 0, माप(vport->info));
		vport->info.link_state = MLX5_VPORT_ADMIN_STATE_AUTO;
	पूर्ण
पूर्ण

/* Public E-Switch API */
पूर्णांक mlx5_eचयन_load_vport(काष्ठा mlx5_eचयन *esw, u16 vport_num,
			    क्रमागत mlx5_eचयन_vport_event enabled_events)
अणु
	पूर्णांक err;

	err = mlx5_esw_vport_enable(esw, vport_num, enabled_events);
	अगर (err)
		वापस err;

	err = esw_offloads_load_rep(esw, vport_num);
	अगर (err)
		जाओ err_rep;

	वापस err;

err_rep:
	mlx5_esw_vport_disable(esw, vport_num);
	वापस err;
पूर्ण

व्योम mlx5_eचयन_unload_vport(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	esw_offloads_unload_rep(esw, vport_num);
	mlx5_esw_vport_disable(esw, vport_num);
पूर्ण

व्योम mlx5_eचयन_unload_vf_vports(काष्ठा mlx5_eचयन *esw, u16 num_vfs)
अणु
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;

	mlx5_esw_क्रम_each_vf_vport(esw, i, vport, num_vfs) अणु
		अगर (!vport->enabled)
			जारी;
		mlx5_eचयन_unload_vport(esw, vport->vport);
	पूर्ण
पूर्ण

पूर्णांक mlx5_eचयन_load_vf_vports(काष्ठा mlx5_eचयन *esw, u16 num_vfs,
				क्रमागत mlx5_eचयन_vport_event enabled_events)
अणु
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;
	पूर्णांक err;

	mlx5_esw_क्रम_each_vf_vport(esw, i, vport, num_vfs) अणु
		err = mlx5_eचयन_load_vport(esw, vport->vport, enabled_events);
		अगर (err)
			जाओ vf_err;
	पूर्ण

	वापस 0;

vf_err:
	mlx5_eचयन_unload_vf_vports(esw, num_vfs);
	वापस err;
पूर्ण

अटल पूर्णांक host_pf_enable_hca(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (!mlx5_core_is_ecpf(dev))
		वापस 0;

	/* Once vport and representor are पढ़ोy, take out the बाह्यal host PF
	 * out of initializing state. Enabling HCA clears the iser->initializing
	 * bit and host PF driver loading can progress.
	 */
	वापस mlx5_cmd_host_pf_enable_hca(dev);
पूर्ण

अटल व्योम host_pf_disable_hca(काष्ठा mlx5_core_dev *dev)
अणु
	अगर (!mlx5_core_is_ecpf(dev))
		वापस;

	mlx5_cmd_host_pf_disable_hca(dev);
पूर्ण

/* mlx5_eचयन_enable_pf_vf_vports() enables vports of PF, ECPF and VFs
 * whichever are present on the eचयन.
 */
पूर्णांक
mlx5_eचयन_enable_pf_vf_vports(काष्ठा mlx5_eचयन *esw,
				 क्रमागत mlx5_eचयन_vport_event enabled_events)
अणु
	पूर्णांक ret;

	/* Enable PF vport */
	ret = mlx5_eचयन_load_vport(esw, MLX5_VPORT_PF, enabled_events);
	अगर (ret)
		वापस ret;

	/* Enable बाह्यal host PF HCA */
	ret = host_pf_enable_hca(esw->dev);
	अगर (ret)
		जाओ pf_hca_err;

	/* Enable ECPF vport */
	अगर (mlx5_ecpf_vport_exists(esw->dev)) अणु
		ret = mlx5_eचयन_load_vport(esw, MLX5_VPORT_ECPF, enabled_events);
		अगर (ret)
			जाओ ecpf_err;
	पूर्ण

	/* Enable VF vports */
	ret = mlx5_eचयन_load_vf_vports(esw, esw->esw_funcs.num_vfs,
					  enabled_events);
	अगर (ret)
		जाओ vf_err;
	वापस 0;

vf_err:
	अगर (mlx5_ecpf_vport_exists(esw->dev))
		mlx5_eचयन_unload_vport(esw, MLX5_VPORT_ECPF);
ecpf_err:
	host_pf_disable_hca(esw->dev);
pf_hca_err:
	mlx5_eचयन_unload_vport(esw, MLX5_VPORT_PF);
	वापस ret;
पूर्ण

/* mlx5_eचयन_disable_pf_vf_vports() disables vports of PF, ECPF and VFs
 * whichever are previously enabled on the eचयन.
 */
व्योम mlx5_eचयन_disable_pf_vf_vports(काष्ठा mlx5_eचयन *esw)
अणु
	mlx5_eचयन_unload_vf_vports(esw, esw->esw_funcs.num_vfs);

	अगर (mlx5_ecpf_vport_exists(esw->dev))
		mlx5_eचयन_unload_vport(esw, MLX5_VPORT_ECPF);

	host_pf_disable_hca(esw->dev);
	mlx5_eचयन_unload_vport(esw, MLX5_VPORT_PF);
पूर्ण

अटल व्योम mlx5_eचयन_get_devlink_param(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा devlink *devlink = priv_to_devlink(esw->dev);
	जोड़ devlink_param_value val;
	पूर्णांक err;

	err = devlink_param_driverinit_value_get(devlink,
						 MLX5_DEVLINK_PARAM_ID_ESW_LARGE_GROUP_NUM,
						 &val);
	अगर (!err) अणु
		esw->params.large_group_num = val.vu32;
	पूर्ण अन्यथा अणु
		esw_warn(esw->dev,
			 "Devlink can't get param fdb_large_groups, uses default (%d).\n",
			 ESW_OFFLOADS_DEFAULT_NUM_GROUPS);
		esw->params.large_group_num = ESW_OFFLOADS_DEFAULT_NUM_GROUPS;
	पूर्ण
पूर्ण

अटल व्योम
mlx5_eचयन_update_num_of_vfs(काष्ठा mlx5_eचयन *esw, पूर्णांक num_vfs)
अणु
	स्थिर u32 *out;

	WARN_ON_ONCE(esw->mode != MLX5_ESWITCH_NONE);

	अगर (num_vfs < 0)
		वापस;

	अगर (!mlx5_core_is_ecpf_esw_manager(esw->dev)) अणु
		esw->esw_funcs.num_vfs = num_vfs;
		वापस;
	पूर्ण

	out = mlx5_esw_query_functions(esw->dev);
	अगर (IS_ERR(out))
		वापस;

	esw->esw_funcs.num_vfs = MLX5_GET(query_esw_functions_out, out,
					  host_params_context.host_num_of_vfs);
	kvमुक्त(out);
पूर्ण

अटल व्योम mlx5_esw_mode_change_notअगरy(काष्ठा mlx5_eचयन *esw, u16 mode)
अणु
	काष्ठा mlx5_esw_event_info info = अणुपूर्ण;

	info.new_mode = mode;

	blocking_notअगरier_call_chain(&esw->n_head, 0, &info);
पूर्ण

अटल पूर्णांक mlx5_esw_acls_ns_init(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_core_dev *dev = esw->dev;
	पूर्णांक total_vports;
	पूर्णांक err;

	total_vports = mlx5_eचयन_get_total_vports(dev);

	अगर (MLX5_CAP_ESW_EGRESS_ACL(dev, ft_support)) अणु
		err = mlx5_fs_egress_acls_init(dev, total_vports);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		esw_warn(dev, "engress ACL is not supported by FW\n");
	पूर्ण

	अगर (MLX5_CAP_ESW_INGRESS_ACL(dev, ft_support)) अणु
		err = mlx5_fs_ingress_acls_init(dev, total_vports);
		अगर (err)
			जाओ err;
	पूर्ण अन्यथा अणु
		esw_warn(dev, "ingress ACL is not supported by FW\n");
	पूर्ण
	वापस 0;

err:
	अगर (MLX5_CAP_ESW_EGRESS_ACL(dev, ft_support))
		mlx5_fs_egress_acls_cleanup(dev);
	वापस err;
पूर्ण

अटल व्योम mlx5_esw_acls_ns_cleanup(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_core_dev *dev = esw->dev;

	अगर (MLX5_CAP_ESW_INGRESS_ACL(dev, ft_support))
		mlx5_fs_ingress_acls_cleanup(dev);
	अगर (MLX5_CAP_ESW_EGRESS_ACL(dev, ft_support))
		mlx5_fs_egress_acls_cleanup(dev);
पूर्ण

/**
 * mlx5_eचयन_enable_locked - Enable eचयन
 * @esw:	Poपूर्णांकer to eचयन
 * @mode:	Eचयन mode to enable
 * @num_vfs:	Enable eचयन क्रम given number of VFs. This is optional.
 *		Valid value are 0, > 0 and MLX5_ESWITCH_IGNORE_NUM_VFS.
 *		Caller should pass num_vfs > 0 when enabling eचयन क्रम
 *		vf vports. Caller should pass num_vfs = 0, when eचयन
 *		is enabled without sriov VFs or when caller
 *		is unaware of the sriov state of the host PF on ECPF based
 *		eचयन. Caller should pass < 0 when num_vfs should be
 *		completely ignored. This is typically the हाल when eचयन
 *		is enabled without sriov regardless of PF/ECPF प्रणाली.
 * mlx5_eचयन_enable_locked() Enables eचयन in either legacy or offloads
 * mode. If num_vfs >=0 is provided, it setup VF related eचयन vports.
 * It वापसs 0 on success or error code on failure.
 */
पूर्णांक mlx5_eचयन_enable_locked(काष्ठा mlx5_eचयन *esw, पूर्णांक mode, पूर्णांक num_vfs)
अणु
	पूर्णांक err;

	lockdep_निश्चित_held(&esw->mode_lock);

	अगर (!MLX5_CAP_ESW_FLOWTABLE_FDB(esw->dev, ft_support)) अणु
		esw_warn(esw->dev, "FDB is not supported, aborting ...\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	mlx5_eचयन_get_devlink_param(esw);

	err = mlx5_esw_acls_ns_init(esw);
	अगर (err)
		वापस err;

	mlx5_eचयन_update_num_of_vfs(esw, num_vfs);

	esw_create_tsar(esw);

	esw->mode = mode;

	mlx5_lag_update(esw->dev);

	अगर (mode == MLX5_ESWITCH_LEGACY) अणु
		err = esw_legacy_enable(esw);
	पूर्ण अन्यथा अणु
		mlx5_rescan_drivers(esw->dev);
		err = esw_offloads_enable(esw);
	पूर्ण

	अगर (err)
		जाओ पात;

	mlx5_eचयन_event_handlers_रेजिस्टर(esw);

	esw_info(esw->dev, "Enable: mode(%s), nvfs(%d), active vports(%d)\n",
		 mode == MLX5_ESWITCH_LEGACY ? "LEGACY" : "OFFLOADS",
		 esw->esw_funcs.num_vfs, esw->enabled_vports);

	mlx5_esw_mode_change_notअगरy(esw, mode);

	वापस 0;

पात:
	esw->mode = MLX5_ESWITCH_NONE;

	अगर (mode == MLX5_ESWITCH_OFFLOADS)
		mlx5_rescan_drivers(esw->dev);

	esw_destroy_tsar(esw);
	mlx5_esw_acls_ns_cleanup(esw);
	वापस err;
पूर्ण

/**
 * mlx5_eचयन_enable - Enable eचयन
 * @esw:	Poपूर्णांकer to eचयन
 * @num_vfs:	Enable eचयन swich क्रम given number of VFs.
 *		Caller must pass num_vfs > 0 when enabling eचयन क्रम
 *		vf vports.
 * mlx5_eचयन_enable() वापसs 0 on success or error code on failure.
 */
पूर्णांक mlx5_eचयन_enable(काष्ठा mlx5_eचयन *esw, पूर्णांक num_vfs)
अणु
	पूर्णांक ret;

	अगर (!mlx5_esw_allowed(esw))
		वापस 0;

	करोwn_ग_लिखो(&esw->mode_lock);
	अगर (esw->mode == MLX5_ESWITCH_NONE) अणु
		ret = mlx5_eचयन_enable_locked(esw, MLX5_ESWITCH_LEGACY, num_vfs);
	पूर्ण अन्यथा अणु
		क्रमागत mlx5_eचयन_vport_event vport_events;

		vport_events = (esw->mode == MLX5_ESWITCH_LEGACY) ?
					MLX5_LEGACY_SRIOV_VPORT_EVENTS : MLX5_VPORT_UC_ADDR_CHANGE;
		ret = mlx5_eचयन_load_vf_vports(esw, num_vfs, vport_events);
		अगर (!ret)
			esw->esw_funcs.num_vfs = num_vfs;
	पूर्ण
	up_ग_लिखो(&esw->mode_lock);
	वापस ret;
पूर्ण

व्योम mlx5_eचयन_disable_locked(काष्ठा mlx5_eचयन *esw, bool clear_vf)
अणु
	पूर्णांक old_mode;

	lockdep_निश्चित_held_ग_लिखो(&esw->mode_lock);

	अगर (esw->mode == MLX5_ESWITCH_NONE)
		वापस;

	esw_info(esw->dev, "Disable: mode(%s), nvfs(%d), active vports(%d)\n",
		 esw->mode == MLX5_ESWITCH_LEGACY ? "LEGACY" : "OFFLOADS",
		 esw->esw_funcs.num_vfs, esw->enabled_vports);

	/* Notअगरy eचयन users that it is निकासing from current mode.
	 * So that it can करो necessary cleanup beक्रमe the eचयन is disabled.
	 */
	mlx5_esw_mode_change_notअगरy(esw, MLX5_ESWITCH_NONE);

	mlx5_eचयन_event_handlers_unरेजिस्टर(esw);

	अगर (esw->mode == MLX5_ESWITCH_LEGACY)
		esw_legacy_disable(esw);
	अन्यथा अगर (esw->mode == MLX5_ESWITCH_OFFLOADS)
		esw_offloads_disable(esw);

	old_mode = esw->mode;
	esw->mode = MLX5_ESWITCH_NONE;

	mlx5_lag_update(esw->dev);

	अगर (old_mode == MLX5_ESWITCH_OFFLOADS)
		mlx5_rescan_drivers(esw->dev);

	esw_destroy_tsar(esw);
	mlx5_esw_acls_ns_cleanup(esw);

	अगर (clear_vf)
		mlx5_eचयन_clear_vf_vports_info(esw);
पूर्ण

व्योम mlx5_eचयन_disable(काष्ठा mlx5_eचयन *esw, bool clear_vf)
अणु
	अगर (!mlx5_esw_allowed(esw))
		वापस;

	करोwn_ग_लिखो(&esw->mode_lock);
	mlx5_eचयन_disable_locked(esw, clear_vf);
	esw->esw_funcs.num_vfs = 0;
	up_ग_लिखो(&esw->mode_lock);
पूर्ण

अटल पूर्णांक mlx5_query_hca_cap_host_pf(काष्ठा mlx5_core_dev *dev, व्योम *out)
अणु
	u16 opmod = (MLX5_CAP_GENERAL << 1) | (HCA_CAP_OPMOD_GET_MAX & 0x01);
	u8 in[MLX5_ST_SZ_BYTES(query_hca_cap_in)] = अणुपूर्ण;

	MLX5_SET(query_hca_cap_in, in, opcode, MLX5_CMD_OP_QUERY_HCA_CAP);
	MLX5_SET(query_hca_cap_in, in, op_mod, opmod);
	MLX5_SET(query_hca_cap_in, in, function_id, MLX5_VPORT_PF);
	MLX5_SET(query_hca_cap_in, in, other_function, true);
	वापस mlx5_cmd_exec_inout(dev, query_hca_cap, in, out);
पूर्ण

पूर्णांक mlx5_esw_sf_max_hpf_functions(काष्ठा mlx5_core_dev *dev, u16 *max_sfs, u16 *sf_base_id)

अणु
	पूर्णांक query_out_sz = MLX5_ST_SZ_BYTES(query_hca_cap_out);
	व्योम *query_ctx;
	व्योम *hca_caps;
	पूर्णांक err;

	अगर (!mlx5_core_is_ecpf(dev)) अणु
		*max_sfs = 0;
		वापस 0;
	पूर्ण

	query_ctx = kzalloc(query_out_sz, GFP_KERNEL);
	अगर (!query_ctx)
		वापस -ENOMEM;

	err = mlx5_query_hca_cap_host_pf(dev, query_ctx);
	अगर (err)
		जाओ out_मुक्त;

	hca_caps = MLX5_ADDR_OF(query_hca_cap_out, query_ctx, capability);
	*max_sfs = MLX5_GET(cmd_hca_cap, hca_caps, max_num_sf);
	*sf_base_id = MLX5_GET(cmd_hca_cap, hca_caps, sf_base_id);

out_मुक्त:
	kमुक्त(query_ctx);
	वापस err;
पूर्ण

अटल पूर्णांक mlx5_esw_vport_alloc(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_core_dev *dev,
				पूर्णांक index, u16 vport_num)
अणु
	काष्ठा mlx5_vport *vport;
	पूर्णांक err;

	vport = kzalloc(माप(*vport), GFP_KERNEL);
	अगर (!vport)
		वापस -ENOMEM;

	vport->dev = esw->dev;
	vport->vport = vport_num;
	vport->index = index;
	vport->info.link_state = MLX5_VPORT_ADMIN_STATE_AUTO;
	INIT_WORK(&vport->vport_change_handler, esw_vport_change_handler);
	err = xa_insert(&esw->vports, vport_num, vport, GFP_KERNEL);
	अगर (err)
		जाओ insert_err;

	esw->total_vports++;
	वापस 0;

insert_err:
	kमुक्त(vport);
	वापस err;
पूर्ण

अटल व्योम mlx5_esw_vport_मुक्त(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport)
अणु
	xa_erase(&esw->vports, vport->vport);
	kमुक्त(vport);
पूर्ण

अटल व्योम mlx5_esw_vports_cleanup(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;

	mlx5_esw_क्रम_each_vport(esw, i, vport)
		mlx5_esw_vport_मुक्त(esw, vport);
	xa_destroy(&esw->vports);
पूर्ण

अटल पूर्णांक mlx5_esw_vports_init(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_core_dev *dev = esw->dev;
	u16 max_host_pf_sfs;
	u16 base_sf_num;
	पूर्णांक idx = 0;
	पूर्णांक err;
	पूर्णांक i;

	xa_init(&esw->vports);

	err = mlx5_esw_vport_alloc(esw, dev, idx, MLX5_VPORT_PF);
	अगर (err)
		जाओ err;
	अगर (esw->first_host_vport == MLX5_VPORT_PF)
		xa_set_mark(&esw->vports, idx, MLX5_ESW_VPT_HOST_FN);
	idx++;

	क्रम (i = 0; i < mlx5_core_max_vfs(dev); i++) अणु
		err = mlx5_esw_vport_alloc(esw, dev, idx, idx);
		अगर (err)
			जाओ err;
		xa_set_mark(&esw->vports, idx, MLX5_ESW_VPT_VF);
		xa_set_mark(&esw->vports, idx, MLX5_ESW_VPT_HOST_FN);
		idx++;
	पूर्ण
	base_sf_num = mlx5_sf_start_function_id(dev);
	क्रम (i = 0; i < mlx5_sf_max_functions(dev); i++) अणु
		err = mlx5_esw_vport_alloc(esw, dev, idx, base_sf_num + i);
		अगर (err)
			जाओ err;
		xa_set_mark(&esw->vports, base_sf_num + i, MLX5_ESW_VPT_SF);
		idx++;
	पूर्ण

	err = mlx5_esw_sf_max_hpf_functions(dev, &max_host_pf_sfs, &base_sf_num);
	अगर (err)
		जाओ err;
	क्रम (i = 0; i < max_host_pf_sfs; i++) अणु
		err = mlx5_esw_vport_alloc(esw, dev, idx, base_sf_num + i);
		अगर (err)
			जाओ err;
		xa_set_mark(&esw->vports, base_sf_num + i, MLX5_ESW_VPT_SF);
		idx++;
	पूर्ण

	अगर (mlx5_ecpf_vport_exists(dev)) अणु
		err = mlx5_esw_vport_alloc(esw, dev, idx, MLX5_VPORT_ECPF);
		अगर (err)
			जाओ err;
		idx++;
	पूर्ण
	err = mlx5_esw_vport_alloc(esw, dev, idx, MLX5_VPORT_UPLINK);
	अगर (err)
		जाओ err;
	वापस 0;

err:
	mlx5_esw_vports_cleanup(esw);
	वापस err;
पूर्ण

पूर्णांक mlx5_eचयन_init(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_eचयन *esw;
	पूर्णांक err;

	अगर (!MLX5_VPORT_MANAGER(dev))
		वापस 0;

	esw = kzalloc(माप(*esw), GFP_KERNEL);
	अगर (!esw)
		वापस -ENOMEM;

	esw->dev = dev;
	esw->manager_vport = mlx5_eचयन_manager_vport(dev);
	esw->first_host_vport = mlx5_eचयन_first_host_vport_num(dev);

	esw->work_queue = create_singlethपढ़ो_workqueue("mlx5_esw_wq");
	अगर (!esw->work_queue) अणु
		err = -ENOMEM;
		जाओ पात;
	पूर्ण

	err = mlx5_esw_vports_init(esw);
	अगर (err)
		जाओ पात;

	err = esw_offloads_init_reps(esw);
	अगर (err)
		जाओ reps_err;

	mutex_init(&esw->offloads.encap_tbl_lock);
	hash_init(esw->offloads.encap_tbl);
	mutex_init(&esw->offloads.decap_tbl_lock);
	hash_init(esw->offloads.decap_tbl);
	mlx5e_mod_hdr_tbl_init(&esw->offloads.mod_hdr);
	atomic64_set(&esw->offloads.num_flows, 0);
	ida_init(&esw->offloads.vport_metadata_ida);
	xa_init_flags(&esw->offloads.vhca_map, XA_FLAGS_ALLOC);
	mutex_init(&esw->state_lock);
	init_rwsem(&esw->mode_lock);

	esw->enabled_vports = 0;
	esw->mode = MLX5_ESWITCH_NONE;
	esw->offloads.अंतरभूत_mode = MLX5_INLINE_MODE_NONE;

	dev->priv.eचयन = esw;
	BLOCKING_INIT_NOTIFIER_HEAD(&esw->n_head);

	esw_info(dev,
		 "Total vports %d, per vport: max uc(%d) max mc(%d)\n",
		 esw->total_vports,
		 MLX5_MAX_UC_PER_VPORT(dev),
		 MLX5_MAX_MC_PER_VPORT(dev));
	वापस 0;

reps_err:
	mlx5_esw_vports_cleanup(esw);
पात:
	अगर (esw->work_queue)
		destroy_workqueue(esw->work_queue);
	kमुक्त(esw);
	वापस err;
पूर्ण

व्योम mlx5_eचयन_cleanup(काष्ठा mlx5_eचयन *esw)
अणु
	अगर (!esw || !MLX5_VPORT_MANAGER(esw->dev))
		वापस;

	esw_info(esw->dev, "cleanup\n");

	esw->dev->priv.eचयन = शून्य;
	destroy_workqueue(esw->work_queue);
	mutex_destroy(&esw->state_lock);
	WARN_ON(!xa_empty(&esw->offloads.vhca_map));
	xa_destroy(&esw->offloads.vhca_map);
	ida_destroy(&esw->offloads.vport_metadata_ida);
	mlx5e_mod_hdr_tbl_destroy(&esw->offloads.mod_hdr);
	mutex_destroy(&esw->offloads.encap_tbl_lock);
	mutex_destroy(&esw->offloads.decap_tbl_lock);
	esw_offloads_cleanup_reps(esw);
	mlx5_esw_vports_cleanup(esw);
	kमुक्त(esw);
पूर्ण

/* Vport Administration */
अटल पूर्णांक
mlx5_esw_set_vport_mac_locked(काष्ठा mlx5_eचयन *esw,
			      काष्ठा mlx5_vport *evport, स्थिर u8 *mac)
अणु
	u16 vport_num = evport->vport;
	u64 node_guid;
	पूर्णांक err = 0;

	अगर (is_multicast_ether_addr(mac))
		वापस -EINVAL;

	अगर (evport->info.spoofchk && !is_valid_ether_addr(mac))
		mlx5_core_warn(esw->dev,
			       "Set invalid MAC while spoofchk is on, vport(%d)\n",
			       vport_num);

	err = mlx5_modअगरy_nic_vport_mac_address(esw->dev, vport_num, mac);
	अगर (err) अणु
		mlx5_core_warn(esw->dev,
			       "Failed to mlx5_modify_nic_vport_mac vport(%d) err=(%d)\n",
			       vport_num, err);
		वापस err;
	पूर्ण

	node_guid_gen_from_mac(&node_guid, mac);
	err = mlx5_modअगरy_nic_vport_node_guid(esw->dev, vport_num, node_guid);
	अगर (err)
		mlx5_core_warn(esw->dev,
			       "Failed to set vport %d node guid, err = %d. RDMA_CM will not function properly for this VF.\n",
			       vport_num, err);

	ether_addr_copy(evport->info.mac, mac);
	evport->info.node_guid = node_guid;
	अगर (evport->enabled && esw->mode == MLX5_ESWITCH_LEGACY)
		err = esw_acl_ingress_lgcy_setup(esw, evport);

	वापस err;
पूर्ण

पूर्णांक mlx5_eचयन_set_vport_mac(काष्ठा mlx5_eचयन *esw,
			       u16 vport, स्थिर u8 *mac)
अणु
	काष्ठा mlx5_vport *evport = mlx5_eचयन_get_vport(esw, vport);
	पूर्णांक err = 0;

	अगर (IS_ERR(evport))
		वापस PTR_ERR(evport);

	mutex_lock(&esw->state_lock);
	err = mlx5_esw_set_vport_mac_locked(esw, evport, mac);
	mutex_unlock(&esw->state_lock);
	वापस err;
पूर्ण

अटल bool mlx5_esw_check_port_type(काष्ठा mlx5_eचयन *esw, u16 vport_num, xa_mark_t mark)
अणु
	काष्ठा mlx5_vport *vport;

	vport = mlx5_eचयन_get_vport(esw, vport_num);
	अगर (IS_ERR(vport))
		वापस false;

	वापस xa_get_mark(&esw->vports, vport_num, mark);
पूर्ण

bool mlx5_eचयन_is_vf_vport(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	वापस mlx5_esw_check_port_type(esw, vport_num, MLX5_ESW_VPT_VF);
पूर्ण

bool mlx5_esw_is_sf_vport(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	वापस mlx5_esw_check_port_type(esw, vport_num, MLX5_ESW_VPT_SF);
पूर्ण

अटल bool
is_port_function_supported(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	वापस vport_num == MLX5_VPORT_PF ||
	       mlx5_eचयन_is_vf_vport(esw, vport_num) ||
	       mlx5_esw_is_sf_vport(esw, vport_num);
पूर्ण

पूर्णांक mlx5_devlink_port_function_hw_addr_get(काष्ठा devlink *devlink,
					   काष्ठा devlink_port *port,
					   u8 *hw_addr, पूर्णांक *hw_addr_len,
					   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_eचयन *esw;
	काष्ठा mlx5_vport *vport;
	पूर्णांक err = -EOPNOTSUPP;
	u16 vport_num;

	esw = mlx5_devlink_eचयन_get(devlink);
	अगर (IS_ERR(esw))
		वापस PTR_ERR(esw);

	vport_num = mlx5_esw_devlink_port_index_to_vport_num(port->index);
	अगर (!is_port_function_supported(esw, vport_num))
		वापस -EOPNOTSUPP;

	vport = mlx5_eचयन_get_vport(esw, vport_num);
	अगर (IS_ERR(vport)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid port");
		वापस PTR_ERR(vport);
	पूर्ण

	mutex_lock(&esw->state_lock);
	अगर (vport->enabled) अणु
		ether_addr_copy(hw_addr, vport->info.mac);
		*hw_addr_len = ETH_ALEN;
		err = 0;
	पूर्ण
	mutex_unlock(&esw->state_lock);
	वापस err;
पूर्ण

पूर्णांक mlx5_devlink_port_function_hw_addr_set(काष्ठा devlink *devlink,
					   काष्ठा devlink_port *port,
					   स्थिर u8 *hw_addr, पूर्णांक hw_addr_len,
					   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlx5_eचयन *esw;
	काष्ठा mlx5_vport *vport;
	पूर्णांक err = -EOPNOTSUPP;
	u16 vport_num;

	esw = mlx5_devlink_eचयन_get(devlink);
	अगर (IS_ERR(esw)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Eswitch doesn't support set hw_addr");
		वापस PTR_ERR(esw);
	पूर्ण

	vport_num = mlx5_esw_devlink_port_index_to_vport_num(port->index);
	अगर (!is_port_function_supported(esw, vport_num)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Port doesn't support set hw_addr");
		वापस -EINVAL;
	पूर्ण
	vport = mlx5_eचयन_get_vport(esw, vport_num);
	अगर (IS_ERR(vport)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Invalid port");
		वापस PTR_ERR(vport);
	पूर्ण

	mutex_lock(&esw->state_lock);
	अगर (vport->enabled)
		err = mlx5_esw_set_vport_mac_locked(esw, vport, hw_addr);
	अन्यथा
		NL_SET_ERR_MSG_MOD(extack, "Eswitch vport is disabled");
	mutex_unlock(&esw->state_lock);
	वापस err;
पूर्ण

पूर्णांक mlx5_eचयन_set_vport_state(काष्ठा mlx5_eचयन *esw,
				 u16 vport, पूर्णांक link_state)
अणु
	काष्ठा mlx5_vport *evport = mlx5_eचयन_get_vport(esw, vport);
	पूर्णांक opmod = MLX5_VPORT_STATE_OP_MOD_ESW_VPORT;
	पूर्णांक other_vport = 1;
	पूर्णांक err = 0;

	अगर (!mlx5_esw_allowed(esw))
		वापस -EPERM;
	अगर (IS_ERR(evport))
		वापस PTR_ERR(evport);

	अगर (vport == MLX5_VPORT_UPLINK) अणु
		opmod = MLX5_VPORT_STATE_OP_MOD_UPLINK;
		other_vport = 0;
		vport = 0;
	पूर्ण
	mutex_lock(&esw->state_lock);
	अगर (esw->mode != MLX5_ESWITCH_LEGACY) अणु
		err = -EOPNOTSUPP;
		जाओ unlock;
	पूर्ण

	err = mlx5_modअगरy_vport_admin_state(esw->dev, opmod, vport, other_vport, link_state);
	अगर (err) अणु
		mlx5_core_warn(esw->dev, "Failed to set vport %d link state, opmod = %d, err = %d",
			       vport, opmod, err);
		जाओ unlock;
	पूर्ण

	evport->info.link_state = link_state;

unlock:
	mutex_unlock(&esw->state_lock);
	वापस err;
पूर्ण

पूर्णांक mlx5_eचयन_get_vport_config(काष्ठा mlx5_eचयन *esw,
				  u16 vport, काष्ठा अगरla_vf_info *ivi)
अणु
	काष्ठा mlx5_vport *evport = mlx5_eचयन_get_vport(esw, vport);

	अगर (IS_ERR(evport))
		वापस PTR_ERR(evport);

	स_रखो(ivi, 0, माप(*ivi));
	ivi->vf = vport - 1;

	mutex_lock(&esw->state_lock);
	ether_addr_copy(ivi->mac, evport->info.mac);
	ivi->linkstate = evport->info.link_state;
	ivi->vlan = evport->info.vlan;
	ivi->qos = evport->info.qos;
	ivi->spoofchk = evport->info.spoofchk;
	ivi->trusted = evport->info.trusted;
	ivi->min_tx_rate = evport->qos.min_rate;
	ivi->max_tx_rate = evport->qos.max_rate;
	mutex_unlock(&esw->state_lock);

	वापस 0;
पूर्ण

पूर्णांक __mlx5_eचयन_set_vport_vlan(काष्ठा mlx5_eचयन *esw,
				  u16 vport, u16 vlan, u8 qos, u8 set_flags)
अणु
	काष्ठा mlx5_vport *evport = mlx5_eचयन_get_vport(esw, vport);
	पूर्णांक err = 0;

	अगर (IS_ERR(evport))
		वापस PTR_ERR(evport);
	अगर (vlan > 4095 || qos > 7)
		वापस -EINVAL;

	err = modअगरy_esw_vport_cvlan(esw->dev, vport, vlan, qos, set_flags);
	अगर (err)
		वापस err;

	evport->info.vlan = vlan;
	evport->info.qos = qos;
	अगर (evport->enabled && esw->mode == MLX5_ESWITCH_LEGACY) अणु
		err = esw_acl_ingress_lgcy_setup(esw, evport);
		अगर (err)
			वापस err;
		err = esw_acl_egress_lgcy_setup(esw, evport);
	पूर्ण

	वापस err;
पूर्ण

अटल u32 calculate_vports_min_rate_भागider(काष्ठा mlx5_eचयन *esw)
अणु
	u32 fw_max_bw_share = MLX5_CAP_QOS(esw->dev, max_tsar_bw_share);
	काष्ठा mlx5_vport *evport;
	u32 max_guarantee = 0;
	अचिन्हित दीर्घ i;

	mlx5_esw_क्रम_each_vport(esw, i, evport) अणु
		अगर (!evport->enabled || evport->qos.min_rate < max_guarantee)
			जारी;
		max_guarantee = evport->qos.min_rate;
	पूर्ण

	अगर (max_guarantee)
		वापस max_t(u32, max_guarantee / fw_max_bw_share, 1);
	वापस 0;
पूर्ण

अटल पूर्णांक normalize_vports_min_rate(काष्ठा mlx5_eचयन *esw)
अणु
	u32 fw_max_bw_share = MLX5_CAP_QOS(esw->dev, max_tsar_bw_share);
	u32 भागider = calculate_vports_min_rate_भागider(esw);
	काष्ठा mlx5_vport *evport;
	u32 vport_max_rate;
	u32 vport_min_rate;
	अचिन्हित दीर्घ i;
	u32 bw_share;
	पूर्णांक err;

	mlx5_esw_क्रम_each_vport(esw, i, evport) अणु
		अगर (!evport->enabled)
			जारी;
		vport_min_rate = evport->qos.min_rate;
		vport_max_rate = evport->qos.max_rate;
		bw_share = 0;

		अगर (भागider)
			bw_share = MLX5_RATE_TO_BW_SHARE(vport_min_rate,
							 भागider,
							 fw_max_bw_share);

		अगर (bw_share == evport->qos.bw_share)
			जारी;

		err = esw_vport_qos_config(esw, evport, vport_max_rate,
					   bw_share);
		अगर (!err)
			evport->qos.bw_share = bw_share;
		अन्यथा
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx5_eचयन_set_vport_rate(काष्ठा mlx5_eचयन *esw, u16 vport,
				u32 max_rate, u32 min_rate)
अणु
	काष्ठा mlx5_vport *evport = mlx5_eचयन_get_vport(esw, vport);
	u32 fw_max_bw_share;
	u32 previous_min_rate;
	bool min_rate_supported;
	bool max_rate_supported;
	पूर्णांक err = 0;

	अगर (!mlx5_esw_allowed(esw))
		वापस -EPERM;
	अगर (IS_ERR(evport))
		वापस PTR_ERR(evport);

	fw_max_bw_share = MLX5_CAP_QOS(esw->dev, max_tsar_bw_share);
	min_rate_supported = MLX5_CAP_QOS(esw->dev, esw_bw_share) &&
				fw_max_bw_share >= MLX5_MIN_BW_SHARE;
	max_rate_supported = MLX5_CAP_QOS(esw->dev, esw_rate_limit);

	अगर ((min_rate && !min_rate_supported) || (max_rate && !max_rate_supported))
		वापस -EOPNOTSUPP;

	mutex_lock(&esw->state_lock);

	अगर (min_rate == evport->qos.min_rate)
		जाओ set_max_rate;

	previous_min_rate = evport->qos.min_rate;
	evport->qos.min_rate = min_rate;
	err = normalize_vports_min_rate(esw);
	अगर (err) अणु
		evport->qos.min_rate = previous_min_rate;
		जाओ unlock;
	पूर्ण

set_max_rate:
	अगर (max_rate == evport->qos.max_rate)
		जाओ unlock;

	err = esw_vport_qos_config(esw, evport, max_rate, evport->qos.bw_share);
	अगर (!err)
		evport->qos.max_rate = max_rate;

unlock:
	mutex_unlock(&esw->state_lock);
	वापस err;
पूर्ण

पूर्णांक mlx5_eचयन_get_vport_stats(काष्ठा mlx5_eचयन *esw,
				 u16 vport_num,
				 काष्ठा अगरla_vf_stats *vf_stats)
अणु
	काष्ठा mlx5_vport *vport = mlx5_eचयन_get_vport(esw, vport_num);
	पूर्णांक outlen = MLX5_ST_SZ_BYTES(query_vport_counter_out);
	u32 in[MLX5_ST_SZ_DW(query_vport_counter_in)] = अणुपूर्ण;
	काष्ठा mlx5_vport_drop_stats stats = अणुपूर्ण;
	पूर्णांक err = 0;
	u32 *out;

	अगर (IS_ERR(vport))
		वापस PTR_ERR(vport);

	out = kvzalloc(outlen, GFP_KERNEL);
	अगर (!out)
		वापस -ENOMEM;

	MLX5_SET(query_vport_counter_in, in, opcode,
		 MLX5_CMD_OP_QUERY_VPORT_COUNTER);
	MLX5_SET(query_vport_counter_in, in, op_mod, 0);
	MLX5_SET(query_vport_counter_in, in, vport_number, vport->vport);
	MLX5_SET(query_vport_counter_in, in, other_vport, 1);

	err = mlx5_cmd_exec_inout(esw->dev, query_vport_counter, in, out);
	अगर (err)
		जाओ मुक्त_out;

	#घोषणा MLX5_GET_CTR(p, x) \
		MLX5_GET64(query_vport_counter_out, p, x)

	स_रखो(vf_stats, 0, माप(*vf_stats));
	vf_stats->rx_packets =
		MLX5_GET_CTR(out, received_eth_unicast.packets) +
		MLX5_GET_CTR(out, received_ib_unicast.packets) +
		MLX5_GET_CTR(out, received_eth_multicast.packets) +
		MLX5_GET_CTR(out, received_ib_multicast.packets) +
		MLX5_GET_CTR(out, received_eth_broadcast.packets);

	vf_stats->rx_bytes =
		MLX5_GET_CTR(out, received_eth_unicast.octets) +
		MLX5_GET_CTR(out, received_ib_unicast.octets) +
		MLX5_GET_CTR(out, received_eth_multicast.octets) +
		MLX5_GET_CTR(out, received_ib_multicast.octets) +
		MLX5_GET_CTR(out, received_eth_broadcast.octets);

	vf_stats->tx_packets =
		MLX5_GET_CTR(out, transmitted_eth_unicast.packets) +
		MLX5_GET_CTR(out, transmitted_ib_unicast.packets) +
		MLX5_GET_CTR(out, transmitted_eth_multicast.packets) +
		MLX5_GET_CTR(out, transmitted_ib_multicast.packets) +
		MLX5_GET_CTR(out, transmitted_eth_broadcast.packets);

	vf_stats->tx_bytes =
		MLX5_GET_CTR(out, transmitted_eth_unicast.octets) +
		MLX5_GET_CTR(out, transmitted_ib_unicast.octets) +
		MLX5_GET_CTR(out, transmitted_eth_multicast.octets) +
		MLX5_GET_CTR(out, transmitted_ib_multicast.octets) +
		MLX5_GET_CTR(out, transmitted_eth_broadcast.octets);

	vf_stats->multicast =
		MLX5_GET_CTR(out, received_eth_multicast.packets) +
		MLX5_GET_CTR(out, received_ib_multicast.packets);

	vf_stats->broadcast =
		MLX5_GET_CTR(out, received_eth_broadcast.packets);

	err = mlx5_esw_query_vport_drop_stats(esw->dev, vport, &stats);
	अगर (err)
		जाओ मुक्त_out;
	vf_stats->rx_dropped = stats.rx_dropped;
	vf_stats->tx_dropped = stats.tx_dropped;

मुक्त_out:
	kvमुक्त(out);
	वापस err;
पूर्ण

u8 mlx5_eचयन_mode(काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_eचयन *esw = dev->priv.eचयन;

	वापस mlx5_esw_allowed(esw) ? esw->mode : MLX5_ESWITCH_NONE;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_eचयन_mode);

क्रमागत devlink_eचयन_encap_mode
mlx5_eचयन_get_encap_mode(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_eचयन *esw;

	esw = dev->priv.eचयन;
	वापस mlx5_esw_allowed(esw) ? esw->offloads.encap :
		DEVLINK_ESWITCH_ENCAP_MODE_NONE;
पूर्ण
EXPORT_SYMBOL(mlx5_eचयन_get_encap_mode);

bool mlx5_esw_lag_prereq(काष्ठा mlx5_core_dev *dev0, काष्ठा mlx5_core_dev *dev1)
अणु
	अगर ((dev0->priv.eचयन->mode == MLX5_ESWITCH_NONE &&
	     dev1->priv.eचयन->mode == MLX5_ESWITCH_NONE) ||
	    (dev0->priv.eचयन->mode == MLX5_ESWITCH_OFFLOADS &&
	     dev1->priv.eचयन->mode == MLX5_ESWITCH_OFFLOADS))
		वापस true;

	वापस false;
पूर्ण

bool mlx5_esw_multipath_prereq(काष्ठा mlx5_core_dev *dev0,
			       काष्ठा mlx5_core_dev *dev1)
अणु
	वापस (dev0->priv.eचयन->mode == MLX5_ESWITCH_OFFLOADS &&
		dev1->priv.eचयन->mode == MLX5_ESWITCH_OFFLOADS);
पूर्ण

पूर्णांक mlx5_esw_event_notअगरier_रेजिस्टर(काष्ठा mlx5_eचयन *esw, काष्ठा notअगरier_block *nb)
अणु
	वापस blocking_notअगरier_chain_रेजिस्टर(&esw->n_head, nb);
पूर्ण

व्योम mlx5_esw_event_notअगरier_unरेजिस्टर(काष्ठा mlx5_eचयन *esw, काष्ठा notअगरier_block *nb)
अणु
	blocking_notअगरier_chain_unरेजिस्टर(&esw->n_head, nb);
पूर्ण

/**
 * mlx5_esw_hold() - Try to take a पढ़ो lock on esw mode lock.
 * @mdev: mlx5 core device.
 *
 * Should be called by esw resources callers.
 *
 * Return: true on success or false.
 */
bool mlx5_esw_hold(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_eचयन *esw = mdev->priv.eचयन;

	/* e.g. VF करोesn't have eचयन so nothing to करो */
	अगर (!mlx5_esw_allowed(esw))
		वापस true;

	अगर (करोwn_पढ़ो_trylock(&esw->mode_lock) != 0)
		वापस true;

	वापस false;
पूर्ण

/**
 * mlx5_esw_release() - Release a पढ़ो lock on esw mode lock.
 * @mdev: mlx5 core device.
 */
व्योम mlx5_esw_release(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_eचयन *esw = mdev->priv.eचयन;

	अगर (mlx5_esw_allowed(esw))
		up_पढ़ो(&esw->mode_lock);
पूर्ण

/**
 * mlx5_esw_get() - Increase esw user count.
 * @mdev: mlx5 core device.
 */
व्योम mlx5_esw_get(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_eचयन *esw = mdev->priv.eचयन;

	अगर (mlx5_esw_allowed(esw))
		atomic64_inc(&esw->user_count);
पूर्ण

/**
 * mlx5_esw_put() - Decrease esw user count.
 * @mdev: mlx5 core device.
 */
व्योम mlx5_esw_put(काष्ठा mlx5_core_dev *mdev)
अणु
	काष्ठा mlx5_eचयन *esw = mdev->priv.eचयन;

	अगर (mlx5_esw_allowed(esw))
		atomic64_dec_अगर_positive(&esw->user_count);
पूर्ण

/**
 * mlx5_esw_try_lock() - Take a ग_लिखो lock on esw mode lock.
 * @esw: eचयन device.
 *
 * Should be called by esw mode change routine.
 *
 * Return:
 * * 0       - esw mode अगर successfully locked and refcount is 0.
 * * -EBUSY  - refcount is not 0.
 * * -EINVAL - In the middle of चयनing mode or lock is alपढ़ोy held.
 */
पूर्णांक mlx5_esw_try_lock(काष्ठा mlx5_eचयन *esw)
अणु
	अगर (करोwn_ग_लिखो_trylock(&esw->mode_lock) == 0)
		वापस -EINVAL;

	अगर (atomic64_पढ़ो(&esw->user_count) > 0) अणु
		up_ग_लिखो(&esw->mode_lock);
		वापस -EBUSY;
	पूर्ण

	वापस esw->mode;
पूर्ण

/**
 * mlx5_esw_unlock() - Release ग_लिखो lock on esw mode lock
 * @esw: eचयन device.
 */
व्योम mlx5_esw_unlock(काष्ठा mlx5_eचयन *esw)
अणु
	up_ग_लिखो(&esw->mode_lock);
पूर्ण

/**
 * mlx5_eचयन_get_total_vports - Get total vports of the eचयन
 *
 * @dev: Poपूर्णांकer to core device
 *
 * mlx5_eचयन_get_total_vports वापसs total number of eचयन vports.
 */
u16 mlx5_eचयन_get_total_vports(स्थिर काष्ठा mlx5_core_dev *dev)
अणु
	काष्ठा mlx5_eचयन *esw;

	esw = dev->priv.eचयन;
	वापस mlx5_esw_allowed(esw) ? esw->total_vports : 0;
पूर्ण
EXPORT_SYMBOL_GPL(mlx5_eचयन_get_total_vports);
