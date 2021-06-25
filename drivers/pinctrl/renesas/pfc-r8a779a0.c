<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * R8A779A0 processor support - PFC hardware block.
 *
 * Copyright (C) 2020 Renesas Electronics Corp.
 *
 * This file is based on the drivers/pinctrl/renesas/pfc-r8a7795.c
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>

#समावेश "sh_pfc.h"

#घोषणा CFG_FLAGS (SH_PFC_PIN_CFG_DRIVE_STRENGTH | SH_PFC_PIN_CFG_PULL_UP_DOWN)

#घोषणा CPU_ALL_GP(fn, sfx)	\
	PORT_GP_CFG_15(0, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(0, 15, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(0, 16, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(0, 17, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(0, 18, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(0, 19, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(0, 20, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(0, 21, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(0, 22, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(0, 23, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(0, 24, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(0, 25, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(0, 26, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(0, 27, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_31(1, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_2(2, fn, sfx, CFG_FLAGS),					\
	PORT_GP_CFG_1(2, 2, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(2, 3, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(2, 4, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(2, 5, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(2, 6, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(2, 7, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(2, 8, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(2, 9, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(2, 10, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(2, 11, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(2, 12, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(2, 13, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(2, 14, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(2, 15, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_18_33),	\
	PORT_GP_CFG_1(2, 16, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(2, 17, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(2, 18, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(2, 19, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(2, 20, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(2, 21, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(2, 22, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(2, 23, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(2, 24, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_17(3, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_18(4, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_25_33),\
	PORT_GP_CFG_1(4, 18, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(4, 19, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(4, 20, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(4, 21, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(4, 22, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(4, 23, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(4, 24, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(4, 25, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(4, 26, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_18(5, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_25_33),\
	PORT_GP_CFG_1(5, 18, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(5, 19, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(5, 20, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_18(6, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_25_33),\
	PORT_GP_CFG_1(6, 18, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(6, 19, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(6, 20, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_18(7, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_25_33),\
	PORT_GP_CFG_1(7, 18, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(7, 19, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(7, 20, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_18(8, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_25_33),\
	PORT_GP_CFG_1(8, 18, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(8, 19, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(8, 20, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_18(9, fn, sfx, CFG_FLAGS | SH_PFC_PIN_CFG_IO_VOLTAGE_25_33),\
	PORT_GP_CFG_1(9, 18, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(9, 19, fn, sfx, CFG_FLAGS),	\
	PORT_GP_CFG_1(9, 20, fn, sfx, CFG_FLAGS)

#घोषणा CPU_ALL_NOGP(fn)									\
	PIN_NOGP_CFG(PRESETOUT_N, "PRESETOUT#", fn, SH_PFC_PIN_CFG_PULL_UP_DOWN),		\
	PIN_NOGP_CFG(EXTALR, "EXTALR", fn, SH_PFC_PIN_CFG_PULL_UP_DOWN),			\
	PIN_NOGP_CFG(DCUTRST_N_LPDRST_N, "DCUTRST#_LPDRST#", fn, SH_PFC_PIN_CFG_PULL_UP_DOWN),	\
	PIN_NOGP_CFG(DCUTCK_LPDCLK, "DCUTCK_LPDCLK", fn, SH_PFC_PIN_CFG_PULL_UP_DOWN),		\
	PIN_NOGP_CFG(DCUTMS, "DCUTMS", fn, SH_PFC_PIN_CFG_PULL_UP_DOWN),			\
	PIN_NOGP_CFG(DCUTDI_LPDI, "DCUTDI_LPDI", fn, SH_PFC_PIN_CFG_PULL_UP_DOWN)

/*
 * F_() : just inक्रमmation
 * FM() : macro क्रम FN_xxx / xxx_MARK
 */

/* GPSR0 */
#घोषणा GPSR0_27	FM(MMC_D7)
#घोषणा GPSR0_26	FM(MMC_D6)
#घोषणा GPSR0_25	FM(MMC_D5)
#घोषणा GPSR0_24	FM(MMC_D4)
#घोषणा GPSR0_23	FM(MMC_SD_CLK)
#घोषणा GPSR0_22	FM(MMC_SD_D3)
#घोषणा GPSR0_21	FM(MMC_SD_D2)
#घोषणा GPSR0_20	FM(MMC_SD_D1)
#घोषणा GPSR0_19	FM(MMC_SD_D0)
#घोषणा GPSR0_18	FM(MMC_SD_CMD)
#घोषणा GPSR0_17	FM(MMC_DS)
#घोषणा GPSR0_16	FM(SD_CD)
#घोषणा GPSR0_15	FM(SD_WP)
#घोषणा GPSR0_14	FM(RPC_INT_N)
#घोषणा GPSR0_13	FM(RPC_WP_N)
#घोषणा GPSR0_12	FM(RPC_RESET_N)
#घोषणा GPSR0_11	FM(QSPI1_SSL)
#घोषणा GPSR0_10	FM(QSPI1_IO3)
#घोषणा GPSR0_9		FM(QSPI1_IO2)
#घोषणा GPSR0_8		FM(QSPI1_MISO_IO1)
#घोषणा GPSR0_7		FM(QSPI1_MOSI_IO0)
#घोषणा GPSR0_6		FM(QSPI1_SPCLK)
#घोषणा GPSR0_5		FM(QSPI0_SSL)
#घोषणा GPSR0_4		FM(QSPI0_IO3)
#घोषणा GPSR0_3		FM(QSPI0_IO2)
#घोषणा GPSR0_2		FM(QSPI0_MISO_IO1)
#घोषणा GPSR0_1		FM(QSPI0_MOSI_IO0)
#घोषणा GPSR0_0		FM(QSPI0_SPCLK)

/* GPSR1 */
#घोषणा GPSR1_30	F_(GP1_30,	IP3SR1_27_24)
#घोषणा GPSR1_29	F_(GP1_29,	IP3SR1_23_20)
#घोषणा GPSR1_28	F_(GP1_28,	IP3SR1_19_16)
#घोषणा GPSR1_27	F_(IRQ3,	IP3SR1_15_12)
#घोषणा GPSR1_26	F_(IRQ2,	IP3SR1_11_8)
#घोषणा GPSR1_25	F_(IRQ1,	IP3SR1_7_4)
#घोषणा GPSR1_24	F_(IRQ0,	IP3SR1_3_0)
#घोषणा GPSR1_23	F_(MSIOF2_SS2,	IP2SR1_31_28)
#घोषणा GPSR1_22	F_(MSIOF2_SS1,	IP2SR1_27_24)
#घोषणा GPSR1_21	F_(MSIOF2_SYNC,	IP2SR1_23_20)
#घोषणा GPSR1_20	F_(MSIOF2_SCK,	IP2SR1_19_16)
#घोषणा GPSR1_19	F_(MSIOF2_TXD,	IP2SR1_15_12)
#घोषणा GPSR1_18	F_(MSIOF2_RXD,	IP2SR1_11_8)
#घोषणा GPSR1_17	F_(MSIOF1_SS2,	IP2SR1_7_4)
#घोषणा GPSR1_16	F_(MSIOF1_SS1,	IP2SR1_3_0)
#घोषणा GPSR1_15	F_(MSIOF1_SYNC,	IP1SR1_31_28)
#घोषणा GPSR1_14	F_(MSIOF1_SCK,	IP1SR1_27_24)
#घोषणा GPSR1_13	F_(MSIOF1_TXD,	IP1SR1_23_20)
#घोषणा GPSR1_12	F_(MSIOF1_RXD,	IP1SR1_19_16)
#घोषणा GPSR1_11	F_(MSIOF0_SS2,	IP1SR1_15_12)
#घोषणा GPSR1_10	F_(MSIOF0_SS1,	IP1SR1_11_8)
#घोषणा GPSR1_9		F_(MSIOF0_SYNC,	IP1SR1_7_4)
#घोषणा GPSR1_8		F_(MSIOF0_SCK,	IP1SR1_3_0)
#घोषणा GPSR1_7		F_(MSIOF0_TXD,	IP0SR1_31_28)
#घोषणा GPSR1_6		F_(MSIOF0_RXD,	IP0SR1_27_24)
#घोषणा GPSR1_5		F_(HTX0,	IP0SR1_23_20)
#घोषणा GPSR1_4		F_(HCTS0_N,	IP0SR1_19_16)
#घोषणा GPSR1_3		F_(HRTS0_N,	IP0SR1_15_12)
#घोषणा GPSR1_2		F_(HSCK0,	IP0SR1_11_8)
#घोषणा GPSR1_1		F_(HRX0,	IP0SR1_7_4)
#घोषणा GPSR1_0		F_(SCIF_CLK,	IP0SR1_3_0)

/* GPSR2 */
#घोषणा GPSR2_24	FM(TCLK2_A)
#घोषणा GPSR2_23	F_(TCLK1_A,		IP2SR2_31_28)
#घोषणा GPSR2_22	F_(TPU0TO1,		IP2SR2_27_24)
#घोषणा GPSR2_21	F_(TPU0TO0,		IP2SR2_23_20)
#घोषणा GPSR2_20	F_(CLK_EXTFXR,		IP2SR2_19_16)
#घोषणा GPSR2_19	F_(RXDB_EXTFXR,		IP2SR2_15_12)
#घोषणा GPSR2_18	F_(FXR_TXDB,		IP2SR2_11_8)
#घोषणा GPSR2_17	F_(RXDA_EXTFXR_A,	IP2SR2_7_4)
#घोषणा GPSR2_16	F_(FXR_TXDA_A,		IP2SR2_3_0)
#घोषणा GPSR2_15	F_(GP2_15,		IP1SR2_31_28)
#घोषणा GPSR2_14	F_(GP2_14,		IP1SR2_27_24)
#घोषणा GPSR2_13	F_(GP2_13,		IP1SR2_23_20)
#घोषणा GPSR2_12	F_(GP2_12,		IP1SR2_19_16)
#घोषणा GPSR2_11	F_(GP2_11,		IP1SR2_15_12)
#घोषणा GPSR2_10	F_(GP2_10,		IP1SR2_11_8)
#घोषणा GPSR2_9		F_(GP2_09,		IP1SR2_7_4)
#घोषणा GPSR2_8		F_(GP2_08,		IP1SR2_3_0)
#घोषणा GPSR2_7		F_(GP2_07,		IP0SR2_31_28)
#घोषणा GPSR2_6		F_(GP2_06,		IP0SR2_27_24)
#घोषणा GPSR2_5		F_(GP2_05,		IP0SR2_23_20)
#घोषणा GPSR2_4		F_(GP2_04,		IP0SR2_19_16)
#घोषणा GPSR2_3		F_(GP2_03,		IP0SR2_15_12)
#घोषणा GPSR2_2		F_(GP2_02,		IP0SR2_11_8)
#घोषणा GPSR2_1		F_(IPC_CLKOUT,		IP0SR2_7_4)
#घोषणा GPSR2_0		F_(IPC_CLKIN,		IP0SR2_3_0)

/* GPSR3 */
#घोषणा GPSR3_16	FM(CANFD7_RX)
#घोषणा GPSR3_15	FM(CANFD7_TX)
#घोषणा GPSR3_14	FM(CANFD6_RX)
#घोषणा GPSR3_13	F_(CANFD6_TX,	IP1SR3_23_20)
#घोषणा GPSR3_12	F_(CANFD5_RX,	IP1SR3_19_16)
#घोषणा GPSR3_11	F_(CANFD5_TX,	IP1SR3_15_12)
#घोषणा GPSR3_10	F_(CANFD4_RX,	IP1SR3_11_8)
#घोषणा GPSR3_9		F_(CANFD4_TX,	IP1SR3_7_4)
#घोषणा GPSR3_8		F_(CANFD3_RX,	IP1SR3_3_0)
#घोषणा GPSR3_7		F_(CANFD3_TX,	IP0SR3_31_28)
#घोषणा GPSR3_6		F_(CANFD2_RX,	IP0SR3_27_24)
#घोषणा GPSR3_5		F_(CANFD2_TX,	IP0SR3_23_20)
#घोषणा GPSR3_4		FM(CANFD1_RX)
#घोषणा GPSR3_3		FM(CANFD1_TX)
#घोषणा GPSR3_2		F_(CANFD0_RX,	IP0SR3_11_8)
#घोषणा GPSR3_1		F_(CANFD0_TX,	IP0SR3_7_4)
#घोषणा GPSR3_0		FM(CAN_CLK)

/* GPSR4 */
#घोषणा GPSR4_26	FM(AVS1)
#घोषणा GPSR4_25	FM(AVS0)
#घोषणा GPSR4_24	FM(PCIE3_CLKREQ_N)
#घोषणा GPSR4_23	FM(PCIE2_CLKREQ_N)
#घोषणा GPSR4_22	FM(PCIE1_CLKREQ_N)
#घोषणा GPSR4_21	FM(PCIE0_CLKREQ_N)
#घोषणा GPSR4_20	F_(AVB0_AVTP_PPS,	IP2SR4_19_16)
#घोषणा GPSR4_19	F_(AVB0_AVTP_CAPTURE,	IP2SR4_15_12)
#घोषणा GPSR4_18	F_(AVB0_AVTP_MATCH,	IP2SR4_11_8)
#घोषणा GPSR4_17	F_(AVB0_LINK,		IP2SR4_7_4)
#घोषणा GPSR4_16	FM(AVB0_PHY_INT)
#घोषणा GPSR4_15	F_(AVB0_MAGIC,		IP1SR4_31_28)
#घोषणा GPSR4_14	F_(AVB0_MDC,		IP1SR4_27_24)
#घोषणा GPSR4_13	F_(AVB0_MDIO,		IP1SR4_23_20)
#घोषणा GPSR4_12	F_(AVB0_TXCREFCLK,	IP1SR4_19_16)
#घोषणा GPSR4_11	F_(AVB0_TD3,		IP1SR4_15_12)
#घोषणा GPSR4_10	F_(AVB0_TD2,		IP1SR4_11_8)
#घोषणा GPSR4_9		F_(AVB0_TD1,		IP1SR4_7_4)
#घोषणा GPSR4_8		F_(AVB0_TD0,		IP1SR4_3_0)
#घोषणा GPSR4_7		F_(AVB0_TXC,		IP0SR4_31_28)
#घोषणा GPSR4_6		F_(AVB0_TX_CTL,		IP0SR4_27_24)
#घोषणा GPSR4_5		F_(AVB0_RD3,		IP0SR4_23_20)
#घोषणा GPSR4_4		F_(AVB0_RD2,		IP0SR4_19_16)
#घोषणा GPSR4_3		F_(AVB0_RD1,		IP0SR4_15_12)
#घोषणा GPSR4_2		F_(AVB0_RD0,		IP0SR4_11_8)
#घोषणा GPSR4_1		F_(AVB0_RXC,		IP0SR4_7_4)
#घोषणा GPSR4_0		F_(AVB0_RX_CTL,		IP0SR4_3_0)

/* GPSR5 */
#घोषणा GPSR5_20	F_(AVB1_AVTP_PPS,	IP2SR5_19_16)
#घोषणा GPSR5_19	F_(AVB1_AVTP_CAPTURE,	IP2SR5_15_12)
#घोषणा GPSR5_18	F_(AVB1_AVTP_MATCH,	IP2SR5_11_8)
#घोषणा GPSR5_17	F_(AVB1_LINK,		IP2SR5_7_4)
#घोषणा GPSR5_16	FM(AVB1_PHY_INT)
#घोषणा GPSR5_15	F_(AVB1_MAGIC,		IP1SR5_31_28)
#घोषणा GPSR5_14	F_(AVB1_MDC,		IP1SR5_27_24)
#घोषणा GPSR5_13	F_(AVB1_MDIO,		IP1SR5_23_20)
#घोषणा GPSR5_12	F_(AVB1_TXCREFCLK,	IP1SR5_19_16)
#घोषणा GPSR5_11	F_(AVB1_TD3,		IP1SR5_15_12)
#घोषणा GPSR5_10	F_(AVB1_TD2,		IP1SR5_11_8)
#घोषणा GPSR5_9		F_(AVB1_TD1,		IP1SR5_7_4)
#घोषणा GPSR5_8		F_(AVB1_TD0,		IP1SR5_3_0)
#घोषणा GPSR5_7		F_(AVB1_TXC,		IP0SR5_31_28)
#घोषणा GPSR5_6		F_(AVB1_TX_CTL,		IP0SR5_27_24)
#घोषणा GPSR5_5		F_(AVB1_RD3,		IP0SR5_23_20)
#घोषणा GPSR5_4		F_(AVB1_RD2,		IP0SR5_19_16)
#घोषणा GPSR5_3		F_(AVB1_RD1,		IP0SR5_15_12)
#घोषणा GPSR5_2		F_(AVB1_RD0,		IP0SR5_11_8)
#घोषणा GPSR5_1		F_(AVB1_RXC,		IP0SR5_7_4)
#घोषणा GPSR5_0		F_(AVB1_RX_CTL,		IP0SR5_3_0)

/* GPSR6 */
#घोषणा GPSR6_20	FM(AVB2_AVTP_PPS)
#घोषणा GPSR6_19	FM(AVB2_AVTP_CAPTURE)
#घोषणा GPSR6_18	FM(AVB2_AVTP_MATCH)
#घोषणा GPSR6_17	FM(AVB2_LINK)
#घोषणा GPSR6_16	FM(AVB2_PHY_INT)
#घोषणा GPSR6_15	FM(AVB2_MAGIC)
#घोषणा GPSR6_14	FM(AVB2_MDC)
#घोषणा GPSR6_13	FM(AVB2_MDIO)
#घोषणा GPSR6_12	FM(AVB2_TXCREFCLK)
#घोषणा GPSR6_11	FM(AVB2_TD3)
#घोषणा GPSR6_10	FM(AVB2_TD2)
#घोषणा GPSR6_9		FM(AVB2_TD1)
#घोषणा GPSR6_8		FM(AVB2_TD0)
#घोषणा GPSR6_7		FM(AVB2_TXC)
#घोषणा GPSR6_6		FM(AVB2_TX_CTL)
#घोषणा GPSR6_5		FM(AVB2_RD3)
#घोषणा GPSR6_4		FM(AVB2_RD2)
#घोषणा GPSR6_3		FM(AVB2_RD1)
#घोषणा GPSR6_2		FM(AVB2_RD0)
#घोषणा GPSR6_1		FM(AVB2_RXC)
#घोषणा GPSR6_0		FM(AVB2_RX_CTL)

/* GPSR7 */
#घोषणा GPSR7_20	FM(AVB3_AVTP_PPS)
#घोषणा GPSR7_19	FM(AVB3_AVTP_CAPTURE)
#घोषणा GPSR7_18	FM(AVB3_AVTP_MATCH)
#घोषणा GPSR7_17	FM(AVB3_LINK)
#घोषणा GPSR7_16	FM(AVB3_PHY_INT)
#घोषणा GPSR7_15	FM(AVB3_MAGIC)
#घोषणा GPSR7_14	FM(AVB3_MDC)
#घोषणा GPSR7_13	FM(AVB3_MDIO)
#घोषणा GPSR7_12	FM(AVB3_TXCREFCLK)
#घोषणा GPSR7_11	FM(AVB3_TD3)
#घोषणा GPSR7_10	FM(AVB3_TD2)
#घोषणा GPSR7_9		FM(AVB3_TD1)
#घोषणा GPSR7_8		FM(AVB3_TD0)
#घोषणा GPSR7_7		FM(AVB3_TXC)
#घोषणा GPSR7_6		FM(AVB3_TX_CTL)
#घोषणा GPSR7_5		FM(AVB3_RD3)
#घोषणा GPSR7_4		FM(AVB3_RD2)
#घोषणा GPSR7_3		FM(AVB3_RD1)
#घोषणा GPSR7_2		FM(AVB3_RD0)
#घोषणा GPSR7_1		FM(AVB3_RXC)
#घोषणा GPSR7_0		FM(AVB3_RX_CTL)

/* GPSR8 */
#घोषणा GPSR8_20	FM(AVB4_AVTP_PPS)
#घोषणा GPSR8_19	FM(AVB4_AVTP_CAPTURE)
#घोषणा GPSR8_18	FM(AVB4_AVTP_MATCH)
#घोषणा GPSR8_17	FM(AVB4_LINK)
#घोषणा GPSR8_16	FM(AVB4_PHY_INT)
#घोषणा GPSR8_15	FM(AVB4_MAGIC)
#घोषणा GPSR8_14	FM(AVB4_MDC)
#घोषणा GPSR8_13	FM(AVB4_MDIO)
#घोषणा GPSR8_12	FM(AVB4_TXCREFCLK)
#घोषणा GPSR8_11	FM(AVB4_TD3)
#घोषणा GPSR8_10	FM(AVB4_TD2)
#घोषणा GPSR8_9		FM(AVB4_TD1)
#घोषणा GPSR8_8		FM(AVB4_TD0)
#घोषणा GPSR8_7		FM(AVB4_TXC)
#घोषणा GPSR8_6		FM(AVB4_TX_CTL)
#घोषणा GPSR8_5		FM(AVB4_RD3)
#घोषणा GPSR8_4		FM(AVB4_RD2)
#घोषणा GPSR8_3		FM(AVB4_RD1)
#घोषणा GPSR8_2		FM(AVB4_RD0)
#घोषणा GPSR8_1		FM(AVB4_RXC)
#घोषणा GPSR8_0		FM(AVB4_RX_CTL)

/* GPSR9 */
#घोषणा GPSR9_20	FM(AVB5_AVTP_PPS)
#घोषणा GPSR9_19	FM(AVB5_AVTP_CAPTURE)
#घोषणा GPSR9_18	FM(AVB5_AVTP_MATCH)
#घोषणा GPSR9_17	FM(AVB5_LINK)
#घोषणा GPSR9_16	FM(AVB5_PHY_INT)
#घोषणा GPSR9_15	FM(AVB5_MAGIC)
#घोषणा GPSR9_14	FM(AVB5_MDC)
#घोषणा GPSR9_13	FM(AVB5_MDIO)
#घोषणा GPSR9_12	FM(AVB5_TXCREFCLK)
#घोषणा GPSR9_11	FM(AVB5_TD3)
#घोषणा GPSR9_10	FM(AVB5_TD2)
#घोषणा GPSR9_9		FM(AVB5_TD1)
#घोषणा GPSR9_8		FM(AVB5_TD0)
#घोषणा GPSR9_7		FM(AVB5_TXC)
#घोषणा GPSR9_6		FM(AVB5_TX_CTL)
#घोषणा GPSR9_5		FM(AVB5_RD3)
#घोषणा GPSR9_4		FM(AVB5_RD2)
#घोषणा GPSR9_3		FM(AVB5_RD1)
#घोषणा GPSR9_2		FM(AVB5_RD0)
#घोषणा GPSR9_1		FM(AVB5_RXC)
#घोषणा GPSR9_0		FM(AVB5_RX_CTL)

/* IP0SR1 */		/* 0 */		/* 1 */		/* 2 */		/* 3 */		/* 4 */		/* 5 */		/* 6 - F */
#घोषणा IP0SR1_3_0	FM(SCIF_CLK)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(A0)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR1_7_4	FM(HRX0)	FM(RX0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(A1)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR1_11_8	FM(HSCK0)	FM(SCK0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(A2)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR1_15_12	FM(HRTS0_N)	FM(RTS0_N)	F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(A3)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR1_19_16	FM(HCTS0_N)	FM(CTS0_N)	F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(A4)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR1_23_20	FM(HTX0)	FM(TX0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(A5)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR1_27_24	FM(MSIOF0_RXD)	F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(DU_DR2)	FM(A6)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR1_31_28	FM(MSIOF0_TXD)	F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(DU_DR3)	FM(A7)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
/* IP1SR1 */		/* 0 */		/* 1 */		/* 2 */		/* 3 */		/* 4 */		/* 5 */		/* 6 - F */
#घोषणा IP1SR1_3_0	FM(MSIOF0_SCK)	F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(DU_DR4)	FM(A8)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR1_7_4	FM(MSIOF0_SYNC)	F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(DU_DR5)	FM(A9)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR1_11_8	FM(MSIOF0_SS1)	F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(DU_DR6)	FM(A10)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR1_15_12	FM(MSIOF0_SS2)	F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(DU_DR7)	FM(A11)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR1_19_16	FM(MSIOF1_RXD)	F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(DU_DG2)	FM(A12)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR1_23_20	FM(MSIOF1_TXD)	FM(HRX3)	FM(SCK3)	F_(0, 0)	FM(DU_DG3)	FM(A13)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR1_27_24	FM(MSIOF1_SCK)	FM(HSCK3)	FM(CTS3_N)	F_(0, 0)	FM(DU_DG4)	FM(A14)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR1_31_28	FM(MSIOF1_SYNC)	FM(HRTS3_N)	FM(RTS3_N)	F_(0, 0)	FM(DU_DG5)	FM(A15)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
/* IP2SR1 */		/* 0 */		/* 1 */		/* 2 */		/* 3 */		/* 4 */		/* 5 */		/* 6 - F */
#घोषणा IP2SR1_3_0	FM(MSIOF1_SS1)	FM(HCTS3_N)	FM(RX3)		F_(0, 0)	FM(DU_DG6)	FM(A16)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR1_7_4	FM(MSIOF1_SS2)	FM(HTX3)	FM(TX3)		F_(0, 0)	FM(DU_DG7)	FM(A17)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR1_11_8	FM(MSIOF2_RXD)	FM(HSCK1)	FM(SCK1)	F_(0, 0)	FM(DU_DB2)	FM(A18)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR1_15_12	FM(MSIOF2_TXD)	FM(HCTS1_N)	FM(CTS1_N)	F_(0, 0)	FM(DU_DB3)	FM(A19)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR1_19_16	FM(MSIOF2_SCK)	FM(HRTS1_N)	FM(RTS1_N)	F_(0, 0)	FM(DU_DB4)	FM(A20)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR1_23_20	FM(MSIOF2_SYNC)	FM(HRX1)	FM(RX1_A)	F_(0, 0)	FM(DU_DB5)	FM(A21)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR1_27_24	FM(MSIOF2_SS1)	FM(HTX1)	FM(TX1_A)	F_(0, 0)	FM(DU_DB6)	FM(A22)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR1_31_28	FM(MSIOF2_SS2)	FM(TCLK1_B)	F_(0, 0)	F_(0, 0)	FM(DU_DB7)	FM(A23)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)

/* IP3SR1 */		/* 0 */			/* 1 */		/* 2 */		/* 3 */		/* 4 */			/* 5 */		/* 6 - F */
#घोषणा IP3SR1_3_0	FM(IRQ0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(DU_DOTCLKOUT)	FM(A24)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP3SR1_7_4	FM(IRQ1)		F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(DU_HSYNC)		FM(A25)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP3SR1_11_8	FM(IRQ2)		F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(DU_VSYNC)		FM(CS1_N_A26)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP3SR1_15_12	FM(IRQ3)		F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(DU_ODDF_DISP_CDE)	FM(CS0_N)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP3SR1_19_16	FM(GP1_28)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)		FM(D0)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP3SR1_23_20	FM(GP1_29)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)		FM(D1)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP3SR1_27_24	FM(GP1_30)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)		FM(D2)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP3SR1_31_28	F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)

/* IP0SR2 */		/* 0 */			/* 1 */			/* 2 */		/* 3 */		/* 4 */		/* 5 */		/* 6 - F */
#घोषणा IP0SR2_3_0	FM(IPC_CLKIN)		FM(IPC_CLKEN_IN)	F_(0, 0)	F_(0, 0)	FM(DU_DOTCLKIN)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR2_7_4	FM(IPC_CLKOUT)		FM(IPC_CLKEN_OUT)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR2_11_8	FM(GP2_02)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(D3)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR2_15_12	FM(GP2_03)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(D4)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR2_19_16	FM(GP2_04)		F_(0, 0)		FM(MSIOF4_RXD)	F_(0, 0)	F_(0, 0)	FM(D5)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR2_23_20	FM(GP2_05)		FM(HSCK2)		FM(MSIOF4_TXD)	FM(SCK4)	F_(0, 0)	FM(D6)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR2_27_24	FM(GP2_06)		FM(HCTS2_N)		FM(MSIOF4_SCK)	FM(CTS4_N)	F_(0, 0)	FM(D7)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR2_31_28	FM(GP2_07)		FM(HRTS2_N)		FM(MSIOF4_SYNC)	FM(RTS4_N)	F_(0, 0)	FM(D8)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
/* IP1SR2 */		/* 0 */			/* 1 */			/* 2 */		/* 3 */		/* 4 */		/* 5 */		/* 6 - F */
#घोषणा IP1SR2_3_0	FM(GP2_08)		FM(HRX2)		FM(MSIOF4_SS1)	FM(RX4)		F_(0, 0)	FM(D9)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR2_7_4	FM(GP2_09)		FM(HTX2)		FM(MSIOF4_SS2)	FM(TX4)		F_(0, 0)	FM(D10)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR2_11_8	FM(GP2_10)		FM(TCLK2_B)		FM(MSIOF5_RXD)	F_(0, 0)	F_(0, 0)	FM(D11)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR2_15_12	FM(GP2_11)		FM(TCLK3)		FM(MSIOF5_TXD)	F_(0, 0)	F_(0, 0)	FM(D12)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR2_19_16	FM(GP2_12)		FM(TCLK4)		FM(MSIOF5_SCK)	F_(0, 0)	F_(0, 0)	FM(D13)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR2_23_20	FM(GP2_13)		F_(0, 0)		FM(MSIOF5_SYNC)	F_(0, 0)	F_(0, 0)	FM(D14)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR2_27_24	FM(GP2_14)		FM(IRQ4)		FM(MSIOF5_SS1)	F_(0, 0)	F_(0, 0)	FM(D15)		F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR2_31_28	FM(GP2_15)		FM(IRQ5)		FM(MSIOF5_SS2)	FM(CPG_CPCKOUT)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
/* IP2SR2 */		/* 0 */			/* 1 */			/* 2 */		/* 3 */		/* 4 */		/* 5 */		/* 6 - F */
#घोषणा IP2SR2_3_0	FM(FXR_TXDA_A)		FM(MSIOF3_SS1)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR2_7_4	FM(RXDA_EXTFXR_A)	FM(MSIOF3_SS2)		F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(BS_N)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR2_11_8	FM(FXR_TXDB)		FM(MSIOF3_RXD)		F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(RD_N)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR2_15_12	FM(RXDB_EXTFXR)		FM(MSIOF3_TXD)		F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(WE0_N)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR2_19_16	FM(CLK_EXTFXR)		FM(MSIOF3_SCK)		F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(WE1_N)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR2_23_20	FM(TPU0TO0)		FM(MSIOF3_SYNC)		F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(RD_WR_N)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR2_27_24	FM(TPU0TO1)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(CLKOUT)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR2_31_28	FM(TCLK1_A)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	FM(EX_WAIT0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)

/* IP0SR3 */		/* 0 */		/* 1 */			/* 2 */		/* 3 */			/* 4 */		/* 5 */		/* 6 - F */
#घोषणा IP0SR3_3_0	F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR3_7_4	FM(CANFD0_TX)	FM(FXR_TXDA_B)		FM(TX1_B)	F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR3_11_8	FM(CANFD0_RX)	FM(RXDA_EXTFXR_B)	FM(RX1_B)	F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR3_15_12	F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR3_19_16	F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR3_23_20	FM(CANFD2_TX)	FM(TPU0TO2)		FM(PWM0)	F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR3_27_24	FM(CANFD2_RX)	FM(TPU0TO3)		FM(PWM1)	F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR3_31_28	FM(CANFD3_TX)	F_(0, 0)		FM(PWM2)	F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
/* IP1SR3 */		/* 0 */		/* 1 */			/* 2 */		/* 3 */			/* 4 */		/* 5 */		/* 6 - F */
#घोषणा IP1SR3_3_0	FM(CANFD3_RX)	F_(0, 0)		FM(PWM3)	F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR3_7_4	FM(CANFD4_TX)	F_(0, 0)		FM(PWM4)	FM(FXR_CLKOUT1)		F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR3_11_8	FM(CANFD4_RX)	F_(0, 0)		F_(0, 0)	FM(FXR_CLKOUT2)		F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR3_15_12	FM(CANFD5_TX)	F_(0, 0)		F_(0, 0)	FM(FXR_TXENA_N)		F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR3_19_16	FM(CANFD5_RX)	F_(0, 0)		F_(0, 0)	FM(FXR_TXENB_N)		F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR3_23_20	FM(CANFD6_TX)	F_(0, 0)		F_(0, 0)	FM(STPWT_EXTFXR)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR3_27_24	F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR3_31_28	F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)

/* IP0SR4 */		/* 0 */		/* 1 */			/* 2 */		/* 3 */		/* 4 */		/* 5 */		/* 6 - F */
#घोषणा IP0SR4_3_0	FM(AVB0_RX_CTL)	FM(AVB0_MII_RX_DV)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR4_7_4	FM(AVB0_RXC)	FM(AVB0_MII_RXC)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR4_11_8	FM(AVB0_RD0)	FM(AVB0_MII_RD0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR4_15_12	FM(AVB0_RD1)	FM(AVB0_MII_RD1)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR4_19_16	FM(AVB0_RD2)	FM(AVB0_MII_RD2)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR4_23_20	FM(AVB0_RD3)	FM(AVB0_MII_RD3)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR4_27_24	FM(AVB0_TX_CTL)	FM(AVB0_MII_TX_EN)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR4_31_28	FM(AVB0_TXC)	FM(AVB0_MII_TXC)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
/* IP1SR4 */		/* 0 */			/* 1 */			/* 2 */		/* 3 */		/* 4 */		/* 5 */		/* 6 - F */
#घोषणा IP1SR4_3_0	FM(AVB0_TD0)		FM(AVB0_MII_TD0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR4_7_4	FM(AVB0_TD1)		FM(AVB0_MII_TD1)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR4_11_8	FM(AVB0_TD2)		FM(AVB0_MII_TD2)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR4_15_12	FM(AVB0_TD3)		FM(AVB0_MII_TD3)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR4_19_16	FM(AVB0_TXCREFCLK)	F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR4_23_20	FM(AVB0_MDIO)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR4_27_24	FM(AVB0_MDC)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR4_31_28	FM(AVB0_MAGIC)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
/* IP2SR4 */		/* 0 */			/* 1 */			/* 2 */		/* 3 */		/* 4 */		/* 5 */		/* 6 - F */
#घोषणा IP2SR4_3_0	F_(0, 0)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR4_7_4	FM(AVB0_LINK)		FM(AVB0_MII_TX_ER)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR4_11_8	FM(AVB0_AVTP_MATCH)	FM(AVB0_MII_RX_ER)	FM(CC5_OSCOUT)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR4_15_12	FM(AVB0_AVTP_CAPTURE)	FM(AVB0_MII_CRS)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR4_19_16	FM(AVB0_AVTP_PPS)	FM(AVB0_MII_COL)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR4_23_20	F_(0, 0)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR4_27_24	F_(0, 0)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR4_31_28	F_(0, 0)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)

/* IP0SR5 */		/* 0 */			/* 1 */			/* 2 */		/* 3 */		/* 4 */		/* 5 */		/* 6 - F */
#घोषणा IP0SR5_3_0	FM(AVB1_RX_CTL)		FM(AVB1_MII_RX_DV)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR5_7_4	FM(AVB1_RXC)		FM(AVB1_MII_RXC)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR5_11_8	FM(AVB1_RD0)		FM(AVB1_MII_RD0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR5_15_12	FM(AVB1_RD1)		FM(AVB1_MII_RD1)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR5_19_16	FM(AVB1_RD2)		FM(AVB1_MII_RD2)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR5_23_20	FM(AVB1_RD3)		FM(AVB1_MII_RD3)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR5_27_24	FM(AVB1_TX_CTL)		FM(AVB1_MII_TX_EN)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP0SR5_31_28	FM(AVB1_TXC)		FM(AVB1_MII_TXC)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
/* IP1SR5 */		/* 0 */			/* 1 */			/* 2 */		/* 3 */		/* 4 */		/* 5 */		/* 6 - F */
#घोषणा IP1SR5_3_0	FM(AVB1_TD0)		FM(AVB1_MII_TD0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR5_7_4	FM(AVB1_TD1)		FM(AVB1_MII_TD1)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR5_11_8	FM(AVB1_TD2)		FM(AVB1_MII_TD2)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR5_15_12	FM(AVB1_TD3)		FM(AVB1_MII_TD3)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR5_19_16	FM(AVB1_TXCREFCLK)	F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR5_23_20	FM(AVB1_MDIO)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR5_27_24	FM(AVB1_MDC)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP1SR5_31_28	FM(AVB1_MAGIC)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
/* IP2SR5 */		/* 0 */			/* 1 */			/* 2 */		/* 3 */		/* 4 */		/* 5 */		/* 6 - F */
#घोषणा IP2SR5_3_0	F_(0, 0)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR5_7_4	FM(AVB1_LINK)		FM(AVB1_MII_TX_ER)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR5_11_8	FM(AVB1_AVTP_MATCH)	FM(AVB1_MII_RX_ER)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR5_15_12	FM(AVB1_AVTP_CAPTURE)	FM(AVB1_MII_CRS)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR5_19_16	FM(AVB1_AVTP_PPS)	FM(AVB1_MII_COL)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR5_23_20	F_(0, 0)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR5_27_24	F_(0, 0)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)
#घोषणा IP2SR5_31_28	F_(0, 0)		F_(0, 0)		F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0)	F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0) F_(0, 0)

#घोषणा PINMUX_GPSR		\
				\
		GPSR1_30	\
		GPSR1_29	\
		GPSR1_28	\
GPSR0_27	GPSR1_27	\
GPSR0_26	GPSR1_26					GPSR4_26 \
GPSR0_25	GPSR1_25					GPSR4_25 \
GPSR0_24	GPSR1_24	GPSR2_24			GPSR4_24 \
GPSR0_23	GPSR1_23	GPSR2_23			GPSR4_23 \
GPSR0_22	GPSR1_22	GPSR2_22			GPSR4_22 \
GPSR0_21	GPSR1_21	GPSR2_21			GPSR4_21 \
GPSR0_20	GPSR1_20	GPSR2_20			GPSR4_20	GPSR5_20	GPSR6_20	GPSR7_20	GPSR8_20	GPSR9_20 \
GPSR0_19	GPSR1_19	GPSR2_19			GPSR4_19	GPSR5_19	GPSR6_19	GPSR7_19	GPSR8_19	GPSR9_19 \
GPSR0_18	GPSR1_18	GPSR2_18			GPSR4_18	GPSR5_18	GPSR6_18	GPSR7_18	GPSR8_18	GPSR9_18 \
GPSR0_17	GPSR1_17	GPSR2_17			GPSR4_17	GPSR5_17	GPSR6_17	GPSR7_17	GPSR8_17	GPSR9_17 \
GPSR0_16	GPSR1_16	GPSR2_16	GPSR3_16	GPSR4_16	GPSR5_16	GPSR6_16	GPSR7_16	GPSR8_16	GPSR9_16 \
GPSR0_15	GPSR1_15	GPSR2_15	GPSR3_15	GPSR4_15	GPSR5_15	GPSR6_15	GPSR7_15	GPSR8_15	GPSR9_15 \
GPSR0_14	GPSR1_14	GPSR2_14	GPSR3_14	GPSR4_14	GPSR5_14	GPSR6_14	GPSR7_14	GPSR8_14	GPSR9_14 \
GPSR0_13	GPSR1_13	GPSR2_13	GPSR3_13	GPSR4_13	GPSR5_13	GPSR6_13	GPSR7_13	GPSR8_13	GPSR9_13 \
GPSR0_12	GPSR1_12	GPSR2_12	GPSR3_12	GPSR4_12	GPSR5_12	GPSR6_12	GPSR7_12	GPSR8_12	GPSR9_12 \
GPSR0_11	GPSR1_11	GPSR2_11	GPSR3_11	GPSR4_11	GPSR5_11	GPSR6_11	GPSR7_11	GPSR8_11	GPSR9_11 \
GPSR0_10	GPSR1_10	GPSR2_10	GPSR3_10	GPSR4_10	GPSR5_10	GPSR6_10	GPSR7_10	GPSR8_10	GPSR9_10 \
GPSR0_9		GPSR1_9		GPSR2_9		GPSR3_9		GPSR4_9		GPSR5_9		GPSR6_9		GPSR7_9		GPSR8_9		GPSR9_9 \
GPSR0_8		GPSR1_8		GPSR2_8		GPSR3_8		GPSR4_8		GPSR5_8		GPSR6_8		GPSR7_8		GPSR8_8		GPSR9_8 \
GPSR0_7		GPSR1_7		GPSR2_7		GPSR3_7		GPSR4_7		GPSR5_7		GPSR6_7		GPSR7_7		GPSR8_7		GPSR9_7 \
GPSR0_6		GPSR1_6		GPSR2_6		GPSR3_6		GPSR4_6		GPSR5_6		GPSR6_6		GPSR7_6		GPSR8_6		GPSR9_6 \
GPSR0_5		GPSR1_5		GPSR2_5		GPSR3_5		GPSR4_5		GPSR5_5		GPSR6_5		GPSR7_5		GPSR8_5		GPSR9_5 \
GPSR0_4		GPSR1_4		GPSR2_4		GPSR3_4		GPSR4_4		GPSR5_4		GPSR6_4		GPSR7_4		GPSR8_4		GPSR9_4 \
GPSR0_3		GPSR1_3		GPSR2_3		GPSR3_3		GPSR4_3		GPSR5_3		GPSR6_3		GPSR7_3		GPSR8_3		GPSR9_3 \
GPSR0_2		GPSR1_2		GPSR2_2		GPSR3_2		GPSR4_2		GPSR5_2		GPSR6_2		GPSR7_2		GPSR8_2		GPSR9_2 \
GPSR0_1		GPSR1_1		GPSR2_1		GPSR3_1		GPSR4_1		GPSR5_1		GPSR6_1		GPSR7_1		GPSR8_1		GPSR9_1 \
GPSR0_0		GPSR1_0		GPSR2_0		GPSR3_0		GPSR4_0		GPSR5_0		GPSR6_0		GPSR7_0		GPSR8_0		GPSR9_0

#घोषणा PINMUX_IPSR	\
\
FM(IP0SR1_3_0)		IP0SR1_3_0	FM(IP1SR1_3_0)		IP1SR1_3_0	FM(IP2SR1_3_0)		IP2SR1_3_0	FM(IP3SR1_3_0)		IP3SR1_3_0 \
FM(IP0SR1_7_4)		IP0SR1_7_4	FM(IP1SR1_7_4)		IP1SR1_7_4	FM(IP2SR1_7_4)		IP2SR1_7_4	FM(IP3SR1_7_4)		IP3SR1_7_4 \
FM(IP0SR1_11_8)		IP0SR1_11_8	FM(IP1SR1_11_8)		IP1SR1_11_8	FM(IP2SR1_11_8)		IP2SR1_11_8	FM(IP3SR1_11_8)		IP3SR1_11_8 \
FM(IP0SR1_15_12)	IP0SR1_15_12	FM(IP1SR1_15_12)	IP1SR1_15_12	FM(IP2SR1_15_12)	IP2SR1_15_12	FM(IP3SR1_15_12)	IP3SR1_15_12 \
FM(IP0SR1_19_16)	IP0SR1_19_16	FM(IP1SR1_19_16)	IP1SR1_19_16	FM(IP2SR1_19_16)	IP2SR1_19_16	FM(IP3SR1_19_16)	IP3SR1_19_16 \
FM(IP0SR1_23_20)	IP0SR1_23_20	FM(IP1SR1_23_20)	IP1SR1_23_20	FM(IP2SR1_23_20)	IP2SR1_23_20	FM(IP3SR1_23_20)	IP3SR1_23_20 \
FM(IP0SR1_27_24)	IP0SR1_27_24	FM(IP1SR1_27_24)	IP1SR1_27_24	FM(IP2SR1_27_24)	IP2SR1_27_24	FM(IP3SR1_27_24)	IP3SR1_27_24 \
FM(IP0SR1_31_28)	IP0SR1_31_28	FM(IP1SR1_31_28)	IP1SR1_31_28	FM(IP2SR1_31_28)	IP2SR1_31_28	FM(IP3SR1_31_28)	IP3SR1_31_28 \
\
FM(IP0SR2_3_0)		IP0SR2_3_0	FM(IP1SR2_3_0)		IP1SR2_3_0	FM(IP2SR2_3_0)		IP2SR2_3_0 \
FM(IP0SR2_7_4)		IP0SR2_7_4	FM(IP1SR2_7_4)		IP1SR2_7_4	FM(IP2SR2_7_4)		IP2SR2_7_4 \
FM(IP0SR2_11_8)		IP0SR2_11_8	FM(IP1SR2_11_8)		IP1SR2_11_8	FM(IP2SR2_11_8)		IP2SR2_11_8 \
FM(IP0SR2_15_12)	IP0SR2_15_12	FM(IP1SR2_15_12)	IP1SR2_15_12	FM(IP2SR2_15_12)	IP2SR2_15_12 \
FM(IP0SR2_19_16)	IP0SR2_19_16	FM(IP1SR2_19_16)	IP1SR2_19_16	FM(IP2SR2_19_16)	IP2SR2_19_16 \
FM(IP0SR2_23_20)	IP0SR2_23_20	FM(IP1SR2_23_20)	IP1SR2_23_20	FM(IP2SR2_23_20)	IP2SR2_23_20 \
FM(IP0SR2_27_24)	IP0SR2_27_24	FM(IP1SR2_27_24)	IP1SR2_27_24	FM(IP2SR2_27_24)	IP2SR2_27_24 \
FM(IP0SR2_31_28)	IP0SR2_31_28	FM(IP1SR2_31_28)	IP1SR2_31_28	FM(IP2SR2_31_28)	IP2SR2_31_28 \
\
FM(IP0SR3_3_0)		IP0SR3_3_0	FM(IP1SR3_3_0)		IP1SR3_3_0	\
FM(IP0SR3_7_4)		IP0SR3_7_4	FM(IP1SR3_7_4)		IP1SR3_7_4	\
FM(IP0SR3_11_8)		IP0SR3_11_8	FM(IP1SR3_11_8)		IP1SR3_11_8	\
FM(IP0SR3_15_12)	IP0SR3_15_12	FM(IP1SR3_15_12)	IP1SR3_15_12	\
FM(IP0SR3_19_16)	IP0SR3_19_16	FM(IP1SR3_19_16)	IP1SR3_19_16	\
FM(IP0SR3_23_20)	IP0SR3_23_20	FM(IP1SR3_23_20)	IP1SR3_23_20	\
FM(IP0SR3_27_24)	IP0SR3_27_24	FM(IP1SR3_27_24)	IP1SR3_27_24	\
FM(IP0SR3_31_28)	IP0SR3_31_28	FM(IP1SR3_31_28)	IP1SR3_31_28	\
\
FM(IP0SR4_3_0)		IP0SR4_3_0	FM(IP1SR4_3_0)		IP1SR4_3_0	FM(IP2SR4_3_0)		IP2SR4_3_0 \
FM(IP0SR4_7_4)		IP0SR4_7_4	FM(IP1SR4_7_4)		IP1SR4_7_4	FM(IP2SR4_7_4)		IP2SR4_7_4 \
FM(IP0SR4_11_8)		IP0SR4_11_8	FM(IP1SR4_11_8)		IP1SR4_11_8	FM(IP2SR4_11_8)		IP2SR4_11_8 \
FM(IP0SR4_15_12)	IP0SR4_15_12	FM(IP1SR4_15_12)	IP1SR4_15_12	FM(IP2SR4_15_12)	IP2SR4_15_12 \
FM(IP0SR4_19_16)	IP0SR4_19_16	FM(IP1SR4_19_16)	IP1SR4_19_16	FM(IP2SR4_19_16)	IP2SR4_19_16 \
FM(IP0SR4_23_20)	IP0SR4_23_20	FM(IP1SR4_23_20)	IP1SR4_23_20	FM(IP2SR4_23_20)	IP2SR4_23_20 \
FM(IP0SR4_27_24)	IP0SR4_27_24	FM(IP1SR4_27_24)	IP1SR4_27_24	FM(IP2SR4_27_24)	IP2SR4_27_24 \
FM(IP0SR4_31_28)	IP0SR4_31_28	FM(IP1SR4_31_28)	IP1SR4_31_28	FM(IP2SR4_31_28)	IP2SR4_31_28 \
\
FM(IP0SR5_3_0)		IP0SR5_3_0	FM(IP1SR5_3_0)		IP1SR5_3_0	FM(IP2SR5_3_0)		IP2SR5_3_0 \
FM(IP0SR5_7_4)		IP0SR5_7_4	FM(IP1SR5_7_4)		IP1SR5_7_4	FM(IP2SR5_7_4)		IP2SR5_7_4 \
FM(IP0SR5_11_8)		IP0SR5_11_8	FM(IP1SR5_11_8)		IP1SR5_11_8	FM(IP2SR5_11_8)		IP2SR5_11_8 \
FM(IP0SR5_15_12)	IP0SR5_15_12	FM(IP1SR5_15_12)	IP1SR5_15_12	FM(IP2SR5_15_12)	IP2SR5_15_12 \
FM(IP0SR5_19_16)	IP0SR5_19_16	FM(IP1SR5_19_16)	IP1SR5_19_16	FM(IP2SR5_19_16)	IP2SR5_19_16 \
FM(IP0SR5_23_20)	IP0SR5_23_20	FM(IP1SR5_23_20)	IP1SR5_23_20	FM(IP2SR5_23_20)	IP2SR5_23_20 \
FM(IP0SR5_27_24)	IP0SR5_27_24	FM(IP1SR5_27_24)	IP1SR5_27_24	FM(IP2SR5_27_24)	IP2SR5_27_24 \
FM(IP0SR5_31_28)	IP0SR5_31_28	FM(IP1SR5_31_28)	IP1SR5_31_28	FM(IP2SR5_31_28)	IP2SR5_31_28

/* MOD_SEL2 */			/* 0 */		/* 1 */		/* 2 */		/* 3 */
#घोषणा MOD_SEL2_14_15		FM(SEL_I2C6_0)	F_(0, 0)	F_(0, 0)	FM(SEL_I2C6_3)
#घोषणा MOD_SEL2_12_13		FM(SEL_I2C5_0)	F_(0, 0)	F_(0, 0)	FM(SEL_I2C5_3)
#घोषणा MOD_SEL2_10_11		FM(SEL_I2C4_0)	F_(0, 0)	F_(0, 0)	FM(SEL_I2C4_3)
#घोषणा MOD_SEL2_8_9		FM(SEL_I2C3_0)	F_(0, 0)	F_(0, 0)	FM(SEL_I2C3_3)
#घोषणा MOD_SEL2_6_7		FM(SEL_I2C2_0)	F_(0, 0)	F_(0, 0)	FM(SEL_I2C2_3)
#घोषणा MOD_SEL2_4_5		FM(SEL_I2C1_0)	F_(0, 0)	F_(0, 0)	FM(SEL_I2C1_3)
#घोषणा MOD_SEL2_2_3		FM(SEL_I2C0_0)	F_(0, 0)	F_(0, 0)	FM(SEL_I2C0_3)

#घोषणा PINMUX_MOD_SELS \
\
MOD_SEL2_14_15 \
MOD_SEL2_12_13 \
MOD_SEL2_10_11 \
MOD_SEL2_8_9 \
MOD_SEL2_6_7 \
MOD_SEL2_4_5 \
MOD_SEL2_2_3

#घोषणा PINMUX_PHYS \
	FM(SCL0) FM(SDA0) FM(SCL1) FM(SDA1) FM(SCL2) FM(SDA2) FM(SCL3) FM(SDA3) \
	FM(SCL4) FM(SDA4) FM(SCL5) FM(SDA5) FM(SCL6) FM(SDA6)

क्रमागत अणु
	PINMUX_RESERVED = 0,

	PINMUX_DATA_BEGIN,
	GP_ALL(DATA),
	PINMUX_DATA_END,

#घोषणा F_(x, y)
#घोषणा FM(x)   FN_##x,
	PINMUX_FUNCTION_BEGIN,
	GP_ALL(FN),
	PINMUX_GPSR
	PINMUX_IPSR
	PINMUX_MOD_SELS
	PINMUX_FUNCTION_END,
#अघोषित F_
#अघोषित FM

#घोषणा F_(x, y)
#घोषणा FM(x)	x##_MARK,
	PINMUX_MARK_BEGIN,
	PINMUX_GPSR
	PINMUX_IPSR
	PINMUX_MOD_SELS
	PINMUX_PHYS
	PINMUX_MARK_END,
#अघोषित F_
#अघोषित FM
पूर्ण;

अटल स्थिर u16 pinmux_data[] = अणु
	PINMUX_DATA_GP_ALL(),

	PINMUX_SINGLE(MMC_D7),
	PINMUX_SINGLE(MMC_D6),
	PINMUX_SINGLE(MMC_D5),
	PINMUX_SINGLE(MMC_D4),
	PINMUX_SINGLE(MMC_SD_CLK),
	PINMUX_SINGLE(MMC_SD_D3),
	PINMUX_SINGLE(MMC_SD_D2),
	PINMUX_SINGLE(MMC_SD_D1),
	PINMUX_SINGLE(MMC_SD_D0),
	PINMUX_SINGLE(MMC_SD_CMD),
	PINMUX_SINGLE(MMC_DS),

	PINMUX_SINGLE(SD_CD),
	PINMUX_SINGLE(SD_WP),

	PINMUX_SINGLE(RPC_INT_N),
	PINMUX_SINGLE(RPC_WP_N),
	PINMUX_SINGLE(RPC_RESET_N),

	PINMUX_SINGLE(QSPI1_SSL),
	PINMUX_SINGLE(QSPI1_IO3),
	PINMUX_SINGLE(QSPI1_IO2),
	PINMUX_SINGLE(QSPI1_MISO_IO1),
	PINMUX_SINGLE(QSPI1_MOSI_IO0),
	PINMUX_SINGLE(QSPI1_SPCLK),
	PINMUX_SINGLE(QSPI0_SSL),
	PINMUX_SINGLE(QSPI0_IO3),
	PINMUX_SINGLE(QSPI0_IO2),
	PINMUX_SINGLE(QSPI0_MISO_IO1),
	PINMUX_SINGLE(QSPI0_MOSI_IO0),
	PINMUX_SINGLE(QSPI0_SPCLK),

	PINMUX_SINGLE(TCLK2_A),

	PINMUX_SINGLE(CANFD7_RX),
	PINMUX_SINGLE(CANFD7_TX),
	PINMUX_SINGLE(CANFD6_RX),
	PINMUX_SINGLE(CANFD1_RX),
	PINMUX_SINGLE(CANFD1_TX),
	PINMUX_SINGLE(CAN_CLK),

	PINMUX_SINGLE(AVS1),
	PINMUX_SINGLE(AVS0),

	PINMUX_SINGLE(PCIE3_CLKREQ_N),
	PINMUX_SINGLE(PCIE2_CLKREQ_N),
	PINMUX_SINGLE(PCIE1_CLKREQ_N),
	PINMUX_SINGLE(PCIE0_CLKREQ_N),

	PINMUX_SINGLE(AVB0_PHY_INT),
	PINMUX_SINGLE(AVB0_MAGIC),
	PINMUX_SINGLE(AVB0_MDC),
	PINMUX_SINGLE(AVB0_MDIO),
	PINMUX_SINGLE(AVB0_TXCREFCLK),

	PINMUX_SINGLE(AVB1_PHY_INT),
	PINMUX_SINGLE(AVB1_MAGIC),
	PINMUX_SINGLE(AVB1_MDC),
	PINMUX_SINGLE(AVB1_MDIO),
	PINMUX_SINGLE(AVB1_TXCREFCLK),

	PINMUX_SINGLE(AVB2_AVTP_PPS),
	PINMUX_SINGLE(AVB2_AVTP_CAPTURE),
	PINMUX_SINGLE(AVB2_AVTP_MATCH),
	PINMUX_SINGLE(AVB2_LINK),
	PINMUX_SINGLE(AVB2_PHY_INT),
	PINMUX_SINGLE(AVB2_MAGIC),
	PINMUX_SINGLE(AVB2_MDC),
	PINMUX_SINGLE(AVB2_MDIO),
	PINMUX_SINGLE(AVB2_TXCREFCLK),
	PINMUX_SINGLE(AVB2_TD3),
	PINMUX_SINGLE(AVB2_TD2),
	PINMUX_SINGLE(AVB2_TD1),
	PINMUX_SINGLE(AVB2_TD0),
	PINMUX_SINGLE(AVB2_TXC),
	PINMUX_SINGLE(AVB2_TX_CTL),
	PINMUX_SINGLE(AVB2_RD3),
	PINMUX_SINGLE(AVB2_RD2),
	PINMUX_SINGLE(AVB2_RD1),
	PINMUX_SINGLE(AVB2_RD0),
	PINMUX_SINGLE(AVB2_RXC),
	PINMUX_SINGLE(AVB2_RX_CTL),

	PINMUX_SINGLE(AVB3_AVTP_PPS),
	PINMUX_SINGLE(AVB3_AVTP_CAPTURE),
	PINMUX_SINGLE(AVB3_AVTP_MATCH),
	PINMUX_SINGLE(AVB3_LINK),
	PINMUX_SINGLE(AVB3_PHY_INT),
	PINMUX_SINGLE(AVB3_MAGIC),
	PINMUX_SINGLE(AVB3_MDC),
	PINMUX_SINGLE(AVB3_MDIO),
	PINMUX_SINGLE(AVB3_TXCREFCLK),
	PINMUX_SINGLE(AVB3_TD3),
	PINMUX_SINGLE(AVB3_TD2),
	PINMUX_SINGLE(AVB3_TD1),
	PINMUX_SINGLE(AVB3_TD0),
	PINMUX_SINGLE(AVB3_TXC),
	PINMUX_SINGLE(AVB3_TX_CTL),
	PINMUX_SINGLE(AVB3_RD3),
	PINMUX_SINGLE(AVB3_RD2),
	PINMUX_SINGLE(AVB3_RD1),
	PINMUX_SINGLE(AVB3_RD0),
	PINMUX_SINGLE(AVB3_RXC),
	PINMUX_SINGLE(AVB3_RX_CTL),

	PINMUX_SINGLE(AVB4_AVTP_PPS),
	PINMUX_SINGLE(AVB4_AVTP_CAPTURE),
	PINMUX_SINGLE(AVB4_AVTP_MATCH),
	PINMUX_SINGLE(AVB4_LINK),
	PINMUX_SINGLE(AVB4_PHY_INT),
	PINMUX_SINGLE(AVB4_MAGIC),
	PINMUX_SINGLE(AVB4_MDC),
	PINMUX_SINGLE(AVB4_MDIO),
	PINMUX_SINGLE(AVB4_TXCREFCLK),
	PINMUX_SINGLE(AVB4_TD3),
	PINMUX_SINGLE(AVB4_TD2),
	PINMUX_SINGLE(AVB4_TD1),
	PINMUX_SINGLE(AVB4_TD0),
	PINMUX_SINGLE(AVB4_TXC),
	PINMUX_SINGLE(AVB4_TX_CTL),
	PINMUX_SINGLE(AVB4_RD3),
	PINMUX_SINGLE(AVB4_RD2),
	PINMUX_SINGLE(AVB4_RD1),
	PINMUX_SINGLE(AVB4_RD0),
	PINMUX_SINGLE(AVB4_RXC),
	PINMUX_SINGLE(AVB4_RX_CTL),

	PINMUX_SINGLE(AVB5_AVTP_PPS),
	PINMUX_SINGLE(AVB5_AVTP_CAPTURE),
	PINMUX_SINGLE(AVB5_AVTP_MATCH),
	PINMUX_SINGLE(AVB5_LINK),
	PINMUX_SINGLE(AVB5_PHY_INT),
	PINMUX_SINGLE(AVB5_MAGIC),
	PINMUX_SINGLE(AVB5_MDC),
	PINMUX_SINGLE(AVB5_MDIO),
	PINMUX_SINGLE(AVB5_TXCREFCLK),
	PINMUX_SINGLE(AVB5_TD3),
	PINMUX_SINGLE(AVB5_TD2),
	PINMUX_SINGLE(AVB5_TD1),
	PINMUX_SINGLE(AVB5_TD0),
	PINMUX_SINGLE(AVB5_TXC),
	PINMUX_SINGLE(AVB5_TX_CTL),
	PINMUX_SINGLE(AVB5_RD3),
	PINMUX_SINGLE(AVB5_RD2),
	PINMUX_SINGLE(AVB5_RD1),
	PINMUX_SINGLE(AVB5_RD0),
	PINMUX_SINGLE(AVB5_RXC),
	PINMUX_SINGLE(AVB5_RX_CTL),

	/* IP0SR1 */
	PINMUX_IPSR_GPSR(IP0SR1_3_0,	SCIF_CLK),
	PINMUX_IPSR_GPSR(IP0SR1_3_0,	A0),

	PINMUX_IPSR_GPSR(IP0SR1_7_4,	HRX0),
	PINMUX_IPSR_GPSR(IP0SR1_7_4,	RX0),
	PINMUX_IPSR_GPSR(IP0SR1_7_4,	A1),

	PINMUX_IPSR_GPSR(IP0SR1_11_8,	HSCK0),
	PINMUX_IPSR_GPSR(IP0SR1_11_8,	SCK0),
	PINMUX_IPSR_GPSR(IP0SR1_11_8,	A2),

	PINMUX_IPSR_GPSR(IP0SR1_15_12,	HRTS0_N),
	PINMUX_IPSR_GPSR(IP0SR1_15_12,	RTS0_N),
	PINMUX_IPSR_GPSR(IP0SR1_15_12,	A3),

	PINMUX_IPSR_GPSR(IP0SR1_19_16,	HCTS0_N),
	PINMUX_IPSR_GPSR(IP0SR1_19_16,	CTS0_N),
	PINMUX_IPSR_GPSR(IP0SR1_19_16,	A4),

	PINMUX_IPSR_GPSR(IP0SR1_23_20,	HTX0),
	PINMUX_IPSR_GPSR(IP0SR1_23_20,	TX0),
	PINMUX_IPSR_GPSR(IP0SR1_23_20,	A5),

	PINMUX_IPSR_GPSR(IP0SR1_27_24,	MSIOF0_RXD),
	PINMUX_IPSR_GPSR(IP0SR1_27_24,	DU_DR2),
	PINMUX_IPSR_GPSR(IP0SR1_27_24,	A6),

	PINMUX_IPSR_GPSR(IP0SR1_31_28,	MSIOF0_TXD),
	PINMUX_IPSR_GPSR(IP0SR1_31_28,	DU_DR3),
	PINMUX_IPSR_GPSR(IP0SR1_31_28,	A7),

	/* IP1SR1 */
	PINMUX_IPSR_GPSR(IP1SR1_3_0,	MSIOF0_SCK),
	PINMUX_IPSR_GPSR(IP1SR1_3_0,	DU_DR4),
	PINMUX_IPSR_GPSR(IP1SR1_3_0,	A8),

	PINMUX_IPSR_GPSR(IP1SR1_7_4,	MSIOF0_SYNC),
	PINMUX_IPSR_GPSR(IP1SR1_7_4,	DU_DR5),
	PINMUX_IPSR_GPSR(IP1SR1_7_4,	A9),

	PINMUX_IPSR_GPSR(IP1SR1_11_8,	MSIOF0_SS1),
	PINMUX_IPSR_GPSR(IP1SR1_11_8,	DU_DR6),
	PINMUX_IPSR_GPSR(IP1SR1_11_8,	A10),

	PINMUX_IPSR_GPSR(IP1SR1_15_12,	MSIOF0_SS2),
	PINMUX_IPSR_GPSR(IP1SR1_15_12,	DU_DR7),
	PINMUX_IPSR_GPSR(IP1SR1_15_12,	A11),

	PINMUX_IPSR_GPSR(IP1SR1_19_16,	MSIOF1_RXD),
	PINMUX_IPSR_GPSR(IP1SR1_19_16,	DU_DG2),
	PINMUX_IPSR_GPSR(IP1SR1_19_16,	A12),

	PINMUX_IPSR_GPSR(IP1SR1_23_20,	MSIOF1_TXD),
	PINMUX_IPSR_GPSR(IP1SR1_23_20,	HRX3),
	PINMUX_IPSR_GPSR(IP1SR1_23_20,	SCK3),
	PINMUX_IPSR_GPSR(IP1SR1_23_20,	DU_DG3),
	PINMUX_IPSR_GPSR(IP1SR1_23_20,	A13),

	PINMUX_IPSR_GPSR(IP1SR1_27_24,	MSIOF1_SCK),
	PINMUX_IPSR_GPSR(IP1SR1_27_24,	HSCK3),
	PINMUX_IPSR_GPSR(IP1SR1_27_24,	CTS3_N),
	PINMUX_IPSR_GPSR(IP1SR1_27_24,	DU_DG4),
	PINMUX_IPSR_GPSR(IP1SR1_27_24,	A14),

	PINMUX_IPSR_GPSR(IP1SR1_31_28,	MSIOF1_SYNC),
	PINMUX_IPSR_GPSR(IP1SR1_31_28,	HRTS3_N),
	PINMUX_IPSR_GPSR(IP1SR1_31_28,	RTS3_N),
	PINMUX_IPSR_GPSR(IP1SR1_31_28,	DU_DG5),
	PINMUX_IPSR_GPSR(IP1SR1_31_28,	A15),

	/* IP2SR1 */
	PINMUX_IPSR_GPSR(IP2SR1_3_0,	MSIOF1_SS1),
	PINMUX_IPSR_GPSR(IP2SR1_3_0,	HCTS3_N),
	PINMUX_IPSR_GPSR(IP2SR1_3_0,	RX3),
	PINMUX_IPSR_GPSR(IP2SR1_3_0,	DU_DG6),
	PINMUX_IPSR_GPSR(IP2SR1_3_0,	A16),

	PINMUX_IPSR_GPSR(IP2SR1_7_4,	MSIOF1_SS2),
	PINMUX_IPSR_GPSR(IP2SR1_7_4,	HTX3),
	PINMUX_IPSR_GPSR(IP2SR1_7_4,	TX3),
	PINMUX_IPSR_GPSR(IP2SR1_7_4,	DU_DG7),
	PINMUX_IPSR_GPSR(IP2SR1_7_4,	A17),

	PINMUX_IPSR_GPSR(IP2SR1_11_8,	MSIOF2_RXD),
	PINMUX_IPSR_GPSR(IP2SR1_11_8,	HSCK1),
	PINMUX_IPSR_GPSR(IP2SR1_11_8,	SCK1),
	PINMUX_IPSR_GPSR(IP2SR1_11_8,	DU_DB2),
	PINMUX_IPSR_GPSR(IP2SR1_11_8,	A18),

	PINMUX_IPSR_GPSR(IP2SR1_15_12,	MSIOF2_TXD),
	PINMUX_IPSR_GPSR(IP2SR1_15_12,	HCTS1_N),
	PINMUX_IPSR_GPSR(IP2SR1_15_12,	CTS1_N),
	PINMUX_IPSR_GPSR(IP2SR1_15_12,	DU_DB3),
	PINMUX_IPSR_GPSR(IP2SR1_15_12,	A19),

	PINMUX_IPSR_GPSR(IP2SR1_19_16,	MSIOF2_SCK),
	PINMUX_IPSR_GPSR(IP2SR1_19_16,	HRTS1_N),
	PINMUX_IPSR_GPSR(IP2SR1_19_16,	RTS1_N),
	PINMUX_IPSR_GPSR(IP2SR1_19_16,	DU_DB4),
	PINMUX_IPSR_GPSR(IP2SR1_19_16,	A20),

	PINMUX_IPSR_GPSR(IP2SR1_23_20,	MSIOF2_SYNC),
	PINMUX_IPSR_GPSR(IP2SR1_23_20,	HRX1),
	PINMUX_IPSR_GPSR(IP2SR1_23_20,	RX1_A),
	PINMUX_IPSR_GPSR(IP2SR1_23_20,	DU_DB5),
	PINMUX_IPSR_GPSR(IP2SR1_23_20,	A21),

	PINMUX_IPSR_GPSR(IP2SR1_27_24,	MSIOF2_SS1),
	PINMUX_IPSR_GPSR(IP2SR1_27_24,	HTX1),
	PINMUX_IPSR_GPSR(IP2SR1_27_24,	TX1_A),
	PINMUX_IPSR_GPSR(IP2SR1_27_24,	DU_DB6),
	PINMUX_IPSR_GPSR(IP2SR1_27_24,	A22),

	PINMUX_IPSR_GPSR(IP2SR1_31_28,	MSIOF2_SS2),
	PINMUX_IPSR_GPSR(IP2SR1_31_28,	TCLK1_B),
	PINMUX_IPSR_GPSR(IP2SR1_31_28,	DU_DB7),
	PINMUX_IPSR_GPSR(IP2SR1_31_28,	A23),

	/* IP3SR1 */
	PINMUX_IPSR_GPSR(IP3SR1_3_0,	IRQ0),
	PINMUX_IPSR_GPSR(IP3SR1_3_0,	DU_DOTCLKOUT),
	PINMUX_IPSR_GPSR(IP3SR1_3_0,	A24),

	PINMUX_IPSR_GPSR(IP3SR1_7_4,	IRQ1),
	PINMUX_IPSR_GPSR(IP3SR1_7_4,	DU_HSYNC),
	PINMUX_IPSR_GPSR(IP3SR1_7_4,	A25),

	PINMUX_IPSR_GPSR(IP3SR1_11_8,	IRQ2),
	PINMUX_IPSR_GPSR(IP3SR1_11_8,	DU_VSYNC),
	PINMUX_IPSR_GPSR(IP3SR1_11_8,	CS1_N_A26),

	PINMUX_IPSR_GPSR(IP3SR1_15_12,	IRQ3),
	PINMUX_IPSR_GPSR(IP3SR1_15_12,	DU_ODDF_DISP_CDE),
	PINMUX_IPSR_GPSR(IP3SR1_15_12,	CS0_N),

	PINMUX_IPSR_GPSR(IP3SR1_19_16,	GP1_28),
	PINMUX_IPSR_GPSR(IP3SR1_19_16,	D0),

	PINMUX_IPSR_GPSR(IP3SR1_23_20,	GP1_29),
	PINMUX_IPSR_GPSR(IP3SR1_23_20,	D1),

	PINMUX_IPSR_GPSR(IP3SR1_27_24,	GP1_30),
	PINMUX_IPSR_GPSR(IP3SR1_27_24,	D2),

	/* IP0SR2 */
	PINMUX_IPSR_GPSR(IP0SR2_3_0,	IPC_CLKIN),
	PINMUX_IPSR_GPSR(IP0SR2_3_0,	IPC_CLKEN_IN),
	PINMUX_IPSR_GPSR(IP0SR2_3_0,	DU_DOTCLKIN),

	PINMUX_IPSR_GPSR(IP0SR2_7_4,	IPC_CLKOUT),
	PINMUX_IPSR_GPSR(IP0SR2_7_4,	IPC_CLKEN_OUT),

	/* GP2_02 = SCL0 */
	PINMUX_IPSR_MSEL(IP0SR2_11_8,	GP2_02,	SEL_I2C0_0),
	PINMUX_IPSR_MSEL(IP0SR2_11_8,	D3,	SEL_I2C0_0),
	PINMUX_IPSR_PHYS(IP0SR2_11_8,	SCL0,	SEL_I2C0_3),

	/* GP2_03 = SDA0 */
	PINMUX_IPSR_MSEL(IP0SR2_15_12,	GP2_03,	SEL_I2C0_0),
	PINMUX_IPSR_MSEL(IP0SR2_15_12,	D4,	SEL_I2C0_0),
	PINMUX_IPSR_PHYS(IP0SR2_15_12,	SDA0,	SEL_I2C0_3),

	/* GP2_04 = SCL1 */
	PINMUX_IPSR_MSEL(IP0SR2_19_16,	GP2_04,		SEL_I2C1_0),
	PINMUX_IPSR_MSEL(IP0SR2_19_16,	MSIOF4_RXD,	SEL_I2C1_0),
	PINMUX_IPSR_MSEL(IP0SR2_19_16,	D5,		SEL_I2C1_0),
	PINMUX_IPSR_PHYS(IP0SR2_19_16,	SCL1,		SEL_I2C1_3),

	/* GP2_05 = SDA1 */
	PINMUX_IPSR_MSEL(IP0SR2_23_20,	GP2_05,		SEL_I2C1_0),
	PINMUX_IPSR_MSEL(IP0SR2_23_20,	HSCK2,		SEL_I2C1_0),
	PINMUX_IPSR_MSEL(IP0SR2_23_20,	MSIOF4_TXD,	SEL_I2C1_0),
	PINMUX_IPSR_MSEL(IP0SR2_23_20,	SCK4,		SEL_I2C1_0),
	PINMUX_IPSR_MSEL(IP0SR2_23_20,	D6,		SEL_I2C1_0),
	PINMUX_IPSR_PHYS(IP0SR2_23_20,	SDA1,		SEL_I2C1_3),

	/* GP2_06 = SCL2 */
	PINMUX_IPSR_MSEL(IP0SR2_27_24,	GP2_06,		SEL_I2C2_0),
	PINMUX_IPSR_MSEL(IP0SR2_27_24,	HCTS2_N,	SEL_I2C2_0),
	PINMUX_IPSR_MSEL(IP0SR2_27_24,	MSIOF4_SCK,	SEL_I2C2_0),
	PINMUX_IPSR_MSEL(IP0SR2_27_24,	CTS4_N,		SEL_I2C2_0),
	PINMUX_IPSR_MSEL(IP0SR2_27_24,	D7,		SEL_I2C2_0),
	PINMUX_IPSR_PHYS(IP0SR2_27_24,	SCL2,		SEL_I2C2_3),

	/* GP2_07 = SDA2 */
	PINMUX_IPSR_MSEL(IP0SR2_31_28,	GP2_07,		SEL_I2C2_0),
	PINMUX_IPSR_MSEL(IP0SR2_31_28,	HRTS2_N,	SEL_I2C2_0),
	PINMUX_IPSR_MSEL(IP0SR2_31_28,	MSIOF4_SYNC,	SEL_I2C2_0),
	PINMUX_IPSR_MSEL(IP0SR2_31_28,	RTS4_N,		SEL_I2C2_0),
	PINMUX_IPSR_MSEL(IP0SR2_31_28,	D8,		SEL_I2C2_0),
	PINMUX_IPSR_PHYS(IP0SR2_31_28,	SDA2,		SEL_I2C2_3),

	/* GP2_08 = SCL3 */
	PINMUX_IPSR_MSEL(IP1SR2_3_0,	GP2_08,		SEL_I2C3_0),
	PINMUX_IPSR_MSEL(IP1SR2_3_0,	HRX2,		SEL_I2C3_0),
	PINMUX_IPSR_MSEL(IP1SR2_3_0,	MSIOF4_SS1,	SEL_I2C3_0),
	PINMUX_IPSR_MSEL(IP1SR2_3_0,	RX4,		SEL_I2C3_0),
	PINMUX_IPSR_MSEL(IP1SR2_3_0,	D9,		SEL_I2C3_0),
	PINMUX_IPSR_PHYS(IP1SR2_3_0,	SCL3,		SEL_I2C3_3),

	/* GP2_09 = SDA3 */
	PINMUX_IPSR_MSEL(IP1SR2_7_4,	GP2_09,		SEL_I2C3_0),
	PINMUX_IPSR_MSEL(IP1SR2_7_4,	HTX2,		SEL_I2C3_0),
	PINMUX_IPSR_MSEL(IP1SR2_7_4,	MSIOF4_SS2,	SEL_I2C3_0),
	PINMUX_IPSR_MSEL(IP1SR2_7_4,	TX4,		SEL_I2C3_0),
	PINMUX_IPSR_MSEL(IP1SR2_7_4,	D10,		SEL_I2C3_0),
	PINMUX_IPSR_PHYS(IP1SR2_7_4,	SDA3,		SEL_I2C3_3),

	/* GP2_10 = SCL4 */
	PINMUX_IPSR_MSEL(IP1SR2_11_8,	GP2_10,		SEL_I2C4_0),
	PINMUX_IPSR_MSEL(IP1SR2_11_8,	TCLK2_B,	SEL_I2C4_0),
	PINMUX_IPSR_MSEL(IP1SR2_11_8,	MSIOF5_RXD,	SEL_I2C4_0),
	PINMUX_IPSR_MSEL(IP1SR2_11_8,	D11,		SEL_I2C4_0),
	PINMUX_IPSR_PHYS(IP1SR2_11_8,	SCL4,		SEL_I2C4_3),

	/* GP2_11 = SDA4 */
	PINMUX_IPSR_MSEL(IP1SR2_15_12,	GP2_11,		SEL_I2C4_0),
	PINMUX_IPSR_MSEL(IP1SR2_15_12,	TCLK3,		SEL_I2C4_0),
	PINMUX_IPSR_MSEL(IP1SR2_15_12,	MSIOF5_TXD,	SEL_I2C4_0),
	PINMUX_IPSR_MSEL(IP1SR2_15_12,	D12,		SEL_I2C4_0),
	PINMUX_IPSR_PHYS(IP1SR2_15_12,	SDA4,		SEL_I2C4_3),

	/* GP2_12 = SCL5 */
	PINMUX_IPSR_MSEL(IP1SR2_19_16,	GP2_12,		SEL_I2C5_0),
	PINMUX_IPSR_MSEL(IP1SR2_19_16,	TCLK4,		SEL_I2C5_0),
	PINMUX_IPSR_MSEL(IP1SR2_19_16,	MSIOF5_SCK,	SEL_I2C5_0),
	PINMUX_IPSR_MSEL(IP1SR2_19_16,	D13,		SEL_I2C5_0),
	PINMUX_IPSR_PHYS(IP1SR2_19_16,	SCL5,		SEL_I2C5_3),

	/* GP2_13 = SDA5 */
	PINMUX_IPSR_MSEL(IP1SR2_23_20,	GP2_13,		SEL_I2C5_0),
	PINMUX_IPSR_MSEL(IP1SR2_23_20,	MSIOF5_SYNC,	SEL_I2C5_0),
	PINMUX_IPSR_MSEL(IP1SR2_23_20,	D14,		SEL_I2C5_0),
	PINMUX_IPSR_PHYS(IP1SR2_23_20,	SDA5,		SEL_I2C5_3),

	/* GP2_14 = SCL6 */
	PINMUX_IPSR_MSEL(IP1SR2_27_24,	GP2_14,		SEL_I2C6_0),
	PINMUX_IPSR_MSEL(IP1SR2_27_24,	IRQ4,		SEL_I2C6_0),
	PINMUX_IPSR_MSEL(IP1SR2_27_24,	MSIOF5_SS1,	SEL_I2C6_0),
	PINMUX_IPSR_MSEL(IP1SR2_27_24,	D15,		SEL_I2C6_0),
	PINMUX_IPSR_PHYS(IP1SR2_27_24,	SCL6,		SEL_I2C6_3),

	/* GP2_15 = SDA6 */
	PINMUX_IPSR_MSEL(IP1SR2_31_28,	GP2_15,		SEL_I2C6_0),
	PINMUX_IPSR_MSEL(IP1SR2_31_28,	IRQ5,		SEL_I2C6_0),
	PINMUX_IPSR_MSEL(IP1SR2_31_28,	MSIOF5_SS2,	SEL_I2C6_0),
	PINMUX_IPSR_MSEL(IP1SR2_31_28,	CPG_CPCKOUT,	SEL_I2C6_0),
	PINMUX_IPSR_PHYS(IP1SR2_31_28,	SDA6,		SEL_I2C6_3),

	/* IP2SR2 */
	PINMUX_IPSR_GPSR(IP2SR2_3_0,	FXR_TXDA_A),
	PINMUX_IPSR_GPSR(IP2SR2_3_0,	MSIOF3_SS1),

	PINMUX_IPSR_GPSR(IP2SR2_7_4,	RXDA_EXTFXR_A),
	PINMUX_IPSR_GPSR(IP2SR2_7_4,	MSIOF3_SS2),
	PINMUX_IPSR_GPSR(IP2SR2_7_4,	BS_N),

	PINMUX_IPSR_GPSR(IP2SR2_11_8,	FXR_TXDB),
	PINMUX_IPSR_GPSR(IP2SR2_11_8,	MSIOF3_RXD),
	PINMUX_IPSR_GPSR(IP2SR2_11_8,	RD_N),

	PINMUX_IPSR_GPSR(IP2SR2_15_12,	RXDB_EXTFXR),
	PINMUX_IPSR_GPSR(IP2SR2_15_12,	MSIOF3_TXD),
	PINMUX_IPSR_GPSR(IP2SR2_15_12,	WE0_N),

	PINMUX_IPSR_GPSR(IP2SR2_19_16,	CLK_EXTFXR),
	PINMUX_IPSR_GPSR(IP2SR2_19_16,	MSIOF3_SCK),
	PINMUX_IPSR_GPSR(IP2SR2_19_16,	WE1_N),

	PINMUX_IPSR_GPSR(IP2SR2_23_20,	TPU0TO0),
	PINMUX_IPSR_GPSR(IP2SR2_23_20,	MSIOF3_SYNC),
	PINMUX_IPSR_GPSR(IP2SR2_23_20,	RD_WR_N),

	PINMUX_IPSR_GPSR(IP2SR2_27_24,	TPU0TO1),
	PINMUX_IPSR_GPSR(IP2SR2_27_24,	CLKOUT),

	PINMUX_IPSR_GPSR(IP2SR2_31_28,	TCLK1_A),
	PINMUX_IPSR_GPSR(IP2SR2_31_28,	EX_WAIT0),

	/* IP0SR3 */
	PINMUX_IPSR_GPSR(IP0SR3_7_4,	CANFD0_TX),
	PINMUX_IPSR_GPSR(IP0SR3_7_4,	FXR_TXDA_B),
	PINMUX_IPSR_GPSR(IP0SR3_7_4,	TX1_B),

	PINMUX_IPSR_GPSR(IP0SR3_11_8,	CANFD0_RX),
	PINMUX_IPSR_GPSR(IP0SR3_11_8,	RXDA_EXTFXR_B),
	PINMUX_IPSR_GPSR(IP0SR3_11_8,	RX1_B),

	PINMUX_IPSR_GPSR(IP0SR3_23_20,	CANFD2_TX),
	PINMUX_IPSR_GPSR(IP0SR3_23_20,	TPU0TO2),
	PINMUX_IPSR_GPSR(IP0SR3_23_20,	PWM0),

	PINMUX_IPSR_GPSR(IP0SR3_27_24,	CANFD2_RX),
	PINMUX_IPSR_GPSR(IP0SR3_27_24,	TPU0TO3),
	PINMUX_IPSR_GPSR(IP0SR3_27_24,	PWM1),

	PINMUX_IPSR_GPSR(IP0SR3_31_28,	CANFD3_TX),
	PINMUX_IPSR_GPSR(IP0SR3_31_28,	PWM2),

	/* IP1SR3 */
	PINMUX_IPSR_GPSR(IP1SR3_3_0,	CANFD3_RX),
	PINMUX_IPSR_GPSR(IP1SR3_3_0,	PWM3),

	PINMUX_IPSR_GPSR(IP1SR3_7_4,	CANFD4_TX),
	PINMUX_IPSR_GPSR(IP1SR3_7_4,	PWM4),
	PINMUX_IPSR_GPSR(IP1SR3_7_4,	FXR_CLKOUT1),

	PINMUX_IPSR_GPSR(IP1SR3_11_8,	CANFD4_RX),
	PINMUX_IPSR_GPSR(IP1SR3_11_8,	FXR_CLKOUT2),

	PINMUX_IPSR_GPSR(IP1SR3_15_12,	CANFD5_TX),
	PINMUX_IPSR_GPSR(IP1SR3_15_12,	FXR_TXENA_N),

	PINMUX_IPSR_GPSR(IP1SR3_19_16,	CANFD5_RX),
	PINMUX_IPSR_GPSR(IP1SR3_19_16,	FXR_TXENB_N),

	PINMUX_IPSR_GPSR(IP1SR3_23_20,	CANFD6_TX),
	PINMUX_IPSR_GPSR(IP1SR3_23_20,	STPWT_EXTFXR),

	/* IP0SR4 */
	PINMUX_IPSR_GPSR(IP0SR4_3_0,	AVB0_RX_CTL),
	PINMUX_IPSR_GPSR(IP0SR4_3_0,	AVB0_MII_RX_DV),

	PINMUX_IPSR_GPSR(IP0SR4_7_4,	AVB0_RXC),
	PINMUX_IPSR_GPSR(IP0SR4_7_4,	AVB0_MII_RXC),

	PINMUX_IPSR_GPSR(IP0SR4_11_8,	AVB0_RD0),
	PINMUX_IPSR_GPSR(IP0SR4_11_8,	AVB0_MII_RD0),

	PINMUX_IPSR_GPSR(IP0SR4_15_12,	AVB0_RD1),
	PINMUX_IPSR_GPSR(IP0SR4_15_12,	AVB0_MII_RD1),

	PINMUX_IPSR_GPSR(IP0SR4_19_16,	AVB0_RD2),
	PINMUX_IPSR_GPSR(IP0SR4_19_16,	AVB0_MII_RD2),

	PINMUX_IPSR_GPSR(IP0SR4_23_20,	AVB0_RD3),
	PINMUX_IPSR_GPSR(IP0SR4_23_20,	AVB0_MII_RD3),

	PINMUX_IPSR_GPSR(IP0SR4_27_24,	AVB0_TX_CTL),
	PINMUX_IPSR_GPSR(IP0SR4_27_24,	AVB0_MII_TX_EN),

	PINMUX_IPSR_GPSR(IP0SR4_31_28,	AVB0_TXC),
	PINMUX_IPSR_GPSR(IP0SR4_31_28,	AVB0_MII_TXC),

	/* IP1SR4 */
	PINMUX_IPSR_GPSR(IP1SR4_3_0,	AVB0_TD0),
	PINMUX_IPSR_GPSR(IP1SR4_3_0,	AVB0_MII_TD0),

	PINMUX_IPSR_GPSR(IP1SR4_7_4,	AVB0_TD1),
	PINMUX_IPSR_GPSR(IP1SR4_7_4,	AVB0_MII_TD1),

	PINMUX_IPSR_GPSR(IP1SR4_11_8,	AVB0_TD2),
	PINMUX_IPSR_GPSR(IP1SR4_11_8,	AVB0_MII_TD2),

	PINMUX_IPSR_GPSR(IP1SR4_15_12,	AVB0_TD3),
	PINMUX_IPSR_GPSR(IP1SR4_15_12,	AVB0_MII_TD3),

	PINMUX_IPSR_GPSR(IP1SR4_19_16,	AVB0_TXCREFCLK),

	PINMUX_IPSR_GPSR(IP1SR4_23_20,	AVB0_MDIO),

	PINMUX_IPSR_GPSR(IP1SR4_27_24,	AVB0_MDC),

	PINMUX_IPSR_GPSR(IP1SR4_31_28,	AVB0_MAGIC),

	/* IP2SR4 */
	PINMUX_IPSR_GPSR(IP2SR4_7_4,	AVB0_LINK),
	PINMUX_IPSR_GPSR(IP2SR4_7_4,	AVB0_MII_TX_ER),

	PINMUX_IPSR_GPSR(IP2SR4_11_8,	AVB0_AVTP_MATCH),
	PINMUX_IPSR_GPSR(IP2SR4_11_8,	AVB0_MII_RX_ER),
	PINMUX_IPSR_GPSR(IP2SR4_11_8,	CC5_OSCOUT),

	PINMUX_IPSR_GPSR(IP2SR4_15_12,	AVB0_AVTP_CAPTURE),
	PINMUX_IPSR_GPSR(IP2SR4_15_12,	AVB0_MII_CRS),

	PINMUX_IPSR_GPSR(IP2SR4_19_16,	AVB0_AVTP_PPS),
	PINMUX_IPSR_GPSR(IP2SR4_19_16,	AVB0_MII_COL),

	/* IP0SR5 */
	PINMUX_IPSR_GPSR(IP0SR5_3_0,	AVB1_RX_CTL),
	PINMUX_IPSR_GPSR(IP0SR5_3_0,	AVB1_MII_RX_DV),

	PINMUX_IPSR_GPSR(IP0SR5_7_4,	AVB1_RXC),
	PINMUX_IPSR_GPSR(IP0SR5_7_4,	AVB1_MII_RXC),

	PINMUX_IPSR_GPSR(IP0SR5_11_8,	AVB1_RD0),
	PINMUX_IPSR_GPSR(IP0SR5_11_8,	AVB1_MII_RD0),

	PINMUX_IPSR_GPSR(IP0SR5_15_12,	AVB1_RD1),
	PINMUX_IPSR_GPSR(IP0SR5_15_12,	AVB1_MII_RD1),

	PINMUX_IPSR_GPSR(IP0SR5_19_16,	AVB1_RD2),
	PINMUX_IPSR_GPSR(IP0SR5_19_16,	AVB1_MII_RD2),

	PINMUX_IPSR_GPSR(IP0SR5_23_20,	AVB1_RD3),
	PINMUX_IPSR_GPSR(IP0SR5_23_20,	AVB1_MII_RD3),

	PINMUX_IPSR_GPSR(IP0SR5_27_24,	AVB1_TX_CTL),
	PINMUX_IPSR_GPSR(IP0SR5_27_24,	AVB1_MII_TX_EN),

	PINMUX_IPSR_GPSR(IP0SR5_31_28,	AVB1_TXC),
	PINMUX_IPSR_GPSR(IP0SR5_31_28,	AVB1_MII_TXC),

	/* IP1SR5 */
	PINMUX_IPSR_GPSR(IP1SR5_3_0,	AVB1_TD0),
	PINMUX_IPSR_GPSR(IP1SR5_3_0,	AVB1_MII_TD0),

	PINMUX_IPSR_GPSR(IP1SR5_7_4,	AVB1_TD1),
	PINMUX_IPSR_GPSR(IP1SR5_7_4,	AVB1_MII_TD1),

	PINMUX_IPSR_GPSR(IP1SR5_11_8,	AVB1_TD2),
	PINMUX_IPSR_GPSR(IP1SR5_11_8,	AVB1_MII_TD2),

	PINMUX_IPSR_GPSR(IP1SR5_15_12,	AVB1_TD3),
	PINMUX_IPSR_GPSR(IP1SR5_15_12,	AVB1_MII_TD3),

	PINMUX_IPSR_GPSR(IP1SR5_19_16,	AVB1_TXCREFCLK),

	PINMUX_IPSR_GPSR(IP1SR5_23_20,	AVB1_MDIO),

	PINMUX_IPSR_GPSR(IP1SR5_27_24,	AVB1_MDC),

	PINMUX_IPSR_GPSR(IP1SR5_31_28,	AVB1_MAGIC),

	/* IP2SR5 */
	PINMUX_IPSR_GPSR(IP2SR5_7_4,	AVB1_LINK),
	PINMUX_IPSR_GPSR(IP2SR5_7_4,	AVB1_MII_TX_ER),

	PINMUX_IPSR_GPSR(IP2SR5_11_8,	AVB1_AVTP_MATCH),
	PINMUX_IPSR_GPSR(IP2SR5_11_8,	AVB1_MII_RX_ER),

	PINMUX_IPSR_GPSR(IP2SR5_15_12,	AVB1_AVTP_CAPTURE),
	PINMUX_IPSR_GPSR(IP2SR5_15_12,	AVB1_MII_CRS),

	PINMUX_IPSR_GPSR(IP2SR5_19_16,	AVB1_AVTP_PPS),
	PINMUX_IPSR_GPSR(IP2SR5_19_16,	AVB1_MII_COL),
पूर्ण;

/*
 * Pins not associated with a GPIO port.
 */
क्रमागत अणु
	GP_ASSIGN_LAST(),
	NOGP_ALL(),
पूर्ण;

अटल स्थिर काष्ठा sh_pfc_pin pinmux_pins[] = अणु
	PINMUX_GPIO_GP_ALL(),
पूर्ण;

/* - AVB0 ------------------------------------------------ */
अटल स्थिर अचिन्हित पूर्णांक avb0_link_pins[] = अणु
	/* AVB0_LINK */
	RCAR_GP_PIN(4, 17),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_link_mux[] = अणु
	AVB0_LINK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_magic_pins[] = अणु
	/* AVB0_MAGIC */
	RCAR_GP_PIN(4, 15),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_magic_mux[] = अणु
	AVB0_MAGIC_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_phy_पूर्णांक_pins[] = अणु
	/* AVB0_PHY_INT */
	RCAR_GP_PIN(4, 16),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_phy_पूर्णांक_mux[] = अणु
	AVB0_PHY_INT_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_mdio_pins[] = अणु
	/* AVB0_MDC, AVB0_MDIO */
	RCAR_GP_PIN(4, 14), RCAR_GP_PIN(4, 13),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_mdio_mux[] = अणु
	AVB0_MDC_MARK, AVB0_MDIO_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_rgmii_pins[] = अणु
	/*
	 * AVB0_TX_CTL, AVB0_TXC, AVB0_TD0, AVB0_TD1, AVB0_TD2, AVB0_TD3,
	 * AVB0_RX_CTL, AVB0_RXC, AVB0_RD0, AVB0_RD1, AVB0_RD2, AVB0_RD3,
	 */
	RCAR_GP_PIN(4, 6), RCAR_GP_PIN(4, 7),
	RCAR_GP_PIN(4, 8), RCAR_GP_PIN(4, 9),
	RCAR_GP_PIN(4, 10), RCAR_GP_PIN(4, 11),
	RCAR_GP_PIN(4, 0), RCAR_GP_PIN(4, 1),
	RCAR_GP_PIN(4, 2), RCAR_GP_PIN(4, 3),
	RCAR_GP_PIN(4, 4), RCAR_GP_PIN(4, 5),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_rgmii_mux[] = अणु
	AVB0_TX_CTL_MARK, AVB0_TXC_MARK,
	AVB0_TD0_MARK, AVB0_TD1_MARK, AVB0_TD2_MARK, AVB0_TD3_MARK,
	AVB0_RX_CTL_MARK, AVB0_RXC_MARK,
	AVB0_RD0_MARK, AVB0_RD1_MARK, AVB0_RD2_MARK, AVB0_RD3_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_txcrefclk_pins[] = अणु
	/* AVB0_TXCREFCLK */
	RCAR_GP_PIN(4, 12),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_txcrefclk_mux[] = अणु
	AVB0_TXCREFCLK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_avtp_pps_pins[] = अणु
	/* AVB0_AVTP_PPS */
	RCAR_GP_PIN(4, 20),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_avtp_pps_mux[] = अणु
	AVB0_AVTP_PPS_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_avtp_capture_pins[] = अणु
	/* AVB0_AVTP_CAPTURE */
	RCAR_GP_PIN(4, 19),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_avtp_capture_mux[] = अणु
	AVB0_AVTP_CAPTURE_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_avtp_match_pins[] = अणु
	/* AVB0_AVTP_MATCH */
	RCAR_GP_PIN(4, 18),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb0_avtp_match_mux[] = अणु
	AVB0_AVTP_MATCH_MARK,
पूर्ण;

/* - AVB1 ------------------------------------------------ */
अटल स्थिर अचिन्हित पूर्णांक avb1_link_pins[] = अणु
	/* AVB1_LINK */
	RCAR_GP_PIN(5, 17),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_link_mux[] = अणु
	AVB1_LINK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_magic_pins[] = अणु
	/* AVB1_MAGIC */
	RCAR_GP_PIN(5, 15),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_magic_mux[] = अणु
	AVB1_MAGIC_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_phy_पूर्णांक_pins[] = अणु
	/* AVB1_PHY_INT */
	RCAR_GP_PIN(5, 16),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_phy_पूर्णांक_mux[] = अणु
	AVB1_PHY_INT_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_mdio_pins[] = अणु
	/* AVB1_MDC, AVB1_MDIO */
	RCAR_GP_PIN(5, 14), RCAR_GP_PIN(5, 13),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_mdio_mux[] = अणु
	AVB1_MDC_MARK, AVB1_MDIO_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_rgmii_pins[] = अणु
	/*
	 * AVB1_TX_CTL, AVB1_TXC, AVB1_TD0, AVB1_TD1, AVB1_TD2, AVB1_TD3,
	 * AVB1_RX_CTL, AVB1_RXC, AVB1_RD0, AVB1_RD1, AVB1_RD2, AVB1_RD3,
	 */
	RCAR_GP_PIN(5, 6), RCAR_GP_PIN(5, 7),
	RCAR_GP_PIN(5, 8), RCAR_GP_PIN(5, 9),
	RCAR_GP_PIN(5, 10), RCAR_GP_PIN(5, 11),
	RCAR_GP_PIN(5, 0), RCAR_GP_PIN(5, 1),
	RCAR_GP_PIN(5, 2), RCAR_GP_PIN(5, 3),
	RCAR_GP_PIN(5, 4), RCAR_GP_PIN(5, 5),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_rgmii_mux[] = अणु
	AVB1_TX_CTL_MARK, AVB1_TXC_MARK,
	AVB1_TD0_MARK, AVB1_TD1_MARK, AVB1_TD2_MARK, AVB1_TD3_MARK,
	AVB1_RX_CTL_MARK, AVB1_RXC_MARK,
	AVB1_RD0_MARK, AVB1_RD1_MARK, AVB1_RD2_MARK, AVB1_RD3_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_txcrefclk_pins[] = अणु
	/* AVB1_TXCREFCLK */
	RCAR_GP_PIN(5, 12),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_txcrefclk_mux[] = अणु
	AVB1_TXCREFCLK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_avtp_pps_pins[] = अणु
	/* AVB1_AVTP_PPS */
	RCAR_GP_PIN(5, 20),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_avtp_pps_mux[] = अणु
	AVB1_AVTP_PPS_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_avtp_capture_pins[] = अणु
	/* AVB1_AVTP_CAPTURE */
	RCAR_GP_PIN(5, 19),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_avtp_capture_mux[] = अणु
	AVB1_AVTP_CAPTURE_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_avtp_match_pins[] = अणु
	/* AVB1_AVTP_MATCH */
	RCAR_GP_PIN(5, 18),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb1_avtp_match_mux[] = अणु
	AVB1_AVTP_MATCH_MARK,
पूर्ण;

/* - AVB2 ------------------------------------------------ */
अटल स्थिर अचिन्हित पूर्णांक avb2_link_pins[] = अणु
	/* AVB2_LINK */
	RCAR_GP_PIN(6, 17),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_link_mux[] = अणु
	AVB2_LINK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_magic_pins[] = अणु
	/* AVB2_MAGIC */
	RCAR_GP_PIN(6, 15),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_magic_mux[] = अणु
	AVB2_MAGIC_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_phy_पूर्णांक_pins[] = अणु
	/* AVB2_PHY_INT */
	RCAR_GP_PIN(6, 16),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_phy_पूर्णांक_mux[] = अणु
	AVB2_PHY_INT_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_mdio_pins[] = अणु
	/* AVB2_MDC, AVB2_MDIO */
	RCAR_GP_PIN(6, 14), RCAR_GP_PIN(6, 13),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_mdio_mux[] = अणु
	AVB2_MDC_MARK, AVB2_MDIO_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_rgmii_pins[] = अणु
	/*
	 * AVB2_TX_CTL, AVB2_TXC, AVB2_TD0, AVB2_TD1, AVB2_TD2, AVB2_TD3,
	 * AVB2_RX_CTL, AVB2_RXC, AVB2_RD0, AVB2_RD1, AVB2_RD2, AVB2_RD3,
	 */
	RCAR_GP_PIN(6, 6), RCAR_GP_PIN(6, 7),
	RCAR_GP_PIN(6, 8), RCAR_GP_PIN(6, 9),
	RCAR_GP_PIN(6, 10), RCAR_GP_PIN(6, 11),
	RCAR_GP_PIN(6, 0), RCAR_GP_PIN(6, 1),
	RCAR_GP_PIN(6, 2), RCAR_GP_PIN(6, 3),
	RCAR_GP_PIN(6, 4), RCAR_GP_PIN(6, 5),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_rgmii_mux[] = अणु
	AVB2_TX_CTL_MARK, AVB2_TXC_MARK,
	AVB2_TD0_MARK, AVB2_TD1_MARK, AVB2_TD2_MARK, AVB2_TD3_MARK,
	AVB2_RX_CTL_MARK, AVB2_RXC_MARK,
	AVB2_RD0_MARK, AVB2_RD1_MARK, AVB2_RD2_MARK, AVB2_RD3_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_txcrefclk_pins[] = अणु
	/* AVB2_TXCREFCLK */
	RCAR_GP_PIN(6, 12),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_txcrefclk_mux[] = अणु
	AVB2_TXCREFCLK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_avtp_pps_pins[] = अणु
	/* AVB2_AVTP_PPS */
	RCAR_GP_PIN(6, 20),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_avtp_pps_mux[] = अणु
	AVB2_AVTP_PPS_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_avtp_capture_pins[] = अणु
	/* AVB2_AVTP_CAPTURE */
	RCAR_GP_PIN(6, 19),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_avtp_capture_mux[] = अणु
	AVB2_AVTP_CAPTURE_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_avtp_match_pins[] = अणु
	/* AVB2_AVTP_MATCH */
	RCAR_GP_PIN(6, 18),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb2_avtp_match_mux[] = अणु
	AVB2_AVTP_MATCH_MARK,
पूर्ण;

/* - AVB3 ------------------------------------------------ */
अटल स्थिर अचिन्हित पूर्णांक avb3_link_pins[] = अणु
	/* AVB3_LINK */
	RCAR_GP_PIN(7, 17),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_link_mux[] = अणु
	AVB3_LINK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_magic_pins[] = अणु
	/* AVB3_MAGIC */
	RCAR_GP_PIN(7, 15),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_magic_mux[] = अणु
	AVB3_MAGIC_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_phy_पूर्णांक_pins[] = अणु
	/* AVB3_PHY_INT */
	RCAR_GP_PIN(7, 16),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_phy_पूर्णांक_mux[] = अणु
	AVB3_PHY_INT_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_mdio_pins[] = अणु
	/* AVB3_MDC, AVB3_MDIO */
	RCAR_GP_PIN(7, 14), RCAR_GP_PIN(7, 13),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_mdio_mux[] = अणु
	AVB3_MDC_MARK, AVB3_MDIO_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_rgmii_pins[] = अणु
	/*
	 * AVB3_TX_CTL, AVB3_TXC, AVB3_TD0, AVB3_TD1, AVB3_TD2, AVB3_TD3,
	 * AVB3_RX_CTL, AVB3_RXC, AVB3_RD0, AVB3_RD1, AVB3_RD2, AVB3_RD3,
	 */
	RCAR_GP_PIN(7, 6), RCAR_GP_PIN(7, 7),
	RCAR_GP_PIN(7, 8), RCAR_GP_PIN(7, 9),
	RCAR_GP_PIN(7, 10), RCAR_GP_PIN(7, 11),
	RCAR_GP_PIN(7, 0), RCAR_GP_PIN(7, 1),
	RCAR_GP_PIN(7, 2), RCAR_GP_PIN(7, 3),
	RCAR_GP_PIN(7, 4), RCAR_GP_PIN(7, 5),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_rgmii_mux[] = अणु
	AVB3_TX_CTL_MARK, AVB3_TXC_MARK,
	AVB3_TD0_MARK, AVB3_TD1_MARK, AVB3_TD2_MARK, AVB3_TD3_MARK,
	AVB3_RX_CTL_MARK, AVB3_RXC_MARK,
	AVB3_RD0_MARK, AVB3_RD1_MARK, AVB3_RD2_MARK, AVB3_RD3_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_txcrefclk_pins[] = अणु
	/* AVB3_TXCREFCLK */
	RCAR_GP_PIN(7, 12),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_txcrefclk_mux[] = अणु
	AVB3_TXCREFCLK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_avtp_pps_pins[] = अणु
	/* AVB3_AVTP_PPS */
	RCAR_GP_PIN(7, 20),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_avtp_pps_mux[] = अणु
	AVB3_AVTP_PPS_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_avtp_capture_pins[] = अणु
	/* AVB3_AVTP_CAPTURE */
	RCAR_GP_PIN(7, 19),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_avtp_capture_mux[] = अणु
	AVB3_AVTP_CAPTURE_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_avtp_match_pins[] = अणु
	/* AVB3_AVTP_MATCH */
	RCAR_GP_PIN(7, 18),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb3_avtp_match_mux[] = अणु
	AVB3_AVTP_MATCH_MARK,
पूर्ण;

/* - AVB4 ------------------------------------------------ */
अटल स्थिर अचिन्हित पूर्णांक avb4_link_pins[] = अणु
	/* AVB4_LINK */
	RCAR_GP_PIN(8, 17),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_link_mux[] = अणु
	AVB4_LINK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_magic_pins[] = अणु
	/* AVB4_MAGIC */
	RCAR_GP_PIN(8, 15),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_magic_mux[] = अणु
	AVB4_MAGIC_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_phy_पूर्णांक_pins[] = अणु
	/* AVB4_PHY_INT */
	RCAR_GP_PIN(8, 16),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_phy_पूर्णांक_mux[] = अणु
	AVB4_PHY_INT_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_mdio_pins[] = अणु
	/* AVB4_MDC, AVB4_MDIO */
	RCAR_GP_PIN(8, 14), RCAR_GP_PIN(8, 13),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_mdio_mux[] = अणु
	AVB4_MDC_MARK, AVB4_MDIO_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_rgmii_pins[] = अणु
	/*
	 * AVB4_TX_CTL, AVB4_TXC, AVB4_TD0, AVB4_TD1, AVB4_TD2, AVB4_TD3,
	 * AVB4_RX_CTL, AVB4_RXC, AVB4_RD0, AVB4_RD1, AVB4_RD2, AVB4_RD3,
	 */
	RCAR_GP_PIN(8, 6), RCAR_GP_PIN(8, 7),
	RCAR_GP_PIN(8, 8), RCAR_GP_PIN(8, 9),
	RCAR_GP_PIN(8, 10), RCAR_GP_PIN(8, 11),
	RCAR_GP_PIN(8, 0), RCAR_GP_PIN(8, 1),
	RCAR_GP_PIN(8, 2), RCAR_GP_PIN(8, 3),
	RCAR_GP_PIN(8, 4), RCAR_GP_PIN(8, 5),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_rgmii_mux[] = अणु
	AVB4_TX_CTL_MARK, AVB4_TXC_MARK,
	AVB4_TD0_MARK, AVB4_TD1_MARK, AVB4_TD2_MARK, AVB4_TD3_MARK,
	AVB4_RX_CTL_MARK, AVB4_RXC_MARK,
	AVB4_RD0_MARK, AVB4_RD1_MARK, AVB4_RD2_MARK, AVB4_RD3_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_txcrefclk_pins[] = अणु
	/* AVB4_TXCREFCLK */
	RCAR_GP_PIN(8, 12),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_txcrefclk_mux[] = अणु
	AVB4_TXCREFCLK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_avtp_pps_pins[] = अणु
	/* AVB4_AVTP_PPS */
	RCAR_GP_PIN(8, 20),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_avtp_pps_mux[] = अणु
	AVB4_AVTP_PPS_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_avtp_capture_pins[] = अणु
	/* AVB4_AVTP_CAPTURE */
	RCAR_GP_PIN(8, 19),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_avtp_capture_mux[] = अणु
	AVB4_AVTP_CAPTURE_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_avtp_match_pins[] = अणु
	/* AVB4_AVTP_MATCH */
	RCAR_GP_PIN(8, 18),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb4_avtp_match_mux[] = अणु
	AVB4_AVTP_MATCH_MARK,
पूर्ण;

/* - AVB5 ------------------------------------------------ */
अटल स्थिर अचिन्हित पूर्णांक avb5_link_pins[] = अणु
	/* AVB5_LINK */
	RCAR_GP_PIN(9, 17),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_link_mux[] = अणु
	AVB5_LINK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_magic_pins[] = अणु
	/* AVB5_MAGIC */
	RCAR_GP_PIN(9, 15),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_magic_mux[] = अणु
	AVB5_MAGIC_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_phy_पूर्णांक_pins[] = अणु
	/* AVB5_PHY_INT */
	RCAR_GP_PIN(9, 16),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_phy_पूर्णांक_mux[] = अणु
	AVB5_PHY_INT_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_mdio_pins[] = अणु
	/* AVB5_MDC, AVB5_MDIO */
	RCAR_GP_PIN(9, 14), RCAR_GP_PIN(9, 13),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_mdio_mux[] = अणु
	AVB5_MDC_MARK, AVB5_MDIO_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_rgmii_pins[] = अणु
	/*
	 * AVB5_TX_CTL, AVB5_TXC, AVB5_TD0, AVB5_TD1, AVB5_TD2, AVB5_TD3,
	 * AVB5_RX_CTL, AVB5_RXC, AVB5_RD0, AVB5_RD1, AVB5_RD2, AVB5_RD3,
	 */
	RCAR_GP_PIN(9, 6), RCAR_GP_PIN(9, 7),
	RCAR_GP_PIN(9, 8), RCAR_GP_PIN(9, 9),
	RCAR_GP_PIN(9, 10), RCAR_GP_PIN(9, 11),
	RCAR_GP_PIN(9, 0), RCAR_GP_PIN(9, 1),
	RCAR_GP_PIN(9, 2), RCAR_GP_PIN(9, 3),
	RCAR_GP_PIN(9, 4), RCAR_GP_PIN(9, 5),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_rgmii_mux[] = अणु
	AVB5_TX_CTL_MARK, AVB5_TXC_MARK,
	AVB5_TD0_MARK, AVB5_TD1_MARK, AVB5_TD2_MARK, AVB5_TD3_MARK,
	AVB5_RX_CTL_MARK, AVB5_RXC_MARK,
	AVB5_RD0_MARK, AVB5_RD1_MARK, AVB5_RD2_MARK, AVB5_RD3_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_txcrefclk_pins[] = अणु
	/* AVB5_TXCREFCLK */
	RCAR_GP_PIN(9, 12),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_txcrefclk_mux[] = अणु
	AVB5_TXCREFCLK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_avtp_pps_pins[] = अणु
	/* AVB5_AVTP_PPS */
	RCAR_GP_PIN(9, 20),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_avtp_pps_mux[] = अणु
	AVB5_AVTP_PPS_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_avtp_capture_pins[] = अणु
	/* AVB5_AVTP_CAPTURE */
	RCAR_GP_PIN(9, 19),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_avtp_capture_mux[] = अणु
	AVB5_AVTP_CAPTURE_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_avtp_match_pins[] = अणु
	/* AVB5_AVTP_MATCH */
	RCAR_GP_PIN(9, 18),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक avb5_avtp_match_mux[] = अणु
	AVB5_AVTP_MATCH_MARK,
पूर्ण;

/* - CANFD0 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक canfd0_data_pins[] = अणु
	/* CANFD0_TX, CANFD0_RX */
	RCAR_GP_PIN(3, 1), RCAR_GP_PIN(3, 2),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक canfd0_data_mux[] = अणु
	CANFD0_TX_MARK, CANFD0_RX_MARK,
पूर्ण;

/* - CANFD1 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक canfd1_data_pins[] = अणु
	/* CANFD1_TX, CANFD1_RX */
	RCAR_GP_PIN(3, 3), RCAR_GP_PIN(3, 4),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक canfd1_data_mux[] = अणु
	CANFD1_TX_MARK, CANFD1_RX_MARK,
पूर्ण;

/* - CANFD2 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक canfd2_data_pins[] = अणु
	/* CANFD2_TX, CANFD2_RX */
	RCAR_GP_PIN(3, 5), RCAR_GP_PIN(3, 6),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक canfd2_data_mux[] = अणु
	CANFD2_TX_MARK, CANFD2_RX_MARK,
पूर्ण;

/* - CANFD3 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक canfd3_data_pins[] = अणु
	/* CANFD3_TX, CANFD3_RX */
	RCAR_GP_PIN(3, 7), RCAR_GP_PIN(3, 8),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक canfd3_data_mux[] = अणु
	CANFD3_TX_MARK, CANFD3_RX_MARK,
पूर्ण;

/* - CANFD4 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक canfd4_data_pins[] = अणु
	/* CANFD4_TX, CANFD4_RX */
	RCAR_GP_PIN(3, 9), RCAR_GP_PIN(3, 10),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक canfd4_data_mux[] = अणु
	CANFD4_TX_MARK, CANFD4_RX_MARK,
पूर्ण;

/* - CANFD5 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक canfd5_data_pins[] = अणु
	/* CANFD5_TX, CANFD5_RX */
	RCAR_GP_PIN(3, 11), RCAR_GP_PIN(3, 12),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक canfd5_data_mux[] = अणु
	CANFD5_TX_MARK, CANFD5_RX_MARK,
पूर्ण;

/* - CANFD6 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक canfd6_data_pins[] = अणु
	/* CANFD6_TX, CANFD6_RX */
	RCAR_GP_PIN(3, 13), RCAR_GP_PIN(3, 14),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक canfd6_data_mux[] = अणु
	CANFD6_TX_MARK, CANFD6_RX_MARK,
पूर्ण;

/* - CANFD7 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक canfd7_data_pins[] = अणु
	/* CANFD7_TX, CANFD7_RX */
	RCAR_GP_PIN(3, 15), RCAR_GP_PIN(3, 16),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक canfd7_data_mux[] = अणु
	CANFD7_TX_MARK, CANFD7_RX_MARK,
पूर्ण;

/* - CANFD Clock ------------------------------------------------------------ */
अटल स्थिर अचिन्हित पूर्णांक can_clk_pins[] = अणु
	/* CAN_CLK */
	RCAR_GP_PIN(3, 0),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक can_clk_mux[] = अणु
	CAN_CLK_MARK,
पूर्ण;

/* - DU --------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक du_rgb888_pins[] = अणु
	/* DU_DR[7:2], DU_DG[7:2], DU_DB[7:2] */
	RCAR_GP_PIN(1, 11), RCAR_GP_PIN(1, 10), RCAR_GP_PIN(1, 9),
	RCAR_GP_PIN(1, 8), RCAR_GP_PIN(1, 7), RCAR_GP_PIN(1, 6),
	RCAR_GP_PIN(1, 17), RCAR_GP_PIN(1, 16), RCAR_GP_PIN(1, 15),
	RCAR_GP_PIN(1, 14), RCAR_GP_PIN(1, 13), RCAR_GP_PIN(1, 12),
	RCAR_GP_PIN(1, 23), RCAR_GP_PIN(1, 22), RCAR_GP_PIN(1, 21),
	RCAR_GP_PIN(1, 20), RCAR_GP_PIN(1, 19), RCAR_GP_PIN(1, 18),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक du_rgb888_mux[] = अणु
	DU_DR7_MARK, DU_DR6_MARK, DU_DR5_MARK,
	DU_DR4_MARK, DU_DR3_MARK, DU_DR2_MARK,
	DU_DG7_MARK, DU_DG6_MARK, DU_DG5_MARK,
	DU_DG4_MARK, DU_DG3_MARK, DU_DG2_MARK,
	DU_DB7_MARK, DU_DB6_MARK, DU_DB5_MARK,
	DU_DB4_MARK, DU_DB3_MARK, DU_DB2_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक du_clk_out_pins[] = अणु
	/* DU_DOTCLKOUT */
	RCAR_GP_PIN(1, 24),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक du_clk_out_mux[] = अणु
	DU_DOTCLKOUT_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक du_sync_pins[] = अणु
	/* DU_HSYNC, DU_VSYNC */
	RCAR_GP_PIN(1, 25), RCAR_GP_PIN(1, 26),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक du_sync_mux[] = अणु
	DU_HSYNC_MARK, DU_VSYNC_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक du_oddf_pins[] = अणु
	/* DU_EXODDF/DU_ODDF/DISP/CDE */
	RCAR_GP_PIN(1, 27),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक du_oddf_mux[] = अणु
	DU_ODDF_DISP_CDE_MARK,
पूर्ण;

/* - HSCIF0 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक hscअगर0_data_pins[] = अणु
	/* HRX0, HTX0 */
	RCAR_GP_PIN(1, 1), RCAR_GP_PIN(1, 5),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर0_data_mux[] = अणु
	HRX0_MARK, HTX0_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर0_clk_pins[] = अणु
	/* HSCK0 */
	RCAR_GP_PIN(1, 2),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर0_clk_mux[] = अणु
	HSCK0_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर0_ctrl_pins[] = अणु
	/* HRTS0#, HCTS0# */
	RCAR_GP_PIN(1, 3), RCAR_GP_PIN(1, 4),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर0_ctrl_mux[] = अणु
	HRTS0_N_MARK, HCTS0_N_MARK,
पूर्ण;

/* - HSCIF1 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक hscअगर1_data_pins[] = अणु
	/* HRX1, HTX1 */
	RCAR_GP_PIN(1, 21), RCAR_GP_PIN(1, 22),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर1_data_mux[] = अणु
	HRX1_MARK, HTX1_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर1_clk_pins[] = अणु
	/* HSCK1 */
	RCAR_GP_PIN(1, 18),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर1_clk_mux[] = अणु
	HSCK1_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर1_ctrl_pins[] = अणु
	/* HRTS1#, HCTS1# */
	RCAR_GP_PIN(1, 20), RCAR_GP_PIN(1, 19),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर1_ctrl_mux[] = अणु
	HRTS1_N_MARK, HCTS1_N_MARK,
पूर्ण;

/* - HSCIF2 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक hscअगर2_data_pins[] = अणु
	/* HRX2, HTX2 */
	RCAR_GP_PIN(2, 8), RCAR_GP_PIN(2, 9),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर2_data_mux[] = अणु
	HRX2_MARK, HTX2_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर2_clk_pins[] = अणु
	/* HSCK2 */
	RCAR_GP_PIN(2, 5),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर2_clk_mux[] = अणु
	HSCK2_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर2_ctrl_pins[] = अणु
	/* HRTS2#, HCTS2# */
	RCAR_GP_PIN(2, 7), RCAR_GP_PIN(2, 6),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर2_ctrl_mux[] = अणु
	HRTS2_N_MARK, HCTS2_N_MARK,
पूर्ण;

/* - HSCIF3 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक hscअगर3_data_pins[] = अणु
	/* HRX3, HTX3 */
	RCAR_GP_PIN(1, 13), RCAR_GP_PIN(1, 17),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर3_data_mux[] = अणु
	HRX3_MARK, HTX3_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर3_clk_pins[] = अणु
	/* HSCK3 */
	RCAR_GP_PIN(1, 14),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर3_clk_mux[] = अणु
	HSCK3_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर3_ctrl_pins[] = अणु
	/* HRTS3#, HCTS3# */
	RCAR_GP_PIN(1, 15), RCAR_GP_PIN(1, 16),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक hscअगर3_ctrl_mux[] = अणु
	HRTS3_N_MARK, HCTS3_N_MARK,
पूर्ण;

/* - I2C0 ------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक i2c0_pins[] = अणु
	/* SDA0, SCL0 */
	RCAR_GP_PIN(2, 3), RCAR_GP_PIN(2, 2),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c0_mux[] = अणु
	SDA0_MARK, SCL0_MARK,
पूर्ण;

/* - I2C1 ------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक i2c1_pins[] = अणु
	/* SDA1, SCL1 */
	RCAR_GP_PIN(2, 5), RCAR_GP_PIN(2, 4),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c1_mux[] = अणु
	SDA1_MARK, SCL1_MARK,
पूर्ण;

/* - I2C2 ------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक i2c2_pins[] = अणु
	/* SDA2, SCL2 */
	RCAR_GP_PIN(2, 7), RCAR_GP_PIN(2, 6),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c2_mux[] = अणु
	SDA2_MARK, SCL2_MARK,
पूर्ण;

/* - I2C3 ------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक i2c3_pins[] = अणु
	/* SDA3, SCL3 */
	RCAR_GP_PIN(2, 9), RCAR_GP_PIN(2, 8),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c3_mux[] = अणु
	SDA3_MARK, SCL3_MARK,
पूर्ण;

/* - I2C4 ------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक i2c4_pins[] = अणु
	/* SDA4, SCL4 */
	RCAR_GP_PIN(2, 11), RCAR_GP_PIN(2, 10),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c4_mux[] = अणु
	SDA4_MARK, SCL4_MARK,
पूर्ण;

/* - I2C5 ------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक i2c5_pins[] = अणु
	/* SDA5, SCL5 */
	RCAR_GP_PIN(2, 13), RCAR_GP_PIN(2, 12),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c5_mux[] = अणु
	SDA5_MARK, SCL5_MARK,
पूर्ण;

/* - I2C6 ------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक i2c6_pins[] = अणु
	/* SDA6, SCL6 */
	RCAR_GP_PIN(2, 15), RCAR_GP_PIN(2, 14),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक i2c6_mux[] = अणु
	SDA6_MARK, SCL6_MARK,
पूर्ण;

/* - INTC-EX ---------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक पूर्णांकc_ex_irq0_pins[] = अणु
	/* IRQ0 */
	RCAR_GP_PIN(1, 24),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पूर्णांकc_ex_irq0_mux[] = अणु
	IRQ0_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पूर्णांकc_ex_irq1_pins[] = अणु
	/* IRQ1 */
	RCAR_GP_PIN(1, 25),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पूर्णांकc_ex_irq1_mux[] = अणु
	IRQ1_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पूर्णांकc_ex_irq2_pins[] = अणु
	/* IRQ2 */
	RCAR_GP_PIN(1, 26),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पूर्णांकc_ex_irq2_mux[] = अणु
	IRQ2_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पूर्णांकc_ex_irq3_pins[] = अणु
	/* IRQ3 */
	RCAR_GP_PIN(1, 27),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पूर्णांकc_ex_irq3_mux[] = अणु
	IRQ3_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पूर्णांकc_ex_irq4_pins[] = अणु
	/* IRQ4 */
	RCAR_GP_PIN(2, 14),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पूर्णांकc_ex_irq4_mux[] = अणु
	IRQ4_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पूर्णांकc_ex_irq5_pins[] = अणु
	/* IRQ5 */
	RCAR_GP_PIN(2, 15),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पूर्णांकc_ex_irq5_mux[] = अणु
	IRQ5_MARK,
पूर्ण;

/* - MMC -------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक mmc_data1_pins[] = अणु
	/* MMC_SD_D0 */
	RCAR_GP_PIN(0, 19),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mmc_data1_mux[] = अणु
	MMC_SD_D0_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mmc_data4_pins[] = अणु
	/* MMC_SD_D[0:3] */
	RCAR_GP_PIN(0, 19), RCAR_GP_PIN(0, 20),
	RCAR_GP_PIN(0, 21), RCAR_GP_PIN(0, 22),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mmc_data4_mux[] = अणु
	MMC_SD_D0_MARK, MMC_SD_D1_MARK,
	MMC_SD_D2_MARK, MMC_SD_D3_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mmc_data8_pins[] = अणु
	/* MMC_SD_D[0:3], MMC_D[4:7] */
	RCAR_GP_PIN(0, 19), RCAR_GP_PIN(0, 20),
	RCAR_GP_PIN(0, 21), RCAR_GP_PIN(0, 22),
	RCAR_GP_PIN(0, 24), RCAR_GP_PIN(0, 25),
	RCAR_GP_PIN(0, 26), RCAR_GP_PIN(0, 27),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mmc_data8_mux[] = अणु
	MMC_SD_D0_MARK, MMC_SD_D1_MARK,
	MMC_SD_D2_MARK, MMC_SD_D3_MARK,
	MMC_D4_MARK, MMC_D5_MARK,
	MMC_D6_MARK, MMC_D7_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mmc_ctrl_pins[] = अणु
	/* MMC_SD_CLK, MMC_SD_CMD */
	RCAR_GP_PIN(0, 23), RCAR_GP_PIN(0, 18),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mmc_ctrl_mux[] = अणु
	MMC_SD_CLK_MARK, MMC_SD_CMD_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mmc_cd_pins[] = अणु
	/* SD_CD */
	RCAR_GP_PIN(0, 16),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mmc_cd_mux[] = अणु
	SD_CD_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mmc_wp_pins[] = अणु
	/* SD_WP */
	RCAR_GP_PIN(0, 15),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mmc_wp_mux[] = अणु
	SD_WP_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mmc_ds_pins[] = अणु
	/* MMC_DS */
	RCAR_GP_PIN(0, 17),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक mmc_ds_mux[] = अणु
	MMC_DS_MARK,
पूर्ण;

/* - MSIOF0 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक msiof0_clk_pins[] = अणु
	/* MSIOF0_SCK */
	RCAR_GP_PIN(1, 8),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof0_clk_mux[] = अणु
	MSIOF0_SCK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof0_sync_pins[] = अणु
	/* MSIOF0_SYNC */
	RCAR_GP_PIN(1, 9),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof0_sync_mux[] = अणु
	MSIOF0_SYNC_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof0_ss1_pins[] = अणु
	/* MSIOF0_SS1 */
	RCAR_GP_PIN(1, 10),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof0_ss1_mux[] = अणु
	MSIOF0_SS1_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof0_ss2_pins[] = अणु
	/* MSIOF0_SS2 */
	RCAR_GP_PIN(1, 11),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof0_ss2_mux[] = अणु
	MSIOF0_SS2_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof0_txd_pins[] = अणु
	/* MSIOF0_TXD */
	RCAR_GP_PIN(1, 7),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof0_txd_mux[] = अणु
	MSIOF0_TXD_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof0_rxd_pins[] = अणु
	/* MSIOF0_RXD */
	RCAR_GP_PIN(1, 6),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof0_rxd_mux[] = अणु
	MSIOF0_RXD_MARK,
पूर्ण;

/* - MSIOF1 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक msiof1_clk_pins[] = अणु
	/* MSIOF1_SCK */
	RCAR_GP_PIN(1, 14),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof1_clk_mux[] = अणु
	MSIOF1_SCK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof1_sync_pins[] = अणु
	/* MSIOF1_SYNC */
	RCAR_GP_PIN(1, 15),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof1_sync_mux[] = अणु
	MSIOF1_SYNC_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof1_ss1_pins[] = अणु
	/* MSIOF1_SS1 */
	RCAR_GP_PIN(1, 16),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof1_ss1_mux[] = अणु
	MSIOF1_SS1_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof1_ss2_pins[] = अणु
	/* MSIOF1_SS2 */
	RCAR_GP_PIN(1, 17),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof1_ss2_mux[] = अणु
	MSIOF1_SS2_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof1_txd_pins[] = अणु
	/* MSIOF1_TXD */
	RCAR_GP_PIN(1, 13),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof1_txd_mux[] = अणु
	MSIOF1_TXD_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof1_rxd_pins[] = अणु
	/* MSIOF1_RXD */
	RCAR_GP_PIN(1, 12),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof1_rxd_mux[] = अणु
	MSIOF1_RXD_MARK,
पूर्ण;

/* - MSIOF2 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक msiof2_clk_pins[] = अणु
	/* MSIOF2_SCK */
	RCAR_GP_PIN(1, 20),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof2_clk_mux[] = अणु
	MSIOF2_SCK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof2_sync_pins[] = अणु
	/* MSIOF2_SYNC */
	RCAR_GP_PIN(1, 21),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof2_sync_mux[] = अणु
	MSIOF2_SYNC_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof2_ss1_pins[] = अणु
	/* MSIOF2_SS1 */
	RCAR_GP_PIN(1, 22),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof2_ss1_mux[] = अणु
	MSIOF2_SS1_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof2_ss2_pins[] = अणु
	/* MSIOF2_SS2 */
	RCAR_GP_PIN(1, 23),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof2_ss2_mux[] = अणु
	MSIOF2_SS2_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof2_txd_pins[] = अणु
	/* MSIOF2_TXD */
	RCAR_GP_PIN(1, 19),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof2_txd_mux[] = अणु
	MSIOF2_TXD_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof2_rxd_pins[] = अणु
	/* MSIOF2_RXD */
	RCAR_GP_PIN(1, 18),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof2_rxd_mux[] = अणु
	MSIOF2_RXD_MARK,
पूर्ण;

/* - MSIOF3 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक msiof3_clk_pins[] = अणु
	/* MSIOF3_SCK */
	RCAR_GP_PIN(2, 20),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof3_clk_mux[] = अणु
	MSIOF3_SCK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof3_sync_pins[] = अणु
	/* MSIOF3_SYNC */
	RCAR_GP_PIN(2, 21),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof3_sync_mux[] = अणु
	MSIOF3_SYNC_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof3_ss1_pins[] = अणु
	/* MSIOF3_SS1 */
	RCAR_GP_PIN(2, 16),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof3_ss1_mux[] = अणु
	MSIOF3_SS1_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof3_ss2_pins[] = अणु
	/* MSIOF3_SS2 */
	RCAR_GP_PIN(2, 17),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof3_ss2_mux[] = अणु
	MSIOF3_SS2_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof3_txd_pins[] = अणु
	/* MSIOF3_TXD */
	RCAR_GP_PIN(2, 19),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof3_txd_mux[] = अणु
	MSIOF3_TXD_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof3_rxd_pins[] = अणु
	/* MSIOF3_RXD */
	RCAR_GP_PIN(2, 18),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof3_rxd_mux[] = अणु
	MSIOF3_RXD_MARK,
पूर्ण;

/* - MSIOF4 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक msiof4_clk_pins[] = अणु
	/* MSIOF4_SCK */
	RCAR_GP_PIN(2, 6),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof4_clk_mux[] = अणु
	MSIOF4_SCK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof4_sync_pins[] = अणु
	/* MSIOF4_SYNC */
	RCAR_GP_PIN(2, 7),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof4_sync_mux[] = अणु
	MSIOF4_SYNC_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof4_ss1_pins[] = अणु
	/* MSIOF4_SS1 */
	RCAR_GP_PIN(2, 8),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof4_ss1_mux[] = अणु
	MSIOF4_SS1_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof4_ss2_pins[] = अणु
	/* MSIOF4_SS2 */
	RCAR_GP_PIN(2, 9),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof4_ss2_mux[] = अणु
	MSIOF4_SS2_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof4_txd_pins[] = अणु
	/* MSIOF4_TXD */
	RCAR_GP_PIN(2, 5),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof4_txd_mux[] = अणु
	MSIOF4_TXD_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof4_rxd_pins[] = अणु
	/* MSIOF4_RXD */
	RCAR_GP_PIN(2, 4),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof4_rxd_mux[] = अणु
	MSIOF4_RXD_MARK,
पूर्ण;

/* - MSIOF5 ----------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक msiof5_clk_pins[] = अणु
	/* MSIOF5_SCK */
	RCAR_GP_PIN(2, 12),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof5_clk_mux[] = अणु
	MSIOF5_SCK_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof5_sync_pins[] = अणु
	/* MSIOF5_SYNC */
	RCAR_GP_PIN(2, 13),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof5_sync_mux[] = अणु
	MSIOF5_SYNC_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof5_ss1_pins[] = अणु
	/* MSIOF5_SS1 */
	RCAR_GP_PIN(2, 14),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof5_ss1_mux[] = अणु
	MSIOF5_SS1_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof5_ss2_pins[] = अणु
	/* MSIOF5_SS2 */
	RCAR_GP_PIN(2, 15),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof5_ss2_mux[] = अणु
	MSIOF5_SS2_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof5_txd_pins[] = अणु
	/* MSIOF5_TXD */
	RCAR_GP_PIN(2, 11),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof5_txd_mux[] = अणु
	MSIOF5_TXD_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof5_rxd_pins[] = अणु
	/* MSIOF5_RXD */
	RCAR_GP_PIN(2, 10),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक msiof5_rxd_mux[] = अणु
	MSIOF5_RXD_MARK,
पूर्ण;

/* - PWM0 ------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक pwm0_pins[] = अणु
	/* PWM0 */
	RCAR_GP_PIN(3, 5),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm0_mux[] = अणु
	PWM0_MARK,
पूर्ण;

/* - PWM1 ------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक pwm1_pins[] = अणु
	/* PWM1 */
	RCAR_GP_PIN(3, 6),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm1_mux[] = अणु
	PWM1_MARK,
पूर्ण;

/* - PWM2 ------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक pwm2_pins[] = अणु
	/* PWM2 */
	RCAR_GP_PIN(3, 7),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm2_mux[] = अणु
	PWM2_MARK,
पूर्ण;

/* - PWM3 ------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक pwm3_pins[] = अणु
	/* PWM3 */
	RCAR_GP_PIN(3, 8),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm3_mux[] = अणु
	PWM3_MARK,
पूर्ण;

/* - PWM4 ------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक pwm4_pins[] = अणु
	/* PWM4 */
	RCAR_GP_PIN(3, 9),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक pwm4_mux[] = अणु
	PWM4_MARK,
पूर्ण;

/* - QSPI0 ------------------------------------------------------------------ */
अटल स्थिर अचिन्हित पूर्णांक qspi0_ctrl_pins[] = अणु
	/* SPCLK, SSL */
	RCAR_GP_PIN(0, 0), RCAR_GP_PIN(0, 5),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qspi0_ctrl_mux[] = अणु
	QSPI0_SPCLK_MARK, QSPI0_SSL_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qspi0_data2_pins[] = अणु
	/* MOSI_IO0, MISO_IO1 */
	RCAR_GP_PIN(0, 1), RCAR_GP_PIN(0, 2),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qspi0_data2_mux[] = अणु
	QSPI0_MOSI_IO0_MARK, QSPI0_MISO_IO1_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qspi0_data4_pins[] = अणु
	/* MOSI_IO0, MISO_IO1, IO2, IO3 */
	RCAR_GP_PIN(0, 1), RCAR_GP_PIN(0, 2),
	RCAR_GP_PIN(0, 3), RCAR_GP_PIN(0, 4),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qspi0_data4_mux[] = अणु
	QSPI0_MOSI_IO0_MARK, QSPI0_MISO_IO1_MARK,
	QSPI0_IO2_MARK, QSPI0_IO3_MARK
पूर्ण;

/* - QSPI1 ------------------------------------------------------------------ */
अटल स्थिर अचिन्हित पूर्णांक qspi1_ctrl_pins[] = अणु
	/* SPCLK, SSL */
	RCAR_GP_PIN(0, 6), RCAR_GP_PIN(0, 11),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qspi1_ctrl_mux[] = अणु
	QSPI1_SPCLK_MARK, QSPI1_SSL_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qspi1_data2_pins[] = अणु
	/* MOSI_IO0, MISO_IO1 */
	RCAR_GP_PIN(0, 7), RCAR_GP_PIN(0, 8),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qspi1_data2_mux[] = अणु
	QSPI1_MOSI_IO0_MARK, QSPI1_MISO_IO1_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qspi1_data4_pins[] = अणु
	/* MOSI_IO0, MISO_IO1, IO2, IO3 */
	RCAR_GP_PIN(0, 7), RCAR_GP_PIN(0, 8),
	RCAR_GP_PIN(0, 9), RCAR_GP_PIN(0, 10),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक qspi1_data4_mux[] = अणु
	QSPI1_MOSI_IO0_MARK, QSPI1_MISO_IO1_MARK,
	QSPI1_IO2_MARK, QSPI1_IO3_MARK
पूर्ण;

/* - SCIF0 ------------------------------------------------------------------ */
अटल स्थिर अचिन्हित पूर्णांक scअगर0_data_pins[] = अणु
	/* RX0, TX0 */
	RCAR_GP_PIN(1, 1), RCAR_GP_PIN(1, 5),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर0_data_mux[] = अणु
	RX0_MARK, TX0_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर0_clk_pins[] = अणु
	/* SCK0 */
	RCAR_GP_PIN(1, 2),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर0_clk_mux[] = अणु
	SCK0_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर0_ctrl_pins[] = अणु
	/* RTS0#, CTS0# */
	RCAR_GP_PIN(1, 3), RCAR_GP_PIN(1, 4),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर0_ctrl_mux[] = अणु
	RTS0_N_MARK, CTS0_N_MARK,
पूर्ण;

/* - SCIF1 ------------------------------------------------------------------ */
अटल स्थिर अचिन्हित पूर्णांक scअगर1_data_a_pins[] = अणु
	/* RX, TX */
	RCAR_GP_PIN(1, 21), RCAR_GP_PIN(1, 22),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर1_data_a_mux[] = अणु
	RX1_A_MARK, TX1_A_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर1_data_b_pins[] = अणु
	/* RX, TX */
	RCAR_GP_PIN(3, 2), RCAR_GP_PIN(3, 1),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर1_data_b_mux[] = अणु
	RX1_B_MARK, TX1_B_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर1_clk_pins[] = अणु
	/* SCK1 */
	RCAR_GP_PIN(1, 18),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर1_clk_mux[] = अणु
	SCK1_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर1_ctrl_pins[] = अणु
	/* RTS1#, CTS1# */
	RCAR_GP_PIN(1, 20), RCAR_GP_PIN(1, 19),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर1_ctrl_mux[] = अणु
	RTS1_N_MARK, CTS1_N_MARK,
पूर्ण;

/* - SCIF3 ------------------------------------------------------------------ */
अटल स्थिर अचिन्हित पूर्णांक scअगर3_data_pins[] = अणु
	/* RX3, TX3 */
	RCAR_GP_PIN(1, 16), RCAR_GP_PIN(1, 17),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर3_data_mux[] = अणु
	RX3_MARK, TX3_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर3_clk_pins[] = अणु
	/* SCK3 */
	RCAR_GP_PIN(1, 13),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर3_clk_mux[] = अणु
	SCK3_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर3_ctrl_pins[] = अणु
	/* RTS3#, CTS3# */
	RCAR_GP_PIN(1, 15), RCAR_GP_PIN(1, 14),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर3_ctrl_mux[] = अणु
	RTS3_N_MARK, CTS3_N_MARK,
पूर्ण;

/* - SCIF4 ------------------------------------------------------------------ */
अटल स्थिर अचिन्हित पूर्णांक scअगर4_data_pins[] = अणु
	/* RX4, TX4 */
	RCAR_GP_PIN(2, 8), RCAR_GP_PIN(2, 9),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर4_data_mux[] = अणु
	RX4_MARK, TX4_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर4_clk_pins[] = अणु
	/* SCK4 */
	RCAR_GP_PIN(2, 5),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर4_clk_mux[] = अणु
	SCK4_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर4_ctrl_pins[] = अणु
	/* RTS4#, CTS4# */
	RCAR_GP_PIN(2, 7), RCAR_GP_PIN(2, 6),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर4_ctrl_mux[] = अणु
	RTS4_N_MARK, CTS4_N_MARK,
पूर्ण;

/* - SCIF Clock ------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक scअगर_clk_pins[] = अणु
	/* SCIF_CLK */
	RCAR_GP_PIN(1, 0),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक scअगर_clk_mux[] = अणु
	SCIF_CLK_MARK,
पूर्ण;

/* - TMU -------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक पंचांगu_tclk1_a_pins[] = अणु
	/* TCLK1 */
	RCAR_GP_PIN(2, 23),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पंचांगu_tclk1_a_mux[] = अणु
	TCLK1_A_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पंचांगu_tclk1_b_pins[] = अणु
	/* TCLK1 */
	RCAR_GP_PIN(1, 23),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पंचांगu_tclk1_b_mux[] = अणु
	TCLK1_B_MARK,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक पंचांगu_tclk2_a_pins[] = अणु
	/* TCLK2 */
	RCAR_GP_PIN(2, 24),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पंचांगu_tclk2_a_mux[] = अणु
	TCLK2_A_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पंचांगu_tclk2_b_pins[] = अणु
	/* TCLK2 */
	RCAR_GP_PIN(2, 10),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पंचांगu_tclk2_b_mux[] = अणु
	TCLK2_B_MARK,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक पंचांगu_tclk3_pins[] = अणु
	/* TCLK3 */
	RCAR_GP_PIN(2, 11),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पंचांगu_tclk3_mux[] = अणु
	TCLK3_MARK,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक पंचांगu_tclk4_pins[] = अणु
	/* TCLK4 */
	RCAR_GP_PIN(2, 12),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक पंचांगu_tclk4_mux[] = अणु
	TCLK4_MARK,
पूर्ण;

/* - TPU ------------------------------------------------------------------- */
अटल स्थिर अचिन्हित पूर्णांक tpu_to0_pins[] = अणु
	/* TPU0TO0 */
	RCAR_GP_PIN(2, 21),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tpu_to0_mux[] = अणु
	TPU0TO0_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tpu_to1_pins[] = अणु
	/* TPU0TO1 */
	RCAR_GP_PIN(2, 22),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tpu_to1_mux[] = अणु
	TPU0TO1_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tpu_to2_pins[] = अणु
	/* TPU0TO2 */
	RCAR_GP_PIN(3, 5),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tpu_to2_mux[] = अणु
	TPU0TO2_MARK,
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tpu_to3_pins[] = अणु
	/* TPU0TO3 */
	RCAR_GP_PIN(3, 6),
पूर्ण;
अटल स्थिर अचिन्हित पूर्णांक tpu_to3_mux[] = अणु
	TPU0TO3_MARK,
पूर्ण;

अटल स्थिर काष्ठा sh_pfc_pin_group pinmux_groups[] = अणु
	SH_PFC_PIN_GROUP(avb0_link),
	SH_PFC_PIN_GROUP(avb0_magic),
	SH_PFC_PIN_GROUP(avb0_phy_पूर्णांक),
	SH_PFC_PIN_GROUP(avb0_mdio),
	SH_PFC_PIN_GROUP(avb0_rgmii),
	SH_PFC_PIN_GROUP(avb0_txcrefclk),
	SH_PFC_PIN_GROUP(avb0_avtp_pps),
	SH_PFC_PIN_GROUP(avb0_avtp_capture),
	SH_PFC_PIN_GROUP(avb0_avtp_match),

	SH_PFC_PIN_GROUP(avb1_link),
	SH_PFC_PIN_GROUP(avb1_magic),
	SH_PFC_PIN_GROUP(avb1_phy_पूर्णांक),
	SH_PFC_PIN_GROUP(avb1_mdio),
	SH_PFC_PIN_GROUP(avb1_rgmii),
	SH_PFC_PIN_GROUP(avb1_txcrefclk),
	SH_PFC_PIN_GROUP(avb1_avtp_pps),
	SH_PFC_PIN_GROUP(avb1_avtp_capture),
	SH_PFC_PIN_GROUP(avb1_avtp_match),

	SH_PFC_PIN_GROUP(avb2_link),
	SH_PFC_PIN_GROUP(avb2_magic),
	SH_PFC_PIN_GROUP(avb2_phy_पूर्णांक),
	SH_PFC_PIN_GROUP(avb2_mdio),
	SH_PFC_PIN_GROUP(avb2_rgmii),
	SH_PFC_PIN_GROUP(avb2_txcrefclk),
	SH_PFC_PIN_GROUP(avb2_avtp_pps),
	SH_PFC_PIN_GROUP(avb2_avtp_capture),
	SH_PFC_PIN_GROUP(avb2_avtp_match),

	SH_PFC_PIN_GROUP(avb3_link),
	SH_PFC_PIN_GROUP(avb3_magic),
	SH_PFC_PIN_GROUP(avb3_phy_पूर्णांक),
	SH_PFC_PIN_GROUP(avb3_mdio),
	SH_PFC_PIN_GROUP(avb3_rgmii),
	SH_PFC_PIN_GROUP(avb3_txcrefclk),
	SH_PFC_PIN_GROUP(avb3_avtp_pps),
	SH_PFC_PIN_GROUP(avb3_avtp_capture),
	SH_PFC_PIN_GROUP(avb3_avtp_match),

	SH_PFC_PIN_GROUP(avb4_link),
	SH_PFC_PIN_GROUP(avb4_magic),
	SH_PFC_PIN_GROUP(avb4_phy_पूर्णांक),
	SH_PFC_PIN_GROUP(avb4_mdio),
	SH_PFC_PIN_GROUP(avb4_rgmii),
	SH_PFC_PIN_GROUP(avb4_txcrefclk),
	SH_PFC_PIN_GROUP(avb4_avtp_pps),
	SH_PFC_PIN_GROUP(avb4_avtp_capture),
	SH_PFC_PIN_GROUP(avb4_avtp_match),

	SH_PFC_PIN_GROUP(avb5_link),
	SH_PFC_PIN_GROUP(avb5_magic),
	SH_PFC_PIN_GROUP(avb5_phy_पूर्णांक),
	SH_PFC_PIN_GROUP(avb5_mdio),
	SH_PFC_PIN_GROUP(avb5_rgmii),
	SH_PFC_PIN_GROUP(avb5_txcrefclk),
	SH_PFC_PIN_GROUP(avb5_avtp_pps),
	SH_PFC_PIN_GROUP(avb5_avtp_capture),
	SH_PFC_PIN_GROUP(avb5_avtp_match),

	SH_PFC_PIN_GROUP(canfd0_data),
	SH_PFC_PIN_GROUP(canfd1_data),
	SH_PFC_PIN_GROUP(canfd2_data),
	SH_PFC_PIN_GROUP(canfd3_data),
	SH_PFC_PIN_GROUP(canfd4_data),
	SH_PFC_PIN_GROUP(canfd5_data),
	SH_PFC_PIN_GROUP(canfd6_data),
	SH_PFC_PIN_GROUP(canfd7_data),
	SH_PFC_PIN_GROUP(can_clk),

	SH_PFC_PIN_GROUP(du_rgb888),
	SH_PFC_PIN_GROUP(du_clk_out),
	SH_PFC_PIN_GROUP(du_sync),
	SH_PFC_PIN_GROUP(du_oddf),

	SH_PFC_PIN_GROUP(hscअगर0_data),
	SH_PFC_PIN_GROUP(hscअगर0_clk),
	SH_PFC_PIN_GROUP(hscअगर0_ctrl),
	SH_PFC_PIN_GROUP(hscअगर1_data),
	SH_PFC_PIN_GROUP(hscअगर1_clk),
	SH_PFC_PIN_GROUP(hscअगर1_ctrl),
	SH_PFC_PIN_GROUP(hscअगर2_data),
	SH_PFC_PIN_GROUP(hscअगर2_clk),
	SH_PFC_PIN_GROUP(hscअगर2_ctrl),
	SH_PFC_PIN_GROUP(hscअगर3_data),
	SH_PFC_PIN_GROUP(hscअगर3_clk),
	SH_PFC_PIN_GROUP(hscअगर3_ctrl),

	SH_PFC_PIN_GROUP(i2c0),
	SH_PFC_PIN_GROUP(i2c1),
	SH_PFC_PIN_GROUP(i2c2),
	SH_PFC_PIN_GROUP(i2c3),
	SH_PFC_PIN_GROUP(i2c4),
	SH_PFC_PIN_GROUP(i2c5),
	SH_PFC_PIN_GROUP(i2c6),

	SH_PFC_PIN_GROUP(पूर्णांकc_ex_irq0),
	SH_PFC_PIN_GROUP(पूर्णांकc_ex_irq1),
	SH_PFC_PIN_GROUP(पूर्णांकc_ex_irq2),
	SH_PFC_PIN_GROUP(पूर्णांकc_ex_irq3),
	SH_PFC_PIN_GROUP(पूर्णांकc_ex_irq4),
	SH_PFC_PIN_GROUP(पूर्णांकc_ex_irq5),

	SH_PFC_PIN_GROUP(mmc_data1),
	SH_PFC_PIN_GROUP(mmc_data4),
	SH_PFC_PIN_GROUP(mmc_data8),
	SH_PFC_PIN_GROUP(mmc_ctrl),
	SH_PFC_PIN_GROUP(mmc_cd),
	SH_PFC_PIN_GROUP(mmc_wp),
	SH_PFC_PIN_GROUP(mmc_ds),

	SH_PFC_PIN_GROUP(msiof0_clk),
	SH_PFC_PIN_GROUP(msiof0_sync),
	SH_PFC_PIN_GROUP(msiof0_ss1),
	SH_PFC_PIN_GROUP(msiof0_ss2),
	SH_PFC_PIN_GROUP(msiof0_txd),
	SH_PFC_PIN_GROUP(msiof0_rxd),
	SH_PFC_PIN_GROUP(msiof1_clk),
	SH_PFC_PIN_GROUP(msiof1_sync),
	SH_PFC_PIN_GROUP(msiof1_ss1),
	SH_PFC_PIN_GROUP(msiof1_ss2),
	SH_PFC_PIN_GROUP(msiof1_txd),
	SH_PFC_PIN_GROUP(msiof1_rxd),
	SH_PFC_PIN_GROUP(msiof2_clk),
	SH_PFC_PIN_GROUP(msiof2_sync),
	SH_PFC_PIN_GROUP(msiof2_ss1),
	SH_PFC_PIN_GROUP(msiof2_ss2),
	SH_PFC_PIN_GROUP(msiof2_txd),
	SH_PFC_PIN_GROUP(msiof2_rxd),
	SH_PFC_PIN_GROUP(msiof3_clk),
	SH_PFC_PIN_GROUP(msiof3_sync),
	SH_PFC_PIN_GROUP(msiof3_ss1),
	SH_PFC_PIN_GROUP(msiof3_ss2),
	SH_PFC_PIN_GROUP(msiof3_txd),
	SH_PFC_PIN_GROUP(msiof3_rxd),
	SH_PFC_PIN_GROUP(msiof4_clk),
	SH_PFC_PIN_GROUP(msiof4_sync),
	SH_PFC_PIN_GROUP(msiof4_ss1),
	SH_PFC_PIN_GROUP(msiof4_ss2),
	SH_PFC_PIN_GROUP(msiof4_txd),
	SH_PFC_PIN_GROUP(msiof4_rxd),
	SH_PFC_PIN_GROUP(msiof5_clk),
	SH_PFC_PIN_GROUP(msiof5_sync),
	SH_PFC_PIN_GROUP(msiof5_ss1),
	SH_PFC_PIN_GROUP(msiof5_ss2),
	SH_PFC_PIN_GROUP(msiof5_txd),
	SH_PFC_PIN_GROUP(msiof5_rxd),

	SH_PFC_PIN_GROUP(pwm0),
	SH_PFC_PIN_GROUP(pwm1),
	SH_PFC_PIN_GROUP(pwm2),
	SH_PFC_PIN_GROUP(pwm3),
	SH_PFC_PIN_GROUP(pwm4),

	SH_PFC_PIN_GROUP(qspi0_ctrl),
	SH_PFC_PIN_GROUP(qspi0_data2),
	SH_PFC_PIN_GROUP(qspi0_data4),
	SH_PFC_PIN_GROUP(qspi1_ctrl),
	SH_PFC_PIN_GROUP(qspi1_data2),
	SH_PFC_PIN_GROUP(qspi1_data4),

	SH_PFC_PIN_GROUP(scअगर0_data),
	SH_PFC_PIN_GROUP(scअगर0_clk),
	SH_PFC_PIN_GROUP(scअगर0_ctrl),
	SH_PFC_PIN_GROUP(scअगर1_data_a),
	SH_PFC_PIN_GROUP(scअगर1_data_b),
	SH_PFC_PIN_GROUP(scअगर1_clk),
	SH_PFC_PIN_GROUP(scअगर1_ctrl),
	SH_PFC_PIN_GROUP(scअगर3_data),
	SH_PFC_PIN_GROUP(scअगर3_clk),
	SH_PFC_PIN_GROUP(scअगर3_ctrl),
	SH_PFC_PIN_GROUP(scअगर4_data),
	SH_PFC_PIN_GROUP(scअगर4_clk),
	SH_PFC_PIN_GROUP(scअगर4_ctrl),
	SH_PFC_PIN_GROUP(scअगर_clk),

	SH_PFC_PIN_GROUP(पंचांगu_tclk1_a),
	SH_PFC_PIN_GROUP(पंचांगu_tclk1_b),
	SH_PFC_PIN_GROUP(पंचांगu_tclk2_a),
	SH_PFC_PIN_GROUP(पंचांगu_tclk2_b),
	SH_PFC_PIN_GROUP(पंचांगu_tclk3),
	SH_PFC_PIN_GROUP(पंचांगu_tclk4),

	SH_PFC_PIN_GROUP(tpu_to0),
	SH_PFC_PIN_GROUP(tpu_to1),
	SH_PFC_PIN_GROUP(tpu_to2),
	SH_PFC_PIN_GROUP(tpu_to3),
पूर्ण;

अटल स्थिर अक्षर * स्थिर avb0_groups[] = अणु
	"avb0_link",
	"avb0_magic",
	"avb0_phy_int",
	"avb0_mdio",
	"avb0_rgmii",
	"avb0_txcrefclk",
	"avb0_avtp_pps",
	"avb0_avtp_capture",
	"avb0_avtp_match",
पूर्ण;

अटल स्थिर अक्षर * स्थिर avb1_groups[] = अणु
	"avb1_link",
	"avb1_magic",
	"avb1_phy_int",
	"avb1_mdio",
	"avb1_rgmii",
	"avb1_txcrefclk",
	"avb1_avtp_pps",
	"avb1_avtp_capture",
	"avb1_avtp_match",
पूर्ण;

अटल स्थिर अक्षर * स्थिर avb2_groups[] = अणु
	"avb2_link",
	"avb2_magic",
	"avb2_phy_int",
	"avb2_mdio",
	"avb2_rgmii",
	"avb2_txcrefclk",
	"avb2_avtp_pps",
	"avb2_avtp_capture",
	"avb2_avtp_match",
पूर्ण;

अटल स्थिर अक्षर * स्थिर avb3_groups[] = अणु
	"avb3_link",
	"avb3_magic",
	"avb3_phy_int",
	"avb3_mdio",
	"avb3_rgmii",
	"avb3_txcrefclk",
	"avb3_avtp_pps",
	"avb3_avtp_capture",
	"avb3_avtp_match",
पूर्ण;

अटल स्थिर अक्षर * स्थिर avb4_groups[] = अणु
	"avb4_link",
	"avb4_magic",
	"avb4_phy_int",
	"avb4_mdio",
	"avb4_rgmii",
	"avb4_txcrefclk",
	"avb4_avtp_pps",
	"avb4_avtp_capture",
	"avb4_avtp_match",
पूर्ण;

अटल स्थिर अक्षर * स्थिर avb5_groups[] = अणु
	"avb5_link",
	"avb5_magic",
	"avb5_phy_int",
	"avb5_mdio",
	"avb5_rgmii",
	"avb5_txcrefclk",
	"avb5_avtp_pps",
	"avb5_avtp_capture",
	"avb5_avtp_match",
पूर्ण;

अटल स्थिर अक्षर * स्थिर canfd0_groups[] = अणु
	"canfd0_data",
पूर्ण;

अटल स्थिर अक्षर * स्थिर canfd1_groups[] = अणु
	"canfd1_data",
पूर्ण;

अटल स्थिर अक्षर * स्थिर canfd2_groups[] = अणु
	"canfd2_data",
पूर्ण;

अटल स्थिर अक्षर * स्थिर canfd3_groups[] = अणु
	"canfd3_data",
पूर्ण;

अटल स्थिर अक्षर * स्थिर canfd4_groups[] = अणु
	"canfd4_data",
पूर्ण;

अटल स्थिर अक्षर * स्थिर canfd5_groups[] = अणु
	"canfd5_data",
पूर्ण;

अटल स्थिर अक्षर * स्थिर canfd6_groups[] = अणु
	"canfd6_data",
पूर्ण;

अटल स्थिर अक्षर * स्थिर canfd7_groups[] = अणु
	"canfd7_data",
पूर्ण;

अटल स्थिर अक्षर * स्थिर can_clk_groups[] = अणु
	"can_clk",
पूर्ण;

अटल स्थिर अक्षर * स्थिर du_groups[] = अणु
	"du_rgb888",
	"du_clk_out",
	"du_sync",
	"du_oddf",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hscअगर0_groups[] = अणु
	"hscif0_data",
	"hscif0_clk",
	"hscif0_ctrl",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hscअगर1_groups[] = अणु
	"hscif1_data",
	"hscif1_clk",
	"hscif1_ctrl",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hscअगर2_groups[] = अणु
	"hscif2_data",
	"hscif2_clk",
	"hscif2_ctrl",
पूर्ण;

अटल स्थिर अक्षर * स्थिर hscअगर3_groups[] = अणु
	"hscif3_data",
	"hscif3_clk",
	"hscif3_ctrl",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c0_groups[] = अणु
	"i2c0",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c1_groups[] = अणु
	"i2c1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c2_groups[] = अणु
	"i2c2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c3_groups[] = अणु
	"i2c3",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c4_groups[] = अणु
	"i2c4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c5_groups[] = अणु
	"i2c5",
पूर्ण;

अटल स्थिर अक्षर * स्थिर i2c6_groups[] = अणु
	"i2c6",
पूर्ण;

अटल स्थिर अक्षर * स्थिर पूर्णांकc_ex_groups[] = अणु
	"intc_ex_irq0",
	"intc_ex_irq1",
	"intc_ex_irq2",
	"intc_ex_irq3",
	"intc_ex_irq4",
	"intc_ex_irq5",
पूर्ण;

अटल स्थिर अक्षर * स्थिर mmc_groups[] = अणु
	"mmc_data1",
	"mmc_data4",
	"mmc_data8",
	"mmc_ctrl",
	"mmc_cd",
	"mmc_wp",
	"mmc_ds",
पूर्ण;

अटल स्थिर अक्षर * स्थिर msiof0_groups[] = अणु
	"msiof0_clk",
	"msiof0_sync",
	"msiof0_ss1",
	"msiof0_ss2",
	"msiof0_txd",
	"msiof0_rxd",
पूर्ण;

अटल स्थिर अक्षर * स्थिर msiof1_groups[] = अणु
	"msiof1_clk",
	"msiof1_sync",
	"msiof1_ss1",
	"msiof1_ss2",
	"msiof1_txd",
	"msiof1_rxd",
पूर्ण;

अटल स्थिर अक्षर * स्थिर msiof2_groups[] = अणु
	"msiof2_clk",
	"msiof2_sync",
	"msiof2_ss1",
	"msiof2_ss2",
	"msiof2_txd",
	"msiof2_rxd",
पूर्ण;

अटल स्थिर अक्षर * स्थिर msiof3_groups[] = अणु
	"msiof3_clk",
	"msiof3_sync",
	"msiof3_ss1",
	"msiof3_ss2",
	"msiof3_txd",
	"msiof3_rxd",
पूर्ण;

अटल स्थिर अक्षर * स्थिर msiof4_groups[] = अणु
	"msiof4_clk",
	"msiof4_sync",
	"msiof4_ss1",
	"msiof4_ss2",
	"msiof4_txd",
	"msiof4_rxd",
पूर्ण;

अटल स्थिर अक्षर * स्थिर msiof5_groups[] = अणु
	"msiof5_clk",
	"msiof5_sync",
	"msiof5_ss1",
	"msiof5_ss2",
	"msiof5_txd",
	"msiof5_rxd",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm0_groups[] = अणु
	"pwm0",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm1_groups[] = अणु
	"pwm1",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm2_groups[] = अणु
	"pwm2",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm3_groups[] = अणु
	"pwm3",
पूर्ण;

अटल स्थिर अक्षर * स्थिर pwm4_groups[] = अणु
	"pwm4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qspi0_groups[] = अणु
	"qspi0_ctrl",
	"qspi0_data2",
	"qspi0_data4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर qspi1_groups[] = अणु
	"qspi1_ctrl",
	"qspi1_data2",
	"qspi1_data4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर scअगर0_groups[] = अणु
	"scif0_data",
	"scif0_clk",
	"scif0_ctrl",
पूर्ण;

अटल स्थिर अक्षर * स्थिर scअगर1_groups[] = अणु
	"scif1_data_a",
	"scif1_data_b",
	"scif1_clk",
	"scif1_ctrl",
पूर्ण;

अटल स्थिर अक्षर * स्थिर scअगर3_groups[] = अणु
	"scif3_data",
	"scif3_clk",
	"scif3_ctrl",
पूर्ण;

अटल स्थिर अक्षर * स्थिर scअगर4_groups[] = अणु
	"scif4_data",
	"scif4_clk",
	"scif4_ctrl",
पूर्ण;

अटल स्थिर अक्षर * स्थिर scअगर_clk_groups[] = अणु
	"scif_clk",
पूर्ण;

अटल स्थिर अक्षर * स्थिर पंचांगu_groups[] = अणु
	"tmu_tclk1_a",
	"tmu_tclk1_b",
	"tmu_tclk2_a",
	"tmu_tclk2_b",
	"tmu_tclk3",
	"tmu_tclk4",
पूर्ण;

अटल स्थिर अक्षर * स्थिर tpu_groups[] = अणु
	"tpu_to0",
	"tpu_to1",
	"tpu_to2",
	"tpu_to3",
पूर्ण;

अटल स्थिर काष्ठा sh_pfc_function pinmux_functions[] = अणु
	SH_PFC_FUNCTION(avb0),
	SH_PFC_FUNCTION(avb1),
	SH_PFC_FUNCTION(avb2),
	SH_PFC_FUNCTION(avb3),
	SH_PFC_FUNCTION(avb4),
	SH_PFC_FUNCTION(avb5),

	SH_PFC_FUNCTION(canfd0),
	SH_PFC_FUNCTION(canfd1),
	SH_PFC_FUNCTION(canfd2),
	SH_PFC_FUNCTION(canfd3),
	SH_PFC_FUNCTION(canfd4),
	SH_PFC_FUNCTION(canfd5),
	SH_PFC_FUNCTION(canfd6),
	SH_PFC_FUNCTION(canfd7),
	SH_PFC_FUNCTION(can_clk),

	SH_PFC_FUNCTION(du),

	SH_PFC_FUNCTION(hscअगर0),
	SH_PFC_FUNCTION(hscअगर1),
	SH_PFC_FUNCTION(hscअगर2),
	SH_PFC_FUNCTION(hscअगर3),

	SH_PFC_FUNCTION(i2c0),
	SH_PFC_FUNCTION(i2c1),
	SH_PFC_FUNCTION(i2c2),
	SH_PFC_FUNCTION(i2c3),
	SH_PFC_FUNCTION(i2c4),
	SH_PFC_FUNCTION(i2c5),
	SH_PFC_FUNCTION(i2c6),

	SH_PFC_FUNCTION(पूर्णांकc_ex),

	SH_PFC_FUNCTION(mmc),

	SH_PFC_FUNCTION(msiof0),
	SH_PFC_FUNCTION(msiof1),
	SH_PFC_FUNCTION(msiof2),
	SH_PFC_FUNCTION(msiof3),
	SH_PFC_FUNCTION(msiof4),
	SH_PFC_FUNCTION(msiof5),

	SH_PFC_FUNCTION(pwm0),
	SH_PFC_FUNCTION(pwm1),
	SH_PFC_FUNCTION(pwm2),
	SH_PFC_FUNCTION(pwm3),
	SH_PFC_FUNCTION(pwm4),

	SH_PFC_FUNCTION(qspi0),
	SH_PFC_FUNCTION(qspi1),

	SH_PFC_FUNCTION(scअगर0),
	SH_PFC_FUNCTION(scअगर1),
	SH_PFC_FUNCTION(scअगर3),
	SH_PFC_FUNCTION(scअगर4),
	SH_PFC_FUNCTION(scअगर_clk),

	SH_PFC_FUNCTION(पंचांगu),

	SH_PFC_FUNCTION(tpu),
पूर्ण;

अटल स्थिर काष्ठा pinmux_cfg_reg pinmux_config_regs[] = अणु
#घोषणा F_(x, y)	FN_##y
#घोषणा FM(x)		FN_##x
	अणु PINMUX_CFG_REG("GPSR0", 0xe6058040, 32, 1, GROUP(
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		GP_0_27_FN,	GPSR0_27,
		GP_0_26_FN,	GPSR0_26,
		GP_0_25_FN,	GPSR0_25,
		GP_0_24_FN,	GPSR0_24,
		GP_0_23_FN,	GPSR0_23,
		GP_0_22_FN,	GPSR0_22,
		GP_0_21_FN,	GPSR0_21,
		GP_0_20_FN,	GPSR0_20,
		GP_0_19_FN,	GPSR0_19,
		GP_0_18_FN,	GPSR0_18,
		GP_0_17_FN,	GPSR0_17,
		GP_0_16_FN,	GPSR0_16,
		GP_0_15_FN,	GPSR0_15,
		GP_0_14_FN,	GPSR0_14,
		GP_0_13_FN,	GPSR0_13,
		GP_0_12_FN,	GPSR0_12,
		GP_0_11_FN,	GPSR0_11,
		GP_0_10_FN,	GPSR0_10,
		GP_0_9_FN,	GPSR0_9,
		GP_0_8_FN,	GPSR0_8,
		GP_0_7_FN,	GPSR0_7,
		GP_0_6_FN,	GPSR0_6,
		GP_0_5_FN,	GPSR0_5,
		GP_0_4_FN,	GPSR0_4,
		GP_0_3_FN,	GPSR0_3,
		GP_0_2_FN,	GPSR0_2,
		GP_0_1_FN,	GPSR0_1,
		GP_0_0_FN,	GPSR0_0, ))
	पूर्ण,
	अणु PINMUX_CFG_REG("GPSR1", 0xe6050040, 32, 1, GROUP(
		0, 0,
		GP_1_30_FN,	GPSR1_30,
		GP_1_29_FN,	GPSR1_29,
		GP_1_28_FN,	GPSR1_28,
		GP_1_27_FN,	GPSR1_27,
		GP_1_26_FN,	GPSR1_26,
		GP_1_25_FN,	GPSR1_25,
		GP_1_24_FN,	GPSR1_24,
		GP_1_23_FN,	GPSR1_23,
		GP_1_22_FN,	GPSR1_22,
		GP_1_21_FN,	GPSR1_21,
		GP_1_20_FN,	GPSR1_20,
		GP_1_19_FN,	GPSR1_19,
		GP_1_18_FN,	GPSR1_18,
		GP_1_17_FN,	GPSR1_17,
		GP_1_16_FN,	GPSR1_16,
		GP_1_15_FN,	GPSR1_15,
		GP_1_14_FN,	GPSR1_14,
		GP_1_13_FN,	GPSR1_13,
		GP_1_12_FN,	GPSR1_12,
		GP_1_11_FN,	GPSR1_11,
		GP_1_10_FN,	GPSR1_10,
		GP_1_9_FN,	GPSR1_9,
		GP_1_8_FN,	GPSR1_8,
		GP_1_7_FN,	GPSR1_7,
		GP_1_6_FN,	GPSR1_6,
		GP_1_5_FN,	GPSR1_5,
		GP_1_4_FN,	GPSR1_4,
		GP_1_3_FN,	GPSR1_3,
		GP_1_2_FN,	GPSR1_2,
		GP_1_1_FN,	GPSR1_1,
		GP_1_0_FN,	GPSR1_0, ))
	पूर्ण,
	अणु PINMUX_CFG_REG("GPSR2", 0xe6050840, 32, 1, GROUP(
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		GP_2_24_FN,	GPSR2_24,
		GP_2_23_FN,	GPSR2_23,
		GP_2_22_FN,	GPSR2_22,
		GP_2_21_FN,	GPSR2_21,
		GP_2_20_FN,	GPSR2_20,
		GP_2_19_FN,	GPSR2_19,
		GP_2_18_FN,	GPSR2_18,
		GP_2_17_FN,	GPSR2_17,
		GP_2_16_FN,	GPSR2_16,
		GP_2_15_FN,	GPSR2_15,
		GP_2_14_FN,	GPSR2_14,
		GP_2_13_FN,	GPSR2_13,
		GP_2_12_FN,	GPSR2_12,
		GP_2_11_FN,	GPSR2_11,
		GP_2_10_FN,	GPSR2_10,
		GP_2_9_FN,	GPSR2_9,
		GP_2_8_FN,	GPSR2_8,
		GP_2_7_FN,	GPSR2_7,
		GP_2_6_FN,	GPSR2_6,
		GP_2_5_FN,	GPSR2_5,
		GP_2_4_FN,	GPSR2_4,
		GP_2_3_FN,	GPSR2_3,
		GP_2_2_FN,	GPSR2_2,
		GP_2_1_FN,	GPSR2_1,
		GP_2_0_FN,	GPSR2_0, ))
	पूर्ण,
	अणु PINMUX_CFG_REG("GPSR3", 0xe6058840, 32, 1, GROUP(
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		GP_3_16_FN,	GPSR3_16,
		GP_3_15_FN,	GPSR3_15,
		GP_3_14_FN,	GPSR3_14,
		GP_3_13_FN,	GPSR3_13,
		GP_3_12_FN,	GPSR3_12,
		GP_3_11_FN,	GPSR3_11,
		GP_3_10_FN,	GPSR3_10,
		GP_3_9_FN,	GPSR3_9,
		GP_3_8_FN,	GPSR3_8,
		GP_3_7_FN,	GPSR3_7,
		GP_3_6_FN,	GPSR3_6,
		GP_3_5_FN,	GPSR3_5,
		GP_3_4_FN,	GPSR3_4,
		GP_3_3_FN,	GPSR3_3,
		GP_3_2_FN,	GPSR3_2,
		GP_3_1_FN,	GPSR3_1,
		GP_3_0_FN,	GPSR3_0, ))
	पूर्ण,
	अणु PINMUX_CFG_REG("GPSR4", 0xe6060040, 32, 1, GROUP(
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		GP_4_26_FN,	GPSR4_26,
		GP_4_25_FN,	GPSR4_25,
		GP_4_24_FN,	GPSR4_24,
		GP_4_23_FN,	GPSR4_23,
		GP_4_22_FN,	GPSR4_22,
		GP_4_21_FN,	GPSR4_21,
		GP_4_20_FN,	GPSR4_20,
		GP_4_19_FN,	GPSR4_19,
		GP_4_18_FN,	GPSR4_18,
		GP_4_17_FN,	GPSR4_17,
		GP_4_16_FN,	GPSR4_16,
		GP_4_15_FN,	GPSR4_15,
		GP_4_14_FN,	GPSR4_14,
		GP_4_13_FN,	GPSR4_13,
		GP_4_12_FN,	GPSR4_12,
		GP_4_11_FN,	GPSR4_11,
		GP_4_10_FN,	GPSR4_10,
		GP_4_9_FN,	GPSR4_9,
		GP_4_8_FN,	GPSR4_8,
		GP_4_7_FN,	GPSR4_7,
		GP_4_6_FN,	GPSR4_6,
		GP_4_5_FN,	GPSR4_5,
		GP_4_4_FN,	GPSR4_4,
		GP_4_3_FN,	GPSR4_3,
		GP_4_2_FN,	GPSR4_2,
		GP_4_1_FN,	GPSR4_1,
		GP_4_0_FN,	GPSR4_0, ))
	पूर्ण,
	अणु PINMUX_CFG_REG("GPSR5", 0xe6060840, 32, 1, GROUP(
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		GP_5_20_FN,	GPSR5_20,
		GP_5_19_FN,	GPSR5_19,
		GP_5_18_FN,	GPSR5_18,
		GP_5_17_FN,	GPSR5_17,
		GP_5_16_FN,	GPSR5_16,
		GP_5_15_FN,	GPSR5_15,
		GP_5_14_FN,	GPSR5_14,
		GP_5_13_FN,	GPSR5_13,
		GP_5_12_FN,	GPSR5_12,
		GP_5_11_FN,	GPSR5_11,
		GP_5_10_FN,	GPSR5_10,
		GP_5_9_FN,	GPSR5_9,
		GP_5_8_FN,	GPSR5_8,
		GP_5_7_FN,	GPSR5_7,
		GP_5_6_FN,	GPSR5_6,
		GP_5_5_FN,	GPSR5_5,
		GP_5_4_FN,	GPSR5_4,
		GP_5_3_FN,	GPSR5_3,
		GP_5_2_FN,	GPSR5_2,
		GP_5_1_FN,	GPSR5_1,
		GP_5_0_FN,	GPSR5_0, ))
	पूर्ण,
	अणु PINMUX_CFG_REG("GPSR6", 0xe6068040, 32, 1, GROUP(
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		GP_6_20_FN,	GPSR6_20,
		GP_6_19_FN,	GPSR6_19,
		GP_6_18_FN,	GPSR6_18,
		GP_6_17_FN,	GPSR6_17,
		GP_6_16_FN,	GPSR6_16,
		GP_6_15_FN,	GPSR6_15,
		GP_6_14_FN,	GPSR6_14,
		GP_6_13_FN,	GPSR6_13,
		GP_6_12_FN,	GPSR6_12,
		GP_6_11_FN,	GPSR6_11,
		GP_6_10_FN,	GPSR6_10,
		GP_6_9_FN,	GPSR6_9,
		GP_6_8_FN,	GPSR6_8,
		GP_6_7_FN,	GPSR6_7,
		GP_6_6_FN,	GPSR6_6,
		GP_6_5_FN,	GPSR6_5,
		GP_6_4_FN,	GPSR6_4,
		GP_6_3_FN,	GPSR6_3,
		GP_6_2_FN,	GPSR6_2,
		GP_6_1_FN,	GPSR6_1,
		GP_6_0_FN,	GPSR6_0, ))
	पूर्ण,
	अणु PINMUX_CFG_REG("GPSR7", 0xe6068840, 32, 1, GROUP(
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		GP_7_20_FN,	GPSR7_20,
		GP_7_19_FN,	GPSR7_19,
		GP_7_18_FN,	GPSR7_18,
		GP_7_17_FN,	GPSR7_17,
		GP_7_16_FN,	GPSR7_16,
		GP_7_15_FN,	GPSR7_15,
		GP_7_14_FN,	GPSR7_14,
		GP_7_13_FN,	GPSR7_13,
		GP_7_12_FN,	GPSR7_12,
		GP_7_11_FN,	GPSR7_11,
		GP_7_10_FN,	GPSR7_10,
		GP_7_9_FN,	GPSR7_9,
		GP_7_8_FN,	GPSR7_8,
		GP_7_7_FN,	GPSR7_7,
		GP_7_6_FN,	GPSR7_6,
		GP_7_5_FN,	GPSR7_5,
		GP_7_4_FN,	GPSR7_4,
		GP_7_3_FN,	GPSR7_3,
		GP_7_2_FN,	GPSR7_2,
		GP_7_1_FN,	GPSR7_1,
		GP_7_0_FN,	GPSR7_0, ))
	पूर्ण,
	अणु PINMUX_CFG_REG("GPSR8", 0xe6069040, 32, 1, GROUP(
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		GP_8_20_FN,	GPSR8_20,
		GP_8_19_FN,	GPSR8_19,
		GP_8_18_FN,	GPSR8_18,
		GP_8_17_FN,	GPSR8_17,
		GP_8_16_FN,	GPSR8_16,
		GP_8_15_FN,	GPSR8_15,
		GP_8_14_FN,	GPSR8_14,
		GP_8_13_FN,	GPSR8_13,
		GP_8_12_FN,	GPSR8_12,
		GP_8_11_FN,	GPSR8_11,
		GP_8_10_FN,	GPSR8_10,
		GP_8_9_FN,	GPSR8_9,
		GP_8_8_FN,	GPSR8_8,
		GP_8_7_FN,	GPSR8_7,
		GP_8_6_FN,	GPSR8_6,
		GP_8_5_FN,	GPSR8_5,
		GP_8_4_FN,	GPSR8_4,
		GP_8_3_FN,	GPSR8_3,
		GP_8_2_FN,	GPSR8_2,
		GP_8_1_FN,	GPSR8_1,
		GP_8_0_FN,	GPSR8_0, ))
	पूर्ण,
	अणु PINMUX_CFG_REG("GPSR9", 0xe6069840, 32, 1, GROUP(
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		0, 0,
		GP_9_20_FN,	GPSR9_20,
		GP_9_19_FN,	GPSR9_19,
		GP_9_18_FN,	GPSR9_18,
		GP_9_17_FN,	GPSR9_17,
		GP_9_16_FN,	GPSR9_16,
		GP_9_15_FN,	GPSR9_15,
		GP_9_14_FN,	GPSR9_14,
		GP_9_13_FN,	GPSR9_13,
		GP_9_12_FN,	GPSR9_12,
		GP_9_11_FN,	GPSR9_11,
		GP_9_10_FN,	GPSR9_10,
		GP_9_9_FN,	GPSR9_9,
		GP_9_8_FN,	GPSR9_8,
		GP_9_7_FN,	GPSR9_7,
		GP_9_6_FN,	GPSR9_6,
		GP_9_5_FN,	GPSR9_5,
		GP_9_4_FN,	GPSR9_4,
		GP_9_3_FN,	GPSR9_3,
		GP_9_2_FN,	GPSR9_2,
		GP_9_1_FN,	GPSR9_1,
		GP_9_0_FN,	GPSR9_0, ))
	पूर्ण,
#अघोषित F_
#अघोषित FM

#घोषणा F_(x, y)	x,
#घोषणा FM(x)		FN_##x,
	अणु PINMUX_CFG_REG("IP0SR1", 0xe6050060, 32, 4, GROUP(
		IP0SR1_31_28
		IP0SR1_27_24
		IP0SR1_23_20
		IP0SR1_19_16
		IP0SR1_15_12
		IP0SR1_11_8
		IP0SR1_7_4
		IP0SR1_3_0))
	पूर्ण,
	अणु PINMUX_CFG_REG("IP1SR1", 0xe6050064, 32, 4, GROUP(
		IP1SR1_31_28
		IP1SR1_27_24
		IP1SR1_23_20
		IP1SR1_19_16
		IP1SR1_15_12
		IP1SR1_11_8
		IP1SR1_7_4
		IP1SR1_3_0))
	पूर्ण,
	अणु PINMUX_CFG_REG("IP2SR1", 0xe6050068, 32, 4, GROUP(
		IP2SR1_31_28
		IP2SR1_27_24
		IP2SR1_23_20
		IP2SR1_19_16
		IP2SR1_15_12
		IP2SR1_11_8
		IP2SR1_7_4
		IP2SR1_3_0))
	पूर्ण,
	अणु PINMUX_CFG_REG("IP3SR1", 0xe605006c, 32, 4, GROUP(
		IP3SR1_31_28
		IP3SR1_27_24
		IP3SR1_23_20
		IP3SR1_19_16
		IP3SR1_15_12
		IP3SR1_11_8
		IP3SR1_7_4
		IP3SR1_3_0))
	पूर्ण,
	अणु PINMUX_CFG_REG("IP0SR2", 0xe6050860, 32, 4, GROUP(
		IP0SR2_31_28
		IP0SR2_27_24
		IP0SR2_23_20
		IP0SR2_19_16
		IP0SR2_15_12
		IP0SR2_11_8
		IP0SR2_7_4
		IP0SR2_3_0))
	पूर्ण,
	अणु PINMUX_CFG_REG("IP1SR2", 0xe6050864, 32, 4, GROUP(
		IP1SR2_31_28
		IP1SR2_27_24
		IP1SR2_23_20
		IP1SR2_19_16
		IP1SR2_15_12
		IP1SR2_11_8
		IP1SR2_7_4
		IP1SR2_3_0))
	पूर्ण,
	अणु PINMUX_CFG_REG("IP2SR2", 0xe6050868, 32, 4, GROUP(
		IP2SR2_31_28
		IP2SR2_27_24
		IP2SR2_23_20
		IP2SR2_19_16
		IP2SR2_15_12
		IP2SR2_11_8
		IP2SR2_7_4
		IP2SR2_3_0))
	पूर्ण,
	अणु PINMUX_CFG_REG("IP0SR3", 0xe6058860, 32, 4, GROUP(
		IP0SR3_31_28
		IP0SR3_27_24
		IP0SR3_23_20
		IP0SR3_19_16
		IP0SR3_15_12
		IP0SR3_11_8
		IP0SR3_7_4
		IP0SR3_3_0))
	पूर्ण,
	अणु PINMUX_CFG_REG("IP1SR3", 0xe6058864, 32, 4, GROUP(
		IP1SR3_31_28
		IP1SR3_27_24
		IP1SR3_23_20
		IP1SR3_19_16
		IP1SR3_15_12
		IP1SR3_11_8
		IP1SR3_7_4
		IP1SR3_3_0))
	पूर्ण,
	अणु PINMUX_CFG_REG("IP0SR4", 0xe6060060, 32, 4, GROUP(
		IP0SR4_31_28
		IP0SR4_27_24
		IP0SR4_23_20
		IP0SR4_19_16
		IP0SR4_15_12
		IP0SR4_11_8
		IP0SR4_7_4
		IP0SR4_3_0))
	पूर्ण,
	अणु PINMUX_CFG_REG("IP1SR4", 0xe6060064, 32, 4, GROUP(
		IP1SR4_31_28
		IP1SR4_27_24
		IP1SR4_23_20
		IP1SR4_19_16
		IP1SR4_15_12
		IP1SR4_11_8
		IP1SR4_7_4
		IP1SR4_3_0))
	पूर्ण,
	अणु PINMUX_CFG_REG("IP2SR4", 0xe6060068, 32, 4, GROUP(
		IP2SR4_31_28
		IP2SR4_27_24
		IP2SR4_23_20
		IP2SR4_19_16
		IP2SR4_15_12
		IP2SR4_11_8
		IP2SR4_7_4
		IP2SR4_3_0))
	पूर्ण,
	अणु PINMUX_CFG_REG("IP0SR5", 0xe6060860, 32, 4, GROUP(
		IP0SR5_31_28
		IP0SR5_27_24
		IP0SR5_23_20
		IP0SR5_19_16
		IP0SR5_15_12
		IP0SR5_11_8
		IP0SR5_7_4
		IP0SR5_3_0))
	पूर्ण,
	अणु PINMUX_CFG_REG("IP1SR5", 0xe6060864, 32, 4, GROUP(
		IP1SR5_31_28
		IP1SR5_27_24
		IP1SR5_23_20
		IP1SR5_19_16
		IP1SR5_15_12
		IP1SR5_11_8
		IP1SR5_7_4
		IP1SR5_3_0))
	पूर्ण,
	अणु PINMUX_CFG_REG("IP2SR5", 0xe6060868, 32, 4, GROUP(
		IP2SR5_31_28
		IP2SR5_27_24
		IP2SR5_23_20
		IP2SR5_19_16
		IP2SR5_15_12
		IP2SR5_11_8
		IP2SR5_7_4
		IP2SR5_3_0))
	पूर्ण,
#अघोषित F_
#अघोषित FM

#घोषणा F_(x, y)	x,
#घोषणा FM(x)		FN_##x,
	अणु PINMUX_CFG_REG_VAR("MOD_SEL2", 0xe6050900, 32,
			     GROUP(4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 1, 1),
			     GROUP(
		/* RESERVED 31, 30, 29, 28 */
		0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0,
		/* RESERVED 27, 26, 25, 24 */
		0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0,
		/* RESERVED 23, 22, 21, 20 */
		0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0,
		/* RESERVED 19, 18, 17, 16 */
		0, 0, 0, 0, 0, 0, 0, 0,	0, 0, 0, 0, 0, 0, 0, 0,
		MOD_SEL2_14_15
		MOD_SEL2_12_13
		MOD_SEL2_10_11
		MOD_SEL2_8_9
		MOD_SEL2_6_7
		MOD_SEL2_4_5
		MOD_SEL2_2_3
		0, 0,
		0, 0, ))
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा pinmux_drive_reg pinmux_drive_regs[] = अणु
	अणु PINMUX_DRIVE_REG("DRV0CTRL0", 0xe6058080) अणु
		अणु RCAR_GP_PIN(0,  7), 28, 2 पूर्ण,	/* QSPI1_MOSI_IO0 */
		अणु RCAR_GP_PIN(0,  6), 24, 2 पूर्ण,	/* QSPI1_SPCLK */
		अणु RCAR_GP_PIN(0,  5), 20, 2 पूर्ण,	/* QSPI0_SSL */
		अणु RCAR_GP_PIN(0,  4), 16, 2 पूर्ण,	/* QSPI0_IO3 */
		अणु RCAR_GP_PIN(0,  3), 12, 2 पूर्ण,	/* QSPI0_IO2 */
		अणु RCAR_GP_PIN(0,  2),  8, 2 पूर्ण,	/* QSPI0_MISO_IO1 */
		अणु RCAR_GP_PIN(0,  1),  4, 2 पूर्ण,	/* QSPI0_MOSI_IO0 */
		अणु RCAR_GP_PIN(0,  0),  0, 2 पूर्ण,	/* QSPI0_SPCLK */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV1CTRL0", 0xe6058084) अणु
		अणु RCAR_GP_PIN(0, 15), 28, 3 पूर्ण,	/* SD_WP */
		अणु RCAR_GP_PIN(0, 14), 24, 2 पूर्ण,	/* RPC_INT_N */
		अणु RCAR_GP_PIN(0, 13), 20, 2 पूर्ण,	/* RPC_WP_N */
		अणु RCAR_GP_PIN(0, 12), 16, 2 पूर्ण,	/* RPC_RESET_N */
		अणु RCAR_GP_PIN(0, 11), 12, 2 पूर्ण,	/* QSPI1_SSL */
		अणु RCAR_GP_PIN(0, 10),  8, 2 पूर्ण,	/* QSPI1_IO3 */
		अणु RCAR_GP_PIN(0,  9),  4, 2 पूर्ण,	/* QSPI1_IO2 */
		अणु RCAR_GP_PIN(0,  8),  0, 2 पूर्ण,	/* QSPI1_MISO_IO1 */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV2CTRL0", 0xe6058088) अणु
		अणु RCAR_GP_PIN(0, 23), 28, 3 पूर्ण,	/* MMC_SD_CLK */
		अणु RCAR_GP_PIN(0, 22), 24, 3 पूर्ण,	/* MMC_SD_D3 */
		अणु RCAR_GP_PIN(0, 21), 20, 3 पूर्ण,	/* MMC_SD_D2 */
		अणु RCAR_GP_PIN(0, 20), 16, 3 पूर्ण,	/* MMC_SD_D1 */
		अणु RCAR_GP_PIN(0, 19), 12, 3 पूर्ण,	/* MMC_SD_D0 */
		अणु RCAR_GP_PIN(0, 18),  8, 3 पूर्ण,	/* MMC_SD_CMD */
		अणु RCAR_GP_PIN(0, 17),  4, 3 पूर्ण,	/* MMC_DS */
		अणु RCAR_GP_PIN(0, 16),  0, 3 पूर्ण,	/* SD_CD */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV3CTRL0", 0xe605808c) अणु
		अणु RCAR_GP_PIN(0, 27), 12, 3 पूर्ण,	/* MMC_D7 */
		अणु RCAR_GP_PIN(0, 26),  8, 3 पूर्ण,	/* MMC_D6 */
		अणु RCAR_GP_PIN(0, 25),  4, 3 पूर्ण,	/* MMC_D5 */
		अणु RCAR_GP_PIN(0, 24),  0, 3 पूर्ण,	/* MMC_D4 */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV0CTRL1", 0xe6050080) अणु
		अणु RCAR_GP_PIN(1,  7), 28, 3 पूर्ण,	/* MSIOF0_TXD */
		अणु RCAR_GP_PIN(1,  6), 24, 3 पूर्ण,	/* MSIOF0_RXD */
		अणु RCAR_GP_PIN(1,  5), 20, 3 पूर्ण,	/* HTX0 */
		अणु RCAR_GP_PIN(1,  4), 16, 3 पूर्ण,	/* HCTS0_N */
		अणु RCAR_GP_PIN(1,  3), 12, 3 पूर्ण,	/* HRTS0_N */
		अणु RCAR_GP_PIN(1,  2),  8, 3 पूर्ण,	/* HSCK0 */
		अणु RCAR_GP_PIN(1,  1),  4, 3 पूर्ण,	/* HRX0 */
		अणु RCAR_GP_PIN(1,  0),  0, 3 पूर्ण,	/* SCIF_CLK */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV1CTRL1", 0xe6050084) अणु
		अणु RCAR_GP_PIN(1, 15), 28, 3 पूर्ण,	/* MSIOF1_SYNC */
		अणु RCAR_GP_PIN(1, 14), 24, 3 पूर्ण,	/* MSIOF1_SCK */
		अणु RCAR_GP_PIN(1, 13), 20, 3 पूर्ण,	/* MSIOF1_TXD */
		अणु RCAR_GP_PIN(1, 12), 16, 3 पूर्ण,	/* MSIOF1_RXD */
		अणु RCAR_GP_PIN(1, 11), 12, 3 पूर्ण,	/* MSIOF0_SS2 */
		अणु RCAR_GP_PIN(1, 10),  8, 3 पूर्ण,	/* MSIOF0_SS1 */
		अणु RCAR_GP_PIN(1,  9),  4, 3 पूर्ण,	/* MSIOF0_SYNC */
		अणु RCAR_GP_PIN(1,  8),  0, 3 पूर्ण,	/* MSIOF0_SCK */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV2CTRL1", 0xe6050088) अणु
		अणु RCAR_GP_PIN(1, 23), 28, 3 पूर्ण,	/* MSIOF2_SS2 */
		अणु RCAR_GP_PIN(1, 22), 24, 3 पूर्ण,	/* MSIOF2_SS1 */
		अणु RCAR_GP_PIN(1, 21), 20, 3 पूर्ण,	/* MSIOF2_SYNC */
		अणु RCAR_GP_PIN(1, 20), 16, 3 पूर्ण,	/* MSIOF2_SCK */
		अणु RCAR_GP_PIN(1, 19), 12, 3 पूर्ण,	/* MSIOF2_TXD */
		अणु RCAR_GP_PIN(1, 18),  8, 3 पूर्ण,	/* MSIOF2_RXD */
		अणु RCAR_GP_PIN(1, 17),  4, 3 पूर्ण,	/* MSIOF1_SS2 */
		अणु RCAR_GP_PIN(1, 16),  0, 3 पूर्ण,	/* MSIOF1_SS1 */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV3CTRL1", 0xe605008c) अणु
		अणु RCAR_GP_PIN(1, 30), 24, 3 पूर्ण,	/* GP1_30 */
		अणु RCAR_GP_PIN(1, 29), 20, 3 पूर्ण,	/* GP1_29 */
		अणु RCAR_GP_PIN(1, 28), 16, 3 पूर्ण,	/* GP1_28 */
		अणु RCAR_GP_PIN(1, 27), 12, 3 पूर्ण,	/* IRQ3 */
		अणु RCAR_GP_PIN(1, 26),  8, 3 पूर्ण,	/* IRQ2 */
		अणु RCAR_GP_PIN(1, 25),  4, 3 पूर्ण,	/* IRQ1 */
		अणु RCAR_GP_PIN(1, 24),  0, 3 पूर्ण,	/* IRQ0 */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV0CTRL2", 0xe6050880) अणु
		अणु RCAR_GP_PIN(2,  7), 28, 3 पूर्ण,	/* GP2_07 */
		अणु RCAR_GP_PIN(2,  6), 24, 3 पूर्ण,	/* GP2_06 */
		अणु RCAR_GP_PIN(2,  5), 20, 3 पूर्ण,	/* GP2_05 */
		अणु RCAR_GP_PIN(2,  4), 16, 3 पूर्ण,	/* GP2_04 */
		अणु RCAR_GP_PIN(2,  3), 12, 3 पूर्ण,	/* GP2_03 */
		अणु RCAR_GP_PIN(2,  2),  8, 3 पूर्ण,	/* GP2_02 */
		अणु RCAR_GP_PIN(2,  1),  4, 2 पूर्ण,	/* IPC_CLKOUT */
		अणु RCAR_GP_PIN(2,  0),  0, 2 पूर्ण,	/* IPC_CLKIN */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV1CTRL2", 0xe6050884) अणु
		अणु RCAR_GP_PIN(2, 15), 28, 3 पूर्ण,	/* GP2_15 */
		अणु RCAR_GP_PIN(2, 14), 24, 3 पूर्ण,	/* GP2_14 */
		अणु RCAR_GP_PIN(2, 13), 20, 3 पूर्ण,	/* GP2_13 */
		अणु RCAR_GP_PIN(2, 12), 16, 3 पूर्ण,	/* GP2_12 */
		अणु RCAR_GP_PIN(2, 11), 12, 3 पूर्ण,	/* GP2_11 */
		अणु RCAR_GP_PIN(2, 10),  8, 3 पूर्ण,	/* GP2_10 */
		अणु RCAR_GP_PIN(2,  9),  4, 3 पूर्ण,	/* GP2_9 */
		अणु RCAR_GP_PIN(2,  8),  0, 3 पूर्ण,	/* GP2_8 */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV2CTRL2", 0xe6050888) अणु
		अणु RCAR_GP_PIN(2, 23), 28, 3 पूर्ण,	/* TCLK1_A */
		अणु RCAR_GP_PIN(2, 22), 24, 3 पूर्ण,	/* TPU0TO1 */
		अणु RCAR_GP_PIN(2, 21), 20, 3 पूर्ण,	/* TPU0TO0 */
		अणु RCAR_GP_PIN(2, 20), 16, 3 पूर्ण,	/* CLK_EXTFXR */
		अणु RCAR_GP_PIN(2, 19), 12, 3 पूर्ण,	/* RXDB_EXTFXR */
		अणु RCAR_GP_PIN(2, 18),  8, 3 पूर्ण,	/* FXR_TXDB */
		अणु RCAR_GP_PIN(2, 17),  4, 3 पूर्ण,	/* RXDA_EXTFXR_A */
		अणु RCAR_GP_PIN(2, 16),  0, 3 पूर्ण,	/* FXR_TXDA_A */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV3CTRL2", 0xe605088c) अणु
		अणु RCAR_GP_PIN(2, 24), 0, 3 पूर्ण,	/* TCLK2_A */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV0CTRL3", 0xe6058880) अणु
		अणु RCAR_GP_PIN(3,  7), 28, 3 पूर्ण,	/* CANFD3_TX */
		अणु RCAR_GP_PIN(3,  6), 24, 3 पूर्ण,	/* CANFD2_RX */
		अणु RCAR_GP_PIN(3,  5), 20, 3 पूर्ण,	/* CANFD2_TX */
		अणु RCAR_GP_PIN(3,  4), 16, 3 पूर्ण,	/* CANFD1_RX */
		अणु RCAR_GP_PIN(3,  3), 12, 3 पूर्ण,	/* CANFD1_TX */
		अणु RCAR_GP_PIN(3,  2),  8, 3 पूर्ण,	/* CANFD0_RX */
		अणु RCAR_GP_PIN(3,  1),  4, 2 पूर्ण,	/* CANFD0_TX */
		अणु RCAR_GP_PIN(3,  0),  0, 2 पूर्ण,	/* CAN_CLK */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV1CTRL3", 0xe6058884) अणु
		अणु RCAR_GP_PIN(3, 15), 28, 3 पूर्ण,	/* CANFD7_TX */
		अणु RCAR_GP_PIN(3, 14), 24, 3 पूर्ण,	/* CANFD6_RX */
		अणु RCAR_GP_PIN(3, 13), 20, 3 पूर्ण,	/* CANFD6_TX */
		अणु RCAR_GP_PIN(3, 12), 16, 3 पूर्ण,	/* CANFD5_RX */
		अणु RCAR_GP_PIN(3, 11), 12, 3 पूर्ण,	/* CANFD5_TX */
		अणु RCAR_GP_PIN(3, 10),  8, 3 पूर्ण,	/* CANFD4_RX */
		अणु RCAR_GP_PIN(3,  9),  4, 3 पूर्ण,	/* CANFD4_TX*/
		अणु RCAR_GP_PIN(3,  8),  0, 3 पूर्ण,	/* CANFD3_RX */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV2CTRL3", 0xe6058888) अणु
		अणु RCAR_GP_PIN(3,  16),  0, 3 पूर्ण,	/* CANFD7_RX */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV0CTRL4", 0xe6060080) अणु
		अणु RCAR_GP_PIN(4,  7), 28, 3 पूर्ण,	/* AVB0_TXC */
		अणु RCAR_GP_PIN(4,  6), 24, 3 पूर्ण,	/* AVB0_TX_CTL */
		अणु RCAR_GP_PIN(4,  5), 20, 3 पूर्ण,	/* AVB0_RD3 */
		अणु RCAR_GP_PIN(4,  4), 16, 3 पूर्ण,	/* AVB0_RD2 */
		अणु RCAR_GP_PIN(4,  3), 12, 3 पूर्ण,	/* AVB0_RD1 */
		अणु RCAR_GP_PIN(4,  2),  8, 3 पूर्ण,	/* AVB0_RD0 */
		अणु RCAR_GP_PIN(4,  1),  4, 3 पूर्ण,	/* AVB0_RXC */
		अणु RCAR_GP_PIN(4,  0),  0, 3 पूर्ण,	/* AVB0_RX_CTL */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV1CTRL4", 0xe6060084) अणु
		अणु RCAR_GP_PIN(4, 15), 28, 3 पूर्ण,	/* AVB0_MAGIC */
		अणु RCAR_GP_PIN(4, 14), 24, 3 पूर्ण,	/* AVB0_MDC */
		अणु RCAR_GP_PIN(4, 13), 20, 3 पूर्ण,	/* AVB0_MDIO */
		अणु RCAR_GP_PIN(4, 12), 16, 3 पूर्ण,	/* AVB0_TXCREFCLK */
		अणु RCAR_GP_PIN(4, 11), 12, 3 पूर्ण,	/* AVB0_TD3 */
		अणु RCAR_GP_PIN(4, 10),  8, 3 पूर्ण,	/* AVB0_TD2 */
		अणु RCAR_GP_PIN(4,  9),  4, 3 पूर्ण,	/* AVB0_TD1*/
		अणु RCAR_GP_PIN(4,  8),  0, 3 पूर्ण,	/* AVB0_TD0 */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV2CTRL4", 0xe6060088) अणु
		अणु RCAR_GP_PIN(4, 23), 28, 3 पूर्ण,	/* PCIE2_CLKREQ_N */
		अणु RCAR_GP_PIN(4, 22), 24, 3 पूर्ण,	/* PCIE1_CLKREQ_N */
		अणु RCAR_GP_PIN(4, 21), 20, 3 पूर्ण,	/* PCIE0_CLKREQ_N */
		अणु RCAR_GP_PIN(4, 20), 16, 3 पूर्ण,	/* AVB0_AVTP_PPS */
		अणु RCAR_GP_PIN(4, 19), 12, 3 पूर्ण,	/* AVB0_AVTP_CAPTURE */
		अणु RCAR_GP_PIN(4, 18),  8, 3 पूर्ण,	/* AVB0_AVTP_MATCH */
		अणु RCAR_GP_PIN(4, 17),  4, 3 पूर्ण,	/* AVB0_LINK */
		अणु RCAR_GP_PIN(4, 16),  0, 3 पूर्ण,	/* AVB0_PHY_INT */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV3CTRL4", 0xe606008c) अणु
		अणु RCAR_GP_PIN(4, 26),  8, 3 पूर्ण,	/* AVS1 */
		अणु RCAR_GP_PIN(4, 25),  4, 3 पूर्ण,	/* AVS0 */
		अणु RCAR_GP_PIN(4, 24),  0, 3 पूर्ण,	/* PCIE3_CLKREQ_N */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV0CTRL5", 0xe6060880) अणु
		अणु RCAR_GP_PIN(5,  7), 28, 3 पूर्ण,	/* AVB1_TXC */
		अणु RCAR_GP_PIN(5,  6), 24, 3 पूर्ण,	/* AVB1_TX_CTL */
		अणु RCAR_GP_PIN(5,  5), 20, 3 पूर्ण,	/* AVB1_RD3 */
		अणु RCAR_GP_PIN(5,  4), 16, 3 पूर्ण,	/* AVB1_RD2 */
		अणु RCAR_GP_PIN(5,  3), 12, 3 पूर्ण,	/* AVB1_RD1 */
		अणु RCAR_GP_PIN(5,  2),  8, 3 पूर्ण,	/* AVB1_RD0 */
		अणु RCAR_GP_PIN(5,  1),  4, 3 पूर्ण,	/* AVB1_RXC */
		अणु RCAR_GP_PIN(5,  0),  0, 3 पूर्ण,	/* AVB1_RX_CTL */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV1CTRL5", 0xe6060884) अणु
		अणु RCAR_GP_PIN(5, 15), 28, 3 पूर्ण,	/* AVB1_MAGIC */
		अणु RCAR_GP_PIN(5, 14), 24, 3 पूर्ण,	/* AVB1_MDC */
		अणु RCAR_GP_PIN(5, 13), 20, 3 पूर्ण,	/* AVB1_MDIO */
		अणु RCAR_GP_PIN(5, 12), 16, 3 पूर्ण,	/* AVB1_TXCREFCLK */
		अणु RCAR_GP_PIN(5, 11), 12, 3 पूर्ण,	/* AVB1_TD3 */
		अणु RCAR_GP_PIN(5, 10),  8, 3 पूर्ण,	/* AVB1_TD2 */
		अणु RCAR_GP_PIN(5,  9),  4, 3 पूर्ण,	/* AVB1_TD1*/
		अणु RCAR_GP_PIN(5,  8),  0, 3 पूर्ण,	/* AVB1_TD0 */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV2CTRL5", 0xe6060888) अणु
		अणु RCAR_GP_PIN(5, 20), 16, 3 पूर्ण,	/* AVB1_AVTP_PPS */
		अणु RCAR_GP_PIN(5, 19), 12, 3 पूर्ण,	/* AVB1_AVTP_CAPTURE */
		अणु RCAR_GP_PIN(5, 18),  8, 3 पूर्ण,	/* AVB1_AVTP_MATCH */
		अणु RCAR_GP_PIN(5, 17),  4, 3 पूर्ण,	/* AVB1_LINK */
		अणु RCAR_GP_PIN(5, 16),  0, 3 पूर्ण,	/* AVB1_PHY_INT */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV0CTRL6", 0xe6068080) अणु
		अणु RCAR_GP_PIN(6,  7), 28, 3 पूर्ण,	/* AVB2_TXC */
		अणु RCAR_GP_PIN(6,  6), 24, 3 पूर्ण,	/* AVB2_TX_CTL */
		अणु RCAR_GP_PIN(6,  5), 20, 3 पूर्ण,	/* AVB2_RD3 */
		अणु RCAR_GP_PIN(6,  4), 16, 3 पूर्ण,	/* AVB2_RD2 */
		अणु RCAR_GP_PIN(6,  3), 12, 3 पूर्ण,	/* AVB2_RD1 */
		अणु RCAR_GP_PIN(6,  2),  8, 3 पूर्ण,	/* AVB2_RD0 */
		अणु RCAR_GP_PIN(6,  1),  4, 3 पूर्ण,	/* AVB2_RXC */
		अणु RCAR_GP_PIN(6,  0),  0, 3 पूर्ण,	/* AVB2_RX_CTL */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV1CTRL6", 0xe6068084) अणु
		अणु RCAR_GP_PIN(6, 15), 28, 3 पूर्ण,	/* AVB2_MAGIC */
		अणु RCAR_GP_PIN(6, 14), 24, 3 पूर्ण,	/* AVB2_MDC */
		अणु RCAR_GP_PIN(6, 13), 20, 3 पूर्ण,	/* AVB2_MDIO */
		अणु RCAR_GP_PIN(6, 12), 16, 3 पूर्ण,	/* AVB2_TXCREFCLK */
		अणु RCAR_GP_PIN(6, 11), 12, 3 पूर्ण,	/* AVB2_TD3 */
		अणु RCAR_GP_PIN(6, 10),  8, 3 पूर्ण,	/* AVB2_TD2 */
		अणु RCAR_GP_PIN(6,  9),  4, 3 पूर्ण,	/* AVB2_TD1*/
		अणु RCAR_GP_PIN(6,  8),  0, 3 पूर्ण,	/* AVB2_TD0 */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV2CTRL6", 0xe6068088) अणु
		अणु RCAR_GP_PIN(6, 20), 16, 3 पूर्ण,	/* AVB2_AVTP_PPS */
		अणु RCAR_GP_PIN(6, 19), 12, 3 पूर्ण,	/* AVB2_AVTP_CAPTURE */
		अणु RCAR_GP_PIN(6, 18),  8, 3 पूर्ण,	/* AVB2_AVTP_MATCH */
		अणु RCAR_GP_PIN(6, 17),  4, 3 पूर्ण,	/* AVB2_LINK */
		अणु RCAR_GP_PIN(6, 16),  0, 3 पूर्ण,	/* AVB2_PHY_INT */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV0CTRL7", 0xe6068880) अणु
		अणु RCAR_GP_PIN(7,  7), 28, 3 पूर्ण,	/* AVB3_TXC */
		अणु RCAR_GP_PIN(7,  6), 24, 3 पूर्ण,	/* AVB3_TX_CTL */
		अणु RCAR_GP_PIN(7,  5), 20, 3 पूर्ण,	/* AVB3_RD3 */
		अणु RCAR_GP_PIN(7,  4), 16, 3 पूर्ण,	/* AVB3_RD2 */
		अणु RCAR_GP_PIN(7,  3), 12, 3 पूर्ण,	/* AVB3_RD1 */
		अणु RCAR_GP_PIN(7,  2),  8, 3 पूर्ण,	/* AVB3_RD0 */
		अणु RCAR_GP_PIN(7,  1),  4, 3 पूर्ण,	/* AVB3_RXC */
		अणु RCAR_GP_PIN(7,  0),  0, 3 पूर्ण,	/* AVB3_RX_CTL */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV1CTRL7", 0xe6068884) अणु
		अणु RCAR_GP_PIN(7, 15), 28, 3 पूर्ण,	/* AVB3_MAGIC */
		अणु RCAR_GP_PIN(7, 14), 24, 3 पूर्ण,	/* AVB3_MDC */
		अणु RCAR_GP_PIN(7, 13), 20, 3 पूर्ण,	/* AVB3_MDIO */
		अणु RCAR_GP_PIN(7, 12), 16, 3 पूर्ण,	/* AVB3_TXCREFCLK */
		अणु RCAR_GP_PIN(7, 11), 12, 3 पूर्ण,	/* AVB3_TD3 */
		अणु RCAR_GP_PIN(7, 10),  8, 3 पूर्ण,	/* AVB3_TD2 */
		अणु RCAR_GP_PIN(7,  9),  4, 3 पूर्ण,	/* AVB3_TD1*/
		अणु RCAR_GP_PIN(7,  8),  0, 3 पूर्ण,	/* AVB3_TD0 */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV2CTRL7", 0xe6068888) अणु
		अणु RCAR_GP_PIN(7, 20), 16, 3 पूर्ण,	/* AVB3_AVTP_PPS */
		अणु RCAR_GP_PIN(7, 19), 12, 3 पूर्ण,	/* AVB3_AVTP_CAPTURE */
		अणु RCAR_GP_PIN(7, 18),  8, 3 पूर्ण,	/* AVB3_AVTP_MATCH */
		अणु RCAR_GP_PIN(7, 17),  4, 3 पूर्ण,	/* AVB3_LINK */
		अणु RCAR_GP_PIN(7, 16),  0, 3 पूर्ण,	/* AVB3_PHY_INT */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV0CTRL8", 0xe6069080) अणु
		अणु RCAR_GP_PIN(8,  7), 28, 3 पूर्ण,	/* AVB4_TXC */
		अणु RCAR_GP_PIN(8,  6), 24, 3 पूर्ण,	/* AVB4_TX_CTL */
		अणु RCAR_GP_PIN(8,  5), 20, 3 पूर्ण,	/* AVB4_RD3 */
		अणु RCAR_GP_PIN(8,  4), 16, 3 पूर्ण,	/* AVB4_RD2 */
		अणु RCAR_GP_PIN(8,  3), 12, 3 पूर्ण,	/* AVB4_RD1 */
		अणु RCAR_GP_PIN(8,  2),  8, 3 पूर्ण,	/* AVB4_RD0 */
		अणु RCAR_GP_PIN(8,  1),  4, 3 पूर्ण,	/* AVB4_RXC */
		अणु RCAR_GP_PIN(8,  0),  0, 3 पूर्ण,	/* AVB4_RX_CTL */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV1CTRL8", 0xe6069084) अणु
		अणु RCAR_GP_PIN(8, 15), 28, 3 पूर्ण,	/* AVB4_MAGIC */
		अणु RCAR_GP_PIN(8, 14), 24, 3 पूर्ण,	/* AVB4_MDC */
		अणु RCAR_GP_PIN(8, 13), 20, 3 पूर्ण,	/* AVB4_MDIO */
		अणु RCAR_GP_PIN(8, 12), 16, 3 पूर्ण,	/* AVB4_TXCREFCLK */
		अणु RCAR_GP_PIN(8, 11), 12, 3 पूर्ण,	/* AVB4_TD3 */
		अणु RCAR_GP_PIN(8, 10),  8, 3 पूर्ण,	/* AVB4_TD2 */
		अणु RCAR_GP_PIN(8,  9),  4, 3 पूर्ण,	/* AVB4_TD1*/
		अणु RCAR_GP_PIN(8,  8),  0, 3 पूर्ण,	/* AVB4_TD0 */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV2CTRL8", 0xe6069088) अणु
		अणु RCAR_GP_PIN(8, 20), 16, 3 पूर्ण,	/* AVB4_AVTP_PPS */
		अणु RCAR_GP_PIN(8, 19), 12, 3 पूर्ण,	/* AVB4_AVTP_CAPTURE */
		अणु RCAR_GP_PIN(8, 18),  8, 3 पूर्ण,	/* AVB4_AVTP_MATCH */
		अणु RCAR_GP_PIN(8, 17),  4, 3 पूर्ण,	/* AVB4_LINK */
		अणु RCAR_GP_PIN(8, 16),  0, 3 पूर्ण,	/* AVB4_PHY_INT */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV0CTRL9", 0xe6069880) अणु
		अणु RCAR_GP_PIN(9,  7), 28, 3 पूर्ण,	/* AVB5_TXC */
		अणु RCAR_GP_PIN(9,  6), 24, 3 पूर्ण,	/* AVB5_TX_CTL */
		अणु RCAR_GP_PIN(9,  5), 20, 3 पूर्ण,	/* AVB5_RD3 */
		अणु RCAR_GP_PIN(9,  4), 16, 3 पूर्ण,	/* AVB5_RD2 */
		अणु RCAR_GP_PIN(9,  3), 12, 3 पूर्ण,	/* AVB5_RD1 */
		अणु RCAR_GP_PIN(9,  2),  8, 3 पूर्ण,	/* AVB5_RD0 */
		अणु RCAR_GP_PIN(9,  1),  4, 3 पूर्ण,	/* AVB5_RXC */
		अणु RCAR_GP_PIN(9,  0),  0, 3 पूर्ण,	/* AVB5_RX_CTL */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV1CTRL9", 0xe6069884) अणु
		अणु RCAR_GP_PIN(9, 15), 28, 3 पूर्ण,	/* AVB5_MAGIC */
		अणु RCAR_GP_PIN(9, 14), 24, 3 पूर्ण,	/* AVB5_MDC */
		अणु RCAR_GP_PIN(9, 13), 20, 3 पूर्ण,	/* AVB5_MDIO */
		अणु RCAR_GP_PIN(9, 12), 16, 3 पूर्ण,	/* AVB5_TXCREFCLK */
		अणु RCAR_GP_PIN(9, 11), 12, 3 पूर्ण,	/* AVB5_TD3 */
		अणु RCAR_GP_PIN(9, 10),  8, 3 पूर्ण,	/* AVB5_TD2 */
		अणु RCAR_GP_PIN(9,  9),  4, 3 पूर्ण,	/* AVB5_TD1*/
		अणु RCAR_GP_PIN(9,  8),  0, 3 पूर्ण,	/* AVB5_TD0 */
	पूर्ण पूर्ण,
	अणु PINMUX_DRIVE_REG("DRV2CTRL9", 0xe6069888) अणु
		अणु RCAR_GP_PIN(9, 20), 16, 3 पूर्ण,	/* AVB5_AVTP_PPS */
		अणु RCAR_GP_PIN(9, 19), 12, 3 पूर्ण,	/* AVB5_AVTP_CAPTURE */
		अणु RCAR_GP_PIN(9, 18),  8, 3 पूर्ण,	/* AVB5_AVTP_MATCH */
		अणु RCAR_GP_PIN(9, 17),  4, 3 पूर्ण,	/* AVB5_LINK */
		अणु RCAR_GP_PIN(9, 16),  0, 3 पूर्ण,	/* AVB5_PHY_INT */
	पूर्ण पूर्ण,
	अणु पूर्ण,
पूर्ण;

क्रमागत ioctrl_regs अणु
	POC0,
	POC1,
	POC2,
	POC4,
	POC5,
	POC6,
	POC7,
	POC8,
	POC9,
	TD1SEL0,
पूर्ण;

अटल स्थिर काष्ठा pinmux_ioctrl_reg pinmux_ioctrl_regs[] = अणु
	[POC0] = अणु 0xe60580a0, पूर्ण,
	[POC1] = अणु 0xe60500a0, पूर्ण,
	[POC2] = अणु 0xe60508a0, पूर्ण,
	[POC4] = अणु 0xe60600a0, पूर्ण,
	[POC5] = अणु 0xe60608a0, पूर्ण,
	[POC6] = अणु 0xe60680a0, पूर्ण,
	[POC7] = अणु 0xe60688a0, पूर्ण,
	[POC8] = अणु 0xe60690a0, पूर्ण,
	[POC9] = अणु 0xe60698a0, पूर्ण,
	[TD1SEL0] = अणु 0xe6058124, पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल पूर्णांक r8a779a0_pin_to_pocctrl(काष्ठा sh_pfc *pfc, अचिन्हित पूर्णांक pin,
				   u32 *pocctrl)
अणु
	पूर्णांक bit = pin & 0x1f;

	*pocctrl = pinmux_ioctrl_regs[POC0].reg;
	अगर (pin >= RCAR_GP_PIN(0, 15) && pin <= RCAR_GP_PIN(0, 27))
		वापस bit;

	*pocctrl = pinmux_ioctrl_regs[POC1].reg;
	अगर (pin >= RCAR_GP_PIN(1, 0) && pin <= RCAR_GP_PIN(1, 30))
		वापस bit;

	*pocctrl = pinmux_ioctrl_regs[POC2].reg;
	अगर (pin >= RCAR_GP_PIN(2, 2) && pin <= RCAR_GP_PIN(2, 15))
		वापस bit;

	*pocctrl = pinmux_ioctrl_regs[POC4].reg;
	अगर (pin >= RCAR_GP_PIN(4, 0) && pin <= RCAR_GP_PIN(4, 17))
		वापस bit;

	*pocctrl = pinmux_ioctrl_regs[POC5].reg;
	अगर (pin >= RCAR_GP_PIN(5, 0) && pin <= RCAR_GP_PIN(5, 17))
		वापस bit;

	*pocctrl = pinmux_ioctrl_regs[POC6].reg;
	अगर (pin >= RCAR_GP_PIN(6, 0) && pin <= RCAR_GP_PIN(6, 17))
		वापस bit;

	*pocctrl = pinmux_ioctrl_regs[POC7].reg;
	अगर (pin >= RCAR_GP_PIN(7, 0) && pin <= RCAR_GP_PIN(7, 17))
		वापस bit;

	*pocctrl = pinmux_ioctrl_regs[POC8].reg;
	अगर (pin >= RCAR_GP_PIN(8, 0) && pin <= RCAR_GP_PIN(8, 17))
		वापस bit;

	*pocctrl = pinmux_ioctrl_regs[POC9].reg;
	अगर (pin >= RCAR_GP_PIN(9, 0) && pin <= RCAR_GP_PIN(9, 17))
		वापस bit;

	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा pinmux_bias_reg pinmux_bias_regs[] = अणु
	अणु PINMUX_BIAS_REG("PUEN0", 0xe60580c0, "PUD0", 0xe60580e0) अणु
		[ 0] = RCAR_GP_PIN(0,  0),	/* QSPI0_SPCLK */
		[ 1] = RCAR_GP_PIN(0,  1),	/* QSPI0_MOSI_IO0 */
		[ 2] = RCAR_GP_PIN(0,  2),	/* QSPI0_MISO_IO1 */
		[ 3] = RCAR_GP_PIN(0,  3),	/* QSPI0_IO2 */
		[ 4] = RCAR_GP_PIN(0,  4),	/* QSPI0_IO3 */
		[ 5] = RCAR_GP_PIN(0,  5),	/* QSPI0_SSL */
		[ 6] = RCAR_GP_PIN(0,  6),	/* QSPI1_SPCLK */
		[ 7] = RCAR_GP_PIN(0,  7),	/* QSPI1_MOSI_IO0 */
		[ 8] = RCAR_GP_PIN(0,  8),	/* QSPI1_MISO_IO1 */
		[ 9] = RCAR_GP_PIN(0,  9),	/* QSPI1_IO2 */
		[10] = RCAR_GP_PIN(0, 10),	/* QSPI1_IO3 */
		[11] = RCAR_GP_PIN(0, 11),	/* QSPI1_SSL */
		[12] = RCAR_GP_PIN(0, 12),	/* RPC_RESET_N */
		[13] = RCAR_GP_PIN(0, 13),	/* RPC_WP_N */
		[14] = RCAR_GP_PIN(0, 14),	/* RPC_INT_N */
		[15] = RCAR_GP_PIN(0, 15),	/* SD_WP */
		[16] = RCAR_GP_PIN(0, 16),	/* SD_CD */
		[17] = RCAR_GP_PIN(0, 17),	/* MMC_DS */
		[18] = RCAR_GP_PIN(0, 18),	/* MMC_SD_CMD */
		[19] = RCAR_GP_PIN(0, 19),	/* MMC_SD_D0 */
		[20] = RCAR_GP_PIN(0, 20),	/* MMC_SD_D1 */
		[21] = RCAR_GP_PIN(0, 21),	/* MMC_SD_D2 */
		[22] = RCAR_GP_PIN(0, 22),	/* MMC_SD_D3 */
		[23] = RCAR_GP_PIN(0, 23),	/* MMC_SD_CLK */
		[24] = RCAR_GP_PIN(0, 24),	/* MMC_D4 */
		[25] = RCAR_GP_PIN(0, 25),	/* MMC_D5 */
		[26] = RCAR_GP_PIN(0, 26),	/* MMC_D6 */
		[27] = RCAR_GP_PIN(0, 27),	/* MMC_D7 */
		[28] = SH_PFC_PIN_NONE,
		[29] = SH_PFC_PIN_NONE,
		[30] = SH_PFC_PIN_NONE,
		[31] = SH_PFC_PIN_NONE,
	पूर्ण पूर्ण,
	अणु PINMUX_BIAS_REG("PUEN1", 0xe60500c0, "PUD1", 0xe60500e0) अणु
		[ 0] = RCAR_GP_PIN(1,  0),	/* SCIF_CLK */
		[ 1] = RCAR_GP_PIN(1,  1),	/* HRX0 */
		[ 2] = RCAR_GP_PIN(1,  2),	/* HSCK0 */
		[ 3] = RCAR_GP_PIN(1,  3),	/* HRTS0_N */
		[ 4] = RCAR_GP_PIN(1,  4),	/* HCTS0_N */
		[ 5] = RCAR_GP_PIN(1,  5),	/* HTX0 */
		[ 6] = RCAR_GP_PIN(1,  6),	/* MSIOF0_RXD */
		[ 7] = RCAR_GP_PIN(1,  7),	/* MSIOF0_TXD */
		[ 8] = RCAR_GP_PIN(1,  8),	/* MSIOF0_SCK */
		[ 9] = RCAR_GP_PIN(1,  9),	/* MSIOF0_SYNC */
		[10] = RCAR_GP_PIN(1, 10),	/* MSIOF0_SS1 */
		[11] = RCAR_GP_PIN(1, 11),	/* MSIOF0_SS2 */
		[12] = RCAR_GP_PIN(1, 12),	/* MSIOF1_RXD */
		[13] = RCAR_GP_PIN(1, 13),	/* MSIOF1_TXD */
		[14] = RCAR_GP_PIN(1, 14),	/* MSIOF1_SCK */
		[15] = RCAR_GP_PIN(1, 15),	/* MSIOF1_SYNC */
		[16] = RCAR_GP_PIN(1, 16),	/* MSIOF1_SS1 */
		[17] = RCAR_GP_PIN(1, 17),	/* MSIOF1_SS2 */
		[18] = RCAR_GP_PIN(1, 18),	/* MSIOF2_RXD */
		[19] = RCAR_GP_PIN(1, 19),	/* MSIOF2_TXD */
		[20] = RCAR_GP_PIN(1, 20),	/* MSIOF2_SCK */
		[21] = RCAR_GP_PIN(1, 21),	/* MSIOF2_SYNC */
		[22] = RCAR_GP_PIN(1, 22),	/* MSIOF2_SS1 */
		[23] = RCAR_GP_PIN(1, 23),	/* MSIOF2_SS2 */
		[24] = RCAR_GP_PIN(1, 24),	/* IRQ0 */
		[25] = RCAR_GP_PIN(1, 25),	/* IRQ1 */
		[26] = RCAR_GP_PIN(1, 26),	/* IRQ2 */
		[27] = RCAR_GP_PIN(1, 27),	/* IRQ3 */
		[28] = RCAR_GP_PIN(1, 28),	/* GP1_28 */
		[29] = RCAR_GP_PIN(1, 29),	/* GP1_29 */
		[30] = RCAR_GP_PIN(1, 30),	/* GP1_30 */
		[31] = SH_PFC_PIN_NONE,
	पूर्ण पूर्ण,
	अणु PINMUX_BIAS_REG("PUEN2", 0xe60508c0, "PUD2", 0xe60508e0) अणु
		[ 0] = RCAR_GP_PIN(2,  0),	/* IPC_CLKIN */
		[ 1] = RCAR_GP_PIN(2,  1),	/* IPC_CLKOUT */
		[ 2] = RCAR_GP_PIN(2,  2),	/* GP2_02 */
		[ 3] = RCAR_GP_PIN(2,  3),	/* GP2_03 */
		[ 4] = RCAR_GP_PIN(2,  4),	/* GP2_04 */
		[ 5] = RCAR_GP_PIN(2,  5),	/* GP2_05 */
		[ 6] = RCAR_GP_PIN(2,  6),	/* GP2_06 */
		[ 7] = RCAR_GP_PIN(2,  7),	/* GP2_07 */
		[ 8] = RCAR_GP_PIN(2,  8),	/* GP2_08 */
		[ 9] = RCAR_GP_PIN(2,  9),	/* GP2_09 */
		[10] = RCAR_GP_PIN(2, 10),	/* GP2_10 */
		[11] = RCAR_GP_PIN(2, 11),	/* GP2_11 */
		[12] = RCAR_GP_PIN(2, 12),	/* GP2_12 */
		[13] = RCAR_GP_PIN(2, 13),	/* GP2_13 */
		[14] = RCAR_GP_PIN(2, 14),	/* GP2_14 */
		[15] = RCAR_GP_PIN(2, 15),	/* GP2_15 */
		[16] = RCAR_GP_PIN(2, 16),	/* FXR_TXDA_A */
		[17] = RCAR_GP_PIN(2, 17),	/* RXDA_EXTFXR_A */
		[18] = RCAR_GP_PIN(2, 18),	/* FXR_TXDB */
		[19] = RCAR_GP_PIN(2, 19),	/* RXDB_EXTFXR */
		[20] = RCAR_GP_PIN(2, 20),	/* CLK_EXTFXR */
		[21] = RCAR_GP_PIN(2, 21),	/* TPU0TO0 */
		[22] = RCAR_GP_PIN(2, 22),	/* TPU0TO1 */
		[23] = RCAR_GP_PIN(2, 23),	/* TCLK1_A */
		[24] = RCAR_GP_PIN(2, 24),	/* TCLK2_A */
		[25] = SH_PFC_PIN_NONE,
		[26] = SH_PFC_PIN_NONE,
		[27] = SH_PFC_PIN_NONE,
		[28] = SH_PFC_PIN_NONE,
		[29] = SH_PFC_PIN_NONE,
		[30] = SH_PFC_PIN_NONE,
		[31] = SH_PFC_PIN_NONE,
	पूर्ण पूर्ण,
	अणु PINMUX_BIAS_REG("PUEN3", 0xe60588c0, "PUD3", 0xe60588e0) अणु
		[ 0] = RCAR_GP_PIN(3,  0),	/* CAN_CLK */
		[ 1] = RCAR_GP_PIN(3,  1),	/* CANFD0_TX */
		[ 2] = RCAR_GP_PIN(3,  2),	/* CANFD0_RX */
		[ 3] = RCAR_GP_PIN(3,  3),	/* CANFD1_TX */
		[ 4] = RCAR_GP_PIN(3,  4),	/* CANFD1_RX */
		[ 5] = RCAR_GP_PIN(3,  5),	/* CANFD2_TX */
		[ 6] = RCAR_GP_PIN(3,  6),	/* CANFD2_RX */
		[ 7] = RCAR_GP_PIN(3,  7),	/* CANFD3_TX */
		[ 8] = RCAR_GP_PIN(3,  8),	/* CANFD3_RX */
		[ 9] = RCAR_GP_PIN(3,  9),	/* CANFD4_TX */
		[10] = RCAR_GP_PIN(3, 10),	/* CANFD4_RX */
		[11] = RCAR_GP_PIN(3, 11),	/* CANFD5_TX */
		[12] = RCAR_GP_PIN(3, 12),	/* CANFD5_RX */
		[13] = RCAR_GP_PIN(3, 13),	/* CANFD6_TX */
		[14] = RCAR_GP_PIN(3, 14),	/* CANFD6_RX */
		[15] = RCAR_GP_PIN(3, 15),	/* CANFD7_TX */
		[16] = RCAR_GP_PIN(3, 16),	/* CANFD7_RX */
		[17] = SH_PFC_PIN_NONE,
		[18] = SH_PFC_PIN_NONE,
		[19] = SH_PFC_PIN_NONE,
		[20] = SH_PFC_PIN_NONE,
		[21] = SH_PFC_PIN_NONE,
		[22] = SH_PFC_PIN_NONE,
		[23] = SH_PFC_PIN_NONE,
		[24] = SH_PFC_PIN_NONE,
		[25] = SH_PFC_PIN_NONE,
		[26] = SH_PFC_PIN_NONE,
		[27] = SH_PFC_PIN_NONE,
		[28] = SH_PFC_PIN_NONE,
		[29] = SH_PFC_PIN_NONE,
		[30] = SH_PFC_PIN_NONE,
		[31] = SH_PFC_PIN_NONE,
	पूर्ण पूर्ण,
	अणु PINMUX_BIAS_REG("PUEN4", 0xe60600c0, "PUD4", 0xe60600e0) अणु
		[ 0] = RCAR_GP_PIN(4,  0),	/* AVB0_RX_CTL */
		[ 1] = RCAR_GP_PIN(4,  1),	/* AVB0_RXC */
		[ 2] = RCAR_GP_PIN(4,  2),	/* AVB0_RD0 */
		[ 3] = RCAR_GP_PIN(4,  3),	/* AVB0_RD1 */
		[ 4] = RCAR_GP_PIN(4,  4),	/* AVB0_RD2 */
		[ 5] = RCAR_GP_PIN(4,  5),	/* AVB0_RD3 */
		[ 6] = RCAR_GP_PIN(4,  6),	/* AVB0_TX_CTL */
		[ 7] = RCAR_GP_PIN(4,  7),	/* AVB0_TXC */
		[ 8] = RCAR_GP_PIN(4,  8),	/* AVB0_TD0 */
		[ 9] = RCAR_GP_PIN(4,  9),	/* AVB0_TD1 */
		[10] = RCAR_GP_PIN(4, 10),	/* AVB0_TD2 */
		[11] = RCAR_GP_PIN(4, 11),	/* AVB0_TD3 */
		[12] = RCAR_GP_PIN(4, 12),	/* AVB0_TXREFCLK */
		[13] = RCAR_GP_PIN(4, 13),	/* AVB0_MDIO */
		[14] = RCAR_GP_PIN(4, 14),	/* AVB0_MDC */
		[15] = RCAR_GP_PIN(4, 15),	/* AVB0_MAGIC */
		[16] = RCAR_GP_PIN(4, 16),	/* AVB0_PHY_INT */
		[17] = RCAR_GP_PIN(4, 17),	/* AVB0_LINK */
		[18] = RCAR_GP_PIN(4, 18),	/* AVB0_AVTP_MATCH */
		[19] = RCAR_GP_PIN(4, 19),	/* AVB0_AVTP_CAPTURE */
		[20] = RCAR_GP_PIN(4, 20),	/* AVB0_AVTP_PPS */
		[21] = RCAR_GP_PIN(4, 21),	/* PCIE0_CLKREQ_N */
		[22] = RCAR_GP_PIN(4, 22),	/* PCIE1_CLKREQ_N */
		[23] = RCAR_GP_PIN(4, 23),	/* PCIE2_CLKREQ_N */
		[24] = RCAR_GP_PIN(4, 24),	/* PCIE3_CLKREQ_N */
		[25] = RCAR_GP_PIN(4, 25),	/* AVS0 */
		[26] = RCAR_GP_PIN(4, 26),	/* AVS1 */
		[27] = SH_PFC_PIN_NONE,
		[28] = SH_PFC_PIN_NONE,
		[29] = SH_PFC_PIN_NONE,
		[30] = SH_PFC_PIN_NONE,
		[31] = SH_PFC_PIN_NONE,
	पूर्ण पूर्ण,
	अणु PINMUX_BIAS_REG("PUEN5", 0xe60608c0, "PUD5", 0xe60608e0) अणु
		[ 0] = RCAR_GP_PIN(5,  0),	/* AVB1_RX_CTL */
		[ 1] = RCAR_GP_PIN(5,  1),	/* AVB1_RXC */
		[ 2] = RCAR_GP_PIN(5,  2),	/* AVB1_RD0 */
		[ 3] = RCAR_GP_PIN(5,  3),	/* AVB1_RD1 */
		[ 4] = RCAR_GP_PIN(5,  4),	/* AVB1_RD2 */
		[ 5] = RCAR_GP_PIN(5,  5),	/* AVB1_RD3 */
		[ 6] = RCAR_GP_PIN(5,  6),	/* AVB1_TX_CTL */
		[ 7] = RCAR_GP_PIN(5,  7),	/* AVB1_TXC */
		[ 8] = RCAR_GP_PIN(5,  8),	/* AVB1_TD0 */
		[ 9] = RCAR_GP_PIN(5,  9),	/* AVB1_TD1 */
		[10] = RCAR_GP_PIN(5, 10),	/* AVB1_TD2 */
		[11] = RCAR_GP_PIN(5, 11),	/* AVB1_TD3 */
		[12] = RCAR_GP_PIN(5, 12),	/* AVB1_TXCREFCLK */
		[13] = RCAR_GP_PIN(5, 13),	/* AVB1_MDIO */
		[14] = RCAR_GP_PIN(5, 14),	/* AVB1_MDC */
		[15] = RCAR_GP_PIN(5, 15),	/* AVB1_MAGIC */
		[16] = RCAR_GP_PIN(5, 16),	/* AVB1_PHY_INT */
		[17] = RCAR_GP_PIN(5, 17),	/* AVB1_LINK */
		[18] = RCAR_GP_PIN(5, 18),	/* AVB1_AVTP_MATCH */
		[19] = RCAR_GP_PIN(5, 19),	/* AVB1_AVTP_CAPTURE */
		[20] = RCAR_GP_PIN(5, 20),	/* AVB1_AVTP_PPS */
		[21] = SH_PFC_PIN_NONE,
		[22] = SH_PFC_PIN_NONE,
		[23] = SH_PFC_PIN_NONE,
		[24] = SH_PFC_PIN_NONE,
		[25] = SH_PFC_PIN_NONE,
		[26] = SH_PFC_PIN_NONE,
		[27] = SH_PFC_PIN_NONE,
		[28] = SH_PFC_PIN_NONE,
		[29] = SH_PFC_PIN_NONE,
		[30] = SH_PFC_PIN_NONE,
		[31] = SH_PFC_PIN_NONE,
	पूर्ण पूर्ण,
	अणु PINMUX_BIAS_REG("PUEN6", 0xe60680c0, "PUD6", 0xe60680e0) अणु
		[ 0] = RCAR_GP_PIN(6,  0),	/* AVB2_RX_CTL */
		[ 1] = RCAR_GP_PIN(6,  1),	/* AVB2_RXC */
		[ 2] = RCAR_GP_PIN(6,  2),	/* AVB2_RD0 */
		[ 3] = RCAR_GP_PIN(6,  3),	/* AVB2_RD1 */
		[ 4] = RCAR_GP_PIN(6,  4),	/* AVB2_RD2 */
		[ 5] = RCAR_GP_PIN(6,  5),	/* AVB2_RD3 */
		[ 6] = RCAR_GP_PIN(6,  6),	/* AVB2_TX_CTL */
		[ 7] = RCAR_GP_PIN(6,  7),	/* AVB2_TXC */
		[ 8] = RCAR_GP_PIN(6,  8),	/* AVB2_TD0 */
		[ 9] = RCAR_GP_PIN(6,  9),	/* AVB2_TD1 */
		[10] = RCAR_GP_PIN(6, 10),	/* AVB2_TD2 */
		[11] = RCAR_GP_PIN(6, 11),	/* AVB2_TD3 */
		[12] = RCAR_GP_PIN(6, 12),	/* AVB2_TXCREFCLK */
		[13] = RCAR_GP_PIN(6, 13),	/* AVB2_MDIO */
		[14] = RCAR_GP_PIN(6, 14),	/* AVB2_MDC*/
		[15] = RCAR_GP_PIN(6, 15),	/* AVB2_MAGIC */
		[16] = RCAR_GP_PIN(6, 16),	/* AVB2_PHY_INT */
		[17] = RCAR_GP_PIN(6, 17),	/* AVB2_LINK */
		[18] = RCAR_GP_PIN(6, 18),	/* AVB2_AVTP_MATCH */
		[19] = RCAR_GP_PIN(6, 19),	/* AVB2_AVTP_CAPTURE */
		[20] = RCAR_GP_PIN(6, 20),	/* AVB2_AVTP_PPS */
		[21] = SH_PFC_PIN_NONE,
		[22] = SH_PFC_PIN_NONE,
		[23] = SH_PFC_PIN_NONE,
		[24] = SH_PFC_PIN_NONE,
		[25] = SH_PFC_PIN_NONE,
		[26] = SH_PFC_PIN_NONE,
		[27] = SH_PFC_PIN_NONE,
		[28] = SH_PFC_PIN_NONE,
		[29] = SH_PFC_PIN_NONE,
		[30] = SH_PFC_PIN_NONE,
		[31] = SH_PFC_PIN_NONE,
	पूर्ण पूर्ण,
	अणु PINMUX_BIAS_REG("PUEN7", 0xe60688c0, "PUD7", 0xe60688e0) अणु
		[ 0] = RCAR_GP_PIN(7,  0),	/* AVB3_RX_CTL */
		[ 1] = RCAR_GP_PIN(7,  1),	/* AVB3_RXC */
		[ 2] = RCAR_GP_PIN(7,  2),	/* AVB3_RD0 */
		[ 3] = RCAR_GP_PIN(7,  3),	/* AVB3_RD1 */
		[ 4] = RCAR_GP_PIN(7,  4),	/* AVB3_RD2 */
		[ 5] = RCAR_GP_PIN(7,  5),	/* AVB3_RD3 */
		[ 6] = RCAR_GP_PIN(7,  6),	/* AVB3_TX_CTL */
		[ 7] = RCAR_GP_PIN(7,  7),	/* AVB3_TXC */
		[ 8] = RCAR_GP_PIN(7,  8),	/* AVB3_TD0 */
		[ 9] = RCAR_GP_PIN(7,  9),	/* AVB3_TD1 */
		[10] = RCAR_GP_PIN(7, 10),	/* AVB3_TD2 */
		[11] = RCAR_GP_PIN(7, 11),	/* AVB3_TD3 */
		[12] = RCAR_GP_PIN(7, 12),	/* AVB3_TXCREFCLK */
		[13] = RCAR_GP_PIN(7, 13),	/* AVB3_MDIO */
		[14] = RCAR_GP_PIN(7, 14),	/* AVB3_MDC */
		[15] = RCAR_GP_PIN(7, 15),	/* AVB3_MAGIC */
		[16] = RCAR_GP_PIN(7, 16),	/* AVB3_PHY_INT */
		[17] = RCAR_GP_PIN(7, 17),	/* AVB3_LINK */
		[18] = RCAR_GP_PIN(7, 18),	/* AVB3_AVTP_MATCH */
		[19] = RCAR_GP_PIN(7, 19),	/* AVB3_AVTP_CAPTURE */
		[20] = RCAR_GP_PIN(7, 20),	/* AVB3_AVTP_PPS */
		[21] = SH_PFC_PIN_NONE,
		[22] = SH_PFC_PIN_NONE,
		[23] = SH_PFC_PIN_NONE,
		[24] = SH_PFC_PIN_NONE,
		[25] = SH_PFC_PIN_NONE,
		[26] = SH_PFC_PIN_NONE,
		[27] = SH_PFC_PIN_NONE,
		[28] = SH_PFC_PIN_NONE,
		[29] = SH_PFC_PIN_NONE,
		[30] = SH_PFC_PIN_NONE,
		[31] = SH_PFC_PIN_NONE,
	पूर्ण पूर्ण,
	अणु PINMUX_BIAS_REG("PUEN8", 0xe60690c0, "PUD8", 0xe60690e0) अणु
		[ 0] = RCAR_GP_PIN(8,  0),	/* AVB4_RX_CTL */
		[ 1] = RCAR_GP_PIN(8,  1),	/* AVB4_RXC */
		[ 2] = RCAR_GP_PIN(8,  2),	/* AVB4_RD0 */
		[ 3] = RCAR_GP_PIN(8,  3),	/* AVB4_RD1 */
		[ 4] = RCAR_GP_PIN(8,  4),	/* AVB4_RD2 */
		[ 5] = RCAR_GP_PIN(8,  5),	/* AVB4_RD3 */
		[ 6] = RCAR_GP_PIN(8,  6),	/* AVB4_TX_CTL */
		[ 7] = RCAR_GP_PIN(8,  7),	/* AVB4_TXC */
		[ 8] = RCAR_GP_PIN(8,  8),	/* AVB4_TD0 */
		[ 9] = RCAR_GP_PIN(8,  9),	/* AVB4_TD1 */
		[10] = RCAR_GP_PIN(8, 10),	/* AVB4_TD2 */
		[11] = RCAR_GP_PIN(8, 11),	/* AVB4_TD3 */
		[12] = RCAR_GP_PIN(8, 12),	/* AVB4_TXCREFCLK */
		[13] = RCAR_GP_PIN(8, 13),	/* AVB4_MDIO */
		[14] = RCAR_GP_PIN(8, 14),	/* AVB4_MDC */
		[15] = RCAR_GP_PIN(8, 15),	/* AVB4_MAGIC */
		[16] = RCAR_GP_PIN(8, 16),	/* AVB4_PHY_INT */
		[17] = RCAR_GP_PIN(8, 17),	/* AVB4_LINK */
		[18] = RCAR_GP_PIN(8, 18),	/* AVB4_AVTP_MATCH */
		[19] = RCAR_GP_PIN(8, 19),	/* AVB4_AVTP_CAPTURE */
		[20] = RCAR_GP_PIN(8, 20),	/* AVB4_AVTP_PPS */
		[21] = SH_PFC_PIN_NONE,
		[22] = SH_PFC_PIN_NONE,
		[23] = SH_PFC_PIN_NONE,
		[24] = SH_PFC_PIN_NONE,
		[25] = SH_PFC_PIN_NONE,
		[26] = SH_PFC_PIN_NONE,
		[27] = SH_PFC_PIN_NONE,
		[28] = SH_PFC_PIN_NONE,
		[29] = SH_PFC_PIN_NONE,
		[30] = SH_PFC_PIN_NONE,
		[31] = SH_PFC_PIN_NONE,
	पूर्ण पूर्ण,
	अणु PINMUX_BIAS_REG("PUEN9", 0xe60698c0, "PUD9", 0xe60698e0) अणु
		[ 0] = RCAR_GP_PIN(9,  0),	/* AVB5_RX_CTL */
		[ 1] = RCAR_GP_PIN(9,  1),	/* AVB5_RXC */
		[ 2] = RCAR_GP_PIN(9,  2),	/* AVB5_RD0 */
		[ 3] = RCAR_GP_PIN(9,  3),	/* AVB5_RD1 */
		[ 4] = RCAR_GP_PIN(9,  4),	/* AVB5_RD2 */
		[ 5] = RCAR_GP_PIN(9,  5),	/* AVB5_RD3 */
		[ 6] = RCAR_GP_PIN(9,  6),	/* AVB5_TX_CTL */
		[ 7] = RCAR_GP_PIN(9,  7),	/* AVB5_TXC */
		[ 8] = RCAR_GP_PIN(9,  8),	/* AVB5_TD0 */
		[ 9] = RCAR_GP_PIN(9,  9),	/* AVB5_TD1 */
		[10] = RCAR_GP_PIN(9, 10),	/* AVB5_TD2 */
		[11] = RCAR_GP_PIN(9, 11),	/* AVB5_TD3 */
		[12] = RCAR_GP_PIN(9, 12),	/* AVB5_TXCREFCLK */
		[13] = RCAR_GP_PIN(9, 13),	/* AVB5_MDIO */
		[14] = RCAR_GP_PIN(9, 14),	/* AVB5_MDC */
		[15] = RCAR_GP_PIN(9, 15),	/* AVB5_MAGIC */
		[16] = RCAR_GP_PIN(9, 16),	/* AVB5_PHY_INT */
		[17] = RCAR_GP_PIN(9, 17),	/* AVB5_LINK */
		[18] = RCAR_GP_PIN(9, 18),	/* AVB5_AVTP_MATCH */
		[19] = RCAR_GP_PIN(9, 19),	/* AVB5_AVTP_CAPTURE */
		[20] = RCAR_GP_PIN(9, 20),	/* AVB5_AVTP_PPS */
		[21] = SH_PFC_PIN_NONE,
		[22] = SH_PFC_PIN_NONE,
		[23] = SH_PFC_PIN_NONE,
		[24] = SH_PFC_PIN_NONE,
		[25] = SH_PFC_PIN_NONE,
		[26] = SH_PFC_PIN_NONE,
		[27] = SH_PFC_PIN_NONE,
		[28] = SH_PFC_PIN_NONE,
		[29] = SH_PFC_PIN_NONE,
		[30] = SH_PFC_PIN_NONE,
		[31] = SH_PFC_PIN_NONE,
	पूर्ण पूर्ण,
	अणु /* sentinel */ पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा sh_pfc_soc_operations pinmux_ops = अणु
	.pin_to_pocctrl = r8a779a0_pin_to_pocctrl,
	.get_bias = rcar_pinmux_get_bias,
	.set_bias = rcar_pinmux_set_bias,
पूर्ण;

स्थिर काष्ठा sh_pfc_soc_info r8a779a0_pinmux_info = अणु
	.name = "r8a779a0_pfc",
	.ops = &pinmux_ops,
	.unlock_reg = 0x1ff,	/* PMMRn mask */

	.function = अणु PINMUX_FUNCTION_BEGIN, PINMUX_FUNCTION_END पूर्ण,

	.pins = pinmux_pins,
	.nr_pins = ARRAY_SIZE(pinmux_pins),
	.groups = pinmux_groups,
	.nr_groups = ARRAY_SIZE(pinmux_groups),
	.functions = pinmux_functions,
	.nr_functions = ARRAY_SIZE(pinmux_functions),

	.cfg_regs = pinmux_config_regs,
	.drive_regs = pinmux_drive_regs,
	.bias_regs = pinmux_bias_regs,
	.ioctrl_regs = pinmux_ioctrl_regs,

	.pinmux_data = pinmux_data,
	.pinmux_data_size = ARRAY_SIZE(pinmux_data),
पूर्ण;
