<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2018-2019 Hisilicon Limited. */

#समावेश <linux/debugfs.h>
#समावेश <linux/device.h>

#समावेश "hnae3.h"
#समावेश "hns3_enet.h"

#घोषणा HNS3_DBG_READ_LEN 65536
#घोषणा HNS3_DBG_WRITE_LEN 1024

अटल काष्ठा dentry *hns3_dbgfs_root;

अटल पूर्णांक hns3_dbg_queue_info(काष्ठा hnae3_handle *h,
			       स्थिर अक्षर *cmd_buf)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(h->pdev);
	काष्ठा hns3_nic_priv *priv = h->priv;
	काष्ठा hns3_enet_ring *ring;
	u32 base_add_l, base_add_h;
	u32 queue_num, queue_max;
	u32 value, i;
	पूर्णांक cnt;

	अगर (!priv->ring) अणु
		dev_err(&h->pdev->dev, "priv->ring is NULL\n");
		वापस -EFAULT;
	पूर्ण

	queue_max = h->kinfo.num_tqps;
	cnt = kstrtouपूर्णांक(&cmd_buf[11], 0, &queue_num);
	अगर (cnt)
		queue_num = 0;
	अन्यथा
		queue_max = queue_num + 1;

	dev_info(&h->pdev->dev, "queue info\n");

	अगर (queue_num >= h->kinfo.num_tqps) अणु
		dev_err(&h->pdev->dev,
			"Queue number(%u) is out of range(0-%u)\n", queue_num,
			h->kinfo.num_tqps - 1);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = queue_num; i < queue_max; i++) अणु
		/* Each cycle needs to determine whether the instance is reset,
		 * to prevent reference to invalid memory. And need to ensure
		 * that the following code is executed within 100ms.
		 */
		अगर (!test_bit(HNS3_NIC_STATE_INITED, &priv->state) ||
		    test_bit(HNS3_NIC_STATE_RESETTING, &priv->state))
			वापस -EPERM;

		ring = &priv->ring[(u32)(i + h->kinfo.num_tqps)];
		base_add_h = पढ़ोl_relaxed(ring->tqp->io_base +
					   HNS3_RING_RX_RING_BASEADDR_H_REG);
		base_add_l = पढ़ोl_relaxed(ring->tqp->io_base +
					   HNS3_RING_RX_RING_BASEADDR_L_REG);
		dev_info(&h->pdev->dev, "RX(%u) BASE ADD: 0x%08x%08x\n", i,
			 base_add_h, base_add_l);

		value = पढ़ोl_relaxed(ring->tqp->io_base +
				      HNS3_RING_RX_RING_BD_NUM_REG);
		dev_info(&h->pdev->dev, "RX(%u) RING BD NUM: %u\n", i, value);

		value = पढ़ोl_relaxed(ring->tqp->io_base +
				      HNS3_RING_RX_RING_BD_LEN_REG);
		dev_info(&h->pdev->dev, "RX(%u) RING BD LEN: %u\n", i, value);

		value = पढ़ोl_relaxed(ring->tqp->io_base +
				      HNS3_RING_RX_RING_TAIL_REG);
		dev_info(&h->pdev->dev, "RX(%u) RING TAIL: %u\n", i, value);

		value = पढ़ोl_relaxed(ring->tqp->io_base +
				      HNS3_RING_RX_RING_HEAD_REG);
		dev_info(&h->pdev->dev, "RX(%u) RING HEAD: %u\n", i, value);

		value = पढ़ोl_relaxed(ring->tqp->io_base +
				      HNS3_RING_RX_RING_FBDNUM_REG);
		dev_info(&h->pdev->dev, "RX(%u) RING FBDNUM: %u\n", i, value);

		value = पढ़ोl_relaxed(ring->tqp->io_base +
				      HNS3_RING_RX_RING_PKTNUM_RECORD_REG);
		dev_info(&h->pdev->dev, "RX(%u) RING PKTNUM: %u\n", i, value);

		ring = &priv->ring[i];
		base_add_h = पढ़ोl_relaxed(ring->tqp->io_base +
					   HNS3_RING_TX_RING_BASEADDR_H_REG);
		base_add_l = पढ़ोl_relaxed(ring->tqp->io_base +
					   HNS3_RING_TX_RING_BASEADDR_L_REG);
		dev_info(&h->pdev->dev, "TX(%u) BASE ADD: 0x%08x%08x\n", i,
			 base_add_h, base_add_l);

		value = पढ़ोl_relaxed(ring->tqp->io_base +
				      HNS3_RING_TX_RING_BD_NUM_REG);
		dev_info(&h->pdev->dev, "TX(%u) RING BD NUM: %u\n", i, value);

		value = पढ़ोl_relaxed(ring->tqp->io_base +
				      HNS3_RING_TX_RING_TC_REG);
		dev_info(&h->pdev->dev, "TX(%u) RING TC: %u\n", i, value);

		value = पढ़ोl_relaxed(ring->tqp->io_base +
				      HNS3_RING_TX_RING_TAIL_REG);
		dev_info(&h->pdev->dev, "TX(%u) RING TAIL: %u\n", i, value);

		value = पढ़ोl_relaxed(ring->tqp->io_base +
				      HNS3_RING_TX_RING_HEAD_REG);
		dev_info(&h->pdev->dev, "TX(%u) RING HEAD: %u\n", i, value);

		value = पढ़ोl_relaxed(ring->tqp->io_base +
				      HNS3_RING_TX_RING_FBDNUM_REG);
		dev_info(&h->pdev->dev, "TX(%u) RING FBDNUM: %u\n", i, value);

		value = पढ़ोl_relaxed(ring->tqp->io_base +
				      HNS3_RING_TX_RING_OFFSET_REG);
		dev_info(&h->pdev->dev, "TX(%u) RING OFFSET: %u\n", i, value);

		value = पढ़ोl_relaxed(ring->tqp->io_base +
				      HNS3_RING_TX_RING_PKTNUM_RECORD_REG);
		dev_info(&h->pdev->dev, "TX(%u) RING PKTNUM: %u\n", i, value);

		value = पढ़ोl_relaxed(ring->tqp->io_base + HNS3_RING_EN_REG);
		dev_info(&h->pdev->dev, "TX/RX(%u) RING EN: %s\n", i,
			 value ? "enable" : "disable");

		अगर (hnae3_ae_dev_tqp_txrx_indep_supported(ae_dev)) अणु
			value = पढ़ोl_relaxed(ring->tqp->io_base +
					      HNS3_RING_TX_EN_REG);
			dev_info(&h->pdev->dev, "TX(%u) RING EN: %s\n", i,
				 value ? "enable" : "disable");

			value = पढ़ोl_relaxed(ring->tqp->io_base +
					      HNS3_RING_RX_EN_REG);
			dev_info(&h->pdev->dev, "RX(%u) RING EN: %s\n", i,
				 value ? "enable" : "disable");
		पूर्ण

		dev_info(&h->pdev->dev, "\n");
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_dbg_queue_map(काष्ठा hnae3_handle *h)
अणु
	काष्ठा hns3_nic_priv *priv = h->priv;
	पूर्णांक i;

	अगर (!h->ae_algo->ops->get_global_queue_id)
		वापस -EOPNOTSUPP;

	dev_info(&h->pdev->dev, "map info for queue id and vector id\n");
	dev_info(&h->pdev->dev,
		 "local queue id | global queue id | vector id\n");
	क्रम (i = 0; i < h->kinfo.num_tqps; i++) अणु
		u16 global_qid;

		global_qid = h->ae_algo->ops->get_global_queue_id(h, i);
		अगर (!priv->ring || !priv->ring[i].tqp_vector)
			जारी;

		dev_info(&h->pdev->dev,
			 "      %4d            %4u            %4d\n",
			 i, global_qid, priv->ring[i].tqp_vector->vector_irq);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक hns3_dbg_bd_info(काष्ठा hnae3_handle *h, स्थिर अक्षर *cmd_buf)
अणु
	काष्ठा hns3_nic_priv *priv = h->priv;
	काष्ठा hns3_desc *rx_desc, *tx_desc;
	काष्ठा device *dev = &h->pdev->dev;
	काष्ठा hns3_enet_ring *ring;
	u32 tx_index, rx_index;
	u32 q_num, value;
	dma_addr_t addr;
	u16 mss_hw_csum;
	u32 l234info;
	पूर्णांक cnt;

	cnt = माला_पूछो(&cmd_buf[8], "%u %u", &q_num, &tx_index);
	अगर (cnt == 2) अणु
		rx_index = tx_index;
	पूर्ण अन्यथा अगर (cnt != 1) अणु
		dev_err(dev, "bd info: bad command string, cnt=%d\n", cnt);
		वापस -EINVAL;
	पूर्ण

	अगर (q_num >= h->kinfo.num_tqps) अणु
		dev_err(dev, "Queue number(%u) is out of range(0-%u)\n", q_num,
			h->kinfo.num_tqps - 1);
		वापस -EINVAL;
	पूर्ण

	ring = &priv->ring[q_num];
	value = पढ़ोl_relaxed(ring->tqp->io_base + HNS3_RING_TX_RING_TAIL_REG);
	tx_index = (cnt == 1) ? value : tx_index;

	अगर (tx_index >= ring->desc_num) अणु
		dev_err(dev, "bd index(%u) is out of range(0-%u)\n", tx_index,
			ring->desc_num - 1);
		वापस -EINVAL;
	पूर्ण

	tx_desc = &ring->desc[tx_index];
	addr = le64_to_cpu(tx_desc->addr);
	mss_hw_csum = le16_to_cpu(tx_desc->tx.mss_hw_csum);
	dev_info(dev, "TX Queue Num: %u, BD Index: %u\n", q_num, tx_index);
	dev_info(dev, "(TX)addr: %pad\n", &addr);
	dev_info(dev, "(TX)vlan_tag: %u\n", le16_to_cpu(tx_desc->tx.vlan_tag));
	dev_info(dev, "(TX)send_size: %u\n",
		 le16_to_cpu(tx_desc->tx.send_size));

	अगर (mss_hw_csum & BIT(HNS3_TXD_HW_CS_B)) अणु
		u32 offset = le32_to_cpu(tx_desc->tx.ol_type_vlan_len_msec);
		u32 start = le32_to_cpu(tx_desc->tx.type_cs_vlan_tso_len);

		dev_info(dev, "(TX)csum start: %u\n",
			 hnae3_get_field(start,
					 HNS3_TXD_CSUM_START_M,
					 HNS3_TXD_CSUM_START_S));
		dev_info(dev, "(TX)csum offset: %u\n",
			 hnae3_get_field(offset,
					 HNS3_TXD_CSUM_OFFSET_M,
					 HNS3_TXD_CSUM_OFFSET_S));
	पूर्ण अन्यथा अणु
		dev_info(dev, "(TX)vlan_tso: %u\n",
			 tx_desc->tx.type_cs_vlan_tso);
		dev_info(dev, "(TX)l2_len: %u\n", tx_desc->tx.l2_len);
		dev_info(dev, "(TX)l3_len: %u\n", tx_desc->tx.l3_len);
		dev_info(dev, "(TX)l4_len: %u\n", tx_desc->tx.l4_len);
		dev_info(dev, "(TX)vlan_msec: %u\n",
			 tx_desc->tx.ol_type_vlan_msec);
		dev_info(dev, "(TX)ol2_len: %u\n", tx_desc->tx.ol2_len);
		dev_info(dev, "(TX)ol3_len: %u\n", tx_desc->tx.ol3_len);
		dev_info(dev, "(TX)ol4_len: %u\n", tx_desc->tx.ol4_len);
	पूर्ण

	dev_info(dev, "(TX)vlan_tag: %u\n",
		 le16_to_cpu(tx_desc->tx.outer_vlan_tag));
	dev_info(dev, "(TX)tv: %u\n", le16_to_cpu(tx_desc->tx.tv));
	dev_info(dev, "(TX)paylen_ol4cs: %u\n",
		 le32_to_cpu(tx_desc->tx.paylen_ol4cs));
	dev_info(dev, "(TX)vld_ra_ri: %u\n",
		 le16_to_cpu(tx_desc->tx.bdtp_fe_sc_vld_ra_ri));
	dev_info(dev, "(TX)mss_hw_csum: %u\n", mss_hw_csum);

	ring = &priv->ring[q_num + h->kinfo.num_tqps];
	value = पढ़ोl_relaxed(ring->tqp->io_base + HNS3_RING_RX_RING_TAIL_REG);
	rx_index = (cnt == 1) ? value : tx_index;
	rx_desc = &ring->desc[rx_index];

	addr = le64_to_cpu(rx_desc->addr);
	l234info = le32_to_cpu(rx_desc->rx.l234_info);
	dev_info(dev, "RX Queue Num: %u, BD Index: %u\n", q_num, rx_index);
	dev_info(dev, "(RX)addr: %pad\n", &addr);
	dev_info(dev, "(RX)l234_info: %u\n", l234info);

	अगर (l234info & BIT(HNS3_RXD_L2_CSUM_B)) अणु
		u32 lo, hi;

		lo = hnae3_get_field(l234info, HNS3_RXD_L2_CSUM_L_M,
				     HNS3_RXD_L2_CSUM_L_S);
		hi = hnae3_get_field(l234info, HNS3_RXD_L2_CSUM_H_M,
				     HNS3_RXD_L2_CSUM_H_S);
		dev_info(dev, "(RX)csum: %u\n", lo | hi << 8);
	पूर्ण

	dev_info(dev, "(RX)pkt_len: %u\n", le16_to_cpu(rx_desc->rx.pkt_len));
	dev_info(dev, "(RX)size: %u\n", le16_to_cpu(rx_desc->rx.size));
	dev_info(dev, "(RX)rss_hash: %u\n", le32_to_cpu(rx_desc->rx.rss_hash));
	dev_info(dev, "(RX)fd_id: %u\n", le16_to_cpu(rx_desc->rx.fd_id));
	dev_info(dev, "(RX)vlan_tag: %u\n", le16_to_cpu(rx_desc->rx.vlan_tag));
	dev_info(dev, "(RX)o_dm_vlan_id_fb: %u\n",
		 le16_to_cpu(rx_desc->rx.o_dm_vlan_id_fb));
	dev_info(dev, "(RX)ot_vlan_tag: %u\n",
		 le16_to_cpu(rx_desc->rx.ot_vlan_tag));
	dev_info(dev, "(RX)bd_base_info: %u\n",
		 le32_to_cpu(rx_desc->rx.bd_base_info));

	वापस 0;
पूर्ण

अटल व्योम hns3_dbg_help(काष्ठा hnae3_handle *h)
अणु
#घोषणा HNS3_DBG_BUF_LEN 256

	अक्षर म_लिखो_buf[HNS3_DBG_BUF_LEN];

	dev_info(&h->pdev->dev, "available commands\n");
	dev_info(&h->pdev->dev, "queue info <number>\n");
	dev_info(&h->pdev->dev, "queue map\n");
	dev_info(&h->pdev->dev, "bd info <q_num> <bd index>\n");
	dev_info(&h->pdev->dev, "dev capability\n");
	dev_info(&h->pdev->dev, "dev spec\n");

	अगर (!hns3_is_phys_func(h->pdev))
		वापस;

	dev_info(&h->pdev->dev, "dump fd tcam\n");
	dev_info(&h->pdev->dev, "dump tc\n");
	dev_info(&h->pdev->dev, "dump tm map <q_num>\n");
	dev_info(&h->pdev->dev, "dump tm\n");
	dev_info(&h->pdev->dev, "dump qos pause cfg\n");
	dev_info(&h->pdev->dev, "dump qos pri map\n");
	dev_info(&h->pdev->dev, "dump qos buf cfg\n");
	dev_info(&h->pdev->dev, "dump mng tbl\n");
	dev_info(&h->pdev->dev, "dump reset info\n");
	dev_info(&h->pdev->dev, "dump m7 info\n");
	dev_info(&h->pdev->dev, "dump ncl_config <offset> <length>(in hex)\n");
	dev_info(&h->pdev->dev, "dump mac tnl status\n");
	dev_info(&h->pdev->dev, "dump loopback\n");
	dev_info(&h->pdev->dev, "dump qs shaper [qs id]\n");
	dev_info(&h->pdev->dev, "dump uc mac list <func id>\n");
	dev_info(&h->pdev->dev, "dump mc mac list <func id>\n");
	dev_info(&h->pdev->dev, "dump intr\n");

	स_रखो(म_लिखो_buf, 0, HNS3_DBG_BUF_LEN);
	म_जोड़न(म_लिखो_buf, "dump reg [[bios common] [ssu <port_id>]",
		HNS3_DBG_BUF_LEN - 1);
	म_जोड़न(म_लिखो_buf + म_माप(म_लिखो_buf),
		" [igu egu <port_id>] [rpu <tc_queue_num>]",
		HNS3_DBG_BUF_LEN - म_माप(म_लिखो_buf) - 1);
	म_जोड़न(म_लिखो_buf + म_माप(म_लिखो_buf),
		" [rtc] [ppp] [rcb] [tqp <queue_num>] [mac]]\n",
		HNS3_DBG_BUF_LEN - म_माप(म_लिखो_buf) - 1);
	dev_info(&h->pdev->dev, "%s", म_लिखो_buf);

	स_रखो(म_लिखो_buf, 0, HNS3_DBG_BUF_LEN);
	म_जोड़न(म_लिखो_buf, "dump reg dcb <port_id> <pri_id> <pg_id>",
		HNS3_DBG_BUF_LEN - 1);
	म_जोड़न(म_लिखो_buf + म_माप(म_लिखो_buf), " <rq_id> <nq_id> <qset_id>\n",
		HNS3_DBG_BUF_LEN - म_माप(म_लिखो_buf) - 1);
	dev_info(&h->pdev->dev, "%s", म_लिखो_buf);
पूर्ण

अटल व्योम hns3_dbg_dev_caps(काष्ठा hnae3_handle *h)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(h->pdev);
	अचिन्हित दीर्घ *caps;

	caps = ae_dev->caps;

	dev_info(&h->pdev->dev, "support FD: %s\n",
		 test_bit(HNAE3_DEV_SUPPORT_FD_B, caps) ? "yes" : "no");
	dev_info(&h->pdev->dev, "support GRO: %s\n",
		 test_bit(HNAE3_DEV_SUPPORT_GRO_B, caps) ? "yes" : "no");
	dev_info(&h->pdev->dev, "support FEC: %s\n",
		 test_bit(HNAE3_DEV_SUPPORT_FEC_B, caps) ? "yes" : "no");
	dev_info(&h->pdev->dev, "support UDP GSO: %s\n",
		 test_bit(HNAE3_DEV_SUPPORT_UDP_GSO_B, caps) ? "yes" : "no");
	dev_info(&h->pdev->dev, "support PTP: %s\n",
		 test_bit(HNAE3_DEV_SUPPORT_PTP_B, caps) ? "yes" : "no");
	dev_info(&h->pdev->dev, "support INT QL: %s\n",
		 test_bit(HNAE3_DEV_SUPPORT_INT_QL_B, caps) ? "yes" : "no");
	dev_info(&h->pdev->dev, "support HW TX csum: %s\n",
		 test_bit(HNAE3_DEV_SUPPORT_HW_TX_CSUM_B, caps) ? "yes" : "no");
	dev_info(&h->pdev->dev, "support UDP tunnel csum: %s\n",
		 test_bit(HNAE3_DEV_SUPPORT_UDP_TUNNEL_CSUM_B, caps) ?
		 "yes" : "no");
	dev_info(&h->pdev->dev, "support PAUSE: %s\n",
		 test_bit(HNAE3_DEV_SUPPORT_PAUSE_B, ae_dev->caps) ?
		 "yes" : "no");
	dev_info(&h->pdev->dev, "support imp-controlled PHY: %s\n",
		 test_bit(HNAE3_DEV_SUPPORT_PHY_IMP_B, caps) ? "yes" : "no");
पूर्ण

अटल व्योम hns3_dbg_dev_specs(काष्ठा hnae3_handle *h)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(h->pdev);
	काष्ठा hnae3_dev_specs *dev_specs = &ae_dev->dev_specs;
	काष्ठा hnae3_knic_निजी_info *kinfo = &h->kinfo;
	काष्ठा hns3_nic_priv *priv  = h->priv;

	dev_info(priv->dev, "MAC entry num: %u\n", dev_specs->mac_entry_num);
	dev_info(priv->dev, "MNG entry num: %u\n", dev_specs->mng_entry_num);
	dev_info(priv->dev, "MAX non tso bd num: %u\n",
		 dev_specs->max_non_tso_bd_num);
	dev_info(priv->dev, "RSS ind tbl size: %u\n",
		 dev_specs->rss_ind_tbl_size);
	dev_info(priv->dev, "RSS key size: %u\n", dev_specs->rss_key_size);
	dev_info(priv->dev, "RSS size: %u\n", kinfo->rss_size);
	dev_info(priv->dev, "Allocated RSS size: %u\n", kinfo->req_rss_size);
	dev_info(priv->dev, "Task queue pairs numbers: %u\n", kinfo->num_tqps);

	dev_info(priv->dev, "RX buffer length: %u\n", kinfo->rx_buf_len);
	dev_info(priv->dev, "Desc num per TX queue: %u\n", kinfo->num_tx_desc);
	dev_info(priv->dev, "Desc num per RX queue: %u\n", kinfo->num_rx_desc);
	dev_info(priv->dev, "Total number of enabled TCs: %u\n",
		 kinfo->tc_info.num_tc);
	dev_info(priv->dev, "MAX INT QL: %u\n", dev_specs->पूर्णांक_ql_max);
	dev_info(priv->dev, "MAX INT GL: %u\n", dev_specs->max_पूर्णांक_gl);
	dev_info(priv->dev, "MAX frame size: %u\n", dev_specs->max_frm_size);
	dev_info(priv->dev, "MAX TM RATE: %uMbps\n", dev_specs->max_पंचांग_rate);
	dev_info(priv->dev, "MAX QSET number: %u\n", dev_specs->max_qset_num);
पूर्ण

अटल sमाप_प्रकार hns3_dbg_cmd_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
				 माप_प्रकार count, loff_t *ppos)
अणु
	पूर्णांक uncopy_bytes;
	अक्षर *buf;
	पूर्णांक len;

	अगर (*ppos != 0)
		वापस 0;

	अगर (count < HNS3_DBG_READ_LEN)
		वापस -ENOSPC;

	buf = kzalloc(HNS3_DBG_READ_LEN, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	len = scnम_लिखो(buf, HNS3_DBG_READ_LEN, "%s\n",
			"Please echo help to cmd to get help information");
	uncopy_bytes = copy_to_user(buffer, buf, len);

	kमुक्त(buf);

	अगर (uncopy_bytes)
		वापस -EFAULT;

	वापस (*ppos = len);
पूर्ण

अटल पूर्णांक hns3_dbg_check_cmd(काष्ठा hnae3_handle *handle, अक्षर *cmd_buf)
अणु
	पूर्णांक ret = 0;

	अगर (म_भेदन(cmd_buf, "help", 4) == 0)
		hns3_dbg_help(handle);
	अन्यथा अगर (म_भेदन(cmd_buf, "queue info", 10) == 0)
		ret = hns3_dbg_queue_info(handle, cmd_buf);
	अन्यथा अगर (म_भेदन(cmd_buf, "queue map", 9) == 0)
		ret = hns3_dbg_queue_map(handle);
	अन्यथा अगर (म_भेदन(cmd_buf, "bd info", 7) == 0)
		ret = hns3_dbg_bd_info(handle, cmd_buf);
	अन्यथा अगर (म_भेदन(cmd_buf, "dev capability", 14) == 0)
		hns3_dbg_dev_caps(handle);
	अन्यथा अगर (म_भेदन(cmd_buf, "dev spec", 8) == 0)
		hns3_dbg_dev_specs(handle);
	अन्यथा अगर (handle->ae_algo->ops->dbg_run_cmd)
		ret = handle->ae_algo->ops->dbg_run_cmd(handle, cmd_buf);
	अन्यथा
		ret = -EOPNOTSUPP;

	वापस ret;
पूर्ण

अटल sमाप_प्रकार hns3_dbg_cmd_ग_लिखो(काष्ठा file *filp, स्थिर अक्षर __user *buffer,
				  माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hnae3_handle *handle = filp->निजी_data;
	काष्ठा hns3_nic_priv *priv  = handle->priv;
	अक्षर *cmd_buf, *cmd_buf_पंचांगp;
	पूर्णांक uncopied_bytes;
	पूर्णांक ret;

	अगर (*ppos != 0)
		वापस 0;

	/* Judge अगर the instance is being reset. */
	अगर (!test_bit(HNS3_NIC_STATE_INITED, &priv->state) ||
	    test_bit(HNS3_NIC_STATE_RESETTING, &priv->state))
		वापस 0;

	अगर (count > HNS3_DBG_WRITE_LEN)
		वापस -ENOSPC;

	cmd_buf = kzalloc(count + 1, GFP_KERNEL);
	अगर (!cmd_buf)
		वापस count;

	uncopied_bytes = copy_from_user(cmd_buf, buffer, count);
	अगर (uncopied_bytes) अणु
		kमुक्त(cmd_buf);
		वापस -EFAULT;
	पूर्ण

	cmd_buf[count] = '\0';

	cmd_buf_पंचांगp = म_अक्षर(cmd_buf, '\n');
	अगर (cmd_buf_पंचांगp) अणु
		*cmd_buf_पंचांगp = '\0';
		count = cmd_buf_पंचांगp - cmd_buf + 1;
	पूर्ण

	ret = hns3_dbg_check_cmd(handle, cmd_buf);
	अगर (ret)
		hns3_dbg_help(handle);

	kमुक्त(cmd_buf);
	cmd_buf = शून्य;

	वापस count;
पूर्ण

अटल sमाप_प्रकार hns3_dbg_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
			     माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा hnae3_handle *handle = filp->निजी_data;
	स्थिर काष्ठा hnae3_ae_ops *ops = handle->ae_algo->ops;
	काष्ठा hns3_nic_priv *priv = handle->priv;
	अक्षर *cmd_buf, *पढ़ो_buf;
	sमाप_प्रकार size = 0;
	पूर्णांक ret = 0;

	पढ़ो_buf = kzalloc(HNS3_DBG_READ_LEN, GFP_KERNEL);
	अगर (!पढ़ो_buf)
		वापस -ENOMEM;

	cmd_buf = filp->f_path.dentry->d_iname;

	अगर (ops->dbg_पढ़ो_cmd)
		ret = ops->dbg_पढ़ो_cmd(handle, cmd_buf, पढ़ो_buf,
					HNS3_DBG_READ_LEN);

	अगर (ret) अणु
		dev_info(priv->dev, "unknown command\n");
		जाओ out;
	पूर्ण

	size = simple_पढ़ो_from_buffer(buffer, count, ppos, पढ़ो_buf,
				       म_माप(पढ़ो_buf));

out:
	kमुक्त(पढ़ो_buf);
	वापस size;
पूर्ण

अटल स्थिर काष्ठा file_operations hns3_dbg_cmd_fops = अणु
	.owner = THIS_MODULE,
	.खोलो  = simple_खोलो,
	.पढ़ो  = hns3_dbg_cmd_पढ़ो,
	.ग_लिखो = hns3_dbg_cmd_ग_लिखो,
पूर्ण;

अटल स्थिर काष्ठा file_operations hns3_dbg_fops = अणु
	.owner = THIS_MODULE,
	.खोलो  = simple_खोलो,
	.पढ़ो  = hns3_dbg_पढ़ो,
पूर्ण;

व्योम hns3_dbg_init(काष्ठा hnae3_handle *handle)
अणु
	काष्ठा hnae3_ae_dev *ae_dev = pci_get_drvdata(handle->pdev);
	स्थिर अक्षर *name = pci_name(handle->pdev);
	काष्ठा dentry *entry_dir;

	handle->hnae3_dbgfs = debugfs_create_dir(name, hns3_dbgfs_root);

	debugfs_create_file("cmd", 0600, handle->hnae3_dbgfs, handle,
			    &hns3_dbg_cmd_fops);

	entry_dir = debugfs_create_dir("tm", handle->hnae3_dbgfs);
	अगर (ae_dev->dev_version > HNAE3_DEVICE_VERSION_V2)
		debugfs_create_file(HNAE3_DBG_TM_NODES, 0600, entry_dir, handle,
				    &hns3_dbg_fops);
	debugfs_create_file(HNAE3_DBG_TM_PRI, 0600, entry_dir, handle,
			    &hns3_dbg_fops);
	debugfs_create_file(HNAE3_DBG_TM_QSET, 0600, entry_dir, handle,
			    &hns3_dbg_fops);
पूर्ण

व्योम hns3_dbg_uninit(काष्ठा hnae3_handle *handle)
अणु
	debugfs_हटाओ_recursive(handle->hnae3_dbgfs);
	handle->hnae3_dbgfs = शून्य;
पूर्ण

व्योम hns3_dbg_रेजिस्टर_debugfs(स्थिर अक्षर *debugfs_dir_name)
अणु
	hns3_dbgfs_root = debugfs_create_dir(debugfs_dir_name, शून्य);
पूर्ण

व्योम hns3_dbg_unरेजिस्टर_debugfs(व्योम)
अणु
	debugfs_हटाओ_recursive(hns3_dbgfs_root);
	hns3_dbgfs_root = शून्य;
पूर्ण
