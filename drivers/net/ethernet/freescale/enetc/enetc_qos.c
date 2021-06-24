<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0+ OR BSD-3-Clause)
/* Copyright 2019 NXP */

#समावेश "enetc.h"

#समावेश <net/pkt_sched.h>
#समावेश <linux/math64.h>
#समावेश <linux/refcount.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/tc_act/tc_gate.h>

अटल u16 enetc_get_max_gcl_len(काष्ठा enetc_hw *hw)
अणु
	वापस enetc_rd(hw, ENETC_QBV_PTGCAPR_OFFSET)
		& ENETC_QBV_MAX_GCL_LEN_MASK;
पूर्ण

व्योम enetc_sched_speed_set(काष्ठा enetc_ndev_priv *priv, पूर्णांक speed)
अणु
	u32 old_speed = priv->speed;
	u32 pspeed;

	अगर (speed == old_speed)
		वापस;

	चयन (speed) अणु
	हाल SPEED_1000:
		pspeed = ENETC_PMR_PSPEED_1000M;
		अवरोध;
	हाल SPEED_2500:
		pspeed = ENETC_PMR_PSPEED_2500M;
		अवरोध;
	हाल SPEED_100:
		pspeed = ENETC_PMR_PSPEED_100M;
		अवरोध;
	हाल SPEED_10:
	शेष:
		pspeed = ENETC_PMR_PSPEED_10M;
	पूर्ण

	priv->speed = speed;
	enetc_port_wr(&priv->si->hw, ENETC_PMR,
		      (enetc_port_rd(&priv->si->hw, ENETC_PMR)
		      & (~ENETC_PMR_PSPEED_MASK))
		      | pspeed);
पूर्ण

अटल पूर्णांक enetc_setup_taprio(काष्ठा net_device *ndev,
			      काष्ठा tc_taprio_qopt_offload *admin_conf)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा enetc_cbd cbd = अणु.cmd = 0पूर्ण;
	काष्ठा tgs_gcl_conf *gcl_config;
	काष्ठा tgs_gcl_data *gcl_data;
	काष्ठा gce *gce;
	dma_addr_t dma;
	u16 data_size;
	u16 gcl_len;
	u32 tge;
	पूर्णांक err;
	पूर्णांक i;

	अगर (admin_conf->num_entries > enetc_get_max_gcl_len(&priv->si->hw))
		वापस -EINVAL;
	gcl_len = admin_conf->num_entries;

	tge = enetc_rd(&priv->si->hw, ENETC_QBV_PTGCR_OFFSET);
	अगर (!admin_conf->enable) अणु
		enetc_wr(&priv->si->hw,
			 ENETC_QBV_PTGCR_OFFSET,
			 tge & (~ENETC_QBV_TGE));
		वापस 0;
	पूर्ण

	अगर (admin_conf->cycle_समय > U32_MAX ||
	    admin_conf->cycle_समय_extension > U32_MAX)
		वापस -EINVAL;

	/* Configure the (administrative) gate control list using the
	 * control BD descriptor.
	 */
	gcl_config = &cbd.gcl_conf;

	data_size = काष्ठा_size(gcl_data, entry, gcl_len);
	gcl_data = kzalloc(data_size, __GFP_DMA | GFP_KERNEL);
	अगर (!gcl_data)
		वापस -ENOMEM;

	gce = (काष्ठा gce *)(gcl_data + 1);

	/* Set all gates खोलो as शेष */
	gcl_config->atc = 0xff;
	gcl_config->acl_len = cpu_to_le16(gcl_len);

	gcl_data->btl = cpu_to_le32(lower_32_bits(admin_conf->base_समय));
	gcl_data->bth = cpu_to_le32(upper_32_bits(admin_conf->base_समय));
	gcl_data->ct = cpu_to_le32(admin_conf->cycle_समय);
	gcl_data->cte = cpu_to_le32(admin_conf->cycle_समय_extension);

	क्रम (i = 0; i < gcl_len; i++) अणु
		काष्ठा tc_taprio_sched_entry *temp_entry;
		काष्ठा gce *temp_gce = gce + i;

		temp_entry = &admin_conf->entries[i];

		temp_gce->gate = (u8)temp_entry->gate_mask;
		temp_gce->period = cpu_to_le32(temp_entry->पूर्णांकerval);
	पूर्ण

	cbd.length = cpu_to_le16(data_size);
	cbd.status_flags = 0;

	dma = dma_map_single(&priv->si->pdev->dev, gcl_data,
			     data_size, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&priv->si->pdev->dev, dma)) अणु
		netdev_err(priv->si->ndev, "DMA mapping failed!\n");
		kमुक्त(gcl_data);
		वापस -ENOMEM;
	पूर्ण

	cbd.addr[0] = cpu_to_le32(lower_32_bits(dma));
	cbd.addr[1] = cpu_to_le32(upper_32_bits(dma));
	cbd.cls = BDCR_CMD_PORT_GCL;
	cbd.status_flags = 0;

	enetc_wr(&priv->si->hw, ENETC_QBV_PTGCR_OFFSET,
		 tge | ENETC_QBV_TGE);

	err = enetc_send_cmd(priv->si, &cbd);
	अगर (err)
		enetc_wr(&priv->si->hw,
			 ENETC_QBV_PTGCR_OFFSET,
			 tge & (~ENETC_QBV_TGE));

	dma_unmap_single(&priv->si->pdev->dev, dma, data_size, DMA_TO_DEVICE);
	kमुक्त(gcl_data);

	वापस err;
पूर्ण

पूर्णांक enetc_setup_tc_taprio(काष्ठा net_device *ndev, व्योम *type_data)
अणु
	काष्ठा tc_taprio_qopt_offload *taprio = type_data;
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	पूर्णांक err;
	पूर्णांक i;

	/* TSD and Qbv are mutually exclusive in hardware */
	क्रम (i = 0; i < priv->num_tx_rings; i++)
		अगर (priv->tx_ring[i]->tsd_enable)
			वापस -EBUSY;

	क्रम (i = 0; i < priv->num_tx_rings; i++)
		enetc_set_bdr_prio(&priv->si->hw,
				   priv->tx_ring[i]->index,
				   taprio->enable ? i : 0);

	err = enetc_setup_taprio(ndev, taprio);

	अगर (err)
		क्रम (i = 0; i < priv->num_tx_rings; i++)
			enetc_set_bdr_prio(&priv->si->hw,
					   priv->tx_ring[i]->index,
					   taprio->enable ? 0 : i);

	वापस err;
पूर्ण

अटल u32 enetc_get_cbs_enable(काष्ठा enetc_hw *hw, u8 tc)
अणु
	वापस enetc_port_rd(hw, ENETC_PTCCBSR0(tc)) & ENETC_CBSE;
पूर्ण

अटल u8 enetc_get_cbs_bw(काष्ठा enetc_hw *hw, u8 tc)
अणु
	वापस enetc_port_rd(hw, ENETC_PTCCBSR0(tc)) & ENETC_CBS_BW_MASK;
पूर्ण

पूर्णांक enetc_setup_tc_cbs(काष्ठा net_device *ndev, व्योम *type_data)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा tc_cbs_qopt_offload *cbs = type_data;
	u32 port_transmit_rate = priv->speed;
	u8 tc_nums = netdev_get_num_tc(ndev);
	काष्ठा enetc_si *si = priv->si;
	u32 hi_credit_bit, hi_credit_reg;
	u32 max_पूर्णांकerference_size;
	u32 port_frame_max_size;
	u8 tc = cbs->queue;
	u8 prio_top, prio_next;
	पूर्णांक bw_sum = 0;
	u8 bw;

	prio_top = netdev_get_prio_tc_map(ndev, tc_nums - 1);
	prio_next = netdev_get_prio_tc_map(ndev, tc_nums - 2);

	/* Support highest prio and second prio tc in cbs mode */
	अगर (tc != prio_top && tc != prio_next)
		वापस -EOPNOTSUPP;

	अगर (!cbs->enable) अणु
		/* Make sure the other TC that are numerically
		 * lower than this TC have been disabled.
		 */
		अगर (tc == prio_top &&
		    enetc_get_cbs_enable(&si->hw, prio_next)) अणु
			dev_err(&ndev->dev,
				"Disable TC%d before disable TC%d\n",
				prio_next, tc);
			वापस -EINVAL;
		पूर्ण

		enetc_port_wr(&si->hw, ENETC_PTCCBSR1(tc), 0);
		enetc_port_wr(&si->hw, ENETC_PTCCBSR0(tc), 0);

		वापस 0;
	पूर्ण

	अगर (cbs->idleslope - cbs->sendslope != port_transmit_rate * 1000L ||
	    cbs->idleslope < 0 || cbs->sendslope > 0)
		वापस -EOPNOTSUPP;

	port_frame_max_size = ndev->mtu + VLAN_ETH_HLEN + ETH_FCS_LEN;

	bw = cbs->idleslope / (port_transmit_rate * 10UL);

	/* Make sure the other TC that are numerically
	 * higher than this TC have been enabled.
	 */
	अगर (tc == prio_next) अणु
		अगर (!enetc_get_cbs_enable(&si->hw, prio_top)) अणु
			dev_err(&ndev->dev,
				"Enable TC%d first before enable TC%d\n",
				prio_top, prio_next);
			वापस -EINVAL;
		पूर्ण
		bw_sum += enetc_get_cbs_bw(&si->hw, prio_top);
	पूर्ण

	अगर (bw_sum + bw >= 100) अणु
		dev_err(&ndev->dev,
			"The sum of all CBS Bandwidth can't exceed 100\n");
		वापस -EINVAL;
	पूर्ण

	enetc_port_rd(&si->hw, ENETC_PTCMSDUR(tc));

	/* For top prio TC, the max_पूर्णांकerfrence_size is maxSizedFrame.
	 *
	 * For next prio TC, the max_पूर्णांकerfrence_size is calculated as below:
	 *
	 *      max_पूर्णांकerference_size = M0 + Ma + Ra * M0 / (R0 - Ra)
	 *
	 *	- RA: idleSlope क्रम AVB Class A
	 *	- R0: port transmit rate
	 *	- M0: maximum sized frame क्रम the port
	 *	- MA: maximum sized frame क्रम AVB Class A
	 */

	अगर (tc == prio_top) अणु
		max_पूर्णांकerference_size = port_frame_max_size * 8;
	पूर्ण अन्यथा अणु
		u32 m0, ma, r0, ra;

		m0 = port_frame_max_size * 8;
		ma = enetc_port_rd(&si->hw, ENETC_PTCMSDUR(prio_top)) * 8;
		ra = enetc_get_cbs_bw(&si->hw, prio_top) *
			port_transmit_rate * 10000ULL;
		r0 = port_transmit_rate * 1000000ULL;
		max_पूर्णांकerference_size = m0 + ma +
			(u32)भाग_u64((u64)ra * m0, r0 - ra);
	पूर्ण

	/* hiCredit bits calculate by:
	 *
	 * maxSizedFrame * (idleSlope/portTxRate)
	 */
	hi_credit_bit = max_पूर्णांकerference_size * bw / 100;

	/* hiCredit bits to hiCredit रेजिस्टर need to calculated as:
	 *
	 * (enetClockFrequency / portTransmitRate) * 100
	 */
	hi_credit_reg = (u32)भाग_u64((ENETC_CLK * 100ULL) * hi_credit_bit,
				     port_transmit_rate * 1000000ULL);

	enetc_port_wr(&si->hw, ENETC_PTCCBSR1(tc), hi_credit_reg);

	/* Set bw रेजिस्टर and enable this traffic class */
	enetc_port_wr(&si->hw, ENETC_PTCCBSR0(tc), bw | ENETC_CBSE);

	वापस 0;
पूर्ण

पूर्णांक enetc_setup_tc_txसमय(काष्ठा net_device *ndev, व्योम *type_data)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा tc_etf_qopt_offload *qopt = type_data;
	u8 tc_nums = netdev_get_num_tc(ndev);
	पूर्णांक tc;

	अगर (!tc_nums)
		वापस -EOPNOTSUPP;

	tc = qopt->queue;

	अगर (tc < 0 || tc >= priv->num_tx_rings)
		वापस -EINVAL;

	/* Do not support TXSTART and TX CSUM offload simutaniously */
	अगर (ndev->features & NETIF_F_CSUM_MASK)
		वापस -EBUSY;

	/* TSD and Qbv are mutually exclusive in hardware */
	अगर (enetc_rd(&priv->si->hw, ENETC_QBV_PTGCR_OFFSET) & ENETC_QBV_TGE)
		वापस -EBUSY;

	priv->tx_ring[tc]->tsd_enable = qopt->enable;
	enetc_port_wr(&priv->si->hw, ENETC_PTCTSDR(tc),
		      qopt->enable ? ENETC_TSDE : 0);

	वापस 0;
पूर्ण

क्रमागत streamid_type अणु
	STREAMID_TYPE_RESERVED = 0,
	STREAMID_TYPE_शून्य,
	STREAMID_TYPE_SMAC,
पूर्ण;

क्रमागत streamid_vlan_tagged अणु
	STREAMID_VLAN_RESERVED = 0,
	STREAMID_VLAN_TAGGED,
	STREAMID_VLAN_UNTAGGED,
	STREAMID_VLAN_ALL,
पूर्ण;

#घोषणा ENETC_PSFP_WILDCARD -1
#घोषणा HANDLE_OFFSET 100

क्रमागत क्रमward_type अणु
	FILTER_ACTION_TYPE_PSFP = BIT(0),
	FILTER_ACTION_TYPE_ACL = BIT(1),
	FILTER_ACTION_TYPE_BOTH = GENMASK(1, 0),
पूर्ण;

/* This is क्रम limit output type क्रम input actions */
काष्ठा actions_fwd अणु
	u64 actions;
	u64 keys;	/* include the must needed keys */
	क्रमागत क्रमward_type output;
पूर्ण;

काष्ठा psfp_streamfilter_counters अणु
	u64 matching_frames_count;
	u64 passing_frames_count;
	u64 not_passing_frames_count;
	u64 passing_sdu_count;
	u64 not_passing_sdu_count;
	u64 red_frames_count;
पूर्ण;

काष्ठा enetc_streamid अणु
	u32 index;
	जोड़ अणु
		u8 src_mac[6];
		u8 dst_mac[6];
	पूर्ण;
	u8 filtertype;
	u16 vid;
	u8 tagged;
	s32 handle;
पूर्ण;

काष्ठा enetc_psfp_filter अणु
	u32 index;
	s32 handle;
	s8 prio;
	u32 maxsdu;
	u32 gate_id;
	s32 meter_id;
	refcount_t refcount;
	काष्ठा hlist_node node;
पूर्ण;

काष्ठा enetc_psfp_gate अणु
	u32 index;
	s8 init_ipv;
	u64 baseसमय;
	u64 cycleसमय;
	u64 cycleसमयxt;
	u32 num_entries;
	refcount_t refcount;
	काष्ठा hlist_node node;
	काष्ठा action_gate_entry entries[];
पूर्ण;

/* Only enable the green color frame now
 * Will add eir and ebs color blind, couple flag etc when
 * policing action add more offloading parameters
 */
काष्ठा enetc_psfp_meter अणु
	u32 index;
	u32 cir;
	u32 cbs;
	refcount_t refcount;
	काष्ठा hlist_node node;
पूर्ण;

#घोषणा ENETC_PSFP_FLAGS_FMI BIT(0)

काष्ठा enetc_stream_filter अणु
	काष्ठा enetc_streamid sid;
	u32 sfi_index;
	u32 sgi_index;
	u32 flags;
	u32 fmi_index;
	काष्ठा flow_stats stats;
	काष्ठा hlist_node node;
पूर्ण;

काष्ठा enetc_psfp अणु
	अचिन्हित दीर्घ dev_biपंचांगap;
	अचिन्हित दीर्घ *psfp_sfi_biपंचांगap;
	काष्ठा hlist_head stream_list;
	काष्ठा hlist_head psfp_filter_list;
	काष्ठा hlist_head psfp_gate_list;
	काष्ठा hlist_head psfp_meter_list;
	spinlock_t psfp_lock; /* spinlock क्रम the काष्ठा enetc_psfp r/w */
पूर्ण;

अटल काष्ठा actions_fwd enetc_act_fwd[] = अणु
	अणु
		BIT(FLOW_ACTION_GATE),
		BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS),
		FILTER_ACTION_TYPE_PSFP
	पूर्ण,
	अणु
		BIT(FLOW_ACTION_POLICE) |
		BIT(FLOW_ACTION_GATE),
		BIT(FLOW_DISSECTOR_KEY_ETH_ADDRS),
		FILTER_ACTION_TYPE_PSFP
	पूर्ण,
	/* example क्रम ACL actions */
	अणु
		BIT(FLOW_ACTION_DROP),
		0,
		FILTER_ACTION_TYPE_ACL
	पूर्ण
पूर्ण;

अटल काष्ठा enetc_psfp epsfp = अणु
	.psfp_sfi_biपंचांगap = शून्य,
पूर्ण;

अटल LIST_HEAD(enetc_block_cb_list);

/* Stream Identity Entry Set Descriptor */
अटल पूर्णांक enetc_streamid_hw_set(काष्ठा enetc_ndev_priv *priv,
				 काष्ठा enetc_streamid *sid,
				 u8 enable)
अणु
	काष्ठा enetc_cbd cbd = अणु.cmd = 0पूर्ण;
	काष्ठा streamid_data *si_data;
	काष्ठा streamid_conf *si_conf;
	u16 data_size;
	dma_addr_t dma;
	पूर्णांक err;

	अगर (sid->index >= priv->psfp_cap.max_streamid)
		वापस -EINVAL;

	अगर (sid->filtertype != STREAMID_TYPE_शून्य &&
	    sid->filtertype != STREAMID_TYPE_SMAC)
		वापस -EOPNOTSUPP;

	/* Disable operation beक्रमe enable */
	cbd.index = cpu_to_le16((u16)sid->index);
	cbd.cls = BDCR_CMD_STREAM_IDENTIFY;
	cbd.status_flags = 0;

	data_size = माप(काष्ठा streamid_data);
	si_data = kzalloc(data_size, __GFP_DMA | GFP_KERNEL);
	cbd.length = cpu_to_le16(data_size);

	dma = dma_map_single(&priv->si->pdev->dev, si_data,
			     data_size, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&priv->si->pdev->dev, dma)) अणु
		netdev_err(priv->si->ndev, "DMA mapping failed!\n");
		kमुक्त(si_data);
		वापस -ENOMEM;
	पूर्ण

	cbd.addr[0] = cpu_to_le32(lower_32_bits(dma));
	cbd.addr[1] = cpu_to_le32(upper_32_bits(dma));
	eth_broadcast_addr(si_data->dmac);
	si_data->vid_vidm_tg = (ENETC_CBDR_SID_VID_MASK
			       + ((0x3 << 14) | ENETC_CBDR_SID_VIDM));

	si_conf = &cbd.sid_set;
	/* Only one port supported क्रम one entry, set itself */
	si_conf->iports = cpu_to_le32(1 << enetc_pf_to_port(priv->si->pdev));
	si_conf->id_type = 1;
	si_conf->oui[2] = 0x0;
	si_conf->oui[1] = 0x80;
	si_conf->oui[0] = 0xC2;

	err = enetc_send_cmd(priv->si, &cbd);
	अगर (err)
		वापस -EINVAL;

	अगर (!enable) अणु
		kमुक्त(si_data);
		वापस 0;
	पूर्ण

	/* Enable the entry overग_लिखो again inहाल space flushed by hardware */
	स_रखो(&cbd, 0, माप(cbd));

	cbd.index = cpu_to_le16((u16)sid->index);
	cbd.cmd = 0;
	cbd.cls = BDCR_CMD_STREAM_IDENTIFY;
	cbd.status_flags = 0;

	si_conf->en = 0x80;
	si_conf->stream_handle = cpu_to_le32(sid->handle);
	si_conf->iports = cpu_to_le32(1 << enetc_pf_to_port(priv->si->pdev));
	si_conf->id_type = sid->filtertype;
	si_conf->oui[2] = 0x0;
	si_conf->oui[1] = 0x80;
	si_conf->oui[0] = 0xC2;

	स_रखो(si_data, 0, data_size);

	cbd.length = cpu_to_le16(data_size);

	cbd.addr[0] = cpu_to_le32(lower_32_bits(dma));
	cbd.addr[1] = cpu_to_le32(upper_32_bits(dma));

	/* VIDM शेष to be 1.
	 * VID Match. If set (b1) then the VID must match, otherwise
	 * any VID is considered a match. VIDM setting is only used
	 * when TG is set to b01.
	 */
	अगर (si_conf->id_type == STREAMID_TYPE_शून्य) अणु
		ether_addr_copy(si_data->dmac, sid->dst_mac);
		si_data->vid_vidm_tg = (sid->vid & ENETC_CBDR_SID_VID_MASK) +
				       ((((u16)(sid->tagged) & 0x3) << 14)
				       | ENETC_CBDR_SID_VIDM);
	पूर्ण अन्यथा अगर (si_conf->id_type == STREAMID_TYPE_SMAC) अणु
		ether_addr_copy(si_data->smac, sid->src_mac);
		si_data->vid_vidm_tg = (sid->vid & ENETC_CBDR_SID_VID_MASK) +
				       ((((u16)(sid->tagged) & 0x3) << 14)
				       | ENETC_CBDR_SID_VIDM);
	पूर्ण

	err = enetc_send_cmd(priv->si, &cbd);
	kमुक्त(si_data);

	वापस err;
पूर्ण

/* Stream Filter Instance Set Descriptor */
अटल पूर्णांक enetc_streamfilter_hw_set(काष्ठा enetc_ndev_priv *priv,
				     काष्ठा enetc_psfp_filter *sfi,
				     u8 enable)
अणु
	काष्ठा enetc_cbd cbd = अणु.cmd = 0पूर्ण;
	काष्ठा sfi_conf *sfi_config;

	cbd.index = cpu_to_le16(sfi->index);
	cbd.cls = BDCR_CMD_STREAM_FILTER;
	cbd.status_flags = 0x80;
	cbd.length = cpu_to_le16(1);

	sfi_config = &cbd.sfi_conf;
	अगर (!enable)
		जाओ निकास;

	sfi_config->en = 0x80;

	अगर (sfi->handle >= 0) अणु
		sfi_config->stream_handle =
			cpu_to_le32(sfi->handle);
		sfi_config->sthm |= 0x80;
	पूर्ण

	sfi_config->sg_inst_table_index = cpu_to_le16(sfi->gate_id);
	sfi_config->input_ports =
		cpu_to_le32(1 << enetc_pf_to_port(priv->si->pdev));

	/* The priority value which may be matched against the
	 * frameै s priority value to determine a match क्रम this entry.
	 */
	अगर (sfi->prio >= 0)
		sfi_config->multi |= (sfi->prio & 0x7) | 0x8;

	/* Filter Type. Identअगरies the contents of the MSDU/FM_INST_INDEX
	 * field as being either an MSDU value or an index पूर्णांकo the Flow
	 * Meter Instance table.
	 */
	अगर (sfi->maxsdu) अणु
		sfi_config->msdu =
		cpu_to_le16(sfi->maxsdu);
		sfi_config->multi |= 0x40;
	पूर्ण

	अगर (sfi->meter_id >= 0) अणु
		sfi_config->fm_inst_table_index = cpu_to_le16(sfi->meter_id);
		sfi_config->multi |= 0x80;
	पूर्ण

निकास:
	वापस enetc_send_cmd(priv->si, &cbd);
पूर्ण

अटल पूर्णांक enetc_streamcounter_hw_get(काष्ठा enetc_ndev_priv *priv,
				      u32 index,
				      काष्ठा psfp_streamfilter_counters *cnt)
अणु
	काष्ठा enetc_cbd cbd = अणु .cmd = 2 पूर्ण;
	काष्ठा sfi_counter_data *data_buf;
	dma_addr_t dma;
	u16 data_size;
	पूर्णांक err;

	cbd.index = cpu_to_le16((u16)index);
	cbd.cmd = 2;
	cbd.cls = BDCR_CMD_STREAM_FILTER;
	cbd.status_flags = 0;

	data_size = माप(काष्ठा sfi_counter_data);
	data_buf = kzalloc(data_size, __GFP_DMA | GFP_KERNEL);
	अगर (!data_buf)
		वापस -ENOMEM;

	dma = dma_map_single(&priv->si->pdev->dev, data_buf,
			     data_size, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&priv->si->pdev->dev, dma)) अणु
		netdev_err(priv->si->ndev, "DMA mapping failed!\n");
		err = -ENOMEM;
		जाओ निकास;
	पूर्ण
	cbd.addr[0] = cpu_to_le32(lower_32_bits(dma));
	cbd.addr[1] = cpu_to_le32(upper_32_bits(dma));

	cbd.length = cpu_to_le16(data_size);

	err = enetc_send_cmd(priv->si, &cbd);
	अगर (err)
		जाओ निकास;

	cnt->matching_frames_count = ((u64)data_buf->matchh << 32) +
				     data_buf->matchl;

	cnt->not_passing_sdu_count = ((u64)data_buf->msdu_droph << 32) +
				     data_buf->msdu_dropl;

	cnt->passing_sdu_count = cnt->matching_frames_count
				- cnt->not_passing_sdu_count;

	cnt->not_passing_frames_count =
				((u64)data_buf->stream_gate_droph << 32) +
				data_buf->stream_gate_dropl;

	cnt->passing_frames_count = cnt->matching_frames_count -
				    cnt->not_passing_sdu_count -
				    cnt->not_passing_frames_count;

	cnt->red_frames_count =	((u64)data_buf->flow_meter_droph << 32)	+
				data_buf->flow_meter_dropl;

निकास:
	kमुक्त(data_buf);
	वापस err;
पूर्ण

अटल u64 get_ptp_now(काष्ठा enetc_hw *hw)
अणु
	u64 now_lo, now_hi, now;

	now_lo = enetc_rd(hw, ENETC_SICTR0);
	now_hi = enetc_rd(hw, ENETC_SICTR1);
	now = now_lo | now_hi << 32;

	वापस now;
पूर्ण

अटल पूर्णांक get_start_ns(u64 now, u64 cycle, u64 *start)
अणु
	u64 n;

	अगर (!cycle)
		वापस -EFAULT;

	n = भाग64_u64(now, cycle);

	*start = (n + 1) * cycle;

	वापस 0;
पूर्ण

/* Stream Gate Instance Set Descriptor */
अटल पूर्णांक enetc_streamgate_hw_set(काष्ठा enetc_ndev_priv *priv,
				   काष्ठा enetc_psfp_gate *sgi,
				   u8 enable)
अणु
	काष्ठा enetc_cbd cbd = अणु .cmd = 0 पूर्ण;
	काष्ठा sgi_table *sgi_config;
	काष्ठा sgcl_conf *sgcl_config;
	काष्ठा sgcl_data *sgcl_data;
	काष्ठा sgce *sgce;
	dma_addr_t dma;
	u16 data_size;
	पूर्णांक err, i;
	u64 now;

	cbd.index = cpu_to_le16(sgi->index);
	cbd.cmd = 0;
	cbd.cls = BDCR_CMD_STREAM_GCL;
	cbd.status_flags = 0x80;

	/* disable */
	अगर (!enable)
		वापस enetc_send_cmd(priv->si, &cbd);

	अगर (!sgi->num_entries)
		वापस 0;

	अगर (sgi->num_entries > priv->psfp_cap.max_psfp_gatelist ||
	    !sgi->cycleसमय)
		वापस -EINVAL;

	/* enable */
	sgi_config = &cbd.sgi_table;

	/* Keep खोलो beक्रमe gate list start */
	sgi_config->ocgtst = 0x80;

	sgi_config->oipv = (sgi->init_ipv < 0) ?
				0x0 : ((sgi->init_ipv & 0x7) | 0x8);

	sgi_config->en = 0x80;

	/* Basic config */
	err = enetc_send_cmd(priv->si, &cbd);
	अगर (err)
		वापस -EINVAL;

	स_रखो(&cbd, 0, माप(cbd));

	cbd.index = cpu_to_le16(sgi->index);
	cbd.cmd = 1;
	cbd.cls = BDCR_CMD_STREAM_GCL;
	cbd.status_flags = 0;

	sgcl_config = &cbd.sgcl_conf;

	sgcl_config->acl_len = (sgi->num_entries - 1) & 0x3;

	data_size = काष्ठा_size(sgcl_data, sgcl, sgi->num_entries);

	sgcl_data = kzalloc(data_size, __GFP_DMA | GFP_KERNEL);
	अगर (!sgcl_data)
		वापस -ENOMEM;

	cbd.length = cpu_to_le16(data_size);

	dma = dma_map_single(&priv->si->pdev->dev,
			     sgcl_data, data_size,
			     DMA_FROM_DEVICE);
	अगर (dma_mapping_error(&priv->si->pdev->dev, dma)) अणु
		netdev_err(priv->si->ndev, "DMA mapping failed!\n");
		kमुक्त(sgcl_data);
		वापस -ENOMEM;
	पूर्ण

	cbd.addr[0] = cpu_to_le32(lower_32_bits(dma));
	cbd.addr[1] = cpu_to_le32(upper_32_bits(dma));

	sgce = &sgcl_data->sgcl[0];

	sgcl_config->agtst = 0x80;

	sgcl_data->ct = sgi->cycleसमय;
	sgcl_data->cte = sgi->cycleसमयxt;

	अगर (sgi->init_ipv >= 0)
		sgcl_config->aipv = (sgi->init_ipv & 0x7) | 0x8;

	क्रम (i = 0; i < sgi->num_entries; i++) अणु
		काष्ठा action_gate_entry *from = &sgi->entries[i];
		काष्ठा sgce *to = &sgce[i];

		अगर (from->gate_state)
			to->multi |= 0x10;

		अगर (from->ipv >= 0)
			to->multi |= ((from->ipv & 0x7) << 5) | 0x08;

		अगर (from->maxoctets >= 0) अणु
			to->multi |= 0x01;
			to->msdu[0] = from->maxoctets & 0xFF;
			to->msdu[1] = (from->maxoctets >> 8) & 0xFF;
			to->msdu[2] = (from->maxoctets >> 16) & 0xFF;
		पूर्ण

		to->पूर्णांकerval = from->पूर्णांकerval;
	पूर्ण

	/* If baseसमय is less than now, calculate start समय */
	now = get_ptp_now(&priv->si->hw);

	अगर (sgi->baseसमय < now) अणु
		u64 start;

		err = get_start_ns(now, sgi->cycleसमय, &start);
		अगर (err)
			जाओ निकास;
		sgcl_data->btl = lower_32_bits(start);
		sgcl_data->bth = upper_32_bits(start);
	पूर्ण अन्यथा अणु
		u32 hi, lo;

		hi = upper_32_bits(sgi->baseसमय);
		lo = lower_32_bits(sgi->baseसमय);
		sgcl_data->bth = hi;
		sgcl_data->btl = lo;
	पूर्ण

	err = enetc_send_cmd(priv->si, &cbd);

निकास:
	kमुक्त(sgcl_data);

	वापस err;
पूर्ण

अटल पूर्णांक enetc_flowmeter_hw_set(काष्ठा enetc_ndev_priv *priv,
				  काष्ठा enetc_psfp_meter *fmi,
				  u8 enable)
अणु
	काष्ठा enetc_cbd cbd = अणु .cmd = 0 पूर्ण;
	काष्ठा fmi_conf *fmi_config;
	u64 temp = 0;

	cbd.index = cpu_to_le16((u16)fmi->index);
	cbd.cls = BDCR_CMD_FLOW_METER;
	cbd.status_flags = 0x80;

	अगर (!enable)
		वापस enetc_send_cmd(priv->si, &cbd);

	fmi_config = &cbd.fmi_conf;
	fmi_config->en = 0x80;

	अगर (fmi->cir) अणु
		temp = (u64)8000 * fmi->cir;
		temp = भाग_u64(temp, 3725);
	पूर्ण

	fmi_config->cir = cpu_to_le32((u32)temp);
	fmi_config->cbs = cpu_to_le32(fmi->cbs);

	/* Default क्रम eir ebs disable */
	fmi_config->eir = 0;
	fmi_config->ebs = 0;

	/* Default:
	 * mark red disable
	 * drop on yellow disable
	 * color mode disable
	 * couple flag disable
	 */
	fmi_config->conf = 0;

	वापस enetc_send_cmd(priv->si, &cbd);
पूर्ण

अटल काष्ठा enetc_stream_filter *enetc_get_stream_by_index(u32 index)
अणु
	काष्ठा enetc_stream_filter *f;

	hlist_क्रम_each_entry(f, &epsfp.stream_list, node)
		अगर (f->sid.index == index)
			वापस f;

	वापस शून्य;
पूर्ण

अटल काष्ठा enetc_psfp_gate *enetc_get_gate_by_index(u32 index)
अणु
	काष्ठा enetc_psfp_gate *g;

	hlist_क्रम_each_entry(g, &epsfp.psfp_gate_list, node)
		अगर (g->index == index)
			वापस g;

	वापस शून्य;
पूर्ण

अटल काष्ठा enetc_psfp_filter *enetc_get_filter_by_index(u32 index)
अणु
	काष्ठा enetc_psfp_filter *s;

	hlist_क्रम_each_entry(s, &epsfp.psfp_filter_list, node)
		अगर (s->index == index)
			वापस s;

	वापस शून्य;
पूर्ण

अटल काष्ठा enetc_psfp_meter *enetc_get_meter_by_index(u32 index)
अणु
	काष्ठा enetc_psfp_meter *m;

	hlist_क्रम_each_entry(m, &epsfp.psfp_meter_list, node)
		अगर (m->index == index)
			वापस m;

	वापस शून्य;
पूर्ण

अटल काष्ठा enetc_psfp_filter
	*enetc_psfp_check_sfi(काष्ठा enetc_psfp_filter *sfi)
अणु
	काष्ठा enetc_psfp_filter *s;

	hlist_क्रम_each_entry(s, &epsfp.psfp_filter_list, node)
		अगर (s->gate_id == sfi->gate_id &&
		    s->prio == sfi->prio &&
		    s->maxsdu == sfi->maxsdu &&
		    s->meter_id == sfi->meter_id)
			वापस s;

	वापस शून्य;
पूर्ण

अटल पूर्णांक enetc_get_मुक्त_index(काष्ठा enetc_ndev_priv *priv)
अणु
	u32 max_size = priv->psfp_cap.max_psfp_filter;
	अचिन्हित दीर्घ index;

	index = find_first_zero_bit(epsfp.psfp_sfi_biपंचांगap, max_size);
	अगर (index == max_size)
		वापस -1;

	वापस index;
पूर्ण

अटल व्योम stream_filter_unref(काष्ठा enetc_ndev_priv *priv, u32 index)
अणु
	काष्ठा enetc_psfp_filter *sfi;
	u8 z;

	sfi = enetc_get_filter_by_index(index);
	WARN_ON(!sfi);
	z = refcount_dec_and_test(&sfi->refcount);

	अगर (z) अणु
		enetc_streamfilter_hw_set(priv, sfi, false);
		hlist_del(&sfi->node);
		kमुक्त(sfi);
		clear_bit(index, epsfp.psfp_sfi_biपंचांगap);
	पूर्ण
पूर्ण

अटल व्योम stream_gate_unref(काष्ठा enetc_ndev_priv *priv, u32 index)
अणु
	काष्ठा enetc_psfp_gate *sgi;
	u8 z;

	sgi = enetc_get_gate_by_index(index);
	WARN_ON(!sgi);
	z = refcount_dec_and_test(&sgi->refcount);
	अगर (z) अणु
		enetc_streamgate_hw_set(priv, sgi, false);
		hlist_del(&sgi->node);
		kमुक्त(sgi);
	पूर्ण
पूर्ण

अटल व्योम flow_meter_unref(काष्ठा enetc_ndev_priv *priv, u32 index)
अणु
	काष्ठा enetc_psfp_meter *fmi;
	u8 z;

	fmi = enetc_get_meter_by_index(index);
	WARN_ON(!fmi);
	z = refcount_dec_and_test(&fmi->refcount);
	अगर (z) अणु
		enetc_flowmeter_hw_set(priv, fmi, false);
		hlist_del(&fmi->node);
		kमुक्त(fmi);
	पूर्ण
पूर्ण

अटल व्योम हटाओ_one_chain(काष्ठा enetc_ndev_priv *priv,
			     काष्ठा enetc_stream_filter *filter)
अणु
	अगर (filter->flags & ENETC_PSFP_FLAGS_FMI)
		flow_meter_unref(priv, filter->fmi_index);

	stream_gate_unref(priv, filter->sgi_index);
	stream_filter_unref(priv, filter->sfi_index);

	hlist_del(&filter->node);
	kमुक्त(filter);
पूर्ण

अटल पूर्णांक enetc_psfp_hw_set(काष्ठा enetc_ndev_priv *priv,
			     काष्ठा enetc_streamid *sid,
			     काष्ठा enetc_psfp_filter *sfi,
			     काष्ठा enetc_psfp_gate *sgi,
			     काष्ठा enetc_psfp_meter *fmi)
अणु
	पूर्णांक err;

	err = enetc_streamid_hw_set(priv, sid, true);
	अगर (err)
		वापस err;

	अगर (sfi) अणु
		err = enetc_streamfilter_hw_set(priv, sfi, true);
		अगर (err)
			जाओ revert_sid;
	पूर्ण

	err = enetc_streamgate_hw_set(priv, sgi, true);
	अगर (err)
		जाओ revert_sfi;

	अगर (fmi) अणु
		err = enetc_flowmeter_hw_set(priv, fmi, true);
		अगर (err)
			जाओ revert_sgi;
	पूर्ण

	वापस 0;

revert_sgi:
	enetc_streamgate_hw_set(priv, sgi, false);
revert_sfi:
	अगर (sfi)
		enetc_streamfilter_hw_set(priv, sfi, false);
revert_sid:
	enetc_streamid_hw_set(priv, sid, false);
	वापस err;
पूर्ण

अटल काष्ठा actions_fwd *enetc_check_flow_actions(u64 acts,
						    अचिन्हित पूर्णांक inputkeys)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(enetc_act_fwd); i++)
		अगर (acts == enetc_act_fwd[i].actions &&
		    inputkeys & enetc_act_fwd[i].keys)
			वापस &enetc_act_fwd[i];

	वापस शून्य;
पूर्ण

अटल पूर्णांक enetc_psfp_parse_clsflower(काष्ठा enetc_ndev_priv *priv,
				      काष्ठा flow_cls_offload *f)
अणु
	काष्ठा flow_action_entry *entryg = शून्य, *entryp = शून्य;
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(f);
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	काष्ठा enetc_stream_filter *filter, *old_filter;
	काष्ठा enetc_psfp_meter *fmi = शून्य, *old_fmi;
	काष्ठा enetc_psfp_filter *sfi, *old_sfi;
	काष्ठा enetc_psfp_gate *sgi, *old_sgi;
	काष्ठा flow_action_entry *entry;
	काष्ठा action_gate_entry *e;
	u8 sfi_overग_लिखो = 0;
	पूर्णांक entries_size;
	पूर्णांक i, err;

	अगर (f->common.chain_index >= priv->psfp_cap.max_streamid) अणु
		NL_SET_ERR_MSG_MOD(extack, "No Stream identify resource!");
		वापस -ENOSPC;
	पूर्ण

	flow_action_क्रम_each(i, entry, &rule->action)
		अगर (entry->id == FLOW_ACTION_GATE)
			entryg = entry;
		अन्यथा अगर (entry->id == FLOW_ACTION_POLICE)
			entryp = entry;

	/* Not support without gate action */
	अगर (!entryg)
		वापस -EINVAL;

	filter = kzalloc(माप(*filter), GFP_KERNEL);
	अगर (!filter)
		वापस -ENOMEM;

	filter->sid.index = f->common.chain_index;

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_ETH_ADDRS)) अणु
		काष्ठा flow_match_eth_addrs match;

		flow_rule_match_eth_addrs(rule, &match);

		अगर (!is_zero_ether_addr(match.mask->dst) &&
		    !is_zero_ether_addr(match.mask->src)) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Cannot match on both source and destination MAC");
			err = -EINVAL;
			जाओ मुक्त_filter;
		पूर्ण

		अगर (!is_zero_ether_addr(match.mask->dst)) अणु
			अगर (!is_broadcast_ether_addr(match.mask->dst)) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Masked matching on destination MAC not supported");
				err = -EINVAL;
				जाओ मुक्त_filter;
			पूर्ण
			ether_addr_copy(filter->sid.dst_mac, match.key->dst);
			filter->sid.filtertype = STREAMID_TYPE_शून्य;
		पूर्ण

		अगर (!is_zero_ether_addr(match.mask->src)) अणु
			अगर (!is_broadcast_ether_addr(match.mask->src)) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Masked matching on source MAC not supported");
				err = -EINVAL;
				जाओ मुक्त_filter;
			पूर्ण
			ether_addr_copy(filter->sid.src_mac, match.key->src);
			filter->sid.filtertype = STREAMID_TYPE_SMAC;
		पूर्ण
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG_MOD(extack, "Unsupported, must include ETH_ADDRS");
		err = -EINVAL;
		जाओ मुक्त_filter;
	पूर्ण

	अगर (flow_rule_match_key(rule, FLOW_DISSECTOR_KEY_VLAN)) अणु
		काष्ठा flow_match_vlan match;

		flow_rule_match_vlan(rule, &match);
		अगर (match.mask->vlan_priority) अणु
			अगर (match.mask->vlan_priority !=
			    (VLAN_PRIO_MASK >> VLAN_PRIO_SHIFT)) अणु
				NL_SET_ERR_MSG_MOD(extack, "Only full mask is supported for VLAN priority");
				err = -EINVAL;
				जाओ मुक्त_filter;
			पूर्ण
		पूर्ण

		अगर (match.mask->vlan_id) अणु
			अगर (match.mask->vlan_id != VLAN_VID_MASK) अणु
				NL_SET_ERR_MSG_MOD(extack, "Only full mask is supported for VLAN id");
				err = -EINVAL;
				जाओ मुक्त_filter;
			पूर्ण

			filter->sid.vid = match.key->vlan_id;
			अगर (!filter->sid.vid)
				filter->sid.tagged = STREAMID_VLAN_UNTAGGED;
			अन्यथा
				filter->sid.tagged = STREAMID_VLAN_TAGGED;
		पूर्ण
	पूर्ण अन्यथा अणु
		filter->sid.tagged = STREAMID_VLAN_ALL;
	पूर्ण

	/* parsing gate action */
	अगर (entryg->gate.index >= priv->psfp_cap.max_psfp_gate) अणु
		NL_SET_ERR_MSG_MOD(extack, "No Stream Gate resource!");
		err = -ENOSPC;
		जाओ मुक्त_filter;
	पूर्ण

	अगर (entryg->gate.num_entries >= priv->psfp_cap.max_psfp_gatelist) अणु
		NL_SET_ERR_MSG_MOD(extack, "No Stream Gate resource!");
		err = -ENOSPC;
		जाओ मुक्त_filter;
	पूर्ण

	entries_size = काष्ठा_size(sgi, entries, entryg->gate.num_entries);
	sgi = kzalloc(entries_size, GFP_KERNEL);
	अगर (!sgi) अणु
		err = -ENOMEM;
		जाओ मुक्त_filter;
	पूर्ण

	refcount_set(&sgi->refcount, 1);
	sgi->index = entryg->gate.index;
	sgi->init_ipv = entryg->gate.prio;
	sgi->baseसमय = entryg->gate.baseसमय;
	sgi->cycleसमय = entryg->gate.cycleसमय;
	sgi->num_entries = entryg->gate.num_entries;

	e = sgi->entries;
	क्रम (i = 0; i < entryg->gate.num_entries; i++) अणु
		e[i].gate_state = entryg->gate.entries[i].gate_state;
		e[i].पूर्णांकerval = entryg->gate.entries[i].पूर्णांकerval;
		e[i].ipv = entryg->gate.entries[i].ipv;
		e[i].maxoctets = entryg->gate.entries[i].maxoctets;
	पूर्ण

	filter->sgi_index = sgi->index;

	sfi = kzalloc(माप(*sfi), GFP_KERNEL);
	अगर (!sfi) अणु
		err = -ENOMEM;
		जाओ मुक्त_gate;
	पूर्ण

	refcount_set(&sfi->refcount, 1);
	sfi->gate_id = sgi->index;
	sfi->meter_id = ENETC_PSFP_WILDCARD;

	/* Flow meter and max frame size */
	अगर (entryp) अणु
		अगर (entryp->police.rate_pkt_ps) अणु
			NL_SET_ERR_MSG_MOD(extack, "QoS offload not support packets per second");
			err = -EOPNOTSUPP;
			जाओ मुक्त_sfi;
		पूर्ण
		अगर (entryp->police.burst) अणु
			fmi = kzalloc(माप(*fmi), GFP_KERNEL);
			अगर (!fmi) अणु
				err = -ENOMEM;
				जाओ मुक्त_sfi;
			पूर्ण
			refcount_set(&fmi->refcount, 1);
			fmi->cir = entryp->police.rate_bytes_ps;
			fmi->cbs = entryp->police.burst;
			fmi->index = entryp->police.index;
			filter->flags |= ENETC_PSFP_FLAGS_FMI;
			filter->fmi_index = fmi->index;
			sfi->meter_id = fmi->index;
		पूर्ण

		अगर (entryp->police.mtu)
			sfi->maxsdu = entryp->police.mtu;
	पूर्ण

	/* prio ref the filter prio */
	अगर (f->common.prio && f->common.prio <= BIT(3))
		sfi->prio = f->common.prio - 1;
	अन्यथा
		sfi->prio = ENETC_PSFP_WILDCARD;

	old_sfi = enetc_psfp_check_sfi(sfi);
	अगर (!old_sfi) अणु
		पूर्णांक index;

		index = enetc_get_मुक्त_index(priv);
		अगर (sfi->handle < 0) अणु
			NL_SET_ERR_MSG_MOD(extack, "No Stream Filter resource!");
			err = -ENOSPC;
			जाओ मुक्त_fmi;
		पूर्ण

		sfi->index = index;
		sfi->handle = index + HANDLE_OFFSET;
		/* Update the stream filter handle also */
		filter->sid.handle = sfi->handle;
		filter->sfi_index = sfi->index;
		sfi_overग_लिखो = 0;
	पूर्ण अन्यथा अणु
		filter->sfi_index = old_sfi->index;
		filter->sid.handle = old_sfi->handle;
		sfi_overग_लिखो = 1;
	पूर्ण

	err = enetc_psfp_hw_set(priv, &filter->sid,
				sfi_overग_लिखो ? शून्य : sfi, sgi, fmi);
	अगर (err)
		जाओ मुक्त_fmi;

	spin_lock(&epsfp.psfp_lock);
	अगर (filter->flags & ENETC_PSFP_FLAGS_FMI) अणु
		old_fmi = enetc_get_meter_by_index(filter->fmi_index);
		अगर (old_fmi) अणु
			fmi->refcount = old_fmi->refcount;
			refcount_set(&fmi->refcount,
				     refcount_पढ़ो(&old_fmi->refcount) + 1);
			hlist_del(&old_fmi->node);
			kमुक्त(old_fmi);
		पूर्ण
		hlist_add_head(&fmi->node, &epsfp.psfp_meter_list);
	पूर्ण

	/* Remove the old node अगर exist and update with a new node */
	old_sgi = enetc_get_gate_by_index(filter->sgi_index);
	अगर (old_sgi) अणु
		refcount_set(&sgi->refcount,
			     refcount_पढ़ो(&old_sgi->refcount) + 1);
		hlist_del(&old_sgi->node);
		kमुक्त(old_sgi);
	पूर्ण

	hlist_add_head(&sgi->node, &epsfp.psfp_gate_list);

	अगर (!old_sfi) अणु
		hlist_add_head(&sfi->node, &epsfp.psfp_filter_list);
		set_bit(sfi->index, epsfp.psfp_sfi_biपंचांगap);
	पूर्ण अन्यथा अणु
		kमुक्त(sfi);
		refcount_inc(&old_sfi->refcount);
	पूर्ण

	old_filter = enetc_get_stream_by_index(filter->sid.index);
	अगर (old_filter)
		हटाओ_one_chain(priv, old_filter);

	filter->stats.lastused = jअगरfies;
	hlist_add_head(&filter->node, &epsfp.stream_list);

	spin_unlock(&epsfp.psfp_lock);

	वापस 0;

मुक्त_fmi:
	kमुक्त(fmi);
मुक्त_sfi:
	kमुक्त(sfi);
मुक्त_gate:
	kमुक्त(sgi);
मुक्त_filter:
	kमुक्त(filter);

	वापस err;
पूर्ण

अटल पूर्णांक enetc_config_clsflower(काष्ठा enetc_ndev_priv *priv,
				  काष्ठा flow_cls_offload *cls_flower)
अणु
	काष्ठा flow_rule *rule = flow_cls_offload_flow_rule(cls_flower);
	काष्ठा netlink_ext_ack *extack = cls_flower->common.extack;
	काष्ठा flow_dissector *dissector = rule->match.dissector;
	काष्ठा flow_action *action = &rule->action;
	काष्ठा flow_action_entry *entry;
	काष्ठा actions_fwd *fwd;
	u64 actions = 0;
	पूर्णांक i, err;

	अगर (!flow_action_has_entries(action)) अणु
		NL_SET_ERR_MSG_MOD(extack, "At least one action is needed");
		वापस -EINVAL;
	पूर्ण

	flow_action_क्रम_each(i, entry, action)
		actions |= BIT(entry->id);

	fwd = enetc_check_flow_actions(actions, dissector->used_keys);
	अगर (!fwd) अणु
		NL_SET_ERR_MSG_MOD(extack, "Unsupported filter type!");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (fwd->output & FILTER_ACTION_TYPE_PSFP) अणु
		err = enetc_psfp_parse_clsflower(priv, cls_flower);
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack, "Invalid PSFP inputs");
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG_MOD(extack, "Unsupported actions");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक enetc_psfp_destroy_clsflower(काष्ठा enetc_ndev_priv *priv,
					काष्ठा flow_cls_offload *f)
अणु
	काष्ठा enetc_stream_filter *filter;
	काष्ठा netlink_ext_ack *extack = f->common.extack;
	पूर्णांक err;

	अगर (f->common.chain_index >= priv->psfp_cap.max_streamid) अणु
		NL_SET_ERR_MSG_MOD(extack, "No Stream identify resource!");
		वापस -ENOSPC;
	पूर्ण

	filter = enetc_get_stream_by_index(f->common.chain_index);
	अगर (!filter)
		वापस -EINVAL;

	err = enetc_streamid_hw_set(priv, &filter->sid, false);
	अगर (err)
		वापस err;

	हटाओ_one_chain(priv, filter);

	वापस 0;
पूर्ण

अटल पूर्णांक enetc_destroy_clsflower(काष्ठा enetc_ndev_priv *priv,
				   काष्ठा flow_cls_offload *f)
अणु
	वापस enetc_psfp_destroy_clsflower(priv, f);
पूर्ण

अटल पूर्णांक enetc_psfp_get_stats(काष्ठा enetc_ndev_priv *priv,
				काष्ठा flow_cls_offload *f)
अणु
	काष्ठा psfp_streamfilter_counters counters = अणुपूर्ण;
	काष्ठा enetc_stream_filter *filter;
	काष्ठा flow_stats stats = अणुपूर्ण;
	पूर्णांक err;

	filter = enetc_get_stream_by_index(f->common.chain_index);
	अगर (!filter)
		वापस -EINVAL;

	err = enetc_streamcounter_hw_get(priv, filter->sfi_index, &counters);
	अगर (err)
		वापस -EINVAL;

	spin_lock(&epsfp.psfp_lock);
	stats.pkts = counters.matching_frames_count +
		     counters.not_passing_sdu_count -
		     filter->stats.pkts;
	stats.drops = counters.not_passing_frames_count +
		      counters.not_passing_sdu_count +
		      counters.red_frames_count -
		      filter->stats.drops;
	stats.lastused = filter->stats.lastused;
	filter->stats.pkts += stats.pkts;
	filter->stats.drops += stats.drops;
	spin_unlock(&epsfp.psfp_lock);

	flow_stats_update(&f->stats, 0x0, stats.pkts, stats.drops,
			  stats.lastused, FLOW_ACTION_HW_STATS_DELAYED);

	वापस 0;
पूर्ण

अटल पूर्णांक enetc_setup_tc_cls_flower(काष्ठा enetc_ndev_priv *priv,
				     काष्ठा flow_cls_offload *cls_flower)
अणु
	चयन (cls_flower->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस enetc_config_clsflower(priv, cls_flower);
	हाल FLOW_CLS_DESTROY:
		वापस enetc_destroy_clsflower(priv, cls_flower);
	हाल FLOW_CLS_STATS:
		वापस enetc_psfp_get_stats(priv, cls_flower);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम clean_psfp_sfi_biपंचांगap(व्योम)
अणु
	biपंचांगap_मुक्त(epsfp.psfp_sfi_biपंचांगap);
	epsfp.psfp_sfi_biपंचांगap = शून्य;
पूर्ण

अटल व्योम clean_stream_list(व्योम)
अणु
	काष्ठा enetc_stream_filter *s;
	काष्ठा hlist_node *पंचांगp;

	hlist_क्रम_each_entry_safe(s, पंचांगp, &epsfp.stream_list, node) अणु
		hlist_del(&s->node);
		kमुक्त(s);
	पूर्ण
पूर्ण

अटल व्योम clean_sfi_list(व्योम)
अणु
	काष्ठा enetc_psfp_filter *sfi;
	काष्ठा hlist_node *पंचांगp;

	hlist_क्रम_each_entry_safe(sfi, पंचांगp, &epsfp.psfp_filter_list, node) अणु
		hlist_del(&sfi->node);
		kमुक्त(sfi);
	पूर्ण
पूर्ण

अटल व्योम clean_sgi_list(व्योम)
अणु
	काष्ठा enetc_psfp_gate *sgi;
	काष्ठा hlist_node *पंचांगp;

	hlist_क्रम_each_entry_safe(sgi, पंचांगp, &epsfp.psfp_gate_list, node) अणु
		hlist_del(&sgi->node);
		kमुक्त(sgi);
	पूर्ण
पूर्ण

अटल व्योम clean_psfp_all(व्योम)
अणु
	/* Disable all list nodes and मुक्त all memory */
	clean_sfi_list();
	clean_sgi_list();
	clean_stream_list();
	epsfp.dev_biपंचांगap = 0;
	clean_psfp_sfi_biपंचांगap();
पूर्ण

पूर्णांक enetc_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data,
			    व्योम *cb_priv)
अणु
	काष्ठा net_device *ndev = cb_priv;

	अगर (!tc_can_offload(ndev))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSFLOWER:
		वापस enetc_setup_tc_cls_flower(netdev_priv(ndev), type_data);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

पूर्णांक enetc_psfp_init(काष्ठा enetc_ndev_priv *priv)
अणु
	अगर (epsfp.psfp_sfi_biपंचांगap)
		वापस 0;

	epsfp.psfp_sfi_biपंचांगap = biपंचांगap_zalloc(priv->psfp_cap.max_psfp_filter,
					      GFP_KERNEL);
	अगर (!epsfp.psfp_sfi_biपंचांगap)
		वापस -ENOMEM;

	spin_lock_init(&epsfp.psfp_lock);

	अगर (list_empty(&enetc_block_cb_list))
		epsfp.dev_biपंचांगap = 0;

	वापस 0;
पूर्ण

पूर्णांक enetc_psfp_clean(काष्ठा enetc_ndev_priv *priv)
अणु
	अगर (!list_empty(&enetc_block_cb_list))
		वापस -EBUSY;

	clean_psfp_all();

	वापस 0;
पूर्ण

पूर्णांक enetc_setup_tc_psfp(काष्ठा net_device *ndev, व्योम *type_data)
अणु
	काष्ठा enetc_ndev_priv *priv = netdev_priv(ndev);
	काष्ठा flow_block_offload *f = type_data;
	पूर्णांक err;

	err = flow_block_cb_setup_simple(f, &enetc_block_cb_list,
					 enetc_setup_tc_block_cb,
					 ndev, ndev, true);
	अगर (err)
		वापस err;

	चयन (f->command) अणु
	हाल FLOW_BLOCK_BIND:
		set_bit(enetc_pf_to_port(priv->si->pdev), &epsfp.dev_biपंचांगap);
		अवरोध;
	हाल FLOW_BLOCK_UNBIND:
		clear_bit(enetc_pf_to_port(priv->si->pdev), &epsfp.dev_biपंचांगap);
		अगर (!epsfp.dev_biपंचांगap)
			clean_psfp_all();
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
