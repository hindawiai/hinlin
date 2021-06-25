<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2018 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "tidss_crtc.h"
#समावेश "tidss_dispc.h"
#समावेश "tidss_drv.h"
#समावेश "tidss_irq.h"
#समावेश "tidss_plane.h"

/* call with रुको_lock and dispc runसमय held */
अटल व्योम tidss_irq_update(काष्ठा tidss_device *tidss)
अणु
	निश्चित_spin_locked(&tidss->रुको_lock);

	dispc_set_irqenable(tidss->dispc, tidss->irq_mask);
पूर्ण

व्योम tidss_irq_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *ddev = crtc->dev;
	काष्ठा tidss_device *tidss = to_tidss(ddev);
	काष्ठा tidss_crtc *tcrtc = to_tidss_crtc(crtc);
	u32 hw_videoport = tcrtc->hw_videoport;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tidss->रुको_lock, flags);
	tidss->irq_mask |= DSS_IRQ_VP_VSYNC_EVEN(hw_videoport) |
			   DSS_IRQ_VP_VSYNC_ODD(hw_videoport);
	tidss_irq_update(tidss);
	spin_unlock_irqrestore(&tidss->रुको_lock, flags);
पूर्ण

व्योम tidss_irq_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *ddev = crtc->dev;
	काष्ठा tidss_device *tidss = to_tidss(ddev);
	काष्ठा tidss_crtc *tcrtc = to_tidss_crtc(crtc);
	u32 hw_videoport = tcrtc->hw_videoport;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tidss->रुको_lock, flags);
	tidss->irq_mask &= ~(DSS_IRQ_VP_VSYNC_EVEN(hw_videoport) |
			     DSS_IRQ_VP_VSYNC_ODD(hw_videoport));
	tidss_irq_update(tidss);
	spin_unlock_irqrestore(&tidss->रुको_lock, flags);
पूर्ण

irqवापस_t tidss_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *ddev = (काष्ठा drm_device *)arg;
	काष्ठा tidss_device *tidss = to_tidss(ddev);
	अचिन्हित पूर्णांक id;
	dispc_irq_t irqstatus;

	अगर (WARN_ON(!ddev->irq_enabled))
		वापस IRQ_NONE;

	irqstatus = dispc_पढ़ो_and_clear_irqstatus(tidss->dispc);

	क्रम (id = 0; id < tidss->num_crtcs; id++) अणु
		काष्ठा drm_crtc *crtc = tidss->crtcs[id];
		काष्ठा tidss_crtc *tcrtc = to_tidss_crtc(crtc);
		u32 hw_videoport = tcrtc->hw_videoport;

		अगर (irqstatus & (DSS_IRQ_VP_VSYNC_EVEN(hw_videoport) |
				 DSS_IRQ_VP_VSYNC_ODD(hw_videoport)))
			tidss_crtc_vblank_irq(crtc);

		अगर (irqstatus & (DSS_IRQ_VP_FRAME_DONE(hw_videoport)))
			tidss_crtc_frameकरोne_irq(crtc);

		अगर (irqstatus & DSS_IRQ_VP_SYNC_LOST(hw_videoport))
			tidss_crtc_error_irq(crtc, irqstatus);
	पूर्ण

	अगर (irqstatus & DSS_IRQ_DEVICE_OCP_ERR)
		dev_err_ratelimited(tidss->dev, "OCP error\n");

	वापस IRQ_HANDLED;
पूर्ण

व्योम tidss_irq_resume(काष्ठा tidss_device *tidss)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&tidss->रुको_lock, flags);
	tidss_irq_update(tidss);
	spin_unlock_irqrestore(&tidss->रुको_lock, flags);
पूर्ण

व्योम tidss_irq_preinstall(काष्ठा drm_device *ddev)
अणु
	काष्ठा tidss_device *tidss = to_tidss(ddev);

	spin_lock_init(&tidss->रुको_lock);

	tidss_runसमय_get(tidss);

	dispc_set_irqenable(tidss->dispc, 0);
	dispc_पढ़ो_and_clear_irqstatus(tidss->dispc);

	tidss_runसमय_put(tidss);
पूर्ण

पूर्णांक tidss_irq_postinstall(काष्ठा drm_device *ddev)
अणु
	काष्ठा tidss_device *tidss = to_tidss(ddev);
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक i;

	tidss_runसमय_get(tidss);

	spin_lock_irqsave(&tidss->रुको_lock, flags);

	tidss->irq_mask = DSS_IRQ_DEVICE_OCP_ERR;

	क्रम (i = 0; i < tidss->num_crtcs; ++i) अणु
		काष्ठा tidss_crtc *tcrtc = to_tidss_crtc(tidss->crtcs[i]);

		tidss->irq_mask |= DSS_IRQ_VP_SYNC_LOST(tcrtc->hw_videoport);

		tidss->irq_mask |= DSS_IRQ_VP_FRAME_DONE(tcrtc->hw_videoport);
	पूर्ण

	tidss_irq_update(tidss);

	spin_unlock_irqrestore(&tidss->रुको_lock, flags);

	tidss_runसमय_put(tidss);

	वापस 0;
पूर्ण

व्योम tidss_irq_uninstall(काष्ठा drm_device *ddev)
अणु
	काष्ठा tidss_device *tidss = to_tidss(ddev);

	tidss_runसमय_get(tidss);
	dispc_set_irqenable(tidss->dispc, 0);
	tidss_runसमय_put(tidss);
पूर्ण
