<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Chip रेजिस्टर definitions क्रम PCILynx chipset.  Based on pcilynx.h
 * from the Linux 1394 drivers, but modअगरied a bit so the names here
 * match the specअगरication exactly (even though they have weird names,
 * like xxx_OVER_FLOW, or arbitrary abbreviations like SNTRJ क्रम "sent
 * reject" etc.)
 */

#घोषणा PCILYNX_MAX_REGISTER     0xfff
#घोषणा PCILYNX_MAX_MEMORY       0xffff

#घोषणा PCI_LATENCY_CACHELINE             0x0c

#घोषणा MISC_CONTROL                      0x40
#घोषणा MISC_CONTROL_SWRESET              (1<<0)

#घोषणा SERIAL_EEPROM_CONTROL             0x44

#घोषणा PCI_INT_STATUS                    0x48
#घोषणा PCI_INT_ENABLE                    0x4c
/* status and enable have identical bit numbers */
#घोषणा PCI_INT_INT_PEND                  (1<<31)
#घोषणा PCI_INT_FRC_INT                   (1<<30)
#घोषणा PCI_INT_SLV_ADR_PERR              (1<<28)
#घोषणा PCI_INT_SLV_DAT_PERR              (1<<27)
#घोषणा PCI_INT_MST_DAT_PERR              (1<<26)
#घोषणा PCI_INT_MST_DEV_TO                (1<<25)
#घोषणा PCI_INT_INT_SLV_TO                (1<<23)
#घोषणा PCI_INT_AUX_TO                    (1<<18)
#घोषणा PCI_INT_AUX_INT                   (1<<17)
#घोषणा PCI_INT_P1394_INT                 (1<<16)
#घोषणा PCI_INT_DMA4_PCL                  (1<<9)
#घोषणा PCI_INT_DMA4_HLT                  (1<<8)
#घोषणा PCI_INT_DMA3_PCL                  (1<<7)
#घोषणा PCI_INT_DMA3_HLT                  (1<<6)
#घोषणा PCI_INT_DMA2_PCL                  (1<<5)
#घोषणा PCI_INT_DMA2_HLT                  (1<<4)
#घोषणा PCI_INT_DMA1_PCL                  (1<<3)
#घोषणा PCI_INT_DMA1_HLT                  (1<<2)
#घोषणा PCI_INT_DMA0_PCL                  (1<<1)
#घोषणा PCI_INT_DMA0_HLT                  (1<<0)
/* all DMA पूर्णांकerrupts combined: */
#घोषणा PCI_INT_DMA_ALL                   0x3ff

#घोषणा PCI_INT_DMA_HLT(chan)             (1 << (chan * 2))
#घोषणा PCI_INT_DMA_PCL(chan)             (1 << (chan * 2 + 1))

#घोषणा LBUS_ADDR                         0xb4
#घोषणा LBUS_ADDR_SEL_RAM                 (0x0<<16)
#घोषणा LBUS_ADDR_SEL_ROM                 (0x1<<16)
#घोषणा LBUS_ADDR_SEL_AUX                 (0x2<<16)
#घोषणा LBUS_ADDR_SEL_ZV                  (0x3<<16)

#घोषणा GPIO_CTRL_A                       0xb8
#घोषणा GPIO_CTRL_B                       0xbc
#घोषणा GPIO_DATA_BASE                    0xc0

#घोषणा DMA_BREG(base, chan)              (base + chan * 0x20)
#घोषणा DMA_SREG(base, chan)              (base + chan * 0x10)

#घोषणा PCL_NEXT_INVALID (1<<0)

/* transfer commands */
#घोषणा PCL_CMD_RCV            (0x1<<24)
#घोषणा PCL_CMD_RCV_AND_UPDATE (0xa<<24)
#घोषणा PCL_CMD_XMT            (0x2<<24)
#घोषणा PCL_CMD_UNFXMT         (0xc<<24)
#घोषणा PCL_CMD_PCI_TO_LBUS    (0x8<<24)
#घोषणा PCL_CMD_LBUS_TO_PCI    (0x9<<24)

/* aux commands */
#घोषणा PCL_CMD_NOP            (0x0<<24)
#घोषणा PCL_CMD_LOAD           (0x3<<24)
#घोषणा PCL_CMD_STOREQ         (0x4<<24)
#घोषणा PCL_CMD_STORED         (0xb<<24)
#घोषणा PCL_CMD_STORE0         (0x5<<24)
#घोषणा PCL_CMD_STORE1         (0x6<<24)
#घोषणा PCL_CMD_COMPARE        (0xe<<24)
#घोषणा PCL_CMD_SWAP_COMPARE   (0xf<<24)
#घोषणा PCL_CMD_ADD            (0xd<<24)
#घोषणा PCL_CMD_BRANCH         (0x7<<24)

/* BRANCH condition codes */
#घोषणा PCL_COND_DMARDY_SET    (0x1<<20)
#घोषणा PCL_COND_DMARDY_CLEAR  (0x2<<20)

#घोषणा PCL_GEN_INTR           (1<<19)
#घोषणा PCL_LAST_BUFF          (1<<18)
#घोषणा PCL_LAST_CMD           (PCL_LAST_BUFF)
#घोषणा PCL_WAITSTAT           (1<<17)
#घोषणा PCL_BIGENDIAN          (1<<16)
#घोषणा PCL_ISOMODE            (1<<12)

#घोषणा DMA0_PREV_PCL                     0x100
#घोषणा DMA1_PREV_PCL                     0x120
#घोषणा DMA2_PREV_PCL                     0x140
#घोषणा DMA3_PREV_PCL                     0x160
#घोषणा DMA4_PREV_PCL                     0x180
#घोषणा DMA_PREV_PCL(chan)                (DMA_BREG(DMA0_PREV_PCL, chan))

#घोषणा DMA0_CURRENT_PCL                  0x104
#घोषणा DMA1_CURRENT_PCL                  0x124
#घोषणा DMA2_CURRENT_PCL                  0x144
#घोषणा DMA3_CURRENT_PCL                  0x164
#घोषणा DMA4_CURRENT_PCL                  0x184
#घोषणा DMA_CURRENT_PCL(chan)             (DMA_BREG(DMA0_CURRENT_PCL, chan))

#घोषणा DMA0_CHAN_STAT                    0x10c
#घोषणा DMA1_CHAN_STAT                    0x12c
#घोषणा DMA2_CHAN_STAT                    0x14c
#घोषणा DMA3_CHAN_STAT                    0x16c
#घोषणा DMA4_CHAN_STAT                    0x18c
#घोषणा DMA_CHAN_STAT(chan)               (DMA_BREG(DMA0_CHAN_STAT, chan))
/* CHAN_STATUS रेजिस्टरs share bits */
#घोषणा DMA_CHAN_STAT_SELFID              (1<<31)
#घोषणा DMA_CHAN_STAT_ISOPKT              (1<<30)
#घोषणा DMA_CHAN_STAT_PCIERR              (1<<29)
#घोषणा DMA_CHAN_STAT_PKTERR              (1<<28)
#घोषणा DMA_CHAN_STAT_PKTCMPL             (1<<27)
#घोषणा DMA_CHAN_STAT_SPECIALACK          (1<<14)

#घोषणा DMA0_CHAN_CTRL                    0x110
#घोषणा DMA1_CHAN_CTRL                    0x130
#घोषणा DMA2_CHAN_CTRL                    0x150
#घोषणा DMA3_CHAN_CTRL                    0x170
#घोषणा DMA4_CHAN_CTRL                    0x190
#घोषणा DMA_CHAN_CTRL(chan)               (DMA_BREG(DMA0_CHAN_CTRL, chan))
/* CHAN_CTRL रेजिस्टरs share bits */
#घोषणा DMA_CHAN_CTRL_ENABLE              (1<<31)
#घोषणा DMA_CHAN_CTRL_BUSY                (1<<30)
#घोषणा DMA_CHAN_CTRL_LINK                (1<<29)

#घोषणा DMA0_READY                        0x114
#घोषणा DMA1_READY                        0x134
#घोषणा DMA2_READY                        0x154
#घोषणा DMA3_READY                        0x174
#घोषणा DMA4_READY                        0x194
#घोषणा DMA_READY(chan)                   (DMA_BREG(DMA0_READY, chan))

#घोषणा DMA_GLOBAL_REGISTER               0x908

#घोषणा FIFO_SIZES                        0xa00

#घोषणा FIFO_CONTROL                      0xa10
#घोषणा FIFO_CONTROL_GRF_FLUSH            (1<<4)
#घोषणा FIFO_CONTROL_ITF_FLUSH            (1<<3)
#घोषणा FIFO_CONTROL_ATF_FLUSH            (1<<2)

#घोषणा FIFO_XMIT_THRESHOLD               0xa14

#घोषणा DMA0_WORD0_CMP_VALUE              0xb00
#घोषणा DMA1_WORD0_CMP_VALUE              0xb10
#घोषणा DMA2_WORD0_CMP_VALUE              0xb20
#घोषणा DMA3_WORD0_CMP_VALUE              0xb30
#घोषणा DMA4_WORD0_CMP_VALUE              0xb40
#घोषणा DMA_WORD0_CMP_VALUE(chan)	(DMA_SREG(DMA0_WORD0_CMP_VALUE, chan))

#घोषणा DMA0_WORD0_CMP_ENABLE             0xb04
#घोषणा DMA1_WORD0_CMP_ENABLE             0xb14
#घोषणा DMA2_WORD0_CMP_ENABLE             0xb24
#घोषणा DMA3_WORD0_CMP_ENABLE             0xb34
#घोषणा DMA4_WORD0_CMP_ENABLE             0xb44
#घोषणा DMA_WORD0_CMP_ENABLE(chan)	(DMA_SREG(DMA0_WORD0_CMP_ENABLE, chan))

#घोषणा DMA0_WORD1_CMP_VALUE              0xb08
#घोषणा DMA1_WORD1_CMP_VALUE              0xb18
#घोषणा DMA2_WORD1_CMP_VALUE              0xb28
#घोषणा DMA3_WORD1_CMP_VALUE              0xb38
#घोषणा DMA4_WORD1_CMP_VALUE              0xb48
#घोषणा DMA_WORD1_CMP_VALUE(chan)	(DMA_SREG(DMA0_WORD1_CMP_VALUE, chan))

#घोषणा DMA0_WORD1_CMP_ENABLE             0xb0c
#घोषणा DMA1_WORD1_CMP_ENABLE             0xb1c
#घोषणा DMA2_WORD1_CMP_ENABLE             0xb2c
#घोषणा DMA3_WORD1_CMP_ENABLE             0xb3c
#घोषणा DMA4_WORD1_CMP_ENABLE             0xb4c
#घोषणा DMA_WORD1_CMP_ENABLE(chan)	(DMA_SREG(DMA0_WORD1_CMP_ENABLE, chan))
/* word 1 compare enable flags */
#घोषणा DMA_WORD1_CMP_MATCH_OTHERBUS      (1<<15)
#घोषणा DMA_WORD1_CMP_MATCH_BROADCAST     (1<<14)
#घोषणा DMA_WORD1_CMP_MATCH_BUS_BCAST     (1<<13)
#घोषणा DMA_WORD1_CMP_MATCH_LOCAL_NODE    (1<<12)
#घोषणा DMA_WORD1_CMP_MATCH_EXACT         (1<<11)
#घोषणा DMA_WORD1_CMP_ENABLE_SELF_ID      (1<<10)
#घोषणा DMA_WORD1_CMP_ENABLE_MASTER       (1<<8)

#घोषणा LINK_ID                           0xf00
#घोषणा LINK_ID_BUS(id)                   (id<<22)
#घोषणा LINK_ID_NODE(id)                  (id<<16)

#घोषणा LINK_CONTROL                      0xf04
#घोषणा LINK_CONTROL_BUSY                 (1<<29)
#घोषणा LINK_CONTROL_TX_ISO_EN            (1<<26)
#घोषणा LINK_CONTROL_RX_ISO_EN            (1<<25)
#घोषणा LINK_CONTROL_TX_ASYNC_EN          (1<<24)
#घोषणा LINK_CONTROL_RX_ASYNC_EN          (1<<23)
#घोषणा LINK_CONTROL_RESET_TX             (1<<21)
#घोषणा LINK_CONTROL_RESET_RX             (1<<20)
#घोषणा LINK_CONTROL_CYCMASTER            (1<<11)
#घोषणा LINK_CONTROL_CYCSOURCE            (1<<10)
#घोषणा LINK_CONTROL_CYCTIMEREN           (1<<9)
#घोषणा LINK_CONTROL_RCV_CMP_VALID        (1<<7)
#घोषणा LINK_CONTROL_SNOOP_ENABLE         (1<<6)

#घोषणा CYCLE_TIMER                       0xf08

#घोषणा LINK_PHY                          0xf0c
#घोषणा LINK_PHY_READ                     (1<<31)
#घोषणा LINK_PHY_WRITE                    (1<<30)
#घोषणा LINK_PHY_ADDR(addr)               (addr<<24)
#घोषणा LINK_PHY_WDATA(data)              (data<<16)
#घोषणा LINK_PHY_RADDR(addr)              (addr<<8)

#घोषणा LINK_INT_STATUS                   0xf14
#घोषणा LINK_INT_ENABLE                   0xf18
/* status and enable have identical bit numbers */
#घोषणा LINK_INT_LINK_INT                 (1<<31)
#घोषणा LINK_INT_PHY_TIME_OUT             (1<<30)
#घोषणा LINK_INT_PHY_REG_RCVD             (1<<29)
#घोषणा LINK_INT_PHY_BUSRESET             (1<<28)
#घोषणा LINK_INT_TX_RDY                   (1<<26)
#घोषणा LINK_INT_RX_DATA_RDY              (1<<25)
#घोषणा LINK_INT_IT_STUCK                 (1<<20)
#घोषणा LINK_INT_AT_STUCK                 (1<<19)
#घोषणा LINK_INT_SNTRJ                    (1<<17)
#घोषणा LINK_INT_HDR_ERR                  (1<<16)
#घोषणा LINK_INT_TC_ERR                   (1<<15)
#घोषणा LINK_INT_CYC_SEC                  (1<<11)
#घोषणा LINK_INT_CYC_STRT                 (1<<10)
#घोषणा LINK_INT_CYC_DONE                 (1<<9)
#घोषणा LINK_INT_CYC_PEND                 (1<<8)
#घोषणा LINK_INT_CYC_LOST                 (1<<7)
#घोषणा LINK_INT_CYC_ARB_FAILED           (1<<6)
#घोषणा LINK_INT_GRF_OVER_FLOW            (1<<5)
#घोषणा LINK_INT_ITF_UNDER_FLOW           (1<<4)
#घोषणा LINK_INT_ATF_UNDER_FLOW           (1<<3)
#घोषणा LINK_INT_IARB_FAILED              (1<<0)
