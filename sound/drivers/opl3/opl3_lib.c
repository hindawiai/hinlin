<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>,
 *                   Hannu Savolainen 1993-1996,
 *                   Rob Hooft
 *                   
 *  Routines क्रम control of AdLib FM cards (OPL2/OPL3/OPL4 chips)
 *
 *  Most अगर code is ported from OSS/Lite.
 */

#समावेश <sound/opl3.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <sound/minors.h>
#समावेश "opl3_voice.h"

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>, Hannu Savolainen 1993-1996, Rob Hooft");
MODULE_DESCRIPTION("Routines for control of AdLib FM cards (OPL2/OPL3/OPL4 chips)");
MODULE_LICENSE("GPL");

अटल व्योम snd_opl2_command(काष्ठा snd_opl3 * opl3, अचिन्हित लघु cmd, अचिन्हित अक्षर val)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ port;

	/*
	 * The original 2-OP synth requires a quite दीर्घ delay
	 * after writing to a रेजिस्टर.
	 */

	port = (cmd & OPL3_RIGHT) ? opl3->r_port : opl3->l_port;

	spin_lock_irqsave(&opl3->reg_lock, flags);

	outb((अचिन्हित अक्षर) cmd, port);
	udelay(10);

	outb((अचिन्हित अक्षर) val, port + 1);
	udelay(30);

	spin_unlock_irqrestore(&opl3->reg_lock, flags);
पूर्ण

अटल व्योम snd_opl3_command(काष्ठा snd_opl3 * opl3, अचिन्हित लघु cmd, अचिन्हित अक्षर val)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ port;

	/*
	 * The OPL-3 survives with just two INBs
	 * after writing to a रेजिस्टर.
	 */

	port = (cmd & OPL3_RIGHT) ? opl3->r_port : opl3->l_port;

	spin_lock_irqsave(&opl3->reg_lock, flags);

	outb((अचिन्हित अक्षर) cmd, port);
	inb(opl3->l_port);
	inb(opl3->l_port);

	outb((अचिन्हित अक्षर) val, port + 1);
	inb(opl3->l_port);
	inb(opl3->l_port);

	spin_unlock_irqrestore(&opl3->reg_lock, flags);
पूर्ण

अटल पूर्णांक snd_opl3_detect(काष्ठा snd_opl3 * opl3)
अणु
	/*
	 * This function वापसs 1 अगर the FM chip is present at the given I/O port
	 * The detection algorithm plays with the समयr built in the FM chip and
	 * looks क्रम a change in the status रेजिस्टर.
	 *
	 * Note! The समयrs of the FM chip are not connected to AdLib (and compatible)
	 * boards.
	 *
	 * Note2! The chip is initialized अगर detected.
	 */

	अचिन्हित अक्षर stat1, stat2, signature;

	/* Reset समयrs 1 and 2 */
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TIMER_CONTROL, OPL3_TIMER1_MASK | OPL3_TIMER2_MASK);
	/* Reset the IRQ of the FM chip */
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TIMER_CONTROL, OPL3_IRQ_RESET);
	signature = stat1 = inb(opl3->l_port);	/* Status रेजिस्टर */
	अगर ((stat1 & 0xe0) != 0x00) अणु	/* Should be 0x00 */
		snd_prपूर्णांकd("OPL3: stat1 = 0x%x\n", stat1);
		वापस -ENODEV;
	पूर्ण
	/* Set समयr1 to 0xff */
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TIMER1, 0xff);
	/* Unmask and start समयr 1 */
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TIMER_CONTROL, OPL3_TIMER2_MASK | OPL3_TIMER1_START);
	/* Now we have to delay at least 80us */
	udelay(200);
	/* Read status after समयrs have expired */
	stat2 = inb(opl3->l_port);
	/* Stop the समयrs */
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TIMER_CONTROL, OPL3_TIMER1_MASK | OPL3_TIMER2_MASK);
	/* Reset the IRQ of the FM chip */
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TIMER_CONTROL, OPL3_IRQ_RESET);
	अगर ((stat2 & 0xe0) != 0xc0) अणु	/* There is no YM3812 */
		snd_prपूर्णांकd("OPL3: stat2 = 0x%x\n", stat2);
		वापस -ENODEV;
	पूर्ण

	/* If the toplevel code knows exactly the type of chip, करोn't try
	   to detect it. */
	अगर (opl3->hardware != OPL3_HW_AUTO)
		वापस 0;

	/* There is a FM chip on this address. Detect the type (OPL2 to OPL4) */
	अगर (signature == 0x06) अणु	/* OPL2 */
		opl3->hardware = OPL3_HW_OPL2;
	पूर्ण अन्यथा अणु
		/*
		 * If we had an OPL4 chip, opl3->hardware would have been set
		 * by the OPL4 driver; so we can assume OPL3 here.
		 */
		अगर (snd_BUG_ON(!opl3->r_port))
			वापस -ENODEV;
		opl3->hardware = OPL3_HW_OPL3;
	पूर्ण
	वापस 0;
पूर्ण

/*
 *  AdLib समयrs
 */

/*
 *  Timer 1 - 80us
 */

अटल पूर्णांक snd_opl3_समयr1_start(काष्ठा snd_समयr * समयr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर पंचांगp;
	अचिन्हित पूर्णांक ticks;
	काष्ठा snd_opl3 *opl3;

	opl3 = snd_समयr_chip(समयr);
	spin_lock_irqsave(&opl3->समयr_lock, flags);
	ticks = समयr->sticks;
	पंचांगp = (opl3->समयr_enable | OPL3_TIMER1_START) & ~OPL3_TIMER1_MASK;
	opl3->समयr_enable = पंचांगp;
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TIMER1, 256 - ticks);	/* समयr 1 count */
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TIMER_CONTROL, पंचांगp);	/* enable समयr 1 IRQ */
	spin_unlock_irqrestore(&opl3->समयr_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl3_समयr1_stop(काष्ठा snd_समयr * समयr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर पंचांगp;
	काष्ठा snd_opl3 *opl3;

	opl3 = snd_समयr_chip(समयr);
	spin_lock_irqsave(&opl3->समयr_lock, flags);
	पंचांगp = (opl3->समयr_enable | OPL3_TIMER1_MASK) & ~OPL3_TIMER1_START;
	opl3->समयr_enable = पंचांगp;
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TIMER_CONTROL, पंचांगp);	/* disable समयr #1 */
	spin_unlock_irqrestore(&opl3->समयr_lock, flags);
	वापस 0;
पूर्ण

/*
 *  Timer 2 - 320us
 */

अटल पूर्णांक snd_opl3_समयr2_start(काष्ठा snd_समयr * समयr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर पंचांगp;
	अचिन्हित पूर्णांक ticks;
	काष्ठा snd_opl3 *opl3;

	opl3 = snd_समयr_chip(समयr);
	spin_lock_irqsave(&opl3->समयr_lock, flags);
	ticks = समयr->sticks;
	पंचांगp = (opl3->समयr_enable | OPL3_TIMER2_START) & ~OPL3_TIMER2_MASK;
	opl3->समयr_enable = पंचांगp;
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TIMER2, 256 - ticks);	/* समयr 1 count */
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TIMER_CONTROL, पंचांगp);	/* enable समयr 1 IRQ */
	spin_unlock_irqrestore(&opl3->समयr_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl3_समयr2_stop(काष्ठा snd_समयr * समयr)
अणु
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर पंचांगp;
	काष्ठा snd_opl3 *opl3;

	opl3 = snd_समयr_chip(समयr);
	spin_lock_irqsave(&opl3->समयr_lock, flags);
	पंचांगp = (opl3->समयr_enable | OPL3_TIMER2_MASK) & ~OPL3_TIMER2_START;
	opl3->समयr_enable = पंचांगp;
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TIMER_CONTROL, पंचांगp);	/* disable समयr #1 */
	spin_unlock_irqrestore(&opl3->समयr_lock, flags);
	वापस 0;
पूर्ण

/*

 */

अटल स्थिर काष्ठा snd_समयr_hardware snd_opl3_समयr1 =
अणु
	.flags =	SNDRV_TIMER_HW_STOP,
	.resolution =	80000,
	.ticks =	256,
	.start =	snd_opl3_समयr1_start,
	.stop =		snd_opl3_समयr1_stop,
पूर्ण;

अटल स्थिर काष्ठा snd_समयr_hardware snd_opl3_समयr2 =
अणु
	.flags =	SNDRV_TIMER_HW_STOP,
	.resolution =	320000,
	.ticks =	256,
	.start =	snd_opl3_समयr2_start,
	.stop =		snd_opl3_समयr2_stop,
पूर्ण;

अटल पूर्णांक snd_opl3_समयr1_init(काष्ठा snd_opl3 * opl3, पूर्णांक समयr_no)
अणु
	काष्ठा snd_समयr *समयr = शून्य;
	काष्ठा snd_समयr_id tid;
	पूर्णांक err;

	tid.dev_class = SNDRV_TIMER_CLASS_CARD;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = opl3->card->number;
	tid.device = समयr_no;
	tid.subdevice = 0;
	अगर ((err = snd_समयr_new(opl3->card, "AdLib timer #1", &tid, &समयr)) >= 0) अणु
		म_नकल(समयr->name, "AdLib timer #1");
		समयr->निजी_data = opl3;
		समयr->hw = snd_opl3_समयr1;
	पूर्ण
	opl3->समयr1 = समयr;
	वापस err;
पूर्ण

अटल पूर्णांक snd_opl3_समयr2_init(काष्ठा snd_opl3 * opl3, पूर्णांक समयr_no)
अणु
	काष्ठा snd_समयr *समयr = शून्य;
	काष्ठा snd_समयr_id tid;
	पूर्णांक err;

	tid.dev_class = SNDRV_TIMER_CLASS_CARD;
	tid.dev_sclass = SNDRV_TIMER_SCLASS_NONE;
	tid.card = opl3->card->number;
	tid.device = समयr_no;
	tid.subdevice = 0;
	अगर ((err = snd_समयr_new(opl3->card, "AdLib timer #2", &tid, &समयr)) >= 0) अणु
		म_नकल(समयr->name, "AdLib timer #2");
		समयr->निजी_data = opl3;
		समयr->hw = snd_opl3_समयr2;
	पूर्ण
	opl3->समयr2 = समयr;
	वापस err;
पूर्ण

/*

 */

व्योम snd_opl3_पूर्णांकerrupt(काष्ठा snd_hwdep * hw)
अणु
	अचिन्हित अक्षर status;
	काष्ठा snd_opl3 *opl3;
	काष्ठा snd_समयr *समयr;

	अगर (hw == शून्य)
		वापस;

	opl3 = hw->निजी_data;
	status = inb(opl3->l_port);
#अगर 0
	snd_prपूर्णांकk(KERN_DEBUG "AdLib IRQ status = 0x%x\n", status);
#पूर्ण_अगर
	अगर (!(status & 0x80))
		वापस;

	अगर (status & 0x40) अणु
		समयr = opl3->समयr1;
		snd_समयr_पूर्णांकerrupt(समयr, समयr->sticks);
	पूर्ण
	अगर (status & 0x20) अणु
		समयr = opl3->समयr2;
		snd_समयr_पूर्णांकerrupt(समयr, समयr->sticks);
	पूर्ण
पूर्ण

EXPORT_SYMBOL(snd_opl3_पूर्णांकerrupt);

/*

 */

अटल पूर्णांक snd_opl3_मुक्त(काष्ठा snd_opl3 *opl3)
अणु
	अगर (snd_BUG_ON(!opl3))
		वापस -ENXIO;
	अगर (opl3->निजी_मुक्त)
		opl3->निजी_मुक्त(opl3);
	snd_opl3_clear_patches(opl3);
	release_and_मुक्त_resource(opl3->res_l_port);
	release_and_मुक्त_resource(opl3->res_r_port);
	kमुक्त(opl3);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl3_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_opl3 *opl3 = device->device_data;
	वापस snd_opl3_मुक्त(opl3);
पूर्ण

पूर्णांक snd_opl3_new(काष्ठा snd_card *card,
		 अचिन्हित लघु hardware,
		 काष्ठा snd_opl3 **ropl3)
अणु
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_opl3_dev_मुक्त,
	पूर्ण;
	काष्ठा snd_opl3 *opl3;
	पूर्णांक err;

	*ropl3 = शून्य;
	opl3 = kzalloc(माप(*opl3), GFP_KERNEL);
	अगर (!opl3)
		वापस -ENOMEM;

	opl3->card = card;
	opl3->hardware = hardware;
	spin_lock_init(&opl3->reg_lock);
	spin_lock_init(&opl3->समयr_lock);

	अगर ((err = snd_device_new(card, SNDRV_DEV_CODEC, opl3, &ops)) < 0) अणु
		snd_opl3_मुक्त(opl3);
		वापस err;
	पूर्ण

	*ropl3 = opl3;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_opl3_new);

पूर्णांक snd_opl3_init(काष्ठा snd_opl3 *opl3)
अणु
	अगर (! opl3->command) अणु
		prपूर्णांकk(KERN_ERR "snd_opl3_init: command not defined!\n");
		वापस -EINVAL;
	पूर्ण

	opl3->command(opl3, OPL3_LEFT | OPL3_REG_TEST, OPL3_ENABLE_WAVE_SELECT);
	/* Melodic mode */
	opl3->command(opl3, OPL3_LEFT | OPL3_REG_PERCUSSION, 0x00);

	चयन (opl3->hardware & OPL3_HW_MASK) अणु
	हाल OPL3_HW_OPL2:
		opl3->max_voices = MAX_OPL2_VOICES;
		अवरोध;
	हाल OPL3_HW_OPL3:
	हाल OPL3_HW_OPL4:
		opl3->max_voices = MAX_OPL3_VOICES;
		/* Enter OPL3 mode */
		opl3->command(opl3, OPL3_RIGHT | OPL3_REG_MODE, OPL3_OPL3_ENABLE);
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_opl3_init);

पूर्णांक snd_opl3_create(काष्ठा snd_card *card,
		    अचिन्हित दीर्घ l_port,
		    अचिन्हित दीर्घ r_port,
		    अचिन्हित लघु hardware,
		    पूर्णांक पूर्णांकegrated,
		    काष्ठा snd_opl3 ** ropl3)
अणु
	काष्ठा snd_opl3 *opl3;
	पूर्णांक err;

	*ropl3 = शून्य;
	अगर ((err = snd_opl3_new(card, hardware, &opl3)) < 0)
		वापस err;
	अगर (! पूर्णांकegrated) अणु
		अगर ((opl3->res_l_port = request_region(l_port, 2, "OPL2/3 (left)")) == शून्य) अणु
			snd_prपूर्णांकk(KERN_ERR "opl3: can't grab left port 0x%lx\n", l_port);
			snd_device_मुक्त(card, opl3);
			वापस -EBUSY;
		पूर्ण
		अगर (r_port != 0 &&
		    (opl3->res_r_port = request_region(r_port, 2, "OPL2/3 (right)")) == शून्य) अणु
			snd_prपूर्णांकk(KERN_ERR "opl3: can't grab right port 0x%lx\n", r_port);
			snd_device_मुक्त(card, opl3);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	opl3->l_port = l_port;
	opl3->r_port = r_port;

	चयन (opl3->hardware) अणु
	/* some hardware करोesn't support समयrs */
	हाल OPL3_HW_OPL3_SV:
	हाल OPL3_HW_OPL3_CS:
	हाल OPL3_HW_OPL3_FM801:
		opl3->command = &snd_opl3_command;
		अवरोध;
	शेष:
		opl3->command = &snd_opl2_command;
		अगर ((err = snd_opl3_detect(opl3)) < 0) अणु
			snd_prपूर्णांकd("OPL2/3 chip not detected at 0x%lx/0x%lx\n",
				   opl3->l_port, opl3->r_port);
			snd_device_मुक्त(card, opl3);
			वापस err;
		पूर्ण
		/* detect routine वापसs correct hardware type */
		चयन (opl3->hardware & OPL3_HW_MASK) अणु
		हाल OPL3_HW_OPL3:
		हाल OPL3_HW_OPL4:
			opl3->command = &snd_opl3_command;
		पूर्ण
	पूर्ण

	snd_opl3_init(opl3);

	*ropl3 = opl3;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_opl3_create);

पूर्णांक snd_opl3_समयr_new(काष्ठा snd_opl3 * opl3, पूर्णांक समयr1_dev, पूर्णांक समयr2_dev)
अणु
	पूर्णांक err;

	अगर (समयr1_dev >= 0)
		अगर ((err = snd_opl3_समयr1_init(opl3, समयr1_dev)) < 0)
			वापस err;
	अगर (समयr2_dev >= 0) अणु
		अगर ((err = snd_opl3_समयr2_init(opl3, समयr2_dev)) < 0) अणु
			snd_device_मुक्त(opl3->card, opl3->समयr1);
			opl3->समयr1 = शून्य;
			वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_opl3_समयr_new);

पूर्णांक snd_opl3_hwdep_new(काष्ठा snd_opl3 * opl3,
		       पूर्णांक device, पूर्णांक seq_device,
		       काष्ठा snd_hwdep ** rhwdep)
अणु
	काष्ठा snd_hwdep *hw;
	काष्ठा snd_card *card = opl3->card;
	पूर्णांक err;

	अगर (rhwdep)
		*rhwdep = शून्य;

	/* create hardware dependent device (direct FM) */

	अगर ((err = snd_hwdep_new(card, "OPL2/OPL3", device, &hw)) < 0) अणु
		snd_device_मुक्त(card, opl3);
		वापस err;
	पूर्ण
	hw->निजी_data = opl3;
	hw->exclusive = 1;
#अगर_घोषित CONFIG_SND_OSSEMUL
	अगर (device == 0)
		hw->oss_type = SNDRV_OSS_DEVICE_TYPE_DMFM;
#पूर्ण_अगर
	म_नकल(hw->name, hw->id);
	चयन (opl3->hardware & OPL3_HW_MASK) अणु
	हाल OPL3_HW_OPL2:
		म_नकल(hw->name, "OPL2 FM");
		hw->अगरace = SNDRV_HWDEP_IFACE_OPL2;
		अवरोध;
	हाल OPL3_HW_OPL3:
		म_नकल(hw->name, "OPL3 FM");
		hw->अगरace = SNDRV_HWDEP_IFACE_OPL3;
		अवरोध;
	हाल OPL3_HW_OPL4:
		म_नकल(hw->name, "OPL4 FM");
		hw->अगरace = SNDRV_HWDEP_IFACE_OPL4;
		अवरोध;
	पूर्ण

	/* चालकs - only ioctl */
	hw->ops.खोलो = snd_opl3_खोलो;
	hw->ops.ioctl = snd_opl3_ioctl;
	hw->ops.ग_लिखो = snd_opl3_ग_लिखो;
	hw->ops.release = snd_opl3_release;

	opl3->hwdep = hw;
	opl3->seq_dev_num = seq_device;
#अगर IS_ENABLED(CONFIG_SND_SEQUENCER)
	अगर (snd_seq_device_new(card, seq_device, SNDRV_SEQ_DEV_ID_OPL3,
			       माप(काष्ठा snd_opl3 *), &opl3->seq_dev) >= 0) अणु
		म_नकल(opl3->seq_dev->name, hw->name);
		*(काष्ठा snd_opl3 **)SNDRV_SEQ_DEVICE_ARGPTR(opl3->seq_dev) = opl3;
	पूर्ण
#पूर्ण_अगर
	अगर (rhwdep)
		*rhwdep = hw;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_opl3_hwdep_new);
