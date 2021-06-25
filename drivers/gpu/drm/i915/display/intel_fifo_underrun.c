<शैली गुरु>
/*
 * Copyright तऊ 2014 Intel Corporation
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Authors:
 *    Daniel Vetter <daniel.vetter@ffwll.ch>
 *
 */

#समावेश "i915_drv.h"
#समावेश "i915_trace.h"
#समावेश "intel_display_types.h"
#समावेश "intel_fbc.h"
#समावेश "intel_fifo_underrun.h"

/**
 * DOC: fअगरo underrun handling
 *
 * The i915 driver checks क्रम display fअगरo underruns using the पूर्णांकerrupt संकेतs
 * provided by the hardware. This is enabled by शेष and fairly useful to
 * debug display issues, especially watermark settings.
 *
 * If an underrun is detected this is logged पूर्णांकo dmesg. To aव्योम flooding logs
 * and occupying the cpu underrun पूर्णांकerrupts are disabled after the first
 * occurrence until the next modeset on a given pipe.
 *
 * Note that underrun detection on gmch platक्रमms is a bit more ugly since there
 * is no पूर्णांकerrupt (despite that the संकेतling bit is in the PIPESTAT pipe
 * पूर्णांकerrupt रेजिस्टर). Also on some other platक्रमms underrun पूर्णांकerrupts are
 * shared, which means that अगर we detect an underrun we need to disable underrun
 * reporting on all pipes.
 *
 * The code also supports underrun detection on the PCH transcoder.
 */

अटल bool ivb_can_enable_err_पूर्णांक(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_crtc *crtc;
	क्रमागत pipe pipe;

	lockdep_निश्चित_held(&dev_priv->irq_lock);

	क्रम_each_pipe(dev_priv, pipe) अणु
		crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);

		अगर (crtc->cpu_fअगरo_underrun_disabled)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool cpt_can_enable_serr_पूर्णांक(काष्ठा drm_device *dev)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	क्रमागत pipe pipe;
	काष्ठा पूर्णांकel_crtc *crtc;

	lockdep_निश्चित_held(&dev_priv->irq_lock);

	क्रम_each_pipe(dev_priv, pipe) अणु
		crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);

		अगर (crtc->pch_fअगरo_underrun_disabled)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम i9xx_check_fअगरo_underruns(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	i915_reg_t reg = PIPESTAT(crtc->pipe);
	u32 enable_mask;

	lockdep_निश्चित_held(&dev_priv->irq_lock);

	अगर ((पूर्णांकel_de_पढ़ो(dev_priv, reg) & PIPE_FIFO_UNDERRUN_STATUS) == 0)
		वापस;

	enable_mask = i915_pipestat_enable_mask(dev_priv, crtc->pipe);
	पूर्णांकel_de_ग_लिखो(dev_priv, reg, enable_mask | PIPE_FIFO_UNDERRUN_STATUS);
	पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);

	trace_पूर्णांकel_cpu_fअगरo_underrun(dev_priv, crtc->pipe);
	drm_err(&dev_priv->drm, "pipe %c underrun\n", pipe_name(crtc->pipe));
पूर्ण

अटल व्योम i9xx_set_fअगरo_underrun_reporting(काष्ठा drm_device *dev,
					     क्रमागत pipe pipe,
					     bool enable, bool old)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	i915_reg_t reg = PIPESTAT(pipe);

	lockdep_निश्चित_held(&dev_priv->irq_lock);

	अगर (enable) अणु
		u32 enable_mask = i915_pipestat_enable_mask(dev_priv, pipe);

		पूर्णांकel_de_ग_लिखो(dev_priv, reg,
			       enable_mask | PIPE_FIFO_UNDERRUN_STATUS);
		पूर्णांकel_de_posting_पढ़ो(dev_priv, reg);
	पूर्ण अन्यथा अणु
		अगर (old && पूर्णांकel_de_पढ़ो(dev_priv, reg) & PIPE_FIFO_UNDERRUN_STATUS)
			drm_err(&dev_priv->drm, "pipe %c underrun\n",
				pipe_name(pipe));
	पूर्ण
पूर्ण

अटल व्योम ilk_set_fअगरo_underrun_reporting(काष्ठा drm_device *dev,
					    क्रमागत pipe pipe, bool enable)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u32 bit = (pipe == PIPE_A) ?
		DE_PIPEA_FIFO_UNDERRUN : DE_PIPEB_FIFO_UNDERRUN;

	अगर (enable)
		ilk_enable_display_irq(dev_priv, bit);
	अन्यथा
		ilk_disable_display_irq(dev_priv, bit);
पूर्ण

अटल व्योम ivb_check_fअगरo_underruns(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pipe = crtc->pipe;
	u32 err_पूर्णांक = पूर्णांकel_de_पढ़ो(dev_priv, GEN7_ERR_INT);

	lockdep_निश्चित_held(&dev_priv->irq_lock);

	अगर ((err_पूर्णांक & ERR_INT_FIFO_UNDERRUN(pipe)) == 0)
		वापस;

	पूर्णांकel_de_ग_लिखो(dev_priv, GEN7_ERR_INT, ERR_INT_FIFO_UNDERRUN(pipe));
	पूर्णांकel_de_posting_पढ़ो(dev_priv, GEN7_ERR_INT);

	trace_पूर्णांकel_cpu_fअगरo_underrun(dev_priv, pipe);
	drm_err(&dev_priv->drm, "fifo underrun on pipe %c\n", pipe_name(pipe));
पूर्ण

अटल व्योम ivb_set_fअगरo_underrun_reporting(काष्ठा drm_device *dev,
					    क्रमागत pipe pipe, bool enable,
					    bool old)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	अगर (enable) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, GEN7_ERR_INT,
			       ERR_INT_FIFO_UNDERRUN(pipe));

		अगर (!ivb_can_enable_err_पूर्णांक(dev))
			वापस;

		ilk_enable_display_irq(dev_priv, DE_ERR_INT_IVB);
	पूर्ण अन्यथा अणु
		ilk_disable_display_irq(dev_priv, DE_ERR_INT_IVB);

		अगर (old &&
		    पूर्णांकel_de_पढ़ो(dev_priv, GEN7_ERR_INT) & ERR_INT_FIFO_UNDERRUN(pipe)) अणु
			drm_err(&dev_priv->drm,
				"uncleared fifo underrun on pipe %c\n",
				pipe_name(pipe));
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम bdw_set_fअगरo_underrun_reporting(काष्ठा drm_device *dev,
					    क्रमागत pipe pipe, bool enable)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);

	अगर (enable)
		bdw_enable_pipe_irq(dev_priv, pipe, GEN8_PIPE_FIFO_UNDERRUN);
	अन्यथा
		bdw_disable_pipe_irq(dev_priv, pipe, GEN8_PIPE_FIFO_UNDERRUN);
पूर्ण

अटल व्योम ibx_set_fअगरo_underrun_reporting(काष्ठा drm_device *dev,
					    क्रमागत pipe pch_transcoder,
					    bool enable)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	u32 bit = (pch_transcoder == PIPE_A) ?
		SDE_TRANSA_FIFO_UNDER : SDE_TRANSB_FIFO_UNDER;

	अगर (enable)
		ibx_enable_display_पूर्णांकerrupt(dev_priv, bit);
	अन्यथा
		ibx_disable_display_पूर्णांकerrupt(dev_priv, bit);
पूर्ण

अटल व्योम cpt_check_pch_fअगरo_underruns(काष्ठा पूर्णांकel_crtc *crtc)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(crtc->base.dev);
	क्रमागत pipe pch_transcoder = crtc->pipe;
	u32 serr_पूर्णांक = पूर्णांकel_de_पढ़ो(dev_priv, SERR_INT);

	lockdep_निश्चित_held(&dev_priv->irq_lock);

	अगर ((serr_पूर्णांक & SERR_INT_TRANS_FIFO_UNDERRUN(pch_transcoder)) == 0)
		वापस;

	पूर्णांकel_de_ग_लिखो(dev_priv, SERR_INT,
		       SERR_INT_TRANS_FIFO_UNDERRUN(pch_transcoder));
	पूर्णांकel_de_posting_पढ़ो(dev_priv, SERR_INT);

	trace_पूर्णांकel_pch_fअगरo_underrun(dev_priv, pch_transcoder);
	drm_err(&dev_priv->drm, "pch fifo underrun on pch transcoder %c\n",
		pipe_name(pch_transcoder));
पूर्ण

अटल व्योम cpt_set_fअगरo_underrun_reporting(काष्ठा drm_device *dev,
					    क्रमागत pipe pch_transcoder,
					    bool enable, bool old)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);

	अगर (enable) अणु
		पूर्णांकel_de_ग_लिखो(dev_priv, SERR_INT,
			       SERR_INT_TRANS_FIFO_UNDERRUN(pch_transcoder));

		अगर (!cpt_can_enable_serr_पूर्णांक(dev))
			वापस;

		ibx_enable_display_पूर्णांकerrupt(dev_priv, SDE_ERROR_CPT);
	पूर्ण अन्यथा अणु
		ibx_disable_display_पूर्णांकerrupt(dev_priv, SDE_ERROR_CPT);

		अगर (old && पूर्णांकel_de_पढ़ो(dev_priv, SERR_INT) &
		    SERR_INT_TRANS_FIFO_UNDERRUN(pch_transcoder)) अणु
			drm_err(&dev_priv->drm,
				"uncleared pch fifo underrun on pch transcoder %c\n",
				pipe_name(pch_transcoder));
		पूर्ण
	पूर्ण
पूर्ण

अटल bool __पूर्णांकel_set_cpu_fअगरo_underrun_reporting(काष्ठा drm_device *dev,
						    क्रमागत pipe pipe, bool enable)
अणु
	काष्ठा drm_i915_निजी *dev_priv = to_i915(dev);
	काष्ठा पूर्णांकel_crtc *crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);
	bool old;

	lockdep_निश्चित_held(&dev_priv->irq_lock);

	old = !crtc->cpu_fअगरo_underrun_disabled;
	crtc->cpu_fअगरo_underrun_disabled = !enable;

	अगर (HAS_GMCH(dev_priv))
		i9xx_set_fअगरo_underrun_reporting(dev, pipe, enable, old);
	अन्यथा अगर (IS_IRONLAKE(dev_priv) || IS_SANDYBRIDGE(dev_priv))
		ilk_set_fअगरo_underrun_reporting(dev, pipe, enable);
	अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 7))
		ivb_set_fअगरo_underrun_reporting(dev, pipe, enable, old);
	अन्यथा अगर (DISPLAY_VER(dev_priv) >= 8)
		bdw_set_fअगरo_underrun_reporting(dev, pipe, enable);

	वापस old;
पूर्ण

/**
 * पूर्णांकel_set_cpu_fअगरo_underrun_reporting - set cpu fअगरo underrrun reporting state
 * @dev_priv: i915 device instance
 * @pipe: (CPU) pipe to set state क्रम
 * @enable: whether underruns should be reported or not
 *
 * This function sets the fअगरo underrun state क्रम @pipe. It is used in the
 * modeset code to aव्योम false positives since on many platक्रमms underruns are
 * expected when disabling or enabling the pipe.
 *
 * Notice that on some platक्रमms disabling underrun reports क्रम one pipe
 * disables क्रम all due to shared पूर्णांकerrupts. Actual reporting is still per-pipe
 * though.
 *
 * Returns the previous state of underrun reporting.
 */
bool पूर्णांकel_set_cpu_fअगरo_underrun_reporting(काष्ठा drm_i915_निजी *dev_priv,
					   क्रमागत pipe pipe, bool enable)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;

	spin_lock_irqsave(&dev_priv->irq_lock, flags);
	ret = __पूर्णांकel_set_cpu_fअगरo_underrun_reporting(&dev_priv->drm, pipe,
						      enable);
	spin_unlock_irqrestore(&dev_priv->irq_lock, flags);

	वापस ret;
पूर्ण

/**
 * पूर्णांकel_set_pch_fअगरo_underrun_reporting - set PCH fअगरo underrun reporting state
 * @dev_priv: i915 device instance
 * @pch_transcoder: the PCH transcoder (same as pipe on IVB and older)
 * @enable: whether underruns should be reported or not
 *
 * This function makes us disable or enable PCH fअगरo underruns क्रम a specअगरic
 * PCH transcoder. Notice that on some PCHs (e.g. CPT/PPT), disabling FIFO
 * underrun reporting क्रम one transcoder may also disable all the other PCH
 * error पूर्णांकerruts क्रम the other transcoders, due to the fact that there's just
 * one पूर्णांकerrupt mask/enable bit क्रम all the transcoders.
 *
 * Returns the previous state of underrun reporting.
 */
bool पूर्णांकel_set_pch_fअगरo_underrun_reporting(काष्ठा drm_i915_निजी *dev_priv,
					   क्रमागत pipe pch_transcoder,
					   bool enable)
अणु
	काष्ठा पूर्णांकel_crtc *crtc =
		पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pch_transcoder);
	अचिन्हित दीर्घ flags;
	bool old;

	/*
	 * NOTE: Pre-LPT has a fixed cpu pipe -> pch transcoder mapping, but LPT
	 * has only one pch transcoder A that all pipes can use. To aव्योम racy
	 * pch transcoder -> pipe lookups from पूर्णांकerrupt code simply store the
	 * underrun statistics in crtc A. Since we never expose this anywhere
	 * nor use it outside of the fअगरo underrun code here using the "wrong"
	 * crtc on LPT won't cause issues.
	 */

	spin_lock_irqsave(&dev_priv->irq_lock, flags);

	old = !crtc->pch_fअगरo_underrun_disabled;
	crtc->pch_fअगरo_underrun_disabled = !enable;

	अगर (HAS_PCH_IBX(dev_priv))
		ibx_set_fअगरo_underrun_reporting(&dev_priv->drm,
						pch_transcoder,
						enable);
	अन्यथा
		cpt_set_fअगरo_underrun_reporting(&dev_priv->drm,
						pch_transcoder,
						enable, old);

	spin_unlock_irqrestore(&dev_priv->irq_lock, flags);
	वापस old;
पूर्ण

/**
 * पूर्णांकel_cpu_fअगरo_underrun_irq_handler - handle CPU fअगरo underrun पूर्णांकerrupt
 * @dev_priv: i915 device instance
 * @pipe: (CPU) pipe to set state क्रम
 *
 * This handles a CPU fअगरo underrun पूर्णांकerrupt, generating an underrun warning
 * पूर्णांकo dmesg अगर underrun reporting is enabled and then disables the underrun
 * पूर्णांकerrupt to aव्योम an irq storm.
 */
व्योम पूर्णांकel_cpu_fअगरo_underrun_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
					 क्रमागत pipe pipe)
अणु
	काष्ठा पूर्णांकel_crtc *crtc = पूर्णांकel_get_crtc_क्रम_pipe(dev_priv, pipe);

	/* We may be called too early in init, thanks BIOS! */
	अगर (crtc == शून्य)
		वापस;

	/* GMCH can't disable fअगरo underruns, filter them. */
	अगर (HAS_GMCH(dev_priv) &&
	    crtc->cpu_fअगरo_underrun_disabled)
		वापस;

	अगर (पूर्णांकel_set_cpu_fअगरo_underrun_reporting(dev_priv, pipe, false)) अणु
		trace_पूर्णांकel_cpu_fअगरo_underrun(dev_priv, pipe);
		drm_err(&dev_priv->drm, "CPU pipe %c FIFO underrun\n",
			pipe_name(pipe));
	पूर्ण

	पूर्णांकel_fbc_handle_fअगरo_underrun_irq(dev_priv);
पूर्ण

/**
 * पूर्णांकel_pch_fअगरo_underrun_irq_handler - handle PCH fअगरo underrun पूर्णांकerrupt
 * @dev_priv: i915 device instance
 * @pch_transcoder: the PCH transcoder (same as pipe on IVB and older)
 *
 * This handles a PCH fअगरo underrun पूर्णांकerrupt, generating an underrun warning
 * पूर्णांकo dmesg अगर underrun reporting is enabled and then disables the underrun
 * पूर्णांकerrupt to aव्योम an irq storm.
 */
व्योम पूर्णांकel_pch_fअगरo_underrun_irq_handler(काष्ठा drm_i915_निजी *dev_priv,
					 क्रमागत pipe pch_transcoder)
अणु
	अगर (पूर्णांकel_set_pch_fअगरo_underrun_reporting(dev_priv, pch_transcoder,
						  false)) अणु
		trace_पूर्णांकel_pch_fअगरo_underrun(dev_priv, pch_transcoder);
		drm_err(&dev_priv->drm, "PCH transcoder %c FIFO underrun\n",
			pipe_name(pch_transcoder));
	पूर्ण
पूर्ण

/**
 * पूर्णांकel_check_cpu_fअगरo_underruns - check क्रम CPU fअगरo underruns immediately
 * @dev_priv: i915 device instance
 *
 * Check क्रम CPU fअगरo underruns immediately. Useful on IVB/HSW where the shared
 * error पूर्णांकerrupt may have been disabled, and so CPU fअगरo underruns won't
 * necessarily उठाओ an पूर्णांकerrupt, and on GMCH platक्रमms where underruns never
 * उठाओ an पूर्णांकerrupt.
 */
व्योम पूर्णांकel_check_cpu_fअगरo_underruns(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_crtc *crtc;

	spin_lock_irq(&dev_priv->irq_lock);

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		अगर (crtc->cpu_fअगरo_underrun_disabled)
			जारी;

		अगर (HAS_GMCH(dev_priv))
			i9xx_check_fअगरo_underruns(crtc);
		अन्यथा अगर (IS_DISPLAY_VER(dev_priv, 7))
			ivb_check_fअगरo_underruns(crtc);
	पूर्ण

	spin_unlock_irq(&dev_priv->irq_lock);
पूर्ण

/**
 * पूर्णांकel_check_pch_fअगरo_underruns - check क्रम PCH fअगरo underruns immediately
 * @dev_priv: i915 device instance
 *
 * Check क्रम PCH fअगरo underruns immediately. Useful on CPT/PPT where the shared
 * error पूर्णांकerrupt may have been disabled, and so PCH fअगरo underruns won't
 * necessarily उठाओ an पूर्णांकerrupt.
 */
व्योम पूर्णांकel_check_pch_fअगरo_underruns(काष्ठा drm_i915_निजी *dev_priv)
अणु
	काष्ठा पूर्णांकel_crtc *crtc;

	spin_lock_irq(&dev_priv->irq_lock);

	क्रम_each_पूर्णांकel_crtc(&dev_priv->drm, crtc) अणु
		अगर (crtc->pch_fअगरo_underrun_disabled)
			जारी;

		अगर (HAS_PCH_CPT(dev_priv))
			cpt_check_pch_fअगरo_underruns(crtc);
	पूर्ण

	spin_unlock_irq(&dev_priv->irq_lock);
पूर्ण
