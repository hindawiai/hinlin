<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */
/*
 * Copyright तऊ 2016-2019 Intel Corporation
 */

#अगर_अघोषित _INTEL_GUC_CT_H_
#घोषणा _INTEL_GUC_CT_H_

#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>

#समावेश "intel_guc_fwif.h"

काष्ठा i915_vma;
काष्ठा पूर्णांकel_guc;

/**
 * DOC: Command Transport (CT).
 *
 * Buffer based command transport is a replacement क्रम MMIO based mechanism.
 * It can be used to perक्रमm both host-2-guc and guc-to-host communication.
 */

/** Represents single command transport buffer.
 *
 * A single command transport buffer consists of two parts, the header
 * record (command transport buffer descriptor) and the actual buffer which
 * holds the commands.
 *
 * @desc: poपूर्णांकer to the buffer descriptor
 * @cmds: poपूर्णांकer to the commands buffer
 */
काष्ठा पूर्णांकel_guc_ct_buffer अणु
	काष्ठा guc_ct_buffer_desc *desc;
	u32 *cmds;
पूर्ण;


/** Top-level काष्ठाure क्रम Command Transport related data
 *
 * Includes a pair of CT buffers क्रम bi-directional communication and tracking
 * क्रम the H2G and G2H requests sent and received through the buffers.
 */
काष्ठा पूर्णांकel_guc_ct अणु
	काष्ठा i915_vma *vma;
	bool enabled;

	/* buffers क्रम sending(0) and receiving(1) commands */
	काष्ठा पूर्णांकel_guc_ct_buffer ctbs[2];

	काष्ठा अणु
		u32 last_fence; /* last fence used to send request */

		spinlock_t lock; /* protects pending requests list */
		काष्ठा list_head pending; /* requests रुकोing क्रम response */

		काष्ठा list_head incoming; /* incoming requests */
		काष्ठा work_काष्ठा worker; /* handler क्रम incoming requests */
	पूर्ण requests;
पूर्ण;

व्योम पूर्णांकel_guc_ct_init_early(काष्ठा पूर्णांकel_guc_ct *ct);
पूर्णांक पूर्णांकel_guc_ct_init(काष्ठा पूर्णांकel_guc_ct *ct);
व्योम पूर्णांकel_guc_ct_fini(काष्ठा पूर्णांकel_guc_ct *ct);
पूर्णांक पूर्णांकel_guc_ct_enable(काष्ठा पूर्णांकel_guc_ct *ct);
व्योम पूर्णांकel_guc_ct_disable(काष्ठा पूर्णांकel_guc_ct *ct);

अटल अंतरभूत व्योम पूर्णांकel_guc_ct_sanitize(काष्ठा पूर्णांकel_guc_ct *ct)
अणु
	ct->enabled = false;
पूर्ण

अटल अंतरभूत bool पूर्णांकel_guc_ct_enabled(काष्ठा पूर्णांकel_guc_ct *ct)
अणु
	वापस ct->enabled;
पूर्ण

पूर्णांक पूर्णांकel_guc_ct_send(काष्ठा पूर्णांकel_guc_ct *ct, स्थिर u32 *action, u32 len,
		      u32 *response_buf, u32 response_buf_size);
व्योम पूर्णांकel_guc_ct_event_handler(काष्ठा पूर्णांकel_guc_ct *ct);

#पूर्ण_अगर /* _INTEL_GUC_CT_H_ */
