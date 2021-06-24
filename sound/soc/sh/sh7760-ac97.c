<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Generic AC97 sound support क्रम SH7760
//
// (c) 2007 Manuel Lauss

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <यंत्र/पन.स>

#घोषणा IPSEL 0xFE400034

SND_SOC_DAILINK_DEFS(ac97,
	DAILINK_COMP_ARRAY(COMP_CPU("hac-dai.0")),	/* HAC0 */
	DAILINK_COMP_ARRAY(COMP_CODEC("ac97-codec", "ac97-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("sh7760-pcm-audio")));

अटल काष्ठा snd_soc_dai_link sh7760_ac97_dai = अणु
	.name = "AC97",
	.stream_name = "AC97 HiFi",
	SND_SOC_DAILINK_REG(ac97),
पूर्ण;

अटल काष्ठा snd_soc_card sh7760_ac97_soc_machine  = अणु
	.name = "SH7760 AC97",
	.owner = THIS_MODULE,
	.dai_link = &sh7760_ac97_dai,
	.num_links = 1,
पूर्ण;

अटल काष्ठा platक्रमm_device *sh7760_ac97_snd_device;

अटल पूर्णांक __init sh7760_ac97_init(व्योम)
अणु
	पूर्णांक ret;
	अचिन्हित लघु ipsel;

	/* enable both AC97 controllers in pinmux reg */
	ipsel = __raw_पढ़ोw(IPSEL);
	__raw_ग_लिखोw(ipsel | (3 << 10), IPSEL);

	ret = -ENOMEM;
	sh7760_ac97_snd_device = platक्रमm_device_alloc("soc-audio", -1);
	अगर (!sh7760_ac97_snd_device)
		जाओ out;

	platक्रमm_set_drvdata(sh7760_ac97_snd_device,
			     &sh7760_ac97_soc_machine);
	ret = platक्रमm_device_add(sh7760_ac97_snd_device);

	अगर (ret)
		platक्रमm_device_put(sh7760_ac97_snd_device);

out:
	वापस ret;
पूर्ण

अटल व्योम __निकास sh7760_ac97_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(sh7760_ac97_snd_device);
पूर्ण

module_init(sh7760_ac97_init);
module_निकास(sh7760_ac97_निकास);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("Generic SH7760 AC97 sound machine");
MODULE_AUTHOR("Manuel Lauss <mano@roarinelk.homelinux.net>");
