<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// siu_dai.c - ALSA SoC driver क्रम Renesas SH7343, SH7722 SIU peripheral.
//
// Copyright (C) 2009-2010 Guennadi Liakhovetski <g.liakhovetski@gmx.de>
// Copyright (C) 2006 Carlos Munoz <carlos@kenati.com>

#समावेश <linux/delay.h>
#समावेश <linux/firmware.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

#समावेश <यंत्र/घड़ी.h>
#समावेश <यंत्र/siu.h>

#समावेश <sound/control.h>
#समावेश <sound/soc.h>

#समावेश "siu.h"

/* Board specअगरics */
#अगर defined(CONFIG_CPU_SUBTYPE_SH7722)
# define SIU_MAX_VOLUME		0x1000
#अन्यथा
# define SIU_MAX_VOLUME		0x7fff
#पूर्ण_अगर

#घोषणा PRAM_SIZE	0x2000
#घोषणा XRAM_SIZE	0x800
#घोषणा YRAM_SIZE	0x800

#घोषणा XRAM_OFFSET	0x4000
#घोषणा YRAM_OFFSET	0x6000
#घोषणा REG_OFFSET	0xc000

#घोषणा PLAYBACK_ENABLED	1
#घोषणा CAPTURE_ENABLED		2

#घोषणा VOLUME_CAPTURE		0
#घोषणा VOLUME_PLAYBACK		1
#घोषणा DFLT_VOLUME_LEVEL	0x08000800

/*
 * SPDIF is only available on port A and on some SIU implementations it is only
 * available क्रम input. Due to the lack of hardware to test it, SPDIF is left
 * disabled in this driver version
 */
काष्ठा क्रमmat_flag अणु
	u32	i2s;
	u32	pcm;
	u32	spdअगर;
	u32	mask;
पूर्ण;

काष्ठा port_flag अणु
	काष्ठा क्रमmat_flag	playback;
	काष्ठा क्रमmat_flag	capture;
पूर्ण;

काष्ठा siu_info *siu_i2s_data;

अटल काष्ठा port_flag siu_flags[SIU_PORT_NUM] = अणु
	[SIU_PORT_A] = अणु
		.playback = अणु
			.i2s	= 0x50000000,
			.pcm	= 0x40000000,
			.spdअगर	= 0x80000000,	/* not on all SIU versions */
			.mask	= 0xd0000000,
		पूर्ण,
		.capture = अणु
			.i2s	= 0x05000000,
			.pcm	= 0x04000000,
			.spdअगर	= 0x08000000,
			.mask	= 0x0d000000,
		पूर्ण,
	पूर्ण,
	[SIU_PORT_B] = अणु
		.playback = अणु
			.i2s	= 0x00500000,
			.pcm	= 0x00400000,
			.spdअगर	= 0,		/* impossible - turn off */
			.mask	= 0x00500000,
		पूर्ण,
		.capture = अणु
			.i2s	= 0x00050000,
			.pcm	= 0x00040000,
			.spdअगर	= 0,		/* impossible - turn off */
			.mask	= 0x00050000,
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम siu_dai_start(काष्ठा siu_port *port_info)
अणु
	काष्ठा siu_info *info = siu_i2s_data;
	u32 __iomem *base = info->reg;

	dev_dbg(port_info->pcm->card->dev, "%s\n", __func__);

	/* Issue software reset to siu */
	siu_ग_लिखो32(base + SIU_SRCTL, 0);

	/* Wait क्रम the reset to take effect */
	udelay(1);

	port_info->stfअगरo = 0;
	port_info->trdat = 0;

	/* portA, portB, SIU operate */
	siu_ग_लिखो32(base + SIU_SRCTL, 0x301);

	/* portA=256fs, portB=256fs */
	siu_ग_लिखो32(base + SIU_CKCTL, 0x40400000);

	/* portA's BRG करोes not भागide SIUCKA */
	siu_ग_लिखो32(base + SIU_BRGASEL, 0);
	siu_ग_लिखो32(base + SIU_BRRA, 0);

	/* portB's BRG भागides SIUCKB by half */
	siu_ग_लिखो32(base + SIU_BRGBSEL, 1);
	siu_ग_लिखो32(base + SIU_BRRB, 0);

	siu_ग_लिखो32(base + SIU_IFCTL, 0x44440000);

	/* portA: 32 bit/fs, master; portB: 32 bit/fs, master */
	siu_ग_लिखो32(base + SIU_SFORM, 0x0c0c0000);

	/*
	 * Volume levels: looks like the DSP firmware implements volume controls
	 * dअगरferently from what's described in the datasheet
	 */
	siu_ग_लिखो32(base + SIU_SBDVCA, port_info->playback.volume);
	siu_ग_लिखो32(base + SIU_SBDVCB, port_info->capture.volume);
पूर्ण

अटल व्योम siu_dai_stop(काष्ठा siu_port *port_info)
अणु
	काष्ठा siu_info *info = siu_i2s_data;
	u32 __iomem *base = info->reg;

	/* SIU software reset */
	siu_ग_लिखो32(base + SIU_SRCTL, 0);
पूर्ण

अटल व्योम siu_dai_spbAselect(काष्ठा siu_port *port_info)
अणु
	काष्ठा siu_info *info = siu_i2s_data;
	काष्ठा siu_firmware *fw = &info->fw;
	u32 *ydef = fw->yram0;
	u32 idx;

	/* path A use */
	अगर (!info->port_id)
		idx = 1;		/* portA */
	अन्यथा
		idx = 2;		/* portB */

	ydef[0] = (fw->spbpar[idx].ab1a << 16) |
		(fw->spbpar[idx].ab0a << 8) |
		(fw->spbpar[idx].dir << 7) | 3;
	ydef[1] = fw->yram0[1];	/* 0x03000300 */
	ydef[2] = (16 / 2) << 24;
	ydef[3] = fw->yram0[3];	/* 0 */
	ydef[4] = fw->yram0[4];	/* 0 */
	ydef[7] = fw->spbpar[idx].event;
	port_info->stfअगरo |= fw->spbpar[idx].stfअगरo;
	port_info->trdat |= fw->spbpar[idx].trdat;
पूर्ण

अटल व्योम siu_dai_spbBselect(काष्ठा siu_port *port_info)
अणु
	काष्ठा siu_info *info = siu_i2s_data;
	काष्ठा siu_firmware *fw = &info->fw;
	u32 *ydef = fw->yram0;
	u32 idx;

	/* path B use */
	अगर (!info->port_id)
		idx = 7;		/* portA */
	अन्यथा
		idx = 8;		/* portB */

	ydef[5] = (fw->spbpar[idx].ab1a << 16) |
		(fw->spbpar[idx].ab0a << 8) | 1;
	ydef[6] = fw->spbpar[idx].event;
	port_info->stfअगरo |= fw->spbpar[idx].stfअगरo;
	port_info->trdat |= fw->spbpar[idx].trdat;
पूर्ण

अटल व्योम siu_dai_खोलो(काष्ठा siu_stream *siu_stream)
अणु
	काष्ठा siu_info *info = siu_i2s_data;
	u32 __iomem *base = info->reg;
	u32 srctl, अगरctl;

	srctl = siu_पढ़ो32(base + SIU_SRCTL);
	अगरctl = siu_पढ़ो32(base + SIU_IFCTL);

	चयन (info->port_id) अणु
	हाल SIU_PORT_A:
		/* portA operates */
		srctl |= 0x200;
		अगरctl &= ~0xc2;
		अवरोध;
	हाल SIU_PORT_B:
		/* portB operates */
		srctl |= 0x100;
		अगरctl &= ~0x31;
		अवरोध;
	पूर्ण

	siu_ग_लिखो32(base + SIU_SRCTL, srctl);
	/* Unmute and configure portA */
	siu_ग_लिखो32(base + SIU_IFCTL, अगरctl);
पूर्ण

/*
 * At the moment only fixed Left-upper, Left-lower, Right-upper, Right-lower
 * packing is supported
 */
अटल व्योम siu_dai_pcmdatapack(काष्ठा siu_stream *siu_stream)
अणु
	काष्ठा siu_info *info = siu_i2s_data;
	u32 __iomem *base = info->reg;
	u32 dpak;

	dpak = siu_पढ़ो32(base + SIU_DPAK);

	चयन (info->port_id) अणु
	हाल SIU_PORT_A:
		dpak &= ~0xc0000000;
		अवरोध;
	हाल SIU_PORT_B:
		dpak &= ~0x00c00000;
		अवरोध;
	पूर्ण

	siu_ग_लिखो32(base + SIU_DPAK, dpak);
पूर्ण

अटल पूर्णांक siu_dai_spbstart(काष्ठा siu_port *port_info)
अणु
	काष्ठा siu_info *info = siu_i2s_data;
	u32 __iomem *base = info->reg;
	काष्ठा siu_firmware *fw = &info->fw;
	u32 *ydef = fw->yram0;
	पूर्णांक cnt;
	u32 __iomem *add;
	u32 *ptr;

	/* Load SPB Program in PRAM */
	ptr = fw->pram0;
	add = info->pram;
	क्रम (cnt = 0; cnt < PRAM0_SIZE; cnt++, add++, ptr++)
		siu_ग_लिखो32(add, *ptr);

	ptr = fw->pram1;
	add = info->pram + (0x0100 / माप(u32));
	क्रम (cnt = 0; cnt < PRAM1_SIZE; cnt++, add++, ptr++)
		siu_ग_लिखो32(add, *ptr);

	/* XRAM initialization */
	add = info->xram;
	क्रम (cnt = 0; cnt < XRAM0_SIZE + XRAM1_SIZE + XRAM2_SIZE; cnt++, add++)
		siu_ग_लिखो32(add, 0);

	/* YRAM variable area initialization */
	add = info->yram;
	क्रम (cnt = 0; cnt < YRAM_DEF_SIZE; cnt++, add++)
		siu_ग_लिखो32(add, ydef[cnt]);

	/* YRAM FIR coefficient area initialization */
	add = info->yram + (0x0200 / माप(u32));
	क्रम (cnt = 0; cnt < YRAM_FIR_SIZE; cnt++, add++)
		siu_ग_लिखो32(add, fw->yram_fir_coeff[cnt]);

	/* YRAM IIR coefficient area initialization */
	add = info->yram + (0x0600 / माप(u32));
	क्रम (cnt = 0; cnt < YRAM_IIR_SIZE; cnt++, add++)
		siu_ग_लिखो32(add, 0);

	siu_ग_लिखो32(base + SIU_TRDAT, port_info->trdat);
	port_info->trdat = 0x0;


	/* SPB start condition: software */
	siu_ग_लिखो32(base + SIU_SBACTIV, 0);
	/* Start SPB */
	siu_ग_लिखो32(base + SIU_SBCTL, 0xc0000000);
	/* Wait क्रम program to halt */
	cnt = 0x10000;
	जबतक (--cnt && siu_पढ़ो32(base + SIU_SBCTL) != 0x80000000)
		cpu_relax();

	अगर (!cnt)
		वापस -EBUSY;

	/* SPB program start address setting */
	siu_ग_लिखो32(base + SIU_SBPSET, 0x00400000);
	/* SPB hardware start(FIFOCTL source) */
	siu_ग_लिखो32(base + SIU_SBACTIV, 0xc0000000);

	वापस 0;
पूर्ण

अटल व्योम siu_dai_spbstop(काष्ठा siu_port *port_info)
अणु
	काष्ठा siu_info *info = siu_i2s_data;
	u32 __iomem *base = info->reg;

	siu_ग_लिखो32(base + SIU_SBACTIV, 0);
	/* SPB stop */
	siu_ग_लिखो32(base + SIU_SBCTL, 0);

	port_info->stfअगरo = 0;
पूर्ण

/*		API functions		*/

/* Playback and capture hardware properties are identical */
अटल स्थिर काष्ठा snd_pcm_hardware siu_dai_pcm_hw = अणु
	.info			= SNDRV_PCM_INFO_INTERLEAVED,
	.क्रमmats		= SNDRV_PCM_FMTBIT_S16,
	.rates			= SNDRV_PCM_RATE_8000_48000,
	.rate_min		= 8000,
	.rate_max		= 48000,
	.channels_min		= 2,
	.channels_max		= 2,
	.buffer_bytes_max	= SIU_BUFFER_BYTES_MAX,
	.period_bytes_min	= SIU_PERIOD_BYTES_MIN,
	.period_bytes_max	= SIU_PERIOD_BYTES_MAX,
	.periods_min		= SIU_PERIODS_MIN,
	.periods_max		= SIU_PERIODS_MAX,
पूर्ण;

अटल पूर्णांक siu_dai_info_volume(काष्ठा snd_kcontrol *kctrl,
			       काष्ठा snd_ctl_elem_info *uinfo)
अणु
	काष्ठा siu_port *port_info = snd_kcontrol_chip(kctrl);

	dev_dbg(port_info->pcm->card->dev, "%s\n", __func__);

	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 2;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = SIU_MAX_VOLUME;

	वापस 0;
पूर्ण

अटल पूर्णांक siu_dai_get_volume(काष्ठा snd_kcontrol *kctrl,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा siu_port *port_info = snd_kcontrol_chip(kctrl);
	काष्ठा device *dev = port_info->pcm->card->dev;
	u32 vol;

	dev_dbg(dev, "%s\n", __func__);

	चयन (kctrl->निजी_value) अणु
	हाल VOLUME_PLAYBACK:
		/* Playback is always on port 0 */
		vol = port_info->playback.volume;
		ucontrol->value.पूर्णांकeger.value[0] = vol & 0xffff;
		ucontrol->value.पूर्णांकeger.value[1] = vol >> 16 & 0xffff;
		अवरोध;
	हाल VOLUME_CAPTURE:
		/* Capture is always on port 1 */
		vol = port_info->capture.volume;
		ucontrol->value.पूर्णांकeger.value[0] = vol & 0xffff;
		ucontrol->value.पूर्णांकeger.value[1] = vol >> 16 & 0xffff;
		अवरोध;
	शेष:
		dev_err(dev, "%s() invalid private_value=%ld\n",
			__func__, kctrl->निजी_value);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक siu_dai_put_volume(काष्ठा snd_kcontrol *kctrl,
			      काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा siu_port *port_info = snd_kcontrol_chip(kctrl);
	काष्ठा device *dev = port_info->pcm->card->dev;
	काष्ठा siu_info *info = siu_i2s_data;
	u32 __iomem *base = info->reg;
	u32 new_vol;
	u32 cur_vol;

	dev_dbg(dev, "%s\n", __func__);

	अगर (ucontrol->value.पूर्णांकeger.value[0] < 0 ||
	    ucontrol->value.पूर्णांकeger.value[0] > SIU_MAX_VOLUME ||
	    ucontrol->value.पूर्णांकeger.value[1] < 0 ||
	    ucontrol->value.पूर्णांकeger.value[1] > SIU_MAX_VOLUME)
		वापस -EINVAL;

	new_vol = ucontrol->value.पूर्णांकeger.value[0] |
		ucontrol->value.पूर्णांकeger.value[1] << 16;

	/* See comment above - DSP firmware implementation */
	चयन (kctrl->निजी_value) अणु
	हाल VOLUME_PLAYBACK:
		/* Playback is always on port 0 */
		cur_vol = port_info->playback.volume;
		siu_ग_लिखो32(base + SIU_SBDVCA, new_vol);
		port_info->playback.volume = new_vol;
		अवरोध;
	हाल VOLUME_CAPTURE:
		/* Capture is always on port 1 */
		cur_vol = port_info->capture.volume;
		siu_ग_लिखो32(base + SIU_SBDVCB, new_vol);
		port_info->capture.volume = new_vol;
		अवरोध;
	शेष:
		dev_err(dev, "%s() invalid private_value=%ld\n",
			__func__, kctrl->निजी_value);
		वापस -EINVAL;
	पूर्ण

	अगर (cur_vol != new_vol)
		वापस 1;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new playback_controls = अणु
	.अगरace		= SNDRV_CTL_ELEM_IFACE_MIXER,
	.name		= "PCM Playback Volume",
	.index		= 0,
	.info		= siu_dai_info_volume,
	.get		= siu_dai_get_volume,
	.put		= siu_dai_put_volume,
	.निजी_value	= VOLUME_PLAYBACK,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new capture_controls = अणु
	.अगरace		= SNDRV_CTL_ELEM_IFACE_MIXER,
	.name		= "PCM Capture Volume",
	.index		= 0,
	.info		= siu_dai_info_volume,
	.get		= siu_dai_get_volume,
	.put		= siu_dai_put_volume,
	.निजी_value	= VOLUME_CAPTURE,
पूर्ण;

पूर्णांक siu_init_port(पूर्णांक port, काष्ठा siu_port **port_info, काष्ठा snd_card *card)
अणु
	काष्ठा device *dev = card->dev;
	काष्ठा snd_kcontrol *kctrl;
	पूर्णांक ret;

	*port_info = kzalloc(माप(**port_info), GFP_KERNEL);
	अगर (!*port_info)
		वापस -ENOMEM;

	dev_dbg(dev, "%s: port #%d@%p\n", __func__, port, *port_info);

	(*port_info)->playback.volume = DFLT_VOLUME_LEVEL;
	(*port_info)->capture.volume = DFLT_VOLUME_LEVEL;

	/*
	 * Add mixer support. The SPB is used to change the volume. Both
	 * ports use the same SPB. Thereक्रमe, we only रेजिस्टर one
	 * control instance since it will be used by both channels.
	 * In error हाल we जारी without controls.
	 */
	kctrl = snd_ctl_new1(&playback_controls, *port_info);
	ret = snd_ctl_add(card, kctrl);
	अगर (ret < 0)
		dev_err(dev,
			"failed to add playback controls %p port=%d err=%d\n",
			kctrl, port, ret);

	kctrl = snd_ctl_new1(&capture_controls, *port_info);
	ret = snd_ctl_add(card, kctrl);
	अगर (ret < 0)
		dev_err(dev,
			"failed to add capture controls %p port=%d err=%d\n",
			kctrl, port, ret);

	वापस 0;
पूर्ण

व्योम siu_मुक्त_port(काष्ठा siu_port *port_info)
अणु
	kमुक्त(port_info);
पूर्ण

अटल पूर्णांक siu_dai_startup(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा siu_info *info = snd_soc_dai_get_drvdata(dai);
	काष्ठा snd_pcm_runसमय *rt = substream->runसमय;
	काष्ठा siu_port	*port_info = siu_port_info(substream);
	पूर्णांक ret;

	dev_dbg(substream->pcm->card->dev, "%s: port=%d@%p\n", __func__,
		info->port_id, port_info);

	snd_soc_set_runसमय_hwparams(substream, &siu_dai_pcm_hw);

	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(rt, SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (unlikely(ret < 0))
		वापस ret;

	siu_dai_start(port_info);

	वापस 0;
पूर्ण

अटल व्योम siu_dai_shutकरोwn(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा siu_info *info = snd_soc_dai_get_drvdata(dai);
	काष्ठा siu_port	*port_info = siu_port_info(substream);

	dev_dbg(substream->pcm->card->dev, "%s: port=%d@%p\n", __func__,
		info->port_id, port_info);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		port_info->play_cap &= ~PLAYBACK_ENABLED;
	अन्यथा
		port_info->play_cap &= ~CAPTURE_ENABLED;

	/* Stop the siu अगर the other stream is not using it */
	अगर (!port_info->play_cap) अणु
		/* during sपंचांगपढ़ो or sपंचांगग_लिखो ? */
		अगर (WARN_ON(port_info->playback.rw_flg || port_info->capture.rw_flg))
			वापस;
		siu_dai_spbstop(port_info);
		siu_dai_stop(port_info);
	पूर्ण
पूर्ण

/* PCM part of siu_dai_playback_prepare() / siu_dai_capture_prepare() */
अटल पूर्णांक siu_dai_prepare(काष्ठा snd_pcm_substream *substream,
			   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा siu_info *info = snd_soc_dai_get_drvdata(dai);
	काष्ठा snd_pcm_runसमय *rt = substream->runसमय;
	काष्ठा siu_port *port_info = siu_port_info(substream);
	काष्ठा siu_stream *siu_stream;
	पूर्णांक self, ret;

	dev_dbg(substream->pcm->card->dev,
		"%s: port %d, active streams %lx, %d channels\n",
		__func__, info->port_id, port_info->play_cap, rt->channels);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		self = PLAYBACK_ENABLED;
		siu_stream = &port_info->playback;
	पूर्ण अन्यथा अणु
		self = CAPTURE_ENABLED;
		siu_stream = &port_info->capture;
	पूर्ण

	/* Set up the siu अगर not alपढ़ोy करोne */
	अगर (!port_info->play_cap) अणु
		siu_stream->rw_flg = 0;	/* stream-data transfer flag */

		siu_dai_spbAselect(port_info);
		siu_dai_spbBselect(port_info);

		siu_dai_खोलो(siu_stream);

		siu_dai_pcmdatapack(siu_stream);

		ret = siu_dai_spbstart(port_info);
		अगर (ret < 0)
			जाओ fail;
	पूर्ण अन्यथा अणु
		ret = 0;
	पूर्ण

	port_info->play_cap |= self;

fail:
	वापस ret;
पूर्ण

/*
 * SIU can set bus क्रमmat to I2S / PCM / SPDIF independently क्रम playback and
 * capture, however, the current API sets the bus क्रमmat globally क्रम a DAI.
 */
अटल पूर्णांक siu_dai_set_fmt(काष्ठा snd_soc_dai *dai,
			   अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा siu_info *info = snd_soc_dai_get_drvdata(dai);
	u32 __iomem *base = info->reg;
	u32 अगरctl;

	dev_dbg(dai->dev, "%s: fmt 0x%x on port %d\n",
		__func__, fmt, info->port_id);

	अगर (info->port_id < 0)
		वापस -ENODEV;

	/* Here select between I2S / PCM / SPDIF */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		अगरctl = siu_flags[info->port_id].playback.i2s |
			siu_flags[info->port_id].capture.i2s;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		अगरctl = siu_flags[info->port_id].playback.pcm |
			siu_flags[info->port_id].capture.pcm;
		अवरोध;
	/* SPDIF disabled - see comment at the top */
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगरctl |= ~(siu_flags[info->port_id].playback.mask |
		   siu_flags[info->port_id].capture.mask) &
		siu_पढ़ो32(base + SIU_IFCTL);
	siu_ग_लिखो32(base + SIU_IFCTL, अगरctl);

	वापस 0;
पूर्ण

अटल पूर्णांक siu_dai_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
			      अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा clk *siu_clk, *parent_clk;
	अक्षर *siu_name, *parent_name;
	पूर्णांक ret;

	अगर (dir != SND_SOC_CLOCK_IN)
		वापस -EINVAL;

	dev_dbg(dai->dev, "%s: using clock %d\n", __func__, clk_id);

	चयन (clk_id) अणु
	हाल SIU_CLKA_PLL:
		siu_name = "siua_clk";
		parent_name = "pll_clk";
		अवरोध;
	हाल SIU_CLKA_EXT:
		siu_name = "siua_clk";
		parent_name = "siumcka_clk";
		अवरोध;
	हाल SIU_CLKB_PLL:
		siu_name = "siub_clk";
		parent_name = "pll_clk";
		अवरोध;
	हाल SIU_CLKB_EXT:
		siu_name = "siub_clk";
		parent_name = "siumckb_clk";
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	siu_clk = clk_get(dai->dev, siu_name);
	अगर (IS_ERR(siu_clk)) अणु
		dev_err(dai->dev, "%s: cannot get a SIU clock: %ld\n", __func__,
			PTR_ERR(siu_clk));
		वापस PTR_ERR(siu_clk);
	पूर्ण

	parent_clk = clk_get(dai->dev, parent_name);
	अगर (IS_ERR(parent_clk)) अणु
		ret = PTR_ERR(parent_clk);
		dev_err(dai->dev, "cannot get a SIU clock parent: %d\n", ret);
		जाओ epclkget;
	पूर्ण

	ret = clk_set_parent(siu_clk, parent_clk);
	अगर (ret < 0) अणु
		dev_err(dai->dev, "cannot reparent the SIU clock: %d\n", ret);
		जाओ eclksetp;
	पूर्ण

	ret = clk_set_rate(siu_clk, freq);
	अगर (ret < 0)
		dev_err(dai->dev, "cannot set SIU clock rate: %d\n", ret);

	/* TODO: when clkdev माला_लो reference counting we'll move these to siu_dai_shutकरोwn() */
eclksetp:
	clk_put(parent_clk);
epclkget:
	clk_put(siu_clk);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops siu_dai_ops = अणु
	.startup	= siu_dai_startup,
	.shutकरोwn	= siu_dai_shutकरोwn,
	.prepare	= siu_dai_prepare,
	.set_sysclk	= siu_dai_set_sysclk,
	.set_fmt	= siu_dai_set_fmt,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver siu_i2s_dai = अणु
	.name	= "siu-i2s-dai",
	.playback = अणु
		.channels_min = 2,
		.channels_max = 2,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16,
		.rates = SNDRV_PCM_RATE_8000_48000,
	पूर्ण,
	.capture = अणु
		.channels_min = 2,
		.channels_max = 2,
		.क्रमmats = SNDRV_PCM_FMTBIT_S16,
		.rates = SNDRV_PCM_RATE_8000_48000,
	 पूर्ण,
	.ops = &siu_dai_ops,
पूर्ण;

अटल पूर्णांक siu_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा firmware *fw_entry;
	काष्ठा resource *res, *region;
	काष्ठा siu_info *info;
	पूर्णांक ret;

	info = devm_kदो_स्मृति(&pdev->dev, माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस -ENOMEM;
	siu_i2s_data = info;
	info->dev = &pdev->dev;

	ret = request_firmware(&fw_entry, "siu_spb.bin", &pdev->dev);
	अगर (ret)
		वापस ret;

	/*
	 * Loaded firmware is "const" - पढ़ो only, but we have to modअगरy it in
	 * snd_siu_sh7343_spbAselect() and snd_siu_sh7343_spbBselect()
	 */
	स_नकल(&info->fw, fw_entry->data, fw_entry->size);

	release_firmware(fw_entry);

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	region = devm_request_mem_region(&pdev->dev, res->start,
					 resource_size(res), pdev->name);
	अगर (!region) अणु
		dev_err(&pdev->dev, "SIU region already claimed\n");
		वापस -EBUSY;
	पूर्ण

	info->pram = devm_ioremap(&pdev->dev, res->start, PRAM_SIZE);
	अगर (!info->pram)
		वापस -ENOMEM;
	info->xram = devm_ioremap(&pdev->dev, res->start + XRAM_OFFSET,
				  XRAM_SIZE);
	अगर (!info->xram)
		वापस -ENOMEM;
	info->yram = devm_ioremap(&pdev->dev, res->start + YRAM_OFFSET,
				  YRAM_SIZE);
	अगर (!info->yram)
		वापस -ENOMEM;
	info->reg = devm_ioremap(&pdev->dev, res->start + REG_OFFSET,
			    resource_size(res) - REG_OFFSET);
	अगर (!info->reg)
		वापस -ENOMEM;

	dev_set_drvdata(&pdev->dev, info);

	/* रेजिस्टर using ARRAY version so we can keep dai name */
	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &siu_component,
					      &siu_i2s_dai, 1);
	अगर (ret < 0)
		वापस ret;

	pm_runसमय_enable(&pdev->dev);

	वापस 0;
पूर्ण

अटल पूर्णांक siu_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	pm_runसमय_disable(&pdev->dev);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver siu_driver = अणु
	.driver 	= अणु
		.name	= "siu-pcm-audio",
	पूर्ण,
	.probe		= siu_probe,
	.हटाओ		= siu_हटाओ,
पूर्ण;

module_platक्रमm_driver(siu_driver);

MODULE_AUTHOR("Carlos Munoz <carlos@kenati.com>");
MODULE_DESCRIPTION("ALSA SoC SH7722 SIU driver");
MODULE_LICENSE("GPL");
