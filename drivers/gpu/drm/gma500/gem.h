<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/**************************************************************************
 * Copyright (c) 2014 Patrik Jakobsson
 * All Rights Reserved.
 *
 **************************************************************************/

#अगर_अघोषित _GEM_H
#घोषणा _GEM_H

काष्ठा drm_device;

बाह्य स्थिर काष्ठा drm_gem_object_funcs psb_gem_object_funcs;

बाह्य पूर्णांक psb_gem_create(काष्ठा drm_file *file, काष्ठा drm_device *dev,
			  u64 size, u32 *handlep, पूर्णांक stolen, u32 align);

#पूर्ण_अगर
