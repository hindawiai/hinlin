<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Functions क्रम accessing OPL4 devices
 * Copyright (c) 2003 by Clemens Ladisch <clemens@ladisch.de>
 */

#समावेश "opl4_local.h"
#समावेश <sound/initval.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>

MODULE_AUTHOR("Clemens Ladisch <clemens@ladisch.de>");
MODULE_DESCRIPTION("OPL4 driver");
MODULE_LICENSE("GPL");

अटल अंतरभूत व्योम snd_opl4_रुको(काष्ठा snd_opl4 *opl4)
अणु
	पूर्णांक समयout = 10;
	जबतक ((inb(opl4->fm_port) & OPL4_STATUS_BUSY) && --समयout > 0)
		;
पूर्ण

व्योम snd_opl4_ग_लिखो(काष्ठा snd_opl4 *opl4, u8 reg, u8 value)
अणु
	snd_opl4_रुको(opl4);
	outb(reg, opl4->pcm_port);

	snd_opl4_रुको(opl4);
	outb(value, opl4->pcm_port + 1);
पूर्ण

EXPORT_SYMBOL(snd_opl4_ग_लिखो);

u8 snd_opl4_पढ़ो(काष्ठा snd_opl4 *opl4, u8 reg)
अणु
	snd_opl4_रुको(opl4);
	outb(reg, opl4->pcm_port);

	snd_opl4_रुको(opl4);
	वापस inb(opl4->pcm_port + 1);
पूर्ण

EXPORT_SYMBOL(snd_opl4_पढ़ो);

व्योम snd_opl4_पढ़ो_memory(काष्ठा snd_opl4 *opl4, अक्षर *buf, पूर्णांक offset, पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags;
	u8 memcfg;

	spin_lock_irqsave(&opl4->reg_lock, flags);

	memcfg = snd_opl4_पढ़ो(opl4, OPL4_REG_MEMORY_CONFIGURATION);
	snd_opl4_ग_लिखो(opl4, OPL4_REG_MEMORY_CONFIGURATION, memcfg | OPL4_MODE_BIT);

	snd_opl4_ग_लिखो(opl4, OPL4_REG_MEMORY_ADDRESS_HIGH, offset >> 16);
	snd_opl4_ग_लिखो(opl4, OPL4_REG_MEMORY_ADDRESS_MID, offset >> 8);
	snd_opl4_ग_लिखो(opl4, OPL4_REG_MEMORY_ADDRESS_LOW, offset);

	snd_opl4_रुको(opl4);
	outb(OPL4_REG_MEMORY_DATA, opl4->pcm_port);
	snd_opl4_रुको(opl4);
	insb(opl4->pcm_port + 1, buf, size);

	snd_opl4_ग_लिखो(opl4, OPL4_REG_MEMORY_CONFIGURATION, memcfg);

	spin_unlock_irqrestore(&opl4->reg_lock, flags);
पूर्ण

EXPORT_SYMBOL(snd_opl4_पढ़ो_memory);

व्योम snd_opl4_ग_लिखो_memory(काष्ठा snd_opl4 *opl4, स्थिर अक्षर *buf, पूर्णांक offset, पूर्णांक size)
अणु
	अचिन्हित दीर्घ flags;
	u8 memcfg;

	spin_lock_irqsave(&opl4->reg_lock, flags);

	memcfg = snd_opl4_पढ़ो(opl4, OPL4_REG_MEMORY_CONFIGURATION);
	snd_opl4_ग_लिखो(opl4, OPL4_REG_MEMORY_CONFIGURATION, memcfg | OPL4_MODE_BIT);

	snd_opl4_ग_लिखो(opl4, OPL4_REG_MEMORY_ADDRESS_HIGH, offset >> 16);
	snd_opl4_ग_लिखो(opl4, OPL4_REG_MEMORY_ADDRESS_MID, offset >> 8);
	snd_opl4_ग_लिखो(opl4, OPL4_REG_MEMORY_ADDRESS_LOW, offset);

	snd_opl4_रुको(opl4);
	outb(OPL4_REG_MEMORY_DATA, opl4->pcm_port);
	snd_opl4_रुको(opl4);
	outsb(opl4->pcm_port + 1, buf, size);

	snd_opl4_ग_लिखो(opl4, OPL4_REG_MEMORY_CONFIGURATION, memcfg);

	spin_unlock_irqrestore(&opl4->reg_lock, flags);
पूर्ण

EXPORT_SYMBOL(snd_opl4_ग_लिखो_memory);

अटल व्योम snd_opl4_enable_opl4(काष्ठा snd_opl4 *opl4)
अणु
	outb(OPL3_REG_MODE, opl4->fm_port + 2);
	inb(opl4->fm_port);
	inb(opl4->fm_port);
	outb(OPL3_OPL3_ENABLE | OPL3_OPL4_ENABLE, opl4->fm_port + 3);
	inb(opl4->fm_port);
	inb(opl4->fm_port);
पूर्ण

अटल पूर्णांक snd_opl4_detect(काष्ठा snd_opl4 *opl4)
अणु
	u8 id1, id2;

	snd_opl4_enable_opl4(opl4);

	id1 = snd_opl4_पढ़ो(opl4, OPL4_REG_MEMORY_CONFIGURATION);
	snd_prपूर्णांकdd("OPL4[02]=%02x\n", id1);
	चयन (id1 & OPL4_DEVICE_ID_MASK) अणु
	हाल 0x20:
		opl4->hardware = OPL3_HW_OPL4;
		अवरोध;
	हाल 0x40:
		opl4->hardware = OPL3_HW_OPL4_ML;
		अवरोध;
	शेष:
		वापस -ENODEV;
	पूर्ण

	snd_opl4_ग_लिखो(opl4, OPL4_REG_MIX_CONTROL_FM, 0x00);
	snd_opl4_ग_लिखो(opl4, OPL4_REG_MIX_CONTROL_PCM, 0xff);
	id1 = snd_opl4_पढ़ो(opl4, OPL4_REG_MIX_CONTROL_FM);
	id2 = snd_opl4_पढ़ो(opl4, OPL4_REG_MIX_CONTROL_PCM);
	snd_prपूर्णांकdd("OPL4 id1=%02x id2=%02x\n", id1, id2);
       	अगर (id1 != 0x00 || id2 != 0xff)
		वापस -ENODEV;

	snd_opl4_ग_लिखो(opl4, OPL4_REG_MIX_CONTROL_FM, 0x3f);
	snd_opl4_ग_लिखो(opl4, OPL4_REG_MIX_CONTROL_PCM, 0x3f);
	snd_opl4_ग_लिखो(opl4, OPL4_REG_MEMORY_CONFIGURATION, 0x00);
	वापस 0;
पूर्ण

#अगर IS_ENABLED(CONFIG_SND_SEQUENCER)
अटल व्योम snd_opl4_seq_dev_मुक्त(काष्ठा snd_seq_device *seq_dev)
अणु
	काष्ठा snd_opl4 *opl4 = seq_dev->निजी_data;
	opl4->seq_dev = शून्य;
पूर्ण

अटल पूर्णांक snd_opl4_create_seq_dev(काष्ठा snd_opl4 *opl4, पूर्णांक seq_device)
अणु
	opl4->seq_dev_num = seq_device;
	अगर (snd_seq_device_new(opl4->card, seq_device, SNDRV_SEQ_DEV_ID_OPL4,
			       माप(काष्ठा snd_opl4 *), &opl4->seq_dev) >= 0) अणु
		म_नकल(opl4->seq_dev->name, "OPL4 Wavetable");
		*(काष्ठा snd_opl4 **)SNDRV_SEQ_DEVICE_ARGPTR(opl4->seq_dev) = opl4;
		opl4->seq_dev->निजी_data = opl4;
		opl4->seq_dev->निजी_मुक्त = snd_opl4_seq_dev_मुक्त;
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल व्योम snd_opl4_मुक्त(काष्ठा snd_opl4 *opl4)
अणु
	snd_opl4_मुक्त_proc(opl4);
	release_and_मुक्त_resource(opl4->res_fm_port);
	release_and_मुक्त_resource(opl4->res_pcm_port);
	kमुक्त(opl4);
पूर्ण

अटल पूर्णांक snd_opl4_dev_मुक्त(काष्ठा snd_device *device)
अणु
	काष्ठा snd_opl4 *opl4 = device->device_data;
	snd_opl4_मुक्त(opl4);
	वापस 0;
पूर्ण

पूर्णांक snd_opl4_create(काष्ठा snd_card *card,
		    अचिन्हित दीर्घ fm_port, अचिन्हित दीर्घ pcm_port,
		    पूर्णांक seq_device,
		    काष्ठा snd_opl3 **ropl3, काष्ठा snd_opl4 **ropl4)
अणु
	काष्ठा snd_opl4 *opl4;
	काष्ठा snd_opl3 *opl3;
	पूर्णांक err;
	अटल स्थिर काष्ठा snd_device_ops ops = अणु
		.dev_मुक्त = snd_opl4_dev_मुक्त
	पूर्ण;

	अगर (ropl3)
		*ropl3 = शून्य;
	अगर (ropl4)
		*ropl4 = शून्य;

	opl4 = kzalloc(माप(*opl4), GFP_KERNEL);
	अगर (!opl4)
		वापस -ENOMEM;

	opl4->res_fm_port = request_region(fm_port, 8, "OPL4 FM");
	opl4->res_pcm_port = request_region(pcm_port, 8, "OPL4 PCM/MIX");
	अगर (!opl4->res_fm_port || !opl4->res_pcm_port) अणु
		snd_prपूर्णांकk(KERN_ERR "opl4: can't grab ports 0x%lx, 0x%lx\n", fm_port, pcm_port);
		snd_opl4_मुक्त(opl4);
		वापस -EBUSY;
	पूर्ण

	opl4->card = card;
	opl4->fm_port = fm_port;
	opl4->pcm_port = pcm_port;
	spin_lock_init(&opl4->reg_lock);
	mutex_init(&opl4->access_mutex);

	err = snd_opl4_detect(opl4);
	अगर (err < 0) अणु
		snd_opl4_मुक्त(opl4);
		snd_prपूर्णांकd("OPL4 chip not detected at %#lx/%#lx\n", fm_port, pcm_port);
		वापस err;
	पूर्ण

	err = snd_device_new(card, SNDRV_DEV_CODEC, opl4, &ops);
	अगर (err < 0) अणु
		snd_opl4_मुक्त(opl4);
		वापस err;
	पूर्ण

	err = snd_opl3_create(card, fm_port, fm_port + 2, opl4->hardware, 1, &opl3);
	अगर (err < 0) अणु
		snd_device_मुक्त(card, opl4);
		वापस err;
	पूर्ण

	/* opl3 initialization disabled opl4, so reenable */
	snd_opl4_enable_opl4(opl4);

	snd_opl4_create_mixer(opl4);
	snd_opl4_create_proc(opl4);

#अगर IS_ENABLED(CONFIG_SND_SEQUENCER)
	opl4->seq_client = -1;
	अगर (opl4->hardware < OPL3_HW_OPL4_ML)
		snd_opl4_create_seq_dev(opl4, seq_device);
#पूर्ण_अगर

	अगर (ropl3)
		*ropl3 = opl3;
	अगर (ropl4)
		*ropl4 = opl4;
	वापस 0;
पूर्ण

EXPORT_SYMBOL(snd_opl4_create);
