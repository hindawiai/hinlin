<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * VMware VMCI driver (vmciContext.h)
 *
 * Copyright (C) 2012 VMware, Inc. All rights reserved.
 */

#अगर_अघोषित _VMCI_CONTEXT_H_
#घोषणा _VMCI_CONTEXT_H_

#समावेश <linux/vmw_vmci_defs.h>
#समावेश <linux/atomic.h>
#समावेश <linux/kref.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>

#समावेश "vmci_handle_array.h"
#समावेश "vmci_datagram.h"

/* Used to determine what checkpoपूर्णांक state to get and set. */
क्रमागत अणु
	VMCI_NOTIFICATION_CPT_STATE = 1,
	VMCI_WELLKNOWN_CPT_STATE    = 2,
	VMCI_DG_OUT_STATE           = 3,
	VMCI_DG_IN_STATE            = 4,
	VMCI_DG_IN_SIZE_STATE       = 5,
	VMCI_DOORBELL_CPT_STATE     = 6,
पूर्ण;

/* Host specअगरic काष्ठा used क्रम संकेतling */
काष्ठा vmci_host अणु
	रुको_queue_head_t रुको_queue;
पूर्ण;

काष्ठा vmci_handle_list अणु
	काष्ठा list_head node;
	काष्ठा vmci_handle handle;
पूर्ण;

काष्ठा vmci_ctx अणु
	काष्ठा list_head list_item;       /* For global VMCI list. */
	u32 cid;
	काष्ठा kref kref;
	काष्ठा list_head datagram_queue;  /* Head of per VM queue. */
	u32 pending_datagrams;
	माप_प्रकार datagram_queue_size;	  /* Size of datagram queue in bytes. */

	/*
	 * Version of the code that created
	 * this context; e.g., VMX.
	 */
	पूर्णांक user_version;
	spinlock_t lock;  /* Locks callQueue and handle_arrays. */

	/*
	 * queue_pairs attached to.  The array of
	 * handles क्रम queue pairs is accessed
	 * from the code क्रम QP API, and there
	 * it is रक्षित by the QP lock.  It
	 * is also accessed from the context
	 * clean up path, which करोes not
	 * require a lock.  VMCILock is not
	 * used to protect the QP array field.
	 */
	काष्ठा vmci_handle_arr *queue_pair_array;

	/* Doorbells created by context. */
	काष्ठा vmci_handle_arr *करोorbell_array;

	/* Doorbells pending क्रम context. */
	काष्ठा vmci_handle_arr *pending_करोorbell_array;

	/* Contexts current context is subscribing to. */
	काष्ठा list_head notअगरier_list;
	अचिन्हित पूर्णांक n_notअगरiers;

	काष्ठा vmci_host host_context;
	u32 priv_flags;

	स्थिर काष्ठा cred *cred;
	bool *notअगरy;		/* Notअगरy flag poपूर्णांकer - hosted only. */
	काष्ठा page *notअगरy_page;	/* Page backing the notअगरy UVA. */
पूर्ण;

/* VMCINotअगरyAddRemoveInfo: Used to add/हटाओ remote context notअगरications. */
काष्ठा vmci_ctx_info अणु
	u32 remote_cid;
	पूर्णांक result;
पूर्ण;

/* VMCICptBufInfo: Used to set/get current context's checkpoपूर्णांक state. */
काष्ठा vmci_ctx_chkpt_buf_info अणु
	u64 cpt_buf;
	u32 cpt_type;
	u32 buf_size;
	s32 result;
	u32 _pad;
पूर्ण;

/*
 * VMCINotअगरicationReceiveInfo: Used to recieve pending notअगरications
 * क्रम करोorbells and queue pairs.
 */
काष्ठा vmci_ctx_notअगरy_recv_info अणु
	u64 db_handle_buf_uva;
	u64 db_handle_buf_size;
	u64 qp_handle_buf_uva;
	u64 qp_handle_buf_size;
	s32 result;
	u32 _pad;
पूर्ण;

/*
 * Utilility function that checks whether two entities are allowed
 * to पूर्णांकeract. If one of them is restricted, the other one must
 * be trusted.
 */
अटल अंतरभूत bool vmci_deny_पूर्णांकeraction(u32 part_one, u32 part_two)
अणु
	वापस ((part_one & VMCI_PRIVILEGE_FLAG_RESTRICTED) &&
		!(part_two & VMCI_PRIVILEGE_FLAG_TRUSTED)) ||
	       ((part_two & VMCI_PRIVILEGE_FLAG_RESTRICTED) &&
		!(part_one & VMCI_PRIVILEGE_FLAG_TRUSTED));
पूर्ण

काष्ठा vmci_ctx *vmci_ctx_create(u32 cid, u32 flags,
				 uपूर्णांकptr_t event_hnd, पूर्णांक version,
				 स्थिर काष्ठा cred *cred);
व्योम vmci_ctx_destroy(काष्ठा vmci_ctx *context);

bool vmci_ctx_supports_host_qp(काष्ठा vmci_ctx *context);
पूर्णांक vmci_ctx_enqueue_datagram(u32 cid, काष्ठा vmci_datagram *dg);
पूर्णांक vmci_ctx_dequeue_datagram(काष्ठा vmci_ctx *context,
			      माप_प्रकार *max_size, काष्ठा vmci_datagram **dg);
पूर्णांक vmci_ctx_pending_datagrams(u32 cid, u32 *pending);
काष्ठा vmci_ctx *vmci_ctx_get(u32 cid);
व्योम vmci_ctx_put(काष्ठा vmci_ctx *context);
bool vmci_ctx_exists(u32 cid);

पूर्णांक vmci_ctx_add_notअगरication(u32 context_id, u32 remote_cid);
पूर्णांक vmci_ctx_हटाओ_notअगरication(u32 context_id, u32 remote_cid);
पूर्णांक vmci_ctx_get_chkpt_state(u32 context_id, u32 cpt_type,
			     u32 *num_cids, व्योम **cpt_buf_ptr);
पूर्णांक vmci_ctx_set_chkpt_state(u32 context_id, u32 cpt_type,
			     u32 num_cids, व्योम *cpt_buf);

पूर्णांक vmci_ctx_qp_create(काष्ठा vmci_ctx *context, काष्ठा vmci_handle handle);
पूर्णांक vmci_ctx_qp_destroy(काष्ठा vmci_ctx *context, काष्ठा vmci_handle handle);
bool vmci_ctx_qp_exists(काष्ठा vmci_ctx *context, काष्ठा vmci_handle handle);

व्योम vmci_ctx_check_संकेत_notअगरy(काष्ठा vmci_ctx *context);
व्योम vmci_ctx_unset_notअगरy(काष्ठा vmci_ctx *context);

पूर्णांक vmci_ctx_dbell_create(u32 context_id, काष्ठा vmci_handle handle);
पूर्णांक vmci_ctx_dbell_destroy(u32 context_id, काष्ठा vmci_handle handle);
पूर्णांक vmci_ctx_dbell_destroy_all(u32 context_id);
पूर्णांक vmci_ctx_notअगरy_dbell(u32 cid, काष्ठा vmci_handle handle,
			  u32 src_priv_flags);

पूर्णांक vmci_ctx_rcv_notअगरications_get(u32 context_id, काष्ठा vmci_handle_arr
				   **db_handle_array, काष्ठा vmci_handle_arr
				   **qp_handle_array);
व्योम vmci_ctx_rcv_notअगरications_release(u32 context_id, काष्ठा vmci_handle_arr
					*db_handle_array, काष्ठा vmci_handle_arr
					*qp_handle_array, bool success);

अटल अंतरभूत u32 vmci_ctx_get_id(काष्ठा vmci_ctx *context)
अणु
	अगर (!context)
		वापस VMCI_INVALID_ID;
	वापस context->cid;
पूर्ण

#पूर्ण_अगर /* _VMCI_CONTEXT_H_ */
