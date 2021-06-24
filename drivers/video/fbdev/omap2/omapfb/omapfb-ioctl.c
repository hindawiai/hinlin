<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/omap2/omapfb-ioctl.c
 *
 * Copyright (C) 2008 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#समावेश <linux/fb.h>
#समावेश <linux/device.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mm.h>
#समावेश <linux/omapfb.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/export.h>
#समावेश <linux/sizes.h>

#समावेश <video/omapfb_dss.h>
#समावेश <video/omapvrfb.h>

#समावेश "omapfb.h"

अटल u8 get_mem_idx(काष्ठा omapfb_info *ofbi)
अणु
	अगर (ofbi->id == ofbi->region->id)
		वापस 0;

	वापस OMAPFB_MEM_IDX_ENABLED | ofbi->region->id;
पूर्ण

अटल काष्ठा omapfb2_mem_region *get_mem_region(काष्ठा omapfb_info *ofbi,
						 u8 mem_idx)
अणु
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;

	अगर (mem_idx & OMAPFB_MEM_IDX_ENABLED)
		mem_idx &= OMAPFB_MEM_IDX_MASK;
	अन्यथा
		mem_idx = ofbi->id;

	अगर (mem_idx >= fbdev->num_fbs)
		वापस शून्य;

	वापस &fbdev->regions[mem_idx];
पूर्ण

अटल पूर्णांक omapfb_setup_plane(काष्ठा fb_info *fbi, काष्ठा omapfb_plane_info *pi)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;
	काष्ठा omap_overlay *ovl;
	काष्ठा omap_overlay_info old_info;
	काष्ठा omapfb2_mem_region *old_rg, *new_rg;
	पूर्णांक r = 0;

	DBG("omapfb_setup_plane\n");

	अगर (ofbi->num_overlays == 0) अणु
		r = -EINVAL;
		जाओ out;
	पूर्ण

	/* XXX uses only the first overlay */
	ovl = ofbi->overlays[0];

	old_rg = ofbi->region;
	new_rg = get_mem_region(ofbi, pi->mem_idx);
	अगर (!new_rg) अणु
		r = -EINVAL;
		जाओ out;
	पूर्ण

	/* Take the locks in a specअगरic order to keep lockdep happy */
	अगर (old_rg->id < new_rg->id) अणु
		omapfb_get_mem_region(old_rg);
		omapfb_get_mem_region(new_rg);
	पूर्ण अन्यथा अगर (new_rg->id < old_rg->id) अणु
		omapfb_get_mem_region(new_rg);
		omapfb_get_mem_region(old_rg);
	पूर्ण अन्यथा
		omapfb_get_mem_region(old_rg);

	अगर (pi->enabled && !new_rg->size) अणु
		/*
		 * This plane's memory was freed, can't enable it
		 * until it's पुनः_स्मृतिated.
		 */
		r = -EINVAL;
		जाओ put_mem;
	पूर्ण

	ovl->get_overlay_info(ovl, &old_info);

	अगर (old_rg != new_rg) अणु
		ofbi->region = new_rg;
		set_fb_fix(fbi);
	पूर्ण

	अगर (!pi->enabled) अणु
		r = ovl->disable(ovl);
		अगर (r)
			जाओ unकरो;
	पूर्ण

	अगर (pi->enabled) अणु
		r = omapfb_setup_overlay(fbi, ovl, pi->pos_x, pi->pos_y,
			pi->out_width, pi->out_height);
		अगर (r)
			जाओ unकरो;
	पूर्ण अन्यथा अणु
		काष्ठा omap_overlay_info info;

		ovl->get_overlay_info(ovl, &info);

		info.pos_x = pi->pos_x;
		info.pos_y = pi->pos_y;
		info.out_width = pi->out_width;
		info.out_height = pi->out_height;

		r = ovl->set_overlay_info(ovl, &info);
		अगर (r)
			जाओ unकरो;
	पूर्ण

	अगर (ovl->manager) अणु
		r = ovl->manager->apply(ovl->manager);
		अगर (r)
			जाओ unकरो;
	पूर्ण

	अगर (pi->enabled) अणु
		r = ovl->enable(ovl);
		अगर (r)
			जाओ unकरो;
	पूर्ण

	/* Release the locks in a specअगरic order to keep lockdep happy */
	अगर (old_rg->id > new_rg->id) अणु
		omapfb_put_mem_region(old_rg);
		omapfb_put_mem_region(new_rg);
	पूर्ण अन्यथा अगर (new_rg->id > old_rg->id) अणु
		omapfb_put_mem_region(new_rg);
		omapfb_put_mem_region(old_rg);
	पूर्ण अन्यथा
		omapfb_put_mem_region(old_rg);

	वापस 0;

 unकरो:
	अगर (old_rg != new_rg) अणु
		ofbi->region = old_rg;
		set_fb_fix(fbi);
	पूर्ण

	ovl->set_overlay_info(ovl, &old_info);
 put_mem:
	/* Release the locks in a specअगरic order to keep lockdep happy */
	अगर (old_rg->id > new_rg->id) अणु
		omapfb_put_mem_region(old_rg);
		omapfb_put_mem_region(new_rg);
	पूर्ण अन्यथा अगर (new_rg->id > old_rg->id) अणु
		omapfb_put_mem_region(new_rg);
		omapfb_put_mem_region(old_rg);
	पूर्ण अन्यथा
		omapfb_put_mem_region(old_rg);
 out:
	dev_err(fbdev->dev, "setup_plane failed\n");

	वापस r;
पूर्ण

अटल पूर्णांक omapfb_query_plane(काष्ठा fb_info *fbi, काष्ठा omapfb_plane_info *pi)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);

	अगर (ofbi->num_overlays == 0) अणु
		स_रखो(pi, 0, माप(*pi));
	पूर्ण अन्यथा अणु
		काष्ठा omap_overlay *ovl;
		काष्ठा omap_overlay_info ovli;

		ovl = ofbi->overlays[0];
		ovl->get_overlay_info(ovl, &ovli);

		pi->pos_x = ovli.pos_x;
		pi->pos_y = ovli.pos_y;
		pi->enabled = ovl->is_enabled(ovl);
		pi->channel_out = 0; /* xxx */
		pi->mirror = 0;
		pi->mem_idx = get_mem_idx(ofbi);
		pi->out_width = ovli.out_width;
		pi->out_height = ovli.out_height;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक omapfb_setup_mem(काष्ठा fb_info *fbi, काष्ठा omapfb_mem_info *mi)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;
	काष्ठा omap_dss_device *display = fb2display(fbi);
	काष्ठा omapfb2_mem_region *rg;
	पूर्णांक r = 0, i;
	माप_प्रकार size;

	अगर (mi->type != OMAPFB_MEMTYPE_SDRAM)
		वापस -EINVAL;

	size = PAGE_ALIGN(mi->size);

	अगर (display && display->driver->sync)
		display->driver->sync(display);

	rg = ofbi->region;

	करोwn_ग_लिखो_nested(&rg->lock, rg->id);
	atomic_inc(&rg->lock_count);

	अगर (rg->size == size && rg->type == mi->type)
		जाओ out;

	अगर (atomic_पढ़ो(&rg->map_count)) अणु
		r = -EBUSY;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < fbdev->num_fbs; i++) अणु
		काष्ठा omapfb_info *ofbi2 = FB2OFB(fbdev->fbs[i]);
		पूर्णांक j;

		अगर (ofbi2->region != rg)
			जारी;

		क्रम (j = 0; j < ofbi2->num_overlays; j++) अणु
			काष्ठा omap_overlay *ovl;
			ovl = ofbi2->overlays[j];
			अगर (ovl->is_enabled(ovl)) अणु
				r = -EBUSY;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	r = omapfb_पुनः_स्मृति_fbmem(fbi, size, mi->type);
	अगर (r) अणु
		dev_err(fbdev->dev, "realloc fbmem failed\n");
		जाओ out;
	पूर्ण

 out:
	atomic_dec(&rg->lock_count);
	up_ग_लिखो(&rg->lock);

	वापस r;
पूर्ण

अटल पूर्णांक omapfb_query_mem(काष्ठा fb_info *fbi, काष्ठा omapfb_mem_info *mi)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_mem_region *rg;

	rg = omapfb_get_mem_region(ofbi->region);
	स_रखो(mi, 0, माप(*mi));

	mi->size = rg->size;
	mi->type = rg->type;

	omapfb_put_mem_region(rg);

	वापस 0;
पूर्ण

अटल पूर्णांक omapfb_update_winकरोw(काष्ठा fb_info *fbi,
		u32 x, u32 y, u32 w, u32 h)
अणु
	काष्ठा omap_dss_device *display = fb2display(fbi);
	u16 dw, dh;

	अगर (!display)
		वापस 0;

	अगर (w == 0 || h == 0)
		वापस 0;

	display->driver->get_resolution(display, &dw, &dh);

	अगर (x + w > dw || y + h > dh)
		वापस -EINVAL;

	वापस display->driver->update(display, x, y, w, h);
पूर्ण

पूर्णांक omapfb_set_update_mode(काष्ठा fb_info *fbi,
				   क्रमागत omapfb_update_mode mode)
अणु
	काष्ठा omap_dss_device *display = fb2display(fbi);
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;
	काष्ठा omapfb_display_data *d;
	पूर्णांक r;

	अगर (!display)
		वापस -EINVAL;

	अगर (mode != OMAPFB_AUTO_UPDATE && mode != OMAPFB_MANUAL_UPDATE)
		वापस -EINVAL;

	omapfb_lock(fbdev);

	d = get_display_data(fbdev, display);

	अगर (d->update_mode == mode) अणु
		omapfb_unlock(fbdev);
		वापस 0;
	पूर्ण

	r = 0;

	अगर (display->caps & OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE) अणु
		अगर (mode == OMAPFB_AUTO_UPDATE)
			omapfb_start_स्वतः_update(fbdev, display);
		अन्यथा /* MANUAL_UPDATE */
			omapfb_stop_स्वतः_update(fbdev, display);

		d->update_mode = mode;
	पूर्ण अन्यथा अणु /* AUTO_UPDATE */
		अगर (mode == OMAPFB_MANUAL_UPDATE)
			r = -EINVAL;
	पूर्ण

	omapfb_unlock(fbdev);

	वापस r;
पूर्ण

पूर्णांक omapfb_get_update_mode(काष्ठा fb_info *fbi,
		क्रमागत omapfb_update_mode *mode)
अणु
	काष्ठा omap_dss_device *display = fb2display(fbi);
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;
	काष्ठा omapfb_display_data *d;

	अगर (!display)
		वापस -EINVAL;

	omapfb_lock(fbdev);

	d = get_display_data(fbdev, display);

	*mode = d->update_mode;

	omapfb_unlock(fbdev);

	वापस 0;
पूर्ण

/* XXX this color key handling is a hack... */
अटल काष्ठा omapfb_color_key omapfb_color_keys[2];

अटल पूर्णांक _omapfb_set_color_key(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omapfb_color_key *ck)
अणु
	काष्ठा omap_overlay_manager_info info;
	क्रमागत omap_dss_trans_key_type kt;
	पूर्णांक r;

	mgr->get_manager_info(mgr, &info);

	अगर (ck->key_type == OMAPFB_COLOR_KEY_DISABLED) अणु
		info.trans_enabled = false;
		omapfb_color_keys[mgr->id] = *ck;

		r = mgr->set_manager_info(mgr, &info);
		अगर (r)
			वापस r;

		r = mgr->apply(mgr);

		वापस r;
	पूर्ण

	चयन (ck->key_type) अणु
	हाल OMAPFB_COLOR_KEY_GFX_DST:
		kt = OMAP_DSS_COLOR_KEY_GFX_DST;
		अवरोध;
	हाल OMAPFB_COLOR_KEY_VID_SRC:
		kt = OMAP_DSS_COLOR_KEY_VID_SRC;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	info.शेष_color = ck->background;
	info.trans_key = ck->trans_key;
	info.trans_key_type = kt;
	info.trans_enabled = true;

	omapfb_color_keys[mgr->id] = *ck;

	r = mgr->set_manager_info(mgr, &info);
	अगर (r)
		वापस r;

	r = mgr->apply(mgr);

	वापस r;
पूर्ण

अटल पूर्णांक omapfb_set_color_key(काष्ठा fb_info *fbi,
		काष्ठा omapfb_color_key *ck)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;
	पूर्णांक r;
	पूर्णांक i;
	काष्ठा omap_overlay_manager *mgr = शून्य;

	omapfb_lock(fbdev);

	क्रम (i = 0; i < ofbi->num_overlays; i++) अणु
		अगर (ofbi->overlays[i]->manager) अणु
			mgr = ofbi->overlays[i]->manager;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!mgr) अणु
		r = -EINVAL;
		जाओ err;
	पूर्ण

	r = _omapfb_set_color_key(mgr, ck);
err:
	omapfb_unlock(fbdev);

	वापस r;
पूर्ण

अटल पूर्णांक omapfb_get_color_key(काष्ठा fb_info *fbi,
		काष्ठा omapfb_color_key *ck)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;
	काष्ठा omap_overlay_manager *mgr = शून्य;
	पूर्णांक r = 0;
	पूर्णांक i;

	omapfb_lock(fbdev);

	क्रम (i = 0; i < ofbi->num_overlays; i++) अणु
		अगर (ofbi->overlays[i]->manager) अणु
			mgr = ofbi->overlays[i]->manager;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!mgr) अणु
		r = -EINVAL;
		जाओ err;
	पूर्ण

	*ck = omapfb_color_keys[mgr->id];
err:
	omapfb_unlock(fbdev);

	वापस r;
पूर्ण

अटल पूर्णांक omapfb_memory_पढ़ो(काष्ठा fb_info *fbi,
		काष्ठा omapfb_memory_पढ़ो *mr)
अणु
	काष्ठा omap_dss_device *display = fb2display(fbi);
	व्योम *buf;
	पूर्णांक r;

	अगर (!display || !display->driver->memory_पढ़ो)
		वापस -ENOENT;

	अगर (mr->w > 4096 || mr->h > 4096)
		वापस -EINVAL;

	अगर (mr->w * mr->h * 3 > mr->buffer_size)
		वापस -EINVAL;

	buf = vदो_स्मृति(mr->buffer_size);
	अगर (!buf) अणु
		DBG("vmalloc failed\n");
		वापस -ENOMEM;
	पूर्ण

	r = display->driver->memory_पढ़ो(display, buf, mr->buffer_size,
			mr->x, mr->y, mr->w, mr->h);

	अगर (r > 0) अणु
		अगर (copy_to_user(mr->buffer, buf, r))
			r = -EFAULT;
	पूर्ण

	vमुक्त(buf);

	वापस r;
पूर्ण

अटल पूर्णांक omapfb_get_ovl_colormode(काष्ठा omapfb2_device *fbdev,
			     काष्ठा omapfb_ovl_colormode *mode)
अणु
	पूर्णांक ovl_idx = mode->overlay_idx;
	पूर्णांक mode_idx = mode->mode_idx;
	काष्ठा omap_overlay *ovl;
	क्रमागत omap_color_mode supported_modes;
	काष्ठा fb_var_screeninfo var;
	पूर्णांक i;

	अगर (ovl_idx >= fbdev->num_overlays)
		वापस -ENODEV;
	ovl = fbdev->overlays[ovl_idx];
	supported_modes = ovl->supported_modes;

	mode_idx = mode->mode_idx;

	क्रम (i = 0; i < माप(supported_modes) * 8; i++) अणु
		अगर (!(supported_modes & (1 << i)))
			जारी;
		/*
		 * It's possible that the FB doesn't support a mode
		 * that is supported by the overlay, so call the
		 * following here.
		 */
		अगर (dss_mode_to_fb_mode(1 << i, &var) < 0)
			जारी;

		mode_idx--;
		अगर (mode_idx < 0)
			अवरोध;
	पूर्ण

	अगर (i == माप(supported_modes) * 8)
		वापस -ENOENT;

	mode->bits_per_pixel = var.bits_per_pixel;
	mode->nonstd = var.nonstd;
	mode->red = var.red;
	mode->green = var.green;
	mode->blue = var.blue;
	mode->transp = var.transp;

	वापस 0;
पूर्ण

अटल पूर्णांक omapfb_रुको_क्रम_go(काष्ठा fb_info *fbi)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	पूर्णांक r = 0;
	पूर्णांक i;

	क्रम (i = 0; i < ofbi->num_overlays; ++i) अणु
		काष्ठा omap_overlay *ovl = ofbi->overlays[i];
		r = ovl->रुको_क्रम_go(ovl);
		अगर (r)
			अवरोध;
	पूर्ण

	वापस r;
पूर्ण

पूर्णांक omapfb_ioctl(काष्ठा fb_info *fbi, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ arg)
अणु
	काष्ठा omapfb_info *ofbi = FB2OFB(fbi);
	काष्ठा omapfb2_device *fbdev = ofbi->fbdev;
	काष्ठा omap_dss_device *display = fb2display(fbi);
	काष्ठा omap_overlay_manager *mgr;

	जोड़ अणु
		काष्ठा omapfb_update_winकरोw_old	uwnd_o;
		काष्ठा omapfb_update_winकरोw	uwnd;
		काष्ठा omapfb_plane_info	plane_info;
		काष्ठा omapfb_caps		caps;
		काष्ठा omapfb_mem_info          mem_info;
		काष्ठा omapfb_color_key		color_key;
		काष्ठा omapfb_ovl_colormode	ovl_colormode;
		क्रमागत omapfb_update_mode		update_mode;
		पूर्णांक test_num;
		काष्ठा omapfb_memory_पढ़ो	memory_पढ़ो;
		काष्ठा omapfb_vram_info		vram_info;
		काष्ठा omapfb_tearsync_info	tearsync_info;
		काष्ठा omapfb_display_info	display_info;
		u32				crt;
	पूर्ण p;

	पूर्णांक r = 0;

	स_रखो(&p, 0, माप(p));

	चयन (cmd) अणु
	हाल OMAPFB_SYNC_GFX:
		DBG("ioctl SYNC_GFX\n");
		अगर (!display || !display->driver->sync) अणु
			/* DSS1 never वापसs an error here, so we neither */
			/*r = -EINVAL;*/
			अवरोध;
		पूर्ण

		r = display->driver->sync(display);
		अवरोध;

	हाल OMAPFB_UPDATE_WINDOW_OLD:
		DBG("ioctl UPDATE_WINDOW_OLD\n");
		अगर (!display || !display->driver->update) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (copy_from_user(&p.uwnd_o,
					(व्योम __user *)arg,
					माप(p.uwnd_o))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण

		r = omapfb_update_winकरोw(fbi, p.uwnd_o.x, p.uwnd_o.y,
				p.uwnd_o.width, p.uwnd_o.height);
		अवरोध;

	हाल OMAPFB_UPDATE_WINDOW:
		DBG("ioctl UPDATE_WINDOW\n");
		अगर (!display || !display->driver->update) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		अगर (copy_from_user(&p.uwnd, (व्योम __user *)arg,
					माप(p.uwnd))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण

		r = omapfb_update_winकरोw(fbi, p.uwnd.x, p.uwnd.y,
				p.uwnd.width, p.uwnd.height);
		अवरोध;

	हाल OMAPFB_SETUP_PLANE:
		DBG("ioctl SETUP_PLANE\n");
		अगर (copy_from_user(&p.plane_info, (व्योम __user *)arg,
					माप(p.plane_info)))
			r = -EFAULT;
		अन्यथा
			r = omapfb_setup_plane(fbi, &p.plane_info);
		अवरोध;

	हाल OMAPFB_QUERY_PLANE:
		DBG("ioctl QUERY_PLANE\n");
		r = omapfb_query_plane(fbi, &p.plane_info);
		अगर (r < 0)
			अवरोध;
		अगर (copy_to_user((व्योम __user *)arg, &p.plane_info,
					माप(p.plane_info)))
			r = -EFAULT;
		अवरोध;

	हाल OMAPFB_SETUP_MEM:
		DBG("ioctl SETUP_MEM\n");
		अगर (copy_from_user(&p.mem_info, (व्योम __user *)arg,
					माप(p.mem_info)))
			r = -EFAULT;
		अन्यथा
			r = omapfb_setup_mem(fbi, &p.mem_info);
		अवरोध;

	हाल OMAPFB_QUERY_MEM:
		DBG("ioctl QUERY_MEM\n");
		r = omapfb_query_mem(fbi, &p.mem_info);
		अगर (r < 0)
			अवरोध;
		अगर (copy_to_user((व्योम __user *)arg, &p.mem_info,
					माप(p.mem_info)))
			r = -EFAULT;
		अवरोध;

	हाल OMAPFB_GET_CAPS:
		DBG("ioctl GET_CAPS\n");
		अगर (!display) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		स_रखो(&p.caps, 0, माप(p.caps));
		अगर (display->caps & OMAP_DSS_DISPLAY_CAP_MANUAL_UPDATE)
			p.caps.ctrl |= OMAPFB_CAPS_MANUAL_UPDATE;
		अगर (display->caps & OMAP_DSS_DISPLAY_CAP_TEAR_ELIM)
			p.caps.ctrl |= OMAPFB_CAPS_TEARSYNC;

		अगर (copy_to_user((व्योम __user *)arg, &p.caps, माप(p.caps)))
			r = -EFAULT;
		अवरोध;

	हाल OMAPFB_GET_OVERLAY_COLORMODE:
		DBG("ioctl GET_OVERLAY_COLORMODE\n");
		अगर (copy_from_user(&p.ovl_colormode, (व्योम __user *)arg,
				   माप(p.ovl_colormode))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण
		r = omapfb_get_ovl_colormode(fbdev, &p.ovl_colormode);
		अगर (r < 0)
			अवरोध;
		अगर (copy_to_user((व्योम __user *)arg, &p.ovl_colormode,
				 माप(p.ovl_colormode)))
			r = -EFAULT;
		अवरोध;

	हाल OMAPFB_SET_UPDATE_MODE:
		DBG("ioctl SET_UPDATE_MODE\n");
		अगर (get_user(p.update_mode, (पूर्णांक __user *)arg))
			r = -EFAULT;
		अन्यथा
			r = omapfb_set_update_mode(fbi, p.update_mode);
		अवरोध;

	हाल OMAPFB_GET_UPDATE_MODE:
		DBG("ioctl GET_UPDATE_MODE\n");
		r = omapfb_get_update_mode(fbi, &p.update_mode);
		अगर (r)
			अवरोध;
		अगर (put_user(p.update_mode,
					(क्रमागत omapfb_update_mode __user *)arg))
			r = -EFAULT;
		अवरोध;

	हाल OMAPFB_SET_COLOR_KEY:
		DBG("ioctl SET_COLOR_KEY\n");
		अगर (copy_from_user(&p.color_key, (व्योम __user *)arg,
				   माप(p.color_key)))
			r = -EFAULT;
		अन्यथा
			r = omapfb_set_color_key(fbi, &p.color_key);
		अवरोध;

	हाल OMAPFB_GET_COLOR_KEY:
		DBG("ioctl GET_COLOR_KEY\n");
		r = omapfb_get_color_key(fbi, &p.color_key);
		अगर (r)
			अवरोध;
		अगर (copy_to_user((व्योम __user *)arg, &p.color_key,
				 माप(p.color_key)))
			r = -EFAULT;
		अवरोध;

	हाल FBIO_WAITFORVSYNC:
		अगर (get_user(p.crt, (__u32 __user *)arg)) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (p.crt != 0) अणु
			r = -ENODEV;
			अवरोध;
		पूर्ण
		fallthrough;

	हाल OMAPFB_WAITFORVSYNC:
		DBG("ioctl WAITFORVSYNC\n");

		अगर (!display) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		mgr = omapdss_find_mgr_from_display(display);
		अगर (!mgr) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		r = mgr->रुको_क्रम_vsync(mgr);
		अवरोध;

	हाल OMAPFB_WAITFORGO:
		DBG("ioctl WAITFORGO\n");
		अगर (!display) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		r = omapfb_रुको_क्रम_go(fbi);
		अवरोध;

	/* LCD and CTRL tests करो the same thing क्रम backward
	 * compatibility */
	हाल OMAPFB_LCD_TEST:
		DBG("ioctl LCD_TEST\n");
		अगर (get_user(p.test_num, (पूर्णांक __user *)arg)) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (!display || !display->driver->run_test) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		r = display->driver->run_test(display, p.test_num);

		अवरोध;

	हाल OMAPFB_CTRL_TEST:
		DBG("ioctl CTRL_TEST\n");
		अगर (get_user(p.test_num, (पूर्णांक __user *)arg)) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण
		अगर (!display || !display->driver->run_test) अणु
			r = -EINVAL;
			अवरोध;
		पूर्ण

		r = display->driver->run_test(display, p.test_num);

		अवरोध;

	हाल OMAPFB_MEMORY_READ:
		DBG("ioctl MEMORY_READ\n");

		अगर (copy_from_user(&p.memory_पढ़ो, (व्योम __user *)arg,
					माप(p.memory_पढ़ो))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण

		r = omapfb_memory_पढ़ो(fbi, &p.memory_पढ़ो);

		अवरोध;

	हाल OMAPFB_GET_VRAM_INFO: अणु
		DBG("ioctl GET_VRAM_INFO\n");

		/*
		 * We करोn't have the ability to get this vram info anymore.
		 * Fill in something that should keep the applications working.
		 */
		p.vram_info.total = SZ_1M * 64;
		p.vram_info.मुक्त = SZ_1M * 64;
		p.vram_info.largest_मुक्त_block = SZ_1M * 64;

		अगर (copy_to_user((व्योम __user *)arg, &p.vram_info,
					माप(p.vram_info)))
			r = -EFAULT;
		अवरोध;
	पूर्ण

	हाल OMAPFB_SET_TEARSYNC: अणु
		DBG("ioctl SET_TEARSYNC\n");

		अगर (copy_from_user(&p.tearsync_info, (व्योम __user *)arg,
					माप(p.tearsync_info))) अणु
			r = -EFAULT;
			अवरोध;
		पूर्ण

		अगर (!display || !display->driver->enable_te) अणु
			r = -ENODEV;
			अवरोध;
		पूर्ण

		r = display->driver->enable_te(display,
				!!p.tearsync_info.enabled);

		अवरोध;
	पूर्ण

	हाल OMAPFB_GET_DISPLAY_INFO: अणु
		u16 xres, yres;

		DBG("ioctl GET_DISPLAY_INFO\n");

		अगर (display == शून्य) अणु
			r = -ENODEV;
			अवरोध;
		पूर्ण

		display->driver->get_resolution(display, &xres, &yres);

		p.display_info.xres = xres;
		p.display_info.yres = yres;

		अगर (display->driver->get_dimensions) अणु
			u32 w, h;
			display->driver->get_dimensions(display, &w, &h);
			p.display_info.width = w;
			p.display_info.height = h;
		पूर्ण अन्यथा अणु
			p.display_info.width = 0;
			p.display_info.height = 0;
		पूर्ण

		अगर (copy_to_user((व्योम __user *)arg, &p.display_info,
					माप(p.display_info)))
			r = -EFAULT;
		अवरोध;
	पूर्ण

	शेष:
		dev_err(fbdev->dev, "Unknown ioctl 0x%x\n", cmd);
		r = -EINVAL;
	पूर्ण

	अगर (r < 0)
		DBG("ioctl failed: %d\n", r);

	वापस r;
पूर्ण


