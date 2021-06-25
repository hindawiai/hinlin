<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/video/vt8500lcdfb.h
 *
 *  Copyright (C) 2010 Alexey Charkov <alअक्षरk@gmail.com>
 */

काष्ठा vt8500lcd_info अणु
	काष्ठा fb_info		fb;
	व्योम __iomem		*regbase;
	व्योम __iomem		*palette_cpu;
	dma_addr_t		palette_phys;
	माप_प्रकार			palette_size;
	रुको_queue_head_t	रुको;
पूर्ण;

अटल पूर्णांक bpp_values[] = अणु
	1,
	2,
	4,
	8,
	12,
	16,
	18,
	24,
पूर्ण;
