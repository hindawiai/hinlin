<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *                   Uros Bizjak <uros@kss-loka.si>
 *
 *  Lowlevel routines क्रम control of Sound Blaster cards
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/ioport.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <sound/core.h>
#समावेश <sound/sb.h>
#समावेश <sound/initval.h>

#समावेश <यंत्र/dma.h>

MODULE_AUTHOR("Jaroslav Kysela <perex@perex.cz>");
MODULE_DESCRIPTION("ALSA lowlevel driver for Sound Blaster cards");
MODULE_LICENSE("GPL");

#घोषणा BUSY_LOOPS 100000

#अघोषित IO_DEBUG

पूर्णांक snd_sbdsp_command(काष्ठा snd_sb *chip, अचिन्हित अक्षर val)
अणु
	पूर्णांक i;
#अगर_घोषित IO_DEBUG
	snd_prपूर्णांकk(KERN_DEBUG "command 0x%x\n", val);
#पूर्ण_अगर
	क्रम (i = BUSY_LOOPS; i; i--)
		अगर ((inb(SBP(chip, STATUS)) & 0x80) == 0) अणु
			outb(val, SBP(chip, COMMAND));
			वापस 1;
		पूर्ण
	snd_prपूर्णांकd("%s [0x%lx]: timeout (0x%x)\n", __func__, chip->port, val);
	वापस 0;
पूर्ण

पूर्णांक snd_sbdsp_get_byte(काष्ठा snd_sb *chip)
अणु
	पूर्णांक val;
	पूर्णांक i;
	क्रम (i = BUSY_LOOPS; i; i--) अणु
		अगर (inb(SBP(chip, DATA_AVAIL)) & 0x80) अणु
			val = inb(SBP(chip, READ));
#अगर_घोषित IO_DEBUG
			snd_prपूर्णांकk(KERN_DEBUG "get_byte 0x%x\n", val);
#पूर्ण_अगर
			वापस val;
		पूर्ण
	पूर्ण
	snd_prपूर्णांकd("%s [0x%lx]: timeout\n", __func__, chip->port);
	वापस -ENODEV;
पूर्ण

पूर्णांक snd_sbdsp_reset(काष्ठा snd_sb *chip)
अणु
	पूर्णांक i;

	outb(1, SBP(chip, RESET));
	udelay(10);
	outb(0, SBP(chip, RESET));
	udelay(30);
	क्रम (i = BUSY_LOOPS; i; i--)
		अगर (inb(SBP(chip, DATA_AVAIL)) & 0x80) अणु
			अगर (inb(SBP(chip, READ)) == 0xaa)
				वापस 0;
			अन्यथा
				अवरोध;
		पूर्ण
	snd_prपूर्णांकdd("%s [0x%lx] failed...\n", __func__, chip->port);
	वापस -ENODEV;
पूर्ण

अटल पूर्णांक snd_sbdsp_version(काष्ठा snd_sb * chip)
अणु
	अचिन्हित पूर्णांक result;

	snd_sbdsp_command(chip, SB_DSP_GET_VERSION);
	result = (लघु) snd_sbdsp_get_byte(chip) << 8;
	result |= (लघु) snd_sbdsp_get_byte(chip);
	वापस result;
पूर्ण

अटल पूर्णांक snd_sbdsp_probe(काष्ठा snd_sb * chip)
अणु
	पूर्णांक version;
	पूर्णांक major, minor;
	अक्षर *str;
	अचिन्हित दीर्घ flags;

	/*
	 *  initialization sequence
	 */

	spin_lock_irqsave(&chip->reg_lock, flags);
	अगर (snd_sbdsp_reset(chip) < 0) अणु
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		वापस -ENODEV;
	पूर्ण
	version = snd_sbdsp_version(chip);
	अगर (version < 0) अणु
		spin_unlock_irqrestore(&chip->reg_lock, flags);
		वापस -ENODEV;
	पूर्ण
	spin_unlock_irqrestore(&chip->reg_lock, flags);
	major = version >> 8;
	minor = version & 0xff;
	snd_prपूर्णांकdd("SB [0x%lx]: DSP chip found, version = %i.%i\n",
		    chip->port, major, minor);

	चयन (chip->hardware) अणु
	हाल SB_HW_AUTO:
		चयन (major) अणु
		हाल 1:
			chip->hardware = SB_HW_10;
			str = "1.0";
			अवरोध;
		हाल 2:
			अगर (minor) अणु
				chip->hardware = SB_HW_201;
				str = "2.01+";
			पूर्ण अन्यथा अणु
				chip->hardware = SB_HW_20;
				str = "2.0";
			पूर्ण
			अवरोध;
		हाल 3:
			chip->hardware = SB_HW_PRO;
			str = "Pro";
			अवरोध;
		हाल 4:
			chip->hardware = SB_HW_16;
			str = "16";
			अवरोध;
		शेष:
			snd_prपूर्णांकk(KERN_INFO "SB [0x%lx]: unknown DSP chip version %i.%i\n",
				   chip->port, major, minor);
			वापस -ENODEV;
		पूर्ण
		अवरोध;
	हाल SB_HW_ALS100:
		str = "16 (ALS-100)";
		अवरोध;
	हाल SB_HW_ALS4000:
		str = "16 (ALS-4000)";
		अवरोध;
	हाल SB_HW_DT019X:
		str = "(DT019X/ALS007)";
		अवरोध;
	हाल SB_HW_CS5530:
		str = "16 (CS5530)";
		अवरोध;
	हाल SB_HW_JAZZ16:
		str = "Pro (Jazz16)";
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण
	प्र_लिखो(chip->name, "Sound Blaster %s", str);
	chip->version = (major << 8) | minor;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sbdsp_मुक्त(काष्ठा snd_sb *chip)
अणु
	release_and_मुक्त_resource(chip->res_port);
	अगर (chip->irq >= 0)
		मुक्त_irq(chip->irq, (व्योम *) chip);
#अगर_घोषित CONFIG_ISA
	अगर (chip->dma8 >= 0) अणु
		disable_dma(chip->dma8);
		मुक्त_dma(chip->dma8);
	पूर्ण
	अगर (chip->dma16 >= 0 && chip->dma16 != chip->dma8) अणु
		disable_dma(chip->dma16);
		मुक्त_dma(chip->dma16);
	पूर्ण
#पूर्ण_अगर
	kमुक्त(chip);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_sbdsp_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_sb *chip = device->device_data;
	वापस snd_sbdsp_मुक्त(chip);
पूर्ण

पूर्णांक snd_sbdsp_create(काष्ठा snd_card *card,
		     अचिन्हित दीर्घ port,
		     पूर्णांक irq,
		     irq_handler_t irq_handler,
		     पूर्णांक dma8,
		     पूर्णांक dma16,
		     अचिन्हित लघु hardware,
		     काष्ठा snd_sb **r_chip)
अणु
	काष्ठा snd_sb *chip;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त =	snd_sbdsp_dev_मुक्त,
	पूर्ण;

	अगर (snd_BUG_ON(!r_chip))
		वापस -EINVAL;
	*r_chip = शून्य;
	chip = kzalloc(माप(*chip), GFP_KERNEL);
	अगर (chip == शून्य)
		वापस -ENOMEM;
	spin_lock_init(&chip->reg_lock);
	spin_lock_init(&chip->खोलो_lock);
	spin_lock_init(&chip->midi_input_lock);
	spin_lock_init(&chip->mixer_lock);
	chip->irq = -1;
	chip->dma8 = -1;
	chip->dma16 = -1;
	chip->port = port;
	
	अगर (request_irq(irq, irq_handler,
			(hardware == SB_HW_ALS4000 ||
			 hardware == SB_HW_CS5530) ?
			IRQF_SHARED : 0,
			"SoundBlaster", (व्योम *) chip)) अणु
		snd_prपूर्णांकk(KERN_ERR "sb: can't grab irq %d\n", irq);
		snd_sbdsp_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->irq = irq;
	card->sync_irq = chip->irq;

	अगर (hardware == SB_HW_ALS4000)
		जाओ __skip_allocation;
	
	अगर ((chip->res_port = request_region(port, 16, "SoundBlaster")) == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR "sb: can't grab port 0x%lx\n", port);
		snd_sbdsp_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण

#अगर_घोषित CONFIG_ISA
	अगर (dma8 >= 0 && request_dma(dma8, "SoundBlaster - 8bit")) अणु
		snd_prपूर्णांकk(KERN_ERR "sb: can't grab DMA8 %d\n", dma8);
		snd_sbdsp_मुक्त(chip);
		वापस -EBUSY;
	पूर्ण
	chip->dma8 = dma8;
	अगर (dma16 >= 0) अणु
		अगर (hardware != SB_HW_ALS100 && (dma16 < 5 || dma16 > 7)) अणु
			/* no duplex */
			dma16 = -1;
		पूर्ण अन्यथा अगर (request_dma(dma16, "SoundBlaster - 16bit")) अणु
			snd_prपूर्णांकk(KERN_ERR "sb: can't grab DMA16 %d\n", dma16);
			snd_sbdsp_मुक्त(chip);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	chip->dma16 = dma16;
#पूर्ण_अगर

      __skip_allocation:
	chip->card = card;
	chip->hardware = hardware;
	अगर ((err = snd_sbdsp_probe(chip)) < 0) अणु
		snd_sbdsp_मुक्त(chip);
		वापस err;
	पूर्ण
	अगर ((err = snd_device_new(card, SNDRV_DEV_LOWLEVEL, chip, &ops)) < 0) अणु
		snd_sbdsp_मुक्त(chip);
		वापस err;
	पूर्ण
	*r_chip = chip;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_sbdsp_command);
EXPORT_SYMBOL(snd_sbdsp_get_byte);
EXPORT_SYMBOL(snd_sbdsp_reset);
EXPORT_SYMBOL(snd_sbdsp_create);
/* sb_mixer.c */
EXPORT_SYMBOL(snd_sbmixer_ग_लिखो);
EXPORT_SYMBOL(snd_sbmixer_पढ़ो);
EXPORT_SYMBOL(snd_sbmixer_new);
EXPORT_SYMBOL(snd_sbmixer_add_ctl);
#अगर_घोषित CONFIG_PM
EXPORT_SYMBOL(snd_sbmixer_suspend);
EXPORT_SYMBOL(snd_sbmixer_resume);
#पूर्ण_अगर
