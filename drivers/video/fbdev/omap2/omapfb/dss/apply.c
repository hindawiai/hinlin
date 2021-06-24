<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2011 Texas Instruments
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 */

#घोषणा DSS_SUBSYS_NAME "APPLY"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/jअगरfies.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"
#समावेश "dss_features.h"
#समावेश "dispc-compat.h"

/*
 * We have 4 levels of cache क्रम the dispc settings. First two are in SW and
 * the latter two in HW.
 *
 *       set_info()
 *          v
 * +--------------------+
 * |     user_info      |
 * +--------------------+
 *          v
 *        apply()
 *          v
 * +--------------------+
 * |       info         |
 * +--------------------+
 *          v
 *      ग_लिखो_regs()
 *          v
 * +--------------------+
 * |  shaकरोw रेजिस्टरs  |
 * +--------------------+
 *          v
 * VFP or lcd/digit_enable
 *          v
 * +--------------------+
 * |      रेजिस्टरs     |
 * +--------------------+
 */

काष्ठा ovl_priv_data अणु

	bool user_info_dirty;
	काष्ठा omap_overlay_info user_info;

	bool info_dirty;
	काष्ठा omap_overlay_info info;

	bool shaकरोw_info_dirty;

	bool extra_info_dirty;
	bool shaकरोw_extra_info_dirty;

	bool enabled;
	u32 fअगरo_low, fअगरo_high;

	/*
	 * True अगर overlay is to be enabled. Used to check and calculate configs
	 * क्रम the overlay beक्रमe it is enabled in the HW.
	 */
	bool enabling;
पूर्ण;

काष्ठा mgr_priv_data अणु

	bool user_info_dirty;
	काष्ठा omap_overlay_manager_info user_info;

	bool info_dirty;
	काष्ठा omap_overlay_manager_info info;

	bool shaकरोw_info_dirty;

	/* If true, GO bit is up and shaकरोw रेजिस्टरs cannot be written.
	 * Never true क्रम manual update displays */
	bool busy;

	/* If true, dispc output is enabled */
	bool updating;

	/* If true, a display is enabled using this manager */
	bool enabled;

	bool extra_info_dirty;
	bool shaकरोw_extra_info_dirty;

	काष्ठा omap_video_timings timings;
	काष्ठा dss_lcd_mgr_config lcd_config;

	व्योम (*frameकरोne_handler)(व्योम *);
	व्योम *frameकरोne_handler_data;
पूर्ण;

अटल काष्ठा अणु
	काष्ठा ovl_priv_data ovl_priv_data_array[MAX_DSS_OVERLAYS];
	काष्ठा mgr_priv_data mgr_priv_data_array[MAX_DSS_MANAGERS];

	bool irq_enabled;
पूर्ण dss_data;

/* protects dss_data */
अटल spinlock_t data_lock;
/* lock क्रम blocking functions */
अटल DEFINE_MUTEX(apply_lock);
अटल DECLARE_COMPLETION(extra_updated_completion);

अटल व्योम dss_रेजिस्टर_vsync_isr(व्योम);

अटल काष्ठा ovl_priv_data *get_ovl_priv(काष्ठा omap_overlay *ovl)
अणु
	वापस &dss_data.ovl_priv_data_array[ovl->id];
पूर्ण

अटल काष्ठा mgr_priv_data *get_mgr_priv(काष्ठा omap_overlay_manager *mgr)
अणु
	वापस &dss_data.mgr_priv_data_array[mgr->id];
पूर्ण

अटल व्योम apply_init_priv(व्योम)
अणु
	स्थिर पूर्णांक num_ovls = dss_feat_get_num_ovls();
	काष्ठा mgr_priv_data *mp;
	पूर्णांक i;

	spin_lock_init(&data_lock);

	क्रम (i = 0; i < num_ovls; ++i) अणु
		काष्ठा ovl_priv_data *op;

		op = &dss_data.ovl_priv_data_array[i];

		op->info.color_mode = OMAP_DSS_COLOR_RGB16;
		op->info.rotation_type = OMAP_DSS_ROT_DMA;

		op->info.global_alpha = 255;

		चयन (i) अणु
		हाल 0:
			op->info.zorder = 0;
			अवरोध;
		हाल 1:
			op->info.zorder =
				dss_has_feature(FEAT_ALPHA_FREE_ZORDER) ? 3 : 0;
			अवरोध;
		हाल 2:
			op->info.zorder =
				dss_has_feature(FEAT_ALPHA_FREE_ZORDER) ? 2 : 0;
			अवरोध;
		हाल 3:
			op->info.zorder =
				dss_has_feature(FEAT_ALPHA_FREE_ZORDER) ? 1 : 0;
			अवरोध;
		पूर्ण

		op->user_info = op->info;
	पूर्ण

	/*
	 * Initialize some of the lcd_config fields क्रम TV manager, this lets
	 * us prevent checking अगर the manager is LCD or TV at some places
	 */
	mp = &dss_data.mgr_priv_data_array[OMAP_DSS_CHANNEL_DIGIT];

	mp->lcd_config.video_port_width = 24;
	mp->lcd_config.घड़ी_info.lck_भाग = 1;
	mp->lcd_config.घड़ी_info.pck_भाग = 1;
पूर्ण

/*
 * A LCD manager's stallmode decides whether it is in manual or स्वतः update. TV
 * manager is always स्वतः update, stallmode field क्रम TV manager is false by
 * शेष
 */
अटल bool ovl_manual_update(काष्ठा omap_overlay *ovl)
अणु
	काष्ठा mgr_priv_data *mp = get_mgr_priv(ovl->manager);

	वापस mp->lcd_config.stallmode;
पूर्ण

अटल bool mgr_manual_update(काष्ठा omap_overlay_manager *mgr)
अणु
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);

	वापस mp->lcd_config.stallmode;
पूर्ण

अटल पूर्णांक dss_check_settings_low(काष्ठा omap_overlay_manager *mgr,
		bool applying)
अणु
	काष्ठा omap_overlay_info *oi;
	काष्ठा omap_overlay_manager_info *mi;
	काष्ठा omap_overlay *ovl;
	काष्ठा omap_overlay_info *ois[MAX_DSS_OVERLAYS];
	काष्ठा ovl_priv_data *op;
	काष्ठा mgr_priv_data *mp;

	mp = get_mgr_priv(mgr);

	अगर (!mp->enabled)
		वापस 0;

	अगर (applying && mp->user_info_dirty)
		mi = &mp->user_info;
	अन्यथा
		mi = &mp->info;

	/* collect the infos to be tested पूर्णांकo the array */
	list_क्रम_each_entry(ovl, &mgr->overlays, list) अणु
		op = get_ovl_priv(ovl);

		अगर (!op->enabled && !op->enabling)
			oi = शून्य;
		अन्यथा अगर (applying && op->user_info_dirty)
			oi = &op->user_info;
		अन्यथा
			oi = &op->info;

		ois[ovl->id] = oi;
	पूर्ण

	वापस dss_mgr_check(mgr, mi, &mp->timings, &mp->lcd_config, ois);
पूर्ण

/*
 * check manager and overlay settings using overlay_info from data->info
 */
अटल पूर्णांक dss_check_settings(काष्ठा omap_overlay_manager *mgr)
अणु
	वापस dss_check_settings_low(mgr, false);
पूर्ण

/*
 * check manager and overlay settings using overlay_info from ovl->info अगर
 * dirty and from data->info otherwise
 */
अटल पूर्णांक dss_check_settings_apply(काष्ठा omap_overlay_manager *mgr)
अणु
	वापस dss_check_settings_low(mgr, true);
पूर्ण

अटल bool need_isr(व्योम)
अणु
	स्थिर पूर्णांक num_mgrs = dss_feat_get_num_mgrs();
	पूर्णांक i;

	क्रम (i = 0; i < num_mgrs; ++i) अणु
		काष्ठा omap_overlay_manager *mgr;
		काष्ठा mgr_priv_data *mp;
		काष्ठा omap_overlay *ovl;

		mgr = omap_dss_get_overlay_manager(i);
		mp = get_mgr_priv(mgr);

		अगर (!mp->enabled)
			जारी;

		अगर (mgr_manual_update(mgr)) अणु
			/* to catch FRAMEDONE */
			अगर (mp->updating)
				वापस true;
		पूर्ण अन्यथा अणु
			/* to catch GO bit going करोwn */
			अगर (mp->busy)
				वापस true;

			/* to ग_लिखो new values to रेजिस्टरs */
			अगर (mp->info_dirty)
				वापस true;

			/* to set GO bit */
			अगर (mp->shaकरोw_info_dirty)
				वापस true;

			/*
			 * NOTE: we करोn't check extra_info flags क्रम disabled
			 * managers, once the manager is enabled, the extra_info
			 * related manager changes will be taken in by HW.
			 */

			/* to ग_लिखो new values to रेजिस्टरs */
			अगर (mp->extra_info_dirty)
				वापस true;

			/* to set GO bit */
			अगर (mp->shaकरोw_extra_info_dirty)
				वापस true;

			list_क्रम_each_entry(ovl, &mgr->overlays, list) अणु
				काष्ठा ovl_priv_data *op;

				op = get_ovl_priv(ovl);

				/*
				 * NOTE: we check extra_info flags even क्रम
				 * disabled overlays, as extra_infos need to be
				 * always written.
				 */

				/* to ग_लिखो new values to रेजिस्टरs */
				अगर (op->extra_info_dirty)
					वापस true;

				/* to set GO bit */
				अगर (op->shaकरोw_extra_info_dirty)
					वापस true;

				अगर (!op->enabled)
					जारी;

				/* to ग_लिखो new values to रेजिस्टरs */
				अगर (op->info_dirty)
					वापस true;

				/* to set GO bit */
				अगर (op->shaकरोw_info_dirty)
					वापस true;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

अटल bool need_go(काष्ठा omap_overlay_manager *mgr)
अणु
	काष्ठा omap_overlay *ovl;
	काष्ठा mgr_priv_data *mp;
	काष्ठा ovl_priv_data *op;

	mp = get_mgr_priv(mgr);

	अगर (mp->shaकरोw_info_dirty || mp->shaकरोw_extra_info_dirty)
		वापस true;

	list_क्रम_each_entry(ovl, &mgr->overlays, list) अणु
		op = get_ovl_priv(ovl);
		अगर (op->shaकरोw_info_dirty || op->shaकरोw_extra_info_dirty)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* वापसs true अगर an extra_info field is currently being updated */
अटल bool extra_info_update_ongoing(व्योम)
अणु
	स्थिर पूर्णांक num_mgrs = dss_feat_get_num_mgrs();
	पूर्णांक i;

	क्रम (i = 0; i < num_mgrs; ++i) अणु
		काष्ठा omap_overlay_manager *mgr;
		काष्ठा omap_overlay *ovl;
		काष्ठा mgr_priv_data *mp;

		mgr = omap_dss_get_overlay_manager(i);
		mp = get_mgr_priv(mgr);

		अगर (!mp->enabled)
			जारी;

		अगर (!mp->updating)
			जारी;

		अगर (mp->extra_info_dirty || mp->shaकरोw_extra_info_dirty)
			वापस true;

		list_क्रम_each_entry(ovl, &mgr->overlays, list) अणु
			काष्ठा ovl_priv_data *op = get_ovl_priv(ovl);

			अगर (op->extra_info_dirty || op->shaकरोw_extra_info_dirty)
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

/* रुको until no extra_info updates are pending */
अटल व्योम रुको_pending_extra_info_updates(व्योम)
अणु
	bool updating;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ t;
	पूर्णांक r;

	spin_lock_irqsave(&data_lock, flags);

	updating = extra_info_update_ongoing();

	अगर (!updating) अणु
		spin_unlock_irqrestore(&data_lock, flags);
		वापस;
	पूर्ण

	init_completion(&extra_updated_completion);

	spin_unlock_irqrestore(&data_lock, flags);

	t = msecs_to_jअगरfies(500);
	r = रुको_क्रम_completion_समयout(&extra_updated_completion, t);
	अगर (r == 0)
		DSSWARN("timeout in wait_pending_extra_info_updates\n");
पूर्ण

अटल काष्ठा omap_dss_device *dss_mgr_get_device(काष्ठा omap_overlay_manager *mgr)
अणु
	काष्ठा omap_dss_device *dssdev;

	dssdev = mgr->output;
	अगर (dssdev == शून्य)
		वापस शून्य;

	जबतक (dssdev->dst)
		dssdev = dssdev->dst;

	अगर (dssdev->driver)
		वापस dssdev;
	अन्यथा
		वापस शून्य;
पूर्ण

अटल काष्ठा omap_dss_device *dss_ovl_get_device(काष्ठा omap_overlay *ovl)
अणु
	वापस ovl->manager ? dss_mgr_get_device(ovl->manager) : शून्य;
पूर्ण

अटल पूर्णांक dss_mgr_रुको_क्रम_vsync(काष्ठा omap_overlay_manager *mgr)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(500);
	u32 irq;
	पूर्णांक r;

	अगर (mgr->output == शून्य)
		वापस -ENODEV;

	r = dispc_runसमय_get();
	अगर (r)
		वापस r;

	चयन (mgr->output->id) अणु
	हाल OMAP_DSS_OUTPUT_VENC:
		irq = DISPC_IRQ_EVSYNC_ODD;
		अवरोध;
	हाल OMAP_DSS_OUTPUT_HDMI:
		irq = DISPC_IRQ_EVSYNC_EVEN;
		अवरोध;
	शेष:
		irq = dispc_mgr_get_vsync_irq(mgr->id);
		अवरोध;
	पूर्ण

	r = omap_dispc_रुको_क्रम_irq_पूर्णांकerruptible_समयout(irq, समयout);

	dispc_runसमय_put();

	वापस r;
पूर्ण

अटल पूर्णांक dss_mgr_रुको_क्रम_go(काष्ठा omap_overlay_manager *mgr)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(500);
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);
	u32 irq;
	अचिन्हित दीर्घ flags;
	पूर्णांक r;
	पूर्णांक i;

	spin_lock_irqsave(&data_lock, flags);

	अगर (mgr_manual_update(mgr)) अणु
		spin_unlock_irqrestore(&data_lock, flags);
		वापस 0;
	पूर्ण

	अगर (!mp->enabled) अणु
		spin_unlock_irqrestore(&data_lock, flags);
		वापस 0;
	पूर्ण

	spin_unlock_irqrestore(&data_lock, flags);

	r = dispc_runसमय_get();
	अगर (r)
		वापस r;

	irq = dispc_mgr_get_vsync_irq(mgr->id);

	i = 0;
	जबतक (1) अणु
		bool shaकरोw_dirty, dirty;

		spin_lock_irqsave(&data_lock, flags);
		dirty = mp->info_dirty;
		shaकरोw_dirty = mp->shaकरोw_info_dirty;
		spin_unlock_irqrestore(&data_lock, flags);

		अगर (!dirty && !shaकरोw_dirty) अणु
			r = 0;
			अवरोध;
		पूर्ण

		/* 4 iterations is the worst हाल:
		 * 1 - initial iteration, dirty = true (between VFP and VSYNC)
		 * 2 - first VSYNC, dirty = true
		 * 3 - dirty = false, shaकरोw_dirty = true
		 * 4 - shaकरोw_dirty = false */
		अगर (i++ == 3) अणु
			DSSERR("mgr(%d)->wait_for_go() not finishing\n",
					mgr->id);
			r = 0;
			अवरोध;
		पूर्ण

		r = omap_dispc_रुको_क्रम_irq_पूर्णांकerruptible_समयout(irq, समयout);
		अगर (r == -ERESTARTSYS)
			अवरोध;

		अगर (r) अणु
			DSSERR("mgr(%d)->wait_for_go() timeout\n", mgr->id);
			अवरोध;
		पूर्ण
	पूर्ण

	dispc_runसमय_put();

	वापस r;
पूर्ण

अटल पूर्णांक dss_mgr_रुको_क्रम_go_ovl(काष्ठा omap_overlay *ovl)
अणु
	अचिन्हित दीर्घ समयout = msecs_to_jअगरfies(500);
	काष्ठा ovl_priv_data *op;
	काष्ठा mgr_priv_data *mp;
	u32 irq;
	अचिन्हित दीर्घ flags;
	पूर्णांक r;
	पूर्णांक i;

	अगर (!ovl->manager)
		वापस 0;

	mp = get_mgr_priv(ovl->manager);

	spin_lock_irqsave(&data_lock, flags);

	अगर (ovl_manual_update(ovl)) अणु
		spin_unlock_irqrestore(&data_lock, flags);
		वापस 0;
	पूर्ण

	अगर (!mp->enabled) अणु
		spin_unlock_irqrestore(&data_lock, flags);
		वापस 0;
	पूर्ण

	spin_unlock_irqrestore(&data_lock, flags);

	r = dispc_runसमय_get();
	अगर (r)
		वापस r;

	irq = dispc_mgr_get_vsync_irq(ovl->manager->id);

	op = get_ovl_priv(ovl);
	i = 0;
	जबतक (1) अणु
		bool shaकरोw_dirty, dirty;

		spin_lock_irqsave(&data_lock, flags);
		dirty = op->info_dirty;
		shaकरोw_dirty = op->shaकरोw_info_dirty;
		spin_unlock_irqrestore(&data_lock, flags);

		अगर (!dirty && !shaकरोw_dirty) अणु
			r = 0;
			अवरोध;
		पूर्ण

		/* 4 iterations is the worst हाल:
		 * 1 - initial iteration, dirty = true (between VFP and VSYNC)
		 * 2 - first VSYNC, dirty = true
		 * 3 - dirty = false, shaकरोw_dirty = true
		 * 4 - shaकरोw_dirty = false */
		अगर (i++ == 3) अणु
			DSSERR("ovl(%d)->wait_for_go() not finishing\n",
					ovl->id);
			r = 0;
			अवरोध;
		पूर्ण

		r = omap_dispc_रुको_क्रम_irq_पूर्णांकerruptible_समयout(irq, समयout);
		अगर (r == -ERESTARTSYS)
			अवरोध;

		अगर (r) अणु
			DSSERR("ovl(%d)->wait_for_go() timeout\n", ovl->id);
			अवरोध;
		पूर्ण
	पूर्ण

	dispc_runसमय_put();

	वापस r;
पूर्ण

अटल व्योम dss_ovl_ग_लिखो_regs(काष्ठा omap_overlay *ovl)
अणु
	काष्ठा ovl_priv_data *op = get_ovl_priv(ovl);
	काष्ठा omap_overlay_info *oi;
	bool replication;
	काष्ठा mgr_priv_data *mp;
	पूर्णांक r;

	DSSDBG("writing ovl %d regs\n", ovl->id);

	अगर (!op->enabled || !op->info_dirty)
		वापस;

	oi = &op->info;

	mp = get_mgr_priv(ovl->manager);

	replication = dss_ovl_use_replication(mp->lcd_config, oi->color_mode);

	r = dispc_ovl_setup(ovl->id, oi, replication, &mp->timings, false);
	अगर (r) अणु
		/*
		 * We can't करो much here, as this function can be called from
		 * vsync पूर्णांकerrupt.
		 */
		DSSERR("dispc_ovl_setup failed for ovl %d\n", ovl->id);

		/* This will leave fअगरo configurations in a nonoptimal state */
		op->enabled = false;
		dispc_ovl_enable(ovl->id, false);
		वापस;
	पूर्ण

	op->info_dirty = false;
	अगर (mp->updating)
		op->shaकरोw_info_dirty = true;
पूर्ण

अटल व्योम dss_ovl_ग_लिखो_regs_extra(काष्ठा omap_overlay *ovl)
अणु
	काष्ठा ovl_priv_data *op = get_ovl_priv(ovl);
	काष्ठा mgr_priv_data *mp;

	DSSDBG("writing ovl %d regs extra\n", ovl->id);

	अगर (!op->extra_info_dirty)
		वापस;

	/* note: ग_लिखो also when op->enabled == false, so that the ovl माला_लो
	 * disabled */

	dispc_ovl_enable(ovl->id, op->enabled);
	dispc_ovl_set_fअगरo_threshold(ovl->id, op->fअगरo_low, op->fअगरo_high);

	mp = get_mgr_priv(ovl->manager);

	op->extra_info_dirty = false;
	अगर (mp->updating)
		op->shaकरोw_extra_info_dirty = true;
पूर्ण

अटल व्योम dss_mgr_ग_लिखो_regs(काष्ठा omap_overlay_manager *mgr)
अणु
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);
	काष्ठा omap_overlay *ovl;

	DSSDBG("writing mgr %d regs\n", mgr->id);

	अगर (!mp->enabled)
		वापस;

	WARN_ON(mp->busy);

	/* Commit overlay settings */
	list_क्रम_each_entry(ovl, &mgr->overlays, list) अणु
		dss_ovl_ग_लिखो_regs(ovl);
		dss_ovl_ग_लिखो_regs_extra(ovl);
	पूर्ण

	अगर (mp->info_dirty) अणु
		dispc_mgr_setup(mgr->id, &mp->info);

		mp->info_dirty = false;
		अगर (mp->updating)
			mp->shaकरोw_info_dirty = true;
	पूर्ण
पूर्ण

अटल व्योम dss_mgr_ग_लिखो_regs_extra(काष्ठा omap_overlay_manager *mgr)
अणु
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);

	DSSDBG("writing mgr %d regs extra\n", mgr->id);

	अगर (!mp->extra_info_dirty)
		वापस;

	dispc_mgr_set_timings(mgr->id, &mp->timings);

	/* lcd_config parameters */
	अगर (dss_mgr_is_lcd(mgr->id))
		dispc_mgr_set_lcd_config(mgr->id, &mp->lcd_config);

	mp->extra_info_dirty = false;
	अगर (mp->updating)
		mp->shaकरोw_extra_info_dirty = true;
पूर्ण

अटल व्योम dss_ग_लिखो_regs(व्योम)
अणु
	स्थिर पूर्णांक num_mgrs = omap_dss_get_num_overlay_managers();
	पूर्णांक i;

	क्रम (i = 0; i < num_mgrs; ++i) अणु
		काष्ठा omap_overlay_manager *mgr;
		काष्ठा mgr_priv_data *mp;
		पूर्णांक r;

		mgr = omap_dss_get_overlay_manager(i);
		mp = get_mgr_priv(mgr);

		अगर (!mp->enabled || mgr_manual_update(mgr) || mp->busy)
			जारी;

		r = dss_check_settings(mgr);
		अगर (r) अणु
			DSSERR("cannot write registers for manager %s: "
					"illegal configuration\n", mgr->name);
			जारी;
		पूर्ण

		dss_mgr_ग_लिखो_regs(mgr);
		dss_mgr_ग_लिखो_regs_extra(mgr);
	पूर्ण
पूर्ण

अटल व्योम dss_set_go_bits(व्योम)
अणु
	स्थिर पूर्णांक num_mgrs = omap_dss_get_num_overlay_managers();
	पूर्णांक i;

	क्रम (i = 0; i < num_mgrs; ++i) अणु
		काष्ठा omap_overlay_manager *mgr;
		काष्ठा mgr_priv_data *mp;

		mgr = omap_dss_get_overlay_manager(i);
		mp = get_mgr_priv(mgr);

		अगर (!mp->enabled || mgr_manual_update(mgr) || mp->busy)
			जारी;

		अगर (!need_go(mgr))
			जारी;

		mp->busy = true;

		अगर (!dss_data.irq_enabled && need_isr())
			dss_रेजिस्टर_vsync_isr();

		dispc_mgr_go(mgr->id);
	पूर्ण

पूर्ण

अटल व्योम mgr_clear_shaकरोw_dirty(काष्ठा omap_overlay_manager *mgr)
अणु
	काष्ठा omap_overlay *ovl;
	काष्ठा mgr_priv_data *mp;
	काष्ठा ovl_priv_data *op;

	mp = get_mgr_priv(mgr);
	mp->shaकरोw_info_dirty = false;
	mp->shaकरोw_extra_info_dirty = false;

	list_क्रम_each_entry(ovl, &mgr->overlays, list) अणु
		op = get_ovl_priv(ovl);
		op->shaकरोw_info_dirty = false;
		op->shaकरोw_extra_info_dirty = false;
	पूर्ण
पूर्ण

अटल पूर्णांक dss_mgr_connect_compat(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omap_dss_device *dst)
अणु
	वापस mgr->set_output(mgr, dst);
पूर्ण

अटल व्योम dss_mgr_disconnect_compat(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omap_dss_device *dst)
अणु
	mgr->unset_output(mgr);
पूर्ण

अटल व्योम dss_mgr_start_update_compat(काष्ठा omap_overlay_manager *mgr)
अणु
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	spin_lock_irqsave(&data_lock, flags);

	WARN_ON(mp->updating);

	r = dss_check_settings(mgr);
	अगर (r) अणु
		DSSERR("cannot start manual update: illegal configuration\n");
		spin_unlock_irqrestore(&data_lock, flags);
		वापस;
	पूर्ण

	dss_mgr_ग_लिखो_regs(mgr);
	dss_mgr_ग_लिखो_regs_extra(mgr);

	mp->updating = true;

	अगर (!dss_data.irq_enabled && need_isr())
		dss_रेजिस्टर_vsync_isr();

	dispc_mgr_enable_sync(mgr->id);

	spin_unlock_irqrestore(&data_lock, flags);
पूर्ण

अटल व्योम dss_apply_irq_handler(व्योम *data, u32 mask);

अटल व्योम dss_रेजिस्टर_vsync_isr(व्योम)
अणु
	स्थिर पूर्णांक num_mgrs = dss_feat_get_num_mgrs();
	u32 mask;
	पूर्णांक r, i;

	mask = 0;
	क्रम (i = 0; i < num_mgrs; ++i)
		mask |= dispc_mgr_get_vsync_irq(i);

	क्रम (i = 0; i < num_mgrs; ++i)
		mask |= dispc_mgr_get_frameकरोne_irq(i);

	r = omap_dispc_रेजिस्टर_isr(dss_apply_irq_handler, शून्य, mask);
	WARN_ON(r);

	dss_data.irq_enabled = true;
पूर्ण

अटल व्योम dss_unरेजिस्टर_vsync_isr(व्योम)
अणु
	स्थिर पूर्णांक num_mgrs = dss_feat_get_num_mgrs();
	u32 mask;
	पूर्णांक r, i;

	mask = 0;
	क्रम (i = 0; i < num_mgrs; ++i)
		mask |= dispc_mgr_get_vsync_irq(i);

	क्रम (i = 0; i < num_mgrs; ++i)
		mask |= dispc_mgr_get_frameकरोne_irq(i);

	r = omap_dispc_unरेजिस्टर_isr(dss_apply_irq_handler, शून्य, mask);
	WARN_ON(r);

	dss_data.irq_enabled = false;
पूर्ण

अटल व्योम dss_apply_irq_handler(व्योम *data, u32 mask)
अणु
	स्थिर पूर्णांक num_mgrs = dss_feat_get_num_mgrs();
	पूर्णांक i;
	bool extra_updating;

	spin_lock(&data_lock);

	/* clear busy, updating flags, shaकरोw_dirty flags */
	क्रम (i = 0; i < num_mgrs; i++) अणु
		काष्ठा omap_overlay_manager *mgr;
		काष्ठा mgr_priv_data *mp;

		mgr = omap_dss_get_overlay_manager(i);
		mp = get_mgr_priv(mgr);

		अगर (!mp->enabled)
			जारी;

		mp->updating = dispc_mgr_is_enabled(i);

		अगर (!mgr_manual_update(mgr)) अणु
			bool was_busy = mp->busy;
			mp->busy = dispc_mgr_go_busy(i);

			अगर (was_busy && !mp->busy)
				mgr_clear_shaकरोw_dirty(mgr);
		पूर्ण
	पूर्ण

	dss_ग_लिखो_regs();
	dss_set_go_bits();

	extra_updating = extra_info_update_ongoing();
	अगर (!extra_updating)
		complete_all(&extra_updated_completion);

	/* call frameकरोne handlers क्रम manual update displays */
	क्रम (i = 0; i < num_mgrs; i++) अणु
		काष्ठा omap_overlay_manager *mgr;
		काष्ठा mgr_priv_data *mp;

		mgr = omap_dss_get_overlay_manager(i);
		mp = get_mgr_priv(mgr);

		अगर (!mgr_manual_update(mgr) || !mp->frameकरोne_handler)
			जारी;

		अगर (mask & dispc_mgr_get_frameकरोne_irq(i))
			mp->frameकरोne_handler(mp->frameकरोne_handler_data);
	पूर्ण

	अगर (!need_isr())
		dss_unरेजिस्टर_vsync_isr();

	spin_unlock(&data_lock);
पूर्ण

अटल व्योम omap_dss_mgr_apply_ovl(काष्ठा omap_overlay *ovl)
अणु
	काष्ठा ovl_priv_data *op;

	op = get_ovl_priv(ovl);

	अगर (!op->user_info_dirty)
		वापस;

	op->user_info_dirty = false;
	op->info_dirty = true;
	op->info = op->user_info;
पूर्ण

अटल व्योम omap_dss_mgr_apply_mgr(काष्ठा omap_overlay_manager *mgr)
अणु
	काष्ठा mgr_priv_data *mp;

	mp = get_mgr_priv(mgr);

	अगर (!mp->user_info_dirty)
		वापस;

	mp->user_info_dirty = false;
	mp->info_dirty = true;
	mp->info = mp->user_info;
पूर्ण

अटल पूर्णांक omap_dss_mgr_apply(काष्ठा omap_overlay_manager *mgr)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा omap_overlay *ovl;
	पूर्णांक r;

	DSSDBG("omap_dss_mgr_apply(%s)\n", mgr->name);

	spin_lock_irqsave(&data_lock, flags);

	r = dss_check_settings_apply(mgr);
	अगर (r) अणु
		spin_unlock_irqrestore(&data_lock, flags);
		DSSERR("failed to apply settings: illegal configuration.\n");
		वापस r;
	पूर्ण

	/* Configure overlays */
	list_क्रम_each_entry(ovl, &mgr->overlays, list)
		omap_dss_mgr_apply_ovl(ovl);

	/* Configure manager */
	omap_dss_mgr_apply_mgr(mgr);

	dss_ग_लिखो_regs();
	dss_set_go_bits();

	spin_unlock_irqrestore(&data_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम dss_apply_ovl_enable(काष्ठा omap_overlay *ovl, bool enable)
अणु
	काष्ठा ovl_priv_data *op;

	op = get_ovl_priv(ovl);

	अगर (op->enabled == enable)
		वापस;

	op->enabled = enable;
	op->extra_info_dirty = true;
पूर्ण

अटल व्योम dss_apply_ovl_fअगरo_thresholds(काष्ठा omap_overlay *ovl,
		u32 fअगरo_low, u32 fअगरo_high)
अणु
	काष्ठा ovl_priv_data *op = get_ovl_priv(ovl);

	अगर (op->fअगरo_low == fअगरo_low && op->fअगरo_high == fअगरo_high)
		वापस;

	op->fअगरo_low = fअगरo_low;
	op->fअगरo_high = fअगरo_high;
	op->extra_info_dirty = true;
पूर्ण

अटल व्योम dss_ovl_setup_fअगरo(काष्ठा omap_overlay *ovl)
अणु
	काष्ठा ovl_priv_data *op = get_ovl_priv(ovl);
	u32 fअगरo_low, fअगरo_high;
	bool use_fअगरo_merge = false;

	अगर (!op->enabled && !op->enabling)
		वापस;

	dispc_ovl_compute_fअगरo_thresholds(ovl->id, &fअगरo_low, &fअगरo_high,
			use_fअगरo_merge, ovl_manual_update(ovl));

	dss_apply_ovl_fअगरo_thresholds(ovl, fअगरo_low, fअगरo_high);
पूर्ण

अटल व्योम dss_mgr_setup_fअगरos(काष्ठा omap_overlay_manager *mgr)
अणु
	काष्ठा omap_overlay *ovl;
	काष्ठा mgr_priv_data *mp;

	mp = get_mgr_priv(mgr);

	अगर (!mp->enabled)
		वापस;

	list_क्रम_each_entry(ovl, &mgr->overlays, list)
		dss_ovl_setup_fअगरo(ovl);
पूर्ण

अटल व्योम dss_setup_fअगरos(व्योम)
अणु
	स्थिर पूर्णांक num_mgrs = omap_dss_get_num_overlay_managers();
	काष्ठा omap_overlay_manager *mgr;
	पूर्णांक i;

	क्रम (i = 0; i < num_mgrs; ++i) अणु
		mgr = omap_dss_get_overlay_manager(i);
		dss_mgr_setup_fअगरos(mgr);
	पूर्ण
पूर्ण

अटल पूर्णांक dss_mgr_enable_compat(काष्ठा omap_overlay_manager *mgr)
अणु
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	mutex_lock(&apply_lock);

	अगर (mp->enabled)
		जाओ out;

	spin_lock_irqsave(&data_lock, flags);

	mp->enabled = true;

	r = dss_check_settings(mgr);
	अगर (r) अणु
		DSSERR("failed to enable manager %d: check_settings failed\n",
				mgr->id);
		जाओ err;
	पूर्ण

	dss_setup_fअगरos();

	dss_ग_लिखो_regs();
	dss_set_go_bits();

	अगर (!mgr_manual_update(mgr))
		mp->updating = true;

	अगर (!dss_data.irq_enabled && need_isr())
		dss_रेजिस्टर_vsync_isr();

	spin_unlock_irqrestore(&data_lock, flags);

	अगर (!mgr_manual_update(mgr))
		dispc_mgr_enable_sync(mgr->id);

out:
	mutex_unlock(&apply_lock);

	वापस 0;

err:
	mp->enabled = false;
	spin_unlock_irqrestore(&data_lock, flags);
	mutex_unlock(&apply_lock);
	वापस r;
पूर्ण

अटल व्योम dss_mgr_disable_compat(काष्ठा omap_overlay_manager *mgr)
अणु
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);
	अचिन्हित दीर्घ flags;

	mutex_lock(&apply_lock);

	अगर (!mp->enabled)
		जाओ out;

	रुको_pending_extra_info_updates();

	अगर (!mgr_manual_update(mgr))
		dispc_mgr_disable_sync(mgr->id);

	spin_lock_irqsave(&data_lock, flags);

	mp->updating = false;
	mp->enabled = false;

	spin_unlock_irqrestore(&data_lock, flags);

out:
	mutex_unlock(&apply_lock);
पूर्ण

अटल पूर्णांक dss_mgr_set_info(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omap_overlay_manager_info *info)
अणु
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	r = dss_mgr_simple_check(mgr, info);
	अगर (r)
		वापस r;

	spin_lock_irqsave(&data_lock, flags);

	mp->user_info = *info;
	mp->user_info_dirty = true;

	spin_unlock_irqrestore(&data_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम dss_mgr_get_info(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omap_overlay_manager_info *info)
अणु
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&data_lock, flags);

	*info = mp->user_info;

	spin_unlock_irqrestore(&data_lock, flags);
पूर्ण

अटल पूर्णांक dss_mgr_set_output(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omap_dss_device *output)
अणु
	पूर्णांक r;

	mutex_lock(&apply_lock);

	अगर (mgr->output) अणु
		DSSERR("manager %s is already connected to an output\n",
			mgr->name);
		r = -EINVAL;
		जाओ err;
	पूर्ण

	अगर ((mgr->supported_outमाला_दो & output->id) == 0) अणु
		DSSERR("output does not support manager %s\n",
			mgr->name);
		r = -EINVAL;
		जाओ err;
	पूर्ण

	output->manager = mgr;
	mgr->output = output;

	mutex_unlock(&apply_lock);

	वापस 0;
err:
	mutex_unlock(&apply_lock);
	वापस r;
पूर्ण

अटल पूर्णांक dss_mgr_unset_output(काष्ठा omap_overlay_manager *mgr)
अणु
	पूर्णांक r;
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);
	अचिन्हित दीर्घ flags;

	mutex_lock(&apply_lock);

	अगर (!mgr->output) अणु
		DSSERR("failed to unset output, output not set\n");
		r = -EINVAL;
		जाओ err;
	पूर्ण

	spin_lock_irqsave(&data_lock, flags);

	अगर (mp->enabled) अणु
		DSSERR("output can't be unset when manager is enabled\n");
		r = -EINVAL;
		जाओ err1;
	पूर्ण

	spin_unlock_irqrestore(&data_lock, flags);

	mgr->output->manager = शून्य;
	mgr->output = शून्य;

	mutex_unlock(&apply_lock);

	वापस 0;
err1:
	spin_unlock_irqrestore(&data_lock, flags);
err:
	mutex_unlock(&apply_lock);

	वापस r;
पूर्ण

अटल व्योम dss_apply_mgr_timings(काष्ठा omap_overlay_manager *mgr,
		स्थिर काष्ठा omap_video_timings *timings)
अणु
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);

	mp->timings = *timings;
	mp->extra_info_dirty = true;
पूर्ण

अटल व्योम dss_mgr_set_timings_compat(काष्ठा omap_overlay_manager *mgr,
		स्थिर काष्ठा omap_video_timings *timings)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);

	spin_lock_irqsave(&data_lock, flags);

	अगर (mp->updating) अणु
		DSSERR("cannot set timings for %s: manager needs to be disabled\n",
			mgr->name);
		जाओ out;
	पूर्ण

	dss_apply_mgr_timings(mgr, timings);
out:
	spin_unlock_irqrestore(&data_lock, flags);
पूर्ण

अटल व्योम dss_apply_mgr_lcd_config(काष्ठा omap_overlay_manager *mgr,
		स्थिर काष्ठा dss_lcd_mgr_config *config)
अणु
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);

	mp->lcd_config = *config;
	mp->extra_info_dirty = true;
पूर्ण

अटल व्योम dss_mgr_set_lcd_config_compat(काष्ठा omap_overlay_manager *mgr,
		स्थिर काष्ठा dss_lcd_mgr_config *config)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);

	spin_lock_irqsave(&data_lock, flags);

	अगर (mp->enabled) अणु
		DSSERR("cannot apply lcd config for %s: manager needs to be disabled\n",
			mgr->name);
		जाओ out;
	पूर्ण

	dss_apply_mgr_lcd_config(mgr, config);
out:
	spin_unlock_irqrestore(&data_lock, flags);
पूर्ण

अटल पूर्णांक dss_ovl_set_info(काष्ठा omap_overlay *ovl,
		काष्ठा omap_overlay_info *info)
अणु
	काष्ठा ovl_priv_data *op = get_ovl_priv(ovl);
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	r = dss_ovl_simple_check(ovl, info);
	अगर (r)
		वापस r;

	spin_lock_irqsave(&data_lock, flags);

	op->user_info = *info;
	op->user_info_dirty = true;

	spin_unlock_irqrestore(&data_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम dss_ovl_get_info(काष्ठा omap_overlay *ovl,
		काष्ठा omap_overlay_info *info)
अणु
	काष्ठा ovl_priv_data *op = get_ovl_priv(ovl);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&data_lock, flags);

	*info = op->user_info;

	spin_unlock_irqrestore(&data_lock, flags);
पूर्ण

अटल पूर्णांक dss_ovl_set_manager(काष्ठा omap_overlay *ovl,
		काष्ठा omap_overlay_manager *mgr)
अणु
	काष्ठा ovl_priv_data *op = get_ovl_priv(ovl);
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	अगर (!mgr)
		वापस -EINVAL;

	mutex_lock(&apply_lock);

	अगर (ovl->manager) अणु
		DSSERR("overlay '%s' already has a manager '%s'\n",
				ovl->name, ovl->manager->name);
		r = -EINVAL;
		जाओ err;
	पूर्ण

	r = dispc_runसमय_get();
	अगर (r)
		जाओ err;

	spin_lock_irqsave(&data_lock, flags);

	अगर (op->enabled) अणु
		spin_unlock_irqrestore(&data_lock, flags);
		DSSERR("overlay has to be disabled to change the manager\n");
		r = -EINVAL;
		जाओ err1;
	पूर्ण

	dispc_ovl_set_channel_out(ovl->id, mgr->id);

	ovl->manager = mgr;
	list_add_tail(&ovl->list, &mgr->overlays);

	spin_unlock_irqrestore(&data_lock, flags);

	dispc_runसमय_put();

	mutex_unlock(&apply_lock);

	वापस 0;

err1:
	dispc_runसमय_put();
err:
	mutex_unlock(&apply_lock);
	वापस r;
पूर्ण

अटल पूर्णांक dss_ovl_unset_manager(काष्ठा omap_overlay *ovl)
अणु
	काष्ठा ovl_priv_data *op = get_ovl_priv(ovl);
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	mutex_lock(&apply_lock);

	अगर (!ovl->manager) अणु
		DSSERR("failed to detach overlay: manager not set\n");
		r = -EINVAL;
		जाओ err;
	पूर्ण

	spin_lock_irqsave(&data_lock, flags);

	अगर (op->enabled) अणु
		spin_unlock_irqrestore(&data_lock, flags);
		DSSERR("overlay has to be disabled to unset the manager\n");
		r = -EINVAL;
		जाओ err;
	पूर्ण

	spin_unlock_irqrestore(&data_lock, flags);

	/* रुको क्रम pending extra_info updates to ensure the ovl is disabled */
	रुको_pending_extra_info_updates();

	/*
	 * For a manual update display, there is no guarantee that the overlay
	 * is really disabled in HW, we may need an extra update from this
	 * manager beक्रमe the configurations can go in. Return an error अगर the
	 * overlay needed an update from the manager.
	 *
	 * TODO: Instead of वापसing an error, try to करो a dummy manager update
	 * here to disable the overlay in hardware. Use the *GATED fields in
	 * the DISPC_CONFIG रेजिस्टरs to करो a dummy update.
	 */
	spin_lock_irqsave(&data_lock, flags);

	अगर (ovl_manual_update(ovl) && op->extra_info_dirty) अणु
		spin_unlock_irqrestore(&data_lock, flags);
		DSSERR("need an update to change the manager\n");
		r = -EINVAL;
		जाओ err;
	पूर्ण

	ovl->manager = शून्य;
	list_del(&ovl->list);

	spin_unlock_irqrestore(&data_lock, flags);

	mutex_unlock(&apply_lock);

	वापस 0;
err:
	mutex_unlock(&apply_lock);
	वापस r;
पूर्ण

अटल bool dss_ovl_is_enabled(काष्ठा omap_overlay *ovl)
अणु
	काष्ठा ovl_priv_data *op = get_ovl_priv(ovl);
	अचिन्हित दीर्घ flags;
	bool e;

	spin_lock_irqsave(&data_lock, flags);

	e = op->enabled;

	spin_unlock_irqrestore(&data_lock, flags);

	वापस e;
पूर्ण

अटल पूर्णांक dss_ovl_enable(काष्ठा omap_overlay *ovl)
अणु
	काष्ठा ovl_priv_data *op = get_ovl_priv(ovl);
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	mutex_lock(&apply_lock);

	अगर (op->enabled) अणु
		r = 0;
		जाओ err1;
	पूर्ण

	अगर (ovl->manager == शून्य || ovl->manager->output == शून्य) अणु
		r = -EINVAL;
		जाओ err1;
	पूर्ण

	spin_lock_irqsave(&data_lock, flags);

	op->enabling = true;

	r = dss_check_settings(ovl->manager);
	अगर (r) अणु
		DSSERR("failed to enable overlay %d: check_settings failed\n",
				ovl->id);
		जाओ err2;
	पूर्ण

	dss_setup_fअगरos();

	op->enabling = false;
	dss_apply_ovl_enable(ovl, true);

	dss_ग_लिखो_regs();
	dss_set_go_bits();

	spin_unlock_irqrestore(&data_lock, flags);

	mutex_unlock(&apply_lock);

	वापस 0;
err2:
	op->enabling = false;
	spin_unlock_irqrestore(&data_lock, flags);
err1:
	mutex_unlock(&apply_lock);
	वापस r;
पूर्ण

अटल पूर्णांक dss_ovl_disable(काष्ठा omap_overlay *ovl)
अणु
	काष्ठा ovl_priv_data *op = get_ovl_priv(ovl);
	अचिन्हित दीर्घ flags;
	पूर्णांक r;

	mutex_lock(&apply_lock);

	अगर (!op->enabled) अणु
		r = 0;
		जाओ err;
	पूर्ण

	अगर (ovl->manager == शून्य || ovl->manager->output == शून्य) अणु
		r = -EINVAL;
		जाओ err;
	पूर्ण

	spin_lock_irqsave(&data_lock, flags);

	dss_apply_ovl_enable(ovl, false);
	dss_ग_लिखो_regs();
	dss_set_go_bits();

	spin_unlock_irqrestore(&data_lock, flags);

	mutex_unlock(&apply_lock);

	वापस 0;

err:
	mutex_unlock(&apply_lock);
	वापस r;
पूर्ण

अटल पूर्णांक dss_mgr_रेजिस्टर_frameकरोne_handler_compat(काष्ठा omap_overlay_manager *mgr,
		व्योम (*handler)(व्योम *), व्योम *data)
अणु
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);

	अगर (mp->frameकरोne_handler)
		वापस -EBUSY;

	mp->frameकरोne_handler = handler;
	mp->frameकरोne_handler_data = data;

	वापस 0;
पूर्ण

अटल व्योम dss_mgr_unरेजिस्टर_frameकरोne_handler_compat(काष्ठा omap_overlay_manager *mgr,
		व्योम (*handler)(व्योम *), व्योम *data)
अणु
	काष्ठा mgr_priv_data *mp = get_mgr_priv(mgr);

	WARN_ON(mp->frameकरोne_handler != handler ||
			mp->frameकरोne_handler_data != data);

	mp->frameकरोne_handler = शून्य;
	mp->frameकरोne_handler_data = शून्य;
पूर्ण

अटल स्थिर काष्ठा dss_mgr_ops apply_mgr_ops = अणु
	.connect = dss_mgr_connect_compat,
	.disconnect = dss_mgr_disconnect_compat,
	.start_update = dss_mgr_start_update_compat,
	.enable = dss_mgr_enable_compat,
	.disable = dss_mgr_disable_compat,
	.set_timings = dss_mgr_set_timings_compat,
	.set_lcd_config = dss_mgr_set_lcd_config_compat,
	.रेजिस्टर_frameकरोne_handler = dss_mgr_रेजिस्टर_frameकरोne_handler_compat,
	.unरेजिस्टर_frameकरोne_handler = dss_mgr_unरेजिस्टर_frameकरोne_handler_compat,
पूर्ण;

अटल पूर्णांक compat_refcnt;
अटल DEFINE_MUTEX(compat_init_lock);

पूर्णांक omapdss_compat_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev = dss_get_core_pdev();
	पूर्णांक i, r;

	mutex_lock(&compat_init_lock);

	अगर (compat_refcnt++ > 0)
		जाओ out;

	apply_init_priv();

	dss_init_overlay_managers_sysfs(pdev);
	dss_init_overlays(pdev);

	क्रम (i = 0; i < omap_dss_get_num_overlay_managers(); i++) अणु
		काष्ठा omap_overlay_manager *mgr;

		mgr = omap_dss_get_overlay_manager(i);

		mgr->set_output = &dss_mgr_set_output;
		mgr->unset_output = &dss_mgr_unset_output;
		mgr->apply = &omap_dss_mgr_apply;
		mgr->set_manager_info = &dss_mgr_set_info;
		mgr->get_manager_info = &dss_mgr_get_info;
		mgr->रुको_क्रम_go = &dss_mgr_रुको_क्रम_go;
		mgr->रुको_क्रम_vsync = &dss_mgr_रुको_क्रम_vsync;
		mgr->get_device = &dss_mgr_get_device;
	पूर्ण

	क्रम (i = 0; i < omap_dss_get_num_overlays(); i++) अणु
		काष्ठा omap_overlay *ovl = omap_dss_get_overlay(i);

		ovl->is_enabled = &dss_ovl_is_enabled;
		ovl->enable = &dss_ovl_enable;
		ovl->disable = &dss_ovl_disable;
		ovl->set_manager = &dss_ovl_set_manager;
		ovl->unset_manager = &dss_ovl_unset_manager;
		ovl->set_overlay_info = &dss_ovl_set_info;
		ovl->get_overlay_info = &dss_ovl_get_info;
		ovl->रुको_क्रम_go = &dss_mgr_रुको_क्रम_go_ovl;
		ovl->get_device = &dss_ovl_get_device;
	पूर्ण

	r = dss_install_mgr_ops(&apply_mgr_ops);
	अगर (r)
		जाओ err_mgr_ops;

	r = display_init_sysfs(pdev);
	अगर (r)
		जाओ err_disp_sysfs;

	dispc_runसमय_get();

	r = dss_dispc_initialize_irq();
	अगर (r)
		जाओ err_init_irq;

	dispc_runसमय_put();

out:
	mutex_unlock(&compat_init_lock);

	वापस 0;

err_init_irq:
	dispc_runसमय_put();
	display_uninit_sysfs(pdev);

err_disp_sysfs:
	dss_uninstall_mgr_ops();

err_mgr_ops:
	dss_uninit_overlay_managers_sysfs(pdev);
	dss_uninit_overlays(pdev);

	compat_refcnt--;

	mutex_unlock(&compat_init_lock);

	वापस r;
पूर्ण
EXPORT_SYMBOL(omapdss_compat_init);

व्योम omapdss_compat_uninit(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev = dss_get_core_pdev();

	mutex_lock(&compat_init_lock);

	अगर (--compat_refcnt > 0)
		जाओ out;

	dss_dispc_uninitialize_irq();

	display_uninit_sysfs(pdev);

	dss_uninstall_mgr_ops();

	dss_uninit_overlay_managers_sysfs(pdev);
	dss_uninit_overlays(pdev);
out:
	mutex_unlock(&compat_init_lock);
पूर्ण
EXPORT_SYMBOL(omapdss_compat_uninit);
