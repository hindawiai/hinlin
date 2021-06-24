<शैली गुरु>
/*
 * drm_irq.c IRQ and vblank support
 *
 * \चuthor Rickard E. (Rik) Faith <faith@valinux.com>
 * \चuthor Gareth Hughes <gareth@valinux.com>
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
 * VA LINUX SYSTEMS AND/OR ITS SUPPLIERS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#समावेश <linux/export.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/moduleparam.h>

#समावेश <drm/drm_crtc.h>
#समावेश <drm/drm_drv.h>
#समावेश <drm/drm_framebuffer.h>
#समावेश <drm/drm_managed.h>
#समावेश <drm/drm_modeset_helper_vtables.h>
#समावेश <drm/drm_prपूर्णांक.h>
#समावेश <drm/drm_vblank.h>

#समावेश "drm_internal.h"
#समावेश "drm_trace.h"

/**
 * DOC: vblank handling
 *
 * From the computer's perspective, every समय the monitor displays
 * a new frame the scanout engine has "scanned out" the display image
 * from top to bottom, one row of pixels at a समय. The current row
 * of pixels is referred to as the current scanline.
 *
 * In addition to the display's visible area, there's usually a couple of
 * extra scanlines which aren't actually displayed on the screen.
 * These extra scanlines करोn't contain image data and are occasionally used
 * क्रम features like audio and infoframes. The region made up of these
 * scanlines is referred to as the vertical blanking region, or vblank क्रम
 * लघु.
 *
 * For historical reference, the vertical blanking period was deचिन्हित to
 * give the electron gun (on CRTs) enough समय to move back to the top of
 * the screen to start scanning out the next frame. Similar क्रम horizontal
 * blanking periods. They were deचिन्हित to give the electron gun enough
 * समय to move back to the other side of the screen to start scanning the
 * next scanline.
 *
 * ::
 *
 *
 *    physical ै   ैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैट
 *    top of      |                                        |
 *    display     |                                        |
 *                |               New frame                |
 *                |                                        |
 *                |ैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैै|
 *                |~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~| ै Scanline,
 *                |ैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैैै|   updates the
 *                |                                        |   frame as it
 *                |                                        |   travels करोwn
 *                |                                        |   ("scan out")
 *                |               Old frame                |
 *                |                                        |
 *                |                                        |
 *                |                                        |
 *                |                                        |   physical
 *                |                                        |   bottom of
 *    vertical    |ैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैट| ै display
 *    blanking    ैxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxै
 *    region   ै  ैxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxै
 *                ैxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxै
 *    start of ै   ैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैटैट
 *    new frame
 *
 * "Physical top of display" is the reference poपूर्णांक क्रम the high-precision/
 * corrected बारtamp.
 *
 * On a lot of display hardware, programming needs to take effect during the
 * vertical blanking period so that settings like gamma, the image buffer
 * buffer to be scanned out, etc. can safely be changed without showing
 * any visual artअगरacts on the screen. In some unक्रमgiving hardware, some of
 * this programming has to both start and end in the same vblank. To help
 * with the timing of the hardware programming, an पूर्णांकerrupt is usually
 * available to notअगरy the driver when it can start the updating of रेजिस्टरs.
 * The पूर्णांकerrupt is in this context named the vblank पूर्णांकerrupt.
 *
 * The vblank पूर्णांकerrupt may be fired at dअगरferent poपूर्णांकs depending on the
 * hardware. Some hardware implementations will fire the पूर्णांकerrupt when the
 * new frame start, other implementations will fire the पूर्णांकerrupt at dअगरferent
 * poपूर्णांकs in समय.
 *
 * Vertical blanking plays a major role in graphics rendering. To achieve
 * tear-मुक्त display, users must synchronize page flips and/or rendering to
 * vertical blanking. The DRM API offers ioctls to perक्रमm page flips
 * synchronized to vertical blanking and रुको क्रम vertical blanking.
 *
 * The DRM core handles most of the vertical blanking management logic, which
 * involves filtering out spurious पूर्णांकerrupts, keeping race-मुक्त blanking
 * counters, coping with counter wrap-around and resets and keeping use counts.
 * It relies on the driver to generate vertical blanking पूर्णांकerrupts and
 * optionally provide a hardware vertical blanking counter.
 *
 * Drivers must initialize the vertical blanking handling core with a call to
 * drm_vblank_init(). Minimally, a driver needs to implement
 * &drm_crtc_funcs.enable_vblank and &drm_crtc_funcs.disable_vblank plus call
 * drm_crtc_handle_vblank() in its vblank पूर्णांकerrupt handler क्रम working vblank
 * support.
 *
 * Vertical blanking पूर्णांकerrupts can be enabled by the DRM core or by drivers
 * themselves (क्रम instance to handle page flipping operations).  The DRM core
 * मुख्यtains a vertical blanking use count to ensure that the पूर्णांकerrupts are not
 * disabled जबतक a user still needs them. To increment the use count, drivers
 * call drm_crtc_vblank_get() and release the vblank reference again with
 * drm_crtc_vblank_put(). In between these two calls vblank पूर्णांकerrupts are
 * guaranteed to be enabled.
 *
 * On many hardware disabling the vblank पूर्णांकerrupt cannot be करोne in a race-मुक्त
 * manner, see &drm_driver.vblank_disable_immediate and
 * &drm_driver.max_vblank_count. In that हाल the vblank core only disables the
 * vblanks after a समयr has expired, which can be configured through the
 * ``vblankoffdelay`` module parameter.
 *
 * Drivers क्रम hardware without support क्रम vertical-blanking पूर्णांकerrupts
 * must not call drm_vblank_init(). For such drivers, atomic helpers will
 * स्वतःmatically generate fake vblank events as part of the display update.
 * This functionality also can be controlled by the driver by enabling and
 * disabling काष्ठा drm_crtc_state.no_vblank.
 */

/* Retry बारtamp calculation up to 3 बार to satisfy
 * drm_बारtamp_precision beक्रमe giving up.
 */
#घोषणा DRM_TIMESTAMP_MAXRETRIES 3

/* Threshold in nanoseconds क्रम detection of redundant
 * vblank irq in drm_handle_vblank(). 1 msec should be ok.
 */
#घोषणा DRM_REDUNDANT_VBLIRQ_THRESH_NS 1000000

अटल bool
drm_get_last_vblबारtamp(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe,
			  kसमय_प्रकार *tvblank, bool in_vblank_irq);

अटल अचिन्हित पूर्णांक drm_बारtamp_precision = 20;  /* Default to 20 usecs. */

अटल पूर्णांक drm_vblank_offdelay = 5000;    /* Default to 5000 msecs. */

module_param_named(vblankoffdelay, drm_vblank_offdelay, पूर्णांक, 0600);
module_param_named(बारtamp_precision_usec, drm_बारtamp_precision, पूर्णांक, 0600);
MODULE_PARM_DESC(vblankoffdelay, "Delay until vblank irq auto-disable [msecs] (0: never disable, <0: disable immediately)");
MODULE_PARM_DESC(बारtamp_precision_usec, "Max. error on timestamps [usecs]");

अटल व्योम store_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe,
			 u32 vblank_count_inc,
			 kसमय_प्रकार t_vblank, u32 last)
अणु
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];

	निश्चित_spin_locked(&dev->vblank_समय_lock);

	vblank->last = last;

	ग_लिखो_seqlock(&vblank->seqlock);
	vblank->समय = t_vblank;
	atomic64_add(vblank_count_inc, &vblank->count);
	ग_लिखो_sequnlock(&vblank->seqlock);
पूर्ण

अटल u32 drm_max_vblank_count(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];

	वापस vblank->max_vblank_count ?: dev->max_vblank_count;
पूर्ण

/*
 * "No hw counter" fallback implementation of .get_vblank_counter() hook,
 * अगर there is no useable hardware frame counter available.
 */
अटल u32 drm_vblank_no_hw_counter(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	drm_WARN_ON_ONCE(dev, drm_max_vblank_count(dev, pipe) != 0);
	वापस 0;
पूर्ण

अटल u32 __get_vblank_counter(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	अगर (drm_core_check_feature(dev, DRIVER_MODESET)) अणु
		काष्ठा drm_crtc *crtc = drm_crtc_from_index(dev, pipe);

		अगर (drm_WARN_ON(dev, !crtc))
			वापस 0;

		अगर (crtc->funcs->get_vblank_counter)
			वापस crtc->funcs->get_vblank_counter(crtc);
	पूर्ण
#अगर_घोषित CONFIG_DRM_LEGACY
	अन्यथा अगर (dev->driver->get_vblank_counter) अणु
		वापस dev->driver->get_vblank_counter(dev, pipe);
	पूर्ण
#पूर्ण_अगर

	वापस drm_vblank_no_hw_counter(dev, pipe);
पूर्ण

/*
 * Reset the stored बारtamp क्रम the current vblank count to correspond
 * to the last vblank occurred.
 *
 * Only to be called from drm_crtc_vblank_on().
 *
 * Note: caller must hold &drm_device.vbl_lock since this पढ़ोs & ग_लिखोs
 * device vblank fields.
 */
अटल व्योम drm_reset_vblank_बारtamp(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	u32 cur_vblank;
	bool rc;
	kसमय_प्रकार t_vblank;
	पूर्णांक count = DRM_TIMESTAMP_MAXRETRIES;

	spin_lock(&dev->vblank_समय_lock);

	/*
	 * sample the current counter to aव्योम अक्रमom jumps
	 * when drm_vblank_enable() applies the dअगरf
	 */
	करो अणु
		cur_vblank = __get_vblank_counter(dev, pipe);
		rc = drm_get_last_vblबारtamp(dev, pipe, &t_vblank, false);
	पूर्ण जबतक (cur_vblank != __get_vblank_counter(dev, pipe) && --count > 0);

	/*
	 * Only reinitialize corresponding vblank बारtamp अगर high-precision query
	 * available and didn't fail. Otherwise reinitialize delayed at next vblank
	 * पूर्णांकerrupt and assign 0 क्रम now, to mark the vblankबारtamp as invalid.
	 */
	अगर (!rc)
		t_vblank = 0;

	/*
	 * +1 to make sure user will never see the same
	 * vblank counter value beक्रमe and after a modeset
	 */
	store_vblank(dev, pipe, 1, t_vblank, cur_vblank);

	spin_unlock(&dev->vblank_समय_lock);
पूर्ण

/*
 * Call back पूर्णांकo the driver to update the appropriate vblank counter
 * (specअगरied by @pipe).  Deal with wraparound, अगर it occurred, and
 * update the last पढ़ो value so we can deal with wraparound on the next
 * call अगर necessary.
 *
 * Only necessary when going from off->on, to account क्रम frames we
 * didn't get an पूर्णांकerrupt क्रम.
 *
 * Note: caller must hold &drm_device.vbl_lock since this पढ़ोs & ग_लिखोs
 * device vblank fields.
 */
अटल व्योम drm_update_vblank_count(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe,
				    bool in_vblank_irq)
अणु
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];
	u32 cur_vblank, dअगरf;
	bool rc;
	kसमय_प्रकार t_vblank;
	पूर्णांक count = DRM_TIMESTAMP_MAXRETRIES;
	पूर्णांक framedur_ns = vblank->framedur_ns;
	u32 max_vblank_count = drm_max_vblank_count(dev, pipe);

	/*
	 * Interrupts were disabled prior to this call, so deal with counter
	 * wrap अगर needed.
	 * NOTE!  It's possible we lost a full dev->max_vblank_count + 1 events
	 * here अगर the रेजिस्टर is small or we had vblank पूर्णांकerrupts off क्रम
	 * a दीर्घ समय.
	 *
	 * We repeat the hardware vblank counter & बारtamp query until
	 * we get consistent results. This to prevent races between gpu
	 * updating its hardware counter जबतक we are retrieving the
	 * corresponding vblank बारtamp.
	 */
	करो अणु
		cur_vblank = __get_vblank_counter(dev, pipe);
		rc = drm_get_last_vblबारtamp(dev, pipe, &t_vblank, in_vblank_irq);
	पूर्ण जबतक (cur_vblank != __get_vblank_counter(dev, pipe) && --count > 0);

	अगर (max_vblank_count) अणु
		/* trust the hw counter when it's around */
		dअगरf = (cur_vblank - vblank->last) & max_vblank_count;
	पूर्ण अन्यथा अगर (rc && framedur_ns) अणु
		u64 dअगरf_ns = kसमय_प्रकारo_ns(kसमय_sub(t_vblank, vblank->समय));

		/*
		 * Figure out how many vblanks we've missed based
		 * on the dअगरference in the बारtamps and the
		 * frame/field duration.
		 */

		drm_dbg_vbl(dev, "crtc %u: Calculating number of vblanks."
			    " diff_ns = %lld, framedur_ns = %d)\n",
			    pipe, (दीर्घ दीर्घ)dअगरf_ns, framedur_ns);

		dअगरf = DIV_ROUND_CLOSEST_ULL(dअगरf_ns, framedur_ns);

		अगर (dअगरf == 0 && in_vblank_irq)
			drm_dbg_vbl(dev, "crtc %u: Redundant vblirq ignored\n",
				    pipe);
	पूर्ण अन्यथा अणु
		/* some kind of शेष क्रम drivers w/o accurate vbl बारtamping */
		dअगरf = in_vblank_irq ? 1 : 0;
	पूर्ण

	/*
	 * Within a drm_vblank_pre_modeset - drm_vblank_post_modeset
	 * पूर्णांकerval? If so then vblank irqs keep running and it will likely
	 * happen that the hardware vblank counter is not trustworthy as it
	 * might reset at some poपूर्णांक in that पूर्णांकerval and vblank बारtamps
	 * are not trustworthy either in that पूर्णांकerval. Iow. this can result
	 * in a bogus dअगरf >> 1 which must be aव्योमed as it would cause
	 * अक्रमom large क्रमward jumps of the software vblank counter.
	 */
	अगर (dअगरf > 1 && (vblank->inmodeset & 0x2)) अणु
		drm_dbg_vbl(dev,
			    "clamping vblank bump to 1 on crtc %u: diffr=%u"
			    " due to pre-modeset.\n", pipe, dअगरf);
		dअगरf = 1;
	पूर्ण

	drm_dbg_vbl(dev, "updating vblank count on crtc %u:"
		    " current=%llu, diff=%u, hw=%u hw_last=%u\n",
		    pipe, (अचिन्हित दीर्घ दीर्घ)atomic64_पढ़ो(&vblank->count),
		    dअगरf, cur_vblank, vblank->last);

	अगर (dअगरf == 0) अणु
		drm_WARN_ON_ONCE(dev, cur_vblank != vblank->last);
		वापस;
	पूर्ण

	/*
	 * Only reinitialize corresponding vblank बारtamp अगर high-precision query
	 * available and didn't fail, or we were called from the vblank पूर्णांकerrupt.
	 * Otherwise reinitialize delayed at next vblank पूर्णांकerrupt and assign 0
	 * क्रम now, to mark the vblankबारtamp as invalid.
	 */
	अगर (!rc && !in_vblank_irq)
		t_vblank = 0;

	store_vblank(dev, pipe, dअगरf, t_vblank, cur_vblank);
पूर्ण

u64 drm_vblank_count(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];
	u64 count;

	अगर (drm_WARN_ON(dev, pipe >= dev->num_crtcs))
		वापस 0;

	count = atomic64_पढ़ो(&vblank->count);

	/*
	 * This पढ़ो barrier corresponds to the implicit ग_लिखो barrier of the
	 * ग_लिखो seqlock in store_vblank(). Note that this is the only place
	 * where we need an explicit barrier, since all other access goes
	 * through drm_vblank_count_and_समय(), which alपढ़ोy has the required
	 * पढ़ो barrier curtesy of the पढ़ो seqlock.
	 */
	smp_rmb();

	वापस count;
पूर्ण

/**
 * drm_crtc_accurate_vblank_count - retrieve the master vblank counter
 * @crtc: which counter to retrieve
 *
 * This function is similar to drm_crtc_vblank_count() but this function
 * पूर्णांकerpolates to handle a race with vblank पूर्णांकerrupts using the high precision
 * बारtamping support.
 *
 * This is mostly useful क्रम hardware that can obtain the scanout position, but
 * करोesn't have a hardware frame counter.
 */
u64 drm_crtc_accurate_vblank_count(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = drm_crtc_index(crtc);
	u64 vblank;
	अचिन्हित दीर्घ flags;

	drm_WARN_ONCE(dev, drm_debug_enabled(DRM_UT_VBL) &&
		      !crtc->funcs->get_vblank_बारtamp,
		      "This function requires support for accurate vblank timestamps.");

	spin_lock_irqsave(&dev->vblank_समय_lock, flags);

	drm_update_vblank_count(dev, pipe, false);
	vblank = drm_vblank_count(dev, pipe);

	spin_unlock_irqrestore(&dev->vblank_समय_lock, flags);

	वापस vblank;
पूर्ण
EXPORT_SYMBOL(drm_crtc_accurate_vblank_count);

अटल व्योम __disable_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	अगर (drm_core_check_feature(dev, DRIVER_MODESET)) अणु
		काष्ठा drm_crtc *crtc = drm_crtc_from_index(dev, pipe);

		अगर (drm_WARN_ON(dev, !crtc))
			वापस;

		अगर (crtc->funcs->disable_vblank)
			crtc->funcs->disable_vblank(crtc);
	पूर्ण
#अगर_घोषित CONFIG_DRM_LEGACY
	अन्यथा अणु
		dev->driver->disable_vblank(dev, pipe);
	पूर्ण
#पूर्ण_अगर
पूर्ण

/*
 * Disable vblank irq's on crtc, make sure that last vblank count
 * of hardware and corresponding consistent software vblank counter
 * are preserved, even अगर there are any spurious vblank irq's after
 * disable.
 */
व्योम drm_vblank_disable_and_save(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];
	अचिन्हित दीर्घ irqflags;

	निश्चित_spin_locked(&dev->vbl_lock);

	/* Prevent vblank irq processing जबतक disabling vblank irqs,
	 * so no updates of बारtamps or count can happen after we've
	 * disabled. Needed to prevent races in हाल of delayed irq's.
	 */
	spin_lock_irqsave(&dev->vblank_समय_lock, irqflags);

	/*
	 * Update vblank count and disable vblank पूर्णांकerrupts only अगर the
	 * पूर्णांकerrupts were enabled. This aव्योमs calling the ->disable_vblank()
	 * operation in atomic context with the hardware potentially runसमय
	 * suspended.
	 */
	अगर (!vblank->enabled)
		जाओ out;

	/*
	 * Update the count and बारtamp to मुख्यtain the
	 * appearance that the counter has been ticking all aदीर्घ until
	 * this समय. This makes the count account क्रम the entire समय
	 * between drm_crtc_vblank_on() and drm_crtc_vblank_off().
	 */
	drm_update_vblank_count(dev, pipe, false);
	__disable_vblank(dev, pipe);
	vblank->enabled = false;

out:
	spin_unlock_irqrestore(&dev->vblank_समय_lock, irqflags);
पूर्ण

अटल व्योम vblank_disable_fn(काष्ठा समयr_list *t)
अणु
	काष्ठा drm_vblank_crtc *vblank = from_समयr(vblank, t, disable_समयr);
	काष्ठा drm_device *dev = vblank->dev;
	अचिन्हित पूर्णांक pipe = vblank->pipe;
	अचिन्हित दीर्घ irqflags;

	spin_lock_irqsave(&dev->vbl_lock, irqflags);
	अगर (atomic_पढ़ो(&vblank->refcount) == 0 && vblank->enabled) अणु
		drm_dbg_core(dev, "disabling vblank on crtc %u\n", pipe);
		drm_vblank_disable_and_save(dev, pipe);
	पूर्ण
	spin_unlock_irqrestore(&dev->vbl_lock, irqflags);
पूर्ण

अटल व्योम drm_vblank_init_release(काष्ठा drm_device *dev, व्योम *ptr)
अणु
	काष्ठा drm_vblank_crtc *vblank = ptr;

	drm_WARN_ON(dev, READ_ONCE(vblank->enabled) &&
		    drm_core_check_feature(dev, DRIVER_MODESET));

	drm_vblank_destroy_worker(vblank);
	del_समयr_sync(&vblank->disable_समयr);
पूर्ण

/**
 * drm_vblank_init - initialize vblank support
 * @dev: DRM device
 * @num_crtcs: number of CRTCs supported by @dev
 *
 * This function initializes vblank support क्रम @num_crtcs display pipelines.
 * Cleanup is handled स्वतःmatically through a cleanup function added with
 * drmm_add_action_or_reset().
 *
 * Returns:
 * Zero on success or a negative error code on failure.
 */
पूर्णांक drm_vblank_init(काष्ठा drm_device *dev, अचिन्हित पूर्णांक num_crtcs)
अणु
	पूर्णांक ret;
	अचिन्हित पूर्णांक i;

	spin_lock_init(&dev->vbl_lock);
	spin_lock_init(&dev->vblank_समय_lock);

	dev->vblank = drmm_kसुस्मृति(dev, num_crtcs, माप(*dev->vblank), GFP_KERNEL);
	अगर (!dev->vblank)
		वापस -ENOMEM;

	dev->num_crtcs = num_crtcs;

	क्रम (i = 0; i < num_crtcs; i++) अणु
		काष्ठा drm_vblank_crtc *vblank = &dev->vblank[i];

		vblank->dev = dev;
		vblank->pipe = i;
		init_रुकोqueue_head(&vblank->queue);
		समयr_setup(&vblank->disable_समयr, vblank_disable_fn, 0);
		seqlock_init(&vblank->seqlock);

		ret = drmm_add_action_or_reset(dev, drm_vblank_init_release,
					       vblank);
		अगर (ret)
			वापस ret;

		ret = drm_vblank_worker_init(vblank);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(drm_vblank_init);

/**
 * drm_dev_has_vblank - test अगर vblanking has been initialized क्रम
 *                      a device
 * @dev: the device
 *
 * Drivers may call this function to test अगर vblank support is
 * initialized क्रम a device. For most hardware this means that vblanking
 * can also be enabled.
 *
 * Atomic helpers use this function to initialize
 * &drm_crtc_state.no_vblank. See also drm_atomic_helper_check_modeset().
 *
 * Returns:
 * True अगर vblanking has been initialized क्रम the given device, false
 * otherwise.
 */
bool drm_dev_has_vblank(स्थिर काष्ठा drm_device *dev)
अणु
	वापस dev->num_crtcs != 0;
पूर्ण
EXPORT_SYMBOL(drm_dev_has_vblank);

/**
 * drm_crtc_vblank_रुकोqueue - get vblank रुकोqueue क्रम the CRTC
 * @crtc: which CRTC's vblank रुकोqueue to retrieve
 *
 * This function वापसs a poपूर्णांकer to the vblank रुकोqueue क्रम the CRTC.
 * Drivers can use this to implement vblank रुकोs using रुको_event() and related
 * functions.
 */
रुको_queue_head_t *drm_crtc_vblank_रुकोqueue(काष्ठा drm_crtc *crtc)
अणु
	वापस &crtc->dev->vblank[drm_crtc_index(crtc)].queue;
पूर्ण
EXPORT_SYMBOL(drm_crtc_vblank_रुकोqueue);


/**
 * drm_calc_बारtamping_स्थिरants - calculate vblank बारtamp स्थिरants
 * @crtc: drm_crtc whose बारtamp स्थिरants should be updated.
 * @mode: display mode containing the scanout timings
 *
 * Calculate and store various स्थिरants which are later needed by vblank and
 * swap-completion बारtamping, e.g, by
 * drm_crtc_vblank_helper_get_vblank_बारtamp(). They are derived from
 * CRTC's true scanout timing, so they take things like panel scaling or
 * other adjusपंचांगents पूर्णांकo account.
 */
व्योम drm_calc_बारtamping_स्थिरants(काष्ठा drm_crtc *crtc,
				     स्थिर काष्ठा drm_display_mode *mode)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = drm_crtc_index(crtc);
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];
	पूर्णांक linedur_ns = 0, framedur_ns = 0;
	पूर्णांक करोtघड़ी = mode->crtc_घड़ी;

	अगर (!drm_dev_has_vblank(dev))
		वापस;

	अगर (drm_WARN_ON(dev, pipe >= dev->num_crtcs))
		वापस;

	/* Valid करोtघड़ी? */
	अगर (करोtघड़ी > 0) अणु
		पूर्णांक frame_size = mode->crtc_htotal * mode->crtc_vtotal;

		/*
		 * Convert scanline length in pixels and video
		 * करोt घड़ी to line duration and frame duration
		 * in nanoseconds:
		 */
		linedur_ns  = भाग_u64((u64) mode->crtc_htotal * 1000000, करोtघड़ी);
		framedur_ns = भाग_u64((u64) frame_size * 1000000, करोtघड़ी);

		/*
		 * Fields of पूर्णांकerlaced scanout modes are only half a frame duration.
		 */
		अगर (mode->flags & DRM_MODE_FLAG_INTERLACE)
			framedur_ns /= 2;
	पूर्ण अन्यथा अणु
		drm_err(dev, "crtc %u: Can't calculate constants, dotclock = 0!\n",
			crtc->base.id);
	पूर्ण

	vblank->linedur_ns  = linedur_ns;
	vblank->framedur_ns = framedur_ns;
	vblank->hwmode = *mode;

	drm_dbg_core(dev,
		     "crtc %u: hwmode: htotal %d, vtotal %d, vdisplay %d\n",
		     crtc->base.id, mode->crtc_htotal,
		     mode->crtc_vtotal, mode->crtc_vdisplay);
	drm_dbg_core(dev, "crtc %u: clock %d kHz framedur %d linedur %d\n",
		     crtc->base.id, करोtघड़ी, framedur_ns, linedur_ns);
पूर्ण
EXPORT_SYMBOL(drm_calc_बारtamping_स्थिरants);

/**
 * drm_crtc_vblank_helper_get_vblank_बारtamp_पूर्णांकernal - precise vblank
 *                                                        बारtamp helper
 * @crtc: CRTC whose vblank बारtamp to retrieve
 * @max_error: Desired maximum allowable error in बारtamps (nanosecs)
 *             On वापस contains true maximum error of बारtamp
 * @vblank_समय: Poपूर्णांकer to समय which should receive the बारtamp
 * @in_vblank_irq:
 *     True when called from drm_crtc_handle_vblank().  Some drivers
 *     need to apply some workarounds क्रम gpu-specअगरic vblank irq quirks
 *     अगर flag is set.
 * @get_scanout_position:
 *     Callback function to retrieve the scanout position. See
 *     @काष्ठा drm_crtc_helper_funcs.get_scanout_position.
 *
 * Implements calculation of exact vblank बारtamps from given drm_display_mode
 * timings and current video scanout position of a CRTC.
 *
 * The current implementation only handles standard video modes. For द्विगुन scan
 * and पूर्णांकerlaced modes the driver is supposed to adjust the hardware mode
 * (taken from &drm_crtc_state.adjusted mode क्रम atomic modeset drivers) to
 * match the scanout position reported.
 *
 * Note that atomic drivers must call drm_calc_बारtamping_स्थिरants() beक्रमe
 * enabling a CRTC. The atomic helpers alपढ़ोy take care of that in
 * drm_atomic_helper_calc_बारtamping_स्थिरants().
 *
 * Returns:
 *
 * Returns true on success, and false on failure, i.e. when no accurate
 * बारtamp could be acquired.
 */
bool
drm_crtc_vblank_helper_get_vblank_बारtamp_पूर्णांकernal(
	काष्ठा drm_crtc *crtc, पूर्णांक *max_error, kसमय_प्रकार *vblank_समय,
	bool in_vblank_irq,
	drm_vblank_get_scanout_position_func get_scanout_position)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = crtc->index;
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];
	काष्ठा बारpec64 ts_eसमय, ts_vblank_समय;
	kसमय_प्रकार sसमय, eसमय;
	bool vbl_status;
	स्थिर काष्ठा drm_display_mode *mode;
	पूर्णांक vpos, hpos, i;
	पूर्णांक delta_ns, duration_ns;

	अगर (pipe >= dev->num_crtcs) अणु
		drm_err(dev, "Invalid crtc %u\n", pipe);
		वापस false;
	पूर्ण

	/* Scanout position query not supported? Should not happen. */
	अगर (!get_scanout_position) अणु
		drm_err(dev, "Called from CRTC w/o get_scanout_position()!?\n");
		वापस false;
	पूर्ण

	अगर (drm_drv_uses_atomic_modeset(dev))
		mode = &vblank->hwmode;
	अन्यथा
		mode = &crtc->hwmode;

	/* If mode timing undefined, just वापस as no-op:
	 * Happens during initial modesetting of a crtc.
	 */
	अगर (mode->crtc_घड़ी == 0) अणु
		drm_dbg_core(dev, "crtc %u: Noop due to uninitialized mode.\n",
			     pipe);
		drm_WARN_ON_ONCE(dev, drm_drv_uses_atomic_modeset(dev));
		वापस false;
	पूर्ण

	/* Get current scanout position with प्रणाली बारtamp.
	 * Repeat query up to DRM_TIMESTAMP_MAXRETRIES बार
	 * अगर single query takes दीर्घer than max_error nanoseconds.
	 *
	 * This guarantees a tight bound on maximum error अगर
	 * code माला_लो preempted or delayed क्रम some reason.
	 */
	क्रम (i = 0; i < DRM_TIMESTAMP_MAXRETRIES; i++) अणु
		/*
		 * Get vertical and horizontal scanout position vpos, hpos,
		 * and bounding बारtamps sसमय, eसमय, pre/post query.
		 */
		vbl_status = get_scanout_position(crtc, in_vblank_irq,
						  &vpos, &hpos,
						  &sसमय, &eसमय,
						  mode);

		/* Return as no-op अगर scanout query unsupported or failed. */
		अगर (!vbl_status) अणु
			drm_dbg_core(dev,
				     "crtc %u : scanoutpos query failed.\n",
				     pipe);
			वापस false;
		पूर्ण

		/* Compute uncertaपूर्णांकy in बारtamp of scanout position query. */
		duration_ns = kसमय_प्रकारo_ns(eसमय) - kसमय_प्रकारo_ns(sसमय);

		/* Accept result with <  max_error nsecs timing uncertaपूर्णांकy. */
		अगर (duration_ns <= *max_error)
			अवरोध;
	पूर्ण

	/* Noisy प्रणाली timing? */
	अगर (i == DRM_TIMESTAMP_MAXRETRIES) अणु
		drm_dbg_core(dev,
			     "crtc %u: Noisy timestamp %d us > %d us [%d reps].\n",
			     pipe, duration_ns / 1000, *max_error / 1000, i);
	पूर्ण

	/* Return upper bound of बारtamp precision error. */
	*max_error = duration_ns;

	/* Convert scanout position पूर्णांकo elapsed समय at raw_समय query
	 * since start of scanout at first display scanline. delta_ns
	 * can be negative अगर start of scanout hasn't happened yet.
	 */
	delta_ns = भाग_s64(1000000LL * (vpos * mode->crtc_htotal + hpos),
			   mode->crtc_घड़ी);

	/* Subtract समय delta from raw बारtamp to get final
	 * vblank_समय बारtamp क्रम end of vblank.
	 */
	*vblank_समय = kसमय_sub_ns(eसमय, delta_ns);

	अगर (!drm_debug_enabled(DRM_UT_VBL))
		वापस true;

	ts_eसमय = kसमय_प्रकारo_बारpec64(eसमय);
	ts_vblank_समय = kसमय_प्रकारo_बारpec64(*vblank_समय);

	drm_dbg_vbl(dev,
		    "crtc %u : v p(%d,%d)@ %lld.%06ld -> %lld.%06ld [e %d us, %d rep]\n",
		    pipe, hpos, vpos,
		    (u64)ts_eसमय.tv_sec, ts_eसमय.tv_nsec / 1000,
		    (u64)ts_vblank_समय.tv_sec, ts_vblank_समय.tv_nsec / 1000,
		    duration_ns / 1000, i);

	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_crtc_vblank_helper_get_vblank_बारtamp_पूर्णांकernal);

/**
 * drm_crtc_vblank_helper_get_vblank_बारtamp - precise vblank बारtamp
 *                                               helper
 * @crtc: CRTC whose vblank बारtamp to retrieve
 * @max_error: Desired maximum allowable error in बारtamps (nanosecs)
 *             On वापस contains true maximum error of बारtamp
 * @vblank_समय: Poपूर्णांकer to समय which should receive the बारtamp
 * @in_vblank_irq:
 *     True when called from drm_crtc_handle_vblank().  Some drivers
 *     need to apply some workarounds क्रम gpu-specअगरic vblank irq quirks
 *     अगर flag is set.
 *
 * Implements calculation of exact vblank बारtamps from given drm_display_mode
 * timings and current video scanout position of a CRTC. This can be directly
 * used as the &drm_crtc_funcs.get_vblank_बारtamp implementation of a kms
 * driver अगर &drm_crtc_helper_funcs.get_scanout_position is implemented.
 *
 * The current implementation only handles standard video modes. For द्विगुन scan
 * and पूर्णांकerlaced modes the driver is supposed to adjust the hardware mode
 * (taken from &drm_crtc_state.adjusted mode क्रम atomic modeset drivers) to
 * match the scanout position reported.
 *
 * Note that atomic drivers must call drm_calc_बारtamping_स्थिरants() beक्रमe
 * enabling a CRTC. The atomic helpers alपढ़ोy take care of that in
 * drm_atomic_helper_calc_बारtamping_स्थिरants().
 *
 * Returns:
 *
 * Returns true on success, and false on failure, i.e. when no accurate
 * बारtamp could be acquired.
 */
bool drm_crtc_vblank_helper_get_vblank_बारtamp(काष्ठा drm_crtc *crtc,
						 पूर्णांक *max_error,
						 kसमय_प्रकार *vblank_समय,
						 bool in_vblank_irq)
अणु
	वापस drm_crtc_vblank_helper_get_vblank_बारtamp_पूर्णांकernal(
		crtc, max_error, vblank_समय, in_vblank_irq,
		crtc->helper_निजी->get_scanout_position);
पूर्ण
EXPORT_SYMBOL(drm_crtc_vblank_helper_get_vblank_बारtamp);

/**
 * drm_get_last_vblबारtamp - retrieve raw बारtamp क्रम the most recent
 *                             vblank पूर्णांकerval
 * @dev: DRM device
 * @pipe: index of CRTC whose vblank बारtamp to retrieve
 * @tvblank: Poपूर्णांकer to target समय which should receive the बारtamp
 * @in_vblank_irq:
 *     True when called from drm_crtc_handle_vblank().  Some drivers
 *     need to apply some workarounds क्रम gpu-specअगरic vblank irq quirks
 *     अगर flag is set.
 *
 * Fetches the प्रणाली बारtamp corresponding to the समय of the most recent
 * vblank पूर्णांकerval on specअगरied CRTC. May call पूर्णांकo kms-driver to
 * compute the बारtamp with a high-precision GPU specअगरic method.
 *
 * Returns zero अगर बारtamp originates from uncorrected करो_समय_लोofday()
 * call, i.e., it isn't very precisely locked to the true vblank.
 *
 * Returns:
 * True अगर बारtamp is considered to be very precise, false otherwise.
 */
अटल bool
drm_get_last_vblबारtamp(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe,
			  kसमय_प्रकार *tvblank, bool in_vblank_irq)
अणु
	काष्ठा drm_crtc *crtc = drm_crtc_from_index(dev, pipe);
	bool ret = false;

	/* Define requested maximum error on बारtamps (nanoseconds). */
	पूर्णांक max_error = (पूर्णांक) drm_बारtamp_precision * 1000;

	/* Query driver अगर possible and precision बारtamping enabled. */
	अगर (crtc && crtc->funcs->get_vblank_बारtamp && max_error > 0) अणु
		काष्ठा drm_crtc *crtc = drm_crtc_from_index(dev, pipe);

		ret = crtc->funcs->get_vblank_बारtamp(crtc, &max_error,
							tvblank, in_vblank_irq);
	पूर्ण

	/* GPU high precision बारtamp query unsupported or failed.
	 * Return current monotonic/समय_लोofday बारtamp as best estimate.
	 */
	अगर (!ret)
		*tvblank = kसमय_get();

	वापस ret;
पूर्ण

/**
 * drm_crtc_vblank_count - retrieve "cooked" vblank counter value
 * @crtc: which counter to retrieve
 *
 * Fetches the "cooked" vblank count value that represents the number of
 * vblank events since the प्रणाली was booted, including lost events due to
 * modesetting activity. Note that this समयr isn't correct against a racing
 * vblank पूर्णांकerrupt (since it only reports the software vblank counter), see
 * drm_crtc_accurate_vblank_count() क्रम such use-हालs.
 *
 * Note that क्रम a given vblank counter value drm_crtc_handle_vblank()
 * and drm_crtc_vblank_count() or drm_crtc_vblank_count_and_समय()
 * provide a barrier: Any ग_लिखोs करोne beक्रमe calling
 * drm_crtc_handle_vblank() will be visible to callers of the later
 * functions, अगरf the vblank count is the same or a later one.
 *
 * See also &drm_vblank_crtc.count.
 *
 * Returns:
 * The software vblank counter.
 */
u64 drm_crtc_vblank_count(काष्ठा drm_crtc *crtc)
अणु
	वापस drm_vblank_count(crtc->dev, drm_crtc_index(crtc));
पूर्ण
EXPORT_SYMBOL(drm_crtc_vblank_count);

/**
 * drm_vblank_count_and_समय - retrieve "cooked" vblank counter value and the
 *     प्रणाली बारtamp corresponding to that vblank counter value.
 * @dev: DRM device
 * @pipe: index of CRTC whose counter to retrieve
 * @vblankसमय: Poपूर्णांकer to kसमय_प्रकार to receive the vblank बारtamp.
 *
 * Fetches the "cooked" vblank count value that represents the number of
 * vblank events since the प्रणाली was booted, including lost events due to
 * modesetting activity. Returns corresponding प्रणाली बारtamp of the समय
 * of the vblank पूर्णांकerval that corresponds to the current vblank counter value.
 *
 * This is the legacy version of drm_crtc_vblank_count_and_समय().
 */
अटल u64 drm_vblank_count_and_समय(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe,
				     kसमय_प्रकार *vblankसमय)
अणु
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];
	u64 vblank_count;
	अचिन्हित पूर्णांक seq;

	अगर (drm_WARN_ON(dev, pipe >= dev->num_crtcs)) अणु
		*vblankसमय = 0;
		वापस 0;
	पूर्ण

	करो अणु
		seq = पढ़ो_seqbegin(&vblank->seqlock);
		vblank_count = atomic64_पढ़ो(&vblank->count);
		*vblankसमय = vblank->समय;
	पूर्ण जबतक (पढ़ो_seqretry(&vblank->seqlock, seq));

	वापस vblank_count;
पूर्ण

/**
 * drm_crtc_vblank_count_and_समय - retrieve "cooked" vblank counter value
 *     and the प्रणाली बारtamp corresponding to that vblank counter value
 * @crtc: which counter to retrieve
 * @vblankसमय: Poपूर्णांकer to समय to receive the vblank बारtamp.
 *
 * Fetches the "cooked" vblank count value that represents the number of
 * vblank events since the प्रणाली was booted, including lost events due to
 * modesetting activity. Returns corresponding प्रणाली बारtamp of the समय
 * of the vblank पूर्णांकerval that corresponds to the current vblank counter value.
 *
 * Note that क्रम a given vblank counter value drm_crtc_handle_vblank()
 * and drm_crtc_vblank_count() or drm_crtc_vblank_count_and_समय()
 * provide a barrier: Any ग_लिखोs करोne beक्रमe calling
 * drm_crtc_handle_vblank() will be visible to callers of the later
 * functions, अगरf the vblank count is the same or a later one.
 *
 * See also &drm_vblank_crtc.count.
 */
u64 drm_crtc_vblank_count_and_समय(काष्ठा drm_crtc *crtc,
				   kसमय_प्रकार *vblankसमय)
अणु
	वापस drm_vblank_count_and_समय(crtc->dev, drm_crtc_index(crtc),
					 vblankसमय);
पूर्ण
EXPORT_SYMBOL(drm_crtc_vblank_count_and_समय);

अटल व्योम send_vblank_event(काष्ठा drm_device *dev,
		काष्ठा drm_pending_vblank_event *e,
		u64 seq, kसमय_प्रकार now)
अणु
	काष्ठा बारpec64 tv;

	चयन (e->event.base.type) अणु
	हाल DRM_EVENT_VBLANK:
	हाल DRM_EVENT_FLIP_COMPLETE:
		tv = kसमय_प्रकारo_बारpec64(now);
		e->event.vbl.sequence = seq;
		/*
		 * e->event is a user space काष्ठाure, with hardcoded अचिन्हित
		 * 32-bit seconds/microseconds. This is safe as we always use
		 * monotonic बारtamps since linux-4.15
		 */
		e->event.vbl.tv_sec = tv.tv_sec;
		e->event.vbl.tv_usec = tv.tv_nsec / 1000;
		अवरोध;
	हाल DRM_EVENT_CRTC_SEQUENCE:
		अगर (seq)
			e->event.seq.sequence = seq;
		e->event.seq.समय_ns = kसमय_प्रकारo_ns(now);
		अवरोध;
	पूर्ण
	trace_drm_vblank_event_delivered(e->base.file_priv, e->pipe, seq);
	/*
	 * Use the same बारtamp क्रम any associated fence संकेत to aव्योम
	 * mismatch in बारtamps क्रम vsync & fence events triggered by the
	 * same HW event. Frameworks like SurfaceFlinger in Android expects the
	 * retire-fence बारtamp to match exactly with HW vsync as it uses it
	 * क्रम its software vsync modeling.
	 */
	drm_send_event_बारtamp_locked(dev, &e->base, now);
पूर्ण

/**
 * drm_crtc_arm_vblank_event - arm vblank event after pageflip
 * @crtc: the source CRTC of the vblank event
 * @e: the event to send
 *
 * A lot of drivers need to generate vblank events क्रम the very next vblank
 * पूर्णांकerrupt. For example when the page flip पूर्णांकerrupt happens when the page
 * flip माला_लो armed, but not when it actually executes within the next vblank
 * period. This helper function implements exactly the required vblank arming
 * behaviour.
 *
 * NOTE: Drivers using this to send out the &drm_crtc_state.event as part of an
 * atomic commit must ensure that the next vblank happens at exactly the same
 * समय as the atomic commit is committed to the hardware. This function itself
 * करोes **not** protect against the next vblank पूर्णांकerrupt racing with either this
 * function call or the atomic commit operation. A possible sequence could be:
 *
 * 1. Driver commits new hardware state पूर्णांकo vblank-synchronized रेजिस्टरs.
 * 2. A vblank happens, committing the hardware state. Also the corresponding
 *    vblank पूर्णांकerrupt is fired off and fully processed by the पूर्णांकerrupt
 *    handler.
 * 3. The atomic commit operation proceeds to call drm_crtc_arm_vblank_event().
 * 4. The event is only send out क्रम the next vblank, which is wrong.
 *
 * An equivalent race can happen when the driver calls
 * drm_crtc_arm_vblank_event() beक्रमe writing out the new hardware state.
 *
 * The only way to make this work safely is to prevent the vblank from firing
 * (and the hardware from committing anything अन्यथा) until the entire atomic
 * commit sequence has run to completion. If the hardware करोes not have such a
 * feature (e.g. using a "go" bit), then it is unsafe to use this functions.
 * Instead drivers need to manually send out the event from their पूर्णांकerrupt
 * handler by calling drm_crtc_send_vblank_event() and make sure that there's no
 * possible race with the hardware committing the atomic update.
 *
 * Caller must hold a vblank reference क्रम the event @e acquired by a
 * drm_crtc_vblank_get(), which will be dropped when the next vblank arrives.
 */
व्योम drm_crtc_arm_vblank_event(काष्ठा drm_crtc *crtc,
			       काष्ठा drm_pending_vblank_event *e)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = drm_crtc_index(crtc);

	निश्चित_spin_locked(&dev->event_lock);

	e->pipe = pipe;
	e->sequence = drm_crtc_accurate_vblank_count(crtc) + 1;
	list_add_tail(&e->base.link, &dev->vblank_event_list);
पूर्ण
EXPORT_SYMBOL(drm_crtc_arm_vblank_event);

/**
 * drm_crtc_send_vblank_event - helper to send vblank event after pageflip
 * @crtc: the source CRTC of the vblank event
 * @e: the event to send
 *
 * Updates sequence # and बारtamp on event क्रम the most recently processed
 * vblank, and sends it to userspace.  Caller must hold event lock.
 *
 * See drm_crtc_arm_vblank_event() क्रम a helper which can be used in certain
 * situation, especially to send out events क्रम atomic commit operations.
 */
व्योम drm_crtc_send_vblank_event(काष्ठा drm_crtc *crtc,
				काष्ठा drm_pending_vblank_event *e)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	u64 seq;
	अचिन्हित पूर्णांक pipe = drm_crtc_index(crtc);
	kसमय_प्रकार now;

	अगर (drm_dev_has_vblank(dev)) अणु
		seq = drm_vblank_count_and_समय(dev, pipe, &now);
	पूर्ण अन्यथा अणु
		seq = 0;

		now = kसमय_get();
	पूर्ण
	e->pipe = pipe;
	send_vblank_event(dev, e, seq, now);
पूर्ण
EXPORT_SYMBOL(drm_crtc_send_vblank_event);

अटल पूर्णांक __enable_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	अगर (drm_core_check_feature(dev, DRIVER_MODESET)) अणु
		काष्ठा drm_crtc *crtc = drm_crtc_from_index(dev, pipe);

		अगर (drm_WARN_ON(dev, !crtc))
			वापस 0;

		अगर (crtc->funcs->enable_vblank)
			वापस crtc->funcs->enable_vblank(crtc);
	पूर्ण
#अगर_घोषित CONFIG_DRM_LEGACY
	अन्यथा अगर (dev->driver->enable_vblank) अणु
		वापस dev->driver->enable_vblank(dev, pipe);
	पूर्ण
#पूर्ण_अगर

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक drm_vblank_enable(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];
	पूर्णांक ret = 0;

	निश्चित_spin_locked(&dev->vbl_lock);

	spin_lock(&dev->vblank_समय_lock);

	अगर (!vblank->enabled) अणु
		/*
		 * Enable vblank irqs under vblank_समय_lock protection.
		 * All vblank count & बारtamp updates are held off
		 * until we are करोne reinitializing master counter and
		 * बारtamps. Filtercode in drm_handle_vblank() will
		 * prevent द्विगुन-accounting of same vblank पूर्णांकerval.
		 */
		ret = __enable_vblank(dev, pipe);
		drm_dbg_core(dev, "enabling vblank on crtc %u, ret: %d\n",
			     pipe, ret);
		अगर (ret) अणु
			atomic_dec(&vblank->refcount);
		पूर्ण अन्यथा अणु
			drm_update_vblank_count(dev, pipe, 0);
			/* drm_update_vblank_count() includes a wmb so we just
			 * need to ensure that the compiler emits the ग_लिखो
			 * to mark the vblank as enabled after the call
			 * to drm_update_vblank_count().
			 */
			WRITE_ONCE(vblank->enabled, true);
		पूर्ण
	पूर्ण

	spin_unlock(&dev->vblank_समय_lock);

	वापस ret;
पूर्ण

पूर्णांक drm_vblank_get(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];
	अचिन्हित दीर्घ irqflags;
	पूर्णांक ret = 0;

	अगर (!drm_dev_has_vblank(dev))
		वापस -EINVAL;

	अगर (drm_WARN_ON(dev, pipe >= dev->num_crtcs))
		वापस -EINVAL;

	spin_lock_irqsave(&dev->vbl_lock, irqflags);
	/* Going from 0->1 means we have to enable पूर्णांकerrupts again */
	अगर (atomic_add_वापस(1, &vblank->refcount) == 1) अणु
		ret = drm_vblank_enable(dev, pipe);
	पूर्ण अन्यथा अणु
		अगर (!vblank->enabled) अणु
			atomic_dec(&vblank->refcount);
			ret = -EINVAL;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev->vbl_lock, irqflags);

	वापस ret;
पूर्ण

/**
 * drm_crtc_vblank_get - get a reference count on vblank events
 * @crtc: which CRTC to own
 *
 * Acquire a reference count on vblank events to aव्योम having them disabled
 * जबतक in use.
 *
 * Returns:
 * Zero on success or a negative error code on failure.
 */
पूर्णांक drm_crtc_vblank_get(काष्ठा drm_crtc *crtc)
अणु
	वापस drm_vblank_get(crtc->dev, drm_crtc_index(crtc));
पूर्ण
EXPORT_SYMBOL(drm_crtc_vblank_get);

व्योम drm_vblank_put(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];

	अगर (drm_WARN_ON(dev, pipe >= dev->num_crtcs))
		वापस;

	अगर (drm_WARN_ON(dev, atomic_पढ़ो(&vblank->refcount) == 0))
		वापस;

	/* Last user schedules पूर्णांकerrupt disable */
	अगर (atomic_dec_and_test(&vblank->refcount)) अणु
		अगर (drm_vblank_offdelay == 0)
			वापस;
		अन्यथा अगर (drm_vblank_offdelay < 0)
			vblank_disable_fn(&vblank->disable_समयr);
		अन्यथा अगर (!dev->vblank_disable_immediate)
			mod_समयr(&vblank->disable_समयr,
				  jअगरfies + ((drm_vblank_offdelay * HZ)/1000));
	पूर्ण
पूर्ण

/**
 * drm_crtc_vblank_put - give up ownership of vblank events
 * @crtc: which counter to give up
 *
 * Release ownership of a given vblank counter, turning off पूर्णांकerrupts
 * अगर possible. Disable पूर्णांकerrupts after drm_vblank_offdelay milliseconds.
 */
व्योम drm_crtc_vblank_put(काष्ठा drm_crtc *crtc)
अणु
	drm_vblank_put(crtc->dev, drm_crtc_index(crtc));
पूर्ण
EXPORT_SYMBOL(drm_crtc_vblank_put);

/**
 * drm_रुको_one_vblank - रुको क्रम one vblank
 * @dev: DRM device
 * @pipe: CRTC index
 *
 * This रुकोs क्रम one vblank to pass on @pipe, using the irq driver पूर्णांकerfaces.
 * It is a failure to call this when the vblank irq क्रम @pipe is disabled, e.g.
 * due to lack of driver support or because the crtc is off.
 *
 * This is the legacy version of drm_crtc_रुको_one_vblank().
 */
व्योम drm_रुको_one_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];
	पूर्णांक ret;
	u64 last;

	अगर (drm_WARN_ON(dev, pipe >= dev->num_crtcs))
		वापस;

	ret = drm_vblank_get(dev, pipe);
	अगर (drm_WARN(dev, ret, "vblank not available on crtc %i, ret=%i\n",
		     pipe, ret))
		वापस;

	last = drm_vblank_count(dev, pipe);

	ret = रुको_event_समयout(vblank->queue,
				 last != drm_vblank_count(dev, pipe),
				 msecs_to_jअगरfies(100));

	drm_WARN(dev, ret == 0, "vblank wait timed out on crtc %i\n", pipe);

	drm_vblank_put(dev, pipe);
पूर्ण
EXPORT_SYMBOL(drm_रुको_one_vblank);

/**
 * drm_crtc_रुको_one_vblank - रुको क्रम one vblank
 * @crtc: DRM crtc
 *
 * This रुकोs क्रम one vblank to pass on @crtc, using the irq driver पूर्णांकerfaces.
 * It is a failure to call this when the vblank irq क्रम @crtc is disabled, e.g.
 * due to lack of driver support or because the crtc is off.
 */
व्योम drm_crtc_रुको_one_vblank(काष्ठा drm_crtc *crtc)
अणु
	drm_रुको_one_vblank(crtc->dev, drm_crtc_index(crtc));
पूर्ण
EXPORT_SYMBOL(drm_crtc_रुको_one_vblank);

/**
 * drm_crtc_vblank_off - disable vblank events on a CRTC
 * @crtc: CRTC in question
 *
 * Drivers can use this function to shut करोwn the vblank पूर्णांकerrupt handling when
 * disabling a crtc. This function ensures that the latest vblank frame count is
 * stored so that drm_vblank_on can restore it again.
 *
 * Drivers must use this function when the hardware vblank counter can get
 * reset, e.g. when suspending or disabling the @crtc in general.
 */
व्योम drm_crtc_vblank_off(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = drm_crtc_index(crtc);
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];
	काष्ठा drm_pending_vblank_event *e, *t;
	kसमय_प्रकार now;
	u64 seq;

	अगर (drm_WARN_ON(dev, pipe >= dev->num_crtcs))
		वापस;

	/*
	 * Grab event_lock early to prevent vblank work from being scheduled
	 * जबतक we're in the middle of shutting करोwn vblank पूर्णांकerrupts
	 */
	spin_lock_irq(&dev->event_lock);

	spin_lock(&dev->vbl_lock);
	drm_dbg_vbl(dev, "crtc %d, vblank enabled %d, inmodeset %d\n",
		    pipe, vblank->enabled, vblank->inmodeset);

	/* Aव्योम redundant vblank disables without previous
	 * drm_crtc_vblank_on(). */
	अगर (drm_core_check_feature(dev, DRIVER_ATOMIC) || !vblank->inmodeset)
		drm_vblank_disable_and_save(dev, pipe);

	wake_up(&vblank->queue);

	/*
	 * Prevent subsequent drm_vblank_get() from re-enabling
	 * the vblank पूर्णांकerrupt by bumping the refcount.
	 */
	अगर (!vblank->inmodeset) अणु
		atomic_inc(&vblank->refcount);
		vblank->inmodeset = 1;
	पूर्ण
	spin_unlock(&dev->vbl_lock);

	/* Send any queued vblank events, lest the natives grow disquiet */
	seq = drm_vblank_count_and_समय(dev, pipe, &now);

	list_क्रम_each_entry_safe(e, t, &dev->vblank_event_list, base.link) अणु
		अगर (e->pipe != pipe)
			जारी;
		drm_dbg_core(dev, "Sending premature vblank event on disable: "
			     "wanted %llu, current %llu\n",
			     e->sequence, seq);
		list_del(&e->base.link);
		drm_vblank_put(dev, pipe);
		send_vblank_event(dev, e, seq, now);
	पूर्ण

	/* Cancel any leftover pending vblank work */
	drm_vblank_cancel_pending_works(vblank);

	spin_unlock_irq(&dev->event_lock);

	/* Will be reset by the modeset helpers when re-enabling the crtc by
	 * calling drm_calc_बारtamping_स्थिरants(). */
	vblank->hwmode.crtc_घड़ी = 0;

	/* Wait क्रम any vblank work that's still executing to finish */
	drm_vblank_flush_worker(vblank);
पूर्ण
EXPORT_SYMBOL(drm_crtc_vblank_off);

/**
 * drm_crtc_vblank_reset - reset vblank state to off on a CRTC
 * @crtc: CRTC in question
 *
 * Drivers can use this function to reset the vblank state to off at load समय.
 * Drivers should use this together with the drm_crtc_vblank_off() and
 * drm_crtc_vblank_on() functions. The dअगरference compared to
 * drm_crtc_vblank_off() is that this function करोesn't save the vblank counter
 * and hence करोesn't need to call any driver hooks.
 *
 * This is useful क्रम recovering driver state e.g. on driver load, or on resume.
 */
व्योम drm_crtc_vblank_reset(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = drm_crtc_index(crtc);
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];

	spin_lock_irq(&dev->vbl_lock);
	/*
	 * Prevent subsequent drm_vblank_get() from enabling the vblank
	 * पूर्णांकerrupt by bumping the refcount.
	 */
	अगर (!vblank->inmodeset) अणु
		atomic_inc(&vblank->refcount);
		vblank->inmodeset = 1;
	पूर्ण
	spin_unlock_irq(&dev->vbl_lock);

	drm_WARN_ON(dev, !list_empty(&dev->vblank_event_list));
	drm_WARN_ON(dev, !list_empty(&vblank->pending_work));
पूर्ण
EXPORT_SYMBOL(drm_crtc_vblank_reset);

/**
 * drm_crtc_set_max_vblank_count - configure the hw max vblank counter value
 * @crtc: CRTC in question
 * @max_vblank_count: max hardware vblank counter value
 *
 * Update the maximum hardware vblank counter value क्रम @crtc
 * at runसमय. Useful क्रम hardware where the operation of the
 * hardware vblank counter depends on the currently active
 * display configuration.
 *
 * For example, अगर the hardware vblank counter करोes not work
 * when a specअगरic connector is active the maximum can be set
 * to zero. And when that specअगरic connector isn't active the
 * maximum can again be set to the appropriate non-zero value.
 *
 * If used, must be called beक्रमe drm_vblank_on().
 */
व्योम drm_crtc_set_max_vblank_count(काष्ठा drm_crtc *crtc,
				   u32 max_vblank_count)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = drm_crtc_index(crtc);
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];

	drm_WARN_ON(dev, dev->max_vblank_count);
	drm_WARN_ON(dev, !READ_ONCE(vblank->inmodeset));

	vblank->max_vblank_count = max_vblank_count;
पूर्ण
EXPORT_SYMBOL(drm_crtc_set_max_vblank_count);

/**
 * drm_crtc_vblank_on - enable vblank events on a CRTC
 * @crtc: CRTC in question
 *
 * This functions restores the vblank पूर्णांकerrupt state captured with
 * drm_crtc_vblank_off() again and is generally called when enabling @crtc. Note
 * that calls to drm_crtc_vblank_on() and drm_crtc_vblank_off() can be
 * unbalanced and so can also be unconditionally called in driver load code to
 * reflect the current hardware state of the crtc.
 */
व्योम drm_crtc_vblank_on(काष्ठा drm_crtc *crtc)
अणु
	काष्ठा drm_device *dev = crtc->dev;
	अचिन्हित पूर्णांक pipe = drm_crtc_index(crtc);
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];

	अगर (drm_WARN_ON(dev, pipe >= dev->num_crtcs))
		वापस;

	spin_lock_irq(&dev->vbl_lock);
	drm_dbg_vbl(dev, "crtc %d, vblank enabled %d, inmodeset %d\n",
		    pipe, vblank->enabled, vblank->inmodeset);

	/* Drop our निजी "prevent drm_vblank_get" refcount */
	अगर (vblank->inmodeset) अणु
		atomic_dec(&vblank->refcount);
		vblank->inmodeset = 0;
	पूर्ण

	drm_reset_vblank_बारtamp(dev, pipe);

	/*
	 * re-enable पूर्णांकerrupts अगर there are users left, or the
	 * user wishes vblank पूर्णांकerrupts to be enabled all the समय.
	 */
	अगर (atomic_पढ़ो(&vblank->refcount) != 0 || drm_vblank_offdelay == 0)
		drm_WARN_ON(dev, drm_vblank_enable(dev, pipe));
	spin_unlock_irq(&dev->vbl_lock);
पूर्ण
EXPORT_SYMBOL(drm_crtc_vblank_on);

अटल व्योम drm_vblank_restore(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	kसमय_प्रकार t_vblank;
	काष्ठा drm_vblank_crtc *vblank;
	पूर्णांक framedur_ns;
	u64 dअगरf_ns;
	u32 cur_vblank, dअगरf = 1;
	पूर्णांक count = DRM_TIMESTAMP_MAXRETRIES;
	u32 max_vblank_count = drm_max_vblank_count(dev, pipe);

	अगर (drm_WARN_ON(dev, pipe >= dev->num_crtcs))
		वापस;

	निश्चित_spin_locked(&dev->vbl_lock);
	निश्चित_spin_locked(&dev->vblank_समय_lock);

	vblank = &dev->vblank[pipe];
	drm_WARN_ONCE(dev,
		      drm_debug_enabled(DRM_UT_VBL) && !vblank->framedur_ns,
		      "Cannot compute missed vblanks without frame duration\n");
	framedur_ns = vblank->framedur_ns;

	करो अणु
		cur_vblank = __get_vblank_counter(dev, pipe);
		drm_get_last_vblबारtamp(dev, pipe, &t_vblank, false);
	पूर्ण जबतक (cur_vblank != __get_vblank_counter(dev, pipe) && --count > 0);

	dअगरf_ns = kसमय_प्रकारo_ns(kसमय_sub(t_vblank, vblank->समय));
	अगर (framedur_ns)
		dअगरf = DIV_ROUND_CLOSEST_ULL(dअगरf_ns, framedur_ns);


	drm_dbg_vbl(dev,
		    "missed %d vblanks in %lld ns, frame duration=%d ns, hw_diff=%d\n",
		    dअगरf, dअगरf_ns, framedur_ns, cur_vblank - vblank->last);
	vblank->last = (cur_vblank - dअगरf) & max_vblank_count;
पूर्ण

/**
 * drm_crtc_vblank_restore - estimate missed vblanks and update vblank count.
 * @crtc: CRTC in question
 *
 * Power manamement features can cause frame counter resets between vblank
 * disable and enable. Drivers can use this function in their
 * &drm_crtc_funcs.enable_vblank implementation to estimate missed vblanks since
 * the last &drm_crtc_funcs.disable_vblank using बारtamps and update the
 * vblank counter.
 *
 * Note that drivers must have race-मुक्त high-precision बारtamping support,
 * i.e.  &drm_crtc_funcs.get_vblank_बारtamp must be hooked up and
 * &drm_driver.vblank_disable_immediate must be set to indicate the
 * समय-stamping functions are race-मुक्त against vblank hardware counter
 * increments.
 */
व्योम drm_crtc_vblank_restore(काष्ठा drm_crtc *crtc)
अणु
	WARN_ON_ONCE(!crtc->funcs->get_vblank_बारtamp);
	WARN_ON_ONCE(!crtc->dev->vblank_disable_immediate);

	drm_vblank_restore(crtc->dev, drm_crtc_index(crtc));
पूर्ण
EXPORT_SYMBOL(drm_crtc_vblank_restore);

अटल व्योम drm_legacy_vblank_pre_modeset(काष्ठा drm_device *dev,
					  अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];

	/* vblank is not initialized (IRQ not installed ?), or has been मुक्तd */
	अगर (!drm_dev_has_vblank(dev))
		वापस;

	अगर (drm_WARN_ON(dev, pipe >= dev->num_crtcs))
		वापस;

	/*
	 * To aव्योम all the problems that might happen अगर पूर्णांकerrupts
	 * were enabled/disabled around or between these calls, we just
	 * have the kernel take a reference on the CRTC (just once though
	 * to aव्योम corrupting the count अगर multiple, mismatch calls occur),
	 * so that पूर्णांकerrupts reमुख्य enabled in the पूर्णांकerim.
	 */
	अगर (!vblank->inmodeset) अणु
		vblank->inmodeset = 0x1;
		अगर (drm_vblank_get(dev, pipe) == 0)
			vblank->inmodeset |= 0x2;
	पूर्ण
पूर्ण

अटल व्योम drm_legacy_vblank_post_modeset(काष्ठा drm_device *dev,
					   अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];

	/* vblank is not initialized (IRQ not installed ?), or has been मुक्तd */
	अगर (!drm_dev_has_vblank(dev))
		वापस;

	अगर (drm_WARN_ON(dev, pipe >= dev->num_crtcs))
		वापस;

	अगर (vblank->inmodeset) अणु
		spin_lock_irq(&dev->vbl_lock);
		drm_reset_vblank_बारtamp(dev, pipe);
		spin_unlock_irq(&dev->vbl_lock);

		अगर (vblank->inmodeset & 0x2)
			drm_vblank_put(dev, pipe);

		vblank->inmodeset = 0;
	पूर्ण
पूर्ण

पूर्णांक drm_legacy_modeset_ctl_ioctl(काष्ठा drm_device *dev, व्योम *data,
				 काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_modeset_ctl *modeset = data;
	अचिन्हित पूर्णांक pipe;

	/* If drm_vblank_init() hasn't been called yet, just no-op */
	अगर (!drm_dev_has_vblank(dev))
		वापस 0;

	/* KMS drivers handle this पूर्णांकernally */
	अगर (!drm_core_check_feature(dev, DRIVER_LEGACY))
		वापस 0;

	pipe = modeset->crtc;
	अगर (pipe >= dev->num_crtcs)
		वापस -EINVAL;

	चयन (modeset->cmd) अणु
	हाल _DRM_PRE_MODESET:
		drm_legacy_vblank_pre_modeset(dev, pipe);
		अवरोध;
	हाल _DRM_POST_MODESET:
		drm_legacy_vblank_post_modeset(dev, pipe);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक drm_queue_vblank_event(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe,
				  u64 req_seq,
				  जोड़ drm_रुको_vblank *vblरुको,
				  काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];
	काष्ठा drm_pending_vblank_event *e;
	kसमय_प्रकार now;
	u64 seq;
	पूर्णांक ret;

	e = kzalloc(माप(*e), GFP_KERNEL);
	अगर (e == शून्य) अणु
		ret = -ENOMEM;
		जाओ err_put;
	पूर्ण

	e->pipe = pipe;
	e->event.base.type = DRM_EVENT_VBLANK;
	e->event.base.length = माप(e->event.vbl);
	e->event.vbl.user_data = vblरुको->request.संकेत;
	e->event.vbl.crtc_id = 0;
	अगर (drm_core_check_feature(dev, DRIVER_MODESET)) अणु
		काष्ठा drm_crtc *crtc = drm_crtc_from_index(dev, pipe);

		अगर (crtc)
			e->event.vbl.crtc_id = crtc->base.id;
	पूर्ण

	spin_lock_irq(&dev->event_lock);

	/*
	 * drm_crtc_vblank_off() might have been called after we called
	 * drm_vblank_get(). drm_crtc_vblank_off() holds event_lock around the
	 * vblank disable, so no need क्रम further locking.  The reference from
	 * drm_vblank_get() protects against vblank disable from another source.
	 */
	अगर (!READ_ONCE(vblank->enabled)) अणु
		ret = -EINVAL;
		जाओ err_unlock;
	पूर्ण

	ret = drm_event_reserve_init_locked(dev, file_priv, &e->base,
					    &e->event.base);

	अगर (ret)
		जाओ err_unlock;

	seq = drm_vblank_count_and_समय(dev, pipe, &now);

	drm_dbg_core(dev, "event on vblank count %llu, current %llu, crtc %u\n",
		     req_seq, seq, pipe);

	trace_drm_vblank_event_queued(file_priv, pipe, req_seq);

	e->sequence = req_seq;
	अगर (drm_vblank_passed(seq, req_seq)) अणु
		drm_vblank_put(dev, pipe);
		send_vblank_event(dev, e, seq, now);
		vblरुको->reply.sequence = seq;
	पूर्ण अन्यथा अणु
		/* drm_handle_vblank_events will call drm_vblank_put */
		list_add_tail(&e->base.link, &dev->vblank_event_list);
		vblरुको->reply.sequence = req_seq;
	पूर्ण

	spin_unlock_irq(&dev->event_lock);

	वापस 0;

err_unlock:
	spin_unlock_irq(&dev->event_lock);
	kमुक्त(e);
err_put:
	drm_vblank_put(dev, pipe);
	वापस ret;
पूर्ण

अटल bool drm_रुको_vblank_is_query(जोड़ drm_रुको_vblank *vblरुको)
अणु
	अगर (vblरुको->request.sequence)
		वापस false;

	वापस _DRM_VBLANK_RELATIVE ==
		(vblरुको->request.type & (_DRM_VBLANK_TYPES_MASK |
					  _DRM_VBLANK_EVENT |
					  _DRM_VBLANK_NEXTONMISS));
पूर्ण

/*
 * Widen a 32-bit param to 64-bits.
 *
 * \param narrow 32-bit value (missing upper 32 bits)
 * \param near 64-bit value that should be 'close' to near
 *
 * This function वापसs a 64-bit value using the lower 32-bits from
 * 'narrow' and स्थिरructing the upper 32-bits so that the result is
 * as बंद as possible to 'near'.
 */

अटल u64 widen_32_to_64(u32 narrow, u64 near)
अणु
	वापस near + (s32) (narrow - near);
पूर्ण

अटल व्योम drm_रुको_vblank_reply(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe,
				  काष्ठा drm_रुको_vblank_reply *reply)
अणु
	kसमय_प्रकार now;
	काष्ठा बारpec64 ts;

	/*
	 * drm_रुको_vblank_reply is a UAPI काष्ठाure that uses 'long'
	 * to store the seconds. This is safe as we always use monotonic
	 * बारtamps since linux-4.15.
	 */
	reply->sequence = drm_vblank_count_and_समय(dev, pipe, &now);
	ts = kसमय_प्रकारo_बारpec64(now);
	reply->tval_sec = (u32)ts.tv_sec;
	reply->tval_usec = ts.tv_nsec / 1000;
पूर्ण

पूर्णांक drm_रुको_vblank_ioctl(काष्ठा drm_device *dev, व्योम *data,
			  काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_vblank_crtc *vblank;
	जोड़ drm_रुको_vblank *vblरुको = data;
	पूर्णांक ret;
	u64 req_seq, seq;
	अचिन्हित पूर्णांक pipe_index;
	अचिन्हित पूर्णांक flags, pipe, high_pipe;

	अगर (!dev->irq_enabled)
		वापस -EOPNOTSUPP;

	अगर (vblरुको->request.type & _DRM_VBLANK_SIGNAL)
		वापस -EINVAL;

	अगर (vblरुको->request.type &
	    ~(_DRM_VBLANK_TYPES_MASK | _DRM_VBLANK_FLAGS_MASK |
	      _DRM_VBLANK_HIGH_CRTC_MASK)) अणु
		drm_dbg_core(dev,
			     "Unsupported type value 0x%x, supported mask 0x%x\n",
			     vblरुको->request.type,
			     (_DRM_VBLANK_TYPES_MASK | _DRM_VBLANK_FLAGS_MASK |
			      _DRM_VBLANK_HIGH_CRTC_MASK));
		वापस -EINVAL;
	पूर्ण

	flags = vblरुको->request.type & _DRM_VBLANK_FLAGS_MASK;
	high_pipe = (vblरुको->request.type & _DRM_VBLANK_HIGH_CRTC_MASK);
	अगर (high_pipe)
		pipe_index = high_pipe >> _DRM_VBLANK_HIGH_CRTC_SHIFT;
	अन्यथा
		pipe_index = flags & _DRM_VBLANK_SECONDARY ? 1 : 0;

	/* Convert lease-relative crtc index पूर्णांकo global crtc index */
	अगर (drm_core_check_feature(dev, DRIVER_MODESET)) अणु
		pipe = 0;
		drm_क्रम_each_crtc(crtc, dev) अणु
			अगर (drm_lease_held(file_priv, crtc->base.id)) अणु
				अगर (pipe_index == 0)
					अवरोध;
				pipe_index--;
			पूर्ण
			pipe++;
		पूर्ण
	पूर्ण अन्यथा अणु
		pipe = pipe_index;
	पूर्ण

	अगर (pipe >= dev->num_crtcs)
		वापस -EINVAL;

	vblank = &dev->vblank[pipe];

	/* If the counter is currently enabled and accurate, लघु-circuit
	 * queries to वापस the cached बारtamp of the last vblank.
	 */
	अगर (dev->vblank_disable_immediate &&
	    drm_रुको_vblank_is_query(vblरुको) &&
	    READ_ONCE(vblank->enabled)) अणु
		drm_रुको_vblank_reply(dev, pipe, &vblरुको->reply);
		वापस 0;
	पूर्ण

	ret = drm_vblank_get(dev, pipe);
	अगर (ret) अणु
		drm_dbg_core(dev,
			     "crtc %d failed to acquire vblank counter, %d\n",
			     pipe, ret);
		वापस ret;
	पूर्ण
	seq = drm_vblank_count(dev, pipe);

	चयन (vblरुको->request.type & _DRM_VBLANK_TYPES_MASK) अणु
	हाल _DRM_VBLANK_RELATIVE:
		req_seq = seq + vblरुको->request.sequence;
		vblरुको->request.sequence = req_seq;
		vblरुको->request.type &= ~_DRM_VBLANK_RELATIVE;
		अवरोध;
	हाल _DRM_VBLANK_ABSOLUTE:
		req_seq = widen_32_to_64(vblरुको->request.sequence, seq);
		अवरोध;
	शेष:
		ret = -EINVAL;
		जाओ करोne;
	पूर्ण

	अगर ((flags & _DRM_VBLANK_NEXTONMISS) &&
	    drm_vblank_passed(seq, req_seq)) अणु
		req_seq = seq + 1;
		vblरुको->request.type &= ~_DRM_VBLANK_NEXTONMISS;
		vblरुको->request.sequence = req_seq;
	पूर्ण

	अगर (flags & _DRM_VBLANK_EVENT) अणु
		/* must hold on to the vblank ref until the event fires
		 * drm_vblank_put will be called asynchronously
		 */
		वापस drm_queue_vblank_event(dev, pipe, req_seq, vblरुको, file_priv);
	पूर्ण

	अगर (req_seq != seq) अणु
		पूर्णांक रुको;

		drm_dbg_core(dev, "waiting on vblank count %llu, crtc %u\n",
			     req_seq, pipe);
		रुको = रुको_event_पूर्णांकerruptible_समयout(vblank->queue,
			drm_vblank_passed(drm_vblank_count(dev, pipe), req_seq) ||
				      !READ_ONCE(vblank->enabled),
			msecs_to_jअगरfies(3000));

		चयन (रुको) अणु
		हाल 0:
			/* समयout */
			ret = -EBUSY;
			अवरोध;
		हाल -ERESTARTSYS:
			/* पूर्णांकerrupted by संकेत */
			ret = -EINTR;
			अवरोध;
		शेष:
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret != -EINTR) अणु
		drm_रुको_vblank_reply(dev, pipe, &vblरुको->reply);

		drm_dbg_core(dev, "crtc %d returning %u to client\n",
			     pipe, vblरुको->reply.sequence);
	पूर्ण अन्यथा अणु
		drm_dbg_core(dev, "crtc %d vblank wait interrupted by signal\n",
			     pipe);
	पूर्ण

करोne:
	drm_vblank_put(dev, pipe);
	वापस ret;
पूर्ण

अटल व्योम drm_handle_vblank_events(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा drm_crtc *crtc = drm_crtc_from_index(dev, pipe);
	bool high_prec = false;
	काष्ठा drm_pending_vblank_event *e, *t;
	kसमय_प्रकार now;
	u64 seq;

	निश्चित_spin_locked(&dev->event_lock);

	seq = drm_vblank_count_and_समय(dev, pipe, &now);

	list_क्रम_each_entry_safe(e, t, &dev->vblank_event_list, base.link) अणु
		अगर (e->pipe != pipe)
			जारी;
		अगर (!drm_vblank_passed(seq, e->sequence))
			जारी;

		drm_dbg_core(dev, "vblank event on %llu, current %llu\n",
			     e->sequence, seq);

		list_del(&e->base.link);
		drm_vblank_put(dev, pipe);
		send_vblank_event(dev, e, seq, now);
	पूर्ण

	अगर (crtc && crtc->funcs->get_vblank_बारtamp)
		high_prec = true;

	trace_drm_vblank_event(pipe, seq, now, high_prec);
पूर्ण

/**
 * drm_handle_vblank - handle a vblank event
 * @dev: DRM device
 * @pipe: index of CRTC where this event occurred
 *
 * Drivers should call this routine in their vblank पूर्णांकerrupt handlers to
 * update the vblank counter and send any संकेतs that may be pending.
 *
 * This is the legacy version of drm_crtc_handle_vblank().
 */
bool drm_handle_vblank(काष्ठा drm_device *dev, अचिन्हित पूर्णांक pipe)
अणु
	काष्ठा drm_vblank_crtc *vblank = &dev->vblank[pipe];
	अचिन्हित दीर्घ irqflags;
	bool disable_irq;

	अगर (drm_WARN_ON_ONCE(dev, !drm_dev_has_vblank(dev)))
		वापस false;

	अगर (drm_WARN_ON(dev, pipe >= dev->num_crtcs))
		वापस false;

	spin_lock_irqsave(&dev->event_lock, irqflags);

	/* Need बारtamp lock to prevent concurrent execution with
	 * vblank enable/disable, as this would cause inconsistent
	 * or corrupted बारtamps and vblank counts.
	 */
	spin_lock(&dev->vblank_समय_lock);

	/* Vblank irq handling disabled. Nothing to करो. */
	अगर (!vblank->enabled) अणु
		spin_unlock(&dev->vblank_समय_lock);
		spin_unlock_irqrestore(&dev->event_lock, irqflags);
		वापस false;
	पूर्ण

	drm_update_vblank_count(dev, pipe, true);

	spin_unlock(&dev->vblank_समय_lock);

	wake_up(&vblank->queue);

	/* With instant-off, we defer disabling the पूर्णांकerrupt until after
	 * we finish processing the following vblank after all events have
	 * been संकेतed. The disable has to be last (after
	 * drm_handle_vblank_events) so that the बारtamp is always accurate.
	 */
	disable_irq = (dev->vblank_disable_immediate &&
		       drm_vblank_offdelay > 0 &&
		       !atomic_पढ़ो(&vblank->refcount));

	drm_handle_vblank_events(dev, pipe);
	drm_handle_vblank_works(vblank);

	spin_unlock_irqrestore(&dev->event_lock, irqflags);

	अगर (disable_irq)
		vblank_disable_fn(&vblank->disable_समयr);

	वापस true;
पूर्ण
EXPORT_SYMBOL(drm_handle_vblank);

/**
 * drm_crtc_handle_vblank - handle a vblank event
 * @crtc: where this event occurred
 *
 * Drivers should call this routine in their vblank पूर्णांकerrupt handlers to
 * update the vblank counter and send any संकेतs that may be pending.
 *
 * This is the native KMS version of drm_handle_vblank().
 *
 * Note that क्रम a given vblank counter value drm_crtc_handle_vblank()
 * and drm_crtc_vblank_count() or drm_crtc_vblank_count_and_समय()
 * provide a barrier: Any ग_लिखोs करोne beक्रमe calling
 * drm_crtc_handle_vblank() will be visible to callers of the later
 * functions, अगरf the vblank count is the same or a later one.
 *
 * See also &drm_vblank_crtc.count.
 *
 * Returns:
 * True अगर the event was successfully handled, false on failure.
 */
bool drm_crtc_handle_vblank(काष्ठा drm_crtc *crtc)
अणु
	वापस drm_handle_vblank(crtc->dev, drm_crtc_index(crtc));
पूर्ण
EXPORT_SYMBOL(drm_crtc_handle_vblank);

/*
 * Get crtc VBLANK count.
 *
 * \param dev DRM device
 * \param data user arguement, poपूर्णांकing to a drm_crtc_get_sequence काष्ठाure.
 * \param file_priv drm file निजी क्रम the user's खोलो file descriptor
 */

पूर्णांक drm_crtc_get_sequence_ioctl(काष्ठा drm_device *dev, व्योम *data,
				काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_vblank_crtc *vblank;
	पूर्णांक pipe;
	काष्ठा drm_crtc_get_sequence *get_seq = data;
	kसमय_प्रकार now;
	bool vblank_enabled;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	अगर (!dev->irq_enabled)
		वापस -EOPNOTSUPP;

	crtc = drm_crtc_find(dev, file_priv, get_seq->crtc_id);
	अगर (!crtc)
		वापस -ENOENT;

	pipe = drm_crtc_index(crtc);

	vblank = &dev->vblank[pipe];
	vblank_enabled = dev->vblank_disable_immediate && READ_ONCE(vblank->enabled);

	अगर (!vblank_enabled) अणु
		ret = drm_crtc_vblank_get(crtc);
		अगर (ret) अणु
			drm_dbg_core(dev,
				     "crtc %d failed to acquire vblank counter, %d\n",
				     pipe, ret);
			वापस ret;
		पूर्ण
	पूर्ण
	drm_modeset_lock(&crtc->mutex, शून्य);
	अगर (crtc->state)
		get_seq->active = crtc->state->enable;
	अन्यथा
		get_seq->active = crtc->enabled;
	drm_modeset_unlock(&crtc->mutex);
	get_seq->sequence = drm_vblank_count_and_समय(dev, pipe, &now);
	get_seq->sequence_ns = kसमय_प्रकारo_ns(now);
	अगर (!vblank_enabled)
		drm_crtc_vblank_put(crtc);
	वापस 0;
पूर्ण

/*
 * Queue a event क्रम VBLANK sequence
 *
 * \param dev DRM device
 * \param data user arguement, poपूर्णांकing to a drm_crtc_queue_sequence काष्ठाure.
 * \param file_priv drm file निजी क्रम the user's खोलो file descriptor
 */

पूर्णांक drm_crtc_queue_sequence_ioctl(काष्ठा drm_device *dev, व्योम *data,
				  काष्ठा drm_file *file_priv)
अणु
	काष्ठा drm_crtc *crtc;
	काष्ठा drm_vblank_crtc *vblank;
	पूर्णांक pipe;
	काष्ठा drm_crtc_queue_sequence *queue_seq = data;
	kसमय_प्रकार now;
	काष्ठा drm_pending_vblank_event *e;
	u32 flags;
	u64 seq;
	u64 req_seq;
	पूर्णांक ret;

	अगर (!drm_core_check_feature(dev, DRIVER_MODESET))
		वापस -EOPNOTSUPP;

	अगर (!dev->irq_enabled)
		वापस -EOPNOTSUPP;

	crtc = drm_crtc_find(dev, file_priv, queue_seq->crtc_id);
	अगर (!crtc)
		वापस -ENOENT;

	flags = queue_seq->flags;
	/* Check valid flag bits */
	अगर (flags & ~(DRM_CRTC_SEQUENCE_RELATIVE|
		      DRM_CRTC_SEQUENCE_NEXT_ON_MISS))
		वापस -EINVAL;

	pipe = drm_crtc_index(crtc);

	vblank = &dev->vblank[pipe];

	e = kzalloc(माप(*e), GFP_KERNEL);
	अगर (e == शून्य)
		वापस -ENOMEM;

	ret = drm_crtc_vblank_get(crtc);
	अगर (ret) अणु
		drm_dbg_core(dev,
			     "crtc %d failed to acquire vblank counter, %d\n",
			     pipe, ret);
		जाओ err_मुक्त;
	पूर्ण

	seq = drm_vblank_count_and_समय(dev, pipe, &now);
	req_seq = queue_seq->sequence;

	अगर (flags & DRM_CRTC_SEQUENCE_RELATIVE)
		req_seq += seq;

	अगर ((flags & DRM_CRTC_SEQUENCE_NEXT_ON_MISS) && drm_vblank_passed(seq, req_seq))
		req_seq = seq + 1;

	e->pipe = pipe;
	e->event.base.type = DRM_EVENT_CRTC_SEQUENCE;
	e->event.base.length = माप(e->event.seq);
	e->event.seq.user_data = queue_seq->user_data;

	spin_lock_irq(&dev->event_lock);

	/*
	 * drm_crtc_vblank_off() might have been called after we called
	 * drm_crtc_vblank_get(). drm_crtc_vblank_off() holds event_lock around the
	 * vblank disable, so no need क्रम further locking.  The reference from
	 * drm_crtc_vblank_get() protects against vblank disable from another source.
	 */
	अगर (!READ_ONCE(vblank->enabled)) अणु
		ret = -EINVAL;
		जाओ err_unlock;
	पूर्ण

	ret = drm_event_reserve_init_locked(dev, file_priv, &e->base,
					    &e->event.base);

	अगर (ret)
		जाओ err_unlock;

	e->sequence = req_seq;

	अगर (drm_vblank_passed(seq, req_seq)) अणु
		drm_crtc_vblank_put(crtc);
		send_vblank_event(dev, e, seq, now);
		queue_seq->sequence = seq;
	पूर्ण अन्यथा अणु
		/* drm_handle_vblank_events will call drm_vblank_put */
		list_add_tail(&e->base.link, &dev->vblank_event_list);
		queue_seq->sequence = req_seq;
	पूर्ण

	spin_unlock_irq(&dev->event_lock);
	वापस 0;

err_unlock:
	spin_unlock_irq(&dev->event_lock);
	drm_crtc_vblank_put(crtc);
err_मुक्त:
	kमुक्त(e);
	वापस ret;
पूर्ण

