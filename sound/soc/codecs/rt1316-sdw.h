<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * rt1316-sdw.h -- RT1316 SDCA ALSA SoC audio driver header
 *
 * Copyright(c) 2021 Realtek Semiconductor Corp.
 */

#अगर_अघोषित __RT1316_SDW_H__
#घोषणा __RT1316_SDW_H__

#समावेश <linux/regmap.h>
#समावेश <linux/soundwire/sdw.h>
#समावेश <linux/soundwire/sdw_type.h>
#समावेश <linux/soundwire/sdw_रेजिस्टरs.h>
#समावेश <sound/soc.h>

/* RT1316 SDCA Control - function number */
#घोषणा FUNC_NUM_SMART_AMP 0x04

/* RT1316 SDCA entity */
#घोषणा RT1316_SDCA_ENT_PDE23 0x31
#घोषणा RT1316_SDCA_ENT_PDE27 0x32
#घोषणा RT1316_SDCA_ENT_PDE22 0x33
#घोषणा RT1316_SDCA_ENT_PDE24 0x34
#घोषणा RT1316_SDCA_ENT_XU24 0x24
#घोषणा RT1316_SDCA_ENT_FU21 0x03
#घोषणा RT1316_SDCA_ENT_UDMPU21 0x02

/* RT1316 SDCA control */
#घोषणा RT1316_SDCA_CTL_SAMPLE_FREQ_INDEX 0x10
#घोषणा RT1316_SDCA_CTL_REQ_POWER_STATE 0x01
#घोषणा RT1316_SDCA_CTL_BYPASS 0x01
#घोषणा RT1316_SDCA_CTL_FU_MUTE 0x01
#घोषणा RT1316_SDCA_CTL_FU_VOLUME 0x02
#घोषणा RT1316_SDCA_CTL_UDMPU_CLUSTER 0x10

/* RT1316 SDCA channel */
#घोषणा CH_L 0x01
#घोषणा CH_R 0x02

काष्ठा rt1316_sdw_priv अणु
	काष्ठा snd_soc_component *component;
	काष्ठा regmap *regmap;
	काष्ठा sdw_slave *sdw_slave;
	क्रमागत sdw_slave_status status;
	काष्ठा sdw_bus_params params;
	bool hw_init;
	bool first_hw_init;
पूर्ण;

काष्ठा sdw_stream_data अणु
	काष्ठा sdw_stream_runसमय *sdw_stream;
पूर्ण;

#पूर्ण_अगर /* __RT1316_SDW_H__ */
