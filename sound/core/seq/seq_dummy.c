<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * ALSA sequencer MIDI-through client
 * Copyright (c) 1999-2000 by Takashi Iwai <tiwai@suse.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश "seq_clientmgr.h"
#समावेश <sound/initval.h>
#समावेश <sound/asoundef.h>

/*

  Sequencer MIDI-through client

  This gives a simple midi-through client.  All the normal input events
  are redirected to output port immediately.
  The routing can be करोne via aconnect program in alsa-utils.

  Each client has a अटल client number 62 (= SNDRV_SEQ_CLIENT_DUMMY).
  If you want to स्वतः-load this module, you may add the following alias
  in your /etc/conf.modules file.

	alias snd-seq-client-62  snd-seq-dummy

  The module is loaded on demand क्रम client 62, or /proc/asound/seq/
  is accessed.  If you करोn't need this module to be loaded, alias
  snd-seq-client-62 as "off".  This will help modprobe.

  The number of ports to be created can be specअगरied via the module
  parameter "ports".  For example, to create four ports, add the
  following option in a configuration file under /etc/modprobe.d/:

	option snd-seq-dummy ports=4

  The model option "duplex=1" enables duplex operation to the port.
  In duplex mode, a pair of ports are created instead of single port,
  and events are tunneled between pair-ports.  For example, input to
  port A is sent to output port of another port B and vice versa.
  In duplex mode, each port has DUPLEX capability.

 */


MODULE_AUTHOR("Takashi Iwai <tiwai@suse.de>");
MODULE_DESCRIPTION("ALSA sequencer MIDI-through client");
MODULE_LICENSE("GPL");
MODULE_ALIAS("snd-seq-client-" __stringअगरy(SNDRV_SEQ_CLIENT_DUMMY));

अटल पूर्णांक ports = 1;
अटल bool duplex;

module_param(ports, पूर्णांक, 0444);
MODULE_PARM_DESC(ports, "number of ports to be created");
module_param(duplex, bool, 0444);
MODULE_PARM_DESC(duplex, "create DUPLEX ports");

काष्ठा snd_seq_dummy_port अणु
	पूर्णांक client;
	पूर्णांक port;
	पूर्णांक duplex;
	पूर्णांक connect;
पूर्ण;

अटल पूर्णांक my_client = -1;

/*
 * event input callback - just redirect events to subscribers
 */
अटल पूर्णांक
dummy_input(काष्ठा snd_seq_event *ev, पूर्णांक direct, व्योम *निजी_data,
	    पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_seq_dummy_port *p;
	काष्ठा snd_seq_event पंचांगpev;

	p = निजी_data;
	अगर (ev->source.client == SNDRV_SEQ_CLIENT_SYSTEM ||
	    ev->type == SNDRV_SEQ_EVENT_KERNEL_ERROR)
		वापस 0; /* ignore प्रणाली messages */
	पंचांगpev = *ev;
	अगर (p->duplex)
		पंचांगpev.source.port = p->connect;
	अन्यथा
		पंचांगpev.source.port = p->port;
	पंचांगpev.dest.client = SNDRV_SEQ_ADDRESS_SUBSCRIBERS;
	वापस snd_seq_kernel_client_dispatch(p->client, &पंचांगpev, atomic, hop);
पूर्ण

/*
 * मुक्त_निजी callback
 */
अटल व्योम
dummy_मुक्त(व्योम *निजी_data)
अणु
	kमुक्त(निजी_data);
पूर्ण

/*
 * create a port
 */
अटल काष्ठा snd_seq_dummy_port __init *
create_port(पूर्णांक idx, पूर्णांक type)
अणु
	काष्ठा snd_seq_port_info pinfo;
	काष्ठा snd_seq_port_callback pcb;
	काष्ठा snd_seq_dummy_port *rec;

	अगर ((rec = kzalloc(माप(*rec), GFP_KERNEL)) == शून्य)
		वापस शून्य;

	rec->client = my_client;
	rec->duplex = duplex;
	rec->connect = 0;
	स_रखो(&pinfo, 0, माप(pinfo));
	pinfo.addr.client = my_client;
	अगर (duplex)
		प्र_लिखो(pinfo.name, "Midi Through Port-%d:%c", idx,
			(type ? 'B' : 'A'));
	अन्यथा
		प्र_लिखो(pinfo.name, "Midi Through Port-%d", idx);
	pinfo.capability = SNDRV_SEQ_PORT_CAP_READ | SNDRV_SEQ_PORT_CAP_SUBS_READ;
	pinfo.capability |= SNDRV_SEQ_PORT_CAP_WRITE | SNDRV_SEQ_PORT_CAP_SUBS_WRITE;
	अगर (duplex)
		pinfo.capability |= SNDRV_SEQ_PORT_CAP_DUPLEX;
	pinfo.type = SNDRV_SEQ_PORT_TYPE_MIDI_GENERIC
		| SNDRV_SEQ_PORT_TYPE_SOFTWARE
		| SNDRV_SEQ_PORT_TYPE_PORT;
	स_रखो(&pcb, 0, माप(pcb));
	pcb.owner = THIS_MODULE;
	pcb.event_input = dummy_input;
	pcb.निजी_मुक्त = dummy_मुक्त;
	pcb.निजी_data = rec;
	pinfo.kernel = &pcb;
	अगर (snd_seq_kernel_client_ctl(my_client, SNDRV_SEQ_IOCTL_CREATE_PORT, &pinfo) < 0) अणु
		kमुक्त(rec);
		वापस शून्य;
	पूर्ण
	rec->port = pinfo.addr.port;
	वापस rec;
पूर्ण

/*
 * रेजिस्टर client and create ports
 */
अटल पूर्णांक __init
रेजिस्टर_client(व्योम)
अणु
	काष्ठा snd_seq_dummy_port *rec1, *rec2;
	पूर्णांक i;

	अगर (ports < 1) अणु
		pr_err("ALSA: seq_dummy: invalid number of ports %d\n", ports);
		वापस -EINVAL;
	पूर्ण

	/* create client */
	my_client = snd_seq_create_kernel_client(शून्य, SNDRV_SEQ_CLIENT_DUMMY,
						 "Midi Through");
	अगर (my_client < 0)
		वापस my_client;

	/* create ports */
	क्रम (i = 0; i < ports; i++) अणु
		rec1 = create_port(i, 0);
		अगर (rec1 == शून्य) अणु
			snd_seq_delete_kernel_client(my_client);
			वापस -ENOMEM;
		पूर्ण
		अगर (duplex) अणु
			rec2 = create_port(i, 1);
			अगर (rec2 == शून्य) अणु
				snd_seq_delete_kernel_client(my_client);
				वापस -ENOMEM;
			पूर्ण
			rec1->connect = rec2->port;
			rec2->connect = rec1->port;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/*
 * delete client अगर exists
 */
अटल व्योम __निकास
delete_client(व्योम)
अणु
	अगर (my_client >= 0)
		snd_seq_delete_kernel_client(my_client);
पूर्ण

/*
 *  Init part
 */

अटल पूर्णांक __init alsa_seq_dummy_init(व्योम)
अणु
	वापस रेजिस्टर_client();
पूर्ण

अटल व्योम __निकास alsa_seq_dummy_निकास(व्योम)
अणु
	delete_client();
पूर्ण

module_init(alsa_seq_dummy_init)
module_निकास(alsa_seq_dummy_निकास)
