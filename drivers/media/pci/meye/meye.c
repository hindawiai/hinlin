<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Motion Eye video4linux driver क्रम Sony Vaio PictureBook
 *
 * Copyright (C) 2001-2004 Stelian Pop <stelian@popies.net>
 *
 * Copyright (C) 2001-2002 Alcथखve <www.alcove.com>
 *
 * Copyright (C) 2000 Andrew Tridgell <tridge@valinux.com>
 *
 * Earlier work by Werner Almesberger, Paul `Rusty' Russell and Paul Mackerras.
 *
 * Some parts borrowed from various video4linux drivers, especially
 * bttv-driver.c and zoran.c, see original files क्रम credits.
 */
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/sched.h>
#समावेश <linux/init.h>
#समावेश <linux/gfp.h>
#समावेश <linux/videodev2.h>
#समावेश <media/v4l2-common.h>
#समावेश <media/v4l2-device.h>
#समावेश <media/v4l2-ioctl.h>
#समावेश <media/v4l2-fh.h>
#समावेश <media/v4l2-event.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/dma-mapping.h>

#समावेश "meye.h"
#समावेश <linux/meye.h>

MODULE_AUTHOR("Stelian Pop <stelian@popies.net>");
MODULE_DESCRIPTION("v4l2 driver for the MotionEye camera");
MODULE_LICENSE("GPL");
MODULE_VERSION(MEYE_DRIVER_VERSION);

/* number of grab buffers */
अटल अचिन्हित पूर्णांक gbuffers = 2;
module_param(gbuffers, पूर्णांक, 0444);
MODULE_PARM_DESC(gbuffers, "number of capture buffers, default is 2 (32 max)");

/* size of a grab buffer */
अटल अचिन्हित पूर्णांक gbufsize = MEYE_MAX_बफ_मानE;
module_param(gbufsize, पूर्णांक, 0444);
MODULE_PARM_DESC(gbufsize, "size of the capture buffers, default is 614400 (will be rounded up to a page multiple)");

/* /dev/videoX registration number */
अटल पूर्णांक video_nr = -1;
module_param(video_nr, पूर्णांक, 0444);
MODULE_PARM_DESC(video_nr, "video device to register (0=/dev/video0, etc)");

/* driver काष्ठाure - only one possible */
अटल काष्ठा meye meye;

/****************************************************************************/
/* Memory allocation routines (stolen from bttv-driver.c)                   */
/****************************************************************************/
अटल व्योम *rvदो_स्मृति(अचिन्हित दीर्घ size)
अणु
	व्योम *mem;
	अचिन्हित दीर्घ adr;

	size = PAGE_ALIGN(size);
	mem = vदो_स्मृति_32(size);
	अगर (mem) अणु
		स_रखो(mem, 0, size);
		adr = (अचिन्हित दीर्घ) mem;
		जबतक (size > 0) अणु
			SetPageReserved(vदो_स्मृति_to_page((व्योम *)adr));
			adr += PAGE_SIZE;
			size -= PAGE_SIZE;
		पूर्ण
	पूर्ण
	वापस mem;
पूर्ण

अटल व्योम rvमुक्त(व्योम * mem, अचिन्हित दीर्घ size)
अणु
	अचिन्हित दीर्घ adr;

	अगर (mem) अणु
		adr = (अचिन्हित दीर्घ) mem;
		जबतक ((दीर्घ) size > 0) अणु
			ClearPageReserved(vदो_स्मृति_to_page((व्योम *)adr));
			adr += PAGE_SIZE;
			size -= PAGE_SIZE;
		पूर्ण
		vमुक्त(mem);
	पूर्ण
पूर्ण

/*
 * वापस a page table poपूर्णांकing to N pages of locked memory
 *
 * NOTE: The meye device expects DMA addresses on 32 bits, we build
 * a table of 1024 entries = 4 bytes * 1024 = 4096 bytes.
 */
अटल पूर्णांक ptable_alloc(व्योम)
अणु
	u32 *pt;
	पूर्णांक i;

	स_रखो(meye.mchip_ptable, 0, माप(meye.mchip_ptable));

	/* give only 32 bit DMA addresses */
	अगर (dma_set_mask(&meye.mchip_dev->dev, DMA_BIT_MASK(32)))
		वापस -1;

	meye.mchip_ptable_toc = dma_alloc_coherent(&meye.mchip_dev->dev,
						   PAGE_SIZE,
						   &meye.mchip_dmahandle,
						   GFP_KERNEL);
	अगर (!meye.mchip_ptable_toc) अणु
		meye.mchip_dmahandle = 0;
		वापस -1;
	पूर्ण

	pt = meye.mchip_ptable_toc;
	क्रम (i = 0; i < MCHIP_NB_PAGES; i++) अणु
		dma_addr_t dma;
		meye.mchip_ptable[i] = dma_alloc_coherent(&meye.mchip_dev->dev,
							  PAGE_SIZE,
							  &dma,
							  GFP_KERNEL);
		अगर (!meye.mchip_ptable[i]) अणु
			पूर्णांक j;
			pt = meye.mchip_ptable_toc;
			क्रम (j = 0; j < i; ++j) अणु
				dma = (dma_addr_t) *pt;
				dma_मुक्त_coherent(&meye.mchip_dev->dev,
						  PAGE_SIZE,
						  meye.mchip_ptable[j], dma);
				pt++;
			पूर्ण
			dma_मुक्त_coherent(&meye.mchip_dev->dev,
					  PAGE_SIZE,
					  meye.mchip_ptable_toc,
					  meye.mchip_dmahandle);
			meye.mchip_ptable_toc = शून्य;
			meye.mchip_dmahandle = 0;
			वापस -1;
		पूर्ण
		*pt = (u32) dma;
		pt++;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ptable_मुक्त(व्योम)
अणु
	u32 *pt;
	पूर्णांक i;

	pt = meye.mchip_ptable_toc;
	क्रम (i = 0; i < MCHIP_NB_PAGES; i++) अणु
		dma_addr_t dma = (dma_addr_t) *pt;
		अगर (meye.mchip_ptable[i])
			dma_मुक्त_coherent(&meye.mchip_dev->dev,
					  PAGE_SIZE,
					  meye.mchip_ptable[i], dma);
		pt++;
	पूर्ण

	अगर (meye.mchip_ptable_toc)
		dma_मुक्त_coherent(&meye.mchip_dev->dev,
				  PAGE_SIZE,
				  meye.mchip_ptable_toc,
				  meye.mchip_dmahandle);

	स_रखो(meye.mchip_ptable, 0, माप(meye.mchip_ptable));
	meye.mchip_ptable_toc = शून्य;
	meye.mchip_dmahandle = 0;
पूर्ण

/* copy data from ptable पूर्णांकo buf */
अटल व्योम ptable_copy(u8 *buf, पूर्णांक start, पूर्णांक size, पूर्णांक pt_pages)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < (size / PAGE_SIZE) * PAGE_SIZE; i += PAGE_SIZE) अणु
		स_नकल(buf + i, meye.mchip_ptable[start++], PAGE_SIZE);
		अगर (start >= pt_pages)
			start = 0;
	पूर्ण
	स_नकल(buf + i, meye.mchip_ptable[start], size % PAGE_SIZE);
पूर्ण

/****************************************************************************/
/* JPEG tables at dअगरferent qualities to load पूर्णांकo the VRJ chip             */
/****************************************************************************/

/* वापस a set of quantisation tables based on a quality from 1 to 10 */
अटल u16 *jpeg_quantisation_tables(पूर्णांक *length, पूर्णांक quality)
अणु
	अटल u16 jpeg_tables[][70] = अणु अणु
		0xdbff, 0x4300, 0xff00, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
		0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
		0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
		0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
		0xffff, 0xffff, 0xffff,
		0xdbff, 0x4300, 0xff01, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
		0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
		0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
		0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
		0xffff, 0xffff, 0xffff,
	पूर्ण,
	अणु
		0xdbff, 0x4300, 0x5000, 0x3c37, 0x3c46, 0x5032, 0x4146, 0x5a46,
		0x5055, 0x785f, 0x82c8, 0x6e78, 0x786e, 0xaff5, 0x91b9, 0xffc8,
		0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
		0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
		0xffff, 0xffff, 0xffff,
		0xdbff, 0x4300, 0x5501, 0x5a5a, 0x6978, 0xeb78, 0x8282, 0xffeb,
		0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
		0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
		0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff,
		0xffff, 0xffff, 0xffff,
	पूर्ण,
	अणु
		0xdbff, 0x4300, 0x2800, 0x1e1c, 0x1e23, 0x2819, 0x2123, 0x2d23,
		0x282b, 0x3c30, 0x4164, 0x373c, 0x3c37, 0x587b, 0x495d, 0x9164,
		0x9980, 0x8f96, 0x8c80, 0xa08a, 0xe6b4, 0xa0c3, 0xdaaa, 0x8aad,
		0xc88c, 0xcbff, 0xeeda, 0xfff5, 0xffff, 0xc19b, 0xffff, 0xfaff,
		0xe6ff, 0xfffd, 0xfff8,
		0xdbff, 0x4300, 0x2b01, 0x2d2d, 0x353c, 0x763c, 0x4141, 0xf876,
		0x8ca5, 0xf8a5, 0xf8f8, 0xf8f8, 0xf8f8, 0xf8f8, 0xf8f8, 0xf8f8,
		0xf8f8, 0xf8f8, 0xf8f8, 0xf8f8, 0xf8f8, 0xf8f8, 0xf8f8, 0xf8f8,
		0xf8f8, 0xf8f8, 0xf8f8, 0xf8f8, 0xf8f8, 0xf8f8, 0xf8f8, 0xf8f8,
		0xf8f8, 0xf8f8, 0xfff8,
	पूर्ण,
	अणु
		0xdbff, 0x4300, 0x1b00, 0x1412, 0x1417, 0x1b11, 0x1617, 0x1e17,
		0x1b1c, 0x2820, 0x2b42, 0x2528, 0x2825, 0x3a51, 0x303d, 0x6042,
		0x6555, 0x5f64, 0x5d55, 0x6a5b, 0x9978, 0x6a81, 0x9071, 0x5b73,
		0x855d, 0x86b5, 0x9e90, 0xaba3, 0xabad, 0x8067, 0xc9bc, 0xa6ba,
		0x99c7, 0xaba8, 0xffa4,
		0xdbff, 0x4300, 0x1c01, 0x1e1e, 0x2328, 0x4e28, 0x2b2b, 0xa44e,
		0x5d6e, 0xa46e, 0xa4a4, 0xa4a4, 0xa4a4, 0xa4a4, 0xa4a4, 0xa4a4,
		0xa4a4, 0xa4a4, 0xa4a4, 0xa4a4, 0xa4a4, 0xa4a4, 0xa4a4, 0xa4a4,
		0xa4a4, 0xa4a4, 0xa4a4, 0xa4a4, 0xa4a4, 0xa4a4, 0xa4a4, 0xa4a4,
		0xa4a4, 0xa4a4, 0xffa4,
	पूर्ण,
	अणु
		0xdbff, 0x4300, 0x1400, 0x0f0e, 0x0f12, 0x140d, 0x1012, 0x1712,
		0x1415, 0x1e18, 0x2132, 0x1c1e, 0x1e1c, 0x2c3d, 0x242e, 0x4932,
		0x4c40, 0x474b, 0x4640, 0x5045, 0x735a, 0x5062, 0x6d55, 0x4556,
		0x6446, 0x6588, 0x776d, 0x817b, 0x8182, 0x604e, 0x978d, 0x7d8c,
		0x7396, 0x817e, 0xff7c,
		0xdbff, 0x4300, 0x1501, 0x1717, 0x1a1e, 0x3b1e, 0x2121, 0x7c3b,
		0x4653, 0x7c53, 0x7c7c, 0x7c7c, 0x7c7c, 0x7c7c, 0x7c7c, 0x7c7c,
		0x7c7c, 0x7c7c, 0x7c7c, 0x7c7c, 0x7c7c, 0x7c7c, 0x7c7c, 0x7c7c,
		0x7c7c, 0x7c7c, 0x7c7c, 0x7c7c, 0x7c7c, 0x7c7c, 0x7c7c, 0x7c7c,
		0x7c7c, 0x7c7c, 0xff7c,
	पूर्ण,
	अणु
		0xdbff, 0x4300, 0x1000, 0x0c0b, 0x0c0e, 0x100a, 0x0d0e, 0x120e,
		0x1011, 0x1813, 0x1a28, 0x1618, 0x1816, 0x2331, 0x1d25, 0x3a28,
		0x3d33, 0x393c, 0x3833, 0x4037, 0x5c48, 0x404e, 0x5744, 0x3745,
		0x5038, 0x516d, 0x5f57, 0x6762, 0x6768, 0x4d3e, 0x7971, 0x6470,
		0x5c78, 0x6765, 0xff63,
		0xdbff, 0x4300, 0x1101, 0x1212, 0x1518, 0x2f18, 0x1a1a, 0x632f,
		0x3842, 0x6342, 0x6363, 0x6363, 0x6363, 0x6363, 0x6363, 0x6363,
		0x6363, 0x6363, 0x6363, 0x6363, 0x6363, 0x6363, 0x6363, 0x6363,
		0x6363, 0x6363, 0x6363, 0x6363, 0x6363, 0x6363, 0x6363, 0x6363,
		0x6363, 0x6363, 0xff63,
	पूर्ण,
	अणु
		0xdbff, 0x4300, 0x0d00, 0x0a09, 0x0a0b, 0x0d08, 0x0a0b, 0x0e0b,
		0x0d0e, 0x130f, 0x1520, 0x1213, 0x1312, 0x1c27, 0x171e, 0x2e20,
		0x3129, 0x2e30, 0x2d29, 0x332c, 0x4a3a, 0x333e, 0x4636, 0x2c37,
		0x402d, 0x4157, 0x4c46, 0x524e, 0x5253, 0x3e32, 0x615a, 0x505a,
		0x4a60, 0x5251, 0xff4f,
		0xdbff, 0x4300, 0x0e01, 0x0e0e, 0x1113, 0x2613, 0x1515, 0x4f26,
		0x2d35, 0x4f35, 0x4f4f, 0x4f4f, 0x4f4f, 0x4f4f, 0x4f4f, 0x4f4f,
		0x4f4f, 0x4f4f, 0x4f4f, 0x4f4f, 0x4f4f, 0x4f4f, 0x4f4f, 0x4f4f,
		0x4f4f, 0x4f4f, 0x4f4f, 0x4f4f, 0x4f4f, 0x4f4f, 0x4f4f, 0x4f4f,
		0x4f4f, 0x4f4f, 0xff4f,
	पूर्ण,
	अणु
		0xdbff, 0x4300, 0x0a00, 0x0707, 0x0708, 0x0a06, 0x0808, 0x0b08,
		0x0a0a, 0x0e0b, 0x1018, 0x0d0e, 0x0e0d, 0x151d, 0x1116, 0x2318,
		0x251f, 0x2224, 0x221f, 0x2621, 0x372b, 0x262f, 0x3429, 0x2129,
		0x3022, 0x3141, 0x3934, 0x3e3b, 0x3e3e, 0x2e25, 0x4944, 0x3c43,
		0x3748, 0x3e3d, 0xff3b,
		0xdbff, 0x4300, 0x0a01, 0x0b0b, 0x0d0e, 0x1c0e, 0x1010, 0x3b1c,
		0x2228, 0x3b28, 0x3b3b, 0x3b3b, 0x3b3b, 0x3b3b, 0x3b3b, 0x3b3b,
		0x3b3b, 0x3b3b, 0x3b3b, 0x3b3b, 0x3b3b, 0x3b3b, 0x3b3b, 0x3b3b,
		0x3b3b, 0x3b3b, 0x3b3b, 0x3b3b, 0x3b3b, 0x3b3b, 0x3b3b, 0x3b3b,
		0x3b3b, 0x3b3b, 0xff3b,
	पूर्ण,
	अणु
		0xdbff, 0x4300, 0x0600, 0x0504, 0x0506, 0x0604, 0x0506, 0x0706,
		0x0607, 0x0a08, 0x0a10, 0x090a, 0x0a09, 0x0e14, 0x0c0f, 0x1710,
		0x1814, 0x1718, 0x1614, 0x1a16, 0x251d, 0x1a1f, 0x231b, 0x161c,
		0x2016, 0x202c, 0x2623, 0x2927, 0x292a, 0x1f19, 0x302d, 0x282d,
		0x2530, 0x2928, 0xff28,
		0xdbff, 0x4300, 0x0701, 0x0707, 0x080a, 0x130a, 0x0a0a, 0x2813,
		0x161a, 0x281a, 0x2828, 0x2828, 0x2828, 0x2828, 0x2828, 0x2828,
		0x2828, 0x2828, 0x2828, 0x2828, 0x2828, 0x2828, 0x2828, 0x2828,
		0x2828, 0x2828, 0x2828, 0x2828, 0x2828, 0x2828, 0x2828, 0x2828,
		0x2828, 0x2828, 0xff28,
	पूर्ण,
	अणु
		0xdbff, 0x4300, 0x0300, 0x0202, 0x0203, 0x0302, 0x0303, 0x0403,
		0x0303, 0x0504, 0x0508, 0x0405, 0x0504, 0x070a, 0x0607, 0x0c08,
		0x0c0a, 0x0b0c, 0x0b0a, 0x0d0b, 0x120e, 0x0d10, 0x110e, 0x0b0e,
		0x100b, 0x1016, 0x1311, 0x1514, 0x1515, 0x0f0c, 0x1817, 0x1416,
		0x1218, 0x1514, 0xff14,
		0xdbff, 0x4300, 0x0301, 0x0404, 0x0405, 0x0905, 0x0505, 0x1409,
		0x0b0d, 0x140d, 0x1414, 0x1414, 0x1414, 0x1414, 0x1414, 0x1414,
		0x1414, 0x1414, 0x1414, 0x1414, 0x1414, 0x1414, 0x1414, 0x1414,
		0x1414, 0x1414, 0x1414, 0x1414, 0x1414, 0x1414, 0x1414, 0x1414,
		0x1414, 0x1414, 0xff14,
	पूर्ण,
	अणु
		0xdbff, 0x4300, 0x0100, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
		0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
		0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
		0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
		0x0101, 0x0101, 0xff01,
		0xdbff, 0x4300, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
		0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
		0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
		0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101, 0x0101,
		0x0101, 0x0101, 0xff01,
	पूर्ण पूर्ण;

	अगर (quality < 0 || quality > 10) अणु
		prपूर्णांकk(KERN_WARNING
		       "meye: invalid quality level %d - using 8\n", quality);
		quality = 8;
	पूर्ण

	*length = ARRAY_SIZE(jpeg_tables[quality]);
	वापस jpeg_tables[quality];
पूर्ण

/* वापस a generic set of huffman tables */
अटल u16 *jpeg_huffman_tables(पूर्णांक *length)
अणु
	अटल u16 tables[] = अणु
		0xC4FF, 0xB500, 0x0010, 0x0102, 0x0303, 0x0402, 0x0503, 0x0405,
		0x0004, 0x0100, 0x017D, 0x0302, 0x0400, 0x0511, 0x2112, 0x4131,
		0x1306, 0x6151, 0x2207, 0x1471, 0x8132, 0xA191, 0x2308, 0xB142,
		0x15C1, 0xD152, 0x24F0, 0x6233, 0x8272, 0x0A09, 0x1716, 0x1918,
		0x251A, 0x2726, 0x2928, 0x342A, 0x3635, 0x3837, 0x3A39, 0x4443,
		0x4645, 0x4847, 0x4A49, 0x5453, 0x5655, 0x5857, 0x5A59, 0x6463,
		0x6665, 0x6867, 0x6A69, 0x7473, 0x7675, 0x7877, 0x7A79, 0x8483,
		0x8685, 0x8887, 0x8A89, 0x9392, 0x9594, 0x9796, 0x9998, 0xA29A,
		0xA4A3, 0xA6A5, 0xA8A7, 0xAAA9, 0xB3B2, 0xB5B4, 0xB7B6, 0xB9B8,
		0xC2BA, 0xC4C3, 0xC6C5, 0xC8C7, 0xCAC9, 0xD3D2, 0xD5D4, 0xD7D6,
		0xD9D8, 0xE1DA, 0xE3E2, 0xE5E4, 0xE7E6, 0xE9E8, 0xF1EA, 0xF3F2,
		0xF5F4, 0xF7F6, 0xF9F8, 0xFFFA,
		0xC4FF, 0xB500, 0x0011, 0x0102, 0x0402, 0x0304, 0x0704, 0x0405,
		0x0004, 0x0201, 0x0077, 0x0201, 0x1103, 0x0504, 0x3121, 0x1206,
		0x5141, 0x6107, 0x1371, 0x3222, 0x0881, 0x4214, 0xA191, 0xC1B1,
		0x2309, 0x5233, 0x15F0, 0x7262, 0x0AD1, 0x2416, 0xE134, 0xF125,
		0x1817, 0x1A19, 0x2726, 0x2928, 0x352A, 0x3736, 0x3938, 0x433A,
		0x4544, 0x4746, 0x4948, 0x534A, 0x5554, 0x5756, 0x5958, 0x635A,
		0x6564, 0x6766, 0x6968, 0x736A, 0x7574, 0x7776, 0x7978, 0x827A,
		0x8483, 0x8685, 0x8887, 0x8A89, 0x9392, 0x9594, 0x9796, 0x9998,
		0xA29A, 0xA4A3, 0xA6A5, 0xA8A7, 0xAAA9, 0xB3B2, 0xB5B4, 0xB7B6,
		0xB9B8, 0xC2BA, 0xC4C3, 0xC6C5, 0xC8C7, 0xCAC9, 0xD3D2, 0xD5D4,
		0xD7D6, 0xD9D8, 0xE2DA, 0xE4E3, 0xE6E5, 0xE8E7, 0xEAE9, 0xF3F2,
		0xF5F4, 0xF7F6, 0xF9F8, 0xFFFA,
		0xC4FF, 0x1F00, 0x0000, 0x0501, 0x0101, 0x0101, 0x0101, 0x0000,
		0x0000, 0x0000, 0x0000, 0x0201, 0x0403, 0x0605, 0x0807, 0x0A09,
		0xFF0B,
		0xC4FF, 0x1F00, 0x0001, 0x0103, 0x0101, 0x0101, 0x0101, 0x0101,
		0x0000, 0x0000, 0x0000, 0x0201, 0x0403, 0x0605, 0x0807, 0x0A09,
		0xFF0B
	पूर्ण;

	*length = ARRAY_SIZE(tables);
	वापस tables;
पूर्ण

/****************************************************************************/
/* MCHIP low-level functions                                                */
/****************************************************************************/

/* वापसs the horizontal capture size */
अटल अंतरभूत पूर्णांक mchip_hsize(व्योम)
अणु
	वापस meye.params.subsample ? 320 : 640;
पूर्ण

/* वापसs the vertical capture size */
अटल अंतरभूत पूर्णांक mchip_vsize(व्योम)
अणु
	वापस meye.params.subsample ? 240 : 480;
पूर्ण

/* रुकोs क्रम a रेजिस्टर to be available */
अटल व्योम mchip_sync(पूर्णांक reg)
अणु
	u32 status;
	पूर्णांक i;

	अगर (reg == MCHIP_MM_FIFO_DATA) अणु
		क्रम (i = 0; i < MCHIP_REG_TIMEOUT; i++) अणु
			status = पढ़ोl(meye.mchip_mmregs +
				       MCHIP_MM_FIFO_STATUS);
			अगर (!(status & MCHIP_MM_FIFO_WAIT)) अणु
				prपूर्णांकk(KERN_WARNING "meye: fifo not ready\n");
				वापस;
			पूर्ण
			अगर (status & MCHIP_MM_FIFO_READY)
				वापस;
			udelay(1);
		पूर्ण
	पूर्ण अन्यथा अगर (reg > 0x80) अणु
		u32 mask = (reg < 0x100) ? MCHIP_HIC_STATUS_MCC_RDY
					 : MCHIP_HIC_STATUS_VRJ_RDY;
		क्रम (i = 0; i < MCHIP_REG_TIMEOUT; i++) अणु
			status = पढ़ोl(meye.mchip_mmregs + MCHIP_HIC_STATUS);
			अगर (status & mask)
				वापस;
			udelay(1);
		पूर्ण
	पूर्ण अन्यथा
		वापस;
	prपूर्णांकk(KERN_WARNING
	       "meye: mchip_sync() timeout on reg 0x%x status=0x%x\n",
	       reg, status);
पूर्ण

/* sets a value पूर्णांकo the रेजिस्टर */
अटल अंतरभूत व्योम mchip_set(पूर्णांक reg, u32 v)
अणु
	mchip_sync(reg);
	ग_लिखोl(v, meye.mchip_mmregs + reg);
पूर्ण

/* get the रेजिस्टर value */
अटल अंतरभूत u32 mchip_पढ़ो(पूर्णांक reg)
अणु
	mchip_sync(reg);
	वापस पढ़ोl(meye.mchip_mmregs + reg);
पूर्ण

/* रुको क्रम a रेजिस्टर to become a particular value */
अटल अंतरभूत पूर्णांक mchip_delay(u32 reg, u32 v)
अणु
	पूर्णांक n = 10;
	जबतक (--n && mchip_पढ़ो(reg) != v)
		udelay(1);
	वापस n;
पूर्ण

/* setup subsampling */
अटल व्योम mchip_subsample(व्योम)
अणु
	mchip_set(MCHIP_MCC_R_SAMPLING, meye.params.subsample);
	mchip_set(MCHIP_MCC_R_XRANGE, mchip_hsize());
	mchip_set(MCHIP_MCC_R_YRANGE, mchip_vsize());
	mchip_set(MCHIP_MCC_B_XRANGE, mchip_hsize());
	mchip_set(MCHIP_MCC_B_YRANGE, mchip_vsize());
	mchip_delay(MCHIP_HIC_STATUS, MCHIP_HIC_STATUS_IDLE);
पूर्ण

/* set the framerate पूर्णांकo the mchip */
अटल व्योम mchip_set_framerate(व्योम)
अणु
	mchip_set(MCHIP_HIC_S_RATE, meye.params.framerate);
पूर्ण

/* load some huffman and quantisation tables पूर्णांकo the VRJ chip पढ़ोy
   क्रम JPEG compression */
अटल व्योम mchip_load_tables(व्योम)
अणु
	पूर्णांक i;
	पूर्णांक length;
	u16 *tables;

	tables = jpeg_huffman_tables(&length);
	क्रम (i = 0; i < length; i++)
		ग_लिखोl(tables[i], meye.mchip_mmregs + MCHIP_VRJ_TABLE_DATA);

	tables = jpeg_quantisation_tables(&length, meye.params.quality);
	क्रम (i = 0; i < length; i++)
		ग_लिखोl(tables[i], meye.mchip_mmregs + MCHIP_VRJ_TABLE_DATA);
पूर्ण

/* setup the VRJ parameters in the chip */
अटल व्योम mchip_vrj_setup(u8 mode)
अणु
	mchip_set(MCHIP_VRJ_BUS_MODE, 5);
	mchip_set(MCHIP_VRJ_SIGNAL_ACTIVE_LEVEL, 0x1f);
	mchip_set(MCHIP_VRJ_PDAT_USE, 1);
	mchip_set(MCHIP_VRJ_IRQ_FLAG, 0xa0);
	mchip_set(MCHIP_VRJ_MODE_SPECIFY, mode);
	mchip_set(MCHIP_VRJ_NUM_LINES, mchip_vsize());
	mchip_set(MCHIP_VRJ_NUM_PIXELS, mchip_hsize());
	mchip_set(MCHIP_VRJ_NUM_COMPONENTS, 0x1b);
	mchip_set(MCHIP_VRJ_LIMIT_COMPRESSED_LO, 0xFFFF);
	mchip_set(MCHIP_VRJ_LIMIT_COMPRESSED_HI, 0xFFFF);
	mchip_set(MCHIP_VRJ_COMP_DATA_FORMAT, 0xC);
	mchip_set(MCHIP_VRJ_RESTART_INTERVAL, 0);
	mchip_set(MCHIP_VRJ_SOF1, 0x601);
	mchip_set(MCHIP_VRJ_SOF2, 0x1502);
	mchip_set(MCHIP_VRJ_SOF3, 0x1503);
	mchip_set(MCHIP_VRJ_SOF4, 0x1596);
	mchip_set(MCHIP_VRJ_SOS, 0x0ed0);

	mchip_load_tables();
पूर्ण

/* sets the DMA parameters पूर्णांकo the chip */
अटल व्योम mchip_dma_setup(dma_addr_t dma_addr)
अणु
	पूर्णांक i;

	mchip_set(MCHIP_MM_PT_ADDR, (u32)dma_addr);
	क्रम (i = 0; i < 4; i++)
		mchip_set(MCHIP_MM_FIR(i), 0);
	meye.mchip_fnum = 0;
पूर्ण

/* setup क्रम DMA transfers - also zeros the framebuffer */
अटल पूर्णांक mchip_dma_alloc(व्योम)
अणु
	अगर (!meye.mchip_dmahandle)
		अगर (ptable_alloc())
			वापस -1;
	वापस 0;
पूर्ण

/* मुक्तs the DMA buffer */
अटल व्योम mchip_dma_मुक्त(व्योम)
अणु
	अगर (meye.mchip_dmahandle) अणु
		mchip_dma_setup(0);
		ptable_मुक्त();
	पूर्ण
पूर्ण

/* stop any existing HIC action and रुको क्रम any dma to complete then
   reset the dma engine */
अटल व्योम mchip_hic_stop(व्योम)
अणु
	पूर्णांक i, j;

	meye.mchip_mode = MCHIP_HIC_MODE_NOOP;
	अगर (!(mchip_पढ़ो(MCHIP_HIC_STATUS) & MCHIP_HIC_STATUS_BUSY))
		वापस;
	क्रम (i = 0; i < 20; ++i) अणु
		mchip_set(MCHIP_HIC_CMD, MCHIP_HIC_CMD_STOP);
		mchip_delay(MCHIP_HIC_CMD, 0);
		क्रम (j = 0; j < 100; ++j) अणु
			अगर (mchip_delay(MCHIP_HIC_STATUS,
					MCHIP_HIC_STATUS_IDLE))
				वापस;
			msleep(1);
		पूर्ण
		prपूर्णांकk(KERN_ERR "meye: need to reset HIC!\n");

		mchip_set(MCHIP_HIC_CTL, MCHIP_HIC_CTL_SOFT_RESET);
		msleep(250);
	पूर्ण
	prपूर्णांकk(KERN_ERR "meye: resetting HIC hanged!\n");
पूर्ण

/****************************************************************************/
/* MCHIP frame processing functions                                         */
/****************************************************************************/

/* get the next पढ़ोy frame from the dma engine */
अटल u32 mchip_get_frame(व्योम)
अणु
	वापस mchip_पढ़ो(MCHIP_MM_FIR(meye.mchip_fnum));
पूर्ण

/* मुक्तs the current frame from the dma engine */
अटल व्योम mchip_मुक्त_frame(व्योम)
अणु
	mchip_set(MCHIP_MM_FIR(meye.mchip_fnum), 0);
	meye.mchip_fnum++;
	meye.mchip_fnum %= 4;
पूर्ण

/* पढ़ो one frame from the framebuffer assuming it was captured using
   a uncompressed transfer */
अटल व्योम mchip_cont_पढ़ो_frame(u32 v, u8 *buf, पूर्णांक size)
अणु
	पूर्णांक pt_id;

	pt_id = (v >> 17) & 0x3FF;

	ptable_copy(buf, pt_id, size, MCHIP_NB_PAGES);
पूर्ण

/* पढ़ो a compressed frame from the framebuffer */
अटल पूर्णांक mchip_comp_पढ़ो_frame(u32 v, u8 *buf, पूर्णांक size)
अणु
	पूर्णांक pt_start, pt_end, trailer;
	पूर्णांक fsize;
	पूर्णांक i;

	pt_start = (v >> 19) & 0xFF;
	pt_end = (v >> 11) & 0xFF;
	trailer = (v >> 1) & 0x3FF;

	अगर (pt_end < pt_start)
		fsize = (MCHIP_NB_PAGES_MJPEG - pt_start) * PAGE_SIZE +
			pt_end * PAGE_SIZE + trailer * 4;
	अन्यथा
		fsize = (pt_end - pt_start) * PAGE_SIZE + trailer * 4;

	अगर (fsize > size) अणु
		prपूर्णांकk(KERN_WARNING "meye: oversized compressed frame %d\n",
		       fsize);
		वापस -1;
	पूर्ण

	ptable_copy(buf, pt_start, fsize, MCHIP_NB_PAGES_MJPEG);

#अगर_घोषित MEYE_JPEG_CORRECTION

	/* Some mchip generated jpeg frames are incorrect. In most
	 * (all ?) of those हालs, the final EOI (0xff 0xd9) marker
	 * is not present at the end of the frame.
	 *
	 * Since adding the final marker is not enough to restore
	 * the jpeg पूर्णांकegrity, we drop the frame.
	 */

	क्रम (i = fsize - 1; i > 0 && buf[i] == 0xff; i--) ;

	अगर (i < 2 || buf[i - 1] != 0xff || buf[i] != 0xd9)
		वापस -1;

#पूर्ण_अगर

	वापस fsize;
पूर्ण

/* take a picture पूर्णांकo SDRAM */
अटल व्योम mchip_take_picture(व्योम)
अणु
	पूर्णांक i;

	mchip_hic_stop();
	mchip_subsample();
	mchip_dma_setup(meye.mchip_dmahandle);

	mchip_set(MCHIP_HIC_MODE, MCHIP_HIC_MODE_STILL_CAP);
	mchip_set(MCHIP_HIC_CMD, MCHIP_HIC_CMD_START);

	mchip_delay(MCHIP_HIC_CMD, 0);

	क्रम (i = 0; i < 100; ++i) अणु
		अगर (mchip_delay(MCHIP_HIC_STATUS, MCHIP_HIC_STATUS_IDLE))
			अवरोध;
		msleep(1);
	पूर्ण
पूर्ण

/* dma a previously taken picture पूर्णांकo a buffer */
अटल व्योम mchip_get_picture(u8 *buf, पूर्णांक bufsize)
अणु
	u32 v;
	पूर्णांक i;

	mchip_set(MCHIP_HIC_MODE, MCHIP_HIC_MODE_STILL_OUT);
	mchip_set(MCHIP_HIC_CMD, MCHIP_HIC_CMD_START);

	mchip_delay(MCHIP_HIC_CMD, 0);
	क्रम (i = 0; i < 100; ++i) अणु
		अगर (mchip_delay(MCHIP_HIC_STATUS, MCHIP_HIC_STATUS_IDLE))
			अवरोध;
		msleep(1);
	पूर्ण
	क्रम (i = 0; i < 4; ++i) अणु
		v = mchip_get_frame();
		अगर (v & MCHIP_MM_FIR_RDY) अणु
			mchip_cont_पढ़ो_frame(v, buf, bufsize);
			अवरोध;
		पूर्ण
		mchip_मुक्त_frame();
	पूर्ण
पूर्ण

/* start continuous dma capture */
अटल व्योम mchip_continuous_start(व्योम)
अणु
	mchip_hic_stop();
	mchip_subsample();
	mchip_set_framerate();
	mchip_dma_setup(meye.mchip_dmahandle);

	meye.mchip_mode = MCHIP_HIC_MODE_CONT_OUT;

	mchip_set(MCHIP_HIC_MODE, MCHIP_HIC_MODE_CONT_OUT);
	mchip_set(MCHIP_HIC_CMD, MCHIP_HIC_CMD_START);

	mchip_delay(MCHIP_HIC_CMD, 0);
पूर्ण

/* compress one frame पूर्णांकo a buffer */
अटल पूर्णांक mchip_compress_frame(u8 *buf, पूर्णांक bufsize)
अणु
	u32 v;
	पूर्णांक len = -1, i;

	mchip_vrj_setup(0x3f);
	udelay(50);

	mchip_set(MCHIP_HIC_MODE, MCHIP_HIC_MODE_STILL_COMP);
	mchip_set(MCHIP_HIC_CMD, MCHIP_HIC_CMD_START);

	mchip_delay(MCHIP_HIC_CMD, 0);
	क्रम (i = 0; i < 100; ++i) अणु
		अगर (mchip_delay(MCHIP_HIC_STATUS, MCHIP_HIC_STATUS_IDLE))
			अवरोध;
		msleep(1);
	पूर्ण

	क्रम (i = 0; i < 4; ++i) अणु
		v = mchip_get_frame();
		अगर (v & MCHIP_MM_FIR_RDY) अणु
			len = mchip_comp_पढ़ो_frame(v, buf, bufsize);
			अवरोध;
		पूर्ण
		mchip_मुक्त_frame();
	पूर्ण
	वापस len;
पूर्ण

#अगर 0
/* uncompress one image पूर्णांकo a buffer */
अटल पूर्णांक mchip_uncompress_frame(u8 *img, पूर्णांक imgsize, u8 *buf, पूर्णांक bufsize)
अणु
	mchip_vrj_setup(0x3f);
	udelay(50);

	mchip_set(MCHIP_HIC_MODE, MCHIP_HIC_MODE_STILL_DECOMP);
	mchip_set(MCHIP_HIC_CMD, MCHIP_HIC_CMD_START);

	mchip_delay(MCHIP_HIC_CMD, 0);

	वापस mchip_comp_पढ़ो_frame(buf, bufsize);
पूर्ण
#पूर्ण_अगर

/* start continuous compressed capture */
अटल व्योम mchip_cont_compression_start(व्योम)
अणु
	mchip_hic_stop();
	mchip_vrj_setup(0x3f);
	mchip_subsample();
	mchip_set_framerate();
	mchip_dma_setup(meye.mchip_dmahandle);

	meye.mchip_mode = MCHIP_HIC_MODE_CONT_COMP;

	mchip_set(MCHIP_HIC_MODE, MCHIP_HIC_MODE_CONT_COMP);
	mchip_set(MCHIP_HIC_CMD, MCHIP_HIC_CMD_START);

	mchip_delay(MCHIP_HIC_CMD, 0);
पूर्ण

/****************************************************************************/
/* Interrupt handling                                                       */
/****************************************************************************/

अटल irqवापस_t meye_irq(पूर्णांक irq, व्योम *dev_id)
अणु
	u32 v;
	पूर्णांक reqnr;
	अटल पूर्णांक sequence;

	v = mchip_पढ़ो(MCHIP_MM_INTA);

	अगर (meye.mchip_mode != MCHIP_HIC_MODE_CONT_OUT &&
	    meye.mchip_mode != MCHIP_HIC_MODE_CONT_COMP)
		वापस IRQ_NONE;

again:
	v = mchip_get_frame();
	अगर (!(v & MCHIP_MM_FIR_RDY))
		वापस IRQ_HANDLED;

	अगर (meye.mchip_mode == MCHIP_HIC_MODE_CONT_OUT) अणु
		अगर (kfअगरo_out_locked(&meye.grabq, (अचिन्हित अक्षर *)&reqnr,
			      माप(पूर्णांक), &meye.grabq_lock) != माप(पूर्णांक)) अणु
			mchip_मुक्त_frame();
			वापस IRQ_HANDLED;
		पूर्ण
		mchip_cont_पढ़ो_frame(v, meye.grab_fbuffer + gbufsize * reqnr,
				      mchip_hsize() * mchip_vsize() * 2);
		meye.grab_buffer[reqnr].size = mchip_hsize() * mchip_vsize() * 2;
		meye.grab_buffer[reqnr].state = MEYE_BUF_DONE;
		meye.grab_buffer[reqnr].ts = kसमय_get_ns();
		meye.grab_buffer[reqnr].sequence = sequence++;
		kfअगरo_in_locked(&meye.करोneq, (अचिन्हित अक्षर *)&reqnr,
				माप(पूर्णांक), &meye.करोneq_lock);
		wake_up_पूर्णांकerruptible(&meye.proc_list);
	पूर्ण अन्यथा अणु
		पूर्णांक size;
		size = mchip_comp_पढ़ो_frame(v, meye.grab_temp, gbufsize);
		अगर (size == -1) अणु
			mchip_मुक्त_frame();
			जाओ again;
		पूर्ण
		अगर (kfअगरo_out_locked(&meye.grabq, (अचिन्हित अक्षर *)&reqnr,
			      माप(पूर्णांक), &meye.grabq_lock) != माप(पूर्णांक)) अणु
			mchip_मुक्त_frame();
			जाओ again;
		पूर्ण
		स_नकल(meye.grab_fbuffer + gbufsize * reqnr, meye.grab_temp,
		       size);
		meye.grab_buffer[reqnr].size = size;
		meye.grab_buffer[reqnr].state = MEYE_BUF_DONE;
		meye.grab_buffer[reqnr].ts = kसमय_get_ns();
		meye.grab_buffer[reqnr].sequence = sequence++;
		kfअगरo_in_locked(&meye.करोneq, (अचिन्हित अक्षर *)&reqnr,
				माप(पूर्णांक), &meye.करोneq_lock);
		wake_up_पूर्णांकerruptible(&meye.proc_list);
	पूर्ण
	mchip_मुक्त_frame();
	जाओ again;
पूर्ण

/****************************************************************************/
/* video4linux पूर्णांकegration                                                  */
/****************************************************************************/

अटल पूर्णांक meye_खोलो(काष्ठा file *file)
अणु
	पूर्णांक i;

	अगर (test_and_set_bit(0, &meye.in_use))
		वापस -EBUSY;

	mchip_hic_stop();

	अगर (mchip_dma_alloc()) अणु
		prपूर्णांकk(KERN_ERR "meye: mchip framebuffer allocation failed\n");
		clear_bit(0, &meye.in_use);
		वापस -ENOBUFS;
	पूर्ण

	क्रम (i = 0; i < MEYE_MAX_BUFNBRS; i++)
		meye.grab_buffer[i].state = MEYE_BUF_UNUSED;
	kfअगरo_reset(&meye.grabq);
	kfअगरo_reset(&meye.करोneq);
	वापस v4l2_fh_खोलो(file);
पूर्ण

अटल पूर्णांक meye_release(काष्ठा file *file)
अणु
	mchip_hic_stop();
	mchip_dma_मुक्त();
	clear_bit(0, &meye.in_use);
	वापस v4l2_fh_release(file);
पूर्ण

अटल पूर्णांक meyeioc_g_params(काष्ठा meye_params *p)
अणु
	*p = meye.params;
	वापस 0;
पूर्ण

अटल पूर्णांक meyeioc_s_params(काष्ठा meye_params *jp)
अणु
	अगर (jp->subsample > 1)
		वापस -EINVAL;

	अगर (jp->quality > 10)
		वापस -EINVAL;

	अगर (jp->sharpness > 63 || jp->agc > 63 || jp->picture > 63)
		वापस -EINVAL;

	अगर (jp->framerate > 31)
		वापस -EINVAL;

	mutex_lock(&meye.lock);

	अगर (meye.params.subsample != jp->subsample ||
	    meye.params.quality != jp->quality)
		mchip_hic_stop();	/* need restart */

	meye.params = *jp;
	sony_pic_camera_command(SONY_PIC_COMMAND_SETCAMERASHARPNESS,
			      meye.params.sharpness);
	sony_pic_camera_command(SONY_PIC_COMMAND_SETCAMERAAGC,
			      meye.params.agc);
	sony_pic_camera_command(SONY_PIC_COMMAND_SETCAMERAPICTURE,
			      meye.params.picture);
	mutex_unlock(&meye.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक meyeioc_qbuf_capt(पूर्णांक *nb)
अणु
	अगर (!meye.grab_fbuffer)
		वापस -EINVAL;

	अगर (*nb >= gbuffers)
		वापस -EINVAL;

	अगर (*nb < 0) अणु
		/* stop capture */
		mchip_hic_stop();
		वापस 0;
	पूर्ण

	अगर (meye.grab_buffer[*nb].state != MEYE_BUF_UNUSED)
		वापस -EBUSY;

	mutex_lock(&meye.lock);

	अगर (meye.mchip_mode != MCHIP_HIC_MODE_CONT_COMP)
		mchip_cont_compression_start();

	meye.grab_buffer[*nb].state = MEYE_BUF_USING;
	kfअगरo_in_locked(&meye.grabq, (अचिन्हित अक्षर *)nb, माप(पूर्णांक),
			 &meye.grabq_lock);
	mutex_unlock(&meye.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक meyeioc_sync(काष्ठा file *file, व्योम *fh, पूर्णांक *i)
अणु
	पूर्णांक unused;

	अगर (*i < 0 || *i >= gbuffers)
		वापस -EINVAL;

	mutex_lock(&meye.lock);
	चयन (meye.grab_buffer[*i].state) अणु

	हाल MEYE_BUF_UNUSED:
		mutex_unlock(&meye.lock);
		वापस -EINVAL;
	हाल MEYE_BUF_USING:
		अगर (file->f_flags & O_NONBLOCK) अणु
			mutex_unlock(&meye.lock);
			वापस -EAGAIN;
		पूर्ण
		अगर (रुको_event_पूर्णांकerruptible(meye.proc_list,
			(meye.grab_buffer[*i].state != MEYE_BUF_USING))) अणु
			mutex_unlock(&meye.lock);
			वापस -EINTR;
		पूर्ण
		fallthrough;
	हाल MEYE_BUF_DONE:
		meye.grab_buffer[*i].state = MEYE_BUF_UNUSED;
		अगर (kfअगरo_out_locked(&meye.करोneq, (अचिन्हित अक्षर *)&unused,
				माप(पूर्णांक), &meye.करोneq_lock) != माप(पूर्णांक))
					अवरोध;
	पूर्ण
	*i = meye.grab_buffer[*i].size;
	mutex_unlock(&meye.lock);
	वापस 0;
पूर्ण

अटल पूर्णांक meyeioc_stillcapt(व्योम)
अणु
	अगर (!meye.grab_fbuffer)
		वापस -EINVAL;

	अगर (meye.grab_buffer[0].state != MEYE_BUF_UNUSED)
		वापस -EBUSY;

	mutex_lock(&meye.lock);
	meye.grab_buffer[0].state = MEYE_BUF_USING;
	mchip_take_picture();

	mchip_get_picture(meye.grab_fbuffer,
			mchip_hsize() * mchip_vsize() * 2);

	meye.grab_buffer[0].state = MEYE_BUF_DONE;
	mutex_unlock(&meye.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक meyeioc_stilljcapt(पूर्णांक *len)
अणु
	अगर (!meye.grab_fbuffer)
		वापस -EINVAL;

	अगर (meye.grab_buffer[0].state != MEYE_BUF_UNUSED)
		वापस -EBUSY;

	mutex_lock(&meye.lock);
	meye.grab_buffer[0].state = MEYE_BUF_USING;
	*len = -1;

	जबतक (*len == -1) अणु
		mchip_take_picture();
		*len = mchip_compress_frame(meye.grab_fbuffer, gbufsize);
	पूर्ण

	meye.grab_buffer[0].state = MEYE_BUF_DONE;
	mutex_unlock(&meye.lock);
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_querycap(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_capability *cap)
अणु
	strscpy(cap->driver, "meye", माप(cap->driver));
	strscpy(cap->card, "meye", माप(cap->card));
	प्र_लिखो(cap->bus_info, "PCI:%s", pci_name(meye.mchip_dev));
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_input(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_input *i)
अणु
	अगर (i->index != 0)
		वापस -EINVAL;

	strscpy(i->name, "Camera", माप(i->name));
	i->type = V4L2_INPUT_TYPE_CAMERA;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक *i)
अणु
	*i = 0;
	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_input(काष्ठा file *file, व्योम *fh, अचिन्हित पूर्णांक i)
अणु
	अगर (i != 0)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक meye_s_ctrl(काष्ठा v4l2_ctrl *ctrl)
अणु
	mutex_lock(&meye.lock);
	चयन (ctrl->id) अणु
	हाल V4L2_CID_BRIGHTNESS:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERABRIGHTNESS, ctrl->val);
		meye.brightness = ctrl->val << 10;
		अवरोध;
	हाल V4L2_CID_HUE:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERAHUE, ctrl->val);
		meye.hue = ctrl->val << 10;
		अवरोध;
	हाल V4L2_CID_CONTRAST:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERACONTRAST, ctrl->val);
		meye.contrast = ctrl->val << 10;
		अवरोध;
	हाल V4L2_CID_SATURATION:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERACOLOR, ctrl->val);
		meye.colour = ctrl->val << 10;
		अवरोध;
	हाल V4L2_CID_MEYE_AGC:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERAAGC, ctrl->val);
		meye.params.agc = ctrl->val;
		अवरोध;
	हाल V4L2_CID_SHARPNESS:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERASHARPNESS, ctrl->val);
		meye.params.sharpness = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MEYE_PICTURE:
		sony_pic_camera_command(
			SONY_PIC_COMMAND_SETCAMERAPICTURE, ctrl->val);
		meye.params.picture = ctrl->val;
		अवरोध;
	हाल V4L2_CID_JPEG_COMPRESSION_QUALITY:
		meye.params.quality = ctrl->val;
		अवरोध;
	हाल V4L2_CID_MEYE_FRAMERATE:
		meye.params.framerate = ctrl->val;
		अवरोध;
	शेष:
		mutex_unlock(&meye.lock);
		वापस -EINVAL;
	पूर्ण
	mutex_unlock(&meye.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_क्रमागत_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_fmtdesc *f)
अणु
	अगर (f->index > 1)
		वापस -EINVAL;

	अगर (f->index == 0) अणु
		/* standard YUV 422 capture */
		f->flags = 0;
		f->pixelक्रमmat = V4L2_PIX_FMT_YUYV;
	पूर्ण अन्यथा अणु
		/* compressed MJPEG capture */
		f->pixelक्रमmat = V4L2_PIX_FMT_MJPEG;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_try_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_क्रमmat *f)
अणु
	अगर (f->fmt.pix.pixelक्रमmat != V4L2_PIX_FMT_YUYV &&
	    f->fmt.pix.pixelक्रमmat != V4L2_PIX_FMT_MJPEG)
		वापस -EINVAL;

	अगर (f->fmt.pix.field != V4L2_FIELD_ANY &&
	    f->fmt.pix.field != V4L2_FIELD_NONE)
		वापस -EINVAL;

	f->fmt.pix.field = V4L2_FIELD_NONE;

	अगर (f->fmt.pix.width <= 320) अणु
		f->fmt.pix.width = 320;
		f->fmt.pix.height = 240;
	पूर्ण अन्यथा अणु
		f->fmt.pix.width = 640;
		f->fmt.pix.height = 480;
	पूर्ण

	f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.height *
			       f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_g_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	चयन (meye.mchip_mode) अणु
	हाल MCHIP_HIC_MODE_CONT_OUT:
	शेष:
		f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_YUYV;
		अवरोध;
	हाल MCHIP_HIC_MODE_CONT_COMP:
		f->fmt.pix.pixelक्रमmat = V4L2_PIX_FMT_MJPEG;
		अवरोध;
	पूर्ण

	f->fmt.pix.field = V4L2_FIELD_NONE;
	f->fmt.pix.width = mchip_hsize();
	f->fmt.pix.height = mchip_vsize();
	f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.height *
			       f->fmt.pix.bytesperline;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_s_fmt_vid_cap(काष्ठा file *file, व्योम *fh,
				    काष्ठा v4l2_क्रमmat *f)
अणु
	अगर (f->fmt.pix.pixelक्रमmat != V4L2_PIX_FMT_YUYV &&
	    f->fmt.pix.pixelक्रमmat != V4L2_PIX_FMT_MJPEG)
		वापस -EINVAL;

	अगर (f->fmt.pix.field != V4L2_FIELD_ANY &&
	    f->fmt.pix.field != V4L2_FIELD_NONE)
		वापस -EINVAL;

	f->fmt.pix.field = V4L2_FIELD_NONE;
	mutex_lock(&meye.lock);

	अगर (f->fmt.pix.width <= 320) अणु
		f->fmt.pix.width = 320;
		f->fmt.pix.height = 240;
		meye.params.subsample = 1;
	पूर्ण अन्यथा अणु
		f->fmt.pix.width = 640;
		f->fmt.pix.height = 480;
		meye.params.subsample = 0;
	पूर्ण

	चयन (f->fmt.pix.pixelक्रमmat) अणु
	हाल V4L2_PIX_FMT_YUYV:
		meye.mchip_mode = MCHIP_HIC_MODE_CONT_OUT;
		अवरोध;
	हाल V4L2_PIX_FMT_MJPEG:
		meye.mchip_mode = MCHIP_HIC_MODE_CONT_COMP;
		अवरोध;
	पूर्ण

	mutex_unlock(&meye.lock);
	f->fmt.pix.bytesperline = f->fmt.pix.width * 2;
	f->fmt.pix.sizeimage = f->fmt.pix.height *
			       f->fmt.pix.bytesperline;
	f->fmt.pix.colorspace = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_reqbufs(काष्ठा file *file, व्योम *fh,
				काष्ठा v4l2_requestbuffers *req)
अणु
	पूर्णांक i;

	अगर (req->memory != V4L2_MEMORY_MMAP)
		वापस -EINVAL;

	अगर (meye.grab_fbuffer && req->count == gbuffers) अणु
		/* alपढ़ोy allocated, no modअगरications */
		वापस 0;
	पूर्ण

	mutex_lock(&meye.lock);
	अगर (meye.grab_fbuffer) अणु
		क्रम (i = 0; i < gbuffers; i++)
			अगर (meye.vma_use_count[i]) अणु
				mutex_unlock(&meye.lock);
				वापस -EINVAL;
			पूर्ण
		rvमुक्त(meye.grab_fbuffer, gbuffers * gbufsize);
		meye.grab_fbuffer = शून्य;
	पूर्ण

	gbuffers = max(2, min((पूर्णांक)req->count, MEYE_MAX_BUFNBRS));
	req->count = gbuffers;
	meye.grab_fbuffer = rvदो_स्मृति(gbuffers * gbufsize);

	अगर (!meye.grab_fbuffer) अणु
		prपूर्णांकk(KERN_ERR "meye: v4l framebuffer allocation failed\n");
		mutex_unlock(&meye.lock);
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < gbuffers; i++)
		meye.vma_use_count[i] = 0;

	mutex_unlock(&meye.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_querybuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *buf)
अणु
	अचिन्हित पूर्णांक index = buf->index;

	अगर (index >= gbuffers)
		वापस -EINVAL;

	buf->bytesused = meye.grab_buffer[index].size;
	buf->flags = V4L2_BUF_FLAG_MAPPED | V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;

	अगर (meye.grab_buffer[index].state == MEYE_BUF_USING)
		buf->flags |= V4L2_BUF_FLAG_QUEUED;

	अगर (meye.grab_buffer[index].state == MEYE_BUF_DONE)
		buf->flags |= V4L2_BUF_FLAG_DONE;

	buf->field = V4L2_FIELD_NONE;
	v4l2_buffer_set_बारtamp(buf, meye.grab_buffer[index].ts);
	buf->sequence = meye.grab_buffer[index].sequence;
	buf->memory = V4L2_MEMORY_MMAP;
	buf->m.offset = index * gbufsize;
	buf->length = gbufsize;

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_qbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *buf)
अणु
	अगर (buf->memory != V4L2_MEMORY_MMAP)
		वापस -EINVAL;

	अगर (buf->index >= gbuffers)
		वापस -EINVAL;

	अगर (meye.grab_buffer[buf->index].state != MEYE_BUF_UNUSED)
		वापस -EINVAL;

	mutex_lock(&meye.lock);
	buf->flags |= V4L2_BUF_FLAG_QUEUED;
	buf->flags &= ~V4L2_BUF_FLAG_DONE;
	meye.grab_buffer[buf->index].state = MEYE_BUF_USING;
	kfअगरo_in_locked(&meye.grabq, (अचिन्हित अक्षर *)&buf->index,
			माप(पूर्णांक), &meye.grabq_lock);
	mutex_unlock(&meye.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_dqbuf(काष्ठा file *file, व्योम *fh, काष्ठा v4l2_buffer *buf)
अणु
	पूर्णांक reqnr;

	अगर (buf->memory != V4L2_MEMORY_MMAP)
		वापस -EINVAL;

	mutex_lock(&meye.lock);

	अगर (kfअगरo_len(&meye.करोneq) == 0 && file->f_flags & O_NONBLOCK) अणु
		mutex_unlock(&meye.lock);
		वापस -EAGAIN;
	पूर्ण

	अगर (रुको_event_पूर्णांकerruptible(meye.proc_list,
				     kfअगरo_len(&meye.करोneq) != 0) < 0) अणु
		mutex_unlock(&meye.lock);
		वापस -EINTR;
	पूर्ण

	अगर (!kfअगरo_out_locked(&meye.करोneq, (अचिन्हित अक्षर *)&reqnr,
		       माप(पूर्णांक), &meye.करोneq_lock)) अणु
		mutex_unlock(&meye.lock);
		वापस -EBUSY;
	पूर्ण

	अगर (meye.grab_buffer[reqnr].state != MEYE_BUF_DONE) अणु
		mutex_unlock(&meye.lock);
		वापस -EINVAL;
	पूर्ण

	buf->index = reqnr;
	buf->bytesused = meye.grab_buffer[reqnr].size;
	buf->flags = V4L2_BUF_FLAG_MAPPED | V4L2_BUF_FLAG_TIMESTAMP_MONOTONIC;
	buf->field = V4L2_FIELD_NONE;
	v4l2_buffer_set_बारtamp(buf, meye.grab_buffer[reqnr].ts);
	buf->sequence = meye.grab_buffer[reqnr].sequence;
	buf->memory = V4L2_MEMORY_MMAP;
	buf->m.offset = reqnr * gbufsize;
	buf->length = gbufsize;
	meye.grab_buffer[reqnr].state = MEYE_BUF_UNUSED;
	mutex_unlock(&meye.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_streamon(काष्ठा file *file, व्योम *fh, क्रमागत v4l2_buf_type i)
अणु
	mutex_lock(&meye.lock);

	चयन (meye.mchip_mode) अणु
	हाल MCHIP_HIC_MODE_CONT_OUT:
		mchip_continuous_start();
		अवरोध;
	हाल MCHIP_HIC_MODE_CONT_COMP:
		mchip_cont_compression_start();
		अवरोध;
	शेष:
		mutex_unlock(&meye.lock);
		वापस -EINVAL;
	पूर्ण

	mutex_unlock(&meye.lock);

	वापस 0;
पूर्ण

अटल पूर्णांक vidioc_streamoff(काष्ठा file *file, व्योम *fh, क्रमागत v4l2_buf_type i)
अणु
	mutex_lock(&meye.lock);
	mchip_hic_stop();
	kfअगरo_reset(&meye.grabq);
	kfअगरo_reset(&meye.करोneq);

	क्रम (i = 0; i < MEYE_MAX_BUFNBRS; i++)
		meye.grab_buffer[i].state = MEYE_BUF_UNUSED;

	mutex_unlock(&meye.lock);
	वापस 0;
पूर्ण

अटल दीर्घ vidioc_शेष(काष्ठा file *file, व्योम *fh, bool valid_prio,
			   अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	चयन (cmd) अणु
	हाल MEYEIOC_G_PARAMS:
		वापस meyeioc_g_params((काष्ठा meye_params *) arg);

	हाल MEYEIOC_S_PARAMS:
		वापस meyeioc_s_params((काष्ठा meye_params *) arg);

	हाल MEYEIOC_QBUF_CAPT:
		वापस meyeioc_qbuf_capt((पूर्णांक *) arg);

	हाल MEYEIOC_SYNC:
		वापस meyeioc_sync(file, fh, (पूर्णांक *) arg);

	हाल MEYEIOC_STILLCAPT:
		वापस meyeioc_stillcapt();

	हाल MEYEIOC_STILLJCAPT:
		वापस meyeioc_stilljcapt((पूर्णांक *) arg);

	शेष:
		वापस -ENOTTY;
	पूर्ण

पूर्ण

अटल __poll_t meye_poll(काष्ठा file *file, poll_table *रुको)
अणु
	__poll_t res = v4l2_ctrl_poll(file, रुको);

	mutex_lock(&meye.lock);
	poll_रुको(file, &meye.proc_list, रुको);
	अगर (kfअगरo_len(&meye.करोneq))
		res |= EPOLLIN | EPOLLRDNORM;
	mutex_unlock(&meye.lock);
	वापस res;
पूर्ण

अटल व्योम meye_vm_खोलो(काष्ठा vm_area_काष्ठा *vma)
अणु
	दीर्घ idx = (दीर्घ)vma->vm_निजी_data;
	meye.vma_use_count[idx]++;
पूर्ण

अटल व्योम meye_vm_बंद(काष्ठा vm_area_काष्ठा *vma)
अणु
	दीर्घ idx = (दीर्घ)vma->vm_निजी_data;
	meye.vma_use_count[idx]--;
पूर्ण

अटल स्थिर काष्ठा vm_operations_काष्ठा meye_vm_ops = अणु
	.खोलो		= meye_vm_खोलो,
	.बंद		= meye_vm_बंद,
पूर्ण;

अटल पूर्णांक meye_mmap(काष्ठा file *file, काष्ठा vm_area_काष्ठा *vma)
अणु
	अचिन्हित दीर्घ start = vma->vm_start;
	अचिन्हित दीर्घ size = vma->vm_end - vma->vm_start;
	अचिन्हित दीर्घ offset = vma->vm_pgoff << PAGE_SHIFT;
	अचिन्हित दीर्घ page, pos;

	mutex_lock(&meye.lock);
	अगर (size > gbuffers * gbufsize || offset > gbuffers * gbufsize - size) अणु
		mutex_unlock(&meye.lock);
		वापस -EINVAL;
	पूर्ण
	अगर (!meye.grab_fbuffer) अणु
		पूर्णांक i;

		/* lazy allocation */
		meye.grab_fbuffer = rvदो_स्मृति(gbuffers*gbufsize);
		अगर (!meye.grab_fbuffer) अणु
			prपूर्णांकk(KERN_ERR "meye: v4l framebuffer allocation failed\n");
			mutex_unlock(&meye.lock);
			वापस -ENOMEM;
		पूर्ण
		क्रम (i = 0; i < gbuffers; i++)
			meye.vma_use_count[i] = 0;
	पूर्ण
	pos = (अचिन्हित दीर्घ)meye.grab_fbuffer + offset;

	जबतक (size > 0) अणु
		page = vदो_स्मृति_to_pfn((व्योम *)pos);
		अगर (remap_pfn_range(vma, start, page, PAGE_SIZE, PAGE_SHARED)) अणु
			mutex_unlock(&meye.lock);
			वापस -EAGAIN;
		पूर्ण
		start += PAGE_SIZE;
		pos += PAGE_SIZE;
		अगर (size > PAGE_SIZE)
			size -= PAGE_SIZE;
		अन्यथा
			size = 0;
	पूर्ण

	vma->vm_ops = &meye_vm_ops;
	vma->vm_flags &= ~VM_IO;	/* not I/O memory */
	vma->vm_flags |= VM_DONTEXPAND | VM_DONTDUMP;
	vma->vm_निजी_data = (व्योम *) (offset / gbufsize);
	meye_vm_खोलो(vma);

	mutex_unlock(&meye.lock);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा v4l2_file_operations meye_fops = अणु
	.owner		= THIS_MODULE,
	.खोलो		= meye_खोलो,
	.release	= meye_release,
	.mmap		= meye_mmap,
	.unlocked_ioctl	= video_ioctl2,
	.poll		= meye_poll,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ioctl_ops meye_ioctl_ops = अणु
	.vidioc_querycap	= vidioc_querycap,
	.vidioc_क्रमागत_input	= vidioc_क्रमागत_input,
	.vidioc_g_input		= vidioc_g_input,
	.vidioc_s_input		= vidioc_s_input,
	.vidioc_क्रमागत_fmt_vid_cap = vidioc_क्रमागत_fmt_vid_cap,
	.vidioc_try_fmt_vid_cap	= vidioc_try_fmt_vid_cap,
	.vidioc_g_fmt_vid_cap	= vidioc_g_fmt_vid_cap,
	.vidioc_s_fmt_vid_cap	= vidioc_s_fmt_vid_cap,
	.vidioc_reqbufs		= vidioc_reqbufs,
	.vidioc_querybuf	= vidioc_querybuf,
	.vidioc_qbuf		= vidioc_qbuf,
	.vidioc_dqbuf		= vidioc_dqbuf,
	.vidioc_streamon	= vidioc_streamon,
	.vidioc_streamoff	= vidioc_streamoff,
	.vidioc_log_status	= v4l2_ctrl_log_status,
	.vidioc_subscribe_event	= v4l2_ctrl_subscribe_event,
	.vidioc_unsubscribe_event = v4l2_event_unsubscribe,
	.vidioc_शेष		= vidioc_शेष,
पूर्ण;

अटल स्थिर काष्ठा video_device meye_ढाँचा = अणु
	.name		= "meye",
	.fops		= &meye_fops,
	.ioctl_ops	= &meye_ioctl_ops,
	.release	= video_device_release_empty,
	.device_caps	= V4L2_CAP_VIDEO_CAPTURE | V4L2_CAP_STREAMING,
पूर्ण;

अटल स्थिर काष्ठा v4l2_ctrl_ops meye_ctrl_ops = अणु
	.s_ctrl = meye_s_ctrl,
पूर्ण;

अटल पूर्णांक __maybe_unused meye_suspend(काष्ठा device *dev)
अणु
	meye.pm_mchip_mode = meye.mchip_mode;
	mchip_hic_stop();
	mchip_set(MCHIP_MM_INTA, 0x0);
	वापस 0;
पूर्ण

अटल पूर्णांक __maybe_unused meye_resume(काष्ठा device *dev)
अणु
	pci_ग_लिखो_config_word(meye.mchip_dev, MCHIP_PCI_SOFTRESET_SET, 1);

	mchip_delay(MCHIP_HIC_CMD, 0);
	mchip_delay(MCHIP_HIC_STATUS, MCHIP_HIC_STATUS_IDLE);
	msleep(1);
	mchip_set(MCHIP_VRJ_SOFT_RESET, 1);
	msleep(1);
	mchip_set(MCHIP_MM_PCI_MODE, 5);
	msleep(1);
	mchip_set(MCHIP_MM_INTA, MCHIP_MM_INTA_HIC_1_MASK);

	चयन (meye.pm_mchip_mode) अणु
	हाल MCHIP_HIC_MODE_CONT_OUT:
		mchip_continuous_start();
		अवरोध;
	हाल MCHIP_HIC_MODE_CONT_COMP:
		mchip_cont_compression_start();
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक meye_probe(काष्ठा pci_dev *pcidev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अटल स्थिर काष्ठा v4l2_ctrl_config ctrl_agc = अणु
		.id = V4L2_CID_MEYE_AGC,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.ops = &meye_ctrl_ops,
		.name = "AGC",
		.max = 63,
		.step = 1,
		.def = 48,
		.flags = V4L2_CTRL_FLAG_SLIDER,
	पूर्ण;
	अटल स्थिर काष्ठा v4l2_ctrl_config ctrl_picture = अणु
		.id = V4L2_CID_MEYE_PICTURE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.ops = &meye_ctrl_ops,
		.name = "Picture",
		.max = 63,
		.step = 1,
	पूर्ण;
	अटल स्थिर काष्ठा v4l2_ctrl_config ctrl_framerate = अणु
		.id = V4L2_CID_MEYE_FRAMERATE,
		.type = V4L2_CTRL_TYPE_INTEGER,
		.ops = &meye_ctrl_ops,
		.name = "Framerate",
		.max = 31,
		.step = 1,
	पूर्ण;
	काष्ठा v4l2_device *v4l2_dev = &meye.v4l2_dev;
	पूर्णांक ret = -EBUSY;
	अचिन्हित दीर्घ mchip_adr;

	अगर (meye.mchip_dev != शून्य) अणु
		prपूर्णांकk(KERN_ERR "meye: only one device allowed!\n");
		वापस ret;
	पूर्ण

	ret = v4l2_device_रेजिस्टर(&pcidev->dev, v4l2_dev);
	अगर (ret < 0) अणु
		v4l2_err(v4l2_dev, "Could not register v4l2_device\n");
		वापस ret;
	पूर्ण
	ret = -ENOMEM;
	meye.mchip_dev = pcidev;

	meye.grab_temp = vदो_स्मृति(array_size(PAGE_SIZE, MCHIP_NB_PAGES_MJPEG));
	अगर (!meye.grab_temp)
		जाओ outvदो_स्मृति;

	spin_lock_init(&meye.grabq_lock);
	अगर (kfअगरo_alloc(&meye.grabq, माप(पूर्णांक) * MEYE_MAX_BUFNBRS,
			GFP_KERNEL))
		जाओ outkfअगरoalloc1;

	spin_lock_init(&meye.करोneq_lock);
	अगर (kfअगरo_alloc(&meye.करोneq, माप(पूर्णांक) * MEYE_MAX_BUFNBRS,
			GFP_KERNEL))
		जाओ outkfअगरoalloc2;

	meye.vdev = meye_ढाँचा;
	meye.vdev.v4l2_dev = &meye.v4l2_dev;

	ret = sony_pic_camera_command(SONY_PIC_COMMAND_SETCAMERA, 1);
	अगर (ret) अणु
		v4l2_err(v4l2_dev, "meye: unable to power on the camera\n");
		v4l2_err(v4l2_dev, "meye: did you enable the camera in sonypi using the module options ?\n");
		जाओ outsonypienable;
	पूर्ण

	ret = pci_enable_device(meye.mchip_dev);
	अगर (ret) अणु
		v4l2_err(v4l2_dev, "meye: pci_enable_device failed\n");
		जाओ outenabledev;
	पूर्ण

	ret = -EIO;
	mchip_adr = pci_resource_start(meye.mchip_dev,0);
	अगर (!mchip_adr) अणु
		v4l2_err(v4l2_dev, "meye: mchip has no device base address\n");
		जाओ outregions;
	पूर्ण
	अगर (!request_mem_region(pci_resource_start(meye.mchip_dev, 0),
				pci_resource_len(meye.mchip_dev, 0),
				"meye")) अणु
		v4l2_err(v4l2_dev, "meye: request_mem_region failed\n");
		जाओ outregions;
	पूर्ण
	meye.mchip_mmregs = ioremap(mchip_adr, MCHIP_MM_REGS);
	अगर (!meye.mchip_mmregs) अणु
		v4l2_err(v4l2_dev, "meye: ioremap failed\n");
		जाओ outremap;
	पूर्ण

	meye.mchip_irq = pcidev->irq;
	अगर (request_irq(meye.mchip_irq, meye_irq,
			IRQF_SHARED, "meye", meye_irq)) अणु
		v4l2_err(v4l2_dev, "request_irq failed\n");
		जाओ outreqirq;
	पूर्ण

	pci_ग_लिखो_config_byte(meye.mchip_dev, PCI_CACHE_LINE_SIZE, 8);
	pci_ग_लिखो_config_byte(meye.mchip_dev, PCI_LATENCY_TIMER, 64);

	pci_set_master(meye.mchip_dev);

	/* Ask the camera to perक्रमm a soft reset. */
	pci_ग_लिखो_config_word(meye.mchip_dev, MCHIP_PCI_SOFTRESET_SET, 1);

	mchip_delay(MCHIP_HIC_CMD, 0);
	mchip_delay(MCHIP_HIC_STATUS, MCHIP_HIC_STATUS_IDLE);

	msleep(1);
	mchip_set(MCHIP_VRJ_SOFT_RESET, 1);

	msleep(1);
	mchip_set(MCHIP_MM_PCI_MODE, 5);

	msleep(1);
	mchip_set(MCHIP_MM_INTA, MCHIP_MM_INTA_HIC_1_MASK);

	mutex_init(&meye.lock);
	init_रुकोqueue_head(&meye.proc_list);

	v4l2_ctrl_handler_init(&meye.hdl, 3);
	v4l2_ctrl_new_std(&meye.hdl, &meye_ctrl_ops,
			  V4L2_CID_BRIGHTNESS, 0, 63, 1, 32);
	v4l2_ctrl_new_std(&meye.hdl, &meye_ctrl_ops,
			  V4L2_CID_HUE, 0, 63, 1, 32);
	v4l2_ctrl_new_std(&meye.hdl, &meye_ctrl_ops,
			  V4L2_CID_CONTRAST, 0, 63, 1, 32);
	v4l2_ctrl_new_std(&meye.hdl, &meye_ctrl_ops,
			  V4L2_CID_SATURATION, 0, 63, 1, 32);
	v4l2_ctrl_new_custom(&meye.hdl, &ctrl_agc, शून्य);
	v4l2_ctrl_new_std(&meye.hdl, &meye_ctrl_ops,
			  V4L2_CID_SHARPNESS, 0, 63, 1, 32);
	v4l2_ctrl_new_custom(&meye.hdl, &ctrl_picture, शून्य);
	v4l2_ctrl_new_std(&meye.hdl, &meye_ctrl_ops,
			  V4L2_CID_JPEG_COMPRESSION_QUALITY, 0, 10, 1, 8);
	v4l2_ctrl_new_custom(&meye.hdl, &ctrl_framerate, शून्य);
	अगर (meye.hdl.error) अणु
		v4l2_err(v4l2_dev, "couldn't register controls\n");
		जाओ outvideoreg;
	पूर्ण

	v4l2_ctrl_handler_setup(&meye.hdl);
	meye.vdev.ctrl_handler = &meye.hdl;

	अगर (video_रेजिस्टर_device(&meye.vdev, VFL_TYPE_VIDEO,
				  video_nr) < 0) अणु
		v4l2_err(v4l2_dev, "video_register_device failed\n");
		जाओ outvideoreg;
	पूर्ण

	v4l2_info(v4l2_dev, "Motion Eye Camera Driver v%s.\n",
	       MEYE_DRIVER_VERSION);
	v4l2_info(v4l2_dev, "mchip KL5A72002 rev. %d, base %lx, irq %d\n",
	       meye.mchip_dev->revision, mchip_adr, meye.mchip_irq);

	वापस 0;

outvideoreg:
	v4l2_ctrl_handler_मुक्त(&meye.hdl);
	मुक्त_irq(meye.mchip_irq, meye_irq);
outreqirq:
	iounmap(meye.mchip_mmregs);
outremap:
	release_mem_region(pci_resource_start(meye.mchip_dev, 0),
			   pci_resource_len(meye.mchip_dev, 0));
outregions:
	pci_disable_device(meye.mchip_dev);
outenabledev:
	sony_pic_camera_command(SONY_PIC_COMMAND_SETCAMERA, 0);
outsonypienable:
	kfअगरo_मुक्त(&meye.करोneq);
outkfअगरoalloc2:
	kfअगरo_मुक्त(&meye.grabq);
outkfअगरoalloc1:
	vमुक्त(meye.grab_temp);
outvदो_स्मृति:
	वापस ret;
पूर्ण

अटल व्योम meye_हटाओ(काष्ठा pci_dev *pcidev)
अणु
	video_unरेजिस्टर_device(&meye.vdev);

	mchip_hic_stop();

	mchip_dma_मुक्त();

	/* disable पूर्णांकerrupts */
	mchip_set(MCHIP_MM_INTA, 0x0);

	मुक्त_irq(meye.mchip_irq, meye_irq);

	iounmap(meye.mchip_mmregs);

	release_mem_region(pci_resource_start(meye.mchip_dev, 0),
			   pci_resource_len(meye.mchip_dev, 0));

	pci_disable_device(meye.mchip_dev);

	sony_pic_camera_command(SONY_PIC_COMMAND_SETCAMERA, 0);

	kfअगरo_मुक्त(&meye.करोneq);
	kfअगरo_मुक्त(&meye.grabq);

	vमुक्त(meye.grab_temp);

	अगर (meye.grab_fbuffer) अणु
		rvमुक्त(meye.grab_fbuffer, gbuffers*gbufsize);
		meye.grab_fbuffer = शून्य;
	पूर्ण

	prपूर्णांकk(KERN_INFO "meye: removed\n");
पूर्ण

अटल स्थिर काष्ठा pci_device_id meye_pci_tbl[] = अणु
	अणु PCI_VDEVICE(KAWASAKI, PCI_DEVICE_ID_MCHIP_KL5A72002), 0 पूर्ण,
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, meye_pci_tbl);

अटल SIMPLE_DEV_PM_OPS(meye_pm_ops, meye_suspend, meye_resume);

अटल काष्ठा pci_driver meye_driver = अणु
	.name		= "meye",
	.id_table	= meye_pci_tbl,
	.probe		= meye_probe,
	.हटाओ		= meye_हटाओ,
	.driver.pm	= &meye_pm_ops,
पूर्ण;

अटल पूर्णांक __init meye_init(व्योम)
अणु
	gbuffers = max(2, min((पूर्णांक)gbuffers, MEYE_MAX_BUFNBRS));
	अगर (gbufsize > MEYE_MAX_बफ_मानE)
		gbufsize = MEYE_MAX_बफ_मानE;
	gbufsize = PAGE_ALIGN(gbufsize);
	prपूर्णांकk(KERN_INFO "meye: using %d buffers with %dk (%dk total) for capture\n",
			 gbuffers,
			 gbufsize / 1024, gbuffers * gbufsize / 1024);
	वापस pci_रेजिस्टर_driver(&meye_driver);
पूर्ण

अटल व्योम __निकास meye_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&meye_driver);
पूर्ण

module_init(meye_init);
module_निकास(meye_निकास);
