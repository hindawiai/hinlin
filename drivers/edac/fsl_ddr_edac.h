<शैली गुरु>
/*
 * Freescale Memory Controller kernel module
 *
 * Support  Power-based SoCs including MPC85xx, MPC86xx, MPC83xx and
 * ARM-based Layerscape SoCs including LS2xxx and LS1021A. Originally
 * split out from mpc85xx_edac EDAC driver.
 *
 * Author: Dave Jiang <djiang@mvista.com>
 *
 * 2006-2007 (c) MontaVista Software, Inc. This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 */
#अगर_अघोषित _FSL_DDR_EDAC_H_
#घोषणा _FSL_DDR_EDAC_H_

#घोषणा fsl_mc_prपूर्णांकk(mci, level, fmt, arg...) \
	edac_mc_chipset_prपूर्णांकk(mci, level, "FSL_DDR", fmt, ##arg)

/*
 * DRAM error defines
 */

/* DDR_SDRAM_CFG */
#घोषणा FSL_MC_DDR_SDRAM_CFG	0x0110
#घोषणा FSL_MC_CS_BNDS_0		0x0000
#घोषणा FSL_MC_CS_BNDS_OFS		0x0008

#घोषणा FSL_MC_DATA_ERR_INJECT_HI	0x0e00
#घोषणा FSL_MC_DATA_ERR_INJECT_LO	0x0e04
#घोषणा FSL_MC_ECC_ERR_INJECT	0x0e08
#घोषणा FSL_MC_CAPTURE_DATA_HI	0x0e20
#घोषणा FSL_MC_CAPTURE_DATA_LO	0x0e24
#घोषणा FSL_MC_CAPTURE_ECC		0x0e28
#घोषणा FSL_MC_ERR_DETECT		0x0e40
#घोषणा FSL_MC_ERR_DISABLE		0x0e44
#घोषणा FSL_MC_ERR_INT_EN		0x0e48
#घोषणा FSL_MC_CAPTURE_ATRIBUTES	0x0e4c
#घोषणा FSL_MC_CAPTURE_ADDRESS	0x0e50
#घोषणा FSL_MC_CAPTURE_EXT_ADDRESS	0x0e54
#घोषणा FSL_MC_ERR_SBE		0x0e58

#घोषणा DSC_MEM_EN	0x80000000
#घोषणा DSC_ECC_EN	0x20000000
#घोषणा DSC_RD_EN	0x10000000
#घोषणा DSC_DBW_MASK	0x00180000
#घोषणा DSC_DBW_32	0x00080000
#घोषणा DSC_DBW_64	0x00000000

#घोषणा DSC_SDTYPE_MASK		0x07000000
#घोषणा DSC_X32_EN	0x00000020

/* Err_Int_En */
#घोषणा DDR_EIE_MSEE	0x1	/* memory select */
#घोषणा DDR_EIE_SBEE	0x4	/* single-bit ECC error */
#घोषणा DDR_EIE_MBEE	0x8	/* multi-bit ECC error */

/* Err_Detect */
#घोषणा DDR_EDE_MSE		0x1	/* memory select */
#घोषणा DDR_EDE_SBE		0x4	/* single-bit ECC error */
#घोषणा DDR_EDE_MBE		0x8	/* multi-bit ECC error */
#घोषणा DDR_EDE_MME		0x80000000	/* multiple memory errors */

/* Err_Disable */
#घोषणा DDR_EDI_MSED	0x1	/* memory select disable */
#घोषणा	DDR_EDI_SBED	0x4	/* single-bit ECC error disable */
#घोषणा	DDR_EDI_MBED	0x8	/* multi-bit ECC error disable */

काष्ठा fsl_mc_pdata अणु
	अक्षर *name;
	पूर्णांक edac_idx;
	व्योम __iomem *mc_vbase;
	पूर्णांक irq;
पूर्ण;
पूर्णांक fsl_mc_err_probe(काष्ठा platक्रमm_device *op);
पूर्णांक fsl_mc_err_हटाओ(काष्ठा platक्रमm_device *op);
#पूर्ण_अगर
