<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/omap2/dss/manager.c
 *
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#घोषणा DSS_SUBSYS_NAME "MANAGER"

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/jअगरfies.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"
#समावेश "dss_features.h"

अटल पूर्णांक num_managers;
अटल काष्ठा omap_overlay_manager *managers;

पूर्णांक dss_init_overlay_managers(व्योम)
अणु
	पूर्णांक i;

	num_managers = dss_feat_get_num_mgrs();

	managers = kसुस्मृति(num_managers, माप(काष्ठा omap_overlay_manager),
			   GFP_KERNEL);

	BUG_ON(managers == शून्य);

	क्रम (i = 0; i < num_managers; ++i) अणु
		काष्ठा omap_overlay_manager *mgr = &managers[i];

		चयन (i) अणु
		हाल 0:
			mgr->name = "lcd";
			mgr->id = OMAP_DSS_CHANNEL_LCD;
			अवरोध;
		हाल 1:
			mgr->name = "tv";
			mgr->id = OMAP_DSS_CHANNEL_DIGIT;
			अवरोध;
		हाल 2:
			mgr->name = "lcd2";
			mgr->id = OMAP_DSS_CHANNEL_LCD2;
			अवरोध;
		हाल 3:
			mgr->name = "lcd3";
			mgr->id = OMAP_DSS_CHANNEL_LCD3;
			अवरोध;
		पूर्ण

		mgr->supported_displays =
			dss_feat_get_supported_displays(mgr->id);
		mgr->supported_outमाला_दो =
			dss_feat_get_supported_outमाला_दो(mgr->id);

		INIT_LIST_HEAD(&mgr->overlays);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dss_init_overlay_managers_sysfs(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, r;

	क्रम (i = 0; i < num_managers; ++i) अणु
		काष्ठा omap_overlay_manager *mgr = &managers[i];

		r = dss_manager_kobj_init(mgr, pdev);
		अगर (r)
			DSSERR("failed to create sysfs file\n");
	पूर्ण

	वापस 0;
पूर्ण

व्योम dss_uninit_overlay_managers(व्योम)
अणु
	kमुक्त(managers);
	managers = शून्य;
	num_managers = 0;
पूर्ण

व्योम dss_uninit_overlay_managers_sysfs(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_managers; ++i) अणु
		काष्ठा omap_overlay_manager *mgr = &managers[i];

		dss_manager_kobj_uninit(mgr);
	पूर्ण
पूर्ण

पूर्णांक omap_dss_get_num_overlay_managers(व्योम)
अणु
	वापस num_managers;
पूर्ण
EXPORT_SYMBOL(omap_dss_get_num_overlay_managers);

काष्ठा omap_overlay_manager *omap_dss_get_overlay_manager(पूर्णांक num)
अणु
	अगर (num >= num_managers)
		वापस शून्य;

	वापस &managers[num];
पूर्ण
EXPORT_SYMBOL(omap_dss_get_overlay_manager);

पूर्णांक dss_mgr_simple_check(काष्ठा omap_overlay_manager *mgr,
		स्थिर काष्ठा omap_overlay_manager_info *info)
अणु
	अगर (dss_has_feature(FEAT_ALPHA_FIXED_ZORDER)) अणु
		/*
		 * OMAP3 supports only graphics source transparency color key
		 * and alpha blending simultaneously. See TRM 15.4.2.4.2.2
		 * Alpha Mode.
		 */
		अगर (info->partial_alpha_enabled && info->trans_enabled
			&& info->trans_key_type != OMAP_DSS_COLOR_KEY_GFX_DST) अणु
			DSSERR("check_manager: illegal transparency key\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dss_mgr_check_zorder(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omap_overlay_info **overlay_infos)
अणु
	काष्ठा omap_overlay *ovl1, *ovl2;
	काष्ठा omap_overlay_info *info1, *info2;

	list_क्रम_each_entry(ovl1, &mgr->overlays, list) अणु
		info1 = overlay_infos[ovl1->id];

		अगर (info1 == शून्य)
			जारी;

		list_क्रम_each_entry(ovl2, &mgr->overlays, list) अणु
			अगर (ovl1 == ovl2)
				जारी;

			info2 = overlay_infos[ovl2->id];

			अगर (info2 == शून्य)
				जारी;

			अगर (info1->zorder == info2->zorder) अणु
				DSSERR("overlays %d and %d have the same "
						"zorder %d\n",
					ovl1->id, ovl2->id, info1->zorder);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक dss_mgr_check_timings(काष्ठा omap_overlay_manager *mgr,
		स्थिर काष्ठा omap_video_timings *timings)
अणु
	अगर (!dispc_mgr_timings_ok(mgr->id, timings)) अणु
		DSSERR("check_manager: invalid timings\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dss_mgr_check_lcd_config(काष्ठा omap_overlay_manager *mgr,
		स्थिर काष्ठा dss_lcd_mgr_config *config)
अणु
	काष्ठा dispc_घड़ी_info cinfo = config->घड़ी_info;
	पूर्णांक dl = config->video_port_width;
	bool stallmode = config->stallmode;
	bool fअगरohandcheck = config->fअगरohandcheck;

	अगर (cinfo.lck_भाग < 1 || cinfo.lck_भाग > 255)
		वापस -EINVAL;

	अगर (cinfo.pck_भाग < 1 || cinfo.pck_भाग > 255)
		वापस -EINVAL;

	अगर (dl != 12 && dl != 16 && dl != 18 && dl != 24)
		वापस -EINVAL;

	/* fअगरohandcheck should be used only with stallmode */
	अगर (!stallmode && fअगरohandcheck)
		वापस -EINVAL;

	/*
	 * io pad mode can be only checked by using dssdev connected to the
	 * manager. Ignore checking these क्रम now, add checks when manager
	 * is capable of holding inक्रमmation related to the connected पूर्णांकerface
	 */

	वापस 0;
पूर्ण

पूर्णांक dss_mgr_check(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omap_overlay_manager_info *info,
		स्थिर काष्ठा omap_video_timings *mgr_timings,
		स्थिर काष्ठा dss_lcd_mgr_config *lcd_config,
		काष्ठा omap_overlay_info **overlay_infos)
अणु
	काष्ठा omap_overlay *ovl;
	पूर्णांक r;

	अगर (dss_has_feature(FEAT_ALPHA_FREE_ZORDER)) अणु
		r = dss_mgr_check_zorder(mgr, overlay_infos);
		अगर (r)
			वापस r;
	पूर्ण

	r = dss_mgr_check_timings(mgr, mgr_timings);
	अगर (r)
		वापस r;

	r = dss_mgr_check_lcd_config(mgr, lcd_config);
	अगर (r)
		वापस r;

	list_क्रम_each_entry(ovl, &mgr->overlays, list) अणु
		काष्ठा omap_overlay_info *oi;
		पूर्णांक r;

		oi = overlay_infos[ovl->id];

		अगर (oi == शून्य)
			जारी;

		r = dss_ovl_check(ovl, oi, mgr_timings);
		अगर (r)
			वापस r;
	पूर्ण

	वापस 0;
पूर्ण
