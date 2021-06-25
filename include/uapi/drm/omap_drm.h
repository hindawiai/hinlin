<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * include/uapi/drm/omap_drm.h
 *
 * Copyright (C) 2011 Texas Instruments
 * Author: Rob Clark <rob@ti.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published by
 * the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 *
 * You should have received a copy of the GNU General Public License aदीर्घ with
 * this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#अगर_अघोषित __OMAP_DRM_H__
#घोषणा __OMAP_DRM_H__

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

/* Please note that modअगरications to all काष्ठाs defined here are
 * subject to backwards-compatibility स्थिरraपूर्णांकs.
 */

#घोषणा OMAP_PARAM_CHIPSET_ID	1	/* ie. 0x3430, 0x4430, etc */

काष्ठा drm_omap_param अणु
	__u64 param;			/* in */
	__u64 value;			/* in (set_param), out (get_param) */
पूर्ण;

/* Scanout buffer, consumable by DSS */
#घोषणा OMAP_BO_SCANOUT		0x00000001

/* Buffer CPU caching mode: cached, ग_लिखो-combining or uncached. */
#घोषणा OMAP_BO_CACHED		0x00000000
#घोषणा OMAP_BO_WC		0x00000002
#घोषणा OMAP_BO_UNCACHED	0x00000004
#घोषणा OMAP_BO_CACHE_MASK	0x00000006

/* Use TILER क्रम the buffer. The TILER container unit can be 8, 16 or 32 bits. */
#घोषणा OMAP_BO_TILED_8		0x00000100
#घोषणा OMAP_BO_TILED_16	0x00000200
#घोषणा OMAP_BO_TILED_32	0x00000300
#घोषणा OMAP_BO_TILED_MASK	0x00000f00

जोड़ omap_gem_size अणु
	__u32 bytes;		/* (क्रम non-tiled क्रमmats) */
	काष्ठा अणु
		__u16 width;
		__u16 height;
	पूर्ण tiled;		/* (क्रम tiled क्रमmats) */
पूर्ण;

काष्ठा drm_omap_gem_new अणु
	जोड़ omap_gem_size size;	/* in */
	__u32 flags;			/* in */
	__u32 handle;			/* out */
	__u32 __pad;
पूर्ण;

/* mask of operations: */
क्रमागत omap_gem_op अणु
	OMAP_GEM_READ = 0x01,
	OMAP_GEM_WRITE = 0x02,
पूर्ण;

काष्ठा drm_omap_gem_cpu_prep अणु
	__u32 handle;			/* buffer handle (in) */
	__u32 op;			/* mask of omap_gem_op (in) */
पूर्ण;

काष्ठा drm_omap_gem_cpu_fini अणु
	__u32 handle;			/* buffer handle (in) */
	__u32 op;			/* mask of omap_gem_op (in) */
	/* TODO maybe here we pass करोwn info about what regions are touched
	 * by sw so we can be clever about cache ops?  For now a placeholder,
	 * set to zero and we just करो full buffer flush..
	 */
	__u32 nregions;
	__u32 __pad;
पूर्ण;

काष्ठा drm_omap_gem_info अणु
	__u32 handle;			/* buffer handle (in) */
	__u32 pad;
	__u64 offset;			/* mmap offset (out) */
	/* note: in हाल of tiled buffers, the user भव size can be
	 * dअगरferent from the physical size (ie. how many pages are needed
	 * to back the object) which is वापसed in DRM_IOCTL_GEM_OPEN..
	 * This size here is the one that should be used अगर you want to
	 * mmap() the buffer:
	 */
	__u32 size;			/* भव size क्रम mmap'ing (out) */
	__u32 __pad;
पूर्ण;

#घोषणा DRM_OMAP_GET_PARAM		0x00
#घोषणा DRM_OMAP_SET_PARAM		0x01
#घोषणा DRM_OMAP_GEM_NEW		0x03
#घोषणा DRM_OMAP_GEM_CPU_PREP		0x04	/* Deprecated, to be हटाओd */
#घोषणा DRM_OMAP_GEM_CPU_FINI		0x05	/* Deprecated, to be हटाओd */
#घोषणा DRM_OMAP_GEM_INFO		0x06
#घोषणा DRM_OMAP_NUM_IOCTLS		0x07

#घोषणा DRM_IOCTL_OMAP_GET_PARAM	DRM_IOWR(DRM_COMMAND_BASE + DRM_OMAP_GET_PARAM, काष्ठा drm_omap_param)
#घोषणा DRM_IOCTL_OMAP_SET_PARAM	DRM_IOW (DRM_COMMAND_BASE + DRM_OMAP_SET_PARAM, काष्ठा drm_omap_param)
#घोषणा DRM_IOCTL_OMAP_GEM_NEW		DRM_IOWR(DRM_COMMAND_BASE + DRM_OMAP_GEM_NEW, काष्ठा drm_omap_gem_new)
#घोषणा DRM_IOCTL_OMAP_GEM_CPU_PREP	DRM_IOW (DRM_COMMAND_BASE + DRM_OMAP_GEM_CPU_PREP, काष्ठा drm_omap_gem_cpu_prep)
#घोषणा DRM_IOCTL_OMAP_GEM_CPU_FINI	DRM_IOW (DRM_COMMAND_BASE + DRM_OMAP_GEM_CPU_FINI, काष्ठा drm_omap_gem_cpu_fini)
#घोषणा DRM_IOCTL_OMAP_GEM_INFO		DRM_IOWR(DRM_COMMAND_BASE + DRM_OMAP_GEM_INFO, काष्ठा drm_omap_gem_info)

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __OMAP_DRM_H__ */
