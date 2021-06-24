<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright (C) 2016-2017 Oracle Corporation
 * This file is based on qxl_irq.c
 * Copyright 2013 Red Hat Inc.
 * Authors: Dave Airlie
 *          Alon Levy
 *          Michael Thayer <michael.thayer@oracle.com,
 *          Hans de Goede <hdegoede@redhat.com>
 */

#समावेश <linux/pci.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_probe_helper.h>

#समावेश "vbox_drv.h"
#समावेश "vboxvideo.h"

अटल व्योम vbox_clear_irq(व्योम)
अणु
	outl((u32)~0, VGA_PORT_HGSMI_HOST);
पूर्ण

अटल u32 vbox_get_flags(काष्ठा vbox_निजी *vbox)
अणु
	वापस पढ़ोl(vbox->guest_heap + HOST_FLAGS_OFFSET);
पूर्ण

व्योम vbox_report_hotplug(काष्ठा vbox_निजी *vbox)
अणु
	schedule_work(&vbox->hotplug_work);
पूर्ण

irqवापस_t vbox_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = (काष्ठा drm_device *)arg;
	काष्ठा vbox_निजी *vbox = to_vbox_dev(dev);
	u32 host_flags = vbox_get_flags(vbox);

	अगर (!(host_flags & HGSMIHOSTFLAGS_IRQ))
		वापस IRQ_NONE;

	/*
	 * Due to a bug in the initial host implementation of hot-plug irqs,
	 * the hot-plug and cursor capability flags were never cleared.
	 * Fortunately we can tell when they would have been set by checking
	 * that the VSYNC flag is not set.
	 */
	अगर (host_flags &
	    (HGSMIHOSTFLAGS_HOTPLUG | HGSMIHOSTFLAGS_CURSOR_CAPABILITIES) &&
	    !(host_flags & HGSMIHOSTFLAGS_VSYNC))
		vbox_report_hotplug(vbox);

	vbox_clear_irq();

	वापस IRQ_HANDLED;
पूर्ण

/*
 * Check that the position hपूर्णांकs provided by the host are suitable क्रम GNOME
 * shell (i.e. all screens disjoपूर्णांक and hपूर्णांकs क्रम all enabled screens) and अगर
 * not replace them with शेष ones.  Providing valid hपूर्णांकs improves the
 * chances that we will get a known screen layout क्रम poपूर्णांकer mapping.
 */
अटल व्योम validate_or_set_position_hपूर्णांकs(काष्ठा vbox_निजी *vbox)
अणु
	काष्ठा vbva_modehपूर्णांक *hपूर्णांकsi, *hपूर्णांकsj;
	bool valid = true;
	u16 currentx = 0;
	पूर्णांक i, j;

	क्रम (i = 0; i < vbox->num_crtcs; ++i) अणु
		क्रम (j = 0; j < i; ++j) अणु
			hपूर्णांकsi = &vbox->last_mode_hपूर्णांकs[i];
			hपूर्णांकsj = &vbox->last_mode_hपूर्णांकs[j];

			अगर (hपूर्णांकsi->enabled && hपूर्णांकsj->enabled) अणु
				अगर (hपूर्णांकsi->dx >= 0xffff ||
				    hपूर्णांकsi->dy >= 0xffff ||
				    hपूर्णांकsj->dx >= 0xffff ||
				    hपूर्णांकsj->dy >= 0xffff ||
				    (hपूर्णांकsi->dx <
					hपूर्णांकsj->dx + (hपूर्णांकsj->cx & 0x8fff) &&
				     hपूर्णांकsi->dx + (hपूर्णांकsi->cx & 0x8fff) >
					hपूर्णांकsj->dx) ||
				    (hपूर्णांकsi->dy <
					hपूर्णांकsj->dy + (hपूर्णांकsj->cy & 0x8fff) &&
				     hपूर्णांकsi->dy + (hपूर्णांकsi->cy & 0x8fff) >
					hपूर्णांकsj->dy))
					valid = false;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (!valid)
		क्रम (i = 0; i < vbox->num_crtcs; ++i) अणु
			अगर (vbox->last_mode_hपूर्णांकs[i].enabled) अणु
				vbox->last_mode_hपूर्णांकs[i].dx = currentx;
				vbox->last_mode_hपूर्णांकs[i].dy = 0;
				currentx +=
				    vbox->last_mode_hपूर्णांकs[i].cx & 0x8fff;
			पूर्ण
		पूर्ण
पूर्ण

/* Query the host क्रम the most recent video mode hपूर्णांकs. */
अटल व्योम vbox_update_mode_hपूर्णांकs(काष्ठा vbox_निजी *vbox)
अणु
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा drm_device *dev = &vbox->ddev;
	काष्ठा drm_connector *connector;
	काष्ठा vbox_connector *vbox_conn;
	काष्ठा vbva_modehपूर्णांक *hपूर्णांकs;
	u16 flags;
	bool disconnected;
	अचिन्हित पूर्णांक crtc_id;
	पूर्णांक ret;

	ret = hgsmi_get_mode_hपूर्णांकs(vbox->guest_pool, vbox->num_crtcs,
				   vbox->last_mode_hपूर्णांकs);
	अगर (ret) अणु
		DRM_ERROR("vboxvideo: hgsmi_get_mode_hints failed: %d\n", ret);
		वापस;
	पूर्ण

	validate_or_set_position_hपूर्णांकs(vbox);

	drm_modeset_lock(&dev->mode_config.connection_mutex, शून्य);
	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
		vbox_conn = to_vbox_connector(connector);

		hपूर्णांकs = &vbox->last_mode_hपूर्णांकs[vbox_conn->vbox_crtc->crtc_id];
		अगर (hपूर्णांकs->magic != VBVAMODEHINT_MAGIC)
			जारी;

		disconnected = !(hपूर्णांकs->enabled);
		crtc_id = vbox_conn->vbox_crtc->crtc_id;
		vbox_conn->mode_hपूर्णांक.width = hपूर्णांकs->cx;
		vbox_conn->mode_hपूर्णांक.height = hपूर्णांकs->cy;
		vbox_conn->vbox_crtc->x_hपूर्णांक = hपूर्णांकs->dx;
		vbox_conn->vbox_crtc->y_hपूर्णांक = hपूर्णांकs->dy;
		vbox_conn->mode_hपूर्णांक.disconnected = disconnected;

		अगर (vbox_conn->vbox_crtc->disconnected == disconnected)
			जारी;

		अगर (disconnected)
			flags = VBVA_SCREEN_F_ACTIVE | VBVA_SCREEN_F_DISABLED;
		अन्यथा
			flags = VBVA_SCREEN_F_ACTIVE | VBVA_SCREEN_F_BLANK;

		hgsmi_process_display_info(vbox->guest_pool, crtc_id, 0, 0, 0,
					   hपूर्णांकs->cx * 4, hपूर्णांकs->cx,
					   hपूर्णांकs->cy, 0, flags);

		vbox_conn->vbox_crtc->disconnected = disconnected;
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);
	drm_modeset_unlock(&dev->mode_config.connection_mutex);
पूर्ण

अटल व्योम vbox_hotplug_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vbox_निजी *vbox = container_of(work, काष्ठा vbox_निजी,
						 hotplug_work);

	vbox_update_mode_hपूर्णांकs(vbox);
	drm_kms_helper_hotplug_event(&vbox->ddev);
पूर्ण

पूर्णांक vbox_irq_init(काष्ठा vbox_निजी *vbox)
अणु
	काष्ठा pci_dev *pdev = to_pci_dev(vbox->ddev.dev);

	INIT_WORK(&vbox->hotplug_work, vbox_hotplug_worker);
	vbox_update_mode_hपूर्णांकs(vbox);

	वापस drm_irq_install(&vbox->ddev, pdev->irq);
पूर्ण

व्योम vbox_irq_fini(काष्ठा vbox_निजी *vbox)
अणु
	drm_irq_uninstall(&vbox->ddev);
	flush_work(&vbox->hotplug_work);
पूर्ण
