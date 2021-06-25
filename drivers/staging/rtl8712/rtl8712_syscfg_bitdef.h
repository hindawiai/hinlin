<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/******************************************************************************
 *
 * Copyright(c) 2007 - 2010 Realtek Corporation. All rights reserved.
 *
 * Modअगरications क्रम inclusion पूर्णांकo the Linux staging tree are
 * Copyright(c) 2010 Larry Finger. All rights reserved.
 *
 * Contact inक्रमmation:
 * WLAN FAE <wlanfae@realtek.com>
 * Larry Finger <Larry.Finger@lwfinger.net>
 *
 ******************************************************************************/
#अगर_अघोषित __RTL8712_SYSCFG_BITDEF_H__
#घोषणा __RTL8712_SYSCFG_BITDEF_H__

/*SYS_PWR_CTRL*/
/*SRCTRL0*/
/*SRCTRL1*/
/*SYS_CLKR*/

/*SYS_IOS_CTRL*/
#घोषणा iso_LDR2RP_SHT		8 /* EE Loader to Retention Path*/
#घोषणा iso_LDR2RP		BIT(iso_LDR2RP_SHT) /* 1:isolation, 0:attach*/

/*SYS_CTRL*/
#घोषणा FEN_DIO_SDIO_SHT	0
#घोषणा FEN_DIO_SDIO		BIT(FEN_DIO_SDIO_SHT)
#घोषणा FEN_SDIO_SHT		1
#घोषणा FEN_SDIO		BIT(FEN_SDIO_SHT)
#घोषणा FEN_USBA_SHT		2
#घोषणा FEN_USBA		BIT(FEN_USBA_SHT)
#घोषणा FEN_UPLL_SHT		3
#घोषणा FEN_UPLL		BIT(FEN_UPLL_SHT)
#घोषणा FEN_USBD_SHT		4
#घोषणा FEN_USBD		BIT(FEN_USBD_SHT)
#घोषणा FEN_DIO_PCIE_SHT	5
#घोषणा FEN_DIO_PCIE		BIT(FEN_DIO_PCIE_SHT)
#घोषणा FEN_PCIEA_SHT		6
#घोषणा FEN_PCIEA		BIT(FEN_PCIEA_SHT)
#घोषणा FEN_PPLL_SHT		7
#घोषणा FEN_PPLL		BIT(FEN_PPLL_SHT)
#घोषणा FEN_PCIED_SHT		8
#घोषणा FEN_PCIED		BIT(FEN_PCIED_SHT)
#घोषणा FEN_CPUEN_SHT		10
#घोषणा FEN_CPUEN		BIT(FEN_CPUEN_SHT)
#घोषणा FEN_DCORE_SHT		11
#घोषणा FEN_DCORE		BIT(FEN_DCORE_SHT)
#घोषणा FEN_ELDR_SHT		12
#घोषणा FEN_ELDR		BIT(FEN_ELDR_SHT)
#घोषणा PWC_DV2LDR_SHT		13
#घोषणा PWC_DV2LDR		BIT(PWC_DV2LDR_SHT) /* Loader Power Enable*/

/*=== SYS_CLKR ===*/
#घोषणा SYS_CLKSEL_SHT		0
#घोषणा SYS_CLKSEL		BIT(SYS_CLKSEL_SHT) /* System Clock 80MHz*/
#घोषणा PS_CLKSEL_SHT		1
#घोषणा PS_CLKSEL		BIT(PS_CLKSEL_SHT) /*System घातer save
						    * घड़ी select.
						    */
#घोषणा CPU_CLKSEL_SHT		2
#घोषणा CPU_CLKSEL		BIT(CPU_CLKSEL_SHT) /* System Clock select,
						     * 1: AFE source,
						     * 0: System घड़ी(L-Bus)
						     */
#घोषणा INT32K_EN_SHT		3
#घोषणा INT32K_EN		BIT(INT32K_EN_SHT)
#घोषणा MACSLP_SHT		4
#घोषणा MACSLP			BIT(MACSLP_SHT)
#घोषणा MAC_CLK_EN_SHT		11
#घोषणा MAC_CLK_EN		BIT(MAC_CLK_EN_SHT) /* MAC Clock Enable.*/
#घोषणा SYS_CLK_EN_SHT		12
#घोषणा SYS_CLK_EN		BIT(SYS_CLK_EN_SHT)
#घोषणा RING_CLK_EN_SHT		13
#घोषणा RING_CLK_EN		BIT(RING_CLK_EN_SHT)
#घोषणा SWHW_SEL_SHT		14
#घोषणा SWHW_SEL		BIT(SWHW_SEL_SHT) /* Load करोne,
						   * control path चयन.
						   */
#घोषणा FWHW_SEL_SHT		15
#घोषणा FWHW_SEL		BIT(FWHW_SEL_SHT) /* Sleep निकास,
						   * control path चयन.
						   */

/*9346CR*/
#घोषणा	_VPDIDX_MSK		0xFF00
#घोषणा	_VPDIDX_SHT		8
#घोषणा	_EEM_MSK		0x00C0
#घोषणा	_EEM_SHT		6
#घोषणा	_EEM0			BIT(6)
#घोषणा	_EEM1			BIT(7)
#घोषणा	_EEPROM_EN		BIT(5)
#घोषणा	_9356SEL		BIT(4)
#घोषणा	_EECS			BIT(3)
#घोषणा	_EESK			BIT(2)
#घोषणा	_EEDI			BIT(1)
#घोषणा	_EEDO			BIT(0)

/*AFE_MISC*/
#घोषणा	AFE_MISC_USB_MBEN_SHT	7
#घोषणा	AFE_MISC_USB_MBEN	BIT(AFE_MISC_USB_MBEN_SHT)
#घोषणा	AFE_MISC_USB_BGEN_SHT	6
#घोषणा	AFE_MISC_USB_BGEN	BIT(AFE_MISC_USB_BGEN_SHT)
#घोषणा	AFE_MISC_LD12_VDAJ_SHT	4
#घोषणा	AFE_MISC_LD12_VDAJ_MSK	0X0030
#घोषणा	AFE_MISC_LD12_VDAJ	BIT(AFE_MISC_LD12_VDAJ_SHT)
#घोषणा	AFE_MISC_I32_EN_SHT	3
#घोषणा	AFE_MISC_I32_EN		BIT(AFE_MISC_I32_EN_SHT)
#घोषणा	AFE_MISC_E32_EN_SHT	2
#घोषणा	AFE_MISC_E32_EN		BIT(AFE_MISC_E32_EN_SHT)
#घोषणा	AFE_MISC_MBEN_SHT	1
#घोषणा	AFE_MISC_MBEN		BIT(AFE_MISC_MBEN_SHT)/* Enable AFE Macro
						       * Block's Mbias.
						       */
#घोषणा	AFE_MISC_BGEN_SHT	0
#घोषणा	AFE_MISC_BGEN		BIT(AFE_MISC_BGEN_SHT)/* Enable AFE Macro
						       * Block's Bandgap.
						       */


/*--------------------------------------------------------------------------*/
/*       SPS1_CTRL bits				(Offset 0x18-1E, 56bits)*/
/*--------------------------------------------------------------------------*/
#घोषणा	SPS1_SWEN		BIT(1)	/* Enable vsps18 SW Macro Block.*/
#घोषणा	SPS1_LDEN		BIT(0)	/* Enable VSPS12 LDO Macro block.*/


/*----------------------------------------------------------------------------*/
/*       LDOA15_CTRL bits		(Offset 0x20, 8bits)*/
/*----------------------------------------------------------------------------*/
#घोषणा	LDA15_EN		BIT(0)	/* Enable LDOA15 Macro Block*/


/*----------------------------------------------------------------------------*/
/*       8192S LDOV12D_CTRL bit		(Offset 0x21, 8bits)*/
/*----------------------------------------------------------------------------*/
#घोषणा	LDV12_EN		BIT(0)	/* Enable LDOVD12 Macro Block*/
#घोषणा	LDV12_SDBY		BIT(1)	/* LDOVD12 standby mode*/

/*CLK_PS_CTRL*/
#घोषणा	_CLK_GATE_EN		BIT(0)


/* EFUSE_CTRL*/
#घोषणा EF_FLAG			BIT(31)		/* Access Flag, Write:1;
						 *	        Read:0
						 */
#घोषणा EF_PGPD			0x70000000	/* E-fuse Program समय*/
#घोषणा EF_RDT			0x0F000000	/* E-fuse पढ़ो समय: in the
						 * unit of cycle समय
						 */
#घोषणा EF_PDN_EN		BIT(19)		/* EFuse Power करोwn enable*/
#घोषणा ALD_EN			BIT(18)		/* Autoload Enable*/
#घोषणा EF_ADDR			0x0003FF00	/* Access Address*/
#घोषणा EF_DATA			0x000000FF	/* Access Data*/

/* EFUSE_TEST*/
#घोषणा LDOE25_EN		BIT(31)		/* Enable LDOE25 Macro Block*/

/* EFUSE_CLK_CTRL*/
#घोषणा EFUSE_CLK_EN		BIT(1)		/* E-Fuse Clock Enable*/
#घोषणा EFUSE_CLK_SEL		BIT(0)		/* E-Fuse Clock Select,
						 * 0:500K, 1:40M
						 */

#पूर्ण_अगर	/*__RTL8712_SYSCFG_BITDEF_H__*/

