<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/**************************************************************************
 * Copyright (c) 2007-2008, Intel Corporation.
 * All Rights Reserved.
 *
 **************************************************************************/

#अगर_अघोषित _PSB_GTT_H_
#घोषणा _PSB_GTT_H_

#समावेश <drm/drm_gem.h>

/* This wants cleaning up with respect to the psb_dev and un-needed stuff */
काष्ठा psb_gtt अणु
	uपूर्णांक32_t gatt_start;
	uपूर्णांक32_t mmu_gatt_start;
	uपूर्णांक32_t gtt_start;
	uपूर्णांक32_t gtt_phys_start;
	अचिन्हित gtt_pages;
	अचिन्हित gatt_pages;
	अचिन्हित दीर्घ stolen_size;
	अचिन्हित दीर्घ vram_stolen_size;
	काष्ठा rw_semaphore sem;
पूर्ण;

/* Exported functions */
बाह्य पूर्णांक psb_gtt_init(काष्ठा drm_device *dev, पूर्णांक resume);
बाह्य व्योम psb_gtt_takeकरोwn(काष्ठा drm_device *dev);

/* Each gtt_range describes an allocation in the GTT area */
काष्ठा gtt_range अणु
	काष्ठा resource resource;	/* Resource क्रम our allocation */
	u32 offset;			/* GTT offset of our object */
	काष्ठा drm_gem_object gem;	/* GEM high level stuff */
	पूर्णांक in_gart;			/* Currently in the GART (ref ct) */
	bool stolen;			/* Backed from stolen RAM */
	bool mmapping;			/* Is mmappable */
	काष्ठा page **pages;		/* Backing pages अगर present */
	पूर्णांक npage;			/* Number of backing pages */
पूर्ण;

#घोषणा to_gtt_range(x) container_of(x, काष्ठा gtt_range, gem)

बाह्य काष्ठा gtt_range *psb_gtt_alloc_range(काष्ठा drm_device *dev, पूर्णांक len,
					     स्थिर अक्षर *name, पूर्णांक backed,
					     u32 align);
बाह्य व्योम psb_gtt_kref_put(काष्ठा gtt_range *gt);
बाह्य व्योम psb_gtt_मुक्त_range(काष्ठा drm_device *dev, काष्ठा gtt_range *gt);
बाह्य पूर्णांक psb_gtt_pin(काष्ठा gtt_range *gt);
बाह्य व्योम psb_gtt_unpin(काष्ठा gtt_range *gt);
बाह्य पूर्णांक psb_gtt_restore(काष्ठा drm_device *dev);
#पूर्ण_अगर
