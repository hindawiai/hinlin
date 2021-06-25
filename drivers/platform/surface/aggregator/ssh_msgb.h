<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * SSH message builder functions.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#अगर_अघोषित _SURFACE_AGGREGATOR_SSH_MSGB_H
#घोषणा _SURFACE_AGGREGATOR_SSH_MSGB_H

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/types.h>

#समावेश <linux/surface_aggregator/controller.h>
#समावेश <linux/surface_aggregator/serial_hub.h>

/**
 * काष्ठा msgbuf - Buffer काष्ठा to स्थिरruct SSH messages.
 * @begin: Poपूर्णांकer to the beginning of the allocated buffer space.
 * @end:   Poपूर्णांकer to the end (one past last element) of the allocated buffer
 *         space.
 * @ptr:   Poपूर्णांकer to the first मुक्त element in the buffer.
 */
काष्ठा msgbuf अणु
	u8 *begin;
	u8 *end;
	u8 *ptr;
पूर्ण;

/**
 * msgb_init() - Initialize the given message buffer काष्ठा.
 * @msgb: The buffer काष्ठा to initialize
 * @ptr:  Poपूर्णांकer to the underlying memory by which the buffer will be backed.
 * @cap:  Size of the underlying memory.
 *
 * Initialize the given message buffer काष्ठा using the provided memory as
 * backing.
 */
अटल अंतरभूत व्योम msgb_init(काष्ठा msgbuf *msgb, u8 *ptr, माप_प्रकार cap)
अणु
	msgb->begin = ptr;
	msgb->end = ptr + cap;
	msgb->ptr = ptr;
पूर्ण

/**
 * msgb_bytes_used() - Return the current number of bytes used in the buffer.
 * @msgb: The message buffer.
 */
अटल अंतरभूत माप_प्रकार msgb_bytes_used(स्थिर काष्ठा msgbuf *msgb)
अणु
	वापस msgb->ptr - msgb->begin;
पूर्ण

अटल अंतरभूत व्योम __msgb_push_u8(काष्ठा msgbuf *msgb, u8 value)
अणु
	*msgb->ptr = value;
	msgb->ptr += माप(u8);
पूर्ण

अटल अंतरभूत व्योम __msgb_push_u16(काष्ठा msgbuf *msgb, u16 value)
अणु
	put_unaligned_le16(value, msgb->ptr);
	msgb->ptr += माप(u16);
पूर्ण

/**
 * msgb_push_u16() - Push a u16 value to the buffer.
 * @msgb:  The message buffer.
 * @value: The value to push to the buffer.
 */
अटल अंतरभूत व्योम msgb_push_u16(काष्ठा msgbuf *msgb, u16 value)
अणु
	अगर (WARN_ON(msgb->ptr + माप(u16) > msgb->end))
		वापस;

	__msgb_push_u16(msgb, value);
पूर्ण

/**
 * msgb_push_syn() - Push SSH SYN bytes to the buffer.
 * @msgb: The message buffer.
 */
अटल अंतरभूत व्योम msgb_push_syn(काष्ठा msgbuf *msgb)
अणु
	msgb_push_u16(msgb, SSH_MSG_SYN);
पूर्ण

/**
 * msgb_push_buf() - Push raw data to the buffer.
 * @msgb: The message buffer.
 * @buf:  The data to push to the buffer.
 * @len:  The length of the data to push to the buffer.
 */
अटल अंतरभूत व्योम msgb_push_buf(काष्ठा msgbuf *msgb, स्थिर u8 *buf, माप_प्रकार len)
अणु
	msgb->ptr = स_नकल(msgb->ptr, buf, len) + len;
पूर्ण

/**
 * msgb_push_crc() - Compute CRC and push it to the buffer.
 * @msgb: The message buffer.
 * @buf:  The data क्रम which the CRC should be computed.
 * @len:  The length of the data क्रम which the CRC should be computed.
 */
अटल अंतरभूत व्योम msgb_push_crc(काष्ठा msgbuf *msgb, स्थिर u8 *buf, माप_प्रकार len)
अणु
	msgb_push_u16(msgb, ssh_crc(buf, len));
पूर्ण

/**
 * msgb_push_frame() - Push a SSH message frame header to the buffer.
 * @msgb: The message buffer
 * @ty:   The type of the frame.
 * @len:  The length of the payload of the frame.
 * @seq:  The sequence ID of the frame/packet.
 */
अटल अंतरभूत व्योम msgb_push_frame(काष्ठा msgbuf *msgb, u8 ty, u16 len, u8 seq)
अणु
	u8 *स्थिर begin = msgb->ptr;

	अगर (WARN_ON(msgb->ptr + माप(काष्ठा ssh_frame) > msgb->end))
		वापस;

	__msgb_push_u8(msgb, ty);	/* Frame type. */
	__msgb_push_u16(msgb, len);	/* Frame payload length. */
	__msgb_push_u8(msgb, seq);	/* Frame sequence ID. */

	msgb_push_crc(msgb, begin, msgb->ptr - begin);
पूर्ण

/**
 * msgb_push_ack() - Push a SSH ACK frame to the buffer.
 * @msgb: The message buffer
 * @seq:  The sequence ID of the frame/packet to be ACKed.
 */
अटल अंतरभूत व्योम msgb_push_ack(काष्ठा msgbuf *msgb, u8 seq)
अणु
	/* SYN. */
	msgb_push_syn(msgb);

	/* ACK-type frame + CRC. */
	msgb_push_frame(msgb, SSH_FRAME_TYPE_ACK, 0x00, seq);

	/* Payload CRC (ACK-type frames करो not have a payload). */
	msgb_push_crc(msgb, msgb->ptr, 0);
पूर्ण

/**
 * msgb_push_nak() - Push a SSH NAK frame to the buffer.
 * @msgb: The message buffer
 */
अटल अंतरभूत व्योम msgb_push_nak(काष्ठा msgbuf *msgb)
अणु
	/* SYN. */
	msgb_push_syn(msgb);

	/* NAK-type frame + CRC. */
	msgb_push_frame(msgb, SSH_FRAME_TYPE_NAK, 0x00, 0x00);

	/* Payload CRC (ACK-type frames करो not have a payload). */
	msgb_push_crc(msgb, msgb->ptr, 0);
पूर्ण

/**
 * msgb_push_cmd() - Push a SSH command frame with payload to the buffer.
 * @msgb: The message buffer.
 * @seq:  The sequence ID (SEQ) of the frame/packet.
 * @rqid: The request ID (RQID) of the request contained in the frame.
 * @rqst: The request to wrap in the frame.
 */
अटल अंतरभूत व्योम msgb_push_cmd(काष्ठा msgbuf *msgb, u8 seq, u16 rqid,
				 स्थिर काष्ठा ssam_request *rqst)
अणु
	स्थिर u8 type = SSH_FRAME_TYPE_DATA_SEQ;
	u8 *cmd;

	/* SYN. */
	msgb_push_syn(msgb);

	/* Command frame + CRC. */
	msgb_push_frame(msgb, type, माप(काष्ठा ssh_command) + rqst->length, seq);

	/* Frame payload: Command काष्ठा + payload. */
	अगर (WARN_ON(msgb->ptr + माप(काष्ठा ssh_command) > msgb->end))
		वापस;

	cmd = msgb->ptr;

	__msgb_push_u8(msgb, SSH_PLD_TYPE_CMD);		/* Payload type. */
	__msgb_push_u8(msgb, rqst->target_category);	/* Target category. */
	__msgb_push_u8(msgb, rqst->target_id);		/* Target ID (out). */
	__msgb_push_u8(msgb, 0x00);			/* Target ID (in). */
	__msgb_push_u8(msgb, rqst->instance_id);	/* Instance ID. */
	__msgb_push_u16(msgb, rqid);			/* Request ID. */
	__msgb_push_u8(msgb, rqst->command_id);		/* Command ID. */

	/* Command payload. */
	msgb_push_buf(msgb, rqst->payload, rqst->length);

	/* CRC क्रम command काष्ठा + payload. */
	msgb_push_crc(msgb, cmd, msgb->ptr - cmd);
पूर्ण

#पूर्ण_अगर /* _SURFACE_AGGREGATOR_SSH_MSGB_H */
