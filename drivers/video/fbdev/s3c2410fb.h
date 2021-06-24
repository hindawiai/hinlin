<शैली गुरु>
/*
 * linux/drivers/video/s3c2410fb.h
 *	Copyright (c) 2004 Arnaud Patard
 *
 *  S3C2410 LCD Framebuffer Driver
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive क्रम
 * more details.
 *
*/

#अगर_अघोषित __S3C2410FB_H
#घोषणा __S3C2410FB_H

क्रमागत s3c_drv_type अणु
	DRV_S3C2410,
	DRV_S3C2412,
पूर्ण;

काष्ठा s3c2410fb_info अणु
	काष्ठा device		*dev;
	काष्ठा clk		*clk;

	काष्ठा resource		*mem;
	व्योम __iomem		*io;
	व्योम __iomem		*irq_base;

	क्रमागत s3c_drv_type	drv_type;
	काष्ठा s3c2410fb_hw	regs;

	अचिन्हित दीर्घ		clk_rate;
	अचिन्हित पूर्णांक		palette_पढ़ोy;

#अगर_घोषित CONFIG_ARM_S3C24XX_CPUFREQ
	काष्ठा notअगरier_block	freq_transition;
#पूर्ण_अगर

	/* keep these रेजिस्टरs in हाल we need to re-ग_लिखो palette */
	u32			palette_buffer[256];
	u32			pseuकरो_pal[16];
पूर्ण;

#घोषणा PALETTE_BUFF_CLEAR (0x80000000)	/* entry is clear/invalid */

पूर्णांक s3c2410fb_init(व्योम);

#पूर्ण_अगर
