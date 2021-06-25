<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2014-2018 Etnaviv Project
 */

#समावेश <drm/drm_drv.h>

#समावेश "etnaviv_cmdbuf.h"
#समावेश "etnaviv_gpu.h"
#समावेश "etnaviv_gem.h"
#समावेश "etnaviv_mmu.h"

#समावेश "common.xml.h"
#समावेश "state.xml.h"
#समावेश "state_blt.xml.h"
#समावेश "state_hi.xml.h"
#समावेश "state_3d.xml.h"
#समावेश "cmdstream.xml.h"

/*
 * Command Buffer helper:
 */


अटल अंतरभूत व्योम OUT(काष्ठा etnaviv_cmdbuf *buffer, u32 data)
अणु
	u32 *vaddr = (u32 *)buffer->vaddr;

	BUG_ON(buffer->user_size >= buffer->size);

	vaddr[buffer->user_size / 4] = data;
	buffer->user_size += 4;
पूर्ण

अटल अंतरभूत व्योम CMD_LOAD_STATE(काष्ठा etnaviv_cmdbuf *buffer,
	u32 reg, u32 value)
अणु
	u32 index = reg >> VIV_FE_LOAD_STATE_HEADER_OFFSET__SHR;

	buffer->user_size = ALIGN(buffer->user_size, 8);

	/* ग_लिखो a रेजिस्टर via cmd stream */
	OUT(buffer, VIV_FE_LOAD_STATE_HEADER_OP_LOAD_STATE |
		    VIV_FE_LOAD_STATE_HEADER_COUNT(1) |
		    VIV_FE_LOAD_STATE_HEADER_OFFSET(index));
	OUT(buffer, value);
पूर्ण

अटल अंतरभूत व्योम CMD_END(काष्ठा etnaviv_cmdbuf *buffer)
अणु
	buffer->user_size = ALIGN(buffer->user_size, 8);

	OUT(buffer, VIV_FE_END_HEADER_OP_END);
पूर्ण

अटल अंतरभूत व्योम CMD_WAIT(काष्ठा etnaviv_cmdbuf *buffer)
अणु
	buffer->user_size = ALIGN(buffer->user_size, 8);

	OUT(buffer, VIV_FE_WAIT_HEADER_OP_WAIT | 200);
पूर्ण

अटल अंतरभूत व्योम CMD_LINK(काष्ठा etnaviv_cmdbuf *buffer,
	u16 prefetch, u32 address)
अणु
	buffer->user_size = ALIGN(buffer->user_size, 8);

	OUT(buffer, VIV_FE_LINK_HEADER_OP_LINK |
		    VIV_FE_LINK_HEADER_PREFETCH(prefetch));
	OUT(buffer, address);
पूर्ण

अटल अंतरभूत व्योम CMD_STALL(काष्ठा etnaviv_cmdbuf *buffer,
	u32 from, u32 to)
अणु
	buffer->user_size = ALIGN(buffer->user_size, 8);

	OUT(buffer, VIV_FE_STALL_HEADER_OP_STALL);
	OUT(buffer, VIV_FE_STALL_TOKEN_FROM(from) | VIV_FE_STALL_TOKEN_TO(to));
पूर्ण

अटल अंतरभूत व्योम CMD_SEM(काष्ठा etnaviv_cmdbuf *buffer, u32 from, u32 to)
अणु
	CMD_LOAD_STATE(buffer, VIVS_GL_SEMAPHORE_TOKEN,
		       VIVS_GL_SEMAPHORE_TOKEN_FROM(from) |
		       VIVS_GL_SEMAPHORE_TOKEN_TO(to));
पूर्ण

अटल व्योम etnaviv_cmd_select_pipe(काष्ठा etnaviv_gpu *gpu,
	काष्ठा etnaviv_cmdbuf *buffer, u8 pipe)
अणु
	u32 flush = 0;

	lockdep_निश्चित_held(&gpu->lock);

	/*
	 * This assumes that अगर we're switching to 2D, we're चयनing
	 * away from 3D, and vice versa.  Hence, अगर we're चयनing to
	 * the 2D core, we need to flush the 3D depth and color caches,
	 * otherwise we need to flush the 2D pixel engine cache.
	 */
	अगर (gpu->exec_state == ETNA_PIPE_2D)
		flush = VIVS_GL_FLUSH_CACHE_PE2D;
	अन्यथा अगर (gpu->exec_state == ETNA_PIPE_3D)
		flush = VIVS_GL_FLUSH_CACHE_DEPTH | VIVS_GL_FLUSH_CACHE_COLOR;

	CMD_LOAD_STATE(buffer, VIVS_GL_FLUSH_CACHE, flush);
	CMD_SEM(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
	CMD_STALL(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);

	CMD_LOAD_STATE(buffer, VIVS_GL_PIPE_SELECT,
		       VIVS_GL_PIPE_SELECT_PIPE(pipe));
पूर्ण

अटल व्योम etnaviv_buffer_dump(काष्ठा etnaviv_gpu *gpu,
	काष्ठा etnaviv_cmdbuf *buf, u32 off, u32 len)
अणु
	u32 size = buf->size;
	u32 *ptr = buf->vaddr + off;

	dev_info(gpu->dev, "virt %p phys 0x%08x free 0x%08x\n",
			ptr, etnaviv_cmdbuf_get_va(buf,
			&gpu->mmu_context->cmdbuf_mapping) +
			off, size - len * 4 - off);

	prपूर्णांक_hex_dump(KERN_INFO, "cmd ", DUMP_PREFIX_OFFSET, 16, 4,
			ptr, len * 4, 0);
पूर्ण

/*
 * Safely replace the WAIT of a रुकोlink with a new command and argument.
 * The GPU may be executing this WAIT जबतक we're modअगरying it, so we have
 * to ग_लिखो it in a specअगरic order to aव्योम the GPU branching to somewhere
 * अन्यथा.  'wl_offset' is the offset to the first byte of the WAIT command.
 */
अटल व्योम etnaviv_buffer_replace_रुको(काष्ठा etnaviv_cmdbuf *buffer,
	अचिन्हित पूर्णांक wl_offset, u32 cmd, u32 arg)
अणु
	u32 *lw = buffer->vaddr + wl_offset;

	lw[1] = arg;
	mb();
	lw[0] = cmd;
	mb();
पूर्ण

/*
 * Ensure that there is space in the command buffer to contiguously ग_लिखो
 * 'cmd_dwords' 64-bit words पूर्णांकo the buffer, wrapping अगर necessary.
 */
अटल u32 etnaviv_buffer_reserve(काष्ठा etnaviv_gpu *gpu,
	काष्ठा etnaviv_cmdbuf *buffer, अचिन्हित पूर्णांक cmd_dwords)
अणु
	अगर (buffer->user_size + cmd_dwords * माप(u64) > buffer->size)
		buffer->user_size = 0;

	वापस etnaviv_cmdbuf_get_va(buffer,
				     &gpu->mmu_context->cmdbuf_mapping) +
	       buffer->user_size;
पूर्ण

u16 etnaviv_buffer_init(काष्ठा etnaviv_gpu *gpu)
अणु
	काष्ठा etnaviv_cmdbuf *buffer = &gpu->buffer;

	lockdep_निश्चित_held(&gpu->lock);

	/* initialize buffer */
	buffer->user_size = 0;

	CMD_WAIT(buffer);
	CMD_LINK(buffer, 2,
		 etnaviv_cmdbuf_get_va(buffer, &gpu->mmu_context->cmdbuf_mapping)
		 + buffer->user_size - 4);

	वापस buffer->user_size / 8;
पूर्ण

u16 etnaviv_buffer_config_mmuv2(काष्ठा etnaviv_gpu *gpu, u32 mtlb_addr, u32 safe_addr)
अणु
	काष्ठा etnaviv_cmdbuf *buffer = &gpu->buffer;

	lockdep_निश्चित_held(&gpu->lock);

	buffer->user_size = 0;

	अगर (gpu->identity.features & chipFeatures_PIPE_3D) अणु
		CMD_LOAD_STATE(buffer, VIVS_GL_PIPE_SELECT,
			       VIVS_GL_PIPE_SELECT_PIPE(ETNA_PIPE_3D));
		CMD_LOAD_STATE(buffer, VIVS_MMUv2_CONFIGURATION,
			mtlb_addr | VIVS_MMUv2_CONFIGURATION_MODE_MODE4_K);
		CMD_LOAD_STATE(buffer, VIVS_MMUv2_SAFE_ADDRESS, safe_addr);
		CMD_SEM(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
		CMD_STALL(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
	पूर्ण

	अगर (gpu->identity.features & chipFeatures_PIPE_2D) अणु
		CMD_LOAD_STATE(buffer, VIVS_GL_PIPE_SELECT,
			       VIVS_GL_PIPE_SELECT_PIPE(ETNA_PIPE_2D));
		CMD_LOAD_STATE(buffer, VIVS_MMUv2_CONFIGURATION,
			mtlb_addr | VIVS_MMUv2_CONFIGURATION_MODE_MODE4_K);
		CMD_LOAD_STATE(buffer, VIVS_MMUv2_SAFE_ADDRESS, safe_addr);
		CMD_SEM(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
		CMD_STALL(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
	पूर्ण

	CMD_END(buffer);

	buffer->user_size = ALIGN(buffer->user_size, 8);

	वापस buffer->user_size / 8;
पूर्ण

u16 etnaviv_buffer_config_pta(काष्ठा etnaviv_gpu *gpu, अचिन्हित लघु id)
अणु
	काष्ठा etnaviv_cmdbuf *buffer = &gpu->buffer;

	lockdep_निश्चित_held(&gpu->lock);

	buffer->user_size = 0;

	CMD_LOAD_STATE(buffer, VIVS_MMUv2_PTA_CONFIG,
		       VIVS_MMUv2_PTA_CONFIG_INDEX(id));

	CMD_END(buffer);

	buffer->user_size = ALIGN(buffer->user_size, 8);

	वापस buffer->user_size / 8;
पूर्ण

व्योम etnaviv_buffer_end(काष्ठा etnaviv_gpu *gpu)
अणु
	काष्ठा etnaviv_cmdbuf *buffer = &gpu->buffer;
	अचिन्हित पूर्णांक रुकोlink_offset = buffer->user_size - 16;
	u32 link_target, flush = 0;
	bool has_blt = !!(gpu->identity.minor_features5 &
			  chipMinorFeatures5_BLT_ENGINE);

	lockdep_निश्चित_held(&gpu->lock);

	अगर (gpu->exec_state == ETNA_PIPE_2D)
		flush = VIVS_GL_FLUSH_CACHE_PE2D;
	अन्यथा अगर (gpu->exec_state == ETNA_PIPE_3D)
		flush = VIVS_GL_FLUSH_CACHE_DEPTH |
			VIVS_GL_FLUSH_CACHE_COLOR |
			VIVS_GL_FLUSH_CACHE_TEXTURE |
			VIVS_GL_FLUSH_CACHE_TEXTUREVS |
			VIVS_GL_FLUSH_CACHE_SHADER_L2;

	अगर (flush) अणु
		अचिन्हित पूर्णांक dwords = 7;

		अगर (has_blt)
			dwords += 10;

		link_target = etnaviv_buffer_reserve(gpu, buffer, dwords);

		CMD_SEM(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
		CMD_STALL(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
		अगर (has_blt) अणु
			CMD_LOAD_STATE(buffer, VIVS_BLT_ENABLE, 0x1);
			CMD_SEM(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_BLT);
			CMD_STALL(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_BLT);
			CMD_LOAD_STATE(buffer, VIVS_BLT_ENABLE, 0x0);
		पूर्ण
		CMD_LOAD_STATE(buffer, VIVS_GL_FLUSH_CACHE, flush);
		अगर (gpu->exec_state == ETNA_PIPE_3D) अणु
			अगर (has_blt) अणु
				CMD_LOAD_STATE(buffer, VIVS_BLT_ENABLE, 0x1);
				CMD_LOAD_STATE(buffer, VIVS_BLT_SET_COMMAND, 0x1);
				CMD_LOAD_STATE(buffer, VIVS_BLT_ENABLE, 0x0);
			पूर्ण अन्यथा अणु
				CMD_LOAD_STATE(buffer, VIVS_TS_FLUSH_CACHE,
					       VIVS_TS_FLUSH_CACHE_FLUSH);
			पूर्ण
		पूर्ण
		CMD_SEM(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
		CMD_STALL(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
		अगर (has_blt) अणु
			CMD_LOAD_STATE(buffer, VIVS_BLT_ENABLE, 0x1);
			CMD_SEM(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_BLT);
			CMD_STALL(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_BLT);
			CMD_LOAD_STATE(buffer, VIVS_BLT_ENABLE, 0x0);
		पूर्ण
		CMD_END(buffer);

		etnaviv_buffer_replace_रुको(buffer, रुकोlink_offset,
					    VIV_FE_LINK_HEADER_OP_LINK |
					    VIV_FE_LINK_HEADER_PREFETCH(dwords),
					    link_target);
	पूर्ण अन्यथा अणु
		/* Replace the last link-रुको with an "END" command */
		etnaviv_buffer_replace_रुको(buffer, रुकोlink_offset,
					    VIV_FE_END_HEADER_OP_END, 0);
	पूर्ण
पूर्ण

/* Append a 'sync point' to the ring buffer. */
व्योम etnaviv_sync_poपूर्णांक_queue(काष्ठा etnaviv_gpu *gpu, अचिन्हित पूर्णांक event)
अणु
	काष्ठा etnaviv_cmdbuf *buffer = &gpu->buffer;
	अचिन्हित पूर्णांक रुकोlink_offset = buffer->user_size - 16;
	u32 dwords, target;

	lockdep_निश्चित_held(&gpu->lock);

	/*
	 * We need at most 3 dwords in the वापस target:
	 * 1 event + 1 end + 1 रुको + 1 link.
	 */
	dwords = 4;
	target = etnaviv_buffer_reserve(gpu, buffer, dwords);

	/* Signal sync poपूर्णांक event */
	CMD_LOAD_STATE(buffer, VIVS_GL_EVENT, VIVS_GL_EVENT_EVENT_ID(event) |
		       VIVS_GL_EVENT_FROM_PE);

	/* Stop the FE to 'pause' the GPU */
	CMD_END(buffer);

	/* Append रुकोlink */
	CMD_WAIT(buffer);
	CMD_LINK(buffer, 2,
		 etnaviv_cmdbuf_get_va(buffer, &gpu->mmu_context->cmdbuf_mapping)
		 + buffer->user_size - 4);

	/*
	 * Kick off the 'sync point' command by replacing the previous
	 * WAIT with a link to the address in the ring buffer.
	 */
	etnaviv_buffer_replace_रुको(buffer, रुकोlink_offset,
				    VIV_FE_LINK_HEADER_OP_LINK |
				    VIV_FE_LINK_HEADER_PREFETCH(dwords),
				    target);
पूर्ण

/* Append a command buffer to the ring buffer. */
व्योम etnaviv_buffer_queue(काष्ठा etnaviv_gpu *gpu, u32 exec_state,
	काष्ठा etnaviv_iommu_context *mmu_context, अचिन्हित पूर्णांक event,
	काष्ठा etnaviv_cmdbuf *cmdbuf)
अणु
	काष्ठा etnaviv_cmdbuf *buffer = &gpu->buffer;
	अचिन्हित पूर्णांक रुकोlink_offset = buffer->user_size - 16;
	u32 वापस_target, वापस_dwords;
	u32 link_target, link_dwords;
	bool चयन_context = gpu->exec_state != exec_state;
	bool चयन_mmu_context = gpu->mmu_context != mmu_context;
	अचिन्हित पूर्णांक new_flush_seq = READ_ONCE(gpu->mmu_context->flush_seq);
	bool need_flush = चयन_mmu_context || gpu->flush_seq != new_flush_seq;
	bool has_blt = !!(gpu->identity.minor_features5 &
			  chipMinorFeatures5_BLT_ENGINE);

	lockdep_निश्चित_held(&gpu->lock);

	अगर (drm_debug_enabled(DRM_UT_DRIVER))
		etnaviv_buffer_dump(gpu, buffer, 0, 0x50);

	link_target = etnaviv_cmdbuf_get_va(cmdbuf,
					    &gpu->mmu_context->cmdbuf_mapping);
	link_dwords = cmdbuf->size / 8;

	/*
	 * If we need मुख्यtenance prior to submitting this buffer, we will
	 * need to append a mmu flush load state, followed by a new
	 * link to this buffer - a total of four additional words.
	 */
	अगर (need_flush || चयन_context) अणु
		u32 target, extra_dwords;

		/* link command */
		extra_dwords = 1;

		/* flush command */
		अगर (need_flush) अणु
			अगर (gpu->mmu_context->global->version == ETNAVIV_IOMMU_V1)
				extra_dwords += 1;
			अन्यथा
				extra_dwords += 3;
		पूर्ण

		/* pipe चयन commands */
		अगर (चयन_context)
			extra_dwords += 4;

		/* PTA load command */
		अगर (चयन_mmu_context && gpu->sec_mode == ETNA_SEC_KERNEL)
			extra_dwords += 1;

		target = etnaviv_buffer_reserve(gpu, buffer, extra_dwords);
		/*
		 * Switch MMU context अगर necessary. Must be करोne after the
		 * link target has been calculated, as the jump क्रमward in the
		 * kernel ring still uses the last active MMU context beक्रमe
		 * the चयन.
		 */
		अगर (चयन_mmu_context) अणु
			काष्ठा etnaviv_iommu_context *old_context = gpu->mmu_context;

			etnaviv_iommu_context_get(mmu_context);
			gpu->mmu_context = mmu_context;
			etnaviv_iommu_context_put(old_context);
		पूर्ण

		अगर (need_flush) अणु
			/* Add the MMU flush */
			अगर (gpu->mmu_context->global->version == ETNAVIV_IOMMU_V1) अणु
				CMD_LOAD_STATE(buffer, VIVS_GL_FLUSH_MMU,
					       VIVS_GL_FLUSH_MMU_FLUSH_FEMMU |
					       VIVS_GL_FLUSH_MMU_FLUSH_UNK1 |
					       VIVS_GL_FLUSH_MMU_FLUSH_UNK2 |
					       VIVS_GL_FLUSH_MMU_FLUSH_PEMMU |
					       VIVS_GL_FLUSH_MMU_FLUSH_UNK4);
			पूर्ण अन्यथा अणु
				u32 flush = VIVS_MMUv2_CONFIGURATION_MODE_MASK |
					    VIVS_MMUv2_CONFIGURATION_FLUSH_FLUSH;

				अगर (चयन_mmu_context &&
				    gpu->sec_mode == ETNA_SEC_KERNEL) अणु
					अचिन्हित लघु id =
						etnaviv_iommuv2_get_pta_id(gpu->mmu_context);
					CMD_LOAD_STATE(buffer,
						VIVS_MMUv2_PTA_CONFIG,
						VIVS_MMUv2_PTA_CONFIG_INDEX(id));
				पूर्ण

				अगर (gpu->sec_mode == ETNA_SEC_NONE)
					flush |= etnaviv_iommuv2_get_mtlb_addr(gpu->mmu_context);

				CMD_LOAD_STATE(buffer, VIVS_MMUv2_CONFIGURATION,
					       flush);
				CMD_SEM(buffer, SYNC_RECIPIENT_FE,
					SYNC_RECIPIENT_PE);
				CMD_STALL(buffer, SYNC_RECIPIENT_FE,
					SYNC_RECIPIENT_PE);
			पूर्ण

			gpu->flush_seq = new_flush_seq;
		पूर्ण

		अगर (चयन_context) अणु
			etnaviv_cmd_select_pipe(gpu, buffer, exec_state);
			gpu->exec_state = exec_state;
		पूर्ण

		/* And the link to the submitted buffer */
		link_target = etnaviv_cmdbuf_get_va(cmdbuf,
					&gpu->mmu_context->cmdbuf_mapping);
		CMD_LINK(buffer, link_dwords, link_target);

		/* Update the link target to poपूर्णांक to above inकाष्ठाions */
		link_target = target;
		link_dwords = extra_dwords;
	पूर्ण

	/*
	 * Append a LINK to the submitted command buffer to वापस to
	 * the ring buffer.  वापस_target is the ring target address.
	 * We need at most 7 dwords in the वापस target: 2 cache flush +
	 * 2 semaphore stall + 1 event + 1 रुको + 1 link.
	 */
	वापस_dwords = 7;

	/*
	 * When the BLT engine is present we need 6 more dwords in the वापस
	 * target: 3 enable/flush/disable + 4 enable/semaphore stall/disable,
	 * but we करोn't need the normal TS flush state.
	 */
	अगर (has_blt)
		वापस_dwords += 6;

	वापस_target = etnaviv_buffer_reserve(gpu, buffer, वापस_dwords);
	CMD_LINK(cmdbuf, वापस_dwords, वापस_target);

	/*
	 * Append a cache flush, stall, event, रुको and link poपूर्णांकing back to
	 * the रुको command to the ring buffer.
	 */
	अगर (gpu->exec_state == ETNA_PIPE_2D) अणु
		CMD_LOAD_STATE(buffer, VIVS_GL_FLUSH_CACHE,
				       VIVS_GL_FLUSH_CACHE_PE2D);
	पूर्ण अन्यथा अणु
		CMD_LOAD_STATE(buffer, VIVS_GL_FLUSH_CACHE,
				       VIVS_GL_FLUSH_CACHE_DEPTH |
				       VIVS_GL_FLUSH_CACHE_COLOR);
		अगर (has_blt) अणु
			CMD_LOAD_STATE(buffer, VIVS_BLT_ENABLE, 0x1);
			CMD_LOAD_STATE(buffer, VIVS_BLT_SET_COMMAND, 0x1);
			CMD_LOAD_STATE(buffer, VIVS_BLT_ENABLE, 0x0);
		पूर्ण अन्यथा अणु
			CMD_LOAD_STATE(buffer, VIVS_TS_FLUSH_CACHE,
					       VIVS_TS_FLUSH_CACHE_FLUSH);
		पूर्ण
	पूर्ण
	CMD_SEM(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);
	CMD_STALL(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_PE);

	अगर (has_blt) अणु
		CMD_LOAD_STATE(buffer, VIVS_BLT_ENABLE, 0x1);
		CMD_SEM(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_BLT);
		CMD_STALL(buffer, SYNC_RECIPIENT_FE, SYNC_RECIPIENT_BLT);
		CMD_LOAD_STATE(buffer, VIVS_BLT_ENABLE, 0x0);
	पूर्ण

	CMD_LOAD_STATE(buffer, VIVS_GL_EVENT, VIVS_GL_EVENT_EVENT_ID(event) |
		       VIVS_GL_EVENT_FROM_PE);
	CMD_WAIT(buffer);
	CMD_LINK(buffer, 2,
		 etnaviv_cmdbuf_get_va(buffer, &gpu->mmu_context->cmdbuf_mapping)
		 + buffer->user_size - 4);

	अगर (drm_debug_enabled(DRM_UT_DRIVER))
		pr_info("stream link to 0x%08x @ 0x%08x %p\n",
			वापस_target,
			etnaviv_cmdbuf_get_va(cmdbuf, &gpu->mmu_context->cmdbuf_mapping),
			cmdbuf->vaddr);

	अगर (drm_debug_enabled(DRM_UT_DRIVER)) अणु
		prपूर्णांक_hex_dump(KERN_INFO, "cmd ", DUMP_PREFIX_OFFSET, 16, 4,
			       cmdbuf->vaddr, cmdbuf->size, 0);

		pr_info("link op: %p\n", buffer->vaddr + रुकोlink_offset);
		pr_info("addr: 0x%08x\n", link_target);
		pr_info("back: 0x%08x\n", वापस_target);
		pr_info("event: %d\n", event);
	पूर्ण

	/*
	 * Kick off the submitted command by replacing the previous
	 * WAIT with a link to the address in the ring buffer.
	 */
	etnaviv_buffer_replace_रुको(buffer, रुकोlink_offset,
				    VIV_FE_LINK_HEADER_OP_LINK |
				    VIV_FE_LINK_HEADER_PREFETCH(link_dwords),
				    link_target);

	अगर (drm_debug_enabled(DRM_UT_DRIVER))
		etnaviv_buffer_dump(gpu, buffer, 0, 0x50);
पूर्ण
