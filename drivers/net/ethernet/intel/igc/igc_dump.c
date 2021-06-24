<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c)  2018 Intel Corporation */

#समावेश "igc.h"

काष्ठा igc_reg_info अणु
	u32 ofs;
	अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा igc_reg_info igc_reg_info_tbl[] = अणु
	/* General Registers */
	अणुIGC_CTRL, "CTRL"पूर्ण,
	अणुIGC_STATUS, "STATUS"पूर्ण,
	अणुIGC_CTRL_EXT, "CTRL_EXT"पूर्ण,
	अणुIGC_MDIC, "MDIC"पूर्ण,

	/* Interrupt Registers */
	अणुIGC_ICR, "ICR"पूर्ण,

	/* RX Registers */
	अणुIGC_RCTL, "RCTL"पूर्ण,
	अणुIGC_RDLEN(0), "RDLEN"पूर्ण,
	अणुIGC_RDH(0), "RDH"पूर्ण,
	अणुIGC_RDT(0), "RDT"पूर्ण,
	अणुIGC_RXDCTL(0), "RXDCTL"पूर्ण,
	अणुIGC_RDBAL(0), "RDBAL"पूर्ण,
	अणुIGC_RDBAH(0), "RDBAH"पूर्ण,

	/* TX Registers */
	अणुIGC_TCTL, "TCTL"पूर्ण,
	अणुIGC_TDBAL(0), "TDBAL"पूर्ण,
	अणुIGC_TDBAH(0), "TDBAH"पूर्ण,
	अणुIGC_TDLEN(0), "TDLEN"पूर्ण,
	अणुIGC_TDH(0), "TDH"पूर्ण,
	अणुIGC_TDT(0), "TDT"पूर्ण,
	अणुIGC_TXDCTL(0), "TXDCTL"पूर्ण,

	/* List Terminator */
	अणुपूर्ण
पूर्ण;

/* igc_regdump - रेजिस्टर prपूर्णांकout routine */
अटल व्योम igc_regdump(काष्ठा igc_hw *hw, काष्ठा igc_reg_info *reginfo)
अणु
	काष्ठा net_device *dev = igc_get_hw_dev(hw);
	पूर्णांक n = 0;
	अक्षर rname[16];
	u32 regs[8];

	चयन (reginfo->ofs) अणु
	हाल IGC_RDLEN(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(IGC_RDLEN(n));
		अवरोध;
	हाल IGC_RDH(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(IGC_RDH(n));
		अवरोध;
	हाल IGC_RDT(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(IGC_RDT(n));
		अवरोध;
	हाल IGC_RXDCTL(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(IGC_RXDCTL(n));
		अवरोध;
	हाल IGC_RDBAL(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(IGC_RDBAL(n));
		अवरोध;
	हाल IGC_RDBAH(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(IGC_RDBAH(n));
		अवरोध;
	हाल IGC_TDBAL(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(IGC_TDBAL(n));
		अवरोध;
	हाल IGC_TDBAH(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(IGC_TDBAH(n));
		अवरोध;
	हाल IGC_TDLEN(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(IGC_TDLEN(n));
		अवरोध;
	हाल IGC_TDH(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(IGC_TDH(n));
		अवरोध;
	हाल IGC_TDT(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(IGC_TDT(n));
		अवरोध;
	हाल IGC_TXDCTL(0):
		क्रम (n = 0; n < 4; n++)
			regs[n] = rd32(IGC_TXDCTL(n));
		अवरोध;
	शेष:
		netdev_info(dev, "%-15s %08x\n", reginfo->name,
			    rd32(reginfo->ofs));
		वापस;
	पूर्ण

	snम_लिखो(rname, 16, "%s%s", reginfo->name, "[0-3]");
	netdev_info(dev, "%-15s %08x %08x %08x %08x\n", rname, regs[0], regs[1],
		    regs[2], regs[3]);
पूर्ण

/* igc_rings_dump - Tx-rings and Rx-rings */
व्योम igc_rings_dump(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा my_u0 अणु u64 a; u64 b; पूर्ण *u0;
	जोड़ igc_adv_tx_desc *tx_desc;
	जोड़ igc_adv_rx_desc *rx_desc;
	काष्ठा igc_ring *tx_ring;
	काष्ठा igc_ring *rx_ring;
	u32 staterr;
	u16 i, n;

	अगर (!netअगर_msg_hw(adapter))
		वापस;

	netdev_info(netdev, "Device info: state %016lX trans_start %016lX\n",
		    netdev->state, dev_trans_start(netdev));

	/* Prपूर्णांक TX Ring Summary */
	अगर (!netअगर_running(netdev))
		जाओ निकास;

	netdev_info(netdev, "TX Rings Summary\n");
	netdev_info(netdev, "Queue [NTU] [NTC] [bi(ntc)->dma  ] leng ntw timestamp\n");
	क्रम (n = 0; n < adapter->num_tx_queues; n++) अणु
		काष्ठा igc_tx_buffer *buffer_info;

		tx_ring = adapter->tx_ring[n];
		buffer_info = &tx_ring->tx_buffer_info[tx_ring->next_to_clean];

		netdev_info(netdev, "%5d %5X %5X %016llX %04X %p %016llX\n",
			    n, tx_ring->next_to_use, tx_ring->next_to_clean,
			    (u64)dma_unmap_addr(buffer_info, dma),
			    dma_unmap_len(buffer_info, len),
			    buffer_info->next_to_watch,
			    (u64)buffer_info->समय_stamp);
	पूर्ण

	/* Prपूर्णांक TX Rings */
	अगर (!netअगर_msg_tx_करोne(adapter))
		जाओ rx_ring_summary;

	netdev_info(netdev, "TX Rings Dump\n");

	/* Transmit Descriptor Formats
	 *
	 * Advanced Transmit Descriptor
	 *   +--------------------------------------------------------------+
	 * 0 |         Buffer Address [63:0]                                |
	 *   +--------------------------------------------------------------+
	 * 8 | PAYLEN  | PORTS  |CC|IDX | STA | DCMD  |DTYP|MAC|RSV| DTALEN |
	 *   +--------------------------------------------------------------+
	 *   63      46 45    40 39 38 36 35 32 31   24             15       0
	 */

	क्रम (n = 0; n < adapter->num_tx_queues; n++) अणु
		tx_ring = adapter->tx_ring[n];
		netdev_info(netdev, "------------------------------------\n");
		netdev_info(netdev, "TX QUEUE INDEX = %d\n",
			    tx_ring->queue_index);
		netdev_info(netdev, "------------------------------------\n");
		netdev_info(netdev, "T [desc]     [address 63:0  ] [PlPOCIStDDM Ln] [bi->dma       ] leng  ntw timestamp        bi->skb\n");

		क्रम (i = 0; tx_ring->desc && (i < tx_ring->count); i++) अणु
			स्थिर अक्षर *next_desc;
			काष्ठा igc_tx_buffer *buffer_info;

			tx_desc = IGC_TX_DESC(tx_ring, i);
			buffer_info = &tx_ring->tx_buffer_info[i];
			u0 = (काष्ठा my_u0 *)tx_desc;
			अगर (i == tx_ring->next_to_use &&
			    i == tx_ring->next_to_clean)
				next_desc = " NTC/U";
			अन्यथा अगर (i == tx_ring->next_to_use)
				next_desc = " NTU";
			अन्यथा अगर (i == tx_ring->next_to_clean)
				next_desc = " NTC";
			अन्यथा
				next_desc = "";

			netdev_info(netdev, "T [0x%03X]    %016llX %016llX %016llX %04X  %p %016llX %p%s\n",
				    i, le64_to_cpu(u0->a),
				    le64_to_cpu(u0->b),
				    (u64)dma_unmap_addr(buffer_info, dma),
				    dma_unmap_len(buffer_info, len),
				    buffer_info->next_to_watch,
				    (u64)buffer_info->समय_stamp,
				    buffer_info->skb, next_desc);

			अगर (netअगर_msg_pktdata(adapter) && buffer_info->skb)
				prपूर्णांक_hex_dump(KERN_INFO, "",
					       DUMP_PREFIX_ADDRESS,
					       16, 1, buffer_info->skb->data,
					       dma_unmap_len(buffer_info, len),
					       true);
		पूर्ण
	पूर्ण

	/* Prपूर्णांक RX Rings Summary */
rx_ring_summary:
	netdev_info(netdev, "RX Rings Summary\n");
	netdev_info(netdev, "Queue [NTU] [NTC]\n");
	क्रम (n = 0; n < adapter->num_rx_queues; n++) अणु
		rx_ring = adapter->rx_ring[n];
		netdev_info(netdev, "%5d %5X %5X\n", n, rx_ring->next_to_use,
			    rx_ring->next_to_clean);
	पूर्ण

	/* Prपूर्णांक RX Rings */
	अगर (!netअगर_msg_rx_status(adapter))
		जाओ निकास;

	netdev_info(netdev, "RX Rings Dump\n");

	/* Advanced Receive Descriptor (Read) Format
	 *    63                                           1        0
	 *    +-----------------------------------------------------+
	 *  0 |       Packet Buffer Address [63:1]           |A0/NSE|
	 *    +----------------------------------------------+------+
	 *  8 |       Header Buffer Address [63:1]           |  DD  |
	 *    +-----------------------------------------------------+
	 *
	 *
	 * Advanced Receive Descriptor (Write-Back) Format
	 *
	 *   63       48 47    32 31  30      21 20 17 16   4 3     0
	 *   +------------------------------------------------------+
	 * 0 | Packet     IP     |SPH| HDR_LEN   | RSV|Packet|  RSS |
	 *   | Checksum   Ident  |   |           |    | Type | Type |
	 *   +------------------------------------------------------+
	 * 8 | VLAN Tag | Length | Extended Error | Extended Status |
	 *   +------------------------------------------------------+
	 *   63       48 47    32 31            20 19               0
	 */

	क्रम (n = 0; n < adapter->num_rx_queues; n++) अणु
		rx_ring = adapter->rx_ring[n];
		netdev_info(netdev, "------------------------------------\n");
		netdev_info(netdev, "RX QUEUE INDEX = %d\n",
			    rx_ring->queue_index);
		netdev_info(netdev, "------------------------------------\n");
		netdev_info(netdev, "R  [desc]      [ PktBuf     A0] [  HeadBuf   DD] [bi->dma       ] [bi->skb] <-- Adv Rx Read format\n");
		netdev_info(netdev, "RWB[desc]      [PcsmIpSHl PtRs] [vl er S cks ln] ---------------- [bi->skb] <-- Adv Rx Write-Back format\n");

		क्रम (i = 0; i < rx_ring->count; i++) अणु
			स्थिर अक्षर *next_desc;
			काष्ठा igc_rx_buffer *buffer_info;

			buffer_info = &rx_ring->rx_buffer_info[i];
			rx_desc = IGC_RX_DESC(rx_ring, i);
			u0 = (काष्ठा my_u0 *)rx_desc;
			staterr = le32_to_cpu(rx_desc->wb.upper.status_error);

			अगर (i == rx_ring->next_to_use)
				next_desc = " NTU";
			अन्यथा अगर (i == rx_ring->next_to_clean)
				next_desc = " NTC";
			अन्यथा
				next_desc = "";

			अगर (staterr & IGC_RXD_STAT_DD) अणु
				/* Descriptor Done */
				netdev_info(netdev, "%s[0x%03X]     %016llX %016llX ---------------- %s\n",
					    "RWB", i,
					    le64_to_cpu(u0->a),
					    le64_to_cpu(u0->b),
					    next_desc);
			पूर्ण अन्यथा अणु
				netdev_info(netdev, "%s[0x%03X]     %016llX %016llX %016llX %s\n",
					    "R  ", i,
					    le64_to_cpu(u0->a),
					    le64_to_cpu(u0->b),
					    (u64)buffer_info->dma,
					    next_desc);

				अगर (netअगर_msg_pktdata(adapter) &&
				    buffer_info->dma && buffer_info->page) अणु
					prपूर्णांक_hex_dump(KERN_INFO, "",
						       DUMP_PREFIX_ADDRESS,
						       16, 1,
						       page_address
						       (buffer_info->page) +
						       buffer_info->page_offset,
						       igc_rx_bufsz(rx_ring),
						       true);
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

निकास:
	वापस;
पूर्ण

/* igc_regs_dump - रेजिस्टरs dump */
व्योम igc_regs_dump(काष्ठा igc_adapter *adapter)
अणु
	काष्ठा igc_hw *hw = &adapter->hw;
	काष्ठा igc_reg_info *reginfo;

	/* Prपूर्णांक Registers */
	netdev_info(adapter->netdev, "Register Dump\n");
	netdev_info(adapter->netdev, "Register Name   Value\n");
	क्रम (reginfo = (काष्ठा igc_reg_info *)igc_reg_info_tbl;
	     reginfo->name; reginfo++) अणु
		igc_regdump(hw, reginfo);
	पूर्ण
पूर्ण
