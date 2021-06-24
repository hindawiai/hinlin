<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright (C) 2013-2017 Oracle Corporation
 * This file is based on ast_मुख्य.c
 * Copyright 2012 Red Hat Inc.
 * Authors: Dave Airlie <airlied@redhat.com>,
 *          Michael Thayer <michael.thayer@oracle.com,
 *          Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/pci.h>
#समावेश <linux/vbox_err.h>

#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_crtc_helper.h>
#समावेश <drm/drm_damage_helper.h>

#समावेश "vbox_drv.h"
#समावेश "vboxvideo_guest.h"
#समावेश "vboxvideo_vbe.h"

व्योम vbox_report_caps(काष्ठा vbox_निजी *vbox)
अणु
	u32 caps = VBVACAPS_DISABLE_CURSOR_INTEGRATION |
		   VBVACAPS_IRQ | VBVACAPS_USE_VBVA_ONLY;

	/* The host only accepts VIDEO_MODE_HINTS अगर it is send separately. */
	hgsmi_send_caps_info(vbox->guest_pool, caps);
	caps |= VBVACAPS_VIDEO_MODE_HINTS;
	hgsmi_send_caps_info(vbox->guest_pool, caps);
पूर्ण

अटल पूर्णांक vbox_accel_init(काष्ठा vbox_निजी *vbox)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(vbox->ddev.dev);
	काष्ठा vbva_buffer *vbva;
	अचिन्हित पूर्णांक i;

	vbox->vbva_info = devm_kसुस्मृति(vbox->ddev.dev, vbox->num_crtcs,
				       माप(*vbox->vbva_info), GFP_KERNEL);
	अगर (!vbox->vbva_info)
		वापस -ENOMEM;

	/* Take a command buffer क्रम each screen from the end of usable VRAM. */
	vbox->available_vram_size -= vbox->num_crtcs * VBVA_MIN_BUFFER_SIZE;

	vbox->vbva_buffers = pci_iomap_range(pdev, 0,
					     vbox->available_vram_size,
					     vbox->num_crtcs *
					     VBVA_MIN_BUFFER_SIZE);
	अगर (!vbox->vbva_buffers)
		वापस -ENOMEM;

	क्रम (i = 0; i < vbox->num_crtcs; ++i) अणु
		vbva_setup_buffer_context(&vbox->vbva_info[i],
					  vbox->available_vram_size +
					  i * VBVA_MIN_BUFFER_SIZE,
					  VBVA_MIN_BUFFER_SIZE);
		vbva = (व्योम __क्रमce *)vbox->vbva_buffers +
			i * VBVA_MIN_BUFFER_SIZE;
		अगर (!vbva_enable(&vbox->vbva_info[i],
				 vbox->guest_pool, vbva, i)) अणु
			/* very old host or driver error. */
			DRM_ERROR("vboxvideo: vbva_enable failed\n");
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vbox_accel_fini(काष्ठा vbox_निजी *vbox)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < vbox->num_crtcs; ++i)
		vbva_disable(&vbox->vbva_info[i], vbox->guest_pool, i);
पूर्ण

/* Do we support the 4.3 plus mode hपूर्णांक reporting पूर्णांकerface? */
अटल bool have_hgsmi_mode_hपूर्णांकs(काष्ठा vbox_निजी *vbox)
अणु
	u32 have_hपूर्णांकs, have_cursor;
	पूर्णांक ret;

	ret = hgsmi_query_conf(vbox->guest_pool,
			       VBOX_VBVA_CONF32_MODE_HINT_REPORTING,
			       &have_hपूर्णांकs);
	अगर (ret)
		वापस false;

	ret = hgsmi_query_conf(vbox->guest_pool,
			       VBOX_VBVA_CONF32_GUEST_CURSOR_REPORTING,
			       &have_cursor);
	अगर (ret)
		वापस false;

	वापस have_hपूर्णांकs == VINF_SUCCESS && have_cursor == VINF_SUCCESS;
पूर्ण

bool vbox_check_supported(u16 id)
अणु
	u16 dispi_id;

	vbox_ग_लिखो_ioport(VBE_DISPI_INDEX_ID, id);
	dispi_id = inw(VBE_DISPI_IOPORT_DATA);

	वापस dispi_id == id;
पूर्ण

पूर्णांक vbox_hw_init(काष्ठा vbox_निजी *vbox)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(vbox->ddev.dev);
	पूर्णांक ret = -ENOMEM;

	vbox->full_vram_size = inl(VBE_DISPI_IOPORT_DATA);
	vbox->any_pitch = vbox_check_supported(VBE_DISPI_ID_ANYX);

	DRM_INFO("VRAM %08x\n", vbox->full_vram_size);

	/* Map guest-heap at end of vram */
	vbox->guest_heap =
	    pci_iomap_range(pdev, 0, GUEST_HEAP_OFFSET(vbox),
			    GUEST_HEAP_SIZE);
	अगर (!vbox->guest_heap)
		वापस -ENOMEM;

	/* Create guest-heap mem-pool use 2^4 = 16 byte chunks */
	vbox->guest_pool = devm_gen_pool_create(vbox->ddev.dev, 4, -1,
						"vboxvideo-accel");
	अगर (!vbox->guest_pool)
		वापस -ENOMEM;

	ret = gen_pool_add_virt(vbox->guest_pool,
				(अचिन्हित दीर्घ)vbox->guest_heap,
				GUEST_HEAP_OFFSET(vbox),
				GUEST_HEAP_USABLE_SIZE, -1);
	अगर (ret)
		वापस ret;

	ret = hgsmi_test_query_conf(vbox->guest_pool);
	अगर (ret) अणु
		DRM_ERROR("vboxvideo: hgsmi_test_query_conf failed\n");
		वापस ret;
	पूर्ण

	/* Reduce available VRAM size to reflect the guest heap. */
	vbox->available_vram_size = GUEST_HEAP_OFFSET(vbox);
	/* Linux drm represents monitors as a 32-bit array. */
	hgsmi_query_conf(vbox->guest_pool, VBOX_VBVA_CONF32_MONITOR_COUNT,
			 &vbox->num_crtcs);
	vbox->num_crtcs = clamp_t(u32, vbox->num_crtcs, 1, VBOX_MAX_SCREENS);

	अगर (!have_hgsmi_mode_hपूर्णांकs(vbox)) अणु
		ret = -ENOTSUPP;
		वापस ret;
	पूर्ण

	vbox->last_mode_hपूर्णांकs = devm_kसुस्मृति(vbox->ddev.dev, vbox->num_crtcs,
					     माप(काष्ठा vbva_modehपूर्णांक),
					     GFP_KERNEL);
	अगर (!vbox->last_mode_hपूर्णांकs)
		वापस -ENOMEM;

	ret = vbox_accel_init(vbox);
	अगर (ret)
		वापस ret;

	वापस 0;
पूर्ण

व्योम vbox_hw_fini(काष्ठा vbox_निजी *vbox)
अणु
	vbox_accel_fini(vbox);
पूर्ण
