<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Texas Instruments Incorporated - https://www.ti.com/
 * Author: Rob Clark <rob.clark@linaro.org>
 */

#समावेश <drm/drm_vblank.h>

#समावेश "omap_drv.h"

काष्ठा omap_irq_रुको अणु
	काष्ठा list_head node;
	रुको_queue_head_t wq;
	u32 irqmask;
	पूर्णांक count;
पूर्ण;

/* call with रुको_lock and dispc runसमय held */
अटल व्योम omap_irq_update(काष्ठा drm_device *dev)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	काष्ठा omap_irq_रुको *रुको;
	u32 irqmask = priv->irq_mask;

	निश्चित_spin_locked(&priv->रुको_lock);

	list_क्रम_each_entry(रुको, &priv->रुको_list, node)
		irqmask |= रुको->irqmask;

	DBG("irqmask=%08x", irqmask);

	dispc_ग_लिखो_irqenable(priv->dispc, irqmask);
पूर्ण

अटल व्योम omap_irq_रुको_handler(काष्ठा omap_irq_रुको *रुको)
अणु
	रुको->count--;
	wake_up(&रुको->wq);
पूर्ण

काष्ठा omap_irq_रुको * omap_irq_रुको_init(काष्ठा drm_device *dev,
		u32 irqmask, पूर्णांक count)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	काष्ठा omap_irq_रुको *रुको = kzalloc(माप(*रुको), GFP_KERNEL);
	अचिन्हित दीर्घ flags;

	init_रुकोqueue_head(&रुको->wq);
	रुको->irqmask = irqmask;
	रुको->count = count;

	spin_lock_irqsave(&priv->रुको_lock, flags);
	list_add(&रुको->node, &priv->रुको_list);
	omap_irq_update(dev);
	spin_unlock_irqrestore(&priv->रुको_lock, flags);

	वापस रुको;
पूर्ण

पूर्णांक omap_irq_रुको(काष्ठा drm_device *dev, काष्ठा omap_irq_रुको *रुको,
		अचिन्हित दीर्घ समयout)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret;

	ret = रुको_event_समयout(रुको->wq, (रुको->count <= 0), समयout);

	spin_lock_irqsave(&priv->रुको_lock, flags);
	list_del(&रुको->node);
	omap_irq_update(dev);
	spin_unlock_irqrestore(&priv->रुको_lock, flags);

	kमुक्त(रुको);

	वापस ret == 0 ? -1 : 0;
पूर्ण

पूर्णांक omap_irq_enable_frameकरोne(काष्ठा drm_crtc *crtc, bool enable)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	अचिन्हित दीर्घ flags;
	क्रमागत omap_channel channel = omap_crtc_channel(crtc);
	पूर्णांक frameकरोne_irq =
		dispc_mgr_get_frameकरोne_irq(priv->dispc, channel);

	DBG("dev=%p, crtc=%u, enable=%d", dev, channel, enable);

	spin_lock_irqsave(&priv->रुको_lock, flags);
	अगर (enable)
		priv->irq_mask |= frameकरोne_irq;
	अन्यथा
		priv->irq_mask &= ~frameकरोne_irq;
	omap_irq_update(dev);
	spin_unlock_irqrestore(&priv->रुको_lock, flags);

	वापस 0;
पूर्ण

/**
 * enable_vblank - enable vblank पूर्णांकerrupt events
 * @crtc: DRM CRTC
 *
 * Enable vblank पूर्णांकerrupts क्रम @crtc.  If the device करोesn't have
 * a hardware vblank counter, this routine should be a no-op, since
 * पूर्णांकerrupts will have to stay on to keep the count accurate.
 *
 * RETURNS
 * Zero on success, appropriate त्रुटि_सं अगर the given @crtc's vblank
 * पूर्णांकerrupt cannot be enabled.
 */
पूर्णांक omap_irq_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	अचिन्हित दीर्घ flags;
	क्रमागत omap_channel channel = omap_crtc_channel(crtc);

	DBG("dev=%p, crtc=%u", dev, channel);

	spin_lock_irqsave(&priv->रुको_lock, flags);
	priv->irq_mask |= dispc_mgr_get_vsync_irq(priv->dispc,
							     channel);
	omap_irq_update(dev);
	spin_unlock_irqrestore(&priv->रुको_lock, flags);

	वापस 0;
पूर्ण

/**
 * disable_vblank - disable vblank पूर्णांकerrupt events
 * @crtc: DRM CRTC
 *
 * Disable vblank पूर्णांकerrupts क्रम @crtc.  If the device करोesn't have
 * a hardware vblank counter, this routine should be a no-op, since
 * पूर्णांकerrupts will have to stay on to keep the count accurate.
 */
व्योम omap_irq_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	अचिन्हित दीर्घ flags;
	क्रमागत omap_channel channel = omap_crtc_channel(crtc);

	DBG("dev=%p, crtc=%u", dev, channel);

	spin_lock_irqsave(&priv->रुको_lock, flags);
	priv->irq_mask &= ~dispc_mgr_get_vsync_irq(priv->dispc,
							      channel);
	omap_irq_update(dev);
	spin_unlock_irqrestore(&priv->रुको_lock, flags);
पूर्ण

अटल व्योम omap_irq_fअगरo_underflow(काष्ठा omap_drm_निजी *priv,
				    u32 irqstatus)
अणु
	अटल DEFINE_RATELIMIT_STATE(_rs, DEFAULT_RATELIMIT_INTERVAL,
				      DEFAULT_RATELIMIT_BURST);
	अटल स्थिर काष्ठा अणु
		स्थिर अक्षर *name;
		u32 mask;
	पूर्ण sources[] = अणु
		अणु "gfx", DISPC_IRQ_GFX_FIFO_UNDERFLOW पूर्ण,
		अणु "vid1", DISPC_IRQ_VID1_FIFO_UNDERFLOW पूर्ण,
		अणु "vid2", DISPC_IRQ_VID2_FIFO_UNDERFLOW पूर्ण,
		अणु "vid3", DISPC_IRQ_VID3_FIFO_UNDERFLOW पूर्ण,
	पूर्ण;

	स्थिर u32 mask = DISPC_IRQ_GFX_FIFO_UNDERFLOW
		       | DISPC_IRQ_VID1_FIFO_UNDERFLOW
		       | DISPC_IRQ_VID2_FIFO_UNDERFLOW
		       | DISPC_IRQ_VID3_FIFO_UNDERFLOW;
	अचिन्हित पूर्णांक i;

	spin_lock(&priv->रुको_lock);
	irqstatus &= priv->irq_mask & mask;
	spin_unlock(&priv->रुको_lock);

	अगर (!irqstatus)
		वापस;

	अगर (!__ratelimit(&_rs))
		वापस;

	DRM_ERROR("FIFO underflow on ");

	क्रम (i = 0; i < ARRAY_SIZE(sources); ++i) अणु
		अगर (sources[i].mask & irqstatus)
			pr_cont("%s ", sources[i].name);
	पूर्ण

	pr_cont("(0x%08x)\n", irqstatus);
पूर्ण

अटल व्योम omap_irq_ocp_error_handler(काष्ठा drm_device *dev,
	u32 irqstatus)
अणु
	अगर (!(irqstatus & DISPC_IRQ_OCP_ERR))
		वापस;

	dev_err_ratelimited(dev->dev, "OCP error\n");
पूर्ण

अटल irqवापस_t omap_irq_handler(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा drm_device *dev = (काष्ठा drm_device *) arg;
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	काष्ठा omap_irq_रुको *रुको, *n;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक id;
	u32 irqstatus;

	irqstatus = dispc_पढ़ो_irqstatus(priv->dispc);
	dispc_clear_irqstatus(priv->dispc, irqstatus);
	dispc_पढ़ो_irqstatus(priv->dispc);	/* flush posted ग_लिखो */

	VERB("irqs: %08x", irqstatus);

	क्रम (id = 0; id < priv->num_pipes; id++) अणु
		काष्ठा drm_crtc *crtc = priv->pipes[id].crtc;
		क्रमागत omap_channel channel = omap_crtc_channel(crtc);

		अगर (irqstatus & dispc_mgr_get_vsync_irq(priv->dispc, channel)) अणु
			drm_handle_vblank(dev, id);
			omap_crtc_vblank_irq(crtc);
		पूर्ण

		अगर (irqstatus & dispc_mgr_get_sync_lost_irq(priv->dispc, channel))
			omap_crtc_error_irq(crtc, irqstatus);

		अगर (irqstatus & dispc_mgr_get_frameकरोne_irq(priv->dispc, channel))
			omap_crtc_frameकरोne_irq(crtc, irqstatus);
	पूर्ण

	omap_irq_ocp_error_handler(dev, irqstatus);
	omap_irq_fअगरo_underflow(priv, irqstatus);

	spin_lock_irqsave(&priv->रुको_lock, flags);
	list_क्रम_each_entry_safe(रुको, n, &priv->रुको_list, node) अणु
		अगर (रुको->irqmask & irqstatus)
			omap_irq_रुको_handler(रुको);
	पूर्ण
	spin_unlock_irqrestore(&priv->रुको_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल स्थिर u32 omap_underflow_irqs[] = अणु
	[OMAP_DSS_GFX] = DISPC_IRQ_GFX_FIFO_UNDERFLOW,
	[OMAP_DSS_VIDEO1] = DISPC_IRQ_VID1_FIFO_UNDERFLOW,
	[OMAP_DSS_VIDEO2] = DISPC_IRQ_VID2_FIFO_UNDERFLOW,
	[OMAP_DSS_VIDEO3] = DISPC_IRQ_VID3_FIFO_UNDERFLOW,
पूर्ण;

/*
 * We need a special version, instead of just using drm_irq_install(),
 * because we need to रेजिस्टर the irq via omapdss.  Once omapdss and
 * omapdrm are merged together we can assign the dispc hwmod data to
 * ourselves and drop these and just use drm_irq_अणुinstall,uninstallपूर्ण()
 */

पूर्णांक omap_drm_irq_install(काष्ठा drm_device *dev)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;
	अचिन्हित पूर्णांक num_mgrs = dispc_get_num_mgrs(priv->dispc);
	अचिन्हित पूर्णांक max_planes;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	spin_lock_init(&priv->रुको_lock);
	INIT_LIST_HEAD(&priv->रुको_list);

	priv->irq_mask = DISPC_IRQ_OCP_ERR;

	max_planes = min(ARRAY_SIZE(priv->planes),
			 ARRAY_SIZE(omap_underflow_irqs));
	क्रम (i = 0; i < max_planes; ++i) अणु
		अगर (priv->planes[i])
			priv->irq_mask |= omap_underflow_irqs[i];
	पूर्ण

	क्रम (i = 0; i < num_mgrs; ++i)
		priv->irq_mask |= dispc_mgr_get_sync_lost_irq(priv->dispc, i);

	dispc_runसमय_get(priv->dispc);
	dispc_clear_irqstatus(priv->dispc, 0xffffffff);
	dispc_runसमय_put(priv->dispc);

	ret = dispc_request_irq(priv->dispc, omap_irq_handler, dev);
	अगर (ret < 0)
		वापस ret;

	dev->irq_enabled = true;

	वापस 0;
पूर्ण

व्योम omap_drm_irq_uninstall(काष्ठा drm_device *dev)
अणु
	काष्ठा omap_drm_निजी *priv = dev->dev_निजी;

	अगर (!dev->irq_enabled)
		वापस;

	dev->irq_enabled = false;

	dispc_मुक्त_irq(priv->dispc, dev);
पूर्ण
