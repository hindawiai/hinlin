<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OSS compatible sequencer driver
 *
 * खोलो/बंद and reset पूर्णांकerface
 *
 * Copyright (C) 1998-1999 Takashi Iwai <tiwai@suse.de>
 */

#समावेश "seq_oss_device.h"
#समावेश "seq_oss_synth.h"
#समावेश "seq_oss_midi.h"
#समावेश "seq_oss_writeq.h"
#समावेश "seq_oss_readq.h"
#समावेश "seq_oss_timer.h"
#समावेश "seq_oss_event.h"
#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>

/*
 * common variables
 */
अटल पूर्णांक maxqlen = SNDRV_SEQ_OSS_MAX_QLEN;
module_param(maxqlen, पूर्णांक, 0444);
MODULE_PARM_DESC(maxqlen, "maximum queue length");

अटल पूर्णांक प्रणाली_client = -1; /* ALSA sequencer client number */
अटल पूर्णांक प्रणाली_port = -1;

अटल पूर्णांक num_clients;
अटल काष्ठा seq_oss_devinfo *client_table[SNDRV_SEQ_OSS_MAX_CLIENTS];


/*
 * prototypes
 */
अटल पूर्णांक receive_announce(काष्ठा snd_seq_event *ev, पूर्णांक direct, व्योम *निजी, पूर्णांक atomic, पूर्णांक hop);
अटल पूर्णांक translate_mode(काष्ठा file *file);
अटल पूर्णांक create_port(काष्ठा seq_oss_devinfo *dp);
अटल पूर्णांक delete_port(काष्ठा seq_oss_devinfo *dp);
अटल पूर्णांक alloc_seq_queue(काष्ठा seq_oss_devinfo *dp);
अटल पूर्णांक delete_seq_queue(पूर्णांक queue);
अटल व्योम मुक्त_devinfo(व्योम *निजी);

#घोषणा call_ctl(type,rec) snd_seq_kernel_client_ctl(प्रणाली_client, type, rec)


/* call snd_seq_oss_midi_lookup_ports() asynchronously */
अटल व्योम async_call_lookup_ports(काष्ठा work_काष्ठा *work)
अणु
	snd_seq_oss_midi_lookup_ports(प्रणाली_client);
पूर्ण

अटल DECLARE_WORK(async_lookup_work, async_call_lookup_ports);

/*
 * create sequencer client क्रम OSS sequencer
 */
पूर्णांक __init
snd_seq_oss_create_client(व्योम)
अणु
	पूर्णांक rc;
	काष्ठा snd_seq_port_info *port;
	काष्ठा snd_seq_port_callback port_callback;

	port = kदो_स्मृति(माप(*port), GFP_KERNEL);
	अगर (!port) अणु
		rc = -ENOMEM;
		जाओ __error;
	पूर्ण

	/* create ALSA client */
	rc = snd_seq_create_kernel_client(शून्य, SNDRV_SEQ_CLIENT_OSS,
					  "OSS sequencer");
	अगर (rc < 0)
		जाओ __error;

	प्रणाली_client = rc;

	/* create annoucement receiver port */
	स_रखो(port, 0, माप(*port));
	म_नकल(port->name, "Receiver");
	port->addr.client = प्रणाली_client;
	port->capability = SNDRV_SEQ_PORT_CAP_WRITE; /* receive only */
	port->type = 0;

	स_रखो(&port_callback, 0, माप(port_callback));
	/* करोn't set port_callback.owner here. otherwise the module counter
	 * is incremented and we can no दीर्घer release the module..
	 */
	port_callback.event_input = receive_announce;
	port->kernel = &port_callback;
	
	call_ctl(SNDRV_SEQ_IOCTL_CREATE_PORT, port);
	अगर ((प्रणाली_port = port->addr.port) >= 0) अणु
		काष्ठा snd_seq_port_subscribe subs;

		स_रखो(&subs, 0, माप(subs));
		subs.sender.client = SNDRV_SEQ_CLIENT_SYSTEM;
		subs.sender.port = SNDRV_SEQ_PORT_SYSTEM_ANNOUNCE;
		subs.dest.client = प्रणाली_client;
		subs.dest.port = प्रणाली_port;
		call_ctl(SNDRV_SEQ_IOCTL_SUBSCRIBE_PORT, &subs);
	पूर्ण
	rc = 0;

	/* look up midi devices */
	schedule_work(&async_lookup_work);

 __error:
	kमुक्त(port);
	वापस rc;
पूर्ण


/*
 * receive annoucement from प्रणाली port, and check the midi device
 */
अटल पूर्णांक
receive_announce(काष्ठा snd_seq_event *ev, पूर्णांक direct, व्योम *निजी, पूर्णांक atomic, पूर्णांक hop)
अणु
	काष्ठा snd_seq_port_info pinfo;

	अगर (atomic)
		वापस 0; /* it must not happen */

	चयन (ev->type) अणु
	हाल SNDRV_SEQ_EVENT_PORT_START:
	हाल SNDRV_SEQ_EVENT_PORT_CHANGE:
		अगर (ev->data.addr.client == प्रणाली_client)
			अवरोध; /* ignore myself */
		स_रखो(&pinfo, 0, माप(pinfo));
		pinfo.addr = ev->data.addr;
		अगर (call_ctl(SNDRV_SEQ_IOCTL_GET_PORT_INFO, &pinfo) >= 0)
			snd_seq_oss_midi_check_new_port(&pinfo);
		अवरोध;

	हाल SNDRV_SEQ_EVENT_PORT_EXIT:
		अगर (ev->data.addr.client == प्रणाली_client)
			अवरोध; /* ignore myself */
		snd_seq_oss_midi_check_निकास_port(ev->data.addr.client,
						ev->data.addr.port);
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण


/*
 * delete OSS sequencer client
 */
पूर्णांक
snd_seq_oss_delete_client(व्योम)
अणु
	cancel_work_sync(&async_lookup_work);
	अगर (प्रणाली_client >= 0)
		snd_seq_delete_kernel_client(प्रणाली_client);

	snd_seq_oss_midi_clear_all();

	वापस 0;
पूर्ण


/*
 * खोलो sequencer device
 */
पूर्णांक
snd_seq_oss_खोलो(काष्ठा file *file, पूर्णांक level)
अणु
	पूर्णांक i, rc;
	काष्ठा seq_oss_devinfo *dp;

	dp = kzalloc(माप(*dp), GFP_KERNEL);
	अगर (!dp)
		वापस -ENOMEM;

	dp->cseq = प्रणाली_client;
	dp->port = -1;
	dp->queue = -1;

	क्रम (i = 0; i < SNDRV_SEQ_OSS_MAX_CLIENTS; i++) अणु
		अगर (client_table[i] == शून्य)
			अवरोध;
	पूर्ण

	dp->index = i;
	अगर (i >= SNDRV_SEQ_OSS_MAX_CLIENTS) अणु
		pr_debug("ALSA: seq_oss: too many applications\n");
		rc = -ENOMEM;
		जाओ _error;
	पूर्ण

	/* look up synth and midi devices */
	snd_seq_oss_synth_setup(dp);
	snd_seq_oss_midi_setup(dp);

	अगर (dp->synth_खोलोed == 0 && dp->max_mididev == 0) अणु
		/* pr_err("ALSA: seq_oss: no device found\n"); */
		rc = -ENODEV;
		जाओ _error;
	पूर्ण

	/* create port */
	rc = create_port(dp);
	अगर (rc < 0) अणु
		pr_err("ALSA: seq_oss: can't create port\n");
		जाओ _error;
	पूर्ण

	/* allocate queue */
	rc = alloc_seq_queue(dp);
	अगर (rc < 0)
		जाओ _error;

	/* set address */
	dp->addr.client = dp->cseq;
	dp->addr.port = dp->port;
	/*dp->addr.queue = dp->queue;*/
	/*dp->addr.channel = 0;*/

	dp->seq_mode = level;

	/* set up file mode */
	dp->file_mode = translate_mode(file);

	/* initialize पढ़ो queue */
	अगर (is_पढ़ो_mode(dp->file_mode)) अणु
		dp->पढ़ोq = snd_seq_oss_पढ़ोq_new(dp, maxqlen);
		अगर (!dp->पढ़ोq) अणु
			rc = -ENOMEM;
			जाओ _error;
		पूर्ण
	पूर्ण

	/* initialize ग_लिखो queue */
	अगर (is_ग_लिखो_mode(dp->file_mode)) अणु
		dp->ग_लिखोq = snd_seq_oss_ग_लिखोq_new(dp, maxqlen);
		अगर (!dp->ग_लिखोq) अणु
			rc = -ENOMEM;
			जाओ _error;
		पूर्ण
	पूर्ण

	/* initialize समयr */
	dp->समयr = snd_seq_oss_समयr_new(dp);
	अगर (!dp->समयr) अणु
		pr_err("ALSA: seq_oss: can't alloc timer\n");
		rc = -ENOMEM;
		जाओ _error;
	पूर्ण

	/* set निजी data poपूर्णांकer */
	file->निजी_data = dp;

	/* set up क्रम mode2 */
	अगर (level == SNDRV_SEQ_OSS_MODE_MUSIC)
		snd_seq_oss_synth_setup_midi(dp);
	अन्यथा अगर (is_पढ़ो_mode(dp->file_mode))
		snd_seq_oss_midi_खोलो_all(dp, SNDRV_SEQ_OSS_खाता_READ);

	client_table[dp->index] = dp;
	num_clients++;

	वापस 0;

 _error:
	snd_seq_oss_synth_cleanup(dp);
	snd_seq_oss_midi_cleanup(dp);
	delete_seq_queue(dp->queue);
	delete_port(dp);

	वापस rc;
पूर्ण

/*
 * translate file flags to निजी mode
 */
अटल पूर्णांक
translate_mode(काष्ठा file *file)
अणु
	पूर्णांक file_mode = 0;
	अगर ((file->f_flags & O_ACCMODE) != O_RDONLY)
		file_mode |= SNDRV_SEQ_OSS_खाता_WRITE;
	अगर ((file->f_flags & O_ACCMODE) != O_WRONLY)
		file_mode |= SNDRV_SEQ_OSS_खाता_READ;
	अगर (file->f_flags & O_NONBLOCK)
		file_mode |= SNDRV_SEQ_OSS_खाता_NONBLOCK;
	वापस file_mode;
पूर्ण


/*
 * create sequencer port
 */
अटल पूर्णांक
create_port(काष्ठा seq_oss_devinfo *dp)
अणु
	पूर्णांक rc;
	काष्ठा snd_seq_port_info port;
	काष्ठा snd_seq_port_callback callback;

	स_रखो(&port, 0, माप(port));
	port.addr.client = dp->cseq;
	प्र_लिखो(port.name, "Sequencer-%d", dp->index);
	port.capability = SNDRV_SEQ_PORT_CAP_READ|SNDRV_SEQ_PORT_CAP_WRITE; /* no subscription */
	port.type = SNDRV_SEQ_PORT_TYPE_SPECIFIC;
	port.midi_channels = 128;
	port.synth_voices = 128;

	स_रखो(&callback, 0, माप(callback));
	callback.owner = THIS_MODULE;
	callback.निजी_data = dp;
	callback.event_input = snd_seq_oss_event_input;
	callback.निजी_मुक्त = मुक्त_devinfo;
	port.kernel = &callback;

	rc = call_ctl(SNDRV_SEQ_IOCTL_CREATE_PORT, &port);
	अगर (rc < 0)
		वापस rc;

	dp->port = port.addr.port;

	वापस 0;
पूर्ण

/*
 * delete ALSA port
 */
अटल पूर्णांक
delete_port(काष्ठा seq_oss_devinfo *dp)
अणु
	अगर (dp->port < 0) अणु
		kमुक्त(dp);
		वापस 0;
	पूर्ण

	वापस snd_seq_event_port_detach(dp->cseq, dp->port);
पूर्ण

/*
 * allocate a queue
 */
अटल पूर्णांक
alloc_seq_queue(काष्ठा seq_oss_devinfo *dp)
अणु
	काष्ठा snd_seq_queue_info qinfo;
	पूर्णांक rc;

	स_रखो(&qinfo, 0, माप(qinfo));
	qinfo.owner = प्रणाली_client;
	qinfo.locked = 1;
	म_नकल(qinfo.name, "OSS Sequencer Emulation");
	अगर ((rc = call_ctl(SNDRV_SEQ_IOCTL_CREATE_QUEUE, &qinfo)) < 0)
		वापस rc;
	dp->queue = qinfo.queue;
	वापस 0;
पूर्ण

/*
 * release queue
 */
अटल पूर्णांक
delete_seq_queue(पूर्णांक queue)
अणु
	काष्ठा snd_seq_queue_info qinfo;
	पूर्णांक rc;

	अगर (queue < 0)
		वापस 0;
	स_रखो(&qinfo, 0, माप(qinfo));
	qinfo.queue = queue;
	rc = call_ctl(SNDRV_SEQ_IOCTL_DELETE_QUEUE, &qinfo);
	अगर (rc < 0)
		pr_err("ALSA: seq_oss: unable to delete queue %d (%d)\n", queue, rc);
	वापस rc;
पूर्ण


/*
 * मुक्त device inक्रमmations - निजी_मुक्त callback of port
 */
अटल व्योम
मुक्त_devinfo(व्योम *निजी)
अणु
	काष्ठा seq_oss_devinfo *dp = (काष्ठा seq_oss_devinfo *)निजी;

	snd_seq_oss_समयr_delete(dp->समयr);
		
	snd_seq_oss_ग_लिखोq_delete(dp->ग_लिखोq);

	snd_seq_oss_पढ़ोq_delete(dp->पढ़ोq);
	
	kमुक्त(dp);
पूर्ण


/*
 * बंद sequencer device
 */
व्योम
snd_seq_oss_release(काष्ठा seq_oss_devinfo *dp)
अणु
	पूर्णांक queue;

	client_table[dp->index] = शून्य;
	num_clients--;

	snd_seq_oss_reset(dp);

	snd_seq_oss_synth_cleanup(dp);
	snd_seq_oss_midi_cleanup(dp);

	/* clear slot */
	queue = dp->queue;
	अगर (dp->port >= 0)
		delete_port(dp);
	delete_seq_queue(queue);
पूर्ण


/*
 * reset sequencer devices
 */
व्योम
snd_seq_oss_reset(काष्ठा seq_oss_devinfo *dp)
अणु
	पूर्णांक i;

	/* reset all synth devices */
	क्रम (i = 0; i < dp->max_synthdev; i++)
		snd_seq_oss_synth_reset(dp, i);

	/* reset all midi devices */
	अगर (dp->seq_mode != SNDRV_SEQ_OSS_MODE_MUSIC) अणु
		क्रम (i = 0; i < dp->max_mididev; i++)
			snd_seq_oss_midi_reset(dp, i);
	पूर्ण

	/* हटाओ queues */
	अगर (dp->पढ़ोq)
		snd_seq_oss_पढ़ोq_clear(dp->पढ़ोq);
	अगर (dp->ग_लिखोq)
		snd_seq_oss_ग_लिखोq_clear(dp->ग_लिखोq);

	/* reset समयr */
	snd_seq_oss_समयr_stop(dp->समयr);
पूर्ण

#अगर_घोषित CONFIG_SND_PROC_FS
/*
 * misc. functions क्रम proc पूर्णांकerface
 */
अक्षर *
enabled_str(पूर्णांक bool)
अणु
	वापस bool ? "enabled" : "disabled";
पूर्ण

अटल स्थिर अक्षर *
filemode_str(पूर्णांक val)
अणु
	अटल स्थिर अक्षर * स्थिर str[] = अणु
		"none", "read", "write", "read/write",
	पूर्ण;
	वापस str[val & SNDRV_SEQ_OSS_खाता_ACMODE];
पूर्ण


/*
 * proc पूर्णांकerface
 */
व्योम
snd_seq_oss_प्रणाली_info_पढ़ो(काष्ठा snd_info_buffer *buf)
अणु
	पूर्णांक i;
	काष्ठा seq_oss_devinfo *dp;

	snd_iम_लिखो(buf, "ALSA client number %d\n", प्रणाली_client);
	snd_iम_लिखो(buf, "ALSA receiver port %d\n", प्रणाली_port);

	snd_iम_लिखो(buf, "\nNumber of applications: %d\n", num_clients);
	क्रम (i = 0; i < num_clients; i++) अणु
		snd_iम_लिखो(buf, "\nApplication %d: ", i);
		अगर ((dp = client_table[i]) == शून्य) अणु
			snd_iम_लिखो(buf, "*empty*\n");
			जारी;
		पूर्ण
		snd_iम_लिखो(buf, "port %d : queue %d\n", dp->port, dp->queue);
		snd_iम_लिखो(buf, "  sequencer mode = %s : file open mode = %s\n",
			    (dp->seq_mode ? "music" : "synth"),
			    filemode_str(dp->file_mode));
		अगर (dp->seq_mode)
			snd_iम_लिखो(buf, "  timer tempo = %d, timebase = %d\n",
				    dp->समयr->oss_tempo, dp->समयr->oss_समयbase);
		snd_iम_लिखो(buf, "  max queue length %d\n", maxqlen);
		अगर (is_पढ़ो_mode(dp->file_mode) && dp->पढ़ोq)
			snd_seq_oss_पढ़ोq_info_पढ़ो(dp->पढ़ोq, buf);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SND_PROC_FS */
