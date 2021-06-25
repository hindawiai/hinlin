<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * shmob_drm.h  --  SH Mobile DRM driver
 *
 * Copyright (C) 2012 Renesas Corporation
 *
 * Laurent Pinअक्षरt (laurent.pinअक्षरt@ideasonboard.com)
 */

#अगर_अघोषित __SHMOB_DRM_H__
#घोषणा __SHMOB_DRM_H__

#समावेश <drm/drm_mode.h>

क्रमागत shmob_drm_clk_source अणु
	SHMOB_DRM_CLK_BUS,
	SHMOB_DRM_CLK_PERIPHERAL,
	SHMOB_DRM_CLK_EXTERNAL,
पूर्ण;

क्रमागत shmob_drm_पूर्णांकerface अणु
	SHMOB_DRM_IFACE_RGB8,		/* 24bpp, 8:8:8 */
	SHMOB_DRM_IFACE_RGB9,		/* 18bpp, 9:9 */
	SHMOB_DRM_IFACE_RGB12A,		/* 24bpp, 12:12 */
	SHMOB_DRM_IFACE_RGB12B,		/* 12bpp */
	SHMOB_DRM_IFACE_RGB16,		/* 16bpp */
	SHMOB_DRM_IFACE_RGB18,		/* 18bpp */
	SHMOB_DRM_IFACE_RGB24,		/* 24bpp */
	SHMOB_DRM_IFACE_YUV422,		/* 16bpp */
	SHMOB_DRM_IFACE_SYS8A,		/* 24bpp, 8:8:8 */
	SHMOB_DRM_IFACE_SYS8B,		/* 18bpp, 8:8:2 */
	SHMOB_DRM_IFACE_SYS8C,		/* 18bpp, 2:8:8 */
	SHMOB_DRM_IFACE_SYS8D,		/* 16bpp, 8:8 */
	SHMOB_DRM_IFACE_SYS9,		/* 18bpp, 9:9 */
	SHMOB_DRM_IFACE_SYS12,		/* 24bpp, 12:12 */
	SHMOB_DRM_IFACE_SYS16A,		/* 16bpp */
	SHMOB_DRM_IFACE_SYS16B,		/* 18bpp, 16:2 */
	SHMOB_DRM_IFACE_SYS16C,		/* 18bpp, 2:16 */
	SHMOB_DRM_IFACE_SYS18,		/* 18bpp */
	SHMOB_DRM_IFACE_SYS24,		/* 24bpp */
पूर्ण;

काष्ठा shmob_drm_backlight_data अणु
	स्थिर अक्षर *name;
	पूर्णांक max_brightness;
	पूर्णांक (*get_brightness)(व्योम);
	पूर्णांक (*set_brightness)(पूर्णांक brightness);
पूर्ण;

काष्ठा shmob_drm_panel_data अणु
	अचिन्हित पूर्णांक width_mm;		/* Panel width in mm */
	अचिन्हित पूर्णांक height_mm;		/* Panel height in mm */
	काष्ठा drm_mode_modeinfo mode;
पूर्ण;

काष्ठा shmob_drm_sys_पूर्णांकerface_data अणु
	अचिन्हित पूर्णांक पढ़ो_latch:6;
	अचिन्हित पूर्णांक पढ़ो_setup:8;
	अचिन्हित पूर्णांक पढ़ो_cycle:8;
	अचिन्हित पूर्णांक पढ़ो_strobe:8;
	अचिन्हित पूर्णांक ग_लिखो_setup:8;
	अचिन्हित पूर्णांक ग_लिखो_cycle:8;
	अचिन्हित पूर्णांक ग_लिखो_strobe:8;
	अचिन्हित पूर्णांक cs_setup:3;
	अचिन्हित पूर्णांक vsync_active_high:1;
	अचिन्हित पूर्णांक vsync_dir_input:1;
पूर्ण;

#घोषणा SHMOB_DRM_IFACE_FL_DWPOL (1 << 0) /* Rising edge करोt घड़ी data latch */
#घोषणा SHMOB_DRM_IFACE_FL_DIPOL (1 << 1) /* Active low display enable */
#घोषणा SHMOB_DRM_IFACE_FL_DAPOL (1 << 2) /* Active low display data */
#घोषणा SHMOB_DRM_IFACE_FL_HSCNT (1 << 3) /* Disable HSYNC during VBLANK */
#घोषणा SHMOB_DRM_IFACE_FL_DWCNT (1 << 4) /* Disable करोtघड़ी during blanking */

काष्ठा shmob_drm_पूर्णांकerface_data अणु
	क्रमागत shmob_drm_पूर्णांकerface पूर्णांकerface;
	काष्ठा shmob_drm_sys_पूर्णांकerface_data sys;
	अचिन्हित पूर्णांक clk_भाग;
	अचिन्हित पूर्णांक flags;
पूर्ण;

काष्ठा shmob_drm_platक्रमm_data अणु
	क्रमागत shmob_drm_clk_source clk_source;
	काष्ठा shmob_drm_पूर्णांकerface_data अगरace;
	काष्ठा shmob_drm_panel_data panel;
	काष्ठा shmob_drm_backlight_data backlight;
पूर्ण;

#पूर्ण_अगर /* __SHMOB_DRM_H__ */
