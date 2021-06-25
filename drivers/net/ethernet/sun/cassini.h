<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/* $Id: cassini.h,v 1.16 2004/08/17 21:15:16 zaumen Exp $
 * cassini.h: Definitions क्रम Sun Microप्रणालीs Cassini(+) ethernet driver.
 *
 * Copyright (C) 2004 Sun Microप्रणालीs Inc.
 * Copyright (c) 2003 Adrian Sun (asun@darksunrising.com)
 *
 * venकरोr id: 0x108E (Sun Microप्रणालीs, Inc.)
 * device id: 0xabba (Cassini)
 * revision ids: 0x01 = Cassini
 *               0x02 = Cassini rev 2
 *               0x10 = Cassini+
 *               0x11 = Cassini+ 0.2u
 *
 * venकरोr id: 0x100b (National Semiconductor)
 * device id: 0x0035 (DP83065/Saturn)
 * revision ids: 0x30 = Saturn B2
 *
 * rings are all offset from 0.
 *
 * there are two घड़ी करोमुख्यs:
 * PCI:  33/66MHz घड़ी
 * chip: 125MHz घड़ी
 */

#अगर_अघोषित _CASSINI_H
#घोषणा _CASSINI_H

/* cassini रेजिस्टर map: 2M memory mapped in 32-bit memory space accessible as
 * 32-bit words. there is no i/o port access. REG_ addresses are
 * shared between cassini and cassini+. REG_PLUS_ addresses only
 * appear in cassini+. REG_MINUS_ addresses only appear in cassini.
 */
#घोषणा CAS_ID_REV2          0x02
#घोषणा CAS_ID_REVPLUS       0x10
#घोषणा CAS_ID_REVPLUS02u    0x11
#घोषणा CAS_ID_REVSATURNB2   0x30

/** global resources **/

/* this रेजिस्टर sets the weights क्रम the weighted round robin arbiter. e.g.,
 * अगर rx weight == 1 and tx weight == 0, rx == 2x tx transfer credit
 * क्रम its next turn to access the pci bus.
 * map: 0x0 = x1, 0x1 = x2, 0x2 = x4, 0x3 = x8
 * DEFAULT: 0x0, SIZE: 5 bits
 */
#घोषणा  REG_CAWR	               0x0004  /* core arbitration weight */
#घोषणा    CAWR_RX_DMA_WEIGHT_SHIFT    0
#घोषणा    CAWR_RX_DMA_WEIGHT_MASK     0x03    /* [0:1] */
#घोषणा    CAWR_TX_DMA_WEIGHT_SHIFT    2
#घोषणा    CAWR_TX_DMA_WEIGHT_MASK     0x0C    /* [3:2] */
#घोषणा    CAWR_RR_DIS                 0x10    /* [4] */

/* अगर enabled, BIM can send bursts across PCI bus > cacheline size. burst
 * sizes determined by length of packet or descriptor transfer and the
 * max length allowed by the target.
 * DEFAULT: 0x0, SIZE: 1 bit
 */
#घोषणा  REG_INF_BURST                 0x0008  /* infinite burst enable reg */
#घोषणा    INF_BURST_EN                0x1     /* enable */

/* top level पूर्णांकerrupts [0-9] are स्वतः-cleared to 0 when the status
 * रेजिस्टर is पढ़ो. second level पूर्णांकerrupts [13 - 18] are cleared at
 * the source. tx completion रेजिस्टर 3 is replicated in [19 - 31]
 * DEFAULT: 0x00000000, SIZE: 29 bits
 */
#घोषणा  REG_INTR_STATUS               0x000C  /* पूर्णांकerrupt status रेजिस्टर */
#घोषणा    INTR_TX_INTME               0x00000001  /* frame w/ INT ME desc bit set
						      xferred from host queue to
						      TX FIFO */
#घोषणा    INTR_TX_ALL                 0x00000002  /* all xmit frames xferred पूर्णांकo
						      TX FIFO. i.e.,
						      TX Kick == TX complete. अगर
						      PACED_MODE set, then TX FIFO
						      also empty */
#घोषणा    INTR_TX_DONE                0x00000004  /* any frame xferred पूर्णांकo tx
						      FIFO */
#घोषणा    INTR_TX_TAG_ERROR           0x00000008  /* TX FIFO tag framing
						      corrupted. FATAL ERROR */
#घोषणा    INTR_RX_DONE                0x00000010  /* at least 1 frame xferred
						      from RX FIFO to host mem.
						      RX completion reg updated.
						      may be delayed by recv
						      पूर्णांकr blanking. */
#घोषणा    INTR_RX_BUF_UNAVAIL         0x00000020  /* no more receive buffers.
						      RX Kick == RX complete */
#घोषणा    INTR_RX_TAG_ERROR           0x00000040  /* RX FIFO tag framing
						      corrupted. FATAL ERROR */
#घोषणा    INTR_RX_COMP_FULL           0x00000080  /* no more room in completion
						      ring to post descriptors.
						      RX complete head incr to
						      almost reach RX complete
						      tail */
#घोषणा    INTR_RX_BUF_AE              0x00000100  /* less than the
						      programmable threshold #
						      of मुक्त descr avail क्रम
						      hw use */
#घोषणा    INTR_RX_COMP_AF             0x00000200  /* less than the
						      programmable threshold #
						      of descr spaces क्रम hw
						      use in completion descr
						      ring */
#घोषणा    INTR_RX_LEN_MISMATCH        0x00000400  /* len field from MAC !=
						      len of non-reassembly pkt
						      from fअगरo during DMA or
						      header parser provides TCP
						      header and payload size >
						      MAC packet size.
						      FATAL ERROR */
#घोषणा    INTR_SUMMARY                0x00001000  /* summary पूर्णांकerrupt bit. this
						      bit will be set अगर an पूर्णांकerrupt
						      generated on the pci bus. useful
						      when driver is polling क्रम
						      पूर्णांकerrupts */
#घोषणा    INTR_PCS_STATUS             0x00002000  /* PCS पूर्णांकerrupt status रेजिस्टर */
#घोषणा    INTR_TX_MAC_STATUS          0x00004000  /* TX MAC status रेजिस्टर has at
						      least 1 unmasked पूर्णांकerrupt set */
#घोषणा    INTR_RX_MAC_STATUS          0x00008000  /* RX MAC status रेजिस्टर has at
						      least 1 unmasked पूर्णांकerrupt set */
#घोषणा    INTR_MAC_CTRL_STATUS        0x00010000  /* MAC control status रेजिस्टर has
						      at least 1 unmasked पूर्णांकerrupt
						      set */
#घोषणा    INTR_MIF_STATUS             0x00020000  /* MIF status रेजिस्टर has at least
						      1 unmasked पूर्णांकerrupt set */
#घोषणा    INTR_PCI_ERROR_STATUS       0x00040000  /* PCI error status रेजिस्टर in the
						      BIF has at least 1 unmasked
						      पूर्णांकerrupt set */
#घोषणा    INTR_TX_COMP_3_MASK         0xFFF80000  /* mask क्रम TX completion
						      3 reg data */
#घोषणा    INTR_TX_COMP_3_SHIFT        19
#घोषणा    INTR_ERROR_MASK (INTR_MIF_STATUS | INTR_PCI_ERROR_STATUS | \
                            INTR_PCS_STATUS | INTR_RX_LEN_MISMATCH | \
                            INTR_TX_MAC_STATUS | INTR_RX_MAC_STATUS | \
                            INTR_TX_TAG_ERROR | INTR_RX_TAG_ERROR | \
                            INTR_MAC_CTRL_STATUS)

/* determines which status events will cause an पूर्णांकerrupt. layout same
 * as REG_INTR_STATUS.
 * DEFAULT: 0xFFFFFFFF, SIZE: 16 bits
 */
#घोषणा  REG_INTR_MASK                 0x0010  /* Interrupt mask */

/* top level पूर्णांकerrupt bits that are cleared during पढ़ो of REG_INTR_STATUS_ALIAS.
 * useful when driver is polling क्रम पूर्णांकerrupts. layout same as REG_INTR_MASK.
 * DEFAULT: 0x00000000, SIZE: 12 bits
 */
#घोषणा  REG_ALIAS_CLEAR               0x0014  /* alias clear mask
						  (used w/ status alias) */
/* same as REG_INTR_STATUS except that only bits cleared are those selected by
 * REG_ALIAS_CLEAR
 * DEFAULT: 0x00000000, SIZE: 29 bits
 */
#घोषणा  REG_INTR_STATUS_ALIAS         0x001C  /* पूर्णांकerrupt status alias
						  (selective clear) */

/* DEFAULT: 0x0, SIZE: 3 bits */
#घोषणा  REG_PCI_ERR_STATUS            0x1000  /* PCI error status */
#घोषणा    PCI_ERR_BADACK              0x01    /* reserved in Cassini+.
						  set अगर no ACK64# during ABS64 cycle
						  in Cassini. */
#घोषणा    PCI_ERR_DTRTO               0x02    /* delayed xaction समयout. set अगर
						  no पढ़ो retry after 2^15 घड़ीs */
#घोषणा    PCI_ERR_OTHER               0x04    /* other PCI errors */
#घोषणा    PCI_ERR_BIM_DMA_WRITE       0x08    /* BIM received 0 count DMA ग_लिखो req.
						  unused in Cassini. */
#घोषणा    PCI_ERR_BIM_DMA_READ        0x10    /* BIM received 0 count DMA पढ़ो req.
						  unused in Cassini. */
#घोषणा    PCI_ERR_BIM_DMA_TIMEOUT     0x20    /* BIM received 255 retries during
						  DMA. unused in cassini. */

/* mask क्रम PCI status events that will set PCI_ERR_STATUS. अगर cleared, event
 * causes an पूर्णांकerrupt to be generated.
 * DEFAULT: 0x7, SIZE: 3 bits
 */
#घोषणा  REG_PCI_ERR_STATUS_MASK       0x1004  /* PCI Error status mask */

/* used to configure PCI related parameters that are not in PCI config space.
 * DEFAULT: 0bxx000, SIZE: 5 bits
 */
#घोषणा  REG_BIM_CFG                0x1008  /* BIM Configuration */
#घोषणा    BIM_CFG_RESERVED0        0x001   /* reserved */
#घोषणा    BIM_CFG_RESERVED1        0x002   /* reserved */
#घोषणा    BIM_CFG_64BIT_DISABLE    0x004   /* disable 64-bit mode */
#घोषणा    BIM_CFG_66MHZ            0x008   /* (ro) 1 = 66MHz, 0 = < 66MHz */
#घोषणा    BIM_CFG_32BIT            0x010   /* (ro) 1 = 32-bit slot, 0 = 64-bit */
#घोषणा    BIM_CFG_DPAR_INTR_ENABLE 0x020   /* detected parity err enable */
#घोषणा    BIM_CFG_RMA_INTR_ENABLE  0x040   /* master पात पूर्णांकr enable */
#घोषणा    BIM_CFG_RTA_INTR_ENABLE  0x080   /* target पात पूर्णांकr enable */
#घोषणा    BIM_CFG_RESERVED2        0x100   /* reserved */
#घोषणा    BIM_CFG_BIM_DISABLE      0x200   /* stop BIM DMA. use beक्रमe global
					       reset. reserved in Cassini. */
#घोषणा    BIM_CFG_BIM_STATUS       0x400   /* (ro) 1 = BIM DMA suspended.
						  reserved in Cassini. */
#घोषणा    BIM_CFG_PERROR_BLOCK     0x800  /* block PERR# to pci bus. def: 0.
						 reserved in Cassini. */

/* DEFAULT: 0x00000000, SIZE: 32 bits */
#घोषणा  REG_BIM_DIAG                  0x100C  /* BIM Diagnostic */
#घोषणा    BIM_DIAG_MSTR_SM_MASK       0x3FFFFF00 /* PCI master controller state
						     machine bits [21:0] */
#घोषणा    BIM_DIAG_BRST_SM_MASK       0x7F    /* PCI burst controller state
						  machine bits [6:0] */

/* writing to SW_RESET_TX and SW_RESET_RX will issue a global
 * reset. poll until TX and RX पढ़ो back as 0's क्रम completion.
 */
#घोषणा  REG_SW_RESET                  0x1010  /* Software reset */
#घोषणा    SW_RESET_TX                 0x00000001  /* reset TX DMA engine. poll until
						      cleared to 0.  */
#घोषणा    SW_RESET_RX                 0x00000002  /* reset RX DMA engine. poll until
						      cleared to 0. */
#घोषणा    SW_RESET_RSTOUT             0x00000004  /* क्रमce RSTOUT# pin active (low).
						      resets PHY and anything अन्यथा
						      connected to RSTOUT#. RSTOUT#
						      is also activated by local PCI
						      reset when hot-swap is being
						      करोne. */
#घोषणा    SW_RESET_BLOCK_PCS_SLINK    0x00000008  /* अगर a global reset is करोne with
						      this bit set, PCS and SLINK
						      modules won't be reset.
						      i.e., link won't drop. */
#घोषणा    SW_RESET_BREQ_SM_MASK       0x00007F00  /* breq state machine [6:0] */
#घोषणा    SW_RESET_PCIARB_SM_MASK     0x00070000  /* pci arbitration state bits:
						      0b000: ARB_IDLE1
						      0b001: ARB_IDLE2
						      0b010: ARB_WB_ACK
						      0b011: ARB_WB_WAT
						      0b100: ARB_RB_ACK
						      0b101: ARB_RB_WAT
						      0b110: ARB_RB_END
						      0b111: ARB_WB_END */
#घोषणा    SW_RESET_RDPCI_SM_MASK      0x00300000  /* पढ़ो pci state bits:
						      0b00: RD_PCI_WAT
						      0b01: RD_PCI_RDY
						      0b11: RD_PCI_ACK */
#घोषणा    SW_RESET_RDARB_SM_MASK      0x00C00000  /* पढ़ो arbitration state bits:
						      0b00: AD_IDL_RX
						      0b01: AD_ACK_RX
						      0b10: AD_ACK_TX
						      0b11: AD_IDL_TX */
#घोषणा    SW_RESET_WRPCI_SM_MASK      0x06000000  /* ग_लिखो pci state bits
						      0b00: WR_PCI_WAT
						      0b01: WR_PCI_RDY
						      0b11: WR_PCI_ACK */
#घोषणा    SW_RESET_WRARB_SM_MASK      0x38000000  /* ग_लिखो arbitration state bits:
						      0b000: ARB_IDLE1
						      0b001: ARB_IDLE2
						      0b010: ARB_TX_ACK
						      0b011: ARB_TX_WAT
						      0b100: ARB_RX_ACK
						      0b110: ARB_RX_WAT */

/* Cassini only. 64-bit रेजिस्टर used to check PCI datapath. when पढ़ो,
 * value written has both lower and upper 32-bit halves rotated to the right
 * one bit position. e.g., FFFFFFFF FFFFFFFF -> 7FFFFFFF 7FFFFFFF
 */
#घोषणा  REG_MINUS_BIM_DATAPATH_TEST   0x1018  /* Cassini: BIM datapath test
						  Cassini+: reserved */

/* output enables are provided क्रम each device's chip select and क्रम the rest
 * of the outमाला_दो from cassini to its local bus devices. two sw programmable
 * bits are connected to general purpus control/status bits.
 * DEFAULT: 0x7
 */
#घोषणा  REG_BIM_LOCAL_DEV_EN          0x1020  /* BIM local device
						  output EN. शेष: 0x7 */
#घोषणा    BIM_LOCAL_DEV_PAD           0x01    /* address bus, RW संकेत, and
						  OE संकेत output enable on the
						  local bus पूर्णांकerface. these
						  are shared between both local
						  bus devices. tristate when 0. */
#घोषणा    BIM_LOCAL_DEV_PROM          0x02    /* PROM chip select */
#घोषणा    BIM_LOCAL_DEV_EXT           0x04    /* secondary local bus device chip
						  select output enable */
#घोषणा    BIM_LOCAL_DEV_SOFT_0        0x08    /* sw programmable ctrl bit 0 */
#घोषणा    BIM_LOCAL_DEV_SOFT_1        0x10    /* sw programmable ctrl bit 1 */
#घोषणा    BIM_LOCAL_DEV_HW_RESET      0x20    /* पूर्णांकernal hw reset. Cassini+ only. */

/* access 24 entry BIM पढ़ो and ग_लिखो buffers. put address in REG_BIM_BUFFER_ADDR
 * and पढ़ो/ग_लिखो from/to it REG_BIM_BUFFER_DATA_LOW and _DATA_HI.
 * _DATA_HI should be the last access of the sequence.
 * DEFAULT: undefined
 */
#घोषणा  REG_BIM_BUFFER_ADDR           0x1024  /* BIM buffer address. क्रम
						  purposes. */
#घोषणा    BIM_BUFFER_ADDR_MASK        0x3F    /* index (0 - 23) of buffer  */
#घोषणा    BIM_BUFFER_WR_SELECT        0x40    /* ग_लिखो buffer access = 1
						  पढ़ो buffer access = 0 */
/* DEFAULT: undefined */
#घोषणा  REG_BIM_BUFFER_DATA_LOW       0x1028  /* BIM buffer data low */
#घोषणा  REG_BIM_BUFFER_DATA_HI        0x102C  /* BIM buffer data high */

/* set BIM_RAM_BIST_START to start built-in self test क्रम BIM पढ़ो buffer.
 * bit स्वतः-clears when करोne with status पढ़ो from _SUMMARY and _PASS bits.
 */
#घोषणा  REG_BIM_RAM_BIST              0x102C  /* BIM RAM (पढ़ो buffer) BIST
						  control/status */
#घोषणा    BIM_RAM_BIST_RD_START       0x01    /* start BIST क्रम BIM पढ़ो buffer */
#घोषणा    BIM_RAM_BIST_WR_START       0x02    /* start BIST क्रम BIM ग_लिखो buffer.
						  Cassini only. reserved in
						  Cassini+. */
#घोषणा    BIM_RAM_BIST_RD_PASS        0x04    /* summary BIST pass status क्रम पढ़ो
						  buffer. */
#घोषणा    BIM_RAM_BIST_WR_PASS        0x08    /* summary BIST pass status क्रम ग_लिखो
						  buffer. Cassini only. reserved
						  in Cassini+. */
#घोषणा    BIM_RAM_BIST_RD_LOW_PASS    0x10    /* पढ़ो low bank passes BIST */
#घोषणा    BIM_RAM_BIST_RD_HI_PASS     0x20    /* पढ़ो high bank passes BIST */
#घोषणा    BIM_RAM_BIST_WR_LOW_PASS    0x40    /* ग_लिखो low bank passes BIST.
						  Cassini only. reserved in
						  Cassini+. */
#घोषणा    BIM_RAM_BIST_WR_HI_PASS     0x80    /* ग_लिखो high bank passes BIST.
						  Cassini only. reserved in
						  Cassini+. */

/* ASUN: i'm not sure what this does as it's not in the spec.
 * DEFAULT: 0xFC
 */
#घोषणा  REG_BIM_DIAG_MUX              0x1030  /* BIM diagnostic probe mux
						  select रेजिस्टर */

/* enable probe monitoring mode and select data appearing on the P_A* bus. bit
 * values क्रम _SEL_HI_MASK and _SEL_LOW_MASK:
 * 0x0: पूर्णांकernal probe[7:0] (pci arb state, wtc empty w, wtc full w, wtc empty w,
 *                           wtc empty r, post pci)
 * 0x1: पूर्णांकernal probe[15:8] (pci wbuf comp, pci wpkt comp, pci rbuf comp,
 *                            pci rpkt comp, txdma wr req, txdma wr ack,
 *			      txdma wr rdy, txdma wr xfr करोne)
 * 0x2: पूर्णांकernal probe[23:16] (txdma rd req, txdma rd ack, txdma rd rdy, rxdma rd,
 *                             rd arb state, rd pci state)
 * 0x3: पूर्णांकernal probe[31:24] (rxdma req, rxdma ack, rxdma rdy, wrarb state,
 *                             wrpci state)
 * 0x4: pci io probe[7:0]     0x5: pci io probe[15:8]
 * 0x6: pci io probe[23:16]   0x7: pci io probe[31:24]
 * 0x8: pci io probe[39:32]   0x9: pci io probe[47:40]
 * 0xa: pci io probe[55:48]   0xb: pci io probe[63:56]
 * the following are not available in Cassini:
 * 0xc: rx probe[7:0]         0xd: tx probe[7:0]
 * 0xe: hp probe[7:0] 	      0xf: mac probe[7:0]
 */
#घोषणा  REG_PLUS_PROBE_MUX_SELECT     0x1034 /* Cassini+: PROBE MUX SELECT */
#घोषणा    PROBE_MUX_EN                0x80000000 /* allow probe संकेतs to be
						     driven on local bus P_A[15:0]
						     क्रम debugging */
#घोषणा    PROBE_MUX_SUB_MUX_MASK      0x0000FF00 /* select sub module probe संकेतs:
						     0x03 = mac[1:0]
						     0x0C = rx[1:0]
						     0x30 = tx[1:0]
						     0xC0 = hp[1:0] */
#घोषणा    PROBE_MUX_SEL_HI_MASK       0x000000F0 /* select which module to appear
						     on P_A[15:8]. see above क्रम
						     values. */
#घोषणा    PROBE_MUX_SEL_LOW_MASK      0x0000000F /* select which module to appear
						     on P_A[7:0]. see above क्रम
						     values. */

/* values mean the same thing as REG_INTR_MASK excep that it's क्रम INTB.
 DEFAULT: 0x1F */
#घोषणा  REG_PLUS_INTR_MASK_1          0x1038 /* Cassini+: पूर्णांकerrupt mask
						 रेजिस्टर 2 क्रम INTB */
#घोषणा  REG_PLUS_INTRN_MASK(x)       (REG_PLUS_INTR_MASK_1 + ((x) - 1)*16)
/* bits correspond to both _MASK and _STATUS रेजिस्टरs. _ALT corresponds to
 * all of the alternate (2-4) INTR रेजिस्टरs जबतक _1 corresponds to only
 * _MASK_1 and _STATUS_1 रेजिस्टरs.
 * DEFAULT: 0x7 क्रम MASK रेजिस्टरs, 0x0 क्रम ALIAS_CLEAR रेजिस्टरs
 */
#घोषणा    INTR_RX_DONE_ALT              0x01
#घोषणा    INTR_RX_COMP_FULL_ALT         0x02
#घोषणा    INTR_RX_COMP_AF_ALT           0x04
#घोषणा    INTR_RX_BUF_UNAVAIL_1         0x08
#घोषणा    INTR_RX_BUF_AE_1              0x10 /* almost empty */
#घोषणा    INTRN_MASK_RX_EN              0x80
#घोषणा    INTRN_MASK_CLEAR_ALL          (INTR_RX_DONE_ALT | \
                                          INTR_RX_COMP_FULL_ALT | \
                                          INTR_RX_COMP_AF_ALT | \
                                          INTR_RX_BUF_UNAVAIL_1 | \
                                          INTR_RX_BUF_AE_1)
#घोषणा  REG_PLUS_INTR_STATUS_1        0x103C /* Cassini+: पूर्णांकerrupt status
						 रेजिस्टर 2 क्रम INTB. शेष: 0x1F */
#घोषणा  REG_PLUS_INTRN_STATUS(x)       (REG_PLUS_INTR_STATUS_1 + ((x) - 1)*16)
#घोषणा    INTR_STATUS_ALT_INTX_EN     0x80   /* generate INTX when one of the
						 flags are set. enables desc ring. */

#घोषणा  REG_PLUS_ALIAS_CLEAR_1        0x1040 /* Cassini+: alias clear mask
						 रेजिस्टर 2 क्रम INTB */
#घोषणा  REG_PLUS_ALIASN_CLEAR(x)      (REG_PLUS_ALIAS_CLEAR_1 + ((x) - 1)*16)

#घोषणा  REG_PLUS_INTR_STATUS_ALIAS_1  0x1044 /* Cassini+: पूर्णांकerrupt status
						 रेजिस्टर alias 2 क्रम INTB */
#घोषणा  REG_PLUS_INTRN_STATUS_ALIAS(x) (REG_PLUS_INTR_STATUS_ALIAS_1 + ((x) - 1)*16)

#घोषणा REG_SATURN_PCFG               0x106c /* pin configuration रेजिस्टर क्रम
						पूर्णांकegrated macphy */

#घोषणा   SATURN_PCFG_TLA             0x00000001 /* 1 = phy actled */
#घोषणा   SATURN_PCFG_FLA             0x00000002 /* 1 = phy link10led */
#घोषणा   SATURN_PCFG_CLA             0x00000004 /* 1 = phy link100led */
#घोषणा   SATURN_PCFG_LLA             0x00000008 /* 1 = phy link1000led */
#घोषणा   SATURN_PCFG_RLA             0x00000010 /* 1 = phy duplexled */
#घोषणा   SATURN_PCFG_PDS             0x00000020 /* phy debug mode.
						    0 = normal */
#घोषणा   SATURN_PCFG_MTP             0x00000080 /* test poपूर्णांक select */
#घोषणा   SATURN_PCFG_GMO             0x00000100 /* GMII observe. 1 =
						    GMII on SERDES pins क्रम
						    monitoring. */
#घोषणा   SATURN_PCFG_FSI             0x00000200 /* 1 = मुक्तze serdes/gmii. all
						    pins configed as outमाला_दो.
						    क्रम घातer saving when using
						    पूर्णांकernal phy. */
#घोषणा   SATURN_PCFG_LAD             0x00000800 /* 0 = mac core led ctrl
						    polarity from strapping
						    value.
						    1 = mac core led ctrl
						    polarity active low. */


/** transmit dma रेजिस्टरs **/
#घोषणा MAX_TX_RINGS_SHIFT            2
#घोषणा MAX_TX_RINGS                  (1 << MAX_TX_RINGS_SHIFT)
#घोषणा MAX_TX_RINGS_MASK             (MAX_TX_RINGS - 1)

/* TX configuration.
 * descr ring sizes size = 32 * (1 << n), n < 9. e.g., 0x8 = 8k. शेष: 0x8
 * DEFAULT: 0x3F000001
 */
#घोषणा  REG_TX_CFG                    0x2004  /* TX config */
#घोषणा    TX_CFG_DMA_EN               0x00000001  /* enable TX DMA. अगर cleared, DMA
						      will stop after xfer of current
						      buffer has been completed. */
#घोषणा    TX_CFG_FIFO_PIO_SEL         0x00000002  /* TX DMA FIFO can be
						      accessed w/ FIFO addr
						      and data रेजिस्टरs.
						      TX DMA should be
						      disabled. */
#घोषणा    TX_CFG_DESC_RING0_MASK      0x0000003C  /* # desc entries in
						      ring 1. */
#घोषणा    TX_CFG_DESC_RING0_SHIFT     2
#घोषणा    TX_CFG_DESC_RINGN_MASK(a)   (TX_CFG_DESC_RING0_MASK << (a)*4)
#घोषणा    TX_CFG_DESC_RINGN_SHIFT(a)  (TX_CFG_DESC_RING0_SHIFT + (a)*4)
#घोषणा    TX_CFG_PACED_MODE           0x00100000  /* TX_ALL only set after
						      TX FIFO becomes empty.
						      अगर 0, TX_ALL set
						      अगर descr queue empty. */
#घोषणा    TX_CFG_DMA_RDPIPE_DIS       0x01000000  /* always set to 1 */
#घोषणा    TX_CFG_COMPWB_Q1            0x02000000  /* completion ग_लिखोback happens at
						      the end of every packet kicked
						      through Q1. */
#घोषणा    TX_CFG_COMPWB_Q2            0x04000000  /* completion ग_लिखोback happens at
						      the end of every packet kicked
						      through Q2. */
#घोषणा    TX_CFG_COMPWB_Q3            0x08000000  /* completion ग_लिखोback happens at
						      the end of every packet kicked
						      through Q3 */
#घोषणा    TX_CFG_COMPWB_Q4            0x10000000  /* completion ग_लिखोback happens at
						      the end of every packet kicked
						      through Q4 */
#घोषणा    TX_CFG_INTR_COMPWB_DIS      0x20000000  /* disable pre-पूर्णांकerrupt completion
						      ग_लिखोback */
#घोषणा    TX_CFG_CTX_SEL_MASK         0xC0000000  /* selects tx test port
						      connection
						      0b00: tx mac req,
						            tx mac retry req,
							    tx ack and tx tag.
						      0b01: txdma rd req,
						            txdma rd ack,
							    txdma rd rdy,
							    txdma rd type0
						      0b11: txdma wr req,
						            txdma wr ack,
							    txdma wr rdy,
							    txdma wr xfr करोne. */
#घोषणा    TX_CFG_CTX_SEL_SHIFT        30

/* 11-bit counters that poपूर्णांक to next location in FIFO to be loaded/retrieved.
 * used क्रम diagnostics only.
 */
#घोषणा  REG_TX_FIFO_WRITE_PTR         0x2014  /* TX FIFO ग_लिखो poपूर्णांकer */
#घोषणा  REG_TX_FIFO_SHADOW_WRITE_PTR  0x2018  /* TX FIFO shaकरोw ग_लिखो
						  poपूर्णांकer. temp hold reg.
					          diagnostics only. */
#घोषणा  REG_TX_FIFO_READ_PTR          0x201C  /* TX FIFO पढ़ो poपूर्णांकer */
#घोषणा  REG_TX_FIFO_SHADOW_READ_PTR   0x2020  /* TX FIFO shaकरोw पढ़ो
						  poपूर्णांकer */

/* (ro) 11-bit up/करोwn counter w/ # of frames currently in TX FIFO */
#घोषणा  REG_TX_FIFO_PKT_CNT           0x2024  /* TX FIFO packet counter */

/* current state of all state machines in TX */
#घोषणा  REG_TX_SM_1                   0x2028  /* TX state machine reg #1 */
#घोषणा    TX_SM_1_CHAIN_MASK          0x000003FF   /* chaining state machine */
#घोषणा    TX_SM_1_CSUM_MASK           0x00000C00   /* checksum state machine */
#घोषणा    TX_SM_1_FIFO_LOAD_MASK      0x0003F000   /* FIFO load state machine.
						       = 0x01 when TX disabled. */
#घोषणा    TX_SM_1_FIFO_UNLOAD_MASK    0x003C0000   /* FIFO unload state machine */
#घोषणा    TX_SM_1_CACHE_MASK          0x03C00000   /* desc. prefetch cache controller
						       state machine */
#घोषणा    TX_SM_1_CBQ_ARB_MASK        0xF8000000   /* CBQ arbiter state machine */

#घोषणा  REG_TX_SM_2                   0x202C  /* TX state machine reg #2 */
#घोषणा    TX_SM_2_COMP_WB_MASK        0x07    /* completion ग_लिखोback sm */
#घोषणा	   TX_SM_2_SUB_LOAD_MASK       0x38    /* sub load state machine */
#घोषणा	   TX_SM_2_KICK_MASK           0xC0    /* kick state machine */

/* 64-bit poपूर्णांकer to the transmit data buffer. only the 50 LSB are incremented
 * जबतक the upper 23 bits are taken from the TX descriptor
 */
#घोषणा  REG_TX_DATA_PTR_LOW           0x2030  /* TX data poपूर्णांकer low */
#घोषणा  REG_TX_DATA_PTR_HI            0x2034  /* TX data poपूर्णांकer high */

/* 13 bit रेजिस्टरs written by driver w/ descriptor value that follows
 * last valid xmit descriptor. kick # and complete # values are used by
 * the xmit dma engine to control tx descr fetching. अगर > 1 valid
 * tx descr is available within the cache line being पढ़ो, cassini will
 * पूर्णांकernally cache up to 4 of them. 0 on reset. _KICK = rw, _COMP = ro.
 */
#घोषणा  REG_TX_KICK0                  0x2038  /* TX kick reg #1 */
#घोषणा  REG_TX_KICKN(x)               (REG_TX_KICK0 + (x)*4)
#घोषणा  REG_TX_COMP0                  0x2048  /* TX completion reg #1 */
#घोषणा  REG_TX_COMPN(x)               (REG_TX_COMP0 + (x)*4)

/* values of TX_COMPLETE_1-4 are written. each completion रेजिस्टर
 * is 2bytes in size and contiguous. 8B allocation w/ 8B alignment.
 * NOTE: completion reg values are only written back prior to TX_INTME and
 * TX_ALL पूर्णांकerrupts. at all other बार, the most up-to-date index values
 * should be obtained from the REG_TX_COMPLETE_# रेजिस्टरs.
 * here's the layout:
 * offset from base addr      completion # byte
 *           0                TX_COMPLETE_1_MSB
 *	     1                TX_COMPLETE_1_LSB
 *           2                TX_COMPLETE_2_MSB
 *	     3                TX_COMPLETE_2_LSB
 *           4                TX_COMPLETE_3_MSB
 *	     5                TX_COMPLETE_3_LSB
 *           6                TX_COMPLETE_4_MSB
 *	     7                TX_COMPLETE_4_LSB
 */
#घोषणा  TX_COMPWB_SIZE             8
#घोषणा  REG_TX_COMPWB_DB_LOW       0x2058  /* TX completion ग_लिखो back
					       base low */
#घोषणा  REG_TX_COMPWB_DB_HI        0x205C  /* TX completion ग_लिखो back
					       base high */
#घोषणा    TX_COMPWB_MSB_MASK       0x00000000000000FFULL
#घोषणा    TX_COMPWB_MSB_SHIFT      0
#घोषणा    TX_COMPWB_LSB_MASK       0x000000000000FF00ULL
#घोषणा    TX_COMPWB_LSB_SHIFT      8
#घोषणा    TX_COMPWB_NEXT(x)        ((x) >> 16)

/* 53 MSB used as base address. 11 LSB assumed to be 0. TX desc poपूर्णांकer must
 * be 2KB-aligned. */
#घोषणा  REG_TX_DB0_LOW         0x2060  /* TX descriptor base low #1 */
#घोषणा  REG_TX_DB0_HI          0x2064  /* TX descriptor base hi #1 */
#घोषणा  REG_TX_DBN_LOW(x)      (REG_TX_DB0_LOW + (x)*8)
#घोषणा  REG_TX_DBN_HI(x)       (REG_TX_DB0_HI + (x)*8)

/* 16-bit रेजिस्टरs hold weights क्रम the weighted round-robin of the
 * four CBQ TX descr rings. weights correspond to # bytes xferred from
 * host to TXFIFO in a round of WRR arbitration. can be set
 * dynamically with new weights set upon completion of the current
 * packet transfer from host memory to TXFIFO. a dummy ग_लिखो to any of
 * these रेजिस्टरs causes a queue1 pre-emption with all historical bw
 * deficit data reset to 0 (useful when congestion requires a
 * pre-emption/re-allocation of network bandwidth
 */
#घोषणा  REG_TX_MAXBURST_0             0x2080  /* TX MaxBurst #1 */
#घोषणा  REG_TX_MAXBURST_1             0x2084  /* TX MaxBurst #2 */
#घोषणा  REG_TX_MAXBURST_2             0x2088  /* TX MaxBurst #3 */
#घोषणा  REG_TX_MAXBURST_3             0x208C  /* TX MaxBurst #4 */

/* diagnostics access to any TX FIFO location. every access is 65
 * bits.  _DATA_LOW = 32 LSB, _DATA_HI_T1/T0 = 32 MSB. _TAG = tag bit.
 * writing _DATA_HI_T0 sets tag bit low, writing _DATA_HI_T1 sets tag
 * bit high.  TX_FIFO_PIO_SEL must be set क्रम TX FIFO PIO access. अगर
 * TX FIFO data पूर्णांकegrity is desired, TX DMA should be
 * disabled. _DATA_HI_Tx should be the last access of the sequence.
 */
#घोषणा  REG_TX_FIFO_ADDR              0x2104  /* TX FIFO address */
#घोषणा  REG_TX_FIFO_TAG               0x2108  /* TX FIFO tag */
#घोषणा  REG_TX_FIFO_DATA_LOW          0x210C  /* TX FIFO data low */
#घोषणा  REG_TX_FIFO_DATA_HI_T1        0x2110  /* TX FIFO data high t1 */
#घोषणा  REG_TX_FIFO_DATA_HI_T0        0x2114  /* TX FIFO data high t0 */
#घोषणा  REG_TX_FIFO_SIZE              0x2118  /* (ro) TX FIFO size = 0x090 = 9KB */

/* 9-bit रेजिस्टर controls BIST of TX FIFO. bit set indicates that the BIST
 * passed क्रम the specअगरied memory
 */
#घोषणा  REG_TX_RAMBIST                0x211C /* TX RAMBIST control/status */
#घोषणा    TX_RAMBIST_STATE            0x01C0 /* progress state of RAMBIST
						 controller state machine */
#घोषणा    TX_RAMBIST_RAM33A_PASS      0x0020 /* RAM33A passed */
#घोषणा    TX_RAMBIST_RAM32A_PASS      0x0010 /* RAM32A passed */
#घोषणा    TX_RAMBIST_RAM33B_PASS      0x0008 /* RAM33B passed */
#घोषणा    TX_RAMBIST_RAM32B_PASS      0x0004 /* RAM32B passed */
#घोषणा    TX_RAMBIST_SUMMARY          0x0002 /* all RAM passed */
#घोषणा    TX_RAMBIST_START            0x0001 /* ग_लिखो 1 to start BIST. self
						 clears on completion. */

/** receive dma रेजिस्टरs **/
#घोषणा MAX_RX_DESC_RINGS              2
#घोषणा MAX_RX_COMP_RINGS              4

/* receive DMA channel configuration. शेष: 0x80910
 * मुक्त ring size       = (1 << n)*32  -> [32 - 8k]
 * completion ring size = (1 << n)*128 -> [128 - 32k], n < 9
 * DEFAULT: 0x80910
 */
#घोषणा  REG_RX_CFG                     0x4000  /* RX config */
#घोषणा    RX_CFG_DMA_EN                0x00000001 /* enable RX DMA. 0 stops
							 channel as soon as current
							 frame xfer has completed.
							 driver should disable MAC
							 क्रम 200ms beक्रमe disabling
							 RX */
#घोषणा    RX_CFG_DESC_RING_MASK        0x0000001E /* # desc entries in RX
							 मुक्त desc ring.
							 def: 0x8 = 8k */
#घोषणा    RX_CFG_DESC_RING_SHIFT       1
#घोषणा    RX_CFG_COMP_RING_MASK        0x000001E0 /* # desc entries in RX complete
							 ring. def: 0x8 = 32k */
#घोषणा    RX_CFG_COMP_RING_SHIFT       5
#घोषणा    RX_CFG_BATCH_DIS             0x00000200 /* disable receive desc
						      batching. def: 0x0 =
						      enabled */
#घोषणा    RX_CFG_SWIVEL_MASK           0x00001C00 /* byte offset of the 1st
						      data byte of the packet
						      w/in 8 byte boundares.
						      this swivels the data
						      DMA'ed to header
						      buffers, jumbo buffers
						      when header split is not
						      requested and MTU sized
						      buffers. def: 0x2 */
#घोषणा    RX_CFG_SWIVEL_SHIFT          10

/* cassini+ only */
#घोषणा    RX_CFG_DESC_RING1_MASK       0x000F0000 /* # of desc entries in
							 RX मुक्त desc ring 2.
							 def: 0x8 = 8k */
#घोषणा    RX_CFG_DESC_RING1_SHIFT      16


/* the page size रेजिस्टर allows cassini chips to करो the following with
 * received data:
 * [--------------------------------------------------------------] page
 * [off][buf1][pad][off][buf2][pad][off][buf3][pad][off][buf4][pad]
 * |--------------| = PAGE_SIZE_BUFFER_STRIDE
 * page = PAGE_SIZE
 * offset = PAGE_SIZE_MTU_OFF
 * क्रम the above example, MTU_BUFFER_COUNT = 4.
 * NOTE: as is apparent, you need to ensure that the following holds:
 * MTU_BUFFER_COUNT <= PAGE_SIZE/PAGE_SIZE_BUFFER_STRIDE
 * DEFAULT: 0x48002002 (8k pages)
 */
#घोषणा  REG_RX_PAGE_SIZE               0x4004  /* RX page size */
#घोषणा    RX_PAGE_SIZE_MASK            0x00000003 /* size of pages poपूर्णांकed to
						      by receive descriptors.
						      अगर jumbo buffers are
						      supported the page size
						      should not be < 8k.
						      0b00 = 2k, 0b01 = 4k
						      0b10 = 8k, 0b11 = 16k
						      DEFAULT: 8k */
#घोषणा    RX_PAGE_SIZE_SHIFT           0
#घोषणा    RX_PAGE_SIZE_MTU_COUNT_MASK  0x00007800 /* # of MTU buffers the hw
						      packs पूर्णांकo a page.
						      DEFAULT: 4 */
#घोषणा    RX_PAGE_SIZE_MTU_COUNT_SHIFT 11
#घोषणा    RX_PAGE_SIZE_MTU_STRIDE_MASK 0x18000000 /* # of bytes that separate
							 each MTU buffer +
							 offset from each
							 other.
							 0b00 = 1k, 0b01 = 2k
							 0b10 = 4k, 0b11 = 8k
							 DEFAULT: 0x1 */
#घोषणा    RX_PAGE_SIZE_MTU_STRIDE_SHIFT 27
#घोषणा    RX_PAGE_SIZE_MTU_OFF_MASK    0xC0000000 /* offset in each page that
						      hw ग_लिखोs the MTU buffer
						      पूर्णांकo.
						      0b00 = 0,
						      0b01 = 64 bytes
						      0b10 = 96, 0b11 = 128
						      DEFAULT: 0x1 */
#घोषणा    RX_PAGE_SIZE_MTU_OFF_SHIFT   30

/* 11-bit counter poपूर्णांकs to next location in RX FIFO to be loaded/पढ़ो.
 * shaकरोw ग_लिखो poपूर्णांकers enable retries in हाल of early receive पातs.
 * DEFAULT: 0x0. generated on 64-bit boundaries.
 */
#घोषणा  REG_RX_FIFO_WRITE_PTR             0x4008  /* RX FIFO ग_लिखो poपूर्णांकer */
#घोषणा  REG_RX_FIFO_READ_PTR              0x400C  /* RX FIFO पढ़ो poपूर्णांकer */
#घोषणा  REG_RX_IPP_FIFO_SHADOW_WRITE_PTR  0x4010  /* RX IPP FIFO shaकरोw ग_लिखो
						      poपूर्णांकer */
#घोषणा  REG_RX_IPP_FIFO_SHADOW_READ_PTR   0x4014  /* RX IPP FIFO shaकरोw पढ़ो
						      poपूर्णांकer */
#घोषणा  REG_RX_IPP_FIFO_READ_PTR          0x400C  /* RX IPP FIFO पढ़ो
						      poपूर्णांकer. (8-bit counter) */

/* current state of RX DMA state engines + other info
 * DEFAULT: 0x0
 */
#घोषणा  REG_RX_DEBUG                      0x401C  /* RX debug */
#घोषणा    RX_DEBUG_LOAD_STATE_MASK        0x0000000F /* load state machine w/ MAC:
							 0x0 = idle,   0x1 = load_bop
							 0x2 = load 1, 0x3 = load 2
							 0x4 = load 3, 0x5 = load 4
							 0x6 = last detect
							 0x7 = रुको req
							 0x8 = रुको req statuss 1st
							 0x9 = load st
							 0xa = bubble mac
							 0xb = error */
#घोषणा    RX_DEBUG_LM_STATE_MASK          0x00000070 /* load state machine w/ HP and
							 RX FIFO:
							 0x0 = idle,   0x1 = hp xfr
							 0x2 = रुको hp पढ़ोy
							 0x3 = रुको flow code
							 0x4 = fअगरo xfer
							 0x5 = make status
							 0x6 = csum पढ़ोy
							 0x7 = error */
#घोषणा    RX_DEBUG_FC_STATE_MASK          0x000000180 /* flow control state machine
							 w/ MAC:
							 0x0 = idle
							 0x1 = रुको xoff ack
							 0x2 = रुको xon
							 0x3 = रुको xon ack */
#घोषणा    RX_DEBUG_DATA_STATE_MASK        0x000001E00 /* unload data state machine
							 states:
							 0x0 = idle data
							 0x1 = header begin
							 0x2 = xfer header
							 0x3 = xfer header ld
							 0x4 = mtu begin
							 0x5 = xfer mtu
							 0x6 = xfer mtu ld
							 0x7 = jumbo begin
							 0x8 = xfer jumbo
							 0x9 = xfer jumbo ld
							 0xa = reas begin
							 0xb = xfer reas
							 0xc = flush tag
							 0xd = xfer reas ld
							 0xe = error
							 0xf = bubble idle */
#घोषणा    RX_DEBUG_DESC_STATE_MASK        0x0001E000 /* unload desc state machine
							 states:
							 0x0 = idle desc
							 0x1 = रुको ack
							 0x9 = रुको ack 2
							 0x2 = fetch desc 1
							 0xa = fetch desc 2
							 0x3 = load ptrs
							 0x4 = रुको dma
							 0x5 = रुको ack batch
							 0x6 = post batch
							 0x7 = xfr करोne */
#घोषणा    RX_DEBUG_INTR_READ_PTR_MASK     0x30000000 /* पूर्णांकerrupt पढ़ो ptr of the
							 पूर्णांकerrupt queue */
#घोषणा    RX_DEBUG_INTR_WRITE_PTR_MASK    0xC0000000 /* पूर्णांकerrupt ग_लिखो poपूर्णांकer
							 of the पूर्णांकerrupt queue */

/* flow control frames are emitted using two PAUSE thresholds:
 * XOFF PAUSE uses छोड़ो समय value pre-programmed in the Send PAUSE MAC reg
 * XON PAUSE uses a छोड़ो समय of 0. granularity of threshold is 64bytes.
 * PAUSE thresholds defined in terms of FIFO occupancy and may be translated
 * पूर्णांकo FIFO vacancy using RX_FIFO_SIZE. setting ON will trigger XON frames
 * when FIFO reaches 0. OFF threshold should not be > size of RX FIFO. max
 * value is is 0x6F.
 * DEFAULT: 0x00078
 */
#घोषणा  REG_RX_PAUSE_THRESH               0x4020  /* RX छोड़ो thresholds */
#घोषणा    RX_PAUSE_THRESH_QUANTUM         64
#घोषणा    RX_PAUSE_THRESH_OFF_MASK        0x000001FF /* XOFF PAUSE emitted when
							 RX FIFO occupancy >
							 value*64B */
#घोषणा    RX_PAUSE_THRESH_OFF_SHIFT       0
#घोषणा    RX_PAUSE_THRESH_ON_MASK         0x001FF000 /* XON PAUSE emitted after
							 emitting XOFF PAUSE when RX
							 FIFO occupancy falls below
							 this value*64B. must be
							 < XOFF threshold. अगर =
							 RX_FIFO_SIZE< XON frames are
							 never emitted. */
#घोषणा    RX_PAUSE_THRESH_ON_SHIFT        12

/* 13-bit रेजिस्टर used to control RX desc fetching and पूर्णांकr generation. अगर 4+
 * valid RX descriptors are available, Cassini will पढ़ो 4 at a समय.
 * writing N means that all desc up to *but* excluding N are available. N must
 * be a multiple of 4 (N % 4 = 0). first desc should be cache-line aligned.
 * DEFAULT: 0 on reset
 */
#घोषणा  REG_RX_KICK                    0x4024  /* RX kick reg */

/* 8KB aligned 64-bit poपूर्णांकer to the base of the RX मुक्त/completion rings.
 * lower 13 bits of the low रेजिस्टर are hard-wired to 0.
 */
#घोषणा  REG_RX_DB_LOW                     0x4028  /* RX descriptor ring
							 base low */
#घोषणा  REG_RX_DB_HI                      0x402C  /* RX descriptor ring
							 base hi */
#घोषणा  REG_RX_CB_LOW                     0x4030  /* RX completion ring
							 base low */
#घोषणा  REG_RX_CB_HI                      0x4034  /* RX completion ring
							 base hi */
/* 13-bit रेजिस्टर indicate desc used by cassini क्रम receive frames. used
 * क्रम diagnostic purposes.
 * DEFAULT: 0 on reset
 */
#घोषणा  REG_RX_COMP                       0x4038  /* (ro) RX completion */

/* HEAD and TAIL are used to control RX desc posting and पूर्णांकerrupt
 * generation.  hw moves the head रेजिस्टर to pass ownership to sw. sw
 * moves the tail रेजिस्टर to pass ownership back to hw. to give all
 * entries to hw, set TAIL = HEAD.  अगर HEAD and TAIL indicate that no
 * more entries are available, DMA will छोड़ो and an पूर्णांकerrupt will be
 * generated to indicate no more entries are available.  sw can use
 * this पूर्णांकerrupt to reduce the # of बार it must update the
 * completion tail रेजिस्टर.
 * DEFAULT: 0 on reset
 */
#घोषणा  REG_RX_COMP_HEAD                  0x403C  /* RX completion head */
#घोषणा  REG_RX_COMP_TAIL                  0x4040  /* RX completion tail */

/* values used क्रम receive पूर्णांकerrupt blanking. loaded each समय the ISR is पढ़ो
 * DEFAULT: 0x00000000
 */
#घोषणा  REG_RX_BLANK                      0x4044  /* RX blanking रेजिस्टर
							 क्रम ISR पढ़ो */
#घोषणा    RX_BLANK_INTR_PKT_MASK          0x000001FF /* RX_DONE पूर्णांकr निश्चितed अगर
							 this many sets of completion
							 ग_लिखोbacks (up to 2 packets)
							 occur since the last समय
							 the ISR was पढ़ो. 0 = no
							 packet blanking */
#घोषणा    RX_BLANK_INTR_PKT_SHIFT         0
#घोषणा    RX_BLANK_INTR_TIME_MASK         0x3FFFF000 /* RX_DONE पूर्णांकerrupt निश्चितed
							 अगर that many घड़ीs were
							 counted since last समय the
							 ISR was पढ़ो.
							 each count is 512 core
							 घड़ीs (125MHz). 0 = no
							 समय blanking */
#घोषणा    RX_BLANK_INTR_TIME_SHIFT        12

/* values used क्रम पूर्णांकerrupt generation based on threshold values of how
 * many मुक्त desc and completion entries are available क्रम hw use.
 * DEFAULT: 0x00000000
 */
#घोषणा  REG_RX_AE_THRESH                  0x4048  /* RX almost empty
							 thresholds */
#घोषणा    RX_AE_THRESH_FREE_MASK          0x00001FFF /* RX_BUF_AE will be
							 generated अगर # desc
							 avail क्रम hw use <=
							 # */
#घोषणा    RX_AE_THRESH_FREE_SHIFT         0
#घोषणा    RX_AE_THRESH_COMP_MASK          0x0FFFE000 /* RX_COMP_AE will be
							 generated अगर # of
							 completion entries
							 avail क्रम hw use <=
							 # */
#घोषणा    RX_AE_THRESH_COMP_SHIFT         13

/* probabilities क्रम अक्रमom early drop (RED) thresholds on a FIFO threshold
 * basis. probability should increase when the FIFO level increases. control
 * packets are never dropped and not counted in stats. probability programmed
 * on a 12.5% granularity. e.g., 0x1 = 1/8 packets dropped.
 * DEFAULT: 0x00000000
 */
#घोषणा  REG_RX_RED                      0x404C  /* RX अक्रमom early detect enable */
#घोषणा    RX_RED_4K_6K_FIFO_MASK        0x000000FF /*  4KB < FIFO thresh < 6KB */
#घोषणा    RX_RED_6K_8K_FIFO_MASK        0x0000FF00 /*  6KB < FIFO thresh < 8KB */
#घोषणा    RX_RED_8K_10K_FIFO_MASK       0x00FF0000 /*  8KB < FIFO thresh < 10KB */
#घोषणा    RX_RED_10K_12K_FIFO_MASK      0xFF000000 /* 10KB < FIFO thresh < 12KB */

/* FIFO fullness levels क्रम RX FIFO, RX control FIFO, and RX IPP FIFO.
 * RX control FIFO = # of packets in RX FIFO.
 * DEFAULT: 0x0
 */
#घोषणा  REG_RX_FIFO_FULLNESS              0x4050  /* (ro) RX FIFO fullness */
#घोषणा    RX_FIFO_FULLNESS_RX_FIFO_MASK   0x3FF80000 /* level w/ 8B granularity */
#घोषणा    RX_FIFO_FULLNESS_IPP_FIFO_MASK  0x0007FF00 /* level w/ 8B granularity */
#घोषणा    RX_FIFO_FULLNESS_RX_PKT_MASK    0x000000FF /* # packets in RX FIFO */
#घोषणा  REG_RX_IPP_PACKET_COUNT           0x4054  /* RX IPP packet counter */
#घोषणा  REG_RX_WORK_DMA_PTR_LOW           0x4058  /* RX working DMA ptr low */
#घोषणा  REG_RX_WORK_DMA_PTR_HI            0x405C  /* RX working DMA ptr
						      high */

/* BIST testing ro RX FIFO, RX control FIFO, and RX IPP FIFO. only RX BIST
 * START/COMPLETE is ग_लिखोable. START will clear when the BIST has completed
 * checking all 17 RAMS.
 * DEFAULT: 0bxxxx xxxxx xxxx xxxx xxxx x000 0000 0000 00x0
 */
#घोषणा  REG_RX_BIST                       0x4060  /* (ro) RX BIST */
#घोषणा    RX_BIST_32A_PASS                0x80000000 /* RX FIFO 32A passed */
#घोषणा    RX_BIST_33A_PASS                0x40000000 /* RX FIFO 33A passed */
#घोषणा    RX_BIST_32B_PASS                0x20000000 /* RX FIFO 32B passed */
#घोषणा    RX_BIST_33B_PASS                0x10000000 /* RX FIFO 33B passed */
#घोषणा    RX_BIST_32C_PASS                0x08000000 /* RX FIFO 32C passed */
#घोषणा    RX_BIST_33C_PASS                0x04000000 /* RX FIFO 33C passed */
#घोषणा    RX_BIST_IPP_32A_PASS            0x02000000 /* RX IPP FIFO 33B passed */
#घोषणा    RX_BIST_IPP_33A_PASS            0x01000000 /* RX IPP FIFO 33A passed */
#घोषणा    RX_BIST_IPP_32B_PASS            0x00800000 /* RX IPP FIFO 32B passed */
#घोषणा    RX_BIST_IPP_33B_PASS            0x00400000 /* RX IPP FIFO 33B passed */
#घोषणा    RX_BIST_IPP_32C_PASS            0x00200000 /* RX IPP FIFO 32C passed */
#घोषणा    RX_BIST_IPP_33C_PASS            0x00100000 /* RX IPP FIFO 33C passed */
#घोषणा    RX_BIST_CTRL_32_PASS            0x00800000 /* RX CTRL FIFO 32 passed */
#घोषणा    RX_BIST_CTRL_33_PASS            0x00400000 /* RX CTRL FIFO 33 passed */
#घोषणा    RX_BIST_REAS_26A_PASS           0x00200000 /* RX Reas 26A passed */
#घोषणा    RX_BIST_REAS_26B_PASS           0x00100000 /* RX Reas 26B passed */
#घोषणा    RX_BIST_REAS_27_PASS            0x00080000 /* RX Reas 27 passed */
#घोषणा    RX_BIST_STATE_MASK              0x00078000 /* BIST state machine */
#घोषणा    RX_BIST_SUMMARY                 0x00000002 /* when BIST complete,
							 summary pass bit
							 contains AND of BIST
							 results of all 16
							 RAMS */
#घोषणा    RX_BIST_START                   0x00000001 /* ग_लिखो 1 to start
							 BIST. self clears
							 on completion. */

/* next location in RX CTRL FIFO that will be loaded w/ data from RX IPP/पढ़ो
 * from to retrieve packet control info.
 * DEFAULT: 0
 */
#घोषणा  REG_RX_CTRL_FIFO_WRITE_PTR        0x4064  /* (ro) RX control FIFO
						      ग_लिखो ptr */
#घोषणा  REG_RX_CTRL_FIFO_READ_PTR         0x4068  /* (ro) RX control FIFO पढ़ो
						      ptr */

/* receive पूर्णांकerrupt blanking. loaded each समय पूर्णांकerrupt alias रेजिस्टर is
 * पढ़ो.
 * DEFAULT: 0x0
 */
#घोषणा  REG_RX_BLANK_ALIAS_READ           0x406C  /* RX blanking रेजिस्टर क्रम
						      alias पढ़ो */
#घोषणा    RX_BAR_INTR_PACKET_MASK         0x000001FF /* निश्चित RX_DONE अगर #
							 completion ग_लिखोbacks
							 > # since last ISR
							 पढ़ो. 0 = no
							 blanking. up to 2
							 packets per
							 completion wb. */
#घोषणा    RX_BAR_INTR_TIME_MASK           0x3FFFF000 /* निश्चित RX_DONE अगर #
							 घड़ीs > # since last
							 ISR पढ़ो. each count
							 is 512 core घड़ीs
							 (125MHz). 0 = no
							 blanking. */

/* diagnostic access to RX FIFO. 32 LSB accessed via DATA_LOW. 32 MSB accessed
 * via DATA_HI_T0 or DATA_HI_T1. TAG पढ़ोs the tag bit. writing HI_T0
 * will unset the tag bit जबतक writing HI_T1 will set the tag bit. to reset
 * to normal operation after diagnostics, ग_लिखो to address location 0x0.
 * RX_DMA_EN bit must be set to 0x0 क्रम RX FIFO PIO access. DATA_HI should
 * be the last ग_लिखो access of a ग_लिखो sequence.
 * DEFAULT: undefined
 */
#घोषणा  REG_RX_FIFO_ADDR                  0x4080  /* RX FIFO address */
#घोषणा  REG_RX_FIFO_TAG                   0x4084  /* RX FIFO tag */
#घोषणा  REG_RX_FIFO_DATA_LOW              0x4088  /* RX FIFO data low */
#घोषणा  REG_RX_FIFO_DATA_HI_T0            0x408C  /* RX FIFO data high T0 */
#घोषणा  REG_RX_FIFO_DATA_HI_T1            0x4090  /* RX FIFO data high T1 */

/* diagnostic assess to RX CTRL FIFO. 8-bit FIFO_ADDR holds address of
 * 81 bit control entry and 6 bit flow id. LOW and MID are both 32-bit
 * accesses. HI is 7-bits with 6-bit flow id and 1 bit control
 * word. RX_DMA_EN must be 0 क्रम RX CTRL FIFO PIO access. DATA_HI
 * should be last ग_लिखो access of the ग_लिखो sequence.
 * DEFAULT: undefined
 */
#घोषणा  REG_RX_CTRL_FIFO_ADDR             0x4094  /* RX Control FIFO and
						      Batching FIFO addr */
#घोषणा  REG_RX_CTRL_FIFO_DATA_LOW         0x4098  /* RX Control FIFO data
						      low */
#घोषणा  REG_RX_CTRL_FIFO_DATA_MID         0x409C  /* RX Control FIFO data
						      mid */
#घोषणा  REG_RX_CTRL_FIFO_DATA_HI          0x4100  /* RX Control FIFO data
						      hi and flow id */
#घोषणा    RX_CTRL_FIFO_DATA_HI_CTRL       0x0001  /* upper bit of ctrl word */
#घोषणा    RX_CTRL_FIFO_DATA_HI_FLOW_MASK  0x007E  /* flow id */

/* diagnostic access to RX IPP FIFO. same semantics as RX_FIFO.
 * DEFAULT: undefined
 */
#घोषणा  REG_RX_IPP_FIFO_ADDR              0x4104  /* RX IPP FIFO address */
#घोषणा  REG_RX_IPP_FIFO_TAG               0x4108  /* RX IPP FIFO tag */
#घोषणा  REG_RX_IPP_FIFO_DATA_LOW          0x410C  /* RX IPP FIFO data low */
#घोषणा  REG_RX_IPP_FIFO_DATA_HI_T0        0x4110  /* RX IPP FIFO data high
						      T0 */
#घोषणा  REG_RX_IPP_FIFO_DATA_HI_T1        0x4114  /* RX IPP FIFO data high
						      T1 */

/* 64-bit poपूर्णांकer to receive data buffer in host memory used क्रम headers and
 * small packets. MSB in high रेजिस्टर. loaded by DMA state machine and
 * increments as DMA ग_लिखोs receive data. only 50 LSB are incremented. top
 * 13 bits taken from RX descriptor.
 * DEFAULT: undefined
 */
#घोषणा  REG_RX_HEADER_PAGE_PTR_LOW        0x4118  /* (ro) RX header page ptr
						      low */
#घोषणा  REG_RX_HEADER_PAGE_PTR_HI         0x411C  /* (ro) RX header page ptr
						      high */
#घोषणा  REG_RX_MTU_PAGE_PTR_LOW           0x4120  /* (ro) RX MTU page poपूर्णांकer
						      low */
#घोषणा  REG_RX_MTU_PAGE_PTR_HI            0x4124  /* (ro) RX MTU page poपूर्णांकer
						      high */

/* PIO diagnostic access to RX reassembly DMA Table RAM. 6-bit रेजिस्टर holds
 * one of 64 79-bit locations in the RX Reassembly DMA table and the addr of
 * one of the 64 byte locations in the Batching table. LOW holds 32 LSB.
 * MID holds the next 32 LSB. HIGH holds the 15 MSB. RX_DMA_EN must be set
 * to 0 क्रम PIO access. DATA_HIGH should be last ग_लिखो of ग_लिखो sequence.
 * layout:
 * reassmbl ptr [78:15] | reassmbl index [14:1] | reassmbl entry valid [0]
 * DEFAULT: undefined
 */
#घोषणा  REG_RX_TABLE_ADDR             0x4128  /* RX reassembly DMA table
						  address */
#घोषणा    RX_TABLE_ADDR_MASK          0x0000003F /* address mask */

#घोषणा  REG_RX_TABLE_DATA_LOW         0x412C  /* RX reassembly DMA table
						  data low */
#घोषणा  REG_RX_TABLE_DATA_MID         0x4130  /* RX reassembly DMA table
						  data mid */
#घोषणा  REG_RX_TABLE_DATA_HI          0x4134  /* RX reassembly DMA table
						  data high */

/* cassini+ only */
/* 8KB aligned 64-bit poपूर्णांकer to base of RX rings. lower 13 bits hardwired to
 * 0. same semantics as primary desc/complete rings.
 */
#घोषणा  REG_PLUS_RX_DB1_LOW            0x4200  /* RX descriptor ring
						   2 base low */
#घोषणा  REG_PLUS_RX_DB1_HI             0x4204  /* RX descriptor ring
						   2 base high */
#घोषणा  REG_PLUS_RX_CB1_LOW            0x4208  /* RX completion ring
						   2 base low. 4 total */
#घोषणा  REG_PLUS_RX_CB1_HI             0x420C  /* RX completion ring
						   2 base high. 4 total */
#घोषणा  REG_PLUS_RX_CBN_LOW(x)        (REG_PLUS_RX_CB1_LOW + 8*((x) - 1))
#घोषणा  REG_PLUS_RX_CBN_HI(x)         (REG_PLUS_RX_CB1_HI + 8*((x) - 1))
#घोषणा  REG_PLUS_RX_KICK1             0x4220  /* RX Kick 2 रेजिस्टर */
#घोषणा  REG_PLUS_RX_COMP1             0x4224  /* (ro) RX completion 2
						  reg */
#घोषणा  REG_PLUS_RX_COMP1_HEAD        0x4228  /* (ro) RX completion 2
						  head reg. 4 total. */
#घोषणा  REG_PLUS_RX_COMP1_TAIL        0x422C  /* RX completion 2
						  tail reg. 4 total. */
#घोषणा  REG_PLUS_RX_COMPN_HEAD(x)    (REG_PLUS_RX_COMP1_HEAD + 8*((x) - 1))
#घोषणा  REG_PLUS_RX_COMPN_TAIL(x)    (REG_PLUS_RX_COMP1_TAIL + 8*((x) - 1))
#घोषणा  REG_PLUS_RX_AE1_THRESH        0x4240  /* RX almost empty 2
						  thresholds */
#घोषणा    RX_AE1_THRESH_FREE_MASK     RX_AE_THRESH_FREE_MASK
#घोषणा    RX_AE1_THRESH_FREE_SHIFT    RX_AE_THRESH_FREE_SHIFT

/** header parser रेजिस्टरs **/

/* RX parser configuration रेजिस्टर.
 * DEFAULT: 0x1651004
 */
#घोषणा  REG_HP_CFG                       0x4140  /* header parser
						     configuration reg */
#घोषणा    HP_CFG_PARSE_EN                0x00000001 /* enab header parsing */
#घोषणा    HP_CFG_NUM_CPU_MASK            0x000000FC /* # processors
						      0 = 64. 0x3f = 63 */
#घोषणा    HP_CFG_NUM_CPU_SHIFT           2
#घोषणा    HP_CFG_SYN_INC_MASK            0x00000100 /* SYN bit won't increment
							TCP seq # by one when
							stored in FDBM */
#घोषणा    HP_CFG_TCP_THRESH_MASK         0x000FFE00 /* # bytes of TCP data
							needed to be considered
							क्रम reassembly */
#घोषणा    HP_CFG_TCP_THRESH_SHIFT        9

/* access to RX Inकाष्ठाion RAM. 5-bit रेजिस्टर/counter holds addr
 * of 39 bit entry to be पढ़ो/written. 32 LSB in _DATA_LOW. 7 MSB in _DATA_HI.
 * RX_DMA_EN must be 0 क्रम RX instr PIO access. DATA_HI should be last access
 * of sequence.
 * DEFAULT: undefined
 */
#घोषणा  REG_HP_INSTR_RAM_ADDR             0x4144  /* HP inकाष्ठाion RAM
						      address */
#घोषणा    HP_INSTR_RAM_ADDR_MASK          0x01F   /* 5-bit mask */
#घोषणा  REG_HP_INSTR_RAM_DATA_LOW         0x4148  /* HP inकाष्ठाion RAM
						      data low */
#घोषणा    HP_INSTR_RAM_LOW_OUTMASK_MASK   0x0000FFFF
#घोषणा    HP_INSTR_RAM_LOW_OUTMASK_SHIFT  0
#घोषणा    HP_INSTR_RAM_LOW_OUTSHIFT_MASK  0x000F0000
#घोषणा    HP_INSTR_RAM_LOW_OUTSHIFT_SHIFT 16
#घोषणा    HP_INSTR_RAM_LOW_OUTEN_MASK     0x00300000
#घोषणा    HP_INSTR_RAM_LOW_OUTEN_SHIFT    20
#घोषणा    HP_INSTR_RAM_LOW_OUTARG_MASK    0xFFC00000
#घोषणा    HP_INSTR_RAM_LOW_OUTARG_SHIFT   22
#घोषणा  REG_HP_INSTR_RAM_DATA_MID         0x414C  /* HP inकाष्ठाion RAM
						      data mid */
#घोषणा    HP_INSTR_RAM_MID_OUTARG_MASK    0x00000003
#घोषणा    HP_INSTR_RAM_MID_OUTARG_SHIFT   0
#घोषणा    HP_INSTR_RAM_MID_OUTOP_MASK     0x0000003C
#घोषणा    HP_INSTR_RAM_MID_OUTOP_SHIFT    2
#घोषणा    HP_INSTR_RAM_MID_FNEXT_MASK     0x000007C0
#घोषणा    HP_INSTR_RAM_MID_FNEXT_SHIFT    6
#घोषणा    HP_INSTR_RAM_MID_FOFF_MASK      0x0003F800
#घोषणा    HP_INSTR_RAM_MID_FOFF_SHIFT     11
#घोषणा    HP_INSTR_RAM_MID_SNEXT_MASK     0x007C0000
#घोषणा    HP_INSTR_RAM_MID_SNEXT_SHIFT    18
#घोषणा    HP_INSTR_RAM_MID_SOFF_MASK      0x3F800000
#घोषणा    HP_INSTR_RAM_MID_SOFF_SHIFT     23
#घोषणा    HP_INSTR_RAM_MID_OP_MASK        0xC0000000
#घोषणा    HP_INSTR_RAM_MID_OP_SHIFT       30
#घोषणा  REG_HP_INSTR_RAM_DATA_HI          0x4150  /* HP inकाष्ठाion RAM
						      data high */
#घोषणा    HP_INSTR_RAM_HI_VAL_MASK        0x0000FFFF
#घोषणा    HP_INSTR_RAM_HI_VAL_SHIFT       0
#घोषणा    HP_INSTR_RAM_HI_MASK_MASK       0xFFFF0000
#घोषणा    HP_INSTR_RAM_HI_MASK_SHIFT      16

/* PIO access पूर्णांकo RX Header parser data RAM and flow database.
 * 11-bit रेजिस्टर. Data fills the LSB portion of bus अगर less than 32 bits.
 * DATA_RAM: ग_लिखो RAM_FDB_DATA with index to access DATA_RAM.
 * RAM bytes = 4*(x - 1) + [3:0]. e.g., 0 -> [3:0], 31 -> [123:120]
 * FLOWDB: ग_लिखो DATA_RAM_FDB रेजिस्टर and then पढ़ो/ग_लिखो FDB1-12 to access
 * flow database.
 * RX_DMA_EN must be 0 क्रम RX parser RAM PIO access. RX Parser RAM data reg
 * should be the last ग_लिखो access of the ग_लिखो sequence.
 * DEFAULT: undefined
 */
#घोषणा  REG_HP_DATA_RAM_FDB_ADDR          0x4154  /* HP data and FDB
						      RAM address */
#घोषणा    HP_DATA_RAM_FDB_DATA_MASK       0x001F  /* select 1 of 86 byte
						      locations in header
						      parser data ram to
						      पढ़ो/ग_लिखो */
#घोषणा    HP_DATA_RAM_FDB_FDB_MASK        0x3F00  /* 1 of 64 353-bit locations
						      in the flow database */
#घोषणा  REG_HP_DATA_RAM_DATA              0x4158  /* HP data RAM data */

/* HP flow database रेजिस्टरs: 1 - 12, 0x415C - 0x4188, 4 8-bit bytes
 * FLOW_DB(1) = IP_SA[127:96], FLOW_DB(2) = IP_SA[95:64]
 * FLOW_DB(3) = IP_SA[63:32],  FLOW_DB(4) = IP_SA[31:0]
 * FLOW_DB(5) = IP_DA[127:96], FLOW_DB(6) = IP_DA[95:64]
 * FLOW_DB(7) = IP_DA[63:32],  FLOW_DB(8) = IP_DA[31:0]
 * FLOW_DB(9) = अणुTCP_SP[15:0],TCP_DP[15:0]पूर्ण
 * FLOW_DB(10) = bit 0 has value क्रम flow valid
 * FLOW_DB(11) = TCP_SEQ[63:32], FLOW_DB(12) = TCP_SEQ[31:0]
 */
#घोषणा  REG_HP_FLOW_DB0                   0x415C  /* HP flow database 1 reg */
#घोषणा  REG_HP_FLOW_DBN(x)                (REG_HP_FLOW_DB0 + (x)*4)

/* diagnostics क्रम RX Header Parser block.
 * ASUN: the header parser state machine रेजिस्टर is used क्रम diagnostics
 * purposes. however, the spec करोesn't have any details on it.
 */
#घोषणा  REG_HP_STATE_MACHINE              0x418C  /* (ro) HP state machine */
#घोषणा  REG_HP_STATUS0                    0x4190  /* (ro) HP status 1 */
#घोषणा    HP_STATUS0_SAP_MASK             0xFFFF0000 /* SAP */
#घोषणा    HP_STATUS0_L3_OFF_MASK          0x0000FE00 /* L3 offset */
#घोषणा    HP_STATUS0_LB_CPUNUM_MASK       0x000001F8 /* load balancing CPU
							 number */
#घोषणा    HP_STATUS0_HRP_OPCODE_MASK      0x00000007 /* HRP opcode */

#घोषणा  REG_HP_STATUS1                    0x4194  /* (ro) HP status 2 */
#घोषणा    HP_STATUS1_ACCUR2_MASK          0xE0000000 /* accu R2[6:4] */
#घोषणा    HP_STATUS1_FLOWID_MASK          0x1F800000 /* flow id */
#घोषणा    HP_STATUS1_TCP_OFF_MASK         0x007F0000 /* tcp payload offset */
#घोषणा    HP_STATUS1_TCP_SIZE_MASK        0x0000FFFF /* tcp payload size */

#घोषणा  REG_HP_STATUS2                    0x4198  /* (ro) HP status 3 */
#घोषणा    HP_STATUS2_ACCUR2_MASK          0xF0000000 /* accu R2[3:0] */
#घोषणा    HP_STATUS2_CSUM_OFF_MASK        0x07F00000 /* checksum start
							 start offset */
#घोषणा    HP_STATUS2_ACCUR1_MASK          0x000FE000 /* accu R1 */
#घोषणा    HP_STATUS2_FORCE_DROP           0x00001000 /* क्रमce drop */
#घोषणा    HP_STATUS2_BWO_REASSM           0x00000800 /* batching w/o
							 reassembly */
#घोषणा    HP_STATUS2_JH_SPLIT_EN          0x00000400 /* jumbo header split
							 enable */
#घोषणा    HP_STATUS2_FORCE_TCP_NOCHECK    0x00000200 /* क्रमce tcp no payload
							 check */
#घोषणा    HP_STATUS2_DATA_MASK_ZERO       0x00000100 /* mask of data length
							 equal to zero */
#घोषणा    HP_STATUS2_FORCE_TCP_CHECK      0x00000080 /* क्रमce tcp payload
							 chk */
#घोषणा    HP_STATUS2_MASK_TCP_THRESH      0x00000040 /* mask of payload
							 threshold */
#घोषणा    HP_STATUS2_NO_ASSIST            0x00000020 /* no assist */
#घोषणा    HP_STATUS2_CTRL_PACKET_FLAG     0x00000010 /* control packet flag */
#घोषणा    HP_STATUS2_TCP_FLAG_CHECK       0x00000008 /* tcp flag check */
#घोषणा    HP_STATUS2_SYN_FLAG             0x00000004 /* syn flag */
#घोषणा    HP_STATUS2_TCP_CHECK            0x00000002 /* tcp payload chk */
#घोषणा    HP_STATUS2_TCP_NOCHECK          0x00000001 /* tcp no payload chk */

/* BIST क्रम header parser(HP) and flow database memories (FDBM). set _START
 * to start BIST. controller clears _START on completion. _START can also
 * be cleared to क्रमce termination of BIST. a bit set indicates that that
 * memory passed its BIST.
 */
#घोषणा  REG_HP_RAM_BIST                   0x419C  /* HP RAM BIST reg */
#घोषणा    HP_RAM_BIST_HP_DATA_PASS        0x80000000 /* HP data ram */
#घोषणा    HP_RAM_BIST_HP_INSTR0_PASS      0x40000000 /* HP instr ram 0 */
#घोषणा    HP_RAM_BIST_HP_INSTR1_PASS      0x20000000 /* HP instr ram 1 */
#घोषणा    HP_RAM_BIST_HP_INSTR2_PASS      0x10000000 /* HP instr ram 2 */
#घोषणा    HP_RAM_BIST_FDBM_AGE0_PASS      0x08000000 /* FDBM aging RAM0 */
#घोषणा    HP_RAM_BIST_FDBM_AGE1_PASS      0x04000000 /* FDBM aging RAM1 */
#घोषणा    HP_RAM_BIST_FDBM_FLOWID00_PASS  0x02000000 /* FDBM flowid RAM0
							 bank 0 */
#घोषणा    HP_RAM_BIST_FDBM_FLOWID10_PASS  0x01000000 /* FDBM flowid RAM1
							 bank 0 */
#घोषणा    HP_RAM_BIST_FDBM_FLOWID20_PASS  0x00800000 /* FDBM flowid RAM2
							 bank 0 */
#घोषणा    HP_RAM_BIST_FDBM_FLOWID30_PASS  0x00400000 /* FDBM flowid RAM3
							 bank 0 */
#घोषणा    HP_RAM_BIST_FDBM_FLOWID01_PASS  0x00200000 /* FDBM flowid RAM0
							 bank 1 */
#घोषणा    HP_RAM_BIST_FDBM_FLOWID11_PASS  0x00100000 /* FDBM flowid RAM1
							 bank 2 */
#घोषणा    HP_RAM_BIST_FDBM_FLOWID21_PASS  0x00080000 /* FDBM flowid RAM2
							 bank 1 */
#घोषणा    HP_RAM_BIST_FDBM_FLOWID31_PASS  0x00040000 /* FDBM flowid RAM3
							 bank 1 */
#घोषणा    HP_RAM_BIST_FDBM_TCPSEQ_PASS    0x00020000 /* FDBM tcp sequence
							 RAM */
#घोषणा    HP_RAM_BIST_SUMMARY             0x00000002 /* all BIST tests */
#घोषणा    HP_RAM_BIST_START               0x00000001 /* start/stop BIST */


/** MAC रेजिस्टरs.  **/
/* reset bits are set using a PIO ग_लिखो and self-cleared after the command
 * execution has completed.
 */
#घोषणा  REG_MAC_TX_RESET                  0x6000  /* TX MAC software reset
						      command (शेष: 0x0) */
#घोषणा  REG_MAC_RX_RESET                  0x6004  /* RX MAC software reset
						      command (शेष: 0x0) */
/* execute a छोड़ो flow control frame transmission
 DEFAULT: 0x0XXXX */
#घोषणा  REG_MAC_SEND_PAUSE                0x6008  /* send छोड़ो command reg */
#घोषणा    MAC_SEND_PAUSE_TIME_MASK        0x0000FFFF /* value of छोड़ो समय
							 to be sent on network
							 in units of slot
							 बार */
#घोषणा    MAC_SEND_PAUSE_SEND             0x00010000 /* send छोड़ो flow ctrl
							 frame on network */

/* bit set indicates that event occurred. स्वतः-cleared when status रेजिस्टर
 * is पढ़ो and have corresponding mask bits in mask रेजिस्टर. events will
 * trigger an पूर्णांकerrupt अगर the corresponding mask bit is 0.
 * status रेजिस्टर शेष: 0x00000000
 * mask रेजिस्टर शेष = 0xFFFFFFFF on reset
 */
#घोषणा  REG_MAC_TX_STATUS                 0x6010  /* TX MAC status reg */
#घोषणा    MAC_TX_FRAME_XMIT               0x0001  /* successful frame
						      transmision */
#घोषणा    MAC_TX_UNDERRUN                 0x0002  /* terminated frame
						      transmission due to
						      data starvation in the
						      xmit data path */
#घोषणा    MAC_TX_MAX_PACKET_ERR           0x0004  /* frame exceeds max allowed
						      length passed to TX MAC
						      by the DMA engine */
#घोषणा    MAC_TX_COLL_NORMAL              0x0008  /* rollover of the normal
						      collision counter */
#घोषणा    MAC_TX_COLL_EXCESS              0x0010  /* rollover of the excessive
						      collision counter */
#घोषणा    MAC_TX_COLL_LATE                0x0020  /* rollover of the late
						      collision counter */
#घोषणा    MAC_TX_COLL_FIRST               0x0040  /* rollover of the first
						      collision counter */
#घोषणा    MAC_TX_DEFER_TIMER              0x0080  /* rollover of the defer
						      समयr */
#घोषणा    MAC_TX_PEAK_ATTEMPTS            0x0100  /* rollover of the peak
						      attempts counter */

#घोषणा  REG_MAC_RX_STATUS                 0x6014  /* RX MAC status reg */
#घोषणा    MAC_RX_FRAME_RECV               0x0001  /* successful receipt of
						      a frame */
#घोषणा    MAC_RX_OVERFLOW                 0x0002  /* dropped frame due to
						      RX FIFO overflow */
#घोषणा    MAC_RX_FRAME_COUNT              0x0004  /* rollover of receive frame
						      counter */
#घोषणा    MAC_RX_ALIGN_ERR                0x0008  /* rollover of alignment
						      error counter */
#घोषणा    MAC_RX_CRC_ERR                  0x0010  /* rollover of crc error
						      counter */
#घोषणा    MAC_RX_LEN_ERR                  0x0020  /* rollover of length
						      error counter */
#घोषणा    MAC_RX_VIOL_ERR                 0x0040  /* rollover of code
						      violation error */

/* DEFAULT: 0xXXXX0000 on reset */
#घोषणा  REG_MAC_CTRL_STATUS               0x6018  /* MAC control status reg */
#घोषणा    MAC_CTRL_PAUSE_RECEIVED         0x00000001  /* successful
							  reception of a
							  छोड़ो control
							  frame */
#घोषणा    MAC_CTRL_PAUSE_STATE            0x00000002  /* MAC has made a
							  transition from
							  "not paused" to
							  "paused" */
#घोषणा    MAC_CTRL_NOPAUSE_STATE          0x00000004  /* MAC has made a
							  transition from
							  "paused" to "not
							  छोड़ोd" */
#घोषणा    MAC_CTRL_PAUSE_TIME_MASK        0xFFFF0000  /* value of छोड़ो समय
							  opeअक्रम that was
							  received in the last
							  छोड़ो flow control
							  frame */

/* layout identical to TX MAC[8:0] */
#घोषणा  REG_MAC_TX_MASK                   0x6020  /* TX MAC mask reg */
/* layout identical to RX MAC[6:0] */
#घोषणा  REG_MAC_RX_MASK                   0x6024  /* RX MAC mask reg */
/* layout identical to CTRL MAC[2:0] */
#घोषणा  REG_MAC_CTRL_MASK                 0x6028  /* MAC control mask reg */

/* to ensure proper operation, CFG_EN must be cleared to 0 and a delay
 * imposed beक्रमe ग_लिखोs to other bits in the TX_MAC_CFG रेजिस्टर or any of
 * the MAC parameters is perक्रमmed. delay dependent upon समय required to
 * transmit a maximum size frame (= MAC_FRAMESIZE_MAX*8/Mbps). e.g.,
 * the delay क्रम a 1518-byte frame on a 100Mbps network is 125us.
 * alternatively, just poll TX_CFG_EN until it पढ़ोs back as 0.
 * NOTE: on half-duplex 1Gbps, TX_CFG_CARRIER_EXTEND and
 * RX_CFG_CARRIER_EXTEND should be set and the SLOT_TIME रेजिस्टर should
 * be 0x200 (slot समय of 512 bytes)
 */
#घोषणा  REG_MAC_TX_CFG                 0x6030  /* TX MAC config reg */
#घोषणा    MAC_TX_CFG_EN                0x0001  /* enable TX MAC. 0 will
						      क्रमce TXMAC state
						      machine to reमुख्य in
						      idle state or to
						      transition to idle state
						      on completion of an
						      ongoing packet. */
#घोषणा    MAC_TX_CFG_IGNORE_CARRIER    0x0002  /* disable CSMA/CD deferral
						   process. set to 1 when
						   full duplex and 0 when
						   half duplex */
#घोषणा    MAC_TX_CFG_IGNORE_COLL       0x0004  /* disable CSMA/CD backoff
						   algorithm. set to 1 when
						   full duplex and 0 when
						   half duplex */
#घोषणा    MAC_TX_CFG_IPG_EN            0x0008  /* enable extension of the
						   Rx-to-TX IPG. after
						   receiving a frame, TX
						   MAC will reset its
						   deferral process to
						   carrier sense क्रम the
						   amount of समय = IPG0 +
						   IPG1 and commit to
						   transmission क्रम समय
						   specअगरied in IPG2. when
						   0 or when xmitting frames
						   back-to-pack (Tx-to-Tx
						   IPG), TX MAC ignores
						   IPG0 and will only use
						   IPG1 क्रम deferral समय.
						   IPG2 still used. */
#घोषणा    MAC_TX_CFG_NEVER_GIVE_UP_EN  0x0010  /* TX MAC will not easily
						   give up on frame
						   xmission. अगर backoff
						   algorithm reaches the
						   ATTEMPT_LIMIT, it will
						   clear attempts counter
						   and जारी trying to
						   send the frame as
						   specअगरied by
						   GIVE_UP_LIM. when 0,
						   TX MAC will execute
						   standard CSMA/CD prot. */
#घोषणा    MAC_TX_CFG_NEVER_GIVE_UP_LIM 0x0020  /* when set, TX MAC will
						   जारी to try to xmit
						   until successful. when
						   0, TX MAC will जारी
						   to try xmitting until
						   successful or backoff
						   algorithm reaches
						   ATTEMPT_LIMIT*16 */
#घोषणा    MAC_TX_CFG_NO_BACKOFF        0x0040  /* modअगरy CSMA/CD to disable
						   backoff algorithm. TX
						   MAC will not back off
						   after a xmission attempt
						   that resulted in a
						   collision. */
#घोषणा    MAC_TX_CFG_SLOW_DOWN         0x0080  /* modअगरy CSMA/CD so that
						   deferral process is reset
						   in response to carrier
						   sense during the entire
						   duration of IPG. TX MAC
						   will only commit to frame
						   xmission after frame
						   xmission has actually
						   begun. */
#घोषणा    MAC_TX_CFG_NO_FCS            0x0100  /* TX MAC will not generate
						   CRC क्रम all xmitted
						   packets. when clear, CRC
						   generation is dependent
						   upon NO_CRC bit in the
						   xmit control word from
						   TX DMA */
#घोषणा    MAC_TX_CFG_CARRIER_EXTEND    0x0200  /* enables xmit part of the
						   carrier extension
						   feature. this allows क्रम
						   दीर्घer collision करोमुख्यs
						   by extending the carrier
						   and collision winकरोw
						   from the end of FCS until
						   the end of the slot समय
						   अगर necessary. Required
						   क्रम half-duplex at 1Gbps,
						   clear otherwise. */

/* when CRC is not stripped, reassembly packets will not contain the CRC.
 * these will be stripped by HRP because it reassembles layer 4 data, and the
 * CRC is layer 2. however, non-reassembly packets will still contain the CRC
 * when passed to the host. to ensure proper operation, need to रुको 3.2ms
 * after clearing RX_CFG_EN beक्रमe writing to any other RX MAC रेजिस्टरs
 * or other MAC parameters. alternatively, poll RX_CFG_EN until it clears
 * to 0. similary, HASH_FILTER_EN and ADDR_FILTER_EN have the same
 * restrictions as CFG_EN.
 */
#घोषणा  REG_MAC_RX_CFG                 0x6034  /* RX MAC config reg */
#घोषणा    MAC_RX_CFG_EN                0x0001  /* enable RX MAC */
#घोषणा    MAC_RX_CFG_STRIP_PAD         0x0002  /* always program to 0.
						   feature not supported */
#घोषणा    MAC_RX_CFG_STRIP_FCS         0x0004  /* RX MAC will strip the
						   last 4 bytes of a
						   received frame. */
#घोषणा    MAC_RX_CFG_PROMISC_EN        0x0008  /* promiscuous mode */
#घोषणा    MAC_RX_CFG_PROMISC_GROUP_EN  0x0010  /* accept all valid
						   multicast frames (group
						   bit in DA field set) */
#घोषणा    MAC_RX_CFG_HASH_FILTER_EN    0x0020  /* use hash table to filter
						   multicast addresses */
#घोषणा    MAC_RX_CFG_ADDR_FILTER_EN    0x0040  /* cause RX MAC to use
						   address filtering regs
						   to filter both unicast
						   and multicast
						   addresses */
#घोषणा    MAC_RX_CFG_DISABLE_DISCARD   0x0080  /* pass errored frames to
						   RX DMA by setting BAD
						   bit but not Abort bit
						   in the status. CRC,
						   framing, and length errs
						   will not increment
						   error counters. frames
						   which करोn't match dest
						   addr will be passed up
						   w/ BAD bit set. */
#घोषणा    MAC_RX_CFG_CARRIER_EXTEND    0x0100  /* enable reception of
						   packet bursts generated
						   by carrier extension
						   with packet bursting
						   senders. only applies
						   to half-duplex 1Gbps */

/* DEFAULT: 0x0 */
#घोषणा  REG_MAC_CTRL_CFG               0x6038  /* MAC control config reg */
#घोषणा    MAC_CTRL_CFG_SEND_PAUSE_EN   0x0001  /* respond to requests क्रम
						   sending छोड़ो flow ctrl
						   frames */
#घोषणा    MAC_CTRL_CFG_RECV_PAUSE_EN   0x0002  /* respond to received
						   छोड़ो flow ctrl frames */
#घोषणा    MAC_CTRL_CFG_PASS_CTRL       0x0004  /* pass valid MAC ctrl
						   packets to RX DMA */

/* to ensure proper operation, a global initialization sequence should be
 * perक्रमmed when a loopback config is entered or निकासed. अगर programmed after
 * a hw or global sw reset, RX/TX MAC software reset and initialization
 * should be करोne to ensure stable घड़ीing.
 * DEFAULT: 0x0
 */
#घोषणा  REG_MAC_XIF_CFG                0x603C  /* XIF config reg */
#घोषणा    MAC_XIF_TX_MII_OUTPUT_EN        0x0001  /* enable output drivers
						      on MII xmit bus */
#घोषणा    MAC_XIF_MII_INT_LOOPBACK        0x0002  /* loopback GMII xmit data
						      path to GMII recv data
						      path. phy mode रेजिस्टर
						      घड़ी selection must be
						      set to GMII mode and
						      GMII_MODE should be set
						      to 1. in loopback mode,
						      REFCLK will drive the
						      entire mac core. 0 क्रम
						      normal operation. */
#घोषणा    MAC_XIF_DISABLE_ECHO            0x0004  /* disables receive data
						      path during packet
						      xmission. clear to 0
						      in any full duplex mode,
						      in any loopback mode,
						      or in half-duplex SERDES
						      or SLINK modes. set when
						      in half-duplex when
						      using बाह्यal phy. */
#घोषणा    MAC_XIF_GMII_MODE               0x0008  /* MAC operates with GMII
						      घड़ीs and datapath */
#घोषणा    MAC_XIF_MII_BUFFER_OUTPUT_EN    0x0010  /* MII_BUF_EN pin. enable
						      बाह्यal tristate buffer
						      on the MII receive
						      bus. */
#घोषणा    MAC_XIF_LINK_LED                0x0020  /* LINKLED# active (low) */
#घोषणा    MAC_XIF_FDPLX_LED               0x0040  /* FDPLXLED# active (low) */

#घोषणा  REG_MAC_IPG0                      0x6040  /* पूर्णांकer-packet gap0 reg.
						      recommended: 0x00 */
#घोषणा  REG_MAC_IPG1                      0x6044  /* पूर्णांकer-packet gap1 reg
						      recommended: 0x08 */
#घोषणा  REG_MAC_IPG2                      0x6048  /* पूर्णांकer-packet gap2 reg
						      recommended: 0x04 */
#घोषणा  REG_MAC_SLOT_TIME                 0x604C  /* slot समय reg
						      recommended: 0x40 */
#घोषणा  REG_MAC_FRAMESIZE_MIN             0x6050  /* min frame size reg
						      recommended: 0x40 */

/* FRAMESIZE_MAX holds both the max frame size as well as the max burst size.
 * recommended value:  0x2000.05EE
 */
#घोषणा  REG_MAC_FRAMESIZE_MAX             0x6054  /* max frame size reg */
#घोषणा    MAC_FRAMESIZE_MAX_BURST_MASK    0x3FFF0000 /* max burst size */
#घोषणा    MAC_FRAMESIZE_MAX_BURST_SHIFT   16
#घोषणा    MAC_FRAMESIZE_MAX_FRAME_MASK    0x00007FFF /* max frame size */
#घोषणा    MAC_FRAMESIZE_MAX_FRAME_SHIFT   0
#घोषणा  REG_MAC_PA_SIZE                   0x6058  /* PA size reg. number of
						      preamble bytes that the
						      TX MAC will xmit at the
						      beginning of each frame
						      value should be 2 or
						      greater. recommended
						      value: 0x07 */
#घोषणा  REG_MAC_JAM_SIZE                  0x605C  /* jam size reg. duration
						      of jam in units of media
						      byte समय. recommended
						      value: 0x04 */
#घोषणा  REG_MAC_ATTEMPT_LIMIT             0x6060  /* attempt limit reg. #
						      of attempts TX MAC will
						      make to xmit a frame
						      beक्रमe it resets its
						      attempts counter. after
						      the limit has been
						      reached, TX MAC may or
						      may not drop the frame
						      dependent upon value
						      in TX_MAC_CFG.
						      recommended
						      value: 0x10 */
#घोषणा  REG_MAC_CTRL_TYPE                 0x6064  /* MAC control type reg.
						      type field of a MAC
						      ctrl frame. recommended
						      value: 0x8808 */

/* mac address रेजिस्टरs: 0 - 44, 0x6080 - 0x6130, 4 8-bit bytes.
 * रेजिस्टर           contains                   comparison
 *    0        16 MSB of primary MAC addr        [47:32] of DA field
 *    1        16 middle bits ""                 [31:16] of DA field
 *    2        16 LSB ""                         [15:0] of DA field
 *    3*x      16MSB of alt MAC addr 1-15        [47:32] of DA field
 *    4*x      16 middle bits ""                 [31:16]
 *    5*x      16 LSB ""                         [15:0]
 *    42       16 MSB of MAC CTRL addr           [47:32] of DA.
 *    43       16 middle bits ""                 [31:16]
 *    44       16 LSB ""                         [15:0]
 *    MAC CTRL addr must be the reserved multicast addr क्रम MAC CTRL frames.
 *    अगर there is a match, MAC will set the bit क्रम alternative address
 *    filter pass [15]

 *    here is the map of रेजिस्टरs given MAC address notation: a:b:c:d:e:f
 *                     ab             cd             ef
 *    primary addr     reg 2          reg 1          reg 0
 *    alt addr 1       reg 5          reg 4          reg 3
 *    alt addr x       reg 5*x        reg 4*x        reg 3*x
 *    ctrl addr        reg 44         reg 43         reg 42
 */
#घोषणा  REG_MAC_ADDR0                     0x6080  /* MAC address 0 reg */
#घोषणा  REG_MAC_ADDRN(x)                  (REG_MAC_ADDR0 + (x)*4)
#घोषणा  REG_MAC_ADDR_FILTER0              0x614C  /* address filter 0 reg
						      [47:32] */
#घोषणा  REG_MAC_ADDR_FILTER1              0x6150  /* address filter 1 reg
						      [31:16] */
#घोषणा  REG_MAC_ADDR_FILTER2              0x6154  /* address filter 2 reg
						      [15:0] */
#घोषणा  REG_MAC_ADDR_FILTER2_1_MASK       0x6158  /* address filter 2 and 1
						      mask reg. 8-bit reg
						      contains nibble mask क्रम
						      reg 2 and 1. */
#घोषणा  REG_MAC_ADDR_FILTER0_MASK         0x615C  /* address filter 0 mask
						      reg */

/* hash table रेजिस्टरs: 0 - 15, 0x6160 - 0x619C, 4 8-bit bytes
 * 16-bit रेजिस्टरs contain bits of the hash table.
 * reg x  -> [16*(15 - x) + 15 : 16*(15 - x)].
 * e.g., 15 -> [15:0], 0 -> [255:240]
 */
#घोषणा  REG_MAC_HASH_TABLE0               0x6160  /* hash table 0 reg */
#घोषणा  REG_MAC_HASH_TABLEN(x)            (REG_MAC_HASH_TABLE0 + (x)*4)

/* statistics रेजिस्टरs. these रेजिस्टरs generate an पूर्णांकerrupt on
 * overflow. recommended initialization: 0x0000. most are 16-bits except
 * क्रम PEAK_ATTEMPTS रेजिस्टर which is 8 bits.
 */
#घोषणा  REG_MAC_COLL_NORMAL               0x61A0 /* normal collision
						     counter. */
#घोषणा  REG_MAC_COLL_FIRST                0x61A4 /* first attempt
						     successful collision
						     counter */
#घोषणा  REG_MAC_COLL_EXCESS               0x61A8 /* excessive collision
						     counter */
#घोषणा  REG_MAC_COLL_LATE                 0x61AC /* late collision counter */
#घोषणा  REG_MAC_TIMER_DEFER               0x61B0 /* defer समयr. समय base
						     is the media byte
						     घड़ी/256 */
#घोषणा  REG_MAC_ATTEMPTS_PEAK             0x61B4 /* peak attempts reg */
#घोषणा  REG_MAC_RECV_FRAME                0x61B8 /* receive frame counter */
#घोषणा  REG_MAC_LEN_ERR                   0x61BC /* length error counter */
#घोषणा  REG_MAC_ALIGN_ERR                 0x61C0 /* alignment error counter */
#घोषणा  REG_MAC_FCS_ERR                   0x61C4 /* FCS error counter */
#घोषणा  REG_MAC_RX_CODE_ERR               0x61C8 /* RX code violation
						     error counter */

/* misc रेजिस्टरs */
#घोषणा  REG_MAC_RANDOM_SEED               0x61CC /* अक्रमom number seed reg.
						   10-bit रेजिस्टर used as a
						   seed  क्रम the अक्रमom number
						   generator क्रम the CSMA/CD
						   backoff algorithm. only
						   programmed after घातer-on
						   reset and should be a
						   अक्रमom value which has a
						   high likelihood of being
						   unique क्रम each MAC
						   attached to a network
						   segment (e.g., 10 LSB of
						   MAC address) */

/* ASUN: there's a PAUSE_TIMER (ro) described, but it's not in the address
 *       map
 */

/* 27-bit रेजिस्टर has the current state क्रम key state machines in the MAC */
#घोषणा  REG_MAC_STATE_MACHINE             0x61D0 /* (ro) state machine reg */
#घोषणा    MAC_SM_RLM_MASK                 0x07800000
#घोषणा    MAC_SM_RLM_SHIFT                23
#घोषणा    MAC_SM_RX_FC_MASK               0x00700000
#घोषणा    MAC_SM_RX_FC_SHIFT              20
#घोषणा    MAC_SM_TLM_MASK                 0x000F0000
#घोषणा    MAC_SM_TLM_SHIFT                16
#घोषणा    MAC_SM_ENCAP_SM_MASK            0x0000F000
#घोषणा    MAC_SM_ENCAP_SM_SHIFT           12
#घोषणा    MAC_SM_TX_REQ_MASK              0x00000C00
#घोषणा    MAC_SM_TX_REQ_SHIFT             10
#घोषणा    MAC_SM_TX_FC_MASK               0x000003C0
#घोषणा    MAC_SM_TX_FC_SHIFT              6
#घोषणा    MAC_SM_FIFO_WRITE_SEL_MASK      0x00000038
#घोषणा    MAC_SM_FIFO_WRITE_SEL_SHIFT     3
#घोषणा    MAC_SM_TX_FIFO_EMPTY_MASK       0x00000007
#घोषणा    MAC_SM_TX_FIFO_EMPTY_SHIFT      0

/** MIF रेजिस्टरs. the MIF can be programmed in either bit-bang or
 *  frame mode.
 **/
#घोषणा  REG_MIF_BIT_BANG_CLOCK            0x6200 /* MIF bit-bang घड़ी.
						   1 -> 0 will generate a
						   rising edge. 0 -> 1 will
						   generate a falling edge. */
#घोषणा  REG_MIF_BIT_BANG_DATA             0x6204 /* MIF bit-bang data. 1-bit
						     रेजिस्टर generates data */
#घोषणा  REG_MIF_BIT_BANG_OUTPUT_EN        0x6208 /* MIF bit-bang output
						     enable. enable when
						     xmitting data from MIF to
						     transceiver. */

/* 32-bit रेजिस्टर serves as an inकाष्ठाion रेजिस्टर when the MIF is
 * programmed in frame mode. load this रेजिस्टर w/ a valid inकाष्ठाion
 * (as per IEEE 802.3u MII spec). poll this रेजिस्टर to check क्रम inकाष्ठाion
 * execution completion. during a पढ़ो operation, this रेजिस्टर will also
 * contain the 16-bit data वापसed by the tranceiver. unless specअगरied
 * otherwise, fields are considered "don't care" when polling क्रम
 * completion.
 */
#घोषणा  REG_MIF_FRAME                     0x620C /* MIF frame/output reg */
#घोषणा    MIF_FRAME_START_MASK            0xC0000000 /* start of frame.
							 load w/ 01 when
							 issuing an instr */
#घोषणा    MIF_FRAME_ST                    0x40000000 /* STart of frame */
#घोषणा    MIF_FRAME_OPCODE_MASK           0x30000000 /* opcode. 01 क्रम a
							 ग_लिखो. 10 क्रम a
							 पढ़ो */
#घोषणा    MIF_FRAME_OP_READ               0x20000000 /* पढ़ो OPcode */
#घोषणा    MIF_FRAME_OP_WRITE              0x10000000 /* ग_लिखो OPcode */
#घोषणा    MIF_FRAME_PHY_ADDR_MASK         0x0F800000 /* phy address. when
							 issuing an instr,
							 this field should be
							 loaded w/ the XCVR
							 addr */
#घोषणा    MIF_FRAME_PHY_ADDR_SHIFT        23
#घोषणा    MIF_FRAME_REG_ADDR_MASK         0x007C0000 /* रेजिस्टर address.
							 when issuing an instr,
							 addr of रेजिस्टर
							 to be पढ़ो/written */
#घोषणा    MIF_FRAME_REG_ADDR_SHIFT        18
#घोषणा    MIF_FRAME_TURN_AROUND_MSB       0x00020000 /* turn around, MSB.
							 when issuing an instr,
							 set this bit to 1 */
#घोषणा    MIF_FRAME_TURN_AROUND_LSB       0x00010000 /* turn around, LSB.
							 when issuing an instr,
							 set this bit to 0.
							 when polling क्रम
							 completion, 1 means
							 that instr execution
							 has been completed */
#घोषणा    MIF_FRAME_DATA_MASK             0x0000FFFF /* inकाष्ठाion payload
							 load with 16-bit data
							 to be written in
							 transceiver reg क्रम a
							 ग_लिखो. करोesn't matter
							 in a पढ़ो. when
							 polling क्रम
							 completion, field is
							 "don't care" क्रम ग_लिखो
							 and 16-bit data
							 वापसed by the
							 transceiver क्रम a
							 पढ़ो (अगर valid bit
							 is set) */
#घोषणा  REG_MIF_CFG                    0x6210 /* MIF config reg */
#घोषणा    MIF_CFG_PHY_SELECT           0x0001 /* 1 -> select MDIO_1
						  0 -> select MDIO_0 */
#घोषणा    MIF_CFG_POLL_EN              0x0002 /* enable polling
						  mechanism. अगर set,
						  BB_MODE should be 0 */
#घोषणा    MIF_CFG_BB_MODE              0x0004 /* 1 -> bit-bang mode
						  0 -> frame mode */
#घोषणा    MIF_CFG_POLL_REG_MASK        0x00F8 /* रेजिस्टर address to be
						  used by polling mode.
						  only meaningful अगर POLL_EN
						  is set to 1 */
#घोषणा    MIF_CFG_POLL_REG_SHIFT       3
#घोषणा    MIF_CFG_MDIO_0               0x0100 /* (ro) dual purpose.
						  when MDIO_0 is idle,
						  1 -> tranceiver is
						  connected to MDIO_0.
						  when MIF is communicating
						  w/ MDIO_0 in bit-bang
						  mode, this bit indicates
						  the incoming bit stream
						  during a पढ़ो op */
#घोषणा    MIF_CFG_MDIO_1               0x0200 /* (ro) dual purpose.
						  when MDIO_1 is idle,
						  1 -> transceiver is
						  connected to MDIO_1.
						  when MIF is communicating
						  w/ MDIO_1 in bit-bang
						  mode, this bit indicates
						  the incoming bit stream
						  during a पढ़ो op */
#घोषणा    MIF_CFG_POLL_PHY_MASK        0x7C00 /* tranceiver address to
						  be polled */
#घोषणा    MIF_CFG_POLL_PHY_SHIFT       10

/* 16-bit रेजिस्टर used to determine which bits in the POLL_STATUS portion of
 * the MIF_STATUS रेजिस्टर will cause an पूर्णांकerrupt. अगर a mask bit is 0,
 * corresponding bit of the POLL_STATUS will generate a MIF पूर्णांकerrupt when
 * set. DEFAULT: 0xFFFF
 */
#घोषणा  REG_MIF_MASK                      0x6214 /* MIF mask reg */

/* 32-bit रेजिस्टर used when in poll mode. स्वतः-cleared after being पढ़ो */
#घोषणा  REG_MIF_STATUS                    0x6218 /* MIF status reg */
#घोषणा    MIF_STATUS_POLL_DATA_MASK       0xFFFF0000 /* poll data contains
							 the "latest image"
							 update of the XCVR
							 reg being पढ़ो */
#घोषणा    MIF_STATUS_POLL_DATA_SHIFT      16
#घोषणा    MIF_STATUS_POLL_STATUS_MASK     0x0000FFFF /* poll status indicates
							 which bits in the
							 POLL_DATA field have
							 changed since the
							 MIF_STATUS reg was
							 last पढ़ो */
#घोषणा    MIF_STATUS_POLL_STATUS_SHIFT    0

/* 7-bit रेजिस्टर has current state क्रम all state machines in the MIF */
#घोषणा  REG_MIF_STATE_MACHINE             0x621C /* MIF state machine reg */
#घोषणा    MIF_SM_CONTROL_MASK             0x07   /* control state machine
						     state */
#घोषणा    MIF_SM_EXECUTION_MASK           0x60   /* execution state machine
						     state */

/** PCS/Serialink. the following रेजिस्टरs are equivalent to the standard
 *  MII management रेजिस्टरs except that they're directly mapped in
 *  Cassini's रेजिस्टर space.
 **/

/* the स्वतः-negotiation enable bit should be programmed the same at
 * the link partner as in the local device to enable स्वतः-negotiation to
 * complete. when that bit is reprogrammed, स्वतः-neg/manual config is
 * restarted स्वतःmatically.
 * DEFAULT: 0x1040
 */
#घोषणा  REG_PCS_MII_CTRL                  0x9000 /* PCS MII control reg */
#घोषणा    PCS_MII_CTRL_1000_SEL           0x0040 /* पढ़ोs 1. ignored on
						     ग_लिखोs */
#घोषणा    PCS_MII_CTRL_COLLISION_TEST     0x0080 /* COL संकेत at the PCS
						     to MAC पूर्णांकerface is
						     activated regardless
						     of activity */
#घोषणा    PCS_MII_CTRL_DUPLEX             0x0100 /* क्रमced 0x0. PCS
						     behaviour same क्रम
						     half and full dplx */
#घोषणा    PCS_MII_RESTART_AUTONEG         0x0200 /* self clearing.
						     restart स्वतः-
						     negotiation */
#घोषणा    PCS_MII_ISOLATE                 0x0400 /* पढ़ो as 0. ignored
						     on ग_लिखोs */
#घोषणा    PCS_MII_POWER_DOWN              0x0800 /* पढ़ो as 0. ignored
						     on ग_लिखोs */
#घोषणा    PCS_MII_AUTONEG_EN              0x1000 /* शेष 1. PCS goes
						     through स्वतःmatic
						     link config beक्रमe it
						     can be used. when 0,
						     link can be used
						     w/out any link config
						     phase */
#घोषणा    PCS_MII_10_100_SEL              0x2000 /* पढ़ो as 0. ignored on
						     ग_लिखोs */
#घोषणा    PCS_MII_RESET                   0x8000 /* reset PCS. self-clears
						     when करोne */

/* DEFAULT: 0x0108 */
#घोषणा  REG_PCS_MII_STATUS                0x9004 /* PCS MII status reg */
#घोषणा    PCS_MII_STATUS_EXTEND_CAP       0x0001 /* पढ़ोs 0 */
#घोषणा    PCS_MII_STATUS_JABBER_DETECT    0x0002 /* पढ़ोs 0 */
#घोषणा    PCS_MII_STATUS_LINK_STATUS      0x0004 /* 1 -> link up.
						     0 -> link करोwn. 0 is
						     latched so that 0 is
						     kept until पढ़ो. पढ़ो
						     2x to determine अगर the
						     link has gone up again */
#घोषणा    PCS_MII_STATUS_AUTONEG_ABLE     0x0008 /* पढ़ोs 1 (able to perक्रमm
						     स्वतः-neg) */
#घोषणा    PCS_MII_STATUS_REMOTE_FAULT     0x0010 /* 1 -> remote fault detected
						     from received link code
						     word. only valid after
						     स्वतः-neg completed */
#घोषणा    PCS_MII_STATUS_AUTONEG_COMP     0x0020 /* 1 -> स्वतः-negotiation
						          completed
						     0 -> स्वतः-negotiation not
						     completed */
#घोषणा    PCS_MII_STATUS_EXTEND_STATUS    0x0100 /* पढ़ोs as 1. used as an
						     indication that this is
						     a 1000 Base-X PHY. ग_लिखोs
						     to it are ignored */

/* used during स्वतः-negotiation.
 * DEFAULT: 0x00E0
 */
#घोषणा  REG_PCS_MII_ADVERT                0x9008 /* PCS MII advertisement
						     reg */
#घोषणा    PCS_MII_ADVERT_FD               0x0020  /* advertise full duplex
						      1000 Base-X */
#घोषणा    PCS_MII_ADVERT_HD               0x0040  /* advertise half-duplex
						      1000 Base-X */
#घोषणा    PCS_MII_ADVERT_SYM_PAUSE        0x0080  /* advertise PAUSE
						      symmetric capability */
#घोषणा    PCS_MII_ADVERT_ASYM_PAUSE       0x0100  /* advertises PAUSE
						      asymmetric capability */
#घोषणा    PCS_MII_ADVERT_RF_MASK          0x3000 /* remote fault. ग_लिखो bit13
						     to optionally indicate to
						     link partner that chip is
						     going off-line. bit12 will
						     get set when संकेत
						     detect == FAIL and will
						     reमुख्य set until
						     successful negotiation */
#घोषणा    PCS_MII_ADVERT_ACK              0x4000 /* (ro) */
#घोषणा    PCS_MII_ADVERT_NEXT_PAGE        0x8000 /* (ro) क्रमced 0x0 */

/* contents updated as a result of स्वतःnegotiation. layout and definitions
 * identical to PCS_MII_ADVERT
 */
#घोषणा  REG_PCS_MII_LPA                   0x900C /* PCS MII link partner
						     ability reg */
#घोषणा    PCS_MII_LPA_FD             PCS_MII_ADVERT_FD
#घोषणा    PCS_MII_LPA_HD             PCS_MII_ADVERT_HD
#घोषणा    PCS_MII_LPA_SYM_PAUSE      PCS_MII_ADVERT_SYM_PAUSE
#घोषणा    PCS_MII_LPA_ASYM_PAUSE     PCS_MII_ADVERT_ASYM_PAUSE
#घोषणा    PCS_MII_LPA_RF_MASK        PCS_MII_ADVERT_RF_MASK
#घोषणा    PCS_MII_LPA_ACK            PCS_MII_ADVERT_ACK
#घोषणा    PCS_MII_LPA_NEXT_PAGE      PCS_MII_ADVERT_NEXT_PAGE

/* DEFAULT: 0x0 */
#घोषणा  REG_PCS_CFG                       0x9010 /* PCS config reg */
#घोषणा    PCS_CFG_EN                      0x01   /* enable PCS. must be
						     0 when modअगरying
						     PCS_MII_ADVERT */
#घोषणा    PCS_CFG_SD_OVERRIDE             0x02   /* sets संकेत detect to
						     OK. bit is
						     non-resettable */
#घोषणा    PCS_CFG_SD_ACTIVE_LOW           0x04   /* changes पूर्णांकerpretation
						     of optical संकेत to make
						     संकेत detect okay when
						     संकेत is low */
#घोषणा    PCS_CFG_JITTER_STUDY_MASK       0x18   /* used to make jitter
						     measurements. a single
						     code group is xmitted
						     regularly.
						     0x0 = normal operation
						     0x1 = high freq test
						           pattern, D21.5
						     0x2 = low freq test
						           pattern, K28.7
						     0x3 = reserved */
#घोषणा    PCS_CFG_10MS_TIMER_OVERRIDE     0x20   /* लघुens 10-20ms स्वतः-
						     negotiation समयr to
						     a few cycles क्रम test
						     purposes */

/* used क्रम diagnostic purposes. bits 20-22 स्वतःclear on पढ़ो */
#घोषणा  REG_PCS_STATE_MACHINE             0x9014 /* (ro) PCS state machine
						     and diagnostic reg */
#घोषणा    PCS_SM_TX_STATE_MASK            0x0000000F /* 0 and 1 indicate
							 xmission of idle.
							 otherwise, xmission of
							 a packet */
#घोषणा    PCS_SM_RX_STATE_MASK            0x000000F0 /* 0 indicates reception
							 of idle. otherwise,
							 reception of packet */
#घोषणा    PCS_SM_WORD_SYNC_STATE_MASK     0x00000700 /* 0 indicates loss of
							 sync */
#घोषणा    PCS_SM_SEQ_DETECT_STATE_MASK    0x00001800 /* cycling through 0-3
							 indicates reception of
							 Config codes. cycling
							 through 0-1 indicates
							 reception of idles */
#घोषणा    PCS_SM_LINK_STATE_MASK          0x0001E000
#घोषणा        SM_LINK_STATE_UP            0x00016000 /* link state is up */

#घोषणा    PCS_SM_LOSS_LINK_C              0x00100000 /* loss of link due to
							 recept of Config
							 codes */
#घोषणा    PCS_SM_LOSS_LINK_SYNC           0x00200000 /* loss of link due to
							 loss of sync */
#घोषणा    PCS_SM_LOSS_SIGNAL_DETECT       0x00400000 /* संकेत detect goes
							 from OK to FAIL. bit29
							 will also be set अगर
							 this is set */
#घोषणा    PCS_SM_NO_LINK_BREAKLINK        0x01000000 /* link not up due to
							receipt of अवरोधlink
							C codes from partner.
							C codes w/ 0 content
							received triggering
							start/restart of
							स्वतःnegotiation.
							should be sent क्रम
							no दीर्घer than 20ms */
#घोषणा    PCS_SM_NO_LINK_SERDES           0x02000000 /* serdes being
							initialized. see serdes
							state reg */
#घोषणा    PCS_SM_NO_LINK_C                0x04000000 /* C codes not stable or
							 not received */
#घोषणा    PCS_SM_NO_LINK_SYNC             0x08000000 /* word sync not
							 achieved */
#घोषणा    PCS_SM_NO_LINK_WAIT_C           0x10000000 /* रुकोing क्रम C codes
							 w/ ack bit set */
#घोषणा    PCS_SM_NO_LINK_NO_IDLE          0x20000000 /* link partner जारीs
							 to send C codes
							 instead of idle
							 symbols or pkt data */

/* this रेजिस्टर indicates पूर्णांकerrupt changes in specअगरic PCS MII status bits.
 * PCS_INT may be masked at the ISR level. only a single bit is implemented
 * क्रम link status change.
 */
#घोषणा  REG_PCS_INTR_STATUS               0x9018 /* PCS पूर्णांकerrupt status */
#घोषणा    PCS_INTR_STATUS_LINK_CHANGE     0x04   /* link status has changed
						     since last पढ़ो */

/* control which network पूर्णांकerface is used. no more than one bit should
 * be set.
 * DEFAULT: none
 */
#घोषणा  REG_PCS_DATAPATH_MODE             0x9050 /* datapath mode reg */
#घोषणा    PCS_DATAPATH_MODE_MII           0x00 /* PCS is not used and
						   MII/GMII is selected.
						   selection between MII and
						   GMII is controlled by
						   XIF_CFG */
#घोषणा    PCS_DATAPATH_MODE_SERDES        0x02 /* PCS is used via the
						   10-bit पूर्णांकerface */

/* input to serdes chip or serialink block */
#घोषणा  REG_PCS_SERDES_CTRL              0x9054 /* serdes control reg */
#घोषणा    PCS_SERDES_CTRL_LOOPBACK       0x01   /* enable loopback on
						    serdes पूर्णांकerface */
#घोषणा    PCS_SERDES_CTRL_SYNCD_EN       0x02   /* enable sync carrier
						    detection. should be
						    0x0 क्रम normal
						    operation */
#घोषणा    PCS_SERDES_CTRL_LOCKREF       0x04   /* frequency-lock RBC[0:1]
						   to REFCLK when set.
						   when clear, receiver
						   घड़ी locks to incoming
						   serial data */

/* multiplex test outमाला_दो पूर्णांकo the PROM address (PA_3 through PA_0) pins.
 * should be 0x0 क्रम normal operations.
 * 0b000          normal operation, PROM address[3:0] selected
 * 0b001          rxdma req, rxdma ack, rxdma पढ़ोy, rxdma पढ़ो
 * 0b010          rxmac req, rx ack, rx tag, rx clk shared
 * 0b011          txmac req, tx ack, tx tag, tx retry req
 * 0b100          tx tp3, tx tp2, tx tp1, tx tp0
 * 0b101          R period RX, R period TX, R period HP, R period BIM
 * DEFAULT: 0x0
 */
#घोषणा  REG_PCS_SHARED_OUTPUT_SEL         0x9058 /* shared output select */
#घोषणा    PCS_SOS_PROM_ADDR_MASK          0x0007

/* used क्रम diagnostics. this रेजिस्टर indicates progress of the SERDES
 * boot up.
 * 0b00       undergoing reset
 * 0b01       रुकोing 500us जबतक lockrefn is निश्चितed
 * 0b10       रुकोing क्रम comma detect
 * 0b11       receive data is synchronized
 * DEFAULT: 0x0
 */
#घोषणा  REG_PCS_SERDES_STATE              0x905C /* (ro) serdes state */
#घोषणा    PCS_SERDES_STATE_MASK           0x03

/* used क्रम diagnostics. indicates number of packets transmitted or received.
 * counters rollover w/out generating an पूर्णांकerrupt.
 * DEFAULT: 0x0
 */
#घोषणा  REG_PCS_PACKET_COUNT              0x9060 /* (ro) PCS packet counter */
#घोषणा    PCS_PACKET_COUNT_TX             0x000007FF /* pkts xmitted by PCS */
#घोषणा    PCS_PACKET_COUNT_RX             0x07FF0000 /* pkts recvd by PCS
							 whether they
							 encountered an error
							 or not */

/** LocalBus Devices. the following provides run-समय access to the
 *  Cassini's PROM
 ***/
#घोषणा  REG_EXPANSION_ROM_RUN_START       0x100000 /* expansion rom run समय
						       access */
#घोषणा  REG_EXPANSION_ROM_RUN_END         0x17FFFF

#घोषणा  REG_SECOND_LOCALBUS_START         0x180000 /* secondary local bus
						       device */
#घोषणा  REG_SECOND_LOCALBUS_END           0x1FFFFF

/* entropy device */
#घोषणा  REG_ENTROPY_START                 REG_SECOND_LOCALBUS_START
#घोषणा  REG_ENTROPY_DATA                  (REG_ENTROPY_START + 0x00)
#घोषणा  REG_ENTROPY_STATUS                (REG_ENTROPY_START + 0x04)
#घोषणा      ENTROPY_STATUS_DRDY           0x01
#घोषणा      ENTROPY_STATUS_BUSY           0x02
#घोषणा      ENTROPY_STATUS_CIPHER         0x04
#घोषणा      ENTROPY_STATUS_BYPASS_MASK    0x18
#घोषणा  REG_ENTROPY_MODE                  (REG_ENTROPY_START + 0x05)
#घोषणा      ENTROPY_MODE_KEY_MASK         0x07
#घोषणा      ENTROPY_MODE_ENCRYPT          0x40
#घोषणा  REG_ENTROPY_RAND_REG              (REG_ENTROPY_START + 0x06)
#घोषणा  REG_ENTROPY_RESET                 (REG_ENTROPY_START + 0x07)
#घोषणा      ENTROPY_RESET_DES_IO          0x01
#घोषणा      ENTROPY_RESET_STC_MODE        0x02
#घोषणा      ENTROPY_RESET_KEY_CACHE       0x04
#घोषणा      ENTROPY_RESET_IV              0x08
#घोषणा  REG_ENTROPY_IV                    (REG_ENTROPY_START + 0x08)
#घोषणा  REG_ENTROPY_KEY0                  (REG_ENTROPY_START + 0x10)
#घोषणा  REG_ENTROPY_KEYN(x)               (REG_ENTROPY_KEY0 + 4*(x))

/* phys of पूर्णांकerest w/ their special mii रेजिस्टरs */
#घोषणा PHY_LUCENT_B0     0x00437421
#घोषणा   LUCENT_MII_REG      0x1F

#घोषणा PHY_NS_DP83065    0x20005c78
#घोषणा   DP83065_MII_MEM     0x16
#घोषणा   DP83065_MII_REGD    0x1D
#घोषणा   DP83065_MII_REGE    0x1E

#घोषणा PHY_BROADCOM_5411 0x00206071
#घोषणा PHY_BROADCOM_B0   0x00206050
#घोषणा   BROADCOM_MII_REG4   0x14
#घोषणा   BROADCOM_MII_REG5   0x15
#घोषणा   BROADCOM_MII_REG7   0x17
#घोषणा   BROADCOM_MII_REG8   0x18

#घोषणा   CAS_MII_ANNPTR          0x07
#घोषणा   CAS_MII_ANNPRR          0x08
#घोषणा   CAS_MII_1000_CTRL       0x09
#घोषणा   CAS_MII_1000_STATUS     0x0A
#घोषणा   CAS_MII_1000_EXTEND     0x0F

#घोषणा   CAS_BMSR_1000_EXTEND    0x0100 /* supports 1000Base-T extended status */
/*
 * अगर स्वतःneg is disabled, here's the table:
 * BMCR_SPEED100 = 100Mbps
 * BMCR_SPEED1000 = 1000Mbps
 * ~(BMCR_SPEED100 | BMCR_SPEED1000) = 10Mbps
 */
#घोषणा   CAS_BMCR_SPEED1000      0x0040  /* Select 1000Mbps */

#घोषणा   CAS_ADVERTISE_1000HALF   0x0100
#घोषणा   CAS_ADVERTISE_1000FULL   0x0200
#घोषणा   CAS_ADVERTISE_PAUSE      0x0400
#घोषणा   CAS_ADVERTISE_ASYM_PAUSE 0x0800

/* regular lpa रेजिस्टर */
#घोषणा   CAS_LPA_PAUSE	           CAS_ADVERTISE_PAUSE
#घोषणा   CAS_LPA_ASYM_PAUSE       CAS_ADVERTISE_ASYM_PAUSE

/* 1000_STATUS रेजिस्टर */
#घोषणा   CAS_LPA_1000HALF        0x0400
#घोषणा   CAS_LPA_1000FULL        0x0800

#घोषणा   CAS_EXTEND_1000XFULL    0x8000
#घोषणा   CAS_EXTEND_1000XHALF    0x4000
#घोषणा   CAS_EXTEND_1000TFULL    0x2000
#घोषणा   CAS_EXTEND_1000THALF    0x1000

/* cassini header parser firmware */
प्रकार काष्ठा cas_hp_inst अणु
	स्थिर अक्षर *note;

	u16 mask, val;

	u8 op;
	u8 soff, snext;	/* अगर match succeeds, new offset and match */
	u8 foff, fnext;	/* अगर match fails, new offset and match */
	/* output info */
	u8 outop;    /* output opcode */

	u16 outarg;  /* output argument */
	u8 outenab;  /* output enable: 0 = not, 1 = अगर match
			 2 = अगर !match, 3 = always */
	u8 outshअगरt; /* barrel shअगरt right, 4 bits */
	u16 ouपंचांगask;
पूर्ण cas_hp_inst_t;

/* comparison */
#घोषणा OP_EQ     0 /* packet == value */
#घोषणा OP_LT     1 /* packet < value */
#घोषणा OP_GT     2 /* packet > value */
#घोषणा OP_NP     3 /* new packet */

/* output opcodes */
#घोषणा	CL_REG	0
#घोषणा	LD_FID	1
#घोषणा	LD_SEQ	2
#घोषणा	LD_CTL	3
#घोषणा	LD_SAP	4
#घोषणा	LD_R1	5
#घोषणा	LD_L3	6
#घोषणा	LD_SUM	7
#घोषणा	LD_HDR	8
#घोषणा	IM_FID	9
#घोषणा	IM_SEQ	10
#घोषणा	IM_SAP	11
#घोषणा	IM_R1	12
#घोषणा	IM_CTL	13
#घोषणा	LD_LEN	14
#घोषणा	ST_FLG	15

/* match setp #s क्रम IP4TCP4 */
#घोषणा S1_PCKT         0
#घोषणा S1_VLAN         1
#घोषणा S1_CFI          2
#घोषणा S1_8023         3
#घोषणा S1_LLC          4
#घोषणा S1_LLCc         5
#घोषणा S1_IPV4         6
#घोषणा S1_IPV4c        7
#घोषणा S1_IPV4F        8
#घोषणा S1_TCP44        9
#घोषणा S1_IPV6         10
#घोषणा S1_IPV6L        11
#घोषणा S1_IPV6c        12
#घोषणा S1_TCP64        13
#घोषणा S1_TCPSQ        14
#घोषणा S1_TCPFG        15
#घोषणा	S1_TCPHL	16
#घोषणा	S1_TCPHc	17
#घोषणा	S1_CLNP		18
#घोषणा	S1_CLNP2	19
#घोषणा	S1_DROP		20
#घोषणा	S2_HTTP		21
#घोषणा	S1_ESP4		22
#घोषणा	S1_AH4		23
#घोषणा	S1_ESP6		24
#घोषणा	S1_AH6		25

#घोषणा CAS_PROG_IP46TCP4_PREAMBLE \
अणु "packet arrival?", 0xffff, 0x0000, OP_NP,  6, S1_VLAN,  0, S1_PCKT,  \
  CL_REG, 0x3ff, 1, 0x0, 0x0000पूर्ण, \
अणु "VLAN?", 0xffff, 0x8100, OP_EQ,  1, S1_CFI,   0, S1_8023,  \
  IM_CTL, 0x00a,  3, 0x0, 0xffffपूर्ण, \
अणु "CFI?", 0x1000, 0x1000, OP_EQ,  0, S1_DROP,  1, S1_8023, \
  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण, \
अणु "8023?", 0xffff, 0x0600, OP_LT,  1, S1_LLC,   0, S1_IPV4, \
  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण, \
अणु "LLC?", 0xffff, 0xaaaa, OP_EQ,  1, S1_LLCc,  0, S1_CLNP, \
  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण, \
अणु "LLCc?", 0xff00, 0x0300, OP_EQ,  2, S1_IPV4,  0, S1_CLNP, \
  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण, \
अणु "IPV4?", 0xffff, 0x0800, OP_EQ,  1, S1_IPV4c, 0, S1_IPV6, \
  LD_SAP, 0x100,  3, 0x0, 0xffffपूर्ण, \
अणु "IPV4 cont?", 0xff00, 0x4500, OP_EQ,  3, S1_IPV4F, 0, S1_CLNP, \
  LD_SUM, 0x00a,  1, 0x0, 0x0000पूर्ण, \
अणु "IPV4 frag?", 0x3fff, 0x0000, OP_EQ,  1, S1_TCP44, 0, S1_CLNP, \
  LD_LEN, 0x03e,  1, 0x0, 0xffffपूर्ण, \
अणु "TCP44?", 0x00ff, 0x0006, OP_EQ,  7, S1_TCPSQ, 0, S1_CLNP, \
  LD_FID, 0x182,  1, 0x0, 0xffffपूर्ण, /* FID IP4&TCP src+dst */ \
अणु "IPV6?", 0xffff, 0x86dd, OP_EQ,  1, S1_IPV6L, 0, S1_CLNP,  \
  LD_SUM, 0x015,  1, 0x0, 0x0000पूर्ण, \
अणु "IPV6 len", 0xf000, 0x6000, OP_EQ,  0, S1_IPV6c, 0, S1_CLNP, \
  IM_R1,  0x128,  1, 0x0, 0xffffपूर्ण, \
अणु "IPV6 cont?", 0x0000, 0x0000, OP_EQ,  3, S1_TCP64, 0, S1_CLNP, \
  LD_FID, 0x484,  1, 0x0, 0xffffपूर्ण, /* FID IP6&TCP src+dst */ \
अणु "TCP64?", 0xff00, 0x0600, OP_EQ, 18, S1_TCPSQ, 0, S1_CLNP, \
  LD_LEN, 0x03f,  1, 0x0, 0xffffपूर्ण

#अगर_घोषित USE_HP_IP46TCP4
अटल cas_hp_inst_t cas_prog_ip46tcp4tab[] = अणु
	CAS_PROG_IP46TCP4_PREAMBLE,
	अणु "TCP seq", /* DADDR should poपूर्णांक to dest port */
	  0x0000, 0x0000, OP_EQ, 0, S1_TCPFG, 4, S1_TCPFG, LD_SEQ,
	  0x081,  3, 0x0, 0xffffपूर्ण, /* Load TCP seq # */
	अणु "TCP control flags", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHL, 0,
	  S1_TCPHL, ST_FLG, 0x045,  3, 0x0, 0x002fपूर्ण, /* Load TCP flags */
	अणु "TCP length", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHc, 0,
	  S1_TCPHc, LD_R1,  0x205,  3, 0xB, 0xf000पूर्ण,
	अणु "TCP length cont", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0,
	  S1_PCKT,  LD_HDR, 0x0ff,  3, 0x0, 0xffffपूर्ण,
	अणु "Cleanup", 0x0000, 0x0000, OP_EQ,  0, S1_CLNP2,  0, S1_CLNP2,
	  IM_CTL, 0x001,  3, 0x0, 0x0001पूर्ण,
	अणु "Cleanup 2", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTL, 0x000,  0, 0x0, 0x0000पूर्ण,
	अणु "Drop packet", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTL, 0x080,  3, 0x0, 0xffffपूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;
#अगर_घोषित HP_IP46TCP4_DEFAULT
#घोषणा CAS_HP_FIRMWARE               cas_prog_ip46tcp4tab
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * Alternate table load which excludes HTTP server traffic from reassembly.
 * It is substantially similar to the basic table, with one extra state
 * and a few extra compares. */
#अगर_घोषित USE_HP_IP46TCP4NOHTTP
अटल cas_hp_inst_t cas_prog_ip46tcp4nohttptab[] = अणु
	CAS_PROG_IP46TCP4_PREAMBLE,
	अणु "TCP seq", /* DADDR should poपूर्णांक to dest port */
	  0xFFFF, 0x0080, OP_EQ,  0, S2_HTTP,  0, S1_TCPFG, LD_SEQ,
	  0x081,  3, 0x0, 0xffffपूर्ण , /* Load TCP seq # */
	अणु "TCP control flags", 0xFFFF, 0x8080, OP_EQ,  0, S2_HTTP,  0,
	  S1_TCPHL, ST_FLG, 0x145,  2, 0x0, 0x002f, पूर्ण, /* Load TCP flags */
	अणु "TCP length", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHc, 0, S1_TCPHc,
	  LD_R1,  0x205,  3, 0xB, 0xf000पूर्ण,
	अणु "TCP length cont", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  LD_HDR, 0x0ff,  3, 0x0, 0xffffपूर्ण,
	अणु "Cleanup", 0x0000, 0x0000, OP_EQ,  0, S1_CLNP2,  0, S1_CLNP2,
	  IM_CTL, 0x001,  3, 0x0, 0x0001पूर्ण,
	अणु "Cleanup 2", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  CL_REG, 0x002,  3, 0x0, 0x0000पूर्ण,
	अणु "Drop packet", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTL, 0x080,  3, 0x0, 0xffffपूर्ण,
	अणु "No HTTP", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTL, 0x044,  3, 0x0, 0xffffपूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;
#अगर_घोषित HP_IP46TCP4NOHTTP_DEFAULT
#घोषणा CAS_HP_FIRMWARE               cas_prog_ip46tcp4nohttptab
#पूर्ण_अगर
#पूर्ण_अगर

/* match step #s क्रम IP4FRAG */
#घोषणा	S3_IPV6c	11
#घोषणा	S3_TCP64	12
#घोषणा	S3_TCPSQ	13
#घोषणा	S3_TCPFG	14
#घोषणा	S3_TCPHL	15
#घोषणा	S3_TCPHc	16
#घोषणा	S3_FRAG		17
#घोषणा	S3_FOFF		18
#घोषणा	S3_CLNP		19

#अगर_घोषित USE_HP_IP4FRAG
अटल cas_hp_inst_t cas_prog_ip4fragtab[] = अणु
	अणु "packet arrival?", 0xffff, 0x0000, OP_NP,  6, S1_VLAN,  0, S1_PCKT,
	  CL_REG, 0x3ff, 1, 0x0, 0x0000पूर्ण,
	अणु "VLAN?", 0xffff, 0x8100, OP_EQ,  1, S1_CFI,   0, S1_8023,
	  IM_CTL, 0x00a,  3, 0x0, 0xffffपूर्ण,
	अणु "CFI?", 0x1000, 0x1000, OP_EQ,  0, S3_CLNP,  1, S1_8023,
	  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण,
	अणु "8023?", 0xffff, 0x0600, OP_LT,  1, S1_LLC,   0, S1_IPV4,
	  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण,
	अणु "LLC?", 0xffff, 0xaaaa, OP_EQ,  1, S1_LLCc,  0, S3_CLNP,
	  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण,
	अणु "LLCc?",0xff00, 0x0300, OP_EQ,  2, S1_IPV4,  0, S3_CLNP,
	  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण,
	अणु "IPV4?", 0xffff, 0x0800, OP_EQ,  1, S1_IPV4c, 0, S1_IPV6,
	  LD_SAP, 0x100,  3, 0x0, 0xffffपूर्ण,
	अणु "IPV4 cont?", 0xff00, 0x4500, OP_EQ,  3, S1_IPV4F, 0, S3_CLNP,
	  LD_SUM, 0x00a,  1, 0x0, 0x0000पूर्ण,
	अणु "IPV4 frag?", 0x3fff, 0x0000, OP_EQ,  1, S1_TCP44, 0, S3_FRAG,
	  LD_LEN, 0x03e,  3, 0x0, 0xffffपूर्ण,
	अणु "TCP44?", 0x00ff, 0x0006, OP_EQ,  7, S3_TCPSQ, 0, S3_CLNP,
	  LD_FID, 0x182,  3, 0x0, 0xffffपूर्ण, /* FID IP4&TCP src+dst */
	अणु "IPV6?", 0xffff, 0x86dd, OP_EQ,  1, S3_IPV6c, 0, S3_CLNP,
	  LD_SUM, 0x015,  1, 0x0, 0x0000पूर्ण,
	अणु "IPV6 cont?", 0xf000, 0x6000, OP_EQ,  3, S3_TCP64, 0, S3_CLNP,
	  LD_FID, 0x484,  1, 0x0, 0xffffपूर्ण, /* FID IP6&TCP src+dst */
	अणु "TCP64?", 0xff00, 0x0600, OP_EQ, 18, S3_TCPSQ, 0, S3_CLNP,
	  LD_LEN, 0x03f,  1, 0x0, 0xffffपूर्ण,
	अणु "TCP seq",	/* DADDR should poपूर्णांक to dest port */
	  0x0000, 0x0000, OP_EQ,  0, S3_TCPFG, 4, S3_TCPFG, LD_SEQ,
	  0x081,  3, 0x0, 0xffffपूर्ण, /* Load TCP seq # */
	अणु "TCP control flags", 0x0000, 0x0000, OP_EQ,  0, S3_TCPHL, 0,
	  S3_TCPHL, ST_FLG, 0x045,  3, 0x0, 0x002fपूर्ण, /* Load TCP flags */
	अणु "TCP length", 0x0000, 0x0000, OP_EQ,  0, S3_TCPHc, 0, S3_TCPHc,
	  LD_R1,  0x205,  3, 0xB, 0xf000पूर्ण,
	अणु "TCP length cont", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  LD_HDR, 0x0ff,  3, 0x0, 0xffffपूर्ण,
	अणु "IP4 Fragment", 0x0000, 0x0000, OP_EQ,  0, S3_FOFF,  0, S3_FOFF,
	  LD_FID, 0x103,  3, 0x0, 0xffffपूर्ण, /* FID IP4 src+dst */
	अणु "IP4 frag offset", 0x0000, 0x0000, OP_EQ,  0, S3_FOFF,  0, S3_FOFF,
	  LD_SEQ, 0x040,  1, 0xD, 0xfff8पूर्ण,
	अणु "Cleanup", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTL, 0x001,  3, 0x0, 0x0001पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;
#अगर_घोषित HP_IP4FRAG_DEFAULT
#घोषणा CAS_HP_FIRMWARE               cas_prog_ip4fragtab
#पूर्ण_अगर
#पूर्ण_अगर

/*
 * Alternate table which करोes batching without reassembly
 */
#अगर_घोषित USE_HP_IP46TCP4BATCH
अटल cas_hp_inst_t cas_prog_ip46tcp4batchtab[] = अणु
	CAS_PROG_IP46TCP4_PREAMBLE,
	अणु "TCP seq",	/* DADDR should poपूर्णांक to dest port */
	  0x0000, 0x0000, OP_EQ,  0, S1_TCPFG, 0, S1_TCPFG, LD_SEQ,
	  0x081,  3, 0x0, 0xffffपूर्ण, /* Load TCP seq # */
	अणु "TCP control flags", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHL, 0,
	  S1_TCPHL, ST_FLG, 0x000,  3, 0x0, 0x0000पूर्ण, /* Load TCP flags */
	अणु "TCP length", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHc, 0,
	  S1_TCPHc, LD_R1,  0x205,  3, 0xB, 0xf000पूर्ण,
	अणु "TCP length cont", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0,
	  S1_PCKT,  IM_CTL, 0x040,  3, 0x0, 0xffffपूर्ण, /* set batch bit */
	अणु "Cleanup", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTL, 0x001,  3, 0x0, 0x0001पूर्ण,
	अणु "Drop packet", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0,
	  S1_PCKT,  IM_CTL, 0x080,  3, 0x0, 0xffffपूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;
#अगर_घोषित HP_IP46TCP4BATCH_DEFAULT
#घोषणा CAS_HP_FIRMWARE               cas_prog_ip46tcp4batchtab
#पूर्ण_अगर
#पूर्ण_अगर

/* Workaround क्रम Cassini rev2 descriptor corruption problem.
 * Does batching without reassembly, and sets the SAP to a known
 * data pattern क्रम all packets.
 */
#अगर_घोषित USE_HP_WORKAROUND
अटल cas_hp_inst_t  cas_prog_workaroundtab[] = अणु
	अणु "packet arrival?", 0xffff, 0x0000, OP_NP,  6, S1_VLAN,  0,
	  S1_PCKT,  CL_REG, 0x3ff,  1, 0x0, 0x0000पूर्ण ,
	अणु "VLAN?", 0xffff, 0x8100, OP_EQ,  1, S1_CFI, 0, S1_8023,
	  IM_CTL, 0x04a,  3, 0x0, 0xffffपूर्ण,
	अणु "CFI?", 0x1000, 0x1000, OP_EQ,  0, S1_CLNP,  1, S1_8023,
	  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण,
	अणु "8023?", 0xffff, 0x0600, OP_LT,  1, S1_LLC,   0, S1_IPV4,
	  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण,
	अणु "LLC?", 0xffff, 0xaaaa, OP_EQ,  1, S1_LLCc,  0, S1_CLNP,
	  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण,
	अणु "LLCc?", 0xff00, 0x0300, OP_EQ,  2, S1_IPV4,  0, S1_CLNP,
	  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण,
	अणु "IPV4?", 0xffff, 0x0800, OP_EQ,  1, S1_IPV4c, 0, S1_IPV6,
	  IM_SAP, 0x6AE,  3, 0x0, 0xffffपूर्ण,
	अणु "IPV4 cont?", 0xff00, 0x4500, OP_EQ,  3, S1_IPV4F, 0, S1_CLNP,
	  LD_SUM, 0x00a,  1, 0x0, 0x0000पूर्ण,
	अणु "IPV4 frag?", 0x3fff, 0x0000, OP_EQ,  1, S1_TCP44, 0, S1_CLNP,
	  LD_LEN, 0x03e,  1, 0x0, 0xffffपूर्ण,
	अणु "TCP44?", 0x00ff, 0x0006, OP_EQ,  7, S1_TCPSQ, 0, S1_CLNP,
	  LD_FID, 0x182,  3, 0x0, 0xffffपूर्ण, /* FID IP4&TCP src+dst */
	अणु "IPV6?", 0xffff, 0x86dd, OP_EQ,  1, S1_IPV6L, 0, S1_CLNP,
	  LD_SUM, 0x015,  1, 0x0, 0x0000पूर्ण,
	अणु "IPV6 len", 0xf000, 0x6000, OP_EQ,  0, S1_IPV6c, 0, S1_CLNP,
	  IM_R1,  0x128,  1, 0x0, 0xffffपूर्ण,
	अणु "IPV6 cont?", 0x0000, 0x0000, OP_EQ,  3, S1_TCP64, 0, S1_CLNP,
	  LD_FID, 0x484,  1, 0x0, 0xffffपूर्ण, /* FID IP6&TCP src+dst */
	अणु "TCP64?", 0xff00, 0x0600, OP_EQ, 18, S1_TCPSQ, 0, S1_CLNP,
	  LD_LEN, 0x03f,  1, 0x0, 0xffffपूर्ण,
	अणु "TCP seq",      /* DADDR should poपूर्णांक to dest port */
	  0x0000, 0x0000, OP_EQ,  0, S1_TCPFG, 4, S1_TCPFG, LD_SEQ,
	  0x081,  3, 0x0, 0xffffपूर्ण, /* Load TCP seq # */
	अणु "TCP control flags", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHL, 0,
	  S1_TCPHL, ST_FLG, 0x045,  3, 0x0, 0x002fपूर्ण, /* Load TCP flags */
	अणु "TCP length", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHc, 0, S1_TCPHc,
	  LD_R1,  0x205,  3, 0xB, 0xf000पूर्ण,
	अणु "TCP length cont", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0,
	  S1_PCKT,  LD_HDR, 0x0ff,  3, 0x0, 0xffffपूर्ण,
	अणु "Cleanup", 0x0000, 0x0000, OP_EQ,  0, S1_CLNP2, 0, S1_CLNP2,
	  IM_SAP, 0x6AE,  3, 0x0, 0xffffपूर्ण ,
	अणु "Cleanup 2", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTL, 0x001,  3, 0x0, 0x0001पूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;
#अगर_घोषित HP_WORKAROUND_DEFAULT
#घोषणा CAS_HP_FIRMWARE               cas_prog_workaroundtab
#पूर्ण_अगर
#पूर्ण_अगर

#अगर_घोषित USE_HP_ENCRYPT
अटल cas_hp_inst_t  cas_prog_encryptiontab[] = अणु
	अणु "packet arrival?", 0xffff, 0x0000, OP_NP,  6, S1_VLAN,  0,
	  S1_PCKT,  CL_REG, 0x3ff,  1, 0x0, 0x0000पूर्ण,
	अणु "VLAN?", 0xffff, 0x8100, OP_EQ,  1, S1_CFI,   0, S1_8023,
	  IM_CTL, 0x00a,  3, 0x0, 0xffffपूर्ण,
#अगर 0
//"CFI?", /* 02 FIND CFI and If FIND go to S1_DROP */
//0x1000, 0x1000, OP_EQ,  0, S1_DROP,  1, S1_8023,  CL_REG, 0x000,  0, 0x0, 0x00
	00,
#पूर्ण_अगर
	अणु "CFI?", /* FIND CFI and If FIND go to CleanUP1 (ignore and send to host) */
	  0x1000, 0x1000, OP_EQ,  0, S1_CLNP,  1, S1_8023,
	  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण,
	अणु "8023?", 0xffff, 0x0600, OP_LT,  1, S1_LLC,   0, S1_IPV4,
	  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण,
	अणु "LLC?", 0xffff, 0xaaaa, OP_EQ,  1, S1_LLCc,  0, S1_CLNP,
	  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण,
	अणु "LLCc?", 0xff00, 0x0300, OP_EQ,  2, S1_IPV4,  0, S1_CLNP,
	  CL_REG, 0x000,  0, 0x0, 0x0000पूर्ण,
	अणु "IPV4?", 0xffff, 0x0800, OP_EQ,  1, S1_IPV4c, 0, S1_IPV6,
	  LD_SAP, 0x100,  3, 0x0, 0xffffपूर्ण,
	अणु "IPV4 cont?", 0xff00, 0x4500, OP_EQ,  3, S1_IPV4F, 0, S1_CLNP,
	  LD_SUM, 0x00a,  1, 0x0, 0x0000पूर्ण,
	अणु "IPV4 frag?", 0x3fff, 0x0000, OP_EQ,  1, S1_TCP44, 0, S1_CLNP,
	  LD_LEN, 0x03e,  1, 0x0, 0xffffपूर्ण,
	अणु "TCP44?", 0x00ff, 0x0006, OP_EQ,  7, S1_TCPSQ, 0, S1_ESP4,
	  LD_FID, 0x182,  1, 0x0, 0xffffपूर्ण, /* FID IP4&TCP src+dst */
	अणु "IPV6?", 0xffff, 0x86dd, OP_EQ,  1, S1_IPV6L, 0, S1_CLNP,
	  LD_SUM, 0x015,  1, 0x0, 0x0000पूर्ण,
	अणु "IPV6 len", 0xf000, 0x6000, OP_EQ,  0, S1_IPV6c, 0, S1_CLNP,
	  IM_R1,  0x128,  1, 0x0, 0xffffपूर्ण,
	अणु "IPV6 cont?", 0x0000, 0x0000, OP_EQ,  3, S1_TCP64, 0, S1_CLNP,
	  LD_FID, 0x484,  1, 0x0, 0xffffपूर्ण, /*  FID IP6&TCP src+dst */
	अणु "TCP64?",
#अगर 0
//@@@0xff00, 0x0600, OP_EQ, 18, S1_TCPSQ, 0, S1_ESP6,  LD_LEN, 0x03f,  1, 0x0, 0xffff,
#पूर्ण_अगर
	  0xff00, 0x0600, OP_EQ, 12, S1_TCPSQ, 0, S1_ESP6,  LD_LEN,
	  0x03f,  1, 0x0, 0xffffपूर्ण,
	अणु "TCP seq", /* 14:DADDR should poपूर्णांक to dest port */
	  0xFFFF, 0x0080, OP_EQ,  0, S2_HTTP,  0, S1_TCPFG, LD_SEQ,
	  0x081,  3, 0x0, 0xffffपूर्ण, /* Load TCP seq # */
	अणु "TCP control flags", 0xFFFF, 0x8080, OP_EQ,  0, S2_HTTP,  0,
	  S1_TCPHL, ST_FLG, 0x145,  2, 0x0, 0x002fपूर्ण, /* Load TCP flags */
	अणु "TCP length", 0x0000, 0x0000, OP_EQ,  0, S1_TCPHc, 0, S1_TCPHc,
	  LD_R1,  0x205,  3, 0xB, 0xf000पूर्ण ,
	अणु "TCP length cont", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0,
	  S1_PCKT,  LD_HDR, 0x0ff,  3, 0x0, 0xffffपूर्ण,
	अणु "Cleanup", 0x0000, 0x0000, OP_EQ,  0, S1_CLNP2,  0, S1_CLNP2,
	  IM_CTL, 0x001,  3, 0x0, 0x0001पूर्ण,
	अणु "Cleanup 2", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  CL_REG, 0x002,  3, 0x0, 0x0000पूर्ण,
	अणु "Drop packet", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTL, 0x080,  3, 0x0, 0xffffपूर्ण,
	अणु "No HTTP", 0x0000, 0x0000, OP_EQ,  0, S1_PCKT,  0, S1_PCKT,
	  IM_CTL, 0x044,  3, 0x0, 0xffffपूर्ण,
	अणु "IPV4 ESP encrypted?",  /* S1_ESP4 */
	  0x00ff, 0x0032, OP_EQ,  0, S1_CLNP2, 0, S1_AH4, IM_CTL,
	  0x021, 1,  0x0, 0xffffपूर्ण,
	अणु "IPV4 AH encrypted?",   /* S1_AH4 */
	  0x00ff, 0x0033, OP_EQ,  0, S1_CLNP2, 0, S1_CLNP, IM_CTL,
	  0x021, 1,  0x0, 0xffffपूर्ण,
	अणु "IPV6 ESP encrypted?",  /* S1_ESP6 */
#अगर 0
//@@@0x00ff, 0x0032, OP_EQ,  0, S1_CLNP2, 0, S1_AH6, IM_CTL, 0x021, 1,  0x0, 0xffff,
#पूर्ण_अगर
	  0xff00, 0x3200, OP_EQ,  0, S1_CLNP2, 0, S1_AH6, IM_CTL,
	  0x021, 1,  0x0, 0xffffपूर्ण,
	अणु "IPV6 AH encrypted?",   /* S1_AH6 */
#अगर 0
//@@@0x00ff, 0x0033, OP_EQ,  0, S1_CLNP2, 0, S1_CLNP, IM_CTL, 0x021, 1,  0x0, 0xffff,
#पूर्ण_अगर
	  0xff00, 0x3300, OP_EQ,  0, S1_CLNP2, 0, S1_CLNP, IM_CTL,
	  0x021, 1,  0x0, 0xffffपूर्ण,
	अणु शून्य पूर्ण,
पूर्ण;
#अगर_घोषित HP_ENCRYPT_DEFAULT
#घोषणा CAS_HP_FIRMWARE               cas_prog_encryptiontab
#पूर्ण_अगर
#पूर्ण_अगर

अटल cas_hp_inst_t cas_prog_null[] = अणु अणुशून्यपूर्ण पूर्ण;
#अगर_घोषित HP_शून्य_DEFAULT
#घोषणा CAS_HP_FIRMWARE               cas_prog_null
#पूर्ण_अगर

/* phy types */
#घोषणा   CAS_PHY_UNKNOWN       0x00
#घोषणा   CAS_PHY_SERDES        0x01
#घोषणा   CAS_PHY_MII_MDIO0     0x02
#घोषणा   CAS_PHY_MII_MDIO1     0x04
#घोषणा   CAS_PHY_MII(x)        ((x) & (CAS_PHY_MII_MDIO0 | CAS_PHY_MII_MDIO1))

/* _RING_INDEX is the index क्रम the ring sizes to be used.  _RING_SIZE
 * is the actual size. the शेष index क्रम the various rings is
 * 8. NOTE: there a bunch of alignment स्थिरraपूर्णांकs क्रम the rings. to
 * deal with that, i just allocate rings to create the desired
 * alignment. here are the स्थिरraपूर्णांकs:
 *   RX DESC and COMP rings must be 8KB aligned
 *   TX DESC must be 2KB aligned.
 * अगर you change the numbers, be cognizant of how the alignment will change
 * in INIT_BLOCK as well.
 */

#घोषणा DESC_RING_I_TO_S(x)  (32*(1 << (x)))
#घोषणा COMP_RING_I_TO_S(x)  (128*(1 << (x)))
#घोषणा TX_DESC_RING_INDEX 4  /* 512 = 8k */
#घोषणा RX_DESC_RING_INDEX 4  /* 512 = 8k */
#घोषणा RX_COMP_RING_INDEX 4  /* 2048 = 64k: should be 4x rx ring size */

#अगर (TX_DESC_RING_INDEX > 8) || (TX_DESC_RING_INDEX < 0)
#त्रुटि TX_DESC_RING_INDEX must be between 0 and 8
#पूर्ण_अगर

#अगर (RX_DESC_RING_INDEX > 8) || (RX_DESC_RING_INDEX < 0)
#त्रुटि RX_DESC_RING_INDEX must be between 0 and 8
#पूर्ण_अगर

#अगर (RX_COMP_RING_INDEX > 8) || (RX_COMP_RING_INDEX < 0)
#त्रुटि RX_COMP_RING_INDEX must be between 0 and 8
#पूर्ण_अगर

#घोषणा N_TX_RINGS                    MAX_TX_RINGS      /* क्रम QoS */
#घोषणा N_TX_RINGS_MASK               MAX_TX_RINGS_MASK
#घोषणा N_RX_DESC_RINGS               MAX_RX_DESC_RINGS /* 1 क्रम ipsec */
#घोषणा N_RX_COMP_RINGS               0x1 /* क्रम mult. PCI पूर्णांकerrupts */

/* number of flows that can go through re-assembly */
#घोषणा N_RX_FLOWS                    64

#घोषणा TX_DESC_RING_SIZE  DESC_RING_I_TO_S(TX_DESC_RING_INDEX)
#घोषणा RX_DESC_RING_SIZE  DESC_RING_I_TO_S(RX_DESC_RING_INDEX)
#घोषणा RX_COMP_RING_SIZE  COMP_RING_I_TO_S(RX_COMP_RING_INDEX)
#घोषणा TX_DESC_RINGN_INDEX(x) TX_DESC_RING_INDEX
#घोषणा RX_DESC_RINGN_INDEX(x) RX_DESC_RING_INDEX
#घोषणा RX_COMP_RINGN_INDEX(x) RX_COMP_RING_INDEX
#घोषणा TX_DESC_RINGN_SIZE(x)  TX_DESC_RING_SIZE
#घोषणा RX_DESC_RINGN_SIZE(x)  RX_DESC_RING_SIZE
#घोषणा RX_COMP_RINGN_SIZE(x)  RX_COMP_RING_SIZE

/* convert values */
#घोषणा CAS_BASE(x, y)                (((y) << (x ## _SHIFT)) & (x ## _MASK))
#घोषणा CAS_VAL(x, y)                 (((y) & (x ## _MASK)) >> (x ## _SHIFT))
#घोषणा CAS_TX_RINGN_BASE(y)          ((TX_DESC_RINGN_INDEX(y) << \
                                        TX_CFG_DESC_RINGN_SHIFT(y)) & \
                                        TX_CFG_DESC_RINGN_MASK(y))

/* min is 2k, but we can't do jumbo frames unless it's at least 8k */
#घोषणा CAS_MIN_PAGE_SHIFT            11 /* 2048 */
#घोषणा CAS_JUMBO_PAGE_SHIFT          13 /* 8192 */
#घोषणा CAS_MAX_PAGE_SHIFT            14 /* 16384 */

#घोषणा TX_DESC_BUFLEN_MASK         0x0000000000003FFFULL /* buffer length in
							     bytes. 0 - 9256 */
#घोषणा TX_DESC_BUFLEN_SHIFT        0
#घोषणा TX_DESC_CSUM_START_MASK     0x00000000001F8000ULL /* checksum start. #
							     of bytes to be
							     skipped beक्रमe
							     csum calc begins.
							     value must be
							     even */
#घोषणा TX_DESC_CSUM_START_SHIFT    15
#घोषणा TX_DESC_CSUM_STUFF_MASK     0x000000001FE00000ULL /* checksum stuff.
							     byte offset w/in
							     the pkt क्रम the
							     1st csum byte.
							     must be > 8 */
#घोषणा TX_DESC_CSUM_STUFF_SHIFT    21
#घोषणा TX_DESC_CSUM_EN             0x0000000020000000ULL /* enable checksum */
#घोषणा TX_DESC_खातापूर्ण                 0x0000000040000000ULL /* end of frame */
#घोषणा TX_DESC_SOF                 0x0000000080000000ULL /* start of frame */
#घोषणा TX_DESC_INTME               0x0000000100000000ULL /* पूर्णांकerrupt me */
#घोषणा TX_DESC_NO_CRC              0x0000000200000000ULL /* debugging only.
							     CRC will not be
							     inserted पूर्णांकo
							     outgoing frame. */
काष्ठा cas_tx_desc अणु
	__le64     control;
	__le64     buffer;
पूर्ण;

/* descriptor ring क्रम मुक्त buffers contains page-sized buffers. the index
 * value is not used by the hw in any way. it's just stored and वापसed in
 * the completion ring.
 */
काष्ठा cas_rx_desc अणु
	__le64     index;
	__le64     buffer;
पूर्ण;

/* received packets are put on the completion ring. */
/* word 1 */
#घोषणा RX_COMP1_DATA_SIZE_MASK           0x0000000007FFE000ULL
#घोषणा RX_COMP1_DATA_SIZE_SHIFT          13
#घोषणा RX_COMP1_DATA_OFF_MASK            0x000001FFF8000000ULL
#घोषणा RX_COMP1_DATA_OFF_SHIFT           27
#घोषणा RX_COMP1_DATA_INDEX_MASK          0x007FFE0000000000ULL
#घोषणा RX_COMP1_DATA_INDEX_SHIFT         41
#घोषणा RX_COMP1_SKIP_MASK                0x0180000000000000ULL
#घोषणा RX_COMP1_SKIP_SHIFT               55
#घोषणा RX_COMP1_RELEASE_NEXT             0x0200000000000000ULL
#घोषणा RX_COMP1_SPLIT_PKT                0x0400000000000000ULL
#घोषणा RX_COMP1_RELEASE_FLOW             0x0800000000000000ULL
#घोषणा RX_COMP1_RELEASE_DATA             0x1000000000000000ULL
#घोषणा RX_COMP1_RELEASE_HDR              0x2000000000000000ULL
#घोषणा RX_COMP1_TYPE_MASK                0xC000000000000000ULL
#घोषणा RX_COMP1_TYPE_SHIFT               62

/* word 2 */
#घोषणा RX_COMP2_NEXT_INDEX_MASK          0x00000007FFE00000ULL
#घोषणा RX_COMP2_NEXT_INDEX_SHIFT         21
#घोषणा RX_COMP2_HDR_SIZE_MASK            0x00000FF800000000ULL
#घोषणा RX_COMP2_HDR_SIZE_SHIFT           35
#घोषणा RX_COMP2_HDR_OFF_MASK             0x0003F00000000000ULL
#घोषणा RX_COMP2_HDR_OFF_SHIFT            44
#घोषणा RX_COMP2_HDR_INDEX_MASK           0xFFFC000000000000ULL
#घोषणा RX_COMP2_HDR_INDEX_SHIFT          50

/* word 3 */
#घोषणा RX_COMP3_SMALL_PKT                0x0000000000000001ULL
#घोषणा RX_COMP3_JUMBO_PKT                0x0000000000000002ULL
#घोषणा RX_COMP3_JUMBO_HDR_SPLIT_EN       0x0000000000000004ULL
#घोषणा RX_COMP3_CSUM_START_MASK          0x000000000007F000ULL
#घोषणा RX_COMP3_CSUM_START_SHIFT         12
#घोषणा RX_COMP3_FLOWID_MASK              0x0000000001F80000ULL
#घोषणा RX_COMP3_FLOWID_SHIFT             19
#घोषणा RX_COMP3_OPCODE_MASK              0x000000000E000000ULL
#घोषणा RX_COMP3_OPCODE_SHIFT             25
#घोषणा RX_COMP3_FORCE_FLAG               0x0000000010000000ULL
#घोषणा RX_COMP3_NO_ASSIST                0x0000000020000000ULL
#घोषणा RX_COMP3_LOAD_BAL_MASK            0x000001F800000000ULL
#घोषणा RX_COMP3_LOAD_BAL_SHIFT           35
#घोषणा RX_PLUS_COMP3_ENC_PKT             0x0000020000000000ULL /* cas+ */
#घोषणा RX_COMP3_L3_HEAD_OFF_MASK         0x0000FE0000000000ULL /* cas */
#घोषणा RX_COMP3_L3_HEAD_OFF_SHIFT        41
#घोषणा RX_PLUS_COMP_L3_HEAD_OFF_MASK     0x0000FC0000000000ULL /* cas+ */
#घोषणा RX_PLUS_COMP_L3_HEAD_OFF_SHIFT    42
#घोषणा RX_COMP3_SAP_MASK                 0xFFFF000000000000ULL
#घोषणा RX_COMP3_SAP_SHIFT                48

/* word 4 */
#घोषणा RX_COMP4_TCP_CSUM_MASK            0x000000000000FFFFULL
#घोषणा RX_COMP4_TCP_CSUM_SHIFT           0
#घोषणा RX_COMP4_PKT_LEN_MASK             0x000000003FFF0000ULL
#घोषणा RX_COMP4_PKT_LEN_SHIFT            16
#घोषणा RX_COMP4_PERFECT_MATCH_MASK       0x00000003C0000000ULL
#घोषणा RX_COMP4_PERFECT_MATCH_SHIFT      30
#घोषणा RX_COMP4_ZERO                     0x0000080000000000ULL
#घोषणा RX_COMP4_HASH_VAL_MASK            0x0FFFF00000000000ULL
#घोषणा RX_COMP4_HASH_VAL_SHIFT           44
#घोषणा RX_COMP4_HASH_PASS                0x1000000000000000ULL
#घोषणा RX_COMP4_BAD                      0x4000000000000000ULL
#घोषणा RX_COMP4_LEN_MISMATCH             0x8000000000000000ULL

/* we encode the following: ring/index/release. only 14 bits
 * are usable.
 * NOTE: the encoding is dependent upon RX_DESC_RING_SIZE and
 *       MAX_RX_DESC_RINGS. */
#घोषणा RX_INDEX_NUM_MASK                 0x0000000000000FFFULL
#घोषणा RX_INDEX_NUM_SHIFT                0
#घोषणा RX_INDEX_RING_MASK                0x0000000000001000ULL
#घोषणा RX_INDEX_RING_SHIFT               12
#घोषणा RX_INDEX_RELEASE                  0x0000000000002000ULL

काष्ठा cas_rx_comp अणु
	__le64     word1;
	__le64     word2;
	__le64     word3;
	__le64     word4;
पूर्ण;

क्रमागत link_state अणु
	link_करोwn = 0,	/* No link, will retry */
	link_aneg,	/* Autoneg in progress */
	link_क्रमce_try,	/* Try Forced link speed */
	link_क्रमce_ret,	/* Forced mode worked, retrying स्वतःneg */
	link_क्रमce_ok,	/* Stay in क्रमced mode */
	link_up		/* Link is up */
पूर्ण;

प्रकार काष्ठा cas_page अणु
	काष्ठा list_head list;
	काष्ठा page *buffer;
	dma_addr_t dma_addr;
	पूर्णांक used;
पूर्ण cas_page_t;


/* some alignment स्थिरraपूर्णांकs:
 * TX DESC, RX DESC, and RX COMP must each be 8K aligned.
 * TX COMPWB must be 8-byte aligned.
 * to accomplish this, here's what we करो:
 *
 * INIT_BLOCK_RX_COMP  = 64k (alपढ़ोy aligned)
 * INIT_BLOCK_RX_DESC  = 8k
 * INIT_BLOCK_TX       = 8k
 * INIT_BLOCK_RX1_DESC = 8k
 * TX COMPWB
 */
#घोषणा INIT_BLOCK_TX           (TX_DESC_RING_SIZE)
#घोषणा INIT_BLOCK_RX_DESC      (RX_DESC_RING_SIZE)
#घोषणा INIT_BLOCK_RX_COMP      (RX_COMP_RING_SIZE)

काष्ठा cas_init_block अणु
	काष्ठा cas_rx_comp rxcs[N_RX_COMP_RINGS][INIT_BLOCK_RX_COMP];
	काष्ठा cas_rx_desc rxds[N_RX_DESC_RINGS][INIT_BLOCK_RX_DESC];
	काष्ठा cas_tx_desc txds[N_TX_RINGS][INIT_BLOCK_TX];
	__le64 tx_compwb;
पूर्ण;

/* tiny buffers to deal with target पात issue. we allocate a bit
 * over so that we करोn't have target पात issues with these buffers
 * as well.
 */
#घोषणा TX_TINY_BUF_LEN    0x100
#घोषणा TX_TINY_BUF_BLOCK  ((INIT_BLOCK_TX + 1)*TX_TINY_BUF_LEN)

काष्ठा cas_tiny_count अणु
	पूर्णांक nbufs;
	पूर्णांक used;
पूर्ण;

काष्ठा cas अणु
	spinlock_t lock; /* क्रम most bits */
	spinlock_t tx_lock[N_TX_RINGS]; /* tx bits */
	spinlock_t stat_lock[N_TX_RINGS + 1]; /* क्रम stat gathering */
	spinlock_t rx_inuse_lock; /* rx inuse list */
	spinlock_t rx_spare_lock; /* rx spare list */

	व्योम __iomem *regs;
	पूर्णांक tx_new[N_TX_RINGS], tx_old[N_TX_RINGS];
	पूर्णांक rx_old[N_RX_DESC_RINGS];
	पूर्णांक rx_cur[N_RX_COMP_RINGS], rx_new[N_RX_COMP_RINGS];
	पूर्णांक rx_last[N_RX_DESC_RINGS];

	काष्ठा napi_काष्ठा napi;

	/* Set when chip is actually in operational state
	 * (ie. not घातer managed) */
	पूर्णांक hw_running;
	पूर्णांक खोलोed;
	काष्ठा mutex pm_mutex; /* खोलो/बंद/suspend/resume */

	काष्ठा cas_init_block *init_block;
	काष्ठा cas_tx_desc *init_txds[MAX_TX_RINGS];
	काष्ठा cas_rx_desc *init_rxds[MAX_RX_DESC_RINGS];
	काष्ठा cas_rx_comp *init_rxcs[MAX_RX_COMP_RINGS];

	/* we use sk_buffs क्रम tx and pages क्रम rx. the rx skbuffs
	 * are there क्रम flow re-assembly. */
	काष्ठा sk_buff      *tx_skbs[N_TX_RINGS][TX_DESC_RING_SIZE];
	काष्ठा sk_buff_head  rx_flows[N_RX_FLOWS];
	cas_page_t          *rx_pages[N_RX_DESC_RINGS][RX_DESC_RING_SIZE];
	काष्ठा list_head     rx_spare_list, rx_inuse_list;
	पूर्णांक                  rx_spares_needed;

	/* क्रम small packets when copying would be quicker than
	   mapping */
	काष्ठा cas_tiny_count tx_tiny_use[N_TX_RINGS][TX_DESC_RING_SIZE];
	u8 *tx_tiny_bufs[N_TX_RINGS];

	u32			msg_enable;

	/* N_TX_RINGS must be >= N_RX_DESC_RINGS */
	काष्ठा net_device_stats net_stats[N_TX_RINGS + 1];

	u32			pci_cfg[64 >> 2];
	u8                      pci_revision;

	पूर्णांक                     phy_type;
	पूर्णांक			phy_addr;
	u32                     phy_id;
#घोषणा CAS_FLAG_1000MB_CAP     0x00000001
#घोषणा CAS_FLAG_REG_PLUS       0x00000002
#घोषणा CAS_FLAG_TARGET_ABORT   0x00000004
#घोषणा CAS_FLAG_SATURN         0x00000008
#घोषणा CAS_FLAG_RXD_POST_MASK  0x000000F0
#घोषणा CAS_FLAG_RXD_POST_SHIFT 4
#घोषणा CAS_FLAG_RXD_POST(x)    ((1 << (CAS_FLAG_RXD_POST_SHIFT + (x))) & \
                                 CAS_FLAG_RXD_POST_MASK)
#घोषणा CAS_FLAG_ENTROPY_DEV    0x00000100
#घोषणा CAS_FLAG_NO_HW_CSUM     0x00000200
	u32                     cas_flags;
	पूर्णांक                     packet_min; /* minimum packet size */
	पूर्णांक			tx_fअगरo_size;
	पूर्णांक			rx_fअगरo_size;
	पूर्णांक			rx_छोड़ो_off;
	पूर्णांक			rx_छोड़ो_on;
	पूर्णांक                     crc_size;      /* 4 अगर half-duplex */

	पूर्णांक                     pci_irq_INTC;
	पूर्णांक                     min_frame_size; /* क्रम tx fअगरo workaround */

	/* page size allocation */
	पूर्णांक                     page_size;
	पूर्णांक                     page_order;
	पूर्णांक                     mtu_stride;

	u32			mac_rx_cfg;

	/* Autoneg & PHY control */
	पूर्णांक			link_cntl;
	पूर्णांक			link_fcntl;
	क्रमागत link_state		lstate;
	काष्ठा समयr_list	link_समयr;
	पूर्णांक			समयr_ticks;
	काष्ठा work_काष्ठा	reset_task;
#अगर 0
	atomic_t		reset_task_pending;
#अन्यथा
	atomic_t		reset_task_pending;
	atomic_t		reset_task_pending_mtu;
	atomic_t		reset_task_pending_spare;
	atomic_t		reset_task_pending_all;
#पूर्ण_अगर

	/* Link-करोwn problem workaround */
#घोषणा LINK_TRANSITION_UNKNOWN 	0
#घोषणा LINK_TRANSITION_ON_FAILURE 	1
#घोषणा LINK_TRANSITION_STILL_FAILED 	2
#घोषणा LINK_TRANSITION_LINK_UP 	3
#घोषणा LINK_TRANSITION_LINK_CONFIG	4
#घोषणा LINK_TRANSITION_LINK_DOWN	5
#घोषणा LINK_TRANSITION_REQUESTED_RESET	6
	पूर्णांक			link_transition;
	पूर्णांक 			link_transition_jअगरfies_valid;
	अचिन्हित दीर्घ		link_transition_jअगरfies;

	/* Tuning */
	u8 orig_cacheline_size;	/* value when loaded */
#घोषणा CAS_PREF_CACHELINE_SIZE	 0x20	/* Minimum desired */

	/* Diagnostic counters and state. */
	पूर्णांक 			casreg_len; /* reg-space size क्रम dumping */
	u64			छोड़ो_entered;
	u16			छोड़ो_last_समय_recvd;

	dma_addr_t block_dvma, tx_tiny_dvma[N_TX_RINGS];
	काष्ठा pci_dev *pdev;
	काष्ठा net_device *dev;
#अगर defined(CONFIG_OF)
	काष्ठा device_node	*of_node;
#पूर्ण_अगर

	/* Firmware Info */
	u16			fw_load_addr;
	u32			fw_size;
	u8			*fw_data;
पूर्ण;

#घोषणा TX_DESC_NEXT(r, x)  (((x) + 1) & (TX_DESC_RINGN_SIZE(r) - 1))
#घोषणा RX_DESC_ENTRY(r, x) ((x) & (RX_DESC_RINGN_SIZE(r) - 1))
#घोषणा RX_COMP_ENTRY(r, x) ((x) & (RX_COMP_RINGN_SIZE(r) - 1))

#घोषणा TX_BUFF_COUNT(r, x, y)    ((x) <= (y) ? ((y) - (x)) : \
        (TX_DESC_RINGN_SIZE(r) - (x) + (y)))

#घोषणा TX_BUFFS_AVAIL(cp, i)	((cp)->tx_old[(i)] <= (cp)->tx_new[(i)] ? \
        (cp)->tx_old[(i)] + (TX_DESC_RINGN_SIZE(i) - 1) - (cp)->tx_new[(i)] : \
        (cp)->tx_old[(i)] - (cp)->tx_new[(i)] - 1)

#घोषणा CAS_ALIGN(addr, align) \
     (((अचिन्हित दीर्घ) (addr) + ((align) - 1UL)) & ~((align) - 1))

#घोषणा RX_FIFO_SIZE                  16384
#घोषणा EXPANSION_ROM_SIZE            65536

#घोषणा CAS_MC_EXACT_MATCH_SIZE       15
#घोषणा CAS_MC_HASH_SIZE              256
#घोषणा CAS_MC_HASH_MAX              (CAS_MC_EXACT_MATCH_SIZE + \
                                      CAS_MC_HASH_SIZE)

#घोषणा TX_TARGET_ABORT_LEN           0x20
#घोषणा RX_SWIVEL_OFF_VAL             0x2
#घोषणा RX_AE_FREEN_VAL(x)            (RX_DESC_RINGN_SIZE(x) >> 1)
#घोषणा RX_AE_COMP_VAL                (RX_COMP_RING_SIZE >> 1)
#घोषणा RX_BLANK_INTR_PKT_VAL         0x05
#घोषणा RX_BLANK_INTR_TIME_VAL        0x0F
#घोषणा HP_TCP_THRESH_VAL             1530 /* reduce to enable reassembly */

#घोषणा RX_SPARE_COUNT                (RX_DESC_RING_SIZE >> 1)
#घोषणा RX_SPARE_RECOVER_VAL          (RX_SPARE_COUNT >> 2)

#पूर्ण_अगर /* _CASSINI_H */
