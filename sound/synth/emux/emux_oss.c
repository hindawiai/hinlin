<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Interface क्रम OSS sequencer emulation
 *
 *  Copyright (C) 1999 Takashi Iwai <tiwai@suse.de>
 *
 * Changes
 * 19990227   Steve Ratclअगरfe   Made separate file and merged in latest
 * 				midi emulation.
 */


#समावेश <linux/export.h>
#समावेश <linux/uaccess.h>
#समावेश <sound/core.h>
#समावेश "emux_voice.h"
#समावेश <sound/asoundef.h>

अटल पूर्णांक snd_emux_खोलो_seq_oss(काष्ठा snd_seq_oss_arg *arg, व्योम *closure);
अटल पूर्णांक snd_emux_बंद_seq_oss(काष्ठा snd_seq_oss_arg *arg);
अटल पूर्णांक snd_emux_ioctl_seq_oss(काष्ठा snd_seq_oss_arg *arg, अचिन्हित पूर्णांक cmd,
				  अचिन्हित दीर्घ ioarg);
अटल पूर्णांक snd_emux_load_patch_seq_oss(काष्ठा snd_seq_oss_arg *arg, पूर्णांक क्रमmat,
				       स्थिर अक्षर __user *buf, पूर्णांक offs, पूर्णांक count);
अटल पूर्णांक snd_emux_reset_seq_oss(काष्ठा snd_seq_oss_arg *arg);
अटल पूर्णांक snd_emux_event_oss_input(काष्ठा snd_seq_event *ev, पूर्णांक direct,
				    व्योम *निजी, पूर्णांक atomic, पूर्णांक hop);
अटल व्योम reset_port_mode(काष्ठा snd_emux_port *port, पूर्णांक midi_mode);
अटल व्योम emuspec_control(काष्ठा snd_emux *emu, काष्ठा snd_emux_port *port,
			    पूर्णांक cmd, अचिन्हित अक्षर *event, पूर्णांक atomic, पूर्णांक hop);
अटल व्योम gusspec_control(काष्ठा snd_emux *emu, काष्ठा snd_emux_port *port,
			    पूर्णांक cmd, अचिन्हित अक्षर *event, पूर्णांक atomic, पूर्णांक hop);
अटल व्योम fake_event(काष्ठा snd_emux *emu, काष्ठा snd_emux_port *port,
		       पूर्णांक ch, पूर्णांक param, पूर्णांक val, पूर्णांक atomic, पूर्णांक hop);

/* चालकs */
अटल स्थिर काष्ठा snd_seq_oss_callback oss_callback = अणु
	.owner = THIS_MODULE,
	.खोलो = snd_emux_खोलो_seq_oss,
	.बंद = snd_emux_बंद_seq_oss,
	.ioctl = snd_emux_ioctl_seq_oss,
	.load_patch = snd_emux_load_patch_seq_oss,
	.reset = snd_emux_reset_seq_oss,
पूर्ण;


/*
 * रेजिस्टर OSS synth
 */

व्योम
snd_emux_init_seq_oss(काष्ठा snd_emux *emu)
अणु
	काष्ठा snd_seq_oss_reg *arg;
	काष्ठा snd_seq_device *dev;

	/* using device#1 here क्रम aव्योमing conflicts with OPL3 */
	अगर (snd_seq_device_new(emu->card, 1, SNDRV_SEQ_DEV_ID_OSS,
			       माप(काष्ठा snd_seq_oss_reg), &dev) < 0)
		वापस;

	emu->oss_synth = dev;
	म_नकल(dev->name, emu->name);
	arg = SNDRV_SEQ_DEVICE_ARGPTR(dev);
	arg->type = SYNTH_TYPE_SAMPLE;
	arg->subtype = SAMPLE_TYPE_AWE32;
	arg->nvoices = emu->max_voices;
	arg->oper = oss_callback;
	arg->निजी_data = emu;

	/* रेजिस्टर to OSS synth table */
	snd_device_रेजिस्टर(emu->card, dev);
पूर्ण


/*
 * unरेजिस्टर
 */
व्योम
snd_emux_detach_seq_oss(काष्ठा snd_emux *emu)
अणु
	अगर (emu->oss_synth) अणु
		snd_device_मुक्त(emu->card, emu->oss_synth);
		emu->oss_synth = शून्य;
	पूर्ण
पूर्ण


/* use port number as a unique soundfont client number */
#घोषणा SF_CLIENT_NO(p)	((p) + 0x1000)

/*
 * खोलो port क्रम OSS sequencer
 */
अटल पूर्णांक
snd_emux_खोलो_seq_oss(काष्ठा snd_seq_oss_arg *arg, व्योम *closure)
अणु
	काष्ठा snd_emux *emu;
	काष्ठा snd_emux_port *p;
	काष्ठा snd_seq_port_callback callback;
	अक्षर क्षणिकe[64];

	emu = closure;
	अगर (snd_BUG_ON(!arg || !emu))
		वापस -ENXIO;

	अगर (!snd_emux_inc_count(emu))
		वापस -EFAULT;

	स_रखो(&callback, 0, माप(callback));
	callback.owner = THIS_MODULE;
	callback.event_input = snd_emux_event_oss_input;

	प्र_लिखो(क्षणिकe, "%s OSS Port", emu->name);
	p = snd_emux_create_port(emu, क्षणिकe, 32,
				 1, &callback);
	अगर (p == शून्य) अणु
		snd_prपूर्णांकk(KERN_ERR "can't create port\n");
		snd_emux_dec_count(emu);
		वापस -ENOMEM;
	पूर्ण

	/* fill the argument data */
	arg->निजी_data = p;
	arg->addr.client = p->chset.client;
	arg->addr.port = p->chset.port;
	p->oss_arg = arg;

	reset_port_mode(p, arg->seq_mode);

	snd_emux_reset_port(p);
	वापस 0;
पूर्ण


#घोषणा DEFAULT_DRUM_FLAGS	((1<<9) | (1<<25))

/*
 * reset port mode
 */
अटल व्योम
reset_port_mode(काष्ठा snd_emux_port *port, पूर्णांक midi_mode)
अणु
	अगर (midi_mode) अणु
		port->port_mode = SNDRV_EMUX_PORT_MODE_OSS_MIDI;
		port->drum_flags = DEFAULT_DRUM_FLAGS;
		port->volume_atten = 0;
		port->oss_arg->event_passing = SNDRV_SEQ_OSS_PROCESS_KEYPRESS;
	पूर्ण अन्यथा अणु
		port->port_mode = SNDRV_EMUX_PORT_MODE_OSS_SYNTH;
		port->drum_flags = 0;
		port->volume_atten = 32;
		port->oss_arg->event_passing = SNDRV_SEQ_OSS_PROCESS_EVENTS;
	पूर्ण
पूर्ण


/*
 * बंद port
 */
अटल पूर्णांक
snd_emux_बंद_seq_oss(काष्ठा snd_seq_oss_arg *arg)
अणु
	काष्ठा snd_emux *emu;
	काष्ठा snd_emux_port *p;

	अगर (snd_BUG_ON(!arg))
		वापस -ENXIO;
	p = arg->निजी_data;
	अगर (snd_BUG_ON(!p))
		वापस -ENXIO;

	emu = p->emu;
	अगर (snd_BUG_ON(!emu))
		वापस -ENXIO;

	snd_emux_sounds_off_all(p);
	snd_soundfont_बंद_check(emu->sflist, SF_CLIENT_NO(p->chset.port));
	snd_seq_event_port_detach(p->chset.client, p->chset.port);
	snd_emux_dec_count(emu);

	वापस 0;
पूर्ण


/*
 * load patch
 */
अटल पूर्णांक
snd_emux_load_patch_seq_oss(काष्ठा snd_seq_oss_arg *arg, पूर्णांक क्रमmat,
			    स्थिर अक्षर __user *buf, पूर्णांक offs, पूर्णांक count)
अणु
	काष्ठा snd_emux *emu;
	काष्ठा snd_emux_port *p;
	पूर्णांक rc;

	अगर (snd_BUG_ON(!arg))
		वापस -ENXIO;
	p = arg->निजी_data;
	अगर (snd_BUG_ON(!p))
		वापस -ENXIO;

	emu = p->emu;
	अगर (snd_BUG_ON(!emu))
		वापस -ENXIO;

	अगर (क्रमmat == GUS_PATCH)
		rc = snd_soundfont_load_guspatch(emu->sflist, buf, count,
						 SF_CLIENT_NO(p->chset.port));
	अन्यथा अगर (क्रमmat == SNDRV_OSS_SOUNDFONT_PATCH) अणु
		काष्ठा soundfont_patch_info patch;
		अगर (count < (पूर्णांक)माप(patch))
			वापस -EINVAL;
		अगर (copy_from_user(&patch, buf, माप(patch)))
			वापस -EFAULT;
		अगर (patch.type >= SNDRV_SFNT_LOAD_INFO &&
		    patch.type <= SNDRV_SFNT_PROBE_DATA)
			rc = snd_soundfont_load(emu->sflist, buf, count, SF_CLIENT_NO(p->chset.port));
		अन्यथा अणु
			अगर (emu->ops.load_fx)
				rc = emu->ops.load_fx(emu, patch.type, patch.optarg, buf, count);
			अन्यथा
				rc = -EINVAL;
		पूर्ण
	पूर्ण अन्यथा
		rc = 0;
	वापस rc;
पूर्ण


/*
 * ioctl
 */
अटल पूर्णांक
snd_emux_ioctl_seq_oss(काष्ठा snd_seq_oss_arg *arg, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ ioarg)
अणु
	काष्ठा snd_emux_port *p;
	काष्ठा snd_emux *emu;

	अगर (snd_BUG_ON(!arg))
		वापस -ENXIO;
	p = arg->निजी_data;
	अगर (snd_BUG_ON(!p))
		वापस -ENXIO;

	emu = p->emu;
	अगर (snd_BUG_ON(!emu))
		वापस -ENXIO;

	चयन (cmd) अणु
	हाल SNDCTL_SEQ_RESETSAMPLES:
		snd_soundfont_हटाओ_samples(emu->sflist);
		वापस 0;
			
	हाल SNDCTL_SYNTH_MEMAVL:
		अगर (emu->memhdr)
			वापस snd_util_mem_avail(emu->memhdr);
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण


/*
 * reset device
 */
अटल पूर्णांक
snd_emux_reset_seq_oss(काष्ठा snd_seq_oss_arg *arg)
अणु
	काष्ठा snd_emux_port *p;

	अगर (snd_BUG_ON(!arg))
		वापस -ENXIO;
	p = arg->निजी_data;
	अगर (snd_BUG_ON(!p))
		वापस -ENXIO;
	snd_emux_reset_port(p);
	वापस 0;
पूर्ण


/*
 * receive raw events: only SEQ_PRIVATE is accepted.
 */
अटल पूर्णांक
snd_emux_event_oss_input(काष्ठा snd_seq_event *ev, पूर्णांक direct, व्योम *निजी_data,
			 पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_emux *emu;
	काष्ठा snd_emux_port *p;
	अचिन्हित अक्षर cmd, *data;

	p = निजी_data;
	अगर (snd_BUG_ON(!p))
		वापस -EINVAL;
	emu = p->emu;
	अगर (snd_BUG_ON(!emu))
		वापस -EINVAL;
	अगर (ev->type != SNDRV_SEQ_EVENT_OSS)
		वापस snd_emux_event_input(ev, direct, निजी_data, atomic, hop);

	data = ev->data.raw8.d;
	/* only SEQ_PRIVATE is accepted */
	अगर (data[0] != 0xfe)
		वापस 0;
	cmd = data[2] & _EMUX_OSS_MODE_VALUE_MASK;
	अगर (data[2] & _EMUX_OSS_MODE_FLAG)
		emuspec_control(emu, p, cmd, data, atomic, hop);
	अन्यथा
		gusspec_control(emu, p, cmd, data, atomic, hop);
	वापस 0;
पूर्ण


/*
 * OSS/AWE driver specअगरic h/w controls
 */
अटल व्योम
emuspec_control(काष्ठा snd_emux *emu, काष्ठा snd_emux_port *port, पूर्णांक cmd,
		अचिन्हित अक्षर *event, पूर्णांक atomic, पूर्णांक hop)
अणु
	पूर्णांक voice;
	अचिन्हित लघु p1;
	लघु p2;
	पूर्णांक i;
	काष्ठा snd_midi_channel *chan;

	voice = event[3];
	अगर (voice < 0 || voice >= port->chset.max_channels)
		chan = शून्य;
	अन्यथा
		chan = &port->chset.channels[voice];

	p1 = *(अचिन्हित लघु *) &event[4];
	p2 = *(लघु *) &event[6];

	चयन (cmd) अणु
#अगर 0 /* करोn't करो this atomically */
	हाल _EMUX_OSS_REMOVE_LAST_SAMPLES:
		snd_soundfont_हटाओ_unlocked(emu->sflist);
		अवरोध;
#पूर्ण_अगर
	हाल _EMUX_OSS_SEND_EFFECT:
		अगर (chan)
			snd_emux_send_effect_oss(port, chan, p1, p2);
		अवरोध;
		
	हाल _EMUX_OSS_TERMINATE_ALL:
		snd_emux_terminate_all(emu);
		अवरोध;

	हाल _EMUX_OSS_TERMINATE_CHANNEL:
		/*snd_emux_mute_channel(emu, chan);*/
		अवरोध;
	हाल _EMUX_OSS_RESET_CHANNEL:
		/*snd_emux_channel_init(chset, chan);*/
		अवरोध;

	हाल _EMUX_OSS_RELEASE_ALL:
		fake_event(emu, port, voice, MIDI_CTL_ALL_NOTES_OFF, 0, atomic, hop);
		अवरोध;
	हाल _EMUX_OSS_NOTखातापूर्णF_ALL:
		fake_event(emu, port, voice, MIDI_CTL_ALL_SOUNDS_OFF, 0, atomic, hop);
		अवरोध;

	हाल _EMUX_OSS_INITIAL_VOLUME:
		अगर (p2) अणु
			port->volume_atten = (लघु)p1;
			snd_emux_update_port(port, SNDRV_EMUX_UPDATE_VOLUME);
		पूर्ण
		अवरोध;

	हाल _EMUX_OSS_CHN_PRESSURE:
		अगर (chan) अणु
			chan->midi_pressure = p1;
			snd_emux_update_channel(port, chan, SNDRV_EMUX_UPDATE_FMMOD|SNDRV_EMUX_UPDATE_FM2FRQ2);
		पूर्ण
		अवरोध;

	हाल _EMUX_OSS_CHANNEL_MODE:
		reset_port_mode(port, p1);
		snd_emux_reset_port(port);
		अवरोध;

	हाल _EMUX_OSS_DRUM_CHANNELS:
		port->drum_flags = *(अचिन्हित पूर्णांक*)&event[4];
		क्रम (i = 0; i < port->chset.max_channels; i++) अणु
			chan = &port->chset.channels[i];
			chan->drum_channel = ((port->drum_flags >> i) & 1) ? 1 : 0;
		पूर्ण
		अवरोध;

	हाल _EMUX_OSS_MISC_MODE:
		अगर (p1 < EMUX_MD_END)
			port->ctrls[p1] = p2;
		अवरोध;
	हाल _EMUX_OSS_DEBUG_MODE:
		अवरोध;

	शेष:
		अगर (emu->ops.oss_ioctl)
			emu->ops.oss_ioctl(emu, cmd, p1, p2);
		अवरोध;
	पूर्ण
पूर्ण

/*
 * GUS specअगरic h/w controls
 */

#समावेश <linux/ultrasound.h>

अटल व्योम
gusspec_control(काष्ठा snd_emux *emu, काष्ठा snd_emux_port *port, पूर्णांक cmd,
		अचिन्हित अक्षर *event, पूर्णांक atomic, पूर्णांक hop)
अणु
	पूर्णांक voice;
	अचिन्हित लघु p1;
	पूर्णांक pदीर्घ;
	काष्ठा snd_midi_channel *chan;

	अगर (port->port_mode != SNDRV_EMUX_PORT_MODE_OSS_SYNTH)
		वापस;
	अगर (cmd == _GUS_NUMVOICES)
		वापस;
	voice = event[3];
	अगर (voice < 0 || voice >= port->chset.max_channels)
		वापस;

	chan = &port->chset.channels[voice];

	p1 = *(अचिन्हित लघु *) &event[4];
	pदीर्घ = *(पूर्णांक*) &event[4];

	चयन (cmd) अणु
	हाल _GUS_VOICESAMPLE:
		chan->midi_program = p1;
		वापस;

	हाल _GUS_VOICEBALA:
		/* 0 to 15 --> 0 to 127 */
		chan->control[MIDI_CTL_MSB_PAN] = (पूर्णांक)p1 << 3;
		snd_emux_update_channel(port, chan, SNDRV_EMUX_UPDATE_PAN);
		वापस;

	हाल _GUS_VOICEVOL:
	हाल _GUS_VOICEVOL2:
		/* not supported yet */
		वापस;

	हाल _GUS_RAMPRANGE:
	हाल _GUS_RAMPRATE:
	हाल _GUS_RAMPMODE:
	हाल _GUS_RAMPON:
	हाल _GUS_RAMPOFF:
		/* volume ramping not supported */
		वापस;

	हाल _GUS_VOLUME_SCALE:
		वापस;

	हाल _GUS_VOICE_POS:
#अगर_घोषित SNDRV_EMUX_USE_RAW_EFFECT
		snd_emux_send_effect(port, chan, EMUX_FX_SAMPLE_START,
				     (लघु)(pदीर्घ & 0x7fff),
				     EMUX_FX_FLAG_SET);
		snd_emux_send_effect(port, chan, EMUX_FX_COARSE_SAMPLE_START,
				     (pदीर्घ >> 15) & 0xffff,
				     EMUX_FX_FLAG_SET);
#पूर्ण_अगर
		वापस;
	पूर्ण
पूर्ण


/*
 * send an event to midi emulation
 */
अटल व्योम
fake_event(काष्ठा snd_emux *emu, काष्ठा snd_emux_port *port, पूर्णांक ch, पूर्णांक param, पूर्णांक val, पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_seq_event ev;
	स_रखो(&ev, 0, माप(ev));
	ev.type = SNDRV_SEQ_EVENT_CONTROLLER;
	ev.data.control.channel = ch;
	ev.data.control.param = param;
	ev.data.control.value = val;
	snd_emux_event_input(&ev, 0, port, atomic, hop);
पूर्ण
