<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (c) by Uros Bizjak <uros@kss-loka.si>
 *
 *  Midi Sequencer पूर्णांकerface routines क्रम OPL2/OPL3/OPL4 FM
 *
 *  OPL2/3 FM instrument loader:
 *   alsa-tools/seq/sbiload/
 */

#समावेश "opl3_voice.h"
#समावेश <linux/init.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/module.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Uros Bizjak <uros@kss-loka.si>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ALSA driver for OPL3 FM synth");

bool use_पूर्णांकernal_drums = 0;
module_param(use_पूर्णांकernal_drums, bool, 0444);
MODULE_PARM_DESC(use_पूर्णांकernal_drums, "Enable internal OPL2/3 drums.");

पूर्णांक snd_opl3_synth_use_inc(काष्ठा snd_opl3 * opl3)
अणु
	अगर (!try_module_get(opl3->card->module))
		वापस -EFAULT;
	वापस 0;

पूर्ण

व्योम snd_opl3_synth_use_dec(काष्ठा snd_opl3 * opl3)
अणु
	module_put(opl3->card->module);
पूर्ण

पूर्णांक snd_opl3_synth_setup(काष्ठा snd_opl3 * opl3)
अणु
	पूर्णांक idx;
	काष्ठा snd_hwdep *hwdep = opl3->hwdep;

	mutex_lock(&hwdep->खोलो_mutex);
	अगर (hwdep->used) अणु
		mutex_unlock(&hwdep->खोलो_mutex);
		वापस -EBUSY;
	पूर्ण
	hwdep->used++;
	mutex_unlock(&hwdep->खोलो_mutex);

	snd_opl3_reset(opl3);

	क्रम (idx = 0; idx < MAX_OPL3_VOICES; idx++) अणु
		opl3->voices[idx].state = SNDRV_OPL3_ST_OFF;
		opl3->voices[idx].समय = 0;
		opl3->voices[idx].keyon_reg = 0x00;
	पूर्ण
	opl3->use_समय = 0;
	opl3->connection_reg = 0x00;
	अगर (opl3->hardware >= OPL3_HW_OPL3) अणु
		/* Clear 4-op connections */
		opl3->command(opl3, OPL3_RIGHT | OPL3_REG_CONNECTION_SELECT,
				 opl3->connection_reg);
		opl3->max_voices = MAX_OPL3_VOICES;
	पूर्ण
	वापस 0;
पूर्ण

व्योम snd_opl3_synth_cleanup(काष्ठा snd_opl3 * opl3)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा snd_hwdep *hwdep;

	/* Stop प्रणाली समयr */
	spin_lock_irqsave(&opl3->sys_समयr_lock, flags);
	अगर (opl3->sys_समयr_status) अणु
		del_समयr(&opl3->tlist);
		opl3->sys_समयr_status = 0;
	पूर्ण
	spin_unlock_irqrestore(&opl3->sys_समयr_lock, flags);

	snd_opl3_reset(opl3);
	hwdep = opl3->hwdep;
	mutex_lock(&hwdep->खोलो_mutex);
	hwdep->used--;
	mutex_unlock(&hwdep->खोलो_mutex);
	wake_up(&hwdep->खोलो_रुको);
पूर्ण

अटल पूर्णांक snd_opl3_synth_use(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe * info)
अणु
	काष्ठा snd_opl3 *opl3 = निजी_data;
	पूर्णांक err;

	अगर ((err = snd_opl3_synth_setup(opl3)) < 0)
		वापस err;

	अगर (use_पूर्णांकernal_drums) अणु
		/* Percussion mode */
		opl3->voices[6].state = opl3->voices[7].state = 
			opl3->voices[8].state = SNDRV_OPL3_ST_NOT_AVAIL;
		snd_opl3_load_drums(opl3);
		opl3->drum_reg = OPL3_PERCUSSION_ENABLE;
		opl3->command(opl3, OPL3_LEFT | OPL3_REG_PERCUSSION, opl3->drum_reg);
	पूर्ण अन्यथा अणु
		opl3->drum_reg = 0x00;
	पूर्ण

	अगर (info->sender.client != SNDRV_SEQ_CLIENT_SYSTEM) अणु
		अगर ((err = snd_opl3_synth_use_inc(opl3)) < 0)
			वापस err;
	पूर्ण
	opl3->synth_mode = SNDRV_OPL3_MODE_SEQ;
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl3_synth_unuse(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe * info)
अणु
	काष्ठा snd_opl3 *opl3 = निजी_data;

	snd_opl3_synth_cleanup(opl3);

	अगर (info->sender.client != SNDRV_SEQ_CLIENT_SYSTEM)
		snd_opl3_synth_use_dec(opl3);
	वापस 0;
पूर्ण

/*
 * MIDI emulation चालकs
 */
स्थिर काष्ठा snd_midi_op opl3_ops = अणु
	.note_on =		snd_opl3_note_on,
	.note_off =		snd_opl3_note_off,
	.key_press =		snd_opl3_key_press,
	.note_terminate =	snd_opl3_terminate_note,
	.control =		snd_opl3_control,
	.nrpn =			snd_opl3_nrpn,
	.sysex =		snd_opl3_sysex,
पूर्ण;

अटल पूर्णांक snd_opl3_synth_event_input(काष्ठा snd_seq_event * ev, पूर्णांक direct,
				      व्योम *निजी_data, पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_opl3 *opl3 = निजी_data;

	snd_midi_process_event(&opl3_ops, ev, opl3->chset);
	वापस 0;
पूर्ण

/* ------------------------------ */

अटल व्योम snd_opl3_synth_मुक्त_port(व्योम *निजी_data)
अणु
	काष्ठा snd_opl3 *opl3 = निजी_data;

	snd_midi_channel_मुक्त_set(opl3->chset);
पूर्ण

अटल पूर्णांक snd_opl3_synth_create_port(काष्ठा snd_opl3 * opl3)
अणु
	काष्ठा snd_seq_port_callback callbacks;
	अक्षर name[32];
	पूर्णांक voices, opl_ver;

	voices = (opl3->hardware < OPL3_HW_OPL3) ?
		MAX_OPL2_VOICES : MAX_OPL3_VOICES;
	opl3->chset = snd_midi_channel_alloc_set(16);
	अगर (opl3->chset == शून्य)
		वापस -ENOMEM;
	opl3->chset->निजी_data = opl3;

	स_रखो(&callbacks, 0, माप(callbacks));
	callbacks.owner = THIS_MODULE;
	callbacks.use = snd_opl3_synth_use;
	callbacks.unuse = snd_opl3_synth_unuse;
	callbacks.event_input = snd_opl3_synth_event_input;
	callbacks.निजी_मुक्त = snd_opl3_synth_मुक्त_port;
	callbacks.निजी_data = opl3;

	opl_ver = (opl3->hardware & OPL3_HW_MASK) >> 8;
	प्र_लिखो(name, "OPL%i FM Port", opl_ver);

	opl3->chset->client = opl3->seq_client;
	opl3->chset->port = snd_seq_event_port_attach(opl3->seq_client, &callbacks,
						      SNDRV_SEQ_PORT_CAP_WRITE |
						      SNDRV_SEQ_PORT_CAP_SUBS_WRITE,
						      SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC |
						      SNDRV_SEQ_PORT_TYPE_MIDI_GM |
						      SNDRV_SEQ_PORT_TYPE_सूचीECT_SAMPLE |
						      SNDRV_SEQ_PORT_TYPE_HARDWARE |
						      SNDRV_SEQ_PORT_TYPE_SYNTHESIZER,
						      16, voices,
						      name);
	अगर (opl3->chset->port < 0) अणु
		पूर्णांक port;
		port = opl3->chset->port;
		snd_midi_channel_मुक्त_set(opl3->chset);
		वापस port;
	पूर्ण
	वापस 0;
पूर्ण

/* ------------------------------ */

अटल पूर्णांक snd_opl3_seq_probe(काष्ठा device *_dev)
अणु
	काष्ठा snd_seq_device *dev = to_seq_dev(_dev);
	काष्ठा snd_opl3 *opl3;
	पूर्णांक client, err;
	अक्षर name[32];
	पूर्णांक opl_ver;

	opl3 = *(काष्ठा snd_opl3 **)SNDRV_SEQ_DEVICE_ARGPTR(dev);
	अगर (opl3 == शून्य)
		वापस -EINVAL;

	spin_lock_init(&opl3->voice_lock);

	opl3->seq_client = -1;

	/* allocate new client */
	opl_ver = (opl3->hardware & OPL3_HW_MASK) >> 8;
	प्र_लिखो(name, "OPL%i FM synth", opl_ver);
	client = opl3->seq_client =
		snd_seq_create_kernel_client(opl3->card, opl3->seq_dev_num,
					     name);
	अगर (client < 0)
		वापस client;

	अगर ((err = snd_opl3_synth_create_port(opl3)) < 0) अणु
		snd_seq_delete_kernel_client(client);
		opl3->seq_client = -1;
		वापस err;
	पूर्ण

	/* setup प्रणाली समयr */
	समयr_setup(&opl3->tlist, snd_opl3_समयr_func, 0);
	spin_lock_init(&opl3->sys_समयr_lock);
	opl3->sys_समयr_status = 0;

#अगर IS_ENABLED(CONFIG_SND_SEQUENCER_OSS)
	snd_opl3_init_seq_oss(opl3, name);
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl3_seq_हटाओ(काष्ठा device *_dev)
अणु
	काष्ठा snd_seq_device *dev = to_seq_dev(_dev);
	काष्ठा snd_opl3 *opl3;

	opl3 = *(काष्ठा snd_opl3 **)SNDRV_SEQ_DEVICE_ARGPTR(dev);
	अगर (opl3 == शून्य)
		वापस -EINVAL;

#अगर IS_ENABLED(CONFIG_SND_SEQUENCER_OSS)
	snd_opl3_मुक्त_seq_oss(opl3);
#पूर्ण_अगर
	अगर (opl3->seq_client >= 0) अणु
		snd_seq_delete_kernel_client(opl3->seq_client);
		opl3->seq_client = -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा snd_seq_driver opl3_seq_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.probe = snd_opl3_seq_probe,
		.हटाओ = snd_opl3_seq_हटाओ,
	पूर्ण,
	.id = SNDRV_SEQ_DEV_ID_OPL3,
	.argsize = माप(काष्ठा snd_opl3 *),
पूर्ण;

module_snd_seq_driver(opl3_seq_driver);
