<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2009 Simtec Electronics
 */

बाह्य व्योम simtec_audio_init(काष्ठा snd_soc_pcm_runसमय *rtd);

बाह्य पूर्णांक simtec_audio_core_probe(काष्ठा platक्रमm_device *pdev,
				   काष्ठा snd_soc_card *card);

बाह्य पूर्णांक simtec_audio_हटाओ(काष्ठा platक्रमm_device *pdev);

#अगर_घोषित CONFIG_PM
बाह्य स्थिर काष्ठा dev_pm_ops simtec_audio_pmops;
#घोषणा simtec_audio_pm &simtec_audio_pmops
#अन्यथा
#घोषणा simtec_audio_pm शून्य
#पूर्ण_अगर
