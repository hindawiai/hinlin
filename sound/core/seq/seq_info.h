<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *   ALSA sequencer /proc info
 *   Copyright (c) 1998 by Frank van de Pol <fvdpol@coil.demon.nl>
 */
#अगर_अघोषित __SND_SEQ_INFO_H
#घोषणा __SND_SEQ_INFO_H

#समावेश <sound/info.h>
#समावेश <sound/seq_kernel.h>

व्योम snd_seq_info_clients_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer);
व्योम snd_seq_info_समयr_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer);
व्योम snd_seq_info_queues_पढ़ो(काष्ठा snd_info_entry *entry, काष्ठा snd_info_buffer *buffer);


#अगर_घोषित CONFIG_SND_PROC_FS
पूर्णांक snd_seq_info_init(व्योम);
व्योम snd_seq_info_करोne(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक snd_seq_info_init(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम snd_seq_info_करोne(व्योम) अणुपूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
