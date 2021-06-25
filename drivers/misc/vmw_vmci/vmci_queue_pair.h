<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VMware VMCI Driver
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#अगर_अघोषित _VMCI_QUEUE_PAIR_H_
#घोषणा _VMCI_QUEUE_PAIR_H_

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/types.h>

#समावेश "vmci_context.h"

/* Callback needed क्रम correctly रुकोing on events. */
प्रकार पूर्णांक (*vmci_event_release_cb) (व्योम *client_data);

/* Guest device port I/O. */
काष्ठा ppn_set अणु
	u64 num_produce_pages;
	u64 num_consume_pages;
	u64 *produce_ppns;
	u64 *consume_ppns;
	bool initialized;
पूर्ण;

/* VMCIqueue_pairAllocInfo */
काष्ठा vmci_qp_alloc_info अणु
	काष्ठा vmci_handle handle;
	u32 peer;
	u32 flags;
	u64 produce_size;
	u64 consume_size;
	u64 ppn_va;	/* Start VA of queue pair PPNs. */
	u64 num_ppns;
	s32 result;
	u32 version;
पूर्ण;

/* VMCIqueue_pairSetVAInfo */
काष्ठा vmci_qp_set_va_info अणु
	काष्ठा vmci_handle handle;
	u64 va;		/* Start VA of queue pair PPNs. */
	u64 num_ppns;
	u32 version;
	s32 result;
पूर्ण;

/*
 * For backwards compatibility, here is a version of the
 * VMCIqueue_pairPageFileInfo beक्रमe host support end-poपूर्णांकs was added.
 * Note that the current version of that काष्ठाure requires VMX to
 * pass करोwn the VA of the mapped file.  Beक्रमe host support was added
 * there was nothing of the sort.  So, when the driver sees the ioctl
 * with a parameter that is the माप
 * VMCIqueue_pairPageFileInfo_NoHostQP then it can infer that the version
 * of VMX running can't attach to host end points because it doesn't
 * provide the VA of the mapped files.
 *
 * The Linux driver करोesn't get an indication of the size of the
 * काष्ठाure passed करोwn from user space.  So, to fix a दीर्घ standing
 * but unfiled bug, the _pad field has been नामd to version.
 * Existing versions of VMX always initialize the PageFileInfo
 * काष्ठाure so that _pad, er, version is set to 0.
 *
 * A version value of 1 indicates that the size of the काष्ठाure has
 * been increased to include two UVA's: produce_uva and consume_uva.
 * These UVA's are of the mmap()'d queue contents backing files.
 *
 * In addition, अगर when VMX is sending करोwn the
 * VMCIqueue_pairPageFileInfo काष्ठाure it माला_लो an error then it will
 * try again with the _NoHostQP version of the file to see अगर an older
 * VMCI kernel module is running.
 */

/* VMCIqueue_pairPageFileInfo */
काष्ठा vmci_qp_page_file_info अणु
	काष्ठा vmci_handle handle;
	u64 produce_page_file;	  /* User VA. */
	u64 consume_page_file;	  /* User VA. */
	u64 produce_page_file_size;  /* Size of the file name array. */
	u64 consume_page_file_size;  /* Size of the file name array. */
	s32 result;
	u32 version;	/* Was _pad. */
	u64 produce_va;	/* User VA of the mapped file. */
	u64 consume_va;	/* User VA of the mapped file. */
पूर्ण;

/* vmci queuepair detach info */
काष्ठा vmci_qp_dtch_info अणु
	काष्ठा vmci_handle handle;
	s32 result;
	u32 _pad;
पूर्ण;

/*
 * काष्ठा vmci_qp_page_store describes how the memory of a given queue pair
 * is backed. When the queue pair is between the host and a guest, the
 * page store consists of references to the guest pages. On vmkernel,
 * this is a list of PPNs, and on hosted, it is a user VA where the
 * queue pair is mapped पूर्णांकo the VMX address space.
 */
काष्ठा vmci_qp_page_store अणु
	/* Reference to pages backing the queue pair. */
	u64 pages;
	/* Length of pageList/भव address range (in pages). */
	u32 len;
पूर्ण;

/*
 * This data type contains the inक्रमmation about a queue.
 * There are two queues (hence, queue pairs) per transaction model between a
 * pair of end poपूर्णांकs, A & B.  One queue is used by end poपूर्णांक A to transmit
 * commands and responses to B.  The other queue is used by B to transmit
 * commands and responses.
 *
 * काष्ठा vmci_queue_kern_अगर is a per-OS defined Queue काष्ठाure.  It contains
 * either a direct poपूर्णांकer to the linear address of the buffer contents or a
 * poपूर्णांकer to काष्ठाures which help the OS locate those data pages.  See
 * vmciKernelIf.c क्रम each platक्रमm क्रम its definition.
 */
काष्ठा vmci_queue अणु
	काष्ठा vmci_queue_header *q_header;
	काष्ठा vmci_queue_header *saved_header;
	काष्ठा vmci_queue_kern_अगर *kernel_अगर;
पूर्ण;

/*
 * Utility function that checks whether the fields of the page
 * store contain valid values.
 * Result:
 * true अगर the page store is wellक्रमmed. false otherwise.
 */
अटल अंतरभूत bool
VMCI_QP_PAGESTORE_IS_WELLFORMED(काष्ठा vmci_qp_page_store *page_store)
अणु
	वापस page_store->len >= 2;
पूर्ण

व्योम vmci_qp_broker_निकास(व्योम);
पूर्णांक vmci_qp_broker_alloc(काष्ठा vmci_handle handle, u32 peer,
			 u32 flags, u32 priv_flags,
			 u64 produce_size, u64 consume_size,
			 काष्ठा vmci_qp_page_store *page_store,
			 काष्ठा vmci_ctx *context);
पूर्णांक vmci_qp_broker_set_page_store(काष्ठा vmci_handle handle,
				  u64 produce_uva, u64 consume_uva,
				  काष्ठा vmci_ctx *context);
पूर्णांक vmci_qp_broker_detach(काष्ठा vmci_handle handle, काष्ठा vmci_ctx *context);

व्योम vmci_qp_guest_endpoपूर्णांकs_निकास(व्योम);

पूर्णांक vmci_qp_alloc(काष्ठा vmci_handle *handle,
		  काष्ठा vmci_queue **produce_q, u64 produce_size,
		  काष्ठा vmci_queue **consume_q, u64 consume_size,
		  u32 peer, u32 flags, u32 priv_flags,
		  bool guest_endpoपूर्णांक, vmci_event_release_cb wakeup_cb,
		  व्योम *client_data);
पूर्णांक vmci_qp_broker_map(काष्ठा vmci_handle handle,
		       काष्ठा vmci_ctx *context, u64 guest_mem);
पूर्णांक vmci_qp_broker_unmap(काष्ठा vmci_handle handle,
			 काष्ठा vmci_ctx *context, u32 gid);

#पूर्ण_अगर /* _VMCI_QUEUE_PAIR_H_ */
