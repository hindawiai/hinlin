<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2006-2009 Freescale Semicondutor, Inc. All rights reserved.
 *
 * Author: Shlomi Gridish <gridish@मुक्तscale.com>
 *	   Li Yang <leoli@मुक्तscale.com>
 *
 * Description:
 * QE UCC Gigabit Ethernet Driver
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/mm.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/mii.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <soc/fsl/qe/immap_qe.h>
#समावेश <soc/fsl/qe/qe.h>
#समावेश <soc/fsl/qe/ucc.h>
#समावेश <soc/fsl/qe/ucc_fast.h>
#समावेश <यंत्र/machdep.h>

#समावेश "ucc_geth.h"

#अघोषित DEBUG

#घोषणा ugeth_prपूर्णांकk(level, क्रमmat, arg...)  \
        prपूर्णांकk(level क्रमmat "\n", ## arg)

#घोषणा ugeth_dbg(क्रमmat, arg...)            \
        ugeth_prपूर्णांकk(KERN_DEBUG , क्रमmat , ## arg)

#अगर_घोषित UGETH_VERBOSE_DEBUG
#घोषणा ugeth_vdbg ugeth_dbg
#अन्यथा
#घोषणा ugeth_vdbg(fmt, args...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर				/* UGETH_VERBOSE_DEBUG */
#घोषणा UGETH_MSG_DEFAULT	(NETIF_MSG_IFUP << 1 ) - 1


अटल DEFINE_SPINLOCK(ugeth_lock);

अटल काष्ठा अणु
	u32 msg_enable;
पूर्ण debug = अणु -1 पूर्ण;

module_param_named(debug, debug.msg_enable, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug verbosity level (0=none, ..., 0xffff=all)");

अटल पूर्णांक ucc_geth_thपढ़ो_count(क्रमागत ucc_geth_num_of_thपढ़ोs idx)
अणु
	अटल स्थिर u8 count[] = अणु
		[UCC_GETH_NUM_OF_THREADS_1] = 1,
		[UCC_GETH_NUM_OF_THREADS_2] = 2,
		[UCC_GETH_NUM_OF_THREADS_4] = 4,
		[UCC_GETH_NUM_OF_THREADS_6] = 6,
		[UCC_GETH_NUM_OF_THREADS_8] = 8,
	पूर्ण;
	अगर (idx >= ARRAY_SIZE(count))
		वापस 0;
	वापस count[idx];
पूर्ण

अटल अंतरभूत पूर्णांक ucc_geth_tx_queues(स्थिर काष्ठा ucc_geth_info *info)
अणु
	वापस 1;
पूर्ण

अटल अंतरभूत पूर्णांक ucc_geth_rx_queues(स्थिर काष्ठा ucc_geth_info *info)
अणु
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा ucc_geth_info ugeth_primary_info = अणु
	.uf_info = अणु
		    .rtsm = UCC_FAST_SEND_IDLES_BETWEEN_FRAMES,
		    .max_rx_buf_length = 1536,
		    /* adjusted at startup अगर max-speed 1000 */
		    .urfs = UCC_GETH_URFS_INIT,
		    .urfet = UCC_GETH_URFET_INIT,
		    .urfset = UCC_GETH_URFSET_INIT,
		    .utfs = UCC_GETH_UTFS_INIT,
		    .utfet = UCC_GETH_UTFET_INIT,
		    .utftt = UCC_GETH_UTFTT_INIT,
		    .ufpt = 256,
		    .mode = UCC_FAST_PROTOCOL_MODE_ETHERNET,
		    .ttx_trx = UCC_FAST_GUMR_TRANSPARENT_TTX_TRX_NORMAL,
		    .tenc = UCC_FAST_TX_ENCODING_NRZ,
		    .renc = UCC_FAST_RX_ENCODING_NRZ,
		    .tcrc = UCC_FAST_16_BIT_CRC,
		    .synl = UCC_FAST_SYNC_LEN_NOT_USED,
		    पूर्ण,
	.extendedFilteringChainPoपूर्णांकer = ((uपूर्णांक32_t) शून्य),
	.typeorlen = 3072 /*1536 */ ,
	.nonBackToBackIfgPart1 = 0x40,
	.nonBackToBackIfgPart2 = 0x60,
	.miminumInterFrameGapEnक्रमcement = 0x50,
	.backToBackInterFrameGap = 0x60,
	.mblपूर्णांकerval = 128,
	.nortsrbyteसमय = 5,
	.fracsiz = 1,
	.strictpriorityq = 0xff,
	.altBebTruncation = 0xa,
	.excessDefer = 1,
	.maxRetransmission = 0xf,
	.collisionWinकरोw = 0x37,
	.receiveFlowControl = 1,
	.transmitFlowControl = 1,
	.maxGroupAddrInHash = 4,
	.maxIndAddrInHash = 4,
	.prel = 7,
	.maxFrameLength = 1518+16, /* Add extra bytes क्रम VLANs etc. */
	.minFrameLength = 64,
	.maxD1Length = 1520+16, /* Add extra bytes क्रम VLANs etc. */
	.maxD2Length = 1520+16, /* Add extra bytes क्रम VLANs etc. */
	.vlantype = 0x8100,
	.ecamptr = ((uपूर्णांक32_t) शून्य),
	.eventRegMask = UCCE_OTHER,
	.छोड़ोPeriod = 0xf000,
	.पूर्णांकerruptcoalescingmaxvalue = अणु1, 1, 1, 1, 1, 1, 1, 1पूर्ण,
	.bdRingLenTx = अणु
			TX_BD_RING_LEN,
			TX_BD_RING_LEN,
			TX_BD_RING_LEN,
			TX_BD_RING_LEN,
			TX_BD_RING_LEN,
			TX_BD_RING_LEN,
			TX_BD_RING_LEN,
			TX_BD_RING_LENपूर्ण,

	.bdRingLenRx = अणु
			RX_BD_RING_LEN,
			RX_BD_RING_LEN,
			RX_BD_RING_LEN,
			RX_BD_RING_LEN,
			RX_BD_RING_LEN,
			RX_BD_RING_LEN,
			RX_BD_RING_LEN,
			RX_BD_RING_LENपूर्ण,

	.numStationAddresses = UCC_GETH_NUM_OF_STATION_ADDRESSES_1,
	.largestबाह्यallookupkeysize =
	    QE_FLTR_LARGEST_EXTERNAL_TABLE_LOOKUP_KEY_SIZE_NONE,
	.statisticsMode = UCC_GETH_STATISTICS_GATHERING_MODE_HARDWARE |
		UCC_GETH_STATISTICS_GATHERING_MODE_FIRMWARE_TX |
		UCC_GETH_STATISTICS_GATHERING_MODE_FIRMWARE_RX,
	.vlanOperationTagged = UCC_GETH_VLAN_OPERATION_TAGGED_NOP,
	.vlanOperationNonTagged = UCC_GETH_VLAN_OPERATION_NON_TAGGED_NOP,
	.rxQoSMode = UCC_GETH_QOS_MODE_DEFAULT,
	.aufc = UPSMR_AUTOMATIC_FLOW_CONTROL_MODE_NONE,
	.padAndCrc = MACCFG2_PAD_AND_CRC_MODE_PAD_AND_CRC,
	.numThपढ़ोsTx = UCC_GETH_NUM_OF_THREADS_1,
	.numThपढ़ोsRx = UCC_GETH_NUM_OF_THREADS_1,
	.riscTx = QE_RISC_ALLOCATION_RISC1_AND_RISC2,
	.riscRx = QE_RISC_ALLOCATION_RISC1_AND_RISC2,
पूर्ण;

#अगर_घोषित DEBUG
अटल व्योम mem_disp(u8 *addr, पूर्णांक size)
अणु
	u8 *i;
	पूर्णांक size16Aling = (size >> 4) << 4;
	पूर्णांक size4Aling = (size >> 2) << 2;
	पूर्णांक notAlign = 0;
	अगर (size % 16)
		notAlign = 1;

	क्रम (i = addr; (u32) i < (u32) addr + size16Aling; i += 16)
		prपूर्णांकk("0x%08x: %08x %08x %08x %08x\r\n",
		       (u32) i,
		       *((u32 *) (i)),
		       *((u32 *) (i + 4)),
		       *((u32 *) (i + 8)), *((u32 *) (i + 12)));
	अगर (notAlign == 1)
		prपूर्णांकk("0x%08x: ", (u32) i);
	क्रम (; (u32) i < (u32) addr + size4Aling; i += 4)
		prपूर्णांकk("%08x ", *((u32 *) (i)));
	क्रम (; (u32) i < (u32) addr + size; i++)
		prपूर्णांकk("%02x", *((i)));
	अगर (notAlign == 1)
		prपूर्णांकk("\r\n");
पूर्ण
#पूर्ण_अगर /* DEBUG */

अटल काष्ठा list_head *dequeue(काष्ठा list_head *lh)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&ugeth_lock, flags);
	अगर (!list_empty(lh)) अणु
		काष्ठा list_head *node = lh->next;
		list_del(node);
		spin_unlock_irqrestore(&ugeth_lock, flags);
		वापस node;
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&ugeth_lock, flags);
		वापस शून्य;
	पूर्ण
पूर्ण

अटल काष्ठा sk_buff *get_new_skb(काष्ठा ucc_geth_निजी *ugeth,
		u8 __iomem *bd)
अणु
	काष्ठा sk_buff *skb;

	skb = netdev_alloc_skb(ugeth->ndev,
			       ugeth->ug_info->uf_info.max_rx_buf_length +
			       UCC_GETH_RX_DATA_BUF_ALIGNMENT);
	अगर (!skb)
		वापस शून्य;

	/* We need the data buffer to be aligned properly.  We will reserve
	 * as many bytes as needed to align the data properly
	 */
	skb_reserve(skb,
		    UCC_GETH_RX_DATA_BUF_ALIGNMENT -
		    (((अचिन्हित)skb->data) & (UCC_GETH_RX_DATA_BUF_ALIGNMENT -
					      1)));

	out_be32(&((काष्ठा qe_bd __iomem *)bd)->buf,
		      dma_map_single(ugeth->dev,
				     skb->data,
				     ugeth->ug_info->uf_info.max_rx_buf_length +
				     UCC_GETH_RX_DATA_BUF_ALIGNMENT,
				     DMA_FROM_DEVICE));

	out_be32((u32 __iomem *)bd,
			(R_E | R_I | (in_be32((u32 __iomem*)bd) & R_W)));

	वापस skb;
पूर्ण

अटल पूर्णांक rx_bd_buffer_set(काष्ठा ucc_geth_निजी *ugeth, u8 rxQ)
अणु
	u8 __iomem *bd;
	u32 bd_status;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	bd = ugeth->p_rx_bd_ring[rxQ];
	i = 0;

	करो अणु
		bd_status = in_be32((u32 __iomem *)bd);
		skb = get_new_skb(ugeth, bd);

		अगर (!skb)	/* If can not allocate data buffer,
				पात. Cleanup will be अन्यथाwhere */
			वापस -ENOMEM;

		ugeth->rx_skbuff[rxQ][i] = skb;

		/* advance the BD poपूर्णांकer */
		bd += माप(काष्ठा qe_bd);
		i++;
	पूर्ण जबतक (!(bd_status & R_W));

	वापस 0;
पूर्ण

अटल पूर्णांक fill_init_enet_entries(काष्ठा ucc_geth_निजी *ugeth,
				  u32 *p_start,
				  u8 num_entries,
				  u32 thपढ़ो_size,
				  u32 thपढ़ो_alignment,
				  अचिन्हित पूर्णांक risc,
				  पूर्णांक skip_page_क्रम_first_entry)
अणु
	u32 init_enet_offset;
	u8 i;
	पूर्णांक snum;

	क्रम (i = 0; i < num_entries; i++) अणु
		अगर ((snum = qe_get_snum()) < 0) अणु
			अगर (netअगर_msg_अगरup(ugeth))
				pr_err("Can not get SNUM\n");
			वापस snum;
		पूर्ण
		अगर ((i == 0) && skip_page_क्रम_first_entry)
		/* First entry of Rx करोes not have page */
			init_enet_offset = 0;
		अन्यथा अणु
			init_enet_offset =
			    qe_muram_alloc(thपढ़ो_size, thपढ़ो_alignment);
			अगर (IS_ERR_VALUE(init_enet_offset)) अणु
				अगर (netअगर_msg_अगरup(ugeth))
					pr_err("Can not allocate DPRAM memory\n");
				qe_put_snum((u8) snum);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण
		*(p_start++) =
		    ((u8) snum << ENET_INIT_PARAM_SNUM_SHIFT) | init_enet_offset
		    | risc;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक वापस_init_enet_entries(काष्ठा ucc_geth_निजी *ugeth,
				    u32 *p_start,
				    u8 num_entries,
				    अचिन्हित पूर्णांक risc,
				    पूर्णांक skip_page_क्रम_first_entry)
अणु
	u32 init_enet_offset;
	u8 i;
	पूर्णांक snum;

	क्रम (i = 0; i < num_entries; i++) अणु
		u32 val = *p_start;

		/* Check that this entry was actually valid --
		needed in हाल failed in allocations */
		अगर ((val & ENET_INIT_PARAM_RISC_MASK) == risc) अणु
			snum =
			    (u32) (val & ENET_INIT_PARAM_SNUM_MASK) >>
			    ENET_INIT_PARAM_SNUM_SHIFT;
			qe_put_snum((u8) snum);
			अगर (!((i == 0) && skip_page_क्रम_first_entry)) अणु
			/* First entry of Rx करोes not have page */
				init_enet_offset =
				    (val & ENET_INIT_PARAM_PTR_MASK);
				qe_muram_मुक्त(init_enet_offset);
			पूर्ण
			*p_start++ = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित DEBUG
अटल पूर्णांक dump_init_enet_entries(काष्ठा ucc_geth_निजी *ugeth,
				  u32 __iomem *p_start,
				  u8 num_entries,
				  u32 thपढ़ो_size,
				  अचिन्हित पूर्णांक risc,
				  पूर्णांक skip_page_क्रम_first_entry)
अणु
	u32 init_enet_offset;
	u8 i;
	पूर्णांक snum;

	क्रम (i = 0; i < num_entries; i++) अणु
		u32 val = in_be32(p_start);

		/* Check that this entry was actually valid --
		needed in हाल failed in allocations */
		अगर ((val & ENET_INIT_PARAM_RISC_MASK) == risc) अणु
			snum =
			    (u32) (val & ENET_INIT_PARAM_SNUM_MASK) >>
			    ENET_INIT_PARAM_SNUM_SHIFT;
			qe_put_snum((u8) snum);
			अगर (!((i == 0) && skip_page_क्रम_first_entry)) अणु
			/* First entry of Rx करोes not have page */
				init_enet_offset =
				    (in_be32(p_start) &
				     ENET_INIT_PARAM_PTR_MASK);
				pr_info("Init enet entry %d:\n", i);
				pr_info("Base address: 0x%08x\n",
					(u32)qe_muram_addr(init_enet_offset));
				mem_disp(qe_muram_addr(init_enet_offset),
					 thपढ़ो_size);
			पूर्ण
			p_start++;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम put_enet_addr_container(काष्ठा enet_addr_container *enet_addr_cont)
अणु
	kमुक्त(enet_addr_cont);
पूर्ण

अटल व्योम set_mac_addr(__be16 __iomem *reg, u8 *mac)
अणु
	out_be16(&reg[0], ((u16)mac[5] << 8) | mac[4]);
	out_be16(&reg[1], ((u16)mac[3] << 8) | mac[2]);
	out_be16(&reg[2], ((u16)mac[1] << 8) | mac[0]);
पूर्ण

अटल पूर्णांक hw_clear_addr_in_paddr(काष्ठा ucc_geth_निजी *ugeth, u8 paddr_num)
अणु
	काष्ठा ucc_geth_82xx_address_filtering_pram __iomem *p_82xx_addr_filt;

	अगर (paddr_num >= NUM_OF_PADDRS) अणु
		pr_warn("%s: Invalid paddr_num: %u\n", __func__, paddr_num);
		वापस -EINVAL;
	पूर्ण

	p_82xx_addr_filt =
	    (काष्ठा ucc_geth_82xx_address_filtering_pram __iomem *) ugeth->p_rx_glbl_pram->
	    addressfiltering;

	/* Writing address ff.ff.ff.ff.ff.ff disables address
	recognition क्रम this रेजिस्टर */
	out_be16(&p_82xx_addr_filt->paddr[paddr_num].h, 0xffff);
	out_be16(&p_82xx_addr_filt->paddr[paddr_num].m, 0xffff);
	out_be16(&p_82xx_addr_filt->paddr[paddr_num].l, 0xffff);

	वापस 0;
पूर्ण

अटल व्योम hw_add_addr_in_hash(काष्ठा ucc_geth_निजी *ugeth,
                                u8 *p_enet_addr)
अणु
	काष्ठा ucc_geth_82xx_address_filtering_pram __iomem *p_82xx_addr_filt;
	u32 cecr_subblock;

	p_82xx_addr_filt =
	    (काष्ठा ucc_geth_82xx_address_filtering_pram __iomem *) ugeth->p_rx_glbl_pram->
	    addressfiltering;

	cecr_subblock =
	    ucc_fast_get_qe_cr_subblock(ugeth->ug_info->uf_info.ucc_num);

	/* Ethernet frames are defined in Little Endian mode,
	thereक्रमe to insert */
	/* the address to the hash (Big Endian mode), we reverse the bytes.*/

	set_mac_addr(&p_82xx_addr_filt->taddr.h, p_enet_addr);

	qe_issue_cmd(QE_SET_GROUP_ADDRESS, cecr_subblock,
		     QE_CR_PROTOCOL_ETHERNET, 0);
पूर्ण

#अगर_घोषित DEBUG
अटल व्योम get_statistics(काष्ठा ucc_geth_निजी *ugeth,
			   काष्ठा ucc_geth_tx_firmware_statistics *
			   tx_firmware_statistics,
			   काष्ठा ucc_geth_rx_firmware_statistics *
			   rx_firmware_statistics,
			   काष्ठा ucc_geth_hardware_statistics *hardware_statistics)
अणु
	काष्ठा ucc_fast __iomem *uf_regs;
	काष्ठा ucc_geth __iomem *ug_regs;
	काष्ठा ucc_geth_tx_firmware_statistics_pram *p_tx_fw_statistics_pram;
	काष्ठा ucc_geth_rx_firmware_statistics_pram *p_rx_fw_statistics_pram;

	ug_regs = ugeth->ug_regs;
	uf_regs = (काष्ठा ucc_fast __iomem *) ug_regs;
	p_tx_fw_statistics_pram = ugeth->p_tx_fw_statistics_pram;
	p_rx_fw_statistics_pram = ugeth->p_rx_fw_statistics_pram;

	/* Tx firmware only अगर user handed poपूर्णांकer and driver actually
	gathers Tx firmware statistics */
	अगर (tx_firmware_statistics && p_tx_fw_statistics_pram) अणु
		tx_firmware_statistics->sicoltx =
		    in_be32(&p_tx_fw_statistics_pram->sicoltx);
		tx_firmware_statistics->mulcoltx =
		    in_be32(&p_tx_fw_statistics_pram->mulcoltx);
		tx_firmware_statistics->latecoltxfr =
		    in_be32(&p_tx_fw_statistics_pram->latecoltxfr);
		tx_firmware_statistics->frपातduecol =
		    in_be32(&p_tx_fw_statistics_pram->frपातduecol);
		tx_firmware_statistics->frlostinmactxer =
		    in_be32(&p_tx_fw_statistics_pram->frlostinmactxer);
		tx_firmware_statistics->carriersenseertx =
		    in_be32(&p_tx_fw_statistics_pram->carriersenseertx);
		tx_firmware_statistics->frtxok =
		    in_be32(&p_tx_fw_statistics_pram->frtxok);
		tx_firmware_statistics->txfrexcessivedefer =
		    in_be32(&p_tx_fw_statistics_pram->txfrexcessivedefer);
		tx_firmware_statistics->txpkts256 =
		    in_be32(&p_tx_fw_statistics_pram->txpkts256);
		tx_firmware_statistics->txpkts512 =
		    in_be32(&p_tx_fw_statistics_pram->txpkts512);
		tx_firmware_statistics->txpkts1024 =
		    in_be32(&p_tx_fw_statistics_pram->txpkts1024);
		tx_firmware_statistics->txpktsjumbo =
		    in_be32(&p_tx_fw_statistics_pram->txpktsjumbo);
	पूर्ण

	/* Rx firmware only अगर user handed poपूर्णांकer and driver actually
	 * gathers Rx firmware statistics */
	अगर (rx_firmware_statistics && p_rx_fw_statistics_pram) अणु
		पूर्णांक i;
		rx_firmware_statistics->frrxfcser =
		    in_be32(&p_rx_fw_statistics_pram->frrxfcser);
		rx_firmware_statistics->fraligner =
		    in_be32(&p_rx_fw_statistics_pram->fraligner);
		rx_firmware_statistics->inrangelenrxer =
		    in_be32(&p_rx_fw_statistics_pram->inrangelenrxer);
		rx_firmware_statistics->outrangelenrxer =
		    in_be32(&p_rx_fw_statistics_pram->outrangelenrxer);
		rx_firmware_statistics->frtooदीर्घ =
		    in_be32(&p_rx_fw_statistics_pram->frtooदीर्घ);
		rx_firmware_statistics->runt =
		    in_be32(&p_rx_fw_statistics_pram->runt);
		rx_firmware_statistics->veryदीर्घevent =
		    in_be32(&p_rx_fw_statistics_pram->veryदीर्घevent);
		rx_firmware_statistics->symbolerror =
		    in_be32(&p_rx_fw_statistics_pram->symbolerror);
		rx_firmware_statistics->dropbsy =
		    in_be32(&p_rx_fw_statistics_pram->dropbsy);
		क्रम (i = 0; i < 0x8; i++)
			rx_firmware_statistics->res0[i] =
			    p_rx_fw_statistics_pram->res0[i];
		rx_firmware_statistics->mismatchdrop =
		    in_be32(&p_rx_fw_statistics_pram->mismatchdrop);
		rx_firmware_statistics->underpkts =
		    in_be32(&p_rx_fw_statistics_pram->underpkts);
		rx_firmware_statistics->pkts256 =
		    in_be32(&p_rx_fw_statistics_pram->pkts256);
		rx_firmware_statistics->pkts512 =
		    in_be32(&p_rx_fw_statistics_pram->pkts512);
		rx_firmware_statistics->pkts1024 =
		    in_be32(&p_rx_fw_statistics_pram->pkts1024);
		rx_firmware_statistics->pktsjumbo =
		    in_be32(&p_rx_fw_statistics_pram->pktsjumbo);
		rx_firmware_statistics->frlossinmacer =
		    in_be32(&p_rx_fw_statistics_pram->frlossinmacer);
		rx_firmware_statistics->छोड़ोfr =
		    in_be32(&p_rx_fw_statistics_pram->छोड़ोfr);
		क्रम (i = 0; i < 0x4; i++)
			rx_firmware_statistics->res1[i] =
			    p_rx_fw_statistics_pram->res1[i];
		rx_firmware_statistics->हटाओvlan =
		    in_be32(&p_rx_fw_statistics_pram->हटाओvlan);
		rx_firmware_statistics->replacevlan =
		    in_be32(&p_rx_fw_statistics_pram->replacevlan);
		rx_firmware_statistics->insertvlan =
		    in_be32(&p_rx_fw_statistics_pram->insertvlan);
	पूर्ण

	/* Hardware only अगर user handed poपूर्णांकer and driver actually
	gathers hardware statistics */
	अगर (hardware_statistics &&
	    (in_be32(&uf_regs->upsmr) & UCC_GETH_UPSMR_HSE)) अणु
		hardware_statistics->tx64 = in_be32(&ug_regs->tx64);
		hardware_statistics->tx127 = in_be32(&ug_regs->tx127);
		hardware_statistics->tx255 = in_be32(&ug_regs->tx255);
		hardware_statistics->rx64 = in_be32(&ug_regs->rx64);
		hardware_statistics->rx127 = in_be32(&ug_regs->rx127);
		hardware_statistics->rx255 = in_be32(&ug_regs->rx255);
		hardware_statistics->txok = in_be32(&ug_regs->txok);
		hardware_statistics->txcf = in_be16(&ug_regs->txcf);
		hardware_statistics->पंचांगca = in_be32(&ug_regs->पंचांगca);
		hardware_statistics->tbca = in_be32(&ug_regs->tbca);
		hardware_statistics->rxfok = in_be32(&ug_regs->rxfok);
		hardware_statistics->rxbok = in_be32(&ug_regs->rxbok);
		hardware_statistics->rbyt = in_be32(&ug_regs->rbyt);
		hardware_statistics->rmca = in_be32(&ug_regs->rmca);
		hardware_statistics->rbca = in_be32(&ug_regs->rbca);
	पूर्ण
पूर्ण

अटल व्योम dump_bds(काष्ठा ucc_geth_निजी *ugeth)
अणु
	पूर्णांक i;
	पूर्णांक length;

	क्रम (i = 0; i < ucc_geth_tx_queues(ugeth->ug_info); i++) अणु
		अगर (ugeth->p_tx_bd_ring[i]) अणु
			length =
			    (ugeth->ug_info->bdRingLenTx[i] *
			     माप(काष्ठा qe_bd));
			pr_info("TX BDs[%d]\n", i);
			mem_disp(ugeth->p_tx_bd_ring[i], length);
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < ucc_geth_rx_queues(ugeth->ug_info); i++) अणु
		अगर (ugeth->p_rx_bd_ring[i]) अणु
			length =
			    (ugeth->ug_info->bdRingLenRx[i] *
			     माप(काष्ठा qe_bd));
			pr_info("RX BDs[%d]\n", i);
			mem_disp(ugeth->p_rx_bd_ring[i], length);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम dump_regs(काष्ठा ucc_geth_निजी *ugeth)
अणु
	पूर्णांक i;

	pr_info("UCC%d Geth registers:\n", ugeth->ug_info->uf_info.ucc_num + 1);
	pr_info("Base address: 0x%08x\n", (u32)ugeth->ug_regs);

	pr_info("maccfg1    : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->maccfg1,
		in_be32(&ugeth->ug_regs->maccfg1));
	pr_info("maccfg2    : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->maccfg2,
		in_be32(&ugeth->ug_regs->maccfg2));
	pr_info("ipgifg     : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->ipgअगरg,
		in_be32(&ugeth->ug_regs->ipgअगरg));
	pr_info("hafdup     : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->hafdup,
		in_be32(&ugeth->ug_regs->hafdup));
	pr_info("ifctl      : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->अगरctl,
		in_be32(&ugeth->ug_regs->अगरctl));
	pr_info("ifstat     : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->अगरstat,
		in_be32(&ugeth->ug_regs->अगरstat));
	pr_info("macstnaddr1: addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->macstnaddr1,
		in_be32(&ugeth->ug_regs->macstnaddr1));
	pr_info("macstnaddr2: addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->macstnaddr2,
		in_be32(&ugeth->ug_regs->macstnaddr2));
	pr_info("uempr      : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->uempr,
		in_be32(&ugeth->ug_regs->uempr));
	pr_info("utbipar    : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->utbipar,
		in_be32(&ugeth->ug_regs->utbipar));
	pr_info("uescr      : addr - 0x%08x, val - 0x%04x\n",
		(u32)&ugeth->ug_regs->uescr,
		in_be16(&ugeth->ug_regs->uescr));
	pr_info("tx64       : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->tx64,
		in_be32(&ugeth->ug_regs->tx64));
	pr_info("tx127      : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->tx127,
		in_be32(&ugeth->ug_regs->tx127));
	pr_info("tx255      : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->tx255,
		in_be32(&ugeth->ug_regs->tx255));
	pr_info("rx64       : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->rx64,
		in_be32(&ugeth->ug_regs->rx64));
	pr_info("rx127      : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->rx127,
		in_be32(&ugeth->ug_regs->rx127));
	pr_info("rx255      : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->rx255,
		in_be32(&ugeth->ug_regs->rx255));
	pr_info("txok       : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->txok,
		in_be32(&ugeth->ug_regs->txok));
	pr_info("txcf       : addr - 0x%08x, val - 0x%04x\n",
		(u32)&ugeth->ug_regs->txcf,
		in_be16(&ugeth->ug_regs->txcf));
	pr_info("tmca       : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->पंचांगca,
		in_be32(&ugeth->ug_regs->पंचांगca));
	pr_info("tbca       : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->tbca,
		in_be32(&ugeth->ug_regs->tbca));
	pr_info("rxfok      : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->rxfok,
		in_be32(&ugeth->ug_regs->rxfok));
	pr_info("rxbok      : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->rxbok,
		in_be32(&ugeth->ug_regs->rxbok));
	pr_info("rbyt       : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->rbyt,
		in_be32(&ugeth->ug_regs->rbyt));
	pr_info("rmca       : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->rmca,
		in_be32(&ugeth->ug_regs->rmca));
	pr_info("rbca       : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->rbca,
		in_be32(&ugeth->ug_regs->rbca));
	pr_info("scar       : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->scar,
		in_be32(&ugeth->ug_regs->scar));
	pr_info("scam       : addr - 0x%08x, val - 0x%08x\n",
		(u32)&ugeth->ug_regs->scam,
		in_be32(&ugeth->ug_regs->scam));

	अगर (ugeth->p_thपढ़ो_data_tx) अणु
		पूर्णांक count = ucc_geth_thपढ़ो_count(ugeth->ug_info->numThपढ़ोsTx);

		pr_info("Thread data TXs:\n");
		pr_info("Base address: 0x%08x\n",
			(u32)ugeth->p_thपढ़ो_data_tx);
		क्रम (i = 0; i < count; i++) अणु
			pr_info("Thread data TX[%d]:\n", i);
			pr_info("Base address: 0x%08x\n",
				(u32)&ugeth->p_thपढ़ो_data_tx[i]);
			mem_disp((u8 *) & ugeth->p_thपढ़ो_data_tx[i],
				 माप(काष्ठा ucc_geth_thपढ़ो_data_tx));
		पूर्ण
	पूर्ण
	अगर (ugeth->p_thपढ़ो_data_rx) अणु
		पूर्णांक count = ucc_geth_thपढ़ो_count(ugeth->ug_info->numThपढ़ोsRx);

		pr_info("Thread data RX:\n");
		pr_info("Base address: 0x%08x\n",
			(u32)ugeth->p_thपढ़ो_data_rx);
		क्रम (i = 0; i < count; i++) अणु
			pr_info("Thread data RX[%d]:\n", i);
			pr_info("Base address: 0x%08x\n",
				(u32)&ugeth->p_thपढ़ो_data_rx[i]);
			mem_disp((u8 *) & ugeth->p_thपढ़ो_data_rx[i],
				 माप(काष्ठा ucc_geth_thपढ़ो_data_rx));
		पूर्ण
	पूर्ण
	अगर (ugeth->p_exf_glbl_param) अणु
		pr_info("EXF global param:\n");
		pr_info("Base address: 0x%08x\n",
			(u32)ugeth->p_exf_glbl_param);
		mem_disp((u8 *) ugeth->p_exf_glbl_param,
			 माप(*ugeth->p_exf_glbl_param));
	पूर्ण
	अगर (ugeth->p_tx_glbl_pram) अणु
		pr_info("TX global param:\n");
		pr_info("Base address: 0x%08x\n", (u32)ugeth->p_tx_glbl_pram);
		pr_info("temoder      : addr - 0x%08x, val - 0x%04x\n",
			(u32)&ugeth->p_tx_glbl_pram->temoder,
			in_be16(&ugeth->p_tx_glbl_pram->temoder));
	       pr_info("sqptr        : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_tx_glbl_pram->sqptr,
			in_be32(&ugeth->p_tx_glbl_pram->sqptr));
		pr_info("schedulerbasepointer: addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_tx_glbl_pram->schedulerbasepoपूर्णांकer,
			in_be32(&ugeth->p_tx_glbl_pram->schedulerbasepoपूर्णांकer));
		pr_info("txrmonbaseptr: addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_tx_glbl_pram->txrmonbaseptr,
			in_be32(&ugeth->p_tx_glbl_pram->txrmonbaseptr));
		pr_info("tstate       : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_tx_glbl_pram->tstate,
			in_be32(&ugeth->p_tx_glbl_pram->tstate));
		pr_info("iphoffset[0] : addr - 0x%08x, val - 0x%02x\n",
			(u32)&ugeth->p_tx_glbl_pram->iphoffset[0],
			ugeth->p_tx_glbl_pram->iphoffset[0]);
		pr_info("iphoffset[1] : addr - 0x%08x, val - 0x%02x\n",
			(u32)&ugeth->p_tx_glbl_pram->iphoffset[1],
			ugeth->p_tx_glbl_pram->iphoffset[1]);
		pr_info("iphoffset[2] : addr - 0x%08x, val - 0x%02x\n",
			(u32)&ugeth->p_tx_glbl_pram->iphoffset[2],
			ugeth->p_tx_glbl_pram->iphoffset[2]);
		pr_info("iphoffset[3] : addr - 0x%08x, val - 0x%02x\n",
			(u32)&ugeth->p_tx_glbl_pram->iphoffset[3],
			ugeth->p_tx_glbl_pram->iphoffset[3]);
		pr_info("iphoffset[4] : addr - 0x%08x, val - 0x%02x\n",
			(u32)&ugeth->p_tx_glbl_pram->iphoffset[4],
			ugeth->p_tx_glbl_pram->iphoffset[4]);
		pr_info("iphoffset[5] : addr - 0x%08x, val - 0x%02x\n",
			(u32)&ugeth->p_tx_glbl_pram->iphoffset[5],
			ugeth->p_tx_glbl_pram->iphoffset[5]);
		pr_info("iphoffset[6] : addr - 0x%08x, val - 0x%02x\n",
			(u32)&ugeth->p_tx_glbl_pram->iphoffset[6],
			ugeth->p_tx_glbl_pram->iphoffset[6]);
		pr_info("iphoffset[7] : addr - 0x%08x, val - 0x%02x\n",
			(u32)&ugeth->p_tx_glbl_pram->iphoffset[7],
			ugeth->p_tx_glbl_pram->iphoffset[7]);
		pr_info("vtagtable[0] : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_tx_glbl_pram->vtagtable[0],
			in_be32(&ugeth->p_tx_glbl_pram->vtagtable[0]));
		pr_info("vtagtable[1] : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_tx_glbl_pram->vtagtable[1],
			in_be32(&ugeth->p_tx_glbl_pram->vtagtable[1]));
		pr_info("vtagtable[2] : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_tx_glbl_pram->vtagtable[2],
			in_be32(&ugeth->p_tx_glbl_pram->vtagtable[2]));
		pr_info("vtagtable[3] : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_tx_glbl_pram->vtagtable[3],
			in_be32(&ugeth->p_tx_glbl_pram->vtagtable[3]));
		pr_info("vtagtable[4] : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_tx_glbl_pram->vtagtable[4],
			in_be32(&ugeth->p_tx_glbl_pram->vtagtable[4]));
		pr_info("vtagtable[5] : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_tx_glbl_pram->vtagtable[5],
			in_be32(&ugeth->p_tx_glbl_pram->vtagtable[5]));
		pr_info("vtagtable[6] : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_tx_glbl_pram->vtagtable[6],
			in_be32(&ugeth->p_tx_glbl_pram->vtagtable[6]));
		pr_info("vtagtable[7] : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_tx_glbl_pram->vtagtable[7],
			in_be32(&ugeth->p_tx_glbl_pram->vtagtable[7]));
		pr_info("tqptr        : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_tx_glbl_pram->tqptr,
			in_be32(&ugeth->p_tx_glbl_pram->tqptr));
	पूर्ण
	अगर (ugeth->p_rx_glbl_pram) अणु
		pr_info("RX global param:\n");
		pr_info("Base address: 0x%08x\n", (u32)ugeth->p_rx_glbl_pram);
		pr_info("remoder         : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->remoder,
			in_be32(&ugeth->p_rx_glbl_pram->remoder));
		pr_info("rqptr           : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->rqptr,
			in_be32(&ugeth->p_rx_glbl_pram->rqptr));
		pr_info("typeorlen       : addr - 0x%08x, val - 0x%04x\n",
			(u32)&ugeth->p_rx_glbl_pram->typeorlen,
			in_be16(&ugeth->p_rx_glbl_pram->typeorlen));
		pr_info("rxgstpack       : addr - 0x%08x, val - 0x%02x\n",
			(u32)&ugeth->p_rx_glbl_pram->rxgstpack,
			ugeth->p_rx_glbl_pram->rxgstpack);
		pr_info("rxrmonbaseptr   : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->rxrmonbaseptr,
			in_be32(&ugeth->p_rx_glbl_pram->rxrmonbaseptr));
		pr_info("intcoalescingptr: addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->पूर्णांकcoalescingptr,
			in_be32(&ugeth->p_rx_glbl_pram->पूर्णांकcoalescingptr));
		pr_info("rstate          : addr - 0x%08x, val - 0x%02x\n",
			(u32)&ugeth->p_rx_glbl_pram->rstate,
			ugeth->p_rx_glbl_pram->rstate);
		pr_info("mrblr           : addr - 0x%08x, val - 0x%04x\n",
			(u32)&ugeth->p_rx_glbl_pram->mrblr,
			in_be16(&ugeth->p_rx_glbl_pram->mrblr));
		pr_info("rbdqptr         : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->rbdqptr,
			in_be32(&ugeth->p_rx_glbl_pram->rbdqptr));
		pr_info("mflr            : addr - 0x%08x, val - 0x%04x\n",
			(u32)&ugeth->p_rx_glbl_pram->mflr,
			in_be16(&ugeth->p_rx_glbl_pram->mflr));
		pr_info("minflr          : addr - 0x%08x, val - 0x%04x\n",
			(u32)&ugeth->p_rx_glbl_pram->minflr,
			in_be16(&ugeth->p_rx_glbl_pram->minflr));
		pr_info("maxd1           : addr - 0x%08x, val - 0x%04x\n",
			(u32)&ugeth->p_rx_glbl_pram->maxd1,
			in_be16(&ugeth->p_rx_glbl_pram->maxd1));
		pr_info("maxd2           : addr - 0x%08x, val - 0x%04x\n",
			(u32)&ugeth->p_rx_glbl_pram->maxd2,
			in_be16(&ugeth->p_rx_glbl_pram->maxd2));
		pr_info("ecamptr         : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->ecamptr,
			in_be32(&ugeth->p_rx_glbl_pram->ecamptr));
		pr_info("l2qt            : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->l2qt,
			in_be32(&ugeth->p_rx_glbl_pram->l2qt));
		pr_info("l3qt[0]         : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->l3qt[0],
			in_be32(&ugeth->p_rx_glbl_pram->l3qt[0]));
		pr_info("l3qt[1]         : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->l3qt[1],
			in_be32(&ugeth->p_rx_glbl_pram->l3qt[1]));
		pr_info("l3qt[2]         : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->l3qt[2],
			in_be32(&ugeth->p_rx_glbl_pram->l3qt[2]));
		pr_info("l3qt[3]         : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->l3qt[3],
			in_be32(&ugeth->p_rx_glbl_pram->l3qt[3]));
		pr_info("l3qt[4]         : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->l3qt[4],
			in_be32(&ugeth->p_rx_glbl_pram->l3qt[4]));
		pr_info("l3qt[5]         : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->l3qt[5],
			in_be32(&ugeth->p_rx_glbl_pram->l3qt[5]));
		pr_info("l3qt[6]         : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->l3qt[6],
			in_be32(&ugeth->p_rx_glbl_pram->l3qt[6]));
		pr_info("l3qt[7]         : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->l3qt[7],
			in_be32(&ugeth->p_rx_glbl_pram->l3qt[7]));
		pr_info("vlantype        : addr - 0x%08x, val - 0x%04x\n",
			(u32)&ugeth->p_rx_glbl_pram->vlantype,
			in_be16(&ugeth->p_rx_glbl_pram->vlantype));
		pr_info("vlantci         : addr - 0x%08x, val - 0x%04x\n",
			(u32)&ugeth->p_rx_glbl_pram->vlantci,
			in_be16(&ugeth->p_rx_glbl_pram->vlantci));
		क्रम (i = 0; i < 64; i++)
			pr_info("addressfiltering[%d]: addr - 0x%08x, val - 0x%02x\n",
				i,
				(u32)&ugeth->p_rx_glbl_pram->addressfiltering[i],
				ugeth->p_rx_glbl_pram->addressfiltering[i]);
		pr_info("exfGlobalParam  : addr - 0x%08x, val - 0x%08x\n",
			(u32)&ugeth->p_rx_glbl_pram->exfGlobalParam,
			in_be32(&ugeth->p_rx_glbl_pram->exfGlobalParam));
	पूर्ण
	अगर (ugeth->p_send_q_mem_reg) अणु
		pr_info("Send Q memory registers:\n");
		pr_info("Base address: 0x%08x\n", (u32)ugeth->p_send_q_mem_reg);
		क्रम (i = 0; i < ucc_geth_tx_queues(ugeth->ug_info); i++) अणु
			pr_info("SQQD[%d]:\n", i);
			pr_info("Base address: 0x%08x\n",
				(u32)&ugeth->p_send_q_mem_reg->sqqd[i]);
			mem_disp((u8 *) & ugeth->p_send_q_mem_reg->sqqd[i],
				 माप(काष्ठा ucc_geth_send_queue_qd));
		पूर्ण
	पूर्ण
	अगर (ugeth->p_scheduler) अणु
		pr_info("Scheduler:\n");
		pr_info("Base address: 0x%08x\n", (u32)ugeth->p_scheduler);
		mem_disp((u8 *) ugeth->p_scheduler,
			 माप(*ugeth->p_scheduler));
	पूर्ण
	अगर (ugeth->p_tx_fw_statistics_pram) अणु
		pr_info("TX FW statistics pram:\n");
		pr_info("Base address: 0x%08x\n",
			(u32)ugeth->p_tx_fw_statistics_pram);
		mem_disp((u8 *) ugeth->p_tx_fw_statistics_pram,
			 माप(*ugeth->p_tx_fw_statistics_pram));
	पूर्ण
	अगर (ugeth->p_rx_fw_statistics_pram) अणु
		pr_info("RX FW statistics pram:\n");
		pr_info("Base address: 0x%08x\n",
			(u32)ugeth->p_rx_fw_statistics_pram);
		mem_disp((u8 *) ugeth->p_rx_fw_statistics_pram,
			 माप(*ugeth->p_rx_fw_statistics_pram));
	पूर्ण
	अगर (ugeth->p_rx_irq_coalescing_tbl) अणु
		pr_info("RX IRQ coalescing tables:\n");
		pr_info("Base address: 0x%08x\n",
			(u32)ugeth->p_rx_irq_coalescing_tbl);
		क्रम (i = 0; i < ucc_geth_rx_queues(ugeth->ug_info); i++) अणु
			pr_info("RX IRQ coalescing table entry[%d]:\n", i);
			pr_info("Base address: 0x%08x\n",
				(u32)&ugeth->p_rx_irq_coalescing_tbl->
				coalescingentry[i]);
			pr_info("interruptcoalescingmaxvalue: addr - 0x%08x, val - 0x%08x\n",
				(u32)&ugeth->p_rx_irq_coalescing_tbl->
				coalescingentry[i].पूर्णांकerruptcoalescingmaxvalue,
				in_be32(&ugeth->p_rx_irq_coalescing_tbl->
					coalescingentry[i].
					पूर्णांकerruptcoalescingmaxvalue));
			pr_info("interruptcoalescingcounter : addr - 0x%08x, val - 0x%08x\n",
				(u32)&ugeth->p_rx_irq_coalescing_tbl->
				coalescingentry[i].पूर्णांकerruptcoalescingcounter,
				in_be32(&ugeth->p_rx_irq_coalescing_tbl->
					coalescingentry[i].
					पूर्णांकerruptcoalescingcounter));
		पूर्ण
	पूर्ण
	अगर (ugeth->p_rx_bd_qs_tbl) अणु
		pr_info("RX BD QS tables:\n");
		pr_info("Base address: 0x%08x\n", (u32)ugeth->p_rx_bd_qs_tbl);
		क्रम (i = 0; i < ucc_geth_rx_queues(ugeth->ug_info); i++) अणु
			pr_info("RX BD QS table[%d]:\n", i);
			pr_info("Base address: 0x%08x\n",
				(u32)&ugeth->p_rx_bd_qs_tbl[i]);
			pr_info("bdbaseptr        : addr - 0x%08x, val - 0x%08x\n",
				(u32)&ugeth->p_rx_bd_qs_tbl[i].bdbaseptr,
				in_be32(&ugeth->p_rx_bd_qs_tbl[i].bdbaseptr));
			pr_info("bdptr            : addr - 0x%08x, val - 0x%08x\n",
				(u32)&ugeth->p_rx_bd_qs_tbl[i].bdptr,
				in_be32(&ugeth->p_rx_bd_qs_tbl[i].bdptr));
			pr_info("externalbdbaseptr: addr - 0x%08x, val - 0x%08x\n",
				(u32)&ugeth->p_rx_bd_qs_tbl[i].बाह्यalbdbaseptr,
				in_be32(&ugeth->p_rx_bd_qs_tbl[i].
					बाह्यalbdbaseptr));
			pr_info("externalbdptr    : addr - 0x%08x, val - 0x%08x\n",
				(u32)&ugeth->p_rx_bd_qs_tbl[i].बाह्यalbdptr,
				in_be32(&ugeth->p_rx_bd_qs_tbl[i].बाह्यalbdptr));
			pr_info("ucode RX Prefetched BDs:\n");
			pr_info("Base address: 0x%08x\n",
				(u32)qe_muram_addr(in_be32
						   (&ugeth->p_rx_bd_qs_tbl[i].
						    bdbaseptr)));
			mem_disp((u8 *)
				 qe_muram_addr(in_be32
					       (&ugeth->p_rx_bd_qs_tbl[i].
						bdbaseptr)),
				 माप(काष्ठा ucc_geth_rx_prefetched_bds));
		पूर्ण
	पूर्ण
	अगर (ugeth->p_init_enet_param_shaकरोw) अणु
		पूर्णांक size;
		pr_info("Init enet param shadow:\n");
		pr_info("Base address: 0x%08x\n",
			(u32) ugeth->p_init_enet_param_shaकरोw);
		mem_disp((u8 *) ugeth->p_init_enet_param_shaकरोw,
			 माप(*ugeth->p_init_enet_param_shaकरोw));

		size = माप(काष्ठा ucc_geth_thपढ़ो_rx_pram);
		अगर (ugeth->ug_info->rxExtendedFiltering) अणु
			size +=
			    THREAD_RX_PRAM_ADDITIONAL_FOR_EXTENDED_FILTERING;
			अगर (ugeth->ug_info->largestबाह्यallookupkeysize ==
			    QE_FLTR_TABLE_LOOKUP_KEY_SIZE_8_BYTES)
				size +=
			THREAD_RX_PRAM_ADDITIONAL_FOR_EXTENDED_FILTERING_8;
			अगर (ugeth->ug_info->largestबाह्यallookupkeysize ==
			    QE_FLTR_TABLE_LOOKUP_KEY_SIZE_16_BYTES)
				size +=
			THREAD_RX_PRAM_ADDITIONAL_FOR_EXTENDED_FILTERING_16;
		पूर्ण

		dump_init_enet_entries(ugeth,
				       &(ugeth->p_init_enet_param_shaकरोw->
					 txthपढ़ो[0]),
				       ENET_INIT_PARAM_MAX_ENTRIES_TX,
				       माप(काष्ठा ucc_geth_thपढ़ो_tx_pram),
				       ugeth->ug_info->riscTx, 0);
		dump_init_enet_entries(ugeth,
				       &(ugeth->p_init_enet_param_shaकरोw->
					 rxthपढ़ो[0]),
				       ENET_INIT_PARAM_MAX_ENTRIES_RX, size,
				       ugeth->ug_info->riscRx, 1);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* DEBUG */

अटल व्योम init_शेष_reg_vals(u32 __iomem *upsmr_रेजिस्टर,
				  u32 __iomem *maccfg1_रेजिस्टर,
				  u32 __iomem *maccfg2_रेजिस्टर)
अणु
	out_be32(upsmr_रेजिस्टर, UCC_GETH_UPSMR_INIT);
	out_be32(maccfg1_रेजिस्टर, UCC_GETH_MACCFG1_INIT);
	out_be32(maccfg2_रेजिस्टर, UCC_GETH_MACCFG2_INIT);
पूर्ण

अटल पूर्णांक init_half_duplex_params(पूर्णांक alt_beb,
				   पूर्णांक back_pressure_no_backoff,
				   पूर्णांक no_backoff,
				   पूर्णांक excess_defer,
				   u8 alt_beb_truncation,
				   u8 max_retransmissions,
				   u8 collision_winकरोw,
				   u32 __iomem *hafdup_रेजिस्टर)
अणु
	u32 value = 0;

	अगर ((alt_beb_truncation > HALFDUP_ALT_BEB_TRUNCATION_MAX) ||
	    (max_retransmissions > HALFDUP_MAX_RETRANSMISSION_MAX) ||
	    (collision_winकरोw > HALFDUP_COLLISION_WINDOW_MAX))
		वापस -EINVAL;

	value = (u32) (alt_beb_truncation << HALFDUP_ALT_BEB_TRUNCATION_SHIFT);

	अगर (alt_beb)
		value |= HALFDUP_ALT_BEB;
	अगर (back_pressure_no_backoff)
		value |= HALFDUP_BACK_PRESSURE_NO_BACKOFF;
	अगर (no_backoff)
		value |= HALFDUP_NO_BACKOFF;
	अगर (excess_defer)
		value |= HALFDUP_EXCESSIVE_DEFER;

	value |= (max_retransmissions << HALFDUP_MAX_RETRANSMISSION_SHIFT);

	value |= collision_winकरोw;

	out_be32(hafdup_रेजिस्टर, value);
	वापस 0;
पूर्ण

अटल पूर्णांक init_पूर्णांकer_frame_gap_params(u8 non_btb_cs_ipg,
				       u8 non_btb_ipg,
				       u8 min_अगरg,
				       u8 btb_ipg,
				       u32 __iomem *ipgअगरg_रेजिस्टर)
अणु
	u32 value = 0;

	/* Non-Back-to-back IPG part 1 should be <= Non-Back-to-back
	IPG part 2 */
	अगर (non_btb_cs_ipg > non_btb_ipg)
		वापस -EINVAL;

	अगर ((non_btb_cs_ipg > IPGIFG_NON_BACK_TO_BACK_IFG_PART1_MAX) ||
	    (non_btb_ipg > IPGIFG_NON_BACK_TO_BACK_IFG_PART2_MAX) ||
	    /*(min_अगरg        > IPGIFG_MINIMUM_IFG_ENFORCEMENT_MAX) || */
	    (btb_ipg > IPGIFG_BACK_TO_BACK_IFG_MAX))
		वापस -EINVAL;

	value |=
	    ((non_btb_cs_ipg << IPGIFG_NON_BACK_TO_BACK_IFG_PART1_SHIFT) &
	     IPGIFG_NBTB_CS_IPG_MASK);
	value |=
	    ((non_btb_ipg << IPGIFG_NON_BACK_TO_BACK_IFG_PART2_SHIFT) &
	     IPGIFG_NBTB_IPG_MASK);
	value |=
	    ((min_अगरg << IPGIFG_MINIMUM_IFG_ENFORCEMENT_SHIFT) &
	     IPGIFG_MIN_IFG_MASK);
	value |= (btb_ipg & IPGIFG_BTB_IPG_MASK);

	out_be32(ipgअगरg_रेजिस्टर, value);
	वापस 0;
पूर्ण

पूर्णांक init_flow_control_params(u32 स्वतःmatic_flow_control_mode,
				    पूर्णांक rx_flow_control_enable,
				    पूर्णांक tx_flow_control_enable,
				    u16 छोड़ो_period,
				    u16 extension_field,
				    u32 __iomem *upsmr_रेजिस्टर,
				    u32 __iomem *uempr_रेजिस्टर,
				    u32 __iomem *maccfg1_रेजिस्टर)
अणु
	u32 value = 0;

	/* Set UEMPR रेजिस्टर */
	value = (u32) छोड़ो_period << UEMPR_PAUSE_TIME_VALUE_SHIFT;
	value |= (u32) extension_field << UEMPR_EXTENDED_PAUSE_TIME_VALUE_SHIFT;
	out_be32(uempr_रेजिस्टर, value);

	/* Set UPSMR रेजिस्टर */
	setbits32(upsmr_रेजिस्टर, स्वतःmatic_flow_control_mode);

	value = in_be32(maccfg1_रेजिस्टर);
	अगर (rx_flow_control_enable)
		value |= MACCFG1_FLOW_RX;
	अगर (tx_flow_control_enable)
		value |= MACCFG1_FLOW_TX;
	out_be32(maccfg1_रेजिस्टर, value);

	वापस 0;
पूर्ण

अटल पूर्णांक init_hw_statistics_gathering_mode(पूर्णांक enable_hardware_statistics,
					     पूर्णांक स्वतः_zero_hardware_statistics,
					     u32 __iomem *upsmr_रेजिस्टर,
					     u16 __iomem *uescr_रेजिस्टर)
अणु
	u16 uescr_value = 0;

	/* Enable hardware statistics gathering अगर requested */
	अगर (enable_hardware_statistics)
		setbits32(upsmr_रेजिस्टर, UCC_GETH_UPSMR_HSE);

	/* Clear hardware statistics counters */
	uescr_value = in_be16(uescr_रेजिस्टर);
	uescr_value |= UESCR_CLRCNT;
	/* Automatically zero hardware statistics counters on पढ़ो,
	अगर requested */
	अगर (स्वतः_zero_hardware_statistics)
		uescr_value |= UESCR_AUTOZ;
	out_be16(uescr_रेजिस्टर, uescr_value);

	वापस 0;
पूर्ण

अटल पूर्णांक init_firmware_statistics_gathering_mode(पूर्णांक
		enable_tx_firmware_statistics,
		पूर्णांक enable_rx_firmware_statistics,
		u32 __iomem *tx_rmon_base_ptr,
		u32 tx_firmware_statistics_काष्ठाure_address,
		u32 __iomem *rx_rmon_base_ptr,
		u32 rx_firmware_statistics_काष्ठाure_address,
		u16 __iomem *temoder_रेजिस्टर,
		u32 __iomem *remoder_रेजिस्टर)
अणु
	/* Note: this function करोes not check अगर */
	/* the parameters it receives are शून्य   */

	अगर (enable_tx_firmware_statistics) अणु
		out_be32(tx_rmon_base_ptr,
			 tx_firmware_statistics_काष्ठाure_address);
		setbits16(temoder_रेजिस्टर, TEMODER_TX_RMON_STATISTICS_ENABLE);
	पूर्ण

	अगर (enable_rx_firmware_statistics) अणु
		out_be32(rx_rmon_base_ptr,
			 rx_firmware_statistics_काष्ठाure_address);
		setbits32(remoder_रेजिस्टर, REMODER_RX_RMON_STATISTICS_ENABLE);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक init_mac_station_addr_regs(u8 address_byte_0,
				      u8 address_byte_1,
				      u8 address_byte_2,
				      u8 address_byte_3,
				      u8 address_byte_4,
				      u8 address_byte_5,
				      u32 __iomem *macstnaddr1_रेजिस्टर,
				      u32 __iomem *macstnaddr2_रेजिस्टर)
अणु
	u32 value = 0;

	/* Example: क्रम a station address of 0x12345678ABCD, */
	/* 0x12 is byte 0, 0x34 is byte 1 and so on and 0xCD is byte 5 */

	/* MACSTNADDR1 Register: */

	/* 0                      7   8                      15  */
	/* station address byte 5     station address byte 4     */
	/* 16                     23  24                     31  */
	/* station address byte 3     station address byte 2     */
	value |= (u32) ((address_byte_2 << 0) & 0x000000FF);
	value |= (u32) ((address_byte_3 << 8) & 0x0000FF00);
	value |= (u32) ((address_byte_4 << 16) & 0x00FF0000);
	value |= (u32) ((address_byte_5 << 24) & 0xFF000000);

	out_be32(macstnaddr1_रेजिस्टर, value);

	/* MACSTNADDR2 Register: */

	/* 0                      7   8                      15  */
	/* station address byte 1     station address byte 0     */
	/* 16                     23  24                     31  */
	/*         reserved                   reserved           */
	value = 0;
	value |= (u32) ((address_byte_0 << 16) & 0x00FF0000);
	value |= (u32) ((address_byte_1 << 24) & 0xFF000000);

	out_be32(macstnaddr2_रेजिस्टर, value);

	वापस 0;
पूर्ण

अटल पूर्णांक init_check_frame_length_mode(पूर्णांक length_check,
					u32 __iomem *maccfg2_रेजिस्टर)
अणु
	u32 value = 0;

	value = in_be32(maccfg2_रेजिस्टर);

	अगर (length_check)
		value |= MACCFG2_LC;
	अन्यथा
		value &= ~MACCFG2_LC;

	out_be32(maccfg2_रेजिस्टर, value);
	वापस 0;
पूर्ण

अटल पूर्णांक init_preamble_length(u8 preamble_length,
				u32 __iomem *maccfg2_रेजिस्टर)
अणु
	अगर ((preamble_length < 3) || (preamble_length > 7))
		वापस -EINVAL;

	clrsetbits_be32(maccfg2_रेजिस्टर, MACCFG2_PREL_MASK,
			preamble_length << MACCFG2_PREL_SHIFT);

	वापस 0;
पूर्ण

अटल पूर्णांक init_rx_parameters(पूर्णांक reject_broadcast,
			      पूर्णांक receive_लघु_frames,
			      पूर्णांक promiscuous, u32 __iomem *upsmr_रेजिस्टर)
अणु
	u32 value = 0;

	value = in_be32(upsmr_रेजिस्टर);

	अगर (reject_broadcast)
		value |= UCC_GETH_UPSMR_BRO;
	अन्यथा
		value &= ~UCC_GETH_UPSMR_BRO;

	अगर (receive_लघु_frames)
		value |= UCC_GETH_UPSMR_RSH;
	अन्यथा
		value &= ~UCC_GETH_UPSMR_RSH;

	अगर (promiscuous)
		value |= UCC_GETH_UPSMR_PRO;
	अन्यथा
		value &= ~UCC_GETH_UPSMR_PRO;

	out_be32(upsmr_रेजिस्टर, value);

	वापस 0;
पूर्ण

अटल पूर्णांक init_max_rx_buff_len(u16 max_rx_buf_len,
				u16 __iomem *mrblr_रेजिस्टर)
अणु
	/* max_rx_buf_len value must be a multiple of 128 */
	अगर ((max_rx_buf_len == 0) ||
	    (max_rx_buf_len % UCC_GETH_MRBLR_ALIGNMENT))
		वापस -EINVAL;

	out_be16(mrblr_रेजिस्टर, max_rx_buf_len);
	वापस 0;
पूर्ण

अटल पूर्णांक init_min_frame_len(u16 min_frame_length,
			      u16 __iomem *minflr_रेजिस्टर,
			      u16 __iomem *mrblr_रेजिस्टर)
अणु
	u16 mrblr_value = 0;

	mrblr_value = in_be16(mrblr_रेजिस्टर);
	अगर (min_frame_length >= (mrblr_value - 4))
		वापस -EINVAL;

	out_be16(minflr_रेजिस्टर, min_frame_length);
	वापस 0;
पूर्ण

अटल पूर्णांक adjust_enet_पूर्णांकerface(काष्ठा ucc_geth_निजी *ugeth)
अणु
	काष्ठा ucc_geth_info *ug_info;
	काष्ठा ucc_geth __iomem *ug_regs;
	काष्ठा ucc_fast __iomem *uf_regs;
	पूर्णांक ret_val;
	u32 upsmr, maccfg2;
	u16 value;

	ugeth_vdbg("%s: IN", __func__);

	ug_info = ugeth->ug_info;
	ug_regs = ugeth->ug_regs;
	uf_regs = ugeth->uccf->uf_regs;

	/*                    Set MACCFG2                    */
	maccfg2 = in_be32(&ug_regs->maccfg2);
	maccfg2 &= ~MACCFG2_INTERFACE_MODE_MASK;
	अगर ((ugeth->max_speed == SPEED_10) ||
	    (ugeth->max_speed == SPEED_100))
		maccfg2 |= MACCFG2_INTERFACE_MODE_NIBBLE;
	अन्यथा अगर (ugeth->max_speed == SPEED_1000)
		maccfg2 |= MACCFG2_INTERFACE_MODE_BYTE;
	maccfg2 |= ug_info->padAndCrc;
	out_be32(&ug_regs->maccfg2, maccfg2);

	/*                    Set UPSMR                      */
	upsmr = in_be32(&uf_regs->upsmr);
	upsmr &= ~(UCC_GETH_UPSMR_RPM | UCC_GETH_UPSMR_R10M |
		   UCC_GETH_UPSMR_TBIM | UCC_GETH_UPSMR_RMM);
	अगर ((ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RMII) ||
	    (ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII) ||
	    (ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID) ||
	    (ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID) ||
	    (ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID) ||
	    (ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RTBI)) अणु
		अगर (ugeth->phy_पूर्णांकerface != PHY_INTERFACE_MODE_RMII)
			upsmr |= UCC_GETH_UPSMR_RPM;
		चयन (ugeth->max_speed) अणु
		हाल SPEED_10:
			upsmr |= UCC_GETH_UPSMR_R10M;
			fallthrough;
		हाल SPEED_100:
			अगर (ugeth->phy_पूर्णांकerface != PHY_INTERFACE_MODE_RTBI)
				upsmr |= UCC_GETH_UPSMR_RMM;
		पूर्ण
	पूर्ण
	अगर ((ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_TBI) ||
	    (ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RTBI)) अणु
		upsmr |= UCC_GETH_UPSMR_TBIM;
	पूर्ण
	अगर (ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_SGMII)
		upsmr |= UCC_GETH_UPSMR_SGMM;

	out_be32(&uf_regs->upsmr, upsmr);

	/* Disable स्वतःnegotiation in tbi mode, because by शेष it
	comes up in स्वतःnegotiation mode. */
	/* Note that this depends on proper setting in utbipar रेजिस्टर. */
	अगर ((ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_TBI) ||
	    (ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RTBI)) अणु
		काष्ठा ucc_geth_info *ug_info = ugeth->ug_info;
		काष्ठा phy_device *tbiphy;

		अगर (!ug_info->tbi_node)
			pr_warn("TBI mode requires that the device tree specify a tbi-handle\n");

		tbiphy = of_phy_find_device(ug_info->tbi_node);
		अगर (!tbiphy)
			pr_warn("Could not get TBI device\n");

		value = phy_पढ़ो(tbiphy, ENET_TBI_MII_CR);
		value &= ~0x1000;	/* Turn off स्वतःnegotiation */
		phy_ग_लिखो(tbiphy, ENET_TBI_MII_CR, value);

		put_device(&tbiphy->mdio.dev);
	पूर्ण

	init_check_frame_length_mode(ug_info->lengthCheckRx, &ug_regs->maccfg2);

	ret_val = init_preamble_length(ug_info->prel, &ug_regs->maccfg2);
	अगर (ret_val != 0) अणु
		अगर (netअगर_msg_probe(ugeth))
			pr_err("Preamble length must be between 3 and 7 inclusive\n");
		वापस ret_val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ugeth_graceful_stop_tx(काष्ठा ucc_geth_निजी *ugeth)
अणु
	काष्ठा ucc_fast_निजी *uccf;
	u32 cecr_subblock;
	u32 temp;
	पूर्णांक i = 10;

	uccf = ugeth->uccf;

	/* Mask GRACEFUL STOP TX पूर्णांकerrupt bit and clear it */
	clrbits32(uccf->p_uccm, UCC_GETH_UCCE_GRA);
	out_be32(uccf->p_ucce, UCC_GETH_UCCE_GRA);  /* clear by writing 1 */

	/* Issue host command */
	cecr_subblock =
	    ucc_fast_get_qe_cr_subblock(ugeth->ug_info->uf_info.ucc_num);
	qe_issue_cmd(QE_GRACEFUL_STOP_TX, cecr_subblock,
		     QE_CR_PROTOCOL_ETHERNET, 0);

	/* Wait क्रम command to complete */
	करो अणु
		msleep(10);
		temp = in_be32(uccf->p_ucce);
	पूर्ण जबतक (!(temp & UCC_GETH_UCCE_GRA) && --i);

	uccf->stopped_tx = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ugeth_graceful_stop_rx(काष्ठा ucc_geth_निजी *ugeth)
अणु
	काष्ठा ucc_fast_निजी *uccf;
	u32 cecr_subblock;
	u8 temp;
	पूर्णांक i = 10;

	uccf = ugeth->uccf;

	/* Clear acknowledge bit */
	temp = in_8(&ugeth->p_rx_glbl_pram->rxgstpack);
	temp &= ~GRACEFUL_STOP_ACKNOWLEDGE_RX;
	out_8(&ugeth->p_rx_glbl_pram->rxgstpack, temp);

	/* Keep issuing command and checking acknowledge bit until
	it is निश्चितed, according to spec */
	करो अणु
		/* Issue host command */
		cecr_subblock =
		    ucc_fast_get_qe_cr_subblock(ugeth->ug_info->uf_info.
						ucc_num);
		qe_issue_cmd(QE_GRACEFUL_STOP_RX, cecr_subblock,
			     QE_CR_PROTOCOL_ETHERNET, 0);
		msleep(10);
		temp = in_8(&ugeth->p_rx_glbl_pram->rxgstpack);
	पूर्ण जबतक (!(temp & GRACEFUL_STOP_ACKNOWLEDGE_RX) && --i);

	uccf->stopped_rx = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ugeth_restart_tx(काष्ठा ucc_geth_निजी *ugeth)
अणु
	काष्ठा ucc_fast_निजी *uccf;
	u32 cecr_subblock;

	uccf = ugeth->uccf;

	cecr_subblock =
	    ucc_fast_get_qe_cr_subblock(ugeth->ug_info->uf_info.ucc_num);
	qe_issue_cmd(QE_RESTART_TX, cecr_subblock, QE_CR_PROTOCOL_ETHERNET, 0);
	uccf->stopped_tx = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ugeth_restart_rx(काष्ठा ucc_geth_निजी *ugeth)
अणु
	काष्ठा ucc_fast_निजी *uccf;
	u32 cecr_subblock;

	uccf = ugeth->uccf;

	cecr_subblock =
	    ucc_fast_get_qe_cr_subblock(ugeth->ug_info->uf_info.ucc_num);
	qe_issue_cmd(QE_RESTART_RX, cecr_subblock, QE_CR_PROTOCOL_ETHERNET,
		     0);
	uccf->stopped_rx = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक ugeth_enable(काष्ठा ucc_geth_निजी *ugeth, क्रमागत comm_dir mode)
अणु
	काष्ठा ucc_fast_निजी *uccf;
	पूर्णांक enabled_tx, enabled_rx;

	uccf = ugeth->uccf;

	/* check अगर the UCC number is in range. */
	अगर (ugeth->ug_info->uf_info.ucc_num >= UCC_MAX_NUM) अणु
		अगर (netअगर_msg_probe(ugeth))
			pr_err("ucc_num out of range\n");
		वापस -EINVAL;
	पूर्ण

	enabled_tx = uccf->enabled_tx;
	enabled_rx = uccf->enabled_rx;

	/* Get Tx and Rx going again, in हाल this channel was actively
	disabled. */
	अगर ((mode & COMM_सूची_TX) && (!enabled_tx) && uccf->stopped_tx)
		ugeth_restart_tx(ugeth);
	अगर ((mode & COMM_सूची_RX) && (!enabled_rx) && uccf->stopped_rx)
		ugeth_restart_rx(ugeth);

	ucc_fast_enable(uccf, mode);	/* OK to करो even अगर not disabled */

	वापस 0;

पूर्ण

अटल पूर्णांक ugeth_disable(काष्ठा ucc_geth_निजी *ugeth, क्रमागत comm_dir mode)
अणु
	काष्ठा ucc_fast_निजी *uccf;

	uccf = ugeth->uccf;

	/* check अगर the UCC number is in range. */
	अगर (ugeth->ug_info->uf_info.ucc_num >= UCC_MAX_NUM) अणु
		अगर (netअगर_msg_probe(ugeth))
			pr_err("ucc_num out of range\n");
		वापस -EINVAL;
	पूर्ण

	/* Stop any transmissions */
	अगर ((mode & COMM_सूची_TX) && uccf->enabled_tx && !uccf->stopped_tx)
		ugeth_graceful_stop_tx(ugeth);

	/* Stop any receptions */
	अगर ((mode & COMM_सूची_RX) && uccf->enabled_rx && !uccf->stopped_rx)
		ugeth_graceful_stop_rx(ugeth);

	ucc_fast_disable(ugeth->uccf, mode); /* OK to करो even अगर not enabled */

	वापस 0;
पूर्ण

अटल व्योम ugeth_quiesce(काष्ठा ucc_geth_निजी *ugeth)
अणु
	/* Prevent any further xmits */
	netअगर_tx_stop_all_queues(ugeth->ndev);

	/* Disable the पूर्णांकerrupt to aव्योम NAPI rescheduling. */
	disable_irq(ugeth->ug_info->uf_info.irq);

	/* Stop NAPI, and possibly रुको क्रम its completion. */
	napi_disable(&ugeth->napi);
पूर्ण

अटल व्योम ugeth_activate(काष्ठा ucc_geth_निजी *ugeth)
अणु
	napi_enable(&ugeth->napi);
	enable_irq(ugeth->ug_info->uf_info.irq);

	/* allow to xmit again  */
	netअगर_tx_wake_all_queues(ugeth->ndev);
	__netdev_watchकरोg_up(ugeth->ndev);
पूर्ण

/* Called every समय the controller might need to be made
 * aware of new link state.  The PHY code conveys this
 * inक्रमmation through variables in the ugeth काष्ठाure, and this
 * function converts those variables पूर्णांकo the appropriate
 * रेजिस्टर values, and can bring करोwn the device अगर needed.
 */

अटल व्योम adjust_link(काष्ठा net_device *dev)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(dev);
	काष्ठा ucc_geth __iomem *ug_regs;
	काष्ठा ucc_fast __iomem *uf_regs;
	काष्ठा phy_device *phydev = ugeth->phydev;
	पूर्णांक new_state = 0;

	ug_regs = ugeth->ug_regs;
	uf_regs = ugeth->uccf->uf_regs;

	अगर (phydev->link) अणु
		u32 tempval = in_be32(&ug_regs->maccfg2);
		u32 upsmr = in_be32(&uf_regs->upsmr);
		/* Now we make sure that we can be in full duplex mode.
		 * If not, we operate in half-duplex mode. */
		अगर (phydev->duplex != ugeth->oldduplex) अणु
			new_state = 1;
			अगर (!(phydev->duplex))
				tempval &= ~(MACCFG2_FDX);
			अन्यथा
				tempval |= MACCFG2_FDX;
			ugeth->oldduplex = phydev->duplex;
		पूर्ण

		अगर (phydev->speed != ugeth->oldspeed) अणु
			new_state = 1;
			चयन (phydev->speed) अणु
			हाल SPEED_1000:
				tempval = ((tempval &
					    ~(MACCFG2_INTERFACE_MODE_MASK)) |
					    MACCFG2_INTERFACE_MODE_BYTE);
				अवरोध;
			हाल SPEED_100:
			हाल SPEED_10:
				tempval = ((tempval &
					    ~(MACCFG2_INTERFACE_MODE_MASK)) |
					    MACCFG2_INTERFACE_MODE_NIBBLE);
				/* अगर reduced mode, re-set UPSMR.R10M */
				अगर ((ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RMII) ||
				    (ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII) ||
				    (ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_ID) ||
				    (ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_RXID) ||
				    (ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RGMII_TXID) ||
				    (ugeth->phy_पूर्णांकerface == PHY_INTERFACE_MODE_RTBI)) अणु
					अगर (phydev->speed == SPEED_10)
						upsmr |= UCC_GETH_UPSMR_R10M;
					अन्यथा
						upsmr &= ~UCC_GETH_UPSMR_R10M;
				पूर्ण
				अवरोध;
			शेष:
				अगर (netअगर_msg_link(ugeth))
					pr_warn(
						"%s: Ack!  Speed (%d) is not 10/100/1000!",
						dev->name, phydev->speed);
				अवरोध;
			पूर्ण
			ugeth->oldspeed = phydev->speed;
		पूर्ण

		अगर (!ugeth->oldlink) अणु
			new_state = 1;
			ugeth->oldlink = 1;
		पूर्ण

		अगर (new_state) अणु
			/*
			 * To change the MAC configuration we need to disable
			 * the controller. To करो so, we have to either grab
			 * ugeth->lock, which is a bad idea since 'graceful
			 * stop' commands might take quite a जबतक, or we can
			 * quiesce driver's activity.
			 */
			ugeth_quiesce(ugeth);
			ugeth_disable(ugeth, COMM_सूची_RX_AND_TX);

			out_be32(&ug_regs->maccfg2, tempval);
			out_be32(&uf_regs->upsmr, upsmr);

			ugeth_enable(ugeth, COMM_सूची_RX_AND_TX);
			ugeth_activate(ugeth);
		पूर्ण
	पूर्ण अन्यथा अगर (ugeth->oldlink) अणु
			new_state = 1;
			ugeth->oldlink = 0;
			ugeth->oldspeed = 0;
			ugeth->oldduplex = -1;
	पूर्ण

	अगर (new_state && netअगर_msg_link(ugeth))
		phy_prपूर्णांक_status(phydev);
पूर्ण

/* Initialize TBI PHY पूर्णांकerface क्रम communicating with the
 * SERDES lynx PHY on the chip.  We communicate with this PHY
 * through the MDIO bus on each controller, treating it as a
 * "normal" PHY at the address found in the UTBIPA रेजिस्टर.  We assume
 * that the UTBIPA रेजिस्टर is valid.  Either the MDIO bus code will set
 * it to a value that करोesn't conflict with other PHYs on the bus, or the
 * value करोesn't matter, as there are no other PHYs on the bus.
 */
अटल व्योम uec_configure_serdes(काष्ठा net_device *dev)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(dev);
	काष्ठा ucc_geth_info *ug_info = ugeth->ug_info;
	काष्ठा phy_device *tbiphy;

	अगर (!ug_info->tbi_node) अणु
		dev_warn(&dev->dev, "SGMII mode requires that the device "
			"tree specify a tbi-handle\n");
		वापस;
	पूर्ण

	tbiphy = of_phy_find_device(ug_info->tbi_node);
	अगर (!tbiphy) अणु
		dev_err(&dev->dev, "error: Could not get TBI device\n");
		वापस;
	पूर्ण

	/*
	 * If the link is alपढ़ोy up, we must alपढ़ोy be ok, and करोn't need to
	 * configure and reset the TBI<->SerDes link.  Maybe U-Boot configured
	 * everything क्रम us?  Resetting it takes the link करोwn and requires
	 * several seconds क्रम it to come back.
	 */
	अगर (phy_पढ़ो(tbiphy, ENET_TBI_MII_SR) & TBISR_LSTATUS) अणु
		put_device(&tbiphy->mdio.dev);
		वापस;
	पूर्ण

	/* Single clk mode, mii mode off(क्रम serdes communication) */
	phy_ग_लिखो(tbiphy, ENET_TBI_MII_ANA, TBIANA_SETTINGS);

	phy_ग_लिखो(tbiphy, ENET_TBI_MII_TBICON, TBICON_CLK_SELECT);

	phy_ग_लिखो(tbiphy, ENET_TBI_MII_CR, TBICR_SETTINGS);

	put_device(&tbiphy->mdio.dev);
पूर्ण

/* Configure the PHY क्रम dev.
 * वापसs 0 अगर success.  -1 अगर failure
 */
अटल पूर्णांक init_phy(काष्ठा net_device *dev)
अणु
	काष्ठा ucc_geth_निजी *priv = netdev_priv(dev);
	काष्ठा ucc_geth_info *ug_info = priv->ug_info;
	काष्ठा phy_device *phydev;

	priv->oldlink = 0;
	priv->oldspeed = 0;
	priv->oldduplex = -1;

	phydev = of_phy_connect(dev, ug_info->phy_node, &adjust_link, 0,
				priv->phy_पूर्णांकerface);
	अगर (!phydev) अणु
		dev_err(&dev->dev, "Could not attach to PHY\n");
		वापस -ENODEV;
	पूर्ण

	अगर (priv->phy_पूर्णांकerface == PHY_INTERFACE_MODE_SGMII)
		uec_configure_serdes(dev);

	phy_set_max_speed(phydev, priv->max_speed);

	priv->phydev = phydev;

	वापस 0;
पूर्ण

अटल व्योम ugeth_dump_regs(काष्ठा ucc_geth_निजी *ugeth)
अणु
#अगर_घोषित DEBUG
	ucc_fast_dump_regs(ugeth->uccf);
	dump_regs(ugeth);
	dump_bds(ugeth);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक ugeth_82xx_filtering_clear_all_addr_in_hash(काष्ठा ucc_geth_निजी *
						       ugeth,
						       क्रमागत enet_addr_type
						       enet_addr_type)
अणु
	काष्ठा ucc_geth_82xx_address_filtering_pram __iomem *p_82xx_addr_filt;
	काष्ठा ucc_fast_निजी *uccf;
	क्रमागत comm_dir comm_dir;
	काष्ठा list_head *p_lh;
	u16 i, num;
	u32 __iomem *addr_h;
	u32 __iomem *addr_l;
	u8 *p_counter;

	uccf = ugeth->uccf;

	p_82xx_addr_filt =
	    (काष्ठा ucc_geth_82xx_address_filtering_pram __iomem *)
	    ugeth->p_rx_glbl_pram->addressfiltering;

	अगर (enet_addr_type == ENET_ADDR_TYPE_GROUP) अणु
		addr_h = &(p_82xx_addr_filt->gaddr_h);
		addr_l = &(p_82xx_addr_filt->gaddr_l);
		p_lh = &ugeth->group_hash_q;
		p_counter = &(ugeth->numGroupAddrInHash);
	पूर्ण अन्यथा अगर (enet_addr_type == ENET_ADDR_TYPE_INDIVIDUAL) अणु
		addr_h = &(p_82xx_addr_filt->iaddr_h);
		addr_l = &(p_82xx_addr_filt->iaddr_l);
		p_lh = &ugeth->ind_hash_q;
		p_counter = &(ugeth->numIndAddrInHash);
	पूर्ण अन्यथा
		वापस -EINVAL;

	comm_dir = 0;
	अगर (uccf->enabled_tx)
		comm_dir |= COMM_सूची_TX;
	अगर (uccf->enabled_rx)
		comm_dir |= COMM_सूची_RX;
	अगर (comm_dir)
		ugeth_disable(ugeth, comm_dir);

	/* Clear the hash table. */
	out_be32(addr_h, 0x00000000);
	out_be32(addr_l, 0x00000000);

	अगर (!p_lh)
		वापस 0;

	num = *p_counter;

	/* Delete all reमुख्यing CQ elements */
	क्रम (i = 0; i < num; i++)
		put_enet_addr_container(ENET_ADDR_CONT_ENTRY(dequeue(p_lh)));

	*p_counter = 0;

	अगर (comm_dir)
		ugeth_enable(ugeth, comm_dir);

	वापस 0;
पूर्ण

अटल पूर्णांक ugeth_82xx_filtering_clear_addr_in_paddr(काष्ठा ucc_geth_निजी *ugeth,
						    u8 paddr_num)
अणु
	ugeth->indAddrRegUsed[paddr_num] = 0; /* mark this paddr as not used */
	वापस hw_clear_addr_in_paddr(ugeth, paddr_num);/* clear in hardware */
पूर्ण

अटल व्योम ucc_geth_मुक्त_rx(काष्ठा ucc_geth_निजी *ugeth)
अणु
	काष्ठा ucc_geth_info *ug_info;
	काष्ठा ucc_fast_info *uf_info;
	u16 i, j;
	u8 __iomem *bd;


	ug_info = ugeth->ug_info;
	uf_info = &ug_info->uf_info;

	क्रम (i = 0; i < ucc_geth_rx_queues(ugeth->ug_info); i++) अणु
		अगर (ugeth->p_rx_bd_ring[i]) अणु
			/* Return existing data buffers in ring */
			bd = ugeth->p_rx_bd_ring[i];
			क्रम (j = 0; j < ugeth->ug_info->bdRingLenRx[i]; j++) अणु
				अगर (ugeth->rx_skbuff[i][j]) अणु
					dma_unmap_single(ugeth->dev,
						in_be32(&((काष्ठा qe_bd __iomem *)bd)->buf),
						ugeth->ug_info->
						uf_info.max_rx_buf_length +
						UCC_GETH_RX_DATA_BUF_ALIGNMENT,
						DMA_FROM_DEVICE);
					dev_kमुक्त_skb_any(
						ugeth->rx_skbuff[i][j]);
					ugeth->rx_skbuff[i][j] = शून्य;
				पूर्ण
				bd += माप(काष्ठा qe_bd);
			पूर्ण

			kमुक्त(ugeth->rx_skbuff[i]);

			kमुक्त(ugeth->p_rx_bd_ring[i]);
			ugeth->p_rx_bd_ring[i] = शून्य;
		पूर्ण
	पूर्ण

पूर्ण

अटल व्योम ucc_geth_मुक्त_tx(काष्ठा ucc_geth_निजी *ugeth)
अणु
	काष्ठा ucc_geth_info *ug_info;
	काष्ठा ucc_fast_info *uf_info;
	u16 i, j;
	u8 __iomem *bd;

	netdev_reset_queue(ugeth->ndev);

	ug_info = ugeth->ug_info;
	uf_info = &ug_info->uf_info;

	क्रम (i = 0; i < ucc_geth_tx_queues(ugeth->ug_info); i++) अणु
		bd = ugeth->p_tx_bd_ring[i];
		अगर (!bd)
			जारी;
		क्रम (j = 0; j < ugeth->ug_info->bdRingLenTx[i]; j++) अणु
			अगर (ugeth->tx_skbuff[i][j]) अणु
				dma_unmap_single(ugeth->dev,
						 in_be32(&((काष्ठा qe_bd __iomem *)bd)->buf),
						 (in_be32((u32 __iomem *)bd) &
						  BD_LENGTH_MASK),
						 DMA_TO_DEVICE);
				dev_kमुक्त_skb_any(ugeth->tx_skbuff[i][j]);
				ugeth->tx_skbuff[i][j] = शून्य;
			पूर्ण
		पूर्ण

		kमुक्त(ugeth->tx_skbuff[i]);

		kमुक्त(ugeth->p_tx_bd_ring[i]);
		ugeth->p_tx_bd_ring[i] = शून्य;
	पूर्ण

पूर्ण

अटल व्योम ucc_geth_memclean(काष्ठा ucc_geth_निजी *ugeth)
अणु
	अगर (!ugeth)
		वापस;

	अगर (ugeth->uccf) अणु
		ucc_fast_मुक्त(ugeth->uccf);
		ugeth->uccf = शून्य;
	पूर्ण

	qe_muram_मुक्त_addr(ugeth->p_thपढ़ो_data_tx);
	ugeth->p_thपढ़ो_data_tx = शून्य;

	qe_muram_मुक्त_addr(ugeth->p_thपढ़ो_data_rx);
	ugeth->p_thपढ़ो_data_rx = शून्य;

	qe_muram_मुक्त_addr(ugeth->p_exf_glbl_param);
	ugeth->p_exf_glbl_param = शून्य;

	qe_muram_मुक्त_addr(ugeth->p_rx_glbl_pram);
	ugeth->p_rx_glbl_pram = शून्य;

	qe_muram_मुक्त_addr(ugeth->p_tx_glbl_pram);
	ugeth->p_tx_glbl_pram = शून्य;

	qe_muram_मुक्त_addr(ugeth->p_send_q_mem_reg);
	ugeth->p_send_q_mem_reg = शून्य;

	qe_muram_मुक्त_addr(ugeth->p_scheduler);
	ugeth->p_scheduler = शून्य;

	qe_muram_मुक्त_addr(ugeth->p_tx_fw_statistics_pram);
	ugeth->p_tx_fw_statistics_pram = शून्य;

	qe_muram_मुक्त_addr(ugeth->p_rx_fw_statistics_pram);
	ugeth->p_rx_fw_statistics_pram = शून्य;

	qe_muram_मुक्त_addr(ugeth->p_rx_irq_coalescing_tbl);
	ugeth->p_rx_irq_coalescing_tbl = शून्य;

	qe_muram_मुक्त_addr(ugeth->p_rx_bd_qs_tbl);
	ugeth->p_rx_bd_qs_tbl = शून्य;

	अगर (ugeth->p_init_enet_param_shaकरोw) अणु
		वापस_init_enet_entries(ugeth,
					 &(ugeth->p_init_enet_param_shaकरोw->
					   rxthपढ़ो[0]),
					 ENET_INIT_PARAM_MAX_ENTRIES_RX,
					 ugeth->ug_info->riscRx, 1);
		वापस_init_enet_entries(ugeth,
					 &(ugeth->p_init_enet_param_shaकरोw->
					   txthपढ़ो[0]),
					 ENET_INIT_PARAM_MAX_ENTRIES_TX,
					 ugeth->ug_info->riscTx, 0);
		kमुक्त(ugeth->p_init_enet_param_shaकरोw);
		ugeth->p_init_enet_param_shaकरोw = शून्य;
	पूर्ण
	ucc_geth_मुक्त_tx(ugeth);
	ucc_geth_मुक्त_rx(ugeth);
	जबतक (!list_empty(&ugeth->group_hash_q))
		put_enet_addr_container(ENET_ADDR_CONT_ENTRY
					(dequeue(&ugeth->group_hash_q)));
	जबतक (!list_empty(&ugeth->ind_hash_q))
		put_enet_addr_container(ENET_ADDR_CONT_ENTRY
					(dequeue(&ugeth->ind_hash_q)));
	अगर (ugeth->ug_regs) अणु
		iounmap(ugeth->ug_regs);
		ugeth->ug_regs = शून्य;
	पूर्ण
पूर्ण

अटल व्योम ucc_geth_set_multi(काष्ठा net_device *dev)
अणु
	काष्ठा ucc_geth_निजी *ugeth;
	काष्ठा netdev_hw_addr *ha;
	काष्ठा ucc_fast __iomem *uf_regs;
	काष्ठा ucc_geth_82xx_address_filtering_pram __iomem *p_82xx_addr_filt;

	ugeth = netdev_priv(dev);

	uf_regs = ugeth->uccf->uf_regs;

	अगर (dev->flags & IFF_PROMISC) अणु
		setbits32(&uf_regs->upsmr, UCC_GETH_UPSMR_PRO);
	पूर्ण अन्यथा अणु
		clrbits32(&uf_regs->upsmr, UCC_GETH_UPSMR_PRO);

		p_82xx_addr_filt =
		    (काष्ठा ucc_geth_82xx_address_filtering_pram __iomem *) ugeth->
		    p_rx_glbl_pram->addressfiltering;

		अगर (dev->flags & IFF_ALLMULTI) अणु
			/* Catch all multicast addresses, so set the
			 * filter to all 1's.
			 */
			out_be32(&p_82xx_addr_filt->gaddr_h, 0xffffffff);
			out_be32(&p_82xx_addr_filt->gaddr_l, 0xffffffff);
		पूर्ण अन्यथा अणु
			/* Clear filter and add the addresses in the list.
			 */
			out_be32(&p_82xx_addr_filt->gaddr_h, 0x0);
			out_be32(&p_82xx_addr_filt->gaddr_l, 0x0);

			netdev_क्रम_each_mc_addr(ha, dev) अणु
				/* Ask CPM to run CRC and set bit in
				 * filter mask.
				 */
				hw_add_addr_in_hash(ugeth, ha->addr);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ucc_geth_stop(काष्ठा ucc_geth_निजी *ugeth)
अणु
	काष्ठा ucc_geth __iomem *ug_regs = ugeth->ug_regs;
	काष्ठा phy_device *phydev = ugeth->phydev;

	ugeth_vdbg("%s: IN", __func__);

	/*
	 * Tell the kernel the link is करोwn.
	 * Must be करोne beक्रमe disabling the controller
	 * or deadlock may happen.
	 */
	phy_stop(phydev);

	/* Disable the controller */
	ugeth_disable(ugeth, COMM_सूची_RX_AND_TX);

	/* Mask all पूर्णांकerrupts */
	out_be32(ugeth->uccf->p_uccm, 0x00000000);

	/* Clear all पूर्णांकerrupts */
	out_be32(ugeth->uccf->p_ucce, 0xffffffff);

	/* Disable Rx and Tx */
	clrbits32(&ug_regs->maccfg1, MACCFG1_ENABLE_RX | MACCFG1_ENABLE_TX);

	ucc_geth_memclean(ugeth);
पूर्ण

अटल पूर्णांक ucc_काष्ठा_init(काष्ठा ucc_geth_निजी *ugeth)
अणु
	काष्ठा ucc_geth_info *ug_info;
	काष्ठा ucc_fast_info *uf_info;
	पूर्णांक i;

	ug_info = ugeth->ug_info;
	uf_info = &ug_info->uf_info;

	/* Rx BD lengths */
	क्रम (i = 0; i < ucc_geth_rx_queues(ug_info); i++) अणु
		अगर ((ug_info->bdRingLenRx[i] < UCC_GETH_RX_BD_RING_SIZE_MIN) ||
		    (ug_info->bdRingLenRx[i] %
		     UCC_GETH_RX_BD_RING_SIZE_ALIGNMENT)) अणु
			अगर (netअगर_msg_probe(ugeth))
				pr_err("Rx BD ring length must be multiple of 4, no smaller than 8\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* Tx BD lengths */
	क्रम (i = 0; i < ucc_geth_tx_queues(ug_info); i++) अणु
		अगर (ug_info->bdRingLenTx[i] < UCC_GETH_TX_BD_RING_SIZE_MIN) अणु
			अगर (netअगर_msg_probe(ugeth))
				pr_err("Tx BD ring length must be no smaller than 2\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* mrblr */
	अगर ((uf_info->max_rx_buf_length == 0) ||
	    (uf_info->max_rx_buf_length % UCC_GETH_MRBLR_ALIGNMENT)) अणु
		अगर (netअगर_msg_probe(ugeth))
			pr_err("max_rx_buf_length must be non-zero multiple of 128\n");
		वापस -EINVAL;
	पूर्ण

	/* num Tx queues */
	अगर (ucc_geth_tx_queues(ug_info) > NUM_TX_QUEUES) अणु
		अगर (netअगर_msg_probe(ugeth))
			pr_err("number of tx queues too large\n");
		वापस -EINVAL;
	पूर्ण

	/* num Rx queues */
	अगर (ucc_geth_rx_queues(ug_info) > NUM_RX_QUEUES) अणु
		अगर (netअगर_msg_probe(ugeth))
			pr_err("number of rx queues too large\n");
		वापस -EINVAL;
	पूर्ण

	/* l2qt */
	क्रम (i = 0; i < UCC_GETH_VLAN_PRIORITY_MAX; i++) अणु
		अगर (ug_info->l2qt[i] >= ucc_geth_rx_queues(ug_info)) अणु
			अगर (netअगर_msg_probe(ugeth))
				pr_err("VLAN priority table entry must not be larger than number of Rx queues\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* l3qt */
	क्रम (i = 0; i < UCC_GETH_IP_PRIORITY_MAX; i++) अणु
		अगर (ug_info->l3qt[i] >= ucc_geth_rx_queues(ug_info)) अणु
			अगर (netअगर_msg_probe(ugeth))
				pr_err("IP priority table entry must not be larger than number of Rx queues\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (ug_info->cam && !ug_info->ecamptr) अणु
		अगर (netअगर_msg_probe(ugeth))
			pr_err("If cam mode is chosen, must supply cam ptr\n");
		वापस -EINVAL;
	पूर्ण

	अगर ((ug_info->numStationAddresses !=
	     UCC_GETH_NUM_OF_STATION_ADDRESSES_1) &&
	    ug_info->rxExtendedFiltering) अणु
		अगर (netअगर_msg_probe(ugeth))
			pr_err("Number of station addresses greater than 1 not allowed in extended parsing mode\n");
		वापस -EINVAL;
	पूर्ण

	/* Generate uccm_mask क्रम receive */
	uf_info->uccm_mask = ug_info->eventRegMask & UCCE_OTHER;/* Errors */
	क्रम (i = 0; i < ucc_geth_rx_queues(ug_info); i++)
		uf_info->uccm_mask |= (UCC_GETH_UCCE_RXF0 << i);

	क्रम (i = 0; i < ucc_geth_tx_queues(ug_info); i++)
		uf_info->uccm_mask |= (UCC_GETH_UCCE_TXB0 << i);
	/* Initialize the general fast UCC block. */
	अगर (ucc_fast_init(uf_info, &ugeth->uccf)) अणु
		अगर (netअगर_msg_probe(ugeth))
			pr_err("Failed to init uccf\n");
		वापस -ENOMEM;
	पूर्ण

	/* पढ़ो the number of risc engines, update the riscTx and riscRx
	 * अगर there are 4 riscs in QE
	 */
	अगर (qe_get_num_of_risc() == 4) अणु
		ug_info->riscTx = QE_RISC_ALLOCATION_FOUR_RISCS;
		ug_info->riscRx = QE_RISC_ALLOCATION_FOUR_RISCS;
	पूर्ण

	ugeth->ug_regs = ioremap(uf_info->regs, माप(*ugeth->ug_regs));
	अगर (!ugeth->ug_regs) अणु
		अगर (netअगर_msg_probe(ugeth))
			pr_err("Failed to ioremap regs\n");
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ucc_geth_alloc_tx(काष्ठा ucc_geth_निजी *ugeth)
अणु
	काष्ठा ucc_geth_info *ug_info;
	काष्ठा ucc_fast_info *uf_info;
	पूर्णांक length;
	u16 i, j;
	u8 __iomem *bd;

	ug_info = ugeth->ug_info;
	uf_info = &ug_info->uf_info;

	/* Allocate Tx bds */
	क्रम (j = 0; j < ucc_geth_tx_queues(ug_info); j++) अणु
		u32 align = max(UCC_GETH_TX_BD_RING_ALIGNMENT,
				UCC_GETH_TX_BD_RING_SIZE_MEMORY_ALIGNMENT);
		u32 alloc;

		length = ug_info->bdRingLenTx[j] * माप(काष्ठा qe_bd);
		alloc = round_up(length, align);
		alloc = roundup_घात_of_two(alloc);

		ugeth->p_tx_bd_ring[j] = kदो_स्मृति(alloc, GFP_KERNEL);

		अगर (!ugeth->p_tx_bd_ring[j]) अणु
			अगर (netअगर_msg_अगरup(ugeth))
				pr_err("Can not allocate memory for Tx bd rings\n");
			वापस -ENOMEM;
		पूर्ण
		/* Zero unused end of bd ring, according to spec */
		स_रखो(ugeth->p_tx_bd_ring[j] + length, 0, alloc - length);
	पूर्ण

	/* Init Tx bds */
	क्रम (j = 0; j < ucc_geth_tx_queues(ug_info); j++) अणु
		/* Setup the skbuff rings */
		ugeth->tx_skbuff[j] =
			kसुस्मृति(ugeth->ug_info->bdRingLenTx[j],
				माप(काष्ठा sk_buff *), GFP_KERNEL);

		अगर (ugeth->tx_skbuff[j] == शून्य) अणु
			अगर (netअगर_msg_अगरup(ugeth))
				pr_err("Could not allocate tx_skbuff\n");
			वापस -ENOMEM;
		पूर्ण

		ugeth->skb_curtx[j] = ugeth->skb_dirtytx[j] = 0;
		bd = ugeth->confBd[j] = ugeth->txBd[j] = ugeth->p_tx_bd_ring[j];
		क्रम (i = 0; i < ug_info->bdRingLenTx[j]; i++) अणु
			/* clear bd buffer */
			out_be32(&((काष्ठा qe_bd __iomem *)bd)->buf, 0);
			/* set bd status and length */
			out_be32((u32 __iomem *)bd, 0);
			bd += माप(काष्ठा qe_bd);
		पूर्ण
		bd -= माप(काष्ठा qe_bd);
		/* set bd status and length */
		out_be32((u32 __iomem *)bd, T_W); /* क्रम last BD set Wrap bit */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ucc_geth_alloc_rx(काष्ठा ucc_geth_निजी *ugeth)
अणु
	काष्ठा ucc_geth_info *ug_info;
	काष्ठा ucc_fast_info *uf_info;
	पूर्णांक length;
	u16 i, j;
	u8 __iomem *bd;

	ug_info = ugeth->ug_info;
	uf_info = &ug_info->uf_info;

	/* Allocate Rx bds */
	क्रम (j = 0; j < ucc_geth_rx_queues(ug_info); j++) अणु
		u32 align = UCC_GETH_RX_BD_RING_ALIGNMENT;
		u32 alloc;

		length = ug_info->bdRingLenRx[j] * माप(काष्ठा qe_bd);
		alloc = round_up(length, align);
		alloc = roundup_घात_of_two(alloc);

		ugeth->p_rx_bd_ring[j] = kदो_स्मृति(alloc, GFP_KERNEL);
		अगर (!ugeth->p_rx_bd_ring[j]) अणु
			अगर (netअगर_msg_अगरup(ugeth))
				pr_err("Can not allocate memory for Rx bd rings\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	/* Init Rx bds */
	क्रम (j = 0; j < ucc_geth_rx_queues(ug_info); j++) अणु
		/* Setup the skbuff rings */
		ugeth->rx_skbuff[j] =
			kसुस्मृति(ugeth->ug_info->bdRingLenRx[j],
				माप(काष्ठा sk_buff *), GFP_KERNEL);

		अगर (ugeth->rx_skbuff[j] == शून्य) अणु
			अगर (netअगर_msg_अगरup(ugeth))
				pr_err("Could not allocate rx_skbuff\n");
			वापस -ENOMEM;
		पूर्ण

		ugeth->skb_currx[j] = 0;
		bd = ugeth->rxBd[j] = ugeth->p_rx_bd_ring[j];
		क्रम (i = 0; i < ug_info->bdRingLenRx[j]; i++) अणु
			/* set bd status and length */
			out_be32((u32 __iomem *)bd, R_I);
			/* clear bd buffer */
			out_be32(&((काष्ठा qe_bd __iomem *)bd)->buf, 0);
			bd += माप(काष्ठा qe_bd);
		पूर्ण
		bd -= माप(काष्ठा qe_bd);
		/* set bd status and length */
		out_be32((u32 __iomem *)bd, R_W); /* क्रम last BD set Wrap bit */
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ucc_geth_startup(काष्ठा ucc_geth_निजी *ugeth)
अणु
	काष्ठा ucc_geth_82xx_address_filtering_pram __iomem *p_82xx_addr_filt;
	काष्ठा ucc_geth_init_pram __iomem *p_init_enet_pram;
	काष्ठा ucc_fast_निजी *uccf;
	काष्ठा ucc_geth_info *ug_info;
	काष्ठा ucc_fast_info *uf_info;
	काष्ठा ucc_fast __iomem *uf_regs;
	काष्ठा ucc_geth __iomem *ug_regs;
	पूर्णांक ret_val = -EINVAL;
	u32 remoder = UCC_GETH_REMODER_INIT;
	u32 init_enet_pram_offset, cecr_subblock, command;
	u32 अगरstat, i, j, size, l2qt, l3qt;
	u16 temoder = UCC_GETH_TEMODER_INIT;
	u8 function_code = 0;
	u8 __iomem *endOfRing;
	u8 numThपढ़ोsRxNumerical, numThपढ़ोsTxNumerical;
	s32 rx_glbl_pram_offset, tx_glbl_pram_offset;

	ugeth_vdbg("%s: IN", __func__);
	uccf = ugeth->uccf;
	ug_info = ugeth->ug_info;
	uf_info = &ug_info->uf_info;
	uf_regs = uccf->uf_regs;
	ug_regs = ugeth->ug_regs;

	numThपढ़ोsRxNumerical = ucc_geth_thपढ़ो_count(ug_info->numThपढ़ोsRx);
	अगर (!numThपढ़ोsRxNumerical) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("Bad number of Rx threads value\n");
		वापस -EINVAL;
	पूर्ण

	numThपढ़ोsTxNumerical = ucc_geth_thपढ़ो_count(ug_info->numThपढ़ोsTx);
	अगर (!numThपढ़ोsTxNumerical) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("Bad number of Tx threads value\n");
		वापस -EINVAL;
	पूर्ण

	/* Calculate rx_extended_features */
	ugeth->rx_non_dynamic_extended_features = ug_info->ipCheckSumCheck ||
	    ug_info->ipAddressAlignment ||
	    (ug_info->numStationAddresses !=
	     UCC_GETH_NUM_OF_STATION_ADDRESSES_1);

	ugeth->rx_extended_features = ugeth->rx_non_dynamic_extended_features ||
		(ug_info->vlanOperationTagged != UCC_GETH_VLAN_OPERATION_TAGGED_NOP) ||
		(ug_info->vlanOperationNonTagged !=
		 UCC_GETH_VLAN_OPERATION_NON_TAGGED_NOP);

	init_शेष_reg_vals(&uf_regs->upsmr,
			      &ug_regs->maccfg1, &ug_regs->maccfg2);

	/*                    Set UPSMR                      */
	/* For more details see the hardware spec.           */
	init_rx_parameters(ug_info->bro,
			   ug_info->rsh, ug_info->pro, &uf_regs->upsmr);

	/* We're going to ignore other रेजिस्टरs क्रम now, */
	/* except as needed to get up and running         */

	/*                    Set MACCFG1                    */
	/* For more details see the hardware spec.           */
	init_flow_control_params(ug_info->aufc,
				 ug_info->receiveFlowControl,
				 ug_info->transmitFlowControl,
				 ug_info->छोड़ोPeriod,
				 ug_info->extensionField,
				 &uf_regs->upsmr,
				 &ug_regs->uempr, &ug_regs->maccfg1);

	setbits32(&ug_regs->maccfg1, MACCFG1_ENABLE_RX | MACCFG1_ENABLE_TX);

	/*                    Set IPGIFG                     */
	/* For more details see the hardware spec.           */
	ret_val = init_पूर्णांकer_frame_gap_params(ug_info->nonBackToBackIfgPart1,
					      ug_info->nonBackToBackIfgPart2,
					      ug_info->
					      miminumInterFrameGapEnक्रमcement,
					      ug_info->backToBackInterFrameGap,
					      &ug_regs->ipgअगरg);
	अगर (ret_val != 0) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("IPGIFG initialization parameter too large\n");
		वापस ret_val;
	पूर्ण

	/*                    Set HAFDUP                     */
	/* For more details see the hardware spec.           */
	ret_val = init_half_duplex_params(ug_info->altBeb,
					  ug_info->backPressureNoBackoff,
					  ug_info->noBackoff,
					  ug_info->excessDefer,
					  ug_info->altBebTruncation,
					  ug_info->maxRetransmission,
					  ug_info->collisionWinकरोw,
					  &ug_regs->hafdup);
	अगर (ret_val != 0) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("Half Duplex initialization parameter too large\n");
		वापस ret_val;
	पूर्ण

	/*                    Set IFSTAT                     */
	/* For more details see the hardware spec.           */
	/* Read only - resets upon पढ़ो                      */
	अगरstat = in_be32(&ug_regs->अगरstat);

	/*                    Clear UEMPR                    */
	/* For more details see the hardware spec.           */
	out_be32(&ug_regs->uempr, 0);

	/*                    Set UESCR                      */
	/* For more details see the hardware spec.           */
	init_hw_statistics_gathering_mode((ug_info->statisticsMode &
				UCC_GETH_STATISTICS_GATHERING_MODE_HARDWARE),
				0, &uf_regs->upsmr, &ug_regs->uescr);

	ret_val = ucc_geth_alloc_tx(ugeth);
	अगर (ret_val != 0)
		वापस ret_val;

	ret_val = ucc_geth_alloc_rx(ugeth);
	अगर (ret_val != 0)
		वापस ret_val;

	/*
	 * Global PRAM
	 */
	/* Tx global PRAM */
	/* Allocate global tx parameter RAM page */
	tx_glbl_pram_offset =
	    qe_muram_alloc(माप(काष्ठा ucc_geth_tx_global_pram),
			   UCC_GETH_TX_GLOBAL_PRAM_ALIGNMENT);
	अगर (tx_glbl_pram_offset < 0) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("Can not allocate DPRAM memory for p_tx_glbl_pram\n");
		वापस -ENOMEM;
	पूर्ण
	ugeth->p_tx_glbl_pram = qe_muram_addr(tx_glbl_pram_offset);
	/* Fill global PRAM */

	/* TQPTR */
	/* Size varies with number of Tx thपढ़ोs */
	ugeth->thपढ़ो_dat_tx_offset =
	    qe_muram_alloc(numThपढ़ोsTxNumerical *
			   माप(काष्ठा ucc_geth_thपढ़ो_data_tx) +
			   32 * (numThपढ़ोsTxNumerical == 1),
			   UCC_GETH_THREAD_DATA_ALIGNMENT);
	अगर (IS_ERR_VALUE(ugeth->thपढ़ो_dat_tx_offset)) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("Can not allocate DPRAM memory for p_thread_data_tx\n");
		वापस -ENOMEM;
	पूर्ण

	ugeth->p_thपढ़ो_data_tx =
	    (काष्ठा ucc_geth_thपढ़ो_data_tx __iomem *) qe_muram_addr(ugeth->
							thपढ़ो_dat_tx_offset);
	out_be32(&ugeth->p_tx_glbl_pram->tqptr, ugeth->thपढ़ो_dat_tx_offset);

	/* vtagtable */
	क्रम (i = 0; i < UCC_GETH_TX_VTAG_TABLE_ENTRY_MAX; i++)
		out_be32(&ugeth->p_tx_glbl_pram->vtagtable[i],
			 ug_info->vtagtable[i]);

	/* iphoffset */
	क्रम (i = 0; i < TX_IP_OFFSET_ENTRY_MAX; i++)
		out_8(&ugeth->p_tx_glbl_pram->iphoffset[i],
				ug_info->iphoffset[i]);

	/* SQPTR */
	/* Size varies with number of Tx queues */
	ugeth->send_q_mem_reg_offset =
	    qe_muram_alloc(ucc_geth_tx_queues(ug_info) *
			   माप(काष्ठा ucc_geth_send_queue_qd),
			   UCC_GETH_SEND_QUEUE_QUEUE_DESCRIPTOR_ALIGNMENT);
	अगर (IS_ERR_VALUE(ugeth->send_q_mem_reg_offset)) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("Can not allocate DPRAM memory for p_send_q_mem_reg\n");
		वापस -ENOMEM;
	पूर्ण

	ugeth->p_send_q_mem_reg =
	    (काष्ठा ucc_geth_send_queue_mem_region __iomem *) qe_muram_addr(ugeth->
			send_q_mem_reg_offset);
	out_be32(&ugeth->p_tx_glbl_pram->sqptr, ugeth->send_q_mem_reg_offset);

	/* Setup the table */
	/* Assume BD rings are alपढ़ोy established */
	क्रम (i = 0; i < ucc_geth_tx_queues(ug_info); i++) अणु
		endOfRing =
		    ugeth->p_tx_bd_ring[i] + (ug_info->bdRingLenTx[i] -
					      1) * माप(काष्ठा qe_bd);
		out_be32(&ugeth->p_send_q_mem_reg->sqqd[i].bd_ring_base,
			 (u32) virt_to_phys(ugeth->p_tx_bd_ring[i]));
		out_be32(&ugeth->p_send_q_mem_reg->sqqd[i].
			 last_bd_completed_address,
			 (u32) virt_to_phys(endOfRing));
	पूर्ण

	/* schedulerbasepoपूर्णांकer */

	अगर (ucc_geth_tx_queues(ug_info) > 1) अणु
	/* scheduler exists only अगर more than 1 tx queue */
		ugeth->scheduler_offset =
		    qe_muram_alloc(माप(काष्ठा ucc_geth_scheduler),
				   UCC_GETH_SCHEDULER_ALIGNMENT);
		अगर (IS_ERR_VALUE(ugeth->scheduler_offset)) अणु
			अगर (netअगर_msg_अगरup(ugeth))
				pr_err("Can not allocate DPRAM memory for p_scheduler\n");
			वापस -ENOMEM;
		पूर्ण

		ugeth->p_scheduler =
		    (काष्ठा ucc_geth_scheduler __iomem *) qe_muram_addr(ugeth->
							   scheduler_offset);
		out_be32(&ugeth->p_tx_glbl_pram->schedulerbasepoपूर्णांकer,
			 ugeth->scheduler_offset);

		/* Set values in scheduler */
		out_be32(&ugeth->p_scheduler->mblपूर्णांकerval,
			 ug_info->mblपूर्णांकerval);
		out_be16(&ugeth->p_scheduler->nortsrbyteसमय,
			 ug_info->nortsrbyteसमय);
		out_8(&ugeth->p_scheduler->fracsiz, ug_info->fracsiz);
		out_8(&ugeth->p_scheduler->strictpriorityq,
				ug_info->strictpriorityq);
		out_8(&ugeth->p_scheduler->txasap, ug_info->txasap);
		out_8(&ugeth->p_scheduler->extrabw, ug_info->extrabw);
		क्रम (i = 0; i < NUM_TX_QUEUES; i++)
			out_8(&ugeth->p_scheduler->weightfactor[i],
			    ug_info->weightfactor[i]);

		/* Set poपूर्णांकers to cpucount रेजिस्टरs in scheduler */
		ugeth->p_cpucount[0] = &(ugeth->p_scheduler->cpucount0);
		ugeth->p_cpucount[1] = &(ugeth->p_scheduler->cpucount1);
		ugeth->p_cpucount[2] = &(ugeth->p_scheduler->cpucount2);
		ugeth->p_cpucount[3] = &(ugeth->p_scheduler->cpucount3);
		ugeth->p_cpucount[4] = &(ugeth->p_scheduler->cpucount4);
		ugeth->p_cpucount[5] = &(ugeth->p_scheduler->cpucount5);
		ugeth->p_cpucount[6] = &(ugeth->p_scheduler->cpucount6);
		ugeth->p_cpucount[7] = &(ugeth->p_scheduler->cpucount7);
	पूर्ण

	/* schedulerbasepoपूर्णांकer */
	/* TxRMON_PTR (statistics) */
	अगर (ug_info->
	    statisticsMode & UCC_GETH_STATISTICS_GATHERING_MODE_FIRMWARE_TX) अणु
		ugeth->tx_fw_statistics_pram_offset =
		    qe_muram_alloc(माप
				   (काष्ठा ucc_geth_tx_firmware_statistics_pram),
				   UCC_GETH_TX_STATISTICS_ALIGNMENT);
		अगर (IS_ERR_VALUE(ugeth->tx_fw_statistics_pram_offset)) अणु
			अगर (netअगर_msg_अगरup(ugeth))
				pr_err("Can not allocate DPRAM memory for p_tx_fw_statistics_pram\n");
			वापस -ENOMEM;
		पूर्ण
		ugeth->p_tx_fw_statistics_pram =
		    (काष्ठा ucc_geth_tx_firmware_statistics_pram __iomem *)
		    qe_muram_addr(ugeth->tx_fw_statistics_pram_offset);
	पूर्ण

	/* temoder */
	/* Alपढ़ोy has speed set */

	अगर (ucc_geth_tx_queues(ug_info) > 1)
		temoder |= TEMODER_SCHEDULER_ENABLE;
	अगर (ug_info->ipCheckSumGenerate)
		temoder |= TEMODER_IP_CHECKSUM_GENERATE;
	temoder |= ((ucc_geth_tx_queues(ug_info) - 1) << TEMODER_NUM_OF_QUEUES_SHIFT);
	out_be16(&ugeth->p_tx_glbl_pram->temoder, temoder);

	/* Function code रेजिस्टर value to be used later */
	function_code = UCC_BMR_BO_BE | UCC_BMR_GBL;
	/* Required क्रम QE */

	/* function code रेजिस्टर */
	out_be32(&ugeth->p_tx_glbl_pram->tstate, ((u32) function_code) << 24);

	/* Rx global PRAM */
	/* Allocate global rx parameter RAM page */
	rx_glbl_pram_offset =
	    qe_muram_alloc(माप(काष्ठा ucc_geth_rx_global_pram),
			   UCC_GETH_RX_GLOBAL_PRAM_ALIGNMENT);
	अगर (rx_glbl_pram_offset < 0) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("Can not allocate DPRAM memory for p_rx_glbl_pram\n");
		वापस -ENOMEM;
	पूर्ण
	ugeth->p_rx_glbl_pram = qe_muram_addr(rx_glbl_pram_offset);
	/* Fill global PRAM */

	/* RQPTR */
	/* Size varies with number of Rx thपढ़ोs */
	ugeth->thपढ़ो_dat_rx_offset =
	    qe_muram_alloc(numThपढ़ोsRxNumerical *
			   माप(काष्ठा ucc_geth_thपढ़ो_data_rx),
			   UCC_GETH_THREAD_DATA_ALIGNMENT);
	अगर (IS_ERR_VALUE(ugeth->thपढ़ो_dat_rx_offset)) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("Can not allocate DPRAM memory for p_thread_data_rx\n");
		वापस -ENOMEM;
	पूर्ण

	ugeth->p_thपढ़ो_data_rx =
	    (काष्ठा ucc_geth_thपढ़ो_data_rx __iomem *) qe_muram_addr(ugeth->
							thपढ़ो_dat_rx_offset);
	out_be32(&ugeth->p_rx_glbl_pram->rqptr, ugeth->thपढ़ो_dat_rx_offset);

	/* typeorlen */
	out_be16(&ugeth->p_rx_glbl_pram->typeorlen, ug_info->typeorlen);

	/* rxrmonbaseptr (statistics) */
	अगर (ug_info->
	    statisticsMode & UCC_GETH_STATISTICS_GATHERING_MODE_FIRMWARE_RX) अणु
		ugeth->rx_fw_statistics_pram_offset =
		    qe_muram_alloc(माप
				   (काष्ठा ucc_geth_rx_firmware_statistics_pram),
				   UCC_GETH_RX_STATISTICS_ALIGNMENT);
		अगर (IS_ERR_VALUE(ugeth->rx_fw_statistics_pram_offset)) अणु
			अगर (netअगर_msg_अगरup(ugeth))
				pr_err("Can not allocate DPRAM memory for p_rx_fw_statistics_pram\n");
			वापस -ENOMEM;
		पूर्ण
		ugeth->p_rx_fw_statistics_pram =
		    (काष्ठा ucc_geth_rx_firmware_statistics_pram __iomem *)
		    qe_muram_addr(ugeth->rx_fw_statistics_pram_offset);
	पूर्ण

	/* पूर्णांकCoalescingPtr */

	/* Size varies with number of Rx queues */
	ugeth->rx_irq_coalescing_tbl_offset =
	    qe_muram_alloc(ucc_geth_rx_queues(ug_info) *
			   माप(काष्ठा ucc_geth_rx_पूर्णांकerrupt_coalescing_entry)
			   + 4, UCC_GETH_RX_INTERRUPT_COALESCING_ALIGNMENT);
	अगर (IS_ERR_VALUE(ugeth->rx_irq_coalescing_tbl_offset)) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("Can not allocate DPRAM memory for p_rx_irq_coalescing_tbl\n");
		वापस -ENOMEM;
	पूर्ण

	ugeth->p_rx_irq_coalescing_tbl =
	    (काष्ठा ucc_geth_rx_पूर्णांकerrupt_coalescing_table __iomem *)
	    qe_muram_addr(ugeth->rx_irq_coalescing_tbl_offset);
	out_be32(&ugeth->p_rx_glbl_pram->पूर्णांकcoalescingptr,
		 ugeth->rx_irq_coalescing_tbl_offset);

	/* Fill पूर्णांकerrupt coalescing table */
	क्रम (i = 0; i < ucc_geth_rx_queues(ug_info); i++) अणु
		out_be32(&ugeth->p_rx_irq_coalescing_tbl->coalescingentry[i].
			 पूर्णांकerruptcoalescingmaxvalue,
			 ug_info->पूर्णांकerruptcoalescingmaxvalue[i]);
		out_be32(&ugeth->p_rx_irq_coalescing_tbl->coalescingentry[i].
			 पूर्णांकerruptcoalescingcounter,
			 ug_info->पूर्णांकerruptcoalescingmaxvalue[i]);
	पूर्ण

	/* MRBLR */
	init_max_rx_buff_len(uf_info->max_rx_buf_length,
			     &ugeth->p_rx_glbl_pram->mrblr);
	/* MFLR */
	out_be16(&ugeth->p_rx_glbl_pram->mflr, ug_info->maxFrameLength);
	/* MINFLR */
	init_min_frame_len(ug_info->minFrameLength,
			   &ugeth->p_rx_glbl_pram->minflr,
			   &ugeth->p_rx_glbl_pram->mrblr);
	/* MAXD1 */
	out_be16(&ugeth->p_rx_glbl_pram->maxd1, ug_info->maxD1Length);
	/* MAXD2 */
	out_be16(&ugeth->p_rx_glbl_pram->maxd2, ug_info->maxD2Length);

	/* l2qt */
	l2qt = 0;
	क्रम (i = 0; i < UCC_GETH_VLAN_PRIORITY_MAX; i++)
		l2qt |= (ug_info->l2qt[i] << (28 - 4 * i));
	out_be32(&ugeth->p_rx_glbl_pram->l2qt, l2qt);

	/* l3qt */
	क्रम (j = 0; j < UCC_GETH_IP_PRIORITY_MAX; j += 8) अणु
		l3qt = 0;
		क्रम (i = 0; i < 8; i++)
			l3qt |= (ug_info->l3qt[j + i] << (28 - 4 * i));
		out_be32(&ugeth->p_rx_glbl_pram->l3qt[j/8], l3qt);
	पूर्ण

	/* vlantype */
	out_be16(&ugeth->p_rx_glbl_pram->vlantype, ug_info->vlantype);

	/* vlantci */
	out_be16(&ugeth->p_rx_glbl_pram->vlantci, ug_info->vlantci);

	/* ecamptr */
	out_be32(&ugeth->p_rx_glbl_pram->ecamptr, ug_info->ecamptr);

	/* RBDQPTR */
	/* Size varies with number of Rx queues */
	ugeth->rx_bd_qs_tbl_offset =
	    qe_muram_alloc(ucc_geth_rx_queues(ug_info) *
			   (माप(काष्ठा ucc_geth_rx_bd_queues_entry) +
			    माप(काष्ठा ucc_geth_rx_prefetched_bds)),
			   UCC_GETH_RX_BD_QUEUES_ALIGNMENT);
	अगर (IS_ERR_VALUE(ugeth->rx_bd_qs_tbl_offset)) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("Can not allocate DPRAM memory for p_rx_bd_qs_tbl\n");
		वापस -ENOMEM;
	पूर्ण

	ugeth->p_rx_bd_qs_tbl =
	    (काष्ठा ucc_geth_rx_bd_queues_entry __iomem *) qe_muram_addr(ugeth->
				    rx_bd_qs_tbl_offset);
	out_be32(&ugeth->p_rx_glbl_pram->rbdqptr, ugeth->rx_bd_qs_tbl_offset);

	/* Setup the table */
	/* Assume BD rings are alपढ़ोy established */
	क्रम (i = 0; i < ucc_geth_rx_queues(ug_info); i++) अणु
		out_be32(&ugeth->p_rx_bd_qs_tbl[i].बाह्यalbdbaseptr,
			 (u32) virt_to_phys(ugeth->p_rx_bd_ring[i]));
		/* rest of fields handled by QE */
	पूर्ण

	/* remoder */
	/* Alपढ़ोy has speed set */

	अगर (ugeth->rx_extended_features)
		remoder |= REMODER_RX_EXTENDED_FEATURES;
	अगर (ug_info->rxExtendedFiltering)
		remoder |= REMODER_RX_EXTENDED_FILTERING;
	अगर (ug_info->dynamicMaxFrameLength)
		remoder |= REMODER_DYNAMIC_MAX_FRAME_LENGTH;
	अगर (ug_info->dynamicMinFrameLength)
		remoder |= REMODER_DYNAMIC_MIN_FRAME_LENGTH;
	remoder |=
	    ug_info->vlanOperationTagged << REMODER_VLAN_OPERATION_TAGGED_SHIFT;
	remoder |=
	    ug_info->
	    vlanOperationNonTagged << REMODER_VLAN_OPERATION_NON_TAGGED_SHIFT;
	remoder |= ug_info->rxQoSMode << REMODER_RX_QOS_MODE_SHIFT;
	remoder |= ((ucc_geth_rx_queues(ug_info) - 1) << REMODER_NUM_OF_QUEUES_SHIFT);
	अगर (ug_info->ipCheckSumCheck)
		remoder |= REMODER_IP_CHECKSUM_CHECK;
	अगर (ug_info->ipAddressAlignment)
		remoder |= REMODER_IP_ADDRESS_ALIGNMENT;
	out_be32(&ugeth->p_rx_glbl_pram->remoder, remoder);

	/* Note that this function must be called */
	/* ONLY AFTER p_tx_fw_statistics_pram */
	/* andp_UccGethRxFirmwareStatisticsPram are allocated ! */
	init_firmware_statistics_gathering_mode((ug_info->
		statisticsMode &
		UCC_GETH_STATISTICS_GATHERING_MODE_FIRMWARE_TX),
		(ug_info->statisticsMode &
		UCC_GETH_STATISTICS_GATHERING_MODE_FIRMWARE_RX),
		&ugeth->p_tx_glbl_pram->txrmonbaseptr,
		ugeth->tx_fw_statistics_pram_offset,
		&ugeth->p_rx_glbl_pram->rxrmonbaseptr,
		ugeth->rx_fw_statistics_pram_offset,
		&ugeth->p_tx_glbl_pram->temoder,
		&ugeth->p_rx_glbl_pram->remoder);

	/* function code रेजिस्टर */
	out_8(&ugeth->p_rx_glbl_pram->rstate, function_code);

	/* initialize extended filtering */
	अगर (ug_info->rxExtendedFiltering) अणु
		अगर (!ug_info->extendedFilteringChainPoपूर्णांकer) अणु
			अगर (netअगर_msg_अगरup(ugeth))
				pr_err("Null Extended Filtering Chain Pointer\n");
			वापस -EINVAL;
		पूर्ण

		/* Allocate memory क्रम extended filtering Mode Global
		Parameters */
		ugeth->exf_glbl_param_offset =
		    qe_muram_alloc(माप(काष्ठा ucc_geth_exf_global_pram),
		UCC_GETH_RX_EXTENDED_FILTERING_GLOBAL_PARAMETERS_ALIGNMENT);
		अगर (IS_ERR_VALUE(ugeth->exf_glbl_param_offset)) अणु
			अगर (netअगर_msg_अगरup(ugeth))
				pr_err("Can not allocate DPRAM memory for p_exf_glbl_param\n");
			वापस -ENOMEM;
		पूर्ण

		ugeth->p_exf_glbl_param =
		    (काष्ठा ucc_geth_exf_global_pram __iomem *) qe_muram_addr(ugeth->
				 exf_glbl_param_offset);
		out_be32(&ugeth->p_rx_glbl_pram->exfGlobalParam,
			 ugeth->exf_glbl_param_offset);
		out_be32(&ugeth->p_exf_glbl_param->l2pcdptr,
			 (u32) ug_info->extendedFilteringChainPoपूर्णांकer);

	पूर्ण अन्यथा अणु		/* initialize 82xx style address filtering */

		/* Init inभागidual address recognition रेजिस्टरs to disabled */

		क्रम (j = 0; j < NUM_OF_PADDRS; j++)
			ugeth_82xx_filtering_clear_addr_in_paddr(ugeth, (u8) j);

		p_82xx_addr_filt =
		    (काष्ठा ucc_geth_82xx_address_filtering_pram __iomem *) ugeth->
		    p_rx_glbl_pram->addressfiltering;

		ugeth_82xx_filtering_clear_all_addr_in_hash(ugeth,
			ENET_ADDR_TYPE_GROUP);
		ugeth_82xx_filtering_clear_all_addr_in_hash(ugeth,
			ENET_ADDR_TYPE_INDIVIDUAL);
	पूर्ण

	/*
	 * Initialize UCC at QE level
	 */

	command = QE_INIT_TX_RX;

	/* Allocate shaकरोw InitEnet command parameter काष्ठाure.
	 * This is needed because after the InitEnet command is executed,
	 * the काष्ठाure in DPRAM is released, because DPRAM is a premium
	 * resource.
	 * This shaकरोw काष्ठाure keeps a copy of what was करोne so that the
	 * allocated resources can be released when the channel is मुक्तd.
	 */
	अगर (!(ugeth->p_init_enet_param_shaकरोw =
	      kzalloc(माप(काष्ठा ucc_geth_init_pram), GFP_KERNEL))) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("Can not allocate memory for p_UccInitEnetParamShadows\n");
		वापस -ENOMEM;
	पूर्ण

	/* Fill shaकरोw InitEnet command parameter काष्ठाure */

	ugeth->p_init_enet_param_shaकरोw->resinit1 =
	    ENET_INIT_PARAM_MAGIC_RES_INIT1;
	ugeth->p_init_enet_param_shaकरोw->resinit2 =
	    ENET_INIT_PARAM_MAGIC_RES_INIT2;
	ugeth->p_init_enet_param_shaकरोw->resinit3 =
	    ENET_INIT_PARAM_MAGIC_RES_INIT3;
	ugeth->p_init_enet_param_shaकरोw->resinit4 =
	    ENET_INIT_PARAM_MAGIC_RES_INIT4;
	ugeth->p_init_enet_param_shaकरोw->resinit5 =
	    ENET_INIT_PARAM_MAGIC_RES_INIT5;
	ugeth->p_init_enet_param_shaकरोw->rgftgfrxglobal |=
	    ((u32) ug_info->numThपढ़ोsRx) << ENET_INIT_PARAM_RGF_SHIFT;
	ugeth->p_init_enet_param_shaकरोw->rgftgfrxglobal |=
	    ((u32) ug_info->numThपढ़ोsTx) << ENET_INIT_PARAM_TGF_SHIFT;

	ugeth->p_init_enet_param_shaकरोw->rgftgfrxglobal |=
	    rx_glbl_pram_offset | ug_info->riscRx;
	अगर ((ug_info->largestबाह्यallookupkeysize !=
	     QE_FLTR_LARGEST_EXTERNAL_TABLE_LOOKUP_KEY_SIZE_NONE) &&
	    (ug_info->largestबाह्यallookupkeysize !=
	     QE_FLTR_LARGEST_EXTERNAL_TABLE_LOOKUP_KEY_SIZE_8_BYTES) &&
	    (ug_info->largestबाह्यallookupkeysize !=
	     QE_FLTR_LARGEST_EXTERNAL_TABLE_LOOKUP_KEY_SIZE_16_BYTES)) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("Invalid largest External Lookup Key Size\n");
		वापस -EINVAL;
	पूर्ण
	ugeth->p_init_enet_param_shaकरोw->largestबाह्यallookupkeysize =
	    ug_info->largestबाह्यallookupkeysize;
	size = माप(काष्ठा ucc_geth_thपढ़ो_rx_pram);
	अगर (ug_info->rxExtendedFiltering) अणु
		size += THREAD_RX_PRAM_ADDITIONAL_FOR_EXTENDED_FILTERING;
		अगर (ug_info->largestबाह्यallookupkeysize ==
		    QE_FLTR_LARGEST_EXTERNAL_TABLE_LOOKUP_KEY_SIZE_8_BYTES)
			size +=
			    THREAD_RX_PRAM_ADDITIONAL_FOR_EXTENDED_FILTERING_8;
		अगर (ug_info->largestबाह्यallookupkeysize ==
		    QE_FLTR_LARGEST_EXTERNAL_TABLE_LOOKUP_KEY_SIZE_16_BYTES)
			size +=
			    THREAD_RX_PRAM_ADDITIONAL_FOR_EXTENDED_FILTERING_16;
	पूर्ण

	अगर ((ret_val = fill_init_enet_entries(ugeth, &(ugeth->
		p_init_enet_param_shaकरोw->rxthपढ़ो[0]),
		(u8) (numThपढ़ोsRxNumerical + 1)
		/* Rx needs one extra क्रम terminator */
		, size, UCC_GETH_THREAD_RX_PRAM_ALIGNMENT,
		ug_info->riscRx, 1)) != 0) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("Can not fill p_init_enet_param_shadow\n");
		वापस ret_val;
	पूर्ण

	ugeth->p_init_enet_param_shaकरोw->txglobal =
	    tx_glbl_pram_offset | ug_info->riscTx;
	अगर ((ret_val =
	     fill_init_enet_entries(ugeth,
				    &(ugeth->p_init_enet_param_shaकरोw->
				      txthपढ़ो[0]), numThपढ़ोsTxNumerical,
				    माप(काष्ठा ucc_geth_thपढ़ो_tx_pram),
				    UCC_GETH_THREAD_TX_PRAM_ALIGNMENT,
				    ug_info->riscTx, 0)) != 0) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("Can not fill p_init_enet_param_shadow\n");
		वापस ret_val;
	पूर्ण

	/* Load Rx bds with buffers */
	क्रम (i = 0; i < ucc_geth_rx_queues(ug_info); i++) अणु
		अगर ((ret_val = rx_bd_buffer_set(ugeth, (u8) i)) != 0) अणु
			अगर (netअगर_msg_अगरup(ugeth))
				pr_err("Can not fill Rx bds with buffers\n");
			वापस ret_val;
		पूर्ण
	पूर्ण

	/* Allocate InitEnet command parameter काष्ठाure */
	init_enet_pram_offset = qe_muram_alloc(माप(काष्ठा ucc_geth_init_pram), 4);
	अगर (IS_ERR_VALUE(init_enet_pram_offset)) अणु
		अगर (netअगर_msg_अगरup(ugeth))
			pr_err("Can not allocate DPRAM memory for p_init_enet_pram\n");
		वापस -ENOMEM;
	पूर्ण
	p_init_enet_pram =
	    (काष्ठा ucc_geth_init_pram __iomem *) qe_muram_addr(init_enet_pram_offset);

	/* Copy shaकरोw InitEnet command parameter काष्ठाure पूर्णांकo PRAM */
	out_8(&p_init_enet_pram->resinit1,
			ugeth->p_init_enet_param_shaकरोw->resinit1);
	out_8(&p_init_enet_pram->resinit2,
			ugeth->p_init_enet_param_shaकरोw->resinit2);
	out_8(&p_init_enet_pram->resinit3,
			ugeth->p_init_enet_param_shaकरोw->resinit3);
	out_8(&p_init_enet_pram->resinit4,
			ugeth->p_init_enet_param_shaकरोw->resinit4);
	out_be16(&p_init_enet_pram->resinit5,
		 ugeth->p_init_enet_param_shaकरोw->resinit5);
	out_8(&p_init_enet_pram->largestबाह्यallookupkeysize,
	    ugeth->p_init_enet_param_shaकरोw->largestबाह्यallookupkeysize);
	out_be32(&p_init_enet_pram->rgftgfrxglobal,
		 ugeth->p_init_enet_param_shaकरोw->rgftgfrxglobal);
	क्रम (i = 0; i < ENET_INIT_PARAM_MAX_ENTRIES_RX; i++)
		out_be32(&p_init_enet_pram->rxthपढ़ो[i],
			 ugeth->p_init_enet_param_shaकरोw->rxthपढ़ो[i]);
	out_be32(&p_init_enet_pram->txglobal,
		 ugeth->p_init_enet_param_shaकरोw->txglobal);
	क्रम (i = 0; i < ENET_INIT_PARAM_MAX_ENTRIES_TX; i++)
		out_be32(&p_init_enet_pram->txthपढ़ो[i],
			 ugeth->p_init_enet_param_shaकरोw->txthपढ़ो[i]);

	/* Issue QE command */
	cecr_subblock =
	    ucc_fast_get_qe_cr_subblock(ugeth->ug_info->uf_info.ucc_num);
	qe_issue_cmd(command, cecr_subblock, QE_CR_PROTOCOL_ETHERNET,
		     init_enet_pram_offset);

	/* Free InitEnet command parameter */
	qe_muram_मुक्त(init_enet_pram_offset);

	वापस 0;
पूर्ण

/* This is called by the kernel when a frame is पढ़ोy क्रम transmission. */
/* It is poपूर्णांकed to by the dev->hard_start_xmit function poपूर्णांकer */
अटल netdev_tx_t
ucc_geth_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(dev);
#अगर_घोषित CONFIG_UGETH_TX_ON_DEMAND
	काष्ठा ucc_fast_निजी *uccf;
#पूर्ण_अगर
	u8 __iomem *bd;			/* BD poपूर्णांकer */
	u32 bd_status;
	u8 txQ = 0;
	अचिन्हित दीर्घ flags;

	ugeth_vdbg("%s: IN", __func__);

	netdev_sent_queue(dev, skb->len);
	spin_lock_irqsave(&ugeth->lock, flags);

	dev->stats.tx_bytes += skb->len;

	/* Start from the next BD that should be filled */
	bd = ugeth->txBd[txQ];
	bd_status = in_be32((u32 __iomem *)bd);
	/* Save the skb poपूर्णांकer so we can मुक्त it later */
	ugeth->tx_skbuff[txQ][ugeth->skb_curtx[txQ]] = skb;

	/* Update the current skb poपूर्णांकer (wrapping अगर this was the last) */
	ugeth->skb_curtx[txQ] =
	    (ugeth->skb_curtx[txQ] +
	     1) & TX_RING_MOD_MASK(ugeth->ug_info->bdRingLenTx[txQ]);

	/* set up the buffer descriptor */
	out_be32(&((काष्ठा qe_bd __iomem *)bd)->buf,
		      dma_map_single(ugeth->dev, skb->data,
			      skb->len, DMA_TO_DEVICE));

	/* prपूर्णांकk(KERN_DEBUG"skb->data is 0x%x\n",skb->data); */

	bd_status = (bd_status & T_W) | T_R | T_I | T_L | skb->len;

	/* set bd status and length */
	out_be32((u32 __iomem *)bd, bd_status);

	/* Move to next BD in the ring */
	अगर (!(bd_status & T_W))
		bd += माप(काष्ठा qe_bd);
	अन्यथा
		bd = ugeth->p_tx_bd_ring[txQ];

	/* If the next BD still needs to be cleaned up, then the bds
	   are full.  We need to tell the kernel to stop sending us stuff. */
	अगर (bd == ugeth->confBd[txQ]) अणु
		अगर (!netअगर_queue_stopped(dev))
			netअगर_stop_queue(dev);
	पूर्ण

	ugeth->txBd[txQ] = bd;

	skb_tx_बारtamp(skb);

	अगर (ugeth->p_scheduler) अणु
		ugeth->cpucount[txQ]++;
		/* Indicate to QE that there are more Tx bds पढ़ोy क्रम
		transmission */
		/* This is करोne by writing a running counter of the bd
		count to the scheduler PRAM. */
		out_be16(ugeth->p_cpucount[txQ], ugeth->cpucount[txQ]);
	पूर्ण

#अगर_घोषित CONFIG_UGETH_TX_ON_DEMAND
	uccf = ugeth->uccf;
	out_be16(uccf->p_utodr, UCC_FAST_TOD);
#पूर्ण_अगर
	spin_unlock_irqrestore(&ugeth->lock, flags);

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक ucc_geth_rx(काष्ठा ucc_geth_निजी *ugeth, u8 rxQ, पूर्णांक rx_work_limit)
अणु
	काष्ठा sk_buff *skb;
	u8 __iomem *bd;
	u16 length, howmany = 0;
	u32 bd_status;
	u8 *bdBuffer;
	काष्ठा net_device *dev;

	ugeth_vdbg("%s: IN", __func__);

	dev = ugeth->ndev;

	/* collect received buffers */
	bd = ugeth->rxBd[rxQ];

	bd_status = in_be32((u32 __iomem *)bd);

	/* जबतक there are received buffers and BD is full (~R_E) */
	जबतक (!((bd_status & (R_E)) || (--rx_work_limit < 0))) अणु
		bdBuffer = (u8 *) in_be32(&((काष्ठा qe_bd __iomem *)bd)->buf);
		length = (u16) ((bd_status & BD_LENGTH_MASK) - 4);
		skb = ugeth->rx_skbuff[rxQ][ugeth->skb_currx[rxQ]];

		/* determine whether buffer is first, last, first and last
		(single buffer frame) or middle (not first and not last) */
		अगर (!skb ||
		    (!(bd_status & (R_F | R_L))) ||
		    (bd_status & R_ERRORS_FATAL)) अणु
			अगर (netअगर_msg_rx_err(ugeth))
				pr_err("%d: ERROR!!! skb - 0x%08x\n",
				       __LINE__, (u32)skb);
			dev_kमुक्त_skb(skb);

			ugeth->rx_skbuff[rxQ][ugeth->skb_currx[rxQ]] = शून्य;
			dev->stats.rx_dropped++;
		पूर्ण अन्यथा अणु
			dev->stats.rx_packets++;
			howmany++;

			/* Prep the skb क्रम the packet */
			skb_put(skb, length);

			/* Tell the skb what kind of packet this is */
			skb->protocol = eth_type_trans(skb, ugeth->ndev);

			dev->stats.rx_bytes += length;
			/* Send the packet up the stack */
			netअगर_receive_skb(skb);
		पूर्ण

		skb = get_new_skb(ugeth, bd);
		अगर (!skb) अणु
			अगर (netअगर_msg_rx_err(ugeth))
				pr_warn("No Rx Data Buffer\n");
			dev->stats.rx_dropped++;
			अवरोध;
		पूर्ण

		ugeth->rx_skbuff[rxQ][ugeth->skb_currx[rxQ]] = skb;

		/* update to poपूर्णांक at the next skb */
		ugeth->skb_currx[rxQ] =
		    (ugeth->skb_currx[rxQ] +
		     1) & RX_RING_MOD_MASK(ugeth->ug_info->bdRingLenRx[rxQ]);

		अगर (bd_status & R_W)
			bd = ugeth->p_rx_bd_ring[rxQ];
		अन्यथा
			bd += माप(काष्ठा qe_bd);

		bd_status = in_be32((u32 __iomem *)bd);
	पूर्ण

	ugeth->rxBd[rxQ] = bd;
	वापस howmany;
पूर्ण

अटल पूर्णांक ucc_geth_tx(काष्ठा net_device *dev, u8 txQ)
अणु
	/* Start from the next BD that should be filled */
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(dev);
	अचिन्हित पूर्णांक bytes_sent = 0;
	पूर्णांक howmany = 0;
	u8 __iomem *bd;		/* BD poपूर्णांकer */
	u32 bd_status;

	bd = ugeth->confBd[txQ];
	bd_status = in_be32((u32 __iomem *)bd);

	/* Normal processing. */
	जबतक ((bd_status & T_R) == 0) अणु
		काष्ठा sk_buff *skb;

		/* BD contains alपढ़ोy transmitted buffer.   */
		/* Handle the transmitted buffer and release */
		/* the BD to be used with the current frame  */

		skb = ugeth->tx_skbuff[txQ][ugeth->skb_dirtytx[txQ]];
		अगर (!skb)
			अवरोध;
		howmany++;
		bytes_sent += skb->len;
		dev->stats.tx_packets++;

		dev_consume_skb_any(skb);

		ugeth->tx_skbuff[txQ][ugeth->skb_dirtytx[txQ]] = शून्य;
		ugeth->skb_dirtytx[txQ] =
		    (ugeth->skb_dirtytx[txQ] +
		     1) & TX_RING_MOD_MASK(ugeth->ug_info->bdRingLenTx[txQ]);

		/* We मुक्तd a buffer, so now we can restart transmission */
		अगर (netअगर_queue_stopped(dev))
			netअगर_wake_queue(dev);

		/* Advance the confirmation BD poपूर्णांकer */
		अगर (!(bd_status & T_W))
			bd += माप(काष्ठा qe_bd);
		अन्यथा
			bd = ugeth->p_tx_bd_ring[txQ];
		bd_status = in_be32((u32 __iomem *)bd);
	पूर्ण
	ugeth->confBd[txQ] = bd;
	netdev_completed_queue(dev, howmany, bytes_sent);
	वापस 0;
पूर्ण

अटल पूर्णांक ucc_geth_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ucc_geth_निजी *ugeth = container_of(napi, काष्ठा ucc_geth_निजी, napi);
	काष्ठा ucc_geth_info *ug_info;
	पूर्णांक howmany, i;

	ug_info = ugeth->ug_info;

	/* Tx event processing */
	spin_lock(&ugeth->lock);
	क्रम (i = 0; i < ucc_geth_tx_queues(ug_info); i++)
		ucc_geth_tx(ugeth->ndev, i);
	spin_unlock(&ugeth->lock);

	howmany = 0;
	क्रम (i = 0; i < ucc_geth_rx_queues(ug_info); i++)
		howmany += ucc_geth_rx(ugeth, i, budget - howmany);

	अगर (howmany < budget) अणु
		napi_complete_करोne(napi, howmany);
		setbits32(ugeth->uccf->p_uccm, UCCE_RX_EVENTS | UCCE_TX_EVENTS);
	पूर्ण

	वापस howmany;
पूर्ण

अटल irqवापस_t ucc_geth_irq_handler(पूर्णांक irq, व्योम *info)
अणु
	काष्ठा net_device *dev = info;
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(dev);
	काष्ठा ucc_fast_निजी *uccf;
	काष्ठा ucc_geth_info *ug_info;
	रेजिस्टर u32 ucce;
	रेजिस्टर u32 uccm;

	ugeth_vdbg("%s: IN", __func__);

	uccf = ugeth->uccf;
	ug_info = ugeth->ug_info;

	/* पढ़ो and clear events */
	ucce = (u32) in_be32(uccf->p_ucce);
	uccm = (u32) in_be32(uccf->p_uccm);
	ucce &= uccm;
	out_be32(uccf->p_ucce, ucce);

	/* check क्रम receive events that require processing */
	अगर (ucce & (UCCE_RX_EVENTS | UCCE_TX_EVENTS)) अणु
		अगर (napi_schedule_prep(&ugeth->napi)) अणु
			uccm &= ~(UCCE_RX_EVENTS | UCCE_TX_EVENTS);
			out_be32(uccf->p_uccm, uccm);
			__napi_schedule(&ugeth->napi);
		पूर्ण
	पूर्ण

	/* Errors and other events */
	अगर (ucce & UCCE_OTHER) अणु
		अगर (ucce & UCC_GETH_UCCE_BSY)
			dev->stats.rx_errors++;
		अगर (ucce & UCC_GETH_UCCE_TXE)
			dev->stats.tx_errors++;
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
/*
 * Polling 'interrupt' - used by things like netconsole to send skbs
 * without having to re-enable पूर्णांकerrupts. It's not called जबतक
 * the पूर्णांकerrupt routine is executing.
 */
अटल व्योम ucc_netpoll(काष्ठा net_device *dev)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(dev);
	पूर्णांक irq = ugeth->ug_info->uf_info.irq;

	disable_irq(irq);
	ucc_geth_irq_handler(irq, dev);
	enable_irq(irq);
पूर्ण
#पूर्ण_अगर /* CONFIG_NET_POLL_CONTROLLER */

अटल पूर्णांक ucc_geth_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(dev);
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(dev->dev_addr, addr->sa_data, dev->addr_len);

	/*
	 * If device is not running, we will set mac addr रेजिस्टर
	 * when खोलोing the device.
	 */
	अगर (!netअगर_running(dev))
		वापस 0;

	spin_lock_irq(&ugeth->lock);
	init_mac_station_addr_regs(dev->dev_addr[0],
				   dev->dev_addr[1],
				   dev->dev_addr[2],
				   dev->dev_addr[3],
				   dev->dev_addr[4],
				   dev->dev_addr[5],
				   &ugeth->ug_regs->macstnaddr1,
				   &ugeth->ug_regs->macstnaddr2);
	spin_unlock_irq(&ugeth->lock);

	वापस 0;
पूर्ण

अटल पूर्णांक ucc_geth_init_mac(काष्ठा ucc_geth_निजी *ugeth)
अणु
	काष्ठा net_device *dev = ugeth->ndev;
	पूर्णांक err;

	err = ucc_काष्ठा_init(ugeth);
	अगर (err) अणु
		netअगर_err(ugeth, अगरup, dev, "Cannot configure internal struct, aborting\n");
		जाओ err;
	पूर्ण

	err = ucc_geth_startup(ugeth);
	अगर (err) अणु
		netअगर_err(ugeth, अगरup, dev, "Cannot configure net device, aborting\n");
		जाओ err;
	पूर्ण

	err = adjust_enet_पूर्णांकerface(ugeth);
	अगर (err) अणु
		netअगर_err(ugeth, अगरup, dev, "Cannot configure net device, aborting\n");
		जाओ err;
	पूर्ण

	/*       Set MACSTNADDR1, MACSTNADDR2                */
	/* For more details see the hardware spec.           */
	init_mac_station_addr_regs(dev->dev_addr[0],
				   dev->dev_addr[1],
				   dev->dev_addr[2],
				   dev->dev_addr[3],
				   dev->dev_addr[4],
				   dev->dev_addr[5],
				   &ugeth->ug_regs->macstnaddr1,
				   &ugeth->ug_regs->macstnaddr2);

	err = ugeth_enable(ugeth, COMM_सूची_RX_AND_TX);
	अगर (err) अणु
		netअगर_err(ugeth, अगरup, dev, "Cannot enable net device, aborting\n");
		जाओ err;
	पूर्ण

	वापस 0;
err:
	ucc_geth_stop(ugeth);
	वापस err;
पूर्ण

/* Called when something needs to use the ethernet device */
/* Returns 0 क्रम success. */
अटल पूर्णांक ucc_geth_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(dev);
	पूर्णांक err;

	ugeth_vdbg("%s: IN", __func__);

	/* Test station address */
	अगर (dev->dev_addr[0] & ENET_GROUP_ADDR) अणु
		netअगर_err(ugeth, अगरup, dev,
			  "Multicast address used for station address - is this what you wanted?\n");
		वापस -EINVAL;
	पूर्ण

	err = init_phy(dev);
	अगर (err) अणु
		netअगर_err(ugeth, अगरup, dev, "Cannot initialize PHY, aborting\n");
		वापस err;
	पूर्ण

	err = ucc_geth_init_mac(ugeth);
	अगर (err) अणु
		netअगर_err(ugeth, अगरup, dev, "Cannot initialize MAC, aborting\n");
		जाओ err;
	पूर्ण

	err = request_irq(ugeth->ug_info->uf_info.irq, ucc_geth_irq_handler,
			  0, "UCC Geth", dev);
	अगर (err) अणु
		netअगर_err(ugeth, अगरup, dev, "Cannot get IRQ for net device, aborting\n");
		जाओ err;
	पूर्ण

	phy_start(ugeth->phydev);
	napi_enable(&ugeth->napi);
	netdev_reset_queue(dev);
	netअगर_start_queue(dev);

	device_set_wakeup_capable(&dev->dev,
			qe_alive_during_sleep() || ugeth->phydev->irq);
	device_set_wakeup_enable(&dev->dev, ugeth->wol_en);

	वापस err;

err:
	ucc_geth_stop(ugeth);
	वापस err;
पूर्ण

/* Stops the kernel queue, and halts the controller */
अटल पूर्णांक ucc_geth_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(dev);

	ugeth_vdbg("%s: IN", __func__);

	napi_disable(&ugeth->napi);

	cancel_work_sync(&ugeth->समयout_work);
	ucc_geth_stop(ugeth);
	phy_disconnect(ugeth->phydev);
	ugeth->phydev = शून्य;

	मुक्त_irq(ugeth->ug_info->uf_info.irq, ugeth->ndev);

	netअगर_stop_queue(dev);
	netdev_reset_queue(dev);

	वापस 0;
पूर्ण

/* Reखोलो device. This will reset the MAC and PHY. */
अटल व्योम ucc_geth_समयout_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ucc_geth_निजी *ugeth;
	काष्ठा net_device *dev;

	ugeth = container_of(work, काष्ठा ucc_geth_निजी, समयout_work);
	dev = ugeth->ndev;

	ugeth_vdbg("%s: IN", __func__);

	dev->stats.tx_errors++;

	ugeth_dump_regs(ugeth);

	अगर (dev->flags & IFF_UP) अणु
		/*
		 * Must reset MAC *and* PHY. This is करोne by reखोलोing
		 * the device.
		 */
		netअगर_tx_stop_all_queues(dev);
		ucc_geth_stop(ugeth);
		ucc_geth_init_mac(ugeth);
		/* Must start PHY here */
		phy_start(ugeth->phydev);
		netअगर_tx_start_all_queues(dev);
	पूर्ण

	netअगर_tx_schedule_all(dev);
पूर्ण

/*
 * ucc_geth_समयout माला_लो called when a packet has not been
 * transmitted after a set amount of समय.
 */
अटल व्योम ucc_geth_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(dev);

	schedule_work(&ugeth->समयout_work);
पूर्ण


#अगर_घोषित CONFIG_PM

अटल पूर्णांक ucc_geth_suspend(काष्ठा platक्रमm_device *ofdev, pm_message_t state)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(ofdev);
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(ndev);

	अगर (!netअगर_running(ndev))
		वापस 0;

	netअगर_device_detach(ndev);
	napi_disable(&ugeth->napi);

	/*
	 * Disable the controller, otherwise we'll wakeup on any network
	 * activity.
	 */
	ugeth_disable(ugeth, COMM_सूची_RX_AND_TX);

	अगर (ugeth->wol_en & WAKE_MAGIC) अणु
		setbits32(ugeth->uccf->p_uccm, UCC_GETH_UCCE_MPD);
		setbits32(&ugeth->ug_regs->maccfg2, MACCFG2_MPE);
		ucc_fast_enable(ugeth->uccf, COMM_सूची_RX_AND_TX);
	पूर्ण अन्यथा अगर (!(ugeth->wol_en & WAKE_PHY)) अणु
		phy_stop(ugeth->phydev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ucc_geth_resume(काष्ठा platक्रमm_device *ofdev)
अणु
	काष्ठा net_device *ndev = platक्रमm_get_drvdata(ofdev);
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(ndev);
	पूर्णांक err;

	अगर (!netअगर_running(ndev))
		वापस 0;

	अगर (qe_alive_during_sleep()) अणु
		अगर (ugeth->wol_en & WAKE_MAGIC) अणु
			ucc_fast_disable(ugeth->uccf, COMM_सूची_RX_AND_TX);
			clrbits32(&ugeth->ug_regs->maccfg2, MACCFG2_MPE);
			clrbits32(ugeth->uccf->p_uccm, UCC_GETH_UCCE_MPD);
		पूर्ण
		ugeth_enable(ugeth, COMM_सूची_RX_AND_TX);
	पूर्ण अन्यथा अणु
		/*
		 * Full reinitialization is required अगर QE shuts करोwn
		 * during sleep.
		 */
		ucc_geth_memclean(ugeth);

		err = ucc_geth_init_mac(ugeth);
		अगर (err) अणु
			netdev_err(ndev, "Cannot initialize MAC, aborting\n");
			वापस err;
		पूर्ण
	पूर्ण

	ugeth->oldlink = 0;
	ugeth->oldspeed = 0;
	ugeth->oldduplex = -1;

	phy_stop(ugeth->phydev);
	phy_start(ugeth->phydev);

	napi_enable(&ugeth->napi);
	netअगर_device_attach(ndev);

	वापस 0;
पूर्ण

#अन्यथा
#घोषणा ucc_geth_suspend शून्य
#घोषणा ucc_geth_resume शून्य
#पूर्ण_अगर

अटल phy_पूर्णांकerface_t to_phy_पूर्णांकerface(स्थिर अक्षर *phy_connection_type)
अणु
	अगर (strहालcmp(phy_connection_type, "mii") == 0)
		वापस PHY_INTERFACE_MODE_MII;
	अगर (strहालcmp(phy_connection_type, "gmii") == 0)
		वापस PHY_INTERFACE_MODE_GMII;
	अगर (strहालcmp(phy_connection_type, "tbi") == 0)
		वापस PHY_INTERFACE_MODE_TBI;
	अगर (strहालcmp(phy_connection_type, "rmii") == 0)
		वापस PHY_INTERFACE_MODE_RMII;
	अगर (strहालcmp(phy_connection_type, "rgmii") == 0)
		वापस PHY_INTERFACE_MODE_RGMII;
	अगर (strहालcmp(phy_connection_type, "rgmii-id") == 0)
		वापस PHY_INTERFACE_MODE_RGMII_ID;
	अगर (strहालcmp(phy_connection_type, "rgmii-txid") == 0)
		वापस PHY_INTERFACE_MODE_RGMII_TXID;
	अगर (strहालcmp(phy_connection_type, "rgmii-rxid") == 0)
		वापस PHY_INTERFACE_MODE_RGMII_RXID;
	अगर (strहालcmp(phy_connection_type, "rtbi") == 0)
		वापस PHY_INTERFACE_MODE_RTBI;
	अगर (strहालcmp(phy_connection_type, "sgmii") == 0)
		वापस PHY_INTERFACE_MODE_SGMII;

	वापस PHY_INTERFACE_MODE_MII;
पूर्ण

अटल पूर्णांक ucc_geth_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *rq, पूर्णांक cmd)
अणु
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(dev);

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	अगर (!ugeth->phydev)
		वापस -ENODEV;

	वापस phy_mii_ioctl(ugeth->phydev, rq, cmd);
पूर्ण

अटल स्थिर काष्ठा net_device_ops ucc_geth_netdev_ops = अणु
	.nकरो_खोलो		= ucc_geth_खोलो,
	.nकरो_stop		= ucc_geth_बंद,
	.nकरो_start_xmit		= ucc_geth_start_xmit,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_change_carrier     = fixed_phy_change_carrier,
	.nकरो_set_mac_address	= ucc_geth_set_mac_addr,
	.nकरो_set_rx_mode	= ucc_geth_set_multi,
	.nकरो_tx_समयout		= ucc_geth_समयout,
	.nकरो_करो_ioctl		= ucc_geth_ioctl,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= ucc_netpoll,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक ucc_geth_parse_घड़ी(काष्ठा device_node *np, स्थिर अक्षर *which,
				क्रमागत qe_घड़ी *out)
अणु
	स्थिर अक्षर *sprop;
	अक्षर buf[24];

	snम_लिखो(buf, माप(buf), "%s-clock-name", which);
	sprop = of_get_property(np, buf, शून्य);
	अगर (sprop) अणु
		*out = qe_घड़ी_source(sprop);
	पूर्ण अन्यथा अणु
		u32 val;

		snम_लिखो(buf, माप(buf), "%s-clock", which);
		अगर (of_property_पढ़ो_u32(np, buf, &val)) अणु
			/* If both *-घड़ी-name and *-घड़ी are missing,
			 * we want to tell people to use *-घड़ी-name.
			 */
			pr_err("missing %s-clock-name property\n", buf);
			वापस -EINVAL;
		पूर्ण
		*out = val;
	पूर्ण
	अगर (*out < QE_CLK_NONE || *out > QE_CLK24) अणु
		pr_err("invalid %s property\n", buf);
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ucc_geth_probe(काष्ठा platक्रमm_device* ofdev)
अणु
	काष्ठा device *device = &ofdev->dev;
	काष्ठा device_node *np = ofdev->dev.of_node;
	काष्ठा net_device *dev = शून्य;
	काष्ठा ucc_geth_निजी *ugeth = शून्य;
	काष्ठा ucc_geth_info *ug_info;
	काष्ठा resource res;
	पूर्णांक err, ucc_num, max_speed = 0;
	स्थिर अचिन्हित पूर्णांक *prop;
	phy_पूर्णांकerface_t phy_पूर्णांकerface;
	अटल स्थिर पूर्णांक enet_to_speed[] = अणु
		SPEED_10, SPEED_10, SPEED_10,
		SPEED_100, SPEED_100, SPEED_100,
		SPEED_1000, SPEED_1000, SPEED_1000, SPEED_1000,
	पूर्ण;
	अटल स्थिर phy_पूर्णांकerface_t enet_to_phy_पूर्णांकerface[] = अणु
		PHY_INTERFACE_MODE_MII, PHY_INTERFACE_MODE_RMII,
		PHY_INTERFACE_MODE_RGMII, PHY_INTERFACE_MODE_MII,
		PHY_INTERFACE_MODE_RMII, PHY_INTERFACE_MODE_RGMII,
		PHY_INTERFACE_MODE_GMII, PHY_INTERFACE_MODE_RGMII,
		PHY_INTERFACE_MODE_TBI, PHY_INTERFACE_MODE_RTBI,
		PHY_INTERFACE_MODE_SGMII,
	पूर्ण;

	ugeth_vdbg("%s: IN", __func__);

	prop = of_get_property(np, "cell-index", शून्य);
	अगर (!prop) अणु
		prop = of_get_property(np, "device-id", शून्य);
		अगर (!prop)
			वापस -ENODEV;
	पूर्ण

	ucc_num = *prop - 1;
	अगर ((ucc_num < 0) || (ucc_num > 7))
		वापस -ENODEV;

	ug_info = kदो_स्मृति(माप(*ug_info), GFP_KERNEL);
	अगर (ug_info == शून्य)
		वापस -ENOMEM;
	स_नकल(ug_info, &ugeth_primary_info, माप(*ug_info));

	ug_info->uf_info.ucc_num = ucc_num;

	err = ucc_geth_parse_घड़ी(np, "rx", &ug_info->uf_info.rx_घड़ी);
	अगर (err)
		जाओ err_मुक्त_info;
	err = ucc_geth_parse_घड़ी(np, "tx", &ug_info->uf_info.tx_घड़ी);
	अगर (err)
		जाओ err_मुक्त_info;

	err = of_address_to_resource(np, 0, &res);
	अगर (err)
		जाओ err_मुक्त_info;

	ug_info->uf_info.regs = res.start;
	ug_info->uf_info.irq = irq_of_parse_and_map(np, 0);

	ug_info->phy_node = of_parse_phandle(np, "phy-handle", 0);
	अगर (!ug_info->phy_node && of_phy_is_fixed_link(np)) अणु
		/*
		 * In the हाल of a fixed PHY, the DT node associated
		 * to the PHY is the Ethernet MAC DT node.
		 */
		err = of_phy_रेजिस्टर_fixed_link(np);
		अगर (err)
			जाओ err_मुक्त_info;
		ug_info->phy_node = of_node_get(np);
	पूर्ण

	/* Find the TBI PHY node.  If it's not there, we don't support SGMII */
	ug_info->tbi_node = of_parse_phandle(np, "tbi-handle", 0);

	/* get the phy पूर्णांकerface type, or शेष to MII */
	prop = of_get_property(np, "phy-connection-type", शून्य);
	अगर (!prop) अणु
		/* handle पूर्णांकerface property present in old trees */
		prop = of_get_property(ug_info->phy_node, "interface", शून्य);
		अगर (prop != शून्य) अणु
			phy_पूर्णांकerface = enet_to_phy_पूर्णांकerface[*prop];
			max_speed = enet_to_speed[*prop];
		पूर्ण अन्यथा
			phy_पूर्णांकerface = PHY_INTERFACE_MODE_MII;
	पूर्ण अन्यथा अणु
		phy_पूर्णांकerface = to_phy_पूर्णांकerface((स्थिर अक्षर *)prop);
	पूर्ण

	/* get speed, or derive from PHY पूर्णांकerface */
	अगर (max_speed == 0)
		चयन (phy_पूर्णांकerface) अणु
		हाल PHY_INTERFACE_MODE_GMII:
		हाल PHY_INTERFACE_MODE_RGMII:
		हाल PHY_INTERFACE_MODE_RGMII_ID:
		हाल PHY_INTERFACE_MODE_RGMII_RXID:
		हाल PHY_INTERFACE_MODE_RGMII_TXID:
		हाल PHY_INTERFACE_MODE_TBI:
		हाल PHY_INTERFACE_MODE_RTBI:
		हाल PHY_INTERFACE_MODE_SGMII:
			max_speed = SPEED_1000;
			अवरोध;
		शेष:
			max_speed = SPEED_100;
			अवरोध;
		पूर्ण

	अगर (max_speed == SPEED_1000) अणु
		अचिन्हित पूर्णांक snums = qe_get_num_of_snums();

		/* configure muram FIFOs क्रम gigabit operation */
		ug_info->uf_info.urfs = UCC_GETH_URFS_GIGA_INIT;
		ug_info->uf_info.urfet = UCC_GETH_URFET_GIGA_INIT;
		ug_info->uf_info.urfset = UCC_GETH_URFSET_GIGA_INIT;
		ug_info->uf_info.utfs = UCC_GETH_UTFS_GIGA_INIT;
		ug_info->uf_info.utfet = UCC_GETH_UTFET_GIGA_INIT;
		ug_info->uf_info.utftt = UCC_GETH_UTFTT_GIGA_INIT;
		ug_info->numThपढ़ोsTx = UCC_GETH_NUM_OF_THREADS_4;

		/* If QE's snum number is 46/76 which means we need to support
		 * 4 UECs at 1000Base-T simultaneously, we need to allocate
		 * more Thपढ़ोs to Rx.
		 */
		अगर ((snums == 76) || (snums == 46))
			ug_info->numThपढ़ोsRx = UCC_GETH_NUM_OF_THREADS_6;
		अन्यथा
			ug_info->numThपढ़ोsRx = UCC_GETH_NUM_OF_THREADS_4;
	पूर्ण

	अगर (netअगर_msg_probe(&debug))
		pr_info("UCC%1d at 0x%8llx (irq = %d)\n",
			ug_info->uf_info.ucc_num + 1,
			(u64)ug_info->uf_info.regs,
			ug_info->uf_info.irq);

	/* Create an ethernet device instance */
	dev = alloc_etherdev(माप(*ugeth));

	अगर (dev == शून्य) अणु
		err = -ENOMEM;
		जाओ err_deरेजिस्टर_fixed_link;
	पूर्ण

	ugeth = netdev_priv(dev);
	spin_lock_init(&ugeth->lock);

	/* Create CQs क्रम hash tables */
	INIT_LIST_HEAD(&ugeth->group_hash_q);
	INIT_LIST_HEAD(&ugeth->ind_hash_q);

	dev_set_drvdata(device, dev);

	/* Set the dev->base_addr to the gfar reg region */
	dev->base_addr = (अचिन्हित दीर्घ)(ug_info->uf_info.regs);

	SET_NETDEV_DEV(dev, device);

	/* Fill in the dev काष्ठाure */
	uec_set_ethtool_ops(dev);
	dev->netdev_ops = &ucc_geth_netdev_ops;
	dev->watchकरोg_समयo = TX_TIMEOUT;
	INIT_WORK(&ugeth->समयout_work, ucc_geth_समयout_work);
	netअगर_napi_add(dev, &ugeth->napi, ucc_geth_poll, 64);
	dev->mtu = 1500;
	dev->max_mtu = 1518;

	ugeth->msg_enable = netअगर_msg_init(debug.msg_enable, UGETH_MSG_DEFAULT);
	ugeth->phy_पूर्णांकerface = phy_पूर्णांकerface;
	ugeth->max_speed = max_speed;

	/* Carrier starts करोwn, phylib will bring it up */
	netअगर_carrier_off(dev);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		अगर (netअगर_msg_probe(ugeth))
			pr_err("%s: Cannot register net device, aborting\n",
			       dev->name);
		जाओ err_मुक्त_netdev;
	पूर्ण

	of_get_mac_address(np, dev->dev_addr);

	ugeth->ug_info = ug_info;
	ugeth->dev = device;
	ugeth->ndev = dev;
	ugeth->node = np;

	वापस 0;

err_मुक्त_netdev:
	मुक्त_netdev(dev);
err_deरेजिस्टर_fixed_link:
	अगर (of_phy_is_fixed_link(np))
		of_phy_deरेजिस्टर_fixed_link(np);
	of_node_put(ug_info->tbi_node);
	of_node_put(ug_info->phy_node);
err_मुक्त_info:
	kमुक्त(ug_info);

	वापस err;
पूर्ण

अटल पूर्णांक ucc_geth_हटाओ(काष्ठा platक्रमm_device* ofdev)
अणु
	काष्ठा net_device *dev = platक्रमm_get_drvdata(ofdev);
	काष्ठा ucc_geth_निजी *ugeth = netdev_priv(dev);
	काष्ठा device_node *np = ofdev->dev.of_node;

	unरेजिस्टर_netdev(dev);
	ucc_geth_memclean(ugeth);
	अगर (of_phy_is_fixed_link(np))
		of_phy_deरेजिस्टर_fixed_link(np);
	of_node_put(ugeth->ug_info->tbi_node);
	of_node_put(ugeth->ug_info->phy_node);
	kमुक्त(ugeth->ug_info);
	मुक्त_netdev(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ucc_geth_match[] = अणु
	अणु
		.type = "network",
		.compatible = "ucc_geth",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, ucc_geth_match);

अटल काष्ठा platक्रमm_driver ucc_geth_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.of_match_table = ucc_geth_match,
	पूर्ण,
	.probe		= ucc_geth_probe,
	.हटाओ		= ucc_geth_हटाओ,
	.suspend	= ucc_geth_suspend,
	.resume		= ucc_geth_resume,
पूर्ण;

अटल पूर्णांक __init ucc_geth_init(व्योम)
अणु
	अगर (netअगर_msg_drv(&debug))
		pr_info(DRV_DESC "\n");

	वापस platक्रमm_driver_रेजिस्टर(&ucc_geth_driver);
पूर्ण

अटल व्योम __निकास ucc_geth_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&ucc_geth_driver);
पूर्ण

module_init(ucc_geth_init);
module_निकास(ucc_geth_निकास);

MODULE_AUTHOR("Freescale Semiconductor, Inc");
MODULE_DESCRIPTION(DRV_DESC);
MODULE_LICENSE("GPL");
