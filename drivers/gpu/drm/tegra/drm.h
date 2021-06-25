<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Avionic Design GmbH
 * Copyright (C) 2012-2013 NVIDIA CORPORATION.  All rights reserved.
 */

#अगर_अघोषित HOST1X_DRM_H
#घोषणा HOST1X_DRM_H 1

#समावेश <linux/host1x.h>
#समावेश <linux/iova.h>
#समावेश <linux/gpio/consumer.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_bridge.h>
#समावेश <drm/drm_edid.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_fixed.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <uapi/drm/tegra_drm.h>

#समावेश "gem.h"
#समावेश "hub.h"
#समावेश "trace.h"

/* XXX move to include/uapi/drm/drm_fourcc.h? */
#घोषणा DRM_FORMAT_MOD_NVIDIA_SECTOR_LAYOUT BIT_ULL(22)

काष्ठा reset_control;

#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
काष्ठा tegra_fbdev अणु
	काष्ठा drm_fb_helper base;
	काष्ठा drm_framebuffer *fb;
पूर्ण;
#पूर्ण_अगर

काष्ठा tegra_drm अणु
	काष्ठा drm_device *drm;

	काष्ठा iommu_करोमुख्य *करोमुख्य;
	bool use_explicit_iommu;
	काष्ठा mutex mm_lock;
	काष्ठा drm_mm mm;

	काष्ठा अणु
		काष्ठा iova_करोमुख्य करोमुख्य;
		अचिन्हित दीर्घ shअगरt;
		अचिन्हित दीर्घ limit;
	पूर्ण carveout;

	काष्ठा mutex clients_lock;
	काष्ठा list_head clients;

#अगर_घोषित CONFIG_DRM_FBDEV_EMULATION
	काष्ठा tegra_fbdev *fbdev;
#पूर्ण_अगर

	अचिन्हित पूर्णांक hmask, vmask;
	अचिन्हित पूर्णांक pitch_align;
	अचिन्हित पूर्णांक num_crtcs;

	काष्ठा tegra_display_hub *hub;
पूर्ण;

काष्ठा tegra_drm_client;

काष्ठा tegra_drm_context अणु
	काष्ठा tegra_drm_client *client;
	काष्ठा host1x_channel *channel;
	अचिन्हित पूर्णांक id;
पूर्ण;

काष्ठा tegra_drm_client_ops अणु
	पूर्णांक (*खोलो_channel)(काष्ठा tegra_drm_client *client,
			    काष्ठा tegra_drm_context *context);
	व्योम (*बंद_channel)(काष्ठा tegra_drm_context *context);
	पूर्णांक (*is_addr_reg)(काष्ठा device *dev, u32 class, u32 offset);
	पूर्णांक (*is_valid_class)(u32 class);
	पूर्णांक (*submit)(काष्ठा tegra_drm_context *context,
		      काष्ठा drm_tegra_submit *args, काष्ठा drm_device *drm,
		      काष्ठा drm_file *file);
पूर्ण;

पूर्णांक tegra_drm_submit(काष्ठा tegra_drm_context *context,
		     काष्ठा drm_tegra_submit *args, काष्ठा drm_device *drm,
		     काष्ठा drm_file *file);

काष्ठा tegra_drm_client अणु
	काष्ठा host1x_client base;
	काष्ठा list_head list;
	काष्ठा tegra_drm *drm;

	अचिन्हित पूर्णांक version;
	स्थिर काष्ठा tegra_drm_client_ops *ops;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_drm_client *
host1x_to_drm_client(काष्ठा host1x_client *client)
अणु
	वापस container_of(client, काष्ठा tegra_drm_client, base);
पूर्ण

पूर्णांक tegra_drm_रेजिस्टर_client(काष्ठा tegra_drm *tegra,
			      काष्ठा tegra_drm_client *client);
पूर्णांक tegra_drm_unरेजिस्टर_client(काष्ठा tegra_drm *tegra,
				काष्ठा tegra_drm_client *client);
पूर्णांक host1x_client_iommu_attach(काष्ठा host1x_client *client);
व्योम host1x_client_iommu_detach(काष्ठा host1x_client *client);

पूर्णांक tegra_drm_init(काष्ठा tegra_drm *tegra, काष्ठा drm_device *drm);
पूर्णांक tegra_drm_निकास(काष्ठा tegra_drm *tegra);

व्योम *tegra_drm_alloc(काष्ठा tegra_drm *tegra, माप_प्रकार size, dma_addr_t *iova);
व्योम tegra_drm_मुक्त(काष्ठा tegra_drm *tegra, माप_प्रकार size, व्योम *virt,
		    dma_addr_t iova);

काष्ठा cec_notअगरier;

काष्ठा tegra_output अणु
	काष्ठा device_node *of_node;
	काष्ठा device *dev;

	काष्ठा drm_bridge *bridge;
	काष्ठा drm_panel *panel;
	काष्ठा i2c_adapter *ddc;
	स्थिर काष्ठा edid *edid;
	काष्ठा cec_notअगरier *cec;
	अचिन्हित पूर्णांक hpd_irq;
	काष्ठा gpio_desc *hpd_gpio;

	काष्ठा drm_encoder encoder;
	काष्ठा drm_connector connector;
पूर्ण;

अटल अंतरभूत काष्ठा tegra_output *encoder_to_output(काष्ठा drm_encoder *e)
अणु
	वापस container_of(e, काष्ठा tegra_output, encoder);
पूर्ण

अटल अंतरभूत काष्ठा tegra_output *connector_to_output(काष्ठा drm_connector *c)
अणु
	वापस container_of(c, काष्ठा tegra_output, connector);
पूर्ण

/* from output.c */
पूर्णांक tegra_output_probe(काष्ठा tegra_output *output);
व्योम tegra_output_हटाओ(काष्ठा tegra_output *output);
पूर्णांक tegra_output_init(काष्ठा drm_device *drm, काष्ठा tegra_output *output);
व्योम tegra_output_निकास(काष्ठा tegra_output *output);
व्योम tegra_output_find_possible_crtcs(काष्ठा tegra_output *output,
				      काष्ठा drm_device *drm);
पूर्णांक tegra_output_suspend(काष्ठा tegra_output *output);
पूर्णांक tegra_output_resume(काष्ठा tegra_output *output);

पूर्णांक tegra_output_connector_get_modes(काष्ठा drm_connector *connector);
क्रमागत drm_connector_status
tegra_output_connector_detect(काष्ठा drm_connector *connector, bool क्रमce);
व्योम tegra_output_connector_destroy(काष्ठा drm_connector *connector);

/* from dpaux.c */
काष्ठा drm_dp_aux *drm_dp_aux_find_by_of_node(काष्ठा device_node *np);
क्रमागत drm_connector_status drm_dp_aux_detect(काष्ठा drm_dp_aux *aux);
पूर्णांक drm_dp_aux_attach(काष्ठा drm_dp_aux *aux, काष्ठा tegra_output *output);
पूर्णांक drm_dp_aux_detach(काष्ठा drm_dp_aux *aux);
पूर्णांक drm_dp_aux_enable(काष्ठा drm_dp_aux *aux);
पूर्णांक drm_dp_aux_disable(काष्ठा drm_dp_aux *aux);

/* from fb.c */
काष्ठा tegra_bo *tegra_fb_get_plane(काष्ठा drm_framebuffer *framebuffer,
				    अचिन्हित पूर्णांक index);
bool tegra_fb_is_bottom_up(काष्ठा drm_framebuffer *framebuffer);
पूर्णांक tegra_fb_get_tiling(काष्ठा drm_framebuffer *framebuffer,
			काष्ठा tegra_bo_tiling *tiling);
काष्ठा drm_framebuffer *tegra_fb_create(काष्ठा drm_device *drm,
					काष्ठा drm_file *file,
					स्थिर काष्ठा drm_mode_fb_cmd2 *cmd);
पूर्णांक tegra_drm_fb_prepare(काष्ठा drm_device *drm);
व्योम tegra_drm_fb_मुक्त(काष्ठा drm_device *drm);
पूर्णांक tegra_drm_fb_init(काष्ठा drm_device *drm);
व्योम tegra_drm_fb_निकास(काष्ठा drm_device *drm);

बाह्य काष्ठा platक्रमm_driver tegra_display_hub_driver;
बाह्य काष्ठा platक्रमm_driver tegra_dc_driver;
बाह्य काष्ठा platक्रमm_driver tegra_hdmi_driver;
बाह्य काष्ठा platक्रमm_driver tegra_dsi_driver;
बाह्य काष्ठा platक्रमm_driver tegra_dpaux_driver;
बाह्य काष्ठा platक्रमm_driver tegra_sor_driver;
बाह्य काष्ठा platक्रमm_driver tegra_gr2d_driver;
बाह्य काष्ठा platक्रमm_driver tegra_gr3d_driver;
बाह्य काष्ठा platक्रमm_driver tegra_vic_driver;

#पूर्ण_अगर /* HOST1X_DRM_H */
