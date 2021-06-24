<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * linux/drivers/video/omap2/dss/dss.h
 *
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@nokia.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#अगर_अघोषित __OMAP2_DSS_H
#घोषणा __OMAP2_DSS_H

#समावेश <linux/पूर्णांकerrupt.h>

#अगर_घोषित pr_fmt
#अघोषित pr_fmt
#पूर्ण_अगर

#अगर_घोषित DSS_SUBSYS_NAME
#घोषणा pr_fmt(fmt) DSS_SUBSYS_NAME ": " fmt
#अन्यथा
#घोषणा pr_fmt(fmt) fmt
#पूर्ण_अगर

#घोषणा DSSDBG(क्रमmat, ...) \
	pr_debug(क्रमmat, ## __VA_ARGS__)

#अगर_घोषित DSS_SUBSYS_NAME
#घोषणा DSSERR(क्रमmat, ...) \
	prपूर्णांकk(KERN_ERR "omapdss " DSS_SUBSYS_NAME " error: " क्रमmat, \
	## __VA_ARGS__)
#अन्यथा
#घोषणा DSSERR(क्रमmat, ...) \
	prपूर्णांकk(KERN_ERR "omapdss error: " क्रमmat, ## __VA_ARGS__)
#पूर्ण_अगर

#अगर_घोषित DSS_SUBSYS_NAME
#घोषणा DSSINFO(क्रमmat, ...) \
	prपूर्णांकk(KERN_INFO "omapdss " DSS_SUBSYS_NAME ": " क्रमmat, \
	## __VA_ARGS__)
#अन्यथा
#घोषणा DSSINFO(क्रमmat, ...) \
	prपूर्णांकk(KERN_INFO "omapdss: " क्रमmat, ## __VA_ARGS__)
#पूर्ण_अगर

#अगर_घोषित DSS_SUBSYS_NAME
#घोषणा DSSWARN(क्रमmat, ...) \
	prपूर्णांकk(KERN_WARNING "omapdss " DSS_SUBSYS_NAME ": " क्रमmat, \
	## __VA_ARGS__)
#अन्यथा
#घोषणा DSSWARN(क्रमmat, ...) \
	prपूर्णांकk(KERN_WARNING "omapdss: " क्रमmat, ## __VA_ARGS__)
#पूर्ण_अगर

/* OMAP TRM gives bitfields as start:end, where start is the higher bit
   number. For example 7:0 */
#घोषणा FLD_MASK(start, end)	(((1 << ((start) - (end) + 1)) - 1) << (end))
#घोषणा FLD_VAL(val, start, end) (((val) << (end)) & FLD_MASK(start, end))
#घोषणा FLD_GET(val, start, end) (((val) & FLD_MASK(start, end)) >> (end))
#घोषणा FLD_MOD(orig, val, start, end) \
	(((orig) & ~FLD_MASK(start, end)) | FLD_VAL(val, start, end))

क्रमागत omap_dss_clk_source अणु
	OMAP_DSS_CLK_SRC_FCK = 0,		/* OMAP2/3: DSS1_ALWON_FCLK
						 * OMAP4: DSS_FCLK */
	OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DISPC,	/* OMAP3: DSI1_PLL_FCLK
						 * OMAP4: PLL1_CLK1 */
	OMAP_DSS_CLK_SRC_DSI_PLL_HSDIV_DSI,	/* OMAP3: DSI2_PLL_FCLK
						 * OMAP4: PLL1_CLK2 */
	OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DISPC,	/* OMAP4: PLL2_CLK1 */
	OMAP_DSS_CLK_SRC_DSI2_PLL_HSDIV_DSI,	/* OMAP4: PLL2_CLK2 */
पूर्ण;

क्रमागत dss_io_pad_mode अणु
	DSS_IO_PAD_MODE_RESET,
	DSS_IO_PAD_MODE_RFBI,
	DSS_IO_PAD_MODE_BYPASS,
पूर्ण;

क्रमागत dss_hdmi_venc_clk_source_select अणु
	DSS_VENC_TV_CLK = 0,
	DSS_HDMI_M_PCLK = 1,
पूर्ण;

क्रमागत dss_dsi_content_type अणु
	DSS_DSI_CONTENT_DCS,
	DSS_DSI_CONTENT_GENERIC,
पूर्ण;

क्रमागत dss_pll_id अणु
	DSS_PLL_DSI1,
	DSS_PLL_DSI2,
	DSS_PLL_HDMI,
	DSS_PLL_VIDEO1,
	DSS_PLL_VIDEO2,
पूर्ण;

काष्ठा dss_pll;

#घोषणा DSS_PLL_MAX_HSDIVS 4

/*
 * Type-A PLLs: clkout[]/mX[] refer to hsभाग outमाला_दो m4, m5, m6, m7.
 * Type-B PLLs: clkout[0] refers to m2.
 */
काष्ठा dss_pll_घड़ी_info अणु
	/* rates that we get with भागiders below */
	अचिन्हित दीर्घ fपूर्णांक;
	अचिन्हित दीर्घ clkdco;
	अचिन्हित दीर्घ clkout[DSS_PLL_MAX_HSDIVS];

	/* भागiders */
	u16 n;
	u16 m;
	u32 mf;
	u16 mX[DSS_PLL_MAX_HSDIVS];
	u16 sd;
पूर्ण;

काष्ठा dss_pll_ops अणु
	पूर्णांक (*enable)(काष्ठा dss_pll *pll);
	व्योम (*disable)(काष्ठा dss_pll *pll);
	पूर्णांक (*set_config)(काष्ठा dss_pll *pll,
		स्थिर काष्ठा dss_pll_घड़ी_info *cinfo);
पूर्ण;

काष्ठा dss_pll_hw अणु
	अचिन्हित n_max;
	अचिन्हित m_min;
	अचिन्हित m_max;
	अचिन्हित mX_max;

	अचिन्हित दीर्घ fपूर्णांक_min, fपूर्णांक_max;
	अचिन्हित दीर्घ clkdco_min, clkdco_low, clkdco_max;

	u8 n_msb, n_lsb;
	u8 m_msb, m_lsb;
	u8 mX_msb[DSS_PLL_MAX_HSDIVS], mX_lsb[DSS_PLL_MAX_HSDIVS];

	bool has_stopmode;
	bool has_freqsel;
	bool has_selfreqdco;
	bool has_refsel;
पूर्ण;

काष्ठा dss_pll अणु
	स्थिर अक्षर *name;
	क्रमागत dss_pll_id id;

	काष्ठा clk *clkin;
	काष्ठा regulator *regulator;

	व्योम __iomem *base;

	स्थिर काष्ठा dss_pll_hw *hw;

	स्थिर काष्ठा dss_pll_ops *ops;

	काष्ठा dss_pll_घड़ी_info cinfo;
पूर्ण;

काष्ठा dispc_घड़ी_info अणु
	/* rates that we get with भागiders below */
	अचिन्हित दीर्घ lck;
	अचिन्हित दीर्घ pck;

	/* भागiders */
	u16 lck_भाग;
	u16 pck_भाग;
पूर्ण;

काष्ठा dss_lcd_mgr_config अणु
	क्रमागत dss_io_pad_mode io_pad_mode;

	bool stallmode;
	bool fअगरohandcheck;

	काष्ठा dispc_घड़ी_info घड़ी_info;

	पूर्णांक video_port_width;

	पूर्णांक lcden_sig_polarity;
पूर्ण;

काष्ठा seq_file;
काष्ठा platक्रमm_device;

/* core */
काष्ठा platक्रमm_device *dss_get_core_pdev(व्योम);
पूर्णांक dss_dsi_enable_pads(पूर्णांक dsi_id, अचिन्हित lane_mask);
व्योम dss_dsi_disable_pads(पूर्णांक dsi_id, अचिन्हित lane_mask);
पूर्णांक dss_set_min_bus_tput(काष्ठा device *dev, अचिन्हित दीर्घ tput);
व्योम dss_debugfs_create_file(स्थिर अक्षर *name, व्योम (*ग_लिखो)(काष्ठा seq_file *));

/* display */
पूर्णांक dss_suspend_all_devices(व्योम);
पूर्णांक dss_resume_all_devices(व्योम);
व्योम dss_disable_all_devices(व्योम);

पूर्णांक display_init_sysfs(काष्ठा platक्रमm_device *pdev);
व्योम display_uninit_sysfs(काष्ठा platक्रमm_device *pdev);

/* manager */
पूर्णांक dss_init_overlay_managers(व्योम);
व्योम dss_uninit_overlay_managers(व्योम);
पूर्णांक dss_init_overlay_managers_sysfs(काष्ठा platक्रमm_device *pdev);
व्योम dss_uninit_overlay_managers_sysfs(काष्ठा platक्रमm_device *pdev);
पूर्णांक dss_mgr_simple_check(काष्ठा omap_overlay_manager *mgr,
		स्थिर काष्ठा omap_overlay_manager_info *info);
पूर्णांक dss_mgr_check_timings(काष्ठा omap_overlay_manager *mgr,
		स्थिर काष्ठा omap_video_timings *timings);
पूर्णांक dss_mgr_check(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omap_overlay_manager_info *info,
		स्थिर काष्ठा omap_video_timings *mgr_timings,
		स्थिर काष्ठा dss_lcd_mgr_config *config,
		काष्ठा omap_overlay_info **overlay_infos);

अटल अंतरभूत bool dss_mgr_is_lcd(क्रमागत omap_channel id)
अणु
	अगर (id == OMAP_DSS_CHANNEL_LCD || id == OMAP_DSS_CHANNEL_LCD2 ||
			id == OMAP_DSS_CHANNEL_LCD3)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

पूर्णांक dss_manager_kobj_init(काष्ठा omap_overlay_manager *mgr,
		काष्ठा platक्रमm_device *pdev);
व्योम dss_manager_kobj_uninit(काष्ठा omap_overlay_manager *mgr);

/* overlay */
व्योम dss_init_overlays(काष्ठा platक्रमm_device *pdev);
व्योम dss_uninit_overlays(काष्ठा platक्रमm_device *pdev);
व्योम dss_overlay_setup_dispc_manager(काष्ठा omap_overlay_manager *mgr);
पूर्णांक dss_ovl_simple_check(काष्ठा omap_overlay *ovl,
		स्थिर काष्ठा omap_overlay_info *info);
पूर्णांक dss_ovl_check(काष्ठा omap_overlay *ovl, काष्ठा omap_overlay_info *info,
		स्थिर काष्ठा omap_video_timings *mgr_timings);
bool dss_ovl_use_replication(काष्ठा dss_lcd_mgr_config config,
		क्रमागत omap_color_mode mode);
पूर्णांक dss_overlay_kobj_init(काष्ठा omap_overlay *ovl,
		काष्ठा platक्रमm_device *pdev);
व्योम dss_overlay_kobj_uninit(काष्ठा omap_overlay *ovl);

/* DSS */
पूर्णांक dss_init_platक्रमm_driver(व्योम) __init;
व्योम dss_uninit_platक्रमm_driver(व्योम);

पूर्णांक dss_runसमय_get(व्योम);
व्योम dss_runसमय_put(व्योम);

अचिन्हित दीर्घ dss_get_dispc_clk_rate(व्योम);
पूर्णांक dss_dpi_select_source(पूर्णांक port, क्रमागत omap_channel channel);
व्योम dss_select_hdmi_venc_clk_source(क्रमागत dss_hdmi_venc_clk_source_select);
क्रमागत dss_hdmi_venc_clk_source_select dss_get_hdmi_venc_clk_source(व्योम);
स्थिर अक्षर *dss_get_generic_clk_source_name(क्रमागत omap_dss_clk_source clk_src);
व्योम dss_dump_घड़ीs(काष्ठा seq_file *s);

/* DSS VIDEO PLL */
काष्ठा dss_pll *dss_video_pll_init(काष्ठा platक्रमm_device *pdev, पूर्णांक id,
	काष्ठा regulator *regulator);
व्योम dss_video_pll_uninit(काष्ठा dss_pll *pll);

/* dss-of */
काष्ठा device_node *dss_of_port_get_parent_device(काष्ठा device_node *port);
u32 dss_of_port_get_port_number(काष्ठा device_node *port);

#अगर defined(CONFIG_FB_OMAP2_DSS_DEBUGFS)
व्योम dss_debug_dump_घड़ीs(काष्ठा seq_file *s);
#पूर्ण_अगर

व्योम dss_ctrl_pll_enable(क्रमागत dss_pll_id pll_id, bool enable);
व्योम dss_ctrl_pll_set_control_mux(क्रमागत dss_pll_id pll_id,
	क्रमागत omap_channel channel);

व्योम dss_sdi_init(पूर्णांक datapairs);
पूर्णांक dss_sdi_enable(व्योम);
व्योम dss_sdi_disable(व्योम);

व्योम dss_select_dsi_clk_source(पूर्णांक dsi_module,
		क्रमागत omap_dss_clk_source clk_src);
व्योम dss_select_lcd_clk_source(क्रमागत omap_channel channel,
		क्रमागत omap_dss_clk_source clk_src);
क्रमागत omap_dss_clk_source dss_get_dispc_clk_source(व्योम);
क्रमागत omap_dss_clk_source dss_get_dsi_clk_source(पूर्णांक dsi_module);
क्रमागत omap_dss_clk_source dss_get_lcd_clk_source(क्रमागत omap_channel channel);

व्योम dss_set_venc_output(क्रमागत omap_dss_venc_type type);
व्योम dss_set_dac_pwrdn_bgz(bool enable);

पूर्णांक dss_set_fck_rate(अचिन्हित दीर्घ rate);

प्रकार bool (*dss_भाग_calc_func)(अचिन्हित दीर्घ fck, व्योम *data);
bool dss_भाग_calc(अचिन्हित दीर्घ pck, अचिन्हित दीर्घ fck_min,
		dss_भाग_calc_func func, व्योम *data);

/* SDI */
पूर्णांक sdi_init_platक्रमm_driver(व्योम) __init;
व्योम sdi_uninit_platक्रमm_driver(व्योम);

#अगर_घोषित CONFIG_FB_OMAP2_DSS_SDI
पूर्णांक sdi_init_port(काष्ठा platक्रमm_device *pdev, काष्ठा device_node *port);
व्योम sdi_uninit_port(काष्ठा device_node *port);
#अन्यथा
अटल अंतरभूत पूर्णांक sdi_init_port(काष्ठा platक्रमm_device *pdev,
		काष्ठा device_node *port)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम sdi_uninit_port(काष्ठा device_node *port)
अणु
पूर्ण
#पूर्ण_अगर

/* DSI */

#अगर_घोषित CONFIG_FB_OMAP2_DSS_DSI

काष्ठा dentry;
काष्ठा file_operations;

पूर्णांक dsi_init_platक्रमm_driver(व्योम) __init;
व्योम dsi_uninit_platक्रमm_driver(व्योम);

व्योम dsi_dump_घड़ीs(काष्ठा seq_file *s);

व्योम dsi_irq_handler(व्योम);
u8 dsi_get_pixel_size(क्रमागत omap_dss_dsi_pixel_क्रमmat fmt);

#अन्यथा
अटल अंतरभूत u8 dsi_get_pixel_size(क्रमागत omap_dss_dsi_pixel_क्रमmat fmt)
अणु
	WARN(1, "%s: DSI not compiled in, returning pixel_size as 0\n",
	     __func__);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/* DPI */
पूर्णांक dpi_init_platक्रमm_driver(व्योम) __init;
व्योम dpi_uninit_platक्रमm_driver(व्योम);

#अगर_घोषित CONFIG_FB_OMAP2_DSS_DPI
पूर्णांक dpi_init_port(काष्ठा platक्रमm_device *pdev, काष्ठा device_node *port);
व्योम dpi_uninit_port(काष्ठा device_node *port);
#अन्यथा
अटल अंतरभूत पूर्णांक dpi_init_port(काष्ठा platक्रमm_device *pdev,
		काष्ठा device_node *port)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम dpi_uninit_port(काष्ठा device_node *port)
अणु
पूर्ण
#पूर्ण_अगर

/* DISPC */
पूर्णांक dispc_init_platक्रमm_driver(व्योम) __init;
व्योम dispc_uninit_platक्रमm_driver(व्योम);
व्योम dispc_dump_घड़ीs(काष्ठा seq_file *s);

व्योम dispc_enable_sidle(व्योम);
व्योम dispc_disable_sidle(व्योम);

व्योम dispc_lcd_enable_संकेत(bool enable);
व्योम dispc_pck_मुक्त_enable(bool enable);
व्योम dispc_enable_fअगरomerge(bool enable);
व्योम dispc_enable_gamma_table(bool enable);

प्रकार bool (*dispc_भाग_calc_func)(पूर्णांक lckd, पूर्णांक pckd, अचिन्हित दीर्घ lck,
		अचिन्हित दीर्घ pck, व्योम *data);
bool dispc_भाग_calc(अचिन्हित दीर्घ dispc,
		अचिन्हित दीर्घ pck_min, अचिन्हित दीर्घ pck_max,
		dispc_भाग_calc_func func, व्योम *data);

bool dispc_mgr_timings_ok(क्रमागत omap_channel channel,
		स्थिर काष्ठा omap_video_timings *timings);
पूर्णांक dispc_calc_घड़ी_rates(अचिन्हित दीर्घ dispc_fclk_rate,
		काष्ठा dispc_घड़ी_info *cinfo);


व्योम dispc_ovl_set_fअगरo_threshold(क्रमागत omap_plane plane, u32 low, u32 high);
व्योम dispc_ovl_compute_fअगरo_thresholds(क्रमागत omap_plane plane,
		u32 *fअगरo_low, u32 *fअगरo_high, bool use_fअगरomerge,
		bool manual_update);

व्योम dispc_mgr_set_घड़ी_भाग(क्रमागत omap_channel channel,
		स्थिर काष्ठा dispc_घड़ी_info *cinfo);
पूर्णांक dispc_mgr_get_घड़ी_भाग(क्रमागत omap_channel channel,
		काष्ठा dispc_घड़ी_info *cinfo);
व्योम dispc_set_tv_pclk(अचिन्हित दीर्घ pclk);

u32 dispc_पढ़ो_irqstatus(व्योम);
व्योम dispc_clear_irqstatus(u32 mask);
u32 dispc_पढ़ो_irqenable(व्योम);
व्योम dispc_ग_लिखो_irqenable(u32 mask);

पूर्णांक dispc_request_irq(irq_handler_t handler, व्योम *dev_id);
व्योम dispc_मुक्त_irq(व्योम *dev_id);

पूर्णांक dispc_runसमय_get(व्योम);
व्योम dispc_runसमय_put(व्योम);

व्योम dispc_mgr_enable(क्रमागत omap_channel channel, bool enable);
bool dispc_mgr_is_enabled(क्रमागत omap_channel channel);
u32 dispc_mgr_get_vsync_irq(क्रमागत omap_channel channel);
u32 dispc_mgr_get_frameकरोne_irq(क्रमागत omap_channel channel);
u32 dispc_mgr_get_sync_lost_irq(क्रमागत omap_channel channel);
bool dispc_mgr_go_busy(क्रमागत omap_channel channel);
व्योम dispc_mgr_go(क्रमागत omap_channel channel);
व्योम dispc_mgr_set_lcd_config(क्रमागत omap_channel channel,
		स्थिर काष्ठा dss_lcd_mgr_config *config);
व्योम dispc_mgr_set_timings(क्रमागत omap_channel channel,
		स्थिर काष्ठा omap_video_timings *timings);
व्योम dispc_mgr_setup(क्रमागत omap_channel channel,
		स्थिर काष्ठा omap_overlay_manager_info *info);

पूर्णांक dispc_ovl_check(क्रमागत omap_plane plane, क्रमागत omap_channel channel,
		स्थिर काष्ठा omap_overlay_info *oi,
		स्थिर काष्ठा omap_video_timings *timings,
		पूर्णांक *x_predecim, पूर्णांक *y_predecim);

पूर्णांक dispc_ovl_enable(क्रमागत omap_plane plane, bool enable);
bool dispc_ovl_enabled(क्रमागत omap_plane plane);
व्योम dispc_ovl_set_channel_out(क्रमागत omap_plane plane,
		क्रमागत omap_channel channel);
पूर्णांक dispc_ovl_setup(क्रमागत omap_plane plane, स्थिर काष्ठा omap_overlay_info *oi,
		bool replication, स्थिर काष्ठा omap_video_timings *mgr_timings,
		bool mem_to_mem);

/* VENC */
पूर्णांक venc_init_platक्रमm_driver(व्योम) __init;
व्योम venc_uninit_platक्रमm_driver(व्योम);

/* HDMI */
पूर्णांक hdmi4_init_platक्रमm_driver(व्योम) __init;
व्योम hdmi4_uninit_platक्रमm_driver(व्योम);

पूर्णांक hdmi5_init_platक्रमm_driver(व्योम) __init;
व्योम hdmi5_uninit_platक्रमm_driver(व्योम);


#अगर_घोषित CONFIG_FB_OMAP2_DSS_COLLECT_IRQ_STATS
अटल अंतरभूत व्योम dss_collect_irq_stats(u32 irqstatus, अचिन्हित *irq_arr)
अणु
	पूर्णांक b;
	क्रम (b = 0; b < 32; ++b) अणु
		अगर (irqstatus & (1 << b))
			irq_arr[b]++;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/* PLL */
प्रकार bool (*dss_pll_calc_func)(पूर्णांक n, पूर्णांक m, अचिन्हित दीर्घ fपूर्णांक,
		अचिन्हित दीर्घ clkdco, व्योम *data);
प्रकार bool (*dss_hsभाग_calc_func)(पूर्णांक m_dispc, अचिन्हित दीर्घ dispc,
		व्योम *data);

पूर्णांक dss_pll_रेजिस्टर(काष्ठा dss_pll *pll);
व्योम dss_pll_unरेजिस्टर(काष्ठा dss_pll *pll);
काष्ठा dss_pll *dss_pll_find(स्थिर अक्षर *name);
पूर्णांक dss_pll_enable(काष्ठा dss_pll *pll);
व्योम dss_pll_disable(काष्ठा dss_pll *pll);
पूर्णांक dss_pll_set_config(काष्ठा dss_pll *pll,
		स्थिर काष्ठा dss_pll_घड़ी_info *cinfo);

bool dss_pll_hsभाग_calc(स्थिर काष्ठा dss_pll *pll, अचिन्हित दीर्घ clkdco,
		अचिन्हित दीर्घ out_min, अचिन्हित दीर्घ out_max,
		dss_hsभाग_calc_func func, व्योम *data);
bool dss_pll_calc(स्थिर काष्ठा dss_pll *pll, अचिन्हित दीर्घ clkin,
		अचिन्हित दीर्घ pll_min, अचिन्हित दीर्घ pll_max,
		dss_pll_calc_func func, व्योम *data);
पूर्णांक dss_pll_ग_लिखो_config_type_a(काष्ठा dss_pll *pll,
		स्थिर काष्ठा dss_pll_घड़ी_info *cinfo);
पूर्णांक dss_pll_ग_लिखो_config_type_b(काष्ठा dss_pll *pll,
		स्थिर काष्ठा dss_pll_घड़ी_info *cinfo);
पूर्णांक dss_pll_रुको_reset_करोne(काष्ठा dss_pll *pll);

/* compat */

काष्ठा dss_mgr_ops अणु
	पूर्णांक (*connect)(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omap_dss_device *dst);
	व्योम (*disconnect)(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omap_dss_device *dst);

	व्योम (*start_update)(काष्ठा omap_overlay_manager *mgr);
	पूर्णांक (*enable)(काष्ठा omap_overlay_manager *mgr);
	व्योम (*disable)(काष्ठा omap_overlay_manager *mgr);
	व्योम (*set_timings)(काष्ठा omap_overlay_manager *mgr,
			स्थिर काष्ठा omap_video_timings *timings);
	व्योम (*set_lcd_config)(काष्ठा omap_overlay_manager *mgr,
			स्थिर काष्ठा dss_lcd_mgr_config *config);
	पूर्णांक (*रेजिस्टर_frameकरोne_handler)(काष्ठा omap_overlay_manager *mgr,
			व्योम (*handler)(व्योम *), व्योम *data);
	व्योम (*unरेजिस्टर_frameकरोne_handler)(काष्ठा omap_overlay_manager *mgr,
			व्योम (*handler)(व्योम *), व्योम *data);
पूर्ण;

पूर्णांक dss_install_mgr_ops(स्थिर काष्ठा dss_mgr_ops *mgr_ops);
व्योम dss_uninstall_mgr_ops(व्योम);

पूर्णांक dss_mgr_connect(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omap_dss_device *dst);
व्योम dss_mgr_disconnect(काष्ठा omap_overlay_manager *mgr,
		काष्ठा omap_dss_device *dst);
व्योम dss_mgr_set_timings(काष्ठा omap_overlay_manager *mgr,
		स्थिर काष्ठा omap_video_timings *timings);
व्योम dss_mgr_set_lcd_config(काष्ठा omap_overlay_manager *mgr,
		स्थिर काष्ठा dss_lcd_mgr_config *config);
पूर्णांक dss_mgr_enable(काष्ठा omap_overlay_manager *mgr);
व्योम dss_mgr_disable(काष्ठा omap_overlay_manager *mgr);
व्योम dss_mgr_start_update(काष्ठा omap_overlay_manager *mgr);
पूर्णांक dss_mgr_रेजिस्टर_frameकरोne_handler(काष्ठा omap_overlay_manager *mgr,
		व्योम (*handler)(व्योम *), व्योम *data);
व्योम dss_mgr_unरेजिस्टर_frameकरोne_handler(काष्ठा omap_overlay_manager *mgr,
		व्योम (*handler)(व्योम *), व्योम *data);

#पूर्ण_अगर
