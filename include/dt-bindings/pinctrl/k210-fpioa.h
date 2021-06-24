<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * Copyright (C) 2020 Sean Anderson <seanga2@gmail.com>
 * Copyright (c) 2020 Western Digital Corporation or its affiliates.
 */
#अगर_अघोषित PINCTRL_K210_FPIOA_H
#घोषणा PINCTRL_K210_FPIOA_H

/*
 * Full list of FPIOA functions from
 * kendryte-standalone-sdk/lib/drivers/include/fpioa.h
 */
#घोषणा K210_PCF_MASK		GENMASK(7, 0)
#घोषणा K210_PCF_JTAG_TCLK	0   /* JTAG Test Clock */
#घोषणा K210_PCF_JTAG_TDI	1   /* JTAG Test Data In */
#घोषणा K210_PCF_JTAG_TMS	2   /* JTAG Test Mode Select */
#घोषणा K210_PCF_JTAG_TDO	3   /* JTAG Test Data Out */
#घोषणा K210_PCF_SPI0_D0	4   /* SPI0 Data 0 */
#घोषणा K210_PCF_SPI0_D1	5   /* SPI0 Data 1 */
#घोषणा K210_PCF_SPI0_D2	6   /* SPI0 Data 2 */
#घोषणा K210_PCF_SPI0_D3	7   /* SPI0 Data 3 */
#घोषणा K210_PCF_SPI0_D4	8   /* SPI0 Data 4 */
#घोषणा K210_PCF_SPI0_D5	9   /* SPI0 Data 5 */
#घोषणा K210_PCF_SPI0_D6	10  /* SPI0 Data 6 */
#घोषणा K210_PCF_SPI0_D7	11  /* SPI0 Data 7 */
#घोषणा K210_PCF_SPI0_SS0	12  /* SPI0 Chip Select 0 */
#घोषणा K210_PCF_SPI0_SS1	13  /* SPI0 Chip Select 1 */
#घोषणा K210_PCF_SPI0_SS2	14  /* SPI0 Chip Select 2 */
#घोषणा K210_PCF_SPI0_SS3	15  /* SPI0 Chip Select 3 */
#घोषणा K210_PCF_SPI0_ARB	16  /* SPI0 Arbitration */
#घोषणा K210_PCF_SPI0_SCLK	17  /* SPI0 Serial Clock */
#घोषणा K210_PCF_UARTHS_RX	18  /* UART High speed Receiver */
#घोषणा K210_PCF_UARTHS_TX	19  /* UART High speed Transmitter */
#घोषणा K210_PCF_RESV6		20  /* Reserved function */
#घोषणा K210_PCF_RESV7		21  /* Reserved function */
#घोषणा K210_PCF_CLK_SPI1	22  /* Clock SPI1 */
#घोषणा K210_PCF_CLK_I2C1	23  /* Clock I2C1 */
#घोषणा K210_PCF_GPIOHS0	24  /* GPIO High speed 0 */
#घोषणा K210_PCF_GPIOHS1	25  /* GPIO High speed 1 */
#घोषणा K210_PCF_GPIOHS2	26  /* GPIO High speed 2 */
#घोषणा K210_PCF_GPIOHS3	27  /* GPIO High speed 3 */
#घोषणा K210_PCF_GPIOHS4	28  /* GPIO High speed 4 */
#घोषणा K210_PCF_GPIOHS5	29  /* GPIO High speed 5 */
#घोषणा K210_PCF_GPIOHS6	30  /* GPIO High speed 6 */
#घोषणा K210_PCF_GPIOHS7	31  /* GPIO High speed 7 */
#घोषणा K210_PCF_GPIOHS8	32  /* GPIO High speed 8 */
#घोषणा K210_PCF_GPIOHS9	33  /* GPIO High speed 9 */
#घोषणा K210_PCF_GPIOHS10	34  /* GPIO High speed 10 */
#घोषणा K210_PCF_GPIOHS11	35  /* GPIO High speed 11 */
#घोषणा K210_PCF_GPIOHS12	36  /* GPIO High speed 12 */
#घोषणा K210_PCF_GPIOHS13	37  /* GPIO High speed 13 */
#घोषणा K210_PCF_GPIOHS14	38  /* GPIO High speed 14 */
#घोषणा K210_PCF_GPIOHS15	39  /* GPIO High speed 15 */
#घोषणा K210_PCF_GPIOHS16	40  /* GPIO High speed 16 */
#घोषणा K210_PCF_GPIOHS17	41  /* GPIO High speed 17 */
#घोषणा K210_PCF_GPIOHS18	42  /* GPIO High speed 18 */
#घोषणा K210_PCF_GPIOHS19	43  /* GPIO High speed 19 */
#घोषणा K210_PCF_GPIOHS20	44  /* GPIO High speed 20 */
#घोषणा K210_PCF_GPIOHS21	45  /* GPIO High speed 21 */
#घोषणा K210_PCF_GPIOHS22	46  /* GPIO High speed 22 */
#घोषणा K210_PCF_GPIOHS23	47  /* GPIO High speed 23 */
#घोषणा K210_PCF_GPIOHS24	48  /* GPIO High speed 24 */
#घोषणा K210_PCF_GPIOHS25	49  /* GPIO High speed 25 */
#घोषणा K210_PCF_GPIOHS26	50  /* GPIO High speed 26 */
#घोषणा K210_PCF_GPIOHS27	51  /* GPIO High speed 27 */
#घोषणा K210_PCF_GPIOHS28	52  /* GPIO High speed 28 */
#घोषणा K210_PCF_GPIOHS29	53  /* GPIO High speed 29 */
#घोषणा K210_PCF_GPIOHS30	54  /* GPIO High speed 30 */
#घोषणा K210_PCF_GPIOHS31	55  /* GPIO High speed 31 */
#घोषणा K210_PCF_GPIO0		56  /* GPIO pin 0 */
#घोषणा K210_PCF_GPIO1		57  /* GPIO pin 1 */
#घोषणा K210_PCF_GPIO2		58  /* GPIO pin 2 */
#घोषणा K210_PCF_GPIO3		59  /* GPIO pin 3 */
#घोषणा K210_PCF_GPIO4		60  /* GPIO pin 4 */
#घोषणा K210_PCF_GPIO5		61  /* GPIO pin 5 */
#घोषणा K210_PCF_GPIO6		62  /* GPIO pin 6 */
#घोषणा K210_PCF_GPIO7		63  /* GPIO pin 7 */
#घोषणा K210_PCF_UART1_RX	64  /* UART1 Receiver */
#घोषणा K210_PCF_UART1_TX	65  /* UART1 Transmitter */
#घोषणा K210_PCF_UART2_RX	66  /* UART2 Receiver */
#घोषणा K210_PCF_UART2_TX	67  /* UART2 Transmitter */
#घोषणा K210_PCF_UART3_RX	68  /* UART3 Receiver */
#घोषणा K210_PCF_UART3_TX	69  /* UART3 Transmitter */
#घोषणा K210_PCF_SPI1_D0	70  /* SPI1 Data 0 */
#घोषणा K210_PCF_SPI1_D1	71  /* SPI1 Data 1 */
#घोषणा K210_PCF_SPI1_D2	72  /* SPI1 Data 2 */
#घोषणा K210_PCF_SPI1_D3	73  /* SPI1 Data 3 */
#घोषणा K210_PCF_SPI1_D4	74  /* SPI1 Data 4 */
#घोषणा K210_PCF_SPI1_D5	75  /* SPI1 Data 5 */
#घोषणा K210_PCF_SPI1_D6	76  /* SPI1 Data 6 */
#घोषणा K210_PCF_SPI1_D7	77  /* SPI1 Data 7 */
#घोषणा K210_PCF_SPI1_SS0	78  /* SPI1 Chip Select 0 */
#घोषणा K210_PCF_SPI1_SS1	79  /* SPI1 Chip Select 1 */
#घोषणा K210_PCF_SPI1_SS2	80  /* SPI1 Chip Select 2 */
#घोषणा K210_PCF_SPI1_SS3	81  /* SPI1 Chip Select 3 */
#घोषणा K210_PCF_SPI1_ARB	82  /* SPI1 Arbitration */
#घोषणा K210_PCF_SPI1_SCLK	83  /* SPI1 Serial Clock */
#घोषणा K210_PCF_SPI2_D0	84  /* SPI2 Data 0 */
#घोषणा K210_PCF_SPI2_SS	85  /* SPI2 Select */
#घोषणा K210_PCF_SPI2_SCLK	86  /* SPI2 Serial Clock */
#घोषणा K210_PCF_I2S0_MCLK	87  /* I2S0 Master Clock */
#घोषणा K210_PCF_I2S0_SCLK	88  /* I2S0 Serial Clock(BCLK) */
#घोषणा K210_PCF_I2S0_WS	89  /* I2S0 Word Select(LRCLK) */
#घोषणा K210_PCF_I2S0_IN_D0	90  /* I2S0 Serial Data Input 0 */
#घोषणा K210_PCF_I2S0_IN_D1	91  /* I2S0 Serial Data Input 1 */
#घोषणा K210_PCF_I2S0_IN_D2	92  /* I2S0 Serial Data Input 2 */
#घोषणा K210_PCF_I2S0_IN_D3	93  /* I2S0 Serial Data Input 3 */
#घोषणा K210_PCF_I2S0_OUT_D0	94  /* I2S0 Serial Data Output 0 */
#घोषणा K210_PCF_I2S0_OUT_D1	95  /* I2S0 Serial Data Output 1 */
#घोषणा K210_PCF_I2S0_OUT_D2	96  /* I2S0 Serial Data Output 2 */
#घोषणा K210_PCF_I2S0_OUT_D3	97  /* I2S0 Serial Data Output 3 */
#घोषणा K210_PCF_I2S1_MCLK	98  /* I2S1 Master Clock */
#घोषणा K210_PCF_I2S1_SCLK	99  /* I2S1 Serial Clock(BCLK) */
#घोषणा K210_PCF_I2S1_WS	100 /* I2S1 Word Select(LRCLK) */
#घोषणा K210_PCF_I2S1_IN_D0	101 /* I2S1 Serial Data Input 0 */
#घोषणा K210_PCF_I2S1_IN_D1	102 /* I2S1 Serial Data Input 1 */
#घोषणा K210_PCF_I2S1_IN_D2	103 /* I2S1 Serial Data Input 2 */
#घोषणा K210_PCF_I2S1_IN_D3	104 /* I2S1 Serial Data Input 3 */
#घोषणा K210_PCF_I2S1_OUT_D0	105 /* I2S1 Serial Data Output 0 */
#घोषणा K210_PCF_I2S1_OUT_D1	106 /* I2S1 Serial Data Output 1 */
#घोषणा K210_PCF_I2S1_OUT_D2	107 /* I2S1 Serial Data Output 2 */
#घोषणा K210_PCF_I2S1_OUT_D3	108 /* I2S1 Serial Data Output 3 */
#घोषणा K210_PCF_I2S2_MCLK	109 /* I2S2 Master Clock */
#घोषणा K210_PCF_I2S2_SCLK	110 /* I2S2 Serial Clock(BCLK) */
#घोषणा K210_PCF_I2S2_WS	111 /* I2S2 Word Select(LRCLK) */
#घोषणा K210_PCF_I2S2_IN_D0	112 /* I2S2 Serial Data Input 0 */
#घोषणा K210_PCF_I2S2_IN_D1	113 /* I2S2 Serial Data Input 1 */
#घोषणा K210_PCF_I2S2_IN_D2	114 /* I2S2 Serial Data Input 2 */
#घोषणा K210_PCF_I2S2_IN_D3	115 /* I2S2 Serial Data Input 3 */
#घोषणा K210_PCF_I2S2_OUT_D0	116 /* I2S2 Serial Data Output 0 */
#घोषणा K210_PCF_I2S2_OUT_D1	117 /* I2S2 Serial Data Output 1 */
#घोषणा K210_PCF_I2S2_OUT_D2	118 /* I2S2 Serial Data Output 2 */
#घोषणा K210_PCF_I2S2_OUT_D3	119 /* I2S2 Serial Data Output 3 */
#घोषणा K210_PCF_RESV0		120 /* Reserved function */
#घोषणा K210_PCF_RESV1		121 /* Reserved function */
#घोषणा K210_PCF_RESV2		122 /* Reserved function */
#घोषणा K210_PCF_RESV3		123 /* Reserved function */
#घोषणा K210_PCF_RESV4		124 /* Reserved function */
#घोषणा K210_PCF_RESV5		125 /* Reserved function */
#घोषणा K210_PCF_I2C0_SCLK	126 /* I2C0 Serial Clock */
#घोषणा K210_PCF_I2C0_SDA	127 /* I2C0 Serial Data */
#घोषणा K210_PCF_I2C1_SCLK	128 /* I2C1 Serial Clock */
#घोषणा K210_PCF_I2C1_SDA	129 /* I2C1 Serial Data */
#घोषणा K210_PCF_I2C2_SCLK	130 /* I2C2 Serial Clock */
#घोषणा K210_PCF_I2C2_SDA	131 /* I2C2 Serial Data */
#घोषणा K210_PCF_DVP_XCLK	132 /* DVP System Clock */
#घोषणा K210_PCF_DVP_RST	133 /* DVP System Reset */
#घोषणा K210_PCF_DVP_PWDN	134 /* DVP Power Down Mode */
#घोषणा K210_PCF_DVP_VSYNC	135 /* DVP Vertical Sync */
#घोषणा K210_PCF_DVP_HSYNC	136 /* DVP Horizontal Sync */
#घोषणा K210_PCF_DVP_PCLK	137 /* Pixel Clock */
#घोषणा K210_PCF_DVP_D0		138 /* Data Bit 0 */
#घोषणा K210_PCF_DVP_D1		139 /* Data Bit 1 */
#घोषणा K210_PCF_DVP_D2		140 /* Data Bit 2 */
#घोषणा K210_PCF_DVP_D3		141 /* Data Bit 3 */
#घोषणा K210_PCF_DVP_D4		142 /* Data Bit 4 */
#घोषणा K210_PCF_DVP_D5		143 /* Data Bit 5 */
#घोषणा K210_PCF_DVP_D6		144 /* Data Bit 6 */
#घोषणा K210_PCF_DVP_D7		145 /* Data Bit 7 */
#घोषणा K210_PCF_SCCB_SCLK	146 /* Serial Camera Control Bus Clock */
#घोषणा K210_PCF_SCCB_SDA	147 /* Serial Camera Control Bus Data */
#घोषणा K210_PCF_UART1_CTS	148 /* UART1 Clear To Send */
#घोषणा K210_PCF_UART1_DSR	149 /* UART1 Data Set Ready */
#घोषणा K210_PCF_UART1_DCD	150 /* UART1 Data Carrier Detect */
#घोषणा K210_PCF_UART1_RI	151 /* UART1 Ring Indicator */
#घोषणा K210_PCF_UART1_SIR_IN	152 /* UART1 Serial Infrared Input */
#घोषणा K210_PCF_UART1_DTR	153 /* UART1 Data Terminal Ready */
#घोषणा K210_PCF_UART1_RTS	154 /* UART1 Request To Send */
#घोषणा K210_PCF_UART1_OUT2	155 /* UART1 User-designated Output 2 */
#घोषणा K210_PCF_UART1_OUT1	156 /* UART1 User-designated Output 1 */
#घोषणा K210_PCF_UART1_SIR_OUT	157 /* UART1 Serial Infrared Output */
#घोषणा K210_PCF_UART1_BAUD	158 /* UART1 Transmit Clock Output */
#घोषणा K210_PCF_UART1_RE	159 /* UART1 Receiver Output Enable */
#घोषणा K210_PCF_UART1_DE	160 /* UART1 Driver Output Enable */
#घोषणा K210_PCF_UART1_RS485_EN	161 /* UART1 RS485 Enable */
#घोषणा K210_PCF_UART2_CTS	162 /* UART2 Clear To Send */
#घोषणा K210_PCF_UART2_DSR	163 /* UART2 Data Set Ready */
#घोषणा K210_PCF_UART2_DCD	164 /* UART2 Data Carrier Detect */
#घोषणा K210_PCF_UART2_RI	165 /* UART2 Ring Indicator */
#घोषणा K210_PCF_UART2_SIR_IN	166 /* UART2 Serial Infrared Input */
#घोषणा K210_PCF_UART2_DTR	167 /* UART2 Data Terminal Ready */
#घोषणा K210_PCF_UART2_RTS	168 /* UART2 Request To Send */
#घोषणा K210_PCF_UART2_OUT2	169 /* UART2 User-designated Output 2 */
#घोषणा K210_PCF_UART2_OUT1	170 /* UART2 User-designated Output 1 */
#घोषणा K210_PCF_UART2_SIR_OUT	171 /* UART2 Serial Infrared Output */
#घोषणा K210_PCF_UART2_BAUD	172 /* UART2 Transmit Clock Output */
#घोषणा K210_PCF_UART2_RE	173 /* UART2 Receiver Output Enable */
#घोषणा K210_PCF_UART2_DE	174 /* UART2 Driver Output Enable */
#घोषणा K210_PCF_UART2_RS485_EN	175 /* UART2 RS485 Enable */
#घोषणा K210_PCF_UART3_CTS	176 /* UART3 Clear To Send */
#घोषणा K210_PCF_UART3_DSR	177 /* UART3 Data Set Ready */
#घोषणा K210_PCF_UART3_DCD	178 /* UART3 Data Carrier Detect */
#घोषणा K210_PCF_UART3_RI	179 /* UART3 Ring Indicator */
#घोषणा K210_PCF_UART3_SIR_IN	180 /* UART3 Serial Infrared Input */
#घोषणा K210_PCF_UART3_DTR	181 /* UART3 Data Terminal Ready */
#घोषणा K210_PCF_UART3_RTS	182 /* UART3 Request To Send */
#घोषणा K210_PCF_UART3_OUT2	183 /* UART3 User-designated Output 2 */
#घोषणा K210_PCF_UART3_OUT1	184 /* UART3 User-designated Output 1 */
#घोषणा K210_PCF_UART3_SIR_OUT	185 /* UART3 Serial Infrared Output */
#घोषणा K210_PCF_UART3_BAUD	186 /* UART3 Transmit Clock Output */
#घोषणा K210_PCF_UART3_RE	187 /* UART3 Receiver Output Enable */
#घोषणा K210_PCF_UART3_DE	188 /* UART3 Driver Output Enable */
#घोषणा K210_PCF_UART3_RS485_EN	189 /* UART3 RS485 Enable */
#घोषणा K210_PCF_TIMER0_TOGGLE1	190 /* TIMER0 Toggle Output 1 */
#घोषणा K210_PCF_TIMER0_TOGGLE2	191 /* TIMER0 Toggle Output 2 */
#घोषणा K210_PCF_TIMER0_TOGGLE3	192 /* TIMER0 Toggle Output 3 */
#घोषणा K210_PCF_TIMER0_TOGGLE4	193 /* TIMER0 Toggle Output 4 */
#घोषणा K210_PCF_TIMER1_TOGGLE1	194 /* TIMER1 Toggle Output 1 */
#घोषणा K210_PCF_TIMER1_TOGGLE2	195 /* TIMER1 Toggle Output 2 */
#घोषणा K210_PCF_TIMER1_TOGGLE3	196 /* TIMER1 Toggle Output 3 */
#घोषणा K210_PCF_TIMER1_TOGGLE4	197 /* TIMER1 Toggle Output 4 */
#घोषणा K210_PCF_TIMER2_TOGGLE1	198 /* TIMER2 Toggle Output 1 */
#घोषणा K210_PCF_TIMER2_TOGGLE2	199 /* TIMER2 Toggle Output 2 */
#घोषणा K210_PCF_TIMER2_TOGGLE3	200 /* TIMER2 Toggle Output 3 */
#घोषणा K210_PCF_TIMER2_TOGGLE4	201 /* TIMER2 Toggle Output 4 */
#घोषणा K210_PCF_CLK_SPI2	202 /* Clock SPI2 */
#घोषणा K210_PCF_CLK_I2C2	203 /* Clock I2C2 */
#घोषणा K210_PCF_INTERNAL0	204 /* Internal function संकेत 0 */
#घोषणा K210_PCF_INTERNAL1	205 /* Internal function संकेत 1 */
#घोषणा K210_PCF_INTERNAL2	206 /* Internal function संकेत 2 */
#घोषणा K210_PCF_INTERNAL3	207 /* Internal function संकेत 3 */
#घोषणा K210_PCF_INTERNAL4	208 /* Internal function संकेत 4 */
#घोषणा K210_PCF_INTERNAL5	209 /* Internal function संकेत 5 */
#घोषणा K210_PCF_INTERNAL6	210 /* Internal function संकेत 6 */
#घोषणा K210_PCF_INTERNAL7	211 /* Internal function संकेत 7 */
#घोषणा K210_PCF_INTERNAL8	212 /* Internal function संकेत 8 */
#घोषणा K210_PCF_INTERNAL9	213 /* Internal function संकेत 9 */
#घोषणा K210_PCF_INTERNAL10	214 /* Internal function संकेत 10 */
#घोषणा K210_PCF_INTERNAL11	215 /* Internal function संकेत 11 */
#घोषणा K210_PCF_INTERNAL12	216 /* Internal function संकेत 12 */
#घोषणा K210_PCF_INTERNAL13	217 /* Internal function संकेत 13 */
#घोषणा K210_PCF_INTERNAL14	218 /* Internal function संकेत 14 */
#घोषणा K210_PCF_INTERNAL15	219 /* Internal function संकेत 15 */
#घोषणा K210_PCF_INTERNAL16	220 /* Internal function संकेत 16 */
#घोषणा K210_PCF_INTERNAL17	221 /* Internal function संकेत 17 */
#घोषणा K210_PCF_CONSTANT	222 /* Constant function */
#घोषणा K210_PCF_INTERNAL18	223 /* Internal function संकेत 18 */
#घोषणा K210_PCF_DEBUG0		224 /* Debug function 0 */
#घोषणा K210_PCF_DEBUG1		225 /* Debug function 1 */
#घोषणा K210_PCF_DEBUG2		226 /* Debug function 2 */
#घोषणा K210_PCF_DEBUG3		227 /* Debug function 3 */
#घोषणा K210_PCF_DEBUG4		228 /* Debug function 4 */
#घोषणा K210_PCF_DEBUG5		229 /* Debug function 5 */
#घोषणा K210_PCF_DEBUG6		230 /* Debug function 6 */
#घोषणा K210_PCF_DEBUG7		231 /* Debug function 7 */
#घोषणा K210_PCF_DEBUG8		232 /* Debug function 8 */
#घोषणा K210_PCF_DEBUG9		233 /* Debug function 9 */
#घोषणा K210_PCF_DEBUG10	234 /* Debug function 10 */
#घोषणा K210_PCF_DEBUG11	235 /* Debug function 11 */
#घोषणा K210_PCF_DEBUG12	236 /* Debug function 12 */
#घोषणा K210_PCF_DEBUG13	237 /* Debug function 13 */
#घोषणा K210_PCF_DEBUG14	238 /* Debug function 14 */
#घोषणा K210_PCF_DEBUG15	239 /* Debug function 15 */
#घोषणा K210_PCF_DEBUG16	240 /* Debug function 16 */
#घोषणा K210_PCF_DEBUG17	241 /* Debug function 17 */
#घोषणा K210_PCF_DEBUG18	242 /* Debug function 18 */
#घोषणा K210_PCF_DEBUG19	243 /* Debug function 19 */
#घोषणा K210_PCF_DEBUG20	244 /* Debug function 20 */
#घोषणा K210_PCF_DEBUG21	245 /* Debug function 21 */
#घोषणा K210_PCF_DEBUG22	246 /* Debug function 22 */
#घोषणा K210_PCF_DEBUG23	247 /* Debug function 23 */
#घोषणा K210_PCF_DEBUG24	248 /* Debug function 24 */
#घोषणा K210_PCF_DEBUG25	249 /* Debug function 25 */
#घोषणा K210_PCF_DEBUG26	250 /* Debug function 26 */
#घोषणा K210_PCF_DEBUG27	251 /* Debug function 27 */
#घोषणा K210_PCF_DEBUG28	252 /* Debug function 28 */
#घोषणा K210_PCF_DEBUG29	253 /* Debug function 29 */
#घोषणा K210_PCF_DEBUG30	254 /* Debug function 30 */
#घोषणा K210_PCF_DEBUG31	255 /* Debug function 31 */

#घोषणा K210_FPIOA(pin, func)		(((pin) << 16) | (func))

#घोषणा K210_PC_POWER_3V3	0
#घोषणा K210_PC_POWER_1V8	1

#पूर्ण_अगर /* PINCTRL_K210_FPIOA_H */
