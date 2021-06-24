<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_KEYLARGO_H
#घोषणा _ASM_POWERPC_KEYLARGO_H
#अगर_घोषित __KERNEL__
/*
 * keylargo.h: definitions क्रम using the "KeyLargo" I/O controller chip.
 *
 */

/* "Pangea" chipset has keylargo device-id 0x25 जबतक core99
 * has device-id 0x22. The rev. of the pangea one is 0, so we
 * fake an artअगरicial rev. in keylargo_rev by oring 0x100
 */
#घोषणा KL_PANGEA_REV		0x100

/* offset from base क्रम feature control रेजिस्टरs */
#घोषणा KEYLARGO_MBCR		0x34	/* KL Only, Media bay control/status */
#घोषणा KEYLARGO_FCR0		0x38
#घोषणा KEYLARGO_FCR1		0x3c
#घोषणा KEYLARGO_FCR2		0x40
#घोषणा KEYLARGO_FCR3		0x44
#घोषणा KEYLARGO_FCR4		0x48
#घोषणा KEYLARGO_FCR5		0x4c	/* Pangea only */

/* K2 additional FCRs */
#घोषणा K2_FCR6			0x34
#घोषणा K2_FCR7			0x30
#घोषणा K2_FCR8			0x2c
#घोषणा K2_FCR9			0x28
#घोषणा K2_FCR10		0x24

/* GPIO रेजिस्टरs */
#घोषणा KEYLARGO_GPIO_LEVELS0		0x50
#घोषणा KEYLARGO_GPIO_LEVELS1		0x54
#घोषणा KEYLARGO_GPIO_EXTINT_0		0x58
#घोषणा KEYLARGO_GPIO_EXTINT_CNT	18
#घोषणा KEYLARGO_GPIO_0			0x6A
#घोषणा KEYLARGO_GPIO_CNT		17
#घोषणा KEYLARGO_GPIO_EXTINT_DUAL_EDGE	0x80
#घोषणा KEYLARGO_GPIO_OUTPUT_ENABLE	0x04
#घोषणा KEYLARGO_GPIO_OUTOUT_DATA	0x01
#घोषणा KEYLARGO_GPIO_INPUT_DATA	0x02

/* K2 करोes only extपूर्णांक GPIOs and करोes 51 of them */
#घोषणा K2_GPIO_EXTINT_0		0x58
#घोषणा K2_GPIO_EXTINT_CNT		51

/* Specअगरic GPIO regs */

#घोषणा KL_GPIO_MODEM_RESET		(KEYLARGO_GPIO_0+0x03)
#घोषणा KL_GPIO_MODEM_POWER		(KEYLARGO_GPIO_0+0x02) /* Pangea */

#घोषणा KL_GPIO_SOUND_POWER		(KEYLARGO_GPIO_0+0x05)

/* Hrm... this one is only to be used on Pismo. It seems to also
 * control the समयbase enable on other machines. Still to be
 * experimented... --BenH.
 */
#घोषणा KL_GPIO_FW_CABLE_POWER		(KEYLARGO_GPIO_0+0x09)
#घोषणा KL_GPIO_TB_ENABLE		(KEYLARGO_GPIO_0+0x09)

#घोषणा KL_GPIO_ETH_PHY_RESET		(KEYLARGO_GPIO_0+0x10)

#घोषणा KL_GPIO_EXTINT_CPU1		(KEYLARGO_GPIO_0+0x0a)
#घोषणा KL_GPIO_EXTINT_CPU1_ASSERT	0x04
#घोषणा KL_GPIO_EXTINT_CPU1_RELEASE	0x38

#घोषणा KL_GPIO_RESET_CPU0		(KEYLARGO_GPIO_EXTINT_0+0x03)
#घोषणा KL_GPIO_RESET_CPU1		(KEYLARGO_GPIO_EXTINT_0+0x04)
#घोषणा KL_GPIO_RESET_CPU2		(KEYLARGO_GPIO_EXTINT_0+0x0f)
#घोषणा KL_GPIO_RESET_CPU3		(KEYLARGO_GPIO_EXTINT_0+0x10)

#घोषणा KL_GPIO_PMU_MESSAGE_IRQ		(KEYLARGO_GPIO_EXTINT_0+0x09)
#घोषणा KL_GPIO_PMU_MESSAGE_BIT		KEYLARGO_GPIO_INPUT_DATA

#घोषणा KL_GPIO_MEDIABAY_IRQ		(KEYLARGO_GPIO_EXTINT_0+0x0e)

#घोषणा KL_GPIO_AIRPORT_0		(KEYLARGO_GPIO_EXTINT_0+0x0a)
#घोषणा KL_GPIO_AIRPORT_1		(KEYLARGO_GPIO_EXTINT_0+0x0d)
#घोषणा KL_GPIO_AIRPORT_2		(KEYLARGO_GPIO_0+0x0d)
#घोषणा KL_GPIO_AIRPORT_3		(KEYLARGO_GPIO_0+0x0e)
#घोषणा KL_GPIO_AIRPORT_4		(KEYLARGO_GPIO_0+0x0f)

/*
 * Bits in feature control रेजिस्टर. Those bits dअगरferent क्रम K2 are
 * listed separately
 */
#घोषणा KL_MBCR_MB0_PCI_ENABLE		0x00000800	/* exist ? */
#घोषणा KL_MBCR_MB0_IDE_ENABLE		0x00001000
#घोषणा KL_MBCR_MB0_FLOPPY_ENABLE	0x00002000	/* exist ? */
#घोषणा KL_MBCR_MB0_SOUND_ENABLE	0x00004000	/* hrm... */
#घोषणा KL_MBCR_MB0_DEV_MASK		0x00007800
#घोषणा KL_MBCR_MB0_DEV_POWER		0x00000400
#घोषणा KL_MBCR_MB0_DEV_RESET		0x00000200
#घोषणा KL_MBCR_MB0_ENABLE		0x00000100
#घोषणा KL_MBCR_MB1_PCI_ENABLE		0x08000000	/* exist ? */
#घोषणा KL_MBCR_MB1_IDE_ENABLE		0x10000000
#घोषणा KL_MBCR_MB1_FLOPPY_ENABLE	0x20000000	/* exist ? */
#घोषणा KL_MBCR_MB1_SOUND_ENABLE	0x40000000	/* hrm... */
#घोषणा KL_MBCR_MB1_DEV_MASK		0x78000000
#घोषणा KL_MBCR_MB1_DEV_POWER		0x04000000
#घोषणा KL_MBCR_MB1_DEV_RESET		0x02000000
#घोषणा KL_MBCR_MB1_ENABLE		0x01000000

#घोषणा KL0_SCC_B_INTF_ENABLE		0x00000001	/* (KL Only) */
#घोषणा KL0_SCC_A_INTF_ENABLE		0x00000002
#घोषणा KL0_SCC_SLOWPCLK		0x00000004
#घोषणा KL0_SCC_RESET			0x00000008
#घोषणा KL0_SCCA_ENABLE			0x00000010
#घोषणा KL0_SCCB_ENABLE			0x00000020
#घोषणा KL0_SCC_CELL_ENABLE		0x00000040
#घोषणा KL0_IRDA_HIGH_BAND		0x00000100	/* (KL Only) */
#घोषणा KL0_IRDA_SOURCE2_SEL		0x00000200	/* (KL Only) */
#घोषणा KL0_IRDA_SOURCE1_SEL		0x00000400	/* (KL Only) */
#घोषणा KL0_PG_USB0_PMI_ENABLE		0x00000400	/* (Pangea/Intrepid Only) */
#घोषणा KL0_IRDA_RESET			0x00000800	/* (KL Only) */
#घोषणा KL0_PG_USB0_REF_SUSPEND_SEL	0x00000800	/* (Pangea/Intrepid Only) */
#घोषणा KL0_IRDA_DEFAULT1		0x00001000	/* (KL Only) */
#घोषणा KL0_PG_USB0_REF_SUSPEND		0x00001000	/* (Pangea/Intrepid Only) */
#घोषणा KL0_IRDA_DEFAULT0		0x00002000	/* (KL Only) */
#घोषणा KL0_PG_USB0_PAD_SUSPEND		0x00002000	/* (Pangea/Intrepid Only) */
#घोषणा KL0_IRDA_FAST_CONNECT		0x00004000	/* (KL Only) */
#घोषणा KL0_PG_USB1_PMI_ENABLE		0x00004000	/* (Pangea/Intrepid Only) */
#घोषणा KL0_IRDA_ENABLE			0x00008000	/* (KL Only) */
#घोषणा KL0_PG_USB1_REF_SUSPEND_SEL	0x00008000	/* (Pangea/Intrepid Only) */
#घोषणा KL0_IRDA_CLK32_ENABLE		0x00010000	/* (KL Only) */
#घोषणा KL0_PG_USB1_REF_SUSPEND		0x00010000	/* (Pangea/Intrepid Only) */
#घोषणा KL0_IRDA_CLK19_ENABLE		0x00020000	/* (KL Only) */
#घोषणा KL0_PG_USB1_PAD_SUSPEND		0x00020000	/* (Pangea/Intrepid Only) */
#घोषणा KL0_USB0_PAD_SUSPEND0		0x00040000
#घोषणा KL0_USB0_PAD_SUSPEND1		0x00080000
#घोषणा KL0_USB0_CELL_ENABLE		0x00100000
#घोषणा KL0_USB1_PAD_SUSPEND0		0x00400000
#घोषणा KL0_USB1_PAD_SUSPEND1		0x00800000
#घोषणा KL0_USB1_CELL_ENABLE		0x01000000
#घोषणा KL0_USB_REF_SUSPEND		0x10000000	/* (KL Only) */

#घोषणा KL0_SERIAL_ENABLE		(KL0_SCC_B_INTF_ENABLE | \
					KL0_SCC_SLOWPCLK | \
					KL0_SCC_CELL_ENABLE | KL0_SCCA_ENABLE)

#घोषणा KL1_USB2_PMI_ENABLE		0x00000001	/* Intrepid only */
#घोषणा KL1_AUDIO_SEL_22MCLK		0x00000002	/* KL/Pangea only */
#घोषणा KL1_USB2_REF_SUSPEND_SEL	0x00000002	/* Intrepid only */
#घोषणा KL1_USB2_REF_SUSPEND		0x00000004	/* Intrepid only */
#घोषणा KL1_AUDIO_CLK_ENABLE_BIT	0x00000008	/* KL/Pangea only */
#घोषणा KL1_USB2_PAD_SUSPEND_SEL	0x00000008	/* Intrepid only */
#घोषणा KL1_USB2_PAD_SUSPEND0		0x00000010	/* Intrepid only */
#घोषणा KL1_AUDIO_CLK_OUT_ENABLE	0x00000020	/* KL/Pangea only */
#घोषणा KL1_USB2_PAD_SUSPEND1		0x00000020	/* Intrepid only */
#घोषणा KL1_AUDIO_CELL_ENABLE		0x00000040	/* KL/Pangea only */
#घोषणा KL1_USB2_CELL_ENABLE		0x00000040	/* Intrepid only */
#घोषणा KL1_AUDIO_CHOOSE		0x00000080	/* KL/Pangea only */
#घोषणा KL1_I2S0_CHOOSE			0x00000200	/* KL Only */
#घोषणा KL1_I2S0_CELL_ENABLE		0x00000400
#घोषणा KL1_I2S0_CLK_ENABLE_BIT		0x00001000
#घोषणा KL1_I2S0_ENABLE			0x00002000
#घोषणा KL1_I2S1_CELL_ENABLE		0x00020000
#घोषणा KL1_I2S1_CLK_ENABLE_BIT		0x00080000
#घोषणा KL1_I2S1_ENABLE			0x00100000
#घोषणा KL1_EIDE0_ENABLE		0x00800000	/* KL/Intrepid Only */
#घोषणा KL1_EIDE0_RESET_N		0x01000000	/* KL/Intrepid Only */
#घोषणा KL1_EIDE1_ENABLE		0x04000000	/* KL Only */
#घोषणा KL1_EIDE1_RESET_N		0x08000000	/* KL Only */
#घोषणा KL1_UIDE_ENABLE			0x20000000	/* KL/Pangea Only */
#घोषणा KL1_UIDE_RESET_N		0x40000000	/* KL/Pangea Only */

#घोषणा KL2_IOBUS_ENABLE		0x00000002
#घोषणा KL2_SLEEP_STATE_BIT		0x00000100	/* KL Only */
#घोषणा KL2_PG_STOP_ALL_CLOCKS		0x00000100	/* Pangea Only */
#घोषणा KL2_MPIC_ENABLE			0x00020000
#घोषणा KL2_CARDSLOT_RESET		0x00040000	/* Pangea/Intrepid Only */
#घोषणा KL2_ALT_DATA_OUT		0x02000000	/* KL Only ??? */
#घोषणा KL2_MEM_IS_BIG			0x04000000
#घोषणा KL2_CARDSEL_16			0x08000000

#घोषणा KL3_SHUTDOWN_PLL_TOTAL		0x00000001	/* KL/Pangea only */
#घोषणा KL3_SHUTDOWN_PLLKW6		0x00000002	/* KL/Pangea only */
#घोषणा KL3_IT_SHUTDOWN_PLL3		0x00000002	/* Intrepid only */
#घोषणा KL3_SHUTDOWN_PLLKW4		0x00000004	/* KL/Pangea only */
#घोषणा KL3_IT_SHUTDOWN_PLL2		0x00000004	/* Intrepid only */
#घोषणा KL3_SHUTDOWN_PLLKW35		0x00000008	/* KL/Pangea only */
#घोषणा KL3_IT_SHUTDOWN_PLL1		0x00000008	/* Intrepid only */
#घोषणा KL3_SHUTDOWN_PLLKW12		0x00000010	/* KL Only */
#घोषणा KL3_IT_ENABLE_PLL3_SHUTDOWN	0x00000010	/* Intrepid only */
#घोषणा KL3_PLL_RESET			0x00000020	/* KL/Pangea only */
#घोषणा KL3_IT_ENABLE_PLL2_SHUTDOWN	0x00000020	/* Intrepid only */
#घोषणा KL3_IT_ENABLE_PLL1_SHUTDOWN	0x00000010	/* Intrepid only */
#घोषणा KL3_SHUTDOWN_PLL2X		0x00000080	/* KL Only */
#घोषणा KL3_CLK66_ENABLE		0x00000100	/* KL Only */
#घोषणा KL3_CLK49_ENABLE		0x00000200
#घोषणा KL3_CLK45_ENABLE		0x00000400
#घोषणा KL3_CLK31_ENABLE		0x00000800	/* KL/Pangea only */
#घोषणा KL3_TIMER_CLK18_ENABLE		0x00001000
#घोषणा KL3_I2S1_CLK18_ENABLE		0x00002000
#घोषणा KL3_I2S0_CLK18_ENABLE		0x00004000
#घोषणा KL3_VIA_CLK16_ENABLE		0x00008000	/* KL/Pangea only */
#घोषणा KL3_IT_VIA_CLK32_ENABLE		0x00008000	/* Intrepid only */
#घोषणा KL3_STOPPING33_ENABLED		0x00080000	/* KL Only */
#घोषणा KL3_PG_PLL_ENABLE_TEST		0x00080000	/* Pangea Only */

/* Intrepid USB bus 2, port 0,1 */
#घोषणा KL3_IT_PORT_WAKEUP_ENABLE(p)		(0x00080000 << ((p)<<3))
#घोषणा KL3_IT_PORT_RESUME_WAKE_EN(p)		(0x00040000 << ((p)<<3))
#घोषणा KL3_IT_PORT_CONNECT_WAKE_EN(p)		(0x00020000 << ((p)<<3))
#घोषणा KL3_IT_PORT_DISCONNECT_WAKE_EN(p)	(0x00010000 << ((p)<<3))
#घोषणा KL3_IT_PORT_RESUME_STAT(p)		(0x00300000 << ((p)<<3))
#घोषणा KL3_IT_PORT_CONNECT_STAT(p)		(0x00200000 << ((p)<<3))
#घोषणा KL3_IT_PORT_DISCONNECT_STAT(p)		(0x00100000 << ((p)<<3))

/* Port 0,1 : bus 0, port 2,3 : bus 1 */
#घोषणा KL4_PORT_WAKEUP_ENABLE(p)	(0x00000008 << ((p)<<3))
#घोषणा KL4_PORT_RESUME_WAKE_EN(p)	(0x00000004 << ((p)<<3))
#घोषणा KL4_PORT_CONNECT_WAKE_EN(p)	(0x00000002 << ((p)<<3))
#घोषणा KL4_PORT_DISCONNECT_WAKE_EN(p)	(0x00000001 << ((p)<<3))
#घोषणा KL4_PORT_RESUME_STAT(p)		(0x00000040 << ((p)<<3))
#घोषणा KL4_PORT_CONNECT_STAT(p)	(0x00000020 << ((p)<<3))
#घोषणा KL4_PORT_DISCONNECT_STAT(p)	(0x00000010 << ((p)<<3))

/* Pangea and Intrepid only */
#घोषणा KL5_VIA_USE_CLK31		0000000001	/* Pangea Only */
#घोषणा KL5_SCC_USE_CLK31		0x00000002	/* Pangea Only */
#घोषणा KL5_PWM_CLK32_EN		0x00000004
#घोषणा KL5_CLK3_68_EN			0x00000010
#घोषणा KL5_CLK32_EN			0x00000020


/* K2 definitions */
#घोषणा K2_FCR0_USB0_SWRESET		0x00200000
#घोषणा K2_FCR0_USB1_SWRESET		0x02000000
#घोषणा K2_FCR0_RING_PME_DISABLE	0x08000000

#घोषणा K2_FCR1_PCI1_BUS_RESET_N	0x00000010
#घोषणा K2_FCR1_PCI1_SLEEP_RESET_EN	0x00000020
#घोषणा K2_FCR1_I2S0_CELL_ENABLE	0x00000400
#घोषणा K2_FCR1_I2S0_RESET		0x00000800
#घोषणा K2_FCR1_I2S0_CLK_ENABLE_BIT	0x00001000
#घोषणा K2_FCR1_I2S0_ENABLE    		0x00002000
#घोषणा K2_FCR1_PCI1_CLK_ENABLE		0x00004000
#घोषणा K2_FCR1_FW_CLK_ENABLE		0x00008000
#घोषणा K2_FCR1_FW_RESET_N		0x00010000
#घोषणा K2_FCR1_I2S1_CELL_ENABLE	0x00020000
#घोषणा K2_FCR1_I2S1_CLK_ENABLE_BIT	0x00080000
#घोषणा K2_FCR1_I2S1_ENABLE		0x00100000
#घोषणा K2_FCR1_GMAC_CLK_ENABLE		0x00400000
#घोषणा K2_FCR1_GMAC_POWER_DOWN		0x00800000
#घोषणा K2_FCR1_GMAC_RESET_N		0x01000000
#घोषणा K2_FCR1_SATA_CLK_ENABLE		0x02000000
#घोषणा K2_FCR1_SATA_POWER_DOWN		0x04000000
#घोषणा K2_FCR1_SATA_RESET_N		0x08000000
#घोषणा K2_FCR1_UATA_CLK_ENABLE		0x10000000
#घोषणा K2_FCR1_UATA_RESET_N		0x40000000
#घोषणा K2_FCR1_UATA_CHOOSE_CLK66	0x80000000

/* Shasta definitions */
#घोषणा SH_FCR1_I2S2_CELL_ENABLE	0x00000010
#घोषणा SH_FCR1_I2S2_CLK_ENABLE_BIT	0x00000040
#घोषणा SH_FCR1_I2S2_ENABLE		0x00000080
#घोषणा SH_FCR3_I2S2_CLK18_ENABLE	0x00008000

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_KEYLARGO_H */
