<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Copyright (c) 2009 by Krzysztof Helt
 *  Routines क्रम control of MPU-401 in UART mode
 *
 *  MPU-401 supports UART mode which is not capable generate transmit
 *  पूर्णांकerrupts thus output is करोne via polling. Also, अगर irq < 0, then
 *  input is करोne also via polling. Do not expect good perक्रमmance.
 */

#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/ioport.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/export.h>
#समावेश <sound/core.h>
#समावेश <sound/rawmidi.h>

#समावेश "msnd.h"

#घोषणा MSNDMIDI_MODE_BIT_INPUT		0
#घोषणा MSNDMIDI_MODE_BIT_OUTPUT		1
#घोषणा MSNDMIDI_MODE_BIT_INPUT_TRIGGER	2
#घोषणा MSNDMIDI_MODE_BIT_OUTPUT_TRIGGER	3

काष्ठा snd_msndmidi अणु
	काष्ठा snd_msnd *dev;

	अचिन्हित दीर्घ mode;		/* MSNDMIDI_MODE_XXXX */

	काष्ठा snd_rawmidi_substream *substream_input;

	spinlock_t input_lock;
पूर्ण;

/*
 * input/output खोलो/बंद - रक्षित by खोलो_mutex in rawmidi.c
 */
अटल पूर्णांक snd_msndmidi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_msndmidi *mpu;

	snd_prपूर्णांकdd("snd_msndmidi_input_open()\n");

	mpu = substream->rmidi->निजी_data;

	mpu->substream_input = substream;

	snd_msnd_enable_irq(mpu->dev);

	snd_msnd_send_dsp_cmd(mpu->dev, HDEX_MIDI_IN_START);
	set_bit(MSNDMIDI_MODE_BIT_INPUT, &mpu->mode);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_msndmidi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_msndmidi *mpu;

	mpu = substream->rmidi->निजी_data;
	snd_msnd_send_dsp_cmd(mpu->dev, HDEX_MIDI_IN_STOP);
	clear_bit(MSNDMIDI_MODE_BIT_INPUT, &mpu->mode);
	mpu->substream_input = शून्य;
	snd_msnd_disable_irq(mpu->dev);
	वापस 0;
पूर्ण

अटल व्योम snd_msndmidi_input_drop(काष्ठा snd_msndmidi *mpu)
अणु
	u16 tail;

	tail = पढ़ोw(mpu->dev->MIDQ + JQS_wTail);
	ग_लिखोw(tail, mpu->dev->MIDQ + JQS_wHead);
पूर्ण

/*
 * trigger input
 */
अटल व्योम snd_msndmidi_input_trigger(काष्ठा snd_rawmidi_substream *substream,
					पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_msndmidi *mpu;

	snd_prपूर्णांकdd("snd_msndmidi_input_trigger(, %i)\n", up);

	mpu = substream->rmidi->निजी_data;
	spin_lock_irqsave(&mpu->input_lock, flags);
	अगर (up) अणु
		अगर (!test_and_set_bit(MSNDMIDI_MODE_BIT_INPUT_TRIGGER,
				      &mpu->mode))
			snd_msndmidi_input_drop(mpu);
	पूर्ण अन्यथा अणु
		clear_bit(MSNDMIDI_MODE_BIT_INPUT_TRIGGER, &mpu->mode);
	पूर्ण
	spin_unlock_irqrestore(&mpu->input_lock, flags);
	अगर (up)
		snd_msndmidi_input_पढ़ो(mpu);
पूर्ण

व्योम snd_msndmidi_input_पढ़ो(व्योम *mpuv)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_msndmidi *mpu = mpuv;
	व्योम __iomem *pwMIDQData = mpu->dev->mappedbase + MIDQ_DATA_BUFF;
	u16 head, tail, size;

	spin_lock_irqsave(&mpu->input_lock, flags);
	head = पढ़ोw(mpu->dev->MIDQ + JQS_wHead);
	tail = पढ़ोw(mpu->dev->MIDQ + JQS_wTail);
	size = पढ़ोw(mpu->dev->MIDQ + JQS_wSize);
	अगर (head > size || tail > size)
		जाओ out;
	जबतक (head != tail) अणु
		अचिन्हित अक्षर val = पढ़ोw(pwMIDQData + 2 * head);

		अगर (test_bit(MSNDMIDI_MODE_BIT_INPUT_TRIGGER, &mpu->mode))
			snd_rawmidi_receive(mpu->substream_input, &val, 1);
		अगर (++head > size)
			head = 0;
		ग_लिखोw(head, mpu->dev->MIDQ + JQS_wHead);
	पूर्ण
 out:
	spin_unlock_irqrestore(&mpu->input_lock, flags);
पूर्ण
EXPORT_SYMBOL(snd_msndmidi_input_पढ़ो);

अटल स्थिर काष्ठा snd_rawmidi_ops snd_msndmidi_input = अणु
	.खोलो =		snd_msndmidi_input_खोलो,
	.बंद =	snd_msndmidi_input_बंद,
	.trigger =	snd_msndmidi_input_trigger,
पूर्ण;

अटल व्योम snd_msndmidi_मुक्त(काष्ठा snd_rawmidi *rmidi)
अणु
	काष्ठा snd_msndmidi *mpu = rmidi->निजी_data;
	kमुक्त(mpu);
पूर्ण

पूर्णांक snd_msndmidi_new(काष्ठा snd_card *card, पूर्णांक device)
अणु
	काष्ठा snd_msnd *chip = card->निजी_data;
	काष्ठा snd_msndmidi *mpu;
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक err;

	err = snd_rawmidi_new(card, "MSND-MIDI", device, 1, 1, &rmidi);
	अगर (err < 0)
		वापस err;
	mpu = kzalloc(माप(*mpu), GFP_KERNEL);
	अगर (mpu == शून्य) अणु
		snd_device_मुक्त(card, rmidi);
		वापस -ENOMEM;
	पूर्ण
	mpu->dev = chip;
	chip->msndmidi_mpu = mpu;
	rmidi->निजी_data = mpu;
	rmidi->निजी_मुक्त = snd_msndmidi_मुक्त;
	spin_lock_init(&mpu->input_lock);
	म_नकल(rmidi->name, "MSND MIDI");
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
			    &snd_msndmidi_input);
	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_INPUT;
	वापस 0;
पूर्ण
