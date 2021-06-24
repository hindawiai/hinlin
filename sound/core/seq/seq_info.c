<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *   ALSA sequencer /proc पूर्णांकerface
 *   Copyright (c) 1998 by Frank van de Pol <fvdpol@coil.demon.nl>
 */

#समावेश <linux/init.h>
#समावेश <linux/export.h>
#समावेश <sound/core.h>

#समावेश "seq_info.h"
#समावेश "seq_clientmgr.h"
#समावेश "seq_timer.h"

अटल काष्ठा snd_info_entry *queues_entry;
अटल काष्ठा snd_info_entry *clients_entry;
अटल काष्ठा snd_info_entry *समयr_entry;


अटल काष्ठा snd_info_entry * __init
create_info_entry(अक्षर *name, व्योम (*पढ़ो)(काष्ठा snd_info_entry *,
					   काष्ठा snd_info_buffer *))
अणु
	काष्ठा snd_info_entry *entry;

	entry = snd_info_create_module_entry(THIS_MODULE, name, snd_seq_root);
	अगर (entry == शून्य)
		वापस शून्य;
	entry->content = SNDRV_INFO_CONTENT_TEXT;
	entry->c.text.पढ़ो = पढ़ो;
	अगर (snd_info_रेजिस्टर(entry) < 0) अणु
		snd_info_मुक्त_entry(entry);
		वापस शून्य;
	पूर्ण
	वापस entry;
पूर्ण

व्योम snd_seq_info_करोne(व्योम)
अणु
	snd_info_मुक्त_entry(queues_entry);
	snd_info_मुक्त_entry(clients_entry);
	snd_info_मुक्त_entry(समयr_entry);
पूर्ण

/* create all our /proc entries */
पूर्णांक __init snd_seq_info_init(व्योम)
अणु
	queues_entry = create_info_entry("queues",
					 snd_seq_info_queues_पढ़ो);
	clients_entry = create_info_entry("clients",
					  snd_seq_info_clients_पढ़ो);
	समयr_entry = create_info_entry("timer", snd_seq_info_समयr_पढ़ो);
	अगर (!queues_entry || !clients_entry || !समयr_entry)
		जाओ error;
	वापस 0;

 error:
	snd_seq_info_करोne();
	वापस -ENOMEM;
पूर्ण
