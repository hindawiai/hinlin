<शैली गुरु>
/****************************************************************************

   Copyright Echo Digital Audio Corporation (c) 1998 - 2004
   All rights reserved
   www.echoaudio.com

   This file is part of Echo Digital Audio's generic driver library.

   Echo Digital Audio's generic driver library is मुक्त software;
   you can redistribute it and/or modअगरy it under the terms of
   the GNU General Public License as published by the Free Software
   Foundation.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License क्रम more details.

   You should have received a copy of the GNU General Public License
   aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330, Boston,
   MA  02111-1307, USA.

   *************************************************************************

 Translation from C++ and adaptation क्रम use in ALSA-Driver
 were made by Giuliano Pochini <pochini@shiny.it>

****************************************************************************/


/******************************************************************************
	MIDI lowlevel code
******************************************************************************/

/* Start and stop Midi input */
अटल पूर्णांक enable_midi_input(काष्ठा echoaudio *chip, अक्षर enable)
अणु
	dev_dbg(chip->card->dev, "enable_midi_input(%d)\n", enable);

	अगर (रुको_handshake(chip))
		वापस -EIO;

	अगर (enable) अणु
		chip->mtc_state = MIDI_IN_STATE_NORMAL;
		chip->comm_page->flags |=
			cpu_to_le32(DSP_FLAG_MIDI_INPUT);
	पूर्ण अन्यथा
		chip->comm_page->flags &=
			~cpu_to_le32(DSP_FLAG_MIDI_INPUT);

	clear_handshake(chip);
	वापस send_vector(chip, DSP_VC_UPDATE_FLAGS);
पूर्ण



/* Send a buffer full of MIDI data to the DSP
Returns how many actually written or < 0 on error */
अटल पूर्णांक ग_लिखो_midi(काष्ठा echoaudio *chip, u8 *data, पूर्णांक bytes)
अणु
	अगर (snd_BUG_ON(bytes <= 0 || bytes >= MIDI_OUT_BUFFER_SIZE))
		वापस -EINVAL;

	अगर (रुको_handshake(chip))
		वापस -EIO;

	/* HF4 indicates that it is safe to ग_लिखो MIDI output data */
	अगर (! (get_dsp_रेजिस्टर(chip, CHI32_STATUS_REG) & CHI32_STATUS_REG_HF4))
		वापस 0;

	chip->comm_page->midi_output[0] = bytes;
	स_नकल(&chip->comm_page->midi_output[1], data, bytes);
	chip->comm_page->midi_out_मुक्त_count = 0;
	clear_handshake(chip);
	send_vector(chip, DSP_VC_MIDI_WRITE);
	dev_dbg(chip->card->dev, "write_midi: %d\n", bytes);
	वापस bytes;
पूर्ण



/* Run the state machine क्रम MIDI input data
MIDI समय code sync isn't supported by this code right now, but you still need
this state machine to parse the incoming MIDI data stream.  Every समय the DSP
sees a 0xF1 byte come in, it adds the DSP sample position to the MIDI data
stream. The DSP sample position is represented as a 32 bit अचिन्हित value,
with the high 16 bits first, followed by the low 16 bits. Since these aren't
real MIDI bytes, the following logic is needed to skip them. */
अटल अंतरभूत पूर्णांक mtc_process_data(काष्ठा echoaudio *chip, लघु midi_byte)
अणु
	चयन (chip->mtc_state) अणु
	हाल MIDI_IN_STATE_NORMAL:
		अगर (midi_byte == 0xF1)
			chip->mtc_state = MIDI_IN_STATE_TS_HIGH;
		अवरोध;
	हाल MIDI_IN_STATE_TS_HIGH:
		chip->mtc_state = MIDI_IN_STATE_TS_LOW;
		वापस MIDI_IN_SKIP_DATA;
		अवरोध;
	हाल MIDI_IN_STATE_TS_LOW:
		chip->mtc_state = MIDI_IN_STATE_F1_DATA;
		वापस MIDI_IN_SKIP_DATA;
		अवरोध;
	हाल MIDI_IN_STATE_F1_DATA:
		chip->mtc_state = MIDI_IN_STATE_NORMAL;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण



/* This function is called from the IRQ handler and it पढ़ोs the midi data
from the DSP's buffer.  It वापसs the number of bytes received. */
अटल पूर्णांक midi_service_irq(काष्ठा echoaudio *chip)
अणु
	लघु पूर्णांक count, midi_byte, i, received;

	/* The count is at index 0, followed by actual data */
	count = le16_to_cpu(chip->comm_page->midi_input[0]);

	अगर (snd_BUG_ON(count >= MIDI_IN_BUFFER_SIZE))
		वापस 0;

	/* Get the MIDI data from the comm page */
	i = 1;
	received = 0;
	क्रम (i = 1; i <= count; i++) अणु
		/* Get the MIDI byte */
		midi_byte = le16_to_cpu(chip->comm_page->midi_input[i]);

		/* Parse the incoming MIDI stream. The incoming MIDI data
		consists of MIDI bytes and बारtamps क्रम the MIDI समय code
		0xF1 bytes. mtc_process_data() is a little state machine that
		parses the stream. If you get MIDI_IN_SKIP_DATA back, then
		this is a बारtamp byte, not a MIDI byte, so करोn't store it
		in the MIDI input buffer. */
		अगर (mtc_process_data(chip, midi_byte) == MIDI_IN_SKIP_DATA)
			जारी;

		chip->midi_buffer[received++] = (u8)midi_byte;
	पूर्ण

	वापस received;
पूर्ण




/******************************************************************************
	MIDI पूर्णांकerface
******************************************************************************/

अटल पूर्णांक snd_echo_midi_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा echoaudio *chip = substream->rmidi->निजी_data;

	chip->midi_in = substream;
	वापस 0;
पूर्ण



अटल व्योम snd_echo_midi_input_trigger(काष्ठा snd_rawmidi_substream *substream,
					पूर्णांक up)
अणु
	काष्ठा echoaudio *chip = substream->rmidi->निजी_data;

	अगर (up != chip->midi_input_enabled) अणु
		spin_lock_irq(&chip->lock);
		enable_midi_input(chip, up);
		spin_unlock_irq(&chip->lock);
		chip->midi_input_enabled = up;
	पूर्ण
पूर्ण



अटल पूर्णांक snd_echo_midi_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा echoaudio *chip = substream->rmidi->निजी_data;

	chip->midi_in = शून्य;
	वापस 0;
पूर्ण



अटल पूर्णांक snd_echo_midi_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा echoaudio *chip = substream->rmidi->निजी_data;

	chip->tinuse = 0;
	chip->midi_full = 0;
	chip->midi_out = substream;
	वापस 0;
पूर्ण



अटल व्योम snd_echo_midi_output_ग_लिखो(काष्ठा समयr_list *t)
अणु
	काष्ठा echoaudio *chip = from_समयr(chip, t, समयr);
	अचिन्हित दीर्घ flags;
	पूर्णांक bytes, sent, समय;
	अचिन्हित अक्षर buf[MIDI_OUT_BUFFER_SIZE - 1];

	/* No पूर्णांकerrupts are involved: we have to check at regular पूर्णांकervals
	अगर the card's output buffer has room क्रम new data. */
	sent = bytes = 0;
	spin_lock_irqsave(&chip->lock, flags);
	chip->midi_full = 0;
	अगर (!snd_rawmidi_transmit_empty(chip->midi_out)) अणु
		bytes = snd_rawmidi_transmit_peek(chip->midi_out, buf,
						  MIDI_OUT_BUFFER_SIZE - 1);
		dev_dbg(chip->card->dev, "Try to send %d bytes...\n", bytes);
		sent = ग_लिखो_midi(chip, buf, bytes);
		अगर (sent < 0) अणु
			dev_err(chip->card->dev,
				"write_midi() error %d\n", sent);
			/* retry later */
			sent = 9000;
			chip->midi_full = 1;
		पूर्ण अन्यथा अगर (sent > 0) अणु
			dev_dbg(chip->card->dev, "%d bytes sent\n", sent);
			snd_rawmidi_transmit_ack(chip->midi_out, sent);
		पूर्ण अन्यथा अणु
			/* Buffer is full. DSP's पूर्णांकernal buffer is 64 (128 ?)
			bytes दीर्घ. Let's रुको until half of them are sent */
			dev_dbg(chip->card->dev, "Full\n");
			sent = 32;
			chip->midi_full = 1;
		पूर्ण
	पूर्ण

	/* We restart the समयr only अगर there is some data left to send */
	अगर (!snd_rawmidi_transmit_empty(chip->midi_out) && chip->tinuse) अणु
		/* The समयr will expire slightly after the data has been
		   sent */
		समय = (sent << 3) / 25 + 1;	/* 8/25=0.32ms to send a byte */
		mod_समयr(&chip->समयr, jअगरfies + (समय * HZ + 999) / 1000);
		dev_dbg(chip->card->dev,
			"Timer armed(%d)\n", ((समय * HZ + 999) / 1000));
	पूर्ण
	spin_unlock_irqrestore(&chip->lock, flags);
पूर्ण



अटल व्योम snd_echo_midi_output_trigger(काष्ठा snd_rawmidi_substream *substream,
					 पूर्णांक up)
अणु
	काष्ठा echoaudio *chip = substream->rmidi->निजी_data;

	dev_dbg(chip->card->dev, "snd_echo_midi_output_trigger(%d)\n", up);
	spin_lock_irq(&chip->lock);
	अगर (up) अणु
		अगर (!chip->tinuse) अणु
			समयr_setup(&chip->समयr, snd_echo_midi_output_ग_लिखो,
				    0);
			chip->tinuse = 1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (chip->tinuse) अणु
			chip->tinuse = 0;
			spin_unlock_irq(&chip->lock);
			del_समयr_sync(&chip->समयr);
			dev_dbg(chip->card->dev, "Timer removed\n");
			वापस;
		पूर्ण
	पूर्ण
	spin_unlock_irq(&chip->lock);

	अगर (up && !chip->midi_full)
		snd_echo_midi_output_ग_लिखो(&chip->समयr);
पूर्ण



अटल पूर्णांक snd_echo_midi_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	काष्ठा echoaudio *chip = substream->rmidi->निजी_data;

	chip->midi_out = शून्य;
	वापस 0;
पूर्ण



अटल स्थिर काष्ठा snd_rawmidi_ops snd_echo_midi_input = अणु
	.खोलो = snd_echo_midi_input_खोलो,
	.बंद = snd_echo_midi_input_बंद,
	.trigger = snd_echo_midi_input_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_echo_midi_output = अणु
	.खोलो = snd_echo_midi_output_खोलो,
	.बंद = snd_echo_midi_output_बंद,
	.trigger = snd_echo_midi_output_trigger,
पूर्ण;



/* <--snd_echo_probe() */
अटल पूर्णांक snd_echo_midi_create(काष्ठा snd_card *card,
				काष्ठा echoaudio *chip)
अणु
	पूर्णांक err;

	अगर ((err = snd_rawmidi_new(card, card->लघुname, 0, 1, 1,
				   &chip->rmidi)) < 0)
		वापस err;

	म_नकल(chip->rmidi->name, card->लघुname);
	chip->rmidi->निजी_data = chip;

	snd_rawmidi_set_ops(chip->rmidi, SNDRV_RAWMIDI_STREAM_INPUT,
			    &snd_echo_midi_input);
	snd_rawmidi_set_ops(chip->rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT,
			    &snd_echo_midi_output);

	chip->rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT |
		SNDRV_RAWMIDI_INFO_INPUT | SNDRV_RAWMIDI_INFO_DUPLEX;
	वापस 0;
पूर्ण
