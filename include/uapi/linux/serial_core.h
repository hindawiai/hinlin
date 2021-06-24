<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/*
 *  linux/drivers/अक्षर/serial_core.h
 *
 *  Copyright (C) 2000 Deep Blue Solutions Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
#अगर_अघोषित _UAPILINUX_SERIAL_CORE_H
#घोषणा _UAPILINUX_SERIAL_CORE_H

#समावेश <linux/serial.h>

/*
 * The type definitions.  These are from Ted Ts'o's serial.h
 */
#घोषणा PORT_NS16550A	14
#घोषणा PORT_XSCALE	15
#घोषणा PORT_RM9000	16	/* PMC-Sierra RM9xxx पूर्णांकernal UART */
#घोषणा PORT_OCTEON	17	/* Cavium OCTEON पूर्णांकernal UART */
#घोषणा PORT_AR7	18	/* Texas Instruments AR7 पूर्णांकernal UART */
#घोषणा PORT_U6_16550A	19	/* ST-Ericsson U6xxx पूर्णांकernal UART */
#घोषणा PORT_TEGRA	20	/* NVIDIA Tegra पूर्णांकernal UART */
#घोषणा PORT_XR17D15X	21	/* Exar XR17D15x UART */
#घोषणा PORT_LPC3220	22	/* NXP LPC32xx SoC "Standard" UART */
#घोषणा PORT_8250_CIR	23	/* CIR infrared port, has its own driver */
#घोषणा PORT_XR17V35X	24	/* Exar XR17V35x UARTs */
#घोषणा PORT_BRCM_TRUMANAGE	25
#घोषणा PORT_ALTR_16550_F32 26	/* Altera 16550 UART with 32 FIFOs */
#घोषणा PORT_ALTR_16550_F64 27	/* Altera 16550 UART with 64 FIFOs */
#घोषणा PORT_ALTR_16550_F128 28 /* Altera 16550 UART with 128 FIFOs */
#घोषणा PORT_RT2880	29	/* Ralink RT2880 पूर्णांकernal UART */
#घोषणा PORT_16550A_FSL64 30	/* Freescale 16550 UART with 64 FIFOs */

/*
 * ARM specअगरic type numbers.  These are not currently guaranteed
 * to be implemented, and will change in the future.  These are
 * separate so any additions to the old serial.c that occur beक्रमe
 * we are merged can be easily merged here.
 */
#घोषणा PORT_PXA	31
#घोषणा PORT_AMBA	32
#घोषणा PORT_CLPS711X	33
#घोषणा PORT_SA1100	34
#घोषणा PORT_UART00	35
#घोषणा PORT_OWL	36
#घोषणा PORT_21285	37

/* Sparc type numbers.  */
#घोषणा PORT_SUNZILOG	38
#घोषणा PORT_SUNSAB	39

/* Nuvoton UART */
#घोषणा PORT_NPCM	40

/* NVIDIA Tegra Combined UART */
#घोषणा PORT_TEGRA_TCU	41

/* Intel EG20 */
#घोषणा PORT_PCH_8LINE	44
#घोषणा PORT_PCH_2LINE	45

/* DEC */
#घोषणा PORT_DZ		46
#घोषणा PORT_ZS		47

/* Parisc type numbers. */
#घोषणा PORT_MUX	48

/* Aपंचांगel AT91 SoC */
#घोषणा PORT_ATMEL	49

/* Macपूर्णांकosh Zilog type numbers */
#घोषणा PORT_MAC_ZILOG	50	/* m68k : not yet implemented */
#घोषणा PORT_PMAC_ZILOG	51

/* SH-SCI */
#घोषणा PORT_SCI	52
#घोषणा PORT_SCIF	53
#घोषणा PORT_IRDA	54

/* Samsung S3C2410 SoC and derivatives thereof */
#घोषणा PORT_S3C2410    55

/* SGI IP22 aka Indy / Challenge S / Indigo 2 */
#घोषणा PORT_IP22ZILOG	56

/* Sharp LH7a40x -- an ARM9 SoC series */
#घोषणा PORT_LH7A40X	57

/* PPC CPM type number */
#घोषणा PORT_CPM        58

/* MPC52xx (and MPC512x) type numbers */
#घोषणा PORT_MPC52xx	59

/* IBM icom */
#घोषणा PORT_ICOM	60

/* Samsung S3C2440 SoC */
#घोषणा PORT_S3C2440	61

/* Motorola i.MX SoC */
#घोषणा PORT_IMX	62

/* Marvell MPSC (obsolete unused) */
#घोषणा PORT_MPSC	63

/* TXX9 type number */
#घोषणा PORT_TXX9	64

/* NEC VR4100 series SIU/DSIU */
#घोषणा PORT_VR41XX_SIU		65
#घोषणा PORT_VR41XX_DSIU	66

/* Samsung S3C2400 SoC */
#घोषणा PORT_S3C2400	67

/* M32R SIO */
#घोषणा PORT_M32R_SIO	68

/*Digi jsm */
#घोषणा PORT_JSM        69

/* SUN4V Hypervisor Console */
#घोषणा PORT_SUNHV	72

#घोषणा PORT_S3C2412	73

/* Xilinx uartlite */
#घोषणा PORT_UARTLITE	74

/* Blackfin bf5xx */
#घोषणा PORT_BFIN	75

/* Broadcom SB1250, etc. SOC */
#घोषणा PORT_SB1250_DUART	77

/* Freescale ColdFire */
#घोषणा PORT_MCF	78

/* Blackfin SPORT */
#घोषणा PORT_BFIN_SPORT		79

/* MN10300 on-chip UART numbers */
#घोषणा PORT_MN10300		80
#घोषणा PORT_MN10300_CTS	81

#घोषणा PORT_SC26XX	82

/* SH-SCI */
#घोषणा PORT_SCIFA	83

#घोषणा PORT_S3C6400	84

/* NWPSERIAL, now हटाओd */
#घोषणा PORT_NWPSERIAL	85

/* MAX3100 */
#घोषणा PORT_MAX3100    86

/* Timberdale UART */
#घोषणा PORT_TIMBUART	87

/* Qualcomm MSM SoCs */
#घोषणा PORT_MSM	88

/* BCM63xx family SoCs */
#घोषणा PORT_BCM63XX	89

/* Aeroflex Gaisler GRLIB APBUART */
#घोषणा PORT_APBUART    90

/* Altera UARTs */
#घोषणा PORT_ALTERA_JTAGUART	91
#घोषणा PORT_ALTERA_UART	92

/* SH-SCI */
#घोषणा PORT_SCIFB	93

/* MAX310X */
#घोषणा PORT_MAX310X	94

/* TI DA8xx/66AK2x */
#घोषणा PORT_DA830	95

/* TI OMAP-UART */
#घोषणा PORT_OMAP	96

/* VIA VT8500 SoC */
#घोषणा PORT_VT8500	97

/* Cadence (Xilinx Zynq) UART */
#घोषणा PORT_XUARTPS	98

/* Atheros AR933X SoC */
#घोषणा PORT_AR933X	99

/* ARC (Synopsys) on-chip UART */
#घोषणा PORT_ARC       101

/* Rocketport EXPRESS/अनन्त */
#घोषणा PORT_RP2	102

/* Freescale lpuart */
#घोषणा PORT_LPUART	103

/* SH-SCI */
#घोषणा PORT_HSCIF	104

/* ST ASC type numbers */
#घोषणा PORT_ASC       105

/* Tilera TILE-Gx UART */
#घोषणा PORT_TILEGX	106

/* MEN 16z135 UART */
#घोषणा PORT_MEN_Z135	107

/* SC16IS74xx */
#घोषणा PORT_SC16IS7XX   108

/* MESON */
#घोषणा PORT_MESON	109

/* Conexant Digicolor */
#घोषणा PORT_DIGICOLOR	110

/* SPRD SERIAL  */
#घोषणा PORT_SPRD	111

/* Cris v10 / v32 SoC */
#घोषणा PORT_CRIS	112

/* STM32 USART */
#घोषणा PORT_STM32	113

/* MVEBU UART */
#घोषणा PORT_MVEBU	114

/* Microchip PIC32 UART */
#घोषणा PORT_PIC32	115

/* MPS2 UART */
#घोषणा PORT_MPS2UART	116

/* MediaTek BTIF */
#घोषणा PORT_MTK_BTIF	117

/* RDA UART */
#घोषणा PORT_RDA	118

/* Socionext Milbeaut UART */
#घोषणा PORT_MLB_USIO	119

/* SiFive UART */
#घोषणा PORT_SIFIVE_V0	120

/* Sunix UART */
#घोषणा PORT_SUNIX	121

/* Freescale LINFlexD UART */
#घोषणा PORT_LINFLEXUART	122

#पूर्ण_अगर /* _UAPILINUX_SERIAL_CORE_H */
