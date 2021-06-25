<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Midi Sequencer पूर्णांकerface routines.
 *
 *  Copyright (C) 1999 Steve Ratclअगरfe
 *  Copyright (c) 1999-2000 Takashi Iwai <tiwai@suse.de>
 */

#समावेश "emux_voice.h"
#समावेश <linux/slab.h>
#समावेश <linux/module.h>

/* Prototypes क्रम अटल functions */
अटल व्योम मुक्त_port(व्योम *निजी);
अटल व्योम snd_emux_init_port(काष्ठा snd_emux_port *p);
अटल पूर्णांक snd_emux_use(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info);
अटल पूर्णांक snd_emux_unuse(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info);

/*
 * MIDI emulation चालकs
 */
अटल स्थिर काष्ठा snd_midi_op emux_ops = अणु
	.note_on = snd_emux_note_on,
	.note_off = snd_emux_note_off,
	.key_press = snd_emux_key_press,
	.note_terminate = snd_emux_terminate_note,
	.control = snd_emux_control,
	.nrpn = snd_emux_nrpn,
	.sysex = snd_emux_sysex,
पूर्ण;


/*
 * number of MIDI channels
 */
#घोषणा MIDI_CHANNELS		16

/*
 * type flags क्रम MIDI sequencer port
 */
#घोषणा DEFAULT_MIDI_TYPE	(SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC |\
				 SNDRV_SEQ_PORT_TYPE_MIDI_GM |\
				 SNDRV_SEQ_PORT_TYPE_MIDI_GS |\
				 SNDRV_SEQ_PORT_TYPE_MIDI_XG |\
				 SNDRV_SEQ_PORT_TYPE_HARDWARE |\
				 SNDRV_SEQ_PORT_TYPE_SYNTHESIZER)

/*
 * Initialise the EMUX Synth by creating a client and रेजिस्टरing
 * a series of ports.
 * Each of the ports will contain the 16 midi channels.  Applications
 * can connect to these ports to play midi data.
 */
पूर्णांक
snd_emux_init_seq(काष्ठा snd_emux *emu, काष्ठा snd_card *card, पूर्णांक index)
अणु
	पूर्णांक  i;
	काष्ठा snd_seq_port_callback pinfo;
	अक्षर क्षणिकe[64];

	emu->client = snd_seq_create_kernel_client(card, index,
						   "%s WaveTable", emu->name);
	अगर (emu->client < 0) अणु
		snd_prपूर्णांकk(KERN_ERR "can't create client\n");
		वापस -ENODEV;
	पूर्ण

	अगर (emu->num_ports < 0) अणु
		snd_prपूर्णांकk(KERN_WARNING "seqports must be greater than zero\n");
		emu->num_ports = 1;
	पूर्ण अन्यथा अगर (emu->num_ports >= SNDRV_EMUX_MAX_PORTS) अणु
		snd_prपूर्णांकk(KERN_WARNING "too many ports."
			   "limited max. ports %d\n", SNDRV_EMUX_MAX_PORTS);
		emu->num_ports = SNDRV_EMUX_MAX_PORTS;
	पूर्ण

	स_रखो(&pinfo, 0, माप(pinfo));
	pinfo.owner = THIS_MODULE;
	pinfo.use = snd_emux_use;
	pinfo.unuse = snd_emux_unuse;
	pinfo.event_input = snd_emux_event_input;

	क्रम (i = 0; i < emu->num_ports; i++) अणु
		काष्ठा snd_emux_port *p;

		प्र_लिखो(क्षणिकe, "%s Port %d", emu->name, i);
		p = snd_emux_create_port(emu, क्षणिकe, MIDI_CHANNELS,
					 0, &pinfo);
		अगर (!p) अणु
			snd_prपूर्णांकk(KERN_ERR "can't create port\n");
			वापस -ENOMEM;
		पूर्ण

		p->port_mode =  SNDRV_EMUX_PORT_MODE_MIDI;
		snd_emux_init_port(p);
		emu->ports[i] = p->chset.port;
		emu->portptrs[i] = p;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * Detach from the ports that were set up क्रम this synthesizer and
 * destroy the kernel client.
 */
व्योम
snd_emux_detach_seq(काष्ठा snd_emux *emu)
अणु
	अगर (emu->voices)
		snd_emux_terminate_all(emu);
		
	अगर (emu->client >= 0) अणु
		snd_seq_delete_kernel_client(emu->client);
		emu->client = -1;
	पूर्ण
पूर्ण


/*
 * create a sequencer port and channel_set
 */

काष्ठा snd_emux_port *
snd_emux_create_port(काष्ठा snd_emux *emu, अक्षर *name,
		     पूर्णांक max_channels, पूर्णांक oss_port,
		     काष्ठा snd_seq_port_callback *callback)
अणु
	काष्ठा snd_emux_port *p;
	पूर्णांक i, type, cap;

	/* Allocate काष्ठाures क्रम this channel */
	p = kzalloc(माप(*p), GFP_KERNEL);
	अगर (!p)
		वापस शून्य;

	p->chset.channels = kसुस्मृति(max_channels, माप(*p->chset.channels),
				    GFP_KERNEL);
	अगर (!p->chset.channels) अणु
		kमुक्त(p);
		वापस शून्य;
	पूर्ण
	क्रम (i = 0; i < max_channels; i++)
		p->chset.channels[i].number = i;
	p->chset.निजी_data = p;
	p->chset.max_channels = max_channels;
	p->emu = emu;
	p->chset.client = emu->client;
#अगर_घोषित SNDRV_EMUX_USE_RAW_EFFECT
	snd_emux_create_effect(p);
#पूर्ण_अगर
	callback->निजी_मुक्त = मुक्त_port;
	callback->निजी_data = p;

	cap = SNDRV_SEQ_PORT_CAP_WRITE;
	अगर (oss_port) अणु
		type = SNDRV_SEQ_PORT_TYPE_SPECIFIC;
	पूर्ण अन्यथा अणु
		type = DEFAULT_MIDI_TYPE;
		cap |= SNDRV_SEQ_PORT_CAP_SUBS_WRITE;
	पूर्ण

	p->chset.port = snd_seq_event_port_attach(emu->client, callback,
						  cap, type, max_channels,
						  emu->max_voices, name);

	वापस p;
पूर्ण


/*
 * release memory block क्रम port
 */
अटल व्योम
मुक्त_port(व्योम *निजी_data)
अणु
	काष्ठा snd_emux_port *p;

	p = निजी_data;
	अगर (p) अणु
#अगर_घोषित SNDRV_EMUX_USE_RAW_EFFECT
		snd_emux_delete_effect(p);
#पूर्ण_अगर
		kमुक्त(p->chset.channels);
		kमुक्त(p);
	पूर्ण
पूर्ण


#घोषणा DEFAULT_DRUM_FLAGS	(1<<9)

/*
 * initialize the port specअगरic parameters
 */
अटल व्योम
snd_emux_init_port(काष्ठा snd_emux_port *p)
अणु
	p->drum_flags = DEFAULT_DRUM_FLAGS;
	p->volume_atten = 0;

	snd_emux_reset_port(p);
पूर्ण


/*
 * reset port
 */
व्योम
snd_emux_reset_port(काष्ठा snd_emux_port *port)
अणु
	पूर्णांक i;

	/* stop all sounds */
	snd_emux_sounds_off_all(port);

	snd_midi_channel_set_clear(&port->chset);

#अगर_घोषित SNDRV_EMUX_USE_RAW_EFFECT
	snd_emux_clear_effect(port);
#पूर्ण_अगर

	/* set port specअगरic control parameters */
	port->ctrls[EMUX_MD_DEF_BANK] = 0;
	port->ctrls[EMUX_MD_DEF_DRUM] = 0;
	port->ctrls[EMUX_MD_REALTIME_PAN] = 1;

	क्रम (i = 0; i < port->chset.max_channels; i++) अणु
		काष्ठा snd_midi_channel *chan = port->chset.channels + i;
		chan->drum_channel = ((port->drum_flags >> i) & 1) ? 1 : 0;
	पूर्ण
पूर्ण


/*
 * input sequencer event
 */
पूर्णांक
snd_emux_event_input(काष्ठा snd_seq_event *ev, पूर्णांक direct, व्योम *निजी_data,
		     पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_emux_port *port;

	port = निजी_data;
	अगर (snd_BUG_ON(!port || !ev))
		वापस -EINVAL;

	snd_midi_process_event(&emux_ops, ev, &port->chset);

	वापस 0;
पूर्ण


/*
 * increment usage count
 */
अटल पूर्णांक
__snd_emux_inc_count(काष्ठा snd_emux *emu)
अणु
	emu->used++;
	अगर (!try_module_get(emu->ops.owner))
		जाओ __error;
	अगर (!try_module_get(emu->card->module)) अणु
		module_put(emu->ops.owner);
	      __error:
		emu->used--;
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

पूर्णांक snd_emux_inc_count(काष्ठा snd_emux *emu)
अणु
	पूर्णांक ret;

	mutex_lock(&emu->रेजिस्टर_mutex);
	ret = __snd_emux_inc_count(emu);
	mutex_unlock(&emu->रेजिस्टर_mutex);
	वापस ret;
पूर्ण

/*
 * decrease usage count
 */
अटल व्योम
__snd_emux_dec_count(काष्ठा snd_emux *emu)
अणु
	module_put(emu->card->module);
	emu->used--;
	अगर (emu->used <= 0)
		snd_emux_terminate_all(emu);
	module_put(emu->ops.owner);
पूर्ण

व्योम snd_emux_dec_count(काष्ठा snd_emux *emu)
अणु
	mutex_lock(&emu->रेजिस्टर_mutex);
	__snd_emux_dec_count(emu);
	mutex_unlock(&emu->रेजिस्टर_mutex);
पूर्ण

/*
 * Routine that is called upon a first use of a particular port
 */
अटल पूर्णांक
snd_emux_use(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info)
अणु
	काष्ठा snd_emux_port *p;
	काष्ठा snd_emux *emu;

	p = निजी_data;
	अगर (snd_BUG_ON(!p))
		वापस -EINVAL;
	emu = p->emu;
	अगर (snd_BUG_ON(!emu))
		वापस -EINVAL;

	mutex_lock(&emu->रेजिस्टर_mutex);
	snd_emux_init_port(p);
	__snd_emux_inc_count(emu);
	mutex_unlock(&emu->रेजिस्टर_mutex);
	वापस 0;
पूर्ण

/*
 * Routine that is called upon the last unuse() of a particular port.
 */
अटल पूर्णांक
snd_emux_unuse(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info)
अणु
	काष्ठा snd_emux_port *p;
	काष्ठा snd_emux *emu;

	p = निजी_data;
	अगर (snd_BUG_ON(!p))
		वापस -EINVAL;
	emu = p->emu;
	अगर (snd_BUG_ON(!emu))
		वापस -EINVAL;

	mutex_lock(&emu->रेजिस्टर_mutex);
	snd_emux_sounds_off_all(p);
	__snd_emux_dec_count(emu);
	mutex_unlock(&emu->रेजिस्टर_mutex);
	वापस 0;
पूर्ण


/*
 * attach भव rawmidi devices
 */
पूर्णांक snd_emux_init_virmidi(काष्ठा snd_emux *emu, काष्ठा snd_card *card)
अणु
	पूर्णांक i;

	emu->vmidi = शून्य;
	अगर (emu->midi_ports <= 0)
		वापस 0;

	emu->vmidi = kसुस्मृति(emu->midi_ports, माप(*emu->vmidi), GFP_KERNEL);
	अगर (!emu->vmidi)
		वापस -ENOMEM;

	क्रम (i = 0; i < emu->midi_ports; i++) अणु
		काष्ठा snd_rawmidi *rmidi;
		काष्ठा snd_virmidi_dev *rdev;
		अगर (snd_virmidi_new(card, emu->midi_devidx + i, &rmidi) < 0)
			जाओ __error;
		rdev = rmidi->निजी_data;
		प्र_लिखो(rmidi->name, "%s Synth MIDI", emu->name);
		rdev->seq_mode = SNDRV_VIRMIDI_SEQ_ATTACH;
		rdev->client = emu->client;
		rdev->port = emu->ports[i];
		अगर (snd_device_रेजिस्टर(card, rmidi) < 0) अणु
			snd_device_मुक्त(card, rmidi);
			जाओ __error;
		पूर्ण
		emu->vmidi[i] = rmidi;
		/* snd_prपूर्णांकk(KERN_DEBUG "virmidi %d ok\n", i); */
	पूर्ण
	वापस 0;

__error:
	/* snd_prपूर्णांकk(KERN_DEBUG "error init..\n"); */
	snd_emux_delete_virmidi(emu);
	वापस -ENOMEM;
पूर्ण

पूर्णांक snd_emux_delete_virmidi(काष्ठा snd_emux *emu)
अणु
	पूर्णांक i;

	अगर (!emu->vmidi)
		वापस 0;

	क्रम (i = 0; i < emu->midi_ports; i++) अणु
		अगर (emu->vmidi[i])
			snd_device_मुक्त(emu->card, emu->vmidi[i]);
	पूर्ण
	kमुक्त(emu->vmidi);
	emu->vmidi = शून्य;
	वापस 0;
पूर्ण
