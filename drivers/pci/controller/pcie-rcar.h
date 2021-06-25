<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * PCIe driver क्रम Renesas R-Car SoCs
 *  Copyright (C) 2014-2020 Renesas Electronics Europe Ltd
 *
 * Author: Phil Edworthy <phil.edworthy@renesas.com>
 */

#अगर_अघोषित _PCIE_RCAR_H
#घोषणा _PCIE_RCAR_H

#घोषणा PCIECAR			0x000010
#घोषणा PCIECCTLR		0x000018
#घोषणा  CONFIG_SEND_ENABLE	BIT(31)
#घोषणा  TYPE0			(0 << 8)
#घोषणा  TYPE1			BIT(8)
#घोषणा PCIECDR			0x000020
#घोषणा PCIEMSR			0x000028
#घोषणा PCIEINTXR		0x000400
#घोषणा  ASTINTX		BIT(16)
#घोषणा PCIEPHYSR		0x0007f0
#घोषणा  PHYRDY			BIT(0)
#घोषणा PCIEMSITXR		0x000840

/* Transfer control */
#घोषणा PCIETCTLR		0x02000
#घोषणा  DL_DOWN		BIT(3)
#घोषणा  CFINIT			BIT(0)
#घोषणा PCIETSTR		0x02004
#घोषणा  DATA_LINK_ACTIVE	BIT(0)
#घोषणा PCIEERRFR		0x02020
#घोषणा  UNSUPPORTED_REQUEST	BIT(4)
#घोषणा PCIEMSIFR		0x02044
#घोषणा PCIEMSIALR		0x02048
#घोषणा  MSIFE			BIT(0)
#घोषणा PCIEMSIAUR		0x0204c
#घोषणा PCIEMSIIER		0x02050

/* root port address */
#घोषणा PCIEPRAR(x)		(0x02080 + ((x) * 0x4))

/* local address reg & mask */
#घोषणा PCIELAR(x)		(0x02200 + ((x) * 0x20))
#घोषणा PCIELAMR(x)		(0x02208 + ((x) * 0x20))
#घोषणा  LAM_PREFETCH		BIT(3)
#घोषणा  LAM_64BIT		BIT(2)
#घोषणा  LAR_ENABLE		BIT(1)

/* PCIe address reg & mask */
#घोषणा PCIEPALR(x)		(0x03400 + ((x) * 0x20))
#घोषणा PCIEPAUR(x)		(0x03404 + ((x) * 0x20))
#घोषणा PCIEPAMR(x)		(0x03408 + ((x) * 0x20))
#घोषणा PCIEPTCTLR(x)		(0x0340c + ((x) * 0x20))
#घोषणा  PAR_ENABLE		BIT(31)
#घोषणा  IO_SPACE		BIT(8)

/* Configuration */
#घोषणा PCICONF(x)		(0x010000 + ((x) * 0x4))
#घोषणा  INTDIS			BIT(10)
#घोषणा PMCAP(x)		(0x010040 + ((x) * 0x4))
#घोषणा MSICAP(x)		(0x010050 + ((x) * 0x4))
#घोषणा  MSICAP0_MSIE		BIT(16)
#घोषणा  MSICAP0_MMESCAP_OFFSET	17
#घोषणा  MSICAP0_MMESE_OFFSET	20
#घोषणा  MSICAP0_MMESE_MASK	GENMASK(22, 20)
#घोषणा EXPCAP(x)		(0x010070 + ((x) * 0x4))
#घोषणा VCCAP(x)		(0x010100 + ((x) * 0x4))

/* link layer */
#घोषणा IDSETR0			0x011000
#घोषणा IDSETR1			0x011004
#घोषणा SUBIDSETR		0x011024
#घोषणा TLCTLR			0x011048
#घोषणा MACSR			0x011054
#घोषणा  SPCHGFIN		BIT(4)
#घोषणा  SPCHGFAIL		BIT(6)
#घोषणा  SPCHGSUC		BIT(7)
#घोषणा  LINK_SPEED		(0xf << 16)
#घोषणा  LINK_SPEED_2_5GTS	(1 << 16)
#घोषणा  LINK_SPEED_5_0GTS	(2 << 16)
#घोषणा MACCTLR			0x011058
#घोषणा  MACCTLR_NFTS_MASK	GENMASK(23, 16)	/* The name is from SH7786 */
#घोषणा  SPEED_CHANGE		BIT(24)
#घोषणा  SCRAMBLE_DISABLE	BIT(27)
#घोषणा  LTSMDIS		BIT(31)
#घोषणा  MACCTLR_INIT_VAL	(LTSMDIS | MACCTLR_NFTS_MASK)
#घोषणा PMSR			0x01105c
#घोषणा MACS2R			0x011078
#घोषणा MACCGSPSETR		0x011084
#घोषणा  SPCNGRSN		BIT(31)

/* R-Car H1 PHY */
#घोषणा H1_PCIEPHYADRR		0x04000c
#घोषणा  WRITE_CMD		BIT(16)
#घोषणा  PHY_ACK		BIT(24)
#घोषणा  RATE_POS		12
#घोषणा  LANE_POS		8
#घोषणा  ADR_POS		0
#घोषणा H1_PCIEPHYDOUTR		0x040014

/* R-Car Gen2 PHY */
#घोषणा GEN2_PCIEPHYADDR	0x780
#घोषणा GEN2_PCIEPHYDATA	0x784
#घोषणा GEN2_PCIEPHYCTRL	0x78c

#घोषणा INT_PCI_MSI_NR		32

#घोषणा RCONF(x)		(PCICONF(0) + (x))
#घोषणा RPMCAP(x)		(PMCAP(0) + (x))
#घोषणा REXPCAP(x)		(EXPCAP(0) + (x))
#घोषणा RVCCAP(x)		(VCCAP(0) + (x))

#घोषणा PCIE_CONF_BUS(b)	(((b) & 0xff) << 24)
#घोषणा PCIE_CONF_DEV(d)	(((d) & 0x1f) << 19)
#घोषणा PCIE_CONF_FUNC(f)	(((f) & 0x7) << 16)

#घोषणा RCAR_PCI_MAX_RESOURCES	4
#घोषणा MAX_NR_INBOUND_MAPS	6

काष्ठा rcar_pcie अणु
	काष्ठा device		*dev;
	व्योम __iomem		*base;
पूर्ण;

क्रमागत अणु
	RCAR_PCI_ACCESS_READ,
	RCAR_PCI_ACCESS_WRITE,
पूर्ण;

व्योम rcar_pci_ग_लिखो_reg(काष्ठा rcar_pcie *pcie, u32 val, अचिन्हित पूर्णांक reg);
u32 rcar_pci_पढ़ो_reg(काष्ठा rcar_pcie *pcie, अचिन्हित पूर्णांक reg);
व्योम rcar_rmw32(काष्ठा rcar_pcie *pcie, पूर्णांक where, u32 mask, u32 data);
पूर्णांक rcar_pcie_रुको_क्रम_phyrdy(काष्ठा rcar_pcie *pcie);
पूर्णांक rcar_pcie_रुको_क्रम_dl(काष्ठा rcar_pcie *pcie);
व्योम rcar_pcie_set_outbound(काष्ठा rcar_pcie *pcie, पूर्णांक win,
			    काष्ठा resource_entry *winकरोw);
व्योम rcar_pcie_set_inbound(काष्ठा rcar_pcie *pcie, u64 cpu_addr,
			   u64 pci_addr, u64 flags, पूर्णांक idx, bool host);

#पूर्ण_अगर
