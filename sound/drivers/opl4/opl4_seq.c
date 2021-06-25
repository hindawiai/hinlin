<शैली गुरु>
/*
 * OPL4 sequencer functions
 *
 * Copyright (c) 2003 by Clemens Ladisch <clemens@ladisch.de>
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. The name of the author may not be used to enकरोrse or promote products
 *    derived from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed and/or modअगरied under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE FOR
 * ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#समावेश "opl4_local.h"
#समावेश <linux/init.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/module.h>
#समावेश <sound/initval.h>

MODULE_AUTHOR("Clemens Ladisch <clemens@ladisch.de>");
MODULE_DESCRIPTION("OPL4 wavetable synth driver");
MODULE_LICENSE("Dual BSD/GPL");

पूर्णांक volume_boost = 8;

module_param(volume_boost, पूर्णांक, 0644);
MODULE_PARM_DESC(volume_boost, "Additional volume for OPL4 wavetable sounds.");

अटल पूर्णांक snd_opl4_seq_use_inc(काष्ठा snd_opl4 *opl4)
अणु
	अगर (!try_module_get(opl4->card->module))
		वापस -EFAULT;
	वापस 0;
पूर्ण

अटल व्योम snd_opl4_seq_use_dec(काष्ठा snd_opl4 *opl4)
अणु
	module_put(opl4->card->module);
पूर्ण

अटल पूर्णांक snd_opl4_seq_use(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info)
अणु
	काष्ठा snd_opl4 *opl4 = निजी_data;
	पूर्णांक err;

	mutex_lock(&opl4->access_mutex);

	अगर (opl4->used) अणु
		mutex_unlock(&opl4->access_mutex);
		वापस -EBUSY;
	पूर्ण
	opl4->used++;

	अगर (info->sender.client != SNDRV_SEQ_CLIENT_SYSTEM) अणु
		err = snd_opl4_seq_use_inc(opl4);
		अगर (err < 0) अणु
			mutex_unlock(&opl4->access_mutex);
			वापस err;
		पूर्ण
	पूर्ण

	mutex_unlock(&opl4->access_mutex);

	snd_opl4_synth_reset(opl4);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl4_seq_unuse(व्योम *निजी_data, काष्ठा snd_seq_port_subscribe *info)
अणु
	काष्ठा snd_opl4 *opl4 = निजी_data;

	snd_opl4_synth_shutकरोwn(opl4);

	mutex_lock(&opl4->access_mutex);
	opl4->used--;
	mutex_unlock(&opl4->access_mutex);

	अगर (info->sender.client != SNDRV_SEQ_CLIENT_SYSTEM)
		snd_opl4_seq_use_dec(opl4);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_midi_op opl4_ops = अणु
	.note_on =		snd_opl4_note_on,
	.note_off =		snd_opl4_note_off,
	.note_terminate =	snd_opl4_terminate_note,
	.control =		snd_opl4_control,
	.sysex =		snd_opl4_sysex,
पूर्ण;

अटल पूर्णांक snd_opl4_seq_event_input(काष्ठा snd_seq_event *ev, पूर्णांक direct,
				    व्योम *निजी_data, पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_opl4 *opl4 = निजी_data;

	snd_midi_process_event(&opl4_ops, ev, opl4->chset);
	वापस 0;
पूर्ण

अटल व्योम snd_opl4_seq_मुक्त_port(व्योम *निजी_data)
अणु
	काष्ठा snd_opl4 *opl4 = निजी_data;

	snd_midi_channel_मुक्त_set(opl4->chset);
पूर्ण

अटल पूर्णांक snd_opl4_seq_probe(काष्ठा device *_dev)
अणु
	काष्ठा snd_seq_device *dev = to_seq_dev(_dev);
	काष्ठा snd_opl4 *opl4;
	पूर्णांक client;
	काष्ठा snd_seq_port_callback pcallbacks;

	opl4 = *(काष्ठा snd_opl4 **)SNDRV_SEQ_DEVICE_ARGPTR(dev);
	अगर (!opl4)
		वापस -EINVAL;

	अगर (snd_yrw801_detect(opl4) < 0)
		वापस -ENODEV;

	opl4->chset = snd_midi_channel_alloc_set(16);
	अगर (!opl4->chset)
		वापस -ENOMEM;
	opl4->chset->निजी_data = opl4;

	/* allocate new client */
	client = snd_seq_create_kernel_client(opl4->card, opl4->seq_dev_num,
					      "OPL4 Wavetable");
	अगर (client < 0) अणु
		snd_midi_channel_मुक्त_set(opl4->chset);
		वापस client;
	पूर्ण
	opl4->seq_client = client;
	opl4->chset->client = client;

	/* create new port */
	स_रखो(&pcallbacks, 0, माप(pcallbacks));
	pcallbacks.owner = THIS_MODULE;
	pcallbacks.use = snd_opl4_seq_use;
	pcallbacks.unuse = snd_opl4_seq_unuse;
	pcallbacks.event_input = snd_opl4_seq_event_input;
	pcallbacks.निजी_मुक्त = snd_opl4_seq_मुक्त_port;
	pcallbacks.निजी_data = opl4;

	opl4->chset->port = snd_seq_event_port_attach(client, &pcallbacks,
						      SNDRV_SEQ_PORT_CAP_WRITE |
						      SNDRV_SEQ_PORT_CAP_SUBS_WRITE,
						      SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC |
						      SNDRV_SEQ_PORT_TYPE_MIDI_GM |
						      SNDRV_SEQ_PORT_TYPE_HARDWARE |
						      SNDRV_SEQ_PORT_TYPE_SYNTHESIZER,
						      16, 24,
						      "OPL4 Wavetable Port");
	अगर (opl4->chset->port < 0) अणु
		पूर्णांक err = opl4->chset->port;
		snd_midi_channel_मुक्त_set(opl4->chset);
		snd_seq_delete_kernel_client(client);
		opl4->seq_client = -1;
		वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_opl4_seq_हटाओ(काष्ठा device *_dev)
अणु
	काष्ठा snd_seq_device *dev = to_seq_dev(_dev);
	काष्ठा snd_opl4 *opl4;

	opl4 = *(काष्ठा snd_opl4 **)SNDRV_SEQ_DEVICE_ARGPTR(dev);
	अगर (!opl4)
		वापस -EINVAL;

	अगर (opl4->seq_client >= 0) अणु
		snd_seq_delete_kernel_client(opl4->seq_client);
		opl4->seq_client = -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा snd_seq_driver opl4_seq_driver = अणु
	.driver = अणु
		.name = KBUILD_MODNAME,
		.probe = snd_opl4_seq_probe,
		.हटाओ = snd_opl4_seq_हटाओ,
	पूर्ण,
	.id = SNDRV_SEQ_DEV_ID_OPL4,
	.argsize = माप(काष्ठा snd_opl4 *),
पूर्ण;

module_snd_seq_driver(opl4_seq_driver);
