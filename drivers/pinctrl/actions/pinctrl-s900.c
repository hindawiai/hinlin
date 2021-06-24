<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * OWL S900 Pinctrl driver
 *
 * Copyright (c) 2014 Actions Semi Inc.
 * Author: David Liu <liuwei@actions-semi.com>
 *
 * Copyright (c) 2018 Linaro Ltd.
 * Author: Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>
 */

#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pinctrl/pinctrl.h>
#समावेश <linux/pinctrl/pinconf-generic.h>
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
#घोषणा PAD_SR0			(0x0270)
#घोषणा PAD_SR1			(0x0274)
#घोषणा PAD_SR2			(0x0278)

#घोषणा _GPIOA(offset)		(offset)
#घोषणा _GPIOB(offset)		(32 + (offset))
#घोषणा _GPIOC(offset)		(64 + (offset))
#घोषणा _GPIOD(offset)		(76 + (offset))
#घोषणा _GPIOE(offset)		(106 + (offset))
#घोषणा _GPIOF(offset)		(138 + (offset))

#घोषणा NUM_GPIOS		(_GPIOF(7) + 1)
#घोषणा _PIN(offset)		(NUM_GPIOS + (offset))

#घोषणा ETH_TXD0		_GPIOA(0)
#घोषणा ETH_TXD1		_GPIOA(1)
#घोषणा ETH_TXEN		_GPIOA(2)
#घोषणा ETH_RXER		_GPIOA(3)
#घोषणा ETH_CRS_DV		_GPIOA(4)
#घोषणा ETH_RXD1		_GPIOA(5)
#घोषणा ETH_RXD0		_GPIOA(6)
#घोषणा ETH_REF_CLK		_GPIOA(7)
#घोषणा ETH_MDC			_GPIOA(8)
#घोषणा ETH_MDIO		_GPIOA(9)
#घोषणा SIRQ0			_GPIOA(10)
#घोषणा SIRQ1			_GPIOA(11)
#घोषणा SIRQ2			_GPIOA(12)
#घोषणा I2S_D0			_GPIOA(13)
#घोषणा I2S_BCLK0		_GPIOA(14)
#घोषणा I2S_LRCLK0		_GPIOA(15)
#घोषणा I2S_MCLK0		_GPIOA(16)
#घोषणा I2S_D1			_GPIOA(17)
#घोषणा I2S_BCLK1		_GPIOA(18)
#घोषणा I2S_LRCLK1		_GPIOA(19)
#घोषणा I2S_MCLK1		_GPIOA(20)
#घोषणा ERAM_A5			_GPIOA(21)
#घोषणा ERAM_A6			_GPIOA(22)
#घोषणा ERAM_A7			_GPIOA(23)
#घोषणा ERAM_A8			_GPIOA(24)
#घोषणा ERAM_A9			_GPIOA(25)
#घोषणा ERAM_A10		_GPIOA(26)
#घोषणा ERAM_A11		_GPIOA(27)
#घोषणा SD0_D0			_GPIOA(28)
#घोषणा SD0_D1			_GPIOA(29)
#घोषणा SD0_D2			_GPIOA(30)
#घोषणा SD0_D3			_GPIOA(31)

#घोषणा SD1_D0			_GPIOB(0)
#घोषणा SD1_D1			_GPIOB(1)
#घोषणा SD1_D2			_GPIOB(2)
#घोषणा SD1_D3			_GPIOB(3)
#घोषणा SD0_CMD			_GPIOB(4)
#घोषणा SD0_CLK			_GPIOB(5)
#घोषणा SD1_CMD			_GPIOB(6)
#घोषणा SD1_CLK			_GPIOB(7)
#घोषणा SPI0_SCLK		_GPIOB(8)
#घोषणा SPI0_SS			_GPIOB(9)
#घोषणा SPI0_MISO		_GPIOB(10)
#घोषणा SPI0_MOSI		_GPIOB(11)
#घोषणा UART0_RX		_GPIOB(12)
#घोषणा UART0_TX		_GPIOB(13)
#घोषणा UART2_RX		_GPIOB(14)
#घोषणा UART2_TX		_GPIOB(15)
#घोषणा UART2_RTSB		_GPIOB(16)
#घोषणा UART2_CTSB		_GPIOB(17)
#घोषणा UART4_RX		_GPIOB(18)
#घोषणा UART4_TX		_GPIOB(19)
#घोषणा I2C0_SCLK		_GPIOB(20)
#घोषणा I2C0_SDATA		_GPIOB(21)
#घोषणा I2C1_SCLK		_GPIOB(22)
#घोषणा I2C1_SDATA		_GPIOB(23)
#घोषणा I2C2_SCLK		_GPIOB(24)
#घोषणा I2C2_SDATA		_GPIOB(25)
#घोषणा CSI0_DN0		_GPIOB(26)
#घोषणा CSI0_DP0		_GPIOB(27)
#घोषणा CSI0_DN1		_GPIOB(28)
#घोषणा CSI0_DP1		_GPIOB(29)
#घोषणा CSI0_CN			_GPIOB(30)
#घोषणा CSI0_CP			_GPIOB(31)

#घोषणा CSI0_DN2		_GPIOC(0)
#घोषणा CSI0_DP2		_GPIOC(1)
#घोषणा CSI0_DN3		_GPIOC(2)
#घोषणा CSI0_DP3		_GPIOC(3)
#घोषणा SENSOR0_PCLK		_GPIOC(4)
#घोषणा CSI1_DN0		_GPIOC(5)
#घोषणा CSI1_DP0		_GPIOC(6)
#घोषणा CSI1_DN1		_GPIOC(7)
#घोषणा CSI1_DP1		_GPIOC(8)
#घोषणा CSI1_CN			_GPIOC(9)
#घोषणा CSI1_CP			_GPIOC(10)
#घोषणा SENSOR0_CKOUT		_GPIOC(11)

#घोषणा LVDS_OEP		_GPIOD(0)
#घोषणा LVDS_OEN		_GPIOD(1)
#घोषणा LVDS_ODP		_GPIOD(2)
#घोषणा LVDS_ODN		_GPIOD(3)
#घोषणा LVDS_OCP		_GPIOD(4)
#घोषणा LVDS_OCN		_GPIOD(5)
#घोषणा LVDS_OBP		_GPIOD(6)
#घोषणा LVDS_OBN		_GPIOD(7)
#घोषणा LVDS_OAP		_GPIOD(8)
#घोषणा LVDS_OAN		_GPIOD(9)
#घोषणा LVDS_EEP		_GPIOD(10)
#घोषणा LVDS_EEN		_GPIOD(11)
#घोषणा LVDS_EDP		_GPIOD(12)
#घोषणा LVDS_EDN		_GPIOD(13)
#घोषणा LVDS_ECP		_GPIOD(14)
#घोषणा LVDS_ECN		_GPIOD(15)
#घोषणा LVDS_EBP		_GPIOD(16)
#घोषणा LVDS_EBN		_GPIOD(17)
#घोषणा LVDS_EAP		_GPIOD(18)
#घोषणा LVDS_EAN		_GPIOD(19)
#घोषणा DSI_DP3			_GPIOD(20)
#घोषणा DSI_DN3			_GPIOD(21)
#घोषणा DSI_DP1			_GPIOD(22)
#घोषणा DSI_DN1			_GPIOD(23)
#घोषणा DSI_CP			_GPIOD(24)
#घोषणा DSI_CN			_GPIOD(25)
#घोषणा DSI_DP0			_GPIOD(26)
#घोषणा DSI_DN0			_GPIOD(27)
#घोषणा DSI_DP2			_GPIOD(28)
#घोषणा DSI_DN2			_GPIOD(29)

#घोषणा न_अंकD0_D0		_GPIOE(0)
#घोषणा न_अंकD0_D1		_GPIOE(1)
#घोषणा न_अंकD0_D2		_GPIOE(2)
#घोषणा न_अंकD0_D3		_GPIOE(3)
#घोषणा न_अंकD0_D4		_GPIOE(4)
#घोषणा न_अंकD0_D5		_GPIOE(5)
#घोषणा न_अंकD0_D6		_GPIOE(6)
#घोषणा न_अंकD0_D7		_GPIOE(7)
#घोषणा न_अंकD0_DQS		_GPIOE(8)
#घोषणा न_अंकD0_DQSN		_GPIOE(9)
#घोषणा न_अंकD0_ALE		_GPIOE(10)
#घोषणा न_अंकD0_CLE		_GPIOE(11)
#घोषणा न_अंकD0_CEB0		_GPIOE(12)
#घोषणा न_अंकD0_CEB1		_GPIOE(13)
#घोषणा न_अंकD0_CEB2		_GPIOE(14)
#घोषणा न_अंकD0_CEB3		_GPIOE(15)
#घोषणा न_अंकD1_D0		_GPIOE(16)
#घोषणा न_अंकD1_D1		_GPIOE(17)
#घोषणा न_अंकD1_D2		_GPIOE(18)
#घोषणा न_अंकD1_D3		_GPIOE(19)
#घोषणा न_अंकD1_D4		_GPIOE(20)
#घोषणा न_अंकD1_D5		_GPIOE(21)
#घोषणा न_अंकD1_D6		_GPIOE(22)
#घोषणा न_अंकD1_D7		_GPIOE(23)
#घोषणा न_अंकD1_DQS		_GPIOE(24)
#घोषणा न_अंकD1_DQSN		_GPIOE(25)
#घोषणा न_अंकD1_ALE		_GPIOE(26)
#घोषणा न_अंकD1_CLE		_GPIOE(27)
#घोषणा न_अंकD1_CEB0		_GPIOE(28)
#घोषणा न_अंकD1_CEB1		_GPIOE(29)
#घोषणा न_अंकD1_CEB2		_GPIOE(30)
#घोषणा न_अंकD1_CEB3		_GPIOE(31)

#घोषणा PCM1_IN			_GPIOF(0)
#घोषणा PCM1_CLK		_GPIOF(1)
#घोषणा PCM1_SYNC		_GPIOF(2)
#घोषणा PCM1_OUT		_GPIOF(3)
#घोषणा UART3_RX		_GPIOF(4)
#घोषणा UART3_TX		_GPIOF(5)
#घोषणा UART3_RTSB		_GPIOF(6)
#घोषणा UART3_CTSB		_GPIOF(7)

/* System */
#घोषणा SGPIO0			_PIN(0)
#घोषणा SGPIO1			_PIN(1)
#घोषणा SGPIO2			_PIN(2)
#घोषणा SGPIO3			_PIN(3)

#घोषणा NUM_PADS		(_PIN(3) + 1)

/* Pad names as specअगरied in datasheet */
अटल स्थिर काष्ठा pinctrl_pin_desc s900_pads[] = अणु
	PINCTRL_PIN(ETH_TXD0, "eth_txd0"),
	PINCTRL_PIN(ETH_TXD1, "eth_txd1"),
	PINCTRL_PIN(ETH_TXEN, "eth_txen"),
	PINCTRL_PIN(ETH_RXER, "eth_rxer"),
	PINCTRL_PIN(ETH_CRS_DV, "eth_crs_dv"),
	PINCTRL_PIN(ETH_RXD1, "eth_rxd1"),
	PINCTRL_PIN(ETH_RXD0, "eth_rxd0"),
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
	PINCTRL_PIN(ERAM_A5, "eram_a5"),
	PINCTRL_PIN(ERAM_A6, "eram_a6"),
	PINCTRL_PIN(ERAM_A7, "eram_a7"),
	PINCTRL_PIN(ERAM_A8, "eram_a8"),
	PINCTRL_PIN(ERAM_A9, "eram_a9"),
	PINCTRL_PIN(ERAM_A10, "eram_a10"),
	PINCTRL_PIN(ERAM_A11, "eram_a11"),
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
	PINCTRL_PIN(SPI0_SCLK, "spi0_sclk"),
	PINCTRL_PIN(SPI0_SS, "spi0_ss"),
	PINCTRL_PIN(SPI0_MISO, "spi0_miso"),
	PINCTRL_PIN(SPI0_MOSI, "spi0_mosi"),
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
	PINCTRL_PIN(UART4_RX, "uart4_rx"),
	PINCTRL_PIN(UART4_TX, "uart4_tx"),
	PINCTRL_PIN(I2C0_SCLK, "i2c0_sclk"),
	PINCTRL_PIN(I2C0_SDATA, "i2c0_sdata"),
	PINCTRL_PIN(I2C1_SCLK, "i2c1_sclk"),
	PINCTRL_PIN(I2C1_SDATA, "i2c1_sdata"),
	PINCTRL_PIN(I2C2_SCLK, "i2c2_sclk"),
	PINCTRL_PIN(I2C2_SDATA, "i2c2_sdata"),
	PINCTRL_PIN(CSI0_DN0, "csi0_dn0"),
	PINCTRL_PIN(CSI0_DP0, "csi0_dp0"),
	PINCTRL_PIN(CSI0_DN1, "csi0_dn1"),
	PINCTRL_PIN(CSI0_DP1, "csi0_dp1"),
	PINCTRL_PIN(CSI0_CN, "csi0_cn"),
	PINCTRL_PIN(CSI0_CP, "csi0_cp"),
	PINCTRL_PIN(CSI0_DN2, "csi0_dn2"),
	PINCTRL_PIN(CSI0_DP2, "csi0_dp2"),
	PINCTRL_PIN(CSI0_DN3, "csi0_dn3"),
	PINCTRL_PIN(CSI0_DP3, "csi0_dp3"),
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
	PINCTRL_PIN(SENSOR0_PCLK, "sensor0_pclk"),
	PINCTRL_PIN(CSI1_DN0, "csi1_dn0"),
	PINCTRL_PIN(CSI1_DP0, "csi1_dp0"),
	PINCTRL_PIN(CSI1_DN1, "csi1_dn1"),
	PINCTRL_PIN(CSI1_DP1, "csi1_dp1"),
	PINCTRL_PIN(CSI1_CN, "csi1_cn"),
	PINCTRL_PIN(CSI1_CP, "csi1_cp"),
	PINCTRL_PIN(SENSOR0_CKOUT, "sensor0_ckout"),
	PINCTRL_PIN(न_अंकD0_D0, "nand0_d0"),
	PINCTRL_PIN(न_अंकD0_D1, "nand0_d1"),
	PINCTRL_PIN(न_अंकD0_D2, "nand0_d2"),
	PINCTRL_PIN(न_अंकD0_D3, "nand0_d3"),
	PINCTRL_PIN(न_अंकD0_D4, "nand0_d4"),
	PINCTRL_PIN(न_अंकD0_D5, "nand0_d5"),
	PINCTRL_PIN(न_अंकD0_D6, "nand0_d6"),
	PINCTRL_PIN(न_अंकD0_D7, "nand0_d7"),
	PINCTRL_PIN(न_अंकD0_DQS, "nand0_dqs"),
	PINCTRL_PIN(न_अंकD0_DQSN, "nand0_dqsn"),
	PINCTRL_PIN(न_अंकD0_ALE, "nand0_ale"),
	PINCTRL_PIN(न_अंकD0_CLE, "nand0_cle"),
	PINCTRL_PIN(न_अंकD0_CEB0, "nand0_ceb0"),
	PINCTRL_PIN(न_अंकD0_CEB1, "nand0_ceb1"),
	PINCTRL_PIN(न_अंकD0_CEB2, "nand0_ceb2"),
	PINCTRL_PIN(न_अंकD0_CEB3, "nand0_ceb3"),
	PINCTRL_PIN(न_अंकD1_D0, "nand1_d0"),
	PINCTRL_PIN(न_अंकD1_D1, "nand1_d1"),
	PINCTRL_PIN(न_अंकD1_D2, "nand1_d2"),
	PINCTRL_PIN(न_अंकD1_D3, "nand1_d3"),
	PINCTRL_PIN(न_अंकD1_D4, "nand1_d4"),
	PINCTRL_PIN(न_अंकD1_D5, "nand1_d5"),
	PINCTRL_PIN(न_अंकD1_D6, "nand1_d6"),
	PINCTRL_PIN(न_अंकD1_D7, "nand1_d7"),
	PINCTRL_PIN(न_अंकD1_DQS, "nand1_dqs"),
	PINCTRL_PIN(न_अंकD1_DQSN, "nand1_dqsn"),
	PINCTRL_PIN(न_अंकD1_ALE, "nand1_ale"),
	PINCTRL_PIN(न_अंकD1_CLE, "nand1_cle"),
	PINCTRL_PIN(न_अंकD1_CEB0, "nand1_ceb0"),
	PINCTRL_PIN(न_अंकD1_CEB1, "nand1_ceb1"),
	PINCTRL_PIN(न_अंकD1_CEB2, "nand1_ceb2"),
	PINCTRL_PIN(न_अंकD1_CEB3, "nand1_ceb3"),
	PINCTRL_PIN(SGPIO0, "sgpio0"),
	PINCTRL_PIN(SGPIO1, "sgpio1"),
	PINCTRL_PIN(SGPIO2, "sgpio2"),
	PINCTRL_PIN(SGPIO3, "sgpio3")
पूर्ण;

क्रमागत s900_pinmux_functions अणु
	S900_MUX_ERAM,
	S900_MUX_ETH_RMII,
	S900_MUX_ETH_SMII,
	S900_MUX_SPI0,
	S900_MUX_SPI1,
	S900_MUX_SPI2,
	S900_MUX_SPI3,
	S900_MUX_SENS0,
	S900_MUX_UART0,
	S900_MUX_UART1,
	S900_MUX_UART2,
	S900_MUX_UART3,
	S900_MUX_UART4,
	S900_MUX_UART5,
	S900_MUX_UART6,
	S900_MUX_I2S0,
	S900_MUX_I2S1,
	S900_MUX_PCM0,
	S900_MUX_PCM1,
	S900_MUX_JTAG,
	S900_MUX_PWM0,
	S900_MUX_PWM1,
	S900_MUX_PWM2,
	S900_MUX_PWM3,
	S900_MUX_PWM4,
	S900_MUX_PWM5,
	S900_MUX_SD0,
	S900_MUX_SD1,
	S900_MUX_SD2,
	S900_MUX_SD3,
	S900_MUX_I2C0,
	S900_MUX_I2C1,
	S900_MUX_I2C2,
	S900_MUX_I2C3,
	S900_MUX_I2C4,
	S900_MUX_I2C5,
	S900_MUX_LVDS,
	S900_MUX_USB20,
	S900_MUX_USB30,
	S900_MUX_GPU,
	S900_MUX_MIPI_CSI0,
	S900_MUX_MIPI_CSI1,
	S900_MUX_MIPI_DSI,
	S900_MUX_न_अंकD0,
	S900_MUX_न_अंकD1,
	S900_MUX_SPDIF,
	S900_MUX_SIRQ0,
	S900_MUX_SIRQ1,
	S900_MUX_SIRQ2,
	S900_MUX_AUX_START,
	S900_MUX_MAX,
	S900_MUX_RESERVED
पूर्ण;

/* mfp0_22 */
अटल अचिन्हित पूर्णांक lvds_oxx_uart4_mfp_pads[]	= अणु LVDS_OAP, LVDS_OAN पूर्ण;
अटल अचिन्हित पूर्णांक lvds_oxx_uart4_mfp_funcs[]	= अणु S900_MUX_ERAM,
						    S900_MUX_UART4 पूर्ण;
/* mfp0_21_20 */
अटल अचिन्हित पूर्णांक rmii_mdc_mfp_pads[]		= अणु ETH_MDC पूर्ण;
अटल अचिन्हित पूर्णांक rmii_mdc_mfp_funcs[]	= अणु S900_MUX_ETH_RMII,
						    S900_MUX_PWM2,
						    S900_MUX_UART2,
						    S900_MUX_RESERVED पूर्ण;
अटल अचिन्हित पूर्णांक rmii_mdio_mfp_pads[]	= अणु ETH_MDIO पूर्ण;
अटल अचिन्हित पूर्णांक rmii_mdio_mfp_funcs[]	= अणु S900_MUX_ETH_RMII,
						    S900_MUX_PWM3,
						    S900_MUX_UART2,
						    S900_MUX_RESERVED पूर्ण;
/* mfp0_19 */
अटल अचिन्हित पूर्णांक sirq0_mfp_pads[]		= अणु SIRQ0 पूर्ण;
अटल अचिन्हित पूर्णांक sirq0_mfp_funcs[]		= अणु S900_MUX_SIRQ0,
						    S900_MUX_PWM0 पूर्ण;
अटल अचिन्हित पूर्णांक sirq1_mfp_pads[]		= अणु SIRQ1 पूर्ण;
अटल अचिन्हित पूर्णांक sirq1_mfp_funcs[]		= अणु S900_MUX_SIRQ1,
						    S900_MUX_PWM1 पूर्ण;
/* mfp0_18_16 */
अटल अचिन्हित पूर्णांक rmii_txd0_mfp_pads[]	= अणु ETH_TXD0 पूर्ण;
अटल अचिन्हित पूर्णांक rmii_txd0_mfp_funcs[]	= अणु S900_MUX_ETH_RMII,
						    S900_MUX_ETH_SMII,
						    S900_MUX_SPI2,
						    S900_MUX_UART6,
						    S900_MUX_SENS0,
						    S900_MUX_PWM0 पूर्ण;
अटल अचिन्हित पूर्णांक rmii_txd1_mfp_pads[]	= अणु ETH_TXD1 पूर्ण;
अटल अचिन्हित पूर्णांक rmii_txd1_mfp_funcs[]	= अणु S900_MUX_ETH_RMII,
						    S900_MUX_ETH_SMII,
						    S900_MUX_SPI2,
						    S900_MUX_UART6,
						    S900_MUX_SENS0,
						    S900_MUX_PWM1 पूर्ण;
/* mfp0_15_13 */
अटल अचिन्हित पूर्णांक rmii_txen_mfp_pads[]	= अणु ETH_TXEN पूर्ण;
अटल अचिन्हित पूर्णांक rmii_txen_mfp_funcs[]	= अणु S900_MUX_ETH_RMII,
						    S900_MUX_UART2,
						    S900_MUX_SPI3,
						    S900_MUX_RESERVED,
						    S900_MUX_RESERVED,
						    S900_MUX_PWM2,
						    S900_MUX_SENS0 पूर्ण;

अटल अचिन्हित पूर्णांक rmii_rxer_mfp_pads[]	= अणु ETH_RXER पूर्ण;
अटल अचिन्हित पूर्णांक rmii_rxer_mfp_funcs[]	= अणु S900_MUX_ETH_RMII,
						    S900_MUX_UART2,
						    S900_MUX_SPI3,
						    S900_MUX_RESERVED,
						    S900_MUX_RESERVED,
						    S900_MUX_PWM3,
						    S900_MUX_SENS0 पूर्ण;
/* mfp0_12_11 */
अटल अचिन्हित पूर्णांक rmii_crs_dv_mfp_pads[]	= अणु ETH_CRS_DV पूर्ण;
अटल अचिन्हित पूर्णांक rmii_crs_dv_mfp_funcs[]	= अणु S900_MUX_ETH_RMII,
						    S900_MUX_ETH_SMII,
						    S900_MUX_SPI2,
						    S900_MUX_UART4 पूर्ण;
/* mfp0_10_8 */
अटल अचिन्हित पूर्णांक rmii_rxd1_mfp_pads[]	= अणु ETH_RXD1 पूर्ण;
अटल अचिन्हित पूर्णांक rmii_rxd1_mfp_funcs[]	= अणु S900_MUX_ETH_RMII,
						    S900_MUX_UART2,
						    S900_MUX_SPI3,
						    S900_MUX_RESERVED,
						    S900_MUX_UART5,
						    S900_MUX_PWM0,
						    S900_MUX_SENS0 पूर्ण;
अटल अचिन्हित पूर्णांक rmii_rxd0_mfp_pads[]	= अणु ETH_RXD0 पूर्ण;
अटल अचिन्हित पूर्णांक rmii_rxd0_mfp_funcs[]	= अणु S900_MUX_ETH_RMII,
						    S900_MUX_UART2,
						    S900_MUX_SPI3,
						    S900_MUX_RESERVED,
						    S900_MUX_UART5,
						    S900_MUX_PWM1,
						    S900_MUX_SENS0 पूर्ण;
/* mfp0_7_6 */
अटल अचिन्हित पूर्णांक rmii_ref_clk_mfp_pads[]	= अणु ETH_REF_CLK पूर्ण;
अटल अचिन्हित पूर्णांक rmii_ref_clk_mfp_funcs[]	= अणु S900_MUX_ETH_RMII,
						    S900_MUX_UART4,
						    S900_MUX_SPI2,
						    S900_MUX_RESERVED पूर्ण;
/* mfp0_5 */
अटल अचिन्हित पूर्णांक i2s_d0_mfp_pads[]		= अणु I2S_D0 पूर्ण;
अटल अचिन्हित पूर्णांक i2s_d0_mfp_funcs[]		= अणु S900_MUX_I2S0,
						    S900_MUX_PCM0 पूर्ण;
अटल अचिन्हित पूर्णांक i2s_d1_mfp_pads[]		= अणु I2S_D1 पूर्ण;
अटल अचिन्हित पूर्णांक i2s_d1_mfp_funcs[]		= अणु S900_MUX_I2S1,
						    S900_MUX_PCM0 पूर्ण;

/* mfp0_4_3 */
अटल अचिन्हित पूर्णांक i2s_lr_m_clk0_mfp_pads[]	= अणु I2S_LRCLK0,
						    I2S_MCLK0 पूर्ण;
अटल अचिन्हित पूर्णांक i2s_lr_m_clk0_mfp_funcs[]	= अणु S900_MUX_I2S0,
						    S900_MUX_PCM0,
						    S900_MUX_PCM1,
						    S900_MUX_RESERVED पूर्ण;
/* mfp0_2 */
अटल अचिन्हित पूर्णांक i2s_bclk0_mfp_pads[]	= अणु I2S_BCLK0 पूर्ण;
अटल अचिन्हित पूर्णांक i2s_bclk0_mfp_funcs[]	= अणु S900_MUX_I2S0,
						    S900_MUX_PCM0 पूर्ण;
अटल अचिन्हित पूर्णांक i2s_bclk1_mclk1_mfp_pads[]	= अणु I2S_BCLK1,
						    I2S_LRCLK1,
						    I2S_MCLK1 पूर्ण;
अटल अचिन्हित पूर्णांक i2s_bclk1_mclk1_mfp_funcs[] = अणु S900_MUX_I2S1,
						    S900_MUX_PCM0 पूर्ण;
/* mfp0_1_0 */
अटल अचिन्हित पूर्णांक pcm1_in_out_mfp_pads[]	= अणु PCM1_IN,
						    PCM1_OUT पूर्ण;
अटल अचिन्हित पूर्णांक pcm1_in_out_mfp_funcs[]	= अणु S900_MUX_PCM1,
						    S900_MUX_SPI1,
						    S900_MUX_I2C3,
						    S900_MUX_UART4 पूर्ण;
अटल अचिन्हित पूर्णांक pcm1_clk_mfp_pads[]		= अणु PCM1_CLK पूर्ण;
अटल अचिन्हित पूर्णांक pcm1_clk_mfp_funcs[]	= अणु S900_MUX_PCM1,
						    S900_MUX_SPI1,
						    S900_MUX_PWM4,
						    S900_MUX_UART4 पूर्ण;
अटल अचिन्हित पूर्णांक pcm1_sync_mfp_pads[]	= अणु PCM1_SYNC पूर्ण;
अटल अचिन्हित पूर्णांक pcm1_sync_mfp_funcs[]	= अणु S900_MUX_PCM1,
						    S900_MUX_SPI1,
						    S900_MUX_PWM5,
						    S900_MUX_UART4 पूर्ण;
/* mfp1_31_29 */
अटल अचिन्हित पूर्णांक eram_a5_mfp_pads[]		= अणु ERAM_A5 पूर्ण;
अटल अचिन्हित पूर्णांक eram_a5_mfp_funcs[]		= अणु S900_MUX_UART4,
						    S900_MUX_JTAG,
						    S900_MUX_ERAM,
						    S900_MUX_PWM0,
						    S900_MUX_RESERVED,
						    S900_MUX_SENS0 पूर्ण;
अटल अचिन्हित पूर्णांक eram_a6_mfp_pads[]		= अणु ERAM_A6 पूर्ण;
अटल अचिन्हित पूर्णांक eram_a6_mfp_funcs[]		= अणु S900_MUX_UART4,
						    S900_MUX_JTAG,
						    S900_MUX_ERAM,
						    S900_MUX_PWM1,
						    S900_MUX_RESERVED,
						    S900_MUX_SENS0,
पूर्ण;
अटल अचिन्हित पूर्णांक eram_a7_mfp_pads[]		= अणु ERAM_A7 पूर्ण;
अटल अचिन्हित पूर्णांक eram_a7_mfp_funcs[]		= अणु S900_MUX_RESERVED,
						    S900_MUX_JTAG,
						    S900_MUX_ERAM,
						    S900_MUX_RESERVED,
						    S900_MUX_RESERVED,
						    S900_MUX_SENS0 पूर्ण;
/* mfp1_28_26 */
अटल अचिन्हित पूर्णांक eram_a8_mfp_pads[]		= अणु ERAM_A8 पूर्ण;
अटल अचिन्हित पूर्णांक eram_a8_mfp_funcs[]		= अणु S900_MUX_RESERVED,
						    S900_MUX_JTAG,
						    S900_MUX_ERAM,
						    S900_MUX_PWM1,
						    S900_MUX_RESERVED,
						    S900_MUX_SENS0 पूर्ण;
अटल अचिन्हित पूर्णांक eram_a9_mfp_pads[]		= अणु ERAM_A9 पूर्ण;
अटल अचिन्हित पूर्णांक eram_a9_mfp_funcs[]		= अणु S900_MUX_USB20,
						    S900_MUX_UART5,
						    S900_MUX_ERAM,
						    S900_MUX_PWM2,
						    S900_MUX_RESERVED,
						    S900_MUX_SENS0 पूर्ण;
अटल अचिन्हित पूर्णांक eram_a10_mfp_pads[]		= अणु ERAM_A10 पूर्ण;
अटल अचिन्हित पूर्णांक eram_a10_mfp_funcs[]	= अणु S900_MUX_USB30,
						    S900_MUX_JTAG,
						    S900_MUX_ERAM,
						    S900_MUX_PWM3,
						    S900_MUX_RESERVED,
						    S900_MUX_SENS0,
						    S900_MUX_RESERVED,
						    S900_MUX_RESERVED पूर्ण;
/* mfp1_25_23 */
अटल अचिन्हित पूर्णांक eram_a11_mfp_pads[]		= अणु ERAM_A11 पूर्ण;
अटल अचिन्हित पूर्णांक eram_a11_mfp_funcs[]	= अणु S900_MUX_RESERVED,
						    S900_MUX_RESERVED,
						    S900_MUX_ERAM,
						    S900_MUX_PWM2,
						    S900_MUX_UART5,
						    S900_MUX_RESERVED,
						    S900_MUX_SENS0,
						    S900_MUX_RESERVED पूर्ण;
/* mfp1_22 */
अटल अचिन्हित पूर्णांक lvds_oep_odn_mfp_pads[]	= अणु LVDS_OEP,
						    LVDS_OEN,
						    LVDS_ODP,
						    LVDS_ODN पूर्ण;
अटल अचिन्हित पूर्णांक lvds_oep_odn_mfp_funcs[]	= अणु S900_MUX_LVDS,
						    S900_MUX_UART2 पूर्ण;
अटल अचिन्हित पूर्णांक lvds_ocp_obn_mfp_pads[]	= अणु LVDS_OCP,
						    LVDS_OCN,
						    LVDS_OBP,
						    LVDS_OBN पूर्ण;
अटल अचिन्हित पूर्णांक lvds_ocp_obn_mfp_funcs[]	= अणु S900_MUX_LVDS,
						    S900_MUX_PCM1 पूर्ण;
अटल अचिन्हित पूर्णांक lvds_oap_oan_mfp_pads[]	= अणु LVDS_OAP,
						    LVDS_OAN पूर्ण;
अटल अचिन्हित पूर्णांक lvds_oap_oan_mfp_funcs[]	= अणु S900_MUX_LVDS,
						    S900_MUX_ERAM पूर्ण;
/* mfp1_21 */
अटल अचिन्हित पूर्णांक lvds_e_mfp_pads[]		= अणु LVDS_EEP,
						    LVDS_EEN,
						    LVDS_EDP,
						    LVDS_EDN,
						    LVDS_ECP,
						    LVDS_ECN,
						    LVDS_EBP,
						    LVDS_EBN,
						    LVDS_EAP,
						    LVDS_EAN पूर्ण;
अटल अचिन्हित पूर्णांक lvds_e_mfp_funcs[]		= अणु S900_MUX_LVDS,
						    S900_MUX_ERAM पूर्ण;
/* mfp1_5_4 */
अटल अचिन्हित पूर्णांक spi0_sclk_mosi_mfp_pads[]	= अणु SPI0_SCLK,
						    SPI0_MOSI पूर्ण;
अटल अचिन्हित पूर्णांक spi0_sclk_mosi_mfp_funcs[]	= अणु S900_MUX_SPI0,
						    S900_MUX_ERAM,
						    S900_MUX_I2C3,
						    S900_MUX_PCM0 पूर्ण;
/* mfp1_3_1 */
अटल अचिन्हित पूर्णांक spi0_ss_mfp_pads[]		= अणु SPI0_SS पूर्ण;
अटल अचिन्हित पूर्णांक spi0_ss_mfp_funcs[]		= अणु S900_MUX_SPI0,
						    S900_MUX_ERAM,
						    S900_MUX_I2S1,
						    S900_MUX_PCM1,
						    S900_MUX_PCM0,
						    S900_MUX_PWM4 पूर्ण;
अटल अचिन्हित पूर्णांक spi0_miso_mfp_pads[]	= अणु SPI0_MISO पूर्ण;
अटल अचिन्हित पूर्णांक spi0_miso_mfp_funcs[]	= अणु S900_MUX_SPI0,
						    S900_MUX_ERAM,
						    S900_MUX_I2S1,
						    S900_MUX_PCM1,
						    S900_MUX_PCM0,
						    S900_MUX_PWM5 पूर्ण;
/* mfp2_23 */
अटल अचिन्हित पूर्णांक uart2_rtsb_mfp_pads[]	= अणु UART2_RTSB पूर्ण;
अटल अचिन्हित पूर्णांक uart2_rtsb_mfp_funcs[]	= अणु S900_MUX_UART2,
						    S900_MUX_UART0 पूर्ण;
/* mfp2_22 */
अटल अचिन्हित पूर्णांक uart2_ctsb_mfp_pads[]	= अणु UART2_CTSB पूर्ण;
अटल अचिन्हित पूर्णांक uart2_ctsb_mfp_funcs[]	= अणु S900_MUX_UART2,
						    S900_MUX_UART0 पूर्ण;
/* mfp2_21 */
अटल अचिन्हित पूर्णांक uart3_rtsb_mfp_pads[]	= अणु UART3_RTSB पूर्ण;
अटल अचिन्हित पूर्णांक uart3_rtsb_mfp_funcs[]	= अणु S900_MUX_UART3,
						    S900_MUX_UART5 पूर्ण;
/* mfp2_20 */
अटल अचिन्हित पूर्णांक uart3_ctsb_mfp_pads[]	= अणु UART3_CTSB पूर्ण;
अटल अचिन्हित पूर्णांक uart3_ctsb_mfp_funcs[]	= अणु S900_MUX_UART3,
						    S900_MUX_UART5 पूर्ण;
/* mfp2_19_17 */
अटल अचिन्हित पूर्णांक sd0_d0_mfp_pads[]		= अणु SD0_D0 पूर्ण;
अटल अचिन्हित पूर्णांक sd0_d0_mfp_funcs[]		= अणु S900_MUX_SD0,
						    S900_MUX_ERAM,
						    S900_MUX_RESERVED,
						    S900_MUX_JTAG,
						    S900_MUX_UART2,
						    S900_MUX_UART5,
						    S900_MUX_GPU पूर्ण;
/* mfp2_16_14 */
अटल अचिन्हित पूर्णांक sd0_d1_mfp_pads[]		= अणु SD0_D1 पूर्ण;
अटल अचिन्हित पूर्णांक sd0_d1_mfp_funcs[]		= अणु S900_MUX_SD0,
						    S900_MUX_ERAM,
						    S900_MUX_GPU,
						    S900_MUX_RESERVED,
						    S900_MUX_UART2,
						    S900_MUX_UART5 पूर्ण;
/* mfp_13_11 */
अटल अचिन्हित पूर्णांक sd0_d2_d3_mfp_pads[]	= अणु SD0_D2,
						    SD0_D3 पूर्ण;
अटल अचिन्हित पूर्णांक sd0_d2_d3_mfp_funcs[]	= अणु S900_MUX_SD0,
						    S900_MUX_ERAM,
						    S900_MUX_RESERVED,
						    S900_MUX_JTAG,
						    S900_MUX_UART2,
						    S900_MUX_UART1,
						    S900_MUX_GPU पूर्ण;
/* mfp2_10_9 */
अटल अचिन्हित पूर्णांक sd1_d0_d3_mfp_pads[]	= अणु SD1_D0, SD1_D1,
						    SD1_D2, SD1_D3 पूर्ण;
अटल अचिन्हित पूर्णांक sd1_d0_d3_mfp_funcs[]	= अणु S900_MUX_SD1,
						    S900_MUX_ERAM पूर्ण;
/* mfp2_8_7 */
अटल अचिन्हित पूर्णांक sd0_cmd_mfp_pads[]		= अणु SD0_CMD पूर्ण;
अटल अचिन्हित पूर्णांक sd0_cmd_mfp_funcs[]		= अणु S900_MUX_SD0,
						    S900_MUX_ERAM,
						    S900_MUX_GPU,
						    S900_MUX_JTAG पूर्ण;
/* mfp2_6_5 */
अटल अचिन्हित पूर्णांक sd0_clk_mfp_pads[]		= अणु SD0_CLK पूर्ण;
अटल अचिन्हित पूर्णांक sd0_clk_mfp_funcs[]		= अणु S900_MUX_SD0,
						    S900_MUX_ERAM,
						    S900_MUX_JTAG,
						    S900_MUX_GPU पूर्ण;
/* mfp2_4_3 */
अटल अचिन्हित पूर्णांक sd1_cmd_clk_mfp_pads[]	= अणु SD1_CMD, SD1_CLK पूर्ण;
अटल अचिन्हित पूर्णांक sd1_cmd_clk_mfp_funcs[]	= अणु S900_MUX_SD1,
						    S900_MUX_ERAM पूर्ण;
/* mfp2_2_0 */
अटल अचिन्हित पूर्णांक uart0_rx_mfp_pads[]		= अणु UART0_RX पूर्ण;
अटल अचिन्हित पूर्णांक uart0_rx_mfp_funcs[]	= अणु S900_MUX_UART0,
						    S900_MUX_UART2,
						    S900_MUX_SPI1,
						    S900_MUX_I2C5,
						    S900_MUX_PCM1,
						    S900_MUX_I2S1 पूर्ण;
/* mfp3_27 */
अटल अचिन्हित पूर्णांक nand0_d0_ceb3_mfp_pads[]	= अणु न_अंकD0_D0, न_अंकD0_D1,
						    न_अंकD0_D2, न_अंकD0_D3,
						    न_अंकD0_D4, न_अंकD0_D5,
						    न_अंकD0_D6, न_अंकD0_D7,
						    न_अंकD0_DQSN, न_अंकD0_CEB3 पूर्ण;
अटल अचिन्हित पूर्णांक nand0_d0_ceb3_mfp_funcs[]	= अणु S900_MUX_न_अंकD0,
						    S900_MUX_SD2 पूर्ण;
/* mfp3_21_19 */
अटल अचिन्हित पूर्णांक uart0_tx_mfp_pads[]		= अणु UART0_TX पूर्ण;
अटल अचिन्हित पूर्णांक uart0_tx_mfp_funcs[]	= अणु S900_MUX_UART0,
						    S900_MUX_UART2,
						    S900_MUX_SPI1,
						    S900_MUX_I2C5,
						    S900_MUX_SPDIF,
						    S900_MUX_PCM1,
						    S900_MUX_I2S1 पूर्ण;
/* mfp3_18_16 */
अटल अचिन्हित पूर्णांक i2c0_mfp_pads[]		= अणु I2C0_SCLK, I2C0_SDATA पूर्ण;
अटल अचिन्हित पूर्णांक i2c0_mfp_funcs[]		= अणु S900_MUX_I2C0,
						    S900_MUX_UART2,
						    S900_MUX_I2C1,
						    S900_MUX_UART1,
						    S900_MUX_SPI1 पूर्ण;
/* mfp3_15 */
अटल अचिन्हित पूर्णांक csi0_cn_cp_mfp_pads[]	= अणु CSI0_CN, CSI0_CP पूर्ण;
अटल अचिन्हित पूर्णांक csi0_cn_cp_mfp_funcs[]	= अणु S900_MUX_SENS0,
						    S900_MUX_SENS0 पूर्ण;
/* mfp3_14 */
अटल अचिन्हित पूर्णांक csi0_dn0_dp3_mfp_pads[]	= अणु CSI0_DN0, CSI0_DP0,
						    CSI0_DN1, CSI0_DP1,
						    CSI0_CN, CSI0_CP,
						    CSI0_DP2, CSI0_DN2,
						    CSI0_DN3, CSI0_DP3 पूर्ण;
अटल अचिन्हित पूर्णांक csi0_dn0_dp3_mfp_funcs[]	= अणु S900_MUX_MIPI_CSI0,
						    S900_MUX_SENS0 पूर्ण;
/* mfp3_13 */
अटल अचिन्हित पूर्णांक csi1_dn0_cp_mfp_pads[]	= अणु CSI1_DN0, CSI1_DP0,
						    CSI1_DN1, CSI1_DP1,
						    CSI1_CN, CSI1_CP पूर्ण;
अटल अचिन्हित पूर्णांक csi1_dn0_cp_mfp_funcs[]	= अणु S900_MUX_MIPI_CSI1,
						    S900_MUX_SENS0 पूर्ण;
/* mfp3_12_dsi */
अटल अचिन्हित पूर्णांक dsi_dp3_dn1_mfp_pads[]	= अणु DSI_DP3, DSI_DN2,
						    DSI_DP1, DSI_DN1 पूर्ण;
अटल अचिन्हित पूर्णांक dsi_dp3_dn1_mfp_funcs[]	= अणु S900_MUX_MIPI_DSI,
						    S900_MUX_UART2 पूर्ण;
अटल अचिन्हित पूर्णांक dsi_cp_dn0_mfp_pads[]	= अणु DSI_CP, DSI_CN,
						    DSI_DP0, DSI_DN0 पूर्ण;
अटल अचिन्हित पूर्णांक dsi_cp_dn0_mfp_funcs[]	= अणु S900_MUX_MIPI_DSI,
						    S900_MUX_PCM1 पूर्ण;
अटल अचिन्हित पूर्णांक dsi_dp2_dn2_mfp_pads[]	= अणु DSI_DP2, DSI_DN2 पूर्ण;
अटल अचिन्हित पूर्णांक dsi_dp2_dn2_mfp_funcs[]	= अणु S900_MUX_MIPI_DSI,
						    S900_MUX_UART4 पूर्ण;
/* mfp3_11 */
अटल अचिन्हित पूर्णांक nand1_d0_ceb1_mfp_pads[]	= अणु न_अंकD1_D0, न_अंकD1_D1,
						    न_अंकD1_D2, न_अंकD1_D3,
						    न_अंकD1_D4, न_अंकD1_D5,
						    न_अंकD1_D6, न_अंकD1_D7,
						    न_अंकD1_DQSN, न_अंकD1_CEB1 पूर्ण;
अटल अचिन्हित पूर्णांक nand1_d0_ceb1_mfp_funcs[]	= अणु S900_MUX_न_अंकD1,
						    S900_MUX_SD3 पूर्ण;
/* mfp3_10 */
अटल अचिन्हित पूर्णांक nand1_ceb3_mfp_pads[]	= अणु न_अंकD1_CEB3 पूर्ण;
अटल अचिन्हित पूर्णांक nand1_ceb3_mfp_funcs[]	= अणु S900_MUX_न_अंकD1,
						    S900_MUX_PWM0 पूर्ण;
अटल अचिन्हित पूर्णांक nand1_ceb0_mfp_pads[]	= अणु न_अंकD1_CEB0 पूर्ण;
अटल अचिन्हित पूर्णांक nand1_ceb0_mfp_funcs[]	= अणु S900_MUX_न_अंकD1,
						    S900_MUX_PWM1 पूर्ण;
/* mfp3_9 */
अटल अचिन्हित पूर्णांक csi1_dn0_dp0_mfp_pads[]	= अणु CSI1_DN0, CSI1_DP0 पूर्ण;
अटल अचिन्हित पूर्णांक csi1_dn0_dp0_mfp_funcs[]	= अणु S900_MUX_SENS0,
						    S900_MUX_SENS0 पूर्ण;
/* mfp3_8 */
अटल अचिन्हित पूर्णांक uart4_rx_tx_mfp_pads[]	= अणु UART4_RX, UART4_TX पूर्ण;
अटल अचिन्हित पूर्णांक uart4_rx_tx_mfp_funcs[]	= अणु S900_MUX_UART4,
						    S900_MUX_I2C4 पूर्ण;
/* PADDRV group data */
/* drv0 */
अटल अचिन्हित पूर्णांक sgpio3_drv_pads[]		= अणु SGPIO3 पूर्ण;
अटल अचिन्हित पूर्णांक sgpio2_drv_pads[]		= अणु SGPIO2 पूर्ण;
अटल अचिन्हित पूर्णांक sgpio1_drv_pads[]		= अणु SGPIO1 पूर्ण;
अटल अचिन्हित पूर्णांक sgpio0_drv_pads[]		= अणु SGPIO0 पूर्ण;
अटल अचिन्हित पूर्णांक rmii_tx_d0_d1_drv_pads[]	= अणु ETH_TXD0, ETH_TXD1 पूर्ण;
अटल अचिन्हित पूर्णांक rmii_txen_rxer_drv_pads[]	= अणु ETH_TXEN, ETH_RXER पूर्ण;
अटल अचिन्हित पूर्णांक rmii_crs_dv_drv_pads[]	= अणु ETH_CRS_DV पूर्ण;
अटल अचिन्हित पूर्णांक rmii_rx_d1_d0_drv_pads[]	= अणु ETH_RXD1, ETH_RXD0 पूर्ण;
अटल अचिन्हित पूर्णांक rmii_ref_clk_drv_pads[]	= अणु ETH_REF_CLK पूर्ण;
अटल अचिन्हित पूर्णांक rmii_mdc_mdio_drv_pads[]	= अणु ETH_MDC, ETH_MDIO पूर्ण;
अटल अचिन्हित पूर्णांक sirq_0_1_drv_pads[]		= अणु SIRQ0, SIRQ1 पूर्ण;
अटल अचिन्हित पूर्णांक sirq2_drv_pads[]		= अणु SIRQ2 पूर्ण;
अटल अचिन्हित पूर्णांक i2s_d0_d1_drv_pads[]	= अणु I2S_D0, I2S_D1 पूर्ण;
अटल अचिन्हित पूर्णांक i2s_lr_m_clk0_drv_pads[]	= अणु I2S_LRCLK0, I2S_MCLK0 पूर्ण;
अटल अचिन्हित पूर्णांक i2s_blk1_mclk1_drv_pads[]	= अणु I2S_BCLK0, I2S_BCLK1,
						    I2S_LRCLK1, I2S_MCLK1 पूर्ण;
अटल अचिन्हित पूर्णांक pcm1_in_out_drv_pads[]	= अणु PCM1_IN, PCM1_CLK,
						    PCM1_SYNC, PCM1_OUT पूर्ण;
/* drv1 */
अटल अचिन्हित पूर्णांक lvds_oap_oan_drv_pads[]	= अणु LVDS_OAP, LVDS_OAN पूर्ण;
अटल अचिन्हित पूर्णांक lvds_oep_odn_drv_pads[]	= अणु LVDS_OEP, LVDS_OEN,
						    LVDS_ODP, LVDS_ODN पूर्ण;
अटल अचिन्हित पूर्णांक lvds_ocp_obn_drv_pads[]	= अणु LVDS_OCP, LVDS_OCN,
						    LVDS_OBP, LVDS_OBN पूर्ण;
अटल अचिन्हित पूर्णांक lvds_e_drv_pads[]		= अणु LVDS_EEP, LVDS_EEN,
						    LVDS_EDP, LVDS_EDN,
						    LVDS_ECP, LVDS_ECN,
						    LVDS_EBP, LVDS_EBN पूर्ण;
अटल अचिन्हित पूर्णांक sd0_d3_d0_drv_pads[]	= अणु SD0_D3, SD0_D2,
						    SD0_D1, SD0_D0 पूर्ण;
अटल अचिन्हित पूर्णांक sd1_d3_d0_drv_pads[]	= अणु SD1_D3, SD1_D2,
						    SD1_D1, SD1_D0 पूर्ण;
अटल अचिन्हित पूर्णांक sd0_sd1_cmd_clk_drv_pads[]	= अणु SD0_CLK, SD0_CMD,
						    SD1_CLK, SD1_CMD पूर्ण;
अटल अचिन्हित पूर्णांक spi0_sclk_mosi_drv_pads[]	= अणु SPI0_SCLK, SPI0_MOSI पूर्ण;
अटल अचिन्हित पूर्णांक spi0_ss_miso_drv_pads[]	= अणु SPI0_SS, SPI0_MISO पूर्ण;
अटल अचिन्हित पूर्णांक uart0_rx_tx_drv_pads[]	= अणु UART0_RX, UART0_TX पूर्ण;
अटल अचिन्हित पूर्णांक uart4_rx_tx_drv_pads[]	= अणु UART4_RX, UART4_TX पूर्ण;
अटल अचिन्हित पूर्णांक uart2_drv_pads[]		= अणु UART2_RX, UART2_TX,
						    UART2_RTSB, UART2_CTSB पूर्ण;
अटल अचिन्हित पूर्णांक uart3_drv_pads[]		= अणु UART3_RX, UART3_TX,
						    UART3_RTSB, UART3_CTSB पूर्ण;
/* drv2 */
अटल अचिन्हित पूर्णांक i2c0_drv_pads[]		= अणु I2C0_SCLK, I2C0_SDATA पूर्ण;
अटल अचिन्हित पूर्णांक i2c1_drv_pads[]		= अणु I2C1_SCLK, I2C1_SDATA पूर्ण;
अटल अचिन्हित पूर्णांक i2c2_drv_pads[]		= अणु I2C2_SCLK, I2C2_SDATA पूर्ण;
अटल अचिन्हित पूर्णांक sensor0_drv_pads[]		= अणु SENSOR0_PCLK,
						    SENSOR0_CKOUT पूर्ण;
/* SR group data */
/* sr0 */
अटल अचिन्हित पूर्णांक sgpio3_sr_pads[]		= अणु SGPIO3 पूर्ण;
अटल अचिन्हित पूर्णांक sgpio2_sr_pads[]		= अणु SGPIO2 पूर्ण;
अटल अचिन्हित पूर्णांक sgpio1_sr_pads[]		= अणु SGPIO1 पूर्ण;
अटल अचिन्हित पूर्णांक sgpio0_sr_pads[]		= अणु SGPIO0 पूर्ण;
अटल अचिन्हित पूर्णांक rmii_tx_d0_d1_sr_pads[]	= अणु ETH_TXD0, ETH_TXD1 पूर्ण;
अटल अचिन्हित पूर्णांक rmii_txen_rxer_sr_pads[]	= अणु ETH_TXEN, ETH_RXER पूर्ण;
अटल अचिन्हित पूर्णांक rmii_crs_dv_sr_pads[]	= अणु ETH_CRS_DV पूर्ण;
अटल अचिन्हित पूर्णांक rmii_rx_d1_d0_sr_pads[]	= अणु ETH_RXD1, ETH_RXD0 पूर्ण;
अटल अचिन्हित पूर्णांक rmii_ref_clk_sr_pads[]	= अणु ETH_REF_CLK पूर्ण;
अटल अचिन्हित पूर्णांक rmii_mdc_mdio_sr_pads[]	= अणु ETH_MDC, ETH_MDIO पूर्ण;
अटल अचिन्हित पूर्णांक sirq_0_1_sr_pads[]		= अणु SIRQ0, SIRQ1 पूर्ण;
अटल अचिन्हित पूर्णांक sirq2_sr_pads[]		= अणु SIRQ2 पूर्ण;
अटल अचिन्हित पूर्णांक i2s_करो_d1_sr_pads[]		= अणु I2S_D0, I2S_D1 पूर्ण;
अटल अचिन्हित पूर्णांक i2s_lr_m_clk0_sr_pads[]	= अणु I2S_LRCLK0, I2S_MCLK0 पूर्ण;
अटल अचिन्हित पूर्णांक i2s_bclk0_mclk1_sr_pads[]	= अणु I2S_BCLK0, I2S_BCLK1,
						    I2S_LRCLK1, I2S_MCLK1 पूर्ण;
अटल अचिन्हित पूर्णांक pcm1_in_out_sr_pads[]	= अणु PCM1_IN, PCM1_CLK,
						    PCM1_SYNC, PCM1_OUT पूर्ण;
/* sr1 */
अटल अचिन्हित पूर्णांक sd1_d3_d0_sr_pads[]		= अणु SD1_D3, SD1_D2,
						    SD1_D1, SD1_D0 पूर्ण;
अटल अचिन्हित पूर्णांक sd0_sd1_clk_cmd_sr_pads[]	= अणु SD0_CLK, SD0_CMD,
						    SD1_CLK, SD1_CMD पूर्ण;
अटल अचिन्हित पूर्णांक spi0_sclk_mosi_sr_pads[]	= अणु SPI0_SCLK, SPI0_MOSI पूर्ण;
अटल अचिन्हित पूर्णांक spi0_ss_miso_sr_pads[]	= अणु SPI0_SS, SPI0_MISO पूर्ण;
अटल अचिन्हित पूर्णांक uart0_rx_tx_sr_pads[]	= अणु UART0_RX, UART0_TX पूर्ण;
अटल अचिन्हित पूर्णांक uart4_rx_tx_sr_pads[]	= अणु UART4_RX, UART4_TX पूर्ण;
अटल अचिन्हित पूर्णांक uart2_sr_pads[]		= अणु UART2_RX, UART2_TX,
						    UART2_RTSB, UART2_CTSB पूर्ण;
अटल अचिन्हित पूर्णांक uart3_sr_pads[]		= अणु UART3_RX, UART3_TX,
						    UART3_RTSB, UART3_CTSB पूर्ण;
/* sr2 */
अटल अचिन्हित पूर्णांक i2c0_sr_pads[]		= अणु I2C0_SCLK, I2C0_SDATA पूर्ण;
अटल अचिन्हित पूर्णांक i2c1_sr_pads[]		= अणु I2C1_SCLK, I2C1_SDATA पूर्ण;
अटल अचिन्हित पूर्णांक i2c2_sr_pads[]		= अणु I2C2_SCLK, I2C2_SDATA पूर्ण;
अटल अचिन्हित पूर्णांक sensor0_sr_pads[]		= अणु SENSOR0_PCLK,
						    SENSOR0_CKOUT पूर्ण;


/* Pinctrl groups */
अटल स्थिर काष्ठा owl_pingroup s900_groups[] = अणु
	MUX_PG(lvds_oxx_uart4_mfp, 0, 22, 1),
	MUX_PG(rmii_mdc_mfp, 0, 20, 2),
	MUX_PG(rmii_mdio_mfp, 0, 20, 2),
	MUX_PG(sirq0_mfp, 0, 19, 1),
	MUX_PG(sirq1_mfp, 0, 19, 1),
	MUX_PG(rmii_txd0_mfp, 0, 16, 3),
	MUX_PG(rmii_txd1_mfp, 0, 16, 3),
	MUX_PG(rmii_txen_mfp, 0, 13, 3),
	MUX_PG(rmii_rxer_mfp, 0, 13, 3),
	MUX_PG(rmii_crs_dv_mfp, 0, 11, 2),
	MUX_PG(rmii_rxd1_mfp, 0, 8, 3),
	MUX_PG(rmii_rxd0_mfp, 0, 8, 3),
	MUX_PG(rmii_ref_clk_mfp, 0, 6, 2),
	MUX_PG(i2s_d0_mfp, 0, 5, 1),
	MUX_PG(i2s_d1_mfp, 0, 5, 1),
	MUX_PG(i2s_lr_m_clk0_mfp, 0, 3, 2),
	MUX_PG(i2s_bclk0_mfp, 0, 2, 1),
	MUX_PG(i2s_bclk1_mclk1_mfp, 0, 2, 1),
	MUX_PG(pcm1_in_out_mfp, 0, 0, 2),
	MUX_PG(pcm1_clk_mfp, 0, 0, 2),
	MUX_PG(pcm1_sync_mfp, 0, 0, 2),
	MUX_PG(eram_a5_mfp, 1, 29, 3),
	MUX_PG(eram_a6_mfp, 1, 29, 3),
	MUX_PG(eram_a7_mfp, 1, 29, 3),
	MUX_PG(eram_a8_mfp, 1, 26, 3),
	MUX_PG(eram_a9_mfp, 1, 26, 3),
	MUX_PG(eram_a10_mfp, 1, 26, 3),
	MUX_PG(eram_a11_mfp, 1, 23, 3),
	MUX_PG(lvds_oep_odn_mfp, 1, 22, 1),
	MUX_PG(lvds_ocp_obn_mfp, 1, 22, 1),
	MUX_PG(lvds_oap_oan_mfp, 1, 22, 1),
	MUX_PG(lvds_e_mfp, 1, 21, 1),
	MUX_PG(spi0_sclk_mosi_mfp, 1, 4, 2),
	MUX_PG(spi0_ss_mfp, 1, 1, 3),
	MUX_PG(spi0_miso_mfp, 1, 1, 3),
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
	MUX_PG(sd1_cmd_clk_mfp, 2, 3, 2),
	MUX_PG(uart0_rx_mfp, 2, 0, 3),
	MUX_PG(nand0_d0_ceb3_mfp, 3, 27, 1),
	MUX_PG(uart0_tx_mfp, 3, 19, 3),
	MUX_PG(i2c0_mfp, 3, 16, 3),
	MUX_PG(csi0_cn_cp_mfp, 3, 15, 1),
	MUX_PG(csi0_dn0_dp3_mfp, 3, 14, 1),
	MUX_PG(csi1_dn0_cp_mfp, 3, 13, 1),
	MUX_PG(dsi_dp3_dn1_mfp, 3, 12, 1),
	MUX_PG(dsi_cp_dn0_mfp, 3, 12, 1),
	MUX_PG(dsi_dp2_dn2_mfp, 3, 12, 1),
	MUX_PG(nand1_d0_ceb1_mfp, 3, 11, 1),
	MUX_PG(nand1_ceb3_mfp, 3, 10, 1),
	MUX_PG(nand1_ceb0_mfp, 3, 10, 1),
	MUX_PG(csi1_dn0_dp0_mfp, 3, 9, 1),
	MUX_PG(uart4_rx_tx_mfp, 3, 8, 1),

	DRV_PG(sgpio3_drv, 0, 30, 2),
	DRV_PG(sgpio2_drv, 0, 28, 2),
	DRV_PG(sgpio1_drv, 0, 26, 2),
	DRV_PG(sgpio0_drv, 0, 24, 2),
	DRV_PG(rmii_tx_d0_d1_drv, 0, 22, 2),
	DRV_PG(rmii_txen_rxer_drv, 0, 20, 2),
	DRV_PG(rmii_crs_dv_drv, 0, 18, 2),
	DRV_PG(rmii_rx_d1_d0_drv, 0, 16, 2),
	DRV_PG(rmii_ref_clk_drv, 0, 14, 2),
	DRV_PG(rmii_mdc_mdio_drv, 0, 12, 2),
	DRV_PG(sirq_0_1_drv, 0, 10, 2),
	DRV_PG(sirq2_drv, 0, 8, 2),
	DRV_PG(i2s_d0_d1_drv, 0, 6, 2),
	DRV_PG(i2s_lr_m_clk0_drv, 0, 4, 2),
	DRV_PG(i2s_blk1_mclk1_drv, 0, 2, 2),
	DRV_PG(pcm1_in_out_drv, 0, 0, 2),
	DRV_PG(lvds_oap_oan_drv, 1, 28, 2),
	DRV_PG(lvds_oep_odn_drv, 1, 26, 2),
	DRV_PG(lvds_ocp_obn_drv, 1, 24, 2),
	DRV_PG(lvds_e_drv, 1, 22, 2),
	DRV_PG(sd0_d3_d0_drv, 1, 20, 2),
	DRV_PG(sd1_d3_d0_drv, 1, 18, 2),
	DRV_PG(sd0_sd1_cmd_clk_drv, 1, 16, 2),
	DRV_PG(spi0_sclk_mosi_drv, 1, 14, 2),
	DRV_PG(spi0_ss_miso_drv, 1, 12, 2),
	DRV_PG(uart0_rx_tx_drv, 1, 10, 2),
	DRV_PG(uart4_rx_tx_drv, 1, 8, 2),
	DRV_PG(uart2_drv, 1, 6, 2),
	DRV_PG(uart3_drv, 1, 4, 2),
	DRV_PG(i2c0_drv, 2, 30, 2),
	DRV_PG(i2c1_drv, 2, 28, 2),
	DRV_PG(i2c2_drv, 2, 26, 2),
	DRV_PG(sensor0_drv, 2, 20, 2),

	SR_PG(sgpio3_sr, 0, 15, 1),
	SR_PG(sgpio2_sr, 0, 14, 1),
	SR_PG(sgpio1_sr, 0, 13, 1),
	SR_PG(sgpio0_sr, 0, 12, 1),
	SR_PG(rmii_tx_d0_d1_sr, 0, 11, 1),
	SR_PG(rmii_txen_rxer_sr, 0, 10, 1),
	SR_PG(rmii_crs_dv_sr, 0, 9, 1),
	SR_PG(rmii_rx_d1_d0_sr, 0, 8, 1),
	SR_PG(rmii_ref_clk_sr, 0, 7, 1),
	SR_PG(rmii_mdc_mdio_sr, 0, 6, 1),
	SR_PG(sirq_0_1_sr, 0, 5, 1),
	SR_PG(sirq2_sr, 0, 4, 1),
	SR_PG(i2s_करो_d1_sr, 0, 3, 1),
	SR_PG(i2s_lr_m_clk0_sr, 0, 2, 1),
	SR_PG(i2s_bclk0_mclk1_sr, 0, 1, 1),
	SR_PG(pcm1_in_out_sr, 0, 0, 1),
	SR_PG(sd1_d3_d0_sr, 1, 25, 1),
	SR_PG(sd0_sd1_clk_cmd_sr, 1, 24, 1),
	SR_PG(spi0_sclk_mosi_sr, 1, 23, 1),
	SR_PG(spi0_ss_miso_sr, 1, 22, 1),
	SR_PG(uart0_rx_tx_sr, 1, 21, 1),
	SR_PG(uart4_rx_tx_sr, 1, 20, 1),
	SR_PG(uart2_sr, 1, 19, 1),
	SR_PG(uart3_sr, 1, 18, 1),
	SR_PG(i2c0_sr, 2, 31, 1),
	SR_PG(i2c1_sr, 2, 30, 1),
	SR_PG(i2c2_sr, 2, 29, 1),
	SR_PG(sensor0_sr, 2, 25, 1)
पूर्ण;

अटल स्थिर अक्षर * स्थिर eram_groups[] = अणु
	"lvds_oxx_uart4_mfp",
	"eram_a5_mfp",
	"eram_a6_mfp",
	"eram_a7_mfp",
	"eram_a8_mfp",
	"eram_a9_mfp",
	"eram_a10_mfp",
	"eram_a11_mfp",
	"lvds_oap_oan_mfp",
	"lvds_e_mfp",
	"spi0_sclk_mosi_mfp",
	"spi0_ss_mfp",
	"spi0_miso_mfp",
	"sd0_d0_mfp",
	"sd0_d1_mfp",
	"sd0_d2_d3_mfp",
	"sd1_d0_d3_mfp",
	"sd0_cmd_mfp",
	"sd0_clk_mfp",
	"sd1_cmd_clk_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर eth_rmii_groups[] = अणु
	"rmii_mdc_mfp",
	"rmii_mdio_mfp",
	"rmii_txd0_mfp",
	"rmii_txd1_mfp",
	"rmii_txen_mfp",
	"rmii_rxer_mfp",
	"rmii_crs_dv_mfp",
	"rmii_rxd1_mfp",
	"rmii_rxd0_mfp",
	"rmii_ref_clk_mfp",
	"eth_smi_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर eth_smii_groups[] = अणु
	"rmii_txd0_mfp",
	"rmii_txd1_mfp",
	"rmii_crs_dv_mfp",
	"eth_smi_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi0_groups[] = अणु
	"spi0_sclk_mosi_mfp",
	"spi0_ss_mfp",
	"spi0_miso_mfp",
	"spi0_sclk_mosi_mfp",
	"spi0_ss_mfp",
	"spi0_miso_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi1_groups[] = अणु
	"pcm1_in_out_mfp",
	"pcm1_clk_mfp",
	"pcm1_sync_mfp",
	"uart0_rx_mfp",
	"uart0_tx_mfp",
	"i2c0_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi2_groups[] = अणु
	"rmii_txd0_mfp",
	"rmii_txd1_mfp",
	"rmii_crs_dv_mfp",
	"rmii_ref_clk_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spi3_groups[] = अणु
	"rmii_txen_mfp",
	"rmii_rxer_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sens0_groups[] = अणु
	"rmii_txd0_mfp",
	"rmii_txd1_mfp",
	"rmii_txen_mfp",
	"rmii_rxer_mfp",
	"rmii_rxd1_mfp",
	"rmii_rxd0_mfp",
	"eram_a5_mfp",
	"eram_a6_mfp",
	"eram_a7_mfp",
	"eram_a8_mfp",
	"eram_a9_mfp",
	"csi0_cn_cp_mfp",
	"csi0_dn0_dp3_mfp",
	"csi1_dn0_cp_mfp",
	"csi1_dn0_dp0_mfp",
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
	"rmii_mdc_mfp",
	"rmii_mdio_mfp",
	"rmii_txen_mfp",
	"rmii_rxer_mfp",
	"rmii_rxd1_mfp",
	"rmii_rxd0_mfp",
	"lvds_oep_odn_mfp",
	"uart2_rtsb_mfp",
	"uart2_ctsb_mfp",
	"sd0_d0_mfp",
	"sd0_d1_mfp",
	"sd0_d2_d3_mfp",
	"uart0_rx_mfp",
	"uart0_tx_mfp_pads",
	"i2c0_mfp_pads",
	"dsi_dp3_dn1_mfp",
	"uart2_dummy"
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart3_groups[] = अणु
	"uart3_rtsb_mfp",
	"uart3_ctsb_mfp",
	"uart3_dummy"
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart4_groups[] = अणु
	"lvds_oxx_uart4_mfp",
	"rmii_crs_dv_mfp",
	"rmii_ref_clk_mfp",
	"pcm1_in_out_mfp",
	"pcm1_clk_mfp",
	"pcm1_sync_mfp",
	"eram_a5_mfp",
	"eram_a6_mfp",
	"dsi_dp2_dn2_mfp",
	"uart4_rx_tx_mfp_pads",
	"uart4_dummy"
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart5_groups[] = अणु
	"rmii_rxd1_mfp",
	"rmii_rxd0_mfp",
	"eram_a9_mfp",
	"eram_a11_mfp",
	"uart3_rtsb_mfp",
	"uart3_ctsb_mfp",
	"sd0_d0_mfp",
	"sd0_d1_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर uart6_groups[] = अणु
	"rmii_txd0_mfp",
	"rmii_txd1_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2s0_groups[] = अणु
	"i2s_d0_mfp",
	"i2s_lr_m_clk0_mfp",
	"i2s_bclk0_mfp",
	"i2s0_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2s1_groups[] = अणु
	"i2s_d1_mfp",
	"i2s_bclk1_mclk1_mfp",
	"spi0_ss_mfp",
	"spi0_miso_mfp",
	"uart0_rx_mfp",
	"uart0_tx_mfp",
	"i2s1_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcm0_groups[] = अणु
	"i2s_d0_mfp",
	"i2s_d1_mfp",
	"i2s_lr_m_clk0_mfp",
	"i2s_bclk0_mfp",
	"i2s_bclk1_mclk1_mfp",
	"spi0_sclk_mosi_mfp",
	"spi0_ss_mfp",
	"spi0_miso_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pcm1_groups[] = अणु
	"i2s_lr_m_clk0_mfp",
	"pcm1_in_out_mfp",
	"pcm1_clk_mfp",
	"pcm1_sync_mfp",
	"lvds_oep_odn_mfp",
	"spi0_ss_mfp",
	"spi0_miso_mfp",
	"uart0_rx_mfp",
	"uart0_tx_mfp",
	"dsi_cp_dn0_mfp",
	"pcm1_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर jtag_groups[] = अणु
	"eram_a5_mfp",
	"eram_a6_mfp",
	"eram_a7_mfp",
	"eram_a8_mfp",
	"eram_a10_mfp",
	"eram_a10_mfp",
	"sd0_d2_d3_mfp",
	"sd0_cmd_mfp",
	"sd0_clk_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm0_groups[] = अणु
	"sirq0_mfp",
	"rmii_txd0_mfp",
	"rmii_rxd1_mfp",
	"eram_a5_mfp",
	"nand1_ceb3_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm1_groups[] = अणु
	"sirq1_mfp",
	"rmii_txd1_mfp",
	"rmii_rxd0_mfp",
	"eram_a6_mfp",
	"eram_a8_mfp",
	"nand1_ceb0_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm2_groups[] = अणु
	"rmii_mdc_mfp",
	"rmii_txen_mfp",
	"eram_a9_mfp",
	"eram_a11_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm3_groups[] = अणु
	"rmii_mdio_mfp",
	"rmii_rxer_mfp",
	"eram_a10_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm4_groups[] = अणु
	"pcm1_clk_mfp",
	"spi0_ss_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm5_groups[] = अणु
	"pcm1_sync_mfp",
	"spi0_miso_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sd0_groups[] = अणु
	"sd0_d0_mfp",
	"sd0_d1_mfp",
	"sd0_d2_d3_mfp",
	"sd0_cmd_mfp",
	"sd0_clk_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sd1_groups[] = अणु
	"sd1_d0_d3_mfp",
	"sd1_cmd_clk_mfp",
	"sd1_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sd2_groups[] = अणु
	"nand0_d0_ceb3_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sd3_groups[] = अणु
	"nand1_d0_ceb1_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c0_groups[] = अणु
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
	"pcm1_in_out_mfp",
	"spi0_sclk_mosi_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c4_groups[] = अणु
	"uart4_rx_tx_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c5_groups[] = अणु
	"uart0_rx_mfp",
	"uart0_tx_mfp",
पूर्ण;


अटल स्थिर अक्षर * स्थिर lvds_groups[] = अणु
	"lvds_oep_odn_mfp",
	"lvds_ocp_obn_mfp",
	"lvds_oap_oan_mfp",
	"lvds_e_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर usb20_groups[] = अणु
	"eram_a9_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर usb30_groups[] = अणु
	"eram_a10_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर gpu_groups[] = अणु
	"sd0_d0_mfp",
	"sd0_d1_mfp",
	"sd0_d2_d3_mfp",
	"sd0_cmd_mfp",
	"sd0_clk_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mipi_csi0_groups[] = अणु
	"csi0_dn0_dp3_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mipi_csi1_groups[] = अणु
	"csi1_dn0_cp_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mipi_dsi_groups[] = अणु
	"dsi_dp3_dn1_mfp",
	"dsi_cp_dn0_mfp",
	"dsi_dp2_dn2_mfp",
	"mipi_dsi_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nand0_groups[] = अणु
	"nand0_d0_ceb3_mfp",
	"nand0_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर nand1_groups[] = अणु
	"nand1_d0_ceb1_mfp",
	"nand1_ceb3_mfp",
	"nand1_ceb0_mfp",
	"nand1_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर spdअगर_groups[] = अणु
	"uart0_tx_mfp",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sirq0_groups[] = अणु
	"sirq0_mfp",
	"sirq0_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sirq1_groups[] = अणु
	"sirq1_mfp",
	"sirq1_dummy",
पूर्ण;

अटल स्थिर अक्षर * स्थिर sirq2_groups[] = अणु
	"sirq2_dummy",
पूर्ण;

अटल स्थिर काष्ठा owl_pinmux_func s900_functions[] = अणु
	[S900_MUX_ERAM] = FUNCTION(eram),
	[S900_MUX_ETH_RMII] = FUNCTION(eth_rmii),
	[S900_MUX_ETH_SMII] = FUNCTION(eth_smii),
	[S900_MUX_SPI0] = FUNCTION(spi0),
	[S900_MUX_SPI1] = FUNCTION(spi1),
	[S900_MUX_SPI2] = FUNCTION(spi2),
	[S900_MUX_SPI3] = FUNCTION(spi3),
	[S900_MUX_SENS0] = FUNCTION(sens0),
	[S900_MUX_UART0] = FUNCTION(uart0),
	[S900_MUX_UART1] = FUNCTION(uart1),
	[S900_MUX_UART2] = FUNCTION(uart2),
	[S900_MUX_UART3] = FUNCTION(uart3),
	[S900_MUX_UART4] = FUNCTION(uart4),
	[S900_MUX_UART5] = FUNCTION(uart5),
	[S900_MUX_UART6] = FUNCTION(uart6),
	[S900_MUX_I2S0] = FUNCTION(i2s0),
	[S900_MUX_I2S1] = FUNCTION(i2s1),
	[S900_MUX_PCM0] = FUNCTION(pcm0),
	[S900_MUX_PCM1] = FUNCTION(pcm1),
	[S900_MUX_JTAG] = FUNCTION(jtag),
	[S900_MUX_PWM0] = FUNCTION(pwm0),
	[S900_MUX_PWM1] = FUNCTION(pwm1),
	[S900_MUX_PWM2] = FUNCTION(pwm2),
	[S900_MUX_PWM3] = FUNCTION(pwm3),
	[S900_MUX_PWM4] = FUNCTION(pwm4),
	[S900_MUX_PWM5] = FUNCTION(pwm5),
	[S900_MUX_SD0] = FUNCTION(sd0),
	[S900_MUX_SD1] = FUNCTION(sd1),
	[S900_MUX_SD2] = FUNCTION(sd2),
	[S900_MUX_SD3] = FUNCTION(sd3),
	[S900_MUX_I2C0] = FUNCTION(i2c0),
	[S900_MUX_I2C1] = FUNCTION(i2c1),
	[S900_MUX_I2C2] = FUNCTION(i2c2),
	[S900_MUX_I2C3] = FUNCTION(i2c3),
	[S900_MUX_I2C4] = FUNCTION(i2c4),
	[S900_MUX_I2C5] = FUNCTION(i2c5),
	[S900_MUX_LVDS] = FUNCTION(lvds),
	[S900_MUX_USB30] = FUNCTION(usb30),
	[S900_MUX_USB20] = FUNCTION(usb20),
	[S900_MUX_GPU] = FUNCTION(gpu),
	[S900_MUX_MIPI_CSI0] = FUNCTION(mipi_csi0),
	[S900_MUX_MIPI_CSI1] = FUNCTION(mipi_csi1),
	[S900_MUX_MIPI_DSI] = FUNCTION(mipi_dsi),
	[S900_MUX_न_अंकD0] = FUNCTION(nand0),
	[S900_MUX_न_अंकD1] = FUNCTION(nand1),
	[S900_MUX_SPDIF] = FUNCTION(spdअगर),
	[S900_MUX_SIRQ0] = FUNCTION(sirq0),
	[S900_MUX_SIRQ1] = FUNCTION(sirq1),
	[S900_MUX_SIRQ2] = FUNCTION(sirq2)
पूर्ण;

/* PAD_PULLCTL0 */
अटल PAD_PULLCTL_CONF(ETH_RXER, 0, 18, 2);
अटल PAD_PULLCTL_CONF(SIRQ0, 0, 16, 2);
अटल PAD_PULLCTL_CONF(SIRQ1, 0, 14, 2);
अटल PAD_PULLCTL_CONF(SIRQ2, 0, 12, 2);
अटल PAD_PULLCTL_CONF(I2C0_SDATA, 0, 10, 2);
अटल PAD_PULLCTL_CONF(I2C0_SCLK, 0, 8, 2);
अटल PAD_PULLCTL_CONF(ERAM_A5, 0, 6, 2);
अटल PAD_PULLCTL_CONF(ERAM_A6, 0, 4, 2);
अटल PAD_PULLCTL_CONF(ERAM_A7, 0, 2, 2);
अटल PAD_PULLCTL_CONF(ERAM_A10, 0, 0, 2);

/* PAD_PULLCTL1 */
अटल PAD_PULLCTL_CONF(PCM1_IN, 1, 30, 2);
अटल PAD_PULLCTL_CONF(PCM1_OUT, 1, 28, 2);
अटल PAD_PULLCTL_CONF(SD0_D0, 1, 26, 2);
अटल PAD_PULLCTL_CONF(SD0_D1, 1, 24, 2);
अटल PAD_PULLCTL_CONF(SD0_D2, 1, 22, 2);
अटल PAD_PULLCTL_CONF(SD0_D3, 1, 20, 2);
अटल PAD_PULLCTL_CONF(SD0_CMD, 1, 18, 2);
अटल PAD_PULLCTL_CONF(SD0_CLK, 1, 16, 2);
अटल PAD_PULLCTL_CONF(SD1_CMD, 1, 14, 2);
अटल PAD_PULLCTL_CONF(SD1_D0, 1, 12, 2);
अटल PAD_PULLCTL_CONF(SD1_D1, 1, 10, 2);
अटल PAD_PULLCTL_CONF(SD1_D2, 1, 8, 2);
अटल PAD_PULLCTL_CONF(SD1_D3, 1, 6, 2);
अटल PAD_PULLCTL_CONF(UART0_RX, 1, 4, 2);
अटल PAD_PULLCTL_CONF(UART0_TX, 1, 2, 2);

/* PAD_PULLCTL2 */
अटल PAD_PULLCTL_CONF(I2C2_SDATA, 2, 26, 2);
अटल PAD_PULLCTL_CONF(I2C2_SCLK, 2, 24, 2);
अटल PAD_PULLCTL_CONF(SPI0_SCLK, 2, 22, 2);
अटल PAD_PULLCTL_CONF(SPI0_MOSI, 2, 20, 2);
अटल PAD_PULLCTL_CONF(I2C1_SDATA, 2, 18, 2);
अटल PAD_PULLCTL_CONF(I2C1_SCLK, 2, 16, 2);
अटल PAD_PULLCTL_CONF(न_अंकD0_D0, 2, 15, 1);
अटल PAD_PULLCTL_CONF(न_अंकD0_D1, 2, 15, 1);
अटल PAD_PULLCTL_CONF(न_अंकD0_D2, 2, 15, 1);
अटल PAD_PULLCTL_CONF(न_अंकD0_D3, 2, 15, 1);
अटल PAD_PULLCTL_CONF(न_अंकD0_D4, 2, 15, 1);
अटल PAD_PULLCTL_CONF(न_अंकD0_D5, 2, 15, 1);
अटल PAD_PULLCTL_CONF(न_अंकD0_D6, 2, 15, 1);
अटल PAD_PULLCTL_CONF(न_अंकD0_D7, 2, 15, 1);
अटल PAD_PULLCTL_CONF(न_अंकD0_DQSN, 2, 14, 1);
अटल PAD_PULLCTL_CONF(न_अंकD0_DQS, 2, 13, 1);
अटल PAD_PULLCTL_CONF(न_अंकD1_D0, 2, 12, 1);
अटल PAD_PULLCTL_CONF(न_अंकD1_D1, 2, 12, 1);
अटल PAD_PULLCTL_CONF(न_अंकD1_D2, 2, 12, 1);
अटल PAD_PULLCTL_CONF(न_अंकD1_D3, 2, 12, 1);
अटल PAD_PULLCTL_CONF(न_अंकD1_D4, 2, 12, 1);
अटल PAD_PULLCTL_CONF(न_अंकD1_D5, 2, 12, 1);
अटल PAD_PULLCTL_CONF(न_अंकD1_D6, 2, 12, 1);
अटल PAD_PULLCTL_CONF(न_अंकD1_D7, 2, 12, 1);
अटल PAD_PULLCTL_CONF(न_अंकD1_DQSN, 2, 11, 1);
अटल PAD_PULLCTL_CONF(न_अंकD1_DQS, 2, 10, 1);
अटल PAD_PULLCTL_CONF(SGPIO2, 2, 8, 2);
अटल PAD_PULLCTL_CONF(SGPIO3, 2, 6, 2);
अटल PAD_PULLCTL_CONF(UART4_RX, 2, 4, 2);
अटल PAD_PULLCTL_CONF(UART4_TX, 2, 2, 2);

/* PAD_ST0 */
अटल PAD_ST_CONF(I2C0_SDATA, 0, 30, 1);
अटल PAD_ST_CONF(UART0_RX, 0, 29, 1);
अटल PAD_ST_CONF(ETH_MDC, 0, 28, 1);
अटल PAD_ST_CONF(I2S_MCLK1, 0, 23, 1);
अटल PAD_ST_CONF(ETH_REF_CLK, 0, 22, 1);
अटल PAD_ST_CONF(ETH_TXEN, 0, 21, 1);
अटल PAD_ST_CONF(ETH_TXD0, 0, 20, 1);
अटल PAD_ST_CONF(I2S_LRCLK1, 0, 19, 1);
अटल PAD_ST_CONF(SGPIO2, 0, 18, 1);
अटल PAD_ST_CONF(SGPIO3, 0, 17, 1);
अटल PAD_ST_CONF(UART4_TX, 0, 16, 1);
अटल PAD_ST_CONF(I2S_D1, 0, 15, 1);
अटल PAD_ST_CONF(UART0_TX, 0, 14, 1);
अटल PAD_ST_CONF(SPI0_SCLK, 0, 13, 1);
अटल PAD_ST_CONF(SD0_CLK, 0, 12, 1);
अटल PAD_ST_CONF(ERAM_A5, 0, 11, 1);
अटल PAD_ST_CONF(I2C0_SCLK, 0, 7, 1);
अटल PAD_ST_CONF(ERAM_A9, 0, 6, 1);
अटल PAD_ST_CONF(LVDS_OEP, 0, 5, 1);
अटल PAD_ST_CONF(LVDS_ODN, 0, 4, 1);
अटल PAD_ST_CONF(LVDS_OAP, 0, 3, 1);
अटल PAD_ST_CONF(I2S_BCLK1, 0, 2, 1);

/* PAD_ST1 */
अटल PAD_ST_CONF(I2S_LRCLK0, 1, 29, 1);
अटल PAD_ST_CONF(UART4_RX, 1, 28, 1);
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
अटल PAD_ST_CONF(LVDS_OCP, 1, 16, 1);
अटल PAD_ST_CONF(LVDS_OBP, 1, 15, 1);
अटल PAD_ST_CONF(LVDS_OBN, 1, 14, 1);
अटल PAD_ST_CONF(PCM1_OUT, 1, 12, 1);
अटल PAD_ST_CONF(PCM1_CLK, 1, 11, 1);
अटल PAD_ST_CONF(PCM1_IN, 1, 10, 1);
अटल PAD_ST_CONF(PCM1_SYNC, 1, 9, 1);
अटल PAD_ST_CONF(I2C1_SCLK, 1, 8, 1);
अटल PAD_ST_CONF(I2C1_SDATA, 1, 7, 1);
अटल PAD_ST_CONF(I2C2_SCLK, 1, 6, 1);
अटल PAD_ST_CONF(I2C2_SDATA, 1, 5, 1);
अटल PAD_ST_CONF(SPI0_MOSI, 1, 4, 1);
अटल PAD_ST_CONF(SPI0_MISO, 1, 3, 1);
अटल PAD_ST_CONF(SPI0_SS, 1, 2, 1);
अटल PAD_ST_CONF(I2S_BCLK0, 1, 1, 1);
अटल PAD_ST_CONF(I2S_MCLK0, 1, 0, 1);

/* Pad info table */
अटल स्थिर काष्ठा owl_padinfo s900_padinfo[NUM_PADS] = अणु
	[ETH_TXD0] = PAD_INFO_ST(ETH_TXD0),
	[ETH_TXD1] = PAD_INFO_ST(ETH_TXD1),
	[ETH_TXEN] = PAD_INFO_ST(ETH_TXEN),
	[ETH_RXER] = PAD_INFO_PULLCTL_ST(ETH_RXER),
	[ETH_CRS_DV] = PAD_INFO_ST(ETH_CRS_DV),
	[ETH_RXD1] = PAD_INFO_ST(ETH_RXD1),
	[ETH_RXD0] = PAD_INFO_ST(ETH_RXD0),
	[ETH_REF_CLK] = PAD_INFO_ST(ETH_REF_CLK),
	[ETH_MDC] = PAD_INFO_ST(ETH_MDC),
	[ETH_MDIO] = PAD_INFO(ETH_MDIO),
	[SIRQ0] = PAD_INFO_PULLCTL(SIRQ0),
	[SIRQ1] = PAD_INFO_PULLCTL(SIRQ1),
	[SIRQ2] = PAD_INFO_PULLCTL(SIRQ2),
	[I2S_D0] = PAD_INFO(I2S_D0),
	[I2S_BCLK0] = PAD_INFO_ST(I2S_BCLK0),
	[I2S_LRCLK0] = PAD_INFO_ST(I2S_LRCLK0),
	[I2S_MCLK0] = PAD_INFO_ST(I2S_MCLK0),
	[I2S_D1] = PAD_INFO_ST(I2S_D1),
	[I2S_BCLK1] = PAD_INFO_ST(I2S_BCLK1),
	[I2S_LRCLK1] = PAD_INFO_ST(I2S_LRCLK1),
	[I2S_MCLK1] = PAD_INFO_ST(I2S_MCLK1),
	[PCM1_IN] = PAD_INFO_PULLCTL_ST(PCM1_IN),
	[PCM1_CLK] = PAD_INFO_ST(PCM1_CLK),
	[PCM1_SYNC] = PAD_INFO_ST(PCM1_SYNC),
	[PCM1_OUT] = PAD_INFO_PULLCTL_ST(PCM1_OUT),
	[ERAM_A5] = PAD_INFO_PULLCTL_ST(ERAM_A5),
	[ERAM_A6] = PAD_INFO_PULLCTL(ERAM_A6),
	[ERAM_A7] = PAD_INFO_PULLCTL(ERAM_A7),
	[ERAM_A8] = PAD_INFO(ERAM_A8),
	[ERAM_A9] = PAD_INFO_ST(ERAM_A9),
	[ERAM_A10] = PAD_INFO_PULLCTL(ERAM_A10),
	[ERAM_A11] = PAD_INFO(ERAM_A11),
	[LVDS_OEP] = PAD_INFO_ST(LVDS_OEP),
	[LVDS_OEN] = PAD_INFO(LVDS_OEN),
	[LVDS_ODP] = PAD_INFO(LVDS_ODP),
	[LVDS_ODN] = PAD_INFO_ST(LVDS_ODN),
	[LVDS_OCP] = PAD_INFO_ST(LVDS_OCP),
	[LVDS_OCN] = PAD_INFO(LVDS_OCN),
	[LVDS_OBP] = PAD_INFO_ST(LVDS_OBP),
	[LVDS_OBN] = PAD_INFO_ST(LVDS_OBN),
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
	[SD0_D0] = PAD_INFO_PULLCTL(SD0_D0),
	[SD0_D1] = PAD_INFO_PULLCTL(SD0_D1),
	[SD0_D2] = PAD_INFO_PULLCTL(SD0_D2),
	[SD0_D3] = PAD_INFO_PULLCTL(SD0_D3),
	[SD1_D0] = PAD_INFO_PULLCTL(SD1_D0),
	[SD1_D1] = PAD_INFO_PULLCTL(SD1_D1),
	[SD1_D2] = PAD_INFO_PULLCTL(SD1_D2),
	[SD1_D3] = PAD_INFO_PULLCTL(SD1_D3),
	[SD0_CMD] = PAD_INFO_PULLCTL(SD0_CMD),
	[SD0_CLK] = PAD_INFO_PULLCTL_ST(SD0_CLK),
	[SD1_CMD] = PAD_INFO_PULLCTL(SD1_CMD),
	[SD1_CLK] = PAD_INFO(SD1_CLK),
	[SPI0_SCLK] = PAD_INFO_PULLCTL_ST(SPI0_SCLK),
	[SPI0_SS] = PAD_INFO_ST(SPI0_SS),
	[SPI0_MISO] = PAD_INFO_ST(SPI0_MISO),
	[SPI0_MOSI] = PAD_INFO_PULLCTL_ST(SPI0_MOSI),
	[UART0_RX] = PAD_INFO_PULLCTL_ST(UART0_RX),
	[UART0_TX] = PAD_INFO_PULLCTL_ST(UART0_TX),
	[UART2_RX] = PAD_INFO_ST(UART2_RX),
	[UART2_TX] = PAD_INFO(UART2_TX),
	[UART2_RTSB] = PAD_INFO_ST(UART2_RTSB),
	[UART2_CTSB] = PAD_INFO_ST(UART2_CTSB),
	[UART3_RX] = PAD_INFO_ST(UART3_RX),
	[UART3_TX] = PAD_INFO(UART3_TX),
	[UART3_RTSB] = PAD_INFO_ST(UART3_RTSB),
	[UART3_CTSB] = PAD_INFO_ST(UART3_CTSB),
	[UART4_RX] = PAD_INFO_PULLCTL_ST(UART4_RX),
	[UART4_TX] = PAD_INFO_PULLCTL_ST(UART4_TX),
	[I2C0_SCLK] = PAD_INFO_PULLCTL_ST(I2C0_SCLK),
	[I2C0_SDATA] = PAD_INFO_PULLCTL_ST(I2C0_SDATA),
	[I2C1_SCLK] = PAD_INFO_PULLCTL_ST(I2C1_SCLK),
	[I2C1_SDATA] = PAD_INFO_PULLCTL_ST(I2C1_SDATA),
	[I2C2_SCLK] = PAD_INFO_PULLCTL_ST(I2C2_SCLK),
	[I2C2_SDATA] = PAD_INFO_PULLCTL_ST(I2C2_SDATA),
	[CSI0_DN0] = PAD_INFO(CSI0_DN0),
	[CSI0_DP0] = PAD_INFO(CSI0_DP0),
	[CSI0_DN1] = PAD_INFO(CSI0_DN1),
	[CSI0_DP1] = PAD_INFO(CSI0_DP1),
	[CSI0_CN] = PAD_INFO(CSI0_CN),
	[CSI0_CP] = PAD_INFO(CSI0_CP),
	[CSI0_DN2] = PAD_INFO(CSI0_DN2),
	[CSI0_DP2] = PAD_INFO(CSI0_DP2),
	[CSI0_DN3] = PAD_INFO(CSI0_DN3),
	[CSI0_DP3] = PAD_INFO(CSI0_DP3),
	[DSI_DP3] = PAD_INFO(DSI_DP3),
	[DSI_DN3] = PAD_INFO(DSI_DN3),
	[DSI_DP1] = PAD_INFO(DSI_DP1),
	[DSI_DN1] = PAD_INFO(DSI_DN1),
	[DSI_CP] = PAD_INFO(DSI_CP),
	[DSI_CN] = PAD_INFO(DSI_CN),
	[DSI_DP0] = PAD_INFO(DSI_DP0),
	[DSI_DN0] = PAD_INFO(DSI_DN0),
	[DSI_DP2] = PAD_INFO(DSI_DP2),
	[DSI_DN2] = PAD_INFO(DSI_DN2),
	[SENSOR0_PCLK] = PAD_INFO(SENSOR0_PCLK),
	[CSI1_DN0] = PAD_INFO(CSI1_DN0),
	[CSI1_DP0] = PAD_INFO(CSI1_DP0),
	[CSI1_DN1] = PAD_INFO(CSI1_DN1),
	[CSI1_DP1] = PAD_INFO(CSI1_DP1),
	[CSI1_CN] = PAD_INFO(CSI1_CN),
	[CSI1_CP] = PAD_INFO(CSI1_CP),
	[SENSOR0_CKOUT] = PAD_INFO(SENSOR0_CKOUT),
	[न_अंकD0_D0] = PAD_INFO_PULLCTL(न_अंकD0_D0),
	[न_अंकD0_D1] = PAD_INFO_PULLCTL(न_अंकD0_D1),
	[न_अंकD0_D2] = PAD_INFO_PULLCTL(न_अंकD0_D2),
	[न_अंकD0_D3] = PAD_INFO_PULLCTL(न_अंकD0_D3),
	[न_अंकD0_D4] = PAD_INFO_PULLCTL(न_अंकD0_D4),
	[न_अंकD0_D5] = PAD_INFO_PULLCTL(न_अंकD0_D5),
	[न_अंकD0_D6] = PAD_INFO_PULLCTL(न_अंकD0_D6),
	[न_अंकD0_D7] = PAD_INFO_PULLCTL(न_अंकD0_D7),
	[न_अंकD0_DQS] = PAD_INFO_PULLCTL(न_अंकD0_DQS),
	[न_अंकD0_DQSN] = PAD_INFO_PULLCTL(न_अंकD0_DQSN),
	[न_अंकD0_ALE] = PAD_INFO(न_अंकD0_ALE),
	[न_अंकD0_CLE] = PAD_INFO(न_अंकD0_CLE),
	[न_अंकD0_CEB0] = PAD_INFO(न_अंकD0_CEB0),
	[न_अंकD0_CEB1] = PAD_INFO(न_अंकD0_CEB1),
	[न_अंकD0_CEB2] = PAD_INFO(न_अंकD0_CEB2),
	[न_अंकD0_CEB3] = PAD_INFO(न_अंकD0_CEB3),
	[न_अंकD1_D0] = PAD_INFO_PULLCTL(न_अंकD1_D0),
	[न_अंकD1_D1] = PAD_INFO_PULLCTL(न_अंकD1_D1),
	[न_अंकD1_D2] = PAD_INFO_PULLCTL(न_अंकD1_D2),
	[न_अंकD1_D3] = PAD_INFO_PULLCTL(न_अंकD1_D3),
	[न_अंकD1_D4] = PAD_INFO_PULLCTL(न_अंकD1_D4),
	[न_अंकD1_D5] = PAD_INFO_PULLCTL(न_अंकD1_D5),
	[न_अंकD1_D6] = PAD_INFO_PULLCTL(न_अंकD1_D6),
	[न_अंकD1_D7] = PAD_INFO_PULLCTL(न_अंकD1_D7),
	[न_अंकD1_DQS] = PAD_INFO_PULLCTL(न_अंकD1_DQS),
	[न_अंकD1_DQSN] = PAD_INFO_PULLCTL(न_अंकD1_DQSN),
	[न_अंकD1_ALE] = PAD_INFO(न_अंकD1_ALE),
	[न_अंकD1_CLE] = PAD_INFO(न_अंकD1_CLE),
	[न_अंकD1_CEB0] = PAD_INFO(न_अंकD1_CEB0),
	[न_अंकD1_CEB1] = PAD_INFO(न_अंकD1_CEB1),
	[न_अंकD1_CEB2] = PAD_INFO(न_अंकD1_CEB2),
	[न_अंकD1_CEB3] = PAD_INFO(न_अंकD1_CEB3),
	[SGPIO0] = PAD_INFO(SGPIO0),
	[SGPIO1] = PAD_INFO(SGPIO1),
	[SGPIO2] = PAD_INFO_PULLCTL_ST(SGPIO2),
	[SGPIO3] = PAD_INFO_PULLCTL_ST(SGPIO3)
पूर्ण;

अटल स्थिर काष्ठा owl_gpio_port s900_gpio_ports[] = अणु
	OWL_GPIO_PORT(A, 0x0000, 32, 0x0, 0x4, 0x8, 0x204, 0x208, 0x20C, 0x240, 0),
	OWL_GPIO_PORT(B, 0x000C, 32, 0x0, 0x4, 0x8, 0x534, 0x204, 0x208, 0x23C, 0),
	OWL_GPIO_PORT(C, 0x0018, 12, 0x0, 0x4, 0x8, 0x52C, 0x200, 0x204, 0x238, 0),
	OWL_GPIO_PORT(D, 0x0024, 30, 0x0, 0x4, 0x8, 0x524, 0x1FC, 0x200, 0x234, 0),
	OWL_GPIO_PORT(E, 0x0030, 32, 0x0, 0x4, 0x8, 0x51C, 0x1F8, 0x1FC, 0x230, 0),
	OWL_GPIO_PORT(F, 0x00F0, 8, 0x0, 0x4, 0x8, 0x460, 0x140, 0x144, 0x178, 0)
पूर्ण;

क्रमागत s900_pinconf_pull अणु
	OWL_PINCONF_PULL_HIZ,
	OWL_PINCONF_PULL_DOWN,
	OWL_PINCONF_PULL_UP,
	OWL_PINCONF_PULL_HOLD,
पूर्ण;

अटल पूर्णांक s900_pad_pinconf_arg2val(स्थिर काष्ठा owl_padinfo *info,
				अचिन्हित पूर्णांक param,
				u32 *arg)
अणु
	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_BUS_HOLD:
		*arg = OWL_PINCONF_PULL_HOLD;
		अवरोध;
	हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		*arg = OWL_PINCONF_PULL_HIZ;
		अवरोध;
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

अटल पूर्णांक s900_pad_pinconf_val2arg(स्थिर काष्ठा owl_padinfo *padinfo,
				अचिन्हित पूर्णांक param,
				u32 *arg)
अणु
	चयन (param) अणु
	हाल PIN_CONFIG_BIAS_BUS_HOLD:
		*arg = *arg == OWL_PINCONF_PULL_HOLD;
		अवरोध;
	हाल PIN_CONFIG_BIAS_HIGH_IMPEDANCE:
		*arg = *arg == OWL_PINCONF_PULL_HIZ;
		अवरोध;
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

अटल काष्ठा owl_pinctrl_soc_data s900_pinctrl_data = अणु
	.padinfo = s900_padinfo,
	.pins = (स्थिर काष्ठा pinctrl_pin_desc *)s900_pads,
	.npins = ARRAY_SIZE(s900_pads),
	.functions = s900_functions,
	.nfunctions = ARRAY_SIZE(s900_functions),
	.groups = s900_groups,
	.ngroups = ARRAY_SIZE(s900_groups),
	.ngpios = NUM_GPIOS,
	.ports = s900_gpio_ports,
	.nports = ARRAY_SIZE(s900_gpio_ports),
	.padctl_arg2val = s900_pad_pinconf_arg2val,
	.padctl_val2arg = s900_pad_pinconf_val2arg,
पूर्ण;

अटल पूर्णांक s900_pinctrl_probe(काष्ठा platक्रमm_device *pdev)
अणु
	वापस owl_pinctrl_probe(pdev, &s900_pinctrl_data);
पूर्ण

अटल स्थिर काष्ठा of_device_id s900_pinctrl_of_match[] = अणु
	अणु .compatible = "actions,s900-pinctrl", पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver s900_pinctrl_driver = अणु
	.driver = अणु
		.name = "pinctrl-s900",
		.of_match_table = of_match_ptr(s900_pinctrl_of_match),
	पूर्ण,
	.probe = s900_pinctrl_probe,
पूर्ण;

अटल पूर्णांक __init s900_pinctrl_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&s900_pinctrl_driver);
पूर्ण
arch_initcall(s900_pinctrl_init);

अटल व्योम __निकास s900_pinctrl_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&s900_pinctrl_driver);
पूर्ण
module_निकास(s900_pinctrl_निकास);

MODULE_AUTHOR("Actions Semi Inc.");
MODULE_AUTHOR("Manivannan Sadhasivam <manivannan.sadhasivam@linaro.org>");
MODULE_DESCRIPTION("Actions Semi S900 SoC Pinctrl Driver");
MODULE_LICENSE("GPL");
