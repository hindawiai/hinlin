<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/drivers/video/omap2/dss/core.c
 *
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#घोषणा DSS_SUBSYS_NAME "CORE"

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/clk.h>
#समावेश <linux/err.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/पन.स>
#समावेश <linux/device.h>
#समावेश <linux/regulator/consumer.h>
#समावेश <linux/suspend.h>
#समावेश <linux/slab.h>

#समावेश <video/omapfb_dss.h>

#समावेश "dss.h"
#समावेश "dss_features.h"

अटल काष्ठा अणु
	काष्ठा platक्रमm_device *pdev;

	स्थिर अक्षर *शेष_display_name;
पूर्ण core;

अटल अक्षर *def_disp_name;
module_param_named(def_disp, def_disp_name, अक्षरp, 0);
MODULE_PARM_DESC(def_disp, "default display name");

स्थिर अक्षर *omapdss_get_शेष_display_name(व्योम)
अणु
	वापस core.शेष_display_name;
पूर्ण
EXPORT_SYMBOL(omapdss_get_शेष_display_name);

क्रमागत omapdss_version omapdss_get_version(व्योम)
अणु
	काष्ठा omap_dss_board_info *pdata = core.pdev->dev.platक्रमm_data;
	वापस pdata->version;
पूर्ण
EXPORT_SYMBOL(omapdss_get_version);

काष्ठा platक्रमm_device *dss_get_core_pdev(व्योम)
अणु
	वापस core.pdev;
पूर्ण

पूर्णांक dss_dsi_enable_pads(पूर्णांक dsi_id, अचिन्हित lane_mask)
अणु
	काष्ठा omap_dss_board_info *board_data = core.pdev->dev.platक्रमm_data;

	अगर (!board_data->dsi_enable_pads)
		वापस -ENOENT;

	वापस board_data->dsi_enable_pads(dsi_id, lane_mask);
पूर्ण

व्योम dss_dsi_disable_pads(पूर्णांक dsi_id, अचिन्हित lane_mask)
अणु
	काष्ठा omap_dss_board_info *board_data = core.pdev->dev.platक्रमm_data;

	अगर (!board_data->dsi_disable_pads)
		वापस;

	वापस board_data->dsi_disable_pads(dsi_id, lane_mask);
पूर्ण

पूर्णांक dss_set_min_bus_tput(काष्ठा device *dev, अचिन्हित दीर्घ tput)
अणु
	काष्ठा omap_dss_board_info *pdata = core.pdev->dev.platक्रमm_data;

	अगर (pdata->set_min_bus_tput)
		वापस pdata->set_min_bus_tput(dev, tput);
	अन्यथा
		वापस 0;
पूर्ण

#अगर defined(CONFIG_FB_OMAP2_DSS_DEBUGFS)
अटल पूर्णांक dss_show(काष्ठा seq_file *s, व्योम *unused)
अणु
	व्योम (*func)(काष्ठा seq_file *) = s->निजी;
	func(s);
	वापस 0;
पूर्ण

DEFINE_SHOW_ATTRIBUTE(dss);

अटल काष्ठा dentry *dss_debugfs_dir;

अटल व्योम dss_initialize_debugfs(व्योम)
अणु
	dss_debugfs_dir = debugfs_create_dir("omapdss", शून्य);

	debugfs_create_file("clk", S_IRUGO, dss_debugfs_dir,
			&dss_debug_dump_घड़ीs, &dss_fops);
पूर्ण

अटल व्योम dss_uninitialize_debugfs(व्योम)
अणु
	debugfs_हटाओ_recursive(dss_debugfs_dir);
पूर्ण

व्योम dss_debugfs_create_file(स्थिर अक्षर *name, व्योम (*ग_लिखो)(काष्ठा seq_file *))
अणु
	debugfs_create_file(name, S_IRUGO, dss_debugfs_dir, ग_लिखो, &dss_fops);
पूर्ण
#अन्यथा /* CONFIG_FB_OMAP2_DSS_DEBUGFS */
अटल अंतरभूत व्योम dss_initialize_debugfs(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम dss_uninitialize_debugfs(व्योम)
अणु
पूर्ण
व्योम dss_debugfs_create_file(स्थिर अक्षर *name, व्योम (*ग_लिखो)(काष्ठा seq_file *))
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_FB_OMAP2_DSS_DEBUGFS */

/* PLATFORM DEVICE */
अटल पूर्णांक omap_dss_pm_notअगर(काष्ठा notअगरier_block *b, अचिन्हित दीर्घ v, व्योम *d)
अणु
	DSSDBG("pm notif %lu\n", v);

	चयन (v) अणु
	हाल PM_SUSPEND_PREPARE:
	हाल PM_HIBERNATION_PREPARE:
	हाल PM_RESTORE_PREPARE:
		DSSDBG("suspending displays\n");
		वापस dss_suspend_all_devices();

	हाल PM_POST_SUSPEND:
	हाल PM_POST_HIBERNATION:
	हाल PM_POST_RESTORE:
		DSSDBG("resuming displays\n");
		वापस dss_resume_all_devices();

	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल काष्ठा notअगरier_block omap_dss_pm_notअगर_block = अणु
	.notअगरier_call = omap_dss_pm_notअगर,
पूर्ण;

अटल पूर्णांक __init omap_dss_probe(काष्ठा platक्रमm_device *pdev)
अणु
	core.pdev = pdev;

	dss_features_init(omapdss_get_version());

	dss_initialize_debugfs();

	अगर (def_disp_name)
		core.शेष_display_name = def_disp_name;

	रेजिस्टर_pm_notअगरier(&omap_dss_pm_notअगर_block);

	वापस 0;
पूर्ण

अटल पूर्णांक omap_dss_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	unरेजिस्टर_pm_notअगरier(&omap_dss_pm_notअगर_block);

	dss_uninitialize_debugfs();

	वापस 0;
पूर्ण

अटल व्योम omap_dss_shutकरोwn(काष्ठा platक्रमm_device *pdev)
अणु
	DSSDBG("shutdown\n");
	dss_disable_all_devices();
पूर्ण

अटल काष्ठा platक्रमm_driver omap_dss_driver = अणु
	.हटाओ         = omap_dss_हटाओ,
	.shutकरोwn	= omap_dss_shutकरोwn,
	.driver         = अणु
		.name   = "omapdss",
	पूर्ण,
पूर्ण;

/* INIT */
अटल पूर्णांक (*dss_output_drv_reg_funcs[])(व्योम) __initdata = अणु
	dss_init_platक्रमm_driver,
	dispc_init_platक्रमm_driver,
#अगर_घोषित CONFIG_FB_OMAP2_DSS_DSI
	dsi_init_platक्रमm_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_OMAP2_DSS_DPI
	dpi_init_platक्रमm_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_OMAP2_DSS_SDI
	sdi_init_platक्रमm_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_OMAP2_DSS_VENC
	venc_init_platक्रमm_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_OMAP4_DSS_HDMI
	hdmi4_init_platक्रमm_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_OMAP5_DSS_HDMI
	hdmi5_init_platक्रमm_driver,
#पूर्ण_अगर
पूर्ण;

अटल व्योम (*dss_output_drv_unreg_funcs[])(व्योम) = अणु
#अगर_घोषित CONFIG_FB_OMAP5_DSS_HDMI
	hdmi5_uninit_platक्रमm_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_OMAP4_DSS_HDMI
	hdmi4_uninit_platक्रमm_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_OMAP2_DSS_VENC
	venc_uninit_platक्रमm_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_OMAP2_DSS_SDI
	sdi_uninit_platक्रमm_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_OMAP2_DSS_DPI
	dpi_uninit_platक्रमm_driver,
#पूर्ण_अगर
#अगर_घोषित CONFIG_FB_OMAP2_DSS_DSI
	dsi_uninit_platक्रमm_driver,
#पूर्ण_अगर
	dispc_uninit_platक्रमm_driver,
	dss_uninit_platक्रमm_driver,
पूर्ण;

अटल पूर्णांक __init omap_dss_init(व्योम)
अणु
	पूर्णांक r;
	पूर्णांक i;

	r = platक्रमm_driver_probe(&omap_dss_driver, omap_dss_probe);
	अगर (r)
		वापस r;

	क्रम (i = 0; i < ARRAY_SIZE(dss_output_drv_reg_funcs); ++i) अणु
		r = dss_output_drv_reg_funcs[i]();
		अगर (r)
			जाओ err_reg;
	पूर्ण

	वापस 0;

err_reg:
	क्रम (i = ARRAY_SIZE(dss_output_drv_reg_funcs) - i;
			i < ARRAY_SIZE(dss_output_drv_reg_funcs);
			++i)
		dss_output_drv_unreg_funcs[i]();

	platक्रमm_driver_unरेजिस्टर(&omap_dss_driver);

	वापस r;
पूर्ण

अटल व्योम __निकास omap_dss_निकास(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(dss_output_drv_unreg_funcs); ++i)
		dss_output_drv_unreg_funcs[i]();

	platक्रमm_driver_unरेजिस्टर(&omap_dss_driver);
पूर्ण

module_init(omap_dss_init);
module_निकास(omap_dss_निकास);

MODULE_AUTHOR("Tomi Valkeinen <tomi.valkeinen@nokia.com>");
MODULE_DESCRIPTION("OMAP2/3 Display Subsystem");
MODULE_LICENSE("GPL v2");

