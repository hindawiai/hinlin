<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2008
 * Guennadi Liakhovetski, DENX Software Engineering, <lg@denx.de>
 */

#अगर_अघोषित __ASM_ARCH_MX3FB_H__
#घोषणा __ASM_ARCH_MX3FB_H__

#समावेश <linux/device.h>
#समावेश <linux/fb.h>

/* Proprietary FB_SYNC_ flags */
#घोषणा FB_SYNC_OE_ACT_HIGH	0x80000000
#घोषणा FB_SYNC_CLK_INVERT	0x40000000
#घोषणा FB_SYNC_DATA_INVERT	0x20000000
#घोषणा FB_SYNC_CLK_IDLE_EN	0x10000000
#घोषणा FB_SYNC_SHARP_MODE	0x08000000
#घोषणा FB_SYNC_SWAP_RGB	0x04000000
#घोषणा FB_SYNC_CLK_SEL_EN	0x02000000

/*
 * Specअगरy the way your display is connected. The IPU can arbitrarily
 * map the पूर्णांकernal colors to the बाह्यal data lines. We only support
 * the following mappings at the moment.
 */
क्रमागत disp_data_mapping अणु
	/* blue -> d[0..5], green -> d[6..11], red -> d[12..17] */
	IPU_DISP_DATA_MAPPING_RGB666,
	/* blue -> d[0..4], green -> d[5..10], red -> d[11..15] */
	IPU_DISP_DATA_MAPPING_RGB565,
	/* blue -> d[0..7], green -> d[8..15], red -> d[16..23] */
	IPU_DISP_DATA_MAPPING_RGB888,
पूर्ण;

/**
 * काष्ठा mx3fb_platक्रमm_data - mx3fb platक्रमm data
 *
 * @dma_dev:	poपूर्णांकer to the dma-device, used क्रम dma-slave connection
 * @mode:	poपूर्णांकer to a platक्रमm-provided per mxc_रेजिस्टर_fb() videomode
 */
काष्ठा mx3fb_platक्रमm_data अणु
	काष्ठा device			*dma_dev;
	स्थिर अक्षर			*name;
	स्थिर काष्ठा fb_videomode	*mode;
	पूर्णांक				num_modes;
	क्रमागत disp_data_mapping		disp_data_fmt;
पूर्ण;

#पूर्ण_अगर
