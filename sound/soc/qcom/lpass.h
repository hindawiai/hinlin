<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2010-2011,2013-2015,2020 The Linux Foundation. All rights reserved.
 *
 * lpass.h - Definitions क्रम the QTi LPASS
 */

#अगर_अघोषित __LPASS_H__
#घोषणा __LPASS_H__

#समावेश <linux/clk.h>
#समावेश <linux/compiler.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/regmap.h>
#समावेश <dt-bindings/sound/qcom,lpass.h>
#समावेश "lpass-hdmi.h"

#घोषणा LPASS_AHBIX_CLOCK_FREQUENCY		131072000
#घोषणा LPASS_MAX_MI2S_PORTS			(8)
#घोषणा LPASS_MAX_DMA_CHANNELS			(8)
#घोषणा LPASS_MAX_HDMI_DMA_CHANNELS		(4)

#घोषणा QCOM_REGMAP_FIELD_ALLOC(d, m, f, mf)    \
	करो अणु \
		mf = devm_regmap_field_alloc(d, m, f);     \
		अगर (IS_ERR(mf))                \
			वापस -EINVAL;         \
	पूर्ण जबतक (0)

काष्ठा lpaअगर_i2sctl अणु
	काष्ठा regmap_field *loopback;
	काष्ठा regmap_field *spken;
	काष्ठा regmap_field *spkmode;
	काष्ठा regmap_field *spkmono;
	काष्ठा regmap_field *micen;
	काष्ठा regmap_field *micmode;
	काष्ठा regmap_field *micmono;
	काष्ठा regmap_field *wssrc;
	काष्ठा regmap_field *bitwidth;
पूर्ण;


काष्ठा lpaअगर_dmactl अणु
	काष्ठा regmap_field *पूर्णांकf;
	काष्ठा regmap_field *bursten;
	काष्ठा regmap_field *wpscnt;
	काष्ठा regmap_field *fअगरowm;
	काष्ठा regmap_field *enable;
	काष्ठा regmap_field *dyncclk;
	काष्ठा regmap_field *burst8;
	काष्ठा regmap_field *burst16;
	काष्ठा regmap_field *dynburst;
पूर्ण;

/* Both the CPU DAI and platक्रमm drivers will access this data */
काष्ठा lpass_data अणु

	/* AHB-I/X bus घड़ीs inside the low-घातer audio subप्रणाली (LPASS) */
	काष्ठा clk *ahbix_clk;

	/* MI2S प्रणाली घड़ी */
	काष्ठा clk *mi2s_osr_clk[LPASS_MAX_MI2S_PORTS];

	/* MI2S bit घड़ी (derived from प्रणाली घड़ी by a भागider */
	काष्ठा clk *mi2s_bit_clk[LPASS_MAX_MI2S_PORTS];

	/* MI2S SD lines to use क्रम playback/capture */
	अचिन्हित पूर्णांक mi2s_playback_sd_mode[LPASS_MAX_MI2S_PORTS];
	अचिन्हित पूर्णांक mi2s_capture_sd_mode[LPASS_MAX_MI2S_PORTS];

	/* The state of MI2S prepare dai_ops was called */
	bool mi2s_was_prepared[LPASS_MAX_MI2S_PORTS];

	पूर्णांक hdmi_port_enable;

	/* low-घातer audio पूर्णांकerface (LPAIF) रेजिस्टरs */
	व्योम __iomem *lpaअगर;
	व्योम __iomem *hdmiअगर;

	/* regmap backed by the low-घातer audio पूर्णांकerface (LPAIF) रेजिस्टरs */
	काष्ठा regmap *lpaअगर_map;
	काष्ठा regmap *hdmiअगर_map;

	/* पूर्णांकerrupts from the low-घातer audio पूर्णांकerface (LPAIF) */
	पूर्णांक lpaअगर_irq;
	पूर्णांक hdmiअगर_irq;
	/* SOC specअगरic variations in the LPASS IP पूर्णांकegration */
	काष्ठा lpass_variant *variant;

	/* bit map to keep track of अटल channel allocations */
	अचिन्हित दीर्घ dma_ch_bit_map;
	अचिन्हित दीर्घ hdmi_dma_ch_bit_map;

	/* used it क्रम handling पूर्णांकerrupt per dma channel */
	काष्ठा snd_pcm_substream *substream[LPASS_MAX_DMA_CHANNELS];
	काष्ठा snd_pcm_substream *hdmi_substream[LPASS_MAX_HDMI_DMA_CHANNELS];

	/* SOC specअगरic घड़ी list */
	काष्ठा clk_bulk_data *clks;
	पूर्णांक num_clks;

	/* Regmap fields of I2SCTL & DMACTL रेजिस्टरs bitfields */
	काष्ठा lpaअगर_i2sctl *i2sctl;
	काष्ठा lpaअगर_dmactl *rd_dmactl;
	काष्ठा lpaअगर_dmactl *wr_dmactl;
	काष्ठा lpaअगर_dmactl *hdmi_rd_dmactl;
	/* Regmap fields of HDMI_CTRL रेजिस्टरs*/
	काष्ठा regmap_field *hdmitx_legacy_en;
	काष्ठा regmap_field *hdmitx_parity_calc_en;
	काष्ठा regmap_field *hdmitx_ch_msb[LPASS_MAX_HDMI_DMA_CHANNELS];
	काष्ठा regmap_field *hdmitx_ch_lsb[LPASS_MAX_HDMI_DMA_CHANNELS];
	काष्ठा lpass_hdmi_tx_ctl *tx_ctl;
	काष्ठा lpass_vbit_ctrl *vbit_ctl;
	काष्ठा lpass_hdmitx_dmactl *hdmi_tx_dmactl[LPASS_MAX_HDMI_DMA_CHANNELS];
	काष्ठा lpass_dp_metadata_ctl *meta_ctl;
	काष्ठा lpass_sstream_ctl *sstream_ctl;
पूर्ण;

/* Vairant data per each SOC */
काष्ठा lpass_variant अणु
	u32	irq_reg_base;
	u32	irq_reg_stride;
	u32	irq_ports;
	u32	rdma_reg_base;
	u32	rdma_reg_stride;
	u32	rdma_channels;
	u32	hdmi_rdma_reg_base;
	u32	hdmi_rdma_reg_stride;
	u32	hdmi_rdma_channels;
	u32	wrdma_reg_base;
	u32	wrdma_reg_stride;
	u32	wrdma_channels;
	u32	i2sctrl_reg_base;
	u32	i2sctrl_reg_stride;
	u32	i2s_ports;

	/* I2SCTL Register fields */
	काष्ठा reg_field loopback;
	काष्ठा reg_field spken;
	काष्ठा reg_field spkmode;
	काष्ठा reg_field spkmono;
	काष्ठा reg_field micen;
	काष्ठा reg_field micmode;
	काष्ठा reg_field micmono;
	काष्ठा reg_field wssrc;
	काष्ठा reg_field bitwidth;

	u32	hdmi_irq_reg_base;
	u32	hdmi_irq_reg_stride;
	u32	hdmi_irq_ports;

	/* HDMI specअगरic controls */
	u32	hdmi_tx_ctl_addr;
	u32	hdmi_legacy_addr;
	u32	hdmi_vbit_addr;
	u32	hdmi_ch_lsb_addr;
	u32	hdmi_ch_msb_addr;
	u32	ch_stride;
	u32	hdmi_parity_addr;
	u32	hdmi_dmactl_addr;
	u32	hdmi_dma_stride;
	u32	hdmi_DP_addr;
	u32	hdmi_sstream_addr;

	/* HDMI SSTREAM CTRL fields  */
	काष्ठा reg_field sstream_en;
	काष्ठा reg_field dma_sel;
	काष्ठा reg_field स्वतः_bbit_en;
	काष्ठा reg_field layout;
	काष्ठा reg_field layout_sp;
	काष्ठा reg_field set_sp_on_en;
	काष्ठा reg_field dp_audio;
	काष्ठा reg_field dp_staffing_en;
	काष्ठा reg_field dp_sp_b_hw_en;

	/* HDMI DP METADATA CTL fields */
	काष्ठा reg_field mute;
	काष्ठा reg_field as_sdp_cc;
	काष्ठा reg_field as_sdp_ct;
	काष्ठा reg_field aअगर_db4;
	काष्ठा reg_field frequency;
	काष्ठा reg_field mst_index;
	काष्ठा reg_field dptx_index;

	/* HDMI TX CTRL fields */
	काष्ठा reg_field soft_reset;
	काष्ठा reg_field क्रमce_reset;

	/* HDMI TX DMA CTRL */
	काष्ठा reg_field use_hw_chs;
	काष्ठा reg_field use_hw_usr;
	काष्ठा reg_field hw_chs_sel;
	काष्ठा reg_field hw_usr_sel;

	/* HDMI VBIT CTRL */
	काष्ठा reg_field replace_vbit;
	काष्ठा reg_field vbit_stream;

	/* HDMI TX LEGACY */
	काष्ठा reg_field legacy_en;

	/* HDMI TX PARITY */
	काष्ठा reg_field calc_en;

	/* HDMI CH LSB */
	काष्ठा reg_field lsb_bits;

	/* HDMI CH MSB */
	काष्ठा reg_field msb_bits;

	काष्ठा reg_field hdmi_rdma_bursten;
	काष्ठा reg_field hdmi_rdma_wpscnt;
	काष्ठा reg_field hdmi_rdma_fअगरowm;
	काष्ठा reg_field hdmi_rdma_enable;
	काष्ठा reg_field hdmi_rdma_dyncclk;
	काष्ठा reg_field hdmi_rdma_burst8;
	काष्ठा reg_field hdmi_rdma_burst16;
	काष्ठा reg_field hdmi_rdma_dynburst;

	/* RD_DMA Register fields */
	काष्ठा reg_field rdma_पूर्णांकf;
	काष्ठा reg_field rdma_bursten;
	काष्ठा reg_field rdma_wpscnt;
	काष्ठा reg_field rdma_fअगरowm;
	काष्ठा reg_field rdma_enable;
	काष्ठा reg_field rdma_dyncclk;

	/* WR_DMA Register fields */
	काष्ठा reg_field wrdma_पूर्णांकf;
	काष्ठा reg_field wrdma_bursten;
	काष्ठा reg_field wrdma_wpscnt;
	काष्ठा reg_field wrdma_fअगरowm;
	काष्ठा reg_field wrdma_enable;
	काष्ठा reg_field wrdma_dyncclk;

	/**
	 * on SOCs like APQ8016 the channel control bits start
	 * at dअगरferent offset to ipq806x
	 **/
	u32	dmactl_audअगर_start;
	u32	wrdma_channel_start;
	/* SOC specअगरic initialization like घड़ीs */
	पूर्णांक (*init)(काष्ठा platक्रमm_device *pdev);
	पूर्णांक (*निकास)(काष्ठा platक्रमm_device *pdev);
	पूर्णांक (*alloc_dma_channel)(काष्ठा lpass_data *data, पूर्णांक direction, अचिन्हित पूर्णांक dai_id);
	पूर्णांक (*मुक्त_dma_channel)(काष्ठा lpass_data *data, पूर्णांक ch, अचिन्हित पूर्णांक dai_id);

	/* SOC specअगरic dais */
	काष्ठा snd_soc_dai_driver *dai_driver;
	पूर्णांक num_dai;
	स्थिर अक्षर * स्थिर *dai_osr_clk_names;
	स्थिर अक्षर * स्थिर *dai_bit_clk_names;

	/* SOC specअगरic घड़ीs configuration */
	स्थिर अक्षर **clk_name;
	पूर्णांक num_clks;
पूर्ण;

/* रेजिस्टर the platक्रमm driver from the CPU DAI driver */
पूर्णांक asoc_qcom_lpass_platक्रमm_रेजिस्टर(काष्ठा platक्रमm_device *);
पूर्णांक asoc_qcom_lpass_cpu_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev);
व्योम asoc_qcom_lpass_cpu_platक्रमm_shutकरोwn(काष्ठा platक्रमm_device *pdev);
पूर्णांक asoc_qcom_lpass_cpu_platक्रमm_probe(काष्ठा platक्रमm_device *pdev);
पूर्णांक asoc_qcom_lpass_cpu_dai_probe(काष्ठा snd_soc_dai *dai);
बाह्य स्थिर काष्ठा snd_soc_dai_ops asoc_qcom_lpass_cpu_dai_ops;

#पूर्ण_अगर /* __LPASS_H__ */
