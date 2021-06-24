<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Driver क्रम Renesas R-Car VIN
 *
 * Copyright (C) 2016 Renesas Electronics Corp.
 * Copyright (C) 2011-2013 Renesas Solutions Corp.
 * Copyright (C) 2013 Cogent Embedded, Inc., <source@cogentembedded.com>
 * Copyright (C) 2008 Magnus Damm
 *
 * Based on the soc-camera rcar_vin driver
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pm_runसमय.स>

#समावेश <media/videobuf2-dma-contig.h>

#समावेश "rcar-vin.h"

/* -----------------------------------------------------------------------------
 * HW Functions
 */

/* Register offsets क्रम R-Car VIN */
#घोषणा VNMC_REG	0x00	/* Video n Main Control Register */
#घोषणा VNMS_REG	0x04	/* Video n Module Status Register */
#घोषणा VNFC_REG	0x08	/* Video n Frame Capture Register */
#घोषणा VNSLPRC_REG	0x0C	/* Video n Start Line Pre-Clip Register */
#घोषणा VNELPRC_REG	0x10	/* Video n End Line Pre-Clip Register */
#घोषणा VNSPPRC_REG	0x14	/* Video n Start Pixel Pre-Clip Register */
#घोषणा VNEPPRC_REG	0x18	/* Video n End Pixel Pre-Clip Register */
#घोषणा VNIS_REG	0x2C	/* Video n Image Stride Register */
#घोषणा VNMB_REG(m)	(0x30 + ((m) << 2)) /* Video n Memory Base m Register */
#घोषणा VNIE_REG	0x40	/* Video n Interrupt Enable Register */
#घोषणा VNINTS_REG	0x44	/* Video n Interrupt Status Register */
#घोषणा VNSI_REG	0x48	/* Video n Scanline Interrupt Register */
#घोषणा VNMTC_REG	0x4C	/* Video n Memory Transfer Control Register */
#घोषणा VNDMR_REG	0x58	/* Video n Data Mode Register */
#घोषणा VNDMR2_REG	0x5C	/* Video n Data Mode Register 2 */
#घोषणा VNUVAOF_REG	0x60	/* Video n UV Address Offset Register */

/* Register offsets specअगरic क्रम Gen2 */
#घोषणा VNSLPOC_REG	0x1C	/* Video n Start Line Post-Clip Register */
#घोषणा VNELPOC_REG	0x20	/* Video n End Line Post-Clip Register */
#घोषणा VNSPPOC_REG	0x24	/* Video n Start Pixel Post-Clip Register */
#घोषणा VNEPPOC_REG	0x28	/* Video n End Pixel Post-Clip Register */
#घोषणा VNYS_REG	0x50	/* Video n Y Scale Register */
#घोषणा VNXS_REG	0x54	/* Video n X Scale Register */
#घोषणा VNC1A_REG	0x80	/* Video n Coefficient Set C1A Register */
#घोषणा VNC1B_REG	0x84	/* Video n Coefficient Set C1B Register */
#घोषणा VNC1C_REG	0x88	/* Video n Coefficient Set C1C Register */
#घोषणा VNC2A_REG	0x90	/* Video n Coefficient Set C2A Register */
#घोषणा VNC2B_REG	0x94	/* Video n Coefficient Set C2B Register */
#घोषणा VNC2C_REG	0x98	/* Video n Coefficient Set C2C Register */
#घोषणा VNC3A_REG	0xA0	/* Video n Coefficient Set C3A Register */
#घोषणा VNC3B_REG	0xA4	/* Video n Coefficient Set C3B Register */
#घोषणा VNC3C_REG	0xA8	/* Video n Coefficient Set C3C Register */
#घोषणा VNC4A_REG	0xB0	/* Video n Coefficient Set C4A Register */
#घोषणा VNC4B_REG	0xB4	/* Video n Coefficient Set C4B Register */
#घोषणा VNC4C_REG	0xB8	/* Video n Coefficient Set C4C Register */
#घोषणा VNC5A_REG	0xC0	/* Video n Coefficient Set C5A Register */
#घोषणा VNC5B_REG	0xC4	/* Video n Coefficient Set C5B Register */
#घोषणा VNC5C_REG	0xC8	/* Video n Coefficient Set C5C Register */
#घोषणा VNC6A_REG	0xD0	/* Video n Coefficient Set C6A Register */
#घोषणा VNC6B_REG	0xD4	/* Video n Coefficient Set C6B Register */
#घोषणा VNC6C_REG	0xD8	/* Video n Coefficient Set C6C Register */
#घोषणा VNC7A_REG	0xE0	/* Video n Coefficient Set C7A Register */
#घोषणा VNC7B_REG	0xE4	/* Video n Coefficient Set C7B Register */
#घोषणा VNC7C_REG	0xE8	/* Video n Coefficient Set C7C Register */
#घोषणा VNC8A_REG	0xF0	/* Video n Coefficient Set C8A Register */
#घोषणा VNC8B_REG	0xF4	/* Video n Coefficient Set C8B Register */
#घोषणा VNC8C_REG	0xF8	/* Video n Coefficient Set C8C Register */

/* Register offsets specअगरic क्रम Gen3 */
#घोषणा VNCSI_IFMD_REG		0x20 /* Video n CSI2 Interface Mode Register */

/* Register bit fields क्रम R-Car VIN */
/* Video n Main Control Register bits */
#घोषणा VNMC_DPINE		(1 << 27) /* Gen3 specअगरic */
#घोषणा VNMC_SCLE		(1 << 26) /* Gen3 specअगरic */
#घोषणा VNMC_FOC		(1 << 21)
#घोषणा VNMC_YCAL		(1 << 19)
#घोषणा VNMC_INF_YUV8_BT656	(0 << 16)
#घोषणा VNMC_INF_YUV8_BT601	(1 << 16)
#घोषणा VNMC_INF_YUV10_BT656	(2 << 16)
#घोषणा VNMC_INF_YUV10_BT601	(3 << 16)
#घोषणा VNMC_INF_RAW8		(4 << 16)
#घोषणा VNMC_INF_YUV16		(5 << 16)
#घोषणा VNMC_INF_RGB888		(6 << 16)
#घोषणा VNMC_VUP		(1 << 10)
#घोषणा VNMC_IM_ODD		(0 << 3)
#घोषणा VNMC_IM_ODD_EVEN	(1 << 3)
#घोषणा VNMC_IM_EVEN		(2 << 3)
#घोषणा VNMC_IM_FULL		(3 << 3)
#घोषणा VNMC_BPS		(1 << 1)
#घोषणा VNMC_ME			(1 << 0)

/* Video n Module Status Register bits */
#घोषणा VNMS_FBS_MASK		(3 << 3)
#घोषणा VNMS_FBS_SHIFT		3
#घोषणा VNMS_FS			(1 << 2)
#घोषणा VNMS_AV			(1 << 1)
#घोषणा VNMS_CA			(1 << 0)

/* Video n Frame Capture Register bits */
#घोषणा VNFC_C_FRAME		(1 << 1)
#घोषणा VNFC_S_FRAME		(1 << 0)

/* Video n Interrupt Enable Register bits */
#घोषणा VNIE_FIE		(1 << 4)
#घोषणा VNIE_EFE		(1 << 1)

/* Video n Data Mode Register bits */
#घोषणा VNDMR_A8BIT(n)		(((n) & 0xff) << 24)
#घोषणा VNDMR_A8BIT_MASK	(0xff << 24)
#घोषणा VNDMR_EXRGB		(1 << 8)
#घोषणा VNDMR_BPSM		(1 << 4)
#घोषणा VNDMR_ABIT		(1 << 2)
#घोषणा VNDMR_DTMD_YCSEP	(1 << 1)
#घोषणा VNDMR_DTMD_ARGB		(1 << 0)
#घोषणा VNDMR_DTMD_YCSEP_420	(3 << 0)

/* Video n Data Mode Register 2 bits */
#घोषणा VNDMR2_VPS		(1 << 30)
#घोषणा VNDMR2_HPS		(1 << 29)
#घोषणा VNDMR2_CES		(1 << 28)
#घोषणा VNDMR2_YDS		(1 << 22)
#घोषणा VNDMR2_FTEV		(1 << 17)
#घोषणा VNDMR2_VLV(n)		((n & 0xf) << 12)

/* Video n CSI2 Interface Mode Register (Gen3) */
#घोषणा VNCSI_IFMD_DES1		(1 << 26)
#घोषणा VNCSI_IFMD_DES0		(1 << 25)
#घोषणा VNCSI_IFMD_CSI_CHSEL(n) (((n) & 0xf) << 0)

काष्ठा rvin_buffer अणु
	काष्ठा vb2_v4l2_buffer vb;
	काष्ठा list_head list;
पूर्ण;

#घोषणा to_buf_list(vb2_buffer) (&container_of(vb2_buffer, \
					       काष्ठा rvin_buffer, \
					       vb)->list)

अटल व्योम rvin_ग_लिखो(काष्ठा rvin_dev *vin, u32 value, u32 offset)
अणु
	ioग_लिखो32(value, vin->base + offset);
पूर्ण

अटल u32 rvin_पढ़ो(काष्ठा rvin_dev *vin, u32 offset)
अणु
	वापस ioपढ़ो32(vin->base + offset);
पूर्ण

/* -----------------------------------------------------------------------------
 * Crop and Scaling Gen2
 */

काष्ठा vin_coeff अणु
	अचिन्हित लघु xs_value;
	u32 coeff_set[24];
पूर्ण;

अटल स्थिर काष्ठा vin_coeff vin_coeff_set[] = अणु
	अणु 0x0000, अणु
			  0x00000000, 0x00000000, 0x00000000,
			  0x00000000, 0x00000000, 0x00000000,
			  0x00000000, 0x00000000, 0x00000000,
			  0x00000000, 0x00000000, 0x00000000,
			  0x00000000, 0x00000000, 0x00000000,
			  0x00000000, 0x00000000, 0x00000000,
			  0x00000000, 0x00000000, 0x00000000,
			  0x00000000, 0x00000000, 0x00000000 पूर्ण,
	पूर्ण,
	अणु 0x1000, अणु
			  0x000fa400, 0x000fa400, 0x09625902,
			  0x000003f8, 0x00000403, 0x3de0d9f0,
			  0x001fffed, 0x00000804, 0x3cc1f9c3,
			  0x001003de, 0x00000c01, 0x3cb34d7f,
			  0x002003d2, 0x00000c00, 0x3d24a92d,
			  0x00200bca, 0x00000bff, 0x3df600d2,
			  0x002013cc, 0x000007ff, 0x3ed70c7e,
			  0x00100fde, 0x00000000, 0x3f87c036 पूर्ण,
	पूर्ण,
	अणु 0x1200, अणु
			  0x002ffff1, 0x002ffff1, 0x02a0a9c8,
			  0x002003e7, 0x001ffffa, 0x000185bc,
			  0x002007dc, 0x000003ff, 0x3e52859c,
			  0x00200bd4, 0x00000002, 0x3d53996b,
			  0x00100fd0, 0x00000403, 0x3d04ad2d,
			  0x00000bd5, 0x00000403, 0x3d35ace7,
			  0x3ff003e4, 0x00000801, 0x3dc674a1,
			  0x3fffe800, 0x00000800, 0x3e76f461 पूर्ण,
	पूर्ण,
	अणु 0x1400, अणु
			  0x00100be3, 0x00100be3, 0x04d1359a,
			  0x00000fdb, 0x002003ed, 0x0211fd93,
			  0x00000fd6, 0x002003f4, 0x0002d97b,
			  0x000007d6, 0x002ffffb, 0x3e93b956,
			  0x3ff003da, 0x001003ff, 0x3db49926,
			  0x3fffefe9, 0x00100001, 0x3d655cee,
			  0x3fffd400, 0x00000003, 0x3d65f4b6,
			  0x000fb421, 0x00000402, 0x3dc6547e पूर्ण,
	पूर्ण,
	अणु 0x1600, अणु
			  0x00000bdd, 0x00000bdd, 0x06519578,
			  0x3ff007da, 0x00000be3, 0x03c24973,
			  0x3ff003d9, 0x00000be9, 0x01b30d5f,
			  0x3ffff7df, 0x001003f1, 0x0003c542,
			  0x000fdfec, 0x001003f7, 0x3ec4711d,
			  0x000fc400, 0x002ffffd, 0x3df504f1,
			  0x001fa81a, 0x002ffc00, 0x3d957cc2,
			  0x002f8c3c, 0x00100000, 0x3db5c891 पूर्ण,
	पूर्ण,
	अणु 0x1800, अणु
			  0x3ff003dc, 0x3ff003dc, 0x0791e558,
			  0x000ff7dd, 0x3ff007de, 0x05328554,
			  0x000fe7e3, 0x3ff00be2, 0x03232546,
			  0x000fd7ee, 0x000007e9, 0x0143bd30,
			  0x001fb800, 0x000007ee, 0x00044511,
			  0x002fa015, 0x000007f4, 0x3ef4bcee,
			  0x002f8832, 0x001003f9, 0x3e4514c7,
			  0x001f7853, 0x001003fd, 0x3de54c9f पूर्ण,
	पूर्ण,
	अणु 0x1a00, अणु
			  0x000fefe0, 0x000fefe0, 0x08721d3c,
			  0x001fdbe7, 0x000ffbde, 0x0652a139,
			  0x001fcbf0, 0x000003df, 0x0463292e,
			  0x002fb3ff, 0x3ff007e3, 0x0293a91d,
			  0x002f9c12, 0x3ff00be7, 0x01241905,
			  0x001f8c29, 0x000007ed, 0x3fe470eb,
			  0x000f7c46, 0x000007f2, 0x3f04b8ca,
			  0x3fef7865, 0x000007f6, 0x3e74e4a8 पूर्ण,
	पूर्ण,
	अणु 0x1c00, अणु
			  0x001fd3e9, 0x001fd3e9, 0x08f23d26,
			  0x002fbff3, 0x001fe3e4, 0x0712ad23,
			  0x002fa800, 0x000ff3e0, 0x05631d1b,
			  0x001f9810, 0x000ffbe1, 0x03b3890d,
			  0x000f8c23, 0x000003e3, 0x0233e8fa,
			  0x3fef843b, 0x000003e7, 0x00f430e4,
			  0x3fbf8456, 0x3ff00bea, 0x00046cc8,
			  0x3f8f8c72, 0x3ff00bef, 0x3f3490ac पूर्ण,
	पूर्ण,
	अणु 0x1e00, अणु
			  0x001fbbf4, 0x001fbbf4, 0x09425112,
			  0x001fa800, 0x002fc7ed, 0x0792b110,
			  0x000f980e, 0x001fdbe6, 0x0613110a,
			  0x3fff8c20, 0x001fe7e3, 0x04a368fd,
			  0x3fcf8c33, 0x000ff7e2, 0x0343b8ed,
			  0x3f9f8c4a, 0x000fffe3, 0x0203f8da,
			  0x3f5f9c61, 0x000003e6, 0x00e428c5,
			  0x3f1fb07b, 0x000003eb, 0x3fe440af पूर्ण,
	पूर्ण,
	अणु 0x2000, अणु
			  0x000fa400, 0x000fa400, 0x09625902,
			  0x3fff980c, 0x001fb7f5, 0x0812b0ff,
			  0x3fdf901c, 0x001fc7ed, 0x06b2fcfa,
			  0x3faf902d, 0x001fd3e8, 0x055348f1,
			  0x3f7f983f, 0x001fe3e5, 0x04038ce3,
			  0x3f3fa454, 0x001fefe3, 0x02e3c8d1,
			  0x3f0fb86a, 0x001ff7e4, 0x01c3e8c0,
			  0x3ecfd880, 0x000fffe6, 0x00c404ac पूर्ण,
	पूर्ण,
	अणु 0x2200, अणु
			  0x3fdf9c0b, 0x3fdf9c0b, 0x09725cf4,
			  0x3fbf9818, 0x3fffa400, 0x0842a8f1,
			  0x3f8f9827, 0x000fb3f7, 0x0702f0ec,
			  0x3f5fa037, 0x000fc3ef, 0x05d330e4,
			  0x3f2fac49, 0x001fcfea, 0x04a364d9,
			  0x3effc05c, 0x001fdbe7, 0x038394ca,
			  0x3ecfdc6f, 0x001fe7e6, 0x0273b0bb,
			  0x3ea00083, 0x001fefe6, 0x0183c0a9 पूर्ण,
	पूर्ण,
	अणु 0x2400, अणु
			  0x3f9fa014, 0x3f9fa014, 0x098260e6,
			  0x3f7f9c23, 0x3fcf9c0a, 0x08629ce5,
			  0x3f4fa431, 0x3fefa400, 0x0742d8e1,
			  0x3f1fb440, 0x3fffb3f8, 0x062310d9,
			  0x3eefc850, 0x000fbbf2, 0x050340d0,
			  0x3ecfe062, 0x000fcbec, 0x041364c2,
			  0x3ea00073, 0x001fd3ea, 0x03037cb5,
			  0x3e902086, 0x001fdfe8, 0x022388a5 पूर्ण,
	पूर्ण,
	अणु 0x2600, अणु
			  0x3f5fa81e, 0x3f5fa81e, 0x096258da,
			  0x3f3fac2b, 0x3f8fa412, 0x088290d8,
			  0x3f0fbc38, 0x3fafa408, 0x0772c8d5,
			  0x3eefcc47, 0x3fcfa800, 0x0672f4ce,
			  0x3ecfe456, 0x3fefaffa, 0x05531cc6,
			  0x3eb00066, 0x3fffbbf3, 0x047334bb,
			  0x3ea01c77, 0x000fc7ee, 0x039348ae,
			  0x3ea04486, 0x000fd3eb, 0x02b350a1 पूर्ण,
	पूर्ण,
	अणु 0x2800, अणु
			  0x3f2fb426, 0x3f2fb426, 0x094250ce,
			  0x3f0fc032, 0x3f4fac1b, 0x086284cd,
			  0x3eefd040, 0x3f7fa811, 0x0782acc9,
			  0x3ecfe84c, 0x3f9fa807, 0x06a2d8c4,
			  0x3eb0005b, 0x3fbfac00, 0x05b2f4bc,
			  0x3eb0186a, 0x3fdfb3fa, 0x04c308b4,
			  0x3eb04077, 0x3fefbbf4, 0x03f31ca8,
			  0x3ec06884, 0x000fbff2, 0x03031c9e पूर्ण,
	पूर्ण,
	अणु 0x2a00, अणु
			  0x3f0fc42d, 0x3f0fc42d, 0x090240c4,
			  0x3eefd439, 0x3f2fb822, 0x08526cc2,
			  0x3edfe845, 0x3f4fb018, 0x078294bf,
			  0x3ec00051, 0x3f6fac0f, 0x06b2b4bb,
			  0x3ec0185f, 0x3f8fac07, 0x05e2ccb4,
			  0x3ec0386b, 0x3fafac00, 0x0502e8ac,
			  0x3ed05c77, 0x3fcfb3fb, 0x0432f0a3,
			  0x3ef08482, 0x3fdfbbf6, 0x0372f898 पूर्ण,
	पूर्ण,
	अणु 0x2c00, अणु
			  0x3eefdc31, 0x3eefdc31, 0x08e238b8,
			  0x3edfec3d, 0x3f0fc828, 0x082258b9,
			  0x3ed00049, 0x3f1fc01e, 0x077278b6,
			  0x3ed01455, 0x3f3fb815, 0x06c294b2,
			  0x3ed03460, 0x3f5fb40d, 0x0602acac,
			  0x3ef0506c, 0x3f7fb006, 0x0542c0a4,
			  0x3f107476, 0x3f9fb400, 0x0472c89d,
			  0x3f309c80, 0x3fbfb7fc, 0x03b2cc94 पूर्ण,
	पूर्ण,
	अणु 0x2e00, अणु
			  0x3eefec37, 0x3eefec37, 0x088220b0,
			  0x3ee00041, 0x3effdc2d, 0x07f244ae,
			  0x3ee0144c, 0x3f0fd023, 0x07625cad,
			  0x3ef02c57, 0x3f1fc81a, 0x06c274a9,
			  0x3f004861, 0x3f3fbc13, 0x060288a6,
			  0x3f20686b, 0x3f5fb80c, 0x05529c9e,
			  0x3f408c74, 0x3f6fb805, 0x04b2ac96,
			  0x3f80ac7e, 0x3f8fb800, 0x0402ac8e पूर्ण,
	पूर्ण,
	अणु 0x3000, अणु
			  0x3ef0003a, 0x3ef0003a, 0x084210a6,
			  0x3ef01045, 0x3effec32, 0x07b228a7,
			  0x3f00284e, 0x3f0fdc29, 0x073244a4,
			  0x3f104058, 0x3f0fd420, 0x06a258a2,
			  0x3f305c62, 0x3f2fc818, 0x0612689d,
			  0x3f508069, 0x3f3fc011, 0x05728496,
			  0x3f80a072, 0x3f4fc00a, 0x04d28c90,
			  0x3fc0c07b, 0x3f6fbc04, 0x04429088 पूर्ण,
	पूर्ण,
	अणु 0x3200, अणु
			  0x3f00103e, 0x3f00103e, 0x07f1fc9e,
			  0x3f102447, 0x3f000035, 0x0782149d,
			  0x3f203c4f, 0x3f0ff02c, 0x07122c9c,
			  0x3f405458, 0x3f0fe424, 0x06924099,
			  0x3f607061, 0x3f1fd41d, 0x06024c97,
			  0x3f909068, 0x3f2fcc16, 0x05726490,
			  0x3fc0b070, 0x3f3fc80f, 0x04f26c8a,
			  0x0000d077, 0x3f4fc409, 0x04627484 पूर्ण,
	पूर्ण,
	अणु 0x3400, अणु
			  0x3f202040, 0x3f202040, 0x07a1e898,
			  0x3f303449, 0x3f100c38, 0x0741fc98,
			  0x3f504c50, 0x3f10002f, 0x06e21495,
			  0x3f706459, 0x3f1ff028, 0x06722492,
			  0x3fa08060, 0x3f1fe421, 0x05f2348f,
			  0x3fd09c67, 0x3f1fdc19, 0x05824c89,
			  0x0000bc6e, 0x3f2fd014, 0x04f25086,
			  0x0040dc74, 0x3f3fcc0d, 0x04825c7f पूर्ण,
	पूर्ण,
	अणु 0x3600, अणु
			  0x3f403042, 0x3f403042, 0x0761d890,
			  0x3f504848, 0x3f301c3b, 0x0701f090,
			  0x3f805c50, 0x3f200c33, 0x06a2008f,
			  0x3fa07458, 0x3f10002b, 0x06520c8d,
			  0x3fd0905e, 0x3f1ff424, 0x05e22089,
			  0x0000ac65, 0x3f1fe81d, 0x05823483,
			  0x0030cc6a, 0x3f2fdc18, 0x04f23c81,
			  0x0080e871, 0x3f2fd412, 0x0482407c पूर्ण,
	पूर्ण,
	अणु 0x3800, अणु
			  0x3f604043, 0x3f604043, 0x0721c88a,
			  0x3f80544a, 0x3f502c3c, 0x06d1d88a,
			  0x3fb06851, 0x3f301c35, 0x0681e889,
			  0x3fd08456, 0x3f30082f, 0x0611fc88,
			  0x00009c5d, 0x3f200027, 0x05d20884,
			  0x0030b863, 0x3f2ff421, 0x05621880,
			  0x0070d468, 0x3f2fe81b, 0x0502247c,
			  0x00c0ec6f, 0x3f2fe015, 0x04a22877 पूर्ण,
	पूर्ण,
	अणु 0x3a00, अणु
			  0x3f904c44, 0x3f904c44, 0x06e1b884,
			  0x3fb0604a, 0x3f70383e, 0x0691c885,
			  0x3fe07451, 0x3f502c36, 0x0661d483,
			  0x00009055, 0x3f401831, 0x0601ec81,
			  0x0030a85b, 0x3f300c2a, 0x05b1f480,
			  0x0070c061, 0x3f300024, 0x0562047a,
			  0x00b0d867, 0x3f3ff41e, 0x05020c77,
			  0x00f0f46b, 0x3f2fec19, 0x04a21474 पूर्ण,
	पूर्ण,
	अणु 0x3c00, अणु
			  0x3fb05c43, 0x3fb05c43, 0x06c1b07e,
			  0x3fe06c4b, 0x3f902c3f, 0x0681c081,
			  0x0000844f, 0x3f703838, 0x0631cc7d,
			  0x00309855, 0x3f602433, 0x05d1d47e,
			  0x0060b459, 0x3f50142e, 0x0581e47b,
			  0x00a0c85f, 0x3f400828, 0x0531f078,
			  0x00e0e064, 0x3f300021, 0x0501fc73,
			  0x00b0fc6a, 0x3f3ff41d, 0x04a20873 पूर्ण,
	पूर्ण,
	अणु 0x3e00, अणु
			  0x3fe06444, 0x3fe06444, 0x0681a07a,
			  0x00007849, 0x3fc0503f, 0x0641b07a,
			  0x0020904d, 0x3fa0403a, 0x05f1c07a,
			  0x0060a453, 0x3f803034, 0x05c1c878,
			  0x0090b858, 0x3f70202f, 0x0571d477,
			  0x00d0d05d, 0x3f501829, 0x0531e073,
			  0x0110e462, 0x3f500825, 0x04e1e471,
			  0x01510065, 0x3f40001f, 0x04a1f06d पूर्ण,
	पूर्ण,
	अणु 0x4000, अणु
			  0x00007044, 0x00007044, 0x06519476,
			  0x00208448, 0x3fe05c3f, 0x0621a476,
			  0x0050984d, 0x3fc04c3a, 0x05e1b075,
			  0x0080ac52, 0x3fa03c35, 0x05a1b875,
			  0x00c0c056, 0x3f803030, 0x0561c473,
			  0x0100d45b, 0x3f70202b, 0x0521d46f,
			  0x0140e860, 0x3f601427, 0x04d1d46e,
			  0x01810064, 0x3f500822, 0x0491dc6b पूर्ण,
	पूर्ण,
	अणु 0x5000, अणु
			  0x0110a442, 0x0110a442, 0x0551545e,
			  0x0140b045, 0x00e0983f, 0x0531585f,
			  0x0160c047, 0x00c08c3c, 0x0511645e,
			  0x0190cc4a, 0x00908039, 0x04f1685f,
			  0x01c0dc4c, 0x00707436, 0x04d1705e,
			  0x0200e850, 0x00506833, 0x04b1785b,
			  0x0230f453, 0x00305c30, 0x0491805a,
			  0x02710056, 0x0010542d, 0x04718059 पूर्ण,
	पूर्ण,
	अणु 0x6000, अणु
			  0x01c0bc40, 0x01c0bc40, 0x04c13052,
			  0x01e0c841, 0x01a0b43d, 0x04c13851,
			  0x0210cc44, 0x0180a83c, 0x04a13453,
			  0x0230d845, 0x0160a03a, 0x04913c52,
			  0x0260e047, 0x01409838, 0x04714052,
			  0x0280ec49, 0x01208c37, 0x04514c50,
			  0x02b0f44b, 0x01008435, 0x04414c50,
			  0x02d1004c, 0x00e07c33, 0x0431544f पूर्ण,
	पूर्ण,
	अणु 0x7000, अणु
			  0x0230c83e, 0x0230c83e, 0x04711c4c,
			  0x0250d03f, 0x0210c43c, 0x0471204b,
			  0x0270d840, 0x0200b83c, 0x0451244b,
			  0x0290dc42, 0x01e0b43a, 0x0441244c,
			  0x02b0e443, 0x01c0b038, 0x0441284b,
			  0x02d0ec44, 0x01b0a438, 0x0421304a,
			  0x02f0f445, 0x0190a036, 0x04213449,
			  0x0310f847, 0x01709c34, 0x04213848 पूर्ण,
	पूर्ण,
	अणु 0x8000, अणु
			  0x0280d03d, 0x0280d03d, 0x04310c48,
			  0x02a0d43e, 0x0270c83c, 0x04311047,
			  0x02b0dc3e, 0x0250c83a, 0x04311447,
			  0x02d0e040, 0x0240c03a, 0x04211446,
			  0x02e0e840, 0x0220bc39, 0x04111847,
			  0x0300e842, 0x0210b438, 0x04012445,
			  0x0310f043, 0x0200b037, 0x04012045,
			  0x0330f444, 0x01e0ac36, 0x03f12445 पूर्ण,
	पूर्ण,
	अणु 0xefff, अणु
			  0x0340dc3a, 0x0340dc3a, 0x03b0ec40,
			  0x0340e03a, 0x0330e039, 0x03c0f03e,
			  0x0350e03b, 0x0330dc39, 0x03c0ec3e,
			  0x0350e43a, 0x0320dc38, 0x03c0f43e,
			  0x0360e43b, 0x0320d839, 0x03b0f03e,
			  0x0360e83b, 0x0310d838, 0x03c0fc3b,
			  0x0370e83b, 0x0310d439, 0x03a0f83d,
			  0x0370e83c, 0x0300d438, 0x03b0fc3c पूर्ण,
	पूर्ण
पूर्ण;

अटल व्योम rvin_set_coeff(काष्ठा rvin_dev *vin, अचिन्हित लघु xs)
अणु
	पूर्णांक i;
	स्थिर काष्ठा vin_coeff *p_prev_set = शून्य;
	स्थिर काष्ठा vin_coeff *p_set = शून्य;

	/* Look क्रम suitable coefficient values */
	क्रम (i = 0; i < ARRAY_SIZE(vin_coeff_set); i++) अणु
		p_prev_set = p_set;
		p_set = &vin_coeff_set[i];

		अगर (xs < p_set->xs_value)
			अवरोध;
	पूर्ण

	/* Use previous value अगर its XS value is बंदr */
	अगर (p_prev_set &&
	    xs - p_prev_set->xs_value < p_set->xs_value - xs)
		p_set = p_prev_set;

	/* Set coefficient रेजिस्टरs */
	rvin_ग_लिखो(vin, p_set->coeff_set[0], VNC1A_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[1], VNC1B_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[2], VNC1C_REG);

	rvin_ग_लिखो(vin, p_set->coeff_set[3], VNC2A_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[4], VNC2B_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[5], VNC2C_REG);

	rvin_ग_लिखो(vin, p_set->coeff_set[6], VNC3A_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[7], VNC3B_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[8], VNC3C_REG);

	rvin_ग_लिखो(vin, p_set->coeff_set[9], VNC4A_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[10], VNC4B_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[11], VNC4C_REG);

	rvin_ग_लिखो(vin, p_set->coeff_set[12], VNC5A_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[13], VNC5B_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[14], VNC5C_REG);

	rvin_ग_लिखो(vin, p_set->coeff_set[15], VNC6A_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[16], VNC6B_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[17], VNC6C_REG);

	rvin_ग_लिखो(vin, p_set->coeff_set[18], VNC7A_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[19], VNC7B_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[20], VNC7C_REG);

	rvin_ग_लिखो(vin, p_set->coeff_set[21], VNC8A_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[22], VNC8B_REG);
	rvin_ग_लिखो(vin, p_set->coeff_set[23], VNC8C_REG);
पूर्ण

अटल व्योम rvin_crop_scale_comp_gen2(काष्ठा rvin_dev *vin)
अणु
	अचिन्हित पूर्णांक crop_height;
	u32 xs, ys;

	/* Set scaling coefficient */
	crop_height = vin->crop.height;
	अगर (V4L2_FIELD_HAS_BOTH(vin->क्रमmat.field))
		crop_height *= 2;

	ys = 0;
	अगर (crop_height != vin->compose.height)
		ys = (4096 * crop_height) / vin->compose.height;
	rvin_ग_लिखो(vin, ys, VNYS_REG);

	xs = 0;
	अगर (vin->crop.width != vin->compose.width)
		xs = (4096 * vin->crop.width) / vin->compose.width;

	/* Horizontal upscaling is up to द्विगुन size */
	अगर (xs > 0 && xs < 2048)
		xs = 2048;

	rvin_ग_लिखो(vin, xs, VNXS_REG);

	/* Horizontal upscaling is करोne out by scaling करोwn from द्विगुन size */
	अगर (xs < 4096)
		xs *= 2;

	rvin_set_coeff(vin, xs);

	/* Set Start/End Pixel/Line Post-Clip */
	rvin_ग_लिखो(vin, 0, VNSPPOC_REG);
	rvin_ग_लिखो(vin, 0, VNSLPOC_REG);
	rvin_ग_लिखो(vin, vin->क्रमmat.width - 1, VNEPPOC_REG);

	अगर (V4L2_FIELD_HAS_BOTH(vin->क्रमmat.field))
		rvin_ग_लिखो(vin, vin->क्रमmat.height / 2 - 1, VNELPOC_REG);
	अन्यथा
		rvin_ग_लिखो(vin, vin->क्रमmat.height - 1, VNELPOC_REG);

	vin_dbg(vin,
		"Pre-Clip: %ux%u@%u:%u YS: %d XS: %d Post-Clip: %ux%u@%u:%u\n",
		vin->crop.width, vin->crop.height, vin->crop.left,
		vin->crop.top, ys, xs, vin->क्रमmat.width, vin->क्रमmat.height,
		0, 0);
पूर्ण

व्योम rvin_crop_scale_comp(काष्ठा rvin_dev *vin)
अणु
	स्थिर काष्ठा rvin_video_क्रमmat *fmt;
	u32 stride;

	/* Set Start/End Pixel/Line Pre-Clip */
	rvin_ग_लिखो(vin, vin->crop.left, VNSPPRC_REG);
	rvin_ग_लिखो(vin, vin->crop.left + vin->crop.width - 1, VNEPPRC_REG);
	rvin_ग_लिखो(vin, vin->crop.top, VNSLPRC_REG);
	rvin_ग_लिखो(vin, vin->crop.top + vin->crop.height - 1, VNELPRC_REG);

	/* TODO: Add support क्रम the UDS scaler. */
	अगर (vin->info->model != RCAR_GEN3)
		rvin_crop_scale_comp_gen2(vin);

	fmt = rvin_क्रमmat_from_pixel(vin, vin->क्रमmat.pixelक्रमmat);
	stride = vin->क्रमmat.bytesperline / fmt->bpp;

	/* For RAW8 क्रमmat bpp is 1, but the hardware process RAW8
	 * क्रमmat in 2 pixel unit hence configure VNIS_REG as stride / 2.
	 */
	चयन (vin->क्रमmat.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_SBGGR8:
	हाल V4L2_PIX_FMT_SGBRG8:
	हाल V4L2_PIX_FMT_SGRBG8:
	हाल V4L2_PIX_FMT_SRGGB8:
		stride /= 2;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	rvin_ग_लिखो(vin, stride, VNIS_REG);
पूर्ण

/* -----------------------------------------------------------------------------
 * Hardware setup
 */

अटल पूर्णांक rvin_setup(काष्ठा rvin_dev *vin)
अणु
	u32 vnmc, dmr, dmr2, पूर्णांकerrupts;
	bool progressive = false, output_is_yuv = false, input_is_yuv = false;

	चयन (vin->क्रमmat.field) अणु
	हाल V4L2_FIELD_TOP:
		vnmc = VNMC_IM_ODD;
		अवरोध;
	हाल V4L2_FIELD_BOTTOM:
		vnmc = VNMC_IM_EVEN;
		अवरोध;
	हाल V4L2_FIELD_INTERLACED:
		/* Default to TB */
		vnmc = VNMC_IM_FULL;
		/* Use BT अगर video standard can be पढ़ो and is 60 Hz क्रमmat */
		अगर (!vin->info->use_mc && vin->std & V4L2_STD_525_60)
			vnmc = VNMC_IM_FULL | VNMC_FOC;
		अवरोध;
	हाल V4L2_FIELD_INTERLACED_TB:
		vnmc = VNMC_IM_FULL;
		अवरोध;
	हाल V4L2_FIELD_INTERLACED_BT:
		vnmc = VNMC_IM_FULL | VNMC_FOC;
		अवरोध;
	हाल V4L2_FIELD_SEQ_TB:
	हाल V4L2_FIELD_SEQ_BT:
	हाल V4L2_FIELD_NONE:
		vnmc = VNMC_IM_ODD_EVEN;
		progressive = true;
		अवरोध;
	हाल V4L2_FIELD_ALTERNATE:
		vnmc = VNMC_IM_ODD_EVEN;
		अवरोध;
	शेष:
		vnmc = VNMC_IM_ODD;
		अवरोध;
	पूर्ण

	/*
	 * Input पूर्णांकerface
	 */
	चयन (vin->mbus_code) अणु
	हाल MEDIA_BUS_FMT_YUYV8_1X16:
		/* BT.601/BT.1358 16bit YCbCr422 */
		vnmc |= VNMC_INF_YUV16;
		input_is_yuv = true;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
		vnmc |= VNMC_INF_YUV16 | VNMC_YCAL;
		input_is_yuv = true;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
		/* BT.656 8bit YCbCr422 or BT.601 8bit YCbCr422 */
		अगर (!vin->is_csi &&
		    vin->parallel.mbus_type == V4L2_MBUS_BT656)
			vnmc |= VNMC_INF_YUV8_BT656;
		अन्यथा
			vnmc |= VNMC_INF_YUV8_BT601;

		input_is_yuv = true;
		अवरोध;
	हाल MEDIA_BUS_FMT_RGB888_1X24:
		vnmc |= VNMC_INF_RGB888;
		अवरोध;
	हाल MEDIA_BUS_FMT_UYVY10_2X10:
		/* BT.656 10bit YCbCr422 or BT.601 10bit YCbCr422 */
		अगर (!vin->is_csi &&
		    vin->parallel.mbus_type == V4L2_MBUS_BT656)
			vnmc |= VNMC_INF_YUV10_BT656;
		अन्यथा
			vnmc |= VNMC_INF_YUV10_BT601;

		input_is_yuv = true;
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
	हाल MEDIA_BUS_FMT_SGBRG8_1X8:
	हाल MEDIA_BUS_FMT_SGRBG8_1X8:
	हाल MEDIA_BUS_FMT_SRGGB8_1X8:
		vnmc |= VNMC_INF_RAW8;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* Enable VSYNC Field Toggle mode after one VSYNC input */
	अगर (vin->info->model == RCAR_GEN3)
		dmr2 = VNDMR2_FTEV;
	अन्यथा
		dmr2 = VNDMR2_FTEV | VNDMR2_VLV(1);

	अगर (!vin->is_csi) अणु
		/* Hsync Signal Polarity Select */
		अगर (!(vin->parallel.bus.flags & V4L2_MBUS_HSYNC_ACTIVE_LOW))
			dmr2 |= VNDMR2_HPS;

		/* Vsync Signal Polarity Select */
		अगर (!(vin->parallel.bus.flags & V4L2_MBUS_VSYNC_ACTIVE_LOW))
			dmr2 |= VNDMR2_VPS;

		/* Data Enable Polarity Select */
		अगर (vin->parallel.bus.flags & V4L2_MBUS_DATA_ENABLE_LOW)
			dmr2 |= VNDMR2_CES;

		चयन (vin->mbus_code) अणु
		हाल MEDIA_BUS_FMT_UYVY8_2X8:
			अगर (vin->parallel.bus.bus_width == 8 &&
			    vin->parallel.bus.data_shअगरt == 8)
				dmr2 |= VNDMR2_YDS;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	/*
	 * Output क्रमmat
	 */
	चयन (vin->क्रमmat.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_NV12:
	हाल V4L2_PIX_FMT_NV16:
		rvin_ग_लिखो(vin,
			   ALIGN(vin->क्रमmat.bytesperline * vin->क्रमmat.height,
				 0x80), VNUVAOF_REG);
		dmr = vin->क्रमmat.pixelक्रमmat == V4L2_PIX_FMT_NV12 ?
			VNDMR_DTMD_YCSEP_420 : VNDMR_DTMD_YCSEP;
		output_is_yuv = true;
		अवरोध;
	हाल V4L2_PIX_FMT_YUYV:
		dmr = VNDMR_BPSM;
		output_is_yuv = true;
		अवरोध;
	हाल V4L2_PIX_FMT_UYVY:
		dmr = 0;
		output_is_yuv = true;
		अवरोध;
	हाल V4L2_PIX_FMT_XRGB555:
		dmr = VNDMR_DTMD_ARGB;
		अवरोध;
	हाल V4L2_PIX_FMT_RGB565:
		dmr = 0;
		अवरोध;
	हाल V4L2_PIX_FMT_XBGR32:
		/* Note: not supported on M1 */
		dmr = VNDMR_EXRGB;
		अवरोध;
	हाल V4L2_PIX_FMT_ARGB555:
		dmr = (vin->alpha ? VNDMR_ABIT : 0) | VNDMR_DTMD_ARGB;
		अवरोध;
	हाल V4L2_PIX_FMT_ABGR32:
		dmr = VNDMR_A8BIT(vin->alpha) | VNDMR_EXRGB | VNDMR_DTMD_ARGB;
		अवरोध;
	हाल V4L2_PIX_FMT_SBGGR8:
	हाल V4L2_PIX_FMT_SGBRG8:
	हाल V4L2_PIX_FMT_SGRBG8:
	हाल V4L2_PIX_FMT_SRGGB8:
		dmr = 0;
		अवरोध;
	शेष:
		vin_err(vin, "Invalid pixelformat (0x%x)\n",
			vin->क्रमmat.pixelक्रमmat);
		वापस -EINVAL;
	पूर्ण

	/* Always update on field change */
	vnmc |= VNMC_VUP;

	/* If input and output use the same colorspace, use bypass mode */
	अगर (input_is_yuv == output_is_yuv)
		vnmc |= VNMC_BPS;

	अगर (vin->info->model == RCAR_GEN3) अणु
		/* Select between CSI-2 and parallel input */
		अगर (vin->is_csi)
			vnmc &= ~VNMC_DPINE;
		अन्यथा
			vnmc |= VNMC_DPINE;
	पूर्ण

	/* Progressive or पूर्णांकerlaced mode */
	पूर्णांकerrupts = progressive ? VNIE_FIE : VNIE_EFE;

	/* Ack पूर्णांकerrupts */
	rvin_ग_लिखो(vin, पूर्णांकerrupts, VNINTS_REG);
	/* Enable पूर्णांकerrupts */
	rvin_ग_लिखो(vin, पूर्णांकerrupts, VNIE_REG);
	/* Start capturing */
	rvin_ग_लिखो(vin, dmr, VNDMR_REG);
	rvin_ग_लिखो(vin, dmr2, VNDMR2_REG);

	/* Enable module */
	rvin_ग_लिखो(vin, vnmc | VNMC_ME, VNMC_REG);

	वापस 0;
पूर्ण

अटल व्योम rvin_disable_पूर्णांकerrupts(काष्ठा rvin_dev *vin)
अणु
	rvin_ग_लिखो(vin, 0, VNIE_REG);
पूर्ण

अटल u32 rvin_get_पूर्णांकerrupt_status(काष्ठा rvin_dev *vin)
अणु
	वापस rvin_पढ़ो(vin, VNINTS_REG);
पूर्ण

अटल व्योम rvin_ack_पूर्णांकerrupt(काष्ठा rvin_dev *vin)
अणु
	rvin_ग_लिखो(vin, rvin_पढ़ो(vin, VNINTS_REG), VNINTS_REG);
पूर्ण

अटल bool rvin_capture_active(काष्ठा rvin_dev *vin)
अणु
	वापस rvin_पढ़ो(vin, VNMS_REG) & VNMS_CA;
पूर्ण

अटल क्रमागत v4l2_field rvin_get_active_field(काष्ठा rvin_dev *vin, u32 vnms)
अणु
	अगर (vin->क्रमmat.field == V4L2_FIELD_ALTERNATE) अणु
		/* If FS is set it is an Even field. */
		अगर (vnms & VNMS_FS)
			वापस V4L2_FIELD_BOTTOM;
		वापस V4L2_FIELD_TOP;
	पूर्ण

	वापस vin->क्रमmat.field;
पूर्ण

अटल व्योम rvin_set_slot_addr(काष्ठा rvin_dev *vin, पूर्णांक slot, dma_addr_t addr)
अणु
	स्थिर काष्ठा rvin_video_क्रमmat *fmt;
	पूर्णांक offsetx, offsety;
	dma_addr_t offset;

	fmt = rvin_क्रमmat_from_pixel(vin, vin->क्रमmat.pixelक्रमmat);

	/*
	 * There is no HW support क्रम composition करो the beast we can
	 * by modअगरying the buffer offset
	 */
	offsetx = vin->compose.left * fmt->bpp;
	offsety = vin->compose.top * vin->क्रमmat.bytesperline;
	offset = addr + offsetx + offsety;

	/*
	 * The address needs to be 128 bytes aligned. Driver should never accept
	 * settings that करो not satisfy this in the first place...
	 */
	अगर (WARN_ON((offsetx | offsety | offset) & HW_BUFFER_MASK))
		वापस;

	rvin_ग_लिखो(vin, offset, VNMB_REG(slot));
पूर्ण

/*
 * Moves a buffer from the queue to the HW slot. If no buffer is
 * available use the scratch buffer. The scratch buffer is never
 * वापसed to userspace, its only function is to enable the capture
 * loop to keep running.
 */
अटल व्योम rvin_fill_hw_slot(काष्ठा rvin_dev *vin, पूर्णांक slot)
अणु
	काष्ठा rvin_buffer *buf;
	काष्ठा vb2_v4l2_buffer *vbuf;
	dma_addr_t phys_addr;
	पूर्णांक prev;

	/* A alपढ़ोy populated slot shall never be overwritten. */
	अगर (WARN_ON(vin->buf_hw[slot].buffer))
		वापस;

	prev = (slot == 0 ? HW_BUFFER_NUM : slot) - 1;

	अगर (vin->buf_hw[prev].type == HALF_TOP) अणु
		vbuf = vin->buf_hw[prev].buffer;
		vin->buf_hw[slot].buffer = vbuf;
		vin->buf_hw[slot].type = HALF_BOTTOM;
		चयन (vin->क्रमmat.pixelक्रमmat) अणु
		हाल V4L2_PIX_FMT_NV12:
		हाल V4L2_PIX_FMT_NV16:
			phys_addr = vin->buf_hw[prev].phys +
				vin->क्रमmat.sizeimage / 4;
			अवरोध;
		शेष:
			phys_addr = vin->buf_hw[prev].phys +
				vin->क्रमmat.sizeimage / 2;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अगर (vin->state != RUNNING || list_empty(&vin->buf_list)) अणु
		vin->buf_hw[slot].buffer = शून्य;
		vin->buf_hw[slot].type = FULL;
		phys_addr = vin->scratch_phys;
	पूर्ण अन्यथा अणु
		/* Keep track of buffer we give to HW */
		buf = list_entry(vin->buf_list.next, काष्ठा rvin_buffer, list);
		vbuf = &buf->vb;
		list_del_init(to_buf_list(vbuf));
		vin->buf_hw[slot].buffer = vbuf;

		vin->buf_hw[slot].type =
			V4L2_FIELD_IS_SEQUENTIAL(vin->क्रमmat.field) ?
			HALF_TOP : FULL;

		/* Setup DMA */
		phys_addr = vb2_dma_contig_plane_dma_addr(&vbuf->vb2_buf, 0);
	पूर्ण

	vin_dbg(vin, "Filling HW slot: %d type: %d buffer: %p\n",
		slot, vin->buf_hw[slot].type, vin->buf_hw[slot].buffer);

	vin->buf_hw[slot].phys = phys_addr;
	rvin_set_slot_addr(vin, slot, phys_addr);
पूर्ण

अटल पूर्णांक rvin_capture_start(काष्ठा rvin_dev *vin)
अणु
	पूर्णांक slot, ret;

	क्रम (slot = 0; slot < HW_BUFFER_NUM; slot++) अणु
		vin->buf_hw[slot].buffer = शून्य;
		vin->buf_hw[slot].type = FULL;
	पूर्ण

	क्रम (slot = 0; slot < HW_BUFFER_NUM; slot++)
		rvin_fill_hw_slot(vin, slot);

	rvin_crop_scale_comp(vin);

	ret = rvin_setup(vin);
	अगर (ret)
		वापस ret;

	vin_dbg(vin, "Starting to capture\n");

	/* Continuous Frame Capture Mode */
	rvin_ग_लिखो(vin, VNFC_C_FRAME, VNFC_REG);

	vin->state = STARTING;

	वापस 0;
पूर्ण

अटल व्योम rvin_capture_stop(काष्ठा rvin_dev *vin)
अणु
	/* Set continuous & single transfer off */
	rvin_ग_लिखो(vin, 0, VNFC_REG);

	/* Disable module */
	rvin_ग_लिखो(vin, rvin_पढ़ो(vin, VNMC_REG) & ~VNMC_ME, VNMC_REG);
पूर्ण

/* -----------------------------------------------------------------------------
 * DMA Functions
 */

#घोषणा RVIN_TIMEOUT_MS 100
#घोषणा RVIN_RETRIES 10

अटल irqवापस_t rvin_irq(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा rvin_dev *vin = data;
	u32 पूर्णांक_status, vnms;
	पूर्णांक slot;
	अचिन्हित पूर्णांक handled = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vin->qlock, flags);

	पूर्णांक_status = rvin_get_पूर्णांकerrupt_status(vin);
	अगर (!पूर्णांक_status)
		जाओ करोne;

	rvin_ack_पूर्णांकerrupt(vin);
	handled = 1;

	/* Nothing to करो अगर capture status is 'STOPPED' */
	अगर (vin->state == STOPPED) अणु
		vin_dbg(vin, "IRQ while state stopped\n");
		जाओ करोne;
	पूर्ण

	/* Prepare क्रम capture and update state */
	vnms = rvin_पढ़ो(vin, VNMS_REG);
	slot = (vnms & VNMS_FBS_MASK) >> VNMS_FBS_SHIFT;

	/*
	 * To hand buffers back in a known order to userspace start
	 * to capture first from slot 0.
	 */
	अगर (vin->state == STARTING) अणु
		अगर (slot != 0) अणु
			vin_dbg(vin, "Starting sync slot: %d\n", slot);
			जाओ करोne;
		पूर्ण

		vin_dbg(vin, "Capture start synced!\n");
		vin->state = RUNNING;
	पूर्ण

	/* Capture frame */
	अगर (vin->buf_hw[slot].buffer) अणु
		/*
		 * Nothing to करो but refill the hardware slot अगर
		 * capture only filled first half of vb2 buffer.
		 */
		अगर (vin->buf_hw[slot].type == HALF_TOP) अणु
			vin->buf_hw[slot].buffer = शून्य;
			rvin_fill_hw_slot(vin, slot);
			जाओ करोne;
		पूर्ण

		vin->buf_hw[slot].buffer->field =
			rvin_get_active_field(vin, vnms);
		vin->buf_hw[slot].buffer->sequence = vin->sequence;
		vin->buf_hw[slot].buffer->vb2_buf.बारtamp = kसमय_get_ns();
		vb2_buffer_करोne(&vin->buf_hw[slot].buffer->vb2_buf,
				VB2_BUF_STATE_DONE);
		vin->buf_hw[slot].buffer = शून्य;
	पूर्ण अन्यथा अणु
		/* Scratch buffer was used, dropping frame. */
		vin_dbg(vin, "Dropping frame %u\n", vin->sequence);
	पूर्ण

	vin->sequence++;

	/* Prepare क्रम next frame */
	rvin_fill_hw_slot(vin, slot);
करोne:
	spin_unlock_irqrestore(&vin->qlock, flags);

	वापस IRQ_RETVAL(handled);
पूर्ण

अटल व्योम वापस_unused_buffers(काष्ठा rvin_dev *vin,
				  क्रमागत vb2_buffer_state state)
अणु
	काष्ठा rvin_buffer *buf, *node;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vin->qlock, flags);

	list_क्रम_each_entry_safe(buf, node, &vin->buf_list, list) अणु
		vb2_buffer_करोne(&buf->vb.vb2_buf, state);
		list_del(&buf->list);
	पूर्ण

	spin_unlock_irqrestore(&vin->qlock, flags);
पूर्ण

अटल पूर्णांक rvin_queue_setup(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक *nbuffers,
			    अचिन्हित पूर्णांक *nplanes, अचिन्हित पूर्णांक sizes[],
			    काष्ठा device *alloc_devs[])

अणु
	काष्ठा rvin_dev *vin = vb2_get_drv_priv(vq);

	/* Make sure the image size is large enough. */
	अगर (*nplanes)
		वापस sizes[0] < vin->क्रमmat.sizeimage ? -EINVAL : 0;

	*nplanes = 1;
	sizes[0] = vin->क्रमmat.sizeimage;

	वापस 0;
पूर्ण;

अटल पूर्णांक rvin_buffer_prepare(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा rvin_dev *vin = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ size = vin->क्रमmat.sizeimage;

	अगर (vb2_plane_size(vb, 0) < size) अणु
		vin_err(vin, "buffer too small (%lu < %lu)\n",
			vb2_plane_size(vb, 0), size);
		वापस -EINVAL;
	पूर्ण

	vb2_set_plane_payload(vb, 0, size);

	वापस 0;
पूर्ण

अटल व्योम rvin_buffer_queue(काष्ठा vb2_buffer *vb)
अणु
	काष्ठा vb2_v4l2_buffer *vbuf = to_vb2_v4l2_buffer(vb);
	काष्ठा rvin_dev *vin = vb2_get_drv_priv(vb->vb2_queue);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&vin->qlock, flags);

	list_add_tail(to_buf_list(vbuf), &vin->buf_list);

	spin_unlock_irqrestore(&vin->qlock, flags);
पूर्ण

अटल पूर्णांक rvin_mc_validate_क्रमmat(काष्ठा rvin_dev *vin, काष्ठा v4l2_subdev *sd,
				   काष्ठा media_pad *pad)
अणु
	काष्ठा v4l2_subdev_क्रमmat fmt = अणु
		.which = V4L2_SUBDEV_FORMAT_ACTIVE,
	पूर्ण;

	fmt.pad = pad->index;
	अगर (v4l2_subdev_call(sd, pad, get_fmt, शून्य, &fmt))
		वापस -EPIPE;

	चयन (fmt.क्रमmat.code) अणु
	हाल MEDIA_BUS_FMT_YUYV8_1X16:
	हाल MEDIA_BUS_FMT_UYVY8_1X16:
	हाल MEDIA_BUS_FMT_UYVY8_2X8:
	हाल MEDIA_BUS_FMT_UYVY10_2X10:
	हाल MEDIA_BUS_FMT_RGB888_1X24:
		अवरोध;
	हाल MEDIA_BUS_FMT_SBGGR8_1X8:
		अगर (vin->क्रमmat.pixelक्रमmat != V4L2_PIX_FMT_SBGGR8)
			वापस -EPIPE;
		अवरोध;
	हाल MEDIA_BUS_FMT_SGBRG8_1X8:
		अगर (vin->क्रमmat.pixelक्रमmat != V4L2_PIX_FMT_SGBRG8)
			वापस -EPIPE;
		अवरोध;
	हाल MEDIA_BUS_FMT_SGRBG8_1X8:
		अगर (vin->क्रमmat.pixelक्रमmat != V4L2_PIX_FMT_SGRBG8)
			वापस -EPIPE;
		अवरोध;
	हाल MEDIA_BUS_FMT_SRGGB8_1X8:
		अगर (vin->क्रमmat.pixelक्रमmat != V4L2_PIX_FMT_SRGGB8)
			वापस -EPIPE;
		अवरोध;
	शेष:
		वापस -EPIPE;
	पूर्ण
	vin->mbus_code = fmt.क्रमmat.code;

	चयन (fmt.क्रमmat.field) अणु
	हाल V4L2_FIELD_TOP:
	हाल V4L2_FIELD_BOTTOM:
	हाल V4L2_FIELD_NONE:
	हाल V4L2_FIELD_INTERLACED_TB:
	हाल V4L2_FIELD_INTERLACED_BT:
	हाल V4L2_FIELD_INTERLACED:
	हाल V4L2_FIELD_SEQ_TB:
	हाल V4L2_FIELD_SEQ_BT:
		/* Supported natively */
		अवरोध;
	हाल V4L2_FIELD_ALTERNATE:
		चयन (vin->क्रमmat.field) अणु
		हाल V4L2_FIELD_TOP:
		हाल V4L2_FIELD_BOTTOM:
		हाल V4L2_FIELD_NONE:
		हाल V4L2_FIELD_ALTERNATE:
			अवरोध;
		हाल V4L2_FIELD_INTERLACED_TB:
		हाल V4L2_FIELD_INTERLACED_BT:
		हाल V4L2_FIELD_INTERLACED:
		हाल V4L2_FIELD_SEQ_TB:
		हाल V4L2_FIELD_SEQ_BT:
			/* Use VIN hardware to combine the two fields */
			fmt.क्रमmat.height *= 2;
			अवरोध;
		शेष:
			वापस -EPIPE;
		पूर्ण
		अवरोध;
	शेष:
		वापस -EPIPE;
	पूर्ण

	अगर (fmt.क्रमmat.width != vin->क्रमmat.width ||
	    fmt.क्रमmat.height != vin->क्रमmat.height ||
	    fmt.क्रमmat.code != vin->mbus_code)
		वापस -EPIPE;

	वापस 0;
पूर्ण

अटल पूर्णांक rvin_set_stream(काष्ठा rvin_dev *vin, पूर्णांक on)
अणु
	काष्ठा media_pipeline *pipe;
	काष्ठा media_device *mdev;
	काष्ठा v4l2_subdev *sd;
	काष्ठा media_pad *pad;
	पूर्णांक ret;

	/* No media controller used, simply pass operation to subdevice. */
	अगर (!vin->info->use_mc) अणु
		ret = v4l2_subdev_call(vin->parallel.subdev, video, s_stream,
				       on);

		वापस ret == -ENOIOCTLCMD ? 0 : ret;
	पूर्ण

	pad = media_entity_remote_pad(&vin->pad);
	अगर (!pad)
		वापस -EPIPE;

	sd = media_entity_to_v4l2_subdev(pad->entity);

	अगर (!on) अणु
		media_pipeline_stop(&vin->vdev.entity);
		वापस v4l2_subdev_call(sd, video, s_stream, 0);
	पूर्ण

	ret = rvin_mc_validate_क्रमmat(vin, sd, pad);
	अगर (ret)
		वापस ret;

	/*
	 * The graph lock needs to be taken to protect concurrent
	 * starts of multiple VIN instances as they might share
	 * a common subdevice करोwn the line and then should use
	 * the same pipe.
	 */
	mdev = vin->vdev.entity.graph_obj.mdev;
	mutex_lock(&mdev->graph_mutex);
	pipe = sd->entity.pipe ? sd->entity.pipe : &vin->vdev.pipe;
	ret = __media_pipeline_start(&vin->vdev.entity, pipe);
	mutex_unlock(&mdev->graph_mutex);
	अगर (ret)
		वापस ret;

	ret = v4l2_subdev_call(sd, video, s_stream, 1);
	अगर (ret == -ENOIOCTLCMD)
		ret = 0;
	अगर (ret)
		media_pipeline_stop(&vin->vdev.entity);

	वापस ret;
पूर्ण

पूर्णांक rvin_start_streaming(काष्ठा rvin_dev *vin)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = rvin_set_stream(vin, 1);
	अगर (ret)
		वापस ret;

	spin_lock_irqsave(&vin->qlock, flags);

	vin->sequence = 0;

	ret = rvin_capture_start(vin);
	अगर (ret)
		rvin_set_stream(vin, 0);

	spin_unlock_irqrestore(&vin->qlock, flags);

	वापस ret;
पूर्ण

अटल पूर्णांक rvin_start_streaming_vq(काष्ठा vb2_queue *vq, अचिन्हित पूर्णांक count)
अणु
	काष्ठा rvin_dev *vin = vb2_get_drv_priv(vq);
	पूर्णांक ret = -ENOMEM;

	/* Allocate scratch buffer. */
	vin->scratch = dma_alloc_coherent(vin->dev, vin->क्रमmat.sizeimage,
					  &vin->scratch_phys, GFP_KERNEL);
	अगर (!vin->scratch)
		जाओ err_scratch;

	ret = rvin_start_streaming(vin);
	अगर (ret)
		जाओ err_start;

	वापस 0;
err_start:
	dma_मुक्त_coherent(vin->dev, vin->क्रमmat.sizeimage, vin->scratch,
			  vin->scratch_phys);
err_scratch:
	वापस_unused_buffers(vin, VB2_BUF_STATE_QUEUED);

	वापस ret;
पूर्ण

व्योम rvin_stop_streaming(काष्ठा rvin_dev *vin)
अणु
	अचिन्हित पूर्णांक i, retries;
	अचिन्हित दीर्घ flags;
	bool buffersFreed;

	spin_lock_irqsave(&vin->qlock, flags);

	अगर (vin->state == STOPPED) अणु
		spin_unlock_irqrestore(&vin->qlock, flags);
		वापस;
	पूर्ण

	vin->state = STOPPING;

	/* Wait until only scratch buffer is used, max 3 पूर्णांकerrupts. */
	retries = 0;
	जबतक (retries++ < RVIN_RETRIES) अणु
		buffersFreed = true;
		क्रम (i = 0; i < HW_BUFFER_NUM; i++)
			अगर (vin->buf_hw[i].buffer)
				buffersFreed = false;

		अगर (buffersFreed)
			अवरोध;

		spin_unlock_irqrestore(&vin->qlock, flags);
		msleep(RVIN_TIMEOUT_MS);
		spin_lock_irqsave(&vin->qlock, flags);
	पूर्ण

	/* Wait क्रम streaming to stop */
	retries = 0;
	जबतक (retries++ < RVIN_RETRIES) अणु

		rvin_capture_stop(vin);

		/* Check अगर HW is stopped */
		अगर (!rvin_capture_active(vin)) अणु
			vin->state = STOPPED;
			अवरोध;
		पूर्ण

		spin_unlock_irqrestore(&vin->qlock, flags);
		msleep(RVIN_TIMEOUT_MS);
		spin_lock_irqsave(&vin->qlock, flags);
	पूर्ण

	अगर (!buffersFreed || vin->state != STOPPED) अणु
		/*
		 * If this happens something have gone horribly wrong.
		 * Set state to stopped to prevent the पूर्णांकerrupt handler
		 * to make things worse...
		 */
		vin_err(vin, "Failed stop HW, something is seriously broken\n");
		vin->state = STOPPED;
	पूर्ण

	spin_unlock_irqrestore(&vin->qlock, flags);

	rvin_set_stream(vin, 0);

	/* disable पूर्णांकerrupts */
	rvin_disable_पूर्णांकerrupts(vin);
पूर्ण

अटल व्योम rvin_stop_streaming_vq(काष्ठा vb2_queue *vq)
अणु
	काष्ठा rvin_dev *vin = vb2_get_drv_priv(vq);

	rvin_stop_streaming(vin);

	/* Free scratch buffer. */
	dma_मुक्त_coherent(vin->dev, vin->क्रमmat.sizeimage, vin->scratch,
			  vin->scratch_phys);

	वापस_unused_buffers(vin, VB2_BUF_STATE_ERROR);
पूर्ण

अटल स्थिर काष्ठा vb2_ops rvin_qops = अणु
	.queue_setup		= rvin_queue_setup,
	.buf_prepare		= rvin_buffer_prepare,
	.buf_queue		= rvin_buffer_queue,
	.start_streaming	= rvin_start_streaming_vq,
	.stop_streaming		= rvin_stop_streaming_vq,
	.रुको_prepare		= vb2_ops_रुको_prepare,
	.रुको_finish		= vb2_ops_रुको_finish,
पूर्ण;

व्योम rvin_dma_unरेजिस्टर(काष्ठा rvin_dev *vin)
अणु
	mutex_destroy(&vin->lock);

	v4l2_device_unरेजिस्टर(&vin->v4l2_dev);
पूर्ण

पूर्णांक rvin_dma_रेजिस्टर(काष्ठा rvin_dev *vin, पूर्णांक irq)
अणु
	काष्ठा vb2_queue *q = &vin->queue;
	पूर्णांक i, ret;

	/* Initialize the top-level काष्ठाure */
	ret = v4l2_device_रेजिस्टर(vin->dev, &vin->v4l2_dev);
	अगर (ret)
		वापस ret;

	mutex_init(&vin->lock);
	INIT_LIST_HEAD(&vin->buf_list);

	spin_lock_init(&vin->qlock);

	vin->state = STOPPED;

	क्रम (i = 0; i < HW_BUFFER_NUM; i++)
		vin->buf_hw[i].buffer = शून्य;

	/* buffer queue */
	q->type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	q->io_modes = VB2_MMAP | VB2_READ | VB2_DMABUF;
	q->lock = &vin->lock;
	q->drv_priv = vin;
	q->buf_काष्ठा_size = माप(काष्ठा rvin_buffer);
	q->ops = &rvin_qops;
	q->mem_ops = &vb2_dma_contig_memops;
	q->बारtamp_flags = V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	q->min_buffers_needed = 4;
	q->dev = vin->dev;

	ret = vb2_queue_init(q);
	अगर (ret < 0) अणु
		vin_err(vin, "failed to initialize VB2 queue\n");
		जाओ error;
	पूर्ण

	/* irq */
	ret = devm_request_irq(vin->dev, irq, rvin_irq, IRQF_SHARED,
			       KBUILD_MODNAME, vin);
	अगर (ret) अणु
		vin_err(vin, "failed to request irq\n");
		जाओ error;
	पूर्ण

	वापस 0;
error:
	rvin_dma_unरेजिस्टर(vin);

	वापस ret;
पूर्ण

/* -----------------------------------------------------------------------------
 * Gen3 CHSEL manipulation
 */

/*
 * There is no need to have locking around changing the routing
 * as it's only possible to करो so when no VIN in the group is
 * streaming so nothing can race with the VNMC रेजिस्टर.
 */
पूर्णांक rvin_set_channel_routing(काष्ठा rvin_dev *vin, u8 chsel)
अणु
	स्थिर काष्ठा rvin_group_route *route;
	u32 अगरmd = 0;
	u32 vnmc;
	पूर्णांक ret;

	ret = pm_runसमय_get_sync(vin->dev);
	अगर (ret < 0) अणु
		pm_runसमय_put_noidle(vin->dev);
		वापस ret;
	पूर्ण

	/* Make रेजिस्टर ग_लिखोs take effect immediately. */
	vnmc = rvin_पढ़ो(vin, VNMC_REG);
	rvin_ग_लिखो(vin, vnmc & ~VNMC_VUP, VNMC_REG);

	/*
	 * Set data expansion mode to "pad with 0s" by inspecting the routes
	 * table to find out which bit fields are available in the IFMD
	 * रेजिस्टर. IFMD_DES1 controls data expansion mode क्रम CSI20/21,
	 * IFMD_DES0 controls data expansion mode क्रम CSI40/41.
	 */
	क्रम (route = vin->info->routes; route->mask; route++) अणु
		अगर (route->csi == RVIN_CSI20 || route->csi == RVIN_CSI21)
			अगरmd |= VNCSI_IFMD_DES1;
		अन्यथा
			अगरmd |= VNCSI_IFMD_DES0;

		अगर (अगरmd == (VNCSI_IFMD_DES0 | VNCSI_IFMD_DES1))
			अवरोध;
	पूर्ण

	अगर (अगरmd) अणु
		अगरmd |= VNCSI_IFMD_CSI_CHSEL(chsel);
		rvin_ग_लिखो(vin, अगरmd, VNCSI_IFMD_REG);
	पूर्ण

	vin_dbg(vin, "Set IFMD 0x%x\n", अगरmd);

	vin->chsel = chsel;

	/* Restore VNMC. */
	rvin_ग_लिखो(vin, vnmc, VNMC_REG);

	pm_runसमय_put(vin->dev);

	वापस 0;
पूर्ण

व्योम rvin_set_alpha(काष्ठा rvin_dev *vin, अचिन्हित पूर्णांक alpha)
अणु
	अचिन्हित दीर्घ flags;
	u32 dmr;

	spin_lock_irqsave(&vin->qlock, flags);

	vin->alpha = alpha;

	अगर (vin->state == STOPPED)
		जाओ out;

	चयन (vin->क्रमmat.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_ARGB555:
		dmr = rvin_पढ़ो(vin, VNDMR_REG) & ~VNDMR_ABIT;
		अगर (vin->alpha)
			dmr |= VNDMR_ABIT;
		अवरोध;
	हाल V4L2_PIX_FMT_ABGR32:
		dmr = rvin_पढ़ो(vin, VNDMR_REG) & ~VNDMR_A8BIT_MASK;
		dmr |= VNDMR_A8BIT(vin->alpha);
		अवरोध;
	शेष:
		जाओ out;
	पूर्ण

	rvin_ग_लिखो(vin, dmr,  VNDMR_REG);
out:
	spin_unlock_irqrestore(&vin->qlock, flags);
पूर्ण
