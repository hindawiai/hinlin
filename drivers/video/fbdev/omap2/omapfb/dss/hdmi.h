<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * HDMI driver definition क्रम TI OMAP4 Processor.
 *
 * Copyright (C) 2010-2011 Texas Instruments Incorporated - https://www.ti.com/
 */

#अगर_अघोषित _HDMI_H
#घोषणा _HDMI_H

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/hdmi.h>
#समावेश <video/omapfb_dss.h>
#समावेश <sound/omap-hdmi-audपन.स>

#समावेश "dss.h"

/* HDMI Wrapper */

#घोषणा HDMI_WP_REVISION			0x0
#घोषणा HDMI_WP_SYSCONFIG			0x10
#घोषणा HDMI_WP_IRQSTATUS_RAW			0x24
#घोषणा HDMI_WP_IRQSTATUS			0x28
#घोषणा HDMI_WP_IRQENABLE_SET			0x2C
#घोषणा HDMI_WP_IRQENABLE_CLR			0x30
#घोषणा HDMI_WP_IRQWAKEEN			0x34
#घोषणा HDMI_WP_PWR_CTRL			0x40
#घोषणा HDMI_WP_DEBOUNCE			0x44
#घोषणा HDMI_WP_VIDEO_CFG			0x50
#घोषणा HDMI_WP_VIDEO_SIZE			0x60
#घोषणा HDMI_WP_VIDEO_TIMING_H			0x68
#घोषणा HDMI_WP_VIDEO_TIMING_V			0x6C
#घोषणा HDMI_WP_CLK				0x70
#घोषणा HDMI_WP_AUDIO_CFG			0x80
#घोषणा HDMI_WP_AUDIO_CFG2			0x84
#घोषणा HDMI_WP_AUDIO_CTRL			0x88
#घोषणा HDMI_WP_AUDIO_DATA			0x8C

/* HDMI WP IRQ flags */
#घोषणा HDMI_IRQ_CORE				(1 << 0)
#घोषणा HDMI_IRQ_OCP_TIMEOUT			(1 << 4)
#घोषणा HDMI_IRQ_AUDIO_FIFO_UNDERFLOW		(1 << 8)
#घोषणा HDMI_IRQ_AUDIO_FIFO_OVERFLOW		(1 << 9)
#घोषणा HDMI_IRQ_AUDIO_FIFO_SAMPLE_REQ		(1 << 10)
#घोषणा HDMI_IRQ_VIDEO_VSYNC			(1 << 16)
#घोषणा HDMI_IRQ_VIDEO_FRAME_DONE		(1 << 17)
#घोषणा HDMI_IRQ_PHY_LINE5V_ASSERT		(1 << 24)
#घोषणा HDMI_IRQ_LINK_CONNECT			(1 << 25)
#घोषणा HDMI_IRQ_LINK_DISCONNECT		(1 << 26)
#घोषणा HDMI_IRQ_PLL_LOCK			(1 << 29)
#घोषणा HDMI_IRQ_PLL_UNLOCK			(1 << 30)
#घोषणा HDMI_IRQ_PLL_RECAL			(1 << 31)

/* HDMI PLL */

#घोषणा PLLCTRL_PLL_CONTROL			0x0
#घोषणा PLLCTRL_PLL_STATUS			0x4
#घोषणा PLLCTRL_PLL_GO				0x8
#घोषणा PLLCTRL_CFG1				0xC
#घोषणा PLLCTRL_CFG2				0x10
#घोषणा PLLCTRL_CFG3				0x14
#घोषणा PLLCTRL_SSC_CFG1			0x18
#घोषणा PLLCTRL_SSC_CFG2			0x1C
#घोषणा PLLCTRL_CFG4				0x20

/* HDMI PHY */

#घोषणा HDMI_TXPHY_TX_CTRL			0x0
#घोषणा HDMI_TXPHY_DIGITAL_CTRL			0x4
#घोषणा HDMI_TXPHY_POWER_CTRL			0x8
#घोषणा HDMI_TXPHY_PAD_CFG_CTRL			0xC
#घोषणा HDMI_TXPHY_BIST_CONTROL			0x1C

क्रमागत hdmi_pll_pwr अणु
	HDMI_PLLPWRCMD_ALLOFF = 0,
	HDMI_PLLPWRCMD_PLLONLY = 1,
	HDMI_PLLPWRCMD_BOTHON_ALLCLKS = 2,
	HDMI_PLLPWRCMD_BOTHON_NOPHYCLK = 3
पूर्ण;

क्रमागत hdmi_phy_pwr अणु
	HDMI_PHYPWRCMD_OFF = 0,
	HDMI_PHYPWRCMD_LDOON = 1,
	HDMI_PHYPWRCMD_TXON = 2
पूर्ण;

क्रमागत hdmi_core_hdmi_dvi अणु
	HDMI_DVI = 0,
	HDMI_HDMI = 1
पूर्ण;

क्रमागत hdmi_packing_mode अणु
	HDMI_PACK_10b_RGB_YUV444 = 0,
	HDMI_PACK_24b_RGB_YUV444_YUV422 = 1,
	HDMI_PACK_20b_YUV422 = 2,
	HDMI_PACK_ALREADYPACKED = 7
पूर्ण;

क्रमागत hdmi_stereo_channels अणु
	HDMI_AUDIO_STEREO_NOCHANNELS = 0,
	HDMI_AUDIO_STEREO_ONECHANNEL = 1,
	HDMI_AUDIO_STEREO_TWOCHANNELS = 2,
	HDMI_AUDIO_STEREO_THREECHANNELS = 3,
	HDMI_AUDIO_STEREO_FOURCHANNELS = 4
पूर्ण;

क्रमागत hdmi_audio_type अणु
	HDMI_AUDIO_TYPE_LPCM = 0,
	HDMI_AUDIO_TYPE_IEC = 1
पूर्ण;

क्रमागत hdmi_audio_justअगरy अणु
	HDMI_AUDIO_JUSTIFY_LEFT = 0,
	HDMI_AUDIO_JUSTIFY_RIGHT = 1
पूर्ण;

क्रमागत hdmi_audio_sample_order अणु
	HDMI_AUDIO_SAMPLE_RIGHT_FIRST = 0,
	HDMI_AUDIO_SAMPLE_LEFT_FIRST = 1
पूर्ण;

क्रमागत hdmi_audio_samples_perword अणु
	HDMI_AUDIO_ONEWORD_ONESAMPLE = 0,
	HDMI_AUDIO_ONEWORD_TWOSAMPLES = 1
पूर्ण;

क्रमागत hdmi_audio_sample_size_omap अणु
	HDMI_AUDIO_SAMPLE_16BITS = 0,
	HDMI_AUDIO_SAMPLE_24BITS = 1
पूर्ण;

क्रमागत hdmi_audio_transf_mode अणु
	HDMI_AUDIO_TRANSF_DMA = 0,
	HDMI_AUDIO_TRANSF_IRQ = 1
पूर्ण;

क्रमागत hdmi_audio_blk_strt_end_sig अणु
	HDMI_AUDIO_BLOCK_SIG_STARTEND_ON = 0,
	HDMI_AUDIO_BLOCK_SIG_STARTEND_OFF = 1
पूर्ण;

क्रमागत hdmi_core_audio_layout अणु
	HDMI_AUDIO_LAYOUT_2CH = 0,
	HDMI_AUDIO_LAYOUT_8CH = 1,
	HDMI_AUDIO_LAYOUT_6CH = 2
पूर्ण;

क्रमागत hdmi_core_cts_mode अणु
	HDMI_AUDIO_CTS_MODE_HW = 0,
	HDMI_AUDIO_CTS_MODE_SW = 1
पूर्ण;

क्रमागत hdmi_audio_mclk_mode अणु
	HDMI_AUDIO_MCLK_128FS = 0,
	HDMI_AUDIO_MCLK_256FS = 1,
	HDMI_AUDIO_MCLK_384FS = 2,
	HDMI_AUDIO_MCLK_512FS = 3,
	HDMI_AUDIO_MCLK_768FS = 4,
	HDMI_AUDIO_MCLK_1024FS = 5,
	HDMI_AUDIO_MCLK_1152FS = 6,
	HDMI_AUDIO_MCLK_192FS = 7
पूर्ण;

काष्ठा hdmi_video_क्रमmat अणु
	क्रमागत hdmi_packing_mode	packing_mode;
	u32			y_res;	/* Line per panel */
	u32			x_res;	/* pixel per line */
पूर्ण;

काष्ठा hdmi_config अणु
	काष्ठा omap_video_timings timings;
	काष्ठा hdmi_avi_infoframe infoframe;
	क्रमागत hdmi_core_hdmi_dvi hdmi_dvi_mode;
पूर्ण;

काष्ठा hdmi_audio_क्रमmat अणु
	क्रमागत hdmi_stereo_channels		stereo_channels;
	u8					active_chnnls_msk;
	क्रमागत hdmi_audio_type			type;
	क्रमागत hdmi_audio_justअगरy			justअगरication;
	क्रमागत hdmi_audio_sample_order		sample_order;
	क्रमागत hdmi_audio_samples_perword		samples_per_word;
	क्रमागत hdmi_audio_sample_size_omap	sample_size;
	क्रमागत hdmi_audio_blk_strt_end_sig	en_sig_blk_strt_end;
पूर्ण;

काष्ठा hdmi_audio_dma अणु
	u8				transfer_size;
	u8				block_size;
	क्रमागत hdmi_audio_transf_mode	mode;
	u16				fअगरo_threshold;
पूर्ण;

काष्ठा hdmi_core_audio_i2s_config अणु
	u8 in_length_bits;
	u8 justअगरication;
	u8 sck_edge_mode;
	u8 vbit;
	u8 direction;
	u8 shअगरt;
	u8 active_sds;
पूर्ण;

काष्ठा hdmi_core_audio_config अणु
	काष्ठा hdmi_core_audio_i2s_config	i2s_cfg;
	काष्ठा snd_aes_iec958			*iec60958_cfg;
	bool					fs_override;
	u32					n;
	u32					cts;
	u32					aud_par_busclk;
	क्रमागत hdmi_core_audio_layout		layout;
	क्रमागत hdmi_core_cts_mode			cts_mode;
	bool					use_mclk;
	क्रमागत hdmi_audio_mclk_mode		mclk_mode;
	bool					en_acr_pkt;
	bool					en_dsd_audio;
	bool					en_parallel_aud_input;
	bool					en_spdअगर;
पूर्ण;

काष्ठा hdmi_wp_data अणु
	व्योम __iomem *base;
	phys_addr_t phys_base;
पूर्ण;

काष्ठा hdmi_pll_data अणु
	काष्ठा dss_pll pll;

	व्योम __iomem *base;

	काष्ठा hdmi_wp_data *wp;
पूर्ण;

काष्ठा hdmi_phy_data अणु
	व्योम __iomem *base;

	u8 lane_function[4];
	u8 lane_polarity[4];
पूर्ण;

काष्ठा hdmi_core_data अणु
	व्योम __iomem *base;
पूर्ण;

अटल अंतरभूत व्योम hdmi_ग_लिखो_reg(व्योम __iomem *base_addr, स्थिर u32 idx,
		u32 val)
अणु
	__raw_ग_लिखोl(val, base_addr + idx);
पूर्ण

अटल अंतरभूत u32 hdmi_पढ़ो_reg(व्योम __iomem *base_addr, स्थिर u32 idx)
अणु
	वापस __raw_पढ़ोl(base_addr + idx);
पूर्ण

#घोषणा REG_FLD_MOD(base, idx, val, start, end) \
	hdmi_ग_लिखो_reg(base, idx, FLD_MOD(hdmi_पढ़ो_reg(base, idx),\
							val, start, end))
#घोषणा REG_GET(base, idx, start, end) \
	FLD_GET(hdmi_पढ़ो_reg(base, idx), start, end)

अटल अंतरभूत पूर्णांक hdmi_रुको_क्रम_bit_change(व्योम __iomem *base_addr,
		स्थिर u32 idx, पूर्णांक b2, पूर्णांक b1, u32 val)
अणु
	u32 t = 0, v;
	जबतक (val != (v = REG_GET(base_addr, idx, b2, b1))) अणु
		अगर (t++ > 10000)
			वापस v;
		udelay(1);
	पूर्ण
	वापस v;
पूर्ण

/* HDMI wrapper funcs */
पूर्णांक hdmi_wp_video_start(काष्ठा hdmi_wp_data *wp);
व्योम hdmi_wp_video_stop(काष्ठा hdmi_wp_data *wp);
व्योम hdmi_wp_dump(काष्ठा hdmi_wp_data *wp, काष्ठा seq_file *s);
u32 hdmi_wp_get_irqstatus(काष्ठा hdmi_wp_data *wp);
व्योम hdmi_wp_set_irqstatus(काष्ठा hdmi_wp_data *wp, u32 irqstatus);
व्योम hdmi_wp_set_irqenable(काष्ठा hdmi_wp_data *wp, u32 mask);
व्योम hdmi_wp_clear_irqenable(काष्ठा hdmi_wp_data *wp, u32 mask);
पूर्णांक hdmi_wp_set_phy_pwr(काष्ठा hdmi_wp_data *wp, क्रमागत hdmi_phy_pwr val);
पूर्णांक hdmi_wp_set_pll_pwr(काष्ठा hdmi_wp_data *wp, क्रमागत hdmi_pll_pwr val);
व्योम hdmi_wp_video_config_क्रमmat(काष्ठा hdmi_wp_data *wp,
		काष्ठा hdmi_video_क्रमmat *video_fmt);
व्योम hdmi_wp_video_config_पूर्णांकerface(काष्ठा hdmi_wp_data *wp,
		काष्ठा omap_video_timings *timings);
व्योम hdmi_wp_video_config_timing(काष्ठा hdmi_wp_data *wp,
		काष्ठा omap_video_timings *timings);
व्योम hdmi_wp_init_vid_fmt_timings(काष्ठा hdmi_video_क्रमmat *video_fmt,
		काष्ठा omap_video_timings *timings, काष्ठा hdmi_config *param);
पूर्णांक hdmi_wp_init(काष्ठा platक्रमm_device *pdev, काष्ठा hdmi_wp_data *wp);
phys_addr_t hdmi_wp_get_audio_dma_addr(काष्ठा hdmi_wp_data *wp);

/* HDMI PLL funcs */
व्योम hdmi_pll_dump(काष्ठा hdmi_pll_data *pll, काष्ठा seq_file *s);
व्योम hdmi_pll_compute(काष्ठा hdmi_pll_data *pll,
	अचिन्हित दीर्घ target_पंचांगds, काष्ठा dss_pll_घड़ी_info *pi);
पूर्णांक hdmi_pll_init(काष्ठा platक्रमm_device *pdev, काष्ठा hdmi_pll_data *pll,
	काष्ठा hdmi_wp_data *wp);
व्योम hdmi_pll_uninit(काष्ठा hdmi_pll_data *hpll);

/* HDMI PHY funcs */
पूर्णांक hdmi_phy_configure(काष्ठा hdmi_phy_data *phy, अचिन्हित दीर्घ hfbitclk,
	अचिन्हित दीर्घ lfbitclk);
व्योम hdmi_phy_dump(काष्ठा hdmi_phy_data *phy, काष्ठा seq_file *s);
पूर्णांक hdmi_phy_init(काष्ठा platक्रमm_device *pdev, काष्ठा hdmi_phy_data *phy);
पूर्णांक hdmi_phy_parse_lanes(काष्ठा hdmi_phy_data *phy, स्थिर u32 *lanes);

/* HDMI common funcs */
पूर्णांक hdmi_parse_lanes_of(काष्ठा platक्रमm_device *pdev, काष्ठा device_node *ep,
	काष्ठा hdmi_phy_data *phy);

/* Audio funcs */
पूर्णांक hdmi_compute_acr(u32 pclk, u32 sample_freq, u32 *n, u32 *cts);
पूर्णांक hdmi_wp_audio_enable(काष्ठा hdmi_wp_data *wp, bool enable);
पूर्णांक hdmi_wp_audio_core_req_enable(काष्ठा hdmi_wp_data *wp, bool enable);
व्योम hdmi_wp_audio_config_क्रमmat(काष्ठा hdmi_wp_data *wp,
		काष्ठा hdmi_audio_क्रमmat *aud_fmt);
व्योम hdmi_wp_audio_config_dma(काष्ठा hdmi_wp_data *wp,
		काष्ठा hdmi_audio_dma *aud_dma);
अटल अंतरभूत bool hdmi_mode_has_audio(काष्ठा hdmi_config *cfg)
अणु
	वापस cfg->hdmi_dvi_mode == HDMI_HDMI ? true : false;
पूर्ण

/* HDMI DRV data */
काष्ठा omap_hdmi अणु
	काष्ठा mutex lock;
	काष्ठा platक्रमm_device *pdev;

	काष्ठा hdmi_wp_data	wp;
	काष्ठा hdmi_pll_data	pll;
	काष्ठा hdmi_phy_data	phy;
	काष्ठा hdmi_core_data	core;

	काष्ठा hdmi_config cfg;

	काष्ठा regulator *vdda_reg;

	bool core_enabled;

	काष्ठा omap_dss_device output;

	काष्ठा platक्रमm_device *audio_pdev;
	व्योम (*audio_पात_cb)(काष्ठा device *dev);
	पूर्णांक wp_idlemode;

	bool audio_configured;
	काष्ठा omap_dss_audio audio_config;

	/* This lock should be taken when booleans bellow are touched. */
	spinlock_t audio_playing_lock;
	bool audio_playing;
	bool display_enabled;
पूर्ण;

#पूर्ण_अगर
