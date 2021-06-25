<शैली गुरु>
/* sis_drv.h -- Private header क्रम sis driver -*- linux-c -*- */
/*
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित _SIS_DRV_H_
#घोषणा _SIS_DRV_H_

#समावेश <drm/drm_ioctl.h>
#समावेश <drm/drm_legacy.h>
#समावेश <drm/drm_mm.h>

/* General customization:
 */

#घोषणा DRIVER_AUTHOR		"SIS, Tungsten Graphics"
#घोषणा DRIVER_NAME		"sis"
#घोषणा DRIVER_DESC		"SIS 300/630/540 and XGI V3XE/V5/V8"
#घोषणा DRIVER_DATE		"20070626"
#घोषणा DRIVER_MAJOR		1
#घोषणा DRIVER_MINOR		3
#घोषणा DRIVER_PATCHLEVEL	0

क्रमागत sis_family अणु
	SIS_OTHER = 0,
	SIS_CHIP_315 = 1,
पूर्ण;

#घोषणा SIS_READ(reg)         पढ़ोl(((व्योम __iomem *)dev_priv->mmio->handle) + (reg))
#घोषणा SIS_WRITE(reg, val)   ग_लिखोl(val, ((व्योम __iomem *)dev_priv->mmio->handle) + (reg))

प्रकार काष्ठा drm_sis_निजी अणु
	drm_local_map_t *mmio;
	अचिन्हित पूर्णांक idle_fault;
	अचिन्हित पूर्णांक chipset;
	पूर्णांक vram_initialized;
	पूर्णांक agp_initialized;
	अचिन्हित दीर्घ vram_offset;
	अचिन्हित दीर्घ agp_offset;
	काष्ठा drm_mm vram_mm;
	काष्ठा drm_mm agp_mm;
	/** Mapping of userspace keys to mm objects */
	काष्ठा idr object_idr;
पूर्ण drm_sis_निजी_t;

काष्ठा sis_file_निजी अणु
	काष्ठा list_head obj_list;
पूर्ण;

बाह्य पूर्णांक sis_idle(काष्ठा drm_device *dev);
बाह्य व्योम sis_reclaim_buffers_locked(काष्ठा drm_device *dev,
				       काष्ठा drm_file *file_priv);
बाह्य व्योम sis_lastबंद(काष्ठा drm_device *dev);

बाह्य स्थिर काष्ठा drm_ioctl_desc sis_ioctls[];
बाह्य पूर्णांक sis_max_ioctl;

#पूर्ण_अगर
