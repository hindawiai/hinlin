<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// idma.c - I2S0 पूर्णांकernal DMA driver
//
// Copyright (c) 2011 Samsung Electronics Co., Ltd.
//		http://www.samsung.com

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "i2s.h"
#समावेश "idma.h"
#समावेश "i2s-regs.h"

#घोषणा ST_RUNNING		(1<<0)
#घोषणा ST_OPENED		(1<<1)

अटल स्थिर काष्ठा snd_pcm_hardware idma_hardware = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		    SNDRV_PCM_INFO_BLOCK_TRANSFER |
		    SNDRV_PCM_INFO_MMAP |
		    SNDRV_PCM_INFO_MMAP_VALID |
		    SNDRV_PCM_INFO_PAUSE |
		    SNDRV_PCM_INFO_RESUME,
	.buffer_bytes_max = MAX_IDMA_BUFFER,
	.period_bytes_min = 128,
	.period_bytes_max = MAX_IDMA_PERIOD,
	.periods_min = 1,
	.periods_max = 2,
पूर्ण;

काष्ठा idma_ctrl अणु
	spinlock_t	lock;
	पूर्णांक		state;
	dma_addr_t	start;
	dma_addr_t	pos;
	dma_addr_t	end;
	dma_addr_t	period;
	dma_addr_t	periodsz;
	व्योम		*token;
	व्योम		(*cb)(व्योम *dt, पूर्णांक bytes_xfer);
पूर्ण;

अटल काष्ठा idma_info अणु
	spinlock_t	lock;
	व्योम		 __iomem  *regs;
	dma_addr_t	lp_tx_addr;
पूर्ण idma;

अटल पूर्णांक idma_irq;

अटल व्योम idma_getpos(dma_addr_t *src)
अणु
	*src = idma.lp_tx_addr +
		(पढ़ोl(idma.regs + I2STRNCNT) & 0xffffff) * 4;
पूर्ण

अटल पूर्णांक idma_enqueue(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा idma_ctrl *prtd = substream->runसमय->निजी_data;
	u32 val;

	spin_lock(&prtd->lock);
	prtd->token = (व्योम *) substream;
	spin_unlock(&prtd->lock);

	/* Internal DMA Level0 Interrupt Address */
	val = idma.lp_tx_addr + prtd->periodsz;
	ग_लिखोl(val, idma.regs + I2SLVL0ADDR);

	/* Start address0 of I2S पूर्णांकernal DMA operation. */
	val = idma.lp_tx_addr;
	ग_लिखोl(val, idma.regs + I2SSTR0);

	/*
	 * Transfer block size क्रम I2S पूर्णांकernal DMA.
	 * Should decide transfer size beक्रमe start dma operation
	 */
	val = पढ़ोl(idma.regs + I2SSIZE);
	val &= ~(I2SSIZE_TRNMSK << I2SSIZE_SHIFT);
	val |= (((runसमय->dma_bytes >> 2) &
			I2SSIZE_TRNMSK) << I2SSIZE_SHIFT);
	ग_लिखोl(val, idma.regs + I2SSIZE);

	val = पढ़ोl(idma.regs + I2SAHB);
	val |= AHB_INTENLVL0;
	ग_लिखोl(val, idma.regs + I2SAHB);

	वापस 0;
पूर्ण

अटल व्योम idma_setcallbk(काष्ठा snd_pcm_substream *substream,
				व्योम (*cb)(व्योम *, पूर्णांक))
अणु
	काष्ठा idma_ctrl *prtd = substream->runसमय->निजी_data;

	spin_lock(&prtd->lock);
	prtd->cb = cb;
	spin_unlock(&prtd->lock);
पूर्ण

अटल व्योम idma_control(पूर्णांक op)
अणु
	u32 val = पढ़ोl(idma.regs + I2SAHB);

	spin_lock(&idma.lock);

	चयन (op) अणु
	हाल LPAM_DMA_START:
		val |= (AHB_INTENLVL0 | AHB_DMAEN);
		अवरोध;
	हाल LPAM_DMA_STOP:
		val &= ~(AHB_INTENLVL0 | AHB_DMAEN);
		अवरोध;
	शेष:
		spin_unlock(&idma.lock);
		वापस;
	पूर्ण

	ग_लिखोl(val, idma.regs + I2SAHB);
	spin_unlock(&idma.lock);
पूर्ण

अटल व्योम idma_करोne(व्योम *id, पूर्णांक bytes_xfer)
अणु
	काष्ठा snd_pcm_substream *substream = id;
	काष्ठा idma_ctrl *prtd = substream->runसमय->निजी_data;

	अगर (prtd && (prtd->state & ST_RUNNING))
		snd_pcm_period_elapsed(substream);
पूर्ण

अटल पूर्णांक idma_hw_params(काष्ठा snd_soc_component *component,
			  काष्ठा snd_pcm_substream *substream,
			  काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा idma_ctrl *prtd = substream->runसमय->निजी_data;
	u32 mod = पढ़ोl(idma.regs + I2SMOD);
	u32 ahb = पढ़ोl(idma.regs + I2SAHB);

	ahb |= (AHB_DMARLD | AHB_INTMASK);
	mod |= MOD_TXS_IDMA;
	ग_लिखोl(ahb, idma.regs + I2SAHB);
	ग_लिखोl(mod, idma.regs + I2SMOD);

	snd_pcm_set_runसमय_buffer(substream, &substream->dma_buffer);
	runसमय->dma_bytes = params_buffer_bytes(params);

	prtd->start = prtd->pos = runसमय->dma_addr;
	prtd->period = params_periods(params);
	prtd->periodsz = params_period_bytes(params);
	prtd->end = runसमय->dma_addr + runसमय->dma_bytes;

	idma_setcallbk(substream, idma_करोne);

	वापस 0;
पूर्ण

अटल पूर्णांक idma_hw_मुक्त(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	snd_pcm_set_runसमय_buffer(substream, शून्य);

	वापस 0;
पूर्ण

अटल पूर्णांक idma_prepare(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा idma_ctrl *prtd = substream->runसमय->निजी_data;

	prtd->pos = prtd->start;

	/* flush the DMA channel */
	idma_control(LPAM_DMA_STOP);
	idma_enqueue(substream);

	वापस 0;
पूर्ण

अटल पूर्णांक idma_trigger(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा idma_ctrl *prtd = substream->runसमय->निजी_data;
	पूर्णांक ret = 0;

	spin_lock(&prtd->lock);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		prtd->state |= ST_RUNNING;
		idma_control(LPAM_DMA_START);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		prtd->state &= ~ST_RUNNING;
		idma_control(LPAM_DMA_STOP);
		अवरोध;

	शेष:
		ret = -EINVAL;
		अवरोध;
	पूर्ण

	spin_unlock(&prtd->lock);

	वापस ret;
पूर्ण

अटल snd_pcm_uframes_t
idma_poपूर्णांकer(काष्ठा snd_soc_component *component,
	     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा idma_ctrl *prtd = runसमय->निजी_data;
	dma_addr_t src;
	अचिन्हित दीर्घ res;

	spin_lock(&prtd->lock);

	idma_getpos(&src);
	res = src - prtd->start;

	spin_unlock(&prtd->lock);

	वापस bytes_to_frames(substream->runसमय, res);
पूर्ण

अटल पूर्णांक idma_mmap(काष्ठा snd_soc_component *component,
		     काष्ठा snd_pcm_substream *substream,
	काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित दीर्घ size, offset;
	पूर्णांक ret;

	/* From snd_pcm_lib_mmap_iomem */
	vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
	size = vma->vm_end - vma->vm_start;
	offset = vma->vm_pgoff << PAGE_SHIFT;
	ret = io_remap_pfn_range(vma, vma->vm_start,
			(runसमय->dma_addr + offset) >> PAGE_SHIFT,
			size, vma->vm_page_prot);

	वापस ret;
पूर्ण

अटल irqवापस_t iis_irq(पूर्णांक irqno, व्योम *dev_id)
अणु
	काष्ठा idma_ctrl *prtd = (काष्ठा idma_ctrl *)dev_id;
	u32 iisahb, val, addr;

	iisahb  = पढ़ोl(idma.regs + I2SAHB);

	val = (iisahb & AHB_LVL0INT) ? AHB_CLRLVL0INT : 0;

	अगर (val) अणु
		iisahb |= val;
		ग_लिखोl(iisahb, idma.regs + I2SAHB);

		addr = पढ़ोl(idma.regs + I2SLVL0ADDR) - idma.lp_tx_addr;
		addr += prtd->periodsz;
		addr %= (u32)(prtd->end - prtd->start);
		addr += idma.lp_tx_addr;

		ग_लिखोl(addr, idma.regs + I2SLVL0ADDR);

		अगर (prtd->cb)
			prtd->cb(prtd->token, prtd->period);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक idma_खोलो(काष्ठा snd_soc_component *component,
		     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा idma_ctrl *prtd;
	पूर्णांक ret;

	snd_soc_set_runसमय_hwparams(substream, &idma_hardware);

	prtd = kzalloc(माप(काष्ठा idma_ctrl), GFP_KERNEL);
	अगर (prtd == शून्य)
		वापस -ENOMEM;

	ret = request_irq(idma_irq, iis_irq, 0, "i2s", prtd);
	अगर (ret < 0) अणु
		pr_err("fail to claim i2s irq , ret = %d\n", ret);
		kमुक्त(prtd);
		वापस ret;
	पूर्ण

	spin_lock_init(&prtd->lock);

	runसमय->निजी_data = prtd;

	वापस 0;
पूर्ण

अटल पूर्णांक idma_बंद(काष्ठा snd_soc_component *component,
		      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा idma_ctrl *prtd = runसमय->निजी_data;

	मुक्त_irq(idma_irq, prtd);

	अगर (!prtd)
		pr_err("idma_close called with prtd == NULL\n");

	kमुक्त(prtd);

	वापस 0;
पूर्ण

अटल व्योम idma_मुक्त(काष्ठा snd_soc_component *component,
		      काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_dma_buffer *buf;

	substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream;
	अगर (!substream)
		वापस;

	buf = &substream->dma_buffer;
	अगर (!buf->area)
		वापस;

	iounmap((व्योम __iomem *)buf->area);

	buf->area = शून्य;
	buf->addr = 0;
पूर्ण

अटल पूर्णांक pपुनः_स्मृतिate_idma_buffer(काष्ठा snd_pcm *pcm, पूर्णांक stream)
अणु
	काष्ठा snd_pcm_substream *substream = pcm->streams[stream].substream;
	काष्ठा snd_dma_buffer *buf = &substream->dma_buffer;

	buf->dev.dev = pcm->card->dev;
	buf->निजी_data = शून्य;

	/* Assign PCM buffer poपूर्णांकers */
	buf->dev.type = SNDRV_DMA_TYPE_CONTINUOUS;
	buf->addr = idma.lp_tx_addr;
	buf->bytes = idma_hardware.buffer_bytes_max;
	buf->area = (अचिन्हित अक्षर * __क्रमce)ioremap(buf->addr, buf->bytes);

	वापस 0;
पूर्ण

अटल पूर्णांक idma_new(काष्ठा snd_soc_component *component,
		    काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_card *card = rtd->card->snd_card;
	काष्ठा snd_pcm *pcm = rtd->pcm;
	पूर्णांक ret;

	ret = dma_coerce_mask_and_coherent(card->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	अगर (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream) अणु
		ret = pपुनः_स्मृतिate_idma_buffer(pcm,
				SNDRV_PCM_STREAM_PLAYBACK);
	पूर्ण

	वापस ret;
पूर्ण

व्योम idma_reg_addr_init(व्योम __iomem *regs, dma_addr_t addr)
अणु
	spin_lock_init(&idma.lock);
	idma.regs = regs;
	idma.lp_tx_addr = addr;
पूर्ण
EXPORT_SYMBOL_GPL(idma_reg_addr_init);

अटल स्थिर काष्ठा snd_soc_component_driver asoc_idma_platक्रमm = अणु
	.खोलो		= idma_खोलो,
	.बंद		= idma_बंद,
	.trigger	= idma_trigger,
	.poपूर्णांकer	= idma_poपूर्णांकer,
	.mmap		= idma_mmap,
	.hw_params	= idma_hw_params,
	.hw_मुक्त	= idma_hw_मुक्त,
	.prepare	= idma_prepare,
	.pcm_स्थिरruct	= idma_new,
	.pcm_deकाष्ठा	= idma_मुक्त,
पूर्ण;

अटल पूर्णांक asoc_idma_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	idma_irq = platक्रमm_get_irq(pdev, 0);
	अगर (idma_irq < 0)
		वापस idma_irq;

	वापस devm_snd_soc_रेजिस्टर_component(&pdev->dev, &asoc_idma_platक्रमm,
					       शून्य, 0);
पूर्ण

अटल काष्ठा platक्रमm_driver asoc_idma_driver = अणु
	.driver = अणु
		.name = "samsung-idma",
	पूर्ण,

	.probe = asoc_idma_platक्रमm_probe,
पूर्ण;

module_platक्रमm_driver(asoc_idma_driver);

MODULE_AUTHOR("Jaswinder Singh, <jassisinghbrar@gmail.com>");
MODULE_DESCRIPTION("Samsung ASoC IDMA Driver");
MODULE_LICENSE("GPL");
