<शैली गुरु>
/*
 * Copyright (c) 2004, 2005 Topspin Communications.  All rights reserved.
 * Copyright (c) 2005, 2006, 2007, 2008 Mellanox Technologies.
 * All rights reserved.
 * Copyright (c) 2005, 2006, 2007 Cisco Systems, Inc.  All rights reserved.
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

#समावेश <linux/sched.h>
#समावेश <linux/pci.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/mlx4/cmd.h>
#समावेश <linux/mlx4/qp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/etherdevice.h>

#समावेश "mlx4.h"
#समावेश "fw.h"
#समावेश "mlx4_stats.h"

#घोषणा MLX4_MAC_VALID		(1ull << 63)
#घोषणा MLX4_PF_COUNTERS_PER_PORT	2
#घोषणा MLX4_VF_COUNTERS_PER_PORT	1

काष्ठा mac_res अणु
	काष्ठा list_head list;
	u64 mac;
	पूर्णांक ref_count;
	u8 smac_index;
	u8 port;
पूर्ण;

काष्ठा vlan_res अणु
	काष्ठा list_head list;
	u16 vlan;
	पूर्णांक ref_count;
	पूर्णांक vlan_index;
	u8 port;
पूर्ण;

काष्ठा res_common अणु
	काष्ठा list_head	list;
	काष्ठा rb_node		node;
	u64		        res_id;
	पूर्णांक			owner;
	पूर्णांक			state;
	पूर्णांक			from_state;
	पूर्णांक			to_state;
	पूर्णांक			removing;
	स्थिर अक्षर		*func_name;
पूर्ण;

क्रमागत अणु
	RES_ANY_BUSY = 1
पूर्ण;

काष्ठा res_gid अणु
	काष्ठा list_head	list;
	u8			gid[16];
	क्रमागत mlx4_protocol	prot;
	क्रमागत mlx4_steer_type	steer;
	u64			reg_id;
पूर्ण;

क्रमागत res_qp_states अणु
	RES_QP_BUSY = RES_ANY_BUSY,

	/* QP number was allocated */
	RES_QP_RESERVED,

	/* ICM memory क्रम QP context was mapped */
	RES_QP_MAPPED,

	/* QP is in hw ownership */
	RES_QP_HW
पूर्ण;

काष्ठा res_qp अणु
	काष्ठा res_common	com;
	काष्ठा res_mtt	       *mtt;
	काष्ठा res_cq	       *rcq;
	काष्ठा res_cq	       *scq;
	काष्ठा res_srq	       *srq;
	काष्ठा list_head	mcg_list;
	spinlock_t		mcg_spl;
	पूर्णांक			local_qpn;
	atomic_t		ref_count;
	u32			qpc_flags;
	/* saved qp params beक्रमe VST enक्रमcement in order to restore on VGT */
	u8			sched_queue;
	__be32			param3;
	u8			vlan_control;
	u8			fvl_rx;
	u8			pri_path_fl;
	u8			vlan_index;
	u8			feup;
पूर्ण;

क्रमागत res_mtt_states अणु
	RES_MTT_BUSY = RES_ANY_BUSY,
	RES_MTT_ALLOCATED,
पूर्ण;

अटल अंतरभूत स्थिर अक्षर *mtt_states_str(क्रमागत res_mtt_states state)
अणु
	चयन (state) अणु
	हाल RES_MTT_BUSY: वापस "RES_MTT_BUSY";
	हाल RES_MTT_ALLOCATED: वापस "RES_MTT_ALLOCATED";
	शेष: वापस "Unknown";
	पूर्ण
पूर्ण

काष्ठा res_mtt अणु
	काष्ठा res_common	com;
	पूर्णांक			order;
	atomic_t		ref_count;
पूर्ण;

क्रमागत res_mpt_states अणु
	RES_MPT_BUSY = RES_ANY_BUSY,
	RES_MPT_RESERVED,
	RES_MPT_MAPPED,
	RES_MPT_HW,
पूर्ण;

काष्ठा res_mpt अणु
	काष्ठा res_common	com;
	काष्ठा res_mtt	       *mtt;
	पूर्णांक			key;
पूर्ण;

क्रमागत res_eq_states अणु
	RES_EQ_BUSY = RES_ANY_BUSY,
	RES_EQ_RESERVED,
	RES_EQ_HW,
पूर्ण;

काष्ठा res_eq अणु
	काष्ठा res_common	com;
	काष्ठा res_mtt	       *mtt;
पूर्ण;

क्रमागत res_cq_states अणु
	RES_CQ_BUSY = RES_ANY_BUSY,
	RES_CQ_ALLOCATED,
	RES_CQ_HW,
पूर्ण;

काष्ठा res_cq अणु
	काष्ठा res_common	com;
	काष्ठा res_mtt	       *mtt;
	atomic_t		ref_count;
पूर्ण;

क्रमागत res_srq_states अणु
	RES_SRQ_BUSY = RES_ANY_BUSY,
	RES_SRQ_ALLOCATED,
	RES_SRQ_HW,
पूर्ण;

काष्ठा res_srq अणु
	काष्ठा res_common	com;
	काष्ठा res_mtt	       *mtt;
	काष्ठा res_cq	       *cq;
	atomic_t		ref_count;
पूर्ण;

क्रमागत res_counter_states अणु
	RES_COUNTER_BUSY = RES_ANY_BUSY,
	RES_COUNTER_ALLOCATED,
पूर्ण;

काष्ठा res_counter अणु
	काष्ठा res_common	com;
	पूर्णांक			port;
पूर्ण;

क्रमागत res_xrcdn_states अणु
	RES_XRCD_BUSY = RES_ANY_BUSY,
	RES_XRCD_ALLOCATED,
पूर्ण;

काष्ठा res_xrcdn अणु
	काष्ठा res_common	com;
	पूर्णांक			port;
पूर्ण;

क्रमागत res_fs_rule_states अणु
	RES_FS_RULE_BUSY = RES_ANY_BUSY,
	RES_FS_RULE_ALLOCATED,
पूर्ण;

काष्ठा res_fs_rule अणु
	काष्ठा res_common	com;
	पूर्णांक			qpn;
	/* VF DMFS mbox with port flipped */
	व्योम			*mirr_mbox;
	/* > 0 --> apply mirror when getting पूर्णांकo HA mode      */
	/* = 0 --> un-apply mirror when getting out of HA mode */
	u32			mirr_mbox_size;
	काष्ठा list_head	mirr_list;
	u64			mirr_rule_id;
पूर्ण;

अटल व्योम *res_tracker_lookup(काष्ठा rb_root *root, u64 res_id)
अणु
	काष्ठा rb_node *node = root->rb_node;

	जबतक (node) अणु
		काष्ठा res_common *res = rb_entry(node, काष्ठा res_common,
						  node);

		अगर (res_id < res->res_id)
			node = node->rb_left;
		अन्यथा अगर (res_id > res->res_id)
			node = node->rb_right;
		अन्यथा
			वापस res;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक res_tracker_insert(काष्ठा rb_root *root, काष्ठा res_common *res)
अणु
	काष्ठा rb_node **new = &(root->rb_node), *parent = शून्य;

	/* Figure out where to put new node */
	जबतक (*new) अणु
		काष्ठा res_common *this = rb_entry(*new, काष्ठा res_common,
						   node);

		parent = *new;
		अगर (res->res_id < this->res_id)
			new = &((*new)->rb_left);
		अन्यथा अगर (res->res_id > this->res_id)
			new = &((*new)->rb_right);
		अन्यथा
			वापस -EEXIST;
	पूर्ण

	/* Add new node and rebalance tree. */
	rb_link_node(&res->node, parent, new);
	rb_insert_color(&res->node, root);

	वापस 0;
पूर्ण

क्रमागत qp_transition अणु
	QP_TRANS_INIT2RTR,
	QP_TRANS_RTR2RTS,
	QP_TRANS_RTS2RTS,
	QP_TRANS_SQERR2RTS,
	QP_TRANS_SQD2SQD,
	QP_TRANS_SQD2RTS
पूर्ण;

/* For Debug uses */
अटल स्थिर अक्षर *resource_str(क्रमागत mlx4_resource rt)
अणु
	चयन (rt) अणु
	हाल RES_QP: वापस "RES_QP";
	हाल RES_CQ: वापस "RES_CQ";
	हाल RES_SRQ: वापस "RES_SRQ";
	हाल RES_MPT: वापस "RES_MPT";
	हाल RES_MTT: वापस "RES_MTT";
	हाल RES_MAC: वापस  "RES_MAC";
	हाल RES_VLAN: वापस  "RES_VLAN";
	हाल RES_EQ: वापस "RES_EQ";
	हाल RES_COUNTER: वापस "RES_COUNTER";
	हाल RES_FS_RULE: वापस "RES_FS_RULE";
	हाल RES_XRCD: वापस "RES_XRCD";
	शेष: वापस "Unknown resource type !!!";
	पूर्ण
पूर्ण

अटल व्योम rem_slave_vlans(काष्ठा mlx4_dev *dev, पूर्णांक slave);
अटल अंतरभूत पूर्णांक mlx4_grant_resource(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				      क्रमागत mlx4_resource res_type, पूर्णांक count,
				      पूर्णांक port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा resource_allocator *res_alloc =
		&priv->mfunc.master.res_tracker.res_alloc[res_type];
	पूर्णांक err = -EDQUOT;
	पूर्णांक allocated, मुक्त, reserved, guaranteed, from_मुक्त;
	पूर्णांक from_rsvd;

	अगर (slave > dev->persist->num_vfs)
		वापस -EINVAL;

	spin_lock(&res_alloc->alloc_lock);
	allocated = (port > 0) ?
		res_alloc->allocated[(port - 1) *
		(dev->persist->num_vfs + 1) + slave] :
		res_alloc->allocated[slave];
	मुक्त = (port > 0) ? res_alloc->res_port_मुक्त[port - 1] :
		res_alloc->res_मुक्त;
	reserved = (port > 0) ? res_alloc->res_port_rsvd[port - 1] :
		res_alloc->res_reserved;
	guaranteed = res_alloc->guaranteed[slave];

	अगर (allocated + count > res_alloc->quota[slave]) अणु
		mlx4_warn(dev, "VF %d port %d res %s: quota exceeded, count %d alloc %d quota %d\n",
			  slave, port, resource_str(res_type), count,
			  allocated, res_alloc->quota[slave]);
		जाओ out;
	पूर्ण

	अगर (allocated + count <= guaranteed) अणु
		err = 0;
		from_rsvd = count;
	पूर्ण अन्यथा अणु
		/* portion may need to be obtained from मुक्त area */
		अगर (guaranteed - allocated > 0)
			from_मुक्त = count - (guaranteed - allocated);
		अन्यथा
			from_मुक्त = count;

		from_rsvd = count - from_मुक्त;

		अगर (मुक्त - from_मुक्त >= reserved)
			err = 0;
		अन्यथा
			mlx4_warn(dev, "VF %d port %d res %s: free pool empty, free %d from_free %d rsvd %d\n",
				  slave, port, resource_str(res_type), मुक्त,
				  from_मुक्त, reserved);
	पूर्ण

	अगर (!err) अणु
		/* grant the request */
		अगर (port > 0) अणु
			res_alloc->allocated[(port - 1) *
			(dev->persist->num_vfs + 1) + slave] += count;
			res_alloc->res_port_मुक्त[port - 1] -= count;
			res_alloc->res_port_rsvd[port - 1] -= from_rsvd;
		पूर्ण अन्यथा अणु
			res_alloc->allocated[slave] += count;
			res_alloc->res_मुक्त -= count;
			res_alloc->res_reserved -= from_rsvd;
		पूर्ण
	पूर्ण

out:
	spin_unlock(&res_alloc->alloc_lock);
	वापस err;
पूर्ण

अटल अंतरभूत व्योम mlx4_release_resource(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				    क्रमागत mlx4_resource res_type, पूर्णांक count,
				    पूर्णांक port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा resource_allocator *res_alloc =
		&priv->mfunc.master.res_tracker.res_alloc[res_type];
	पूर्णांक allocated, guaranteed, from_rsvd;

	अगर (slave > dev->persist->num_vfs)
		वापस;

	spin_lock(&res_alloc->alloc_lock);

	allocated = (port > 0) ?
		res_alloc->allocated[(port - 1) *
		(dev->persist->num_vfs + 1) + slave] :
		res_alloc->allocated[slave];
	guaranteed = res_alloc->guaranteed[slave];

	अगर (allocated - count >= guaranteed) अणु
		from_rsvd = 0;
	पूर्ण अन्यथा अणु
		/* portion may need to be वापसed to reserved area */
		अगर (allocated - guaranteed > 0)
			from_rsvd = count - (allocated - guaranteed);
		अन्यथा
			from_rsvd = count;
	पूर्ण

	अगर (port > 0) अणु
		res_alloc->allocated[(port - 1) *
		(dev->persist->num_vfs + 1) + slave] -= count;
		res_alloc->res_port_मुक्त[port - 1] += count;
		res_alloc->res_port_rsvd[port - 1] += from_rsvd;
	पूर्ण अन्यथा अणु
		res_alloc->allocated[slave] -= count;
		res_alloc->res_मुक्त += count;
		res_alloc->res_reserved += from_rsvd;
	पूर्ण

	spin_unlock(&res_alloc->alloc_lock);
	वापस;
पूर्ण

अटल अंतरभूत व्योम initialize_res_quotas(काष्ठा mlx4_dev *dev,
					 काष्ठा resource_allocator *res_alloc,
					 क्रमागत mlx4_resource res_type,
					 पूर्णांक vf, पूर्णांक num_instances)
अणु
	res_alloc->guaranteed[vf] = num_instances /
				    (2 * (dev->persist->num_vfs + 1));
	res_alloc->quota[vf] = (num_instances / 2) + res_alloc->guaranteed[vf];
	अगर (vf == mlx4_master_func_num(dev)) अणु
		res_alloc->res_मुक्त = num_instances;
		अगर (res_type == RES_MTT) अणु
			/* reserved mtts will be taken out of the PF allocation */
			res_alloc->res_मुक्त += dev->caps.reserved_mtts;
			res_alloc->guaranteed[vf] += dev->caps.reserved_mtts;
			res_alloc->quota[vf] += dev->caps.reserved_mtts;
		पूर्ण
	पूर्ण
पूर्ण

व्योम mlx4_init_quotas(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक pf;

	/* quotas क्रम VFs are initialized in mlx4_slave_cap */
	अगर (mlx4_is_slave(dev))
		वापस;

	अगर (!mlx4_is_mfunc(dev)) अणु
		dev->quotas.qp = dev->caps.num_qps - dev->caps.reserved_qps -
			mlx4_num_reserved_sqps(dev);
		dev->quotas.cq = dev->caps.num_cqs - dev->caps.reserved_cqs;
		dev->quotas.srq = dev->caps.num_srqs - dev->caps.reserved_srqs;
		dev->quotas.mtt = dev->caps.num_mtts - dev->caps.reserved_mtts;
		dev->quotas.mpt = dev->caps.num_mpts - dev->caps.reserved_mrws;
		वापस;
	पूर्ण

	pf = mlx4_master_func_num(dev);
	dev->quotas.qp =
		priv->mfunc.master.res_tracker.res_alloc[RES_QP].quota[pf];
	dev->quotas.cq =
		priv->mfunc.master.res_tracker.res_alloc[RES_CQ].quota[pf];
	dev->quotas.srq =
		priv->mfunc.master.res_tracker.res_alloc[RES_SRQ].quota[pf];
	dev->quotas.mtt =
		priv->mfunc.master.res_tracker.res_alloc[RES_MTT].quota[pf];
	dev->quotas.mpt =
		priv->mfunc.master.res_tracker.res_alloc[RES_MPT].quota[pf];
पूर्ण

अटल पूर्णांक
mlx4_calc_res_counter_guaranteed(काष्ठा mlx4_dev *dev,
				 काष्ठा resource_allocator *res_alloc,
				 पूर्णांक vf)
अणु
	काष्ठा mlx4_active_ports actv_ports;
	पूर्णांक ports, counters_guaranteed;

	/* For master, only allocate according to the number of phys ports */
	अगर (vf == mlx4_master_func_num(dev))
		वापस MLX4_PF_COUNTERS_PER_PORT * dev->caps.num_ports;

	/* calculate real number of ports क्रम the VF */
	actv_ports = mlx4_get_active_ports(dev, vf);
	ports = biपंचांगap_weight(actv_ports.ports, dev->caps.num_ports);
	counters_guaranteed = ports * MLX4_VF_COUNTERS_PER_PORT;

	/* If we करो not have enough counters क्रम this VF, करो not
	 * allocate any क्रम it. '-1' to reduce the sink counter.
	 */
	अगर ((res_alloc->res_reserved + counters_guaranteed) >
	    (dev->caps.max_counters - 1))
		वापस 0;

	वापस counters_guaranteed;
पूर्ण

पूर्णांक mlx4_init_resource_tracker(काष्ठा mlx4_dev *dev)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक i, j;
	पूर्णांक t;

	priv->mfunc.master.res_tracker.slave_list =
		kसुस्मृति(dev->num_slaves, माप(काष्ठा slave_list),
			GFP_KERNEL);
	अगर (!priv->mfunc.master.res_tracker.slave_list)
		वापस -ENOMEM;

	क्रम (i = 0 ; i < dev->num_slaves; i++) अणु
		क्रम (t = 0; t < MLX4_NUM_OF_RESOURCE_TYPE; ++t)
			INIT_LIST_HEAD(&priv->mfunc.master.res_tracker.
				       slave_list[i].res_list[t]);
		mutex_init(&priv->mfunc.master.res_tracker.slave_list[i].mutex);
	पूर्ण

	mlx4_dbg(dev, "Started init_resource_tracker: %ld slaves\n",
		 dev->num_slaves);
	क्रम (i = 0 ; i < MLX4_NUM_OF_RESOURCE_TYPE; i++)
		priv->mfunc.master.res_tracker.res_tree[i] = RB_ROOT;

	क्रम (i = 0; i < MLX4_NUM_OF_RESOURCE_TYPE; i++) अणु
		काष्ठा resource_allocator *res_alloc =
			&priv->mfunc.master.res_tracker.res_alloc[i];
		res_alloc->quota = kदो_स्मृति_array(dev->persist->num_vfs + 1,
						 माप(पूर्णांक),
						 GFP_KERNEL);
		res_alloc->guaranteed = kदो_स्मृति_array(dev->persist->num_vfs + 1,
						      माप(पूर्णांक),
						      GFP_KERNEL);
		अगर (i == RES_MAC || i == RES_VLAN)
			res_alloc->allocated =
				kसुस्मृति(MLX4_MAX_PORTS *
						(dev->persist->num_vfs + 1),
					माप(पूर्णांक), GFP_KERNEL);
		अन्यथा
			res_alloc->allocated =
				kसुस्मृति(dev->persist->num_vfs + 1,
					माप(पूर्णांक), GFP_KERNEL);
		/* Reduce the sink counter */
		अगर (i == RES_COUNTER)
			res_alloc->res_मुक्त = dev->caps.max_counters - 1;

		अगर (!res_alloc->quota || !res_alloc->guaranteed ||
		    !res_alloc->allocated)
			जाओ no_mem_err;

		spin_lock_init(&res_alloc->alloc_lock);
		क्रम (t = 0; t < dev->persist->num_vfs + 1; t++) अणु
			काष्ठा mlx4_active_ports actv_ports =
				mlx4_get_active_ports(dev, t);
			चयन (i) अणु
			हाल RES_QP:
				initialize_res_quotas(dev, res_alloc, RES_QP,
						      t, dev->caps.num_qps -
						      dev->caps.reserved_qps -
						      mlx4_num_reserved_sqps(dev));
				अवरोध;
			हाल RES_CQ:
				initialize_res_quotas(dev, res_alloc, RES_CQ,
						      t, dev->caps.num_cqs -
						      dev->caps.reserved_cqs);
				अवरोध;
			हाल RES_SRQ:
				initialize_res_quotas(dev, res_alloc, RES_SRQ,
						      t, dev->caps.num_srqs -
						      dev->caps.reserved_srqs);
				अवरोध;
			हाल RES_MPT:
				initialize_res_quotas(dev, res_alloc, RES_MPT,
						      t, dev->caps.num_mpts -
						      dev->caps.reserved_mrws);
				अवरोध;
			हाल RES_MTT:
				initialize_res_quotas(dev, res_alloc, RES_MTT,
						      t, dev->caps.num_mtts -
						      dev->caps.reserved_mtts);
				अवरोध;
			हाल RES_MAC:
				अगर (t == mlx4_master_func_num(dev)) अणु
					पूर्णांक max_vfs_pport = 0;
					/* Calculate the max vfs per port क्रम */
					/* both ports.			      */
					क्रम (j = 0; j < dev->caps.num_ports;
					     j++) अणु
						काष्ठा mlx4_slaves_pport slaves_pport =
							mlx4_phys_to_slaves_pport(dev, j + 1);
						अचिन्हित current_slaves =
							biपंचांगap_weight(slaves_pport.slaves,
								      dev->caps.num_ports) - 1;
						अगर (max_vfs_pport < current_slaves)
							max_vfs_pport =
								current_slaves;
					पूर्ण
					res_alloc->quota[t] =
						MLX4_MAX_MAC_NUM -
						2 * max_vfs_pport;
					res_alloc->guaranteed[t] = 2;
					क्रम (j = 0; j < MLX4_MAX_PORTS; j++)
						res_alloc->res_port_मुक्त[j] =
							MLX4_MAX_MAC_NUM;
				पूर्ण अन्यथा अणु
					res_alloc->quota[t] = MLX4_MAX_MAC_NUM;
					res_alloc->guaranteed[t] = 2;
				पूर्ण
				अवरोध;
			हाल RES_VLAN:
				अगर (t == mlx4_master_func_num(dev)) अणु
					res_alloc->quota[t] = MLX4_MAX_VLAN_NUM;
					res_alloc->guaranteed[t] = MLX4_MAX_VLAN_NUM / 2;
					क्रम (j = 0; j < MLX4_MAX_PORTS; j++)
						res_alloc->res_port_मुक्त[j] =
							res_alloc->quota[t];
				पूर्ण अन्यथा अणु
					res_alloc->quota[t] = MLX4_MAX_VLAN_NUM / 2;
					res_alloc->guaranteed[t] = 0;
				पूर्ण
				अवरोध;
			हाल RES_COUNTER:
				res_alloc->quota[t] = dev->caps.max_counters;
				res_alloc->guaranteed[t] =
					mlx4_calc_res_counter_guaranteed(dev, res_alloc, t);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अगर (i == RES_MAC || i == RES_VLAN) अणु
				क्रम (j = 0; j < dev->caps.num_ports; j++)
					अगर (test_bit(j, actv_ports.ports))
						res_alloc->res_port_rsvd[j] +=
							res_alloc->guaranteed[t];
			पूर्ण अन्यथा अणु
				res_alloc->res_reserved += res_alloc->guaranteed[t];
			पूर्ण
		पूर्ण
	पूर्ण
	spin_lock_init(&priv->mfunc.master.res_tracker.lock);
	वापस 0;

no_mem_err:
	क्रम (i = 0; i < MLX4_NUM_OF_RESOURCE_TYPE; i++) अणु
		kमुक्त(priv->mfunc.master.res_tracker.res_alloc[i].allocated);
		priv->mfunc.master.res_tracker.res_alloc[i].allocated = शून्य;
		kमुक्त(priv->mfunc.master.res_tracker.res_alloc[i].guaranteed);
		priv->mfunc.master.res_tracker.res_alloc[i].guaranteed = शून्य;
		kमुक्त(priv->mfunc.master.res_tracker.res_alloc[i].quota);
		priv->mfunc.master.res_tracker.res_alloc[i].quota = शून्य;
	पूर्ण
	वापस -ENOMEM;
पूर्ण

व्योम mlx4_मुक्त_resource_tracker(काष्ठा mlx4_dev *dev,
				क्रमागत mlx4_res_tracker_मुक्त_type type)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक i;

	अगर (priv->mfunc.master.res_tracker.slave_list) अणु
		अगर (type != RES_TR_FREE_STRUCTS_ONLY) अणु
			क्रम (i = 0; i < dev->num_slaves; i++) अणु
				अगर (type == RES_TR_FREE_ALL ||
				    dev->caps.function != i)
					mlx4_delete_all_resources_क्रम_slave(dev, i);
			पूर्ण
			/* मुक्त master's vlans */
			i = dev->caps.function;
			mlx4_reset_roce_gids(dev, i);
			mutex_lock(&priv->mfunc.master.res_tracker.slave_list[i].mutex);
			rem_slave_vlans(dev, i);
			mutex_unlock(&priv->mfunc.master.res_tracker.slave_list[i].mutex);
		पूर्ण

		अगर (type != RES_TR_FREE_SLAVES_ONLY) अणु
			क्रम (i = 0; i < MLX4_NUM_OF_RESOURCE_TYPE; i++) अणु
				kमुक्त(priv->mfunc.master.res_tracker.res_alloc[i].allocated);
				priv->mfunc.master.res_tracker.res_alloc[i].allocated = शून्य;
				kमुक्त(priv->mfunc.master.res_tracker.res_alloc[i].guaranteed);
				priv->mfunc.master.res_tracker.res_alloc[i].guaranteed = शून्य;
				kमुक्त(priv->mfunc.master.res_tracker.res_alloc[i].quota);
				priv->mfunc.master.res_tracker.res_alloc[i].quota = शून्य;
			पूर्ण
			kमुक्त(priv->mfunc.master.res_tracker.slave_list);
			priv->mfunc.master.res_tracker.slave_list = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम update_pkey_index(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			      काष्ठा mlx4_cmd_mailbox *inbox)
अणु
	u8 sched = *(u8 *)(inbox->buf + 64);
	u8 orig_index = *(u8 *)(inbox->buf + 35);
	u8 new_index;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	पूर्णांक port;

	port = (sched >> 6 & 1) + 1;

	new_index = priv->virt2phys_pkey[slave][port - 1][orig_index];
	*(u8 *)(inbox->buf + 35) = new_index;
पूर्ण

अटल व्योम update_gid(काष्ठा mlx4_dev *dev, काष्ठा mlx4_cmd_mailbox *inbox,
		       u8 slave)
अणु
	काष्ठा mlx4_qp_context	*qp_ctx = inbox->buf + 8;
	क्रमागत mlx4_qp_optpar	optpar = be32_to_cpu(*(__be32 *) inbox->buf);
	u32			ts = (be32_to_cpu(qp_ctx->flags) >> 16) & 0xff;
	पूर्णांक port;

	अगर (MLX4_QP_ST_UD == ts) अणु
		port = (qp_ctx->pri_path.sched_queue >> 6 & 1) + 1;
		अगर (mlx4_is_eth(dev, port))
			qp_ctx->pri_path.mgid_index =
				mlx4_get_base_gid_ix(dev, slave, port) | 0x80;
		अन्यथा
			qp_ctx->pri_path.mgid_index = slave | 0x80;

	पूर्ण अन्यथा अगर (MLX4_QP_ST_RC == ts || MLX4_QP_ST_XRC == ts || MLX4_QP_ST_UC == ts) अणु
		अगर (optpar & MLX4_QP_OPTPAR_PRIMARY_ADDR_PATH) अणु
			port = (qp_ctx->pri_path.sched_queue >> 6 & 1) + 1;
			अगर (mlx4_is_eth(dev, port)) अणु
				qp_ctx->pri_path.mgid_index +=
					mlx4_get_base_gid_ix(dev, slave, port);
				qp_ctx->pri_path.mgid_index &= 0x7f;
			पूर्ण अन्यथा अणु
				qp_ctx->pri_path.mgid_index = slave & 0x7F;
			पूर्ण
		पूर्ण
		अगर (optpar & MLX4_QP_OPTPAR_ALT_ADDR_PATH) अणु
			port = (qp_ctx->alt_path.sched_queue >> 6 & 1) + 1;
			अगर (mlx4_is_eth(dev, port)) अणु
				qp_ctx->alt_path.mgid_index +=
					mlx4_get_base_gid_ix(dev, slave, port);
				qp_ctx->alt_path.mgid_index &= 0x7f;
			पूर्ण अन्यथा अणु
				qp_ctx->alt_path.mgid_index = slave & 0x7F;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक handle_counter(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp_context *qpc,
			  u8 slave, पूर्णांक port);

अटल पूर्णांक update_vport_qp_param(काष्ठा mlx4_dev *dev,
				 काष्ठा mlx4_cmd_mailbox *inbox,
				 u8 slave, u32 qpn)
अणु
	काष्ठा mlx4_qp_context	*qpc = inbox->buf + 8;
	काष्ठा mlx4_vport_oper_state *vp_oper;
	काष्ठा mlx4_priv *priv;
	u32 qp_type;
	पूर्णांक port, err = 0;

	port = (qpc->pri_path.sched_queue & 0x40) ? 2 : 1;
	priv = mlx4_priv(dev);
	vp_oper = &priv->mfunc.master.vf_oper[slave].vport[port];
	qp_type	= (be32_to_cpu(qpc->flags) >> 16) & 0xff;

	err = handle_counter(dev, qpc, slave, port);
	अगर (err)
		जाओ out;

	अगर (MLX4_VGT != vp_oper->state.शेष_vlan) अणु
		/* the reserved QPs (special, proxy, tunnel)
		 * करो not operate over vlans
		 */
		अगर (mlx4_is_qp_reserved(dev, qpn))
			वापस 0;

		/* क्रमce strip vlan by clear vsd, MLX QP refers to Raw Ethernet */
		अगर (qp_type == MLX4_QP_ST_UD ||
		    (qp_type == MLX4_QP_ST_MLX && mlx4_is_eth(dev, port))) अणु
			अगर (dev->caps.bmme_flags & MLX4_BMME_FLAG_VSD_INIT2RTR) अणु
				*(__be32 *)inbox->buf =
					cpu_to_be32(be32_to_cpu(*(__be32 *)inbox->buf) |
					MLX4_QP_OPTPAR_VLAN_STRIPPING);
				qpc->param3 &= ~cpu_to_be32(MLX4_STRIP_VLAN);
			पूर्ण अन्यथा अणु
				काष्ठा mlx4_update_qp_params params = अणु.flags = 0पूर्ण;

				err = mlx4_update_qp(dev, qpn, MLX4_UPDATE_QP_VSD, &params);
				अगर (err)
					जाओ out;
			पूर्ण
		पूर्ण

		/* preserve IF_COUNTER flag */
		qpc->pri_path.vlan_control &=
			MLX4_CTRL_ETH_SRC_CHECK_IF_COUNTER;
		अगर (vp_oper->state.link_state == IFLA_VF_LINK_STATE_DISABLE &&
		    dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_UPDATE_QP) अणु
			qpc->pri_path.vlan_control |=
				MLX4_VLAN_CTRL_ETH_TX_BLOCK_TAGGED |
				MLX4_VLAN_CTRL_ETH_TX_BLOCK_PRIO_TAGGED |
				MLX4_VLAN_CTRL_ETH_TX_BLOCK_UNTAGGED |
				MLX4_VLAN_CTRL_ETH_RX_BLOCK_PRIO_TAGGED |
				MLX4_VLAN_CTRL_ETH_RX_BLOCK_UNTAGGED |
				MLX4_VLAN_CTRL_ETH_RX_BLOCK_TAGGED;
		पूर्ण अन्यथा अगर (0 != vp_oper->state.शेष_vlan) अणु
			अगर (vp_oper->state.vlan_proto == htons(ETH_P_8021AD)) अणु
				/* vst QinQ should block untagged on TX,
				 * but cvlan is in payload and phv is set so
				 * hw see it as untagged. Block tagged instead.
				 */
				qpc->pri_path.vlan_control |=
					MLX4_VLAN_CTRL_ETH_TX_BLOCK_PRIO_TAGGED |
					MLX4_VLAN_CTRL_ETH_TX_BLOCK_TAGGED |
					MLX4_VLAN_CTRL_ETH_RX_BLOCK_PRIO_TAGGED |
					MLX4_VLAN_CTRL_ETH_RX_BLOCK_UNTAGGED;
			पूर्ण अन्यथा अणु /* vst 802.1Q */
				qpc->pri_path.vlan_control |=
					MLX4_VLAN_CTRL_ETH_TX_BLOCK_TAGGED |
					MLX4_VLAN_CTRL_ETH_RX_BLOCK_PRIO_TAGGED |
					MLX4_VLAN_CTRL_ETH_RX_BLOCK_UNTAGGED;
			पूर्ण
		पूर्ण अन्यथा अणु /* priority tagged */
			qpc->pri_path.vlan_control |=
				MLX4_VLAN_CTRL_ETH_TX_BLOCK_TAGGED |
				MLX4_VLAN_CTRL_ETH_RX_BLOCK_TAGGED;
		पूर्ण

		qpc->pri_path.fvl_rx |= MLX4_FVL_RX_FORCE_ETH_VLAN;
		qpc->pri_path.vlan_index = vp_oper->vlan_idx;
		qpc->pri_path.fl |= MLX4_FL_ETH_HIDE_CQE_VLAN;
		अगर (vp_oper->state.vlan_proto == htons(ETH_P_8021AD))
			qpc->pri_path.fl |= MLX4_FL_SV;
		अन्यथा
			qpc->pri_path.fl |= MLX4_FL_CV;
		qpc->pri_path.feup |= MLX4_FEUP_FORCE_ETH_UP | MLX4_FVL_FORCE_ETH_VLAN;
		qpc->pri_path.sched_queue &= 0xC7;
		qpc->pri_path.sched_queue |= (vp_oper->state.शेष_qos) << 3;
		qpc->qos_vport = vp_oper->state.qos_vport;
	पूर्ण
	अगर (vp_oper->state.spoofchk) अणु
		qpc->pri_path.feup |= MLX4_FSM_FORCE_ETH_SRC_MAC;
		qpc->pri_path.grh_mylmc = (0x80 & qpc->pri_path.grh_mylmc) + vp_oper->mac_idx;
	पूर्ण
out:
	वापस err;
पूर्ण

अटल पूर्णांक mpt_mask(काष्ठा mlx4_dev *dev)
अणु
	वापस dev->caps.num_mpts - 1;
पूर्ण

अटल स्थिर अक्षर *mlx4_resource_type_to_str(क्रमागत mlx4_resource t)
अणु
	चयन (t) अणु
	हाल RES_QP:
		वापस "QP";
	हाल RES_CQ:
		वापस "CQ";
	हाल RES_SRQ:
		वापस "SRQ";
	हाल RES_XRCD:
		वापस "XRCD";
	हाल RES_MPT:
		वापस "MPT";
	हाल RES_MTT:
		वापस "MTT";
	हाल RES_MAC:
		वापस "MAC";
	हाल RES_VLAN:
		वापस "VLAN";
	हाल RES_COUNTER:
		वापस "COUNTER";
	हाल RES_FS_RULE:
		वापस "FS_RULE";
	हाल RES_EQ:
		वापस "EQ";
	शेष:
		वापस "INVALID RESOURCE";
	पूर्ण
पूर्ण

अटल व्योम *find_res(काष्ठा mlx4_dev *dev, u64 res_id,
		      क्रमागत mlx4_resource type)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);

	वापस res_tracker_lookup(&priv->mfunc.master.res_tracker.res_tree[type],
				  res_id);
पूर्ण

अटल पूर्णांक _get_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, u64 res_id,
		    क्रमागत mlx4_resource type,
		    व्योम *res, स्थिर अक्षर *func_name)
अणु
	काष्ठा res_common *r;
	पूर्णांक err = 0;

	spin_lock_irq(mlx4_tlock(dev));
	r = find_res(dev, res_id, type);
	अगर (!r) अणु
		err = -ENONET;
		जाओ निकास;
	पूर्ण

	अगर (r->state == RES_ANY_BUSY) अणु
		mlx4_warn(dev,
			  "%s(%d) trying to get resource %llx of type %s, but it's already taken by %s\n",
			  func_name, slave, res_id, mlx4_resource_type_to_str(type),
			  r->func_name);
		err = -EBUSY;
		जाओ निकास;
	पूर्ण

	अगर (r->owner != slave) अणु
		err = -EPERM;
		जाओ निकास;
	पूर्ण

	r->from_state = r->state;
	r->state = RES_ANY_BUSY;
	r->func_name = func_name;

	अगर (res)
		*((काष्ठा res_common **)res) = r;

निकास:
	spin_unlock_irq(mlx4_tlock(dev));
	वापस err;
पूर्ण

#घोषणा get_res(dev, slave, res_id, type, res) \
	_get_res((dev), (slave), (res_id), (type), (res), __func__)

पूर्णांक mlx4_get_slave_from_resource_id(काष्ठा mlx4_dev *dev,
				    क्रमागत mlx4_resource type,
				    u64 res_id, पूर्णांक *slave)
अणु

	काष्ठा res_common *r;
	पूर्णांक err = -ENOENT;
	पूर्णांक id = res_id;

	अगर (type == RES_QP)
		id &= 0x7fffff;
	spin_lock(mlx4_tlock(dev));

	r = find_res(dev, id, type);
	अगर (r) अणु
		*slave = r->owner;
		err = 0;
	पूर्ण
	spin_unlock(mlx4_tlock(dev));

	वापस err;
पूर्ण

अटल व्योम put_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, u64 res_id,
		    क्रमागत mlx4_resource type)
अणु
	काष्ठा res_common *r;

	spin_lock_irq(mlx4_tlock(dev));
	r = find_res(dev, res_id, type);
	अगर (r) अणु
		r->state = r->from_state;
		r->func_name = "";
	पूर्ण
	spin_unlock_irq(mlx4_tlock(dev));
पूर्ण

अटल पूर्णांक counter_alloc_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			     u64 in_param, u64 *out_param, पूर्णांक port);

अटल पूर्णांक handle_existing_counter(काष्ठा mlx4_dev *dev, u8 slave, पूर्णांक port,
				   पूर्णांक counter_index)
अणु
	काष्ठा res_common *r;
	काष्ठा res_counter *counter;
	पूर्णांक ret = 0;

	अगर (counter_index == MLX4_SINK_COUNTER_INDEX(dev))
		वापस ret;

	spin_lock_irq(mlx4_tlock(dev));
	r = find_res(dev, counter_index, RES_COUNTER);
	अगर (!r || r->owner != slave) अणु
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		counter = container_of(r, काष्ठा res_counter, com);
		अगर (!counter->port)
			counter->port = port;
	पूर्ण

	spin_unlock_irq(mlx4_tlock(dev));
	वापस ret;
पूर्ण

अटल पूर्णांक handle_unexisting_counter(काष्ठा mlx4_dev *dev,
				     काष्ठा mlx4_qp_context *qpc, u8 slave,
				     पूर्णांक port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा res_common *पंचांगp;
	काष्ठा res_counter *counter;
	u64 counter_idx = MLX4_SINK_COUNTER_INDEX(dev);
	पूर्णांक err = 0;

	spin_lock_irq(mlx4_tlock(dev));
	list_क्रम_each_entry(पंचांगp,
			    &tracker->slave_list[slave].res_list[RES_COUNTER],
			    list) अणु
		counter = container_of(पंचांगp, काष्ठा res_counter, com);
		अगर (port == counter->port) अणु
			qpc->pri_path.counter_index  = counter->com.res_id;
			spin_unlock_irq(mlx4_tlock(dev));
			वापस 0;
		पूर्ण
	पूर्ण
	spin_unlock_irq(mlx4_tlock(dev));

	/* No existing counter, need to allocate a new counter */
	err = counter_alloc_res(dev, slave, RES_OP_RESERVE, 0, 0, &counter_idx,
				port);
	अगर (err == -ENOENT) अणु
		err = 0;
	पूर्ण अन्यथा अगर (err && err != -ENOSPC) अणु
		mlx4_err(dev, "%s: failed to create new counter for slave %d err %d\n",
			 __func__, slave, err);
	पूर्ण अन्यथा अणु
		qpc->pri_path.counter_index = counter_idx;
		mlx4_dbg(dev, "%s: alloc new counter for slave %d index %d\n",
			 __func__, slave, qpc->pri_path.counter_index);
		err = 0;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक handle_counter(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp_context *qpc,
			  u8 slave, पूर्णांक port)
अणु
	अगर (qpc->pri_path.counter_index != MLX4_SINK_COUNTER_INDEX(dev))
		वापस handle_existing_counter(dev, slave, port,
					       qpc->pri_path.counter_index);

	वापस handle_unexisting_counter(dev, qpc, slave, port);
पूर्ण

अटल काष्ठा res_common *alloc_qp_tr(पूर्णांक id)
अणु
	काष्ठा res_qp *ret;

	ret = kzalloc(माप(*ret), GFP_KERNEL);
	अगर (!ret)
		वापस शून्य;

	ret->com.res_id = id;
	ret->com.state = RES_QP_RESERVED;
	ret->local_qpn = id;
	INIT_LIST_HEAD(&ret->mcg_list);
	spin_lock_init(&ret->mcg_spl);
	atomic_set(&ret->ref_count, 0);

	वापस &ret->com;
पूर्ण

अटल काष्ठा res_common *alloc_mtt_tr(पूर्णांक id, पूर्णांक order)
अणु
	काष्ठा res_mtt *ret;

	ret = kzalloc(माप(*ret), GFP_KERNEL);
	अगर (!ret)
		वापस शून्य;

	ret->com.res_id = id;
	ret->order = order;
	ret->com.state = RES_MTT_ALLOCATED;
	atomic_set(&ret->ref_count, 0);

	वापस &ret->com;
पूर्ण

अटल काष्ठा res_common *alloc_mpt_tr(पूर्णांक id, पूर्णांक key)
अणु
	काष्ठा res_mpt *ret;

	ret = kzalloc(माप(*ret), GFP_KERNEL);
	अगर (!ret)
		वापस शून्य;

	ret->com.res_id = id;
	ret->com.state = RES_MPT_RESERVED;
	ret->key = key;

	वापस &ret->com;
पूर्ण

अटल काष्ठा res_common *alloc_eq_tr(पूर्णांक id)
अणु
	काष्ठा res_eq *ret;

	ret = kzalloc(माप(*ret), GFP_KERNEL);
	अगर (!ret)
		वापस शून्य;

	ret->com.res_id = id;
	ret->com.state = RES_EQ_RESERVED;

	वापस &ret->com;
पूर्ण

अटल काष्ठा res_common *alloc_cq_tr(पूर्णांक id)
अणु
	काष्ठा res_cq *ret;

	ret = kzalloc(माप(*ret), GFP_KERNEL);
	अगर (!ret)
		वापस शून्य;

	ret->com.res_id = id;
	ret->com.state = RES_CQ_ALLOCATED;
	atomic_set(&ret->ref_count, 0);

	वापस &ret->com;
पूर्ण

अटल काष्ठा res_common *alloc_srq_tr(पूर्णांक id)
अणु
	काष्ठा res_srq *ret;

	ret = kzalloc(माप(*ret), GFP_KERNEL);
	अगर (!ret)
		वापस शून्य;

	ret->com.res_id = id;
	ret->com.state = RES_SRQ_ALLOCATED;
	atomic_set(&ret->ref_count, 0);

	वापस &ret->com;
पूर्ण

अटल काष्ठा res_common *alloc_counter_tr(पूर्णांक id, पूर्णांक port)
अणु
	काष्ठा res_counter *ret;

	ret = kzalloc(माप(*ret), GFP_KERNEL);
	अगर (!ret)
		वापस शून्य;

	ret->com.res_id = id;
	ret->com.state = RES_COUNTER_ALLOCATED;
	ret->port = port;

	वापस &ret->com;
पूर्ण

अटल काष्ठा res_common *alloc_xrcdn_tr(पूर्णांक id)
अणु
	काष्ठा res_xrcdn *ret;

	ret = kzalloc(माप(*ret), GFP_KERNEL);
	अगर (!ret)
		वापस शून्य;

	ret->com.res_id = id;
	ret->com.state = RES_XRCD_ALLOCATED;

	वापस &ret->com;
पूर्ण

अटल काष्ठा res_common *alloc_fs_rule_tr(u64 id, पूर्णांक qpn)
अणु
	काष्ठा res_fs_rule *ret;

	ret = kzalloc(माप(*ret), GFP_KERNEL);
	अगर (!ret)
		वापस शून्य;

	ret->com.res_id = id;
	ret->com.state = RES_FS_RULE_ALLOCATED;
	ret->qpn = qpn;
	वापस &ret->com;
पूर्ण

अटल काष्ठा res_common *alloc_tr(u64 id, क्रमागत mlx4_resource type, पूर्णांक slave,
				   पूर्णांक extra)
अणु
	काष्ठा res_common *ret;

	चयन (type) अणु
	हाल RES_QP:
		ret = alloc_qp_tr(id);
		अवरोध;
	हाल RES_MPT:
		ret = alloc_mpt_tr(id, extra);
		अवरोध;
	हाल RES_MTT:
		ret = alloc_mtt_tr(id, extra);
		अवरोध;
	हाल RES_EQ:
		ret = alloc_eq_tr(id);
		अवरोध;
	हाल RES_CQ:
		ret = alloc_cq_tr(id);
		अवरोध;
	हाल RES_SRQ:
		ret = alloc_srq_tr(id);
		अवरोध;
	हाल RES_MAC:
		pr_err("implementation missing\n");
		वापस शून्य;
	हाल RES_COUNTER:
		ret = alloc_counter_tr(id, extra);
		अवरोध;
	हाल RES_XRCD:
		ret = alloc_xrcdn_tr(id);
		अवरोध;
	हाल RES_FS_RULE:
		ret = alloc_fs_rule_tr(id, extra);
		अवरोध;
	शेष:
		वापस शून्य;
	पूर्ण
	अगर (ret)
		ret->owner = slave;

	वापस ret;
पूर्ण

पूर्णांक mlx4_calc_vf_counters(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port,
			  काष्ठा mlx4_counter *data)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा res_common *पंचांगp;
	काष्ठा res_counter *counter;
	पूर्णांक *counters_arr;
	पूर्णांक i = 0, err = 0;

	स_रखो(data, 0, माप(*data));

	counters_arr = kदो_स्मृति_array(dev->caps.max_counters,
				     माप(*counters_arr), GFP_KERNEL);
	अगर (!counters_arr)
		वापस -ENOMEM;

	spin_lock_irq(mlx4_tlock(dev));
	list_क्रम_each_entry(पंचांगp,
			    &tracker->slave_list[slave].res_list[RES_COUNTER],
			    list) अणु
		counter = container_of(पंचांगp, काष्ठा res_counter, com);
		अगर (counter->port == port) अणु
			counters_arr[i] = (पूर्णांक)पंचांगp->res_id;
			i++;
		पूर्ण
	पूर्ण
	spin_unlock_irq(mlx4_tlock(dev));
	counters_arr[i] = -1;

	i = 0;

	जबतक (counters_arr[i] != -1) अणु
		err = mlx4_get_counter_stats(dev, counters_arr[i], data,
					     0);
		अगर (err) अणु
			स_रखो(data, 0, माप(*data));
			जाओ table_changed;
		पूर्ण
		i++;
	पूर्ण

table_changed:
	kमुक्त(counters_arr);
	वापस 0;
पूर्ण

अटल पूर्णांक add_res_range(काष्ठा mlx4_dev *dev, पूर्णांक slave, u64 base, पूर्णांक count,
			 क्रमागत mlx4_resource type, पूर्णांक extra)
अणु
	पूर्णांक i;
	पूर्णांक err;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा res_common **res_arr;
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा rb_root *root = &tracker->res_tree[type];

	res_arr = kसुस्मृति(count, माप(*res_arr), GFP_KERNEL);
	अगर (!res_arr)
		वापस -ENOMEM;

	क्रम (i = 0; i < count; ++i) अणु
		res_arr[i] = alloc_tr(base + i, type, slave, extra);
		अगर (!res_arr[i]) अणु
			क्रम (--i; i >= 0; --i)
				kमुक्त(res_arr[i]);

			kमुक्त(res_arr);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	spin_lock_irq(mlx4_tlock(dev));
	क्रम (i = 0; i < count; ++i) अणु
		अगर (find_res(dev, base + i, type)) अणु
			err = -EEXIST;
			जाओ unकरो;
		पूर्ण
		err = res_tracker_insert(root, res_arr[i]);
		अगर (err)
			जाओ unकरो;
		list_add_tail(&res_arr[i]->list,
			      &tracker->slave_list[slave].res_list[type]);
	पूर्ण
	spin_unlock_irq(mlx4_tlock(dev));
	kमुक्त(res_arr);

	वापस 0;

unकरो:
	क्रम (--i; i >= 0; --i) अणु
		rb_erase(&res_arr[i]->node, root);
		list_del_init(&res_arr[i]->list);
	पूर्ण

	spin_unlock_irq(mlx4_tlock(dev));

	क्रम (i = 0; i < count; ++i)
		kमुक्त(res_arr[i]);

	kमुक्त(res_arr);

	वापस err;
पूर्ण

अटल पूर्णांक हटाओ_qp_ok(काष्ठा res_qp *res)
अणु
	अगर (res->com.state == RES_QP_BUSY || atomic_पढ़ो(&res->ref_count) ||
	    !list_empty(&res->mcg_list)) अणु
		pr_err("resource tracker: fail to remove qp, state %d, ref_count %d\n",
		       res->com.state, atomic_पढ़ो(&res->ref_count));
		वापस -EBUSY;
	पूर्ण अन्यथा अगर (res->com.state != RES_QP_RESERVED) अणु
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक हटाओ_mtt_ok(काष्ठा res_mtt *res, पूर्णांक order)
अणु
	अगर (res->com.state == RES_MTT_BUSY ||
	    atomic_पढ़ो(&res->ref_count)) अणु
		pr_devel("%s-%d: state %s, ref_count %d\n",
			 __func__, __LINE__,
			 mtt_states_str(res->com.state),
			 atomic_पढ़ो(&res->ref_count));
		वापस -EBUSY;
	पूर्ण अन्यथा अगर (res->com.state != RES_MTT_ALLOCATED)
		वापस -EPERM;
	अन्यथा अगर (res->order != order)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक हटाओ_mpt_ok(काष्ठा res_mpt *res)
अणु
	अगर (res->com.state == RES_MPT_BUSY)
		वापस -EBUSY;
	अन्यथा अगर (res->com.state != RES_MPT_RESERVED)
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल पूर्णांक हटाओ_eq_ok(काष्ठा res_eq *res)
अणु
	अगर (res->com.state == RES_MPT_BUSY)
		वापस -EBUSY;
	अन्यथा अगर (res->com.state != RES_MPT_RESERVED)
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल पूर्णांक हटाओ_counter_ok(काष्ठा res_counter *res)
अणु
	अगर (res->com.state == RES_COUNTER_BUSY)
		वापस -EBUSY;
	अन्यथा अगर (res->com.state != RES_COUNTER_ALLOCATED)
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल पूर्णांक हटाओ_xrcdn_ok(काष्ठा res_xrcdn *res)
अणु
	अगर (res->com.state == RES_XRCD_BUSY)
		वापस -EBUSY;
	अन्यथा अगर (res->com.state != RES_XRCD_ALLOCATED)
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल पूर्णांक हटाओ_fs_rule_ok(काष्ठा res_fs_rule *res)
अणु
	अगर (res->com.state == RES_FS_RULE_BUSY)
		वापस -EBUSY;
	अन्यथा अगर (res->com.state != RES_FS_RULE_ALLOCATED)
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल पूर्णांक हटाओ_cq_ok(काष्ठा res_cq *res)
अणु
	अगर (res->com.state == RES_CQ_BUSY)
		वापस -EBUSY;
	अन्यथा अगर (res->com.state != RES_CQ_ALLOCATED)
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल पूर्णांक हटाओ_srq_ok(काष्ठा res_srq *res)
अणु
	अगर (res->com.state == RES_SRQ_BUSY)
		वापस -EBUSY;
	अन्यथा अगर (res->com.state != RES_SRQ_ALLOCATED)
		वापस -EPERM;

	वापस 0;
पूर्ण

अटल पूर्णांक हटाओ_ok(काष्ठा res_common *res, क्रमागत mlx4_resource type, पूर्णांक extra)
अणु
	चयन (type) अणु
	हाल RES_QP:
		वापस हटाओ_qp_ok((काष्ठा res_qp *)res);
	हाल RES_CQ:
		वापस हटाओ_cq_ok((काष्ठा res_cq *)res);
	हाल RES_SRQ:
		वापस हटाओ_srq_ok((काष्ठा res_srq *)res);
	हाल RES_MPT:
		वापस हटाओ_mpt_ok((काष्ठा res_mpt *)res);
	हाल RES_MTT:
		वापस हटाओ_mtt_ok((काष्ठा res_mtt *)res, extra);
	हाल RES_MAC:
		वापस -EOPNOTSUPP;
	हाल RES_EQ:
		वापस हटाओ_eq_ok((काष्ठा res_eq *)res);
	हाल RES_COUNTER:
		वापस हटाओ_counter_ok((काष्ठा res_counter *)res);
	हाल RES_XRCD:
		वापस हटाओ_xrcdn_ok((काष्ठा res_xrcdn *)res);
	हाल RES_FS_RULE:
		वापस हटाओ_fs_rule_ok((काष्ठा res_fs_rule *)res);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक rem_res_range(काष्ठा mlx4_dev *dev, पूर्णांक slave, u64 base, पूर्णांक count,
			 क्रमागत mlx4_resource type, पूर्णांक extra)
अणु
	u64 i;
	पूर्णांक err;
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा res_common *r;

	spin_lock_irq(mlx4_tlock(dev));
	क्रम (i = base; i < base + count; ++i) अणु
		r = res_tracker_lookup(&tracker->res_tree[type], i);
		अगर (!r) अणु
			err = -ENOENT;
			जाओ out;
		पूर्ण
		अगर (r->owner != slave) अणु
			err = -EPERM;
			जाओ out;
		पूर्ण
		err = हटाओ_ok(r, type, extra);
		अगर (err)
			जाओ out;
	पूर्ण

	क्रम (i = base; i < base + count; ++i) अणु
		r = res_tracker_lookup(&tracker->res_tree[type], i);
		rb_erase(&r->node, &tracker->res_tree[type]);
		list_del(&r->list);
		kमुक्त(r);
	पूर्ण
	err = 0;

out:
	spin_unlock_irq(mlx4_tlock(dev));

	वापस err;
पूर्ण

अटल पूर्णांक qp_res_start_move_to(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक qpn,
				क्रमागत res_qp_states state, काष्ठा res_qp **qp,
				पूर्णांक alloc)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा res_qp *r;
	पूर्णांक err = 0;

	spin_lock_irq(mlx4_tlock(dev));
	r = res_tracker_lookup(&tracker->res_tree[RES_QP], qpn);
	अगर (!r)
		err = -ENOENT;
	अन्यथा अगर (r->com.owner != slave)
		err = -EPERM;
	अन्यथा अणु
		चयन (state) अणु
		हाल RES_QP_BUSY:
			mlx4_dbg(dev, "%s: failed RES_QP, 0x%llx\n",
				 __func__, r->com.res_id);
			err = -EBUSY;
			अवरोध;

		हाल RES_QP_RESERVED:
			अगर (r->com.state == RES_QP_MAPPED && !alloc)
				अवरोध;

			mlx4_dbg(dev, "failed RES_QP, 0x%llx\n", r->com.res_id);
			err = -EINVAL;
			अवरोध;

		हाल RES_QP_MAPPED:
			अगर ((r->com.state == RES_QP_RESERVED && alloc) ||
			    r->com.state == RES_QP_HW)
				अवरोध;
			अन्यथा अणु
				mlx4_dbg(dev, "failed RES_QP, 0x%llx\n",
					  r->com.res_id);
				err = -EINVAL;
			पूर्ण

			अवरोध;

		हाल RES_QP_HW:
			अगर (r->com.state != RES_QP_MAPPED)
				err = -EINVAL;
			अवरोध;
		शेष:
			err = -EINVAL;
		पूर्ण

		अगर (!err) अणु
			r->com.from_state = r->com.state;
			r->com.to_state = state;
			r->com.state = RES_QP_BUSY;
			अगर (qp)
				*qp = r;
		पूर्ण
	पूर्ण

	spin_unlock_irq(mlx4_tlock(dev));

	वापस err;
पूर्ण

अटल पूर्णांक mr_res_start_move_to(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक index,
				क्रमागत res_mpt_states state, काष्ठा res_mpt **mpt)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा res_mpt *r;
	पूर्णांक err = 0;

	spin_lock_irq(mlx4_tlock(dev));
	r = res_tracker_lookup(&tracker->res_tree[RES_MPT], index);
	अगर (!r)
		err = -ENOENT;
	अन्यथा अगर (r->com.owner != slave)
		err = -EPERM;
	अन्यथा अणु
		चयन (state) अणु
		हाल RES_MPT_BUSY:
			err = -EINVAL;
			अवरोध;

		हाल RES_MPT_RESERVED:
			अगर (r->com.state != RES_MPT_MAPPED)
				err = -EINVAL;
			अवरोध;

		हाल RES_MPT_MAPPED:
			अगर (r->com.state != RES_MPT_RESERVED &&
			    r->com.state != RES_MPT_HW)
				err = -EINVAL;
			अवरोध;

		हाल RES_MPT_HW:
			अगर (r->com.state != RES_MPT_MAPPED)
				err = -EINVAL;
			अवरोध;
		शेष:
			err = -EINVAL;
		पूर्ण

		अगर (!err) अणु
			r->com.from_state = r->com.state;
			r->com.to_state = state;
			r->com.state = RES_MPT_BUSY;
			अगर (mpt)
				*mpt = r;
		पूर्ण
	पूर्ण

	spin_unlock_irq(mlx4_tlock(dev));

	वापस err;
पूर्ण

अटल पूर्णांक eq_res_start_move_to(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक index,
				क्रमागत res_eq_states state, काष्ठा res_eq **eq)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा res_eq *r;
	पूर्णांक err = 0;

	spin_lock_irq(mlx4_tlock(dev));
	r = res_tracker_lookup(&tracker->res_tree[RES_EQ], index);
	अगर (!r)
		err = -ENOENT;
	अन्यथा अगर (r->com.owner != slave)
		err = -EPERM;
	अन्यथा अणु
		चयन (state) अणु
		हाल RES_EQ_BUSY:
			err = -EINVAL;
			अवरोध;

		हाल RES_EQ_RESERVED:
			अगर (r->com.state != RES_EQ_HW)
				err = -EINVAL;
			अवरोध;

		हाल RES_EQ_HW:
			अगर (r->com.state != RES_EQ_RESERVED)
				err = -EINVAL;
			अवरोध;

		शेष:
			err = -EINVAL;
		पूर्ण

		अगर (!err) अणु
			r->com.from_state = r->com.state;
			r->com.to_state = state;
			r->com.state = RES_EQ_BUSY;
		पूर्ण
	पूर्ण

	spin_unlock_irq(mlx4_tlock(dev));

	अगर (!err && eq)
		*eq = r;

	वापस err;
पूर्ण

अटल पूर्णांक cq_res_start_move_to(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक cqn,
				क्रमागत res_cq_states state, काष्ठा res_cq **cq)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा res_cq *r;
	पूर्णांक err;

	spin_lock_irq(mlx4_tlock(dev));
	r = res_tracker_lookup(&tracker->res_tree[RES_CQ], cqn);
	अगर (!r) अणु
		err = -ENOENT;
	पूर्ण अन्यथा अगर (r->com.owner != slave) अणु
		err = -EPERM;
	पूर्ण अन्यथा अगर (state == RES_CQ_ALLOCATED) अणु
		अगर (r->com.state != RES_CQ_HW)
			err = -EINVAL;
		अन्यथा अगर (atomic_पढ़ो(&r->ref_count))
			err = -EBUSY;
		अन्यथा
			err = 0;
	पूर्ण अन्यथा अगर (state != RES_CQ_HW || r->com.state != RES_CQ_ALLOCATED) अणु
		err = -EINVAL;
	पूर्ण अन्यथा अणु
		err = 0;
	पूर्ण

	अगर (!err) अणु
		r->com.from_state = r->com.state;
		r->com.to_state = state;
		r->com.state = RES_CQ_BUSY;
		अगर (cq)
			*cq = r;
	पूर्ण

	spin_unlock_irq(mlx4_tlock(dev));

	वापस err;
पूर्ण

अटल पूर्णांक srq_res_start_move_to(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक index,
				 क्रमागत res_srq_states state, काष्ठा res_srq **srq)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा res_srq *r;
	पूर्णांक err = 0;

	spin_lock_irq(mlx4_tlock(dev));
	r = res_tracker_lookup(&tracker->res_tree[RES_SRQ], index);
	अगर (!r) अणु
		err = -ENOENT;
	पूर्ण अन्यथा अगर (r->com.owner != slave) अणु
		err = -EPERM;
	पूर्ण अन्यथा अगर (state == RES_SRQ_ALLOCATED) अणु
		अगर (r->com.state != RES_SRQ_HW)
			err = -EINVAL;
		अन्यथा अगर (atomic_पढ़ो(&r->ref_count))
			err = -EBUSY;
	पूर्ण अन्यथा अगर (state != RES_SRQ_HW || r->com.state != RES_SRQ_ALLOCATED) अणु
		err = -EINVAL;
	पूर्ण

	अगर (!err) अणु
		r->com.from_state = r->com.state;
		r->com.to_state = state;
		r->com.state = RES_SRQ_BUSY;
		अगर (srq)
			*srq = r;
	पूर्ण

	spin_unlock_irq(mlx4_tlock(dev));

	वापस err;
पूर्ण

अटल व्योम res_पात_move(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   क्रमागत mlx4_resource type, पूर्णांक id)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा res_common *r;

	spin_lock_irq(mlx4_tlock(dev));
	r = res_tracker_lookup(&tracker->res_tree[type], id);
	अगर (r && (r->owner == slave))
		r->state = r->from_state;
	spin_unlock_irq(mlx4_tlock(dev));
पूर्ण

अटल व्योम res_end_move(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			 क्रमागत mlx4_resource type, पूर्णांक id)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा res_common *r;

	spin_lock_irq(mlx4_tlock(dev));
	r = res_tracker_lookup(&tracker->res_tree[type], id);
	अगर (r && (r->owner == slave))
		r->state = r->to_state;
	spin_unlock_irq(mlx4_tlock(dev));
पूर्ण

अटल पूर्णांक valid_reserved(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक qpn)
अणु
	वापस mlx4_is_qp_reserved(dev, qpn) &&
		(mlx4_is_master(dev) || mlx4_is_guest_proxy(dev, slave, qpn));
पूर्ण

अटल पूर्णांक fw_reserved(काष्ठा mlx4_dev *dev, पूर्णांक qpn)
अणु
	वापस qpn < dev->caps.reserved_qps_cnt[MLX4_QP_REGION_FW];
पूर्ण

अटल पूर्णांक qp_alloc_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			u64 in_param, u64 *out_param)
अणु
	पूर्णांक err;
	पूर्णांक count;
	पूर्णांक align;
	पूर्णांक base;
	पूर्णांक qpn;
	u8 flags;

	चयन (op) अणु
	हाल RES_OP_RESERVE:
		count = get_param_l(&in_param) & 0xffffff;
		/* Turn off all unsupported QP allocation flags that the
		 * slave tries to set.
		 */
		flags = (get_param_l(&in_param) >> 24) & dev->caps.alloc_res_qp_mask;
		align = get_param_h(&in_param);
		err = mlx4_grant_resource(dev, slave, RES_QP, count, 0);
		अगर (err)
			वापस err;

		err = __mlx4_qp_reserve_range(dev, count, align, &base, flags);
		अगर (err) अणु
			mlx4_release_resource(dev, slave, RES_QP, count, 0);
			वापस err;
		पूर्ण

		err = add_res_range(dev, slave, base, count, RES_QP, 0);
		अगर (err) अणु
			mlx4_release_resource(dev, slave, RES_QP, count, 0);
			__mlx4_qp_release_range(dev, base, count);
			वापस err;
		पूर्ण
		set_param_l(out_param, base);
		अवरोध;
	हाल RES_OP_MAP_ICM:
		qpn = get_param_l(&in_param) & 0x7fffff;
		अगर (valid_reserved(dev, slave, qpn)) अणु
			err = add_res_range(dev, slave, qpn, 1, RES_QP, 0);
			अगर (err)
				वापस err;
		पूर्ण

		err = qp_res_start_move_to(dev, slave, qpn, RES_QP_MAPPED,
					   शून्य, 1);
		अगर (err)
			वापस err;

		अगर (!fw_reserved(dev, qpn)) अणु
			err = __mlx4_qp_alloc_icm(dev, qpn);
			अगर (err) अणु
				res_पात_move(dev, slave, RES_QP, qpn);
				वापस err;
			पूर्ण
		पूर्ण

		res_end_move(dev, slave, RES_QP, qpn);
		अवरोध;

	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक mtt_alloc_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			 u64 in_param, u64 *out_param)
अणु
	पूर्णांक err = -EINVAL;
	पूर्णांक base;
	पूर्णांक order;

	अगर (op != RES_OP_RESERVE_AND_MAP)
		वापस err;

	order = get_param_l(&in_param);

	err = mlx4_grant_resource(dev, slave, RES_MTT, 1 << order, 0);
	अगर (err)
		वापस err;

	base = __mlx4_alloc_mtt_range(dev, order);
	अगर (base == -1) अणु
		mlx4_release_resource(dev, slave, RES_MTT, 1 << order, 0);
		वापस -ENOMEM;
	पूर्ण

	err = add_res_range(dev, slave, base, 1, RES_MTT, order);
	अगर (err) अणु
		mlx4_release_resource(dev, slave, RES_MTT, 1 << order, 0);
		__mlx4_मुक्त_mtt_range(dev, base, order);
	पूर्ण अन्यथा अणु
		set_param_l(out_param, base);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mpt_alloc_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			 u64 in_param, u64 *out_param)
अणु
	पूर्णांक err = -EINVAL;
	पूर्णांक index;
	पूर्णांक id;
	काष्ठा res_mpt *mpt;

	चयन (op) अणु
	हाल RES_OP_RESERVE:
		err = mlx4_grant_resource(dev, slave, RES_MPT, 1, 0);
		अगर (err)
			अवरोध;

		index = __mlx4_mpt_reserve(dev);
		अगर (index == -1) अणु
			mlx4_release_resource(dev, slave, RES_MPT, 1, 0);
			अवरोध;
		पूर्ण
		id = index & mpt_mask(dev);

		err = add_res_range(dev, slave, id, 1, RES_MPT, index);
		अगर (err) अणु
			mlx4_release_resource(dev, slave, RES_MPT, 1, 0);
			__mlx4_mpt_release(dev, index);
			अवरोध;
		पूर्ण
		set_param_l(out_param, index);
		अवरोध;
	हाल RES_OP_MAP_ICM:
		index = get_param_l(&in_param);
		id = index & mpt_mask(dev);
		err = mr_res_start_move_to(dev, slave, id,
					   RES_MPT_MAPPED, &mpt);
		अगर (err)
			वापस err;

		err = __mlx4_mpt_alloc_icm(dev, mpt->key);
		अगर (err) अणु
			res_पात_move(dev, slave, RES_MPT, id);
			वापस err;
		पूर्ण

		res_end_move(dev, slave, RES_MPT, id);
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक cq_alloc_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			u64 in_param, u64 *out_param)
अणु
	पूर्णांक cqn;
	पूर्णांक err;

	चयन (op) अणु
	हाल RES_OP_RESERVE_AND_MAP:
		err = mlx4_grant_resource(dev, slave, RES_CQ, 1, 0);
		अगर (err)
			अवरोध;

		err = __mlx4_cq_alloc_icm(dev, &cqn);
		अगर (err) अणु
			mlx4_release_resource(dev, slave, RES_CQ, 1, 0);
			अवरोध;
		पूर्ण

		err = add_res_range(dev, slave, cqn, 1, RES_CQ, 0);
		अगर (err) अणु
			mlx4_release_resource(dev, slave, RES_CQ, 1, 0);
			__mlx4_cq_मुक्त_icm(dev, cqn);
			अवरोध;
		पूर्ण

		set_param_l(out_param, cqn);
		अवरोध;

	शेष:
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक srq_alloc_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			 u64 in_param, u64 *out_param)
अणु
	पूर्णांक srqn;
	पूर्णांक err;

	चयन (op) अणु
	हाल RES_OP_RESERVE_AND_MAP:
		err = mlx4_grant_resource(dev, slave, RES_SRQ, 1, 0);
		अगर (err)
			अवरोध;

		err = __mlx4_srq_alloc_icm(dev, &srqn);
		अगर (err) अणु
			mlx4_release_resource(dev, slave, RES_SRQ, 1, 0);
			अवरोध;
		पूर्ण

		err = add_res_range(dev, slave, srqn, 1, RES_SRQ, 0);
		अगर (err) अणु
			mlx4_release_resource(dev, slave, RES_SRQ, 1, 0);
			__mlx4_srq_मुक्त_icm(dev, srqn);
			अवरोध;
		पूर्ण

		set_param_l(out_param, srqn);
		अवरोध;

	शेष:
		err = -EINVAL;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mac_find_smac_ix_in_slave(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक port,
				     u8 smac_index, u64 *mac)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा list_head *mac_list =
		&tracker->slave_list[slave].res_list[RES_MAC];
	काष्ठा mac_res *res, *पंचांगp;

	list_क्रम_each_entry_safe(res, पंचांगp, mac_list, list) अणु
		अगर (res->smac_index == smac_index && res->port == (u8) port) अणु
			*mac = res->mac;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक mac_add_to_slave(काष्ठा mlx4_dev *dev, पूर्णांक slave, u64 mac, पूर्णांक port, u8 smac_index)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा list_head *mac_list =
		&tracker->slave_list[slave].res_list[RES_MAC];
	काष्ठा mac_res *res, *पंचांगp;

	list_क्रम_each_entry_safe(res, पंचांगp, mac_list, list) अणु
		अगर (res->mac == mac && res->port == (u8) port) अणु
			/* mac found. update ref count */
			++res->ref_count;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (mlx4_grant_resource(dev, slave, RES_MAC, 1, port))
		वापस -EINVAL;
	res = kzalloc(माप(*res), GFP_KERNEL);
	अगर (!res) अणु
		mlx4_release_resource(dev, slave, RES_MAC, 1, port);
		वापस -ENOMEM;
	पूर्ण
	res->mac = mac;
	res->port = (u8) port;
	res->smac_index = smac_index;
	res->ref_count = 1;
	list_add_tail(&res->list,
		      &tracker->slave_list[slave].res_list[RES_MAC]);
	वापस 0;
पूर्ण

अटल व्योम mac_del_from_slave(काष्ठा mlx4_dev *dev, पूर्णांक slave, u64 mac,
			       पूर्णांक port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा list_head *mac_list =
		&tracker->slave_list[slave].res_list[RES_MAC];
	काष्ठा mac_res *res, *पंचांगp;

	list_क्रम_each_entry_safe(res, पंचांगp, mac_list, list) अणु
		अगर (res->mac == mac && res->port == (u8) port) अणु
			अगर (!--res->ref_count) अणु
				list_del(&res->list);
				mlx4_release_resource(dev, slave, RES_MAC, 1, port);
				kमुक्त(res);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rem_slave_macs(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा list_head *mac_list =
		&tracker->slave_list[slave].res_list[RES_MAC];
	काष्ठा mac_res *res, *पंचांगp;
	पूर्णांक i;

	list_क्रम_each_entry_safe(res, पंचांगp, mac_list, list) अणु
		list_del(&res->list);
		/* dereference the mac the num बार the slave referenced it */
		क्रम (i = 0; i < res->ref_count; i++)
			__mlx4_unरेजिस्टर_mac(dev, res->port, res->mac);
		mlx4_release_resource(dev, slave, RES_MAC, 1, res->port);
		kमुक्त(res);
	पूर्ण
पूर्ण

अटल पूर्णांक mac_alloc_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			 u64 in_param, u64 *out_param, पूर्णांक in_port)
अणु
	पूर्णांक err = -EINVAL;
	पूर्णांक port;
	u64 mac;
	u8 smac_index;

	अगर (op != RES_OP_RESERVE_AND_MAP)
		वापस err;

	port = !in_port ? get_param_l(out_param) : in_port;
	port = mlx4_slave_convert_port(
			dev, slave, port);

	अगर (port < 0)
		वापस -EINVAL;
	mac = in_param;

	err = __mlx4_रेजिस्टर_mac(dev, port, mac);
	अगर (err >= 0) अणु
		smac_index = err;
		set_param_l(out_param, err);
		err = 0;
	पूर्ण

	अगर (!err) अणु
		err = mac_add_to_slave(dev, slave, mac, port, smac_index);
		अगर (err)
			__mlx4_unरेजिस्टर_mac(dev, port, mac);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक vlan_add_to_slave(काष्ठा mlx4_dev *dev, पूर्णांक slave, u16 vlan,
			     पूर्णांक port, पूर्णांक vlan_index)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा list_head *vlan_list =
		&tracker->slave_list[slave].res_list[RES_VLAN];
	काष्ठा vlan_res *res, *पंचांगp;

	list_क्रम_each_entry_safe(res, पंचांगp, vlan_list, list) अणु
		अगर (res->vlan == vlan && res->port == (u8) port) अणु
			/* vlan found. update ref count */
			++res->ref_count;
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (mlx4_grant_resource(dev, slave, RES_VLAN, 1, port))
		वापस -EINVAL;
	res = kzalloc(माप(*res), GFP_KERNEL);
	अगर (!res) अणु
		mlx4_release_resource(dev, slave, RES_VLAN, 1, port);
		वापस -ENOMEM;
	पूर्ण
	res->vlan = vlan;
	res->port = (u8) port;
	res->vlan_index = vlan_index;
	res->ref_count = 1;
	list_add_tail(&res->list,
		      &tracker->slave_list[slave].res_list[RES_VLAN]);
	वापस 0;
पूर्ण


अटल व्योम vlan_del_from_slave(काष्ठा mlx4_dev *dev, पूर्णांक slave, u16 vlan,
				पूर्णांक port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा list_head *vlan_list =
		&tracker->slave_list[slave].res_list[RES_VLAN];
	काष्ठा vlan_res *res, *पंचांगp;

	list_क्रम_each_entry_safe(res, पंचांगp, vlan_list, list) अणु
		अगर (res->vlan == vlan && res->port == (u8) port) अणु
			अगर (!--res->ref_count) अणु
				list_del(&res->list);
				mlx4_release_resource(dev, slave, RES_VLAN,
						      1, port);
				kमुक्त(res);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rem_slave_vlans(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा list_head *vlan_list =
		&tracker->slave_list[slave].res_list[RES_VLAN];
	काष्ठा vlan_res *res, *पंचांगp;
	पूर्णांक i;

	list_क्रम_each_entry_safe(res, पंचांगp, vlan_list, list) अणु
		list_del(&res->list);
		/* dereference the vlan the num बार the slave referenced it */
		क्रम (i = 0; i < res->ref_count; i++)
			__mlx4_unरेजिस्टर_vlan(dev, res->port, res->vlan);
		mlx4_release_resource(dev, slave, RES_VLAN, 1, res->port);
		kमुक्त(res);
	पूर्ण
पूर्ण

अटल पूर्णांक vlan_alloc_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			  u64 in_param, u64 *out_param, पूर्णांक in_port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_slave_state *slave_state = priv->mfunc.master.slave_state;
	पूर्णांक err;
	u16 vlan;
	पूर्णांक vlan_index;
	पूर्णांक port;

	port = !in_port ? get_param_l(out_param) : in_port;

	अगर (!port || op != RES_OP_RESERVE_AND_MAP)
		वापस -EINVAL;

	port = mlx4_slave_convert_port(
			dev, slave, port);

	अगर (port < 0)
		वापस -EINVAL;
	/* upstream kernels had NOP क्रम reg/unreg vlan. Continue this. */
	अगर (!in_port && port > 0 && port <= dev->caps.num_ports) अणु
		slave_state[slave].old_vlan_api = true;
		वापस 0;
	पूर्ण

	vlan = (u16) in_param;

	err = __mlx4_रेजिस्टर_vlan(dev, port, vlan, &vlan_index);
	अगर (!err) अणु
		set_param_l(out_param, (u32) vlan_index);
		err = vlan_add_to_slave(dev, slave, vlan, port, vlan_index);
		अगर (err)
			__mlx4_unरेजिस्टर_vlan(dev, port, vlan);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक counter_alloc_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			     u64 in_param, u64 *out_param, पूर्णांक port)
अणु
	u32 index;
	पूर्णांक err;

	अगर (op != RES_OP_RESERVE)
		वापस -EINVAL;

	err = mlx4_grant_resource(dev, slave, RES_COUNTER, 1, 0);
	अगर (err)
		वापस err;

	err = __mlx4_counter_alloc(dev, &index);
	अगर (err) अणु
		mlx4_release_resource(dev, slave, RES_COUNTER, 1, 0);
		वापस err;
	पूर्ण

	err = add_res_range(dev, slave, index, 1, RES_COUNTER, port);
	अगर (err) अणु
		__mlx4_counter_मुक्त(dev, index);
		mlx4_release_resource(dev, slave, RES_COUNTER, 1, 0);
	पूर्ण अन्यथा अणु
		set_param_l(out_param, index);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक xrcdn_alloc_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			   u64 in_param, u64 *out_param)
अणु
	u32 xrcdn;
	पूर्णांक err;

	अगर (op != RES_OP_RESERVE)
		वापस -EINVAL;

	err = __mlx4_xrcd_alloc(dev, &xrcdn);
	अगर (err)
		वापस err;

	err = add_res_range(dev, slave, xrcdn, 1, RES_XRCD, 0);
	अगर (err)
		__mlx4_xrcd_मुक्त(dev, xrcdn);
	अन्यथा
		set_param_l(out_param, xrcdn);

	वापस err;
पूर्ण

पूर्णांक mlx4_ALLOC_RES_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	पूर्णांक alop = vhcr->op_modअगरier;

	चयन (vhcr->in_modअगरier & 0xFF) अणु
	हाल RES_QP:
		err = qp_alloc_res(dev, slave, vhcr->op_modअगरier, alop,
				   vhcr->in_param, &vhcr->out_param);
		अवरोध;

	हाल RES_MTT:
		err = mtt_alloc_res(dev, slave, vhcr->op_modअगरier, alop,
				    vhcr->in_param, &vhcr->out_param);
		अवरोध;

	हाल RES_MPT:
		err = mpt_alloc_res(dev, slave, vhcr->op_modअगरier, alop,
				    vhcr->in_param, &vhcr->out_param);
		अवरोध;

	हाल RES_CQ:
		err = cq_alloc_res(dev, slave, vhcr->op_modअगरier, alop,
				   vhcr->in_param, &vhcr->out_param);
		अवरोध;

	हाल RES_SRQ:
		err = srq_alloc_res(dev, slave, vhcr->op_modअगरier, alop,
				    vhcr->in_param, &vhcr->out_param);
		अवरोध;

	हाल RES_MAC:
		err = mac_alloc_res(dev, slave, vhcr->op_modअगरier, alop,
				    vhcr->in_param, &vhcr->out_param,
				    (vhcr->in_modअगरier >> 8) & 0xFF);
		अवरोध;

	हाल RES_VLAN:
		err = vlan_alloc_res(dev, slave, vhcr->op_modअगरier, alop,
				     vhcr->in_param, &vhcr->out_param,
				     (vhcr->in_modअगरier >> 8) & 0xFF);
		अवरोध;

	हाल RES_COUNTER:
		err = counter_alloc_res(dev, slave, vhcr->op_modअगरier, alop,
					vhcr->in_param, &vhcr->out_param, 0);
		अवरोध;

	हाल RES_XRCD:
		err = xrcdn_alloc_res(dev, slave, vhcr->op_modअगरier, alop,
				      vhcr->in_param, &vhcr->out_param);
		अवरोध;

	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक qp_मुक्त_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
		       u64 in_param)
अणु
	पूर्णांक err;
	पूर्णांक count;
	पूर्णांक base;
	पूर्णांक qpn;

	चयन (op) अणु
	हाल RES_OP_RESERVE:
		base = get_param_l(&in_param) & 0x7fffff;
		count = get_param_h(&in_param);
		err = rem_res_range(dev, slave, base, count, RES_QP, 0);
		अगर (err)
			अवरोध;
		mlx4_release_resource(dev, slave, RES_QP, count, 0);
		__mlx4_qp_release_range(dev, base, count);
		अवरोध;
	हाल RES_OP_MAP_ICM:
		qpn = get_param_l(&in_param) & 0x7fffff;
		err = qp_res_start_move_to(dev, slave, qpn, RES_QP_RESERVED,
					   शून्य, 0);
		अगर (err)
			वापस err;

		अगर (!fw_reserved(dev, qpn))
			__mlx4_qp_मुक्त_icm(dev, qpn);

		res_end_move(dev, slave, RES_QP, qpn);

		अगर (valid_reserved(dev, slave, qpn))
			err = rem_res_range(dev, slave, qpn, 1, RES_QP, 0);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक mtt_मुक्त_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			u64 in_param, u64 *out_param)
अणु
	पूर्णांक err = -EINVAL;
	पूर्णांक base;
	पूर्णांक order;

	अगर (op != RES_OP_RESERVE_AND_MAP)
		वापस err;

	base = get_param_l(&in_param);
	order = get_param_h(&in_param);
	err = rem_res_range(dev, slave, base, 1, RES_MTT, order);
	अगर (!err) अणु
		mlx4_release_resource(dev, slave, RES_MTT, 1 << order, 0);
		__mlx4_मुक्त_mtt_range(dev, base, order);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक mpt_मुक्त_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			u64 in_param)
अणु
	पूर्णांक err = -EINVAL;
	पूर्णांक index;
	पूर्णांक id;
	काष्ठा res_mpt *mpt;

	चयन (op) अणु
	हाल RES_OP_RESERVE:
		index = get_param_l(&in_param);
		id = index & mpt_mask(dev);
		err = get_res(dev, slave, id, RES_MPT, &mpt);
		अगर (err)
			अवरोध;
		index = mpt->key;
		put_res(dev, slave, id, RES_MPT);

		err = rem_res_range(dev, slave, id, 1, RES_MPT, 0);
		अगर (err)
			अवरोध;
		mlx4_release_resource(dev, slave, RES_MPT, 1, 0);
		__mlx4_mpt_release(dev, index);
		अवरोध;
	हाल RES_OP_MAP_ICM:
		index = get_param_l(&in_param);
		id = index & mpt_mask(dev);
		err = mr_res_start_move_to(dev, slave, id,
					   RES_MPT_RESERVED, &mpt);
		अगर (err)
			वापस err;

		__mlx4_mpt_मुक्त_icm(dev, mpt->key);
		res_end_move(dev, slave, RES_MPT, id);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक cq_मुक्त_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
		       u64 in_param, u64 *out_param)
अणु
	पूर्णांक cqn;
	पूर्णांक err;

	चयन (op) अणु
	हाल RES_OP_RESERVE_AND_MAP:
		cqn = get_param_l(&in_param);
		err = rem_res_range(dev, slave, cqn, 1, RES_CQ, 0);
		अगर (err)
			अवरोध;

		mlx4_release_resource(dev, slave, RES_CQ, 1, 0);
		__mlx4_cq_मुक्त_icm(dev, cqn);
		अवरोध;

	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक srq_मुक्त_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			u64 in_param, u64 *out_param)
अणु
	पूर्णांक srqn;
	पूर्णांक err;

	चयन (op) अणु
	हाल RES_OP_RESERVE_AND_MAP:
		srqn = get_param_l(&in_param);
		err = rem_res_range(dev, slave, srqn, 1, RES_SRQ, 0);
		अगर (err)
			अवरोध;

		mlx4_release_resource(dev, slave, RES_SRQ, 1, 0);
		__mlx4_srq_मुक्त_icm(dev, srqn);
		अवरोध;

	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक mac_मुक्त_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			    u64 in_param, u64 *out_param, पूर्णांक in_port)
अणु
	पूर्णांक port;
	पूर्णांक err = 0;

	चयन (op) अणु
	हाल RES_OP_RESERVE_AND_MAP:
		port = !in_port ? get_param_l(out_param) : in_port;
		port = mlx4_slave_convert_port(
				dev, slave, port);

		अगर (port < 0)
			वापस -EINVAL;
		mac_del_from_slave(dev, slave, in_param, port);
		__mlx4_unरेजिस्टर_mac(dev, port, in_param);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;

पूर्ण

अटल पूर्णांक vlan_मुक्त_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			    u64 in_param, u64 *out_param, पूर्णांक port)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_slave_state *slave_state = priv->mfunc.master.slave_state;
	पूर्णांक err = 0;

	port = mlx4_slave_convert_port(
			dev, slave, port);

	अगर (port < 0)
		वापस -EINVAL;
	चयन (op) अणु
	हाल RES_OP_RESERVE_AND_MAP:
		अगर (slave_state[slave].old_vlan_api)
			वापस 0;
		अगर (!port)
			वापस -EINVAL;
		vlan_del_from_slave(dev, slave, in_param, port);
		__mlx4_unरेजिस्टर_vlan(dev, port, in_param);
		अवरोध;
	शेष:
		err = -EINVAL;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक counter_मुक्त_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			    u64 in_param, u64 *out_param)
अणु
	पूर्णांक index;
	पूर्णांक err;

	अगर (op != RES_OP_RESERVE)
		वापस -EINVAL;

	index = get_param_l(&in_param);
	अगर (index == MLX4_SINK_COUNTER_INDEX(dev))
		वापस 0;

	err = rem_res_range(dev, slave, index, 1, RES_COUNTER, 0);
	अगर (err)
		वापस err;

	__mlx4_counter_मुक्त(dev, index);
	mlx4_release_resource(dev, slave, RES_COUNTER, 1, 0);

	वापस err;
पूर्ण

अटल पूर्णांक xrcdn_मुक्त_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक op, पूर्णांक cmd,
			  u64 in_param, u64 *out_param)
अणु
	पूर्णांक xrcdn;
	पूर्णांक err;

	अगर (op != RES_OP_RESERVE)
		वापस -EINVAL;

	xrcdn = get_param_l(&in_param);
	err = rem_res_range(dev, slave, xrcdn, 1, RES_XRCD, 0);
	अगर (err)
		वापस err;

	__mlx4_xrcd_मुक्त(dev, xrcdn);

	वापस err;
पूर्ण

पूर्णांक mlx4_FREE_RES_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err = -EINVAL;
	पूर्णांक alop = vhcr->op_modअगरier;

	चयन (vhcr->in_modअगरier & 0xFF) अणु
	हाल RES_QP:
		err = qp_मुक्त_res(dev, slave, vhcr->op_modअगरier, alop,
				  vhcr->in_param);
		अवरोध;

	हाल RES_MTT:
		err = mtt_मुक्त_res(dev, slave, vhcr->op_modअगरier, alop,
				   vhcr->in_param, &vhcr->out_param);
		अवरोध;

	हाल RES_MPT:
		err = mpt_मुक्त_res(dev, slave, vhcr->op_modअगरier, alop,
				   vhcr->in_param);
		अवरोध;

	हाल RES_CQ:
		err = cq_मुक्त_res(dev, slave, vhcr->op_modअगरier, alop,
				  vhcr->in_param, &vhcr->out_param);
		अवरोध;

	हाल RES_SRQ:
		err = srq_मुक्त_res(dev, slave, vhcr->op_modअगरier, alop,
				   vhcr->in_param, &vhcr->out_param);
		अवरोध;

	हाल RES_MAC:
		err = mac_मुक्त_res(dev, slave, vhcr->op_modअगरier, alop,
				   vhcr->in_param, &vhcr->out_param,
				   (vhcr->in_modअगरier >> 8) & 0xFF);
		अवरोध;

	हाल RES_VLAN:
		err = vlan_मुक्त_res(dev, slave, vhcr->op_modअगरier, alop,
				    vhcr->in_param, &vhcr->out_param,
				    (vhcr->in_modअगरier >> 8) & 0xFF);
		अवरोध;

	हाल RES_COUNTER:
		err = counter_मुक्त_res(dev, slave, vhcr->op_modअगरier, alop,
				       vhcr->in_param, &vhcr->out_param);
		अवरोध;

	हाल RES_XRCD:
		err = xrcdn_मुक्त_res(dev, slave, vhcr->op_modअगरier, alop,
				     vhcr->in_param, &vhcr->out_param);

	शेष:
		अवरोध;
	पूर्ण
	वापस err;
पूर्ण

/* ugly but other choices are uglier */
अटल पूर्णांक mr_phys_mpt(काष्ठा mlx4_mpt_entry *mpt)
अणु
	वापस (be32_to_cpu(mpt->flags) >> 9) & 1;
पूर्ण

अटल पूर्णांक mr_get_mtt_addr(काष्ठा mlx4_mpt_entry *mpt)
अणु
	वापस (पूर्णांक)be64_to_cpu(mpt->mtt_addr) & 0xfffffff8;
पूर्ण

अटल पूर्णांक mr_get_mtt_size(काष्ठा mlx4_mpt_entry *mpt)
अणु
	वापस be32_to_cpu(mpt->mtt_sz);
पूर्ण

अटल u32 mr_get_pd(काष्ठा mlx4_mpt_entry *mpt)
अणु
	वापस be32_to_cpu(mpt->pd_flags) & 0x00ffffff;
पूर्ण

अटल पूर्णांक mr_is_fmr(काष्ठा mlx4_mpt_entry *mpt)
अणु
	वापस be32_to_cpu(mpt->pd_flags) & MLX4_MPT_PD_FLAG_FAST_REG;
पूर्ण

अटल पूर्णांक mr_is_bind_enabled(काष्ठा mlx4_mpt_entry *mpt)
अणु
	वापस be32_to_cpu(mpt->flags) & MLX4_MPT_FLAG_BIND_ENABLE;
पूर्ण

अटल पूर्णांक mr_is_region(काष्ठा mlx4_mpt_entry *mpt)
अणु
	वापस be32_to_cpu(mpt->flags) & MLX4_MPT_FLAG_REGION;
पूर्ण

अटल पूर्णांक qp_get_mtt_addr(काष्ठा mlx4_qp_context *qpc)
अणु
	वापस be32_to_cpu(qpc->mtt_base_addr_l) & 0xfffffff8;
पूर्ण

अटल पूर्णांक srq_get_mtt_addr(काष्ठा mlx4_srq_context *srqc)
अणु
	वापस be32_to_cpu(srqc->mtt_base_addr_l) & 0xfffffff8;
पूर्ण

अटल पूर्णांक qp_get_mtt_size(काष्ठा mlx4_qp_context *qpc)
अणु
	पूर्णांक page_shअगरt = (qpc->log_page_size & 0x3f) + 12;
	पूर्णांक log_sq_size = (qpc->sq_size_stride >> 3) & 0xf;
	पूर्णांक log_sq_sride = qpc->sq_size_stride & 7;
	पूर्णांक log_rq_size = (qpc->rq_size_stride >> 3) & 0xf;
	पूर्णांक log_rq_stride = qpc->rq_size_stride & 7;
	पूर्णांक srq = (be32_to_cpu(qpc->srqn) >> 24) & 1;
	पूर्णांक rss = (be32_to_cpu(qpc->flags) >> 13) & 1;
	u32 ts = (be32_to_cpu(qpc->flags) >> 16) & 0xff;
	पूर्णांक xrc = (ts == MLX4_QP_ST_XRC) ? 1 : 0;
	पूर्णांक sq_size;
	पूर्णांक rq_size;
	पूर्णांक total_pages;
	पूर्णांक total_mem;
	पूर्णांक page_offset = (be32_to_cpu(qpc->params2) >> 6) & 0x3f;
	पूर्णांक tot;

	sq_size = 1 << (log_sq_size + log_sq_sride + 4);
	rq_size = (srq|rss|xrc) ? 0 : (1 << (log_rq_size + log_rq_stride + 4));
	total_mem = sq_size + rq_size;
	tot = (total_mem + (page_offset << 6)) >> page_shअगरt;
	total_pages = !tot ? 1 : roundup_घात_of_two(tot);

	वापस total_pages;
पूर्ण

अटल पूर्णांक check_mtt_range(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक start,
			   पूर्णांक size, काष्ठा res_mtt *mtt)
अणु
	पूर्णांक res_start = mtt->com.res_id;
	पूर्णांक res_size = (1 << mtt->order);

	अगर (start < res_start || start + size > res_start + res_size)
		वापस -EPERM;
	वापस 0;
पूर्ण

पूर्णांक mlx4_SW2HW_MPT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	पूर्णांक index = vhcr->in_modअगरier;
	काष्ठा res_mtt *mtt;
	काष्ठा res_mpt *mpt = शून्य;
	पूर्णांक mtt_base = mr_get_mtt_addr(inbox->buf) / dev->caps.mtt_entry_sz;
	पूर्णांक phys;
	पूर्णांक id;
	u32 pd;
	पूर्णांक pd_slave;

	id = index & mpt_mask(dev);
	err = mr_res_start_move_to(dev, slave, id, RES_MPT_HW, &mpt);
	अगर (err)
		वापस err;

	/* Disable memory winकरोws क्रम VFs. */
	अगर (!mr_is_region(inbox->buf)) अणु
		err = -EPERM;
		जाओ ex_पात;
	पूर्ण

	/* Make sure that the PD bits related to the slave id are zeros. */
	pd = mr_get_pd(inbox->buf);
	pd_slave = (pd >> 17) & 0x7f;
	अगर (pd_slave != 0 && --pd_slave != slave) अणु
		err = -EPERM;
		जाओ ex_पात;
	पूर्ण

	अगर (mr_is_fmr(inbox->buf)) अणु
		/* FMR and Bind Enable are क्रमbidden in slave devices. */
		अगर (mr_is_bind_enabled(inbox->buf)) अणु
			err = -EPERM;
			जाओ ex_पात;
		पूर्ण
		/* FMR and Memory Winकरोws are also क्रमbidden. */
		अगर (!mr_is_region(inbox->buf)) अणु
			err = -EPERM;
			जाओ ex_पात;
		पूर्ण
	पूर्ण

	phys = mr_phys_mpt(inbox->buf);
	अगर (!phys) अणु
		err = get_res(dev, slave, mtt_base, RES_MTT, &mtt);
		अगर (err)
			जाओ ex_पात;

		err = check_mtt_range(dev, slave, mtt_base,
				      mr_get_mtt_size(inbox->buf), mtt);
		अगर (err)
			जाओ ex_put;

		mpt->mtt = mtt;
	पूर्ण

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	अगर (err)
		जाओ ex_put;

	अगर (!phys) अणु
		atomic_inc(&mtt->ref_count);
		put_res(dev, slave, mtt->com.res_id, RES_MTT);
	पूर्ण

	res_end_move(dev, slave, RES_MPT, id);
	वापस 0;

ex_put:
	अगर (!phys)
		put_res(dev, slave, mtt->com.res_id, RES_MTT);
ex_पात:
	res_पात_move(dev, slave, RES_MPT, id);

	वापस err;
पूर्ण

पूर्णांक mlx4_HW2SW_MPT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	पूर्णांक index = vhcr->in_modअगरier;
	काष्ठा res_mpt *mpt;
	पूर्णांक id;

	id = index & mpt_mask(dev);
	err = mr_res_start_move_to(dev, slave, id, RES_MPT_MAPPED, &mpt);
	अगर (err)
		वापस err;

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	अगर (err)
		जाओ ex_पात;

	अगर (mpt->mtt)
		atomic_dec(&mpt->mtt->ref_count);

	res_end_move(dev, slave, RES_MPT, id);
	वापस 0;

ex_पात:
	res_पात_move(dev, slave, RES_MPT, id);

	वापस err;
पूर्ण

पूर्णांक mlx4_QUERY_MPT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	पूर्णांक index = vhcr->in_modअगरier;
	काष्ठा res_mpt *mpt;
	पूर्णांक id;

	id = index & mpt_mask(dev);
	err = get_res(dev, slave, id, RES_MPT, &mpt);
	अगर (err)
		वापस err;

	अगर (mpt->com.from_state == RES_MPT_MAPPED) अणु
		/* In order to allow rereg in SRIOV, we need to alter the MPT entry. To करो
		 * that, the VF must पढ़ो the MPT. But since the MPT entry memory is not
		 * in the VF's भव memory space, it must use QUERY_MPT to obtain the
		 * entry contents. To guarantee that the MPT cannot be changed, the driver
		 * must perक्रमm HW2SW_MPT beक्रमe this query and वापस the MPT entry to HW
		 * ownership fofollowing the change. The change here allows the VF to
		 * perक्रमm QUERY_MPT also when the entry is in SW ownership.
		 */
		काष्ठा mlx4_mpt_entry *mpt_entry = mlx4_table_find(
					&mlx4_priv(dev)->mr_table.dmpt_table,
					mpt->key, शून्य);

		अगर (शून्य == mpt_entry || शून्य == outbox->buf) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		स_नकल(outbox->buf, mpt_entry, माप(*mpt_entry));

		err = 0;
	पूर्ण अन्यथा अगर (mpt->com.from_state == RES_MPT_HW) अणु
		err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	पूर्ण अन्यथा अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण


out:
	put_res(dev, slave, id, RES_MPT);
	वापस err;
पूर्ण

अटल पूर्णांक qp_get_rcqn(काष्ठा mlx4_qp_context *qpc)
अणु
	वापस be32_to_cpu(qpc->cqn_recv) & 0xffffff;
पूर्ण

अटल पूर्णांक qp_get_scqn(काष्ठा mlx4_qp_context *qpc)
अणु
	वापस be32_to_cpu(qpc->cqn_send) & 0xffffff;
पूर्ण

अटल u32 qp_get_srqn(काष्ठा mlx4_qp_context *qpc)
अणु
	वापस be32_to_cpu(qpc->srqn) & 0x1ffffff;
पूर्ण

अटल व्योम adjust_proxy_tun_qkey(काष्ठा mlx4_dev *dev, काष्ठा mlx4_vhcr *vhcr,
				  काष्ठा mlx4_qp_context *context)
अणु
	u32 qpn = vhcr->in_modअगरier & 0xffffff;
	u32 qkey = 0;

	अगर (mlx4_get_parav_qkey(dev, qpn, &qkey))
		वापस;

	/* adjust qkey in qp context */
	context->qkey = cpu_to_be32(qkey);
पूर्ण

अटल पूर्णांक adjust_qp_sched_queue(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				 काष्ठा mlx4_qp_context *qpc,
				 काष्ठा mlx4_cmd_mailbox *inbox);

पूर्णांक mlx4_RST2INIT_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			     काष्ठा mlx4_vhcr *vhcr,
			     काष्ठा mlx4_cmd_mailbox *inbox,
			     काष्ठा mlx4_cmd_mailbox *outbox,
			     काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	पूर्णांक qpn = vhcr->in_modअगरier & 0x7fffff;
	काष्ठा res_mtt *mtt;
	काष्ठा res_qp *qp;
	काष्ठा mlx4_qp_context *qpc = inbox->buf + 8;
	पूर्णांक mtt_base = qp_get_mtt_addr(qpc) / dev->caps.mtt_entry_sz;
	पूर्णांक mtt_size = qp_get_mtt_size(qpc);
	काष्ठा res_cq *rcq;
	काष्ठा res_cq *scq;
	पूर्णांक rcqn = qp_get_rcqn(qpc);
	पूर्णांक scqn = qp_get_scqn(qpc);
	u32 srqn = qp_get_srqn(qpc) & 0xffffff;
	पूर्णांक use_srq = (qp_get_srqn(qpc) >> 24) & 1;
	काष्ठा res_srq *srq;
	पूर्णांक local_qpn = vhcr->in_modअगरier & 0xffffff;

	err = adjust_qp_sched_queue(dev, slave, qpc, inbox);
	अगर (err)
		वापस err;

	err = qp_res_start_move_to(dev, slave, qpn, RES_QP_HW, &qp, 0);
	अगर (err)
		वापस err;
	qp->local_qpn = local_qpn;
	qp->sched_queue = 0;
	qp->param3 = 0;
	qp->vlan_control = 0;
	qp->fvl_rx = 0;
	qp->pri_path_fl = 0;
	qp->vlan_index = 0;
	qp->feup = 0;
	qp->qpc_flags = be32_to_cpu(qpc->flags);

	err = get_res(dev, slave, mtt_base, RES_MTT, &mtt);
	अगर (err)
		जाओ ex_पात;

	err = check_mtt_range(dev, slave, mtt_base, mtt_size, mtt);
	अगर (err)
		जाओ ex_put_mtt;

	err = get_res(dev, slave, rcqn, RES_CQ, &rcq);
	अगर (err)
		जाओ ex_put_mtt;

	अगर (scqn != rcqn) अणु
		err = get_res(dev, slave, scqn, RES_CQ, &scq);
		अगर (err)
			जाओ ex_put_rcq;
	पूर्ण अन्यथा
		scq = rcq;

	अगर (use_srq) अणु
		err = get_res(dev, slave, srqn, RES_SRQ, &srq);
		अगर (err)
			जाओ ex_put_scq;
	पूर्ण

	adjust_proxy_tun_qkey(dev, vhcr, qpc);
	update_pkey_index(dev, slave, inbox);
	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	अगर (err)
		जाओ ex_put_srq;
	atomic_inc(&mtt->ref_count);
	qp->mtt = mtt;
	atomic_inc(&rcq->ref_count);
	qp->rcq = rcq;
	atomic_inc(&scq->ref_count);
	qp->scq = scq;

	अगर (scqn != rcqn)
		put_res(dev, slave, scqn, RES_CQ);

	अगर (use_srq) अणु
		atomic_inc(&srq->ref_count);
		put_res(dev, slave, srqn, RES_SRQ);
		qp->srq = srq;
	पूर्ण

	/* Save param3 क्रम dynamic changes from VST back to VGT */
	qp->param3 = qpc->param3;
	put_res(dev, slave, rcqn, RES_CQ);
	put_res(dev, slave, mtt_base, RES_MTT);
	res_end_move(dev, slave, RES_QP, qpn);

	वापस 0;

ex_put_srq:
	अगर (use_srq)
		put_res(dev, slave, srqn, RES_SRQ);
ex_put_scq:
	अगर (scqn != rcqn)
		put_res(dev, slave, scqn, RES_CQ);
ex_put_rcq:
	put_res(dev, slave, rcqn, RES_CQ);
ex_put_mtt:
	put_res(dev, slave, mtt_base, RES_MTT);
ex_पात:
	res_पात_move(dev, slave, RES_QP, qpn);

	वापस err;
पूर्ण

अटल पूर्णांक eq_get_mtt_addr(काष्ठा mlx4_eq_context *eqc)
अणु
	वापस be32_to_cpu(eqc->mtt_base_addr_l) & 0xfffffff8;
पूर्ण

अटल पूर्णांक eq_get_mtt_size(काष्ठा mlx4_eq_context *eqc)
अणु
	पूर्णांक log_eq_size = eqc->log_eq_size & 0x1f;
	पूर्णांक page_shअगरt = (eqc->log_page_size & 0x3f) + 12;

	अगर (log_eq_size + 5 < page_shअगरt)
		वापस 1;

	वापस 1 << (log_eq_size + 5 - page_shअगरt);
पूर्ण

अटल पूर्णांक cq_get_mtt_addr(काष्ठा mlx4_cq_context *cqc)
अणु
	वापस be32_to_cpu(cqc->mtt_base_addr_l) & 0xfffffff8;
पूर्ण

अटल पूर्णांक cq_get_mtt_size(काष्ठा mlx4_cq_context *cqc)
अणु
	पूर्णांक log_cq_size = (be32_to_cpu(cqc->logsize_usrpage) >> 24) & 0x1f;
	पूर्णांक page_shअगरt = (cqc->log_page_size & 0x3f) + 12;

	अगर (log_cq_size + 5 < page_shअगरt)
		वापस 1;

	वापस 1 << (log_cq_size + 5 - page_shअगरt);
पूर्ण

पूर्णांक mlx4_SW2HW_EQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	पूर्णांक eqn = vhcr->in_modअगरier;
	पूर्णांक res_id = (slave << 10) | eqn;
	काष्ठा mlx4_eq_context *eqc = inbox->buf;
	पूर्णांक mtt_base = eq_get_mtt_addr(eqc) / dev->caps.mtt_entry_sz;
	पूर्णांक mtt_size = eq_get_mtt_size(eqc);
	काष्ठा res_eq *eq;
	काष्ठा res_mtt *mtt;

	err = add_res_range(dev, slave, res_id, 1, RES_EQ, 0);
	अगर (err)
		वापस err;
	err = eq_res_start_move_to(dev, slave, res_id, RES_EQ_HW, &eq);
	अगर (err)
		जाओ out_add;

	err = get_res(dev, slave, mtt_base, RES_MTT, &mtt);
	अगर (err)
		जाओ out_move;

	err = check_mtt_range(dev, slave, mtt_base, mtt_size, mtt);
	अगर (err)
		जाओ out_put;

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	अगर (err)
		जाओ out_put;

	atomic_inc(&mtt->ref_count);
	eq->mtt = mtt;
	put_res(dev, slave, mtt->com.res_id, RES_MTT);
	res_end_move(dev, slave, RES_EQ, res_id);
	वापस 0;

out_put:
	put_res(dev, slave, mtt->com.res_id, RES_MTT);
out_move:
	res_पात_move(dev, slave, RES_EQ, res_id);
out_add:
	rem_res_range(dev, slave, res_id, 1, RES_EQ, 0);
	वापस err;
पूर्ण

पूर्णांक mlx4_CONFIG_DEV_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	u8 get = vhcr->op_modअगरier;

	अगर (get != 1)
		वापस -EPERM;

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);

	वापस err;
पूर्ण

अटल पूर्णांक get_containing_mtt(काष्ठा mlx4_dev *dev, पूर्णांक slave, पूर्णांक start,
			      पूर्णांक len, काष्ठा res_mtt **res)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा res_mtt *mtt;
	पूर्णांक err = -EINVAL;

	spin_lock_irq(mlx4_tlock(dev));
	list_क्रम_each_entry(mtt, &tracker->slave_list[slave].res_list[RES_MTT],
			    com.list) अणु
		अगर (!check_mtt_range(dev, slave, start, len, mtt)) अणु
			*res = mtt;
			mtt->com.from_state = mtt->com.state;
			mtt->com.state = RES_MTT_BUSY;
			err = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	spin_unlock_irq(mlx4_tlock(dev));

	वापस err;
पूर्ण

अटल पूर्णांक verअगरy_qp_parameters(काष्ठा mlx4_dev *dev,
				काष्ठा mlx4_vhcr *vhcr,
				काष्ठा mlx4_cmd_mailbox *inbox,
				क्रमागत qp_transition transition, u8 slave)
अणु
	u32			qp_type;
	u32			qpn;
	काष्ठा mlx4_qp_context	*qp_ctx;
	क्रमागत mlx4_qp_optpar	optpar;
	पूर्णांक port;
	पूर्णांक num_gids;

	qp_ctx  = inbox->buf + 8;
	qp_type	= (be32_to_cpu(qp_ctx->flags) >> 16) & 0xff;
	optpar	= be32_to_cpu(*(__be32 *) inbox->buf);

	अगर (slave != mlx4_master_func_num(dev)) अणु
		qp_ctx->params2 &= ~cpu_to_be32(MLX4_QP_BIT_FPP);
		/* setting QP rate-limit is disallowed क्रम VFs */
		अगर (qp_ctx->rate_limit_params)
			वापस -EPERM;
	पूर्ण

	चयन (qp_type) अणु
	हाल MLX4_QP_ST_RC:
	हाल MLX4_QP_ST_XRC:
	हाल MLX4_QP_ST_UC:
		चयन (transition) अणु
		हाल QP_TRANS_INIT2RTR:
		हाल QP_TRANS_RTR2RTS:
		हाल QP_TRANS_RTS2RTS:
		हाल QP_TRANS_SQD2SQD:
		हाल QP_TRANS_SQD2RTS:
			अगर (slave != mlx4_master_func_num(dev)) अणु
				अगर (optpar & MLX4_QP_OPTPAR_PRIMARY_ADDR_PATH) अणु
					port = (qp_ctx->pri_path.sched_queue >> 6 & 1) + 1;
					अगर (dev->caps.port_mask[port] != MLX4_PORT_TYPE_IB)
						num_gids = mlx4_get_slave_num_gids(dev, slave, port);
					अन्यथा
						num_gids = 1;
					अगर (qp_ctx->pri_path.mgid_index >= num_gids)
						वापस -EINVAL;
				पूर्ण
				अगर (optpar & MLX4_QP_OPTPAR_ALT_ADDR_PATH) अणु
					port = (qp_ctx->alt_path.sched_queue >> 6 & 1) + 1;
					अगर (dev->caps.port_mask[port] != MLX4_PORT_TYPE_IB)
						num_gids = mlx4_get_slave_num_gids(dev, slave, port);
					अन्यथा
						num_gids = 1;
					अगर (qp_ctx->alt_path.mgid_index >= num_gids)
						वापस -EINVAL;
				पूर्ण
			पूर्ण
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल MLX4_QP_ST_MLX:
		qpn = vhcr->in_modअगरier & 0x7fffff;
		port = (qp_ctx->pri_path.sched_queue >> 6 & 1) + 1;
		अगर (transition == QP_TRANS_INIT2RTR &&
		    slave != mlx4_master_func_num(dev) &&
		    mlx4_is_qp_reserved(dev, qpn) &&
		    !mlx4_vf_smi_enabled(dev, slave, port)) अणु
			/* only enabled VFs may create MLX proxy QPs */
			mlx4_err(dev, "%s: unprivileged slave %d attempting to create an MLX proxy special QP on port %d\n",
				 __func__, slave, port);
			वापस -EPERM;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx4_WRITE_MTT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd)
अणु
	काष्ठा mlx4_mtt mtt;
	__be64 *page_list = inbox->buf;
	u64 *pg_list = (u64 *)page_list;
	पूर्णांक i;
	काष्ठा res_mtt *rmtt = शून्य;
	पूर्णांक start = be64_to_cpu(page_list[0]);
	पूर्णांक npages = vhcr->in_modअगरier;
	पूर्णांक err;

	err = get_containing_mtt(dev, slave, start, npages, &rmtt);
	अगर (err)
		वापस err;

	/* Call the SW implementation of ग_लिखो_mtt:
	 * - Prepare a dummy mtt काष्ठा
	 * - Translate inbox contents to simple addresses in host endianness */
	mtt.offset = 0;  /* TBD this is broken but I करोn't handle it since
			    we करोn't really use it */
	mtt.order = 0;
	mtt.page_shअगरt = 0;
	क्रम (i = 0; i < npages; ++i)
		pg_list[i + 2] = (be64_to_cpu(page_list[i + 2]) & ~1ULL);

	err = __mlx4_ग_लिखो_mtt(dev, &mtt, be64_to_cpu(page_list[0]), npages,
			       ((u64 *)page_list + 2));

	अगर (rmtt)
		put_res(dev, slave, rmtt->com.res_id, RES_MTT);

	वापस err;
पूर्ण

पूर्णांक mlx4_HW2SW_EQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक eqn = vhcr->in_modअगरier;
	पूर्णांक res_id = eqn | (slave << 10);
	काष्ठा res_eq *eq;
	पूर्णांक err;

	err = eq_res_start_move_to(dev, slave, res_id, RES_EQ_RESERVED, &eq);
	अगर (err)
		वापस err;

	err = get_res(dev, slave, eq->mtt->com.res_id, RES_MTT, शून्य);
	अगर (err)
		जाओ ex_पात;

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	अगर (err)
		जाओ ex_put;

	atomic_dec(&eq->mtt->ref_count);
	put_res(dev, slave, eq->mtt->com.res_id, RES_MTT);
	res_end_move(dev, slave, RES_EQ, res_id);
	rem_res_range(dev, slave, res_id, 1, RES_EQ, 0);

	वापस 0;

ex_put:
	put_res(dev, slave, eq->mtt->com.res_id, RES_MTT);
ex_पात:
	res_पात_move(dev, slave, RES_EQ, res_id);

	वापस err;
पूर्ण

पूर्णांक mlx4_GEN_EQE(काष्ठा mlx4_dev *dev, पूर्णांक slave, काष्ठा mlx4_eqe *eqe)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_slave_event_eq_info *event_eq;
	काष्ठा mlx4_cmd_mailbox *mailbox;
	u32 in_modअगरier = 0;
	पूर्णांक err;
	पूर्णांक res_id;
	काष्ठा res_eq *req;

	अगर (!priv->mfunc.master.slave_state)
		वापस -EINVAL;

	/* check क्रम slave valid, slave not PF, and slave active */
	अगर (slave < 0 || slave > dev->persist->num_vfs ||
	    slave == dev->caps.function ||
	    !priv->mfunc.master.slave_state[slave].active)
		वापस 0;

	event_eq = &priv->mfunc.master.slave_state[slave].event_eq[eqe->type];

	/* Create the event only अगर the slave is रेजिस्टरed */
	अगर (event_eq->eqn < 0)
		वापस 0;

	mutex_lock(&priv->mfunc.master.gen_eqe_mutex[slave]);
	res_id = (slave << 10) | event_eq->eqn;
	err = get_res(dev, slave, res_id, RES_EQ, &req);
	अगर (err)
		जाओ unlock;

	अगर (req->com.from_state != RES_EQ_HW) अणु
		err = -EINVAL;
		जाओ put;
	पूर्ण

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox)) अणु
		err = PTR_ERR(mailbox);
		जाओ put;
	पूर्ण

	अगर (eqe->type == MLX4_EVENT_TYPE_CMD) अणु
		++event_eq->token;
		eqe->event.cmd.token = cpu_to_be16(event_eq->token);
	पूर्ण

	स_नकल(mailbox->buf, (u8 *) eqe, 28);

	in_modअगरier = (slave & 0xff) | ((event_eq->eqn & 0x3ff) << 16);

	err = mlx4_cmd(dev, mailbox->dma, in_modअगरier, 0,
		       MLX4_CMD_GEN_EQE, MLX4_CMD_TIME_CLASS_B,
		       MLX4_CMD_NATIVE);

	put_res(dev, slave, res_id, RES_EQ);
	mutex_unlock(&priv->mfunc.master.gen_eqe_mutex[slave]);
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);
	वापस err;

put:
	put_res(dev, slave, res_id, RES_EQ);

unlock:
	mutex_unlock(&priv->mfunc.master.gen_eqe_mutex[slave]);
	वापस err;
पूर्ण

पूर्णांक mlx4_QUERY_EQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक eqn = vhcr->in_modअगरier;
	पूर्णांक res_id = eqn | (slave << 10);
	काष्ठा res_eq *eq;
	पूर्णांक err;

	err = get_res(dev, slave, res_id, RES_EQ, &eq);
	अगर (err)
		वापस err;

	अगर (eq->com.from_state != RES_EQ_HW) अणु
		err = -EINVAL;
		जाओ ex_put;
	पूर्ण

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);

ex_put:
	put_res(dev, slave, res_id, RES_EQ);
	वापस err;
पूर्ण

पूर्णांक mlx4_SW2HW_CQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	पूर्णांक cqn = vhcr->in_modअगरier;
	काष्ठा mlx4_cq_context *cqc = inbox->buf;
	पूर्णांक mtt_base = cq_get_mtt_addr(cqc) / dev->caps.mtt_entry_sz;
	काष्ठा res_cq *cq = शून्य;
	काष्ठा res_mtt *mtt;

	err = cq_res_start_move_to(dev, slave, cqn, RES_CQ_HW, &cq);
	अगर (err)
		वापस err;
	err = get_res(dev, slave, mtt_base, RES_MTT, &mtt);
	अगर (err)
		जाओ out_move;
	err = check_mtt_range(dev, slave, mtt_base, cq_get_mtt_size(cqc), mtt);
	अगर (err)
		जाओ out_put;
	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	अगर (err)
		जाओ out_put;
	atomic_inc(&mtt->ref_count);
	cq->mtt = mtt;
	put_res(dev, slave, mtt->com.res_id, RES_MTT);
	res_end_move(dev, slave, RES_CQ, cqn);
	वापस 0;

out_put:
	put_res(dev, slave, mtt->com.res_id, RES_MTT);
out_move:
	res_पात_move(dev, slave, RES_CQ, cqn);
	वापस err;
पूर्ण

पूर्णांक mlx4_HW2SW_CQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	पूर्णांक cqn = vhcr->in_modअगरier;
	काष्ठा res_cq *cq = शून्य;

	err = cq_res_start_move_to(dev, slave, cqn, RES_CQ_ALLOCATED, &cq);
	अगर (err)
		वापस err;
	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	अगर (err)
		जाओ out_move;
	atomic_dec(&cq->mtt->ref_count);
	res_end_move(dev, slave, RES_CQ, cqn);
	वापस 0;

out_move:
	res_पात_move(dev, slave, RES_CQ, cqn);
	वापस err;
पूर्ण

पूर्णांक mlx4_QUERY_CQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_vhcr *vhcr,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा mlx4_cmd_mailbox *outbox,
			  काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक cqn = vhcr->in_modअगरier;
	काष्ठा res_cq *cq;
	पूर्णांक err;

	err = get_res(dev, slave, cqn, RES_CQ, &cq);
	अगर (err)
		वापस err;

	अगर (cq->com.from_state != RES_CQ_HW)
		जाओ ex_put;

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
ex_put:
	put_res(dev, slave, cqn, RES_CQ);

	वापस err;
पूर्ण

अटल पूर्णांक handle_resize(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			 काष्ठा mlx4_vhcr *vhcr,
			 काष्ठा mlx4_cmd_mailbox *inbox,
			 काष्ठा mlx4_cmd_mailbox *outbox,
			 काष्ठा mlx4_cmd_info *cmd,
			 काष्ठा res_cq *cq)
अणु
	पूर्णांक err;
	काष्ठा res_mtt *orig_mtt;
	काष्ठा res_mtt *mtt;
	काष्ठा mlx4_cq_context *cqc = inbox->buf;
	पूर्णांक mtt_base = cq_get_mtt_addr(cqc) / dev->caps.mtt_entry_sz;

	err = get_res(dev, slave, cq->mtt->com.res_id, RES_MTT, &orig_mtt);
	अगर (err)
		वापस err;

	अगर (orig_mtt != cq->mtt) अणु
		err = -EINVAL;
		जाओ ex_put;
	पूर्ण

	err = get_res(dev, slave, mtt_base, RES_MTT, &mtt);
	अगर (err)
		जाओ ex_put;

	err = check_mtt_range(dev, slave, mtt_base, cq_get_mtt_size(cqc), mtt);
	अगर (err)
		जाओ ex_put1;
	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	अगर (err)
		जाओ ex_put1;
	atomic_dec(&orig_mtt->ref_count);
	put_res(dev, slave, orig_mtt->com.res_id, RES_MTT);
	atomic_inc(&mtt->ref_count);
	cq->mtt = mtt;
	put_res(dev, slave, mtt->com.res_id, RES_MTT);
	वापस 0;

ex_put1:
	put_res(dev, slave, mtt->com.res_id, RES_MTT);
ex_put:
	put_res(dev, slave, orig_mtt->com.res_id, RES_MTT);

	वापस err;

पूर्ण

पूर्णांक mlx4_MODIFY_CQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक cqn = vhcr->in_modअगरier;
	काष्ठा res_cq *cq;
	पूर्णांक err;

	err = get_res(dev, slave, cqn, RES_CQ, &cq);
	अगर (err)
		वापस err;

	अगर (cq->com.from_state != RES_CQ_HW)
		जाओ ex_put;

	अगर (vhcr->op_modअगरier == 0) अणु
		err = handle_resize(dev, slave, vhcr, inbox, outbox, cmd, cq);
		जाओ ex_put;
	पूर्ण

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
ex_put:
	put_res(dev, slave, cqn, RES_CQ);

	वापस err;
पूर्ण

अटल पूर्णांक srq_get_mtt_size(काष्ठा mlx4_srq_context *srqc)
अणु
	पूर्णांक log_srq_size = (be32_to_cpu(srqc->state_logsize_srqn) >> 24) & 0xf;
	पूर्णांक log_rq_stride = srqc->logstride & 7;
	पूर्णांक page_shअगरt = (srqc->log_page_size & 0x3f) + 12;

	अगर (log_srq_size + log_rq_stride + 4 < page_shअगरt)
		वापस 1;

	वापस 1 << (log_srq_size + log_rq_stride + 4 - page_shअगरt);
पूर्ण

पूर्णांक mlx4_SW2HW_SRQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	पूर्णांक srqn = vhcr->in_modअगरier;
	काष्ठा res_mtt *mtt;
	काष्ठा res_srq *srq = शून्य;
	काष्ठा mlx4_srq_context *srqc = inbox->buf;
	पूर्णांक mtt_base = srq_get_mtt_addr(srqc) / dev->caps.mtt_entry_sz;

	अगर (srqn != (be32_to_cpu(srqc->state_logsize_srqn) & 0xffffff))
		वापस -EINVAL;

	err = srq_res_start_move_to(dev, slave, srqn, RES_SRQ_HW, &srq);
	अगर (err)
		वापस err;
	err = get_res(dev, slave, mtt_base, RES_MTT, &mtt);
	अगर (err)
		जाओ ex_पात;
	err = check_mtt_range(dev, slave, mtt_base, srq_get_mtt_size(srqc),
			      mtt);
	अगर (err)
		जाओ ex_put_mtt;

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	अगर (err)
		जाओ ex_put_mtt;

	atomic_inc(&mtt->ref_count);
	srq->mtt = mtt;
	put_res(dev, slave, mtt->com.res_id, RES_MTT);
	res_end_move(dev, slave, RES_SRQ, srqn);
	वापस 0;

ex_put_mtt:
	put_res(dev, slave, mtt->com.res_id, RES_MTT);
ex_पात:
	res_पात_move(dev, slave, RES_SRQ, srqn);

	वापस err;
पूर्ण

पूर्णांक mlx4_HW2SW_SRQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	पूर्णांक srqn = vhcr->in_modअगरier;
	काष्ठा res_srq *srq = शून्य;

	err = srq_res_start_move_to(dev, slave, srqn, RES_SRQ_ALLOCATED, &srq);
	अगर (err)
		वापस err;
	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	अगर (err)
		जाओ ex_पात;
	atomic_dec(&srq->mtt->ref_count);
	अगर (srq->cq)
		atomic_dec(&srq->cq->ref_count);
	res_end_move(dev, slave, RES_SRQ, srqn);

	वापस 0;

ex_पात:
	res_पात_move(dev, slave, RES_SRQ, srqn);

	वापस err;
पूर्ण

पूर्णांक mlx4_QUERY_SRQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	पूर्णांक srqn = vhcr->in_modअगरier;
	काष्ठा res_srq *srq;

	err = get_res(dev, slave, srqn, RES_SRQ, &srq);
	अगर (err)
		वापस err;
	अगर (srq->com.from_state != RES_SRQ_HW) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण
	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
out:
	put_res(dev, slave, srqn, RES_SRQ);
	वापस err;
पूर्ण

पूर्णांक mlx4_ARM_SRQ_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			 काष्ठा mlx4_vhcr *vhcr,
			 काष्ठा mlx4_cmd_mailbox *inbox,
			 काष्ठा mlx4_cmd_mailbox *outbox,
			 काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	पूर्णांक srqn = vhcr->in_modअगरier;
	काष्ठा res_srq *srq;

	err = get_res(dev, slave, srqn, RES_SRQ, &srq);
	अगर (err)
		वापस err;

	अगर (srq->com.from_state != RES_SRQ_HW) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
out:
	put_res(dev, slave, srqn, RES_SRQ);
	वापस err;
पूर्ण

पूर्णांक mlx4_GEN_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			काष्ठा mlx4_vhcr *vhcr,
			काष्ठा mlx4_cmd_mailbox *inbox,
			काष्ठा mlx4_cmd_mailbox *outbox,
			काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	पूर्णांक qpn = vhcr->in_modअगरier & 0x7fffff;
	काष्ठा res_qp *qp;

	err = get_res(dev, slave, qpn, RES_QP, &qp);
	अगर (err)
		वापस err;
	अगर (qp->com.from_state != RES_QP_HW) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
out:
	put_res(dev, slave, qpn, RES_QP);
	वापस err;
पूर्ण

पूर्णांक mlx4_INIT2INIT_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			      काष्ठा mlx4_vhcr *vhcr,
			      काष्ठा mlx4_cmd_mailbox *inbox,
			      काष्ठा mlx4_cmd_mailbox *outbox,
			      काष्ठा mlx4_cmd_info *cmd)
अणु
	काष्ठा mlx4_qp_context *context = inbox->buf + 8;
	adjust_proxy_tun_qkey(dev, vhcr, context);
	update_pkey_index(dev, slave, inbox);
	वापस mlx4_GEN_QP_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
पूर्ण

अटल पूर्णांक adjust_qp_sched_queue(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				  काष्ठा mlx4_qp_context *qpc,
				  काष्ठा mlx4_cmd_mailbox *inbox)
अणु
	क्रमागत mlx4_qp_optpar optpar = be32_to_cpu(*(__be32 *)inbox->buf);
	u8 pri_sched_queue;
	पूर्णांक port = mlx4_slave_convert_port(
		   dev, slave, (qpc->pri_path.sched_queue >> 6 & 1) + 1) - 1;

	अगर (port < 0)
		वापस -EINVAL;

	pri_sched_queue = (qpc->pri_path.sched_queue & ~(1 << 6)) |
			  ((port & 1) << 6);

	अगर (optpar & (MLX4_QP_OPTPAR_PRIMARY_ADDR_PATH | MLX4_QP_OPTPAR_SCHED_QUEUE) ||
	    qpc->pri_path.sched_queue || mlx4_is_eth(dev, port + 1)) अणु
		qpc->pri_path.sched_queue = pri_sched_queue;
	पूर्ण

	अगर (optpar & MLX4_QP_OPTPAR_ALT_ADDR_PATH) अणु
		port = mlx4_slave_convert_port(
				dev, slave, (qpc->alt_path.sched_queue >> 6 & 1)
				+ 1) - 1;
		अगर (port < 0)
			वापस -EINVAL;
		qpc->alt_path.sched_queue =
			(qpc->alt_path.sched_queue & ~(1 << 6)) |
			(port & 1) << 6;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक roce_verअगरy_mac(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				काष्ठा mlx4_qp_context *qpc,
				काष्ठा mlx4_cmd_mailbox *inbox)
अणु
	u64 mac;
	पूर्णांक port;
	u32 ts = (be32_to_cpu(qpc->flags) >> 16) & 0xff;
	u8 sched = *(u8 *)(inbox->buf + 64);
	u8 smac_ix;

	port = (sched >> 6 & 1) + 1;
	अगर (mlx4_is_eth(dev, port) && (ts != MLX4_QP_ST_MLX)) अणु
		smac_ix = qpc->pri_path.grh_mylmc & 0x7f;
		अगर (mac_find_smac_ix_in_slave(dev, slave, port, smac_ix, &mac))
			वापस -ENOENT;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक mlx4_INIT2RTR_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			     काष्ठा mlx4_vhcr *vhcr,
			     काष्ठा mlx4_cmd_mailbox *inbox,
			     काष्ठा mlx4_cmd_mailbox *outbox,
			     काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	काष्ठा mlx4_qp_context *qpc = inbox->buf + 8;
	पूर्णांक qpn = vhcr->in_modअगरier & 0x7fffff;
	काष्ठा res_qp *qp;
	u8 orig_sched_queue;
	u8 orig_vlan_control = qpc->pri_path.vlan_control;
	u8 orig_fvl_rx = qpc->pri_path.fvl_rx;
	u8 orig_pri_path_fl = qpc->pri_path.fl;
	u8 orig_vlan_index = qpc->pri_path.vlan_index;
	u8 orig_feup = qpc->pri_path.feup;

	err = adjust_qp_sched_queue(dev, slave, qpc, inbox);
	अगर (err)
		वापस err;
	err = verअगरy_qp_parameters(dev, vhcr, inbox, QP_TRANS_INIT2RTR, slave);
	अगर (err)
		वापस err;

	अगर (roce_verअगरy_mac(dev, slave, qpc, inbox))
		वापस -EINVAL;

	update_pkey_index(dev, slave, inbox);
	update_gid(dev, inbox, (u8)slave);
	adjust_proxy_tun_qkey(dev, vhcr, qpc);
	orig_sched_queue = qpc->pri_path.sched_queue;

	err = get_res(dev, slave, qpn, RES_QP, &qp);
	अगर (err)
		वापस err;
	अगर (qp->com.from_state != RES_QP_HW) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	err = update_vport_qp_param(dev, inbox, slave, qpn);
	अगर (err)
		जाओ out;

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
out:
	/* अगर no error, save sched queue value passed in by VF. This is
	 * essentially the QOS value provided by the VF. This will be useful
	 * अगर we allow dynamic changes from VST back to VGT
	 */
	अगर (!err) अणु
		qp->sched_queue = orig_sched_queue;
		qp->vlan_control = orig_vlan_control;
		qp->fvl_rx	=  orig_fvl_rx;
		qp->pri_path_fl = orig_pri_path_fl;
		qp->vlan_index  = orig_vlan_index;
		qp->feup	= orig_feup;
	पूर्ण
	put_res(dev, slave, qpn, RES_QP);
	वापस err;
पूर्ण

पूर्णांक mlx4_RTR2RTS_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	काष्ठा mlx4_qp_context *context = inbox->buf + 8;

	err = adjust_qp_sched_queue(dev, slave, context, inbox);
	अगर (err)
		वापस err;
	err = verअगरy_qp_parameters(dev, vhcr, inbox, QP_TRANS_RTR2RTS, slave);
	अगर (err)
		वापस err;

	update_pkey_index(dev, slave, inbox);
	update_gid(dev, inbox, (u8)slave);
	adjust_proxy_tun_qkey(dev, vhcr, context);
	वापस mlx4_GEN_QP_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
पूर्ण

पूर्णांक mlx4_RTS2RTS_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	काष्ठा mlx4_qp_context *context = inbox->buf + 8;

	err = adjust_qp_sched_queue(dev, slave, context, inbox);
	अगर (err)
		वापस err;
	err = verअगरy_qp_parameters(dev, vhcr, inbox, QP_TRANS_RTS2RTS, slave);
	अगर (err)
		वापस err;

	update_pkey_index(dev, slave, inbox);
	update_gid(dev, inbox, (u8)slave);
	adjust_proxy_tun_qkey(dev, vhcr, context);
	वापस mlx4_GEN_QP_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
पूर्ण


पूर्णांक mlx4_SQERR2RTS_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			      काष्ठा mlx4_vhcr *vhcr,
			      काष्ठा mlx4_cmd_mailbox *inbox,
			      काष्ठा mlx4_cmd_mailbox *outbox,
			      काष्ठा mlx4_cmd_info *cmd)
अणु
	काष्ठा mlx4_qp_context *context = inbox->buf + 8;
	पूर्णांक err = adjust_qp_sched_queue(dev, slave, context, inbox);
	अगर (err)
		वापस err;
	adjust_proxy_tun_qkey(dev, vhcr, context);
	वापस mlx4_GEN_QP_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
पूर्ण

पूर्णांक mlx4_SQD2SQD_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	काष्ठा mlx4_qp_context *context = inbox->buf + 8;

	err = adjust_qp_sched_queue(dev, slave, context, inbox);
	अगर (err)
		वापस err;
	err = verअगरy_qp_parameters(dev, vhcr, inbox, QP_TRANS_SQD2SQD, slave);
	अगर (err)
		वापस err;

	adjust_proxy_tun_qkey(dev, vhcr, context);
	update_gid(dev, inbox, (u8)slave);
	update_pkey_index(dev, slave, inbox);
	वापस mlx4_GEN_QP_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
पूर्ण

पूर्णांक mlx4_SQD2RTS_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    काष्ठा mlx4_vhcr *vhcr,
			    काष्ठा mlx4_cmd_mailbox *inbox,
			    काष्ठा mlx4_cmd_mailbox *outbox,
			    काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	काष्ठा mlx4_qp_context *context = inbox->buf + 8;

	err = adjust_qp_sched_queue(dev, slave, context, inbox);
	अगर (err)
		वापस err;
	err = verअगरy_qp_parameters(dev, vhcr, inbox, QP_TRANS_SQD2RTS, slave);
	अगर (err)
		वापस err;

	adjust_proxy_tun_qkey(dev, vhcr, context);
	update_gid(dev, inbox, (u8)slave);
	update_pkey_index(dev, slave, inbox);
	वापस mlx4_GEN_QP_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
पूर्ण

पूर्णांक mlx4_2RST_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			 काष्ठा mlx4_vhcr *vhcr,
			 काष्ठा mlx4_cmd_mailbox *inbox,
			 काष्ठा mlx4_cmd_mailbox *outbox,
			 काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	पूर्णांक qpn = vhcr->in_modअगरier & 0x7fffff;
	काष्ठा res_qp *qp;

	err = qp_res_start_move_to(dev, slave, qpn, RES_QP_MAPPED, &qp, 0);
	अगर (err)
		वापस err;
	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	अगर (err)
		जाओ ex_पात;

	atomic_dec(&qp->mtt->ref_count);
	atomic_dec(&qp->rcq->ref_count);
	atomic_dec(&qp->scq->ref_count);
	अगर (qp->srq)
		atomic_dec(&qp->srq->ref_count);
	res_end_move(dev, slave, RES_QP, qpn);
	वापस 0;

ex_पात:
	res_पात_move(dev, slave, RES_QP, qpn);

	वापस err;
पूर्ण

अटल काष्ठा res_gid *find_gid(काष्ठा mlx4_dev *dev, पूर्णांक slave,
				काष्ठा res_qp *rqp, u8 *gid)
अणु
	काष्ठा res_gid *res;

	list_क्रम_each_entry(res, &rqp->mcg_list, list) अणु
		अगर (!स_भेद(res->gid, gid, 16))
			वापस res;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक add_mcg_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, काष्ठा res_qp *rqp,
		       u8 *gid, क्रमागत mlx4_protocol prot,
		       क्रमागत mlx4_steer_type steer, u64 reg_id)
अणु
	काष्ठा res_gid *res;
	पूर्णांक err;

	res = kzalloc(माप(*res), GFP_KERNEL);
	अगर (!res)
		वापस -ENOMEM;

	spin_lock_irq(&rqp->mcg_spl);
	अगर (find_gid(dev, slave, rqp, gid)) अणु
		kमुक्त(res);
		err = -EEXIST;
	पूर्ण अन्यथा अणु
		स_नकल(res->gid, gid, 16);
		res->prot = prot;
		res->steer = steer;
		res->reg_id = reg_id;
		list_add_tail(&res->list, &rqp->mcg_list);
		err = 0;
	पूर्ण
	spin_unlock_irq(&rqp->mcg_spl);

	वापस err;
पूर्ण

अटल पूर्णांक rem_mcg_res(काष्ठा mlx4_dev *dev, पूर्णांक slave, काष्ठा res_qp *rqp,
		       u8 *gid, क्रमागत mlx4_protocol prot,
		       क्रमागत mlx4_steer_type steer, u64 *reg_id)
अणु
	काष्ठा res_gid *res;
	पूर्णांक err;

	spin_lock_irq(&rqp->mcg_spl);
	res = find_gid(dev, slave, rqp, gid);
	अगर (!res || res->prot != prot || res->steer != steer)
		err = -EINVAL;
	अन्यथा अणु
		*reg_id = res->reg_id;
		list_del(&res->list);
		kमुक्त(res);
		err = 0;
	पूर्ण
	spin_unlock_irq(&rqp->mcg_spl);

	वापस err;
पूर्ण

अटल पूर्णांक qp_attach(काष्ठा mlx4_dev *dev, पूर्णांक slave, काष्ठा mlx4_qp *qp,
		     u8 gid[16], पूर्णांक block_loopback, क्रमागत mlx4_protocol prot,
		     क्रमागत mlx4_steer_type type, u64 *reg_id)
अणु
	चयन (dev->caps.steering_mode) अणु
	हाल MLX4_STEERING_MODE_DEVICE_MANAGED: अणु
		पूर्णांक port = mlx4_slave_convert_port(dev, slave, gid[5]);
		अगर (port < 0)
			वापस port;
		वापस mlx4_trans_to_dmfs_attach(dev, qp, gid, port,
						block_loopback, prot,
						reg_id);
	पूर्ण
	हाल MLX4_STEERING_MODE_B0:
		अगर (prot == MLX4_PROT_ETH) अणु
			पूर्णांक port = mlx4_slave_convert_port(dev, slave, gid[5]);
			अगर (port < 0)
				वापस port;
			gid[5] = port;
		पूर्ण
		वापस mlx4_qp_attach_common(dev, qp, gid,
					    block_loopback, prot, type);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक qp_detach(काष्ठा mlx4_dev *dev, काष्ठा mlx4_qp *qp,
		     u8 gid[16], क्रमागत mlx4_protocol prot,
		     क्रमागत mlx4_steer_type type, u64 reg_id)
अणु
	चयन (dev->caps.steering_mode) अणु
	हाल MLX4_STEERING_MODE_DEVICE_MANAGED:
		वापस mlx4_flow_detach(dev, reg_id);
	हाल MLX4_STEERING_MODE_B0:
		वापस mlx4_qp_detach_common(dev, qp, gid, prot, type);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx4_adjust_port(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			    u8 *gid, क्रमागत mlx4_protocol prot)
अणु
	पूर्णांक real_port;

	अगर (prot != MLX4_PROT_ETH)
		वापस 0;

	अगर (dev->caps.steering_mode == MLX4_STEERING_MODE_B0 ||
	    dev->caps.steering_mode == MLX4_STEERING_MODE_DEVICE_MANAGED) अणु
		real_port = mlx4_slave_convert_port(dev, slave, gid[5]);
		अगर (real_port < 0)
			वापस -EINVAL;
		gid[5] = real_port;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक mlx4_QP_ATTACH_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			       काष्ठा mlx4_vhcr *vhcr,
			       काष्ठा mlx4_cmd_mailbox *inbox,
			       काष्ठा mlx4_cmd_mailbox *outbox,
			       काष्ठा mlx4_cmd_info *cmd)
अणु
	काष्ठा mlx4_qp qp; /* dummy क्रम calling attach/detach */
	u8 *gid = inbox->buf;
	क्रमागत mlx4_protocol prot = (vhcr->in_modअगरier >> 28) & 0x7;
	पूर्णांक err;
	पूर्णांक qpn;
	काष्ठा res_qp *rqp;
	u64 reg_id = 0;
	पूर्णांक attach = vhcr->op_modअगरier;
	पूर्णांक block_loopback = vhcr->in_modअगरier >> 31;
	u8 steer_type_mask = 2;
	क्रमागत mlx4_steer_type type = (gid[7] & steer_type_mask) >> 1;

	qpn = vhcr->in_modअगरier & 0xffffff;
	err = get_res(dev, slave, qpn, RES_QP, &rqp);
	अगर (err)
		वापस err;

	qp.qpn = qpn;
	अगर (attach) अणु
		err = qp_attach(dev, slave, &qp, gid, block_loopback, prot,
				type, &reg_id);
		अगर (err) अणु
			pr_err("Fail to attach rule to qp 0x%x\n", qpn);
			जाओ ex_put;
		पूर्ण
		err = add_mcg_res(dev, slave, rqp, gid, prot, type, reg_id);
		अगर (err)
			जाओ ex_detach;
	पूर्ण अन्यथा अणु
		err = mlx4_adjust_port(dev, slave, gid, prot);
		अगर (err)
			जाओ ex_put;

		err = rem_mcg_res(dev, slave, rqp, gid, prot, type, &reg_id);
		अगर (err)
			जाओ ex_put;

		err = qp_detach(dev, &qp, gid, prot, type, reg_id);
		अगर (err)
			pr_err("Fail to detach rule from qp 0x%x reg_id = 0x%llx\n",
			       qpn, reg_id);
	पूर्ण
	put_res(dev, slave, qpn, RES_QP);
	वापस err;

ex_detach:
	qp_detach(dev, &qp, gid, prot, type, reg_id);
ex_put:
	put_res(dev, slave, qpn, RES_QP);
	वापस err;
पूर्ण

/*
 * MAC validation क्रम Flow Steering rules.
 * VF can attach rules only with a mac address which is asचिन्हित to it.
 */
अटल पूर्णांक validate_eth_header_mac(पूर्णांक slave, काष्ठा _rule_hw *eth_header,
				   काष्ठा list_head *rlist)
अणु
	काष्ठा mac_res *res, *पंचांगp;
	__be64 be_mac;

	/* make sure it isn't multicast or broadcast mac*/
	अगर (!is_multicast_ether_addr(eth_header->eth.dst_mac) &&
	    !is_broadcast_ether_addr(eth_header->eth.dst_mac)) अणु
		list_क्रम_each_entry_safe(res, पंचांगp, rlist, list) अणु
			be_mac = cpu_to_be64(res->mac << 16);
			अगर (ether_addr_equal((u8 *)&be_mac, eth_header->eth.dst_mac))
				वापस 0;
		पूर्ण
		pr_err("MAC %pM doesn't belong to VF %d, Steering rule rejected\n",
		       eth_header->eth.dst_mac, slave);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * In हाल of missing eth header, append eth header with a MAC address
 * asचिन्हित to the VF.
 */
अटल पूर्णांक add_eth_header(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  काष्ठा mlx4_cmd_mailbox *inbox,
			  काष्ठा list_head *rlist, पूर्णांक header_id)
अणु
	काष्ठा mac_res *res, *पंचांगp;
	u8 port;
	काष्ठा mlx4_net_trans_rule_hw_ctrl *ctrl;
	काष्ठा mlx4_net_trans_rule_hw_eth *eth_header;
	काष्ठा mlx4_net_trans_rule_hw_ipv4 *ip_header;
	काष्ठा mlx4_net_trans_rule_hw_tcp_udp *l4_header;
	__be64 be_mac = 0;
	__be64 mac_msk = cpu_to_be64(MLX4_MAC_MASK << 16);

	ctrl = (काष्ठा mlx4_net_trans_rule_hw_ctrl *)inbox->buf;
	port = ctrl->port;
	eth_header = (काष्ठा mlx4_net_trans_rule_hw_eth *)(ctrl + 1);

	/* Clear a space in the inbox क्रम eth header */
	चयन (header_id) अणु
	हाल MLX4_NET_TRANS_RULE_ID_IPV4:
		ip_header =
			(काष्ठा mlx4_net_trans_rule_hw_ipv4 *)(eth_header + 1);
		स_हटाओ(ip_header, eth_header,
			माप(*ip_header) + माप(*l4_header));
		अवरोध;
	हाल MLX4_NET_TRANS_RULE_ID_TCP:
	हाल MLX4_NET_TRANS_RULE_ID_UDP:
		l4_header = (काष्ठा mlx4_net_trans_rule_hw_tcp_udp *)
			    (eth_header + 1);
		स_हटाओ(l4_header, eth_header, माप(*l4_header));
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	list_क्रम_each_entry_safe(res, पंचांगp, rlist, list) अणु
		अगर (port == res->port) अणु
			be_mac = cpu_to_be64(res->mac << 16);
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!be_mac) अणु
		pr_err("Failed adding eth header to FS rule, Can't find matching MAC for port %d\n",
		       port);
		वापस -EINVAL;
	पूर्ण

	स_रखो(eth_header, 0, माप(*eth_header));
	eth_header->size = माप(*eth_header) >> 2;
	eth_header->id = cpu_to_be16(__sw_id_hw[MLX4_NET_TRANS_RULE_ID_ETH]);
	स_नकल(eth_header->dst_mac, &be_mac, ETH_ALEN);
	स_नकल(eth_header->dst_mac_msk, &mac_msk, ETH_ALEN);

	वापस 0;

पूर्ण

#घोषणा MLX4_UPD_QP_PATH_MASK_SUPPORTED      (                                \
	1ULL << MLX4_UPD_QP_PATH_MASK_MAC_INDEX                     |\
	1ULL << MLX4_UPD_QP_PATH_MASK_ETH_SRC_CHECK_MC_LB)
पूर्णांक mlx4_UPDATE_QP_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			   काष्ठा mlx4_vhcr *vhcr,
			   काष्ठा mlx4_cmd_mailbox *inbox,
			   काष्ठा mlx4_cmd_mailbox *outbox,
			   काष्ठा mlx4_cmd_info *cmd_info)
अणु
	पूर्णांक err;
	u32 qpn = vhcr->in_modअगरier & 0xffffff;
	काष्ठा res_qp *rqp;
	u64 mac;
	अचिन्हित port;
	u64 pri_addr_path_mask;
	काष्ठा mlx4_update_qp_context *cmd;
	पूर्णांक smac_index;

	cmd = (काष्ठा mlx4_update_qp_context *)inbox->buf;

	pri_addr_path_mask = be64_to_cpu(cmd->primary_addr_path_mask);
	अगर (cmd->qp_mask || cmd->secondary_addr_path_mask ||
	    (pri_addr_path_mask & ~MLX4_UPD_QP_PATH_MASK_SUPPORTED))
		वापस -EPERM;

	अगर ((pri_addr_path_mask &
	     (1ULL << MLX4_UPD_QP_PATH_MASK_ETH_SRC_CHECK_MC_LB)) &&
		!(dev->caps.flags2 &
		  MLX4_DEV_CAP_FLAG2_UPDATE_QP_SRC_CHECK_LB)) अणु
		mlx4_warn(dev, "Src check LB for slave %d isn't supported\n",
			  slave);
		वापस -EOPNOTSUPP;
	पूर्ण

	/* Just change the smac क्रम the QP */
	err = get_res(dev, slave, qpn, RES_QP, &rqp);
	अगर (err) अणु
		mlx4_err(dev, "Updating qpn 0x%x for slave %d rejected\n", qpn, slave);
		वापस err;
	पूर्ण

	port = (rqp->sched_queue >> 6 & 1) + 1;

	अगर (pri_addr_path_mask & (1ULL << MLX4_UPD_QP_PATH_MASK_MAC_INDEX)) अणु
		smac_index = cmd->qp_context.pri_path.grh_mylmc;
		err = mac_find_smac_ix_in_slave(dev, slave, port,
						smac_index, &mac);

		अगर (err) अणु
			mlx4_err(dev, "Failed to update qpn 0x%x, MAC is invalid. smac_ix: %d\n",
				 qpn, smac_index);
			जाओ err_mac;
		पूर्ण
	पूर्ण

	err = mlx4_cmd(dev, inbox->dma,
		       vhcr->in_modअगरier, 0,
		       MLX4_CMD_UPDATE_QP, MLX4_CMD_TIME_CLASS_A,
		       MLX4_CMD_NATIVE);
	अगर (err) अणु
		mlx4_err(dev, "Failed to update qpn on qpn 0x%x, command failed\n", qpn);
		जाओ err_mac;
	पूर्ण

err_mac:
	put_res(dev, slave, qpn, RES_QP);
	वापस err;
पूर्ण

अटल u32 qp_attach_mbox_size(व्योम *mbox)
अणु
	u32 size = माप(काष्ठा mlx4_net_trans_rule_hw_ctrl);
	काष्ठा _rule_hw  *rule_header;

	rule_header = (काष्ठा _rule_hw *)(mbox + size);

	जबतक (rule_header->size) अणु
		size += rule_header->size * माप(u32);
		rule_header += 1;
	पूर्ण
	वापस size;
पूर्ण

अटल पूर्णांक mlx4_करो_mirror_rule(काष्ठा mlx4_dev *dev, काष्ठा res_fs_rule *fs_rule);

पूर्णांक mlx4_QP_FLOW_STEERING_ATTACH_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
					 काष्ठा mlx4_vhcr *vhcr,
					 काष्ठा mlx4_cmd_mailbox *inbox,
					 काष्ठा mlx4_cmd_mailbox *outbox,
					 काष्ठा mlx4_cmd_info *cmd)
अणु

	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा list_head *rlist = &tracker->slave_list[slave].res_list[RES_MAC];
	पूर्णांक err;
	पूर्णांक qpn;
	काष्ठा res_qp *rqp;
	काष्ठा mlx4_net_trans_rule_hw_ctrl *ctrl;
	काष्ठा _rule_hw  *rule_header;
	पूर्णांक header_id;
	काष्ठा res_fs_rule *rrule;
	u32 mbox_size;

	अगर (dev->caps.steering_mode !=
	    MLX4_STEERING_MODE_DEVICE_MANAGED)
		वापस -EOPNOTSUPP;

	ctrl = (काष्ठा mlx4_net_trans_rule_hw_ctrl *)inbox->buf;
	err = mlx4_slave_convert_port(dev, slave, ctrl->port);
	अगर (err <= 0)
		वापस -EINVAL;
	ctrl->port = err;
	qpn = be32_to_cpu(ctrl->qpn) & 0xffffff;
	err = get_res(dev, slave, qpn, RES_QP, &rqp);
	अगर (err) अणु
		pr_err("Steering rule with qpn 0x%x rejected\n", qpn);
		वापस err;
	पूर्ण
	rule_header = (काष्ठा _rule_hw *)(ctrl + 1);
	header_id = map_hw_to_sw_id(be16_to_cpu(rule_header->id));

	अगर (header_id == MLX4_NET_TRANS_RULE_ID_ETH)
		mlx4_handle_eth_header_mcast_prio(ctrl, rule_header);

	चयन (header_id) अणु
	हाल MLX4_NET_TRANS_RULE_ID_ETH:
		अगर (validate_eth_header_mac(slave, rule_header, rlist)) अणु
			err = -EINVAL;
			जाओ err_put_qp;
		पूर्ण
		अवरोध;
	हाल MLX4_NET_TRANS_RULE_ID_IB:
		अवरोध;
	हाल MLX4_NET_TRANS_RULE_ID_IPV4:
	हाल MLX4_NET_TRANS_RULE_ID_TCP:
	हाल MLX4_NET_TRANS_RULE_ID_UDP:
		pr_warn("Can't attach FS rule without L2 headers, adding L2 header\n");
		अगर (add_eth_header(dev, slave, inbox, rlist, header_id)) अणु
			err = -EINVAL;
			जाओ err_put_qp;
		पूर्ण
		vhcr->in_modअगरier +=
			माप(काष्ठा mlx4_net_trans_rule_hw_eth) >> 2;
		अवरोध;
	शेष:
		pr_err("Corrupted mailbox\n");
		err = -EINVAL;
		जाओ err_put_qp;
	पूर्ण

	err = mlx4_cmd_imm(dev, inbox->dma, &vhcr->out_param,
			   vhcr->in_modअगरier, 0,
			   MLX4_QP_FLOW_STEERING_ATTACH, MLX4_CMD_TIME_CLASS_A,
			   MLX4_CMD_NATIVE);
	अगर (err)
		जाओ err_put_qp;


	err = add_res_range(dev, slave, vhcr->out_param, 1, RES_FS_RULE, qpn);
	अगर (err) अणु
		mlx4_err(dev, "Fail to add flow steering resources\n");
		जाओ err_detach;
	पूर्ण

	err = get_res(dev, slave, vhcr->out_param, RES_FS_RULE, &rrule);
	अगर (err)
		जाओ err_detach;

	mbox_size = qp_attach_mbox_size(inbox->buf);
	rrule->mirr_mbox = kदो_स्मृति(mbox_size, GFP_KERNEL);
	अगर (!rrule->mirr_mbox) अणु
		err = -ENOMEM;
		जाओ err_put_rule;
	पूर्ण
	rrule->mirr_mbox_size = mbox_size;
	rrule->mirr_rule_id = 0;
	स_नकल(rrule->mirr_mbox, inbox->buf, mbox_size);

	/* set dअगरferent port */
	ctrl = (काष्ठा mlx4_net_trans_rule_hw_ctrl *)rrule->mirr_mbox;
	अगर (ctrl->port == 1)
		ctrl->port = 2;
	अन्यथा
		ctrl->port = 1;

	अगर (mlx4_is_bonded(dev))
		mlx4_करो_mirror_rule(dev, rrule);

	atomic_inc(&rqp->ref_count);

err_put_rule:
	put_res(dev, slave, vhcr->out_param, RES_FS_RULE);
err_detach:
	/* detach rule on error */
	अगर (err)
		mlx4_cmd(dev, vhcr->out_param, 0, 0,
			 MLX4_QP_FLOW_STEERING_DETACH, MLX4_CMD_TIME_CLASS_A,
			 MLX4_CMD_NATIVE);
err_put_qp:
	put_res(dev, slave, qpn, RES_QP);
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_unकरो_mirror_rule(काष्ठा mlx4_dev *dev, काष्ठा res_fs_rule *fs_rule)
अणु
	पूर्णांक err;

	err = rem_res_range(dev, fs_rule->com.owner, fs_rule->com.res_id, 1, RES_FS_RULE, 0);
	अगर (err) अणु
		mlx4_err(dev, "Fail to remove flow steering resources\n");
		वापस err;
	पूर्ण

	mlx4_cmd(dev, fs_rule->com.res_id, 0, 0, MLX4_QP_FLOW_STEERING_DETACH,
		 MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
	वापस 0;
पूर्ण

पूर्णांक mlx4_QP_FLOW_STEERING_DETACH_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
					 काष्ठा mlx4_vhcr *vhcr,
					 काष्ठा mlx4_cmd_mailbox *inbox,
					 काष्ठा mlx4_cmd_mailbox *outbox,
					 काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	काष्ठा res_qp *rqp;
	काष्ठा res_fs_rule *rrule;
	u64 mirr_reg_id;
	पूर्णांक qpn;

	अगर (dev->caps.steering_mode !=
	    MLX4_STEERING_MODE_DEVICE_MANAGED)
		वापस -EOPNOTSUPP;

	err = get_res(dev, slave, vhcr->in_param, RES_FS_RULE, &rrule);
	अगर (err)
		वापस err;

	अगर (!rrule->mirr_mbox) अणु
		mlx4_err(dev, "Mirror rules cannot be removed explicitly\n");
		put_res(dev, slave, vhcr->in_param, RES_FS_RULE);
		वापस -EINVAL;
	पूर्ण
	mirr_reg_id = rrule->mirr_rule_id;
	kमुक्त(rrule->mirr_mbox);
	qpn = rrule->qpn;

	/* Release the rule क्रमm busy state beक्रमe removal */
	put_res(dev, slave, vhcr->in_param, RES_FS_RULE);
	err = get_res(dev, slave, qpn, RES_QP, &rqp);
	अगर (err)
		वापस err;

	अगर (mirr_reg_id && mlx4_is_bonded(dev)) अणु
		err = get_res(dev, slave, mirr_reg_id, RES_FS_RULE, &rrule);
		अगर (err) अणु
			mlx4_err(dev, "Fail to get resource of mirror rule\n");
		पूर्ण अन्यथा अणु
			put_res(dev, slave, mirr_reg_id, RES_FS_RULE);
			mlx4_unकरो_mirror_rule(dev, rrule);
		पूर्ण
	पूर्ण
	err = rem_res_range(dev, slave, vhcr->in_param, 1, RES_FS_RULE, 0);
	अगर (err) अणु
		mlx4_err(dev, "Fail to remove flow steering resources\n");
		जाओ out;
	पूर्ण

	err = mlx4_cmd(dev, vhcr->in_param, 0, 0,
		       MLX4_QP_FLOW_STEERING_DETACH, MLX4_CMD_TIME_CLASS_A,
		       MLX4_CMD_NATIVE);
	अगर (!err)
		atomic_dec(&rqp->ref_count);
out:
	put_res(dev, slave, qpn, RES_QP);
	वापस err;
पूर्ण

क्रमागत अणु
	BUSY_MAX_RETRIES = 10
पूर्ण;

पूर्णांक mlx4_QUERY_IF_STAT_wrapper(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			       काष्ठा mlx4_vhcr *vhcr,
			       काष्ठा mlx4_cmd_mailbox *inbox,
			       काष्ठा mlx4_cmd_mailbox *outbox,
			       काष्ठा mlx4_cmd_info *cmd)
अणु
	पूर्णांक err;
	पूर्णांक index = vhcr->in_modअगरier & 0xffff;

	err = get_res(dev, slave, index, RES_COUNTER, शून्य);
	अगर (err)
		वापस err;

	err = mlx4_DMA_wrapper(dev, slave, vhcr, inbox, outbox, cmd);
	put_res(dev, slave, index, RES_COUNTER);
	वापस err;
पूर्ण

अटल व्योम detach_qp(काष्ठा mlx4_dev *dev, पूर्णांक slave, काष्ठा res_qp *rqp)
अणु
	काष्ठा res_gid *rgid;
	काष्ठा res_gid *पंचांगp;
	काष्ठा mlx4_qp qp; /* dummy क्रम calling attach/detach */

	list_क्रम_each_entry_safe(rgid, पंचांगp, &rqp->mcg_list, list) अणु
		चयन (dev->caps.steering_mode) अणु
		हाल MLX4_STEERING_MODE_DEVICE_MANAGED:
			mlx4_flow_detach(dev, rgid->reg_id);
			अवरोध;
		हाल MLX4_STEERING_MODE_B0:
			qp.qpn = rqp->local_qpn;
			(व्योम) mlx4_qp_detach_common(dev, &qp, rgid->gid,
						     rgid->prot, rgid->steer);
			अवरोध;
		पूर्ण
		list_del(&rgid->list);
		kमुक्त(rgid);
	पूर्ण
पूर्ण

अटल पूर्णांक _move_all_busy(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			  क्रमागत mlx4_resource type, पूर्णांक prपूर्णांक)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker =
		&priv->mfunc.master.res_tracker;
	काष्ठा list_head *rlist = &tracker->slave_list[slave].res_list[type];
	काष्ठा res_common *r;
	काष्ठा res_common *पंचांगp;
	पूर्णांक busy;

	busy = 0;
	spin_lock_irq(mlx4_tlock(dev));
	list_क्रम_each_entry_safe(r, पंचांगp, rlist, list) अणु
		अगर (r->owner == slave) अणु
			अगर (!r->removing) अणु
				अगर (r->state == RES_ANY_BUSY) अणु
					अगर (prपूर्णांक)
						mlx4_dbg(dev,
							 "%s id 0x%llx is busy\n",
							  resource_str(type),
							  r->res_id);
					++busy;
				पूर्ण अन्यथा अणु
					r->from_state = r->state;
					r->state = RES_ANY_BUSY;
					r->removing = 1;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irq(mlx4_tlock(dev));

	वापस busy;
पूर्ण

अटल पूर्णांक move_all_busy(काष्ठा mlx4_dev *dev, पूर्णांक slave,
			 क्रमागत mlx4_resource type)
अणु
	अचिन्हित दीर्घ begin;
	पूर्णांक busy;

	begin = jअगरfies;
	करो अणु
		busy = _move_all_busy(dev, slave, type, 0);
		अगर (समय_after(jअगरfies, begin + 5 * HZ))
			अवरोध;
		अगर (busy)
			cond_resched();
	पूर्ण जबतक (busy);

	अगर (busy)
		busy = _move_all_busy(dev, slave, type, 1);

	वापस busy;
पूर्ण
अटल व्योम rem_slave_qps(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा list_head *qp_list =
		&tracker->slave_list[slave].res_list[RES_QP];
	काष्ठा res_qp *qp;
	काष्ठा res_qp *पंचांगp;
	पूर्णांक state;
	u64 in_param;
	पूर्णांक qpn;
	पूर्णांक err;

	err = move_all_busy(dev, slave, RES_QP);
	अगर (err)
		mlx4_warn(dev, "rem_slave_qps: Could not move all qps to busy for slave %d\n",
			  slave);

	spin_lock_irq(mlx4_tlock(dev));
	list_क्रम_each_entry_safe(qp, पंचांगp, qp_list, com.list) अणु
		spin_unlock_irq(mlx4_tlock(dev));
		अगर (qp->com.owner == slave) अणु
			qpn = qp->com.res_id;
			detach_qp(dev, slave, qp);
			state = qp->com.from_state;
			जबतक (state != 0) अणु
				चयन (state) अणु
				हाल RES_QP_RESERVED:
					spin_lock_irq(mlx4_tlock(dev));
					rb_erase(&qp->com.node,
						 &tracker->res_tree[RES_QP]);
					list_del(&qp->com.list);
					spin_unlock_irq(mlx4_tlock(dev));
					अगर (!valid_reserved(dev, slave, qpn)) अणु
						__mlx4_qp_release_range(dev, qpn, 1);
						mlx4_release_resource(dev, slave,
								      RES_QP, 1, 0);
					पूर्ण
					kमुक्त(qp);
					state = 0;
					अवरोध;
				हाल RES_QP_MAPPED:
					अगर (!valid_reserved(dev, slave, qpn))
						__mlx4_qp_मुक्त_icm(dev, qpn);
					state = RES_QP_RESERVED;
					अवरोध;
				हाल RES_QP_HW:
					in_param = slave;
					err = mlx4_cmd(dev, in_param,
						       qp->local_qpn, 2,
						       MLX4_CMD_2RST_QP,
						       MLX4_CMD_TIME_CLASS_A,
						       MLX4_CMD_NATIVE);
					अगर (err)
						mlx4_dbg(dev, "rem_slave_qps: failed to move slave %d qpn %d to reset\n",
							 slave, qp->local_qpn);
					atomic_dec(&qp->rcq->ref_count);
					atomic_dec(&qp->scq->ref_count);
					atomic_dec(&qp->mtt->ref_count);
					अगर (qp->srq)
						atomic_dec(&qp->srq->ref_count);
					state = RES_QP_MAPPED;
					अवरोध;
				शेष:
					state = 0;
				पूर्ण
			पूर्ण
		पूर्ण
		spin_lock_irq(mlx4_tlock(dev));
	पूर्ण
	spin_unlock_irq(mlx4_tlock(dev));
पूर्ण

अटल व्योम rem_slave_srqs(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा list_head *srq_list =
		&tracker->slave_list[slave].res_list[RES_SRQ];
	काष्ठा res_srq *srq;
	काष्ठा res_srq *पंचांगp;
	पूर्णांक state;
	u64 in_param;
	पूर्णांक srqn;
	पूर्णांक err;

	err = move_all_busy(dev, slave, RES_SRQ);
	अगर (err)
		mlx4_warn(dev, "rem_slave_srqs: Could not move all srqs - too busy for slave %d\n",
			  slave);

	spin_lock_irq(mlx4_tlock(dev));
	list_क्रम_each_entry_safe(srq, पंचांगp, srq_list, com.list) अणु
		spin_unlock_irq(mlx4_tlock(dev));
		अगर (srq->com.owner == slave) अणु
			srqn = srq->com.res_id;
			state = srq->com.from_state;
			जबतक (state != 0) अणु
				चयन (state) अणु
				हाल RES_SRQ_ALLOCATED:
					__mlx4_srq_मुक्त_icm(dev, srqn);
					spin_lock_irq(mlx4_tlock(dev));
					rb_erase(&srq->com.node,
						 &tracker->res_tree[RES_SRQ]);
					list_del(&srq->com.list);
					spin_unlock_irq(mlx4_tlock(dev));
					mlx4_release_resource(dev, slave,
							      RES_SRQ, 1, 0);
					kमुक्त(srq);
					state = 0;
					अवरोध;

				हाल RES_SRQ_HW:
					in_param = slave;
					err = mlx4_cmd(dev, in_param, srqn, 1,
						       MLX4_CMD_HW2SW_SRQ,
						       MLX4_CMD_TIME_CLASS_A,
						       MLX4_CMD_NATIVE);
					अगर (err)
						mlx4_dbg(dev, "rem_slave_srqs: failed to move slave %d srq %d to SW ownership\n",
							 slave, srqn);

					atomic_dec(&srq->mtt->ref_count);
					अगर (srq->cq)
						atomic_dec(&srq->cq->ref_count);
					state = RES_SRQ_ALLOCATED;
					अवरोध;

				शेष:
					state = 0;
				पूर्ण
			पूर्ण
		पूर्ण
		spin_lock_irq(mlx4_tlock(dev));
	पूर्ण
	spin_unlock_irq(mlx4_tlock(dev));
पूर्ण

अटल व्योम rem_slave_cqs(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा list_head *cq_list =
		&tracker->slave_list[slave].res_list[RES_CQ];
	काष्ठा res_cq *cq;
	काष्ठा res_cq *पंचांगp;
	पूर्णांक state;
	u64 in_param;
	पूर्णांक cqn;
	पूर्णांक err;

	err = move_all_busy(dev, slave, RES_CQ);
	अगर (err)
		mlx4_warn(dev, "rem_slave_cqs: Could not move all cqs - too busy for slave %d\n",
			  slave);

	spin_lock_irq(mlx4_tlock(dev));
	list_क्रम_each_entry_safe(cq, पंचांगp, cq_list, com.list) अणु
		spin_unlock_irq(mlx4_tlock(dev));
		अगर (cq->com.owner == slave && !atomic_पढ़ो(&cq->ref_count)) अणु
			cqn = cq->com.res_id;
			state = cq->com.from_state;
			जबतक (state != 0) अणु
				चयन (state) अणु
				हाल RES_CQ_ALLOCATED:
					__mlx4_cq_मुक्त_icm(dev, cqn);
					spin_lock_irq(mlx4_tlock(dev));
					rb_erase(&cq->com.node,
						 &tracker->res_tree[RES_CQ]);
					list_del(&cq->com.list);
					spin_unlock_irq(mlx4_tlock(dev));
					mlx4_release_resource(dev, slave,
							      RES_CQ, 1, 0);
					kमुक्त(cq);
					state = 0;
					अवरोध;

				हाल RES_CQ_HW:
					in_param = slave;
					err = mlx4_cmd(dev, in_param, cqn, 1,
						       MLX4_CMD_HW2SW_CQ,
						       MLX4_CMD_TIME_CLASS_A,
						       MLX4_CMD_NATIVE);
					अगर (err)
						mlx4_dbg(dev, "rem_slave_cqs: failed to move slave %d cq %d to SW ownership\n",
							 slave, cqn);
					atomic_dec(&cq->mtt->ref_count);
					state = RES_CQ_ALLOCATED;
					अवरोध;

				शेष:
					state = 0;
				पूर्ण
			पूर्ण
		पूर्ण
		spin_lock_irq(mlx4_tlock(dev));
	पूर्ण
	spin_unlock_irq(mlx4_tlock(dev));
पूर्ण

अटल व्योम rem_slave_mrs(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा list_head *mpt_list =
		&tracker->slave_list[slave].res_list[RES_MPT];
	काष्ठा res_mpt *mpt;
	काष्ठा res_mpt *पंचांगp;
	पूर्णांक state;
	u64 in_param;
	पूर्णांक mptn;
	पूर्णांक err;

	err = move_all_busy(dev, slave, RES_MPT);
	अगर (err)
		mlx4_warn(dev, "rem_slave_mrs: Could not move all mpts - too busy for slave %d\n",
			  slave);

	spin_lock_irq(mlx4_tlock(dev));
	list_क्रम_each_entry_safe(mpt, पंचांगp, mpt_list, com.list) अणु
		spin_unlock_irq(mlx4_tlock(dev));
		अगर (mpt->com.owner == slave) अणु
			mptn = mpt->com.res_id;
			state = mpt->com.from_state;
			जबतक (state != 0) अणु
				चयन (state) अणु
				हाल RES_MPT_RESERVED:
					__mlx4_mpt_release(dev, mpt->key);
					spin_lock_irq(mlx4_tlock(dev));
					rb_erase(&mpt->com.node,
						 &tracker->res_tree[RES_MPT]);
					list_del(&mpt->com.list);
					spin_unlock_irq(mlx4_tlock(dev));
					mlx4_release_resource(dev, slave,
							      RES_MPT, 1, 0);
					kमुक्त(mpt);
					state = 0;
					अवरोध;

				हाल RES_MPT_MAPPED:
					__mlx4_mpt_मुक्त_icm(dev, mpt->key);
					state = RES_MPT_RESERVED;
					अवरोध;

				हाल RES_MPT_HW:
					in_param = slave;
					err = mlx4_cmd(dev, in_param, mptn, 0,
						     MLX4_CMD_HW2SW_MPT,
						     MLX4_CMD_TIME_CLASS_A,
						     MLX4_CMD_NATIVE);
					अगर (err)
						mlx4_dbg(dev, "rem_slave_mrs: failed to move slave %d mpt %d to SW ownership\n",
							 slave, mptn);
					अगर (mpt->mtt)
						atomic_dec(&mpt->mtt->ref_count);
					state = RES_MPT_MAPPED;
					अवरोध;
				शेष:
					state = 0;
				पूर्ण
			पूर्ण
		पूर्ण
		spin_lock_irq(mlx4_tlock(dev));
	पूर्ण
	spin_unlock_irq(mlx4_tlock(dev));
पूर्ण

अटल व्योम rem_slave_mtts(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker =
		&priv->mfunc.master.res_tracker;
	काष्ठा list_head *mtt_list =
		&tracker->slave_list[slave].res_list[RES_MTT];
	काष्ठा res_mtt *mtt;
	काष्ठा res_mtt *पंचांगp;
	पूर्णांक state;
	पूर्णांक base;
	पूर्णांक err;

	err = move_all_busy(dev, slave, RES_MTT);
	अगर (err)
		mlx4_warn(dev, "rem_slave_mtts: Could not move all mtts  - too busy for slave %d\n",
			  slave);

	spin_lock_irq(mlx4_tlock(dev));
	list_क्रम_each_entry_safe(mtt, पंचांगp, mtt_list, com.list) अणु
		spin_unlock_irq(mlx4_tlock(dev));
		अगर (mtt->com.owner == slave) अणु
			base = mtt->com.res_id;
			state = mtt->com.from_state;
			जबतक (state != 0) अणु
				चयन (state) अणु
				हाल RES_MTT_ALLOCATED:
					__mlx4_मुक्त_mtt_range(dev, base,
							      mtt->order);
					spin_lock_irq(mlx4_tlock(dev));
					rb_erase(&mtt->com.node,
						 &tracker->res_tree[RES_MTT]);
					list_del(&mtt->com.list);
					spin_unlock_irq(mlx4_tlock(dev));
					mlx4_release_resource(dev, slave, RES_MTT,
							      1 << mtt->order, 0);
					kमुक्त(mtt);
					state = 0;
					अवरोध;

				शेष:
					state = 0;
				पूर्ण
			पूर्ण
		पूर्ण
		spin_lock_irq(mlx4_tlock(dev));
	पूर्ण
	spin_unlock_irq(mlx4_tlock(dev));
पूर्ण

अटल पूर्णांक mlx4_करो_mirror_rule(काष्ठा mlx4_dev *dev, काष्ठा res_fs_rule *fs_rule)
अणु
	काष्ठा mlx4_cmd_mailbox *mailbox;
	पूर्णांक err;
	काष्ठा res_fs_rule *mirr_rule;
	u64 reg_id;

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		वापस PTR_ERR(mailbox);

	अगर (!fs_rule->mirr_mbox) अणु
		mlx4_err(dev, "rule mirroring mailbox is null\n");
		mlx4_मुक्त_cmd_mailbox(dev, mailbox);
		वापस -EINVAL;
	पूर्ण
	स_नकल(mailbox->buf, fs_rule->mirr_mbox, fs_rule->mirr_mbox_size);
	err = mlx4_cmd_imm(dev, mailbox->dma, &reg_id, fs_rule->mirr_mbox_size >> 2, 0,
			   MLX4_QP_FLOW_STEERING_ATTACH, MLX4_CMD_TIME_CLASS_A,
			   MLX4_CMD_NATIVE);
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);

	अगर (err)
		जाओ err;

	err = add_res_range(dev, fs_rule->com.owner, reg_id, 1, RES_FS_RULE, fs_rule->qpn);
	अगर (err)
		जाओ err_detach;

	err = get_res(dev, fs_rule->com.owner, reg_id, RES_FS_RULE, &mirr_rule);
	अगर (err)
		जाओ err_rem;

	fs_rule->mirr_rule_id = reg_id;
	mirr_rule->mirr_rule_id = 0;
	mirr_rule->mirr_mbox_size = 0;
	mirr_rule->mirr_mbox = शून्य;
	put_res(dev, fs_rule->com.owner, reg_id, RES_FS_RULE);

	वापस 0;
err_rem:
	rem_res_range(dev, fs_rule->com.owner, reg_id, 1, RES_FS_RULE, 0);
err_detach:
	mlx4_cmd(dev, reg_id, 0, 0, MLX4_QP_FLOW_STEERING_DETACH,
		 MLX4_CMD_TIME_CLASS_A, MLX4_CMD_NATIVE);
err:
	वापस err;
पूर्ण

अटल पूर्णांक mlx4_mirror_fs_rules(काष्ठा mlx4_dev *dev, bool bond)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker =
		&priv->mfunc.master.res_tracker;
	काष्ठा rb_root *root = &tracker->res_tree[RES_FS_RULE];
	काष्ठा rb_node *p;
	काष्ठा res_fs_rule *fs_rule;
	पूर्णांक err = 0;
	LIST_HEAD(mirr_list);

	क्रम (p = rb_first(root); p; p = rb_next(p)) अणु
		fs_rule = rb_entry(p, काष्ठा res_fs_rule, com.node);
		अगर ((bond && fs_rule->mirr_mbox_size) ||
		    (!bond && !fs_rule->mirr_mbox_size))
			list_add_tail(&fs_rule->mirr_list, &mirr_list);
	पूर्ण

	list_क्रम_each_entry(fs_rule, &mirr_list, mirr_list) अणु
		अगर (bond)
			err += mlx4_करो_mirror_rule(dev, fs_rule);
		अन्यथा
			err += mlx4_unकरो_mirror_rule(dev, fs_rule);
	पूर्ण
	वापस err;
पूर्ण

पूर्णांक mlx4_bond_fs_rules(काष्ठा mlx4_dev *dev)
अणु
	वापस mlx4_mirror_fs_rules(dev, true);
पूर्ण

पूर्णांक mlx4_unbond_fs_rules(काष्ठा mlx4_dev *dev)
अणु
	वापस mlx4_mirror_fs_rules(dev, false);
पूर्ण

अटल व्योम rem_slave_fs_rule(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker =
		&priv->mfunc.master.res_tracker;
	काष्ठा list_head *fs_rule_list =
		&tracker->slave_list[slave].res_list[RES_FS_RULE];
	काष्ठा res_fs_rule *fs_rule;
	काष्ठा res_fs_rule *पंचांगp;
	पूर्णांक state;
	u64 base;
	पूर्णांक err;

	err = move_all_busy(dev, slave, RES_FS_RULE);
	अगर (err)
		mlx4_warn(dev, "rem_slave_fs_rule: Could not move all mtts to busy for slave %d\n",
			  slave);

	spin_lock_irq(mlx4_tlock(dev));
	list_क्रम_each_entry_safe(fs_rule, पंचांगp, fs_rule_list, com.list) अणु
		spin_unlock_irq(mlx4_tlock(dev));
		अगर (fs_rule->com.owner == slave) अणु
			base = fs_rule->com.res_id;
			state = fs_rule->com.from_state;
			जबतक (state != 0) अणु
				चयन (state) अणु
				हाल RES_FS_RULE_ALLOCATED:
					/* detach rule */
					err = mlx4_cmd(dev, base, 0, 0,
						       MLX4_QP_FLOW_STEERING_DETACH,
						       MLX4_CMD_TIME_CLASS_A,
						       MLX4_CMD_NATIVE);

					spin_lock_irq(mlx4_tlock(dev));
					rb_erase(&fs_rule->com.node,
						 &tracker->res_tree[RES_FS_RULE]);
					list_del(&fs_rule->com.list);
					spin_unlock_irq(mlx4_tlock(dev));
					kमुक्त(fs_rule->mirr_mbox);
					kमुक्त(fs_rule);
					state = 0;
					अवरोध;

				शेष:
					state = 0;
				पूर्ण
			पूर्ण
		पूर्ण
		spin_lock_irq(mlx4_tlock(dev));
	पूर्ण
	spin_unlock_irq(mlx4_tlock(dev));
पूर्ण

अटल व्योम rem_slave_eqs(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा list_head *eq_list =
		&tracker->slave_list[slave].res_list[RES_EQ];
	काष्ठा res_eq *eq;
	काष्ठा res_eq *पंचांगp;
	पूर्णांक err;
	पूर्णांक state;
	पूर्णांक eqn;

	err = move_all_busy(dev, slave, RES_EQ);
	अगर (err)
		mlx4_warn(dev, "rem_slave_eqs: Could not move all eqs - too busy for slave %d\n",
			  slave);

	spin_lock_irq(mlx4_tlock(dev));
	list_क्रम_each_entry_safe(eq, पंचांगp, eq_list, com.list) अणु
		spin_unlock_irq(mlx4_tlock(dev));
		अगर (eq->com.owner == slave) अणु
			eqn = eq->com.res_id;
			state = eq->com.from_state;
			जबतक (state != 0) अणु
				चयन (state) अणु
				हाल RES_EQ_RESERVED:
					spin_lock_irq(mlx4_tlock(dev));
					rb_erase(&eq->com.node,
						 &tracker->res_tree[RES_EQ]);
					list_del(&eq->com.list);
					spin_unlock_irq(mlx4_tlock(dev));
					kमुक्त(eq);
					state = 0;
					अवरोध;

				हाल RES_EQ_HW:
					err = mlx4_cmd(dev, slave, eqn & 0x3ff,
						       1, MLX4_CMD_HW2SW_EQ,
						       MLX4_CMD_TIME_CLASS_A,
						       MLX4_CMD_NATIVE);
					अगर (err)
						mlx4_dbg(dev, "rem_slave_eqs: failed to move slave %d eqs %d to SW ownership\n",
							 slave, eqn & 0x3ff);
					atomic_dec(&eq->mtt->ref_count);
					state = RES_EQ_RESERVED;
					अवरोध;

				शेष:
					state = 0;
				पूर्ण
			पूर्ण
		पूर्ण
		spin_lock_irq(mlx4_tlock(dev));
	पूर्ण
	spin_unlock_irq(mlx4_tlock(dev));
पूर्ण

अटल व्योम rem_slave_counters(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा list_head *counter_list =
		&tracker->slave_list[slave].res_list[RES_COUNTER];
	काष्ठा res_counter *counter;
	काष्ठा res_counter *पंचांगp;
	पूर्णांक err;
	पूर्णांक *counters_arr = शून्य;
	पूर्णांक i, j;

	err = move_all_busy(dev, slave, RES_COUNTER);
	अगर (err)
		mlx4_warn(dev, "rem_slave_counters: Could not move all counters - too busy for slave %d\n",
			  slave);

	counters_arr = kदो_स्मृति_array(dev->caps.max_counters,
				     माप(*counters_arr), GFP_KERNEL);
	अगर (!counters_arr)
		वापस;

	करो अणु
		i = 0;
		j = 0;
		spin_lock_irq(mlx4_tlock(dev));
		list_क्रम_each_entry_safe(counter, पंचांगp, counter_list, com.list) अणु
			अगर (counter->com.owner == slave) अणु
				counters_arr[i++] = counter->com.res_id;
				rb_erase(&counter->com.node,
					 &tracker->res_tree[RES_COUNTER]);
				list_del(&counter->com.list);
				kमुक्त(counter);
			पूर्ण
		पूर्ण
		spin_unlock_irq(mlx4_tlock(dev));

		जबतक (j < i) अणु
			__mlx4_counter_मुक्त(dev, counters_arr[j++]);
			mlx4_release_resource(dev, slave, RES_COUNTER, 1, 0);
		पूर्ण
	पूर्ण जबतक (i);

	kमुक्त(counters_arr);
पूर्ण

अटल व्योम rem_slave_xrcdns(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	काष्ठा mlx4_resource_tracker *tracker = &priv->mfunc.master.res_tracker;
	काष्ठा list_head *xrcdn_list =
		&tracker->slave_list[slave].res_list[RES_XRCD];
	काष्ठा res_xrcdn *xrcd;
	काष्ठा res_xrcdn *पंचांगp;
	पूर्णांक err;
	पूर्णांक xrcdn;

	err = move_all_busy(dev, slave, RES_XRCD);
	अगर (err)
		mlx4_warn(dev, "rem_slave_xrcdns: Could not move all xrcdns - too busy for slave %d\n",
			  slave);

	spin_lock_irq(mlx4_tlock(dev));
	list_क्रम_each_entry_safe(xrcd, पंचांगp, xrcdn_list, com.list) अणु
		अगर (xrcd->com.owner == slave) अणु
			xrcdn = xrcd->com.res_id;
			rb_erase(&xrcd->com.node, &tracker->res_tree[RES_XRCD]);
			list_del(&xrcd->com.list);
			kमुक्त(xrcd);
			__mlx4_xrcd_मुक्त(dev, xrcdn);
		पूर्ण
	पूर्ण
	spin_unlock_irq(mlx4_tlock(dev));
पूर्ण

व्योम mlx4_delete_all_resources_क्रम_slave(काष्ठा mlx4_dev *dev, पूर्णांक slave)
अणु
	काष्ठा mlx4_priv *priv = mlx4_priv(dev);
	mlx4_reset_roce_gids(dev, slave);
	mutex_lock(&priv->mfunc.master.res_tracker.slave_list[slave].mutex);
	rem_slave_vlans(dev, slave);
	rem_slave_macs(dev, slave);
	rem_slave_fs_rule(dev, slave);
	rem_slave_qps(dev, slave);
	rem_slave_srqs(dev, slave);
	rem_slave_cqs(dev, slave);
	rem_slave_mrs(dev, slave);
	rem_slave_eqs(dev, slave);
	rem_slave_mtts(dev, slave);
	rem_slave_counters(dev, slave);
	rem_slave_xrcdns(dev, slave);
	mutex_unlock(&priv->mfunc.master.res_tracker.slave_list[slave].mutex);
पूर्ण

अटल व्योम update_qos_vpp(काष्ठा mlx4_update_qp_context *ctx,
			   काष्ठा mlx4_vf_immed_vlan_work *work)
अणु
	ctx->qp_mask |= cpu_to_be64(1ULL << MLX4_UPD_QP_MASK_QOS_VPP);
	ctx->qp_context.qos_vport = work->qos_vport;
पूर्ण

व्योम mlx4_vf_immed_vlan_work_handler(काष्ठा work_काष्ठा *_work)
अणु
	काष्ठा mlx4_vf_immed_vlan_work *work =
		container_of(_work, काष्ठा mlx4_vf_immed_vlan_work, work);
	काष्ठा mlx4_cmd_mailbox *mailbox;
	काष्ठा mlx4_update_qp_context *upd_context;
	काष्ठा mlx4_dev *dev = &work->priv->dev;
	काष्ठा mlx4_resource_tracker *tracker =
		&work->priv->mfunc.master.res_tracker;
	काष्ठा list_head *qp_list =
		&tracker->slave_list[work->slave].res_list[RES_QP];
	काष्ठा res_qp *qp;
	काष्ठा res_qp *पंचांगp;
	u64 qp_path_mask_vlan_ctrl =
		       ((1ULL << MLX4_UPD_QP_PATH_MASK_ETH_TX_BLOCK_UNTAGGED) |
		       (1ULL << MLX4_UPD_QP_PATH_MASK_ETH_TX_BLOCK_1P) |
		       (1ULL << MLX4_UPD_QP_PATH_MASK_ETH_TX_BLOCK_TAGGED) |
		       (1ULL << MLX4_UPD_QP_PATH_MASK_ETH_RX_BLOCK_UNTAGGED) |
		       (1ULL << MLX4_UPD_QP_PATH_MASK_ETH_RX_BLOCK_1P) |
		       (1ULL << MLX4_UPD_QP_PATH_MASK_ETH_RX_BLOCK_TAGGED));

	u64 qp_path_mask = ((1ULL << MLX4_UPD_QP_PATH_MASK_VLAN_INDEX) |
		       (1ULL << MLX4_UPD_QP_PATH_MASK_FVL) |
		       (1ULL << MLX4_UPD_QP_PATH_MASK_CV) |
		       (1ULL << MLX4_UPD_QP_PATH_MASK_SV) |
		       (1ULL << MLX4_UPD_QP_PATH_MASK_ETH_HIDE_CQE_VLAN) |
		       (1ULL << MLX4_UPD_QP_PATH_MASK_FEUP) |
		       (1ULL << MLX4_UPD_QP_PATH_MASK_FVL_RX) |
		       (1ULL << MLX4_UPD_QP_PATH_MASK_SCHED_QUEUE));

	पूर्णांक err;
	पूर्णांक port, errors = 0;
	u8 vlan_control;

	अगर (mlx4_is_slave(dev)) अणु
		mlx4_warn(dev, "Trying to update-qp in slave %d\n",
			  work->slave);
		जाओ out;
	पूर्ण

	mailbox = mlx4_alloc_cmd_mailbox(dev);
	अगर (IS_ERR(mailbox))
		जाओ out;
	अगर (work->flags & MLX4_VF_IMMED_VLAN_FLAG_LINK_DISABLE) /* block all */
		vlan_control = MLX4_VLAN_CTRL_ETH_TX_BLOCK_TAGGED |
			MLX4_VLAN_CTRL_ETH_TX_BLOCK_PRIO_TAGGED |
			MLX4_VLAN_CTRL_ETH_TX_BLOCK_UNTAGGED |
			MLX4_VLAN_CTRL_ETH_RX_BLOCK_PRIO_TAGGED |
			MLX4_VLAN_CTRL_ETH_RX_BLOCK_UNTAGGED |
			MLX4_VLAN_CTRL_ETH_RX_BLOCK_TAGGED;
	अन्यथा अगर (!work->vlan_id)
		vlan_control = MLX4_VLAN_CTRL_ETH_TX_BLOCK_TAGGED |
			MLX4_VLAN_CTRL_ETH_RX_BLOCK_TAGGED;
	अन्यथा अगर (work->vlan_proto == htons(ETH_P_8021AD))
		vlan_control = MLX4_VLAN_CTRL_ETH_TX_BLOCK_PRIO_TAGGED |
			MLX4_VLAN_CTRL_ETH_TX_BLOCK_TAGGED |
			MLX4_VLAN_CTRL_ETH_RX_BLOCK_PRIO_TAGGED |
			MLX4_VLAN_CTRL_ETH_RX_BLOCK_UNTAGGED;
	अन्यथा  /* vst 802.1Q */
		vlan_control = MLX4_VLAN_CTRL_ETH_TX_BLOCK_TAGGED |
			MLX4_VLAN_CTRL_ETH_RX_BLOCK_PRIO_TAGGED |
			MLX4_VLAN_CTRL_ETH_RX_BLOCK_UNTAGGED;

	upd_context = mailbox->buf;
	upd_context->qp_mask = cpu_to_be64(1ULL << MLX4_UPD_QP_MASK_VSD);

	spin_lock_irq(mlx4_tlock(dev));
	list_क्रम_each_entry_safe(qp, पंचांगp, qp_list, com.list) अणु
		spin_unlock_irq(mlx4_tlock(dev));
		अगर (qp->com.owner == work->slave) अणु
			अगर (qp->com.from_state != RES_QP_HW ||
			    !qp->sched_queue ||  /* no INIT2RTR trans yet */
			    mlx4_is_qp_reserved(dev, qp->local_qpn) ||
			    qp->qpc_flags & (1 << MLX4_RSS_QPC_FLAG_OFFSET)) अणु
				spin_lock_irq(mlx4_tlock(dev));
				जारी;
			पूर्ण
			port = (qp->sched_queue >> 6 & 1) + 1;
			अगर (port != work->port) अणु
				spin_lock_irq(mlx4_tlock(dev));
				जारी;
			पूर्ण
			अगर (MLX4_QP_ST_RC == ((qp->qpc_flags >> 16) & 0xff))
				upd_context->primary_addr_path_mask = cpu_to_be64(qp_path_mask);
			अन्यथा
				upd_context->primary_addr_path_mask =
					cpu_to_be64(qp_path_mask | qp_path_mask_vlan_ctrl);
			अगर (work->vlan_id == MLX4_VGT) अणु
				upd_context->qp_context.param3 = qp->param3;
				upd_context->qp_context.pri_path.vlan_control = qp->vlan_control;
				upd_context->qp_context.pri_path.fvl_rx = qp->fvl_rx;
				upd_context->qp_context.pri_path.vlan_index = qp->vlan_index;
				upd_context->qp_context.pri_path.fl = qp->pri_path_fl;
				upd_context->qp_context.pri_path.feup = qp->feup;
				upd_context->qp_context.pri_path.sched_queue =
					qp->sched_queue;
			पूर्ण अन्यथा अणु
				upd_context->qp_context.param3 = qp->param3 & ~cpu_to_be32(MLX4_STRIP_VLAN);
				upd_context->qp_context.pri_path.vlan_control = vlan_control;
				upd_context->qp_context.pri_path.vlan_index = work->vlan_ix;
				upd_context->qp_context.pri_path.fvl_rx =
					qp->fvl_rx | MLX4_FVL_RX_FORCE_ETH_VLAN;
				upd_context->qp_context.pri_path.fl =
					qp->pri_path_fl | MLX4_FL_ETH_HIDE_CQE_VLAN;
				अगर (work->vlan_proto == htons(ETH_P_8021AD))
					upd_context->qp_context.pri_path.fl |= MLX4_FL_SV;
				अन्यथा
					upd_context->qp_context.pri_path.fl |= MLX4_FL_CV;
				upd_context->qp_context.pri_path.feup =
					qp->feup | MLX4_FEUP_FORCE_ETH_UP | MLX4_FVL_FORCE_ETH_VLAN;
				upd_context->qp_context.pri_path.sched_queue =
					qp->sched_queue & 0xC7;
				upd_context->qp_context.pri_path.sched_queue |=
					((work->qos & 0x7) << 3);

				अगर (dev->caps.flags2 &
				    MLX4_DEV_CAP_FLAG2_QOS_VPP)
					update_qos_vpp(upd_context, work);
			पूर्ण

			err = mlx4_cmd(dev, mailbox->dma,
				       qp->local_qpn & 0xffffff,
				       0, MLX4_CMD_UPDATE_QP,
				       MLX4_CMD_TIME_CLASS_C, MLX4_CMD_NATIVE);
			अगर (err) अणु
				mlx4_info(dev, "UPDATE_QP failed for slave %d, port %d, qpn %d (%d)\n",
					  work->slave, port, qp->local_qpn, err);
				errors++;
			पूर्ण
		पूर्ण
		spin_lock_irq(mlx4_tlock(dev));
	पूर्ण
	spin_unlock_irq(mlx4_tlock(dev));
	mlx4_मुक्त_cmd_mailbox(dev, mailbox);

	अगर (errors)
		mlx4_err(dev, "%d UPDATE_QP failures for slave %d, port %d\n",
			 errors, work->slave, work->port);

	/* unरेजिस्टर previous vlan_id अगर needed and we had no errors
	 * जबतक updating the QPs
	 */
	अगर (work->flags & MLX4_VF_IMMED_VLAN_FLAG_VLAN && !errors &&
	    NO_INDX != work->orig_vlan_ix)
		__mlx4_unरेजिस्टर_vlan(&work->priv->dev, work->port,
				       work->orig_vlan_id);
out:
	kमुक्त(work);
	वापस;
पूर्ण
