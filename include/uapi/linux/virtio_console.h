<शैली गुरु>
/*
 * This header, excluding the #अगर_घोषित __KERNEL__ part, is BSD licensed so
 * anyone can use the definitions to implement compatible drivers/servers:
 *
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    करोcumentation and/or other materials provided with the distribution.
 * 3. Neither the name of IBM nor the names of its contributors
 *    may be used to enकरोrse or promote products derived from this software
 *    without specअगरic prior written permission.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL IBM OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Copyright (C) Red Hat, Inc., 2009, 2010, 2011
 * Copyright (C) Amit Shah <amit.shah@redhat.com>, 2009, 2010, 2011
 */
#अगर_अघोषित _UAPI_LINUX_VIRTIO_CONSOLE_H
#घोषणा _UAPI_LINUX_VIRTIO_CONSOLE_H
#समावेश <linux/types.h>
#समावेश <linux/virtio_types.h>
#समावेश <linux/virtio_ids.h>
#समावेश <linux/virtio_config.h>

/* Feature bits */
#घोषणा VIRTIO_CONSOLE_F_SIZE	0	/* Does host provide console size? */
#घोषणा VIRTIO_CONSOLE_F_MULTIPORT 1	/* Does host provide multiple ports? */
#घोषणा VIRTIO_CONSOLE_F_EMERG_WRITE 2 /* Does host support emergency ग_लिखो? */

#घोषणा VIRTIO_CONSOLE_BAD_ID		(~(__u32)0)

काष्ठा virtio_console_config अणु
	/* colums of the screens */
	__virtio16 cols;
	/* rows of the screens */
	__virtio16 rows;
	/* max. number of ports this device can hold */
	__virtio32 max_nr_ports;
	/* emergency ग_लिखो रेजिस्टर */
	__virtio32 emerg_wr;
पूर्ण __attribute__((packed));

/*
 * A message that's passed between the Host and the Guest क्रम a
 * particular port.
 */
काष्ठा virtio_console_control अणु
	__virtio32 id;		/* Port number */
	__virtio16 event;	/* The kind of control event (see below) */
	__virtio16 value;	/* Extra inक्रमmation क्रम the key */
पूर्ण;

/* Some events क्रम control messages */
#घोषणा VIRTIO_CONSOLE_DEVICE_READY	0
#घोषणा VIRTIO_CONSOLE_PORT_ADD		1
#घोषणा VIRTIO_CONSOLE_PORT_REMOVE	2
#घोषणा VIRTIO_CONSOLE_PORT_READY	3
#घोषणा VIRTIO_CONSOLE_CONSOLE_PORT	4
#घोषणा VIRTIO_CONSOLE_RESIZE		5
#घोषणा VIRTIO_CONSOLE_PORT_OPEN	6
#घोषणा VIRTIO_CONSOLE_PORT_NAME	7


#पूर्ण_अगर /* _UAPI_LINUX_VIRTIO_CONSOLE_H */
