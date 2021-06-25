<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright (C) 2013-2017 Oracle Corporation
 * This file is based on ast_drv.h
 * Copyright 2012 Red Hat Inc.
 * Authors: Dave Airlie <airlied@redhat.com>
 *          Michael Thayer <michael.thayer@oracle.com,
 *          Hans de Goede <hdegoede@redhat.com>
 */
#अगर_अघोषित __VBOX_DRV_H__
#घोषणा __VBOX_DRV_H__

#समावेश <linux/genभाग.स>
#समावेश <linux/पन.स>
#समावेश <linux/irqवापस.h>
#समावेश <linux/माला.स>

#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_gem.h>
#समावेश <drm/drm_gem_vram_helper.h>

#समावेश "vboxvideo_guest.h"
#समावेश "vboxvideo_vbe.h"
#समावेश "hgsmi_ch_setup.h"

#घोषणा DRIVER_NAME         "vboxvideo"
#घोषणा DRIVER_DESC         "Oracle VM VirtualBox Graphics Card"
#घोषणा DRIVER_DATE         "20130823"

#घोषणा DRIVER_MAJOR        1
#घोषणा DRIVER_MINOR        0
#घोषणा DRIVER_PATCHLEVEL   0

#घोषणा VBOX_MAX_CURSOR_WIDTH  64
#घोषणा VBOX_MAX_CURSOR_HEIGHT 64
#घोषणा CURSOR_PIXEL_COUNT (VBOX_MAX_CURSOR_WIDTH * VBOX_MAX_CURSOR_HEIGHT)
#घोषणा CURSOR_DATA_SIZE (CURSOR_PIXEL_COUNT * 4 + CURSOR_PIXEL_COUNT / 8)

#घोषणा VBOX_MAX_SCREENS  32

#घोषणा GUEST_HEAP_OFFSET(vbox) ((vbox)->full_vram_size - \
				 VBVA_ADAPTER_INFORMATION_SIZE)
#घोषणा GUEST_HEAP_SIZE   VBVA_ADAPTER_INFORMATION_SIZE
#घोषणा GUEST_HEAP_USABLE_SIZE (VBVA_ADAPTER_INFORMATION_SIZE - \
				माप(काष्ठा hgsmi_host_flags))
#घोषणा HOST_FLAGS_OFFSET GUEST_HEAP_USABLE_SIZE

काष्ठा vbox_निजी अणु
	/* Must be first; or we must define our own release callback */
	काष्ठा drm_device ddev;

	u8 __iomem *guest_heap;
	u8 __iomem *vbva_buffers;
	काष्ठा gen_pool *guest_pool;
	काष्ठा vbva_buf_ctx *vbva_info;
	bool any_pitch;
	u32 num_crtcs;
	/* Amount of available VRAM, including space used क्रम buffers. */
	u32 full_vram_size;
	/* Amount of available VRAM, not including space used क्रम buffers. */
	u32 available_vram_size;
	/* Array of काष्ठाures क्रम receiving mode hपूर्णांकs. */
	काष्ठा vbva_modehपूर्णांक *last_mode_hपूर्णांकs;

	पूर्णांक fb_mtrr;

	काष्ठा mutex hw_mutex; /* protects modeset and accel/vbva accesses */
	काष्ठा work_काष्ठा hotplug_work;
	u32 input_mapping_width;
	u32 input_mapping_height;
	/*
	 * Is user-space using an X.Org-style layout of one large frame-buffer
	 * encompassing all screen ones or is the fbdev console active?
	 */
	bool single_framebuffer;
	u8 cursor_data[CURSOR_DATA_SIZE];
पूर्ण;

#अघोषित CURSOR_PIXEL_COUNT
#अघोषित CURSOR_DATA_SIZE

काष्ठा vbox_connector अणु
	काष्ठा drm_connector base;
	अक्षर name[32];
	काष्ठा vbox_crtc *vbox_crtc;
	काष्ठा अणु
		u32 width;
		u32 height;
		bool disconnected;
	पूर्ण mode_hपूर्णांक;
पूर्ण;

काष्ठा vbox_crtc अणु
	काष्ठा drm_crtc base;
	bool disconnected;
	अचिन्हित पूर्णांक crtc_id;
	u32 fb_offset;
	bool cursor_enabled;
	u32 x_hपूर्णांक;
	u32 y_hपूर्णांक;
	/*
	 * When setting a mode we not only pass the mode to the hypervisor,
	 * but also inक्रमmation on how to map / translate input coordinates
	 * क्रम the emulated USB tablet.  This input-mapping may change when
	 * the mode on *another* crtc changes.
	 *
	 * This means that someबार we must करो a modeset on other crtc-s then
	 * the one being changed to update the input-mapping. Including crtc-s
	 * which may be disabled inside the guest (shown as a black winकरोw
	 * on the host unless बंदd by the user).
	 *
	 * With atomic modesetting the mode-info of disabled crtcs माला_लो zeroed
	 * yet we need it when updating the input-map to aव्योम resizing the
	 * winकरोw as a side effect of a mode_set on another crtc. Thereक्रम we
	 * cache the info of the last mode below.
	 */
	u32 width;
	u32 height;
	u32 x;
	u32 y;
पूर्ण;

काष्ठा vbox_encoder अणु
	काष्ठा drm_encoder base;
पूर्ण;

#घोषणा to_vbox_crtc(x) container_of(x, काष्ठा vbox_crtc, base)
#घोषणा to_vbox_connector(x) container_of(x, काष्ठा vbox_connector, base)
#घोषणा to_vbox_encoder(x) container_of(x, काष्ठा vbox_encoder, base)
#घोषणा to_vbox_dev(x) container_of(x, काष्ठा vbox_निजी, ddev)

bool vbox_check_supported(u16 id);
पूर्णांक vbox_hw_init(काष्ठा vbox_निजी *vbox);
व्योम vbox_hw_fini(काष्ठा vbox_निजी *vbox);

पूर्णांक vbox_mode_init(काष्ठा vbox_निजी *vbox);
व्योम vbox_mode_fini(काष्ठा vbox_निजी *vbox);

व्योम vbox_report_caps(काष्ठा vbox_निजी *vbox);

पूर्णांक vbox_mm_init(काष्ठा vbox_निजी *vbox);
व्योम vbox_mm_fini(काष्ठा vbox_निजी *vbox);

/* vbox_irq.c */
पूर्णांक vbox_irq_init(काष्ठा vbox_निजी *vbox);
व्योम vbox_irq_fini(काष्ठा vbox_निजी *vbox);
व्योम vbox_report_hotplug(काष्ठा vbox_निजी *vbox);
irqवापस_t vbox_irq_handler(पूर्णांक irq, व्योम *arg);

/* vbox_hgsmi.c */
व्योम *hgsmi_buffer_alloc(काष्ठा gen_pool *guest_pool, माप_प्रकार size,
			 u8 channel, u16 channel_info);
व्योम hgsmi_buffer_मुक्त(काष्ठा gen_pool *guest_pool, व्योम *buf);
पूर्णांक hgsmi_buffer_submit(काष्ठा gen_pool *guest_pool, व्योम *buf);

अटल अंतरभूत व्योम vbox_ग_लिखो_ioport(u16 index, u16 data)
अणु
	outw(index, VBE_DISPI_IOPORT_INDEX);
	outw(data, VBE_DISPI_IOPORT_DATA);
पूर्ण

#पूर्ण_अगर
