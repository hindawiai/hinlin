<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * rt715-sdca.h -- RT715 ALSA SoC audio driver header
 *
 * Copyright(c) 2020 Realtek Semiconductor Corp.
 */

#अगर_अघोषित __RT715_SDCA_H__
#घोषणा __RT715_SDCA_H__

#समावेश <linux/regmap.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_type.h>
#समावेश <sound/soc.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/device.h>

काष्ठा rt715_sdca_priv अणु
	काष्ठा regmap *regmap;
	काष्ठा regmap *mbq_regmap;
	काष्ठा snd_soc_codec *codec;
	काष्ठा sdw_slave *slave;
	काष्ठा delayed_work adc_mute_work;
	पूर्णांक dbg_nid;
	पूर्णांक dbg_vid;
	पूर्णांक dbg_payload;
	क्रमागत sdw_slave_status status;
	काष्ठा sdw_bus_params params;
	bool hw_init;
	bool first_init;
	पूर्णांक l_is_unmute;
	पूर्णांक r_is_unmute;
	पूर्णांक hw_sdw_ver;
	पूर्णांक kctl_चयन_orig[4];
	पूर्णांक kctl_2ch_orig[2];
	पूर्णांक kctl_4ch_orig[4];
	पूर्णांक kctl_8ch_orig[8];
पूर्ण;

काष्ठा rt715_sdw_stream_data अणु
	काष्ठा sdw_stream_runसमय *sdw_stream;
पूर्ण;

काष्ठा rt715_sdca_kcontrol_निजी अणु
	अचिन्हित पूर्णांक reg_base;
	अचिन्हित पूर्णांक count;
	अचिन्हित पूर्णांक max;
	अचिन्हित पूर्णांक shअगरt;
	अचिन्हित पूर्णांक invert;
पूर्ण;

/* MIPI Register */
#घोषणा RT715_INT_CTRL					0x005a
#घोषणा RT715_INT_MASK					0x005e

/* NID */
#घोषणा RT715_AUDIO_FUNCTION_GROUP			0x01
#घोषणा RT715_MIC_ADC					0x07
#घोषणा RT715_LINE_ADC					0x08
#घोषणा RT715_MIX_ADC					0x09
#घोषणा RT715_DMIC1					0x12
#घोषणा RT715_DMIC2					0x13
#घोषणा RT715_MIC1					0x18
#घोषणा RT715_MIC2					0x19
#घोषणा RT715_LINE1					0x1a
#घोषणा RT715_LINE2					0x1b
#घोषणा RT715_DMIC3					0x1d
#घोषणा RT715_DMIC4					0x29
#घोषणा RT715_VENDOR_REG				0x20
#घोषणा RT715_MUX_IN1					0x22
#घोषणा RT715_MUX_IN2					0x23
#घोषणा RT715_MUX_IN3					0x24
#घोषणा RT715_MUX_IN4					0x25
#घोषणा RT715_MIX_ADC2					0x27
#घोषणा RT715_INLINE_CMD				0x55
#घोषणा RT715_VENDOR_HDA_CTL				0x61

/* Index (NID:20h) */
#घोषणा RT715_PRODUCT_NUM				0x0
#घोषणा RT715_IRQ_CTRL					0x2b
#घोषणा RT715_AD_FUNC_EN				0x36
#घोषणा RT715_REV_1					0x37
#घोषणा RT715_SDW_INPUT_SEL				0x39
#घोषणा RT715_EXT_DMIC_CLK_CTRL2			0x54

/* Index (NID:61h) */
#घोषणा RT715_HDA_LEGACY_MUX_CTL1			0x00

/* SDCA (Function) */
#घोषणा FUN_JACK_CODEC				0x01
#घोषणा FUN_MIC_ARRAY				0x02
#घोषणा FUN_HID						0x03
/* SDCA (Entity) */
#घोषणा RT715_SDCA_ST_EN							0x00
#घोषणा RT715_SDCA_CS_FREQ_IND_EN					0x01
#घोषणा RT715_SDCA_FU_ADC8_9_VOL					0x02
#घोषणा RT715_SDCA_SMPU_TRIG_ST_EN					0x05
#घोषणा RT715_SDCA_FU_ADC10_11_VOL					0x06
#घोषणा RT715_SDCA_FU_ADC7_27_VOL					0x0a
#घोषणा RT715_SDCA_FU_AMIC_GAIN_EN					0x0c
#घोषणा RT715_SDCA_FU_DMIC_GAIN_EN					0x0e
#घोषणा RT715_SDCA_CX_CLK_SEL_EN					0x10
#घोषणा RT715_SDCA_CREQ_POW_EN						0x18
/* SDCA (Control) */
#घोषणा RT715_SDCA_ST_CTRL							0x00
#घोषणा RT715_SDCA_CX_CLK_SEL_CTRL					0x01
#घोषणा RT715_SDCA_REQ_POW_CTRL					0x01
#घोषणा RT715_SDCA_FU_MUTE_CTRL					0x01
#घोषणा RT715_SDCA_FU_VOL_CTRL						0x02
#घोषणा RT715_SDCA_FU_DMIC_GAIN_CTRL				0x0b
#घोषणा RT715_SDCA_FREQ_IND_CTRL					0x10
#घोषणा RT715_SDCA_SMPU_TRIG_EN_CTRL				0x10
#घोषणा RT715_SDCA_SMPU_TRIG_ST_CTRL				0x11
/* SDCA (Channel) */
#घोषणा CH_00						0x00
#घोषणा CH_01						0x01
#घोषणा CH_02						0x02
#घोषणा CH_03						0x03
#घोषणा CH_04						0x04
#घोषणा CH_05						0x05
#घोषणा CH_06						0x06
#घोषणा CH_07						0x07
#घोषणा CH_08						0x08

#घोषणा RT715_SDCA_DB_STEP			375

क्रमागत अणु
	RT715_AIF1,
	RT715_AIF2,
पूर्ण;

पूर्णांक rt715_sdca_io_init(काष्ठा device *dev, काष्ठा sdw_slave *slave);
पूर्णांक rt715_sdca_init(काष्ठा device *dev, काष्ठा regmap *mbq_regmap,
	काष्ठा regmap *regmap, काष्ठा sdw_slave *slave);

#पूर्ण_अगर /* __RT715_SDCA_H__ */
