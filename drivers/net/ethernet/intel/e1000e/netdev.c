<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 1999 - 2018 Intel Corporation. */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/tcp.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/slab.h>
#समावेश <net/checksum.h>
#समावेश <net/ip6_checksum.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/cpu.h>
#समावेश <linux/smp.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/aer.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/suspend.h>

#समावेश "e1000.h"

अक्षर e1000e_driver_name[] = "e1000e";

#घोषणा DEFAULT_MSG_ENABLE (NETIF_MSG_DRV|NETIF_MSG_PROBE|NETIF_MSG_LINK)
अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

अटल स्थिर काष्ठा e1000_info *e1000_info_tbl[] = अणु
	[board_82571]		= &e1000_82571_info,
	[board_82572]		= &e1000_82572_info,
	[board_82573]		= &e1000_82573_info,
	[board_82574]		= &e1000_82574_info,
	[board_82583]		= &e1000_82583_info,
	[board_80003es2lan]	= &e1000_es2_info,
	[board_ich8lan]		= &e1000_ich8_info,
	[board_ich9lan]		= &e1000_ich9_info,
	[board_ich10lan]	= &e1000_ich10_info,
	[board_pchlan]		= &e1000_pch_info,
	[board_pch2lan]		= &e1000_pch2_info,
	[board_pch_lpt]		= &e1000_pch_lpt_info,
	[board_pch_spt]		= &e1000_pch_spt_info,
	[board_pch_cnp]		= &e1000_pch_cnp_info,
पूर्ण;

काष्ठा e1000_reg_info अणु
	u32 ofs;
	अक्षर *name;
पूर्ण;

अटल स्थिर काष्ठा e1000_reg_info e1000_reg_info_tbl[] = अणु
	/* General Registers */
	अणुE1000_CTRL, "CTRL"पूर्ण,
	अणुE1000_STATUS, "STATUS"पूर्ण,
	अणुE1000_CTRL_EXT, "CTRL_EXT"पूर्ण,

	/* Interrupt Registers */
	अणुE1000_ICR, "ICR"पूर्ण,

	/* Rx Registers */
	अणुE1000_RCTL, "RCTL"पूर्ण,
	अणुE1000_RDLEN(0), "RDLEN"पूर्ण,
	अणुE1000_RDH(0), "RDH"पूर्ण,
	अणुE1000_RDT(0), "RDT"पूर्ण,
	अणुE1000_RDTR, "RDTR"पूर्ण,
	अणुE1000_RXDCTL(0), "RXDCTL"पूर्ण,
	अणुE1000_ERT, "ERT"पूर्ण,
	अणुE1000_RDBAL(0), "RDBAL"पूर्ण,
	अणुE1000_RDBAH(0), "RDBAH"पूर्ण,
	अणुE1000_RDFH, "RDFH"पूर्ण,
	अणुE1000_RDFT, "RDFT"पूर्ण,
	अणुE1000_RDFHS, "RDFHS"पूर्ण,
	अणुE1000_RDFTS, "RDFTS"पूर्ण,
	अणुE1000_RDFPC, "RDFPC"पूर्ण,

	/* Tx Registers */
	अणुE1000_TCTL, "TCTL"पूर्ण,
	अणुE1000_TDBAL(0), "TDBAL"पूर्ण,
	अणुE1000_TDBAH(0), "TDBAH"पूर्ण,
	अणुE1000_TDLEN(0), "TDLEN"पूर्ण,
	अणुE1000_TDH(0), "TDH"पूर्ण,
	अणुE1000_TDT(0), "TDT"पूर्ण,
	अणुE1000_TIDV, "TIDV"पूर्ण,
	अणुE1000_TXDCTL(0), "TXDCTL"पूर्ण,
	अणुE1000_TADV, "TADV"पूर्ण,
	अणुE1000_TARC(0), "TARC"पूर्ण,
	अणुE1000_TDFH, "TDFH"पूर्ण,
	अणुE1000_TDFT, "TDFT"पूर्ण,
	अणुE1000_TDFHS, "TDFHS"पूर्ण,
	अणुE1000_TDFTS, "TDFTS"पूर्ण,
	अणुE1000_TDFPC, "TDFPC"पूर्ण,

	/* List Terminator */
	अणु0, शून्यपूर्ण
पूर्ण;

/**
 * __ew32_prepare - prepare to ग_लिखो to MAC CSR रेजिस्टर on certain parts
 * @hw: poपूर्णांकer to the HW काष्ठाure
 *
 * When updating the MAC CSR रेजिस्टरs, the Manageability Engine (ME) could
 * be accessing the रेजिस्टरs at the same समय.  Normally, this is handled in
 * h/w by an arbiter but on some parts there is a bug that acknowledges Host
 * accesses later than it should which could result in the रेजिस्टर to have
 * an incorrect value.  Workaround this by checking the FWSM रेजिस्टर which
 * has bit 24 set जबतक ME is accessing MAC CSR रेजिस्टरs, रुको अगर it is set
 * and try again a number of बार.
 **/
अटल व्योम __ew32_prepare(काष्ठा e1000_hw *hw)
अणु
	s32 i = E1000_ICH_FWSM_PCIM2PCI_COUNT;

	जबतक ((er32(FWSM) & E1000_ICH_FWSM_PCIM2PCI) && --i)
		udelay(50);
पूर्ण

व्योम __ew32(काष्ठा e1000_hw *hw, अचिन्हित दीर्घ reg, u32 val)
अणु
	अगर (hw->adapter->flags2 & FLAG2_PCIM2PCI_ARBITER_WA)
		__ew32_prepare(hw);

	ग_लिखोl(val, hw->hw_addr + reg);
पूर्ण

/**
 * e1000_regdump - रेजिस्टर prपूर्णांकout routine
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @reginfo: poपूर्णांकer to the रेजिस्टर info table
 **/
अटल व्योम e1000_regdump(काष्ठा e1000_hw *hw, काष्ठा e1000_reg_info *reginfo)
अणु
	पूर्णांक n = 0;
	अक्षर rname[16];
	u32 regs[8];

	चयन (reginfo->ofs) अणु
	हाल E1000_RXDCTL(0):
		क्रम (n = 0; n < 2; n++)
			regs[n] = __er32(hw, E1000_RXDCTL(n));
		अवरोध;
	हाल E1000_TXDCTL(0):
		क्रम (n = 0; n < 2; n++)
			regs[n] = __er32(hw, E1000_TXDCTL(n));
		अवरोध;
	हाल E1000_TARC(0):
		क्रम (n = 0; n < 2; n++)
			regs[n] = __er32(hw, E1000_TARC(n));
		अवरोध;
	शेष:
		pr_info("%-15s %08x\n",
			reginfo->name, __er32(hw, reginfo->ofs));
		वापस;
	पूर्ण

	snम_लिखो(rname, 16, "%s%s", reginfo->name, "[0-1]");
	pr_info("%-15s %08x %08x\n", rname, regs[0], regs[1]);
पूर्ण

अटल व्योम e1000e_dump_ps_pages(काष्ठा e1000_adapter *adapter,
				 काष्ठा e1000_buffer *bi)
अणु
	पूर्णांक i;
	काष्ठा e1000_ps_page *ps_page;

	क्रम (i = 0; i < adapter->rx_ps_pages; i++) अणु
		ps_page = &bi->ps_pages[i];

		अगर (ps_page->page) अणु
			pr_info("packet dump for ps_page %d:\n", i);
			prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_ADDRESS,
				       16, 1, page_address(ps_page->page),
				       PAGE_SIZE, true);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * e1000e_dump - Prपूर्णांक रेजिस्टरs, Tx-ring and Rx-ring
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम e1000e_dump(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_reg_info *reginfo;
	काष्ठा e1000_ring *tx_ring = adapter->tx_ring;
	काष्ठा e1000_tx_desc *tx_desc;
	काष्ठा my_u0 अणु
		__le64 a;
		__le64 b;
	पूर्ण *u0;
	काष्ठा e1000_buffer *buffer_info;
	काष्ठा e1000_ring *rx_ring = adapter->rx_ring;
	जोड़ e1000_rx_desc_packet_split *rx_desc_ps;
	जोड़ e1000_rx_desc_extended *rx_desc;
	काष्ठा my_u1 अणु
		__le64 a;
		__le64 b;
		__le64 c;
		__le64 d;
	पूर्ण *u1;
	u32 staterr;
	पूर्णांक i = 0;

	अगर (!netअगर_msg_hw(adapter))
		वापस;

	/* Prपूर्णांक netdevice Info */
	अगर (netdev) अणु
		dev_info(&adapter->pdev->dev, "Net device Info\n");
		pr_info("Device Name     state            trans_start\n");
		pr_info("%-15s %016lX %016lX\n", netdev->name,
			netdev->state, dev_trans_start(netdev));
	पूर्ण

	/* Prपूर्णांक Registers */
	dev_info(&adapter->pdev->dev, "Register Dump\n");
	pr_info(" Register Name   Value\n");
	क्रम (reginfo = (काष्ठा e1000_reg_info *)e1000_reg_info_tbl;
	     reginfo->name; reginfo++) अणु
		e1000_regdump(hw, reginfo);
	पूर्ण

	/* Prपूर्णांक Tx Ring Summary */
	अगर (!netdev || !netअगर_running(netdev))
		वापस;

	dev_info(&adapter->pdev->dev, "Tx Ring Summary\n");
	pr_info("Queue [NTU] [NTC] [bi(ntc)->dma  ] leng ntw timestamp\n");
	buffer_info = &tx_ring->buffer_info[tx_ring->next_to_clean];
	pr_info(" %5d %5X %5X %016llX %04X %3X %016llX\n",
		0, tx_ring->next_to_use, tx_ring->next_to_clean,
		(अचिन्हित दीर्घ दीर्घ)buffer_info->dma,
		buffer_info->length,
		buffer_info->next_to_watch,
		(अचिन्हित दीर्घ दीर्घ)buffer_info->समय_stamp);

	/* Prपूर्णांक Tx Ring */
	अगर (!netअगर_msg_tx_करोne(adapter))
		जाओ rx_ring_summary;

	dev_info(&adapter->pdev->dev, "Tx Ring Dump\n");

	/* Transmit Descriptor Formats - DEXT[29] is 0 (Legacy) or 1 (Extended)
	 *
	 * Legacy Transmit Descriptor
	 *   +--------------------------------------------------------------+
	 * 0 |         Buffer Address [63:0] (Reserved on Write Back)       |
	 *   +--------------------------------------------------------------+
	 * 8 | Special  |    CSS     | Status |  CMD    |  CSO   |  Length  |
	 *   +--------------------------------------------------------------+
	 *   63       48 47        36 35    32 31     24 23    16 15        0
	 *
	 * Extended Context Descriptor (DTYP=0x0) क्रम TSO or checksum offload
	 *   63      48 47    40 39       32 31             16 15    8 7      0
	 *   +----------------------------------------------------------------+
	 * 0 |  TUCSE  | TUCS0  |   TUCSS   |     IPCSE       | IPCS0 | IPCSS |
	 *   +----------------------------------------------------------------+
	 * 8 |   MSS   | HDRLEN | RSV | STA | TUCMD | DTYP |      PAYLEN      |
	 *   +----------------------------------------------------------------+
	 *   63      48 47    40 39 36 35 32 31   24 23  20 19                0
	 *
	 * Extended Data Descriptor (DTYP=0x1)
	 *   +----------------------------------------------------------------+
	 * 0 |                     Buffer Address [63:0]                      |
	 *   +----------------------------------------------------------------+
	 * 8 | VLAN tag |  POPTS  | Rsvd | Status | Command | DTYP |  DTALEN  |
	 *   +----------------------------------------------------------------+
	 *   63       48 47     40 39  36 35    32 31     24 23  20 19        0
	 */
	pr_info("Tl[desc]     [address 63:0  ] [SpeCssSCmCsLen] [bi->dma       ] leng  ntw timestamp        bi->skb <-- Legacy format\n");
	pr_info("Tc[desc]     [Ce CoCsIpceCoS] [MssHlRSCm0Plen] [bi->dma       ] leng  ntw timestamp        bi->skb <-- Ext Context format\n");
	pr_info("Td[desc]     [address 63:0  ] [VlaPoRSCm1Dlen] [bi->dma       ] leng  ntw timestamp        bi->skb <-- Ext Data format\n");
	क्रम (i = 0; tx_ring->desc && (i < tx_ring->count); i++) अणु
		स्थिर अक्षर *next_desc;
		tx_desc = E1000_TX_DESC(*tx_ring, i);
		buffer_info = &tx_ring->buffer_info[i];
		u0 = (काष्ठा my_u0 *)tx_desc;
		अगर (i == tx_ring->next_to_use && i == tx_ring->next_to_clean)
			next_desc = " NTC/U";
		अन्यथा अगर (i == tx_ring->next_to_use)
			next_desc = " NTU";
		अन्यथा अगर (i == tx_ring->next_to_clean)
			next_desc = " NTC";
		अन्यथा
			next_desc = "";
		pr_info("T%c[0x%03X]    %016llX %016llX %016llX %04X  %3X %016llX %p%s\n",
			(!(le64_to_cpu(u0->b) & BIT(29)) ? 'l' :
			 ((le64_to_cpu(u0->b) & BIT(20)) ? 'd' : 'c')),
			i,
			(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(u0->a),
			(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(u0->b),
			(अचिन्हित दीर्घ दीर्घ)buffer_info->dma,
			buffer_info->length, buffer_info->next_to_watch,
			(अचिन्हित दीर्घ दीर्घ)buffer_info->समय_stamp,
			buffer_info->skb, next_desc);

		अगर (netअगर_msg_pktdata(adapter) && buffer_info->skb)
			prपूर्णांक_hex_dump(KERN_INFO, "", DUMP_PREFIX_ADDRESS,
				       16, 1, buffer_info->skb->data,
				       buffer_info->skb->len, true);
	पूर्ण

	/* Prपूर्णांक Rx Ring Summary */
rx_ring_summary:
	dev_info(&adapter->pdev->dev, "Rx Ring Summary\n");
	pr_info("Queue [NTU] [NTC]\n");
	pr_info(" %5d %5X %5X\n",
		0, rx_ring->next_to_use, rx_ring->next_to_clean);

	/* Prपूर्णांक Rx Ring */
	अगर (!netअगर_msg_rx_status(adapter))
		वापस;

	dev_info(&adapter->pdev->dev, "Rx Ring Dump\n");
	चयन (adapter->rx_ps_pages) अणु
	हाल 1:
	हाल 2:
	हाल 3:
		/* [Extended] Packet Split Receive Descriptor Format
		 *
		 *    +-----------------------------------------------------+
		 *  0 |                Buffer Address 0 [63:0]              |
		 *    +-----------------------------------------------------+
		 *  8 |                Buffer Address 1 [63:0]              |
		 *    +-----------------------------------------------------+
		 * 16 |                Buffer Address 2 [63:0]              |
		 *    +-----------------------------------------------------+
		 * 24 |                Buffer Address 3 [63:0]              |
		 *    +-----------------------------------------------------+
		 */
		pr_info("R  [desc]      [buffer 0 63:0 ] [buffer 1 63:0 ] [buffer 2 63:0 ] [buffer 3 63:0 ] [bi->dma       ] [bi->skb] <-- Ext Pkt Split format\n");
		/* [Extended] Receive Descriptor (Write-Back) Format
		 *
		 *   63       48 47    32 31     13 12    8 7    4 3        0
		 *   +------------------------------------------------------+
		 * 0 | Packet   | IP     |  Rsvd   | MRQ   | Rsvd | MRQ RSS |
		 *   | Checksum | Ident  |         | Queue |      |  Type   |
		 *   +------------------------------------------------------+
		 * 8 | VLAN Tag | Length | Extended Error | Extended Status |
		 *   +------------------------------------------------------+
		 *   63       48 47    32 31            20 19               0
		 */
		pr_info("RWB[desc]      [ck ipid mrqhsh] [vl   l0 ee  es] [ l3  l2  l1 hs] [reserved      ] ---------------- [bi->skb] <-- Ext Rx Write-Back format\n");
		क्रम (i = 0; i < rx_ring->count; i++) अणु
			स्थिर अक्षर *next_desc;
			buffer_info = &rx_ring->buffer_info[i];
			rx_desc_ps = E1000_RX_DESC_PS(*rx_ring, i);
			u1 = (काष्ठा my_u1 *)rx_desc_ps;
			staterr =
			    le32_to_cpu(rx_desc_ps->wb.middle.status_error);

			अगर (i == rx_ring->next_to_use)
				next_desc = " NTU";
			अन्यथा अगर (i == rx_ring->next_to_clean)
				next_desc = " NTC";
			अन्यथा
				next_desc = "";

			अगर (staterr & E1000_RXD_STAT_DD) अणु
				/* Descriptor Done */
				pr_info("%s[0x%03X]     %016llX %016llX %016llX %016llX ---------------- %p%s\n",
					"RWB", i,
					(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(u1->a),
					(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(u1->b),
					(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(u1->c),
					(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(u1->d),
					buffer_info->skb, next_desc);
			पूर्ण अन्यथा अणु
				pr_info("%s[0x%03X]     %016llX %016llX %016llX %016llX %016llX %p%s\n",
					"R  ", i,
					(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(u1->a),
					(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(u1->b),
					(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(u1->c),
					(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(u1->d),
					(अचिन्हित दीर्घ दीर्घ)buffer_info->dma,
					buffer_info->skb, next_desc);

				अगर (netअगर_msg_pktdata(adapter))
					e1000e_dump_ps_pages(adapter,
							     buffer_info);
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
	हाल 0:
		/* Extended Receive Descriptor (Read) Format
		 *
		 *   +-----------------------------------------------------+
		 * 0 |                Buffer Address [63:0]                |
		 *   +-----------------------------------------------------+
		 * 8 |                      Reserved                       |
		 *   +-----------------------------------------------------+
		 */
		pr_info("R  [desc]      [buf addr 63:0 ] [reserved 63:0 ] [bi->dma       ] [bi->skb] <-- Ext (Read) format\n");
		/* Extended Receive Descriptor (Write-Back) Format
		 *
		 *   63       48 47    32 31    24 23            4 3        0
		 *   +------------------------------------------------------+
		 *   |     RSS Hash      |        |               |         |
		 * 0 +-------------------+  Rsvd  |   Reserved    | MRQ RSS |
		 *   | Packet   | IP     |        |               |  Type   |
		 *   | Checksum | Ident  |        |               |         |
		 *   +------------------------------------------------------+
		 * 8 | VLAN Tag | Length | Extended Error | Extended Status |
		 *   +------------------------------------------------------+
		 *   63       48 47    32 31            20 19               0
		 */
		pr_info("RWB[desc]      [cs ipid    mrq] [vt   ln xe  xs] [bi->skb] <-- Ext (Write-Back) format\n");

		क्रम (i = 0; i < rx_ring->count; i++) अणु
			स्थिर अक्षर *next_desc;

			buffer_info = &rx_ring->buffer_info[i];
			rx_desc = E1000_RX_DESC_EXT(*rx_ring, i);
			u1 = (काष्ठा my_u1 *)rx_desc;
			staterr = le32_to_cpu(rx_desc->wb.upper.status_error);

			अगर (i == rx_ring->next_to_use)
				next_desc = " NTU";
			अन्यथा अगर (i == rx_ring->next_to_clean)
				next_desc = " NTC";
			अन्यथा
				next_desc = "";

			अगर (staterr & E1000_RXD_STAT_DD) अणु
				/* Descriptor Done */
				pr_info("%s[0x%03X]     %016llX %016llX ---------------- %p%s\n",
					"RWB", i,
					(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(u1->a),
					(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(u1->b),
					buffer_info->skb, next_desc);
			पूर्ण अन्यथा अणु
				pr_info("%s[0x%03X]     %016llX %016llX %016llX %p%s\n",
					"R  ", i,
					(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(u1->a),
					(अचिन्हित दीर्घ दीर्घ)le64_to_cpu(u1->b),
					(अचिन्हित दीर्घ दीर्घ)buffer_info->dma,
					buffer_info->skb, next_desc);

				अगर (netअगर_msg_pktdata(adapter) &&
				    buffer_info->skb)
					prपूर्णांक_hex_dump(KERN_INFO, "",
						       DUMP_PREFIX_ADDRESS, 16,
						       1,
						       buffer_info->skb->data,
						       adapter->rx_buffer_len,
						       true);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/**
 * e1000_desc_unused - calculate अगर we have unused descriptors
 * @ring: poपूर्णांकer to ring काष्ठा to perक्रमm calculation on
 **/
अटल पूर्णांक e1000_desc_unused(काष्ठा e1000_ring *ring)
अणु
	अगर (ring->next_to_clean > ring->next_to_use)
		वापस ring->next_to_clean - ring->next_to_use - 1;

	वापस ring->count + ring->next_to_clean - ring->next_to_use - 1;
पूर्ण

/**
 * e1000e_systim_to_hwtstamp - convert प्रणाली समय value to hw समय stamp
 * @adapter: board निजी काष्ठाure
 * @hwtstamps: समय stamp काष्ठाure to update
 * @systim: अचिन्हित 64bit प्रणाली समय value.
 *
 * Convert the प्रणाली समय value stored in the RX/TXSTMP रेजिस्टरs पूर्णांकo a
 * hwtstamp which can be used by the upper level समय stamping functions.
 *
 * The 'systim_lock' spinlock is used to protect the consistency of the
 * प्रणाली समय value. This is needed because पढ़ोing the 64 bit समय
 * value involves पढ़ोing two 32 bit रेजिस्टरs. The first पढ़ो latches the
 * value.
 **/
अटल व्योम e1000e_systim_to_hwtstamp(काष्ठा e1000_adapter *adapter,
				      काष्ठा skb_shared_hwtstamps *hwtstamps,
				      u64 systim)
अणु
	u64 ns;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&adapter->systim_lock, flags);
	ns = समयcounter_cyc2समय(&adapter->tc, systim);
	spin_unlock_irqrestore(&adapter->systim_lock, flags);

	स_रखो(hwtstamps, 0, माप(*hwtstamps));
	hwtstamps->hwtstamp = ns_to_kसमय(ns);
पूर्ण

/**
 * e1000e_rx_hwtstamp - utility function which checks क्रम Rx समय stamp
 * @adapter: board निजी काष्ठाure
 * @status: descriptor extended error and status field
 * @skb: particular skb to include समय stamp
 *
 * If the समय stamp is valid, convert it पूर्णांकo the समयcounter ns value
 * and store that result पूर्णांकo the shhwtstamps काष्ठाure which is passed
 * up the network stack.
 **/
अटल व्योम e1000e_rx_hwtstamp(काष्ठा e1000_adapter *adapter, u32 status,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u64 rxsपंचांगp;

	अगर (!(adapter->flags & FLAG_HAS_HW_TIMESTAMP) ||
	    !(status & E1000_RXDEXT_STATERR_TST) ||
	    !(er32(TSYNCRXCTL) & E1000_TSYNCRXCTL_VALID))
		वापस;

	/* The Rx समय stamp रेजिस्टरs contain the समय stamp.  No other
	 * received packet will be समय stamped until the Rx समय stamp
	 * रेजिस्टरs are पढ़ो.  Because only one packet can be समय stamped
	 * at a समय, the रेजिस्टर values must beदीर्घ to this packet and
	 * thereक्रमe none of the other additional attributes need to be
	 * compared.
	 */
	rxsपंचांगp = (u64)er32(RXSTMPL);
	rxsपंचांगp |= (u64)er32(RXSTMPH) << 32;
	e1000e_systim_to_hwtstamp(adapter, skb_hwtstamps(skb), rxsपंचांगp);

	adapter->flags2 &= ~FLAG2_CHECK_RX_HWTSTAMP;
पूर्ण

/**
 * e1000_receive_skb - helper function to handle Rx indications
 * @adapter: board निजी काष्ठाure
 * @netdev: poपूर्णांकer to netdev काष्ठा
 * @staterr: descriptor extended error and status field as written by hardware
 * @vlan: descriptor vlan field as written by hardware (no le/be conversion)
 * @skb: poपूर्णांकer to sk_buff to be indicated to stack
 **/
अटल व्योम e1000_receive_skb(काष्ठा e1000_adapter *adapter,
			      काष्ठा net_device *netdev, काष्ठा sk_buff *skb,
			      u32 staterr, __le16 vlan)
अणु
	u16 tag = le16_to_cpu(vlan);

	e1000e_rx_hwtstamp(adapter, staterr, skb);

	skb->protocol = eth_type_trans(skb, netdev);

	अगर (staterr & E1000_RXD_STAT_VP)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), tag);

	napi_gro_receive(&adapter->napi, skb);
पूर्ण

/**
 * e1000_rx_checksum - Receive Checksum Offload
 * @adapter: board निजी काष्ठाure
 * @status_err: receive descriptor status and error fields
 * @skb: socket buffer with received data
 **/
अटल व्योम e1000_rx_checksum(काष्ठा e1000_adapter *adapter, u32 status_err,
			      काष्ठा sk_buff *skb)
अणु
	u16 status = (u16)status_err;
	u8 errors = (u8)(status_err >> 24);

	skb_checksum_none_निश्चित(skb);

	/* Rx checksum disabled */
	अगर (!(adapter->netdev->features & NETIF_F_RXCSUM))
		वापस;

	/* Ignore Checksum bit is set */
	अगर (status & E1000_RXD_STAT_IXSM)
		वापस;

	/* TCP/UDP checksum error bit or IP checksum error bit is set */
	अगर (errors & (E1000_RXD_ERR_TCPE | E1000_RXD_ERR_IPE)) अणु
		/* let the stack verअगरy checksum errors */
		adapter->hw_csum_err++;
		वापस;
	पूर्ण

	/* TCP/UDP Checksum has not been calculated */
	अगर (!(status & (E1000_RXD_STAT_TCPCS | E1000_RXD_STAT_UDPCS)))
		वापस;

	/* It must be a TCP or UDP packet with a valid checksum */
	skb->ip_summed = CHECKSUM_UNNECESSARY;
	adapter->hw_csum_good++;
पूर्ण

अटल व्योम e1000e_update_rdt_wa(काष्ठा e1000_ring *rx_ring, अचिन्हित पूर्णांक i)
अणु
	काष्ठा e1000_adapter *adapter = rx_ring->adapter;
	काष्ठा e1000_hw *hw = &adapter->hw;

	__ew32_prepare(hw);
	ग_लिखोl(i, rx_ring->tail);

	अगर (unlikely(i != पढ़ोl(rx_ring->tail))) अणु
		u32 rctl = er32(RCTL);

		ew32(RCTL, rctl & ~E1000_RCTL_EN);
		e_err("ME firmware caused invalid RDT - resetting\n");
		schedule_work(&adapter->reset_task);
	पूर्ण
पूर्ण

अटल व्योम e1000e_update_tdt_wa(काष्ठा e1000_ring *tx_ring, अचिन्हित पूर्णांक i)
अणु
	काष्ठा e1000_adapter *adapter = tx_ring->adapter;
	काष्ठा e1000_hw *hw = &adapter->hw;

	__ew32_prepare(hw);
	ग_लिखोl(i, tx_ring->tail);

	अगर (unlikely(i != पढ़ोl(tx_ring->tail))) अणु
		u32 tctl = er32(TCTL);

		ew32(TCTL, tctl & ~E1000_TCTL_EN);
		e_err("ME firmware caused invalid TDT - resetting\n");
		schedule_work(&adapter->reset_task);
	पूर्ण
पूर्ण

/**
 * e1000_alloc_rx_buffers - Replace used receive buffers
 * @rx_ring: Rx descriptor ring
 * @cleaned_count: number to पुनः_स्मृतिate
 * @gfp: flags क्रम allocation
 **/
अटल व्योम e1000_alloc_rx_buffers(काष्ठा e1000_ring *rx_ring,
				   पूर्णांक cleaned_count, gfp_t gfp)
अणु
	काष्ठा e1000_adapter *adapter = rx_ring->adapter;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	जोड़ e1000_rx_desc_extended *rx_desc;
	काष्ठा e1000_buffer *buffer_info;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक bufsz = adapter->rx_buffer_len;

	i = rx_ring->next_to_use;
	buffer_info = &rx_ring->buffer_info[i];

	जबतक (cleaned_count--) अणु
		skb = buffer_info->skb;
		अगर (skb) अणु
			skb_trim(skb, 0);
			जाओ map_skb;
		पूर्ण

		skb = __netdev_alloc_skb_ip_align(netdev, bufsz, gfp);
		अगर (!skb) अणु
			/* Better luck next round */
			adapter->alloc_rx_buff_failed++;
			अवरोध;
		पूर्ण

		buffer_info->skb = skb;
map_skb:
		buffer_info->dma = dma_map_single(&pdev->dev, skb->data,
						  adapter->rx_buffer_len,
						  DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&pdev->dev, buffer_info->dma)) अणु
			dev_err(&pdev->dev, "Rx DMA map failed\n");
			adapter->rx_dma_failed++;
			अवरोध;
		पूर्ण

		rx_desc = E1000_RX_DESC_EXT(*rx_ring, i);
		rx_desc->पढ़ो.buffer_addr = cpu_to_le64(buffer_info->dma);

		अगर (unlikely(!(i & (E1000_RX_BUFFER_WRITE - 1)))) अणु
			/* Force memory ग_लिखोs to complete beक्रमe letting h/w
			 * know there are new descriptors to fetch.  (Only
			 * applicable क्रम weak-ordered memory model archs,
			 * such as IA-64).
			 */
			wmb();
			अगर (adapter->flags2 & FLAG2_PCIM2PCI_ARBITER_WA)
				e1000e_update_rdt_wa(rx_ring, i);
			अन्यथा
				ग_लिखोl(i, rx_ring->tail);
		पूर्ण
		i++;
		अगर (i == rx_ring->count)
			i = 0;
		buffer_info = &rx_ring->buffer_info[i];
	पूर्ण

	rx_ring->next_to_use = i;
पूर्ण

/**
 * e1000_alloc_rx_buffers_ps - Replace used receive buffers; packet split
 * @rx_ring: Rx descriptor ring
 * @cleaned_count: number to पुनः_स्मृतिate
 * @gfp: flags क्रम allocation
 **/
अटल व्योम e1000_alloc_rx_buffers_ps(काष्ठा e1000_ring *rx_ring,
				      पूर्णांक cleaned_count, gfp_t gfp)
अणु
	काष्ठा e1000_adapter *adapter = rx_ring->adapter;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	जोड़ e1000_rx_desc_packet_split *rx_desc;
	काष्ठा e1000_buffer *buffer_info;
	काष्ठा e1000_ps_page *ps_page;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक i, j;

	i = rx_ring->next_to_use;
	buffer_info = &rx_ring->buffer_info[i];

	जबतक (cleaned_count--) अणु
		rx_desc = E1000_RX_DESC_PS(*rx_ring, i);

		क्रम (j = 0; j < PS_PAGE_BUFFERS; j++) अणु
			ps_page = &buffer_info->ps_pages[j];
			अगर (j >= adapter->rx_ps_pages) अणु
				/* all unused desc entries get hw null ptr */
				rx_desc->पढ़ो.buffer_addr[j + 1] =
				    ~cpu_to_le64(0);
				जारी;
			पूर्ण
			अगर (!ps_page->page) अणु
				ps_page->page = alloc_page(gfp);
				अगर (!ps_page->page) अणु
					adapter->alloc_rx_buff_failed++;
					जाओ no_buffers;
				पूर्ण
				ps_page->dma = dma_map_page(&pdev->dev,
							    ps_page->page,
							    0, PAGE_SIZE,
							    DMA_FROM_DEVICE);
				अगर (dma_mapping_error(&pdev->dev,
						      ps_page->dma)) अणु
					dev_err(&adapter->pdev->dev,
						"Rx DMA page map failed\n");
					adapter->rx_dma_failed++;
					जाओ no_buffers;
				पूर्ण
			पूर्ण
			/* Refresh the desc even अगर buffer_addrs
			 * didn't change because each ग_लिखो-back
			 * erases this info.
			 */
			rx_desc->पढ़ो.buffer_addr[j + 1] =
			    cpu_to_le64(ps_page->dma);
		पूर्ण

		skb = __netdev_alloc_skb_ip_align(netdev, adapter->rx_ps_bsize0,
						  gfp);

		अगर (!skb) अणु
			adapter->alloc_rx_buff_failed++;
			अवरोध;
		पूर्ण

		buffer_info->skb = skb;
		buffer_info->dma = dma_map_single(&pdev->dev, skb->data,
						  adapter->rx_ps_bsize0,
						  DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&pdev->dev, buffer_info->dma)) अणु
			dev_err(&pdev->dev, "Rx DMA map failed\n");
			adapter->rx_dma_failed++;
			/* cleanup skb */
			dev_kमुक्त_skb_any(skb);
			buffer_info->skb = शून्य;
			अवरोध;
		पूर्ण

		rx_desc->पढ़ो.buffer_addr[0] = cpu_to_le64(buffer_info->dma);

		अगर (unlikely(!(i & (E1000_RX_BUFFER_WRITE - 1)))) अणु
			/* Force memory ग_लिखोs to complete beक्रमe letting h/w
			 * know there are new descriptors to fetch.  (Only
			 * applicable क्रम weak-ordered memory model archs,
			 * such as IA-64).
			 */
			wmb();
			अगर (adapter->flags2 & FLAG2_PCIM2PCI_ARBITER_WA)
				e1000e_update_rdt_wa(rx_ring, i << 1);
			अन्यथा
				ग_लिखोl(i << 1, rx_ring->tail);
		पूर्ण

		i++;
		अगर (i == rx_ring->count)
			i = 0;
		buffer_info = &rx_ring->buffer_info[i];
	पूर्ण

no_buffers:
	rx_ring->next_to_use = i;
पूर्ण

/**
 * e1000_alloc_jumbo_rx_buffers - Replace used jumbo receive buffers
 * @rx_ring: Rx descriptor ring
 * @cleaned_count: number of buffers to allocate this pass
 * @gfp: flags क्रम allocation
 **/

अटल व्योम e1000_alloc_jumbo_rx_buffers(काष्ठा e1000_ring *rx_ring,
					 पूर्णांक cleaned_count, gfp_t gfp)
अणु
	काष्ठा e1000_adapter *adapter = rx_ring->adapter;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	जोड़ e1000_rx_desc_extended *rx_desc;
	काष्ठा e1000_buffer *buffer_info;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक bufsz = 256 - 16;	/* क्रम skb_reserve */

	i = rx_ring->next_to_use;
	buffer_info = &rx_ring->buffer_info[i];

	जबतक (cleaned_count--) अणु
		skb = buffer_info->skb;
		अगर (skb) अणु
			skb_trim(skb, 0);
			जाओ check_page;
		पूर्ण

		skb = __netdev_alloc_skb_ip_align(netdev, bufsz, gfp);
		अगर (unlikely(!skb)) अणु
			/* Better luck next round */
			adapter->alloc_rx_buff_failed++;
			अवरोध;
		पूर्ण

		buffer_info->skb = skb;
check_page:
		/* allocate a new page अगर necessary */
		अगर (!buffer_info->page) अणु
			buffer_info->page = alloc_page(gfp);
			अगर (unlikely(!buffer_info->page)) अणु
				adapter->alloc_rx_buff_failed++;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!buffer_info->dma) अणु
			buffer_info->dma = dma_map_page(&pdev->dev,
							buffer_info->page, 0,
							PAGE_SIZE,
							DMA_FROM_DEVICE);
			अगर (dma_mapping_error(&pdev->dev, buffer_info->dma)) अणु
				adapter->alloc_rx_buff_failed++;
				अवरोध;
			पूर्ण
		पूर्ण

		rx_desc = E1000_RX_DESC_EXT(*rx_ring, i);
		rx_desc->पढ़ो.buffer_addr = cpu_to_le64(buffer_info->dma);

		अगर (unlikely(++i == rx_ring->count))
			i = 0;
		buffer_info = &rx_ring->buffer_info[i];
	पूर्ण

	अगर (likely(rx_ring->next_to_use != i)) अणु
		rx_ring->next_to_use = i;
		अगर (unlikely(i-- == 0))
			i = (rx_ring->count - 1);

		/* Force memory ग_लिखोs to complete beक्रमe letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable क्रम weak-ordered memory model archs,
		 * such as IA-64).
		 */
		wmb();
		अगर (adapter->flags2 & FLAG2_PCIM2PCI_ARBITER_WA)
			e1000e_update_rdt_wa(rx_ring, i);
		अन्यथा
			ग_लिखोl(i, rx_ring->tail);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम e1000_rx_hash(काष्ठा net_device *netdev, __le32 rss,
				 काष्ठा sk_buff *skb)
अणु
	अगर (netdev->features & NETIF_F_RXHASH)
		skb_set_hash(skb, le32_to_cpu(rss), PKT_HASH_TYPE_L3);
पूर्ण

/**
 * e1000_clean_rx_irq - Send received data up the network stack
 * @rx_ring: Rx descriptor ring
 * @work_करोne: output parameter क्रम indicating completed work
 * @work_to_करो: how many packets we can clean
 *
 * the वापस value indicates whether actual cleaning was करोne, there
 * is no guarantee that everything was cleaned
 **/
अटल bool e1000_clean_rx_irq(काष्ठा e1000_ring *rx_ring, पूर्णांक *work_करोne,
			       पूर्णांक work_to_करो)
अणु
	काष्ठा e1000_adapter *adapter = rx_ring->adapter;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	जोड़ e1000_rx_desc_extended *rx_desc, *next_rxd;
	काष्ठा e1000_buffer *buffer_info, *next_buffer;
	u32 length, staterr;
	अचिन्हित पूर्णांक i;
	पूर्णांक cleaned_count = 0;
	bool cleaned = false;
	अचिन्हित पूर्णांक total_rx_bytes = 0, total_rx_packets = 0;

	i = rx_ring->next_to_clean;
	rx_desc = E1000_RX_DESC_EXT(*rx_ring, i);
	staterr = le32_to_cpu(rx_desc->wb.upper.status_error);
	buffer_info = &rx_ring->buffer_info[i];

	जबतक (staterr & E1000_RXD_STAT_DD) अणु
		काष्ठा sk_buff *skb;

		अगर (*work_करोne >= work_to_करो)
			अवरोध;
		(*work_करोne)++;
		dma_rmb();	/* पढ़ो descriptor and rx_buffer_info after status DD */

		skb = buffer_info->skb;
		buffer_info->skb = शून्य;

		prefetch(skb->data - NET_IP_ALIGN);

		i++;
		अगर (i == rx_ring->count)
			i = 0;
		next_rxd = E1000_RX_DESC_EXT(*rx_ring, i);
		prefetch(next_rxd);

		next_buffer = &rx_ring->buffer_info[i];

		cleaned = true;
		cleaned_count++;
		dma_unmap_single(&pdev->dev, buffer_info->dma,
				 adapter->rx_buffer_len, DMA_FROM_DEVICE);
		buffer_info->dma = 0;

		length = le16_to_cpu(rx_desc->wb.upper.length);

		/* !EOP means multiple descriptors were used to store a single
		 * packet, अगर that's the हाल we need to toss it.  In fact, we
		 * need to toss every packet with the EOP bit clear and the
		 * next frame that _करोes_ have the EOP bit set, as it is by
		 * definition only a frame fragment
		 */
		अगर (unlikely(!(staterr & E1000_RXD_STAT_EOP)))
			adapter->flags2 |= FLAG2_IS_DISCARDING;

		अगर (adapter->flags2 & FLAG2_IS_DISCARDING) अणु
			/* All receives must fit पूर्णांकo a single buffer */
			e_dbg("Receive packet consumed multiple buffers\n");
			/* recycle */
			buffer_info->skb = skb;
			अगर (staterr & E1000_RXD_STAT_EOP)
				adapter->flags2 &= ~FLAG2_IS_DISCARDING;
			जाओ next_desc;
		पूर्ण

		अगर (unlikely((staterr & E1000_RXDEXT_ERR_FRAME_ERR_MASK) &&
			     !(netdev->features & NETIF_F_RXALL))) अणु
			/* recycle */
			buffer_info->skb = skb;
			जाओ next_desc;
		पूर्ण

		/* adjust length to हटाओ Ethernet CRC */
		अगर (!(adapter->flags2 & FLAG2_CRC_STRIPPING)) अणु
			/* If configured to store CRC, करोn't subtract FCS,
			 * but keep the FCS bytes out of the total_rx_bytes
			 * counter
			 */
			अगर (netdev->features & NETIF_F_RXFCS)
				total_rx_bytes -= 4;
			अन्यथा
				length -= 4;
		पूर्ण

		total_rx_bytes += length;
		total_rx_packets++;

		/* code added क्रम copyअवरोध, this should improve
		 * perक्रमmance क्रम small packets with large amounts
		 * of reassembly being करोne in the stack
		 */
		अगर (length < copyअवरोध) अणु
			काष्ठा sk_buff *new_skb =
				napi_alloc_skb(&adapter->napi, length);
			अगर (new_skb) अणु
				skb_copy_to_linear_data_offset(new_skb,
							       -NET_IP_ALIGN,
							       (skb->data -
								NET_IP_ALIGN),
							       (length +
								NET_IP_ALIGN));
				/* save the skb in buffer_info as good */
				buffer_info->skb = skb;
				skb = new_skb;
			पूर्ण
			/* अन्यथा just जारी with the old one */
		पूर्ण
		/* end copyअवरोध code */
		skb_put(skb, length);

		/* Receive Checksum Offload */
		e1000_rx_checksum(adapter, staterr, skb);

		e1000_rx_hash(netdev, rx_desc->wb.lower.hi_dword.rss, skb);

		e1000_receive_skb(adapter, netdev, skb, staterr,
				  rx_desc->wb.upper.vlan);

next_desc:
		rx_desc->wb.upper.status_error &= cpu_to_le32(~0xFF);

		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (cleaned_count >= E1000_RX_BUFFER_WRITE) अणु
			adapter->alloc_rx_buf(rx_ring, cleaned_count,
					      GFP_ATOMIC);
			cleaned_count = 0;
		पूर्ण

		/* use prefetched values */
		rx_desc = next_rxd;
		buffer_info = next_buffer;

		staterr = le32_to_cpu(rx_desc->wb.upper.status_error);
	पूर्ण
	rx_ring->next_to_clean = i;

	cleaned_count = e1000_desc_unused(rx_ring);
	अगर (cleaned_count)
		adapter->alloc_rx_buf(rx_ring, cleaned_count, GFP_ATOMIC);

	adapter->total_rx_bytes += total_rx_bytes;
	adapter->total_rx_packets += total_rx_packets;
	वापस cleaned;
पूर्ण

अटल व्योम e1000_put_txbuf(काष्ठा e1000_ring *tx_ring,
			    काष्ठा e1000_buffer *buffer_info,
			    bool drop)
अणु
	काष्ठा e1000_adapter *adapter = tx_ring->adapter;

	अगर (buffer_info->dma) अणु
		अगर (buffer_info->mapped_as_page)
			dma_unmap_page(&adapter->pdev->dev, buffer_info->dma,
				       buffer_info->length, DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_single(&adapter->pdev->dev, buffer_info->dma,
					 buffer_info->length, DMA_TO_DEVICE);
		buffer_info->dma = 0;
	पूर्ण
	अगर (buffer_info->skb) अणु
		अगर (drop)
			dev_kमुक्त_skb_any(buffer_info->skb);
		अन्यथा
			dev_consume_skb_any(buffer_info->skb);
		buffer_info->skb = शून्य;
	पूर्ण
	buffer_info->समय_stamp = 0;
पूर्ण

अटल व्योम e1000_prपूर्णांक_hw_hang(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा e1000_adapter *adapter = container_of(work,
						     काष्ठा e1000_adapter,
						     prपूर्णांक_hang_task);
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_ring *tx_ring = adapter->tx_ring;
	अचिन्हित पूर्णांक i = tx_ring->next_to_clean;
	अचिन्हित पूर्णांक eop = tx_ring->buffer_info[i].next_to_watch;
	काष्ठा e1000_tx_desc *eop_desc = E1000_TX_DESC(*tx_ring, eop);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 phy_status, phy_1000t_status, phy_ext_status;
	u16 pci_status;

	अगर (test_bit(__E1000_DOWN, &adapter->state))
		वापस;

	अगर (!adapter->tx_hang_recheck && (adapter->flags2 & FLAG2_DMA_BURST)) अणु
		/* May be block on ग_लिखो-back, flush and detect again
		 * flush pending descriptor ग_लिखोbacks to memory
		 */
		ew32(TIDV, adapter->tx_पूर्णांक_delay | E1000_TIDV_FPD);
		/* execute the ग_लिखोs immediately */
		e1e_flush();
		/* Due to rare timing issues, ग_लिखो to TIDV again to ensure
		 * the ग_लिखो is successful
		 */
		ew32(TIDV, adapter->tx_पूर्णांक_delay | E1000_TIDV_FPD);
		/* execute the ग_लिखोs immediately */
		e1e_flush();
		adapter->tx_hang_recheck = true;
		वापस;
	पूर्ण
	adapter->tx_hang_recheck = false;

	अगर (er32(TDH(0)) == er32(TDT(0))) अणु
		e_dbg("false hang detected, ignoring\n");
		वापस;
	पूर्ण

	/* Real hang detected */
	netअगर_stop_queue(netdev);

	e1e_rphy(hw, MII_BMSR, &phy_status);
	e1e_rphy(hw, MII_STAT1000, &phy_1000t_status);
	e1e_rphy(hw, MII_ESTATUS, &phy_ext_status);

	pci_पढ़ो_config_word(adapter->pdev, PCI_STATUS, &pci_status);

	/* detected Hardware unit hang */
	e_err("Detected Hardware Unit Hang:\n"
	      "  TDH                  <%x>\n"
	      "  TDT                  <%x>\n"
	      "  next_to_use          <%x>\n"
	      "  next_to_clean        <%x>\n"
	      "buffer_info[next_to_clean]:\n"
	      "  time_stamp           <%lx>\n"
	      "  next_to_watch        <%x>\n"
	      "  jiffies              <%lx>\n"
	      "  next_to_watch.status <%x>\n"
	      "MAC Status             <%x>\n"
	      "PHY Status             <%x>\n"
	      "PHY 1000BASE-T Status  <%x>\n"
	      "PHY Extended Status    <%x>\n"
	      "PCI Status             <%x>\n",
	      पढ़ोl(tx_ring->head), पढ़ोl(tx_ring->tail), tx_ring->next_to_use,
	      tx_ring->next_to_clean, tx_ring->buffer_info[eop].समय_stamp,
	      eop, jअगरfies, eop_desc->upper.fields.status, er32(STATUS),
	      phy_status, phy_1000t_status, phy_ext_status, pci_status);

	e1000e_dump(adapter);

	/* Suggest workaround क्रम known h/w issue */
	अगर ((hw->mac.type == e1000_pchlan) && (er32(CTRL) & E1000_CTRL_TFCE))
		e_err("Try turning off Tx pause (flow control) via ethtool\n");
पूर्ण

/**
 * e1000e_tx_hwtstamp_work - check क्रम Tx समय stamp
 * @work: poपूर्णांकer to work काष्ठा
 *
 * This work function polls the TSYNCTXCTL valid bit to determine when a
 * बारtamp has been taken क्रम the current stored skb.  The बारtamp must
 * be क्रम this skb because only one such packet is allowed in the queue.
 */
अटल व्योम e1000e_tx_hwtstamp_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा e1000_adapter *adapter = container_of(work, काष्ठा e1000_adapter,
						     tx_hwtstamp_work);
	काष्ठा e1000_hw *hw = &adapter->hw;

	अगर (er32(TSYNCTXCTL) & E1000_TSYNCTXCTL_VALID) अणु
		काष्ठा sk_buff *skb = adapter->tx_hwtstamp_skb;
		काष्ठा skb_shared_hwtstamps shhwtstamps;
		u64 txsपंचांगp;

		txsपंचांगp = er32(TXSTMPL);
		txsपंचांगp |= (u64)er32(TXSTMPH) << 32;

		e1000e_systim_to_hwtstamp(adapter, &shhwtstamps, txsपंचांगp);

		/* Clear the global tx_hwtstamp_skb poपूर्णांकer and क्रमce ग_लिखोs
		 * prior to notअगरying the stack of a Tx बारtamp.
		 */
		adapter->tx_hwtstamp_skb = शून्य;
		wmb(); /* क्रमce ग_लिखो prior to skb_tstamp_tx */

		skb_tstamp_tx(skb, &shhwtstamps);
		dev_consume_skb_any(skb);
	पूर्ण अन्यथा अगर (समय_after(jअगरfies, adapter->tx_hwtstamp_start
			      + adapter->tx_समयout_factor * HZ)) अणु
		dev_kमुक्त_skb_any(adapter->tx_hwtstamp_skb);
		adapter->tx_hwtstamp_skb = शून्य;
		adapter->tx_hwtstamp_समयouts++;
		e_warn("clearing Tx timestamp hang\n");
	पूर्ण अन्यथा अणु
		/* reschedule to check later */
		schedule_work(&adapter->tx_hwtstamp_work);
	पूर्ण
पूर्ण

/**
 * e1000_clean_tx_irq - Reclaim resources after transmit completes
 * @tx_ring: Tx descriptor ring
 *
 * the वापस value indicates whether actual cleaning was करोne, there
 * is no guarantee that everything was cleaned
 **/
अटल bool e1000_clean_tx_irq(काष्ठा e1000_ring *tx_ring)
अणु
	काष्ठा e1000_adapter *adapter = tx_ring->adapter;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_tx_desc *tx_desc, *eop_desc;
	काष्ठा e1000_buffer *buffer_info;
	अचिन्हित पूर्णांक i, eop;
	अचिन्हित पूर्णांक count = 0;
	अचिन्हित पूर्णांक total_tx_bytes = 0, total_tx_packets = 0;
	अचिन्हित पूर्णांक bytes_compl = 0, pkts_compl = 0;

	i = tx_ring->next_to_clean;
	eop = tx_ring->buffer_info[i].next_to_watch;
	eop_desc = E1000_TX_DESC(*tx_ring, eop);

	जबतक ((eop_desc->upper.data & cpu_to_le32(E1000_TXD_STAT_DD)) &&
	       (count < tx_ring->count)) अणु
		bool cleaned = false;

		dma_rmb();		/* पढ़ो buffer_info after eop_desc */
		क्रम (; !cleaned; count++) अणु
			tx_desc = E1000_TX_DESC(*tx_ring, i);
			buffer_info = &tx_ring->buffer_info[i];
			cleaned = (i == eop);

			अगर (cleaned) अणु
				total_tx_packets += buffer_info->segs;
				total_tx_bytes += buffer_info->bytecount;
				अगर (buffer_info->skb) अणु
					bytes_compl += buffer_info->skb->len;
					pkts_compl++;
				पूर्ण
			पूर्ण

			e1000_put_txbuf(tx_ring, buffer_info, false);
			tx_desc->upper.data = 0;

			i++;
			अगर (i == tx_ring->count)
				i = 0;
		पूर्ण

		अगर (i == tx_ring->next_to_use)
			अवरोध;
		eop = tx_ring->buffer_info[i].next_to_watch;
		eop_desc = E1000_TX_DESC(*tx_ring, eop);
	पूर्ण

	tx_ring->next_to_clean = i;

	netdev_completed_queue(netdev, pkts_compl, bytes_compl);

#घोषणा TX_WAKE_THRESHOLD 32
	अगर (count && netअगर_carrier_ok(netdev) &&
	    e1000_desc_unused(tx_ring) >= TX_WAKE_THRESHOLD) अणु
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();

		अगर (netअगर_queue_stopped(netdev) &&
		    !(test_bit(__E1000_DOWN, &adapter->state))) अणु
			netअगर_wake_queue(netdev);
			++adapter->restart_queue;
		पूर्ण
	पूर्ण

	अगर (adapter->detect_tx_hung) अणु
		/* Detect a transmit hang in hardware, this serializes the
		 * check with the clearing of समय_stamp and movement of i
		 */
		adapter->detect_tx_hung = false;
		अगर (tx_ring->buffer_info[i].समय_stamp &&
		    समय_after(jअगरfies, tx_ring->buffer_info[i].समय_stamp
			       + (adapter->tx_समयout_factor * HZ)) &&
		    !(er32(STATUS) & E1000_STATUS_TXOFF))
			schedule_work(&adapter->prपूर्णांक_hang_task);
		अन्यथा
			adapter->tx_hang_recheck = false;
	पूर्ण
	adapter->total_tx_bytes += total_tx_bytes;
	adapter->total_tx_packets += total_tx_packets;
	वापस count < tx_ring->count;
पूर्ण

/**
 * e1000_clean_rx_irq_ps - Send received data up the network stack; packet split
 * @rx_ring: Rx descriptor ring
 * @work_करोne: output parameter क्रम indicating completed work
 * @work_to_करो: how many packets we can clean
 *
 * the वापस value indicates whether actual cleaning was करोne, there
 * is no guarantee that everything was cleaned
 **/
अटल bool e1000_clean_rx_irq_ps(काष्ठा e1000_ring *rx_ring, पूर्णांक *work_करोne,
				  पूर्णांक work_to_करो)
अणु
	काष्ठा e1000_adapter *adapter = rx_ring->adapter;
	काष्ठा e1000_hw *hw = &adapter->hw;
	जोड़ e1000_rx_desc_packet_split *rx_desc, *next_rxd;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा e1000_buffer *buffer_info, *next_buffer;
	काष्ठा e1000_ps_page *ps_page;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक i, j;
	u32 length, staterr;
	पूर्णांक cleaned_count = 0;
	bool cleaned = false;
	अचिन्हित पूर्णांक total_rx_bytes = 0, total_rx_packets = 0;

	i = rx_ring->next_to_clean;
	rx_desc = E1000_RX_DESC_PS(*rx_ring, i);
	staterr = le32_to_cpu(rx_desc->wb.middle.status_error);
	buffer_info = &rx_ring->buffer_info[i];

	जबतक (staterr & E1000_RXD_STAT_DD) अणु
		अगर (*work_करोne >= work_to_करो)
			अवरोध;
		(*work_करोne)++;
		skb = buffer_info->skb;
		dma_rmb();	/* पढ़ो descriptor and rx_buffer_info after status DD */

		/* in the packet split हाल this is header only */
		prefetch(skb->data - NET_IP_ALIGN);

		i++;
		अगर (i == rx_ring->count)
			i = 0;
		next_rxd = E1000_RX_DESC_PS(*rx_ring, i);
		prefetch(next_rxd);

		next_buffer = &rx_ring->buffer_info[i];

		cleaned = true;
		cleaned_count++;
		dma_unmap_single(&pdev->dev, buffer_info->dma,
				 adapter->rx_ps_bsize0, DMA_FROM_DEVICE);
		buffer_info->dma = 0;

		/* see !EOP comment in other Rx routine */
		अगर (!(staterr & E1000_RXD_STAT_EOP))
			adapter->flags2 |= FLAG2_IS_DISCARDING;

		अगर (adapter->flags2 & FLAG2_IS_DISCARDING) अणु
			e_dbg("Packet Split buffers didn't pick up the full packet\n");
			dev_kमुक्त_skb_irq(skb);
			अगर (staterr & E1000_RXD_STAT_EOP)
				adapter->flags2 &= ~FLAG2_IS_DISCARDING;
			जाओ next_desc;
		पूर्ण

		अगर (unlikely((staterr & E1000_RXDEXT_ERR_FRAME_ERR_MASK) &&
			     !(netdev->features & NETIF_F_RXALL))) अणु
			dev_kमुक्त_skb_irq(skb);
			जाओ next_desc;
		पूर्ण

		length = le16_to_cpu(rx_desc->wb.middle.length0);

		अगर (!length) अणु
			e_dbg("Last part of the packet spanning multiple descriptors\n");
			dev_kमुक्त_skb_irq(skb);
			जाओ next_desc;
		पूर्ण

		/* Good Receive */
		skb_put(skb, length);

		अणु
			/* this looks ugly, but it seems compiler issues make
			 * it more efficient than reusing j
			 */
			पूर्णांक l1 = le16_to_cpu(rx_desc->wb.upper.length[0]);

			/* page alloc/put takes too दीर्घ and effects small
			 * packet throughput, so unsplit small packets and
			 * save the alloc/put only valid in softirq (napi)
			 * context to call kmap_*
			 */
			अगर (l1 && (l1 <= copyअवरोध) &&
			    ((length + l1) <= adapter->rx_ps_bsize0)) अणु
				u8 *vaddr;

				ps_page = &buffer_info->ps_pages[0];

				/* there is no करोcumentation about how to call
				 * kmap_atomic, so we can't hold the mapping
				 * very दीर्घ
				 */
				dma_sync_single_क्रम_cpu(&pdev->dev,
							ps_page->dma,
							PAGE_SIZE,
							DMA_FROM_DEVICE);
				vaddr = kmap_atomic(ps_page->page);
				स_नकल(skb_tail_poपूर्णांकer(skb), vaddr, l1);
				kunmap_atomic(vaddr);
				dma_sync_single_क्रम_device(&pdev->dev,
							   ps_page->dma,
							   PAGE_SIZE,
							   DMA_FROM_DEVICE);

				/* हटाओ the CRC */
				अगर (!(adapter->flags2 & FLAG2_CRC_STRIPPING)) अणु
					अगर (!(netdev->features & NETIF_F_RXFCS))
						l1 -= 4;
				पूर्ण

				skb_put(skb, l1);
				जाओ copyकरोne;
			पूर्ण	/* अगर */
		पूर्ण

		क्रम (j = 0; j < PS_PAGE_BUFFERS; j++) अणु
			length = le16_to_cpu(rx_desc->wb.upper.length[j]);
			अगर (!length)
				अवरोध;

			ps_page = &buffer_info->ps_pages[j];
			dma_unmap_page(&pdev->dev, ps_page->dma, PAGE_SIZE,
				       DMA_FROM_DEVICE);
			ps_page->dma = 0;
			skb_fill_page_desc(skb, j, ps_page->page, 0, length);
			ps_page->page = शून्य;
			skb->len += length;
			skb->data_len += length;
			skb->truesize += PAGE_SIZE;
		पूर्ण

		/* strip the ethernet crc, problem is we're using pages now so
		 * this whole operation can get a little cpu पूर्णांकensive
		 */
		अगर (!(adapter->flags2 & FLAG2_CRC_STRIPPING)) अणु
			अगर (!(netdev->features & NETIF_F_RXFCS))
				pskb_trim(skb, skb->len - 4);
		पूर्ण

copyकरोne:
		total_rx_bytes += skb->len;
		total_rx_packets++;

		e1000_rx_checksum(adapter, staterr, skb);

		e1000_rx_hash(netdev, rx_desc->wb.lower.hi_dword.rss, skb);

		अगर (rx_desc->wb.upper.header_status &
		    cpu_to_le16(E1000_RXDPS_HDRSTAT_HDRSP))
			adapter->rx_hdr_split++;

		e1000_receive_skb(adapter, netdev, skb, staterr,
				  rx_desc->wb.middle.vlan);

next_desc:
		rx_desc->wb.middle.status_error &= cpu_to_le32(~0xFF);
		buffer_info->skb = शून्य;

		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (cleaned_count >= E1000_RX_BUFFER_WRITE) अणु
			adapter->alloc_rx_buf(rx_ring, cleaned_count,
					      GFP_ATOMIC);
			cleaned_count = 0;
		पूर्ण

		/* use prefetched values */
		rx_desc = next_rxd;
		buffer_info = next_buffer;

		staterr = le32_to_cpu(rx_desc->wb.middle.status_error);
	पूर्ण
	rx_ring->next_to_clean = i;

	cleaned_count = e1000_desc_unused(rx_ring);
	अगर (cleaned_count)
		adapter->alloc_rx_buf(rx_ring, cleaned_count, GFP_ATOMIC);

	adapter->total_rx_bytes += total_rx_bytes;
	adapter->total_rx_packets += total_rx_packets;
	वापस cleaned;
पूर्ण

अटल व्योम e1000_consume_page(काष्ठा e1000_buffer *bi, काष्ठा sk_buff *skb,
			       u16 length)
अणु
	bi->page = शून्य;
	skb->len += length;
	skb->data_len += length;
	skb->truesize += PAGE_SIZE;
पूर्ण

/**
 * e1000_clean_jumbo_rx_irq - Send received data up the network stack; legacy
 * @rx_ring: Rx descriptor ring
 * @work_करोne: output parameter क्रम indicating completed work
 * @work_to_करो: how many packets we can clean
 *
 * the वापस value indicates whether actual cleaning was करोne, there
 * is no guarantee that everything was cleaned
 **/
अटल bool e1000_clean_jumbo_rx_irq(काष्ठा e1000_ring *rx_ring, पूर्णांक *work_करोne,
				     पूर्णांक work_to_करो)
अणु
	काष्ठा e1000_adapter *adapter = rx_ring->adapter;
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा pci_dev *pdev = adapter->pdev;
	जोड़ e1000_rx_desc_extended *rx_desc, *next_rxd;
	काष्ठा e1000_buffer *buffer_info, *next_buffer;
	u32 length, staterr;
	अचिन्हित पूर्णांक i;
	पूर्णांक cleaned_count = 0;
	bool cleaned = false;
	अचिन्हित पूर्णांक total_rx_bytes = 0, total_rx_packets = 0;
	काष्ठा skb_shared_info *shinfo;

	i = rx_ring->next_to_clean;
	rx_desc = E1000_RX_DESC_EXT(*rx_ring, i);
	staterr = le32_to_cpu(rx_desc->wb.upper.status_error);
	buffer_info = &rx_ring->buffer_info[i];

	जबतक (staterr & E1000_RXD_STAT_DD) अणु
		काष्ठा sk_buff *skb;

		अगर (*work_करोne >= work_to_करो)
			अवरोध;
		(*work_करोne)++;
		dma_rmb();	/* पढ़ो descriptor and rx_buffer_info after status DD */

		skb = buffer_info->skb;
		buffer_info->skb = शून्य;

		++i;
		अगर (i == rx_ring->count)
			i = 0;
		next_rxd = E1000_RX_DESC_EXT(*rx_ring, i);
		prefetch(next_rxd);

		next_buffer = &rx_ring->buffer_info[i];

		cleaned = true;
		cleaned_count++;
		dma_unmap_page(&pdev->dev, buffer_info->dma, PAGE_SIZE,
			       DMA_FROM_DEVICE);
		buffer_info->dma = 0;

		length = le16_to_cpu(rx_desc->wb.upper.length);

		/* errors is only valid क्रम DD + EOP descriptors */
		अगर (unlikely((staterr & E1000_RXD_STAT_EOP) &&
			     ((staterr & E1000_RXDEXT_ERR_FRAME_ERR_MASK) &&
			      !(netdev->features & NETIF_F_RXALL)))) अणु
			/* recycle both page and skb */
			buffer_info->skb = skb;
			/* an error means any chain goes out the winकरोw too */
			अगर (rx_ring->rx_skb_top)
				dev_kमुक्त_skb_irq(rx_ring->rx_skb_top);
			rx_ring->rx_skb_top = शून्य;
			जाओ next_desc;
		पूर्ण
#घोषणा rxtop (rx_ring->rx_skb_top)
		अगर (!(staterr & E1000_RXD_STAT_EOP)) अणु
			/* this descriptor is only the beginning (or middle) */
			अगर (!rxtop) अणु
				/* this is the beginning of a chain */
				rxtop = skb;
				skb_fill_page_desc(rxtop, 0, buffer_info->page,
						   0, length);
			पूर्ण अन्यथा अणु
				/* this is the middle of a chain */
				shinfo = skb_shinfo(rxtop);
				skb_fill_page_desc(rxtop, shinfo->nr_frags,
						   buffer_info->page, 0,
						   length);
				/* re-use the skb, only consumed the page */
				buffer_info->skb = skb;
			पूर्ण
			e1000_consume_page(buffer_info, rxtop, length);
			जाओ next_desc;
		पूर्ण अन्यथा अणु
			अगर (rxtop) अणु
				/* end of the chain */
				shinfo = skb_shinfo(rxtop);
				skb_fill_page_desc(rxtop, shinfo->nr_frags,
						   buffer_info->page, 0,
						   length);
				/* re-use the current skb, we only consumed the
				 * page
				 */
				buffer_info->skb = skb;
				skb = rxtop;
				rxtop = शून्य;
				e1000_consume_page(buffer_info, skb, length);
			पूर्ण अन्यथा अणु
				/* no chain, got EOP, this buf is the packet
				 * copyअवरोध to save the put_page/alloc_page
				 */
				अगर (length <= copyअवरोध &&
				    skb_tailroom(skb) >= length) अणु
					u8 *vaddr;
					vaddr = kmap_atomic(buffer_info->page);
					स_नकल(skb_tail_poपूर्णांकer(skb), vaddr,
					       length);
					kunmap_atomic(vaddr);
					/* re-use the page, so करोn't erase
					 * buffer_info->page
					 */
					skb_put(skb, length);
				पूर्ण अन्यथा अणु
					skb_fill_page_desc(skb, 0,
							   buffer_info->page, 0,
							   length);
					e1000_consume_page(buffer_info, skb,
							   length);
				पूर्ण
			पूर्ण
		पूर्ण

		/* Receive Checksum Offload */
		e1000_rx_checksum(adapter, staterr, skb);

		e1000_rx_hash(netdev, rx_desc->wb.lower.hi_dword.rss, skb);

		/* probably a little skewed due to removing CRC */
		total_rx_bytes += skb->len;
		total_rx_packets++;

		/* eth type trans needs skb->data to poपूर्णांक to something */
		अगर (!pskb_may_pull(skb, ETH_HLEN)) अणु
			e_err("pskb_may_pull failed.\n");
			dev_kमुक्त_skb_irq(skb);
			जाओ next_desc;
		पूर्ण

		e1000_receive_skb(adapter, netdev, skb, staterr,
				  rx_desc->wb.upper.vlan);

next_desc:
		rx_desc->wb.upper.status_error &= cpu_to_le32(~0xFF);

		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (unlikely(cleaned_count >= E1000_RX_BUFFER_WRITE)) अणु
			adapter->alloc_rx_buf(rx_ring, cleaned_count,
					      GFP_ATOMIC);
			cleaned_count = 0;
		पूर्ण

		/* use prefetched values */
		rx_desc = next_rxd;
		buffer_info = next_buffer;

		staterr = le32_to_cpu(rx_desc->wb.upper.status_error);
	पूर्ण
	rx_ring->next_to_clean = i;

	cleaned_count = e1000_desc_unused(rx_ring);
	अगर (cleaned_count)
		adapter->alloc_rx_buf(rx_ring, cleaned_count, GFP_ATOMIC);

	adapter->total_rx_bytes += total_rx_bytes;
	adapter->total_rx_packets += total_rx_packets;
	वापस cleaned;
पूर्ण

/**
 * e1000_clean_rx_ring - Free Rx Buffers per Queue
 * @rx_ring: Rx descriptor ring
 **/
अटल व्योम e1000_clean_rx_ring(काष्ठा e1000_ring *rx_ring)
अणु
	काष्ठा e1000_adapter *adapter = rx_ring->adapter;
	काष्ठा e1000_buffer *buffer_info;
	काष्ठा e1000_ps_page *ps_page;
	काष्ठा pci_dev *pdev = adapter->pdev;
	अचिन्हित पूर्णांक i, j;

	/* Free all the Rx ring sk_buffs */
	क्रम (i = 0; i < rx_ring->count; i++) अणु
		buffer_info = &rx_ring->buffer_info[i];
		अगर (buffer_info->dma) अणु
			अगर (adapter->clean_rx == e1000_clean_rx_irq)
				dma_unmap_single(&pdev->dev, buffer_info->dma,
						 adapter->rx_buffer_len,
						 DMA_FROM_DEVICE);
			अन्यथा अगर (adapter->clean_rx == e1000_clean_jumbo_rx_irq)
				dma_unmap_page(&pdev->dev, buffer_info->dma,
					       PAGE_SIZE, DMA_FROM_DEVICE);
			अन्यथा अगर (adapter->clean_rx == e1000_clean_rx_irq_ps)
				dma_unmap_single(&pdev->dev, buffer_info->dma,
						 adapter->rx_ps_bsize0,
						 DMA_FROM_DEVICE);
			buffer_info->dma = 0;
		पूर्ण

		अगर (buffer_info->page) अणु
			put_page(buffer_info->page);
			buffer_info->page = शून्य;
		पूर्ण

		अगर (buffer_info->skb) अणु
			dev_kमुक्त_skb(buffer_info->skb);
			buffer_info->skb = शून्य;
		पूर्ण

		क्रम (j = 0; j < PS_PAGE_BUFFERS; j++) अणु
			ps_page = &buffer_info->ps_pages[j];
			अगर (!ps_page->page)
				अवरोध;
			dma_unmap_page(&pdev->dev, ps_page->dma, PAGE_SIZE,
				       DMA_FROM_DEVICE);
			ps_page->dma = 0;
			put_page(ps_page->page);
			ps_page->page = शून्य;
		पूर्ण
	पूर्ण

	/* there also may be some cached data from a chained receive */
	अगर (rx_ring->rx_skb_top) अणु
		dev_kमुक्त_skb(rx_ring->rx_skb_top);
		rx_ring->rx_skb_top = शून्य;
	पूर्ण

	/* Zero out the descriptor ring */
	स_रखो(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
	adapter->flags2 &= ~FLAG2_IS_DISCARDING;
पूर्ण

अटल व्योम e1000e_करोwnshअगरt_workaround(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा e1000_adapter *adapter = container_of(work,
						     काष्ठा e1000_adapter,
						     करोwnshअगरt_task);

	अगर (test_bit(__E1000_DOWN, &adapter->state))
		वापस;

	e1000e_gig_करोwnshअगरt_workaround_ich8lan(&adapter->hw);
पूर्ण

/**
 * e1000_पूर्णांकr_msi - Interrupt Handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a network पूर्णांकerface device काष्ठाure
 **/
अटल irqवापस_t e1000_पूर्णांकr_msi(पूर्णांक __always_unused irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 icr = er32(ICR);

	/* पढ़ो ICR disables पूर्णांकerrupts using IAM */
	अगर (icr & E1000_ICR_LSC) अणु
		hw->mac.get_link_status = true;
		/* ICH8 workaround-- Call gig speed drop workaround on cable
		 * disconnect (LSC) beक्रमe accessing any PHY रेजिस्टरs
		 */
		अगर ((adapter->flags & FLAG_LSC_GIG_SPEED_DROP) &&
		    (!(er32(STATUS) & E1000_STATUS_LU)))
			schedule_work(&adapter->करोwnshअगरt_task);

		/* 80003ES2LAN workaround-- For packet buffer work-around on
		 * link करोwn event; disable receives here in the ISR and reset
		 * adapter in watchकरोg
		 */
		अगर (netअगर_carrier_ok(netdev) &&
		    adapter->flags & FLAG_RX_NEEDS_RESTART) अणु
			/* disable receives */
			u32 rctl = er32(RCTL);

			ew32(RCTL, rctl & ~E1000_RCTL_EN);
			adapter->flags |= FLAG_RESTART_NOW;
		पूर्ण
		/* guard against पूर्णांकerrupt when we're going करोwn */
		अगर (!test_bit(__E1000_DOWN, &adapter->state))
			mod_समयr(&adapter->watchकरोg_समयr, jअगरfies + 1);
	पूर्ण

	/* Reset on uncorrectable ECC error */
	अगर ((icr & E1000_ICR_ECCER) && (hw->mac.type >= e1000_pch_lpt)) अणु
		u32 pbeccsts = er32(PBECCSTS);

		adapter->corr_errors +=
		    pbeccsts & E1000_PBECCSTS_CORR_ERR_CNT_MASK;
		adapter->uncorr_errors +=
		    (pbeccsts & E1000_PBECCSTS_UNCORR_ERR_CNT_MASK) >>
		    E1000_PBECCSTS_UNCORR_ERR_CNT_SHIFT;

		/* Do the reset outside of पूर्णांकerrupt context */
		schedule_work(&adapter->reset_task);

		/* वापस immediately since reset is imminent */
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (napi_schedule_prep(&adapter->napi)) अणु
		adapter->total_tx_bytes = 0;
		adapter->total_tx_packets = 0;
		adapter->total_rx_bytes = 0;
		adapter->total_rx_packets = 0;
		__napi_schedule(&adapter->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * e1000_पूर्णांकr - Interrupt Handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a network पूर्णांकerface device काष्ठाure
 **/
अटल irqवापस_t e1000_पूर्णांकr(पूर्णांक __always_unused irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rctl, icr = er32(ICR);

	अगर (!icr || test_bit(__E1000_DOWN, &adapter->state))
		वापस IRQ_NONE;	/* Not our पूर्णांकerrupt */

	/* IMS will not स्वतः-mask अगर INT_ASSERTED is not set, and अगर it is
	 * not set, then the adapter didn't send an पूर्णांकerrupt
	 */
	अगर (!(icr & E1000_ICR_INT_ASSERTED))
		वापस IRQ_NONE;

	/* Interrupt Auto-Mask...upon पढ़ोing ICR,
	 * पूर्णांकerrupts are masked.  No need क्रम the
	 * IMC ग_लिखो
	 */

	अगर (icr & E1000_ICR_LSC) अणु
		hw->mac.get_link_status = true;
		/* ICH8 workaround-- Call gig speed drop workaround on cable
		 * disconnect (LSC) beक्रमe accessing any PHY रेजिस्टरs
		 */
		अगर ((adapter->flags & FLAG_LSC_GIG_SPEED_DROP) &&
		    (!(er32(STATUS) & E1000_STATUS_LU)))
			schedule_work(&adapter->करोwnshअगरt_task);

		/* 80003ES2LAN workaround--
		 * For packet buffer work-around on link करोwn event;
		 * disable receives here in the ISR and
		 * reset adapter in watchकरोg
		 */
		अगर (netअगर_carrier_ok(netdev) &&
		    (adapter->flags & FLAG_RX_NEEDS_RESTART)) अणु
			/* disable receives */
			rctl = er32(RCTL);
			ew32(RCTL, rctl & ~E1000_RCTL_EN);
			adapter->flags |= FLAG_RESTART_NOW;
		पूर्ण
		/* guard against पूर्णांकerrupt when we're going करोwn */
		अगर (!test_bit(__E1000_DOWN, &adapter->state))
			mod_समयr(&adapter->watchकरोg_समयr, jअगरfies + 1);
	पूर्ण

	/* Reset on uncorrectable ECC error */
	अगर ((icr & E1000_ICR_ECCER) && (hw->mac.type >= e1000_pch_lpt)) अणु
		u32 pbeccsts = er32(PBECCSTS);

		adapter->corr_errors +=
		    pbeccsts & E1000_PBECCSTS_CORR_ERR_CNT_MASK;
		adapter->uncorr_errors +=
		    (pbeccsts & E1000_PBECCSTS_UNCORR_ERR_CNT_MASK) >>
		    E1000_PBECCSTS_UNCORR_ERR_CNT_SHIFT;

		/* Do the reset outside of पूर्णांकerrupt context */
		schedule_work(&adapter->reset_task);

		/* वापस immediately since reset is imminent */
		वापस IRQ_HANDLED;
	पूर्ण

	अगर (napi_schedule_prep(&adapter->napi)) अणु
		adapter->total_tx_bytes = 0;
		adapter->total_tx_packets = 0;
		adapter->total_rx_bytes = 0;
		adapter->total_rx_packets = 0;
		__napi_schedule(&adapter->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t e1000_msix_other(पूर्णांक __always_unused irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 icr = er32(ICR);

	अगर (icr & adapter->eiac_mask)
		ew32(ICS, (icr & adapter->eiac_mask));

	अगर (icr & E1000_ICR_LSC) अणु
		hw->mac.get_link_status = true;
		/* guard against पूर्णांकerrupt when we're going करोwn */
		अगर (!test_bit(__E1000_DOWN, &adapter->state))
			mod_समयr(&adapter->watchकरोg_समयr, jअगरfies + 1);
	पूर्ण

	अगर (!test_bit(__E1000_DOWN, &adapter->state))
		ew32(IMS, E1000_IMS_OTHER | IMS_OTHER_MASK);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t e1000_पूर्णांकr_msix_tx(पूर्णांक __always_unused irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_ring *tx_ring = adapter->tx_ring;

	adapter->total_tx_bytes = 0;
	adapter->total_tx_packets = 0;

	अगर (!e1000_clean_tx_irq(tx_ring))
		/* Ring was not completely cleaned, so fire another पूर्णांकerrupt */
		ew32(ICS, tx_ring->ims_val);

	अगर (!test_bit(__E1000_DOWN, &adapter->state))
		ew32(IMS, adapter->tx_ring->ims_val);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t e1000_पूर्णांकr_msix_rx(पूर्णांक __always_unused irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_ring *rx_ring = adapter->rx_ring;

	/* Write the ITR value calculated at the end of the
	 * previous पूर्णांकerrupt.
	 */
	अगर (rx_ring->set_itr) अणु
		u32 itr = rx_ring->itr_val ?
			  1000000000 / (rx_ring->itr_val * 256) : 0;

		ग_लिखोl(itr, rx_ring->itr_रेजिस्टर);
		rx_ring->set_itr = 0;
	पूर्ण

	अगर (napi_schedule_prep(&adapter->napi)) अणु
		adapter->total_rx_bytes = 0;
		adapter->total_rx_packets = 0;
		__napi_schedule(&adapter->napi);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/**
 * e1000_configure_msix - Configure MSI-X hardware
 * @adapter: board निजी काष्ठाure
 *
 * e1000_configure_msix sets up the hardware to properly
 * generate MSI-X पूर्णांकerrupts.
 **/
अटल व्योम e1000_configure_msix(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_ring *rx_ring = adapter->rx_ring;
	काष्ठा e1000_ring *tx_ring = adapter->tx_ring;
	पूर्णांक vector = 0;
	u32 ctrl_ext, ivar = 0;

	adapter->eiac_mask = 0;

	/* Workaround issue with spurious पूर्णांकerrupts on 82574 in MSI-X mode */
	अगर (hw->mac.type == e1000_82574) अणु
		u32 rfctl = er32(RFCTL);

		rfctl |= E1000_RFCTL_ACK_DIS;
		ew32(RFCTL, rfctl);
	पूर्ण

	/* Configure Rx vector */
	rx_ring->ims_val = E1000_IMS_RXQ0;
	adapter->eiac_mask |= rx_ring->ims_val;
	अगर (rx_ring->itr_val)
		ग_लिखोl(1000000000 / (rx_ring->itr_val * 256),
		       rx_ring->itr_रेजिस्टर);
	अन्यथा
		ग_लिखोl(1, rx_ring->itr_रेजिस्टर);
	ivar = E1000_IVAR_INT_ALLOC_VALID | vector;

	/* Configure Tx vector */
	tx_ring->ims_val = E1000_IMS_TXQ0;
	vector++;
	अगर (tx_ring->itr_val)
		ग_लिखोl(1000000000 / (tx_ring->itr_val * 256),
		       tx_ring->itr_रेजिस्टर);
	अन्यथा
		ग_लिखोl(1, tx_ring->itr_रेजिस्टर);
	adapter->eiac_mask |= tx_ring->ims_val;
	ivar |= ((E1000_IVAR_INT_ALLOC_VALID | vector) << 8);

	/* set vector क्रम Other Causes, e.g. link changes */
	vector++;
	ivar |= ((E1000_IVAR_INT_ALLOC_VALID | vector) << 16);
	अगर (rx_ring->itr_val)
		ग_लिखोl(1000000000 / (rx_ring->itr_val * 256),
		       hw->hw_addr + E1000_EITR_82574(vector));
	अन्यथा
		ग_लिखोl(1, hw->hw_addr + E1000_EITR_82574(vector));

	/* Cause Tx पूर्णांकerrupts on every ग_लिखो back */
	ivar |= BIT(31);

	ew32(IVAR, ivar);

	/* enable MSI-X PBA support */
	ctrl_ext = er32(CTRL_EXT) & ~E1000_CTRL_EXT_IAME;
	ctrl_ext |= E1000_CTRL_EXT_PBA_CLR | E1000_CTRL_EXT_EIAME;
	ew32(CTRL_EXT, ctrl_ext);
	e1e_flush();
पूर्ण

व्योम e1000e_reset_पूर्णांकerrupt_capability(काष्ठा e1000_adapter *adapter)
अणु
	अगर (adapter->msix_entries) अणु
		pci_disable_msix(adapter->pdev);
		kमुक्त(adapter->msix_entries);
		adapter->msix_entries = शून्य;
	पूर्ण अन्यथा अगर (adapter->flags & FLAG_MSI_ENABLED) अणु
		pci_disable_msi(adapter->pdev);
		adapter->flags &= ~FLAG_MSI_ENABLED;
	पूर्ण
पूर्ण

/**
 * e1000e_set_पूर्णांकerrupt_capability - set MSI or MSI-X अगर supported
 * @adapter: board निजी काष्ठाure
 *
 * Attempt to configure पूर्णांकerrupts using the best available
 * capabilities of the hardware and kernel.
 **/
व्योम e1000e_set_पूर्णांकerrupt_capability(काष्ठा e1000_adapter *adapter)
अणु
	पूर्णांक err;
	पूर्णांक i;

	चयन (adapter->पूर्णांक_mode) अणु
	हाल E1000E_INT_MODE_MSIX:
		अगर (adapter->flags & FLAG_HAS_MSIX) अणु
			adapter->num_vectors = 3; /* RxQ0, TxQ0 and other */
			adapter->msix_entries = kसुस्मृति(adapter->num_vectors,
							माप(काष्ठा
							       msix_entry),
							GFP_KERNEL);
			अगर (adapter->msix_entries) अणु
				काष्ठा e1000_adapter *a = adapter;

				क्रम (i = 0; i < adapter->num_vectors; i++)
					adapter->msix_entries[i].entry = i;

				err = pci_enable_msix_range(a->pdev,
							    a->msix_entries,
							    a->num_vectors,
							    a->num_vectors);
				अगर (err > 0)
					वापस;
			पूर्ण
			/* MSI-X failed, so fall through and try MSI */
			e_err("Failed to initialize MSI-X interrupts.  Falling back to MSI interrupts.\n");
			e1000e_reset_पूर्णांकerrupt_capability(adapter);
		पूर्ण
		adapter->पूर्णांक_mode = E1000E_INT_MODE_MSI;
		fallthrough;
	हाल E1000E_INT_MODE_MSI:
		अगर (!pci_enable_msi(adapter->pdev)) अणु
			adapter->flags |= FLAG_MSI_ENABLED;
		पूर्ण अन्यथा अणु
			adapter->पूर्णांक_mode = E1000E_INT_MODE_LEGACY;
			e_err("Failed to initialize MSI interrupts.  Falling back to legacy interrupts.\n");
		पूर्ण
		fallthrough;
	हाल E1000E_INT_MODE_LEGACY:
		/* Don't करो anything; this is the प्रणाली शेष */
		अवरोध;
	पूर्ण

	/* store the number of vectors being used */
	adapter->num_vectors = 1;
पूर्ण

/**
 * e1000_request_msix - Initialize MSI-X पूर्णांकerrupts
 * @adapter: board निजी काष्ठाure
 *
 * e1000_request_msix allocates MSI-X vectors and requests पूर्णांकerrupts from the
 * kernel.
 **/
अटल पूर्णांक e1000_request_msix(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err = 0, vector = 0;

	अगर (म_माप(netdev->name) < (IFNAMSIZ - 5))
		snम_लिखो(adapter->rx_ring->name,
			 माप(adapter->rx_ring->name) - 1,
			 "%.14s-rx-0", netdev->name);
	अन्यथा
		स_नकल(adapter->rx_ring->name, netdev->name, IFNAMSIZ);
	err = request_irq(adapter->msix_entries[vector].vector,
			  e1000_पूर्णांकr_msix_rx, 0, adapter->rx_ring->name,
			  netdev);
	अगर (err)
		वापस err;
	adapter->rx_ring->itr_रेजिस्टर = adapter->hw.hw_addr +
	    E1000_EITR_82574(vector);
	adapter->rx_ring->itr_val = adapter->itr;
	vector++;

	अगर (म_माप(netdev->name) < (IFNAMSIZ - 5))
		snम_लिखो(adapter->tx_ring->name,
			 माप(adapter->tx_ring->name) - 1,
			 "%.14s-tx-0", netdev->name);
	अन्यथा
		स_नकल(adapter->tx_ring->name, netdev->name, IFNAMSIZ);
	err = request_irq(adapter->msix_entries[vector].vector,
			  e1000_पूर्णांकr_msix_tx, 0, adapter->tx_ring->name,
			  netdev);
	अगर (err)
		वापस err;
	adapter->tx_ring->itr_रेजिस्टर = adapter->hw.hw_addr +
	    E1000_EITR_82574(vector);
	adapter->tx_ring->itr_val = adapter->itr;
	vector++;

	err = request_irq(adapter->msix_entries[vector].vector,
			  e1000_msix_other, 0, netdev->name, netdev);
	अगर (err)
		वापस err;

	e1000_configure_msix(adapter);

	वापस 0;
पूर्ण

/**
 * e1000_request_irq - initialize पूर्णांकerrupts
 * @adapter: board निजी काष्ठाure
 *
 * Attempts to configure पूर्णांकerrupts using the best available
 * capabilities of the hardware and kernel.
 **/
अटल पूर्णांक e1000_request_irq(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	पूर्णांक err;

	अगर (adapter->msix_entries) अणु
		err = e1000_request_msix(adapter);
		अगर (!err)
			वापस err;
		/* fall back to MSI */
		e1000e_reset_पूर्णांकerrupt_capability(adapter);
		adapter->पूर्णांक_mode = E1000E_INT_MODE_MSI;
		e1000e_set_पूर्णांकerrupt_capability(adapter);
	पूर्ण
	अगर (adapter->flags & FLAG_MSI_ENABLED) अणु
		err = request_irq(adapter->pdev->irq, e1000_पूर्णांकr_msi, 0,
				  netdev->name, netdev);
		अगर (!err)
			वापस err;

		/* fall back to legacy पूर्णांकerrupt */
		e1000e_reset_पूर्णांकerrupt_capability(adapter);
		adapter->पूर्णांक_mode = E1000E_INT_MODE_LEGACY;
	पूर्ण

	err = request_irq(adapter->pdev->irq, e1000_पूर्णांकr, IRQF_SHARED,
			  netdev->name, netdev);
	अगर (err)
		e_err("Unable to allocate interrupt, Error: %d\n", err);

	वापस err;
पूर्ण

अटल व्योम e1000_मुक्त_irq(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	अगर (adapter->msix_entries) अणु
		पूर्णांक vector = 0;

		मुक्त_irq(adapter->msix_entries[vector].vector, netdev);
		vector++;

		मुक्त_irq(adapter->msix_entries[vector].vector, netdev);
		vector++;

		/* Other Causes पूर्णांकerrupt vector */
		मुक्त_irq(adapter->msix_entries[vector].vector, netdev);
		वापस;
	पूर्ण

	मुक्त_irq(adapter->pdev->irq, netdev);
पूर्ण

/**
 * e1000_irq_disable - Mask off पूर्णांकerrupt generation on the NIC
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम e1000_irq_disable(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	ew32(IMC, ~0);
	अगर (adapter->msix_entries)
		ew32(EIAC_82574, 0);
	e1e_flush();

	अगर (adapter->msix_entries) अणु
		पूर्णांक i;

		क्रम (i = 0; i < adapter->num_vectors; i++)
			synchronize_irq(adapter->msix_entries[i].vector);
	पूर्ण अन्यथा अणु
		synchronize_irq(adapter->pdev->irq);
	पूर्ण
पूर्ण

/**
 * e1000_irq_enable - Enable शेष पूर्णांकerrupt generation settings
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम e1000_irq_enable(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	अगर (adapter->msix_entries) अणु
		ew32(EIAC_82574, adapter->eiac_mask & E1000_EIAC_MASK_82574);
		ew32(IMS, adapter->eiac_mask | E1000_IMS_OTHER |
		     IMS_OTHER_MASK);
	पूर्ण अन्यथा अगर (hw->mac.type >= e1000_pch_lpt) अणु
		ew32(IMS, IMS_ENABLE_MASK | E1000_IMS_ECCER);
	पूर्ण अन्यथा अणु
		ew32(IMS, IMS_ENABLE_MASK);
	पूर्ण
	e1e_flush();
पूर्ण

/**
 * e1000e_get_hw_control - get control of the h/w from f/w
 * @adapter: address of board निजी काष्ठाure
 *
 * e1000e_get_hw_control sets अणुCTRL_EXT|SWSMपूर्ण:DRV_LOAD bit.
 * For ASF and Pass Through versions of f/w this means that
 * the driver is loaded. For AMT version (only with 82573)
 * of the f/w this means that the network i/f is खोलो.
 **/
व्योम e1000e_get_hw_control(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl_ext;
	u32 swsm;

	/* Let firmware know the driver has taken over */
	अगर (adapter->flags & FLAG_HAS_SWSM_ON_LOAD) अणु
		swsm = er32(SWSM);
		ew32(SWSM, swsm | E1000_SWSM_DRV_LOAD);
	पूर्ण अन्यथा अगर (adapter->flags & FLAG_HAS_CTRLEXT_ON_LOAD) अणु
		ctrl_ext = er32(CTRL_EXT);
		ew32(CTRL_EXT, ctrl_ext | E1000_CTRL_EXT_DRV_LOAD);
	पूर्ण
पूर्ण

/**
 * e1000e_release_hw_control - release control of the h/w to f/w
 * @adapter: address of board निजी काष्ठाure
 *
 * e1000e_release_hw_control resets अणुCTRL_EXT|SWSMपूर्ण:DRV_LOAD bit.
 * For ASF and Pass Through versions of f/w this means that the
 * driver is no दीर्घer loaded. For AMT version (only with 82573) i
 * of the f/w this means that the network i/f is बंदd.
 *
 **/
व्योम e1000e_release_hw_control(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl_ext;
	u32 swsm;

	/* Let firmware taken over control of h/w */
	अगर (adapter->flags & FLAG_HAS_SWSM_ON_LOAD) अणु
		swsm = er32(SWSM);
		ew32(SWSM, swsm & ~E1000_SWSM_DRV_LOAD);
	पूर्ण अन्यथा अगर (adapter->flags & FLAG_HAS_CTRLEXT_ON_LOAD) अणु
		ctrl_ext = er32(CTRL_EXT);
		ew32(CTRL_EXT, ctrl_ext & ~E1000_CTRL_EXT_DRV_LOAD);
	पूर्ण
पूर्ण

/**
 * e1000_alloc_ring_dma - allocate memory क्रम a ring काष्ठाure
 * @adapter: board निजी काष्ठाure
 * @ring: ring काष्ठा क्रम which to allocate dma
 **/
अटल पूर्णांक e1000_alloc_ring_dma(काष्ठा e1000_adapter *adapter,
				काष्ठा e1000_ring *ring)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;

	ring->desc = dma_alloc_coherent(&pdev->dev, ring->size, &ring->dma,
					GFP_KERNEL);
	अगर (!ring->desc)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * e1000e_setup_tx_resources - allocate Tx resources (Descriptors)
 * @tx_ring: Tx descriptor ring
 *
 * Return 0 on success, negative on failure
 **/
पूर्णांक e1000e_setup_tx_resources(काष्ठा e1000_ring *tx_ring)
अणु
	काष्ठा e1000_adapter *adapter = tx_ring->adapter;
	पूर्णांक err = -ENOMEM, size;

	size = माप(काष्ठा e1000_buffer) * tx_ring->count;
	tx_ring->buffer_info = vzalloc(size);
	अगर (!tx_ring->buffer_info)
		जाओ err;

	/* round up to nearest 4K */
	tx_ring->size = tx_ring->count * माप(काष्ठा e1000_tx_desc);
	tx_ring->size = ALIGN(tx_ring->size, 4096);

	err = e1000_alloc_ring_dma(adapter, tx_ring);
	अगर (err)
		जाओ err;

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	वापस 0;
err:
	vमुक्त(tx_ring->buffer_info);
	e_err("Unable to allocate memory for the transmit descriptor ring\n");
	वापस err;
पूर्ण

/**
 * e1000e_setup_rx_resources - allocate Rx resources (Descriptors)
 * @rx_ring: Rx descriptor ring
 *
 * Returns 0 on success, negative on failure
 **/
पूर्णांक e1000e_setup_rx_resources(काष्ठा e1000_ring *rx_ring)
अणु
	काष्ठा e1000_adapter *adapter = rx_ring->adapter;
	काष्ठा e1000_buffer *buffer_info;
	पूर्णांक i, size, desc_len, err = -ENOMEM;

	size = माप(काष्ठा e1000_buffer) * rx_ring->count;
	rx_ring->buffer_info = vzalloc(size);
	अगर (!rx_ring->buffer_info)
		जाओ err;

	क्रम (i = 0; i < rx_ring->count; i++) अणु
		buffer_info = &rx_ring->buffer_info[i];
		buffer_info->ps_pages = kसुस्मृति(PS_PAGE_BUFFERS,
						माप(काष्ठा e1000_ps_page),
						GFP_KERNEL);
		अगर (!buffer_info->ps_pages)
			जाओ err_pages;
	पूर्ण

	desc_len = माप(जोड़ e1000_rx_desc_packet_split);

	/* Round up to nearest 4K */
	rx_ring->size = rx_ring->count * desc_len;
	rx_ring->size = ALIGN(rx_ring->size, 4096);

	err = e1000_alloc_ring_dma(adapter, rx_ring);
	अगर (err)
		जाओ err_pages;

	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
	rx_ring->rx_skb_top = शून्य;

	वापस 0;

err_pages:
	क्रम (i = 0; i < rx_ring->count; i++) अणु
		buffer_info = &rx_ring->buffer_info[i];
		kमुक्त(buffer_info->ps_pages);
	पूर्ण
err:
	vमुक्त(rx_ring->buffer_info);
	e_err("Unable to allocate memory for the receive descriptor ring\n");
	वापस err;
पूर्ण

/**
 * e1000_clean_tx_ring - Free Tx Buffers
 * @tx_ring: Tx descriptor ring
 **/
अटल व्योम e1000_clean_tx_ring(काष्ठा e1000_ring *tx_ring)
अणु
	काष्ठा e1000_adapter *adapter = tx_ring->adapter;
	काष्ठा e1000_buffer *buffer_info;
	अचिन्हित दीर्घ size;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < tx_ring->count; i++) अणु
		buffer_info = &tx_ring->buffer_info[i];
		e1000_put_txbuf(tx_ring, buffer_info, false);
	पूर्ण

	netdev_reset_queue(adapter->netdev);
	size = माप(काष्ठा e1000_buffer) * tx_ring->count;
	स_रखो(tx_ring->buffer_info, 0, size);

	स_रखो(tx_ring->desc, 0, tx_ring->size);

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
पूर्ण

/**
 * e1000e_मुक्त_tx_resources - Free Tx Resources per Queue
 * @tx_ring: Tx descriptor ring
 *
 * Free all transmit software resources
 **/
व्योम e1000e_मुक्त_tx_resources(काष्ठा e1000_ring *tx_ring)
अणु
	काष्ठा e1000_adapter *adapter = tx_ring->adapter;
	काष्ठा pci_dev *pdev = adapter->pdev;

	e1000_clean_tx_ring(tx_ring);

	vमुक्त(tx_ring->buffer_info);
	tx_ring->buffer_info = शून्य;

	dma_मुक्त_coherent(&pdev->dev, tx_ring->size, tx_ring->desc,
			  tx_ring->dma);
	tx_ring->desc = शून्य;
पूर्ण

/**
 * e1000e_मुक्त_rx_resources - Free Rx Resources
 * @rx_ring: Rx descriptor ring
 *
 * Free all receive software resources
 **/
व्योम e1000e_मुक्त_rx_resources(काष्ठा e1000_ring *rx_ring)
अणु
	काष्ठा e1000_adapter *adapter = rx_ring->adapter;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक i;

	e1000_clean_rx_ring(rx_ring);

	क्रम (i = 0; i < rx_ring->count; i++)
		kमुक्त(rx_ring->buffer_info[i].ps_pages);

	vमुक्त(rx_ring->buffer_info);
	rx_ring->buffer_info = शून्य;

	dma_मुक्त_coherent(&pdev->dev, rx_ring->size, rx_ring->desc,
			  rx_ring->dma);
	rx_ring->desc = शून्य;
पूर्ण

/**
 * e1000_update_itr - update the dynamic ITR value based on statistics
 * @itr_setting: current adapter->itr
 * @packets: the number of packets during this measurement पूर्णांकerval
 * @bytes: the number of bytes during this measurement पूर्णांकerval
 *
 *      Stores a new ITR value based on packets and byte
 *      counts during the last पूर्णांकerrupt.  The advantage of per पूर्णांकerrupt
 *      computation is faster updates and more accurate ITR क्रम the current
 *      traffic pattern.  Constants in this function were computed
 *      based on theoretical maximum wire speed and thresholds were set based
 *      on testing data as well as attempting to minimize response समय
 *      जबतक increasing bulk throughput.  This functionality is controlled
 *      by the InterruptThrottleRate module parameter.
 **/
अटल अचिन्हित पूर्णांक e1000_update_itr(u16 itr_setting, पूर्णांक packets, पूर्णांक bytes)
अणु
	अचिन्हित पूर्णांक retval = itr_setting;

	अगर (packets == 0)
		वापस itr_setting;

	चयन (itr_setting) अणु
	हाल lowest_latency:
		/* handle TSO and jumbo frames */
		अगर (bytes / packets > 8000)
			retval = bulk_latency;
		अन्यथा अगर ((packets < 5) && (bytes > 512))
			retval = low_latency;
		अवरोध;
	हाल low_latency:	/* 50 usec aka 20000 पूर्णांकs/s */
		अगर (bytes > 10000) अणु
			/* this अगर handles the TSO accounting */
			अगर (bytes / packets > 8000)
				retval = bulk_latency;
			अन्यथा अगर ((packets < 10) || ((bytes / packets) > 1200))
				retval = bulk_latency;
			अन्यथा अगर ((packets > 35))
				retval = lowest_latency;
		पूर्ण अन्यथा अगर (bytes / packets > 2000) अणु
			retval = bulk_latency;
		पूर्ण अन्यथा अगर (packets <= 2 && bytes < 512) अणु
			retval = lowest_latency;
		पूर्ण
		अवरोध;
	हाल bulk_latency:	/* 250 usec aka 4000 पूर्णांकs/s */
		अगर (bytes > 25000) अणु
			अगर (packets > 35)
				retval = low_latency;
		पूर्ण अन्यथा अगर (bytes < 6000) अणु
			retval = low_latency;
		पूर्ण
		अवरोध;
	पूर्ण

	वापस retval;
पूर्ण

अटल व्योम e1000_set_itr(काष्ठा e1000_adapter *adapter)
अणु
	u16 current_itr;
	u32 new_itr = adapter->itr;

	/* क्रम non-gigabit speeds, just fix the पूर्णांकerrupt rate at 4000 */
	अगर (adapter->link_speed != SPEED_1000) अणु
		current_itr = 0;
		new_itr = 4000;
		जाओ set_itr_now;
	पूर्ण

	अगर (adapter->flags2 & FLAG2_DISABLE_AIM) अणु
		new_itr = 0;
		जाओ set_itr_now;
	पूर्ण

	adapter->tx_itr = e1000_update_itr(adapter->tx_itr,
					   adapter->total_tx_packets,
					   adapter->total_tx_bytes);
	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	अगर (adapter->itr_setting == 3 && adapter->tx_itr == lowest_latency)
		adapter->tx_itr = low_latency;

	adapter->rx_itr = e1000_update_itr(adapter->rx_itr,
					   adapter->total_rx_packets,
					   adapter->total_rx_bytes);
	/* conservative mode (itr 3) eliminates the lowest_latency setting */
	अगर (adapter->itr_setting == 3 && adapter->rx_itr == lowest_latency)
		adapter->rx_itr = low_latency;

	current_itr = max(adapter->rx_itr, adapter->tx_itr);

	/* counts and packets in update_itr are dependent on these numbers */
	चयन (current_itr) अणु
	हाल lowest_latency:
		new_itr = 70000;
		अवरोध;
	हाल low_latency:
		new_itr = 20000;	/* aka hwitr = ~200 */
		अवरोध;
	हाल bulk_latency:
		new_itr = 4000;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

set_itr_now:
	अगर (new_itr != adapter->itr) अणु
		/* this attempts to bias the पूर्णांकerrupt rate towards Bulk
		 * by adding पूर्णांकermediate steps when पूर्णांकerrupt rate is
		 * increasing
		 */
		new_itr = new_itr > adapter->itr ?
		    min(adapter->itr + (new_itr >> 2), new_itr) : new_itr;
		adapter->itr = new_itr;
		adapter->rx_ring->itr_val = new_itr;
		अगर (adapter->msix_entries)
			adapter->rx_ring->set_itr = 1;
		अन्यथा
			e1000e_ग_लिखो_itr(adapter, new_itr);
	पूर्ण
पूर्ण

/**
 * e1000e_ग_लिखो_itr - ग_लिखो the ITR value to the appropriate रेजिस्टरs
 * @adapter: address of board निजी काष्ठाure
 * @itr: new ITR value to program
 *
 * e1000e_ग_लिखो_itr determines अगर the adapter is in MSI-X mode
 * and, अगर so, ग_लिखोs the EITR रेजिस्टरs with the ITR value.
 * Otherwise, it ग_लिखोs the ITR value पूर्णांकo the ITR रेजिस्टर.
 **/
व्योम e1000e_ग_लिखो_itr(काष्ठा e1000_adapter *adapter, u32 itr)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 new_itr = itr ? 1000000000 / (itr * 256) : 0;

	अगर (adapter->msix_entries) अणु
		पूर्णांक vector;

		क्रम (vector = 0; vector < adapter->num_vectors; vector++)
			ग_लिखोl(new_itr, hw->hw_addr + E1000_EITR_82574(vector));
	पूर्ण अन्यथा अणु
		ew32(ITR, new_itr);
	पूर्ण
पूर्ण

/**
 * e1000_alloc_queues - Allocate memory क्रम all rings
 * @adapter: board निजी काष्ठाure to initialize
 **/
अटल पूर्णांक e1000_alloc_queues(काष्ठा e1000_adapter *adapter)
अणु
	पूर्णांक size = माप(काष्ठा e1000_ring);

	adapter->tx_ring = kzalloc(size, GFP_KERNEL);
	अगर (!adapter->tx_ring)
		जाओ err;
	adapter->tx_ring->count = adapter->tx_ring_count;
	adapter->tx_ring->adapter = adapter;

	adapter->rx_ring = kzalloc(size, GFP_KERNEL);
	अगर (!adapter->rx_ring)
		जाओ err;
	adapter->rx_ring->count = adapter->rx_ring_count;
	adapter->rx_ring->adapter = adapter;

	वापस 0;
err:
	e_err("Unable to allocate memory for queues\n");
	kमुक्त(adapter->rx_ring);
	kमुक्त(adapter->tx_ring);
	वापस -ENOMEM;
पूर्ण

/**
 * e1000e_poll - NAPI Rx polling callback
 * @napi: काष्ठा associated with this polling callback
 * @budget: number of packets driver is allowed to process this poll
 **/
अटल पूर्णांक e1000e_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा e1000_adapter *adapter = container_of(napi, काष्ठा e1000_adapter,
						     napi);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा net_device *poll_dev = adapter->netdev;
	पूर्णांक tx_cleaned = 1, work_करोne = 0;

	adapter = netdev_priv(poll_dev);

	अगर (!adapter->msix_entries ||
	    (adapter->rx_ring->ims_val & adapter->tx_ring->ims_val))
		tx_cleaned = e1000_clean_tx_irq(adapter->tx_ring);

	adapter->clean_rx(adapter->rx_ring, &work_करोne, budget);

	अगर (!tx_cleaned || work_करोne == budget)
		वापस budget;

	/* Exit the polling mode, but करोn't re-enable पूर्णांकerrupts अगर stack might
	 * poll us due to busy-polling
	 */
	अगर (likely(napi_complete_करोne(napi, work_करोne))) अणु
		अगर (adapter->itr_setting & 3)
			e1000_set_itr(adapter);
		अगर (!test_bit(__E1000_DOWN, &adapter->state)) अणु
			अगर (adapter->msix_entries)
				ew32(IMS, adapter->rx_ring->ims_val);
			अन्यथा
				e1000_irq_enable(adapter);
		पूर्ण
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल पूर्णांक e1000_vlan_rx_add_vid(काष्ठा net_device *netdev,
				 __always_unused __be16 proto, u16 vid)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 vfta, index;

	/* करोn't update vlan cookie अगर alपढ़ोy programmed */
	अगर ((adapter->hw.mng_cookie.status &
	     E1000_MNG_DHCP_COOKIE_STATUS_VLAN) &&
	    (vid == adapter->mng_vlan_id))
		वापस 0;

	/* add VID to filter table */
	अगर (adapter->flags & FLAG_HAS_HW_VLAN_FILTER) अणु
		index = (vid >> 5) & 0x7F;
		vfta = E1000_READ_REG_ARRAY(hw, E1000_VFTA, index);
		vfta |= BIT((vid & 0x1F));
		hw->mac.ops.ग_लिखो_vfta(hw, index, vfta);
	पूर्ण

	set_bit(vid, adapter->active_vlans);

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				  __always_unused __be16 proto, u16 vid)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 vfta, index;

	अगर ((adapter->hw.mng_cookie.status &
	     E1000_MNG_DHCP_COOKIE_STATUS_VLAN) &&
	    (vid == adapter->mng_vlan_id)) अणु
		/* release control to f/w */
		e1000e_release_hw_control(adapter);
		वापस 0;
	पूर्ण

	/* हटाओ VID from filter table */
	अगर (adapter->flags & FLAG_HAS_HW_VLAN_FILTER) अणु
		index = (vid >> 5) & 0x7F;
		vfta = E1000_READ_REG_ARRAY(hw, E1000_VFTA, index);
		vfta &= ~BIT((vid & 0x1F));
		hw->mac.ops.ग_लिखो_vfta(hw, index, vfta);
	पूर्ण

	clear_bit(vid, adapter->active_vlans);

	वापस 0;
पूर्ण

/**
 * e1000e_vlan_filter_disable - helper to disable hw VLAN filtering
 * @adapter: board निजी काष्ठाure to initialize
 **/
अटल व्योम e1000e_vlan_filter_disable(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rctl;

	अगर (adapter->flags & FLAG_HAS_HW_VLAN_FILTER) अणु
		/* disable VLAN receive filtering */
		rctl = er32(RCTL);
		rctl &= ~(E1000_RCTL_VFE | E1000_RCTL_CFIEN);
		ew32(RCTL, rctl);

		अगर (adapter->mng_vlan_id != (u16)E1000_MNG_VLAN_NONE) अणु
			e1000_vlan_rx_समाप्त_vid(netdev, htons(ETH_P_8021Q),
					       adapter->mng_vlan_id);
			adapter->mng_vlan_id = E1000_MNG_VLAN_NONE;
		पूर्ण
	पूर्ण
पूर्ण

/**
 * e1000e_vlan_filter_enable - helper to enable HW VLAN filtering
 * @adapter: board निजी काष्ठाure to initialize
 **/
अटल व्योम e1000e_vlan_filter_enable(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rctl;

	अगर (adapter->flags & FLAG_HAS_HW_VLAN_FILTER) अणु
		/* enable VLAN receive filtering */
		rctl = er32(RCTL);
		rctl |= E1000_RCTL_VFE;
		rctl &= ~E1000_RCTL_CFIEN;
		ew32(RCTL, rctl);
	पूर्ण
पूर्ण

/**
 * e1000e_vlan_strip_disable - helper to disable HW VLAN stripping
 * @adapter: board निजी काष्ठाure to initialize
 **/
अटल व्योम e1000e_vlan_strip_disable(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl;

	/* disable VLAN tag insert/strip */
	ctrl = er32(CTRL);
	ctrl &= ~E1000_CTRL_VME;
	ew32(CTRL, ctrl);
पूर्ण

/**
 * e1000e_vlan_strip_enable - helper to enable HW VLAN stripping
 * @adapter: board निजी काष्ठाure to initialize
 **/
अटल व्योम e1000e_vlan_strip_enable(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl;

	/* enable VLAN tag insert/strip */
	ctrl = er32(CTRL);
	ctrl |= E1000_CTRL_VME;
	ew32(CTRL, ctrl);
पूर्ण

अटल व्योम e1000_update_mng_vlan(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	u16 vid = adapter->hw.mng_cookie.vlan_id;
	u16 old_vid = adapter->mng_vlan_id;

	अगर (adapter->hw.mng_cookie.status & E1000_MNG_DHCP_COOKIE_STATUS_VLAN) अणु
		e1000_vlan_rx_add_vid(netdev, htons(ETH_P_8021Q), vid);
		adapter->mng_vlan_id = vid;
	पूर्ण

	अगर ((old_vid != (u16)E1000_MNG_VLAN_NONE) && (vid != old_vid))
		e1000_vlan_rx_समाप्त_vid(netdev, htons(ETH_P_8021Q), old_vid);
पूर्ण

अटल व्योम e1000_restore_vlan(काष्ठा e1000_adapter *adapter)
अणु
	u16 vid;

	e1000_vlan_rx_add_vid(adapter->netdev, htons(ETH_P_8021Q), 0);

	क्रम_each_set_bit(vid, adapter->active_vlans, VLAN_N_VID)
	    e1000_vlan_rx_add_vid(adapter->netdev, htons(ETH_P_8021Q), vid);
पूर्ण

अटल व्योम e1000_init_manageability_pt(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 manc, manc2h, mdef, i, j;

	अगर (!(adapter->flags & FLAG_MNG_PT_ENABLED))
		वापस;

	manc = er32(MANC);

	/* enable receiving management packets to the host. this will probably
	 * generate destination unreachable messages from the host OS, but
	 * the packets will be handled on SMBUS
	 */
	manc |= E1000_MANC_EN_MNG2HOST;
	manc2h = er32(MANC2H);

	चयन (hw->mac.type) अणु
	शेष:
		manc2h |= (E1000_MANC2H_PORT_623 | E1000_MANC2H_PORT_664);
		अवरोध;
	हाल e1000_82574:
	हाल e1000_82583:
		/* Check अगर IPMI pass-through decision filter alपढ़ोy exists;
		 * अगर so, enable it.
		 */
		क्रम (i = 0, j = 0; i < 8; i++) अणु
			mdef = er32(MDEF(i));

			/* Ignore filters with anything other than IPMI ports */
			अगर (mdef & ~(E1000_MDEF_PORT_623 | E1000_MDEF_PORT_664))
				जारी;

			/* Enable this decision filter in MANC2H */
			अगर (mdef)
				manc2h |= BIT(i);

			j |= mdef;
		पूर्ण

		अगर (j == (E1000_MDEF_PORT_623 | E1000_MDEF_PORT_664))
			अवरोध;

		/* Create new decision filter in an empty filter */
		क्रम (i = 0, j = 0; i < 8; i++)
			अगर (er32(MDEF(i)) == 0) अणु
				ew32(MDEF(i), (E1000_MDEF_PORT_623 |
					       E1000_MDEF_PORT_664));
				manc2h |= BIT(1);
				j++;
				अवरोध;
			पूर्ण

		अगर (!j)
			e_warn("Unable to create IPMI pass-through filter\n");
		अवरोध;
	पूर्ण

	ew32(MANC2H, manc2h);
	ew32(MANC, manc);
पूर्ण

/**
 * e1000_configure_tx - Configure Transmit Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Tx unit of the MAC after a reset.
 **/
अटल व्योम e1000_configure_tx(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_ring *tx_ring = adapter->tx_ring;
	u64 tdba;
	u32 tdlen, tctl, tarc;

	/* Setup the HW Tx Head and Tail descriptor poपूर्णांकers */
	tdba = tx_ring->dma;
	tdlen = tx_ring->count * माप(काष्ठा e1000_tx_desc);
	ew32(TDBAL(0), (tdba & DMA_BIT_MASK(32)));
	ew32(TDBAH(0), (tdba >> 32));
	ew32(TDLEN(0), tdlen);
	ew32(TDH(0), 0);
	ew32(TDT(0), 0);
	tx_ring->head = adapter->hw.hw_addr + E1000_TDH(0);
	tx_ring->tail = adapter->hw.hw_addr + E1000_TDT(0);

	ग_लिखोl(0, tx_ring->head);
	अगर (adapter->flags2 & FLAG2_PCIM2PCI_ARBITER_WA)
		e1000e_update_tdt_wa(tx_ring, 0);
	अन्यथा
		ग_लिखोl(0, tx_ring->tail);

	/* Set the Tx Interrupt Delay रेजिस्टर */
	ew32(TIDV, adapter->tx_पूर्णांक_delay);
	/* Tx irq moderation */
	ew32(TADV, adapter->tx_असल_पूर्णांक_delay);

	अगर (adapter->flags2 & FLAG2_DMA_BURST) अणु
		u32 txdctl = er32(TXDCTL(0));

		txdctl &= ~(E1000_TXDCTL_PTHRESH | E1000_TXDCTL_HTHRESH |
			    E1000_TXDCTL_WTHRESH);
		/* set up some perक्रमmance related parameters to encourage the
		 * hardware to use the bus more efficiently in bursts, depends
		 * on the tx_पूर्णांक_delay to be enabled,
		 * wthresh = 1 ==> burst ग_लिखो is disabled to aव्योम Tx stalls
		 * hthresh = 1 ==> prefetch when one or more available
		 * pthresh = 0x1f ==> prefetch अगर पूर्णांकernal cache 31 or less
		 * BEWARE: this seems to work but should be considered first अगर
		 * there are Tx hangs or other Tx related bugs
		 */
		txdctl |= E1000_TXDCTL_DMA_BURST_ENABLE;
		ew32(TXDCTL(0), txdctl);
	पूर्ण
	/* erratum work around: set txdctl the same क्रम both queues */
	ew32(TXDCTL(1), er32(TXDCTL(0)));

	/* Program the Transmit Control Register */
	tctl = er32(TCTL);
	tctl &= ~E1000_TCTL_CT;
	tctl |= E1000_TCTL_PSP | E1000_TCTL_RTLC |
		(E1000_COLLISION_THRESHOLD << E1000_CT_SHIFT);

	अगर (adapter->flags & FLAG_TARC_SPEED_MODE_BIT) अणु
		tarc = er32(TARC(0));
		/* set the speed mode bit, we'll clear it if we're not at
		 * gigabit link later
		 */
#घोषणा SPEED_MODE_BIT BIT(21)
		tarc |= SPEED_MODE_BIT;
		ew32(TARC(0), tarc);
	पूर्ण

	/* errata: program both queues to unweighted RR */
	अगर (adapter->flags & FLAG_TARC_SET_BIT_ZERO) अणु
		tarc = er32(TARC(0));
		tarc |= 1;
		ew32(TARC(0), tarc);
		tarc = er32(TARC(1));
		tarc |= 1;
		ew32(TARC(1), tarc);
	पूर्ण

	/* Setup Transmit Descriptor Settings क्रम eop descriptor */
	adapter->txd_cmd = E1000_TXD_CMD_EOP | E1000_TXD_CMD_IFCS;

	/* only set IDE अगर we are delaying पूर्णांकerrupts using the समयrs */
	अगर (adapter->tx_पूर्णांक_delay)
		adapter->txd_cmd |= E1000_TXD_CMD_IDE;

	/* enable Report Status bit */
	adapter->txd_cmd |= E1000_TXD_CMD_RS;

	ew32(TCTL, tctl);

	hw->mac.ops.config_collision_dist(hw);

	/* SPT and KBL Si errata workaround to aव्योम data corruption */
	अगर (hw->mac.type == e1000_pch_spt) अणु
		u32 reg_val;

		reg_val = er32(IOSFPC);
		reg_val |= E1000_RCTL_RDMTS_HEX;
		ew32(IOSFPC, reg_val);

		reg_val = er32(TARC(0));
		/* SPT and KBL Si errata workaround to aव्योम Tx hang.
		 * Dropping the number of outstanding requests from
		 * 3 to 2 in order to aव्योम a buffer overrun.
		 */
		reg_val &= ~E1000_TARC0_CB_MULTIQ_3_REQ;
		reg_val |= E1000_TARC0_CB_MULTIQ_2_REQ;
		ew32(TARC(0), reg_val);
	पूर्ण
पूर्ण

#घोषणा PAGE_USE_COUNT(S) (((S) >> PAGE_SHIFT) + \
			   (((S) & (PAGE_SIZE - 1)) ? 1 : 0))

/**
 * e1000_setup_rctl - configure the receive control रेजिस्टरs
 * @adapter: Board निजी काष्ठाure
 **/
अटल व्योम e1000_setup_rctl(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rctl, rfctl;
	u32 pages = 0;

	/* Workaround Si errata on PCHx - configure jumbo frame flow.
	 * If jumbo frames not set, program related MAC/PHY रेजिस्टरs
	 * to h/w शेषs
	 */
	अगर (hw->mac.type >= e1000_pch2lan) अणु
		s32 ret_val;

		अगर (adapter->netdev->mtu > ETH_DATA_LEN)
			ret_val = e1000_lv_jumbo_workaround_ich8lan(hw, true);
		अन्यथा
			ret_val = e1000_lv_jumbo_workaround_ich8lan(hw, false);

		अगर (ret_val)
			e_dbg("failed to enable|disable jumbo frame workaround mode\n");
	पूर्ण

	/* Program MC offset vector base */
	rctl = er32(RCTL);
	rctl &= ~(3 << E1000_RCTL_MO_SHIFT);
	rctl |= E1000_RCTL_EN | E1000_RCTL_BAM |
	    E1000_RCTL_LBM_NO | E1000_RCTL_RDMTS_HALF |
	    (adapter->hw.mac.mc_filter_type << E1000_RCTL_MO_SHIFT);

	/* Do not Store bad packets */
	rctl &= ~E1000_RCTL_SBP;

	/* Enable Long Packet receive */
	अगर (adapter->netdev->mtu <= ETH_DATA_LEN)
		rctl &= ~E1000_RCTL_LPE;
	अन्यथा
		rctl |= E1000_RCTL_LPE;

	/* Some प्रणालीs expect that the CRC is included in SMBUS traffic. The
	 * hardware strips the CRC beक्रमe sending to both SMBUS (BMC) and to
	 * host memory when this is enabled
	 */
	अगर (adapter->flags2 & FLAG2_CRC_STRIPPING)
		rctl |= E1000_RCTL_SECRC;

	/* Workaround Si errata on 82577 PHY - configure IPG क्रम jumbos */
	अगर ((hw->phy.type == e1000_phy_82577) && (rctl & E1000_RCTL_LPE)) अणु
		u16 phy_data;

		e1e_rphy(hw, PHY_REG(770, 26), &phy_data);
		phy_data &= 0xfff8;
		phy_data |= BIT(2);
		e1e_wphy(hw, PHY_REG(770, 26), phy_data);

		e1e_rphy(hw, 22, &phy_data);
		phy_data &= 0x0fff;
		phy_data |= BIT(14);
		e1e_wphy(hw, 0x10, 0x2823);
		e1e_wphy(hw, 0x11, 0x0003);
		e1e_wphy(hw, 22, phy_data);
	पूर्ण

	/* Setup buffer sizes */
	rctl &= ~E1000_RCTL_SZ_4096;
	rctl |= E1000_RCTL_BSEX;
	चयन (adapter->rx_buffer_len) अणु
	हाल 2048:
	शेष:
		rctl |= E1000_RCTL_SZ_2048;
		rctl &= ~E1000_RCTL_BSEX;
		अवरोध;
	हाल 4096:
		rctl |= E1000_RCTL_SZ_4096;
		अवरोध;
	हाल 8192:
		rctl |= E1000_RCTL_SZ_8192;
		अवरोध;
	हाल 16384:
		rctl |= E1000_RCTL_SZ_16384;
		अवरोध;
	पूर्ण

	/* Enable Extended Status in all Receive Descriptors */
	rfctl = er32(RFCTL);
	rfctl |= E1000_RFCTL_EXTEN;
	ew32(RFCTL, rfctl);

	/* 82571 and greater support packet-split where the protocol
	 * header is placed in skb->data and the packet data is
	 * placed in pages hanging off of skb_shinfo(skb)->nr_frags.
	 * In the हाल of a non-split, skb->data is linearly filled,
	 * followed by the page buffers.  Thereक्रमe, skb->data is
	 * sized to hold the largest protocol header.
	 *
	 * allocations using alloc_page take too दीर्घ क्रम regular MTU
	 * so only enable packet split क्रम jumbo frames
	 *
	 * Using pages when the page size is greater than 16k wastes
	 * a lot of memory, since we allocate 3 pages at all बार
	 * per packet.
	 */
	pages = PAGE_USE_COUNT(adapter->netdev->mtu);
	अगर ((pages <= 3) && (PAGE_SIZE <= 16384) && (rctl & E1000_RCTL_LPE))
		adapter->rx_ps_pages = pages;
	अन्यथा
		adapter->rx_ps_pages = 0;

	अगर (adapter->rx_ps_pages) अणु
		u32 psrctl = 0;

		/* Enable Packet split descriptors */
		rctl |= E1000_RCTL_DTYP_PS;

		psrctl |= adapter->rx_ps_bsize0 >> E1000_PSRCTL_BSIZE0_SHIFT;

		चयन (adapter->rx_ps_pages) अणु
		हाल 3:
			psrctl |= PAGE_SIZE << E1000_PSRCTL_BSIZE3_SHIFT;
			fallthrough;
		हाल 2:
			psrctl |= PAGE_SIZE << E1000_PSRCTL_BSIZE2_SHIFT;
			fallthrough;
		हाल 1:
			psrctl |= PAGE_SIZE >> E1000_PSRCTL_BSIZE1_SHIFT;
			अवरोध;
		पूर्ण

		ew32(PSRCTL, psrctl);
	पूर्ण

	/* This is useful क्रम snअगरfing bad packets. */
	अगर (adapter->netdev->features & NETIF_F_RXALL) अणु
		/* UPE and MPE will be handled by normal PROMISC logic
		 * in e1000e_set_rx_mode
		 */
		rctl |= (E1000_RCTL_SBP |	/* Receive bad packets */
			 E1000_RCTL_BAM |	/* RX All Bcast Pkts */
			 E1000_RCTL_PMCF);	/* RX All MAC Ctrl Pkts */

		rctl &= ~(E1000_RCTL_VFE |	/* Disable VLAN filter */
			  E1000_RCTL_DPF |	/* Allow filtered छोड़ो */
			  E1000_RCTL_CFIEN);	/* Dis VLAN CFIEN Filter */
		/* Do not mess with E1000_CTRL_VME, it affects transmit as well,
		 * and that अवरोधs VLANs.
		 */
	पूर्ण

	ew32(RCTL, rctl);
	/* just started the receive unit, no need to restart */
	adapter->flags &= ~FLAG_RESTART_NOW;
पूर्ण

/**
 * e1000_configure_rx - Configure Receive Unit after Reset
 * @adapter: board निजी काष्ठाure
 *
 * Configure the Rx unit of the MAC after a reset.
 **/
अटल व्योम e1000_configure_rx(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_ring *rx_ring = adapter->rx_ring;
	u64 rdba;
	u32 rdlen, rctl, rxcsum, ctrl_ext;

	अगर (adapter->rx_ps_pages) अणु
		/* this is a 32 byte descriptor */
		rdlen = rx_ring->count *
		    माप(जोड़ e1000_rx_desc_packet_split);
		adapter->clean_rx = e1000_clean_rx_irq_ps;
		adapter->alloc_rx_buf = e1000_alloc_rx_buffers_ps;
	पूर्ण अन्यथा अगर (adapter->netdev->mtu > ETH_FRAME_LEN + ETH_FCS_LEN) अणु
		rdlen = rx_ring->count * माप(जोड़ e1000_rx_desc_extended);
		adapter->clean_rx = e1000_clean_jumbo_rx_irq;
		adapter->alloc_rx_buf = e1000_alloc_jumbo_rx_buffers;
	पूर्ण अन्यथा अणु
		rdlen = rx_ring->count * माप(जोड़ e1000_rx_desc_extended);
		adapter->clean_rx = e1000_clean_rx_irq;
		adapter->alloc_rx_buf = e1000_alloc_rx_buffers;
	पूर्ण

	/* disable receives जबतक setting up the descriptors */
	rctl = er32(RCTL);
	अगर (!(adapter->flags2 & FLAG2_NO_DISABLE_RX))
		ew32(RCTL, rctl & ~E1000_RCTL_EN);
	e1e_flush();
	usleep_range(10000, 11000);

	अगर (adapter->flags2 & FLAG2_DMA_BURST) अणु
		/* set the ग_लिखोback threshold (only takes effect अगर the RDTR
		 * is set). set GRAN=1 and ग_लिखो back up to 0x4 worth, and
		 * enable prefetching of 0x20 Rx descriptors
		 * granularity = 01
		 * wthresh = 04,
		 * hthresh = 04,
		 * pthresh = 0x20
		 */
		ew32(RXDCTL(0), E1000_RXDCTL_DMA_BURST_ENABLE);
		ew32(RXDCTL(1), E1000_RXDCTL_DMA_BURST_ENABLE);
	पूर्ण

	/* set the Receive Delay Timer Register */
	ew32(RDTR, adapter->rx_पूर्णांक_delay);

	/* irq moderation */
	ew32(RADV, adapter->rx_असल_पूर्णांक_delay);
	अगर ((adapter->itr_setting != 0) && (adapter->itr != 0))
		e1000e_ग_लिखो_itr(adapter, adapter->itr);

	ctrl_ext = er32(CTRL_EXT);
	/* Auto-Mask पूर्णांकerrupts upon ICR access */
	ctrl_ext |= E1000_CTRL_EXT_IAME;
	ew32(IAM, 0xffffffff);
	ew32(CTRL_EXT, ctrl_ext);
	e1e_flush();

	/* Setup the HW Rx Head and Tail Descriptor Poपूर्णांकers and
	 * the Base and Length of the Rx Descriptor Ring
	 */
	rdba = rx_ring->dma;
	ew32(RDBAL(0), (rdba & DMA_BIT_MASK(32)));
	ew32(RDBAH(0), (rdba >> 32));
	ew32(RDLEN(0), rdlen);
	ew32(RDH(0), 0);
	ew32(RDT(0), 0);
	rx_ring->head = adapter->hw.hw_addr + E1000_RDH(0);
	rx_ring->tail = adapter->hw.hw_addr + E1000_RDT(0);

	ग_लिखोl(0, rx_ring->head);
	अगर (adapter->flags2 & FLAG2_PCIM2PCI_ARBITER_WA)
		e1000e_update_rdt_wa(rx_ring, 0);
	अन्यथा
		ग_लिखोl(0, rx_ring->tail);

	/* Enable Receive Checksum Offload क्रम TCP and UDP */
	rxcsum = er32(RXCSUM);
	अगर (adapter->netdev->features & NETIF_F_RXCSUM)
		rxcsum |= E1000_RXCSUM_TUOFL;
	अन्यथा
		rxcsum &= ~E1000_RXCSUM_TUOFL;
	ew32(RXCSUM, rxcsum);

	/* With jumbo frames, excessive C-state transition latencies result
	 * in dropped transactions.
	 */
	अगर (adapter->netdev->mtu > ETH_DATA_LEN) अणु
		u32 lat =
		    ((er32(PBA) & E1000_PBA_RXA_MASK) * 1024 -
		     adapter->max_frame_size) * 8 / 1000;

		अगर (adapter->flags & FLAG_IS_ICH) अणु
			u32 rxdctl = er32(RXDCTL(0));

			ew32(RXDCTL(0), rxdctl | 0x3 | BIT(8));
		पूर्ण

		dev_info(&adapter->pdev->dev,
			 "Some CPU C-states have been disabled in order to enable jumbo frames\n");
		cpu_latency_qos_update_request(&adapter->pm_qos_req, lat);
	पूर्ण अन्यथा अणु
		cpu_latency_qos_update_request(&adapter->pm_qos_req,
					       PM_QOS_DEFAULT_VALUE);
	पूर्ण

	/* Enable Receives */
	ew32(RCTL, rctl);
पूर्ण

/**
 * e1000e_ग_लिखो_mc_addr_list - ग_लिखो multicast addresses to MTA
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Writes multicast address list to the MTA hash table.
 * Returns: -ENOMEM on failure
 *                0 on no addresses written
 *                X on writing X addresses to MTA
 */
अटल पूर्णांक e1000e_ग_लिखो_mc_addr_list(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा netdev_hw_addr *ha;
	u8 *mta_list;
	पूर्णांक i;

	अगर (netdev_mc_empty(netdev)) अणु
		/* nothing to program, so clear mc list */
		hw->mac.ops.update_mc_addr_list(hw, शून्य, 0);
		वापस 0;
	पूर्ण

	mta_list = kसुस्मृति(netdev_mc_count(netdev), ETH_ALEN, GFP_ATOMIC);
	अगर (!mta_list)
		वापस -ENOMEM;

	/* update_mc_addr_list expects a packed array of only addresses. */
	i = 0;
	netdev_क्रम_each_mc_addr(ha, netdev)
	    स_नकल(mta_list + (i++ * ETH_ALEN), ha->addr, ETH_ALEN);

	hw->mac.ops.update_mc_addr_list(hw, mta_list, i);
	kमुक्त(mta_list);

	वापस netdev_mc_count(netdev);
पूर्ण

/**
 * e1000e_ग_लिखो_uc_addr_list - ग_लिखो unicast addresses to RAR table
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Writes unicast address list to the RAR table.
 * Returns: -ENOMEM on failure/insufficient address space
 *                0 on no addresses written
 *                X on writing X addresses to the RAR table
 **/
अटल पूर्णांक e1000e_ग_लिखो_uc_addr_list(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	अचिन्हित पूर्णांक rar_entries;
	पूर्णांक count = 0;

	rar_entries = hw->mac.ops.rar_get_count(hw);

	/* save a rar entry क्रम our hardware address */
	rar_entries--;

	/* save a rar entry क्रम the LAA workaround */
	अगर (adapter->flags & FLAG_RESET_OVERWRITES_LAA)
		rar_entries--;

	/* वापस ENOMEM indicating insufficient memory क्रम addresses */
	अगर (netdev_uc_count(netdev) > rar_entries)
		वापस -ENOMEM;

	अगर (!netdev_uc_empty(netdev) && rar_entries) अणु
		काष्ठा netdev_hw_addr *ha;

		/* ग_लिखो the addresses in reverse order to aव्योम ग_लिखो
		 * combining
		 */
		netdev_क्रम_each_uc_addr(ha, netdev) अणु
			पूर्णांक ret_val;

			अगर (!rar_entries)
				अवरोध;
			ret_val = hw->mac.ops.rar_set(hw, ha->addr, rar_entries--);
			अगर (ret_val < 0)
				वापस -ENOMEM;
			count++;
		पूर्ण
	पूर्ण

	/* zero out the reमुख्यing RAR entries not used above */
	क्रम (; rar_entries > 0; rar_entries--) अणु
		ew32(RAH(rar_entries), 0);
		ew32(RAL(rar_entries), 0);
	पूर्ण
	e1e_flush();

	वापस count;
पूर्ण

/**
 * e1000e_set_rx_mode - secondary unicast, Multicast and Promiscuous mode set
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * The nकरो_set_rx_mode entry poपूर्णांक is called whenever the unicast or multicast
 * address list or the network पूर्णांकerface flags are updated.  This routine is
 * responsible क्रम configuring the hardware क्रम proper unicast, multicast,
 * promiscuous mode, and all-multi behavior.
 **/
अटल व्योम e1000e_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 rctl;

	अगर (pm_runसमय_suspended(netdev->dev.parent))
		वापस;

	/* Check क्रम Promiscuous and All Multicast modes */
	rctl = er32(RCTL);

	/* clear the affected bits */
	rctl &= ~(E1000_RCTL_UPE | E1000_RCTL_MPE);

	अगर (netdev->flags & IFF_PROMISC) अणु
		rctl |= (E1000_RCTL_UPE | E1000_RCTL_MPE);
		/* Do not hardware filter VLANs in promisc mode */
		e1000e_vlan_filter_disable(adapter);
	पूर्ण अन्यथा अणु
		पूर्णांक count;

		अगर (netdev->flags & IFF_ALLMULTI) अणु
			rctl |= E1000_RCTL_MPE;
		पूर्ण अन्यथा अणु
			/* Write addresses to the MTA, अगर the attempt fails
			 * then we should just turn on promiscuous mode so
			 * that we can at least receive multicast traffic
			 */
			count = e1000e_ग_लिखो_mc_addr_list(netdev);
			अगर (count < 0)
				rctl |= E1000_RCTL_MPE;
		पूर्ण
		e1000e_vlan_filter_enable(adapter);
		/* Write addresses to available RAR रेजिस्टरs, अगर there is not
		 * sufficient space to store all the addresses then enable
		 * unicast promiscuous mode
		 */
		count = e1000e_ग_लिखो_uc_addr_list(netdev);
		अगर (count < 0)
			rctl |= E1000_RCTL_UPE;
	पूर्ण

	ew32(RCTL, rctl);

	अगर (netdev->features & NETIF_F_HW_VLAN_CTAG_RX)
		e1000e_vlan_strip_enable(adapter);
	अन्यथा
		e1000e_vlan_strip_disable(adapter);
पूर्ण

अटल व्योम e1000e_setup_rss_hash(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 mrqc, rxcsum;
	u32 rss_key[10];
	पूर्णांक i;

	netdev_rss_key_fill(rss_key, माप(rss_key));
	क्रम (i = 0; i < 10; i++)
		ew32(RSSRK(i), rss_key[i]);

	/* Direct all traffic to queue 0 */
	क्रम (i = 0; i < 32; i++)
		ew32(RETA(i), 0);

	/* Disable raw packet checksumming so that RSS hash is placed in
	 * descriptor on ग_लिखोback.
	 */
	rxcsum = er32(RXCSUM);
	rxcsum |= E1000_RXCSUM_PCSD;

	ew32(RXCSUM, rxcsum);

	mrqc = (E1000_MRQC_RSS_FIELD_IPV4 |
		E1000_MRQC_RSS_FIELD_IPV4_TCP |
		E1000_MRQC_RSS_FIELD_IPV6 |
		E1000_MRQC_RSS_FIELD_IPV6_TCP |
		E1000_MRQC_RSS_FIELD_IPV6_TCP_EX);

	ew32(MRQC, mrqc);
पूर्ण

/**
 * e1000e_get_base_timinca - get शेष SYSTIM समय increment attributes
 * @adapter: board निजी काष्ठाure
 * @timinca: poपूर्णांकer to वापसed समय increment attributes
 *
 * Get attributes क्रम incrementing the System Time Register SYSTIML/H at
 * the शेष base frequency, and set the cyclecounter shअगरt value.
 **/
s32 e1000e_get_base_timinca(काष्ठा e1000_adapter *adapter, u32 *timinca)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 incvalue, incperiod, shअगरt;

	/* Make sure घड़ी is enabled on I217/I218/I219  beक्रमe checking
	 * the frequency
	 */
	अगर ((hw->mac.type >= e1000_pch_lpt) &&
	    !(er32(TSYNCTXCTL) & E1000_TSYNCTXCTL_ENABLED) &&
	    !(er32(TSYNCRXCTL) & E1000_TSYNCRXCTL_ENABLED)) अणु
		u32 fextnvm7 = er32(FEXTNVM7);

		अगर (!(fextnvm7 & BIT(0))) अणु
			ew32(FEXTNVM7, fextnvm7 | BIT(0));
			e1e_flush();
		पूर्ण
	पूर्ण

	चयन (hw->mac.type) अणु
	हाल e1000_pch2lan:
		/* Stable 96MHz frequency */
		incperiod = INCPERIOD_96MHZ;
		incvalue = INCVALUE_96MHZ;
		shअगरt = INCVALUE_SHIFT_96MHZ;
		adapter->cc.shअगरt = shअगरt + INCPERIOD_SHIFT_96MHZ;
		अवरोध;
	हाल e1000_pch_lpt:
		अगर (er32(TSYNCRXCTL) & E1000_TSYNCRXCTL_SYSCFI) अणु
			/* Stable 96MHz frequency */
			incperiod = INCPERIOD_96MHZ;
			incvalue = INCVALUE_96MHZ;
			shअगरt = INCVALUE_SHIFT_96MHZ;
			adapter->cc.shअगरt = shअगरt + INCPERIOD_SHIFT_96MHZ;
		पूर्ण अन्यथा अणु
			/* Stable 25MHz frequency */
			incperiod = INCPERIOD_25MHZ;
			incvalue = INCVALUE_25MHZ;
			shअगरt = INCVALUE_SHIFT_25MHZ;
			adapter->cc.shअगरt = shअगरt;
		पूर्ण
		अवरोध;
	हाल e1000_pch_spt:
		/* Stable 24MHz frequency */
		incperiod = INCPERIOD_24MHZ;
		incvalue = INCVALUE_24MHZ;
		shअगरt = INCVALUE_SHIFT_24MHZ;
		adapter->cc.shअगरt = shअगरt;
		अवरोध;
	हाल e1000_pch_cnp:
	हाल e1000_pch_tgp:
	हाल e1000_pch_adp:
	हाल e1000_pch_mtp:
		अगर (er32(TSYNCRXCTL) & E1000_TSYNCRXCTL_SYSCFI) अणु
			/* Stable 24MHz frequency */
			incperiod = INCPERIOD_24MHZ;
			incvalue = INCVALUE_24MHZ;
			shअगरt = INCVALUE_SHIFT_24MHZ;
			adapter->cc.shअगरt = shअगरt;
		पूर्ण अन्यथा अणु
			/* Stable 38400KHz frequency */
			incperiod = INCPERIOD_38400KHZ;
			incvalue = INCVALUE_38400KHZ;
			shअगरt = INCVALUE_SHIFT_38400KHZ;
			adapter->cc.shअगरt = shअगरt;
		पूर्ण
		अवरोध;
	हाल e1000_82574:
	हाल e1000_82583:
		/* Stable 25MHz frequency */
		incperiod = INCPERIOD_25MHZ;
		incvalue = INCVALUE_25MHZ;
		shअगरt = INCVALUE_SHIFT_25MHZ;
		adapter->cc.shअगरt = shअगरt;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	*timinca = ((incperiod << E1000_TIMINCA_INCPERIOD_SHIFT) |
		    ((incvalue << shअगरt) & E1000_TIMINCA_INCVALUE_MASK));

	वापस 0;
पूर्ण

/**
 * e1000e_config_hwtstamp - configure the hwtstamp रेजिस्टरs and enable/disable
 * @adapter: board निजी काष्ठाure
 * @config: बारtamp configuration
 *
 * Outgoing समय stamping can be enabled and disabled. Play nice and
 * disable it when requested, although it shouldn't cause any overhead
 * when no packet needs it. At most one packet in the queue may be
 * marked क्रम समय stamping, otherwise it would be impossible to tell
 * क्रम sure to which packet the hardware समय stamp beदीर्घs.
 *
 * Incoming समय stamping has to be configured via the hardware filters.
 * Not all combinations are supported, in particular event type has to be
 * specअगरied. Matching the kind of event packet is not supported, with the
 * exception of "all V2 events regardless of level 2 or 4".
 **/
अटल पूर्णांक e1000e_config_hwtstamp(काष्ठा e1000_adapter *adapter,
				  काष्ठा hwtstamp_config *config)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 tsync_tx_ctl = E1000_TSYNCTXCTL_ENABLED;
	u32 tsync_rx_ctl = E1000_TSYNCRXCTL_ENABLED;
	u32 rxmtrl = 0;
	u16 rxudp = 0;
	bool is_l4 = false;
	bool is_l2 = false;
	u32 regval;

	अगर (!(adapter->flags & FLAG_HAS_HW_TIMESTAMP))
		वापस -EINVAL;

	/* flags reserved क्रम future extensions - must be zero */
	अगर (config->flags)
		वापस -EINVAL;

	चयन (config->tx_type) अणु
	हाल HWTSTAMP_TX_OFF:
		tsync_tx_ctl = 0;
		अवरोध;
	हाल HWTSTAMP_TX_ON:
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	चयन (config->rx_filter) अणु
	हाल HWTSTAMP_FILTER_NONE:
		tsync_rx_ctl = 0;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_SYNC:
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_L4_V1;
		rxmtrl = E1000_RXMTRL_PTP_V1_SYNC_MESSAGE;
		is_l4 = true;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_DELAY_REQ:
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_L4_V1;
		rxmtrl = E1000_RXMTRL_PTP_V1_DELAY_REQ_MESSAGE;
		is_l4 = true;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
		/* Also समय stamps V2 L2 Path Delay Request/Response */
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_L2_V2;
		rxmtrl = E1000_RXMTRL_PTP_V2_SYNC_MESSAGE;
		is_l2 = true;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
		/* Also समय stamps V2 L2 Path Delay Request/Response. */
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_L2_V2;
		rxmtrl = E1000_RXMTRL_PTP_V2_DELAY_REQ_MESSAGE;
		is_l2 = true;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
		/* Hardware cannot filter just V2 L4 Sync messages */
		fallthrough;
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
		/* Also समय stamps V2 Path Delay Request/Response. */
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_L2_L4_V2;
		rxmtrl = E1000_RXMTRL_PTP_V2_SYNC_MESSAGE;
		is_l2 = true;
		is_l4 = true;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
		/* Hardware cannot filter just V2 L4 Delay Request messages */
		fallthrough;
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		/* Also समय stamps V2 Path Delay Request/Response. */
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_L2_L4_V2;
		rxmtrl = E1000_RXMTRL_PTP_V2_DELAY_REQ_MESSAGE;
		is_l2 = true;
		is_l4 = true;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V2_L4_EVENT:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_EVENT:
		/* Hardware cannot filter just V2 L4 or L2 Event messages */
		fallthrough;
	हाल HWTSTAMP_FILTER_PTP_V2_EVENT:
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_EVENT_V2;
		config->rx_filter = HWTSTAMP_FILTER_PTP_V2_EVENT;
		is_l2 = true;
		is_l4 = true;
		अवरोध;
	हाल HWTSTAMP_FILTER_PTP_V1_L4_EVENT:
		/* For V1, the hardware can only filter Sync messages or
		 * Delay Request messages but not both so fall-through to
		 * समय stamp all packets.
		 */
		fallthrough;
	हाल HWTSTAMP_FILTER_NTP_ALL:
	हाल HWTSTAMP_FILTER_ALL:
		is_l2 = true;
		is_l4 = true;
		tsync_rx_ctl |= E1000_TSYNCRXCTL_TYPE_ALL;
		config->rx_filter = HWTSTAMP_FILTER_ALL;
		अवरोध;
	शेष:
		वापस -दुस्फल;
	पूर्ण

	adapter->hwtstamp_config = *config;

	/* enable/disable Tx h/w समय stamping */
	regval = er32(TSYNCTXCTL);
	regval &= ~E1000_TSYNCTXCTL_ENABLED;
	regval |= tsync_tx_ctl;
	ew32(TSYNCTXCTL, regval);
	अगर ((er32(TSYNCTXCTL) & E1000_TSYNCTXCTL_ENABLED) !=
	    (regval & E1000_TSYNCTXCTL_ENABLED)) अणु
		e_err("Timesync Tx Control register not set as expected\n");
		वापस -EAGAIN;
	पूर्ण

	/* enable/disable Rx h/w समय stamping */
	regval = er32(TSYNCRXCTL);
	regval &= ~(E1000_TSYNCRXCTL_ENABLED | E1000_TSYNCRXCTL_TYPE_MASK);
	regval |= tsync_rx_ctl;
	ew32(TSYNCRXCTL, regval);
	अगर ((er32(TSYNCRXCTL) & (E1000_TSYNCRXCTL_ENABLED |
				 E1000_TSYNCRXCTL_TYPE_MASK)) !=
	    (regval & (E1000_TSYNCRXCTL_ENABLED |
		       E1000_TSYNCRXCTL_TYPE_MASK))) अणु
		e_err("Timesync Rx Control register not set as expected\n");
		वापस -EAGAIN;
	पूर्ण

	/* L2: define ethertype filter क्रम समय stamped packets */
	अगर (is_l2)
		rxmtrl |= ETH_P_1588;

	/* define which PTP packets get समय stamped */
	ew32(RXMTRL, rxmtrl);

	/* Filter by destination port */
	अगर (is_l4) अणु
		rxudp = PTP_EV_PORT;
		cpu_to_be16s(&rxudp);
	पूर्ण
	ew32(RXUDP, rxudp);

	e1e_flush();

	/* Clear TSYNCRXCTL_VALID & TSYNCTXCTL_VALID bit */
	er32(RXSTMPH);
	er32(TXSTMPH);

	वापस 0;
पूर्ण

/**
 * e1000_configure - configure the hardware क्रम Rx and Tx
 * @adapter: निजी board काष्ठाure
 **/
अटल व्योम e1000_configure(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_ring *rx_ring = adapter->rx_ring;

	e1000e_set_rx_mode(adapter->netdev);

	e1000_restore_vlan(adapter);
	e1000_init_manageability_pt(adapter);

	e1000_configure_tx(adapter);

	अगर (adapter->netdev->features & NETIF_F_RXHASH)
		e1000e_setup_rss_hash(adapter);
	e1000_setup_rctl(adapter);
	e1000_configure_rx(adapter);
	adapter->alloc_rx_buf(rx_ring, e1000_desc_unused(rx_ring), GFP_KERNEL);
पूर्ण

/**
 * e1000e_घातer_up_phy - restore link in हाल the phy was घातered करोwn
 * @adapter: address of board निजी काष्ठाure
 *
 * The phy may be घातered करोwn to save घातer and turn off link when the
 * driver is unloaded and wake on lan is not enabled (among others)
 * *** this routine MUST be followed by a call to e1000e_reset ***
 **/
व्योम e1000e_घातer_up_phy(काष्ठा e1000_adapter *adapter)
अणु
	अगर (adapter->hw.phy.ops.घातer_up)
		adapter->hw.phy.ops.घातer_up(&adapter->hw);

	adapter->hw.mac.ops.setup_link(&adapter->hw);
पूर्ण

/**
 * e1000_घातer_करोwn_phy - Power करोwn the PHY
 * @adapter: board निजी काष्ठाure
 *
 * Power करोwn the PHY so no link is implied when पूर्णांकerface is करोwn.
 * The PHY cannot be घातered करोwn अगर management or WoL is active.
 */
अटल व्योम e1000_घातer_करोwn_phy(काष्ठा e1000_adapter *adapter)
अणु
	अगर (adapter->hw.phy.ops.घातer_करोwn)
		adapter->hw.phy.ops.घातer_करोwn(&adapter->hw);
पूर्ण

/**
 * e1000_flush_tx_ring - हटाओ all descriptors from the tx_ring
 * @adapter: board निजी काष्ठाure
 *
 * We want to clear all pending descriptors from the TX ring.
 * zeroing happens when the HW पढ़ोs the regs. We  assign the ring itself as
 * the data of the next descriptor. We करोn't care about the data we are about
 * to reset the HW.
 */
अटल व्योम e1000_flush_tx_ring(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_ring *tx_ring = adapter->tx_ring;
	काष्ठा e1000_tx_desc *tx_desc = शून्य;
	u32 tdt, tctl, txd_lower = E1000_TXD_CMD_IFCS;
	u16 size = 512;

	tctl = er32(TCTL);
	ew32(TCTL, tctl | E1000_TCTL_EN);
	tdt = er32(TDT(0));
	BUG_ON(tdt != tx_ring->next_to_use);
	tx_desc =  E1000_TX_DESC(*tx_ring, tx_ring->next_to_use);
	tx_desc->buffer_addr = cpu_to_le64(tx_ring->dma);

	tx_desc->lower.data = cpu_to_le32(txd_lower | size);
	tx_desc->upper.data = 0;
	/* flush descriptors to memory beक्रमe notअगरying the HW */
	wmb();
	tx_ring->next_to_use++;
	अगर (tx_ring->next_to_use == tx_ring->count)
		tx_ring->next_to_use = 0;
	ew32(TDT(0), tx_ring->next_to_use);
	usleep_range(200, 250);
पूर्ण

/**
 * e1000_flush_rx_ring - हटाओ all descriptors from the rx_ring
 * @adapter: board निजी काष्ठाure
 *
 * Mark all descriptors in the RX ring as consumed and disable the rx ring
 */
अटल व्योम e1000_flush_rx_ring(काष्ठा e1000_adapter *adapter)
अणु
	u32 rctl, rxdctl;
	काष्ठा e1000_hw *hw = &adapter->hw;

	rctl = er32(RCTL);
	ew32(RCTL, rctl & ~E1000_RCTL_EN);
	e1e_flush();
	usleep_range(100, 150);

	rxdctl = er32(RXDCTL(0));
	/* zero the lower 14 bits (prefetch and host thresholds) */
	rxdctl &= 0xffffc000;

	/* update thresholds: prefetch threshold to 31, host threshold to 1
	 * and make sure the granularity is "descriptors" and not "cache lines"
	 */
	rxdctl |= (0x1F | BIT(8) | E1000_RXDCTL_THRESH_UNIT_DESC);

	ew32(RXDCTL(0), rxdctl);
	/* momentarily enable the RX ring क्रम the changes to take effect */
	ew32(RCTL, rctl | E1000_RCTL_EN);
	e1e_flush();
	usleep_range(100, 150);
	ew32(RCTL, rctl & ~E1000_RCTL_EN);
पूर्ण

/**
 * e1000_flush_desc_rings - हटाओ all descriptors from the descriptor rings
 * @adapter: board निजी काष्ठाure
 *
 * In i219, the descriptor rings must be emptied beक्रमe resetting the HW
 * or beक्रमe changing the device state to D3 during runसमय (runसमय PM).
 *
 * Failure to करो this will cause the HW to enter a unit hang state which can
 * only be released by PCI reset on the device
 *
 */

अटल व्योम e1000_flush_desc_rings(काष्ठा e1000_adapter *adapter)
अणु
	u16 hang_state;
	u32 fext_nvm11, tdlen;
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* First, disable MULR fix in FEXTNVM11 */
	fext_nvm11 = er32(FEXTNVM11);
	fext_nvm11 |= E1000_FEXTNVM11_DISABLE_MULR_FIX;
	ew32(FEXTNVM11, fext_nvm11);
	/* करो nothing अगर we're not in faulty state, or अगर the queue is empty */
	tdlen = er32(TDLEN(0));
	pci_पढ़ो_config_word(adapter->pdev, PCICFG_DESC_RING_STATUS,
			     &hang_state);
	अगर (!(hang_state & FLUSH_DESC_REQUIRED) || !tdlen)
		वापस;
	e1000_flush_tx_ring(adapter);
	/* recheck, maybe the fault is caused by the rx ring */
	pci_पढ़ो_config_word(adapter->pdev, PCICFG_DESC_RING_STATUS,
			     &hang_state);
	अगर (hang_state & FLUSH_DESC_REQUIRED)
		e1000_flush_rx_ring(adapter);
पूर्ण

/**
 * e1000e_systim_reset - reset the बारync रेजिस्टरs after a hardware reset
 * @adapter: board निजी काष्ठाure
 *
 * When the MAC is reset, all hardware bits क्रम बारync will be reset to the
 * शेष values. This function will restore the settings last in place.
 * Since the घड़ी SYSTIME रेजिस्टरs are reset, we will simply restore the
 * cyclecounter to the kernel real घड़ी समय.
 **/
अटल व्योम e1000e_systim_reset(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा ptp_घड़ी_info *info = &adapter->ptp_घड़ी_info;
	काष्ठा e1000_hw *hw = &adapter->hw;
	अचिन्हित दीर्घ flags;
	u32 timinca;
	s32 ret_val;

	अगर (!(adapter->flags & FLAG_HAS_HW_TIMESTAMP))
		वापस;

	अगर (info->adjfreq) अणु
		/* restore the previous ptp frequency delta */
		ret_val = info->adjfreq(info, adapter->ptp_delta);
	पूर्ण अन्यथा अणु
		/* set the शेष base frequency अगर no adjusपंचांगent possible */
		ret_val = e1000e_get_base_timinca(adapter, &timinca);
		अगर (!ret_val)
			ew32(TIMINCA, timinca);
	पूर्ण

	अगर (ret_val) अणु
		dev_warn(&adapter->pdev->dev,
			 "Failed to restore TIMINCA clock rate delta: %d\n",
			 ret_val);
		वापस;
	पूर्ण

	/* reset the systim ns समय counter */
	spin_lock_irqsave(&adapter->systim_lock, flags);
	समयcounter_init(&adapter->tc, &adapter->cc,
			 kसमय_प्रकारo_ns(kसमय_get_real()));
	spin_unlock_irqrestore(&adapter->systim_lock, flags);

	/* restore the previous hwtstamp configuration settings */
	e1000e_config_hwtstamp(adapter, &adapter->hwtstamp_config);
पूर्ण

/**
 * e1000e_reset - bring the hardware पूर्णांकo a known good state
 * @adapter: board निजी काष्ठाure
 *
 * This function boots the hardware and enables some settings that
 * require a configuration cycle of the hardware - those cannot be
 * set/changed during runसमय. After reset the device needs to be
 * properly configured क्रम Rx, Tx etc.
 */
व्योम e1000e_reset(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_mac_info *mac = &adapter->hw.mac;
	काष्ठा e1000_fc_info *fc = &adapter->hw.fc;
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 tx_space, min_tx_space, min_rx_space;
	u32 pba = adapter->pba;
	u16 hwm;

	/* reset Packet Buffer Allocation to शेष */
	ew32(PBA, pba);

	अगर (adapter->max_frame_size > (VLAN_ETH_FRAME_LEN + ETH_FCS_LEN)) अणु
		/* To मुख्यtain wire speed transmits, the Tx FIFO should be
		 * large enough to accommodate two full transmit packets,
		 * rounded up to the next 1KB and expressed in KB.  Likewise,
		 * the Rx FIFO should be large enough to accommodate at least
		 * one full receive packet and is similarly rounded up and
		 * expressed in KB.
		 */
		pba = er32(PBA);
		/* upper 16 bits has Tx packet buffer allocation size in KB */
		tx_space = pba >> 16;
		/* lower 16 bits has Rx packet buffer allocation size in KB */
		pba &= 0xffff;
		/* the Tx fअगरo also stores 16 bytes of inक्रमmation about the Tx
		 * but करोn't include ethernet FCS because hardware appends it
		 */
		min_tx_space = (adapter->max_frame_size +
				माप(काष्ठा e1000_tx_desc) - ETH_FCS_LEN) * 2;
		min_tx_space = ALIGN(min_tx_space, 1024);
		min_tx_space >>= 10;
		/* software strips receive CRC, so leave room क्रम it */
		min_rx_space = adapter->max_frame_size;
		min_rx_space = ALIGN(min_rx_space, 1024);
		min_rx_space >>= 10;

		/* If current Tx allocation is less than the min Tx FIFO size,
		 * and the min Tx FIFO size is less than the current Rx FIFO
		 * allocation, take space away from current Rx allocation
		 */
		अगर ((tx_space < min_tx_space) &&
		    ((min_tx_space - tx_space) < pba)) अणु
			pba -= min_tx_space - tx_space;

			/* अगर लघु on Rx space, Rx wins and must trump Tx
			 * adjusपंचांगent
			 */
			अगर (pba < min_rx_space)
				pba = min_rx_space;
		पूर्ण

		ew32(PBA, pba);
	पूर्ण

	/* flow control settings
	 *
	 * The high water mark must be low enough to fit one full frame
	 * (or the size used क्रम early receive) above it in the Rx FIFO.
	 * Set it to the lower of:
	 * - 90% of the Rx FIFO size, and
	 * - the full Rx FIFO size minus one full frame
	 */
	अगर (adapter->flags & FLAG_DISABLE_FC_PAUSE_TIME)
		fc->छोड़ो_समय = 0xFFFF;
	अन्यथा
		fc->छोड़ो_समय = E1000_FC_PAUSE_TIME;
	fc->send_xon = true;
	fc->current_mode = fc->requested_mode;

	चयन (hw->mac.type) अणु
	हाल e1000_ich9lan:
	हाल e1000_ich10lan:
		अगर (adapter->netdev->mtu > ETH_DATA_LEN) अणु
			pba = 14;
			ew32(PBA, pba);
			fc->high_water = 0x2800;
			fc->low_water = fc->high_water - 8;
			अवरोध;
		पूर्ण
		fallthrough;
	शेष:
		hwm = min(((pba << 10) * 9 / 10),
			  ((pba << 10) - adapter->max_frame_size));

		fc->high_water = hwm & E1000_FCRTH_RTH;	/* 8-byte granularity */
		fc->low_water = fc->high_water - 8;
		अवरोध;
	हाल e1000_pchlan:
		/* Workaround PCH LOM adapter hangs with certain network
		 * loads.  If hangs persist, try disabling Tx flow control.
		 */
		अगर (adapter->netdev->mtu > ETH_DATA_LEN) अणु
			fc->high_water = 0x3500;
			fc->low_water = 0x1500;
		पूर्ण अन्यथा अणु
			fc->high_water = 0x5000;
			fc->low_water = 0x3000;
		पूर्ण
		fc->refresh_समय = 0x1000;
		अवरोध;
	हाल e1000_pch2lan:
	हाल e1000_pch_lpt:
	हाल e1000_pch_spt:
	हाल e1000_pch_cnp:
	हाल e1000_pch_tgp:
	हाल e1000_pch_adp:
	हाल e1000_pch_mtp:
		fc->refresh_समय = 0xFFFF;
		fc->छोड़ो_समय = 0xFFFF;

		अगर (adapter->netdev->mtu <= ETH_DATA_LEN) अणु
			fc->high_water = 0x05C20;
			fc->low_water = 0x05048;
			अवरोध;
		पूर्ण

		pba = 14;
		ew32(PBA, pba);
		fc->high_water = ((pba << 10) * 9 / 10) & E1000_FCRTH_RTH;
		fc->low_water = ((pba << 10) * 8 / 10) & E1000_FCRTL_RTL;
		अवरोध;
	पूर्ण

	/* Alignment of Tx data is on an arbitrary byte boundary with the
	 * maximum size per Tx descriptor limited only to the transmit
	 * allocation of the packet buffer minus 96 bytes with an upper
	 * limit of 24KB due to receive synchronization limitations.
	 */
	adapter->tx_fअगरo_limit = min_t(u32, ((er32(PBA) >> 16) << 10) - 96,
				       24 << 10);

	/* Disable Adaptive Interrupt Moderation अगर 2 full packets cannot
	 * fit in receive buffer.
	 */
	अगर (adapter->itr_setting & 0x3) अणु
		अगर ((adapter->max_frame_size * 2) > (pba << 10)) अणु
			अगर (!(adapter->flags2 & FLAG2_DISABLE_AIM)) अणु
				dev_info(&adapter->pdev->dev,
					 "Interrupt Throttle Rate off\n");
				adapter->flags2 |= FLAG2_DISABLE_AIM;
				e1000e_ग_लिखो_itr(adapter, 0);
			पूर्ण
		पूर्ण अन्यथा अगर (adapter->flags2 & FLAG2_DISABLE_AIM) अणु
			dev_info(&adapter->pdev->dev,
				 "Interrupt Throttle Rate on\n");
			adapter->flags2 &= ~FLAG2_DISABLE_AIM;
			adapter->itr = 20000;
			e1000e_ग_लिखो_itr(adapter, adapter->itr);
		पूर्ण
	पूर्ण

	अगर (hw->mac.type >= e1000_pch_spt)
		e1000_flush_desc_rings(adapter);
	/* Allow समय क्रम pending master requests to run */
	mac->ops.reset_hw(hw);

	/* For parts with AMT enabled, let the firmware know
	 * that the network पूर्णांकerface is in control
	 */
	अगर (adapter->flags & FLAG_HAS_AMT)
		e1000e_get_hw_control(adapter);

	ew32(WUC, 0);

	अगर (mac->ops.init_hw(hw))
		e_err("Hardware Error\n");

	e1000_update_mng_vlan(adapter);

	/* Enable h/w to recognize an 802.1Q VLAN Ethernet packet */
	ew32(VET, ETH_P_8021Q);

	e1000e_reset_adaptive(hw);

	/* restore systim and hwtstamp settings */
	e1000e_systim_reset(adapter);

	/* Set EEE advertisement as appropriate */
	अगर (adapter->flags2 & FLAG2_HAS_EEE) अणु
		s32 ret_val;
		u16 adv_addr;

		चयन (hw->phy.type) अणु
		हाल e1000_phy_82579:
			adv_addr = I82579_EEE_ADVERTISEMENT;
			अवरोध;
		हाल e1000_phy_i217:
			adv_addr = I217_EEE_ADVERTISEMENT;
			अवरोध;
		शेष:
			dev_err(&adapter->pdev->dev,
				"Invalid PHY type setting EEE advertisement\n");
			वापस;
		पूर्ण

		ret_val = hw->phy.ops.acquire(hw);
		अगर (ret_val) अणु
			dev_err(&adapter->pdev->dev,
				"EEE advertisement - unable to acquire PHY\n");
			वापस;
		पूर्ण

		e1000_ग_लिखो_emi_reg_locked(hw, adv_addr,
					   hw->dev_spec.ich8lan.eee_disable ?
					   0 : adapter->eee_advert);

		hw->phy.ops.release(hw);
	पूर्ण

	अगर (!netअगर_running(adapter->netdev) &&
	    !test_bit(__E1000_TESTING, &adapter->state))
		e1000_घातer_करोwn_phy(adapter);

	e1000_get_phy_info(hw);

	अगर ((adapter->flags & FLAG_HAS_SMART_POWER_DOWN) &&
	    !(adapter->flags & FLAG_SMART_POWER_DOWN)) अणु
		u16 phy_data = 0;
		/* speed up समय to link by disabling smart घातer करोwn, ignore
		 * the वापस value of this function because there is nothing
		 * dअगरferent we would करो अगर it failed
		 */
		e1e_rphy(hw, IGP02E1000_PHY_POWER_MGMT, &phy_data);
		phy_data &= ~IGP02E1000_PM_SPD;
		e1e_wphy(hw, IGP02E1000_PHY_POWER_MGMT, phy_data);
	पूर्ण
	अगर (hw->mac.type >= e1000_pch_spt && adapter->पूर्णांक_mode == 0) अणु
		u32 reg;

		/* Fextnvm7 @ 0xe4[2] = 1 */
		reg = er32(FEXTNVM7);
		reg |= E1000_FEXTNVM7_SIDE_CLK_UNGATE;
		ew32(FEXTNVM7, reg);
		/* Fextnvm9 @ 0x5bb4[13:12] = 11 */
		reg = er32(FEXTNVM9);
		reg |= E1000_FEXTNVM9_IOSFSB_CLKGATE_DIS |
		       E1000_FEXTNVM9_IOSFSB_CLKREQ_DIS;
		ew32(FEXTNVM9, reg);
	पूर्ण

पूर्ण

/**
 * e1000e_trigger_lsc - trigger an LSC पूर्णांकerrupt
 * @adapter: 
 *
 * Fire a link status change पूर्णांकerrupt to start the watchकरोg.
 **/
अटल व्योम e1000e_trigger_lsc(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	अगर (adapter->msix_entries)
		ew32(ICS, E1000_ICS_LSC | E1000_ICS_OTHER);
	अन्यथा
		ew32(ICS, E1000_ICS_LSC);
पूर्ण

व्योम e1000e_up(काष्ठा e1000_adapter *adapter)
अणु
	/* hardware has been reset, we need to reload some things */
	e1000_configure(adapter);

	clear_bit(__E1000_DOWN, &adapter->state);

	अगर (adapter->msix_entries)
		e1000_configure_msix(adapter);
	e1000_irq_enable(adapter);

	/* Tx queue started by watchकरोg समयr when link is up */

	e1000e_trigger_lsc(adapter);
पूर्ण

अटल व्योम e1000e_flush_descriptors(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	अगर (!(adapter->flags2 & FLAG2_DMA_BURST))
		वापस;

	/* flush pending descriptor ग_लिखोbacks to memory */
	ew32(TIDV, adapter->tx_पूर्णांक_delay | E1000_TIDV_FPD);
	ew32(RDTR, adapter->rx_पूर्णांक_delay | E1000_RDTR_FPD);

	/* execute the ग_लिखोs immediately */
	e1e_flush();

	/* due to rare timing issues, ग_लिखो to TIDV/RDTR again to ensure the
	 * ग_लिखो is successful
	 */
	ew32(TIDV, adapter->tx_पूर्णांक_delay | E1000_TIDV_FPD);
	ew32(RDTR, adapter->rx_पूर्णांक_delay | E1000_RDTR_FPD);

	/* execute the ग_लिखोs immediately */
	e1e_flush();
पूर्ण

अटल व्योम e1000e_update_stats(काष्ठा e1000_adapter *adapter);

/**
 * e1000e_करोwn - quiesce the device and optionally reset the hardware
 * @adapter: board निजी काष्ठाure
 * @reset: boolean flag to reset the hardware or not
 */
व्योम e1000e_करोwn(काष्ठा e1000_adapter *adapter, bool reset)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 tctl, rctl;

	/* संकेत that we're करोwn so the पूर्णांकerrupt handler करोes not
	 * reschedule our watchकरोg समयr
	 */
	set_bit(__E1000_DOWN, &adapter->state);

	netअगर_carrier_off(netdev);

	/* disable receives in the hardware */
	rctl = er32(RCTL);
	अगर (!(adapter->flags2 & FLAG2_NO_DISABLE_RX))
		ew32(RCTL, rctl & ~E1000_RCTL_EN);
	/* flush and sleep below */

	netअगर_stop_queue(netdev);

	/* disable transmits in the hardware */
	tctl = er32(TCTL);
	tctl &= ~E1000_TCTL_EN;
	ew32(TCTL, tctl);

	/* flush both disables and रुको क्रम them to finish */
	e1e_flush();
	usleep_range(10000, 11000);

	e1000_irq_disable(adapter);

	napi_synchronize(&adapter->napi);

	del_समयr_sync(&adapter->watchकरोg_समयr);
	del_समयr_sync(&adapter->phy_info_समयr);

	spin_lock(&adapter->stats64_lock);
	e1000e_update_stats(adapter);
	spin_unlock(&adapter->stats64_lock);

	e1000e_flush_descriptors(adapter);

	adapter->link_speed = 0;
	adapter->link_duplex = 0;

	/* Disable Si errata workaround on PCHx क्रम jumbo frame flow */
	अगर ((hw->mac.type >= e1000_pch2lan) &&
	    (adapter->netdev->mtu > ETH_DATA_LEN) &&
	    e1000_lv_jumbo_workaround_ich8lan(hw, false))
		e_dbg("failed to disable jumbo frame workaround mode\n");

	अगर (!pci_channel_offline(adapter->pdev)) अणु
		अगर (reset)
			e1000e_reset(adapter);
		अन्यथा अगर (hw->mac.type >= e1000_pch_spt)
			e1000_flush_desc_rings(adapter);
	पूर्ण
	e1000_clean_tx_ring(adapter->tx_ring);
	e1000_clean_rx_ring(adapter->rx_ring);
पूर्ण

व्योम e1000e_reinit_locked(काष्ठा e1000_adapter *adapter)
अणु
	might_sleep();
	जबतक (test_and_set_bit(__E1000_RESETTING, &adapter->state))
		usleep_range(1000, 1100);
	e1000e_करोwn(adapter, true);
	e1000e_up(adapter);
	clear_bit(__E1000_RESETTING, &adapter->state);
पूर्ण

/**
 * e1000e_sanitize_systim - sanitize raw cycle counter पढ़ोs
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @systim: PHC समय value पढ़ो, sanitized and वापसed
 * @sts: काष्ठाure to hold प्रणाली समय beक्रमe and after पढ़ोing SYSTIML,
 * may be शून्य
 *
 * Errata क्रम 82574/82583 possible bad bits पढ़ो from SYSTIMH/L:
 * check to see that the समय is incrementing at a reasonable
 * rate and is a multiple of incvalue.
 **/
अटल u64 e1000e_sanitize_systim(काष्ठा e1000_hw *hw, u64 systim,
				  काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	u64 समय_delta, rem, temp;
	u64 systim_next;
	u32 incvalue;
	पूर्णांक i;

	incvalue = er32(TIMINCA) & E1000_TIMINCA_INCVALUE_MASK;
	क्रम (i = 0; i < E1000_MAX_82574_SYSTIM_REREADS; i++) अणु
		/* latch SYSTIMH on पढ़ो of SYSTIML */
		ptp_पढ़ो_प्रणाली_prets(sts);
		systim_next = (u64)er32(SYSTIML);
		ptp_पढ़ो_प्रणाली_postts(sts);
		systim_next |= (u64)er32(SYSTIMH) << 32;

		समय_delta = systim_next - systim;
		temp = समय_delta;
		/* VMWare users have seen incvalue of zero, करोn't भाग / 0 */
		rem = incvalue ? करो_भाग(temp, incvalue) : (समय_delta != 0);

		systim = systim_next;

		अगर ((समय_delta < E1000_82574_SYSTIM_EPSILON) && (rem == 0))
			अवरोध;
	पूर्ण

	वापस systim;
पूर्ण

/**
 * e1000e_पढ़ो_systim - पढ़ो SYSTIM रेजिस्टर
 * @adapter: board निजी काष्ठाure
 * @sts: काष्ठाure which will contain प्रणाली समय beक्रमe and after पढ़ोing
 * SYSTIML, may be शून्य
 **/
u64 e1000e_पढ़ो_systim(काष्ठा e1000_adapter *adapter,
		       काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 sysसमयl, sysसमयl_2, sysसमयh;
	u64 systim;
	/* SYSTIMH latching upon SYSTIML पढ़ो करोes not work well.
	 * This means that अगर SYSTIML overflows after we पढ़ो it but beक्रमe
	 * we पढ़ो SYSTIMH, the value of SYSTIMH has been incremented and we
	 * will experience a huge non linear increment in the sysसमय value
	 * to fix that we test क्रम overflow and अगर true, we re-पढ़ो sysसमय.
	 */
	ptp_पढ़ो_प्रणाली_prets(sts);
	sysसमयl = er32(SYSTIML);
	ptp_पढ़ो_प्रणाली_postts(sts);
	sysसमयh = er32(SYSTIMH);
	/* Is sysसमयl is so large that overflow is possible? */
	अगर (sysसमयl >= (u32)0xffffffff - E1000_TIMINCA_INCVALUE_MASK) अणु
		ptp_पढ़ो_प्रणाली_prets(sts);
		sysसमयl_2 = er32(SYSTIML);
		ptp_पढ़ो_प्रणाली_postts(sts);
		अगर (sysसमयl > sysसमयl_2) अणु
			/* There was an overflow, पढ़ो again SYSTIMH, and use
			 * sysसमयl_2
			 */
			sysसमयh = er32(SYSTIMH);
			sysसमयl = sysसमयl_2;
		पूर्ण
	पूर्ण
	systim = (u64)sysसमयl;
	systim |= (u64)sysसमयh << 32;

	अगर (adapter->flags2 & FLAG2_CHECK_SYSTIM_OVERFLOW)
		systim = e1000e_sanitize_systim(hw, systim, sts);

	वापस systim;
पूर्ण

/**
 * e1000e_cyclecounter_पढ़ो - पढ़ो raw cycle counter (used by समय counter)
 * @cc: cyclecounter काष्ठाure
 **/
अटल u64 e1000e_cyclecounter_पढ़ो(स्थिर काष्ठा cyclecounter *cc)
अणु
	काष्ठा e1000_adapter *adapter = container_of(cc, काष्ठा e1000_adapter,
						     cc);

	वापस e1000e_पढ़ो_systim(adapter, शून्य);
पूर्ण

/**
 * e1000_sw_init - Initialize general software काष्ठाures (काष्ठा e1000_adapter)
 * @adapter: board निजी काष्ठाure to initialize
 *
 * e1000_sw_init initializes the Adapter निजी data काष्ठाure.
 * Fields are initialized based on PCI device inक्रमmation and
 * OS network device settings (MTU size).
 **/
अटल पूर्णांक e1000_sw_init(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;

	adapter->rx_buffer_len = VLAN_ETH_FRAME_LEN + ETH_FCS_LEN;
	adapter->rx_ps_bsize0 = 128;
	adapter->max_frame_size = netdev->mtu + VLAN_ETH_HLEN + ETH_FCS_LEN;
	adapter->min_frame_size = ETH_ZLEN + ETH_FCS_LEN;
	adapter->tx_ring_count = E1000_DEFAULT_TXD;
	adapter->rx_ring_count = E1000_DEFAULT_RXD;

	spin_lock_init(&adapter->stats64_lock);

	e1000e_set_पूर्णांकerrupt_capability(adapter);

	अगर (e1000_alloc_queues(adapter))
		वापस -ENOMEM;

	/* Setup hardware समय stamping cyclecounter */
	अगर (adapter->flags & FLAG_HAS_HW_TIMESTAMP) अणु
		adapter->cc.पढ़ो = e1000e_cyclecounter_पढ़ो;
		adapter->cc.mask = CYCLECOUNTER_MASK(64);
		adapter->cc.mult = 1;
		/* cc.shअगरt set in e1000e_get_base_tininca() */

		spin_lock_init(&adapter->systim_lock);
		INIT_WORK(&adapter->tx_hwtstamp_work, e1000e_tx_hwtstamp_work);
	पूर्ण

	/* Explicitly disable IRQ since the NIC can be in any state. */
	e1000_irq_disable(adapter);

	set_bit(__E1000_DOWN, &adapter->state);
	वापस 0;
पूर्ण

/**
 * e1000_पूर्णांकr_msi_test - Interrupt Handler
 * @irq: पूर्णांकerrupt number
 * @data: poपूर्णांकer to a network पूर्णांकerface device काष्ठाure
 **/
अटल irqवापस_t e1000_पूर्णांकr_msi_test(पूर्णांक __always_unused irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 icr = er32(ICR);

	e_dbg("icr is %08X\n", icr);
	अगर (icr & E1000_ICR_RXSEQ) अणु
		adapter->flags &= ~FLAG_MSI_TEST_FAILED;
		/* Force memory ग_लिखोs to complete beक्रमe acknowledging the
		 * पूर्णांकerrupt is handled.
		 */
		wmb();
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * e1000_test_msi_पूर्णांकerrupt - Returns 0 क्रम successful test
 * @adapter: board निजी काष्ठा
 *
 * code flow taken from tg3.c
 **/
अटल पूर्णांक e1000_test_msi_पूर्णांकerrupt(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक err;

	/* poll_enable hasn't been called yet, so don't need disable */
	/* clear any pending events */
	er32(ICR);

	/* मुक्त the real vector and request a test handler */
	e1000_मुक्त_irq(adapter);
	e1000e_reset_पूर्णांकerrupt_capability(adapter);

	/* Assume that the test fails, अगर it succeeds then the test
	 * MSI irq handler will unset this flag
	 */
	adapter->flags |= FLAG_MSI_TEST_FAILED;

	err = pci_enable_msi(adapter->pdev);
	अगर (err)
		जाओ msi_test_failed;

	err = request_irq(adapter->pdev->irq, e1000_पूर्णांकr_msi_test, 0,
			  netdev->name, netdev);
	अगर (err) अणु
		pci_disable_msi(adapter->pdev);
		जाओ msi_test_failed;
	पूर्ण

	/* Force memory ग_लिखोs to complete beक्रमe enabling and firing an
	 * पूर्णांकerrupt.
	 */
	wmb();

	e1000_irq_enable(adapter);

	/* fire an unusual पूर्णांकerrupt on the test handler */
	ew32(ICS, E1000_ICS_RXSEQ);
	e1e_flush();
	msleep(100);

	e1000_irq_disable(adapter);

	rmb();			/* पढ़ो flags after पूर्णांकerrupt has been fired */

	अगर (adapter->flags & FLAG_MSI_TEST_FAILED) अणु
		adapter->पूर्णांक_mode = E1000E_INT_MODE_LEGACY;
		e_info("MSI interrupt test failed, using legacy interrupt.\n");
	पूर्ण अन्यथा अणु
		e_dbg("MSI interrupt test succeeded!\n");
	पूर्ण

	मुक्त_irq(adapter->pdev->irq, netdev);
	pci_disable_msi(adapter->pdev);

msi_test_failed:
	e1000e_set_पूर्णांकerrupt_capability(adapter);
	वापस e1000_request_irq(adapter);
पूर्ण

/**
 * e1000_test_msi - Returns 0 अगर MSI test succeeds or INTx mode is restored
 * @adapter: board निजी काष्ठा
 *
 * code flow taken from tg3.c, called with e1000 पूर्णांकerrupts disabled.
 **/
अटल पूर्णांक e1000_test_msi(काष्ठा e1000_adapter *adapter)
अणु
	पूर्णांक err;
	u16 pci_cmd;

	अगर (!(adapter->flags & FLAG_MSI_ENABLED))
		वापस 0;

	/* disable SERR in हाल the MSI ग_लिखो causes a master पात */
	pci_पढ़ो_config_word(adapter->pdev, PCI_COMMAND, &pci_cmd);
	अगर (pci_cmd & PCI_COMMAND_SERR)
		pci_ग_लिखो_config_word(adapter->pdev, PCI_COMMAND,
				      pci_cmd & ~PCI_COMMAND_SERR);

	err = e1000_test_msi_पूर्णांकerrupt(adapter);

	/* re-enable SERR */
	अगर (pci_cmd & PCI_COMMAND_SERR) अणु
		pci_पढ़ो_config_word(adapter->pdev, PCI_COMMAND, &pci_cmd);
		pci_cmd |= PCI_COMMAND_SERR;
		pci_ग_लिखो_config_word(adapter->pdev, PCI_COMMAND, pci_cmd);
	पूर्ण

	वापस err;
पूर्ण

/**
 * e1000e_खोलो - Called when a network पूर्णांकerface is made active
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0 on success, negative value on failure
 *
 * The खोलो entry poपूर्णांक is called when a network पूर्णांकerface is made
 * active by the प्रणाली (IFF_UP).  At this poपूर्णांक all resources needed
 * क्रम transmit and receive operations are allocated, the पूर्णांकerrupt
 * handler is रेजिस्टरed with the OS, the watchकरोg समयr is started,
 * and the stack is notअगरied that the पूर्णांकerface is पढ़ोy.
 **/
पूर्णांक e1000e_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक err;

	/* disallow खोलो during test */
	अगर (test_bit(__E1000_TESTING, &adapter->state))
		वापस -EBUSY;

	pm_runसमय_get_sync(&pdev->dev);

	netअगर_carrier_off(netdev);
	netअगर_stop_queue(netdev);

	/* allocate transmit descriptors */
	err = e1000e_setup_tx_resources(adapter->tx_ring);
	अगर (err)
		जाओ err_setup_tx;

	/* allocate receive descriptors */
	err = e1000e_setup_rx_resources(adapter->rx_ring);
	अगर (err)
		जाओ err_setup_rx;

	/* If AMT is enabled, let the firmware know that the network
	 * पूर्णांकerface is now खोलो and reset the part to a known state.
	 */
	अगर (adapter->flags & FLAG_HAS_AMT) अणु
		e1000e_get_hw_control(adapter);
		e1000e_reset(adapter);
	पूर्ण

	e1000e_घातer_up_phy(adapter);

	adapter->mng_vlan_id = E1000_MNG_VLAN_NONE;
	अगर ((adapter->hw.mng_cookie.status & E1000_MNG_DHCP_COOKIE_STATUS_VLAN))
		e1000_update_mng_vlan(adapter);

	/* DMA latency requirement to workaround jumbo issue */
	cpu_latency_qos_add_request(&adapter->pm_qos_req, PM_QOS_DEFAULT_VALUE);

	/* beक्रमe we allocate an पूर्णांकerrupt, we must be पढ़ोy to handle it.
	 * Setting DEBUG_SHIRQ in the kernel makes it fire an पूर्णांकerrupt
	 * as soon as we call pci_request_irq, so we have to setup our
	 * clean_rx handler beक्रमe we करो so.
	 */
	e1000_configure(adapter);

	err = e1000_request_irq(adapter);
	अगर (err)
		जाओ err_req_irq;

	/* Work around PCIe errata with MSI पूर्णांकerrupts causing some chipsets to
	 * ignore e1000e MSI messages, which means we need to test our MSI
	 * पूर्णांकerrupt now
	 */
	अगर (adapter->पूर्णांक_mode != E1000E_INT_MODE_LEGACY) अणु
		err = e1000_test_msi(adapter);
		अगर (err) अणु
			e_err("Interrupt allocation failed\n");
			जाओ err_req_irq;
		पूर्ण
	पूर्ण

	/* From here on the code is the same as e1000e_up() */
	clear_bit(__E1000_DOWN, &adapter->state);

	napi_enable(&adapter->napi);

	e1000_irq_enable(adapter);

	adapter->tx_hang_recheck = false;

	hw->mac.get_link_status = true;
	pm_runसमय_put(&pdev->dev);

	e1000e_trigger_lsc(adapter);

	वापस 0;

err_req_irq:
	cpu_latency_qos_हटाओ_request(&adapter->pm_qos_req);
	e1000e_release_hw_control(adapter);
	e1000_घातer_करोwn_phy(adapter);
	e1000e_मुक्त_rx_resources(adapter->rx_ring);
err_setup_rx:
	e1000e_मुक्त_tx_resources(adapter->tx_ring);
err_setup_tx:
	e1000e_reset(adapter);
	pm_runसमय_put_sync(&pdev->dev);

	वापस err;
पूर्ण

/**
 * e1000e_बंद - Disables a network पूर्णांकerface
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns 0, this is not allowed to fail
 *
 * The बंद entry poपूर्णांक is called when an पूर्णांकerface is de-activated
 * by the OS.  The hardware is still under the drivers control, but
 * needs to be disabled.  A global MAC reset is issued to stop the
 * hardware, and all transmit and receive resources are मुक्तd.
 **/
पूर्णांक e1000e_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक count = E1000_CHECK_RESET_COUNT;

	जबतक (test_bit(__E1000_RESETTING, &adapter->state) && count--)
		usleep_range(10000, 11000);

	WARN_ON(test_bit(__E1000_RESETTING, &adapter->state));

	pm_runसमय_get_sync(&pdev->dev);

	अगर (netअगर_device_present(netdev)) अणु
		e1000e_करोwn(adapter, true);
		e1000_मुक्त_irq(adapter);

		/* Link status message must follow this क्रमmat */
		netdev_info(netdev, "NIC Link is Down\n");
	पूर्ण

	napi_disable(&adapter->napi);

	e1000e_मुक्त_tx_resources(adapter->tx_ring);
	e1000e_मुक्त_rx_resources(adapter->rx_ring);

	/* समाप्त manageability vlan ID अगर supported, but not अगर a vlan with
	 * the same ID is रेजिस्टरed on the host OS (let 8021q समाप्त it)
	 */
	अगर (adapter->hw.mng_cookie.status & E1000_MNG_DHCP_COOKIE_STATUS_VLAN)
		e1000_vlan_rx_समाप्त_vid(netdev, htons(ETH_P_8021Q),
				       adapter->mng_vlan_id);

	/* If AMT is enabled, let the firmware know that the network
	 * पूर्णांकerface is now बंदd
	 */
	अगर ((adapter->flags & FLAG_HAS_AMT) &&
	    !test_bit(__E1000_TESTING, &adapter->state))
		e1000e_release_hw_control(adapter);

	cpu_latency_qos_हटाओ_request(&adapter->pm_qos_req);

	pm_runसमय_put_sync(&pdev->dev);

	वापस 0;
पूर्ण

/**
 * e1000_set_mac - Change the Ethernet Address of the NIC
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @p: poपूर्णांकer to an address काष्ठाure
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक e1000_set_mac(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
	स_नकल(adapter->hw.mac.addr, addr->sa_data, netdev->addr_len);

	hw->mac.ops.rar_set(&adapter->hw, adapter->hw.mac.addr, 0);

	अगर (adapter->flags & FLAG_RESET_OVERWRITES_LAA) अणु
		/* activate the work around */
		e1000e_set_laa_state_82571(&adapter->hw, 1);

		/* Hold a copy of the LAA in RAR[14] This is करोne so that
		 * between the समय RAR[0] माला_लो clobbered  and the समय it
		 * माला_लो fixed (in e1000_watchकरोg), the actual LAA is in one
		 * of the RARs and no incoming packets directed to this port
		 * are dropped. Eventually the LAA will be in RAR[0] and
		 * RAR[14]
		 */
		hw->mac.ops.rar_set(&adapter->hw, adapter->hw.mac.addr,
				    adapter->hw.mac.rar_entry_count - 1);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * e1000e_update_phy_task - work thपढ़ो to update phy
 * @work: poपूर्णांकer to our work काष्ठा
 *
 * this worker thपढ़ो exists because we must acquire a
 * semaphore to पढ़ो the phy, which we could msleep जबतक
 * रुकोing क्रम it, and we can't msleep in a समयr.
 **/
अटल व्योम e1000e_update_phy_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा e1000_adapter *adapter = container_of(work,
						     काष्ठा e1000_adapter,
						     update_phy_task);
	काष्ठा e1000_hw *hw = &adapter->hw;

	अगर (test_bit(__E1000_DOWN, &adapter->state))
		वापस;

	e1000_get_phy_info(hw);

	/* Enable EEE on 82579 after link up */
	अगर (hw->phy.type >= e1000_phy_82579)
		e1000_set_eee_pchlan(hw);
पूर्ण

/**
 * e1000_update_phy_info - timre call-back to update PHY info
 * @t: poपूर्णांकer to समयr_list containing निजी info adapter
 *
 * Need to रुको a few seconds after link up to get diagnostic inक्रमmation from
 * the phy
 **/
अटल व्योम e1000_update_phy_info(काष्ठा समयr_list *t)
अणु
	काष्ठा e1000_adapter *adapter = from_समयr(adapter, t, phy_info_समयr);

	अगर (test_bit(__E1000_DOWN, &adapter->state))
		वापस;

	schedule_work(&adapter->update_phy_task);
पूर्ण

/**
 * e1000e_update_phy_stats - Update the PHY statistics counters
 * @adapter: board निजी काष्ठाure
 *
 * Read/clear the upper 16-bit PHY रेजिस्टरs and पढ़ो/accumulate lower
 **/
अटल व्योम e1000e_update_phy_stats(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	s32 ret_val;
	u16 phy_data;

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		वापस;

	/* A page set is expensive so check अगर alपढ़ोy on desired page.
	 * If not, set to the page with the PHY status रेजिस्टरs.
	 */
	hw->phy.addr = 1;
	ret_val = e1000e_पढ़ो_phy_reg_mdic(hw, IGP01E1000_PHY_PAGE_SELECT,
					   &phy_data);
	अगर (ret_val)
		जाओ release;
	अगर (phy_data != (HV_STATS_PAGE << IGP_PAGE_SHIFT)) अणु
		ret_val = hw->phy.ops.set_page(hw,
					       HV_STATS_PAGE << IGP_PAGE_SHIFT);
		अगर (ret_val)
			जाओ release;
	पूर्ण

	/* Single Collision Count */
	hw->phy.ops.पढ़ो_reg_page(hw, HV_SCC_UPPER, &phy_data);
	ret_val = hw->phy.ops.पढ़ो_reg_page(hw, HV_SCC_LOWER, &phy_data);
	अगर (!ret_val)
		adapter->stats.scc += phy_data;

	/* Excessive Collision Count */
	hw->phy.ops.पढ़ो_reg_page(hw, HV_ECOL_UPPER, &phy_data);
	ret_val = hw->phy.ops.पढ़ो_reg_page(hw, HV_ECOL_LOWER, &phy_data);
	अगर (!ret_val)
		adapter->stats.ecol += phy_data;

	/* Multiple Collision Count */
	hw->phy.ops.पढ़ो_reg_page(hw, HV_MCC_UPPER, &phy_data);
	ret_val = hw->phy.ops.पढ़ो_reg_page(hw, HV_MCC_LOWER, &phy_data);
	अगर (!ret_val)
		adapter->stats.mcc += phy_data;

	/* Late Collision Count */
	hw->phy.ops.पढ़ो_reg_page(hw, HV_LATECOL_UPPER, &phy_data);
	ret_val = hw->phy.ops.पढ़ो_reg_page(hw, HV_LATECOL_LOWER, &phy_data);
	अगर (!ret_val)
		adapter->stats.latecol += phy_data;

	/* Collision Count - also used क्रम adaptive IFS */
	hw->phy.ops.पढ़ो_reg_page(hw, HV_COLC_UPPER, &phy_data);
	ret_val = hw->phy.ops.पढ़ो_reg_page(hw, HV_COLC_LOWER, &phy_data);
	अगर (!ret_val)
		hw->mac.collision_delta = phy_data;

	/* Defer Count */
	hw->phy.ops.पढ़ो_reg_page(hw, HV_DC_UPPER, &phy_data);
	ret_val = hw->phy.ops.पढ़ो_reg_page(hw, HV_DC_LOWER, &phy_data);
	अगर (!ret_val)
		adapter->stats.dc += phy_data;

	/* Transmit with no CRS */
	hw->phy.ops.पढ़ो_reg_page(hw, HV_TNCRS_UPPER, &phy_data);
	ret_val = hw->phy.ops.पढ़ो_reg_page(hw, HV_TNCRS_LOWER, &phy_data);
	अगर (!ret_val)
		adapter->stats.tncrs += phy_data;

release:
	hw->phy.ops.release(hw);
पूर्ण

/**
 * e1000e_update_stats - Update the board statistics counters
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम e1000e_update_stats(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा pci_dev *pdev = adapter->pdev;

	/* Prevent stats update जबतक adapter is being reset, or अगर the pci
	 * connection is करोwn.
	 */
	अगर (adapter->link_speed == 0)
		वापस;
	अगर (pci_channel_offline(pdev))
		वापस;

	adapter->stats.crcerrs += er32(CRCERRS);
	adapter->stats.gprc += er32(GPRC);
	adapter->stats.gorc += er32(GORCL);
	er32(GORCH);		/* Clear gorc */
	adapter->stats.bprc += er32(BPRC);
	adapter->stats.mprc += er32(MPRC);
	adapter->stats.roc += er32(ROC);

	adapter->stats.mpc += er32(MPC);

	/* Half-duplex statistics */
	अगर (adapter->link_duplex == HALF_DUPLEX) अणु
		अगर (adapter->flags2 & FLAG2_HAS_PHY_STATS) अणु
			e1000e_update_phy_stats(adapter);
		पूर्ण अन्यथा अणु
			adapter->stats.scc += er32(SCC);
			adapter->stats.ecol += er32(ECOL);
			adapter->stats.mcc += er32(MCC);
			adapter->stats.latecol += er32(LATECOL);
			adapter->stats.dc += er32(DC);

			hw->mac.collision_delta = er32(COLC);

			अगर ((hw->mac.type != e1000_82574) &&
			    (hw->mac.type != e1000_82583))
				adapter->stats.tncrs += er32(TNCRS);
		पूर्ण
		adapter->stats.colc += hw->mac.collision_delta;
	पूर्ण

	adapter->stats.xonrxc += er32(XONRXC);
	adapter->stats.xontxc += er32(XONTXC);
	adapter->stats.xoffrxc += er32(XOFFRXC);
	adapter->stats.xofftxc += er32(XOFFTXC);
	adapter->stats.gptc += er32(GPTC);
	adapter->stats.gotc += er32(GOTCL);
	er32(GOTCH);		/* Clear gotc */
	adapter->stats.rnbc += er32(RNBC);
	adapter->stats.ruc += er32(RUC);

	adapter->stats.mptc += er32(MPTC);
	adapter->stats.bptc += er32(BPTC);

	/* used क्रम adaptive IFS */

	hw->mac.tx_packet_delta = er32(TPT);
	adapter->stats.tpt += hw->mac.tx_packet_delta;

	adapter->stats.algnerrc += er32(ALGNERRC);
	adapter->stats.rxerrc += er32(RXERRC);
	adapter->stats.cexterr += er32(CEXTERR);
	adapter->stats.tsctc += er32(TSCTC);
	adapter->stats.tsctfc += er32(TSCTFC);

	/* Fill out the OS statistics काष्ठाure */
	netdev->stats.multicast = adapter->stats.mprc;
	netdev->stats.collisions = adapter->stats.colc;

	/* Rx Errors */

	/* RLEC on some newer hardware can be incorrect so build
	 * our own version based on RUC and ROC
	 */
	netdev->stats.rx_errors = adapter->stats.rxerrc +
	    adapter->stats.crcerrs + adapter->stats.algnerrc +
	    adapter->stats.ruc + adapter->stats.roc + adapter->stats.cexterr;
	netdev->stats.rx_length_errors = adapter->stats.ruc +
	    adapter->stats.roc;
	netdev->stats.rx_crc_errors = adapter->stats.crcerrs;
	netdev->stats.rx_frame_errors = adapter->stats.algnerrc;
	netdev->stats.rx_missed_errors = adapter->stats.mpc;

	/* Tx Errors */
	netdev->stats.tx_errors = adapter->stats.ecol + adapter->stats.latecol;
	netdev->stats.tx_पातed_errors = adapter->stats.ecol;
	netdev->stats.tx_winकरोw_errors = adapter->stats.latecol;
	netdev->stats.tx_carrier_errors = adapter->stats.tncrs;

	/* Tx Dropped needs to be मुख्यtained अन्यथाwhere */

	/* Management Stats */
	adapter->stats.mgptc += er32(MGTPTC);
	adapter->stats.mgprc += er32(MGTPRC);
	adapter->stats.mgpdc += er32(MGTPDC);

	/* Correctable ECC Errors */
	अगर (hw->mac.type >= e1000_pch_lpt) अणु
		u32 pbeccsts = er32(PBECCSTS);

		adapter->corr_errors +=
		    pbeccsts & E1000_PBECCSTS_CORR_ERR_CNT_MASK;
		adapter->uncorr_errors +=
		    (pbeccsts & E1000_PBECCSTS_UNCORR_ERR_CNT_MASK) >>
		    E1000_PBECCSTS_UNCORR_ERR_CNT_SHIFT;
	पूर्ण
पूर्ण

/**
 * e1000_phy_पढ़ो_status - Update the PHY रेजिस्टर status snapshot
 * @adapter: board निजी काष्ठाure
 **/
अटल व्योम e1000_phy_पढ़ो_status(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा e1000_phy_regs *phy = &adapter->phy_regs;

	अगर (!pm_runसमय_suspended((&adapter->pdev->dev)->parent) &&
	    (er32(STATUS) & E1000_STATUS_LU) &&
	    (adapter->hw.phy.media_type == e1000_media_type_copper)) अणु
		पूर्णांक ret_val;

		ret_val = e1e_rphy(hw, MII_BMCR, &phy->bmcr);
		ret_val |= e1e_rphy(hw, MII_BMSR, &phy->bmsr);
		ret_val |= e1e_rphy(hw, MII_ADVERTISE, &phy->advertise);
		ret_val |= e1e_rphy(hw, MII_LPA, &phy->lpa);
		ret_val |= e1e_rphy(hw, MII_EXPANSION, &phy->expansion);
		ret_val |= e1e_rphy(hw, MII_CTRL1000, &phy->ctrl1000);
		ret_val |= e1e_rphy(hw, MII_STAT1000, &phy->stat1000);
		ret_val |= e1e_rphy(hw, MII_ESTATUS, &phy->estatus);
		अगर (ret_val)
			e_warn("Error reading PHY register\n");
	पूर्ण अन्यथा अणु
		/* Do not पढ़ो PHY रेजिस्टरs अगर link is not up
		 * Set values to typical घातer-on शेषs
		 */
		phy->bmcr = (BMCR_SPEED1000 | BMCR_ANENABLE | BMCR_FULLDPLX);
		phy->bmsr = (BMSR_100FULL | BMSR_100HALF | BMSR_10FULL |
			     BMSR_10HALF | BMSR_ESTATEN | BMSR_ANEGCAPABLE |
			     BMSR_ERCAP);
		phy->advertise = (ADVERTISE_PAUSE_ASYM | ADVERTISE_PAUSE_CAP |
				  ADVERTISE_ALL | ADVERTISE_CSMA);
		phy->lpa = 0;
		phy->expansion = EXPANSION_ENABLENPAGE;
		phy->ctrl1000 = ADVERTISE_1000FULL;
		phy->stat1000 = 0;
		phy->estatus = (ESTATUS_1000_TFULL | ESTATUS_1000_THALF);
	पूर्ण
पूर्ण

अटल व्योम e1000_prपूर्णांक_link_info(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl = er32(CTRL);

	/* Link status message must follow this क्रमmat क्रम user tools */
	netdev_info(adapter->netdev,
		    "NIC Link is Up %d Mbps %s Duplex, Flow Control: %s\n",
		    adapter->link_speed,
		    adapter->link_duplex == FULL_DUPLEX ? "Full" : "Half",
		    (ctrl & E1000_CTRL_TFCE) && (ctrl & E1000_CTRL_RFCE) ? "Rx/Tx" :
		    (ctrl & E1000_CTRL_RFCE) ? "Rx" :
		    (ctrl & E1000_CTRL_TFCE) ? "Tx" : "None");
पूर्ण

अटल bool e1000e_has_link(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	bool link_active = false;
	s32 ret_val = 0;

	/* get_link_status is set on LSC (link status) पूर्णांकerrupt or
	 * Rx sequence error पूर्णांकerrupt.  get_link_status will stay
	 * true until the check_क्रम_link establishes link
	 * क्रम copper adapters ONLY
	 */
	चयन (hw->phy.media_type) अणु
	हाल e1000_media_type_copper:
		अगर (hw->mac.get_link_status) अणु
			ret_val = hw->mac.ops.check_क्रम_link(hw);
			link_active = !hw->mac.get_link_status;
		पूर्ण अन्यथा अणु
			link_active = true;
		पूर्ण
		अवरोध;
	हाल e1000_media_type_fiber:
		ret_val = hw->mac.ops.check_क्रम_link(hw);
		link_active = !!(er32(STATUS) & E1000_STATUS_LU);
		अवरोध;
	हाल e1000_media_type_पूर्णांकernal_serdes:
		ret_val = hw->mac.ops.check_क्रम_link(hw);
		link_active = hw->mac.serdes_has_link;
		अवरोध;
	शेष:
	हाल e1000_media_type_unknown:
		अवरोध;
	पूर्ण

	अगर ((ret_val == -E1000_ERR_PHY) && (hw->phy.type == e1000_phy_igp_3) &&
	    (er32(CTRL) & E1000_PHY_CTRL_GBE_DISABLE)) अणु
		/* See e1000_kmrn_lock_loss_workaround_ich8lan() */
		e_info("Gigabit has been disabled, downgrading speed\n");
	पूर्ण

	वापस link_active;
पूर्ण

अटल व्योम e1000e_enable_receives(काष्ठा e1000_adapter *adapter)
अणु
	/* make sure the receive unit is started */
	अगर ((adapter->flags & FLAG_RX_NEEDS_RESTART) &&
	    (adapter->flags & FLAG_RESTART_NOW)) अणु
		काष्ठा e1000_hw *hw = &adapter->hw;
		u32 rctl = er32(RCTL);

		ew32(RCTL, rctl | E1000_RCTL_EN);
		adapter->flags &= ~FLAG_RESTART_NOW;
	पूर्ण
पूर्ण

अटल व्योम e1000e_check_82574_phy_workaround(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* With 82574 controllers, PHY needs to be checked periodically
	 * क्रम hung state and reset, अगर two calls वापस true
	 */
	अगर (e1000_check_phy_82574(hw))
		adapter->phy_hang_count++;
	अन्यथा
		adapter->phy_hang_count = 0;

	अगर (adapter->phy_hang_count > 1) अणु
		adapter->phy_hang_count = 0;
		e_dbg("PHY appears hung - resetting\n");
		schedule_work(&adapter->reset_task);
	पूर्ण
पूर्ण

/**
 * e1000_watchकरोg - Timer Call-back
 * @t: poपूर्णांकer to समयr_list containing निजी info adapter
 **/
अटल व्योम e1000_watchकरोg(काष्ठा समयr_list *t)
अणु
	काष्ठा e1000_adapter *adapter = from_समयr(adapter, t, watchकरोg_समयr);

	/* Do the rest outside of पूर्णांकerrupt context */
	schedule_work(&adapter->watchकरोg_task);

	/* TODO: make this use queue_delayed_work() */
पूर्ण

अटल व्योम e1000_watchकरोg_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा e1000_adapter *adapter = container_of(work,
						     काष्ठा e1000_adapter,
						     watchकरोg_task);
	काष्ठा net_device *netdev = adapter->netdev;
	काष्ठा e1000_mac_info *mac = &adapter->hw.mac;
	काष्ठा e1000_phy_info *phy = &adapter->hw.phy;
	काष्ठा e1000_ring *tx_ring = adapter->tx_ring;
	u32 dmoff_निकास_समयout = 100, tries = 0;
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 link, tctl, pcim_state;

	अगर (test_bit(__E1000_DOWN, &adapter->state))
		वापस;

	link = e1000e_has_link(adapter);
	अगर ((netअगर_carrier_ok(netdev)) && link) अणु
		/* Cancel scheduled suspend requests. */
		pm_runसमय_resume(netdev->dev.parent);

		e1000e_enable_receives(adapter);
		जाओ link_up;
	पूर्ण

	अगर ((e1000e_enable_tx_pkt_filtering(hw)) &&
	    (adapter->mng_vlan_id != adapter->hw.mng_cookie.vlan_id))
		e1000_update_mng_vlan(adapter);

	अगर (link) अणु
		अगर (!netअगर_carrier_ok(netdev)) अणु
			bool txb2b = true;

			/* Cancel scheduled suspend requests. */
			pm_runसमय_resume(netdev->dev.parent);

			/* Checking अगर MAC is in DMoff state*/
			pcim_state = er32(STATUS);
			जबतक (pcim_state & E1000_STATUS_PCIM_STATE) अणु
				अगर (tries++ == dmoff_निकास_समयout) अणु
					e_dbg("Error in exiting dmoff\n");
					अवरोध;
				पूर्ण
				usleep_range(10000, 20000);
				pcim_state = er32(STATUS);

				/* Checking अगर MAC निकासed DMoff state */
				अगर (!(pcim_state & E1000_STATUS_PCIM_STATE))
					e1000_phy_hw_reset(&adapter->hw);
			पूर्ण

			/* update snapshot of PHY रेजिस्टरs on LSC */
			e1000_phy_पढ़ो_status(adapter);
			mac->ops.get_link_up_info(&adapter->hw,
						  &adapter->link_speed,
						  &adapter->link_duplex);
			e1000_prपूर्णांक_link_info(adapter);

			/* check अगर SmartSpeed worked */
			e1000e_check_करोwnshअगरt(hw);
			अगर (phy->speed_करोwngraded)
				netdev_warn(netdev,
					    "Link Speed was downgraded by SmartSpeed\n");

			/* On supported PHYs, check क्रम duplex mismatch only
			 * अगर link has स्वतःnegotiated at 10/100 half
			 */
			अगर ((hw->phy.type == e1000_phy_igp_3 ||
			     hw->phy.type == e1000_phy_bm) &&
			    hw->mac.स्वतःneg &&
			    (adapter->link_speed == SPEED_10 ||
			     adapter->link_speed == SPEED_100) &&
			    (adapter->link_duplex == HALF_DUPLEX)) अणु
				u16 स्वतःneg_exp;

				e1e_rphy(hw, MII_EXPANSION, &स्वतःneg_exp);

				अगर (!(स्वतःneg_exp & EXPANSION_NWAY))
					e_info("Autonegotiated half duplex but link partner cannot autoneg.  Try forcing full duplex if link gets many collisions.\n");
			पूर्ण

			/* adjust समयout factor according to speed/duplex */
			adapter->tx_समयout_factor = 1;
			चयन (adapter->link_speed) अणु
			हाल SPEED_10:
				txb2b = false;
				adapter->tx_समयout_factor = 16;
				अवरोध;
			हाल SPEED_100:
				txb2b = false;
				adapter->tx_समयout_factor = 10;
				अवरोध;
			पूर्ण

			/* workaround: re-program speed mode bit after
			 * link-up event
			 */
			अगर ((adapter->flags & FLAG_TARC_SPEED_MODE_BIT) &&
			    !txb2b) अणु
				u32 tarc0;

				tarc0 = er32(TARC(0));
				tarc0 &= ~SPEED_MODE_BIT;
				ew32(TARC(0), tarc0);
			पूर्ण

			/* disable TSO क्रम pcie and 10/100 speeds, to aव्योम
			 * some hardware issues
			 */
			अगर (!(adapter->flags & FLAG_TSO_FORCE)) अणु
				चयन (adapter->link_speed) अणु
				हाल SPEED_10:
				हाल SPEED_100:
					e_info("10/100 speed: disabling TSO\n");
					netdev->features &= ~NETIF_F_TSO;
					netdev->features &= ~NETIF_F_TSO6;
					अवरोध;
				हाल SPEED_1000:
					netdev->features |= NETIF_F_TSO;
					netdev->features |= NETIF_F_TSO6;
					अवरोध;
				शेष:
					/* oops */
					अवरोध;
				पूर्ण
				अगर (hw->mac.type == e1000_pch_spt) अणु
					netdev->features &= ~NETIF_F_TSO;
					netdev->features &= ~NETIF_F_TSO6;
				पूर्ण
			पूर्ण

			/* enable transmits in the hardware, need to करो this
			 * after setting TARC(0)
			 */
			tctl = er32(TCTL);
			tctl |= E1000_TCTL_EN;
			ew32(TCTL, tctl);

			/* Perक्रमm any post-link-up configuration beक्रमe
			 * reporting link up.
			 */
			अगर (phy->ops.cfg_on_link_up)
				phy->ops.cfg_on_link_up(hw);

			netअगर_wake_queue(netdev);
			netअगर_carrier_on(netdev);

			अगर (!test_bit(__E1000_DOWN, &adapter->state))
				mod_समयr(&adapter->phy_info_समयr,
					  round_jअगरfies(jअगरfies + 2 * HZ));
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(netdev)) अणु
			adapter->link_speed = 0;
			adapter->link_duplex = 0;
			/* Link status message must follow this क्रमmat */
			netdev_info(netdev, "NIC Link is Down\n");
			netअगर_carrier_off(netdev);
			netअगर_stop_queue(netdev);
			अगर (!test_bit(__E1000_DOWN, &adapter->state))
				mod_समयr(&adapter->phy_info_समयr,
					  round_jअगरfies(jअगरfies + 2 * HZ));

			/* 8000ES2LAN requires a Rx packet buffer work-around
			 * on link करोwn event; reset the controller to flush
			 * the Rx packet buffer.
			 */
			अगर (adapter->flags & FLAG_RX_NEEDS_RESTART)
				adapter->flags |= FLAG_RESTART_NOW;
			अन्यथा
				pm_schedule_suspend(netdev->dev.parent,
						    LINK_TIMEOUT);
		पूर्ण
	पूर्ण

link_up:
	spin_lock(&adapter->stats64_lock);
	e1000e_update_stats(adapter);

	mac->tx_packet_delta = adapter->stats.tpt - adapter->tpt_old;
	adapter->tpt_old = adapter->stats.tpt;
	mac->collision_delta = adapter->stats.colc - adapter->colc_old;
	adapter->colc_old = adapter->stats.colc;

	adapter->gorc = adapter->stats.gorc - adapter->gorc_old;
	adapter->gorc_old = adapter->stats.gorc;
	adapter->gotc = adapter->stats.gotc - adapter->gotc_old;
	adapter->gotc_old = adapter->stats.gotc;
	spin_unlock(&adapter->stats64_lock);

	/* If the link is lost the controller stops DMA, but
	 * अगर there is queued Tx work it cannot be करोne.  So
	 * reset the controller to flush the Tx packet buffers.
	 */
	अगर (!netअगर_carrier_ok(netdev) &&
	    (e1000_desc_unused(tx_ring) + 1 < tx_ring->count))
		adapter->flags |= FLAG_RESTART_NOW;

	/* If reset is necessary, करो it outside of पूर्णांकerrupt context. */
	अगर (adapter->flags & FLAG_RESTART_NOW) अणु
		schedule_work(&adapter->reset_task);
		/* वापस immediately since reset is imminent */
		वापस;
	पूर्ण

	e1000e_update_adaptive(&adapter->hw);

	/* Simple mode क्रम Interrupt Throttle Rate (ITR) */
	अगर (adapter->itr_setting == 4) अणु
		/* Symmetric Tx/Rx माला_लो a reduced ITR=2000;
		 * Total asymmetrical Tx or Rx माला_लो ITR=8000;
		 * everyone अन्यथा is between 2000-8000.
		 */
		u32 goc = (adapter->gotc + adapter->gorc) / 10000;
		u32 dअगर = (adapter->gotc > adapter->gorc ?
			   adapter->gotc - adapter->gorc :
			   adapter->gorc - adapter->gotc) / 10000;
		u32 itr = goc > 0 ? (dअगर * 6000 / goc + 2000) : 8000;

		e1000e_ग_लिखो_itr(adapter, itr);
	पूर्ण

	/* Cause software पूर्णांकerrupt to ensure Rx ring is cleaned */
	अगर (adapter->msix_entries)
		ew32(ICS, adapter->rx_ring->ims_val);
	अन्यथा
		ew32(ICS, E1000_ICS_RXDMT0);

	/* flush pending descriptors to memory beक्रमe detecting Tx hang */
	e1000e_flush_descriptors(adapter);

	/* Force detection of hung controller every watchकरोg period */
	adapter->detect_tx_hung = true;

	/* With 82571 controllers, LAA may be overwritten due to controller
	 * reset from the other port. Set the appropriate LAA in RAR[0]
	 */
	अगर (e1000e_get_laa_state_82571(hw))
		hw->mac.ops.rar_set(hw, adapter->hw.mac.addr, 0);

	अगर (adapter->flags2 & FLAG2_CHECK_PHY_HANG)
		e1000e_check_82574_phy_workaround(adapter);

	/* Clear valid बारtamp stuck in RXSTMPL/H due to a Rx error */
	अगर (adapter->hwtstamp_config.rx_filter != HWTSTAMP_FILTER_NONE) अणु
		अगर ((adapter->flags2 & FLAG2_CHECK_RX_HWTSTAMP) &&
		    (er32(TSYNCRXCTL) & E1000_TSYNCRXCTL_VALID)) अणु
			er32(RXSTMPH);
			adapter->rx_hwtstamp_cleared++;
		पूर्ण अन्यथा अणु
			adapter->flags2 |= FLAG2_CHECK_RX_HWTSTAMP;
		पूर्ण
	पूर्ण

	/* Reset the समयr */
	अगर (!test_bit(__E1000_DOWN, &adapter->state))
		mod_समयr(&adapter->watchकरोg_समयr,
			  round_jअगरfies(jअगरfies + 2 * HZ));
पूर्ण

#घोषणा E1000_TX_FLAGS_CSUM		0x00000001
#घोषणा E1000_TX_FLAGS_VLAN		0x00000002
#घोषणा E1000_TX_FLAGS_TSO		0x00000004
#घोषणा E1000_TX_FLAGS_IPV4		0x00000008
#घोषणा E1000_TX_FLAGS_NO_FCS		0x00000010
#घोषणा E1000_TX_FLAGS_HWTSTAMP		0x00000020
#घोषणा E1000_TX_FLAGS_VLAN_MASK	0xffff0000
#घोषणा E1000_TX_FLAGS_VLAN_SHIFT	16

अटल पूर्णांक e1000_tso(काष्ठा e1000_ring *tx_ring, काष्ठा sk_buff *skb,
		     __be16 protocol)
अणु
	काष्ठा e1000_context_desc *context_desc;
	काष्ठा e1000_buffer *buffer_info;
	अचिन्हित पूर्णांक i;
	u32 cmd_length = 0;
	u16 ipcse = 0, mss;
	u8 ipcss, ipcso, tucss, tucso, hdr_len;
	पूर्णांक err;

	अगर (!skb_is_gso(skb))
		वापस 0;

	err = skb_cow_head(skb, 0);
	अगर (err < 0)
		वापस err;

	hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
	mss = skb_shinfo(skb)->gso_size;
	अगर (protocol == htons(ETH_P_IP)) अणु
		काष्ठा iphdr *iph = ip_hdr(skb);
		iph->tot_len = 0;
		iph->check = 0;
		tcp_hdr(skb)->check = ~csum_tcpudp_magic(iph->saddr, iph->daddr,
							 0, IPPROTO_TCP, 0);
		cmd_length = E1000_TXD_CMD_IP;
		ipcse = skb_transport_offset(skb) - 1;
	पूर्ण अन्यथा अगर (skb_is_gso_v6(skb)) अणु
		tcp_v6_gso_csum_prep(skb);
		ipcse = 0;
	पूर्ण
	ipcss = skb_network_offset(skb);
	ipcso = (व्योम *)&(ip_hdr(skb)->check) - (व्योम *)skb->data;
	tucss = skb_transport_offset(skb);
	tucso = (व्योम *)&(tcp_hdr(skb)->check) - (व्योम *)skb->data;

	cmd_length |= (E1000_TXD_CMD_DEXT | E1000_TXD_CMD_TSE |
		       E1000_TXD_CMD_TCP | (skb->len - (hdr_len)));

	i = tx_ring->next_to_use;
	context_desc = E1000_CONTEXT_DESC(*tx_ring, i);
	buffer_info = &tx_ring->buffer_info[i];

	context_desc->lower_setup.ip_fields.ipcss = ipcss;
	context_desc->lower_setup.ip_fields.ipcso = ipcso;
	context_desc->lower_setup.ip_fields.ipcse = cpu_to_le16(ipcse);
	context_desc->upper_setup.tcp_fields.tucss = tucss;
	context_desc->upper_setup.tcp_fields.tucso = tucso;
	context_desc->upper_setup.tcp_fields.tucse = 0;
	context_desc->tcp_seg_setup.fields.mss = cpu_to_le16(mss);
	context_desc->tcp_seg_setup.fields.hdr_len = hdr_len;
	context_desc->cmd_and_length = cpu_to_le32(cmd_length);

	buffer_info->समय_stamp = jअगरfies;
	buffer_info->next_to_watch = i;

	i++;
	अगर (i == tx_ring->count)
		i = 0;
	tx_ring->next_to_use = i;

	वापस 1;
पूर्ण

अटल bool e1000_tx_csum(काष्ठा e1000_ring *tx_ring, काष्ठा sk_buff *skb,
			  __be16 protocol)
अणु
	काष्ठा e1000_adapter *adapter = tx_ring->adapter;
	काष्ठा e1000_context_desc *context_desc;
	काष्ठा e1000_buffer *buffer_info;
	अचिन्हित पूर्णांक i;
	u8 css;
	u32 cmd_len = E1000_TXD_CMD_DEXT;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस false;

	चयन (protocol) अणु
	हाल cpu_to_be16(ETH_P_IP):
		अगर (ip_hdr(skb)->protocol == IPPROTO_TCP)
			cmd_len |= E1000_TXD_CMD_TCP;
		अवरोध;
	हाल cpu_to_be16(ETH_P_IPV6):
		/* XXX not handling all IPV6 headers */
		अगर (ipv6_hdr(skb)->nexthdr == IPPROTO_TCP)
			cmd_len |= E1000_TXD_CMD_TCP;
		अवरोध;
	शेष:
		अगर (unlikely(net_ratelimit()))
			e_warn("checksum_partial proto=%x!\n",
			       be16_to_cpu(protocol));
		अवरोध;
	पूर्ण

	css = skb_checksum_start_offset(skb);

	i = tx_ring->next_to_use;
	buffer_info = &tx_ring->buffer_info[i];
	context_desc = E1000_CONTEXT_DESC(*tx_ring, i);

	context_desc->lower_setup.ip_config = 0;
	context_desc->upper_setup.tcp_fields.tucss = css;
	context_desc->upper_setup.tcp_fields.tucso = css + skb->csum_offset;
	context_desc->upper_setup.tcp_fields.tucse = 0;
	context_desc->tcp_seg_setup.data = 0;
	context_desc->cmd_and_length = cpu_to_le32(cmd_len);

	buffer_info->समय_stamp = jअगरfies;
	buffer_info->next_to_watch = i;

	i++;
	अगर (i == tx_ring->count)
		i = 0;
	tx_ring->next_to_use = i;

	वापस true;
पूर्ण

अटल पूर्णांक e1000_tx_map(काष्ठा e1000_ring *tx_ring, काष्ठा sk_buff *skb,
			अचिन्हित पूर्णांक first, अचिन्हित पूर्णांक max_per_txd,
			अचिन्हित पूर्णांक nr_frags)
अणु
	काष्ठा e1000_adapter *adapter = tx_ring->adapter;
	काष्ठा pci_dev *pdev = adapter->pdev;
	काष्ठा e1000_buffer *buffer_info;
	अचिन्हित पूर्णांक len = skb_headlen(skb);
	अचिन्हित पूर्णांक offset = 0, size, count = 0, i;
	अचिन्हित पूर्णांक f, bytecount, segs;

	i = tx_ring->next_to_use;

	जबतक (len) अणु
		buffer_info = &tx_ring->buffer_info[i];
		size = min(len, max_per_txd);

		buffer_info->length = size;
		buffer_info->समय_stamp = jअगरfies;
		buffer_info->next_to_watch = i;
		buffer_info->dma = dma_map_single(&pdev->dev,
						  skb->data + offset,
						  size, DMA_TO_DEVICE);
		buffer_info->mapped_as_page = false;
		अगर (dma_mapping_error(&pdev->dev, buffer_info->dma))
			जाओ dma_error;

		len -= size;
		offset += size;
		count++;

		अगर (len) अणु
			i++;
			अगर (i == tx_ring->count)
				i = 0;
		पूर्ण
	पूर्ण

	क्रम (f = 0; f < nr_frags; f++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[f];

		len = skb_frag_size(frag);
		offset = 0;

		जबतक (len) अणु
			i++;
			अगर (i == tx_ring->count)
				i = 0;

			buffer_info = &tx_ring->buffer_info[i];
			size = min(len, max_per_txd);

			buffer_info->length = size;
			buffer_info->समय_stamp = jअगरfies;
			buffer_info->next_to_watch = i;
			buffer_info->dma = skb_frag_dma_map(&pdev->dev, frag,
							    offset, size,
							    DMA_TO_DEVICE);
			buffer_info->mapped_as_page = true;
			अगर (dma_mapping_error(&pdev->dev, buffer_info->dma))
				जाओ dma_error;

			len -= size;
			offset += size;
			count++;
		पूर्ण
	पूर्ण

	segs = skb_shinfo(skb)->gso_segs ? : 1;
	/* multiply data chunks by size of headers */
	bytecount = ((segs - 1) * skb_headlen(skb)) + skb->len;

	tx_ring->buffer_info[i].skb = skb;
	tx_ring->buffer_info[i].segs = segs;
	tx_ring->buffer_info[i].bytecount = bytecount;
	tx_ring->buffer_info[first].next_to_watch = i;

	वापस count;

dma_error:
	dev_err(&pdev->dev, "Tx DMA map failed\n");
	buffer_info->dma = 0;
	अगर (count)
		count--;

	जबतक (count--) अणु
		अगर (i == 0)
			i += tx_ring->count;
		i--;
		buffer_info = &tx_ring->buffer_info[i];
		e1000_put_txbuf(tx_ring, buffer_info, true);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम e1000_tx_queue(काष्ठा e1000_ring *tx_ring, पूर्णांक tx_flags, पूर्णांक count)
अणु
	काष्ठा e1000_adapter *adapter = tx_ring->adapter;
	काष्ठा e1000_tx_desc *tx_desc = शून्य;
	काष्ठा e1000_buffer *buffer_info;
	u32 txd_upper = 0, txd_lower = E1000_TXD_CMD_IFCS;
	अचिन्हित पूर्णांक i;

	अगर (tx_flags & E1000_TX_FLAGS_TSO) अणु
		txd_lower |= E1000_TXD_CMD_DEXT | E1000_TXD_DTYP_D |
		    E1000_TXD_CMD_TSE;
		txd_upper |= E1000_TXD_POPTS_TXSM << 8;

		अगर (tx_flags & E1000_TX_FLAGS_IPV4)
			txd_upper |= E1000_TXD_POPTS_IXSM << 8;
	पूर्ण

	अगर (tx_flags & E1000_TX_FLAGS_CSUM) अणु
		txd_lower |= E1000_TXD_CMD_DEXT | E1000_TXD_DTYP_D;
		txd_upper |= E1000_TXD_POPTS_TXSM << 8;
	पूर्ण

	अगर (tx_flags & E1000_TX_FLAGS_VLAN) अणु
		txd_lower |= E1000_TXD_CMD_VLE;
		txd_upper |= (tx_flags & E1000_TX_FLAGS_VLAN_MASK);
	पूर्ण

	अगर (unlikely(tx_flags & E1000_TX_FLAGS_NO_FCS))
		txd_lower &= ~(E1000_TXD_CMD_IFCS);

	अगर (unlikely(tx_flags & E1000_TX_FLAGS_HWTSTAMP)) अणु
		txd_lower |= E1000_TXD_CMD_DEXT | E1000_TXD_DTYP_D;
		txd_upper |= E1000_TXD_EXTCMD_TSTAMP;
	पूर्ण

	i = tx_ring->next_to_use;

	करो अणु
		buffer_info = &tx_ring->buffer_info[i];
		tx_desc = E1000_TX_DESC(*tx_ring, i);
		tx_desc->buffer_addr = cpu_to_le64(buffer_info->dma);
		tx_desc->lower.data = cpu_to_le32(txd_lower |
						  buffer_info->length);
		tx_desc->upper.data = cpu_to_le32(txd_upper);

		i++;
		अगर (i == tx_ring->count)
			i = 0;
	पूर्ण जबतक (--count > 0);

	tx_desc->lower.data |= cpu_to_le32(adapter->txd_cmd);

	/* txd_cmd re-enables FCS, so we'll re-disable it here as desired. */
	अगर (unlikely(tx_flags & E1000_TX_FLAGS_NO_FCS))
		tx_desc->lower.data &= ~(cpu_to_le32(E1000_TXD_CMD_IFCS));

	/* Force memory ग_लिखोs to complete beक्रमe letting h/w
	 * know there are new descriptors to fetch.  (Only
	 * applicable क्रम weak-ordered memory model archs,
	 * such as IA-64).
	 */
	wmb();

	tx_ring->next_to_use = i;
पूर्ण

#घोषणा MINIMUM_DHCP_PACKET_SIZE 282
अटल पूर्णांक e1000_transfer_dhcp_info(काष्ठा e1000_adapter *adapter,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 length, offset;

	अगर (skb_vlan_tag_present(skb) &&
	    !((skb_vlan_tag_get(skb) == adapter->hw.mng_cookie.vlan_id) &&
	      (adapter->hw.mng_cookie.status &
	       E1000_MNG_DHCP_COOKIE_STATUS_VLAN)))
		वापस 0;

	अगर (skb->len <= MINIMUM_DHCP_PACKET_SIZE)
		वापस 0;

	अगर (((काष्ठा ethhdr *)skb->data)->h_proto != htons(ETH_P_IP))
		वापस 0;

	अणु
		स्थिर काष्ठा iphdr *ip = (काष्ठा iphdr *)((u8 *)skb->data + 14);
		काष्ठा udphdr *udp;

		अगर (ip->protocol != IPPROTO_UDP)
			वापस 0;

		udp = (काष्ठा udphdr *)((u8 *)ip + (ip->ihl << 2));
		अगर (ntohs(udp->dest) != 67)
			वापस 0;

		offset = (u8 *)udp + 8 - skb->data;
		length = skb->len - offset;
		वापस e1000e_mng_ग_लिखो_dhcp_info(hw, (u8 *)udp + 8, length);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __e1000_maybe_stop_tx(काष्ठा e1000_ring *tx_ring, पूर्णांक size)
अणु
	काष्ठा e1000_adapter *adapter = tx_ring->adapter;

	netअगर_stop_queue(adapter->netdev);
	/* Herbert's original patch had:
	 *  smp_mb__after_netअगर_stop_queue();
	 * but since that करोesn't exist yet, just खोलो code it.
	 */
	smp_mb();

	/* We need to check again in a हाल another CPU has just
	 * made room available.
	 */
	अगर (e1000_desc_unused(tx_ring) < size)
		वापस -EBUSY;

	/* A reprieve! */
	netअगर_start_queue(adapter->netdev);
	++adapter->restart_queue;
	वापस 0;
पूर्ण

अटल पूर्णांक e1000_maybe_stop_tx(काष्ठा e1000_ring *tx_ring, पूर्णांक size)
अणु
	BUG_ON(size > tx_ring->count);

	अगर (e1000_desc_unused(tx_ring) >= size)
		वापस 0;
	वापस __e1000_maybe_stop_tx(tx_ring, size);
पूर्ण

अटल netdev_tx_t e1000_xmit_frame(काष्ठा sk_buff *skb,
				    काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_ring *tx_ring = adapter->tx_ring;
	अचिन्हित पूर्णांक first;
	अचिन्हित पूर्णांक tx_flags = 0;
	अचिन्हित पूर्णांक len = skb_headlen(skb);
	अचिन्हित पूर्णांक nr_frags;
	अचिन्हित पूर्णांक mss;
	पूर्णांक count = 0;
	पूर्णांक tso;
	अचिन्हित पूर्णांक f;
	__be16 protocol = vlan_get_protocol(skb);

	अगर (test_bit(__E1000_DOWN, &adapter->state)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (skb->len <= 0) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* The minimum packet size with TCTL.PSP set is 17 bytes so
	 * pad skb in order to meet this minimum size requirement
	 */
	अगर (skb_put_padto(skb, 17))
		वापस NETDEV_TX_OK;

	mss = skb_shinfo(skb)->gso_size;
	अगर (mss) अणु
		u8 hdr_len;

		/* TSO Workaround क्रम 82571/2/3 Controllers -- अगर skb->data
		 * poपूर्णांकs to just header, pull a few bytes of payload from
		 * frags पूर्णांकo skb->data
		 */
		hdr_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
		/* we करो this workaround क्रम ES2LAN, but it is un-necessary,
		 * aव्योमing it could save a lot of cycles
		 */
		अगर (skb->data_len && (hdr_len == len)) अणु
			अचिन्हित पूर्णांक pull_size;

			pull_size = min_t(अचिन्हित पूर्णांक, 4, skb->data_len);
			अगर (!__pskb_pull_tail(skb, pull_size)) अणु
				e_err("__pskb_pull_tail failed.\n");
				dev_kमुक्त_skb_any(skb);
				वापस NETDEV_TX_OK;
			पूर्ण
			len = skb_headlen(skb);
		पूर्ण
	पूर्ण

	/* reserve a descriptor क्रम the offload context */
	अगर ((mss) || (skb->ip_summed == CHECKSUM_PARTIAL))
		count++;
	count++;

	count += DIV_ROUND_UP(len, adapter->tx_fअगरo_limit);

	nr_frags = skb_shinfo(skb)->nr_frags;
	क्रम (f = 0; f < nr_frags; f++)
		count += DIV_ROUND_UP(skb_frag_size(&skb_shinfo(skb)->frags[f]),
				      adapter->tx_fअगरo_limit);

	अगर (adapter->hw.mac.tx_pkt_filtering)
		e1000_transfer_dhcp_info(adapter, skb);

	/* need: count + 2 desc gap to keep tail from touching
	 * head, otherwise try next समय
	 */
	अगर (e1000_maybe_stop_tx(tx_ring, count + 2))
		वापस NETDEV_TX_BUSY;

	अगर (skb_vlan_tag_present(skb)) अणु
		tx_flags |= E1000_TX_FLAGS_VLAN;
		tx_flags |= (skb_vlan_tag_get(skb) <<
			     E1000_TX_FLAGS_VLAN_SHIFT);
	पूर्ण

	first = tx_ring->next_to_use;

	tso = e1000_tso(tx_ring, skb, protocol);
	अगर (tso < 0) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (tso)
		tx_flags |= E1000_TX_FLAGS_TSO;
	अन्यथा अगर (e1000_tx_csum(tx_ring, skb, protocol))
		tx_flags |= E1000_TX_FLAGS_CSUM;

	/* Old method was to assume IPv4 packet by शेष अगर TSO was enabled.
	 * 82571 hardware supports TSO capabilities क्रम IPv6 as well...
	 * no दीर्घer assume, we must.
	 */
	अगर (protocol == htons(ETH_P_IP))
		tx_flags |= E1000_TX_FLAGS_IPV4;

	अगर (unlikely(skb->no_fcs))
		tx_flags |= E1000_TX_FLAGS_NO_FCS;

	/* अगर count is 0 then mapping error has occurred */
	count = e1000_tx_map(tx_ring, skb, first, adapter->tx_fअगरo_limit,
			     nr_frags);
	अगर (count) अणु
		अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP) &&
		    (adapter->flags & FLAG_HAS_HW_TIMESTAMP)) अणु
			अगर (!adapter->tx_hwtstamp_skb) अणु
				skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
				tx_flags |= E1000_TX_FLAGS_HWTSTAMP;
				adapter->tx_hwtstamp_skb = skb_get(skb);
				adapter->tx_hwtstamp_start = jअगरfies;
				schedule_work(&adapter->tx_hwtstamp_work);
			पूर्ण अन्यथा अणु
				adapter->tx_hwtstamp_skipped++;
			पूर्ण
		पूर्ण

		skb_tx_बारtamp(skb);

		netdev_sent_queue(netdev, skb->len);
		e1000_tx_queue(tx_ring, tx_flags, count);
		/* Make sure there is space in the ring क्रम the next send. */
		e1000_maybe_stop_tx(tx_ring,
				    (MAX_SKB_FRAGS *
				     DIV_ROUND_UP(PAGE_SIZE,
						  adapter->tx_fअगरo_limit) + 2));

		अगर (!netdev_xmit_more() ||
		    netअगर_xmit_stopped(netdev_get_tx_queue(netdev, 0))) अणु
			अगर (adapter->flags2 & FLAG2_PCIM2PCI_ARBITER_WA)
				e1000e_update_tdt_wa(tx_ring,
						     tx_ring->next_to_use);
			अन्यथा
				ग_लिखोl(tx_ring->next_to_use, tx_ring->tail);
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb_any(skb);
		tx_ring->buffer_info[first].समय_stamp = 0;
		tx_ring->next_to_use = first;
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

/**
 * e1000_tx_समयout - Respond to a Tx Hang
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @txqueue: index of the hung queue (unused)
 **/
अटल व्योम e1000_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक __always_unused txqueue)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	/* Do the reset outside of पूर्णांकerrupt context */
	adapter->tx_समयout_count++;
	schedule_work(&adapter->reset_task);
पूर्ण

अटल व्योम e1000_reset_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा e1000_adapter *adapter;
	adapter = container_of(work, काष्ठा e1000_adapter, reset_task);

	rtnl_lock();
	/* करोn't run the task अगर alपढ़ोy करोwn */
	अगर (test_bit(__E1000_DOWN, &adapter->state)) अणु
		rtnl_unlock();
		वापस;
	पूर्ण

	अगर (!(adapter->flags & FLAG_RESTART_NOW)) अणु
		e1000e_dump(adapter);
		e_err("Reset adapter unexpectedly\n");
	पूर्ण
	e1000e_reinit_locked(adapter);
	rtnl_unlock();
पूर्ण

/**
 * e1000e_get_stats64 - Get System Network Statistics
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @stats: rtnl_link_stats64 poपूर्णांकer
 *
 * Returns the address of the device statistics काष्ठाure.
 **/
व्योम e1000e_get_stats64(काष्ठा net_device *netdev,
			काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	spin_lock(&adapter->stats64_lock);
	e1000e_update_stats(adapter);
	/* Fill out the OS statistics काष्ठाure */
	stats->rx_bytes = adapter->stats.gorc;
	stats->rx_packets = adapter->stats.gprc;
	stats->tx_bytes = adapter->stats.gotc;
	stats->tx_packets = adapter->stats.gptc;
	stats->multicast = adapter->stats.mprc;
	stats->collisions = adapter->stats.colc;

	/* Rx Errors */

	/* RLEC on some newer hardware can be incorrect so build
	 * our own version based on RUC and ROC
	 */
	stats->rx_errors = adapter->stats.rxerrc +
	    adapter->stats.crcerrs + adapter->stats.algnerrc +
	    adapter->stats.ruc + adapter->stats.roc + adapter->stats.cexterr;
	stats->rx_length_errors = adapter->stats.ruc + adapter->stats.roc;
	stats->rx_crc_errors = adapter->stats.crcerrs;
	stats->rx_frame_errors = adapter->stats.algnerrc;
	stats->rx_missed_errors = adapter->stats.mpc;

	/* Tx Errors */
	stats->tx_errors = adapter->stats.ecol + adapter->stats.latecol;
	stats->tx_पातed_errors = adapter->stats.ecol;
	stats->tx_winकरोw_errors = adapter->stats.latecol;
	stats->tx_carrier_errors = adapter->stats.tncrs;

	/* Tx Dropped needs to be मुख्यtained अन्यथाwhere */

	spin_unlock(&adapter->stats64_lock);
पूर्ण

/**
 * e1000_change_mtu - Change the Maximum Transfer Unit
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @new_mtu: new value क्रम maximum frame size
 *
 * Returns 0 on success, negative on failure
 **/
अटल पूर्णांक e1000_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	पूर्णांक max_frame = new_mtu + VLAN_ETH_HLEN + ETH_FCS_LEN;

	/* Jumbo frame support */
	अगर ((new_mtu > ETH_DATA_LEN) &&
	    !(adapter->flags & FLAG_HAS_JUMBO_FRAMES)) अणु
		e_err("Jumbo Frames not supported.\n");
		वापस -EINVAL;
	पूर्ण

	/* Jumbo frame workaround on 82579 and newer requires CRC be stripped */
	अगर ((adapter->hw.mac.type >= e1000_pch2lan) &&
	    !(adapter->flags2 & FLAG2_CRC_STRIPPING) &&
	    (new_mtu > ETH_DATA_LEN)) अणु
		e_err("Jumbo Frames not supported on this device when CRC stripping is disabled.\n");
		वापस -EINVAL;
	पूर्ण

	जबतक (test_and_set_bit(__E1000_RESETTING, &adapter->state))
		usleep_range(1000, 1100);
	/* e1000e_करोwn -> e1000e_reset dependent on max_frame_size & mtu */
	adapter->max_frame_size = max_frame;
	netdev_dbg(netdev, "changing MTU from %d to %d\n",
		   netdev->mtu, new_mtu);
	netdev->mtu = new_mtu;

	pm_runसमय_get_sync(netdev->dev.parent);

	अगर (netअगर_running(netdev))
		e1000e_करोwn(adapter, true);

	/* NOTE: netdev_alloc_skb reserves 16 bytes, and typically NET_IP_ALIGN
	 * means we reserve 2 more, this pushes us to allocate from the next
	 * larger slab size.
	 * i.e. RXBUFFER_2048 --> size-4096 slab
	 * However with the new *_jumbo_rx* routines, jumbo receives will use
	 * fragmented skbs
	 */

	अगर (max_frame <= 2048)
		adapter->rx_buffer_len = 2048;
	अन्यथा
		adapter->rx_buffer_len = 4096;

	/* adjust allocation अगर LPE protects us, and we aren't using SBP */
	अगर (max_frame <= (VLAN_ETH_FRAME_LEN + ETH_FCS_LEN))
		adapter->rx_buffer_len = VLAN_ETH_FRAME_LEN + ETH_FCS_LEN;

	अगर (netअगर_running(netdev))
		e1000e_up(adapter);
	अन्यथा
		e1000e_reset(adapter);

	pm_runसमय_put_sync(netdev->dev.parent);

	clear_bit(__E1000_RESETTING, &adapter->state);

	वापस 0;
पूर्ण

अटल पूर्णांक e1000_mii_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr,
			   पूर्णांक cmd)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा mii_ioctl_data *data = अगर_mii(अगरr);

	अगर (adapter->hw.phy.media_type != e1000_media_type_copper)
		वापस -EOPNOTSUPP;

	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
		data->phy_id = adapter->hw.phy.addr;
		अवरोध;
	हाल SIOCGMIIREG:
		e1000_phy_पढ़ो_status(adapter);

		चयन (data->reg_num & 0x1F) अणु
		हाल MII_BMCR:
			data->val_out = adapter->phy_regs.bmcr;
			अवरोध;
		हाल MII_BMSR:
			data->val_out = adapter->phy_regs.bmsr;
			अवरोध;
		हाल MII_PHYSID1:
			data->val_out = (adapter->hw.phy.id >> 16);
			अवरोध;
		हाल MII_PHYSID2:
			data->val_out = (adapter->hw.phy.id & 0xFFFF);
			अवरोध;
		हाल MII_ADVERTISE:
			data->val_out = adapter->phy_regs.advertise;
			अवरोध;
		हाल MII_LPA:
			data->val_out = adapter->phy_regs.lpa;
			अवरोध;
		हाल MII_EXPANSION:
			data->val_out = adapter->phy_regs.expansion;
			अवरोध;
		हाल MII_CTRL1000:
			data->val_out = adapter->phy_regs.ctrl1000;
			अवरोध;
		हाल MII_STAT1000:
			data->val_out = adapter->phy_regs.stat1000;
			अवरोध;
		हाल MII_ESTATUS:
			data->val_out = adapter->phy_regs.estatus;
			अवरोध;
		शेष:
			वापस -EIO;
		पूर्ण
		अवरोध;
	हाल SIOCSMIIREG:
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * e1000e_hwtstamp_set - control hardware समय stamping
 * @netdev: network पूर्णांकerface device काष्ठाure
 * @अगरr: पूर्णांकerface request
 *
 * Outgoing समय stamping can be enabled and disabled. Play nice and
 * disable it when requested, although it shouldn't cause any overhead
 * when no packet needs it. At most one packet in the queue may be
 * marked क्रम समय stamping, otherwise it would be impossible to tell
 * क्रम sure to which packet the hardware समय stamp beदीर्घs.
 *
 * Incoming समय stamping has to be configured via the hardware filters.
 * Not all combinations are supported, in particular event type has to be
 * specअगरied. Matching the kind of event packet is not supported, with the
 * exception of "all V2 events regardless of level 2 or 4".
 **/
अटल पूर्णांक e1000e_hwtstamp_set(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा hwtstamp_config config;
	पूर्णांक ret_val;

	अगर (copy_from_user(&config, अगरr->अगरr_data, माप(config)))
		वापस -EFAULT;

	ret_val = e1000e_config_hwtstamp(adapter, &config);
	अगर (ret_val)
		वापस ret_val;

	चयन (config.rx_filter) अणु
	हाल HWTSTAMP_FILTER_PTP_V2_L4_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_SYNC:
	हाल HWTSTAMP_FILTER_PTP_V2_L4_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_L2_DELAY_REQ:
	हाल HWTSTAMP_FILTER_PTP_V2_DELAY_REQ:
		/* With V2 type filters which specअगरy a Sync or Delay Request,
		 * Path Delay Request/Response messages are also समय stamped
		 * by hardware so notअगरy the caller the requested packets plus
		 * some others are समय stamped.
		 */
		config.rx_filter = HWTSTAMP_FILTER_SOME;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस copy_to_user(अगरr->अगरr_data, &config,
			    माप(config)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक e1000e_hwtstamp_get(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	वापस copy_to_user(अगरr->अगरr_data, &adapter->hwtstamp_config,
			    माप(adapter->hwtstamp_config)) ? -EFAULT : 0;
पूर्ण

अटल पूर्णांक e1000_ioctl(काष्ठा net_device *netdev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SIOCGMIIPHY:
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
		वापस e1000_mii_ioctl(netdev, अगरr, cmd);
	हाल SIOCSHWTSTAMP:
		वापस e1000e_hwtstamp_set(netdev, अगरr);
	हाल SIOCGHWTSTAMP:
		वापस e1000e_hwtstamp_get(netdev, अगरr);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक e1000_init_phy_wakeup(काष्ठा e1000_adapter *adapter, u32 wufc)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 i, mac_reg, wuc;
	u16 phy_reg, wuc_enable;
	पूर्णांक retval;

	/* copy MAC RARs to PHY RARs */
	e1000_copy_rx_addrs_to_phy_ich8lan(hw);

	retval = hw->phy.ops.acquire(hw);
	अगर (retval) अणु
		e_err("Could not acquire PHY\n");
		वापस retval;
	पूर्ण

	/* Enable access to wakeup रेजिस्टरs on and set page to BM_WUC_PAGE */
	retval = e1000_enable_phy_wakeup_reg_access_bm(hw, &wuc_enable);
	अगर (retval)
		जाओ release;

	/* copy MAC MTA to PHY MTA - only needed क्रम pchlan */
	क्रम (i = 0; i < adapter->hw.mac.mta_reg_count; i++) अणु
		mac_reg = E1000_READ_REG_ARRAY(hw, E1000_MTA, i);
		hw->phy.ops.ग_लिखो_reg_page(hw, BM_MTA(i),
					   (u16)(mac_reg & 0xFFFF));
		hw->phy.ops.ग_लिखो_reg_page(hw, BM_MTA(i) + 1,
					   (u16)((mac_reg >> 16) & 0xFFFF));
	पूर्ण

	/* configure PHY Rx Control रेजिस्टर */
	hw->phy.ops.पढ़ो_reg_page(&adapter->hw, BM_RCTL, &phy_reg);
	mac_reg = er32(RCTL);
	अगर (mac_reg & E1000_RCTL_UPE)
		phy_reg |= BM_RCTL_UPE;
	अगर (mac_reg & E1000_RCTL_MPE)
		phy_reg |= BM_RCTL_MPE;
	phy_reg &= ~(BM_RCTL_MO_MASK);
	अगर (mac_reg & E1000_RCTL_MO_3)
		phy_reg |= (((mac_reg & E1000_RCTL_MO_3) >> E1000_RCTL_MO_SHIFT)
			    << BM_RCTL_MO_SHIFT);
	अगर (mac_reg & E1000_RCTL_BAM)
		phy_reg |= BM_RCTL_BAM;
	अगर (mac_reg & E1000_RCTL_PMCF)
		phy_reg |= BM_RCTL_PMCF;
	mac_reg = er32(CTRL);
	अगर (mac_reg & E1000_CTRL_RFCE)
		phy_reg |= BM_RCTL_RFCE;
	hw->phy.ops.ग_लिखो_reg_page(&adapter->hw, BM_RCTL, phy_reg);

	wuc = E1000_WUC_PME_EN;
	अगर (wufc & (E1000_WUFC_MAG | E1000_WUFC_LNKC))
		wuc |= E1000_WUC_APME;

	/* enable PHY wakeup in MAC रेजिस्टर */
	ew32(WUFC, wufc);
	ew32(WUC, (E1000_WUC_PHY_WAKE | E1000_WUC_APMPME |
		   E1000_WUC_PME_STATUS | wuc));

	/* configure and enable PHY wakeup in PHY रेजिस्टरs */
	hw->phy.ops.ग_लिखो_reg_page(&adapter->hw, BM_WUFC, wufc);
	hw->phy.ops.ग_लिखो_reg_page(&adapter->hw, BM_WUC, wuc);

	/* activate PHY wakeup */
	wuc_enable |= BM_WUC_ENABLE_BIT | BM_WUC_HOST_WU_BIT;
	retval = e1000_disable_phy_wakeup_reg_access_bm(hw, &wuc_enable);
	अगर (retval)
		e_err("Could not set PHY Host Wakeup bit\n");
release:
	hw->phy.ops.release(hw);

	वापस retval;
पूर्ण

अटल व्योम e1000e_flush_lpic(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ret_val;

	pm_runसमय_get_sync(netdev->dev.parent);

	ret_val = hw->phy.ops.acquire(hw);
	अगर (ret_val)
		जाओ fl_out;

	pr_info("EEE TX LPI TIMER: %08X\n",
		er32(LPIC) >> E1000_LPIC_LPIET_SHIFT);

	hw->phy.ops.release(hw);

fl_out:
	pm_runसमय_put_sync(netdev->dev.parent);
पूर्ण

/* S0ix implementation */
अटल व्योम e1000e_s0ix_entry_flow(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 mac_data;
	u16 phy_data;

	/* Disable the periodic inband message,
	 * करोn't request PCIe घड़ी in K1 page770_17[10:9] = 10b
	 */
	e1e_rphy(hw, HV_PM_CTRL, &phy_data);
	phy_data &= ~HV_PM_CTRL_K1_CLK_REQ;
	phy_data |= BIT(10);
	e1e_wphy(hw, HV_PM_CTRL, phy_data);

	/* Make sure we करोn't निकास K1 every समय a new packet arrives
	 * 772_29[5] = 1 CS_Mode_Stay_In_K1
	 */
	e1e_rphy(hw, I217_CGFREG, &phy_data);
	phy_data |= BIT(5);
	e1e_wphy(hw, I217_CGFREG, phy_data);

	/* Change the MAC/PHY पूर्णांकerface to SMBus
	 * Force the SMBus in PHY page769_23[0] = 1
	 * Force the SMBus in MAC CTRL_EXT[11] = 1
	 */
	e1e_rphy(hw, CV_SMB_CTRL, &phy_data);
	phy_data |= CV_SMB_CTRL_FORCE_SMBUS;
	e1e_wphy(hw, CV_SMB_CTRL, phy_data);
	mac_data = er32(CTRL_EXT);
	mac_data |= E1000_CTRL_EXT_FORCE_SMBUS;
	ew32(CTRL_EXT, mac_data);

	/* DFT control: PHY bit: page769_20[0] = 1
	 * Gate PPW via EXTCNF_CTRL - set 0x0F00[7] = 1
	 */
	e1e_rphy(hw, I82579_DFT_CTRL, &phy_data);
	phy_data |= BIT(0);
	e1e_wphy(hw, I82579_DFT_CTRL, phy_data);

	mac_data = er32(EXTCNF_CTRL);
	mac_data |= E1000_EXTCNF_CTRL_GATE_PHY_CFG;
	ew32(EXTCNF_CTRL, mac_data);

	/* Check MAC Tx/Rx packet buffer poपूर्णांकers.
	 * Reset MAC Tx/Rx packet buffer poपूर्णांकers to suppress any
	 * pending traffic indication that would prevent घातer gating.
	 */
	mac_data = er32(TDFH);
	अगर (mac_data)
		ew32(TDFH, 0);
	mac_data = er32(TDFT);
	अगर (mac_data)
		ew32(TDFT, 0);
	mac_data = er32(TDFHS);
	अगर (mac_data)
		ew32(TDFHS, 0);
	mac_data = er32(TDFTS);
	अगर (mac_data)
		ew32(TDFTS, 0);
	mac_data = er32(TDFPC);
	अगर (mac_data)
		ew32(TDFPC, 0);
	mac_data = er32(RDFH);
	अगर (mac_data)
		ew32(RDFH, 0);
	mac_data = er32(RDFT);
	अगर (mac_data)
		ew32(RDFT, 0);
	mac_data = er32(RDFHS);
	अगर (mac_data)
		ew32(RDFHS, 0);
	mac_data = er32(RDFTS);
	अगर (mac_data)
		ew32(RDFTS, 0);
	mac_data = er32(RDFPC);
	अगर (mac_data)
		ew32(RDFPC, 0);

	/* Enable the Dynamic Power Gating in the MAC */
	mac_data = er32(FEXTNVM7);
	mac_data |= BIT(22);
	ew32(FEXTNVM7, mac_data);

	/* Disable the समय synchronization घड़ी */
	mac_data = er32(FEXTNVM7);
	mac_data |= BIT(31);
	mac_data &= ~BIT(0);
	ew32(FEXTNVM7, mac_data);

	/* Dynamic Power Gating Enable */
	mac_data = er32(CTRL_EXT);
	mac_data |= BIT(3);
	ew32(CTRL_EXT, mac_data);

	/* Disable disconnected cable conditioning क्रम Power Gating */
	mac_data = er32(DPGFR);
	mac_data |= BIT(2);
	ew32(DPGFR, mac_data);

	/* Don't wake from dynamic Power Gating with घड़ी request */
	mac_data = er32(FEXTNVM12);
	mac_data |= BIT(12);
	ew32(FEXTNVM12, mac_data);

	/* Ungate PGCB घड़ी */
	mac_data = er32(FEXTNVM9);
	mac_data &= ~BIT(28);
	ew32(FEXTNVM9, mac_data);

	/* Enable K1 off to enable mPHY Power Gating */
	mac_data = er32(FEXTNVM6);
	mac_data |= BIT(31);
	ew32(FEXTNVM6, mac_data);

	/* Enable mPHY घातer gating क्रम any link and speed */
	mac_data = er32(FEXTNVM8);
	mac_data |= BIT(9);
	ew32(FEXTNVM8, mac_data);

	/* Enable the Dynamic Clock Gating in the DMA and MAC */
	mac_data = er32(CTRL_EXT);
	mac_data |= E1000_CTRL_EXT_DMA_DYN_CLK_EN;
	ew32(CTRL_EXT, mac_data);

	/* No MAC DPG gating SLP_S0 in modern standby
	 * Switch the logic of the lanphypc to use PMC counter
	 */
	mac_data = er32(FEXTNVM5);
	mac_data |= BIT(7);
	ew32(FEXTNVM5, mac_data);
पूर्ण

अटल व्योम e1000e_s0ix_निकास_flow(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 mac_data;
	u16 phy_data;

	/* Disable the Dynamic Power Gating in the MAC */
	mac_data = er32(FEXTNVM7);
	mac_data &= 0xFFBFFFFF;
	ew32(FEXTNVM7, mac_data);

	/* Enable the समय synchronization घड़ी */
	mac_data = er32(FEXTNVM7);
	mac_data |= BIT(0);
	ew32(FEXTNVM7, mac_data);

	/* Disable mPHY घातer gating क्रम any link and speed */
	mac_data = er32(FEXTNVM8);
	mac_data &= ~BIT(9);
	ew32(FEXTNVM8, mac_data);

	/* Disable K1 off */
	mac_data = er32(FEXTNVM6);
	mac_data &= ~BIT(31);
	ew32(FEXTNVM6, mac_data);

	/* Disable Ungate PGCB घड़ी */
	mac_data = er32(FEXTNVM9);
	mac_data |= BIT(28);
	ew32(FEXTNVM9, mac_data);

	/* Cancel not waking from dynamic
	 * Power Gating with घड़ी request
	 */
	mac_data = er32(FEXTNVM12);
	mac_data &= ~BIT(12);
	ew32(FEXTNVM12, mac_data);

	/* Cancel disable disconnected cable conditioning
	 * क्रम Power Gating
	 */
	mac_data = er32(DPGFR);
	mac_data &= ~BIT(2);
	ew32(DPGFR, mac_data);

	/* Disable Dynamic Power Gating */
	mac_data = er32(CTRL_EXT);
	mac_data &= 0xFFFFFFF7;
	ew32(CTRL_EXT, mac_data);

	/* Disable the Dynamic Clock Gating in the DMA and MAC */
	mac_data = er32(CTRL_EXT);
	mac_data &= 0xFFF7FFFF;
	ew32(CTRL_EXT, mac_data);

	/* Revert the lanphypc logic to use the पूर्णांकernal Gbe counter
	 * and not the PMC counter
	 */
	mac_data = er32(FEXTNVM5);
	mac_data &= 0xFFFFFF7F;
	ew32(FEXTNVM5, mac_data);

	/* Enable the periodic inband message,
	 * Request PCIe घड़ी in K1 page770_17[10:9] =01b
	 */
	e1e_rphy(hw, HV_PM_CTRL, &phy_data);
	phy_data &= 0xFBFF;
	phy_data |= HV_PM_CTRL_K1_CLK_REQ;
	e1e_wphy(hw, HV_PM_CTRL, phy_data);

	/* Return back configuration
	 * 772_29[5] = 0 CS_Mode_Stay_In_K1
	 */
	e1e_rphy(hw, I217_CGFREG, &phy_data);
	phy_data &= 0xFFDF;
	e1e_wphy(hw, I217_CGFREG, phy_data);

	/* Change the MAC/PHY पूर्णांकerface to Kumeran
	 * Unक्रमce the SMBus in PHY page769_23[0] = 0
	 * Unक्रमce the SMBus in MAC CTRL_EXT[11] = 0
	 */
	e1e_rphy(hw, CV_SMB_CTRL, &phy_data);
	phy_data &= ~CV_SMB_CTRL_FORCE_SMBUS;
	e1e_wphy(hw, CV_SMB_CTRL, phy_data);
	mac_data = er32(CTRL_EXT);
	mac_data &= ~E1000_CTRL_EXT_FORCE_SMBUS;
	ew32(CTRL_EXT, mac_data);
पूर्ण

अटल पूर्णांक e1000e_pm_मुक्तze(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	bool present;

	rtnl_lock();

	present = netअगर_device_present(netdev);
	netअगर_device_detach(netdev);

	अगर (present && netअगर_running(netdev)) अणु
		पूर्णांक count = E1000_CHECK_RESET_COUNT;

		जबतक (test_bit(__E1000_RESETTING, &adapter->state) && count--)
			usleep_range(10000, 11000);

		WARN_ON(test_bit(__E1000_RESETTING, &adapter->state));

		/* Quiesce the device without resetting the hardware */
		e1000e_करोwn(adapter, false);
		e1000_मुक्त_irq(adapter);
	पूर्ण
	rtnl_unlock();

	e1000e_reset_पूर्णांकerrupt_capability(adapter);

	/* Allow समय क्रम pending master requests to run */
	e1000e_disable_pcie_master(&adapter->hw);

	वापस 0;
पूर्ण

अटल पूर्णांक __e1000_shutकरोwn(काष्ठा pci_dev *pdev, bool runसमय)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u32 ctrl, ctrl_ext, rctl, status, wufc;
	पूर्णांक retval = 0;

	/* Runसमय suspend should only enable wakeup क्रम link changes */
	अगर (runसमय)
		wufc = E1000_WUFC_LNKC;
	अन्यथा अगर (device_may_wakeup(&pdev->dev))
		wufc = adapter->wol;
	अन्यथा
		wufc = 0;

	status = er32(STATUS);
	अगर (status & E1000_STATUS_LU)
		wufc &= ~E1000_WUFC_LNKC;

	अगर (wufc) अणु
		e1000_setup_rctl(adapter);
		e1000e_set_rx_mode(netdev);

		/* turn on all-multi mode अगर wake on multicast is enabled */
		अगर (wufc & E1000_WUFC_MC) अणु
			rctl = er32(RCTL);
			rctl |= E1000_RCTL_MPE;
			ew32(RCTL, rctl);
		पूर्ण

		ctrl = er32(CTRL);
		ctrl |= E1000_CTRL_ADVD3WUC;
		अगर (!(adapter->flags2 & FLAG2_HAS_PHY_WAKEUP))
			ctrl |= E1000_CTRL_EN_PHY_PWR_MGMT;
		ew32(CTRL, ctrl);

		अगर (adapter->hw.phy.media_type == e1000_media_type_fiber ||
		    adapter->hw.phy.media_type ==
		    e1000_media_type_पूर्णांकernal_serdes) अणु
			/* keep the laser running in D3 */
			ctrl_ext = er32(CTRL_EXT);
			ctrl_ext |= E1000_CTRL_EXT_SDP3_DATA;
			ew32(CTRL_EXT, ctrl_ext);
		पूर्ण

		अगर (!runसमय)
			e1000e_घातer_up_phy(adapter);

		अगर (adapter->flags & FLAG_IS_ICH)
			e1000_suspend_workarounds_ich8lan(&adapter->hw);

		अगर (adapter->flags2 & FLAG2_HAS_PHY_WAKEUP) अणु
			/* enable wakeup by the PHY */
			retval = e1000_init_phy_wakeup(adapter, wufc);
			अगर (retval)
				वापस retval;
		पूर्ण अन्यथा अणु
			/* enable wakeup by the MAC */
			ew32(WUFC, wufc);
			ew32(WUC, E1000_WUC_PME_EN);
		पूर्ण
	पूर्ण अन्यथा अणु
		ew32(WUC, 0);
		ew32(WUFC, 0);

		e1000_घातer_करोwn_phy(adapter);
	पूर्ण

	अगर (adapter->hw.phy.type == e1000_phy_igp_3) अणु
		e1000e_igp3_phy_घातerकरोwn_workaround_ich8lan(&adapter->hw);
	पूर्ण अन्यथा अगर (hw->mac.type >= e1000_pch_lpt) अणु
		अगर (wufc && !(wufc & (E1000_WUFC_EX | E1000_WUFC_MC | E1000_WUFC_BC)))
			/* ULP करोes not support wake from unicast, multicast
			 * or broadcast.
			 */
			retval = e1000_enable_ulp_lpt_lp(hw, !runसमय);

		अगर (retval)
			वापस retval;
	पूर्ण

	/* Ensure that the appropriate bits are set in LPI_CTRL
	 * क्रम EEE in Sx
	 */
	अगर ((hw->phy.type >= e1000_phy_i217) &&
	    adapter->eee_advert && hw->dev_spec.ich8lan.eee_lp_ability) अणु
		u16 lpi_ctrl = 0;

		retval = hw->phy.ops.acquire(hw);
		अगर (!retval) अणु
			retval = e1e_rphy_locked(hw, I82579_LPI_CTRL,
						 &lpi_ctrl);
			अगर (!retval) अणु
				अगर (adapter->eee_advert &
				    hw->dev_spec.ich8lan.eee_lp_ability &
				    I82579_EEE_100_SUPPORTED)
					lpi_ctrl |= I82579_LPI_CTRL_100_ENABLE;
				अगर (adapter->eee_advert &
				    hw->dev_spec.ich8lan.eee_lp_ability &
				    I82579_EEE_1000_SUPPORTED)
					lpi_ctrl |= I82579_LPI_CTRL_1000_ENABLE;

				retval = e1e_wphy_locked(hw, I82579_LPI_CTRL,
							 lpi_ctrl);
			पूर्ण
		पूर्ण
		hw->phy.ops.release(hw);
	पूर्ण

	/* Release control of h/w to f/w.  If f/w is AMT enabled, this
	 * would have alपढ़ोy happened in बंद and is redundant.
	 */
	e1000e_release_hw_control(adapter);

	pci_clear_master(pdev);

	/* The pci-e चयन on some quad port adapters will report a
	 * correctable error when the MAC transitions from D0 to D3.  To
	 * prevent this we need to mask off the correctable errors on the
	 * करोwnstream port of the pci-e चयन.
	 *
	 * We करोn't have the associated upstream bridge जबतक assigning
	 * the PCI device पूर्णांकo guest. For example, the KVM on घातer is
	 * one of the हालs.
	 */
	अगर (adapter->flags & FLAG_IS_QUAD_PORT) अणु
		काष्ठा pci_dev *us_dev = pdev->bus->self;
		u16 devctl;

		अगर (!us_dev)
			वापस 0;

		pcie_capability_पढ़ो_word(us_dev, PCI_EXP_DEVCTL, &devctl);
		pcie_capability_ग_लिखो_word(us_dev, PCI_EXP_DEVCTL,
					   (devctl & ~PCI_EXP_DEVCTL_CERE));

		pci_save_state(pdev);
		pci_prepare_to_sleep(pdev);

		pcie_capability_ग_लिखो_word(us_dev, PCI_EXP_DEVCTL, devctl);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * __e1000e_disable_aspm - Disable ASPM states
 * @pdev: poपूर्णांकer to PCI device काष्ठा
 * @state: bit-mask of ASPM states to disable
 * @locked: indication अगर this context holds pci_bus_sem locked.
 *
 * Some devices *must* have certain ASPM states disabled per hardware errata.
 **/
अटल व्योम __e1000e_disable_aspm(काष्ठा pci_dev *pdev, u16 state, पूर्णांक locked)
अणु
	काष्ठा pci_dev *parent = pdev->bus->self;
	u16 aspm_dis_mask = 0;
	u16 pdev_aspmc, parent_aspmc;

	चयन (state) अणु
	हाल PCIE_LINK_STATE_L0S:
	हाल PCIE_LINK_STATE_L0S | PCIE_LINK_STATE_L1:
		aspm_dis_mask |= PCI_EXP_LNKCTL_ASPM_L0S;
		fallthrough; /* can't have L1 without L0s */
	हाल PCIE_LINK_STATE_L1:
		aspm_dis_mask |= PCI_EXP_LNKCTL_ASPM_L1;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	pcie_capability_पढ़ो_word(pdev, PCI_EXP_LNKCTL, &pdev_aspmc);
	pdev_aspmc &= PCI_EXP_LNKCTL_ASPMC;

	अगर (parent) अणु
		pcie_capability_पढ़ो_word(parent, PCI_EXP_LNKCTL,
					  &parent_aspmc);
		parent_aspmc &= PCI_EXP_LNKCTL_ASPMC;
	पूर्ण

	/* Nothing to करो अगर the ASPM states to be disabled alपढ़ोy are */
	अगर (!(pdev_aspmc & aspm_dis_mask) &&
	    (!parent || !(parent_aspmc & aspm_dis_mask)))
		वापस;

	dev_info(&pdev->dev, "Disabling ASPM %s %s\n",
		 (aspm_dis_mask & pdev_aspmc & PCI_EXP_LNKCTL_ASPM_L0S) ?
		 "L0s" : "",
		 (aspm_dis_mask & pdev_aspmc & PCI_EXP_LNKCTL_ASPM_L1) ?
		 "L1" : "");

#अगर_घोषित CONFIG_PCIEASPM
	अगर (locked)
		pci_disable_link_state_locked(pdev, state);
	अन्यथा
		pci_disable_link_state(pdev, state);

	/* Double-check ASPM control.  If not disabled by the above, the
	 * BIOS is preventing that from happening (or CONFIG_PCIEASPM is
	 * not enabled); override by writing PCI config space directly.
	 */
	pcie_capability_पढ़ो_word(pdev, PCI_EXP_LNKCTL, &pdev_aspmc);
	pdev_aspmc &= PCI_EXP_LNKCTL_ASPMC;

	अगर (!(aspm_dis_mask & pdev_aspmc))
		वापस;
#पूर्ण_अगर

	/* Both device and parent should have the same ASPM setting.
	 * Disable ASPM in करोwnstream component first and then upstream.
	 */
	pcie_capability_clear_word(pdev, PCI_EXP_LNKCTL, aspm_dis_mask);

	अगर (parent)
		pcie_capability_clear_word(parent, PCI_EXP_LNKCTL,
					   aspm_dis_mask);
पूर्ण

/**
 * e1000e_disable_aspm - Disable ASPM states.
 * @pdev: poपूर्णांकer to PCI device काष्ठा
 * @state: bit-mask of ASPM states to disable
 *
 * This function acquires the pci_bus_sem!
 * Some devices *must* have certain ASPM states disabled per hardware errata.
 **/
अटल व्योम e1000e_disable_aspm(काष्ठा pci_dev *pdev, u16 state)
अणु
	__e1000e_disable_aspm(pdev, state, 0);
पूर्ण

/**
 * e1000e_disable_aspm_locked - Disable ASPM states.
 * @pdev: poपूर्णांकer to PCI device काष्ठा
 * @state: bit-mask of ASPM states to disable
 *
 * This function must be called with pci_bus_sem acquired!
 * Some devices *must* have certain ASPM states disabled per hardware errata.
 **/
अटल व्योम e1000e_disable_aspm_locked(काष्ठा pci_dev *pdev, u16 state)
अणु
	__e1000e_disable_aspm(pdev, state, 1);
पूर्ण

अटल पूर्णांक e1000e_pm_thaw(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	पूर्णांक rc = 0;

	e1000e_set_पूर्णांकerrupt_capability(adapter);

	rtnl_lock();
	अगर (netअगर_running(netdev)) अणु
		rc = e1000_request_irq(adapter);
		अगर (rc)
			जाओ err_irq;

		e1000e_up(adapter);
	पूर्ण

	netअगर_device_attach(netdev);
err_irq:
	rtnl_unlock();

	वापस rc;
पूर्ण

अटल पूर्णांक __e1000_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 aspm_disable_flag = 0;

	अगर (adapter->flags2 & FLAG2_DISABLE_ASPM_L0S)
		aspm_disable_flag = PCIE_LINK_STATE_L0S;
	अगर (adapter->flags2 & FLAG2_DISABLE_ASPM_L1)
		aspm_disable_flag |= PCIE_LINK_STATE_L1;
	अगर (aspm_disable_flag)
		e1000e_disable_aspm(pdev, aspm_disable_flag);

	pci_set_master(pdev);

	अगर (hw->mac.type >= e1000_pch2lan)
		e1000_resume_workarounds_pchlan(&adapter->hw);

	e1000e_घातer_up_phy(adapter);

	/* report the प्रणाली wakeup cause from S3/S4 */
	अगर (adapter->flags2 & FLAG2_HAS_PHY_WAKEUP) अणु
		u16 phy_data;

		e1e_rphy(&adapter->hw, BM_WUS, &phy_data);
		अगर (phy_data) अणु
			e_info("PHY Wakeup cause - %s\n",
			       phy_data & E1000_WUS_EX ? "Unicast Packet" :
			       phy_data & E1000_WUS_MC ? "Multicast Packet" :
			       phy_data & E1000_WUS_BC ? "Broadcast Packet" :
			       phy_data & E1000_WUS_MAG ? "Magic Packet" :
			       phy_data & E1000_WUS_LNKC ?
			       "Link Status Change" : "other");
		पूर्ण
		e1e_wphy(&adapter->hw, BM_WUS, ~0);
	पूर्ण अन्यथा अणु
		u32 wus = er32(WUS);

		अगर (wus) अणु
			e_info("MAC Wakeup cause - %s\n",
			       wus & E1000_WUS_EX ? "Unicast Packet" :
			       wus & E1000_WUS_MC ? "Multicast Packet" :
			       wus & E1000_WUS_BC ? "Broadcast Packet" :
			       wus & E1000_WUS_MAG ? "Magic Packet" :
			       wus & E1000_WUS_LNKC ? "Link Status Change" :
			       "other");
		पूर्ण
		ew32(WUS, ~0);
	पूर्ण

	e1000e_reset(adapter);

	e1000_init_manageability_pt(adapter);

	/* If the controller has AMT, करो not set DRV_LOAD until the पूर्णांकerface
	 * is up.  For all other हालs, let the f/w know that the h/w is now
	 * under the control of the driver.
	 */
	अगर (!(adapter->flags & FLAG_HAS_AMT))
		e1000e_get_hw_control(adapter);

	वापस 0;
पूर्ण

अटल __maybe_unused पूर्णांक e1000e_pm_prepare(काष्ठा device *dev)
अणु
	वापस pm_runसमय_suspended(dev) &&
		pm_suspend_via_firmware();
पूर्ण

अटल __maybe_unused पूर्णांक e1000e_pm_suspend(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(to_pci_dev(dev));
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	पूर्णांक rc;

	e1000e_flush_lpic(pdev);

	e1000e_pm_मुक्तze(dev);

	rc = __e1000_shutकरोwn(pdev, false);
	अगर (rc) अणु
		e1000e_pm_thaw(dev);
	पूर्ण अन्यथा अणु
		/* Introduce S0ix implementation */
		अगर (adapter->flags2 & FLAG2_ENABLE_S0IX_FLOWS)
			e1000e_s0ix_entry_flow(adapter);
	पूर्ण

	वापस rc;
पूर्ण

अटल __maybe_unused पूर्णांक e1000e_pm_resume(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(to_pci_dev(dev));
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	पूर्णांक rc;

	/* Introduce S0ix implementation */
	अगर (adapter->flags2 & FLAG2_ENABLE_S0IX_FLOWS)
		e1000e_s0ix_निकास_flow(adapter);

	rc = __e1000_resume(pdev);
	अगर (rc)
		वापस rc;

	वापस e1000e_pm_thaw(dev);
पूर्ण

अटल __maybe_unused पूर्णांक e1000e_pm_runसमय_idle(काष्ठा device *dev)
अणु
	काष्ठा net_device *netdev = dev_get_drvdata(dev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	u16 eee_lp;

	eee_lp = adapter->hw.dev_spec.ich8lan.eee_lp_ability;

	अगर (!e1000e_has_link(adapter)) अणु
		adapter->hw.dev_spec.ich8lan.eee_lp_ability = eee_lp;
		pm_schedule_suspend(dev, 5 * MSEC_PER_SEC);
	पूर्ण

	वापस -EBUSY;
पूर्ण

अटल __maybe_unused पूर्णांक e1000e_pm_runसमय_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	पूर्णांक rc;

	rc = __e1000_resume(pdev);
	अगर (rc)
		वापस rc;

	अगर (netdev->flags & IFF_UP)
		e1000e_up(adapter);

	वापस rc;
पूर्ण

अटल __maybe_unused पूर्णांक e1000e_pm_runसमय_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	अगर (netdev->flags & IFF_UP) अणु
		पूर्णांक count = E1000_CHECK_RESET_COUNT;

		जबतक (test_bit(__E1000_RESETTING, &adapter->state) && count--)
			usleep_range(10000, 11000);

		WARN_ON(test_bit(__E1000_RESETTING, &adapter->state));

		/* Down the device without resetting the hardware */
		e1000e_करोwn(adapter, false);
	पूर्ण

	अगर (__e1000_shutकरोwn(pdev, true)) अणु
		e1000e_pm_runसमय_resume(dev);
		वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम e1000_shutकरोwn(काष्ठा pci_dev *pdev)
अणु
	e1000e_flush_lpic(pdev);

	e1000e_pm_मुक्तze(&pdev->dev);

	__e1000_shutकरोwn(pdev, false);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER

अटल irqवापस_t e1000_पूर्णांकr_msix(पूर्णांक __always_unused irq, व्योम *data)
अणु
	काष्ठा net_device *netdev = data;
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	अगर (adapter->msix_entries) अणु
		पूर्णांक vector, msix_irq;

		vector = 0;
		msix_irq = adapter->msix_entries[vector].vector;
		अगर (disable_hardirq(msix_irq))
			e1000_पूर्णांकr_msix_rx(msix_irq, netdev);
		enable_irq(msix_irq);

		vector++;
		msix_irq = adapter->msix_entries[vector].vector;
		अगर (disable_hardirq(msix_irq))
			e1000_पूर्णांकr_msix_tx(msix_irq, netdev);
		enable_irq(msix_irq);

		vector++;
		msix_irq = adapter->msix_entries[vector].vector;
		अगर (disable_hardirq(msix_irq))
			e1000_msix_other(msix_irq, netdev);
		enable_irq(msix_irq);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/**
 * e1000_netpoll
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Polling 'interrupt' - used by things like netconsole to send skbs
 * without having to re-enable पूर्णांकerrupts. It's not called जबतक
 * the पूर्णांकerrupt routine is executing.
 */
अटल व्योम e1000_netpoll(काष्ठा net_device *netdev)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	चयन (adapter->पूर्णांक_mode) अणु
	हाल E1000E_INT_MODE_MSIX:
		e1000_पूर्णांकr_msix(adapter->pdev->irq, netdev);
		अवरोध;
	हाल E1000E_INT_MODE_MSI:
		अगर (disable_hardirq(adapter->pdev->irq))
			e1000_पूर्णांकr_msi(adapter->pdev->irq, netdev);
		enable_irq(adapter->pdev->irq);
		अवरोध;
	शेष:		/* E1000E_INT_MODE_LEGACY */
		अगर (disable_hardirq(adapter->pdev->irq))
			e1000_पूर्णांकr(adapter->pdev->irq, netdev);
		enable_irq(adapter->pdev->irq);
		अवरोध;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/**
 * e1000_io_error_detected - called when PCI error is detected
 * @pdev: Poपूर्णांकer to PCI device
 * @state: The current pci connection state
 *
 * This function is called after a PCI bus error affecting
 * this device has been detected.
 */
अटल pci_ers_result_t e1000_io_error_detected(काष्ठा pci_dev *pdev,
						pci_channel_state_t state)
अणु
	e1000e_pm_मुक्तze(&pdev->dev);

	अगर (state == pci_channel_io_perm_failure)
		वापस PCI_ERS_RESULT_DISCONNECT;

	pci_disable_device(pdev);

	/* Request a slot slot reset. */
	वापस PCI_ERS_RESULT_NEED_RESET;
पूर्ण

/**
 * e1000_io_slot_reset - called after the pci bus has been reset.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * Restart the card from scratch, as अगर from a cold-boot. Implementation
 * resembles the first-half of the e1000e_pm_resume routine.
 */
अटल pci_ers_result_t e1000_io_slot_reset(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;
	u16 aspm_disable_flag = 0;
	पूर्णांक err;
	pci_ers_result_t result;

	अगर (adapter->flags2 & FLAG2_DISABLE_ASPM_L0S)
		aspm_disable_flag = PCIE_LINK_STATE_L0S;
	अगर (adapter->flags2 & FLAG2_DISABLE_ASPM_L1)
		aspm_disable_flag |= PCIE_LINK_STATE_L1;
	अगर (aspm_disable_flag)
		e1000e_disable_aspm_locked(pdev, aspm_disable_flag);

	err = pci_enable_device_mem(pdev);
	अगर (err) अणु
		dev_err(&pdev->dev,
			"Cannot re-enable PCI device after reset.\n");
		result = PCI_ERS_RESULT_DISCONNECT;
	पूर्ण अन्यथा अणु
		pdev->state_saved = true;
		pci_restore_state(pdev);
		pci_set_master(pdev);

		pci_enable_wake(pdev, PCI_D3hot, 0);
		pci_enable_wake(pdev, PCI_D3cold, 0);

		e1000e_reset(adapter);
		ew32(WUS, ~0);
		result = PCI_ERS_RESULT_RECOVERED;
	पूर्ण

	वापस result;
पूर्ण

/**
 * e1000_io_resume - called when traffic can start flowing again.
 * @pdev: Poपूर्णांकer to PCI device
 *
 * This callback is called when the error recovery driver tells us that
 * its OK to resume normal operation. Implementation resembles the
 * second-half of the e1000e_pm_resume routine.
 */
अटल व्योम e1000_io_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	e1000_init_manageability_pt(adapter);

	e1000e_pm_thaw(&pdev->dev);

	/* If the controller has AMT, करो not set DRV_LOAD until the पूर्णांकerface
	 * is up.  For all other हालs, let the f/w know that the h/w is now
	 * under the control of the driver.
	 */
	अगर (!(adapter->flags & FLAG_HAS_AMT))
		e1000e_get_hw_control(adapter);
पूर्ण

अटल व्योम e1000_prपूर्णांक_device_info(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	काष्ठा net_device *netdev = adapter->netdev;
	u32 ret_val;
	u8 pba_str[E1000_PBANUM_LENGTH];

	/* prपूर्णांक bus type/speed/width info */
	e_info("(PCI Express:2.5GT/s:%s) %pM\n",
	       /* bus width */
	       ((hw->bus.width == e1000_bus_width_pcie_x4) ? "Width x4" :
		"Width x1"),
	       /* MAC address */
	       netdev->dev_addr);
	e_info("Intel(R) PRO/%s Network Connection\n",
	       (hw->phy.type == e1000_phy_अगरe) ? "10/100" : "1000");
	ret_val = e1000_पढ़ो_pba_string_generic(hw, pba_str,
						E1000_PBANUM_LENGTH);
	अगर (ret_val)
		strlcpy((अक्षर *)pba_str, "Unknown", माप(pba_str));
	e_info("MAC: %d, PHY: %d, PBA No: %s\n",
	       hw->mac.type, hw->phy.type, pba_str);
पूर्ण

अटल व्योम e1000_eeprom_checks(काष्ठा e1000_adapter *adapter)
अणु
	काष्ठा e1000_hw *hw = &adapter->hw;
	पूर्णांक ret_val;
	u16 buf = 0;

	अगर (hw->mac.type != e1000_82573)
		वापस;

	ret_val = e1000_पढ़ो_nvm(hw, NVM_INIT_CONTROL2_REG, 1, &buf);
	le16_to_cpus(&buf);
	अगर (!ret_val && (!(buf & BIT(0)))) अणु
		/* Deep Smart Power Down (DSPD) */
		dev_warn(&adapter->pdev->dev,
			 "Warning: detected DSPD enabled in EEPROM\n");
	पूर्ण
पूर्ण

अटल netdev_features_t e1000_fix_features(काष्ठा net_device *netdev,
					    netdev_features_t features)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	काष्ठा e1000_hw *hw = &adapter->hw;

	/* Jumbo frame workaround on 82579 and newer requires CRC be stripped */
	अगर ((hw->mac.type >= e1000_pch2lan) && (netdev->mtu > ETH_DATA_LEN))
		features &= ~NETIF_F_RXFCS;

	/* Since there is no support क्रम separate Rx/Tx vlan accel
	 * enable/disable make sure Tx flag is always in same state as Rx.
	 */
	अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
		features |= NETIF_F_HW_VLAN_CTAG_TX;
	अन्यथा
		features &= ~NETIF_F_HW_VLAN_CTAG_TX;

	वापस features;
पूर्ण

अटल पूर्णांक e1000_set_features(काष्ठा net_device *netdev,
			      netdev_features_t features)
अणु
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);
	netdev_features_t changed = features ^ netdev->features;

	अगर (changed & (NETIF_F_TSO | NETIF_F_TSO6))
		adapter->flags |= FLAG_TSO_FORCE;

	अगर (!(changed & (NETIF_F_HW_VLAN_CTAG_RX | NETIF_F_HW_VLAN_CTAG_TX |
			 NETIF_F_RXCSUM | NETIF_F_RXHASH | NETIF_F_RXFCS |
			 NETIF_F_RXALL)))
		वापस 0;

	अगर (changed & NETIF_F_RXFCS) अणु
		अगर (features & NETIF_F_RXFCS) अणु
			adapter->flags2 &= ~FLAG2_CRC_STRIPPING;
		पूर्ण अन्यथा अणु
			/* We need to take it back to शेषs, which might mean
			 * stripping is still disabled at the adapter level.
			 */
			अगर (adapter->flags2 & FLAG2_DFLT_CRC_STRIPPING)
				adapter->flags2 |= FLAG2_CRC_STRIPPING;
			अन्यथा
				adapter->flags2 &= ~FLAG2_CRC_STRIPPING;
		पूर्ण
	पूर्ण

	netdev->features = features;

	अगर (netअगर_running(netdev))
		e1000e_reinit_locked(adapter);
	अन्यथा
		e1000e_reset(adapter);

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा net_device_ops e1000e_netdev_ops = अणु
	.nकरो_खोलो		= e1000e_खोलो,
	.nकरो_stop		= e1000e_बंद,
	.nकरो_start_xmit		= e1000_xmit_frame,
	.nकरो_get_stats64	= e1000e_get_stats64,
	.nकरो_set_rx_mode	= e1000e_set_rx_mode,
	.nकरो_set_mac_address	= e1000_set_mac,
	.nकरो_change_mtu		= e1000_change_mtu,
	.nकरो_करो_ioctl		= e1000_ioctl,
	.nकरो_tx_समयout		= e1000_tx_समयout,
	.nकरो_validate_addr	= eth_validate_addr,

	.nकरो_vlan_rx_add_vid	= e1000_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= e1000_vlan_rx_समाप्त_vid,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= e1000_netpoll,
#पूर्ण_अगर
	.nकरो_set_features = e1000_set_features,
	.nकरो_fix_features = e1000_fix_features,
	.nकरो_features_check	= passthru_features_check,
पूर्ण;

/**
 * e1000_probe - Device Initialization Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 * @ent: entry in e1000_pci_tbl
 *
 * Returns 0 on success, negative on failure
 *
 * e1000_probe initializes an adapter identअगरied by a pci_dev काष्ठाure.
 * The OS initialization, configuring of the adapter निजी काष्ठाure,
 * and a hardware reset occur.
 **/
अटल पूर्णांक e1000_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा e1000_adapter *adapter;
	काष्ठा e1000_hw *hw;
	स्थिर काष्ठा e1000_info *ei = e1000_info_tbl[ent->driver_data];
	resource_माप_प्रकार mmio_start, mmio_len;
	resource_माप_प्रकार flash_start, flash_len;
	अटल पूर्णांक cards_found;
	u16 aspm_disable_flag = 0;
	पूर्णांक bars, i, err, pci_using_dac;
	u16 eeprom_data = 0;
	u16 eeprom_apme_mask = E1000_EEPROM_APME;
	s32 ret_val = 0;

	अगर (ei->flags2 & FLAG2_DISABLE_ASPM_L0S)
		aspm_disable_flag = PCIE_LINK_STATE_L0S;
	अगर (ei->flags2 & FLAG2_DISABLE_ASPM_L1)
		aspm_disable_flag |= PCIE_LINK_STATE_L1;
	अगर (aspm_disable_flag)
		e1000e_disable_aspm(pdev, aspm_disable_flag);

	err = pci_enable_device_mem(pdev);
	अगर (err)
		वापस err;

	pci_using_dac = 0;
	err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	अगर (!err) अणु
		pci_using_dac = 1;
	पूर्ण अन्यथा अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err) अणु
			dev_err(&pdev->dev,
				"No usable DMA configuration, aborting\n");
			जाओ err_dma;
		पूर्ण
	पूर्ण

	bars = pci_select_bars(pdev, IORESOURCE_MEM);
	err = pci_request_selected_regions_exclusive(pdev, bars,
						     e1000e_driver_name);
	अगर (err)
		जाओ err_pci_reg;

	/* AER (Advanced Error Reporting) hooks */
	pci_enable_pcie_error_reporting(pdev);

	pci_set_master(pdev);
	/* PCI config space info */
	err = pci_save_state(pdev);
	अगर (err)
		जाओ err_alloc_etherdev;

	err = -ENOMEM;
	netdev = alloc_etherdev(माप(काष्ठा e1000_adapter));
	अगर (!netdev)
		जाओ err_alloc_etherdev;

	SET_NETDEV_DEV(netdev, &pdev->dev);

	netdev->irq = pdev->irq;

	pci_set_drvdata(pdev, netdev);
	adapter = netdev_priv(netdev);
	hw = &adapter->hw;
	adapter->netdev = netdev;
	adapter->pdev = pdev;
	adapter->ei = ei;
	adapter->pba = ei->pba;
	adapter->flags = ei->flags;
	adapter->flags2 = ei->flags2;
	adapter->hw.adapter = adapter;
	adapter->hw.mac.type = ei->mac;
	adapter->max_hw_frame_size = ei->max_hw_frame_size;
	adapter->msg_enable = netअगर_msg_init(debug, DEFAULT_MSG_ENABLE);

	mmio_start = pci_resource_start(pdev, 0);
	mmio_len = pci_resource_len(pdev, 0);

	err = -EIO;
	adapter->hw.hw_addr = ioremap(mmio_start, mmio_len);
	अगर (!adapter->hw.hw_addr)
		जाओ err_ioremap;

	अगर ((adapter->flags & FLAG_HAS_FLASH) &&
	    (pci_resource_flags(pdev, 1) & IORESOURCE_MEM) &&
	    (hw->mac.type < e1000_pch_spt)) अणु
		flash_start = pci_resource_start(pdev, 1);
		flash_len = pci_resource_len(pdev, 1);
		adapter->hw.flash_address = ioremap(flash_start, flash_len);
		अगर (!adapter->hw.flash_address)
			जाओ err_flashmap;
	पूर्ण

	/* Set शेष EEE advertisement */
	अगर (adapter->flags2 & FLAG2_HAS_EEE)
		adapter->eee_advert = MDIO_EEE_100TX | MDIO_EEE_1000T;

	/* स्थिरruct the net_device काष्ठा */
	netdev->netdev_ops = &e1000e_netdev_ops;
	e1000e_set_ethtool_ops(netdev);
	netdev->watchकरोg_समयo = 5 * HZ;
	netअगर_napi_add(netdev, &adapter->napi, e1000e_poll, 64);
	strlcpy(netdev->name, pci_name(pdev), माप(netdev->name));

	netdev->mem_start = mmio_start;
	netdev->mem_end = mmio_start + mmio_len;

	adapter->bd_number = cards_found++;

	e1000e_check_options(adapter);

	/* setup adapter काष्ठा */
	err = e1000_sw_init(adapter);
	अगर (err)
		जाओ err_sw_init;

	स_नकल(&hw->mac.ops, ei->mac_ops, माप(hw->mac.ops));
	स_नकल(&hw->nvm.ops, ei->nvm_ops, माप(hw->nvm.ops));
	स_नकल(&hw->phy.ops, ei->phy_ops, माप(hw->phy.ops));

	err = ei->get_variants(adapter);
	अगर (err)
		जाओ err_hw_init;

	अगर ((adapter->flags & FLAG_IS_ICH) &&
	    (adapter->flags & FLAG_READ_ONLY_NVM) &&
	    (hw->mac.type < e1000_pch_spt))
		e1000e_ग_लिखो_protect_nvm_ich8lan(&adapter->hw);

	hw->mac.ops.get_bus_info(&adapter->hw);

	adapter->hw.phy.स्वतःneg_रुको_to_complete = 0;

	/* Copper options */
	अगर (adapter->hw.phy.media_type == e1000_media_type_copper) अणु
		adapter->hw.phy.mdix = AUTO_ALL_MODES;
		adapter->hw.phy.disable_polarity_correction = 0;
		adapter->hw.phy.ms_type = e1000_ms_hw_शेष;
	पूर्ण

	अगर (hw->phy.ops.check_reset_block && hw->phy.ops.check_reset_block(hw))
		dev_info(&pdev->dev,
			 "PHY reset is blocked due to SOL/IDER session.\n");

	/* Set initial शेष active device features */
	netdev->features = (NETIF_F_SG |
			    NETIF_F_HW_VLAN_CTAG_RX |
			    NETIF_F_HW_VLAN_CTAG_TX |
			    NETIF_F_TSO |
			    NETIF_F_TSO6 |
			    NETIF_F_RXHASH |
			    NETIF_F_RXCSUM |
			    NETIF_F_HW_CSUM);

	/* Set user-changeable features (subset of all device features) */
	netdev->hw_features = netdev->features;
	netdev->hw_features |= NETIF_F_RXFCS;
	netdev->priv_flags |= IFF_SUPP_NOFCS;
	netdev->hw_features |= NETIF_F_RXALL;

	अगर (adapter->flags & FLAG_HAS_HW_VLAN_FILTER)
		netdev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;

	netdev->vlan_features |= (NETIF_F_SG |
				  NETIF_F_TSO |
				  NETIF_F_TSO6 |
				  NETIF_F_HW_CSUM);

	netdev->priv_flags |= IFF_UNICAST_FLT;

	अगर (pci_using_dac) अणु
		netdev->features |= NETIF_F_HIGHDMA;
		netdev->vlan_features |= NETIF_F_HIGHDMA;
	पूर्ण

	/* MTU range: 68 - max_hw_frame_size */
	netdev->min_mtu = ETH_MIN_MTU;
	netdev->max_mtu = adapter->max_hw_frame_size -
			  (VLAN_ETH_HLEN + ETH_FCS_LEN);

	अगर (e1000e_enable_mng_pass_thru(&adapter->hw))
		adapter->flags |= FLAG_MNG_PT_ENABLED;

	/* beक्रमe पढ़ोing the NVM, reset the controller to
	 * put the device in a known good starting state
	 */
	adapter->hw.mac.ops.reset_hw(&adapter->hw);

	/* प्रणालीs with ASPM and others may see the checksum fail on the first
	 * attempt. Let's give it a few tries
	 */
	क्रम (i = 0;; i++) अणु
		अगर (e1000_validate_nvm_checksum(&adapter->hw) >= 0)
			अवरोध;
		अगर (i == 2) अणु
			dev_err(&pdev->dev, "The NVM Checksum Is Not Valid\n");
			err = -EIO;
			जाओ err_eeprom;
		पूर्ण
	पूर्ण

	e1000_eeprom_checks(adapter);

	/* copy the MAC address */
	अगर (e1000e_पढ़ो_mac_addr(&adapter->hw))
		dev_err(&pdev->dev,
			"NVM Read Error while reading MAC address\n");

	स_नकल(netdev->dev_addr, adapter->hw.mac.addr, netdev->addr_len);

	अगर (!is_valid_ether_addr(netdev->dev_addr)) अणु
		dev_err(&pdev->dev, "Invalid MAC Address: %pM\n",
			netdev->dev_addr);
		err = -EIO;
		जाओ err_eeprom;
	पूर्ण

	समयr_setup(&adapter->watchकरोg_समयr, e1000_watchकरोg, 0);
	समयr_setup(&adapter->phy_info_समयr, e1000_update_phy_info, 0);

	INIT_WORK(&adapter->reset_task, e1000_reset_task);
	INIT_WORK(&adapter->watchकरोg_task, e1000_watchकरोg_task);
	INIT_WORK(&adapter->करोwnshअगरt_task, e1000e_करोwnshअगरt_workaround);
	INIT_WORK(&adapter->update_phy_task, e1000e_update_phy_task);
	INIT_WORK(&adapter->prपूर्णांक_hang_task, e1000_prपूर्णांक_hw_hang);

	/* Initialize link parameters. User can change them with ethtool */
	adapter->hw.mac.स्वतःneg = 1;
	adapter->fc_स्वतःneg = true;
	adapter->hw.fc.requested_mode = e1000_fc_शेष;
	adapter->hw.fc.current_mode = e1000_fc_शेष;
	adapter->hw.phy.स्वतःneg_advertised = 0x2f;

	/* Initial Wake on LAN setting - If APM wake is enabled in
	 * the EEPROM, enable the ACPI Magic Packet filter
	 */
	अगर (adapter->flags & FLAG_APME_IN_WUC) अणु
		/* APME bit in EEPROM is mapped to WUC.APME */
		eeprom_data = er32(WUC);
		eeprom_apme_mask = E1000_WUC_APME;
		अगर ((hw->mac.type > e1000_ich10lan) &&
		    (eeprom_data & E1000_WUC_PHY_WAKE))
			adapter->flags2 |= FLAG2_HAS_PHY_WAKEUP;
	पूर्ण अन्यथा अगर (adapter->flags & FLAG_APME_IN_CTRL3) अणु
		अगर (adapter->flags & FLAG_APME_CHECK_PORT_B &&
		    (adapter->hw.bus.func == 1))
			ret_val = e1000_पढ़ो_nvm(&adapter->hw,
					      NVM_INIT_CONTROL3_PORT_B,
					      1, &eeprom_data);
		अन्यथा
			ret_val = e1000_पढ़ो_nvm(&adapter->hw,
					      NVM_INIT_CONTROL3_PORT_A,
					      1, &eeprom_data);
	पूर्ण

	/* fetch WoL from EEPROM */
	अगर (ret_val)
		e_dbg("NVM read error getting WoL initial values: %d\n", ret_val);
	अन्यथा अगर (eeprom_data & eeprom_apme_mask)
		adapter->eeprom_wol |= E1000_WUFC_MAG;

	/* now that we have the eeprom settings, apply the special हालs
	 * where the eeprom may be wrong or the board simply won't support
	 * wake on lan on a particular port
	 */
	अगर (!(adapter->flags & FLAG_HAS_WOL))
		adapter->eeprom_wol = 0;

	/* initialize the wol settings based on the eeprom settings */
	adapter->wol = adapter->eeprom_wol;

	/* make sure adapter isn't asleep अगर manageability is enabled */
	अगर (adapter->wol || (adapter->flags & FLAG_MNG_PT_ENABLED) ||
	    (hw->mac.ops.check_mng_mode(hw)))
		device_wakeup_enable(&pdev->dev);

	/* save off EEPROM version number */
	ret_val = e1000_पढ़ो_nvm(&adapter->hw, 5, 1, &adapter->eeprom_vers);

	अगर (ret_val) अणु
		e_dbg("NVM read error getting EEPROM version: %d\n", ret_val);
		adapter->eeprom_vers = 0;
	पूर्ण

	/* init PTP hardware घड़ी */
	e1000e_ptp_init(adapter);

	/* reset the hardware with the new settings */
	e1000e_reset(adapter);

	/* If the controller has AMT, करो not set DRV_LOAD until the पूर्णांकerface
	 * is up.  For all other हालs, let the f/w know that the h/w is now
	 * under the control of the driver.
	 */
	अगर (!(adapter->flags & FLAG_HAS_AMT))
		e1000e_get_hw_control(adapter);

	अगर (hw->mac.type >= e1000_pch_cnp)
		adapter->flags2 |= FLAG2_ENABLE_S0IX_FLOWS;

	strlcpy(netdev->name, "eth%d", माप(netdev->name));
	err = रेजिस्टर_netdev(netdev);
	अगर (err)
		जाओ err_रेजिस्टर;

	/* carrier off reporting is important to ethtool even BEFORE खोलो */
	netअगर_carrier_off(netdev);

	e1000_prपूर्णांक_device_info(adapter);

	dev_pm_set_driver_flags(&pdev->dev, DPM_FLAG_SMART_PREPARE);

	अगर (pci_dev_run_wake(pdev) && hw->mac.type != e1000_pch_cnp)
		pm_runसमय_put_noidle(&pdev->dev);

	वापस 0;

err_रेजिस्टर:
	अगर (!(adapter->flags & FLAG_HAS_AMT))
		e1000e_release_hw_control(adapter);
err_eeprom:
	अगर (hw->phy.ops.check_reset_block && !hw->phy.ops.check_reset_block(hw))
		e1000_phy_hw_reset(&adapter->hw);
err_hw_init:
	kमुक्त(adapter->tx_ring);
	kमुक्त(adapter->rx_ring);
err_sw_init:
	अगर ((adapter->hw.flash_address) && (hw->mac.type < e1000_pch_spt))
		iounmap(adapter->hw.flash_address);
	e1000e_reset_पूर्णांकerrupt_capability(adapter);
err_flashmap:
	iounmap(adapter->hw.hw_addr);
err_ioremap:
	मुक्त_netdev(netdev);
err_alloc_etherdev:
	pci_release_mem_regions(pdev);
err_pci_reg:
err_dma:
	pci_disable_device(pdev);
	वापस err;
पूर्ण

/**
 * e1000_हटाओ - Device Removal Routine
 * @pdev: PCI device inक्रमmation काष्ठा
 *
 * e1000_हटाओ is called by the PCI subप्रणाली to alert the driver
 * that it should release a PCI device.  The could be caused by a
 * Hot-Plug event, or because the driver is going to be हटाओd from
 * memory.
 **/
अटल व्योम e1000_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा e1000_adapter *adapter = netdev_priv(netdev);

	e1000e_ptp_हटाओ(adapter);

	/* The समयrs may be rescheduled, so explicitly disable them
	 * from being rescheduled.
	 */
	set_bit(__E1000_DOWN, &adapter->state);
	del_समयr_sync(&adapter->watchकरोg_समयr);
	del_समयr_sync(&adapter->phy_info_समयr);

	cancel_work_sync(&adapter->reset_task);
	cancel_work_sync(&adapter->watchकरोg_task);
	cancel_work_sync(&adapter->करोwnshअगरt_task);
	cancel_work_sync(&adapter->update_phy_task);
	cancel_work_sync(&adapter->prपूर्णांक_hang_task);

	अगर (adapter->flags & FLAG_HAS_HW_TIMESTAMP) अणु
		cancel_work_sync(&adapter->tx_hwtstamp_work);
		अगर (adapter->tx_hwtstamp_skb) अणु
			dev_consume_skb_any(adapter->tx_hwtstamp_skb);
			adapter->tx_hwtstamp_skb = शून्य;
		पूर्ण
	पूर्ण

	unरेजिस्टर_netdev(netdev);

	अगर (pci_dev_run_wake(pdev))
		pm_runसमय_get_noresume(&pdev->dev);

	/* Release control of h/w to f/w.  If f/w is AMT enabled, this
	 * would have alपढ़ोy happened in बंद and is redundant.
	 */
	e1000e_release_hw_control(adapter);

	e1000e_reset_पूर्णांकerrupt_capability(adapter);
	kमुक्त(adapter->tx_ring);
	kमुक्त(adapter->rx_ring);

	iounmap(adapter->hw.hw_addr);
	अगर ((adapter->hw.flash_address) &&
	    (adapter->hw.mac.type < e1000_pch_spt))
		iounmap(adapter->hw.flash_address);
	pci_release_mem_regions(pdev);

	मुक्त_netdev(netdev);

	/* AER disable */
	pci_disable_pcie_error_reporting(pdev);

	pci_disable_device(pdev);
पूर्ण

/* PCI Error Recovery (ERS) */
अटल स्थिर काष्ठा pci_error_handlers e1000_err_handler = अणु
	.error_detected = e1000_io_error_detected,
	.slot_reset = e1000_io_slot_reset,
	.resume = e1000_io_resume,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id e1000_pci_tbl[] = अणु
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82571EB_COPPER), board_82571 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82571EB_FIBER), board_82571 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82571EB_QUAD_COPPER), board_82571 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82571EB_QUAD_COPPER_LP),
	  board_82571 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82571EB_QUAD_FIBER), board_82571 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82571EB_SERDES), board_82571 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82571EB_SERDES_DUAL), board_82571 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82571EB_SERDES_QUAD), board_82571 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82571PT_QUAD_COPPER), board_82571 पूर्ण,

	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82572EI), board_82572 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82572EI_COPPER), board_82572 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82572EI_FIBER), board_82572 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82572EI_SERDES), board_82572 पूर्ण,

	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82573E), board_82573 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82573E_IAMT), board_82573 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82573L), board_82573 पूर्ण,

	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82574L), board_82574 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82574LA), board_82574 पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_82583V), board_82583 पूर्ण,

	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_80003ES2LAN_COPPER_DPT),
	  board_80003es2lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_80003ES2LAN_COPPER_SPT),
	  board_80003es2lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_80003ES2LAN_SERDES_DPT),
	  board_80003es2lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_80003ES2LAN_SERDES_SPT),
	  board_80003es2lan पूर्ण,

	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH8_IFE), board_ich8lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH8_IFE_G), board_ich8lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH8_IFE_GT), board_ich8lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH8_IGP_AMT), board_ich8lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH8_IGP_C), board_ich8lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH8_IGP_M), board_ich8lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH8_IGP_M_AMT), board_ich8lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH8_82567V_3), board_ich8lan पूर्ण,

	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH9_IFE), board_ich9lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH9_IFE_G), board_ich9lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH9_IFE_GT), board_ich9lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH9_IGP_AMT), board_ich9lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH9_IGP_C), board_ich9lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH9_BM), board_ich9lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH9_IGP_M), board_ich9lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH9_IGP_M_AMT), board_ich9lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH9_IGP_M_V), board_ich9lan पूर्ण,

	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH10_R_BM_LM), board_ich9lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH10_R_BM_LF), board_ich9lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH10_R_BM_V), board_ich9lan पूर्ण,

	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH10_D_BM_LM), board_ich10lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH10_D_BM_LF), board_ich10lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_ICH10_D_BM_V), board_ich10lan पूर्ण,

	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_M_HV_LM), board_pchlan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_M_HV_LC), board_pchlan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_D_HV_DM), board_pchlan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_D_HV_DC), board_pchlan पूर्ण,

	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH2_LV_LM), board_pch2lan पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH2_LV_V), board_pch2lan पूर्ण,

	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_LPT_I217_LM), board_pch_lpt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_LPT_I217_V), board_pch_lpt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_LPTLP_I218_LM), board_pch_lpt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_LPTLP_I218_V), board_pch_lpt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_I218_LM2), board_pch_lpt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_I218_V2), board_pch_lpt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_I218_LM3), board_pch_lpt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_I218_V3), board_pch_lpt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_SPT_I219_LM), board_pch_spt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_SPT_I219_V), board_pch_spt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_SPT_I219_LM2), board_pch_spt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_SPT_I219_V2), board_pch_spt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_LBG_I219_LM3), board_pch_spt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_SPT_I219_LM4), board_pch_spt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_SPT_I219_V4), board_pch_spt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_SPT_I219_LM5), board_pch_spt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_SPT_I219_V5), board_pch_spt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_CNP_I219_LM6), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_CNP_I219_V6), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_CNP_I219_LM7), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_CNP_I219_V7), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_ICP_I219_LM8), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_ICP_I219_V8), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_ICP_I219_LM9), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_ICP_I219_V9), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_CMP_I219_LM10), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_CMP_I219_V10), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_CMP_I219_LM11), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_CMP_I219_V11), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_CMP_I219_LM12), board_pch_spt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_CMP_I219_V12), board_pch_spt पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_TGP_I219_LM13), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_TGP_I219_V13), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_TGP_I219_LM14), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_TGP_I219_V14), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_TGP_I219_LM15), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_TGP_I219_V15), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_ADP_I219_LM16), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_ADP_I219_V16), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_ADP_I219_LM17), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_ADP_I219_V17), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_MTP_I219_LM18), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_MTP_I219_V18), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_MTP_I219_LM19), board_pch_cnp पूर्ण,
	अणु PCI_VDEVICE(INTEL, E1000_DEV_ID_PCH_MTP_I219_V19), board_pch_cnp पूर्ण,

	अणु 0, 0, 0, 0, 0, 0, 0 पूर्ण	/* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, e1000_pci_tbl);

अटल स्थिर काष्ठा dev_pm_ops e1000_pm_ops = अणु
#अगर_घोषित CONFIG_PM_SLEEP
	.prepare	= e1000e_pm_prepare,
	.suspend	= e1000e_pm_suspend,
	.resume		= e1000e_pm_resume,
	.मुक्तze		= e1000e_pm_मुक्तze,
	.thaw		= e1000e_pm_thaw,
	.घातeroff	= e1000e_pm_suspend,
	.restore	= e1000e_pm_resume,
#पूर्ण_अगर
	SET_RUNTIME_PM_OPS(e1000e_pm_runसमय_suspend, e1000e_pm_runसमय_resume,
			   e1000e_pm_runसमय_idle)
पूर्ण;

/* PCI Device API Driver */
अटल काष्ठा pci_driver e1000_driver = अणु
	.name     = e1000e_driver_name,
	.id_table = e1000_pci_tbl,
	.probe    = e1000_probe,
	.हटाओ   = e1000_हटाओ,
	.driver   = अणु
		.pm = &e1000_pm_ops,
	पूर्ण,
	.shutकरोwn = e1000_shutकरोwn,
	.err_handler = &e1000_err_handler
पूर्ण;

/**
 * e1000_init_module - Driver Registration Routine
 *
 * e1000_init_module is the first routine called when the driver is
 * loaded. All it करोes is रेजिस्टर with the PCI subप्रणाली.
 **/
अटल पूर्णांक __init e1000_init_module(व्योम)
अणु
	pr_info("Intel(R) PRO/1000 Network Driver\n");
	pr_info("Copyright(c) 1999 - 2015 Intel Corporation.\n");

	वापस pci_रेजिस्टर_driver(&e1000_driver);
पूर्ण
module_init(e1000_init_module);

/**
 * e1000_निकास_module - Driver Exit Cleanup Routine
 *
 * e1000_निकास_module is called just beक्रमe the driver is हटाओd
 * from memory.
 **/
अटल व्योम __निकास e1000_निकास_module(व्योम)
अणु
	pci_unरेजिस्टर_driver(&e1000_driver);
पूर्ण
module_निकास(e1000_निकास_module);

MODULE_AUTHOR("Intel Corporation, <linux.nics@intel.com>");
MODULE_DESCRIPTION("Intel(R) PRO/1000 Network Driver");
MODULE_LICENSE("GPL v2");

/* netdev.c */
