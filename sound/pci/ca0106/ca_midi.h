<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/* 
 *  Copyright 10/16/2005 Tilman Kranz <tilde@tk-sls.de>
 *  Creative Audio MIDI, क्रम the CA0106 Driver
 *  Version: 0.0.1
 *
 *  Changelog:
 *    See ca_midi.c
 */

#समावेश <linux/spinlock.h>
#समावेश <sound/rawmidi.h>
#समावेश <sound/mpu401.h>

#घोषणा CA_MIDI_MODE_INPUT	MPU401_MODE_INPUT
#घोषणा CA_MIDI_MODE_OUTPUT	MPU401_MODE_OUTPUT

काष्ठा snd_ca_midi अणु

	काष्ठा snd_rawmidi *rmidi;
	काष्ठा snd_rawmidi_substream *substream_input;
	काष्ठा snd_rawmidi_substream *substream_output;

	व्योम *dev_id;

	spinlock_t input_lock;
	spinlock_t output_lock;
	spinlock_t खोलो_lock;

	अचिन्हित पूर्णांक channel;

	अचिन्हित पूर्णांक midi_mode;
	पूर्णांक port;
	पूर्णांक tx_enable, rx_enable;
	पूर्णांक ipr_tx, ipr_rx;            
	
	पूर्णांक input_avail, output_पढ़ोy;
	पूर्णांक ack, reset, enter_uart;

	व्योम (*पूर्णांकerrupt)(काष्ठा snd_ca_midi *midi, अचिन्हित पूर्णांक status);
	व्योम (*पूर्णांकerrupt_enable)(काष्ठा snd_ca_midi *midi, पूर्णांक पूर्णांकr);
	व्योम (*पूर्णांकerrupt_disable)(काष्ठा snd_ca_midi *midi, पूर्णांक पूर्णांकr);

	अचिन्हित अक्षर (*पढ़ो)(काष्ठा snd_ca_midi *midi, पूर्णांक idx);
	व्योम (*ग_लिखो)(काष्ठा snd_ca_midi *midi, पूर्णांक data, पूर्णांक idx);

	/* get info from dev_id */
	काष्ठा snd_card *(*get_dev_id_card)(व्योम *dev_id);
	पूर्णांक (*get_dev_id_port)(व्योम *dev_id);
पूर्ण;

पूर्णांक ca_midi_init(व्योम *card, काष्ठा snd_ca_midi *midi, पूर्णांक device, अक्षर *name);
