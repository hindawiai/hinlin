<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Renesas R-Car
//
// Copyright (C) 2013 Renesas Solutions Corp.
// Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>

#अगर_अघोषित RSND_H
#घोषणा RSND_H

#समावेश <linux/clk.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>
#समावेश <linux/list.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_graph.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/sh_dma.h>
#समावेश <linux/workqueue.h>
#समावेश <sound/soc.h>
#समावेश <sound/pcm_params.h>

#घोषणा RSND_GEN1_SRU	0
#घोषणा RSND_GEN1_ADG	1
#घोषणा RSND_GEN1_SSI	2

#घोषणा RSND_GEN2_SCU	0
#घोषणा RSND_GEN2_ADG	1
#घोषणा RSND_GEN2_SSIU	2
#घोषणा RSND_GEN2_SSI	3

#घोषणा RSND_BASE_MAX	4

/*
 *	pseuकरो रेजिस्टर
 *
 * The रेजिस्टर address offsets SRU/SCU/SSIU on Gen1/Gen2 are very dअगरferent.
 * This driver uses pseuकरो रेजिस्टर in order to hide it.
 * see gen1/gen2 क्रम detail
 */
क्रमागत rsnd_reg अणु
	/* SCU (MIX/CTU/DVC) */
	SRC_I_BUSIF_MODE,
	SRC_O_BUSIF_MODE,
	SRC_ROUTE_MODE0,
	SRC_SWRSR,
	SRC_SRCIR,
	SRC_ADINR,
	SRC_IFSCR,
	SRC_IFSVR,
	SRC_SRCCR,
	SRC_CTRL,
	SRC_BSDSR,
	SRC_BSISR,
	SRC_INT_ENABLE0,
	SRC_BUSIF_DALIGN,
	SRCIN_TIMSEL0,
	SRCIN_TIMSEL1,
	SRCIN_TIMSEL2,
	SRCIN_TIMSEL3,
	SRCIN_TIMSEL4,
	SRCOUT_TIMSEL0,
	SRCOUT_TIMSEL1,
	SRCOUT_TIMSEL2,
	SRCOUT_TIMSEL3,
	SRCOUT_TIMSEL4,
	SCU_SYS_STATUS0,
	SCU_SYS_STATUS1,
	SCU_SYS_INT_EN0,
	SCU_SYS_INT_EN1,
	CMD_CTRL,
	CMD_BUSIF_MODE,
	CMD_BUSIF_DALIGN,
	CMD_ROUTE_SLCT,
	CMDOUT_TIMSEL,
	CTU_SWRSR,
	CTU_CTUIR,
	CTU_ADINR,
	CTU_CPMDR,
	CTU_SCMDR,
	CTU_SV00R,
	CTU_SV01R,
	CTU_SV02R,
	CTU_SV03R,
	CTU_SV04R,
	CTU_SV05R,
	CTU_SV06R,
	CTU_SV07R,
	CTU_SV10R,
	CTU_SV11R,
	CTU_SV12R,
	CTU_SV13R,
	CTU_SV14R,
	CTU_SV15R,
	CTU_SV16R,
	CTU_SV17R,
	CTU_SV20R,
	CTU_SV21R,
	CTU_SV22R,
	CTU_SV23R,
	CTU_SV24R,
	CTU_SV25R,
	CTU_SV26R,
	CTU_SV27R,
	CTU_SV30R,
	CTU_SV31R,
	CTU_SV32R,
	CTU_SV33R,
	CTU_SV34R,
	CTU_SV35R,
	CTU_SV36R,
	CTU_SV37R,
	MIX_SWRSR,
	MIX_MIXIR,
	MIX_ADINR,
	MIX_MIXMR,
	MIX_MVPDR,
	MIX_MDBAR,
	MIX_MDBBR,
	MIX_MDBCR,
	MIX_MDBDR,
	MIX_MDBER,
	DVC_SWRSR,
	DVC_DVUIR,
	DVC_ADINR,
	DVC_DVUCR,
	DVC_ZCMCR,
	DVC_VOL0R,
	DVC_VOL1R,
	DVC_VOL2R,
	DVC_VOL3R,
	DVC_VOL4R,
	DVC_VOL5R,
	DVC_VOL6R,
	DVC_VOL7R,
	DVC_DVUER,
	DVC_VRCTR,
	DVC_VRPDR,
	DVC_VRDBR,

	/* ADG */
	BRRA,
	BRRB,
	BRGCKR,
	DIV_EN,
	AUDIO_CLK_SEL0,
	AUDIO_CLK_SEL1,
	AUDIO_CLK_SEL2,

	/* SSIU */
	SSI_MODE,
	SSI_MODE0,
	SSI_MODE1,
	SSI_MODE2,
	SSI_CONTROL,
	SSI_CTRL,
	SSI_BUSIF0_MODE,
	SSI_BUSIF1_MODE,
	SSI_BUSIF2_MODE,
	SSI_BUSIF3_MODE,
	SSI_BUSIF4_MODE,
	SSI_BUSIF5_MODE,
	SSI_BUSIF6_MODE,
	SSI_BUSIF7_MODE,
	SSI_BUSIF0_ADINR,
	SSI_BUSIF1_ADINR,
	SSI_BUSIF2_ADINR,
	SSI_BUSIF3_ADINR,
	SSI_BUSIF4_ADINR,
	SSI_BUSIF5_ADINR,
	SSI_BUSIF6_ADINR,
	SSI_BUSIF7_ADINR,
	SSI_BUSIF0_DALIGN,
	SSI_BUSIF1_DALIGN,
	SSI_BUSIF2_DALIGN,
	SSI_BUSIF3_DALIGN,
	SSI_BUSIF4_DALIGN,
	SSI_BUSIF5_DALIGN,
	SSI_BUSIF6_DALIGN,
	SSI_BUSIF7_DALIGN,
	SSI_INT_ENABLE,
	SSI_SYS_STATUS0,
	SSI_SYS_STATUS1,
	SSI_SYS_STATUS2,
	SSI_SYS_STATUS3,
	SSI_SYS_STATUS4,
	SSI_SYS_STATUS5,
	SSI_SYS_STATUS6,
	SSI_SYS_STATUS7,
	SSI_SYS_INT_ENABLE0,
	SSI_SYS_INT_ENABLE1,
	SSI_SYS_INT_ENABLE2,
	SSI_SYS_INT_ENABLE3,
	SSI_SYS_INT_ENABLE4,
	SSI_SYS_INT_ENABLE5,
	SSI_SYS_INT_ENABLE6,
	SSI_SYS_INT_ENABLE7,
	HDMI0_SEL,
	HDMI1_SEL,
	SSI9_BUSIF0_MODE,
	SSI9_BUSIF1_MODE,
	SSI9_BUSIF2_MODE,
	SSI9_BUSIF3_MODE,
	SSI9_BUSIF4_MODE,
	SSI9_BUSIF5_MODE,
	SSI9_BUSIF6_MODE,
	SSI9_BUSIF7_MODE,
	SSI9_BUSIF0_ADINR,
	SSI9_BUSIF1_ADINR,
	SSI9_BUSIF2_ADINR,
	SSI9_BUSIF3_ADINR,
	SSI9_BUSIF4_ADINR,
	SSI9_BUSIF5_ADINR,
	SSI9_BUSIF6_ADINR,
	SSI9_BUSIF7_ADINR,
	SSI9_BUSIF0_DALIGN,
	SSI9_BUSIF1_DALIGN,
	SSI9_BUSIF2_DALIGN,
	SSI9_BUSIF3_DALIGN,
	SSI9_BUSIF4_DALIGN,
	SSI9_BUSIF5_DALIGN,
	SSI9_BUSIF6_DALIGN,
	SSI9_BUSIF7_DALIGN,

	/* SSI */
	SSICR,
	SSISR,
	SSITDR,
	SSIRDR,
	SSIWSR,

	REG_MAX,
पूर्ण;
#घोषणा SRCIN_TIMSEL(i)		(SRCIN_TIMSEL0 + (i))
#घोषणा SRCOUT_TIMSEL(i)	(SRCOUT_TIMSEL0 + (i))
#घोषणा CTU_SVxxR(i, j)		(CTU_SV00R + (i * 8) + (j))
#घोषणा DVC_VOLxR(i)		(DVC_VOL0R + (i))
#घोषणा AUDIO_CLK_SEL(i)	(AUDIO_CLK_SEL0 + (i))
#घोषणा SSI_BUSIF_MODE(i)	(SSI_BUSIF0_MODE + (i))
#घोषणा SSI_BUSIF_ADINR(i)	(SSI_BUSIF0_ADINR + (i))
#घोषणा SSI_BUSIF_DALIGN(i)	(SSI_BUSIF0_DALIGN + (i))
#घोषणा SSI9_BUSIF_MODE(i)	(SSI9_BUSIF0_MODE + (i))
#घोषणा SSI9_BUSIF_ADINR(i)	(SSI9_BUSIF0_ADINR + (i))
#घोषणा SSI9_BUSIF_DALIGN(i)	(SSI9_BUSIF0_DALIGN + (i))
#घोषणा SSI_SYS_STATUS(i)	(SSI_SYS_STATUS0 + (i))
#घोषणा SSI_SYS_INT_ENABLE(i) (SSI_SYS_INT_ENABLE0 + (i))


काष्ठा rsnd_priv;
काष्ठा rsnd_mod;
काष्ठा rsnd_dai;
काष्ठा rsnd_dai_stream;

/*
 *	R-Car basic functions
 */
u32 rsnd_mod_पढ़ो(काष्ठा rsnd_mod *mod, क्रमागत rsnd_reg reg);
व्योम rsnd_mod_ग_लिखो(काष्ठा rsnd_mod *mod, क्रमागत rsnd_reg reg, u32 data);
व्योम rsnd_mod_bset(काष्ठा rsnd_mod *mod, क्रमागत rsnd_reg reg, u32 mask, u32 data);
u32 rsnd_get_adinr_bit(काष्ठा rsnd_mod *mod, काष्ठा rsnd_dai_stream *io);
u32 rsnd_get_dalign(काष्ठा rsnd_mod *mod, काष्ठा rsnd_dai_stream *io);
u32 rsnd_get_busअगर_shअगरt(काष्ठा rsnd_dai_stream *io, काष्ठा rsnd_mod *mod);

/*
 *	R-Car DMA
 */
पूर्णांक rsnd_dma_attach(काष्ठा rsnd_dai_stream *io,
		    काष्ठा rsnd_mod *mod, काष्ठा rsnd_mod **dma_mod);
पूर्णांक rsnd_dma_probe(काष्ठा rsnd_priv *priv);
काष्ठा dma_chan *rsnd_dma_request_channel(काष्ठा device_node *of_node,
					  काष्ठा rsnd_mod *mod, अक्षर *name);

/*
 *	R-Car sound mod
 */
क्रमागत rsnd_mod_type अणु
	RSND_MOD_AUDMAPP,
	RSND_MOD_AUDMA,
	RSND_MOD_DVC,
	RSND_MOD_MIX,
	RSND_MOD_CTU,
	RSND_MOD_CMD,
	RSND_MOD_SRC,
	RSND_MOD_SSIM3,		/* SSI multi 3 */
	RSND_MOD_SSIM2,		/* SSI multi 2 */
	RSND_MOD_SSIM1,		/* SSI multi 1 */
	RSND_MOD_SSIP,		/* SSI parent */
	RSND_MOD_SSI,
	RSND_MOD_SSIU,
	RSND_MOD_MAX,
पूर्ण;

काष्ठा rsnd_mod_ops अणु
	अक्षर *name;
	काष्ठा dma_chan* (*dma_req)(काष्ठा rsnd_dai_stream *io,
				    काष्ठा rsnd_mod *mod);
	पूर्णांक (*probe)(काष्ठा rsnd_mod *mod,
		     काष्ठा rsnd_dai_stream *io,
		     काष्ठा rsnd_priv *priv);
	पूर्णांक (*हटाओ)(काष्ठा rsnd_mod *mod,
		      काष्ठा rsnd_dai_stream *io,
		      काष्ठा rsnd_priv *priv);
	पूर्णांक (*init)(काष्ठा rsnd_mod *mod,
		    काष्ठा rsnd_dai_stream *io,
		    काष्ठा rsnd_priv *priv);
	पूर्णांक (*quit)(काष्ठा rsnd_mod *mod,
		    काष्ठा rsnd_dai_stream *io,
		    काष्ठा rsnd_priv *priv);
	पूर्णांक (*start)(काष्ठा rsnd_mod *mod,
		     काष्ठा rsnd_dai_stream *io,
		     काष्ठा rsnd_priv *priv);
	पूर्णांक (*stop)(काष्ठा rsnd_mod *mod,
		    काष्ठा rsnd_dai_stream *io,
		    काष्ठा rsnd_priv *priv);
	पूर्णांक (*irq)(काष्ठा rsnd_mod *mod,
		   काष्ठा rsnd_dai_stream *io,
		   काष्ठा rsnd_priv *priv, पूर्णांक enable);
	पूर्णांक (*pcm_new)(काष्ठा rsnd_mod *mod,
		       काष्ठा rsnd_dai_stream *io,
		       काष्ठा snd_soc_pcm_runसमय *rtd);
	पूर्णांक (*hw_params)(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *hw_params);
	पूर्णांक (*poपूर्णांकer)(काष्ठा rsnd_mod *mod,
		       काष्ठा rsnd_dai_stream *io,
		       snd_pcm_uframes_t *poपूर्णांकer);
	पूर्णांक (*fallback)(काष्ठा rsnd_mod *mod,
			काष्ठा rsnd_dai_stream *io,
			काष्ठा rsnd_priv *priv);
	पूर्णांक (*prepare)(काष्ठा rsnd_mod *mod,
		       काष्ठा rsnd_dai_stream *io,
		       काष्ठा rsnd_priv *priv);
	पूर्णांक (*cleanup)(काष्ठा rsnd_mod *mod,
		       काष्ठा rsnd_dai_stream *io,
		       काष्ठा rsnd_priv *priv);
	पूर्णांक (*hw_मुक्त)(काष्ठा rsnd_mod *mod,
		       काष्ठा rsnd_dai_stream *io,
		       काष्ठा snd_pcm_substream *substream);
	u32 *(*get_status)(काष्ठा rsnd_mod *mod,
			   काष्ठा rsnd_dai_stream *io,
			   क्रमागत rsnd_mod_type type);
	पूर्णांक (*id)(काष्ठा rsnd_mod *mod);
	पूर्णांक (*id_sub)(काष्ठा rsnd_mod *mod);
	पूर्णांक (*id_cmd)(काष्ठा rsnd_mod *mod);
पूर्ण;

काष्ठा rsnd_dai_stream;
काष्ठा rsnd_mod अणु
	पूर्णांक id;
	क्रमागत rsnd_mod_type type;
	काष्ठा rsnd_mod_ops *ops;
	काष्ठा rsnd_priv *priv;
	काष्ठा clk *clk;
	u32 status;
पूर्ण;
/*
 * status
 *
 * 0xH0000CB0
 *
 * B	0: init		1: quit
 * C	0: start	1: stop
 * D	0: hw_params	1: hw_मुक्त
 *
 * H is always called (see __rsnd_mod_call)
 * H	0: probe	1: हटाओ
 * H	0: pcm_new
 * H	0: fallback
 * H	0: poपूर्णांकer
 * H	0: prepare
 * H	0: cleanup
 */
#घोषणा __rsnd_mod_shअगरt_init		4
#घोषणा __rsnd_mod_shअगरt_quit		4
#घोषणा __rsnd_mod_shअगरt_start		8
#घोषणा __rsnd_mod_shअगरt_stop		8
#घोषणा __rsnd_mod_shअगरt_hw_params	12
#घोषणा __rsnd_mod_shअगरt_hw_मुक्त	12
#घोषणा __rsnd_mod_shअगरt_probe		28 /* always called */
#घोषणा __rsnd_mod_shअगरt_हटाओ		28 /* always called */
#घोषणा __rsnd_mod_shअगरt_irq		28 /* always called */
#घोषणा __rsnd_mod_shअगरt_pcm_new	28 /* always called */
#घोषणा __rsnd_mod_shअगरt_fallback	28 /* always called */
#घोषणा __rsnd_mod_shअगरt_poपूर्णांकer	28 /* always called */
#घोषणा __rsnd_mod_shअगरt_prepare	28 /* always called */
#घोषणा __rsnd_mod_shअगरt_cleanup	28 /* always called */

#घोषणा __rsnd_mod_add_probe		0
#घोषणा __rsnd_mod_add_हटाओ		0
#घोषणा __rsnd_mod_add_prepare		0
#घोषणा __rsnd_mod_add_cleanup		0
#घोषणा __rsnd_mod_add_init		 1
#घोषणा __rsnd_mod_add_quit		-1
#घोषणा __rsnd_mod_add_start		 1
#घोषणा __rsnd_mod_add_stop		-1
#घोषणा __rsnd_mod_add_hw_params	1
#घोषणा __rsnd_mod_add_hw_मुक्त		-1
#घोषणा __rsnd_mod_add_irq		0
#घोषणा __rsnd_mod_add_pcm_new		0
#घोषणा __rsnd_mod_add_fallback		0
#घोषणा __rsnd_mod_add_poपूर्णांकer		0

#घोषणा __rsnd_mod_call_probe		0
#घोषणा __rsnd_mod_call_हटाओ		0
#घोषणा __rsnd_mod_call_prepare		0
#घोषणा __rsnd_mod_call_cleanup		0
#घोषणा __rsnd_mod_call_init		0
#घोषणा __rsnd_mod_call_quit		1
#घोषणा __rsnd_mod_call_start		0
#घोषणा __rsnd_mod_call_stop		1
#घोषणा __rsnd_mod_call_irq		0
#घोषणा __rsnd_mod_call_pcm_new		0
#घोषणा __rsnd_mod_call_fallback	0
#घोषणा __rsnd_mod_call_hw_params	0
#घोषणा __rsnd_mod_call_poपूर्णांकer		0
#घोषणा __rsnd_mod_call_hw_मुक्त		1

#घोषणा rsnd_mod_to_priv(mod)	((mod)->priv)
#घोषणा rsnd_mod_घातer_on(mod)	clk_enable((mod)->clk)
#घोषणा rsnd_mod_घातer_off(mod)	clk_disable((mod)->clk)
#घोषणा rsnd_mod_get(ip)	(&(ip)->mod)

पूर्णांक rsnd_mod_init(काष्ठा rsnd_priv *priv,
		  काष्ठा rsnd_mod *mod,
		  काष्ठा rsnd_mod_ops *ops,
		  काष्ठा clk *clk,
		  क्रमागत rsnd_mod_type type,
		  पूर्णांक id);
व्योम rsnd_mod_quit(काष्ठा rsnd_mod *mod);
काष्ठा dma_chan *rsnd_mod_dma_req(काष्ठा rsnd_dai_stream *io,
				  काष्ठा rsnd_mod *mod);
व्योम rsnd_mod_पूर्णांकerrupt(काष्ठा rsnd_mod *mod,
			व्योम (*callback)(काष्ठा rsnd_mod *mod,
					 काष्ठा rsnd_dai_stream *io));
u32 *rsnd_mod_get_status(काष्ठा rsnd_mod *mod,
			 काष्ठा rsnd_dai_stream *io,
			 क्रमागत rsnd_mod_type type);
पूर्णांक rsnd_mod_id(काष्ठा rsnd_mod *mod);
पूर्णांक rsnd_mod_id_raw(काष्ठा rsnd_mod *mod);
पूर्णांक rsnd_mod_id_sub(काष्ठा rsnd_mod *mod);
अक्षर *rsnd_mod_name(काष्ठा rsnd_mod *mod);
काष्ठा rsnd_mod *rsnd_mod_next(पूर्णांक *iterator,
			       काष्ठा rsnd_dai_stream *io,
			       क्रमागत rsnd_mod_type *array,
			       पूर्णांक array_size);
#घोषणा क्रम_each_rsnd_mod(iterator, pos, io)				\
	क्रम (iterator = 0;						\
	     (pos = rsnd_mod_next(&iterator, io, शून्य, 0)); iterator++)
#घोषणा क्रम_each_rsnd_mod_arrays(iterator, pos, io, array, size)	\
	क्रम (iterator = 0;						\
	     (pos = rsnd_mod_next(&iterator, io, array, size)); iterator++)
#घोषणा क्रम_each_rsnd_mod_array(iterator, pos, io, array)		\
	क्रम_each_rsnd_mod_arrays(iterator, pos, io, array, ARRAY_SIZE(array))

व्योम rsnd_parse_connect_common(काष्ठा rsnd_dai *rdai,
		काष्ठा rsnd_mod* (*mod_get)(काष्ठा rsnd_priv *priv, पूर्णांक id),
		काष्ठा device_node *node,
		काष्ठा device_node *playback,
		काष्ठा device_node *capture);

पूर्णांक rsnd_channel_normalization(पूर्णांक chan);
#घोषणा rsnd_runसमय_channel_original(io) \
	rsnd_runसमय_channel_original_with_params(io, शून्य)
पूर्णांक rsnd_runसमय_channel_original_with_params(काष्ठा rsnd_dai_stream *io,
				काष्ठा snd_pcm_hw_params *params);
#घोषणा rsnd_runसमय_channel_after_ctu(io)			\
	rsnd_runसमय_channel_after_ctu_with_params(io, शून्य)
पूर्णांक rsnd_runसमय_channel_after_ctu_with_params(काष्ठा rsnd_dai_stream *io,
				काष्ठा snd_pcm_hw_params *params);
#घोषणा rsnd_runसमय_channel_क्रम_ssi(io) \
	rsnd_runसमय_channel_क्रम_ssi_with_params(io, शून्य)
पूर्णांक rsnd_runसमय_channel_क्रम_ssi_with_params(काष्ठा rsnd_dai_stream *io,
				 काष्ठा snd_pcm_hw_params *params);
पूर्णांक rsnd_runसमय_is_multi_ssi(काष्ठा rsnd_dai_stream *io);
पूर्णांक rsnd_runसमय_is_tdm(काष्ठा rsnd_dai_stream *io);
पूर्णांक rsnd_runसमय_is_tdm_split(काष्ठा rsnd_dai_stream *io);

/*
 * DT
 */
#घोषणा rsnd_parse_of_node(priv, node)					\
	of_get_child_by_name(rsnd_priv_to_dev(priv)->of_node, node)
#घोषणा RSND_NODE_DAI	"rcar_sound,dai"
#घोषणा RSND_NODE_SSI	"rcar_sound,ssi"
#घोषणा RSND_NODE_SSIU	"rcar_sound,ssiu"
#घोषणा RSND_NODE_SRC	"rcar_sound,src"
#घोषणा RSND_NODE_CTU	"rcar_sound,ctu"
#घोषणा RSND_NODE_MIX	"rcar_sound,mix"
#घोषणा RSND_NODE_DVC	"rcar_sound,dvc"

/*
 *	R-Car sound DAI
 */
#घोषणा RSND_DAI_NAME_SIZE	16
काष्ठा rsnd_dai_stream अणु
	अक्षर name[RSND_DAI_NAME_SIZE];
	काष्ठा snd_pcm_substream *substream;
	काष्ठा rsnd_mod *mod[RSND_MOD_MAX];
	काष्ठा rsnd_mod *dma;
	काष्ठा rsnd_dai *rdai;
	काष्ठा device *dmac_dev; /* क्रम IPMMU */
	u32 converted_rate;      /* converted sampling rate */
	पूर्णांक converted_chan;      /* converted channels */
	u32 parent_ssi_status;
	u32 flags;
पूर्ण;

/* flags */
#घोषणा RSND_STREAM_HDMI0	(1 << 0) /* क्रम HDMI0 */
#घोषणा RSND_STREAM_HDMI1	(1 << 1) /* क्रम HDMI1 */
#घोषणा RSND_STREAM_TDM_SPLIT	(1 << 2) /* क्रम TDM split mode */

#घोषणा rsnd_io_to_mod(io, i)	((i) < RSND_MOD_MAX ? (io)->mod[(i)] : शून्य)
#घोषणा rsnd_io_to_mod_ssi(io)	rsnd_io_to_mod((io), RSND_MOD_SSI)
#घोषणा rsnd_io_to_mod_ssiu(io)	rsnd_io_to_mod((io), RSND_MOD_SSIU)
#घोषणा rsnd_io_to_mod_ssip(io)	rsnd_io_to_mod((io), RSND_MOD_SSIP)
#घोषणा rsnd_io_to_mod_src(io)	rsnd_io_to_mod((io), RSND_MOD_SRC)
#घोषणा rsnd_io_to_mod_ctu(io)	rsnd_io_to_mod((io), RSND_MOD_CTU)
#घोषणा rsnd_io_to_mod_mix(io)	rsnd_io_to_mod((io), RSND_MOD_MIX)
#घोषणा rsnd_io_to_mod_dvc(io)	rsnd_io_to_mod((io), RSND_MOD_DVC)
#घोषणा rsnd_io_to_mod_cmd(io)	rsnd_io_to_mod((io), RSND_MOD_CMD)
#घोषणा rsnd_io_to_rdai(io)	((io)->rdai)
#घोषणा rsnd_io_to_priv(io)	(rsnd_rdai_to_priv(rsnd_io_to_rdai(io)))
#घोषणा rsnd_io_is_play(io)	(&rsnd_io_to_rdai(io)->playback == io)
#घोषणा rsnd_io_to_runसमय(io) ((io)->substream ? \
				(io)->substream->runसमय : शून्य)
#घोषणा rsnd_io_converted_rate(io)	((io)->converted_rate)
#घोषणा rsnd_io_converted_chan(io)	((io)->converted_chan)
पूर्णांक rsnd_io_is_working(काष्ठा rsnd_dai_stream *io);

काष्ठा rsnd_dai अणु
	अक्षर name[RSND_DAI_NAME_SIZE];
	काष्ठा rsnd_dai_stream playback;
	काष्ठा rsnd_dai_stream capture;
	काष्ठा rsnd_priv *priv;
	काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांक;

	पूर्णांक max_channels;	/* 2ch - 16ch */
	पूर्णांक ssi_lane;		/* 1lane - 4lane */
	पूर्णांक chan_width;		/* 16/24/32 bit width */

	अचिन्हित पूर्णांक clk_master:1;
	अचिन्हित पूर्णांक bit_clk_inv:1;
	अचिन्हित पूर्णांक frm_clk_inv:1;
	अचिन्हित पूर्णांक sys_delay:1;
	अचिन्हित पूर्णांक data_alignment:1;
पूर्ण;

#घोषणा rsnd_rdai_nr(priv) ((priv)->rdai_nr)
#घोषणा rsnd_rdai_is_clk_master(rdai) ((rdai)->clk_master)
#घोषणा rsnd_rdai_to_priv(rdai) ((rdai)->priv)
#घोषणा क्रम_each_rsnd_dai(rdai, priv, i)		\
	क्रम (i = 0;					\
	     (i < rsnd_rdai_nr(priv)) &&		\
	     ((rdai) = rsnd_rdai_get(priv, i));		\
	     i++)

काष्ठा rsnd_dai *rsnd_rdai_get(काष्ठा rsnd_priv *priv, पूर्णांक id);

#घोषणा rsnd_rdai_channels_set(rdai, max_channels) \
	rsnd_rdai_channels_ctrl(rdai, max_channels)
#घोषणा rsnd_rdai_channels_get(rdai) \
	rsnd_rdai_channels_ctrl(rdai, 0)
पूर्णांक rsnd_rdai_channels_ctrl(काष्ठा rsnd_dai *rdai,
			    पूर्णांक max_channels);

#घोषणा rsnd_rdai_ssi_lane_set(rdai, ssi_lane) \
	rsnd_rdai_ssi_lane_ctrl(rdai, ssi_lane)
#घोषणा rsnd_rdai_ssi_lane_get(rdai) \
	rsnd_rdai_ssi_lane_ctrl(rdai, 0)
पूर्णांक rsnd_rdai_ssi_lane_ctrl(काष्ठा rsnd_dai *rdai,
			    पूर्णांक ssi_lane);

#घोषणा rsnd_rdai_width_set(rdai, width) \
	rsnd_rdai_width_ctrl(rdai, width)
#घोषणा rsnd_rdai_width_get(rdai) \
	rsnd_rdai_width_ctrl(rdai, 0)
पूर्णांक rsnd_rdai_width_ctrl(काष्ठा rsnd_dai *rdai, पूर्णांक width);
व्योम rsnd_dai_period_elapsed(काष्ठा rsnd_dai_stream *io);
पूर्णांक rsnd_dai_connect(काष्ठा rsnd_mod *mod,
		     काष्ठा rsnd_dai_stream *io,
		     क्रमागत rsnd_mod_type type);

/*
 *	R-Car Gen1/Gen2
 */
पूर्णांक rsnd_gen_probe(काष्ठा rsnd_priv *priv);
व्योम __iomem *rsnd_gen_reg_get(काष्ठा rsnd_priv *priv,
			       काष्ठा rsnd_mod *mod,
			       क्रमागत rsnd_reg reg);
phys_addr_t rsnd_gen_get_phy_addr(काष्ठा rsnd_priv *priv, पूर्णांक reg_id);

/*
 *	R-Car ADG
 */
पूर्णांक rsnd_adg_clk_query(काष्ठा rsnd_priv *priv, अचिन्हित पूर्णांक rate);
पूर्णांक rsnd_adg_ssi_clk_stop(काष्ठा rsnd_mod *ssi_mod);
पूर्णांक rsnd_adg_ssi_clk_try_start(काष्ठा rsnd_mod *ssi_mod, अचिन्हित पूर्णांक rate);
पूर्णांक rsnd_adg_probe(काष्ठा rsnd_priv *priv);
व्योम rsnd_adg_हटाओ(काष्ठा rsnd_priv *priv);
पूर्णांक rsnd_adg_set_src_बारel_gen2(काष्ठा rsnd_mod *src_mod,
				  काष्ठा rsnd_dai_stream *io,
				  अचिन्हित पूर्णांक in_rate,
				  अचिन्हित पूर्णांक out_rate);
पूर्णांक rsnd_adg_set_cmd_timsel_gen2(काष्ठा rsnd_mod *cmd_mod,
				 काष्ठा rsnd_dai_stream *io);
#घोषणा rsnd_adg_clk_enable(priv)	rsnd_adg_clk_control(priv, 1)
#घोषणा rsnd_adg_clk_disable(priv)	rsnd_adg_clk_control(priv, 0)
व्योम rsnd_adg_clk_control(काष्ठा rsnd_priv *priv, पूर्णांक enable);

/*
 *	R-Car sound priv
 */
काष्ठा rsnd_priv अणु

	काष्ठा platक्रमm_device *pdev;
	spinlock_t lock;
	अचिन्हित दीर्घ flags;
#घोषणा RSND_GEN_MASK	(0xF << 0)
#घोषणा RSND_GEN1	(1 << 0)
#घोषणा RSND_GEN2	(2 << 0)
#घोषणा RSND_GEN3	(3 << 0)
#घोषणा RSND_SOC_MASK	(0xFF << 4)
#घोषणा RSND_SOC_E	(1 << 4) /* E1/E2/E3 */

	/*
	 * below value will be filled on rsnd_gen_probe()
	 */
	व्योम *gen;

	/*
	 * below value will be filled on rsnd_adg_probe()
	 */
	व्योम *adg;

	/*
	 * below value will be filled on rsnd_dma_probe()
	 */
	व्योम *dma;

	/*
	 * below value will be filled on rsnd_ssi_probe()
	 */
	व्योम *ssi;
	पूर्णांक ssi_nr;

	/*
	 * below value will be filled on rsnd_ssiu_probe()
	 */
	व्योम *ssiu;
	पूर्णांक ssiu_nr;

	/*
	 * below value will be filled on rsnd_src_probe()
	 */
	व्योम *src;
	पूर्णांक src_nr;

	/*
	 * below value will be filled on rsnd_ctu_probe()
	 */
	व्योम *ctu;
	पूर्णांक ctu_nr;

	/*
	 * below value will be filled on rsnd_mix_probe()
	 */
	व्योम *mix;
	पूर्णांक mix_nr;

	/*
	 * below value will be filled on rsnd_dvc_probe()
	 */
	व्योम *dvc;
	पूर्णांक dvc_nr;

	/*
	 * below value will be filled on rsnd_cmd_probe()
	 */
	व्योम *cmd;
	पूर्णांक cmd_nr;

	/*
	 * below value will be filled on rsnd_dai_probe()
	 */
	काष्ठा snd_soc_dai_driver *daidrv;
	काष्ठा rsnd_dai *rdai;
	पूर्णांक rdai_nr;
पूर्ण;

#घोषणा rsnd_priv_to_pdev(priv)	((priv)->pdev)
#घोषणा rsnd_priv_to_dev(priv)	(&(rsnd_priv_to_pdev(priv)->dev))

#घोषणा rsnd_is_gen1(priv)	(((priv)->flags & RSND_GEN_MASK) == RSND_GEN1)
#घोषणा rsnd_is_gen2(priv)	(((priv)->flags & RSND_GEN_MASK) == RSND_GEN2)
#घोषणा rsnd_is_gen3(priv)	(((priv)->flags & RSND_GEN_MASK) == RSND_GEN3)
#घोषणा rsnd_is_e3(priv)	(((priv)->flags & \
					(RSND_GEN_MASK | RSND_SOC_MASK)) == \
					(RSND_GEN3 | RSND_SOC_E))

#घोषणा rsnd_flags_has(p, f) ((p)->flags & (f))
#घोषणा rsnd_flags_set(p, f) ((p)->flags |= (f))
#घोषणा rsnd_flags_del(p, f) ((p)->flags &= ~(f))

/*
 *	rsnd_kctrl
 */
काष्ठा rsnd_kctrl_cfg अणु
	अचिन्हित पूर्णांक max;
	अचिन्हित पूर्णांक size;
	u32 *val;
	स्थिर अक्षर * स्थिर *texts;
	पूर्णांक (*accept)(काष्ठा rsnd_dai_stream *io);
	व्योम (*update)(काष्ठा rsnd_dai_stream *io, काष्ठा rsnd_mod *mod);
	काष्ठा rsnd_dai_stream *io;
	काष्ठा snd_card *card;
	काष्ठा snd_kcontrol *kctrl;
	काष्ठा rsnd_mod *mod;
पूर्ण;

#घोषणा RSND_MAX_CHANNELS	8
काष्ठा rsnd_kctrl_cfg_m अणु
	काष्ठा rsnd_kctrl_cfg cfg;
	u32 val[RSND_MAX_CHANNELS];
पूर्ण;

काष्ठा rsnd_kctrl_cfg_s अणु
	काष्ठा rsnd_kctrl_cfg cfg;
	u32 val;
पूर्ण;
#घोषणा rsnd_kctrl_size(x)	((x).cfg.size)
#घोषणा rsnd_kctrl_max(x)	((x).cfg.max)
#घोषणा rsnd_kctrl_valm(x, i)	((x).val[i])	/* = (x).cfg.val[i] */
#घोषणा rsnd_kctrl_vals(x)	((x).val)	/* = (x).cfg.val[0] */

पूर्णांक rsnd_kctrl_accept_anyसमय(काष्ठा rsnd_dai_stream *io);
पूर्णांक rsnd_kctrl_accept_runसमय(काष्ठा rsnd_dai_stream *io);
काष्ठा rsnd_kctrl_cfg *rsnd_kctrl_init_m(काष्ठा rsnd_kctrl_cfg_m *cfg);
काष्ठा rsnd_kctrl_cfg *rsnd_kctrl_init_s(काष्ठा rsnd_kctrl_cfg_s *cfg);
पूर्णांक rsnd_kctrl_new(काष्ठा rsnd_mod *mod,
		   काष्ठा rsnd_dai_stream *io,
		   काष्ठा snd_soc_pcm_runसमय *rtd,
		   स्थिर अचिन्हित अक्षर *name,
		   पूर्णांक (*accept)(काष्ठा rsnd_dai_stream *io),
		   व्योम (*update)(काष्ठा rsnd_dai_stream *io,
				  काष्ठा rsnd_mod *mod),
		   काष्ठा rsnd_kctrl_cfg *cfg,
		   स्थिर अक्षर * स्थिर *texts,
		   पूर्णांक size,
		   u32 max);

#घोषणा rsnd_kctrl_new_m(mod, io, rtd, name, accept, update, cfg, size, max) \
	rsnd_kctrl_new(mod, io, rtd, name, accept, update, rsnd_kctrl_init_m(cfg), \
		       शून्य, size, max)

#घोषणा rsnd_kctrl_new_s(mod, io, rtd, name, accept, update, cfg, max)	\
	rsnd_kctrl_new(mod, io, rtd, name, accept, update, rsnd_kctrl_init_s(cfg), \
		       शून्य, 1, max)

#घोषणा rsnd_kctrl_new_e(mod, io, rtd, name, accept, update, cfg, texts, size) \
	rsnd_kctrl_new(mod, io, rtd, name, accept, update, rsnd_kctrl_init_s(cfg), \
		       texts, 1, size)

बाह्य स्थिर अक्षर * स्थिर volume_ramp_rate[];
#घोषणा VOLUME_RAMP_MAX_DVC	(0x17 + 1)
#घोषणा VOLUME_RAMP_MAX_MIX	(0x0a + 1)

/*
 *	R-Car SSI
 */
पूर्णांक rsnd_ssi_probe(काष्ठा rsnd_priv *priv);
व्योम rsnd_ssi_हटाओ(काष्ठा rsnd_priv *priv);
काष्ठा rsnd_mod *rsnd_ssi_mod_get(काष्ठा rsnd_priv *priv, पूर्णांक id);
पूर्णांक rsnd_ssi_use_busअगर(काष्ठा rsnd_dai_stream *io);
u32 rsnd_ssi_multi_secondaries_runसमय(काष्ठा rsnd_dai_stream *io);

#घोषणा rsnd_ssi_is_pin_sharing(io)	\
	__rsnd_ssi_is_pin_sharing(rsnd_io_to_mod_ssi(io))
पूर्णांक __rsnd_ssi_is_pin_sharing(काष्ठा rsnd_mod *mod);

#घोषणा rsnd_ssi_of_node(priv) rsnd_parse_of_node(priv, RSND_NODE_SSI)
व्योम rsnd_parse_connect_ssi(काष्ठा rsnd_dai *rdai,
			    काष्ठा device_node *playback,
			    काष्ठा device_node *capture);
अचिन्हित पूर्णांक rsnd_ssi_clk_query(काष्ठा rsnd_dai *rdai,
		       पूर्णांक param1, पूर्णांक param2, पूर्णांक *idx);

/*
 *	R-Car SSIU
 */
पूर्णांक rsnd_ssiu_attach(काष्ठा rsnd_dai_stream *io,
		     काष्ठा rsnd_mod *mod);
पूर्णांक rsnd_ssiu_probe(काष्ठा rsnd_priv *priv);
व्योम rsnd_ssiu_हटाओ(काष्ठा rsnd_priv *priv);
व्योम rsnd_parse_connect_ssiu(काष्ठा rsnd_dai *rdai,
			     काष्ठा device_node *playback,
			     काष्ठा device_node *capture);
#घोषणा rsnd_ssiu_of_node(priv) rsnd_parse_of_node(priv, RSND_NODE_SSIU)

/*
 *	R-Car SRC
 */
पूर्णांक rsnd_src_probe(काष्ठा rsnd_priv *priv);
व्योम rsnd_src_हटाओ(काष्ठा rsnd_priv *priv);
काष्ठा rsnd_mod *rsnd_src_mod_get(काष्ठा rsnd_priv *priv, पूर्णांक id);

#घोषणा rsnd_src_get_in_rate(priv, io) rsnd_src_get_rate(priv, io, 1)
#घोषणा rsnd_src_get_out_rate(priv, io) rsnd_src_get_rate(priv, io, 0)
अचिन्हित पूर्णांक rsnd_src_get_rate(काष्ठा rsnd_priv *priv,
			       काष्ठा rsnd_dai_stream *io,
			       पूर्णांक is_in);

#घोषणा rsnd_src_of_node(priv) rsnd_parse_of_node(priv, RSND_NODE_SRC)
#घोषणा rsnd_parse_connect_src(rdai, playback, capture)			\
	rsnd_parse_connect_common(rdai, rsnd_src_mod_get,		\
				  rsnd_src_of_node(rsnd_rdai_to_priv(rdai)), \
						   playback, capture)

/*
 *	R-Car CTU
 */
पूर्णांक rsnd_ctu_probe(काष्ठा rsnd_priv *priv);
व्योम rsnd_ctu_हटाओ(काष्ठा rsnd_priv *priv);
काष्ठा rsnd_mod *rsnd_ctu_mod_get(काष्ठा rsnd_priv *priv, पूर्णांक id);
#घोषणा rsnd_ctu_of_node(priv) rsnd_parse_of_node(priv, RSND_NODE_CTU)
#घोषणा rsnd_parse_connect_ctu(rdai, playback, capture)			\
	rsnd_parse_connect_common(rdai, rsnd_ctu_mod_get,		\
				  rsnd_ctu_of_node(rsnd_rdai_to_priv(rdai)), \
						   playback, capture)

/*
 *	R-Car MIX
 */
पूर्णांक rsnd_mix_probe(काष्ठा rsnd_priv *priv);
व्योम rsnd_mix_हटाओ(काष्ठा rsnd_priv *priv);
काष्ठा rsnd_mod *rsnd_mix_mod_get(काष्ठा rsnd_priv *priv, पूर्णांक id);
#घोषणा rsnd_mix_of_node(priv) rsnd_parse_of_node(priv, RSND_NODE_MIX)
#घोषणा rsnd_parse_connect_mix(rdai, playback, capture)			\
	rsnd_parse_connect_common(rdai, rsnd_mix_mod_get,		\
				  rsnd_mix_of_node(rsnd_rdai_to_priv(rdai)), \
						   playback, capture)

/*
 *	R-Car DVC
 */
पूर्णांक rsnd_dvc_probe(काष्ठा rsnd_priv *priv);
व्योम rsnd_dvc_हटाओ(काष्ठा rsnd_priv *priv);
काष्ठा rsnd_mod *rsnd_dvc_mod_get(काष्ठा rsnd_priv *priv, पूर्णांक id);
#घोषणा rsnd_dvc_of_node(priv) rsnd_parse_of_node(priv, RSND_NODE_DVC)
#घोषणा rsnd_parse_connect_dvc(rdai, playback, capture)			\
	rsnd_parse_connect_common(rdai, rsnd_dvc_mod_get,		\
				  rsnd_dvc_of_node(rsnd_rdai_to_priv(rdai)), \
						   playback, capture)

/*
 *	R-Car CMD
 */
पूर्णांक rsnd_cmd_probe(काष्ठा rsnd_priv *priv);
व्योम rsnd_cmd_हटाओ(काष्ठा rsnd_priv *priv);
पूर्णांक rsnd_cmd_attach(काष्ठा rsnd_dai_stream *io, पूर्णांक id);

व्योम rsnd_mod_make_sure(काष्ठा rsnd_mod *mod, क्रमागत rsnd_mod_type type);
#अगर_घोषित DEBUG
#घोषणा rsnd_mod_confirm_ssi(mssi)	rsnd_mod_make_sure(mssi, RSND_MOD_SSI)
#घोषणा rsnd_mod_confirm_src(msrc)	rsnd_mod_make_sure(msrc, RSND_MOD_SRC)
#घोषणा rsnd_mod_confirm_dvc(mdvc)	rsnd_mod_make_sure(mdvc, RSND_MOD_DVC)
#अन्यथा
#घोषणा rsnd_mod_confirm_ssi(mssi)
#घोषणा rsnd_mod_confirm_src(msrc)
#घोषणा rsnd_mod_confirm_dvc(mdvc)
#पूर्ण_अगर

/*
 * If you करोn't need पूर्णांकerrupt status debug message,
 * define RSND_DEBUG_NO_IRQ_STATUS as 1 on top of src.c/ssi.c
 *
 * #घोषणा RSND_DEBUG_NO_IRQ_STATUS 1
 */
#घोषणा rsnd_dbg_irq_status(dev, param...)		\
	अगर (!IS_BUILTIN(RSND_DEBUG_NO_IRQ_STATUS))	\
		dev_dbg(dev, param)

/*
 * If you करोn't need rsnd_dai_call debug message,
 * define RSND_DEBUG_NO_DAI_CALL as 1 on top of core.c
 *
 * #घोषणा RSND_DEBUG_NO_DAI_CALL 1
 */
#घोषणा rsnd_dbg_dai_call(dev, param...)		\
	अगर (!IS_BUILTIN(RSND_DEBUG_NO_DAI_CALL))	\
		dev_dbg(dev, param)

#पूर्ण_अगर
