<शैली गुरु>
/*
 * Freescale MPC85xx Memory Controller kernel module
 * Author: Dave Jiang <djiang@mvista.com>
 *
 * 2006-2007 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 */
#अगर_अघोषित _MPC85XX_EDAC_H_
#घोषणा _MPC85XX_EDAC_H_

#घोषणा MPC85XX_REVISION " Ver: 2.0.0"
#घोषणा EDAC_MOD_STR	"MPC85xx_edac"

#घोषणा mpc85xx_prपूर्णांकk(level, fmt, arg...) \
	edac_prपूर्णांकk(level, "MPC85xx", fmt, ##arg)

/*
 * L2 Err defines
 */
#घोषणा MPC85XX_L2_ERRINJHI	0x0000
#घोषणा MPC85XX_L2_ERRINJLO	0x0004
#घोषणा MPC85XX_L2_ERRINJCTL	0x0008
#घोषणा MPC85XX_L2_CAPTDATAHI	0x0020
#घोषणा MPC85XX_L2_CAPTDATALO	0x0024
#घोषणा MPC85XX_L2_CAPTECC	0x0028
#घोषणा MPC85XX_L2_ERRDET	0x0040
#घोषणा MPC85XX_L2_ERRDIS	0x0044
#घोषणा MPC85XX_L2_ERRINTEN	0x0048
#घोषणा MPC85XX_L2_ERRATTR	0x004c
#घोषणा MPC85XX_L2_ERRADDR	0x0050
#घोषणा MPC85XX_L2_ERRCTL	0x0058

/* Error Interrupt Enable */
#घोषणा L2_EIE_L2CFGINTEN	0x1
#घोषणा L2_EIE_SBECCINTEN	0x4
#घोषणा L2_EIE_MBECCINTEN	0x8
#घोषणा L2_EIE_TPARINTEN	0x10
#घोषणा L2_EIE_MASK	(L2_EIE_L2CFGINTEN | L2_EIE_SBECCINTEN | \
			L2_EIE_MBECCINTEN | L2_EIE_TPARINTEN)

/* Error Detect */
#घोषणा L2_EDE_L2CFGERR		0x1
#घोषणा L2_EDE_SBECCERR		0x4
#घोषणा L2_EDE_MBECCERR		0x8
#घोषणा L2_EDE_TPARERR		0x10
#घोषणा L2_EDE_MULL2ERR		0x80000000

#घोषणा L2_EDE_CE_MASK	L2_EDE_SBECCERR
#घोषणा L2_EDE_UE_MASK	(L2_EDE_L2CFGERR | L2_EDE_MBECCERR | \
			L2_EDE_TPARERR)
#घोषणा L2_EDE_MASK	(L2_EDE_L2CFGERR | L2_EDE_SBECCERR | \
			L2_EDE_MBECCERR | L2_EDE_TPARERR | L2_EDE_MULL2ERR)

/*
 * PCI Err defines
 */
#घोषणा PCI_EDE_TOE			0x00000001
#घोषणा PCI_EDE_SCM			0x00000002
#घोषणा PCI_EDE_IRMSV			0x00000004
#घोषणा PCI_EDE_ORMSV			0x00000008
#घोषणा PCI_EDE_OWMSV			0x00000010
#घोषणा PCI_EDE_TGT_ABRT		0x00000020
#घोषणा PCI_EDE_MST_ABRT		0x00000040
#घोषणा PCI_EDE_TGT_PERR		0x00000080
#घोषणा PCI_EDE_MST_PERR		0x00000100
#घोषणा PCI_EDE_RCVD_SERR		0x00000200
#घोषणा PCI_EDE_ADDR_PERR		0x00000400
#घोषणा PCI_EDE_MULTI_ERR		0x80000000

#घोषणा PCI_EDE_PERR_MASK	(PCI_EDE_TGT_PERR | PCI_EDE_MST_PERR | \
				PCI_EDE_ADDR_PERR)

#घोषणा MPC85XX_PCI_ERR_DR		0x0000
#घोषणा MPC85XX_PCI_ERR_CAP_DR		0x0004
#घोषणा MPC85XX_PCI_ERR_EN		0x0008
#घोषणा   PEX_ERR_ICCAIE_EN_BIT		0x00020000
#घोषणा MPC85XX_PCI_ERR_ATTRIB		0x000c
#घोषणा MPC85XX_PCI_ERR_ADDR		0x0010
#घोषणा   PEX_ERR_ICCAD_DISR_BIT	0x00020000
#घोषणा MPC85XX_PCI_ERR_EXT_ADDR	0x0014
#घोषणा MPC85XX_PCI_ERR_DL		0x0018
#घोषणा MPC85XX_PCI_ERR_DH		0x001c
#घोषणा MPC85XX_PCI_GAS_TIMR		0x0020
#घोषणा MPC85XX_PCI_PCIX_TIMR		0x0024
#घोषणा MPC85XX_PCIE_ERR_CAP_R0		0x0028
#घोषणा MPC85XX_PCIE_ERR_CAP_R1		0x002c
#घोषणा MPC85XX_PCIE_ERR_CAP_R2		0x0030
#घोषणा MPC85XX_PCIE_ERR_CAP_R3		0x0034

काष्ठा mpc85xx_l2_pdata अणु
	अक्षर *name;
	पूर्णांक edac_idx;
	व्योम __iomem *l2_vbase;
	पूर्णांक irq;
पूर्ण;

काष्ठा mpc85xx_pci_pdata अणु
	अक्षर *name;
	bool is_pcie;
	पूर्णांक edac_idx;
	व्योम __iomem *pci_vbase;
	पूर्णांक irq;
पूर्ण;

#पूर्ण_अगर
