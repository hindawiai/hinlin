<शैली गुरु>
/*
 *
 * dvb_ringbuffer.h: ring buffer implementation क्रम the dvb driver
 *
 * Copyright (C) 2003 Oliver Endriss
 * Copyright (C) 2004 Andrew de Quincey
 *
 * based on code originally found in av7110.c & dvb_ci.c:
 * Copyright (C) 1999-2003 Ralph Metzler & Marcus Metzler
 *                         क्रम convergence पूर्णांकegrated media GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License क्रम more details.
 */

#अगर_अघोषित _DVB_RINGBUFFER_H_
#घोषणा _DVB_RINGBUFFER_H_

#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>

/**
 * काष्ठा dvb_ringbuffer - Describes a ring buffer used at DVB framework
 *
 * @data: Area were the ringbuffer data is written
 * @size: size of the ringbuffer
 * @pपढ़ो: next position to पढ़ो
 * @pग_लिखो: next position to ग_लिखो
 * @error: used by ringbuffer clients to indicate that an error happened.
 * @queue: Wait queue used by ringbuffer clients to indicate when buffer
 *         was filled
 * @lock: Spinlock used to protect the ringbuffer
 */
काष्ठा dvb_ringbuffer अणु
	u8               *data;
	sमाप_प्रकार           size;
	sमाप_प्रकार           pपढ़ो;
	sमाप_प्रकार           pग_लिखो;
	पूर्णांक               error;

	रुको_queue_head_t queue;
	spinlock_t        lock;
पूर्ण;

#घोषणा DVB_RINGBUFFER_PKTHDRSIZE 3

/**
 * dvb_ringbuffer_init - initialize ring buffer, lock and queue
 *
 * @rbuf: poपूर्णांकer to काष्ठा dvb_ringbuffer
 * @data: poपूर्णांकer to the buffer where the data will be stored
 * @len: bytes from ring buffer पूर्णांकo @buf
 */
बाह्य व्योम dvb_ringbuffer_init(काष्ठा dvb_ringbuffer *rbuf, व्योम *data,
				माप_प्रकार len);

/**
 * dvb_ringbuffer_empty - test whether buffer is empty
 *
 * @rbuf: poपूर्णांकer to काष्ठा dvb_ringbuffer
 */
बाह्य पूर्णांक dvb_ringbuffer_empty(काष्ठा dvb_ringbuffer *rbuf);

/**
 * dvb_ringbuffer_मुक्त - वापसs the number of मुक्त bytes in the buffer
 *
 * @rbuf: poपूर्णांकer to काष्ठा dvb_ringbuffer
 *
 * Return: number of मुक्त bytes in the buffer
 */
बाह्य sमाप_प्रकार dvb_ringbuffer_मुक्त(काष्ठा dvb_ringbuffer *rbuf);

/**
 * dvb_ringbuffer_avail - वापसs the number of bytes रुकोing in the buffer
 *
 * @rbuf: poपूर्णांकer to काष्ठा dvb_ringbuffer
 *
 * Return: number of bytes रुकोing in the buffer
 */
बाह्य sमाप_प्रकार dvb_ringbuffer_avail(काष्ठा dvb_ringbuffer *rbuf);

/**
 * dvb_ringbuffer_reset - resets the ringbuffer to initial state
 *
 * @rbuf: poपूर्णांकer to काष्ठा dvb_ringbuffer
 *
 * Resets the पढ़ो and ग_लिखो poपूर्णांकers to zero and flush the buffer.
 *
 * This counts as a पढ़ो and ग_लिखो operation
 */
बाह्य व्योम dvb_ringbuffer_reset(काष्ठा dvb_ringbuffer *rbuf);

/*
 * पढ़ो routines & macros
 */

/**
 * dvb_ringbuffer_flush - flush buffer
 *
 * @rbuf: poपूर्णांकer to काष्ठा dvb_ringbuffer
 */
बाह्य व्योम dvb_ringbuffer_flush(काष्ठा dvb_ringbuffer *rbuf);

/**
 * dvb_ringbuffer_flush_spinlock_wakeup- flush buffer रक्षित by spinlock
 *      and wake-up रुकोing task(s)
 *
 * @rbuf: poपूर्णांकer to काष्ठा dvb_ringbuffer
 */
बाह्य व्योम dvb_ringbuffer_flush_spinlock_wakeup(काष्ठा dvb_ringbuffer *rbuf);

/**
 * DVB_RINGBUFFER_PEEK - peek at byte @offs in the buffer
 *
 * @rbuf: poपूर्णांकer to काष्ठा dvb_ringbuffer
 * @offs: offset inside the ringbuffer
 */
#घोषणा DVB_RINGBUFFER_PEEK(rbuf, offs)	\
			((rbuf)->data[((rbuf)->pपढ़ो + (offs)) % (rbuf)->size])

/**
 * DVB_RINGBUFFER_SKIP - advance पढ़ो ptr by @num bytes
 *
 * @rbuf: poपूर्णांकer to काष्ठा dvb_ringbuffer
 * @num: number of bytes to advance
 */
#घोषणा DVB_RINGBUFFER_SKIP(rbuf, num)	अणु\
			(rbuf)->pपढ़ो = ((rbuf)->pपढ़ो + (num)) % (rbuf)->size;\
पूर्ण

/**
 * dvb_ringbuffer_पढ़ो_user - Reads a buffer पूर्णांकo a user poपूर्णांकer
 *
 * @rbuf: poपूर्णांकer to काष्ठा dvb_ringbuffer
 * @buf: poपूर्णांकer to the buffer where the data will be stored
 * @len: bytes from ring buffer पूर्णांकo @buf
 *
 * This variant assumes that the buffer is a memory at the userspace. So,
 * it will पूर्णांकernally call copy_to_user().
 *
 * Return: number of bytes transferred or -EFAULT
 */
बाह्य sमाप_प्रकार dvb_ringbuffer_पढ़ो_user(काष्ठा dvb_ringbuffer *rbuf,
				   u8 __user *buf, माप_प्रकार len);

/**
 * dvb_ringbuffer_पढ़ो - Reads a buffer पूर्णांकo a poपूर्णांकer
 *
 * @rbuf: poपूर्णांकer to काष्ठा dvb_ringbuffer
 * @buf: poपूर्णांकer to the buffer where the data will be stored
 * @len: bytes from ring buffer पूर्णांकo @buf
 *
 * This variant assumes that the buffer is a memory at the Kernel space
 *
 * Return: number of bytes transferred or -EFAULT
 */
बाह्य व्योम dvb_ringbuffer_पढ़ो(काष्ठा dvb_ringbuffer *rbuf,
				   u8 *buf, माप_प्रकार len);

/*
 * ग_लिखो routines & macros
 */

/**
 * DVB_RINGBUFFER_WRITE_BYTE - ग_लिखो single byte to ring buffer
 *
 * @rbuf: poपूर्णांकer to काष्ठा dvb_ringbuffer
 * @byte: byte to ग_लिखो
 */
#घोषणा DVB_RINGBUFFER_WRITE_BYTE(rbuf, byte)	\
			अणु (rbuf)->data[(rbuf)->pग_लिखो] = (byte); \
			(rbuf)->pग_लिखो = ((rbuf)->pग_लिखो + 1) % (rbuf)->size; पूर्ण

/**
 * dvb_ringbuffer_ग_लिखो - Writes a buffer पूर्णांकo the ringbuffer
 *
 * @rbuf: poपूर्णांकer to काष्ठा dvb_ringbuffer
 * @buf: poपूर्णांकer to the buffer where the data will be पढ़ो
 * @len: bytes from ring buffer पूर्णांकo @buf
 *
 * This variant assumes that the buffer is a memory at the Kernel space
 *
 * वापस: number of bytes transferred or -EFAULT
 */
बाह्य sमाप_प्रकार dvb_ringbuffer_ग_लिखो(काष्ठा dvb_ringbuffer *rbuf, स्थिर u8 *buf,
				    माप_प्रकार len);

/**
 * dvb_ringbuffer_ग_लिखो_user - Writes a buffer received via a user poपूर्णांकer
 *
 * @rbuf: poपूर्णांकer to काष्ठा dvb_ringbuffer
 * @buf: poपूर्णांकer to the buffer where the data will be पढ़ो
 * @len: bytes from ring buffer पूर्णांकo @buf
 *
 * This variant assumes that the buffer is a memory at the userspace. So,
 * it will पूर्णांकernally call copy_from_user().
 *
 * Return: number of bytes transferred or -EFAULT
 */
बाह्य sमाप_प्रकार dvb_ringbuffer_ग_लिखो_user(काष्ठा dvb_ringbuffer *rbuf,
					 स्थिर u8 __user *buf, माप_प्रकार len);

/**
 * dvb_ringbuffer_pkt_ग_लिखो - Write a packet पूर्णांकo the ringbuffer.
 *
 * @rbuf: Ringbuffer to ग_लिखो to.
 * @buf: Buffer to ग_लिखो.
 * @len: Length of buffer (currently limited to 65535 bytes max).
 *
 * Return: Number of bytes written, or -EFAULT, -ENOMEM, -EVINAL.
 */
बाह्य sमाप_प्रकार dvb_ringbuffer_pkt_ग_लिखो(काष्ठा dvb_ringbuffer *rbuf, u8 *buf,
					माप_प्रकार len);

/**
 * dvb_ringbuffer_pkt_पढ़ो_user - Read from a packet in the ringbuffer.
 *
 * @rbuf: Ringbuffer concerned.
 * @idx: Packet index as वापसed by dvb_ringbuffer_pkt_next().
 * @offset: Offset पूर्णांकo packet to पढ़ो from.
 * @buf: Destination buffer क्रम data.
 * @len: Size of destination buffer.
 *
 * Return: Number of bytes पढ़ो, or -EFAULT.
 *
 * .. note::
 *
 *    unlike dvb_ringbuffer_पढ़ो(), this करोes **NOT** update the पढ़ो poपूर्णांकer
 *    in the ringbuffer. You must use dvb_ringbuffer_pkt_dispose() to mark a
 *    packet as no दीर्घer required.
 */
बाह्य sमाप_प्रकार dvb_ringbuffer_pkt_पढ़ो_user(काष्ठा dvb_ringbuffer *rbuf,
					    माप_प्रकार idx,
					    पूर्णांक offset, u8 __user *buf,
					    माप_प्रकार len);

/**
 * dvb_ringbuffer_pkt_पढ़ो - Read from a packet in the ringbuffer.
 * Note: unlike dvb_ringbuffer_पढ़ो_user(), this DOES update the पढ़ो poपूर्णांकer
 * in the ringbuffer.
 *
 * @rbuf: Ringbuffer concerned.
 * @idx: Packet index as वापसed by dvb_ringbuffer_pkt_next().
 * @offset: Offset पूर्णांकo packet to पढ़ो from.
 * @buf: Destination buffer क्रम data.
 * @len: Size of destination buffer.
 *
 * Return: Number of bytes पढ़ो, or -EFAULT.
 */
बाह्य sमाप_प्रकार dvb_ringbuffer_pkt_पढ़ो(काष्ठा dvb_ringbuffer *rbuf, माप_प्रकार idx,
				       पूर्णांक offset, u8 *buf, माप_प्रकार len);

/**
 * dvb_ringbuffer_pkt_dispose - Dispose of a packet in the ring buffer.
 *
 * @rbuf: Ring buffer concerned.
 * @idx: Packet index as वापसed by dvb_ringbuffer_pkt_next().
 */
बाह्य व्योम dvb_ringbuffer_pkt_dispose(काष्ठा dvb_ringbuffer *rbuf, माप_प्रकार idx);

/**
 * dvb_ringbuffer_pkt_next - Get the index of the next packet in a ringbuffer.
 *
 * @rbuf: Ringbuffer concerned.
 * @idx: Previous packet index, or -1 to वापस the first packet index.
 * @pktlen: On success, will be updated to contain the length of the packet
 *          in bytes.
 * वापसs Packet index (अगर >=0), or -1 अगर no packets available.
 */
बाह्य sमाप_प्रकार dvb_ringbuffer_pkt_next(काष्ठा dvb_ringbuffer *rbuf,
				       माप_प्रकार idx, माप_प्रकार *pktlen);

#पूर्ण_अगर /* _DVB_RINGBUFFER_H_ */
