<शैली गुरु>
/* radeon_drv.h -- Private header क्रम radeon driver -*- linux-c -*-
 *
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Fremont, Calअगरornia.
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
 * Authors:
 *    Kevin E. Martin <martin@valinux.com>
 *    Gareth Hughes <gareth@valinux.com>
 */

#अगर_अघोषित __RADEON_DRV_H__
#घोषणा __RADEON_DRV_H__

#समावेश <linux/firmware.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <drm/drm_legacy.h>

#समावेश "radeon_family.h"

/* General customization:
 */

#घोषणा DRIVER_AUTHOR		"Gareth Hughes, Keith Whitwell, others."

#घोषणा DRIVER_NAME		"radeon"
#घोषणा DRIVER_DESC		"ATI Radeon"
#घोषणा DRIVER_DATE		"20080528"

/* Interface history:
 *
 * 1.1 - ??
 * 1.2 - Add vertex2 ioctl (keith)
 *     - Add stencil capability to clear ioctl (gareth, keith)
 *     - Increase MAX_TEXTURE_LEVELS (brian)
 * 1.3 - Add cmdbuf ioctl (keith)
 *     - Add support क्रम new radeon packets (keith)
 *     - Add getparam ioctl (keith)
 *     - Add flip-buffers ioctl, deprecate fullscreen foo (keith).
 * 1.4 - Add scratch रेजिस्टरs to get_param ioctl.
 * 1.5 - Add r200 packets to cmdbuf ioctl
 *     - Add r200 function to init ioctl
 *     - Add 'scalar2' inकाष्ठाion to cmdbuf
 * 1.6 - Add अटल GART memory manager
 *       Add irq handler (won't be turned on unless X server knows to)
 *       Add irq ioctls and irq_active getparam.
 *       Add रुको command क्रम cmdbuf ioctl
 *       Add GART offset query क्रम getparam
 * 1.7 - Add support क्रम cube map रेजिस्टरs: R200_PP_CUBIC_FACES_[0..5]
 *       and R200_PP_CUBIC_OFFSET_F1_[0..5].
 *       Added packets R200_EMIT_PP_CUBIC_FACES_[0..5] and
 *       R200_EMIT_PP_CUBIC_OFFSETS_[0..5].  (brian)
 * 1.8 - Remove need to call cleanup ioctls on last client निकास (keith)
 *       Add 'GET' queries for starting additional clients on different VT's.
 * 1.9 - Add DRM_IOCTL_RADEON_CP_RESUME ioctl.
 *       Add texture rectangle support क्रम r100.
 * 1.10- Add SETPARAM ioctl; first parameter to set is FB_LOCATION, which
 *       clients use to tell the DRM where they think the framebuffer is
 *       located in the card's address space
 * 1.11- Add packet R200_EMIT_RB3D_BLENDCOLOR to support GL_EXT_blend_color
 *       and GL_EXT_blend_[func|equation]_separate on r200
 * 1.12- Add R300 CP microcode support - this just loads the CP on r300
 *       (No 3D support yet - just microcode loading).
 * 1.13- Add packet R200_EMIT_TCL_POINT_SPRITE_CNTL क्रम ARB_poपूर्णांक_parameters
 *     - Add hyperz support, add hyperz flags to clear ioctl.
 * 1.14- Add support क्रम color tiling
 *     - Add R100/R200 surface allocation/मुक्त support
 * 1.15- Add support क्रम texture micro tiling
 *     - Add support क्रम r100 cube maps
 * 1.16- Add R200_EMIT_PP_TRI_PERF_CNTL packet to support brilinear
 *       texture filtering on r200
 * 1.17- Add initial support क्रम R300 (3D).
 * 1.18- Add support क्रम GL_ATI_fragment_shader, new packets
 *       R200_EMIT_PP_AFS_0/1, R200_EMIT_PP_TXCTLALL_0-5 (replaces
 *       R200_EMIT_PP_TXFILTER_0-5, 2 more regs) and R200_EMIT_ATF_TFACTOR
 *       (replaces R200_EMIT_TFACTOR_0 (8 स्थिरs instead of 6)
 * 1.19- Add support क्रम gart table in FB memory and PCIE r300
 * 1.20- Add support क्रम r300 texrect
 * 1.21- Add support क्रम card type getparam
 * 1.22- Add support क्रम texture cache flushes (R300_TX_CNTL)
 * 1.23- Add new radeon memory map work from benh
 * 1.24- Add general-purpose packet क्रम manipulating scratch रेजिस्टरs (r300)
 * 1.25- Add support क्रम r200 vertex programs (R200_EMIT_VAP_PVS_CNTL,
 *       new packet type)
 * 1.26- Add support क्रम variable size PCI(E) gart aperture
 * 1.27- Add support क्रम IGP GART
 * 1.28- Add support क्रम VBL on CRTC2
 * 1.29- R500 3D cmd buffer support
 * 1.30- Add support क्रम occlusion queries
 * 1.31- Add support क्रम num Z pipes from GET_PARAM
 * 1.32- fixes क्रम rv740 setup
 * 1.33- Add r6xx/r7xx स्थिर buffer support
 * 1.34- fix evergreen/cayman GS रेजिस्टर
 */
#घोषणा DRIVER_MAJOR		1
#घोषणा DRIVER_MINOR		34
#घोषणा DRIVER_PATCHLEVEL	0

दीर्घ radeon_drm_ioctl(काष्ठा file *filp,
		      अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg);

पूर्णांक radeon_driver_load_kms(काष्ठा drm_device *dev, अचिन्हित दीर्घ flags);
व्योम radeon_driver_unload_kms(काष्ठा drm_device *dev);
व्योम radeon_driver_lastबंद_kms(काष्ठा drm_device *dev);
पूर्णांक radeon_driver_खोलो_kms(काष्ठा drm_device *dev, काष्ठा drm_file *file_priv);
व्योम radeon_driver_postबंद_kms(काष्ठा drm_device *dev,
				 काष्ठा drm_file *file_priv);

#पूर्ण_अगर				/* __RADEON_DRV_H__ */
