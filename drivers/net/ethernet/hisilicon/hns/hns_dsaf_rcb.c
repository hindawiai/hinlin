<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) 2014-2015 Hisilicon Limited.
 */

#समावेश <linux/cdev.h>
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/spinlock.h>

#समावेश "hns_dsaf_main.h"
#समावेश "hns_dsaf_ppe.h"
#समावेश "hns_dsaf_rcb.h"

#घोषणा RCB_COMMON_REG_OFFSET 0x80000
#घोषणा TX_RING 0
#घोषणा RX_RING 1

#घोषणा RCB_RESET_WAIT_TIMES 30
#घोषणा RCB_RESET_TRY_TIMES 10

/* Because शेष mtu is 1500, rcb buffer size is set to 2048 enough */
#घोषणा RCB_DEFAULT_BUFFER_SIZE 2048

/**
 *hns_rcb_रुको_fbd_clean - clean fbd
 *@qs: ring काष्ठा poपूर्णांकer array
 *@q_num: num of array
 *@flag: tx or rx flag
 */
व्योम hns_rcb_रुको_fbd_clean(काष्ठा hnae_queue **qs, पूर्णांक q_num, u32 flag)
अणु
	पूर्णांक i, रुको_cnt;
	u32 fbd_num;

	क्रम (रुको_cnt = i = 0; i < q_num; रुको_cnt++) अणु
		usleep_range(200, 300);
		fbd_num = 0;
		अगर (flag & RCB_INT_FLAG_TX)
			fbd_num += dsaf_पढ़ो_dev(qs[i],
						 RCB_RING_TX_RING_FBDNUM_REG);
		अगर (flag & RCB_INT_FLAG_RX)
			fbd_num += dsaf_पढ़ो_dev(qs[i],
						 RCB_RING_RX_RING_FBDNUM_REG);
		अगर (!fbd_num)
			i++;
		अगर (रुको_cnt >= 10000)
			अवरोध;
	पूर्ण

	अगर (i < q_num)
		dev_err(qs[i]->handle->owner_dev,
			"queue(%d) wait fbd(%d) clean fail!!\n", i, fbd_num);
पूर्ण

पूर्णांक hns_rcb_रुको_tx_ring_clean(काष्ठा hnae_queue *qs)
अणु
	u32 head, tail;
	पूर्णांक रुको_cnt;

	tail = dsaf_पढ़ो_dev(&qs->tx_ring, RCB_REG_TAIL);
	रुको_cnt = 0;
	जबतक (रुको_cnt++ < HNS_MAX_WAIT_CNT) अणु
		head = dsaf_पढ़ो_dev(&qs->tx_ring, RCB_REG_HEAD);
		अगर (tail == head)
			अवरोध;

		usleep_range(100, 200);
	पूर्ण

	अगर (रुको_cnt >= HNS_MAX_WAIT_CNT) अणु
		dev_err(qs->dev->dev, "rcb wait timeout, head not equal to tail.\n");
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

/**
 *hns_rcb_reset_ring_hw - ring reset
 *@q: ring काष्ठा poपूर्णांकer
 */
व्योम hns_rcb_reset_ring_hw(काष्ठा hnae_queue *q)
अणु
	u32 रुको_cnt;
	u32 try_cnt = 0;
	u32 could_ret;

	u32 tx_fbd_num;

	जबतक (try_cnt++ < RCB_RESET_TRY_TIMES) अणु
		usleep_range(100, 200);
		tx_fbd_num = dsaf_पढ़ो_dev(q, RCB_RING_TX_RING_FBDNUM_REG);
		अगर (tx_fbd_num)
			जारी;

		dsaf_ग_लिखो_dev(q, RCB_RING_PREFETCH_EN_REG, 0);

		dsaf_ग_लिखो_dev(q, RCB_RING_T0_BE_RST, 1);

		msleep(20);
		could_ret = dsaf_पढ़ो_dev(q, RCB_RING_COULD_BE_RST);

		रुको_cnt = 0;
		जबतक (!could_ret && (रुको_cnt < RCB_RESET_WAIT_TIMES)) अणु
			dsaf_ग_लिखो_dev(q, RCB_RING_T0_BE_RST, 0);

			dsaf_ग_लिखो_dev(q, RCB_RING_T0_BE_RST, 1);

			msleep(20);
			could_ret = dsaf_पढ़ो_dev(q, RCB_RING_COULD_BE_RST);

			रुको_cnt++;
		पूर्ण

		dsaf_ग_लिखो_dev(q, RCB_RING_T0_BE_RST, 0);

		अगर (could_ret)
			अवरोध;
	पूर्ण

	अगर (try_cnt >= RCB_RESET_TRY_TIMES)
		dev_err(q->dev->dev, "port%d reset ring fail\n",
			hns_ae_get_vf_cb(q->handle)->port_index);
पूर्ण

/**
 *hns_rcb_पूर्णांक_ctrl_hw - rcb irq enable control
 *@q: hnae queue काष्ठा poपूर्णांकer
 *@flag:ring flag tx or rx
 *@mask:mask
 */
व्योम hns_rcb_पूर्णांक_ctrl_hw(काष्ठा hnae_queue *q, u32 flag, u32 mask)
अणु
	u32 पूर्णांक_mask_en = !!mask;

	अगर (flag & RCB_INT_FLAG_TX) अणु
		dsaf_ग_लिखो_dev(q, RCB_RING_INTMSK_TXWL_REG, पूर्णांक_mask_en);
		dsaf_ग_लिखो_dev(q, RCB_RING_INTMSK_TX_OVERTIME_REG,
			       पूर्णांक_mask_en);
	पूर्ण

	अगर (flag & RCB_INT_FLAG_RX) अणु
		dsaf_ग_लिखो_dev(q, RCB_RING_INTMSK_RXWL_REG, पूर्णांक_mask_en);
		dsaf_ग_लिखो_dev(q, RCB_RING_INTMSK_RX_OVERTIME_REG,
			       पूर्णांक_mask_en);
	पूर्ण
पूर्ण

व्योम hns_rcb_पूर्णांक_clr_hw(काष्ठा hnae_queue *q, u32 flag)
अणु
	अगर (flag & RCB_INT_FLAG_TX) अणु
		dsaf_ग_लिखो_dev(q, RCB_RING_INTSTS_TX_RING_REG, 1);
		dsaf_ग_लिखो_dev(q, RCB_RING_INTSTS_TX_OVERTIME_REG, 1);
	पूर्ण

	अगर (flag & RCB_INT_FLAG_RX) अणु
		dsaf_ग_लिखो_dev(q, RCB_RING_INTSTS_RX_RING_REG, 1);
		dsaf_ग_लिखो_dev(q, RCB_RING_INTSTS_RX_OVERTIME_REG, 1);
	पूर्ण
पूर्ण

व्योम hns_rcbv2_पूर्णांक_ctrl_hw(काष्ठा hnae_queue *q, u32 flag, u32 mask)
अणु
	u32 पूर्णांक_mask_en = !!mask;

	अगर (flag & RCB_INT_FLAG_TX)
		dsaf_ग_लिखो_dev(q, RCB_RING_INTMSK_TXWL_REG, पूर्णांक_mask_en);

	अगर (flag & RCB_INT_FLAG_RX)
		dsaf_ग_लिखो_dev(q, RCB_RING_INTMSK_RXWL_REG, पूर्णांक_mask_en);
पूर्ण

व्योम hns_rcbv2_पूर्णांक_clr_hw(काष्ठा hnae_queue *q, u32 flag)
अणु
	अगर (flag & RCB_INT_FLAG_TX)
		dsaf_ग_लिखो_dev(q, RCBV2_TX_RING_INT_STS_REG, 1);

	अगर (flag & RCB_INT_FLAG_RX)
		dsaf_ग_लिखो_dev(q, RCBV2_RX_RING_INT_STS_REG, 1);
पूर्ण

/**
 *hns_rcb_ring_enable_hw - enable ring
 *@q: rcb ring
 *@val: value to ग_लिखो
 */
व्योम hns_rcb_ring_enable_hw(काष्ठा hnae_queue *q, u32 val)
अणु
	dsaf_ग_लिखो_dev(q, RCB_RING_PREFETCH_EN_REG, !!val);
पूर्ण

व्योम hns_rcb_start(काष्ठा hnae_queue *q, u32 val)
अणु
	hns_rcb_ring_enable_hw(q, val);
पूर्ण

/**
 *hns_rcb_common_init_commit_hw - make rcb common init completed
 *@rcb_common: rcb common device
 */
व्योम hns_rcb_common_init_commit_hw(काष्ठा rcb_common_cb *rcb_common)
अणु
	wmb();	/* Sync poपूर्णांक beक्रमe अवरोधpoपूर्णांक */
	dsaf_ग_लिखो_dev(rcb_common, RCB_COM_CFG_SYS_FSH_REG, 1);
	wmb();	/* Sync poपूर्णांक after अवरोधpoपूर्णांक */
पूर्ण

/* hns_rcb_set_tx_ring_bs - init rcb ring buf size regester
 *@q: hnae_queue
 *@buf_size: buffer size set to hw
 */
व्योम hns_rcb_set_tx_ring_bs(काष्ठा hnae_queue *q, u32 buf_size)
अणु
	u32 bd_माप_प्रकारype = hns_rcb_buf_size2type(buf_size);

	dsaf_ग_लिखो_dev(q, RCB_RING_TX_RING_BD_LEN_REG,
		       bd_माप_प्रकारype);
पूर्ण

/* hns_rcb_set_rx_ring_bs - init rcb ring buf size regester
 *@q: hnae_queue
 *@buf_size: buffer size set to hw
 */
व्योम hns_rcb_set_rx_ring_bs(काष्ठा hnae_queue *q, u32 buf_size)
अणु
	u32 bd_माप_प्रकारype = hns_rcb_buf_size2type(buf_size);

	dsaf_ग_लिखो_dev(q, RCB_RING_RX_RING_BD_LEN_REG,
		       bd_माप_प्रकारype);
पूर्ण

/**
 *hns_rcb_ring_init - init rcb ring
 *@ring_pair: ring pair control block
 *@ring_type: ring type, RX_RING or TX_RING
 */
अटल व्योम hns_rcb_ring_init(काष्ठा ring_pair_cb *ring_pair, पूर्णांक ring_type)
अणु
	काष्ठा hnae_queue *q = &ring_pair->q;
	काष्ठा hnae_ring *ring =
		(ring_type == RX_RING) ? &q->rx_ring : &q->tx_ring;
	dma_addr_t dma = ring->desc_dma_addr;

	अगर (ring_type == RX_RING) अणु
		dsaf_ग_लिखो_dev(q, RCB_RING_RX_RING_BASEADDR_L_REG,
			       (u32)dma);
		dsaf_ग_लिखो_dev(q, RCB_RING_RX_RING_BASEADDR_H_REG,
			       (u32)((dma >> 31) >> 1));

		hns_rcb_set_rx_ring_bs(q, ring->buf_size);

		dsaf_ग_लिखो_dev(q, RCB_RING_RX_RING_BD_NUM_REG,
			       ring_pair->port_id_in_comm);
		dsaf_ग_लिखो_dev(q, RCB_RING_RX_RING_PKTLINE_REG,
			       ring_pair->port_id_in_comm);
	पूर्ण अन्यथा अणु
		dsaf_ग_लिखो_dev(q, RCB_RING_TX_RING_BASEADDR_L_REG,
			       (u32)dma);
		dsaf_ग_लिखो_dev(q, RCB_RING_TX_RING_BASEADDR_H_REG,
			       (u32)((dma >> 31) >> 1));

		hns_rcb_set_tx_ring_bs(q, ring->buf_size);

		dsaf_ग_लिखो_dev(q, RCB_RING_TX_RING_BD_NUM_REG,
			       ring_pair->port_id_in_comm);
		dsaf_ग_लिखो_dev(q, RCB_RING_TX_RING_PKTLINE_REG,
			ring_pair->port_id_in_comm + HNS_RCB_TX_PKTLINE_OFFSET);
	पूर्ण
पूर्ण

/**
 *hns_rcb_init_hw - init rcb hardware
 *@ring: rcb ring
 */
व्योम hns_rcb_init_hw(काष्ठा ring_pair_cb *ring)
अणु
	hns_rcb_ring_init(ring, RX_RING);
	hns_rcb_ring_init(ring, TX_RING);
पूर्ण

/**
 *hns_rcb_set_port_desc_cnt - set rcb port description num
 *@rcb_common: rcb_common device
 *@port_idx:port index
 *@desc_cnt:BD num
 */
अटल व्योम hns_rcb_set_port_desc_cnt(काष्ठा rcb_common_cb *rcb_common,
				      u32 port_idx, u32 desc_cnt)
अणु
	dsaf_ग_लिखो_dev(rcb_common, RCB_CFG_BD_NUM_REG + port_idx * 4,
		       desc_cnt);
पूर्ण

अटल व्योम hns_rcb_set_port_समयout(
	काष्ठा rcb_common_cb *rcb_common, u32 port_idx, u32 समयout)
अणु
	अगर (AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver)) अणु
		dsaf_ग_लिखो_dev(rcb_common, RCB_CFG_OVERTIME_REG,
			       समयout * HNS_RCB_CLK_FREQ_MHZ);
	पूर्ण अन्यथा अगर (!HNS_DSAF_IS_DEBUG(rcb_common->dsaf_dev)) अणु
		अगर (समयout > HNS_RCB_DEF_GAP_TIME_USECS)
			dsaf_ग_लिखो_dev(rcb_common,
				       RCB_PORT_INT_GAPTIME_REG + port_idx * 4,
				       HNS_RCB_DEF_GAP_TIME_USECS);
		अन्यथा
			dsaf_ग_लिखो_dev(rcb_common,
				       RCB_PORT_INT_GAPTIME_REG + port_idx * 4,
				       समयout);

		dsaf_ग_लिखो_dev(rcb_common,
			       RCB_PORT_CFG_OVERTIME_REG + port_idx * 4,
			       समयout);
	पूर्ण अन्यथा अणु
		dsaf_ग_लिखो_dev(rcb_common,
			       RCB_PORT_CFG_OVERTIME_REG + port_idx * 4,
			       समयout);
	पूर्ण
पूर्ण

अटल पूर्णांक hns_rcb_common_get_port_num(काष्ठा rcb_common_cb *rcb_common)
अणु
	अगर (!HNS_DSAF_IS_DEBUG(rcb_common->dsaf_dev))
		वापस HNS_RCB_SERVICE_NW_ENGINE_NUM;
	अन्यथा
		वापस HNS_RCB_DEBUG_NW_ENGINE_NUM;
पूर्ण

/*clr rcb comm exception irq**/
अटल व्योम hns_rcb_comm_exc_irq_en(
			काष्ठा rcb_common_cb *rcb_common, पूर्णांक en)
अणु
	u32 clr_vlue = 0xfffffffful;
	u32 msk_vlue = en ? 0 : 0xfffffffful;

	/* clr पूर्णांक*/
	dsaf_ग_लिखो_dev(rcb_common, RCB_COM_INTSTS_ECC_ERR_REG, clr_vlue);

	dsaf_ग_लिखो_dev(rcb_common, RCB_COM_SF_CFG_RING_STS, clr_vlue);

	dsaf_ग_लिखो_dev(rcb_common, RCB_COM_SF_CFG_BD_RINT_STS, clr_vlue);

	dsaf_ग_लिखो_dev(rcb_common, RCB_COM_RINT_TX_PKT_REG, clr_vlue);
	dsaf_ग_लिखो_dev(rcb_common, RCB_COM_AXI_ERR_STS, clr_vlue);

	/*en msk*/
	dsaf_ग_लिखो_dev(rcb_common, RCB_COM_INTMASK_ECC_ERR_REG, msk_vlue);

	dsaf_ग_लिखो_dev(rcb_common, RCB_COM_SF_CFG_INTMASK_RING, msk_vlue);

	/*क्रम tx bd neednot cacheline, so msk sf_txring_fbd_पूर्णांकmask (bit 1)**/
	dsaf_ग_लिखो_dev(rcb_common, RCB_COM_SF_CFG_INTMASK_BD, msk_vlue | 2);

	dsaf_ग_लिखो_dev(rcb_common, RCB_COM_INTMSK_TX_PKT_REG, msk_vlue);
	dsaf_ग_लिखो_dev(rcb_common, RCB_COM_AXI_WR_ERR_INTMASK, msk_vlue);
पूर्ण

/**
 *hns_rcb_common_init_hw - init rcb common hardware
 *@rcb_common: rcb_common device
 *retuen 0 - success , negative --fail
 */
पूर्णांक hns_rcb_common_init_hw(काष्ठा rcb_common_cb *rcb_common)
अणु
	u32 reg_val;
	पूर्णांक i;
	पूर्णांक port_num = hns_rcb_common_get_port_num(rcb_common);

	hns_rcb_comm_exc_irq_en(rcb_common, 0);

	reg_val = dsaf_पढ़ो_dev(rcb_common, RCB_COM_CFG_INIT_FLAG_REG);
	अगर (0x1 != (reg_val & 0x1)) अणु
		dev_err(rcb_common->dsaf_dev->dev,
			"RCB_COM_CFG_INIT_FLAG_REG reg = 0x%x\n", reg_val);
		वापस -EBUSY;
	पूर्ण

	क्रम (i = 0; i < port_num; i++) अणु
		hns_rcb_set_port_desc_cnt(rcb_common, i, rcb_common->desc_num);
		hns_rcb_set_rx_coalesced_frames(
			rcb_common, i, HNS_RCB_DEF_RX_COALESCED_FRAMES);
		अगर (!AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver) &&
		    !HNS_DSAF_IS_DEBUG(rcb_common->dsaf_dev))
			hns_rcb_set_tx_coalesced_frames(
				rcb_common, i, HNS_RCB_DEF_TX_COALESCED_FRAMES);
		hns_rcb_set_port_समयout(
			rcb_common, i, HNS_RCB_DEF_COALESCED_USECS);
	पूर्ण

	dsaf_ग_लिखो_dev(rcb_common, RCB_COM_CFG_ENDIAN_REG,
		       HNS_RCB_COMMON_ENDIAN);

	अगर (AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver)) अणु
		dsaf_ग_लिखो_dev(rcb_common, RCB_COM_CFG_FNA_REG, 0x0);
		dsaf_ग_लिखो_dev(rcb_common, RCB_COM_CFG_FA_REG, 0x1);
	पूर्ण अन्यथा अणु
		dsaf_set_dev_bit(rcb_common, RCBV2_COM_CFG_USER_REG,
				 RCB_COM_CFG_FNA_B, false);
		dsaf_set_dev_bit(rcb_common, RCBV2_COM_CFG_USER_REG,
				 RCB_COM_CFG_FA_B, true);
		dsaf_set_dev_bit(rcb_common, RCBV2_COM_CFG_TSO_MODE_REG,
				 RCB_COM_TSO_MODE_B, HNS_TSO_MODE_8BD_32K);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक hns_rcb_buf_size2type(u32 buf_size)
अणु
	पूर्णांक bd_माप_प्रकारype;

	चयन (buf_size) अणु
	हाल 512:
		bd_माप_प्रकारype = HNS_BD_SIZE_512_TYPE;
		अवरोध;
	हाल 1024:
		bd_माप_प्रकारype = HNS_BD_SIZE_1024_TYPE;
		अवरोध;
	हाल 2048:
		bd_माप_प्रकारype = HNS_BD_SIZE_2048_TYPE;
		अवरोध;
	हाल 4096:
		bd_माप_प्रकारype = HNS_BD_SIZE_4096_TYPE;
		अवरोध;
	शेष:
		bd_माप_प्रकारype = -EINVAL;
	पूर्ण

	वापस bd_माप_प्रकारype;
पूर्ण

अटल व्योम hns_rcb_ring_get_cfg(काष्ठा hnae_queue *q, पूर्णांक ring_type)
अणु
	काष्ठा hnae_ring *ring;
	काष्ठा rcb_common_cb *rcb_common;
	काष्ठा ring_pair_cb *ring_pair_cb;
	u16 desc_num, mdnum_ppkt;
	bool irq_idx, is_ver1;

	ring_pair_cb = container_of(q, काष्ठा ring_pair_cb, q);
	is_ver1 = AE_IS_VER1(ring_pair_cb->rcb_common->dsaf_dev->dsaf_ver);
	अगर (ring_type == RX_RING) अणु
		ring = &q->rx_ring;
		ring->io_base = ring_pair_cb->q.io_base;
		irq_idx = HNS_RCB_IRQ_IDX_RX;
		mdnum_ppkt = HNS_RCB_RING_MAX_BD_PER_PKT;
	पूर्ण अन्यथा अणु
		ring = &q->tx_ring;
		ring->io_base = ring_pair_cb->q.io_base +
			HNS_RCB_TX_REG_OFFSET;
		irq_idx = HNS_RCB_IRQ_IDX_TX;
		mdnum_ppkt = is_ver1 ? HNS_RCB_RING_MAX_TXBD_PER_PKT :
				 HNS_RCBV2_RING_MAX_TXBD_PER_PKT;
	पूर्ण

	rcb_common = ring_pair_cb->rcb_common;
	desc_num = rcb_common->dsaf_dev->desc_num;

	ring->desc = शून्य;
	ring->desc_cb = शून्य;

	ring->irq = ring_pair_cb->virq[irq_idx];
	ring->desc_dma_addr = 0;

	ring->buf_size = RCB_DEFAULT_BUFFER_SIZE;
	ring->desc_num = desc_num;
	ring->max_desc_num_per_pkt = mdnum_ppkt;
	ring->max_raw_data_sz_per_desc = HNS_RCB_MAX_PKT_SIZE;
	ring->max_pkt_size = HNS_RCB_MAX_PKT_SIZE;
	ring->next_to_use = 0;
	ring->next_to_clean = 0;
पूर्ण

अटल व्योम hns_rcb_ring_pair_get_cfg(काष्ठा ring_pair_cb *ring_pair_cb)
अणु
	ring_pair_cb->q.handle = शून्य;

	hns_rcb_ring_get_cfg(&ring_pair_cb->q, RX_RING);
	hns_rcb_ring_get_cfg(&ring_pair_cb->q, TX_RING);
पूर्ण

अटल पूर्णांक hns_rcb_get_port_in_comm(
	काष्ठा rcb_common_cb *rcb_common, पूर्णांक ring_idx)
अणु
	वापस ring_idx / (rcb_common->max_q_per_vf * rcb_common->max_vfn);
पूर्ण

#घोषणा SERVICE_RING_IRQ_IDX(v1) \
	((v1) ? HNS_SERVICE_RING_IRQ_IDX : HNSV2_SERVICE_RING_IRQ_IDX)
अटल पूर्णांक hns_rcb_get_base_irq_idx(काष्ठा rcb_common_cb *rcb_common)
अणु
	bool is_ver1 = AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver);

	अगर (!HNS_DSAF_IS_DEBUG(rcb_common->dsaf_dev))
		वापस SERVICE_RING_IRQ_IDX(is_ver1);
	अन्यथा
		वापस  HNS_DEBUG_RING_IRQ_IDX;
पूर्ण

#घोषणा RCB_COMM_BASE_TO_RING_BASE(base, ringid)\
	((base) + 0x10000 + HNS_RCB_REG_OFFSET * (ringid))
/**
 *hns_rcb_get_cfg - get rcb config
 *@rcb_common: rcb common device
 */
पूर्णांक hns_rcb_get_cfg(काष्ठा rcb_common_cb *rcb_common)
अणु
	काष्ठा ring_pair_cb *ring_pair_cb;
	u32 i;
	u32 ring_num = rcb_common->ring_num;
	पूर्णांक base_irq_idx = hns_rcb_get_base_irq_idx(rcb_common);
	काष्ठा platक्रमm_device *pdev =
		to_platक्रमm_device(rcb_common->dsaf_dev->dev);
	bool is_ver1 = AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver);

	क्रम (i = 0; i < ring_num; i++) अणु
		ring_pair_cb = &rcb_common->ring_pair_cb[i];
		ring_pair_cb->rcb_common = rcb_common;
		ring_pair_cb->dev = rcb_common->dsaf_dev->dev;
		ring_pair_cb->index = i;
		ring_pair_cb->q.io_base =
			RCB_COMM_BASE_TO_RING_BASE(rcb_common->io_base, i);
		ring_pair_cb->port_id_in_comm =
			hns_rcb_get_port_in_comm(rcb_common, i);
		ring_pair_cb->virq[HNS_RCB_IRQ_IDX_TX] =
		is_ver1 ? platक्रमm_get_irq(pdev, base_irq_idx + i * 2) :
			  platक्रमm_get_irq(pdev, base_irq_idx + i * 3 + 1);
		ring_pair_cb->virq[HNS_RCB_IRQ_IDX_RX] =
		is_ver1 ? platक्रमm_get_irq(pdev, base_irq_idx + i * 2 + 1) :
			  platक्रमm_get_irq(pdev, base_irq_idx + i * 3);
		अगर ((ring_pair_cb->virq[HNS_RCB_IRQ_IDX_TX] == -EPROBE_DEFER) ||
		    (ring_pair_cb->virq[HNS_RCB_IRQ_IDX_RX] == -EPROBE_DEFER))
			वापस -EPROBE_DEFER;

		ring_pair_cb->q.phy_base =
			RCB_COMM_BASE_TO_RING_BASE(rcb_common->phy_base, i);
		hns_rcb_ring_pair_get_cfg(ring_pair_cb);
	पूर्ण

	वापस 0;
पूर्ण

/**
 *hns_rcb_get_rx_coalesced_frames - get rcb port rx coalesced frames
 *@rcb_common: rcb_common device
 *@port_idx:port id in comm
 *
 *Returns: coalesced_frames
 */
u32 hns_rcb_get_rx_coalesced_frames(
	काष्ठा rcb_common_cb *rcb_common, u32 port_idx)
अणु
	वापस dsaf_पढ़ो_dev(rcb_common, RCB_CFG_PKTLINE_REG + port_idx * 4);
पूर्ण

/**
 *hns_rcb_get_tx_coalesced_frames - get rcb port tx coalesced frames
 *@rcb_common: rcb_common device
 *@port_idx:port id in comm
 *
 *Returns: coalesced_frames
 */
u32 hns_rcb_get_tx_coalesced_frames(
	काष्ठा rcb_common_cb *rcb_common, u32 port_idx)
अणु
	u64 reg;

	reg = RCB_CFG_PKTLINE_REG + (port_idx + HNS_RCB_TX_PKTLINE_OFFSET) * 4;
	वापस dsaf_पढ़ो_dev(rcb_common, reg);
पूर्ण

/**
 *hns_rcb_get_coalesce_usecs - get rcb port coalesced समय_out
 *@rcb_common: rcb_common device
 *@port_idx:port id in comm
 *
 *Returns: समय_out
 */
u32 hns_rcb_get_coalesce_usecs(
	काष्ठा rcb_common_cb *rcb_common, u32 port_idx)
अणु
	अगर (AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver))
		वापस dsaf_पढ़ो_dev(rcb_common, RCB_CFG_OVERTIME_REG) /
		       HNS_RCB_CLK_FREQ_MHZ;
	अन्यथा
		वापस dsaf_पढ़ो_dev(rcb_common,
				     RCB_PORT_CFG_OVERTIME_REG + port_idx * 4);
पूर्ण

/**
 *hns_rcb_set_coalesce_usecs - set rcb port coalesced समय_out
 *@rcb_common: rcb_common device
 *@port_idx:port id in comm
 *@समयout:tx/rx समय क्रम coalesced समय_out
 *
 * Returns:
 * Zero क्रम success, or an error code in हाल of failure
 */
पूर्णांक hns_rcb_set_coalesce_usecs(
	काष्ठा rcb_common_cb *rcb_common, u32 port_idx, u32 समयout)
अणु
	u32 old_समयout = hns_rcb_get_coalesce_usecs(rcb_common, port_idx);

	अगर (समयout == old_समयout)
		वापस 0;

	अगर (AE_IS_VER1(rcb_common->dsaf_dev->dsaf_ver)) अणु
		अगर (!HNS_DSAF_IS_DEBUG(rcb_common->dsaf_dev)) अणु
			dev_err(rcb_common->dsaf_dev->dev,
				"error: not support coalesce_usecs setting!\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	अगर (समयout > HNS_RCB_MAX_COALESCED_USECS || समयout == 0) अणु
		dev_err(rcb_common->dsaf_dev->dev,
			"error: coalesce_usecs setting supports 1~1023us\n");
		वापस -EINVAL;
	पूर्ण
	hns_rcb_set_port_समयout(rcb_common, port_idx, समयout);
	वापस 0;
पूर्ण

/**
 *hns_rcb_set_tx_coalesced_frames - set rcb coalesced frames
 *@rcb_common: rcb_common device
 *@port_idx:port id in comm
 *@coalesced_frames:tx/rx BD num क्रम coalesced frames
 *
 * Returns:
 * Zero क्रम success, or an error code in हाल of failure
 */
पूर्णांक hns_rcb_set_tx_coalesced_frames(
	काष्ठा rcb_common_cb *rcb_common, u32 port_idx, u32 coalesced_frames)
अणु
	u32 old_waterline =
		hns_rcb_get_tx_coalesced_frames(rcb_common, port_idx);
	u64 reg;

	अगर (coalesced_frames == old_waterline)
		वापस 0;

	अगर (coalesced_frames != 1) अणु
		dev_err(rcb_common->dsaf_dev->dev,
			"error: not support tx coalesce_frames setting!\n");
		वापस -EINVAL;
	पूर्ण

	reg = RCB_CFG_PKTLINE_REG + (port_idx + HNS_RCB_TX_PKTLINE_OFFSET) * 4;
	dsaf_ग_लिखो_dev(rcb_common, reg,	coalesced_frames);
	वापस 0;
पूर्ण

/**
 *hns_rcb_set_rx_coalesced_frames - set rcb rx coalesced frames
 *@rcb_common: rcb_common device
 *@port_idx:port id in comm
 *@coalesced_frames:tx/rx BD num क्रम coalesced frames
 *
 * Returns:
 * Zero क्रम success, or an error code in हाल of failure
 */
पूर्णांक hns_rcb_set_rx_coalesced_frames(
	काष्ठा rcb_common_cb *rcb_common, u32 port_idx, u32 coalesced_frames)
अणु
	u32 old_waterline =
		hns_rcb_get_rx_coalesced_frames(rcb_common, port_idx);

	अगर (coalesced_frames == old_waterline)
		वापस 0;

	अगर (coalesced_frames >= rcb_common->desc_num ||
	    coalesced_frames > HNS_RCB_MAX_COALESCED_FRAMES ||
	    coalesced_frames < HNS_RCB_MIN_COALESCED_FRAMES) अणु
		dev_err(rcb_common->dsaf_dev->dev,
			"error: not support coalesce_frames setting!\n");
		वापस -EINVAL;
	पूर्ण

	dsaf_ग_लिखो_dev(rcb_common, RCB_CFG_PKTLINE_REG + port_idx * 4,
		       coalesced_frames);
	वापस 0;
पूर्ण

/**
 *hns_rcb_get_queue_mode - get max VM number and max ring number per VM
 *						accordding to dsaf mode
 *@dsaf_mode: dsaf mode
 *@max_vfn : max vfn number
 *@max_q_per_vf:max ring number per vm
 */
व्योम hns_rcb_get_queue_mode(क्रमागत dsaf_mode dsaf_mode, u16 *max_vfn,
			    u16 *max_q_per_vf)
अणु
	चयन (dsaf_mode) अणु
	हाल DSAF_MODE_DISABLE_6PORT_0VM:
		*max_vfn = 1;
		*max_q_per_vf = 16;
		अवरोध;
	हाल DSAF_MODE_DISABLE_FIX:
	हाल DSAF_MODE_DISABLE_SP:
		*max_vfn = 1;
		*max_q_per_vf = 1;
		अवरोध;
	हाल DSAF_MODE_DISABLE_2PORT_64VM:
		*max_vfn = 64;
		*max_q_per_vf = 1;
		अवरोध;
	हाल DSAF_MODE_DISABLE_6PORT_16VM:
		*max_vfn = 16;
		*max_q_per_vf = 1;
		अवरोध;
	शेष:
		*max_vfn = 1;
		*max_q_per_vf = 16;
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक hns_rcb_get_ring_num(काष्ठा dsaf_device *dsaf_dev)
अणु
	चयन (dsaf_dev->dsaf_mode) अणु
	हाल DSAF_MODE_ENABLE_FIX:
	हाल DSAF_MODE_DISABLE_SP:
		वापस 1;

	हाल DSAF_MODE_DISABLE_FIX:
		वापस 6;

	हाल DSAF_MODE_ENABLE_0VM:
		वापस 32;

	हाल DSAF_MODE_DISABLE_6PORT_0VM:
	हाल DSAF_MODE_ENABLE_16VM:
	हाल DSAF_MODE_DISABLE_6PORT_2VM:
	हाल DSAF_MODE_DISABLE_6PORT_16VM:
	हाल DSAF_MODE_DISABLE_6PORT_4VM:
	हाल DSAF_MODE_ENABLE_8VM:
		वापस 96;

	हाल DSAF_MODE_DISABLE_2PORT_16VM:
	हाल DSAF_MODE_DISABLE_2PORT_8VM:
	हाल DSAF_MODE_ENABLE_32VM:
	हाल DSAF_MODE_DISABLE_2PORT_64VM:
	हाल DSAF_MODE_ENABLE_128VM:
		वापस 128;

	शेष:
		dev_warn(dsaf_dev->dev,
			 "get ring num fail,use default!dsaf_mode=%d\n",
			 dsaf_dev->dsaf_mode);
		वापस 128;
	पूर्ण
पूर्ण

अटल u8 __iomem *hns_rcb_common_get_vaddr(काष्ठा rcb_common_cb *rcb_common)
अणु
	काष्ठा dsaf_device *dsaf_dev = rcb_common->dsaf_dev;

	वापस dsaf_dev->ppe_base + RCB_COMMON_REG_OFFSET;
पूर्ण

अटल phys_addr_t hns_rcb_common_get_paddr(काष्ठा rcb_common_cb *rcb_common)
अणु
	काष्ठा dsaf_device *dsaf_dev = rcb_common->dsaf_dev;

	वापस dsaf_dev->ppe_paddr + RCB_COMMON_REG_OFFSET;
पूर्ण

पूर्णांक hns_rcb_common_get_cfg(काष्ठा dsaf_device *dsaf_dev,
			   पूर्णांक comm_index)
अणु
	काष्ठा rcb_common_cb *rcb_common;
	क्रमागत dsaf_mode dsaf_mode = dsaf_dev->dsaf_mode;
	u16 max_vfn;
	u16 max_q_per_vf;
	पूर्णांक ring_num = hns_rcb_get_ring_num(dsaf_dev);

	rcb_common =
		devm_kzalloc(dsaf_dev->dev,
			     काष्ठा_size(rcb_common, ring_pair_cb, ring_num),
			     GFP_KERNEL);
	अगर (!rcb_common) अणु
		dev_err(dsaf_dev->dev, "rcb common devm_kzalloc fail!\n");
		वापस -ENOMEM;
	पूर्ण
	rcb_common->comm_index = comm_index;
	rcb_common->ring_num = ring_num;
	rcb_common->dsaf_dev = dsaf_dev;

	rcb_common->desc_num = dsaf_dev->desc_num;

	hns_rcb_get_queue_mode(dsaf_mode, &max_vfn, &max_q_per_vf);
	rcb_common->max_vfn = max_vfn;
	rcb_common->max_q_per_vf = max_q_per_vf;

	rcb_common->io_base = hns_rcb_common_get_vaddr(rcb_common);
	rcb_common->phy_base = hns_rcb_common_get_paddr(rcb_common);

	dsaf_dev->rcb_common[comm_index] = rcb_common;
	वापस 0;
पूर्ण

व्योम hns_rcb_common_मुक्त_cfg(काष्ठा dsaf_device *dsaf_dev,
			     u32 comm_index)
अणु
	dsaf_dev->rcb_common[comm_index] = शून्य;
पूर्ण

व्योम hns_rcb_update_stats(काष्ठा hnae_queue *queue)
अणु
	काष्ठा ring_pair_cb *ring =
		container_of(queue, काष्ठा ring_pair_cb, q);
	काष्ठा dsaf_device *dsaf_dev = ring->rcb_common->dsaf_dev;
	काष्ठा ppe_common_cb *ppe_common
		= dsaf_dev->ppe_common[ring->rcb_common->comm_index];
	काष्ठा hns_ring_hw_stats *hw_stats = &ring->hw_stats;

	hw_stats->rx_pkts += dsaf_पढ़ो_dev(queue,
			 RCB_RING_RX_RING_PKTNUM_RECORD_REG);
	dsaf_ग_लिखो_dev(queue, RCB_RING_RX_RING_PKTNUM_RECORD_REG, 0x1);

	hw_stats->ppe_rx_ok_pkts += dsaf_पढ़ो_dev(ppe_common,
			 PPE_COM_HIS_RX_PKT_QID_OK_CNT_REG + 4 * ring->index);
	hw_stats->ppe_rx_drop_pkts += dsaf_पढ़ो_dev(ppe_common,
			 PPE_COM_HIS_RX_PKT_QID_DROP_CNT_REG + 4 * ring->index);

	hw_stats->tx_pkts += dsaf_पढ़ो_dev(queue,
			 RCB_RING_TX_RING_PKTNUM_RECORD_REG);
	dsaf_ग_लिखो_dev(queue, RCB_RING_TX_RING_PKTNUM_RECORD_REG, 0x1);

	hw_stats->ppe_tx_ok_pkts += dsaf_पढ़ो_dev(ppe_common,
			 PPE_COM_HIS_TX_PKT_QID_OK_CNT_REG + 4 * ring->index);
	hw_stats->ppe_tx_drop_pkts += dsaf_पढ़ो_dev(ppe_common,
			 PPE_COM_HIS_TX_PKT_QID_ERR_CNT_REG + 4 * ring->index);
पूर्ण

/**
 *hns_rcb_get_stats - get rcb statistic
 *@queue: rcb ring
 *@data:statistic value
 */
व्योम hns_rcb_get_stats(काष्ठा hnae_queue *queue, u64 *data)
अणु
	u64 *regs_buff = data;
	काष्ठा ring_pair_cb *ring =
		container_of(queue, काष्ठा ring_pair_cb, q);
	काष्ठा hns_ring_hw_stats *hw_stats = &ring->hw_stats;

	regs_buff[0] = hw_stats->tx_pkts;
	regs_buff[1] = hw_stats->ppe_tx_ok_pkts;
	regs_buff[2] = hw_stats->ppe_tx_drop_pkts;
	regs_buff[3] =
		dsaf_पढ़ो_dev(queue, RCB_RING_TX_RING_FBDNUM_REG);

	regs_buff[4] = queue->tx_ring.stats.tx_pkts;
	regs_buff[5] = queue->tx_ring.stats.tx_bytes;
	regs_buff[6] = queue->tx_ring.stats.tx_err_cnt;
	regs_buff[7] = queue->tx_ring.stats.io_err_cnt;
	regs_buff[8] = queue->tx_ring.stats.sw_err_cnt;
	regs_buff[9] = queue->tx_ring.stats.seg_pkt_cnt;
	regs_buff[10] = queue->tx_ring.stats.restart_queue;
	regs_buff[11] = queue->tx_ring.stats.tx_busy;

	regs_buff[12] = hw_stats->rx_pkts;
	regs_buff[13] = hw_stats->ppe_rx_ok_pkts;
	regs_buff[14] = hw_stats->ppe_rx_drop_pkts;
	regs_buff[15] =
		dsaf_पढ़ो_dev(queue, RCB_RING_RX_RING_FBDNUM_REG);

	regs_buff[16] = queue->rx_ring.stats.rx_pkts;
	regs_buff[17] = queue->rx_ring.stats.rx_bytes;
	regs_buff[18] = queue->rx_ring.stats.rx_err_cnt;
	regs_buff[19] = queue->rx_ring.stats.io_err_cnt;
	regs_buff[20] = queue->rx_ring.stats.sw_err_cnt;
	regs_buff[21] = queue->rx_ring.stats.seg_pkt_cnt;
	regs_buff[22] = queue->rx_ring.stats.reuse_pg_cnt;
	regs_buff[23] = queue->rx_ring.stats.err_pkt_len;
	regs_buff[24] = queue->rx_ring.stats.non_vld_descs;
	regs_buff[25] = queue->rx_ring.stats.err_bd_num;
	regs_buff[26] = queue->rx_ring.stats.l2_err;
	regs_buff[27] = queue->rx_ring.stats.l3l4_csum_err;
पूर्ण

/**
 *hns_rcb_get_ring_sset_count - rcb string set count
 *@stringset:ethtool cmd
 *वापस rcb ring string set count
 */
पूर्णांक hns_rcb_get_ring_sset_count(पूर्णांक stringset)
अणु
	अगर (stringset == ETH_SS_STATS)
		वापस HNS_RING_STATIC_REG_NUM;

	वापस 0;
पूर्ण

/**
 *hns_rcb_get_common_regs_count - rcb common regs count
 *वापस regs count
 */
पूर्णांक hns_rcb_get_common_regs_count(व्योम)
अणु
	वापस HNS_RCB_COMMON_DUMP_REG_NUM;
पूर्ण

/**
 *rcb_get_sset_count - rcb ring regs count
 *वापस regs count
 */
पूर्णांक hns_rcb_get_ring_regs_count(व्योम)
अणु
	वापस HNS_RCB_RING_DUMP_REG_NUM;
पूर्ण

/**
 *hns_rcb_get_strings - get rcb string set
 *@stringset:string set index
 *@data:strings name value
 *@index:queue index
 */
व्योम hns_rcb_get_strings(पूर्णांक stringset, u8 *data, पूर्णांक index)
अणु
	u8 *buff = data;

	अगर (stringset != ETH_SS_STATS)
		वापस;

	ethtool_प्र_लिखो(&buff, "tx_ring%d_rcb_pkt_num", index);
	ethtool_प्र_लिखो(&buff, "tx_ring%d_ppe_tx_pkt_num", index);
	ethtool_प्र_लिखो(&buff, "tx_ring%d_ppe_drop_pkt_num", index);
	ethtool_प्र_लिखो(&buff, "tx_ring%d_fbd_num", index);

	ethtool_प्र_लिखो(&buff, "tx_ring%d_pkt_num", index);
	ethtool_प्र_लिखो(&buff, "tx_ring%d_bytes", index);
	ethtool_प्र_लिखो(&buff, "tx_ring%d_err_cnt", index);
	ethtool_प्र_लिखो(&buff, "tx_ring%d_io_err", index);
	ethtool_प्र_लिखो(&buff, "tx_ring%d_sw_err", index);
	ethtool_प्र_लिखो(&buff, "tx_ring%d_seg_pkt", index);
	ethtool_प्र_लिखो(&buff, "tx_ring%d_restart_queue", index);
	ethtool_प्र_लिखो(&buff, "tx_ring%d_tx_busy", index);

	ethtool_प्र_लिखो(&buff, "rx_ring%d_rcb_pkt_num", index);
	ethtool_प्र_लिखो(&buff, "rx_ring%d_ppe_pkt_num", index);
	ethtool_प्र_लिखो(&buff, "rx_ring%d_ppe_drop_pkt_num", index);
	ethtool_प्र_लिखो(&buff, "rx_ring%d_fbd_num", index);

	ethtool_प्र_लिखो(&buff, "rx_ring%d_pkt_num", index);
	ethtool_प्र_लिखो(&buff, "rx_ring%d_bytes", index);
	ethtool_प्र_लिखो(&buff, "rx_ring%d_err_cnt", index);
	ethtool_प्र_लिखो(&buff, "rx_ring%d_io_err", index);
	ethtool_प्र_लिखो(&buff, "rx_ring%d_sw_err", index);
	ethtool_प्र_लिखो(&buff, "rx_ring%d_seg_pkt", index);
	ethtool_प्र_लिखो(&buff, "rx_ring%d_reuse_pg", index);
	ethtool_प्र_लिखो(&buff, "rx_ring%d_len_err", index);
	ethtool_प्र_लिखो(&buff, "rx_ring%d_non_vld_desc_err", index);
	ethtool_प्र_लिखो(&buff, "rx_ring%d_bd_num_err", index);
	ethtool_प्र_लिखो(&buff, "rx_ring%d_l2_err", index);
	ethtool_प्र_लिखो(&buff, "rx_ring%d_l3l4csum_err", index);
पूर्ण

व्योम hns_rcb_get_common_regs(काष्ठा rcb_common_cb *rcb_com, व्योम *data)
अणु
	u32 *regs = data;
	bool is_ver1 = AE_IS_VER1(rcb_com->dsaf_dev->dsaf_ver);
	bool is_dbg = HNS_DSAF_IS_DEBUG(rcb_com->dsaf_dev);
	u32 reg_पंचांगp;
	u32 reg_num_पंचांगp;
	u32 i;

	/*rcb common रेजिस्टरs */
	regs[0] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_CFG_ENDIAN_REG);
	regs[1] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_CFG_SYS_FSH_REG);
	regs[2] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_CFG_INIT_FLAG_REG);

	regs[3] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_CFG_PKT_REG);
	regs[4] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_CFG_RINVLD_REG);
	regs[5] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_CFG_FNA_REG);
	regs[6] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_CFG_FA_REG);
	regs[7] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_CFG_PKT_TC_BP_REG);
	regs[8] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_CFG_PPE_TNL_CLKEN_REG);

	regs[9] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_INTMSK_TX_PKT_REG);
	regs[10] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_RINT_TX_PKT_REG);
	regs[11] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_INTMASK_ECC_ERR_REG);
	regs[12] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_INTSTS_ECC_ERR_REG);
	regs[13] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_EBD_SRAM_ERR_REG);
	regs[14] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_RXRING_ERR_REG);
	regs[15] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_TXRING_ERR_REG);
	regs[16] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_TX_FBD_ERR_REG);
	regs[17] = dsaf_पढ़ो_dev(rcb_com, RCB_SRAM_ECC_CHK_EN_REG);
	regs[18] = dsaf_पढ़ो_dev(rcb_com, RCB_SRAM_ECC_CHK0_REG);
	regs[19] = dsaf_पढ़ो_dev(rcb_com, RCB_SRAM_ECC_CHK1_REG);
	regs[20] = dsaf_पढ़ो_dev(rcb_com, RCB_SRAM_ECC_CHK2_REG);
	regs[21] = dsaf_पढ़ो_dev(rcb_com, RCB_SRAM_ECC_CHK3_REG);
	regs[22] = dsaf_पढ़ो_dev(rcb_com, RCB_SRAM_ECC_CHK4_REG);
	regs[23] = dsaf_पढ़ो_dev(rcb_com, RCB_SRAM_ECC_CHK5_REG);
	regs[24] = dsaf_पढ़ो_dev(rcb_com, RCB_ECC_ERR_ADDR0_REG);
	regs[25] = dsaf_पढ़ो_dev(rcb_com, RCB_ECC_ERR_ADDR3_REG);
	regs[26] = dsaf_पढ़ो_dev(rcb_com, RCB_ECC_ERR_ADDR4_REG);
	regs[27] = dsaf_पढ़ो_dev(rcb_com, RCB_ECC_ERR_ADDR5_REG);

	regs[28] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_SF_CFG_INTMASK_RING);
	regs[29] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_SF_CFG_RING_STS);
	regs[30] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_SF_CFG_RING);
	regs[31] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_SF_CFG_INTMASK_BD);
	regs[32] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_SF_CFG_BD_RINT_STS);
	regs[33] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_RCB_RD_BD_BUSY);
	regs[34] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_RCB_FBD_CRT_EN);
	regs[35] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_AXI_WR_ERR_INTMASK);
	regs[36] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_AXI_ERR_STS);
	regs[37] = dsaf_पढ़ो_dev(rcb_com, RCB_COM_CHK_TX_FBD_NUM_REG);

	/* rcb common entry रेजिस्टरs */
	क्रम (i = 0; i < 16; i++) अणु /* total 16 model रेजिस्टरs */
		regs[38 + i]
			= dsaf_पढ़ो_dev(rcb_com, RCB_CFG_BD_NUM_REG + 4 * i);
		regs[54 + i]
			= dsaf_पढ़ो_dev(rcb_com, RCB_CFG_PKTLINE_REG + 4 * i);
	पूर्ण

	reg_पंचांगp = is_ver1 ? RCB_CFG_OVERTIME_REG : RCB_PORT_CFG_OVERTIME_REG;
	reg_num_पंचांगp = (is_ver1 || is_dbg) ? 1 : 6;
	क्रम (i = 0; i < reg_num_पंचांगp; i++)
		regs[70 + i] = dsaf_पढ़ो_dev(rcb_com, reg_पंचांगp);

	regs[76] = dsaf_पढ़ो_dev(rcb_com, RCB_CFG_PKTLINE_INT_NUM_REG);
	regs[77] = dsaf_पढ़ो_dev(rcb_com, RCB_CFG_OVERTIME_INT_NUM_REG);

	/* mark end of rcb common regs */
	क्रम (i = 78; i < 80; i++)
		regs[i] = 0xcccccccc;
पूर्ण

व्योम hns_rcb_get_ring_regs(काष्ठा hnae_queue *queue, व्योम *data)
अणु
	u32 *regs = data;
	काष्ठा ring_pair_cb *ring_pair
		= container_of(queue, काष्ठा ring_pair_cb, q);
	u32 i;

	/*rcb ring रेजिस्टरs */
	regs[0] = dsaf_पढ़ो_dev(queue, RCB_RING_RX_RING_BASEADDR_L_REG);
	regs[1] = dsaf_पढ़ो_dev(queue, RCB_RING_RX_RING_BASEADDR_H_REG);
	regs[2] = dsaf_पढ़ो_dev(queue, RCB_RING_RX_RING_BD_NUM_REG);
	regs[3] = dsaf_पढ़ो_dev(queue, RCB_RING_RX_RING_BD_LEN_REG);
	regs[4] = dsaf_पढ़ो_dev(queue, RCB_RING_RX_RING_PKTLINE_REG);
	regs[5] = dsaf_पढ़ो_dev(queue, RCB_RING_RX_RING_TAIL_REG);
	regs[6] = dsaf_पढ़ो_dev(queue, RCB_RING_RX_RING_HEAD_REG);
	regs[7] = dsaf_पढ़ो_dev(queue, RCB_RING_RX_RING_FBDNUM_REG);
	regs[8] = dsaf_पढ़ो_dev(queue, RCB_RING_RX_RING_PKTNUM_RECORD_REG);

	regs[9] = dsaf_पढ़ो_dev(queue, RCB_RING_TX_RING_BASEADDR_L_REG);
	regs[10] = dsaf_पढ़ो_dev(queue, RCB_RING_TX_RING_BASEADDR_H_REG);
	regs[11] = dsaf_पढ़ो_dev(queue, RCB_RING_TX_RING_BD_NUM_REG);
	regs[12] = dsaf_पढ़ो_dev(queue, RCB_RING_TX_RING_BD_LEN_REG);
	regs[13] = dsaf_पढ़ो_dev(queue, RCB_RING_TX_RING_PKTLINE_REG);
	regs[15] = dsaf_पढ़ो_dev(queue, RCB_RING_TX_RING_TAIL_REG);
	regs[16] = dsaf_पढ़ो_dev(queue, RCB_RING_TX_RING_HEAD_REG);
	regs[17] = dsaf_पढ़ो_dev(queue, RCB_RING_TX_RING_FBDNUM_REG);
	regs[18] = dsaf_पढ़ो_dev(queue, RCB_RING_TX_RING_OFFSET_REG);
	regs[19] = dsaf_पढ़ो_dev(queue, RCB_RING_TX_RING_PKTNUM_RECORD_REG);

	regs[20] = dsaf_पढ़ो_dev(queue, RCB_RING_PREFETCH_EN_REG);
	regs[21] = dsaf_पढ़ो_dev(queue, RCB_RING_CFG_VF_NUM_REG);
	regs[22] = dsaf_पढ़ो_dev(queue, RCB_RING_ASID_REG);
	regs[23] = dsaf_पढ़ो_dev(queue, RCB_RING_RX_VM_REG);
	regs[24] = dsaf_पढ़ो_dev(queue, RCB_RING_T0_BE_RST);
	regs[25] = dsaf_पढ़ो_dev(queue, RCB_RING_COULD_BE_RST);
	regs[26] = dsaf_पढ़ो_dev(queue, RCB_RING_WRR_WEIGHT_REG);

	regs[27] = dsaf_पढ़ो_dev(queue, RCB_RING_INTMSK_RXWL_REG);
	regs[28] = dsaf_पढ़ो_dev(queue, RCB_RING_INTSTS_RX_RING_REG);
	regs[29] = dsaf_पढ़ो_dev(queue, RCB_RING_INTMSK_TXWL_REG);
	regs[30] = dsaf_पढ़ो_dev(queue, RCB_RING_INTSTS_TX_RING_REG);
	regs[31] = dsaf_पढ़ो_dev(queue, RCB_RING_INTMSK_RX_OVERTIME_REG);
	regs[32] = dsaf_पढ़ो_dev(queue, RCB_RING_INTSTS_RX_OVERTIME_REG);
	regs[33] = dsaf_पढ़ो_dev(queue, RCB_RING_INTMSK_TX_OVERTIME_REG);
	regs[34] = dsaf_पढ़ो_dev(queue, RCB_RING_INTSTS_TX_OVERTIME_REG);

	/* mark end of ring regs */
	क्रम (i = 35; i < 40; i++)
		regs[i] = 0xcccccc00 + ring_pair->index;
पूर्ण
