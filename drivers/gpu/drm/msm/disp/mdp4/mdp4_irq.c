<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_vblank.h>

#समावेश "msm_drv.h"
#समावेश "mdp4_kms.h"

व्योम mdp4_set_irqmask(काष्ठा mdp_kms *mdp_kms, uपूर्णांक32_t irqmask,
		uपूर्णांक32_t old_irqmask)
अणु
	mdp4_ग_लिखो(to_mdp4_kms(mdp_kms), REG_MDP4_INTR_CLEAR,
		irqmask ^ (irqmask & old_irqmask));
	mdp4_ग_लिखो(to_mdp4_kms(mdp_kms), REG_MDP4_INTR_ENABLE, irqmask);
पूर्ण

अटल व्योम mdp4_irq_error_handler(काष्ठा mdp_irq *irq, uपूर्णांक32_t irqstatus)
अणु
	काष्ठा mdp4_kms *mdp4_kms = container_of(irq, काष्ठा mdp4_kms, error_handler);
	अटल DEFINE_RATELIMIT_STATE(rs, 5*HZ, 1);
	बाह्य bool dumpstate;

	DRM_ERROR_RATELIMITED("errors: %08x\n", irqstatus);

	अगर (dumpstate && __ratelimit(&rs)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(mdp4_kms->dev->dev);
		drm_state_dump(mdp4_kms->dev, &p);
	पूर्ण
पूर्ण

व्योम mdp4_irq_preinstall(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	mdp4_enable(mdp4_kms);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_INTR_CLEAR, 0xffffffff);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_INTR_ENABLE, 0x00000000);
	mdp4_disable(mdp4_kms);
पूर्ण

पूर्णांक mdp4_irq_postinstall(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp_kms *mdp_kms = to_mdp_kms(kms);
	काष्ठा mdp4_kms *mdp4_kms = to_mdp4_kms(mdp_kms);
	काष्ठा mdp_irq *error_handler = &mdp4_kms->error_handler;

	error_handler->irq = mdp4_irq_error_handler;
	error_handler->irqmask = MDP4_IRQ_PRIMARY_INTF_UDERRUN |
			MDP4_IRQ_EXTERNAL_INTF_UDERRUN;

	mdp_irq_रेजिस्टर(mdp_kms, error_handler);

	वापस 0;
पूर्ण

व्योम mdp4_irq_uninstall(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));
	mdp4_enable(mdp4_kms);
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_INTR_ENABLE, 0x00000000);
	mdp4_disable(mdp4_kms);
पूर्ण

irqवापस_t mdp4_irq(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp_kms *mdp_kms = to_mdp_kms(kms);
	काष्ठा mdp4_kms *mdp4_kms = to_mdp4_kms(mdp_kms);
	काष्ठा drm_device *dev = mdp4_kms->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	अचिन्हित पूर्णांक id;
	uपूर्णांक32_t status, enable;

	enable = mdp4_पढ़ो(mdp4_kms, REG_MDP4_INTR_ENABLE);
	status = mdp4_पढ़ो(mdp4_kms, REG_MDP4_INTR_STATUS) & enable;
	mdp4_ग_लिखो(mdp4_kms, REG_MDP4_INTR_CLEAR, status);

	VERB("status=%08x", status);

	mdp_dispatch_irqs(mdp_kms, status);

	क्रम (id = 0; id < priv->num_crtcs; id++)
		अगर (status & mdp4_crtc_vblank(priv->crtcs[id]))
			drm_handle_vblank(dev, id);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक mdp4_enable_vblank(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));

	mdp4_enable(mdp4_kms);
	mdp_update_vblank_mask(to_mdp_kms(kms),
			mdp4_crtc_vblank(crtc), true);
	mdp4_disable(mdp4_kms);

	वापस 0;
पूर्ण

व्योम mdp4_disable_vblank(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp4_kms *mdp4_kms = to_mdp4_kms(to_mdp_kms(kms));

	mdp4_enable(mdp4_kms);
	mdp_update_vblank_mask(to_mdp_kms(kms),
			mdp4_crtc_vblank(crtc), false);
	mdp4_disable(mdp4_kms);
पूर्ण
