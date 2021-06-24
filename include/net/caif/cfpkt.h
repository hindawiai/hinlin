<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) ST-Ericsson AB 2010
 * Author:	Sjur Brendeland
 */

#अगर_अघोषित CFPKT_H_
#घोषणा CFPKT_H_
#समावेश <net/caअगर/caअगर_layer.h>
#समावेश <linux/types.h>
काष्ठा cfpkt;

/* Create a CAIF packet.
 * len: Length of packet to be created
 * @वापस New packet.
 */
काष्ठा cfpkt *cfpkt_create(u16 len);

/*
 * Destroy a CAIF Packet.
 * pkt Packet to be destoyed.
 */
व्योम cfpkt_destroy(काष्ठा cfpkt *pkt);

/*
 * Extract header from packet.
 *
 * pkt Packet to extract header data from.
 * data Poपूर्णांकer to copy the header data पूर्णांकo.
 * len Length of head data to copy.
 * @वापस zero on success and error code upon failure
 */
पूर्णांक cfpkt_extr_head(काष्ठा cfpkt *pkt, व्योम *data, u16 len);

अटल अंतरभूत u8 cfpkt_extr_head_u8(काष्ठा cfpkt *pkt)
अणु
	u8 पंचांगp;

	cfpkt_extr_head(pkt, &पंचांगp, 1);

	वापस पंचांगp;
पूर्ण

अटल अंतरभूत u16 cfpkt_extr_head_u16(काष्ठा cfpkt *pkt)
अणु
	__le16 पंचांगp;

	cfpkt_extr_head(pkt, &पंचांगp, 2);

	वापस le16_to_cpu(पंचांगp);
पूर्ण

अटल अंतरभूत u32 cfpkt_extr_head_u32(काष्ठा cfpkt *pkt)
अणु
	__le32 पंचांगp;

	cfpkt_extr_head(pkt, &पंचांगp, 4);

	वापस le32_to_cpu(पंचांगp);
पूर्ण

/*
 * Peek header from packet.
 * Reads data from packet without changing packet.
 *
 * pkt Packet to extract header data from.
 * data Poपूर्णांकer to copy the header data पूर्णांकo.
 * len Length of head data to copy.
 * @वापस zero on success and error code upon failure
 */
पूर्णांक cfpkt_peek_head(काष्ठा cfpkt *pkt, व्योम *data, u16 len);

/*
 * Extract header from trailer (end of packet).
 *
 * pkt Packet to extract header data from.
 * data Poपूर्णांकer to copy the trailer data पूर्णांकo.
 * len Length of header data to copy.
 * @वापस zero on success and error code upon failure
 */
पूर्णांक cfpkt_extr_trail(काष्ठा cfpkt *pkt, व्योम *data, u16 len);

/*
 * Add header to packet.
 *
 *
 * pkt Packet to add header data to.
 * data Poपूर्णांकer to data to copy पूर्णांकo the header.
 * len Length of header data to copy.
 * @वापस zero on success and error code upon failure
 */
पूर्णांक cfpkt_add_head(काष्ठा cfpkt *pkt, स्थिर व्योम *data, u16 len);

/*
 * Add trailer to packet.
 *
 *
 * pkt Packet to add trailer data to.
 * data Poपूर्णांकer to data to copy पूर्णांकo the trailer.
 * len Length of trailer data to copy.
 * @वापस zero on success and error code upon failure
 */
पूर्णांक cfpkt_add_trail(काष्ठा cfpkt *pkt, स्थिर व्योम *data, u16 len);

/*
 * Pad trailer on packet.
 * Moves data poपूर्णांकer in packet, no content copied.
 *
 * pkt Packet in which to pad trailer.
 * len Length of padding to add.
 * @वापस zero on success and error code upon failure
 */
पूर्णांक cfpkt_pad_trail(काष्ठा cfpkt *pkt, u16 len);

/*
 * Add a single byte to packet body (tail).
 *
 * pkt Packet in which to add byte.
 * data Byte to add.
 * @वापस zero on success and error code upon failure
 */
पूर्णांक cfpkt_addbdy(काष्ठा cfpkt *pkt, स्थिर u8 data);

/*
 * Add a data to packet body (tail).
 *
 * pkt Packet in which to add data.
 * data Poपूर्णांकer to data to copy पूर्णांकo the packet body.
 * len Length of data to add.
 * @वापस zero on success and error code upon failure
 */
पूर्णांक cfpkt_add_body(काष्ठा cfpkt *pkt, स्थिर व्योम *data, u16 len);

/*
 * Checks whether there are more data to process in packet.
 * pkt Packet to check.
 * @वापस true अगर more data are available in packet false otherwise
 */
bool cfpkt_more(काष्ठा cfpkt *pkt);

/*
 * Checks whether the packet is erroneous,
 * i.e. अगर it has been attempted to extract more data than available in packet
 * or writing more data than has been allocated in cfpkt_create().
 * pkt Packet to check.
 * @वापस true on error false otherwise
 */
bool cfpkt_erroneous(काष्ठा cfpkt *pkt);

/*
 * Get the packet length.
 * pkt Packet to get length from.
 * @वापस Number of bytes in packet.
 */
u16 cfpkt_getlen(काष्ठा cfpkt *pkt);

/*
 * Set the packet length, by adjusting the trailer poपूर्णांकer according to length.
 * pkt Packet to set length.
 * len Packet length.
 * @वापस Number of bytes in packet.
 */
पूर्णांक cfpkt_setlen(काष्ठा cfpkt *pkt, u16 len);

/*
 * cfpkt_append - Appends a packet's data to another packet.
 * dstpkt:    Packet to append data पूर्णांकo, WILL BE FREED BY THIS FUNCTION
 * addpkt:    Packet to be appended and स्वतःmatically released,
 *            WILL BE FREED BY THIS FUNCTION.
 * expectlen: Packet's expected total length. This should be considered
 *            as a hपूर्णांक.
 * NB: Input packets will be destroyed after appending and cannot be used
 * after calling this function.
 * @वापस    The new appended packet.
 */
काष्ठा cfpkt *cfpkt_append(काष्ठा cfpkt *dstpkt, काष्ठा cfpkt *addpkt,
		      u16 expectlen);

/*
 * cfpkt_split - Split a packet पूर्णांकo two packets at the specअगरied split poपूर्णांक.
 * pkt: Packet to be split (will contain the first part of the data on निकास)
 * pos: Position to split packet in two parts.
 * @वापस The new packet, containing the second part of the data.
 */
काष्ठा cfpkt *cfpkt_split(काष्ठा cfpkt *pkt, u16 pos);

/*
 * Iteration function, iterates the packet buffers from start to end.
 *
 * Checksum iteration function used to iterate buffers
 * (we may have packets consisting of a chain of buffers)
 * pkt:       Packet to calculate checksum क्रम
 * iter_func: Function poपूर्णांकer to iteration function
 * chks:      Checksum calculated so far.
 * buf:       Poपूर्णांकer to the buffer to checksum
 * len:       Length of buf.
 * data:      Initial checksum value.
 * @वापस    Checksum of buffer.
 */

पूर्णांक cfpkt_iterate(काष्ठा cfpkt *pkt,
		u16 (*iter_func)(u16 chks, व्योम *buf, u16 len),
		u16 data);

/* Map from a "native" packet (e.g. Linux Socket Buffer) to a CAIF packet.
 *  dir - Direction indicating whether this packet is to be sent or received.
 *  nativepkt  - The native packet to be transक्रमmed to a CAIF packet
 *  @वापस The mapped CAIF Packet CFPKT.
 */
काष्ठा cfpkt *cfpkt_fromnative(क्रमागत caअगर_direction dir, व्योम *nativepkt);

/* Map from a CAIF packet to a "native" packet (e.g. Linux Socket Buffer).
 *  pkt  - The CAIF packet to be transक्रमmed पूर्णांकo a "native" packet.
 *  @वापस The native packet transक्रमmed from a CAIF packet.
 */
व्योम *cfpkt_tonative(काष्ठा cfpkt *pkt);

/*
 * Returns packet inक्रमmation क्रम a packet.
 * pkt Packet to get info from;
 * @वापस Packet inक्रमmation
 */
काष्ठा caअगर_payload_info *cfpkt_info(काष्ठा cfpkt *pkt);

/** cfpkt_set_prio - set priority क्रम a CAIF packet.
 *
 * @pkt: The CAIF packet to be adjusted.
 * @prio: one of TC_PRIO_ स्थिरants.
 */
व्योम cfpkt_set_prio(काष्ठा cfpkt *pkt, पूर्णांक prio);

#पूर्ण_अगर				/* CFPKT_H_ */
