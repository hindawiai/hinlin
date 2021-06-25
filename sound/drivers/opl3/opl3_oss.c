<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Interface क्रम OSS sequencer emulation
 *
 *  Copyright (C) 2000 Uros Bizjak <uros@kss-loka.si>
 */

#समावेश <linux/export.h>
#समावेश "opl3_voice.h"

अटल पूर्णांक snd_opl3_खोलो_seq_oss(काष्ठा snd_seq_oss_arg *arg, व्योम *closure);
अटल पूर्णांक snd_opl3_बंद_seq_oss(काष्ठा snd_seq_oss_arg *arg);
अटल पूर्णांक snd_opl3_ioctl_seq_oss(काष्ठा snd_seq_oss_arg *arg, अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ ioarg);
अटल पूर्णांक snd_opl3_load_patch_seq_oss(काष्ठा snd_seq_oss_arg *arg, पूर्णांक क्रमmat, स्थिर अक्षर __user *buf, पूर्णांक offs, पूर्णांक count);
अटल पूर्णांक snd_opl3_reset_seq_oss(काष्ठा snd_seq_oss_arg *arg);

/* चालकs */

अटल स्थिर काष्ठा snd_seq_oss_callback oss_callback = अणु
	.owner = 	THIS_MODULE,
	.खोलो =		snd_opl3_खोलो_seq_oss,
	.बंद =	snd_opl3_बंद_seq_oss,
	.ioctl =	snd_opl3_ioctl_seq_oss,
	.load_patch =	snd_opl3_load_patch_seq_oss,
	.reset =	snd_opl3_reset_seq_oss,
पूर्ण;

अटल पूर्णांक snd_opl3_oss_event_input(काष्ठा snd_seq_event *ev, पूर्णांक direct,
				    व्योम *निजी_data, पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_opl3 *opl3 = निजी_data;

	अगर (ev->type != SNDRV_SEQ_EVENT_OSS)
		snd_midi_process_event(&opl3_ops, ev, opl3->oss_chset);
	वापस 0;
पूर्ण

/* ------------------------------ */

अटल व्योम snd_opl3_oss_मुक्त_port(व्योम *निजी_data)
अणु
	काष्ठा snd_opl3 *opl3 = निजी_data;

	snd_midi_channel_मुक्त_set(opl3->oss_chset);
पूर्ण

अटल पूर्णांक snd_opl3_oss_create_port(काष्ठा snd_opl3 * opl3)
अणु
	काष्ठा snd_seq_port_callback callbacks;
	अक्षर name[32];
	पूर्णांक voices, opl_ver;

	voices = (opl3->hardware < OPL3_HW_OPL3) ?
		MAX_OPL2_VOICES : MAX_OPL3_VOICES;
	opl3->oss_chset = snd_midi_channel_alloc_set(voices);
	अगर (opl3->oss_chset == शून्य)
		वापस -ENOMEM;
	opl3->oss_chset->निजी_data = opl3;

	स_रखो(&callbacks, 0, माप(callbacks));
	callbacks.owner = THIS_MODULE;
	callbacks.event_input = snd_opl3_oss_event_input;
	callbacks.निजी_मुक्त = snd_opl3_oss_मुक्त_port;
	callbacks.निजी_data = opl3;

	opl_ver = (opl3->hardware & OPL3_HW_MASK) >> 8;
	प्र_लिखो(name, "OPL%i OSS Port", opl_ver);

	opl3->oss_chset->client = opl3->seq_client;
	opl3->oss_chset->port = snd_seq_event_port_attach(opl3->seq_client, &callbacks,
							  SNDRV_SEQ_PORT_CAP_WRITE,
							  SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC |
							  SNDRV_SEQ_PORT_TYPE_MIDI_GM |
							  SNDRV_SEQ_PORT_TYPE_HARDWARE |
							  SNDRV_SEQ_PORT_TYPE_SYNTHESIZER,
							  voices, voices,
							  name);
	अगर (opl3->oss_chset->port < 0) अणु
		पूर्णांक port;
		port = opl3->oss_chset->port;
		snd_midi_channel_मुक्त_set(opl3->oss_chset);
		वापस port;
	पूर्ण
	वापस 0;
पूर्ण

/* ------------------------------ */

/* रेजिस्टर OSS synth */
व्योम snd_opl3_init_seq_oss(काष्ठा snd_opl3 *opl3, अक्षर *name)
अणु
	काष्ठा snd_seq_oss_reg *arg;
	काष्ठा snd_seq_device *dev;

	अगर (snd_seq_device_new(opl3->card, 0, SNDRV_SEQ_DEV_ID_OSS,
			       माप(काष्ठा snd_seq_oss_reg), &dev) < 0)
		वापस;

	opl3->oss_seq_dev = dev;
	strscpy(dev->name, name, माप(dev->name));
	arg = SNDRV_SEQ_DEVICE_ARGPTR(dev);
	arg->type = SYNTH_TYPE_FM;
	अगर (opl3->hardware < OPL3_HW_OPL3) अणु
		arg->subtype = FM_TYPE_ADLIB;
		arg->nvoices = MAX_OPL2_VOICES;
	पूर्ण अन्यथा अणु
		arg->subtype = FM_TYPE_OPL3;
		arg->nvoices = MAX_OPL3_VOICES;
	पूर्ण
	arg->oper = oss_callback;
	arg->निजी_data = opl3;

	अगर (snd_opl3_oss_create_port(opl3)) अणु
		/* रेजिस्टर to OSS synth table */
		snd_device_रेजिस्टर(opl3->card, dev);
	पूर्ण
पूर्ण

/* unरेजिस्टर */
व्योम snd_opl3_मुक्त_seq_oss(काष्ठा snd_opl3 *opl3)
अणु
	अगर (opl3->oss_seq_dev) अणु
		/* The instance should have been released in prior */
		opl3->oss_seq_dev = शून्य;
	पूर्ण
पूर्ण

/* ------------------------------ */

/* खोलो OSS sequencer */
अटल पूर्णांक snd_opl3_खोलो_seq_oss(काष्ठा snd_seq_oss_arg *arg, व्योम *closure)
अणु
	काष्ठा snd_opl3 *opl3 = closure;
	पूर्णांक err;

	अगर (snd_BUG_ON(!arg))
		वापस -ENXIO;

	अगर ((err = snd_opl3_synth_setup(opl3)) < 0)
		वापस err;

	/* fill the argument data */
	arg->निजी_data = opl3;
	arg->addr.client = opl3->oss_chset->client;
	arg->addr.port = opl3->oss_chset->port;

	अगर ((err = snd_opl3_synth_use_inc(opl3)) < 0)
		वापस err;

	opl3->synth_mode = SNDRV_OPL3_MODE_SYNTH;
	वापस 0;
पूर्ण

/* बंद OSS sequencer */
अटल पूर्णांक snd_opl3_बंद_seq_oss(काष्ठा snd_seq_oss_arg *arg)
अणु
	काष्ठा snd_opl3 *opl3;

	अगर (snd_BUG_ON(!arg))
		वापस -ENXIO;
	opl3 = arg->निजी_data;

	snd_opl3_synth_cleanup(opl3);

	snd_opl3_synth_use_dec(opl3);
	वापस 0;
पूर्ण

/* load patch */

/* from sound_config.h */
#घोषणा SBFM_MAXINSTR	256

अटल पूर्णांक snd_opl3_load_patch_seq_oss(काष्ठा snd_seq_oss_arg *arg, पूर्णांक क्रमmat,
				       स्थिर अक्षर __user *buf, पूर्णांक offs, पूर्णांक count)
अणु
	काष्ठा snd_opl3 *opl3;
	काष्ठा sbi_instrument sbi;
	अक्षर name[32];
	पूर्णांक err, type;

	अगर (snd_BUG_ON(!arg))
		वापस -ENXIO;
	opl3 = arg->निजी_data;

	अगर (क्रमmat == FM_PATCH)
		type = FM_PATCH_OPL2;
	अन्यथा अगर (क्रमmat == OPL3_PATCH)
		type = FM_PATCH_OPL3;
	अन्यथा
		वापस -EINVAL;

	अगर (count < (पूर्णांक)माप(sbi)) अणु
		snd_prपूर्णांकk(KERN_ERR "FM Error: Patch record too short\n");
		वापस -EINVAL;
	पूर्ण
	अगर (copy_from_user(&sbi, buf, माप(sbi)))
		वापस -EFAULT;

	अगर (sbi.channel < 0 || sbi.channel >= SBFM_MAXINSTR) अणु
		snd_prपूर्णांकk(KERN_ERR "FM Error: Invalid instrument number %d\n",
			   sbi.channel);
		वापस -EINVAL;
	पूर्ण

	स_रखो(name, 0, माप(name));
	प्र_लिखो(name, "Chan%d", sbi.channel);

	err = snd_opl3_load_patch(opl3, sbi.channel, 127, type, name, शून्य,
				  sbi.चालकs);
	अगर (err < 0)
		वापस err;

	वापस माप(sbi);
पूर्ण

/* ioctl */
अटल पूर्णांक snd_opl3_ioctl_seq_oss(काष्ठा snd_seq_oss_arg *arg, अचिन्हित पूर्णांक cmd,
				  अचिन्हित दीर्घ ioarg)
अणु
	अगर (snd_BUG_ON(!arg))
		वापस -ENXIO;
	चयन (cmd) अणु
		हाल SNDCTL_FM_LOAD_INSTR:
			snd_prपूर्णांकk(KERN_ERR "OPL3: "
				   "Obsolete ioctl(SNDCTL_FM_LOAD_INSTR) used. "
				   "Fix the program.\n");
			वापस -EINVAL;

		हाल SNDCTL_SYNTH_MEMAVL:
			वापस 0x7fffffff;

		हाल SNDCTL_FM_4OP_ENABLE:
			// handled स्वतःmatically by OPL instrument type
			वापस 0;

		शेष:
			वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

/* reset device */
अटल पूर्णांक snd_opl3_reset_seq_oss(काष्ठा snd_seq_oss_arg *arg)
अणु
	अगर (snd_BUG_ON(!arg))
		वापस -ENXIO;

	वापस 0;
पूर्ण
