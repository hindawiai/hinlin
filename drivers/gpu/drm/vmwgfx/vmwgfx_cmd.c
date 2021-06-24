<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/**************************************************************************
 *
 * Copyright 2009-2020 VMware, Inc., Palo Alto, CA., USA
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

#समावेश <linux/sched/संकेत.स>

#समावेश <drm/tपंचांग/tपंचांग_placement.h>

#समावेश "vmwgfx_drv.h"

काष्ठा vmw_temp_set_context अणु
	SVGA3dCmdHeader header;
	SVGA3dCmdDXTempSetContext body;
पूर्ण;

bool vmw_supports_3d(काष्ठा vmw_निजी *dev_priv)
अणु
	uपूर्णांक32_t fअगरo_min, hwversion;
	स्थिर काष्ठा vmw_fअगरo_state *fअगरo = &dev_priv->fअगरo;

	अगर (!(dev_priv->capabilities & SVGA_CAP_3D))
		वापस false;

	अगर (dev_priv->capabilities & SVGA_CAP_GBOBJECTS) अणु
		uपूर्णांक32_t result;

		अगर (!dev_priv->has_mob)
			वापस false;

		spin_lock(&dev_priv->cap_lock);
		vmw_ग_लिखो(dev_priv, SVGA_REG_DEV_CAP, SVGA3D_DEVCAP_3D);
		result = vmw_पढ़ो(dev_priv, SVGA_REG_DEV_CAP);
		spin_unlock(&dev_priv->cap_lock);

		वापस (result != 0);
	पूर्ण

	अगर (!(dev_priv->capabilities & SVGA_CAP_EXTENDED_FIFO))
		वापस false;

	fअगरo_min = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_MIN);
	अगर (fअगरo_min <= SVGA_FIFO_3D_HWVERSION * माप(अचिन्हित पूर्णांक))
		वापस false;

	hwversion = vmw_fअगरo_mem_पढ़ो(dev_priv,
				      ((fअगरo->capabilities &
					SVGA_FIFO_CAP_3D_HWVERSION_REVISED) ?
					       SVGA_FIFO_3D_HWVERSION_REVISED :
					       SVGA_FIFO_3D_HWVERSION));

	अगर (hwversion == 0)
		वापस false;

	अगर (hwversion < SVGA3D_HWVERSION_WS8_B1)
		वापस false;

	/* Legacy Display Unit करोes not support surfaces */
	अगर (dev_priv->active_display_unit == vmw_du_legacy)
		वापस false;

	वापस true;
पूर्ण

bool vmw_fअगरo_have_pitchlock(काष्ठा vmw_निजी *dev_priv)
अणु
	uपूर्णांक32_t caps;

	अगर (!(dev_priv->capabilities & SVGA_CAP_EXTENDED_FIFO))
		वापस false;

	caps = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_CAPABILITIES);
	अगर (caps & SVGA_FIFO_CAP_PITCHLOCK)
		वापस true;

	वापस false;
पूर्ण

पूर्णांक vmw_fअगरo_init(काष्ठा vmw_निजी *dev_priv, काष्ठा vmw_fअगरo_state *fअगरo)
अणु
	uपूर्णांक32_t max;
	uपूर्णांक32_t min;

	fअगरo->dx = false;
	fअगरo->अटल_buffer_size = VMWGFX_FIFO_STATIC_SIZE;
	fअगरo->अटल_buffer = vदो_स्मृति(fअगरo->अटल_buffer_size);
	अगर (unlikely(fअगरo->अटल_buffer == शून्य))
		वापस -ENOMEM;

	fअगरo->dynamic_buffer = शून्य;
	fअगरo->reserved_size = 0;
	fअगरo->using_bounce_buffer = false;

	mutex_init(&fअगरo->fअगरo_mutex);
	init_rwsem(&fअगरo->rwsem);

	DRM_INFO("width %d\n", vmw_पढ़ो(dev_priv, SVGA_REG_WIDTH));
	DRM_INFO("height %d\n", vmw_पढ़ो(dev_priv, SVGA_REG_HEIGHT));
	DRM_INFO("bpp %d\n", vmw_पढ़ो(dev_priv, SVGA_REG_BITS_PER_PIXEL));

	dev_priv->enable_state = vmw_पढ़ो(dev_priv, SVGA_REG_ENABLE);
	dev_priv->config_करोne_state = vmw_पढ़ो(dev_priv, SVGA_REG_CONFIG_DONE);
	dev_priv->traces_state = vmw_पढ़ो(dev_priv, SVGA_REG_TRACES);

	vmw_ग_लिखो(dev_priv, SVGA_REG_ENABLE, SVGA_REG_ENABLE_ENABLE |
		  SVGA_REG_ENABLE_HIDE);

	vmw_ग_लिखो(dev_priv, SVGA_REG_TRACES, 0);

	min = 4;
	अगर (dev_priv->capabilities & SVGA_CAP_EXTENDED_FIFO)
		min = vmw_पढ़ो(dev_priv, SVGA_REG_MEM_REGS);
	min <<= 2;

	अगर (min < PAGE_SIZE)
		min = PAGE_SIZE;

	vmw_fअगरo_mem_ग_लिखो(dev_priv, SVGA_FIFO_MIN, min);
	vmw_fअगरo_mem_ग_लिखो(dev_priv, SVGA_FIFO_MAX, dev_priv->fअगरo_mem_size);
	wmb();
	vmw_fअगरo_mem_ग_लिखो(dev_priv, SVGA_FIFO_NEXT_CMD, min);
	vmw_fअगरo_mem_ग_लिखो(dev_priv, SVGA_FIFO_STOP, min);
	vmw_fअगरo_mem_ग_लिखो(dev_priv, SVGA_FIFO_BUSY, 0);
	mb();

	vmw_ग_लिखो(dev_priv, SVGA_REG_CONFIG_DONE, 1);

	max = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_MAX);
	min = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_MIN);
	fअगरo->capabilities = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_CAPABILITIES);

	DRM_INFO("Fifo max 0x%08x min 0x%08x cap 0x%08x\n",
		 (अचिन्हित पूर्णांक) max,
		 (अचिन्हित पूर्णांक) min,
		 (अचिन्हित पूर्णांक) fअगरo->capabilities);

	atomic_set(&dev_priv->marker_seq, dev_priv->last_पढ़ो_seqno);
	vmw_fअगरo_mem_ग_लिखो(dev_priv, SVGA_FIFO_FENCE, dev_priv->last_पढ़ो_seqno);

	वापस 0;
पूर्ण

व्योम vmw_fअगरo_ping_host(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t reason)
अणु
	u32 *fअगरo_mem = dev_priv->fअगरo_mem;

	अगर (cmpxchg(fअगरo_mem + SVGA_FIFO_BUSY, 0, 1) == 0)
		vmw_ग_लिखो(dev_priv, SVGA_REG_SYNC, reason);
पूर्ण

व्योम vmw_fअगरo_release(काष्ठा vmw_निजी *dev_priv, काष्ठा vmw_fअगरo_state *fअगरo)
अणु
	vmw_ग_लिखो(dev_priv, SVGA_REG_SYNC, SVGA_SYNC_GENERIC);
	जबतक (vmw_पढ़ो(dev_priv, SVGA_REG_BUSY) != 0)
		;

	dev_priv->last_पढ़ो_seqno = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_FENCE);

	vmw_ग_लिखो(dev_priv, SVGA_REG_CONFIG_DONE,
		  dev_priv->config_करोne_state);
	vmw_ग_लिखो(dev_priv, SVGA_REG_ENABLE,
		  dev_priv->enable_state);
	vmw_ग_लिखो(dev_priv, SVGA_REG_TRACES,
		  dev_priv->traces_state);

	अगर (likely(fअगरo->अटल_buffer != शून्य)) अणु
		vमुक्त(fअगरo->अटल_buffer);
		fअगरo->अटल_buffer = शून्य;
	पूर्ण

	अगर (likely(fअगरo->dynamic_buffer != शून्य)) अणु
		vमुक्त(fअगरo->dynamic_buffer);
		fअगरo->dynamic_buffer = शून्य;
	पूर्ण
पूर्ण

अटल bool vmw_fअगरo_is_full(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t bytes)
अणु
	uपूर्णांक32_t max = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_MAX);
	uपूर्णांक32_t next_cmd = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_NEXT_CMD);
	uपूर्णांक32_t min = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_MIN);
	uपूर्णांक32_t stop = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_STOP);

	वापस ((max - next_cmd) + (stop - min) <= bytes);
पूर्ण

अटल पूर्णांक vmw_fअगरo_रुको_noirq(काष्ठा vmw_निजी *dev_priv,
			       uपूर्णांक32_t bytes, bool पूर्णांकerruptible,
			       अचिन्हित दीर्घ समयout)
अणु
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ end_jअगरfies = jअगरfies + समयout;
	DEFINE_WAIT(__रुको);

	DRM_INFO("Fifo wait noirq.\n");

	क्रम (;;) अणु
		prepare_to_रुको(&dev_priv->fअगरo_queue, &__रुको,
				(पूर्णांकerruptible) ?
				TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE);
		अगर (!vmw_fअगरo_is_full(dev_priv, bytes))
			अवरोध;
		अगर (समय_after_eq(jअगरfies, end_jअगरfies)) अणु
			ret = -EBUSY;
			DRM_ERROR("SVGA device lockup.\n");
			अवरोध;
		पूर्ण
		schedule_समयout(1);
		अगर (पूर्णांकerruptible && संकेत_pending(current)) अणु
			ret = -ERESTARTSYS;
			अवरोध;
		पूर्ण
	पूर्ण
	finish_रुको(&dev_priv->fअगरo_queue, &__रुको);
	wake_up_all(&dev_priv->fअगरo_queue);
	DRM_INFO("Fifo noirq exit.\n");
	वापस ret;
पूर्ण

अटल पूर्णांक vmw_fअगरo_रुको(काष्ठा vmw_निजी *dev_priv,
			 uपूर्णांक32_t bytes, bool पूर्णांकerruptible,
			 अचिन्हित दीर्घ समयout)
अणु
	दीर्घ ret = 1L;

	अगर (likely(!vmw_fअगरo_is_full(dev_priv, bytes)))
		वापस 0;

	vmw_fअगरo_ping_host(dev_priv, SVGA_SYNC_FIFOFULL);
	अगर (!(dev_priv->capabilities & SVGA_CAP_IRQMASK))
		वापस vmw_fअगरo_रुको_noirq(dev_priv, bytes,
					   पूर्णांकerruptible, समयout);

	vmw_generic_रुकोer_add(dev_priv, SVGA_IRQFLAG_FIFO_PROGRESS,
			       &dev_priv->fअगरo_queue_रुकोers);

	अगर (पूर्णांकerruptible)
		ret = रुको_event_पूर्णांकerruptible_समयout
		    (dev_priv->fअगरo_queue,
		     !vmw_fअगरo_is_full(dev_priv, bytes), समयout);
	अन्यथा
		ret = रुको_event_समयout
		    (dev_priv->fअगरo_queue,
		     !vmw_fअगरo_is_full(dev_priv, bytes), समयout);

	अगर (unlikely(ret == 0))
		ret = -EBUSY;
	अन्यथा अगर (likely(ret > 0))
		ret = 0;

	vmw_generic_रुकोer_हटाओ(dev_priv, SVGA_IRQFLAG_FIFO_PROGRESS,
				  &dev_priv->fअगरo_queue_रुकोers);

	वापस ret;
पूर्ण

/*
 * Reserve @bytes number of bytes in the fअगरo.
 *
 * This function will वापस शून्य (error) on two conditions:
 *  If it समयouts रुकोing क्रम fअगरo space, or अगर @bytes is larger than the
 *   available fअगरo space.
 *
 * Returns:
 *   Poपूर्णांकer to the fअगरo, or null on error (possible hardware hang).
 */
अटल व्योम *vmw_local_fअगरo_reserve(काष्ठा vmw_निजी *dev_priv,
				    uपूर्णांक32_t bytes)
अणु
	काष्ठा vmw_fअगरo_state *fअगरo_state = &dev_priv->fअगरo;
	u32  *fअगरo_mem = dev_priv->fअगरo_mem;
	uपूर्णांक32_t max;
	uपूर्णांक32_t min;
	uपूर्णांक32_t next_cmd;
	uपूर्णांक32_t reserveable = fअगरo_state->capabilities & SVGA_FIFO_CAP_RESERVE;
	पूर्णांक ret;

	mutex_lock(&fअगरo_state->fअगरo_mutex);
	max = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_MAX);
	min = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_MIN);
	next_cmd = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_NEXT_CMD);

	अगर (unlikely(bytes >= (max - min)))
		जाओ out_err;

	BUG_ON(fअगरo_state->reserved_size != 0);
	BUG_ON(fअगरo_state->dynamic_buffer != शून्य);

	fअगरo_state->reserved_size = bytes;

	जबतक (1) अणु
		uपूर्णांक32_t stop = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_STOP);
		bool need_bounce = false;
		bool reserve_in_place = false;

		अगर (next_cmd >= stop) अणु
			अगर (likely((next_cmd + bytes < max ||
				    (next_cmd + bytes == max && stop > min))))
				reserve_in_place = true;

			अन्यथा अगर (vmw_fअगरo_is_full(dev_priv, bytes)) अणु
				ret = vmw_fअगरo_रुको(dev_priv, bytes,
						    false, 3 * HZ);
				अगर (unlikely(ret != 0))
					जाओ out_err;
			पूर्ण अन्यथा
				need_bounce = true;

		पूर्ण अन्यथा अणु

			अगर (likely((next_cmd + bytes < stop)))
				reserve_in_place = true;
			अन्यथा अणु
				ret = vmw_fअगरo_रुको(dev_priv, bytes,
						    false, 3 * HZ);
				अगर (unlikely(ret != 0))
					जाओ out_err;
			पूर्ण
		पूर्ण

		अगर (reserve_in_place) अणु
			अगर (reserveable || bytes <= माप(uपूर्णांक32_t)) अणु
				fअगरo_state->using_bounce_buffer = false;

				अगर (reserveable)
					vmw_fअगरo_mem_ग_लिखो(dev_priv,
							   SVGA_FIFO_RESERVED,
							   bytes);
				वापस (व्योम __क्रमce *) (fअगरo_mem +
							 (next_cmd >> 2));
			पूर्ण अन्यथा अणु
				need_bounce = true;
			पूर्ण
		पूर्ण

		अगर (need_bounce) अणु
			fअगरo_state->using_bounce_buffer = true;
			अगर (bytes < fअगरo_state->अटल_buffer_size)
				वापस fअगरo_state->अटल_buffer;
			अन्यथा अणु
				fअगरo_state->dynamic_buffer = vदो_स्मृति(bytes);
				अगर (!fअगरo_state->dynamic_buffer)
					जाओ out_err;
				वापस fअगरo_state->dynamic_buffer;
			पूर्ण
		पूर्ण
	पूर्ण
out_err:
	fअगरo_state->reserved_size = 0;
	mutex_unlock(&fअगरo_state->fअगरo_mutex);

	वापस शून्य;
पूर्ण

व्योम *vmw_cmd_ctx_reserve(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t bytes,
			  पूर्णांक ctx_id)
अणु
	व्योम *ret;

	अगर (dev_priv->cman)
		ret = vmw_cmdbuf_reserve(dev_priv->cman, bytes,
					 ctx_id, false, शून्य);
	अन्यथा अगर (ctx_id == SVGA3D_INVALID_ID)
		ret = vmw_local_fअगरo_reserve(dev_priv, bytes);
	अन्यथा अणु
		WARN(1, "Command buffer has not been allocated.\n");
		ret = शून्य;
	पूर्ण
	अगर (IS_ERR_OR_शून्य(ret))
		वापस शून्य;

	वापस ret;
पूर्ण

अटल व्योम vmw_fअगरo_res_copy(काष्ठा vmw_fअगरo_state *fअगरo_state,
			      काष्ठा vmw_निजी *vmw,
			      uपूर्णांक32_t next_cmd,
			      uपूर्णांक32_t max, uपूर्णांक32_t min, uपूर्णांक32_t bytes)
अणु
	u32 *fअगरo_mem = vmw->fअगरo_mem;
	uपूर्णांक32_t chunk_size = max - next_cmd;
	uपूर्णांक32_t rest;
	uपूर्णांक32_t *buffer = (fअगरo_state->dynamic_buffer != शून्य) ?
	    fअगरo_state->dynamic_buffer : fअगरo_state->अटल_buffer;

	अगर (bytes < chunk_size)
		chunk_size = bytes;

	vmw_fअगरo_mem_ग_लिखो(vmw, SVGA_FIFO_RESERVED, bytes);
	mb();
	स_नकल(fअगरo_mem + (next_cmd >> 2), buffer, chunk_size);
	rest = bytes - chunk_size;
	अगर (rest)
		स_नकल(fअगरo_mem + (min >> 2), buffer + (chunk_size >> 2), rest);
पूर्ण

अटल व्योम vmw_fअगरo_slow_copy(काष्ठा vmw_fअगरo_state *fअगरo_state,
			       काष्ठा vmw_निजी *vmw,
			       uपूर्णांक32_t next_cmd,
			       uपूर्णांक32_t max, uपूर्णांक32_t min, uपूर्णांक32_t bytes)
अणु
	uपूर्णांक32_t *buffer = (fअगरo_state->dynamic_buffer != शून्य) ?
	    fअगरo_state->dynamic_buffer : fअगरo_state->अटल_buffer;

	जबतक (bytes > 0) अणु
		vmw_fअगरo_mem_ग_लिखो(vmw, (next_cmd >> 2), *buffer++);
		next_cmd += माप(uपूर्णांक32_t);
		अगर (unlikely(next_cmd == max))
			next_cmd = min;
		mb();
		vmw_fअगरo_mem_ग_लिखो(vmw, SVGA_FIFO_NEXT_CMD, next_cmd);
		mb();
		bytes -= माप(uपूर्णांक32_t);
	पूर्ण
पूर्ण

अटल व्योम vmw_local_fअगरo_commit(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t bytes)
अणु
	काष्ठा vmw_fअगरo_state *fअगरo_state = &dev_priv->fअगरo;
	uपूर्णांक32_t next_cmd = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_NEXT_CMD);
	uपूर्णांक32_t max = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_MAX);
	uपूर्णांक32_t min = vmw_fअगरo_mem_पढ़ो(dev_priv, SVGA_FIFO_MIN);
	bool reserveable = fअगरo_state->capabilities & SVGA_FIFO_CAP_RESERVE;

	अगर (fअगरo_state->dx)
		bytes += माप(काष्ठा vmw_temp_set_context);

	fअगरo_state->dx = false;
	BUG_ON((bytes & 3) != 0);
	BUG_ON(bytes > fअगरo_state->reserved_size);

	fअगरo_state->reserved_size = 0;

	अगर (fअगरo_state->using_bounce_buffer) अणु
		अगर (reserveable)
			vmw_fअगरo_res_copy(fअगरo_state, dev_priv,
					  next_cmd, max, min, bytes);
		अन्यथा
			vmw_fअगरo_slow_copy(fअगरo_state, dev_priv,
					   next_cmd, max, min, bytes);

		अगर (fअगरo_state->dynamic_buffer) अणु
			vमुक्त(fअगरo_state->dynamic_buffer);
			fअगरo_state->dynamic_buffer = शून्य;
		पूर्ण

	पूर्ण

	करोwn_ग_लिखो(&fअगरo_state->rwsem);
	अगर (fअगरo_state->using_bounce_buffer || reserveable) अणु
		next_cmd += bytes;
		अगर (next_cmd >= max)
			next_cmd -= max - min;
		mb();
		vmw_fअगरo_mem_ग_लिखो(dev_priv, SVGA_FIFO_NEXT_CMD, next_cmd);
	पूर्ण

	अगर (reserveable)
		vmw_fअगरo_mem_ग_लिखो(dev_priv, SVGA_FIFO_RESERVED, 0);
	mb();
	up_ग_लिखो(&fअगरo_state->rwsem);
	vmw_fअगरo_ping_host(dev_priv, SVGA_SYNC_GENERIC);
	mutex_unlock(&fअगरo_state->fअगरo_mutex);
पूर्ण

व्योम vmw_cmd_commit(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t bytes)
अणु
	अगर (dev_priv->cman)
		vmw_cmdbuf_commit(dev_priv->cman, bytes, शून्य, false);
	अन्यथा
		vmw_local_fअगरo_commit(dev_priv, bytes);
पूर्ण


/**
 * vmw_fअगरo_commit_flush - Commit fअगरo space and flush any buffered commands.
 *
 * @dev_priv: Poपूर्णांकer to device निजी काष्ठाure.
 * @bytes: Number of bytes to commit.
 */
व्योम vmw_cmd_commit_flush(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t bytes)
अणु
	अगर (dev_priv->cman)
		vmw_cmdbuf_commit(dev_priv->cman, bytes, शून्य, true);
	अन्यथा
		vmw_local_fअगरo_commit(dev_priv, bytes);
पूर्ण

/**
 * vmw_fअगरo_flush - Flush any buffered commands and make sure command processing
 * starts.
 *
 * @dev_priv: Poपूर्णांकer to device निजी काष्ठाure.
 * @पूर्णांकerruptible: Whether to रुको पूर्णांकerruptible अगर function needs to sleep.
 */
पूर्णांक vmw_cmd_flush(काष्ठा vmw_निजी *dev_priv, bool पूर्णांकerruptible)
अणु
	might_sleep();

	अगर (dev_priv->cman)
		वापस vmw_cmdbuf_cur_flush(dev_priv->cman, पूर्णांकerruptible);
	अन्यथा
		वापस 0;
पूर्ण

पूर्णांक vmw_cmd_send_fence(काष्ठा vmw_निजी *dev_priv, uपूर्णांक32_t *seqno)
अणु
	काष्ठा vmw_fअगरo_state *fअगरo_state = &dev_priv->fअगरo;
	काष्ठा svga_fअगरo_cmd_fence *cmd_fence;
	u32 *fm;
	पूर्णांक ret = 0;
	uपूर्णांक32_t bytes = माप(u32) + माप(*cmd_fence);

	fm = VMW_CMD_RESERVE(dev_priv, bytes);
	अगर (unlikely(fm == शून्य)) अणु
		*seqno = atomic_पढ़ो(&dev_priv->marker_seq);
		ret = -ENOMEM;
		(व्योम)vmw_fallback_रुको(dev_priv, false, true, *seqno,
					false, 3*HZ);
		जाओ out_err;
	पूर्ण

	करो अणु
		*seqno = atomic_add_वापस(1, &dev_priv->marker_seq);
	पूर्ण जबतक (*seqno == 0);

	अगर (!(fअगरo_state->capabilities & SVGA_FIFO_CAP_FENCE)) अणु

		/*
		 * Don't request hardware to send a fence. The
		 * रुकोing code in vmwgfx_irq.c will emulate this.
		 */

		vmw_cmd_commit(dev_priv, 0);
		वापस 0;
	पूर्ण

	*fm++ = SVGA_CMD_FENCE;
	cmd_fence = (काष्ठा svga_fअगरo_cmd_fence *) fm;
	cmd_fence->fence = *seqno;
	vmw_cmd_commit_flush(dev_priv, bytes);
	vmw_update_seqno(dev_priv, fअगरo_state);

out_err:
	वापस ret;
पूर्ण

/**
 * vmw_fअगरo_emit_dummy_legacy_query - emits a dummy query to the fअगरo using
 * legacy query commands.
 *
 * @dev_priv: The device निजी काष्ठाure.
 * @cid: The hardware context id used क्रम the query.
 *
 * See the vmw_fअगरo_emit_dummy_query करोcumentation.
 */
अटल पूर्णांक vmw_fअगरo_emit_dummy_legacy_query(काष्ठा vmw_निजी *dev_priv,
					    uपूर्णांक32_t cid)
अणु
	/*
	 * A query रुको without a preceding query end will
	 * actually finish all queries क्रम this cid
	 * without writing to the query result काष्ठाure.
	 */

	काष्ठा tपंचांग_buffer_object *bo = &dev_priv->dummy_query_bo->base;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdWaitForQuery body;
	पूर्ण *cmd;

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_WAIT_FOR_QUERY;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = cid;
	cmd->body.type = SVGA3D_QUERYTYPE_OCCLUSION;

	अगर (bo->mem.mem_type == TTM_PL_VRAM) अणु
		cmd->body.guestResult.gmrId = SVGA_GMR_FRAMEBUFFER;
		cmd->body.guestResult.offset = bo->mem.start << PAGE_SHIFT;
	पूर्ण अन्यथा अणु
		cmd->body.guestResult.gmrId = bo->mem.start;
		cmd->body.guestResult.offset = 0;
	पूर्ण

	vmw_cmd_commit(dev_priv, माप(*cmd));

	वापस 0;
पूर्ण

/**
 * vmw_fअगरo_emit_dummy_gb_query - emits a dummy query to the fअगरo using
 * guest-backed resource query commands.
 *
 * @dev_priv: The device निजी काष्ठाure.
 * @cid: The hardware context id used क्रम the query.
 *
 * See the vmw_fअगरo_emit_dummy_query करोcumentation.
 */
अटल पूर्णांक vmw_fअगरo_emit_dummy_gb_query(काष्ठा vmw_निजी *dev_priv,
					uपूर्णांक32_t cid)
अणु
	/*
	 * A query रुको without a preceding query end will
	 * actually finish all queries क्रम this cid
	 * without writing to the query result काष्ठाure.
	 */

	काष्ठा tपंचांग_buffer_object *bo = &dev_priv->dummy_query_bo->base;
	काष्ठा अणु
		SVGA3dCmdHeader header;
		SVGA3dCmdWaitForGBQuery body;
	पूर्ण *cmd;

	cmd = VMW_CMD_RESERVE(dev_priv, माप(*cmd));
	अगर (unlikely(cmd == शून्य))
		वापस -ENOMEM;

	cmd->header.id = SVGA_3D_CMD_WAIT_FOR_GB_QUERY;
	cmd->header.size = माप(cmd->body);
	cmd->body.cid = cid;
	cmd->body.type = SVGA3D_QUERYTYPE_OCCLUSION;
	BUG_ON(bo->mem.mem_type != VMW_PL_MOB);
	cmd->body.mobid = bo->mem.start;
	cmd->body.offset = 0;

	vmw_cmd_commit(dev_priv, माप(*cmd));

	वापस 0;
पूर्ण


/**
 * vmw_fअगरo_emit_dummy_gb_query - emits a dummy query to the fअगरo using
 * appropriate resource query commands.
 *
 * @dev_priv: The device निजी काष्ठाure.
 * @cid: The hardware context id used क्रम the query.
 *
 * This function is used to emit a dummy occlusion query with
 * no primitives rendered between query begin and query end.
 * It's used to provide a query barrier, in order to know that when
 * this query is finished, all preceding queries are also finished.
 *
 * A Query results काष्ठाure should have been initialized at the start
 * of the dev_priv->dummy_query_bo buffer object. And that buffer object
 * must also be either reserved or pinned when this function is called.
 *
 * Returns -ENOMEM on failure to reserve fअगरo space.
 */
पूर्णांक vmw_cmd_emit_dummy_query(काष्ठा vmw_निजी *dev_priv,
			      uपूर्णांक32_t cid)
अणु
	अगर (dev_priv->has_mob)
		वापस vmw_fअगरo_emit_dummy_gb_query(dev_priv, cid);

	वापस vmw_fअगरo_emit_dummy_legacy_query(dev_priv, cid);
पूर्ण
