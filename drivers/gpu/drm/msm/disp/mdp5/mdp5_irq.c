<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Red Hat
 * Author: Rob Clark <robdclark@gmail.com>
 */

#समावेश <linux/irq.h>

#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_vblank.h>

#समावेश "msm_drv.h"
#समावेश "mdp5_kms.h"

व्योम mdp5_set_irqmask(काष्ठा mdp_kms *mdp_kms, uपूर्णांक32_t irqmask,
		uपूर्णांक32_t old_irqmask)
अणु
	mdp5_ग_लिखो(to_mdp5_kms(mdp_kms), REG_MDP5_INTR_CLEAR,
		   irqmask ^ (irqmask & old_irqmask));
	mdp5_ग_लिखो(to_mdp5_kms(mdp_kms), REG_MDP5_INTR_EN, irqmask);
पूर्ण

अटल व्योम mdp5_irq_error_handler(काष्ठा mdp_irq *irq, uपूर्णांक32_t irqstatus)
अणु
	काष्ठा mdp5_kms *mdp5_kms = container_of(irq, काष्ठा mdp5_kms, error_handler);
	अटल DEFINE_RATELIMIT_STATE(rs, 5*HZ, 1);
	बाह्य bool dumpstate;

	DRM_ERROR_RATELIMITED("errors: %08x\n", irqstatus);

	अगर (dumpstate && __ratelimit(&rs)) अणु
		काष्ठा drm_prपूर्णांकer p = drm_info_prपूर्णांकer(mdp5_kms->dev->dev);
		drm_state_dump(mdp5_kms->dev, &p);
		अगर (mdp5_kms->smp)
			mdp5_smp_dump(mdp5_kms->smp, &p);
	पूर्ण
पूर्ण

व्योम mdp5_irq_preinstall(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	काष्ठा device *dev = &mdp5_kms->pdev->dev;

	pm_runसमय_get_sync(dev);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTR_CLEAR, 0xffffffff);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTR_EN, 0x00000000);
	pm_runसमय_put_sync(dev);
पूर्ण

पूर्णांक mdp5_irq_postinstall(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp_kms *mdp_kms = to_mdp_kms(kms);
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(mdp_kms);
	काष्ठा device *dev = &mdp5_kms->pdev->dev;
	काष्ठा mdp_irq *error_handler = &mdp5_kms->error_handler;

	error_handler->irq = mdp5_irq_error_handler;
	error_handler->irqmask = MDP5_IRQ_INTF0_UNDER_RUN |
			MDP5_IRQ_INTF1_UNDER_RUN |
			MDP5_IRQ_INTF2_UNDER_RUN |
			MDP5_IRQ_INTF3_UNDER_RUN;

	pm_runसमय_get_sync(dev);
	mdp_irq_रेजिस्टर(mdp_kms, error_handler);
	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण

व्योम mdp5_irq_uninstall(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	काष्ठा device *dev = &mdp5_kms->pdev->dev;

	pm_runसमय_get_sync(dev);
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTR_EN, 0x00000000);
	pm_runसमय_put_sync(dev);
पूर्ण

irqवापस_t mdp5_irq(काष्ठा msm_kms *kms)
अणु
	काष्ठा mdp_kms *mdp_kms = to_mdp_kms(kms);
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(mdp_kms);
	काष्ठा drm_device *dev = mdp5_kms->dev;
	काष्ठा msm_drm_निजी *priv = dev->dev_निजी;
	अचिन्हित पूर्णांक id;
	uपूर्णांक32_t status, enable;

	enable = mdp5_पढ़ो(mdp5_kms, REG_MDP5_INTR_EN);
	status = mdp5_पढ़ो(mdp5_kms, REG_MDP5_INTR_STATUS) & enable;
	mdp5_ग_लिखो(mdp5_kms, REG_MDP5_INTR_CLEAR, status);

	VERB("status=%08x", status);

	mdp_dispatch_irqs(mdp_kms, status);

	क्रम (id = 0; id < priv->num_crtcs; id++)
		अगर (status & mdp5_crtc_vblank(priv->crtcs[id]))
			drm_handle_vblank(dev, id);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक mdp5_enable_vblank(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	काष्ठा device *dev = &mdp5_kms->pdev->dev;

	pm_runसमय_get_sync(dev);
	mdp_update_vblank_mask(to_mdp_kms(kms),
			mdp5_crtc_vblank(crtc), true);
	pm_runसमय_put_sync(dev);

	वापस 0;
पूर्ण

व्योम mdp5_disable_vblank(काष्ठा msm_kms *kms, काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mdp5_kms *mdp5_kms = to_mdp5_kms(to_mdp_kms(kms));
	काष्ठा device *dev = &mdp5_kms->pdev->dev;

	pm_runसमय_get_sync(dev);
	mdp_update_vblank_mask(to_mdp_kms(kms),
			mdp5_crtc_vblank(crtc), false);
	pm_runसमय_put_sync(dev);
पूर्ण
