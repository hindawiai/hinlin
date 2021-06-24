<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Routines क्रम control of EMU10K1 MPU-401 in UART mode
 */

#समावेश <linux/समय.स>
#समावेश <linux/init.h>
#समावेश <sound/core.h>
#समावेश <sound/emu10k1.h>

#घोषणा EMU10K1_MIDI_MODE_INPUT		(1<<0)
#घोषणा EMU10K1_MIDI_MODE_OUTPUT	(1<<1)

अटल अंतरभूत अचिन्हित अक्षर mpu401_पढ़ो(काष्ठा snd_emu10k1 *emu,
					काष्ठा snd_emu10k1_midi *mpu, पूर्णांक idx)
अणु
	अगर (emu->audigy)
		वापस (अचिन्हित अक्षर)snd_emu10k1_ptr_पढ़ो(emu, mpu->port + idx, 0);
	अन्यथा
		वापस inb(emu->port + mpu->port + idx);
पूर्ण

अटल अंतरभूत व्योम mpu401_ग_लिखो(काष्ठा snd_emu10k1 *emu,
				काष्ठा snd_emu10k1_midi *mpu, पूर्णांक data, पूर्णांक idx)
अणु
	अगर (emu->audigy)
		snd_emu10k1_ptr_ग_लिखो(emu, mpu->port + idx, 0, data);
	अन्यथा
		outb(data, emu->port + mpu->port + idx);
पूर्ण

#घोषणा mpu401_ग_लिखो_data(emu, mpu, data)	mpu401_ग_लिखो(emu, mpu, data, 0)
#घोषणा mpu401_ग_लिखो_cmd(emu, mpu, data)	mpu401_ग_लिखो(emu, mpu, data, 1)
#घोषणा mpu401_पढ़ो_data(emu, mpu)		mpu401_पढ़ो(emu, mpu, 0)
#घोषणा mpu401_पढ़ो_stat(emu, mpu)		mpu401_पढ़ो(emu, mpu, 1)

#घोषणा mpu401_input_avail(emu,mpu)	(!(mpu401_पढ़ो_stat(emu,mpu) & 0x80))
#घोषणा mpu401_output_पढ़ोy(emu,mpu)	(!(mpu401_पढ़ो_stat(emu,mpu) & 0x40))

#घोषणा MPU401_RESET		0xff
#घोषणा MPU401_ENTER_UART	0x3f
#घोषणा MPU401_ACK		0xfe

अटल व्योम mpu401_clear_rx(काष्ठा snd_emu10k1 *emu, काष्ठा snd_emu10k1_midi *mpu)
अणु
	पूर्णांक समयout = 100000;
	क्रम (; समयout > 0 && mpu401_input_avail(emu, mpu); समयout--)
		mpu401_पढ़ो_data(emu, mpu);
#अगर_घोषित CONFIG_SND_DEBUG
	अगर (समयout <= 0)
		dev_err(emu->card->dev,
			"cmd: clear rx timeout (status = 0x%x)\n",
			mpu401_पढ़ो_stat(emu, mpu));
#पूर्ण_अगर
पूर्ण

/*

 */

अटल व्योम करो_emu10k1_midi_पूर्णांकerrupt(काष्ठा snd_emu10k1 *emu, काष्ठा snd_emu10k1_midi *midi, अचिन्हित पूर्णांक status)
अणु
	अचिन्हित अक्षर byte;

	अगर (midi->rmidi == शून्य) अणु
		snd_emu10k1_पूर्णांकr_disable(emu, midi->tx_enable | midi->rx_enable);
		वापस;
	पूर्ण

	spin_lock(&midi->input_lock);
	अगर ((status & midi->ipr_rx) && mpu401_input_avail(emu, midi)) अणु
		अगर (!(midi->midi_mode & EMU10K1_MIDI_MODE_INPUT)) अणु
			mpu401_clear_rx(emu, midi);
		पूर्ण अन्यथा अणु
			byte = mpu401_पढ़ो_data(emu, midi);
			अगर (midi->substream_input)
				snd_rawmidi_receive(midi->substream_input, &byte, 1);
		पूर्ण
	पूर्ण
	spin_unlock(&midi->input_lock);

	spin_lock(&midi->output_lock);
	अगर ((status & midi->ipr_tx) && mpu401_output_पढ़ोy(emu, midi)) अणु
		अगर (midi->substream_output &&
		    snd_rawmidi_transmit(midi->substream_output, &byte, 1) == 1) अणु
			mpu401_ग_लिखो_data(emu, midi, byte);
		पूर्ण अन्यथा अणु
			snd_emu10k1_पूर्णांकr_disable(emu, midi->tx_enable);
		पूर्ण
	पूर्ण
	spin_unlock(&midi->output_lock);
पूर्ण

अटल व्योम snd_emu10k1_midi_पूर्णांकerrupt(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक status)
अणु
	करो_emu10k1_midi_पूर्णांकerrupt(emu, &emu->midi, status);
पूर्ण

अटल व्योम snd_emu10k1_midi_पूर्णांकerrupt2(काष्ठा snd_emu10k1 *emu, अचिन्हित पूर्णांक status)
अणु
	करो_emu10k1_midi_पूर्णांकerrupt(emu, &emu->midi2, status);
पूर्ण

अटल पूर्णांक snd_emu10k1_midi_cmd(काष्ठा snd_emu10k1 * emu, काष्ठा snd_emu10k1_midi *midi, अचिन्हित अक्षर cmd, पूर्णांक ack)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक समयout, ok;

	spin_lock_irqsave(&midi->input_lock, flags);
	mpu401_ग_लिखो_data(emu, midi, 0x00);
	/* mpu401_clear_rx(emu, midi); */

	mpu401_ग_लिखो_cmd(emu, midi, cmd);
	अगर (ack) अणु
		ok = 0;
		समयout = 10000;
		जबतक (!ok && समयout-- > 0) अणु
			अगर (mpu401_input_avail(emu, midi)) अणु
				अगर (mpu401_पढ़ो_data(emu, midi) == MPU401_ACK)
					ok = 1;
			पूर्ण
		पूर्ण
		अगर (!ok && mpu401_पढ़ो_data(emu, midi) == MPU401_ACK)
			ok = 1;
	पूर्ण अन्यथा अणु
		ok = 1;
	पूर्ण
	spin_unlock_irqrestore(&midi->input_lock, flags);
	अगर (!ok) अणु
		dev_err(emu->card->dev,
			"midi_cmd: 0x%x failed at 0x%lx (status = 0x%x, data = 0x%x)!!!\n",
			   cmd, emu->port,
			   mpu401_पढ़ो_stat(emu, midi),
			   mpu401_पढ़ो_data(emu, midi));
		वापस 1;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_emu10k1_midi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu;
	काष्ठा snd_emu10k1_midi *midi = (काष्ठा snd_emu10k1_midi *)substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	emu = midi->emu;
	अगर (snd_BUG_ON(!emu))
		वापस -ENXIO;
	spin_lock_irqsave(&midi->खोलो_lock, flags);
	midi->midi_mode |= EMU10K1_MIDI_MODE_INPUT;
	midi->substream_input = substream;
	अगर (!(midi->midi_mode & EMU10K1_MIDI_MODE_OUTPUT)) अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
		अगर (snd_emu10k1_midi_cmd(emu, midi, MPU401_RESET, 1))
			जाओ error_out;
		अगर (snd_emu10k1_midi_cmd(emu, midi, MPU401_ENTER_UART, 1))
			जाओ error_out;
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
	पूर्ण
	वापस 0;

error_out:
	वापस -EIO;
पूर्ण

अटल पूर्णांक snd_emu10k1_midi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu;
	काष्ठा snd_emu10k1_midi *midi = (काष्ठा snd_emu10k1_midi *)substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	emu = midi->emu;
	अगर (snd_BUG_ON(!emu))
		वापस -ENXIO;
	spin_lock_irqsave(&midi->खोलो_lock, flags);
	midi->midi_mode |= EMU10K1_MIDI_MODE_OUTPUT;
	midi->substream_output = substream;
	अगर (!(midi->midi_mode & EMU10K1_MIDI_MODE_INPUT)) अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
		अगर (snd_emu10k1_midi_cmd(emu, midi, MPU401_RESET, 1))
			जाओ error_out;
		अगर (snd_emu10k1_midi_cmd(emu, midi, MPU401_ENTER_UART, 1))
			जाओ error_out;
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
	पूर्ण
	वापस 0;

error_out:
	वापस -EIO;
पूर्ण

अटल पूर्णांक snd_emu10k1_midi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu;
	काष्ठा snd_emu10k1_midi *midi = (काष्ठा snd_emu10k1_midi *)substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	emu = midi->emu;
	अगर (snd_BUG_ON(!emu))
		वापस -ENXIO;
	spin_lock_irqsave(&midi->खोलो_lock, flags);
	snd_emu10k1_पूर्णांकr_disable(emu, midi->rx_enable);
	midi->midi_mode &= ~EMU10K1_MIDI_MODE_INPUT;
	midi->substream_input = शून्य;
	अगर (!(midi->midi_mode & EMU10K1_MIDI_MODE_OUTPUT)) अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
		err = snd_emu10k1_midi_cmd(emu, midi, MPU401_RESET, 0);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक snd_emu10k1_midi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा snd_emu10k1 *emu;
	काष्ठा snd_emu10k1_midi *midi = (काष्ठा snd_emu10k1_midi *)substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	emu = midi->emu;
	अगर (snd_BUG_ON(!emu))
		वापस -ENXIO;
	spin_lock_irqsave(&midi->खोलो_lock, flags);
	snd_emu10k1_पूर्णांकr_disable(emu, midi->tx_enable);
	midi->midi_mode &= ~EMU10K1_MIDI_MODE_OUTPUT;
	midi->substream_output = शून्य;
	अगर (!(midi->midi_mode & EMU10K1_MIDI_MODE_INPUT)) अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
		err = snd_emu10k1_midi_cmd(emu, midi, MPU401_RESET, 0);
	पूर्ण अन्यथा अणु
		spin_unlock_irqrestore(&midi->खोलो_lock, flags);
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम snd_emu10k1_midi_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा snd_emu10k1 *emu;
	काष्ठा snd_emu10k1_midi *midi = (काष्ठा snd_emu10k1_midi *)substream->rmidi->निजी_data;
	emu = midi->emu;
	अगर (snd_BUG_ON(!emu))
		वापस;

	अगर (up)
		snd_emu10k1_पूर्णांकr_enable(emu, midi->rx_enable);
	अन्यथा
		snd_emu10k1_पूर्णांकr_disable(emu, midi->rx_enable);
पूर्ण

अटल व्योम snd_emu10k1_midi_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा snd_emu10k1 *emu;
	काष्ठा snd_emu10k1_midi *midi = (काष्ठा snd_emu10k1_midi *)substream->rmidi->निजी_data;
	अचिन्हित दीर्घ flags;

	emu = midi->emu;
	अगर (snd_BUG_ON(!emu))
		वापस;

	अगर (up) अणु
		पूर्णांक max = 4;
		अचिन्हित अक्षर byte;
	
		/* try to send some amount of bytes here beक्रमe पूर्णांकerrupts */
		spin_lock_irqsave(&midi->output_lock, flags);
		जबतक (max > 0) अणु
			अगर (mpu401_output_पढ़ोy(emu, midi)) अणु
				अगर (!(midi->midi_mode & EMU10K1_MIDI_MODE_OUTPUT) ||
				    snd_rawmidi_transmit(substream, &byte, 1) != 1) अणु
					/* no more data */
					spin_unlock_irqrestore(&midi->output_lock, flags);
					वापस;
				पूर्ण
				mpu401_ग_लिखो_data(emu, midi, byte);
				max--;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&midi->output_lock, flags);
		snd_emu10k1_पूर्णांकr_enable(emu, midi->tx_enable);
	पूर्ण अन्यथा अणु
		snd_emu10k1_पूर्णांकr_disable(emu, midi->tx_enable);
	पूर्ण
पूर्ण

/*

 */

अटल स्थिर काष्ठा snd_rawmidi_ops snd_emu10k1_midi_output =
अणु
	.खोलो =		snd_emu10k1_midi_output_खोलो,
	.बंद =	snd_emu10k1_midi_output_बंद,
	.trigger =	snd_emu10k1_midi_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_emu10k1_midi_input =
अणु
	.खोलो =		snd_emu10k1_midi_input_खोलो,
	.बंद =	snd_emu10k1_midi_input_बंद,
	.trigger =	snd_emu10k1_midi_input_trigger,
पूर्ण;

अटल व्योम snd_emu10k1_midi_मुक्त(काष्ठा snd_rawmidi *rmidi)
अणु
	काष्ठा snd_emu10k1_midi *midi = rmidi->निजी_data;
	midi->पूर्णांकerrupt = शून्य;
	midi->rmidi = शून्य;
पूर्ण

अटल पूर्णांक emu10k1_midi_init(काष्ठा snd_emu10k1 *emu, काष्ठा snd_emu10k1_midi *midi, पूर्णांक device, अक्षर *name)
अणु
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक err;

	अगर ((err = snd_rawmidi_new(emu->card, name, device, 1, 1, &rmidi)) < 0)
		वापस err;
	midi->emu = emu;
	spin_lock_init(&midi->खोलो_lock);
	spin_lock_init(&midi->input_lock);
	spin_lock_init(&midi->output_lock);
	म_नकल(rmidi->name, name);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &snd_emu10k1_midi_output);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &snd_emu10k1_midi_input);
	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT |
	                     SNDRV_RAWMIDI_INFO_INPUT |
	                     SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->निजी_data = midi;
	rmidi->निजी_मुक्त = snd_emu10k1_midi_मुक्त;
	midi->rmidi = rmidi;
	वापस 0;
पूर्ण

पूर्णांक snd_emu10k1_midi(काष्ठा snd_emu10k1 *emu)
अणु
	काष्ठा snd_emu10k1_midi *midi = &emu->midi;
	पूर्णांक err;

	अगर ((err = emu10k1_midi_init(emu, midi, 0, "EMU10K1 MPU-401 (UART)")) < 0)
		वापस err;

	midi->tx_enable = INTE_MIDITXENABLE;
	midi->rx_enable = INTE_MIसूचीXENABLE;
	midi->port = MUDATA;
	midi->ipr_tx = IPR_MIDITRANSBUFEMPTY;
	midi->ipr_rx = IPR_MIसूचीECVBUFEMPTY;
	midi->पूर्णांकerrupt = snd_emu10k1_midi_पूर्णांकerrupt;
	वापस 0;
पूर्ण

पूर्णांक snd_emu10k1_audigy_midi(काष्ठा snd_emu10k1 *emu)
अणु
	काष्ठा snd_emu10k1_midi *midi;
	पूर्णांक err;

	midi = &emu->midi;
	अगर ((err = emu10k1_midi_init(emu, midi, 0, "Audigy MPU-401 (UART)")) < 0)
		वापस err;

	midi->tx_enable = INTE_MIDITXENABLE;
	midi->rx_enable = INTE_MIसूचीXENABLE;
	midi->port = A_MUDATA1;
	midi->ipr_tx = IPR_MIDITRANSBUFEMPTY;
	midi->ipr_rx = IPR_MIसूचीECVBUFEMPTY;
	midi->पूर्णांकerrupt = snd_emu10k1_midi_पूर्णांकerrupt;

	midi = &emu->midi2;
	अगर ((err = emu10k1_midi_init(emu, midi, 1, "Audigy MPU-401 #2")) < 0)
		वापस err;

	midi->tx_enable = INTE_A_MIDITXENABLE2;
	midi->rx_enable = INTE_A_MIसूचीXENABLE2;
	midi->port = A_MUDATA2;
	midi->ipr_tx = IPR_A_MIDITRANSBUFEMPTY2;
	midi->ipr_rx = IPR_A_MIसूचीECVBUFEMPTY2;
	midi->पूर्णांकerrupt = snd_emu10k1_midi_पूर्णांकerrupt2;
	वापस 0;
पूर्ण
