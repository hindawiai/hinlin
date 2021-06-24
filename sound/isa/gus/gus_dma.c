<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Routines क्रम GF1 DMA control
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <यंत्र/dma.h>
#समावेश <linux/slab.h>
#समावेश <sound/core.h>
#समावेश <sound/gus.h>

अटल व्योम snd_gf1_dma_ack(काष्ठा snd_gus_card * gus)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&gus->reg_lock, flags);
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_DRAM_DMA_CONTROL, 0x00);
	snd_gf1_look8(gus, SNDRV_GF1_GB_DRAM_DMA_CONTROL);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
पूर्ण

अटल व्योम snd_gf1_dma_program(काष्ठा snd_gus_card * gus,
				अचिन्हित पूर्णांक addr,
				अचिन्हित दीर्घ buf_addr,
				अचिन्हित पूर्णांक count,
				अचिन्हित पूर्णांक cmd)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक address;
	अचिन्हित अक्षर dma_cmd;
	अचिन्हित पूर्णांक address_high;

	snd_prपूर्णांकdd("dma_transfer: addr=0x%x, buf=0x%lx, count=0x%x\n",
		    addr, buf_addr, count);

	अगर (gus->gf1.dma1 > 3) अणु
		अगर (gus->gf1.enh_mode) अणु
			address = addr >> 1;
		पूर्ण अन्यथा अणु
			अगर (addr & 0x1f) अणु
				snd_prपूर्णांकd("snd_gf1_dma_transfer: unaligned address (0x%x)?\n", addr);
				वापस;
			पूर्ण
			address = (addr & 0x000c0000) | ((addr & 0x0003ffff) >> 1);
		पूर्ण
	पूर्ण अन्यथा अणु
		address = addr;
	पूर्ण

	dma_cmd = SNDRV_GF1_DMA_ENABLE | (अचिन्हित लघु) cmd;
#अगर 0
	dma_cmd |= 0x08;
#पूर्ण_अगर
	अगर (dma_cmd & SNDRV_GF1_DMA_16BIT) अणु
		count++;
		count &= ~1;	/* align */
	पूर्ण
	अगर (gus->gf1.dma1 > 3) अणु
		dma_cmd |= SNDRV_GF1_DMA_WIDTH16;
		count++;
		count &= ~1;	/* align */
	पूर्ण
	snd_gf1_dma_ack(gus);
	snd_dma_program(gus->gf1.dma1, buf_addr, count, dma_cmd & SNDRV_GF1_DMA_READ ? DMA_MODE_READ : DMA_MODE_WRITE);
#अगर 0
	snd_prपूर्णांकk(KERN_DEBUG "address = 0x%x, count = 0x%x, dma_cmd = 0x%x\n",
		   address << 1, count, dma_cmd);
#पूर्ण_अगर
	spin_lock_irqsave(&gus->reg_lock, flags);
	अगर (gus->gf1.enh_mode) अणु
		address_high = ((address >> 16) & 0x000000f0) | (address & 0x0000000f);
		snd_gf1_ग_लिखो16(gus, SNDRV_GF1_GW_DRAM_DMA_LOW, (अचिन्हित लघु) (address >> 4));
		snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_DRAM_DMA_HIGH, (अचिन्हित अक्षर) address_high);
	पूर्ण अन्यथा
		snd_gf1_ग_लिखो16(gus, SNDRV_GF1_GW_DRAM_DMA_LOW, (अचिन्हित लघु) (address >> 4));
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_DRAM_DMA_CONTROL, dma_cmd);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
पूर्ण

अटल काष्ठा snd_gf1_dma_block *snd_gf1_dma_next_block(काष्ठा snd_gus_card * gus)
अणु
	काष्ठा snd_gf1_dma_block *block;

	/* PCM block have bigger priority than synthesizer one */
	अगर (gus->gf1.dma_data_pcm) अणु
		block = gus->gf1.dma_data_pcm;
		अगर (gus->gf1.dma_data_pcm_last == block) अणु
			gus->gf1.dma_data_pcm =
			gus->gf1.dma_data_pcm_last = शून्य;
		पूर्ण अन्यथा अणु
			gus->gf1.dma_data_pcm = block->next;
		पूर्ण
	पूर्ण अन्यथा अगर (gus->gf1.dma_data_synth) अणु
		block = gus->gf1.dma_data_synth;
		अगर (gus->gf1.dma_data_synth_last == block) अणु
			gus->gf1.dma_data_synth =
			gus->gf1.dma_data_synth_last = शून्य;
		पूर्ण अन्यथा अणु
			gus->gf1.dma_data_synth = block->next;
		पूर्ण
	पूर्ण अन्यथा अणु
		block = शून्य;
	पूर्ण
	अगर (block) अणु
		gus->gf1.dma_ack = block->ack;
		gus->gf1.dma_निजी_data = block->निजी_data;
	पूर्ण
	वापस block;
पूर्ण


अटल व्योम snd_gf1_dma_पूर्णांकerrupt(काष्ठा snd_gus_card * gus)
अणु
	काष्ठा snd_gf1_dma_block *block;

	snd_gf1_dma_ack(gus);
	अगर (gus->gf1.dma_ack)
		gus->gf1.dma_ack(gus, gus->gf1.dma_निजी_data);
	spin_lock(&gus->dma_lock);
	अगर (gus->gf1.dma_data_pcm == शून्य &&
	    gus->gf1.dma_data_synth == शून्य) अणु
	    	gus->gf1.dma_ack = शून्य;
		gus->gf1.dma_flags &= ~SNDRV_GF1_DMA_TRIGGER;
		spin_unlock(&gus->dma_lock);
		वापस;
	पूर्ण
	block = snd_gf1_dma_next_block(gus);
	spin_unlock(&gus->dma_lock);
	snd_gf1_dma_program(gus, block->addr, block->buf_addr, block->count, (अचिन्हित लघु) block->cmd);
	kमुक्त(block);
#अगर 0
	snd_prपूर्णांकd(KERN_DEBUG "program dma (IRQ) - "
		   "addr = 0x%x, buffer = 0x%lx, count = 0x%x, cmd = 0x%x\n",
		   block->addr, block->buf_addr, block->count, block->cmd);
#पूर्ण_अगर
पूर्ण

पूर्णांक snd_gf1_dma_init(काष्ठा snd_gus_card * gus)
अणु
	mutex_lock(&gus->dma_mutex);
	gus->gf1.dma_shared++;
	अगर (gus->gf1.dma_shared > 1) अणु
		mutex_unlock(&gus->dma_mutex);
		वापस 0;
	पूर्ण
	gus->gf1.पूर्णांकerrupt_handler_dma_ग_लिखो = snd_gf1_dma_पूर्णांकerrupt;
	gus->gf1.dma_data_pcm = 
	gus->gf1.dma_data_pcm_last =
	gus->gf1.dma_data_synth = 
	gus->gf1.dma_data_synth_last = शून्य;
	mutex_unlock(&gus->dma_mutex);
	वापस 0;
पूर्ण

पूर्णांक snd_gf1_dma_करोne(काष्ठा snd_gus_card * gus)
अणु
	काष्ठा snd_gf1_dma_block *block;

	mutex_lock(&gus->dma_mutex);
	gus->gf1.dma_shared--;
	अगर (!gus->gf1.dma_shared) अणु
		snd_dma_disable(gus->gf1.dma1);
		snd_gf1_set_शेष_handlers(gus, SNDRV_GF1_HANDLER_DMA_WRITE);
		snd_gf1_dma_ack(gus);
		जबतक ((block = gus->gf1.dma_data_pcm)) अणु
			gus->gf1.dma_data_pcm = block->next;
			kमुक्त(block);
		पूर्ण
		जबतक ((block = gus->gf1.dma_data_synth)) अणु
			gus->gf1.dma_data_synth = block->next;
			kमुक्त(block);
		पूर्ण
		gus->gf1.dma_data_pcm_last =
		gus->gf1.dma_data_synth_last = शून्य;
	पूर्ण
	mutex_unlock(&gus->dma_mutex);
	वापस 0;
पूर्ण

पूर्णांक snd_gf1_dma_transfer_block(काष्ठा snd_gus_card * gus,
			       काष्ठा snd_gf1_dma_block * __block,
			       पूर्णांक atomic,
			       पूर्णांक synth)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_gf1_dma_block *block;

	block = kदो_स्मृति(माप(*block), atomic ? GFP_ATOMIC : GFP_KERNEL);
	अगर (!block)
		वापस -ENOMEM;

	*block = *__block;
	block->next = शून्य;

	snd_prपूर्णांकdd("addr = 0x%x, buffer = 0x%lx, count = 0x%x, cmd = 0x%x\n",
		    block->addr, (दीर्घ) block->buffer, block->count,
		    block->cmd);

	snd_prपूर्णांकdd("gus->gf1.dma_data_pcm_last = 0x%lx\n",
		    (दीर्घ)gus->gf1.dma_data_pcm_last);
	snd_prपूर्णांकdd("gus->gf1.dma_data_pcm = 0x%lx\n",
		    (दीर्घ)gus->gf1.dma_data_pcm);

	spin_lock_irqsave(&gus->dma_lock, flags);
	अगर (synth) अणु
		अगर (gus->gf1.dma_data_synth_last) अणु
			gus->gf1.dma_data_synth_last->next = block;
			gus->gf1.dma_data_synth_last = block;
		पूर्ण अन्यथा अणु
			gus->gf1.dma_data_synth = 
			gus->gf1.dma_data_synth_last = block;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (gus->gf1.dma_data_pcm_last) अणु
			gus->gf1.dma_data_pcm_last->next = block;
			gus->gf1.dma_data_pcm_last = block;
		पूर्ण अन्यथा अणु
			gus->gf1.dma_data_pcm = 
			gus->gf1.dma_data_pcm_last = block;
		पूर्ण
	पूर्ण
	अगर (!(gus->gf1.dma_flags & SNDRV_GF1_DMA_TRIGGER)) अणु
		gus->gf1.dma_flags |= SNDRV_GF1_DMA_TRIGGER;
		block = snd_gf1_dma_next_block(gus);
		spin_unlock_irqrestore(&gus->dma_lock, flags);
		अगर (block == शून्य)
			वापस 0;
		snd_gf1_dma_program(gus, block->addr, block->buf_addr, block->count, (अचिन्हित लघु) block->cmd);
		kमुक्त(block);
		वापस 0;
	पूर्ण
	spin_unlock_irqrestore(&gus->dma_lock, flags);
	वापस 0;
पूर्ण
