<शैली गुरु>
/* SPDX-License-Identअगरier: MIT */

#अगर_अघोषित _DRM_VBLANK_WORK_H_
#घोषणा _DRM_VBLANK_WORK_H_

#समावेश <linux/kthपढ़ो.h>

काष्ठा drm_crtc;

/**
 * काष्ठा drm_vblank_work - A delayed work item which delays until a target
 * vblank passes, and then executes at realसमय priority outside of IRQ
 * context.
 *
 * See also:
 * drm_vblank_work_schedule()
 * drm_vblank_work_init()
 * drm_vblank_work_cancel_sync()
 * drm_vblank_work_flush()
 */
काष्ठा drm_vblank_work अणु
	/**
	 * @base: The base &kthपढ़ो_work item which will be executed by
	 * &drm_vblank_crtc.worker. Drivers should not पूर्णांकeract with this
	 * directly, and instead rely on drm_vblank_work_init() to initialize
	 * this.
	 */
	काष्ठा kthपढ़ो_work base;

	/**
	 * @vblank: A poपूर्णांकer to &drm_vblank_crtc this work item beदीर्घs to.
	 */
	काष्ठा drm_vblank_crtc *vblank;

	/**
	 * @count: The target vblank this work will execute on. Drivers should
	 * not modअगरy this value directly, and instead use
	 * drm_vblank_work_schedule()
	 */
	u64 count;

	/**
	 * @cancelling: The number of drm_vblank_work_cancel_sync() calls that
	 * are currently running. A work item cannot be rescheduled until all
	 * calls have finished.
	 */
	पूर्णांक cancelling;

	/**
	 * @node: The position of this work item in
	 * &drm_vblank_crtc.pending_work.
	 */
	काष्ठा list_head node;
पूर्ण;

/**
 * to_drm_vblank_work - Retrieve the respective &drm_vblank_work item from a
 * &kthपढ़ो_work
 * @_work: The &kthपढ़ो_work embedded inside a &drm_vblank_work
 */
#घोषणा to_drm_vblank_work(_work) \
	container_of((_work), काष्ठा drm_vblank_work, base)

पूर्णांक drm_vblank_work_schedule(काष्ठा drm_vblank_work *work,
			     u64 count, bool nextonmiss);
व्योम drm_vblank_work_init(काष्ठा drm_vblank_work *work, काष्ठा drm_crtc *crtc,
			  व्योम (*func)(काष्ठा kthपढ़ो_work *work));
bool drm_vblank_work_cancel_sync(काष्ठा drm_vblank_work *work);
व्योम drm_vblank_work_flush(काष्ठा drm_vblank_work *work);

#पूर्ण_अगर /* !_DRM_VBLANK_WORK_H_ */
