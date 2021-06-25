<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  ALSA sequencer System Client
 *  Copyright (c) 1998 by Frank van de Pol <fvdpol@coil.demon.nl>
 */
#अगर_अघोषित __SND_SEQ_SYSTEM_H
#घोषणा __SND_SEQ_SYSTEM_H

#समावेश <sound/seq_kernel.h>


/* entry poपूर्णांकs क्रम broadcasting प्रणाली events */
व्योम snd_seq_प्रणाली_broadcast(पूर्णांक client, पूर्णांक port, पूर्णांक type);

#घोषणा snd_seq_प्रणाली_client_ev_client_start(client) snd_seq_प्रणाली_broadcast(client, 0, SNDRV_SEQ_EVENT_CLIENT_START)
#घोषणा snd_seq_प्रणाली_client_ev_client_निकास(client) snd_seq_प्रणाली_broadcast(client, 0, SNDRV_SEQ_EVENT_CLIENT_EXIT)
#घोषणा snd_seq_प्रणाली_client_ev_client_change(client) snd_seq_प्रणाली_broadcast(client, 0, SNDRV_SEQ_EVENT_CLIENT_CHANGE)
#घोषणा snd_seq_प्रणाली_client_ev_port_start(client, port) snd_seq_प्रणाली_broadcast(client, port, SNDRV_SEQ_EVENT_PORT_START)
#घोषणा snd_seq_प्रणाली_client_ev_port_निकास(client, port) snd_seq_प्रणाली_broadcast(client, port, SNDRV_SEQ_EVENT_PORT_EXIT)
#घोषणा snd_seq_प्रणाली_client_ev_port_change(client, port) snd_seq_प्रणाली_broadcast(client, port, SNDRV_SEQ_EVENT_PORT_CHANGE)

पूर्णांक snd_seq_प्रणाली_notअगरy(पूर्णांक client, पूर्णांक port, काष्ठा snd_seq_event *ev);

/* रेजिस्टर our पूर्णांकernal client */
पूर्णांक snd_seq_प्रणाली_client_init(व्योम);

/* unरेजिस्टर our पूर्णांकernal client */
व्योम snd_seq_प्रणाली_client_करोne(व्योम);


#पूर्ण_अगर
