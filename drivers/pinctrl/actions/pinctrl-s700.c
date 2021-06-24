<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Actions Semi Owl S700 Pinctrl driver
 *
 * Copyright (c) 2014 Actions Semi Inc.
 * Author: David Liu <liuwei@actions-semi.com>
 *
 * Author: Pathiban Nallathambi <pn@denx.de>
 * Author: Saravanan Sekar <sravanhome@gmail.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश "pinctrl-owl.h"

/* Pinctrl रेजिस्टरs offset */
#घोषणा MFCTL0			(0x0040)
#घोषणा MFCTL1			(0x0044)
#घोषणा MFCTL2			(0x0048)
#घोषणा MFCTL3			(0x004C)
#घोषणा PAD_PULLCTL0		(0x0060)
#घोषणा PAD_PULLCTL1		(0x0064)
#घोषणा PAD_PULLCTL2		(0x0068)
#घोषणा PAD_ST0			(0x006C)
#घोषणा PAD_ST1			(0x0070)
#घोषणा PAD_CTL			(0x0074)
#घोषणा PAD_DRV0		(0x0080)
#घोषणा PAD_DRV1		(0x0084)
#घोषणा PAD_DRV2		(0x0088)

/*
 * Most pins affected by the pinmux can also be GPIOs. Define these first.
 * These must match how the GPIO driver names/numbers its pins.
 */
#घोषणा _GPIOA(offset)		(offset)
#घोषणा _GPIOB(offset)		(32 + (offset))
#घोषणा _GPIOC(offset)		(64 + (offset))
#घोषणा _GPIOD(offset)		(96 + (offset))
#घोषणा _GPIOE(offset)		(128 + (offset))

/* All non-GPIO pins follow */
#घोषणा NUM_GPIOS		(_GPIOE(7) + 1)
#घोषणा _PIN(offset)		(NUM_GPIOS + (offset))

/* Ethernet MAC */
#घोषणा ETH_TXD0		_GPIOA(14)
#घोषणा ETH_TXD1		_GPIOA(15)
#घोषणा ETH_TXD2		_GPIOE(4)
#घोषणा ETH_TXD3		_GPIOE(5)
#घोषणा ETH_TXEN		_GPIOA(16)
#घोषणा ETH_RXER		_GPIOA(17)
#घोषणा ETH_CRS_DV		_GPIOA(18)
#घोषणा ETH_RXD1		_GPIOA(19)
#घोषणा ETH_RXD0		_GPIOA(20)
#घोषणा ETH_RXD2		_GPIOE(6)
#घोषणा ETH_RXD3		_GPIOE(7)
#घोषणा ETH_REF_CLK		_GPIOA(21)
#घोषणा ETH_MDC			_GPIOA(22)
#घोषणा ETH_MDIO		_GPIOA(23)

/* SIRQ */
#घोषणा SIRQ0			_GPIOA(24)
#घोषणा SIRQ1			_GPIOA(25)
#घोषणा SIRQ2			_GPIOA(26)

/* I2S */
#घोषणा I2S_D0			_GPIOA(27)
#घोषणा I2S_BCLK0		_GPIOA(28)
#घोषणा I2S_LRCLK0		_GPIOA(29)
#घोषणा I2S_MCLK0		_GPIOA(30)
#घोषणा I2S_D1			_GPIOA(31)
#घोषणा I2S_BCLK1		_GPIOB(0)
#घोषणा I2S_LRCLK1		_GPIOB(1)
#घोषणा I2S_MCLK1		_GPIOB(2)

/* PCM1 */
#घोषणा PCM1_IN			_GPIOD(28)
#घोषणा PCM1_CLK		_GPIOD(29)
#घोषणा PCM1_SYNC		_GPIOD(30)
#घोषणा PCM1_OUT		_GPIOD(31)

/* KEY */
#घोषणा KS_IN0			_GPIOB(3)
#घोषणा KS_IN1			_GPIOB(4)
#घोषणा KS_IN2			_GPIOB(5)
#घोषणा KS_IN3			_GPIOB(6)
#घोषणा KS_OUT0			_GPIOB(7)
#घोषणा KS_OUT1			_GPIOB(8)
#घोषणा KS_OUT2			_GPIOB(9)

/* LVDS */
#घोषणा LVDS_OEP		_GPIOB(10)
#घोषणा LVDS_OEN		_GPIOB(11)
#घोषणा LVDS_ODP		_GPIOB(12)
#घोषणा LVDS_ODN		_GPIOB(13)
#घोषणा LVDS_OCP		_GPIOB(14)
#घोषणा LVDS_OCN		_GPIOB(15)
#घोषणा LVDS_OBP		_GPIOB(16)
#घोषणा LVDS_OBN		_GPIOB(17)
#घोषणा LVDS_OAP		_GPIOB(18)
#घोषणा LVDS_OAN		_GPIOB(19)
#घोषणा LVDS_EEP		_GPIOB(20)
#घोषणा LVDS_EEN		_GPIOB(21)
#घोषणा LVDS_EDP		_GPIOB(22)
#घोषणा LVDS_EDN		_GPIOB(23)
#घोषणा LVDS_ECP		_GPIOB(24)
#घोषणा LVDS_ECN		_GPIOB(25)
#घोषणा LVDS_EBP		_GPIOB(26)
#घोषणा LVDS_EBN		_GPIOB(27)
#घोषणा LVDS_EAP		_GPIOB(28)
#घोषणा LVDS_EAN		_GPIOB(29)
#घोषणा LCD0_D18		_GPIOB(30)
#घोषणा LCD0_D2			_GPIOB(31)

/* DSI */
#घोषणा DSI_DP3			_GPIOC(0)
#घोषणा DSI_DN3			_GPIOC(1)
#घोषणा DSI_DP1			_GPIOC(2)
#घोषणा DSI_DN1			_GPIOC(3)
#घोषणा DSI_CP			_GPIOC(4)
#घोषणा DSI_CN			_GPIOC(5)
#घोषणा DSI_DP0			_GPIOC(6)
#घोषणा DSI_DN0			_GPIOC(7)
#घोषणा DSI_DP2			_GPIOC(8)
#घोषणा DSI_DN2			_GPIOC(9)

/* SD */
#घोषणा SD0_D0			_GPIOC(10)
#घोषणा SD0_D1			_GPIOC(11)
#घोषणा SD0_D2			_GPIOC(12)
#घोषणा SD0_D3			_GPIOC(13)
#घोषणा SD0_D4			_GPIOC(14)
#घोषणा SD0_D5			_GPIOC(15)
#घोषणा SD0_D6			_GPIOC(16)
#घोषणा SD0_D7			_GPIOC(17)
#घोषणा SD0_CMD			_GPIOC(18)
#घोषणा SD0_CLK			_GPIOC(19)
#घोषणा SD1_CMD			_GPIOC(20)
#घोषणा SD1_CLK			_GPIOC(21)
#घोषणा SD1_D0			SD0_D4
#घोषणा SD1_D1			SD0_D5
#घोषणा SD1_D2			SD0_D6
#घोषणा SD1_D3			SD0_D7

/* SPI */
#घोषणा SPI0_SS			_GPIOC(23)
#घोषणा SPI0_MISO		_GPIOC(24)

/* UART क्रम console */
#घोषणा UART0_RX		_GPIOC(26)
#घोषणा UART0_TX		_GPIOC(27)

/* UART क्रम Bluetooth */
#घोषणा UART2_RX		_GPIOD(18)
#घोषणा UART2_TX		_GPIOD(19)
#घोषणा UART2_RTSB		_GPIOD(20)
#घोषणा UART2_CTSB		_GPIOD(21)

/* UART क्रम 3G */
#घोषणा UART3_RX		_GPIOD(22)
#घोषणा UART3_TX		_GPIOD(23)
#घोषणा UART3_RTSB		_GPIOD(24)
#घोषणा UART3_CTSB		_GPIOD(25)

/* I2C */
#घोषणा I2C0_SCLK		_GPIOC(28)
#घोषणा I2C0_SDATA		_GPIOC(29)
#घोषणा I2C1_SCLK		_GPIOE(0)
#घोषणा I2C1_SDATA		_GPIOE(1)
#घोषणा I2C2_SCLK		_GPIOE(2)
#घोषणा I2C2_SDATA		_GPIOE(3)

/* CSI*/
#घोषणा CSI_DN0			_PIN(0)
#घोषणा CSI_DP0			_PIN(1)
#घोषणा CSI_DN1			_PIN(2)
#घोषणा CSI_DP1			_PIN(3)
#घोषणा CSI_CN			_PIN(4)
#घोषणा CSI_CP			_PIN(5)
#घोषणा CSI_DN2			_PIN(6)
#घोषणा CSI_DP2			_PIN(7)
#घोषणा CSI_DN3			_PIN(8)
#घोषणा CSI_DP3			_PIN(9)

/* Sensor */
#घोषणा SENSOR0_PCLK		_GPIOC(31)
#घोषणा SENSOR0_CKOUT		_GPIOD(10)

/* न_अंकD (1.8v / 3.3v) */
#घोषणा Dन_अंकD_D0		_PIN(10)
#घोषणा Dन_अंकD_D1		_PIN(11)
#घोषणा Dन_अंकD_D2		_PIN(12)
#घोषणा Dन_अंकD_D3		_PIN(13)
#घोषणा Dन_अंकD_D4		_PIN(14)
#घोषणा Dन_अंकD_D5		_PIN(15)
#घोषणा Dन_अंकD_D6		_PIN(16)
#घोषणा Dन_अंकD_D7		_PIN(17)
#घोषणा Dन_अंकD_WRB		_PIN(18)
#घोषणा Dन_अंकD_RDB		_PIN(19)
#घोषणा Dन_अंकD_RDBN		_PIN(20)
#घोषणा Dन_अंकD_DQS		_GPIOA(12)
#घोषणा Dन_अंकD_DQSN		_GPIOA(13)
#घोषणा Dन_अंकD_RB0		_PIN(21)
#घोषणा Dन_अंकD_ALE		_GPIOD(12)
#घोषणा Dन_अंकD_CLE		_GPIOD(13)
#घोषणा Dन_अंकD_CEB0		_GPIOD(14)
#घोषणा Dन_अंकD_CEB1		_GPIOD(15)
#घोषणा Dन_अंकD_CEB2		_GPIOD(16)
#घोषणा Dन_अंकD_CEB3		_GPIOD(17)

/* System */
#घोषणा PORB			_PIN(22)
#घोषणा CLKO_25M		_PIN(23)
#घोषणा BSEL			_PIN(24)
#घोषणा PKG0			_PIN(25)
#घोषणा PKG1			_PIN(26)
#घोषणा PKG2			_PIN(27)
#घोषणा PKG3			_PIN(28)

#घोषणा _FIRSTPAD		_GPIOA(0)
#घोषणा _LASTPAD		PKG3
#घोषणा NUM_PADS		(_PIN(28) + 1)

/* Pad names क्रम the pinmux subप्रणाली */
अटल स्थिर काष्ठा pinctrl_pin_desc s700_pads[] = अणु
	PINCTRL_PIN(ETH_TXD0, "eth_txd0"),
	PINCTRL_PIN(ETH_TXD1, "eth_txd1"),
	PINCTRL_PIN(ETH_TXD2, "eth_txd2"),
	PINCTRL_PIN(ETH_TXD3, "eth_txd3"),
	PINCTRL_PIN(ETH_TXEN, "eth_txen"),
	PINCTRL_PIN(ETH_RXER, "eth_rxer"),
	PINCTRL_PIN(ETH_CRS_DV, "eth_crs_dv"),
	PINCTRL_PIN(ETH_RXD1, "eth_rxd1"),
	PINCTRL_PIN(ETH_RXD0, "eth_rxd0"),
	PINCTRL_PIN(ETH_RXD2, "eth_rxd2"),
	PINCTRL_PIN(ETH_RXD3, "eth_rxd3"),
	PINCTRL_PIN(ETH_REF_CLK, "eth_ref_clk"),
	PINCTRL_PIN(ETH_MDC, "eth_mdc"),
	PINCTRL_PIN(ETH_MDIO, "eth_mdio"),
	PINCTRL_PIN(SIRQ0, "sirq0"),
	PINCTRL_PIN(SIRQ1, "sirq1"),
	PINCTRL_PIN(SIRQ2, "sirq2"),
	PINCTRL_PIN(I2S_D0, "i2s_d0"),
	PINCTRL_PIN(I2S_BCLK0, "i2s_bclk0"),
	PINCTRL_PIN(I2S_LRCLK0, "i2s_lrclk0"),
	PINCTRL_PIN(I2S_MCLK0, "i2s_mclk0"),
	PINCTRL_PIN(I2S_D1, "i2s_d1"),
	PINCTRL_PIN(I2S_BCLK1, "i2s_bclk1"),
	PINCTRL_PIN(I2S_LRCLK1, "i2s_lrclk1"),
	PINCTRL_PIN(I2S_MCLK1, "i2s_mclk1"),
	PINCTRL_PIN(PCM1_IN, "pcm1_in"),
	PINCTRL_PIN(PCM1_CLK, "pcm1_clk"),
	PINCTRL_PIN(PCM1_SYNC, "pcm1_sync"),
	PINCTRL_PIN(PCM1_OUT, "pcm1_out"),
	PINCTRL_PIN(KS_IN0, "ks_in0"),
	PINCTRL_PIN(KS_IN1, "ks_in1"),
	PINCTRL_PIN(KS_IN2, "ks_in2"),
	PINCTRL_PIN(KS_IN3, "ks_in3"),
	PINCTRL_PIN(KS_OUT0, "ks_out0"),
	PINCTRL_PIN(KS_OUT1, "ks_out1"),
	PINCTRL_PIN(KS_OUT2, "ks_out2"),
	PINCTRL_PIN(LVDS_OEP, "lvds_oep"),
	PINCTRL_PIN(LVDS_OEN, "lvds_oen"),
	PINCTRL_PIN(LVDS_ODP, "lvds_odp"),
	PINCTRL_PIN(LVDS_ODN, "lvds_odn"),
	PINCTRL_PIN(LVDS_OCP, "lvds_ocp"),
	PINCTRL_PIN(LVDS_OCN, "lvds_ocn"),
	PINCTRL_PIN(LVDS_OBP, "lvds_obp"),
	PINCTRL_PIN(LVDS_OBN, "lvds_obn"),
	PINCTRL_PIN(LVDS_OAP, "lvds_oap"),
	PINCTRL_PIN(LVDS_OAN, "lvds_oan"),
	PINCTRL_PIN(LVDS_EEP, "lvds_eep"),
	PINCTRL_PIN(LVDS_EEN, "lvds_een"),
	PINCTRL_PIN(LVDS_EDP, "lvds_edp"),
	PINCTRL_PIN(LVDS_EDN, "lvds_edn"),
	PINCTRL_PIN(LVDS_ECP, "lvds_ecp"),
	PINCTRL_PIN(LVDS_ECN, "lvds_ecn"),
	PINCTRL_PIN(LVDS_EBP, "lvds_ebp"),
	PINCTRL_PIN(LVDS_EBN, "lvds_ebn"),
	PINCTRL_PIN(LVDS_EAP, "lvds_eap"),
	PINCTRL_PIN(LVDS_EAN, "lvds_ean"),
	PINCTRL_PIN(LCD0_D18, "lcd0_d18"),
	PINCTRL_PIN(LCD0_D2, "lcd0_d2"),
	PINCTRL_PIN(DSI_DP3, "dsi_dp3"),
	PINCTRL_PIN(DSI_DN3, "dsi_dn3"),
	PINCTRL_PIN(DSI_DP1, "dsi_dp1"),
	PINCTRL_PIN(DSI_DN1, "dsi_dn1"),
	PINCTRL_PIN(DSI_CP, "dsi_cp"),
	PINCTRL_PIN(DSI_CN, "dsi_cn"),
	PINCTRL_PIN(DSI_DP0, "dsi_dp0"),
	PINCTRL_PIN(DSI_DN0, "dsi_dn0"),
	PINCTRL_PIN(DSI_DP2, "dsi_dp2"),
	PINCTRL_PIN(DSI_DN2, "dsi_dn2"),
	PINCTRL_PIN(SD0_D0, "sd0_d0"),
	PINCTRL_PIN(SD0_D1, "sd0_d1"),
	PINCTRL_PIN(SD0_D2, "sd0_d2"),
	PINCTRL_PIN(SD0_D3, "sd0_d3"),
	PINCTRL_PIN(SD1_D0, "sd1_d0"),
	PINCTRL_PIN(SD1_D1, "sd1_d1"),
	PINCTRL_PIN(SD1_D2, "sd1_d2"),
	PINCTRL_PIN(SD1_D3, "sd1_d3"),
	PINCTRL_PIN(SD0_CMD, "sd0_cmd"),
	PINCTRL_PIN(SD0_CLK, "sd0_clk"),
	PINCTRL_PIN(SD1_CMD, "sd1_cmd"),
	PINCTRL_PIN(SD1_CLK, "sd1_clk"),
	PINCTRL_PIN(SPI0_SS, "spi0_ss"),
	PINCTRL_PIN(SPI0_MISO, "spi0_miso"),
	PINCTRL_PIN(UART0_RX, "uart0_rx"),
	PINCTRL_PIN(UART0_TX, "uart0_tx"),
	PINCTRL_PIN(UART2_RX, "uart2_rx"),
	PINCTRL_PIN(UART2_TX, "uart2_tx"),
	PINCTRL_PIN(UART2_RTSB, "uart2_rtsb"),
	PINCTRL_PIN(UART2_CTSB, "uart2_ctsb"),
	PINCTRL_PIN(UART3_RX, "uart3_rx"),
	PINCTRL_PIN(UART3_TX, "uart3_tx"),
	PINCTRL_PIN(UART3_RTSB, "uart3_rtsb"),
	PINCTRL_PIN(UART3_CTSB, "uart3_ctsb"),
	PINCTRL_PIN(I2C0_SCLK, "i2c0_sclk"),
	PINCTRL_PIN(I2C0_SDATA, "i2c0_sdata"),
	PINCTRL_PIN(I2C1_SCLK, "i2c1_sclk"),
	PINCTRL_PIN(I2C1_SDATA, "i2c1_sdata"),
	PINCTRL_PIN(I2C2_SCLK, "i2c2_sclk"),
	PINCTRL_PIN(I2C2_SDATA, "i2c2_sdata"),
	PINCTRL_PIN(CSI_DN0, "csi_dn0"),
	PINCTRL_PIN(CSI_DP0, "csi_dp0"),
	PINCTRL_PIN(CSI_DN1, "csi_dn1"),
	PINCTRL_PIN(CSI_DP1, "csi_dp1"),
	PINCTRL_PIN(CSI_CN, "csi_cn"),
	PINCTRL_PIN(CSI_CP, "csi_cp"),
	PINCTRL_PIN(CSI_DN2, "csi_dn2"),
	PINCTRL_PIN(CSI_DP2, "csi_dp2"),
	PINCTRL_PIN(CSI_DN3, "csi_dn3"),
	PINCTRL_PIN(CSI_DP3, "csi_dp3"),
	PINCTRL_PIN(SENSOR0_PCLK, "sensor0_pclk"),
	PINCTRL_PIN(SENSOR0_CKOUT, "sensor0_ckout"),
	PINCTRL_PIN(Dन_अंकD_D0, "dnand_d0"),
	PINCTRL_PIN(Dन_अंकD_D1, "dnand_d1"),
	PINCTRL_PIN(Dन_अंकD_D2, "dnand_d2"),
	PINCTRL_PIN(Dन_अंकD_D3, "dnand_d3"),
	PINCTRL_PIN(Dन_अंकD_D4, "dnand_d4"),
	PINCTRL_PIN(Dन_अंकD_D5, "dnand_d5"),
	PINCTRL_PIN(Dन_अंकD_D6, "dnand_d6"),
	PINCTRL_PIN(Dन_अंकD_D7, "dnand_d7"),
	PINCTRL_PIN(Dन_अंकD_WRB, "dnand_wrb"),
	PINCTRL_PIN(Dन_अंकD_RDB, "dnand_rdb"),
	PINCTRL_PIN(Dन_अंकD_RDBN, "dnand_rdbn"),
	PINCTRL_PIN(Dन_अंकD_DQS, "dnand_dqs"),
	PINCTRL_PIN(Dन_अंकD_DQSN, "dnand_dqsn"),
	PINCTRL_PIN(Dन_अंकD_RB0, "dnand_rb0"),
	PINCTRL_PIN(Dन_अंकD_ALE, "dnand_ale"),
	PINCTRL_PIN(Dन_अंकD_CLE, "dnand_cle"),
	PINCTRL_PIN(Dन_अंकD_CEB0, "dnand_ceb0"),
	PINCTRL_PIN(Dन_अंकD_CEB1, "dnand_ceb1"),
	PINCTRL_PIN(Dन_अंकD_CEB2, "dnand_ceb2"),
	PINCTRL_PIN(Dन_अंकD_CEB3, "dnand_ceb3"),
	PINCTRL_PIN(PORB, "porb"),
	PINCTRL_PIN(CLKO_25M, "clko_25m"),
	PINCTRL_PIN(BSEL, "bsel"),
	PINCTRL_PIN(PKG0, "pkg0"),
	PINCTRL_PIN(PKG1, "pkg1"),
	PINCTRL_PIN(PKG2, "pkg2"),
	PINCTRL_PIN(PKG3, "pkg3"),
पूर्ण;

क्रमागत s700_pinmux_functions अणु
	S700_MUX_NOR,
	S700_MUX_ETH_RGMII,
	S700_MUX_ETH_SGMII,
	S700_MUX_SPI0,
	S700_MUX_SPI1,
	S700_MUX_SPI2,
	S700_MUX_SPI3,
	S700_MUX_SENS0,
	S700_MUX_SENS1,
	S700_MUX_UART0,
	S700_MUX_UART1,
	S700_MUX_UART2,
	S700_MUX_UART3,
	S700_MUX_UART4,
	S700_MUX_UART5,
	S700_MUX_UART6,
	S700_MUX_I2S0,
	S700_MUX_I2S1,
	S700_MUX_PCM1,
	S700_MUX_PCM0,
	S700_MUX_KS,
	S700_MUX_JTAG,
	S700_MUX_PWM0,
	S700_MUX_PWM1,
	S700_MUX_PWM2,
	S700_MUX_PWM3,
	S700_MUX_PWM4,
	S700_MUX_PWM5,
	S700_MUX_P0,
	S700_MUX_SD0,
	S700_MUX_SD1,
	S700_MUX_SD2,
	S700_MUX_I2C0,
	S700_MUX_I2C1,
	S700_MUX_I2C2,
	S700_MUX_I2C3,
	S700_MUX_DSI,
	S700_MUX_LVDS,
	S700_MUX_USB30,
	S700_MUX_CLKO_25M,
	S700_MUX_MIPI_CSI,
	S700_MUX_न_अंकD,
	S700_MUX_SPDIF,
	S700_MUX_SIRQ0,
	S700_MUX_SIRQ1,
	S700_MUX_SIRQ2,
	S700_MUX_BT,
	S700_MUX_LCD0,
	S700_MUX_RESERVED,
पूर्ण;

/* mfp0_31_30 reserved */

/* rgmii_txd23 */
अटल अचिन्हित पूर्णांक  rgmii_txd23_mfp_pads[]		= अणु ETH_TXD2, ETH_TXD3पूर्ण;
अटल अचिन्हित पूर्णांक  rgmii_txd23_mfp_funcs[]		= अणु S700_MUX_ETH_RGMII,
							    S700_MUX_I2C1,
							    S700_MUX_UART3 पूर्ण;
/* rgmii_rxd2 */
अटल अचिन्हित पूर्णांक  rgmii_rxd2_mfp_pads[]		= अणु ETH_RXD2 पूर्ण;
अटल अचिन्हित पूर्णांक  rgmii_rxd2_mfp_funcs[]		= अणु S700_MUX_ETH_RGMII,
							    S700_MUX_PWM0,
							    S700_MUX_UART3 पूर्ण;
/* rgmii_rxd3 */
अटल अचिन्हित पूर्णांक  rgmii_rxd3_mfp_pads[]		= अणु ETH_RXD3पूर्ण;
अटल अचिन्हित पूर्णांक  rgmii_rxd3_mfp_funcs[]		= अणु S700_MUX_ETH_RGMII,
							    S700_MUX_PWM2,
							    S700_MUX_UART3 पूर्ण;
/* lcd0_d18 */
अटल अचिन्हित पूर्णांक  lcd0_d18_mfp_pads[]		= अणु LCD0_D18 पूर्ण;
अटल अचिन्हित पूर्णांक  lcd0_d18_mfp_funcs[]		= अणु S700_MUX_NOR,
							    S700_MUX_SENS1,
							    S700_MUX_PWM2,
							    S700_MUX_PWM4,
							    S700_MUX_LCD0 पूर्ण;
/* rgmii_txd01 */
अटल अचिन्हित पूर्णांक  rgmii_txd01_mfp_pads[]		= अणु ETH_CRS_DV पूर्ण;
अटल अचिन्हित पूर्णांक  rgmii_txd01_mfp_funcs[]		= अणु S700_MUX_ETH_RGMII,
							    S700_MUX_RESERVED,
							    S700_MUX_SPI2,
							    S700_MUX_UART4,
							    S700_MUX_PWM4 पूर्ण;
/* rgmii_txd0 */
अटल अचिन्हित पूर्णांक  rgmii_txd0_mfp_pads[]		= अणु ETH_TXD0 पूर्ण;
अटल अचिन्हित पूर्णांक  rgmii_txd0_mfp_funcs[]		= अणु S700_MUX_ETH_RGMII,
							    S700_MUX_ETH_SGMII,
							    S700_MUX_SPI2,
							    S700_MUX_UART6,
							    S700_MUX_PWM4 पूर्ण;
/* rgmii_txd1 */
अटल अचिन्हित पूर्णांक  rgmii_txd1_mfp_pads[]		= अणु ETH_TXD1 पूर्ण;
अटल अचिन्हित पूर्णांक  rgmii_txd1_mfp_funcs[]		= अणु S700_MUX_ETH_RGMII,
							    S700_MUX_ETH_SGMII,
							    S700_MUX_SPI2,
							    S700_MUX_UART6,
							    S700_MUX_PWM5 पूर्ण;
/* rgmii_txen */
अटल अचिन्हित पूर्णांक  rgmii_txen_mfp_pads[]		= अणु ETH_TXEN पूर्ण;
अटल अचिन्हित पूर्णांक  rgmii_txen_mfp_funcs[]		= अणु S700_MUX_ETH_RGMII,
							    S700_MUX_UART2,
							    S700_MUX_SPI3,
							    S700_MUX_PWM0 पूर्ण;
/* rgmii_rxen */
अटल अचिन्हित पूर्णांक  rgmii_rxen_mfp_pads[]		= अणु ETH_RXER पूर्ण;
अटल अचिन्हित पूर्णांक  rgmii_rxen_mfp_funcs[]		= अणु S700_MUX_ETH_RGMII,
							    S700_MUX_UART2,
							    S700_MUX_SPI3,
							    S700_MUX_PWM1 पूर्ण;
/* mfp0_12_11 reserved */
/* rgmii_rxd1*/
अटल अचिन्हित पूर्णांक  rgmii_rxd1_mfp_pads[]		= अणु ETH_RXD1 पूर्ण;
अटल अचिन्हित पूर्णांक  rgmii_rxd1_mfp_funcs[]		= अणु S700_MUX_ETH_RGMII,
							    S700_MUX_UART2,
							    S700_MUX_SPI3,
							    S700_MUX_PWM2,
							    S700_MUX_UART5,
							    S700_MUX_ETH_SGMII पूर्ण;
/* rgmii_rxd0 */
अटल अचिन्हित पूर्णांक  rgmii_rxd0_mfp_pads[]		= अणु ETH_RXD0 पूर्ण;
अटल अचिन्हित पूर्णांक  rgmii_rxd0_mfp_funcs[]		= अणु S700_MUX_ETH_RGMII,
							    S700_MUX_UART2,
							    S700_MUX_SPI3,
							    S700_MUX_PWM3,
							    S700_MUX_UART5,
							    S700_MUX_ETH_SGMII पूर्ण;
/* rgmii_ref_clk */
अटल अचिन्हित पूर्णांक  rgmii_ref_clk_mfp_pads[]		= अणु ETH_REF_CLK पूर्ण;
अटल अचिन्हित पूर्णांक  rgmii_ref_clk_mfp_funcs[]		= अणु S700_MUX_ETH_RGMII,
							    S700_MUX_UART4,
							    S700_MUX_SPI2,
							    S700_MUX_RESERVED,
							    S700_MUX_ETH_SGMII पूर्ण;
/* i2s_d0 */
अटल अचिन्हित पूर्णांक  i2s_d0_mfp_pads[]			= अणु I2S_D0 पूर्ण;
अटल अचिन्हित पूर्णांक  i2s_d0_mfp_funcs[]			= अणु S700_MUX_I2S0,
							    S700_MUX_NOR पूर्ण;
/* i2s_pcm1 */
अटल अचिन्हित पूर्णांक  i2s_pcm1_mfp_pads[]		= अणु I2S_LRCLK0,
							    I2S_MCLK0 पूर्ण;
अटल अचिन्हित पूर्णांक  i2s_pcm1_mfp_funcs[]		= अणु S700_MUX_I2S0,
							    S700_MUX_NOR,
							    S700_MUX_PCM1,
							    S700_MUX_BT पूर्ण;
/* i2s0_pcm0 */
अटल अचिन्हित पूर्णांक  i2s0_pcm0_mfp_pads[]		= अणु I2S_BCLK0 पूर्ण;
अटल अचिन्हित पूर्णांक  i2s0_pcm0_mfp_funcs[]		= अणु S700_MUX_I2S0,
							    S700_MUX_NOR,
							    S700_MUX_PCM0,
							    S700_MUX_BT पूर्ण;
/* i2s1_pcm0 */
अटल अचिन्हित पूर्णांक  i2s1_pcm0_mfp_pads[]		= अणु I2S_BCLK1,
							    I2S_LRCLK1,
							    I2S_MCLK1 पूर्ण;

अटल अचिन्हित पूर्णांक  i2s1_pcm0_mfp_funcs[]		= अणु S700_MUX_I2S1,
							    S700_MUX_NOR,
							    S700_MUX_PCM0,
							    S700_MUX_BT पूर्ण;
/* i2s_d1 */
अटल अचिन्हित पूर्णांक  i2s_d1_mfp_pads[]			= अणु I2S_D1 पूर्ण;
अटल अचिन्हित पूर्णांक  i2s_d1_mfp_funcs[]			= अणु S700_MUX_I2S1,
							    S700_MUX_NOR पूर्ण;
/* ks_in2 */
अटल अचिन्हित पूर्णांक  ks_in2_mfp_pads[]			= अणु KS_IN2 पूर्ण;
अटल अचिन्हित पूर्णांक  ks_in2_mfp_funcs[]			= अणु S700_MUX_KS,
							    S700_MUX_JTAG,
							    S700_MUX_NOR,
							    S700_MUX_BT,
							    S700_MUX_PWM0,
							    S700_MUX_SENS1,
							    S700_MUX_PWM0,
							    S700_MUX_P0 पूर्ण;
/* ks_in1 */
अटल अचिन्हित पूर्णांक  ks_in1_mfp_pads[]			= अणु KS_IN1 पूर्ण;
अटल अचिन्हित पूर्णांक  ks_in1_mfp_funcs[]			= अणु S700_MUX_KS,
							    S700_MUX_JTAG,
							    S700_MUX_NOR,
							    S700_MUX_BT,
							    S700_MUX_PWM5,
							    S700_MUX_SENS1,
							    S700_MUX_PWM1,
							    S700_MUX_USB30 पूर्ण;
/* ks_in0 */
अटल अचिन्हित पूर्णांक  ks_in0_mfp_pads[]			= अणु KS_IN0 पूर्ण;
अटल अचिन्हित पूर्णांक  ks_in0_mfp_funcs[]			= अणु S700_MUX_KS,
							    S700_MUX_JTAG,
							    S700_MUX_NOR,
							    S700_MUX_BT,
							    S700_MUX_PWM4,
							    S700_MUX_SENS1,
							    S700_MUX_PWM4,
							    S700_MUX_P0 पूर्ण;
/* ks_in3 */
अटल अचिन्हित पूर्णांक  ks_in3_mfp_pads[]			= अणु KS_IN3 पूर्ण;
अटल अचिन्हित पूर्णांक  ks_in3_mfp_funcs[]			= अणु S700_MUX_KS,
							    S700_MUX_JTAG,
							    S700_MUX_NOR,
							    S700_MUX_PWM1,
							    S700_MUX_BT,
							    S700_MUX_SENS1 पूर्ण;
/* ks_out0 */
अटल अचिन्हित पूर्णांक  ks_out0_mfp_pads[]			= अणु KS_OUT0 पूर्ण;
अटल अचिन्हित पूर्णांक  ks_out0_mfp_funcs[]		= अणु S700_MUX_KS,
							    S700_MUX_UART5,
							    S700_MUX_NOR,
							    S700_MUX_PWM2,
							    S700_MUX_BT,
							    S700_MUX_SENS1,
							    S700_MUX_SD0,
							    S700_MUX_UART4 पूर्ण;

/* ks_out1 */
अटल अचिन्हित पूर्णांक  ks_out1_mfp_pads[]			= अणु KS_OUT1 पूर्ण;
अटल अचिन्हित पूर्णांक  ks_out1_mfp_funcs[]		= अणु S700_MUX_KS,
							    S700_MUX_JTAG,
							    S700_MUX_NOR,
							    S700_MUX_PWM3,
							    S700_MUX_BT,
							    S700_MUX_SENS1,
							    S700_MUX_SD0,
							    S700_MUX_UART4 पूर्ण;
/* ks_out2 */
अटल अचिन्हित पूर्णांक  ks_out2_mfp_pads[]			= अणु KS_OUT2 पूर्ण;
अटल अचिन्हित पूर्णांक  ks_out2_mfp_funcs[]		= अणु S700_MUX_SD0,
							    S700_MUX_KS,
							    S700_MUX_NOR,
							    S700_MUX_PWM2,
							    S700_MUX_UART5,
							    S700_MUX_SENS1,
							    S700_MUX_BT पूर्ण;
/* lvds_o_pn */
अटल अचिन्हित पूर्णांक  lvds_o_pn_mfp_pads[]		= अणु LVDS_OEP,
							    LVDS_OEN,
							    LVDS_ODP,
							    LVDS_ODN,
							    LVDS_OCP,
							    LVDS_OCN,
							    LVDS_OBP,
							    LVDS_OBN,
							    LVDS_OAP,
							    LVDS_OAN पूर्ण;

अटल अचिन्हित पूर्णांक  lvds_o_pn_mfp_funcs[]		= अणु S700_MUX_LVDS,
							    S700_MUX_BT,
							    S700_MUX_LCD0 पूर्ण;

/* dsi_dn0 */
अटल अचिन्हित पूर्णांक  dsi_dn0_mfp_pads[]			= अणु DSI_DN0 पूर्ण;
अटल अचिन्हित पूर्णांक  dsi_dn0_mfp_funcs[]		= अणु S700_MUX_DSI,
							    S700_MUX_UART2,
							    S700_MUX_SPI0 पूर्ण;
/* dsi_dp2 */
अटल अचिन्हित पूर्णांक  dsi_dp2_mfp_pads[]			= अणु DSI_DP2 पूर्ण;
अटल अचिन्हित पूर्णांक  dsi_dp2_mfp_funcs[]		= अणु S700_MUX_DSI,
							    S700_MUX_UART2,
							    S700_MUX_SPI0,
							    S700_MUX_SD1 पूर्ण;
/* lcd0_d2 */
अटल अचिन्हित पूर्णांक  lcd0_d2_mfp_pads[]			= अणु LCD0_D2 पूर्ण;
अटल अचिन्हित पूर्णांक  lcd0_d2_mfp_funcs[]		= अणु S700_MUX_NOR,
							    S700_MUX_SD0,
							    S700_MUX_RESERVED,
							    S700_MUX_PWM3,
							    S700_MUX_LCD0 पूर्ण;
/* dsi_dp3 */
अटल अचिन्हित पूर्णांक  dsi_dp3_mfp_pads[]			= अणु DSI_DP3 पूर्ण;
अटल अचिन्हित पूर्णांक  dsi_dp3_mfp_funcs[]		= अणु S700_MUX_DSI,
							    S700_MUX_SD0,
							    S700_MUX_SD1,
							    S700_MUX_LCD0 पूर्ण;
/* dsi_dn3 */
अटल अचिन्हित पूर्णांक  dsi_dn3_mfp_pads[]			= अणु DSI_DN3 पूर्ण;
अटल अचिन्हित पूर्णांक  dsi_dn3_mfp_funcs[]		= अणु S700_MUX_DSI,
							    S700_MUX_SD0,
							    S700_MUX_SD1,
							    S700_MUX_LCD0 पूर्ण;
/* dsi_dp0 */
अटल अचिन्हित पूर्णांक  dsi_dp0_mfp_pads[]			= अणु DSI_DP0 पूर्ण;
अटल अचिन्हित पूर्णांक  dsi_dp0_mfp_funcs[]		= अणु S700_MUX_DSI,
							    S700_MUX_RESERVED,
							    S700_MUX_SD0,
							    S700_MUX_UART2,
							    S700_MUX_SPI0 पूर्ण;
/* lvds_ee_pn */
अटल अचिन्हित पूर्णांक  lvds_ee_pn_mfp_pads[]		= अणु LVDS_EEP,
							    LVDS_EEN पूर्ण;
अटल अचिन्हित पूर्णांक  lvds_ee_pn_mfp_funcs[]		= अणु S700_MUX_LVDS,
							    S700_MUX_NOR,
							    S700_MUX_BT,
							    S700_MUX_LCD0 पूर्ण;
/* uart2_rx_tx */
अटल अचिन्हित पूर्णांक  uart2_rx_tx_mfp_pads[]		= अणु UART2_RX,
							    UART2_TX पूर्ण;
अटल अचिन्हित पूर्णांक  uart2_rx_tx_mfp_funcs[]		= अणु S700_MUX_UART2,
							    S700_MUX_NOR,
							    S700_MUX_SPI0,
							    S700_MUX_PCM0 पूर्ण;
/* spi0_i2c_pcm */
अटल अचिन्हित पूर्णांक  spi0_i2c_pcm_mfp_pads[]		= अणु SPI0_SS,
							    SPI0_MISO पूर्ण;
अटल अचिन्हित पूर्णांक  spi0_i2c_pcm_mfp_funcs[]		= अणु S700_MUX_SPI0,
							    S700_MUX_NOR,
							    S700_MUX_I2S1,
							    S700_MUX_PCM1,
							    S700_MUX_PCM0,
							    S700_MUX_I2C2 पूर्ण;
/* mfp2_31 reserved */

/* dsi_dnp1_cp_d2 */
अटल अचिन्हित पूर्णांक  dsi_dnp1_cp_d2_mfp_pads[]		= अणु DSI_DP1,
							    DSI_CP,
							    DSI_CN पूर्ण;
अटल अचिन्हित पूर्णांक  dsi_dnp1_cp_d2_mfp_funcs[]		= अणु S700_MUX_DSI,
							    S700_MUX_LCD0,
							    S700_MUX_RESERVED पूर्ण;
/* dsi_dnp1_cp_d17 */
अटल अचिन्हित पूर्णांक  dsi_dnp1_cp_d17_mfp_pads[]		= अणु DSI_DP1,
							    DSI_CP,
							    DSI_CN पूर्ण;

अटल अचिन्हित पूर्णांक  dsi_dnp1_cp_d17_mfp_funcs[]	= अणु S700_MUX_DSI,
							    S700_MUX_RESERVED,
							    S700_MUX_LCD0 पूर्ण;
/* lvds_e_pn */
अटल अचिन्हित पूर्णांक  lvds_e_pn_mfp_pads[]		= अणु LVDS_EDP,
							    LVDS_EDN,
							    LVDS_ECP,
							    LVDS_ECN,
							    LVDS_EBP,
							    LVDS_EBN,
							    LVDS_EAP,
							    LVDS_EAN पूर्ण;

अटल अचिन्हित पूर्णांक  lvds_e_pn_mfp_funcs[]		= अणु S700_MUX_LVDS,
							    S700_MUX_NOR,
							    S700_MUX_LCD0 पूर्ण;
/* dsi_dn2 */
अटल अचिन्हित पूर्णांक  dsi_dn2_mfp_pads[]			= अणु DSI_DN2 पूर्ण;
अटल अचिन्हित पूर्णांक  dsi_dn2_mfp_funcs[]		= अणु S700_MUX_DSI,
							    S700_MUX_RESERVED,
							    S700_MUX_SD1,
							    S700_MUX_UART2,
							    S700_MUX_SPI0 पूर्ण;
/* uart2_rtsb */
अटल अचिन्हित पूर्णांक  uart2_rtsb_mfp_pads[]		= अणु UART2_RTSB पूर्ण;
अटल अचिन्हित पूर्णांक  uart2_rtsb_mfp_funcs[]		= अणु S700_MUX_UART2,
							    S700_MUX_UART0 पूर्ण;

/* uart2_ctsb */
अटल अचिन्हित पूर्णांक  uart2_ctsb_mfp_pads[]		= अणु UART2_CTSB पूर्ण;
अटल अचिन्हित पूर्णांक  uart2_ctsb_mfp_funcs[]		= अणु S700_MUX_UART2,
							    S700_MUX_UART0 पूर्ण;
/* uart3_rtsb */
अटल अचिन्हित पूर्णांक  uart3_rtsb_mfp_pads[]		= अणु UART3_RTSB पूर्ण;
अटल अचिन्हित पूर्णांक  uart3_rtsb_mfp_funcs[]		= अणु S700_MUX_UART3,
							    S700_MUX_UART5 पूर्ण;

/* uart3_ctsb */
अटल अचिन्हित पूर्णांक  uart3_ctsb_mfp_pads[]		= अणु UART3_CTSB पूर्ण;
अटल अचिन्हित पूर्णांक  uart3_ctsb_mfp_funcs[]		= अणु S700_MUX_UART3,
							    S700_MUX_UART5 पूर्ण;
/* sd0_d0 */
अटल अचिन्हित पूर्णांक  sd0_d0_mfp_pads[]			= अणु SD0_D0 पूर्ण;
अटल अचिन्हित पूर्णांक  sd0_d0_mfp_funcs[]			= अणु S700_MUX_SD0,
							    S700_MUX_NOR,
							    S700_MUX_RESERVED,
							    S700_MUX_JTAG,
							    S700_MUX_UART2,
							    S700_MUX_UART5 पूर्ण;
/* sd0_d1 */
अटल अचिन्हित पूर्णांक  sd0_d1_mfp_pads[]			= अणु SD0_D1 पूर्ण;
अटल अचिन्हित पूर्णांक  sd0_d1_mfp_funcs[]			= अणु S700_MUX_SD0,
							    S700_MUX_NOR,
							    S700_MUX_RESERVED,
							    S700_MUX_RESERVED,
							    S700_MUX_UART2,
							    S700_MUX_UART5 पूर्ण;
/* sd0_d2_d3 */
अटल अचिन्हित पूर्णांक  sd0_d2_d3_mfp_pads[]		= अणु SD0_D2,
							    SD0_D3 पूर्ण;
अटल अचिन्हित पूर्णांक  sd0_d2_d3_mfp_funcs[]		= अणु S700_MUX_SD0,
							    S700_MUX_NOR,
							    S700_MUX_RESERVED,
							    S700_MUX_JTAG,
							    S700_MUX_UART2,
							    S700_MUX_UART1 पूर्ण;

/* sd1_d0_d3 */
अटल अचिन्हित पूर्णांक  sd1_d0_d3_mfp_pads[]		= अणु SD1_D0,
							    SD1_D1,
							    SD1_D2,
							    SD1_D3 पूर्ण;
अटल अचिन्हित पूर्णांक  sd1_d0_d3_mfp_funcs[]		= अणु S700_MUX_SD0,
							    S700_MUX_NOR,
							    S700_MUX_RESERVED,
							    S700_MUX_SD1 पूर्ण;

/* sd0_cmd */
अटल अचिन्हित पूर्णांक  sd0_cmd_mfp_pads[]			= अणु SD0_CMD पूर्ण;
अटल अचिन्हित पूर्णांक  sd0_cmd_mfp_funcs[]		= अणु S700_MUX_SD0,
							    S700_MUX_NOR,
							    S700_MUX_RESERVED,
							    S700_MUX_JTAG पूर्ण;
/* sd0_clk */
अटल अचिन्हित पूर्णांक  sd0_clk_mfp_pads[]			= अणु SD0_CLK पूर्ण;
अटल अचिन्हित पूर्णांक  sd0_clk_mfp_funcs[]		= अणु S700_MUX_SD0,
							    S700_MUX_RESERVED,
							    S700_MUX_JTAG पूर्ण;
/* sd1_cmd */
अटल अचिन्हित पूर्णांक  sd1_cmd_mfp_pads[]			= अणु SD1_CMD पूर्ण;
अटल अचिन्हित पूर्णांक  sd1_cmd_mfp_funcs[]		= अणु S700_MUX_SD1,
							    S700_MUX_NOR पूर्ण;
/* uart0_rx */
अटल अचिन्हित पूर्णांक  uart0_rx_mfp_pads[]		= अणु UART0_RX पूर्ण;
अटल अचिन्हित पूर्णांक  uart0_rx_mfp_funcs[]		= अणु S700_MUX_UART0,
							    S700_MUX_UART2,
							    S700_MUX_SPI1,
							    S700_MUX_I2C0,
							    S700_MUX_PCM1,
							    S700_MUX_I2S1 पूर्ण;
/* dnand_data_wr1 reserved */

/* clko_25m */
अटल अचिन्हित पूर्णांक  clko_25m_mfp_pads[]		= अणु CLKO_25M पूर्ण;
अटल अचिन्हित पूर्णांक  clko_25m_mfp_funcs[]		= अणु S700_MUX_RESERVED,
							    S700_MUX_CLKO_25M पूर्ण;
/* csi_cn_cp */
अटल अचिन्हित पूर्णांक  csi_cn_cp_mfp_pads[]		= अणु CSI_CN,
							    CSI_CP पूर्ण;
अटल अचिन्हित पूर्णांक  csi_cn_cp_mfp_funcs[]		= अणु S700_MUX_MIPI_CSI,
							    S700_MUX_SENS0 पूर्ण;
/* dnand_acle_ce07_24 reserved */

/* sens0_ckout */
अटल अचिन्हित पूर्णांक  sens0_ckout_mfp_pads[]		= अणु SENSOR0_CKOUT पूर्ण;
अटल अचिन्हित पूर्णांक  sens0_ckout_mfp_funcs[]		= अणु S700_MUX_SENS0,
							    S700_MUX_NOR,
							    S700_MUX_SENS1,
							    S700_MUX_PWM1 पूर्ण;
/* uart0_tx */
अटल अचिन्हित पूर्णांक  uart0_tx_mfp_pads[]		= अणु UART0_TX पूर्ण;
अटल अचिन्हित पूर्णांक  uart0_tx_mfp_funcs[]		= अणु S700_MUX_UART0,
							    S700_MUX_UART2,
							    S700_MUX_SPI1,
							    S700_MUX_I2C0,
							    S700_MUX_SPDIF,
							    S700_MUX_PCM1,
							    S700_MUX_I2S1 पूर्ण;
/* i2c0_mfp */
अटल अचिन्हित पूर्णांक  i2c0_mfp_pads[]		= अणु I2C0_SCLK,
							    I2C0_SDATA पूर्ण;
अटल अचिन्हित पूर्णांक  i2c0_mfp_funcs[]		= अणु S700_MUX_I2C0,
							    S700_MUX_UART2,
							    S700_MUX_I2C1,
							    S700_MUX_UART1,
							    S700_MUX_SPI1 पूर्ण;
/* csi_dn_dp */
अटल अचिन्हित पूर्णांक  csi_dn_dp_mfp_pads[]		= अणु CSI_DN0,
							    CSI_DN1,
							    CSI_DN2,
							    CSI_DN3,
							    CSI_DP0,
							    CSI_DP1,
							    CSI_DP2,
							    CSI_DP3 पूर्ण;
अटल अचिन्हित पूर्णांक  csi_dn_dp_mfp_funcs[]		= अणु S700_MUX_MIPI_CSI,
							    S700_MUX_SENS0 पूर्ण;
/* sen0_pclk */
अटल अचिन्हित पूर्णांक  sen0_pclk_mfp_pads[]		= अणु SENSOR0_PCLK पूर्ण;
अटल अचिन्हित पूर्णांक  sen0_pclk_mfp_funcs[]		= अणु S700_MUX_SENS0,
							    S700_MUX_NOR,
							    S700_MUX_PWM0 पूर्ण;
/* pcm1_in */
अटल अचिन्हित पूर्णांक  pcm1_in_mfp_pads[]			= अणु PCM1_IN पूर्ण;
अटल अचिन्हित पूर्णांक  pcm1_in_mfp_funcs[]		= अणु S700_MUX_PCM1,
							    S700_MUX_SENS1,
							    S700_MUX_BT,
							    S700_MUX_PWM4 पूर्ण;
/* pcm1_clk */
अटल अचिन्हित पूर्णांक  pcm1_clk_mfp_pads[]		= अणु PCM1_CLK पूर्ण;
अटल अचिन्हित पूर्णांक  pcm1_clk_mfp_funcs[]		= अणु S700_MUX_PCM1,
							    S700_MUX_SENS1,
							    S700_MUX_BT,
							    S700_MUX_PWM5 पूर्ण;
/* pcm1_sync */
अटल अचिन्हित पूर्णांक  pcm1_sync_mfp_pads[]		= अणु PCM1_SYNC पूर्ण;
अटल अचिन्हित पूर्णांक  pcm1_sync_mfp_funcs[]		= अणु S700_MUX_PCM1,
							    S700_MUX_SENS1,
							    S700_MUX_BT,
							    S700_MUX_I2C3 पूर्ण;
/* pcm1_out */
अटल अचिन्हित पूर्णांक  pcm1_out_mfp_pads[]		= अणु PCM1_OUT पूर्ण;
अटल अचिन्हित पूर्णांक  pcm1_out_mfp_funcs[]		= अणु S700_MUX_PCM1,
							    S700_MUX_SENS1,
							    S700_MUX_BT,
							    S700_MUX_I2C3 पूर्ण;
/* dnand_data_wr */
अटल अचिन्हित पूर्णांक  dnand_data_wr_mfp_pads[]		= अणु Dन_अंकD_D0,
							    Dन_अंकD_D1,
							    Dन_अंकD_D2,
							    Dन_अंकD_D3,
							    Dन_अंकD_D4,
							    Dन_अंकD_D5,
							    Dन_अंकD_D6,
							    Dन_अंकD_D7,
							    Dन_अंकD_RDB,
							    Dन_अंकD_RDBN पूर्ण;
अटल अचिन्हित पूर्णांक  dnand_data_wr_mfp_funcs[]		= अणु S700_MUX_न_अंकD,
							    S700_MUX_SD2 पूर्ण;
/* dnand_acle_ce0 */
अटल अचिन्हित पूर्णांक  dnand_acle_ce0_mfp_pads[]		= अणु Dन_अंकD_ALE,
							    Dन_अंकD_CLE,
							    Dन_अंकD_CEB0,
							    Dन_अंकD_CEB1 पूर्ण;
अटल अचिन्हित पूर्णांक  dnand_acle_ce0_mfp_funcs[]		= अणु S700_MUX_न_अंकD,
							    S700_MUX_SPI2 पूर्ण;

/* nand_ceb2 */
अटल अचिन्हित पूर्णांक  nand_ceb2_mfp_pads[]		= अणु Dन_अंकD_CEB2 पूर्ण;
अटल अचिन्हित पूर्णांक  nand_ceb2_mfp_funcs[]		= अणु S700_MUX_न_अंकD,
							    S700_MUX_PWM5 पूर्ण;
/* nand_ceb3 */
अटल अचिन्हित पूर्णांक  nand_ceb3_mfp_pads[]		= अणु Dन_अंकD_CEB3 पूर्ण;
अटल अचिन्हित पूर्णांक  nand_ceb3_mfp_funcs[]		= अणु S700_MUX_न_अंकD,
							    S700_MUX_PWM4 पूर्ण;
/*****End MFP group data****************************/

/*****PADDRV group data****************************/

/*PAD_DRV0*/
अटल अचिन्हित पूर्णांक  sirq_drv_pads[]			= अणु SIRQ0,
							    SIRQ1,
							    SIRQ2 पूर्ण;

अटल अचिन्हित पूर्णांक  rgmii_txd23_drv_pads[]		= अणु ETH_TXD2,
							    ETH_TXD3 पूर्ण;

अटल अचिन्हित पूर्णांक  rgmii_rxd23_drv_pads[]		= अणु ETH_RXD2,
							    ETH_RXD3 पूर्ण;

अटल अचिन्हित पूर्णांक  rgmii_txd01_txen_drv_pads[]	= अणु ETH_TXD0,
							    ETH_TXD1,
							    ETH_TXEN पूर्ण;

अटल अचिन्हित पूर्णांक  rgmii_rxer_drv_pads[]		= अणु ETH_RXER पूर्ण;

अटल अचिन्हित पूर्णांक  rgmii_crs_drv_pads[]		= अणु ETH_CRS_DV पूर्ण;

अटल अचिन्हित पूर्णांक  rgmii_rxd10_drv_pads[]		= अणु ETH_RXD0,
							    ETH_RXD1 पूर्ण;

अटल अचिन्हित पूर्णांक  rgmii_ref_clk_drv_pads[]		= अणु ETH_REF_CLK पूर्ण;

अटल अचिन्हित पूर्णांक  smi_mdc_mdio_drv_pads[]		= अणु ETH_MDC,
							    ETH_MDIO पूर्ण;

अटल अचिन्हित पूर्णांक  i2s_d0_drv_pads[]			= अणु I2S_D0 पूर्ण;

अटल अचिन्हित पूर्णांक  i2s_bclk0_drv_pads[]		= अणु I2S_BCLK0 पूर्ण;

अटल अचिन्हित पूर्णांक  i2s3_drv_pads[]			= अणु I2S_LRCLK0,
							    I2S_MCLK0,
							    I2S_D1 पूर्ण;

अटल अचिन्हित पूर्णांक  i2s13_drv_pads[]			= अणु I2S_BCLK1,
							    I2S_LRCLK1,
							    I2S_MCLK1 पूर्ण;

अटल अचिन्हित पूर्णांक  pcm1_drv_pads[]			= अणु PCM1_IN,
							    PCM1_CLK,
							    PCM1_SYNC,
							    PCM1_OUT पूर्ण;

अटल अचिन्हित पूर्णांक  ks_in_drv_pads[]			= अणु KS_IN0,
							    KS_IN1,
							    KS_IN2,
							    KS_IN3 पूर्ण;

/*PAD_DRV1*/
अटल अचिन्हित पूर्णांक  ks_out_drv_pads[]			= अणु KS_OUT0,
							    KS_OUT1,
							    KS_OUT2 पूर्ण;

अटल अचिन्हित पूर्णांक  lvds_all_drv_pads[]		= अणु LVDS_OEP,
							    LVDS_OEN,
							    LVDS_ODP,
							    LVDS_ODN,
							    LVDS_OCP,
							    LVDS_OCN,
							    LVDS_OBP,
							    LVDS_OBN,
							    LVDS_OAP,
							    LVDS_OAN,
							    LVDS_EEP,
							    LVDS_EEN,
							    LVDS_EDP,
							    LVDS_EDN,
							    LVDS_ECP,
							    LVDS_ECN,
							    LVDS_EBP,
							    LVDS_EBN,
							    LVDS_EAP,
							    LVDS_EAN पूर्ण;

अटल अचिन्हित पूर्णांक  lcd_d18_d2_drv_pads[]		= अणु LCD0_D18,
							    LCD0_D2 पूर्ण;

अटल अचिन्हित पूर्णांक  dsi_all_drv_pads[]			= अणु DSI_DP0,
							    DSI_DN0,
							    DSI_DP2,
							    DSI_DN2,
							    DSI_DP3,
							    DSI_DN3,
							    DSI_DP1,
							    DSI_DN1,
							    DSI_CP,
							    DSI_CN पूर्ण;

अटल अचिन्हित पूर्णांक  sd0_d0_d3_drv_pads[]		= अणु SD0_D0,
							    SD0_D1,
							    SD0_D2,
							    SD0_D3 पूर्ण;

अटल अचिन्हित पूर्णांक  sd0_cmd_drv_pads[]			= अणु SD0_CMD पूर्ण;

अटल अचिन्हित पूर्णांक  sd0_clk_drv_pads[]			= अणु SD0_CLK पूर्ण;

अटल अचिन्हित पूर्णांक  spi0_all_drv_pads[]		= अणु SPI0_SS,
							    SPI0_MISO पूर्ण;

/*PAD_DRV2*/
अटल अचिन्हित पूर्णांक  uart0_rx_drv_pads[]		= अणु UART0_RX पूर्ण;

अटल अचिन्हित पूर्णांक  uart0_tx_drv_pads[]		= अणु UART0_TX पूर्ण;

अटल अचिन्हित पूर्णांक  uart2_all_drv_pads[]		= अणु UART2_RX,
							    UART2_TX,
							    UART2_RTSB,
							    UART2_CTSB पूर्ण;

अटल अचिन्हित पूर्णांक  i2c0_all_drv_pads[]		= अणु I2C0_SCLK,
							    I2C0_SDATA पूर्ण;

अटल अचिन्हित पूर्णांक  i2c12_all_drv_pads[]		= अणु I2C1_SCLK,
							    I2C1_SDATA,
							    I2C2_SCLK,
							    I2C2_SDATA पूर्ण;

अटल अचिन्हित पूर्णांक  sens0_pclk_drv_pads[]		= अणु SENSOR0_PCLK पूर्ण;

अटल अचिन्हित पूर्णांक  sens0_ckout_drv_pads[]		= अणु SENSOR0_CKOUT पूर्ण;

अटल अचिन्हित पूर्णांक  uart3_all_drv_pads[]		= अणु UART3_RX,
							    UART3_TX,
							    UART3_RTSB,
							    UART3_CTSB पूर्ण;

/* all pinctrl groups of S700 board */
अटल स्थिर काष्ठा owl_pingroup s700_groups[] = अणु
	MUX_PG(rgmii_txd23_mfp, 0, 28, 2),
	MUX_PG(rgmii_rxd2_mfp, 0, 26, 2),
	MUX_PG(rgmii_rxd3_mfp, 0, 26, 2),
	MUX_PG(lcd0_d18_mfp, 0, 23, 3),
	MUX_PG(rgmii_txd01_mfp, 0, 20, 3),
	MUX_PG(rgmii_txd0_mfp, 0, 16, 3),
	MUX_PG(rgmii_txd1_mfp, 0, 16, 3),
	MUX_PG(rgmii_txen_mfp, 0, 13, 3),
	MUX_PG(rgmii_rxen_mfp, 0, 13, 3),
	MUX_PG(rgmii_rxd1_mfp, 0, 8, 3),
	MUX_PG(rgmii_rxd0_mfp, 0, 8, 3),
	MUX_PG(rgmii_ref_clk_mfp, 0, 6, 2),
	MUX_PG(i2s_d0_mfp, 0, 5, 1),
	MUX_PG(i2s_pcm1_mfp, 0, 3, 2),
	MUX_PG(i2s0_pcm0_mfp, 0, 1, 2),
	MUX_PG(i2s1_pcm0_mfp, 0, 1, 2),
	MUX_PG(i2s_d1_mfp, 0, 0, 1),
	MUX_PG(ks_in2_mfp, 1, 29, 3),
	MUX_PG(ks_in1_mfp, 1, 29, 3),
	MUX_PG(ks_in0_mfp, 1, 29, 3),
	MUX_PG(ks_in3_mfp, 1, 26, 3),
	MUX_PG(ks_out0_mfp, 1, 26, 3),
	MUX_PG(ks_out1_mfp, 1, 26, 3),
	MUX_PG(ks_out2_mfp, 1, 23, 3),
	MUX_PG(lvds_o_pn_mfp, 1, 21, 2),
	MUX_PG(dsi_dn0_mfp, 1, 19, 2),
	MUX_PG(dsi_dp2_mfp, 1, 17, 2),
	MUX_PG(lcd0_d2_mfp, 1, 14, 3),
	MUX_PG(dsi_dp3_mfp, 1, 12, 2),
	MUX_PG(dsi_dn3_mfp, 1, 10, 2),
	MUX_PG(dsi_dp0_mfp, 1, 7, 3),
	MUX_PG(lvds_ee_pn_mfp, 1, 5, 2),
	MUX_PG(uart2_rx_tx_mfp, 1, 3, 2),
	MUX_PG(spi0_i2c_pcm_mfp, 1, 0, 3),
	MUX_PG(dsi_dnp1_cp_d2_mfp, 2, 29, 2),
	MUX_PG(dsi_dnp1_cp_d17_mfp, 2, 29, 2),
	MUX_PG(lvds_e_pn_mfp, 2, 27, 2),
	MUX_PG(dsi_dn2_mfp, 2, 24, 3),
	MUX_PG(uart2_rtsb_mfp, 2, 23, 1),
	MUX_PG(uart2_ctsb_mfp, 2, 22, 1),
	MUX_PG(uart3_rtsb_mfp, 2, 21, 1),
	MUX_PG(uart3_ctsb_mfp, 2, 20, 1),
	MUX_PG(sd0_d0_mfp, 2, 17, 3),
	MUX_PG(sd0_d1_mfp, 2, 14, 3),
	MUX_PG(sd0_d2_d3_mfp, 2, 11, 3),
	MUX_PG(sd1_d0_d3_mfp, 2, 9, 2),
	MUX_PG(sd0_cmd_mfp, 2, 7, 2),
	MUX_PG(sd0_clk_mfp, 2, 5, 2),
	MUX_PG(sd1_cmd_mfp, 2, 3, 2),
	MUX_PG(uart0_rx_mfp, 2, 0, 3),
	MUX_PG(clko_25m_mfp, 3, 30, 1),
	MUX_PG(csi_cn_cp_mfp, 3, 28, 2),
	MUX_PG(sens0_ckout_mfp, 3, 22, 2),
	MUX_PG(uart0_tx_mfp, 3, 19, 3),
	MUX_PG(i2c0_mfp, 3, 16, 3),
	MUX_PG(csi_dn_dp_mfp, 3, 14, 2),
	MUX_PG(sen0_pclk_mfp, 3, 12, 2),
	MUX_PG(pcm1_in_mfp, 3, 10, 2),
	MUX_PG(pcm1_clk_mfp, 3, 8, 2),
	MUX_PG(pcm1_sync_mfp, 3, 6, 2),
	MUX_PG(pcm1_out_mfp, 3, 4, 2),
	MUX_PG(dnand_data_wr_mfp, 3, 3, 1),
	MUX_PG(dnand_acle_ce0_mfp, 3, 2, 1),
	MUX_PG(nand_ceb2_mfp, 3, 0, 2),
	MUX_PG(nand_ceb3_mfp, 3, 0, 2),

	DRV_PG(sirq_drv, 0, 28, 2),
	DRV_PG(rgmii_txd23_drv, 0, 26, 2),
	DRV_PG(rgmii_rxd23_drv, 0, 24, 2),
	DRV_PG(rgmii_txd01_txen_drv, 0, 22, 2),
	DRV_PG(rgmii_rxer_drv, 0, 20, 2),
	DRV_PG(rgmii_crs_drv, 0, 18, 2),
	DRV_PG(rgmii_rxd10_drv, 0, 16, 2),
	DRV_PG(rgmii_ref_clk_drv, 0, 14, 2),
	DRV_PG(smi_mdc_mdio_drv, 0, 12, 2),
	DRV_PG(i2s_d0_drv, 0, 10, 2),
	DRV_PG(i2s_bclk0_drv, 0, 8, 2),
	DRV_PG(i2s3_drv, 0, 6, 2),
	DRV_PG(i2s13_drv, 0, 4, 2),
	DRV_PG(pcm1_drv, 0, 2, 2),
	DRV_PG(ks_in_drv, 0, 0, 2),
	DRV_PG(ks_out_drv, 1, 30, 2),
	DRV_PG(lvds_all_drv, 1, 28, 2),
	DRV_PG(lcd_d18_d2_drv, 1, 26, 2),
	DRV_PG(dsi_all_drv, 1, 24, 2),
	DRV_PG(sd0_d0_d3_drv, 1, 22, 2),
	DRV_PG(sd0_cmd_drv, 1, 18, 2),
	DRV_PG(sd0_clk_drv, 1, 16, 2),
	DRV_PG(spi0_all_drv, 1, 10, 2),
	DRV_PG(uart0_rx_drv, 2, 30, 2),
	DRV_PG(uart0_tx_drv, 2, 28, 2),
	DRV_PG(uart2_all_drv, 2, 26, 2),
	DRV_PG(i2c0_all_drv, 2, 23, 2),
	DRV_PG(i2c12_all_drv, 2, 21, 2),
	DRV_PG(sens0_pclk_drv, 2, 18, 2),
	DRV_PG(sens0_ckout_drv, 2, 12, 2),
	DRV_PG(uart3_all_drv, 2, 2, 2),
पूर्ण;

अटल स्थिर अक्षर * स्थिर nor_groups[] = अणु
	"lcd0_d18_mfp",
	"i2s_d0_mfp",
	"i2s0_pcm0_mfp",
	"i2s1_pcm0_mfp",
	"i2s_d1_mfp",
	"ks_in2_mfp",
	"ks_in1_mfp",
	"ks_in0_mfp",
	"ks_in3_mfp",
	"ks_out0_mfp",
	"ks_out1_mfp",
	"ks_out2_mfp",
	"lcd0_d2_mfp",
	"lvds_ee_pn_mfp",
	"uart2_rx_tx_mfp",
	"spi0_i2c_pcm_mfp",
	"lvds_e_pn_mfp",
	"sd0_d0_mfp",
	"sd0_d1_mfp",
	"sd0_d2_d3_mfp",
	"sd1_d0_d3_mfp",
	"sd0_cmd_mfp",
	"sd1_cmd_mfp",
	"sens0_ckout_mfp",
	"sen0_pclk_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर eth_rmii_groups[] = अणु
	"rgmii_txd23_mfp",
	"rgmii_rxd2_mfp",
	"rgmii_rxd3_mfp",
	"rgmii_txd01_mfp",
	"rgmii_txd0_mfp",
	"rgmii_txd1_mfp",
	"rgmii_txen_mfp",
	"rgmii_rxen_mfp",
	"rgmii_rxd1_mfp",
	"rgmii_rxd0_mfp",
	"rgmii_ref_clk_mfp",
	"eth_smi_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर eth_smii_groups[] = अणु
	"rgmii_txd0_mfp",
	"rgmii_txd1_mfp",
	"rgmii_rxd0_mfp",
	"rgmii_rxd1_mfp",
	"rgmii_ref_clk_mfp",
	"eth_smi_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi0_groups[] = अणु
	"dsi_dn0_mfp",
	"dsi_dp2_mfp",
	"dsi_dp0_mfp",
	"uart2_rx_tx_mfp",
	"spi0_i2c_pcm_mfp",
	"dsi_dn2_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi1_groups[] = अणु
	"uart0_rx_mfp",
	"uart0_tx_mfp",
	"i2c0_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi2_groups[] = अणु
	"rgmii_txd01_mfp",
	"rgmii_txd0_mfp",
	"rgmii_txd1_mfp",
	"rgmii_ref_clk_mfp",
	"dnand_acle_ce0_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi3_groups[] = अणु
	"rgmii_txen_mfp",
	"rgmii_rxen_mfp",
	"rgmii_rxd1_mfp",
	"rgmii_rxd0_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sens0_groups[] = अणु
	"csi_cn_cp_mfp",
	"sens0_ckout_mfp",
	"csi_dn_dp_mfp",
	"sen0_pclk_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sens1_groups[] = अणु
	"lcd0_d18_mfp",
	"ks_in2_mfp",
	"ks_in1_mfp",
	"ks_in0_mfp",
	"ks_in3_mfp",
	"ks_out0_mfp",
	"ks_out1_mfp",
	"ks_out2_mfp",
	"sens0_ckout_mfp",
	"pcm1_in_mfp",
	"pcm1_clk_mfp",
	"pcm1_sync_mfp",
	"pcm1_out_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart0_groups[] = अणु
	"uart2_rtsb_mfp",
	"uart2_ctsb_mfp",
	"uart0_rx_mfp",
	"uart0_tx_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart1_groups[] = अणु
	"sd0_d2_d3_mfp",
	"i2c0_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart2_groups[] = अणु
	"rgmii_txen_mfp",
	"rgmii_rxen_mfp",
	"rgmii_rxd1_mfp",
	"rgmii_rxd0_mfp",
	"dsi_dn0_mfp",
	"dsi_dp2_mfp",
	"dsi_dp0_mfp",
	"uart2_rx_tx_mfp",
	"dsi_dn2_mfp",
	"uart2_rtsb_mfp",
	"uart2_ctsb_mfp",
	"sd0_d0_mfp",
	"sd0_d1_mfp",
	"sd0_d2_d3_mfp",
	"uart0_rx_mfp",
	"uart0_tx_mfp",
	"i2c0_mfp",
	"uart2_dummy"
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart3_groups[] = अणु
	"rgmii_txd23_mfp",
	"rgmii_rxd2_mfp",
	"rgmii_rxd3_mfp",
	"uart3_rtsb_mfp",
	"uart3_ctsb_mfp",
	"uart3_dummy"
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart4_groups[] = अणु
	"rgmii_txd01_mfp",
	"rgmii_ref_clk_mfp",
	"ks_out0_mfp",
	"ks_out1_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart5_groups[] = अणु
	"rgmii_rxd1_mfp",
	"rgmii_rxd0_mfp",
	"ks_out0_mfp",
	"ks_out2_mfp",
	"uart3_rtsb_mfp",
	"uart3_ctsb_mfp",
	"sd0_d0_mfp",
	"sd0_d1_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart6_groups[] = अणु
	"rgmii_txd0_mfp",
	"rgmii_txd1_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2s0_groups[] = अणु
	"i2s_d0_mfp",
	"i2s_pcm1_mfp",
	"i2s0_pcm0_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2s1_groups[] = अणु
	"i2s1_pcm0_mfp",
	"i2s_d1_mfp",
	"i2s1_dummy",
	"spi0_i2c_pcm_mfp",
	"uart0_rx_mfp",
	"uart0_tx_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcm1_groups[] = अणु
	"i2s_pcm1_mfp",
	"spi0_i2c_pcm_mfp",
	"uart0_rx_mfp",
	"uart0_tx_mfp",
	"pcm1_in_mfp",
	"pcm1_clk_mfp",
	"pcm1_sync_mfp",
	"pcm1_out_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcm0_groups[] = अणु
	"i2s0_pcm0_mfp",
	"i2s1_pcm0_mfp",
	"uart2_rx_tx_mfp",
	"spi0_i2c_pcm_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर ks_groups[] = अणु
	"ks_in2_mfp",
	"ks_in1_mfp",
	"ks_in0_mfp",
	"ks_in3_mfp",
	"ks_out0_mfp",
	"ks_out1_mfp",
	"ks_out2_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर jtag_groups[] = अणु
	"ks_in2_mfp",
	"ks_in1_mfp",
	"ks_in0_mfp",
	"ks_in3_mfp",
	"ks_out1_mfp",
	"sd0_d0_mfp",
	"sd0_d2_d3_mfp",
	"sd0_cmd_mfp",
	"sd0_clk_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm0_groups[] = अणु
	"rgmii_rxd2_mfp",
	"rgmii_txen_mfp",
	"ks_in2_mfp",
	"sen0_pclk_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm1_groups[] = अणु
	"rgmii_rxen_mfp",
	"ks_in1_mfp",
	"ks_in3_mfp",
	"sens0_ckout_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm2_groups[] = अणु
	"lcd0_d18_mfp",
	"rgmii_rxd3_mfp",
	"rgmii_rxd1_mfp",
	"ks_out0_mfp",
	"ks_out2_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm3_groups[] = अणु
	"rgmii_rxd0_mfp",
	"ks_out1_mfp",
	"lcd0_d2_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm4_groups[] = अणु
	"lcd0_d18_mfp",
	"rgmii_txd01_mfp",
	"rgmii_txd0_mfp",
	"ks_in0_mfp",
	"pcm1_in_mfp",
	"nand_ceb3_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm5_groups[] = अणु
	"rgmii_txd1_mfp",
	"ks_in1_mfp",
	"pcm1_clk_mfp",
	"nand_ceb2_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर p0_groups[] = अणु
	"ks_in2_mfp",
	"ks_in0_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sd0_groups[] = अणु
	"ks_out0_mfp",
	"ks_out1_mfp",
	"ks_out2_mfp",
	"lcd0_d2_mfp",
	"dsi_dp3_mfp",
	"dsi_dp0_mfp",
	"sd0_d0_mfp",
	"sd0_d1_mfp",
	"sd0_d2_d3_mfp",
	"sd1_d0_d3_mfp",
	"sd0_cmd_mfp",
	"sd0_clk_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sd1_groups[] = अणु
	"dsi_dp2_mfp",
	"mfp1_16_14_mfp",
	"lcd0_d2_mfp",
	"mfp1_16_14_d17_mfp",
	"dsi_dp3_mfp",
	"dsi_dn3_mfp",
	"dsi_dnp1_cp_d2_mfp",
	"dsi_dnp1_cp_d17_mfp",
	"dsi_dn2_mfp",
	"sd1_d0_d3_mfp",
	"sd1_cmd_mfp",
	"sd1_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sd2_groups[] = अणु
	"dnand_data_wr_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c0_groups[] = अणु
	"uart0_rx_mfp",
	"uart0_tx_mfp",
	"i2c0_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c1_groups[] = अणु
	"i2c0_mfp",
	"i2c1_dummy"
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c2_groups[] = अणु
	"i2c2_dummy"
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c3_groups[] = अणु
	"uart2_rx_tx_mfp",
	"pcm1_sync_mfp",
	"pcm1_out_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर lvds_groups[] = अणु
	"lvds_o_pn_mfp",
	"lvds_ee_pn_mfp",
	"lvds_e_pn_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर bt_groups[] = अणु
	"i2s_pcm1_mfp",
	"i2s0_pcm0_mfp",
	"i2s1_pcm0_mfp",
	"ks_in2_mfp",
	"ks_in1_mfp",
	"ks_in0_mfp",
	"ks_in3_mfp",
	"ks_out0_mfp",
	"ks_out1_mfp",
	"ks_out2_mfp",
	"lvds_o_pn_mfp",
	"lvds_ee_pn_mfp",
	"pcm1_in_mfp",
	"pcm1_clk_mfp",
	"pcm1_sync_mfp",
	"pcm1_out_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर lcd0_groups[] = अणु
	"lcd0_d18_mfp",
	"lcd0_d2_mfp",
	"mfp1_16_14_d17_mfp",
	"lvds_o_pn_mfp",
	"dsi_dp3_mfp",
	"dsi_dn3_mfp",
	"lvds_ee_pn_mfp",
	"dsi_dnp1_cp_d2_mfp",
	"dsi_dnp1_cp_d17_mfp",
	"lvds_e_pn_mfp",
पूर्ण;


अटल स्थिर अक्षर * स्थिर usb30_groups[] = अणु
	"ks_in1_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर clko_25m_groups[] = अणु
	"clko_25m_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mipi_csi_groups[] = अणु
	"csi_cn_cp_mfp",
	"csi_dn_dp_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर dsi_groups[] = अणु
	"dsi_dn0_mfp",
	"dsi_dp2_mfp",
	"dsi_dp3_mfp",
	"dsi_dn3_mfp",
	"dsi_dp0_mfp",
	"dsi_dnp1_cp_d2_mfp",
	"dsi_dnp1_cp_d17_mfp",
	"dsi_dn2_mfp",
	"dsi_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nand_groups[] = अणु
	"dnand_data_wr_mfp",
	"dnand_acle_ce0_mfp",
	"nand_ceb2_mfp",
	"nand_ceb3_mfp",
	"nand_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spdअगर_groups[] = अणु
	"uart0_tx_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sirq0_groups[] = अणु
	"sirq0_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sirq1_groups[] = अणु
	"sirq1_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sirq2_groups[] = अणु
	"sirq2_dummy",
पूर्ण;

अटल स्थिर काष्ठा owl_pinmux_func s700_functions[] = अणु
	[S700_MUX_NOR] = FUNCTION(nor),
	[S700_MUX_ETH_RGMII] = FUNCTION(eth_rmii),
	[S700_MUX_ETH_SGMII] = FUNCTION(eth_smii),
	[S700_MUX_SPI0] = FUNCTION(spi0),
	[S700_MUX_SPI1] = FUNCTION(spi1),
	[S700_MUX_SPI2] = FUNCTION(spi2),
	[S700_MUX_SPI3] = FUNCTION(spi3),
	[S700_MUX_SENS0] = FUNCTION(sens0),
	[S700_MUX_SENS1] = FUNCTION(sens1),
	[S700_MUX_UART0] = FUNCTION(uart0),
	[S700_MUX_UART1] = FUNCTION(uart1),
	[S700_MUX_UART2] = FUNCTION(uart2),
	[S700_MUX_UART3] = FUNCTION(uart3),
	[S700_MUX_UART4] = FUNCTION(uart4),
	[S700_MUX_UART5] = FUNCTION(uart5),
	[S700_MUX_UART6] = FUNCTION(uart6),
	[S700_MUX_I2S0] = FUNCTION(i2s0),
	[S700_MUX_I2S1] = FUNCTION(i2s1),
	[S700_MUX_PCM1] = FUNCTION(pcm1),
	[S700_MUX_PCM0] = FUNCTION(pcm0),
	[S700_MUX_KS] = FUNCTION(ks),
	[S700_MUX_JTAG] = FUNCTION(jtag),
	[S700_MUX_PWM0] = FUNCTION(pwm0),
	[S700_MUX_PWM1] = FUNCTION(pwm1),
	[S700_MUX_PWM2] = FUNCTION(pwm2),
	[S700_MUX_PWM3] = FUNCTION(pwm3),
	[S700_MUX_PWM4] = FUNCTION(pwm4),
	[S700_MUX_PWM5] = FUNCTION(pwm5),
	[S700_MUX_P0] = FUNCTION(p0),
	[S700_MUX_SD0] = FUNCTION(sd0),
	[S700_MUX_SD1] = FUNCTION(sd1),
	[S700_MUX_SD2] = FUNCTION(sd2),
	[S700_MUX_I2C0] = FUNCTION(i2c0),
	[S700_MUX_I2C1] = FUNCTION(i2c1),
	[S700_MUX_I2C2] = FUNCTION(i2c2),
	[S700_MUX_I2C3] = FUNCTION(i2c3),
	[S700_MUX_DSI] = FUNCTION(dsi),
	[S700_MUX_LVDS] = FUNCTION(lvds),
	[S700_MUX_USB30] = FUNCTION(usb30),
	[S700_MUX_CLKO_25M] = FUNCTION(clko_25m),
	[S700_MUX_MIPI_CSI] = FUNCTION(mipi_csi),
	[S700_MUX_न_अंकD] = FUNCTION(nand),
	[S700_MUX_SPDIF] = FUNCTION(spdअगर),
	[S700_MUX_SIRQ0] = FUNCTION(sirq0),
	[S700_MUX_SIRQ1] = FUNCTION(sirq1),
	[S700_MUX_SIRQ2] = FUNCTION(sirq2),
	[S700_MUX_BT] = FUNCTION(bt),
	[S700_MUX_LCD0] = FUNCTION(lcd0),
पूर्ण;

/* PAD_ST0 */
अटल PAD_ST_CONF(UART2_TX, 0, 31, 1);
अटल PAD_ST_CONF(I2C0_SDATA, 0, 30, 1);
अटल PAD_ST_CONF(UART0_RX, 0, 29, 1);
अटल PAD_ST_CONF(I2S_MCLK1, 0, 23, 1);
अटल PAD_ST_CONF(ETH_REF_CLK, 0, 22, 1);
अटल PAD_ST_CONF(ETH_TXEN, 0, 21, 1);
अटल PAD_ST_CONF(ETH_TXD0, 0, 20, 1);
अटल PAD_ST_CONF(I2S_LRCLK1, 0, 19, 1);
अटल PAD_ST_CONF(DSI_DP0, 0, 16, 1);
अटल PAD_ST_CONF(DSI_DN0, 0, 15, 1);
अटल PAD_ST_CONF(UART0_TX, 0, 14, 1);
अटल PAD_ST_CONF(SD0_CLK, 0, 12, 1);
अटल PAD_ST_CONF(KS_IN0, 0, 11, 1);
अटल PAD_ST_CONF(SENSOR0_PCLK, 0, 9, 1);
अटल PAD_ST_CONF(I2C0_SCLK, 0, 7, 1);
अटल PAD_ST_CONF(KS_OUT0, 0, 6, 1);
अटल PAD_ST_CONF(KS_OUT1, 0, 5, 1);
अटल PAD_ST_CONF(KS_OUT2, 0, 4, 1);
अटल PAD_ST_CONF(ETH_TXD3, 0, 3, 1);
अटल PAD_ST_CONF(ETH_TXD2, 0, 2, 1);

/* PAD_ST1 */
अटल PAD_ST_CONF(DSI_DP2, 1, 31, 1);
अटल PAD_ST_CONF(DSI_DN2, 1, 30, 1);
अटल PAD_ST_CONF(I2S_LRCLK0, 1, 29, 1);
अटल PAD_ST_CONF(UART3_CTSB, 1, 27, 1);
अटल PAD_ST_CONF(UART3_RTSB, 1, 26, 1);
अटल PAD_ST_CONF(UART3_RX, 1, 25, 1);
अटल PAD_ST_CONF(UART2_RTSB, 1, 24, 1);
अटल PAD_ST_CONF(UART2_CTSB, 1, 23, 1);
अटल PAD_ST_CONF(UART2_RX, 1, 22, 1);
अटल PAD_ST_CONF(ETH_RXD0, 1, 21, 1);
अटल PAD_ST_CONF(ETH_RXD1, 1, 20, 1);
अटल PAD_ST_CONF(ETH_CRS_DV, 1, 19, 1);
अटल PAD_ST_CONF(ETH_RXER, 1, 18, 1);
अटल PAD_ST_CONF(ETH_TXD1, 1, 17, 1);
अटल PAD_ST_CONF(LVDS_OAP, 1, 12, 1);
अटल PAD_ST_CONF(PCM1_CLK, 1, 11, 1);
अटल PAD_ST_CONF(PCM1_IN, 1, 10, 1);
अटल PAD_ST_CONF(PCM1_SYNC, 1, 9, 1);
अटल PAD_ST_CONF(I2C1_SCLK, 1, 8, 1);
अटल PAD_ST_CONF(I2C1_SDATA, 1, 7, 1);
अटल PAD_ST_CONF(I2C2_SCLK, 1, 6, 1);
अटल PAD_ST_CONF(I2C2_SDATA, 1, 5, 1);

अटल PAD_ST_CONF(SPI0_MISO, 1, 3, 1);
अटल PAD_ST_CONF(SPI0_SS, 1, 2, 1);
अटल PAD_ST_CONF(I2S_BCLK0, 1, 1, 1);
अटल PAD_ST_CONF(I2S_MCLK0, 1, 0, 1);

/* PAD_PULLCTL0 */
अटल PAD_PULLCTL_CONF(PCM1_SYNC, 0, 30, 1);
अटल PAD_PULLCTL_CONF(PCM1_OUT, 0, 29, 1);
अटल PAD_PULLCTL_CONF(KS_OUT2, 0, 28, 1);
अटल PAD_PULLCTL_CONF(LCD0_D2, 0, 27, 1);
अटल PAD_PULLCTL_CONF(DSI_DN3, 0, 26, 1);
अटल PAD_PULLCTL_CONF(ETH_RXER, 0, 16, 1);
अटल PAD_PULLCTL_CONF(SIRQ0, 0, 14, 2);
अटल PAD_PULLCTL_CONF(SIRQ1, 0, 12, 2);
अटल PAD_PULLCTL_CONF(SIRQ2, 0, 10, 2);
अटल PAD_PULLCTL_CONF(I2C0_SDATA, 0, 9, 1);
अटल PAD_PULLCTL_CONF(I2C0_SCLK, 0, 8, 1);
अटल PAD_PULLCTL_CONF(KS_IN0, 0, 7, 1);
अटल PAD_PULLCTL_CONF(KS_IN1, 0, 6, 1);
अटल PAD_PULLCTL_CONF(KS_IN2, 0, 5, 1);
अटल PAD_PULLCTL_CONF(KS_IN3, 0, 4, 1);
अटल PAD_PULLCTL_CONF(KS_OUT0, 0, 2, 1);
अटल PAD_PULLCTL_CONF(KS_OUT1, 0, 1, 1);
अटल PAD_PULLCTL_CONF(DSI_DP1, 0, 0, 1);

/* PAD_PULLCTL1 */
अटल PAD_PULLCTL_CONF(SD0_D0, 1, 17, 1);
अटल PAD_PULLCTL_CONF(SD0_D1, 1, 16, 1);
अटल PAD_PULLCTL_CONF(SD0_D2, 1, 15, 1);
अटल PAD_PULLCTL_CONF(SD0_D3, 1, 14, 1);
अटल PAD_PULLCTL_CONF(SD0_CMD, 1, 13, 1);
अटल PAD_PULLCTL_CONF(SD0_CLK, 1, 12, 1);
अटल PAD_PULLCTL_CONF(UART0_RX, 1, 2, 1);
अटल PAD_PULLCTL_CONF(UART0_TX, 1, 1, 1);
अटल PAD_PULLCTL_CONF(CLKO_25M, 1, 0, 1);

/* PAD_PULLCTL2 */
अटल PAD_PULLCTL_CONF(ETH_TXD2, 2, 18, 1);
अटल PAD_PULLCTL_CONF(ETH_TXD3, 2, 17, 1);
अटल PAD_PULLCTL_CONF(SPI0_SS, 2, 16, 1);
अटल PAD_PULLCTL_CONF(SPI0_MISO, 2, 15, 1);
अटल PAD_PULLCTL_CONF(I2C1_SDATA, 2, 10, 1);
अटल PAD_PULLCTL_CONF(I2C1_SCLK, 2, 9, 1);
अटल PAD_PULLCTL_CONF(I2C2_SDATA, 2, 8, 1);
अटल PAD_PULLCTL_CONF(I2C2_SCLK, 2, 7, 1);

/* Pad info table क्रम the pinmux subप्रणाली */
अटल स्थिर काष्ठा owl_padinfo s700_padinfo[NUM_PADS] = अणु
	[ETH_TXD0] = PAD_INFO_ST(ETH_TXD0),
	[ETH_TXD1] = PAD_INFO_ST(ETH_TXD1),
	[ETH_TXEN] = PAD_INFO_ST(ETH_TXEN),
	[ETH_RXER] = PAD_INFO_PULLCTL_ST(ETH_RXER),
	[ETH_CRS_DV] = PAD_INFO_ST(ETH_CRS_DV),
	[ETH_RXD1] = PAD_INFO_ST(ETH_RXD1),
	[ETH_RXD0] = PAD_INFO_ST(ETH_RXD0),
	[ETH_REF_CLK] = PAD_INFO_ST(ETH_REF_CLK),
	[ETH_MDC] = PAD_INFO(ETH_MDC),
	[ETH_MDIO] = PAD_INFO(ETH_MDIO),
	[SIRQ0] = PAD_INFO_PULLCTL(SIRQ0),
	[SIRQ1] = PAD_INFO_PULLCTL(SIRQ1),
	[SIRQ2] = PAD_INFO_PULLCTL(SIRQ2),
	[I2S_D0] = PAD_INFO(I2S_D0),
	[I2S_BCLK0] = PAD_INFO_ST(I2S_BCLK0),
	[I2S_LRCLK0] = PAD_INFO_ST(I2S_LRCLK0),
	[I2S_MCLK0] = PAD_INFO_ST(I2S_MCLK0),
	[I2S_D1] = PAD_INFO(I2S_D1),
	[I2S_BCLK1] = PAD_INFO(I2S_BCLK1),
	[I2S_LRCLK1] = PAD_INFO_ST(I2S_LRCLK1),
	[I2S_MCLK1] = PAD_INFO_ST(I2S_MCLK1),
	[KS_IN0] = PAD_INFO_PULLCTL_ST(KS_IN0),
	[KS_IN1] = PAD_INFO_PULLCTL(KS_IN1),
	[KS_IN2] = PAD_INFO_PULLCTL(KS_IN2),
	[KS_IN3] = PAD_INFO_PULLCTL(KS_IN3),
	[KS_OUT0] = PAD_INFO_PULLCTL_ST(KS_OUT0),
	[KS_OUT1] = PAD_INFO_PULLCTL_ST(KS_OUT1),
	[KS_OUT2] = PAD_INFO_PULLCTL_ST(KS_OUT2),
	[LVDS_OEP] = PAD_INFO(LVDS_OEP),
	[LVDS_OEN] = PAD_INFO(LVDS_OEN),
	[LVDS_ODP] = PAD_INFO(LVDS_ODP),
	[LVDS_ODN] = PAD_INFO(LVDS_ODN),
	[LVDS_OCP] = PAD_INFO(LVDS_OCP),
	[LVDS_OCN] = PAD_INFO(LVDS_OCN),
	[LVDS_OBP] = PAD_INFO(LVDS_OBP),
	[LVDS_OBN] = PAD_INFO(LVDS_OBN),
	[LVDS_OAP] = PAD_INFO_ST(LVDS_OAP),
	[LVDS_OAN] = PAD_INFO(LVDS_OAN),
	[LVDS_EEP] = PAD_INFO(LVDS_EEP),
	[LVDS_EEN] = PAD_INFO(LVDS_EEN),
	[LVDS_EDP] = PAD_INFO(LVDS_EDP),
	[LVDS_EDN] = PAD_INFO(LVDS_EDN),
	[LVDS_ECP] = PAD_INFO(LVDS_ECP),
	[LVDS_ECN] = PAD_INFO(LVDS_ECN),
	[LVDS_EBP] = PAD_INFO(LVDS_EBP),
	[LVDS_EBN] = PAD_INFO(LVDS_EBN),
	[LVDS_EAP] = PAD_INFO(LVDS_EAP),
	[LVDS_EAN] = PAD_INFO(LVDS_EAN),
	[LCD0_D18] = PAD_INFO(LCD0_D18),
	[LCD0_D2] = PAD_INFO_PULLCTL(LCD0_D2),
	[DSI_DP3] = PAD_INFO(DSI_DP3),
	[DSI_DN3] = PAD_INFO_PULLCTL(DSI_DN3),
	[DSI_DP1] = PAD_INFO_PULLCTL(DSI_DP1),
	[DSI_DN1] = PAD_INFO(DSI_DN1),
	[DSI_DP0] = PAD_INFO_ST(DSI_DP0),
	[DSI_DN0] = PAD_INFO_ST(DSI_DN0),
	[DSI_DP2] = PAD_INFO_ST(DSI_DP2),
	[DSI_DN2] = PAD_INFO_ST(DSI_DN2),
	[SD0_D0] = PAD_INFO_PULLCTL(SD0_D0),
	[SD0_D1] = PAD_INFO_PULLCTL(SD0_D1),
	[SD0_D2] = PAD_INFO_PULLCTL(SD0_D2),
	[SD0_D3] = PAD_INFO_PULLCTL(SD0_D3),
	[SD0_CMD] = PAD_INFO_PULLCTL(SD0_CMD),
	[SD0_CLK] = PAD_INFO_PULLCTL_ST(SD0_CLK),
	[SD1_CLK] = PAD_INFO(SD1_CLK),
	[SPI0_SS] = PAD_INFO_PULLCTL_ST(SPI0_SS),
	[SPI0_MISO] = PAD_INFO_PULLCTL_ST(SPI0_MISO),
	[UART0_RX] = PAD_INFO_PULLCTL_ST(UART0_RX),
	[UART0_TX] = PAD_INFO_PULLCTL_ST(UART0_TX),
	[I2C0_SCLK] = PAD_INFO_PULLCTL_ST(I2C0_SCLK),
	[I2C0_SDATA] = PAD_INFO_PULLCTL_ST(I2C0_SDATA),
	[SENSOR0_PCLK] = PAD_INFO_ST(SENSOR0_PCLK),
	[SENSOR0_CKOUT] = PAD_INFO(SENSOR0_CKOUT),
	[Dन_अंकD_ALE] = PAD_INFO(Dन_अंकD_ALE),
	[Dन_अंकD_CLE] = PAD_INFO(Dन_अंकD_CLE),
	[Dन_अंकD_CEB0] = PAD_INFO(Dन_अंकD_CEB0),
	[Dन_अंकD_CEB1] = PAD_INFO(Dन_अंकD_CEB1),
	[Dन_अंकD_CEB2] = PAD_INFO(Dन_अंकD_CEB2),
	[Dन_अंकD_CEB3] = PAD_INFO(Dन_अंकD_CEB3),
	[UART2_RX] = PAD_INFO_ST(UART2_RX),
	[UART2_TX] = PAD_INFO_ST(UART2_TX),
	[UART2_RTSB] = PAD_INFO_ST(UART2_RTSB),
	[UART2_CTSB] = PAD_INFO_ST(UART2_CTSB),
	[UART3_RX] = PAD_INFO_ST(UART3_RX),
	[UART3_TX] = PAD_INFO(UART3_TX),
	[UART3_RTSB] = PAD_INFO_ST(UART3_RTSB),
	[UART3_CTSB] = PAD_INFO_ST(UART3_CTSB),
	[PCM1_IN] = PAD_INFO_ST(PCM1_IN),
	[PCM1_CLK] = PAD_INFO_ST(PCM1_CLK),
	[PCM1_SYNC] = PAD_INFO_PULLCTL_ST(PCM1_SYNC),
	[PCM1_OUT] = PAD_INFO_PULLCTL(PCM1_OUT),
	[I2C1_SCLK] = PAD_INFO_PULLCTL_ST(I2C1_SCLK),
	[I2C1_SDATA] = PAD_INFO_PULLCTL_ST(I2C1_SDATA),
	[I2C2_SCLK] = PAD_INFO_PULLCTL_ST(I2C2_SCLK),
	[I2C2_SDATA] = PAD_INFO_PULLCTL_ST(I2C2_SDATA),
	[CSI_DN0] = PAD_INFO(CSI_DN0),
	[CSI_DP0] = PAD_INFO(CSI_DP0),
	[CSI_DN1] = PAD_INFO(CSI_DN1),
	[CSI_DP1] = PAD_INFO(CSI_DP1),
	[CSI_CN] = PAD_INFO(CSI_CN),
	[CSI_CP] = PAD_INFO(CSI_CP),
	[CSI_DN2] = PAD_INFO(CSI_DN2),
	[CSI_DP2] = PAD_INFO(CSI_DP2),
	[CSI_DN3] = PAD_INFO(CSI_DN3),
	[CSI_DP3] = PAD_INFO(CSI_DP3),
	[Dन_अंकD_WRB] = PAD_INFO(Dन_अंकD_WRB),
	[Dन_अंकD_RDB] = PAD_INFO(Dन_अंकD_RDB),
	[Dन_अंकD_RB0] = PAD_INFO(Dन_अंकD_RB0),
	[PORB] = PAD_INFO(PORB),
	[CLKO_25M] = PAD_INFO_PULLCTL(CLKO_25M),
	[BSEL] = PAD_INFO(BSEL),
	[PKG0] = PAD_INFO(PKG0),
	[PKG1] = PAD_INFO(PKG1),
	[PKG2] = PAD_INFO(PKG2),
	[PKG3] = PAD_INFO(PKG3),
	[ETH_TXD2] = PAD_INFO_PULLCTL_ST(ETH_TXD2),
	[ETH_TXD3] = PAD_INFO_PULLCTL_ST(ETH_TXD3),
पूर्ण;

अटल स्थिर काष्ठा owl_gpio_port s700_gpio_ports[] = अणु
	OWL_GPIO_PORT(A, 0x0000, 32, 0x0, 0x4, 0x8, 0x204, 0x208, 0x20C, 0x230, 0),
	OWL_GPIO_PORT(B, 0x000C, 32, 0x0, 0x4, 0x8, 0x204, 0x210, 0x214, 0x238, 1),
	OWL_GPIO_PORT(C, 0x0018, 32, 0x0, 0x4, 0x8, 0x204, 0x218, 0x21C, 0x240, 2),
	OWL_GPIO_PORT(D, 0x0024, 32, 0x0, 0x4, 0x8, 0x204, 0x220, 0x224, 0x248, 3),
	/* 0x24C (INTC_GPIOD_TYPE1) used to tweak the driver to handle generic */
	OWL_GPIO_PORT(E, 0x0030, 8, 0x0, 0x4, 0x8, 0x204, 0x228, 0x22C, 0x24C, 4),
पूर्ण;

क्रमागत s700_pinconf_pull अणु
	OWL_PINCONF_PULL_DOWN,
	OWL_PINCONF_PULL_UP,
पूर्ण;

अटल पूर्णांक s700_pad_pinconf_arg2val(स्थिर काष्ठा owl_padinfo *info,
				अचिन्हित पूर्णांक param,
				u32 *arg)
अणु
	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		*arg = OWL_PINCONF_PULL_DOWN;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		*arg = OWL_PINCONF_PULL_UP;
		अवरोध;
	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		*arg = (*arg >= 1 ? 1 : 0);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक s700_pad_pinconf_val2arg(स्थिर काष्ठा owl_padinfo *padinfo,
				अचिन्हित पूर्णांक param,
				u32 *arg)
अणु
	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_PULL_DOWN:
		*arg = *arg == OWL_PINCONF_PULL_DOWN;
		अवरोध;
	हाल PIN_CONFIG_BIAS_PULL_UP:
		*arg = *arg == OWL_PINCONF_PULL_UP;
		अवरोध;
	हाल PIN_CONFIG_INPUT_SCHMITT_ENABLE:
		*arg = *arg == 1;
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा owl_pinctrl_soc_data s700_pinctrl_data = अणु
	.padinfo = s700_padinfo,
	.pins = (स्थिर काष्ठा pinctrl_pin_desc *)s700_pads,
	.npins = ARRAY_SIZE(s700_pads),
	.functions = s700_functions,
	.nfunctions = ARRAY_SIZE(s700_functions),
	.groups = s700_groups,
	.ngroups = ARRAY_SIZE(s700_groups),
	.ngpios = NUM_GPIOS,
	.ports = s700_gpio_ports,
	.nports = ARRAY_SIZE(s700_gpio_ports),
	.padctl_arg2val = s700_pad_pinconf_arg2val,
	.padctl_val2arg = s700_pad_pinconf_val2arg,
पूर्ण;

अटल पूर्णांक s700_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस owl_pinctrl_probe(pdev, &s700_pinctrl_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id s700_pinctrl_of_match[] = अणु
	अणु .compatible = "actions,s700-pinctrl", पूर्ण,
	अणुपूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver s700_pinctrl_driver = अणु
	.probe = s700_pinctrl_probe,
	.driver = अणु
		.name = "pinctrl-s700",
		.of_match_table = of_match_ptr(s700_pinctrl_of_match),
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init s700_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&s700_pinctrl_driver);
पूर्ण
arch_initcall(s700_pinctrl_init);

अटल व्योम __निकास s700_pinctrl_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&s700_pinctrl_driver);
पूर्ण
module_निकास(s700_pinctrl_निकास);

MODULE_AUTHOR("Actions Semi Inc.");
MODULE_DESCRIPTION("Actions Semi S700 Soc Pinctrl Driver");
MODULE_LICENSE("GPL");
