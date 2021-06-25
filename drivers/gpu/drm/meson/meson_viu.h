<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Copyright (C) 2016 BayLibre, SAS
 * Author: Neil Armstrong <narmstrong@baylibre.com>
 */

/* Video Input Unit */

#अगर_अघोषित __MESON_VIU_H
#घोषणा __MESON_VIU_H

/* OSDx_BLKx_CFG */
#घोषणा OSD_MALI_SRC_EN		BIT(30)

#घोषणा OSD_CANVAS_SEL		16

#घोषणा OSD_ENDIANNESS_LE	BIT(15)
#घोषणा OSD_ENDIANNESS_BE	(0)

#घोषणा OSD_BLK_MODE_422	(0x03 << 8)
#घोषणा OSD_BLK_MODE_16		(0x04 << 8)
#घोषणा OSD_BLK_MODE_32		(0x05 << 8)
#घोषणा OSD_BLK_MODE_24		(0x07 << 8)

#घोषणा OSD_OUTPUT_COLOR_RGB	BIT(7)
#घोषणा OSD_OUTPUT_COLOR_YUV	(0)

#घोषणा OSD_COLOR_MATRIX_32_RGBA	(0x00 << 2)
#घोषणा OSD_COLOR_MATRIX_32_ARGB	(0x01 << 2)
#घोषणा OSD_COLOR_MATRIX_32_ABGR	(0x02 << 2)
#घोषणा OSD_COLOR_MATRIX_32_BGRA	(0x03 << 2)

#घोषणा OSD_COLOR_MATRIX_24_RGB		(0x00 << 2)

#घोषणा OSD_COLOR_MATRIX_16_RGB655	(0x00 << 2)
#घोषणा OSD_COLOR_MATRIX_16_RGB565	(0x04 << 2)

#घोषणा OSD_MALI_COLOR_MODE_R8		(0 << 8)
#घोषणा OSD_MALI_COLOR_MODE_YUV422	(1 << 8)
#घोषणा OSD_MALI_COLOR_MODE_RGB565	(2 << 8)
#घोषणा OSD_MALI_COLOR_MODE_RGBA5551	(3 << 8)
#घोषणा OSD_MALI_COLOR_MODE_RGBA4444	(4 << 8)
#घोषणा OSD_MALI_COLOR_MODE_RGBA8888	(5 << 8)
#घोषणा OSD_MALI_COLOR_MODE_RGB888	(7 << 8)
#घोषणा OSD_MALI_COLOR_MODE_YUV422_10B	(8 << 8)
#घोषणा OSD_MALI_COLOR_MODE_RGBA1010102	(9 << 8)

#घोषणा OSD_INTERLACE_ENABLED	BIT(1)
#घोषणा OSD_INTERLACE_ODD	BIT(0)
#घोषणा OSD_INTERLACE_EVEN	(0)

/* OSDx_CTRL_STAT */
#घोषणा OSD_ENABLE		BIT(21)
#घोषणा OSD_MEM_LINEAR_ADDR	BIT(2)
#घोषणा OSD_BLK0_ENABLE		BIT(0)

#घोषणा OSD_GLOBAL_ALPHA_SHIFT	12

/* OSDx_CTRL_STAT2 */
#घोषणा OSD_DPATH_MALI_AFBCD	BIT(15)
#घोषणा OSD_REPLACE_EN		BIT(14)
#घोषणा OSD_REPLACE_SHIFT	6
#घोषणा OSD_PENDING_STAT_CLEAN	BIT(1)

व्योम meson_viu_osd1_reset(काष्ठा meson_drm *priv);
व्योम meson_viu_g12a_enable_osd1_afbc(काष्ठा meson_drm *priv);
व्योम meson_viu_g12a_disable_osd1_afbc(काष्ठा meson_drm *priv);
व्योम meson_viu_gxm_enable_osd1_afbc(काष्ठा meson_drm *priv);
व्योम meson_viu_gxm_disable_osd1_afbc(काष्ठा meson_drm *priv);
व्योम meson_viu_init(काष्ठा meson_drm *priv);

#पूर्ण_अगर /* __MESON_VIU_H */
