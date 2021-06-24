<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Hitachi Audio Controller (AC97) support क्रम SH7760/SH7780
//
// Copyright (c) 2007 Manuel Lauss <mano@roarinelk.homelinux.net>
//
// करोnt क्रमget to set IPSEL/OMSEL रेजिस्टर bits (in your board code) to
// enable HAC output pins!

/* BIG FAT FIXME: although the SH7760 has 2 independent AC97 units, only
 * the FIRST can be used since ASoC करोes not pass any inक्रमmation to the
 * ac97_पढ़ो/ग_लिखो() functions regarding WHICH unit to use.  You'll have
 * to edit the code a bit to use the other AC97 unit.		--mlau
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/रुको.h>
#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/ac97_codec.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>

/* regs and bits */
#घोषणा HACCR		0x08
#घोषणा HACCSAR		0x20
#घोषणा HACCSDR		0x24
#घोषणा HACPCML		0x28
#घोषणा HACPCMR		0x2C
#घोषणा HACTIER		0x50
#घोषणा	HACTSR		0x54
#घोषणा HACRIER		0x58
#घोषणा HACRSR		0x5C
#घोषणा HACACR		0x60

#घोषणा CR_CR		(1 << 15)	/* "codec-ready" indicator */
#घोषणा CR_CDRT		(1 << 11)	/* cold reset */
#घोषणा CR_WMRT		(1 << 10)	/* warm reset */
#घोषणा CR_B9		(1 << 9)	/* the mysterious "bit 9" */
#घोषणा CR_ST		(1 << 5)	/* AC97 link start bit */

#घोषणा CSAR_RD		(1 << 19)	/* AC97 data पढ़ो bit */
#घोषणा CSAR_WR		(0)

#घोषणा TSR_CMDAMT	(1 << 31)
#घोषणा TSR_CMDDMT	(1 << 30)

#घोषणा RSR_STARY	(1 << 22)
#घोषणा RSR_STDRY	(1 << 21)

#घोषणा ACR_DMARX16	(1 << 30)
#घोषणा ACR_DMATX16	(1 << 29)
#घोषणा ACR_TX12ATOM	(1 << 26)
#घोषणा ACR_DMARX20	((1 << 24) | (1 << 22))
#घोषणा ACR_DMATX20	((1 << 23) | (1 << 21))

#घोषणा CSDR_SHIFT	4
#घोषणा CSDR_MASK	(0xffff << CSDR_SHIFT)
#घोषणा CSAR_SHIFT	12
#घोषणा CSAR_MASK	(0x7f << CSAR_SHIFT)

#घोषणा AC97_WRITE_RETRY	1
#घोषणा AC97_READ_RETRY		5

/* manual-suggested AC97 codec access समयouts (us) */
#घोषणा TMO_E1	500	/* 21 < E1 < 1000 */
#घोषणा TMO_E2	13	/* 13 < E2 */
#घोषणा TMO_E3	21	/* 21 < E3 */
#घोषणा TMO_E4	500	/* 21 < E4 < 1000 */

काष्ठा hac_priv अणु
	अचिन्हित दीर्घ mmio;	/* HAC base address */
पूर्ण hac_cpu_data[] = अणु
#अगर defined(CONFIG_CPU_SUBTYPE_SH7760)
	अणु
		.mmio	= 0xFE240000,
	पूर्ण,
	अणु
		.mmio	= 0xFE250000,
	पूर्ण,
#या_अगर defined(CONFIG_CPU_SUBTYPE_SH7780)
	अणु
		.mmio	= 0xFFE40000,
	पूर्ण,
#अन्यथा
#त्रुटि "Unsupported SuperH SoC"
#पूर्ण_अगर
पूर्ण;

#घोषणा HACREG(reg)	(*(अचिन्हित दीर्घ *)(hac->mmio + (reg)))

/*
 * AC97 पढ़ो/ग_लिखो flow as outlined in the SH7760 manual (pages 903-906)
 */
अटल पूर्णांक hac_get_codec_data(काष्ठा hac_priv *hac, अचिन्हित लघु r,
			      अचिन्हित लघु *v)
अणु
	अचिन्हित पूर्णांक to1, to2, i;
	अचिन्हित लघु adr;

	क्रम (i = AC97_READ_RETRY; i; i--) अणु
		*v = 0;
		/* रुको क्रम HAC to receive something from the codec */
		क्रम (to1 = TMO_E4;
		     to1 && !(HACREG(HACRSR) & RSR_STARY);
		     --to1)
			udelay(1);
		क्रम (to2 = TMO_E4; 
		     to2 && !(HACREG(HACRSR) & RSR_STDRY);
		     --to2)
			udelay(1);

		अगर (!to1 && !to2)
			वापस 0;	/* codec comm is करोwn */

		adr = ((HACREG(HACCSAR) & CSAR_MASK) >> CSAR_SHIFT);
		*v  = ((HACREG(HACCSDR) & CSDR_MASK) >> CSDR_SHIFT);

		HACREG(HACRSR) &= ~(RSR_STDRY | RSR_STARY);

		अगर (r == adr)
			अवरोध;

		/* manual says: रुको at least 21 usec beक्रमe retrying */
		udelay(21);
	पूर्ण
	HACREG(HACRSR) &= ~(RSR_STDRY | RSR_STARY);
	वापस i;
पूर्ण

अटल अचिन्हित लघु hac_पढ़ो_codec_aux(काष्ठा hac_priv *hac,
					 अचिन्हित लघु reg)
अणु
	अचिन्हित लघु val;
	अचिन्हित पूर्णांक i, to;

	क्रम (i = AC97_READ_RETRY; i; i--) अणु
		/* send_पढ़ो_request */
		local_irq_disable();
		HACREG(HACTSR) &= ~(TSR_CMDAMT);
		HACREG(HACCSAR) = (reg << CSAR_SHIFT) | CSAR_RD;
		local_irq_enable();

		क्रम (to = TMO_E3;
		     to && !(HACREG(HACTSR) & TSR_CMDAMT);
		     --to)
			udelay(1);

		HACREG(HACTSR) &= ~TSR_CMDAMT;
		val = 0;
		अगर (hac_get_codec_data(hac, reg, &val) != 0)
			अवरोध;
	पूर्ण

	वापस i ? val : ~0;
पूर्ण

अटल व्योम hac_ac97_ग_लिखो(काष्ठा snd_ac97 *ac97, अचिन्हित लघु reg,
			   अचिन्हित लघु val)
अणु
	पूर्णांक unit_id = 0 /* ac97->निजी_data */;
	काष्ठा hac_priv *hac = &hac_cpu_data[unit_id];
	अचिन्हित पूर्णांक i, to;
	/* ग_लिखो_codec_aux */
	क्रम (i = AC97_WRITE_RETRY; i; i--) अणु
		/* send_ग_लिखो_request */
		local_irq_disable();
		HACREG(HACTSR) &= ~(TSR_CMDDMT | TSR_CMDAMT);
		HACREG(HACCSDR) = (val << CSDR_SHIFT);
		HACREG(HACCSAR) = (reg << CSAR_SHIFT) & (~CSAR_RD);
		local_irq_enable();

		/* poll-रुको क्रम CMDAMT and CMDDMT */
		क्रम (to = TMO_E1;
		     to && !(HACREG(HACTSR) & (TSR_CMDAMT|TSR_CMDDMT));
		     --to)
			udelay(1);

		HACREG(HACTSR) &= ~(TSR_CMDAMT | TSR_CMDDMT);
		अगर (to)
			अवरोध;
		/* समयout, try again */
	पूर्ण
पूर्ण

अटल अचिन्हित लघु hac_ac97_पढ़ो(काष्ठा snd_ac97 *ac97,
				    अचिन्हित लघु reg)
अणु
	पूर्णांक unit_id = 0 /* ac97->निजी_data */;
	काष्ठा hac_priv *hac = &hac_cpu_data[unit_id];
	वापस hac_पढ़ो_codec_aux(hac, reg);
पूर्ण

अटल व्योम hac_ac97_warmrst(काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक unit_id = 0 /* ac97->निजी_data */;
	काष्ठा hac_priv *hac = &hac_cpu_data[unit_id];
	अचिन्हित पूर्णांक पंचांगo;

	HACREG(HACCR) = CR_WMRT | CR_ST | CR_B9;
	msleep(10);
	HACREG(HACCR) = CR_ST | CR_B9;
	क्रम (पंचांगo = 1000; (पंचांगo > 0) && !(HACREG(HACCR) & CR_CR); पंचांगo--)
		udelay(1);

	अगर (!पंचांगo)
		prपूर्णांकk(KERN_INFO "hac: reset: AC97 link down!\n");
	/* settings this bit lets us have a conversation with codec */
	HACREG(HACACR) |= ACR_TX12ATOM;
पूर्ण

अटल व्योम hac_ac97_coldrst(काष्ठा snd_ac97 *ac97)
अणु
	पूर्णांक unit_id = 0 /* ac97->निजी_data */;
	काष्ठा hac_priv *hac;
	hac = &hac_cpu_data[unit_id];

	HACREG(HACCR) = 0;
	HACREG(HACCR) = CR_CDRT | CR_ST | CR_B9;
	msleep(10);
	hac_ac97_warmrst(ac97);
पूर्ण

अटल काष्ठा snd_ac97_bus_ops hac_ac97_ops = अणु
	.पढ़ो	= hac_ac97_पढ़ो,
	.ग_लिखो	= hac_ac97_ग_लिखो,
	.reset	= hac_ac97_coldrst,
	.warm_reset = hac_ac97_warmrst,
पूर्ण;

अटल पूर्णांक hac_hw_params(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *params,
			 काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा hac_priv *hac = &hac_cpu_data[dai->id];
	पूर्णांक d = substream->stream == SNDRV_PCM_STREAM_PLAYBACK ? 0 : 1;

	चयन (params->msbits) अणु
	हाल 16:
		HACREG(HACACR) |= d ?  ACR_DMARX16 :  ACR_DMATX16;
		HACREG(HACACR) &= d ? ~ACR_DMARX20 : ~ACR_DMATX20;
		अवरोध;
	हाल 20:
		HACREG(HACACR) &= d ? ~ACR_DMARX16 : ~ACR_DMATX16;
		HACREG(HACACR) |= d ?  ACR_DMARX20 :  ACR_DMATX20;
		अवरोध;
	शेष:
		pr_debug("hac: invalid depth %d bit\n", params->msbits);
		वापस -EINVAL;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

#घोषणा AC97_RATES	\
	SNDRV_PCM_RATE_8000_192000

#घोषणा AC97_FMTS	\
	SNDRV_PCM_FMTBIT_S16_LE

अटल स्थिर काष्ठा snd_soc_dai_ops hac_dai_ops = अणु
	.hw_params	= hac_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver sh4_hac_dai[] = अणु
अणु
	.name			= "hac-dai.0",
	.playback = अणु
		.rates		= AC97_RATES,
		.क्रमmats	= AC97_FMTS,
		.channels_min	= 2,
		.channels_max	= 2,
	पूर्ण,
	.capture = अणु
		.rates		= AC97_RATES,
		.क्रमmats	= AC97_FMTS,
		.channels_min	= 2,
		.channels_max	= 2,
	पूर्ण,
	.ops = &hac_dai_ops,
पूर्ण,
#अगर_घोषित CONFIG_CPU_SUBTYPE_SH7760
अणु
	.name			= "hac-dai.1",
	.id			= 1,
	.playback = अणु
		.rates		= AC97_RATES,
		.क्रमmats	= AC97_FMTS,
		.channels_min	= 2,
		.channels_max	= 2,
	पूर्ण,
	.capture = अणु
		.rates		= AC97_RATES,
		.क्रमmats	= AC97_FMTS,
		.channels_min	= 2,
		.channels_max	= 2,
	पूर्ण,
	.ops = &hac_dai_ops,

पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver sh4_hac_component = अणु
	.name		= "sh4-hac",
पूर्ण;

अटल पूर्णांक hac_soc_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = snd_soc_set_ac97_ops(&hac_ac97_ops);
	अगर (ret != 0)
		वापस ret;

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev, &sh4_hac_component,
					  sh4_hac_dai, ARRAY_SIZE(sh4_hac_dai));
पूर्ण

अटल पूर्णांक hac_soc_platक्रमm_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	snd_soc_set_ac97_ops(शून्य);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver hac_pcm_driver = अणु
	.driver = अणु
			.name = "hac-pcm-audio",
	पूर्ण,

	.probe = hac_soc_platक्रमm_probe,
	.हटाओ = hac_soc_platक्रमm_हटाओ,
पूर्ण;

module_platक्रमm_driver(hac_pcm_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("SuperH onchip HAC (AC97) audio driver");
MODULE_AUTHOR("Manuel Lauss <mano@roarinelk.homelinux.net>");
