<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2011-2017, The Linux Foundation. All rights reserved.
// Copyright (c) 2018, Linaro Limited

#समावेश <linux/init.h>
#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/bitops.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/pcm.h>
#समावेश <sound/control.h>
#समावेश <sound/asound.h>
#समावेश <sound/pcm_params.h>
#समावेश "q6afe.h"
#समावेश "q6asm.h"
#समावेश "q6adm.h"
#समावेश "q6routing.h"

#घोषणा DRV_NAME "q6routing-component"

#घोषणा Q6ROUTING_RX_MIXERS(id)						\
	SOC_SINGLE_EXT("MultiMedia1", id,				\
	MSM_FRONTEND_DAI_MULTIMEDIA1, 1, 0, msm_routing_get_audio_mixer,\
	msm_routing_put_audio_mixer),					\
	SOC_SINGLE_EXT("MultiMedia2", id,				\
	MSM_FRONTEND_DAI_MULTIMEDIA2, 1, 0, msm_routing_get_audio_mixer,\
	msm_routing_put_audio_mixer),					\
	SOC_SINGLE_EXT("MultiMedia3", id,				\
	MSM_FRONTEND_DAI_MULTIMEDIA3, 1, 0, msm_routing_get_audio_mixer,\
	msm_routing_put_audio_mixer),					\
	SOC_SINGLE_EXT("MultiMedia4", id,				\
	MSM_FRONTEND_DAI_MULTIMEDIA4, 1, 0, msm_routing_get_audio_mixer,\
	msm_routing_put_audio_mixer),					\
	SOC_SINGLE_EXT("MultiMedia5", id,				\
	MSM_FRONTEND_DAI_MULTIMEDIA5, 1, 0, msm_routing_get_audio_mixer,\
	msm_routing_put_audio_mixer),					\
	SOC_SINGLE_EXT("MultiMedia6", id,				\
	MSM_FRONTEND_DAI_MULTIMEDIA6, 1, 0, msm_routing_get_audio_mixer,\
	msm_routing_put_audio_mixer),					\
	SOC_SINGLE_EXT("MultiMedia7", id,				\
	MSM_FRONTEND_DAI_MULTIMEDIA7, 1, 0, msm_routing_get_audio_mixer,\
	msm_routing_put_audio_mixer),					\
	SOC_SINGLE_EXT("MultiMedia8", id,				\
	MSM_FRONTEND_DAI_MULTIMEDIA8, 1, 0, msm_routing_get_audio_mixer,\
	msm_routing_put_audio_mixer),

#घोषणा Q6ROUTING_RX_DAPM_ROUTE(mix_name, s)	\
	अणु mix_name, "MultiMedia1", "MM_DL1" पूर्ण,	\
	अणु mix_name, "MultiMedia2", "MM_DL2" पूर्ण,	\
	अणु mix_name, "MultiMedia3", "MM_DL3" पूर्ण,	\
	अणु mix_name, "MultiMedia4", "MM_DL4" पूर्ण,	\
	अणु mix_name, "MultiMedia5", "MM_DL5" पूर्ण,	\
	अणु mix_name, "MultiMedia6", "MM_DL6" पूर्ण,	\
	अणु mix_name, "MultiMedia7", "MM_DL7" पूर्ण,	\
	अणु mix_name, "MultiMedia8", "MM_DL8" पूर्ण,	\
	अणु s, शून्य, mix_name पूर्ण

#घोषणा Q6ROUTING_TX_DAPM_ROUTE(mix_name)		\
	अणु mix_name, "PRI_MI2S_TX", "PRI_MI2S_TX" पूर्ण,	\
	अणु mix_name, "SEC_MI2S_TX", "SEC_MI2S_TX" पूर्ण,	\
	अणु mix_name, "QUAT_MI2S_TX", "QUAT_MI2S_TX" पूर्ण,	\
	अणु mix_name, "TERT_MI2S_TX", "TERT_MI2S_TX" पूर्ण,		\
	अणु mix_name, "SLIMBUS_0_TX", "SLIMBUS_0_TX" पूर्ण,		\
	अणु mix_name, "SLIMBUS_1_TX", "SLIMBUS_1_TX" पूर्ण,		\
	अणु mix_name, "SLIMBUS_2_TX", "SLIMBUS_2_TX" पूर्ण,		\
	अणु mix_name, "SLIMBUS_3_TX", "SLIMBUS_3_TX" पूर्ण,		\
	अणु mix_name, "SLIMBUS_4_TX", "SLIMBUS_4_TX" पूर्ण,		\
	अणु mix_name, "SLIMBUS_5_TX", "SLIMBUS_5_TX" पूर्ण,		\
	अणु mix_name, "SLIMBUS_6_TX", "SLIMBUS_6_TX" पूर्ण,		\
	अणु mix_name, "PRIMARY_TDM_TX_0", "PRIMARY_TDM_TX_0"पूर्ण,	\
	अणु mix_name, "PRIMARY_TDM_TX_1", "PRIMARY_TDM_TX_1"पूर्ण,	\
	अणु mix_name, "PRIMARY_TDM_TX_2", "PRIMARY_TDM_TX_2"पूर्ण,	\
	अणु mix_name, "PRIMARY_TDM_TX_3", "PRIMARY_TDM_TX_3"पूर्ण,	\
	अणु mix_name, "PRIMARY_TDM_TX_4", "PRIMARY_TDM_TX_4"पूर्ण,	\
	अणु mix_name, "PRIMARY_TDM_TX_5", "PRIMARY_TDM_TX_5"पूर्ण,	\
	अणु mix_name, "PRIMARY_TDM_TX_6", "PRIMARY_TDM_TX_6"पूर्ण,	\
	अणु mix_name, "PRIMARY_TDM_TX_7", "PRIMARY_TDM_TX_7"पूर्ण,	\
	अणु mix_name, "SEC_TDM_TX_0", "SEC_TDM_TX_0"पूर्ण,		\
	अणु mix_name, "SEC_TDM_TX_1", "SEC_TDM_TX_1"पूर्ण,		\
	अणु mix_name, "SEC_TDM_TX_2", "SEC_TDM_TX_2"पूर्ण,		\
	अणु mix_name, "SEC_TDM_TX_3", "SEC_TDM_TX_3"पूर्ण,		\
	अणु mix_name, "SEC_TDM_TX_4", "SEC_TDM_TX_4"पूर्ण,		\
	अणु mix_name, "SEC_TDM_TX_5", "SEC_TDM_TX_5"पूर्ण,		\
	अणु mix_name, "SEC_TDM_TX_6", "SEC_TDM_TX_6"पूर्ण,		\
	अणु mix_name, "SEC_TDM_TX_7", "SEC_TDM_TX_7"पूर्ण,		\
	अणु mix_name, "TERT_TDM_TX_0", "TERT_TDM_TX_0"पूर्ण,		\
	अणु mix_name, "TERT_TDM_TX_1", "TERT_TDM_TX_1"पूर्ण,		\
	अणु mix_name, "TERT_TDM_TX_2", "TERT_TDM_TX_2"पूर्ण,		\
	अणु mix_name, "TERT_TDM_TX_3", "TERT_TDM_TX_3"पूर्ण,		\
	अणु mix_name, "TERT_TDM_TX_4", "TERT_TDM_TX_4"पूर्ण,		\
	अणु mix_name, "TERT_TDM_TX_5", "TERT_TDM_TX_5"पूर्ण,		\
	अणु mix_name, "TERT_TDM_TX_6", "TERT_TDM_TX_6"पूर्ण,		\
	अणु mix_name, "TERT_TDM_TX_7", "TERT_TDM_TX_7"पूर्ण,		\
	अणु mix_name, "QUAT_TDM_TX_0", "QUAT_TDM_TX_0"पूर्ण,		\
	अणु mix_name, "QUAT_TDM_TX_1", "QUAT_TDM_TX_1"पूर्ण,		\
	अणु mix_name, "QUAT_TDM_TX_2", "QUAT_TDM_TX_2"पूर्ण,		\
	अणु mix_name, "QUAT_TDM_TX_3", "QUAT_TDM_TX_3"पूर्ण,		\
	अणु mix_name, "QUAT_TDM_TX_4", "QUAT_TDM_TX_4"पूर्ण,		\
	अणु mix_name, "QUAT_TDM_TX_5", "QUAT_TDM_TX_5"पूर्ण,		\
	अणु mix_name, "QUAT_TDM_TX_6", "QUAT_TDM_TX_6"पूर्ण,		\
	अणु mix_name, "QUAT_TDM_TX_7", "QUAT_TDM_TX_7"पूर्ण,		\
	अणु mix_name, "QUIN_TDM_TX_0", "QUIN_TDM_TX_0"पूर्ण,		\
	अणु mix_name, "QUIN_TDM_TX_1", "QUIN_TDM_TX_1"पूर्ण,		\
	अणु mix_name, "QUIN_TDM_TX_2", "QUIN_TDM_TX_2"पूर्ण,		\
	अणु mix_name, "QUIN_TDM_TX_3", "QUIN_TDM_TX_3"पूर्ण,		\
	अणु mix_name, "QUIN_TDM_TX_4", "QUIN_TDM_TX_4"पूर्ण,		\
	अणु mix_name, "QUIN_TDM_TX_5", "QUIN_TDM_TX_5"पूर्ण,		\
	अणु mix_name, "QUIN_TDM_TX_6", "QUIN_TDM_TX_6"पूर्ण,		\
	अणु mix_name, "QUIN_TDM_TX_7", "QUIN_TDM_TX_7"पूर्ण,		\
	अणु mix_name, "WSA_CODEC_DMA_TX_0", "WSA_CODEC_DMA_TX_0"पूर्ण,	\
	अणु mix_name, "WSA_CODEC_DMA_TX_1", "WSA_CODEC_DMA_TX_1"पूर्ण,	\
	अणु mix_name, "WSA_CODEC_DMA_TX_2", "WSA_CODEC_DMA_TX_2"पूर्ण,	\
	अणु mix_name, "VA_CODEC_DMA_TX_0", "VA_CODEC_DMA_TX_0"पूर्ण,	\
	अणु mix_name, "VA_CODEC_DMA_TX_1", "VA_CODEC_DMA_TX_1"पूर्ण,	\
	अणु mix_name, "VA_CODEC_DMA_TX_2", "VA_CODEC_DMA_TX_2"पूर्ण,	\
	अणु mix_name, "TX_CODEC_DMA_TX_0", "TX_CODEC_DMA_TX_0"पूर्ण,	\
	अणु mix_name, "TX_CODEC_DMA_TX_1", "TX_CODEC_DMA_TX_1"पूर्ण,	\
	अणु mix_name, "TX_CODEC_DMA_TX_2", "TX_CODEC_DMA_TX_2"पूर्ण,	\
	अणु mix_name, "TX_CODEC_DMA_TX_3", "TX_CODEC_DMA_TX_3"पूर्ण,	\
	अणु mix_name, "TX_CODEC_DMA_TX_4", "TX_CODEC_DMA_TX_4"पूर्ण,	\
	अणु mix_name, "TX_CODEC_DMA_TX_5", "TX_CODEC_DMA_TX_5"पूर्ण

#घोषणा Q6ROUTING_TX_MIXERS(id)						\
	SOC_SINGLE_EXT("PRI_MI2S_TX", PRIMARY_MI2S_TX,			\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SEC_MI2S_TX", SECONDARY_MI2S_TX,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("TERT_MI2S_TX", TERTIARY_MI2S_TX,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUAT_MI2S_TX", QUATERNARY_MI2S_TX,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SLIMBUS_0_TX", SLIMBUS_0_TX,			\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SLIMBUS_1_TX", SLIMBUS_1_TX,			\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SLIMBUS_2_TX", SLIMBUS_2_TX,			\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SLIMBUS_3_TX", SLIMBUS_3_TX,			\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SLIMBUS_4_TX", SLIMBUS_4_TX,			\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SLIMBUS_5_TX", SLIMBUS_5_TX,			\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SLIMBUS_6_TX", SLIMBUS_6_TX,			\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("PRIMARY_TDM_TX_0", PRIMARY_TDM_TX_0,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("PRIMARY_TDM_TX_1", PRIMARY_TDM_TX_1,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("PRIMARY_TDM_TX_2", PRIMARY_TDM_TX_2,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("PRIMARY_TDM_TX_3", PRIMARY_TDM_TX_3,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("PRIMARY_TDM_TX_4", PRIMARY_TDM_TX_4,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("PRIMARY_TDM_TX_5", PRIMARY_TDM_TX_5,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("PRIMARY_TDM_TX_6", PRIMARY_TDM_TX_6,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("PRIMARY_TDM_TX_7", PRIMARY_TDM_TX_7,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SEC_TDM_TX_0", SECONDARY_TDM_TX_0,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SEC_TDM_TX_1", SECONDARY_TDM_TX_1,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SEC_TDM_TX_2", SECONDARY_TDM_TX_2,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SEC_TDM_TX_3", SECONDARY_TDM_TX_3,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SEC_TDM_TX_4", SECONDARY_TDM_TX_4,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SEC_TDM_TX_5", SECONDARY_TDM_TX_5,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SEC_TDM_TX_6", SECONDARY_TDM_TX_6,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("SEC_TDM_TX_7", SECONDARY_TDM_TX_7,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("TERT_TDM_TX_0", TERTIARY_TDM_TX_0,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("TERT_TDM_TX_1", TERTIARY_TDM_TX_1,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("TERT_TDM_TX_2", TERTIARY_TDM_TX_2,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("TERT_TDM_TX_3", TERTIARY_TDM_TX_3,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("TERT_TDM_TX_4", TERTIARY_TDM_TX_4,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("TERT_TDM_TX_5", TERTIARY_TDM_TX_5,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("TERT_TDM_TX_6", TERTIARY_TDM_TX_6,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("TERT_TDM_TX_7", TERTIARY_TDM_TX_7,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUAT_TDM_TX_0", QUATERNARY_TDM_TX_0,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUAT_TDM_TX_1", QUATERNARY_TDM_TX_1,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUAT_TDM_TX_2", QUATERNARY_TDM_TX_2,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUAT_TDM_TX_3", QUATERNARY_TDM_TX_3,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUAT_TDM_TX_4", QUATERNARY_TDM_TX_4,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUAT_TDM_TX_5", QUATERNARY_TDM_TX_5,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUAT_TDM_TX_6", QUATERNARY_TDM_TX_6,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUAT_TDM_TX_7", QUATERNARY_TDM_TX_7,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUIN_TDM_TX_0", QUINARY_TDM_TX_0,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUIN_TDM_TX_1", QUINARY_TDM_TX_1,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUIN_TDM_TX_2", QUINARY_TDM_TX_2,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUIN_TDM_TX_3", QUINARY_TDM_TX_3,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUIN_TDM_TX_4", QUINARY_TDM_TX_4,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUIN_TDM_TX_5", QUINARY_TDM_TX_5,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUIN_TDM_TX_6", QUINARY_TDM_TX_6,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("QUIN_TDM_TX_7", QUINARY_TDM_TX_7,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("WSA_CODEC_DMA_TX_0", WSA_CODEC_DMA_TX_0,	\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("WSA_CODEC_DMA_TX_1", WSA_CODEC_DMA_TX_1,	\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("WSA_CODEC_DMA_TX_2", WSA_CODEC_DMA_TX_2,	\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("VA_CODEC_DMA_TX_0", VA_CODEC_DMA_TX_0,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("VA_CODEC_DMA_TX_1", VA_CODEC_DMA_TX_1,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("VA_CODEC_DMA_TX_2", VA_CODEC_DMA_TX_2,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("TX_CODEC_DMA_TX_0", TX_CODEC_DMA_TX_0,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("TX_CODEC_DMA_TX_1", TX_CODEC_DMA_TX_1,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("TX_CODEC_DMA_TX_2", TX_CODEC_DMA_TX_2,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("TX_CODEC_DMA_TX_3", TX_CODEC_DMA_TX_3,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("TX_CODEC_DMA_TX_4", TX_CODEC_DMA_TX_4,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),				\
	SOC_SINGLE_EXT("TX_CODEC_DMA_TX_5", TX_CODEC_DMA_TX_5,		\
		id, 1, 0, msm_routing_get_audio_mixer,			\
		msm_routing_put_audio_mixer),

काष्ठा session_data अणु
	पूर्णांक state;
	पूर्णांक port_id;
	पूर्णांक path_type;
	पूर्णांक app_type;
	पूर्णांक acdb_id;
	पूर्णांक sample_rate;
	पूर्णांक bits_per_sample;
	पूर्णांक channels;
	पूर्णांक perf_mode;
	पूर्णांक numcopps;
	पूर्णांक fedai_id;
	अचिन्हित दीर्घ copp_map;
	काष्ठा q6copp *copps[MAX_COPPS_PER_PORT];
पूर्ण;

काष्ठा msm_routing_data अणु
	काष्ठा session_data sessions[MAX_SESSIONS];
	काष्ठा session_data port_data[AFE_MAX_PORTS];
	काष्ठा device *dev;
	काष्ठा mutex lock;
पूर्ण;

अटल काष्ठा msm_routing_data *routing_data;

/**
 * q6routing_stream_खोलो() - Register a new stream क्रम route setup
 *
 * @fedai_id: Frontend dai id.
 * @perf_mode: Perक्रमmance mode.
 * @stream_id: ASM stream id to map.
 * @stream_type: Direction of stream
 *
 * Return: Will be an negative on error or a zero on success.
 */
पूर्णांक q6routing_stream_खोलो(पूर्णांक fedai_id, पूर्णांक perf_mode,
			   पूर्णांक stream_id, पूर्णांक stream_type)
अणु
	पूर्णांक j, topology, num_copps = 0;
	काष्ठा route_payload payload;
	काष्ठा q6copp *copp;
	पूर्णांक copp_idx;
	काष्ठा session_data *session, *pdata;

	अगर (!routing_data) अणु
		pr_err("Routing driver not yet ready\n");
		वापस -EINVAL;
	पूर्ण

	session = &routing_data->sessions[stream_id - 1];
	pdata = &routing_data->port_data[session->port_id];

	mutex_lock(&routing_data->lock);
	session->fedai_id = fedai_id;

	session->path_type = pdata->path_type;
	session->sample_rate = pdata->sample_rate;
	session->channels = pdata->channels;
	session->bits_per_sample = pdata->bits_per_sample;

	payload.num_copps = 0; /* only RX needs to use payload */
	topology = शून्य_COPP_TOPOLOGY;
	copp = q6adm_खोलो(routing_data->dev, session->port_id,
			      session->path_type, session->sample_rate,
			      session->channels, topology, perf_mode,
			      session->bits_per_sample, 0, 0);

	अगर (IS_ERR_OR_शून्य(copp)) अणु
		mutex_unlock(&routing_data->lock);
		वापस -EINVAL;
	पूर्ण

	copp_idx = q6adm_get_copp_id(copp);
	set_bit(copp_idx, &session->copp_map);
	session->copps[copp_idx] = copp;

	क्रम_each_set_bit(j, &session->copp_map, MAX_COPPS_PER_PORT) अणु
		payload.port_id[num_copps] = session->port_id;
		payload.copp_idx[num_copps] = j;
		num_copps++;
	पूर्ण

	अगर (num_copps) अणु
		payload.num_copps = num_copps;
		payload.session_id = stream_id;
		q6adm_matrix_map(routing_data->dev, session->path_type,
				 payload, perf_mode);
	पूर्ण
	mutex_unlock(&routing_data->lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(q6routing_stream_खोलो);

अटल काष्ठा session_data *get_session_from_id(काष्ठा msm_routing_data *data,
						पूर्णांक fedai_id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_SESSIONS; i++) अणु
		अगर (fedai_id == data->sessions[i].fedai_id)
			वापस &data->sessions[i];
	पूर्ण

	वापस शून्य;
पूर्ण
/**
 * q6routing_stream_बंद() - Deरेजिस्टर a stream
 *
 * @fedai_id: Frontend dai id.
 * @stream_type: Direction of stream
 *
 * Return: Will be an negative on error or a zero on success.
 */
व्योम q6routing_stream_बंद(पूर्णांक fedai_id, पूर्णांक stream_type)
अणु
	काष्ठा session_data *session;
	पूर्णांक idx;

	session = get_session_from_id(routing_data, fedai_id);
	अगर (!session)
		वापस;

	क्रम_each_set_bit(idx, &session->copp_map, MAX_COPPS_PER_PORT) अणु
		अगर (session->copps[idx]) अणु
			q6adm_बंद(routing_data->dev, session->copps[idx]);
			session->copps[idx] = शून्य;
		पूर्ण
	पूर्ण

	session->fedai_id = -1;
	session->copp_map = 0;
पूर्ण
EXPORT_SYMBOL_GPL(q6routing_stream_बंद);

अटल पूर्णांक msm_routing_get_audio_mixer(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm =
	    snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा soc_mixer_control *mc =
	    (काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	पूर्णांक session_id = mc->shअगरt;
	काष्ठा snd_soc_component *c = snd_soc_dapm_to_component(dapm);
	काष्ठा msm_routing_data *priv = dev_get_drvdata(c->dev);
	काष्ठा session_data *session = &priv->sessions[session_id];

	अगर (session->port_id == mc->reg)
		ucontrol->value.पूर्णांकeger.value[0] = 1;
	अन्यथा
		ucontrol->value.पूर्णांकeger.value[0] = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक msm_routing_put_audio_mixer(काष्ठा snd_kcontrol *kcontrol,
				       काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_soc_dapm_context *dapm =
				    snd_soc_dapm_kcontrol_dapm(kcontrol);
	काष्ठा snd_soc_component *c = snd_soc_dapm_to_component(dapm);
	काष्ठा msm_routing_data *data = dev_get_drvdata(c->dev);
	काष्ठा soc_mixer_control *mc =
		    (काष्ठा soc_mixer_control *)kcontrol->निजी_value;
	काष्ठा snd_soc_dapm_update *update = शून्य;
	पूर्णांक be_id = mc->reg;
	पूर्णांक session_id = mc->shअगरt;
	काष्ठा session_data *session = &data->sessions[session_id];

	अगर (ucontrol->value.पूर्णांकeger.value[0]) अणु
		session->port_id = be_id;
		snd_soc_dapm_mixer_update_घातer(dapm, kcontrol, 1, update);
	पूर्ण अन्यथा अणु
		session->port_id = -1;
		snd_soc_dapm_mixer_update_घातer(dapm, kcontrol, 0, update);
	पूर्ण

	वापस 1;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new hdmi_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(HDMI_RX) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new display_port_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(DISPLAY_PORT_RX) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new primary_mi2s_rx_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(PRIMARY_MI2S_RX) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new secondary_mi2s_rx_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SECONDARY_MI2S_RX) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quaternary_mi2s_rx_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUATERNARY_MI2S_RX) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tertiary_mi2s_rx_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(TERTIARY_MI2S_RX) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new slimbus_rx_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SLIMBUS_0_RX) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new slimbus_1_rx_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SLIMBUS_1_RX) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new slimbus_2_rx_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SLIMBUS_2_RX) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new slimbus_3_rx_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SLIMBUS_3_RX) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new slimbus_4_rx_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SLIMBUS_4_RX) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new slimbus_5_rx_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SLIMBUS_5_RX) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new slimbus_6_rx_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SLIMBUS_6_RX) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new pri_tdm_rx_0_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(PRIMARY_TDM_RX_0) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new pri_tdm_rx_1_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(PRIMARY_TDM_RX_1) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new pri_tdm_rx_2_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(PRIMARY_TDM_RX_2) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new pri_tdm_rx_3_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(PRIMARY_TDM_RX_3) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new pri_tdm_rx_4_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(PRIMARY_TDM_RX_4) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new pri_tdm_rx_5_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(PRIMARY_TDM_RX_5) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new pri_tdm_rx_6_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(PRIMARY_TDM_RX_6) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new pri_tdm_rx_7_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(PRIMARY_TDM_RX_7) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sec_tdm_rx_0_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SECONDARY_TDM_RX_0) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sec_tdm_rx_1_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SECONDARY_TDM_RX_1) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sec_tdm_rx_2_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SECONDARY_TDM_RX_2) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sec_tdm_rx_3_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SECONDARY_TDM_RX_3) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sec_tdm_rx_4_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SECONDARY_TDM_RX_4) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sec_tdm_rx_5_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SECONDARY_TDM_RX_5) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sec_tdm_rx_6_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SECONDARY_TDM_RX_6) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new sec_tdm_rx_7_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(SECONDARY_TDM_RX_7) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tert_tdm_rx_0_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(TERTIARY_TDM_RX_0) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tert_tdm_rx_1_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(TERTIARY_TDM_RX_1) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tert_tdm_rx_2_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(TERTIARY_TDM_RX_2) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tert_tdm_rx_3_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(TERTIARY_TDM_RX_3) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tert_tdm_rx_4_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(TERTIARY_TDM_RX_4) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tert_tdm_rx_5_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(TERTIARY_TDM_RX_5) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tert_tdm_rx_6_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(TERTIARY_TDM_RX_6) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new tert_tdm_rx_7_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(TERTIARY_TDM_RX_7) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quat_tdm_rx_0_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUATERNARY_TDM_RX_0) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quat_tdm_rx_1_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUATERNARY_TDM_RX_1) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quat_tdm_rx_2_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUATERNARY_TDM_RX_2) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quat_tdm_rx_3_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUATERNARY_TDM_RX_3) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quat_tdm_rx_4_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUATERNARY_TDM_RX_4) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quat_tdm_rx_5_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUATERNARY_TDM_RX_5) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quat_tdm_rx_6_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUATERNARY_TDM_RX_6) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quat_tdm_rx_7_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUATERNARY_TDM_RX_7) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quin_tdm_rx_0_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUINARY_TDM_RX_0) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quin_tdm_rx_1_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUINARY_TDM_RX_1) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quin_tdm_rx_2_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUINARY_TDM_RX_2) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quin_tdm_rx_3_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUINARY_TDM_RX_3) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quin_tdm_rx_4_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUINARY_TDM_RX_4) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quin_tdm_rx_5_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUINARY_TDM_RX_5) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quin_tdm_rx_6_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUINARY_TDM_RX_6) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new quin_tdm_rx_7_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(QUINARY_TDM_RX_7) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wsa_codec_dma_rx_0_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(WSA_CODEC_DMA_RX_0) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new wsa_codec_dma_rx_1_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(WSA_CODEC_DMA_RX_1) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rx_codec_dma_rx_0_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(RX_CODEC_DMA_RX_0) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rx_codec_dma_rx_1_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(RX_CODEC_DMA_RX_1) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rx_codec_dma_rx_2_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(RX_CODEC_DMA_RX_2) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rx_codec_dma_rx_3_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(RX_CODEC_DMA_RX_3) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rx_codec_dma_rx_4_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(RX_CODEC_DMA_RX_4) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rx_codec_dma_rx_5_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(RX_CODEC_DMA_RX_5) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rxcodec_dma_rx_6_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(RX_CODEC_DMA_RX_6) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rx_codec_dma_rx_7_mixer_controls[] = अणु
	Q6ROUTING_RX_MIXERS(RX_CODEC_DMA_RX_7) पूर्ण;


अटल स्थिर काष्ठा snd_kcontrol_new mmul1_mixer_controls[] = अणु
	Q6ROUTING_TX_MIXERS(MSM_FRONTEND_DAI_MULTIMEDIA1) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mmul2_mixer_controls[] = अणु
	Q6ROUTING_TX_MIXERS(MSM_FRONTEND_DAI_MULTIMEDIA2) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mmul3_mixer_controls[] = अणु
	Q6ROUTING_TX_MIXERS(MSM_FRONTEND_DAI_MULTIMEDIA3) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mmul4_mixer_controls[] = अणु
	Q6ROUTING_TX_MIXERS(MSM_FRONTEND_DAI_MULTIMEDIA4) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mmul5_mixer_controls[] = अणु
	Q6ROUTING_TX_MIXERS(MSM_FRONTEND_DAI_MULTIMEDIA5) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mmul6_mixer_controls[] = अणु
	Q6ROUTING_TX_MIXERS(MSM_FRONTEND_DAI_MULTIMEDIA6) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mmul7_mixer_controls[] = अणु
	Q6ROUTING_TX_MIXERS(MSM_FRONTEND_DAI_MULTIMEDIA7) पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mmul8_mixer_controls[] = अणु
	Q6ROUTING_TX_MIXERS(MSM_FRONTEND_DAI_MULTIMEDIA8) पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget msm_qdsp6_widमाला_लो[] = अणु
	/* Mixer definitions */
	SND_SOC_DAPM_MIXER("HDMI Mixer", SND_SOC_NOPM, 0, 0,
			   hdmi_mixer_controls,
			   ARRAY_SIZE(hdmi_mixer_controls)),

	SND_SOC_DAPM_MIXER("DISPLAY_PORT_RX Audio Mixer", SND_SOC_NOPM, 0, 0,
			   display_port_mixer_controls,
			   ARRAY_SIZE(display_port_mixer_controls)),

	SND_SOC_DAPM_MIXER("SLIMBUS_0_RX Audio Mixer", SND_SOC_NOPM, 0, 0,
			   slimbus_rx_mixer_controls,
			   ARRAY_SIZE(slimbus_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("SLIMBUS_1_RX Audio Mixer", SND_SOC_NOPM, 0, 0,
			   slimbus_1_rx_mixer_controls,
			   ARRAY_SIZE(slimbus_1_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("SLIMBUS_2_RX Audio Mixer", SND_SOC_NOPM, 0, 0,
			   slimbus_2_rx_mixer_controls,
			   ARRAY_SIZE(slimbus_2_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("SLIMBUS_3_RX Audio Mixer", SND_SOC_NOPM, 0, 0,
			   slimbus_3_rx_mixer_controls,
			   ARRAY_SIZE(slimbus_3_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("SLIMBUS_4_RX Audio Mixer", SND_SOC_NOPM, 0, 0,
			   slimbus_4_rx_mixer_controls,
			   ARRAY_SIZE(slimbus_4_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("SLIMBUS_5_RX Audio Mixer", SND_SOC_NOPM, 0, 0,
			   slimbus_5_rx_mixer_controls,
			    ARRAY_SIZE(slimbus_5_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("SLIMBUS_6_RX Audio Mixer", SND_SOC_NOPM, 0, 0,
			   slimbus_6_rx_mixer_controls,
			   ARRAY_SIZE(slimbus_6_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("PRI_MI2S_RX Audio Mixer", SND_SOC_NOPM, 0, 0,
			   primary_mi2s_rx_mixer_controls,
			   ARRAY_SIZE(primary_mi2s_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("SEC_MI2S_RX Audio Mixer", SND_SOC_NOPM, 0, 0,
			   secondary_mi2s_rx_mixer_controls,
			   ARRAY_SIZE(secondary_mi2s_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUAT_MI2S_RX Audio Mixer", SND_SOC_NOPM, 0, 0,
			   quaternary_mi2s_rx_mixer_controls,
			   ARRAY_SIZE(quaternary_mi2s_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("TERT_MI2S_RX Audio Mixer", SND_SOC_NOPM, 0, 0,
			   tertiary_mi2s_rx_mixer_controls,
			   ARRAY_SIZE(tertiary_mi2s_rx_mixer_controls)),
	SND_SOC_DAPM_MIXER("PRIMARY_TDM_RX_0 Audio Mixer", SND_SOC_NOPM, 0, 0,
				pri_tdm_rx_0_mixer_controls,
				ARRAY_SIZE(pri_tdm_rx_0_mixer_controls)),
	SND_SOC_DAPM_MIXER("PRIMARY_TDM_RX_1 Audio Mixer", SND_SOC_NOPM, 0, 0,
				pri_tdm_rx_1_mixer_controls,
				ARRAY_SIZE(pri_tdm_rx_1_mixer_controls)),
	SND_SOC_DAPM_MIXER("PRIMARY_TDM_RX_2 Audio Mixer", SND_SOC_NOPM, 0, 0,
				pri_tdm_rx_2_mixer_controls,
				ARRAY_SIZE(pri_tdm_rx_2_mixer_controls)),
	SND_SOC_DAPM_MIXER("PRIMARY_TDM_RX_3 Audio Mixer", SND_SOC_NOPM, 0, 0,
				pri_tdm_rx_3_mixer_controls,
				ARRAY_SIZE(pri_tdm_rx_3_mixer_controls)),
	SND_SOC_DAPM_MIXER("PRIMARY_TDM_RX_4 Audio Mixer", SND_SOC_NOPM, 0, 0,
				pri_tdm_rx_4_mixer_controls,
				ARRAY_SIZE(pri_tdm_rx_4_mixer_controls)),
	SND_SOC_DAPM_MIXER("PRIMARY_TDM_RX_5 Audio Mixer", SND_SOC_NOPM, 0, 0,
				pri_tdm_rx_5_mixer_controls,
				ARRAY_SIZE(pri_tdm_rx_5_mixer_controls)),
	SND_SOC_DAPM_MIXER("PRIMARY_TDM_RX_6 Audio Mixer", SND_SOC_NOPM, 0, 0,
				pri_tdm_rx_6_mixer_controls,
				ARRAY_SIZE(pri_tdm_rx_6_mixer_controls)),
	SND_SOC_DAPM_MIXER("PRIMARY_TDM_RX_7 Audio Mixer", SND_SOC_NOPM, 0, 0,
				pri_tdm_rx_7_mixer_controls,
				ARRAY_SIZE(pri_tdm_rx_7_mixer_controls)),

	SND_SOC_DAPM_MIXER("SEC_TDM_RX_0 Audio Mixer", SND_SOC_NOPM, 0, 0,
				sec_tdm_rx_0_mixer_controls,
				ARRAY_SIZE(sec_tdm_rx_0_mixer_controls)),
	SND_SOC_DAPM_MIXER("SEC_TDM_RX_1 Audio Mixer", SND_SOC_NOPM, 0, 0,
				sec_tdm_rx_1_mixer_controls,
				ARRAY_SIZE(sec_tdm_rx_1_mixer_controls)),
	SND_SOC_DAPM_MIXER("SEC_TDM_RX_2 Audio Mixer", SND_SOC_NOPM, 0, 0,
				sec_tdm_rx_2_mixer_controls,
				ARRAY_SIZE(sec_tdm_rx_2_mixer_controls)),
	SND_SOC_DAPM_MIXER("SEC_TDM_RX_3 Audio Mixer", SND_SOC_NOPM, 0, 0,
				sec_tdm_rx_3_mixer_controls,
				ARRAY_SIZE(sec_tdm_rx_3_mixer_controls)),
	SND_SOC_DAPM_MIXER("SEC_TDM_RX_4 Audio Mixer", SND_SOC_NOPM, 0, 0,
				sec_tdm_rx_4_mixer_controls,
				ARRAY_SIZE(sec_tdm_rx_4_mixer_controls)),
	SND_SOC_DAPM_MIXER("SEC_TDM_RX_5 Audio Mixer", SND_SOC_NOPM, 0, 0,
				sec_tdm_rx_5_mixer_controls,
				ARRAY_SIZE(sec_tdm_rx_5_mixer_controls)),
	SND_SOC_DAPM_MIXER("SEC_TDM_RX_6 Audio Mixer", SND_SOC_NOPM, 0, 0,
				sec_tdm_rx_6_mixer_controls,
				ARRAY_SIZE(sec_tdm_rx_6_mixer_controls)),
	SND_SOC_DAPM_MIXER("SEC_TDM_RX_7 Audio Mixer", SND_SOC_NOPM, 0, 0,
				sec_tdm_rx_7_mixer_controls,
				ARRAY_SIZE(sec_tdm_rx_7_mixer_controls)),

	SND_SOC_DAPM_MIXER("TERT_TDM_RX_0 Audio Mixer", SND_SOC_NOPM, 0, 0,
				tert_tdm_rx_0_mixer_controls,
				ARRAY_SIZE(tert_tdm_rx_0_mixer_controls)),
	SND_SOC_DAPM_MIXER("TERT_TDM_RX_1 Audio Mixer", SND_SOC_NOPM, 0, 0,
				tert_tdm_rx_1_mixer_controls,
				ARRAY_SIZE(tert_tdm_rx_1_mixer_controls)),
	SND_SOC_DAPM_MIXER("TERT_TDM_RX_2 Audio Mixer", SND_SOC_NOPM, 0, 0,
				tert_tdm_rx_2_mixer_controls,
				ARRAY_SIZE(tert_tdm_rx_2_mixer_controls)),
	SND_SOC_DAPM_MIXER("TERT_TDM_RX_3 Audio Mixer", SND_SOC_NOPM, 0, 0,
				tert_tdm_rx_3_mixer_controls,
				ARRAY_SIZE(tert_tdm_rx_3_mixer_controls)),
	SND_SOC_DAPM_MIXER("TERT_TDM_RX_4 Audio Mixer", SND_SOC_NOPM, 0, 0,
				tert_tdm_rx_4_mixer_controls,
				ARRAY_SIZE(tert_tdm_rx_4_mixer_controls)),
	SND_SOC_DAPM_MIXER("TERT_TDM_RX_5 Audio Mixer", SND_SOC_NOPM, 0, 0,
				tert_tdm_rx_5_mixer_controls,
				ARRAY_SIZE(tert_tdm_rx_5_mixer_controls)),
	SND_SOC_DAPM_MIXER("TERT_TDM_RX_6 Audio Mixer", SND_SOC_NOPM, 0, 0,
				tert_tdm_rx_6_mixer_controls,
				ARRAY_SIZE(tert_tdm_rx_6_mixer_controls)),
	SND_SOC_DAPM_MIXER("TERT_TDM_RX_7 Audio Mixer", SND_SOC_NOPM, 0, 0,
				tert_tdm_rx_7_mixer_controls,
				ARRAY_SIZE(tert_tdm_rx_7_mixer_controls)),

	SND_SOC_DAPM_MIXER("QUAT_TDM_RX_0 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quat_tdm_rx_0_mixer_controls,
				ARRAY_SIZE(quat_tdm_rx_0_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUAT_TDM_RX_1 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quat_tdm_rx_1_mixer_controls,
				ARRAY_SIZE(quat_tdm_rx_1_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUAT_TDM_RX_2 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quat_tdm_rx_2_mixer_controls,
				ARRAY_SIZE(quat_tdm_rx_2_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUAT_TDM_RX_3 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quat_tdm_rx_3_mixer_controls,
				ARRAY_SIZE(quat_tdm_rx_3_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUAT_TDM_RX_4 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quat_tdm_rx_4_mixer_controls,
				ARRAY_SIZE(quat_tdm_rx_4_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUAT_TDM_RX_5 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quat_tdm_rx_5_mixer_controls,
				ARRAY_SIZE(quat_tdm_rx_5_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUAT_TDM_RX_6 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quat_tdm_rx_6_mixer_controls,
				ARRAY_SIZE(quat_tdm_rx_6_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUAT_TDM_RX_7 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quat_tdm_rx_7_mixer_controls,
				ARRAY_SIZE(quat_tdm_rx_7_mixer_controls)),

	SND_SOC_DAPM_MIXER("QUIN_TDM_RX_0 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quin_tdm_rx_0_mixer_controls,
				ARRAY_SIZE(quin_tdm_rx_0_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUIN_TDM_RX_1 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quin_tdm_rx_1_mixer_controls,
				ARRAY_SIZE(quin_tdm_rx_1_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUIN_TDM_RX_2 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quin_tdm_rx_2_mixer_controls,
				ARRAY_SIZE(quin_tdm_rx_2_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUIN_TDM_RX_3 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quin_tdm_rx_3_mixer_controls,
				ARRAY_SIZE(quin_tdm_rx_3_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUIN_TDM_RX_4 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quin_tdm_rx_4_mixer_controls,
				ARRAY_SIZE(quin_tdm_rx_4_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUIN_TDM_RX_5 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quin_tdm_rx_5_mixer_controls,
				ARRAY_SIZE(quin_tdm_rx_5_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUIN_TDM_RX_6 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quin_tdm_rx_6_mixer_controls,
				ARRAY_SIZE(quin_tdm_rx_6_mixer_controls)),
	SND_SOC_DAPM_MIXER("QUIN_TDM_RX_7 Audio Mixer", SND_SOC_NOPM, 0, 0,
				quin_tdm_rx_7_mixer_controls,
				ARRAY_SIZE(quin_tdm_rx_7_mixer_controls)),

	SND_SOC_DAPM_MIXER("WSA_CODEC_DMA_RX_0 Audio Mixer", SND_SOC_NOPM, 0, 0,
		wsa_codec_dma_rx_0_mixer_controls,
		ARRAY_SIZE(wsa_codec_dma_rx_0_mixer_controls)),
	SND_SOC_DAPM_MIXER("WSA_CODEC_DMA_RX_1 Audio Mixer", SND_SOC_NOPM, 0, 0,
		wsa_codec_dma_rx_1_mixer_controls,
		ARRAY_SIZE(wsa_codec_dma_rx_1_mixer_controls)),
	SND_SOC_DAPM_MIXER("RX_CODEC_DMA_RX_0 Audio Mixer", SND_SOC_NOPM, 0, 0,
		rx_codec_dma_rx_0_mixer_controls,
		ARRAY_SIZE(rx_codec_dma_rx_0_mixer_controls)),
	SND_SOC_DAPM_MIXER("RX_CODEC_DMA_RX_1 Audio Mixer", SND_SOC_NOPM, 0, 0,
		rx_codec_dma_rx_1_mixer_controls,
		ARRAY_SIZE(rx_codec_dma_rx_1_mixer_controls)),
	SND_SOC_DAPM_MIXER("RX_CODEC_DMA_RX_2 Audio Mixer", SND_SOC_NOPM, 0, 0,
		rx_codec_dma_rx_2_mixer_controls,
		ARRAY_SIZE(rx_codec_dma_rx_2_mixer_controls)),
	SND_SOC_DAPM_MIXER("RX_CODEC_DMA_RX_3 Audio Mixer", SND_SOC_NOPM, 0, 0,
		rx_codec_dma_rx_3_mixer_controls,
		ARRAY_SIZE(rx_codec_dma_rx_3_mixer_controls)),
	SND_SOC_DAPM_MIXER("RX_CODEC_DMA_RX_4 Audio Mixer", SND_SOC_NOPM, 0, 0,
		rx_codec_dma_rx_4_mixer_controls,
		ARRAY_SIZE(rx_codec_dma_rx_4_mixer_controls)),
	SND_SOC_DAPM_MIXER("RX_CODEC_DMA_RX_5 Audio Mixer", SND_SOC_NOPM, 0, 0,
		rx_codec_dma_rx_5_mixer_controls,
		ARRAY_SIZE(rx_codec_dma_rx_5_mixer_controls)),
	SND_SOC_DAPM_MIXER("RX_CODEC_DMA_RX_6 Audio Mixer", SND_SOC_NOPM, 0, 0,
		rxcodec_dma_rx_6_mixer_controls,
		ARRAY_SIZE(rxcodec_dma_rx_6_mixer_controls)),
	SND_SOC_DAPM_MIXER("RX_CODEC_DMA_RX_7 Audio Mixer", SND_SOC_NOPM, 0, 0,
		rx_codec_dma_rx_7_mixer_controls,
		ARRAY_SIZE(rx_codec_dma_rx_7_mixer_controls)),
	SND_SOC_DAPM_MIXER("MultiMedia1 Mixer", SND_SOC_NOPM, 0, 0,
		mmul1_mixer_controls, ARRAY_SIZE(mmul1_mixer_controls)),
	SND_SOC_DAPM_MIXER("MultiMedia2 Mixer", SND_SOC_NOPM, 0, 0,
		mmul2_mixer_controls, ARRAY_SIZE(mmul2_mixer_controls)),
	SND_SOC_DAPM_MIXER("MultiMedia3 Mixer", SND_SOC_NOPM, 0, 0,
		mmul3_mixer_controls, ARRAY_SIZE(mmul3_mixer_controls)),
	SND_SOC_DAPM_MIXER("MultiMedia4 Mixer", SND_SOC_NOPM, 0, 0,
		mmul4_mixer_controls, ARRAY_SIZE(mmul4_mixer_controls)),
	SND_SOC_DAPM_MIXER("MultiMedia5 Mixer", SND_SOC_NOPM, 0, 0,
		mmul5_mixer_controls, ARRAY_SIZE(mmul5_mixer_controls)),
	SND_SOC_DAPM_MIXER("MultiMedia6 Mixer", SND_SOC_NOPM, 0, 0,
		mmul6_mixer_controls, ARRAY_SIZE(mmul6_mixer_controls)),
	SND_SOC_DAPM_MIXER("MultiMedia7 Mixer", SND_SOC_NOPM, 0, 0,
		mmul7_mixer_controls, ARRAY_SIZE(mmul7_mixer_controls)),
	SND_SOC_DAPM_MIXER("MultiMedia8 Mixer", SND_SOC_NOPM, 0, 0,
		mmul8_mixer_controls, ARRAY_SIZE(mmul8_mixer_controls)),

पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route पूर्णांकercon[] = अणु
	Q6ROUTING_RX_DAPM_ROUTE("HDMI Mixer", "HDMI_RX"),
	Q6ROUTING_RX_DAPM_ROUTE("DISPLAY_PORT_RX Audio Mixer",
				"DISPLAY_PORT_RX"),
	Q6ROUTING_RX_DAPM_ROUTE("SLIMBUS_0_RX Audio Mixer", "SLIMBUS_0_RX"),
	Q6ROUTING_RX_DAPM_ROUTE("SLIMBUS_1_RX Audio Mixer", "SLIMBUS_1_RX"),
	Q6ROUTING_RX_DAPM_ROUTE("SLIMBUS_2_RX Audio Mixer", "SLIMBUS_2_RX"),
	Q6ROUTING_RX_DAPM_ROUTE("SLIMBUS_3_RX Audio Mixer", "SLIMBUS_3_RX"),
	Q6ROUTING_RX_DAPM_ROUTE("SLIMBUS_4_RX Audio Mixer", "SLIMBUS_4_RX"),
	Q6ROUTING_RX_DAPM_ROUTE("SLIMBUS_5_RX Audio Mixer", "SLIMBUS_5_RX"),
	Q6ROUTING_RX_DAPM_ROUTE("SLIMBUS_6_RX Audio Mixer", "SLIMBUS_6_RX"),
	Q6ROUTING_RX_DAPM_ROUTE("QUAT_MI2S_RX Audio Mixer", "QUAT_MI2S_RX"),
	Q6ROUTING_RX_DAPM_ROUTE("TERT_MI2S_RX Audio Mixer", "TERT_MI2S_RX"),
	Q6ROUTING_RX_DAPM_ROUTE("SEC_MI2S_RX Audio Mixer", "SEC_MI2S_RX"),
	Q6ROUTING_RX_DAPM_ROUTE("PRI_MI2S_RX Audio Mixer", "PRI_MI2S_RX"),
	Q6ROUTING_RX_DAPM_ROUTE("PRIMARY_TDM_RX_0 Audio Mixer",
				"PRIMARY_TDM_RX_0"),
	Q6ROUTING_RX_DAPM_ROUTE("PRIMARY_TDM_RX_1 Audio Mixer",
				"PRIMARY_TDM_RX_1"),
	Q6ROUTING_RX_DAPM_ROUTE("PRIMARY_TDM_RX_2 Audio Mixer",
				"PRIMARY_TDM_RX_2"),
	Q6ROUTING_RX_DAPM_ROUTE("PRIMARY_TDM_RX_3 Audio Mixer",
				"PRIMARY_TDM_RX_3"),
	Q6ROUTING_RX_DAPM_ROUTE("PRIMARY_TDM_RX_4 Audio Mixer",
				"PRIMARY_TDM_RX_4"),
	Q6ROUTING_RX_DAPM_ROUTE("PRIMARY_TDM_RX_5 Audio Mixer",
				"PRIMARY_TDM_RX_5"),
	Q6ROUTING_RX_DAPM_ROUTE("PRIMARY_TDM_RX_6 Audio Mixer",
				"PRIMARY_TDM_RX_6"),
	Q6ROUTING_RX_DAPM_ROUTE("PRIMARY_TDM_RX_7 Audio Mixer",
				"PRIMARY_TDM_RX_7"),
	Q6ROUTING_RX_DAPM_ROUTE("SEC_TDM_RX_0 Audio Mixer", "SEC_TDM_RX_0"),
	Q6ROUTING_RX_DAPM_ROUTE("SEC_TDM_RX_1 Audio Mixer", "SEC_TDM_RX_1"),
	Q6ROUTING_RX_DAPM_ROUTE("SEC_TDM_RX_2 Audio Mixer", "SEC_TDM_RX_2"),
	Q6ROUTING_RX_DAPM_ROUTE("SEC_TDM_RX_3 Audio Mixer", "SEC_TDM_RX_3"),
	Q6ROUTING_RX_DAPM_ROUTE("SEC_TDM_RX_4 Audio Mixer", "SEC_TDM_RX_4"),
	Q6ROUTING_RX_DAPM_ROUTE("SEC_TDM_RX_5 Audio Mixer", "SEC_TDM_RX_5"),
	Q6ROUTING_RX_DAPM_ROUTE("SEC_TDM_RX_6 Audio Mixer", "SEC_TDM_RX_6"),
	Q6ROUTING_RX_DAPM_ROUTE("SEC_TDM_RX_7 Audio Mixer", "SEC_TDM_RX_7"),
	Q6ROUTING_RX_DAPM_ROUTE("TERT_TDM_RX_0 Audio Mixer", "TERT_TDM_RX_0"),
	Q6ROUTING_RX_DAPM_ROUTE("TERT_TDM_RX_1 Audio Mixer", "TERT_TDM_RX_1"),
	Q6ROUTING_RX_DAPM_ROUTE("TERT_TDM_RX_2 Audio Mixer", "TERT_TDM_RX_2"),
	Q6ROUTING_RX_DAPM_ROUTE("TERT_TDM_RX_3 Audio Mixer", "TERT_TDM_RX_3"),
	Q6ROUTING_RX_DAPM_ROUTE("TERT_TDM_RX_4 Audio Mixer", "TERT_TDM_RX_4"),
	Q6ROUTING_RX_DAPM_ROUTE("TERT_TDM_RX_5 Audio Mixer", "TERT_TDM_RX_5"),
	Q6ROUTING_RX_DAPM_ROUTE("TERT_TDM_RX_6 Audio Mixer", "TERT_TDM_RX_6"),
	Q6ROUTING_RX_DAPM_ROUTE("TERT_TDM_RX_7 Audio Mixer", "TERT_TDM_RX_7"),
	Q6ROUTING_RX_DAPM_ROUTE("QUAT_TDM_RX_0 Audio Mixer", "QUAT_TDM_RX_0"),
	Q6ROUTING_RX_DAPM_ROUTE("QUAT_TDM_RX_1 Audio Mixer", "QUAT_TDM_RX_1"),
	Q6ROUTING_RX_DAPM_ROUTE("QUAT_TDM_RX_2 Audio Mixer", "QUAT_TDM_RX_2"),
	Q6ROUTING_RX_DAPM_ROUTE("QUAT_TDM_RX_3 Audio Mixer", "QUAT_TDM_RX_3"),
	Q6ROUTING_RX_DAPM_ROUTE("QUAT_TDM_RX_4 Audio Mixer", "QUAT_TDM_RX_4"),
	Q6ROUTING_RX_DAPM_ROUTE("QUAT_TDM_RX_5 Audio Mixer", "QUAT_TDM_RX_5"),
	Q6ROUTING_RX_DAPM_ROUTE("QUAT_TDM_RX_6 Audio Mixer", "QUAT_TDM_RX_6"),
	Q6ROUTING_RX_DAPM_ROUTE("QUAT_TDM_RX_7 Audio Mixer", "QUAT_TDM_RX_7"),
	Q6ROUTING_RX_DAPM_ROUTE("QUIN_TDM_RX_0 Audio Mixer", "QUIN_TDM_RX_0"),
	Q6ROUTING_RX_DAPM_ROUTE("QUIN_TDM_RX_1 Audio Mixer", "QUIN_TDM_RX_1"),
	Q6ROUTING_RX_DAPM_ROUTE("QUIN_TDM_RX_2 Audio Mixer", "QUIN_TDM_RX_2"),
	Q6ROUTING_RX_DAPM_ROUTE("QUIN_TDM_RX_3 Audio Mixer", "QUIN_TDM_RX_3"),
	Q6ROUTING_RX_DAPM_ROUTE("QUIN_TDM_RX_4 Audio Mixer", "QUIN_TDM_RX_4"),
	Q6ROUTING_RX_DAPM_ROUTE("QUIN_TDM_RX_5 Audio Mixer", "QUIN_TDM_RX_5"),
	Q6ROUTING_RX_DAPM_ROUTE("QUIN_TDM_RX_6 Audio Mixer", "QUIN_TDM_RX_6"),
	Q6ROUTING_RX_DAPM_ROUTE("QUIN_TDM_RX_7 Audio Mixer", "QUIN_TDM_RX_7"),
	Q6ROUTING_RX_DAPM_ROUTE("WSA_CODEC_DMA_RX_0 Audio Mixer", "WSA_CODEC_DMA_RX_0"),
	Q6ROUTING_RX_DAPM_ROUTE("WSA_CODEC_DMA_RX_1 Audio Mixer", "WSA_CODEC_DMA_RX_1"),
	Q6ROUTING_RX_DAPM_ROUTE("RX_CODEC_DMA_RX_0 Audio Mixer", "RX_CODEC_DMA_RX_0"),
	Q6ROUTING_RX_DAPM_ROUTE("RX_CODEC_DMA_RX_1 Audio Mixer", "RX_CODEC_DMA_RX_1"),
	Q6ROUTING_RX_DAPM_ROUTE("RX_CODEC_DMA_RX_2 Audio Mixer", "RX_CODEC_DMA_RX_2"),
	Q6ROUTING_RX_DAPM_ROUTE("RX_CODEC_DMA_RX_3 Audio Mixer", "RX_CODEC_DMA_RX_3"),
	Q6ROUTING_RX_DAPM_ROUTE("RX_CODEC_DMA_RX_4 Audio Mixer", "RX_CODEC_DMA_RX_4"),
	Q6ROUTING_RX_DAPM_ROUTE("RX_CODEC_DMA_RX_5 Audio Mixer", "RX_CODEC_DMA_RX_5"),
	Q6ROUTING_RX_DAPM_ROUTE("RX_CODEC_DMA_RX_6 Audio Mixer", "RX_CODEC_DMA_RX_6"),
	Q6ROUTING_RX_DAPM_ROUTE("RX_CODEC_DMA_RX_7 Audio Mixer", "RX_CODEC_DMA_RX_7"),
	Q6ROUTING_TX_DAPM_ROUTE("MultiMedia1 Mixer"),
	Q6ROUTING_TX_DAPM_ROUTE("MultiMedia2 Mixer"),
	Q6ROUTING_TX_DAPM_ROUTE("MultiMedia3 Mixer"),
	Q6ROUTING_TX_DAPM_ROUTE("MultiMedia4 Mixer"),
	Q6ROUTING_TX_DAPM_ROUTE("MultiMedia5 Mixer"),
	Q6ROUTING_TX_DAPM_ROUTE("MultiMedia6 Mixer"),
	Q6ROUTING_TX_DAPM_ROUTE("MultiMedia7 Mixer"),
	Q6ROUTING_TX_DAPM_ROUTE("MultiMedia8 Mixer"),

	अणु"MM_UL1", शून्य, "MultiMedia1 Mixer"पूर्ण,
	अणु"MM_UL2", शून्य, "MultiMedia2 Mixer"पूर्ण,
	अणु"MM_UL3", शून्य, "MultiMedia3 Mixer"पूर्ण,
	अणु"MM_UL4", शून्य, "MultiMedia4 Mixer"पूर्ण,
	अणु"MM_UL5", शून्य, "MultiMedia5 Mixer"पूर्ण,
	अणु"MM_UL6", शून्य, "MultiMedia6 Mixer"पूर्ण,
	अणु"MM_UL7", शून्य, "MultiMedia7 Mixer"पूर्ण,
	अणु"MM_UL8", शून्य, "MultiMedia8 Mixer"पूर्ण,
पूर्ण;

अटल पूर्णांक routing_hw_params(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा msm_routing_data *data = dev_get_drvdata(component->dev);
	अचिन्हित पूर्णांक be_id = asoc_rtd_to_cpu(rtd, 0)->id;
	काष्ठा session_data *session;
	पूर्णांक path_type;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		path_type = ADM_PATH_PLAYBACK;
	अन्यथा
		path_type = ADM_PATH_LIVE_REC;

	अगर (be_id >= AFE_MAX_PORTS)
		वापस -EINVAL;

	session = &data->port_data[be_id];

	mutex_lock(&data->lock);

	session->path_type = path_type;
	session->sample_rate = params_rate(params);
	session->channels = params_channels(params);

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S16_LE:
			session->bits_per_sample = 16;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S24_LE:
			session->bits_per_sample = 24;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	mutex_unlock(&data->lock);
	वापस 0;
पूर्ण

अटल पूर्णांक msm_routing_probe(काष्ठा snd_soc_component *c)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_SESSIONS; i++) अणु
		routing_data->sessions[i].port_id = -1;
		routing_data->sessions[i].fedai_id = -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक q6routing_reg_पढ़ो(काष्ठा snd_soc_component *component,
				       अचिन्हित पूर्णांक reg)
अणु
	/* शेष value */
	वापस 0;
पूर्ण

अटल पूर्णांक q6routing_reg_ग_लिखो(काष्ठा snd_soc_component *component,
			       अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक val)
अणु
	/* dummy */
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver msm_soc_routing_component = अणु
	.probe = msm_routing_probe,
	.name = DRV_NAME,
	.hw_params = routing_hw_params,
	.dapm_widमाला_लो = msm_qdsp6_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(msm_qdsp6_widमाला_लो),
	.dapm_routes = पूर्णांकercon,
	.num_dapm_routes = ARRAY_SIZE(पूर्णांकercon),
	.पढ़ो = q6routing_reg_पढ़ो,
	.ग_लिखो = q6routing_reg_ग_लिखो,
पूर्ण;

अटल पूर्णांक q6pcm_routing_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;

	routing_data = kzalloc(माप(*routing_data), GFP_KERNEL);
	अगर (!routing_data)
		वापस -ENOMEM;

	routing_data->dev = dev;

	mutex_init(&routing_data->lock);
	dev_set_drvdata(dev, routing_data);

	वापस devm_snd_soc_रेजिस्टर_component(dev, &msm_soc_routing_component,
					  शून्य, 0);
पूर्ण

अटल पूर्णांक q6pcm_routing_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	kमुक्त(routing_data);
	routing_data = शून्य;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id q6pcm_routing_device_id[] = अणु
	अणु .compatible = "qcom,q6adm-routing" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, q6pcm_routing_device_id);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver q6pcm_routing_platक्रमm_driver = अणु
	.driver = अणु
		.name = "q6routing",
		.of_match_table = of_match_ptr(q6pcm_routing_device_id),
	पूर्ण,
	.probe = q6pcm_routing_probe,
	.हटाओ = q6pcm_routing_हटाओ,
पूर्ण;
module_platक्रमm_driver(q6pcm_routing_platक्रमm_driver);

MODULE_DESCRIPTION("Q6 Routing platform");
MODULE_LICENSE("GPL v2");
