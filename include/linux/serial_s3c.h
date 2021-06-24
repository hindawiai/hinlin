<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 *  Internal header file क्रम Samsung S3C2410 serial ports (UART0-2)
 *
 *  Copyright (C) 2002 Shane Nay (shane@minirl.com)
 *
 *  Additional defines, Copyright 2003 Simtec Electronics (linux@simtec.co.uk)
 *
 *  Adapted from:
 *
 *  Internal header file क्रम MX1ADS serial ports (UART1 & 2)
 *
 *  Copyright (C) 2002 Shane Nay (shane@minirl.com)
 */

#अगर_अघोषित __ASM_ARM_REGS_SERIAL_H
#घोषणा __ASM_ARM_REGS_SERIAL_H

#घोषणा S3C2410_URXH	  (0x24)
#घोषणा S3C2410_UTXH	  (0x20)
#घोषणा S3C2410_ULCON	  (0x00)
#घोषणा S3C2410_UCON	  (0x04)
#घोषणा S3C2410_UFCON	  (0x08)
#घोषणा S3C2410_UMCON	  (0x0C)
#घोषणा S3C2410_UBRDIV	  (0x28)
#घोषणा S3C2410_UTRSTAT	  (0x10)
#घोषणा S3C2410_UERSTAT	  (0x14)
#घोषणा S3C2410_UFSTAT	  (0x18)
#घोषणा S3C2410_UMSTAT	  (0x1C)

#घोषणा S3C2410_LCON_CFGMASK	  ((0xF<<3)|(0x3))

#घोषणा S3C2410_LCON_CS5	  (0x0)
#घोषणा S3C2410_LCON_CS6	  (0x1)
#घोषणा S3C2410_LCON_CS7	  (0x2)
#घोषणा S3C2410_LCON_CS8	  (0x3)
#घोषणा S3C2410_LCON_CSMASK	  (0x3)

#घोषणा S3C2410_LCON_PNONE	  (0x0)
#घोषणा S3C2410_LCON_PEVEN	  (0x5 << 3)
#घोषणा S3C2410_LCON_PODD	  (0x4 << 3)
#घोषणा S3C2410_LCON_PMASK	  (0x7 << 3)

#घोषणा S3C2410_LCON_STOPB	  (1<<2)
#घोषणा S3C2410_LCON_IRM          (1<<6)

#घोषणा S3C2440_UCON_CLKMASK	  (3<<10)
#घोषणा S3C2440_UCON_CLKSHIFT	  (10)
#घोषणा S3C2440_UCON_PCLK	  (0<<10)
#घोषणा S3C2440_UCON_UCLK	  (1<<10)
#घोषणा S3C2440_UCON_PCLK2	  (2<<10)
#घोषणा S3C2440_UCON_FCLK	  (3<<10)
#घोषणा S3C2443_UCON_EPLL	  (3<<10)

#घोषणा S3C6400_UCON_CLKMASK	(3<<10)
#घोषणा S3C6400_UCON_CLKSHIFT	(10)
#घोषणा S3C6400_UCON_PCLK	(0<<10)
#घोषणा S3C6400_UCON_PCLK2	(2<<10)
#घोषणा S3C6400_UCON_UCLK0	(1<<10)
#घोषणा S3C6400_UCON_UCLK1	(3<<10)

#घोषणा S3C2440_UCON2_FCLK_EN	  (1<<15)
#घोषणा S3C2440_UCON0_DIVMASK	  (15 << 12)
#घोषणा S3C2440_UCON1_DIVMASK	  (15 << 12)
#घोषणा S3C2440_UCON2_DIVMASK	  (7 << 12)
#घोषणा S3C2440_UCON_DIVSHIFT	  (12)

#घोषणा S3C2412_UCON_CLKMASK	(3<<10)
#घोषणा S3C2412_UCON_CLKSHIFT	(10)
#घोषणा S3C2412_UCON_UCLK	(1<<10)
#घोषणा S3C2412_UCON_USYSCLK	(3<<10)
#घोषणा S3C2412_UCON_PCLK	(0<<10)
#घोषणा S3C2412_UCON_PCLK2	(2<<10)

#घोषणा S3C2410_UCON_CLKMASK	(1 << 10)
#घोषणा S3C2410_UCON_CLKSHIFT	(10)
#घोषणा S3C2410_UCON_UCLK	  (1<<10)
#घोषणा S3C2410_UCON_SBREAK	  (1<<4)

#घोषणा S3C2410_UCON_TXILEVEL	  (1<<9)
#घोषणा S3C2410_UCON_RXILEVEL	  (1<<8)
#घोषणा S3C2410_UCON_TXIRQMODE	  (1<<2)
#घोषणा S3C2410_UCON_RXIRQMODE	  (1<<0)
#घोषणा S3C2410_UCON_RXFIFO_TOI	  (1<<7)
#घोषणा S3C2443_UCON_RXERR_IRQEN  (1<<6)
#घोषणा S3C2443_UCON_LOOPBACK	  (1<<5)

#घोषणा S3C2410_UCON_DEFAULT	  (S3C2410_UCON_TXILEVEL  | \
				   S3C2410_UCON_RXILEVEL  | \
				   S3C2410_UCON_TXIRQMODE | \
				   S3C2410_UCON_RXIRQMODE | \
				   S3C2410_UCON_RXFIFO_TOI)

#घोषणा S3C64XX_UCON_TXBURST_1          (0<<20)
#घोषणा S3C64XX_UCON_TXBURST_4          (1<<20)
#घोषणा S3C64XX_UCON_TXBURST_8          (2<<20)
#घोषणा S3C64XX_UCON_TXBURST_16         (3<<20)
#घोषणा S3C64XX_UCON_TXBURST_MASK       (0xf<<20)
#घोषणा S3C64XX_UCON_RXBURST_1          (0<<16)
#घोषणा S3C64XX_UCON_RXBURST_4          (1<<16)
#घोषणा S3C64XX_UCON_RXBURST_8          (2<<16)
#घोषणा S3C64XX_UCON_RXBURST_16         (3<<16)
#घोषणा S3C64XX_UCON_RXBURST_MASK       (0xf<<16)
#घोषणा S3C64XX_UCON_TIMEOUT_SHIFT      (12)
#घोषणा S3C64XX_UCON_TIMEOUT_MASK       (0xf<<12)
#घोषणा S3C64XX_UCON_EMPTYINT_EN        (1<<11)
#घोषणा S3C64XX_UCON_DMASUS_EN          (1<<10)
#घोषणा S3C64XX_UCON_TXINT_LEVEL        (1<<9)
#घोषणा S3C64XX_UCON_RXINT_LEVEL        (1<<8)
#घोषणा S3C64XX_UCON_TIMEOUT_EN         (1<<7)
#घोषणा S3C64XX_UCON_ERRINT_EN          (1<<6)
#घोषणा S3C64XX_UCON_TXMODE_DMA         (2<<2)
#घोषणा S3C64XX_UCON_TXMODE_CPU         (1<<2)
#घोषणा S3C64XX_UCON_TXMODE_MASK        (3<<2)
#घोषणा S3C64XX_UCON_RXMODE_DMA         (2<<0)
#घोषणा S3C64XX_UCON_RXMODE_CPU         (1<<0)
#घोषणा S3C64XX_UCON_RXMODE_MASK        (3<<0)

#घोषणा S3C2410_UFCON_FIFOMODE	  (1<<0)
#घोषणा S3C2410_UFCON_TXTRIG0	  (0<<6)
#घोषणा S3C2410_UFCON_RXTRIG8	  (1<<4)
#घोषणा S3C2410_UFCON_RXTRIG12	  (2<<4)

/* S3C2440 FIFO trigger levels */
#घोषणा S3C2440_UFCON_RXTRIG1	  (0<<4)
#घोषणा S3C2440_UFCON_RXTRIG8	  (1<<4)
#घोषणा S3C2440_UFCON_RXTRIG16	  (2<<4)
#घोषणा S3C2440_UFCON_RXTRIG32	  (3<<4)

#घोषणा S3C2440_UFCON_TXTRIG0	  (0<<6)
#घोषणा S3C2440_UFCON_TXTRIG16	  (1<<6)
#घोषणा S3C2440_UFCON_TXTRIG32	  (2<<6)
#घोषणा S3C2440_UFCON_TXTRIG48	  (3<<6)

#घोषणा S3C2410_UFCON_RESETBOTH	  (3<<1)
#घोषणा S3C2410_UFCON_RESETTX	  (1<<2)
#घोषणा S3C2410_UFCON_RESETRX	  (1<<1)

#घोषणा S3C2410_UFCON_DEFAULT	  (S3C2410_UFCON_FIFOMODE | \
				   S3C2410_UFCON_TXTRIG0  | \
				   S3C2410_UFCON_RXTRIG8 )

#घोषणा	S3C2410_UMCOM_AFC	  (1<<4)
#घोषणा	S3C2410_UMCOM_RTS_LOW	  (1<<0)

#घोषणा S3C2412_UMCON_AFC_63	(0<<5)		/* same as s3c2443 */
#घोषणा S3C2412_UMCON_AFC_56	(1<<5)
#घोषणा S3C2412_UMCON_AFC_48	(2<<5)
#घोषणा S3C2412_UMCON_AFC_40	(3<<5)
#घोषणा S3C2412_UMCON_AFC_32	(4<<5)
#घोषणा S3C2412_UMCON_AFC_24	(5<<5)
#घोषणा S3C2412_UMCON_AFC_16	(6<<5)
#घोषणा S3C2412_UMCON_AFC_8	(7<<5)

#घोषणा S3C2410_UFSTAT_TXFULL	  (1<<9)
#घोषणा S3C2410_UFSTAT_RXFULL	  (1<<8)
#घोषणा S3C2410_UFSTAT_TXMASK	  (15<<4)
#घोषणा S3C2410_UFSTAT_TXSHIFT	  (4)
#घोषणा S3C2410_UFSTAT_RXMASK	  (15<<0)
#घोषणा S3C2410_UFSTAT_RXSHIFT	  (0)

/* UFSTAT S3C2443 same as S3C2440 */
#घोषणा S3C2440_UFSTAT_TXFULL	  (1<<14)
#घोषणा S3C2440_UFSTAT_RXFULL	  (1<<6)
#घोषणा S3C2440_UFSTAT_TXSHIFT	  (8)
#घोषणा S3C2440_UFSTAT_RXSHIFT	  (0)
#घोषणा S3C2440_UFSTAT_TXMASK	  (63<<8)
#घोषणा S3C2440_UFSTAT_RXMASK	  (63)

#घोषणा S3C2410_UTRSTAT_TIMEOUT   (1<<3)
#घोषणा S3C2410_UTRSTAT_TXE	  (1<<2)
#घोषणा S3C2410_UTRSTAT_TXFE	  (1<<1)
#घोषणा S3C2410_UTRSTAT_RXDR	  (1<<0)

#घोषणा S3C2410_UERSTAT_OVERRUN	  (1<<0)
#घोषणा S3C2410_UERSTAT_FRAME	  (1<<2)
#घोषणा S3C2410_UERSTAT_BREAK	  (1<<3)
#घोषणा S3C2443_UERSTAT_PARITY	  (1<<1)

#घोषणा S3C2410_UERSTAT_ANY	  (S3C2410_UERSTAT_OVERRUN | \
				   S3C2410_UERSTAT_FRAME | \
				   S3C2410_UERSTAT_BREAK)

#घोषणा S3C2410_UMSTAT_CTS	  (1<<0)
#घोषणा S3C2410_UMSTAT_DeltaCTS	  (1<<2)

#घोषणा S3C2443_DIVSLOT		  (0x2C)

/* S3C64XX पूर्णांकerrupt रेजिस्टरs. */
#घोषणा S3C64XX_UINTP		0x30
#घोषणा S3C64XX_UINTSP		0x34
#घोषणा S3C64XX_UINTM		0x38

#घोषणा S3C64XX_UINTM_RXD	(0)
#घोषणा S3C64XX_UINTM_ERROR     (1)
#घोषणा S3C64XX_UINTM_TXD	(2)
#घोषणा S3C64XX_UINTM_RXD_MSK	(1 << S3C64XX_UINTM_RXD)
#घोषणा S3C64XX_UINTM_ERR_MSK   (1 << S3C64XX_UINTM_ERROR)
#घोषणा S3C64XX_UINTM_TXD_MSK	(1 << S3C64XX_UINTM_TXD)

/* Following are specअगरic to S5PV210 */
#घोषणा S5PV210_UCON_CLKMASK	(1<<10)
#घोषणा S5PV210_UCON_CLKSHIFT	(10)
#घोषणा S5PV210_UCON_PCLK	(0<<10)
#घोषणा S5PV210_UCON_UCLK	(1<<10)

#घोषणा S5PV210_UFCON_TXTRIG0	(0<<8)
#घोषणा S5PV210_UFCON_TXTRIG4	(1<<8)
#घोषणा S5PV210_UFCON_TXTRIG8	(2<<8)
#घोषणा S5PV210_UFCON_TXTRIG16	(3<<8)
#घोषणा S5PV210_UFCON_TXTRIG32	(4<<8)
#घोषणा S5PV210_UFCON_TXTRIG64	(5<<8)
#घोषणा S5PV210_UFCON_TXTRIG128 (6<<8)
#घोषणा S5PV210_UFCON_TXTRIG256 (7<<8)

#घोषणा S5PV210_UFCON_RXTRIG1	(0<<4)
#घोषणा S5PV210_UFCON_RXTRIG4	(1<<4)
#घोषणा S5PV210_UFCON_RXTRIG8	(2<<4)
#घोषणा S5PV210_UFCON_RXTRIG16	(3<<4)
#घोषणा S5PV210_UFCON_RXTRIG32	(4<<4)
#घोषणा S5PV210_UFCON_RXTRIG64	(5<<4)
#घोषणा S5PV210_UFCON_RXTRIG128	(6<<4)
#घोषणा S5PV210_UFCON_RXTRIG256	(7<<4)

#घोषणा S5PV210_UFSTAT_TXFULL	(1<<24)
#घोषणा S5PV210_UFSTAT_RXFULL	(1<<8)
#घोषणा S5PV210_UFSTAT_TXMASK	(255<<16)
#घोषणा S5PV210_UFSTAT_TXSHIFT	(16)
#घोषणा S5PV210_UFSTAT_RXMASK	(255<<0)
#घोषणा S5PV210_UFSTAT_RXSHIFT	(0)

#घोषणा S3C2410_UCON_CLKSEL0	(1 << 0)
#घोषणा S3C2410_UCON_CLKSEL1	(1 << 1)
#घोषणा S3C2410_UCON_CLKSEL2	(1 << 2)
#घोषणा S3C2410_UCON_CLKSEL3	(1 << 3)

/* Default values क्रम s5pv210 UCON and UFCON uart रेजिस्टरs */
#घोषणा S5PV210_UCON_DEFAULT	(S3C2410_UCON_TXILEVEL |	\
				 S3C2410_UCON_RXILEVEL |	\
				 S3C2410_UCON_TXIRQMODE |	\
				 S3C2410_UCON_RXIRQMODE |	\
				 S3C2410_UCON_RXFIFO_TOI |	\
				 S3C2443_UCON_RXERR_IRQEN)

#घोषणा S5PV210_UFCON_DEFAULT	(S3C2410_UFCON_FIFOMODE |	\
				 S5PV210_UFCON_TXTRIG4 |	\
				 S5PV210_UFCON_RXTRIG4)

#घोषणा APPLE_S5L_UCON_RXTO_ENA		9
#घोषणा APPLE_S5L_UCON_RXTHRESH_ENA	12
#घोषणा APPLE_S5L_UCON_TXTHRESH_ENA	13
#घोषणा APPLE_S5L_UCON_RXTO_ENA_MSK	(1 << APPLE_S5L_UCON_RXTO_ENA)
#घोषणा APPLE_S5L_UCON_RXTHRESH_ENA_MSK	(1 << APPLE_S5L_UCON_RXTHRESH_ENA)
#घोषणा APPLE_S5L_UCON_TXTHRESH_ENA_MSK	(1 << APPLE_S5L_UCON_TXTHRESH_ENA)

#घोषणा APPLE_S5L_UCON_DEFAULT		(S3C2410_UCON_TXIRQMODE | \
					 S3C2410_UCON_RXIRQMODE | \
					 S3C2410_UCON_RXFIFO_TOI)

#घोषणा APPLE_S5L_UTRSTAT_RXTHRESH	(1<<4)
#घोषणा APPLE_S5L_UTRSTAT_TXTHRESH	(1<<5)
#घोषणा APPLE_S5L_UTRSTAT_RXTO		(1<<9)
#घोषणा APPLE_S5L_UTRSTAT_ALL_FLAGS	(0x3f0)

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/serial_core.h>

/* configuration काष्ठाure क्रम per-machine configurations क्रम the
 * serial port
 *
 * the poपूर्णांकer is setup by the machine specअगरic initialisation from the
 * arch/arm/mach-s3c/ directory.
*/

काष्ठा s3c2410_uartcfg अणु
	अचिन्हित अक्षर	   hwport;	 /* hardware port number */
	अचिन्हित अक्षर	   unused;
	अचिन्हित लघु	   flags;
	upf_t		   uart_flags;	 /* शेष uart flags */
	अचिन्हित पूर्णांक	   clk_sel;

	अचिन्हित पूर्णांक	   has_fracval;

	अचिन्हित दीर्घ	   ucon;	 /* value of ucon क्रम port */
	अचिन्हित दीर्घ	   ulcon;	 /* value of ulcon क्रम port */
	अचिन्हित दीर्घ	   ufcon;	 /* value of ufcon क्रम port */
पूर्ण;

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_ARM_REGS_SERIAL_H */

