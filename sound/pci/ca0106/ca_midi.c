<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* 
 *  Copyright 10/16/2005 Tilman Kranz <tilde@tk-sls.de>
 *  Creative Audio MIDI, क्रम the CA0106 Driver
 *  Version: 0.0.1
 *
 *  Changelog:
 *    Implementation is based on mpu401 and emu10k1x and
 *    tested with ca0106.
 *    mpu401: Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *    emu10k1x: Copyright (c) by Francisco Moraes <fmoraes@nc.rr.com>
 */

#समावेश <linux/spinlock.h>
#समावेश <sound/core.h>
#समावेश <sound/rawmidi.h>

#समावेश "ca_midi.h"

#घोषणा ca_midi_ग_लिखो_data(midi, data)	midi->ग_लिखो(midi, data, 0)
#घोषणा ca_midi_ग_लिखो_cmd(midi, data)	midi->ग_लिखो(midi, data, 1)
#घोषणा ca_midi_पढ़ो_data(midi)		midi->पढ़ो(midi, 0)
#घोषणा ca_midi_पढ़ो_stat(midi)		midi->पढ़ो(midi, 1)
#घोषणा ca_midi_input_avail(midi)	(!(ca_midi_पढ़ो_stat(midi) & midi->input_avail))
#घोषणा ca_midi_output_पढ़ोy(midi)	(!(ca_midi_पढ़ो_stat(midi) & midi->output_पढ़ोy))

अटल व्योम ca_midi_clear_rx(काष्ठा snd_ca_midi *midi)
अणु
	पूर्णांक समयout = 100000;
	क्रम (; समयout > 0 && ca_midi_input_avail(midi); समयout--)
		ca_midi_पढ़ो_data(midi);
#अगर_घोषित CONFIG_SND_DEBUG
	अगर (समयout <= 0)
		pr_err("ca_midi_clear_rx: timeout (status = 0x%x)\n",
			   ca_midi_पढ़ो_stat(midi));
#पूर्ण_अगर
पूर्ण

अटल व्योम ca_midi_पूर्णांकerrupt(काष्ठा snd_ca_midi *midi, अचिन्हित पूर्णांक status)
अणु
	अचिन्हित अक्षर byte;

	अगर (midi->rmidi == शून्य) अणु
		midi->पूर्णांकerrupt_disable(midi,midi->tx_enable | midi->rx_enable);
		वापस;
	पूर्ण

	spin_lock(&midi->input_lock);
	अगर ((status & midi->ipr_rx) && ca_midi_input_avail(midi)) अणु
		अगर (!(midi->midi_mode & CA_MIDI_MODE_INPUT)) अणु
			ca_midi_clear_rx(midi);
		पूर्ण अन्यथा अणु
			byte = ca_midi_पढ़ो_data(midi);
			अगर(midi->substream_input)
				snd_rawmidi_receive(midi->substream_input, &byte, 1);


		पूर्ण
	पूर्ण
	spin_unlock(&midi->input_lock);

	spin_lock(&midi->output_lock);
	अगर ((status & midi->ipr_tx) && ca_midi_output_पढ़ोy(midi)) अणु
		अगर (midi->substream_output &&
		    snd_rawmidi_transmit(midi->substream_output, &byte, 1) == 1) अणु
			ca_midi_ग_लिखो_data(midi, byte);
		पूर्ण अन्यथा अणु
			midi->पूर्णांकerrupt_disable(midi,midi->tx_enable);
		पूर्ण
	पूर्ण
	spin_unlock(&midi->output_lock);

पूर्ण

अटल व्योम ca_midi_cmd(काष्ठा snd_ca_midi *midi, अचिन्हित अक्षर cmd, पूर्णांक ack)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक समयout, ok;

	spin_lock_irqsave(&midi->input_lock, flags);
	ca_midi_ग_लिखो_data(midi, 0x00);
	/* ca_midi_clear_rx(midi); */

	ca_midi_ग_लिखो_cmd(midi, cmd);
	अगर (ack) अणु
		ok = 0;
		समयout = 10000;
		जबतक (!ok && समयout-- > 0) अणु
			अगर (ca_midi_input_avail(midi)) अणु
				अगर (ca_midi_पढ़ो_data(midi) == midi->ack)
					ok = 1;
			पूर्ण
		पूर्ण
		अगर (!ok && ca_midi_पढ़ो_data(midi) == midi->ack)
			ok = 1;
	पूर्ण अन्यथा अणु
		ok = 1;
	पूर्ण
	spin_unlock_irqrestore(&midi->input_lock, flags);
	अगर (!ok)
		pr_err("ca_midi_cmd: 0x%x failed at 0x%x (status = 0x%x, data = 0x%x)!!!\n",
			   cmd,
			   midi->get_dev_id_port(midi->dev_id),
			   ca_midi_पढ़ो_stat(midi),
			   ca_midi_पढ़ो_data(midi));
पूर्ण

अटल पूर्णांक ca_midi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_ca_midi *midi = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;
	
	अगर (snd_BUG_ON(!midi->dev_id))
		वापस -ENXIO;
	spin_lock_irqsave(&midi->खोलो_lock, flags);
	midi->midi_mode |= CA_MIDI_MODE_INPUT;
	midi->substream_input = substream;
	अगर (!(midi->midi_mode & CA_MIDI_MODE_OUTPUT)) अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
		ca_midi_cmd(midi, midi->reset, 1);
		ca_midi_cmd(midi, midi->enter_uart, 1);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ca_midi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_ca_midi *midi = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!midi->dev_id))
		वापस -ENXIO;
	spin_lock_irqsave(&midi->खोलो_lock, flags);
	midi->midi_mode |= CA_MIDI_MODE_OUTPUT;
	midi->substream_output = substream;
	अगर (!(midi->midi_mode & CA_MIDI_MODE_INPUT)) अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
		ca_midi_cmd(midi, midi->reset, 1);
		ca_midi_cmd(midi, midi->enter_uart, 1);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ca_midi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_ca_midi *midi = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!midi->dev_id))
		वापस -ENXIO;
	spin_lock_irqsave(&midi->खोलो_lock, flags);
	midi->पूर्णांकerrupt_disable(midi,midi->rx_enable);
	midi->midi_mode &= ~CA_MIDI_MODE_INPUT;
	midi->substream_input = शून्य;
	अगर (!(midi->midi_mode & CA_MIDI_MODE_OUTPUT)) अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
		ca_midi_cmd(midi, midi->reset, 0);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक ca_midi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_ca_midi *midi = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!midi->dev_id))
		वापस -ENXIO;
	
	spin_lock_irqsave(&midi->खोलो_lock, flags);

	midi->पूर्णांकerrupt_disable(midi,midi->tx_enable);
	midi->midi_mode &= ~CA_MIDI_MODE_OUTPUT;
	midi->substream_output = शून्य;
	
	अगर (!(midi->midi_mode & CA_MIDI_MODE_INPUT)) अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
		ca_midi_cmd(midi, midi->reset, 0);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम ca_midi_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा snd_ca_midi *midi = substream->rmidi->निजी_data;

	अगर (snd_BUG_ON(!midi->dev_id))
		वापस;

	अगर (up) अणु
		midi->पूर्णांकerrupt_enable(midi,midi->rx_enable);
	पूर्ण अन्यथा अणु
		midi->पूर्णांकerrupt_disable(midi, midi->rx_enable);
	पूर्ण
पूर्ण

अटल व्योम ca_midi_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा snd_ca_midi *midi = substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	अगर (snd_BUG_ON(!midi->dev_id))
		वापस;

	अगर (up) अणु
		पूर्णांक max = 4;
		अचिन्हित अक्षर byte;

		spin_lock_irqsave(&midi->output_lock, flags);
	
		/* try to send some amount of bytes here beक्रमe पूर्णांकerrupts */
		जबतक (max > 0) अणु
			अगर (ca_midi_output_पढ़ोy(midi)) अणु
				अगर (!(midi->midi_mode & CA_MIDI_MODE_OUTPUT) ||
				    snd_rawmidi_transmit(substream, &byte, 1) != 1) अणु
					/* no more data */
					spin_unlock_irqrestore(&midi->output_lock, flags);
					वापस;
				पूर्ण
				ca_midi_ग_लिखो_data(midi, byte);
				max--;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण

		spin_unlock_irqrestore(&midi->output_lock, flags);
		midi->पूर्णांकerrupt_enable(midi,midi->tx_enable);

	पूर्ण अन्यथा अणु
		midi->पूर्णांकerrupt_disable(midi,midi->tx_enable);
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops ca_midi_output =
अणु
	.खोलो =		ca_midi_output_खोलो,
	.बंद =	ca_midi_output_बंद,
	.trigger =	ca_midi_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops ca_midi_input =
अणु
	.खोलो =		ca_midi_input_खोलो,
	.बंद =	ca_midi_input_बंद,
	.trigger =	ca_midi_input_trigger,
पूर्ण;

अटल व्योम ca_midi_मुक्त(काष्ठा snd_ca_midi *midi)
अणु
	midi->पूर्णांकerrupt = शून्य;
	midi->पूर्णांकerrupt_enable = शून्य;
	midi->पूर्णांकerrupt_disable = शून्य;
	midi->पढ़ो = शून्य;
	midi->ग_लिखो = शून्य;
	midi->get_dev_id_card = शून्य;
	midi->get_dev_id_port = शून्य;
	midi->rmidi = शून्य;
पूर्ण

अटल व्योम ca_rmidi_मुक्त(काष्ठा snd_rawmidi *rmidi)
अणु
	ca_midi_मुक्त(rmidi->निजी_data);
पूर्ण

पूर्णांक ca_midi_init(व्योम *dev_id, काष्ठा snd_ca_midi *midi, पूर्णांक device, अक्षर *name)
अणु
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक err;

	अगर ((err = snd_rawmidi_new(midi->get_dev_id_card(midi->dev_id), name, device, 1, 1, &rmidi)) < 0)
		वापस err;

	midi->dev_id = dev_id;
	midi->पूर्णांकerrupt = ca_midi_पूर्णांकerrupt;

	spin_lock_init(&midi->खोलो_lock);
	spin_lock_init(&midi->input_lock);
	spin_lock_init(&midi->output_lock);

	म_नकल(rmidi->name, name);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &ca_midi_output);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &ca_midi_input);
	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT |
	                     SNDRV_RAWMIDI_INFO_INPUT |
	                     SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->निजी_data = midi;
	rmidi->निजी_मुक्त = ca_rmidi_मुक्त;
	
	midi->rmidi = rmidi;
	वापस 0;
पूर्ण

