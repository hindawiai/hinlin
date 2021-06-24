<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ */
/*
 * SSH message parser.
 *
 * Copyright (C) 2019-2020 Maximilian Luz <luzmaximilian@gmail.com>
 */

#अगर_अघोषित _SURFACE_AGGREGATOR_SSH_PARSER_H
#घोषणा _SURFACE_AGGREGATOR_SSH_PARSER_H

#समावेश <linux/device.h>
#समावेश <linux/kfअगरo.h>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>

#समावेश <linux/surface_aggregator/serial_hub.h>

/**
 * काष्ठा sshp_buf - Parser buffer क्रम SSH messages.
 * @ptr: Poपूर्णांकer to the beginning of the buffer.
 * @len: Number of bytes used in the buffer.
 * @cap: Maximum capacity of the buffer.
 */
काष्ठा sshp_buf अणु
	u8    *ptr;
	माप_प्रकार len;
	माप_प्रकार cap;
पूर्ण;

/**
 * sshp_buf_init() - Initialize a SSH parser buffer.
 * @buf: The buffer to initialize.
 * @ptr: The memory backing the buffer.
 * @cap: The length of the memory backing the buffer, i.e. its capacity.
 *
 * Initializes the buffer with the given memory as backing and set its used
 * length to zero.
 */
अटल अंतरभूत व्योम sshp_buf_init(काष्ठा sshp_buf *buf, u8 *ptr, माप_प्रकार cap)
अणु
	buf->ptr = ptr;
	buf->len = 0;
	buf->cap = cap;
पूर्ण

/**
 * sshp_buf_alloc() - Allocate and initialize a SSH parser buffer.
 * @buf:   The buffer to initialize/allocate to.
 * @cap:   The desired capacity of the buffer.
 * @flags: The flags used क्रम allocating the memory.
 *
 * Allocates @cap bytes and initializes the provided buffer काष्ठा with the
 * allocated memory.
 *
 * Return: Returns zero on success and %-ENOMEM अगर allocation failed.
 */
अटल अंतरभूत पूर्णांक sshp_buf_alloc(काष्ठा sshp_buf *buf, माप_प्रकार cap, gfp_t flags)
अणु
	u8 *ptr;

	ptr = kzalloc(cap, flags);
	अगर (!ptr)
		वापस -ENOMEM;

	sshp_buf_init(buf, ptr, cap);
	वापस 0;
पूर्ण

/**
 * sshp_buf_मुक्त() - Free a SSH parser buffer.
 * @buf: The buffer to मुक्त.
 *
 * Frees a SSH parser buffer by मुक्तing the memory backing it and then
 * resetting its poपूर्णांकer to %शून्य and length and capacity to zero. Intended to
 * मुक्त a buffer previously allocated with sshp_buf_alloc().
 */
अटल अंतरभूत व्योम sshp_buf_मुक्त(काष्ठा sshp_buf *buf)
अणु
	kमुक्त(buf->ptr);
	buf->ptr = शून्य;
	buf->len = 0;
	buf->cap = 0;
पूर्ण

/**
 * sshp_buf_drop() - Drop data from the beginning of the buffer.
 * @buf: The buffer to drop data from.
 * @n:   The number of bytes to drop.
 *
 * Drops the first @n bytes from the buffer. Re-aligns any reमुख्यing data to
 * the beginning of the buffer.
 */
अटल अंतरभूत व्योम sshp_buf_drop(काष्ठा sshp_buf *buf, माप_प्रकार n)
अणु
	स_हटाओ(buf->ptr, buf->ptr + n, buf->len - n);
	buf->len -= n;
पूर्ण

/**
 * sshp_buf_पढ़ो_from_fअगरo() - Transfer data from a fअगरo to the buffer.
 * @buf:  The buffer to ग_लिखो the data पूर्णांकo.
 * @fअगरo: The fअगरo to पढ़ो the data from.
 *
 * Transfers the data contained in the fअगरo to the buffer, removing it from
 * the fअगरo. This function will try to transfer as much data as possible,
 * limited either by the reमुख्यing space in the buffer or by the number of
 * bytes available in the fअगरo.
 *
 * Return: Returns the number of bytes transferred.
 */
अटल अंतरभूत माप_प्रकार sshp_buf_पढ़ो_from_fअगरo(काष्ठा sshp_buf *buf,
					     काष्ठा kfअगरo *fअगरo)
अणु
	माप_प्रकार n;

	n =  kfअगरo_out(fअगरo, buf->ptr + buf->len, buf->cap - buf->len);
	buf->len += n;

	वापस n;
पूर्ण

/**
 * sshp_buf_span_from() - Initialize a span from the given buffer and offset.
 * @buf:    The buffer to create the span from.
 * @offset: The offset in the buffer at which the span should start.
 * @span:   The span to initialize (output).
 *
 * Initializes the provided span to poपूर्णांक to the memory at the given offset in
 * the buffer, with the length of the span being capped by the number of bytes
 * used in the buffer after the offset (i.e. bytes reमुख्यing after the
 * offset).
 *
 * Warning: This function करोes not validate that @offset is less than or equal
 * to the number of bytes used in the buffer or the buffer capacity. This must
 * be guaranteed by the caller.
 */
अटल अंतरभूत व्योम sshp_buf_span_from(काष्ठा sshp_buf *buf, माप_प्रकार offset,
				      काष्ठा ssam_span *span)
अणु
	span->ptr = buf->ptr + offset;
	span->len = buf->len - offset;
पूर्ण

bool sshp_find_syn(स्थिर काष्ठा ssam_span *src, काष्ठा ssam_span *rem);

पूर्णांक sshp_parse_frame(स्थिर काष्ठा device *dev, स्थिर काष्ठा ssam_span *source,
		     काष्ठा ssh_frame **frame, काष्ठा ssam_span *payload,
		     माप_प्रकार maxlen);

पूर्णांक sshp_parse_command(स्थिर काष्ठा device *dev, स्थिर काष्ठा ssam_span *source,
		       काष्ठा ssh_command **command,
		       काष्ठा ssam_span *command_data);

#पूर्ण_अगर /* _SURFACE_AGGREGATOR_SSH_PARSER_h */
