<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * linux/drivers/video/mmp/fb/mmpfb.h
 * Framebuffer driver क्रम Marvell Display controller.
 *
 * Copyright (C) 2012 Marvell Technology Group Ltd.
 * Authors: Zhou Zhu <zzhu3@marvell.com>
 */

#अगर_अघोषित _MMP_FB_H_
#घोषणा _MMP_FB_H_

#समावेश <video/mmp_disp.h>
#समावेश <linux/fb.h>

/* LCD controller निजी state. */
काष्ठा mmpfb_info अणु
	काष्ठा device	*dev;
	पूर्णांक	id;
	स्थिर अक्षर	*name;

	काष्ठा fb_info	*fb_info;
	/* basicaly videomode is क्रम output */
	काष्ठा fb_videomode	mode;
	पूर्णांक	pix_fmt;

	व्योम	*fb_start;
	पूर्णांक	fb_size;
	dma_addr_t	fb_start_dma;

	काष्ठा mmp_overlay	*overlay;
	काष्ठा mmp_path	*path;

	काष्ठा mutex	access_ok;

	अचिन्हित पूर्णांक		pseuकरो_palette[16];
	पूर्णांक output_fmt;
पूर्ण;

#घोषणा MMPFB_DEFAULT_SIZE (PAGE_ALIGN(1920 * 1080 * 4 * 2))
#पूर्ण_अगर /* _MMP_FB_H_ */
