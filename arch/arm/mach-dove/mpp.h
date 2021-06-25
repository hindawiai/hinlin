<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ARCH_DOVE_MPP_CODED_H
#घोषणा __ARCH_DOVE_MPP_CODED_H

#घोषणा MPP(_num, _sel, _in, _out) ( \
	/* MPP number */		((_num) & 0xff) | \
	/* MPP select value */		(((_sel) & 0xf) << 8) | \
	/* may be input संकेत */	((!!(_in)) << 12) | \
	/* may be output संकेत */	((!!(_out)) << 13))

#घोषणा MPP0_GPIO0		MPP(0, 0x0, 1, 1)
#घोषणा MPP0_UA2_RTSn		MPP(0, 0x2, 0, 0)
#घोषणा MPP0_SDIO0_CD		MPP(0, 0x3, 0, 0)
#घोषणा MPP0_LCD0_PWM		MPP(0, 0xf, 0, 0)

#घोषणा MPP1_GPIO1		MPP(1, 0x0, 1, 1)
#घोषणा MPP1_UA2_CTSn		MPP(1, 0x2, 0, 0)
#घोषणा MPP1_SDIO0_WP		MPP(1, 0x3, 0, 0)
#घोषणा MPP1_LCD1_PWM		MPP(1, 0xf, 0, 0)

#घोषणा MPP2_GPIO2		MPP(2, 0x0, 1, 1)
#घोषणा MPP2_SATA_PRESENT	MPP(2, 0x1, 0, 0)
#घोषणा MPP2_UA2_TXD		MPP(2, 0x2, 0, 0)
#घोषणा MPP2_SDIO0_BUS_POWER	MPP(2, 0x3, 0, 0)
#घोषणा MPP2_UA_RTSn1		MPP(2, 0x4, 0, 0)

#घोषणा MPP3_GPIO3		MPP(3, 0x0, 1, 1)
#घोषणा MPP3_SATA_ACT		MPP(3, 0x1, 0, 0)
#घोषणा MPP3_UA2_RXD		MPP(3, 0x2, 0, 0)
#घोषणा MPP3_SDIO0_LED_CTRL	MPP(3, 0x3, 0, 0)
#घोषणा MPP3_UA_CTSn1		MPP(3, 0x4, 0, 0)
#घोषणा MPP3_SPI_LCD_CS1	MPP(3, 0xf, 0, 0)

#घोषणा MPP4_GPIO4		MPP(4, 0x0, 1, 1)
#घोषणा MPP4_UA3_RTSn		MPP(4, 0x2, 0, 0)
#घोषणा MPP4_SDIO1_CD		MPP(4, 0x3, 0, 0)
#घोषणा MPP4_SPI_1_MISO		MPP(4, 0x4, 0, 0)

#घोषणा MPP5_GPIO5		MPP(5, 0x0, 1, 1)
#घोषणा MPP5_UA3_CTSn		MPP(5, 0x2, 0, 0)
#घोषणा MPP5_SDIO1_WP		MPP(5, 0x3, 0, 0)
#घोषणा MPP5_SPI_1_CS		MPP(5, 0x4, 0, 0)

#घोषणा MPP6_GPIO6		MPP(6, 0x0, 1, 1)
#घोषणा MPP6_UA3_TXD		MPP(6, 0x2, 0, 0)
#घोषणा MPP6_SDIO1_BUS_POWER	MPP(6, 0x3, 0, 0)
#घोषणा MPP6_SPI_1_MOSI		MPP(6, 0x4, 0, 0)

#घोषणा MPP7_GPIO7		MPP(7, 0x0, 1, 1)
#घोषणा MPP7_UA3_RXD		MPP(7, 0x2, 0, 0)
#घोषणा MPP7_SDIO1_LED_CTRL	MPP(7, 0x3, 0, 0)
#घोषणा MPP7_SPI_1_SCK		MPP(7, 0x4, 0, 0)

#घोषणा MPP8_GPIO8		MPP(8, 0x0, 1, 1)
#घोषणा MPP8_WD_RST_OUT		MPP(8, 0x1, 0, 0)

#घोषणा MPP9_GPIO9		MPP(9, 0x0, 1, 1)
#घोषणा MPP9_PEX1_CLKREQn	MPP(9, 0x5, 0, 0)

#घोषणा MPP10_GPIO10		MPP(10, 0x0, 1, 1)
#घोषणा MPP10_SSP_SCLK		MPP(10, 0x5, 0, 0)

#घोषणा MPP11_GPIO11		MPP(11, 0x0, 1, 1)
#घोषणा MPP11_SATA_PRESENT	MPP(11, 0x1, 0, 0)
#घोषणा MPP11_SATA_ACT		MPP(11, 0x2, 0, 0)
#घोषणा MPP11_SDIO0_LED_CTRL	MPP(11, 0x3, 0, 0)
#घोषणा MPP11_SDIO1_LED_CTRL	MPP(11, 0x4, 0, 0)
#घोषणा MPP11_PEX0_CLKREQn	MPP(11, 0x5, 0, 0)

#घोषणा MPP12_GPIO12		MPP(12, 0x0, 1, 1)
#घोषणा MPP12_SATA_ACT		MPP(12, 0x1, 0, 0)
#घोषणा MPP12_UA2_RTSn		MPP(12, 0x2, 0, 0)
#घोषणा MPP12_AD0_I2S_EXT_MCLK	MPP(12, 0x3, 0, 0)
#घोषणा MPP12_SDIO1_CD		MPP(12, 0x4, 0, 0)

#घोषणा MPP13_GPIO13		MPP(13, 0x0, 1, 1)
#घोषणा MPP13_UA2_CTSn		MPP(13, 0x2, 0, 0)
#घोषणा MPP13_AD1_I2S_EXT_MCLK	MPP(13, 0x3, 0, 0)
#घोषणा MPP13_SDIO1WP		MPP(13, 0x4, 0, 0)
#घोषणा MPP13_SSP_EXTCLK	MPP(13, 0x5, 0, 0)

#घोषणा MPP14_GPIO14		MPP(14, 0x0, 1, 1)
#घोषणा MPP14_UA2_TXD		MPP(14, 0x2, 0, 0)
#घोषणा MPP14_SDIO1_BUS_POWER	MPP(14, 0x4, 0, 0)
#घोषणा MPP14_SSP_RXD		MPP(14, 0x5, 0, 0)

#घोषणा MPP15_GPIO15		MPP(15, 0x0, 1, 1)
#घोषणा MPP15_UA2_RXD		MPP(15, 0x2, 0, 0)
#घोषणा MPP15_SDIO1_LED_CTRL	MPP(15, 0x4, 0, 0)
#घोषणा MPP15_SSP_SFRM		MPP(15, 0x5, 0, 0)

#घोषणा MPP16_GPIO16		MPP(16, 0x0, 1, 1)
#घोषणा MPP16_UA3_RTSn		MPP(16, 0x2, 0, 0)
#घोषणा MPP16_SDIO0_CD		MPP(16, 0x3, 0, 0)
#घोषणा MPP16_SPI_LCD_CS1	MPP(16, 0x4, 0, 0)
#घोषणा MPP16_AC97_SDATA_IN1	MPP(16, 0x5, 0, 0)

#घोषणा MPP17_GPIO17		MPP(17, 0x0, 1, 1)
#घोषणा MPP17_AC97_SYSCLK_OUT	MPP(17, 0x1, 0, 0)
#घोषणा MPP17_UA3_CTSn		MPP(17, 0x2, 0, 0)
#घोषणा MPP17_SDIO0_WP		MPP(17, 0x3, 0, 0)
#घोषणा MPP17_TW_SDA2		MPP(17, 0x4, 0, 0)
#घोषणा MPP17_AC97_SDATA_IN2	MPP(17, 0x5, 0, 0)

#घोषणा MPP18_GPIO18		MPP(18, 0x0, 1, 1)
#घोषणा MPP18_UA3_TXD		MPP(18, 0x2, 0, 0)
#घोषणा MPP18_SDIO0_BUS_POWER	MPP(18, 0x3, 0, 0)
#घोषणा MPP18_LCD0_PWM		MPP(18, 0x4, 0, 0)
#घोषणा MPP18_AC_SDATA_IN3	MPP(18, 0x5, 0, 0)

#घोषणा MPP19_GPIO19		MPP(19, 0x0, 1, 1)
#घोषणा MPP19_UA3_RXD		MPP(19, 0x2, 0, 0)
#घोषणा MPP19_SDIO0_LED_CTRL	MPP(19, 0x3, 0, 0)
#घोषणा MPP19_TW_SCK2		MPP(19, 0x4, 0, 0)

#घोषणा MPP20_GPIO20		MPP(20, 0x0, 1, 1)
#घोषणा MPP20_AC97_SYSCLK_OUT	MPP(20, 0x1, 0, 0)
#घोषणा MPP20_SPI_LCD_MISO	MPP(20, 0x2, 0, 0)
#घोषणा MPP20_SDIO1_CD		MPP(20, 0x3, 0, 0)
#घोषणा MPP20_SDIO0_CD		MPP(20, 0x5, 0, 0)
#घोषणा MPP20_SPI_1_MISO	MPP(20, 0x6, 0, 0)

#घोषणा MPP21_GPIO21		MPP(21, 0x0, 1, 1)
#घोषणा MPP21_UA1_RTSn		MPP(21, 0x1, 0, 0)
#घोषणा MPP21_SPI_LCD_CS0	MPP(21, 0x2, 0, 0)
#घोषणा MPP21_SDIO1_WP		MPP(21, 0x3, 0, 0)
#घोषणा MPP21_SSP_SFRM		MPP(21, 0x4, 0, 0)
#घोषणा MPP21_SDIO0_WP		MPP(21, 0x5, 0, 0)
#घोषणा MPP21_SPI_1_CS		MPP(21, 0x6, 0, 0)

#घोषणा MPP22_GPIO22		MPP(22, 0x0, 1, 1)
#घोषणा MPP22_UA1_CTSn		MPP(22, 0x1, 0, 0)
#घोषणा MPP22_SPI_LCD_MOSI	MPP(22, 0x2, 0, 0)
#घोषणा MPP22_SDIO1_BUS_POWER	MPP(22, 0x3, 0, 0)
#घोषणा MPP22_SSP_TXD		MPP(22, 0x4, 0, 0)
#घोषणा MPP22_SDIO0_BUS_POWER	MPP(22, 0x5, 0, 0)
#घोषणा MPP22_SPI_1_MOSI	MPP(22, 0x6, 0, 0)

#घोषणा MPP23_GPIO23		MPP(23, 0x0, 1, 1)
#घोषणा MPP23_SPI_LCD_SCK	MPP(23, 0x2, 0, 0)
#घोषणा MPP23_SDIO1_LED_CTRL	MPP(23, 0x3, 0, 0)
#घोषणा MPP23_SSP_SCLK		MPP(23, 0x4, 0, 0)
#घोषणा MPP23_SDIO0_LED_CTRL	MPP(23, 0x5, 0, 0)
#घोषणा MPP23_SPI_1_SCK		MPP(23, 0x6, 0, 0)

#घोषणा MPP_MAX			23

#घोषणा MPP_GRP(_grp, _mode)	MPP((_grp), (_mode), 0, 0)

/* क्रम MPP groups _num is a group index */
क्रमागत करोve_mpp_grp_idx अणु
	MPP_24_39 = 2,
	MPP_40_45 = 0,
	MPP_46_51 = 1,
	MPP_58_61 = 5,
	MPP_62_63 = 4,
	MPP_GRP_MAX = 5,
पूर्ण;

#घोषणा MPP_GRP_24_39_GPIO		MPP_GRP(MPP_24_39, 0x1)
#घोषणा MPP_GRP_24_39_CAM		MPP_GRP(MPP_24_39, 0x0)

#घोषणा MPP_GRP_40_45_GPIO		MPP_GRP(MPP_40_45, 0x1)
#घोषणा MPP_GRP_40_45_SD0		MPP_GRP(MPP_40_45, 0x0)

#घोषणा MPP_GRP_46_51_GPIO		MPP_GRP(MPP_46_51, 0x1)
#घोषणा MPP_GRP_46_51_SD1		MPP_GRP(MPP_46_51, 0x0)

#घोषणा MPP_GRP_58_61_GPIO		MPP_GRP(MPP_58_61, 0x1)
#घोषणा MPP_GRP_58_61_SPI		MPP_GRP(MPP_58_61, 0x0)

#घोषणा MPP_GRP_62_63_GPIO		MPP_GRP(MPP_62_63, 0x1)
#घोषणा MPP_GRP_62_63_UA1		MPP_GRP(MPP_62_63, 0x0)

/* The MPP[64:71] control dअगरfers from other groups */
#घोषणा MPP_GRP_NFC_64_71_GPO		0x1
#घोषणा MPP_GRP_NFC_64_71_NFC		0x0

/*
 * The MPP[52:57] functionality is encoded by 4 bits in dअगरferent
 * रेजिस्टरs. The _num field in this हाल encodes those bits in
 * correspodence with Table 135 of 88AP510 Functional specअगरication
 */
#घोषणा MPP_GRP_AU1_52_57_AU1		0x0
#घोषणा MPP_GRP_AU1_52_57_AU1_GPIO57	0x2
#घोषणा MPP_GRP_AU1_52_57_GPIO		0xa
#घोषणा MPP_GRP_AU1_52_57_TW_GPIO	0xb
#घोषणा MPP_GRP_AU1_52_57_AU1_SSP	0xc
#घोषणा MPP_GRP_AU1_52_57_SSP_GPIO	0xe
#घोषणा MPP_GRP_AU1_52_57_SSP_TW	0xf

व्योम करोve_mpp_conf(अचिन्हित पूर्णांक *mpp_list,
		   अचिन्हित पूर्णांक *mpp_grp_list,
		   अचिन्हित पूर्णांक grp_au1_52_57,
		   अचिन्हित पूर्णांक grp_nfc_64_71);

#पूर्ण_अगर	/* __ARCH_DOVE_MPP_CODED_H */
