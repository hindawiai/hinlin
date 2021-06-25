<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Copyright (C) 2012 Russell King
 *  With inspiration from the i915 driver
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#अगर_अघोषित DRM_ARMADA_IOCTL_H
#घोषणा DRM_ARMADA_IOCTL_H

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

#घोषणा DRM_ARMADA_GEM_CREATE		0x00
#घोषणा DRM_ARMADA_GEM_MMAP		0x02
#घोषणा DRM_ARMADA_GEM_PWRITE		0x03

#घोषणा ARMADA_IOCTL(dir, name, str) \
	DRM_##dir(DRM_COMMAND_BASE + DRM_ARMADA_##name, काष्ठा drm_armada_##str)

काष्ठा drm_armada_gem_create अणु
	__u32 handle;
	__u32 size;
पूर्ण;
#घोषणा DRM_IOCTL_ARMADA_GEM_CREATE \
	ARMADA_IOCTL(IOWR, GEM_CREATE, gem_create)

काष्ठा drm_armada_gem_mmap अणु
	__u32 handle;
	__u32 pad;
	__u64 offset;
	__u64 size;
	__u64 addr;
पूर्ण;
#घोषणा DRM_IOCTL_ARMADA_GEM_MMAP \
	ARMADA_IOCTL(IOWR, GEM_MMAP, gem_mmap)

काष्ठा drm_armada_gem_pग_लिखो अणु
	__u64 ptr;
	__u32 handle;
	__u32 offset;
	__u32 size;
पूर्ण;
#घोषणा DRM_IOCTL_ARMADA_GEM_PWRITE \
	ARMADA_IOCTL(IOW, GEM_PWRITE, gem_pग_लिखो)

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
