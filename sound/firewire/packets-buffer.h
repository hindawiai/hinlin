<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित SOUND_FIREWIRE_PACKETS_BUFFER_H_INCLUDED
#घोषणा SOUND_FIREWIRE_PACKETS_BUFFER_H_INCLUDED

#समावेश <linux/dma-mapping.h>
#समावेश <linux/firewire.h>

/**
 * काष्ठा iso_packets_buffer - manages a buffer क्रम many packets
 * @iso_buffer: the memory containing the packets
 * @packets: an array, with each element poपूर्णांकing to one packet
 */
काष्ठा iso_packets_buffer अणु
	काष्ठा fw_iso_buffer iso_buffer;
	काष्ठा अणु
		व्योम *buffer;
		अचिन्हित पूर्णांक offset;
	पूर्ण *packets;
पूर्ण;

पूर्णांक iso_packets_buffer_init(काष्ठा iso_packets_buffer *b, काष्ठा fw_unit *unit,
			    अचिन्हित पूर्णांक count, अचिन्हित पूर्णांक packet_size,
			    क्रमागत dma_data_direction direction);
व्योम iso_packets_buffer_destroy(काष्ठा iso_packets_buffer *b,
				काष्ठा fw_unit *unit);

#पूर्ण_अगर
