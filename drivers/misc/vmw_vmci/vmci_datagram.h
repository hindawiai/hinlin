<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#अगर_अघोषित _VMCI_DATAGRAM_H_
#घोषणा _VMCI_DATAGRAM_H_

#समावेश <linux/types.h>
#समावेश <linux/list.h>

#समावेश "vmci_context.h"

#घोषणा VMCI_MAX_DELAYED_DG_HOST_QUEUE_SIZE 256

/*
 * The काष्ठा vmci_datagram_queue_entry is a queue header क्रम the in-kernel VMCI
 * datagram queues. It is allocated in non-paged memory, as the
 * content is accessed जबतक holding a spinlock. The pending datagram
 * itself may be allocated from paged memory. We shaकरोw the size of
 * the datagram in the non-paged queue entry as this size is used
 * जबतक holding the same spinlock as above.
 */
काष्ठा vmci_datagram_queue_entry अणु
	काष्ठा list_head list_item;	/* For queuing. */
	माप_प्रकार dg_size;		/* Size of datagram. */
	काष्ठा vmci_datagram *dg;	/* Pending datagram. */
पूर्ण;

/* VMCIDatagramSendRecvInfo */
काष्ठा vmci_datagram_snd_rcv_info अणु
	u64 addr;
	u32 len;
	s32 result;
पूर्ण;

/* Datagram API क्रम non-खुला use. */
पूर्णांक vmci_datagram_dispatch(u32 context_id, काष्ठा vmci_datagram *dg,
			   bool from_guest);
पूर्णांक vmci_datagram_invoke_guest_handler(काष्ठा vmci_datagram *dg);

#पूर्ण_अगर /* _VMCI_DATAGRAM_H_ */
