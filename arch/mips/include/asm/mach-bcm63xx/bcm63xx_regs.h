<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BCM63XX_REGS_H_
#घोषणा BCM63XX_REGS_H_

/*************************************************************************
 * _REG relative to RSET_PERF
 *************************************************************************/

/* Chip Identअगरier / Revision रेजिस्टर */
#घोषणा PERF_REV_REG			0x0
#घोषणा REV_CHIPID_SHIFT		16
#घोषणा REV_CHIPID_MASK			(0xffff << REV_CHIPID_SHIFT)
#घोषणा REV_REVID_SHIFT			0
#घोषणा REV_REVID_MASK			(0xff << REV_REVID_SHIFT)

/* Clock Control रेजिस्टर */
#घोषणा PERF_CKCTL_REG			0x4

#घोषणा CKCTL_3368_MAC_EN		(1 << 3)
#घोषणा CKCTL_3368_TC_EN		(1 << 5)
#घोषणा CKCTL_3368_US_TOP_EN		(1 << 6)
#घोषणा CKCTL_3368_DS_TOP_EN		(1 << 7)
#घोषणा CKCTL_3368_APM_EN		(1 << 8)
#घोषणा CKCTL_3368_SPI_EN		(1 << 9)
#घोषणा CKCTL_3368_USBS_EN		(1 << 10)
#घोषणा CKCTL_3368_BMU_EN		(1 << 11)
#घोषणा CKCTL_3368_PCM_EN		(1 << 12)
#घोषणा CKCTL_3368_NTP_EN		(1 << 13)
#घोषणा CKCTL_3368_ACP_B_EN		(1 << 14)
#घोषणा CKCTL_3368_ACP_A_EN		(1 << 15)
#घोषणा CKCTL_3368_EMUSB_EN		(1 << 17)
#घोषणा CKCTL_3368_ENET0_EN		(1 << 18)
#घोषणा CKCTL_3368_ENET1_EN		(1 << 19)
#घोषणा CKCTL_3368_USBU_EN		(1 << 20)
#घोषणा CKCTL_3368_EPHY_EN		(1 << 21)

#घोषणा CKCTL_3368_ALL_SAFE_EN		(CKCTL_3368_MAC_EN | \
					 CKCTL_3368_TC_EN | \
					 CKCTL_3368_US_TOP_EN | \
					 CKCTL_3368_DS_TOP_EN | \
					 CKCTL_3368_APM_EN | \
					 CKCTL_3368_SPI_EN | \
					 CKCTL_3368_USBS_EN | \
					 CKCTL_3368_BMU_EN | \
					 CKCTL_3368_PCM_EN | \
					 CKCTL_3368_NTP_EN | \
					 CKCTL_3368_ACP_B_EN | \
					 CKCTL_3368_ACP_A_EN | \
					 CKCTL_3368_EMUSB_EN | \
					 CKCTL_3368_USBU_EN)

#घोषणा CKCTL_6328_PHYMIPS_EN		(1 << 0)
#घोषणा CKCTL_6328_ADSL_QPROC_EN	(1 << 1)
#घोषणा CKCTL_6328_ADSL_AFE_EN		(1 << 2)
#घोषणा CKCTL_6328_ADSL_EN		(1 << 3)
#घोषणा CKCTL_6328_MIPS_EN		(1 << 4)
#घोषणा CKCTL_6328_SAR_EN		(1 << 5)
#घोषणा CKCTL_6328_PCM_EN		(1 << 6)
#घोषणा CKCTL_6328_USBD_EN		(1 << 7)
#घोषणा CKCTL_6328_USBH_EN		(1 << 8)
#घोषणा CKCTL_6328_HSSPI_EN		(1 << 9)
#घोषणा CKCTL_6328_PCIE_EN		(1 << 10)
#घोषणा CKCTL_6328_ROBOSW_EN		(1 << 11)

#घोषणा CKCTL_6328_ALL_SAFE_EN		(CKCTL_6328_PHYMIPS_EN |	\
					CKCTL_6328_ADSL_QPROC_EN |	\
					CKCTL_6328_ADSL_AFE_EN |	\
					CKCTL_6328_ADSL_EN |		\
					CKCTL_6328_SAR_EN  |		\
					CKCTL_6328_PCM_EN  |		\
					CKCTL_6328_USBD_EN |		\
					CKCTL_6328_USBH_EN |		\
					CKCTL_6328_ROBOSW_EN |		\
					CKCTL_6328_PCIE_EN)

#घोषणा CKCTL_6338_ADSLPHY_EN		(1 << 0)
#घोषणा CKCTL_6338_MPI_EN		(1 << 1)
#घोषणा CKCTL_6338_DRAM_EN		(1 << 2)
#घोषणा CKCTL_6338_ENET_EN		(1 << 4)
#घोषणा CKCTL_6338_USBS_EN		(1 << 4)
#घोषणा CKCTL_6338_SAR_EN		(1 << 5)
#घोषणा CKCTL_6338_SPI_EN		(1 << 9)

#घोषणा CKCTL_6338_ALL_SAFE_EN		(CKCTL_6338_ADSLPHY_EN |	\
					CKCTL_6338_MPI_EN |		\
					CKCTL_6338_ENET_EN |		\
					CKCTL_6338_SAR_EN |		\
					CKCTL_6338_SPI_EN)

/* BCM6345 घड़ी bits are shअगरted by 16 on the left, because of the test
 * control रेजिस्टर which is 16-bits wide. That way we करो not have any
 * specअगरic BCM6345 code क्रम handling घड़ीs, and writing 0 to the test
 * control रेजिस्टर is fine.
 */
#घोषणा CKCTL_6345_CPU_EN		(1 << 16)
#घोषणा CKCTL_6345_BUS_EN		(1 << 17)
#घोषणा CKCTL_6345_EBI_EN		(1 << 18)
#घोषणा CKCTL_6345_UART_EN		(1 << 19)
#घोषणा CKCTL_6345_ADSLPHY_EN		(1 << 20)
#घोषणा CKCTL_6345_ENET_EN		(1 << 23)
#घोषणा CKCTL_6345_USBH_EN		(1 << 24)

#घोषणा CKCTL_6345_ALL_SAFE_EN		(CKCTL_6345_ENET_EN |	\
					CKCTL_6345_USBH_EN |	\
					CKCTL_6345_ADSLPHY_EN)

#घोषणा CKCTL_6348_ADSLPHY_EN		(1 << 0)
#घोषणा CKCTL_6348_MPI_EN		(1 << 1)
#घोषणा CKCTL_6348_SDRAM_EN		(1 << 2)
#घोषणा CKCTL_6348_M2M_EN		(1 << 3)
#घोषणा CKCTL_6348_ENET_EN		(1 << 4)
#घोषणा CKCTL_6348_SAR_EN		(1 << 5)
#घोषणा CKCTL_6348_USBS_EN		(1 << 6)
#घोषणा CKCTL_6348_USBH_EN		(1 << 8)
#घोषणा CKCTL_6348_SPI_EN		(1 << 9)

#घोषणा CKCTL_6348_ALL_SAFE_EN		(CKCTL_6348_ADSLPHY_EN |	\
					CKCTL_6348_M2M_EN |		\
					CKCTL_6348_ENET_EN |		\
					CKCTL_6348_SAR_EN |		\
					CKCTL_6348_USBS_EN |		\
					CKCTL_6348_USBH_EN |		\
					CKCTL_6348_SPI_EN)

#घोषणा CKCTL_6358_ENET_EN		(1 << 4)
#घोषणा CKCTL_6358_ADSLPHY_EN		(1 << 5)
#घोषणा CKCTL_6358_PCM_EN		(1 << 8)
#घोषणा CKCTL_6358_SPI_EN		(1 << 9)
#घोषणा CKCTL_6358_USBS_EN		(1 << 10)
#घोषणा CKCTL_6358_SAR_EN		(1 << 11)
#घोषणा CKCTL_6358_EMUSB_EN		(1 << 17)
#घोषणा CKCTL_6358_ENET0_EN		(1 << 18)
#घोषणा CKCTL_6358_ENET1_EN		(1 << 19)
#घोषणा CKCTL_6358_USBSU_EN		(1 << 20)
#घोषणा CKCTL_6358_EPHY_EN		(1 << 21)

#घोषणा CKCTL_6358_ALL_SAFE_EN		(CKCTL_6358_ENET_EN |		\
					CKCTL_6358_ADSLPHY_EN |		\
					CKCTL_6358_PCM_EN |		\
					CKCTL_6358_SPI_EN |		\
					CKCTL_6358_USBS_EN |		\
					CKCTL_6358_SAR_EN |		\
					CKCTL_6358_EMUSB_EN |		\
					CKCTL_6358_ENET0_EN |		\
					CKCTL_6358_ENET1_EN |		\
					CKCTL_6358_USBSU_EN |		\
					CKCTL_6358_EPHY_EN)

#घोषणा CKCTL_6362_ADSL_QPROC_EN	(1 << 1)
#घोषणा CKCTL_6362_ADSL_AFE_EN		(1 << 2)
#घोषणा CKCTL_6362_ADSL_EN		(1 << 3)
#घोषणा CKCTL_6362_MIPS_EN		(1 << 4)
#घोषणा CKCTL_6362_WLAN_OCP_EN		(1 << 5)
#घोषणा CKCTL_6362_SWPKT_USB_EN		(1 << 7)
#घोषणा CKCTL_6362_SWPKT_SAR_EN		(1 << 8)
#घोषणा CKCTL_6362_SAR_EN		(1 << 9)
#घोषणा CKCTL_6362_ROBOSW_EN		(1 << 10)
#घोषणा CKCTL_6362_PCM_EN		(1 << 11)
#घोषणा CKCTL_6362_USBD_EN		(1 << 12)
#घोषणा CKCTL_6362_USBH_EN		(1 << 13)
#घोषणा CKCTL_6362_IPSEC_EN		(1 << 14)
#घोषणा CKCTL_6362_SPI_EN		(1 << 15)
#घोषणा CKCTL_6362_HSSPI_EN		(1 << 16)
#घोषणा CKCTL_6362_PCIE_EN		(1 << 17)
#घोषणा CKCTL_6362_FAP_EN		(1 << 18)
#घोषणा CKCTL_6362_PHYMIPS_EN		(1 << 19)
#घोषणा CKCTL_6362_न_अंकD_EN		(1 << 20)

#घोषणा CKCTL_6362_ALL_SAFE_EN		(CKCTL_6362_PHYMIPS_EN |	\
					CKCTL_6362_ADSL_QPROC_EN |	\
					CKCTL_6362_ADSL_AFE_EN |	\
					CKCTL_6362_ADSL_EN |		\
					CKCTL_6362_SAR_EN  |		\
					CKCTL_6362_PCM_EN  |		\
					CKCTL_6362_IPSEC_EN |		\
					CKCTL_6362_USBD_EN |		\
					CKCTL_6362_USBH_EN |		\
					CKCTL_6362_ROBOSW_EN |		\
					CKCTL_6362_PCIE_EN)


#घोषणा CKCTL_6368_VDSL_QPROC_EN	(1 << 2)
#घोषणा CKCTL_6368_VDSL_AFE_EN		(1 << 3)
#घोषणा CKCTL_6368_VDSL_BONDING_EN	(1 << 4)
#घोषणा CKCTL_6368_VDSL_EN		(1 << 5)
#घोषणा CKCTL_6368_PHYMIPS_EN		(1 << 6)
#घोषणा CKCTL_6368_SWPKT_USB_EN		(1 << 7)
#घोषणा CKCTL_6368_SWPKT_SAR_EN		(1 << 8)
#घोषणा CKCTL_6368_SPI_EN		(1 << 9)
#घोषणा CKCTL_6368_USBD_EN		(1 << 10)
#घोषणा CKCTL_6368_SAR_EN		(1 << 11)
#घोषणा CKCTL_6368_ROBOSW_EN		(1 << 12)
#घोषणा CKCTL_6368_UTOPIA_EN		(1 << 13)
#घोषणा CKCTL_6368_PCM_EN		(1 << 14)
#घोषणा CKCTL_6368_USBH_EN		(1 << 15)
#घोषणा CKCTL_6368_DISABLE_GLESS_EN	(1 << 16)
#घोषणा CKCTL_6368_न_अंकD_EN		(1 << 17)
#घोषणा CKCTL_6368_IPSEC_EN		(1 << 18)

#घोषणा CKCTL_6368_ALL_SAFE_EN		(CKCTL_6368_SWPKT_USB_EN |	\
					CKCTL_6368_SWPKT_SAR_EN |	\
					CKCTL_6368_SPI_EN |		\
					CKCTL_6368_USBD_EN |		\
					CKCTL_6368_SAR_EN |		\
					CKCTL_6368_ROBOSW_EN |		\
					CKCTL_6368_UTOPIA_EN |		\
					CKCTL_6368_PCM_EN |		\
					CKCTL_6368_USBH_EN |		\
					CKCTL_6368_DISABLE_GLESS_EN |	\
					CKCTL_6368_न_अंकD_EN |		\
					CKCTL_6368_IPSEC_EN)

/* System PLL Control रेजिस्टर	*/
#घोषणा PERF_SYS_PLL_CTL_REG		0x8
#घोषणा SYS_PLL_SOFT_RESET		0x1

/* Interrupt Mask रेजिस्टर */
#घोषणा PERF_IRQMASK_3368_REG		0xc
#घोषणा PERF_IRQMASK_6328_REG(x)	(0x20 + (x) * 0x10)
#घोषणा PERF_IRQMASK_6338_REG		0xc
#घोषणा PERF_IRQMASK_6345_REG		0xc
#घोषणा PERF_IRQMASK_6348_REG		0xc
#घोषणा PERF_IRQMASK_6358_REG(x)	(0xc + (x) * 0x2c)
#घोषणा PERF_IRQMASK_6362_REG(x)	(0x20 + (x) * 0x10)
#घोषणा PERF_IRQMASK_6368_REG(x)	(0x20 + (x) * 0x10)

/* Interrupt Status रेजिस्टर */
#घोषणा PERF_IRQSTAT_3368_REG		0x10
#घोषणा PERF_IRQSTAT_6328_REG(x)	(0x28 + (x) * 0x10)
#घोषणा PERF_IRQSTAT_6338_REG		0x10
#घोषणा PERF_IRQSTAT_6345_REG		0x10
#घोषणा PERF_IRQSTAT_6348_REG		0x10
#घोषणा PERF_IRQSTAT_6358_REG(x)	(0x10 + (x) * 0x2c)
#घोषणा PERF_IRQSTAT_6362_REG(x)	(0x28 + (x) * 0x10)
#घोषणा PERF_IRQSTAT_6368_REG(x)	(0x28 + (x) * 0x10)

/* External Interrupt Configuration रेजिस्टर */
#घोषणा PERF_EXTIRQ_CFG_REG_3368	0x14
#घोषणा PERF_EXTIRQ_CFG_REG_6328	0x18
#घोषणा PERF_EXTIRQ_CFG_REG_6338	0x14
#घोषणा PERF_EXTIRQ_CFG_REG_6345	0x14
#घोषणा PERF_EXTIRQ_CFG_REG_6348	0x14
#घोषणा PERF_EXTIRQ_CFG_REG_6358	0x14
#घोषणा PERF_EXTIRQ_CFG_REG_6362	0x18
#घोषणा PERF_EXTIRQ_CFG_REG_6368	0x18

#घोषणा PERF_EXTIRQ_CFG_REG2_6368	0x1c

/* क्रम 6348 only */
#घोषणा EXTIRQ_CFG_SENSE_6348(x)	(1 << (x))
#घोषणा EXTIRQ_CFG_STAT_6348(x)		(1 << (x + 5))
#घोषणा EXTIRQ_CFG_CLEAR_6348(x)	(1 << (x + 10))
#घोषणा EXTIRQ_CFG_MASK_6348(x)		(1 << (x + 15))
#घोषणा EXTIRQ_CFG_BOTHEDGE_6348(x)	(1 << (x + 20))
#घोषणा EXTIRQ_CFG_LEVELSENSE_6348(x)	(1 << (x + 25))
#घोषणा EXTIRQ_CFG_CLEAR_ALL_6348	(0xf << 10)
#घोषणा EXTIRQ_CFG_MASK_ALL_6348	(0xf << 15)

/* क्रम all others */
#घोषणा EXTIRQ_CFG_SENSE(x)		(1 << (x))
#घोषणा EXTIRQ_CFG_STAT(x)		(1 << (x + 4))
#घोषणा EXTIRQ_CFG_CLEAR(x)		(1 << (x + 8))
#घोषणा EXTIRQ_CFG_MASK(x)		(1 << (x + 12))
#घोषणा EXTIRQ_CFG_BOTHEDGE(x)		(1 << (x + 16))
#घोषणा EXTIRQ_CFG_LEVELSENSE(x)	(1 << (x + 20))
#घोषणा EXTIRQ_CFG_CLEAR_ALL		(0xf << 8)
#घोषणा EXTIRQ_CFG_MASK_ALL		(0xf << 12)

/* Soft Reset रेजिस्टर */
#घोषणा PERF_SOFTRESET_REG		0x28
#घोषणा PERF_SOFTRESET_6328_REG		0x10
#घोषणा PERF_SOFTRESET_6358_REG		0x34
#घोषणा PERF_SOFTRESET_6362_REG		0x10
#घोषणा PERF_SOFTRESET_6368_REG		0x10

#घोषणा SOFTRESET_3368_SPI_MASK		(1 << 0)
#घोषणा SOFTRESET_3368_ENET_MASK	(1 << 2)
#घोषणा SOFTRESET_3368_MPI_MASK		(1 << 3)
#घोषणा SOFTRESET_3368_EPHY_MASK	(1 << 6)
#घोषणा SOFTRESET_3368_USBS_MASK	(1 << 11)
#घोषणा SOFTRESET_3368_PCM_MASK		(1 << 13)

#घोषणा SOFTRESET_6328_SPI_MASK		(1 << 0)
#घोषणा SOFTRESET_6328_EPHY_MASK	(1 << 1)
#घोषणा SOFTRESET_6328_SAR_MASK		(1 << 2)
#घोषणा SOFTRESET_6328_ENETSW_MASK	(1 << 3)
#घोषणा SOFTRESET_6328_USBS_MASK	(1 << 4)
#घोषणा SOFTRESET_6328_USBH_MASK	(1 << 5)
#घोषणा SOFTRESET_6328_PCM_MASK		(1 << 6)
#घोषणा SOFTRESET_6328_PCIE_CORE_MASK	(1 << 7)
#घोषणा SOFTRESET_6328_PCIE_MASK	(1 << 8)
#घोषणा SOFTRESET_6328_PCIE_EXT_MASK	(1 << 9)
#घोषणा SOFTRESET_6328_PCIE_HARD_MASK	(1 << 10)

#घोषणा SOFTRESET_6338_SPI_MASK		(1 << 0)
#घोषणा SOFTRESET_6338_ENET_MASK	(1 << 2)
#घोषणा SOFTRESET_6338_USBH_MASK	(1 << 3)
#घोषणा SOFTRESET_6338_USBS_MASK	(1 << 4)
#घोषणा SOFTRESET_6338_ADSL_MASK	(1 << 5)
#घोषणा SOFTRESET_6338_DMAMEM_MASK	(1 << 6)
#घोषणा SOFTRESET_6338_SAR_MASK		(1 << 7)
#घोषणा SOFTRESET_6338_ACLC_MASK	(1 << 8)
#घोषणा SOFTRESET_6338_ADSLMIPSPLL_MASK (1 << 10)
#घोषणा SOFTRESET_6338_ALL	 (SOFTRESET_6338_SPI_MASK |		\
				  SOFTRESET_6338_ENET_MASK |		\
				  SOFTRESET_6338_USBH_MASK |		\
				  SOFTRESET_6338_USBS_MASK |		\
				  SOFTRESET_6338_ADSL_MASK |		\
				  SOFTRESET_6338_DMAMEM_MASK |		\
				  SOFTRESET_6338_SAR_MASK |		\
				  SOFTRESET_6338_ACLC_MASK |		\
				  SOFTRESET_6338_ADSLMIPSPLL_MASK)

#घोषणा SOFTRESET_6348_SPI_MASK		(1 << 0)
#घोषणा SOFTRESET_6348_ENET_MASK	(1 << 2)
#घोषणा SOFTRESET_6348_USBH_MASK	(1 << 3)
#घोषणा SOFTRESET_6348_USBS_MASK	(1 << 4)
#घोषणा SOFTRESET_6348_ADSL_MASK	(1 << 5)
#घोषणा SOFTRESET_6348_DMAMEM_MASK	(1 << 6)
#घोषणा SOFTRESET_6348_SAR_MASK		(1 << 7)
#घोषणा SOFTRESET_6348_ACLC_MASK	(1 << 8)
#घोषणा SOFTRESET_6348_ADSLMIPSPLL_MASK (1 << 10)

#घोषणा SOFTRESET_6348_ALL	 (SOFTRESET_6348_SPI_MASK |		\
				  SOFTRESET_6348_ENET_MASK |		\
				  SOFTRESET_6348_USBH_MASK |		\
				  SOFTRESET_6348_USBS_MASK |		\
				  SOFTRESET_6348_ADSL_MASK |		\
				  SOFTRESET_6348_DMAMEM_MASK |		\
				  SOFTRESET_6348_SAR_MASK |		\
				  SOFTRESET_6348_ACLC_MASK |		\
				  SOFTRESET_6348_ADSLMIPSPLL_MASK)

#घोषणा SOFTRESET_6358_SPI_MASK		(1 << 0)
#घोषणा SOFTRESET_6358_ENET_MASK	(1 << 2)
#घोषणा SOFTRESET_6358_MPI_MASK		(1 << 3)
#घोषणा SOFTRESET_6358_EPHY_MASK	(1 << 6)
#घोषणा SOFTRESET_6358_SAR_MASK		(1 << 7)
#घोषणा SOFTRESET_6358_USBH_MASK	(1 << 12)
#घोषणा SOFTRESET_6358_PCM_MASK		(1 << 13)
#घोषणा SOFTRESET_6358_ADSL_MASK	(1 << 14)

#घोषणा SOFTRESET_6362_SPI_MASK		(1 << 0)
#घोषणा SOFTRESET_6362_IPSEC_MASK	(1 << 1)
#घोषणा SOFTRESET_6362_EPHY_MASK	(1 << 2)
#घोषणा SOFTRESET_6362_SAR_MASK		(1 << 3)
#घोषणा SOFTRESET_6362_ENETSW_MASK	(1 << 4)
#घोषणा SOFTRESET_6362_USBS_MASK	(1 << 5)
#घोषणा SOFTRESET_6362_USBH_MASK	(1 << 6)
#घोषणा SOFTRESET_6362_PCM_MASK		(1 << 7)
#घोषणा SOFTRESET_6362_PCIE_CORE_MASK	(1 << 8)
#घोषणा SOFTRESET_6362_PCIE_MASK	(1 << 9)
#घोषणा SOFTRESET_6362_PCIE_EXT_MASK	(1 << 10)
#घोषणा SOFTRESET_6362_WLAN_SHIM_MASK	(1 << 11)
#घोषणा SOFTRESET_6362_DDR_PHY_MASK	(1 << 12)
#घोषणा SOFTRESET_6362_FAP_MASK		(1 << 13)
#घोषणा SOFTRESET_6362_WLAN_UBUS_MASK	(1 << 14)

#घोषणा SOFTRESET_6368_SPI_MASK		(1 << 0)
#घोषणा SOFTRESET_6368_MPI_MASK		(1 << 3)
#घोषणा SOFTRESET_6368_EPHY_MASK	(1 << 6)
#घोषणा SOFTRESET_6368_SAR_MASK		(1 << 7)
#घोषणा SOFTRESET_6368_ENETSW_MASK	(1 << 10)
#घोषणा SOFTRESET_6368_USBS_MASK	(1 << 11)
#घोषणा SOFTRESET_6368_USBH_MASK	(1 << 12)
#घोषणा SOFTRESET_6368_PCM_MASK		(1 << 13)

/* MIPS PLL control रेजिस्टर */
#घोषणा PERF_MIPSPLLCTL_REG		0x34
#घोषणा MIPSPLLCTL_N1_SHIFT		20
#घोषणा MIPSPLLCTL_N1_MASK		(0x7 << MIPSPLLCTL_N1_SHIFT)
#घोषणा MIPSPLLCTL_N2_SHIFT		15
#घोषणा MIPSPLLCTL_N2_MASK		(0x1f << MIPSPLLCTL_N2_SHIFT)
#घोषणा MIPSPLLCTL_M1REF_SHIFT		12
#घोषणा MIPSPLLCTL_M1REF_MASK		(0x7 << MIPSPLLCTL_M1REF_SHIFT)
#घोषणा MIPSPLLCTL_M2REF_SHIFT		9
#घोषणा MIPSPLLCTL_M2REF_MASK		(0x7 << MIPSPLLCTL_M2REF_SHIFT)
#घोषणा MIPSPLLCTL_M1CPU_SHIFT		6
#घोषणा MIPSPLLCTL_M1CPU_MASK		(0x7 << MIPSPLLCTL_M1CPU_SHIFT)
#घोषणा MIPSPLLCTL_M1BUS_SHIFT		3
#घोषणा MIPSPLLCTL_M1BUS_MASK		(0x7 << MIPSPLLCTL_M1BUS_SHIFT)
#घोषणा MIPSPLLCTL_M2BUS_SHIFT		0
#घोषणा MIPSPLLCTL_M2BUS_MASK		(0x7 << MIPSPLLCTL_M2BUS_SHIFT)

/* ADSL PHY PLL Control रेजिस्टर */
#घोषणा PERF_ADSLPLLCTL_REG		0x38
#घोषणा ADSLPLLCTL_N1_SHIFT		20
#घोषणा ADSLPLLCTL_N1_MASK		(0x7 << ADSLPLLCTL_N1_SHIFT)
#घोषणा ADSLPLLCTL_N2_SHIFT		15
#घोषणा ADSLPLLCTL_N2_MASK		(0x1f << ADSLPLLCTL_N2_SHIFT)
#घोषणा ADSLPLLCTL_M1REF_SHIFT		12
#घोषणा ADSLPLLCTL_M1REF_MASK		(0x7 << ADSLPLLCTL_M1REF_SHIFT)
#घोषणा ADSLPLLCTL_M2REF_SHIFT		9
#घोषणा ADSLPLLCTL_M2REF_MASK		(0x7 << ADSLPLLCTL_M2REF_SHIFT)
#घोषणा ADSLPLLCTL_M1CPU_SHIFT		6
#घोषणा ADSLPLLCTL_M1CPU_MASK		(0x7 << ADSLPLLCTL_M1CPU_SHIFT)
#घोषणा ADSLPLLCTL_M1BUS_SHIFT		3
#घोषणा ADSLPLLCTL_M1BUS_MASK		(0x7 << ADSLPLLCTL_M1BUS_SHIFT)
#घोषणा ADSLPLLCTL_M2BUS_SHIFT		0
#घोषणा ADSLPLLCTL_M2BUS_MASK		(0x7 << ADSLPLLCTL_M2BUS_SHIFT)

#घोषणा ADSLPLLCTL_VAL(n1, n2, m1ref, m2ref, m1cpu, m1bus, m2bus)	\
				(((n1) << ADSLPLLCTL_N1_SHIFT) |	\
				((n2) << ADSLPLLCTL_N2_SHIFT) |		\
				((m1ref) << ADSLPLLCTL_M1REF_SHIFT) |	\
				((m2ref) << ADSLPLLCTL_M2REF_SHIFT) |	\
				((m1cpu) << ADSLPLLCTL_M1CPU_SHIFT) |	\
				((m1bus) << ADSLPLLCTL_M1BUS_SHIFT) |	\
				((m2bus) << ADSLPLLCTL_M2BUS_SHIFT))


/*************************************************************************
 * _REG relative to RSET_TIMER
 *************************************************************************/

#घोषणा BCM63XX_TIMER_COUNT		4
#घोषणा TIMER_T0_ID			0
#घोषणा TIMER_T1_ID			1
#घोषणा TIMER_T2_ID			2
#घोषणा TIMER_WDT_ID			3

/* Timer irqstat रेजिस्टर */
#घोषणा TIMER_IRQSTAT_REG		0
#घोषणा TIMER_IRQSTAT_TIMER_CAUSE(x)	(1 << (x))
#घोषणा TIMER_IRQSTAT_TIMER0_CAUSE	(1 << 0)
#घोषणा TIMER_IRQSTAT_TIMER1_CAUSE	(1 << 1)
#घोषणा TIMER_IRQSTAT_TIMER2_CAUSE	(1 << 2)
#घोषणा TIMER_IRQSTAT_WDT_CAUSE		(1 << 3)
#घोषणा TIMER_IRQSTAT_TIMER_IR_EN(x)	(1 << ((x) + 8))
#घोषणा TIMER_IRQSTAT_TIMER0_IR_EN	(1 << 8)
#घोषणा TIMER_IRQSTAT_TIMER1_IR_EN	(1 << 9)
#घोषणा TIMER_IRQSTAT_TIMER2_IR_EN	(1 << 10)

/* Timer control रेजिस्टर */
#घोषणा TIMER_CTLx_REG(x)		(0x4 + (x * 4))
#घोषणा TIMER_CTL0_REG			0x4
#घोषणा TIMER_CTL1_REG			0x8
#घोषणा TIMER_CTL2_REG			0xC
#घोषणा TIMER_CTL_COUNTDOWN_MASK	(0x3fffffff)
#घोषणा TIMER_CTL_MONOTONIC_MASK	(1 << 30)
#घोषणा TIMER_CTL_ENABLE_MASK		(1 << 31)


/*************************************************************************
 * _REG relative to RSET_WDT
 *************************************************************************/

/* Watchकरोg शेष count रेजिस्टर */
#घोषणा WDT_DEFVAL_REG			0x0

/* Watchकरोg control रेजिस्टर */
#घोषणा WDT_CTL_REG			0x4

/* Watchकरोg control रेजिस्टर स्थिरants */
#घोषणा WDT_START_1			(0xff00)
#घोषणा WDT_START_2			(0x00ff)
#घोषणा WDT_STOP_1			(0xee00)
#घोषणा WDT_STOP_2			(0x00ee)

/* Watchकरोg reset length रेजिस्टर */
#घोषणा WDT_RSTLEN_REG			0x8

/* Watchकरोg soft reset रेजिस्टर (BCM6328 only) */
#घोषणा WDT_SOFTRESET_REG		0xc

/*************************************************************************
 * _REG relative to RSET_GPIO
 *************************************************************************/

/* GPIO रेजिस्टरs */
#घोषणा GPIO_CTL_HI_REG			0x0
#घोषणा GPIO_CTL_LO_REG			0x4
#घोषणा GPIO_DATA_HI_REG		0x8
#घोषणा GPIO_DATA_LO_REG		0xC
#घोषणा GPIO_DATA_LO_REG_6345		0x8

/* GPIO mux रेजिस्टरs and स्थिरants */
#घोषणा GPIO_MODE_REG			0x18

#घोषणा GPIO_MODE_6348_G4_DIAG		0x00090000
#घोषणा GPIO_MODE_6348_G4_UTOPIA	0x00080000
#घोषणा GPIO_MODE_6348_G4_LEGACY_LED	0x00030000
#घोषणा GPIO_MODE_6348_G4_MII_SNOOP	0x00020000
#घोषणा GPIO_MODE_6348_G4_EXT_EPHY	0x00010000
#घोषणा GPIO_MODE_6348_G3_DIAG		0x00009000
#घोषणा GPIO_MODE_6348_G3_UTOPIA	0x00008000
#घोषणा GPIO_MODE_6348_G3_EXT_MII	0x00007000
#घोषणा GPIO_MODE_6348_G2_DIAG		0x00000900
#घोषणा GPIO_MODE_6348_G2_PCI		0x00000500
#घोषणा GPIO_MODE_6348_G1_DIAG		0x00000090
#घोषणा GPIO_MODE_6348_G1_UTOPIA	0x00000080
#घोषणा GPIO_MODE_6348_G1_SPI_UART	0x00000060
#घोषणा GPIO_MODE_6348_G1_SPI_MASTER	0x00000060
#घोषणा GPIO_MODE_6348_G1_MII_PCCARD	0x00000040
#घोषणा GPIO_MODE_6348_G1_MII_SNOOP	0x00000020
#घोषणा GPIO_MODE_6348_G1_EXT_EPHY	0x00000010
#घोषणा GPIO_MODE_6348_G0_DIAG		0x00000009
#घोषणा GPIO_MODE_6348_G0_EXT_MII	0x00000007

#घोषणा GPIO_MODE_6358_EXTRACS		(1 << 5)
#घोषणा GPIO_MODE_6358_UART1		(1 << 6)
#घोषणा GPIO_MODE_6358_EXTRA_SPI_SS	(1 << 7)
#घोषणा GPIO_MODE_6358_SERIAL_LED	(1 << 10)
#घोषणा GPIO_MODE_6358_UTOPIA		(1 << 12)

#घोषणा GPIO_MODE_6368_ANALOG_AFE_0	(1 << 0)
#घोषणा GPIO_MODE_6368_ANALOG_AFE_1	(1 << 1)
#घोषणा GPIO_MODE_6368_SYS_IRQ		(1 << 2)
#घोषणा GPIO_MODE_6368_SERIAL_LED_DATA	(1 << 3)
#घोषणा GPIO_MODE_6368_SERIAL_LED_CLK	(1 << 4)
#घोषणा GPIO_MODE_6368_INET_LED		(1 << 5)
#घोषणा GPIO_MODE_6368_EPHY0_LED	(1 << 6)
#घोषणा GPIO_MODE_6368_EPHY1_LED	(1 << 7)
#घोषणा GPIO_MODE_6368_EPHY2_LED	(1 << 8)
#घोषणा GPIO_MODE_6368_EPHY3_LED	(1 << 9)
#घोषणा GPIO_MODE_6368_ROBOSW_LED_DAT	(1 << 10)
#घोषणा GPIO_MODE_6368_ROBOSW_LED_CLK	(1 << 11)
#घोषणा GPIO_MODE_6368_ROBOSW_LED0	(1 << 12)
#घोषणा GPIO_MODE_6368_ROBOSW_LED1	(1 << 13)
#घोषणा GPIO_MODE_6368_USBD_LED		(1 << 14)
#घोषणा GPIO_MODE_6368_NTR_PULSE	(1 << 15)
#घोषणा GPIO_MODE_6368_PCI_REQ1		(1 << 16)
#घोषणा GPIO_MODE_6368_PCI_GNT1		(1 << 17)
#घोषणा GPIO_MODE_6368_PCI_INTB		(1 << 18)
#घोषणा GPIO_MODE_6368_PCI_REQ0		(1 << 19)
#घोषणा GPIO_MODE_6368_PCI_GNT0		(1 << 20)
#घोषणा GPIO_MODE_6368_PCMCIA_CD1	(1 << 22)
#घोषणा GPIO_MODE_6368_PCMCIA_CD2	(1 << 23)
#घोषणा GPIO_MODE_6368_PCMCIA_VS1	(1 << 24)
#घोषणा GPIO_MODE_6368_PCMCIA_VS2	(1 << 25)
#घोषणा GPIO_MODE_6368_EBI_CS2		(1 << 26)
#घोषणा GPIO_MODE_6368_EBI_CS3		(1 << 27)
#घोषणा GPIO_MODE_6368_SPI_SSN2		(1 << 28)
#घोषणा GPIO_MODE_6368_SPI_SSN3		(1 << 29)
#घोषणा GPIO_MODE_6368_SPI_SSN4		(1 << 30)
#घोषणा GPIO_MODE_6368_SPI_SSN5		(1 << 31)


#घोषणा GPIO_PINMUX_OTHR_REG		0x24
#घोषणा GPIO_PINMUX_OTHR_6328_USB_SHIFT 12
#घोषणा GPIO_PINMUX_OTHR_6328_USB_MASK	(3 << GPIO_PINMUX_OTHR_6328_USB_SHIFT)
#घोषणा GPIO_PINMUX_OTHR_6328_USB_HOST	(1 << GPIO_PINMUX_OTHR_6328_USB_SHIFT)
#घोषणा GPIO_PINMUX_OTHR_6328_USB_DEV	(2 << GPIO_PINMUX_OTHR_6328_USB_SHIFT)

#घोषणा GPIO_BASEMODE_6368_REG		0x38
#घोषणा GPIO_BASEMODE_6368_UART2	0x1
#घोषणा GPIO_BASEMODE_6368_GPIO		0x0
#घोषणा GPIO_BASEMODE_6368_MASK		0x7
/* those bits must be kept as पढ़ो in gpio basemode रेजिस्टर*/

#घोषणा GPIO_STRAPBUS_REG		0x40
#घोषणा STRAPBUS_6358_BOOT_SEL_PARALLEL (1 << 1)
#घोषणा STRAPBUS_6358_BOOT_SEL_SERIAL	(0 << 1)
#घोषणा STRAPBUS_6368_BOOT_SEL_MASK	0x3
#घोषणा STRAPBUS_6368_BOOT_SEL_न_अंकD	0
#घोषणा STRAPBUS_6368_BOOT_SEL_SERIAL	1
#घोषणा STRAPBUS_6368_BOOT_SEL_PARALLEL 3


/*************************************************************************
 * _REG relative to RSET_ENET
 *************************************************************************/

/* Receiver Configuration रेजिस्टर */
#घोषणा ENET_RXCFG_REG			0x0
#घोषणा ENET_RXCFG_ALLMCAST_SHIFT	1
#घोषणा ENET_RXCFG_ALLMCAST_MASK	(1 << ENET_RXCFG_ALLMCAST_SHIFT)
#घोषणा ENET_RXCFG_PROMISC_SHIFT	3
#घोषणा ENET_RXCFG_PROMISC_MASK		(1 << ENET_RXCFG_PROMISC_SHIFT)
#घोषणा ENET_RXCFG_LOOPBACK_SHIFT	4
#घोषणा ENET_RXCFG_LOOPBACK_MASK	(1 << ENET_RXCFG_LOOPBACK_SHIFT)
#घोषणा ENET_RXCFG_ENFLOW_SHIFT		5
#घोषणा ENET_RXCFG_ENFLOW_MASK		(1 << ENET_RXCFG_ENFLOW_SHIFT)

/* Receive Maximum Length रेजिस्टर */
#घोषणा ENET_RXMAXLEN_REG		0x4
#घोषणा ENET_RXMAXLEN_SHIFT		0
#घोषणा ENET_RXMAXLEN_MASK		(0x7ff << ENET_RXMAXLEN_SHIFT)

/* Transmit Maximum Length रेजिस्टर */
#घोषणा ENET_TXMAXLEN_REG		0x8
#घोषणा ENET_TXMAXLEN_SHIFT		0
#घोषणा ENET_TXMAXLEN_MASK		(0x7ff << ENET_TXMAXLEN_SHIFT)

/* MII Status/Control रेजिस्टर */
#घोषणा ENET_MIISC_REG			0x10
#घोषणा ENET_MIISC_MDCFREQDIV_SHIFT	0
#घोषणा ENET_MIISC_MDCFREQDIV_MASK	(0x7f << ENET_MIISC_MDCFREQDIV_SHIFT)
#घोषणा ENET_MIISC_PREAMBLEEN_SHIFT	7
#घोषणा ENET_MIISC_PREAMBLEEN_MASK	(1 << ENET_MIISC_PREAMBLEEN_SHIFT)

/* MII Data रेजिस्टर */
#घोषणा ENET_MIIDATA_REG		0x14
#घोषणा ENET_MIIDATA_DATA_SHIFT		0
#घोषणा ENET_MIIDATA_DATA_MASK		(0xffff << ENET_MIIDATA_DATA_SHIFT)
#घोषणा ENET_MIIDATA_TA_SHIFT		16
#घोषणा ENET_MIIDATA_TA_MASK		(0x3 << ENET_MIIDATA_TA_SHIFT)
#घोषणा ENET_MIIDATA_REG_SHIFT		18
#घोषणा ENET_MIIDATA_REG_MASK		(0x1f << ENET_MIIDATA_REG_SHIFT)
#घोषणा ENET_MIIDATA_PHYID_SHIFT	23
#घोषणा ENET_MIIDATA_PHYID_MASK		(0x1f << ENET_MIIDATA_PHYID_SHIFT)
#घोषणा ENET_MIIDATA_OP_READ_MASK	(0x6 << 28)
#घोषणा ENET_MIIDATA_OP_WRITE_MASK	(0x5 << 28)

/* Ethernet Interrupt Mask रेजिस्टर */
#घोषणा ENET_IRMASK_REG			0x18

/* Ethernet Interrupt रेजिस्टर */
#घोषणा ENET_IR_REG			0x1c
#घोषणा ENET_IR_MII			(1 << 0)
#घोषणा ENET_IR_MIB			(1 << 1)
#घोषणा ENET_IR_FLOWC			(1 << 2)

/* Ethernet Control रेजिस्टर */
#घोषणा ENET_CTL_REG			0x2c
#घोषणा ENET_CTL_ENABLE_SHIFT		0
#घोषणा ENET_CTL_ENABLE_MASK		(1 << ENET_CTL_ENABLE_SHIFT)
#घोषणा ENET_CTL_DISABLE_SHIFT		1
#घोषणा ENET_CTL_DISABLE_MASK		(1 << ENET_CTL_DISABLE_SHIFT)
#घोषणा ENET_CTL_SRESET_SHIFT		2
#घोषणा ENET_CTL_SRESET_MASK		(1 << ENET_CTL_SRESET_SHIFT)
#घोषणा ENET_CTL_EPHYSEL_SHIFT		3
#घोषणा ENET_CTL_EPHYSEL_MASK		(1 << ENET_CTL_EPHYSEL_SHIFT)

/* Transmit Control रेजिस्टर */
#घोषणा ENET_TXCTL_REG			0x30
#घोषणा ENET_TXCTL_FD_SHIFT		0
#घोषणा ENET_TXCTL_FD_MASK		(1 << ENET_TXCTL_FD_SHIFT)

/* Transmit Watermask रेजिस्टर */
#घोषणा ENET_TXWMARK_REG		0x34
#घोषणा ENET_TXWMARK_WM_SHIFT		0
#घोषणा ENET_TXWMARK_WM_MASK		(0x3f << ENET_TXWMARK_WM_SHIFT)

/* MIB Control रेजिस्टर */
#घोषणा ENET_MIBCTL_REG			0x38
#घोषणा ENET_MIBCTL_RDCLEAR_SHIFT	0
#घोषणा ENET_MIBCTL_RDCLEAR_MASK	(1 << ENET_MIBCTL_RDCLEAR_SHIFT)

/* Perfect Match Data Low रेजिस्टर */
#घोषणा ENET_PML_REG(x)			(0x58 + (x) * 8)
#घोषणा ENET_PMH_REG(x)			(0x5c + (x) * 8)
#घोषणा ENET_PMH_DATAVALID_SHIFT	16
#घोषणा ENET_PMH_DATAVALID_MASK		(1 << ENET_PMH_DATAVALID_SHIFT)

/* MIB रेजिस्टर */
#घोषणा ENET_MIB_REG(x)			(0x200 + (x) * 4)
#घोषणा ENET_MIB_REG_COUNT		55


/*************************************************************************
 * _REG relative to RSET_ENETDMA
 *************************************************************************/
#घोषणा ENETDMA_CHAN_WIDTH		0x10
#घोषणा ENETDMA_6345_CHAN_WIDTH		0x40

/* Controller Configuration Register */
#घोषणा ENETDMA_CFG_REG			(0x0)
#घोषणा ENETDMA_CFG_EN_SHIFT		0
#घोषणा ENETDMA_CFG_EN_MASK		(1 << ENETDMA_CFG_EN_SHIFT)
#घोषणा ENETDMA_CFG_FLOWCH_MASK(x)	(1 << ((x >> 1) + 1))

/* Flow Control Descriptor Low Threshold रेजिस्टर */
#घोषणा ENETDMA_FLOWCL_REG(x)		(0x4 + (x) * 6)

/* Flow Control Descriptor High Threshold रेजिस्टर */
#घोषणा ENETDMA_FLOWCH_REG(x)		(0x8 + (x) * 6)

/* Flow Control Descriptor Buffer Alloca Threshold रेजिस्टर */
#घोषणा ENETDMA_BUFALLOC_REG(x)		(0xc + (x) * 6)
#घोषणा ENETDMA_BUFALLOC_FORCE_SHIFT	31
#घोषणा ENETDMA_BUFALLOC_FORCE_MASK	(1 << ENETDMA_BUFALLOC_FORCE_SHIFT)

/* Global पूर्णांकerrupt status */
#घोषणा ENETDMA_GLB_IRQSTAT_REG		(0x40)

/* Global पूर्णांकerrupt mask */
#घोषणा ENETDMA_GLB_IRQMASK_REG		(0x44)

/* Channel Configuration रेजिस्टर */
#घोषणा ENETDMA_CHANCFG_REG(x)		(0x100 + (x) * 0x10)
#घोषणा ENETDMA_CHANCFG_EN_SHIFT	0
#घोषणा ENETDMA_CHANCFG_EN_MASK		(1 << ENETDMA_CHANCFG_EN_SHIFT)
#घोषणा ENETDMA_CHANCFG_PKTHALT_SHIFT	1
#घोषणा ENETDMA_CHANCFG_PKTHALT_MASK	(1 << ENETDMA_CHANCFG_PKTHALT_SHIFT)

/* Interrupt Control/Status रेजिस्टर */
#घोषणा ENETDMA_IR_REG(x)		(0x104 + (x) * 0x10)
#घोषणा ENETDMA_IR_BUFDONE_MASK		(1 << 0)
#घोषणा ENETDMA_IR_PKTDONE_MASK		(1 << 1)
#घोषणा ENETDMA_IR_NOTOWNER_MASK	(1 << 2)

/* Interrupt Mask रेजिस्टर */
#घोषणा ENETDMA_IRMASK_REG(x)		(0x108 + (x) * 0x10)

/* Maximum Burst Length */
#घोषणा ENETDMA_MAXBURST_REG(x)		(0x10C + (x) * 0x10)

/* Ring Start Address रेजिस्टर */
#घोषणा ENETDMA_RSTART_REG(x)		(0x200 + (x) * 0x10)

/* State Ram Word 2 */
#घोषणा ENETDMA_SRAM2_REG(x)		(0x204 + (x) * 0x10)

/* State Ram Word 3 */
#घोषणा ENETDMA_SRAM3_REG(x)		(0x208 + (x) * 0x10)

/* State Ram Word 4 */
#घोषणा ENETDMA_SRAM4_REG(x)		(0x20c + (x) * 0x10)

/* Broadcom 6345 ENET DMA definitions */
#घोषणा ENETDMA_6345_CHANCFG_REG	(0x00)

#घोषणा ENETDMA_6345_MAXBURST_REG	(0x04)

#घोषणा ENETDMA_6345_RSTART_REG		(0x08)

#घोषणा ENETDMA_6345_LEN_REG		(0x0C)

#घोषणा ENETDMA_6345_IR_REG		(0x14)

#घोषणा ENETDMA_6345_IRMASK_REG		(0x18)

#घोषणा ENETDMA_6345_FC_REG		(0x1C)

#घोषणा ENETDMA_6345_BUFALLOC_REG	(0x20)

/* Shअगरt करोwn क्रम EOP, SOP and WRAP bits */
#घोषणा ENETDMA_6345_DESC_SHIFT		(3)

/*************************************************************************
 * _REG relative to RSET_ENETDMAC
 *************************************************************************/

/* Channel Configuration रेजिस्टर */
#घोषणा ENETDMAC_CHANCFG_REG		(0x0)
#घोषणा ENETDMAC_CHANCFG_EN_SHIFT	0
#घोषणा ENETDMAC_CHANCFG_EN_MASK	(1 << ENETDMAC_CHANCFG_EN_SHIFT)
#घोषणा ENETDMAC_CHANCFG_PKTHALT_SHIFT	1
#घोषणा ENETDMAC_CHANCFG_PKTHALT_MASK	(1 << ENETDMAC_CHANCFG_PKTHALT_SHIFT)
#घोषणा ENETDMAC_CHANCFG_BUFHALT_SHIFT	2
#घोषणा ENETDMAC_CHANCFG_BUFHALT_MASK	(1 << ENETDMAC_CHANCFG_BUFHALT_SHIFT)
#घोषणा ENETDMAC_CHANCFG_CHAINING_SHIFT	2
#घोषणा ENETDMAC_CHANCFG_CHAINING_MASK	(1 << ENETDMAC_CHANCFG_CHAINING_SHIFT)
#घोषणा ENETDMAC_CHANCFG_WRAP_EN_SHIFT	3
#घोषणा ENETDMAC_CHANCFG_WRAP_EN_MASK	(1 << ENETDMAC_CHANCFG_WRAP_EN_SHIFT)
#घोषणा ENETDMAC_CHANCFG_FLOWC_EN_SHIFT	4
#घोषणा ENETDMAC_CHANCFG_FLOWC_EN_MASK	(1 << ENETDMAC_CHANCFG_FLOWC_EN_SHIFT)

/* Interrupt Control/Status रेजिस्टर */
#घोषणा ENETDMAC_IR_REG			(0x4)
#घोषणा ENETDMAC_IR_BUFDONE_MASK	(1 << 0)
#घोषणा ENETDMAC_IR_PKTDONE_MASK	(1 << 1)
#घोषणा ENETDMAC_IR_NOTOWNER_MASK	(1 << 2)

/* Interrupt Mask रेजिस्टर */
#घोषणा ENETDMAC_IRMASK_REG		(0x8)

/* Maximum Burst Length */
#घोषणा ENETDMAC_MAXBURST_REG		(0xc)


/*************************************************************************
 * _REG relative to RSET_ENETDMAS
 *************************************************************************/

/* Ring Start Address रेजिस्टर */
#घोषणा ENETDMAS_RSTART_REG		(0x0)

/* State Ram Word 2 */
#घोषणा ENETDMAS_SRAM2_REG		(0x4)

/* State Ram Word 3 */
#घोषणा ENETDMAS_SRAM3_REG		(0x8)

/* State Ram Word 4 */
#घोषणा ENETDMAS_SRAM4_REG		(0xc)


/*************************************************************************
 * _REG relative to RSET_ENETSW
 *************************************************************************/

/* Port traffic control */
#घोषणा ENETSW_PTCTRL_REG(x)		(0x0 + (x))
#घोषणा ENETSW_PTCTRL_RXDIS_MASK	(1 << 0)
#घोषणा ENETSW_PTCTRL_TXDIS_MASK	(1 << 1)

/* Switch mode रेजिस्टर */
#घोषणा ENETSW_SWMODE_REG		(0xb)
#घोषणा ENETSW_SWMODE_FWD_EN_MASK	(1 << 1)

/* IMP override Register */
#घोषणा ENETSW_IMPOV_REG		(0xe)
#घोषणा ENETSW_IMPOV_FORCE_MASK		(1 << 7)
#घोषणा ENETSW_IMPOV_TXFLOW_MASK	(1 << 5)
#घोषणा ENETSW_IMPOV_RXFLOW_MASK	(1 << 4)
#घोषणा ENETSW_IMPOV_1000_MASK		(1 << 3)
#घोषणा ENETSW_IMPOV_100_MASK		(1 << 2)
#घोषणा ENETSW_IMPOV_FDX_MASK		(1 << 1)
#घोषणा ENETSW_IMPOV_LINKUP_MASK	(1 << 0)

/* Port override Register */
#घोषणा ENETSW_PORTOV_REG(x)		(0x58 + (x))
#घोषणा ENETSW_PORTOV_ENABLE_MASK	(1 << 6)
#घोषणा ENETSW_PORTOV_TXFLOW_MASK	(1 << 5)
#घोषणा ENETSW_PORTOV_RXFLOW_MASK	(1 << 4)
#घोषणा ENETSW_PORTOV_1000_MASK		(1 << 3)
#घोषणा ENETSW_PORTOV_100_MASK		(1 << 2)
#घोषणा ENETSW_PORTOV_FDX_MASK		(1 << 1)
#घोषणा ENETSW_PORTOV_LINKUP_MASK	(1 << 0)

/* MDIO control रेजिस्टर */
#घोषणा ENETSW_MDIOC_REG		(0xb0)
#घोषणा ENETSW_MDIOC_EXT_MASK		(1 << 16)
#घोषणा ENETSW_MDIOC_REG_SHIFT		20
#घोषणा ENETSW_MDIOC_PHYID_SHIFT	25
#घोषणा ENETSW_MDIOC_RD_MASK		(1 << 30)
#घोषणा ENETSW_MDIOC_WR_MASK		(1 << 31)

/* MDIO data रेजिस्टर */
#घोषणा ENETSW_MDIOD_REG		(0xb4)

/* Global Management Configuration Register */
#घोषणा ENETSW_GMCR_REG			(0x200)
#घोषणा ENETSW_GMCR_RST_MIB_MASK	(1 << 0)

/* MIB रेजिस्टर */
#घोषणा ENETSW_MIB_REG(x)		(0x2800 + (x) * 4)
#घोषणा ENETSW_MIB_REG_COUNT		47

/* Jumbo control रेजिस्टर port mask रेजिस्टर */
#घोषणा ENETSW_JMBCTL_PORT_REG		(0x4004)

/* Jumbo control mib good frame रेजिस्टर */
#घोषणा ENETSW_JMBCTL_MAXSIZE_REG	(0x4008)


/*************************************************************************
 * _REG relative to RSET_OHCI_PRIV
 *************************************************************************/

#घोषणा OHCI_PRIV_REG			0x0
#घोषणा OHCI_PRIV_PORT1_HOST_SHIFT	0
#घोषणा OHCI_PRIV_PORT1_HOST_MASK	(1 << OHCI_PRIV_PORT1_HOST_SHIFT)
#घोषणा OHCI_PRIV_REG_SWAP_SHIFT	3
#घोषणा OHCI_PRIV_REG_SWAP_MASK		(1 << OHCI_PRIV_REG_SWAP_SHIFT)


/*************************************************************************
 * _REG relative to RSET_USBH_PRIV
 *************************************************************************/

#घोषणा USBH_PRIV_SWAP_6358_REG		0x0
#घोषणा USBH_PRIV_SWAP_6368_REG		0x1c

#घोषणा USBH_PRIV_SWAP_USBD_SHIFT	6
#घोषणा USBH_PRIV_SWAP_USBD_MASK	(1 << USBH_PRIV_SWAP_USBD_SHIFT)
#घोषणा USBH_PRIV_SWAP_EHCI_ENDN_SHIFT	4
#घोषणा USBH_PRIV_SWAP_EHCI_ENDN_MASK	(1 << USBH_PRIV_SWAP_EHCI_ENDN_SHIFT)
#घोषणा USBH_PRIV_SWAP_EHCI_DATA_SHIFT	3
#घोषणा USBH_PRIV_SWAP_EHCI_DATA_MASK	(1 << USBH_PRIV_SWAP_EHCI_DATA_SHIFT)
#घोषणा USBH_PRIV_SWAP_OHCI_ENDN_SHIFT	1
#घोषणा USBH_PRIV_SWAP_OHCI_ENDN_MASK	(1 << USBH_PRIV_SWAP_OHCI_ENDN_SHIFT)
#घोषणा USBH_PRIV_SWAP_OHCI_DATA_SHIFT	0
#घोषणा USBH_PRIV_SWAP_OHCI_DATA_MASK	(1 << USBH_PRIV_SWAP_OHCI_DATA_SHIFT)

#घोषणा USBH_PRIV_UTMI_CTL_6368_REG	0x10
#घोषणा USBH_PRIV_UTMI_CTL_NODRIV_SHIFT 12
#घोषणा USBH_PRIV_UTMI_CTL_NODRIV_MASK	(0xf << USBH_PRIV_UTMI_CTL_NODRIV_SHIFT)
#घोषणा USBH_PRIV_UTMI_CTL_HOSTB_SHIFT	0
#घोषणा USBH_PRIV_UTMI_CTL_HOSTB_MASK	(0xf << USBH_PRIV_UTMI_CTL_HOSTB_SHIFT)

#घोषणा USBH_PRIV_TEST_6358_REG		0x24
#घोषणा USBH_PRIV_TEST_6368_REG		0x14

#घोषणा USBH_PRIV_SETUP_6368_REG	0x28
#घोषणा USBH_PRIV_SETUP_IOC_SHIFT	4
#घोषणा USBH_PRIV_SETUP_IOC_MASK	(1 << USBH_PRIV_SETUP_IOC_SHIFT)


/*************************************************************************
 * _REG relative to RSET_USBD
 *************************************************************************/

/* General control */
#घोषणा USBD_CONTROL_REG		0x00
#घोषणा USBD_CONTROL_TXZLENINS_SHIFT	14
#घोषणा USBD_CONTROL_TXZLENINS_MASK	(1 << USBD_CONTROL_TXZLENINS_SHIFT)
#घोषणा USBD_CONTROL_AUTO_CSRS_SHIFT	13
#घोषणा USBD_CONTROL_AUTO_CSRS_MASK	(1 << USBD_CONTROL_AUTO_CSRS_SHIFT)
#घोषणा USBD_CONTROL_RXZSCFG_SHIFT	12
#घोषणा USBD_CONTROL_RXZSCFG_MASK	(1 << USBD_CONTROL_RXZSCFG_SHIFT)
#घोषणा USBD_CONTROL_INIT_SEL_SHIFT	8
#घोषणा USBD_CONTROL_INIT_SEL_MASK	(0xf << USBD_CONTROL_INIT_SEL_SHIFT)
#घोषणा USBD_CONTROL_FIFO_RESET_SHIFT	6
#घोषणा USBD_CONTROL_FIFO_RESET_MASK	(3 << USBD_CONTROL_FIFO_RESET_SHIFT)
#घोषणा USBD_CONTROL_SETUPERRLOCK_SHIFT 5
#घोषणा USBD_CONTROL_SETUPERRLOCK_MASK	(1 << USBD_CONTROL_SETUPERRLOCK_SHIFT)
#घोषणा USBD_CONTROL_DONE_CSRS_SHIFT	0
#घोषणा USBD_CONTROL_DONE_CSRS_MASK	(1 << USBD_CONTROL_DONE_CSRS_SHIFT)

/* Strap options */
#घोषणा USBD_STRAPS_REG			0x04
#घोषणा USBD_STRAPS_APP_SELF_PWR_SHIFT	10
#घोषणा USBD_STRAPS_APP_SELF_PWR_MASK	(1 << USBD_STRAPS_APP_SELF_PWR_SHIFT)
#घोषणा USBD_STRAPS_APP_DISCON_SHIFT	9
#घोषणा USBD_STRAPS_APP_DISCON_MASK	(1 << USBD_STRAPS_APP_DISCON_SHIFT)
#घोषणा USBD_STRAPS_APP_CSRPRGSUP_SHIFT 8
#घोषणा USBD_STRAPS_APP_CSRPRGSUP_MASK	(1 << USBD_STRAPS_APP_CSRPRGSUP_SHIFT)
#घोषणा USBD_STRAPS_APP_RMTWKUP_SHIFT	6
#घोषणा USBD_STRAPS_APP_RMTWKUP_MASK	(1 << USBD_STRAPS_APP_RMTWKUP_SHIFT)
#घोषणा USBD_STRAPS_APP_RAM_IF_SHIFT	7
#घोषणा USBD_STRAPS_APP_RAM_IF_MASK	(1 << USBD_STRAPS_APP_RAM_IF_SHIFT)
#घोषणा USBD_STRAPS_APP_8BITPHY_SHIFT	2
#घोषणा USBD_STRAPS_APP_8BITPHY_MASK	(1 << USBD_STRAPS_APP_8BITPHY_SHIFT)
#घोषणा USBD_STRAPS_SPEED_SHIFT		0
#घोषणा USBD_STRAPS_SPEED_MASK		(3 << USBD_STRAPS_SPEED_SHIFT)

/* Stall control */
#घोषणा USBD_STALL_REG			0x08
#घोषणा USBD_STALL_UPDATE_SHIFT		7
#घोषणा USBD_STALL_UPDATE_MASK		(1 << USBD_STALL_UPDATE_SHIFT)
#घोषणा USBD_STALL_ENABLE_SHIFT		6
#घोषणा USBD_STALL_ENABLE_MASK		(1 << USBD_STALL_ENABLE_SHIFT)
#घोषणा USBD_STALL_EPNUM_SHIFT		0
#घोषणा USBD_STALL_EPNUM_MASK		(0xf << USBD_STALL_EPNUM_SHIFT)

/* General status */
#घोषणा USBD_STATUS_REG			0x0c
#घोषणा USBD_STATUS_SOF_SHIFT		16
#घोषणा USBD_STATUS_SOF_MASK		(0x7ff << USBD_STATUS_SOF_SHIFT)
#घोषणा USBD_STATUS_SPD_SHIFT		12
#घोषणा USBD_STATUS_SPD_MASK		(3 << USBD_STATUS_SPD_SHIFT)
#घोषणा USBD_STATUS_ALTINTF_SHIFT	8
#घोषणा USBD_STATUS_ALTINTF_MASK	(0xf << USBD_STATUS_ALTINTF_SHIFT)
#घोषणा USBD_STATUS_INTF_SHIFT		4
#घोषणा USBD_STATUS_INTF_MASK		(0xf << USBD_STATUS_INTF_SHIFT)
#घोषणा USBD_STATUS_CFG_SHIFT		0
#घोषणा USBD_STATUS_CFG_MASK		(0xf << USBD_STATUS_CFG_SHIFT)

/* Other events */
#घोषणा USBD_EVENTS_REG			0x10
#घोषणा USBD_EVENTS_USB_LINK_SHIFT	10
#घोषणा USBD_EVENTS_USB_LINK_MASK	(1 << USBD_EVENTS_USB_LINK_SHIFT)

/* IRQ status */
#घोषणा USBD_EVENT_IRQ_STATUS_REG	0x14

/* IRQ level (2 bits per IRQ event) */
#घोषणा USBD_EVENT_IRQ_CFG_HI_REG	0x18

#घोषणा USBD_EVENT_IRQ_CFG_LO_REG	0x1c

#घोषणा USBD_EVENT_IRQ_CFG_SHIFT(x)	((x & 0xf) << 1)
#घोषणा USBD_EVENT_IRQ_CFG_MASK(x)	(3 << USBD_EVENT_IRQ_CFG_SHIFT(x))
#घोषणा USBD_EVENT_IRQ_CFG_RISING(x)	(0 << USBD_EVENT_IRQ_CFG_SHIFT(x))
#घोषणा USBD_EVENT_IRQ_CFG_FALLING(x)	(1 << USBD_EVENT_IRQ_CFG_SHIFT(x))

/* IRQ mask (1=unmasked) */
#घोषणा USBD_EVENT_IRQ_MASK_REG		0x20

/* IRQ bits */
#घोषणा USBD_EVENT_IRQ_USB_LINK		10
#घोषणा USBD_EVENT_IRQ_SETCFG		9
#घोषणा USBD_EVENT_IRQ_SETINTF		8
#घोषणा USBD_EVENT_IRQ_ERRATIC_ERR	7
#घोषणा USBD_EVENT_IRQ_SET_CSRS		6
#घोषणा USBD_EVENT_IRQ_SUSPEND		5
#घोषणा USBD_EVENT_IRQ_EARLY_SUSPEND	4
#घोषणा USBD_EVENT_IRQ_SOF		3
#घोषणा USBD_EVENT_IRQ_ENUM_ON		2
#घोषणा USBD_EVENT_IRQ_SETUP		1
#घोषणा USBD_EVENT_IRQ_USB_RESET	0

/* TX FIFO partitioning */
#घोषणा USBD_TXFIFO_CONFIG_REG		0x40
#घोषणा USBD_TXFIFO_CONFIG_END_SHIFT	16
#घोषणा USBD_TXFIFO_CONFIG_END_MASK	(0xff << USBD_TXFIFO_CONFIG_END_SHIFT)
#घोषणा USBD_TXFIFO_CONFIG_START_SHIFT	0
#घोषणा USBD_TXFIFO_CONFIG_START_MASK	(0xff << USBD_TXFIFO_CONFIG_START_SHIFT)

/* RX FIFO partitioning */
#घोषणा USBD_RXFIFO_CONFIG_REG		0x44
#घोषणा USBD_RXFIFO_CONFIG_END_SHIFT	16
#घोषणा USBD_RXFIFO_CONFIG_END_MASK	(0xff << USBD_TXFIFO_CONFIG_END_SHIFT)
#घोषणा USBD_RXFIFO_CONFIG_START_SHIFT	0
#घोषणा USBD_RXFIFO_CONFIG_START_MASK	(0xff << USBD_TXFIFO_CONFIG_START_SHIFT)

/* TX FIFO/endpoपूर्णांक configuration */
#घोषणा USBD_TXFIFO_EPSIZE_REG		0x48

/* RX FIFO/endpoपूर्णांक configuration */
#घोषणा USBD_RXFIFO_EPSIZE_REG		0x4c

/* Endpoपूर्णांक<->DMA mappings */
#घोषणा USBD_EPNUM_TYPEMAP_REG		0x50
#घोषणा USBD_EPNUM_TYPEMAP_TYPE_SHIFT	8
#घोषणा USBD_EPNUM_TYPEMAP_TYPE_MASK	(0x3 << USBD_EPNUM_TYPEMAP_TYPE_SHIFT)
#घोषणा USBD_EPNUM_TYPEMAP_DMA_CH_SHIFT 0
#घोषणा USBD_EPNUM_TYPEMAP_DMA_CH_MASK	(0xf << USBD_EPNUM_TYPEMAP_DMACH_SHIFT)

/* Misc per-endpoपूर्णांक settings */
#घोषणा USBD_CSR_SETUPADDR_REG		0x80
#घोषणा USBD_CSR_SETUPADDR_DEF		0xb550

#घोषणा USBD_CSR_EP_REG(x)		(0x84 + (x) * 4)
#घोषणा USBD_CSR_EP_MAXPKT_SHIFT	19
#घोषणा USBD_CSR_EP_MAXPKT_MASK		(0x7ff << USBD_CSR_EP_MAXPKT_SHIFT)
#घोषणा USBD_CSR_EP_ALTIFACE_SHIFT	15
#घोषणा USBD_CSR_EP_ALTIFACE_MASK	(0xf << USBD_CSR_EP_ALTIFACE_SHIFT)
#घोषणा USBD_CSR_EP_IFACE_SHIFT		11
#घोषणा USBD_CSR_EP_IFACE_MASK		(0xf << USBD_CSR_EP_IFACE_SHIFT)
#घोषणा USBD_CSR_EP_CFG_SHIFT		7
#घोषणा USBD_CSR_EP_CFG_MASK		(0xf << USBD_CSR_EP_CFG_SHIFT)
#घोषणा USBD_CSR_EP_TYPE_SHIFT		5
#घोषणा USBD_CSR_EP_TYPE_MASK		(3 << USBD_CSR_EP_TYPE_SHIFT)
#घोषणा USBD_CSR_EP_सूची_SHIFT		4
#घोषणा USBD_CSR_EP_सूची_MASK		(1 << USBD_CSR_EP_सूची_SHIFT)
#घोषणा USBD_CSR_EP_LOG_SHIFT		0
#घोषणा USBD_CSR_EP_LOG_MASK		(0xf << USBD_CSR_EP_LOG_SHIFT)


/*************************************************************************
 * _REG relative to RSET_MPI
 *************************************************************************/

/* well known (hard wired) chip select */
#घोषणा MPI_CS_PCMCIA_COMMON		4
#घोषणा MPI_CS_PCMCIA_ATTR		5
#घोषणा MPI_CS_PCMCIA_IO		6

/* Chip select base रेजिस्टर */
#घोषणा MPI_CSBASE_REG(x)		(0x0 + (x) * 8)
#घोषणा MPI_CSBASE_BASE_SHIFT		13
#घोषणा MPI_CSBASE_BASE_MASK		(0x1ffff << MPI_CSBASE_BASE_SHIFT)
#घोषणा MPI_CSBASE_SIZE_SHIFT		0
#घोषणा MPI_CSBASE_SIZE_MASK		(0xf << MPI_CSBASE_SIZE_SHIFT)

#घोषणा MPI_CSBASE_SIZE_8K		0
#घोषणा MPI_CSBASE_SIZE_16K		1
#घोषणा MPI_CSBASE_SIZE_32K		2
#घोषणा MPI_CSBASE_SIZE_64K		3
#घोषणा MPI_CSBASE_SIZE_128K		4
#घोषणा MPI_CSBASE_SIZE_256K		5
#घोषणा MPI_CSBASE_SIZE_512K		6
#घोषणा MPI_CSBASE_SIZE_1M		7
#घोषणा MPI_CSBASE_SIZE_2M		8
#घोषणा MPI_CSBASE_SIZE_4M		9
#घोषणा MPI_CSBASE_SIZE_8M		10
#घोषणा MPI_CSBASE_SIZE_16M		11
#घोषणा MPI_CSBASE_SIZE_32M		12
#घोषणा MPI_CSBASE_SIZE_64M		13
#घोषणा MPI_CSBASE_SIZE_128M		14
#घोषणा MPI_CSBASE_SIZE_256M		15

/* Chip select control रेजिस्टर */
#घोषणा MPI_CSCTL_REG(x)		(0x4 + (x) * 8)
#घोषणा MPI_CSCTL_ENABLE_MASK		(1 << 0)
#घोषणा MPI_CSCTL_WAIT_SHIFT		1
#घोषणा MPI_CSCTL_WAIT_MASK		(0x7 << MPI_CSCTL_WAIT_SHIFT)
#घोषणा MPI_CSCTL_DATA16_MASK		(1 << 4)
#घोषणा MPI_CSCTL_SYNCMODE_MASK		(1 << 7)
#घोषणा MPI_CSCTL_TSIZE_MASK		(1 << 8)
#घोषणा MPI_CSCTL_ENDIANSWAP_MASK	(1 << 10)
#घोषणा MPI_CSCTL_SETUP_SHIFT		16
#घोषणा MPI_CSCTL_SETUP_MASK		(0xf << MPI_CSCTL_SETUP_SHIFT)
#घोषणा MPI_CSCTL_HOLD_SHIFT		20
#घोषणा MPI_CSCTL_HOLD_MASK		(0xf << MPI_CSCTL_HOLD_SHIFT)

/* PCI रेजिस्टरs */
#घोषणा MPI_SP0_RANGE_REG		0x100
#घोषणा MPI_SP0_REMAP_REG		0x104
#घोषणा MPI_SP0_REMAP_ENABLE_MASK	(1 << 0)
#घोषणा MPI_SP1_RANGE_REG		0x10C
#घोषणा MPI_SP1_REMAP_REG		0x110
#घोषणा MPI_SP1_REMAP_ENABLE_MASK	(1 << 0)

#घोषणा MPI_L2PCFG_REG			0x11C
#घोषणा MPI_L2PCFG_CFG_TYPE_SHIFT	0
#घोषणा MPI_L2PCFG_CFG_TYPE_MASK	(0x3 << MPI_L2PCFG_CFG_TYPE_SHIFT)
#घोषणा MPI_L2PCFG_REG_SHIFT		2
#घोषणा MPI_L2PCFG_REG_MASK		(0x3f << MPI_L2PCFG_REG_SHIFT)
#घोषणा MPI_L2PCFG_FUNC_SHIFT		8
#घोषणा MPI_L2PCFG_FUNC_MASK		(0x7 << MPI_L2PCFG_FUNC_SHIFT)
#घोषणा MPI_L2PCFG_DEVNUM_SHIFT		11
#घोषणा MPI_L2PCFG_DEVNUM_MASK		(0x1f << MPI_L2PCFG_DEVNUM_SHIFT)
#घोषणा MPI_L2PCFG_CFG_USEREG_MASK	(1 << 30)
#घोषणा MPI_L2PCFG_CFG_SEL_MASK		(1 << 31)

#घोषणा MPI_L2PMEMRANGE1_REG		0x120
#घोषणा MPI_L2PMEMBASE1_REG		0x124
#घोषणा MPI_L2PMEMREMAP1_REG		0x128
#घोषणा MPI_L2PMEMRANGE2_REG		0x12C
#घोषणा MPI_L2PMEMBASE2_REG		0x130
#घोषणा MPI_L2PMEMREMAP2_REG		0x134
#घोषणा MPI_L2PIORANGE_REG		0x138
#घोषणा MPI_L2PIOBASE_REG		0x13C
#घोषणा MPI_L2PIOREMAP_REG		0x140
#घोषणा MPI_L2P_BASE_MASK		(0xffff8000)
#घोषणा MPI_L2PREMAP_ENABLED_MASK	(1 << 0)
#घोषणा MPI_L2PREMAP_IS_CARDBUS_MASK	(1 << 2)

#घोषणा MPI_PCIMODESEL_REG		0x144
#घोषणा MPI_PCIMODESEL_BAR1_NOSWAP_MASK (1 << 0)
#घोषणा MPI_PCIMODESEL_BAR2_NOSWAP_MASK (1 << 1)
#घोषणा MPI_PCIMODESEL_EXT_ARB_MASK	(1 << 2)
#घोषणा MPI_PCIMODESEL_PREFETCH_SHIFT	4
#घोषणा MPI_PCIMODESEL_PREFETCH_MASK	(0xf << MPI_PCIMODESEL_PREFETCH_SHIFT)

#घोषणा MPI_LOCBUSCTL_REG		0x14C
#घोषणा MPI_LOCBUSCTL_EN_PCI_GPIO_MASK	(1 << 0)
#घोषणा MPI_LOCBUSCTL_U2P_NOSWAP_MASK	(1 << 1)

#घोषणा MPI_LOCINT_REG			0x150
#घोषणा MPI_LOCINT_MASK(x)		(1 << (x + 16))
#घोषणा MPI_LOCINT_STAT(x)		(1 << (x))
#घोषणा MPI_LOCINT_सूची_FAILED		6
#घोषणा MPI_LOCINT_EXT_PCI_INT		7
#घोषणा MPI_LOCINT_SERR			8
#घोषणा MPI_LOCINT_CSERR		9

#घोषणा MPI_PCICFGCTL_REG		0x178
#घोषणा MPI_PCICFGCTL_CFGADDR_SHIFT	2
#घोषणा MPI_PCICFGCTL_CFGADDR_MASK	(0x1f << MPI_PCICFGCTL_CFGADDR_SHIFT)
#घोषणा MPI_PCICFGCTL_WRITEEN_MASK	(1 << 7)

#घोषणा MPI_PCICFGDATA_REG		0x17C

/* PCI host bridge custom रेजिस्टर */
#घोषणा BCMPCI_REG_TIMERS		0x40
#घोषणा REG_TIMER_TRDY_SHIFT		0
#घोषणा REG_TIMER_TRDY_MASK		(0xff << REG_TIMER_TRDY_SHIFT)
#घोषणा REG_TIMER_RETRY_SHIFT		8
#घोषणा REG_TIMER_RETRY_MASK		(0xff << REG_TIMER_RETRY_SHIFT)


/*************************************************************************
 * _REG relative to RSET_PCMCIA
 *************************************************************************/

#घोषणा PCMCIA_C1_REG			0x0
#घोषणा PCMCIA_C1_CD1_MASK		(1 << 0)
#घोषणा PCMCIA_C1_CD2_MASK		(1 << 1)
#घोषणा PCMCIA_C1_VS1_MASK		(1 << 2)
#घोषणा PCMCIA_C1_VS2_MASK		(1 << 3)
#घोषणा PCMCIA_C1_VS1OE_MASK		(1 << 6)
#घोषणा PCMCIA_C1_VS2OE_MASK		(1 << 7)
#घोषणा PCMCIA_C1_CBIDSEL_SHIFT		(8)
#घोषणा PCMCIA_C1_CBIDSEL_MASK		(0x1f << PCMCIA_C1_CBIDSEL_SHIFT)
#घोषणा PCMCIA_C1_EN_PCMCIA_GPIO_MASK	(1 << 13)
#घोषणा PCMCIA_C1_EN_PCMCIA_MASK	(1 << 14)
#घोषणा PCMCIA_C1_EN_CARDBUS_MASK	(1 << 15)
#घोषणा PCMCIA_C1_RESET_MASK		(1 << 18)

#घोषणा PCMCIA_C2_REG			0x8
#घोषणा PCMCIA_C2_DATA16_MASK		(1 << 0)
#घोषणा PCMCIA_C2_BYTESWAP_MASK		(1 << 1)
#घोषणा PCMCIA_C2_RWCOUNT_SHIFT		2
#घोषणा PCMCIA_C2_RWCOUNT_MASK		(0x3f << PCMCIA_C2_RWCOUNT_SHIFT)
#घोषणा PCMCIA_C2_INACTIVE_SHIFT	8
#घोषणा PCMCIA_C2_INACTIVE_MASK		(0x3f << PCMCIA_C2_INACTIVE_SHIFT)
#घोषणा PCMCIA_C2_SETUP_SHIFT		16
#घोषणा PCMCIA_C2_SETUP_MASK		(0x3f << PCMCIA_C2_SETUP_SHIFT)
#घोषणा PCMCIA_C2_HOLD_SHIFT		24
#घोषणा PCMCIA_C2_HOLD_MASK		(0x3f << PCMCIA_C2_HOLD_SHIFT)


/*************************************************************************
 * _REG relative to RSET_SDRAM
 *************************************************************************/

#घोषणा SDRAM_CFG_REG			0x0
#घोषणा SDRAM_CFG_ROW_SHIFT		4
#घोषणा SDRAM_CFG_ROW_MASK		(0x3 << SDRAM_CFG_ROW_SHIFT)
#घोषणा SDRAM_CFG_COL_SHIFT		6
#घोषणा SDRAM_CFG_COL_MASK		(0x3 << SDRAM_CFG_COL_SHIFT)
#घोषणा SDRAM_CFG_32B_SHIFT		10
#घोषणा SDRAM_CFG_32B_MASK		(1 << SDRAM_CFG_32B_SHIFT)
#घोषणा SDRAM_CFG_BANK_SHIFT		13
#घोषणा SDRAM_CFG_BANK_MASK		(1 << SDRAM_CFG_BANK_SHIFT)

#घोषणा SDRAM_MBASE_REG			0xc

#घोषणा SDRAM_PRIO_REG			0x2C
#घोषणा SDRAM_PRIO_MIPS_SHIFT		29
#घोषणा SDRAM_PRIO_MIPS_MASK		(1 << SDRAM_PRIO_MIPS_SHIFT)
#घोषणा SDRAM_PRIO_ADSL_SHIFT		30
#घोषणा SDRAM_PRIO_ADSL_MASK		(1 << SDRAM_PRIO_ADSL_SHIFT)
#घोषणा SDRAM_PRIO_EN_SHIFT		31
#घोषणा SDRAM_PRIO_EN_MASK		(1 << SDRAM_PRIO_EN_SHIFT)


/*************************************************************************
 * _REG relative to RSET_MEMC
 *************************************************************************/

#घोषणा MEMC_CFG_REG			0x4
#घोषणा MEMC_CFG_32B_SHIFT		1
#घोषणा MEMC_CFG_32B_MASK		(1 << MEMC_CFG_32B_SHIFT)
#घोषणा MEMC_CFG_COL_SHIFT		3
#घोषणा MEMC_CFG_COL_MASK		(0x3 << MEMC_CFG_COL_SHIFT)
#घोषणा MEMC_CFG_ROW_SHIFT		6
#घोषणा MEMC_CFG_ROW_MASK		(0x3 << MEMC_CFG_ROW_SHIFT)


/*************************************************************************
 * _REG relative to RSET_DDR
 *************************************************************************/

#घोषणा DDR_CSEND_REG			0x8

#घोषणा DDR_DMIPSPLLCFG_REG		0x18
#घोषणा DMIPSPLLCFG_M1_SHIFT		0
#घोषणा DMIPSPLLCFG_M1_MASK		(0xff << DMIPSPLLCFG_M1_SHIFT)
#घोषणा DMIPSPLLCFG_N1_SHIFT		23
#घोषणा DMIPSPLLCFG_N1_MASK		(0x3f << DMIPSPLLCFG_N1_SHIFT)
#घोषणा DMIPSPLLCFG_N2_SHIFT		29
#घोषणा DMIPSPLLCFG_N2_MASK		(0x7 << DMIPSPLLCFG_N2_SHIFT)

#घोषणा DDR_DMIPSPLLCFG_6368_REG	0x20
#घोषणा DMIPSPLLCFG_6368_P1_SHIFT	0
#घोषणा DMIPSPLLCFG_6368_P1_MASK	(0xf << DMIPSPLLCFG_6368_P1_SHIFT)
#घोषणा DMIPSPLLCFG_6368_P2_SHIFT	4
#घोषणा DMIPSPLLCFG_6368_P2_MASK	(0xf << DMIPSPLLCFG_6368_P2_SHIFT)
#घोषणा DMIPSPLLCFG_6368_NDIV_SHIFT	16
#घोषणा DMIPSPLLCFG_6368_NDIV_MASK	(0x1ff << DMIPSPLLCFG_6368_NDIV_SHIFT)

#घोषणा DDR_DMIPSPLLDIV_6368_REG	0x24
#घोषणा DMIPSPLLDIV_6368_MDIV_SHIFT	0
#घोषणा DMIPSPLLDIV_6368_MDIV_MASK	(0xff << DMIPSPLLDIV_6368_MDIV_SHIFT)


/*************************************************************************
 * _REG relative to RSET_M2M
 *************************************************************************/

#घोषणा M2M_RX				0
#घोषणा M2M_TX				1

#घोषणा M2M_SRC_REG(x)			((x) * 0x40 + 0x00)
#घोषणा M2M_DST_REG(x)			((x) * 0x40 + 0x04)
#घोषणा M2M_SIZE_REG(x)			((x) * 0x40 + 0x08)

#घोषणा M2M_CTRL_REG(x)			((x) * 0x40 + 0x0c)
#घोषणा M2M_CTRL_ENABLE_MASK		(1 << 0)
#घोषणा M2M_CTRL_IRQEN_MASK		(1 << 1)
#घोषणा M2M_CTRL_ERROR_CLR_MASK		(1 << 6)
#घोषणा M2M_CTRL_DONE_CLR_MASK		(1 << 7)
#घोषणा M2M_CTRL_NOINC_MASK		(1 << 8)
#घोषणा M2M_CTRL_PCMCIASWAP_MASK	(1 << 9)
#घोषणा M2M_CTRL_SWAPBYTE_MASK		(1 << 10)
#घोषणा M2M_CTRL_ENDIAN_MASK		(1 << 11)

#घोषणा M2M_STAT_REG(x)			((x) * 0x40 + 0x10)
#घोषणा M2M_STAT_DONE			(1 << 0)
#घोषणा M2M_STAT_ERROR			(1 << 1)

#घोषणा M2M_SRCID_REG(x)		((x) * 0x40 + 0x14)
#घोषणा M2M_DSTID_REG(x)		((x) * 0x40 + 0x18)

/*************************************************************************
 * _REG relative to RSET_SPI
 *************************************************************************/

/* BCM 6338/6348 SPI core */
#घोषणा SPI_6348_CMD			0x00	/* 16-bits रेजिस्टर */
#घोषणा SPI_6348_INT_STATUS		0x02
#घोषणा SPI_6348_INT_MASK_ST		0x03
#घोषणा SPI_6348_INT_MASK		0x04
#घोषणा SPI_6348_ST			0x05
#घोषणा SPI_6348_CLK_CFG		0x06
#घोषणा SPI_6348_FILL_BYTE		0x07
#घोषणा SPI_6348_MSG_TAIL		0x09
#घोषणा SPI_6348_RX_TAIL		0x0b
#घोषणा SPI_6348_MSG_CTL		0x40	/* 8-bits रेजिस्टर */
#घोषणा SPI_6348_MSG_CTL_WIDTH		8
#घोषणा SPI_6348_MSG_DATA		0x41
#घोषणा SPI_6348_MSG_DATA_SIZE		0x3f
#घोषणा SPI_6348_RX_DATA		0x80
#घोषणा SPI_6348_RX_DATA_SIZE		0x3f

/* BCM 3368/6358/6262/6368 SPI core */
#घोषणा SPI_6358_MSG_CTL		0x00	/* 16-bits रेजिस्टर */
#घोषणा SPI_6358_MSG_CTL_WIDTH		16
#घोषणा SPI_6358_MSG_DATA		0x02
#घोषणा SPI_6358_MSG_DATA_SIZE		0x21e
#घोषणा SPI_6358_RX_DATA		0x400
#घोषणा SPI_6358_RX_DATA_SIZE		0x220
#घोषणा SPI_6358_CMD			0x700	/* 16-bits रेजिस्टर */
#घोषणा SPI_6358_INT_STATUS		0x702
#घोषणा SPI_6358_INT_MASK_ST		0x703
#घोषणा SPI_6358_INT_MASK		0x704
#घोषणा SPI_6358_ST			0x705
#घोषणा SPI_6358_CLK_CFG		0x706
#घोषणा SPI_6358_FILL_BYTE		0x707
#घोषणा SPI_6358_MSG_TAIL		0x709
#घोषणा SPI_6358_RX_TAIL		0x70B

/* Shared SPI definitions */

/* Message configuration */
#घोषणा SPI_FD_RW			0x00
#घोषणा SPI_HD_W			0x01
#घोषणा SPI_HD_R			0x02
#घोषणा SPI_BYTE_CNT_SHIFT		0
#घोषणा SPI_6348_MSG_TYPE_SHIFT		6
#घोषणा SPI_6358_MSG_TYPE_SHIFT		14

/* Command */
#घोषणा SPI_CMD_NOOP			0x00
#घोषणा SPI_CMD_SOFT_RESET		0x01
#घोषणा SPI_CMD_HARD_RESET		0x02
#घोषणा SPI_CMD_START_IMMEDIATE		0x03
#घोषणा SPI_CMD_COMMAND_SHIFT		0
#घोषणा SPI_CMD_COMMAND_MASK		0x000f
#घोषणा SPI_CMD_DEVICE_ID_SHIFT		4
#घोषणा SPI_CMD_PREPEND_BYTE_CNT_SHIFT	8
#घोषणा SPI_CMD_ONE_BYTE_SHIFT		11
#घोषणा SPI_CMD_ONE_WIRE_SHIFT		12
#घोषणा SPI_DEV_ID_0			0
#घोषणा SPI_DEV_ID_1			1
#घोषणा SPI_DEV_ID_2			2
#घोषणा SPI_DEV_ID_3			3

/* Interrupt mask */
#घोषणा SPI_INTR_CMD_DONE		0x01
#घोषणा SPI_INTR_RX_OVERFLOW		0x02
#घोषणा SPI_INTR_TX_UNDERFLOW		0x04
#घोषणा SPI_INTR_TX_OVERFLOW		0x08
#घोषणा SPI_INTR_RX_UNDERFLOW		0x10
#घोषणा SPI_INTR_CLEAR_ALL		0x1f

/* Status */
#घोषणा SPI_RX_EMPTY			0x02
#घोषणा SPI_CMD_BUSY			0x04
#घोषणा SPI_SERIAL_BUSY			0x08

/* Clock configuration */
#घोषणा SPI_CLK_20MHZ			0x00
#घोषणा SPI_CLK_0_391MHZ		0x01
#घोषणा SPI_CLK_0_781MHZ		0x02 /* शेष */
#घोषणा SPI_CLK_1_563MHZ		0x03
#घोषणा SPI_CLK_3_125MHZ		0x04
#घोषणा SPI_CLK_6_250MHZ		0x05
#घोषणा SPI_CLK_12_50MHZ		0x06
#घोषणा SPI_CLK_MASK			0x07
#घोषणा SPI_SSOFFTIME_MASK		0x38
#घोषणा SPI_SSOFFTIME_SHIFT		3
#घोषणा SPI_BYTE_SWAP			0x80

/*************************************************************************
 * _REG relative to RSET_MISC
 *************************************************************************/
#घोषणा MISC_SERDES_CTRL_6328_REG	0x0
#घोषणा MISC_SERDES_CTRL_6362_REG	0x4
#घोषणा SERDES_PCIE_EN			(1 << 0)
#घोषणा SERDES_PCIE_EXD_EN		(1 << 15)

#घोषणा MISC_STRAPBUS_6362_REG		0x14
#घोषणा STRAPBUS_6362_FCVO_SHIFT	1
#घोषणा STRAPBUS_6362_HSSPI_CLK_FAST	(1 << 13)
#घोषणा STRAPBUS_6362_FCVO_MASK		(0x1f << STRAPBUS_6362_FCVO_SHIFT)
#घोषणा STRAPBUS_6362_BOOT_SEL_SERIAL	(1 << 15)
#घोषणा STRAPBUS_6362_BOOT_SEL_न_अंकD	(0 << 15)

#घोषणा MISC_STRAPBUS_6328_REG		0x240
#घोषणा STRAPBUS_6328_FCVO_SHIFT	7
#घोषणा STRAPBUS_6328_FCVO_MASK		(0x1f << STRAPBUS_6328_FCVO_SHIFT)
#घोषणा STRAPBUS_6328_BOOT_SEL_SERIAL	(1 << 18)
#घोषणा STRAPBUS_6328_BOOT_SEL_न_अंकD	(0 << 18)

/*************************************************************************
 * _REG relative to RSET_PCIE
 *************************************************************************/

#घोषणा PCIE_CONFIG2_REG		0x408
#घोषणा CONFIG2_BAR1_SIZE_EN		1
#घोषणा CONFIG2_BAR1_SIZE_MASK		0xf

#घोषणा PCIE_IDVAL3_REG			0x43c
#घोषणा IDVAL3_CLASS_CODE_MASK		0xffffff
#घोषणा IDVAL3_SUBCLASS_SHIFT		8
#घोषणा IDVAL3_CLASS_SHIFT		16

#घोषणा PCIE_DLSTATUS_REG		0x1048
#घोषणा DLSTATUS_PHYLINKUP		(1 << 13)

#घोषणा PCIE_BRIDGE_OPT1_REG		0x2820
#घोषणा OPT1_RD_BE_OPT_EN		(1 << 7)
#घोषणा OPT1_RD_REPLY_BE_FIX_EN		(1 << 9)
#घोषणा OPT1_PCIE_BRIDGE_HOLE_DET_EN	(1 << 11)
#घोषणा OPT1_L1_INT_STATUS_MASK_POL	(1 << 12)

#घोषणा PCIE_BRIDGE_OPT2_REG		0x2824
#घोषणा OPT2_UBUS_UR_DECODE_DIS		(1 << 2)
#घोषणा OPT2_TX_CREDIT_CHK_EN		(1 << 4)
#घोषणा OPT2_CFG_TYPE1_BD_SEL		(1 << 7)
#घोषणा OPT2_CFG_TYPE1_BUS_NO_SHIFT	16
#घोषणा OPT2_CFG_TYPE1_BUS_NO_MASK	(0xff << OPT2_CFG_TYPE1_BUS_NO_SHIFT)

#घोषणा PCIE_BRIDGE_BAR0_BASEMASK_REG	0x2828
#घोषणा PCIE_BRIDGE_BAR1_BASEMASK_REG	0x2830
#घोषणा BASEMASK_REMAP_EN		(1 << 0)
#घोषणा BASEMASK_SWAP_EN		(1 << 1)
#घोषणा BASEMASK_MASK_SHIFT		4
#घोषणा BASEMASK_MASK_MASK		(0xfff << BASEMASK_MASK_SHIFT)
#घोषणा BASEMASK_BASE_SHIFT		20
#घोषणा BASEMASK_BASE_MASK		(0xfff << BASEMASK_BASE_SHIFT)

#घोषणा PCIE_BRIDGE_BAR0_REBASE_ADDR_REG 0x282c
#घोषणा PCIE_BRIDGE_BAR1_REBASE_ADDR_REG 0x2834
#घोषणा REBASE_ADDR_BASE_SHIFT		20
#घोषणा REBASE_ADDR_BASE_MASK		(0xfff << REBASE_ADDR_BASE_SHIFT)

#घोषणा PCIE_BRIDGE_RC_INT_MASK_REG	0x2854
#घोषणा PCIE_RC_INT_A			(1 << 0)
#घोषणा PCIE_RC_INT_B			(1 << 1)
#घोषणा PCIE_RC_INT_C			(1 << 2)
#घोषणा PCIE_RC_INT_D			(1 << 3)

#घोषणा PCIE_DEVICE_OFFSET		0x8000

/*************************************************************************
 * _REG relative to RSET_OTP
 *************************************************************************/

#घोषणा OTP_USER_BITS_6328_REG(i)	(0x20 + (i) * 4)
#घोषणा   OTP_6328_REG3_TP1_DISABLED	BIT(9)

#पूर्ण_अगर /* BCM63XX_REGS_H_ */
