<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2015 VMware, Inc., Palo Alto, CA., USA
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sub license, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial portions
 * of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL
 * THE COPYRIGHT HOLDERS, AUTHORS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
 * USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 **************************************************************************/

#समावेश <linux/dmapool.h>
#समावेश <linux/pci.h>

#समावेश <drm/tपंचांग/tपंचांग_bo_api.h>

#समावेश "vmwgfx_drv.h"

/*
 * Size of अंतरभूत command buffers. Try to make sure that a page size is a
 * multiple of the DMA pool allocation size.
 */
#घोषणा VMW_CMDBUF_INLINE_ALIGN 64
#घोषणा VMW_CMDBUF_INLINE_SIZE \
	(1024 - ALIGN(माप(SVGACBHeader), VMW_CMDBUF_INLINE_ALIGN))

/**
 * काष्ठा vmw_cmdbuf_context - Command buffer context queues
 *
 * @submitted: List of command buffers that have been submitted to the
 * manager but not yet submitted to hardware.
 * @hw_submitted: List of command buffers submitted to hardware.
 * @preempted: List of preempted command buffers.
 * @num_hw_submitted: Number of buffers currently being processed by hardware
 * @block_submission: Identअगरies a block command submission.
 */
काष्ठा vmw_cmdbuf_context अणु
	काष्ठा list_head submitted;
	काष्ठा list_head hw_submitted;
	काष्ठा list_head preempted;
	अचिन्हित num_hw_submitted;
	bool block_submission;
पूर्ण;

/**
 * काष्ठा vmw_cmdbuf_man - Command buffer manager
 *
 * @cur_mutex: Mutex protecting the command buffer used क्रम incremental small
 * kernel command submissions, @cur.
 * @space_mutex: Mutex to protect against starvation when we allocate
 * मुख्य pool buffer space.
 * @error_mutex: Mutex to serialize the work queue error handling.
 * Note this is not needed अगर the same workqueue handler
 * can't race with itself...
 * @work: A काष्ठा work_काष्ठा implementeing command buffer error handling.
 * Immutable.
 * @dev_priv: Poपूर्णांकer to the device निजी काष्ठा. Immutable.
 * @ctx: Array of command buffer context queues. The queues and the context
 * data is रक्षित by @lock.
 * @error: List of command buffers that have caused device errors.
 * Protected by @lock.
 * @mm: Range manager क्रम the command buffer space. Manager allocations and
 * मुक्तs are रक्षित by @lock.
 * @cmd_space: Buffer object क्रम the command buffer space, unless we were
 * able to make a contigous coherent DMA memory allocation, @handle. Immutable.
 * @map_obj: Mapping state क्रम @cmd_space. Immutable.
 * @map: Poपूर्णांकer to command buffer space. May be a mapped buffer object or
 * a contigous coherent DMA memory allocation. Immutable.
 * @cur: Command buffer क्रम small kernel command submissions. Protected by
 * the @cur_mutex.
 * @cur_pos: Space alपढ़ोy used in @cur. Protected by @cur_mutex.
 * @शेष_size: Default size क्रम the @cur command buffer. Immutable.
 * @max_hw_submitted: Max number of in-flight command buffers the device can
 * handle. Immutable.
 * @lock: Spinlock protecting command submission queues.
 * @headers: Pool of DMA memory क्रम device command buffer headers.
 * Internal protection.
 * @dheaders: Pool of DMA memory क्रम device command buffer headers with trailing
 * space क्रम अंतरभूत data. Internal protection.
 * @alloc_queue: Wait queue क्रम processes रुकोing to allocate command buffer
 * space.
 * @idle_queue: Wait queue क्रम processes रुकोing क्रम command buffer idle.
 * @irq_on: Whether the process function has requested irq to be turned on.
 * Protected by @lock.
 * @using_mob: Whether the command buffer space is a MOB or a contigous DMA
 * allocation. Immutable.
 * @has_pool: Has a large pool of DMA memory which allows larger allocations.
 * Typically this is false only during bootstrap.
 * @handle: DMA address handle क्रम the command buffer space अगर @using_mob is
 * false. Immutable.
 * @size: The size of the command buffer space. Immutable.
 * @num_contexts: Number of contexts actually enabled.
 */
काष्ठा vmw_cmdbuf_man अणु
	काष्ठा mutex cur_mutex;
	काष्ठा mutex space_mutex;
	काष्ठा mutex error_mutex;
	काष्ठा work_काष्ठा work;
	काष्ठा vmw_निजी *dev_priv;
	काष्ठा vmw_cmdbuf_context ctx[SVGA_CB_CONTEXT_MAX];
	काष्ठा list_head error;
	काष्ठा drm_mm mm;
	काष्ठा tपंचांग_buffer_object *cmd_space;
	काष्ठा tपंचांग_bo_kmap_obj map_obj;
	u8 *map;
	काष्ठा vmw_cmdbuf_header *cur;
	माप_प्रकार cur_pos;
	माप_प्रकार शेष_size;
	अचिन्हित max_hw_submitted;
	spinlock_t lock;
	काष्ठा dma_pool *headers;
	काष्ठा dma_pool *dheaders;
	रुको_queue_head_t alloc_queue;
	रुको_queue_head_t idle_queue;
	bool irq_on;
	bool using_mob;
	bool has_pool;
	dma_addr_t handle;
	माप_प्रकार size;
	u32 num_contexts;
पूर्ण;

/**
 * काष्ठा vmw_cmdbuf_header - Command buffer metadata
 *
 * @man: The command buffer manager.
 * @cb_header: Device command buffer header, allocated from a DMA pool.
 * @cb_context: The device command buffer context.
 * @list: List head क्रम attaching to the manager lists.
 * @node: The range manager node.
 * @handle: The DMA address of @cb_header. Handed to the device on command
 * buffer submission.
 * @cmd: Poपूर्णांकer to the command buffer space of this buffer.
 * @size: Size of the command buffer space of this buffer.
 * @reserved: Reserved space of this buffer.
 * @अंतरभूत_space: Whether अंतरभूत command buffer space is used.
 */
काष्ठा vmw_cmdbuf_header अणु
	काष्ठा vmw_cmdbuf_man *man;
	SVGACBHeader *cb_header;
	SVGACBContext cb_context;
	काष्ठा list_head list;
	काष्ठा drm_mm_node node;
	dma_addr_t handle;
	u8 *cmd;
	माप_प्रकार size;
	माप_प्रकार reserved;
	bool अंतरभूत_space;
पूर्ण;

/**
 * काष्ठा vmw_cmdbuf_dheader - Device command buffer header with अंतरभूत
 * command buffer space.
 *
 * @cb_header: Device command buffer header.
 * @cmd: Inline command buffer space.
 */
काष्ठा vmw_cmdbuf_dheader अणु
	SVGACBHeader cb_header;
	u8 cmd[VMW_CMDBUF_INLINE_SIZE] __aligned(VMW_CMDBUF_INLINE_ALIGN);
पूर्ण;

/**
 * काष्ठा vmw_cmdbuf_alloc_info - Command buffer space allocation metadata
 *
 * @page_size: Size of requested command buffer space in pages.
 * @node: Poपूर्णांकer to the range manager node.
 * @करोne: True अगर this allocation has succeeded.
 */
काष्ठा vmw_cmdbuf_alloc_info अणु
	माप_प्रकार page_size;
	काष्ठा drm_mm_node *node;
	bool करोne;
पूर्ण;

/* Loop over each context in the command buffer manager. */
#घोषणा क्रम_each_cmdbuf_ctx(_man, _i, _ctx)				\
	क्रम (_i = 0, _ctx = &(_man)->ctx[0]; (_i) < (_man)->num_contexts; \
	     ++(_i), ++(_ctx))

अटल पूर्णांक vmw_cmdbuf_startstop(काष्ठा vmw_cmdbuf_man *man, u32 context,
				bool enable);
अटल पूर्णांक vmw_cmdbuf_preempt(काष्ठा vmw_cmdbuf_man *man, u32 context);

/**
 * vmw_cmdbuf_cur_lock - Helper to lock the cur_mutex.
 *
 * @man: The range manager.
 * @पूर्णांकerruptible: Whether to रुको पूर्णांकerruptible when locking.
 */
अटल पूर्णांक vmw_cmdbuf_cur_lock(काष्ठा vmw_cmdbuf_man *man, bool पूर्णांकerruptible)
अणु
	अगर (पूर्णांकerruptible) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&man->cur_mutex))
			वापस -ERESTARTSYS;
	पूर्ण अन्यथा अणु
		mutex_lock(&man->cur_mutex);
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_cmdbuf_cur_unlock - Helper to unlock the cur_mutex.
 *
 * @man: The range manager.
 */
अटल व्योम vmw_cmdbuf_cur_unlock(काष्ठा vmw_cmdbuf_man *man)
अणु
	mutex_unlock(&man->cur_mutex);
पूर्ण

/**
 * vmw_cmdbuf_header_अंतरभूत_मुक्त - Free a काष्ठा vmw_cmdbuf_header that has
 * been used क्रम the device context with अंतरभूत command buffers.
 * Need not be called locked.
 *
 * @header: Poपूर्णांकer to the header to मुक्त.
 */
अटल व्योम vmw_cmdbuf_header_अंतरभूत_मुक्त(काष्ठा vmw_cmdbuf_header *header)
अणु
	काष्ठा vmw_cmdbuf_dheader *dheader;

	अगर (WARN_ON_ONCE(!header->अंतरभूत_space))
		वापस;

	dheader = container_of(header->cb_header, काष्ठा vmw_cmdbuf_dheader,
			       cb_header);
	dma_pool_मुक्त(header->man->dheaders, dheader, header->handle);
	kमुक्त(header);
पूर्ण

/**
 * __vmw_cmdbuf_header_मुक्त - Free a काष्ठा vmw_cmdbuf_header  and its
 * associated काष्ठाures.
 *
 * @header: Poपूर्णांकer to the header to मुक्त.
 *
 * For पूर्णांकernal use. Must be called with man::lock held.
 */
अटल व्योम __vmw_cmdbuf_header_मुक्त(काष्ठा vmw_cmdbuf_header *header)
अणु
	काष्ठा vmw_cmdbuf_man *man = header->man;

	lockdep_निश्चित_held_once(&man->lock);

	अगर (header->अंतरभूत_space) अणु
		vmw_cmdbuf_header_अंतरभूत_मुक्त(header);
		वापस;
	पूर्ण

	drm_mm_हटाओ_node(&header->node);
	wake_up_all(&man->alloc_queue);
	अगर (header->cb_header)
		dma_pool_मुक्त(man->headers, header->cb_header,
			      header->handle);
	kमुक्त(header);
पूर्ण

/**
 * vmw_cmdbuf_header_मुक्त - Free a काष्ठा vmw_cmdbuf_header  and its
 * associated काष्ठाures.
 *
 * @header: Poपूर्णांकer to the header to मुक्त.
 */
व्योम vmw_cmdbuf_header_मुक्त(काष्ठा vmw_cmdbuf_header *header)
अणु
	काष्ठा vmw_cmdbuf_man *man = header->man;

	/* Aव्योम locking अगर अंतरभूत_space */
	अगर (header->अंतरभूत_space) अणु
		vmw_cmdbuf_header_अंतरभूत_मुक्त(header);
		वापस;
	पूर्ण
	spin_lock(&man->lock);
	__vmw_cmdbuf_header_मुक्त(header);
	spin_unlock(&man->lock);
पूर्ण


/**
 * vmw_cmbuf_header_submit: Submit a command buffer to hardware.
 *
 * @header: The header of the buffer to submit.
 */
अटल पूर्णांक vmw_cmdbuf_header_submit(काष्ठा vmw_cmdbuf_header *header)
अणु
	काष्ठा vmw_cmdbuf_man *man = header->man;
	u32 val;

	val = upper_32_bits(header->handle);
	vmw_ग_लिखो(man->dev_priv, SVGA_REG_COMMAND_HIGH, val);

	val = lower_32_bits(header->handle);
	val |= header->cb_context & SVGA_CB_CONTEXT_MASK;
	vmw_ग_लिखो(man->dev_priv, SVGA_REG_COMMAND_LOW, val);

	वापस header->cb_header->status;
पूर्ण

/**
 * vmw_cmdbuf_ctx_init: Initialize a command buffer context.
 *
 * @ctx: The command buffer context to initialize
 */
अटल व्योम vmw_cmdbuf_ctx_init(काष्ठा vmw_cmdbuf_context *ctx)
अणु
	INIT_LIST_HEAD(&ctx->hw_submitted);
	INIT_LIST_HEAD(&ctx->submitted);
	INIT_LIST_HEAD(&ctx->preempted);
	ctx->num_hw_submitted = 0;
पूर्ण

/**
 * vmw_cmdbuf_ctx_submit: Submit command buffers from a command buffer
 * context.
 *
 * @man: The command buffer manager.
 * @ctx: The command buffer context.
 *
 * Submits command buffers to hardware until there are no more command
 * buffers to submit or the hardware can't handle more command buffers.
 */
अटल व्योम vmw_cmdbuf_ctx_submit(काष्ठा vmw_cmdbuf_man *man,
				  काष्ठा vmw_cmdbuf_context *ctx)
अणु
	जबतक (ctx->num_hw_submitted < man->max_hw_submitted &&
	       !list_empty(&ctx->submitted) &&
	       !ctx->block_submission) अणु
		काष्ठा vmw_cmdbuf_header *entry;
		SVGACBStatus status;

		entry = list_first_entry(&ctx->submitted,
					 काष्ठा vmw_cmdbuf_header,
					 list);

		status = vmw_cmdbuf_header_submit(entry);

		/* This should never happen */
		अगर (WARN_ON_ONCE(status == SVGA_CB_STATUS_QUEUE_FULL)) अणु
			entry->cb_header->status = SVGA_CB_STATUS_NONE;
			अवरोध;
		पूर्ण

		list_del(&entry->list);
		list_add_tail(&entry->list, &ctx->hw_submitted);
		ctx->num_hw_submitted++;
	पूर्ण

पूर्ण

/**
 * vmw_cmdbuf_ctx_process - Process a command buffer context.
 *
 * @man: The command buffer manager.
 * @ctx: The command buffer context.
 * @notempty: Pass back count of non-empty command submitted lists.
 *
 * Submit command buffers to hardware अगर possible, and process finished
 * buffers. Typically मुक्तing them, but on preemption or error take
 * appropriate action. Wake up रुकोers अगर appropriate.
 */
अटल व्योम vmw_cmdbuf_ctx_process(काष्ठा vmw_cmdbuf_man *man,
				   काष्ठा vmw_cmdbuf_context *ctx,
				   पूर्णांक *notempty)
अणु
	काष्ठा vmw_cmdbuf_header *entry, *next;

	vmw_cmdbuf_ctx_submit(man, ctx);

	list_क्रम_each_entry_safe(entry, next, &ctx->hw_submitted, list) अणु
		SVGACBStatus status = entry->cb_header->status;

		अगर (status == SVGA_CB_STATUS_NONE)
			अवरोध;

		list_del(&entry->list);
		wake_up_all(&man->idle_queue);
		ctx->num_hw_submitted--;
		चयन (status) अणु
		हाल SVGA_CB_STATUS_COMPLETED:
			__vmw_cmdbuf_header_मुक्त(entry);
			अवरोध;
		हाल SVGA_CB_STATUS_COMMAND_ERROR:
			WARN_ONCE(true, "Command buffer error.\n");
			entry->cb_header->status = SVGA_CB_STATUS_NONE;
			list_add_tail(&entry->list, &man->error);
			schedule_work(&man->work);
			अवरोध;
		हाल SVGA_CB_STATUS_PREEMPTED:
			entry->cb_header->status = SVGA_CB_STATUS_NONE;
			list_add_tail(&entry->list, &ctx->preempted);
			अवरोध;
		हाल SVGA_CB_STATUS_CB_HEADER_ERROR:
			WARN_ONCE(true, "Command buffer header error.\n");
			__vmw_cmdbuf_header_मुक्त(entry);
			अवरोध;
		शेष:
			WARN_ONCE(true, "Undefined command buffer status.\n");
			__vmw_cmdbuf_header_मुक्त(entry);
			अवरोध;
		पूर्ण
	पूर्ण

	vmw_cmdbuf_ctx_submit(man, ctx);
	अगर (!list_empty(&ctx->submitted))
		(*notempty)++;
पूर्ण

/**
 * vmw_cmdbuf_man_process - Process all command buffer contexts and
 * चयन on and off irqs as appropriate.
 *
 * @man: The command buffer manager.
 *
 * Calls vmw_cmdbuf_ctx_process() on all contexts. If any context has
 * command buffers left that are not submitted to hardware, Make sure
 * IRQ handling is turned on. Otherwise, make sure it's turned off.
 */
अटल व्योम vmw_cmdbuf_man_process(काष्ठा vmw_cmdbuf_man *man)
अणु
	पूर्णांक notempty;
	काष्ठा vmw_cmdbuf_context *ctx;
	पूर्णांक i;

retry:
	notempty = 0;
	क्रम_each_cmdbuf_ctx(man, i, ctx)
		vmw_cmdbuf_ctx_process(man, ctx, &notempty);

	अगर (man->irq_on && !notempty) अणु
		vmw_generic_रुकोer_हटाओ(man->dev_priv,
					  SVGA_IRQFLAG_COMMAND_BUFFER,
					  &man->dev_priv->cmdbuf_रुकोers);
		man->irq_on = false;
	पूर्ण अन्यथा अगर (!man->irq_on && notempty) अणु
		vmw_generic_रुकोer_add(man->dev_priv,
				       SVGA_IRQFLAG_COMMAND_BUFFER,
				       &man->dev_priv->cmdbuf_रुकोers);
		man->irq_on = true;

		/* Rerun in हाल we just missed an irq. */
		जाओ retry;
	पूर्ण
पूर्ण

/**
 * vmw_cmdbuf_ctx_add - Schedule a command buffer क्रम submission on a
 * command buffer context
 *
 * @man: The command buffer manager.
 * @header: The header of the buffer to submit.
 * @cb_context: The command buffer context to use.
 *
 * This function adds @header to the "submitted" queue of the command
 * buffer context identअगरied by @cb_context. It then calls the command buffer
 * manager processing to potentially submit the buffer to hardware.
 * @man->lock needs to be held when calling this function.
 */
अटल व्योम vmw_cmdbuf_ctx_add(काष्ठा vmw_cmdbuf_man *man,
			       काष्ठा vmw_cmdbuf_header *header,
			       SVGACBContext cb_context)
अणु
	अगर (!(header->cb_header->flags & SVGA_CB_FLAG_DX_CONTEXT))
		header->cb_header->dxContext = 0;
	header->cb_context = cb_context;
	list_add_tail(&header->list, &man->ctx[cb_context].submitted);

	vmw_cmdbuf_man_process(man);
पूर्ण

/**
 * vmw_cmdbuf_irqthपढ़ो - The मुख्य part of the command buffer पूर्णांकerrupt
 * handler implemented as a thपढ़ोed irq task.
 *
 * @man: Poपूर्णांकer to the command buffer manager.
 *
 * The bottom half of the पूर्णांकerrupt handler simply calls पूर्णांकo the
 * command buffer processor to मुक्त finished buffers and submit any
 * queued buffers to hardware.
 */
व्योम vmw_cmdbuf_irqthपढ़ो(काष्ठा vmw_cmdbuf_man *man)
अणु
	spin_lock(&man->lock);
	vmw_cmdbuf_man_process(man);
	spin_unlock(&man->lock);
पूर्ण

/**
 * vmw_cmdbuf_work_func - The deferred work function that handles
 * command buffer errors.
 *
 * @work: The work func closure argument.
 *
 * Restarting the command buffer context after an error requires process
 * context, so it is deferred to this work function.
 */
अटल व्योम vmw_cmdbuf_work_func(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा vmw_cmdbuf_man *man =
		container_of(work, काष्ठा vmw_cmdbuf_man, work);
	काष्ठा vmw_cmdbuf_header *entry, *next;
	uपूर्णांक32_t dummy;
	bool send_fence = false;
	काष्ठा list_head restart_head[SVGA_CB_CONTEXT_MAX];
	पूर्णांक i;
	काष्ठा vmw_cmdbuf_context *ctx;
	bool global_block = false;

	क्रम_each_cmdbuf_ctx(man, i, ctx)
		INIT_LIST_HEAD(&restart_head[i]);

	mutex_lock(&man->error_mutex);
	spin_lock(&man->lock);
	list_क्रम_each_entry_safe(entry, next, &man->error, list) अणु
		SVGACBHeader *cb_hdr = entry->cb_header;
		SVGA3dCmdHeader *header = (SVGA3dCmdHeader *)
			(entry->cmd + cb_hdr->errorOffset);
		u32 error_cmd_size, new_start_offset;
		स्थिर अक्षर *cmd_name;

		list_del_init(&entry->list);
		global_block = true;

		अगर (!vmw_cmd_describe(header, &error_cmd_size, &cmd_name)) अणु
			VMW_DEBUG_USER("Unknown command causing device error.\n");
			VMW_DEBUG_USER("Command buffer offset is %lu\n",
				       (अचिन्हित दीर्घ) cb_hdr->errorOffset);
			__vmw_cmdbuf_header_मुक्त(entry);
			send_fence = true;
			जारी;
		पूर्ण

		VMW_DEBUG_USER("Command \"%s\" causing device error.\n",
			       cmd_name);
		VMW_DEBUG_USER("Command buffer offset is %lu\n",
			       (अचिन्हित दीर्घ) cb_hdr->errorOffset);
		VMW_DEBUG_USER("Command size is %lu\n",
			       (अचिन्हित दीर्घ) error_cmd_size);

		new_start_offset = cb_hdr->errorOffset + error_cmd_size;

		अगर (new_start_offset >= cb_hdr->length) अणु
			__vmw_cmdbuf_header_मुक्त(entry);
			send_fence = true;
			जारी;
		पूर्ण

		अगर (man->using_mob)
			cb_hdr->ptr.mob.mobOffset += new_start_offset;
		अन्यथा
			cb_hdr->ptr.pa += (u64) new_start_offset;

		entry->cmd += new_start_offset;
		cb_hdr->length -= new_start_offset;
		cb_hdr->errorOffset = 0;
		cb_hdr->offset = 0;

		list_add_tail(&entry->list, &restart_head[entry->cb_context]);
	पूर्ण

	क्रम_each_cmdbuf_ctx(man, i, ctx)
		man->ctx[i].block_submission = true;

	spin_unlock(&man->lock);

	/* Preempt all contexts */
	अगर (global_block && vmw_cmdbuf_preempt(man, 0))
		DRM_ERROR("Failed preempting command buffer contexts\n");

	spin_lock(&man->lock);
	क्रम_each_cmdbuf_ctx(man, i, ctx) अणु
		/* Move preempted command buffers to the preempted queue. */
		vmw_cmdbuf_ctx_process(man, ctx, &dummy);

		/*
		 * Add the preempted queue after the command buffer
		 * that caused an error.
		 */
		list_splice_init(&ctx->preempted, restart_head[i].prev);

		/*
		 * Finally add all command buffers first in the submitted
		 * queue, to rerun them.
		 */

		ctx->block_submission = false;
		list_splice_init(&restart_head[i], &ctx->submitted);
	पूर्ण

	vmw_cmdbuf_man_process(man);
	spin_unlock(&man->lock);

	अगर (global_block && vmw_cmdbuf_startstop(man, 0, true))
		DRM_ERROR("Failed restarting command buffer contexts\n");

	/* Send a new fence in हाल one was हटाओd */
	अगर (send_fence) अणु
		vmw_cmd_send_fence(man->dev_priv, &dummy);
		wake_up_all(&man->idle_queue);
	पूर्ण

	mutex_unlock(&man->error_mutex);
पूर्ण

/**
 * vmw_cmdbuf_man idle - Check whether the command buffer manager is idle.
 *
 * @man: The command buffer manager.
 * @check_preempted: Check also the preempted queue क्रम pending command buffers.
 *
 */
अटल bool vmw_cmdbuf_man_idle(काष्ठा vmw_cmdbuf_man *man,
				bool check_preempted)
अणु
	काष्ठा vmw_cmdbuf_context *ctx;
	bool idle = false;
	पूर्णांक i;

	spin_lock(&man->lock);
	vmw_cmdbuf_man_process(man);
	क्रम_each_cmdbuf_ctx(man, i, ctx) अणु
		अगर (!list_empty(&ctx->submitted) ||
		    !list_empty(&ctx->hw_submitted) ||
		    (check_preempted && !list_empty(&ctx->preempted)))
			जाओ out_unlock;
	पूर्ण

	idle = list_empty(&man->error);

out_unlock:
	spin_unlock(&man->lock);

	वापस idle;
पूर्ण

/**
 * __vmw_cmdbuf_cur_flush - Flush the current command buffer क्रम small kernel
 * command submissions
 *
 * @man: The command buffer manager.
 *
 * Flushes the current command buffer without allocating a new one. A new one
 * is स्वतःmatically allocated when needed. Call with @man->cur_mutex held.
 */
अटल व्योम __vmw_cmdbuf_cur_flush(काष्ठा vmw_cmdbuf_man *man)
अणु
	काष्ठा vmw_cmdbuf_header *cur = man->cur;

	lockdep_निश्चित_held_once(&man->cur_mutex);

	अगर (!cur)
		वापस;

	spin_lock(&man->lock);
	अगर (man->cur_pos == 0) अणु
		__vmw_cmdbuf_header_मुक्त(cur);
		जाओ out_unlock;
	पूर्ण

	man->cur->cb_header->length = man->cur_pos;
	vmw_cmdbuf_ctx_add(man, man->cur, SVGA_CB_CONTEXT_0);
out_unlock:
	spin_unlock(&man->lock);
	man->cur = शून्य;
	man->cur_pos = 0;
पूर्ण

/**
 * vmw_cmdbuf_cur_flush - Flush the current command buffer क्रम small kernel
 * command submissions
 *
 * @man: The command buffer manager.
 * @पूर्णांकerruptible: Whether to sleep पूर्णांकerruptible when sleeping.
 *
 * Flushes the current command buffer without allocating a new one. A new one
 * is स्वतःmatically allocated when needed.
 */
पूर्णांक vmw_cmdbuf_cur_flush(काष्ठा vmw_cmdbuf_man *man,
			 bool पूर्णांकerruptible)
अणु
	पूर्णांक ret = vmw_cmdbuf_cur_lock(man, पूर्णांकerruptible);

	अगर (ret)
		वापस ret;

	__vmw_cmdbuf_cur_flush(man);
	vmw_cmdbuf_cur_unlock(man);

	वापस 0;
पूर्ण

/**
 * vmw_cmdbuf_idle - Wait क्रम command buffer manager idle.
 *
 * @man: The command buffer manager.
 * @पूर्णांकerruptible: Sleep पूर्णांकerruptible जबतक रुकोing.
 * @समयout: Time out after this many ticks.
 *
 * Wait until the command buffer manager has processed all command buffers,
 * or until a समयout occurs. If a समयout occurs, the function will वापस
 * -EBUSY.
 */
पूर्णांक vmw_cmdbuf_idle(काष्ठा vmw_cmdbuf_man *man, bool पूर्णांकerruptible,
		    अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक ret;

	ret = vmw_cmdbuf_cur_flush(man, पूर्णांकerruptible);
	vmw_generic_रुकोer_add(man->dev_priv,
			       SVGA_IRQFLAG_COMMAND_BUFFER,
			       &man->dev_priv->cmdbuf_रुकोers);

	अगर (पूर्णांकerruptible) अणु
		ret = रुको_event_पूर्णांकerruptible_समयout
			(man->idle_queue, vmw_cmdbuf_man_idle(man, true),
			 समयout);
	पूर्ण अन्यथा अणु
		ret = रुको_event_समयout
			(man->idle_queue, vmw_cmdbuf_man_idle(man, true),
			 समयout);
	पूर्ण
	vmw_generic_रुकोer_हटाओ(man->dev_priv,
				  SVGA_IRQFLAG_COMMAND_BUFFER,
				  &man->dev_priv->cmdbuf_रुकोers);
	अगर (ret == 0) अणु
		अगर (!vmw_cmdbuf_man_idle(man, true))
			ret = -EBUSY;
		अन्यथा
			ret = 0;
	पूर्ण
	अगर (ret > 0)
		ret = 0;

	वापस ret;
पूर्ण

/**
 * vmw_cmdbuf_try_alloc - Try to allocate buffer space from the मुख्य pool.
 *
 * @man: The command buffer manager.
 * @info: Allocation info. Will hold the size on entry and allocated mm node
 * on successful वापस.
 *
 * Try to allocate buffer space from the मुख्य pool. Returns true अगर succeeded.
 * If a fatal error was hit, the error code is वापसed in @info->ret.
 */
अटल bool vmw_cmdbuf_try_alloc(काष्ठा vmw_cmdbuf_man *man,
				 काष्ठा vmw_cmdbuf_alloc_info *info)
अणु
	पूर्णांक ret;

	अगर (info->करोne)
		वापस true;

	स_रखो(info->node, 0, माप(*info->node));
	spin_lock(&man->lock);
	ret = drm_mm_insert_node(&man->mm, info->node, info->page_size);
	अगर (ret) अणु
		vmw_cmdbuf_man_process(man);
		ret = drm_mm_insert_node(&man->mm, info->node, info->page_size);
	पूर्ण

	spin_unlock(&man->lock);
	info->करोne = !ret;

	वापस info->करोne;
पूर्ण

/**
 * vmw_cmdbuf_alloc_space - Allocate buffer space from the मुख्य pool.
 *
 * @man: The command buffer manager.
 * @node: Poपूर्णांकer to pre-allocated range-manager node.
 * @size: The size of the allocation.
 * @पूर्णांकerruptible: Whether to sleep पूर्णांकerruptible जबतक रुकोing क्रम space.
 *
 * This function allocates buffer space from the मुख्य pool, and अगर there is
 * no space available ATM, it turns on IRQ handling and sleeps रुकोing क्रम it to
 * become available.
 */
अटल पूर्णांक vmw_cmdbuf_alloc_space(काष्ठा vmw_cmdbuf_man *man,
				  काष्ठा drm_mm_node *node,
				  माप_प्रकार size,
				  bool पूर्णांकerruptible)
अणु
	काष्ठा vmw_cmdbuf_alloc_info info;

	info.page_size = PAGE_ALIGN(size) >> PAGE_SHIFT;
	info.node = node;
	info.करोne = false;

	/*
	 * To prevent starvation of large requests, only one allocating call
	 * at a समय रुकोing क्रम space.
	 */
	अगर (पूर्णांकerruptible) अणु
		अगर (mutex_lock_पूर्णांकerruptible(&man->space_mutex))
			वापस -ERESTARTSYS;
	पूर्ण अन्यथा अणु
		mutex_lock(&man->space_mutex);
	पूर्ण

	/* Try to allocate space without रुकोing. */
	अगर (vmw_cmdbuf_try_alloc(man, &info))
		जाओ out_unlock;

	vmw_generic_रुकोer_add(man->dev_priv,
			       SVGA_IRQFLAG_COMMAND_BUFFER,
			       &man->dev_priv->cmdbuf_रुकोers);

	अगर (पूर्णांकerruptible) अणु
		पूर्णांक ret;

		ret = रुको_event_पूर्णांकerruptible
			(man->alloc_queue, vmw_cmdbuf_try_alloc(man, &info));
		अगर (ret) अणु
			vmw_generic_रुकोer_हटाओ
				(man->dev_priv, SVGA_IRQFLAG_COMMAND_BUFFER,
				 &man->dev_priv->cmdbuf_रुकोers);
			mutex_unlock(&man->space_mutex);
			वापस ret;
		पूर्ण
	पूर्ण अन्यथा अणु
		रुको_event(man->alloc_queue, vmw_cmdbuf_try_alloc(man, &info));
	पूर्ण
	vmw_generic_रुकोer_हटाओ(man->dev_priv,
				  SVGA_IRQFLAG_COMMAND_BUFFER,
				  &man->dev_priv->cmdbuf_रुकोers);

out_unlock:
	mutex_unlock(&man->space_mutex);

	वापस 0;
पूर्ण

/**
 * vmw_cmdbuf_space_pool - Set up a command buffer header with command buffer
 * space from the मुख्य pool.
 *
 * @man: The command buffer manager.
 * @header: Poपूर्णांकer to the header to set up.
 * @size: The requested size of the buffer space.
 * @पूर्णांकerruptible: Whether to sleep पूर्णांकerruptible जबतक रुकोing क्रम space.
 */
अटल पूर्णांक vmw_cmdbuf_space_pool(काष्ठा vmw_cmdbuf_man *man,
				 काष्ठा vmw_cmdbuf_header *header,
				 माप_प्रकार size,
				 bool पूर्णांकerruptible)
अणु
	SVGACBHeader *cb_hdr;
	माप_प्रकार offset;
	पूर्णांक ret;

	अगर (!man->has_pool)
		वापस -ENOMEM;

	ret = vmw_cmdbuf_alloc_space(man, &header->node,  size, पूर्णांकerruptible);

	अगर (ret)
		वापस ret;

	header->cb_header = dma_pool_zalloc(man->headers, GFP_KERNEL,
					    &header->handle);
	अगर (!header->cb_header) अणु
		ret = -ENOMEM;
		जाओ out_no_cb_header;
	पूर्ण

	header->size = header->node.size << PAGE_SHIFT;
	cb_hdr = header->cb_header;
	offset = header->node.start << PAGE_SHIFT;
	header->cmd = man->map + offset;
	अगर (man->using_mob) अणु
		cb_hdr->flags = SVGA_CB_FLAG_MOB;
		cb_hdr->ptr.mob.mobid = man->cmd_space->mem.start;
		cb_hdr->ptr.mob.mobOffset = offset;
	पूर्ण अन्यथा अणु
		cb_hdr->ptr.pa = (u64)man->handle + (u64)offset;
	पूर्ण

	वापस 0;

out_no_cb_header:
	spin_lock(&man->lock);
	drm_mm_हटाओ_node(&header->node);
	spin_unlock(&man->lock);

	वापस ret;
पूर्ण

/**
 * vmw_cmdbuf_space_अंतरभूत - Set up a command buffer header with
 * अंतरभूत command buffer space.
 *
 * @man: The command buffer manager.
 * @header: Poपूर्णांकer to the header to set up.
 * @size: The requested size of the buffer space.
 */
अटल पूर्णांक vmw_cmdbuf_space_अंतरभूत(काष्ठा vmw_cmdbuf_man *man,
				   काष्ठा vmw_cmdbuf_header *header,
				   पूर्णांक size)
अणु
	काष्ठा vmw_cmdbuf_dheader *dheader;
	SVGACBHeader *cb_hdr;

	अगर (WARN_ON_ONCE(size > VMW_CMDBUF_INLINE_SIZE))
		वापस -ENOMEM;

	dheader = dma_pool_zalloc(man->dheaders, GFP_KERNEL,
				  &header->handle);
	अगर (!dheader)
		वापस -ENOMEM;

	header->अंतरभूत_space = true;
	header->size = VMW_CMDBUF_INLINE_SIZE;
	cb_hdr = &dheader->cb_header;
	header->cb_header = cb_hdr;
	header->cmd = dheader->cmd;
	cb_hdr->status = SVGA_CB_STATUS_NONE;
	cb_hdr->flags = SVGA_CB_FLAG_NONE;
	cb_hdr->ptr.pa = (u64)header->handle +
		(u64)दुरत्व(काष्ठा vmw_cmdbuf_dheader, cmd);

	वापस 0;
पूर्ण

/**
 * vmw_cmdbuf_alloc - Allocate a command buffer header complete with
 * command buffer space.
 *
 * @man: The command buffer manager.
 * @size: The requested size of the buffer space.
 * @पूर्णांकerruptible: Whether to sleep पूर्णांकerruptible जबतक रुकोing क्रम space.
 * @p_header: poपूर्णांकs to a header poपूर्णांकer to populate on successful वापस.
 *
 * Returns a poपूर्णांकer to command buffer space अगर successful. Otherwise
 * वापसs an error poपूर्णांकer. The header poपूर्णांकer वापसed in @p_header should
 * be used क्रम upcoming calls to vmw_cmdbuf_reserve() and vmw_cmdbuf_commit().
 */
व्योम *vmw_cmdbuf_alloc(काष्ठा vmw_cmdbuf_man *man,
		       माप_प्रकार size, bool पूर्णांकerruptible,
		       काष्ठा vmw_cmdbuf_header **p_header)
अणु
	काष्ठा vmw_cmdbuf_header *header;
	पूर्णांक ret = 0;

	*p_header = शून्य;

	header = kzalloc(माप(*header), GFP_KERNEL);
	अगर (!header)
		वापस ERR_PTR(-ENOMEM);

	अगर (size <= VMW_CMDBUF_INLINE_SIZE)
		ret = vmw_cmdbuf_space_अंतरभूत(man, header, size);
	अन्यथा
		ret = vmw_cmdbuf_space_pool(man, header, size, पूर्णांकerruptible);

	अगर (ret) अणु
		kमुक्त(header);
		वापस ERR_PTR(ret);
	पूर्ण

	header->man = man;
	INIT_LIST_HEAD(&header->list);
	header->cb_header->status = SVGA_CB_STATUS_NONE;
	*p_header = header;

	वापस header->cmd;
पूर्ण

/**
 * vmw_cmdbuf_reserve_cur - Reserve space क्रम commands in the current
 * command buffer.
 *
 * @man: The command buffer manager.
 * @size: The requested size of the commands.
 * @ctx_id: The context id अगर any. Otherwise set to SVGA3D_REG_INVALID.
 * @पूर्णांकerruptible: Whether to sleep पूर्णांकerruptible जबतक रुकोing क्रम space.
 *
 * Returns a poपूर्णांकer to command buffer space अगर successful. Otherwise
 * वापसs an error poपूर्णांकer.
 */
अटल व्योम *vmw_cmdbuf_reserve_cur(काष्ठा vmw_cmdbuf_man *man,
				    माप_प्रकार size,
				    पूर्णांक ctx_id,
				    bool पूर्णांकerruptible)
अणु
	काष्ठा vmw_cmdbuf_header *cur;
	व्योम *ret;

	अगर (vmw_cmdbuf_cur_lock(man, पूर्णांकerruptible))
		वापस ERR_PTR(-ERESTARTSYS);

	cur = man->cur;
	अगर (cur && (size + man->cur_pos > cur->size ||
		    ((cur->cb_header->flags & SVGA_CB_FLAG_DX_CONTEXT) &&
		     ctx_id != cur->cb_header->dxContext)))
		__vmw_cmdbuf_cur_flush(man);

	अगर (!man->cur) अणु
		ret = vmw_cmdbuf_alloc(man,
				       max_t(माप_प्रकार, size, man->शेष_size),
				       पूर्णांकerruptible, &man->cur);
		अगर (IS_ERR(ret)) अणु
			vmw_cmdbuf_cur_unlock(man);
			वापस ret;
		पूर्ण

		cur = man->cur;
	पूर्ण

	अगर (ctx_id != SVGA3D_INVALID_ID) अणु
		cur->cb_header->flags |= SVGA_CB_FLAG_DX_CONTEXT;
		cur->cb_header->dxContext = ctx_id;
	पूर्ण

	cur->reserved = size;

	वापस (व्योम *) (man->cur->cmd + man->cur_pos);
पूर्ण

/**
 * vmw_cmdbuf_commit_cur - Commit commands in the current command buffer.
 *
 * @man: The command buffer manager.
 * @size: The size of the commands actually written.
 * @flush: Whether to flush the command buffer immediately.
 */
अटल व्योम vmw_cmdbuf_commit_cur(काष्ठा vmw_cmdbuf_man *man,
				  माप_प्रकार size, bool flush)
अणु
	काष्ठा vmw_cmdbuf_header *cur = man->cur;

	lockdep_निश्चित_held_once(&man->cur_mutex);

	WARN_ON(size > cur->reserved);
	man->cur_pos += size;
	अगर (!size)
		cur->cb_header->flags &= ~SVGA_CB_FLAG_DX_CONTEXT;
	अगर (flush)
		__vmw_cmdbuf_cur_flush(man);
	vmw_cmdbuf_cur_unlock(man);
पूर्ण

/**
 * vmw_cmdbuf_reserve - Reserve space क्रम commands in a command buffer.
 *
 * @man: The command buffer manager.
 * @size: The requested size of the commands.
 * @ctx_id: The context id अगर any. Otherwise set to SVGA3D_REG_INVALID.
 * @पूर्णांकerruptible: Whether to sleep पूर्णांकerruptible जबतक रुकोing क्रम space.
 * @header: Header of the command buffer. शून्य अगर the current command buffer
 * should be used.
 *
 * Returns a poपूर्णांकer to command buffer space अगर successful. Otherwise
 * वापसs an error poपूर्णांकer.
 */
व्योम *vmw_cmdbuf_reserve(काष्ठा vmw_cmdbuf_man *man, माप_प्रकार size,
			 पूर्णांक ctx_id, bool पूर्णांकerruptible,
			 काष्ठा vmw_cmdbuf_header *header)
अणु
	अगर (!header)
		वापस vmw_cmdbuf_reserve_cur(man, size, ctx_id, पूर्णांकerruptible);

	अगर (size > header->size)
		वापस ERR_PTR(-EINVAL);

	अगर (ctx_id != SVGA3D_INVALID_ID) अणु
		header->cb_header->flags |= SVGA_CB_FLAG_DX_CONTEXT;
		header->cb_header->dxContext = ctx_id;
	पूर्ण

	header->reserved = size;
	वापस header->cmd;
पूर्ण

/**
 * vmw_cmdbuf_commit - Commit commands in a command buffer.
 *
 * @man: The command buffer manager.
 * @size: The size of the commands actually written.
 * @header: Header of the command buffer. शून्य अगर the current command buffer
 * should be used.
 * @flush: Whether to flush the command buffer immediately.
 */
व्योम vmw_cmdbuf_commit(काष्ठा vmw_cmdbuf_man *man, माप_प्रकार size,
		       काष्ठा vmw_cmdbuf_header *header, bool flush)
अणु
	अगर (!header) अणु
		vmw_cmdbuf_commit_cur(man, size, flush);
		वापस;
	पूर्ण

	(व्योम) vmw_cmdbuf_cur_lock(man, false);
	__vmw_cmdbuf_cur_flush(man);
	WARN_ON(size > header->reserved);
	man->cur = header;
	man->cur_pos = size;
	अगर (!size)
		header->cb_header->flags &= ~SVGA_CB_FLAG_DX_CONTEXT;
	अगर (flush)
		__vmw_cmdbuf_cur_flush(man);
	vmw_cmdbuf_cur_unlock(man);
पूर्ण


/**
 * vmw_cmdbuf_send_device_command - Send a command through the device context.
 *
 * @man: The command buffer manager.
 * @command: Poपूर्णांकer to the command to send.
 * @size: Size of the command.
 *
 * Synchronously sends a device context command.
 */
अटल पूर्णांक vmw_cmdbuf_send_device_command(काष्ठा vmw_cmdbuf_man *man,
					  स्थिर व्योम *command,
					  माप_प्रकार size)
अणु
	काष्ठा vmw_cmdbuf_header *header;
	पूर्णांक status;
	व्योम *cmd = vmw_cmdbuf_alloc(man, size, false, &header);

	अगर (IS_ERR(cmd))
		वापस PTR_ERR(cmd);

	स_नकल(cmd, command, size);
	header->cb_header->length = size;
	header->cb_context = SVGA_CB_CONTEXT_DEVICE;
	spin_lock(&man->lock);
	status = vmw_cmdbuf_header_submit(header);
	spin_unlock(&man->lock);
	vmw_cmdbuf_header_मुक्त(header);

	अगर (status != SVGA_CB_STATUS_COMPLETED) अणु
		DRM_ERROR("Device context command failed with status %d\n",
			  status);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * vmw_cmdbuf_preempt - Send a preempt command through the device
 * context.
 *
 * @man: The command buffer manager.
 * @context: Device context to pass command through.
 *
 * Synchronously sends a preempt command.
 */
अटल पूर्णांक vmw_cmdbuf_preempt(काष्ठा vmw_cmdbuf_man *man, u32 context)
अणु
	काष्ठा अणु
		uपूर्णांक32 id;
		SVGADCCmdPreempt body;
	पूर्ण __packed cmd;

	cmd.id = SVGA_DC_CMD_PREEMPT;
	cmd.body.context = SVGA_CB_CONTEXT_0 + context;
	cmd.body.ignoreIDZero = 0;

	वापस vmw_cmdbuf_send_device_command(man, &cmd, माप(cmd));
पूर्ण


/**
 * vmw_cmdbuf_startstop - Send a start / stop command through the device
 * context.
 *
 * @man: The command buffer manager.
 * @context: Device context to start/stop.
 * @enable: Whether to enable or disable the context.
 *
 * Synchronously sends a device start / stop context command.
 */
अटल पूर्णांक vmw_cmdbuf_startstop(काष्ठा vmw_cmdbuf_man *man, u32 context,
				bool enable)
अणु
	काष्ठा अणु
		uपूर्णांक32 id;
		SVGADCCmdStartStop body;
	पूर्ण __packed cmd;

	cmd.id = SVGA_DC_CMD_START_STOP_CONTEXT;
	cmd.body.enable = (enable) ? 1 : 0;
	cmd.body.context = SVGA_CB_CONTEXT_0 + context;

	वापस vmw_cmdbuf_send_device_command(man, &cmd, माप(cmd));
पूर्ण

/**
 * vmw_cmdbuf_set_pool_size - Set command buffer manager sizes
 *
 * @man: The command buffer manager.
 * @size: The size of the मुख्य space pool.
 *
 * Set the size and allocate the मुख्य command buffer space pool.
 * If successful, this enables large command submissions.
 * Note that this function requires that rudimentary command
 * submission is alपढ़ोy available and that the MOB memory manager is alive.
 * Returns 0 on success. Negative error code on failure.
 */
पूर्णांक vmw_cmdbuf_set_pool_size(काष्ठा vmw_cmdbuf_man *man, माप_प्रकार size)
अणु
	काष्ठा vmw_निजी *dev_priv = man->dev_priv;
	bool dummy;
	पूर्णांक ret;

	अगर (man->has_pool)
		वापस -EINVAL;

	/* First, try to allocate a huge chunk of DMA memory */
	size = PAGE_ALIGN(size);
	man->map = dma_alloc_coherent(dev_priv->drm.dev, size,
				      &man->handle, GFP_KERNEL);
	अगर (man->map) अणु
		man->using_mob = false;
	पूर्ण अन्यथा अणु
		/*
		 * DMA memory failed. If we can have command buffers in a
		 * MOB, try to use that instead. Note that this will
		 * actually call पूर्णांकo the alपढ़ोy enabled manager, when
		 * binding the MOB.
		 */
		अगर (!(dev_priv->capabilities & SVGA_CAP_DX) ||
		    !dev_priv->has_mob)
			वापस -ENOMEM;

		ret = vmw_bo_create_kernel(dev_priv, size,
					   &vmw_mob_placement,
					   &man->cmd_space);
		अगर (ret)
			वापस ret;

		man->using_mob = true;
		ret = tपंचांग_bo_kmap(man->cmd_space, 0, size >> PAGE_SHIFT,
				  &man->map_obj);
		अगर (ret)
			जाओ out_no_map;

		man->map = tपंचांग_kmap_obj_भव(&man->map_obj, &dummy);
	पूर्ण

	man->size = size;
	drm_mm_init(&man->mm, 0, size >> PAGE_SHIFT);

	man->has_pool = true;

	/*
	 * For now, set the शेष size to VMW_CMDBUF_INLINE_SIZE to
	 * prevent deadlocks from happening when vmw_cmdbuf_space_pool()
	 * needs to रुको क्रम space and we block on further command
	 * submissions to be able to मुक्त up space.
	 */
	man->शेष_size = VMW_CMDBUF_INLINE_SIZE;
	DRM_INFO("Using command buffers with %s pool.\n",
		 (man->using_mob) ? "MOB" : "DMA");

	वापस 0;

out_no_map:
	अगर (man->using_mob) अणु
		tपंचांग_bo_put(man->cmd_space);
		man->cmd_space = शून्य;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * vmw_cmdbuf_man_create: Create a command buffer manager and enable it क्रम
 * अंतरभूत command buffer submissions only.
 *
 * @dev_priv: Poपूर्णांकer to device निजी काष्ठाure.
 *
 * Returns a poपूर्णांकer to a cummand buffer manager to success or error poपूर्णांकer
 * on failure. The command buffer manager will be enabled क्रम submissions of
 * size VMW_CMDBUF_INLINE_SIZE only.
 */
काष्ठा vmw_cmdbuf_man *vmw_cmdbuf_man_create(काष्ठा vmw_निजी *dev_priv)
अणु
	काष्ठा vmw_cmdbuf_man *man;
	काष्ठा vmw_cmdbuf_context *ctx;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	अगर (!(dev_priv->capabilities & SVGA_CAP_COMMAND_BUFFERS))
		वापस ERR_PTR(-ENOSYS);

	man = kzalloc(माप(*man), GFP_KERNEL);
	अगर (!man)
		वापस ERR_PTR(-ENOMEM);

	man->num_contexts = (dev_priv->capabilities & SVGA_CAP_HP_CMD_QUEUE) ?
		2 : 1;
	man->headers = dma_pool_create("vmwgfx cmdbuf",
				       dev_priv->drm.dev,
				       माप(SVGACBHeader),
				       64, PAGE_SIZE);
	अगर (!man->headers) अणु
		ret = -ENOMEM;
		जाओ out_no_pool;
	पूर्ण

	man->dheaders = dma_pool_create("vmwgfx inline cmdbuf",
					dev_priv->drm.dev,
					माप(काष्ठा vmw_cmdbuf_dheader),
					64, PAGE_SIZE);
	अगर (!man->dheaders) अणु
		ret = -ENOMEM;
		जाओ out_no_dpool;
	पूर्ण

	क्रम_each_cmdbuf_ctx(man, i, ctx)
		vmw_cmdbuf_ctx_init(ctx);

	INIT_LIST_HEAD(&man->error);
	spin_lock_init(&man->lock);
	mutex_init(&man->cur_mutex);
	mutex_init(&man->space_mutex);
	mutex_init(&man->error_mutex);
	man->शेष_size = VMW_CMDBUF_INLINE_SIZE;
	init_रुकोqueue_head(&man->alloc_queue);
	init_रुकोqueue_head(&man->idle_queue);
	man->dev_priv = dev_priv;
	man->max_hw_submitted = SVGA_CB_MAX_QUEUED_PER_CONTEXT - 1;
	INIT_WORK(&man->work, &vmw_cmdbuf_work_func);
	vmw_generic_रुकोer_add(dev_priv, SVGA_IRQFLAG_ERROR,
			       &dev_priv->error_रुकोers);
	ret = vmw_cmdbuf_startstop(man, 0, true);
	अगर (ret) अणु
		DRM_ERROR("Failed starting command buffer contexts\n");
		vmw_cmdbuf_man_destroy(man);
		वापस ERR_PTR(ret);
	पूर्ण

	वापस man;

out_no_dpool:
	dma_pool_destroy(man->headers);
out_no_pool:
	kमुक्त(man);

	वापस ERR_PTR(ret);
पूर्ण

/**
 * vmw_cmdbuf_हटाओ_pool - Take करोwn the मुख्य buffer space pool.
 *
 * @man: Poपूर्णांकer to a command buffer manager.
 *
 * This function हटाओs the मुख्य buffer space pool, and should be called
 * beक्रमe MOB memory management is हटाओd. When this function has been called,
 * only small command buffer submissions of size VMW_CMDBUF_INLINE_SIZE or
 * less are allowed, and the शेष size of the command buffer क्रम small kernel
 * submissions is also set to this size.
 */
व्योम vmw_cmdbuf_हटाओ_pool(काष्ठा vmw_cmdbuf_man *man)
अणु
	अगर (!man->has_pool)
		वापस;

	man->has_pool = false;
	man->शेष_size = VMW_CMDBUF_INLINE_SIZE;
	(व्योम) vmw_cmdbuf_idle(man, false, 10*HZ);
	अगर (man->using_mob) अणु
		(व्योम) tपंचांग_bo_kunmap(&man->map_obj);
		tपंचांग_bo_put(man->cmd_space);
		man->cmd_space = शून्य;
	पूर्ण अन्यथा अणु
		dma_मुक्त_coherent(man->dev_priv->drm.dev,
				  man->size, man->map, man->handle);
	पूर्ण
पूर्ण

/**
 * vmw_cmdbuf_man_destroy - Take करोwn a command buffer manager.
 *
 * @man: Poपूर्णांकer to a command buffer manager.
 *
 * This function idles and then destroys a command buffer manager.
 */
व्योम vmw_cmdbuf_man_destroy(काष्ठा vmw_cmdbuf_man *man)
अणु
	WARN_ON_ONCE(man->has_pool);
	(व्योम) vmw_cmdbuf_idle(man, false, 10*HZ);

	अगर (vmw_cmdbuf_startstop(man, 0, false))
		DRM_ERROR("Failed stopping command buffer contexts.\n");

	vmw_generic_रुकोer_हटाओ(man->dev_priv, SVGA_IRQFLAG_ERROR,
				  &man->dev_priv->error_रुकोers);
	(व्योम) cancel_work_sync(&man->work);
	dma_pool_destroy(man->dheaders);
	dma_pool_destroy(man->headers);
	mutex_destroy(&man->cur_mutex);
	mutex_destroy(&man->space_mutex);
	mutex_destroy(&man->error_mutex);
	kमुक्त(man);
पूर्ण
