<शैली गुरु>
/* Agere Systems Inc.
 * 10/100/1000 Base-T Ethernet Driver क्रम the ET1301 and ET131x series MACs
 *
 * Copyright तऊ 2005 Agere Systems Inc.
 * All rights reserved.
 *   http://www.agere.com
 *
 * Copyright (c) 2011 Mark Einon <mark.einon@gmail.com>
 *
 *------------------------------------------------------------------------------
 *
 * SOFTWARE LICENSE
 *
 * This software is provided subject to the following terms and conditions,
 * which you should पढ़ो carefully beक्रमe using the software.  Using this
 * software indicates your acceptance of these terms and conditions.  If you करो
 * not agree with these terms and conditions, करो not use the software.
 *
 * Copyright तऊ 2005 Agere Systems Inc.
 * All rights reserved.
 *
 * Redistribution and use in source or binary क्रमms, with or without
 * modअगरications, are permitted provided that the following conditions are met:
 *
 * . Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following Disclaimer as comments in the code as
 *    well as in the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * . Redistributions in binary क्रमm must reproduce the above copyright notice,
 *    this list of conditions and the following Disclaimer in the करोcumentation
 *    and/or other materials provided with the distribution.
 *
 * . Neither the name of Agere Systems Inc. nor the names of the contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 *
 * Disclaimer
 *
 * THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, INFRINGEMENT AND THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  ANY
 * USE, MODIFICATION OR DISTRIBUTION OF THIS SOFTWARE IS SOLELY AT THE USERS OWN
 * RISK. IN NO EVENT SHALL AGERE SYSTEMS INC. OR CONTRIBUTORS BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, INCLUDING, BUT NOT LIMITED TO, CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/pci.h>
#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>

#समावेश <linux/sched.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/in.h>
#समावेश <linux/delay.h>
#समावेश <linux/bitops.h>
#समावेश <linux/पन.स>

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/ioport.h>
#समावेश <linux/crc32.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/phy.h>

#समावेश "et131x.h"

MODULE_AUTHOR("Victor Soriano <vjsoriano@agere.com>");
MODULE_AUTHOR("Mark Einon <mark.einon@gmail.com>");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("10/100/1000 Base-T Ethernet Driver for the ET1310 by Agere Systems");

/* EEPROM defines */
#घोषणा MAX_NUM_REGISTER_POLLS          1000
#घोषणा MAX_NUM_WRITE_RETRIES           2

/* MAC defines */
#घोषणा COUNTER_WRAP_16_BIT 0x10000
#घोषणा COUNTER_WRAP_12_BIT 0x1000

/* PCI defines */
#घोषणा INTERNAL_MEM_SIZE       0x400	/* 1024 of पूर्णांकernal memory */
#घोषणा INTERNAL_MEM_RX_OFFSET  0x1FF	/* 50%   Tx, 50%   Rx */

/* ISR defines */
/* For पूर्णांकerrupts, normal running is:
 *       rxdma_xfr_करोne, phy_पूर्णांकerrupt, mac_stat_पूर्णांकerrupt,
 *       watchकरोg_पूर्णांकerrupt & txdma_xfer_करोne
 *
 * In both हालs, when flow control is enabled क्रम either Tx or bi-direction,
 * we additional enable rx_fbr0_low and rx_fbr1_low, so we know when the
 * buffer rings are running low.
 */
#घोषणा INT_MASK_DISABLE            0xffffffff

/* NOTE: Masking out MAC_STAT Interrupt क्रम now...
 * #घोषणा INT_MASK_ENABLE             0xfff6bf17
 * #घोषणा INT_MASK_ENABLE_NO_FLOW     0xfff6bfd7
 */
#घोषणा INT_MASK_ENABLE             0xfffebf17
#घोषणा INT_MASK_ENABLE_NO_FLOW     0xfffebfd7

/* General defines */
/* Packet and header sizes */
#घोषणा NIC_MIN_PACKET_SIZE	60

/* Multicast list size */
#घोषणा NIC_MAX_MCAST_LIST	128

/* Supported Filters */
#घोषणा ET131X_PACKET_TYPE_सूचीECTED		0x0001
#घोषणा ET131X_PACKET_TYPE_MULTICAST		0x0002
#घोषणा ET131X_PACKET_TYPE_BROADCAST		0x0004
#घोषणा ET131X_PACKET_TYPE_PROMISCUOUS		0x0008
#घोषणा ET131X_PACKET_TYPE_ALL_MULTICAST	0x0010

/* Tx Timeout */
#घोषणा ET131X_TX_TIMEOUT	(1 * HZ)
#घोषणा NIC_SEND_HANG_THRESHOLD	0

/* MP_ADAPTER flags */
#घोषणा FMP_ADAPTER_INTERRUPT_IN_USE	0x00000008

/* MP_SHARED flags */
#घोषणा FMP_ADAPTER_LOWER_POWER		0x00200000

#घोषणा FMP_ADAPTER_NON_RECOVER_ERROR	0x00800000
#घोषणा FMP_ADAPTER_HARDWARE_ERROR	0x04000000

#घोषणा FMP_ADAPTER_FAIL_SEND_MASK	0x3ff00000

/* Some offsets in PCI config space that are actually used. */
#घोषणा ET1310_PCI_MAC_ADDRESS		0xA4
#घोषणा ET1310_PCI_EEPROM_STATUS	0xB2
#घोषणा ET1310_PCI_ACK_NACK		0xC0
#घोषणा ET1310_PCI_REPLAY		0xC2
#घोषणा ET1310_PCI_L0L1LATENCY		0xCF

/* PCI Product IDs */
#घोषणा ET131X_PCI_DEVICE_ID_GIG	0xED00	/* ET1310 1000 Base-T 8 */
#घोषणा ET131X_PCI_DEVICE_ID_FAST	0xED01	/* ET1310 100  Base-T */

/* Define order of magnitude converter */
#घोषणा न_अंकO_IN_A_MICRO	1000

#घोषणा PARM_RX_NUM_BUFS_DEF    4
#घोषणा PARM_RX_TIME_INT_DEF    10
#घोषणा PARM_RX_MEM_END_DEF     0x2bc
#घोषणा PARM_TX_TIME_INT_DEF    40
#घोषणा PARM_TX_NUM_BUFS_DEF    4
#घोषणा PARM_DMA_CACHE_DEF      0

/* RX defines */
#घोषणा FBR_CHUNKS		32
#घोषणा MAX_DESC_PER_RING_RX	1024

/* number of RFDs - शेष and min */
#घोषणा RFD_LOW_WATER_MARK	40
#घोषणा NIC_DEFAULT_NUM_RFD	1024
#घोषणा NUM_FBRS		2

#घोषणा MAX_PACKETS_HANDLED	256
#घोषणा ET131X_MIN_MTU		64
#घोषणा ET131X_MAX_MTU		9216

#घोषणा ALCATEL_MULTICAST_PKT	0x01000000
#घोषणा ALCATEL_BROADCAST_PKT	0x02000000

/* प्रकारs क्रम Free Buffer Descriptors */
काष्ठा fbr_desc अणु
	u32 addr_lo;
	u32 addr_hi;
	u32 word2;		/* Bits 10-31 reserved, 0-9 descriptor */
पूर्ण;

/* Packet Status Ring Descriptors
 *
 * Word 0:
 *
 * top 16 bits are from the Alcatel Status Word as क्रमागतerated in
 * PE-MCXMAC Data Sheet IPD DS54 0210-1 (also IPD-DS80 0205-2)
 *
 * 0: hp			hash pass
 * 1: ipa			IP checksum assist
 * 2: ipp			IP checksum pass
 * 3: tcpa			TCP checksum assist
 * 4: tcpp			TCP checksum pass
 * 5: wol			WOL Event
 * 6: rxmac_error		RXMAC Error Indicator
 * 7: drop			Drop packet
 * 8: ft			Frame Truncated
 * 9: jp			Jumbo Packet
 * 10: vp			VLAN Packet
 * 11-15: unused
 * 16: asw_prev_pkt_dropped	e.g. IFG too small on previous
 * 17: asw_RX_DV_event		लघु receive event detected
 * 18: asw_false_carrier_event	bad carrier since last good packet
 * 19: asw_code_err		one or more nibbles संकेतled as errors
 * 20: asw_CRC_err		CRC error
 * 21: asw_len_chk_err		frame length field incorrect
 * 22: asw_too_दीर्घ		frame length > 1518 bytes
 * 23: asw_OK			valid CRC + no code error
 * 24: asw_multicast		has a multicast address
 * 25: asw_broadcast		has a broadcast address
 * 26: asw_dribble_nibble	spurious bits after EOP
 * 27: asw_control_frame	is a control frame
 * 28: asw_छोड़ो_frame		is a छोड़ो frame
 * 29: asw_unsupported_op	unsupported OP code
 * 30: asw_VLAN_tag		VLAN tag detected
 * 31: asw_दीर्घ_evt		Rx दीर्घ event
 *
 * Word 1:
 * 0-15: length			length in bytes
 * 16-25: bi			Buffer Index
 * 26-27: ri			Ring Index
 * 28-31: reserved
 */
काष्ठा pkt_stat_desc अणु
	u32 word0;
	u32 word1;
पूर्ण;

/* Typedefs क्रम the RX DMA status word */

/* rx status word 0 holds part of the status bits of the Rx DMA engine
 * that get copied out to memory by the ET-1310.  Word 0 is a 32 bit word
 * which contains the Free Buffer ring 0 and 1 available offset.
 *
 * bit 0-9 FBR1 offset
 * bit 10 Wrap flag क्रम FBR1
 * bit 16-25 FBR0 offset
 * bit 26 Wrap flag क्रम FBR0
 */

/* RXSTAT_WORD1_t काष्ठाure holds part of the status bits of the Rx DMA engine
 * that get copied out to memory by the ET-1310.  Word 3 is a 32 bit word
 * which contains the Packet Status Ring available offset.
 *
 * bit 0-15 reserved
 * bit 16-27 PSRoffset
 * bit 28 PSRwrap
 * bit 29-31 unused
 */

/* काष्ठा rx_status_block is a काष्ठाure representing the status of the Rx
 * DMA engine it sits in मुक्त memory, and is poपूर्णांकed to by 0x101c / 0x1020
 */
काष्ठा rx_status_block अणु
	u32 word0;
	u32 word1;
पूर्ण;

/* Structure क्रम look-up table holding मुक्त buffer ring poपूर्णांकers, addresses
 * and state.
 */
काष्ठा fbr_lookup अणु
	व्योम		*virt[MAX_DESC_PER_RING_RX];
	u32		 bus_high[MAX_DESC_PER_RING_RX];
	u32		 bus_low[MAX_DESC_PER_RING_RX];
	व्योम		*ring_virtaddr;
	dma_addr_t	 ring_physaddr;
	व्योम		*mem_virtaddrs[MAX_DESC_PER_RING_RX / FBR_CHUNKS];
	dma_addr_t	 mem_physaddrs[MAX_DESC_PER_RING_RX / FBR_CHUNKS];
	u32		 local_full;
	u32		 num_entries;
	dma_addr_t	 buffsize;
पूर्ण;

/* काष्ठा rx_ring is the काष्ठाure representing the adaptor's local
 * reference(s) to the rings
 */
काष्ठा rx_ring अणु
	काष्ठा fbr_lookup *fbr[NUM_FBRS];
	व्योम *ps_ring_virtaddr;
	dma_addr_t ps_ring_physaddr;
	u32 local_psr_full;
	u32 psr_entries;

	काष्ठा rx_status_block *rx_status_block;
	dma_addr_t rx_status_bus;

	काष्ठा list_head recv_list;
	u32 num_पढ़ोy_recv;

	u32 num_rfd;

	bool unfinished_receives;
पूर्ण;

/* TX defines */
/* word 2 of the control bits in the Tx Descriptor ring क्रम the ET-1310
 *
 * 0-15: length of packet
 * 16-27: VLAN tag
 * 28: VLAN CFI
 * 29-31: VLAN priority
 *
 * word 3 of the control bits in the Tx Descriptor ring क्रम the ET-1310
 *
 * 0: last packet in the sequence
 * 1: first packet in the sequence
 * 2: पूर्णांकerrupt the processor when this pkt sent
 * 3: Control word - no packet data
 * 4: Issue half-duplex backpressure : XON/XOFF
 * 5: send छोड़ो frame
 * 6: Tx frame has error
 * 7: append CRC
 * 8: MAC override
 * 9: pad packet
 * 10: Packet is a Huge packet
 * 11: append VLAN tag
 * 12: IP checksum assist
 * 13: TCP checksum assist
 * 14: UDP checksum assist
 */
#घोषणा TXDESC_FLAG_LASTPKT		0x0001
#घोषणा TXDESC_FLAG_FIRSTPKT		0x0002
#घोषणा TXDESC_FLAG_INTPROC		0x0004

/* काष्ठा tx_desc represents each descriptor on the ring */
काष्ठा tx_desc अणु
	u32 addr_hi;
	u32 addr_lo;
	u32 len_vlan;	/* control words how to xmit the */
	u32 flags;	/* data (detailed above) */
पूर्ण;

/* The status of the Tx DMA engine it sits in मुक्त memory, and is poपूर्णांकed to
 * by 0x101c / 0x1020. This is a DMA10 type
 */

/* TCB (Transmit Control Block: Host Side) */
काष्ठा tcb अणु
	काष्ठा tcb *next;	/* Next entry in ring */
	u32 count;		/* Used to spot stuck/lost packets */
	u32 stale;		/* Used to spot stuck/lost packets */
	काष्ठा sk_buff *skb;	/* Network skb we are tied to */
	u32 index;		/* Ring indexes */
	u32 index_start;
पूर्ण;

/* Structure representing our local reference(s) to the ring */
काष्ठा tx_ring अणु
	/* TCB (Transmit Control Block) memory and lists */
	काष्ठा tcb *tcb_ring;

	/* List of TCBs that are पढ़ोy to be used */
	काष्ठा tcb *tcb_qhead;
	काष्ठा tcb *tcb_qtail;

	/* list of TCBs that are currently being sent. */
	काष्ठा tcb *send_head;
	काष्ठा tcb *send_tail;
	पूर्णांक used;

	/* The actual descriptor ring */
	काष्ठा tx_desc *tx_desc_ring;
	dma_addr_t tx_desc_ring_pa;

	/* send_idx indicates where we last wrote to in the descriptor ring. */
	u32 send_idx;

	/* The location of the ग_लिखो-back status block */
	u32 *tx_status;
	dma_addr_t tx_status_pa;

	/* Packets since the last IRQ: used क्रम पूर्णांकerrupt coalescing */
	पूर्णांक since_irq;
पूर्ण;

/* Do not change these values: अगर changed, then change also in respective
 * TXdma and Rxdma engines
 */
#घोषणा NUM_DESC_PER_RING_TX         512    /* TX Do not change these values */
#घोषणा NUM_TCB                      64

/* These values are all superseded by registry entries to facilitate tuning.
 * Once the desired perक्रमmance has been achieved, the optimal registry values
 * should be re-populated to these #घोषणाs:
 */
#घोषणा TX_ERROR_PERIOD             1000

#घोषणा LO_MARK_PERCENT_FOR_PSR     15
#घोषणा LO_MARK_PERCENT_FOR_RX      15

/* RFD (Receive Frame Descriptor) */
काष्ठा rfd अणु
	काष्ठा list_head list_node;
	काष्ठा sk_buff *skb;
	u32 len;	/* total size of receive frame */
	u16 bufferindex;
	u8 ringindex;
पूर्ण;

/* Flow Control */
#घोषणा FLOW_BOTH	0
#घोषणा FLOW_TXONLY	1
#घोषणा FLOW_RXONLY	2
#घोषणा FLOW_NONE	3

/* Struct to define some device statistics */
काष्ठा ce_stats अणु
	u32		multicast_pkts_rcvd;
	u32		rcvd_pkts_dropped;

	u32		tx_underflows;
	u32		tx_collisions;
	u32		tx_excessive_collisions;
	u32		tx_first_collisions;
	u32		tx_late_collisions;
	u32		tx_max_pkt_errs;
	u32		tx_deferred;

	u32		rx_overflows;
	u32		rx_length_errs;
	u32		rx_align_errs;
	u32		rx_crc_errs;
	u32		rx_code_violations;
	u32		rx_other_errs;

	u32		पूर्णांकerrupt_status;
पूर्ण;

/* The निजी adapter काष्ठाure */
काष्ठा et131x_adapter अणु
	काष्ठा net_device *netdev;
	काष्ठा pci_dev *pdev;
	काष्ठा mii_bus *mii_bus;
	काष्ठा napi_काष्ठा napi;

	/* Flags that indicate current state of the adapter */
	u32 flags;

	/* local link state, to determine अगर a state change has occurred */
	पूर्णांक link;

	/* Configuration  */
	u8 rom_addr[ETH_ALEN];
	u8 addr[ETH_ALEN];
	bool has_eeprom;
	u8 eeprom_data[2];

	spinlock_t tcb_send_qlock; /* protects the tx_ring send tcb list */
	spinlock_t tcb_पढ़ोy_qlock; /* protects the tx_ring पढ़ोy tcb list */
	spinlock_t rcv_lock; /* protects the rx_ring receive list */

	/* Packet Filter and look ahead size */
	u32 packet_filter;

	/* multicast list */
	u32 multicast_addr_count;
	u8 multicast_list[NIC_MAX_MCAST_LIST][ETH_ALEN];

	/* Poपूर्णांकer to the device's PCI रेजिस्टर space */
	काष्ठा address_map __iomem *regs;

	/* Registry parameters */
	u8 wanted_flow;		/* Flow we want क्रम 802.3x flow control */
	u32 registry_jumbo_packet;	/* Max supported ethernet packet size */

	/* Derived from the registry: */
	u8 flow;		/* flow control validated by the far-end */

	/* Minimize init-समय */
	काष्ठा समयr_list error_समयr;

	/* variable putting the phy पूर्णांकo coma mode when boot up with no cable
	 * plugged in after 5 seconds
	 */
	u8 boot_coma;

	/* Tx Memory Variables */
	काष्ठा tx_ring tx_ring;

	/* Rx Memory Variables */
	काष्ठा rx_ring rx_ring;

	काष्ठा ce_stats stats;
पूर्ण;

अटल पूर्णांक eeprom_रुको_पढ़ोy(काष्ठा pci_dev *pdev, u32 *status)
अणु
	u32 reg;
	पूर्णांक i;

	/* 1. Check LBCIF Status Register क्रम bits 6 & 3:2 all equal to 0 and
	 *    bits 7,1:0 both equal to 1, at least once after reset.
	 *    Subsequent operations need only to check that bits 1:0 are equal
	 *    to 1 prior to starting a single byte पढ़ो/ग_लिखो
	 */
	क्रम (i = 0; i < MAX_NUM_REGISTER_POLLS; i++) अणु
		अगर (pci_पढ़ो_config_dword(pdev, LBCIF_DWORD1_GROUP, &reg))
			वापस -EIO;

		/* I2C idle and Phy Queue Avail both true */
		अगर ((reg & 0x3000) == 0x3000) अणु
			अगर (status)
				*status = reg;
			वापस reg & 0xFF;
		पूर्ण
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक eeprom_ग_लिखो(काष्ठा et131x_adapter *adapter, u32 addr, u8 data)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक index = 0;
	पूर्णांक retries;
	पूर्णांक err = 0;
	पूर्णांक ग_लिखोok = 0;
	u32 status;
	u32 val = 0;

	/* For an EEPROM, an I2C single byte ग_लिखो is defined as a START
	 * condition followed by the device address, EEPROM address, one byte
	 * of data and a STOP condition.  The STOP condition will trigger the
	 * EEPROM's पूर्णांकernally समयd ग_लिखो cycle to the nonअस्थिर memory.
	 * All inमाला_दो are disabled during this ग_लिखो cycle and the EEPROM will
	 * not respond to any access until the पूर्णांकernal ग_लिखो is complete.
	 */
	err = eeprom_रुको_पढ़ोy(pdev, शून्य);
	अगर (err < 0)
		वापस err;

	 /* 2. Write to the LBCIF Control Register:  bit 7=1, bit 6=1, bit 3=0,
	  *    and bits 1:0 both =0.  Bit 5 should be set according to the
	  *    type of EEPROM being accessed (1=two byte addressing, 0=one
	  *    byte addressing).
	  */
	अगर (pci_ग_लिखो_config_byte(pdev, LBCIF_CONTROL_REGISTER,
				  LBCIF_CONTROL_LBCIF_ENABLE |
					LBCIF_CONTROL_I2C_WRITE))
		वापस -EIO;

	/* Prepare EEPROM address क्रम Step 3 */
	क्रम (retries = 0; retries < MAX_NUM_WRITE_RETRIES; retries++) अणु
		अगर (pci_ग_लिखो_config_dword(pdev, LBCIF_ADDRESS_REGISTER, addr))
			अवरोध;
		/* Write the data to the LBCIF Data Register (the I2C ग_लिखो
		 * will begin).
		 */
		अगर (pci_ग_लिखो_config_byte(pdev, LBCIF_DATA_REGISTER, data))
			अवरोध;
		/* Monitor bit 1:0 of the LBCIF Status Register.  When bits
		 * 1:0 are both equal to 1, the I2C ग_लिखो has completed and the
		 * पूर्णांकernal ग_लिखो cycle of the EEPROM is about to start.
		 * (bits 1:0 = 01 is a legal state जबतक रुकोing from both
		 * equal to 1, but bits 1:0 = 10 is invalid and implies that
		 * something is broken).
		 */
		err = eeprom_रुको_पढ़ोy(pdev, &status);
		अगर (err < 0)
			वापस 0;

		/* Check bit 3 of the LBCIF Status Register.  If  equal to 1,
		 * an error has occurred.Don't अवरोध here अगर we are revision
		 * 1, this is so we करो a blind ग_लिखो क्रम load bug.
		 */
		अगर ((status & LBCIF_STATUS_GENERAL_ERROR) &&
		    adapter->pdev->revision == 0)
			अवरोध;

		/* Check bit 2 of the LBCIF Status Register.  If equal to 1 an
		 * ACK error has occurred on the address phase of the ग_लिखो.
		 * This could be due to an actual hardware failure or the
		 * EEPROM may still be in its पूर्णांकernal ग_लिखो cycle from a
		 * previous ग_लिखो. This ग_लिखो operation was ignored and must be
		  *repeated later.
		 */
		अगर (status & LBCIF_STATUS_ACK_ERROR) अणु
			/* This could be due to an actual hardware failure
			 * or the EEPROM may still be in its पूर्णांकernal ग_लिखो
			 * cycle from a previous ग_लिखो. This ग_लिखो operation
			 * was ignored and must be repeated later.
			 */
			udelay(10);
			जारी;
		पूर्ण

		ग_लिखोok = 1;
		अवरोध;
	पूर्ण

	udelay(10);

	जबतक (1) अणु
		अगर (pci_ग_लिखो_config_byte(pdev, LBCIF_CONTROL_REGISTER,
					  LBCIF_CONTROL_LBCIF_ENABLE))
			ग_लिखोok = 0;

		/* Do पढ़ो until पूर्णांकernal ACK_ERROR goes away meaning ग_लिखो
		 * completed
		 */
		करो अणु
			pci_ग_लिखो_config_dword(pdev,
					       LBCIF_ADDRESS_REGISTER,
					       addr);
			करो अणु
				pci_पढ़ो_config_dword(pdev,
						      LBCIF_DATA_REGISTER,
						      &val);
			पूर्ण जबतक ((val & 0x00010000) == 0);
		पूर्ण जबतक (val & 0x00040000);

		अगर ((val & 0xFF00) != 0xC000 || index == 10000)
			अवरोध;
		index++;
	पूर्ण
	वापस ग_लिखोok ? 0 : -EIO;
पूर्ण

अटल पूर्णांक eeprom_पढ़ो(काष्ठा et131x_adapter *adapter, u32 addr, u8 *pdata)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	पूर्णांक err;
	u32 status;

	/* A single byte पढ़ो is similar to the single byte ग_लिखो, with the
	 * exception of the data flow:
	 */
	err = eeprom_रुको_पढ़ोy(pdev, शून्य);
	अगर (err < 0)
		वापस err;
	/* Write to the LBCIF Control Register:  bit 7=1, bit 6=0, bit 3=0,
	 * and bits 1:0 both =0.  Bit 5 should be set according to the type
	 * of EEPROM being accessed (1=two byte addressing, 0=one byte
	 * addressing).
	 */
	अगर (pci_ग_लिखो_config_byte(pdev, LBCIF_CONTROL_REGISTER,
				  LBCIF_CONTROL_LBCIF_ENABLE))
		वापस -EIO;
	/* Write the address to the LBCIF Address Register (I2C पढ़ो will
	 * begin).
	 */
	अगर (pci_ग_लिखो_config_dword(pdev, LBCIF_ADDRESS_REGISTER, addr))
		वापस -EIO;
	/* Monitor bit 0 of the LBCIF Status Register.  When = 1, I2C पढ़ो
	 * is complete. (अगर bit 1 =1 and bit 0 stays = 0, a hardware failure
	 * has occurred).
	 */
	err = eeprom_रुको_पढ़ोy(pdev, &status);
	अगर (err < 0)
		वापस err;
	/* Regardless of error status, पढ़ो data byte from LBCIF Data
	 * Register.
	 */
	*pdata = err;

	वापस (status & LBCIF_STATUS_ACK_ERROR) ? -EIO : 0;
पूर्ण

अटल पूर्णांक et131x_init_eeprom(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा pci_dev *pdev = adapter->pdev;
	u8 eestatus;

	pci_पढ़ो_config_byte(pdev, ET1310_PCI_EEPROM_STATUS, &eestatus);

	/* THIS IS A WORKAROUND:
	 * I need to call this function twice to get my card in a
	 * LG M1 Express Dual running. I tried also a msleep beक्रमe this
	 * function, because I thought there could be some समय conditions
	 * but it didn't work. Call the whole function twice also work.
	 */
	अगर (pci_पढ़ो_config_byte(pdev, ET1310_PCI_EEPROM_STATUS, &eestatus)) अणु
		dev_err(&pdev->dev,
			"Could not read PCI config space for EEPROM Status\n");
		वापस -EIO;
	पूर्ण

	/* Determine अगर the error(s) we care about are present. If they are
	 * present we need to fail.
	 */
	अगर (eestatus & 0x4C) अणु
		पूर्णांक ग_लिखो_failed = 0;

		अगर (pdev->revision == 0x01) अणु
			पूर्णांक	i;
			अटल स्थिर u8 eedata[4] = अणु 0xFE, 0x13, 0x10, 0xFF पूर्ण;

			/* Re-ग_लिखो the first 4 bytes अगर we have an eeprom
			 * present and the revision id is 1, this fixes the
			 * corruption seen with 1310 B Silicon
			 */
			क्रम (i = 0; i < 3; i++)
				अगर (eeprom_ग_लिखो(adapter, i, eedata[i]) < 0)
					ग_लिखो_failed = 1;
		पूर्ण
		अगर (pdev->revision  != 0x01 || ग_लिखो_failed) अणु
			dev_err(&pdev->dev,
				"Fatal EEPROM Status Error - 0x%04x\n",
				eestatus);

			/* This error could mean that there was an error
			 * पढ़ोing the eeprom or that the eeprom करोesn't exist.
			 * We will treat each हाल the same and not try to
			 * gather additional inक्रमmation that normally would
			 * come from the eeprom, like MAC Address
			 */
			adapter->has_eeprom = false;
			वापस -EIO;
		पूर्ण
	पूर्ण
	adapter->has_eeprom = true;

	/* Read the EEPROM क्रम inक्रमmation regarding LED behavior. Refer to
	 * et131x_xcvr_init() क्रम its use.
	 */
	eeprom_पढ़ो(adapter, 0x70, &adapter->eeprom_data[0]);
	eeprom_पढ़ो(adapter, 0x71, &adapter->eeprom_data[1]);

	अगर (adapter->eeprom_data[0] != 0xcd)
		/* Disable all optional features */
		adapter->eeprom_data[1] = 0x00;

	वापस 0;
पूर्ण

अटल व्योम et131x_rx_dma_enable(काष्ठा et131x_adapter *adapter)
अणु
	/* Setup the receive dma configuration रेजिस्टर क्रम normal operation */
	u32 csr =  ET_RXDMA_CSR_FBR1_ENABLE;
	काष्ठा rx_ring *rx_ring = &adapter->rx_ring;

	अगर (rx_ring->fbr[1]->buffsize == 4096)
		csr |= ET_RXDMA_CSR_FBR1_SIZE_LO;
	अन्यथा अगर (rx_ring->fbr[1]->buffsize == 8192)
		csr |= ET_RXDMA_CSR_FBR1_SIZE_HI;
	अन्यथा अगर (rx_ring->fbr[1]->buffsize == 16384)
		csr |= ET_RXDMA_CSR_FBR1_SIZE_LO | ET_RXDMA_CSR_FBR1_SIZE_HI;

	csr |= ET_RXDMA_CSR_FBR0_ENABLE;
	अगर (rx_ring->fbr[0]->buffsize == 256)
		csr |= ET_RXDMA_CSR_FBR0_SIZE_LO;
	अन्यथा अगर (rx_ring->fbr[0]->buffsize == 512)
		csr |= ET_RXDMA_CSR_FBR0_SIZE_HI;
	अन्यथा अगर (rx_ring->fbr[0]->buffsize == 1024)
		csr |= ET_RXDMA_CSR_FBR0_SIZE_LO | ET_RXDMA_CSR_FBR0_SIZE_HI;
	ग_लिखोl(csr, &adapter->regs->rxdma.csr);

	csr = पढ़ोl(&adapter->regs->rxdma.csr);
	अगर (csr & ET_RXDMA_CSR_HALT_STATUS) अणु
		udelay(5);
		csr = पढ़ोl(&adapter->regs->rxdma.csr);
		अगर (csr & ET_RXDMA_CSR_HALT_STATUS) अणु
			dev_err(&adapter->pdev->dev,
				"RX Dma failed to exit halt state. CSR 0x%08x\n",
				csr);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम et131x_rx_dma_disable(काष्ठा et131x_adapter *adapter)
अणु
	u32 csr;
	/* Setup the receive dma configuration रेजिस्टर */
	ग_लिखोl(ET_RXDMA_CSR_HALT | ET_RXDMA_CSR_FBR1_ENABLE,
	       &adapter->regs->rxdma.csr);
	csr = पढ़ोl(&adapter->regs->rxdma.csr);
	अगर (!(csr & ET_RXDMA_CSR_HALT_STATUS)) अणु
		udelay(5);
		csr = पढ़ोl(&adapter->regs->rxdma.csr);
		अगर (!(csr & ET_RXDMA_CSR_HALT_STATUS))
			dev_err(&adapter->pdev->dev,
				"RX Dma failed to enter halt state. CSR 0x%08x\n",
				csr);
	पूर्ण
पूर्ण

अटल व्योम et131x_tx_dma_enable(काष्ठा et131x_adapter *adapter)
अणु
	/* Setup the transmit dma configuration रेजिस्टर क्रम normal
	 * operation
	 */
	ग_लिखोl(ET_TXDMA_SNGL_EPKT | (PARM_DMA_CACHE_DEF << ET_TXDMA_CACHE_SHIFT),
	       &adapter->regs->txdma.csr);
पूर्ण

अटल अंतरभूत व्योम add_10bit(u32 *v, पूर्णांक n)
अणु
	*v = INDEX10(*v + n) | (*v & ET_DMA10_WRAP);
पूर्ण

अटल अंतरभूत व्योम add_12bit(u32 *v, पूर्णांक n)
अणु
	*v = INDEX12(*v + n) | (*v & ET_DMA12_WRAP);
पूर्ण

अटल व्योम et1310_config_mac_regs1(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा mac_regs __iomem *macregs = &adapter->regs->mac;
	u32 station1;
	u32 station2;
	u32 ipg;

	/* First we need to reset everything.  Write to MAC configuration
	 * रेजिस्टर 1 to perक्रमm reset.
	 */
	ग_लिखोl(ET_MAC_CFG1_SOFT_RESET | ET_MAC_CFG1_SIM_RESET  |
	       ET_MAC_CFG1_RESET_RXMC | ET_MAC_CFG1_RESET_TXMC |
	       ET_MAC_CFG1_RESET_RXFUNC | ET_MAC_CFG1_RESET_TXFUNC,
	       &macregs->cfg1);

	/* Next lets configure the MAC Inter-packet gap रेजिस्टर */
	ipg = 0x38005860;		/* IPG1 0x38 IPG2 0x58 B2B 0x60 */
	ipg |= 0x50 << 8;		/* अगरg enक्रमce 0x50 */
	ग_लिखोl(ipg, &macregs->ipg);

	/* Next lets configure the MAC Half Duplex रेजिस्टर */
	/* BEB trunc 0xA, Ex Defer, Rexmit 0xF Coll 0x37 */
	ग_लिखोl(0x00A1F037, &macregs->hfdp);

	/* Next lets configure the MAC Interface Control रेजिस्टर */
	ग_लिखोl(0, &macregs->अगर_ctrl);

	ग_लिखोl(ET_MAC_MIIMGMT_CLK_RST, &macregs->mii_mgmt_cfg);

	/* Next lets configure the MAC Station Address रेजिस्टर.  These
	 * values are पढ़ो from the EEPROM during initialization and stored
	 * in the adapter काष्ठाure.  We ग_लिखो what is stored in the adapter
	 * काष्ठाure to the MAC Station Address रेजिस्टरs high and low.  This
	 * station address is used क्रम generating and checking छोड़ो control
	 * packets.
	 */
	station2 = (adapter->addr[1] << ET_MAC_STATION_ADDR2_OC2_SHIFT) |
		   (adapter->addr[0] << ET_MAC_STATION_ADDR2_OC1_SHIFT);
	station1 = (adapter->addr[5] << ET_MAC_STATION_ADDR1_OC6_SHIFT) |
		   (adapter->addr[4] << ET_MAC_STATION_ADDR1_OC5_SHIFT) |
		   (adapter->addr[3] << ET_MAC_STATION_ADDR1_OC4_SHIFT) |
		    adapter->addr[2];
	ग_लिखोl(station1, &macregs->station_addr_1);
	ग_लिखोl(station2, &macregs->station_addr_2);

	/* Max ethernet packet in bytes that will be passed by the mac without
	 * being truncated.  Allow the MAC to pass 4 more than our max packet
	 * size.  This is 4 क्रम the Ethernet CRC.
	 *
	 * Packets larger than (registry_jumbo_packet) that करो not contain a
	 * VLAN ID will be dropped by the Rx function.
	 */
	ग_लिखोl(adapter->registry_jumbo_packet + 4, &macregs->max_fm_len);

	/* clear out MAC config reset */
	ग_लिखोl(0, &macregs->cfg1);
पूर्ण

अटल व्योम et1310_config_mac_regs2(काष्ठा et131x_adapter *adapter)
अणु
	पूर्णांक32_t delay = 0;
	काष्ठा mac_regs __iomem *mac = &adapter->regs->mac;
	काष्ठा phy_device *phydev = adapter->netdev->phydev;
	u32 cfg1;
	u32 cfg2;
	u32 अगरctrl;
	u32 ctl;

	ctl = पढ़ोl(&adapter->regs->txmac.ctl);
	cfg1 = पढ़ोl(&mac->cfg1);
	cfg2 = पढ़ोl(&mac->cfg2);
	अगरctrl = पढ़ोl(&mac->अगर_ctrl);

	/* Set up the अगर mode bits */
	cfg2 &= ~ET_MAC_CFG2_IFMODE_MASK;
	अगर (phydev->speed == SPEED_1000) अणु
		cfg2 |= ET_MAC_CFG2_IFMODE_1000;
		अगरctrl &= ~ET_MAC_IFCTRL_PHYMODE;
	पूर्ण अन्यथा अणु
		cfg2 |= ET_MAC_CFG2_IFMODE_100;
		अगरctrl |= ET_MAC_IFCTRL_PHYMODE;
	पूर्ण

	cfg1 |= ET_MAC_CFG1_RX_ENABLE | ET_MAC_CFG1_TX_ENABLE |
							ET_MAC_CFG1_TX_FLOW;

	cfg1 &= ~(ET_MAC_CFG1_LOOPBACK | ET_MAC_CFG1_RX_FLOW);
	अगर (adapter->flow == FLOW_RXONLY || adapter->flow == FLOW_BOTH)
		cfg1 |= ET_MAC_CFG1_RX_FLOW;
	ग_लिखोl(cfg1, &mac->cfg1);

	/* Now we need to initialize the MAC Configuration 2 रेजिस्टर */
	/* preamble 7, check length, huge frame off, pad crc, crc enable
	 * full duplex off
	 */
	cfg2 |= 0x7 << ET_MAC_CFG2_PREAMBLE_SHIFT;
	cfg2 |= ET_MAC_CFG2_IFMODE_LEN_CHECK;
	cfg2 |= ET_MAC_CFG2_IFMODE_PAD_CRC;
	cfg2 |=	ET_MAC_CFG2_IFMODE_CRC_ENABLE;
	cfg2 &= ~ET_MAC_CFG2_IFMODE_HUGE_FRAME;
	cfg2 &= ~ET_MAC_CFG2_IFMODE_FULL_DPLX;

	अगर (phydev->duplex == DUPLEX_FULL)
		cfg2 |= ET_MAC_CFG2_IFMODE_FULL_DPLX;

	अगरctrl &= ~ET_MAC_IFCTRL_GHDMODE;
	अगर (phydev->duplex == DUPLEX_HALF)
		अगरctrl |= ET_MAC_IFCTRL_GHDMODE;

	ग_लिखोl(अगरctrl, &mac->अगर_ctrl);
	ग_लिखोl(cfg2, &mac->cfg2);

	करो अणु
		udelay(10);
		delay++;
		cfg1 = पढ़ोl(&mac->cfg1);
	पूर्ण जबतक ((cfg1 & ET_MAC_CFG1_WAIT) != ET_MAC_CFG1_WAIT && delay < 100);

	अगर (delay == 100) अणु
		dev_warn(&adapter->pdev->dev,
			 "Syncd bits did not respond correctly cfg1 word 0x%08x\n",
			 cfg1);
	पूर्ण

	ctl |= ET_TX_CTRL_TXMAC_ENABLE | ET_TX_CTRL_FC_DISABLE;
	ग_लिखोl(ctl, &adapter->regs->txmac.ctl);

	अगर (adapter->flags & FMP_ADAPTER_LOWER_POWER) अणु
		et131x_rx_dma_enable(adapter);
		et131x_tx_dma_enable(adapter);
	पूर्ण
पूर्ण

अटल पूर्णांक et1310_in_phy_coma(काष्ठा et131x_adapter *adapter)
अणु
	u32 pmcsr = पढ़ोl(&adapter->regs->global.pm_csr);

	वापस ET_PM_PHY_SW_COMA & pmcsr ? 1 : 0;
पूर्ण

अटल व्योम et1310_setup_device_क्रम_multicast(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा rxmac_regs __iomem *rxmac = &adapter->regs->rxmac;
	u32 hash1 = 0;
	u32 hash2 = 0;
	u32 hash3 = 0;
	u32 hash4 = 0;

	/* If ET131X_PACKET_TYPE_MULTICAST is specअगरied, then we provision
	 * the multi-cast LIST.  If it is NOT specअगरied, (and "ALL" is not
	 * specअगरied) then we should pass NO multi-cast addresses to the
	 * driver.
	 */
	अगर (adapter->packet_filter & ET131X_PACKET_TYPE_MULTICAST) अणु
		पूर्णांक i;

		/* Loop through our multicast array and set up the device */
		क्रम (i = 0; i < adapter->multicast_addr_count; i++) अणु
			u32 result;

			result = ether_crc(6, adapter->multicast_list[i]);

			result = (result & 0x3F800000) >> 23;

			अगर (result < 32) अणु
				hash1 |= (1 << result);
			पूर्ण अन्यथा अगर ((31 < result) && (result < 64)) अणु
				result -= 32;
				hash2 |= (1 << result);
			पूर्ण अन्यथा अगर ((63 < result) && (result < 96)) अणु
				result -= 64;
				hash3 |= (1 << result);
			पूर्ण अन्यथा अणु
				result -= 96;
				hash4 |= (1 << result);
			पूर्ण
		पूर्ण
	पूर्ण

	/* Write out the new hash to the device */
	अगर (!et1310_in_phy_coma(adapter)) अणु
		ग_लिखोl(hash1, &rxmac->multi_hash1);
		ग_लिखोl(hash2, &rxmac->multi_hash2);
		ग_लिखोl(hash3, &rxmac->multi_hash3);
		ग_लिखोl(hash4, &rxmac->multi_hash4);
	पूर्ण
पूर्ण

अटल व्योम et1310_setup_device_क्रम_unicast(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा rxmac_regs __iomem *rxmac = &adapter->regs->rxmac;
	u32 uni_pf1;
	u32 uni_pf2;
	u32 uni_pf3;

	/* Set up unicast packet filter reg 3 to be the first two octets of
	 * the MAC address क्रम both address
	 *
	 * Set up unicast packet filter reg 2 to be the octets 2 - 5 of the
	 * MAC address क्रम second address
	 *
	 * Set up unicast packet filter reg 3 to be the octets 2 - 5 of the
	 * MAC address क्रम first address
	 */
	uni_pf3 = (adapter->addr[0] << ET_RX_UNI_PF_ADDR2_1_SHIFT) |
		  (adapter->addr[1] << ET_RX_UNI_PF_ADDR2_2_SHIFT) |
		  (adapter->addr[0] << ET_RX_UNI_PF_ADDR1_1_SHIFT) |
		   adapter->addr[1];

	uni_pf2 = (adapter->addr[2] << ET_RX_UNI_PF_ADDR2_3_SHIFT) |
		  (adapter->addr[3] << ET_RX_UNI_PF_ADDR2_4_SHIFT) |
		  (adapter->addr[4] << ET_RX_UNI_PF_ADDR2_5_SHIFT) |
		   adapter->addr[5];

	uni_pf1 = (adapter->addr[2] << ET_RX_UNI_PF_ADDR1_3_SHIFT) |
		  (adapter->addr[3] << ET_RX_UNI_PF_ADDR1_4_SHIFT) |
		  (adapter->addr[4] << ET_RX_UNI_PF_ADDR1_5_SHIFT) |
		   adapter->addr[5];

	अगर (!et1310_in_phy_coma(adapter)) अणु
		ग_लिखोl(uni_pf1, &rxmac->uni_pf_addr1);
		ग_लिखोl(uni_pf2, &rxmac->uni_pf_addr2);
		ग_लिखोl(uni_pf3, &rxmac->uni_pf_addr3);
	पूर्ण
पूर्ण

अटल व्योम et1310_config_rxmac_regs(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा rxmac_regs __iomem *rxmac = &adapter->regs->rxmac;
	काष्ठा phy_device *phydev = adapter->netdev->phydev;
	u32 sa_lo;
	u32 sa_hi = 0;
	u32 pf_ctrl = 0;
	u32 __iomem *wolw;

	/* Disable the MAC जबतक it is being configured (also disable WOL) */
	ग_लिखोl(0x8, &rxmac->ctrl);

	/* Initialize WOL to disabled. */
	ग_लिखोl(0, &rxmac->crc0);
	ग_लिखोl(0, &rxmac->crc12);
	ग_लिखोl(0, &rxmac->crc34);

	/* We need to set the WOL mask0 - mask4 next.  We initialize it to
	 * its शेष Values of 0x00000000 because there are not WOL masks
	 * as of this समय.
	 */
	क्रम (wolw = &rxmac->mask0_word0; wolw <= &rxmac->mask4_word3; wolw++)
		ग_लिखोl(0, wolw);

	/* Lets setup the WOL Source Address */
	sa_lo = (adapter->addr[2] << ET_RX_WOL_LO_SA3_SHIFT) |
		(adapter->addr[3] << ET_RX_WOL_LO_SA4_SHIFT) |
		(adapter->addr[4] << ET_RX_WOL_LO_SA5_SHIFT) |
		 adapter->addr[5];
	ग_लिखोl(sa_lo, &rxmac->sa_lo);

	sa_hi = (u32)(adapter->addr[0] << ET_RX_WOL_HI_SA1_SHIFT) |
		       adapter->addr[1];
	ग_लिखोl(sa_hi, &rxmac->sa_hi);

	/* Disable all Packet Filtering */
	ग_लिखोl(0, &rxmac->pf_ctrl);

	/* Let's initialize the Unicast Packet filtering address */
	अगर (adapter->packet_filter & ET131X_PACKET_TYPE_सूचीECTED) अणु
		et1310_setup_device_क्रम_unicast(adapter);
		pf_ctrl |= ET_RX_PFCTRL_UNICST_FILTER_ENABLE;
	पूर्ण अन्यथा अणु
		ग_लिखोl(0, &rxmac->uni_pf_addr1);
		ग_लिखोl(0, &rxmac->uni_pf_addr2);
		ग_लिखोl(0, &rxmac->uni_pf_addr3);
	पूर्ण

	/* Let's initialize the Multicast hash */
	अगर (!(adapter->packet_filter & ET131X_PACKET_TYPE_ALL_MULTICAST)) अणु
		pf_ctrl |= ET_RX_PFCTRL_MLTCST_FILTER_ENABLE;
		et1310_setup_device_क्रम_multicast(adapter);
	पूर्ण

	/* Runt packet filtering.  Didn't work in version A silicon. */
	pf_ctrl |= (NIC_MIN_PACKET_SIZE + 4) << ET_RX_PFCTRL_MIN_PKT_SZ_SHIFT;
	pf_ctrl |= ET_RX_PFCTRL_FRAG_FILTER_ENABLE;

	अगर (adapter->registry_jumbo_packet > 8192)
		/* In order to transmit jumbo packets greater than 8k, the
		 * FIFO between RxMAC and RxDMA needs to be reduced in size
		 * to (16k - Jumbo packet size).  In order to implement this,
		 * we must use "cut through" mode in the RxMAC, which chops
		 * packets करोwn पूर्णांकo segments which are (max_size * 16).  In
		 * this हाल we selected 256 bytes, since this is the size of
		 * the PCI-Express TLP's that the 1310 uses.
		 *
		 * seg_en on, fc_en off, size 0x10
		 */
		ग_लिखोl(0x41, &rxmac->mcअगर_ctrl_max_seg);
	अन्यथा
		ग_लिखोl(0, &rxmac->mcअगर_ctrl_max_seg);

	ग_लिखोl(0, &rxmac->mcअगर_water_mark);
	ग_लिखोl(0, &rxmac->mअगर_ctrl);
	ग_लिखोl(0, &rxmac->space_avail);

	/* Initialize the the mअगर_ctrl रेजिस्टर
	 * bit 3:  Receive code error. One or more nibbles were संकेतed as
	 *	   errors  during the reception of the packet.  Clear this
	 *	   bit in Gigabit, set it in 100Mbit.  This was derived
	 *	   experimentally at UNH.
	 * bit 4:  Receive CRC error. The packet's CRC did not match the
	 *	   पूर्णांकernally generated CRC.
	 * bit 5:  Receive length check error. Indicates that frame length
	 *	   field value in the packet करोes not match the actual data
	 *	   byte length and is not a type field.
	 * bit 16: Receive frame truncated.
	 * bit 17: Drop packet enable
	 */
	अगर (phydev && phydev->speed == SPEED_100)
		ग_लिखोl(0x30038, &rxmac->mअगर_ctrl);
	अन्यथा
		ग_लिखोl(0x30030, &rxmac->mअगर_ctrl);

	/* Finally we initialize RxMac to be enabled & WOL disabled.  Packet
	 * filter is always enabled since it is where the runt packets are
	 * supposed to be dropped.  For version A silicon, runt packet
	 * dropping करोesn't work, so it is disabled in the pf_ctrl रेजिस्टर,
	 * but we still leave the packet filter on.
	 */
	ग_लिखोl(pf_ctrl, &rxmac->pf_ctrl);
	ग_लिखोl(ET_RX_CTRL_RXMAC_ENABLE | ET_RX_CTRL_WOL_DISABLE, &rxmac->ctrl);
पूर्ण

अटल व्योम et1310_config_txmac_regs(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा txmac_regs __iomem *txmac = &adapter->regs->txmac;

	/* We need to update the Control Frame Parameters
	 * cfpt - control frame छोड़ो समयr set to 64 (0x40)
	 * cfep - control frame extended छोड़ो समयr set to 0x0
	 */
	अगर (adapter->flow == FLOW_NONE)
		ग_लिखोl(0, &txmac->cf_param);
	अन्यथा
		ग_लिखोl(0x40, &txmac->cf_param);
पूर्ण

अटल व्योम et1310_config_macstat_regs(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा macstat_regs __iomem *macstat = &adapter->regs->macstat;
	u32 __iomem *reg;

	/* initialize all the macstat रेजिस्टरs to zero on the device  */
	क्रम (reg = &macstat->txrx_0_64_byte_frames;
	     reg <= &macstat->carry_reg2; reg++)
		ग_लिखोl(0, reg);

	/* Unmask any counters that we want to track the overflow of.
	 * Initially this will be all counters.  It may become clear later
	 * that we करो not need to track all counters.
	 */
	ग_लिखोl(0xFFFFBE32, &macstat->carry_reg1_mask);
	ग_लिखोl(0xFFFE7E8B, &macstat->carry_reg2_mask);
पूर्ण

अटल पूर्णांक et131x_phy_mii_पढ़ो(काष्ठा et131x_adapter *adapter, u8 addr,
			       u8 reg, u16 *value)
अणु
	काष्ठा mac_regs __iomem *mac = &adapter->regs->mac;
	पूर्णांक status = 0;
	u32 delay = 0;
	u32 mii_addr;
	u32 mii_cmd;
	u32 mii_indicator;

	/* Save a local copy of the रेजिस्टरs we are dealing with so we can
	 * set them back
	 */
	mii_addr = पढ़ोl(&mac->mii_mgmt_addr);
	mii_cmd = पढ़ोl(&mac->mii_mgmt_cmd);

	/* Stop the current operation */
	ग_लिखोl(0, &mac->mii_mgmt_cmd);

	/* Set up the रेजिस्टर we need to पढ़ो from on the correct PHY */
	ग_लिखोl(ET_MAC_MII_ADDR(addr, reg), &mac->mii_mgmt_addr);

	ग_लिखोl(0x1, &mac->mii_mgmt_cmd);

	करो अणु
		udelay(50);
		delay++;
		mii_indicator = पढ़ोl(&mac->mii_mgmt_indicator);
	पूर्ण जबतक ((mii_indicator & ET_MAC_MGMT_WAIT) && delay < 50);

	/* If we hit the max delay, we could not पढ़ो the रेजिस्टर */
	अगर (delay == 50) अणु
		dev_warn(&adapter->pdev->dev,
			 "reg 0x%08x could not be read\n", reg);
		dev_warn(&adapter->pdev->dev, "status is  0x%08x\n",
			 mii_indicator);

		status = -EIO;
		जाओ out;
	पूर्ण

	/* If we hit here we were able to पढ़ो the रेजिस्टर and we need to
	 * वापस the value to the caller
	 */
	*value = पढ़ोl(&mac->mii_mgmt_stat) & ET_MAC_MIIMGMT_STAT_PHYCRTL_MASK;

out:
	/* Stop the पढ़ो operation */
	ग_लिखोl(0, &mac->mii_mgmt_cmd);

	/* set the रेजिस्टरs we touched back to the state at which we entered
	 * this function
	 */
	ग_लिखोl(mii_addr, &mac->mii_mgmt_addr);
	ग_लिखोl(mii_cmd, &mac->mii_mgmt_cmd);

	वापस status;
पूर्ण

अटल पूर्णांक et131x_mii_पढ़ो(काष्ठा et131x_adapter *adapter, u8 reg, u16 *value)
अणु
	काष्ठा phy_device *phydev = adapter->netdev->phydev;

	अगर (!phydev)
		वापस -EIO;

	वापस et131x_phy_mii_पढ़ो(adapter, phydev->mdio.addr, reg, value);
पूर्ण

अटल पूर्णांक et131x_mii_ग_लिखो(काष्ठा et131x_adapter *adapter, u8 addr, u8 reg,
			    u16 value)
अणु
	काष्ठा mac_regs __iomem *mac = &adapter->regs->mac;
	पूर्णांक status = 0;
	u32 delay = 0;
	u32 mii_addr;
	u32 mii_cmd;
	u32 mii_indicator;

	/* Save a local copy of the रेजिस्टरs we are dealing with so we can
	 * set them back
	 */
	mii_addr = पढ़ोl(&mac->mii_mgmt_addr);
	mii_cmd = पढ़ोl(&mac->mii_mgmt_cmd);

	/* Stop the current operation */
	ग_लिखोl(0, &mac->mii_mgmt_cmd);

	/* Set up the रेजिस्टर we need to ग_लिखो to on the correct PHY */
	ग_लिखोl(ET_MAC_MII_ADDR(addr, reg), &mac->mii_mgmt_addr);

	/* Add the value to ग_लिखो to the रेजिस्टरs to the mac */
	ग_लिखोl(value, &mac->mii_mgmt_ctrl);

	करो अणु
		udelay(50);
		delay++;
		mii_indicator = पढ़ोl(&mac->mii_mgmt_indicator);
	पूर्ण जबतक ((mii_indicator & ET_MAC_MGMT_BUSY) && delay < 100);

	/* If we hit the max delay, we could not ग_लिखो the रेजिस्टर */
	अगर (delay == 100) अणु
		u16 पंचांगp;

		dev_warn(&adapter->pdev->dev,
			 "reg 0x%08x could not be written", reg);
		dev_warn(&adapter->pdev->dev, "status is  0x%08x\n",
			 mii_indicator);
		dev_warn(&adapter->pdev->dev, "command is  0x%08x\n",
			 पढ़ोl(&mac->mii_mgmt_cmd));

		et131x_mii_पढ़ो(adapter, reg, &पंचांगp);

		status = -EIO;
	पूर्ण
	/* Stop the ग_लिखो operation */
	ग_लिखोl(0, &mac->mii_mgmt_cmd);

	/* set the रेजिस्टरs we touched back to the state at which we entered
	 * this function
	 */
	ग_लिखोl(mii_addr, &mac->mii_mgmt_addr);
	ग_लिखोl(mii_cmd, &mac->mii_mgmt_cmd);

	वापस status;
पूर्ण

अटल व्योम et1310_phy_पढ़ो_mii_bit(काष्ठा et131x_adapter *adapter,
				    u16 regnum,
				    u16 bitnum,
				    u8 *value)
अणु
	u16 reg;
	u16 mask = 1 << bitnum;

	et131x_mii_पढ़ो(adapter, regnum, &reg);

	*value = (reg & mask) >> bitnum;
पूर्ण

अटल व्योम et1310_config_flow_control(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा phy_device *phydev = adapter->netdev->phydev;

	अगर (phydev->duplex == DUPLEX_HALF) अणु
		adapter->flow = FLOW_NONE;
	पूर्ण अन्यथा अणु
		अक्षर remote_छोड़ो, remote_async_छोड़ो;

		et1310_phy_पढ़ो_mii_bit(adapter, 5, 10, &remote_छोड़ो);
		et1310_phy_पढ़ो_mii_bit(adapter, 5, 11, &remote_async_छोड़ो);

		अगर (remote_छोड़ो && remote_async_छोड़ो) अणु
			adapter->flow = adapter->wanted_flow;
		पूर्ण अन्यथा अगर (remote_छोड़ो && !remote_async_छोड़ो) अणु
			अगर (adapter->wanted_flow == FLOW_BOTH)
				adapter->flow = FLOW_BOTH;
			अन्यथा
				adapter->flow = FLOW_NONE;
		पूर्ण अन्यथा अगर (!remote_छोड़ो && !remote_async_छोड़ो) अणु
			adapter->flow = FLOW_NONE;
		पूर्ण अन्यथा अणु
			अगर (adapter->wanted_flow == FLOW_BOTH)
				adapter->flow = FLOW_RXONLY;
			अन्यथा
				adapter->flow = FLOW_NONE;
		पूर्ण
	पूर्ण
पूर्ण

/* et1310_update_macstat_host_counters - Update local copy of the statistics */
अटल व्योम et1310_update_macstat_host_counters(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा ce_stats *stats = &adapter->stats;
	काष्ठा macstat_regs __iomem *macstat =
		&adapter->regs->macstat;

	stats->tx_collisions	       += पढ़ोl(&macstat->tx_total_collisions);
	stats->tx_first_collisions     += पढ़ोl(&macstat->tx_single_collisions);
	stats->tx_deferred	       += पढ़ोl(&macstat->tx_deferred);
	stats->tx_excessive_collisions +=
				पढ़ोl(&macstat->tx_multiple_collisions);
	stats->tx_late_collisions      += पढ़ोl(&macstat->tx_late_collisions);
	stats->tx_underflows	       += पढ़ोl(&macstat->tx_undersize_frames);
	stats->tx_max_pkt_errs	       += पढ़ोl(&macstat->tx_oversize_frames);

	stats->rx_align_errs        += पढ़ोl(&macstat->rx_align_errs);
	stats->rx_crc_errs          += पढ़ोl(&macstat->rx_code_errs);
	stats->rcvd_pkts_dropped    += पढ़ोl(&macstat->rx_drops);
	stats->rx_overflows         += पढ़ोl(&macstat->rx_oversize_packets);
	stats->rx_code_violations   += पढ़ोl(&macstat->rx_fcs_errs);
	stats->rx_length_errs       += पढ़ोl(&macstat->rx_frame_len_errs);
	stats->rx_other_errs        += पढ़ोl(&macstat->rx_fragment_packets);
पूर्ण

/* et1310_handle_macstat_पूर्णांकerrupt
 *
 * One of the MACSTAT counters has wrapped.  Update the local copy of
 * the statistics held in the adapter काष्ठाure, checking the "wrap"
 * bit क्रम each counter.
 */
अटल व्योम et1310_handle_macstat_पूर्णांकerrupt(काष्ठा et131x_adapter *adapter)
अणु
	u32 carry_reg1;
	u32 carry_reg2;

	/* Read the पूर्णांकerrupt bits from the रेजिस्टर(s).  These are Clear On
	 * Write.
	 */
	carry_reg1 = पढ़ोl(&adapter->regs->macstat.carry_reg1);
	carry_reg2 = पढ़ोl(&adapter->regs->macstat.carry_reg2);

	ग_लिखोl(carry_reg1, &adapter->regs->macstat.carry_reg1);
	ग_लिखोl(carry_reg2, &adapter->regs->macstat.carry_reg2);

	/* We need to करो update the host copy of all the MAC_STAT counters.
	 * For each counter, check it's overflow bit.  If the overflow bit is
	 * set, then increment the host version of the count by one complete
	 * revolution of the counter.  This routine is called when the counter
	 * block indicates that one of the counters has wrapped.
	 */
	अगर (carry_reg1 & (1 << 14))
		adapter->stats.rx_code_violations	+= COUNTER_WRAP_16_BIT;
	अगर (carry_reg1 & (1 << 8))
		adapter->stats.rx_align_errs	+= COUNTER_WRAP_12_BIT;
	अगर (carry_reg1 & (1 << 7))
		adapter->stats.rx_length_errs	+= COUNTER_WRAP_16_BIT;
	अगर (carry_reg1 & (1 << 2))
		adapter->stats.rx_other_errs	+= COUNTER_WRAP_16_BIT;
	अगर (carry_reg1 & (1 << 6))
		adapter->stats.rx_crc_errs	+= COUNTER_WRAP_16_BIT;
	अगर (carry_reg1 & (1 << 3))
		adapter->stats.rx_overflows	+= COUNTER_WRAP_16_BIT;
	अगर (carry_reg1 & (1 << 0))
		adapter->stats.rcvd_pkts_dropped	+= COUNTER_WRAP_16_BIT;
	अगर (carry_reg2 & (1 << 16))
		adapter->stats.tx_max_pkt_errs	+= COUNTER_WRAP_12_BIT;
	अगर (carry_reg2 & (1 << 15))
		adapter->stats.tx_underflows	+= COUNTER_WRAP_12_BIT;
	अगर (carry_reg2 & (1 << 6))
		adapter->stats.tx_first_collisions += COUNTER_WRAP_12_BIT;
	अगर (carry_reg2 & (1 << 8))
		adapter->stats.tx_deferred	+= COUNTER_WRAP_12_BIT;
	अगर (carry_reg2 & (1 << 5))
		adapter->stats.tx_excessive_collisions += COUNTER_WRAP_12_BIT;
	अगर (carry_reg2 & (1 << 4))
		adapter->stats.tx_late_collisions	+= COUNTER_WRAP_12_BIT;
	अगर (carry_reg2 & (1 << 2))
		adapter->stats.tx_collisions	+= COUNTER_WRAP_12_BIT;
पूर्ण

अटल पूर्णांक et131x_mdio_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक phy_addr, पूर्णांक reg)
अणु
	काष्ठा net_device *netdev = bus->priv;
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);
	u16 value;
	पूर्णांक ret;

	ret = et131x_phy_mii_पढ़ो(adapter, phy_addr, reg, &value);

	अगर (ret < 0)
		वापस ret;

	वापस value;
पूर्ण

अटल पूर्णांक et131x_mdio_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक phy_addr,
			     पूर्णांक reg, u16 value)
अणु
	काष्ठा net_device *netdev = bus->priv;
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);

	वापस et131x_mii_ग_लिखो(adapter, phy_addr, reg, value);
पूर्ण

/*	et1310_phy_घातer_चयन	-	PHY घातer control
 *	@adapter: device to control
 *	@करोwn: true क्रम off/false क्रम back on
 *
 *	one hundred, ten, one thousand megs
 *	How would you like to have your LAN accessed
 *	Can't you see that this code processed
 *	Phy घातer, phy घातer..
 */
अटल व्योम et1310_phy_घातer_चयन(काष्ठा et131x_adapter *adapter, bool करोwn)
अणु
	u16 data;
	काष्ठा  phy_device *phydev = adapter->netdev->phydev;

	et131x_mii_पढ़ो(adapter, MII_BMCR, &data);
	data &= ~BMCR_PDOWN;
	अगर (करोwn)
		data |= BMCR_PDOWN;
	et131x_mii_ग_लिखो(adapter, phydev->mdio.addr, MII_BMCR, data);
पूर्ण

/* et131x_xcvr_init - Init the phy अगर we are setting it पूर्णांकo क्रमce mode */
अटल व्योम et131x_xcvr_init(काष्ठा et131x_adapter *adapter)
अणु
	u16 lcr2;
	काष्ठा  phy_device *phydev = adapter->netdev->phydev;

	/* Set the LED behavior such that LED 1 indicates speed (off =
	 * 10Mbits, blink = 100Mbits, on = 1000Mbits) and LED 2 indicates
	 * link and activity (on क्रम link, blink off क्रम activity).
	 *
	 * NOTE: Some customizations have been added here क्रम specअगरic
	 * venकरोrs; The LED behavior is now determined by venकरोr data in the
	 * EEPROM. However, the above description is the शेष.
	 */
	अगर ((adapter->eeprom_data[1] & 0x4) == 0) अणु
		et131x_mii_पढ़ो(adapter, PHY_LED_2, &lcr2);

		lcr2 &= (ET_LED2_LED_100TX | ET_LED2_LED_1000T);
		lcr2 |= (LED_VAL_LINKON_ACTIVE << LED_LINK_SHIFT);

		अगर ((adapter->eeprom_data[1] & 0x8) == 0)
			lcr2 |= (LED_VAL_1000BT_100BTX << LED_TXRX_SHIFT);
		अन्यथा
			lcr2 |= (LED_VAL_LINKON << LED_TXRX_SHIFT);

		et131x_mii_ग_लिखो(adapter, phydev->mdio.addr, PHY_LED_2, lcr2);
	पूर्ण
पूर्ण

/* et131x_configure_global_regs	- configure JAGCore global regs */
अटल व्योम et131x_configure_global_regs(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा global_regs __iomem *regs = &adapter->regs->global;

	ग_लिखोl(0, &regs->rxq_start_addr);
	ग_लिखोl(INTERNAL_MEM_SIZE - 1, &regs->txq_end_addr);

	अगर (adapter->registry_jumbo_packet < 2048) अणु
		/* Tx / RxDMA and Tx/Rx MAC पूर्णांकerfaces have a 1k word
		 * block of RAM that the driver can split between Tx
		 * and Rx as it desires.  Our शेष is to split it
		 * 50/50:
		 */
		ग_लिखोl(PARM_RX_MEM_END_DEF, &regs->rxq_end_addr);
		ग_लिखोl(PARM_RX_MEM_END_DEF + 1, &regs->txq_start_addr);
	पूर्ण अन्यथा अगर (adapter->registry_jumbo_packet < 8192) अणु
		/* For jumbo packets > 2k but < 8k, split 50-50. */
		ग_लिखोl(INTERNAL_MEM_RX_OFFSET, &regs->rxq_end_addr);
		ग_लिखोl(INTERNAL_MEM_RX_OFFSET + 1, &regs->txq_start_addr);
	पूर्ण अन्यथा अणु
		/* 9216 is the only packet size greater than 8k that
		 * is available. The Tx buffer has to be big enough
		 * क्रम one whole packet on the Tx side. We'll make
		 * the Tx 9408, and give the rest to Rx
		 */
		ग_लिखोl(0x01b3, &regs->rxq_end_addr);
		ग_लिखोl(0x01b4, &regs->txq_start_addr);
	पूर्ण

	/* Initialize the loopback रेजिस्टर. Disable all loopbacks. */
	ग_लिखोl(0, &regs->loopback);

	ग_लिखोl(0, &regs->msi_config);

	/* By शेष, disable the watchकरोg समयr.  It will be enabled when
	 * a packet is queued.
	 */
	ग_लिखोl(0, &regs->watchकरोg_समयr);
पूर्ण

/* et131x_config_rx_dma_regs - Start of Rx_DMA init sequence */
अटल व्योम et131x_config_rx_dma_regs(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा rxdma_regs __iomem *rx_dma = &adapter->regs->rxdma;
	काष्ठा rx_ring *rx_local = &adapter->rx_ring;
	काष्ठा fbr_desc *fbr_entry;
	u32 entry;
	u32 psr_num_des;
	अचिन्हित दीर्घ flags;
	u8 id;

	et131x_rx_dma_disable(adapter);

	/* Load the completion ग_लिखोback physical address */
	ग_लिखोl(upper_32_bits(rx_local->rx_status_bus), &rx_dma->dma_wb_base_hi);
	ग_लिखोl(lower_32_bits(rx_local->rx_status_bus), &rx_dma->dma_wb_base_lo);

	स_रखो(rx_local->rx_status_block, 0, माप(काष्ठा rx_status_block));

	/* Set the address and parameters of the packet status ring */
	ग_लिखोl(upper_32_bits(rx_local->ps_ring_physaddr), &rx_dma->psr_base_hi);
	ग_लिखोl(lower_32_bits(rx_local->ps_ring_physaddr), &rx_dma->psr_base_lo);
	ग_लिखोl(rx_local->psr_entries - 1, &rx_dma->psr_num_des);
	ग_लिखोl(0, &rx_dma->psr_full_offset);

	psr_num_des = पढ़ोl(&rx_dma->psr_num_des) & ET_RXDMA_PSR_NUM_DES_MASK;
	ग_लिखोl((psr_num_des * LO_MARK_PERCENT_FOR_PSR) / 100,
	       &rx_dma->psr_min_des);

	spin_lock_irqsave(&adapter->rcv_lock, flags);

	/* These local variables track the PSR in the adapter काष्ठाure */
	rx_local->local_psr_full = 0;

	क्रम (id = 0; id < NUM_FBRS; id++) अणु
		u32 __iomem *num_des;
		u32 __iomem *full_offset;
		u32 __iomem *min_des;
		u32 __iomem *base_hi;
		u32 __iomem *base_lo;
		काष्ठा fbr_lookup *fbr = rx_local->fbr[id];

		अगर (id == 0) अणु
			num_des = &rx_dma->fbr0_num_des;
			full_offset = &rx_dma->fbr0_full_offset;
			min_des = &rx_dma->fbr0_min_des;
			base_hi = &rx_dma->fbr0_base_hi;
			base_lo = &rx_dma->fbr0_base_lo;
		पूर्ण अन्यथा अणु
			num_des = &rx_dma->fbr1_num_des;
			full_offset = &rx_dma->fbr1_full_offset;
			min_des = &rx_dma->fbr1_min_des;
			base_hi = &rx_dma->fbr1_base_hi;
			base_lo = &rx_dma->fbr1_base_lo;
		पूर्ण

		/* Now's the best समय to initialize FBR contents */
		fbr_entry = fbr->ring_virtaddr;
		क्रम (entry = 0; entry < fbr->num_entries; entry++) अणु
			fbr_entry->addr_hi = fbr->bus_high[entry];
			fbr_entry->addr_lo = fbr->bus_low[entry];
			fbr_entry->word2 = entry;
			fbr_entry++;
		पूर्ण

		/* Set the address and parameters of Free buffer ring 1 and 0 */
		ग_लिखोl(upper_32_bits(fbr->ring_physaddr), base_hi);
		ग_लिखोl(lower_32_bits(fbr->ring_physaddr), base_lo);
		ग_लिखोl(fbr->num_entries - 1, num_des);
		ग_लिखोl(ET_DMA10_WRAP, full_offset);

		/* This variable tracks the मुक्त buffer ring 1 full position,
		 * so it has to match the above.
		 */
		fbr->local_full = ET_DMA10_WRAP;
		ग_लिखोl(((fbr->num_entries * LO_MARK_PERCENT_FOR_RX) / 100) - 1,
		       min_des);
	पूर्ण

	/* Program the number of packets we will receive beक्रमe generating an
	 * पूर्णांकerrupt.
	 * For version B silicon, this value माला_लो updated once स्वतःneg is
	 *complete.
	 */
	ग_लिखोl(PARM_RX_NUM_BUFS_DEF, &rx_dma->num_pkt_करोne);

	/* The "time_done" is not working correctly to coalesce पूर्णांकerrupts
	 * after a given समय period, but rather is giving us an पूर्णांकerrupt
	 * regardless of whether we have received packets.
	 * This value माला_लो updated once स्वतःneg is complete.
	 */
	ग_लिखोl(PARM_RX_TIME_INT_DEF, &rx_dma->max_pkt_समय);

	spin_unlock_irqrestore(&adapter->rcv_lock, flags);
पूर्ण

/* et131x_config_tx_dma_regs - Set up the tx dma section of the JAGCore.
 *
 * Configure the transmit engine with the ring buffers we have created
 * and prepare it क्रम use.
 */
अटल व्योम et131x_config_tx_dma_regs(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा txdma_regs __iomem *txdma = &adapter->regs->txdma;
	काष्ठा tx_ring *tx_ring = &adapter->tx_ring;

	/* Load the hardware with the start of the transmit descriptor ring. */
	ग_लिखोl(upper_32_bits(tx_ring->tx_desc_ring_pa), &txdma->pr_base_hi);
	ग_लिखोl(lower_32_bits(tx_ring->tx_desc_ring_pa), &txdma->pr_base_lo);

	/* Initialise the transmit DMA engine */
	ग_लिखोl(NUM_DESC_PER_RING_TX - 1, &txdma->pr_num_des);

	/* Load the completion ग_लिखोback physical address */
	ग_लिखोl(upper_32_bits(tx_ring->tx_status_pa), &txdma->dma_wb_base_hi);
	ग_लिखोl(lower_32_bits(tx_ring->tx_status_pa), &txdma->dma_wb_base_lo);

	*tx_ring->tx_status = 0;

	ग_लिखोl(0, &txdma->service_request);
	tx_ring->send_idx = 0;
पूर्ण

/* et131x_adapter_setup - Set the adapter up as per cassini+ करोcumentation */
अटल व्योम et131x_adapter_setup(काष्ठा et131x_adapter *adapter)
अणु
	et131x_configure_global_regs(adapter);
	et1310_config_mac_regs1(adapter);

	/* Configure the MMC रेजिस्टरs */
	/* All we need to करो is initialize the Memory Control Register */
	ग_लिखोl(ET_MMC_ENABLE, &adapter->regs->mmc.mmc_ctrl);

	et1310_config_rxmac_regs(adapter);
	et1310_config_txmac_regs(adapter);

	et131x_config_rx_dma_regs(adapter);
	et131x_config_tx_dma_regs(adapter);

	et1310_config_macstat_regs(adapter);

	et1310_phy_घातer_चयन(adapter, 0);
	et131x_xcvr_init(adapter);
पूर्ण

/* et131x_soft_reset - Issue soft reset to the hardware, complete क्रम ET1310 */
अटल व्योम et131x_soft_reset(काष्ठा et131x_adapter *adapter)
अणु
	u32 reg;

	/* Disable MAC Core */
	reg = ET_MAC_CFG1_SOFT_RESET | ET_MAC_CFG1_SIM_RESET |
	      ET_MAC_CFG1_RESET_RXMC | ET_MAC_CFG1_RESET_TXMC |
	      ET_MAC_CFG1_RESET_RXFUNC | ET_MAC_CFG1_RESET_TXFUNC;
	ग_लिखोl(reg, &adapter->regs->mac.cfg1);

	reg = ET_RESET_ALL;
	ग_लिखोl(reg, &adapter->regs->global.sw_reset);

	reg = ET_MAC_CFG1_RESET_RXMC | ET_MAC_CFG1_RESET_TXMC |
	      ET_MAC_CFG1_RESET_RXFUNC | ET_MAC_CFG1_RESET_TXFUNC;
	ग_लिखोl(reg, &adapter->regs->mac.cfg1);
	ग_लिखोl(0, &adapter->regs->mac.cfg1);
पूर्ण

अटल व्योम et131x_enable_पूर्णांकerrupts(काष्ठा et131x_adapter *adapter)
अणु
	u32 mask;

	अगर (adapter->flow == FLOW_TXONLY || adapter->flow == FLOW_BOTH)
		mask = INT_MASK_ENABLE;
	अन्यथा
		mask = INT_MASK_ENABLE_NO_FLOW;

	ग_लिखोl(mask, &adapter->regs->global.पूर्णांक_mask);
पूर्ण

अटल व्योम et131x_disable_पूर्णांकerrupts(काष्ठा et131x_adapter *adapter)
अणु
	ग_लिखोl(INT_MASK_DISABLE, &adapter->regs->global.पूर्णांक_mask);
पूर्ण

अटल व्योम et131x_tx_dma_disable(काष्ठा et131x_adapter *adapter)
अणु
	/* Setup the transmit dma configuration रेजिस्टर */
	ग_लिखोl(ET_TXDMA_CSR_HALT | ET_TXDMA_SNGL_EPKT,
	       &adapter->regs->txdma.csr);
पूर्ण

अटल व्योम et131x_enable_txrx(काष्ठा net_device *netdev)
अणु
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);

	et131x_rx_dma_enable(adapter);
	et131x_tx_dma_enable(adapter);

	अगर (adapter->flags & FMP_ADAPTER_INTERRUPT_IN_USE)
		et131x_enable_पूर्णांकerrupts(adapter);

	netअगर_start_queue(netdev);
पूर्ण

अटल व्योम et131x_disable_txrx(काष्ठा net_device *netdev)
अणु
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);

	netअगर_stop_queue(netdev);

	et131x_rx_dma_disable(adapter);
	et131x_tx_dma_disable(adapter);

	et131x_disable_पूर्णांकerrupts(adapter);
पूर्ण

अटल व्योम et131x_init_send(काष्ठा et131x_adapter *adapter)
अणु
	पूर्णांक i;
	काष्ठा tx_ring *tx_ring = &adapter->tx_ring;
	काष्ठा tcb *tcb = tx_ring->tcb_ring;

	tx_ring->tcb_qhead = tcb;

	स_रखो(tcb, 0, माप(काष्ठा tcb) * NUM_TCB);

	क्रम (i = 0; i < NUM_TCB; i++) अणु
		tcb->next = tcb + 1;
		tcb++;
	पूर्ण

	tcb--;
	tx_ring->tcb_qtail = tcb;
	tcb->next = शून्य;
	/* Curr send queue should now be empty */
	tx_ring->send_head = शून्य;
	tx_ring->send_tail = शून्य;
पूर्ण

/* et1310_enable_phy_coma
 *
 * driver receive an phy status change पूर्णांकerrupt जबतक in D0 and check that
 * phy_status is करोwn.
 *
 *          -- gate off JAGCore;
 *          -- set gigE PHY in Coma mode
 *          -- wake on phy_पूर्णांकerrupt; Perक्रमm software reset JAGCore,
 *             re-initialize jagcore and gigE PHY
 */
अटल व्योम et1310_enable_phy_coma(काष्ठा et131x_adapter *adapter)
अणु
	u32 pmcsr = पढ़ोl(&adapter->regs->global.pm_csr);

	/* Stop sending packets. */
	adapter->flags |= FMP_ADAPTER_LOWER_POWER;

	/* Wait क्रम outstanding Receive packets */
	et131x_disable_txrx(adapter->netdev);

	/* Gate off JAGCore 3 घड़ी करोमुख्यs */
	pmcsr &= ~ET_PMCSR_INIT;
	ग_लिखोl(pmcsr, &adapter->regs->global.pm_csr);

	/* Program gigE PHY in to Coma mode */
	pmcsr |= ET_PM_PHY_SW_COMA;
	ग_लिखोl(pmcsr, &adapter->regs->global.pm_csr);
पूर्ण

अटल व्योम et1310_disable_phy_coma(काष्ठा et131x_adapter *adapter)
अणु
	u32 pmcsr;

	pmcsr = पढ़ोl(&adapter->regs->global.pm_csr);

	/* Disable phy_sw_coma रेजिस्टर and re-enable JAGCore घड़ीs */
	pmcsr |= ET_PMCSR_INIT;
	pmcsr &= ~ET_PM_PHY_SW_COMA;
	ग_लिखोl(pmcsr, &adapter->regs->global.pm_csr);

	/* Restore the GbE PHY speed and duplex modes;
	 * Reset JAGCore; re-configure and initialize JAGCore and gigE PHY
	 */

	/* Re-initialize the send काष्ठाures */
	et131x_init_send(adapter);

	/* Bring the device back to the state it was during init prior to
	 * स्वतःnegotiation being complete.  This way, when we get the स्वतः-neg
	 * complete पूर्णांकerrupt, we can complete init by calling ConfigMacREGS2.
	 */
	et131x_soft_reset(adapter);

	et131x_adapter_setup(adapter);

	/* Allow Tx to restart */
	adapter->flags &= ~FMP_ADAPTER_LOWER_POWER;

	et131x_enable_txrx(adapter->netdev);
पूर्ण

अटल अंतरभूत u32 bump_मुक्त_buff_ring(u32 *मुक्त_buff_ring, u32 limit)
अणु
	u32 पंचांगp_मुक्त_buff_ring = *मुक्त_buff_ring;

	पंचांगp_मुक्त_buff_ring++;
	/* This works क्रम all हालs where limit < 1024. The 1023 हाल
	 * works because 1023++ is 1024 which means the अगर condition is not
	 * taken but the carry of the bit पूर्णांकo the wrap bit toggles the wrap
	 * value correctly
	 */
	अगर ((पंचांगp_मुक्त_buff_ring & ET_DMA10_MASK) > limit) अणु
		पंचांगp_मुक्त_buff_ring &= ~ET_DMA10_MASK;
		पंचांगp_मुक्त_buff_ring ^= ET_DMA10_WRAP;
	पूर्ण
	/* For the 1023 हाल */
	पंचांगp_मुक्त_buff_ring &= (ET_DMA10_MASK | ET_DMA10_WRAP);
	*मुक्त_buff_ring = पंचांगp_मुक्त_buff_ring;
	वापस पंचांगp_मुक्त_buff_ring;
पूर्ण

/* et131x_rx_dma_memory_alloc
 *
 * Allocates Free buffer ring 1 क्रम sure, मुक्त buffer ring 0 अगर required,
 * and the Packet Status Ring.
 */
अटल पूर्णांक et131x_rx_dma_memory_alloc(काष्ठा et131x_adapter *adapter)
अणु
	u8 id;
	u32 i, j;
	u32 bufsize;
	u32 psr_size;
	u32 fbr_chunksize;
	काष्ठा rx_ring *rx_ring = &adapter->rx_ring;
	काष्ठा fbr_lookup *fbr;

	/* Alloc memory क्रम the lookup table */
	rx_ring->fbr[0] = kzalloc(माप(*fbr), GFP_KERNEL);
	अगर (rx_ring->fbr[0] == शून्य)
		वापस -ENOMEM;
	rx_ring->fbr[1] = kzalloc(माप(*fbr), GFP_KERNEL);
	अगर (rx_ring->fbr[1] == शून्य)
		वापस -ENOMEM;

	/* The first thing we will करो is configure the sizes of the buffer
	 * rings. These will change based on jumbo packet support.  Larger
	 * jumbo packets increases the size of each entry in FBR0, and the
	 * number of entries in FBR0, जबतक at the same समय decreasing the
	 * number of entries in FBR1.
	 *
	 * FBR1 holds "large" frames, FBR0 holds "small" frames.  If FBR1
	 * entries are huge in order to accommodate a "jumbo" frame, then it
	 * will have less entries.  Conversely, FBR1 will now be relied upon
	 * to carry more "normal" frames, thus it's entry size also increases
	 * and the number of entries goes up too (since it now carries
	 * "small" + "regular" packets.
	 *
	 * In this scheme, we try to मुख्यtain 512 entries between the two
	 * rings. Also, FBR1 reमुख्यs a स्थिरant size - when it's size द्विगुनs
	 * the number of entries halves.  FBR0 increases in size, however.
	 */
	अगर (adapter->registry_jumbo_packet < 2048) अणु
		rx_ring->fbr[0]->buffsize = 256;
		rx_ring->fbr[0]->num_entries = 512;
		rx_ring->fbr[1]->buffsize = 2048;
		rx_ring->fbr[1]->num_entries = 512;
	पूर्ण अन्यथा अगर (adapter->registry_jumbo_packet < 4096) अणु
		rx_ring->fbr[0]->buffsize = 512;
		rx_ring->fbr[0]->num_entries = 1024;
		rx_ring->fbr[1]->buffsize = 4096;
		rx_ring->fbr[1]->num_entries = 512;
	पूर्ण अन्यथा अणु
		rx_ring->fbr[0]->buffsize = 1024;
		rx_ring->fbr[0]->num_entries = 768;
		rx_ring->fbr[1]->buffsize = 16384;
		rx_ring->fbr[1]->num_entries = 128;
	पूर्ण

	rx_ring->psr_entries = rx_ring->fbr[0]->num_entries +
			       rx_ring->fbr[1]->num_entries;

	क्रम (id = 0; id < NUM_FBRS; id++) अणु
		fbr = rx_ring->fbr[id];
		/* Allocate an area of memory क्रम Free Buffer Ring */
		bufsize = माप(काष्ठा fbr_desc) * fbr->num_entries;
		fbr->ring_virtaddr = dma_alloc_coherent(&adapter->pdev->dev,
							bufsize,
							&fbr->ring_physaddr,
							GFP_KERNEL);
		अगर (!fbr->ring_virtaddr) अणु
			dev_err(&adapter->pdev->dev,
				"Cannot alloc memory for Free Buffer Ring %d\n",
				id);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	क्रम (id = 0; id < NUM_FBRS; id++) अणु
		fbr = rx_ring->fbr[id];
		fbr_chunksize = (FBR_CHUNKS * fbr->buffsize);

		क्रम (i = 0; i < fbr->num_entries / FBR_CHUNKS; i++) अणु
			dma_addr_t fbr_physaddr;

			fbr->mem_virtaddrs[i] = dma_alloc_coherent(
					&adapter->pdev->dev, fbr_chunksize,
					&fbr->mem_physaddrs[i],
					GFP_KERNEL);

			अगर (!fbr->mem_virtaddrs[i]) अणु
				dev_err(&adapter->pdev->dev,
					"Could not alloc memory\n");
				वापस -ENOMEM;
			पूर्ण

			/* See NOTE in "Save Physical Address" comment above */
			fbr_physaddr = fbr->mem_physaddrs[i];

			क्रम (j = 0; j < FBR_CHUNKS; j++) अणु
				u32 k = (i * FBR_CHUNKS) + j;

				/* Save the Virtual address of this index क्रम
				 * quick access later
				 */
				fbr->virt[k] = (u8 *)fbr->mem_virtaddrs[i] +
						   (j * fbr->buffsize);

				/* now store the physical address in the
				 * descriptor so the device can access it
				 */
				fbr->bus_high[k] = upper_32_bits(fbr_physaddr);
				fbr->bus_low[k] = lower_32_bits(fbr_physaddr);
				fbr_physaddr += fbr->buffsize;
			पूर्ण
		पूर्ण
	पूर्ण

	/* Allocate an area of memory क्रम FIFO of Packet Status ring entries */
	psr_size = माप(काष्ठा pkt_stat_desc) * rx_ring->psr_entries;

	rx_ring->ps_ring_virtaddr = dma_alloc_coherent(&adapter->pdev->dev,
						  psr_size,
						  &rx_ring->ps_ring_physaddr,
						  GFP_KERNEL);

	अगर (!rx_ring->ps_ring_virtaddr) अणु
		dev_err(&adapter->pdev->dev,
			"Cannot alloc memory for Packet Status Ring\n");
		वापस -ENOMEM;
	पूर्ण

	/* Allocate an area of memory क्रम ग_लिखोback of status inक्रमmation */
	rx_ring->rx_status_block = dma_alloc_coherent(&adapter->pdev->dev,
					    माप(काष्ठा rx_status_block),
					    &rx_ring->rx_status_bus,
					    GFP_KERNEL);
	अगर (!rx_ring->rx_status_block) अणु
		dev_err(&adapter->pdev->dev,
			"Cannot alloc memory for Status Block\n");
		वापस -ENOMEM;
	पूर्ण
	rx_ring->num_rfd = NIC_DEFAULT_NUM_RFD;

	/* The RFDs are going to be put on lists later on, so initialize the
	 * lists now.
	 */
	INIT_LIST_HEAD(&rx_ring->recv_list);
	वापस 0;
पूर्ण

अटल व्योम et131x_rx_dma_memory_मुक्त(काष्ठा et131x_adapter *adapter)
अणु
	u8 id;
	u32 ii;
	u32 bufsize;
	u32 psr_size;
	काष्ठा rfd *rfd;
	काष्ठा rx_ring *rx_ring = &adapter->rx_ring;
	काष्ठा fbr_lookup *fbr;

	/* Free RFDs and associated packet descriptors */
	WARN_ON(rx_ring->num_पढ़ोy_recv != rx_ring->num_rfd);

	जबतक (!list_empty(&rx_ring->recv_list)) अणु
		rfd = list_entry(rx_ring->recv_list.next,
				 काष्ठा rfd, list_node);

		list_del(&rfd->list_node);
		rfd->skb = शून्य;
		kमुक्त(rfd);
	पूर्ण

	/* Free Free Buffer Rings */
	क्रम (id = 0; id < NUM_FBRS; id++) अणु
		fbr = rx_ring->fbr[id];

		अगर (!fbr || !fbr->ring_virtaddr)
			जारी;

		/* First the packet memory */
		क्रम (ii = 0; ii < fbr->num_entries / FBR_CHUNKS; ii++) अणु
			अगर (fbr->mem_virtaddrs[ii]) अणु
				bufsize = fbr->buffsize * FBR_CHUNKS;

				dma_मुक्त_coherent(&adapter->pdev->dev,
						  bufsize,
						  fbr->mem_virtaddrs[ii],
						  fbr->mem_physaddrs[ii]);

				fbr->mem_virtaddrs[ii] = शून्य;
			पूर्ण
		पूर्ण

		bufsize = माप(काष्ठा fbr_desc) * fbr->num_entries;

		dma_मुक्त_coherent(&adapter->pdev->dev,
				  bufsize,
				  fbr->ring_virtaddr,
				  fbr->ring_physaddr);

		fbr->ring_virtaddr = शून्य;
	पूर्ण

	/* Free Packet Status Ring */
	अगर (rx_ring->ps_ring_virtaddr) अणु
		psr_size = माप(काष्ठा pkt_stat_desc) * rx_ring->psr_entries;

		dma_मुक्त_coherent(&adapter->pdev->dev, psr_size,
				  rx_ring->ps_ring_virtaddr,
				  rx_ring->ps_ring_physaddr);

		rx_ring->ps_ring_virtaddr = शून्य;
	पूर्ण

	/* Free area of memory क्रम the ग_लिखोback of status inक्रमmation */
	अगर (rx_ring->rx_status_block) अणु
		dma_मुक्त_coherent(&adapter->pdev->dev,
				  माप(काष्ठा rx_status_block),
				  rx_ring->rx_status_block,
				  rx_ring->rx_status_bus);
		rx_ring->rx_status_block = शून्य;
	पूर्ण

	/* Free the FBR Lookup Table */
	kमुक्त(rx_ring->fbr[0]);
	kमुक्त(rx_ring->fbr[1]);

	/* Reset Counters */
	rx_ring->num_पढ़ोy_recv = 0;
पूर्ण

/* et131x_init_recv - Initialize receive data काष्ठाures */
अटल पूर्णांक et131x_init_recv(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा rfd *rfd;
	u32 rfdct;
	काष्ठा rx_ring *rx_ring = &adapter->rx_ring;

	/* Setup each RFD */
	क्रम (rfdct = 0; rfdct < rx_ring->num_rfd; rfdct++) अणु
		rfd = kzalloc(माप(*rfd), GFP_ATOMIC | GFP_DMA);
		अगर (!rfd)
			वापस -ENOMEM;

		rfd->skb = शून्य;

		/* Add this RFD to the recv_list */
		list_add_tail(&rfd->list_node, &rx_ring->recv_list);

		/* Increment the available RFD's */
		rx_ring->num_पढ़ोy_recv++;
	पूर्ण

	वापस 0;
पूर्ण

/* et131x_set_rx_dma_समयr - Set the heartbeat समयr according to line rate */
अटल व्योम et131x_set_rx_dma_समयr(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा phy_device *phydev = adapter->netdev->phydev;

	/* For version B silicon, we करो not use the RxDMA समयr क्रम 10 and 100
	 * Mbits/s line rates. We करो not enable and RxDMA पूर्णांकerrupt coalescing.
	 */
	अगर ((phydev->speed == SPEED_100) || (phydev->speed == SPEED_10)) अणु
		ग_लिखोl(0, &adapter->regs->rxdma.max_pkt_समय);
		ग_लिखोl(1, &adapter->regs->rxdma.num_pkt_करोne);
	पूर्ण
पूर्ण

/* nic_वापस_rfd - Recycle a RFD and put it back onto the receive list */
अटल व्योम nic_वापस_rfd(काष्ठा et131x_adapter *adapter, काष्ठा rfd *rfd)
अणु
	काष्ठा rx_ring *rx_local = &adapter->rx_ring;
	काष्ठा rxdma_regs __iomem *rx_dma = &adapter->regs->rxdma;
	u16 buff_index = rfd->bufferindex;
	u8 ring_index = rfd->ringindex;
	अचिन्हित दीर्घ flags;
	काष्ठा fbr_lookup *fbr = rx_local->fbr[ring_index];

	/* We करोn't use any of the OOB data besides status. Otherwise, we
	 * need to clean up OOB data
	 */
	अगर (buff_index < fbr->num_entries) अणु
		u32 मुक्त_buff_ring;
		u32 __iomem *offset;
		काष्ठा fbr_desc *next;

		अगर (ring_index == 0)
			offset = &rx_dma->fbr0_full_offset;
		अन्यथा
			offset = &rx_dma->fbr1_full_offset;

		next = (काष्ठा fbr_desc *)(fbr->ring_virtaddr) +
		       INDEX10(fbr->local_full);

		/* Handle the Free Buffer Ring advancement here. Write
		 * the PA / Buffer Index क्रम the वापसed buffer पूर्णांकo
		 * the oldest (next to be मुक्तd)FBR entry
		 */
		next->addr_hi = fbr->bus_high[buff_index];
		next->addr_lo = fbr->bus_low[buff_index];
		next->word2 = buff_index;

		मुक्त_buff_ring = bump_मुक्त_buff_ring(&fbr->local_full,
						     fbr->num_entries - 1);
		ग_लिखोl(मुक्त_buff_ring, offset);
	पूर्ण अन्यथा अणु
		dev_err(&adapter->pdev->dev,
			"%s illegal Buffer Index returned\n", __func__);
	पूर्ण

	/* The processing on this RFD is करोne, so put it back on the tail of
	 * our list
	 */
	spin_lock_irqsave(&adapter->rcv_lock, flags);
	list_add_tail(&rfd->list_node, &rx_local->recv_list);
	rx_local->num_पढ़ोy_recv++;
	spin_unlock_irqrestore(&adapter->rcv_lock, flags);

	WARN_ON(rx_local->num_पढ़ोy_recv > rx_local->num_rfd);
पूर्ण

/* nic_rx_pkts - Checks the hardware क्रम available packets
 *
 * Checks the hardware क्रम available packets, using completion ring
 * If packets are available, it माला_लो an RFD from the recv_list, attaches
 * the packet to it, माला_दो the RFD in the RecvPendList, and also वापसs
 * the poपूर्णांकer to the RFD.
 */
अटल काष्ठा rfd *nic_rx_pkts(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा rx_ring *rx_local = &adapter->rx_ring;
	काष्ठा rx_status_block *status;
	काष्ठा pkt_stat_desc *psr;
	काष्ठा rfd *rfd;
	अचिन्हित दीर्घ flags;
	काष्ठा list_head *element;
	u8 ring_index;
	u16 buff_index;
	u32 len;
	u32 word0;
	u32 word1;
	काष्ठा sk_buff *skb;
	काष्ठा fbr_lookup *fbr;

	/* RX Status block is written by the DMA engine prior to every
	 * पूर्णांकerrupt. It contains the next to be used entry in the Packet
	 * Status Ring, and also the two Free Buffer rings.
	 */
	status = rx_local->rx_status_block;
	word1 = status->word1 >> 16;

	/* Check the PSR and wrap bits करो not match */
	अगर ((word1 & 0x1FFF) == (rx_local->local_psr_full & 0x1FFF))
		वापस शून्य; /* Looks like this ring is not updated yet */

	/* The packet status ring indicates that data is available. */
	psr = (काष्ठा pkt_stat_desc *)(rx_local->ps_ring_virtaddr) +
			(rx_local->local_psr_full & 0xFFF);

	/* Grab any inक्रमmation that is required once the PSR is advanced,
	 * since we can no दीर्घer rely on the memory being accurate
	 */
	len = psr->word1 & 0xFFFF;
	ring_index = (psr->word1 >> 26) & 0x03;
	fbr = rx_local->fbr[ring_index];
	buff_index = (psr->word1 >> 16) & 0x3FF;
	word0 = psr->word0;

	/* Indicate that we have used this PSR entry. */
	/* FIXME wrap 12 */
	add_12bit(&rx_local->local_psr_full, 1);
	अगर ((rx_local->local_psr_full & 0xFFF) > rx_local->psr_entries - 1) अणु
		/* Clear psr full and toggle the wrap bit */
		rx_local->local_psr_full &=  ~0xFFF;
		rx_local->local_psr_full ^= 0x1000;
	पूर्ण

	ग_लिखोl(rx_local->local_psr_full, &adapter->regs->rxdma.psr_full_offset);

	अगर (ring_index > 1 || buff_index > fbr->num_entries - 1) अणु
		/* Illegal buffer or ring index cannot be used by S/W*/
		dev_err(&adapter->pdev->dev,
			"NICRxPkts PSR Entry %d indicates length of %d and/or bad bi(%d)\n",
			rx_local->local_psr_full & 0xFFF, len, buff_index);
		वापस शून्य;
	पूर्ण

	/* Get and fill the RFD. */
	spin_lock_irqsave(&adapter->rcv_lock, flags);

	element = rx_local->recv_list.next;
	rfd = list_entry(element, काष्ठा rfd, list_node);

	अगर (!rfd) अणु
		spin_unlock_irqrestore(&adapter->rcv_lock, flags);
		वापस शून्य;
	पूर्ण

	list_del(&rfd->list_node);
	rx_local->num_पढ़ोy_recv--;

	spin_unlock_irqrestore(&adapter->rcv_lock, flags);

	rfd->bufferindex = buff_index;
	rfd->ringindex = ring_index;

	/* In V1 silicon, there is a bug which screws up filtering of runt
	 * packets. Thereक्रमe runt packet filtering is disabled in the MAC and
	 * the packets are dropped here. They are also counted here.
	 */
	अगर (len < (NIC_MIN_PACKET_SIZE + 4)) अणु
		adapter->stats.rx_other_errs++;
		rfd->len = 0;
		जाओ out;
	पूर्ण

	अगर ((word0 & ALCATEL_MULTICAST_PKT) && !(word0 & ALCATEL_BROADCAST_PKT))
		adapter->stats.multicast_pkts_rcvd++;

	rfd->len = len;

	skb = dev_alloc_skb(rfd->len + 2);
	अगर (!skb)
		वापस शून्य;

	adapter->netdev->stats.rx_bytes += rfd->len;

	skb_put_data(skb, fbr->virt[buff_index], rfd->len);

	skb->protocol = eth_type_trans(skb, adapter->netdev);
	skb->ip_summed = CHECKSUM_NONE;
	netअगर_receive_skb(skb);

out:
	nic_वापस_rfd(adapter, rfd);
	वापस rfd;
पूर्ण

अटल पूर्णांक et131x_handle_recv_pkts(काष्ठा et131x_adapter *adapter, पूर्णांक budget)
अणु
	काष्ठा rfd *rfd = शून्य;
	पूर्णांक count = 0;
	पूर्णांक limit = budget;
	bool करोne = true;
	काष्ठा rx_ring *rx_ring = &adapter->rx_ring;

	अगर (budget > MAX_PACKETS_HANDLED)
		limit = MAX_PACKETS_HANDLED;

	/* Process up to available RFD's */
	जबतक (count < limit) अणु
		अगर (list_empty(&rx_ring->recv_list)) अणु
			WARN_ON(rx_ring->num_पढ़ोy_recv != 0);
			करोne = false;
			अवरोध;
		पूर्ण

		rfd = nic_rx_pkts(adapter);

		अगर (rfd == शून्य)
			अवरोध;

		/* Do not receive any packets until a filter has been set.
		 * Do not receive any packets until we have link.
		 * If length is zero, वापस the RFD in order to advance the
		 * Free buffer ring.
		 */
		अगर (!adapter->packet_filter ||
		    !netअगर_carrier_ok(adapter->netdev) ||
		    rfd->len == 0)
			जारी;

		adapter->netdev->stats.rx_packets++;

		अगर (rx_ring->num_पढ़ोy_recv < RFD_LOW_WATER_MARK)
			dev_warn(&adapter->pdev->dev, "RFD's are running out\n");

		count++;
	पूर्ण

	अगर (count == limit || !करोne) अणु
		rx_ring->unfinished_receives = true;
		ग_लिखोl(PARM_TX_TIME_INT_DEF * न_अंकO_IN_A_MICRO,
		       &adapter->regs->global.watchकरोg_समयr);
	पूर्ण अन्यथा अणु
		/* Watchकरोg समयr will disable itself अगर appropriate. */
		rx_ring->unfinished_receives = false;
	पूर्ण

	वापस count;
पूर्ण

/* et131x_tx_dma_memory_alloc
 *
 * Allocates memory that will be visible both to the device and to the CPU.
 * The OS will pass us packets, poपूर्णांकers to which we will insert in the Tx
 * Descriptor queue. The device will पढ़ो this queue to find the packets in
 * memory. The device will update the "status" in memory each समय it xmits a
 * packet.
 */
अटल पूर्णांक et131x_tx_dma_memory_alloc(काष्ठा et131x_adapter *adapter)
अणु
	पूर्णांक desc_size = 0;
	काष्ठा tx_ring *tx_ring = &adapter->tx_ring;

	/* Allocate memory क्रम the TCB's (Transmit Control Block) */
	tx_ring->tcb_ring = kसुस्मृति(NUM_TCB, माप(काष्ठा tcb),
				    GFP_KERNEL | GFP_DMA);
	अगर (!tx_ring->tcb_ring)
		वापस -ENOMEM;

	desc_size = (माप(काष्ठा tx_desc) * NUM_DESC_PER_RING_TX);
	tx_ring->tx_desc_ring = dma_alloc_coherent(&adapter->pdev->dev,
						   desc_size,
						   &tx_ring->tx_desc_ring_pa,
						   GFP_KERNEL);
	अगर (!tx_ring->tx_desc_ring) अणु
		dev_err(&adapter->pdev->dev,
			"Cannot alloc memory for Tx Ring\n");
		वापस -ENOMEM;
	पूर्ण

	tx_ring->tx_status = dma_alloc_coherent(&adapter->pdev->dev,
						    माप(u32),
						    &tx_ring->tx_status_pa,
						    GFP_KERNEL);
	अगर (!tx_ring->tx_status) अणु
		dev_err(&adapter->pdev->dev,
			"Cannot alloc memory for Tx status block\n");
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम et131x_tx_dma_memory_मुक्त(काष्ठा et131x_adapter *adapter)
अणु
	पूर्णांक desc_size = 0;
	काष्ठा tx_ring *tx_ring = &adapter->tx_ring;

	अगर (tx_ring->tx_desc_ring) अणु
		/* Free memory relating to Tx rings here */
		desc_size = (माप(काष्ठा tx_desc) * NUM_DESC_PER_RING_TX);
		dma_मुक्त_coherent(&adapter->pdev->dev,
				  desc_size,
				  tx_ring->tx_desc_ring,
				  tx_ring->tx_desc_ring_pa);
		tx_ring->tx_desc_ring = शून्य;
	पूर्ण

	/* Free memory क्रम the Tx status block */
	अगर (tx_ring->tx_status) अणु
		dma_मुक्त_coherent(&adapter->pdev->dev,
				  माप(u32),
				  tx_ring->tx_status,
				  tx_ring->tx_status_pa);

		tx_ring->tx_status = शून्य;
	पूर्ण
	/* Free the memory क्रम the tcb काष्ठाures */
	kमुक्त(tx_ring->tcb_ring);
पूर्ण

/* nic_send_packet - NIC specअगरic send handler क्रम version B silicon. */
अटल पूर्णांक nic_send_packet(काष्ठा et131x_adapter *adapter, काष्ठा tcb *tcb)
अणु
	u32 i;
	काष्ठा tx_desc desc[24];
	u32 frag = 0;
	u32 thiscopy, reमुख्यder;
	काष्ठा sk_buff *skb = tcb->skb;
	u32 nr_frags = skb_shinfo(skb)->nr_frags + 1;
	skb_frag_t *frags = &skb_shinfo(skb)->frags[0];
	काष्ठा phy_device *phydev = adapter->netdev->phydev;
	dma_addr_t dma_addr;
	काष्ठा tx_ring *tx_ring = &adapter->tx_ring;

	/* Part of the optimizations of this send routine restrict us to
	 * sending 24 fragments at a pass.  In practice we should never see
	 * more than 5 fragments.
	 */

	/* nr_frags should be no more than 18. */
	BUILD_BUG_ON(MAX_SKB_FRAGS + 1 > 23);

	स_रखो(desc, 0, माप(काष्ठा tx_desc) * (nr_frags + 1));

	क्रम (i = 0; i < nr_frags; i++) अणु
		/* If there is something in this element, lets get a
		 * descriptor from the ring and get the necessary data
		 */
		अगर (i == 0) अणु
			/* If the fragments are smaller than a standard MTU,
			 * then map them to a single descriptor in the Tx
			 * Desc ring. However, अगर they're larger, as is
			 * possible with support क्रम jumbo packets, then
			 * split them each across 2 descriptors.
			 *
			 * This will work until we determine why the hardware
			 * करोesn't seem to like large fragments.
			 */
			अगर (skb_headlen(skb) <= 1514) अणु
				/* Low 16bits are length, high is vlan and
				 * unused currently so zero
				 */
				desc[frag].len_vlan = skb_headlen(skb);
				dma_addr = dma_map_single(&adapter->pdev->dev,
							  skb->data,
							  skb_headlen(skb),
							  DMA_TO_DEVICE);
				desc[frag].addr_lo = lower_32_bits(dma_addr);
				desc[frag].addr_hi = upper_32_bits(dma_addr);
				frag++;
			पूर्ण अन्यथा अणु
				desc[frag].len_vlan = skb_headlen(skb) / 2;
				dma_addr = dma_map_single(&adapter->pdev->dev,
							  skb->data,
							  skb_headlen(skb) / 2,
							  DMA_TO_DEVICE);
				desc[frag].addr_lo = lower_32_bits(dma_addr);
				desc[frag].addr_hi = upper_32_bits(dma_addr);
				frag++;

				desc[frag].len_vlan = skb_headlen(skb) / 2;
				dma_addr = dma_map_single(&adapter->pdev->dev,
							  skb->data +
							  skb_headlen(skb) / 2,
							  skb_headlen(skb) / 2,
							  DMA_TO_DEVICE);
				desc[frag].addr_lo = lower_32_bits(dma_addr);
				desc[frag].addr_hi = upper_32_bits(dma_addr);
				frag++;
			पूर्ण
		पूर्ण अन्यथा अणु
			desc[frag].len_vlan = skb_frag_size(&frags[i - 1]);
			dma_addr = skb_frag_dma_map(&adapter->pdev->dev,
						    &frags[i - 1],
						    0,
						    desc[frag].len_vlan,
						    DMA_TO_DEVICE);
			desc[frag].addr_lo = lower_32_bits(dma_addr);
			desc[frag].addr_hi = upper_32_bits(dma_addr);
			frag++;
		पूर्ण
	पूर्ण

	अगर (phydev && phydev->speed == SPEED_1000) अणु
		अगर (++tx_ring->since_irq == PARM_TX_NUM_BUFS_DEF) अणु
			/* Last element & Interrupt flag */
			desc[frag - 1].flags =
				    TXDESC_FLAG_INTPROC | TXDESC_FLAG_LASTPKT;
			tx_ring->since_irq = 0;
		पूर्ण अन्यथा अणु /* Last element */
			desc[frag - 1].flags = TXDESC_FLAG_LASTPKT;
		पूर्ण
	पूर्ण अन्यथा अणु
		desc[frag - 1].flags =
				    TXDESC_FLAG_INTPROC | TXDESC_FLAG_LASTPKT;
	पूर्ण

	desc[0].flags |= TXDESC_FLAG_FIRSTPKT;

	tcb->index_start = tx_ring->send_idx;
	tcb->stale = 0;

	thiscopy = NUM_DESC_PER_RING_TX - INDEX10(tx_ring->send_idx);

	अगर (thiscopy >= frag) अणु
		reमुख्यder = 0;
		thiscopy = frag;
	पूर्ण अन्यथा अणु
		reमुख्यder = frag - thiscopy;
	पूर्ण

	स_नकल(tx_ring->tx_desc_ring + INDEX10(tx_ring->send_idx),
	       desc,
	       माप(काष्ठा tx_desc) * thiscopy);

	add_10bit(&tx_ring->send_idx, thiscopy);

	अगर (INDEX10(tx_ring->send_idx) == 0 ||
	    INDEX10(tx_ring->send_idx) == NUM_DESC_PER_RING_TX) अणु
		tx_ring->send_idx &= ~ET_DMA10_MASK;
		tx_ring->send_idx ^= ET_DMA10_WRAP;
	पूर्ण

	अगर (reमुख्यder) अणु
		स_नकल(tx_ring->tx_desc_ring,
		       desc + thiscopy,
		       माप(काष्ठा tx_desc) * reमुख्यder);

		add_10bit(&tx_ring->send_idx, reमुख्यder);
	पूर्ण

	अगर (INDEX10(tx_ring->send_idx) == 0) अणु
		अगर (tx_ring->send_idx)
			tcb->index = NUM_DESC_PER_RING_TX - 1;
		अन्यथा
			tcb->index = ET_DMA10_WRAP|(NUM_DESC_PER_RING_TX - 1);
	पूर्ण अन्यथा अणु
		tcb->index = tx_ring->send_idx - 1;
	पूर्ण

	spin_lock(&adapter->tcb_send_qlock);

	अगर (tx_ring->send_tail)
		tx_ring->send_tail->next = tcb;
	अन्यथा
		tx_ring->send_head = tcb;

	tx_ring->send_tail = tcb;

	WARN_ON(tcb->next != शून्य);

	tx_ring->used++;

	spin_unlock(&adapter->tcb_send_qlock);

	/* Write the new ग_लिखो poपूर्णांकer back to the device. */
	ग_लिखोl(tx_ring->send_idx, &adapter->regs->txdma.service_request);

	/* For Gig only, we use Tx Interrupt coalescing.  Enable the software
	 * समयr to wake us up अगर this packet isn't followed by N more.
	 */
	अगर (phydev && phydev->speed == SPEED_1000) अणु
		ग_लिखोl(PARM_TX_TIME_INT_DEF * न_अंकO_IN_A_MICRO,
		       &adapter->regs->global.watchकरोg_समयr);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक send_packet(काष्ठा sk_buff *skb, काष्ठा et131x_adapter *adapter)
अणु
	पूर्णांक status;
	काष्ठा tcb *tcb;
	अचिन्हित दीर्घ flags;
	काष्ठा tx_ring *tx_ring = &adapter->tx_ring;

	/* All packets must have at least a MAC address and a protocol type */
	अगर (skb->len < ETH_HLEN)
		वापस -EIO;

	spin_lock_irqsave(&adapter->tcb_पढ़ोy_qlock, flags);

	tcb = tx_ring->tcb_qhead;

	अगर (tcb == शून्य) अणु
		spin_unlock_irqrestore(&adapter->tcb_पढ़ोy_qlock, flags);
		वापस -ENOMEM;
	पूर्ण

	tx_ring->tcb_qhead = tcb->next;

	अगर (tx_ring->tcb_qhead == शून्य)
		tx_ring->tcb_qtail = शून्य;

	spin_unlock_irqrestore(&adapter->tcb_पढ़ोy_qlock, flags);

	tcb->skb = skb;
	tcb->next = शून्य;

	status = nic_send_packet(adapter, tcb);

	अगर (status != 0) अणु
		spin_lock_irqsave(&adapter->tcb_पढ़ोy_qlock, flags);

		अगर (tx_ring->tcb_qtail)
			tx_ring->tcb_qtail->next = tcb;
		अन्यथा
			/* Apparently पढ़ोy Q is empty. */
			tx_ring->tcb_qhead = tcb;

		tx_ring->tcb_qtail = tcb;
		spin_unlock_irqrestore(&adapter->tcb_पढ़ोy_qlock, flags);
		वापस status;
	पूर्ण
	WARN_ON(tx_ring->used > NUM_TCB);
	वापस 0;
पूर्ण

/* मुक्त_send_packet - Recycle a काष्ठा tcb */
अटल अंतरभूत व्योम मुक्त_send_packet(काष्ठा et131x_adapter *adapter,
				    काष्ठा tcb *tcb)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा tx_desc *desc = शून्य;
	काष्ठा net_device_stats *stats = &adapter->netdev->stats;
	काष्ठा tx_ring *tx_ring = &adapter->tx_ring;
	u64  dma_addr;

	अगर (tcb->skb) अणु
		stats->tx_bytes += tcb->skb->len;

		/* Iterate through the TX descriptors on the ring
		 * corresponding to this packet and umap the fragments
		 * they poपूर्णांक to
		 */
		करो अणु
			desc = tx_ring->tx_desc_ring +
			       INDEX10(tcb->index_start);

			dma_addr = desc->addr_lo;
			dma_addr |= (u64)desc->addr_hi << 32;

			dma_unmap_single(&adapter->pdev->dev,
					 dma_addr,
					 desc->len_vlan, DMA_TO_DEVICE);

			add_10bit(&tcb->index_start, 1);
			अगर (INDEX10(tcb->index_start) >=
							NUM_DESC_PER_RING_TX) अणु
				tcb->index_start &= ~ET_DMA10_MASK;
				tcb->index_start ^= ET_DMA10_WRAP;
			पूर्ण
		पूर्ण जबतक (desc != tx_ring->tx_desc_ring + INDEX10(tcb->index));

		dev_kमुक्त_skb_any(tcb->skb);
	पूर्ण

	स_रखो(tcb, 0, माप(काष्ठा tcb));

	/* Add the TCB to the Ready Q */
	spin_lock_irqsave(&adapter->tcb_पढ़ोy_qlock, flags);

	stats->tx_packets++;

	अगर (tx_ring->tcb_qtail)
		tx_ring->tcb_qtail->next = tcb;
	अन्यथा /* Apparently पढ़ोy Q is empty. */
		tx_ring->tcb_qhead = tcb;

	tx_ring->tcb_qtail = tcb;

	spin_unlock_irqrestore(&adapter->tcb_पढ़ोy_qlock, flags);
	WARN_ON(tx_ring->used < 0);
पूर्ण

/* et131x_मुक्त_busy_send_packets - Free and complete the stopped active sends */
अटल व्योम et131x_मुक्त_busy_send_packets(काष्ठा et131x_adapter *adapter)
अणु
	काष्ठा tcb *tcb;
	अचिन्हित दीर्घ flags;
	u32 मुक्तd = 0;
	काष्ठा tx_ring *tx_ring = &adapter->tx_ring;

	/* Any packets being sent? Check the first TCB on the send list */
	spin_lock_irqsave(&adapter->tcb_send_qlock, flags);

	tcb = tx_ring->send_head;

	जबतक (tcb != शून्य && मुक्तd < NUM_TCB) अणु
		काष्ठा tcb *next = tcb->next;

		tx_ring->send_head = next;

		अगर (next == शून्य)
			tx_ring->send_tail = शून्य;

		tx_ring->used--;

		spin_unlock_irqrestore(&adapter->tcb_send_qlock, flags);

		मुक्तd++;
		मुक्त_send_packet(adapter, tcb);

		spin_lock_irqsave(&adapter->tcb_send_qlock, flags);

		tcb = tx_ring->send_head;
	पूर्ण

	WARN_ON(मुक्तd == NUM_TCB);

	spin_unlock_irqrestore(&adapter->tcb_send_qlock, flags);

	tx_ring->used = 0;
पूर्ण

/* et131x_handle_send_pkts
 *
 * Re-claim the send resources, complete sends and get more to send from
 * the send रुको queue.
 */
अटल व्योम et131x_handle_send_pkts(काष्ठा et131x_adapter *adapter)
अणु
	अचिन्हित दीर्घ flags;
	u32 serviced;
	काष्ठा tcb *tcb;
	u32 index;
	काष्ठा tx_ring *tx_ring = &adapter->tx_ring;

	serviced = पढ़ोl(&adapter->regs->txdma.new_service_complete);
	index = INDEX10(serviced);

	/* Has the ring wrapped?  Process any descriptors that करो not have
	 * the same "wrap" indicator as the current completion indicator
	 */
	spin_lock_irqsave(&adapter->tcb_send_qlock, flags);

	tcb = tx_ring->send_head;

	जबतक (tcb &&
	       ((serviced ^ tcb->index) & ET_DMA10_WRAP) &&
	       index < INDEX10(tcb->index)) अणु
		tx_ring->used--;
		tx_ring->send_head = tcb->next;
		अगर (tcb->next == शून्य)
			tx_ring->send_tail = शून्य;

		spin_unlock_irqrestore(&adapter->tcb_send_qlock, flags);
		मुक्त_send_packet(adapter, tcb);
		spin_lock_irqsave(&adapter->tcb_send_qlock, flags);

		/* Goto the next packet */
		tcb = tx_ring->send_head;
	पूर्ण
	जबतक (tcb &&
	       !((serviced ^ tcb->index) & ET_DMA10_WRAP) &&
	       index > (tcb->index & ET_DMA10_MASK)) अणु
		tx_ring->used--;
		tx_ring->send_head = tcb->next;
		अगर (tcb->next == शून्य)
			tx_ring->send_tail = शून्य;

		spin_unlock_irqrestore(&adapter->tcb_send_qlock, flags);
		मुक्त_send_packet(adapter, tcb);
		spin_lock_irqsave(&adapter->tcb_send_qlock, flags);

		/* Goto the next packet */
		tcb = tx_ring->send_head;
	पूर्ण

	/* Wake up the queue when we hit a low-water mark */
	अगर (tx_ring->used <= NUM_TCB / 3)
		netअगर_wake_queue(adapter->netdev);

	spin_unlock_irqrestore(&adapter->tcb_send_qlock, flags);
पूर्ण

अटल पूर्णांक et131x_get_regs_len(काष्ठा net_device *netdev)
अणु
#घोषणा ET131X_REGS_LEN 256
	वापस ET131X_REGS_LEN * माप(u32);
पूर्ण

अटल व्योम et131x_get_regs(काष्ठा net_device *netdev,
			    काष्ठा ethtool_regs *regs, व्योम *regs_data)
अणु
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);
	काष्ठा address_map __iomem *aregs = adapter->regs;
	u32 *regs_buff = regs_data;
	u32 num = 0;
	u16 पंचांगp;

	स_रखो(regs_data, 0, et131x_get_regs_len(netdev));

	regs->version = (1 << 24) | (adapter->pdev->revision << 16) |
			adapter->pdev->device;

	/* PHY regs */
	et131x_mii_पढ़ो(adapter, MII_BMCR, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, MII_BMSR, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, MII_PHYSID1, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, MII_PHYSID2, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, MII_ADVERTISE, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, MII_LPA, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, MII_EXPANSION, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	/* Autoneg next page transmit reg */
	et131x_mii_पढ़ो(adapter, 0x07, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	/* Link partner next page reg */
	et131x_mii_पढ़ो(adapter, 0x08, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, MII_CTRL1000, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, MII_STAT1000, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, 0x0b, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, 0x0c, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, MII_MMD_CTRL, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, MII_MMD_DATA, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, MII_ESTATUS, &पंचांगp);
	regs_buff[num++] = पंचांगp;

	et131x_mii_पढ़ो(adapter, PHY_INDEX_REG, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, PHY_DATA_REG, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, PHY_MPHY_CONTROL_REG, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, PHY_LOOPBACK_CONTROL, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, PHY_LOOPBACK_CONTROL + 1, &पंचांगp);
	regs_buff[num++] = पंचांगp;

	et131x_mii_पढ़ो(adapter, PHY_REGISTER_MGMT_CONTROL, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, PHY_CONFIG, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, PHY_PHY_CONTROL, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, PHY_INTERRUPT_MASK, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, PHY_INTERRUPT_STATUS, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, PHY_PHY_STATUS, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, PHY_LED_1, &पंचांगp);
	regs_buff[num++] = पंचांगp;
	et131x_mii_पढ़ो(adapter, PHY_LED_2, &पंचांगp);
	regs_buff[num++] = पंचांगp;

	/* Global regs */
	regs_buff[num++] = पढ़ोl(&aregs->global.txq_start_addr);
	regs_buff[num++] = पढ़ोl(&aregs->global.txq_end_addr);
	regs_buff[num++] = पढ़ोl(&aregs->global.rxq_start_addr);
	regs_buff[num++] = पढ़ोl(&aregs->global.rxq_end_addr);
	regs_buff[num++] = पढ़ोl(&aregs->global.pm_csr);
	regs_buff[num++] = adapter->stats.पूर्णांकerrupt_status;
	regs_buff[num++] = पढ़ोl(&aregs->global.पूर्णांक_mask);
	regs_buff[num++] = पढ़ोl(&aregs->global.पूर्णांक_alias_clr_en);
	regs_buff[num++] = पढ़ोl(&aregs->global.पूर्णांक_status_alias);
	regs_buff[num++] = पढ़ोl(&aregs->global.sw_reset);
	regs_buff[num++] = पढ़ोl(&aregs->global.slv_समयr);
	regs_buff[num++] = पढ़ोl(&aregs->global.msi_config);
	regs_buff[num++] = पढ़ोl(&aregs->global.loopback);
	regs_buff[num++] = पढ़ोl(&aregs->global.watchकरोg_समयr);

	/* TXDMA regs */
	regs_buff[num++] = पढ़ोl(&aregs->txdma.csr);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.pr_base_hi);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.pr_base_lo);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.pr_num_des);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.txq_wr_addr);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.txq_wr_addr_ext);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.txq_rd_addr);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.dma_wb_base_hi);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.dma_wb_base_lo);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.service_request);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.service_complete);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.cache_rd_index);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.cache_wr_index);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.tx_dma_error);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.desc_पात_cnt);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.payload_पात_cnt);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.ग_लिखोback_पात_cnt);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.desc_समयout_cnt);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.payload_समयout_cnt);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.ग_लिखोback_समयout_cnt);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.desc_error_cnt);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.payload_error_cnt);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.ग_लिखोback_error_cnt);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.dropped_tlp_cnt);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.new_service_complete);
	regs_buff[num++] = पढ़ोl(&aregs->txdma.ethernet_packet_cnt);

	/* RXDMA regs */
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.csr);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.dma_wb_base_hi);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.dma_wb_base_lo);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.num_pkt_करोne);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.max_pkt_समय);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.rxq_rd_addr);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.rxq_rd_addr_ext);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.rxq_wr_addr);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.psr_base_hi);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.psr_base_lo);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.psr_num_des);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.psr_avail_offset);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.psr_full_offset);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.psr_access_index);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.psr_min_des);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.fbr0_base_lo);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.fbr0_base_hi);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.fbr0_num_des);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.fbr0_avail_offset);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.fbr0_full_offset);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.fbr0_rd_index);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.fbr0_min_des);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.fbr1_base_lo);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.fbr1_base_hi);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.fbr1_num_des);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.fbr1_avail_offset);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.fbr1_full_offset);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.fbr1_rd_index);
	regs_buff[num++] = पढ़ोl(&aregs->rxdma.fbr1_min_des);
पूर्ण

अटल व्योम et131x_get_drvinfo(काष्ठा net_device *netdev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);

	strlcpy(info->driver, DRIVER_NAME, माप(info->driver));
	strlcpy(info->bus_info, pci_name(adapter->pdev),
		माप(info->bus_info));
पूर्ण

अटल स्थिर काष्ठा ethtool_ops et131x_ethtool_ops = अणु
	.get_drvinfo	= et131x_get_drvinfo,
	.get_regs_len	= et131x_get_regs_len,
	.get_regs	= et131x_get_regs,
	.get_link	= ethtool_op_get_link,
	.get_link_ksettings = phy_ethtool_get_link_ksettings,
	.set_link_ksettings = phy_ethtool_set_link_ksettings,
पूर्ण;

/* et131x_hwaddr_init - set up the MAC Address */
अटल व्योम et131x_hwaddr_init(काष्ठा et131x_adapter *adapter)
अणु
	/* If have our शेष mac from init and no mac address from
	 * EEPROM then we need to generate the last octet and set it on the
	 * device
	 */
	अगर (is_zero_ether_addr(adapter->rom_addr)) अणु
		/* We need to अक्रमomly generate the last octet so we
		 * decrease our chances of setting the mac address to
		 * same as another one of our cards in the प्रणाली
		 */
		get_अक्रमom_bytes(&adapter->addr[5], 1);
		/* We have the शेष value in the रेजिस्टर we are
		 * working with so we need to copy the current
		 * address पूर्णांकo the permanent address
		 */
		ether_addr_copy(adapter->rom_addr, adapter->addr);
	पूर्ण अन्यथा अणु
		/* We करो not have an override address, so set the
		 * current address to the permanent address and add
		 * it to the device
		 */
		ether_addr_copy(adapter->addr, adapter->rom_addr);
	पूर्ण
पूर्ण

अटल पूर्णांक et131x_pci_init(काष्ठा et131x_adapter *adapter,
			   काष्ठा pci_dev *pdev)
अणु
	u16 max_payload;
	पूर्णांक i, rc;

	rc = et131x_init_eeprom(adapter);
	अगर (rc < 0)
		जाओ out;

	अगर (!pci_is_pcie(pdev)) अणु
		dev_err(&pdev->dev, "Missing PCIe capabilities\n");
		जाओ err_out;
	पूर्ण

	/* Program the Ack/Nak latency and replay समयrs */
	max_payload = pdev->pcie_mpss;

	अगर (max_payload < 2) अणु
		अटल स्थिर u16 acknak[2] = अणु 0x76, 0xD0 पूर्ण;
		अटल स्थिर u16 replay[2] = अणु 0x1E0, 0x2ED पूर्ण;

		अगर (pci_ग_लिखो_config_word(pdev, ET1310_PCI_ACK_NACK,
					  acknak[max_payload])) अणु
			dev_err(&pdev->dev,
				"Could not write PCI config space for ACK/NAK\n");
			जाओ err_out;
		पूर्ण
		अगर (pci_ग_लिखो_config_word(pdev, ET1310_PCI_REPLAY,
					  replay[max_payload])) अणु
			dev_err(&pdev->dev,
				"Could not write PCI config space for Replay Timer\n");
			जाओ err_out;
		पूर्ण
	पूर्ण

	/* l0s and l1 latency समयrs.  We are using शेष values.
	 * Representing 001 क्रम L0s and 010 क्रम L1
	 */
	अगर (pci_ग_लिखो_config_byte(pdev, ET1310_PCI_L0L1LATENCY, 0x11)) अणु
		dev_err(&pdev->dev,
			"Could not write PCI config space for Latency Timers\n");
		जाओ err_out;
	पूर्ण

	/* Change the max पढ़ो size to 2k */
	अगर (pcie_set_पढ़ोrq(pdev, 2048)) अणु
		dev_err(&pdev->dev,
			"Couldn't change PCI config space for Max read size\n");
		जाओ err_out;
	पूर्ण

	/* Get MAC address from config space अगर an eeprom exists, otherwise
	 * the MAC address there will not be valid
	 */
	अगर (!adapter->has_eeprom) अणु
		et131x_hwaddr_init(adapter);
		वापस 0;
	पूर्ण

	क्रम (i = 0; i < ETH_ALEN; i++) अणु
		अगर (pci_पढ़ो_config_byte(pdev, ET1310_PCI_MAC_ADDRESS + i,
					 adapter->rom_addr + i)) अणु
			dev_err(&pdev->dev, "Could not read PCI config space for MAC address\n");
			जाओ err_out;
		पूर्ण
	पूर्ण
	ether_addr_copy(adapter->addr, adapter->rom_addr);
out:
	वापस rc;
err_out:
	rc = -EIO;
	जाओ out;
पूर्ण

/* et131x_error_समयr_handler
 * @data: समयr-specअगरic variable; here a poपूर्णांकer to our adapter काष्ठाure
 *
 * The routine called when the error समयr expires, to track the number of
 * recurring errors.
 */
अटल व्योम et131x_error_समयr_handler(काष्ठा समयr_list *t)
अणु
	काष्ठा et131x_adapter *adapter = from_समयr(adapter, t, error_समयr);
	काष्ठा phy_device *phydev = adapter->netdev->phydev;

	अगर (et1310_in_phy_coma(adapter)) अणु
		/* Bring the device immediately out of coma, to
		 * prevent it from sleeping indefinitely, this
		 * mechanism could be improved!
		 */
		et1310_disable_phy_coma(adapter);
		adapter->boot_coma = 20;
	पूर्ण अन्यथा अणु
		et1310_update_macstat_host_counters(adapter);
	पूर्ण

	अगर (!phydev->link && adapter->boot_coma < 11)
		adapter->boot_coma++;

	अगर (adapter->boot_coma == 10) अणु
		अगर (!phydev->link) अणु
			अगर (!et1310_in_phy_coma(adapter)) अणु
				/* NOTE - This was originally a 'sync with
				 *  पूर्णांकerrupt'. How to करो that under Linux?
				 */
				et131x_enable_पूर्णांकerrupts(adapter);
				et1310_enable_phy_coma(adapter);
			पूर्ण
		पूर्ण
	पूर्ण

	/* This is a periodic समयr, so reschedule */
	mod_समयr(&adapter->error_समयr, jअगरfies +
		  msecs_to_jअगरfies(TX_ERROR_PERIOD));
पूर्ण

अटल व्योम et131x_adapter_memory_मुक्त(काष्ठा et131x_adapter *adapter)
अणु
	et131x_tx_dma_memory_मुक्त(adapter);
	et131x_rx_dma_memory_मुक्त(adapter);
पूर्ण

अटल पूर्णांक et131x_adapter_memory_alloc(काष्ठा et131x_adapter *adapter)
अणु
	पूर्णांक status;

	status = et131x_tx_dma_memory_alloc(adapter);
	अगर (status) अणु
		dev_err(&adapter->pdev->dev,
			"et131x_tx_dma_memory_alloc FAILED\n");
		et131x_tx_dma_memory_मुक्त(adapter);
		वापस status;
	पूर्ण

	status = et131x_rx_dma_memory_alloc(adapter);
	अगर (status) अणु
		dev_err(&adapter->pdev->dev,
			"et131x_rx_dma_memory_alloc FAILED\n");
		et131x_adapter_memory_मुक्त(adapter);
		वापस status;
	पूर्ण

	status = et131x_init_recv(adapter);
	अगर (status) अणु
		dev_err(&adapter->pdev->dev, "et131x_init_recv FAILED\n");
		et131x_adapter_memory_मुक्त(adapter);
	पूर्ण
	वापस status;
पूर्ण

अटल व्योम et131x_adjust_link(काष्ठा net_device *netdev)
अणु
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);
	काष्ठा  phy_device *phydev = netdev->phydev;

	अगर (!phydev)
		वापस;
	अगर (phydev->link == adapter->link)
		वापस;

	/* Check to see अगर we are in coma mode and अगर
	 * so, disable it because we will not be able
	 * to पढ़ो PHY values until we are out.
	 */
	अगर (et1310_in_phy_coma(adapter))
		et1310_disable_phy_coma(adapter);

	adapter->link = phydev->link;
	phy_prपूर्णांक_status(phydev);

	अगर (phydev->link) अणु
		adapter->boot_coma = 20;
		अगर (phydev->speed == SPEED_10) अणु
			u16 रेजिस्टर18;

			et131x_mii_पढ़ो(adapter, PHY_MPHY_CONTROL_REG,
					&रेजिस्टर18);
			et131x_mii_ग_लिखो(adapter, phydev->mdio.addr,
					 PHY_MPHY_CONTROL_REG,
					 रेजिस्टर18 | 0x4);
			et131x_mii_ग_लिखो(adapter, phydev->mdio.addr,
					 PHY_INDEX_REG, रेजिस्टर18 | 0x8402);
			et131x_mii_ग_लिखो(adapter, phydev->mdio.addr,
					 PHY_DATA_REG, रेजिस्टर18 | 511);
			et131x_mii_ग_लिखो(adapter, phydev->mdio.addr,
					 PHY_MPHY_CONTROL_REG, रेजिस्टर18);
		पूर्ण

		et1310_config_flow_control(adapter);

		अगर (phydev->speed == SPEED_1000 &&
		    adapter->registry_jumbo_packet > 2048) अणु
			u16 reg;

			et131x_mii_पढ़ो(adapter, PHY_CONFIG, &reg);
			reg &= ~ET_PHY_CONFIG_TX_FIFO_DEPTH;
			reg |= ET_PHY_CONFIG_FIFO_DEPTH_32;
			et131x_mii_ग_लिखो(adapter, phydev->mdio.addr,
					 PHY_CONFIG, reg);
		पूर्ण

		et131x_set_rx_dma_समयr(adapter);
		et1310_config_mac_regs2(adapter);
	पूर्ण अन्यथा अणु
		adapter->boot_coma = 0;

		अगर (phydev->speed == SPEED_10) अणु
			u16 रेजिस्टर18;

			et131x_mii_पढ़ो(adapter, PHY_MPHY_CONTROL_REG,
					&रेजिस्टर18);
			et131x_mii_ग_लिखो(adapter, phydev->mdio.addr,
					 PHY_MPHY_CONTROL_REG,
					 रेजिस्टर18 | 0x4);
			et131x_mii_ग_लिखो(adapter, phydev->mdio.addr,
					 PHY_INDEX_REG, रेजिस्टर18 | 0x8402);
			et131x_mii_ग_लिखो(adapter, phydev->mdio.addr,
					 PHY_DATA_REG, रेजिस्टर18 | 511);
			et131x_mii_ग_लिखो(adapter, phydev->mdio.addr,
					 PHY_MPHY_CONTROL_REG, रेजिस्टर18);
		पूर्ण

		et131x_मुक्त_busy_send_packets(adapter);
		et131x_init_send(adapter);

		/* Bring the device back to the state it was during
		 * init prior to स्वतःnegotiation being complete. This
		 * way, when we get the स्वतः-neg complete पूर्णांकerrupt,
		 * we can complete init by calling config_mac_regs2.
		 */
		et131x_soft_reset(adapter);

		et131x_adapter_setup(adapter);

		et131x_disable_txrx(netdev);
		et131x_enable_txrx(netdev);
	पूर्ण
पूर्ण

अटल पूर्णांक et131x_mii_probe(काष्ठा net_device *netdev)
अणु
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);
	काष्ठा  phy_device *phydev = शून्य;

	phydev = phy_find_first(adapter->mii_bus);
	अगर (!phydev) अणु
		dev_err(&adapter->pdev->dev, "no PHY found\n");
		वापस -ENODEV;
	पूर्ण

	phydev = phy_connect(netdev, phydev_name(phydev),
			     &et131x_adjust_link, PHY_INTERFACE_MODE_MII);

	अगर (IS_ERR(phydev)) अणु
		dev_err(&adapter->pdev->dev, "Could not attach to PHY\n");
		वापस PTR_ERR(phydev);
	पूर्ण

	phy_set_max_speed(phydev, SPEED_100);

	अगर (adapter->pdev->device != ET131X_PCI_DEVICE_ID_FAST)
		phy_set_max_speed(phydev, SPEED_1000);

	phydev->स्वतःneg = AUTONEG_ENABLE;

	phy_attached_info(phydev);

	वापस 0;
पूर्ण

अटल काष्ठा et131x_adapter *et131x_adapter_init(काष्ठा net_device *netdev,
						  काष्ठा pci_dev *pdev)
अणु
	अटल स्थिर u8 शेष_mac[] = अणु 0x00, 0x05, 0x3d, 0x00, 0x02, 0x00 पूर्ण;

	काष्ठा et131x_adapter *adapter;

	adapter = netdev_priv(netdev);
	adapter->pdev = pci_dev_get(pdev);
	adapter->netdev = netdev;

	spin_lock_init(&adapter->tcb_send_qlock);
	spin_lock_init(&adapter->tcb_पढ़ोy_qlock);
	spin_lock_init(&adapter->rcv_lock);

	adapter->registry_jumbo_packet = 1514;	/* 1514-9216 */

	ether_addr_copy(adapter->addr, शेष_mac);

	वापस adapter;
पूर्ण

अटल व्योम et131x_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);

	unरेजिस्टर_netdev(netdev);
	netअगर_napi_del(&adapter->napi);
	phy_disconnect(netdev->phydev);
	mdiobus_unरेजिस्टर(adapter->mii_bus);
	mdiobus_मुक्त(adapter->mii_bus);

	et131x_adapter_memory_मुक्त(adapter);
	iounmap(adapter->regs);
	pci_dev_put(pdev);

	मुक्त_netdev(netdev);
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल व्योम et131x_up(काष्ठा net_device *netdev)
अणु
	et131x_enable_txrx(netdev);
	phy_start(netdev->phydev);
पूर्ण

अटल व्योम et131x_करोwn(काष्ठा net_device *netdev)
अणु
	/* Save the बारtamp क्रम the TX watchकरोg, prevent a समयout */
	netअगर_trans_update(netdev);

	phy_stop(netdev->phydev);
	et131x_disable_txrx(netdev);
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक et131x_suspend(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);

	अगर (netअगर_running(netdev)) अणु
		netअगर_device_detach(netdev);
		et131x_करोwn(netdev);
		pci_save_state(pdev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक et131x_resume(काष्ठा device *dev)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(dev);
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);

	अगर (netअगर_running(netdev)) अणु
		pci_restore_state(pdev);
		et131x_up(netdev);
		netअगर_device_attach(netdev);
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल SIMPLE_DEV_PM_OPS(et131x_pm_ops, et131x_suspend, et131x_resume);

अटल irqवापस_t et131x_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	bool handled = true;
	bool enable_पूर्णांकerrupts = true;
	काष्ठा net_device *netdev = dev_id;
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);
	काष्ठा address_map __iomem *iomem = adapter->regs;
	काष्ठा rx_ring *rx_ring = &adapter->rx_ring;
	काष्ठा tx_ring *tx_ring = &adapter->tx_ring;
	u32 status;

	अगर (!netअगर_device_present(netdev)) अणु
		handled = false;
		enable_पूर्णांकerrupts = false;
		जाओ out;
	पूर्ण

	et131x_disable_पूर्णांकerrupts(adapter);

	status = पढ़ोl(&adapter->regs->global.पूर्णांक_status);

	अगर (adapter->flow == FLOW_TXONLY || adapter->flow == FLOW_BOTH)
		status &= ~INT_MASK_ENABLE;
	अन्यथा
		status &= ~INT_MASK_ENABLE_NO_FLOW;

	/* Make sure this is our पूर्णांकerrupt */
	अगर (!status) अणु
		handled = false;
		et131x_enable_पूर्णांकerrupts(adapter);
		जाओ out;
	पूर्ण

	/* This is our पूर्णांकerrupt, so process accordingly */
	अगर (status & ET_INTR_WATCHDOG) अणु
		काष्ठा tcb *tcb = tx_ring->send_head;

		अगर (tcb)
			अगर (++tcb->stale > 1)
				status |= ET_INTR_TXDMA_ISR;

		अगर (rx_ring->unfinished_receives)
			status |= ET_INTR_RXDMA_XFR_DONE;
		अन्यथा अगर (tcb == शून्य)
			ग_लिखोl(0, &adapter->regs->global.watchकरोg_समयr);

		status &= ~ET_INTR_WATCHDOG;
	पूर्ण

	अगर (status & (ET_INTR_RXDMA_XFR_DONE | ET_INTR_TXDMA_ISR)) अणु
		enable_पूर्णांकerrupts = false;
		napi_schedule(&adapter->napi);
	पूर्ण

	status &= ~(ET_INTR_TXDMA_ISR | ET_INTR_RXDMA_XFR_DONE);

	अगर (!status)
		जाओ out;

	अगर (status & ET_INTR_TXDMA_ERR) अणु
		/* Following पढ़ो also clears the रेजिस्टर (COR) */
		u32 txdma_err = पढ़ोl(&iomem->txdma.tx_dma_error);

		dev_warn(&adapter->pdev->dev,
			 "TXDMA_ERR interrupt, error = %d\n",
			 txdma_err);
	पूर्ण

	अगर (status & (ET_INTR_RXDMA_FB_R0_LOW | ET_INTR_RXDMA_FB_R1_LOW)) अणु
		/* This indicates the number of unused buffers in RXDMA मुक्त
		 * buffer ring 0 is <= the limit you programmed. Free buffer
		 * resources need to be वापसed.  Free buffers are consumed as
		 * packets are passed from the network to the host. The host
		 * becomes aware of the packets from the contents of the packet
		 * status ring. This ring is queried when the packet करोne
		 * पूर्णांकerrupt occurs. Packets are then passed to the OS. When
		 * the OS is करोne with the packets the resources can be
		 * वापसed to the ET1310 क्रम re-use. This पूर्णांकerrupt is one
		 * method of वापसing resources.
		 */

		/*  If the user has flow control on, then we will
		 * send a छोड़ो packet, otherwise just निकास
		 */
		अगर (adapter->flow == FLOW_TXONLY || adapter->flow == FLOW_BOTH) अणु
			/* Tell the device to send a छोड़ो packet via the back
			 * pressure रेजिस्टर (bp req and bp xon/xoff)
			 */
			अगर (!et1310_in_phy_coma(adapter))
				ग_लिखोl(3, &iomem->txmac.bp_ctrl);
		पूर्ण
	पूर्ण

	/* Handle Packet Status Ring Low Interrupt */
	अगर (status & ET_INTR_RXDMA_STAT_LOW) अणु
		/* Same idea as with the two Free Buffer Rings. Packets going
		 * from the network to the host each consume a मुक्त buffer
		 * resource and a packet status resource. These resources are
		 * passed to the OS. When the OS is करोne with the resources,
		 * they need to be वापसed to the ET1310. This is one method
		 * of वापसing the resources.
		 */
	पूर्ण

	अगर (status & ET_INTR_RXDMA_ERR) अणु
		/* The rxdma_error पूर्णांकerrupt is sent when a समय-out on a
		 * request issued by the JAGCore has occurred or a completion is
		 * वापसed with an un-successful status. In both हालs the
		 * request is considered complete. The JAGCore will
		 * स्वतःmatically re-try the request in question. Normally
		 * inक्रमmation on events like these are sent to the host using
		 * the "Advanced Error Reporting" capability. This पूर्णांकerrupt is
		 * another way of getting similar inक्रमmation. The only thing
		 * required is to clear the पूर्णांकerrupt by पढ़ोing the ISR in the
		 * global resources. The JAGCore will करो a re-try on the
		 * request. Normally you should never see this पूर्णांकerrupt. If
		 * you start to see this पूर्णांकerrupt occurring frequently then
		 * something bad has occurred. A reset might be the thing to करो.
		 */
		/* TRAP();*/

		dev_warn(&adapter->pdev->dev, "RxDMA_ERR interrupt, error %x\n",
			 पढ़ोl(&iomem->txmac.tx_test));
	पूर्ण

	/* Handle the Wake on LAN Event */
	अगर (status & ET_INTR_WOL) अणु
		/* This is a secondary पूर्णांकerrupt क्रम wake on LAN. The driver
		 * should never see this, अगर it करोes, something serious is
		 * wrong.
		 */
		dev_err(&adapter->pdev->dev, "WAKE_ON_LAN interrupt\n");
	पूर्ण

	अगर (status & ET_INTR_TXMAC) अणु
		u32 err = पढ़ोl(&iomem->txmac.err);

		/* When any of the errors occur and TXMAC generates an
		 * पूर्णांकerrupt to report these errors, it usually means that
		 * TXMAC has detected an error in the data stream retrieved
		 * from the on-chip Tx Q. All of these errors are catastrophic
		 * and TXMAC won't be able to recover data when these errors
		 * occur. In a nutshell, the whole Tx path will have to be reset
		 * and re-configured afterwards.
		 */
		dev_warn(&adapter->pdev->dev, "TXMAC interrupt, error 0x%08x\n",
			 err);

		/* If we are debugging, we want to see this error, otherwise we
		 * just want the device to be reset and जारी
		 */
	पूर्ण

	अगर (status & ET_INTR_RXMAC) अणु
		/* These पूर्णांकerrupts are catastrophic to the device, what we need
		 * to करो is disable the पूर्णांकerrupts and set the flag to cause us
		 * to reset so we can solve this issue.
		 */
		dev_warn(&adapter->pdev->dev,
			 "RXMAC interrupt, error 0x%08x.  Requesting reset\n",
			 पढ़ोl(&iomem->rxmac.err_reg));

		dev_warn(&adapter->pdev->dev,
			 "Enable 0x%08x, Diag 0x%08x\n",
			 पढ़ोl(&iomem->rxmac.ctrl),
			 पढ़ोl(&iomem->rxmac.rxq_diag));

		/* If we are debugging, we want to see this error, otherwise we
		 * just want the device to be reset and जारी
		 */
	पूर्ण

	अगर (status & ET_INTR_MAC_STAT) अणु
		/* This means at least one of the un-masked counters in the
		 * MAC_STAT block has rolled over. Use this to मुख्यtain the top,
		 * software managed bits of the counter(s).
		 */
		et1310_handle_macstat_पूर्णांकerrupt(adapter);
	पूर्ण

	अगर (status & ET_INTR_SLV_TIMEOUT) अणु
		/* This means a समयout has occurred on a पढ़ो or ग_लिखो request
		 * to one of the JAGCore रेजिस्टरs. The Global Resources block
		 * has terminated the request and on a पढ़ो request, वापसed a
		 * "fake" value. The most likely reasons are: Bad Address or the
		 * addressed module is in a घातer-करोwn state and can't respond.
		 */
	पूर्ण

out:
	अगर (enable_पूर्णांकerrupts)
		et131x_enable_पूर्णांकerrupts(adapter);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल पूर्णांक et131x_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा et131x_adapter *adapter =
		container_of(napi, काष्ठा et131x_adapter, napi);
	पूर्णांक work_करोne = et131x_handle_recv_pkts(adapter, budget);

	et131x_handle_send_pkts(adapter);

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(&adapter->napi, work_करोne);
		et131x_enable_पूर्णांकerrupts(adapter);
	पूर्ण

	वापस work_करोne;
पूर्ण

/* et131x_stats - Return the current device statistics  */
अटल काष्ठा net_device_stats *et131x_stats(काष्ठा net_device *netdev)
अणु
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);
	काष्ठा net_device_stats *stats = &adapter->netdev->stats;
	काष्ठा ce_stats *devstat = &adapter->stats;

	stats->rx_errors = devstat->rx_length_errs +
			   devstat->rx_align_errs +
			   devstat->rx_crc_errs +
			   devstat->rx_code_violations +
			   devstat->rx_other_errs;
	stats->tx_errors = devstat->tx_max_pkt_errs;
	stats->multicast = devstat->multicast_pkts_rcvd;
	stats->collisions = devstat->tx_collisions;

	stats->rx_length_errors = devstat->rx_length_errs;
	stats->rx_over_errors = devstat->rx_overflows;
	stats->rx_crc_errors = devstat->rx_crc_errs;
	stats->rx_dropped = devstat->rcvd_pkts_dropped;

	/* NOTE: Not used, can't find analogous statistics */
	/* stats->rx_frame_errors     = devstat->; */
	/* stats->rx_fअगरo_errors      = devstat->; */
	/* stats->rx_missed_errors    = devstat->; */

	/* stats->tx_पातed_errors   = devstat->; */
	/* stats->tx_carrier_errors   = devstat->; */
	/* stats->tx_fअगरo_errors      = devstat->; */
	/* stats->tx_heartbeat_errors = devstat->; */
	/* stats->tx_winकरोw_errors    = devstat->; */
	वापस stats;
पूर्ण

अटल पूर्णांक et131x_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);
	काष्ठा pci_dev *pdev = adapter->pdev;
	अचिन्हित पूर्णांक irq = pdev->irq;
	पूर्णांक result;

	/* Start the समयr to track NIC errors */
	समयr_setup(&adapter->error_समयr, et131x_error_समयr_handler, 0);
	adapter->error_समयr.expires = jअगरfies +
		msecs_to_jअगरfies(TX_ERROR_PERIOD);
	add_समयr(&adapter->error_समयr);

	result = request_irq(irq, et131x_isr,
			     IRQF_SHARED, netdev->name, netdev);
	अगर (result) अणु
		dev_err(&pdev->dev, "could not register IRQ %d\n", irq);
		वापस result;
	पूर्ण

	adapter->flags |= FMP_ADAPTER_INTERRUPT_IN_USE;

	napi_enable(&adapter->napi);

	et131x_up(netdev);

	वापस result;
पूर्ण

अटल पूर्णांक et131x_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);

	et131x_करोwn(netdev);
	napi_disable(&adapter->napi);

	adapter->flags &= ~FMP_ADAPTER_INTERRUPT_IN_USE;
	मुक्त_irq(adapter->pdev->irq, netdev);

	/* Stop the error समयr */
	वापस del_समयr_sync(&adapter->error_समयr);
पूर्ण

/* et131x_set_packet_filter - Configures the Rx Packet filtering */
अटल पूर्णांक et131x_set_packet_filter(काष्ठा et131x_adapter *adapter)
अणु
	पूर्णांक filter = adapter->packet_filter;
	u32 ctrl;
	u32 pf_ctrl;

	ctrl = पढ़ोl(&adapter->regs->rxmac.ctrl);
	pf_ctrl = पढ़ोl(&adapter->regs->rxmac.pf_ctrl);

	/* Default to disabled packet filtering */
	ctrl |= 0x04;

	/* Set us to be in promiscuous mode so we receive everything, this
	 * is also true when we get a packet filter of 0
	 */
	अगर ((filter & ET131X_PACKET_TYPE_PROMISCUOUS) || filter == 0)
		pf_ctrl &= ~7;	/* Clear filter bits */
	अन्यथा अणु
		/* Set us up with Multicast packet filtering.  Three हालs are
		 * possible - (1) we have a multi-cast list, (2) we receive ALL
		 * multicast entries or (3) we receive none.
		 */
		अगर (filter & ET131X_PACKET_TYPE_ALL_MULTICAST)
			pf_ctrl &= ~2;	/* Multicast filter bit */
		अन्यथा अणु
			et1310_setup_device_क्रम_multicast(adapter);
			pf_ctrl |= 2;
			ctrl &= ~0x04;
		पूर्ण

		/* Set us up with Unicast packet filtering */
		अगर (filter & ET131X_PACKET_TYPE_सूचीECTED) अणु
			et1310_setup_device_क्रम_unicast(adapter);
			pf_ctrl |= 4;
			ctrl &= ~0x04;
		पूर्ण

		/* Set us up with Broadcast packet filtering */
		अगर (filter & ET131X_PACKET_TYPE_BROADCAST) अणु
			pf_ctrl |= 1;	/* Broadcast filter bit */
			ctrl &= ~0x04;
		पूर्ण अन्यथा अणु
			pf_ctrl &= ~1;
		पूर्ण

		/* Setup the receive mac configuration रेजिस्टरs - Packet
		 * Filter control + the enable / disable क्रम packet filter
		 * in the control reg.
		 */
		ग_लिखोl(pf_ctrl, &adapter->regs->rxmac.pf_ctrl);
		ग_लिखोl(ctrl, &adapter->regs->rxmac.ctrl);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम et131x_multicast(काष्ठा net_device *netdev)
अणु
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);
	पूर्णांक packet_filter;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i;

	/* Beक्रमe we modअगरy the platक्रमm-independent filter flags, store them
	 * locally. This allows us to determine अगर anything's changed and अगर
	 * we even need to bother the hardware
	 */
	packet_filter = adapter->packet_filter;

	/* Clear the 'multicast' flag locally; because we only have a single
	 * flag to check multicast, and multiple multicast addresses can be
	 * set, this is the easiest way to determine अगर more than one
	 * multicast address is being set.
	 */
	packet_filter &= ~ET131X_PACKET_TYPE_MULTICAST;

	/* Check the net_device flags and set the device independent flags
	 * accordingly
	 */
	अगर (netdev->flags & IFF_PROMISC)
		adapter->packet_filter |= ET131X_PACKET_TYPE_PROMISCUOUS;
	अन्यथा
		adapter->packet_filter &= ~ET131X_PACKET_TYPE_PROMISCUOUS;

	अगर ((netdev->flags & IFF_ALLMULTI) ||
	    (netdev_mc_count(netdev) > NIC_MAX_MCAST_LIST))
		adapter->packet_filter |= ET131X_PACKET_TYPE_ALL_MULTICAST;

	अगर (netdev_mc_count(netdev) < 1) अणु
		adapter->packet_filter &= ~ET131X_PACKET_TYPE_ALL_MULTICAST;
		adapter->packet_filter &= ~ET131X_PACKET_TYPE_MULTICAST;
	पूर्ण अन्यथा अणु
		adapter->packet_filter |= ET131X_PACKET_TYPE_MULTICAST;
	पूर्ण

	/* Set values in the निजी adapter काष्ठा */
	i = 0;
	netdev_क्रम_each_mc_addr(ha, netdev) अणु
		अगर (i == NIC_MAX_MCAST_LIST)
			अवरोध;
		ether_addr_copy(adapter->multicast_list[i++], ha->addr);
	पूर्ण
	adapter->multicast_addr_count = i;

	/* Are the new flags dअगरferent from the previous ones? If not, then no
	 * action is required
	 *
	 * NOTE - This block will always update the multicast_list with the
	 *        hardware, even अगर the addresses aren't the same.
	 */
	अगर (packet_filter != adapter->packet_filter)
		et131x_set_packet_filter(adapter);
पूर्ण

अटल netdev_tx_t et131x_tx(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);
	काष्ठा tx_ring *tx_ring = &adapter->tx_ring;

	/* stop the queue अगर it's getting full */
	अगर (tx_ring->used >= NUM_TCB - 1 && !netअगर_queue_stopped(netdev))
		netअगर_stop_queue(netdev);

	/* Save the बारtamp क्रम the TX समयout watchकरोg */
	netअगर_trans_update(netdev);

	/* TCB is not available */
	अगर (tx_ring->used >= NUM_TCB)
		जाओ drop_err;

	अगर ((adapter->flags & FMP_ADAPTER_FAIL_SEND_MASK) ||
	    !netअगर_carrier_ok(netdev))
		जाओ drop_err;

	अगर (send_packet(skb, adapter))
		जाओ drop_err;

	वापस NETDEV_TX_OK;

drop_err:
	dev_kमुक्त_skb_any(skb);
	adapter->netdev->stats.tx_dropped++;
	वापस NETDEV_TX_OK;
पूर्ण

/* et131x_tx_समयout - Timeout handler
 *
 * The handler called when a Tx request बार out. The समयout period is
 * specअगरied by the 'tx_समयo" element in the net_device काष्ठाure (see
 * et131x_alloc_device() to see how this value is set).
 */
अटल व्योम et131x_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);
	काष्ठा tx_ring *tx_ring = &adapter->tx_ring;
	काष्ठा tcb *tcb;
	अचिन्हित दीर्घ flags;

	/* If the device is बंदd, ignore the समयout */
	अगर (!(adapter->flags & FMP_ADAPTER_INTERRUPT_IN_USE))
		वापस;

	/* Any nonrecoverable hardware error?
	 * Checks adapter->flags क्रम any failure in phy पढ़ोing
	 */
	अगर (adapter->flags & FMP_ADAPTER_NON_RECOVER_ERROR)
		वापस;

	/* Hardware failure? */
	अगर (adapter->flags & FMP_ADAPTER_HARDWARE_ERROR) अणु
		dev_err(&adapter->pdev->dev, "hardware error - reset\n");
		वापस;
	पूर्ण

	/* Is send stuck? */
	spin_lock_irqsave(&adapter->tcb_send_qlock, flags);
	tcb = tx_ring->send_head;
	spin_unlock_irqrestore(&adapter->tcb_send_qlock, flags);

	अगर (tcb) अणु
		tcb->count++;

		अगर (tcb->count > NIC_SEND_HANG_THRESHOLD) अणु
			dev_warn(&adapter->pdev->dev,
				 "Send stuck - reset. tcb->WrIndex %x\n",
				 tcb->index);

			adapter->netdev->stats.tx_errors++;

			/* perक्रमm reset of tx/rx */
			et131x_disable_txrx(netdev);
			et131x_enable_txrx(netdev);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक et131x_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	पूर्णांक result = 0;
	काष्ठा et131x_adapter *adapter = netdev_priv(netdev);

	et131x_disable_txrx(netdev);

	netdev->mtu = new_mtu;

	et131x_adapter_memory_मुक्त(adapter);

	/* Set the config parameter क्रम Jumbo Packet support */
	adapter->registry_jumbo_packet = new_mtu + 14;
	et131x_soft_reset(adapter);

	result = et131x_adapter_memory_alloc(adapter);
	अगर (result != 0) अणु
		dev_warn(&adapter->pdev->dev,
			 "Change MTU failed; couldn't re-alloc DMA memory\n");
		वापस result;
	पूर्ण

	et131x_init_send(adapter);
	et131x_hwaddr_init(adapter);
	ether_addr_copy(netdev->dev_addr, adapter->addr);

	/* Init the device with the new settings */
	et131x_adapter_setup(adapter);
	et131x_enable_txrx(netdev);

	वापस result;
पूर्ण

अटल स्थिर काष्ठा net_device_ops et131x_netdev_ops = अणु
	.nकरो_खोलो		= et131x_खोलो,
	.nकरो_stop		= et131x_बंद,
	.nकरो_start_xmit		= et131x_tx,
	.nकरो_set_rx_mode	= et131x_multicast,
	.nकरो_tx_समयout		= et131x_tx_समयout,
	.nकरो_change_mtu		= et131x_change_mtu,
	.nकरो_set_mac_address	= eth_mac_addr,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_get_stats		= et131x_stats,
	.nकरो_करो_ioctl		= phy_करो_ioctl,
पूर्ण;

अटल पूर्णांक et131x_pci_setup(काष्ठा pci_dev *pdev,
			    स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा net_device *netdev;
	काष्ठा et131x_adapter *adapter;
	पूर्णांक rc;

	rc = pci_enable_device(pdev);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "pci_enable_device() failed\n");
		जाओ out;
	पूर्ण

	/* Perक्रमm some basic PCI checks */
	अगर (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) अणु
		dev_err(&pdev->dev, "Can't find PCI device's base address\n");
		rc = -ENODEV;
		जाओ err_disable;
	पूर्ण

	rc = pci_request_regions(pdev, DRIVER_NAME);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Can't get PCI resources\n");
		जाओ err_disable;
	पूर्ण

	pci_set_master(pdev);

	/* Check the DMA addressing support of this device */
	अगर (dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64)) &&
	    dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32))) अणु
		dev_err(&pdev->dev, "No usable DMA addressing method\n");
		rc = -EIO;
		जाओ err_release_res;
	पूर्ण

	netdev = alloc_etherdev(माप(काष्ठा et131x_adapter));
	अगर (!netdev) अणु
		dev_err(&pdev->dev, "Couldn't alloc netdev struct\n");
		rc = -ENOMEM;
		जाओ err_release_res;
	पूर्ण

	netdev->watchकरोg_समयo = ET131X_TX_TIMEOUT;
	netdev->netdev_ops     = &et131x_netdev_ops;
	netdev->min_mtu        = ET131X_MIN_MTU;
	netdev->max_mtu        = ET131X_MAX_MTU;

	SET_NETDEV_DEV(netdev, &pdev->dev);
	netdev->ethtool_ops = &et131x_ethtool_ops;

	adapter = et131x_adapter_init(netdev, pdev);

	rc = et131x_pci_init(adapter, pdev);
	अगर (rc < 0)
		जाओ err_मुक्त_dev;

	/* Map the bus-relative रेजिस्टरs to प्रणाली भव memory */
	adapter->regs = pci_ioremap_bar(pdev, 0);
	अगर (!adapter->regs) अणु
		dev_err(&pdev->dev, "Cannot map device registers\n");
		rc = -ENOMEM;
		जाओ err_मुक्त_dev;
	पूर्ण

	/* If Phy COMA mode was enabled when we went करोwn, disable it here. */
	ग_लिखोl(ET_PMCSR_INIT,  &adapter->regs->global.pm_csr);

	et131x_soft_reset(adapter);
	et131x_disable_पूर्णांकerrupts(adapter);

	rc = et131x_adapter_memory_alloc(adapter);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "Could not alloc adapter memory (DMA)\n");
		जाओ err_iounmap;
	पूर्ण

	et131x_init_send(adapter);

	netअगर_napi_add(netdev, &adapter->napi, et131x_poll, 64);

	ether_addr_copy(netdev->dev_addr, adapter->addr);

	rc = -ENOMEM;

	adapter->mii_bus = mdiobus_alloc();
	अगर (!adapter->mii_bus) अणु
		dev_err(&pdev->dev, "Alloc of mii_bus struct failed\n");
		जाओ err_mem_मुक्त;
	पूर्ण

	adapter->mii_bus->name = "et131x_eth_mii";
	snम_लिखो(adapter->mii_bus->id, MII_BUS_ID_SIZE, "%x",
		 (adapter->pdev->bus->number << 8) | adapter->pdev->devfn);
	adapter->mii_bus->priv = netdev;
	adapter->mii_bus->पढ़ो = et131x_mdio_पढ़ो;
	adapter->mii_bus->ग_लिखो = et131x_mdio_ग_लिखो;

	rc = mdiobus_रेजिस्टर(adapter->mii_bus);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "failed to register MII bus\n");
		जाओ err_mdio_मुक्त;
	पूर्ण

	rc = et131x_mii_probe(netdev);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "failed to probe MII bus\n");
		जाओ err_mdio_unरेजिस्टर;
	पूर्ण

	et131x_adapter_setup(adapter);

	/* Init variable क्रम counting how दीर्घ we करो not have link status */
	adapter->boot_coma = 0;
	et1310_disable_phy_coma(adapter);

	/* We can enable पूर्णांकerrupts now
	 *
	 *  NOTE - Because registration of पूर्णांकerrupt handler is करोne in the
	 *         device's खोलो(), defer enabling device पूर्णांकerrupts to that
	 *         poपूर्णांक
	 */

	rc = रेजिस्टर_netdev(netdev);
	अगर (rc < 0) अणु
		dev_err(&pdev->dev, "register_netdev() failed\n");
		जाओ err_phy_disconnect;
	पूर्ण

	/* Register the net_device काष्ठा with the PCI subप्रणाली. Save a copy
	 * of the PCI config space क्रम this device now that the device has
	 * been initialized, just in हाल it needs to be quickly restored.
	 */
	pci_set_drvdata(pdev, netdev);
out:
	वापस rc;

err_phy_disconnect:
	phy_disconnect(netdev->phydev);
err_mdio_unरेजिस्टर:
	mdiobus_unरेजिस्टर(adapter->mii_bus);
err_mdio_मुक्त:
	mdiobus_मुक्त(adapter->mii_bus);
err_mem_मुक्त:
	et131x_adapter_memory_मुक्त(adapter);
err_iounmap:
	iounmap(adapter->regs);
err_मुक्त_dev:
	pci_dev_put(pdev);
	मुक्त_netdev(netdev);
err_release_res:
	pci_release_regions(pdev);
err_disable:
	pci_disable_device(pdev);
	जाओ out;
पूर्ण

अटल स्थिर काष्ठा pci_device_id et131x_pci_table[] = अणु
	अणु PCI_VDEVICE(ATT, ET131X_PCI_DEVICE_ID_GIG), 0ULपूर्ण,
	अणु PCI_VDEVICE(ATT, ET131X_PCI_DEVICE_ID_FAST), 0ULपूर्ण,
	अणु 0,पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, et131x_pci_table);

अटल काष्ठा pci_driver et131x_driver = अणु
	.name		= DRIVER_NAME,
	.id_table	= et131x_pci_table,
	.probe		= et131x_pci_setup,
	.हटाओ		= et131x_pci_हटाओ,
	.driver.pm	= &et131x_pm_ops,
पूर्ण;

module_pci_driver(et131x_driver);
