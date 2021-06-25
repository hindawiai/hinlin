<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित PXA2XX_LIB_H
#घोषणा PXA2XX_LIB_H

#समावेश <uapi/sound/asound.h>
#समावेश <linux/platक्रमm_device.h>

/* PCM */
काष्ठा snd_pcm_substream;
काष्ठा snd_pcm_hw_params;
काष्ठा snd_soc_pcm_runसमय;
काष्ठा snd_pcm;
काष्ठा snd_soc_component;

बाह्य पूर्णांक pxa2xx_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params);
बाह्य पूर्णांक pxa2xx_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream);
बाह्य पूर्णांक pxa2xx_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd);
बाह्य snd_pcm_uframes_t pxa2xx_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream);
बाह्य पूर्णांक pxa2xx_pcm_prepare(काष्ठा snd_pcm_substream *substream);
बाह्य पूर्णांक pxa2xx_pcm_खोलो(काष्ठा snd_pcm_substream *substream);
बाह्य पूर्णांक pxa2xx_pcm_बंद(काष्ठा snd_pcm_substream *substream);
बाह्य पूर्णांक pxa2xx_pcm_mmap(काष्ठा snd_pcm_substream *substream,
	काष्ठा vm_area_काष्ठा *vma);
बाह्य पूर्णांक pxa2xx_pcm_pपुनः_स्मृतिate_dma_buffer(काष्ठा snd_pcm *pcm, पूर्णांक stream);
बाह्य व्योम pxa2xx_pcm_मुक्त_dma_buffers(काष्ठा snd_pcm *pcm);
बाह्य व्योम pxa2xx_soc_pcm_मुक्त(काष्ठा snd_soc_component *component,
				काष्ठा snd_pcm *pcm);
बाह्य पूर्णांक pxa2xx_soc_pcm_new(काष्ठा snd_soc_component *component,
			      काष्ठा snd_soc_pcm_runसमय *rtd);
बाह्य पूर्णांक pxa2xx_soc_pcm_खोलो(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream);
बाह्य पूर्णांक pxa2xx_soc_pcm_बंद(काष्ठा snd_soc_component *component,
				काष्ठा snd_pcm_substream *substream);
बाह्य पूर्णांक pxa2xx_soc_pcm_hw_params(काष्ठा snd_soc_component *component,
				    काष्ठा snd_pcm_substream *substream,
				    काष्ठा snd_pcm_hw_params *params);
बाह्य पूर्णांक pxa2xx_soc_pcm_hw_मुक्त(काष्ठा snd_soc_component *component,
				  काष्ठा snd_pcm_substream *substream);
बाह्य पूर्णांक pxa2xx_soc_pcm_prepare(काष्ठा snd_soc_component *component,
				  काष्ठा snd_pcm_substream *substream);
बाह्य पूर्णांक pxa2xx_soc_pcm_trigger(काष्ठा snd_soc_component *component,
				  काष्ठा snd_pcm_substream *substream, पूर्णांक cmd);
बाह्य snd_pcm_uframes_t
pxa2xx_soc_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
		       काष्ठा snd_pcm_substream *substream);
बाह्य पूर्णांक pxa2xx_soc_pcm_mmap(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream,
			       काष्ठा vm_area_काष्ठा *vma);

/* AC97 */

बाह्य पूर्णांक pxa2xx_ac97_पढ़ो(पूर्णांक slot, अचिन्हित लघु reg);
बाह्य पूर्णांक pxa2xx_ac97_ग_लिखो(पूर्णांक slot, अचिन्हित लघु reg, अचिन्हित लघु val);

बाह्य bool pxa2xx_ac97_try_warm_reset(व्योम);
बाह्य bool pxa2xx_ac97_try_cold_reset(व्योम);
बाह्य व्योम pxa2xx_ac97_finish_reset(व्योम);

बाह्य पूर्णांक pxa2xx_ac97_hw_suspend(व्योम);
बाह्य पूर्णांक pxa2xx_ac97_hw_resume(व्योम);

बाह्य पूर्णांक pxa2xx_ac97_hw_probe(काष्ठा platक्रमm_device *dev);
बाह्य व्योम pxa2xx_ac97_hw_हटाओ(काष्ठा platक्रमm_device *dev);

#पूर्ण_अगर
