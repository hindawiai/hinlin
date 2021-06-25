<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2016-2019 Intel Corporation
 */

#समावेश "i915_drv.h"
#समावेश "intel_guc_ct.h"
#समावेश "gt/intel_gt.h"

#घोषणा CT_ERROR(_ct, _fmt, ...) \
	DRM_DEV_ERROR(ct_to_dev(_ct), "CT: " _fmt, ##__VA_ARGS__)
#अगर_घोषित CONFIG_DRM_I915_DEBUG_GUC
#घोषणा CT_DEBUG(_ct, _fmt, ...) \
	DRM_DEV_DEBUG_DRIVER(ct_to_dev(_ct), "CT: " _fmt, ##__VA_ARGS__)
#अन्यथा
#घोषणा CT_DEBUG(...)	करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

काष्ठा ct_request अणु
	काष्ठा list_head link;
	u32 fence;
	u32 status;
	u32 response_len;
	u32 *response_buf;
पूर्ण;

काष्ठा ct_incoming_request अणु
	काष्ठा list_head link;
	u32 msg[];
पूर्ण;

क्रमागत अणु CTB_SEND = 0, CTB_RECV = 1 पूर्ण;

क्रमागत अणु CTB_OWNER_HOST = 0 पूर्ण;

अटल व्योम ct_incoming_request_worker_func(काष्ठा work_काष्ठा *w);

/**
 * पूर्णांकel_guc_ct_init_early - Initialize CT state without requiring device access
 * @ct: poपूर्णांकer to CT काष्ठा
 */
व्योम पूर्णांकel_guc_ct_init_early(काष्ठा पूर्णांकel_guc_ct *ct)
अणु
	spin_lock_init(&ct->requests.lock);
	INIT_LIST_HEAD(&ct->requests.pending);
	INIT_LIST_HEAD(&ct->requests.incoming);
	INIT_WORK(&ct->requests.worker, ct_incoming_request_worker_func);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_guc *ct_to_guc(काष्ठा पूर्णांकel_guc_ct *ct)
अणु
	वापस container_of(ct, काष्ठा पूर्णांकel_guc, ct);
पूर्ण

अटल अंतरभूत काष्ठा पूर्णांकel_gt *ct_to_gt(काष्ठा पूर्णांकel_guc_ct *ct)
अणु
	वापस guc_to_gt(ct_to_guc(ct));
पूर्ण

अटल अंतरभूत काष्ठा drm_i915_निजी *ct_to_i915(काष्ठा पूर्णांकel_guc_ct *ct)
अणु
	वापस ct_to_gt(ct)->i915;
पूर्ण

अटल अंतरभूत काष्ठा device *ct_to_dev(काष्ठा पूर्णांकel_guc_ct *ct)
अणु
	वापस ct_to_i915(ct)->drm.dev;
पूर्ण

अटल अंतरभूत स्थिर अक्षर *guc_ct_buffer_type_to_str(u32 type)
अणु
	चयन (type) अणु
	हाल INTEL_GUC_CT_BUFFER_TYPE_SEND:
		वापस "SEND";
	हाल INTEL_GUC_CT_BUFFER_TYPE_RECV:
		वापस "RECV";
	शेष:
		वापस "<invalid>";
	पूर्ण
पूर्ण

अटल व्योम guc_ct_buffer_desc_init(काष्ठा guc_ct_buffer_desc *desc,
				    u32 cmds_addr, u32 size)
अणु
	स_रखो(desc, 0, माप(*desc));
	desc->addr = cmds_addr;
	desc->size = size;
	desc->owner = CTB_OWNER_HOST;
पूर्ण

अटल व्योम guc_ct_buffer_desc_reset(काष्ठा guc_ct_buffer_desc *desc)
अणु
	desc->head = 0;
	desc->tail = 0;
	desc->is_in_error = 0;
पूर्ण

अटल पूर्णांक guc_action_रेजिस्टर_ct_buffer(काष्ठा पूर्णांकel_guc *guc,
					 u32 desc_addr,
					 u32 type)
अणु
	u32 action[] = अणु
		INTEL_GUC_ACTION_REGISTER_COMMAND_TRANSPORT_BUFFER,
		desc_addr,
		माप(काष्ठा guc_ct_buffer_desc),
		type
	पूर्ण;

	/* Can't use generic send(), CT registration must go over MMIO */
	वापस पूर्णांकel_guc_send_mmio(guc, action, ARRAY_SIZE(action), शून्य, 0);
पूर्ण

अटल पूर्णांक ct_रेजिस्टर_buffer(काष्ठा पूर्णांकel_guc_ct *ct, u32 desc_addr, u32 type)
अणु
	पूर्णांक err = guc_action_रेजिस्टर_ct_buffer(ct_to_guc(ct), desc_addr, type);

	अगर (unlikely(err))
		CT_ERROR(ct, "Failed to register %s buffer (err=%d)\n",
			 guc_ct_buffer_type_to_str(type), err);
	वापस err;
पूर्ण

अटल पूर्णांक guc_action_deरेजिस्टर_ct_buffer(काष्ठा पूर्णांकel_guc *guc, u32 type)
अणु
	u32 action[] = अणु
		INTEL_GUC_ACTION_DEREGISTER_COMMAND_TRANSPORT_BUFFER,
		CTB_OWNER_HOST,
		type
	पूर्ण;

	/* Can't use generic send(), CT deregistration must go over MMIO */
	वापस पूर्णांकel_guc_send_mmio(guc, action, ARRAY_SIZE(action), शून्य, 0);
पूर्ण

अटल पूर्णांक ct_deरेजिस्टर_buffer(काष्ठा पूर्णांकel_guc_ct *ct, u32 type)
अणु
	पूर्णांक err = guc_action_deरेजिस्टर_ct_buffer(ct_to_guc(ct), type);

	अगर (unlikely(err))
		CT_ERROR(ct, "Failed to deregister %s buffer (err=%d)\n",
			 guc_ct_buffer_type_to_str(type), err);
	वापस err;
पूर्ण

/**
 * पूर्णांकel_guc_ct_init - Init buffer-based communication
 * @ct: poपूर्णांकer to CT काष्ठा
 *
 * Allocate memory required क्रम buffer-based communication.
 *
 * Return: 0 on success, a negative त्रुटि_सं code on failure.
 */
पूर्णांक पूर्णांकel_guc_ct_init(काष्ठा पूर्णांकel_guc_ct *ct)
अणु
	काष्ठा पूर्णांकel_guc *guc = ct_to_guc(ct);
	व्योम *blob;
	पूर्णांक err;
	पूर्णांक i;

	GEM_BUG_ON(ct->vma);

	/* We allocate 1 page to hold both descriptors and both buffers.
	 *       ___________.....................
	 *      |desc (SEND)|                   :
	 *      |___________|                   PAGE/4
	 *      :___________....................:
	 *      |desc (RECV)|                   :
	 *      |___________|                   PAGE/4
	 *      :_______________________________:
	 *      |cmds (SEND)                    |
	 *      |                               PAGE/4
	 *      |_______________________________|
	 *      |cmds (RECV)                    |
	 *      |                               PAGE/4
	 *      |_______________________________|
	 *
	 * Each message can use a maximum of 32 dwords and we करोn't expect to
	 * have more than 1 in flight at any समय, so we have enough space.
	 * Some logic further ahead will rely on the fact that there is only 1
	 * page and that it is always mapped, so अगर the size is changed the
	 * other code will need updating as well.
	 */

	err = पूर्णांकel_guc_allocate_and_map_vma(guc, PAGE_SIZE, &ct->vma, &blob);
	अगर (unlikely(err)) अणु
		CT_ERROR(ct, "Failed to allocate CT channel (err=%d)\n", err);
		वापस err;
	पूर्ण

	CT_DEBUG(ct, "vma base=%#x\n", पूर्णांकel_guc_ggtt_offset(guc, ct->vma));

	/* store poपूर्णांकers to desc and cmds */
	क्रम (i = 0; i < ARRAY_SIZE(ct->ctbs); i++) अणु
		GEM_BUG_ON((i !=  CTB_SEND) && (i != CTB_RECV));
		ct->ctbs[i].desc = blob + PAGE_SIZE/4 * i;
		ct->ctbs[i].cmds = blob + PAGE_SIZE/4 * i + PAGE_SIZE/2;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * पूर्णांकel_guc_ct_fini - Fini buffer-based communication
 * @ct: poपूर्णांकer to CT काष्ठा
 *
 * Deallocate memory required क्रम buffer-based communication.
 */
व्योम पूर्णांकel_guc_ct_fini(काष्ठा पूर्णांकel_guc_ct *ct)
अणु
	GEM_BUG_ON(ct->enabled);

	i915_vma_unpin_and_release(&ct->vma, I915_VMA_RELEASE_MAP);
	स_रखो(ct, 0, माप(*ct));
पूर्ण

/**
 * पूर्णांकel_guc_ct_enable - Enable buffer based command transport.
 * @ct: poपूर्णांकer to CT काष्ठा
 *
 * Return: 0 on success, a negative त्रुटि_सं code on failure.
 */
पूर्णांक पूर्णांकel_guc_ct_enable(काष्ठा पूर्णांकel_guc_ct *ct)
अणु
	काष्ठा पूर्णांकel_guc *guc = ct_to_guc(ct);
	u32 base, cmds, size;
	पूर्णांक err;
	पूर्णांक i;

	GEM_BUG_ON(ct->enabled);

	/* vma should be alपढ़ोy allocated and map'ed */
	GEM_BUG_ON(!ct->vma);
	base = पूर्णांकel_guc_ggtt_offset(guc, ct->vma);

	/* (re)initialize descriptors
	 * cmds buffers are in the second half of the blob page
	 */
	क्रम (i = 0; i < ARRAY_SIZE(ct->ctbs); i++) अणु
		GEM_BUG_ON((i != CTB_SEND) && (i != CTB_RECV));
		cmds = base + PAGE_SIZE / 4 * i + PAGE_SIZE / 2;
		size = PAGE_SIZE / 4;
		CT_DEBUG(ct, "%d: addr=%#x size=%u\n", i, cmds, size);
		guc_ct_buffer_desc_init(ct->ctbs[i].desc, cmds, size);
	पूर्ण

	/*
	 * Register both CT buffers starting with RECV buffer.
	 * Descriptors are in first half of the blob.
	 */
	err = ct_रेजिस्टर_buffer(ct, base + PAGE_SIZE / 4 * CTB_RECV,
				 INTEL_GUC_CT_BUFFER_TYPE_RECV);
	अगर (unlikely(err))
		जाओ err_out;

	err = ct_रेजिस्टर_buffer(ct, base + PAGE_SIZE / 4 * CTB_SEND,
				 INTEL_GUC_CT_BUFFER_TYPE_SEND);
	अगर (unlikely(err))
		जाओ err_deरेजिस्टर;

	ct->enabled = true;

	वापस 0;

err_deरेजिस्टर:
	ct_deरेजिस्टर_buffer(ct, INTEL_GUC_CT_BUFFER_TYPE_RECV);
err_out:
	CT_ERROR(ct, "Failed to open open CT channel (err=%d)\n", err);
	वापस err;
पूर्ण

/**
 * पूर्णांकel_guc_ct_disable - Disable buffer based command transport.
 * @ct: poपूर्णांकer to CT काष्ठा
 */
व्योम पूर्णांकel_guc_ct_disable(काष्ठा पूर्णांकel_guc_ct *ct)
अणु
	काष्ठा पूर्णांकel_guc *guc = ct_to_guc(ct);

	GEM_BUG_ON(!ct->enabled);

	ct->enabled = false;

	अगर (पूर्णांकel_guc_is_fw_running(guc)) अणु
		ct_deरेजिस्टर_buffer(ct, INTEL_GUC_CT_BUFFER_TYPE_SEND);
		ct_deरेजिस्टर_buffer(ct, INTEL_GUC_CT_BUFFER_TYPE_RECV);
	पूर्ण
पूर्ण

अटल u32 ct_get_next_fence(काष्ठा पूर्णांकel_guc_ct *ct)
अणु
	/* For now it's trivial */
	वापस ++ct->requests.last_fence;
पूर्ण

/**
 * DOC: CTB Host to GuC request
 *
 * Format of the CTB Host to GuC request message is as follows::
 *
 *      +------------+---------+---------+---------+---------+
 *      |   msg[0]   |   [1]   |   [2]   |   ...   |  [n-1]  |
 *      +------------+---------+---------+---------+---------+
 *      |   MESSAGE  |       MESSAGE PAYLOAD                 |
 *      +   HEADER   +---------+---------+---------+---------+
 *      |            |    0    |    1    |   ...   |    n    |
 *      +============+=========+=========+=========+=========+
 *      |  len >= 1  |  FENCE  |     request specअगरic data   |
 *      +------+-----+---------+---------+---------+---------+
 *
 *                   ^-----------------len-------------------^
 */

अटल पूर्णांक ct_ग_लिखो(काष्ठा पूर्णांकel_guc_ct *ct,
		    स्थिर u32 *action,
		    u32 len /* in dwords */,
		    u32 fence,
		    bool want_response)
अणु
	काष्ठा पूर्णांकel_guc_ct_buffer *ctb = &ct->ctbs[CTB_SEND];
	काष्ठा guc_ct_buffer_desc *desc = ctb->desc;
	u32 head = desc->head;
	u32 tail = desc->tail;
	u32 size = desc->size;
	u32 used;
	u32 header;
	u32 *cmds = ctb->cmds;
	अचिन्हित पूर्णांक i;

	अगर (unlikely(desc->is_in_error))
		वापस -EPIPE;

	अगर (unlikely(!IS_ALIGNED(head | tail | size, 4) ||
		     (tail | head) >= size))
		जाओ corrupted;

	/* later calculations will be करोne in dwords */
	head /= 4;
	tail /= 4;
	size /= 4;

	/*
	 * tail == head condition indicates empty. GuC FW करोes not support
	 * using up the entire buffer to get tail == head meaning full.
	 */
	अगर (tail < head)
		used = (size - head) + tail;
	अन्यथा
		used = tail - head;

	/* make sure there is a space including extra dw क्रम the fence */
	अगर (unlikely(used + len + 1 >= size))
		वापस -ENOSPC;

	/*
	 * Write the message. The क्रमmat is the following:
	 * DW0: header (including action code)
	 * DW1: fence
	 * DW2+: action data
	 */
	header = (len << GUC_CT_MSG_LEN_SHIFT) |
		 (GUC_CT_MSG_WRITE_FENCE_TO_DESC) |
		 (want_response ? GUC_CT_MSG_SEND_STATUS : 0) |
		 (action[0] << GUC_CT_MSG_ACTION_SHIFT);

	CT_DEBUG(ct, "writing %*ph %*ph %*ph\n",
		 4, &header, 4, &fence, 4 * (len - 1), &action[1]);

	cmds[tail] = header;
	tail = (tail + 1) % size;

	cmds[tail] = fence;
	tail = (tail + 1) % size;

	क्रम (i = 1; i < len; i++) अणु
		cmds[tail] = action[i];
		tail = (tail + 1) % size;
	पूर्ण
	GEM_BUG_ON(tail > size);

	/* now update desc tail (back in bytes) */
	desc->tail = tail * 4;
	वापस 0;

corrupted:
	CT_ERROR(ct, "Corrupted descriptor addr=%#x head=%u tail=%u size=%u\n",
		 desc->addr, desc->head, desc->tail, desc->size);
	desc->is_in_error = 1;
	वापस -EPIPE;
पूर्ण

/**
 * रुको_क्रम_ctb_desc_update - Wait क्रम the CT buffer descriptor update.
 * @desc:	buffer descriptor
 * @fence:	response fence
 * @status:	placeholder क्रम status
 *
 * Guc will update CT buffer descriptor with new fence and status
 * after processing the command identअगरied by the fence. Wait क्रम
 * specअगरied fence and then पढ़ो from the descriptor status of the
 * command.
 *
 * Return:
 * *	0 response received (status is valid)
 * *	-ETIMEDOUT no response within hardcoded समयout
 * *	-EPROTO no response, CT buffer is in error
 */
अटल पूर्णांक रुको_क्रम_ctb_desc_update(काष्ठा guc_ct_buffer_desc *desc,
				    u32 fence,
				    u32 *status)
अणु
	पूर्णांक err;

	/*
	 * Fast commands should complete in less than 10us, so sample quickly
	 * up to that length of समय, then चयन to a slower sleep-रुको loop.
	 * No GuC command should ever take दीर्घer than 10ms.
	 */
#घोषणा करोne (READ_ONCE(desc->fence) == fence)
	err = रुको_क्रम_us(करोne, 10);
	अगर (err)
		err = रुको_क्रम(करोne, 10);
#अघोषित करोne

	अगर (unlikely(err)) अणु
		DRM_ERROR("CT: fence %u failed; reported fence=%u\n",
			  fence, desc->fence);

		अगर (WARN_ON(desc->is_in_error)) अणु
			/* Something went wrong with the messaging, try to reset
			 * the buffer and hope क्रम the best
			 */
			guc_ct_buffer_desc_reset(desc);
			err = -EPROTO;
		पूर्ण
	पूर्ण

	*status = desc->status;
	वापस err;
पूर्ण

/**
 * रुको_क्रम_ct_request_update - Wait क्रम CT request state update.
 * @req:	poपूर्णांकer to pending request
 * @status:	placeholder क्रम status
 *
 * For each sent request, Guc shall send bac CT response message.
 * Our message handler will update status of tracked request once
 * response message with given fence is received. Wait here and
 * check क्रम valid response status value.
 *
 * Return:
 * *	0 response received (status is valid)
 * *	-ETIMEDOUT no response within hardcoded समयout
 */
अटल पूर्णांक रुको_क्रम_ct_request_update(काष्ठा ct_request *req, u32 *status)
अणु
	पूर्णांक err;

	/*
	 * Fast commands should complete in less than 10us, so sample quickly
	 * up to that length of समय, then चयन to a slower sleep-रुको loop.
	 * No GuC command should ever take दीर्घer than 10ms.
	 */
#घोषणा करोne INTEL_GUC_MSG_IS_RESPONSE(READ_ONCE(req->status))
	err = रुको_क्रम_us(करोne, 10);
	अगर (err)
		err = रुको_क्रम(करोne, 10);
#अघोषित करोne

	अगर (unlikely(err))
		DRM_ERROR("CT: fence %u err %d\n", req->fence, err);

	*status = req->status;
	वापस err;
पूर्ण

अटल पूर्णांक ct_send(काष्ठा पूर्णांकel_guc_ct *ct,
		   स्थिर u32 *action,
		   u32 len,
		   u32 *response_buf,
		   u32 response_buf_size,
		   u32 *status)
अणु
	काष्ठा पूर्णांकel_guc_ct_buffer *ctb = &ct->ctbs[CTB_SEND];
	काष्ठा guc_ct_buffer_desc *desc = ctb->desc;
	काष्ठा ct_request request;
	अचिन्हित दीर्घ flags;
	u32 fence;
	पूर्णांक err;

	GEM_BUG_ON(!ct->enabled);
	GEM_BUG_ON(!len);
	GEM_BUG_ON(len & ~GUC_CT_MSG_LEN_MASK);
	GEM_BUG_ON(!response_buf && response_buf_size);

	fence = ct_get_next_fence(ct);
	request.fence = fence;
	request.status = 0;
	request.response_len = response_buf_size;
	request.response_buf = response_buf;

	spin_lock_irqsave(&ct->requests.lock, flags);
	list_add_tail(&request.link, &ct->requests.pending);
	spin_unlock_irqrestore(&ct->requests.lock, flags);

	err = ct_ग_लिखो(ct, action, len, fence, !!response_buf);
	अगर (unlikely(err))
		जाओ unlink;

	पूर्णांकel_guc_notअगरy(ct_to_guc(ct));

	अगर (response_buf)
		err = रुको_क्रम_ct_request_update(&request, status);
	अन्यथा
		err = रुको_क्रम_ctb_desc_update(desc, fence, status);
	अगर (unlikely(err))
		जाओ unlink;

	अगर (!INTEL_GUC_MSG_IS_RESPONSE_SUCCESS(*status)) अणु
		err = -EIO;
		जाओ unlink;
	पूर्ण

	अगर (response_buf) अणु
		/* There shall be no data in the status */
		WARN_ON(INTEL_GUC_MSG_TO_DATA(request.status));
		/* Return actual response len */
		err = request.response_len;
	पूर्ण अन्यथा अणु
		/* There shall be no response payload */
		WARN_ON(request.response_len);
		/* Return data decoded from the status dword */
		err = INTEL_GUC_MSG_TO_DATA(*status);
	पूर्ण

unlink:
	spin_lock_irqsave(&ct->requests.lock, flags);
	list_del(&request.link);
	spin_unlock_irqrestore(&ct->requests.lock, flags);

	वापस err;
पूर्ण

/*
 * Command Transport (CT) buffer based GuC send function.
 */
पूर्णांक पूर्णांकel_guc_ct_send(काष्ठा पूर्णांकel_guc_ct *ct, स्थिर u32 *action, u32 len,
		      u32 *response_buf, u32 response_buf_size)
अणु
	काष्ठा पूर्णांकel_guc *guc = ct_to_guc(ct);
	u32 status = ~0; /* undefined */
	पूर्णांक ret;

	अगर (unlikely(!ct->enabled)) अणु
		WARN(1, "Unexpected send: action=%#x\n", *action);
		वापस -ENODEV;
	पूर्ण

	mutex_lock(&guc->send_mutex);

	ret = ct_send(ct, action, len, response_buf, response_buf_size, &status);
	अगर (unlikely(ret < 0)) अणु
		CT_ERROR(ct, "Sending action %#x failed (err=%d status=%#X)\n",
			 action[0], ret, status);
	पूर्ण अन्यथा अगर (unlikely(ret)) अणु
		CT_DEBUG(ct, "send action %#x returned %d (%#x)\n",
			 action[0], ret, ret);
	पूर्ण

	mutex_unlock(&guc->send_mutex);
	वापस ret;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ct_header_get_len(u32 header)
अणु
	वापस (header >> GUC_CT_MSG_LEN_SHIFT) & GUC_CT_MSG_LEN_MASK;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक ct_header_get_action(u32 header)
अणु
	वापस (header >> GUC_CT_MSG_ACTION_SHIFT) & GUC_CT_MSG_ACTION_MASK;
पूर्ण

अटल अंतरभूत bool ct_header_is_response(u32 header)
अणु
	वापस !!(header & GUC_CT_MSG_IS_RESPONSE);
पूर्ण

अटल पूर्णांक ct_पढ़ो(काष्ठा पूर्णांकel_guc_ct *ct, u32 *data)
अणु
	काष्ठा पूर्णांकel_guc_ct_buffer *ctb = &ct->ctbs[CTB_RECV];
	काष्ठा guc_ct_buffer_desc *desc = ctb->desc;
	u32 head = desc->head;
	u32 tail = desc->tail;
	u32 size = desc->size;
	u32 *cmds = ctb->cmds;
	s32 available;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक i;

	अगर (unlikely(desc->is_in_error))
		वापस -EPIPE;

	अगर (unlikely(!IS_ALIGNED(head | tail | size, 4) ||
		     (tail | head) >= size))
		जाओ corrupted;

	/* later calculations will be करोne in dwords */
	head /= 4;
	tail /= 4;
	size /= 4;

	/* tail == head condition indicates empty */
	available = tail - head;
	अगर (unlikely(available == 0))
		वापस -ENODATA;

	/* beware of buffer wrap हाल */
	अगर (unlikely(available < 0))
		available += size;
	CT_DEBUG(ct, "available %d (%u:%u)\n", available, head, tail);
	GEM_BUG_ON(available < 0);

	data[0] = cmds[head];
	head = (head + 1) % size;

	/* message len with header */
	len = ct_header_get_len(data[0]) + 1;
	अगर (unlikely(len > (u32)available)) अणु
		CT_ERROR(ct, "Incomplete message %*ph %*ph %*ph\n",
			 4, data,
			 4 * (head + available - 1 > size ?
			      size - head : available - 1), &cmds[head],
			 4 * (head + available - 1 > size ?
			      available - 1 - size + head : 0), &cmds[0]);
		जाओ corrupted;
	पूर्ण

	क्रम (i = 1; i < len; i++) अणु
		data[i] = cmds[head];
		head = (head + 1) % size;
	पूर्ण
	CT_DEBUG(ct, "received %*ph\n", 4 * len, data);

	desc->head = head * 4;
	वापस 0;

corrupted:
	CT_ERROR(ct, "Corrupted descriptor addr=%#x head=%u tail=%u size=%u\n",
		 desc->addr, desc->head, desc->tail, desc->size);
	desc->is_in_error = 1;
	वापस -EPIPE;
पूर्ण

/**
 * DOC: CTB GuC to Host response
 *
 * Format of the CTB GuC to Host response message is as follows::
 *
 *      +------------+---------+---------+---------+---------+---------+
 *      |   msg[0]   |   [1]   |   [2]   |   [3]   |   ...   |  [n-1]  |
 *      +------------+---------+---------+---------+---------+---------+
 *      |   MESSAGE  |       MESSAGE PAYLOAD                           |
 *      +   HEADER   +---------+---------+---------+---------+---------+
 *      |            |    0    |    1    |    2    |   ...   |    n    |
 *      +============+=========+=========+=========+=========+=========+
 *      |  len >= 2  |  FENCE  |  STATUS |   response specअगरic data    |
 *      +------+-----+---------+---------+---------+---------+---------+
 *
 *                   ^-----------------------len-----------------------^
 */

अटल पूर्णांक ct_handle_response(काष्ठा पूर्णांकel_guc_ct *ct, स्थिर u32 *msg)
अणु
	u32 header = msg[0];
	u32 len = ct_header_get_len(header);
	u32 msgsize = (len + 1) * माप(u32); /* msg size in bytes w/header */
	u32 fence;
	u32 status;
	u32 datalen;
	काष्ठा ct_request *req;
	bool found = false;

	GEM_BUG_ON(!ct_header_is_response(header));
	GEM_BUG_ON(!in_irq());

	/* Response payload shall at least include fence and status */
	अगर (unlikely(len < 2)) अणु
		CT_ERROR(ct, "Corrupted response %*ph\n", msgsize, msg);
		वापस -EPROTO;
	पूर्ण

	fence = msg[1];
	status = msg[2];
	datalen = len - 2;

	/* Format of the status follows RESPONSE message */
	अगर (unlikely(!INTEL_GUC_MSG_IS_RESPONSE(status))) अणु
		CT_ERROR(ct, "Corrupted response %*ph\n", msgsize, msg);
		वापस -EPROTO;
	पूर्ण

	CT_DEBUG(ct, "response fence %u status %#x\n", fence, status);

	spin_lock(&ct->requests.lock);
	list_क्रम_each_entry(req, &ct->requests.pending, link) अणु
		अगर (unlikely(fence != req->fence)) अणु
			CT_DEBUG(ct, "request %u awaits response\n",
				 req->fence);
			जारी;
		पूर्ण
		अगर (unlikely(datalen > req->response_len)) अणु
			CT_ERROR(ct, "Response for %u is too long %*ph\n",
				 req->fence, msgsize, msg);
			datalen = 0;
		पूर्ण
		अगर (datalen)
			स_नकल(req->response_buf, msg + 3, 4 * datalen);
		req->response_len = datalen;
		WRITE_ONCE(req->status, status);
		found = true;
		अवरोध;
	पूर्ण
	spin_unlock(&ct->requests.lock);

	अगर (!found)
		CT_ERROR(ct, "Unsolicited response %*ph\n", msgsize, msg);
	वापस 0;
पूर्ण

अटल व्योम ct_process_request(काष्ठा पूर्णांकel_guc_ct *ct,
			       u32 action, u32 len, स्थिर u32 *payload)
अणु
	काष्ठा पूर्णांकel_guc *guc = ct_to_guc(ct);
	पूर्णांक ret;

	CT_DEBUG(ct, "request %x %*ph\n", action, 4 * len, payload);

	चयन (action) अणु
	हाल INTEL_GUC_ACTION_DEFAULT:
		ret = पूर्णांकel_guc_to_host_process_recv_msg(guc, payload, len);
		अगर (unlikely(ret))
			जाओ fail_unexpected;
		अवरोध;

	शेष:
fail_unexpected:
		CT_ERROR(ct, "Unexpected request %x %*ph\n",
			 action, 4 * len, payload);
		अवरोध;
	पूर्ण
पूर्ण

अटल bool ct_process_incoming_requests(काष्ठा पूर्णांकel_guc_ct *ct)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा ct_incoming_request *request;
	u32 header;
	u32 *payload;
	bool करोne;

	spin_lock_irqsave(&ct->requests.lock, flags);
	request = list_first_entry_or_null(&ct->requests.incoming,
					   काष्ठा ct_incoming_request, link);
	अगर (request)
		list_del(&request->link);
	करोne = !!list_empty(&ct->requests.incoming);
	spin_unlock_irqrestore(&ct->requests.lock, flags);

	अगर (!request)
		वापस true;

	header = request->msg[0];
	payload = &request->msg[1];
	ct_process_request(ct,
			   ct_header_get_action(header),
			   ct_header_get_len(header),
			   payload);

	kमुक्त(request);
	वापस करोne;
पूर्ण

अटल व्योम ct_incoming_request_worker_func(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा पूर्णांकel_guc_ct *ct =
		container_of(w, काष्ठा पूर्णांकel_guc_ct, requests.worker);
	bool करोne;

	करोne = ct_process_incoming_requests(ct);
	अगर (!करोne)
		queue_work(प्रणाली_unbound_wq, &ct->requests.worker);
पूर्ण

/**
 * DOC: CTB GuC to Host request
 *
 * Format of the CTB GuC to Host request message is as follows::
 *
 *      +------------+---------+---------+---------+---------+---------+
 *      |   msg[0]   |   [1]   |   [2]   |   [3]   |   ...   |  [n-1]  |
 *      +------------+---------+---------+---------+---------+---------+
 *      |   MESSAGE  |       MESSAGE PAYLOAD                           |
 *      +   HEADER   +---------+---------+---------+---------+---------+
 *      |            |    0    |    1    |    2    |   ...   |    n    |
 *      +============+=========+=========+=========+=========+=========+
 *      |     len    |            request specअगरic data                |
 *      +------+-----+---------+---------+---------+---------+---------+
 *
 *                   ^-----------------------len-----------------------^
 */

अटल पूर्णांक ct_handle_request(काष्ठा पूर्णांकel_guc_ct *ct, स्थिर u32 *msg)
अणु
	u32 header = msg[0];
	u32 len = ct_header_get_len(header);
	u32 msgsize = (len + 1) * माप(u32); /* msg size in bytes w/header */
	काष्ठा ct_incoming_request *request;
	अचिन्हित दीर्घ flags;

	GEM_BUG_ON(ct_header_is_response(header));

	request = kदो_स्मृति(माप(*request) + msgsize, GFP_ATOMIC);
	अगर (unlikely(!request)) अणु
		CT_ERROR(ct, "Dropping request %*ph\n", msgsize, msg);
		वापस 0; /* XXX: -ENOMEM ? */
	पूर्ण
	स_नकल(request->msg, msg, msgsize);

	spin_lock_irqsave(&ct->requests.lock, flags);
	list_add_tail(&request->link, &ct->requests.incoming);
	spin_unlock_irqrestore(&ct->requests.lock, flags);

	queue_work(प्रणाली_unbound_wq, &ct->requests.worker);
	वापस 0;
पूर्ण

/*
 * When we're communicating with the GuC over CT, GuC uses events
 * to notअगरy us about new messages being posted on the RECV buffer.
 */
व्योम पूर्णांकel_guc_ct_event_handler(काष्ठा पूर्णांकel_guc_ct *ct)
अणु
	u32 msg[GUC_CT_MSG_LEN_MASK + 1]; /* one extra dw क्रम the header */
	पूर्णांक err = 0;

	अगर (unlikely(!ct->enabled)) अणु
		WARN(1, "Unexpected GuC event received while CT disabled!\n");
		वापस;
	पूर्ण

	करो अणु
		err = ct_पढ़ो(ct, msg);
		अगर (err)
			अवरोध;

		अगर (ct_header_is_response(msg[0]))
			err = ct_handle_response(ct, msg);
		अन्यथा
			err = ct_handle_request(ct, msg);
	पूर्ण जबतक (!err);
पूर्ण
