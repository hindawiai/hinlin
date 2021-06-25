<शैली गुरु>
/*
 * Copyright (C) 2014-2015 Broadcom Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 */
#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "cygnus-ssp.h"

#घोषणा DEFAULT_VCO    1354750204

#घोषणा CAPTURE_FCI_ID_BASE 0x180
#घोषणा CYGNUS_SSP_TRISTATE_MASK 0x001fff
#घोषणा CYGNUS_PLLCLKSEL_MASK 0xf

/* Used with stream_on field to indicate which streams are active */
#घोषणा  PLAYBACK_STREAM_MASK   BIT(0)
#घोषणा  CAPTURE_STREAM_MASK    BIT(1)

#घोषणा I2S_STREAM_CFG_MASK      0xff003ff
#घोषणा I2S_CAP_STREAM_CFG_MASK  0xf0
#घोषणा SPDIF_STREAM_CFG_MASK    0x3ff
#घोषणा CH_GRP_STEREO            0x1

/* Begin रेजिस्टर offset defines */
#घोषणा AUD_MISC_SEROUT_OE_REG_BASE  0x01c
#घोषणा AUD_MISC_SEROUT_SPDIF_OE  12
#घोषणा AUD_MISC_SEROUT_MCLK_OE   3
#घोषणा AUD_MISC_SEROUT_LRCK_OE   2
#घोषणा AUD_MISC_SEROUT_SCLK_OE   1
#घोषणा AUD_MISC_SEROUT_SDAT_OE   0

/* AUD_FMM_BF_CTRL_xxx regs */
#घोषणा BF_DST_CFG0_OFFSET  0x100
#घोषणा BF_DST_CFG1_OFFSET  0x104
#घोषणा BF_DST_CFG2_OFFSET  0x108

#घोषणा BF_DST_CTRL0_OFFSET 0x130
#घोषणा BF_DST_CTRL1_OFFSET 0x134
#घोषणा BF_DST_CTRL2_OFFSET 0x138

#घोषणा BF_SRC_CFG0_OFFSET  0x148
#घोषणा BF_SRC_CFG1_OFFSET  0x14c
#घोषणा BF_SRC_CFG2_OFFSET  0x150
#घोषणा BF_SRC_CFG3_OFFSET  0x154

#घोषणा BF_SRC_CTRL0_OFFSET 0x1c0
#घोषणा BF_SRC_CTRL1_OFFSET 0x1c4
#घोषणा BF_SRC_CTRL2_OFFSET 0x1c8
#घोषणा BF_SRC_CTRL3_OFFSET 0x1cc

#घोषणा BF_SRC_GRP0_OFFSET  0x1fc
#घोषणा BF_SRC_GRP1_OFFSET  0x200
#घोषणा BF_SRC_GRP2_OFFSET  0x204
#घोषणा BF_SRC_GRP3_OFFSET  0x208

#घोषणा BF_SRC_GRP_EN_OFFSET        0x320
#घोषणा BF_SRC_GRP_FLOWON_OFFSET    0x324
#घोषणा BF_SRC_GRP_SYNC_DIS_OFFSET  0x328

/* AUD_FMM_IOP_OUT_I2S_xxx regs */
#घोषणा OUT_I2S_0_STREAM_CFG_OFFSET 0xa00
#घोषणा OUT_I2S_0_CFG_OFFSET        0xa04
#घोषणा OUT_I2S_0_MCLK_CFG_OFFSET   0xa0c

#घोषणा OUT_I2S_1_STREAM_CFG_OFFSET 0xa40
#घोषणा OUT_I2S_1_CFG_OFFSET        0xa44
#घोषणा OUT_I2S_1_MCLK_CFG_OFFSET   0xa4c

#घोषणा OUT_I2S_2_STREAM_CFG_OFFSET 0xa80
#घोषणा OUT_I2S_2_CFG_OFFSET        0xa84
#घोषणा OUT_I2S_2_MCLK_CFG_OFFSET   0xa8c

/* AUD_FMM_IOP_OUT_SPDIF_xxx regs */
#घोषणा SPDIF_STREAM_CFG_OFFSET  0xac0
#घोषणा SPDIF_CTRL_OFFSET        0xac4
#घोषणा SPDIF_FORMAT_CFG_OFFSET  0xad8
#घोषणा SPDIF_MCLK_CFG_OFFSET    0xadc

/* AUD_FMM_IOP_PLL_0_xxx regs */
#घोषणा IOP_PLL_0_MACRO_OFFSET    0xb00
#घोषणा IOP_PLL_0_MDIV_Ch0_OFFSET 0xb14
#घोषणा IOP_PLL_0_MDIV_Ch1_OFFSET 0xb18
#घोषणा IOP_PLL_0_MDIV_Ch2_OFFSET 0xb1c

#घोषणा IOP_PLL_0_ACTIVE_MDIV_Ch0_OFFSET 0xb30
#घोषणा IOP_PLL_0_ACTIVE_MDIV_Ch1_OFFSET 0xb34
#घोषणा IOP_PLL_0_ACTIVE_MDIV_Ch2_OFFSET 0xb38

/* AUD_FMM_IOP_xxx regs */
#घोषणा IOP_PLL_0_CONTROL_OFFSET     0xb04
#घोषणा IOP_PLL_0_USER_NDIV_OFFSET   0xb08
#घोषणा IOP_PLL_0_ACTIVE_NDIV_OFFSET 0xb20
#घोषणा IOP_PLL_0_RESET_OFFSET       0xb5c

/* AUD_FMM_IOP_IN_I2S_xxx regs */
#घोषणा IN_I2S_0_STREAM_CFG_OFFSET 0x00
#घोषणा IN_I2S_0_CFG_OFFSET        0x04
#घोषणा IN_I2S_1_STREAM_CFG_OFFSET 0x40
#घोषणा IN_I2S_1_CFG_OFFSET        0x44
#घोषणा IN_I2S_2_STREAM_CFG_OFFSET 0x80
#घोषणा IN_I2S_2_CFG_OFFSET        0x84

/* AUD_FMM_IOP_MISC_xxx regs */
#घोषणा IOP_SW_INIT_LOGIC          0x1c0

/* End रेजिस्टर offset defines */


/* AUD_FMM_IOP_OUT_I2S_x_MCLK_CFG_0_REG */
#घोषणा I2S_OUT_MCLKRATE_SHIFT 16

/* AUD_FMM_IOP_OUT_I2S_x_MCLK_CFG_REG */
#घोषणा I2S_OUT_PLLCLKSEL_SHIFT  0

/* AUD_FMM_IOP_OUT_I2S_x_STREAM_CFG */
#घोषणा I2S_OUT_STREAM_ENA  31
#घोषणा I2S_OUT_STREAM_CFG_GROUP_ID  20
#घोषणा I2S_OUT_STREAM_CFG_CHANNEL_GROUPING  24

/* AUD_FMM_IOP_IN_I2S_x_CAP */
#घोषणा I2S_IN_STREAM_CFG_CAP_ENA   31
#घोषणा I2S_IN_STREAM_CFG_0_GROUP_ID 4

/* AUD_FMM_IOP_OUT_I2S_x_I2S_CFG_REG */
#घोषणा I2S_OUT_CFGX_CLK_ENA         0
#घोषणा I2S_OUT_CFGX_DATA_ENABLE     1
#घोषणा I2S_OUT_CFGX_DATA_ALIGNMENT  6
#घोषणा I2S_OUT_CFGX_BITS_PER_SLOT  13
#घोषणा I2S_OUT_CFGX_VALID_SLOT     14
#घोषणा I2S_OUT_CFGX_FSYNC_WIDTH    18
#घोषणा I2S_OUT_CFGX_SCLKS_PER_1FS_DIV32 26
#घोषणा I2S_OUT_CFGX_SLAVE_MODE     30
#घोषणा I2S_OUT_CFGX_TDM_MODE       31

/* AUD_FMM_BF_CTRL_SOURCECH_CFGx_REG */
#घोषणा BF_SRC_CFGX_SFIFO_ENA              0
#घोषणा BF_SRC_CFGX_BUFFER_PAIR_ENABLE     1
#घोषणा BF_SRC_CFGX_SAMPLE_CH_MODE         2
#घोषणा BF_SRC_CFGX_SFIFO_SZ_DOUBLE        5
#घोषणा BF_SRC_CFGX_NOT_PAUSE_WHEN_EMPTY  10
#घोषणा BF_SRC_CFGX_BIT_RES               20
#घोषणा BF_SRC_CFGX_PROCESS_SEQ_ID_VALID  31

/* AUD_FMM_BF_CTRL_DESTCH_CFGx_REG */
#घोषणा BF_DST_CFGX_CAP_ENA              0
#घोषणा BF_DST_CFGX_BUFFER_PAIR_ENABLE   1
#घोषणा BF_DST_CFGX_DFIFO_SZ_DOUBLE      2
#घोषणा BF_DST_CFGX_NOT_PAUSE_WHEN_FULL 11
#घोषणा BF_DST_CFGX_FCI_ID              12
#घोषणा BF_DST_CFGX_CAP_MODE            24
#घोषणा BF_DST_CFGX_PROC_SEQ_ID_VALID   31

/* AUD_FMM_IOP_OUT_SPDIF_xxx */
#घोषणा SPDIF_0_OUT_DITHER_ENA     3
#घोषणा SPDIF_0_OUT_STREAM_ENA    31

/* AUD_FMM_IOP_PLL_0_USER */
#घोषणा IOP_PLL_0_USER_NDIV_FRAC   10

/* AUD_FMM_IOP_PLL_0_ACTIVE */
#घोषणा IOP_PLL_0_ACTIVE_NDIV_FRAC 10


#घोषणा INIT_SSP_REGS(num) (काष्ठा cygnus_ssp_regs)अणु \
		.i2s_stream_cfg = OUT_I2S_ ##num## _STREAM_CFG_OFFSET, \
		.i2s_cap_stream_cfg = IN_I2S_ ##num## _STREAM_CFG_OFFSET, \
		.i2s_cfg = OUT_I2S_ ##num## _CFG_OFFSET, \
		.i2s_cap_cfg = IN_I2S_ ##num## _CFG_OFFSET, \
		.i2s_mclk_cfg = OUT_I2S_ ##num## _MCLK_CFG_OFFSET, \
		.bf_destch_ctrl = BF_DST_CTRL ##num## _OFFSET, \
		.bf_destch_cfg = BF_DST_CFG ##num## _OFFSET, \
		.bf_sourcech_ctrl = BF_SRC_CTRL ##num## _OFFSET, \
		.bf_sourcech_cfg = BF_SRC_CFG ##num## _OFFSET, \
		.bf_sourcech_grp = BF_SRC_GRP ##num## _OFFSET \
पूर्ण

काष्ठा pll_macro_entry अणु
	u32 mclk;
	u32 pll_ch_num;
पूर्ण;

/*
 * PLL has 3 output channels (1x, 2x, and 4x). Below are
 * the common MCLK frequencies used by audio driver
 */
अटल स्थिर काष्ठा pll_macro_entry pll_predef_mclk[] = अणु
	अणु 4096000, 0पूर्ण,
	अणु 8192000, 1पूर्ण,
	अणु16384000, 2पूर्ण,

	अणु 5644800, 0पूर्ण,
	अणु11289600, 1पूर्ण,
	अणु22579200, 2पूर्ण,

	अणु 6144000, 0पूर्ण,
	अणु12288000, 1पूर्ण,
	अणु24576000, 2पूर्ण,

	अणु12288000, 0पूर्ण,
	अणु24576000, 1पूर्ण,
	अणु49152000, 2पूर्ण,

	अणु22579200, 0पूर्ण,
	अणु45158400, 1पूर्ण,
	अणु90316800, 2पूर्ण,

	अणु24576000, 0पूर्ण,
	अणु49152000, 1पूर्ण,
	अणु98304000, 2पूर्ण,
पूर्ण;

#घोषणा CYGNUS_RATE_MIN     8000
#घोषणा CYGNUS_RATE_MAX   384000

/* List of valid frame sizes क्रम tdm mode */
अटल स्थिर पूर्णांक ssp_valid_tdm_framesize[] = अणु32, 64, 128, 256, 512पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक cygnus_rates[] = अणु
	 8000, 11025,  16000,  22050,  32000,  44100, 48000,
	88200, 96000, 176400, 192000, 352800, 384000
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list cygnus_rate_स्थिरraपूर्णांक = अणु
	.count = ARRAY_SIZE(cygnus_rates),
	.list = cygnus_rates,
पूर्ण;

अटल काष्ठा cygnus_aio_port *cygnus_dai_get_portinfo(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा cygnus_audio *cygaud = snd_soc_dai_get_drvdata(dai);

	वापस &cygaud->portinfo[dai->id];
पूर्ण

अटल पूर्णांक audio_ssp_init_portregs(काष्ठा cygnus_aio_port *aio)
अणु
	u32 value, fci_id;
	पूर्णांक status = 0;

	चयन (aio->port_type) अणु
	हाल PORT_TDM:
		value = पढ़ोl(aio->cygaud->audio + aio->regs.i2s_stream_cfg);
		value &= ~I2S_STREAM_CFG_MASK;

		/* Set Group ID */
		ग_लिखोl(aio->portnum,
			aio->cygaud->audio + aio->regs.bf_sourcech_grp);

		/* Configure the AUD_FMM_IOP_OUT_I2S_x_STREAM_CFG reg */
		value |= aio->portnum << I2S_OUT_STREAM_CFG_GROUP_ID;
		value |= aio->portnum; /* FCI ID is the port num */
		value |= CH_GRP_STEREO << I2S_OUT_STREAM_CFG_CHANNEL_GROUPING;
		ग_लिखोl(value, aio->cygaud->audio + aio->regs.i2s_stream_cfg);

		/* Configure the AUD_FMM_BF_CTRL_SOURCECH_CFGX reg */
		value = पढ़ोl(aio->cygaud->audio + aio->regs.bf_sourcech_cfg);
		value &= ~BIT(BF_SRC_CFGX_NOT_PAUSE_WHEN_EMPTY);
		value |= BIT(BF_SRC_CFGX_SFIFO_SZ_DOUBLE);
		value |= BIT(BF_SRC_CFGX_PROCESS_SEQ_ID_VALID);
		ग_लिखोl(value, aio->cygaud->audio + aio->regs.bf_sourcech_cfg);

		/* Configure the AUD_FMM_IOP_IN_I2S_x_CAP_STREAM_CFG_0 reg */
		value = पढ़ोl(aio->cygaud->i2s_in +
			aio->regs.i2s_cap_stream_cfg);
		value &= ~I2S_CAP_STREAM_CFG_MASK;
		value |= aio->portnum << I2S_IN_STREAM_CFG_0_GROUP_ID;
		ग_लिखोl(value, aio->cygaud->i2s_in +
			aio->regs.i2s_cap_stream_cfg);

		/* Configure the AUD_FMM_BF_CTRL_DESTCH_CFGX_REG_BASE reg */
		fci_id = CAPTURE_FCI_ID_BASE + aio->portnum;

		value = पढ़ोl(aio->cygaud->audio + aio->regs.bf_destch_cfg);
		value |= BIT(BF_DST_CFGX_DFIFO_SZ_DOUBLE);
		value &= ~BIT(BF_DST_CFGX_NOT_PAUSE_WHEN_FULL);
		value |= (fci_id << BF_DST_CFGX_FCI_ID);
		value |= BIT(BF_DST_CFGX_PROC_SEQ_ID_VALID);
		ग_लिखोl(value, aio->cygaud->audio + aio->regs.bf_destch_cfg);

		/* Enable the transmit pin क्रम this port */
		value = पढ़ोl(aio->cygaud->audio + AUD_MISC_SEROUT_OE_REG_BASE);
		value &= ~BIT((aio->portnum * 4) + AUD_MISC_SEROUT_SDAT_OE);
		ग_लिखोl(value, aio->cygaud->audio + AUD_MISC_SEROUT_OE_REG_BASE);
		अवरोध;
	हाल PORT_SPDIF:
		ग_लिखोl(aio->portnum, aio->cygaud->audio + BF_SRC_GRP3_OFFSET);

		value = पढ़ोl(aio->cygaud->audio + SPDIF_CTRL_OFFSET);
		value |= BIT(SPDIF_0_OUT_DITHER_ENA);
		ग_लिखोl(value, aio->cygaud->audio + SPDIF_CTRL_OFFSET);

		/* Enable and set the FCI ID क्रम the SPDIF channel */
		value = पढ़ोl(aio->cygaud->audio + SPDIF_STREAM_CFG_OFFSET);
		value &= ~SPDIF_STREAM_CFG_MASK;
		value |= aio->portnum; /* FCI ID is the port num */
		value |= BIT(SPDIF_0_OUT_STREAM_ENA);
		ग_लिखोl(value, aio->cygaud->audio + SPDIF_STREAM_CFG_OFFSET);

		value = पढ़ोl(aio->cygaud->audio + aio->regs.bf_sourcech_cfg);
		value &= ~BIT(BF_SRC_CFGX_NOT_PAUSE_WHEN_EMPTY);
		value |= BIT(BF_SRC_CFGX_SFIFO_SZ_DOUBLE);
		value |= BIT(BF_SRC_CFGX_PROCESS_SEQ_ID_VALID);
		ग_लिखोl(value, aio->cygaud->audio + aio->regs.bf_sourcech_cfg);

		/* Enable the spdअगर output pin */
		value = पढ़ोl(aio->cygaud->audio + AUD_MISC_SEROUT_OE_REG_BASE);
		value &= ~BIT(AUD_MISC_SEROUT_SPDIF_OE);
		ग_लिखोl(value, aio->cygaud->audio + AUD_MISC_SEROUT_OE_REG_BASE);
		अवरोध;
	शेष:
		dev_err(aio->cygaud->dev, "Port not supported\n");
		status = -EINVAL;
	पूर्ण

	वापस status;
पूर्ण

अटल व्योम audio_ssp_in_enable(काष्ठा cygnus_aio_port *aio)
अणु
	u32 value;

	value = पढ़ोl(aio->cygaud->audio + aio->regs.bf_destch_cfg);
	value |= BIT(BF_DST_CFGX_CAP_ENA);
	ग_लिखोl(value, aio->cygaud->audio + aio->regs.bf_destch_cfg);

	ग_लिखोl(0x1, aio->cygaud->audio + aio->regs.bf_destch_ctrl);

	value = पढ़ोl(aio->cygaud->audio + aio->regs.i2s_cfg);
	value |= BIT(I2S_OUT_CFGX_CLK_ENA);
	value |= BIT(I2S_OUT_CFGX_DATA_ENABLE);
	ग_लिखोl(value, aio->cygaud->audio + aio->regs.i2s_cfg);

	value = पढ़ोl(aio->cygaud->i2s_in + aio->regs.i2s_cap_stream_cfg);
	value |= BIT(I2S_IN_STREAM_CFG_CAP_ENA);
	ग_लिखोl(value, aio->cygaud->i2s_in + aio->regs.i2s_cap_stream_cfg);

	aio->streams_on |= CAPTURE_STREAM_MASK;
पूर्ण

अटल व्योम audio_ssp_in_disable(काष्ठा cygnus_aio_port *aio)
अणु
	u32 value;

	value = पढ़ोl(aio->cygaud->i2s_in + aio->regs.i2s_cap_stream_cfg);
	value &= ~BIT(I2S_IN_STREAM_CFG_CAP_ENA);
	ग_लिखोl(value, aio->cygaud->i2s_in + aio->regs.i2s_cap_stream_cfg);

	aio->streams_on &= ~CAPTURE_STREAM_MASK;

	/* If both playback and capture are off */
	अगर (!aio->streams_on) अणु
		value = पढ़ोl(aio->cygaud->audio + aio->regs.i2s_cfg);
		value &= ~BIT(I2S_OUT_CFGX_CLK_ENA);
		value &= ~BIT(I2S_OUT_CFGX_DATA_ENABLE);
		ग_लिखोl(value, aio->cygaud->audio + aio->regs.i2s_cfg);
	पूर्ण

	ग_लिखोl(0x0, aio->cygaud->audio + aio->regs.bf_destch_ctrl);

	value = पढ़ोl(aio->cygaud->audio + aio->regs.bf_destch_cfg);
	value &= ~BIT(BF_DST_CFGX_CAP_ENA);
	ग_लिखोl(value, aio->cygaud->audio + aio->regs.bf_destch_cfg);
पूर्ण

अटल पूर्णांक audio_ssp_out_enable(काष्ठा cygnus_aio_port *aio)
अणु
	u32 value;
	पूर्णांक status = 0;

	चयन (aio->port_type) अणु
	हाल PORT_TDM:
		value = पढ़ोl(aio->cygaud->audio + aio->regs.i2s_stream_cfg);
		value |= BIT(I2S_OUT_STREAM_ENA);
		ग_लिखोl(value, aio->cygaud->audio + aio->regs.i2s_stream_cfg);

		ग_लिखोl(1, aio->cygaud->audio + aio->regs.bf_sourcech_ctrl);

		value = पढ़ोl(aio->cygaud->audio + aio->regs.i2s_cfg);
		value |= BIT(I2S_OUT_CFGX_CLK_ENA);
		value |= BIT(I2S_OUT_CFGX_DATA_ENABLE);
		ग_लिखोl(value, aio->cygaud->audio + aio->regs.i2s_cfg);

		value = पढ़ोl(aio->cygaud->audio + aio->regs.bf_sourcech_cfg);
		value |= BIT(BF_SRC_CFGX_SFIFO_ENA);
		ग_लिखोl(value, aio->cygaud->audio + aio->regs.bf_sourcech_cfg);

		aio->streams_on |= PLAYBACK_STREAM_MASK;
		अवरोध;
	हाल PORT_SPDIF:
		value = पढ़ोl(aio->cygaud->audio + SPDIF_FORMAT_CFG_OFFSET);
		value |= 0x3;
		ग_लिखोl(value, aio->cygaud->audio + SPDIF_FORMAT_CFG_OFFSET);

		ग_लिखोl(1, aio->cygaud->audio + aio->regs.bf_sourcech_ctrl);

		value = पढ़ोl(aio->cygaud->audio + aio->regs.bf_sourcech_cfg);
		value |= BIT(BF_SRC_CFGX_SFIFO_ENA);
		ग_लिखोl(value, aio->cygaud->audio + aio->regs.bf_sourcech_cfg);
		अवरोध;
	शेष:
		dev_err(aio->cygaud->dev,
			"Port not supported %d\n", aio->portnum);
		status = -EINVAL;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक audio_ssp_out_disable(काष्ठा cygnus_aio_port *aio)
अणु
	u32 value;
	पूर्णांक status = 0;

	चयन (aio->port_type) अणु
	हाल PORT_TDM:
		aio->streams_on &= ~PLAYBACK_STREAM_MASK;

		/* If both playback and capture are off */
		अगर (!aio->streams_on) अणु
			value = पढ़ोl(aio->cygaud->audio + aio->regs.i2s_cfg);
			value &= ~BIT(I2S_OUT_CFGX_CLK_ENA);
			value &= ~BIT(I2S_OUT_CFGX_DATA_ENABLE);
			ग_लिखोl(value, aio->cygaud->audio + aio->regs.i2s_cfg);
		पूर्ण

		/* set group_sync_dis = 1 */
		value = पढ़ोl(aio->cygaud->audio + BF_SRC_GRP_SYNC_DIS_OFFSET);
		value |= BIT(aio->portnum);
		ग_लिखोl(value, aio->cygaud->audio + BF_SRC_GRP_SYNC_DIS_OFFSET);

		ग_लिखोl(0, aio->cygaud->audio + aio->regs.bf_sourcech_ctrl);

		value = पढ़ोl(aio->cygaud->audio + aio->regs.bf_sourcech_cfg);
		value &= ~BIT(BF_SRC_CFGX_SFIFO_ENA);
		ग_लिखोl(value, aio->cygaud->audio + aio->regs.bf_sourcech_cfg);

		/* set group_sync_dis = 0 */
		value = पढ़ोl(aio->cygaud->audio + BF_SRC_GRP_SYNC_DIS_OFFSET);
		value &= ~BIT(aio->portnum);
		ग_लिखोl(value, aio->cygaud->audio + BF_SRC_GRP_SYNC_DIS_OFFSET);

		value = पढ़ोl(aio->cygaud->audio + aio->regs.i2s_stream_cfg);
		value &= ~BIT(I2S_OUT_STREAM_ENA);
		ग_लिखोl(value, aio->cygaud->audio + aio->regs.i2s_stream_cfg);

		/* IOP SW INIT on OUT_I2S_x */
		value = पढ़ोl(aio->cygaud->i2s_in + IOP_SW_INIT_LOGIC);
		value |= BIT(aio->portnum);
		ग_लिखोl(value, aio->cygaud->i2s_in + IOP_SW_INIT_LOGIC);
		value &= ~BIT(aio->portnum);
		ग_लिखोl(value, aio->cygaud->i2s_in + IOP_SW_INIT_LOGIC);
		अवरोध;
	हाल PORT_SPDIF:
		value = पढ़ोl(aio->cygaud->audio + SPDIF_FORMAT_CFG_OFFSET);
		value &= ~0x3;
		ग_लिखोl(value, aio->cygaud->audio + SPDIF_FORMAT_CFG_OFFSET);
		ग_लिखोl(0, aio->cygaud->audio + aio->regs.bf_sourcech_ctrl);

		value = पढ़ोl(aio->cygaud->audio + aio->regs.bf_sourcech_cfg);
		value &= ~BIT(BF_SRC_CFGX_SFIFO_ENA);
		ग_लिखोl(value, aio->cygaud->audio + aio->regs.bf_sourcech_cfg);
		अवरोध;
	शेष:
		dev_err(aio->cygaud->dev,
			"Port not supported %d\n", aio->portnum);
		status = -EINVAL;
	पूर्ण

	वापस status;
पूर्ण

अटल पूर्णांक pll_configure_mclk(काष्ठा cygnus_audio *cygaud, u32 mclk,
	काष्ठा cygnus_aio_port *aio)
अणु
	पूर्णांक i = 0, error;
	bool found = false;
	स्थिर काष्ठा pll_macro_entry *p_entry;
	काष्ठा clk *ch_clk;

	क्रम (i = 0; i < ARRAY_SIZE(pll_predef_mclk); i++) अणु
		p_entry = &pll_predef_mclk[i];
		अगर (p_entry->mclk == mclk) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (!found) अणु
		dev_err(cygaud->dev,
			"%s No valid mclk freq (%u) found!\n", __func__, mclk);
		वापस -EINVAL;
	पूर्ण

	ch_clk = cygaud->audio_clk[p_entry->pll_ch_num];

	अगर ((aio->clk_trace.cap_en) && (!aio->clk_trace.cap_clk_en)) अणु
		error = clk_prepare_enable(ch_clk);
		अगर (error) अणु
			dev_err(cygaud->dev, "%s clk_prepare_enable failed %d\n",
				__func__, error);
			वापस error;
		पूर्ण
		aio->clk_trace.cap_clk_en = true;
	पूर्ण

	अगर ((aio->clk_trace.play_en) && (!aio->clk_trace.play_clk_en)) अणु
		error = clk_prepare_enable(ch_clk);
		अगर (error) अणु
			dev_err(cygaud->dev, "%s clk_prepare_enable failed %d\n",
				__func__, error);
			वापस error;
		पूर्ण
		aio->clk_trace.play_clk_en = true;
	पूर्ण

	error = clk_set_rate(ch_clk, mclk);
	अगर (error) अणु
		dev_err(cygaud->dev, "%s Set MCLK rate failed: %d\n",
			__func__, error);
		वापस error;
	पूर्ण

	वापस p_entry->pll_ch_num;
पूर्ण

अटल पूर्णांक cygnus_ssp_set_घड़ीs(काष्ठा cygnus_aio_port *aio)
अणु
	u32 value;
	u32 mask = 0xf;
	u32 sclk;
	u32 mclk_rate;
	अचिन्हित पूर्णांक bit_rate;
	अचिन्हित पूर्णांक ratio;

	bit_rate = aio->bit_per_frame * aio->lrclk;

	/*
	 * Check अगर the bit घड़ी can be generated from the given MCLK.
	 * MCLK must be a perfect multiple of bit घड़ी and must be one of the
	 * following values... (2,4,6,8,10,12,14)
	 */
	अगर ((aio->mclk % bit_rate) != 0)
		वापस -EINVAL;

	ratio = aio->mclk / bit_rate;
	चयन (ratio) अणु
	हाल 2:
	हाल 4:
	हाल 6:
	हाल 8:
	हाल 10:
	हाल 12:
	हाल 14:
		mclk_rate = ratio / 2;
		अवरोध;

	शेष:
		dev_err(aio->cygaud->dev,
			"Invalid combination of MCLK and BCLK\n");
		dev_err(aio->cygaud->dev, "lrclk = %u, bits/frame = %u, mclk = %u\n",
			aio->lrclk, aio->bit_per_frame, aio->mclk);
		वापस -EINVAL;
	पूर्ण

	/* Set sclk rate */
	चयन (aio->port_type) अणु
	हाल PORT_TDM:
		sclk = aio->bit_per_frame;
		अगर (sclk == 512)
			sclk = 0;

		/* sclks_per_1fs_भाग = sclk cycles/32 */
		sclk /= 32;

		/* Set number of bitclks per frame */
		value = पढ़ोl(aio->cygaud->audio + aio->regs.i2s_cfg);
		value &= ~(mask << I2S_OUT_CFGX_SCLKS_PER_1FS_DIV32);
		value |= sclk << I2S_OUT_CFGX_SCLKS_PER_1FS_DIV32;
		ग_लिखोl(value, aio->cygaud->audio + aio->regs.i2s_cfg);
		dev_dbg(aio->cygaud->dev,
			"SCLKS_PER_1FS_DIV32 = 0x%x\n", value);
		अवरोध;
	हाल PORT_SPDIF:
		अवरोध;
	शेष:
		dev_err(aio->cygaud->dev, "Unknown port type\n");
		वापस -EINVAL;
	पूर्ण

	/* Set MCLK_RATE ssp port (spdअगर and ssp are the same) */
	value = पढ़ोl(aio->cygaud->audio + aio->regs.i2s_mclk_cfg);
	value &= ~(0xf << I2S_OUT_MCLKRATE_SHIFT);
	value |= (mclk_rate << I2S_OUT_MCLKRATE_SHIFT);
	ग_लिखोl(value, aio->cygaud->audio + aio->regs.i2s_mclk_cfg);

	dev_dbg(aio->cygaud->dev, "mclk cfg reg = 0x%x\n", value);
	dev_dbg(aio->cygaud->dev, "bits per frame = %u, mclk = %u Hz, lrclk = %u Hz\n",
			aio->bit_per_frame, aio->mclk, aio->lrclk);
	वापस 0;
पूर्ण

अटल पूर्णांक cygnus_ssp_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params,
				 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा cygnus_aio_port *aio = cygnus_dai_get_portinfo(dai);
	पूर्णांक rate, bitres;
	u32 value;
	u32 mask = 0x1f;
	पूर्णांक ret = 0;

	dev_dbg(aio->cygaud->dev, "%s port = %d\n", __func__, aio->portnum);
	dev_dbg(aio->cygaud->dev, "params_channels %d\n",
			params_channels(params));
	dev_dbg(aio->cygaud->dev, "rate %d\n", params_rate(params));
	dev_dbg(aio->cygaud->dev, "format %d\n", params_क्रमmat(params));

	rate = params_rate(params);

	चयन (aio->mode) अणु
	हाल CYGNUS_SSPMODE_TDM:
		अगर ((rate == 192000) && (params_channels(params) > 4)) अणु
			dev_err(aio->cygaud->dev, "Cannot run %d channels at %dHz\n",
				params_channels(params), rate);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल CYGNUS_SSPMODE_I2S:
		aio->bit_per_frame = 64; /* I2S must be 64 bit per frame */
		अवरोध;
	शेष:
		dev_err(aio->cygaud->dev,
			"%s port running in unknown mode\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		value = पढ़ोl(aio->cygaud->audio + aio->regs.bf_sourcech_cfg);
		value &= ~BIT(BF_SRC_CFGX_BUFFER_PAIR_ENABLE);
		value &= ~BIT(BF_SRC_CFGX_SAMPLE_CH_MODE);
		ग_लिखोl(value, aio->cygaud->audio + aio->regs.bf_sourcech_cfg);

		चयन (params_क्रमmat(params)) अणु
		हाल SNDRV_PCM_FORMAT_S16_LE:
			bitres = 16;
			अवरोध;

		हाल SNDRV_PCM_FORMAT_S32_LE:
			/* 32 bit mode is coded as 0 */
			bitres = 0;
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण

		value = पढ़ोl(aio->cygaud->audio + aio->regs.bf_sourcech_cfg);
		value &= ~(mask << BF_SRC_CFGX_BIT_RES);
		value |= (bitres << BF_SRC_CFGX_BIT_RES);
		ग_लिखोl(value, aio->cygaud->audio + aio->regs.bf_sourcech_cfg);

	पूर्ण अन्यथा अणु

		चयन (params_क्रमmat(params)) अणु
		हाल SNDRV_PCM_FORMAT_S16_LE:
			value = पढ़ोl(aio->cygaud->audio +
					aio->regs.bf_destch_cfg);
			value |= BIT(BF_DST_CFGX_CAP_MODE);
			ग_लिखोl(value, aio->cygaud->audio +
					aio->regs.bf_destch_cfg);
			अवरोध;

		हाल SNDRV_PCM_FORMAT_S32_LE:
			value = पढ़ोl(aio->cygaud->audio +
					aio->regs.bf_destch_cfg);
			value &= ~BIT(BF_DST_CFGX_CAP_MODE);
			ग_लिखोl(value, aio->cygaud->audio +
					aio->regs.bf_destch_cfg);
			अवरोध;

		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	aio->lrclk = rate;

	अगर (!aio->is_slave)
		ret = cygnus_ssp_set_घड़ीs(aio);

	वापस ret;
पूर्ण

/*
 * This function sets the mclk frequency क्रम pll घड़ी
 */
अटल पूर्णांक cygnus_ssp_set_sysclk(काष्ठा snd_soc_dai *dai,
			पूर्णांक clk_id, अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	पूर्णांक sel;
	u32 value;
	काष्ठा cygnus_aio_port *aio = cygnus_dai_get_portinfo(dai);
	काष्ठा cygnus_audio *cygaud = snd_soc_dai_get_drvdata(dai);

	dev_dbg(aio->cygaud->dev,
		"%s Enter port = %d\n", __func__, aio->portnum);
	sel = pll_configure_mclk(cygaud, freq, aio);
	अगर (sel < 0) अणु
		dev_err(aio->cygaud->dev,
			"%s Setting mclk failed.\n", __func__);
		वापस -EINVAL;
	पूर्ण

	aio->mclk = freq;

	dev_dbg(aio->cygaud->dev, "%s Setting MCLKSEL to %d\n", __func__, sel);
	value = पढ़ोl(aio->cygaud->audio + aio->regs.i2s_mclk_cfg);
	value &= ~(0xf << I2S_OUT_PLLCLKSEL_SHIFT);
	value |= (sel << I2S_OUT_PLLCLKSEL_SHIFT);
	ग_लिखोl(value, aio->cygaud->audio + aio->regs.i2s_mclk_cfg);

	वापस 0;
पूर्ण

अटल पूर्णांक cygnus_ssp_startup(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा cygnus_aio_port *aio = cygnus_dai_get_portinfo(dai);

	snd_soc_dai_set_dma_data(dai, substream, aio);
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		aio->clk_trace.play_en = true;
	अन्यथा
		aio->clk_trace.cap_en = true;

	substream->runसमय->hw.rate_min = CYGNUS_RATE_MIN;
	substream->runसमय->hw.rate_max = CYGNUS_RATE_MAX;

	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE, &cygnus_rate_स्थिरraपूर्णांक);
	वापस 0;
पूर्ण

अटल व्योम cygnus_ssp_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा cygnus_aio_port *aio = cygnus_dai_get_portinfo(dai);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		aio->clk_trace.play_en = false;
	अन्यथा
		aio->clk_trace.cap_en = false;

	अगर (!aio->is_slave) अणु
		u32 val;

		val = पढ़ोl(aio->cygaud->audio + aio->regs.i2s_mclk_cfg);
		val &= CYGNUS_PLLCLKSEL_MASK;
		अगर (val >= ARRAY_SIZE(aio->cygaud->audio_clk)) अणु
			dev_err(aio->cygaud->dev, "Clk index %u is out of bounds\n",
				val);
			वापस;
		पूर्ण

		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
			अगर (aio->clk_trace.play_clk_en) अणु
				clk_disable_unprepare(aio->cygaud->
						audio_clk[val]);
				aio->clk_trace.play_clk_en = false;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (aio->clk_trace.cap_clk_en) अणु
				clk_disable_unprepare(aio->cygaud->
						audio_clk[val]);
				aio->clk_trace.cap_clk_en = false;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Bit    Update  Notes
 * 31     Yes     TDM Mode        (1 = TDM, 0 = i2s)
 * 30     Yes     Slave Mode	  (1 = Slave, 0 = Master)
 * 29:26  No      Sclks per frame
 * 25:18  Yes     FS Width
 * 17:14  No      Valid Slots
 * 13     No      Bits		  (1 = 16 bits, 0 = 32 bits)
 * 12:08  No     Bits per samp
 * 07     Yes     Justअगरcation    (1 = LSB, 0 = MSB)
 * 06     Yes     Alignment       (1 = Delay 1 clk, 0 = no delay
 * 05     Yes     SCLK polarity   (1 = Rising, 0 = Falling)
 * 04     Yes     LRCLK Polarity  (1 = High क्रम left, 0 = Low क्रम left)
 * 03:02  Yes     Reserved - ग_लिखो as zero
 * 01     No      Data Enable
 * 00     No      CLK Enable
 */
#घोषणा I2S_OUT_CFG_REG_UPDATE_MASK   0x3C03FF03

/* Input cfg is same as output, but the FS width is not a valid field */
#घोषणा I2S_IN_CFG_REG_UPDATE_MASK  (I2S_OUT_CFG_REG_UPDATE_MASK | 0x03FC0000)

पूर्णांक cygnus_ssp_set_custom_fsync_width(काष्ठा snd_soc_dai *cpu_dai, पूर्णांक len)
अणु
	काष्ठा cygnus_aio_port *aio = cygnus_dai_get_portinfo(cpu_dai);

	अगर ((len > 0) && (len < 256)) अणु
		aio->fsync_width = len;
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(cygnus_ssp_set_custom_fsync_width);

अटल पूर्णांक cygnus_ssp_set_fmt(काष्ठा snd_soc_dai *cpu_dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा cygnus_aio_port *aio = cygnus_dai_get_portinfo(cpu_dai);
	u32 ssp_curcfg;
	u32 ssp_newcfg;
	u32 ssp_outcfg;
	u32 ssp_incfg;
	u32 val;
	u32 mask;

	dev_dbg(aio->cygaud->dev, "%s Enter  fmt: %x\n", __func__, fmt);

	अगर (aio->port_type == PORT_SPDIF)
		वापस -EINVAL;

	ssp_newcfg = 0;

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBM_CFM:
		ssp_newcfg |= BIT(I2S_OUT_CFGX_SLAVE_MODE);
		aio->is_slave = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFS:
		ssp_newcfg &= ~BIT(I2S_OUT_CFGX_SLAVE_MODE);
		aio->is_slave = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		ssp_newcfg |= BIT(I2S_OUT_CFGX_DATA_ALIGNMENT);
		ssp_newcfg |= BIT(I2S_OUT_CFGX_FSYNC_WIDTH);
		aio->mode = CYGNUS_SSPMODE_I2S;
		अवरोध;

	हाल SND_SOC_DAIFMT_DSP_A:
	हाल SND_SOC_DAIFMT_DSP_B:
		ssp_newcfg |= BIT(I2S_OUT_CFGX_TDM_MODE);

		/* DSP_A = data after FS, DSP_B = data during FS */
		अगर ((fmt & SND_SOC_DAIFMT_FORMAT_MASK) == SND_SOC_DAIFMT_DSP_A)
			ssp_newcfg |= BIT(I2S_OUT_CFGX_DATA_ALIGNMENT);

		अगर ((aio->fsync_width > 0) && (aio->fsync_width < 256))
			ssp_newcfg |=
				(aio->fsync_width << I2S_OUT_CFGX_FSYNC_WIDTH);
		अन्यथा
			ssp_newcfg |= BIT(I2S_OUT_CFGX_FSYNC_WIDTH);

		aio->mode = CYGNUS_SSPMODE_TDM;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * SSP out cfg.
	 * Retain bits we करो not want to update, then OR in new bits
	 */
	ssp_curcfg = पढ़ोl(aio->cygaud->audio + aio->regs.i2s_cfg);
	ssp_outcfg = (ssp_curcfg & I2S_OUT_CFG_REG_UPDATE_MASK) | ssp_newcfg;
	ग_लिखोl(ssp_outcfg, aio->cygaud->audio + aio->regs.i2s_cfg);

	/*
	 * SSP in cfg.
	 * Retain bits we करो not want to update, then OR in new bits
	 */
	ssp_curcfg = पढ़ोl(aio->cygaud->i2s_in + aio->regs.i2s_cap_cfg);
	ssp_incfg = (ssp_curcfg & I2S_IN_CFG_REG_UPDATE_MASK) | ssp_newcfg;
	ग_लिखोl(ssp_incfg, aio->cygaud->i2s_in + aio->regs.i2s_cap_cfg);

	val = पढ़ोl(aio->cygaud->audio + AUD_MISC_SEROUT_OE_REG_BASE);

	/*
	 * Configure the word clk and bit clk as output or tristate
	 * Each port has 4 bits क्रम controlling its pins.
	 * Shअगरt the mask based upon port number.
	 */
	mask = BIT(AUD_MISC_SEROUT_LRCK_OE)
			| BIT(AUD_MISC_SEROUT_SCLK_OE)
			| BIT(AUD_MISC_SEROUT_MCLK_OE);
	mask = mask << (aio->portnum * 4);
	अगर (aio->is_slave)
		/* Set bit क्रम tri-state */
		val |= mask;
	अन्यथा
		/* Clear bit क्रम drive */
		val &= ~mask;

	dev_dbg(aio->cygaud->dev, "%s  Set OE bits 0x%x\n", __func__, val);
	ग_लिखोl(val, aio->cygaud->audio + AUD_MISC_SEROUT_OE_REG_BASE);

	वापस 0;
पूर्ण

अटल पूर्णांक cygnus_ssp_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा cygnus_aio_port *aio = cygnus_dai_get_portinfo(dai);
	काष्ठा cygnus_audio *cygaud = snd_soc_dai_get_drvdata(dai);

	dev_dbg(aio->cygaud->dev,
		"%s cmd %d at port = %d\n", __func__, cmd, aio->portnum);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			audio_ssp_out_enable(aio);
		अन्यथा
			audio_ssp_in_enable(aio);
		cygaud->active_ports++;

		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			audio_ssp_out_disable(aio);
		अन्यथा
			audio_ssp_in_disable(aio);
		cygaud->active_ports--;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cygnus_set_dai_tdm_slot(काष्ठा snd_soc_dai *cpu_dai,
	अचिन्हित पूर्णांक tx_mask, अचिन्हित पूर्णांक rx_mask, पूर्णांक slots, पूर्णांक slot_width)
अणु
	काष्ठा cygnus_aio_port *aio = cygnus_dai_get_portinfo(cpu_dai);
	u32 value;
	पूर्णांक bits_per_slot = 0;     /* शेष to 32-bits per slot */
	पूर्णांक frame_bits;
	अचिन्हित पूर्णांक active_slots;
	bool found = false;
	पूर्णांक i;

	अगर (tx_mask != rx_mask) अणु
		dev_err(aio->cygaud->dev,
			"%s tx_mask must equal rx_mask\n", __func__);
		वापस -EINVAL;
	पूर्ण

	active_slots = hweight32(tx_mask);

	अगर (active_slots > 16)
		वापस -EINVAL;

	/* Slot value must be even */
	अगर (active_slots % 2)
		वापस -EINVAL;

	/* We encode 16 slots as 0 in the reg */
	अगर (active_slots == 16)
		active_slots = 0;

	/* Slot Width is either 16 or 32 */
	चयन (slot_width) अणु
	हाल 16:
		bits_per_slot = 1;
		अवरोध;
	हाल 32:
		bits_per_slot = 0;
		अवरोध;
	शेष:
		bits_per_slot = 0;
		dev_warn(aio->cygaud->dev,
			"%s Defaulting Slot Width to 32\n", __func__);
	पूर्ण

	frame_bits = slots * slot_width;

	क्रम (i = 0; i < ARRAY_SIZE(ssp_valid_tdm_framesize); i++) अणु
		अगर (ssp_valid_tdm_framesize[i] == frame_bits) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		dev_err(aio->cygaud->dev,
			"%s In TDM mode, frame bits INVALID (%d)\n",
			__func__, frame_bits);
		वापस -EINVAL;
	पूर्ण

	aio->bit_per_frame = frame_bits;

	dev_dbg(aio->cygaud->dev, "%s active_slots %u, bits per frame %d\n",
			__func__, active_slots, frame_bits);

	/* Set capture side of ssp port */
	value = पढ़ोl(aio->cygaud->i2s_in + aio->regs.i2s_cap_cfg);
	value &= ~(0xf << I2S_OUT_CFGX_VALID_SLOT);
	value |= (active_slots << I2S_OUT_CFGX_VALID_SLOT);
	value &= ~BIT(I2S_OUT_CFGX_BITS_PER_SLOT);
	value |= (bits_per_slot << I2S_OUT_CFGX_BITS_PER_SLOT);
	ग_लिखोl(value, aio->cygaud->i2s_in + aio->regs.i2s_cap_cfg);

	/* Set playback side of ssp port */
	value = पढ़ोl(aio->cygaud->audio + aio->regs.i2s_cfg);
	value &= ~(0xf << I2S_OUT_CFGX_VALID_SLOT);
	value |= (active_slots << I2S_OUT_CFGX_VALID_SLOT);
	value &= ~BIT(I2S_OUT_CFGX_BITS_PER_SLOT);
	value |= (bits_per_slot << I2S_OUT_CFGX_BITS_PER_SLOT);
	ग_लिखोl(value, aio->cygaud->audio + aio->regs.i2s_cfg);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल पूर्णांक __cygnus_ssp_suspend(काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा cygnus_aio_port *aio = cygnus_dai_get_portinfo(cpu_dai);

	अगर (!snd_soc_dai_active(cpu_dai))
		वापस 0;

	अगर (!aio->is_slave) अणु
		u32 val;

		val = पढ़ोl(aio->cygaud->audio + aio->regs.i2s_mclk_cfg);
		val &= CYGNUS_PLLCLKSEL_MASK;
		अगर (val >= ARRAY_SIZE(aio->cygaud->audio_clk)) अणु
			dev_err(aio->cygaud->dev, "Clk index %u is out of bounds\n",
				val);
			वापस -EINVAL;
		पूर्ण

		अगर (aio->clk_trace.cap_clk_en)
			clk_disable_unprepare(aio->cygaud->audio_clk[val]);
		अगर (aio->clk_trace.play_clk_en)
			clk_disable_unprepare(aio->cygaud->audio_clk[val]);

		aio->pll_clk_num = val;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cygnus_ssp_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dai *dai;
	पूर्णांक ret = 0;

	क्रम_each_component_dais(component, dai)
		ret |= __cygnus_ssp_suspend(dai);

	वापस ret;
पूर्ण

अटल पूर्णांक __cygnus_ssp_resume(काष्ठा snd_soc_dai *cpu_dai)
अणु
	काष्ठा cygnus_aio_port *aio = cygnus_dai_get_portinfo(cpu_dai);
	पूर्णांक error;

	अगर (!snd_soc_dai_active(cpu_dai))
		वापस 0;

	अगर (!aio->is_slave) अणु
		अगर (aio->clk_trace.cap_clk_en) अणु
			error = clk_prepare_enable(aio->cygaud->
					audio_clk[aio->pll_clk_num]);
			अगर (error) अणु
				dev_err(aio->cygaud->dev, "%s clk_prepare_enable failed\n",
					__func__);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अगर (aio->clk_trace.play_clk_en) अणु
			error = clk_prepare_enable(aio->cygaud->
					audio_clk[aio->pll_clk_num]);
			अगर (error) अणु
				अगर (aio->clk_trace.cap_clk_en)
					clk_disable_unprepare(aio->cygaud->
						audio_clk[aio->pll_clk_num]);
				dev_err(aio->cygaud->dev, "%s clk_prepare_enable failed\n",
					__func__);
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cygnus_ssp_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा snd_soc_dai *dai;
	पूर्णांक ret = 0;

	क्रम_each_component_dais(component, dai)
		ret |= __cygnus_ssp_resume(dai);

	वापस ret;
पूर्ण

#अन्यथा
#घोषणा cygnus_ssp_suspend शून्य
#घोषणा cygnus_ssp_resume  शून्य
#पूर्ण_अगर

अटल स्थिर काष्ठा snd_soc_dai_ops cygnus_ssp_dai_ops = अणु
	.startup	= cygnus_ssp_startup,
	.shutकरोwn	= cygnus_ssp_shutकरोwn,
	.trigger	= cygnus_ssp_trigger,
	.hw_params	= cygnus_ssp_hw_params,
	.set_fmt	= cygnus_ssp_set_fmt,
	.set_sysclk	= cygnus_ssp_set_sysclk,
	.set_tdm_slot	= cygnus_set_dai_tdm_slot,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_ops cygnus_spdअगर_dai_ops = अणु
	.startup	= cygnus_ssp_startup,
	.shutकरोwn	= cygnus_ssp_shutकरोwn,
	.trigger	= cygnus_ssp_trigger,
	.hw_params	= cygnus_ssp_hw_params,
	.set_sysclk	= cygnus_ssp_set_sysclk,
पूर्ण;

#घोषणा INIT_CPU_DAI(num) अणु \
	.name = "cygnus-ssp" #num, \
	.playback = अणु \
		.channels_min = 2, \
		.channels_max = 16, \
		.rates = SNDRV_PCM_RATE_KNOT, \
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | \
				SNDRV_PCM_FMTBIT_S32_LE, \
	पूर्ण, \
	.capture = अणु \
		.channels_min = 2, \
		.channels_max = 16, \
		.rates = SNDRV_PCM_RATE_KNOT, \
		.क्रमmats =  SNDRV_PCM_FMTBIT_S16_LE | \
				SNDRV_PCM_FMTBIT_S32_LE, \
	पूर्ण, \
	.ops = &cygnus_ssp_dai_ops, \
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_driver cygnus_ssp_dai_info[] = अणु
	INIT_CPU_DAI(0),
	INIT_CPU_DAI(1),
	INIT_CPU_DAI(2),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dai_driver cygnus_spdअगर_dai_info = अणु
	.name = "cygnus-spdif",
	.playback = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_KNOT,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE |
			SNDRV_PCM_FMTBIT_S32_LE,
	पूर्ण,
	.ops = &cygnus_spdअगर_dai_ops,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver cygnus_ssp_dai[CYGNUS_MAX_PORTS];

अटल स्थिर काष्ठा snd_soc_component_driver cygnus_ssp_component = अणु
	.name		= "cygnus-audio",
	.suspend	= cygnus_ssp_suspend,
	.resume		= cygnus_ssp_resume,
पूर्ण;

/*
 * Return < 0 अगर error
 * Return 0 अगर disabled
 * Return 1 अगर enabled and node is parsed successfully
 */
अटल पूर्णांक parse_ssp_child_node(काष्ठा platक्रमm_device *pdev,
				काष्ठा device_node *dn,
				काष्ठा cygnus_audio *cygaud,
				काष्ठा snd_soc_dai_driver *p_dai)
अणु
	काष्ठा cygnus_aio_port *aio;
	काष्ठा cygnus_ssp_regs ssp_regs[3];
	u32 rawval;
	पूर्णांक portnum = -1;
	क्रमागत cygnus_audio_port_type port_type;

	अगर (of_property_पढ़ो_u32(dn, "reg", &rawval)) अणु
		dev_err(&pdev->dev, "Missing reg property\n");
		वापस -EINVAL;
	पूर्ण

	portnum = rawval;
	चयन (rawval) अणु
	हाल 0:
		ssp_regs[0] = INIT_SSP_REGS(0);
		port_type = PORT_TDM;
		अवरोध;
	हाल 1:
		ssp_regs[1] = INIT_SSP_REGS(1);
		port_type = PORT_TDM;
		अवरोध;
	हाल 2:
		ssp_regs[2] = INIT_SSP_REGS(2);
		port_type = PORT_TDM;
		अवरोध;
	हाल 3:
		port_type = PORT_SPDIF;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Bad value for reg %u\n", rawval);
		वापस -EINVAL;
	पूर्ण

	aio = &cygaud->portinfo[portnum];
	aio->cygaud = cygaud;
	aio->portnum = portnum;
	aio->port_type = port_type;
	aio->fsync_width = -1;

	चयन (port_type) अणु
	हाल PORT_TDM:
		aio->regs = ssp_regs[portnum];
		*p_dai = cygnus_ssp_dai_info[portnum];
		aio->mode = CYGNUS_SSPMODE_UNKNOWN;
		अवरोध;

	हाल PORT_SPDIF:
		aio->regs.bf_sourcech_cfg = BF_SRC_CFG3_OFFSET;
		aio->regs.bf_sourcech_ctrl = BF_SRC_CTRL3_OFFSET;
		aio->regs.i2s_mclk_cfg = SPDIF_MCLK_CFG_OFFSET;
		aio->regs.i2s_stream_cfg = SPDIF_STREAM_CFG_OFFSET;
		*p_dai = cygnus_spdअगर_dai_info;

		/* For the purposes of this code SPDIF can be I2S mode */
		aio->mode = CYGNUS_SSPMODE_I2S;
		अवरोध;
	शेष:
		dev_err(&pdev->dev, "Bad value for port_type %d\n", port_type);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(&pdev->dev, "%s portnum = %d\n", __func__, aio->portnum);
	aio->streams_on = 0;
	aio->cygaud->dev = &pdev->dev;
	aio->clk_trace.play_en = false;
	aio->clk_trace.cap_en = false;

	audio_ssp_init_portregs(aio);
	वापस 0;
पूर्ण

अटल पूर्णांक audio_clk_init(काष्ठा platक्रमm_device *pdev,
						काष्ठा cygnus_audio *cygaud)
अणु
	पूर्णांक i;
	अक्षर clk_name[PROP_LEN_MAX];

	क्रम (i = 0; i < ARRAY_SIZE(cygaud->audio_clk); i++) अणु
		snम_लिखो(clk_name, PROP_LEN_MAX, "ch%d_audio", i);

		cygaud->audio_clk[i] = devm_clk_get(&pdev->dev, clk_name);
		अगर (IS_ERR(cygaud->audio_clk[i]))
			वापस PTR_ERR(cygaud->audio_clk[i]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cygnus_ssp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *child_node;
	काष्ठा resource *res;
	काष्ठा cygnus_audio *cygaud;
	पूर्णांक err;
	पूर्णांक node_count;
	पूर्णांक active_port_count;

	cygaud = devm_kzalloc(dev, माप(काष्ठा cygnus_audio), GFP_KERNEL);
	अगर (!cygaud)
		वापस -ENOMEM;

	dev_set_drvdata(dev, cygaud);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "aud");
	cygaud->audio = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(cygaud->audio))
		वापस PTR_ERR(cygaud->audio);

	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_MEM, "i2s_in");
	cygaud->i2s_in = devm_ioremap_resource(dev, res);
	अगर (IS_ERR(cygaud->i2s_in))
		वापस PTR_ERR(cygaud->i2s_in);

	/* Tri-state all controlable pins until we know that we need them */
	ग_लिखोl(CYGNUS_SSP_TRISTATE_MASK,
			cygaud->audio + AUD_MISC_SEROUT_OE_REG_BASE);

	node_count = of_get_child_count(pdev->dev.of_node);
	अगर ((node_count < 1) || (node_count > CYGNUS_MAX_PORTS)) अणु
		dev_err(dev, "child nodes is %d.  Must be between 1 and %d\n",
			node_count, CYGNUS_MAX_PORTS);
		वापस -EINVAL;
	पूर्ण

	active_port_count = 0;

	क्रम_each_available_child_of_node(pdev->dev.of_node, child_node) अणु
		err = parse_ssp_child_node(pdev, child_node, cygaud,
					&cygnus_ssp_dai[active_port_count]);

		/* negative is err, 0 is active and good, 1 is disabled */
		अगर (err < 0) अणु
			of_node_put(child_node);
			वापस err;
		पूर्ण
		अन्यथा अगर (!err) अणु
			dev_dbg(dev, "Activating DAI: %s\n",
				cygnus_ssp_dai[active_port_count].name);
			active_port_count++;
		पूर्ण
	पूर्ण

	cygaud->dev = dev;
	cygaud->active_ports = 0;

	dev_dbg(dev, "Registering %d DAIs\n", active_port_count);
	err = devm_snd_soc_रेजिस्टर_component(dev, &cygnus_ssp_component,
				cygnus_ssp_dai, active_port_count);
	अगर (err) अणु
		dev_err(dev, "snd_soc_register_dai failed\n");
		वापस err;
	पूर्ण

	cygaud->irq_num = platक्रमm_get_irq(pdev, 0);
	अगर (cygaud->irq_num <= 0)
		वापस cygaud->irq_num;

	err = audio_clk_init(pdev, cygaud);
	अगर (err) अणु
		dev_err(dev, "audio clock initialization failed\n");
		वापस err;
	पूर्ण

	err = cygnus_soc_platक्रमm_रेजिस्टर(dev, cygaud);
	अगर (err) अणु
		dev_err(dev, "platform reg error %d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cygnus_ssp_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	cygnus_soc_platक्रमm_unरेजिस्टर(&pdev->dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id cygnus_ssp_of_match[] = अणु
	अणु .compatible = "brcm,cygnus-audio" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, cygnus_ssp_of_match);

अटल काष्ठा platक्रमm_driver cygnus_ssp_driver = अणु
	.probe		= cygnus_ssp_probe,
	.हटाओ		= cygnus_ssp_हटाओ,
	.driver		= अणु
		.name	= "cygnus-ssp",
		.of_match_table = cygnus_ssp_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(cygnus_ssp_driver);

MODULE_ALIAS("platform:cygnus-ssp");
MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Broadcom");
MODULE_DESCRIPTION("Cygnus ASoC SSP Interface");
