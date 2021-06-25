<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MIT) */
// Copyright (c) 2017 Synopsys, Inc. and/or its affiliates.
// sपंचांगmac Support क्रम 5.xx Ethernet QoS cores

#अगर_अघोषित __DWMAC5_H__
#घोषणा __DWMAC5_H__

#घोषणा MAC_DPP_FSM_INT_STATUS		0x00000140
#घोषणा MAC_AXI_SLV_DPE_ADDR_STATUS	0x00000144
#घोषणा MAC_FSM_CONTROL			0x00000148
#घोषणा PRTYEN				BIT(1)
#घोषणा TMOUTEN				BIT(0)

#घोषणा MAC_FPE_CTRL_STS		0x00000234
#घोषणा TRSP				BIT(19)
#घोषणा TVER				BIT(18)
#घोषणा RRSP				BIT(17)
#घोषणा RVER				BIT(16)
#घोषणा SRSP				BIT(2)
#घोषणा SVER				BIT(1)
#घोषणा EFPE				BIT(0)

#घोषणा MAC_PPS_CONTROL			0x00000b70
#घोषणा PPS_MAXIDX(x)			((((x) + 1) * 8) - 1)
#घोषणा PPS_MINIDX(x)			((x) * 8)
#घोषणा PPSx_MASK(x)			GENMASK(PPS_MAXIDX(x), PPS_MINIDX(x))
#घोषणा MCGRENx(x)			BIT(PPS_MAXIDX(x))
#घोषणा TRGTMODSELx(x, val)		\
	GENMASK(PPS_MAXIDX(x) - 1, PPS_MAXIDX(x) - 2) & \
	((val) << (PPS_MAXIDX(x) - 2))
#घोषणा PPSCMDx(x, val)			\
	GENMASK(PPS_MINIDX(x) + 3, PPS_MINIDX(x)) & \
	((val) << PPS_MINIDX(x))
#घोषणा PPSEN0				BIT(4)
#घोषणा MAC_PPSx_TARGET_TIME_SEC(x)	(0x00000b80 + ((x) * 0x10))
#घोषणा MAC_PPSx_TARGET_TIME_NSEC(x)	(0x00000b84 + ((x) * 0x10))
#घोषणा TRGTBUSY0			BIT(31)
#घोषणा TTSL0				GENMASK(30, 0)
#घोषणा MAC_PPSx_INTERVAL(x)		(0x00000b88 + ((x) * 0x10))
#घोषणा MAC_PPSx_WIDTH(x)		(0x00000b8c + ((x) * 0x10))

#घोषणा MTL_EST_CONTROL			0x00000c50
#घोषणा PTOV				GENMASK(31, 24)
#घोषणा PTOV_SHIFT			24
#घोषणा SSWL				BIT(1)
#घोषणा EEST				BIT(0)

#घोषणा MTL_EST_STATUS			0x00000c58
#घोषणा BTRL				GENMASK(11, 8)
#घोषणा BTRL_SHIFT			8
#घोषणा BTRL_MAX			(0xF << BTRL_SHIFT)
#घोषणा SWOL				BIT(7)
#घोषणा SWOL_SHIFT			7
#घोषणा CGCE				BIT(4)
#घोषणा HLBS				BIT(3)
#घोषणा HLBF				BIT(2)
#घोषणा BTRE				BIT(1)
#घोषणा SWLC				BIT(0)

#घोषणा MTL_EST_SCH_ERR			0x00000c60
#घोषणा MTL_EST_FRM_SZ_ERR		0x00000c64
#घोषणा MTL_EST_FRM_SZ_CAP		0x00000c68
#घोषणा SZ_CAP_HBFS_MASK		GENMASK(14, 0)
#घोषणा SZ_CAP_HBFQ_SHIFT		16
#घोषणा SZ_CAP_HBFQ_MASK(_val)		(अणु typeof(_val) (val) = (_val);	\
					((val) > 4 ? GENMASK(18, 16) :	\
					 (val) > 2 ? GENMASK(17, 16) :	\
					 BIT(16)); पूर्ण)

#घोषणा MTL_EST_INT_EN			0x00000c70
#घोषणा IECGCE				CGCE
#घोषणा IEHS				HLBS
#घोषणा IEHF				HLBF
#घोषणा IEBE				BTRE
#घोषणा IECC				SWLC

#घोषणा MTL_EST_GCL_CONTROL		0x00000c80
#घोषणा BTR_LOW				0x0
#घोषणा BTR_HIGH			0x1
#घोषणा CTR_LOW				0x2
#घोषणा CTR_HIGH			0x3
#घोषणा TER				0x4
#घोषणा LLR				0x5
#घोषणा ADDR_SHIFT			8
#घोषणा GCRR				BIT(2)
#घोषणा SRWO				BIT(0)
#घोषणा MTL_EST_GCL_DATA		0x00000c84

#घोषणा MTL_RXP_CONTROL_STATUS		0x00000ca0
#घोषणा RXPI				BIT(31)
#घोषणा NPE				GENMASK(23, 16)
#घोषणा NVE				GENMASK(7, 0)
#घोषणा MTL_RXP_IACC_CTRL_STATUS	0x00000cb0
#घोषणा STARTBUSY			BIT(31)
#घोषणा RXPEIEC				GENMASK(22, 21)
#घोषणा RXPEIEE				BIT(20)
#घोषणा WRRDN				BIT(16)
#घोषणा ADDR				GENMASK(15, 0)
#घोषणा MTL_RXP_IACC_DATA		0x00000cb4
#घोषणा MTL_ECC_CONTROL			0x00000cc0
#घोषणा MEEAO				BIT(8)
#घोषणा TSOEE				BIT(4)
#घोषणा MRXPEE				BIT(3)
#घोषणा MESTEE				BIT(2)
#घोषणा MRXEE				BIT(1)
#घोषणा MTXEE				BIT(0)

#घोषणा MTL_SAFETY_INT_STATUS		0x00000cc4
#घोषणा MCSIS				BIT(31)
#घोषणा MEUIS				BIT(1)
#घोषणा MECIS				BIT(0)
#घोषणा MTL_ECC_INT_ENABLE		0x00000cc8
#घोषणा RPCEIE				BIT(12)
#घोषणा ECEIE				BIT(8)
#घोषणा RXCEIE				BIT(4)
#घोषणा TXCEIE				BIT(0)
#घोषणा MTL_ECC_INT_STATUS		0x00000ccc
#घोषणा MTL_DPP_CONTROL			0x00000ce0
#घोषणा EPSI				BIT(2)
#घोषणा OPE				BIT(1)
#घोषणा EDPP				BIT(0)

#घोषणा DMA_SAFETY_INT_STATUS		0x00001080
#घोषणा MSUIS				BIT(29)
#घोषणा MSCIS				BIT(28)
#घोषणा DEUIS				BIT(1)
#घोषणा DECIS				BIT(0)
#घोषणा DMA_ECC_INT_ENABLE		0x00001084
#घोषणा TCEIE				BIT(0)
#घोषणा DMA_ECC_INT_STATUS		0x00001088

/* EQoS version 5.xx VLAN Tag Filter Fail Packets Queuing */
#घोषणा GMAC_RXQ_CTRL4			0x00000094
#घोषणा GMAC_RXQCTRL_VFFQ_MASK		GENMASK(19, 17)
#घोषणा GMAC_RXQCTRL_VFFQ_SHIFT		17
#घोषणा GMAC_RXQCTRL_VFFQE		BIT(16)

#घोषणा GMAC_INT_FPE_EN			BIT(17)

पूर्णांक dwmac5_safety_feat_config(व्योम __iomem *ioaddr, अचिन्हित पूर्णांक asp);
पूर्णांक dwmac5_safety_feat_irq_status(काष्ठा net_device *ndev,
		व्योम __iomem *ioaddr, अचिन्हित पूर्णांक asp,
		काष्ठा sपंचांगmac_safety_stats *stats);
पूर्णांक dwmac5_safety_feat_dump(काष्ठा sपंचांगmac_safety_stats *stats,
			पूर्णांक index, अचिन्हित दीर्घ *count, स्थिर अक्षर **desc);
पूर्णांक dwmac5_rxp_config(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_tc_entry *entries,
		      अचिन्हित पूर्णांक count);
पूर्णांक dwmac5_flex_pps_config(व्योम __iomem *ioaddr, पूर्णांक index,
			   काष्ठा sपंचांगmac_pps_cfg *cfg, bool enable,
			   u32 sub_second_inc, u32 sysसमय_flags);
पूर्णांक dwmac5_est_configure(व्योम __iomem *ioaddr, काष्ठा sपंचांगmac_est *cfg,
			 अचिन्हित पूर्णांक ptp_rate);
व्योम dwmac5_est_irq_status(व्योम __iomem *ioaddr, काष्ठा net_device *dev,
			   काष्ठा sपंचांगmac_extra_stats *x, u32 txqcnt);
व्योम dwmac5_fpe_configure(व्योम __iomem *ioaddr, u32 num_txq, u32 num_rxq,
			  bool enable);
व्योम dwmac5_fpe_send_mpacket(व्योम __iomem *ioaddr,
			     क्रमागत sपंचांगmac_mpacket_type type);
पूर्णांक dwmac5_fpe_irq_status(व्योम __iomem *ioaddr, काष्ठा net_device *dev);

#पूर्ण_अगर /* __DWMAC5_H__ */
