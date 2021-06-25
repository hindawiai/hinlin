<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2019 NXP.
 */

#अगर_अघोषित __DCSS_PRV_H__
#घोषणा __DCSS_PRV_H__

#समावेश <drm/drm_fourcc.h>
#समावेश <drm/drm_plane.h>
#समावेश <linux/पन.स>
#समावेश <video/videomode.h>

#घोषणा SET			0x04
#घोषणा CLR			0x08
#घोषणा TGL			0x0C

#घोषणा dcss_ग_लिखोl(v, c)	ग_लिखोl((v), (c))
#घोषणा dcss_पढ़ोl(c)		पढ़ोl(c)
#घोषणा dcss_set(v, c)		ग_लिखोl((v), (c) + SET)
#घोषणा dcss_clr(v, c)		ग_लिखोl((v), (c) + CLR)
#घोषणा dcss_toggle(v, c)	ग_लिखोl((v), (c) + TGL)

अटल अंतरभूत व्योम dcss_update(u32 v, u32 m, व्योम __iomem *c)
अणु
	ग_लिखोl((पढ़ोl(c) & ~(m)) | (v), (c));
पूर्ण

#घोषणा DCSS_DBG_REG(reg)	अणु.name = #reg, .ofs = regपूर्ण

क्रमागत अणु
	DCSS_IMX8MQ = 0,
पूर्ण;

काष्ठा dcss_type_data अणु
	स्थिर अक्षर *name;
	u32 blkctl_ofs;
	u32 ctxld_ofs;
	u32 rdsrc_ofs;
	u32 wrscl_ofs;
	u32 dtg_ofs;
	u32 scaler_ofs;
	u32 ss_ofs;
	u32 dpr_ofs;
	u32 dtrc_ofs;
	u32 dec400d_ofs;
	u32 hdr10_ofs;
पूर्ण;

काष्ठा dcss_debug_reg अणु
	अक्षर *name;
	u32 ofs;
पूर्ण;

क्रमागत dcss_ctxld_ctx_type अणु
	CTX_DB,
	CTX_SB_HP, /* high-priority */
	CTX_SB_LP, /* low-priority  */
पूर्ण;

काष्ठा dcss_dev अणु
	काष्ठा device *dev;
	स्थिर काष्ठा dcss_type_data *devtype;
	काष्ठा device_node *of_port;

	u32 start_addr;

	काष्ठा dcss_blkctl *blkctl;
	काष्ठा dcss_ctxld *ctxld;
	काष्ठा dcss_dpr *dpr;
	काष्ठा dcss_dtg *dtg;
	काष्ठा dcss_ss *ss;
	काष्ठा dcss_hdr10 *hdr10;
	काष्ठा dcss_scaler *scaler;
	काष्ठा dcss_dtrc *dtrc;
	काष्ठा dcss_dec400d *dec400d;
	काष्ठा dcss_wrscl *wrscl;
	काष्ठा dcss_rdsrc *rdsrc;

	काष्ठा clk *apb_clk;
	काष्ठा clk *axi_clk;
	काष्ठा clk *pix_clk;
	काष्ठा clk *rtrm_clk;
	काष्ठा clk *dtrc_clk;
	काष्ठा clk *pll_src_clk;
	काष्ठा clk *pll_phy_ref_clk;

	bool hdmi_output;

	व्योम (*disable_callback)(व्योम *data);
	काष्ठा completion disable_completion;
पूर्ण;

काष्ठा dcss_dev *dcss_drv_dev_to_dcss(काष्ठा device *dev);
काष्ठा drm_device *dcss_drv_dev_to_drm(काष्ठा device *dev);
काष्ठा dcss_dev *dcss_dev_create(काष्ठा device *dev, bool hdmi_output);
व्योम dcss_dev_destroy(काष्ठा dcss_dev *dcss);
पूर्णांक dcss_dev_runसमय_suspend(काष्ठा device *dev);
पूर्णांक dcss_dev_runसमय_resume(काष्ठा device *dev);
पूर्णांक dcss_dev_suspend(काष्ठा device *dev);
पूर्णांक dcss_dev_resume(काष्ठा device *dev);
व्योम dcss_enable_dtg_and_ss(काष्ठा dcss_dev *dcss);
व्योम dcss_disable_dtg_and_ss(काष्ठा dcss_dev *dcss);

/* BLKCTL */
पूर्णांक dcss_blkctl_init(काष्ठा dcss_dev *dcss, अचिन्हित दीर्घ blkctl_base);
व्योम dcss_blkctl_cfg(काष्ठा dcss_blkctl *blkctl);
व्योम dcss_blkctl_निकास(काष्ठा dcss_blkctl *blkctl);

/* CTXLD */
पूर्णांक dcss_ctxld_init(काष्ठा dcss_dev *dcss, अचिन्हित दीर्घ ctxld_base);
व्योम dcss_ctxld_निकास(काष्ठा dcss_ctxld *ctxld);
व्योम dcss_ctxld_ग_लिखो(काष्ठा dcss_ctxld *ctxld, u32 ctx_id,
		      u32 val, u32 reg_idx);
पूर्णांक dcss_ctxld_resume(काष्ठा dcss_ctxld *dcss_ctxld);
पूर्णांक dcss_ctxld_suspend(काष्ठा dcss_ctxld *dcss_ctxld);
व्योम dcss_ctxld_ग_लिखो_irqsafe(काष्ठा dcss_ctxld *ctlxd, u32 ctx_id, u32 val,
			      u32 reg_ofs);
व्योम dcss_ctxld_kick(काष्ठा dcss_ctxld *ctxld);
bool dcss_ctxld_is_flushed(काष्ठा dcss_ctxld *ctxld);
पूर्णांक dcss_ctxld_enable(काष्ठा dcss_ctxld *ctxld);
व्योम dcss_ctxld_रेजिस्टर_completion(काष्ठा dcss_ctxld *ctxld,
				    काष्ठा completion *dis_completion);
व्योम dcss_ctxld_निश्चित_locked(काष्ठा dcss_ctxld *ctxld);

/* DPR */
पूर्णांक dcss_dpr_init(काष्ठा dcss_dev *dcss, अचिन्हित दीर्घ dpr_base);
व्योम dcss_dpr_निकास(काष्ठा dcss_dpr *dpr);
व्योम dcss_dpr_ग_लिखो_sysctrl(काष्ठा dcss_dpr *dpr);
व्योम dcss_dpr_set_res(काष्ठा dcss_dpr *dpr, पूर्णांक ch_num, u32 xres, u32 yres);
व्योम dcss_dpr_addr_set(काष्ठा dcss_dpr *dpr, पूर्णांक ch_num, u32 luma_base_addr,
		       u32 chroma_base_addr, u16 pitch);
व्योम dcss_dpr_enable(काष्ठा dcss_dpr *dpr, पूर्णांक ch_num, bool en);
व्योम dcss_dpr_क्रमmat_set(काष्ठा dcss_dpr *dpr, पूर्णांक ch_num,
			 स्थिर काष्ठा drm_क्रमmat_info *क्रमmat, u64 modअगरier);
व्योम dcss_dpr_set_rotation(काष्ठा dcss_dpr *dpr, पूर्णांक ch_num, u32 rotation);

/* DTG */
पूर्णांक dcss_dtg_init(काष्ठा dcss_dev *dcss, अचिन्हित दीर्घ dtg_base);
व्योम dcss_dtg_निकास(काष्ठा dcss_dtg *dtg);
bool dcss_dtg_vblank_irq_valid(काष्ठा dcss_dtg *dtg);
व्योम dcss_dtg_vblank_irq_enable(काष्ठा dcss_dtg *dtg, bool en);
व्योम dcss_dtg_vblank_irq_clear(काष्ठा dcss_dtg *dtg);
व्योम dcss_dtg_sync_set(काष्ठा dcss_dtg *dtg, काष्ठा videomode *vm);
व्योम dcss_dtg_css_set(काष्ठा dcss_dtg *dtg);
व्योम dcss_dtg_enable(काष्ठा dcss_dtg *dtg);
व्योम dcss_dtg_shutoff(काष्ठा dcss_dtg *dtg);
bool dcss_dtg_is_enabled(काष्ठा dcss_dtg *dtg);
व्योम dcss_dtg_ctxld_kick_irq_enable(काष्ठा dcss_dtg *dtg, bool en);
bool dcss_dtg_global_alpha_changed(काष्ठा dcss_dtg *dtg, पूर्णांक ch_num, पूर्णांक alpha);
व्योम dcss_dtg_plane_alpha_set(काष्ठा dcss_dtg *dtg, पूर्णांक ch_num,
			      स्थिर काष्ठा drm_क्रमmat_info *क्रमmat, पूर्णांक alpha);
व्योम dcss_dtg_plane_pos_set(काष्ठा dcss_dtg *dtg, पूर्णांक ch_num,
			    पूर्णांक px, पूर्णांक py, पूर्णांक pw, पूर्णांक ph);
व्योम dcss_dtg_ch_enable(काष्ठा dcss_dtg *dtg, पूर्णांक ch_num, bool en);

/* SUBSAM */
पूर्णांक dcss_ss_init(काष्ठा dcss_dev *dcss, अचिन्हित दीर्घ subsam_base);
व्योम dcss_ss_निकास(काष्ठा dcss_ss *ss);
व्योम dcss_ss_enable(काष्ठा dcss_ss *ss);
व्योम dcss_ss_shutoff(काष्ठा dcss_ss *ss);
व्योम dcss_ss_subsam_set(काष्ठा dcss_ss *ss);
व्योम dcss_ss_sync_set(काष्ठा dcss_ss *ss, काष्ठा videomode *vm,
		      bool phsync, bool pvsync);

/* SCALER */
पूर्णांक dcss_scaler_init(काष्ठा dcss_dev *dcss, अचिन्हित दीर्घ scaler_base);
व्योम dcss_scaler_निकास(काष्ठा dcss_scaler *scl);
व्योम dcss_scaler_set_filter(काष्ठा dcss_scaler *scl, पूर्णांक ch_num,
			    क्रमागत drm_scaling_filter scaling_filter);
व्योम dcss_scaler_setup(काष्ठा dcss_scaler *scl, पूर्णांक ch_num,
		       स्थिर काष्ठा drm_क्रमmat_info *क्रमmat,
		       पूर्णांक src_xres, पूर्णांक src_yres, पूर्णांक dst_xres, पूर्णांक dst_yres,
		       u32 vrefresh_hz);
व्योम dcss_scaler_ch_enable(काष्ठा dcss_scaler *scl, पूर्णांक ch_num, bool en);
पूर्णांक dcss_scaler_get_min_max_ratios(काष्ठा dcss_scaler *scl, पूर्णांक ch_num,
				   पूर्णांक *min, पूर्णांक *max);
व्योम dcss_scaler_ग_लिखो_sclctrl(काष्ठा dcss_scaler *scl);

#पूर्ण_अगर /* __DCSS_PRV_H__ */
