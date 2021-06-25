<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* linux/arch/arm/mach-s3c64xx/include/mach/irqs.h
 *
 * Copyright 2008 Openmoko, Inc.
 * Copyright 2008 Simtec Electronics
 *      Ben Dooks <ben@simtec.co.uk>
 *      http://armlinux.simtec.co.uk/
 *
 * S3C64XX - IRQ support
 */

#अगर_अघोषित __ASM_MACH_S3C64XX_IRQS_H
#घोषणा __ASM_MACH_S3C64XX_IRQS_H __खाता__

/* we keep the first set of CPU IRQs out of the range of
 * the ISA space, so that the PC104 has them to itself
 * and we करोn't end up having to करो horrible things to the
 * standard ISA drivers....
 *
 * note, since we're using the VICs, our start must be a
 * mulitple of 32 to allow the common code to work
 */

#घोषणा S3C_IRQ_OFFSET	(32)

#घोषणा S3C_IRQ(x)	((x) + S3C_IRQ_OFFSET)

#घोषणा IRQ_VIC0_BASE	S3C_IRQ(0)
#घोषणा IRQ_VIC1_BASE	S3C_IRQ(32)

/* VIC based IRQs */

#घोषणा S3C64XX_IRQ_VIC0(x)	(IRQ_VIC0_BASE + (x))
#घोषणा S3C64XX_IRQ_VIC1(x)	(IRQ_VIC1_BASE + (x))

/* VIC0 */

#घोषणा IRQ_EINT0_3		S3C64XX_IRQ_VIC0(0)
#घोषणा IRQ_EINT4_11		S3C64XX_IRQ_VIC0(1)
#घोषणा IRQ_RTC_TIC		S3C64XX_IRQ_VIC0(2)
#घोषणा IRQ_CAMIF_C		S3C64XX_IRQ_VIC0(3)
#घोषणा IRQ_CAMIF_P		S3C64XX_IRQ_VIC0(4)
#घोषणा IRQ_CAMIF_MC		S3C64XX_IRQ_VIC0(5)
#घोषणा IRQ_S3C6410_IIC1	S3C64XX_IRQ_VIC0(5)
#घोषणा IRQ_S3C6410_IIS		S3C64XX_IRQ_VIC0(6)
#घोषणा IRQ_S3C6400_CAMIF_MP	S3C64XX_IRQ_VIC0(6)
#घोषणा IRQ_CAMIF_WE_C		S3C64XX_IRQ_VIC0(7)
#घोषणा IRQ_S3C6410_G3D		S3C64XX_IRQ_VIC0(8)
#घोषणा IRQ_S3C6400_CAMIF_WE_P	S3C64XX_IRQ_VIC0(8)
#घोषणा IRQ_POST0		S3C64XX_IRQ_VIC0(9)
#घोषणा IRQ_ROTATOR		S3C64XX_IRQ_VIC0(10)
#घोषणा IRQ_2D			S3C64XX_IRQ_VIC0(11)
#घोषणा IRQ_TVENC		S3C64XX_IRQ_VIC0(12)
#घोषणा IRQ_SCALER		S3C64XX_IRQ_VIC0(13)
#घोषणा IRQ_BATF		S3C64XX_IRQ_VIC0(14)
#घोषणा IRQ_JPEG		S3C64XX_IRQ_VIC0(15)
#घोषणा IRQ_MFC			S3C64XX_IRQ_VIC0(16)
#घोषणा IRQ_SDMA0		S3C64XX_IRQ_VIC0(17)
#घोषणा IRQ_SDMA1		S3C64XX_IRQ_VIC0(18)
#घोषणा IRQ_ARM_DMAERR		S3C64XX_IRQ_VIC0(19)
#घोषणा IRQ_ARM_DMA		S3C64XX_IRQ_VIC0(20)
#घोषणा IRQ_ARM_DMAS		S3C64XX_IRQ_VIC0(21)
#घोषणा IRQ_KEYPAD		S3C64XX_IRQ_VIC0(22)
#घोषणा IRQ_TIMER0_VIC		S3C64XX_IRQ_VIC0(23)
#घोषणा IRQ_TIMER1_VIC		S3C64XX_IRQ_VIC0(24)
#घोषणा IRQ_TIMER2_VIC		S3C64XX_IRQ_VIC0(25)
#घोषणा IRQ_WDT			S3C64XX_IRQ_VIC0(26)
#घोषणा IRQ_TIMER3_VIC		S3C64XX_IRQ_VIC0(27)
#घोषणा IRQ_TIMER4_VIC		S3C64XX_IRQ_VIC0(28)
#घोषणा IRQ_LCD_FIFO		S3C64XX_IRQ_VIC0(29)
#घोषणा IRQ_LCD_VSYNC		S3C64XX_IRQ_VIC0(30)
#घोषणा IRQ_LCD_SYSTEM		S3C64XX_IRQ_VIC0(31)

/* VIC1 */

#घोषणा IRQ_EINT12_19		S3C64XX_IRQ_VIC1(0)
#घोषणा IRQ_EINT20_27		S3C64XX_IRQ_VIC1(1)
#घोषणा IRQ_PCM0		S3C64XX_IRQ_VIC1(2)
#घोषणा IRQ_PCM1		S3C64XX_IRQ_VIC1(3)
#घोषणा IRQ_AC97		S3C64XX_IRQ_VIC1(4)
#घोषणा IRQ_UART0		S3C64XX_IRQ_VIC1(5)
#घोषणा IRQ_UART1		S3C64XX_IRQ_VIC1(6)
#घोषणा IRQ_UART2		S3C64XX_IRQ_VIC1(7)
#घोषणा IRQ_UART3		S3C64XX_IRQ_VIC1(8)
#घोषणा IRQ_DMA0		S3C64XX_IRQ_VIC1(9)
#घोषणा IRQ_DMA1		S3C64XX_IRQ_VIC1(10)
#घोषणा IRQ_ONEन_अंकD0		S3C64XX_IRQ_VIC1(11)
#घोषणा IRQ_ONEन_अंकD1		S3C64XX_IRQ_VIC1(12)
#घोषणा IRQ_NFC			S3C64XX_IRQ_VIC1(13)
#घोषणा IRQ_CFCON		S3C64XX_IRQ_VIC1(14)
#घोषणा IRQ_USBH		S3C64XX_IRQ_VIC1(15)
#घोषणा IRQ_SPI0		S3C64XX_IRQ_VIC1(16)
#घोषणा IRQ_SPI1		S3C64XX_IRQ_VIC1(17)
#घोषणा IRQ_IIC			S3C64XX_IRQ_VIC1(18)
#घोषणा IRQ_HSItx		S3C64XX_IRQ_VIC1(19)
#घोषणा IRQ_HSIrx		S3C64XX_IRQ_VIC1(20)
#घोषणा IRQ_RESERVED		S3C64XX_IRQ_VIC1(21)
#घोषणा IRQ_MSM			S3C64XX_IRQ_VIC1(22)
#घोषणा IRQ_HOSTIF		S3C64XX_IRQ_VIC1(23)
#घोषणा IRQ_HSMMC0		S3C64XX_IRQ_VIC1(24)
#घोषणा IRQ_HSMMC1		S3C64XX_IRQ_VIC1(25)
#घोषणा IRQ_HSMMC2		IRQ_SPI1	/* shared with SPI1 */
#घोषणा IRQ_OTG			S3C64XX_IRQ_VIC1(26)
#घोषणा IRQ_IRDA		S3C64XX_IRQ_VIC1(27)
#घोषणा IRQ_RTC_ALARM		S3C64XX_IRQ_VIC1(28)
#घोषणा IRQ_SEC			S3C64XX_IRQ_VIC1(29)
#घोषणा IRQ_PENDN		S3C64XX_IRQ_VIC1(30)
#घोषणा IRQ_TC			IRQ_PENDN
#घोषणा IRQ_ADC			S3C64XX_IRQ_VIC1(31)

/* compatibility क्रम device defines */

#घोषणा IRQ_IIC1		IRQ_S3C6410_IIC1

/* Since the IRQ_EINT(x) are a linear mapping on current s3c64xx series
 * we just defined them as an IRQ_EINT(x) macro from S3C_IRQ_EINT_BASE
 * which we place after the pair of VICs. */

#घोषणा S3C_IRQ_EINT_BASE	S3C_IRQ(64+5)

#घोषणा S3C_EINT(x)		((x) + S3C_IRQ_EINT_BASE)
#घोषणा IRQ_EINT(x)		S3C_EINT(x)
#घोषणा IRQ_EINT_BIT(x)		((x) - S3C_EINT(0))

/* Next the बाह्यal पूर्णांकerrupt groups. These are similar to the IRQ_EINT(x)
 * that they are sourced from the GPIO pins but with a dअगरferent scheme क्रम
 * priority and source indication.
 *
 * The IRQ_EINT(x) can be thought of as 'group 0' of the available GPIO
 * पूर्णांकerrupts, but क्रम historical reasons they are kept apart from these
 * next पूर्णांकerrupts.
 *
 * Use IRQ_EINT_GROUP(group, offset) to get the number क्रम use in the
 * machine specअगरic support files.
 */

#घोषणा IRQ_EINT_GROUP1_NR	(15)
#घोषणा IRQ_EINT_GROUP2_NR	(8)
#घोषणा IRQ_EINT_GROUP3_NR	(5)
#घोषणा IRQ_EINT_GROUP4_NR	(14)
#घोषणा IRQ_EINT_GROUP5_NR	(7)
#घोषणा IRQ_EINT_GROUP6_NR	(10)
#घोषणा IRQ_EINT_GROUP7_NR	(16)
#घोषणा IRQ_EINT_GROUP8_NR	(15)
#घोषणा IRQ_EINT_GROUP9_NR	(9)

#घोषणा IRQ_EINT_GROUP_BASE	S3C_EINT(28)
#घोषणा IRQ_EINT_GROUP1_BASE	(IRQ_EINT_GROUP_BASE + 0x00)
#घोषणा IRQ_EINT_GROUP2_BASE	(IRQ_EINT_GROUP1_BASE + IRQ_EINT_GROUP1_NR)
#घोषणा IRQ_EINT_GROUP3_BASE	(IRQ_EINT_GROUP2_BASE + IRQ_EINT_GROUP2_NR)
#घोषणा IRQ_EINT_GROUP4_BASE	(IRQ_EINT_GROUP3_BASE + IRQ_EINT_GROUP3_NR)
#घोषणा IRQ_EINT_GROUP5_BASE	(IRQ_EINT_GROUP4_BASE + IRQ_EINT_GROUP4_NR)
#घोषणा IRQ_EINT_GROUP6_BASE	(IRQ_EINT_GROUP5_BASE + IRQ_EINT_GROUP5_NR)
#घोषणा IRQ_EINT_GROUP7_BASE	(IRQ_EINT_GROUP6_BASE + IRQ_EINT_GROUP6_NR)
#घोषणा IRQ_EINT_GROUP8_BASE	(IRQ_EINT_GROUP7_BASE + IRQ_EINT_GROUP7_NR)
#घोषणा IRQ_EINT_GROUP9_BASE	(IRQ_EINT_GROUP8_BASE + IRQ_EINT_GROUP8_NR)

#घोषणा IRQ_EINT_GROUP(group, no)	(IRQ_EINT_GROUP##group##_BASE + (no))

/* Some boards have their own IRQs behind this */
#घोषणा IRQ_BOARD_START (IRQ_EINT_GROUP9_BASE + IRQ_EINT_GROUP9_NR + 1)

/* Set the शेष nr_irqs, boards can override अगर necessary */
#घोषणा S3C64XX_NR_IRQS	IRQ_BOARD_START

/* Compatibility */

#घोषणा IRQ_ONEन_अंकD	IRQ_ONEन_अंकD0
#घोषणा IRQ_I2S0	IRQ_S3C6410_IIS

#पूर्ण_अगर /* __ASM_MACH_S3C64XX_IRQS_H */

