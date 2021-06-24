<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/omap2/dss/overlay.c
 *
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#घोषणा DSS_SUBSYS_NAME "OVERLAY"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"
#समावेश "dss_features.h"

अटल पूर्णांक num_overlays;
अटल काष्ठा omap_overlay *overlays;

पूर्णांक omap_dss_get_num_overlays(व्योम)
अणु
	वापस num_overlays;
पूर्ण
EXPORT_SYMBOL(omap_dss_get_num_overlays);

काष्ठा omap_overlay *omap_dss_get_overlay(पूर्णांक num)
अणु
	अगर (num >= num_overlays)
		वापस शून्य;

	वापस &overlays[num];
पूर्ण
EXPORT_SYMBOL(omap_dss_get_overlay);

व्योम dss_init_overlays(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, r;

	num_overlays = dss_feat_get_num_ovls();

	overlays = kसुस्मृति(num_overlays, माप(काष्ठा omap_overlay),
			   GFP_KERNEL);

	BUG_ON(overlays == शून्य);

	क्रम (i = 0; i < num_overlays; ++i) अणु
		काष्ठा omap_overlay *ovl = &overlays[i];

		चयन (i) अणु
		हाल 0:
			ovl->name = "gfx";
			ovl->id = OMAP_DSS_GFX;
			अवरोध;
		हाल 1:
			ovl->name = "vid1";
			ovl->id = OMAP_DSS_VIDEO1;
			अवरोध;
		हाल 2:
			ovl->name = "vid2";
			ovl->id = OMAP_DSS_VIDEO2;
			अवरोध;
		हाल 3:
			ovl->name = "vid3";
			ovl->id = OMAP_DSS_VIDEO3;
			अवरोध;
		पूर्ण

		ovl->caps = dss_feat_get_overlay_caps(ovl->id);
		ovl->supported_modes =
			dss_feat_get_supported_color_modes(ovl->id);

		r = dss_overlay_kobj_init(ovl, pdev);
		अगर (r)
			DSSERR("failed to create sysfs file\n");
	पूर्ण
पूर्ण

व्योम dss_uninit_overlays(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_overlays; ++i) अणु
		काष्ठा omap_overlay *ovl = &overlays[i];
		dss_overlay_kobj_uninit(ovl);
	पूर्ण

	kमुक्त(overlays);
	overlays = शून्य;
	num_overlays = 0;
पूर्ण

पूर्णांक dss_ovl_simple_check(काष्ठा omap_overlay *ovl,
		स्थिर काष्ठा omap_overlay_info *info)
अणु
	अगर ((ovl->caps & OMAP_DSS_OVL_CAP_SCALE) == 0) अणु
		अगर (info->out_width != 0 && info->width != info->out_width) अणु
			DSSERR("check_overlay: overlay %d doesn't support "
					"scaling\n", ovl->id);
			वापस -EINVAL;
		पूर्ण

		अगर (info->out_height != 0 && info->height != info->out_height) अणु
			DSSERR("check_overlay: overlay %d doesn't support "
					"scaling\n", ovl->id);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर ((ovl->supported_modes & info->color_mode) == 0) अणु
		DSSERR("check_overlay: overlay %d doesn't support mode %d\n",
				ovl->id, info->color_mode);
		वापस -EINVAL;
	पूर्ण

	अगर (info->zorder >= omap_dss_get_num_overlays()) अणु
		DSSERR("check_overlay: zorder %d too high\n", info->zorder);
		वापस -EINVAL;
	पूर्ण

	अगर (dss_feat_rotation_type_supported(info->rotation_type) == 0) अणु
		DSSERR("check_overlay: rotation type %d not supported\n",
				info->rotation_type);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dss_ovl_check(काष्ठा omap_overlay *ovl, काष्ठा omap_overlay_info *info,
		स्थिर काष्ठा omap_video_timings *mgr_timings)
अणु
	u16 outw, outh;
	u16 dw, dh;

	dw = mgr_timings->x_res;
	dh = mgr_timings->y_res;

	अगर ((ovl->caps & OMAP_DSS_OVL_CAP_SCALE) == 0) अणु
		outw = info->width;
		outh = info->height;
	पूर्ण अन्यथा अणु
		अगर (info->out_width == 0)
			outw = info->width;
		अन्यथा
			outw = info->out_width;

		अगर (info->out_height == 0)
			outh = info->height;
		अन्यथा
			outh = info->out_height;
	पूर्ण

	अगर (dw < info->pos_x + outw) अणु
		DSSERR("overlay %d horizontally not inside the display area "
				"(%d + %d >= %d)\n",
				ovl->id, info->pos_x, outw, dw);
		वापस -EINVAL;
	पूर्ण

	अगर (dh < info->pos_y + outh) अणु
		DSSERR("overlay %d vertically not inside the display area "
				"(%d + %d >= %d)\n",
				ovl->id, info->pos_y, outh, dh);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Checks अगर replication logic should be used. Only use when overlay is in
 * RGB12U or RGB16 mode, and video port width पूर्णांकerface is 18bpp or 24bpp
 */
bool dss_ovl_use_replication(काष्ठा dss_lcd_mgr_config config,
		क्रमागत omap_color_mode mode)
अणु
	अगर (mode != OMAP_DSS_COLOR_RGB12U && mode != OMAP_DSS_COLOR_RGB16)
		वापस false;

	वापस config.video_port_width > 16;
पूर्ण
