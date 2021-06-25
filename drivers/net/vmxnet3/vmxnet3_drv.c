<शैली गुरु>
/*
 * Linux driver क्रम VMware's vmxnet3 ethernet NIC.
 *
 * Copyright (C) 2008-2020, VMware, Inc. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; version 2 of the License and no later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, GOOD TITLE or
 * NON INFRINGEMENT. See the GNU General Public License क्रम more
 * details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St, Fअगरth Floor, Boston, MA 02110-1301 USA.
 *
 * The full GNU General Public License is included in this distribution in
 * the file called "COPYING".
 *
 * Maपूर्णांकained by: pv-drivers@vmware.com
 *
 */

#समावेश <linux/module.h>
#समावेश <net/ip6_checksum.h>

#समावेश "vmxnet3_int.h"

अक्षर vmxnet3_driver_name[] = "vmxnet3";
#घोषणा VMXNET3_DRIVER_DESC "VMware vmxnet3 virtual NIC driver"

/*
 * PCI Device ID Table
 * Last entry must be all 0s
 */
अटल स्थिर काष्ठा pci_device_id vmxnet3_pciid_table[] = अणु
	अणुPCI_VDEVICE(VMWARE, PCI_DEVICE_ID_VMWARE_VMXNET3)पूर्ण,
	अणु0पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, vmxnet3_pciid_table);

अटल पूर्णांक enable_mq = 1;

अटल व्योम
vmxnet3_ग_लिखो_mac_addr(काष्ठा vmxnet3_adapter *adapter, u8 *mac);

/*
 *    Enable/Disable the given पूर्णांकr
 */
अटल व्योम
vmxnet3_enable_पूर्णांकr(काष्ठा vmxnet3_adapter *adapter, अचिन्हित पूर्णांकr_idx)
अणु
	VMXNET3_WRITE_BAR0_REG(adapter, VMXNET3_REG_IMR + पूर्णांकr_idx * 8, 0);
पूर्ण


अटल व्योम
vmxnet3_disable_पूर्णांकr(काष्ठा vmxnet3_adapter *adapter, अचिन्हित पूर्णांकr_idx)
अणु
	VMXNET3_WRITE_BAR0_REG(adapter, VMXNET3_REG_IMR + पूर्णांकr_idx * 8, 1);
पूर्ण


/*
 *    Enable/Disable all पूर्णांकrs used by the device
 */
अटल व्योम
vmxnet3_enable_all_पूर्णांकrs(काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->पूर्णांकr.num_पूर्णांकrs; i++)
		vmxnet3_enable_पूर्णांकr(adapter, i);
	adapter->shared->devRead.पूर्णांकrConf.पूर्णांकrCtrl &=
					cpu_to_le32(~VMXNET3_IC_DISABLE_ALL);
पूर्ण


अटल व्योम
vmxnet3_disable_all_पूर्णांकrs(काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i;

	adapter->shared->devRead.पूर्णांकrConf.पूर्णांकrCtrl |=
					cpu_to_le32(VMXNET3_IC_DISABLE_ALL);
	क्रम (i = 0; i < adapter->पूर्णांकr.num_पूर्णांकrs; i++)
		vmxnet3_disable_पूर्णांकr(adapter, i);
पूर्ण


अटल व्योम
vmxnet3_ack_events(काष्ठा vmxnet3_adapter *adapter, u32 events)
अणु
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_ECR, events);
पूर्ण


अटल bool
vmxnet3_tq_stopped(काष्ठा vmxnet3_tx_queue *tq, काष्ठा vmxnet3_adapter *adapter)
अणु
	वापस tq->stopped;
पूर्ण


अटल व्योम
vmxnet3_tq_start(काष्ठा vmxnet3_tx_queue *tq, काष्ठा vmxnet3_adapter *adapter)
अणु
	tq->stopped = false;
	netअगर_start_subqueue(adapter->netdev, tq - adapter->tx_queue);
पूर्ण


अटल व्योम
vmxnet3_tq_wake(काष्ठा vmxnet3_tx_queue *tq, काष्ठा vmxnet3_adapter *adapter)
अणु
	tq->stopped = false;
	netअगर_wake_subqueue(adapter->netdev, (tq - adapter->tx_queue));
पूर्ण


अटल व्योम
vmxnet3_tq_stop(काष्ठा vmxnet3_tx_queue *tq, काष्ठा vmxnet3_adapter *adapter)
अणु
	tq->stopped = true;
	tq->num_stop++;
	netअगर_stop_subqueue(adapter->netdev, (tq - adapter->tx_queue));
पूर्ण


/*
 * Check the link state. This may start or stop the tx queue.
 */
अटल व्योम
vmxnet3_check_link(काष्ठा vmxnet3_adapter *adapter, bool affectTxQueue)
अणु
	u32 ret;
	पूर्णांक i;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD, VMXNET3_CMD_GET_LINK);
	ret = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_CMD);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);

	adapter->link_speed = ret >> 16;
	अगर (ret & 1) अणु /* Link is up. */
		netdev_info(adapter->netdev, "NIC Link is Up %d Mbps\n",
			    adapter->link_speed);
		netअगर_carrier_on(adapter->netdev);

		अगर (affectTxQueue) अणु
			क्रम (i = 0; i < adapter->num_tx_queues; i++)
				vmxnet3_tq_start(&adapter->tx_queue[i],
						 adapter);
		पूर्ण
	पूर्ण अन्यथा अणु
		netdev_info(adapter->netdev, "NIC Link is Down\n");
		netअगर_carrier_off(adapter->netdev);

		अगर (affectTxQueue) अणु
			क्रम (i = 0; i < adapter->num_tx_queues; i++)
				vmxnet3_tq_stop(&adapter->tx_queue[i], adapter);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
vmxnet3_process_events(काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	u32 events = le32_to_cpu(adapter->shared->ecr);
	अगर (!events)
		वापस;

	vmxnet3_ack_events(adapter, events);

	/* Check अगर link state has changed */
	अगर (events & VMXNET3_ECR_LINK)
		vmxnet3_check_link(adapter, true);

	/* Check अगर there is an error on xmit/recv queues */
	अगर (events & (VMXNET3_ECR_TQERR | VMXNET3_ECR_RQERR)) अणु
		spin_lock_irqsave(&adapter->cmd_lock, flags);
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_GET_QUEUE_STATUS);
		spin_unlock_irqrestore(&adapter->cmd_lock, flags);

		क्रम (i = 0; i < adapter->num_tx_queues; i++)
			अगर (adapter->tqd_start[i].status.stopped)
				dev_err(&adapter->netdev->dev,
					"%s: tq[%d] error 0x%x\n",
					adapter->netdev->name, i, le32_to_cpu(
					adapter->tqd_start[i].status.error));
		क्रम (i = 0; i < adapter->num_rx_queues; i++)
			अगर (adapter->rqd_start[i].status.stopped)
				dev_err(&adapter->netdev->dev,
					"%s: rq[%d] error 0x%x\n",
					adapter->netdev->name, i,
					adapter->rqd_start[i].status.error);

		schedule_work(&adapter->work);
	पूर्ण
पूर्ण

#अगर_घोषित __BIG_ENDIAN_BITFIELD
/*
 * The device expects the bitfields in shared काष्ठाures to be written in
 * little endian. When CPU is big endian, the following routines are used to
 * correctly पढ़ो and ग_लिखो पूर्णांकo ABI.
 * The general technique used here is : द्विगुन word bitfields are defined in
 * opposite order क्रम big endian architecture. Then beक्रमe पढ़ोing them in
 * driver the complete द्विगुन word is translated using le32_to_cpu. Similarly
 * After the driver ग_लिखोs पूर्णांकo bitfields, cpu_to_le32 is used to translate the
 * द्विगुन words पूर्णांकo required क्रमmat.
 * In order to aव्योम touching bits in shared काष्ठाure more than once, temporary
 * descriptors are used. These are passed as srcDesc to following functions.
 */
अटल व्योम vmxnet3_RxDescToCPU(स्थिर काष्ठा Vmxnet3_RxDesc *srcDesc,
				काष्ठा Vmxnet3_RxDesc *dstDesc)
अणु
	u32 *src = (u32 *)srcDesc + 2;
	u32 *dst = (u32 *)dstDesc + 2;
	dstDesc->addr = le64_to_cpu(srcDesc->addr);
	*dst = le32_to_cpu(*src);
	dstDesc->ext1 = le32_to_cpu(srcDesc->ext1);
पूर्ण

अटल व्योम vmxnet3_TxDescToLe(स्थिर काष्ठा Vmxnet3_TxDesc *srcDesc,
			       काष्ठा Vmxnet3_TxDesc *dstDesc)
अणु
	पूर्णांक i;
	u32 *src = (u32 *)(srcDesc + 1);
	u32 *dst = (u32 *)(dstDesc + 1);

	/* Working backwards so that the gen bit is set at the end. */
	क्रम (i = 2; i > 0; i--) अणु
		src--;
		dst--;
		*dst = cpu_to_le32(*src);
	पूर्ण
पूर्ण


अटल व्योम vmxnet3_RxCompToCPU(स्थिर काष्ठा Vmxnet3_RxCompDesc *srcDesc,
				काष्ठा Vmxnet3_RxCompDesc *dstDesc)
अणु
	पूर्णांक i = 0;
	u32 *src = (u32 *)srcDesc;
	u32 *dst = (u32 *)dstDesc;
	क्रम (i = 0; i < माप(काष्ठा Vmxnet3_RxCompDesc) / माप(u32); i++) अणु
		*dst = le32_to_cpu(*src);
		src++;
		dst++;
	पूर्ण
पूर्ण


/* Used to पढ़ो bitfield values from द्विगुन words. */
अटल u32 get_bitfield32(स्थिर __le32 *bitfield, u32 pos, u32 size)
अणु
	u32 temp = le32_to_cpu(*bitfield);
	u32 mask = ((1 << size) - 1) << pos;
	temp &= mask;
	temp >>= pos;
	वापस temp;
पूर्ण



#पूर्ण_अगर  /* __BIG_ENDIAN_BITFIELD */

#अगर_घोषित __BIG_ENDIAN_BITFIELD

#   define VMXNET3_TXDESC_GET_GEN(txdesc) get_bitfield32(((स्थिर __le32 *) \
			txdesc) + VMXNET3_TXD_GEN_DWORD_SHIFT, \
			VMXNET3_TXD_GEN_SHIFT, VMXNET3_TXD_GEN_SIZE)
#   define VMXNET3_TXDESC_GET_EOP(txdesc) get_bitfield32(((स्थिर __le32 *) \
			txdesc) + VMXNET3_TXD_EOP_DWORD_SHIFT, \
			VMXNET3_TXD_EOP_SHIFT, VMXNET3_TXD_EOP_SIZE)
#   define VMXNET3_TCD_GET_GEN(tcd) get_bitfield32(((स्थिर __le32 *)tcd) + \
			VMXNET3_TCD_GEN_DWORD_SHIFT, VMXNET3_TCD_GEN_SHIFT, \
			VMXNET3_TCD_GEN_SIZE)
#   define VMXNET3_TCD_GET_TXIDX(tcd) get_bitfield32((स्थिर __le32 *)tcd, \
			VMXNET3_TCD_TXIDX_SHIFT, VMXNET3_TCD_TXIDX_SIZE)
#   define vmxnet3_getRxComp(dstrcd, rcd, पंचांगp) करो अणु \
			(dstrcd) = (पंचांगp); \
			vmxnet3_RxCompToCPU((rcd), (पंचांगp)); \
		पूर्ण जबतक (0)
#   define vmxnet3_getRxDesc(dstrxd, rxd, पंचांगp) करो अणु \
			(dstrxd) = (पंचांगp); \
			vmxnet3_RxDescToCPU((rxd), (पंचांगp)); \
		पूर्ण जबतक (0)

#अन्यथा

#   define VMXNET3_TXDESC_GET_GEN(txdesc) ((txdesc)->gen)
#   define VMXNET3_TXDESC_GET_EOP(txdesc) ((txdesc)->eop)
#   define VMXNET3_TCD_GET_GEN(tcd) ((tcd)->gen)
#   define VMXNET3_TCD_GET_TXIDX(tcd) ((tcd)->txdIdx)
#   define vmxnet3_getRxComp(dstrcd, rcd, पंचांगp) (dstrcd) = (rcd)
#   define vmxnet3_getRxDesc(dstrxd, rxd, पंचांगp) (dstrxd) = (rxd)

#पूर्ण_अगर /* __BIG_ENDIAN_BITFIELD  */


अटल व्योम
vmxnet3_unmap_tx_buf(काष्ठा vmxnet3_tx_buf_info *tbi,
		     काष्ठा pci_dev *pdev)
अणु
	अगर (tbi->map_type == VMXNET3_MAP_SINGLE)
		dma_unmap_single(&pdev->dev, tbi->dma_addr, tbi->len,
				 PCI_DMA_TODEVICE);
	अन्यथा अगर (tbi->map_type == VMXNET3_MAP_PAGE)
		dma_unmap_page(&pdev->dev, tbi->dma_addr, tbi->len,
			       PCI_DMA_TODEVICE);
	अन्यथा
		BUG_ON(tbi->map_type != VMXNET3_MAP_NONE);

	tbi->map_type = VMXNET3_MAP_NONE; /* to help debugging */
पूर्ण


अटल पूर्णांक
vmxnet3_unmap_pkt(u32 eop_idx, काष्ठा vmxnet3_tx_queue *tq,
		  काष्ठा pci_dev *pdev,	काष्ठा vmxnet3_adapter *adapter)
अणु
	काष्ठा sk_buff *skb;
	पूर्णांक entries = 0;

	/* no out of order completion */
	BUG_ON(tq->buf_info[eop_idx].sop_idx != tq->tx_ring.next2comp);
	BUG_ON(VMXNET3_TXDESC_GET_EOP(&(tq->tx_ring.base[eop_idx].txd)) != 1);

	skb = tq->buf_info[eop_idx].skb;
	BUG_ON(skb == शून्य);
	tq->buf_info[eop_idx].skb = शून्य;

	VMXNET3_INC_RING_IDX_ONLY(eop_idx, tq->tx_ring.size);

	जबतक (tq->tx_ring.next2comp != eop_idx) अणु
		vmxnet3_unmap_tx_buf(tq->buf_info + tq->tx_ring.next2comp,
				     pdev);

		/* update next2comp w/o tx_lock. Since we are marking more,
		 * instead of less, tx ring entries avail, the worst हाल is
		 * that the tx routine incorrectly re-queues a pkt due to
		 * insufficient tx ring entries.
		 */
		vmxnet3_cmd_ring_adv_next2comp(&tq->tx_ring);
		entries++;
	पूर्ण

	dev_kमुक्त_skb_any(skb);
	वापस entries;
पूर्ण


अटल पूर्णांक
vmxnet3_tq_tx_complete(काष्ठा vmxnet3_tx_queue *tq,
			काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक completed = 0;
	जोड़ Vmxnet3_GenericDesc *gdesc;

	gdesc = tq->comp_ring.base + tq->comp_ring.next2proc;
	जबतक (VMXNET3_TCD_GET_GEN(&gdesc->tcd) == tq->comp_ring.gen) अणु
		/* Prevent any &gdesc->tcd field from being (speculatively)
		 * पढ़ो beक्रमe (&gdesc->tcd)->gen is पढ़ो.
		 */
		dma_rmb();

		completed += vmxnet3_unmap_pkt(VMXNET3_TCD_GET_TXIDX(
					       &gdesc->tcd), tq, adapter->pdev,
					       adapter);

		vmxnet3_comp_ring_adv_next2proc(&tq->comp_ring);
		gdesc = tq->comp_ring.base + tq->comp_ring.next2proc;
	पूर्ण

	अगर (completed) अणु
		spin_lock(&tq->tx_lock);
		अगर (unlikely(vmxnet3_tq_stopped(tq, adapter) &&
			     vmxnet3_cmd_ring_desc_avail(&tq->tx_ring) >
			     VMXNET3_WAKE_QUEUE_THRESHOLD(tq) &&
			     netअगर_carrier_ok(adapter->netdev))) अणु
			vmxnet3_tq_wake(tq, adapter);
		पूर्ण
		spin_unlock(&tq->tx_lock);
	पूर्ण
	वापस completed;
पूर्ण


अटल व्योम
vmxnet3_tq_cleanup(काष्ठा vmxnet3_tx_queue *tq,
		   काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i;

	जबतक (tq->tx_ring.next2comp != tq->tx_ring.next2fill) अणु
		काष्ठा vmxnet3_tx_buf_info *tbi;

		tbi = tq->buf_info + tq->tx_ring.next2comp;

		vmxnet3_unmap_tx_buf(tbi, adapter->pdev);
		अगर (tbi->skb) अणु
			dev_kमुक्त_skb_any(tbi->skb);
			tbi->skb = शून्य;
		पूर्ण
		vmxnet3_cmd_ring_adv_next2comp(&tq->tx_ring);
	पूर्ण

	/* sanity check, verअगरy all buffers are indeed unmapped and मुक्तd */
	क्रम (i = 0; i < tq->tx_ring.size; i++) अणु
		BUG_ON(tq->buf_info[i].skb != शून्य ||
		       tq->buf_info[i].map_type != VMXNET3_MAP_NONE);
	पूर्ण

	tq->tx_ring.gen = VMXNET3_INIT_GEN;
	tq->tx_ring.next2fill = tq->tx_ring.next2comp = 0;

	tq->comp_ring.gen = VMXNET3_INIT_GEN;
	tq->comp_ring.next2proc = 0;
पूर्ण


अटल व्योम
vmxnet3_tq_destroy(काष्ठा vmxnet3_tx_queue *tq,
		   काष्ठा vmxnet3_adapter *adapter)
अणु
	अगर (tq->tx_ring.base) अणु
		dma_मुक्त_coherent(&adapter->pdev->dev, tq->tx_ring.size *
				  माप(काष्ठा Vmxnet3_TxDesc),
				  tq->tx_ring.base, tq->tx_ring.basePA);
		tq->tx_ring.base = शून्य;
	पूर्ण
	अगर (tq->data_ring.base) अणु
		dma_मुक्त_coherent(&adapter->pdev->dev,
				  tq->data_ring.size * tq->txdata_desc_size,
				  tq->data_ring.base, tq->data_ring.basePA);
		tq->data_ring.base = शून्य;
	पूर्ण
	अगर (tq->comp_ring.base) अणु
		dma_मुक्त_coherent(&adapter->pdev->dev, tq->comp_ring.size *
				  माप(काष्ठा Vmxnet3_TxCompDesc),
				  tq->comp_ring.base, tq->comp_ring.basePA);
		tq->comp_ring.base = शून्य;
	पूर्ण
	kमुक्त(tq->buf_info);
	tq->buf_info = शून्य;
पूर्ण


/* Destroy all tx queues */
व्योम
vmxnet3_tq_destroy_all(काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		vmxnet3_tq_destroy(&adapter->tx_queue[i], adapter);
पूर्ण


अटल व्योम
vmxnet3_tq_init(काष्ठा vmxnet3_tx_queue *tq,
		काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i;

	/* reset the tx ring contents to 0 and reset the tx ring states */
	स_रखो(tq->tx_ring.base, 0, tq->tx_ring.size *
	       माप(काष्ठा Vmxnet3_TxDesc));
	tq->tx_ring.next2fill = tq->tx_ring.next2comp = 0;
	tq->tx_ring.gen = VMXNET3_INIT_GEN;

	स_रखो(tq->data_ring.base, 0,
	       tq->data_ring.size * tq->txdata_desc_size);

	/* reset the tx comp ring contents to 0 and reset comp ring states */
	स_रखो(tq->comp_ring.base, 0, tq->comp_ring.size *
	       माप(काष्ठा Vmxnet3_TxCompDesc));
	tq->comp_ring.next2proc = 0;
	tq->comp_ring.gen = VMXNET3_INIT_GEN;

	/* reset the bookkeeping data */
	स_रखो(tq->buf_info, 0, माप(tq->buf_info[0]) * tq->tx_ring.size);
	क्रम (i = 0; i < tq->tx_ring.size; i++)
		tq->buf_info[i].map_type = VMXNET3_MAP_NONE;

	/* stats are not reset */
पूर्ण


अटल पूर्णांक
vmxnet3_tq_create(काष्ठा vmxnet3_tx_queue *tq,
		  काष्ठा vmxnet3_adapter *adapter)
अणु
	BUG_ON(tq->tx_ring.base || tq->data_ring.base ||
	       tq->comp_ring.base || tq->buf_info);

	tq->tx_ring.base = dma_alloc_coherent(&adapter->pdev->dev,
			tq->tx_ring.size * माप(काष्ठा Vmxnet3_TxDesc),
			&tq->tx_ring.basePA, GFP_KERNEL);
	अगर (!tq->tx_ring.base) अणु
		netdev_err(adapter->netdev, "failed to allocate tx ring\n");
		जाओ err;
	पूर्ण

	tq->data_ring.base = dma_alloc_coherent(&adapter->pdev->dev,
			tq->data_ring.size * tq->txdata_desc_size,
			&tq->data_ring.basePA, GFP_KERNEL);
	अगर (!tq->data_ring.base) अणु
		netdev_err(adapter->netdev, "failed to allocate tx data ring\n");
		जाओ err;
	पूर्ण

	tq->comp_ring.base = dma_alloc_coherent(&adapter->pdev->dev,
			tq->comp_ring.size * माप(काष्ठा Vmxnet3_TxCompDesc),
			&tq->comp_ring.basePA, GFP_KERNEL);
	अगर (!tq->comp_ring.base) अणु
		netdev_err(adapter->netdev, "failed to allocate tx comp ring\n");
		जाओ err;
	पूर्ण

	tq->buf_info = kसुस्मृति_node(tq->tx_ring.size, माप(tq->buf_info[0]),
				    GFP_KERNEL,
				    dev_to_node(&adapter->pdev->dev));
	अगर (!tq->buf_info)
		जाओ err;

	वापस 0;

err:
	vmxnet3_tq_destroy(tq, adapter);
	वापस -ENOMEM;
पूर्ण

अटल व्योम
vmxnet3_tq_cleanup_all(काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		vmxnet3_tq_cleanup(&adapter->tx_queue[i], adapter);
पूर्ण

/*
 *    starting from ring->next2fill, allocate rx buffers क्रम the given ring
 *    of the rx queue and update the rx desc. stop after @num_to_alloc buffers
 *    are allocated or allocation fails
 */

अटल पूर्णांक
vmxnet3_rq_alloc_rx_buf(काष्ठा vmxnet3_rx_queue *rq, u32 ring_idx,
			पूर्णांक num_to_alloc, काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक num_allocated = 0;
	काष्ठा vmxnet3_rx_buf_info *rbi_base = rq->buf_info[ring_idx];
	काष्ठा vmxnet3_cmd_ring *ring = &rq->rx_ring[ring_idx];
	u32 val;

	जबतक (num_allocated <= num_to_alloc) अणु
		काष्ठा vmxnet3_rx_buf_info *rbi;
		जोड़ Vmxnet3_GenericDesc *gd;

		rbi = rbi_base + ring->next2fill;
		gd = ring->base + ring->next2fill;

		अगर (rbi->buf_type == VMXNET3_RX_BUF_SKB) अणु
			अगर (rbi->skb == शून्य) अणु
				rbi->skb = __netdev_alloc_skb_ip_align(adapter->netdev,
								       rbi->len,
								       GFP_KERNEL);
				अगर (unlikely(rbi->skb == शून्य)) अणु
					rq->stats.rx_buf_alloc_failure++;
					अवरोध;
				पूर्ण

				rbi->dma_addr = dma_map_single(
						&adapter->pdev->dev,
						rbi->skb->data, rbi->len,
						PCI_DMA_FROMDEVICE);
				अगर (dma_mapping_error(&adapter->pdev->dev,
						      rbi->dma_addr)) अणु
					dev_kमुक्त_skb_any(rbi->skb);
					rq->stats.rx_buf_alloc_failure++;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* rx buffer skipped by the device */
			पूर्ण
			val = VMXNET3_RXD_BTYPE_HEAD << VMXNET3_RXD_BTYPE_SHIFT;
		पूर्ण अन्यथा अणु
			BUG_ON(rbi->buf_type != VMXNET3_RX_BUF_PAGE ||
			       rbi->len  != PAGE_SIZE);

			अगर (rbi->page == शून्य) अणु
				rbi->page = alloc_page(GFP_ATOMIC);
				अगर (unlikely(rbi->page == शून्य)) अणु
					rq->stats.rx_buf_alloc_failure++;
					अवरोध;
				पूर्ण
				rbi->dma_addr = dma_map_page(
						&adapter->pdev->dev,
						rbi->page, 0, PAGE_SIZE,
						PCI_DMA_FROMDEVICE);
				अगर (dma_mapping_error(&adapter->pdev->dev,
						      rbi->dma_addr)) अणु
					put_page(rbi->page);
					rq->stats.rx_buf_alloc_failure++;
					अवरोध;
				पूर्ण
			पूर्ण अन्यथा अणु
				/* rx buffers skipped by the device */
			पूर्ण
			val = VMXNET3_RXD_BTYPE_BODY << VMXNET3_RXD_BTYPE_SHIFT;
		पूर्ण

		gd->rxd.addr = cpu_to_le64(rbi->dma_addr);
		gd->dword[2] = cpu_to_le32((!ring->gen << VMXNET3_RXD_GEN_SHIFT)
					   | val | rbi->len);

		/* Fill the last buffer but करोnt mark it पढ़ोy, or अन्यथा the
		 * device will think that the queue is full */
		अगर (num_allocated == num_to_alloc)
			अवरोध;

		gd->dword[2] |= cpu_to_le32(ring->gen << VMXNET3_RXD_GEN_SHIFT);
		num_allocated++;
		vmxnet3_cmd_ring_adv_next2fill(ring);
	पूर्ण

	netdev_dbg(adapter->netdev,
		"alloc_rx_buf: %d allocated, next2fill %u, next2comp %u\n",
		num_allocated, ring->next2fill, ring->next2comp);

	/* so that the device can distinguish a full ring and an empty ring */
	BUG_ON(num_allocated != 0 && ring->next2fill == ring->next2comp);

	वापस num_allocated;
पूर्ण


अटल व्योम
vmxnet3_append_frag(काष्ठा sk_buff *skb, काष्ठा Vmxnet3_RxCompDesc *rcd,
		    काष्ठा vmxnet3_rx_buf_info *rbi)
अणु
	skb_frag_t *frag = skb_shinfo(skb)->frags + skb_shinfo(skb)->nr_frags;

	BUG_ON(skb_shinfo(skb)->nr_frags >= MAX_SKB_FRAGS);

	__skb_frag_set_page(frag, rbi->page);
	skb_frag_off_set(frag, 0);
	skb_frag_size_set(frag, rcd->len);
	skb->data_len += rcd->len;
	skb->truesize += PAGE_SIZE;
	skb_shinfo(skb)->nr_frags++;
पूर्ण


अटल पूर्णांक
vmxnet3_map_pkt(काष्ठा sk_buff *skb, काष्ठा vmxnet3_tx_ctx *ctx,
		काष्ठा vmxnet3_tx_queue *tq, काष्ठा pci_dev *pdev,
		काष्ठा vmxnet3_adapter *adapter)
अणु
	u32 dw2, len;
	अचिन्हित दीर्घ buf_offset;
	पूर्णांक i;
	जोड़ Vmxnet3_GenericDesc *gdesc;
	काष्ठा vmxnet3_tx_buf_info *tbi = शून्य;

	BUG_ON(ctx->copy_size > skb_headlen(skb));

	/* use the previous gen bit क्रम the SOP desc */
	dw2 = (tq->tx_ring.gen ^ 0x1) << VMXNET3_TXD_GEN_SHIFT;

	ctx->sop_txd = tq->tx_ring.base + tq->tx_ring.next2fill;
	gdesc = ctx->sop_txd; /* both loops below can be skipped */

	/* no need to map the buffer अगर headers are copied */
	अगर (ctx->copy_size) अणु
		ctx->sop_txd->txd.addr = cpu_to_le64(tq->data_ring.basePA +
					tq->tx_ring.next2fill *
					tq->txdata_desc_size);
		ctx->sop_txd->dword[2] = cpu_to_le32(dw2 | ctx->copy_size);
		ctx->sop_txd->dword[3] = 0;

		tbi = tq->buf_info + tq->tx_ring.next2fill;
		tbi->map_type = VMXNET3_MAP_NONE;

		netdev_dbg(adapter->netdev,
			"txd[%u]: 0x%Lx 0x%x 0x%x\n",
			tq->tx_ring.next2fill,
			le64_to_cpu(ctx->sop_txd->txd.addr),
			ctx->sop_txd->dword[2], ctx->sop_txd->dword[3]);
		vmxnet3_cmd_ring_adv_next2fill(&tq->tx_ring);

		/* use the right gen क्रम non-SOP desc */
		dw2 = tq->tx_ring.gen << VMXNET3_TXD_GEN_SHIFT;
	पूर्ण

	/* linear part can use multiple tx desc अगर it's big */
	len = skb_headlen(skb) - ctx->copy_size;
	buf_offset = ctx->copy_size;
	जबतक (len) अणु
		u32 buf_size;

		अगर (len < VMXNET3_MAX_TX_BUF_SIZE) अणु
			buf_size = len;
			dw2 |= len;
		पूर्ण अन्यथा अणु
			buf_size = VMXNET3_MAX_TX_BUF_SIZE;
			/* spec says that क्रम TxDesc.len, 0 == 2^14 */
		पूर्ण

		tbi = tq->buf_info + tq->tx_ring.next2fill;
		tbi->map_type = VMXNET3_MAP_SINGLE;
		tbi->dma_addr = dma_map_single(&adapter->pdev->dev,
				skb->data + buf_offset, buf_size,
				PCI_DMA_TODEVICE);
		अगर (dma_mapping_error(&adapter->pdev->dev, tbi->dma_addr))
			वापस -EFAULT;

		tbi->len = buf_size;

		gdesc = tq->tx_ring.base + tq->tx_ring.next2fill;
		BUG_ON(gdesc->txd.gen == tq->tx_ring.gen);

		gdesc->txd.addr = cpu_to_le64(tbi->dma_addr);
		gdesc->dword[2] = cpu_to_le32(dw2);
		gdesc->dword[3] = 0;

		netdev_dbg(adapter->netdev,
			"txd[%u]: 0x%Lx 0x%x 0x%x\n",
			tq->tx_ring.next2fill, le64_to_cpu(gdesc->txd.addr),
			le32_to_cpu(gdesc->dword[2]), gdesc->dword[3]);
		vmxnet3_cmd_ring_adv_next2fill(&tq->tx_ring);
		dw2 = tq->tx_ring.gen << VMXNET3_TXD_GEN_SHIFT;

		len -= buf_size;
		buf_offset += buf_size;
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		u32 buf_size;

		buf_offset = 0;
		len = skb_frag_size(frag);
		जबतक (len) अणु
			tbi = tq->buf_info + tq->tx_ring.next2fill;
			अगर (len < VMXNET3_MAX_TX_BUF_SIZE) अणु
				buf_size = len;
				dw2 |= len;
			पूर्ण अन्यथा अणु
				buf_size = VMXNET3_MAX_TX_BUF_SIZE;
				/* spec says that क्रम TxDesc.len, 0 == 2^14 */
			पूर्ण
			tbi->map_type = VMXNET3_MAP_PAGE;
			tbi->dma_addr = skb_frag_dma_map(&adapter->pdev->dev, frag,
							 buf_offset, buf_size,
							 DMA_TO_DEVICE);
			अगर (dma_mapping_error(&adapter->pdev->dev, tbi->dma_addr))
				वापस -EFAULT;

			tbi->len = buf_size;

			gdesc = tq->tx_ring.base + tq->tx_ring.next2fill;
			BUG_ON(gdesc->txd.gen == tq->tx_ring.gen);

			gdesc->txd.addr = cpu_to_le64(tbi->dma_addr);
			gdesc->dword[2] = cpu_to_le32(dw2);
			gdesc->dword[3] = 0;

			netdev_dbg(adapter->netdev,
				"txd[%u]: 0x%llx %u %u\n",
				tq->tx_ring.next2fill, le64_to_cpu(gdesc->txd.addr),
				le32_to_cpu(gdesc->dword[2]), gdesc->dword[3]);
			vmxnet3_cmd_ring_adv_next2fill(&tq->tx_ring);
			dw2 = tq->tx_ring.gen << VMXNET3_TXD_GEN_SHIFT;

			len -= buf_size;
			buf_offset += buf_size;
		पूर्ण
	पूर्ण

	ctx->eop_txd = gdesc;

	/* set the last buf_info क्रम the pkt */
	tbi->skb = skb;
	tbi->sop_idx = ctx->sop_txd - tq->tx_ring.base;

	वापस 0;
पूर्ण


/* Init all tx queues */
अटल व्योम
vmxnet3_tq_init_all(काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		vmxnet3_tq_init(&adapter->tx_queue[i], adapter);
पूर्ण


/*
 *    parse relevant protocol headers:
 *      For a tso pkt, relevant headers are L2/3/4 including options
 *      For a pkt requesting csum offloading, they are L2/3 and may include L4
 *      अगर it's a TCP/UDP pkt
 *
 * Returns:
 *    -1:  error happens during parsing
 *     0:  protocol headers parsed, but too big to be copied
 *     1:  protocol headers parsed and copied
 *
 * Other effects:
 *    1. related *ctx fields are updated.
 *    2. ctx->copy_size is # of bytes copied
 *    3. the portion to be copied is guaranteed to be in the linear part
 *
 */
अटल पूर्णांक
vmxnet3_parse_hdr(काष्ठा sk_buff *skb, काष्ठा vmxnet3_tx_queue *tq,
		  काष्ठा vmxnet3_tx_ctx *ctx,
		  काष्ठा vmxnet3_adapter *adapter)
अणु
	u8 protocol = 0;

	अगर (ctx->mss) अणु	/* TSO */
		अगर (VMXNET3_VERSION_GE_4(adapter) && skb->encapsulation) अणु
			ctx->l4_offset = skb_inner_transport_offset(skb);
			ctx->l4_hdr_size = inner_tcp_hdrlen(skb);
			ctx->copy_size = ctx->l4_offset + ctx->l4_hdr_size;
		पूर्ण अन्यथा अणु
			ctx->l4_offset = skb_transport_offset(skb);
			ctx->l4_hdr_size = tcp_hdrlen(skb);
			ctx->copy_size = ctx->l4_offset + ctx->l4_hdr_size;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
			/* For encap packets, skb_checksum_start_offset refers
			 * to inner L4 offset. Thus, below works क्रम encap as
			 * well as non-encap हाल
			 */
			ctx->l4_offset = skb_checksum_start_offset(skb);

			अगर (VMXNET3_VERSION_GE_4(adapter) &&
			    skb->encapsulation) अणु
				काष्ठा iphdr *iph = inner_ip_hdr(skb);

				अगर (iph->version == 4) अणु
					protocol = iph->protocol;
				पूर्ण अन्यथा अणु
					स्थिर काष्ठा ipv6hdr *ipv6h;

					ipv6h = inner_ipv6_hdr(skb);
					protocol = ipv6h->nexthdr;
				पूर्ण
			पूर्ण अन्यथा अणु
				अगर (ctx->ipv4) अणु
					स्थिर काष्ठा iphdr *iph = ip_hdr(skb);

					protocol = iph->protocol;
				पूर्ण अन्यथा अगर (ctx->ipv6) अणु
					स्थिर काष्ठा ipv6hdr *ipv6h;

					ipv6h = ipv6_hdr(skb);
					protocol = ipv6h->nexthdr;
				पूर्ण
			पूर्ण

			चयन (protocol) अणु
			हाल IPPROTO_TCP:
				ctx->l4_hdr_size = skb->encapsulation ? inner_tcp_hdrlen(skb) :
						   tcp_hdrlen(skb);
				अवरोध;
			हाल IPPROTO_UDP:
				ctx->l4_hdr_size = माप(काष्ठा udphdr);
				अवरोध;
			शेष:
				ctx->l4_hdr_size = 0;
				अवरोध;
			पूर्ण

			ctx->copy_size = min(ctx->l4_offset +
					 ctx->l4_hdr_size, skb->len);
		पूर्ण अन्यथा अणु
			ctx->l4_offset = 0;
			ctx->l4_hdr_size = 0;
			/* copy as much as allowed */
			ctx->copy_size = min_t(अचिन्हित पूर्णांक,
					       tq->txdata_desc_size,
					       skb_headlen(skb));
		पूर्ण

		अगर (skb->len <= VMXNET3_HDR_COPY_SIZE)
			ctx->copy_size = skb->len;

		/* make sure headers are accessible directly */
		अगर (unlikely(!pskb_may_pull(skb, ctx->copy_size)))
			जाओ err;
	पूर्ण

	अगर (unlikely(ctx->copy_size > tq->txdata_desc_size)) अणु
		tq->stats.oversized_hdr++;
		ctx->copy_size = 0;
		वापस 0;
	पूर्ण

	वापस 1;
err:
	वापस -1;
पूर्ण

/*
 *    copy relevant protocol headers to the transmit ring:
 *      For a tso pkt, relevant headers are L2/3/4 including options
 *      For a pkt requesting csum offloading, they are L2/3 and may include L4
 *      अगर it's a TCP/UDP pkt
 *
 *
 *    Note that this requires that vmxnet3_parse_hdr be called first to set the
 *      appropriate bits in ctx first
 */
अटल व्योम
vmxnet3_copy_hdr(काष्ठा sk_buff *skb, काष्ठा vmxnet3_tx_queue *tq,
		 काष्ठा vmxnet3_tx_ctx *ctx,
		 काष्ठा vmxnet3_adapter *adapter)
अणु
	काष्ठा Vmxnet3_TxDataDesc *tdd;

	tdd = (काष्ठा Vmxnet3_TxDataDesc *)((u8 *)tq->data_ring.base +
					    tq->tx_ring.next2fill *
					    tq->txdata_desc_size);

	स_नकल(tdd->data, skb->data, ctx->copy_size);
	netdev_dbg(adapter->netdev,
		"copy %u bytes to dataRing[%u]\n",
		ctx->copy_size, tq->tx_ring.next2fill);
पूर्ण


अटल व्योम
vmxnet3_prepare_inner_tso(काष्ठा sk_buff *skb,
			  काष्ठा vmxnet3_tx_ctx *ctx)
अणु
	काष्ठा tcphdr *tcph = inner_tcp_hdr(skb);
	काष्ठा iphdr *iph = inner_ip_hdr(skb);

	अगर (iph->version == 4) अणु
		iph->check = 0;
		tcph->check = ~csum_tcpudp_magic(iph->saddr, iph->daddr, 0,
						 IPPROTO_TCP, 0);
	पूर्ण अन्यथा अणु
		काष्ठा ipv6hdr *iph = inner_ipv6_hdr(skb);

		tcph->check = ~csum_ipv6_magic(&iph->saddr, &iph->daddr, 0,
					       IPPROTO_TCP, 0);
	पूर्ण
पूर्ण

अटल व्योम
vmxnet3_prepare_tso(काष्ठा sk_buff *skb,
		    काष्ठा vmxnet3_tx_ctx *ctx)
अणु
	काष्ठा tcphdr *tcph = tcp_hdr(skb);

	अगर (ctx->ipv4) अणु
		काष्ठा iphdr *iph = ip_hdr(skb);

		iph->check = 0;
		tcph->check = ~csum_tcpudp_magic(iph->saddr, iph->daddr, 0,
						 IPPROTO_TCP, 0);
	पूर्ण अन्यथा अगर (ctx->ipv6) अणु
		tcp_v6_gso_csum_prep(skb);
	पूर्ण
पूर्ण

अटल पूर्णांक txd_estimate(स्थिर काष्ठा sk_buff *skb)
अणु
	पूर्णांक count = VMXNET3_TXD_NEEDED(skb_headlen(skb)) + 1;
	पूर्णांक i;

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		count += VMXNET3_TXD_NEEDED(skb_frag_size(frag));
	पूर्ण
	वापस count;
पूर्ण

/*
 * Transmits a pkt thru a given tq
 * Returns:
 *    NETDEV_TX_OK:      descriptors are setup successfully
 *    NETDEV_TX_OK:      error occurred, the pkt is dropped
 *    NETDEV_TX_BUSY:    tx ring is full, queue is stopped
 *
 * Side-effects:
 *    1. tx ring may be changed
 *    2. tq stats may be updated accordingly
 *    3. shared->txNumDeferred may be updated
 */

अटल पूर्णांक
vmxnet3_tq_xmit(काष्ठा sk_buff *skb, काष्ठा vmxnet3_tx_queue *tq,
		काष्ठा vmxnet3_adapter *adapter, काष्ठा net_device *netdev)
अणु
	पूर्णांक ret;
	u32 count;
	पूर्णांक num_pkts;
	पूर्णांक tx_num_deferred;
	अचिन्हित दीर्घ flags;
	काष्ठा vmxnet3_tx_ctx ctx;
	जोड़ Vmxnet3_GenericDesc *gdesc;
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	/* Use temporary descriptor to aव्योम touching bits multiple बार */
	जोड़ Vmxnet3_GenericDesc tempTxDesc;
#पूर्ण_अगर

	count = txd_estimate(skb);

	ctx.ipv4 = (vlan_get_protocol(skb) == cpu_to_be16(ETH_P_IP));
	ctx.ipv6 = (vlan_get_protocol(skb) == cpu_to_be16(ETH_P_IPV6));

	ctx.mss = skb_shinfo(skb)->gso_size;
	अगर (ctx.mss) अणु
		अगर (skb_header_cloned(skb)) अणु
			अगर (unlikely(pskb_expand_head(skb, 0, 0,
						      GFP_ATOMIC) != 0)) अणु
				tq->stats.drop_tso++;
				जाओ drop_pkt;
			पूर्ण
			tq->stats.copy_skb_header++;
		पूर्ण
		अगर (skb->encapsulation) अणु
			vmxnet3_prepare_inner_tso(skb, &ctx);
		पूर्ण अन्यथा अणु
			vmxnet3_prepare_tso(skb, &ctx);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (unlikely(count > VMXNET3_MAX_TXD_PER_PKT)) अणु

			/* non-tso pkts must not use more than
			 * VMXNET3_MAX_TXD_PER_PKT entries
			 */
			अगर (skb_linearize(skb) != 0) अणु
				tq->stats.drop_too_many_frags++;
				जाओ drop_pkt;
			पूर्ण
			tq->stats.linearized++;

			/* recalculate the # of descriptors to use */
			count = VMXNET3_TXD_NEEDED(skb_headlen(skb)) + 1;
		पूर्ण
	पूर्ण

	ret = vmxnet3_parse_hdr(skb, tq, &ctx, adapter);
	अगर (ret >= 0) अणु
		BUG_ON(ret <= 0 && ctx.copy_size != 0);
		/* hdrs parsed, check against other limits */
		अगर (ctx.mss) अणु
			अगर (unlikely(ctx.l4_offset + ctx.l4_hdr_size >
				     VMXNET3_MAX_TX_BUF_SIZE)) अणु
				tq->stats.drop_oversized_hdr++;
				जाओ drop_pkt;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
				अगर (unlikely(ctx.l4_offset +
					     skb->csum_offset >
					     VMXNET3_MAX_CSUM_OFFSET)) अणु
					tq->stats.drop_oversized_hdr++;
					जाओ drop_pkt;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		tq->stats.drop_hdr_inspect_err++;
		जाओ drop_pkt;
	पूर्ण

	spin_lock_irqsave(&tq->tx_lock, flags);

	अगर (count > vmxnet3_cmd_ring_desc_avail(&tq->tx_ring)) अणु
		tq->stats.tx_ring_full++;
		netdev_dbg(adapter->netdev,
			"tx queue stopped on %s, next2comp %u"
			" next2fill %u\n", adapter->netdev->name,
			tq->tx_ring.next2comp, tq->tx_ring.next2fill);

		vmxnet3_tq_stop(tq, adapter);
		spin_unlock_irqrestore(&tq->tx_lock, flags);
		वापस NETDEV_TX_BUSY;
	पूर्ण


	vmxnet3_copy_hdr(skb, tq, &ctx, adapter);

	/* fill tx descs related to addr & len */
	अगर (vmxnet3_map_pkt(skb, &ctx, tq, adapter->pdev, adapter))
		जाओ unlock_drop_pkt;

	/* setup the EOP desc */
	ctx.eop_txd->dword[3] = cpu_to_le32(VMXNET3_TXD_CQ | VMXNET3_TXD_EOP);

	/* setup the SOP desc */
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	gdesc = &tempTxDesc;
	gdesc->dword[2] = ctx.sop_txd->dword[2];
	gdesc->dword[3] = ctx.sop_txd->dword[3];
#अन्यथा
	gdesc = ctx.sop_txd;
#पूर्ण_अगर
	tx_num_deferred = le32_to_cpu(tq->shared->txNumDeferred);
	अगर (ctx.mss) अणु
		अगर (VMXNET3_VERSION_GE_4(adapter) && skb->encapsulation) अणु
			gdesc->txd.hlen = ctx.l4_offset + ctx.l4_hdr_size;
			gdesc->txd.om = VMXNET3_OM_ENCAP;
			gdesc->txd.msscof = ctx.mss;

			अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEL_CSUM)
				gdesc->txd.oco = 1;
		पूर्ण अन्यथा अणु
			gdesc->txd.hlen = ctx.l4_offset + ctx.l4_hdr_size;
			gdesc->txd.om = VMXNET3_OM_TSO;
			gdesc->txd.msscof = ctx.mss;
		पूर्ण
		num_pkts = (skb->len - gdesc->txd.hlen + ctx.mss - 1) / ctx.mss;
	पूर्ण अन्यथा अणु
		अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
			अगर (VMXNET3_VERSION_GE_4(adapter) &&
			    skb->encapsulation) अणु
				gdesc->txd.hlen = ctx.l4_offset +
						  ctx.l4_hdr_size;
				gdesc->txd.om = VMXNET3_OM_ENCAP;
				gdesc->txd.msscof = 0;		/* Reserved */
			पूर्ण अन्यथा अणु
				gdesc->txd.hlen = ctx.l4_offset;
				gdesc->txd.om = VMXNET3_OM_CSUM;
				gdesc->txd.msscof = ctx.l4_offset +
						    skb->csum_offset;
			पूर्ण
		पूर्ण अन्यथा अणु
			gdesc->txd.om = 0;
			gdesc->txd.msscof = 0;
		पूर्ण
		num_pkts = 1;
	पूर्ण
	le32_add_cpu(&tq->shared->txNumDeferred, num_pkts);
	tx_num_deferred += num_pkts;

	अगर (skb_vlan_tag_present(skb)) अणु
		gdesc->txd.ti = 1;
		gdesc->txd.tci = skb_vlan_tag_get(skb);
	पूर्ण

	/* Ensure that the ग_लिखो to (&gdesc->txd)->gen will be observed after
	 * all other ग_लिखोs to &gdesc->txd.
	 */
	dma_wmb();

	/* finally flips the GEN bit of the SOP desc. */
	gdesc->dword[2] = cpu_to_le32(le32_to_cpu(gdesc->dword[2]) ^
						  VMXNET3_TXD_GEN);
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	/* Finished updating in bitfields of Tx Desc, so ग_लिखो them in original
	 * place.
	 */
	vmxnet3_TxDescToLe((काष्ठा Vmxnet3_TxDesc *)gdesc,
			   (काष्ठा Vmxnet3_TxDesc *)ctx.sop_txd);
	gdesc = ctx.sop_txd;
#पूर्ण_अगर
	netdev_dbg(adapter->netdev,
		"txd[%u]: SOP 0x%Lx 0x%x 0x%x\n",
		(u32)(ctx.sop_txd -
		tq->tx_ring.base), le64_to_cpu(gdesc->txd.addr),
		le32_to_cpu(gdesc->dword[2]), le32_to_cpu(gdesc->dword[3]));

	spin_unlock_irqrestore(&tq->tx_lock, flags);

	अगर (tx_num_deferred >= le32_to_cpu(tq->shared->txThreshold)) अणु
		tq->shared->txNumDeferred = 0;
		VMXNET3_WRITE_BAR0_REG(adapter,
				       VMXNET3_REG_TXPROD + tq->qid * 8,
				       tq->tx_ring.next2fill);
	पूर्ण

	वापस NETDEV_TX_OK;

unlock_drop_pkt:
	spin_unlock_irqrestore(&tq->tx_lock, flags);
drop_pkt:
	tq->stats.drop_total++;
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण


अटल netdev_tx_t
vmxnet3_xmit_frame(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	BUG_ON(skb->queue_mapping > adapter->num_tx_queues);
	वापस vmxnet3_tq_xmit(skb,
			       &adapter->tx_queue[skb->queue_mapping],
			       adapter, netdev);
पूर्ण


अटल व्योम
vmxnet3_rx_csum(काष्ठा vmxnet3_adapter *adapter,
		काष्ठा sk_buff *skb,
		जोड़ Vmxnet3_GenericDesc *gdesc)
अणु
	अगर (!gdesc->rcd.cnc && adapter->netdev->features & NETIF_F_RXCSUM) अणु
		अगर (gdesc->rcd.v4 &&
		    (le32_to_cpu(gdesc->dword[3]) &
		     VMXNET3_RCD_CSUM_OK) == VMXNET3_RCD_CSUM_OK) अणु
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			WARN_ON_ONCE(!(gdesc->rcd.tcp || gdesc->rcd.udp) &&
				     !(le32_to_cpu(gdesc->dword[0]) &
				     (1UL << VMXNET3_RCD_HDR_INNER_SHIFT)));
			WARN_ON_ONCE(gdesc->rcd.frg &&
				     !(le32_to_cpu(gdesc->dword[0]) &
				     (1UL << VMXNET3_RCD_HDR_INNER_SHIFT)));
		पूर्ण अन्यथा अगर (gdesc->rcd.v6 && (le32_to_cpu(gdesc->dword[3]) &
					     (1 << VMXNET3_RCD_TUC_SHIFT))) अणु
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			WARN_ON_ONCE(!(gdesc->rcd.tcp || gdesc->rcd.udp) &&
				     !(le32_to_cpu(gdesc->dword[0]) &
				     (1UL << VMXNET3_RCD_HDR_INNER_SHIFT)));
			WARN_ON_ONCE(gdesc->rcd.frg &&
				     !(le32_to_cpu(gdesc->dword[0]) &
				     (1UL << VMXNET3_RCD_HDR_INNER_SHIFT)));
		पूर्ण अन्यथा अणु
			अगर (gdesc->rcd.csum) अणु
				skb->csum = htons(gdesc->rcd.csum);
				skb->ip_summed = CHECKSUM_PARTIAL;
			पूर्ण अन्यथा अणु
				skb_checksum_none_निश्चित(skb);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		skb_checksum_none_निश्चित(skb);
	पूर्ण
पूर्ण


अटल व्योम
vmxnet3_rx_error(काष्ठा vmxnet3_rx_queue *rq, काष्ठा Vmxnet3_RxCompDesc *rcd,
		 काष्ठा vmxnet3_rx_ctx *ctx,  काष्ठा vmxnet3_adapter *adapter)
अणु
	rq->stats.drop_err++;
	अगर (!rcd->fcs)
		rq->stats.drop_fcs++;

	rq->stats.drop_total++;

	/*
	 * We करो not unmap and chain the rx buffer to the skb.
	 * We basically pretend this buffer is not used and will be recycled
	 * by vmxnet3_rq_alloc_rx_buf()
	 */

	/*
	 * ctx->skb may be शून्य अगर this is the first and the only one
	 * desc क्रम the pkt
	 */
	अगर (ctx->skb)
		dev_kमुक्त_skb_irq(ctx->skb);

	ctx->skb = शून्य;
पूर्ण


अटल u32
vmxnet3_get_hdr_len(काष्ठा vmxnet3_adapter *adapter, काष्ठा sk_buff *skb,
		    जोड़ Vmxnet3_GenericDesc *gdesc)
अणु
	u32 hlen, maplen;
	जोड़ अणु
		व्योम *ptr;
		काष्ठा ethhdr *eth;
		काष्ठा vlan_ethhdr *veth;
		काष्ठा iphdr *ipv4;
		काष्ठा ipv6hdr *ipv6;
		काष्ठा tcphdr *tcp;
	पूर्ण hdr;
	BUG_ON(gdesc->rcd.tcp == 0);

	maplen = skb_headlen(skb);
	अगर (unlikely(माप(काष्ठा iphdr) + माप(काष्ठा tcphdr) > maplen))
		वापस 0;

	अगर (skb->protocol == cpu_to_be16(ETH_P_8021Q) ||
	    skb->protocol == cpu_to_be16(ETH_P_8021AD))
		hlen = माप(काष्ठा vlan_ethhdr);
	अन्यथा
		hlen = माप(काष्ठा ethhdr);

	hdr.eth = eth_hdr(skb);
	अगर (gdesc->rcd.v4) अणु
		BUG_ON(hdr.eth->h_proto != htons(ETH_P_IP) &&
		       hdr.veth->h_vlan_encapsulated_proto != htons(ETH_P_IP));
		hdr.ptr += hlen;
		BUG_ON(hdr.ipv4->protocol != IPPROTO_TCP);
		hlen = hdr.ipv4->ihl << 2;
		hdr.ptr += hdr.ipv4->ihl << 2;
	पूर्ण अन्यथा अगर (gdesc->rcd.v6) अणु
		BUG_ON(hdr.eth->h_proto != htons(ETH_P_IPV6) &&
		       hdr.veth->h_vlan_encapsulated_proto != htons(ETH_P_IPV6));
		hdr.ptr += hlen;
		/* Use an estimated value, since we also need to handle
		 * TSO हाल.
		 */
		अगर (hdr.ipv6->nexthdr != IPPROTO_TCP)
			वापस माप(काष्ठा ipv6hdr) + माप(काष्ठा tcphdr);
		hlen = माप(काष्ठा ipv6hdr);
		hdr.ptr += माप(काष्ठा ipv6hdr);
	पूर्ण अन्यथा अणु
		/* Non-IP pkt, करोnt estimate header length */
		वापस 0;
	पूर्ण

	अगर (hlen + माप(काष्ठा tcphdr) > maplen)
		वापस 0;

	वापस (hlen + (hdr.tcp->करोff << 2));
पूर्ण

अटल पूर्णांक
vmxnet3_rq_rx_complete(काष्ठा vmxnet3_rx_queue *rq,
		       काष्ठा vmxnet3_adapter *adapter, पूर्णांक quota)
अणु
	अटल स्थिर u32 rxprod_reg[2] = अणु
		VMXNET3_REG_RXPROD, VMXNET3_REG_RXPROD2
	पूर्ण;
	u32 num_pkts = 0;
	bool skip_page_frags = false;
	काष्ठा Vmxnet3_RxCompDesc *rcd;
	काष्ठा vmxnet3_rx_ctx *ctx = &rq->rx_ctx;
	u16 segCnt = 0, mss = 0;
#अगर_घोषित __BIG_ENDIAN_BITFIELD
	काष्ठा Vmxnet3_RxDesc rxCmdDesc;
	काष्ठा Vmxnet3_RxCompDesc rxComp;
#पूर्ण_अगर
	vmxnet3_getRxComp(rcd, &rq->comp_ring.base[rq->comp_ring.next2proc].rcd,
			  &rxComp);
	जबतक (rcd->gen == rq->comp_ring.gen) अणु
		काष्ठा vmxnet3_rx_buf_info *rbi;
		काष्ठा sk_buff *skb, *new_skb = शून्य;
		काष्ठा page *new_page = शून्य;
		dma_addr_t new_dma_addr;
		पूर्णांक num_to_alloc;
		काष्ठा Vmxnet3_RxDesc *rxd;
		u32 idx, ring_idx;
		काष्ठा vmxnet3_cmd_ring	*ring = शून्य;
		अगर (num_pkts >= quota) अणु
			/* we may stop even beक्रमe we see the EOP desc of
			 * the current pkt
			 */
			अवरोध;
		पूर्ण

		/* Prevent any rcd field from being (speculatively) पढ़ो beक्रमe
		 * rcd->gen is पढ़ो.
		 */
		dma_rmb();

		BUG_ON(rcd->rqID != rq->qid && rcd->rqID != rq->qid2 &&
		       rcd->rqID != rq->dataRingQid);
		idx = rcd->rxdIdx;
		ring_idx = VMXNET3_GET_RING_IDX(adapter, rcd->rqID);
		ring = rq->rx_ring + ring_idx;
		vmxnet3_getRxDesc(rxd, &rq->rx_ring[ring_idx].base[idx].rxd,
				  &rxCmdDesc);
		rbi = rq->buf_info[ring_idx] + idx;

		BUG_ON(rxd->addr != rbi->dma_addr ||
		       rxd->len != rbi->len);

		अगर (unlikely(rcd->eop && rcd->err)) अणु
			vmxnet3_rx_error(rq, rcd, ctx, adapter);
			जाओ rcd_करोne;
		पूर्ण

		अगर (rcd->sop) अणु /* first buf of the pkt */
			bool rxDataRingUsed;
			u16 len;

			BUG_ON(rxd->btype != VMXNET3_RXD_BTYPE_HEAD ||
			       (rcd->rqID != rq->qid &&
				rcd->rqID != rq->dataRingQid));

			BUG_ON(rbi->buf_type != VMXNET3_RX_BUF_SKB);
			BUG_ON(ctx->skb != शून्य || rbi->skb == शून्य);

			अगर (unlikely(rcd->len == 0)) अणु
				/* Pretend the rx buffer is skipped. */
				BUG_ON(!(rcd->sop && rcd->eop));
				netdev_dbg(adapter->netdev,
					"rxRing[%u][%u] 0 length\n",
					ring_idx, idx);
				जाओ rcd_करोne;
			पूर्ण

			skip_page_frags = false;
			ctx->skb = rbi->skb;

			rxDataRingUsed =
				VMXNET3_RX_DATA_RING(adapter, rcd->rqID);
			len = rxDataRingUsed ? rcd->len : rbi->len;
			new_skb = netdev_alloc_skb_ip_align(adapter->netdev,
							    len);
			अगर (new_skb == शून्य) अणु
				/* Skb allocation failed, करो not hanकरोver this
				 * skb to stack. Reuse it. Drop the existing pkt
				 */
				rq->stats.rx_buf_alloc_failure++;
				ctx->skb = शून्य;
				rq->stats.drop_total++;
				skip_page_frags = true;
				जाओ rcd_करोne;
			पूर्ण

			अगर (rxDataRingUsed) अणु
				माप_प्रकार sz;

				BUG_ON(rcd->len > rq->data_ring.desc_size);

				ctx->skb = new_skb;
				sz = rcd->rxdIdx * rq->data_ring.desc_size;
				स_नकल(new_skb->data,
				       &rq->data_ring.base[sz], rcd->len);
			पूर्ण अन्यथा अणु
				ctx->skb = rbi->skb;

				new_dma_addr =
					dma_map_single(&adapter->pdev->dev,
						       new_skb->data, rbi->len,
						       PCI_DMA_FROMDEVICE);
				अगर (dma_mapping_error(&adapter->pdev->dev,
						      new_dma_addr)) अणु
					dev_kमुक्त_skb(new_skb);
					/* Skb allocation failed, करो not
					 * hanकरोver this skb to stack. Reuse
					 * it. Drop the existing pkt.
					 */
					rq->stats.rx_buf_alloc_failure++;
					ctx->skb = शून्य;
					rq->stats.drop_total++;
					skip_page_frags = true;
					जाओ rcd_करोne;
				पूर्ण

				dma_unmap_single(&adapter->pdev->dev,
						 rbi->dma_addr,
						 rbi->len,
						 PCI_DMA_FROMDEVICE);

				/* Immediate refill */
				rbi->skb = new_skb;
				rbi->dma_addr = new_dma_addr;
				rxd->addr = cpu_to_le64(rbi->dma_addr);
				rxd->len = rbi->len;
			पूर्ण

#अगर_घोषित VMXNET3_RSS
			अगर (rcd->rssType != VMXNET3_RCD_RSS_TYPE_NONE &&
			    (adapter->netdev->features & NETIF_F_RXHASH))
				skb_set_hash(ctx->skb,
					     le32_to_cpu(rcd->rssHash),
					     PKT_HASH_TYPE_L3);
#पूर्ण_अगर
			skb_put(ctx->skb, rcd->len);

			अगर (VMXNET3_VERSION_GE_2(adapter) &&
			    rcd->type == VMXNET3_CDTYPE_RXCOMP_LRO) अणु
				काष्ठा Vmxnet3_RxCompDescExt *rcdlro;
				rcdlro = (काष्ठा Vmxnet3_RxCompDescExt *)rcd;

				segCnt = rcdlro->segCnt;
				WARN_ON_ONCE(segCnt == 0);
				mss = rcdlro->mss;
				अगर (unlikely(segCnt <= 1))
					segCnt = 0;
			पूर्ण अन्यथा अणु
				segCnt = 0;
			पूर्ण
		पूर्ण अन्यथा अणु
			BUG_ON(ctx->skb == शून्य && !skip_page_frags);

			/* non SOP buffer must be type 1 in most हालs */
			BUG_ON(rbi->buf_type != VMXNET3_RX_BUF_PAGE);
			BUG_ON(rxd->btype != VMXNET3_RXD_BTYPE_BODY);

			/* If an sop buffer was dropped, skip all
			 * following non-sop fragments. They will be reused.
			 */
			अगर (skip_page_frags)
				जाओ rcd_करोne;

			अगर (rcd->len) अणु
				new_page = alloc_page(GFP_ATOMIC);
				/* Replacement page frag could not be allocated.
				 * Reuse this page. Drop the pkt and मुक्त the
				 * skb which contained this page as a frag. Skip
				 * processing all the following non-sop frags.
				 */
				अगर (unlikely(!new_page)) अणु
					rq->stats.rx_buf_alloc_failure++;
					dev_kमुक्त_skb(ctx->skb);
					ctx->skb = शून्य;
					skip_page_frags = true;
					जाओ rcd_करोne;
				पूर्ण
				new_dma_addr = dma_map_page(&adapter->pdev->dev,
							    new_page,
							    0, PAGE_SIZE,
							    PCI_DMA_FROMDEVICE);
				अगर (dma_mapping_error(&adapter->pdev->dev,
						      new_dma_addr)) अणु
					put_page(new_page);
					rq->stats.rx_buf_alloc_failure++;
					dev_kमुक्त_skb(ctx->skb);
					ctx->skb = शून्य;
					skip_page_frags = true;
					जाओ rcd_करोne;
				पूर्ण

				dma_unmap_page(&adapter->pdev->dev,
					       rbi->dma_addr, rbi->len,
					       PCI_DMA_FROMDEVICE);

				vmxnet3_append_frag(ctx->skb, rcd, rbi);

				/* Immediate refill */
				rbi->page = new_page;
				rbi->dma_addr = new_dma_addr;
				rxd->addr = cpu_to_le64(rbi->dma_addr);
				rxd->len = rbi->len;
			पूर्ण
		पूर्ण


		skb = ctx->skb;
		अगर (rcd->eop) अणु
			u32 mtu = adapter->netdev->mtu;
			skb->len += skb->data_len;

			vmxnet3_rx_csum(adapter, skb,
					(जोड़ Vmxnet3_GenericDesc *)rcd);
			skb->protocol = eth_type_trans(skb, adapter->netdev);
			अगर (!rcd->tcp ||
			    !(adapter->netdev->features & NETIF_F_LRO))
				जाओ not_lro;

			अगर (segCnt != 0 && mss != 0) अणु
				skb_shinfo(skb)->gso_type = rcd->v4 ?
					SKB_GSO_TCPV4 : SKB_GSO_TCPV6;
				skb_shinfo(skb)->gso_size = mss;
				skb_shinfo(skb)->gso_segs = segCnt;
			पूर्ण अन्यथा अगर (segCnt != 0 || skb->len > mtu) अणु
				u32 hlen;

				hlen = vmxnet3_get_hdr_len(adapter, skb,
					(जोड़ Vmxnet3_GenericDesc *)rcd);
				अगर (hlen == 0)
					जाओ not_lro;

				skb_shinfo(skb)->gso_type =
					rcd->v4 ? SKB_GSO_TCPV4 : SKB_GSO_TCPV6;
				अगर (segCnt != 0) अणु
					skb_shinfo(skb)->gso_segs = segCnt;
					skb_shinfo(skb)->gso_size =
						DIV_ROUND_UP(skb->len -
							hlen, segCnt);
				पूर्ण अन्यथा अणु
					skb_shinfo(skb)->gso_size = mtu - hlen;
				पूर्ण
			पूर्ण
not_lro:
			अगर (unlikely(rcd->ts))
				__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), rcd->tci);

			अगर (adapter->netdev->features & NETIF_F_LRO)
				netअगर_receive_skb(skb);
			अन्यथा
				napi_gro_receive(&rq->napi, skb);

			ctx->skb = शून्य;
			num_pkts++;
		पूर्ण

rcd_करोne:
		/* device may have skipped some rx descs */
		ring->next2comp = idx;
		num_to_alloc = vmxnet3_cmd_ring_desc_avail(ring);
		ring = rq->rx_ring + ring_idx;

		/* Ensure that the ग_लिखोs to rxd->gen bits will be observed
		 * after all other ग_लिखोs to rxd objects.
		 */
		dma_wmb();

		जबतक (num_to_alloc) अणु
			vmxnet3_getRxDesc(rxd, &ring->base[ring->next2fill].rxd,
					  &rxCmdDesc);
			BUG_ON(!rxd->addr);

			/* Recv desc is पढ़ोy to be used by the device */
			rxd->gen = ring->gen;
			vmxnet3_cmd_ring_adv_next2fill(ring);
			num_to_alloc--;
		पूर्ण

		/* अगर needed, update the रेजिस्टर */
		अगर (unlikely(rq->shared->updateRxProd)) अणु
			VMXNET3_WRITE_BAR0_REG(adapter,
					       rxprod_reg[ring_idx] + rq->qid * 8,
					       ring->next2fill);
		पूर्ण

		vmxnet3_comp_ring_adv_next2proc(&rq->comp_ring);
		vmxnet3_getRxComp(rcd,
				  &rq->comp_ring.base[rq->comp_ring.next2proc].rcd, &rxComp);
	पूर्ण

	वापस num_pkts;
पूर्ण


अटल व्योम
vmxnet3_rq_cleanup(काष्ठा vmxnet3_rx_queue *rq,
		   काष्ठा vmxnet3_adapter *adapter)
अणु
	u32 i, ring_idx;
	काष्ठा Vmxnet3_RxDesc *rxd;

	क्रम (ring_idx = 0; ring_idx < 2; ring_idx++) अणु
		क्रम (i = 0; i < rq->rx_ring[ring_idx].size; i++) अणु
#अगर_घोषित __BIG_ENDIAN_BITFIELD
			काष्ठा Vmxnet3_RxDesc rxDesc;
#पूर्ण_अगर
			vmxnet3_getRxDesc(rxd,
				&rq->rx_ring[ring_idx].base[i].rxd, &rxDesc);

			अगर (rxd->btype == VMXNET3_RXD_BTYPE_HEAD &&
					rq->buf_info[ring_idx][i].skb) अणु
				dma_unmap_single(&adapter->pdev->dev, rxd->addr,
						 rxd->len, PCI_DMA_FROMDEVICE);
				dev_kमुक्त_skb(rq->buf_info[ring_idx][i].skb);
				rq->buf_info[ring_idx][i].skb = शून्य;
			पूर्ण अन्यथा अगर (rxd->btype == VMXNET3_RXD_BTYPE_BODY &&
					rq->buf_info[ring_idx][i].page) अणु
				dma_unmap_page(&adapter->pdev->dev, rxd->addr,
					       rxd->len, PCI_DMA_FROMDEVICE);
				put_page(rq->buf_info[ring_idx][i].page);
				rq->buf_info[ring_idx][i].page = शून्य;
			पूर्ण
		पूर्ण

		rq->rx_ring[ring_idx].gen = VMXNET3_INIT_GEN;
		rq->rx_ring[ring_idx].next2fill =
					rq->rx_ring[ring_idx].next2comp = 0;
	पूर्ण

	rq->comp_ring.gen = VMXNET3_INIT_GEN;
	rq->comp_ring.next2proc = 0;
पूर्ण


अटल व्योम
vmxnet3_rq_cleanup_all(काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		vmxnet3_rq_cleanup(&adapter->rx_queue[i], adapter);
पूर्ण


अटल व्योम vmxnet3_rq_destroy(काष्ठा vmxnet3_rx_queue *rq,
			       काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i;
	पूर्णांक j;

	/* all rx buffers must have alपढ़ोy been मुक्तd */
	क्रम (i = 0; i < 2; i++) अणु
		अगर (rq->buf_info[i]) अणु
			क्रम (j = 0; j < rq->rx_ring[i].size; j++)
				BUG_ON(rq->buf_info[i][j].page != शून्य);
		पूर्ण
	पूर्ण


	क्रम (i = 0; i < 2; i++) अणु
		अगर (rq->rx_ring[i].base) अणु
			dma_मुक्त_coherent(&adapter->pdev->dev,
					  rq->rx_ring[i].size
					  * माप(काष्ठा Vmxnet3_RxDesc),
					  rq->rx_ring[i].base,
					  rq->rx_ring[i].basePA);
			rq->rx_ring[i].base = शून्य;
		पूर्ण
	पूर्ण

	अगर (rq->data_ring.base) अणु
		dma_मुक्त_coherent(&adapter->pdev->dev,
				  rq->rx_ring[0].size * rq->data_ring.desc_size,
				  rq->data_ring.base, rq->data_ring.basePA);
		rq->data_ring.base = शून्य;
	पूर्ण

	अगर (rq->comp_ring.base) अणु
		dma_मुक्त_coherent(&adapter->pdev->dev, rq->comp_ring.size
				  * माप(काष्ठा Vmxnet3_RxCompDesc),
				  rq->comp_ring.base, rq->comp_ring.basePA);
		rq->comp_ring.base = शून्य;
	पूर्ण

	kमुक्त(rq->buf_info[0]);
	rq->buf_info[0] = शून्य;
	rq->buf_info[1] = शून्य;
पूर्ण

अटल व्योम
vmxnet3_rq_destroy_all_rxdataring(काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा vmxnet3_rx_queue *rq = &adapter->rx_queue[i];

		अगर (rq->data_ring.base) अणु
			dma_मुक्त_coherent(&adapter->pdev->dev,
					  (rq->rx_ring[0].size *
					  rq->data_ring.desc_size),
					  rq->data_ring.base,
					  rq->data_ring.basePA);
			rq->data_ring.base = शून्य;
			rq->data_ring.desc_size = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक
vmxnet3_rq_init(काष्ठा vmxnet3_rx_queue *rq,
		काष्ठा vmxnet3_adapter  *adapter)
अणु
	पूर्णांक i;

	/* initialize buf_info */
	क्रम (i = 0; i < rq->rx_ring[0].size; i++) अणु

		/* 1st buf क्रम a pkt is skbuff */
		अगर (i % adapter->rx_buf_per_pkt == 0) अणु
			rq->buf_info[0][i].buf_type = VMXNET3_RX_BUF_SKB;
			rq->buf_info[0][i].len = adapter->skb_buf_size;
		पूर्ण अन्यथा अणु /* subsequent bufs क्रम a pkt is frag */
			rq->buf_info[0][i].buf_type = VMXNET3_RX_BUF_PAGE;
			rq->buf_info[0][i].len = PAGE_SIZE;
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < rq->rx_ring[1].size; i++) अणु
		rq->buf_info[1][i].buf_type = VMXNET3_RX_BUF_PAGE;
		rq->buf_info[1][i].len = PAGE_SIZE;
	पूर्ण

	/* reset पूर्णांकernal state and allocate buffers क्रम both rings */
	क्रम (i = 0; i < 2; i++) अणु
		rq->rx_ring[i].next2fill = rq->rx_ring[i].next2comp = 0;

		स_रखो(rq->rx_ring[i].base, 0, rq->rx_ring[i].size *
		       माप(काष्ठा Vmxnet3_RxDesc));
		rq->rx_ring[i].gen = VMXNET3_INIT_GEN;
	पूर्ण
	अगर (vmxnet3_rq_alloc_rx_buf(rq, 0, rq->rx_ring[0].size - 1,
				    adapter) == 0) अणु
		/* at least has 1 rx buffer क्रम the 1st ring */
		वापस -ENOMEM;
	पूर्ण
	vmxnet3_rq_alloc_rx_buf(rq, 1, rq->rx_ring[1].size - 1, adapter);

	/* reset the comp ring */
	rq->comp_ring.next2proc = 0;
	स_रखो(rq->comp_ring.base, 0, rq->comp_ring.size *
	       माप(काष्ठा Vmxnet3_RxCompDesc));
	rq->comp_ring.gen = VMXNET3_INIT_GEN;

	/* reset rxctx */
	rq->rx_ctx.skb = शून्य;

	/* stats are not reset */
	वापस 0;
पूर्ण


अटल पूर्णांक
vmxnet3_rq_init_all(काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		err = vmxnet3_rq_init(&adapter->rx_queue[i], adapter);
		अगर (unlikely(err)) अणु
			dev_err(&adapter->netdev->dev, "%s: failed to "
				"initialize rx queue%i\n",
				adapter->netdev->name, i);
			अवरोध;
		पूर्ण
	पूर्ण
	वापस err;

पूर्ण


अटल पूर्णांक
vmxnet3_rq_create(काष्ठा vmxnet3_rx_queue *rq, काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i;
	माप_प्रकार sz;
	काष्ठा vmxnet3_rx_buf_info *bi;

	क्रम (i = 0; i < 2; i++) अणु

		sz = rq->rx_ring[i].size * माप(काष्ठा Vmxnet3_RxDesc);
		rq->rx_ring[i].base = dma_alloc_coherent(
						&adapter->pdev->dev, sz,
						&rq->rx_ring[i].basePA,
						GFP_KERNEL);
		अगर (!rq->rx_ring[i].base) अणु
			netdev_err(adapter->netdev,
				   "failed to allocate rx ring %d\n", i);
			जाओ err;
		पूर्ण
	पूर्ण

	अगर ((adapter->rxdataring_enabled) && (rq->data_ring.desc_size != 0)) अणु
		sz = rq->rx_ring[0].size * rq->data_ring.desc_size;
		rq->data_ring.base =
			dma_alloc_coherent(&adapter->pdev->dev, sz,
					   &rq->data_ring.basePA,
					   GFP_KERNEL);
		अगर (!rq->data_ring.base) अणु
			netdev_err(adapter->netdev,
				   "rx data ring will be disabled\n");
			adapter->rxdataring_enabled = false;
		पूर्ण
	पूर्ण अन्यथा अणु
		rq->data_ring.base = शून्य;
		rq->data_ring.desc_size = 0;
	पूर्ण

	sz = rq->comp_ring.size * माप(काष्ठा Vmxnet3_RxCompDesc);
	rq->comp_ring.base = dma_alloc_coherent(&adapter->pdev->dev, sz,
						&rq->comp_ring.basePA,
						GFP_KERNEL);
	अगर (!rq->comp_ring.base) अणु
		netdev_err(adapter->netdev, "failed to allocate rx comp ring\n");
		जाओ err;
	पूर्ण

	bi = kसुस्मृति_node(rq->rx_ring[0].size + rq->rx_ring[1].size,
			  माप(rq->buf_info[0][0]), GFP_KERNEL,
			  dev_to_node(&adapter->pdev->dev));
	अगर (!bi)
		जाओ err;

	rq->buf_info[0] = bi;
	rq->buf_info[1] = bi + rq->rx_ring[0].size;

	वापस 0;

err:
	vmxnet3_rq_destroy(rq, adapter);
	वापस -ENOMEM;
पूर्ण


अटल पूर्णांक
vmxnet3_rq_create_all(काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i, err = 0;

	adapter->rxdataring_enabled = VMXNET3_VERSION_GE_3(adapter);

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		err = vmxnet3_rq_create(&adapter->rx_queue[i], adapter);
		अगर (unlikely(err)) अणु
			dev_err(&adapter->netdev->dev,
				"%s: failed to create rx queue%i\n",
				adapter->netdev->name, i);
			जाओ err_out;
		पूर्ण
	पूर्ण

	अगर (!adapter->rxdataring_enabled)
		vmxnet3_rq_destroy_all_rxdataring(adapter);

	वापस err;
err_out:
	vmxnet3_rq_destroy_all(adapter);
	वापस err;

पूर्ण

/* Multiple queue aware polling function क्रम tx and rx */

अटल पूर्णांक
vmxnet3_करो_poll(काष्ठा vmxnet3_adapter *adapter, पूर्णांक budget)
अणु
	पूर्णांक rcd_करोne = 0, i;
	अगर (unlikely(adapter->shared->ecr))
		vmxnet3_process_events(adapter);
	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		vmxnet3_tq_tx_complete(&adapter->tx_queue[i], adapter);

	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		rcd_करोne += vmxnet3_rq_rx_complete(&adapter->rx_queue[i],
						   adapter, budget);
	वापस rcd_करोne;
पूर्ण


अटल पूर्णांक
vmxnet3_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा vmxnet3_rx_queue *rx_queue = container_of(napi,
					  काष्ठा vmxnet3_rx_queue, napi);
	पूर्णांक rxd_करोne;

	rxd_करोne = vmxnet3_करो_poll(rx_queue->adapter, budget);

	अगर (rxd_करोne < budget) अणु
		napi_complete_करोne(napi, rxd_करोne);
		vmxnet3_enable_all_पूर्णांकrs(rx_queue->adapter);
	पूर्ण
	वापस rxd_करोne;
पूर्ण

/*
 * NAPI polling function क्रम MSI-X mode with multiple Rx queues
 * Returns the # of the NAPI credit consumed (# of rx descriptors processed)
 */

अटल पूर्णांक
vmxnet3_poll_rx_only(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा vmxnet3_rx_queue *rq = container_of(napi,
						काष्ठा vmxnet3_rx_queue, napi);
	काष्ठा vmxnet3_adapter *adapter = rq->adapter;
	पूर्णांक rxd_करोne;

	/* When sharing पूर्णांकerrupt with corresponding tx queue, process
	 * tx completions in that queue as well
	 */
	अगर (adapter->share_पूर्णांकr == VMXNET3_INTR_BUDDYSHARE) अणु
		काष्ठा vmxnet3_tx_queue *tq =
				&adapter->tx_queue[rq - adapter->rx_queue];
		vmxnet3_tq_tx_complete(tq, adapter);
	पूर्ण

	rxd_करोne = vmxnet3_rq_rx_complete(rq, adapter, budget);

	अगर (rxd_करोne < budget) अणु
		napi_complete_करोne(napi, rxd_करोne);
		vmxnet3_enable_पूर्णांकr(adapter, rq->comp_ring.पूर्णांकr_idx);
	पूर्ण
	वापस rxd_करोne;
पूर्ण


#अगर_घोषित CONFIG_PCI_MSI

/*
 * Handle completion पूर्णांकerrupts on tx queues
 * Returns whether or not the पूर्णांकr is handled
 */

अटल irqवापस_t
vmxnet3_msix_tx(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा vmxnet3_tx_queue *tq = data;
	काष्ठा vmxnet3_adapter *adapter = tq->adapter;

	अगर (adapter->पूर्णांकr.mask_mode == VMXNET3_IMM_ACTIVE)
		vmxnet3_disable_पूर्णांकr(adapter, tq->comp_ring.पूर्णांकr_idx);

	/* Handle the हाल where only one irq is allocate क्रम all tx queues */
	अगर (adapter->share_पूर्णांकr == VMXNET3_INTR_TXSHARE) अणु
		पूर्णांक i;
		क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
			काष्ठा vmxnet3_tx_queue *txq = &adapter->tx_queue[i];
			vmxnet3_tq_tx_complete(txq, adapter);
		पूर्ण
	पूर्ण अन्यथा अणु
		vmxnet3_tq_tx_complete(tq, adapter);
	पूर्ण
	vmxnet3_enable_पूर्णांकr(adapter, tq->comp_ring.पूर्णांकr_idx);

	वापस IRQ_HANDLED;
पूर्ण


/*
 * Handle completion पूर्णांकerrupts on rx queues. Returns whether or not the
 * पूर्णांकr is handled
 */

अटल irqवापस_t
vmxnet3_msix_rx(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा vmxnet3_rx_queue *rq = data;
	काष्ठा vmxnet3_adapter *adapter = rq->adapter;

	/* disable पूर्णांकr अगर needed */
	अगर (adapter->पूर्णांकr.mask_mode == VMXNET3_IMM_ACTIVE)
		vmxnet3_disable_पूर्णांकr(adapter, rq->comp_ring.पूर्णांकr_idx);
	napi_schedule(&rq->napi);

	वापस IRQ_HANDLED;
पूर्ण

/*
 *----------------------------------------------------------------------------
 *
 * vmxnet3_msix_event --
 *
 *    vmxnet3 msix event पूर्णांकr handler
 *
 * Result:
 *    whether or not the पूर्णांकr is handled
 *
 *----------------------------------------------------------------------------
 */

अटल irqवापस_t
vmxnet3_msix_event(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा net_device *dev = data;
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(dev);

	/* disable पूर्णांकr अगर needed */
	अगर (adapter->पूर्णांकr.mask_mode == VMXNET3_IMM_ACTIVE)
		vmxnet3_disable_पूर्णांकr(adapter, adapter->पूर्णांकr.event_पूर्णांकr_idx);

	अगर (adapter->shared->ecr)
		vmxnet3_process_events(adapter);

	vmxnet3_enable_पूर्णांकr(adapter, adapter->पूर्णांकr.event_पूर्णांकr_idx);

	वापस IRQ_HANDLED;
पूर्ण

#पूर्ण_अगर /* CONFIG_PCI_MSI  */


/* Interrupt handler क्रम vmxnet3  */
अटल irqवापस_t
vmxnet3_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा net_device *dev = dev_id;
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(dev);

	अगर (adapter->पूर्णांकr.type == VMXNET3_IT_INTX) अणु
		u32 icr = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_ICR);
		अगर (unlikely(icr == 0))
			/* not ours */
			वापस IRQ_NONE;
	पूर्ण


	/* disable पूर्णांकr अगर needed */
	अगर (adapter->पूर्णांकr.mask_mode == VMXNET3_IMM_ACTIVE)
		vmxnet3_disable_all_पूर्णांकrs(adapter);

	napi_schedule(&adapter->rx_queue[0].napi);

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER

/* netpoll callback. */
अटल व्योम
vmxnet3_netpoll(काष्ठा net_device *netdev)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	चयन (adapter->पूर्णांकr.type) अणु
#अगर_घोषित CONFIG_PCI_MSI
	हाल VMXNET3_IT_MSIX: अणु
		पूर्णांक i;
		क्रम (i = 0; i < adapter->num_rx_queues; i++)
			vmxnet3_msix_rx(0, &adapter->rx_queue[i]);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	हाल VMXNET3_IT_MSI:
	शेष:
		vmxnet3_पूर्णांकr(0, adapter->netdev);
		अवरोध;
	पूर्ण

पूर्ण
#पूर्ण_अगर	/* CONFIG_NET_POLL_CONTROLLER */

अटल पूर्णांक
vmxnet3_request_irqs(काष्ठा vmxnet3_adapter *adapter)
अणु
	काष्ठा vmxnet3_पूर्णांकr *पूर्णांकr = &adapter->पूर्णांकr;
	पूर्णांक err = 0, i;
	पूर्णांक vector = 0;

#अगर_घोषित CONFIG_PCI_MSI
	अगर (adapter->पूर्णांकr.type == VMXNET3_IT_MSIX) अणु
		क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
			अगर (adapter->share_पूर्णांकr != VMXNET3_INTR_BUDDYSHARE) अणु
				प्र_लिखो(adapter->tx_queue[i].name, "%s-tx-%d",
					adapter->netdev->name, vector);
				err = request_irq(
					      पूर्णांकr->msix_entries[vector].vector,
					      vmxnet3_msix_tx, 0,
					      adapter->tx_queue[i].name,
					      &adapter->tx_queue[i]);
			पूर्ण अन्यथा अणु
				प्र_लिखो(adapter->tx_queue[i].name, "%s-rxtx-%d",
					adapter->netdev->name, vector);
			पूर्ण
			अगर (err) अणु
				dev_err(&adapter->netdev->dev,
					"Failed to request irq for MSIX, %s, "
					"error %d\n",
					adapter->tx_queue[i].name, err);
				वापस err;
			पूर्ण

			/* Handle the हाल where only 1 MSIx was allocated क्रम
			 * all tx queues */
			अगर (adapter->share_पूर्णांकr == VMXNET3_INTR_TXSHARE) अणु
				क्रम (; i < adapter->num_tx_queues; i++)
					adapter->tx_queue[i].comp_ring.पूर्णांकr_idx
								= vector;
				vector++;
				अवरोध;
			पूर्ण अन्यथा अणु
				adapter->tx_queue[i].comp_ring.पूर्णांकr_idx
								= vector++;
			पूर्ण
		पूर्ण
		अगर (adapter->share_पूर्णांकr == VMXNET3_INTR_BUDDYSHARE)
			vector = 0;

		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			अगर (adapter->share_पूर्णांकr != VMXNET3_INTR_BUDDYSHARE)
				प्र_लिखो(adapter->rx_queue[i].name, "%s-rx-%d",
					adapter->netdev->name, vector);
			अन्यथा
				प्र_लिखो(adapter->rx_queue[i].name, "%s-rxtx-%d",
					adapter->netdev->name, vector);
			err = request_irq(पूर्णांकr->msix_entries[vector].vector,
					  vmxnet3_msix_rx, 0,
					  adapter->rx_queue[i].name,
					  &(adapter->rx_queue[i]));
			अगर (err) अणु
				netdev_err(adapter->netdev,
					   "Failed to request irq for MSIX, "
					   "%s, error %d\n",
					   adapter->rx_queue[i].name, err);
				वापस err;
			पूर्ण

			adapter->rx_queue[i].comp_ring.पूर्णांकr_idx = vector++;
		पूर्ण

		प्र_लिखो(पूर्णांकr->event_msi_vector_name, "%s-event-%d",
			adapter->netdev->name, vector);
		err = request_irq(पूर्णांकr->msix_entries[vector].vector,
				  vmxnet3_msix_event, 0,
				  पूर्णांकr->event_msi_vector_name, adapter->netdev);
		पूर्णांकr->event_पूर्णांकr_idx = vector;

	पूर्ण अन्यथा अगर (पूर्णांकr->type == VMXNET3_IT_MSI) अणु
		adapter->num_rx_queues = 1;
		err = request_irq(adapter->pdev->irq, vmxnet3_पूर्णांकr, 0,
				  adapter->netdev->name, adapter->netdev);
	पूर्ण अन्यथा अणु
#पूर्ण_अगर
		adapter->num_rx_queues = 1;
		err = request_irq(adapter->pdev->irq, vmxnet3_पूर्णांकr,
				  IRQF_SHARED, adapter->netdev->name,
				  adapter->netdev);
#अगर_घोषित CONFIG_PCI_MSI
	पूर्ण
#पूर्ण_अगर
	पूर्णांकr->num_पूर्णांकrs = vector + 1;
	अगर (err) अणु
		netdev_err(adapter->netdev,
			   "Failed to request irq (intr type:%d), error %d\n",
			   पूर्णांकr->type, err);
	पूर्ण अन्यथा अणु
		/* Number of rx queues will not change after this */
		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			काष्ठा vmxnet3_rx_queue *rq = &adapter->rx_queue[i];
			rq->qid = i;
			rq->qid2 = i + adapter->num_rx_queues;
			rq->dataRingQid = i + 2 * adapter->num_rx_queues;
		पूर्ण

		/* init our पूर्णांकr settings */
		क्रम (i = 0; i < पूर्णांकr->num_पूर्णांकrs; i++)
			पूर्णांकr->mod_levels[i] = UPT1_IML_ADAPTIVE;
		अगर (adapter->पूर्णांकr.type != VMXNET3_IT_MSIX) अणु
			adapter->पूर्णांकr.event_पूर्णांकr_idx = 0;
			क्रम (i = 0; i < adapter->num_tx_queues; i++)
				adapter->tx_queue[i].comp_ring.पूर्णांकr_idx = 0;
			adapter->rx_queue[0].comp_ring.पूर्णांकr_idx = 0;
		पूर्ण

		netdev_info(adapter->netdev,
			    "intr type %u, mode %u, %u vectors allocated\n",
			    पूर्णांकr->type, पूर्णांकr->mask_mode, पूर्णांकr->num_पूर्णांकrs);
	पूर्ण

	वापस err;
पूर्ण


अटल व्योम
vmxnet3_मुक्त_irqs(काष्ठा vmxnet3_adapter *adapter)
अणु
	काष्ठा vmxnet3_पूर्णांकr *पूर्णांकr = &adapter->पूर्णांकr;
	BUG_ON(पूर्णांकr->type == VMXNET3_IT_AUTO || पूर्णांकr->num_पूर्णांकrs <= 0);

	चयन (पूर्णांकr->type) अणु
#अगर_घोषित CONFIG_PCI_MSI
	हाल VMXNET3_IT_MSIX:
	अणु
		पूर्णांक i, vector = 0;

		अगर (adapter->share_पूर्णांकr != VMXNET3_INTR_BUDDYSHARE) अणु
			क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
				मुक्त_irq(पूर्णांकr->msix_entries[vector++].vector,
					 &(adapter->tx_queue[i]));
				अगर (adapter->share_पूर्णांकr == VMXNET3_INTR_TXSHARE)
					अवरोध;
			पूर्ण
		पूर्ण

		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			मुक्त_irq(पूर्णांकr->msix_entries[vector++].vector,
				 &(adapter->rx_queue[i]));
		पूर्ण

		मुक्त_irq(पूर्णांकr->msix_entries[vector].vector,
			 adapter->netdev);
		BUG_ON(vector >= पूर्णांकr->num_पूर्णांकrs);
		अवरोध;
	पूर्ण
#पूर्ण_अगर
	हाल VMXNET3_IT_MSI:
		मुक्त_irq(adapter->pdev->irq, adapter->netdev);
		अवरोध;
	हाल VMXNET3_IT_INTX:
		मुक्त_irq(adapter->pdev->irq, adapter->netdev);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
पूर्ण


अटल व्योम
vmxnet3_restore_vlan(काष्ठा vmxnet3_adapter *adapter)
अणु
	u32 *vfTable = adapter->shared->devRead.rxFilterConf.vfTable;
	u16 vid;

	/* allow untagged pkts */
	VMXNET3_SET_VFTABLE_ENTRY(vfTable, 0);

	क्रम_each_set_bit(vid, adapter->active_vlans, VLAN_N_VID)
		VMXNET3_SET_VFTABLE_ENTRY(vfTable, vid);
पूर्ण


अटल पूर्णांक
vmxnet3_vlan_rx_add_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	अगर (!(netdev->flags & IFF_PROMISC)) अणु
		u32 *vfTable = adapter->shared->devRead.rxFilterConf.vfTable;
		अचिन्हित दीर्घ flags;

		VMXNET3_SET_VFTABLE_ENTRY(vfTable, vid);
		spin_lock_irqsave(&adapter->cmd_lock, flags);
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_UPDATE_VLAN_FILTERS);
		spin_unlock_irqrestore(&adapter->cmd_lock, flags);
	पूर्ण

	set_bit(vid, adapter->active_vlans);

	वापस 0;
पूर्ण


अटल पूर्णांक
vmxnet3_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	अगर (!(netdev->flags & IFF_PROMISC)) अणु
		u32 *vfTable = adapter->shared->devRead.rxFilterConf.vfTable;
		अचिन्हित दीर्घ flags;

		VMXNET3_CLEAR_VFTABLE_ENTRY(vfTable, vid);
		spin_lock_irqsave(&adapter->cmd_lock, flags);
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_UPDATE_VLAN_FILTERS);
		spin_unlock_irqrestore(&adapter->cmd_lock, flags);
	पूर्ण

	clear_bit(vid, adapter->active_vlans);

	वापस 0;
पूर्ण


अटल u8 *
vmxnet3_copy_mc(काष्ठा net_device *netdev)
अणु
	u8 *buf = शून्य;
	u32 sz = netdev_mc_count(netdev) * ETH_ALEN;

	/* काष्ठा Vmxnet3_RxFilterConf.mfTableLen is u16. */
	अगर (sz <= 0xffff) अणु
		/* We may be called with BH disabled */
		buf = kदो_स्मृति(sz, GFP_ATOMIC);
		अगर (buf) अणु
			काष्ठा netdev_hw_addr *ha;
			पूर्णांक i = 0;

			netdev_क्रम_each_mc_addr(ha, netdev)
				स_नकल(buf + i++ * ETH_ALEN, ha->addr,
				       ETH_ALEN);
		पूर्ण
	पूर्ण
	वापस buf;
पूर्ण


अटल व्योम
vmxnet3_set_mc(काष्ठा net_device *netdev)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;
	काष्ठा Vmxnet3_RxFilterConf *rxConf =
					&adapter->shared->devRead.rxFilterConf;
	u8 *new_table = शून्य;
	dma_addr_t new_table_pa = 0;
	bool new_table_pa_valid = false;
	u32 new_mode = VMXNET3_RXM_UCAST;

	अगर (netdev->flags & IFF_PROMISC) अणु
		u32 *vfTable = adapter->shared->devRead.rxFilterConf.vfTable;
		स_रखो(vfTable, 0, VMXNET3_VFT_SIZE * माप(*vfTable));

		new_mode |= VMXNET3_RXM_PROMISC;
	पूर्ण अन्यथा अणु
		vmxnet3_restore_vlan(adapter);
	पूर्ण

	अगर (netdev->flags & IFF_BROADCAST)
		new_mode |= VMXNET3_RXM_BCAST;

	अगर (netdev->flags & IFF_ALLMULTI)
		new_mode |= VMXNET3_RXM_ALL_MULTI;
	अन्यथा
		अगर (!netdev_mc_empty(netdev)) अणु
			new_table = vmxnet3_copy_mc(netdev);
			अगर (new_table) अणु
				माप_प्रकार sz = netdev_mc_count(netdev) * ETH_ALEN;

				rxConf->mfTableLen = cpu_to_le16(sz);
				new_table_pa = dma_map_single(
							&adapter->pdev->dev,
							new_table,
							sz,
							PCI_DMA_TODEVICE);
				अगर (!dma_mapping_error(&adapter->pdev->dev,
						       new_table_pa)) अणु
					new_mode |= VMXNET3_RXM_MCAST;
					new_table_pa_valid = true;
					rxConf->mfTablePA = cpu_to_le64(
								new_table_pa);
				पूर्ण
			पूर्ण
			अगर (!new_table_pa_valid) अणु
				netdev_info(netdev,
					    "failed to copy mcast list, setting ALL_MULTI\n");
				new_mode |= VMXNET3_RXM_ALL_MULTI;
			पूर्ण
		पूर्ण

	अगर (!(new_mode & VMXNET3_RXM_MCAST)) अणु
		rxConf->mfTableLen = 0;
		rxConf->mfTablePA = 0;
	पूर्ण

	spin_lock_irqsave(&adapter->cmd_lock, flags);
	अगर (new_mode != rxConf->rxMode) अणु
		rxConf->rxMode = cpu_to_le32(new_mode);
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_UPDATE_RX_MODE);
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_UPDATE_VLAN_FILTERS);
	पूर्ण

	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
			       VMXNET3_CMD_UPDATE_MAC_FILTERS);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);

	अगर (new_table_pa_valid)
		dma_unmap_single(&adapter->pdev->dev, new_table_pa,
				 rxConf->mfTableLen, PCI_DMA_TODEVICE);
	kमुक्त(new_table);
पूर्ण

व्योम
vmxnet3_rq_destroy_all(काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		vmxnet3_rq_destroy(&adapter->rx_queue[i], adapter);
पूर्ण


/*
 *   Set up driver_shared based on settings in adapter.
 */

अटल व्योम
vmxnet3_setup_driver_shared(काष्ठा vmxnet3_adapter *adapter)
अणु
	काष्ठा Vmxnet3_DriverShared *shared = adapter->shared;
	काष्ठा Vmxnet3_DSDevRead *devRead = &shared->devRead;
	काष्ठा Vmxnet3_TxQueueConf *tqc;
	काष्ठा Vmxnet3_RxQueueConf *rqc;
	पूर्णांक i;

	स_रखो(shared, 0, माप(*shared));

	/* driver settings */
	shared->magic = cpu_to_le32(VMXNET3_REV1_MAGIC);
	devRead->misc.driverInfo.version = cpu_to_le32(
						VMXNET3_DRIVER_VERSION_NUM);
	devRead->misc.driverInfo.gos.gosBits = (माप(व्योम *) == 4 ?
				VMXNET3_GOS_BITS_32 : VMXNET3_GOS_BITS_64);
	devRead->misc.driverInfo.gos.gosType = VMXNET3_GOS_TYPE_LINUX;
	*((u32 *)&devRead->misc.driverInfo.gos) = cpu_to_le32(
				*((u32 *)&devRead->misc.driverInfo.gos));
	devRead->misc.driverInfo.vmxnet3RevSpt = cpu_to_le32(1);
	devRead->misc.driverInfo.uptVerSpt = cpu_to_le32(1);

	devRead->misc.ddPA = cpu_to_le64(adapter->adapter_pa);
	devRead->misc.ddLen = cpu_to_le32(माप(काष्ठा vmxnet3_adapter));

	/* set up feature flags */
	अगर (adapter->netdev->features & NETIF_F_RXCSUM)
		devRead->misc.uptFeatures |= UPT1_F_RXCSUM;

	अगर (adapter->netdev->features & NETIF_F_LRO) अणु
		devRead->misc.uptFeatures |= UPT1_F_LRO;
		devRead->misc.maxNumRxSG = cpu_to_le16(1 + MAX_SKB_FRAGS);
	पूर्ण
	अगर (adapter->netdev->features & NETIF_F_HW_VLAN_CTAG_RX)
		devRead->misc.uptFeatures |= UPT1_F_RXVLAN;

	अगर (adapter->netdev->features & (NETIF_F_GSO_UDP_TUNNEL |
					 NETIF_F_GSO_UDP_TUNNEL_CSUM))
		devRead->misc.uptFeatures |= UPT1_F_RXINNEROFLD;

	devRead->misc.mtu = cpu_to_le32(adapter->netdev->mtu);
	devRead->misc.queueDescPA = cpu_to_le64(adapter->queue_desc_pa);
	devRead->misc.queueDescLen = cpu_to_le32(
		adapter->num_tx_queues * माप(काष्ठा Vmxnet3_TxQueueDesc) +
		adapter->num_rx_queues * माप(काष्ठा Vmxnet3_RxQueueDesc));

	/* tx queue settings */
	devRead->misc.numTxQueues =  adapter->num_tx_queues;
	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		काष्ठा vmxnet3_tx_queue	*tq = &adapter->tx_queue[i];
		BUG_ON(adapter->tx_queue[i].tx_ring.base == शून्य);
		tqc = &adapter->tqd_start[i].conf;
		tqc->txRingBasePA   = cpu_to_le64(tq->tx_ring.basePA);
		tqc->dataRingBasePA = cpu_to_le64(tq->data_ring.basePA);
		tqc->compRingBasePA = cpu_to_le64(tq->comp_ring.basePA);
		tqc->ddPA           = cpu_to_le64(~0ULL);
		tqc->txRingSize     = cpu_to_le32(tq->tx_ring.size);
		tqc->dataRingSize   = cpu_to_le32(tq->data_ring.size);
		tqc->txDataRingDescSize = cpu_to_le32(tq->txdata_desc_size);
		tqc->compRingSize   = cpu_to_le32(tq->comp_ring.size);
		tqc->ddLen          = cpu_to_le32(0);
		tqc->पूर्णांकrIdx        = tq->comp_ring.पूर्णांकr_idx;
	पूर्ण

	/* rx queue settings */
	devRead->misc.numRxQueues = adapter->num_rx_queues;
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा vmxnet3_rx_queue	*rq = &adapter->rx_queue[i];
		rqc = &adapter->rqd_start[i].conf;
		rqc->rxRingBasePA[0] = cpu_to_le64(rq->rx_ring[0].basePA);
		rqc->rxRingBasePA[1] = cpu_to_le64(rq->rx_ring[1].basePA);
		rqc->compRingBasePA  = cpu_to_le64(rq->comp_ring.basePA);
		rqc->ddPA            = cpu_to_le64(~0ULL);
		rqc->rxRingSize[0]   = cpu_to_le32(rq->rx_ring[0].size);
		rqc->rxRingSize[1]   = cpu_to_le32(rq->rx_ring[1].size);
		rqc->compRingSize    = cpu_to_le32(rq->comp_ring.size);
		rqc->ddLen           = cpu_to_le32(0);
		rqc->पूर्णांकrIdx         = rq->comp_ring.पूर्णांकr_idx;
		अगर (VMXNET3_VERSION_GE_3(adapter)) अणु
			rqc->rxDataRingBasePA =
				cpu_to_le64(rq->data_ring.basePA);
			rqc->rxDataRingDescSize =
				cpu_to_le16(rq->data_ring.desc_size);
		पूर्ण
	पूर्ण

#अगर_घोषित VMXNET3_RSS
	स_रखो(adapter->rss_conf, 0, माप(*adapter->rss_conf));

	अगर (adapter->rss) अणु
		काष्ठा UPT1_RSSConf *rssConf = adapter->rss_conf;

		devRead->misc.uptFeatures |= UPT1_F_RSS;
		devRead->misc.numRxQueues = adapter->num_rx_queues;
		rssConf->hashType = UPT1_RSS_HASH_TYPE_TCP_IPV4 |
				    UPT1_RSS_HASH_TYPE_IPV4 |
				    UPT1_RSS_HASH_TYPE_TCP_IPV6 |
				    UPT1_RSS_HASH_TYPE_IPV6;
		rssConf->hashFunc = UPT1_RSS_HASH_FUNC_TOEPLITZ;
		rssConf->hashKeySize = UPT1_RSS_MAX_KEY_SIZE;
		rssConf->indTableSize = VMXNET3_RSS_IND_TABLE_SIZE;
		netdev_rss_key_fill(rssConf->hashKey, माप(rssConf->hashKey));

		क्रम (i = 0; i < rssConf->indTableSize; i++)
			rssConf->indTable[i] = ethtool_rxfh_indir_शेष(
				i, adapter->num_rx_queues);

		devRead->rssConfDesc.confVer = 1;
		devRead->rssConfDesc.confLen = cpu_to_le32(माप(*rssConf));
		devRead->rssConfDesc.confPA =
			cpu_to_le64(adapter->rss_conf_pa);
	पूर्ण

#पूर्ण_अगर /* VMXNET3_RSS */

	/* पूर्णांकr settings */
	devRead->पूर्णांकrConf.स्वतःMask = adapter->पूर्णांकr.mask_mode ==
				     VMXNET3_IMM_AUTO;
	devRead->पूर्णांकrConf.numIntrs = adapter->पूर्णांकr.num_पूर्णांकrs;
	क्रम (i = 0; i < adapter->पूर्णांकr.num_पूर्णांकrs; i++)
		devRead->पूर्णांकrConf.modLevels[i] = adapter->पूर्णांकr.mod_levels[i];

	devRead->पूर्णांकrConf.eventIntrIdx = adapter->पूर्णांकr.event_पूर्णांकr_idx;
	devRead->पूर्णांकrConf.पूर्णांकrCtrl |= cpu_to_le32(VMXNET3_IC_DISABLE_ALL);

	/* rx filter settings */
	devRead->rxFilterConf.rxMode = 0;
	vmxnet3_restore_vlan(adapter);
	vmxnet3_ग_लिखो_mac_addr(adapter, adapter->netdev->dev_addr);

	/* the rest are alपढ़ोy zeroed */
पूर्ण

अटल व्योम
vmxnet3_init_coalesce(काष्ठा vmxnet3_adapter *adapter)
अणु
	काष्ठा Vmxnet3_DriverShared *shared = adapter->shared;
	जोड़ Vmxnet3_CmdInfo *cmdInfo = &shared->cu.cmdInfo;
	अचिन्हित दीर्घ flags;

	अगर (!VMXNET3_VERSION_GE_3(adapter))
		वापस;

	spin_lock_irqsave(&adapter->cmd_lock, flags);
	cmdInfo->varConf.confVer = 1;
	cmdInfo->varConf.confLen =
		cpu_to_le32(माप(*adapter->coal_conf));
	cmdInfo->varConf.confPA  = cpu_to_le64(adapter->coal_conf_pa);

	अगर (adapter->शेष_coal_mode) अणु
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_GET_COALESCE);
	पूर्ण अन्यथा अणु
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_SET_COALESCE);
	पूर्ण

	spin_unlock_irqrestore(&adapter->cmd_lock, flags);
पूर्ण

अटल व्योम
vmxnet3_init_rssfields(काष्ठा vmxnet3_adapter *adapter)
अणु
	काष्ठा Vmxnet3_DriverShared *shared = adapter->shared;
	जोड़ Vmxnet3_CmdInfo *cmdInfo = &shared->cu.cmdInfo;
	अचिन्हित दीर्घ flags;

	अगर (!VMXNET3_VERSION_GE_4(adapter))
		वापस;

	spin_lock_irqsave(&adapter->cmd_lock, flags);

	अगर (adapter->शेष_rss_fields) अणु
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_GET_RSS_FIELDS);
		adapter->rss_fields =
			VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_CMD);
	पूर्ण अन्यथा अणु
		cmdInfo->setRssFields = adapter->rss_fields;
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_SET_RSS_FIELDS);
		/* Not all requested RSS may get applied, so get and
		 * cache what was actually applied.
		 */
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_GET_RSS_FIELDS);
		adapter->rss_fields =
			VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_CMD);
	पूर्ण

	spin_unlock_irqrestore(&adapter->cmd_lock, flags);
पूर्ण

पूर्णांक
vmxnet3_activate_dev(काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक err, i;
	u32 ret;
	अचिन्हित दीर्घ flags;

	netdev_dbg(adapter->netdev, "%s: skb_buf_size %d, rx_buf_per_pkt %d,"
		" ring sizes %u %u %u\n", adapter->netdev->name,
		adapter->skb_buf_size, adapter->rx_buf_per_pkt,
		adapter->tx_queue[0].tx_ring.size,
		adapter->rx_queue[0].rx_ring[0].size,
		adapter->rx_queue[0].rx_ring[1].size);

	vmxnet3_tq_init_all(adapter);
	err = vmxnet3_rq_init_all(adapter);
	अगर (err) अणु
		netdev_err(adapter->netdev,
			   "Failed to init rx queue error %d\n", err);
		जाओ rq_err;
	पूर्ण

	err = vmxnet3_request_irqs(adapter);
	अगर (err) अणु
		netdev_err(adapter->netdev,
			   "Failed to setup irq for error %d\n", err);
		जाओ irq_err;
	पूर्ण

	vmxnet3_setup_driver_shared(adapter);

	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_DSAL, VMXNET3_GET_ADDR_LO(
			       adapter->shared_pa));
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_DSAH, VMXNET3_GET_ADDR_HI(
			       adapter->shared_pa));
	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
			       VMXNET3_CMD_ACTIVATE_DEV);
	ret = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_CMD);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);

	अगर (ret != 0) अणु
		netdev_err(adapter->netdev,
			   "Failed to activate dev: error %u\n", ret);
		err = -EINVAL;
		जाओ activate_err;
	पूर्ण

	vmxnet3_init_coalesce(adapter);
	vmxnet3_init_rssfields(adapter);

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		VMXNET3_WRITE_BAR0_REG(adapter,
				VMXNET3_REG_RXPROD + i * VMXNET3_REG_ALIGN,
				adapter->rx_queue[i].rx_ring[0].next2fill);
		VMXNET3_WRITE_BAR0_REG(adapter, (VMXNET3_REG_RXPROD2 +
				(i * VMXNET3_REG_ALIGN)),
				adapter->rx_queue[i].rx_ring[1].next2fill);
	पूर्ण

	/* Apply the rx filter settins last. */
	vmxnet3_set_mc(adapter->netdev);

	/*
	 * Check link state when first activating device. It will start the
	 * tx queue अगर the link is up.
	 */
	vmxnet3_check_link(adapter, true);
	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		napi_enable(&adapter->rx_queue[i].napi);
	vmxnet3_enable_all_पूर्णांकrs(adapter);
	clear_bit(VMXNET3_STATE_BIT_QUIESCED, &adapter->state);
	वापस 0;

activate_err:
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_DSAL, 0);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_DSAH, 0);
	vmxnet3_मुक्त_irqs(adapter);
irq_err:
rq_err:
	/* मुक्त up buffers we allocated */
	vmxnet3_rq_cleanup_all(adapter);
	वापस err;
पूर्ण


व्योम
vmxnet3_reset_dev(काष्ठा vmxnet3_adapter *adapter)
अणु
	अचिन्हित दीर्घ flags;
	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD, VMXNET3_CMD_RESET_DEV);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);
पूर्ण


पूर्णांक
vmxnet3_quiesce_dev(काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ flags;
	अगर (test_and_set_bit(VMXNET3_STATE_BIT_QUIESCED, &adapter->state))
		वापस 0;


	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
			       VMXNET3_CMD_QUIESCE_DEV);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);
	vmxnet3_disable_all_पूर्णांकrs(adapter);

	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		napi_disable(&adapter->rx_queue[i].napi);
	netअगर_tx_disable(adapter->netdev);
	adapter->link_speed = 0;
	netअगर_carrier_off(adapter->netdev);

	vmxnet3_tq_cleanup_all(adapter);
	vmxnet3_rq_cleanup_all(adapter);
	vmxnet3_मुक्त_irqs(adapter);
	वापस 0;
पूर्ण


अटल व्योम
vmxnet3_ग_लिखो_mac_addr(काष्ठा vmxnet3_adapter *adapter, u8 *mac)
अणु
	u32 पंचांगp;

	पंचांगp = *(u32 *)mac;
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_MACL, पंचांगp);

	पंचांगp = (mac[5] << 8) | mac[4];
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_MACH, पंचांगp);
पूर्ण


अटल पूर्णांक
vmxnet3_set_mac_addr(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा sockaddr *addr = p;
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	vmxnet3_ग_लिखो_mac_addr(adapter, addr->sa_data);

	वापस 0;
पूर्ण


/* ==================== initialization and cleanup routines ============ */

अटल पूर्णांक
vmxnet3_alloc_pci_resources(काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ mmio_start, mmio_len;
	काष्ठा pci_dev *pdev = adapter->pdev;

	err = pci_enable_device(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to enable adapter: error %d\n", err);
		वापस err;
	पूर्ण

	err = pci_request_selected_regions(pdev, (1 << 2) - 1,
					   vmxnet3_driver_name);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"Failed to request region for adapter: error %d\n", err);
		जाओ err_enable_device;
	पूर्ण

	pci_set_master(pdev);

	mmio_start = pci_resource_start(pdev, 0);
	mmio_len = pci_resource_len(pdev, 0);
	adapter->hw_addr0 = ioremap(mmio_start, mmio_len);
	अगर (!adapter->hw_addr0) अणु
		dev_err(&pdev->dev, "Failed to map bar0\n");
		err = -EIO;
		जाओ err_ioremap;
	पूर्ण

	mmio_start = pci_resource_start(pdev, 1);
	mmio_len = pci_resource_len(pdev, 1);
	adapter->hw_addr1 = ioremap(mmio_start, mmio_len);
	अगर (!adapter->hw_addr1) अणु
		dev_err(&pdev->dev, "Failed to map bar1\n");
		err = -EIO;
		जाओ err_bar1;
	पूर्ण
	वापस 0;

err_bar1:
	iounmap(adapter->hw_addr0);
err_ioremap:
	pci_release_selected_regions(pdev, (1 << 2) - 1);
err_enable_device:
	pci_disable_device(pdev);
	वापस err;
पूर्ण


अटल व्योम
vmxnet3_मुक्त_pci_resources(काष्ठा vmxnet3_adapter *adapter)
अणु
	BUG_ON(!adapter->pdev);

	iounmap(adapter->hw_addr0);
	iounmap(adapter->hw_addr1);
	pci_release_selected_regions(adapter->pdev, (1 << 2) - 1);
	pci_disable_device(adapter->pdev);
पूर्ण


अटल व्योम
vmxnet3_adjust_rx_ring_size(काष्ठा vmxnet3_adapter *adapter)
अणु
	माप_प्रकार sz, i, ring0_size, ring1_size, comp_size;
	अगर (adapter->netdev->mtu <= VMXNET3_MAX_SKB_BUF_SIZE -
				    VMXNET3_MAX_ETH_HDR_SIZE) अणु
		adapter->skb_buf_size = adapter->netdev->mtu +
					VMXNET3_MAX_ETH_HDR_SIZE;
		अगर (adapter->skb_buf_size < VMXNET3_MIN_T0_BUF_SIZE)
			adapter->skb_buf_size = VMXNET3_MIN_T0_BUF_SIZE;

		adapter->rx_buf_per_pkt = 1;
	पूर्ण अन्यथा अणु
		adapter->skb_buf_size = VMXNET3_MAX_SKB_BUF_SIZE;
		sz = adapter->netdev->mtu - VMXNET3_MAX_SKB_BUF_SIZE +
					    VMXNET3_MAX_ETH_HDR_SIZE;
		adapter->rx_buf_per_pkt = 1 + (sz + PAGE_SIZE - 1) / PAGE_SIZE;
	पूर्ण

	/*
	 * क्रम simplicity, क्रमce the ring0 size to be a multiple of
	 * rx_buf_per_pkt * VMXNET3_RING_SIZE_ALIGN
	 */
	sz = adapter->rx_buf_per_pkt * VMXNET3_RING_SIZE_ALIGN;
	ring0_size = adapter->rx_queue[0].rx_ring[0].size;
	ring0_size = (ring0_size + sz - 1) / sz * sz;
	ring0_size = min_t(u32, ring0_size, VMXNET3_RX_RING_MAX_SIZE /
			   sz * sz);
	ring1_size = adapter->rx_queue[0].rx_ring[1].size;
	ring1_size = (ring1_size + sz - 1) / sz * sz;
	ring1_size = min_t(u32, ring1_size, VMXNET3_RX_RING2_MAX_SIZE /
			   sz * sz);
	comp_size = ring0_size + ring1_size;

	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा vmxnet3_rx_queue	*rq = &adapter->rx_queue[i];

		rq->rx_ring[0].size = ring0_size;
		rq->rx_ring[1].size = ring1_size;
		rq->comp_ring.size = comp_size;
	पूर्ण
पूर्ण


पूर्णांक
vmxnet3_create_queues(काष्ठा vmxnet3_adapter *adapter, u32 tx_ring_size,
		      u32 rx_ring_size, u32 rx_ring2_size,
		      u16 txdata_desc_size, u16 rxdata_desc_size)
अणु
	पूर्णांक err = 0, i;

	क्रम (i = 0; i < adapter->num_tx_queues; i++) अणु
		काष्ठा vmxnet3_tx_queue	*tq = &adapter->tx_queue[i];
		tq->tx_ring.size   = tx_ring_size;
		tq->data_ring.size = tx_ring_size;
		tq->comp_ring.size = tx_ring_size;
		tq->txdata_desc_size = txdata_desc_size;
		tq->shared = &adapter->tqd_start[i].ctrl;
		tq->stopped = true;
		tq->adapter = adapter;
		tq->qid = i;
		err = vmxnet3_tq_create(tq, adapter);
		/*
		 * Too late to change num_tx_queues. We cannot करो away with
		 * lesser number of queues than what we asked क्रम
		 */
		अगर (err)
			जाओ queue_err;
	पूर्ण

	adapter->rx_queue[0].rx_ring[0].size = rx_ring_size;
	adapter->rx_queue[0].rx_ring[1].size = rx_ring2_size;
	vmxnet3_adjust_rx_ring_size(adapter);

	adapter->rxdataring_enabled = VMXNET3_VERSION_GE_3(adapter);
	क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
		काष्ठा vmxnet3_rx_queue *rq = &adapter->rx_queue[i];
		/* qid and qid2 क्रम rx queues will be asचिन्हित later when num
		 * of rx queues is finalized after allocating पूर्णांकrs */
		rq->shared = &adapter->rqd_start[i].ctrl;
		rq->adapter = adapter;
		rq->data_ring.desc_size = rxdata_desc_size;
		err = vmxnet3_rq_create(rq, adapter);
		अगर (err) अणु
			अगर (i == 0) अणु
				netdev_err(adapter->netdev,
					   "Could not allocate any rx queues. "
					   "Aborting.\n");
				जाओ queue_err;
			पूर्ण अन्यथा अणु
				netdev_info(adapter->netdev,
					    "Number of rx queues changed "
					    "to : %d.\n", i);
				adapter->num_rx_queues = i;
				err = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!adapter->rxdataring_enabled)
		vmxnet3_rq_destroy_all_rxdataring(adapter);

	वापस err;
queue_err:
	vmxnet3_tq_destroy_all(adapter);
	वापस err;
पूर्ण

अटल पूर्णांक
vmxnet3_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा vmxnet3_adapter *adapter;
	पूर्णांक err, i;

	adapter = netdev_priv(netdev);

	क्रम (i = 0; i < adapter->num_tx_queues; i++)
		spin_lock_init(&adapter->tx_queue[i].tx_lock);

	अगर (VMXNET3_VERSION_GE_3(adapter)) अणु
		अचिन्हित दीर्घ flags;
		u16 txdata_desc_size;

		spin_lock_irqsave(&adapter->cmd_lock, flags);
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
				       VMXNET3_CMD_GET_TXDATA_DESC_SIZE);
		txdata_desc_size = VMXNET3_READ_BAR1_REG(adapter,
							 VMXNET3_REG_CMD);
		spin_unlock_irqrestore(&adapter->cmd_lock, flags);

		अगर ((txdata_desc_size < VMXNET3_TXDATA_DESC_MIN_SIZE) ||
		    (txdata_desc_size > VMXNET3_TXDATA_DESC_MAX_SIZE) ||
		    (txdata_desc_size & VMXNET3_TXDATA_DESC_SIZE_MASK)) अणु
			adapter->txdata_desc_size =
				माप(काष्ठा Vmxnet3_TxDataDesc);
		पूर्ण अन्यथा अणु
			adapter->txdata_desc_size = txdata_desc_size;
		पूर्ण
	पूर्ण अन्यथा अणु
		adapter->txdata_desc_size = माप(काष्ठा Vmxnet3_TxDataDesc);
	पूर्ण

	err = vmxnet3_create_queues(adapter,
				    adapter->tx_ring_size,
				    adapter->rx_ring_size,
				    adapter->rx_ring2_size,
				    adapter->txdata_desc_size,
				    adapter->rxdata_desc_size);
	अगर (err)
		जाओ queue_err;

	err = vmxnet3_activate_dev(adapter);
	अगर (err)
		जाओ activate_err;

	वापस 0;

activate_err:
	vmxnet3_rq_destroy_all(adapter);
	vmxnet3_tq_destroy_all(adapter);
queue_err:
	वापस err;
पूर्ण


अटल पूर्णांक
vmxnet3_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	/*
	 * Reset_work may be in the middle of resetting the device, रुको क्रम its
	 * completion.
	 */
	जबतक (test_and_set_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	vmxnet3_quiesce_dev(adapter);

	vmxnet3_rq_destroy_all(adapter);
	vmxnet3_tq_destroy_all(adapter);

	clear_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state);


	वापस 0;
पूर्ण


व्योम
vmxnet3_क्रमce_बंद(काष्ठा vmxnet3_adapter *adapter)
अणु
	पूर्णांक i;

	/*
	 * we must clear VMXNET3_STATE_BIT_RESETTING, otherwise
	 * vmxnet3_बंद() will deadlock.
	 */
	BUG_ON(test_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state));

	/* we need to enable NAPI, otherwise dev_बंद will deadlock */
	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		napi_enable(&adapter->rx_queue[i].napi);
	/*
	 * Need to clear the quiesce bit to ensure that vmxnet3_बंद
	 * can quiesce the device properly
	 */
	clear_bit(VMXNET3_STATE_BIT_QUIESCED, &adapter->state);
	dev_बंद(adapter->netdev);
पूर्ण


अटल पूर्णांक
vmxnet3_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	पूर्णांक err = 0;

	netdev->mtu = new_mtu;

	/*
	 * Reset_work may be in the middle of resetting the device, रुको क्रम its
	 * completion.
	 */
	जबतक (test_and_set_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	अगर (netअगर_running(netdev)) अणु
		vmxnet3_quiesce_dev(adapter);
		vmxnet3_reset_dev(adapter);

		/* we need to re-create the rx queue based on the new mtu */
		vmxnet3_rq_destroy_all(adapter);
		vmxnet3_adjust_rx_ring_size(adapter);
		err = vmxnet3_rq_create_all(adapter);
		अगर (err) अणु
			netdev_err(netdev,
				   "failed to re-create rx queues, "
				   " error %d. Closing it.\n", err);
			जाओ out;
		पूर्ण

		err = vmxnet3_activate_dev(adapter);
		अगर (err) अणु
			netdev_err(netdev,
				   "failed to re-activate, error %d. "
				   "Closing it\n", err);
			जाओ out;
		पूर्ण
	पूर्ण

out:
	clear_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state);
	अगर (err)
		vmxnet3_क्रमce_बंद(adapter);

	वापस err;
पूर्ण


अटल व्योम
vmxnet3_declare_features(काष्ठा vmxnet3_adapter *adapter, bool dma64)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	netdev->hw_features = NETIF_F_SG | NETIF_F_RXCSUM |
		NETIF_F_HW_CSUM | NETIF_F_HW_VLAN_CTAG_TX |
		NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_TSO | NETIF_F_TSO6 |
		NETIF_F_LRO;

	अगर (VMXNET3_VERSION_GE_4(adapter)) अणु
		netdev->hw_features |= NETIF_F_GSO_UDP_TUNNEL |
				NETIF_F_GSO_UDP_TUNNEL_CSUM;

		netdev->hw_enc_features = NETIF_F_SG | NETIF_F_RXCSUM |
			NETIF_F_HW_CSUM | NETIF_F_HW_VLAN_CTAG_TX |
			NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_TSO | NETIF_F_TSO6 |
			NETIF_F_LRO | NETIF_F_GSO_UDP_TUNNEL |
			NETIF_F_GSO_UDP_TUNNEL_CSUM;
	पूर्ण

	अगर (dma64)
		netdev->hw_features |= NETIF_F_HIGHDMA;
	netdev->vlan_features = netdev->hw_features &
				~(NETIF_F_HW_VLAN_CTAG_TX |
				  NETIF_F_HW_VLAN_CTAG_RX);
	netdev->features = netdev->hw_features | NETIF_F_HW_VLAN_CTAG_FILTER;
पूर्ण


अटल व्योम
vmxnet3_पढ़ो_mac_addr(काष्ठा vmxnet3_adapter *adapter, u8 *mac)
अणु
	u32 पंचांगp;

	पंचांगp = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_MACL);
	*(u32 *)mac = पंचांगp;

	पंचांगp = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_MACH);
	mac[4] = पंचांगp & 0xff;
	mac[5] = (पंचांगp >> 8) & 0xff;
पूर्ण

#अगर_घोषित CONFIG_PCI_MSI

/*
 * Enable MSIx vectors.
 * Returns :
 *	VMXNET3_LINUX_MIN_MSIX_VECT when only minimum number of vectors required
 *	 were enabled.
 *	number of vectors which were enabled otherwise (this number is greater
 *	 than VMXNET3_LINUX_MIN_MSIX_VECT)
 */

अटल पूर्णांक
vmxnet3_acquire_msix_vectors(काष्ठा vmxnet3_adapter *adapter, पूर्णांक nvec)
अणु
	पूर्णांक ret = pci_enable_msix_range(adapter->pdev,
					adapter->पूर्णांकr.msix_entries, nvec, nvec);

	अगर (ret == -ENOSPC && nvec > VMXNET3_LINUX_MIN_MSIX_VECT) अणु
		dev_err(&adapter->netdev->dev,
			"Failed to enable %d MSI-X, trying %d\n",
			nvec, VMXNET3_LINUX_MIN_MSIX_VECT);

		ret = pci_enable_msix_range(adapter->pdev,
					    adapter->पूर्णांकr.msix_entries,
					    VMXNET3_LINUX_MIN_MSIX_VECT,
					    VMXNET3_LINUX_MIN_MSIX_VECT);
	पूर्ण

	अगर (ret < 0) अणु
		dev_err(&adapter->netdev->dev,
			"Failed to enable MSI-X, error: %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण


#पूर्ण_अगर /* CONFIG_PCI_MSI */

अटल व्योम
vmxnet3_alloc_पूर्णांकr_resources(काष्ठा vmxnet3_adapter *adapter)
अणु
	u32 cfg;
	अचिन्हित दीर्घ flags;

	/* पूर्णांकr settings */
	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
			       VMXNET3_CMD_GET_CONF_INTR);
	cfg = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_CMD);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);
	adapter->पूर्णांकr.type = cfg & 0x3;
	adapter->पूर्णांकr.mask_mode = (cfg >> 2) & 0x3;

	अगर (adapter->पूर्णांकr.type == VMXNET3_IT_AUTO) अणु
		adapter->पूर्णांकr.type = VMXNET3_IT_MSIX;
	पूर्ण

#अगर_घोषित CONFIG_PCI_MSI
	अगर (adapter->पूर्णांकr.type == VMXNET3_IT_MSIX) अणु
		पूर्णांक i, nvec;

		nvec  = adapter->share_पूर्णांकr == VMXNET3_INTR_TXSHARE ?
			1 : adapter->num_tx_queues;
		nvec += adapter->share_पूर्णांकr == VMXNET3_INTR_BUDDYSHARE ?
			0 : adapter->num_rx_queues;
		nvec += 1;	/* क्रम link event */
		nvec = nvec > VMXNET3_LINUX_MIN_MSIX_VECT ?
		       nvec : VMXNET3_LINUX_MIN_MSIX_VECT;

		क्रम (i = 0; i < nvec; i++)
			adapter->पूर्णांकr.msix_entries[i].entry = i;

		nvec = vmxnet3_acquire_msix_vectors(adapter, nvec);
		अगर (nvec < 0)
			जाओ msix_err;

		/* If we cannot allocate one MSIx vector per queue
		 * then limit the number of rx queues to 1
		 */
		अगर (nvec == VMXNET3_LINUX_MIN_MSIX_VECT) अणु
			अगर (adapter->share_पूर्णांकr != VMXNET3_INTR_BUDDYSHARE
			    || adapter->num_rx_queues != 1) अणु
				adapter->share_पूर्णांकr = VMXNET3_INTR_TXSHARE;
				netdev_err(adapter->netdev,
					   "Number of rx queues : 1\n");
				adapter->num_rx_queues = 1;
			पूर्ण
		पूर्ण

		adapter->पूर्णांकr.num_पूर्णांकrs = nvec;
		वापस;

msix_err:
		/* If we cannot allocate MSIx vectors use only one rx queue */
		dev_info(&adapter->pdev->dev,
			 "Failed to enable MSI-X, error %d. "
			 "Limiting #rx queues to 1, try MSI.\n", nvec);

		adapter->पूर्णांकr.type = VMXNET3_IT_MSI;
	पूर्ण

	अगर (adapter->पूर्णांकr.type == VMXNET3_IT_MSI) अणु
		अगर (!pci_enable_msi(adapter->pdev)) अणु
			adapter->num_rx_queues = 1;
			adapter->पूर्णांकr.num_पूर्णांकrs = 1;
			वापस;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_PCI_MSI */

	adapter->num_rx_queues = 1;
	dev_info(&adapter->netdev->dev,
		 "Using INTx interrupt, #Rx queues: 1.\n");
	adapter->पूर्णांकr.type = VMXNET3_IT_INTX;

	/* INT-X related setting */
	adapter->पूर्णांकr.num_पूर्णांकrs = 1;
पूर्ण


अटल व्योम
vmxnet3_मुक्त_पूर्णांकr_resources(काष्ठा vmxnet3_adapter *adapter)
अणु
	अगर (adapter->पूर्णांकr.type == VMXNET3_IT_MSIX)
		pci_disable_msix(adapter->pdev);
	अन्यथा अगर (adapter->पूर्णांकr.type == VMXNET3_IT_MSI)
		pci_disable_msi(adapter->pdev);
	अन्यथा
		BUG_ON(adapter->पूर्णांकr.type != VMXNET3_IT_INTX);
पूर्ण


अटल व्योम
vmxnet3_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	adapter->tx_समयout_count++;

	netdev_err(adapter->netdev, "tx hang\n");
	schedule_work(&adapter->work);
पूर्ण


अटल व्योम
vmxnet3_reset_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा vmxnet3_adapter *adapter;

	adapter = container_of(data, काष्ठा vmxnet3_adapter, work);

	/* अगर another thपढ़ो is resetting the device, no need to proceed */
	अगर (test_and_set_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state))
		वापस;

	/* अगर the device is बंदd, we must leave it alone */
	rtnl_lock();
	अगर (netअगर_running(adapter->netdev)) अणु
		netdev_notice(adapter->netdev, "resetting\n");
		vmxnet3_quiesce_dev(adapter);
		vmxnet3_reset_dev(adapter);
		vmxnet3_activate_dev(adapter);
	पूर्ण अन्यथा अणु
		netdev_info(adapter->netdev, "already closed\n");
	पूर्ण
	rtnl_unlock();

	netअगर_wake_queue(adapter->netdev);
	clear_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state);
पूर्ण


अटल पूर्णांक
vmxnet3_probe_device(काष्ठा pci_dev *pdev,
		     स्थिर काष्ठा pci_device_id *id)
अणु
	अटल स्थिर काष्ठा net_device_ops vmxnet3_netdev_ops = अणु
		.nकरो_खोलो = vmxnet3_खोलो,
		.nकरो_stop = vmxnet3_बंद,
		.nकरो_start_xmit = vmxnet3_xmit_frame,
		.nकरो_set_mac_address = vmxnet3_set_mac_addr,
		.nकरो_change_mtu = vmxnet3_change_mtu,
		.nकरो_fix_features = vmxnet3_fix_features,
		.nकरो_set_features = vmxnet3_set_features,
		.nकरो_features_check = vmxnet3_features_check,
		.nकरो_get_stats64 = vmxnet3_get_stats64,
		.nकरो_tx_समयout = vmxnet3_tx_समयout,
		.nकरो_set_rx_mode = vmxnet3_set_mc,
		.nकरो_vlan_rx_add_vid = vmxnet3_vlan_rx_add_vid,
		.nकरो_vlan_rx_समाप्त_vid = vmxnet3_vlan_rx_समाप्त_vid,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
		.nकरो_poll_controller = vmxnet3_netpoll,
#पूर्ण_अगर
	पूर्ण;
	पूर्णांक err;
	bool dma64;
	u32 ver;
	काष्ठा net_device *netdev;
	काष्ठा vmxnet3_adapter *adapter;
	u8 mac[ETH_ALEN];
	पूर्णांक size;
	पूर्णांक num_tx_queues;
	पूर्णांक num_rx_queues;

	अगर (!pci_msi_enabled())
		enable_mq = 0;

#अगर_घोषित VMXNET3_RSS
	अगर (enable_mq)
		num_rx_queues = min(VMXNET3_DEVICE_MAX_RX_QUEUES,
				    (पूर्णांक)num_online_cpus());
	अन्यथा
#पूर्ण_अगर
		num_rx_queues = 1;
	num_rx_queues = roundकरोwn_घात_of_two(num_rx_queues);

	अगर (enable_mq)
		num_tx_queues = min(VMXNET3_DEVICE_MAX_TX_QUEUES,
				    (पूर्णांक)num_online_cpus());
	अन्यथा
		num_tx_queues = 1;

	num_tx_queues = roundकरोwn_घात_of_two(num_tx_queues);
	netdev = alloc_etherdev_mq(माप(काष्ठा vmxnet3_adapter),
				   max(num_tx_queues, num_rx_queues));
	dev_info(&pdev->dev,
		 "# of Tx queues : %d, # of Rx queues : %d\n",
		 num_tx_queues, num_rx_queues);

	अगर (!netdev)
		वापस -ENOMEM;

	pci_set_drvdata(pdev, netdev);
	adapter = netdev_priv(netdev);
	adapter->netdev = netdev;
	adapter->pdev = pdev;

	adapter->tx_ring_size = VMXNET3_DEF_TX_RING_SIZE;
	adapter->rx_ring_size = VMXNET3_DEF_RX_RING_SIZE;
	adapter->rx_ring2_size = VMXNET3_DEF_RX_RING2_SIZE;

	अगर (pci_set_dma_mask(pdev, DMA_BIT_MASK(64)) == 0) अणु
		अगर (pci_set_consistent_dma_mask(pdev, DMA_BIT_MASK(64)) != 0) अणु
			dev_err(&pdev->dev,
				"pci_set_consistent_dma_mask failed\n");
			err = -EIO;
			जाओ err_set_mask;
		पूर्ण
		dma64 = true;
	पूर्ण अन्यथा अणु
		अगर (pci_set_dma_mask(pdev, DMA_BIT_MASK(32)) != 0) अणु
			dev_err(&pdev->dev,
				"pci_set_dma_mask failed\n");
			err = -EIO;
			जाओ err_set_mask;
		पूर्ण
		dma64 = false;
	पूर्ण

	spin_lock_init(&adapter->cmd_lock);
	adapter->adapter_pa = dma_map_single(&adapter->pdev->dev, adapter,
					     माप(काष्ठा vmxnet3_adapter),
					     PCI_DMA_TODEVICE);
	अगर (dma_mapping_error(&adapter->pdev->dev, adapter->adapter_pa)) अणु
		dev_err(&pdev->dev, "Failed to map dma\n");
		err = -EFAULT;
		जाओ err_set_mask;
	पूर्ण
	adapter->shared = dma_alloc_coherent(
				&adapter->pdev->dev,
				माप(काष्ठा Vmxnet3_DriverShared),
				&adapter->shared_pa, GFP_KERNEL);
	अगर (!adapter->shared) अणु
		dev_err(&pdev->dev, "Failed to allocate memory\n");
		err = -ENOMEM;
		जाओ err_alloc_shared;
	पूर्ण

	adapter->num_rx_queues = num_rx_queues;
	adapter->num_tx_queues = num_tx_queues;
	adapter->rx_buf_per_pkt = 1;

	size = माप(काष्ठा Vmxnet3_TxQueueDesc) * adapter->num_tx_queues;
	size += माप(काष्ठा Vmxnet3_RxQueueDesc) * adapter->num_rx_queues;
	adapter->tqd_start = dma_alloc_coherent(&adapter->pdev->dev, size,
						&adapter->queue_desc_pa,
						GFP_KERNEL);

	अगर (!adapter->tqd_start) अणु
		dev_err(&pdev->dev, "Failed to allocate memory\n");
		err = -ENOMEM;
		जाओ err_alloc_queue_desc;
	पूर्ण
	adapter->rqd_start = (काष्ठा Vmxnet3_RxQueueDesc *)(adapter->tqd_start +
							    adapter->num_tx_queues);

	adapter->pm_conf = dma_alloc_coherent(&adapter->pdev->dev,
					      माप(काष्ठा Vmxnet3_PMConf),
					      &adapter->pm_conf_pa,
					      GFP_KERNEL);
	अगर (adapter->pm_conf == शून्य) अणु
		err = -ENOMEM;
		जाओ err_alloc_pm;
	पूर्ण

#अगर_घोषित VMXNET3_RSS

	adapter->rss_conf = dma_alloc_coherent(&adapter->pdev->dev,
					       माप(काष्ठा UPT1_RSSConf),
					       &adapter->rss_conf_pa,
					       GFP_KERNEL);
	अगर (adapter->rss_conf == शून्य) अणु
		err = -ENOMEM;
		जाओ err_alloc_rss;
	पूर्ण
#पूर्ण_अगर /* VMXNET3_RSS */

	err = vmxnet3_alloc_pci_resources(adapter);
	अगर (err < 0)
		जाओ err_alloc_pci;

	ver = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_VRRS);
	अगर (ver & (1 << VMXNET3_REV_4)) अणु
		VMXNET3_WRITE_BAR1_REG(adapter,
				       VMXNET3_REG_VRRS,
				       1 << VMXNET3_REV_4);
		adapter->version = VMXNET3_REV_4 + 1;
	पूर्ण अन्यथा अगर (ver & (1 << VMXNET3_REV_3)) अणु
		VMXNET3_WRITE_BAR1_REG(adapter,
				       VMXNET3_REG_VRRS,
				       1 << VMXNET3_REV_3);
		adapter->version = VMXNET3_REV_3 + 1;
	पूर्ण अन्यथा अगर (ver & (1 << VMXNET3_REV_2)) अणु
		VMXNET3_WRITE_BAR1_REG(adapter,
				       VMXNET3_REG_VRRS,
				       1 << VMXNET3_REV_2);
		adapter->version = VMXNET3_REV_2 + 1;
	पूर्ण अन्यथा अगर (ver & (1 << VMXNET3_REV_1)) अणु
		VMXNET3_WRITE_BAR1_REG(adapter,
				       VMXNET3_REG_VRRS,
				       1 << VMXNET3_REV_1);
		adapter->version = VMXNET3_REV_1 + 1;
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev,
			"Incompatible h/w version (0x%x) for adapter\n", ver);
		err = -EBUSY;
		जाओ err_ver;
	पूर्ण
	dev_dbg(&pdev->dev, "Using device version %d\n", adapter->version);

	ver = VMXNET3_READ_BAR1_REG(adapter, VMXNET3_REG_UVRS);
	अगर (ver & 1) अणु
		VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_UVRS, 1);
	पूर्ण अन्यथा अणु
		dev_err(&pdev->dev,
			"Incompatible upt version (0x%x) for adapter\n", ver);
		err = -EBUSY;
		जाओ err_ver;
	पूर्ण

	अगर (VMXNET3_VERSION_GE_3(adapter)) अणु
		adapter->coal_conf =
			dma_alloc_coherent(&adapter->pdev->dev,
					   माप(काष्ठा Vmxnet3_CoalesceScheme)
					   ,
					   &adapter->coal_conf_pa,
					   GFP_KERNEL);
		अगर (!adapter->coal_conf) अणु
			err = -ENOMEM;
			जाओ err_ver;
		पूर्ण
		adapter->coal_conf->coalMode = VMXNET3_COALESCE_DISABLED;
		adapter->शेष_coal_mode = true;
	पूर्ण

	अगर (VMXNET3_VERSION_GE_4(adapter)) अणु
		adapter->शेष_rss_fields = true;
		adapter->rss_fields = VMXNET3_RSS_FIELDS_DEFAULT;
	पूर्ण

	SET_NETDEV_DEV(netdev, &pdev->dev);
	vmxnet3_declare_features(adapter, dma64);

	adapter->rxdata_desc_size = VMXNET3_VERSION_GE_3(adapter) ?
		VMXNET3_DEF_RXDATA_DESC_SIZE : 0;

	अगर (adapter->num_tx_queues == adapter->num_rx_queues)
		adapter->share_पूर्णांकr = VMXNET3_INTR_BUDDYSHARE;
	अन्यथा
		adapter->share_पूर्णांकr = VMXNET3_INTR_DONTSHARE;

	vmxnet3_alloc_पूर्णांकr_resources(adapter);

#अगर_घोषित VMXNET3_RSS
	अगर (adapter->num_rx_queues > 1 &&
	    adapter->पूर्णांकr.type == VMXNET3_IT_MSIX) अणु
		adapter->rss = true;
		netdev->hw_features |= NETIF_F_RXHASH;
		netdev->features |= NETIF_F_RXHASH;
		dev_dbg(&pdev->dev, "RSS is enabled.\n");
	पूर्ण अन्यथा अणु
		adapter->rss = false;
	पूर्ण
#पूर्ण_अगर

	vmxnet3_पढ़ो_mac_addr(adapter, mac);
	स_नकल(netdev->dev_addr,  mac, netdev->addr_len);

	netdev->netdev_ops = &vmxnet3_netdev_ops;
	vmxnet3_set_ethtool_ops(netdev);
	netdev->watchकरोg_समयo = 5 * HZ;

	/* MTU range: 60 - 9000 */
	netdev->min_mtu = VMXNET3_MIN_MTU;
	netdev->max_mtu = VMXNET3_MAX_MTU;

	INIT_WORK(&adapter->work, vmxnet3_reset_work);
	set_bit(VMXNET3_STATE_BIT_QUIESCED, &adapter->state);

	अगर (adapter->पूर्णांकr.type == VMXNET3_IT_MSIX) अणु
		पूर्णांक i;
		क्रम (i = 0; i < adapter->num_rx_queues; i++) अणु
			netअगर_napi_add(adapter->netdev,
				       &adapter->rx_queue[i].napi,
				       vmxnet3_poll_rx_only, 64);
		पूर्ण
	पूर्ण अन्यथा अणु
		netअगर_napi_add(adapter->netdev, &adapter->rx_queue[0].napi,
			       vmxnet3_poll, 64);
	पूर्ण

	netअगर_set_real_num_tx_queues(adapter->netdev, adapter->num_tx_queues);
	netअगर_set_real_num_rx_queues(adapter->netdev, adapter->num_rx_queues);

	netअगर_carrier_off(netdev);
	err = रेजिस्टर_netdev(netdev);

	अगर (err) अणु
		dev_err(&pdev->dev, "Failed to register adapter\n");
		जाओ err_रेजिस्टर;
	पूर्ण

	vmxnet3_check_link(adapter, false);
	वापस 0;

err_रेजिस्टर:
	अगर (VMXNET3_VERSION_GE_3(adapter)) अणु
		dma_मुक्त_coherent(&adapter->pdev->dev,
				  माप(काष्ठा Vmxnet3_CoalesceScheme),
				  adapter->coal_conf, adapter->coal_conf_pa);
	पूर्ण
	vmxnet3_मुक्त_पूर्णांकr_resources(adapter);
err_ver:
	vmxnet3_मुक्त_pci_resources(adapter);
err_alloc_pci:
#अगर_घोषित VMXNET3_RSS
	dma_मुक्त_coherent(&adapter->pdev->dev, माप(काष्ठा UPT1_RSSConf),
			  adapter->rss_conf, adapter->rss_conf_pa);
err_alloc_rss:
#पूर्ण_अगर
	dma_मुक्त_coherent(&adapter->pdev->dev, माप(काष्ठा Vmxnet3_PMConf),
			  adapter->pm_conf, adapter->pm_conf_pa);
err_alloc_pm:
	dma_मुक्त_coherent(&adapter->pdev->dev, size, adapter->tqd_start,
			  adapter->queue_desc_pa);
err_alloc_queue_desc:
	dma_मुक्त_coherent(&adapter->pdev->dev,
			  माप(काष्ठा Vmxnet3_DriverShared),
			  adapter->shared, adapter->shared_pa);
err_alloc_shared:
	dma_unmap_single(&adapter->pdev->dev, adapter->adapter_pa,
			 माप(काष्ठा vmxnet3_adapter), PCI_DMA_TODEVICE);
err_set_mask:
	मुक्त_netdev(netdev);
	वापस err;
पूर्ण


अटल व्योम
vmxnet3_हटाओ_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	पूर्णांक size = 0;
	पूर्णांक num_rx_queues;

#अगर_घोषित VMXNET3_RSS
	अगर (enable_mq)
		num_rx_queues = min(VMXNET3_DEVICE_MAX_RX_QUEUES,
				    (पूर्णांक)num_online_cpus());
	अन्यथा
#पूर्ण_अगर
		num_rx_queues = 1;
	num_rx_queues = roundकरोwn_घात_of_two(num_rx_queues);

	cancel_work_sync(&adapter->work);

	unरेजिस्टर_netdev(netdev);

	vmxnet3_मुक्त_पूर्णांकr_resources(adapter);
	vmxnet3_मुक्त_pci_resources(adapter);
	अगर (VMXNET3_VERSION_GE_3(adapter)) अणु
		dma_मुक्त_coherent(&adapter->pdev->dev,
				  माप(काष्ठा Vmxnet3_CoalesceScheme),
				  adapter->coal_conf, adapter->coal_conf_pa);
	पूर्ण
#अगर_घोषित VMXNET3_RSS
	dma_मुक्त_coherent(&adapter->pdev->dev, माप(काष्ठा UPT1_RSSConf),
			  adapter->rss_conf, adapter->rss_conf_pa);
#पूर्ण_अगर
	dma_मुक्त_coherent(&adapter->pdev->dev, माप(काष्ठा Vmxnet3_PMConf),
			  adapter->pm_conf, adapter->pm_conf_pa);

	size = माप(काष्ठा Vmxnet3_TxQueueDesc) * adapter->num_tx_queues;
	size += माप(काष्ठा Vmxnet3_RxQueueDesc) * num_rx_queues;
	dma_मुक्त_coherent(&adapter->pdev->dev, size, adapter->tqd_start,
			  adapter->queue_desc_pa);
	dma_मुक्त_coherent(&adapter->pdev->dev,
			  माप(काष्ठा Vmxnet3_DriverShared),
			  adapter->shared, adapter->shared_pa);
	dma_unmap_single(&adapter->pdev->dev, adapter->adapter_pa,
			 माप(काष्ठा vmxnet3_adapter), PCI_DMA_TODEVICE);
	मुक्त_netdev(netdev);
पूर्ण

अटल व्योम vmxnet3_shutकरोwn_device(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;

	/* Reset_work may be in the middle of resetting the device, रुको क्रम its
	 * completion.
	 */
	जबतक (test_and_set_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state))
		usleep_range(1000, 2000);

	अगर (test_and_set_bit(VMXNET3_STATE_BIT_QUIESCED,
			     &adapter->state)) अणु
		clear_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state);
		वापस;
	पूर्ण
	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
			       VMXNET3_CMD_QUIESCE_DEV);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);
	vmxnet3_disable_all_पूर्णांकrs(adapter);

	clear_bit(VMXNET3_STATE_BIT_RESETTING, &adapter->state);
पूर्ण


#अगर_घोषित CONFIG_PM

अटल पूर्णांक
vmxnet3_suspend(काष्ठा device *device)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);
	काष्ठा Vmxnet3_PMConf *pmConf;
	काष्ठा ethhdr *ehdr;
	काष्ठा arphdr *ahdr;
	u8 *arpreq;
	काष्ठा in_device *in_dev;
	काष्ठा in_अगरaddr *अगरa;
	अचिन्हित दीर्घ flags;
	पूर्णांक i = 0;

	अगर (!netअगर_running(netdev))
		वापस 0;

	क्रम (i = 0; i < adapter->num_rx_queues; i++)
		napi_disable(&adapter->rx_queue[i].napi);

	vmxnet3_disable_all_पूर्णांकrs(adapter);
	vmxnet3_मुक्त_irqs(adapter);
	vmxnet3_मुक्त_पूर्णांकr_resources(adapter);

	netअगर_device_detach(netdev);
	netअगर_tx_stop_all_queues(netdev);

	/* Create wake-up filters. */
	pmConf = adapter->pm_conf;
	स_रखो(pmConf, 0, माप(*pmConf));

	अगर (adapter->wol & WAKE_UCAST) अणु
		pmConf->filters[i].patternSize = ETH_ALEN;
		pmConf->filters[i].maskSize = 1;
		स_नकल(pmConf->filters[i].pattern, netdev->dev_addr, ETH_ALEN);
		pmConf->filters[i].mask[0] = 0x3F; /* LSB ETH_ALEN bits */

		pmConf->wakeUpEvents |= VMXNET3_PM_WAKEUP_FILTER;
		i++;
	पूर्ण

	अगर (adapter->wol & WAKE_ARP) अणु
		rcu_पढ़ो_lock();

		in_dev = __in_dev_get_rcu(netdev);
		अगर (!in_dev) अणु
			rcu_पढ़ो_unlock();
			जाओ skip_arp;
		पूर्ण

		अगरa = rcu_dereference(in_dev->अगरa_list);
		अगर (!अगरa) अणु
			rcu_पढ़ो_unlock();
			जाओ skip_arp;
		पूर्ण

		pmConf->filters[i].patternSize = ETH_HLEN + /* Ethernet header*/
			माप(काष्ठा arphdr) +		/* ARP header */
			2 * ETH_ALEN +		/* 2 Ethernet addresses*/
			2 * माप(u32);	/*2 IPv4 addresses */
		pmConf->filters[i].maskSize =
			(pmConf->filters[i].patternSize - 1) / 8 + 1;

		/* ETH_P_ARP in Ethernet header. */
		ehdr = (काष्ठा ethhdr *)pmConf->filters[i].pattern;
		ehdr->h_proto = htons(ETH_P_ARP);

		/* ARPOP_REQUEST in ARP header. */
		ahdr = (काष्ठा arphdr *)&pmConf->filters[i].pattern[ETH_HLEN];
		ahdr->ar_op = htons(ARPOP_REQUEST);
		arpreq = (u8 *)(ahdr + 1);

		/* The Unicast IPv4 address in 'tip' field. */
		arpreq += 2 * ETH_ALEN + माप(u32);
		*(__be32 *)arpreq = अगरa->अगरa_address;

		rcu_पढ़ो_unlock();

		/* The mask क्रम the relevant bits. */
		pmConf->filters[i].mask[0] = 0x00;
		pmConf->filters[i].mask[1] = 0x30; /* ETH_P_ARP */
		pmConf->filters[i].mask[2] = 0x30; /* ARPOP_REQUEST */
		pmConf->filters[i].mask[3] = 0x00;
		pmConf->filters[i].mask[4] = 0xC0; /* IPv4 TIP */
		pmConf->filters[i].mask[5] = 0x03; /* IPv4 TIP */

		pmConf->wakeUpEvents |= VMXNET3_PM_WAKEUP_FILTER;
		i++;
	पूर्ण

skip_arp:
	अगर (adapter->wol & WAKE_MAGIC)
		pmConf->wakeUpEvents |= VMXNET3_PM_WAKEUP_MAGIC;

	pmConf->numFilters = i;

	adapter->shared->devRead.pmConfDesc.confVer = cpu_to_le32(1);
	adapter->shared->devRead.pmConfDesc.confLen = cpu_to_le32(माप(
								  *pmConf));
	adapter->shared->devRead.pmConfDesc.confPA =
		cpu_to_le64(adapter->pm_conf_pa);

	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
			       VMXNET3_CMD_UPDATE_PMCFG);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);

	pci_save_state(pdev);
	pci_enable_wake(pdev, pci_choose_state(pdev, PMSG_SUSPEND),
			adapter->wol);
	pci_disable_device(pdev);
	pci_set_घातer_state(pdev, pci_choose_state(pdev, PMSG_SUSPEND));

	वापस 0;
पूर्ण


अटल पूर्णांक
vmxnet3_resume(काष्ठा device *device)
अणु
	पूर्णांक err;
	अचिन्हित दीर्घ flags;
	काष्ठा pci_dev *pdev = to_pci_dev(device);
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा vmxnet3_adapter *adapter = netdev_priv(netdev);

	अगर (!netअगर_running(netdev))
		वापस 0;

	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);
	err = pci_enable_device_mem(pdev);
	अगर (err != 0)
		वापस err;

	pci_enable_wake(pdev, PCI_D0, 0);

	vmxnet3_alloc_पूर्णांकr_resources(adapter);

	/* During hibernate and suspend, device has to be reinitialized as the
	 * device state need not be preserved.
	 */

	/* Need not check adapter state as other reset tasks cannot run during
	 * device resume.
	 */
	spin_lock_irqsave(&adapter->cmd_lock, flags);
	VMXNET3_WRITE_BAR1_REG(adapter, VMXNET3_REG_CMD,
			       VMXNET3_CMD_QUIESCE_DEV);
	spin_unlock_irqrestore(&adapter->cmd_lock, flags);
	vmxnet3_tq_cleanup_all(adapter);
	vmxnet3_rq_cleanup_all(adapter);

	vmxnet3_reset_dev(adapter);
	err = vmxnet3_activate_dev(adapter);
	अगर (err != 0) अणु
		netdev_err(netdev,
			   "failed to re-activate on resume, error: %d", err);
		vmxnet3_क्रमce_बंद(adapter);
		वापस err;
	पूर्ण
	netअगर_device_attach(netdev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dev_pm_ops vmxnet3_pm_ops = अणु
	.suspend = vmxnet3_suspend,
	.resume = vmxnet3_resume,
	.मुक्तze = vmxnet3_suspend,
	.restore = vmxnet3_resume,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा pci_driver vmxnet3_driver = अणु
	.name		= vmxnet3_driver_name,
	.id_table	= vmxnet3_pciid_table,
	.probe		= vmxnet3_probe_device,
	.हटाओ		= vmxnet3_हटाओ_device,
	.shutकरोwn	= vmxnet3_shutकरोwn_device,
#अगर_घोषित CONFIG_PM
	.driver.pm	= &vmxnet3_pm_ops,
#पूर्ण_अगर
पूर्ण;


अटल पूर्णांक __init
vmxnet3_init_module(व्योम)
अणु
	pr_info("%s - version %s\n", VMXNET3_DRIVER_DESC,
		VMXNET3_DRIVER_VERSION_REPORT);
	वापस pci_रेजिस्टर_driver(&vmxnet3_driver);
पूर्ण

module_init(vmxnet3_init_module);


अटल व्योम
vmxnet3_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&vmxnet3_driver);
पूर्ण

module_निकास(vmxnet3_निकास_module);

MODULE_AUTHOR("VMware, Inc.");
MODULE_DESCRIPTION(VMXNET3_DRIVER_DESC);
MODULE_LICENSE("GPL v2");
MODULE_VERSION(VMXNET3_DRIVER_VERSION_STRING);
