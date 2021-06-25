<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (c) 2011-2017, The Linux Foundation. All rights reserved.
// Copyright (c) 2018, Linaro Limited

#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/रुको.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/sched.h>
#समावेश <linux/module.h>
#समावेश <linux/kref.h>
#समावेश <linux/of.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/delay.h>
#समावेश <linux/soc/qcom/apr.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश "q6dsp-errno.h"
#समावेश "q6core.h"
#समावेश "q6afe.h"

/* AFE CMDs */
#घोषणा AFE_PORT_CMD_DEVICE_START	0x000100E5
#घोषणा AFE_PORT_CMD_DEVICE_STOP	0x000100E6
#घोषणा AFE_PORT_CMD_SET_PARAM_V2	0x000100EF
#घोषणा AFE_SVC_CMD_SET_PARAM		0x000100f3
#घोषणा AFE_PORT_CMDRSP_GET_PARAM_V2	0x00010106
#घोषणा AFE_PARAM_ID_HDMI_CONFIG	0x00010210
#घोषणा AFE_MODULE_AUDIO_DEV_INTERFACE	0x0001020C
#घोषणा AFE_MODULE_TDM			0x0001028A

#घोषणा AFE_PARAM_ID_CDC_SLIMBUS_SLAVE_CFG 0x00010235

#घोषणा AFE_PARAM_ID_LPAIF_CLK_CONFIG	0x00010238
#घोषणा AFE_PARAM_ID_INT_DIGITAL_CDC_CLK_CONFIG	0x00010239

#घोषणा AFE_PARAM_ID_SLIMBUS_CONFIG    0x00010212
#घोषणा AFE_PARAM_ID_I2S_CONFIG	0x0001020D
#घोषणा AFE_PARAM_ID_TDM_CONFIG	0x0001029D
#घोषणा AFE_PARAM_ID_PORT_SLOT_MAPPING_CONFIG	0x00010297
#घोषणा AFE_PARAM_ID_CODEC_DMA_CONFIG	0x000102B8
#घोषणा AFE_CMD_REMOTE_LPASS_CORE_HW_VOTE_REQUEST	0x000100f4
#घोषणा AFE_CMD_RSP_REMOTE_LPASS_CORE_HW_VOTE_REQUEST   0x000100f5
#घोषणा AFE_CMD_REMOTE_LPASS_CORE_HW_DEVOTE_REQUEST	0x000100f6

/* I2S config specअगरic */
#घोषणा AFE_API_VERSION_I2S_CONFIG	0x1
#घोषणा AFE_PORT_I2S_SD0		0x1
#घोषणा AFE_PORT_I2S_SD1		0x2
#घोषणा AFE_PORT_I2S_SD2		0x3
#घोषणा AFE_PORT_I2S_SD3		0x4
#घोषणा AFE_PORT_I2S_SD0_MASK		BIT(0x0)
#घोषणा AFE_PORT_I2S_SD1_MASK		BIT(0x1)
#घोषणा AFE_PORT_I2S_SD2_MASK		BIT(0x2)
#घोषणा AFE_PORT_I2S_SD3_MASK		BIT(0x3)
#घोषणा AFE_PORT_I2S_SD0_1_MASK		GENMASK(1, 0)
#घोषणा AFE_PORT_I2S_SD2_3_MASK		GENMASK(3, 2)
#घोषणा AFE_PORT_I2S_SD0_1_2_MASK	GENMASK(2, 0)
#घोषणा AFE_PORT_I2S_SD0_1_2_3_MASK	GENMASK(3, 0)
#घोषणा AFE_PORT_I2S_QUAD01		0x5
#घोषणा AFE_PORT_I2S_QUAD23		0x6
#घोषणा AFE_PORT_I2S_6CHS		0x7
#घोषणा AFE_PORT_I2S_8CHS		0x8
#घोषणा AFE_PORT_I2S_MONO		0x0
#घोषणा AFE_PORT_I2S_STEREO		0x1
#घोषणा AFE_PORT_CONFIG_I2S_WS_SRC_EXTERNAL	0x0
#घोषणा AFE_PORT_CONFIG_I2S_WS_SRC_INTERNAL	0x1
#घोषणा AFE_LINEAR_PCM_DATA				0x0


/* Port IDs */
#घोषणा AFE_API_VERSION_HDMI_CONFIG	0x1
#घोषणा AFE_PORT_ID_MULTICHAN_HDMI_RX	0x100E
#घोषणा AFE_PORT_ID_HDMI_OVER_DP_RX	0x6020

#घोषणा AFE_API_VERSION_SLIMBUS_CONFIG 0x1
/* Clock set API version */
#घोषणा AFE_API_VERSION_CLOCK_SET 1
#घोषणा Q6AFE_LPASS_CLK_CONFIG_API_VERSION	0x1
#घोषणा AFE_MODULE_CLOCK_SET		0x0001028F
#घोषणा AFE_PARAM_ID_CLOCK_SET		0x00010290

/* SLIMbus Rx port on channel 0. */
#घोषणा AFE_PORT_ID_SLIMBUS_MULTI_CHAN_0_RX      0x4000
/* SLIMbus Tx port on channel 0. */
#घोषणा AFE_PORT_ID_SLIMBUS_MULTI_CHAN_0_TX      0x4001
/* SLIMbus Rx port on channel 1. */
#घोषणा AFE_PORT_ID_SLIMBUS_MULTI_CHAN_1_RX      0x4002
/* SLIMbus Tx port on channel 1. */
#घोषणा AFE_PORT_ID_SLIMBUS_MULTI_CHAN_1_TX      0x4003
/* SLIMbus Rx port on channel 2. */
#घोषणा AFE_PORT_ID_SLIMBUS_MULTI_CHAN_2_RX      0x4004
/* SLIMbus Tx port on channel 2. */
#घोषणा AFE_PORT_ID_SLIMBUS_MULTI_CHAN_2_TX      0x4005
/* SLIMbus Rx port on channel 3. */
#घोषणा AFE_PORT_ID_SLIMBUS_MULTI_CHAN_3_RX      0x4006
/* SLIMbus Tx port on channel 3. */
#घोषणा AFE_PORT_ID_SLIMBUS_MULTI_CHAN_3_TX      0x4007
/* SLIMbus Rx port on channel 4. */
#घोषणा AFE_PORT_ID_SLIMBUS_MULTI_CHAN_4_RX      0x4008
/* SLIMbus Tx port on channel 4. */
#घोषणा AFE_PORT_ID_SLIMBUS_MULTI_CHAN_4_TX      0x4009
/* SLIMbus Rx port on channel 5. */
#घोषणा AFE_PORT_ID_SLIMBUS_MULTI_CHAN_5_RX      0x400a
/* SLIMbus Tx port on channel 5. */
#घोषणा AFE_PORT_ID_SLIMBUS_MULTI_CHAN_5_TX      0x400b
/* SLIMbus Rx port on channel 6. */
#घोषणा AFE_PORT_ID_SLIMBUS_MULTI_CHAN_6_RX      0x400c
/* SLIMbus Tx port on channel 6. */
#घोषणा AFE_PORT_ID_SLIMBUS_MULTI_CHAN_6_TX      0x400d
#घोषणा AFE_PORT_ID_PRIMARY_MI2S_RX         0x1000
#घोषणा AFE_PORT_ID_PRIMARY_MI2S_TX         0x1001
#घोषणा AFE_PORT_ID_SECONDARY_MI2S_RX       0x1002
#घोषणा AFE_PORT_ID_SECONDARY_MI2S_TX       0x1003
#घोषणा AFE_PORT_ID_TERTIARY_MI2S_RX        0x1004
#घोषणा AFE_PORT_ID_TERTIARY_MI2S_TX        0x1005
#घोषणा AFE_PORT_ID_QUATERNARY_MI2S_RX      0x1006
#घोषणा AFE_PORT_ID_QUATERNARY_MI2S_TX      0x1007

/* Start of the range of port IDs क्रम TDM devices. */
#घोषणा AFE_PORT_ID_TDM_PORT_RANGE_START	0x9000

/* End of the range of port IDs क्रम TDM devices. */
#घोषणा AFE_PORT_ID_TDM_PORT_RANGE_END \
	(AFE_PORT_ID_TDM_PORT_RANGE_START+0x50-1)

/* Size of the range of port IDs क्रम TDM ports. */
#घोषणा AFE_PORT_ID_TDM_PORT_RANGE_SIZE \
	(AFE_PORT_ID_TDM_PORT_RANGE_END - \
	AFE_PORT_ID_TDM_PORT_RANGE_START+1)

#घोषणा AFE_PORT_ID_PRIMARY_TDM_RX \
	(AFE_PORT_ID_TDM_PORT_RANGE_START + 0x00)
#घोषणा AFE_PORT_ID_PRIMARY_TDM_RX_1 \
	(AFE_PORT_ID_PRIMARY_TDM_RX + 0x02)
#घोषणा AFE_PORT_ID_PRIMARY_TDM_RX_2 \
	(AFE_PORT_ID_PRIMARY_TDM_RX + 0x04)
#घोषणा AFE_PORT_ID_PRIMARY_TDM_RX_3 \
	(AFE_PORT_ID_PRIMARY_TDM_RX + 0x06)
#घोषणा AFE_PORT_ID_PRIMARY_TDM_RX_4 \
	(AFE_PORT_ID_PRIMARY_TDM_RX + 0x08)
#घोषणा AFE_PORT_ID_PRIMARY_TDM_RX_5 \
	(AFE_PORT_ID_PRIMARY_TDM_RX + 0x0A)
#घोषणा AFE_PORT_ID_PRIMARY_TDM_RX_6 \
	(AFE_PORT_ID_PRIMARY_TDM_RX + 0x0C)
#घोषणा AFE_PORT_ID_PRIMARY_TDM_RX_7 \
	(AFE_PORT_ID_PRIMARY_TDM_RX + 0x0E)

#घोषणा AFE_PORT_ID_PRIMARY_TDM_TX \
	(AFE_PORT_ID_TDM_PORT_RANGE_START + 0x01)
#घोषणा AFE_PORT_ID_PRIMARY_TDM_TX_1 \
	(AFE_PORT_ID_PRIMARY_TDM_TX + 0x02)
#घोषणा AFE_PORT_ID_PRIMARY_TDM_TX_2 \
	(AFE_PORT_ID_PRIMARY_TDM_TX + 0x04)
#घोषणा AFE_PORT_ID_PRIMARY_TDM_TX_3 \
	(AFE_PORT_ID_PRIMARY_TDM_TX + 0x06)
#घोषणा AFE_PORT_ID_PRIMARY_TDM_TX_4 \
	(AFE_PORT_ID_PRIMARY_TDM_TX + 0x08)
#घोषणा AFE_PORT_ID_PRIMARY_TDM_TX_5 \
	(AFE_PORT_ID_PRIMARY_TDM_TX + 0x0A)
#घोषणा AFE_PORT_ID_PRIMARY_TDM_TX_6 \
	(AFE_PORT_ID_PRIMARY_TDM_TX + 0x0C)
#घोषणा AFE_PORT_ID_PRIMARY_TDM_TX_7 \
	(AFE_PORT_ID_PRIMARY_TDM_TX + 0x0E)

#घोषणा AFE_PORT_ID_SECONDARY_TDM_RX \
	(AFE_PORT_ID_TDM_PORT_RANGE_START + 0x10)
#घोषणा AFE_PORT_ID_SECONDARY_TDM_RX_1 \
	(AFE_PORT_ID_SECONDARY_TDM_RX + 0x02)
#घोषणा AFE_PORT_ID_SECONDARY_TDM_RX_2 \
	(AFE_PORT_ID_SECONDARY_TDM_RX + 0x04)
#घोषणा AFE_PORT_ID_SECONDARY_TDM_RX_3 \
	(AFE_PORT_ID_SECONDARY_TDM_RX + 0x06)
#घोषणा AFE_PORT_ID_SECONDARY_TDM_RX_4 \
	(AFE_PORT_ID_SECONDARY_TDM_RX + 0x08)
#घोषणा AFE_PORT_ID_SECONDARY_TDM_RX_5 \
	(AFE_PORT_ID_SECONDARY_TDM_RX + 0x0A)
#घोषणा AFE_PORT_ID_SECONDARY_TDM_RX_6 \
	(AFE_PORT_ID_SECONDARY_TDM_RX + 0x0C)
#घोषणा AFE_PORT_ID_SECONDARY_TDM_RX_7 \
	(AFE_PORT_ID_SECONDARY_TDM_RX + 0x0E)

#घोषणा AFE_PORT_ID_SECONDARY_TDM_TX \
	(AFE_PORT_ID_TDM_PORT_RANGE_START + 0x11)
#घोषणा AFE_PORT_ID_SECONDARY_TDM_TX_1 \
	(AFE_PORT_ID_SECONDARY_TDM_TX + 0x02)
#घोषणा AFE_PORT_ID_SECONDARY_TDM_TX_2 \
	(AFE_PORT_ID_SECONDARY_TDM_TX + 0x04)
#घोषणा AFE_PORT_ID_SECONDARY_TDM_TX_3 \
	(AFE_PORT_ID_SECONDARY_TDM_TX + 0x06)
#घोषणा AFE_PORT_ID_SECONDARY_TDM_TX_4 \
	(AFE_PORT_ID_SECONDARY_TDM_TX + 0x08)
#घोषणा AFE_PORT_ID_SECONDARY_TDM_TX_5 \
	(AFE_PORT_ID_SECONDARY_TDM_TX + 0x0A)
#घोषणा AFE_PORT_ID_SECONDARY_TDM_TX_6 \
	(AFE_PORT_ID_SECONDARY_TDM_TX + 0x0C)
#घोषणा AFE_PORT_ID_SECONDARY_TDM_TX_7 \
	(AFE_PORT_ID_SECONDARY_TDM_TX + 0x0E)

#घोषणा AFE_PORT_ID_TERTIARY_TDM_RX \
	(AFE_PORT_ID_TDM_PORT_RANGE_START + 0x20)
#घोषणा AFE_PORT_ID_TERTIARY_TDM_RX_1 \
	(AFE_PORT_ID_TERTIARY_TDM_RX + 0x02)
#घोषणा AFE_PORT_ID_TERTIARY_TDM_RX_2 \
	(AFE_PORT_ID_TERTIARY_TDM_RX + 0x04)
#घोषणा AFE_PORT_ID_TERTIARY_TDM_RX_3 \
	(AFE_PORT_ID_TERTIARY_TDM_RX + 0x06)
#घोषणा AFE_PORT_ID_TERTIARY_TDM_RX_4 \
	(AFE_PORT_ID_TERTIARY_TDM_RX + 0x08)
#घोषणा AFE_PORT_ID_TERTIARY_TDM_RX_5 \
	(AFE_PORT_ID_TERTIARY_TDM_RX + 0x0A)
#घोषणा AFE_PORT_ID_TERTIARY_TDM_RX_6 \
	(AFE_PORT_ID_TERTIARY_TDM_RX + 0x0C)
#घोषणा AFE_PORT_ID_TERTIARY_TDM_RX_7 \
	(AFE_PORT_ID_TERTIARY_TDM_RX + 0x0E)

#घोषणा AFE_PORT_ID_TERTIARY_TDM_TX \
	(AFE_PORT_ID_TDM_PORT_RANGE_START + 0x21)
#घोषणा AFE_PORT_ID_TERTIARY_TDM_TX_1 \
	(AFE_PORT_ID_TERTIARY_TDM_TX + 0x02)
#घोषणा AFE_PORT_ID_TERTIARY_TDM_TX_2 \
	(AFE_PORT_ID_TERTIARY_TDM_TX + 0x04)
#घोषणा AFE_PORT_ID_TERTIARY_TDM_TX_3 \
	(AFE_PORT_ID_TERTIARY_TDM_TX + 0x06)
#घोषणा AFE_PORT_ID_TERTIARY_TDM_TX_4 \
	(AFE_PORT_ID_TERTIARY_TDM_TX + 0x08)
#घोषणा AFE_PORT_ID_TERTIARY_TDM_TX_5 \
	(AFE_PORT_ID_TERTIARY_TDM_TX + 0x0A)
#घोषणा AFE_PORT_ID_TERTIARY_TDM_TX_6 \
	(AFE_PORT_ID_TERTIARY_TDM_TX + 0x0C)
#घोषणा AFE_PORT_ID_TERTIARY_TDM_TX_7 \
	(AFE_PORT_ID_TERTIARY_TDM_TX + 0x0E)

#घोषणा AFE_PORT_ID_QUATERNARY_TDM_RX \
	(AFE_PORT_ID_TDM_PORT_RANGE_START + 0x30)
#घोषणा AFE_PORT_ID_QUATERNARY_TDM_RX_1 \
	(AFE_PORT_ID_QUATERNARY_TDM_RX + 0x02)
#घोषणा AFE_PORT_ID_QUATERNARY_TDM_RX_2 \
	(AFE_PORT_ID_QUATERNARY_TDM_RX + 0x04)
#घोषणा AFE_PORT_ID_QUATERNARY_TDM_RX_3 \
	(AFE_PORT_ID_QUATERNARY_TDM_RX + 0x06)
#घोषणा AFE_PORT_ID_QUATERNARY_TDM_RX_4 \
	(AFE_PORT_ID_QUATERNARY_TDM_RX + 0x08)
#घोषणा AFE_PORT_ID_QUATERNARY_TDM_RX_5 \
	(AFE_PORT_ID_QUATERNARY_TDM_RX + 0x0A)
#घोषणा AFE_PORT_ID_QUATERNARY_TDM_RX_6 \
	(AFE_PORT_ID_QUATERNARY_TDM_RX + 0x0C)
#घोषणा AFE_PORT_ID_QUATERNARY_TDM_RX_7 \
	(AFE_PORT_ID_QUATERNARY_TDM_RX + 0x0E)

#घोषणा AFE_PORT_ID_QUATERNARY_TDM_TX \
	(AFE_PORT_ID_TDM_PORT_RANGE_START + 0x31)
#घोषणा AFE_PORT_ID_QUATERNARY_TDM_TX_1 \
	(AFE_PORT_ID_QUATERNARY_TDM_TX + 0x02)
#घोषणा AFE_PORT_ID_QUATERNARY_TDM_TX_2 \
	(AFE_PORT_ID_QUATERNARY_TDM_TX + 0x04)
#घोषणा AFE_PORT_ID_QUATERNARY_TDM_TX_3 \
	(AFE_PORT_ID_QUATERNARY_TDM_TX + 0x06)
#घोषणा AFE_PORT_ID_QUATERNARY_TDM_TX_4 \
	(AFE_PORT_ID_QUATERNARY_TDM_TX + 0x08)
#घोषणा AFE_PORT_ID_QUATERNARY_TDM_TX_5 \
	(AFE_PORT_ID_QUATERNARY_TDM_TX + 0x0A)
#घोषणा AFE_PORT_ID_QUATERNARY_TDM_TX_6 \
	(AFE_PORT_ID_QUATERNARY_TDM_TX + 0x0C)
#घोषणा AFE_PORT_ID_QUATERNARY_TDM_TX_7 \
	(AFE_PORT_ID_QUATERNARY_TDM_TX + 0x0E)

#घोषणा AFE_PORT_ID_QUINARY_TDM_RX \
	(AFE_PORT_ID_TDM_PORT_RANGE_START + 0x40)
#घोषणा AFE_PORT_ID_QUINARY_TDM_RX_1 \
	(AFE_PORT_ID_QUINARY_TDM_RX + 0x02)
#घोषणा AFE_PORT_ID_QUINARY_TDM_RX_2 \
	(AFE_PORT_ID_QUINARY_TDM_RX + 0x04)
#घोषणा AFE_PORT_ID_QUINARY_TDM_RX_3 \
	(AFE_PORT_ID_QUINARY_TDM_RX + 0x06)
#घोषणा AFE_PORT_ID_QUINARY_TDM_RX_4 \
	(AFE_PORT_ID_QUINARY_TDM_RX + 0x08)
#घोषणा AFE_PORT_ID_QUINARY_TDM_RX_5 \
	(AFE_PORT_ID_QUINARY_TDM_RX + 0x0A)
#घोषणा AFE_PORT_ID_QUINARY_TDM_RX_6 \
	(AFE_PORT_ID_QUINARY_TDM_RX + 0x0C)
#घोषणा AFE_PORT_ID_QUINARY_TDM_RX_7 \
	(AFE_PORT_ID_QUINARY_TDM_RX + 0x0E)

#घोषणा AFE_PORT_ID_QUINARY_TDM_TX \
	(AFE_PORT_ID_TDM_PORT_RANGE_START + 0x41)
#घोषणा AFE_PORT_ID_QUINARY_TDM_TX_1 \
	(AFE_PORT_ID_QUINARY_TDM_TX + 0x02)
#घोषणा AFE_PORT_ID_QUINARY_TDM_TX_2 \
	(AFE_PORT_ID_QUINARY_TDM_TX + 0x04)
#घोषणा AFE_PORT_ID_QUINARY_TDM_TX_3 \
	(AFE_PORT_ID_QUINARY_TDM_TX + 0x06)
#घोषणा AFE_PORT_ID_QUINARY_TDM_TX_4 \
	(AFE_PORT_ID_QUINARY_TDM_TX + 0x08)
#घोषणा AFE_PORT_ID_QUINARY_TDM_TX_5 \
	(AFE_PORT_ID_QUINARY_TDM_TX + 0x0A)
#घोषणा AFE_PORT_ID_QUINARY_TDM_TX_6 \
	(AFE_PORT_ID_QUINARY_TDM_TX + 0x0C)
#घोषणा AFE_PORT_ID_QUINARY_TDM_TX_7 \
	(AFE_PORT_ID_QUINARY_TDM_TX + 0x0E)

/* AFE WSA Codec DMA Rx port 0 */
#घोषणा AFE_PORT_ID_WSA_CODEC_DMA_RX_0	0xB000
/* AFE WSA Codec DMA Tx port 0 */
#घोषणा AFE_PORT_ID_WSA_CODEC_DMA_TX_0	0xB001
/* AFE WSA Codec DMA Rx port 1 */
#घोषणा AFE_PORT_ID_WSA_CODEC_DMA_RX_1	0xB002
/* AFE WSA Codec DMA Tx port 1 */
#घोषणा AFE_PORT_ID_WSA_CODEC_DMA_TX_1	0xB003
/* AFE WSA Codec DMA Tx port 2 */
#घोषणा AFE_PORT_ID_WSA_CODEC_DMA_TX_2	0xB005
/* AFE VA Codec DMA Tx port 0 */
#घोषणा AFE_PORT_ID_VA_CODEC_DMA_TX_0	0xB021
/* AFE VA Codec DMA Tx port 1 */
#घोषणा AFE_PORT_ID_VA_CODEC_DMA_TX_1	0xB023
/* AFE VA Codec DMA Tx port 2 */
#घोषणा AFE_PORT_ID_VA_CODEC_DMA_TX_2	0xB025
/* AFE Rx Codec DMA Rx port 0 */
#घोषणा AFE_PORT_ID_RX_CODEC_DMA_RX_0	0xB030
/* AFE Tx Codec DMA Tx port 0 */
#घोषणा AFE_PORT_ID_TX_CODEC_DMA_TX_0	0xB031
/* AFE Rx Codec DMA Rx port 1 */
#घोषणा AFE_PORT_ID_RX_CODEC_DMA_RX_1	0xB032
/* AFE Tx Codec DMA Tx port 1 */
#घोषणा AFE_PORT_ID_TX_CODEC_DMA_TX_1	0xB033
/* AFE Rx Codec DMA Rx port 2 */
#घोषणा AFE_PORT_ID_RX_CODEC_DMA_RX_2	0xB034
/* AFE Tx Codec DMA Tx port 2 */
#घोषणा AFE_PORT_ID_TX_CODEC_DMA_TX_2	0xB035
/* AFE Rx Codec DMA Rx port 3 */
#घोषणा AFE_PORT_ID_RX_CODEC_DMA_RX_3	0xB036
/* AFE Tx Codec DMA Tx port 3 */
#घोषणा AFE_PORT_ID_TX_CODEC_DMA_TX_3	0xB037
/* AFE Rx Codec DMA Rx port 4 */
#घोषणा AFE_PORT_ID_RX_CODEC_DMA_RX_4	0xB038
/* AFE Tx Codec DMA Tx port 4 */
#घोषणा AFE_PORT_ID_TX_CODEC_DMA_TX_4	0xB039
/* AFE Rx Codec DMA Rx port 5 */
#घोषणा AFE_PORT_ID_RX_CODEC_DMA_RX_5	0xB03A
/* AFE Tx Codec DMA Tx port 5 */
#घोषणा AFE_PORT_ID_TX_CODEC_DMA_TX_5	0xB03B
/* AFE Rx Codec DMA Rx port 6 */
#घोषणा AFE_PORT_ID_RX_CODEC_DMA_RX_6	0xB03C
/* AFE Rx Codec DMA Rx port 7 */
#घोषणा AFE_PORT_ID_RX_CODEC_DMA_RX_7	0xB03E

#घोषणा Q6AFE_LPASS_MODE_CLK1_VALID 1
#घोषणा Q6AFE_LPASS_MODE_CLK2_VALID 2
#घोषणा Q6AFE_LPASS_CLK_SRC_INTERNAL 1
#घोषणा Q6AFE_LPASS_CLK_ROOT_DEFAULT 0
#घोषणा AFE_API_VERSION_TDM_CONFIG              1
#घोषणा AFE_API_VERSION_SLOT_MAPPING_CONFIG	1
#घोषणा AFE_API_VERSION_CODEC_DMA_CONFIG	1

#घोषणा TIMEOUT_MS 1000
#घोषणा AFE_CMD_RESP_AVAIL	0
#घोषणा AFE_CMD_RESP_NONE	1
#घोषणा AFE_CLK_TOKEN		1024

काष्ठा q6afe अणु
	काष्ठा apr_device *apr;
	काष्ठा device *dev;
	काष्ठा q6core_svc_api_info ainfo;
	काष्ठा mutex lock;
	काष्ठा aprv2_ibasic_rsp_result_t result;
	रुको_queue_head_t रुको;
	काष्ठा list_head port_list;
	spinlock_t port_list_lock;
पूर्ण;

काष्ठा afe_port_cmd_device_start अणु
	u16 port_id;
	u16 reserved;
पूर्ण __packed;

काष्ठा afe_port_cmd_device_stop अणु
	u16 port_id;
	u16 reserved;
/* Reserved क्रम 32-bit alignment. This field must be set to 0.*/
पूर्ण __packed;

काष्ठा afe_port_param_data_v2 अणु
	u32 module_id;
	u32 param_id;
	u16 param_size;
	u16 reserved;
पूर्ण __packed;

काष्ठा afe_svc_cmd_set_param अणु
	uपूर्णांक32_t payload_size;
	uपूर्णांक32_t payload_address_lsw;
	uपूर्णांक32_t payload_address_msw;
	uपूर्णांक32_t mem_map_handle;
पूर्ण __packed;

काष्ठा afe_port_cmd_set_param_v2 अणु
	u16 port_id;
	u16 payload_size;
	u32 payload_address_lsw;
	u32 payload_address_msw;
	u32 mem_map_handle;
पूर्ण __packed;

काष्ठा afe_param_id_hdmi_multi_chan_audio_cfg अणु
	u32 hdmi_cfg_minor_version;
	u16 datatype;
	u16 channel_allocation;
	u32 sample_rate;
	u16 bit_width;
	u16 reserved;
पूर्ण __packed;

काष्ठा afe_param_id_slimbus_cfg अणु
	u32                  sb_cfg_minor_version;
/* Minor version used क्रम tracking the version of the SLIMBUS
 * configuration पूर्णांकerface.
 * Supported values: #AFE_API_VERSION_SLIMBUS_CONFIG
 */

	u16                  slimbus_dev_id;
/* SLIMbus hardware device ID, which is required to handle
 * multiple SLIMbus hardware blocks.
 * Supported values: - #AFE_SLIMBUS_DEVICE_1 - #AFE_SLIMBUS_DEVICE_2
 */
	u16                  bit_width;
/* Bit width of the sample.
 * Supported values: 16, 24
 */
	u16                  data_क्रमmat;
/* Data क्रमmat supported by the SLIMbus hardware. The शेष is
 * 0 (#AFE_SB_DATA_FORMAT_NOT_INDICATED), which indicates the
 * hardware करोes not perक्रमm any क्रमmat conversions beक्रमe the data
 * transfer.
 */
	u16                  num_channels;
/* Number of channels.
 * Supported values: 1 to #AFE_PORT_MAX_AUDIO_CHAN_CNT
 */
	u8  shared_ch_mapping[AFE_PORT_MAX_AUDIO_CHAN_CNT];
/* Mapping of shared channel IDs (128 to 255) to which the
 * master port is to be connected.
 * Shared_channel_mapping[i] represents the shared channel asचिन्हित
 * क्रम audio channel i in multichannel audio data.
 */
	u32              sample_rate;
/* Sampling rate of the port.
 * Supported values:
 * - #AFE_PORT_SAMPLE_RATE_8K
 * - #AFE_PORT_SAMPLE_RATE_16K
 * - #AFE_PORT_SAMPLE_RATE_48K
 * - #AFE_PORT_SAMPLE_RATE_96K
 * - #AFE_PORT_SAMPLE_RATE_192K
 */
पूर्ण __packed;

काष्ठा afe_clk_cfg अणु
	u32                  i2s_cfg_minor_version;
	u32                  clk_val1;
	u32                  clk_val2;
	u16                  clk_src;
	u16                  clk_root;
	u16                  clk_set_mode;
	u16                  reserved;
पूर्ण __packed;

काष्ठा afe_digital_clk_cfg अणु
	u32                  i2s_cfg_minor_version;
	u32                  clk_val;
	u16                  clk_root;
	u16                  reserved;
पूर्ण __packed;

काष्ठा afe_param_id_i2s_cfg अणु
	u32	i2s_cfg_minor_version;
	u16	bit_width;
	u16	channel_mode;
	u16	mono_stereo;
	u16	ws_src;
	u32	sample_rate;
	u16	data_क्रमmat;
	u16	reserved;
पूर्ण __packed;

काष्ठा afe_param_id_tdm_cfg अणु
	u32	tdm_cfg_minor_version;
	u32	num_channels;
	u32	sample_rate;
	u32	bit_width;
	u16	data_क्रमmat;
	u16	sync_mode;
	u16	sync_src;
	u16	nslots_per_frame;
	u16	ctrl_data_out_enable;
	u16	ctrl_invert_sync_pulse;
	u16	ctrl_sync_data_delay;
	u16	slot_width;
	u32	slot_mask;
पूर्ण __packed;

काष्ठा afe_param_id_cdc_dma_cfg अणु
	u32	cdc_dma_cfg_minor_version;
	u32	sample_rate;
	u16	bit_width;
	u16	data_क्रमmat;
	u16	num_channels;
	u16	active_channels_mask;
पूर्ण __packed;

जोड़ afe_port_config अणु
	काष्ठा afe_param_id_hdmi_multi_chan_audio_cfg hdmi_multi_ch;
	काष्ठा afe_param_id_slimbus_cfg           slim_cfg;
	काष्ठा afe_param_id_i2s_cfg	i2s_cfg;
	काष्ठा afe_param_id_tdm_cfg	tdm_cfg;
	काष्ठा afe_param_id_cdc_dma_cfg	dma_cfg;
पूर्ण __packed;


काष्ठा afe_clk_set अणु
	uपूर्णांक32_t clk_set_minor_version;
	uपूर्णांक32_t clk_id;
	uपूर्णांक32_t clk_freq_in_hz;
	uपूर्णांक16_t clk_attri;
	uपूर्णांक16_t clk_root;
	uपूर्णांक32_t enable;
पूर्ण;

काष्ठा afe_param_id_slot_mapping_cfg अणु
	u32	minor_version;
	u16	num_channels;
	u16	bitwidth;
	u32	data_align_type;
	u16	ch_mapping[AFE_PORT_MAX_AUDIO_CHAN_CNT];
पूर्ण __packed;

काष्ठा q6afe_port अणु
	रुको_queue_head_t रुको;
	जोड़ afe_port_config port_cfg;
	काष्ठा afe_param_id_slot_mapping_cfg *scfg;
	काष्ठा aprv2_ibasic_rsp_result_t result;
	पूर्णांक token;
	पूर्णांक id;
	पूर्णांक cfg_type;
	काष्ठा q6afe *afe;
	काष्ठा kref refcount;
	काष्ठा list_head node;
पूर्ण;

काष्ठा afe_cmd_remote_lpass_core_hw_vote_request अणु
        uपूर्णांक32_t  hw_block_id;
        अक्षर client_name[8];
पूर्ण __packed;

काष्ठा afe_cmd_remote_lpass_core_hw_devote_request अणु
        uपूर्णांक32_t  hw_block_id;
        uपूर्णांक32_t client_handle;
पूर्ण __packed;



काष्ठा afe_port_map अणु
	पूर्णांक port_id;
	पूर्णांक token;
	पूर्णांक is_rx;
	पूर्णांक is_dig_pcm;
पूर्ण;

/*
 * Mapping between Virtual Port IDs to DSP AFE Port ID
 * On B Family SoCs DSP Port IDs are consistent across multiple SoCs
 * on A Family SoCs DSP port IDs are same as भव Port IDs.
 */

अटल काष्ठा afe_port_map port_maps[AFE_PORT_MAX] = अणु
	[HDMI_RX] = अणु AFE_PORT_ID_MULTICHAN_HDMI_RX, HDMI_RX, 1, 1पूर्ण,
	[SLIMBUS_0_RX] = अणु AFE_PORT_ID_SLIMBUS_MULTI_CHAN_0_RX,
				SLIMBUS_0_RX, 1, 1पूर्ण,
	[SLIMBUS_1_RX] = अणु AFE_PORT_ID_SLIMBUS_MULTI_CHAN_1_RX,
				SLIMBUS_1_RX, 1, 1पूर्ण,
	[SLIMBUS_2_RX] = अणु AFE_PORT_ID_SLIMBUS_MULTI_CHAN_2_RX,
				SLIMBUS_2_RX, 1, 1पूर्ण,
	[SLIMBUS_3_RX] = अणु AFE_PORT_ID_SLIMBUS_MULTI_CHAN_3_RX,
				SLIMBUS_3_RX, 1, 1पूर्ण,
	[SLIMBUS_4_RX] = अणु AFE_PORT_ID_SLIMBUS_MULTI_CHAN_4_RX,
				SLIMBUS_4_RX, 1, 1पूर्ण,
	[SLIMBUS_5_RX] = अणु AFE_PORT_ID_SLIMBUS_MULTI_CHAN_5_RX,
				SLIMBUS_5_RX, 1, 1पूर्ण,
	[SLIMBUS_6_RX] = अणु AFE_PORT_ID_SLIMBUS_MULTI_CHAN_6_RX,
				SLIMBUS_6_RX, 1, 1पूर्ण,
	[SLIMBUS_0_TX] = अणु AFE_PORT_ID_SLIMBUS_MULTI_CHAN_0_TX,
				SLIMBUS_0_TX, 0, 1पूर्ण,
	[SLIMBUS_1_TX] = अणु AFE_PORT_ID_SLIMBUS_MULTI_CHAN_1_TX,
				SLIMBUS_1_TX, 0, 1पूर्ण,
	[SLIMBUS_2_TX] = अणु AFE_PORT_ID_SLIMBUS_MULTI_CHAN_2_TX,
				SLIMBUS_2_TX, 0, 1पूर्ण,
	[SLIMBUS_3_TX] = अणु AFE_PORT_ID_SLIMBUS_MULTI_CHAN_3_TX,
				SLIMBUS_3_TX, 0, 1पूर्ण,
	[SLIMBUS_4_TX] = अणु AFE_PORT_ID_SLIMBUS_MULTI_CHAN_4_TX,
				SLIMBUS_4_TX, 0, 1पूर्ण,
	[SLIMBUS_5_TX] = अणु AFE_PORT_ID_SLIMBUS_MULTI_CHAN_5_TX,
				SLIMBUS_5_TX, 0, 1पूर्ण,
	[SLIMBUS_6_TX] = अणु AFE_PORT_ID_SLIMBUS_MULTI_CHAN_6_TX,
				SLIMBUS_6_TX, 0, 1पूर्ण,
	[PRIMARY_MI2S_RX] = अणु AFE_PORT_ID_PRIMARY_MI2S_RX,
				PRIMARY_MI2S_RX, 1, 1पूर्ण,
	[PRIMARY_MI2S_TX] = अणु AFE_PORT_ID_PRIMARY_MI2S_TX,
				PRIMARY_MI2S_RX, 0, 1पूर्ण,
	[SECONDARY_MI2S_RX] = अणु AFE_PORT_ID_SECONDARY_MI2S_RX,
				SECONDARY_MI2S_RX, 1, 1पूर्ण,
	[SECONDARY_MI2S_TX] = अणु AFE_PORT_ID_SECONDARY_MI2S_TX,
				SECONDARY_MI2S_TX, 0, 1पूर्ण,
	[TERTIARY_MI2S_RX] = अणु AFE_PORT_ID_TERTIARY_MI2S_RX,
				TERTIARY_MI2S_RX, 1, 1पूर्ण,
	[TERTIARY_MI2S_TX] = अणु AFE_PORT_ID_TERTIARY_MI2S_TX,
				TERTIARY_MI2S_TX, 0, 1पूर्ण,
	[QUATERNARY_MI2S_RX] = अणु AFE_PORT_ID_QUATERNARY_MI2S_RX,
				QUATERNARY_MI2S_RX, 1, 1पूर्ण,
	[QUATERNARY_MI2S_TX] = अणु AFE_PORT_ID_QUATERNARY_MI2S_TX,
				QUATERNARY_MI2S_TX, 0, 1पूर्ण,
	[PRIMARY_TDM_RX_0] =  अणु AFE_PORT_ID_PRIMARY_TDM_RX,
				PRIMARY_TDM_RX_0, 1, 1पूर्ण,
	[PRIMARY_TDM_TX_0] =  अणु AFE_PORT_ID_PRIMARY_TDM_TX,
				PRIMARY_TDM_TX_0, 0, 1पूर्ण,
	[PRIMARY_TDM_RX_1] =  अणु AFE_PORT_ID_PRIMARY_TDM_RX_1,
				PRIMARY_TDM_RX_1, 1, 1पूर्ण,
	[PRIMARY_TDM_TX_1] =  अणु AFE_PORT_ID_PRIMARY_TDM_TX_1,
				PRIMARY_TDM_TX_1, 0, 1पूर्ण,
	[PRIMARY_TDM_RX_2] =  अणु AFE_PORT_ID_PRIMARY_TDM_RX_2,
				PRIMARY_TDM_RX_2, 1, 1पूर्ण,
	[PRIMARY_TDM_TX_2] =  अणु AFE_PORT_ID_PRIMARY_TDM_TX_2,
				PRIMARY_TDM_TX_2, 0, 1पूर्ण,
	[PRIMARY_TDM_RX_3] =  अणु AFE_PORT_ID_PRIMARY_TDM_RX_3,
				PRIMARY_TDM_RX_3, 1, 1पूर्ण,
	[PRIMARY_TDM_TX_3] =  अणु AFE_PORT_ID_PRIMARY_TDM_TX_3,
				PRIMARY_TDM_TX_3, 0, 1पूर्ण,
	[PRIMARY_TDM_RX_4] =  अणु AFE_PORT_ID_PRIMARY_TDM_RX_4,
				PRIMARY_TDM_RX_4, 1, 1पूर्ण,
	[PRIMARY_TDM_TX_4] =  अणु AFE_PORT_ID_PRIMARY_TDM_TX_4,
				PRIMARY_TDM_TX_4, 0, 1पूर्ण,
	[PRIMARY_TDM_RX_5] =  अणु AFE_PORT_ID_PRIMARY_TDM_RX_5,
				PRIMARY_TDM_RX_5, 1, 1पूर्ण,
	[PRIMARY_TDM_TX_5] =  अणु AFE_PORT_ID_PRIMARY_TDM_TX_5,
				PRIMARY_TDM_TX_5, 0, 1पूर्ण,
	[PRIMARY_TDM_RX_6] =  अणु AFE_PORT_ID_PRIMARY_TDM_RX_6,
				PRIMARY_TDM_RX_6, 1, 1पूर्ण,
	[PRIMARY_TDM_TX_6] =  अणु AFE_PORT_ID_PRIMARY_TDM_TX_6,
				PRIMARY_TDM_TX_6, 0, 1पूर्ण,
	[PRIMARY_TDM_RX_7] =  अणु AFE_PORT_ID_PRIMARY_TDM_RX_7,
				PRIMARY_TDM_RX_7, 1, 1पूर्ण,
	[PRIMARY_TDM_TX_7] =  अणु AFE_PORT_ID_PRIMARY_TDM_TX_7,
				PRIMARY_TDM_TX_7, 0, 1पूर्ण,
	[SECONDARY_TDM_RX_0] =  अणु AFE_PORT_ID_SECONDARY_TDM_RX,
				SECONDARY_TDM_RX_0, 1, 1पूर्ण,
	[SECONDARY_TDM_TX_0] =  अणु AFE_PORT_ID_SECONDARY_TDM_TX,
				SECONDARY_TDM_TX_0, 0, 1पूर्ण,
	[SECONDARY_TDM_RX_1] =  अणु AFE_PORT_ID_SECONDARY_TDM_RX_1,
				SECONDARY_TDM_RX_1, 1, 1पूर्ण,
	[SECONDARY_TDM_TX_1] =  अणु AFE_PORT_ID_SECONDARY_TDM_TX_1,
				SECONDARY_TDM_TX_1, 0, 1पूर्ण,
	[SECONDARY_TDM_RX_2] =  अणु AFE_PORT_ID_SECONDARY_TDM_RX_2,
				SECONDARY_TDM_RX_2, 1, 1पूर्ण,
	[SECONDARY_TDM_TX_2] =  अणु AFE_PORT_ID_SECONDARY_TDM_TX_2,
				SECONDARY_TDM_TX_2, 0, 1पूर्ण,
	[SECONDARY_TDM_RX_3] =  अणु AFE_PORT_ID_SECONDARY_TDM_RX_3,
				SECONDARY_TDM_RX_3, 1, 1पूर्ण,
	[SECONDARY_TDM_TX_3] =  अणु AFE_PORT_ID_SECONDARY_TDM_TX_3,
				SECONDARY_TDM_TX_3, 0, 1पूर्ण,
	[SECONDARY_TDM_RX_4] =  अणु AFE_PORT_ID_SECONDARY_TDM_RX_4,
				SECONDARY_TDM_RX_4, 1, 1पूर्ण,
	[SECONDARY_TDM_TX_4] =  अणु AFE_PORT_ID_SECONDARY_TDM_TX_4,
				SECONDARY_TDM_TX_4, 0, 1पूर्ण,
	[SECONDARY_TDM_RX_5] =  अणु AFE_PORT_ID_SECONDARY_TDM_RX_5,
				SECONDARY_TDM_RX_5, 1, 1पूर्ण,
	[SECONDARY_TDM_TX_5] =  अणु AFE_PORT_ID_SECONDARY_TDM_TX_5,
				SECONDARY_TDM_TX_5, 0, 1पूर्ण,
	[SECONDARY_TDM_RX_6] =  अणु AFE_PORT_ID_SECONDARY_TDM_RX_6,
				SECONDARY_TDM_RX_6, 1, 1पूर्ण,
	[SECONDARY_TDM_TX_6] =  अणु AFE_PORT_ID_SECONDARY_TDM_TX_6,
				SECONDARY_TDM_TX_6, 0, 1पूर्ण,
	[SECONDARY_TDM_RX_7] =  अणु AFE_PORT_ID_SECONDARY_TDM_RX_7,
				SECONDARY_TDM_RX_7, 1, 1पूर्ण,
	[SECONDARY_TDM_TX_7] =  अणु AFE_PORT_ID_SECONDARY_TDM_TX_7,
				SECONDARY_TDM_TX_7, 0, 1पूर्ण,
	[TERTIARY_TDM_RX_0] =  अणु AFE_PORT_ID_TERTIARY_TDM_RX,
				TERTIARY_TDM_RX_0, 1, 1पूर्ण,
	[TERTIARY_TDM_TX_0] =  अणु AFE_PORT_ID_TERTIARY_TDM_TX,
				TERTIARY_TDM_TX_0, 0, 1पूर्ण,
	[TERTIARY_TDM_RX_1] =  अणु AFE_PORT_ID_TERTIARY_TDM_RX_1,
				TERTIARY_TDM_RX_1, 1, 1पूर्ण,
	[TERTIARY_TDM_TX_1] =  अणु AFE_PORT_ID_TERTIARY_TDM_TX_1,
				TERTIARY_TDM_TX_1, 0, 1पूर्ण,
	[TERTIARY_TDM_RX_2] =  अणु AFE_PORT_ID_TERTIARY_TDM_RX_2,
				TERTIARY_TDM_RX_2, 1, 1पूर्ण,
	[TERTIARY_TDM_TX_2] =  अणु AFE_PORT_ID_TERTIARY_TDM_TX_2,
				TERTIARY_TDM_TX_2, 0, 1पूर्ण,
	[TERTIARY_TDM_RX_3] =  अणु AFE_PORT_ID_TERTIARY_TDM_RX_3,
				TERTIARY_TDM_RX_3, 1, 1पूर्ण,
	[TERTIARY_TDM_TX_3] =  अणु AFE_PORT_ID_TERTIARY_TDM_TX_3,
				TERTIARY_TDM_TX_3, 0, 1पूर्ण,
	[TERTIARY_TDM_RX_4] =  अणु AFE_PORT_ID_TERTIARY_TDM_RX_4,
				TERTIARY_TDM_RX_4, 1, 1पूर्ण,
	[TERTIARY_TDM_TX_4] =  अणु AFE_PORT_ID_TERTIARY_TDM_TX_4,
				TERTIARY_TDM_TX_4, 0, 1पूर्ण,
	[TERTIARY_TDM_RX_5] =  अणु AFE_PORT_ID_TERTIARY_TDM_RX_5,
				TERTIARY_TDM_RX_5, 1, 1पूर्ण,
	[TERTIARY_TDM_TX_5] =  अणु AFE_PORT_ID_TERTIARY_TDM_TX_5,
				TERTIARY_TDM_TX_5, 0, 1पूर्ण,
	[TERTIARY_TDM_RX_6] =  अणु AFE_PORT_ID_TERTIARY_TDM_RX_6,
				TERTIARY_TDM_RX_6, 1, 1पूर्ण,
	[TERTIARY_TDM_TX_6] =  अणु AFE_PORT_ID_TERTIARY_TDM_TX_6,
				TERTIARY_TDM_TX_6, 0, 1पूर्ण,
	[TERTIARY_TDM_RX_7] =  अणु AFE_PORT_ID_TERTIARY_TDM_RX_7,
				TERTIARY_TDM_RX_7, 1, 1पूर्ण,
	[TERTIARY_TDM_TX_7] =  अणु AFE_PORT_ID_TERTIARY_TDM_TX_7,
				TERTIARY_TDM_TX_7, 0, 1पूर्ण,
	[QUATERNARY_TDM_RX_0] =  अणु AFE_PORT_ID_QUATERNARY_TDM_RX,
				QUATERNARY_TDM_RX_0, 1, 1पूर्ण,
	[QUATERNARY_TDM_TX_0] =  अणु AFE_PORT_ID_QUATERNARY_TDM_TX,
				QUATERNARY_TDM_TX_0, 0, 1पूर्ण,
	[QUATERNARY_TDM_RX_1] =  अणु AFE_PORT_ID_QUATERNARY_TDM_RX_1,
				QUATERNARY_TDM_RX_1, 1, 1पूर्ण,
	[QUATERNARY_TDM_TX_1] =  अणु AFE_PORT_ID_QUATERNARY_TDM_TX_1,
				QUATERNARY_TDM_TX_1, 0, 1पूर्ण,
	[QUATERNARY_TDM_RX_2] =  अणु AFE_PORT_ID_QUATERNARY_TDM_RX_2,
				QUATERNARY_TDM_RX_2, 1, 1पूर्ण,
	[QUATERNARY_TDM_TX_2] =  अणु AFE_PORT_ID_QUATERNARY_TDM_TX_2,
				QUATERNARY_TDM_TX_2, 0, 1पूर्ण,
	[QUATERNARY_TDM_RX_3] =  अणु AFE_PORT_ID_QUATERNARY_TDM_RX_3,
				QUATERNARY_TDM_RX_3, 1, 1पूर्ण,
	[QUATERNARY_TDM_TX_3] =  अणु AFE_PORT_ID_QUATERNARY_TDM_TX_3,
				QUATERNARY_TDM_TX_3, 0, 1पूर्ण,
	[QUATERNARY_TDM_RX_4] =  अणु AFE_PORT_ID_QUATERNARY_TDM_RX_4,
				QUATERNARY_TDM_RX_4, 1, 1पूर्ण,
	[QUATERNARY_TDM_TX_4] =  अणु AFE_PORT_ID_QUATERNARY_TDM_TX_4,
				QUATERNARY_TDM_TX_4, 0, 1पूर्ण,
	[QUATERNARY_TDM_RX_5] =  अणु AFE_PORT_ID_QUATERNARY_TDM_RX_5,
				QUATERNARY_TDM_RX_5, 1, 1पूर्ण,
	[QUATERNARY_TDM_TX_5] =  अणु AFE_PORT_ID_QUATERNARY_TDM_TX_5,
				QUATERNARY_TDM_TX_5, 0, 1पूर्ण,
	[QUATERNARY_TDM_RX_6] =  अणु AFE_PORT_ID_QUATERNARY_TDM_RX_6,
				QUATERNARY_TDM_RX_6, 1, 1पूर्ण,
	[QUATERNARY_TDM_TX_6] =  अणु AFE_PORT_ID_QUATERNARY_TDM_TX_6,
				QUATERNARY_TDM_TX_6, 0, 1पूर्ण,
	[QUATERNARY_TDM_RX_7] =  अणु AFE_PORT_ID_QUATERNARY_TDM_RX_7,
				QUATERNARY_TDM_RX_7, 1, 1पूर्ण,
	[QUATERNARY_TDM_TX_7] =  अणु AFE_PORT_ID_QUATERNARY_TDM_TX_7,
				QUATERNARY_TDM_TX_7, 0, 1पूर्ण,
	[QUINARY_TDM_RX_0] =  अणु AFE_PORT_ID_QUINARY_TDM_RX,
				QUINARY_TDM_RX_0, 1, 1पूर्ण,
	[QUINARY_TDM_TX_0] =  अणु AFE_PORT_ID_QUINARY_TDM_TX,
				QUINARY_TDM_TX_0, 0, 1पूर्ण,
	[QUINARY_TDM_RX_1] =  अणु AFE_PORT_ID_QUINARY_TDM_RX_1,
				QUINARY_TDM_RX_1, 1, 1पूर्ण,
	[QUINARY_TDM_TX_1] =  अणु AFE_PORT_ID_QUINARY_TDM_TX_1,
				QUINARY_TDM_TX_1, 0, 1पूर्ण,
	[QUINARY_TDM_RX_2] =  अणु AFE_PORT_ID_QUINARY_TDM_RX_2,
				QUINARY_TDM_RX_2, 1, 1पूर्ण,
	[QUINARY_TDM_TX_2] =  अणु AFE_PORT_ID_QUINARY_TDM_TX_2,
				QUINARY_TDM_TX_2, 0, 1पूर्ण,
	[QUINARY_TDM_RX_3] =  अणु AFE_PORT_ID_QUINARY_TDM_RX_3,
				QUINARY_TDM_RX_3, 1, 1पूर्ण,
	[QUINARY_TDM_TX_3] =  अणु AFE_PORT_ID_QUINARY_TDM_TX_3,
				QUINARY_TDM_TX_3, 0, 1पूर्ण,
	[QUINARY_TDM_RX_4] =  अणु AFE_PORT_ID_QUINARY_TDM_RX_4,
				QUINARY_TDM_RX_4, 1, 1पूर्ण,
	[QUINARY_TDM_TX_4] =  अणु AFE_PORT_ID_QUINARY_TDM_TX_4,
				QUINARY_TDM_TX_4, 0, 1पूर्ण,
	[QUINARY_TDM_RX_5] =  अणु AFE_PORT_ID_QUINARY_TDM_RX_5,
				QUINARY_TDM_RX_5, 1, 1पूर्ण,
	[QUINARY_TDM_TX_5] =  अणु AFE_PORT_ID_QUINARY_TDM_TX_5,
				QUINARY_TDM_TX_5, 0, 1पूर्ण,
	[QUINARY_TDM_RX_6] =  अणु AFE_PORT_ID_QUINARY_TDM_RX_6,
				QUINARY_TDM_RX_6, 1, 1पूर्ण,
	[QUINARY_TDM_TX_6] =  अणु AFE_PORT_ID_QUINARY_TDM_TX_6,
				QUINARY_TDM_TX_6, 0, 1पूर्ण,
	[QUINARY_TDM_RX_7] =  अणु AFE_PORT_ID_QUINARY_TDM_RX_7,
				QUINARY_TDM_RX_7, 1, 1पूर्ण,
	[QUINARY_TDM_TX_7] =  अणु AFE_PORT_ID_QUINARY_TDM_TX_7,
				QUINARY_TDM_TX_7, 0, 1पूर्ण,
	[DISPLAY_PORT_RX] = अणु AFE_PORT_ID_HDMI_OVER_DP_RX,
				DISPLAY_PORT_RX, 1, 1पूर्ण,
	[WSA_CODEC_DMA_RX_0] = अणु AFE_PORT_ID_WSA_CODEC_DMA_RX_0,
				WSA_CODEC_DMA_RX_0, 1, 1पूर्ण,
	[WSA_CODEC_DMA_TX_0] = अणु AFE_PORT_ID_WSA_CODEC_DMA_TX_0,
				WSA_CODEC_DMA_TX_0, 0, 1पूर्ण,
	[WSA_CODEC_DMA_RX_1] = अणु AFE_PORT_ID_WSA_CODEC_DMA_RX_1,
				WSA_CODEC_DMA_RX_1, 1, 1पूर्ण,
	[WSA_CODEC_DMA_TX_1] = अणु AFE_PORT_ID_WSA_CODEC_DMA_TX_1,
				WSA_CODEC_DMA_TX_1, 0, 1पूर्ण,
	[WSA_CODEC_DMA_TX_2] = अणु AFE_PORT_ID_WSA_CODEC_DMA_TX_2,
				WSA_CODEC_DMA_TX_2, 0, 1पूर्ण,
	[VA_CODEC_DMA_TX_0] = अणु AFE_PORT_ID_VA_CODEC_DMA_TX_0,
				VA_CODEC_DMA_TX_0, 0, 1पूर्ण,
	[VA_CODEC_DMA_TX_1] = अणु AFE_PORT_ID_VA_CODEC_DMA_TX_1,
				VA_CODEC_DMA_TX_1, 0, 1पूर्ण,
	[VA_CODEC_DMA_TX_2] = अणु AFE_PORT_ID_VA_CODEC_DMA_TX_2,
				VA_CODEC_DMA_TX_2, 0, 1पूर्ण,
	[RX_CODEC_DMA_RX_0] = अणु AFE_PORT_ID_RX_CODEC_DMA_RX_0,
				RX_CODEC_DMA_RX_0, 1, 1पूर्ण,
	[TX_CODEC_DMA_TX_0] = अणु AFE_PORT_ID_TX_CODEC_DMA_TX_0,
				TX_CODEC_DMA_TX_0, 0, 1पूर्ण,
	[RX_CODEC_DMA_RX_1] = अणु AFE_PORT_ID_RX_CODEC_DMA_RX_1,
				RX_CODEC_DMA_RX_1, 1, 1पूर्ण,
	[TX_CODEC_DMA_TX_1] = अणु AFE_PORT_ID_TX_CODEC_DMA_TX_1,
				TX_CODEC_DMA_TX_1, 0, 1पूर्ण,
	[RX_CODEC_DMA_RX_2] = अणु AFE_PORT_ID_RX_CODEC_DMA_RX_2,
				RX_CODEC_DMA_RX_2, 1, 1पूर्ण,
	[TX_CODEC_DMA_TX_2] = अणु AFE_PORT_ID_TX_CODEC_DMA_TX_2,
				TX_CODEC_DMA_TX_2, 0, 1पूर्ण,
	[RX_CODEC_DMA_RX_3] = अणु AFE_PORT_ID_RX_CODEC_DMA_RX_3,
				RX_CODEC_DMA_RX_3, 1, 1पूर्ण,
	[TX_CODEC_DMA_TX_3] = अणु AFE_PORT_ID_TX_CODEC_DMA_TX_3,
				TX_CODEC_DMA_TX_3, 0, 1पूर्ण,
	[RX_CODEC_DMA_RX_4] = अणु AFE_PORT_ID_RX_CODEC_DMA_RX_4,
				RX_CODEC_DMA_RX_4, 1, 1पूर्ण,
	[TX_CODEC_DMA_TX_4] = अणु AFE_PORT_ID_TX_CODEC_DMA_TX_4,
				TX_CODEC_DMA_TX_4, 0, 1पूर्ण,
	[RX_CODEC_DMA_RX_5] = अणु AFE_PORT_ID_RX_CODEC_DMA_RX_5,
				RX_CODEC_DMA_RX_5, 1, 1पूर्ण,
	[TX_CODEC_DMA_TX_5] = अणु AFE_PORT_ID_TX_CODEC_DMA_TX_5,
				TX_CODEC_DMA_TX_5, 0, 1पूर्ण,
	[RX_CODEC_DMA_RX_6] = अणु AFE_PORT_ID_RX_CODEC_DMA_RX_6,
				RX_CODEC_DMA_RX_6, 1, 1पूर्ण,
	[RX_CODEC_DMA_RX_7] = अणु AFE_PORT_ID_RX_CODEC_DMA_RX_7,
				RX_CODEC_DMA_RX_7, 1, 1पूर्ण,
पूर्ण;

अटल व्योम q6afe_port_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा q6afe_port *port;
	काष्ठा q6afe *afe;
	अचिन्हित दीर्घ flags;

	port = container_of(ref, काष्ठा q6afe_port, refcount);
	afe = port->afe;
	spin_lock_irqsave(&afe->port_list_lock, flags);
	list_del(&port->node);
	spin_unlock_irqrestore(&afe->port_list_lock, flags);
	kमुक्त(port->scfg);
	kमुक्त(port);
पूर्ण

अटल काष्ठा q6afe_port *q6afe_find_port(काष्ठा q6afe *afe, पूर्णांक token)
अणु
	काष्ठा q6afe_port *p;
	काष्ठा q6afe_port *ret = शून्य;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&afe->port_list_lock, flags);
	list_क्रम_each_entry(p, &afe->port_list, node)
		अगर (p->token == token) अणु
			ret = p;
			kref_get(&p->refcount);
			अवरोध;
		पूर्ण

	spin_unlock_irqrestore(&afe->port_list_lock, flags);
	वापस ret;
पूर्ण

अटल पूर्णांक q6afe_callback(काष्ठा apr_device *adev, काष्ठा apr_resp_pkt *data)
अणु
	काष्ठा q6afe *afe = dev_get_drvdata(&adev->dev);
	काष्ठा aprv2_ibasic_rsp_result_t *res;
	काष्ठा apr_hdr *hdr = &data->hdr;
	काष्ठा q6afe_port *port;

	अगर (!data->payload_size)
		वापस 0;

	res = data->payload;
	चयन (hdr->opcode) अणु
	हाल APR_BASIC_RSP_RESULT: अणु
		अगर (res->status) अणु
			dev_err(afe->dev, "cmd = 0x%x returned error = 0x%x\n",
				res->opcode, res->status);
		पूर्ण
		चयन (res->opcode) अणु
		हाल AFE_PORT_CMD_SET_PARAM_V2:
		हाल AFE_PORT_CMD_DEVICE_STOP:
		हाल AFE_PORT_CMD_DEVICE_START:
		हाल AFE_SVC_CMD_SET_PARAM:
			port = q6afe_find_port(afe, hdr->token);
			अगर (port) अणु
				port->result = *res;
				wake_up(&port->रुको);
				kref_put(&port->refcount, q6afe_port_मुक्त);
			पूर्ण अन्यथा अगर (hdr->token == AFE_CLK_TOKEN) अणु
				afe->result = *res;
				wake_up(&afe->रुको);
			पूर्ण
			अवरोध;
		शेष:
			dev_err(afe->dev, "Unknown cmd 0x%x\n",	res->opcode);
			अवरोध;
		पूर्ण
	पूर्ण
		अवरोध;
	हाल AFE_CMD_RSP_REMOTE_LPASS_CORE_HW_VOTE_REQUEST:
		afe->result.opcode = hdr->opcode;
		afe->result.status = res->status;
		wake_up(&afe->रुको);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * q6afe_get_port_id() - Get port id from a given port index
 *
 * @index: port index
 *
 * Return: Will be an negative on error or valid port_id on success
 */
पूर्णांक q6afe_get_port_id(पूर्णांक index)
अणु
	अगर (index < 0 || index >= AFE_PORT_MAX)
		वापस -EINVAL;

	वापस port_maps[index].port_id;
पूर्ण
EXPORT_SYMBOL_GPL(q6afe_get_port_id);

अटल पूर्णांक afe_apr_send_pkt(काष्ठा q6afe *afe, काष्ठा apr_pkt *pkt,
			    काष्ठा q6afe_port *port, uपूर्णांक32_t rsp_opcode)
अणु
	रुको_queue_head_t *रुको;
	काष्ठा aprv2_ibasic_rsp_result_t *result;
	पूर्णांक ret;

	mutex_lock(&afe->lock);
	अगर (port) अणु
		रुको = &port->रुको;
		result = &port->result;
	पूर्ण अन्यथा अणु
		result = &afe->result;
		रुको = &afe->रुको;
	पूर्ण

	result->opcode = 0;
	result->status = 0;

	ret = apr_send_pkt(afe->apr, pkt);
	अगर (ret < 0) अणु
		dev_err(afe->dev, "packet not transmitted (%d)\n", ret);
		ret = -EINVAL;
		जाओ err;
	पूर्ण

	ret = रुको_event_समयout(*रुको, (result->opcode == rsp_opcode),
				 msecs_to_jअगरfies(TIMEOUT_MS));
	अगर (!ret) अणु
		ret = -ETIMEDOUT;
	पूर्ण अन्यथा अगर (result->status > 0) अणु
		dev_err(afe->dev, "DSP returned error[%x]\n",
			result->status);
		ret = -EINVAL;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

err:
	mutex_unlock(&afe->lock);

	वापस ret;
पूर्ण

अटल पूर्णांक q6afe_set_param(काष्ठा q6afe *afe, काष्ठा q6afe_port *port,
			   व्योम *data, पूर्णांक param_id, पूर्णांक module_id, पूर्णांक psize,
			   पूर्णांक token)
अणु
	काष्ठा afe_svc_cmd_set_param *param;
	काष्ठा afe_port_param_data_v2 *pdata;
	काष्ठा apr_pkt *pkt;
	पूर्णांक ret, pkt_size;
	व्योम *p, *pl;

	pkt_size = APR_HDR_SIZE + माप(*param) + माप(*pdata) + psize;
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	param = p + APR_HDR_SIZE;
	pdata = p + APR_HDR_SIZE + माप(*param);
	pl = p + APR_HDR_SIZE + माप(*param) + माप(*pdata);
	स_नकल(pl, data, psize);

	pkt->hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD,
					   APR_HDR_LEN(APR_HDR_SIZE),
					   APR_PKT_VER);
	pkt->hdr.pkt_size = pkt_size;
	pkt->hdr.src_port = 0;
	pkt->hdr.dest_port = 0;
	pkt->hdr.token = token;
	pkt->hdr.opcode = AFE_SVC_CMD_SET_PARAM;

	param->payload_size = माप(*pdata) + psize;
	param->payload_address_lsw = 0x00;
	param->payload_address_msw = 0x00;
	param->mem_map_handle = 0x00;
	pdata->module_id = module_id;
	pdata->param_id = param_id;
	pdata->param_size = psize;

	ret = afe_apr_send_pkt(afe, pkt, port, AFE_SVC_CMD_SET_PARAM);
	अगर (ret)
		dev_err(afe->dev, "AFE set params failed %d\n", ret);

	kमुक्त(pkt);
	वापस ret;
पूर्ण

अटल पूर्णांक q6afe_port_set_param(काष्ठा q6afe_port *port, व्योम *data,
				पूर्णांक param_id, पूर्णांक module_id, पूर्णांक psize)
अणु
	वापस q6afe_set_param(port->afe, port, data, param_id, module_id,
			       psize, port->token);
पूर्ण

अटल पूर्णांक q6afe_port_set_param_v2(काष्ठा q6afe_port *port, व्योम *data,
				   पूर्णांक param_id, पूर्णांक module_id, पूर्णांक psize)
अणु
	काष्ठा afe_port_cmd_set_param_v2 *param;
	काष्ठा afe_port_param_data_v2 *pdata;
	काष्ठा q6afe *afe = port->afe;
	काष्ठा apr_pkt *pkt;
	u16 port_id = port->id;
	पूर्णांक ret, pkt_size;
	व्योम *p, *pl;

	pkt_size = APR_HDR_SIZE + माप(*param) + माप(*pdata) + psize;
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	param = p + APR_HDR_SIZE;
	pdata = p + APR_HDR_SIZE + माप(*param);
	pl = p + APR_HDR_SIZE + माप(*param) + माप(*pdata);
	स_नकल(pl, data, psize);

	pkt->hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD,
					   APR_HDR_LEN(APR_HDR_SIZE),
					   APR_PKT_VER);
	pkt->hdr.pkt_size = pkt_size;
	pkt->hdr.src_port = 0;
	pkt->hdr.dest_port = 0;
	pkt->hdr.token = port->token;
	pkt->hdr.opcode = AFE_PORT_CMD_SET_PARAM_V2;

	param->port_id = port_id;
	param->payload_size = माप(*pdata) + psize;
	param->payload_address_lsw = 0x00;
	param->payload_address_msw = 0x00;
	param->mem_map_handle = 0x00;
	pdata->module_id = module_id;
	pdata->param_id = param_id;
	pdata->param_size = psize;

	ret = afe_apr_send_pkt(afe, pkt, port, AFE_PORT_CMD_SET_PARAM_V2);
	अगर (ret)
		dev_err(afe->dev, "AFE enable for port 0x%x failed %d\n",
		       port_id, ret);

	kमुक्त(pkt);
	वापस ret;
पूर्ण

अटल पूर्णांक q6afe_port_set_lpass_घड़ी(काष्ठा q6afe_port *port,
				 काष्ठा afe_clk_cfg *cfg)
अणु
	वापस q6afe_port_set_param_v2(port, cfg,
				       AFE_PARAM_ID_LPAIF_CLK_CONFIG,
				       AFE_MODULE_AUDIO_DEV_INTERFACE,
				       माप(*cfg));
पूर्ण

अटल पूर्णांक q6afe_set_lpass_घड़ी_v2(काष्ठा q6afe_port *port,
				 काष्ठा afe_clk_set *cfg)
अणु
	वापस q6afe_port_set_param(port, cfg, AFE_PARAM_ID_CLOCK_SET,
				    AFE_MODULE_CLOCK_SET, माप(*cfg));
पूर्ण

अटल पूर्णांक q6afe_set_digital_codec_core_घड़ी(काष्ठा q6afe_port *port,
					      काष्ठा afe_digital_clk_cfg *cfg)
अणु
	वापस q6afe_port_set_param_v2(port, cfg,
				       AFE_PARAM_ID_INT_DIGITAL_CDC_CLK_CONFIG,
				       AFE_MODULE_AUDIO_DEV_INTERFACE,
				       माप(*cfg));
पूर्ण

पूर्णांक q6afe_set_lpass_घड़ी(काष्ठा device *dev, पूर्णांक clk_id, पूर्णांक attri,
			  पूर्णांक clk_root, अचिन्हित पूर्णांक freq)
अणु
	काष्ठा q6afe *afe = dev_get_drvdata(dev->parent);
	काष्ठा afe_clk_set cset = अणु0,पूर्ण;

	cset.clk_set_minor_version = AFE_API_VERSION_CLOCK_SET;
	cset.clk_id = clk_id;
	cset.clk_freq_in_hz = freq;
	cset.clk_attri = attri;
	cset.clk_root = clk_root;
	cset.enable = !!freq;

	वापस q6afe_set_param(afe, शून्य, &cset, AFE_PARAM_ID_CLOCK_SET,
			       AFE_MODULE_CLOCK_SET, माप(cset),
			       AFE_CLK_TOKEN);
पूर्ण
EXPORT_SYMBOL_GPL(q6afe_set_lpass_घड़ी);

पूर्णांक q6afe_port_set_sysclk(काष्ठा q6afe_port *port, पूर्णांक clk_id,
			  पूर्णांक clk_src, पूर्णांक clk_root,
			  अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा afe_clk_cfg ccfg = अणु0,पूर्ण;
	काष्ठा afe_clk_set cset = अणु0,पूर्ण;
	काष्ठा afe_digital_clk_cfg dcfg = अणु0,पूर्ण;
	पूर्णांक ret;

	चयन (clk_id) अणु
	हाल LPAIF_DIG_CLK:
		dcfg.i2s_cfg_minor_version = AFE_API_VERSION_I2S_CONFIG;
		dcfg.clk_val = freq;
		dcfg.clk_root = clk_root;
		ret = q6afe_set_digital_codec_core_घड़ी(port, &dcfg);
		अवरोध;
	हाल LPAIF_BIT_CLK:
		ccfg.i2s_cfg_minor_version = AFE_API_VERSION_I2S_CONFIG;
		ccfg.clk_val1 = freq;
		ccfg.clk_src = clk_src;
		ccfg.clk_root = clk_root;
		ccfg.clk_set_mode = Q6AFE_LPASS_MODE_CLK1_VALID;
		ret = q6afe_port_set_lpass_घड़ी(port, &ccfg);
		अवरोध;

	हाल LPAIF_OSR_CLK:
		ccfg.i2s_cfg_minor_version = AFE_API_VERSION_I2S_CONFIG;
		ccfg.clk_val2 = freq;
		ccfg.clk_src = clk_src;
		ccfg.clk_root = clk_root;
		ccfg.clk_set_mode = Q6AFE_LPASS_MODE_CLK2_VALID;
		ret = q6afe_port_set_lpass_घड़ी(port, &ccfg);
		अवरोध;
	हाल Q6AFE_LPASS_CLK_ID_PRI_MI2S_IBIT ... Q6AFE_LPASS_CLK_ID_QUI_MI2S_OSR:
	हाल Q6AFE_LPASS_CLK_ID_MCLK_1 ... Q6AFE_LPASS_CLK_ID_INT_MCLK_1:
	हाल Q6AFE_LPASS_CLK_ID_PRI_TDM_IBIT ... Q6AFE_LPASS_CLK_ID_QUIN_TDM_EBIT:
	हाल Q6AFE_LPASS_CLK_ID_WSA_CORE_MCLK ... Q6AFE_LPASS_CLK_ID_VA_CORE_2X_MCLK:
		cset.clk_set_minor_version = AFE_API_VERSION_CLOCK_SET;
		cset.clk_id = clk_id;
		cset.clk_freq_in_hz = freq;
		cset.clk_attri = clk_src;
		cset.clk_root = clk_root;
		cset.enable = !!freq;
		ret = q6afe_set_lpass_घड़ी_v2(port, &cset);
		अवरोध;
	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(q6afe_port_set_sysclk);

/**
 * q6afe_port_stop() - Stop a afe port
 *
 * @port: Instance of port to stop
 *
 * Return: Will be an negative on packet size on success.
 */
पूर्णांक q6afe_port_stop(काष्ठा q6afe_port *port)
अणु
	काष्ठा afe_port_cmd_device_stop *stop;
	काष्ठा q6afe *afe = port->afe;
	काष्ठा apr_pkt *pkt;
	पूर्णांक port_id = port->id;
	पूर्णांक ret = 0;
	पूर्णांक index, pkt_size;
	व्योम *p;

	index = port->token;
	अगर (index < 0 || index >= AFE_PORT_MAX) अणु
		dev_err(afe->dev, "AFE port index[%d] invalid!\n", index);
		वापस -EINVAL;
	पूर्ण

	pkt_size = APR_HDR_SIZE + माप(*stop);
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	stop = p + APR_HDR_SIZE;

	pkt->hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD,
					   APR_HDR_LEN(APR_HDR_SIZE),
					   APR_PKT_VER);
	pkt->hdr.pkt_size = pkt_size;
	pkt->hdr.src_port = 0;
	pkt->hdr.dest_port = 0;
	pkt->hdr.token = index;
	pkt->hdr.opcode = AFE_PORT_CMD_DEVICE_STOP;
	stop->port_id = port_id;
	stop->reserved = 0;

	ret = afe_apr_send_pkt(afe, pkt, port, AFE_PORT_CMD_DEVICE_STOP);
	अगर (ret)
		dev_err(afe->dev, "AFE close failed %d\n", ret);

	kमुक्त(pkt);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(q6afe_port_stop);

/**
 * q6afe_slim_port_prepare() - Prepare slim afe port.
 *
 * @port: Instance of afe port
 * @cfg: SLIM configuration क्रम the afe port
 *
 */
व्योम q6afe_slim_port_prepare(काष्ठा q6afe_port *port,
			     काष्ठा q6afe_slim_cfg *cfg)
अणु
	जोड़ afe_port_config *pcfg = &port->port_cfg;

	pcfg->slim_cfg.sb_cfg_minor_version = AFE_API_VERSION_SLIMBUS_CONFIG;
	pcfg->slim_cfg.sample_rate = cfg->sample_rate;
	pcfg->slim_cfg.bit_width = cfg->bit_width;
	pcfg->slim_cfg.num_channels = cfg->num_channels;
	pcfg->slim_cfg.data_क्रमmat = cfg->data_क्रमmat;
	pcfg->slim_cfg.shared_ch_mapping[0] = cfg->ch_mapping[0];
	pcfg->slim_cfg.shared_ch_mapping[1] = cfg->ch_mapping[1];
	pcfg->slim_cfg.shared_ch_mapping[2] = cfg->ch_mapping[2];
	pcfg->slim_cfg.shared_ch_mapping[3] = cfg->ch_mapping[3];

पूर्ण
EXPORT_SYMBOL_GPL(q6afe_slim_port_prepare);

/**
 * q6afe_tdm_port_prepare() - Prepare tdm afe port.
 *
 * @port: Instance of afe port
 * @cfg: TDM configuration क्रम the afe port
 *
 */
व्योम q6afe_tdm_port_prepare(काष्ठा q6afe_port *port,
			     काष्ठा q6afe_tdm_cfg *cfg)
अणु
	जोड़ afe_port_config *pcfg = &port->port_cfg;

	pcfg->tdm_cfg.tdm_cfg_minor_version = AFE_API_VERSION_TDM_CONFIG;
	pcfg->tdm_cfg.num_channels = cfg->num_channels;
	pcfg->tdm_cfg.sample_rate = cfg->sample_rate;
	pcfg->tdm_cfg.bit_width = cfg->bit_width;
	pcfg->tdm_cfg.data_क्रमmat = cfg->data_क्रमmat;
	pcfg->tdm_cfg.sync_mode = cfg->sync_mode;
	pcfg->tdm_cfg.sync_src = cfg->sync_src;
	pcfg->tdm_cfg.nslots_per_frame = cfg->nslots_per_frame;

	pcfg->tdm_cfg.slot_width = cfg->slot_width;
	pcfg->tdm_cfg.slot_mask = cfg->slot_mask;
	port->scfg = kzalloc(माप(*port->scfg), GFP_KERNEL);
	अगर (!port->scfg)
		वापस;

	port->scfg->minor_version = AFE_API_VERSION_SLOT_MAPPING_CONFIG;
	port->scfg->num_channels = cfg->num_channels;
	port->scfg->bitwidth = cfg->bit_width;
	port->scfg->data_align_type = cfg->data_align_type;
	स_नकल(port->scfg->ch_mapping, cfg->ch_mapping,
			माप(u16) * AFE_PORT_MAX_AUDIO_CHAN_CNT);
पूर्ण
EXPORT_SYMBOL_GPL(q6afe_tdm_port_prepare);

/**
 * q6afe_hdmi_port_prepare() - Prepare hdmi afe port.
 *
 * @port: Instance of afe port
 * @cfg: HDMI configuration क्रम the afe port
 *
 */
व्योम q6afe_hdmi_port_prepare(काष्ठा q6afe_port *port,
			     काष्ठा q6afe_hdmi_cfg *cfg)
अणु
	जोड़ afe_port_config *pcfg = &port->port_cfg;

	pcfg->hdmi_multi_ch.hdmi_cfg_minor_version =
					AFE_API_VERSION_HDMI_CONFIG;
	pcfg->hdmi_multi_ch.datatype = cfg->datatype;
	pcfg->hdmi_multi_ch.channel_allocation = cfg->channel_allocation;
	pcfg->hdmi_multi_ch.sample_rate = cfg->sample_rate;
	pcfg->hdmi_multi_ch.bit_width = cfg->bit_width;
पूर्ण
EXPORT_SYMBOL_GPL(q6afe_hdmi_port_prepare);

/**
 * q6afe_i2s_port_prepare() - Prepare i2s afe port.
 *
 * @port: Instance of afe port
 * @cfg: I2S configuration क्रम the afe port
 * Return: Will be an negative on error and zero on success.
 */
पूर्णांक q6afe_i2s_port_prepare(काष्ठा q6afe_port *port, काष्ठा q6afe_i2s_cfg *cfg)
अणु
	जोड़ afe_port_config *pcfg = &port->port_cfg;
	काष्ठा device *dev = port->afe->dev;
	पूर्णांक num_sd_lines;

	pcfg->i2s_cfg.i2s_cfg_minor_version = AFE_API_VERSION_I2S_CONFIG;
	pcfg->i2s_cfg.sample_rate = cfg->sample_rate;
	pcfg->i2s_cfg.bit_width = cfg->bit_width;
	pcfg->i2s_cfg.data_क्रमmat = AFE_LINEAR_PCM_DATA;

	चयन (cfg->fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		pcfg->i2s_cfg.ws_src = AFE_PORT_CONFIG_I2S_WS_SRC_INTERNAL;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		/* CPU is slave */
		pcfg->i2s_cfg.ws_src = AFE_PORT_CONFIG_I2S_WS_SRC_EXTERNAL;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	num_sd_lines = hweight_दीर्घ(cfg->sd_line_mask);

	चयन (num_sd_lines) अणु
	हाल 0:
		dev_err(dev, "no line is assigned\n");
		वापस -EINVAL;
	हाल 1:
		चयन (cfg->sd_line_mask) अणु
		हाल AFE_PORT_I2S_SD0_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_SD0;
			अवरोध;
		हाल AFE_PORT_I2S_SD1_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_SD1;
			अवरोध;
		हाल AFE_PORT_I2S_SD2_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_SD2;
			अवरोध;
		हाल AFE_PORT_I2S_SD3_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_SD3;
			अवरोध;
		शेष:
			dev_err(dev, "Invalid SD lines\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल 2:
		चयन (cfg->sd_line_mask) अणु
		हाल AFE_PORT_I2S_SD0_1_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_QUAD01;
			अवरोध;
		हाल AFE_PORT_I2S_SD2_3_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_QUAD23;
			अवरोध;
		शेष:
			dev_err(dev, "Invalid SD lines\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल 3:
		चयन (cfg->sd_line_mask) अणु
		हाल AFE_PORT_I2S_SD0_1_2_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_6CHS;
			अवरोध;
		शेष:
			dev_err(dev, "Invalid SD lines\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल 4:
		चयन (cfg->sd_line_mask) अणु
		हाल AFE_PORT_I2S_SD0_1_2_3_MASK:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_8CHS;

			अवरोध;
		शेष:
			dev_err(dev, "Invalid SD lines\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		dev_err(dev, "Invalid SD lines\n");
		वापस -EINVAL;
	पूर्ण

	चयन (cfg->num_channels) अणु
	हाल 1:
	हाल 2:
		चयन (pcfg->i2s_cfg.channel_mode) अणु
		हाल AFE_PORT_I2S_QUAD01:
		हाल AFE_PORT_I2S_6CHS:
		हाल AFE_PORT_I2S_8CHS:
			pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_SD0;
			अवरोध;
		हाल AFE_PORT_I2S_QUAD23:
				pcfg->i2s_cfg.channel_mode = AFE_PORT_I2S_SD2;
			अवरोध;
		पूर्ण

		अगर (cfg->num_channels == 2)
			pcfg->i2s_cfg.mono_stereo = AFE_PORT_I2S_STEREO;
		अन्यथा
			pcfg->i2s_cfg.mono_stereo = AFE_PORT_I2S_MONO;

		अवरोध;
	हाल 3:
	हाल 4:
		अगर (pcfg->i2s_cfg.channel_mode < AFE_PORT_I2S_QUAD01) अणु
			dev_err(dev, "Invalid Channel mode\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल 5:
	हाल 6:
		अगर (pcfg->i2s_cfg.channel_mode < AFE_PORT_I2S_6CHS) अणु
			dev_err(dev, "Invalid Channel mode\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल 7:
	हाल 8:
		अगर (pcfg->i2s_cfg.channel_mode < AFE_PORT_I2S_8CHS) अणु
			dev_err(dev, "Invalid Channel mode\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(q6afe_i2s_port_prepare);

/**
 * q6afe_cdc_dma_port_prepare() - Prepare dma afe port.
 *
 * @port: Instance of afe port
 * @cfg: DMA configuration क्रम the afe port
 *
 */
व्योम q6afe_cdc_dma_port_prepare(काष्ठा q6afe_port *port,
				काष्ठा q6afe_cdc_dma_cfg *cfg)
अणु
	जोड़ afe_port_config *pcfg = &port->port_cfg;
	काष्ठा afe_param_id_cdc_dma_cfg *dma_cfg = &pcfg->dma_cfg;

	dma_cfg->cdc_dma_cfg_minor_version = AFE_API_VERSION_CODEC_DMA_CONFIG;
	dma_cfg->sample_rate = cfg->sample_rate;
	dma_cfg->bit_width = cfg->bit_width;
	dma_cfg->data_क्रमmat = cfg->data_क्रमmat;
	dma_cfg->num_channels = cfg->num_channels;
	अगर (!cfg->active_channels_mask)
		dma_cfg->active_channels_mask = (1 << cfg->num_channels) - 1;
पूर्ण
EXPORT_SYMBOL_GPL(q6afe_cdc_dma_port_prepare);
/**
 * q6afe_port_start() - Start a afe port
 *
 * @port: Instance of port to start
 *
 * Return: Will be an negative on packet size on success.
 */
पूर्णांक q6afe_port_start(काष्ठा q6afe_port *port)
अणु
	काष्ठा afe_port_cmd_device_start *start;
	काष्ठा q6afe *afe = port->afe;
	पूर्णांक port_id = port->id;
	पूर्णांक ret, param_id = port->cfg_type;
	काष्ठा apr_pkt *pkt;
	पूर्णांक pkt_size;
	व्योम *p;

	ret  = q6afe_port_set_param_v2(port, &port->port_cfg, param_id,
				       AFE_MODULE_AUDIO_DEV_INTERFACE,
				       माप(port->port_cfg));
	अगर (ret) अणु
		dev_err(afe->dev, "AFE enable for port 0x%x failed %d\n",
			port_id, ret);
		वापस ret;
	पूर्ण

	अगर (port->scfg) अणु
		ret  = q6afe_port_set_param_v2(port, port->scfg,
					AFE_PARAM_ID_PORT_SLOT_MAPPING_CONFIG,
					AFE_MODULE_TDM, माप(*port->scfg));
		अगर (ret) अणु
			dev_err(afe->dev, "AFE enable for port 0x%x failed %d\n",
			port_id, ret);
			वापस ret;
		पूर्ण
	पूर्ण

	pkt_size = APR_HDR_SIZE + माप(*start);
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	start = p + APR_HDR_SIZE;

	pkt->hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD,
					    APR_HDR_LEN(APR_HDR_SIZE),
					    APR_PKT_VER);
	pkt->hdr.pkt_size = pkt_size;
	pkt->hdr.src_port = 0;
	pkt->hdr.dest_port = 0;
	pkt->hdr.token = port->token;
	pkt->hdr.opcode = AFE_PORT_CMD_DEVICE_START;

	start->port_id = port_id;

	ret = afe_apr_send_pkt(afe, pkt, port, AFE_PORT_CMD_DEVICE_START);
	अगर (ret)
		dev_err(afe->dev, "AFE enable for port 0x%x failed %d\n",
			port_id, ret);

	kमुक्त(pkt);
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(q6afe_port_start);

/**
 * q6afe_port_get_from_id() - Get port instance from a port id
 *
 * @dev: Poपूर्णांकer to afe child device.
 * @id: port id
 *
 * Return: Will be an error poपूर्णांकer on error or a valid afe port
 * on success.
 */
काष्ठा q6afe_port *q6afe_port_get_from_id(काष्ठा device *dev, पूर्णांक id)
अणु
	पूर्णांक port_id;
	काष्ठा q6afe *afe = dev_get_drvdata(dev->parent);
	काष्ठा q6afe_port *port;
	अचिन्हित दीर्घ flags;
	पूर्णांक cfg_type;

	अगर (id < 0 || id >= AFE_PORT_MAX) अणु
		dev_err(dev, "AFE port token[%d] invalid!\n", id);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	/* अगर port is multiple बार bind/unbind beक्रमe callback finishes */
	port = q6afe_find_port(afe, id);
	अगर (port) अणु
		dev_err(dev, "AFE Port already open\n");
		वापस port;
	पूर्ण

	port_id = port_maps[id].port_id;

	चयन (port_id) अणु
	हाल AFE_PORT_ID_MULTICHAN_HDMI_RX:
	हाल AFE_PORT_ID_HDMI_OVER_DP_RX:
		cfg_type = AFE_PARAM_ID_HDMI_CONFIG;
		अवरोध;
	हाल AFE_PORT_ID_SLIMBUS_MULTI_CHAN_0_TX:
	हाल AFE_PORT_ID_SLIMBUS_MULTI_CHAN_1_TX:
	हाल AFE_PORT_ID_SLIMBUS_MULTI_CHAN_2_TX:
	हाल AFE_PORT_ID_SLIMBUS_MULTI_CHAN_3_TX:
	हाल AFE_PORT_ID_SLIMBUS_MULTI_CHAN_4_TX:
	हाल AFE_PORT_ID_SLIMBUS_MULTI_CHAN_5_TX:
	हाल AFE_PORT_ID_SLIMBUS_MULTI_CHAN_6_TX:
	हाल AFE_PORT_ID_SLIMBUS_MULTI_CHAN_0_RX:
	हाल AFE_PORT_ID_SLIMBUS_MULTI_CHAN_1_RX:
	हाल AFE_PORT_ID_SLIMBUS_MULTI_CHAN_2_RX:
	हाल AFE_PORT_ID_SLIMBUS_MULTI_CHAN_3_RX:
	हाल AFE_PORT_ID_SLIMBUS_MULTI_CHAN_4_RX:
	हाल AFE_PORT_ID_SLIMBUS_MULTI_CHAN_5_RX:
	हाल AFE_PORT_ID_SLIMBUS_MULTI_CHAN_6_RX:
		cfg_type = AFE_PARAM_ID_SLIMBUS_CONFIG;
		अवरोध;

	हाल AFE_PORT_ID_PRIMARY_MI2S_RX:
	हाल AFE_PORT_ID_PRIMARY_MI2S_TX:
	हाल AFE_PORT_ID_SECONDARY_MI2S_RX:
	हाल AFE_PORT_ID_SECONDARY_MI2S_TX:
	हाल AFE_PORT_ID_TERTIARY_MI2S_RX:
	हाल AFE_PORT_ID_TERTIARY_MI2S_TX:
	हाल AFE_PORT_ID_QUATERNARY_MI2S_RX:
	हाल AFE_PORT_ID_QUATERNARY_MI2S_TX:
		cfg_type = AFE_PARAM_ID_I2S_CONFIG;
		अवरोध;
	हाल AFE_PORT_ID_PRIMARY_TDM_RX ... AFE_PORT_ID_QUINARY_TDM_TX_7:
		cfg_type = AFE_PARAM_ID_TDM_CONFIG;
		अवरोध;
	हाल AFE_PORT_ID_WSA_CODEC_DMA_RX_0 ... AFE_PORT_ID_RX_CODEC_DMA_RX_7:
		cfg_type = AFE_PARAM_ID_CODEC_DMA_CONFIG;
	अवरोध;
	शेष:
		dev_err(dev, "Invalid port id 0x%x\n", port_id);
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	port = kzalloc(माप(*port), GFP_KERNEL);
	अगर (!port)
		वापस ERR_PTR(-ENOMEM);

	init_रुकोqueue_head(&port->रुको);

	port->token = id;
	port->id = port_id;
	port->afe = afe;
	port->cfg_type = cfg_type;
	kref_init(&port->refcount);

	spin_lock_irqsave(&afe->port_list_lock, flags);
	list_add_tail(&port->node, &afe->port_list);
	spin_unlock_irqrestore(&afe->port_list_lock, flags);

	वापस port;

पूर्ण
EXPORT_SYMBOL_GPL(q6afe_port_get_from_id);

/**
 * q6afe_port_put() - Release port reference
 *
 * @port: Instance of port to put
 */
व्योम q6afe_port_put(काष्ठा q6afe_port *port)
अणु
	kref_put(&port->refcount, q6afe_port_मुक्त);
पूर्ण
EXPORT_SYMBOL_GPL(q6afe_port_put);

पूर्णांक q6afe_unvote_lpass_core_hw(काष्ठा device *dev, uपूर्णांक32_t hw_block_id,
			       uपूर्णांक32_t client_handle)
अणु
	काष्ठा q6afe *afe = dev_get_drvdata(dev->parent);
	काष्ठा afe_cmd_remote_lpass_core_hw_devote_request *vote_cfg;
	काष्ठा apr_pkt *pkt;
	पूर्णांक ret = 0;
	पूर्णांक pkt_size;
	व्योम *p;

	pkt_size = APR_HDR_SIZE + माप(*vote_cfg);
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	vote_cfg = p + APR_HDR_SIZE;

	pkt->hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD,
					   APR_HDR_LEN(APR_HDR_SIZE),
					   APR_PKT_VER);
	pkt->hdr.pkt_size = pkt_size;
	pkt->hdr.src_port = 0;
	pkt->hdr.dest_port = 0;
	pkt->hdr.token = hw_block_id;
	pkt->hdr.opcode = AFE_CMD_REMOTE_LPASS_CORE_HW_DEVOTE_REQUEST;
	vote_cfg->hw_block_id = hw_block_id;
	vote_cfg->client_handle = client_handle;

	ret = apr_send_pkt(afe->apr, pkt);
	अगर (ret < 0)
		dev_err(afe->dev, "AFE failed to unvote (%d)\n", hw_block_id);

	kमुक्त(pkt);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(q6afe_unvote_lpass_core_hw);

पूर्णांक q6afe_vote_lpass_core_hw(काष्ठा device *dev, uपूर्णांक32_t hw_block_id,
			     स्थिर अक्षर *client_name, uपूर्णांक32_t *client_handle)
अणु
	काष्ठा q6afe *afe = dev_get_drvdata(dev->parent);
	काष्ठा afe_cmd_remote_lpass_core_hw_vote_request *vote_cfg;
	काष्ठा apr_pkt *pkt;
	पूर्णांक ret = 0;
	पूर्णांक pkt_size;
	व्योम *p;

	pkt_size = APR_HDR_SIZE + माप(*vote_cfg);
	p = kzalloc(pkt_size, GFP_KERNEL);
	अगर (!p)
		वापस -ENOMEM;

	pkt = p;
	vote_cfg = p + APR_HDR_SIZE;

	pkt->hdr.hdr_field = APR_HDR_FIELD(APR_MSG_TYPE_SEQ_CMD,
					   APR_HDR_LEN(APR_HDR_SIZE),
					   APR_PKT_VER);
	pkt->hdr.pkt_size = pkt_size;
	pkt->hdr.src_port = 0;
	pkt->hdr.dest_port = 0;
	pkt->hdr.token = hw_block_id;
	pkt->hdr.opcode = AFE_CMD_REMOTE_LPASS_CORE_HW_VOTE_REQUEST;
	vote_cfg->hw_block_id = hw_block_id;
	strscpy(vote_cfg->client_name, client_name,
			माप(vote_cfg->client_name));

	ret = afe_apr_send_pkt(afe, pkt, शून्य,
			       AFE_CMD_RSP_REMOTE_LPASS_CORE_HW_VOTE_REQUEST);
	अगर (ret)
		dev_err(afe->dev, "AFE failed to vote (%d)\n", hw_block_id);


	kमुक्त(pkt);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(q6afe_vote_lpass_core_hw);

अटल पूर्णांक q6afe_probe(काष्ठा apr_device *adev)
अणु
	काष्ठा q6afe *afe;
	काष्ठा device *dev = &adev->dev;

	afe = devm_kzalloc(dev, माप(*afe), GFP_KERNEL);
	अगर (!afe)
		वापस -ENOMEM;

	q6core_get_svc_api_info(adev->svc_id, &afe->ainfo);
	afe->apr = adev;
	mutex_init(&afe->lock);
	init_रुकोqueue_head(&afe->रुको);
	afe->dev = dev;
	INIT_LIST_HEAD(&afe->port_list);
	spin_lock_init(&afe->port_list_lock);

	dev_set_drvdata(dev, afe);

	वापस devm_of_platक्रमm_populate(dev);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id q6afe_device_id[]  = अणु
	अणु .compatible = "qcom,q6afe" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, q6afe_device_id);
#पूर्ण_अगर

अटल काष्ठा apr_driver qcom_q6afe_driver = अणु
	.probe = q6afe_probe,
	.callback = q6afe_callback,
	.driver = अणु
		.name = "qcom-q6afe",
		.of_match_table = of_match_ptr(q6afe_device_id),

	पूर्ण,
पूर्ण;

module_apr_driver(qcom_q6afe_driver);
MODULE_DESCRIPTION("Q6 Audio Front End");
MODULE_LICENSE("GPL v2");
