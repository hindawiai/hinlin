<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित XILINX_LL_TEMAC_H
#घोषणा XILINX_LL_TEMAC_H

#समावेश <linux/netdevice.h>
#समावेश <linux/of.h>
#समावेश <linux/spinlock.h>

#अगर_घोषित CONFIG_PPC_DCR
#समावेश <यंत्र/dcr.h>
#समावेश <यंत्र/dcr-regs.h>
#पूर्ण_अगर

/* packet size info */
#घोषणा XTE_HDR_SIZE			14      /* size of Ethernet header */
#घोषणा XTE_TRL_SIZE			4       /* size of Ethernet trailer (FCS) */
#घोषणा XTE_JUMBO_MTU			9000
#घोषणा XTE_MAX_JUMBO_FRAME_SIZE	(XTE_JUMBO_MTU + XTE_HDR_SIZE + XTE_TRL_SIZE)

/*  Configuration options */

/*  Accept all incoming packets.
 *  This option शेषs to disabled (cleared) */
#घोषणा XTE_OPTION_PROMISC                      (1 << 0)
/*  Jumbo frame support क्रम Tx & Rx.
 *  This option शेषs to disabled (cleared) */
#घोषणा XTE_OPTION_JUMBO                        (1 << 1)
/*  VLAN Rx & Tx frame support.
 *  This option शेषs to disabled (cleared) */
#घोषणा XTE_OPTION_VLAN                         (1 << 2)
/*  Enable recognition of flow control frames on Rx
 *  This option शेषs to enabled (set) */
#घोषणा XTE_OPTION_FLOW_CONTROL                 (1 << 4)
/*  Strip FCS and PAD from incoming frames.
 *  Note: PAD from VLAN frames is not stripped.
 *  This option शेषs to disabled (set) */
#घोषणा XTE_OPTION_FCS_STRIP                    (1 << 5)
/*  Generate FCS field and add PAD स्वतःmatically क्रम outgoing frames.
 *  This option शेषs to enabled (set) */
#घोषणा XTE_OPTION_FCS_INSERT                   (1 << 6)
/*  Enable Length/Type error checking क्रम incoming frames. When this option is
set, the MAC will filter frames that have a mismatched type/length field
and अगर XTE_OPTION_REPORT_RXERR is set, the user is notअगरied when these
types of frames are encountered. When this option is cleared, the MAC will
allow these types of frames to be received.
This option शेषs to enabled (set) */
#घोषणा XTE_OPTION_LENTYPE_ERR                  (1 << 7)
/*  Enable the transmitter.
 *  This option शेषs to enabled (set) */
#घोषणा XTE_OPTION_TXEN                         (1 << 11)
/*  Enable the receiver
*   This option शेषs to enabled (set) */
#घोषणा XTE_OPTION_RXEN                         (1 << 12)

/*  Default options set when device is initialized or reset */
#घोषणा XTE_OPTION_DEFAULTS                     \
	(XTE_OPTION_TXEN |                          \
	 XTE_OPTION_FLOW_CONTROL |                  \
	 XTE_OPTION_RXEN)

/* XPS_LL_TEMAC SDMA रेजिस्टरs definition */

#घोषणा TX_NXTDESC_PTR      0x00            /* r */
#घोषणा TX_CURBUF_ADDR      0x01            /* r */
#घोषणा TX_CURBUF_LENGTH    0x02            /* r */
#घोषणा TX_CURDESC_PTR      0x03            /* rw */
#घोषणा TX_TAILDESC_PTR     0x04            /* rw */
#घोषणा TX_CHNL_CTRL        0x05            /* rw */
/*
 0:7      24:31       IRQTimeout
 8:15     16:23       IRQCount
 16:20    11:15       Reserved
 21       10          0
 22       9           UseIntOnEnd
 23       8           LdIRQCnt
 24       7           IRQEn
 25:28    3:6         Reserved
 29       2           IrqErrEn
 30       1           IrqDlyEn
 31       0           IrqCoalEn
*/
#घोषणा CHNL_CTRL_IRQ_IOE       (1 << 9)
#घोषणा CHNL_CTRL_IRQ_EN        (1 << 7)
#घोषणा CHNL_CTRL_IRQ_ERR_EN    (1 << 2)
#घोषणा CHNL_CTRL_IRQ_DLY_EN    (1 << 1)
#घोषणा CHNL_CTRL_IRQ_COAL_EN   (1 << 0)
#घोषणा TX_IRQ_REG          0x06            /* rw */
/*
  0:7      24:31       DltTmrValue
 8:15     16:23       ClscCntrValue
 16:17    14:15       Reserved
 18:21    10:13       ClscCnt
 22:23    8:9         DlyCnt
 24:28    3::7        Reserved
 29       2           ErrIrq
 30       1           DlyIrq
 31       0           CoalIrq
 */
#घोषणा TX_CHNL_STS         0x07            /* r */
/*
   0:9      22:31   Reserved
 10       21      TailPErr
 11       20      CmpErr
 12       19      AddrErr
 13       18      NxtPErr
 14       17      CurPErr
 15       16      BsyWr
 16:23    8:15    Reserved
 24       7       Error
 25       6       IOE
 26       5       SOE
 27       4       Cmplt
 28       3       SOP
 29       2       EOP
 30       1       EngBusy
 31       0       Reserved
*/

#घोषणा RX_NXTDESC_PTR      0x08            /* r */
#घोषणा RX_CURBUF_ADDR      0x09            /* r */
#घोषणा RX_CURBUF_LENGTH    0x0a            /* r */
#घोषणा RX_CURDESC_PTR      0x0b            /* rw */
#घोषणा RX_TAILDESC_PTR     0x0c            /* rw */
#घोषणा RX_CHNL_CTRL        0x0d            /* rw */
/*
 0:7      24:31       IRQTimeout
 8:15     16:23       IRQCount
 16:20    11:15       Reserved
 21       10          0
 22       9           UseIntOnEnd
 23       8           LdIRQCnt
 24       7           IRQEn
 25:28    3:6         Reserved
 29       2           IrqErrEn
 30       1           IrqDlyEn
 31       0           IrqCoalEn
 */
#घोषणा RX_IRQ_REG          0x0e            /* rw */
#घोषणा IRQ_COAL        (1 << 0)
#घोषणा IRQ_DLY         (1 << 1)
#घोषणा IRQ_ERR         (1 << 2)
#घोषणा IRQ_DMAERR      (1 << 7)            /* this is not करोcumented ??? */
/*
 0:7      24:31       DltTmrValue
 8:15     16:23       ClscCntrValue
 16:17    14:15       Reserved
 18:21    10:13       ClscCnt
 22:23    8:9         DlyCnt
 24:28    3::7        Reserved
*/
#घोषणा RX_CHNL_STS         0x0f        /* r */
#घोषणा CHNL_STS_ENGBUSY    (1 << 1)
#घोषणा CHNL_STS_EOP        (1 << 2)
#घोषणा CHNL_STS_SOP        (1 << 3)
#घोषणा CHNL_STS_CMPLT      (1 << 4)
#घोषणा CHNL_STS_SOE        (1 << 5)
#घोषणा CHNL_STS_IOE        (1 << 6)
#घोषणा CHNL_STS_ERR        (1 << 7)

#घोषणा CHNL_STS_BSYWR      (1 << 16)
#घोषणा CHNL_STS_CURPERR    (1 << 17)
#घोषणा CHNL_STS_NXTPERR    (1 << 18)
#घोषणा CHNL_STS_ADDRERR    (1 << 19)
#घोषणा CHNL_STS_CMPERR     (1 << 20)
#घोषणा CHNL_STS_TAILERR    (1 << 21)
/*
 0:9      22:31   Reserved
 10       21      TailPErr
 11       20      CmpErr
 12       19      AddrErr
 13       18      NxtPErr
 14       17      CurPErr
 15       16      BsyWr
 16:23    8:15    Reserved
 24       7       Error
 25       6       IOE
 26       5       SOE
 27       4       Cmplt
 28       3       SOP
 29       2       EOP
 30       1       EngBusy
 31       0       Reserved
*/

#घोषणा DMA_CONTROL_REG             0x10            /* rw */
#घोषणा DMA_CONTROL_RST                 (1 << 0)
#घोषणा DMA_TAIL_ENABLE                 (1 << 2)

/* XPS_LL_TEMAC direct रेजिस्टरs definition */

#घोषणा XTE_RAF0_OFFSET              0x00
#घोषणा RAF0_RST                        (1 << 0)
#घोषणा RAF0_MCSTREJ                    (1 << 1)
#घोषणा RAF0_BCSTREJ                    (1 << 2)
#घोषणा XTE_TPF0_OFFSET              0x04
#घोषणा XTE_IFGP0_OFFSET             0x08
#घोषणा XTE_ISR0_OFFSET              0x0c
#घोषणा ISR0_HARDACSCMPLT               (1 << 0)
#घोषणा ISR0_AUTONEG                    (1 << 1)
#घोषणा ISR0_RXCMPLT                    (1 << 2)
#घोषणा ISR0_RXREJ                      (1 << 3)
#घोषणा ISR0_RXFIFOOVR                  (1 << 4)
#घोषणा ISR0_TXCMPLT                    (1 << 5)
#घोषणा ISR0_RXDCMLCK                   (1 << 6)

#घोषणा XTE_IPR0_OFFSET              0x10
#घोषणा XTE_IER0_OFFSET              0x14

#घोषणा XTE_MSW0_OFFSET              0x20
#घोषणा XTE_LSW0_OFFSET              0x24
#घोषणा XTE_CTL0_OFFSET              0x28
#घोषणा XTE_RDY0_OFFSET              0x2c

#घोषणा XTE_RSE_MIIM_RR_MASK      0x0002
#घोषणा XTE_RSE_MIIM_WR_MASK      0x0004
#घोषणा XTE_RSE_CFG_RR_MASK       0x0020
#घोषणा XTE_RSE_CFG_WR_MASK       0x0040
#घोषणा XTE_RDY0_HARD_ACS_RDY_MASK  (0x10000)

/* XPS_LL_TEMAC indirect रेजिस्टरs offset definition */

#घोषणा	XTE_RXC0_OFFSET			0x00000200 /* Rx configuration word 0 */
#घोषणा	XTE_RXC1_OFFSET			0x00000240 /* Rx configuration word 1 */
#घोषणा XTE_RXC1_RXRST_MASK		(1 << 31)  /* Receiver reset */
#घोषणा XTE_RXC1_RXJMBO_MASK		(1 << 30)  /* Jumbo frame enable */
#घोषणा XTE_RXC1_RXFCS_MASK		(1 << 29)  /* FCS not stripped */
#घोषणा XTE_RXC1_RXEN_MASK		(1 << 28)  /* Receiver enable */
#घोषणा XTE_RXC1_RXVLAN_MASK		(1 << 27)  /* VLAN enable */
#घोषणा XTE_RXC1_RXHD_MASK		(1 << 26)  /* Half duplex */
#घोषणा XTE_RXC1_RXLT_MASK		(1 << 25)  /* Length/type check disable */

#घोषणा XTE_TXC_OFFSET			0x00000280 /*  Tx configuration */
#घोषणा XTE_TXC_TXRST_MASK		(1 << 31)  /* Transmitter reset */
#घोषणा XTE_TXC_TXJMBO_MASK		(1 << 30)  /* Jumbo frame enable */
#घोषणा XTE_TXC_TXFCS_MASK		(1 << 29)  /* Generate FCS */
#घोषणा XTE_TXC_TXEN_MASK		(1 << 28)  /* Transmitter enable */
#घोषणा XTE_TXC_TXVLAN_MASK		(1 << 27)  /* VLAN enable */
#घोषणा XTE_TXC_TXHD_MASK		(1 << 26)  /* Half duplex */

#घोषणा XTE_FCC_OFFSET			0x000002C0 /* Flow control config */
#घोषणा XTE_FCC_RXFLO_MASK		(1 << 29)  /* Rx flow control enable */
#घोषणा XTE_FCC_TXFLO_MASK		(1 << 30)  /* Tx flow control enable */

#घोषणा XTE_EMCFG_OFFSET		0x00000300 /* EMAC configuration */
#घोषणा XTE_EMCFG_LINKSPD_MASK		0xC0000000 /* Link speed */
#घोषणा XTE_EMCFG_HOSTEN_MASK		(1 << 26)  /* Host पूर्णांकerface enable */
#घोषणा XTE_EMCFG_LINKSPD_10		0x00000000 /* 10 Mbit LINKSPD_MASK */
#घोषणा XTE_EMCFG_LINKSPD_100		(1 << 30)  /* 100 Mbit LINKSPD_MASK */
#घोषणा XTE_EMCFG_LINKSPD_1000		(1 << 31)  /* 1000 Mbit LINKSPD_MASK */

#घोषणा XTE_GMIC_OFFSET			0x00000320 /* RGMII/SGMII config */
#घोषणा XTE_MC_OFFSET			0x00000340 /* MDIO configuration */
#घोषणा XTE_UAW0_OFFSET			0x00000380 /* Unicast address word 0 */
#घोषणा XTE_UAW1_OFFSET			0x00000384 /* Unicast address word 1 */

#घोषणा XTE_MAW0_OFFSET			0x00000388 /* Multicast addr word 0 */
#घोषणा XTE_MAW1_OFFSET			0x0000038C /* Multicast addr word 1 */
#घोषणा XTE_AFM_OFFSET			0x00000390 /* Promiscuous mode */
#घोषणा XTE_AFM_EPPRM_MASK		(1 << 31)  /* Promiscuous mode enable */

/* Interrupt Request status */
#घोषणा XTE_TIS_OFFSET			0x000003A0
#घोषणा TIS_FRIS			(1 << 0)
#घोषणा TIS_MRIS			(1 << 1)
#घोषणा TIS_MWIS			(1 << 2)
#घोषणा TIS_ARIS			(1 << 3)
#घोषणा TIS_AWIS			(1 << 4)
#घोषणा TIS_CRIS			(1 << 5)
#घोषणा TIS_CWIS			(1 << 6)

#घोषणा XTE_TIE_OFFSET			0x000003A4 /* Interrupt enable */

/**  MII Mamagement Control रेजिस्टर (MGTCR) */
#घोषणा XTE_MGTDR_OFFSET		0x000003B0 /* MII data */
#घोषणा XTE_MIIMAI_OFFSET		0x000003B4 /* MII control */

#घोषणा CNTLREG_WRITE_ENABLE_MASK   0x8000
#घोषणा CNTLREG_EMAC1SEL_MASK       0x0400
#घोषणा CNTLREG_ADDRESSCODE_MASK    0x03ff

/* CDMAC descriptor status bit definitions */

#घोषणा STS_CTRL_APP0_ERR         (1 << 31)
#घोषणा STS_CTRL_APP0_IRQONEND    (1 << 30)
/* unकरोccumented */
#घोषणा STS_CTRL_APP0_STOPONEND   (1 << 29)
#घोषणा STS_CTRL_APP0_CMPLT       (1 << 28)
#घोषणा STS_CTRL_APP0_SOP         (1 << 27)
#घोषणा STS_CTRL_APP0_EOP         (1 << 26)
#घोषणा STS_CTRL_APP0_ENGBUSY     (1 << 25)
/* unकरोcumented */
#घोषणा STS_CTRL_APP0_ENGRST      (1 << 24)

#घोषणा TX_CONTROL_CALC_CSUM_MASK   1

#घोषणा MULTICAST_CAM_TABLE_NUM 4

/* TEMAC Synthesis features */
#घोषणा TEMAC_FEATURE_RX_CSUM  (1 << 0)
#घोषणा TEMAC_FEATURE_TX_CSUM  (1 << 1)

/* TX/RX CURDESC_PTR poपूर्णांकs to first descriptor */
/* TX/RX TAILDESC_PTR poपूर्णांकs to last descriptor in linked list */

/**
 * काष्ठा cdmac_bd - LocalLink buffer descriptor क्रमmat
 *
 * app0 bits:
 *	0    Error
 *	1    IrqOnEnd    generate an पूर्णांकerrupt at completion of DMA  op
 *	2    reserved
 *	3    completed   Current descriptor completed
 *	4    SOP         TX - marks first desc/ RX marks first desct
 *	5    EOP         TX marks last desc/RX marks last desc
 *	6    EngBusy     DMA is processing
 *	7    reserved
 *	8:31 application specअगरic
 */
काष्ठा cdmac_bd अणु
	u32 next;	/* Physical address of next buffer descriptor */
	u32 phys;
	u32 len;
	u32 app0;
	u32 app1;	/* TX start << 16 | insert */
	u32 app2;	/* TX csum */
	u32 app3;
	u32 app4;	/* skb क्रम TX length क्रम RX */
पूर्ण;

काष्ठा temac_local अणु
	काष्ठा net_device *ndev;
	काष्ठा device *dev;

	/* Connection to PHY device */
	काष्ठा device_node *phy_node;
	/* For non-device-tree devices */
	अक्षर phy_name[MII_BUS_ID_SIZE + 3];
	phy_पूर्णांकerface_t phy_पूर्णांकerface;

	/* MDIO bus data */
	काष्ठा mii_bus *mii_bus;	/* MII bus reference */

	/* IO रेजिस्टरs, dma functions and IRQs */
	व्योम __iomem *regs;
	व्योम __iomem *sdma_regs;
#अगर_घोषित CONFIG_PPC_DCR
	dcr_host_t sdma_dcrs;
#पूर्ण_अगर
	u32 (*temac_ior)(काष्ठा temac_local *lp, पूर्णांक offset);
	व्योम (*temac_iow)(काष्ठा temac_local *lp, पूर्णांक offset, u32 value);
	u32 (*dma_in)(काष्ठा temac_local *lp, पूर्णांक reg);
	व्योम (*dma_out)(काष्ठा temac_local *lp, पूर्णांक reg, u32 value);

	पूर्णांक tx_irq;
	पूर्णांक rx_irq;
	पूर्णांक emac_num;

	काष्ठा sk_buff **rx_skb;
	spinlock_t rx_lock;
	/* For synchronization of indirect रेजिस्टर access.  Must be
	 * shared mutex between पूर्णांकerfaces in same TEMAC block.
	 */
	spinlock_t *indirect_lock;
	u32 options;			/* Current options word */
	पूर्णांक last_link;
	अचिन्हित पूर्णांक temac_features;

	/* Buffer descriptors */
	काष्ठा cdmac_bd *tx_bd_v;
	dma_addr_t tx_bd_p;
	u32 tx_bd_num;
	काष्ठा cdmac_bd *rx_bd_v;
	dma_addr_t rx_bd_p;
	u32 rx_bd_num;
	पूर्णांक tx_bd_ci;
	पूर्णांक tx_bd_tail;
	पूर्णांक rx_bd_ci;
	पूर्णांक rx_bd_tail;

	/* DMA channel control setup */
	u8 coalesce_count_tx;
	u8 coalesce_delay_tx;
	u8 coalesce_count_rx;
	u8 coalesce_delay_rx;

	काष्ठा delayed_work restart_work;
पूर्ण;

/* Wrappers क्रम temac_ior()/temac_iow() function poपूर्णांकers above */
#घोषणा temac_ior(lp, o) ((lp)->temac_ior(lp, o))
#घोषणा temac_iow(lp, o, v) ((lp)->temac_iow(lp, o, v))

/* xilinx_temac.c */
पूर्णांक temac_indirect_busyरुको(काष्ठा temac_local *lp);
u32 temac_indirect_in32(काष्ठा temac_local *lp, पूर्णांक reg);
u32 temac_indirect_in32_locked(काष्ठा temac_local *lp, पूर्णांक reg);
व्योम temac_indirect_out32(काष्ठा temac_local *lp, पूर्णांक reg, u32 value);
व्योम temac_indirect_out32_locked(काष्ठा temac_local *lp, पूर्णांक reg, u32 value);

/* xilinx_temac_mdio.c */
पूर्णांक temac_mdio_setup(काष्ठा temac_local *lp, काष्ठा platक्रमm_device *pdev);
व्योम temac_mdio_tearकरोwn(काष्ठा temac_local *lp);

#पूर्ण_अगर /* XILINX_LL_TEMAC_H */
