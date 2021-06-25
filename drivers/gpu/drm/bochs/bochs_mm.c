<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 */

#समावेश "bochs.h"

/* ---------------------------------------------------------------------- */

पूर्णांक bochs_mm_init(काष्ठा bochs_device *bochs)
अणु
	काष्ठा drm_vram_mm *vmm;

	vmm = drm_vram_helper_alloc_mm(bochs->dev, bochs->fb_base,
				       bochs->fb_size);
	वापस PTR_ERR_OR_ZERO(vmm);
पूर्ण

व्योम bochs_mm_fini(काष्ठा bochs_device *bochs)
अणु
	अगर (!bochs->dev->vram_mm)
		वापस;

	drm_vram_helper_release_mm(bochs->dev);
पूर्ण
