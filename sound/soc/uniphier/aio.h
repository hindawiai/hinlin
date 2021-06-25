<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Socionext UniPhier AIO ALSA driver.
 *
 * Copyright (c) 2016-2018 Socionext Inc.
 */

#अगर_अघोषित SND_UNIPHIER_AIO_H__
#घोषणा SND_UNIPHIER_AIO_H__

#समावेश <linux/spinlock.h>
#समावेश <linux/types.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

काष्ठा platक्रमm_device;

क्रमागत ID_PORT_TYPE अणु
	PORT_TYPE_UNKNOWN,
	PORT_TYPE_I2S,
	PORT_TYPE_SPDIF,
	PORT_TYPE_EVE,
	PORT_TYPE_CONV,
पूर्ण;

क्रमागत ID_PORT_सूची अणु
	PORT_सूची_OUTPUT,
	PORT_सूची_INPUT,
पूर्ण;

क्रमागत IEC61937_PC अणु
	IEC61937_PC_AC3   = 0x0001,
	IEC61937_PC_PAUSE = 0x0003,
	IEC61937_PC_MPA   = 0x0004,
	IEC61937_PC_MP3   = 0x0005,
	IEC61937_PC_DTS1  = 0x000b,
	IEC61937_PC_DTS2  = 0x000c,
	IEC61937_PC_DTS3  = 0x000d,
	IEC61937_PC_AAC   = 0x0007,
पूर्ण;

/* IEC61937 Repetition period of data-burst in IEC60958 frames */
#घोषणा IEC61937_FRM_STR_AC3       1536
#घोषणा IEC61937_FRM_STR_MPA       1152
#घोषणा IEC61937_FRM_STR_MP3       1152
#घोषणा IEC61937_FRM_STR_DTS1      512
#घोषणा IEC61937_FRM_STR_DTS2      1024
#घोषणा IEC61937_FRM_STR_DTS3      2048
#घोषणा IEC61937_FRM_STR_AAC       1024

/* IEC61937 Repetition period of Pause data-burst in IEC60958 frames */
#घोषणा IEC61937_FRM_PAU_AC3       3
#घोषणा IEC61937_FRM_PAU_MPA       32
#घोषणा IEC61937_FRM_PAU_MP3       32
#घोषणा IEC61937_FRM_PAU_DTS1      3
#घोषणा IEC61937_FRM_PAU_DTS2      3
#घोषणा IEC61937_FRM_PAU_DTS3      3
#घोषणा IEC61937_FRM_PAU_AAC       32

/* IEC61937 Pa and Pb */
#घोषणा IEC61937_HEADER_SIGN       0x1f4e72f8

#घोषणा AUD_HW_PCMIN1    0
#घोषणा AUD_HW_PCMIN2    1
#घोषणा AUD_HW_PCMIN3    2
#घोषणा AUD_HW_IECIN1    3
#घोषणा AUD_HW_DIECIN1   4

#घोषणा AUD_NAME_PCMIN1     "aio-pcmin1"
#घोषणा AUD_NAME_PCMIN2     "aio-pcmin2"
#घोषणा AUD_NAME_PCMIN3     "aio-pcmin3"
#घोषणा AUD_NAME_IECIN1     "aio-iecin1"
#घोषणा AUD_NAME_DIECIN1    "aio-diecin1"

#घोषणा AUD_HW_HPCMOUT1    0
#घोषणा AUD_HW_PCMOUT1     1
#घोषणा AUD_HW_PCMOUT2     2
#घोषणा AUD_HW_PCMOUT3     3
#घोषणा AUD_HW_EPCMOUT1    4
#घोषणा AUD_HW_EPCMOUT2    5
#घोषणा AUD_HW_EPCMOUT3    6
#घोषणा AUD_HW_EPCMOUT6    9
#घोषणा AUD_HW_HIECOUT1    10
#घोषणा AUD_HW_IECOUT1     11
#घोषणा AUD_HW_CMASTER     31

#घोषणा AUD_NAME_HPCMOUT1        "aio-hpcmout1"
#घोषणा AUD_NAME_PCMOUT1         "aio-pcmout1"
#घोषणा AUD_NAME_PCMOUT2         "aio-pcmout2"
#घोषणा AUD_NAME_PCMOUT3         "aio-pcmout3"
#घोषणा AUD_NAME_EPCMOUT1        "aio-epcmout1"
#घोषणा AUD_NAME_EPCMOUT2        "aio-epcmout2"
#घोषणा AUD_NAME_EPCMOUT3        "aio-epcmout3"
#घोषणा AUD_NAME_EPCMOUT6        "aio-epcmout6"
#घोषणा AUD_NAME_HIECOUT1        "aio-hiecout1"
#घोषणा AUD_NAME_IECOUT1         "aio-iecout1"
#घोषणा AUD_NAME_CMASTER         "aio-cmaster"
#घोषणा AUD_NAME_HIECCOMPOUT1    "aio-hieccompout1"
#घोषणा AUD_NAME_IECCOMPOUT1     "aio-ieccompout1"

#घोषणा AUD_GNAME_HDMI    "aio-hdmi"
#घोषणा AUD_GNAME_LINE    "aio-line"
#घोषणा AUD_GNAME_AUX     "aio-aux"
#घोषणा AUD_GNAME_IEC     "aio-iec"

#घोषणा AUD_CLK_IO        0
#घोषणा AUD_CLK_A1        1
#घोषणा AUD_CLK_F1        2
#घोषणा AUD_CLK_A2        3
#घोषणा AUD_CLK_F2        4
#घोषणा AUD_CLK_A         5
#घोषणा AUD_CLK_F         6
#घोषणा AUD_CLK_APLL      7
#घोषणा AUD_CLK_RX0       8
#घोषणा AUD_CLK_USB0      9
#घोषणा AUD_CLK_HSC0      10

#घोषणा AUD_PLL_A1        0
#घोषणा AUD_PLL_F1        1
#घोषणा AUD_PLL_A2        2
#घोषणा AUD_PLL_F2        3
#घोषणा AUD_PLL_APLL      4
#घोषणा AUD_PLL_RX0       5
#घोषणा AUD_PLL_USB0      6
#घोषणा AUD_PLL_HSC0      7

#घोषणा AUD_PLLDIV_1_2    0
#घोषणा AUD_PLLDIV_1_3    1
#घोषणा AUD_PLLDIV_1_1    2
#घोषणा AUD_PLLDIV_2_3    3

#घोषणा AUD_VOL_INIT         0x4000 /* +0dB */
#घोषणा AUD_VOL_MAX          0xffff /* +6dB */
#घोषणा AUD_VOL_FADE_TIME    20 /* 20ms */

#घोषणा AUD_RING_SIZE            (128 * 1024)

#घोषणा AUD_MIN_FRAGMENT         4
#घोषणा AUD_MAX_FRAGMENT         8
#घोषणा AUD_MIN_FRAGMENT_SIZE    (4 * 1024)
#घोषणा AUD_MAX_FRAGMENT_SIZE    (16 * 1024)

/* max 5 slots, 10 channels, 2 channel in 1 slot */
#घोषणा AUD_MAX_SLOTSEL    5

/*
 * This is a selector क्रम भव रेजिस्टर map of AIO.
 *
 * map:  Specअगरy the index of भव रेजिस्टर map.
 * hw :  Specअगरy the ID of real रेजिस्टर map, selector uses this value.
 *       A meaning of this value depends specअगरication of SoC.
 */
काष्ठा uniphier_aio_selector अणु
	पूर्णांक map;
	पूर्णांक hw;
पूर्ण;

/**
 * 'SoftWare MAPping' setting of UniPhier AIO रेजिस्टरs.
 *
 * We have to setup 'virtual' register maps to access 'real' रेजिस्टरs of AIO.
 * This feature is legacy and meaningless but AIO needs this to work.
 *
 * Each hardware blocks have own भव रेजिस्टर maps as following:
 *
 * Address Virtual                      Real
 * ------- ---------                    ---------------
 * 0x12000 DMAC map0 --> [selector] --> DMAC hardware 3
 * 0x12080 DMAC map1 --> [selector] --> DMAC hardware 1
 * ...
 * 0x42000 Port map0 --> [selector] --> Port hardware 1
 * 0x42400 Port map1 --> [selector] --> Port hardware 2
 * ...
 *
 * ch   : Input or output channel of DMAC
 * rb   : Ring buffer
 * iport: PCM input port
 * iअगर  : Input पूर्णांकerface
 * oport: PCM output port
 * oअगर  : Output पूर्णांकerface
 * och  : Output channel of DMAC क्रम sampling rate converter
 *
 * These are examples क्रम sound data paths:
 *
 * For caputure device:
 *   (outer of AIO) -> iport -> iअगर -> ch -> rb -> (CPU)
 * For playback device:
 *   (CPU) -> rb -> ch -> oअगर -> oport -> (outer of AIO)
 * For sampling rate converter device:
 *   (CPU) -> rb -> ch -> oअगर -> (HW SRC) -> iअगर -> och -> orb -> (CPU)
 */
काष्ठा uniphier_aio_swmap अणु
	पूर्णांक type;
	पूर्णांक dir;

	काष्ठा uniphier_aio_selector ch;
	काष्ठा uniphier_aio_selector rb;
	काष्ठा uniphier_aio_selector iport;
	काष्ठा uniphier_aio_selector iअगर;
	काष्ठा uniphier_aio_selector oport;
	काष्ठा uniphier_aio_selector oअगर;
	काष्ठा uniphier_aio_selector och;
पूर्ण;

काष्ठा uniphier_aio_spec अणु
	स्थिर अक्षर *name;
	स्थिर अक्षर *gname;
	काष्ठा uniphier_aio_swmap swm;
पूर्ण;

काष्ठा uniphier_aio_pll अणु
	bool enable;
	अचिन्हित पूर्णांक freq;
पूर्ण;

काष्ठा uniphier_aio_chip_spec अणु
	स्थिर काष्ठा uniphier_aio_spec *specs;
	पूर्णांक num_specs;
	स्थिर काष्ठा uniphier_aio_pll *plls;
	पूर्णांक num_plls;
	काष्ठा snd_soc_dai_driver *dais;
	पूर्णांक num_dais;

	/* DMA access mode, this is workaround क्रम DMA hungup */
	पूर्णांक addr_ext;
पूर्ण;

काष्ठा uniphier_aio_sub अणु
	काष्ठा uniphier_aio *aio;

	/* Guard sub->rd_offs and wr_offs from IRQ handler. */
	spinlock_t lock;

	स्थिर काष्ठा uniphier_aio_swmap *swm;
	स्थिर काष्ठा uniphier_aio_spec *spec;

	/* For PCM audio */
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_hw_params params;
	पूर्णांक vol;

	/* For compress audio */
	काष्ठा snd_compr_stream *cstream;
	काष्ठा snd_compr_params cparams;
	अचिन्हित अक्षर *compr_area;
	dma_addr_t compr_addr;
	माप_प्रकार compr_bytes;
	पूर्णांक pass_through;
	क्रमागत IEC61937_PC iec_pc;
	bool iec_header;

	/* Both PCM and compress audio */
	bool use_mmap;
	पूर्णांक setting;
	पूर्णांक running;
	u64 rd_offs;
	u64 wr_offs;
	u32 threshold;
	u64 rd_org;
	u64 wr_org;
	u64 rd_total;
	u64 wr_total;
पूर्ण;

काष्ठा uniphier_aio अणु
	काष्ठा uniphier_aio_chip *chip;

	काष्ठा uniphier_aio_sub sub[2];

	अचिन्हित पूर्णांक fmt;
	/* Set one of AUD_CLK_X */
	पूर्णांक clk_in;
	पूर्णांक clk_out;
	/* Set one of AUD_PLL_X */
	पूर्णांक pll_in;
	पूर्णांक pll_out;
	/* Set one of AUD_PLLDIV_X */
	पूर्णांक plद_भाग;
पूर्ण;

काष्ठा uniphier_aio_chip अणु
	काष्ठा platक्रमm_device *pdev;
	स्थिर काष्ठा uniphier_aio_chip_spec *chip_spec;

	काष्ठा uniphier_aio *aios;
	पूर्णांक num_aios;
	पूर्णांक num_wup_aios;
	काष्ठा uniphier_aio_pll *plls;
	पूर्णांक num_plls;

	काष्ठा clk *clk;
	काष्ठा reset_control *rst;
	काष्ठा regmap *regmap;
	काष्ठा regmap *regmap_sg;
	पूर्णांक active;
पूर्ण;

अटल अंतरभूत काष्ठा uniphier_aio *uniphier_priv(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा uniphier_aio_chip *chip = snd_soc_dai_get_drvdata(dai);

	वापस &chip->aios[dai->id];
पूर्ण

पूर्णांक uniphier_aiodma_soc_रेजिस्टर_platक्रमm(काष्ठा platक्रमm_device *pdev);
बाह्य स्थिर काष्ठा snd_compress_ops uniphier_aio_compress_ops;

पूर्णांक uniphier_aio_dai_probe(काष्ठा snd_soc_dai *dai);
पूर्णांक uniphier_aio_dai_हटाओ(काष्ठा snd_soc_dai *dai);
पूर्णांक uniphier_aio_probe(काष्ठा platक्रमm_device *pdev);
पूर्णांक uniphier_aio_हटाओ(काष्ठा platक्रमm_device *pdev);
बाह्य स्थिर काष्ठा snd_soc_dai_ops uniphier_aio_i2s_ops;
बाह्य स्थिर काष्ठा snd_soc_dai_ops uniphier_aio_spdअगर_ops;

u64 aio_rb_cnt(काष्ठा uniphier_aio_sub *sub);
u64 aio_rbt_cnt_to_end(काष्ठा uniphier_aio_sub *sub);
u64 aio_rb_space(काष्ठा uniphier_aio_sub *sub);
u64 aio_rb_space_to_end(काष्ठा uniphier_aio_sub *sub);

व्योम aio_iecout_set_enable(काष्ठा uniphier_aio_chip *chip, bool enable);
पूर्णांक aio_chip_set_pll(काष्ठा uniphier_aio_chip *chip, पूर्णांक pll_id,
		     अचिन्हित पूर्णांक freq);
व्योम aio_chip_init(काष्ठा uniphier_aio_chip *chip);
पूर्णांक aio_init(काष्ठा uniphier_aio_sub *sub);
व्योम aio_port_reset(काष्ठा uniphier_aio_sub *sub);
पूर्णांक aio_port_set_param(काष्ठा uniphier_aio_sub *sub, पूर्णांक pass_through,
		       स्थिर काष्ठा snd_pcm_hw_params *params);
व्योम aio_port_set_enable(काष्ठा uniphier_aio_sub *sub, पूर्णांक enable);
पूर्णांक aio_port_get_volume(काष्ठा uniphier_aio_sub *sub);
व्योम aio_port_set_volume(काष्ठा uniphier_aio_sub *sub, पूर्णांक vol);
पूर्णांक aio_अगर_set_param(काष्ठा uniphier_aio_sub *sub, पूर्णांक pass_through);
पूर्णांक aio_oport_set_stream_type(काष्ठा uniphier_aio_sub *sub,
			      क्रमागत IEC61937_PC pc);
व्योम aio_src_reset(काष्ठा uniphier_aio_sub *sub);
पूर्णांक aio_src_set_param(काष्ठा uniphier_aio_sub *sub,
		      स्थिर काष्ठा snd_pcm_hw_params *params);
पूर्णांक aio_srcअगर_set_param(काष्ठा uniphier_aio_sub *sub);
पूर्णांक aio_srcch_set_param(काष्ठा uniphier_aio_sub *sub);
व्योम aio_srcch_set_enable(काष्ठा uniphier_aio_sub *sub, पूर्णांक enable);

पूर्णांक aiodma_ch_set_param(काष्ठा uniphier_aio_sub *sub);
व्योम aiodma_ch_set_enable(काष्ठा uniphier_aio_sub *sub, पूर्णांक enable);
पूर्णांक aiodma_rb_set_threshold(काष्ठा uniphier_aio_sub *sub, u64 size, u32 th);
पूर्णांक aiodma_rb_set_buffer(काष्ठा uniphier_aio_sub *sub, u64 start, u64 end,
			 पूर्णांक period);
व्योम aiodma_rb_sync(काष्ठा uniphier_aio_sub *sub, u64 start, u64 size,
		    पूर्णांक period);
bool aiodma_rb_is_irq(काष्ठा uniphier_aio_sub *sub);
व्योम aiodma_rb_clear_irq(काष्ठा uniphier_aio_sub *sub);

#पूर्ण_अगर /* SND_UNIPHIER_AIO_H__ */
