<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * (c) 2005 Guillaume GOURAT / NexVision
 *          guillaume.gourat@nexvision.fr
 *
 * NexVision OTOM board memory map definitions
 */

/*
 * ok, we've used up to 0x01300000, now we need to find space क्रम the
 * peripherals that live in the nGCS[x] areas, which are quite numerous
 * in their space.
 */

#अगर_अघोषित __MACH_S3C24XX_OTOM_H
#घोषणा __MACH_S3C24XX_OTOM_H __खाता__

#घोषणा OTOM_PA_CS8900A_BASE	(S3C2410_CS3 + 0x01000000)	/* nGCS3 +0x01000000 */
#घोषणा OTOM_VA_CS8900A_BASE	S3C2410_ADDR(0x04000000)	/* 0xF4000000 */

/* physical offset addresses क्रम the peripherals */

#घोषणा OTOM_PA_FLASH0_BASE	(S3C2410_CS0)

#पूर्ण_अगर /* __MACH_S3C24XX_OTOM_H */
