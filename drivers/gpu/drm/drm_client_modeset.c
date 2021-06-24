<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright 2018 Noralf Trथचnnes
 * Copyright (c) 2006-2009 Red Hat Inc.
 * Copyright (c) 2006-2008 Intel Corporation
 *   Jesse Barnes <jesse.barnes@पूर्णांकel.com>
 * Copyright (c) 2007 Dave Airlie <airlied@linux.ie>
 */

#समावेश "drm/drm_modeset_lock.h"
#समावेश <linux/module.h>
#समावेश <linux/mutex.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_atomic.h>
#समावेश <drm/drm_client.h>
#समावेश <drm/drm_connector.h>
#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_device.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_encoder.h>
#समावेश <drm/drm_prपूर्णांक.h>

#समावेश "drm_crtc_internal.h"
#समावेश "drm_internal.h"

#घोषणा DRM_CLIENT_MAX_CLONED_CONNECTORS	8

काष्ठा drm_client_offset अणु
	पूर्णांक x, y;
पूर्ण;

पूर्णांक drm_client_modeset_create(काष्ठा drm_client_dev *client)
अणु
	काष्ठा drm_device *dev = client->dev;
	अचिन्हित पूर्णांक num_crtc = dev->mode_config.num_crtc;
	अचिन्हित पूर्णांक max_connector_count = 1;
	काष्ठा drm_mode_set *modeset;
	काष्ठा drm_crtc *crtc;
	अचिन्हित पूर्णांक i = 0;

	/* Add terminating zero entry to enable index less iteration */
	client->modesets = kसुस्मृति(num_crtc + 1, माप(*client->modesets), GFP_KERNEL);
	अगर (!client->modesets)
		वापस -ENOMEM;

	mutex_init(&client->modeset_mutex);

	drm_क्रम_each_crtc(crtc, dev)
		client->modesets[i++].crtc = crtc;

	/* Cloning is only supported in the single crtc हाल. */
	अगर (num_crtc == 1)
		max_connector_count = DRM_CLIENT_MAX_CLONED_CONNECTORS;

	क्रम (modeset = client->modesets; modeset->crtc; modeset++) अणु
		modeset->connectors = kसुस्मृति(max_connector_count,
					      माप(*modeset->connectors), GFP_KERNEL);
		अगर (!modeset->connectors)
			जाओ err_मुक्त;
	पूर्ण

	वापस 0;

err_मुक्त:
	drm_client_modeset_मुक्त(client);

	वापस -ENOMEM;
पूर्ण

अटल व्योम drm_client_modeset_release(काष्ठा drm_client_dev *client)
अणु
	काष्ठा drm_mode_set *modeset;
	अचिन्हित पूर्णांक i;

	drm_client_क्रम_each_modeset(modeset, client) अणु
		drm_mode_destroy(client->dev, modeset->mode);
		modeset->mode = शून्य;
		modeset->fb = शून्य;

		क्रम (i = 0; i < modeset->num_connectors; i++) अणु
			drm_connector_put(modeset->connectors[i]);
			modeset->connectors[i] = शून्य;
		पूर्ण
		modeset->num_connectors = 0;
	पूर्ण
पूर्ण

व्योम drm_client_modeset_मुक्त(काष्ठा drm_client_dev *client)
अणु
	काष्ठा drm_mode_set *modeset;

	mutex_lock(&client->modeset_mutex);

	drm_client_modeset_release(client);

	drm_client_क्रम_each_modeset(modeset, client)
		kमुक्त(modeset->connectors);

	mutex_unlock(&client->modeset_mutex);

	mutex_destroy(&client->modeset_mutex);
	kमुक्त(client->modesets);
पूर्ण

अटल काष्ठा drm_mode_set *
drm_client_find_modeset(काष्ठा drm_client_dev *client, काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_mode_set *modeset;

	drm_client_क्रम_each_modeset(modeset, client)
		अगर (modeset->crtc == crtc)
			वापस modeset;

	वापस शून्य;
पूर्ण

अटल काष्ठा drm_display_mode *
drm_connector_get_tiled_mode(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	list_क्रम_each_entry(mode, &connector->modes, head) अणु
		अगर (mode->hdisplay == connector->tile_h_size &&
		    mode->vdisplay == connector->tile_v_size)
			वापस mode;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा drm_display_mode *
drm_connector_fallback_non_tiled_mode(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_display_mode *mode;

	list_क्रम_each_entry(mode, &connector->modes, head) अणु
		अगर (mode->hdisplay == connector->tile_h_size &&
		    mode->vdisplay == connector->tile_v_size)
			जारी;
		वापस mode;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा drm_display_mode *
drm_connector_has_preferred_mode(काष्ठा drm_connector *connector, पूर्णांक width, पूर्णांक height)
अणु
	काष्ठा drm_display_mode *mode;

	list_क्रम_each_entry(mode, &connector->modes, head) अणु
		अगर (mode->hdisplay > width ||
		    mode->vdisplay > height)
			जारी;
		अगर (mode->type & DRM_MODE_TYPE_PREFERRED)
			वापस mode;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा drm_display_mode *
drm_connector_pick_cmdline_mode(काष्ठा drm_connector *connector)
अणु
	काष्ठा drm_cmdline_mode *cmdline_mode;
	काष्ठा drm_display_mode *mode;
	bool prefer_non_पूर्णांकerlace;

	cmdline_mode = &connector->cmdline_mode;
	अगर (cmdline_mode->specअगरied == false)
		वापस शून्य;

	/* attempt to find a matching mode in the list of modes
	 *  we have gotten so far, अगर not add a CVT mode that conक्रमms
	 */
	अगर (cmdline_mode->rb || cmdline_mode->margins)
		जाओ create_mode;

	prefer_non_पूर्णांकerlace = !cmdline_mode->पूर्णांकerlace;
again:
	list_क्रम_each_entry(mode, &connector->modes, head) अणु
		/* Check (optional) mode name first */
		अगर (!म_भेद(mode->name, cmdline_mode->name))
			वापस mode;

		/* check width/height */
		अगर (mode->hdisplay != cmdline_mode->xres ||
		    mode->vdisplay != cmdline_mode->yres)
			जारी;

		अगर (cmdline_mode->refresh_specअगरied) अणु
			अगर (drm_mode_vrefresh(mode) != cmdline_mode->refresh)
				जारी;
		पूर्ण

		अगर (cmdline_mode->पूर्णांकerlace) अणु
			अगर (!(mode->flags & DRM_MODE_FLAG_INTERLACE))
				जारी;
		पूर्ण अन्यथा अगर (prefer_non_पूर्णांकerlace) अणु
			अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
				जारी;
		पूर्ण
		वापस mode;
	पूर्ण

	अगर (prefer_non_पूर्णांकerlace) अणु
		prefer_non_पूर्णांकerlace = false;
		जाओ again;
	पूर्ण

create_mode:
	mode = drm_mode_create_from_cmdline_mode(connector->dev, cmdline_mode);
	अगर (mode)
		list_add(&mode->head, &connector->modes);

	वापस mode;
पूर्ण

अटल bool drm_connector_enabled(काष्ठा drm_connector *connector, bool strict)
अणु
	bool enable;

	अगर (connector->display_info.non_desktop)
		वापस false;

	अगर (strict)
		enable = connector->status == connector_status_connected;
	अन्यथा
		enable = connector->status != connector_status_disconnected;

	वापस enable;
पूर्ण

अटल व्योम drm_client_connectors_enabled(काष्ठा drm_connector **connectors,
					  अचिन्हित पूर्णांक connector_count,
					  bool *enabled)
अणु
	bool any_enabled = false;
	काष्ठा drm_connector *connector;
	पूर्णांक i = 0;

	क्रम (i = 0; i < connector_count; i++) अणु
		connector = connectors[i];
		enabled[i] = drm_connector_enabled(connector, true);
		DRM_DEBUG_KMS("connector %d enabled? %s\n", connector->base.id,
			      connector->display_info.non_desktop ? "non desktop" : enabled[i] ? "yes" : "no");

		any_enabled |= enabled[i];
	पूर्ण

	अगर (any_enabled)
		वापस;

	क्रम (i = 0; i < connector_count; i++)
		enabled[i] = drm_connector_enabled(connectors[i], false);
पूर्ण

अटल bool drm_client_target_cloned(काष्ठा drm_device *dev,
				     काष्ठा drm_connector **connectors,
				     अचिन्हित पूर्णांक connector_count,
				     काष्ठा drm_display_mode **modes,
				     काष्ठा drm_client_offset *offsets,
				     bool *enabled, पूर्णांक width, पूर्णांक height)
अणु
	पूर्णांक count, i, j;
	bool can_clone = false;
	काष्ठा drm_display_mode *dmt_mode, *mode;

	/* only conढाँचा cloning in the single crtc हाल */
	अगर (dev->mode_config.num_crtc > 1)
		वापस false;

	count = 0;
	क्रम (i = 0; i < connector_count; i++) अणु
		अगर (enabled[i])
			count++;
	पूर्ण

	/* only conढाँचा cloning अगर more than one connector is enabled */
	अगर (count <= 1)
		वापस false;

	/* check the command line or अगर nothing common pick 1024x768 */
	can_clone = true;
	क्रम (i = 0; i < connector_count; i++) अणु
		अगर (!enabled[i])
			जारी;
		modes[i] = drm_connector_pick_cmdline_mode(connectors[i]);
		अगर (!modes[i]) अणु
			can_clone = false;
			अवरोध;
		पूर्ण
		क्रम (j = 0; j < i; j++) अणु
			अगर (!enabled[j])
				जारी;
			अगर (!drm_mode_match(modes[j], modes[i],
					    DRM_MODE_MATCH_TIMINGS |
					    DRM_MODE_MATCH_CLOCK |
					    DRM_MODE_MATCH_FLAGS |
					    DRM_MODE_MATCH_3D_FLAGS))
				can_clone = false;
		पूर्ण
	पूर्ण

	अगर (can_clone) अणु
		DRM_DEBUG_KMS("can clone using command line\n");
		वापस true;
	पूर्ण

	/* try and find a 1024x768 mode on each connector */
	can_clone = true;
	dmt_mode = drm_mode_find_dmt(dev, 1024, 768, 60, false);

	क्रम (i = 0; i < connector_count; i++) अणु
		अगर (!enabled[i])
			जारी;

		list_क्रम_each_entry(mode, &connectors[i]->modes, head) अणु
			अगर (drm_mode_match(mode, dmt_mode,
					   DRM_MODE_MATCH_TIMINGS |
					   DRM_MODE_MATCH_CLOCK |
					   DRM_MODE_MATCH_FLAGS |
					   DRM_MODE_MATCH_3D_FLAGS))
				modes[i] = mode;
		पूर्ण
		अगर (!modes[i])
			can_clone = false;
	पूर्ण

	अगर (can_clone) अणु
		DRM_DEBUG_KMS("can clone using 1024x768\n");
		वापस true;
	पूर्ण
	DRM_INFO("kms: can't enable cloning when we probably wanted to.\n");
	वापस false;
पूर्ण

अटल पूर्णांक drm_client_get_tile_offsets(काष्ठा drm_connector **connectors,
				       अचिन्हित पूर्णांक connector_count,
				       काष्ठा drm_display_mode **modes,
				       काष्ठा drm_client_offset *offsets,
				       पूर्णांक idx,
				       पूर्णांक h_idx, पूर्णांक v_idx)
अणु
	काष्ठा drm_connector *connector;
	पूर्णांक i;
	पूर्णांक hoffset = 0, voffset = 0;

	क्रम (i = 0; i < connector_count; i++) अणु
		connector = connectors[i];
		अगर (!connector->has_tile)
			जारी;

		अगर (!modes[i] && (h_idx || v_idx)) अणु
			DRM_DEBUG_KMS("no modes for connector tiled %d %d\n", i,
				      connector->base.id);
			जारी;
		पूर्ण
		अगर (connector->tile_h_loc < h_idx)
			hoffset += modes[i]->hdisplay;

		अगर (connector->tile_v_loc < v_idx)
			voffset += modes[i]->vdisplay;
	पूर्ण
	offsets[idx].x = hoffset;
	offsets[idx].y = voffset;
	DRM_DEBUG_KMS("returned %d %d for %d %d\n", hoffset, voffset, h_idx, v_idx);
	वापस 0;
पूर्ण

अटल bool drm_client_target_preferred(काष्ठा drm_connector **connectors,
					अचिन्हित पूर्णांक connector_count,
					काष्ठा drm_display_mode **modes,
					काष्ठा drm_client_offset *offsets,
					bool *enabled, पूर्णांक width, पूर्णांक height)
अणु
	स्थिर u64 mask = BIT_ULL(connector_count) - 1;
	काष्ठा drm_connector *connector;
	u64 conn_configured = 0;
	पूर्णांक tile_pass = 0;
	पूर्णांक num_tiled_conns = 0;
	पूर्णांक i;

	क्रम (i = 0; i < connector_count; i++) अणु
		अगर (connectors[i]->has_tile &&
		    connectors[i]->status == connector_status_connected)
			num_tiled_conns++;
	पूर्ण

retry:
	क्रम (i = 0; i < connector_count; i++) अणु
		connector = connectors[i];

		अगर (conn_configured & BIT_ULL(i))
			जारी;

		अगर (enabled[i] == false) अणु
			conn_configured |= BIT_ULL(i);
			जारी;
		पूर्ण

		/* first pass over all the untiled connectors */
		अगर (tile_pass == 0 && connector->has_tile)
			जारी;

		अगर (tile_pass == 1) अणु
			अगर (connector->tile_h_loc != 0 ||
			    connector->tile_v_loc != 0)
				जारी;

		पूर्ण अन्यथा अणु
			अगर (connector->tile_h_loc != tile_pass - 1 &&
			    connector->tile_v_loc != tile_pass - 1)
			/* अगर this tile_pass करोesn't cover any of the tiles - keep going */
				जारी;

			/*
			 * find the tile offsets क्रम this pass - need to find
			 * all tiles left and above
			 */
			drm_client_get_tile_offsets(connectors, connector_count, modes, offsets, i,
						    connector->tile_h_loc, connector->tile_v_loc);
		पूर्ण
		DRM_DEBUG_KMS("looking for cmdline mode on connector %d\n",
			      connector->base.id);

		/* got क्रम command line mode first */
		modes[i] = drm_connector_pick_cmdline_mode(connector);
		अगर (!modes[i]) अणु
			DRM_DEBUG_KMS("looking for preferred mode on connector %d %d\n",
				      connector->base.id, connector->tile_group ? connector->tile_group->id : 0);
			modes[i] = drm_connector_has_preferred_mode(connector, width, height);
		पूर्ण
		/* No preferred modes, pick one off the list */
		अगर (!modes[i] && !list_empty(&connector->modes)) अणु
			list_क्रम_each_entry(modes[i], &connector->modes, head)
				अवरोध;
		पूर्ण
		/*
		 * In हाल of tiled mode अगर all tiles not present fallback to
		 * first available non tiled mode.
		 * After all tiles are present, try to find the tiled mode
		 * क्रम all and अगर tiled mode not present due to fbcon size
		 * limitations, use first non tiled mode only क्रम
		 * tile 0,0 and set to no mode क्रम all other tiles.
		 */
		अगर (connector->has_tile) अणु
			अगर (num_tiled_conns <
			    connector->num_h_tile * connector->num_v_tile ||
			    (connector->tile_h_loc == 0 &&
			     connector->tile_v_loc == 0 &&
			     !drm_connector_get_tiled_mode(connector))) अणु
				DRM_DEBUG_KMS("Falling back to non tiled mode on Connector %d\n",
					      connector->base.id);
				modes[i] = drm_connector_fallback_non_tiled_mode(connector);
			पूर्ण अन्यथा अणु
				modes[i] = drm_connector_get_tiled_mode(connector);
			पूर्ण
		पूर्ण

		DRM_DEBUG_KMS("found mode %s\n", modes[i] ? modes[i]->name :
			  "none");
		conn_configured |= BIT_ULL(i);
	पूर्ण

	अगर ((conn_configured & mask) != mask) अणु
		tile_pass++;
		जाओ retry;
	पूर्ण
	वापस true;
पूर्ण

अटल bool connector_has_possible_crtc(काष्ठा drm_connector *connector,
					काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_encoder *encoder;

	drm_connector_क्रम_each_possible_encoder(connector, encoder) अणु
		अगर (encoder->possible_crtcs & drm_crtc_mask(crtc))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक drm_client_pick_crtcs(काष्ठा drm_client_dev *client,
				 काष्ठा drm_connector **connectors,
				 अचिन्हित पूर्णांक connector_count,
				 काष्ठा drm_crtc **best_crtcs,
				 काष्ठा drm_display_mode **modes,
				 पूर्णांक n, पूर्णांक width, पूर्णांक height)
अणु
	काष्ठा drm_device *dev = client->dev;
	काष्ठा drm_connector *connector;
	पूर्णांक my_score, best_score, score;
	काष्ठा drm_crtc **crtcs, *crtc;
	काष्ठा drm_mode_set *modeset;
	पूर्णांक o;

	अगर (n == connector_count)
		वापस 0;

	connector = connectors[n];

	best_crtcs[n] = शून्य;
	best_score = drm_client_pick_crtcs(client, connectors, connector_count,
					   best_crtcs, modes, n + 1, width, height);
	अगर (modes[n] == शून्य)
		वापस best_score;

	crtcs = kसुस्मृति(connector_count, माप(*crtcs), GFP_KERNEL);
	अगर (!crtcs)
		वापस best_score;

	my_score = 1;
	अगर (connector->status == connector_status_connected)
		my_score++;
	अगर (connector->cmdline_mode.specअगरied)
		my_score++;
	अगर (drm_connector_has_preferred_mode(connector, width, height))
		my_score++;

	/*
	 * select a crtc क्रम this connector and then attempt to configure
	 * reमुख्यing connectors
	 */
	drm_client_क्रम_each_modeset(modeset, client) अणु
		crtc = modeset->crtc;

		अगर (!connector_has_possible_crtc(connector, crtc))
			जारी;

		क्रम (o = 0; o < n; o++)
			अगर (best_crtcs[o] == crtc)
				अवरोध;

		अगर (o < n) अणु
			/* ignore cloning unless only a single crtc */
			अगर (dev->mode_config.num_crtc > 1)
				जारी;

			अगर (!drm_mode_equal(modes[o], modes[n]))
				जारी;
		पूर्ण

		crtcs[n] = crtc;
		स_नकल(crtcs, best_crtcs, n * माप(*crtcs));
		score = my_score + drm_client_pick_crtcs(client, connectors, connector_count,
							 crtcs, modes, n + 1, width, height);
		अगर (score > best_score) अणु
			best_score = score;
			स_नकल(best_crtcs, crtcs, connector_count * माप(*crtcs));
		पूर्ण
	पूर्ण

	kमुक्त(crtcs);
	वापस best_score;
पूर्ण

/* Try to पढ़ो the BIOS display configuration and use it क्रम the initial config */
अटल bool drm_client_firmware_config(काष्ठा drm_client_dev *client,
				       काष्ठा drm_connector **connectors,
				       अचिन्हित पूर्णांक connector_count,
				       काष्ठा drm_crtc **crtcs,
				       काष्ठा drm_display_mode **modes,
				       काष्ठा drm_client_offset *offsets,
				       bool *enabled, पूर्णांक width, पूर्णांक height)
अणु
	स्थिर पूर्णांक count = min_t(अचिन्हित पूर्णांक, connector_count, BITS_PER_LONG);
	अचिन्हित दीर्घ conn_configured, conn_seq, mask;
	काष्ठा drm_device *dev = client->dev;
	पूर्णांक i, j;
	bool *save_enabled;
	bool fallback = true, ret = true;
	पूर्णांक num_connectors_enabled = 0;
	पूर्णांक num_connectors_detected = 0;
	पूर्णांक num_tiled_conns = 0;
	काष्ठा drm_modeset_acquire_ctx ctx;

	अगर (!drm_drv_uses_atomic_modeset(dev))
		वापस false;

	अगर (WARN_ON(count <= 0))
		वापस false;

	save_enabled = kसुस्मृति(count, माप(bool), GFP_KERNEL);
	अगर (!save_enabled)
		वापस false;

	drm_modeset_acquire_init(&ctx, 0);

	जबतक (drm_modeset_lock_all_ctx(dev, &ctx) != 0)
		drm_modeset_backoff(&ctx);

	स_नकल(save_enabled, enabled, count);
	mask = GENMASK(count - 1, 0);
	conn_configured = 0;
	क्रम (i = 0; i < count; i++) अणु
		अगर (connectors[i]->has_tile &&
		    connectors[i]->status == connector_status_connected)
			num_tiled_conns++;
	पूर्ण
retry:
	conn_seq = conn_configured;
	क्रम (i = 0; i < count; i++) अणु
		काष्ठा drm_connector *connector;
		काष्ठा drm_encoder *encoder;
		काष्ठा drm_crtc *new_crtc;

		connector = connectors[i];

		अगर (conn_configured & BIT(i))
			जारी;

		अगर (conn_seq == 0 && !connector->has_tile)
			जारी;

		अगर (connector->status == connector_status_connected)
			num_connectors_detected++;

		अगर (!enabled[i]) अणु
			DRM_DEBUG_KMS("connector %s not enabled, skipping\n",
				      connector->name);
			conn_configured |= BIT(i);
			जारी;
		पूर्ण

		अगर (connector->क्रमce == DRM_FORCE_OFF) अणु
			DRM_DEBUG_KMS("connector %s is disabled by user, skipping\n",
				      connector->name);
			enabled[i] = false;
			जारी;
		पूर्ण

		encoder = connector->state->best_encoder;
		अगर (!encoder || WARN_ON(!connector->state->crtc)) अणु
			अगर (connector->क्रमce > DRM_FORCE_OFF)
				जाओ bail;

			DRM_DEBUG_KMS("connector %s has no encoder or crtc, skipping\n",
				      connector->name);
			enabled[i] = false;
			conn_configured |= BIT(i);
			जारी;
		पूर्ण

		num_connectors_enabled++;

		new_crtc = connector->state->crtc;

		/*
		 * Make sure we're not trying to drive multiple connectors
		 * with a single CRTC, since our cloning support may not
		 * match the BIOS.
		 */
		क्रम (j = 0; j < count; j++) अणु
			अगर (crtcs[j] == new_crtc) अणु
				DRM_DEBUG_KMS("fallback: cloned configuration\n");
				जाओ bail;
			पूर्ण
		पूर्ण

		DRM_DEBUG_KMS("looking for cmdline mode on connector %s\n",
			      connector->name);

		/* go क्रम command line mode first */
		modes[i] = drm_connector_pick_cmdline_mode(connector);

		/* try क्रम preferred next */
		अगर (!modes[i]) अणु
			DRM_DEBUG_KMS("looking for preferred mode on connector %s %d\n",
				      connector->name, connector->has_tile);
			modes[i] = drm_connector_has_preferred_mode(connector, width, height);
		पूर्ण

		/* No preferred mode marked by the EDID? Are there any modes? */
		अगर (!modes[i] && !list_empty(&connector->modes)) अणु
			DRM_DEBUG_KMS("using first mode listed on connector %s\n",
				      connector->name);
			modes[i] = list_first_entry(&connector->modes,
						    काष्ठा drm_display_mode,
						    head);
		पूर्ण

		/* last resort: use current mode */
		अगर (!modes[i]) अणु
			/*
			 * IMPORTANT: We want to use the adjusted mode (i.e.
			 * after the panel fitter upscaling) as the initial
			 * config, not the input mode, which is what crtc->mode
			 * usually contains. But since our current
			 * code माला_दो a mode derived from the post-pfit timings
			 * पूर्णांकo crtc->mode this works out correctly.
			 *
			 * This is crtc->mode and not crtc->state->mode क्रम the
			 * fastboot check to work correctly.
			 */
			DRM_DEBUG_KMS("looking for current mode on connector %s\n",
				      connector->name);
			modes[i] = &connector->state->crtc->mode;
		पूर्ण
		/*
		 * In हाल of tiled modes, अगर all tiles are not present
		 * then fallback to a non tiled mode.
		 */
		अगर (connector->has_tile &&
		    num_tiled_conns < connector->num_h_tile * connector->num_v_tile) अणु
			DRM_DEBUG_KMS("Falling back to non tiled mode on Connector %d\n",
				      connector->base.id);
			modes[i] = drm_connector_fallback_non_tiled_mode(connector);
		पूर्ण
		crtcs[i] = new_crtc;

		DRM_DEBUG_KMS("connector %s on [CRTC:%d:%s]: %dx%d%s\n",
			      connector->name,
			      connector->state->crtc->base.id,
			      connector->state->crtc->name,
			      modes[i]->hdisplay, modes[i]->vdisplay,
			      modes[i]->flags & DRM_MODE_FLAG_INTERLACE ? "i" : "");

		fallback = false;
		conn_configured |= BIT(i);
	पूर्ण

	अगर ((conn_configured & mask) != mask && conn_configured != conn_seq)
		जाओ retry;

	/*
	 * If the BIOS didn't enable everything it could, fall back to have the
	 * same user experiencing of lighting up as much as possible like the
	 * fbdev helper library.
	 */
	अगर (num_connectors_enabled != num_connectors_detected &&
	    num_connectors_enabled < dev->mode_config.num_crtc) अणु
		DRM_DEBUG_KMS("fallback: Not all outputs enabled\n");
		DRM_DEBUG_KMS("Enabled: %i, detected: %i\n", num_connectors_enabled,
			      num_connectors_detected);
		fallback = true;
	पूर्ण

	अगर (fallback) अणु
bail:
		DRM_DEBUG_KMS("Not using firmware configuration\n");
		स_नकल(enabled, save_enabled, count);
		ret = false;
	पूर्ण

	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	kमुक्त(save_enabled);
	वापस ret;
पूर्ण

/**
 * drm_client_modeset_probe() - Probe क्रम displays
 * @client: DRM client
 * @width: Maximum display mode width (optional)
 * @height: Maximum display mode height (optional)
 *
 * This function sets up display pipelines क्रम enabled connectors and stores the
 * config in the client's modeset array.
 *
 * Returns:
 * Zero on success or negative error code on failure.
 */
पूर्णांक drm_client_modeset_probe(काष्ठा drm_client_dev *client, अचिन्हित पूर्णांक width, अचिन्हित पूर्णांक height)
अणु
	काष्ठा drm_connector *connector, **connectors = शून्य;
	काष्ठा drm_connector_list_iter conn_iter;
	काष्ठा drm_device *dev = client->dev;
	अचिन्हित पूर्णांक total_modes_count = 0;
	काष्ठा drm_client_offset *offsets;
	अचिन्हित पूर्णांक connector_count = 0;
	काष्ठा drm_display_mode **modes;
	काष्ठा drm_crtc **crtcs;
	पूर्णांक i, ret = 0;
	bool *enabled;

	DRM_DEBUG_KMS("\n");

	अगर (!width)
		width = dev->mode_config.max_width;
	अगर (!height)
		height = dev->mode_config.max_height;

	drm_connector_list_iter_begin(dev, &conn_iter);
	drm_client_क्रम_each_connector_iter(connector, &conn_iter) अणु
		काष्ठा drm_connector **पंचांगp;

		पंचांगp = kपुनः_स्मृति(connectors, (connector_count + 1) * माप(*connectors), GFP_KERNEL);
		अगर (!पंचांगp) अणु
			ret = -ENOMEM;
			जाओ मुक्त_connectors;
		पूर्ण

		connectors = पंचांगp;
		drm_connector_get(connector);
		connectors[connector_count++] = connector;
	पूर्ण
	drm_connector_list_iter_end(&conn_iter);

	अगर (!connector_count)
		वापस 0;

	crtcs = kसुस्मृति(connector_count, माप(*crtcs), GFP_KERNEL);
	modes = kसुस्मृति(connector_count, माप(*modes), GFP_KERNEL);
	offsets = kसुस्मृति(connector_count, माप(*offsets), GFP_KERNEL);
	enabled = kसुस्मृति(connector_count, माप(bool), GFP_KERNEL);
	अगर (!crtcs || !modes || !enabled || !offsets) अणु
		DRM_ERROR("Memory allocation failed\n");
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	mutex_lock(&client->modeset_mutex);

	mutex_lock(&dev->mode_config.mutex);
	क्रम (i = 0; i < connector_count; i++)
		total_modes_count += connectors[i]->funcs->fill_modes(connectors[i], width, height);
	अगर (!total_modes_count)
		DRM_DEBUG_KMS("No connectors reported connected with modes\n");
	drm_client_connectors_enabled(connectors, connector_count, enabled);

	अगर (!drm_client_firmware_config(client, connectors, connector_count, crtcs,
					modes, offsets, enabled, width, height)) अणु
		स_रखो(modes, 0, connector_count * माप(*modes));
		स_रखो(crtcs, 0, connector_count * माप(*crtcs));
		स_रखो(offsets, 0, connector_count * माप(*offsets));

		अगर (!drm_client_target_cloned(dev, connectors, connector_count, modes,
					      offsets, enabled, width, height) &&
		    !drm_client_target_preferred(connectors, connector_count, modes,
						 offsets, enabled, width, height))
			DRM_ERROR("Unable to find initial modes\n");

		DRM_DEBUG_KMS("picking CRTCs for %dx%d config\n",
			      width, height);

		drm_client_pick_crtcs(client, connectors, connector_count,
				      crtcs, modes, 0, width, height);
	पूर्ण
	mutex_unlock(&dev->mode_config.mutex);

	drm_client_modeset_release(client);

	क्रम (i = 0; i < connector_count; i++) अणु
		काष्ठा drm_display_mode *mode = modes[i];
		काष्ठा drm_crtc *crtc = crtcs[i];
		काष्ठा drm_client_offset *offset = &offsets[i];

		अगर (mode && crtc) अणु
			काष्ठा drm_mode_set *modeset = drm_client_find_modeset(client, crtc);
			काष्ठा drm_connector *connector = connectors[i];

			DRM_DEBUG_KMS("desired mode %s set on crtc %d (%d,%d)\n",
				      mode->name, crtc->base.id, offset->x, offset->y);

			अगर (WARN_ON_ONCE(modeset->num_connectors == DRM_CLIENT_MAX_CLONED_CONNECTORS ||
					 (dev->mode_config.num_crtc > 1 && modeset->num_connectors == 1))) अणु
				ret = -EINVAL;
				अवरोध;
			पूर्ण

			modeset->mode = drm_mode_duplicate(dev, mode);
			drm_connector_get(connector);
			modeset->connectors[modeset->num_connectors++] = connector;
			modeset->x = offset->x;
			modeset->y = offset->y;
		पूर्ण
	पूर्ण

	mutex_unlock(&client->modeset_mutex);
out:
	kमुक्त(crtcs);
	kमुक्त(modes);
	kमुक्त(offsets);
	kमुक्त(enabled);
मुक्त_connectors:
	क्रम (i = 0; i < connector_count; i++)
		drm_connector_put(connectors[i]);
	kमुक्त(connectors);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_client_modeset_probe);

/**
 * drm_client_rotation() - Check the initial rotation value
 * @modeset: DRM modeset
 * @rotation: Returned rotation value
 *
 * This function checks अगर the primary plane in @modeset can hw rotate
 * to match the rotation needed on its connector.
 *
 * Note: Currently only 0 and 180 degrees are supported.
 *
 * Return:
 * True अगर the plane can करो the rotation, false otherwise.
 */
bool drm_client_rotation(काष्ठा drm_mode_set *modeset, अचिन्हित पूर्णांक *rotation)
अणु
	काष्ठा drm_connector *connector = modeset->connectors[0];
	काष्ठा drm_plane *plane = modeset->crtc->primary;
	काष्ठा drm_cmdline_mode *cmdline;
	u64 valid_mask = 0;
	अचिन्हित पूर्णांक i;

	अगर (!modeset->num_connectors)
		वापस false;

	चयन (connector->display_info.panel_orientation) अणु
	हाल DRM_MODE_PANEL_ORIENTATION_BOTTOM_UP:
		*rotation = DRM_MODE_ROTATE_180;
		अवरोध;
	हाल DRM_MODE_PANEL_ORIENTATION_LEFT_UP:
		*rotation = DRM_MODE_ROTATE_90;
		अवरोध;
	हाल DRM_MODE_PANEL_ORIENTATION_RIGHT_UP:
		*rotation = DRM_MODE_ROTATE_270;
		अवरोध;
	शेष:
		*rotation = DRM_MODE_ROTATE_0;
	पूर्ण

	/**
	 * The panel alपढ़ोy defined the शेष rotation
	 * through its orientation. Whatever has been provided
	 * on the command line needs to be added to that.
	 *
	 * Unक्रमtunately, the rotations are at dअगरferent bit
	 * indices, so the math to add them up are not as
	 * trivial as they could.
	 *
	 * Reflections on the other hand are pretty trivial to deal with, a
	 * simple XOR between the two handle the addition nicely.
	 */
	cmdline = &connector->cmdline_mode;
	अगर (cmdline->specअगरied && cmdline->rotation_reflection) अणु
		अचिन्हित पूर्णांक cmdline_rest, panel_rest;
		अचिन्हित पूर्णांक cmdline_rot, panel_rot;
		अचिन्हित पूर्णांक sum_rot, sum_rest;

		panel_rot = ilog2(*rotation & DRM_MODE_ROTATE_MASK);
		cmdline_rot = ilog2(cmdline->rotation_reflection & DRM_MODE_ROTATE_MASK);
		sum_rot = (panel_rot + cmdline_rot) % 4;

		panel_rest = *rotation & ~DRM_MODE_ROTATE_MASK;
		cmdline_rest = cmdline->rotation_reflection & ~DRM_MODE_ROTATE_MASK;
		sum_rest = panel_rest ^ cmdline_rest;

		*rotation = (1 << sum_rot) | sum_rest;
	पूर्ण

	/*
	 * TODO: support 90 / 270 degree hardware rotation,
	 * depending on the hardware this may require the framebuffer
	 * to be in a specअगरic tiling क्रमmat.
	 */
	अगर (((*rotation & DRM_MODE_ROTATE_MASK) != DRM_MODE_ROTATE_0 &&
	     (*rotation & DRM_MODE_ROTATE_MASK) != DRM_MODE_ROTATE_180) ||
	    !plane->rotation_property)
		वापस false;

	क्रम (i = 0; i < plane->rotation_property->num_values; i++)
		valid_mask |= (1ULL << plane->rotation_property->values[i]);

	अगर (!(*rotation & valid_mask))
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_client_rotation);

अटल पूर्णांक drm_client_modeset_commit_atomic(काष्ठा drm_client_dev *client, bool active, bool check)
अणु
	काष्ठा drm_device *dev = client->dev;
	काष्ठा drm_plane *plane;
	काष्ठा drm_atomic_state *state;
	काष्ठा drm_modeset_acquire_ctx ctx;
	काष्ठा drm_mode_set *mode_set;
	पूर्णांक ret;

	drm_modeset_acquire_init(&ctx, 0);

	state = drm_atomic_state_alloc(dev);
	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ out_ctx;
	पूर्ण

	state->acquire_ctx = &ctx;
retry:
	drm_क्रम_each_plane(plane, dev) अणु
		काष्ठा drm_plane_state *plane_state;

		plane_state = drm_atomic_get_plane_state(state, plane);
		अगर (IS_ERR(plane_state)) अणु
			ret = PTR_ERR(plane_state);
			जाओ out_state;
		पूर्ण

		plane_state->rotation = DRM_MODE_ROTATE_0;

		/* disable non-primary: */
		अगर (plane->type == DRM_PLANE_TYPE_PRIMARY)
			जारी;

		ret = __drm_atomic_helper_disable_plane(plane, plane_state);
		अगर (ret != 0)
			जाओ out_state;
	पूर्ण

	drm_client_क्रम_each_modeset(mode_set, client) अणु
		काष्ठा drm_plane *primary = mode_set->crtc->primary;
		अचिन्हित पूर्णांक rotation;

		अगर (drm_client_rotation(mode_set, &rotation)) अणु
			काष्ठा drm_plane_state *plane_state;

			/* Cannot fail as we've alपढ़ोy gotten the plane state above */
			plane_state = drm_atomic_get_new_plane_state(state, primary);
			plane_state->rotation = rotation;
		पूर्ण

		ret = __drm_atomic_helper_set_config(mode_set, state);
		अगर (ret != 0)
			जाओ out_state;

		/*
		 * __drm_atomic_helper_set_config() sets active when a
		 * mode is set, unconditionally clear it अगर we क्रमce DPMS off
		 */
		अगर (!active) अणु
			काष्ठा drm_crtc *crtc = mode_set->crtc;
			काष्ठा drm_crtc_state *crtc_state = drm_atomic_get_new_crtc_state(state, crtc);

			crtc_state->active = false;
		पूर्ण
	पूर्ण

	अगर (check)
		ret = drm_atomic_check_only(state);
	अन्यथा
		ret = drm_atomic_commit(state);

out_state:
	अगर (ret == -EDEADLK)
		जाओ backoff;

	drm_atomic_state_put(state);
out_ctx:
	drm_modeset_drop_locks(&ctx);
	drm_modeset_acquire_fini(&ctx);

	वापस ret;

backoff:
	drm_atomic_state_clear(state);
	drm_modeset_backoff(&ctx);

	जाओ retry;
पूर्ण

अटल पूर्णांक drm_client_modeset_commit_legacy(काष्ठा drm_client_dev *client)
अणु
	काष्ठा drm_device *dev = client->dev;
	काष्ठा drm_mode_set *mode_set;
	काष्ठा drm_plane *plane;
	पूर्णांक ret = 0;

	drm_modeset_lock_all(dev);
	drm_क्रम_each_plane(plane, dev) अणु
		अगर (plane->type != DRM_PLANE_TYPE_PRIMARY)
			drm_plane_क्रमce_disable(plane);

		अगर (plane->rotation_property)
			drm_mode_plane_set_obj_prop(plane,
						    plane->rotation_property,
						    DRM_MODE_ROTATE_0);
	पूर्ण

	drm_client_क्रम_each_modeset(mode_set, client) अणु
		काष्ठा drm_crtc *crtc = mode_set->crtc;

		अगर (crtc->funcs->cursor_set2) अणु
			ret = crtc->funcs->cursor_set2(crtc, शून्य, 0, 0, 0, 0, 0);
			अगर (ret)
				जाओ out;
		पूर्ण अन्यथा अगर (crtc->funcs->cursor_set) अणु
			ret = crtc->funcs->cursor_set(crtc, शून्य, 0, 0, 0);
			अगर (ret)
				जाओ out;
		पूर्ण

		ret = drm_mode_set_config_पूर्णांकernal(mode_set);
		अगर (ret)
			जाओ out;
	पूर्ण
out:
	drm_modeset_unlock_all(dev);

	वापस ret;
पूर्ण

/**
 * drm_client_modeset_check() - Check modeset configuration
 * @client: DRM client
 *
 * Check modeset configuration.
 *
 * Returns:
 * Zero on success or negative error code on failure.
 */
पूर्णांक drm_client_modeset_check(काष्ठा drm_client_dev *client)
अणु
	पूर्णांक ret;

	अगर (!drm_drv_uses_atomic_modeset(client->dev))
		वापस 0;

	mutex_lock(&client->modeset_mutex);
	ret = drm_client_modeset_commit_atomic(client, true, true);
	mutex_unlock(&client->modeset_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_client_modeset_check);

/**
 * drm_client_modeset_commit_locked() - Force commit CRTC configuration
 * @client: DRM client
 *
 * Commit modeset configuration to crtcs without checking अगर there is a DRM
 * master. The assumption is that the caller alपढ़ोy holds an पूर्णांकernal DRM
 * master reference acquired with drm_master_पूर्णांकernal_acquire().
 *
 * Returns:
 * Zero on success or negative error code on failure.
 */
पूर्णांक drm_client_modeset_commit_locked(काष्ठा drm_client_dev *client)
अणु
	काष्ठा drm_device *dev = client->dev;
	पूर्णांक ret;

	mutex_lock(&client->modeset_mutex);
	अगर (drm_drv_uses_atomic_modeset(dev))
		ret = drm_client_modeset_commit_atomic(client, true, false);
	अन्यथा
		ret = drm_client_modeset_commit_legacy(client);
	mutex_unlock(&client->modeset_mutex);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_client_modeset_commit_locked);

/**
 * drm_client_modeset_commit() - Commit CRTC configuration
 * @client: DRM client
 *
 * Commit modeset configuration to crtcs.
 *
 * Returns:
 * Zero on success or negative error code on failure.
 */
पूर्णांक drm_client_modeset_commit(काष्ठा drm_client_dev *client)
अणु
	काष्ठा drm_device *dev = client->dev;
	पूर्णांक ret;

	अगर (!drm_master_पूर्णांकernal_acquire(dev))
		वापस -EBUSY;

	ret = drm_client_modeset_commit_locked(client);

	drm_master_पूर्णांकernal_release(dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_client_modeset_commit);

अटल व्योम drm_client_modeset_dpms_legacy(काष्ठा drm_client_dev *client, पूर्णांक dpms_mode)
अणु
	काष्ठा drm_device *dev = client->dev;
	काष्ठा drm_connector *connector;
	काष्ठा drm_mode_set *modeset;
	काष्ठा drm_modeset_acquire_ctx ctx;
	पूर्णांक j;
	पूर्णांक ret;

	DRM_MODESET_LOCK_ALL_BEGIN(dev, ctx, 0, ret);
	drm_client_क्रम_each_modeset(modeset, client) अणु
		अगर (!modeset->crtc->enabled)
			जारी;

		क्रम (j = 0; j < modeset->num_connectors; j++) अणु
			connector = modeset->connectors[j];
			connector->funcs->dpms(connector, dpms_mode);
			drm_object_property_set_value(&connector->base,
				dev->mode_config.dpms_property, dpms_mode);
		पूर्ण
	पूर्ण
	DRM_MODESET_LOCK_ALL_END(dev, ctx, ret);
पूर्ण

/**
 * drm_client_modeset_dpms() - Set DPMS mode
 * @client: DRM client
 * @mode: DPMS mode
 *
 * Note: For atomic drivers @mode is reduced to on/off.
 *
 * Returns:
 * Zero on success or negative error code on failure.
 */
पूर्णांक drm_client_modeset_dpms(काष्ठा drm_client_dev *client, पूर्णांक mode)
अणु
	काष्ठा drm_device *dev = client->dev;
	पूर्णांक ret = 0;

	अगर (!drm_master_पूर्णांकernal_acquire(dev))
		वापस -EBUSY;

	mutex_lock(&client->modeset_mutex);
	अगर (drm_drv_uses_atomic_modeset(dev))
		ret = drm_client_modeset_commit_atomic(client, mode == DRM_MODE_DPMS_ON, false);
	अन्यथा
		drm_client_modeset_dpms_legacy(client, mode);
	mutex_unlock(&client->modeset_mutex);

	drm_master_पूर्णांकernal_release(dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(drm_client_modeset_dpms);
