<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * (C) COPYRIGHT 2018 ARM Limited. All rights reserved.
 * Author: James.Qian.Wang <james.qian.wang@arm.com>
 *
 */
#समावेश <linux/component.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_atomic_helper.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_fb_helper.h>
#समावेश <drm/drm_gem_cma_helper.h>
#समावेश <drm/drm_gem_framebuffer_helper.h>
#समावेश <drm/drm_irq.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_probe_helper.h>
#समावेश <drm/drm_vblank.h>

#समावेश "komeda_dev.h"
#समावेश "komeda_framebuffer.h"
#समावेश "komeda_kms.h"

DEFINE_DRM_GEM_CMA_FOPS(komeda_cma_fops);

अटल पूर्णांक komeda_gem_cma_dumb_create(काष्ठा drm_file *file,
				      काष्ठा drm_device *dev,
				      काष्ठा drm_mode_create_dumb *args)
अणु
	काष्ठा komeda_dev *mdev = dev->dev_निजी;
	u32 pitch = DIV_ROUND_UP(args->width * args->bpp, 8);

	args->pitch = ALIGN(pitch, mdev->chip.bus_width);

	वापस drm_gem_cma_dumb_create_पूर्णांकernal(file, dev, args);
पूर्ण

अटल irqवापस_t komeda_kms_irq_handler(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा drm_device *drm = data;
	काष्ठा komeda_dev *mdev = drm->dev_निजी;
	काष्ठा komeda_kms_dev *kms = to_kdev(drm);
	काष्ठा komeda_events evts;
	irqवापस_t status;
	u32 i;

	/* Call पूर्णांकo the CHIP to recognize events */
	स_रखो(&evts, 0, माप(evts));
	status = mdev->funcs->irq_handler(mdev, &evts);

	komeda_prपूर्णांक_events(&evts, drm);

	/* Notअगरy the crtc to handle the events */
	क्रम (i = 0; i < kms->n_crtcs; i++)
		komeda_crtc_handle_event(&kms->crtcs[i], &evts);

	वापस status;
पूर्ण

अटल स्थिर काष्ठा drm_driver komeda_kms_driver = अणु
	.driver_features = DRIVER_GEM | DRIVER_MODESET | DRIVER_ATOMIC,
	.lastबंद			= drm_fb_helper_lastबंद,
	DRM_GEM_CMA_DRIVER_OPS_WITH_DUMB_CREATE(komeda_gem_cma_dumb_create),
	.fops = &komeda_cma_fops,
	.name = "komeda",
	.desc = "Arm Komeda Display Processor driver",
	.date = "20181101",
	.major = 0,
	.minor = 1,
पूर्ण;

अटल व्योम komeda_kms_commit_tail(काष्ठा drm_atomic_state *old_state)
अणु
	काष्ठा drm_device *dev = old_state->dev;
	bool fence_cookie = dma_fence_begin_संकेतling();

	drm_atomic_helper_commit_modeset_disables(dev, old_state);

	drm_atomic_helper_commit_planes(dev, old_state,
					DRM_PLANE_COMMIT_ACTIVE_ONLY);

	drm_atomic_helper_commit_modeset_enables(dev, old_state);

	drm_atomic_helper_commit_hw_करोne(old_state);

	drm_atomic_helper_रुको_क्रम_flip_करोne(dev, old_state);

	dma_fence_end_संकेतling(fence_cookie);

	drm_atomic_helper_cleanup_planes(dev, old_state);
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_helper_funcs komeda_mode_config_helpers = अणु
	.atomic_commit_tail = komeda_kms_commit_tail,
पूर्ण;

अटल पूर्णांक komeda_plane_state_list_add(काष्ठा drm_plane_state *plane_st,
				       काष्ठा list_head *zorder_list)
अणु
	काष्ठा komeda_plane_state *new = to_kplane_st(plane_st);
	काष्ठा komeda_plane_state *node, *last;

	last = list_empty(zorder_list) ?
	       शून्य : list_last_entry(zorder_list, typeof(*last), zlist_node);

	/* Considering the list sequence is zpos increasing, so अगर list is empty
	 * or the zpos of new node bigger than the last node in list, no need
	 * loop and just insert the new one to the tail of the list.
	 */
	अगर (!last || (new->base.zpos > last->base.zpos)) अणु
		list_add_tail(&new->zlist_node, zorder_list);
		वापस 0;
	पूर्ण

	/* Build the list by zpos increasing */
	list_क्रम_each_entry(node, zorder_list, zlist_node) अणु
		अगर (new->base.zpos < node->base.zpos) अणु
			list_add_tail(&new->zlist_node, &node->zlist_node);
			अवरोध;
		पूर्ण अन्यथा अगर (node->base.zpos == new->base.zpos) अणु
			काष्ठा drm_plane *a = node->base.plane;
			काष्ठा drm_plane *b = new->base.plane;

			/* Komeda करोesn't support setting a same zpos क्रम
			 * dअगरferent planes.
			 */
			DRM_DEBUG_ATOMIC("PLANE: %s and PLANE: %s are configured same zpos: %d.\n",
					 a->name, b->name, node->base.zpos);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक komeda_crtc_normalize_zpos(काष्ठा drm_crtc *crtc,
				      काष्ठा drm_crtc_state *crtc_st)
अणु
	काष्ठा drm_atomic_state *state = crtc_st->state;
	काष्ठा komeda_crtc *kcrtc = to_kcrtc(crtc);
	काष्ठा komeda_crtc_state *kcrtc_st = to_kcrtc_st(crtc_st);
	काष्ठा komeda_plane_state *kplane_st;
	काष्ठा drm_plane_state *plane_st;
	काष्ठा drm_plane *plane;
	काष्ठा list_head zorder_list;
	पूर्णांक order = 0, err;

	DRM_DEBUG_ATOMIC("[CRTC:%d:%s] calculating normalized zpos values\n",
			 crtc->base.id, crtc->name);

	INIT_LIST_HEAD(&zorder_list);

	/* This loop also added all effected planes पूर्णांकo the new state */
	drm_क्रम_each_plane_mask(plane, crtc->dev, crtc_st->plane_mask) अणु
		plane_st = drm_atomic_get_plane_state(state, plane);
		अगर (IS_ERR(plane_st))
			वापस PTR_ERR(plane_st);

		/* Build a list by zpos increasing */
		err = komeda_plane_state_list_add(plane_st, &zorder_list);
		अगर (err)
			वापस err;
	पूर्ण

	kcrtc_st->max_slave_zorder = 0;

	list_क्रम_each_entry(kplane_st, &zorder_list, zlist_node) अणु
		plane_st = &kplane_st->base;
		plane = plane_st->plane;

		plane_st->normalized_zpos = order++;
		/* When layer_split has been enabled, one plane will be handled
		 * by two separated komeda layers (left/right), which may needs
		 * two zorders.
		 * - zorder: क्रम left_layer क्रम left display part.
		 * - zorder + 1: will be reserved क्रम right layer.
		 */
		अगर (to_kplane_st(plane_st)->layer_split)
			order++;

		DRM_DEBUG_ATOMIC("[PLANE:%d:%s] zpos:%d, normalized zpos: %d\n",
				 plane->base.id, plane->name,
				 plane_st->zpos, plane_st->normalized_zpos);

		/* calculate max slave zorder */
		अगर (has_bit(drm_plane_index(plane), kcrtc->slave_planes))
			kcrtc_st->max_slave_zorder =
				max(plane_st->normalized_zpos,
				    kcrtc_st->max_slave_zorder);
	पूर्ण

	crtc_st->zpos_changed = true;

	वापस 0;
पूर्ण

अटल पूर्णांक komeda_kms_check(काष्ठा drm_device *dev,
			    काष्ठा drm_atomic_state *state)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_crtc_state *new_crtc_st;
	पूर्णांक i, err;

	err = drm_atomic_helper_check_modeset(dev, state);
	अगर (err)
		वापस err;

	/* Komeda need to re-calculate resource assumption in every commit
	 * so need to add all affected_planes (even unchanged) to
	 * drm_atomic_state.
	 */
	क्रम_each_new_crtc_in_state(state, crtc, new_crtc_st, i) अणु
		err = drm_atomic_add_affected_planes(state, crtc);
		अगर (err)
			वापस err;

		err = komeda_crtc_normalize_zpos(crtc, new_crtc_st);
		अगर (err)
			वापस err;
	पूर्ण

	err = drm_atomic_helper_check_planes(dev, state);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा drm_mode_config_funcs komeda_mode_config_funcs = अणु
	.fb_create		= komeda_fb_create,
	.atomic_check		= komeda_kms_check,
	.atomic_commit		= drm_atomic_helper_commit,
पूर्ण;

अटल व्योम komeda_kms_mode_config_init(काष्ठा komeda_kms_dev *kms,
					काष्ठा komeda_dev *mdev)
अणु
	काष्ठा drm_mode_config *config = &kms->base.mode_config;

	drm_mode_config_init(&kms->base);

	komeda_kms_setup_crtcs(kms, mdev);

	/* Get value from dev */
	config->min_width	= 0;
	config->min_height	= 0;
	config->max_width	= 4096;
	config->max_height	= 4096;
	config->allow_fb_modअगरiers = true;

	config->funcs = &komeda_mode_config_funcs;
	config->helper_निजी = &komeda_mode_config_helpers;
पूर्ण

काष्ठा komeda_kms_dev *komeda_kms_attach(काष्ठा komeda_dev *mdev)
अणु
	काष्ठा komeda_kms_dev *kms;
	काष्ठा drm_device *drm;
	पूर्णांक err;

	kms = devm_drm_dev_alloc(mdev->dev, &komeda_kms_driver,
				 काष्ठा komeda_kms_dev, base);
	अगर (IS_ERR(kms))
		वापस kms;

	drm = &kms->base;

	drm->dev_निजी = mdev;

	komeda_kms_mode_config_init(kms, mdev);

	err = komeda_kms_add_निजी_objs(kms, mdev);
	अगर (err)
		जाओ cleanup_mode_config;

	err = komeda_kms_add_planes(kms, mdev);
	अगर (err)
		जाओ cleanup_mode_config;

	err = drm_vblank_init(drm, kms->n_crtcs);
	अगर (err)
		जाओ cleanup_mode_config;

	err = komeda_kms_add_crtcs(kms, mdev);
	अगर (err)
		जाओ cleanup_mode_config;

	err = komeda_kms_add_wb_connectors(kms, mdev);
	अगर (err)
		जाओ cleanup_mode_config;

	err = component_bind_all(mdev->dev, kms);
	अगर (err)
		जाओ cleanup_mode_config;

	drm_mode_config_reset(drm);

	err = devm_request_irq(drm->dev, mdev->irq,
			       komeda_kms_irq_handler, IRQF_SHARED,
			       drm->driver->name, drm);
	अगर (err)
		जाओ मुक्त_component_binding;

	drm->irq_enabled = true;

	drm_kms_helper_poll_init(drm);

	err = drm_dev_रेजिस्टर(drm, 0);
	अगर (err)
		जाओ मुक्त_पूर्णांकerrupts;

	वापस kms;

मुक्त_पूर्णांकerrupts:
	drm_kms_helper_poll_fini(drm);
	drm->irq_enabled = false;
मुक्त_component_binding:
	component_unbind_all(mdev->dev, drm);
cleanup_mode_config:
	drm_mode_config_cleanup(drm);
	komeda_kms_cleanup_निजी_objs(kms);
	drm->dev_निजी = शून्य;
	वापस ERR_PTR(err);
पूर्ण

व्योम komeda_kms_detach(काष्ठा komeda_kms_dev *kms)
अणु
	काष्ठा drm_device *drm = &kms->base;
	काष्ठा komeda_dev *mdev = drm->dev_निजी;

	drm_dev_unरेजिस्टर(drm);
	drm_kms_helper_poll_fini(drm);
	drm_atomic_helper_shutकरोwn(drm);
	drm->irq_enabled = false;
	component_unbind_all(mdev->dev, drm);
	drm_mode_config_cleanup(drm);
	komeda_kms_cleanup_निजी_objs(kms);
	drm->dev_निजी = शून्य;
पूर्ण
