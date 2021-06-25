<शैली गुरु>
/*
 * Copyright (c) 2007 Cisco Systems, Inc. All rights reserved.
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

#समावेश <rdma/ib_mad.h>
#समावेश <rdma/ib_smi.h>
#समावेश <rdma/ib_sa.h>
#समावेश <rdma/ib_cache.h>

#समावेश <linux/अक्रमom.h>
#समावेश <linux/mlx4/cmd.h>
#समावेश <linux/gfp.h>
#समावेश <rdma/ib_pma.h>
#समावेश <linux/ip.h>
#समावेश <net/ipv6.h>

#समावेश <linux/mlx4/driver.h>
#समावेश "mlx4_ib.h"

क्रमागत अणु
	MLX4_IB_VENDOR_CLASS1 = 0x9,
	MLX4_IB_VENDOR_CLASS2 = 0xa
पूर्ण;

#घोषणा MLX4_TUN_SEND_WRID_SHIFT 34
#घोषणा MLX4_TUN_QPN_SHIFT 32
#घोषणा MLX4_TUN_WRID_RECV (((u64) 1) << MLX4_TUN_SEND_WRID_SHIFT)
#घोषणा MLX4_TUN_SET_WRID_QPN(a) (((u64) ((a) & 0x3)) << MLX4_TUN_QPN_SHIFT)

#घोषणा MLX4_TUN_IS_RECV(a)  (((a) >>  MLX4_TUN_SEND_WRID_SHIFT) & 0x1)
#घोषणा MLX4_TUN_WRID_QPN(a) (((a) >> MLX4_TUN_QPN_SHIFT) & 0x3)

 /* Port mgmt change event handling */

#घोषणा GET_BLK_PTR_FROM_EQE(eqe) be32_to_cpu(eqe->event.port_mgmt_change.params.tbl_change_info.block_ptr)
#घोषणा GET_MASK_FROM_EQE(eqe) be32_to_cpu(eqe->event.port_mgmt_change.params.tbl_change_info.tbl_entries_mask)
#घोषणा NUM_IDX_IN_PKEY_TBL_BLK 32
#घोषणा GUID_TBL_ENTRY_SIZE 8	   /* size in bytes */
#घोषणा GUID_TBL_BLK_NUM_ENTRIES 8
#घोषणा GUID_TBL_BLK_SIZE (GUID_TBL_ENTRY_SIZE * GUID_TBL_BLK_NUM_ENTRIES)

काष्ठा mlx4_mad_rcv_buf अणु
	काष्ठा ib_grh grh;
	u8 payload[256];
पूर्ण __packed;

काष्ठा mlx4_mad_snd_buf अणु
	u8 payload[256];
पूर्ण __packed;

काष्ठा mlx4_tunnel_mad अणु
	काष्ठा ib_grh grh;
	काष्ठा mlx4_ib_tunnel_header hdr;
	काष्ठा ib_mad mad;
पूर्ण __packed;

काष्ठा mlx4_rcv_tunnel_mad अणु
	काष्ठा mlx4_rcv_tunnel_hdr hdr;
	काष्ठा ib_grh grh;
	काष्ठा ib_mad mad;
पूर्ण __packed;

अटल व्योम handle_client_rereg_event(काष्ठा mlx4_ib_dev *dev, u32 port_num);
अटल व्योम handle_lid_change_event(काष्ठा mlx4_ib_dev *dev, u32 port_num);
अटल व्योम __propagate_pkey_ev(काष्ठा mlx4_ib_dev *dev, पूर्णांक port_num,
				पूर्णांक block, u32 change_biपंचांगap);

__be64 mlx4_ib_gen_node_guid(व्योम)
अणु
#घोषणा NODE_GUID_HI	((u64) (((u64)IB_OPENIB_OUI) << 40))
	वापस cpu_to_be64(NODE_GUID_HI | pअक्रमom_u32());
पूर्ण

__be64 mlx4_ib_get_new_demux_tid(काष्ठा mlx4_ib_demux_ctx *ctx)
अणु
	वापस cpu_to_be64(atomic_inc_वापस(&ctx->tid)) |
		cpu_to_be64(0xff00000000000000LL);
पूर्ण

पूर्णांक mlx4_MAD_IFC(काष्ठा mlx4_ib_dev *dev, पूर्णांक mad_अगरc_flags,
		 पूर्णांक port, स्थिर काष्ठा ib_wc *in_wc,
		 स्थिर काष्ठा ib_grh *in_grh,
		 स्थिर व्योम *in_mad, व्योम *response_mad)
अणु
	काष्ठा mlx4_cmd_mailbox *inmailbox, *ouपंचांगailbox;
	व्योम *inbox;
	पूर्णांक err;
	u32 in_modअगरier = port;
	u8 op_modअगरier = 0;

	inmailbox = mlx4_alloc_cmd_mailbox(dev->dev);
	अगर (IS_ERR(inmailbox))
		वापस PTR_ERR(inmailbox);
	inbox = inmailbox->buf;

	ouपंचांगailbox = mlx4_alloc_cmd_mailbox(dev->dev);
	अगर (IS_ERR(ouपंचांगailbox)) अणु
		mlx4_मुक्त_cmd_mailbox(dev->dev, inmailbox);
		वापस PTR_ERR(ouपंचांगailbox);
	पूर्ण

	स_नकल(inbox, in_mad, 256);

	/*
	 * Key check traps can't be generated unless we have in_wc to
	 * tell us where to send the trap.
	 */
	अगर ((mad_अगरc_flags & MLX4_MAD_IFC_IGNORE_MKEY) || !in_wc)
		op_modअगरier |= 0x1;
	अगर ((mad_अगरc_flags & MLX4_MAD_IFC_IGNORE_BKEY) || !in_wc)
		op_modअगरier |= 0x2;
	अगर (mlx4_is_mfunc(dev->dev) &&
	    (mad_अगरc_flags & MLX4_MAD_IFC_NET_VIEW || in_wc))
		op_modअगरier |= 0x8;

	अगर (in_wc) अणु
		काष्ठा अणु
			__be32		my_qpn;
			u32		reserved1;
			__be32		rqpn;
			u8		sl;
			u8		g_path;
			u16		reserved2[2];
			__be16		pkey;
			u32		reserved3[11];
			u8		grh[40];
		पूर्ण *ext_info;

		स_रखो(inbox + 256, 0, 256);
		ext_info = inbox + 256;

		ext_info->my_qpn = cpu_to_be32(in_wc->qp->qp_num);
		ext_info->rqpn   = cpu_to_be32(in_wc->src_qp);
		ext_info->sl     = in_wc->sl << 4;
		ext_info->g_path = in_wc->dlid_path_bits |
			(in_wc->wc_flags & IB_WC_GRH ? 0x80 : 0);
		ext_info->pkey   = cpu_to_be16(in_wc->pkey_index);

		अगर (in_grh)
			स_नकल(ext_info->grh, in_grh, 40);

		op_modअगरier |= 0x4;

		in_modअगरier |= ib_lid_cpu16(in_wc->slid) << 16;
	पूर्ण

	err = mlx4_cmd_box(dev->dev, inmailbox->dma, ouपंचांगailbox->dma, in_modअगरier,
			   mlx4_is_master(dev->dev) ? (op_modअगरier & ~0x8) : op_modअगरier,
			   MLX4_CMD_MAD_IFC, MLX4_CMD_TIME_CLASS_C,
			   (op_modअगरier & 0x8) ? MLX4_CMD_NATIVE : MLX4_CMD_WRAPPED);

	अगर (!err)
		स_नकल(response_mad, ouपंचांगailbox->buf, 256);

	mlx4_मुक्त_cmd_mailbox(dev->dev, inmailbox);
	mlx4_मुक्त_cmd_mailbox(dev->dev, ouपंचांगailbox);

	वापस err;
पूर्ण

अटल व्योम update_sm_ah(काष्ठा mlx4_ib_dev *dev, u32 port_num, u16 lid, u8 sl)
अणु
	काष्ठा ib_ah *new_ah;
	काष्ठा rdma_ah_attr ah_attr;
	अचिन्हित दीर्घ flags;

	अगर (!dev->send_agent[port_num - 1][0])
		वापस;

	स_रखो(&ah_attr, 0, माप ah_attr);
	ah_attr.type = rdma_ah_find_type(&dev->ib_dev, port_num);
	rdma_ah_set_dlid(&ah_attr, lid);
	rdma_ah_set_sl(&ah_attr, sl);
	rdma_ah_set_port_num(&ah_attr, port_num);

	new_ah = rdma_create_ah(dev->send_agent[port_num - 1][0]->qp->pd,
				&ah_attr, 0);
	अगर (IS_ERR(new_ah))
		वापस;

	spin_lock_irqsave(&dev->sm_lock, flags);
	अगर (dev->sm_ah[port_num - 1])
		rdma_destroy_ah(dev->sm_ah[port_num - 1], 0);
	dev->sm_ah[port_num - 1] = new_ah;
	spin_unlock_irqrestore(&dev->sm_lock, flags);
पूर्ण

/*
 * Snoop SM MADs क्रम port info, GUID info, and  P_Key table sets, so we can
 * synthesize LID change, Client-Rereg, GID change, and P_Key change events.
 */
अटल व्योम smp_snoop(काष्ठा ib_device *ibdev, u32 port_num,
		      स्थिर काष्ठा ib_mad *mad, u16 prev_lid)
अणु
	काष्ठा ib_port_info *pinfo;
	u16 lid;
	__be16 *base;
	u32 bn, pkey_change_biपंचांगap;
	पूर्णांक i;


	काष्ठा mlx4_ib_dev *dev = to_mdev(ibdev);
	अगर ((mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_LID_ROUTED ||
	     mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE) &&
	    mad->mad_hdr.method == IB_MGMT_METHOD_SET)
		चयन (mad->mad_hdr.attr_id) अणु
		हाल IB_SMP_ATTR_PORT_INFO:
			अगर (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_PORT_MNG_CHG_EV)
				वापस;
			pinfo = (काष्ठा ib_port_info *) ((काष्ठा ib_smp *) mad)->data;
			lid = be16_to_cpu(pinfo->lid);

			update_sm_ah(dev, port_num,
				     be16_to_cpu(pinfo->sm_lid),
				     pinfo->neighbormtu_mastersmsl & 0xf);

			अगर (pinfo->clientrereg_resv_subnetto & 0x80)
				handle_client_rereg_event(dev, port_num);

			अगर (prev_lid != lid)
				handle_lid_change_event(dev, port_num);
			अवरोध;

		हाल IB_SMP_ATTR_PKEY_TABLE:
			अगर (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_PORT_MNG_CHG_EV)
				वापस;
			अगर (!mlx4_is_mfunc(dev->dev)) अणु
				mlx4_ib_dispatch_event(dev, port_num,
						       IB_EVENT_PKEY_CHANGE);
				अवरोध;
			पूर्ण

			/* at this poपूर्णांक, we are running in the master.
			 * Slaves करो not receive SMPs.
			 */
			bn  = be32_to_cpu(((काष्ठा ib_smp *)mad)->attr_mod) & 0xFFFF;
			base = (__be16 *) &(((काष्ठा ib_smp *)mad)->data[0]);
			pkey_change_biपंचांगap = 0;
			क्रम (i = 0; i < 32; i++) अणु
				pr_debug("PKEY[%d] = x%x\n",
					 i + bn*32, be16_to_cpu(base[i]));
				अगर (be16_to_cpu(base[i]) !=
				    dev->pkeys.phys_pkey_cache[port_num - 1][i + bn*32]) अणु
					pkey_change_biपंचांगap |= (1 << i);
					dev->pkeys.phys_pkey_cache[port_num - 1][i + bn*32] =
						be16_to_cpu(base[i]);
				पूर्ण
			पूर्ण
			pr_debug("PKEY Change event: port=%u, "
				 "block=0x%x, change_bitmap=0x%x\n",
				 port_num, bn, pkey_change_biपंचांगap);

			अगर (pkey_change_biपंचांगap) अणु
				mlx4_ib_dispatch_event(dev, port_num,
						       IB_EVENT_PKEY_CHANGE);
				अगर (!dev->sriov.is_going_करोwn)
					__propagate_pkey_ev(dev, port_num, bn,
							    pkey_change_biपंचांगap);
			पूर्ण
			अवरोध;

		हाल IB_SMP_ATTR_GUID_INFO:
			अगर (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_PORT_MNG_CHG_EV)
				वापस;
			/* paraभवized master's guid is guid 0 -- करोes not change */
			अगर (!mlx4_is_master(dev->dev))
				mlx4_ib_dispatch_event(dev, port_num,
						       IB_EVENT_GID_CHANGE);
			/*अगर master, notअगरy relevant slaves*/
			अगर (mlx4_is_master(dev->dev) &&
			    !dev->sriov.is_going_करोwn) अणु
				bn = be32_to_cpu(((काष्ठा ib_smp *)mad)->attr_mod);
				mlx4_ib_update_cache_on_guid_change(dev, bn, port_num,
								    (u8 *)(&((काष्ठा ib_smp *)mad)->data));
				mlx4_ib_notअगरy_slaves_on_guid_change(dev, bn, port_num,
								     (u8 *)(&((काष्ठा ib_smp *)mad)->data));
			पूर्ण
			अवरोध;

		हाल IB_SMP_ATTR_SL_TO_VL_TABLE:
			/* cache sl to vl mapping changes क्रम use in
			 * filling QP1 LRH VL field when sending packets
			 */
			अगर (dev->dev->caps.flags & MLX4_DEV_CAP_FLAG_PORT_MNG_CHG_EV &&
			    dev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SL_TO_VL_CHANGE_EVENT)
				वापस;
			अगर (!mlx4_is_slave(dev->dev)) अणु
				जोड़ sl2vl_tbl_to_u64 sl2vl64;
				पूर्णांक jj;

				क्रम (jj = 0; jj < 8; jj++) अणु
					sl2vl64.sl8[jj] = ((काष्ठा ib_smp *)mad)->data[jj];
					pr_debug("port %u, sl2vl[%d] = %02x\n",
						 port_num, jj, sl2vl64.sl8[jj]);
				पूर्ण
				atomic64_set(&dev->sl2vl[port_num - 1], sl2vl64.sl64);
			पूर्ण
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
पूर्ण

अटल व्योम __propagate_pkey_ev(काष्ठा mlx4_ib_dev *dev, पूर्णांक port_num,
				पूर्णांक block, u32 change_biपंचांगap)
अणु
	पूर्णांक i, ix, slave, err;
	पूर्णांक have_event = 0;

	क्रम (slave = 0; slave < dev->dev->caps.sqp_demux; slave++) अणु
		अगर (slave == mlx4_master_func_num(dev->dev))
			जारी;
		अगर (!mlx4_is_slave_active(dev->dev, slave))
			जारी;

		have_event = 0;
		क्रम (i = 0; i < 32; i++) अणु
			अगर (!(change_biपंचांगap & (1 << i)))
				जारी;
			क्रम (ix = 0;
			     ix < dev->dev->caps.pkey_table_len[port_num]; ix++) अणु
				अगर (dev->pkeys.virt2phys_pkey[slave][port_num - 1]
				    [ix] == i + 32 * block) अणु
					err = mlx4_gen_pkey_eqe(dev->dev, slave, port_num);
					pr_debug("propagate_pkey_ev: slave %d,"
						 " port %d, ix %d (%d)\n",
						 slave, port_num, ix, err);
					have_event = 1;
					अवरोध;
				पूर्ण
			पूर्ण
			अगर (have_event)
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम node_desc_override(काष्ठा ib_device *dev,
			       काष्ठा ib_mad *mad)
अणु
	अचिन्हित दीर्घ flags;

	अगर ((mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_LID_ROUTED ||
	     mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE) &&
	    mad->mad_hdr.method == IB_MGMT_METHOD_GET_RESP &&
	    mad->mad_hdr.attr_id == IB_SMP_ATTR_NODE_DESC) अणु
		spin_lock_irqsave(&to_mdev(dev)->sm_lock, flags);
		स_नकल(((काष्ठा ib_smp *) mad)->data, dev->node_desc,
		       IB_DEVICE_NODE_DESC_MAX);
		spin_unlock_irqrestore(&to_mdev(dev)->sm_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम क्रमward_trap(काष्ठा mlx4_ib_dev *dev, u32 port_num,
			 स्थिर काष्ठा ib_mad *mad)
अणु
	पूर्णांक qpn = mad->mad_hdr.mgmt_class != IB_MGMT_CLASS_SUBN_LID_ROUTED;
	काष्ठा ib_mad_send_buf *send_buf;
	काष्ठा ib_mad_agent *agent = dev->send_agent[port_num - 1][qpn];
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	अगर (agent) अणु
		send_buf = ib_create_send_mad(agent, qpn, 0, 0, IB_MGMT_MAD_HDR,
					      IB_MGMT_MAD_DATA, GFP_ATOMIC,
					      IB_MGMT_BASE_VERSION);
		अगर (IS_ERR(send_buf))
			वापस;
		/*
		 * We rely here on the fact that MLX QPs करोn't use the
		 * address handle after the send is posted (this is
		 * wrong following the IB spec strictly, but we know
		 * it's OK क्रम our devices).
		 */
		spin_lock_irqsave(&dev->sm_lock, flags);
		स_नकल(send_buf->mad, mad, माप *mad);
		अगर ((send_buf->ah = dev->sm_ah[port_num - 1]))
			ret = ib_post_send_mad(send_buf, शून्य);
		अन्यथा
			ret = -EINVAL;
		spin_unlock_irqrestore(&dev->sm_lock, flags);

		अगर (ret)
			ib_मुक्त_send_mad(send_buf);
	पूर्ण
पूर्ण

अटल पूर्णांक mlx4_ib_demux_sa_handler(काष्ठा ib_device *ibdev, पूर्णांक port, पूर्णांक slave,
							     काष्ठा ib_sa_mad *sa_mad)
अणु
	पूर्णांक ret = 0;

	/* dispatch to dअगरferent sa handlers */
	चयन (be16_to_cpu(sa_mad->mad_hdr.attr_id)) अणु
	हाल IB_SA_ATTR_MC_MEMBER_REC:
		ret = mlx4_ib_mcg_demux_handler(ibdev, port, slave, sa_mad);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक mlx4_ib_find_real_gid(काष्ठा ib_device *ibdev, u32 port, __be64 guid)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibdev);
	पूर्णांक i;

	क्रम (i = 0; i < dev->dev->caps.sqp_demux; i++) अणु
		अगर (dev->sriov.demux[port - 1].guid_cache[i] == guid)
			वापस i;
	पूर्ण
	वापस -1;
पूर्ण


अटल पूर्णांक find_slave_port_pkey_ix(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave,
				   u32 port, u16 pkey, u16 *ix)
अणु
	पूर्णांक i, ret;
	u8 unasचिन्हित_pkey_ix, pkey_ix, partial_ix = 0xFF;
	u16 slot_pkey;

	अगर (slave == mlx4_master_func_num(dev->dev))
		वापस ib_find_cached_pkey(&dev->ib_dev, port, pkey, ix);

	unasचिन्हित_pkey_ix = dev->dev->phys_caps.pkey_phys_table_len[port] - 1;

	क्रम (i = 0; i < dev->dev->caps.pkey_table_len[port]; i++) अणु
		अगर (dev->pkeys.virt2phys_pkey[slave][port - 1][i] == unasचिन्हित_pkey_ix)
			जारी;

		pkey_ix = dev->pkeys.virt2phys_pkey[slave][port - 1][i];

		ret = ib_get_cached_pkey(&dev->ib_dev, port, pkey_ix, &slot_pkey);
		अगर (ret)
			जारी;
		अगर ((slot_pkey & 0x7FFF) == (pkey & 0x7FFF)) अणु
			अगर (slot_pkey & 0x8000) अणु
				*ix = (u16) pkey_ix;
				वापस 0;
			पूर्ण अन्यथा अणु
				/* take first partial pkey index found */
				अगर (partial_ix == 0xFF)
					partial_ix = pkey_ix;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (partial_ix < 0xFF) अणु
		*ix = (u16) partial_ix;
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक get_gids_from_l3_hdr(काष्ठा ib_grh *grh, जोड़ ib_gid *sgid,
				जोड़ ib_gid *dgid)
अणु
	पूर्णांक version = ib_get_rdma_header_version((स्थिर जोड़ rdma_network_hdr *)grh);
	क्रमागत rdma_network_type net_type;

	अगर (version == 4)
		net_type = RDMA_NETWORK_IPV4;
	अन्यथा अगर (version == 6)
		net_type = RDMA_NETWORK_IPV6;
	अन्यथा
		वापस -EINVAL;

	वापस ib_get_gids_from_rdma_hdr((जोड़ rdma_network_hdr *)grh, net_type,
					 sgid, dgid);
पूर्ण

अटल पूर्णांक is_proxy_qp0(काष्ठा mlx4_ib_dev *dev, पूर्णांक qpn, पूर्णांक slave)
अणु
	पूर्णांक proxy_start = dev->dev->phys_caps.base_proxy_sqpn + 8 * slave;

	वापस (qpn >= proxy_start && qpn <= proxy_start + 1);
पूर्ण

पूर्णांक mlx4_ib_send_to_slave(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave, u32 port,
			  क्रमागत ib_qp_type dest_qpt, काष्ठा ib_wc *wc,
			  काष्ठा ib_grh *grh, काष्ठा ib_mad *mad)
अणु
	काष्ठा ib_sge list;
	काष्ठा ib_ud_wr wr;
	स्थिर काष्ठा ib_send_wr *bad_wr;
	काष्ठा mlx4_ib_demux_pv_ctx *tun_ctx;
	काष्ठा mlx4_ib_demux_pv_qp *tun_qp;
	काष्ठा mlx4_rcv_tunnel_mad *tun_mad;
	काष्ठा rdma_ah_attr attr;
	काष्ठा ib_ah *ah;
	काष्ठा ib_qp *src_qp = शून्य;
	अचिन्हित tun_tx_ix = 0;
	पूर्णांक dqpn;
	पूर्णांक ret = 0;
	u16 tun_pkey_ix;
	u16 cached_pkey;
	u8 is_eth = dev->dev->caps.port_type[port] == MLX4_PORT_TYPE_ETH;

	अगर (dest_qpt > IB_QPT_GSI) अणु
		pr_debug("dest_qpt (%d) > IB_QPT_GSI\n", dest_qpt);
		वापस -EINVAL;
	पूर्ण

	tun_ctx = dev->sriov.demux[port-1].tun[slave];

	/* check अगर proxy qp created */
	अगर (!tun_ctx || tun_ctx->state != DEMUX_PV_STATE_ACTIVE)
		वापस -EAGAIN;

	अगर (!dest_qpt)
		tun_qp = &tun_ctx->qp[0];
	अन्यथा
		tun_qp = &tun_ctx->qp[1];

	/* compute P_Key index to put in tunnel header क्रम slave */
	अगर (dest_qpt) अणु
		u16 pkey_ix;
		ret = ib_get_cached_pkey(&dev->ib_dev, port, wc->pkey_index, &cached_pkey);
		अगर (ret) अणु
			pr_debug("unable to get %s cached pkey for index %d, ret %d\n",
				 is_proxy_qp0(dev, wc->src_qp, slave) ? "SMI" : "GSI",
				 wc->pkey_index, ret);
			वापस -EINVAL;
		पूर्ण

		ret = find_slave_port_pkey_ix(dev, slave, port, cached_pkey, &pkey_ix);
		अगर (ret) अणु
			pr_debug("unable to get %s pkey ix for pkey 0x%x, ret %d\n",
				 is_proxy_qp0(dev, wc->src_qp, slave) ? "SMI" : "GSI",
				 cached_pkey, ret);
			वापस -EINVAL;
		पूर्ण
		tun_pkey_ix = pkey_ix;
	पूर्ण अन्यथा
		tun_pkey_ix = dev->pkeys.virt2phys_pkey[slave][port - 1][0];

	dqpn = dev->dev->phys_caps.base_proxy_sqpn + 8 * slave + port + (dest_qpt * 2) - 1;

	/* get tunnel tx data buf क्रम slave */
	src_qp = tun_qp->qp;

	/* create ah. Just need an empty one with the port num क्रम the post send.
	 * The driver will set the क्रमce loopback bit in post_send */
	स_रखो(&attr, 0, माप attr);
	attr.type = rdma_ah_find_type(&dev->ib_dev, port);

	rdma_ah_set_port_num(&attr, port);
	अगर (is_eth) अणु
		जोड़ ib_gid sgid;
		जोड़ ib_gid dgid;

		अगर (get_gids_from_l3_hdr(grh, &sgid, &dgid))
			वापस -EINVAL;
		rdma_ah_set_grh(&attr, &dgid, 0, 0, 0, 0);
	पूर्ण
	ah = rdma_create_ah(tun_ctx->pd, &attr, 0);
	अगर (IS_ERR(ah))
		वापस -ENOMEM;

	/* allocate tunnel tx buf after pass failure वापसs */
	spin_lock(&tun_qp->tx_lock);
	अगर (tun_qp->tx_ix_head - tun_qp->tx_ix_tail >=
	    (MLX4_NUM_TUNNEL_BUFS - 1))
		ret = -EAGAIN;
	अन्यथा
		tun_tx_ix = (++tun_qp->tx_ix_head) & (MLX4_NUM_TUNNEL_BUFS - 1);
	spin_unlock(&tun_qp->tx_lock);
	अगर (ret)
		जाओ end;

	tun_mad = (काष्ठा mlx4_rcv_tunnel_mad *) (tun_qp->tx_ring[tun_tx_ix].buf.addr);
	अगर (tun_qp->tx_ring[tun_tx_ix].ah)
		rdma_destroy_ah(tun_qp->tx_ring[tun_tx_ix].ah, 0);
	tun_qp->tx_ring[tun_tx_ix].ah = ah;
	ib_dma_sync_single_क्रम_cpu(&dev->ib_dev,
				   tun_qp->tx_ring[tun_tx_ix].buf.map,
				   माप (काष्ठा mlx4_rcv_tunnel_mad),
				   DMA_TO_DEVICE);

	/* copy over to tunnel buffer */
	अगर (grh)
		स_नकल(&tun_mad->grh, grh, माप *grh);
	स_नकल(&tun_mad->mad, mad, माप *mad);

	/* adjust tunnel data */
	tun_mad->hdr.pkey_index = cpu_to_be16(tun_pkey_ix);
	tun_mad->hdr.flags_src_qp = cpu_to_be32(wc->src_qp & 0xFFFFFF);
	tun_mad->hdr.g_ml_path = (grh && (wc->wc_flags & IB_WC_GRH)) ? 0x80 : 0;

	अगर (is_eth) अणु
		u16 vlan = 0;
		अगर (mlx4_get_slave_शेष_vlan(dev->dev, port, slave, &vlan,
						शून्य)) अणु
			/* VST mode */
			अगर (vlan != wc->vlan_id)
				/* Packet vlan is not the VST-asचिन्हित vlan.
				 * Drop the packet.
				 */
				जाओ out;
			 अन्यथा
				/* Remove the vlan tag beक्रमe क्रमwarding
				 * the packet to the VF.
				 */
				vlan = 0xffff;
		पूर्ण अन्यथा अणु
			vlan = wc->vlan_id;
		पूर्ण

		tun_mad->hdr.sl_vid = cpu_to_be16(vlan);
		स_नकल((अक्षर *)&tun_mad->hdr.mac_31_0, &(wc->smac[0]), 4);
		स_नकल((अक्षर *)&tun_mad->hdr.slid_mac_47_32, &(wc->smac[4]), 2);
	पूर्ण अन्यथा अणु
		tun_mad->hdr.sl_vid = cpu_to_be16(((u16)(wc->sl)) << 12);
		tun_mad->hdr.slid_mac_47_32 = ib_lid_be16(wc->slid);
	पूर्ण

	ib_dma_sync_single_क्रम_device(&dev->ib_dev,
				      tun_qp->tx_ring[tun_tx_ix].buf.map,
				      माप (काष्ठा mlx4_rcv_tunnel_mad),
				      DMA_TO_DEVICE);

	list.addr = tun_qp->tx_ring[tun_tx_ix].buf.map;
	list.length = माप (काष्ठा mlx4_rcv_tunnel_mad);
	list.lkey = tun_ctx->pd->local_dma_lkey;

	wr.ah = ah;
	wr.port_num = port;
	wr.remote_qkey = IB_QP_SET_QKEY;
	wr.remote_qpn = dqpn;
	wr.wr.next = शून्य;
	wr.wr.wr_id = ((u64) tun_tx_ix) | MLX4_TUN_SET_WRID_QPN(dest_qpt);
	wr.wr.sg_list = &list;
	wr.wr.num_sge = 1;
	wr.wr.opcode = IB_WR_SEND;
	wr.wr.send_flags = IB_SEND_SIGNALED;

	ret = ib_post_send(src_qp, &wr.wr, &bad_wr);
	अगर (!ret)
		वापस 0;
 out:
	spin_lock(&tun_qp->tx_lock);
	tun_qp->tx_ix_tail++;
	spin_unlock(&tun_qp->tx_lock);
	tun_qp->tx_ring[tun_tx_ix].ah = शून्य;
end:
	rdma_destroy_ah(ah, 0);
	वापस ret;
पूर्ण

अटल पूर्णांक mlx4_ib_demux_mad(काष्ठा ib_device *ibdev, u32 port,
			काष्ठा ib_wc *wc, काष्ठा ib_grh *grh,
			काष्ठा ib_mad *mad)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibdev);
	पूर्णांक err, other_port;
	पूर्णांक slave = -1;
	u8 *slave_id;
	पूर्णांक is_eth = 0;

	अगर (rdma_port_get_link_layer(ibdev, port) == IB_LINK_LAYER_INFINIBAND)
		is_eth = 0;
	अन्यथा
		is_eth = 1;

	अगर (is_eth) अणु
		जोड़ ib_gid dgid;
		जोड़ ib_gid sgid;

		अगर (get_gids_from_l3_hdr(grh, &sgid, &dgid))
			वापस -EINVAL;
		अगर (!(wc->wc_flags & IB_WC_GRH)) अणु
			mlx4_ib_warn(ibdev, "RoCE grh not present.\n");
			वापस -EINVAL;
		पूर्ण
		अगर (mad->mad_hdr.mgmt_class != IB_MGMT_CLASS_CM) अणु
			mlx4_ib_warn(ibdev, "RoCE mgmt class is not CM\n");
			वापस -EINVAL;
		पूर्ण
		err = mlx4_get_slave_from_roce_gid(dev->dev, port, dgid.raw, &slave);
		अगर (err && mlx4_is_mf_bonded(dev->dev)) अणु
			other_port = (port == 1) ? 2 : 1;
			err = mlx4_get_slave_from_roce_gid(dev->dev, other_port, dgid.raw, &slave);
			अगर (!err) अणु
				port = other_port;
				pr_debug("resolved slave %d from gid %pI6 wire port %d other %d\n",
					 slave, grh->dgid.raw, port, other_port);
			पूर्ण
		पूर्ण
		अगर (err) अणु
			mlx4_ib_warn(ibdev, "failed matching grh\n");
			वापस -ENOENT;
		पूर्ण
		अगर (slave >= dev->dev->caps.sqp_demux) अणु
			mlx4_ib_warn(ibdev, "slave id: %d is bigger than allowed:%d\n",
				     slave, dev->dev->caps.sqp_demux);
			वापस -ENOENT;
		पूर्ण

		अगर (mlx4_ib_demux_cm_handler(ibdev, port, शून्य, mad))
			वापस 0;

		err = mlx4_ib_send_to_slave(dev, slave, port, wc->qp->qp_type, wc, grh, mad);
		अगर (err)
			pr_debug("failed sending %s to slave %d via tunnel qp (%d)\n",
				 is_proxy_qp0(dev, wc->src_qp, slave) ? "SMI" : "GSI",
				 slave, err);
		वापस 0;
	पूर्ण

	/* Initially assume that this mad is क्रम us */
	slave = mlx4_master_func_num(dev->dev);

	/* See अगर the slave id is encoded in a response mad */
	अगर (mad->mad_hdr.method & 0x80) अणु
		slave_id = (u8 *) &mad->mad_hdr.tid;
		slave = *slave_id;
		अगर (slave != 255) /*255 indicates the करोm0*/
			*slave_id = 0; /* remap tid */
	पूर्ण

	/* If a grh is present, we demux according to it */
	अगर (wc->wc_flags & IB_WC_GRH) अणु
		अगर (grh->dgid.global.पूर्णांकerface_id ==
			cpu_to_be64(IB_SA_WELL_KNOWN_GUID) &&
		    grh->dgid.global.subnet_prefix == cpu_to_be64(
			atomic64_पढ़ो(&dev->sriov.demux[port - 1].subnet_prefix))) अणु
			slave = 0;
		पूर्ण अन्यथा अणु
			slave = mlx4_ib_find_real_gid(ibdev, port,
						      grh->dgid.global.पूर्णांकerface_id);
			अगर (slave < 0) अणु
				mlx4_ib_warn(ibdev, "failed matching grh\n");
				वापस -ENOENT;
			पूर्ण
		पूर्ण
	पूर्ण
	/* Class-specअगरic handling */
	चयन (mad->mad_hdr.mgmt_class) अणु
	हाल IB_MGMT_CLASS_SUBN_LID_ROUTED:
	हाल IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE:
		/* 255 indicates the करोm0 */
		अगर (slave != 255 && slave != mlx4_master_func_num(dev->dev)) अणु
			अगर (!mlx4_vf_smi_enabled(dev->dev, slave, port))
				वापस -EPERM;
			/* क्रम a VF. drop unsolicited MADs */
			अगर (!(mad->mad_hdr.method & IB_MGMT_METHOD_RESP)) अणु
				mlx4_ib_warn(ibdev, "demux QP0. rejecting unsolicited mad for slave %d class 0x%x, method 0x%x\n",
					     slave, mad->mad_hdr.mgmt_class,
					     mad->mad_hdr.method);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अवरोध;
	हाल IB_MGMT_CLASS_SUBN_ADM:
		अगर (mlx4_ib_demux_sa_handler(ibdev, port, slave,
					     (काष्ठा ib_sa_mad *) mad))
			वापस 0;
		अवरोध;
	हाल IB_MGMT_CLASS_CM:
		अगर (mlx4_ib_demux_cm_handler(ibdev, port, &slave, mad))
			वापस 0;
		अवरोध;
	हाल IB_MGMT_CLASS_DEVICE_MGMT:
		अगर (mad->mad_hdr.method != IB_MGMT_METHOD_GET_RESP)
			वापस 0;
		अवरोध;
	शेष:
		/* Drop unsupported classes क्रम slaves in tunnel mode */
		अगर (slave != mlx4_master_func_num(dev->dev)) अणु
			pr_debug("dropping unsupported ingress mad from class:%d "
				 "for slave:%d\n", mad->mad_hdr.mgmt_class, slave);
			वापस 0;
		पूर्ण
	पूर्ण
	/*make sure that no slave==255 was not handled yet.*/
	अगर (slave >= dev->dev->caps.sqp_demux) अणु
		mlx4_ib_warn(ibdev, "slave id: %d is bigger than allowed:%d\n",
			     slave, dev->dev->caps.sqp_demux);
		वापस -ENOENT;
	पूर्ण

	err = mlx4_ib_send_to_slave(dev, slave, port, wc->qp->qp_type, wc, grh, mad);
	अगर (err)
		pr_debug("failed sending %s to slave %d via tunnel qp (%d)\n",
			 is_proxy_qp0(dev, wc->src_qp, slave) ? "SMI" : "GSI",
			 slave, err);
	वापस 0;
पूर्ण

अटल पूर्णांक ib_process_mad(काष्ठा ib_device *ibdev, पूर्णांक mad_flags, u32 port_num,
			स्थिर काष्ठा ib_wc *in_wc, स्थिर काष्ठा ib_grh *in_grh,
			स्थिर काष्ठा ib_mad *in_mad, काष्ठा ib_mad *out_mad)
अणु
	u16 slid, prev_lid = 0;
	पूर्णांक err;
	काष्ठा ib_port_attr pattr;

	slid = in_wc ? ib_lid_cpu16(in_wc->slid) : be16_to_cpu(IB_LID_PERMISSIVE);

	अगर (in_mad->mad_hdr.method == IB_MGMT_METHOD_TRAP && slid == 0) अणु
		क्रमward_trap(to_mdev(ibdev), port_num, in_mad);
		वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;
	पूर्ण

	अगर (in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_LID_ROUTED ||
	    in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE) अणु
		अगर (in_mad->mad_hdr.method   != IB_MGMT_METHOD_GET &&
		    in_mad->mad_hdr.method   != IB_MGMT_METHOD_SET &&
		    in_mad->mad_hdr.method   != IB_MGMT_METHOD_TRAP_REPRESS)
			वापस IB_MAD_RESULT_SUCCESS;

		/*
		 * Don't process SMInfo queries -- the SMA can't handle them.
		 */
		अगर (in_mad->mad_hdr.attr_id == IB_SMP_ATTR_SM_INFO)
			वापस IB_MAD_RESULT_SUCCESS;
	पूर्ण अन्यथा अगर (in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_PERF_MGMT ||
		   in_mad->mad_hdr.mgmt_class == MLX4_IB_VENDOR_CLASS1   ||
		   in_mad->mad_hdr.mgmt_class == MLX4_IB_VENDOR_CLASS2   ||
		   in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_CONG_MGMT) अणु
		अगर (in_mad->mad_hdr.method  != IB_MGMT_METHOD_GET &&
		    in_mad->mad_hdr.method  != IB_MGMT_METHOD_SET)
			वापस IB_MAD_RESULT_SUCCESS;
	पूर्ण अन्यथा
		वापस IB_MAD_RESULT_SUCCESS;

	अगर ((in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_LID_ROUTED ||
	     in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE) &&
	    in_mad->mad_hdr.method == IB_MGMT_METHOD_SET &&
	    in_mad->mad_hdr.attr_id == IB_SMP_ATTR_PORT_INFO &&
	    !ib_query_port(ibdev, port_num, &pattr))
		prev_lid = ib_lid_cpu16(pattr.lid);

	err = mlx4_MAD_IFC(to_mdev(ibdev),
			   (mad_flags & IB_MAD_IGNORE_MKEY ? MLX4_MAD_IFC_IGNORE_MKEY : 0) |
			   (mad_flags & IB_MAD_IGNORE_BKEY ? MLX4_MAD_IFC_IGNORE_BKEY : 0) |
			   MLX4_MAD_IFC_NET_VIEW,
			   port_num, in_wc, in_grh, in_mad, out_mad);
	अगर (err)
		वापस IB_MAD_RESULT_FAILURE;

	अगर (!out_mad->mad_hdr.status) अणु
		smp_snoop(ibdev, port_num, in_mad, prev_lid);
		/* slaves get node desc from FW */
		अगर (!mlx4_is_slave(to_mdev(ibdev)->dev))
			node_desc_override(ibdev, out_mad);
	पूर्ण

	/* set वापस bit in status of directed route responses */
	अगर (in_mad->mad_hdr.mgmt_class == IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE)
		out_mad->mad_hdr.status |= cpu_to_be16(1 << 15);

	अगर (in_mad->mad_hdr.method == IB_MGMT_METHOD_TRAP_REPRESS)
		/* no response क्रम trap repress */
		वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;

	वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY;
पूर्ण

अटल व्योम edit_counter(काष्ठा mlx4_counter *cnt, व्योम *counters,
			 __be16 attr_id)
अणु
	चयन (attr_id) अणु
	हाल IB_PMA_PORT_COUNTERS:
	अणु
		काष्ठा ib_pma_portcounters *pma_cnt =
			(काष्ठा ib_pma_portcounters *)counters;

		ASSIGN_32BIT_COUNTER(pma_cnt->port_xmit_data,
				     (be64_to_cpu(cnt->tx_bytes) >> 2));
		ASSIGN_32BIT_COUNTER(pma_cnt->port_rcv_data,
				     (be64_to_cpu(cnt->rx_bytes) >> 2));
		ASSIGN_32BIT_COUNTER(pma_cnt->port_xmit_packets,
				     be64_to_cpu(cnt->tx_frames));
		ASSIGN_32BIT_COUNTER(pma_cnt->port_rcv_packets,
				     be64_to_cpu(cnt->rx_frames));
		अवरोध;
	पूर्ण
	हाल IB_PMA_PORT_COUNTERS_EXT:
	अणु
		काष्ठा ib_pma_portcounters_ext *pma_cnt_ext =
			(काष्ठा ib_pma_portcounters_ext *)counters;

		pma_cnt_ext->port_xmit_data =
			cpu_to_be64(be64_to_cpu(cnt->tx_bytes) >> 2);
		pma_cnt_ext->port_rcv_data =
			cpu_to_be64(be64_to_cpu(cnt->rx_bytes) >> 2);
		pma_cnt_ext->port_xmit_packets = cnt->tx_frames;
		pma_cnt_ext->port_rcv_packets = cnt->rx_frames;
		अवरोध;
	पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक iboe_process_mad_port_info(व्योम *out_mad)
अणु
	काष्ठा ib_class_port_info cpi = अणुपूर्ण;

	cpi.capability_mask = IB_PMA_CLASS_CAP_EXT_WIDTH;
	स_नकल(out_mad, &cpi, माप(cpi));
	वापस IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY;
पूर्ण

अटल पूर्णांक iboe_process_mad(काष्ठा ib_device *ibdev, पूर्णांक mad_flags,
			    u32 port_num, स्थिर काष्ठा ib_wc *in_wc,
			    स्थिर काष्ठा ib_grh *in_grh,
			    स्थिर काष्ठा ib_mad *in_mad, काष्ठा ib_mad *out_mad)
अणु
	काष्ठा mlx4_counter counter_stats;
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibdev);
	काष्ठा counter_index *पंचांगp_counter;
	पूर्णांक err = IB_MAD_RESULT_FAILURE, stats_avail = 0;

	अगर (in_mad->mad_hdr.mgmt_class != IB_MGMT_CLASS_PERF_MGMT)
		वापस -EINVAL;

	अगर (in_mad->mad_hdr.attr_id == IB_PMA_CLASS_PORT_INFO)
		वापस iboe_process_mad_port_info((व्योम *)(out_mad->data + 40));

	स_रखो(&counter_stats, 0, माप(counter_stats));
	mutex_lock(&dev->counters_table[port_num - 1].mutex);
	list_क्रम_each_entry(पंचांगp_counter,
			    &dev->counters_table[port_num - 1].counters_list,
			    list) अणु
		err = mlx4_get_counter_stats(dev->dev,
					     पंचांगp_counter->index,
					     &counter_stats, 0);
		अगर (err) अणु
			err = IB_MAD_RESULT_FAILURE;
			stats_avail = 0;
			अवरोध;
		पूर्ण
		stats_avail = 1;
	पूर्ण
	mutex_unlock(&dev->counters_table[port_num - 1].mutex);
	अगर (stats_avail) अणु
		चयन (counter_stats.counter_mode & 0xf) अणु
		हाल 0:
			edit_counter(&counter_stats,
				     (व्योम *)(out_mad->data + 40),
				     in_mad->mad_hdr.attr_id);
			err = IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_REPLY;
			अवरोध;
		शेष:
			err = IB_MAD_RESULT_FAILURE;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

पूर्णांक mlx4_ib_process_mad(काष्ठा ib_device *ibdev, पूर्णांक mad_flags, u32 port_num,
			स्थिर काष्ठा ib_wc *in_wc, स्थिर काष्ठा ib_grh *in_grh,
			स्थिर काष्ठा ib_mad *in, काष्ठा ib_mad *out,
			माप_प्रकार *out_mad_size, u16 *out_mad_pkey_index)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ibdev);
	क्रमागत rdma_link_layer link = rdma_port_get_link_layer(ibdev, port_num);

	/* iboe_process_mad() which uses the HCA flow-counters to implement IB PMA
	 * queries, should be called only by VFs and क्रम that specअगरic purpose
	 */
	अगर (link == IB_LINK_LAYER_INFINIBAND) अणु
		अगर (mlx4_is_slave(dev->dev) &&
		    (in->mad_hdr.mgmt_class == IB_MGMT_CLASS_PERF_MGMT &&
		     (in->mad_hdr.attr_id == IB_PMA_PORT_COUNTERS ||
		      in->mad_hdr.attr_id == IB_PMA_PORT_COUNTERS_EXT ||
		      in->mad_hdr.attr_id == IB_PMA_CLASS_PORT_INFO)))
			वापस iboe_process_mad(ibdev, mad_flags, port_num,
						in_wc, in_grh, in, out);

		वापस ib_process_mad(ibdev, mad_flags, port_num, in_wc, in_grh,
				      in, out);
	पूर्ण

	अगर (link == IB_LINK_LAYER_ETHERNET)
		वापस iboe_process_mad(ibdev, mad_flags, port_num, in_wc,
					in_grh, in, out);

	वापस -EINVAL;
पूर्ण

अटल व्योम send_handler(काष्ठा ib_mad_agent *agent,
			 काष्ठा ib_mad_send_wc *mad_send_wc)
अणु
	अगर (mad_send_wc->send_buf->context[0])
		rdma_destroy_ah(mad_send_wc->send_buf->context[0], 0);
	ib_मुक्त_send_mad(mad_send_wc->send_buf);
पूर्ण

पूर्णांक mlx4_ib_mad_init(काष्ठा mlx4_ib_dev *dev)
अणु
	काष्ठा ib_mad_agent *agent;
	पूर्णांक p, q;
	पूर्णांक ret;
	क्रमागत rdma_link_layer ll;

	क्रम (p = 0; p < dev->num_ports; ++p) अणु
		ll = rdma_port_get_link_layer(&dev->ib_dev, p + 1);
		क्रम (q = 0; q <= 1; ++q) अणु
			अगर (ll == IB_LINK_LAYER_INFINIBAND) अणु
				agent = ib_रेजिस्टर_mad_agent(&dev->ib_dev, p + 1,
							      q ? IB_QPT_GSI : IB_QPT_SMI,
							      शून्य, 0, send_handler,
							      शून्य, शून्य, 0);
				अगर (IS_ERR(agent)) अणु
					ret = PTR_ERR(agent);
					जाओ err;
				पूर्ण
				dev->send_agent[p][q] = agent;
			पूर्ण अन्यथा
				dev->send_agent[p][q] = शून्य;
		पूर्ण
	पूर्ण

	वापस 0;

err:
	क्रम (p = 0; p < dev->num_ports; ++p)
		क्रम (q = 0; q <= 1; ++q)
			अगर (dev->send_agent[p][q])
				ib_unरेजिस्टर_mad_agent(dev->send_agent[p][q]);

	वापस ret;
पूर्ण

व्योम mlx4_ib_mad_cleanup(काष्ठा mlx4_ib_dev *dev)
अणु
	काष्ठा ib_mad_agent *agent;
	पूर्णांक p, q;

	क्रम (p = 0; p < dev->num_ports; ++p) अणु
		क्रम (q = 0; q <= 1; ++q) अणु
			agent = dev->send_agent[p][q];
			अगर (agent) अणु
				dev->send_agent[p][q] = शून्य;
				ib_unरेजिस्टर_mad_agent(agent);
			पूर्ण
		पूर्ण

		अगर (dev->sm_ah[p])
			rdma_destroy_ah(dev->sm_ah[p], 0);
	पूर्ण
पूर्ण

अटल व्योम handle_lid_change_event(काष्ठा mlx4_ib_dev *dev, u32 port_num)
अणु
	mlx4_ib_dispatch_event(dev, port_num, IB_EVENT_LID_CHANGE);

	अगर (mlx4_is_master(dev->dev) && !dev->sriov.is_going_करोwn)
		mlx4_gen_slaves_port_mgt_ev(dev->dev, port_num,
					    MLX4_EQ_PORT_INFO_LID_CHANGE_MASK);
पूर्ण

अटल व्योम handle_client_rereg_event(काष्ठा mlx4_ib_dev *dev, u32 port_num)
अणु
	/* re-configure the alias-guid and mcg's */
	अगर (mlx4_is_master(dev->dev)) अणु
		mlx4_ib_invalidate_all_guid_record(dev, port_num);

		अगर (!dev->sriov.is_going_करोwn) अणु
			mlx4_ib_mcg_port_cleanup(&dev->sriov.demux[port_num - 1], 0);
			mlx4_gen_slaves_port_mgt_ev(dev->dev, port_num,
						    MLX4_EQ_PORT_INFO_CLIENT_REREG_MASK);
		पूर्ण
	पूर्ण

	/* Update the sl to vl table from inside client rereg
	 * only अगर in secure-host mode (snooping is not possible)
	 * and the sl-to-vl change event is not generated by FW.
	 */
	अगर (!mlx4_is_slave(dev->dev) &&
	    dev->dev->flags & MLX4_FLAG_SECURE_HOST &&
	    !(dev->dev->caps.flags2 & MLX4_DEV_CAP_FLAG2_SL_TO_VL_CHANGE_EVENT)) अणु
		अगर (mlx4_is_master(dev->dev))
			/* alपढ़ोy in work queue from mlx4_ib_event queueing
			 * mlx4_handle_port_mgmt_change_event, which calls
			 * this procedure. Thereक्रमe, call sl2vl_update directly.
			 */
			mlx4_ib_sl2vl_update(dev, port_num);
		अन्यथा
			mlx4_sched_ib_sl2vl_update_work(dev, port_num);
	पूर्ण
	mlx4_ib_dispatch_event(dev, port_num, IB_EVENT_CLIENT_REREGISTER);
पूर्ण

अटल व्योम propagate_pkey_ev(काष्ठा mlx4_ib_dev *dev, पूर्णांक port_num,
			      काष्ठा mlx4_eqe *eqe)
अणु
	__propagate_pkey_ev(dev, port_num, GET_BLK_PTR_FROM_EQE(eqe),
			    GET_MASK_FROM_EQE(eqe));
पूर्ण

अटल व्योम handle_slaves_guid_change(काष्ठा mlx4_ib_dev *dev, u32 port_num,
				      u32 guid_tbl_blk_num, u32 change_biपंचांगap)
अणु
	काष्ठा ib_smp *in_mad  = शून्य;
	काष्ठा ib_smp *out_mad  = शून्य;
	u16 i;

	अगर (!mlx4_is_mfunc(dev->dev) || !mlx4_is_master(dev->dev))
		वापस;

	in_mad  = kदो_स्मृति(माप *in_mad, GFP_KERNEL);
	out_mad = kदो_स्मृति(माप *out_mad, GFP_KERNEL);
	अगर (!in_mad || !out_mad)
		जाओ out;

	guid_tbl_blk_num  *= 4;

	क्रम (i = 0; i < 4; i++) अणु
		अगर (change_biपंचांगap && (!((change_biपंचांगap >> (8 * i)) & 0xff)))
			जारी;
		स_रखो(in_mad, 0, माप *in_mad);
		स_रखो(out_mad, 0, माप *out_mad);

		in_mad->base_version  = 1;
		in_mad->mgmt_class    = IB_MGMT_CLASS_SUBN_LID_ROUTED;
		in_mad->class_version = 1;
		in_mad->method        = IB_MGMT_METHOD_GET;
		in_mad->attr_id       = IB_SMP_ATTR_GUID_INFO;
		in_mad->attr_mod      = cpu_to_be32(guid_tbl_blk_num + i);

		अगर (mlx4_MAD_IFC(dev,
				 MLX4_MAD_IFC_IGNORE_KEYS | MLX4_MAD_IFC_NET_VIEW,
				 port_num, शून्य, शून्य, in_mad, out_mad)) अणु
			mlx4_ib_warn(&dev->ib_dev, "Failed in get GUID INFO MAD_IFC\n");
			जाओ out;
		पूर्ण

		mlx4_ib_update_cache_on_guid_change(dev, guid_tbl_blk_num + i,
						    port_num,
						    (u8 *)(&((काष्ठा ib_smp *)out_mad)->data));
		mlx4_ib_notअगरy_slaves_on_guid_change(dev, guid_tbl_blk_num + i,
						     port_num,
						     (u8 *)(&((काष्ठा ib_smp *)out_mad)->data));
	पूर्ण

out:
	kमुक्त(in_mad);
	kमुक्त(out_mad);
	वापस;
पूर्ण

व्योम handle_port_mgmt_change_event(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ib_event_work *ew = container_of(work, काष्ठा ib_event_work, work);
	काष्ठा mlx4_ib_dev *dev = ew->ib_dev;
	काष्ठा mlx4_eqe *eqe = &(ew->ib_eqe);
	u32 port = eqe->event.port_mgmt_change.port;
	u32 changed_attr;
	u32 tbl_block;
	u32 change_biपंचांगap;

	चयन (eqe->subtype) अणु
	हाल MLX4_DEV_PMC_SUBTYPE_PORT_INFO:
		changed_attr = be32_to_cpu(eqe->event.port_mgmt_change.params.port_info.changed_attr);

		/* Update the SM ah - This should be करोne beक्रमe handling
		   the other changed attributes so that MADs can be sent to the SM */
		अगर (changed_attr & MSTR_SM_CHANGE_MASK) अणु
			u16 lid = be16_to_cpu(eqe->event.port_mgmt_change.params.port_info.mstr_sm_lid);
			u8 sl = eqe->event.port_mgmt_change.params.port_info.mstr_sm_sl & 0xf;
			update_sm_ah(dev, port, lid, sl);
		पूर्ण

		/* Check अगर it is a lid change event */
		अगर (changed_attr & MLX4_EQ_PORT_INFO_LID_CHANGE_MASK)
			handle_lid_change_event(dev, port);

		/* Generate GUID changed event */
		अगर (changed_attr & MLX4_EQ_PORT_INFO_GID_PFX_CHANGE_MASK) अणु
			अगर (mlx4_is_master(dev->dev)) अणु
				जोड़ ib_gid gid;
				पूर्णांक err = 0;

				अगर (!eqe->event.port_mgmt_change.params.port_info.gid_prefix)
					err = __mlx4_ib_query_gid(&dev->ib_dev, port, 0, &gid, 1);
				अन्यथा
					gid.global.subnet_prefix =
						eqe->event.port_mgmt_change.params.port_info.gid_prefix;
				अगर (err) अणु
					pr_warn("Could not change QP1 subnet prefix for port %d: query_gid error (%d)\n",
						port, err);
				पूर्ण अन्यथा अणु
					pr_debug("Changing QP1 subnet prefix for port %d. old=0x%llx. new=0x%llx\n",
						 port,
						 (u64)atomic64_पढ़ो(&dev->sriov.demux[port - 1].subnet_prefix),
						 be64_to_cpu(gid.global.subnet_prefix));
					atomic64_set(&dev->sriov.demux[port - 1].subnet_prefix,
						     be64_to_cpu(gid.global.subnet_prefix));
				पूर्ण
			पूर्ण
			mlx4_ib_dispatch_event(dev, port, IB_EVENT_GID_CHANGE);
			/*अगर master, notअगरy all slaves*/
			अगर (mlx4_is_master(dev->dev))
				mlx4_gen_slaves_port_mgt_ev(dev->dev, port,
							    MLX4_EQ_PORT_INFO_GID_PFX_CHANGE_MASK);
		पूर्ण

		अगर (changed_attr & MLX4_EQ_PORT_INFO_CLIENT_REREG_MASK)
			handle_client_rereg_event(dev, port);
		अवरोध;

	हाल MLX4_DEV_PMC_SUBTYPE_PKEY_TABLE:
		mlx4_ib_dispatch_event(dev, port, IB_EVENT_PKEY_CHANGE);
		अगर (mlx4_is_master(dev->dev) && !dev->sriov.is_going_करोwn)
			propagate_pkey_ev(dev, port, eqe);
		अवरोध;
	हाल MLX4_DEV_PMC_SUBTYPE_GUID_INFO:
		/* paraभवized master's guid is guid 0 -- करोes not change */
		अगर (!mlx4_is_master(dev->dev))
			mlx4_ib_dispatch_event(dev, port, IB_EVENT_GID_CHANGE);
		/*अगर master, notअगरy relevant slaves*/
		अन्यथा अगर (!dev->sriov.is_going_करोwn) अणु
			tbl_block = GET_BLK_PTR_FROM_EQE(eqe);
			change_biपंचांगap = GET_MASK_FROM_EQE(eqe);
			handle_slaves_guid_change(dev, port, tbl_block, change_biपंचांगap);
		पूर्ण
		अवरोध;

	हाल MLX4_DEV_PMC_SUBTYPE_SL_TO_VL_MAP:
		/* cache sl to vl mapping changes क्रम use in
		 * filling QP1 LRH VL field when sending packets
		 */
		अगर (!mlx4_is_slave(dev->dev)) अणु
			जोड़ sl2vl_tbl_to_u64 sl2vl64;
			पूर्णांक jj;

			क्रम (jj = 0; jj < 8; jj++) अणु
				sl2vl64.sl8[jj] =
					eqe->event.port_mgmt_change.params.sl2vl_tbl_change_info.sl2vl_table[jj];
				pr_debug("port %u, sl2vl[%d] = %02x\n",
					 port, jj, sl2vl64.sl8[jj]);
			पूर्ण
			atomic64_set(&dev->sl2vl[port - 1], sl2vl64.sl64);
		पूर्ण
		अवरोध;
	शेष:
		pr_warn("Unsupported subtype 0x%x for "
			"Port Management Change event\n", eqe->subtype);
	पूर्ण

	kमुक्त(ew);
पूर्ण

व्योम mlx4_ib_dispatch_event(काष्ठा mlx4_ib_dev *dev, u32 port_num,
			    क्रमागत ib_event_type type)
अणु
	काष्ठा ib_event event;

	event.device		= &dev->ib_dev;
	event.element.port_num	= port_num;
	event.event		= type;

	ib_dispatch_event(&event);
पूर्ण

अटल व्योम mlx4_ib_tunnel_comp_handler(काष्ठा ib_cq *cq, व्योम *arg)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mlx4_ib_demux_pv_ctx *ctx = cq->cq_context;
	काष्ठा mlx4_ib_dev *dev = to_mdev(ctx->ib_dev);
	spin_lock_irqsave(&dev->sriov.going_करोwn_lock, flags);
	अगर (!dev->sriov.is_going_करोwn && ctx->state == DEMUX_PV_STATE_ACTIVE)
		queue_work(ctx->wq, &ctx->work);
	spin_unlock_irqrestore(&dev->sriov.going_करोwn_lock, flags);
पूर्ण

अटल व्योम mlx4_ib_wire_comp_handler(काष्ठा ib_cq *cq, व्योम *arg)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mlx4_ib_demux_pv_ctx *ctx = cq->cq_context;
	काष्ठा mlx4_ib_dev *dev = to_mdev(ctx->ib_dev);

	spin_lock_irqsave(&dev->sriov.going_करोwn_lock, flags);
	अगर (!dev->sriov.is_going_करोwn && ctx->state == DEMUX_PV_STATE_ACTIVE)
		queue_work(ctx->wi_wq, &ctx->work);
	spin_unlock_irqrestore(&dev->sriov.going_करोwn_lock, flags);
पूर्ण

अटल पूर्णांक mlx4_ib_post_pv_qp_buf(काष्ठा mlx4_ib_demux_pv_ctx *ctx,
				  काष्ठा mlx4_ib_demux_pv_qp *tun_qp,
				  पूर्णांक index)
अणु
	काष्ठा ib_sge sg_list;
	काष्ठा ib_recv_wr recv_wr;
	स्थिर काष्ठा ib_recv_wr *bad_recv_wr;
	पूर्णांक size;

	size = (tun_qp->qp->qp_type == IB_QPT_UD) ?
		माप (काष्ठा mlx4_tunnel_mad) : माप (काष्ठा mlx4_mad_rcv_buf);

	sg_list.addr = tun_qp->ring[index].map;
	sg_list.length = size;
	sg_list.lkey = ctx->pd->local_dma_lkey;

	recv_wr.next = शून्य;
	recv_wr.sg_list = &sg_list;
	recv_wr.num_sge = 1;
	recv_wr.wr_id = (u64) index | MLX4_TUN_WRID_RECV |
		MLX4_TUN_SET_WRID_QPN(tun_qp->proxy_qpt);
	ib_dma_sync_single_क्रम_device(ctx->ib_dev, tun_qp->ring[index].map,
				      size, DMA_FROM_DEVICE);
	वापस ib_post_recv(tun_qp->qp, &recv_wr, &bad_recv_wr);
पूर्ण

अटल पूर्णांक mlx4_ib_multiplex_sa_handler(काष्ठा ib_device *ibdev, पूर्णांक port,
		पूर्णांक slave, काष्ठा ib_sa_mad *sa_mad)
अणु
	पूर्णांक ret = 0;

	/* dispatch to dअगरferent sa handlers */
	चयन (be16_to_cpu(sa_mad->mad_hdr.attr_id)) अणु
	हाल IB_SA_ATTR_MC_MEMBER_REC:
		ret = mlx4_ib_mcg_multiplex_handler(ibdev, port, slave, sa_mad);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक mlx4_ib_send_to_wire(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave, u32 port,
			 क्रमागत ib_qp_type dest_qpt, u16 pkey_index,
			 u32 remote_qpn, u32 qkey, काष्ठा rdma_ah_attr *attr,
			 u8 *s_mac, u16 vlan_id, काष्ठा ib_mad *mad)
अणु
	काष्ठा ib_sge list;
	काष्ठा ib_ud_wr wr;
	स्थिर काष्ठा ib_send_wr *bad_wr;
	काष्ठा mlx4_ib_demux_pv_ctx *sqp_ctx;
	काष्ठा mlx4_ib_demux_pv_qp *sqp;
	काष्ठा mlx4_mad_snd_buf *sqp_mad;
	काष्ठा ib_ah *ah;
	काष्ठा ib_qp *send_qp = शून्य;
	अचिन्हित wire_tx_ix = 0;
	u16 wire_pkey_ix;
	पूर्णांक src_qpnum;
	पूर्णांक ret;

	sqp_ctx = dev->sriov.sqps[port-1];

	/* check अगर proxy qp created */
	अगर (!sqp_ctx || sqp_ctx->state != DEMUX_PV_STATE_ACTIVE)
		वापस -EAGAIN;

	अगर (dest_qpt == IB_QPT_SMI) अणु
		src_qpnum = 0;
		sqp = &sqp_ctx->qp[0];
		wire_pkey_ix = dev->pkeys.virt2phys_pkey[slave][port - 1][0];
	पूर्ण अन्यथा अणु
		src_qpnum = 1;
		sqp = &sqp_ctx->qp[1];
		wire_pkey_ix = dev->pkeys.virt2phys_pkey[slave][port - 1][pkey_index];
	पूर्ण

	send_qp = sqp->qp;

	ah = rdma_zalloc_drv_obj(sqp_ctx->pd->device, ib_ah);
	अगर (!ah)
		वापस -ENOMEM;

	ah->device = sqp_ctx->pd->device;
	ah->pd = sqp_ctx->pd;

	/* create ah */
	ret = mlx4_ib_create_ah_slave(ah, attr,
				      rdma_ah_retrieve_grh(attr)->sgid_index,
				      s_mac, vlan_id);
	अगर (ret)
		जाओ out;

	spin_lock(&sqp->tx_lock);
	अगर (sqp->tx_ix_head - sqp->tx_ix_tail >=
	    (MLX4_NUM_WIRE_BUFS - 1))
		ret = -EAGAIN;
	अन्यथा
		wire_tx_ix = (++sqp->tx_ix_head) & (MLX4_NUM_WIRE_BUFS - 1);
	spin_unlock(&sqp->tx_lock);
	अगर (ret)
		जाओ out;

	sqp_mad = (काष्ठा mlx4_mad_snd_buf *) (sqp->tx_ring[wire_tx_ix].buf.addr);
	kमुक्त(sqp->tx_ring[wire_tx_ix].ah);
	sqp->tx_ring[wire_tx_ix].ah = ah;
	ib_dma_sync_single_क्रम_cpu(&dev->ib_dev,
				   sqp->tx_ring[wire_tx_ix].buf.map,
				   माप (काष्ठा mlx4_mad_snd_buf),
				   DMA_TO_DEVICE);

	स_नकल(&sqp_mad->payload, mad, माप *mad);

	ib_dma_sync_single_क्रम_device(&dev->ib_dev,
				      sqp->tx_ring[wire_tx_ix].buf.map,
				      माप (काष्ठा mlx4_mad_snd_buf),
				      DMA_TO_DEVICE);

	list.addr = sqp->tx_ring[wire_tx_ix].buf.map;
	list.length = माप (काष्ठा mlx4_mad_snd_buf);
	list.lkey = sqp_ctx->pd->local_dma_lkey;

	wr.ah = ah;
	wr.port_num = port;
	wr.pkey_index = wire_pkey_ix;
	wr.remote_qkey = qkey;
	wr.remote_qpn = remote_qpn;
	wr.wr.next = शून्य;
	wr.wr.wr_id = ((u64) wire_tx_ix) | MLX4_TUN_SET_WRID_QPN(src_qpnum);
	wr.wr.sg_list = &list;
	wr.wr.num_sge = 1;
	wr.wr.opcode = IB_WR_SEND;
	wr.wr.send_flags = IB_SEND_SIGNALED;

	ret = ib_post_send(send_qp, &wr.wr, &bad_wr);
	अगर (!ret)
		वापस 0;

	spin_lock(&sqp->tx_lock);
	sqp->tx_ix_tail++;
	spin_unlock(&sqp->tx_lock);
	sqp->tx_ring[wire_tx_ix].ah = शून्य;
out:
	kमुक्त(ah);
	वापस ret;
पूर्ण

अटल पूर्णांक get_slave_base_gid_ix(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave, पूर्णांक port)
अणु
	अगर (rdma_port_get_link_layer(&dev->ib_dev, port) == IB_LINK_LAYER_INFINIBAND)
		वापस slave;
	वापस mlx4_get_base_gid_ix(dev->dev, slave, port);
पूर्ण

अटल व्योम fill_in_real_sgid_index(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave, पूर्णांक port,
				    काष्ठा rdma_ah_attr *ah_attr)
अणु
	काष्ठा ib_global_route *grh = rdma_ah_retrieve_grh(ah_attr);
	अगर (rdma_port_get_link_layer(&dev->ib_dev, port) == IB_LINK_LAYER_INFINIBAND)
		grh->sgid_index = slave;
	अन्यथा
		grh->sgid_index += get_slave_base_gid_ix(dev, slave, port);
पूर्ण

अटल व्योम mlx4_ib_multiplex_mad(काष्ठा mlx4_ib_demux_pv_ctx *ctx, काष्ठा ib_wc *wc)
अणु
	काष्ठा mlx4_ib_dev *dev = to_mdev(ctx->ib_dev);
	काष्ठा mlx4_ib_demux_pv_qp *tun_qp = &ctx->qp[MLX4_TUN_WRID_QPN(wc->wr_id)];
	पूर्णांक wr_ix = wc->wr_id & (MLX4_NUM_TUNNEL_BUFS - 1);
	काष्ठा mlx4_tunnel_mad *tunnel = tun_qp->ring[wr_ix].addr;
	काष्ठा mlx4_ib_ah ah;
	काष्ठा rdma_ah_attr ah_attr;
	u8 *slave_id;
	पूर्णांक slave;
	पूर्णांक port;
	u16 vlan_id;
	u8 qos;
	u8 *dmac;
	पूर्णांक sts;

	/* Get slave that sent this packet */
	अगर (wc->src_qp < dev->dev->phys_caps.base_proxy_sqpn ||
	    wc->src_qp >= dev->dev->phys_caps.base_proxy_sqpn + 8 * MLX4_MFUNC_MAX ||
	    (wc->src_qp & 0x1) != ctx->port - 1 ||
	    wc->src_qp & 0x4) अणु
		mlx4_ib_warn(ctx->ib_dev, "can't multiplex bad sqp:%d\n", wc->src_qp);
		वापस;
	पूर्ण
	slave = ((wc->src_qp & ~0x7) - dev->dev->phys_caps.base_proxy_sqpn) / 8;
	अगर (slave != ctx->slave) अणु
		mlx4_ib_warn(ctx->ib_dev, "can't multiplex bad sqp:%d: "
			     "belongs to another slave\n", wc->src_qp);
		वापस;
	पूर्ण

	/* Map transaction ID */
	ib_dma_sync_single_क्रम_cpu(ctx->ib_dev, tun_qp->ring[wr_ix].map,
				   माप (काष्ठा mlx4_tunnel_mad),
				   DMA_FROM_DEVICE);
	चयन (tunnel->mad.mad_hdr.method) अणु
	हाल IB_MGMT_METHOD_SET:
	हाल IB_MGMT_METHOD_GET:
	हाल IB_MGMT_METHOD_REPORT:
	हाल IB_SA_METHOD_GET_TABLE:
	हाल IB_SA_METHOD_DELETE:
	हाल IB_SA_METHOD_GET_MULTI:
	हाल IB_SA_METHOD_GET_TRACE_TBL:
		slave_id = (u8 *) &tunnel->mad.mad_hdr.tid;
		अगर (*slave_id) अणु
			mlx4_ib_warn(ctx->ib_dev, "egress mad has non-null tid msb:%d "
				     "class:%d slave:%d\n", *slave_id,
				     tunnel->mad.mad_hdr.mgmt_class, slave);
			वापस;
		पूर्ण अन्यथा
			*slave_id = slave;
		अवरोध;
	शेष:
		/* nothing */;
	पूर्ण

	/* Class-specअगरic handling */
	चयन (tunnel->mad.mad_hdr.mgmt_class) अणु
	हाल IB_MGMT_CLASS_SUBN_LID_ROUTED:
	हाल IB_MGMT_CLASS_SUBN_सूचीECTED_ROUTE:
		अगर (slave != mlx4_master_func_num(dev->dev) &&
		    !mlx4_vf_smi_enabled(dev->dev, slave, ctx->port))
			वापस;
		अवरोध;
	हाल IB_MGMT_CLASS_SUBN_ADM:
		अगर (mlx4_ib_multiplex_sa_handler(ctx->ib_dev, ctx->port, slave,
			      (काष्ठा ib_sa_mad *) &tunnel->mad))
			वापस;
		अवरोध;
	हाल IB_MGMT_CLASS_CM:
		अगर (mlx4_ib_multiplex_cm_handler(ctx->ib_dev, ctx->port, slave,
			      (काष्ठा ib_mad *) &tunnel->mad))
			वापस;
		अवरोध;
	हाल IB_MGMT_CLASS_DEVICE_MGMT:
		अगर (tunnel->mad.mad_hdr.method != IB_MGMT_METHOD_GET &&
		    tunnel->mad.mad_hdr.method != IB_MGMT_METHOD_SET)
			वापस;
		अवरोध;
	शेष:
		/* Drop unsupported classes क्रम slaves in tunnel mode */
		अगर (slave != mlx4_master_func_num(dev->dev)) अणु
			mlx4_ib_warn(ctx->ib_dev, "dropping unsupported egress mad from class:%d "
				     "for slave:%d\n", tunnel->mad.mad_hdr.mgmt_class, slave);
			वापस;
		पूर्ण
	पूर्ण

	/* We are using standard ib_core services to send the mad, so generate a
	 * stadard address handle by decoding the tunnelled mlx4_ah fields */
	स_नकल(&ah.av, &tunnel->hdr.av, माप (काष्ठा mlx4_av));
	ah.ibah.device = ctx->ib_dev;

	port = be32_to_cpu(ah.av.ib.port_pd) >> 24;
	port = mlx4_slave_convert_port(dev->dev, slave, port);
	अगर (port < 0)
		वापस;
	ah.av.ib.port_pd = cpu_to_be32(port << 24 | (be32_to_cpu(ah.av.ib.port_pd) & 0xffffff));
	ah.ibah.type = rdma_ah_find_type(&dev->ib_dev, port);

	mlx4_ib_query_ah(&ah.ibah, &ah_attr);
	अगर (rdma_ah_get_ah_flags(&ah_attr) & IB_AH_GRH)
		fill_in_real_sgid_index(dev, slave, ctx->port, &ah_attr);
	dmac = rdma_ah_retrieve_dmac(&ah_attr);
	अगर (dmac)
		स_नकल(dmac, tunnel->hdr.mac, ETH_ALEN);
	vlan_id = be16_to_cpu(tunnel->hdr.vlan);
	/* अगर slave have शेष vlan use it */
	अगर (mlx4_get_slave_शेष_vlan(dev->dev, ctx->port, slave,
					&vlan_id, &qos))
		rdma_ah_set_sl(&ah_attr, qos);

	sts = mlx4_ib_send_to_wire(dev, slave, ctx->port,
				   is_proxy_qp0(dev, wc->src_qp, slave) ?
				   IB_QPT_SMI : IB_QPT_GSI,
				   be16_to_cpu(tunnel->hdr.pkey_index),
				   be32_to_cpu(tunnel->hdr.remote_qpn),
				   be32_to_cpu(tunnel->hdr.qkey),
				   &ah_attr, wc->smac, vlan_id, &tunnel->mad);
	अगर (sts)
		pr_debug("failed sending %s to wire on behalf of slave %d (%d)\n",
			 is_proxy_qp0(dev, wc->src_qp, slave) ? "SMI" : "GSI",
			 slave, sts);
पूर्ण

अटल पूर्णांक mlx4_ib_alloc_pv_bufs(काष्ठा mlx4_ib_demux_pv_ctx *ctx,
				 क्रमागत ib_qp_type qp_type, पूर्णांक is_tun)
अणु
	पूर्णांक i;
	काष्ठा mlx4_ib_demux_pv_qp *tun_qp;
	पूर्णांक rx_buf_size, tx_buf_size;
	स्थिर पूर्णांक nmbr_bufs = is_tun ? MLX4_NUM_TUNNEL_BUFS : MLX4_NUM_WIRE_BUFS;

	अगर (qp_type > IB_QPT_GSI)
		वापस -EINVAL;

	tun_qp = &ctx->qp[qp_type];

	tun_qp->ring = kसुस्मृति(nmbr_bufs,
			       माप(काष्ठा mlx4_ib_buf),
			       GFP_KERNEL);
	अगर (!tun_qp->ring)
		वापस -ENOMEM;

	tun_qp->tx_ring = kसुस्मृति(nmbr_bufs,
				  माप (काष्ठा mlx4_ib_tun_tx_buf),
				  GFP_KERNEL);
	अगर (!tun_qp->tx_ring) अणु
		kमुक्त(tun_qp->ring);
		tun_qp->ring = शून्य;
		वापस -ENOMEM;
	पूर्ण

	अगर (is_tun) अणु
		rx_buf_size = माप (काष्ठा mlx4_tunnel_mad);
		tx_buf_size = माप (काष्ठा mlx4_rcv_tunnel_mad);
	पूर्ण अन्यथा अणु
		rx_buf_size = माप (काष्ठा mlx4_mad_rcv_buf);
		tx_buf_size = माप (काष्ठा mlx4_mad_snd_buf);
	पूर्ण

	क्रम (i = 0; i < nmbr_bufs; i++) अणु
		tun_qp->ring[i].addr = kदो_स्मृति(rx_buf_size, GFP_KERNEL);
		अगर (!tun_qp->ring[i].addr)
			जाओ err;
		tun_qp->ring[i].map = ib_dma_map_single(ctx->ib_dev,
							tun_qp->ring[i].addr,
							rx_buf_size,
							DMA_FROM_DEVICE);
		अगर (ib_dma_mapping_error(ctx->ib_dev, tun_qp->ring[i].map)) अणु
			kमुक्त(tun_qp->ring[i].addr);
			जाओ err;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < nmbr_bufs; i++) अणु
		tun_qp->tx_ring[i].buf.addr =
			kदो_स्मृति(tx_buf_size, GFP_KERNEL);
		अगर (!tun_qp->tx_ring[i].buf.addr)
			जाओ tx_err;
		tun_qp->tx_ring[i].buf.map =
			ib_dma_map_single(ctx->ib_dev,
					  tun_qp->tx_ring[i].buf.addr,
					  tx_buf_size,
					  DMA_TO_DEVICE);
		अगर (ib_dma_mapping_error(ctx->ib_dev,
					 tun_qp->tx_ring[i].buf.map)) अणु
			kमुक्त(tun_qp->tx_ring[i].buf.addr);
			जाओ tx_err;
		पूर्ण
		tun_qp->tx_ring[i].ah = शून्य;
	पूर्ण
	spin_lock_init(&tun_qp->tx_lock);
	tun_qp->tx_ix_head = 0;
	tun_qp->tx_ix_tail = 0;
	tun_qp->proxy_qpt = qp_type;

	वापस 0;

tx_err:
	जबतक (i > 0) अणु
		--i;
		ib_dma_unmap_single(ctx->ib_dev, tun_qp->tx_ring[i].buf.map,
				    tx_buf_size, DMA_TO_DEVICE);
		kमुक्त(tun_qp->tx_ring[i].buf.addr);
	पूर्ण
	i = nmbr_bufs;
err:
	जबतक (i > 0) अणु
		--i;
		ib_dma_unmap_single(ctx->ib_dev, tun_qp->ring[i].map,
				    rx_buf_size, DMA_FROM_DEVICE);
		kमुक्त(tun_qp->ring[i].addr);
	पूर्ण
	kमुक्त(tun_qp->tx_ring);
	tun_qp->tx_ring = शून्य;
	kमुक्त(tun_qp->ring);
	tun_qp->ring = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल व्योम mlx4_ib_मुक्त_pv_qp_bufs(काष्ठा mlx4_ib_demux_pv_ctx *ctx,
				     क्रमागत ib_qp_type qp_type, पूर्णांक is_tun)
अणु
	पूर्णांक i;
	काष्ठा mlx4_ib_demux_pv_qp *tun_qp;
	पूर्णांक rx_buf_size, tx_buf_size;
	स्थिर पूर्णांक nmbr_bufs = is_tun ? MLX4_NUM_TUNNEL_BUFS : MLX4_NUM_WIRE_BUFS;

	अगर (qp_type > IB_QPT_GSI)
		वापस;

	tun_qp = &ctx->qp[qp_type];
	अगर (is_tun) अणु
		rx_buf_size = माप (काष्ठा mlx4_tunnel_mad);
		tx_buf_size = माप (काष्ठा mlx4_rcv_tunnel_mad);
	पूर्ण अन्यथा अणु
		rx_buf_size = माप (काष्ठा mlx4_mad_rcv_buf);
		tx_buf_size = माप (काष्ठा mlx4_mad_snd_buf);
	पूर्ण


	क्रम (i = 0; i < nmbr_bufs; i++) अणु
		ib_dma_unmap_single(ctx->ib_dev, tun_qp->ring[i].map,
				    rx_buf_size, DMA_FROM_DEVICE);
		kमुक्त(tun_qp->ring[i].addr);
	पूर्ण

	क्रम (i = 0; i < nmbr_bufs; i++) अणु
		ib_dma_unmap_single(ctx->ib_dev, tun_qp->tx_ring[i].buf.map,
				    tx_buf_size, DMA_TO_DEVICE);
		kमुक्त(tun_qp->tx_ring[i].buf.addr);
		अगर (tun_qp->tx_ring[i].ah)
			rdma_destroy_ah(tun_qp->tx_ring[i].ah, 0);
	पूर्ण
	kमुक्त(tun_qp->tx_ring);
	kमुक्त(tun_qp->ring);
पूर्ण

अटल व्योम mlx4_ib_tunnel_comp_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx4_ib_demux_pv_ctx *ctx;
	काष्ठा mlx4_ib_demux_pv_qp *tun_qp;
	काष्ठा ib_wc wc;
	पूर्णांक ret;
	ctx = container_of(work, काष्ठा mlx4_ib_demux_pv_ctx, work);
	ib_req_notअगरy_cq(ctx->cq, IB_CQ_NEXT_COMP);

	जबतक (ib_poll_cq(ctx->cq, 1, &wc) == 1) अणु
		tun_qp = &ctx->qp[MLX4_TUN_WRID_QPN(wc.wr_id)];
		अगर (wc.status == IB_WC_SUCCESS) अणु
			चयन (wc.opcode) अणु
			हाल IB_WC_RECV:
				mlx4_ib_multiplex_mad(ctx, &wc);
				ret = mlx4_ib_post_pv_qp_buf(ctx, tun_qp,
							     wc.wr_id &
							     (MLX4_NUM_TUNNEL_BUFS - 1));
				अगर (ret)
					pr_err("Failed reposting tunnel "
					       "buf:%lld\n", wc.wr_id);
				अवरोध;
			हाल IB_WC_SEND:
				rdma_destroy_ah(tun_qp->tx_ring[wc.wr_id &
					      (MLX4_NUM_TUNNEL_BUFS - 1)].ah, 0);
				tun_qp->tx_ring[wc.wr_id & (MLX4_NUM_TUNNEL_BUFS - 1)].ah
					= शून्य;
				spin_lock(&tun_qp->tx_lock);
				tun_qp->tx_ix_tail++;
				spin_unlock(&tun_qp->tx_lock);

				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा  अणु
			pr_debug("mlx4_ib: completion error in tunnel: %d."
				 " status = %d, wrid = 0x%llx\n",
				 ctx->slave, wc.status, wc.wr_id);
			अगर (!MLX4_TUN_IS_RECV(wc.wr_id)) अणु
				rdma_destroy_ah(tun_qp->tx_ring[wc.wr_id &
					      (MLX4_NUM_TUNNEL_BUFS - 1)].ah, 0);
				tun_qp->tx_ring[wc.wr_id & (MLX4_NUM_TUNNEL_BUFS - 1)].ah
					= शून्य;
				spin_lock(&tun_qp->tx_lock);
				tun_qp->tx_ix_tail++;
				spin_unlock(&tun_qp->tx_lock);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम pv_qp_event_handler(काष्ठा ib_event *event, व्योम *qp_context)
अणु
	काष्ठा mlx4_ib_demux_pv_ctx *sqp = qp_context;

	/* It's worse than that! He's dead, Jim! */
	pr_err("Fatal error (%d) on a MAD QP on port %d\n",
	       event->event, sqp->port);
पूर्ण

अटल पूर्णांक create_pv_sqp(काष्ठा mlx4_ib_demux_pv_ctx *ctx,
			    क्रमागत ib_qp_type qp_type, पूर्णांक create_tun)
अणु
	पूर्णांक i, ret;
	काष्ठा mlx4_ib_demux_pv_qp *tun_qp;
	काष्ठा mlx4_ib_qp_tunnel_init_attr qp_init_attr;
	काष्ठा ib_qp_attr attr;
	पूर्णांक qp_attr_mask_INIT;
	स्थिर पूर्णांक nmbr_bufs = create_tun ? MLX4_NUM_TUNNEL_BUFS : MLX4_NUM_WIRE_BUFS;

	अगर (qp_type > IB_QPT_GSI)
		वापस -EINVAL;

	tun_qp = &ctx->qp[qp_type];

	स_रखो(&qp_init_attr, 0, माप qp_init_attr);
	qp_init_attr.init_attr.send_cq = ctx->cq;
	qp_init_attr.init_attr.recv_cq = ctx->cq;
	qp_init_attr.init_attr.sq_sig_type = IB_SIGNAL_ALL_WR;
	qp_init_attr.init_attr.cap.max_send_wr = nmbr_bufs;
	qp_init_attr.init_attr.cap.max_recv_wr = nmbr_bufs;
	qp_init_attr.init_attr.cap.max_send_sge = 1;
	qp_init_attr.init_attr.cap.max_recv_sge = 1;
	अगर (create_tun) अणु
		qp_init_attr.init_attr.qp_type = IB_QPT_UD;
		qp_init_attr.init_attr.create_flags = MLX4_IB_SRIOV_TUNNEL_QP;
		qp_init_attr.port = ctx->port;
		qp_init_attr.slave = ctx->slave;
		qp_init_attr.proxy_qp_type = qp_type;
		qp_attr_mask_INIT = IB_QP_STATE | IB_QP_PKEY_INDEX |
			   IB_QP_QKEY | IB_QP_PORT;
	पूर्ण अन्यथा अणु
		qp_init_attr.init_attr.qp_type = qp_type;
		qp_init_attr.init_attr.create_flags = MLX4_IB_SRIOV_SQP;
		qp_attr_mask_INIT = IB_QP_STATE | IB_QP_PKEY_INDEX | IB_QP_QKEY;
	पूर्ण
	qp_init_attr.init_attr.port_num = ctx->port;
	qp_init_attr.init_attr.qp_context = ctx;
	qp_init_attr.init_attr.event_handler = pv_qp_event_handler;
	tun_qp->qp = ib_create_qp(ctx->pd, &qp_init_attr.init_attr);
	अगर (IS_ERR(tun_qp->qp)) अणु
		ret = PTR_ERR(tun_qp->qp);
		tun_qp->qp = शून्य;
		pr_err("Couldn't create %s QP (%d)\n",
		       create_tun ? "tunnel" : "special", ret);
		वापस ret;
	पूर्ण

	स_रखो(&attr, 0, माप attr);
	attr.qp_state = IB_QPS_INIT;
	ret = 0;
	अगर (create_tun)
		ret = find_slave_port_pkey_ix(to_mdev(ctx->ib_dev), ctx->slave,
					      ctx->port, IB_DEFAULT_PKEY_FULL,
					      &attr.pkey_index);
	अगर (ret || !create_tun)
		attr.pkey_index =
			to_mdev(ctx->ib_dev)->pkeys.virt2phys_pkey[ctx->slave][ctx->port - 1][0];
	attr.qkey = IB_QP1_QKEY;
	attr.port_num = ctx->port;
	ret = ib_modअगरy_qp(tun_qp->qp, &attr, qp_attr_mask_INIT);
	अगर (ret) अणु
		pr_err("Couldn't change %s qp state to INIT (%d)\n",
		       create_tun ? "tunnel" : "special", ret);
		जाओ err_qp;
	पूर्ण
	attr.qp_state = IB_QPS_RTR;
	ret = ib_modअगरy_qp(tun_qp->qp, &attr, IB_QP_STATE);
	अगर (ret) अणु
		pr_err("Couldn't change %s qp state to RTR (%d)\n",
		       create_tun ? "tunnel" : "special", ret);
		जाओ err_qp;
	पूर्ण
	attr.qp_state = IB_QPS_RTS;
	attr.sq_psn = 0;
	ret = ib_modअगरy_qp(tun_qp->qp, &attr, IB_QP_STATE | IB_QP_SQ_PSN);
	अगर (ret) अणु
		pr_err("Couldn't change %s qp state to RTS (%d)\n",
		       create_tun ? "tunnel" : "special", ret);
		जाओ err_qp;
	पूर्ण

	क्रम (i = 0; i < nmbr_bufs; i++) अणु
		ret = mlx4_ib_post_pv_qp_buf(ctx, tun_qp, i);
		अगर (ret) अणु
			pr_err(" mlx4_ib_post_pv_buf error"
			       " (err = %d, i = %d)\n", ret, i);
			जाओ err_qp;
		पूर्ण
	पूर्ण
	वापस 0;

err_qp:
	ib_destroy_qp(tun_qp->qp);
	tun_qp->qp = शून्य;
	वापस ret;
पूर्ण

/*
 * IB MAD completion callback क्रम real SQPs
 */
अटल व्योम mlx4_ib_sqp_comp_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx4_ib_demux_pv_ctx *ctx;
	काष्ठा mlx4_ib_demux_pv_qp *sqp;
	काष्ठा ib_wc wc;
	काष्ठा ib_grh *grh;
	काष्ठा ib_mad *mad;

	ctx = container_of(work, काष्ठा mlx4_ib_demux_pv_ctx, work);
	ib_req_notअगरy_cq(ctx->cq, IB_CQ_NEXT_COMP);

	जबतक (mlx4_ib_poll_cq(ctx->cq, 1, &wc) == 1) अणु
		sqp = &ctx->qp[MLX4_TUN_WRID_QPN(wc.wr_id)];
		अगर (wc.status == IB_WC_SUCCESS) अणु
			चयन (wc.opcode) अणु
			हाल IB_WC_SEND:
				kमुक्त(sqp->tx_ring[wc.wr_id &
				      (MLX4_NUM_WIRE_BUFS - 1)].ah);
				sqp->tx_ring[wc.wr_id & (MLX4_NUM_WIRE_BUFS - 1)].ah
					= शून्य;
				spin_lock(&sqp->tx_lock);
				sqp->tx_ix_tail++;
				spin_unlock(&sqp->tx_lock);
				अवरोध;
			हाल IB_WC_RECV:
				mad = (काष्ठा ib_mad *) &(((काष्ठा mlx4_mad_rcv_buf *)
						(sqp->ring[wc.wr_id &
						(MLX4_NUM_WIRE_BUFS - 1)].addr))->payload);
				grh = &(((काष्ठा mlx4_mad_rcv_buf *)
						(sqp->ring[wc.wr_id &
						(MLX4_NUM_WIRE_BUFS - 1)].addr))->grh);
				mlx4_ib_demux_mad(ctx->ib_dev, ctx->port, &wc, grh, mad);
				अगर (mlx4_ib_post_pv_qp_buf(ctx, sqp, wc.wr_id &
							   (MLX4_NUM_WIRE_BUFS - 1)))
					pr_err("Failed reposting SQP "
					       "buf:%lld\n", wc.wr_id);
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा  अणु
			pr_debug("mlx4_ib: completion error in tunnel: %d."
				 " status = %d, wrid = 0x%llx\n",
				 ctx->slave, wc.status, wc.wr_id);
			अगर (!MLX4_TUN_IS_RECV(wc.wr_id)) अणु
				kमुक्त(sqp->tx_ring[wc.wr_id &
				      (MLX4_NUM_WIRE_BUFS - 1)].ah);
				sqp->tx_ring[wc.wr_id & (MLX4_NUM_WIRE_BUFS - 1)].ah
					= शून्य;
				spin_lock(&sqp->tx_lock);
				sqp->tx_ix_tail++;
				spin_unlock(&sqp->tx_lock);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक alloc_pv_object(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave, पूर्णांक port,
			       काष्ठा mlx4_ib_demux_pv_ctx **ret_ctx)
अणु
	काष्ठा mlx4_ib_demux_pv_ctx *ctx;

	*ret_ctx = शून्य;
	ctx = kzalloc(माप (काष्ठा mlx4_ib_demux_pv_ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	ctx->ib_dev = &dev->ib_dev;
	ctx->port = port;
	ctx->slave = slave;
	*ret_ctx = ctx;
	वापस 0;
पूर्ण

अटल व्योम मुक्त_pv_object(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave, पूर्णांक port)
अणु
	अगर (dev->sriov.demux[port - 1].tun[slave]) अणु
		kमुक्त(dev->sriov.demux[port - 1].tun[slave]);
		dev->sriov.demux[port - 1].tun[slave] = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक create_pv_resources(काष्ठा ib_device *ibdev, पूर्णांक slave, पूर्णांक port,
			       पूर्णांक create_tun, काष्ठा mlx4_ib_demux_pv_ctx *ctx)
अणु
	पूर्णांक ret, cq_size;
	काष्ठा ib_cq_init_attr cq_attr = अणुपूर्ण;
	स्थिर पूर्णांक nmbr_bufs = create_tun ? MLX4_NUM_TUNNEL_BUFS : MLX4_NUM_WIRE_BUFS;

	अगर (ctx->state != DEMUX_PV_STATE_DOWN)
		वापस -EEXIST;

	ctx->state = DEMUX_PV_STATE_STARTING;
	/* have QP0 only अगर link layer is IB */
	अगर (rdma_port_get_link_layer(ibdev, ctx->port) ==
	    IB_LINK_LAYER_INFINIBAND)
		ctx->has_smi = 1;

	अगर (ctx->has_smi) अणु
		ret = mlx4_ib_alloc_pv_bufs(ctx, IB_QPT_SMI, create_tun);
		अगर (ret) अणु
			pr_err("Failed allocating qp0 tunnel bufs (%d)\n", ret);
			जाओ err_out;
		पूर्ण
	पूर्ण

	ret = mlx4_ib_alloc_pv_bufs(ctx, IB_QPT_GSI, create_tun);
	अगर (ret) अणु
		pr_err("Failed allocating qp1 tunnel bufs (%d)\n", ret);
		जाओ err_out_qp0;
	पूर्ण

	cq_size = 2 * nmbr_bufs;
	अगर (ctx->has_smi)
		cq_size *= 2;

	cq_attr.cqe = cq_size;
	ctx->cq = ib_create_cq(ctx->ib_dev,
			       create_tun ? mlx4_ib_tunnel_comp_handler : mlx4_ib_wire_comp_handler,
			       शून्य, ctx, &cq_attr);
	अगर (IS_ERR(ctx->cq)) अणु
		ret = PTR_ERR(ctx->cq);
		pr_err("Couldn't create tunnel CQ (%d)\n", ret);
		जाओ err_buf;
	पूर्ण

	ctx->pd = ib_alloc_pd(ctx->ib_dev, 0);
	अगर (IS_ERR(ctx->pd)) अणु
		ret = PTR_ERR(ctx->pd);
		pr_err("Couldn't create tunnel PD (%d)\n", ret);
		जाओ err_cq;
	पूर्ण

	अगर (ctx->has_smi) अणु
		ret = create_pv_sqp(ctx, IB_QPT_SMI, create_tun);
		अगर (ret) अणु
			pr_err("Couldn't create %s QP0 (%d)\n",
			       create_tun ? "tunnel for" : "",  ret);
			जाओ err_pd;
		पूर्ण
	पूर्ण

	ret = create_pv_sqp(ctx, IB_QPT_GSI, create_tun);
	अगर (ret) अणु
		pr_err("Couldn't create %s QP1 (%d)\n",
		       create_tun ? "tunnel for" : "",  ret);
		जाओ err_qp0;
	पूर्ण

	अगर (create_tun)
		INIT_WORK(&ctx->work, mlx4_ib_tunnel_comp_worker);
	अन्यथा
		INIT_WORK(&ctx->work, mlx4_ib_sqp_comp_worker);

	ctx->wq = to_mdev(ibdev)->sriov.demux[port - 1].wq;
	ctx->wi_wq = to_mdev(ibdev)->sriov.demux[port - 1].wi_wq;

	ret = ib_req_notअगरy_cq(ctx->cq, IB_CQ_NEXT_COMP);
	अगर (ret) अणु
		pr_err("Couldn't arm tunnel cq (%d)\n", ret);
		जाओ err_wq;
	पूर्ण
	ctx->state = DEMUX_PV_STATE_ACTIVE;
	वापस 0;

err_wq:
	ctx->wq = शून्य;
	ib_destroy_qp(ctx->qp[1].qp);
	ctx->qp[1].qp = शून्य;


err_qp0:
	अगर (ctx->has_smi)
		ib_destroy_qp(ctx->qp[0].qp);
	ctx->qp[0].qp = शून्य;

err_pd:
	ib_dealloc_pd(ctx->pd);
	ctx->pd = शून्य;

err_cq:
	ib_destroy_cq(ctx->cq);
	ctx->cq = शून्य;

err_buf:
	mlx4_ib_मुक्त_pv_qp_bufs(ctx, IB_QPT_GSI, create_tun);

err_out_qp0:
	अगर (ctx->has_smi)
		mlx4_ib_मुक्त_pv_qp_bufs(ctx, IB_QPT_SMI, create_tun);
err_out:
	ctx->state = DEMUX_PV_STATE_DOWN;
	वापस ret;
पूर्ण

अटल व्योम destroy_pv_resources(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave, पूर्णांक port,
				 काष्ठा mlx4_ib_demux_pv_ctx *ctx, पूर्णांक flush)
अणु
	अगर (!ctx)
		वापस;
	अगर (ctx->state > DEMUX_PV_STATE_DOWN) अणु
		ctx->state = DEMUX_PV_STATE_DOWNING;
		अगर (flush)
			flush_workqueue(ctx->wq);
		अगर (ctx->has_smi) अणु
			ib_destroy_qp(ctx->qp[0].qp);
			ctx->qp[0].qp = शून्य;
			mlx4_ib_मुक्त_pv_qp_bufs(ctx, IB_QPT_SMI, 1);
		पूर्ण
		ib_destroy_qp(ctx->qp[1].qp);
		ctx->qp[1].qp = शून्य;
		mlx4_ib_मुक्त_pv_qp_bufs(ctx, IB_QPT_GSI, 1);
		ib_dealloc_pd(ctx->pd);
		ctx->pd = शून्य;
		ib_destroy_cq(ctx->cq);
		ctx->cq = शून्य;
		ctx->state = DEMUX_PV_STATE_DOWN;
	पूर्ण
पूर्ण

अटल पूर्णांक mlx4_ib_tunnels_update(काष्ठा mlx4_ib_dev *dev, पूर्णांक slave,
				  पूर्णांक port, पूर्णांक करो_init)
अणु
	पूर्णांक ret = 0;

	अगर (!करो_init) अणु
		clean_vf_mcast(&dev->sriov.demux[port - 1], slave);
		/* क्रम master, destroy real sqp resources */
		अगर (slave == mlx4_master_func_num(dev->dev))
			destroy_pv_resources(dev, slave, port,
					     dev->sriov.sqps[port - 1], 1);
		/* destroy the tunnel qp resources */
		destroy_pv_resources(dev, slave, port,
				     dev->sriov.demux[port - 1].tun[slave], 1);
		वापस 0;
	पूर्ण

	/* create the tunnel qp resources */
	ret = create_pv_resources(&dev->ib_dev, slave, port, 1,
				  dev->sriov.demux[port - 1].tun[slave]);

	/* क्रम master, create the real sqp resources */
	अगर (!ret && slave == mlx4_master_func_num(dev->dev))
		ret = create_pv_resources(&dev->ib_dev, slave, port, 0,
					  dev->sriov.sqps[port - 1]);
	वापस ret;
पूर्ण

व्योम mlx4_ib_tunnels_update_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlx4_ib_demux_work *dmxw;

	dmxw = container_of(work, काष्ठा mlx4_ib_demux_work, work);
	mlx4_ib_tunnels_update(dmxw->dev, dmxw->slave, (पूर्णांक) dmxw->port,
			       dmxw->करो_init);
	kमुक्त(dmxw);
	वापस;
पूर्ण

अटल पूर्णांक mlx4_ib_alloc_demux_ctx(काष्ठा mlx4_ib_dev *dev,
				       काष्ठा mlx4_ib_demux_ctx *ctx,
				       पूर्णांक port)
अणु
	अक्षर name[12];
	पूर्णांक ret = 0;
	पूर्णांक i;

	ctx->tun = kसुस्मृति(dev->dev->caps.sqp_demux,
			   माप (काष्ठा mlx4_ib_demux_pv_ctx *), GFP_KERNEL);
	अगर (!ctx->tun)
		वापस -ENOMEM;

	ctx->dev = dev;
	ctx->port = port;
	ctx->ib_dev = &dev->ib_dev;

	क्रम (i = 0;
	     i < min(dev->dev->caps.sqp_demux,
	     (u16)(dev->dev->persist->num_vfs + 1));
	     i++) अणु
		काष्ठा mlx4_active_ports actv_ports =
			mlx4_get_active_ports(dev->dev, i);

		अगर (!test_bit(port - 1, actv_ports.ports))
			जारी;

		ret = alloc_pv_object(dev, i, port, &ctx->tun[i]);
		अगर (ret) अणु
			ret = -ENOMEM;
			जाओ err_mcg;
		पूर्ण
	पूर्ण

	ret = mlx4_ib_mcg_port_init(ctx);
	अगर (ret) अणु
		pr_err("Failed initializing mcg para-virt (%d)\n", ret);
		जाओ err_mcg;
	पूर्ण

	snम_लिखो(name, माप(name), "mlx4_ibt%d", port);
	ctx->wq = alloc_ordered_workqueue(name, WQ_MEM_RECLAIM);
	अगर (!ctx->wq) अणु
		pr_err("Failed to create tunnelling WQ for port %d\n", port);
		ret = -ENOMEM;
		जाओ err_wq;
	पूर्ण

	snम_लिखो(name, माप(name), "mlx4_ibwi%d", port);
	ctx->wi_wq = alloc_ordered_workqueue(name, WQ_MEM_RECLAIM);
	अगर (!ctx->wi_wq) अणु
		pr_err("Failed to create wire WQ for port %d\n", port);
		ret = -ENOMEM;
		जाओ err_wiwq;
	पूर्ण

	snम_लिखो(name, माप(name), "mlx4_ibud%d", port);
	ctx->ud_wq = alloc_ordered_workqueue(name, WQ_MEM_RECLAIM);
	अगर (!ctx->ud_wq) अणु
		pr_err("Failed to create up/down WQ for port %d\n", port);
		ret = -ENOMEM;
		जाओ err_udwq;
	पूर्ण

	वापस 0;

err_udwq:
	destroy_workqueue(ctx->wi_wq);
	ctx->wi_wq = शून्य;

err_wiwq:
	destroy_workqueue(ctx->wq);
	ctx->wq = शून्य;

err_wq:
	mlx4_ib_mcg_port_cleanup(ctx, 1);
err_mcg:
	क्रम (i = 0; i < dev->dev->caps.sqp_demux; i++)
		मुक्त_pv_object(dev, i, port);
	kमुक्त(ctx->tun);
	ctx->tun = शून्य;
	वापस ret;
पूर्ण

अटल व्योम mlx4_ib_मुक्त_sqp_ctx(काष्ठा mlx4_ib_demux_pv_ctx *sqp_ctx)
अणु
	अगर (sqp_ctx->state > DEMUX_PV_STATE_DOWN) अणु
		sqp_ctx->state = DEMUX_PV_STATE_DOWNING;
		flush_workqueue(sqp_ctx->wq);
		अगर (sqp_ctx->has_smi) अणु
			ib_destroy_qp(sqp_ctx->qp[0].qp);
			sqp_ctx->qp[0].qp = शून्य;
			mlx4_ib_मुक्त_pv_qp_bufs(sqp_ctx, IB_QPT_SMI, 0);
		पूर्ण
		ib_destroy_qp(sqp_ctx->qp[1].qp);
		sqp_ctx->qp[1].qp = शून्य;
		mlx4_ib_मुक्त_pv_qp_bufs(sqp_ctx, IB_QPT_GSI, 0);
		ib_dealloc_pd(sqp_ctx->pd);
		sqp_ctx->pd = शून्य;
		ib_destroy_cq(sqp_ctx->cq);
		sqp_ctx->cq = शून्य;
		sqp_ctx->state = DEMUX_PV_STATE_DOWN;
	पूर्ण
पूर्ण

अटल व्योम mlx4_ib_मुक्त_demux_ctx(काष्ठा mlx4_ib_demux_ctx *ctx)
अणु
	पूर्णांक i;
	अगर (ctx) अणु
		काष्ठा mlx4_ib_dev *dev = to_mdev(ctx->ib_dev);
		mlx4_ib_mcg_port_cleanup(ctx, 1);
		क्रम (i = 0; i < dev->dev->caps.sqp_demux; i++) अणु
			अगर (!ctx->tun[i])
				जारी;
			अगर (ctx->tun[i]->state > DEMUX_PV_STATE_DOWN)
				ctx->tun[i]->state = DEMUX_PV_STATE_DOWNING;
		पूर्ण
		flush_workqueue(ctx->wq);
		flush_workqueue(ctx->wi_wq);
		क्रम (i = 0; i < dev->dev->caps.sqp_demux; i++) अणु
			destroy_pv_resources(dev, i, ctx->port, ctx->tun[i], 0);
			मुक्त_pv_object(dev, i, ctx->port);
		पूर्ण
		kमुक्त(ctx->tun);
		destroy_workqueue(ctx->ud_wq);
		destroy_workqueue(ctx->wi_wq);
		destroy_workqueue(ctx->wq);
	पूर्ण
पूर्ण

अटल व्योम mlx4_ib_master_tunnels(काष्ठा mlx4_ib_dev *dev, पूर्णांक करो_init)
अणु
	पूर्णांक i;

	अगर (!mlx4_is_master(dev->dev))
		वापस;
	/* initialize or tear करोwn tunnel QPs क्रम the master */
	क्रम (i = 0; i < dev->dev->caps.num_ports; i++)
		mlx4_ib_tunnels_update(dev, mlx4_master_func_num(dev->dev), i + 1, करो_init);
	वापस;
पूर्ण

पूर्णांक mlx4_ib_init_sriov(काष्ठा mlx4_ib_dev *dev)
अणु
	पूर्णांक i = 0;
	पूर्णांक err;

	अगर (!mlx4_is_mfunc(dev->dev))
		वापस 0;

	dev->sriov.is_going_करोwn = 0;
	spin_lock_init(&dev->sriov.going_करोwn_lock);
	mlx4_ib_cm_paravirt_init(dev);

	mlx4_ib_warn(&dev->ib_dev, "multi-function enabled\n");

	अगर (mlx4_is_slave(dev->dev)) अणु
		mlx4_ib_warn(&dev->ib_dev, "operating in qp1 tunnel mode\n");
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < dev->dev->caps.sqp_demux; i++) अणु
		अगर (i == mlx4_master_func_num(dev->dev))
			mlx4_put_slave_node_guid(dev->dev, i, dev->ib_dev.node_guid);
		अन्यथा
			mlx4_put_slave_node_guid(dev->dev, i, mlx4_ib_gen_node_guid());
	पूर्ण

	err = mlx4_ib_init_alias_guid_service(dev);
	अगर (err) अणु
		mlx4_ib_warn(&dev->ib_dev, "Failed init alias guid process.\n");
		जाओ paravirt_err;
	पूर्ण
	err = mlx4_ib_device_रेजिस्टर_sysfs(dev);
	अगर (err) अणु
		mlx4_ib_warn(&dev->ib_dev, "Failed to register sysfs\n");
		जाओ sysfs_err;
	पूर्ण

	mlx4_ib_warn(&dev->ib_dev, "initializing demux service for %d qp1 clients\n",
		     dev->dev->caps.sqp_demux);
	क्रम (i = 0; i < dev->num_ports; i++) अणु
		जोड़ ib_gid gid;
		err = __mlx4_ib_query_gid(&dev->ib_dev, i + 1, 0, &gid, 1);
		अगर (err)
			जाओ demux_err;
		dev->sriov.demux[i].guid_cache[0] = gid.global.पूर्णांकerface_id;
		atomic64_set(&dev->sriov.demux[i].subnet_prefix,
			     be64_to_cpu(gid.global.subnet_prefix));
		err = alloc_pv_object(dev, mlx4_master_func_num(dev->dev), i + 1,
				      &dev->sriov.sqps[i]);
		अगर (err)
			जाओ demux_err;
		err = mlx4_ib_alloc_demux_ctx(dev, &dev->sriov.demux[i], i + 1);
		अगर (err)
			जाओ मुक्त_pv;
	पूर्ण
	mlx4_ib_master_tunnels(dev, 1);
	वापस 0;

मुक्त_pv:
	मुक्त_pv_object(dev, mlx4_master_func_num(dev->dev), i + 1);
demux_err:
	जबतक (--i >= 0) अणु
		मुक्त_pv_object(dev, mlx4_master_func_num(dev->dev), i + 1);
		mlx4_ib_मुक्त_demux_ctx(&dev->sriov.demux[i]);
	पूर्ण
	mlx4_ib_device_unरेजिस्टर_sysfs(dev);

sysfs_err:
	mlx4_ib_destroy_alias_guid_service(dev);

paravirt_err:
	mlx4_ib_cm_paravirt_clean(dev, -1);

	वापस err;
पूर्ण

व्योम mlx4_ib_बंद_sriov(काष्ठा mlx4_ib_dev *dev)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	अगर (!mlx4_is_mfunc(dev->dev))
		वापस;

	spin_lock_irqsave(&dev->sriov.going_करोwn_lock, flags);
	dev->sriov.is_going_करोwn = 1;
	spin_unlock_irqrestore(&dev->sriov.going_करोwn_lock, flags);
	अगर (mlx4_is_master(dev->dev)) अणु
		क्रम (i = 0; i < dev->num_ports; i++) अणु
			flush_workqueue(dev->sriov.demux[i].ud_wq);
			mlx4_ib_मुक्त_sqp_ctx(dev->sriov.sqps[i]);
			kमुक्त(dev->sriov.sqps[i]);
			dev->sriov.sqps[i] = शून्य;
			mlx4_ib_मुक्त_demux_ctx(&dev->sriov.demux[i]);
		पूर्ण

		mlx4_ib_cm_paravirt_clean(dev, -1);
		mlx4_ib_destroy_alias_guid_service(dev);
		mlx4_ib_device_unरेजिस्टर_sysfs(dev);
	पूर्ण
पूर्ण
