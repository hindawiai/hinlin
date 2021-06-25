<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2003 Simtec Electronics <linux@simtec.co.uk>
 *		      http://www.simtec.co.uk/products/SWLINUX/
 *
 * S3C2410 Internal RTC रेजिस्टर definition
*/

#अगर_अघोषित __ASM_ARCH_REGS_RTC_H
#घोषणा __ASM_ARCH_REGS_RTC_H __खाता__

#घोषणा S3C2410_RTCREG(x) (x)
#घोषणा S3C2410_INTP		S3C2410_RTCREG(0x30)
#घोषणा S3C2410_INTP_ALM	(1 << 1)
#घोषणा S3C2410_INTP_TIC	(1 << 0)

#घोषणा S3C2410_RTCCON		S3C2410_RTCREG(0x40)
#घोषणा S3C2410_RTCCON_RTCEN	(1 << 0)
#घोषणा S3C2410_RTCCON_CNTSEL	(1 << 2)
#घोषणा S3C2410_RTCCON_CLKRST	(1 << 3)
#घोषणा S3C2443_RTCCON_TICSEL	(1 << 4)
#घोषणा S3C64XX_RTCCON_TICEN	(1 << 8)

#घोषणा S3C2410_TICNT		S3C2410_RTCREG(0x44)
#घोषणा S3C2410_TICNT_ENABLE	(1 << 7)

/* S3C2443: tick count is 15 bit wide
 * TICNT[6:0] contains upper 7 bits
 * TICNT1[7:0] contains lower 8 bits
 */
#घोषणा S3C2443_TICNT_PART(x)	((x & 0x7f00) >> 8)
#घोषणा S3C2443_TICNT1		S3C2410_RTCREG(0x4C)
#घोषणा S3C2443_TICNT1_PART(x)	(x & 0xff)

/* S3C2416: tick count is 32 bit wide
 * TICNT[6:0] contains bits [14:8]
 * TICNT1[7:0] contains lower 8 bits
 * TICNT2[16:0] contains upper 17 bits
 */
#घोषणा S3C2416_TICNT2		S3C2410_RTCREG(0x48)
#घोषणा S3C2416_TICNT2_PART(x)	((x & 0xffff8000) >> 15)

#घोषणा S3C2410_RTCALM		S3C2410_RTCREG(0x50)
#घोषणा S3C2410_RTCALM_ALMEN	(1 << 6)
#घोषणा S3C2410_RTCALM_YEAREN	(1 << 5)
#घोषणा S3C2410_RTCALM_MONEN	(1 << 4)
#घोषणा S3C2410_RTCALM_DAYEN	(1 << 3)
#घोषणा S3C2410_RTCALM_HOUREN	(1 << 2)
#घोषणा S3C2410_RTCALM_MINEN	(1 << 1)
#घोषणा S3C2410_RTCALM_SECEN	(1 << 0)

#घोषणा S3C2410_ALMSEC		S3C2410_RTCREG(0x54)
#घोषणा S3C2410_ALMMIN		S3C2410_RTCREG(0x58)
#घोषणा S3C2410_ALMHOUR		S3C2410_RTCREG(0x5c)

#घोषणा S3C2410_ALMDATE		S3C2410_RTCREG(0x60)
#घोषणा S3C2410_ALMMON		S3C2410_RTCREG(0x64)
#घोषणा S3C2410_ALMYEAR		S3C2410_RTCREG(0x68)

#घोषणा S3C2410_RTCSEC		S3C2410_RTCREG(0x70)
#घोषणा S3C2410_RTCMIN		S3C2410_RTCREG(0x74)
#घोषणा S3C2410_RTCHOUR		S3C2410_RTCREG(0x78)
#घोषणा S3C2410_RTCDATE		S3C2410_RTCREG(0x7c)
#घोषणा S3C2410_RTCMON		S3C2410_RTCREG(0x84)
#घोषणा S3C2410_RTCYEAR		S3C2410_RTCREG(0x88)

#पूर्ण_अगर /* __ASM_ARCH_REGS_RTC_H */
