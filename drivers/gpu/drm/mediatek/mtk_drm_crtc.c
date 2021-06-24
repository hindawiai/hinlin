<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2015 MediaTek Inc.
 */

#समावेश <linux/clk.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/soc/mediatek/mtk-cmdq.h>
#समावेश <linux/soc/mediatek/mtk-mmsys.h>
#समावेश <linux/soc/mediatek/mtk-mutex.h>

#समावेश <यंत्र/barrier.h>
#समावेश <soc/mediatek/smi.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_plane_helper.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "mtk_drm_drv.h"
#समावेश "mtk_drm_crtc.h"
#समावेश "mtk_drm_ddp_comp.h"
#समावेश "mtk_drm_gem.h"
#समावेश "mtk_drm_plane.h"

/*
 * काष्ठा mtk_drm_crtc - MediaTek specअगरic crtc काष्ठाure.
 * @base: crtc object.
 * @enabled: records whether crtc_enable succeeded
 * @planes: array of 4 drm_plane काष्ठाures, one क्रम each overlay plane
 * @pending_planes: whether any plane has pending changes to be applied
 * @mmsys_dev: poपूर्णांकer to the mmsys device क्रम configuration रेजिस्टरs
 * @mutex: handle to one of the ten disp_mutex streams
 * @ddp_comp_nr: number of components in ddp_comp
 * @ddp_comp: array of poपूर्णांकers the mtk_ddp_comp काष्ठाures used by this crtc
 *
 * TODO: Needs update: this header is missing a bunch of member descriptions.
 */
काष्ठा mtk_drm_crtc अणु
	काष्ठा drm_crtc			base;
	bool				enabled;

	bool				pending_needs_vblank;
	काष्ठा drm_pending_vblank_event	*event;

	काष्ठा drm_plane		*planes;
	अचिन्हित पूर्णांक			layer_nr;
	bool				pending_planes;
	bool				pending_async_planes;

#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
	काष्ठा cmdq_client		*cmdq_client;
	u32				cmdq_event;
#पूर्ण_अगर

	काष्ठा device			*mmsys_dev;
	काष्ठा mtk_mutex		*mutex;
	अचिन्हित पूर्णांक			ddp_comp_nr;
	काष्ठा mtk_ddp_comp		**ddp_comp;

	/* lock क्रम display hardware access */
	काष्ठा mutex			hw_lock;
	bool				config_updating;
पूर्ण;

काष्ठा mtk_crtc_state अणु
	काष्ठा drm_crtc_state		base;

	bool				pending_config;
	अचिन्हित पूर्णांक			pending_width;
	अचिन्हित पूर्णांक			pending_height;
	अचिन्हित पूर्णांक			pending_vrefresh;
पूर्ण;

अटल अंतरभूत काष्ठा mtk_drm_crtc *to_mtk_crtc(काष्ठा drm_crtc *c)
अणु
	वापस container_of(c, काष्ठा mtk_drm_crtc, base);
पूर्ण

अटल अंतरभूत काष्ठा mtk_crtc_state *to_mtk_crtc_state(काष्ठा drm_crtc_state *s)
अणु
	वापस container_of(s, काष्ठा mtk_crtc_state, base);
पूर्ण

अटल व्योम mtk_drm_crtc_finish_page_flip(काष्ठा mtk_drm_crtc *mtk_crtc)
अणु
	काष्ठा drm_crtc *crtc = &mtk_crtc->base;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&crtc->dev->event_lock, flags);
	drm_crtc_send_vblank_event(crtc, mtk_crtc->event);
	drm_crtc_vblank_put(crtc);
	mtk_crtc->event = शून्य;
	spin_unlock_irqrestore(&crtc->dev->event_lock, flags);
पूर्ण

अटल व्योम mtk_drm_finish_page_flip(काष्ठा mtk_drm_crtc *mtk_crtc)
अणु
	drm_crtc_handle_vblank(&mtk_crtc->base);
	अगर (!mtk_crtc->config_updating && mtk_crtc->pending_needs_vblank) अणु
		mtk_drm_crtc_finish_page_flip(mtk_crtc);
		mtk_crtc->pending_needs_vblank = false;
	पूर्ण
पूर्ण

अटल व्योम mtk_drm_crtc_destroy(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mtk_drm_crtc *mtk_crtc = to_mtk_crtc(crtc);

	mtk_mutex_put(mtk_crtc->mutex);

	drm_crtc_cleanup(crtc);
पूर्ण

अटल व्योम mtk_drm_crtc_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mtk_crtc_state *state;

	अगर (crtc->state)
		__drm_atomic_helper_crtc_destroy_state(crtc->state);

	kमुक्त(to_mtk_crtc_state(crtc->state));
	crtc->state = शून्य;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (state)
		__drm_atomic_helper_crtc_reset(crtc, &state->base);
पूर्ण

अटल काष्ठा drm_crtc_state *mtk_drm_crtc_duplicate_state(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mtk_crtc_state *state;

	state = kzalloc(माप(*state), GFP_KERNEL);
	अगर (!state)
		वापस शून्य;

	__drm_atomic_helper_crtc_duplicate_state(crtc, &state->base);

	WARN_ON(state->base.crtc != crtc);
	state->base.crtc = crtc;

	वापस &state->base;
पूर्ण

अटल व्योम mtk_drm_crtc_destroy_state(काष्ठा drm_crtc *crtc,
				       काष्ठा drm_crtc_state *state)
अणु
	__drm_atomic_helper_crtc_destroy_state(state);
	kमुक्त(to_mtk_crtc_state(state));
पूर्ण

अटल bool mtk_drm_crtc_mode_fixup(काष्ठा drm_crtc *crtc,
				    स्थिर काष्ठा drm_display_mode *mode,
				    काष्ठा drm_display_mode *adjusted_mode)
अणु
	/* Nothing to करो here, but this callback is mandatory. */
	वापस true;
पूर्ण

अटल व्योम mtk_drm_crtc_mode_set_nofb(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mtk_crtc_state *state = to_mtk_crtc_state(crtc->state);

	state->pending_width = crtc->mode.hdisplay;
	state->pending_height = crtc->mode.vdisplay;
	state->pending_vrefresh = drm_mode_vrefresh(&crtc->mode);
	wmb();	/* Make sure the above parameters are set beक्रमe update */
	state->pending_config = true;
पूर्ण

अटल पूर्णांक mtk_crtc_ddp_clk_enable(काष्ठा mtk_drm_crtc *mtk_crtc)
अणु
	पूर्णांक ret;
	पूर्णांक i;

	क्रम (i = 0; i < mtk_crtc->ddp_comp_nr; i++) अणु
		ret = mtk_ddp_comp_clk_enable(mtk_crtc->ddp_comp[i]);
		अगर (ret) अणु
			DRM_ERROR("Failed to enable clock %d: %d\n", i, ret);
			जाओ err;
		पूर्ण
	पूर्ण

	वापस 0;
err:
	जबतक (--i >= 0)
		mtk_ddp_comp_clk_disable(mtk_crtc->ddp_comp[i]);
	वापस ret;
पूर्ण

अटल व्योम mtk_crtc_ddp_clk_disable(काष्ठा mtk_drm_crtc *mtk_crtc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < mtk_crtc->ddp_comp_nr; i++)
		mtk_ddp_comp_clk_disable(mtk_crtc->ddp_comp[i]);
पूर्ण

अटल
काष्ठा mtk_ddp_comp *mtk_drm_ddp_comp_क्रम_plane(काष्ठा drm_crtc *crtc,
						काष्ठा drm_plane *plane,
						अचिन्हित पूर्णांक *local_layer)
अणु
	काष्ठा mtk_drm_crtc *mtk_crtc = to_mtk_crtc(crtc);
	काष्ठा mtk_ddp_comp *comp;
	पूर्णांक i, count = 0;
	अचिन्हित पूर्णांक local_index = plane - mtk_crtc->planes;

	क्रम (i = 0; i < mtk_crtc->ddp_comp_nr; i++) अणु
		comp = mtk_crtc->ddp_comp[i];
		अगर (local_index < (count + mtk_ddp_comp_layer_nr(comp))) अणु
			*local_layer = local_index - count;
			वापस comp;
		पूर्ण
		count += mtk_ddp_comp_layer_nr(comp);
	पूर्ण

	WARN(1, "Failed to find component for plane %d\n", plane->index);
	वापस शून्य;
पूर्ण

#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
अटल व्योम ddp_cmdq_cb(काष्ठा cmdq_cb_data data)
अणु
	cmdq_pkt_destroy(data.data);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक mtk_crtc_ddp_hw_init(काष्ठा mtk_drm_crtc *mtk_crtc)
अणु
	काष्ठा drm_crtc *crtc = &mtk_crtc->base;
	काष्ठा drm_connector *connector;
	काष्ठा drm_encoder *encoder;
	काष्ठा drm_connector_list_iter conn_iter;
	अचिन्हित पूर्णांक width, height, vrefresh, bpc = MTK_MAX_BPC;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (WARN_ON(!crtc->state))
		वापस -EINVAL;

	width = crtc->state->adjusted_mode.hdisplay;
	height = crtc->state->adjusted_mode.vdisplay;
	vrefresh = drm_mode_vrefresh(&crtc->state->adjusted_mode);

	drm_क्रम_each_encoder(encoder, crtc->dev) अणु
		अगर (encoder->crtc != crtc)
			जारी;

		drm_connector_list_iter_begin(crtc->dev, &conn_iter);
		drm_क्रम_each_connector_iter(connector, &conn_iter) अणु
			अगर (connector->encoder != encoder)
				जारी;
			अगर (connector->display_info.bpc != 0 &&
			    bpc > connector->display_info.bpc)
				bpc = connector->display_info.bpc;
		पूर्ण
		drm_connector_list_iter_end(&conn_iter);
	पूर्ण

	ret = pm_runसमय_get_sync(crtc->dev->dev);
	अगर (ret < 0) अणु
		DRM_ERROR("Failed to enable power domain: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = mtk_mutex_prepare(mtk_crtc->mutex);
	अगर (ret < 0) अणु
		DRM_ERROR("Failed to enable mutex clock: %d\n", ret);
		जाओ err_pm_runसमय_put;
	पूर्ण

	ret = mtk_crtc_ddp_clk_enable(mtk_crtc);
	अगर (ret < 0) अणु
		DRM_ERROR("Failed to enable component clocks: %d\n", ret);
		जाओ err_mutex_unprepare;
	पूर्ण

	क्रम (i = 0; i < mtk_crtc->ddp_comp_nr - 1; i++) अणु
		mtk_mmsys_ddp_connect(mtk_crtc->mmsys_dev,
				      mtk_crtc->ddp_comp[i]->id,
				      mtk_crtc->ddp_comp[i + 1]->id);
		mtk_mutex_add_comp(mtk_crtc->mutex,
					mtk_crtc->ddp_comp[i]->id);
	पूर्ण
	mtk_mutex_add_comp(mtk_crtc->mutex, mtk_crtc->ddp_comp[i]->id);
	mtk_mutex_enable(mtk_crtc->mutex);

	क्रम (i = 0; i < mtk_crtc->ddp_comp_nr; i++) अणु
		काष्ठा mtk_ddp_comp *comp = mtk_crtc->ddp_comp[i];

		अगर (i == 1)
			mtk_ddp_comp_bgclr_in_on(comp);

		mtk_ddp_comp_config(comp, width, height, vrefresh, bpc, शून्य);
		mtk_ddp_comp_start(comp);
	पूर्ण

	/* Initially configure all planes */
	क्रम (i = 0; i < mtk_crtc->layer_nr; i++) अणु
		काष्ठा drm_plane *plane = &mtk_crtc->planes[i];
		काष्ठा mtk_plane_state *plane_state;
		काष्ठा mtk_ddp_comp *comp;
		अचिन्हित पूर्णांक local_layer;

		plane_state = to_mtk_plane_state(plane->state);
		comp = mtk_drm_ddp_comp_क्रम_plane(crtc, plane, &local_layer);
		अगर (comp)
			mtk_ddp_comp_layer_config(comp, local_layer,
						  plane_state, शून्य);
	पूर्ण

	वापस 0;

err_mutex_unprepare:
	mtk_mutex_unprepare(mtk_crtc->mutex);
err_pm_runसमय_put:
	pm_runसमय_put(crtc->dev->dev);
	वापस ret;
पूर्ण

अटल व्योम mtk_crtc_ddp_hw_fini(काष्ठा mtk_drm_crtc *mtk_crtc)
अणु
	काष्ठा drm_device *drm = mtk_crtc->base.dev;
	काष्ठा drm_crtc *crtc = &mtk_crtc->base;
	पूर्णांक i;

	क्रम (i = 0; i < mtk_crtc->ddp_comp_nr; i++) अणु
		mtk_ddp_comp_stop(mtk_crtc->ddp_comp[i]);
		अगर (i == 1)
			mtk_ddp_comp_bgclr_in_off(mtk_crtc->ddp_comp[i]);
	पूर्ण

	क्रम (i = 0; i < mtk_crtc->ddp_comp_nr; i++)
		mtk_mutex_हटाओ_comp(mtk_crtc->mutex,
					   mtk_crtc->ddp_comp[i]->id);
	mtk_mutex_disable(mtk_crtc->mutex);
	क्रम (i = 0; i < mtk_crtc->ddp_comp_nr - 1; i++) अणु
		mtk_mmsys_ddp_disconnect(mtk_crtc->mmsys_dev,
					 mtk_crtc->ddp_comp[i]->id,
					 mtk_crtc->ddp_comp[i + 1]->id);
		mtk_mutex_हटाओ_comp(mtk_crtc->mutex,
					   mtk_crtc->ddp_comp[i]->id);
	पूर्ण
	mtk_mutex_हटाओ_comp(mtk_crtc->mutex, mtk_crtc->ddp_comp[i]->id);
	mtk_crtc_ddp_clk_disable(mtk_crtc);
	mtk_mutex_unprepare(mtk_crtc->mutex);

	pm_runसमय_put(drm->dev);

	अगर (crtc->state->event && !crtc->state->active) अणु
		spin_lock_irq(&crtc->dev->event_lock);
		drm_crtc_send_vblank_event(crtc, crtc->state->event);
		crtc->state->event = शून्य;
		spin_unlock_irq(&crtc->dev->event_lock);
	पूर्ण
पूर्ण

अटल व्योम mtk_crtc_ddp_config(काष्ठा drm_crtc *crtc,
				काष्ठा cmdq_pkt *cmdq_handle)
अणु
	काष्ठा mtk_drm_crtc *mtk_crtc = to_mtk_crtc(crtc);
	काष्ठा mtk_crtc_state *state = to_mtk_crtc_state(mtk_crtc->base.state);
	काष्ठा mtk_ddp_comp *comp = mtk_crtc->ddp_comp[0];
	अचिन्हित पूर्णांक i;
	अचिन्हित पूर्णांक local_layer;

	/*
	 * TODO: instead of updating the रेजिस्टरs here, we should prepare
	 * working रेजिस्टरs in atomic_commit and let the hardware command
	 * queue update module रेजिस्टरs on vblank.
	 */
	अगर (state->pending_config) अणु
		mtk_ddp_comp_config(comp, state->pending_width,
				    state->pending_height,
				    state->pending_vrefresh, 0,
				    cmdq_handle);

		state->pending_config = false;
	पूर्ण

	अगर (mtk_crtc->pending_planes) अणु
		क्रम (i = 0; i < mtk_crtc->layer_nr; i++) अणु
			काष्ठा drm_plane *plane = &mtk_crtc->planes[i];
			काष्ठा mtk_plane_state *plane_state;

			plane_state = to_mtk_plane_state(plane->state);

			अगर (!plane_state->pending.config)
				जारी;

			comp = mtk_drm_ddp_comp_क्रम_plane(crtc, plane,
							  &local_layer);

			अगर (comp)
				mtk_ddp_comp_layer_config(comp, local_layer,
							  plane_state,
							  cmdq_handle);
			plane_state->pending.config = false;
		पूर्ण
		mtk_crtc->pending_planes = false;
	पूर्ण

	अगर (mtk_crtc->pending_async_planes) अणु
		क्रम (i = 0; i < mtk_crtc->layer_nr; i++) अणु
			काष्ठा drm_plane *plane = &mtk_crtc->planes[i];
			काष्ठा mtk_plane_state *plane_state;

			plane_state = to_mtk_plane_state(plane->state);

			अगर (!plane_state->pending.async_config)
				जारी;

			comp = mtk_drm_ddp_comp_क्रम_plane(crtc, plane,
							  &local_layer);

			अगर (comp)
				mtk_ddp_comp_layer_config(comp, local_layer,
							  plane_state,
							  cmdq_handle);
			plane_state->pending.async_config = false;
		पूर्ण
		mtk_crtc->pending_async_planes = false;
	पूर्ण
पूर्ण

अटल व्योम mtk_drm_crtc_update_config(काष्ठा mtk_drm_crtc *mtk_crtc,
				       bool needs_vblank)
अणु
#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
	काष्ठा cmdq_pkt *cmdq_handle;
#पूर्ण_अगर
	काष्ठा drm_crtc *crtc = &mtk_crtc->base;
	काष्ठा mtk_drm_निजी *priv = crtc->dev->dev_निजी;
	अचिन्हित पूर्णांक pending_planes = 0, pending_async_planes = 0;
	पूर्णांक i;

	mutex_lock(&mtk_crtc->hw_lock);
	mtk_crtc->config_updating = true;
	अगर (needs_vblank)
		mtk_crtc->pending_needs_vblank = true;

	क्रम (i = 0; i < mtk_crtc->layer_nr; i++) अणु
		काष्ठा drm_plane *plane = &mtk_crtc->planes[i];
		काष्ठा mtk_plane_state *plane_state;

		plane_state = to_mtk_plane_state(plane->state);
		अगर (plane_state->pending.dirty) अणु
			plane_state->pending.config = true;
			plane_state->pending.dirty = false;
			pending_planes |= BIT(i);
		पूर्ण अन्यथा अगर (plane_state->pending.async_dirty) अणु
			plane_state->pending.async_config = true;
			plane_state->pending.async_dirty = false;
			pending_async_planes |= BIT(i);
		पूर्ण
	पूर्ण
	अगर (pending_planes)
		mtk_crtc->pending_planes = true;
	अगर (pending_async_planes)
		mtk_crtc->pending_async_planes = true;

	अगर (priv->data->shaकरोw_रेजिस्टर) अणु
		mtk_mutex_acquire(mtk_crtc->mutex);
		mtk_crtc_ddp_config(crtc, शून्य);
		mtk_mutex_release(mtk_crtc->mutex);
	पूर्ण
#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
	अगर (mtk_crtc->cmdq_client) अणु
		mbox_flush(mtk_crtc->cmdq_client->chan, 2000);
		cmdq_handle = cmdq_pkt_create(mtk_crtc->cmdq_client, PAGE_SIZE);
		cmdq_pkt_clear_event(cmdq_handle, mtk_crtc->cmdq_event);
		cmdq_pkt_wfe(cmdq_handle, mtk_crtc->cmdq_event, false);
		mtk_crtc_ddp_config(crtc, cmdq_handle);
		cmdq_pkt_finalize(cmdq_handle);
		cmdq_pkt_flush_async(cmdq_handle, ddp_cmdq_cb, cmdq_handle);
	पूर्ण
#पूर्ण_अगर
	mtk_crtc->config_updating = false;
	mutex_unlock(&mtk_crtc->hw_lock);
पूर्ण

अटल व्योम mtk_crtc_ddp_irq(व्योम *data)
अणु
	काष्ठा drm_crtc *crtc = data;
	काष्ठा mtk_drm_crtc *mtk_crtc = to_mtk_crtc(crtc);
	काष्ठा mtk_drm_निजी *priv = crtc->dev->dev_निजी;

#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
	अगर (!priv->data->shaकरोw_रेजिस्टर && !mtk_crtc->cmdq_client)
#अन्यथा
	अगर (!priv->data->shaकरोw_रेजिस्टर)
#पूर्ण_अगर
		mtk_crtc_ddp_config(crtc, शून्य);

	mtk_drm_finish_page_flip(mtk_crtc);
पूर्ण

अटल पूर्णांक mtk_drm_crtc_enable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mtk_drm_crtc *mtk_crtc = to_mtk_crtc(crtc);
	काष्ठा mtk_ddp_comp *comp = mtk_crtc->ddp_comp[0];

	mtk_ddp_comp_enable_vblank(comp, mtk_crtc_ddp_irq, &mtk_crtc->base);

	वापस 0;
पूर्ण

अटल व्योम mtk_drm_crtc_disable_vblank(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा mtk_drm_crtc *mtk_crtc = to_mtk_crtc(crtc);
	काष्ठा mtk_ddp_comp *comp = mtk_crtc->ddp_comp[0];

	mtk_ddp_comp_disable_vblank(comp);
पूर्ण

पूर्णांक mtk_drm_crtc_plane_check(काष्ठा drm_crtc *crtc, काष्ठा drm_plane *plane,
			     काष्ठा mtk_plane_state *state)
अणु
	अचिन्हित पूर्णांक local_layer;
	काष्ठा mtk_ddp_comp *comp;

	comp = mtk_drm_ddp_comp_क्रम_plane(crtc, plane, &local_layer);
	अगर (comp)
		वापस mtk_ddp_comp_layer_check(comp, local_layer, state);
	वापस 0;
पूर्ण

व्योम mtk_drm_crtc_async_update(काष्ठा drm_crtc *crtc, काष्ठा drm_plane *plane,
			       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mtk_drm_crtc *mtk_crtc = to_mtk_crtc(crtc);
	स्थिर काष्ठा drm_plane_helper_funcs *plane_helper_funcs =
			plane->helper_निजी;

	अगर (!mtk_crtc->enabled)
		वापस;

	plane_helper_funcs->atomic_update(plane, state);
	mtk_drm_crtc_update_config(mtk_crtc, false);
पूर्ण

अटल व्योम mtk_drm_crtc_atomic_enable(काष्ठा drm_crtc *crtc,
				       काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mtk_drm_crtc *mtk_crtc = to_mtk_crtc(crtc);
	काष्ठा mtk_ddp_comp *comp = mtk_crtc->ddp_comp[0];
	पूर्णांक ret;

	DRM_DEBUG_DRIVER("%s %d\n", __func__, crtc->base.id);

	ret = mtk_smi_larb_get(comp->larb_dev);
	अगर (ret) अणु
		DRM_ERROR("Failed to get larb: %d\n", ret);
		वापस;
	पूर्ण

	ret = mtk_crtc_ddp_hw_init(mtk_crtc);
	अगर (ret) अणु
		mtk_smi_larb_put(comp->larb_dev);
		वापस;
	पूर्ण

	drm_crtc_vblank_on(crtc);
	mtk_crtc->enabled = true;
पूर्ण

अटल व्योम mtk_drm_crtc_atomic_disable(काष्ठा drm_crtc *crtc,
					काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mtk_drm_crtc *mtk_crtc = to_mtk_crtc(crtc);
	काष्ठा mtk_ddp_comp *comp = mtk_crtc->ddp_comp[0];
	पूर्णांक i;

	DRM_DEBUG_DRIVER("%s %d\n", __func__, crtc->base.id);
	अगर (!mtk_crtc->enabled)
		वापस;

	/* Set all pending plane state to disabled */
	क्रम (i = 0; i < mtk_crtc->layer_nr; i++) अणु
		काष्ठा drm_plane *plane = &mtk_crtc->planes[i];
		काष्ठा mtk_plane_state *plane_state;

		plane_state = to_mtk_plane_state(plane->state);
		plane_state->pending.enable = false;
		plane_state->pending.config = true;
	पूर्ण
	mtk_crtc->pending_planes = true;

	mtk_drm_crtc_update_config(mtk_crtc, false);
	/* Wait क्रम planes to be disabled */
	drm_crtc_रुको_one_vblank(crtc);

	drm_crtc_vblank_off(crtc);
	mtk_crtc_ddp_hw_fini(mtk_crtc);
	mtk_smi_larb_put(comp->larb_dev);

	mtk_crtc->enabled = false;
पूर्ण

अटल व्योम mtk_drm_crtc_atomic_begin(काष्ठा drm_crtc *crtc,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state,
									  crtc);
	काष्ठा mtk_crtc_state *mtk_crtc_state = to_mtk_crtc_state(crtc_state);
	काष्ठा mtk_drm_crtc *mtk_crtc = to_mtk_crtc(crtc);

	अगर (mtk_crtc->event && mtk_crtc_state->base.event)
		DRM_ERROR("new event while there is still a pending event\n");

	अगर (mtk_crtc_state->base.event) अणु
		mtk_crtc_state->base.event->pipe = drm_crtc_index(crtc);
		WARN_ON(drm_crtc_vblank_get(crtc) != 0);
		mtk_crtc->event = mtk_crtc_state->base.event;
		mtk_crtc_state->base.event = शून्य;
	पूर्ण
पूर्ण

अटल व्योम mtk_drm_crtc_atomic_flush(काष्ठा drm_crtc *crtc,
				      काष्ठा drm_atomic_state *state)
अणु
	काष्ठा mtk_drm_crtc *mtk_crtc = to_mtk_crtc(crtc);
	पूर्णांक i;

	अगर (crtc->state->color_mgmt_changed)
		क्रम (i = 0; i < mtk_crtc->ddp_comp_nr; i++) अणु
			mtk_ddp_gamma_set(mtk_crtc->ddp_comp[i], crtc->state);
			mtk_ddp_cपंचांग_set(mtk_crtc->ddp_comp[i], crtc->state);
		पूर्ण
	mtk_drm_crtc_update_config(mtk_crtc, !!mtk_crtc->event);
पूर्ण

अटल स्थिर काष्ठा drm_crtc_funcs mtk_crtc_funcs = अणु
	.set_config		= drm_atomic_helper_set_config,
	.page_flip		= drm_atomic_helper_page_flip,
	.destroy		= mtk_drm_crtc_destroy,
	.reset			= mtk_drm_crtc_reset,
	.atomic_duplicate_state	= mtk_drm_crtc_duplicate_state,
	.atomic_destroy_state	= mtk_drm_crtc_destroy_state,
	.enable_vblank		= mtk_drm_crtc_enable_vblank,
	.disable_vblank		= mtk_drm_crtc_disable_vblank,
पूर्ण;

अटल स्थिर काष्ठा drm_crtc_helper_funcs mtk_crtc_helper_funcs = अणु
	.mode_fixup	= mtk_drm_crtc_mode_fixup,
	.mode_set_nofb	= mtk_drm_crtc_mode_set_nofb,
	.atomic_begin	= mtk_drm_crtc_atomic_begin,
	.atomic_flush	= mtk_drm_crtc_atomic_flush,
	.atomic_enable	= mtk_drm_crtc_atomic_enable,
	.atomic_disable	= mtk_drm_crtc_atomic_disable,
पूर्ण;

अटल पूर्णांक mtk_drm_crtc_init(काष्ठा drm_device *drm,
			     काष्ठा mtk_drm_crtc *mtk_crtc,
			     अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा drm_plane *primary = शून्य;
	काष्ठा drm_plane *cursor = शून्य;
	पूर्णांक i, ret;

	क्रम (i = 0; i < mtk_crtc->layer_nr; i++) अणु
		अगर (mtk_crtc->planes[i].type == DRM_PLANE_TYPE_PRIMARY)
			primary = &mtk_crtc->planes[i];
		अन्यथा अगर (mtk_crtc->planes[i].type == DRM_PLANE_TYPE_CURSOR)
			cursor = &mtk_crtc->planes[i];
	पूर्ण

	ret = drm_crtc_init_with_planes(drm, &mtk_crtc->base, primary, cursor,
					&mtk_crtc_funcs, शून्य);
	अगर (ret)
		जाओ err_cleanup_crtc;

	drm_crtc_helper_add(&mtk_crtc->base, &mtk_crtc_helper_funcs);

	वापस 0;

err_cleanup_crtc:
	drm_crtc_cleanup(&mtk_crtc->base);
	वापस ret;
पूर्ण

अटल पूर्णांक mtk_drm_crtc_num_comp_planes(काष्ठा mtk_drm_crtc *mtk_crtc,
					पूर्णांक comp_idx)
अणु
	काष्ठा mtk_ddp_comp *comp;

	अगर (comp_idx > 1)
		वापस 0;

	comp = mtk_crtc->ddp_comp[comp_idx];
	अगर (!comp->funcs)
		वापस 0;

	अगर (comp_idx == 1 && !comp->funcs->bgclr_in_on)
		वापस 0;

	वापस mtk_ddp_comp_layer_nr(comp);
पूर्ण

अटल अंतरभूत
क्रमागत drm_plane_type mtk_drm_crtc_plane_type(अचिन्हित पूर्णांक plane_idx,
					    अचिन्हित पूर्णांक num_planes)
अणु
	अगर (plane_idx == 0)
		वापस DRM_PLANE_TYPE_PRIMARY;
	अन्यथा अगर (plane_idx == (num_planes - 1))
		वापस DRM_PLANE_TYPE_CURSOR;
	अन्यथा
		वापस DRM_PLANE_TYPE_OVERLAY;

पूर्ण

अटल पूर्णांक mtk_drm_crtc_init_comp_planes(काष्ठा drm_device *drm_dev,
					 काष्ठा mtk_drm_crtc *mtk_crtc,
					 पूर्णांक comp_idx, पूर्णांक pipe)
अणु
	पूर्णांक num_planes = mtk_drm_crtc_num_comp_planes(mtk_crtc, comp_idx);
	काष्ठा mtk_ddp_comp *comp = mtk_crtc->ddp_comp[comp_idx];
	पूर्णांक i, ret;

	क्रम (i = 0; i < num_planes; i++) अणु
		ret = mtk_plane_init(drm_dev,
				&mtk_crtc->planes[mtk_crtc->layer_nr],
				BIT(pipe),
				mtk_drm_crtc_plane_type(mtk_crtc->layer_nr,
							num_planes),
				mtk_ddp_comp_supported_rotations(comp));
		अगर (ret)
			वापस ret;

		mtk_crtc->layer_nr++;
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक mtk_drm_crtc_create(काष्ठा drm_device *drm_dev,
			स्थिर क्रमागत mtk_ddp_comp_id *path, अचिन्हित पूर्णांक path_len)
अणु
	काष्ठा mtk_drm_निजी *priv = drm_dev->dev_निजी;
	काष्ठा device *dev = drm_dev->dev;
	काष्ठा mtk_drm_crtc *mtk_crtc;
	अचिन्हित पूर्णांक num_comp_planes = 0;
	पूर्णांक pipe = priv->num_pipes;
	पूर्णांक ret;
	पूर्णांक i;
	bool has_cपंचांग = false;
	uपूर्णांक gamma_lut_size = 0;

	अगर (!path)
		वापस 0;

	क्रम (i = 0; i < path_len; i++) अणु
		क्रमागत mtk_ddp_comp_id comp_id = path[i];
		काष्ठा device_node *node;

		node = priv->comp_node[comp_id];
		अगर (!node) अणु
			dev_info(dev,
				 "Not creating crtc %d because component %d is disabled or missing\n",
				 pipe, comp_id);
			वापस 0;
		पूर्ण
	पूर्ण

	mtk_crtc = devm_kzalloc(dev, माप(*mtk_crtc), GFP_KERNEL);
	अगर (!mtk_crtc)
		वापस -ENOMEM;

	mtk_crtc->mmsys_dev = priv->mmsys_dev;
	mtk_crtc->ddp_comp_nr = path_len;
	mtk_crtc->ddp_comp = devm_kदो_स्मृति_array(dev, mtk_crtc->ddp_comp_nr,
						माप(*mtk_crtc->ddp_comp),
						GFP_KERNEL);
	अगर (!mtk_crtc->ddp_comp)
		वापस -ENOMEM;

	mtk_crtc->mutex = mtk_mutex_get(priv->mutex_dev);
	अगर (IS_ERR(mtk_crtc->mutex)) अणु
		ret = PTR_ERR(mtk_crtc->mutex);
		dev_err(dev, "Failed to get mutex: %d\n", ret);
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < mtk_crtc->ddp_comp_nr; i++) अणु
		क्रमागत mtk_ddp_comp_id comp_id = path[i];
		काष्ठा mtk_ddp_comp *comp;
		काष्ठा device_node *node;

		node = priv->comp_node[comp_id];
		comp = &priv->ddp_comp[comp_id];
		अगर (!comp) अणु
			dev_err(dev, "Component %pOF not initialized\n", node);
			ret = -ENODEV;
			वापस ret;
		पूर्ण

		mtk_crtc->ddp_comp[i] = comp;

		अगर (comp->funcs) अणु
			अगर (comp->funcs->gamma_set)
				gamma_lut_size = MTK_LUT_SIZE;

			अगर (comp->funcs->cपंचांग_set)
				has_cपंचांग = true;
		पूर्ण
	पूर्ण

	क्रम (i = 0; i < mtk_crtc->ddp_comp_nr; i++)
		num_comp_planes += mtk_drm_crtc_num_comp_planes(mtk_crtc, i);

	mtk_crtc->planes = devm_kसुस्मृति(dev, num_comp_planes,
					माप(काष्ठा drm_plane), GFP_KERNEL);

	क्रम (i = 0; i < mtk_crtc->ddp_comp_nr; i++) अणु
		ret = mtk_drm_crtc_init_comp_planes(drm_dev, mtk_crtc, i,
						    pipe);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = mtk_drm_crtc_init(drm_dev, mtk_crtc, pipe);
	अगर (ret < 0)
		वापस ret;

	अगर (gamma_lut_size)
		drm_mode_crtc_set_gamma_size(&mtk_crtc->base, gamma_lut_size);
	drm_crtc_enable_color_mgmt(&mtk_crtc->base, 0, has_cपंचांग, gamma_lut_size);
	priv->num_pipes++;
	mutex_init(&mtk_crtc->hw_lock);

#अगर IS_REACHABLE(CONFIG_MTK_CMDQ)
	mtk_crtc->cmdq_client =
			cmdq_mbox_create(mtk_crtc->mmsys_dev,
					 drm_crtc_index(&mtk_crtc->base));
	अगर (IS_ERR(mtk_crtc->cmdq_client)) अणु
		dev_dbg(dev, "mtk_crtc %d failed to create mailbox client, writing register by CPU now\n",
			drm_crtc_index(&mtk_crtc->base));
		mtk_crtc->cmdq_client = शून्य;
	पूर्ण

	अगर (mtk_crtc->cmdq_client) अणु
		ret = of_property_पढ़ो_u32_index(priv->mutex_node,
						 "mediatek,gce-events",
						 drm_crtc_index(&mtk_crtc->base),
						 &mtk_crtc->cmdq_event);
		अगर (ret) अणु
			dev_dbg(dev, "mtk_crtc %d failed to get mediatek,gce-events property\n",
				drm_crtc_index(&mtk_crtc->base));
			cmdq_mbox_destroy(mtk_crtc->cmdq_client);
			mtk_crtc->cmdq_client = शून्य;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
	वापस 0;
पूर्ण
