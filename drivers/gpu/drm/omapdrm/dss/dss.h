<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2009 Nokia Corporation
 * Author: Tomi Valkeinen <tomi.valkeinen@ti.com>
 *
 * Some code and ideas taken from drivers/video/omap/ driver
 * by Imre Deak.
 */

#अगर_अघोषित __OMAP2_DSS_H
#घोषणा __OMAP2_DSS_H

#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "omapdss.h"

काष्ठा dispc_device;
काष्ठा dss_debugfs_entry;
काष्ठा platक्रमm_device;
काष्ठा seq_file;

#घोषणा MAX_DSS_LCD_MANAGERS	3
#घोषणा MAX_NUM_DSI		2

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
	pr_err("omapdss " DSS_SUBSYS_NAME " error: " क्रमmat, ##__VA_ARGS__)
#अन्यथा
#घोषणा DSSERR(क्रमmat, ...) \
	pr_err("omapdss error: " क्रमmat, ##__VA_ARGS__)
#पूर्ण_अगर

#अगर_घोषित DSS_SUBSYS_NAME
#घोषणा DSSINFO(क्रमmat, ...) \
	pr_info("omapdss " DSS_SUBSYS_NAME ": " क्रमmat, ##__VA_ARGS__)
#अन्यथा
#घोषणा DSSINFO(क्रमmat, ...) \
	pr_info("omapdss: " क्रमmat, ## __VA_ARGS__)
#पूर्ण_अगर

#अगर_घोषित DSS_SUBSYS_NAME
#घोषणा DSSWARN(क्रमmat, ...) \
	pr_warn("omapdss " DSS_SUBSYS_NAME ": " क्रमmat, ##__VA_ARGS__)
#अन्यथा
#घोषणा DSSWARN(क्रमmat, ...) \
	pr_warn("omapdss: " क्रमmat, ##__VA_ARGS__)
#पूर्ण_अगर

/* OMAP TRM gives bitfields as start:end, where start is the higher bit
   number. For example 7:0 */
#घोषणा FLD_MASK(start, end)	(((1 << ((start) - (end) + 1)) - 1) << (end))
#घोषणा FLD_VAL(val, start, end) (((val) << (end)) & FLD_MASK(start, end))
#घोषणा FLD_GET(val, start, end) (((val) & FLD_MASK(start, end)) >> (end))
#घोषणा FLD_MOD(orig, val, start, end) \
	(((orig) & ~FLD_MASK(start, end)) | FLD_VAL(val, start, end))

क्रमागत dss_model अणु
	DSS_MODEL_OMAP2,
	DSS_MODEL_OMAP3,
	DSS_MODEL_OMAP4,
	DSS_MODEL_OMAP5,
	DSS_MODEL_DRA7,
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

क्रमागत dss_clk_source अणु
	DSS_CLK_SRC_FCK = 0,

	DSS_CLK_SRC_PLL1_1,
	DSS_CLK_SRC_PLL1_2,
	DSS_CLK_SRC_PLL1_3,

	DSS_CLK_SRC_PLL2_1,
	DSS_CLK_SRC_PLL2_2,
	DSS_CLK_SRC_PLL2_3,

	DSS_CLK_SRC_HDMI_PLL,
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

क्रमागत dss_pll_type अणु
	DSS_PLL_TYPE_A,
	DSS_PLL_TYPE_B,
पूर्ण;

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
	क्रमागत dss_pll_type type;

	अचिन्हित पूर्णांक n_max;
	अचिन्हित पूर्णांक m_min;
	अचिन्हित पूर्णांक m_max;
	अचिन्हित पूर्णांक mX_max;

	अचिन्हित दीर्घ fपूर्णांक_min, fपूर्णांक_max;
	अचिन्हित दीर्घ clkdco_min, clkdco_low, clkdco_max;

	u8 n_msb, n_lsb;
	u8 m_msb, m_lsb;
	u8 mX_msb[DSS_PLL_MAX_HSDIVS], mX_lsb[DSS_PLL_MAX_HSDIVS];

	bool has_stopmode;
	bool has_freqsel;
	bool has_selfreqdco;
	bool has_refsel;

	/* DRA7 errata i886: use high N & M to aव्योम jitter */
	bool errata_i886;

	/* DRA7 errata i932: retry pll lock on failure */
	bool errata_i932;
पूर्ण;

काष्ठा dss_pll अणु
	स्थिर अक्षर *name;
	क्रमागत dss_pll_id id;
	काष्ठा dss_device *dss;

	काष्ठा clk *clkin;
	काष्ठा regulator *regulator;

	व्योम __iomem *base;

	स्थिर काष्ठा dss_pll_hw *hw;

	स्थिर काष्ठा dss_pll_ops *ops;

	काष्ठा dss_pll_घड़ी_info cinfo;
पूर्ण;

/* Defines a generic omap रेजिस्टर field */
काष्ठा dss_reg_field अणु
	u8 start, end;
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

#घोषणा DSS_SZ_REGS			SZ_512

काष्ठा dss_device अणु
	काष्ठा platक्रमm_device *pdev;
	व्योम __iomem    *base;
	काष्ठा regmap	*syscon_pll_ctrl;
	u32		syscon_pll_ctrl_offset;

	काष्ठा platक्रमm_device *drm_pdev;

	काष्ठा clk	*parent_clk;
	काष्ठा clk	*dss_clk;
	अचिन्हित दीर्घ	dss_clk_rate;

	अचिन्हित दीर्घ	cache_req_pck;
	अचिन्हित दीर्घ	cache_prate;
	काष्ठा dispc_घड़ी_info cache_dispc_cinfo;

	क्रमागत dss_clk_source dsi_clk_source[MAX_NUM_DSI];
	क्रमागत dss_clk_source dispc_clk_source;
	क्रमागत dss_clk_source lcd_clk_source[MAX_DSS_LCD_MANAGERS];

	bool		ctx_valid;
	u32		ctx[DSS_SZ_REGS / माप(u32)];

	स्थिर काष्ठा dss_features *feat;

	काष्ठा अणु
		काष्ठा dentry *root;
		काष्ठा dss_debugfs_entry *clk;
		काष्ठा dss_debugfs_entry *dss;
	पूर्ण debugfs;

	काष्ठा dss_pll *plls[4];
	काष्ठा dss_pll	*video1_pll;
	काष्ठा dss_pll	*video2_pll;

	काष्ठा dispc_device *dispc;
	काष्ठा omap_drm_निजी *mgr_ops_priv;
पूर्ण;

/* core */
अटल अंतरभूत पूर्णांक dss_set_min_bus_tput(काष्ठा device *dev, अचिन्हित दीर्घ tput)
अणु
	/* To be implemented when the OMAP platक्रमm will provide this feature */
	वापस 0;
पूर्ण

अटल अंतरभूत bool dss_mgr_is_lcd(क्रमागत omap_channel id)
अणु
	अगर (id == OMAP_DSS_CHANNEL_LCD || id == OMAP_DSS_CHANNEL_LCD2 ||
			id == OMAP_DSS_CHANNEL_LCD3)
		वापस true;
	अन्यथा
		वापस false;
पूर्ण

/* DSS */
#अगर defined(CONFIG_OMAP2_DSS_DEBUGFS)
काष्ठा dss_debugfs_entry *
dss_debugfs_create_file(काष्ठा dss_device *dss, स्थिर अक्षर *name,
			पूर्णांक (*show_fn)(काष्ठा seq_file *s, व्योम *data),
			व्योम *data);
व्योम dss_debugfs_हटाओ_file(काष्ठा dss_debugfs_entry *entry);
#अन्यथा
अटल अंतरभूत काष्ठा dss_debugfs_entry *
dss_debugfs_create_file(काष्ठा dss_device *dss, स्थिर अक्षर *name,
			पूर्णांक (*show_fn)(काष्ठा seq_file *s, व्योम *data),
			व्योम *data)
अणु
	वापस शून्य;
पूर्ण

अटल अंतरभूत व्योम dss_debugfs_हटाओ_file(काष्ठा dss_debugfs_entry *entry)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_OMAP2_DSS_DEBUGFS */

काष्ठा dss_device *dss_get_device(काष्ठा device *dev);

पूर्णांक dss_runसमय_get(काष्ठा dss_device *dss);
व्योम dss_runसमय_put(काष्ठा dss_device *dss);

अचिन्हित दीर्घ dss_get_dispc_clk_rate(काष्ठा dss_device *dss);
अचिन्हित दीर्घ dss_get_max_fck_rate(काष्ठा dss_device *dss);
पूर्णांक dss_dpi_select_source(काष्ठा dss_device *dss, पूर्णांक port,
			  क्रमागत omap_channel channel);
व्योम dss_select_hdmi_venc_clk_source(काष्ठा dss_device *dss,
				     क्रमागत dss_hdmi_venc_clk_source_select src);
स्थिर अक्षर *dss_get_clk_source_name(क्रमागत dss_clk_source clk_src);

/* DSS VIDEO PLL */
काष्ठा dss_pll *dss_video_pll_init(काष्ठा dss_device *dss,
				   काष्ठा platक्रमm_device *pdev, पूर्णांक id,
				   काष्ठा regulator *regulator);
व्योम dss_video_pll_uninit(काष्ठा dss_pll *pll);

व्योम dss_ctrl_pll_enable(काष्ठा dss_pll *pll, bool enable);

व्योम dss_sdi_init(काष्ठा dss_device *dss, पूर्णांक datapairs);
पूर्णांक dss_sdi_enable(काष्ठा dss_device *dss);
व्योम dss_sdi_disable(काष्ठा dss_device *dss);

व्योम dss_select_dsi_clk_source(काष्ठा dss_device *dss, पूर्णांक dsi_module,
			       क्रमागत dss_clk_source clk_src);
व्योम dss_select_lcd_clk_source(काष्ठा dss_device *dss,
			       क्रमागत omap_channel channel,
			       क्रमागत dss_clk_source clk_src);
क्रमागत dss_clk_source dss_get_dispc_clk_source(काष्ठा dss_device *dss);
क्रमागत dss_clk_source dss_get_dsi_clk_source(काष्ठा dss_device *dss,
					   पूर्णांक dsi_module);
क्रमागत dss_clk_source dss_get_lcd_clk_source(काष्ठा dss_device *dss,
					   क्रमागत omap_channel channel);

व्योम dss_set_venc_output(काष्ठा dss_device *dss, क्रमागत omap_dss_venc_type type);
व्योम dss_set_dac_pwrdn_bgz(काष्ठा dss_device *dss, bool enable);

पूर्णांक dss_set_fck_rate(काष्ठा dss_device *dss, अचिन्हित दीर्घ rate);

प्रकार bool (*dss_भाग_calc_func)(अचिन्हित दीर्घ fck, व्योम *data);
bool dss_भाग_calc(काष्ठा dss_device *dss, अचिन्हित दीर्घ pck,
		  अचिन्हित दीर्घ fck_min, dss_भाग_calc_func func, व्योम *data);

/* SDI */
#अगर_घोषित CONFIG_OMAP2_DSS_SDI
पूर्णांक sdi_init_port(काष्ठा dss_device *dss, काष्ठा platक्रमm_device *pdev,
		  काष्ठा device_node *port);
व्योम sdi_uninit_port(काष्ठा device_node *port);
#अन्यथा
अटल अंतरभूत पूर्णांक sdi_init_port(काष्ठा dss_device *dss,
				काष्ठा platक्रमm_device *pdev,
				काष्ठा device_node *port)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम sdi_uninit_port(काष्ठा device_node *port)
अणु
पूर्ण
#पूर्ण_अगर

/* DSI */

#अगर_घोषित CONFIG_OMAP2_DSS_DSI

व्योम dsi_irq_handler(व्योम);

#पूर्ण_अगर

/* DPI */
#अगर_घोषित CONFIG_OMAP2_DSS_DPI
पूर्णांक dpi_init_port(काष्ठा dss_device *dss, काष्ठा platक्रमm_device *pdev,
		  काष्ठा device_node *port, क्रमागत dss_model dss_model);
व्योम dpi_uninit_port(काष्ठा device_node *port);
#अन्यथा
अटल अंतरभूत पूर्णांक dpi_init_port(काष्ठा dss_device *dss,
				काष्ठा platक्रमm_device *pdev,
				काष्ठा device_node *port,
				क्रमागत dss_model dss_model)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम dpi_uninit_port(काष्ठा device_node *port)
अणु
पूर्ण
#पूर्ण_अगर

/* DISPC */
व्योम dispc_dump_घड़ीs(काष्ठा dispc_device *dispc, काष्ठा seq_file *s);

पूर्णांक dispc_runसमय_get(काष्ठा dispc_device *dispc);
व्योम dispc_runसमय_put(काष्ठा dispc_device *dispc);

पूर्णांक dispc_get_num_ovls(काष्ठा dispc_device *dispc);
पूर्णांक dispc_get_num_mgrs(काष्ठा dispc_device *dispc);

स्थिर u32 *dispc_ovl_get_color_modes(काष्ठा dispc_device *dispc,
					    क्रमागत omap_plane_id plane);

u32 dispc_पढ़ो_irqstatus(काष्ठा dispc_device *dispc);
व्योम dispc_clear_irqstatus(काष्ठा dispc_device *dispc, u32 mask);
व्योम dispc_ग_लिखो_irqenable(काष्ठा dispc_device *dispc, u32 mask);

पूर्णांक dispc_request_irq(काष्ठा dispc_device *dispc, irq_handler_t handler,
			     व्योम *dev_id);
व्योम dispc_मुक्त_irq(काष्ठा dispc_device *dispc, व्योम *dev_id);

u32 dispc_mgr_get_vsync_irq(काष्ठा dispc_device *dispc,
				   क्रमागत omap_channel channel);
u32 dispc_mgr_get_frameकरोne_irq(काष्ठा dispc_device *dispc,
				       क्रमागत omap_channel channel);
u32 dispc_mgr_get_sync_lost_irq(काष्ठा dispc_device *dispc,
				       क्रमागत omap_channel channel);
u32 dispc_wb_get_frameकरोne_irq(काष्ठा dispc_device *dispc);

u32 dispc_get_memory_bandwidth_limit(काष्ठा dispc_device *dispc);

व्योम dispc_mgr_enable(काष्ठा dispc_device *dispc,
			     क्रमागत omap_channel channel, bool enable);

bool dispc_mgr_go_busy(काष्ठा dispc_device *dispc,
			      क्रमागत omap_channel channel);

व्योम dispc_mgr_go(काष्ठा dispc_device *dispc, क्रमागत omap_channel channel);

व्योम dispc_mgr_set_lcd_config(काष्ठा dispc_device *dispc,
				     क्रमागत omap_channel channel,
				     स्थिर काष्ठा dss_lcd_mgr_config *config);
व्योम dispc_mgr_set_timings(काष्ठा dispc_device *dispc,
				  क्रमागत omap_channel channel,
				  स्थिर काष्ठा videomode *vm);
व्योम dispc_mgr_setup(काष्ठा dispc_device *dispc,
			    क्रमागत omap_channel channel,
			    स्थिर काष्ठा omap_overlay_manager_info *info);

पूर्णांक dispc_mgr_check_timings(काष्ठा dispc_device *dispc,
				   क्रमागत omap_channel channel,
				   स्थिर काष्ठा videomode *vm);

u32 dispc_mgr_gamma_size(काष्ठा dispc_device *dispc,
				क्रमागत omap_channel channel);
व्योम dispc_mgr_set_gamma(काष्ठा dispc_device *dispc,
				क्रमागत omap_channel channel,
				स्थिर काष्ठा drm_color_lut *lut,
				अचिन्हित पूर्णांक length);

पूर्णांक dispc_ovl_setup(काष्ठा dispc_device *dispc,
			   क्रमागत omap_plane_id plane,
			   स्थिर काष्ठा omap_overlay_info *oi,
			   स्थिर काष्ठा videomode *vm, bool mem_to_mem,
			   क्रमागत omap_channel channel);

पूर्णांक dispc_ovl_enable(काष्ठा dispc_device *dispc,
			    क्रमागत omap_plane_id plane, bool enable);

bool dispc_has_ग_लिखोback(काष्ठा dispc_device *dispc);
पूर्णांक dispc_wb_setup(काष्ठा dispc_device *dispc,
		   स्थिर काष्ठा omap_dss_ग_लिखोback_info *wi,
		   bool mem_to_mem, स्थिर काष्ठा videomode *vm,
		   क्रमागत dss_ग_लिखोback_channel channel_in);
bool dispc_wb_go_busy(काष्ठा dispc_device *dispc);
व्योम dispc_wb_go(काष्ठा dispc_device *dispc);

व्योम dispc_enable_sidle(काष्ठा dispc_device *dispc);
व्योम dispc_disable_sidle(काष्ठा dispc_device *dispc);

व्योम dispc_lcd_enable_संकेत(काष्ठा dispc_device *dispc, bool enable);
व्योम dispc_pck_मुक्त_enable(काष्ठा dispc_device *dispc, bool enable);
व्योम dispc_enable_fअगरomerge(काष्ठा dispc_device *dispc, bool enable);

प्रकार bool (*dispc_भाग_calc_func)(पूर्णांक lckd, पूर्णांक pckd, अचिन्हित दीर्घ lck,
		अचिन्हित दीर्घ pck, व्योम *data);
bool dispc_भाग_calc(काष्ठा dispc_device *dispc, अचिन्हित दीर्घ dispc_freq,
		    अचिन्हित दीर्घ pck_min, अचिन्हित दीर्घ pck_max,
		    dispc_भाग_calc_func func, व्योम *data);

पूर्णांक dispc_calc_घड़ी_rates(काष्ठा dispc_device *dispc,
			   अचिन्हित दीर्घ dispc_fclk_rate,
			   काष्ठा dispc_घड़ी_info *cinfo);


व्योम dispc_ovl_set_fअगरo_threshold(काष्ठा dispc_device *dispc,
				  क्रमागत omap_plane_id plane, u32 low, u32 high);
व्योम dispc_ovl_compute_fअगरo_thresholds(काष्ठा dispc_device *dispc,
				       क्रमागत omap_plane_id plane,
				       u32 *fअगरo_low, u32 *fअगरo_high,
				       bool use_fअगरomerge, bool manual_update);

व्योम dispc_mgr_set_घड़ी_भाग(काष्ठा dispc_device *dispc,
			     क्रमागत omap_channel channel,
			     स्थिर काष्ठा dispc_घड़ी_info *cinfo);
पूर्णांक dispc_mgr_get_घड़ी_भाग(काष्ठा dispc_device *dispc,
			    क्रमागत omap_channel channel,
			    काष्ठा dispc_घड़ी_info *cinfo);
व्योम dispc_set_tv_pclk(काष्ठा dispc_device *dispc, अचिन्हित दीर्घ pclk);

#अगर_घोषित CONFIG_OMAP2_DSS_COLLECT_IRQ_STATS
अटल अंतरभूत व्योम dss_collect_irq_stats(u32 irqstatus, अचिन्हित पूर्णांक *irq_arr)
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

पूर्णांक dss_pll_रेजिस्टर(काष्ठा dss_device *dss, काष्ठा dss_pll *pll);
व्योम dss_pll_unरेजिस्टर(काष्ठा dss_pll *pll);
काष्ठा dss_pll *dss_pll_find(काष्ठा dss_device *dss, स्थिर अक्षर *name);
काष्ठा dss_pll *dss_pll_find_by_src(काष्ठा dss_device *dss,
				    क्रमागत dss_clk_source src);
अचिन्हित पूर्णांक dss_pll_get_clkout_idx_क्रम_src(क्रमागत dss_clk_source src);
पूर्णांक dss_pll_enable(काष्ठा dss_pll *pll);
व्योम dss_pll_disable(काष्ठा dss_pll *pll);
पूर्णांक dss_pll_set_config(काष्ठा dss_pll *pll,
		स्थिर काष्ठा dss_pll_घड़ी_info *cinfo);

bool dss_pll_hsभाग_calc_a(स्थिर काष्ठा dss_pll *pll, अचिन्हित दीर्घ clkdco,
		अचिन्हित दीर्घ out_min, अचिन्हित दीर्घ out_max,
		dss_hsभाग_calc_func func, व्योम *data);
bool dss_pll_calc_a(स्थिर काष्ठा dss_pll *pll, अचिन्हित दीर्घ clkin,
		अचिन्हित दीर्घ pll_min, अचिन्हित दीर्घ pll_max,
		dss_pll_calc_func func, व्योम *data);

bool dss_pll_calc_b(स्थिर काष्ठा dss_pll *pll, अचिन्हित दीर्घ clkin,
	अचिन्हित दीर्घ target_clkout, काष्ठा dss_pll_घड़ी_info *cinfo);

पूर्णांक dss_pll_ग_लिखो_config_type_a(काष्ठा dss_pll *pll,
		स्थिर काष्ठा dss_pll_घड़ी_info *cinfo);
पूर्णांक dss_pll_ग_लिखो_config_type_b(काष्ठा dss_pll *pll,
		स्थिर काष्ठा dss_pll_घड़ी_info *cinfo);
पूर्णांक dss_pll_रुको_reset_करोne(काष्ठा dss_pll *pll);

बाह्य काष्ठा platक्रमm_driver omap_dsshw_driver;
बाह्य काष्ठा platक्रमm_driver omap_dispchw_driver;
#अगर_घोषित CONFIG_OMAP2_DSS_DSI
बाह्य काष्ठा platक्रमm_driver omap_dsihw_driver;
#पूर्ण_अगर
#अगर_घोषित CONFIG_OMAP2_DSS_VENC
बाह्य काष्ठा platक्रमm_driver omap_venchw_driver;
#पूर्ण_अगर
#अगर_घोषित CONFIG_OMAP4_DSS_HDMI
बाह्य काष्ठा platक्रमm_driver omapdss_hdmi4hw_driver;
#पूर्ण_अगर
#अगर_घोषित CONFIG_OMAP5_DSS_HDMI
बाह्य काष्ठा platक्रमm_driver omapdss_hdmi5hw_driver;
#पूर्ण_अगर

#पूर्ण_अगर
