<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (c) 2020 The Linux Foundation. All rights reserved.
 *
 * lpass_hdmi.h - Definitions क्रम the QTi LPASS HDMI
 */

#अगर_अघोषित __LPASS_HDMI_H__
#घोषणा __LPASS_HDMI_H__

#समावेश <linux/regmap.h>

#घोषणा LPASS_HDMITX_LEGACY_DISABLE		0x0
#घोषणा LPASS_HDMITX_LEGACY_ENABLE		0x1
#घोषणा LPASS_DP_AUDIO_BITWIDTH16		0x0
#घोषणा LPASS_DP_AUDIO_BITWIDTH24		0xb
#घोषणा LPASS_DATA_FORMAT_SHIFT			0x1
#घोषणा LPASS_FREQ_BIT_SHIFT			24
#घोषणा LPASS_DATA_FORMAT_LINEAR		0x0
#घोषणा LPASS_DATA_FORMAT_NON_LINEAR	0x1
#घोषणा LPASS_SAMPLING_FREQ32			0x3
#घोषणा LPASS_SAMPLING_FREQ44			0x0
#घोषणा LPASS_SAMPLING_FREQ48			0x2
#घोषणा LPASS_TX_CTL_RESET				0x1
#घोषणा LPASS_TX_CTL_CLEAR				0x0
#घोषणा LPASS_SSTREAM_ENABLE			1
#घोषणा LPASS_SSTREAM_DISABLE			0
#घोषणा LPASS_LAYOUT_SP_DEFAULT			0xf
#घोषणा LPASS_SSTREAM_DEFAULT_ENABLE	1
#घोषणा LPASS_SSTREAM_DEFAULT_DISABLE	0
#घोषणा LPASS_MUTE_ENABLE				1
#घोषणा LPASS_MUTE_DISABLE				0
#घोषणा LPASS_META_DEFAULT_VAL			0
#घोषणा HW_MODE							1
#घोषणा SW_MODE							0
#घोषणा LEGACY_LPASS_LPAIF				1
#घोषणा LEGACY_LPASS_HDMI				0
#घोषणा REPLACE_VBIT					0x1
#घोषणा LINEAR_PCM_DATA					0x0
#घोषणा NON_LINEAR_PCM_DATA				0x1
#घोषणा HDMITX_PARITY_CALC_EN			0x1
#घोषणा HDMITX_PARITY_CALC_DIS			0x0
#घोषणा LPASS_DATA_FORMAT_MASK			GENMASK(1, 1)
#घोषणा LPASS_WORDLENGTH_MASK			GENMASK(3, 0)
#घोषणा LPASS_FREQ_BIT_MASK				GENMASK(27, 24)

#घोषणा LPASS_HDMI_TX_CTL_ADDR(v)		(v->hdmi_tx_ctl_addr)
#घोषणा LPASS_HDMI_TX_LEGACY_ADDR(v)	(v->hdmi_legacy_addr)
#घोषणा LPASS_HDMI_TX_VBIT_CTL_ADDR(v)	(v->hdmi_vbit_addr)
#घोषणा LPASS_HDMI_TX_PARITY_ADDR(v)	(v->hdmi_parity_addr)
#घोषणा LPASS_HDMI_TX_DP_ADDR(v)		(v->hdmi_DP_addr)
#घोषणा LPASS_HDMI_TX_SSTREAM_ADDR(v)	(v->hdmi_sstream_addr)

#घोषणा LPASS_HDMI_TX_CH_LSB_ADDR(v, port) \
		(v->hdmi_ch_lsb_addr + v->ch_stride * (port))
#घोषणा LPASS_HDMI_TX_CH_MSB_ADDR(v, port) \
		(v->hdmi_ch_msb_addr + v->ch_stride * (port))
#घोषणा LPASS_HDMI_TX_DMA_ADDR(v, port) \
		(v->hdmi_dmactl_addr + v->hdmi_dma_stride * (port))

काष्ठा lpass_sstream_ctl अणु
	काष्ठा regmap_field *sstream_en;
	काष्ठा regmap_field *dma_sel;
	काष्ठा regmap_field *स्वतः_bbit_en;
	काष्ठा regmap_field *layout;
	काष्ठा regmap_field *layout_sp;
	काष्ठा regmap_field *set_sp_on_en;
	काष्ठा regmap_field *dp_audio;
	काष्ठा regmap_field *dp_staffing_en;
	काष्ठा regmap_field *dp_sp_b_hw_en;
पूर्ण;

काष्ठा lpass_dp_metadata_ctl अणु
	काष्ठा regmap_field *mute;
	काष्ठा regmap_field *as_sdp_cc;
	काष्ठा regmap_field *as_sdp_ct;
	काष्ठा regmap_field *aअगर_db4;
	काष्ठा regmap_field *frequency;
	काष्ठा regmap_field *mst_index;
	काष्ठा regmap_field *dptx_index;
पूर्ण;

काष्ठा lpass_hdmi_tx_ctl अणु
	काष्ठा regmap_field *soft_reset;
	काष्ठा regmap_field *क्रमce_reset;
पूर्ण;

काष्ठा lpass_hdmitx_dmactl अणु
	काष्ठा regmap_field *use_hw_chs;
	काष्ठा regmap_field *use_hw_usr;
	काष्ठा regmap_field *hw_chs_sel;
	काष्ठा regmap_field *hw_usr_sel;
पूर्ण;

काष्ठा lpass_vbit_ctrl अणु
		काष्ठा regmap_field *replace_vbit;
		काष्ठा regmap_field *vbit_stream;
पूर्ण;

बाह्य स्थिर काष्ठा snd_soc_dai_ops asoc_qcom_lpass_hdmi_dai_ops;

#पूर्ण_अगर /* __LPASS_HDMI_H__ */
