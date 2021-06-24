<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2019 Intel Corporation
 *
 */

#समावेश "i915_drv.h"
#समावेश "intel_display_types.h"

#घोषणा DSB_BUF_SIZE    (2 * PAGE_SIZE)

/**
 * DOC: DSB
 *
 * A DSB (Display State Buffer) is a queue of MMIO inकाष्ठाions in the memory
 * which can be offloaded to DSB HW in Display Controller. DSB HW is a DMA
 * engine that can be programmed to करोwnload the DSB from memory.
 * It allows driver to batch submit display HW programming. This helps to
 * reduce loading समय and CPU activity, thereby making the context चयन
 * faster. DSB Support added from Gen12 Intel graphics based platक्रमm.
 *
 * DSB's can access only the pipe, plane, and transcoder Data Island Packet
 * रेजिस्टरs.
 *
 * DSB HW can support only रेजिस्टर ग_लिखोs (both indexed and direct MMIO
 * ग_लिखोs). There are no रेजिस्टरs पढ़ोs possible with DSB HW engine.
 */

/* DSB opcodes. */
#घोषणा DSB_OPCODE_SHIFT		24
#घोषणा DSB_OPCODE_MMIO_WRITE		0x1
#घोषणा DSB_OPCODE_INDEXED_WRITE	0x9
#घोषणा DSB_BYTE_EN			0xF
#घोषणा DSB_BYTE_EN_SHIFT		20
#घोषणा DSB_REG_VALUE_MASK		0xfffff

अटल bool is_dsb_busy(काष्ठा drm_i915_निजी *i915, क्रमागत pipe pipe,
			क्रमागत dsb_id id)
अणु
	वापस DSB_STATUS & पूर्णांकel_de_पढ़ो(i915, DSB_CTRL(pipe, id));
पूर्ण

अटल bool पूर्णांकel_dsb_enable_engine(काष्ठा drm_i915_निजी *i915,
				    क्रमागत pipe pipe, क्रमागत dsb_id id)
अणु
	u32 dsb_ctrl;

	dsb_ctrl = पूर्णांकel_de_पढ़ो(i915, DSB_CTRL(pipe, id));
	अगर (DSB_STATUS & dsb_ctrl) अणु
		drm_dbg_kms(&i915->drm, "DSB engine is busy.\n");
		वापस false;
	पूर्ण

	dsb_ctrl |= DSB_ENABLE;
	पूर्णांकel_de_ग_लिखो(i915, DSB_CTRL(pipe, id), dsb_ctrl);

	पूर्णांकel_de_posting_पढ़ो(i915, DSB_CTRL(pipe, id));
	वापस true;
पूर्ण

अटल bool पूर्णांकel_dsb_disable_engine(काष्ठा drm_i915_निजी *i915,
				     क्रमागत pipe pipe, क्रमागत dsb_id id)
अणु
	u32 dsb_ctrl;

	dsb_ctrl = पूर्णांकel_de_पढ़ो(i915, DSB_CTRL(pipe, id));
	अगर (DSB_STATUS & dsb_ctrl) अणु
		drm_dbg_kms(&i915->drm, "DSB engine is busy.\n");
		वापस false;
	पूर्ण

	dsb_ctrl &= ~DSB_ENABLE;
	पूर्णांकel_de_ग_लिखो(i915, DSB_CTRL(pipe, id), dsb_ctrl);

	पूर्णांकel_de_posting_पढ़ो(i915, DSB_CTRL(pipe, id));
	वापस true;
पूर्ण

/**
 * पूर्णांकel_dsb_indexed_reg_ग_लिखो() -Write to the DSB context क्रम स्वतः
 * increment रेजिस्टर.
 * @crtc_state: पूर्णांकel_crtc_state काष्ठाure
 * @reg: रेजिस्टर address.
 * @val: value.
 *
 * This function is used क्रम writing रेजिस्टर-value pair in command
 * buffer of DSB क्रम स्वतः-increment रेजिस्टर. During command buffer overflow,
 * a warning is thrown and rest all erroneous condition रेजिस्टर programming
 * is करोne through mmio ग_लिखो.
 */

व्योम पूर्णांकel_dsb_indexed_reg_ग_लिखो(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
				 i915_reg_t reg, u32 val)
अणु
	काष्ठा पूर्णांकel_dsb *dsb = crtc_state->dsb;
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	u32 *buf;
	u32 reg_val;

	अगर (!dsb) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
		वापस;
	पूर्ण
	buf = dsb->cmd_buf;
	अगर (drm_WARN_ON(&dev_priv->drm, dsb->मुक्त_pos >= DSB_BUF_SIZE)) अणु
		drm_dbg_kms(&dev_priv->drm, "DSB buffer overflow\n");
		वापस;
	पूर्ण

	/*
	 * For example the buffer will look like below क्रम 3 dwords क्रम स्वतः
	 * increment रेजिस्टर:
	 * +--------------------------------------------------------+
	 * | size = 3 | offset &| value1 | value2 | value3 | zero   |
	 * |          | opcode  |        |        |        |        |
	 * +--------------------------------------------------------+
	 * +          +         +        +        +        +        +
	 * 0          4         8        12       16       20       24
	 * Byte
	 *
	 * As every inकाष्ठाion is 8 byte aligned the index of dsb inकाष्ठाion
	 * will start always from even number जबतक dealing with u32 array. If
	 * we are writing odd no of dwords, Zeros will be added in the end क्रम
	 * padding.
	 */
	reg_val = buf[dsb->ins_start_offset + 1] & DSB_REG_VALUE_MASK;
	अगर (reg_val != i915_mmio_reg_offset(reg)) अणु
		/* Every inकाष्ठाion should be 8 byte aligned. */
		dsb->मुक्त_pos = ALIGN(dsb->मुक्त_pos, 2);

		dsb->ins_start_offset = dsb->मुक्त_pos;

		/* Update the size. */
		buf[dsb->मुक्त_pos++] = 1;

		/* Update the opcode and reg. */
		buf[dsb->मुक्त_pos++] = (DSB_OPCODE_INDEXED_WRITE  <<
					DSB_OPCODE_SHIFT) |
					i915_mmio_reg_offset(reg);

		/* Update the value. */
		buf[dsb->मुक्त_pos++] = val;
	पूर्ण अन्यथा अणु
		/* Update the new value. */
		buf[dsb->मुक्त_pos++] = val;

		/* Update the size. */
		buf[dsb->ins_start_offset]++;
	पूर्ण

	/* अगर number of data words is odd, then the last dword should be 0.*/
	अगर (dsb->मुक्त_pos & 0x1)
		buf[dsb->मुक्त_pos] = 0;
पूर्ण

/**
 * पूर्णांकel_dsb_reg_ग_लिखो() -Write to the DSB context क्रम normal
 * रेजिस्टर.
 * @crtc_state: पूर्णांकel_crtc_state काष्ठाure
 * @reg: रेजिस्टर address.
 * @val: value.
 *
 * This function is used क्रम writing रेजिस्टर-value pair in command
 * buffer of DSB. During command buffer overflow, a warning  is thrown
 * and rest all erroneous condition रेजिस्टर programming is करोne
 * through mmio ग_लिखो.
 */
व्योम पूर्णांकel_dsb_reg_ग_लिखो(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state,
			 i915_reg_t reg, u32 val)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_dsb *dsb;
	u32 *buf;

	dsb = crtc_state->dsb;
	अगर (!dsb) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, reg, val);
		वापस;
	पूर्ण

	buf = dsb->cmd_buf;
	अगर (drm_WARN_ON(&dev_priv->drm, dsb->मुक्त_pos >= DSB_BUF_SIZE)) अणु
		drm_dbg_kms(&dev_priv->drm, "DSB buffer overflow\n");
		वापस;
	पूर्ण

	dsb->ins_start_offset = dsb->मुक्त_pos;
	buf[dsb->मुक्त_pos++] = val;
	buf[dsb->मुक्त_pos++] = (DSB_OPCODE_MMIO_WRITE  << DSB_OPCODE_SHIFT) |
			       (DSB_BYTE_EN << DSB_BYTE_EN_SHIFT) |
			       i915_mmio_reg_offset(reg);
पूर्ण

/**
 * पूर्णांकel_dsb_commit() - Trigger workload execution of DSB.
 * @crtc_state: पूर्णांकel_crtc_state काष्ठाure
 *
 * This function is used to करो actual ग_लिखो to hardware using DSB.
 * On errors, fall back to MMIO. Also this function help to reset the context.
 */
व्योम पूर्णांकel_dsb_commit(स्थिर काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_dsb *dsb = crtc_state->dsb;
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_device *dev = crtc->base.dev;
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत pipe pipe = crtc->pipe;
	u32 tail;

	अगर (!(dsb && dsb->मुक्त_pos))
		वापस;

	अगर (!पूर्णांकel_dsb_enable_engine(dev_priv, pipe, dsb->id))
		जाओ reset;

	अगर (is_dsb_busy(dev_priv, pipe, dsb->id)) अणु
		drm_err(&dev_priv->drm,
			"HEAD_PTR write failed - dsb engine is busy.\n");
		जाओ reset;
	पूर्ण
	पूर्णांकel_de_ग_लिखो(dev_priv, DSB_HEAD(pipe, dsb->id),
		       i915_ggtt_offset(dsb->vma));

	tail = ALIGN(dsb->मुक्त_pos * 4, CACHELINE_BYTES);
	अगर (tail > dsb->मुक्त_pos * 4)
		स_रखो(&dsb->cmd_buf[dsb->मुक्त_pos], 0,
		       (tail - dsb->मुक्त_pos * 4));

	अगर (is_dsb_busy(dev_priv, pipe, dsb->id)) अणु
		drm_err(&dev_priv->drm,
			"TAIL_PTR write failed - dsb engine is busy.\n");
		जाओ reset;
	पूर्ण
	drm_dbg_kms(&dev_priv->drm,
		    "DSB execution started - head 0x%x, tail 0x%x\n",
		    i915_ggtt_offset(dsb->vma), tail);
	पूर्णांकel_de_ग_लिखो(dev_priv, DSB_TAIL(pipe, dsb->id),
		       i915_ggtt_offset(dsb->vma) + tail);
	अगर (रुको_क्रम(!is_dsb_busy(dev_priv, pipe, dsb->id), 1)) अणु
		drm_err(&dev_priv->drm,
			"Timed out waiting for DSB workload completion.\n");
		जाओ reset;
	पूर्ण

reset:
	dsb->मुक्त_pos = 0;
	dsb->ins_start_offset = 0;
	पूर्णांकel_dsb_disable_engine(dev_priv, pipe, dsb->id);
पूर्ण

/**
 * पूर्णांकel_dsb_prepare() - Allocate, pin and map the DSB command buffer.
 * @crtc_state: पूर्णांकel_crtc_state काष्ठाure to prepare associated dsb instance.
 *
 * This function prepare the command buffer which is used to store dsb
 * inकाष्ठाions with data.
 */
व्योम पूर्णांकel_dsb_prepare(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = to_पूर्णांकel_crtc(crtc_state->uapi.crtc);
	काष्ठा drm_i915_निजी *i915 = to_i915(crtc->base.dev);
	काष्ठा पूर्णांकel_dsb *dsb;
	काष्ठा drm_i915_gem_object *obj;
	काष्ठा i915_vma *vma;
	u32 *buf;
	पूर्णांकel_wakeref_t wakeref;

	अगर (!HAS_DSB(i915))
		वापस;

	dsb = kदो_स्मृति(माप(*dsb), GFP_KERNEL);
	अगर (!dsb) अणु
		drm_err(&i915->drm, "DSB object creation failed\n");
		वापस;
	पूर्ण

	wakeref = पूर्णांकel_runसमय_pm_get(&i915->runसमय_pm);

	obj = i915_gem_object_create_पूर्णांकernal(i915, DSB_BUF_SIZE);
	अगर (IS_ERR(obj)) अणु
		drm_err(&i915->drm, "Gem object creation failed\n");
		kमुक्त(dsb);
		जाओ out;
	पूर्ण

	vma = i915_gem_object_ggtt_pin(obj, शून्य, 0, 0, 0);
	अगर (IS_ERR(vma)) अणु
		drm_err(&i915->drm, "Vma creation failed\n");
		i915_gem_object_put(obj);
		kमुक्त(dsb);
		जाओ out;
	पूर्ण

	buf = i915_gem_object_pin_map_unlocked(vma->obj, I915_MAP_WC);
	अगर (IS_ERR(buf)) अणु
		drm_err(&i915->drm, "Command buffer creation failed\n");
		i915_vma_unpin_and_release(&vma, I915_VMA_RELEASE_MAP);
		kमुक्त(dsb);
		जाओ out;
	पूर्ण

	dsb->id = DSB1;
	dsb->vma = vma;
	dsb->cmd_buf = buf;
	dsb->मुक्त_pos = 0;
	dsb->ins_start_offset = 0;
	crtc_state->dsb = dsb;
out:
	पूर्णांकel_runसमय_pm_put(&i915->runसमय_pm, wakeref);
पूर्ण

/**
 * पूर्णांकel_dsb_cleanup() - To cleanup DSB context.
 * @crtc_state: पूर्णांकel_crtc_state काष्ठाure to cleanup associated dsb instance.
 *
 * This function cleanup the DSB context by unpinning and releasing
 * the VMA object associated with it.
 */
व्योम पूर्णांकel_dsb_cleanup(काष्ठा पूर्णांकel_crtc_state *crtc_state)
अणु
	अगर (!crtc_state->dsb)
		वापस;

	i915_vma_unpin_and_release(&crtc_state->dsb->vma, I915_VMA_RELEASE_MAP);
	kमुक्त(crtc_state->dsb);
	crtc_state->dsb = शून्य;
पूर्ण
