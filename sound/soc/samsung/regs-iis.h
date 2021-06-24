<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2003 Simtec Electronics <linux@simtec.co.uk>
 *		      http://www.simtec.co.uk/products/SWLINUX/
 *
 * S3C2410 IIS रेजिस्टर definition
 */

#अगर_अघोषित __SAMSUNG_REGS_IIS_H__
#घोषणा __SAMSUNG_REGS_IIS_H__

#घोषणा S3C2410_IISCON			(0x00)

#घोषणा S3C2410_IISCON_LRINDEX		(1 << 8)
#घोषणा S3C2410_IISCON_TXFIFORDY	(1 << 7)
#घोषणा S3C2410_IISCON_RXFIFORDY	(1 << 6)
#घोषणा S3C2410_IISCON_TXDMAEN		(1 << 5)
#घोषणा S3C2410_IISCON_RXDMAEN		(1 << 4)
#घोषणा S3C2410_IISCON_TXIDLE		(1 << 3)
#घोषणा S3C2410_IISCON_RXIDLE		(1 << 2)
#घोषणा S3C2410_IISCON_PSCEN		(1 << 1)
#घोषणा S3C2410_IISCON_IISEN		(1 << 0)

#घोषणा S3C2410_IISMOD			(0x04)

#घोषणा S3C2440_IISMOD_MPLL		(1 << 9)
#घोषणा S3C2410_IISMOD_SLAVE		(1 << 8)
#घोषणा S3C2410_IISMOD_NOXFER		(0 << 6)
#घोषणा S3C2410_IISMOD_RXMODE		(1 << 6)
#घोषणा S3C2410_IISMOD_TXMODE		(2 << 6)
#घोषणा S3C2410_IISMOD_TXRXMODE		(3 << 6)
#घोषणा S3C2410_IISMOD_LR_LLOW		(0 << 5)
#घोषणा S3C2410_IISMOD_LR_RLOW		(1 << 5)
#घोषणा S3C2410_IISMOD_IIS		(0 << 4)
#घोषणा S3C2410_IISMOD_MSB		(1 << 4)
#घोषणा S3C2410_IISMOD_8BIT		(0 << 3)
#घोषणा S3C2410_IISMOD_16BIT		(1 << 3)
#घोषणा S3C2410_IISMOD_BITMASK		(1 << 3)
#घोषणा S3C2410_IISMOD_256FS		(0 << 2)
#घोषणा S3C2410_IISMOD_384FS		(1 << 2)
#घोषणा S3C2410_IISMOD_16FS		(0 << 0)
#घोषणा S3C2410_IISMOD_32FS		(1 << 0)
#घोषणा S3C2410_IISMOD_48FS		(2 << 0)
#घोषणा S3C2410_IISMOD_FS_MASK		(3 << 0)

#घोषणा S3C2410_IISPSR			(0x08)

#घोषणा S3C2410_IISPSR_INTMASK		(31 << 5)
#घोषणा S3C2410_IISPSR_INTSHIFT		(5)
#घोषणा S3C2410_IISPSR_EXTMASK		(31 << 0)
#घोषणा S3C2410_IISPSR_EXTSHFIT		(0)

#घोषणा S3C2410_IISFCON			(0x0c)

#घोषणा S3C2410_IISFCON_TXDMA		(1 << 15)
#घोषणा S3C2410_IISFCON_RXDMA		(1 << 14)
#घोषणा S3C2410_IISFCON_TXENABLE	(1 << 13)
#घोषणा S3C2410_IISFCON_RXENABLE	(1 << 12)
#घोषणा S3C2410_IISFCON_TXMASK		(0x3f << 6)
#घोषणा S3C2410_IISFCON_TXSHIFT		(6)
#घोषणा S3C2410_IISFCON_RXMASK		(0x3f)
#घोषणा S3C2410_IISFCON_RXSHIFT		(0)

#घोषणा S3C2410_IISFIFO			(0x10)

#पूर्ण_अगर /* __SAMSUNG_REGS_IIS_H__ */
