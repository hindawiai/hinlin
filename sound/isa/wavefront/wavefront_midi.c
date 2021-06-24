<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) by Paul Barton-Davis 1998-1999
 */

/* The low level driver क्रम the WaveFront ICS2115 MIDI पूर्णांकerface(s)
 *
 * Note that there is also an MPU-401 emulation (actually, a UART-401
 * emulation) on the CS4232 on the Tropez and Tropez Plus. This code
 * has nothing to करो with that पूर्णांकerface at all.
 *
 * The पूर्णांकerface is essentially just a UART-401, but is has the
 * पूर्णांकeresting property of supporting what Turtle Beach called
 * "Virtual MIDI" mode. In this mode, there are effectively *two*
 * MIDI buses accessible via the पूर्णांकerface, one that is routed
 * solely to/from the बाह्यal WaveFront synthesizer and the other
 * corresponding to the pin/socket connector used to link बाह्यal
 * MIDI devices to the board.
 *
 * This driver fully supports this mode, allowing two distinct MIDI
 * busses to be used completely independently, giving 32 channels of
 * MIDI routing, 16 to the WaveFront synth and 16 to the बाह्यal MIDI
 * bus. The devices are named /dev/snd/midiCnD0 and /dev/snd/midiCnD1,
 * where `n' is the card number. Note that the device numbers may be
 * something other than 0 and 1 अगर the CS4232 UART/MPU-401 पूर्णांकerface
 * is enabled.
 *
 * Switching between the two is accomplished बाह्यally by the driver
 * using the two otherwise unused MIDI bytes. See the code क्रम more details.
 *
 * NOTE: VIRTUAL MIDI MODE IS ON BY DEFAULT (see lowlevel/isa/wavefront.c)
 *
 * The मुख्य reason to turn off Virtual MIDI mode is when you want to
 * tightly couple the WaveFront synth with an बाह्यal MIDI
 * device. You won't be able to distinguish the source of any MIDI
 * data except via SysEx ID, but thats probably OK, since क्रम the most
 * part, the WaveFront won't be sending any MIDI data at all.
 *  
 * The मुख्य reason to turn on Virtual MIDI Mode is to provide two
 * completely independent 16-channel MIDI buses, one to the
 * WaveFront and one to any बाह्यal MIDI devices. Given the 32
 * voice nature of the WaveFront, its pretty easy to find a use
 * क्रम all 16 channels driving just that synth.
 *  
 */

#समावेश <linux/पन.स>
#समावेश <linux/init.h>
#समावेश <linux/समय.स>
#समावेश <linux/रुको.h>
#समावेश <sound/core.h>
#समावेश <sound/snd_wavefront.h>

अटल अंतरभूत पूर्णांक 
wf_mpu_status (snd_wavefront_midi_t *midi)

अणु
	वापस inb (midi->mpu_status_port);
पूर्ण

अटल अंतरभूत पूर्णांक 
input_avail (snd_wavefront_midi_t *midi)

अणु
	वापस !(wf_mpu_status(midi) & INPUT_AVAIL);
पूर्ण

अटल अंतरभूत पूर्णांक
output_पढ़ोy (snd_wavefront_midi_t *midi)

अणु
	वापस !(wf_mpu_status(midi) & OUTPUT_READY);
पूर्ण

अटल अंतरभूत पूर्णांक 
पढ़ो_data (snd_wavefront_midi_t *midi)

अणु
	वापस inb (midi->mpu_data_port);
पूर्ण

अटल अंतरभूत व्योम 
ग_लिखो_data (snd_wavefront_midi_t *midi, अचिन्हित अक्षर byte)

अणु
	outb (byte, midi->mpu_data_port);
पूर्ण

अटल snd_wavefront_midi_t *
get_wavefront_midi (काष्ठा snd_rawmidi_substream *substream)

अणु
	काष्ठा snd_card *card;
	snd_wavefront_card_t *acard;

	अगर (substream == शून्य || substream->rmidi == शून्य) 
	        वापस शून्य;

	card = substream->rmidi->card;

	अगर (card == शून्य) 
	        वापस शून्य;

	अगर (card->निजी_data == शून्य) 
 	        वापस शून्य;

	acard = card->निजी_data;

	वापस &acard->wavefront.midi;
पूर्ण

अटल व्योम snd_wavefront_midi_output_ग_लिखो(snd_wavefront_card_t *card)
अणु
	snd_wavefront_midi_t *midi = &card->wavefront.midi;
	snd_wavefront_mpu_id  mpu;
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर midi_byte;
	पूर्णांक max = 256, mask = 1;
	पूर्णांक समयout;

	/* Its not OK to try to change the status of "virtuality" of
	   the MIDI पूर्णांकerface जबतक we're outputting stuff.  See
	   snd_wavefront_midi_अणुenable,disableपूर्ण_भव () क्रम the
	   other half of this.  

	   The first loop attempts to flush any data from the
	   current output device, and then the second 
	   emits the चयन byte (अगर necessary), and starts
	   outputting data क्रम the output device currently in use.
	*/

	अगर (midi->substream_output[midi->output_mpu] == शून्य) अणु
		जाओ __second;
	पूर्ण

	जबतक (max > 0) अणु

		/* XXX fix me - no hard timing loops allowed! */

		क्रम (समयout = 30000; समयout > 0; समयout--) अणु
			अगर (output_पढ़ोy (midi))
				अवरोध;
		पूर्ण
	
		spin_lock_irqsave (&midi->भव, flags);
		अगर ((midi->mode[midi->output_mpu] & MPU401_MODE_OUTPUT) == 0) अणु
			spin_unlock_irqrestore (&midi->भव, flags);
			जाओ __second;
		पूर्ण
		अगर (output_पढ़ोy (midi)) अणु
			अगर (snd_rawmidi_transmit(midi->substream_output[midi->output_mpu], &midi_byte, 1) == 1) अणु
				अगर (!midi->isभव ||
					(midi_byte != WF_INTERNAL_SWITCH &&
					 midi_byte != WF_EXTERNAL_SWITCH))
					ग_लिखो_data(midi, midi_byte);
				max--;
			पूर्ण अन्यथा अणु
				अगर (midi->isसमयr) अणु
					अगर (--midi->isसमयr <= 0)
						del_समयr(&midi->समयr);
				पूर्ण
				midi->mode[midi->output_mpu] &= ~MPU401_MODE_OUTPUT_TRIGGER;
				spin_unlock_irqrestore (&midi->भव, flags);
				जाओ __second;
			पूर्ण
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore (&midi->भव, flags);
			वापस;
		पूर्ण
		spin_unlock_irqrestore (&midi->भव, flags);
	पूर्ण

      __second:

	अगर (midi->substream_output[!midi->output_mpu] == शून्य) अणु
		वापस;
	पूर्ण

	जबतक (max > 0) अणु

		/* XXX fix me - no hard timing loops allowed! */

		क्रम (समयout = 30000; समयout > 0; समयout--) अणु
			अगर (output_पढ़ोy (midi))
				अवरोध;
		पूर्ण
	
		spin_lock_irqsave (&midi->भव, flags);
		अगर (!midi->isभव)
			mask = 0;
		mpu = midi->output_mpu ^ mask;
		mask = 0;	/* करोn't invert the value from now */
		अगर ((midi->mode[mpu] & MPU401_MODE_OUTPUT) == 0) अणु
			spin_unlock_irqrestore (&midi->भव, flags);
			वापस;
		पूर्ण
		अगर (snd_rawmidi_transmit_empty(midi->substream_output[mpu]))
			जाओ __समयr;
		अगर (output_पढ़ोy (midi)) अणु
			अगर (mpu != midi->output_mpu) अणु
				ग_लिखो_data(midi, mpu == पूर्णांकernal_mpu ?
							WF_INTERNAL_SWITCH :
							WF_EXTERNAL_SWITCH);
				midi->output_mpu = mpu;
			पूर्ण अन्यथा अगर (snd_rawmidi_transmit(midi->substream_output[mpu], &midi_byte, 1) == 1) अणु
				अगर (!midi->isभव ||
					(midi_byte != WF_INTERNAL_SWITCH &&
					 midi_byte != WF_EXTERNAL_SWITCH))
					ग_लिखो_data(midi, midi_byte);
				max--;
			पूर्ण अन्यथा अणु
			      __समयr:
				अगर (midi->isसमयr) अणु
					अगर (--midi->isसमयr <= 0)
						del_समयr(&midi->समयr);
				पूर्ण
				midi->mode[mpu] &= ~MPU401_MODE_OUTPUT_TRIGGER;
				spin_unlock_irqrestore (&midi->भव, flags);
				वापस;
			पूर्ण
		पूर्ण अन्यथा अणु
			spin_unlock_irqrestore (&midi->भव, flags);
			वापस;
		पूर्ण
		spin_unlock_irqrestore (&midi->भव, flags);
	पूर्ण
पूर्ण

अटल पूर्णांक snd_wavefront_midi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	snd_wavefront_midi_t *midi;
	snd_wavefront_mpu_id mpu;

	अगर (snd_BUG_ON(!substream || !substream->rmidi))
		वापस -ENXIO;
	अगर (snd_BUG_ON(!substream->rmidi->निजी_data))
		वापस -ENXIO;

	mpu = *((snd_wavefront_mpu_id *) substream->rmidi->निजी_data);

	अगर ((midi = get_wavefront_midi (substream)) == शून्य)
	        वापस -EIO;

	spin_lock_irqsave (&midi->खोलो, flags);
	midi->mode[mpu] |= MPU401_MODE_INPUT;
	midi->substream_input[mpu] = substream;
	spin_unlock_irqrestore (&midi->खोलो, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_wavefront_midi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	snd_wavefront_midi_t *midi;
	snd_wavefront_mpu_id mpu;

	अगर (snd_BUG_ON(!substream || !substream->rmidi))
		वापस -ENXIO;
	अगर (snd_BUG_ON(!substream->rmidi->निजी_data))
		वापस -ENXIO;

	mpu = *((snd_wavefront_mpu_id *) substream->rmidi->निजी_data);

	अगर ((midi = get_wavefront_midi (substream)) == शून्य)
	        वापस -EIO;

	spin_lock_irqsave (&midi->खोलो, flags);
	midi->mode[mpu] |= MPU401_MODE_OUTPUT;
	midi->substream_output[mpu] = substream;
	spin_unlock_irqrestore (&midi->खोलो, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_wavefront_midi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	snd_wavefront_midi_t *midi;
	snd_wavefront_mpu_id mpu;

	अगर (snd_BUG_ON(!substream || !substream->rmidi))
		वापस -ENXIO;
	अगर (snd_BUG_ON(!substream->rmidi->निजी_data))
		वापस -ENXIO;

	mpu = *((snd_wavefront_mpu_id *) substream->rmidi->निजी_data);

	अगर ((midi = get_wavefront_midi (substream)) == शून्य)
	        वापस -EIO;

	spin_lock_irqsave (&midi->खोलो, flags);
	midi->mode[mpu] &= ~MPU401_MODE_INPUT;
	spin_unlock_irqrestore (&midi->खोलो, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_wavefront_midi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	snd_wavefront_midi_t *midi;
	snd_wavefront_mpu_id mpu;

	अगर (snd_BUG_ON(!substream || !substream->rmidi))
		वापस -ENXIO;
	अगर (snd_BUG_ON(!substream->rmidi->निजी_data))
		वापस -ENXIO;

	mpu = *((snd_wavefront_mpu_id *) substream->rmidi->निजी_data);

	अगर ((midi = get_wavefront_midi (substream)) == शून्य)
	        वापस -EIO;

	spin_lock_irqsave (&midi->खोलो, flags);
	midi->mode[mpu] &= ~MPU401_MODE_OUTPUT;
	spin_unlock_irqrestore (&midi->खोलो, flags);
	वापस 0;
पूर्ण

अटल व्योम snd_wavefront_midi_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	snd_wavefront_midi_t *midi;
	snd_wavefront_mpu_id mpu;

	अगर (substream == शून्य || substream->rmidi == शून्य) 
	        वापस;

	अगर (substream->rmidi->निजी_data == शून्य)
	        वापस;

	mpu = *((snd_wavefront_mpu_id *) substream->rmidi->निजी_data);

	अगर ((midi = get_wavefront_midi (substream)) == शून्य) अणु
		वापस;
	पूर्ण

	spin_lock_irqsave (&midi->भव, flags);
	अगर (up) अणु
		midi->mode[mpu] |= MPU401_MODE_INPUT_TRIGGER;
	पूर्ण अन्यथा अणु
		midi->mode[mpu] &= ~MPU401_MODE_INPUT_TRIGGER;
	पूर्ण
	spin_unlock_irqrestore (&midi->भव, flags);
पूर्ण

अटल व्योम snd_wavefront_midi_output_समयr(काष्ठा समयr_list *t)
अणु
	snd_wavefront_midi_t *midi = from_समयr(midi, t, समयr);
	snd_wavefront_card_t *card = midi->समयr_card;
	अचिन्हित दीर्घ flags;
	
	spin_lock_irqsave (&midi->भव, flags);
	mod_समयr(&midi->समयr, 1 + jअगरfies);
	spin_unlock_irqrestore (&midi->भव, flags);
	snd_wavefront_midi_output_ग_लिखो(card);
पूर्ण

अटल व्योम snd_wavefront_midi_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	snd_wavefront_midi_t *midi;
	snd_wavefront_mpu_id mpu;

	अगर (substream == शून्य || substream->rmidi == शून्य) 
	        वापस;

	अगर (substream->rmidi->निजी_data == शून्य)
	        वापस;

	mpu = *((snd_wavefront_mpu_id *) substream->rmidi->निजी_data);

	अगर ((midi = get_wavefront_midi (substream)) == शून्य) अणु
		वापस;
	पूर्ण

	spin_lock_irqsave (&midi->भव, flags);
	अगर (up) अणु
		अगर ((midi->mode[mpu] & MPU401_MODE_OUTPUT_TRIGGER) == 0) अणु
			अगर (!midi->isसमयr) अणु
				समयr_setup(&midi->समयr,
					    snd_wavefront_midi_output_समयr,
					    0);
				mod_समयr(&midi->समयr, 1 + jअगरfies);
			पूर्ण
			midi->isसमयr++;
			midi->mode[mpu] |= MPU401_MODE_OUTPUT_TRIGGER;
		पूर्ण
	पूर्ण अन्यथा अणु
		midi->mode[mpu] &= ~MPU401_MODE_OUTPUT_TRIGGER;
	पूर्ण
	spin_unlock_irqrestore (&midi->भव, flags);

	अगर (up)
		snd_wavefront_midi_output_ग_लिखो((snd_wavefront_card_t *)substream->rmidi->card->निजी_data);
पूर्ण

व्योम
snd_wavefront_midi_पूर्णांकerrupt (snd_wavefront_card_t *card)

अणु
	अचिन्हित दीर्घ flags;
	snd_wavefront_midi_t *midi;
	अटल काष्ठा snd_rawmidi_substream *substream = शून्य;
	अटल पूर्णांक mpu = बाह्यal_mpu; 
	पूर्णांक max = 128;
	अचिन्हित अक्षर byte;

	midi = &card->wavefront.midi;

	अगर (!input_avail (midi)) अणु /* not क्रम us */
		snd_wavefront_midi_output_ग_लिखो(card);
		वापस;
	पूर्ण

	spin_lock_irqsave (&midi->भव, flags);
	जबतक (--max) अणु

		अगर (input_avail (midi)) अणु
			byte = पढ़ो_data (midi);

			अगर (midi->isभव) अणु				
				अगर (byte == WF_EXTERNAL_SWITCH) अणु
					substream = midi->substream_input[बाह्यal_mpu];
					mpu = बाह्यal_mpu;
				पूर्ण अन्यथा अगर (byte == WF_INTERNAL_SWITCH) अणु 
					substream = midi->substream_output[पूर्णांकernal_mpu];
					mpu = पूर्णांकernal_mpu;
				पूर्ण /* अन्यथा just leave it as it is */
			पूर्ण अन्यथा अणु
				substream = midi->substream_input[पूर्णांकernal_mpu];
				mpu = पूर्णांकernal_mpu;
			पूर्ण

			अगर (substream == शून्य) अणु
				जारी;
			पूर्ण

			अगर (midi->mode[mpu] & MPU401_MODE_INPUT_TRIGGER) अणु
				snd_rawmidi_receive(substream, &byte, 1);
			पूर्ण
		पूर्ण अन्यथा अणु
			अवरोध;
		पूर्ण
	पूर्ण 
	spin_unlock_irqrestore (&midi->भव, flags);

	snd_wavefront_midi_output_ग_लिखो(card);
पूर्ण

व्योम
snd_wavefront_midi_enable_भव (snd_wavefront_card_t *card)

अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave (&card->wavefront.midi.भव, flags);
	card->wavefront.midi.isभव = 1;
	card->wavefront.midi.output_mpu = पूर्णांकernal_mpu;
	card->wavefront.midi.input_mpu = पूर्णांकernal_mpu;
	spin_unlock_irqrestore (&card->wavefront.midi.भव, flags);
पूर्ण

व्योम
snd_wavefront_midi_disable_भव (snd_wavefront_card_t *card)

अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave (&card->wavefront.midi.भव, flags);
	// snd_wavefront_midi_input_बंद (card->ics2115_बाह्यal_rmidi);
	// snd_wavefront_midi_output_बंद (card->ics2115_बाह्यal_rmidi);
	card->wavefront.midi.isभव = 0;
	spin_unlock_irqrestore (&card->wavefront.midi.भव, flags);
पूर्ण

पूर्णांक
snd_wavefront_midi_start (snd_wavefront_card_t *card)

अणु
	पूर्णांक ok, i;
	अचिन्हित अक्षर rbuf[4], wbuf[4];
	snd_wavefront_t *dev;
	snd_wavefront_midi_t *midi;

	dev = &card->wavefront;
	midi = &dev->midi;

	/* The ICS2115 MPU-401 पूर्णांकerface करोesn't करो anything
	   until its set पूर्णांकo UART mode.
	*/

	/* XXX fix me - no hard timing loops allowed! */

	क्रम (i = 0; i < 30000 && !output_पढ़ोy (midi); i++);

	अगर (!output_पढ़ोy (midi)) अणु
		snd_prपूर्णांकk ("MIDI interface not ready for command\n");
		वापस -1;
	पूर्ण

	/* Any पूर्णांकerrupts received from now on
	   are owned by the MIDI side of things.
	*/

	dev->पूर्णांकerrupts_are_midi = 1;
	
	outb (UART_MODE_ON, midi->mpu_command_port);

	क्रम (ok = 0, i = 50000; i > 0 && !ok; i--) अणु
		अगर (input_avail (midi)) अणु
			अगर (पढ़ो_data (midi) == MPU_ACK) अणु
				ok = 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!ok) अणु
		snd_prपूर्णांकk ("cannot set UART mode for MIDI interface");
		dev->पूर्णांकerrupts_are_midi = 0;
		वापस -1;
	पूर्ण

	/* Route बाह्यal MIDI to WaveFront synth (by शेष) */
    
	अगर (snd_wavefront_cmd (dev, WFC_MISYNTH_ON, rbuf, wbuf)) अणु
		snd_prपूर्णांकk ("can't enable MIDI-IN-2-synth routing.\n");
		/* XXX error ? */
	पूर्ण

	/* Turn on Virtual MIDI, but first *always* turn it off,
	   since otherwise consecutive reloads of the driver will
	   never cause the hardware to generate the initial "internal" or 
	   "external" source bytes in the MIDI data stream. This
	   is pretty important, since the पूर्णांकernal hardware generally will
	   be used to generate none or very little MIDI output, and
	   thus the only source of MIDI data is actually बाह्यal. Without
	   the चयन bytes, the driver will think it all comes from
	   the पूर्णांकernal पूर्णांकerface. Duh.
	*/

	अगर (snd_wavefront_cmd (dev, WFC_VMIDI_OFF, rbuf, wbuf)) अणु 
		snd_prपूर्णांकk ("virtual MIDI mode not disabled\n");
		वापस 0; /* We're OK, but missing the बाह्यal MIDI dev */
	पूर्ण

	snd_wavefront_midi_enable_भव (card);

	अगर (snd_wavefront_cmd (dev, WFC_VMIDI_ON, rbuf, wbuf)) अणु
		snd_prपूर्णांकk ("cannot enable virtual MIDI mode.\n");
		snd_wavefront_midi_disable_भव (card);
	पूर्ण 
	वापस 0;
पूर्ण

स्थिर काष्ठा snd_rawmidi_ops snd_wavefront_midi_output =
अणु
	.खोलो =		snd_wavefront_midi_output_खोलो,
	.बंद =	snd_wavefront_midi_output_बंद,
	.trigger =	snd_wavefront_midi_output_trigger,
पूर्ण;

स्थिर काष्ठा snd_rawmidi_ops snd_wavefront_midi_input =
अणु
	.खोलो =		snd_wavefront_midi_input_खोलो,
	.बंद =	snd_wavefront_midi_input_बंद,
	.trigger =	snd_wavefront_midi_input_trigger,
पूर्ण;

