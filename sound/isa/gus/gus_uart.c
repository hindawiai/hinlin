<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Jaroslav Kysela <perex@perex.cz>
 *  Routines क्रम the GF1 MIDI पूर्णांकerface - like UART 6850
 */

#समावेश <linux/delay.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/gus.h>

अटल व्योम snd_gf1_पूर्णांकerrupt_midi_in(काष्ठा snd_gus_card * gus)
अणु
	पूर्णांक count;
	अचिन्हित अक्षर stat, byte;
	__always_unused अचिन्हित अक्षर data;
	अचिन्हित दीर्घ flags;

	count = 10;
	जबतक (count) अणु
		spin_lock_irqsave(&gus->uart_cmd_lock, flags);
		stat = snd_gf1_uart_stat(gus);
		अगर (!(stat & 0x01)) अणु	/* data in Rx FIFO? */
			spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
			count--;
			जारी;
		पूर्ण
		count = 100;	/* arm counter to new value */
		data = snd_gf1_uart_get(gus);
		अगर (!(gus->gf1.uart_cmd & 0x80)) अणु
			spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
			जारी;
		पूर्ण			
		अगर (stat & 0x10) अणु	/* framing error */
			gus->gf1.uart_framing++;
			spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
			जारी;
		पूर्ण
		byte = snd_gf1_uart_get(gus);
		spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
		snd_rawmidi_receive(gus->midi_substream_input, &byte, 1);
		अगर (stat & 0x20) अणु
			gus->gf1.uart_overrun++;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम snd_gf1_पूर्णांकerrupt_midi_out(काष्ठा snd_gus_card * gus)
अणु
	अक्षर byte;
	अचिन्हित दीर्घ flags;

	/* try unlock output */
	अगर (snd_gf1_uart_stat(gus) & 0x01)
		snd_gf1_पूर्णांकerrupt_midi_in(gus);

	spin_lock_irqsave(&gus->uart_cmd_lock, flags);
	अगर (snd_gf1_uart_stat(gus) & 0x02) अणु	/* Tx FIFO मुक्त? */
		अगर (snd_rawmidi_transmit(gus->midi_substream_output, &byte, 1) != 1) अणु	/* no other bytes or error */
			snd_gf1_uart_cmd(gus, gus->gf1.uart_cmd & ~0x20); /* disable Tx पूर्णांकerrupt */
		पूर्ण अन्यथा अणु
			snd_gf1_uart_put(gus, byte);
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
पूर्ण

अटल व्योम snd_gf1_uart_reset(काष्ठा snd_gus_card * gus, पूर्णांक बंद)
अणु
	snd_gf1_uart_cmd(gus, 0x03);	/* reset */
	अगर (!बंद && gus->uart_enable) अणु
		udelay(160);
		snd_gf1_uart_cmd(gus, 0x00);	/* normal operations */
	पूर्ण
पूर्ण

अटल पूर्णांक snd_gf1_uart_output_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_gus_card *gus;

	gus = substream->rmidi->निजी_data;
	spin_lock_irqsave(&gus->uart_cmd_lock, flags);
	अगर (!(gus->gf1.uart_cmd & 0x80)) अणु	/* input active? */
		snd_gf1_uart_reset(gus, 0);
	पूर्ण
	gus->gf1.पूर्णांकerrupt_handler_midi_out = snd_gf1_पूर्णांकerrupt_midi_out;
	gus->midi_substream_output = substream;
	spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
#अगर 0
	snd_prपूर्णांकk(KERN_DEBUG "write init - cmd = 0x%x, stat = 0x%x\n", gus->gf1.uart_cmd, snd_gf1_uart_stat(gus));
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_uart_input_खोलो(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_gus_card *gus;
	पूर्णांक i;

	gus = substream->rmidi->निजी_data;
	spin_lock_irqsave(&gus->uart_cmd_lock, flags);
	अगर (gus->gf1.पूर्णांकerrupt_handler_midi_out != snd_gf1_पूर्णांकerrupt_midi_out) अणु
		snd_gf1_uart_reset(gus, 0);
	पूर्ण
	gus->gf1.पूर्णांकerrupt_handler_midi_in = snd_gf1_पूर्णांकerrupt_midi_in;
	gus->midi_substream_input = substream;
	अगर (gus->uart_enable) अणु
		क्रम (i = 0; i < 1000 && (snd_gf1_uart_stat(gus) & 0x01); i++)
			snd_gf1_uart_get(gus);	/* clean Rx */
		अगर (i >= 1000)
			snd_prपूर्णांकk(KERN_ERR "gus midi uart init read - cleanup error\n");
	पूर्ण
	spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
#अगर 0
	snd_prपूर्णांकk(KERN_DEBUG
		   "read init - enable = %i, cmd = 0x%x, stat = 0x%x\n",
		   gus->uart_enable, gus->gf1.uart_cmd, snd_gf1_uart_stat(gus));
	snd_prपूर्णांकk(KERN_DEBUG
		   "[0x%x] reg (ctrl/status) = 0x%x, reg (data) = 0x%x "
		   "(page = 0x%x)\n",
		   gus->gf1.port + 0x100, inb(gus->gf1.port + 0x100),
		   inb(gus->gf1.port + 0x101), inb(gus->gf1.port + 0x102));
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_uart_output_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_gus_card *gus;

	gus = substream->rmidi->निजी_data;
	spin_lock_irqsave(&gus->uart_cmd_lock, flags);
	अगर (gus->gf1.पूर्णांकerrupt_handler_midi_in != snd_gf1_पूर्णांकerrupt_midi_in)
		snd_gf1_uart_reset(gus, 1);
	snd_gf1_set_शेष_handlers(gus, SNDRV_GF1_HANDLER_MIDI_OUT);
	gus->midi_substream_output = शून्य;
	spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_gf1_uart_input_बंद(काष्ठा snd_rawmidi_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_gus_card *gus;

	gus = substream->rmidi->निजी_data;
	spin_lock_irqsave(&gus->uart_cmd_lock, flags);
	अगर (gus->gf1.पूर्णांकerrupt_handler_midi_out != snd_gf1_पूर्णांकerrupt_midi_out)
		snd_gf1_uart_reset(gus, 1);
	snd_gf1_set_शेष_handlers(gus, SNDRV_GF1_HANDLER_MIDI_IN);
	gus->midi_substream_input = शून्य;
	spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
	वापस 0;
पूर्ण

अटल व्योम snd_gf1_uart_input_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	काष्ठा snd_gus_card *gus;
	अचिन्हित दीर्घ flags;

	gus = substream->rmidi->निजी_data;

	spin_lock_irqsave(&gus->uart_cmd_lock, flags);
	अगर (up) अणु
		अगर ((gus->gf1.uart_cmd & 0x80) == 0)
			snd_gf1_uart_cmd(gus, gus->gf1.uart_cmd | 0x80); /* enable Rx पूर्णांकerrupts */
	पूर्ण अन्यथा अणु
		अगर (gus->gf1.uart_cmd & 0x80)
			snd_gf1_uart_cmd(gus, gus->gf1.uart_cmd & ~0x80); /* disable Rx पूर्णांकerrupts */
	पूर्ण
	spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
पूर्ण

अटल व्योम snd_gf1_uart_output_trigger(काष्ठा snd_rawmidi_substream *substream, पूर्णांक up)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_gus_card *gus;
	अक्षर byte;
	पूर्णांक समयout;

	gus = substream->rmidi->निजी_data;

	spin_lock_irqsave(&gus->uart_cmd_lock, flags);
	अगर (up) अणु
		अगर ((gus->gf1.uart_cmd & 0x20) == 0) अणु
			spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
			/* रुको क्रम empty Rx - Tx is probably unlocked */
			समयout = 10000;
			जबतक (समयout-- > 0 && snd_gf1_uart_stat(gus) & 0x01);
			/* Tx FIFO मुक्त? */
			spin_lock_irqsave(&gus->uart_cmd_lock, flags);
			अगर (gus->gf1.uart_cmd & 0x20) अणु
				spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
				वापस;
			पूर्ण
			अगर (snd_gf1_uart_stat(gus) & 0x02) अणु
				अगर (snd_rawmidi_transmit(substream, &byte, 1) != 1) अणु
					spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
					वापस;
				पूर्ण
				snd_gf1_uart_put(gus, byte);
			पूर्ण
			snd_gf1_uart_cmd(gus, gus->gf1.uart_cmd | 0x20);	/* enable Tx पूर्णांकerrupt */
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (gus->gf1.uart_cmd & 0x20)
			snd_gf1_uart_cmd(gus, gus->gf1.uart_cmd & ~0x20);
	पूर्ण
	spin_unlock_irqrestore(&gus->uart_cmd_lock, flags);
पूर्ण

अटल स्थिर काष्ठा snd_rawmidi_ops snd_gf1_uart_output =
अणु
	.खोलो =		snd_gf1_uart_output_खोलो,
	.बंद =	snd_gf1_uart_output_बंद,
	.trigger =	snd_gf1_uart_output_trigger,
पूर्ण;

अटल स्थिर काष्ठा snd_rawmidi_ops snd_gf1_uart_input =
अणु
	.खोलो =		snd_gf1_uart_input_खोलो,
	.बंद =	snd_gf1_uart_input_बंद,
	.trigger =	snd_gf1_uart_input_trigger,
पूर्ण;

पूर्णांक snd_gf1_rawmidi_new(काष्ठा snd_gus_card *gus, पूर्णांक device)
अणु
	काष्ठा snd_rawmidi *rmidi;
	पूर्णांक err;

	अगर ((err = snd_rawmidi_new(gus->card, "GF1", device, 1, 1, &rmidi)) < 0)
		वापस err;
	म_नकल(rmidi->name, gus->पूर्णांकerwave ? "AMD InterWave" : "GF1");
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_OUTPUT, &snd_gf1_uart_output);
	snd_rawmidi_set_ops(rmidi, SNDRV_RAWMIDI_STREAM_INPUT, &snd_gf1_uart_input);
	rmidi->info_flags |= SNDRV_RAWMIDI_INFO_OUTPUT | SNDRV_RAWMIDI_INFO_INPUT | SNDRV_RAWMIDI_INFO_DUPLEX;
	rmidi->निजी_data = gus;
	gus->midi_uart = rmidi;
	वापस err;
पूर्ण
