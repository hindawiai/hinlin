<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Routines क्रम Gravis UltraSound soundcards
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/gus.h>
#समावेश <sound/control.h>

#समावेश <यंत्र/dma.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("Routines for Gravis UltraSound soundcards");
MODULE_LICENSE("GPL");

अटल पूर्णांक snd_gus_init_dma_irq(काष्ठा snd_gus_card * gus, पूर्णांक latches);

पूर्णांक snd_gus_use_inc(काष्ठा snd_gus_card * gus)
अणु
	अगर (!try_module_get(gus->card->module))
		वापस 0;
	वापस 1;
पूर्ण

व्योम snd_gus_use_dec(काष्ठा snd_gus_card * gus)
अणु
	module_put(gus->card->module);
पूर्ण

अटल पूर्णांक snd_gus_joystick_info(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_info *uinfo)
अणु
	uinfo->type = SNDRV_CTL_ELEM_TYPE_INTEGER;
	uinfo->count = 1;
	uinfo->value.पूर्णांकeger.min = 0;
	uinfo->value.पूर्णांकeger.max = 31;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gus_joystick_get(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_gus_card *gus = snd_kcontrol_chip(kcontrol);
	
	ucontrol->value.पूर्णांकeger.value[0] = gus->joystick_dac & 31;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gus_joystick_put(काष्ठा snd_kcontrol *kcontrol, काष्ठा snd_ctl_elem_value *ucontrol)
अणु
	काष्ठा snd_gus_card *gus = snd_kcontrol_chip(kcontrol);
	अचिन्हित दीर्घ flags;
	पूर्णांक change;
	अचिन्हित अक्षर nval;
	
	nval = ucontrol->value.पूर्णांकeger.value[0] & 31;
	spin_lock_irqsave(&gus->reg_lock, flags);
	change = gus->joystick_dac != nval;
	gus->joystick_dac = nval;
	snd_gf1_ग_लिखो8(gus, SNDRV_GF1_GB_JOYSTICK_DAC_LEVEL, gus->joystick_dac);
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	वापस change;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new snd_gus_joystick_control = अणु
	.अगरace = SNDRV_CTL_ELEM_IFACE_CARD,
	.name = "Joystick Speed",
	.info = snd_gus_joystick_info,
	.get = snd_gus_joystick_get,
	.put = snd_gus_joystick_put
पूर्ण;

अटल व्योम snd_gus_init_control(काष्ठा snd_gus_card *gus)
अणु
	अगर (!gus->ace_flag)
		snd_ctl_add(gus->card, snd_ctl_new1(&snd_gus_joystick_control, gus));
पूर्ण

/*
 *
 */

अटल पूर्णांक snd_gus_मुक्त(काष्ठा snd_gus_card *gus)
अणु
	अगर (gus->gf1.res_port2 == शून्य)
		जाओ __hw_end;
	snd_gf1_stop(gus);
	snd_gus_init_dma_irq(gus, 0);
      __hw_end:
	release_and_मुक्त_resource(gus->gf1.res_port1);
	release_and_मुक्त_resource(gus->gf1.res_port2);
	अगर (gus->gf1.irq >= 0)
		मुक्त_irq(gus->gf1.irq, (व्योम *) gus);
	अगर (gus->gf1.dma1 >= 0) अणु
		disable_dma(gus->gf1.dma1);
		मुक्त_dma(gus->gf1.dma1);
	पूर्ण
	अगर (!gus->equal_dma && gus->gf1.dma2 >= 0) अणु
		disable_dma(gus->gf1.dma2);
		मुक्त_dma(gus->gf1.dma2);
	पूर्ण
	kमुक्त(gus);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gus_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_gus_card *gus = device->device_data;
	वापस snd_gus_मुक्त(gus);
पूर्ण

पूर्णांक snd_gus_create(काष्ठा snd_card *card,
		   अचिन्हित दीर्घ port,
		   पूर्णांक irq, पूर्णांक dma1, पूर्णांक dma2,
		   पूर्णांक समयr_dev,
		   पूर्णांक voices,
		   पूर्णांक pcm_channels,
		   पूर्णांक effect,
		   काष्ठा snd_gus_card **rgus)
अणु
	काष्ठा snd_gus_card *gus;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_gus_dev_मुक्त,
	पूर्ण;

	*rgus = शून्य;
	gus = kzalloc(माप(*gus), GFP_KERNEL);
	अगर (gus == शून्य)
		वापस -ENOMEM;
	spin_lock_init(&gus->reg_lock);
	spin_lock_init(&gus->voice_alloc);
	spin_lock_init(&gus->active_voice_lock);
	spin_lock_init(&gus->event_lock);
	spin_lock_init(&gus->dma_lock);
	spin_lock_init(&gus->pcm_volume_level_lock);
	spin_lock_init(&gus->uart_cmd_lock);
	mutex_init(&gus->dma_mutex);
	gus->gf1.irq = -1;
	gus->gf1.dma1 = -1;
	gus->gf1.dma2 = -1;
	gus->card = card;
	gus->gf1.port = port;
	/* fill रेजिस्टर variables क्रम speedup */
	gus->gf1.reg_page = GUSP(gus, GF1PAGE);
	gus->gf1.reg_regsel = GUSP(gus, GF1REGSEL);
	gus->gf1.reg_data8 = GUSP(gus, GF1DATAHIGH);
	gus->gf1.reg_data16 = GUSP(gus, GF1DATALOW);
	gus->gf1.reg_irqstat = GUSP(gus, IRQSTAT);
	gus->gf1.reg_dram = GUSP(gus, DRAM);
	gus->gf1.reg_समयrctrl = GUSP(gus, TIMERCNTRL);
	gus->gf1.reg_समयrdata = GUSP(gus, TIMERDATA);
	/* allocate resources */
	अगर ((gus->gf1.res_port1 = request_region(port, 16, "GUS GF1 (Adlib/SB)")) == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR "gus: can't grab SB port 0x%lx\n", port);
		snd_gus_मुक्त(gus);
		वापस -EBUSY;
	पूर्ण
	अगर ((gus->gf1.res_port2 = request_region(port + 0x100, 12, "GUS GF1 (Synth)")) == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR "gus: can't grab synth port 0x%lx\n", port + 0x100);
		snd_gus_मुक्त(gus);
		वापस -EBUSY;
	पूर्ण
	अगर (irq >= 0 && request_irq(irq, snd_gus_पूर्णांकerrupt, 0, "GUS GF1", (व्योम *) gus)) अणु
		snd_prपूर्णांकk(KERN_ERR "gus: can't grab irq %d\n", irq);
		snd_gus_मुक्त(gus);
		वापस -EBUSY;
	पूर्ण
	gus->gf1.irq = irq;
	card->sync_irq = irq;
	अगर (request_dma(dma1, "GUS - 1")) अणु
		snd_prपूर्णांकk(KERN_ERR "gus: can't grab DMA1 %d\n", dma1);
		snd_gus_मुक्त(gus);
		वापस -EBUSY;
	पूर्ण
	gus->gf1.dma1 = dma1;
	अगर (dma2 >= 0 && dma1 != dma2) अणु
		अगर (request_dma(dma2, "GUS - 2")) अणु
			snd_prपूर्णांकk(KERN_ERR "gus: can't grab DMA2 %d\n", dma2);
			snd_gus_मुक्त(gus);
			वापस -EBUSY;
		पूर्ण
		gus->gf1.dma2 = dma2;
	पूर्ण अन्यथा अणु
		gus->gf1.dma2 = gus->gf1.dma1;
		gus->equal_dma = 1;
	पूर्ण
	gus->समयr_dev = समयr_dev;
	अगर (voices < 14)
		voices = 14;
	अगर (voices > 32)
		voices = 32;
	अगर (pcm_channels < 0)
		pcm_channels = 0;
	अगर (pcm_channels > 8)
		pcm_channels = 8;
	pcm_channels++;
	pcm_channels &= ~1;
	gus->gf1.effect = effect ? 1 : 0;
	gus->gf1.active_voices = voices;
	gus->gf1.pcm_channels = pcm_channels;
	gus->gf1.volume_ramp = 25;
	gus->gf1.smooth_pan = 1;
	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, gus, &ops)) < 0) अणु
		snd_gus_मुक्त(gus);
		वापस err;
	पूर्ण
	*rgus = gus;
	वापस 0;
पूर्ण

/*
 *  Memory detection routine क्रम plain GF1 soundcards
 */

अटल पूर्णांक snd_gus_detect_memory(काष्ठा snd_gus_card * gus)
अणु
	पूर्णांक l, idx, local;
	अचिन्हित अक्षर d;

	snd_gf1_poke(gus, 0L, 0xaa);
	snd_gf1_poke(gus, 1L, 0x55);
	अगर (snd_gf1_peek(gus, 0L) != 0xaa || snd_gf1_peek(gus, 1L) != 0x55) अणु
		snd_prपूर्णांकk(KERN_ERR "plain GF1 card at 0x%lx without onboard DRAM?\n", gus->gf1.port);
		वापस -ENOMEM;
	पूर्ण
	क्रम (idx = 1, d = 0xab; idx < 4; idx++, d++) अणु
		local = idx << 18;
		snd_gf1_poke(gus, local, d);
		snd_gf1_poke(gus, local + 1, d + 1);
		अगर (snd_gf1_peek(gus, local) != d ||
		    snd_gf1_peek(gus, local + 1) != d + 1 ||
		    snd_gf1_peek(gus, 0L) != 0xaa)
			अवरोध;
	पूर्ण
#अगर 1
	gus->gf1.memory = idx << 18;
#अन्यथा
	gus->gf1.memory = 256 * 1024;
#पूर्ण_अगर
	क्रम (l = 0, local = gus->gf1.memory; l < 4; l++, local -= 256 * 1024) अणु
		gus->gf1.mem_alloc.banks_8[l].address =
		    gus->gf1.mem_alloc.banks_8[l].size = 0;
		gus->gf1.mem_alloc.banks_16[l].address = l << 18;
		gus->gf1.mem_alloc.banks_16[l].size = local > 0 ? 256 * 1024 : 0;
	पूर्ण
	gus->gf1.mem_alloc.banks_8[0].size = gus->gf1.memory;
	वापस 0;		/* some memory were detected */
पूर्ण

अटल पूर्णांक snd_gus_init_dma_irq(काष्ठा snd_gus_card * gus, पूर्णांक latches)
अणु
	काष्ठा snd_card *card;
	अचिन्हित दीर्घ flags;
	पूर्णांक irq, dma1, dma2;
	अटल स्थिर अचिन्हित अक्षर irqs[16] =
		अणु0, 0, 1, 3, 0, 2, 0, 4, 0, 1, 0, 5, 6, 0, 0, 7पूर्ण;
	अटल स्थिर अचिन्हित अक्षर dmas[8] =
		अणु6, 1, 0, 2, 0, 3, 4, 5पूर्ण;

	अगर (snd_BUG_ON(!gus))
		वापस -EINVAL;
	card = gus->card;
	अगर (snd_BUG_ON(!card))
		वापस -EINVAL;

	gus->mix_cntrl_reg &= 0xf8;
	gus->mix_cntrl_reg |= 0x01;	/* disable MIC, LINE IN, enable LINE OUT */
	अगर (gus->codec_flag || gus->ess_flag) अणु
		gus->mix_cntrl_reg &= ~1;	/* enable LINE IN */
		gus->mix_cntrl_reg |= 4;	/* enable MIC */
	पूर्ण
	dma1 = gus->gf1.dma1;
	dma1 = असल(dma1);
	dma1 = dmas[dma1 & 7];
	dma2 = gus->gf1.dma2;
	dma2 = असल(dma2);
	dma2 = dmas[dma2 & 7];
	dma1 |= gus->equal_dma ? 0x40 : (dma2 << 3);

	अगर ((dma1 & 7) == 0 || (dma2 & 7) == 0) अणु
		snd_prपूर्णांकk(KERN_ERR "Error! DMA isn't defined.\n");
		वापस -EINVAL;
	पूर्ण
	irq = gus->gf1.irq;
	irq = असल(irq);
	irq = irqs[irq & 0x0f];
	अगर (irq == 0) अणु
		snd_prपूर्णांकk(KERN_ERR "Error! IRQ isn't defined.\n");
		वापस -EINVAL;
	पूर्ण
	irq |= 0x40;
#अगर 0
	card->mixer.mix_ctrl_reg |= 0x10;
#पूर्ण_अगर

	spin_lock_irqsave(&gus->reg_lock, flags);
	outb(5, GUSP(gus, REGCNTRLS));
	outb(gus->mix_cntrl_reg, GUSP(gus, MIXCNTRLREG));
	outb(0x00, GUSP(gus, IRQDMACNTRLREG));
	outb(0, GUSP(gus, REGCNTRLS));
	spin_unlock_irqrestore(&gus->reg_lock, flags);

	udelay(100);

	spin_lock_irqsave(&gus->reg_lock, flags);
	outb(0x00 | gus->mix_cntrl_reg, GUSP(gus, MIXCNTRLREG));
	outb(dma1, GUSP(gus, IRQDMACNTRLREG));
	अगर (latches) अणु
		outb(0x40 | gus->mix_cntrl_reg, GUSP(gus, MIXCNTRLREG));
		outb(irq, GUSP(gus, IRQDMACNTRLREG));
	पूर्ण
	spin_unlock_irqrestore(&gus->reg_lock, flags);

	udelay(100);

	spin_lock_irqsave(&gus->reg_lock, flags);
	outb(0x00 | gus->mix_cntrl_reg, GUSP(gus, MIXCNTRLREG));
	outb(dma1, GUSP(gus, IRQDMACNTRLREG));
	अगर (latches) अणु
		outb(0x40 | gus->mix_cntrl_reg, GUSP(gus, MIXCNTRLREG));
		outb(irq, GUSP(gus, IRQDMACNTRLREG));
	पूर्ण
	spin_unlock_irqrestore(&gus->reg_lock, flags);

	snd_gf1_delay(gus);

	अगर (latches)
		gus->mix_cntrl_reg |= 0x08;	/* enable latches */
	अन्यथा
		gus->mix_cntrl_reg &= ~0x08;	/* disable latches */
	spin_lock_irqsave(&gus->reg_lock, flags);
	outb(gus->mix_cntrl_reg, GUSP(gus, MIXCNTRLREG));
	outb(0, GUSP(gus, GF1PAGE));
	spin_unlock_irqrestore(&gus->reg_lock, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_gus_check_version(काष्ठा snd_gus_card * gus)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर val, rev;
	काष्ठा snd_card *card;

	card = gus->card;
	spin_lock_irqsave(&gus->reg_lock, flags);
	outb(0x20, GUSP(gus, REGCNTRLS));
	val = inb(GUSP(gus, REGCNTRLS));
	rev = inb(GUSP(gus, BOARDVERSION));
	spin_unlock_irqrestore(&gus->reg_lock, flags);
	snd_prपूर्णांकdd("GF1 [0x%lx] init - val = 0x%x, rev = 0x%x\n", gus->gf1.port, val, rev);
	म_नकल(card->driver, "GUS");
	म_नकल(card->दीर्घname, "Gravis UltraSound Classic (2.4)");
	अगर ((val != 255 && (val & 0x06)) || (rev >= 5 && rev != 255)) अणु
		अगर (rev >= 5 && rev <= 9) अणु
			gus->ics_flag = 1;
			अगर (rev == 5)
				gus->ics_flipped = 1;
			card->दीर्घname[27] = '3';
			card->दीर्घname[29] = rev == 5 ? '5' : '7';
		पूर्ण
		अगर (rev >= 10 && rev != 255) अणु
			अगर (rev >= 10 && rev <= 11) अणु
				म_नकल(card->driver, "GUS MAX");
				म_नकल(card->दीर्घname, "Gravis UltraSound MAX");
				gus->max_flag = 1;
			पूर्ण अन्यथा अगर (rev == 0x30) अणु
				म_नकल(card->driver, "GUS ACE");
				म_नकल(card->दीर्घname, "Gravis UltraSound Ace");
				gus->ace_flag = 1;
			पूर्ण अन्यथा अगर (rev == 0x50) अणु
				म_नकल(card->driver, "GUS Extreme");
				म_नकल(card->दीर्घname, "Gravis UltraSound Extreme");
				gus->ess_flag = 1;
			पूर्ण अन्यथा अणु
				snd_prपूर्णांकk(KERN_ERR "unknown GF1 revision number at 0x%lx - 0x%x (0x%x)\n", gus->gf1.port, rev, val);
				snd_prपूर्णांकk(KERN_ERR "  please - report to <perex@perex.cz>\n");
			पूर्ण
		पूर्ण
	पूर्ण
	म_नकल(card->लघुname, card->दीर्घname);
	gus->uart_enable = 1;	/* standard GUSes करोesn't have midi uart trouble */
	snd_gus_init_control(gus);
	वापस 0;
पूर्ण

पूर्णांक snd_gus_initialize(काष्ठा snd_gus_card *gus)
अणु
	पूर्णांक err;

	अगर (!gus->पूर्णांकerwave) अणु
		अगर ((err = snd_gus_check_version(gus)) < 0) अणु
			snd_prपूर्णांकk(KERN_ERR "version check failed\n");
			वापस err;
		पूर्ण
		अगर ((err = snd_gus_detect_memory(gus)) < 0)
			वापस err;
	पूर्ण
	अगर ((err = snd_gus_init_dma_irq(gus, 1)) < 0)
		वापस err;
	snd_gf1_start(gus);
	gus->initialized = 1;
	वापस 0;
पूर्ण

  /* gus_io.c */
EXPORT_SYMBOL(snd_gf1_delay);
EXPORT_SYMBOL(snd_gf1_ग_लिखो8);
EXPORT_SYMBOL(snd_gf1_look8);
EXPORT_SYMBOL(snd_gf1_ग_लिखो16);
EXPORT_SYMBOL(snd_gf1_look16);
EXPORT_SYMBOL(snd_gf1_i_ग_लिखो8);
EXPORT_SYMBOL(snd_gf1_i_look8);
EXPORT_SYMBOL(snd_gf1_i_look16);
EXPORT_SYMBOL(snd_gf1_dram_addr);
EXPORT_SYMBOL(snd_gf1_ग_लिखो_addr);
EXPORT_SYMBOL(snd_gf1_poke);
EXPORT_SYMBOL(snd_gf1_peek);
  /* gus_reset.c */
EXPORT_SYMBOL(snd_gf1_alloc_voice);
EXPORT_SYMBOL(snd_gf1_मुक्त_voice);
EXPORT_SYMBOL(snd_gf1_ctrl_stop);
EXPORT_SYMBOL(snd_gf1_stop_voice);
  /* gus_mixer.c */
EXPORT_SYMBOL(snd_gf1_new_mixer);
  /* gus_pcm.c */
EXPORT_SYMBOL(snd_gf1_pcm_new);
  /* gus.c */
EXPORT_SYMBOL(snd_gus_use_inc);
EXPORT_SYMBOL(snd_gus_use_dec);
EXPORT_SYMBOL(snd_gus_create);
EXPORT_SYMBOL(snd_gus_initialize);
  /* gus_irq.c */
EXPORT_SYMBOL(snd_gus_पूर्णांकerrupt);
  /* gus_uart.c */
EXPORT_SYMBOL(snd_gf1_rawmidi_new);
  /* gus_dram.c */
EXPORT_SYMBOL(snd_gus_dram_ग_लिखो);
EXPORT_SYMBOL(snd_gus_dram_पढ़ो);
  /* gus_volume.c */
EXPORT_SYMBOL(snd_gf1_lvol_to_gvol_raw);
EXPORT_SYMBOL(snd_gf1_translate_freq);
  /* gus_mem.c */
EXPORT_SYMBOL(snd_gf1_mem_alloc);
EXPORT_SYMBOL(snd_gf1_mem_xमुक्त);
EXPORT_SYMBOL(snd_gf1_mem_मुक्त);
EXPORT_SYMBOL(snd_gf1_mem_lock);
