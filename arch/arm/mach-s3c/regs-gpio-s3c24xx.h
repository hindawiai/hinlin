<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2003-2004 Simtec Electronics <linux@simtec.co.uk>
 *	http://www.simtec.co.uk/products/SWLINUX/
 *
 * S3C2410 GPIO रेजिस्टर definitions
 */


#अगर_अघोषित __ASM_ARCH_REGS_GPIO_H
#घोषणा __ASM_ARCH_REGS_GPIO_H

#समावेश "map-s3c.h"

#घोषणा S3C24XX_MISCCR		S3C24XX_GPIOREG2(0x80)

/* general configuration options */

#घोषणा S3C2410_GPIO_LEAVE   (0xFFFFFFFF)
#घोषणा S3C2410_GPIO_INPUT   (0xFFFFFFF0)	/* not available on A */
#घोषणा S3C2410_GPIO_OUTPUT  (0xFFFFFFF1)
#घोषणा S3C2410_GPIO_IRQ     (0xFFFFFFF2)	/* not available क्रम all */
#घोषणा S3C2410_GPIO_SFN2    (0xFFFFFFF2)	/* bank A => addr/cs/nand */
#घोषणा S3C2410_GPIO_SFN3    (0xFFFFFFF3)	/* not available on A */

/* रेजिस्टर address क्रम the GPIO रेजिस्टरs.
 * S3C24XX_GPIOREG2 is क्रम the second set of रेजिस्टरs in the
 * GPIO which move between s3c2410 and s3c2412 type प्रणालीs */

#घोषणा S3C2410_GPIOREG(x) ((x) + S3C24XX_VA_GPIO)
#घोषणा S3C24XX_GPIOREG2(x) ((x) + S3C24XX_VA_GPIO2)


/* configure GPIO ports A..G */

/* port A - S3C2410: 22bits, zero in bit X makes pin X output
 * 1 makes port special function, this is शेष
*/
#घोषणा S3C2410_GPACON	   S3C2410_GPIOREG(0x00)
#घोषणा S3C2410_GPADAT	   S3C2410_GPIOREG(0x04)

#घोषणा S3C2410_GPA0_ADDR0   (1<<0)
#घोषणा S3C2410_GPA1_ADDR16  (1<<1)
#घोषणा S3C2410_GPA2_ADDR17  (1<<2)
#घोषणा S3C2410_GPA3_ADDR18  (1<<3)
#घोषणा S3C2410_GPA4_ADDR19  (1<<4)
#घोषणा S3C2410_GPA5_ADDR20  (1<<5)
#घोषणा S3C2410_GPA6_ADDR21  (1<<6)
#घोषणा S3C2410_GPA7_ADDR22  (1<<7)
#घोषणा S3C2410_GPA8_ADDR23  (1<<8)
#घोषणा S3C2410_GPA9_ADDR24  (1<<9)
#घोषणा S3C2410_GPA10_ADDR25 (1<<10)
#घोषणा S3C2410_GPA11_ADDR26 (1<<11)
#घोषणा S3C2410_GPA12_nGCS1  (1<<12)
#घोषणा S3C2410_GPA13_nGCS2  (1<<13)
#घोषणा S3C2410_GPA14_nGCS3  (1<<14)
#घोषणा S3C2410_GPA15_nGCS4  (1<<15)
#घोषणा S3C2410_GPA16_nGCS5  (1<<16)
#घोषणा S3C2410_GPA17_CLE    (1<<17)
#घोषणा S3C2410_GPA18_ALE    (1<<18)
#घोषणा S3C2410_GPA19_nFWE   (1<<19)
#घोषणा S3C2410_GPA20_nFRE   (1<<20)
#घोषणा S3C2410_GPA21_nRSTOUT (1<<21)
#घोषणा S3C2410_GPA22_nFCE   (1<<22)

/* 0x08 and 0x0c are reserved on S3C2410 */

/* S3C2410:
 * GPB is 10 IO pins, each configured by 2 bits each in GPBCON.
 *   00 = input, 01 = output, 10=special function, 11=reserved

 * bit 0,1 = pin 0, 2,3= pin 1...
 *
 * CPBUP = pull up resistor control, 1=disabled, 0=enabled
*/

#घोषणा S3C2410_GPBCON	   S3C2410_GPIOREG(0x10)
#घोषणा S3C2410_GPBDAT	   S3C2410_GPIOREG(0x14)
#घोषणा S3C2410_GPBUP	   S3C2410_GPIOREG(0x18)

/* no i/o pin in port b can have value 3 (unless it is a s3c2443) ! */

#घोषणा S3C2410_GPB0_TOUT0   (0x02 << 0)

#घोषणा S3C2410_GPB1_TOUT1   (0x02 << 2)

#घोषणा S3C2410_GPB2_TOUT2   (0x02 << 4)

#घोषणा S3C2410_GPB3_TOUT3   (0x02 << 6)

#घोषणा S3C2410_GPB4_TCLK0   (0x02 << 8)
#घोषणा S3C2410_GPB4_MASK    (0x03 << 8)

#घोषणा S3C2410_GPB5_nXBACK  (0x02 << 10)
#घोषणा S3C2443_GPB5_XBACK   (0x03 << 10)

#घोषणा S3C2410_GPB6_nXBREQ  (0x02 << 12)
#घोषणा S3C2443_GPB6_XBREQ   (0x03 << 12)

#घोषणा S3C2410_GPB7_nXDACK1 (0x02 << 14)
#घोषणा S3C2443_GPB7_XDACK1  (0x03 << 14)

#घोषणा S3C2410_GPB8_nXDREQ1 (0x02 << 16)

#घोषणा S3C2410_GPB9_nXDACK0 (0x02 << 18)
#घोषणा S3C2443_GPB9_XDACK0  (0x03 << 18)

#घोषणा S3C2410_GPB10_nXDRE0 (0x02 << 20)
#घोषणा S3C2443_GPB10_XDREQ0 (0x03 << 20)

#घोषणा S3C2410_GPB_PUPDIS(x)  (1<<(x))

/* Port C consits of 16 GPIO/Special function
 *
 * almost identical setup to port b, but the special functions are mostly
 * to करो with the video प्रणाली's sync/etc.
*/

#घोषणा S3C2410_GPCCON	   S3C2410_GPIOREG(0x20)
#घोषणा S3C2410_GPCDAT	   S3C2410_GPIOREG(0x24)
#घोषणा S3C2410_GPCUP	   S3C2410_GPIOREG(0x28)
#घोषणा S3C2410_GPC0_LEND	(0x02 << 0)
#घोषणा S3C2410_GPC1_VCLK	(0x02 << 2)
#घोषणा S3C2410_GPC2_VLINE	(0x02 << 4)
#घोषणा S3C2410_GPC3_VFRAME	(0x02 << 6)
#घोषणा S3C2410_GPC4_VM		(0x02 << 8)
#घोषणा S3C2410_GPC5_LCDVF0	(0x02 << 10)
#घोषणा S3C2410_GPC6_LCDVF1	(0x02 << 12)
#घोषणा S3C2410_GPC7_LCDVF2	(0x02 << 14)
#घोषणा S3C2410_GPC8_VD0	(0x02 << 16)
#घोषणा S3C2410_GPC9_VD1	(0x02 << 18)
#घोषणा S3C2410_GPC10_VD2	(0x02 << 20)
#घोषणा S3C2410_GPC11_VD3	(0x02 << 22)
#घोषणा S3C2410_GPC12_VD4	(0x02 << 24)
#घोषणा S3C2410_GPC13_VD5	(0x02 << 26)
#घोषणा S3C2410_GPC14_VD6	(0x02 << 28)
#घोषणा S3C2410_GPC15_VD7	(0x02 << 30)
#घोषणा S3C2410_GPC_PUPDIS(x)  (1<<(x))

/*
 * S3C2410: Port D consists of 16 GPIO/Special function
 *
 * almost identical setup to port b, but the special functions are mostly
 * to करो with the video प्रणाली's data.
 *
 * almost identical setup to port c
*/

#घोषणा S3C2410_GPDCON	   S3C2410_GPIOREG(0x30)
#घोषणा S3C2410_GPDDAT	   S3C2410_GPIOREG(0x34)
#घोषणा S3C2410_GPDUP	   S3C2410_GPIOREG(0x38)

#घोषणा S3C2410_GPD0_VD8	(0x02 << 0)
#घोषणा S3C2442_GPD0_nSPICS1	(0x03 << 0)

#घोषणा S3C2410_GPD1_VD9	(0x02 << 2)
#घोषणा S3C2442_GPD1_SPICLK1	(0x03 << 2)

#घोषणा S3C2410_GPD2_VD10	(0x02 << 4)

#घोषणा S3C2410_GPD3_VD11	(0x02 << 6)

#घोषणा S3C2410_GPD4_VD12	(0x02 << 8)

#घोषणा S3C2410_GPD5_VD13	(0x02 << 10)

#घोषणा S3C2410_GPD6_VD14	(0x02 << 12)

#घोषणा S3C2410_GPD7_VD15	(0x02 << 14)

#घोषणा S3C2410_GPD8_VD16	(0x02 << 16)
#घोषणा S3C2440_GPD8_SPIMISO1	(0x03 << 16)

#घोषणा S3C2410_GPD9_VD17	(0x02 << 18)
#घोषणा S3C2440_GPD9_SPIMOSI1	(0x03 << 18)

#घोषणा S3C2410_GPD10_VD18	(0x02 << 20)
#घोषणा S3C2440_GPD10_SPICLK1	(0x03 << 20)

#घोषणा S3C2410_GPD11_VD19	(0x02 << 22)

#घोषणा S3C2410_GPD12_VD20	(0x02 << 24)

#घोषणा S3C2410_GPD13_VD21	(0x02 << 26)

#घोषणा S3C2410_GPD14_VD22	(0x02 << 28)
#घोषणा S3C2410_GPD14_nSS1	(0x03 << 28)

#घोषणा S3C2410_GPD15_VD23	(0x02 << 30)
#घोषणा S3C2410_GPD15_nSS0	(0x03 << 30)

#घोषणा S3C2410_GPD_PUPDIS(x)  (1<<(x))

/* S3C2410:
 * Port E consists of 16 GPIO/Special function
 *
 * again, the same as port B, but dealing with I2S, SDI, and
 * more miscellaneous functions
 *
 * GPIO / पूर्णांकerrupt inमाला_दो
*/

#घोषणा S3C2410_GPECON	   S3C2410_GPIOREG(0x40)
#घोषणा S3C2410_GPEDAT	   S3C2410_GPIOREG(0x44)
#घोषणा S3C2410_GPEUP	   S3C2410_GPIOREG(0x48)

#घोषणा S3C2410_GPE0_I2SLRCK   (0x02 << 0)
#घोषणा S3C2443_GPE0_AC_nRESET (0x03 << 0)
#घोषणा S3C2410_GPE0_MASK      (0x03 << 0)

#घोषणा S3C2410_GPE1_I2SSCLK   (0x02 << 2)
#घोषणा S3C2443_GPE1_AC_SYNC   (0x03 << 2)
#घोषणा S3C2410_GPE1_MASK      (0x03 << 2)

#घोषणा S3C2410_GPE2_CDCLK     (0x02 << 4)
#घोषणा S3C2443_GPE2_AC_BITCLK (0x03 << 4)

#घोषणा S3C2410_GPE3_I2SSDI    (0x02 << 6)
#घोषणा S3C2443_GPE3_AC_SDI    (0x03 << 6)
#घोषणा S3C2410_GPE3_nSS0      (0x03 << 6)
#घोषणा S3C2410_GPE3_MASK      (0x03 << 6)

#घोषणा S3C2410_GPE4_I2SSDO    (0x02 << 8)
#घोषणा S3C2443_GPE4_AC_SDO    (0x03 << 8)
#घोषणा S3C2410_GPE4_I2SSDI    (0x03 << 8)
#घोषणा S3C2410_GPE4_MASK      (0x03 << 8)

#घोषणा S3C2410_GPE5_SDCLK     (0x02 << 10)
#घोषणा S3C2443_GPE5_SD1_CLK   (0x02 << 10)
#घोषणा S3C2443_GPE5_AC_BITCLK (0x03 << 10)

#घोषणा S3C2410_GPE6_SDCMD     (0x02 << 12)
#घोषणा S3C2443_GPE6_SD1_CMD   (0x02 << 12)
#घोषणा S3C2443_GPE6_AC_SDI    (0x03 << 12)

#घोषणा S3C2410_GPE7_SDDAT0    (0x02 << 14)
#घोषणा S3C2443_GPE5_SD1_DAT0  (0x02 << 14)
#घोषणा S3C2443_GPE7_AC_SDO    (0x03 << 14)

#घोषणा S3C2410_GPE8_SDDAT1    (0x02 << 16)
#घोषणा S3C2443_GPE8_SD1_DAT1  (0x02 << 16)
#घोषणा S3C2443_GPE8_AC_SYNC   (0x03 << 16)

#घोषणा S3C2410_GPE9_SDDAT2    (0x02 << 18)
#घोषणा S3C2443_GPE9_SD1_DAT2  (0x02 << 18)
#घोषणा S3C2443_GPE9_AC_nRESET (0x03 << 18)

#घोषणा S3C2410_GPE10_SDDAT3   (0x02 << 20)
#घोषणा S3C2443_GPE10_SD1_DAT3 (0x02 << 20)

#घोषणा S3C2410_GPE11_SPIMISO0 (0x02 << 22)

#घोषणा S3C2410_GPE12_SPIMOSI0 (0x02 << 24)

#घोषणा S3C2410_GPE13_SPICLK0  (0x02 << 26)

#घोषणा S3C2410_GPE14_IICSCL   (0x02 << 28)
#घोषणा S3C2410_GPE14_MASK     (0x03 << 28)

#घोषणा S3C2410_GPE15_IICSDA   (0x02 << 30)
#घोषणा S3C2410_GPE15_MASK     (0x03 << 30)

#घोषणा S3C2440_GPE0_ACSYNC    (0x03 << 0)
#घोषणा S3C2440_GPE1_ACBITCLK  (0x03 << 2)
#घोषणा S3C2440_GPE2_ACRESET   (0x03 << 4)
#घोषणा S3C2440_GPE3_ACIN      (0x03 << 6)
#घोषणा S3C2440_GPE4_ACOUT     (0x03 << 8)

#घोषणा S3C2410_GPE_PUPDIS(x)  (1<<(x))

/* S3C2410:
 * Port F consists of 8 GPIO/Special function
 *
 * GPIO / पूर्णांकerrupt inमाला_दो
 *
 * GPFCON has 2 bits क्रम each of the input pins on port F
 *   00 = 0 input, 1 output, 2 पूर्णांकerrupt (EINT0..7), 3 undefined
 *
 * pull up works like all other ports.
 *
 * GPIO/serial/misc pins
*/

#घोषणा S3C2410_GPFCON	   S3C2410_GPIOREG(0x50)
#घोषणा S3C2410_GPFDAT	   S3C2410_GPIOREG(0x54)
#घोषणा S3C2410_GPFUP	   S3C2410_GPIOREG(0x58)

#घोषणा S3C2410_GPF0_EINT0  (0x02 << 0)
#घोषणा S3C2410_GPF1_EINT1  (0x02 << 2)
#घोषणा S3C2410_GPF2_EINT2  (0x02 << 4)
#घोषणा S3C2410_GPF3_EINT3  (0x02 << 6)
#घोषणा S3C2410_GPF4_EINT4  (0x02 << 8)
#घोषणा S3C2410_GPF5_EINT5  (0x02 << 10)
#घोषणा S3C2410_GPF6_EINT6  (0x02 << 12)
#घोषणा S3C2410_GPF7_EINT7  (0x02 << 14)
#घोषणा S3C2410_GPF_PUPDIS(x)  (1<<(x))

/* S3C2410:
 * Port G consists of 8 GPIO/IRQ/Special function
 *
 * GPGCON has 2 bits क्रम each of the input pins on port G
 *   00 = 0 input, 1 output, 2 पूर्णांकerrupt (EINT0..7), 3 special func
 *
 * pull up works like all other ports.
*/

#घोषणा S3C2410_GPGCON	   S3C2410_GPIOREG(0x60)
#घोषणा S3C2410_GPGDAT	   S3C2410_GPIOREG(0x64)
#घोषणा S3C2410_GPGUP	   S3C2410_GPIOREG(0x68)

#घोषणा S3C2410_GPG0_EINT8    (0x02 << 0)

#घोषणा S3C2410_GPG1_EINT9    (0x02 << 2)

#घोषणा S3C2410_GPG2_EINT10   (0x02 << 4)
#घोषणा S3C2410_GPG2_nSS0     (0x03 << 4)

#घोषणा S3C2410_GPG3_EINT11   (0x02 << 6)
#घोषणा S3C2410_GPG3_nSS1     (0x03 << 6)

#घोषणा S3C2410_GPG4_EINT12   (0x02 << 8)
#घोषणा S3C2410_GPG4_LCDPWREN (0x03 << 8)
#घोषणा S3C2443_GPG4_LCDPWRDN (0x03 << 8)

#घोषणा S3C2410_GPG5_EINT13   (0x02 << 10)
#घोषणा S3C2410_GPG5_SPIMISO1 (0x03 << 10)	/* not s3c2443 */

#घोषणा S3C2410_GPG6_EINT14   (0x02 << 12)
#घोषणा S3C2410_GPG6_SPIMOSI1 (0x03 << 12)

#घोषणा S3C2410_GPG7_EINT15   (0x02 << 14)
#घोषणा S3C2410_GPG7_SPICLK1  (0x03 << 14)

#घोषणा S3C2410_GPG8_EINT16   (0x02 << 16)

#घोषणा S3C2410_GPG9_EINT17   (0x02 << 18)

#घोषणा S3C2410_GPG10_EINT18  (0x02 << 20)

#घोषणा S3C2410_GPG11_EINT19  (0x02 << 22)
#घोषणा S3C2410_GPG11_TCLK1   (0x03 << 22)
#घोषणा S3C2443_GPG11_CF_nIREQ (0x03 << 22)

#घोषणा S3C2410_GPG12_EINT20  (0x02 << 24)
#घोषणा S3C2410_GPG12_XMON    (0x03 << 24)
#घोषणा S3C2442_GPG12_nSPICS0 (0x03 << 24)
#घोषणा S3C2443_GPG12_nINPACK (0x03 << 24)

#घोषणा S3C2410_GPG13_EINT21  (0x02 << 26)
#घोषणा S3C2410_GPG13_nXPON   (0x03 << 26)
#घोषणा S3C2443_GPG13_CF_nREG (0x03 << 26)

#घोषणा S3C2410_GPG14_EINT22  (0x02 << 28)
#घोषणा S3C2410_GPG14_YMON    (0x03 << 28)
#घोषणा S3C2443_GPG14_CF_RESET (0x03 << 28)

#घोषणा S3C2410_GPG15_EINT23  (0x02 << 30)
#घोषणा S3C2410_GPG15_nYPON   (0x03 << 30)
#घोषणा S3C2443_GPG15_CF_PWR  (0x03 << 30)

#घोषणा S3C2410_GPG_PUPDIS(x)  (1<<(x))

/* Port H consists of11 GPIO/serial/Misc pins
 *
 * GPHCON has 2 bits क्रम each of the input pins on port H
 *   00 = 0 input, 1 output, 2 पूर्णांकerrupt (EINT0..7), 3 special func
 *
 * pull up works like all other ports.
*/

#घोषणा S3C2410_GPHCON	   S3C2410_GPIOREG(0x70)
#घोषणा S3C2410_GPHDAT	   S3C2410_GPIOREG(0x74)
#घोषणा S3C2410_GPHUP	   S3C2410_GPIOREG(0x78)

#घोषणा S3C2410_GPH0_nCTS0  (0x02 << 0)
#घोषणा S3C2416_GPH0_TXD0  (0x02 << 0)

#घोषणा S3C2410_GPH1_nRTS0  (0x02 << 2)
#घोषणा S3C2416_GPH1_RXD0  (0x02 << 2)

#घोषणा S3C2410_GPH2_TXD0   (0x02 << 4)
#घोषणा S3C2416_GPH2_TXD1   (0x02 << 4)

#घोषणा S3C2410_GPH3_RXD0   (0x02 << 6)
#घोषणा S3C2416_GPH3_RXD1   (0x02 << 6)

#घोषणा S3C2410_GPH4_TXD1   (0x02 << 8)
#घोषणा S3C2416_GPH4_TXD2   (0x02 << 8)

#घोषणा S3C2410_GPH5_RXD1   (0x02 << 10)
#घोषणा S3C2416_GPH5_RXD2   (0x02 << 10)

#घोषणा S3C2410_GPH6_TXD2   (0x02 << 12)
#घोषणा S3C2416_GPH6_TXD3   (0x02 << 12)
#घोषणा S3C2410_GPH6_nRTS1  (0x03 << 12)
#घोषणा S3C2416_GPH6_nRTS2  (0x03 << 12)

#घोषणा S3C2410_GPH7_RXD2   (0x02 << 14)
#घोषणा S3C2416_GPH7_RXD3   (0x02 << 14)
#घोषणा S3C2410_GPH7_nCTS1  (0x03 << 14)
#घोषणा S3C2416_GPH7_nCTS2  (0x03 << 14)

#घोषणा S3C2410_GPH8_UCLK   (0x02 << 16)
#घोषणा S3C2416_GPH8_nCTS0  (0x02 << 16)

#घोषणा S3C2410_GPH9_CLKOUT0  (0x02 << 18)
#घोषणा S3C2442_GPH9_nSPICS0  (0x03 << 18)
#घोषणा S3C2416_GPH9_nRTS0    (0x02 << 18)

#घोषणा S3C2410_GPH10_CLKOUT1 (0x02 << 20)
#घोषणा S3C2416_GPH10_nCTS1   (0x02 << 20)

#घोषणा S3C2416_GPH11_nRTS1   (0x02 << 22)

#घोषणा S3C2416_GPH12_EXTUARTCLK (0x02 << 24)

#घोषणा S3C2416_GPH13_CLKOUT0 (0x02 << 26)

#घोषणा S3C2416_GPH14_CLKOUT1 (0x02 << 28)

/* The S3C2412 and S3C2413 move the GPJ रेजिस्टर set to after
 * GPH, which means all रेजिस्टरs after 0x80 are now offset by 0x10
 * क्रम the 2412/2413 from the 2410/2440/2442
*/

/*
 * Port J consists of 13 GPIO/Camera pins. GPJCON has 2 bits
 * क्रम each of the pins on port J.
 *   00 - input, 01 output, 10 - camera
 *
 * Pull up works like all other ports.
 */

#घोषणा S3C2413_GPJCON	   S3C2410_GPIOREG(0x80)
#घोषणा S3C2413_GPJDAT	   S3C2410_GPIOREG(0x84)
#घोषणा S3C2413_GPJUP	   S3C2410_GPIOREG(0x88)
#घोषणा S3C2413_GPJSLPCON  S3C2410_GPIOREG(0x8C)

/* S3C2443 and above */
#घोषणा S3C2440_GPJCON	   S3C2410_GPIOREG(0xD0)
#घोषणा S3C2440_GPJDAT	   S3C2410_GPIOREG(0xD4)
#घोषणा S3C2440_GPJUP	   S3C2410_GPIOREG(0xD8)

#घोषणा S3C2443_GPKCON	   S3C2410_GPIOREG(0xE0)
#घोषणा S3C2443_GPKDAT	   S3C2410_GPIOREG(0xE4)
#घोषणा S3C2443_GPKUP	   S3C2410_GPIOREG(0xE8)

#घोषणा S3C2443_GPLCON	   S3C2410_GPIOREG(0xF0)
#घोषणा S3C2443_GPLDAT	   S3C2410_GPIOREG(0xF4)
#घोषणा S3C2443_GPLUP	   S3C2410_GPIOREG(0xF8)

#घोषणा S3C2443_GPMCON	   S3C2410_GPIOREG(0x100)
#घोषणा S3C2443_GPMDAT	   S3C2410_GPIOREG(0x104)
#घोषणा S3C2443_GPMUP	   S3C2410_GPIOREG(0x108)

/* miscellaneous control */
#घोषणा S3C2410_MISCCR	   S3C2410_GPIOREG(0x80)

/* see घड़ी.h क्रम dclk definitions */

/* pullup control on databus */
#घोषणा S3C2410_MISCCR_SPUCR_HEN    (0<<0)
#घोषणा S3C2410_MISCCR_SPUCR_HDIS   (1<<0)
#घोषणा S3C2410_MISCCR_SPUCR_LEN    (0<<1)
#घोषणा S3C2410_MISCCR_SPUCR_LDIS   (1<<1)

#घोषणा S3C2410_MISCCR_USBDEV	    (0<<3)
#घोषणा S3C2410_MISCCR_USBHOST	    (1<<3)

#घोषणा S3C2410_MISCCR_CLK0_MPLL    (0<<4)
#घोषणा S3C2410_MISCCR_CLK0_UPLL    (1<<4)
#घोषणा S3C2410_MISCCR_CLK0_FCLK    (2<<4)
#घोषणा S3C2410_MISCCR_CLK0_HCLK    (3<<4)
#घोषणा S3C2410_MISCCR_CLK0_PCLK    (4<<4)
#घोषणा S3C2410_MISCCR_CLK0_DCLK0   (5<<4)
#घोषणा S3C2410_MISCCR_CLK0_MASK    (7<<4)

#घोषणा S3C2412_MISCCR_CLK0_RTC	    (2<<4)

#घोषणा S3C2410_MISCCR_CLK1_MPLL    (0<<8)
#घोषणा S3C2410_MISCCR_CLK1_UPLL    (1<<8)
#घोषणा S3C2410_MISCCR_CLK1_FCLK    (2<<8)
#घोषणा S3C2410_MISCCR_CLK1_HCLK    (3<<8)
#घोषणा S3C2410_MISCCR_CLK1_PCLK    (4<<8)
#घोषणा S3C2410_MISCCR_CLK1_DCLK1   (5<<8)
#घोषणा S3C2410_MISCCR_CLK1_MASK    (7<<8)

#घोषणा S3C2412_MISCCR_CLK1_CLKsrc  (0<<8)

#घोषणा S3C2410_MISCCR_USBSUSPND0   (1<<12)
#घोषणा S3C2416_MISCCR_SEL_SUSPND   (1<<12)
#घोषणा S3C2410_MISCCR_USBSUSPND1   (1<<13)

#घोषणा S3C2410_MISCCR_nRSTCON	    (1<<16)

#घोषणा S3C2410_MISCCR_nEN_SCLK0    (1<<17)
#घोषणा S3C2410_MISCCR_nEN_SCLK1    (1<<18)
#घोषणा S3C2410_MISCCR_nEN_SCLKE    (1<<19)	/* not 2412 */
#घोषणा S3C2410_MISCCR_SDSLEEP	    (7<<17)

#घोषणा S3C2416_MISCCR_FLT_I2C      (1<<24)
#घोषणा S3C2416_MISCCR_HSSPI_EN2    (1<<31)

/* बाह्यal पूर्णांकerrupt control... */
/* S3C2410_EXTINT0 -> irq sense control क्रम EINT0..EINT7
 * S3C2410_EXTINT1 -> irq sense control क्रम EINT8..EINT15
 * S3C2410_EXTINT2 -> irq sense control क्रम EINT16..EINT23
 *
 * note S3C2410_EXTINT2 has filtering options क्रम EINT16..EINT23
 *
 * Samsung datasheet p9-25
*/
#घोषणा S3C2410_EXTINT0	   S3C2410_GPIOREG(0x88)
#घोषणा S3C2410_EXTINT1	   S3C2410_GPIOREG(0x8C)
#घोषणा S3C2410_EXTINT2	   S3C2410_GPIOREG(0x90)

#घोषणा S3C24XX_EXTINT0	   S3C24XX_GPIOREG2(0x88)
#घोषणा S3C24XX_EXTINT1	   S3C24XX_GPIOREG2(0x8C)
#घोषणा S3C24XX_EXTINT2	   S3C24XX_GPIOREG2(0x90)

/* पूर्णांकerrupt filtering control क्रम EINT16..EINT23 */
#घोषणा S3C2410_EINFLT0	   S3C2410_GPIOREG(0x94)
#घोषणा S3C2410_EINFLT1	   S3C2410_GPIOREG(0x98)
#घोषणा S3C2410_EINFLT2	   S3C2410_GPIOREG(0x9C)
#घोषणा S3C2410_EINFLT3	   S3C2410_GPIOREG(0xA0)

#घोषणा S3C24XX_EINFLT0	   S3C24XX_GPIOREG2(0x94)
#घोषणा S3C24XX_EINFLT1	   S3C24XX_GPIOREG2(0x98)
#घोषणा S3C24XX_EINFLT2	   S3C24XX_GPIOREG2(0x9C)
#घोषणा S3C24XX_EINFLT3	   S3C24XX_GPIOREG2(0xA0)

/* values क्रम पूर्णांकerrupt filtering */
#घोषणा S3C2410_EINTFLT_PCLK		(0x00)
#घोषणा S3C2410_EINTFLT_EXTCLK		(1<<7)
#घोषणा S3C2410_EINTFLT_WIDTHMSK(x)	((x) & 0x3f)

/* हटाओd EINTxxxx defs from here, not meant क्रम this */

/* GSTATUS have miscellaneous inक्रमmation in them
 *
 * These move between s3c2410 and s3c2412 style प्रणालीs.
 */

#घोषणा S3C2410_GSTATUS0   S3C2410_GPIOREG(0x0AC)
#घोषणा S3C2410_GSTATUS1   S3C2410_GPIOREG(0x0B0)
#घोषणा S3C2410_GSTATUS2   S3C2410_GPIOREG(0x0B4)
#घोषणा S3C2410_GSTATUS3   S3C2410_GPIOREG(0x0B8)
#घोषणा S3C2410_GSTATUS4   S3C2410_GPIOREG(0x0BC)

#घोषणा S3C2412_GSTATUS0   S3C2410_GPIOREG(0x0BC)
#घोषणा S3C2412_GSTATUS1   S3C2410_GPIOREG(0x0C0)
#घोषणा S3C2412_GSTATUS2   S3C2410_GPIOREG(0x0C4)
#घोषणा S3C2412_GSTATUS3   S3C2410_GPIOREG(0x0C8)
#घोषणा S3C2412_GSTATUS4   S3C2410_GPIOREG(0x0CC)

#घोषणा S3C24XX_GSTATUS0   S3C24XX_GPIOREG2(0x0AC)
#घोषणा S3C24XX_GSTATUS1   S3C24XX_GPIOREG2(0x0B0)
#घोषणा S3C24XX_GSTATUS2   S3C24XX_GPIOREG2(0x0B4)
#घोषणा S3C24XX_GSTATUS3   S3C24XX_GPIOREG2(0x0B8)
#घोषणा S3C24XX_GSTATUS4   S3C24XX_GPIOREG2(0x0BC)

#घोषणा S3C2410_GSTATUS0_nWAIT	   (1<<3)
#घोषणा S3C2410_GSTATUS0_NCON	   (1<<2)
#घोषणा S3C2410_GSTATUS0_RnB	   (1<<1)
#घोषणा S3C2410_GSTATUS0_nBATTFLT  (1<<0)

#घोषणा S3C2410_GSTATUS1_IDMASK	   (0xffff0000)
#घोषणा S3C2410_GSTATUS1_2410	   (0x32410000)
#घोषणा S3C2410_GSTATUS1_2412	   (0x32412001)
#घोषणा S3C2410_GSTATUS1_2416	   (0x32416003)
#घोषणा S3C2410_GSTATUS1_2440	   (0x32440000)
#घोषणा S3C2410_GSTATUS1_2442	   (0x32440aaa)
/* some 2416 CPUs report this value also */
#घोषणा S3C2410_GSTATUS1_2450	   (0x32450003)

#घोषणा S3C2410_GSTATUS2_WTRESET   (1<<2)
#घोषणा S3C2410_GSTATUS2_OFFRESET  (1<<1)
#घोषणा S3C2410_GSTATUS2_PONRESET  (1<<0)

/* 2412/2413 sleep configuration रेजिस्टरs */

#घोषणा S3C2412_GPBSLPCON	S3C2410_GPIOREG(0x1C)
#घोषणा S3C2412_GPCSLPCON	S3C2410_GPIOREG(0x2C)
#घोषणा S3C2412_GPDSLPCON	S3C2410_GPIOREG(0x3C)
#घोषणा S3C2412_GPFSLPCON	S3C2410_GPIOREG(0x5C)
#घोषणा S3C2412_GPGSLPCON	S3C2410_GPIOREG(0x6C)
#घोषणा S3C2412_GPHSLPCON	S3C2410_GPIOREG(0x7C)

/* definitions क्रम each pin bit */
#घोषणा S3C2412_GPIO_SLPCON_LOW	 ( 0x00 )
#घोषणा S3C2412_GPIO_SLPCON_HIGH ( 0x01 )
#घोषणा S3C2412_GPIO_SLPCON_IN   ( 0x02 )
#घोषणा S3C2412_GPIO_SLPCON_PULL ( 0x03 )

#घोषणा S3C2412_SLPCON_LOW(x)	( 0x00 << ((x) * 2))
#घोषणा S3C2412_SLPCON_HIGH(x)	( 0x01 << ((x) * 2))
#घोषणा S3C2412_SLPCON_IN(x)	( 0x02 << ((x) * 2))
#घोषणा S3C2412_SLPCON_PULL(x)	( 0x03 << ((x) * 2))
#घोषणा S3C2412_SLPCON_EINT(x)	( 0x02 << ((x) * 2))  /* only IRQ pins */
#घोषणा S3C2412_SLPCON_MASK(x)	( 0x03 << ((x) * 2))

#घोषणा S3C2412_SLPCON_ALL_LOW	(0x0)
#घोषणा S3C2412_SLPCON_ALL_HIGH	(0x11111111 | 0x44444444)
#घोषणा S3C2412_SLPCON_ALL_IN  	(0x22222222 | 0x88888888)
#घोषणा S3C2412_SLPCON_ALL_PULL	(0x33333333)

#पूर्ण_अगर	/* __ASM_ARCH_REGS_GPIO_H */

