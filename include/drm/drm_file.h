<शैली गुरु>
/*
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * Copyright (c) 2009-2010, Code Aurora Forum.
 * All rights reserved.
 *
 * Author: Rickard E. (Rik) Faith <faith@valinux.com>
 * Author: Gareth Hughes <gareth@valinux.com>
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

#अगर_अघोषित _DRM_खाता_H_
#घोषणा _DRM_खाता_H_

#समावेश <linux/types.h>
#समावेश <linux/completion.h>
#समावेश <linux/idr.h>

#समावेश <uapi/drm/drm.h>

#समावेश <drm/drm_prime.h>

काष्ठा dma_fence;
काष्ठा drm_file;
काष्ठा drm_device;
काष्ठा device;
काष्ठा file;

/*
 * FIXME: Not sure we want to have drm_minor here in the end, but to aव्योम
 * header include loops we need it here क्रम now.
 */

/* Note that the order of this क्रमागत is ABI (it determines
 * /dev/dri/renderD* numbers).
 */
क्रमागत drm_minor_type अणु
	DRM_MINOR_PRIMARY,
	DRM_MINOR_CONTROL,
	DRM_MINOR_RENDER,
पूर्ण;

/**
 * काष्ठा drm_minor - DRM device minor काष्ठाure
 *
 * This काष्ठाure represents a DRM minor number क्रम device nodes in /dev.
 * Entirely opaque to drivers and should never be inspected directly by drivers.
 * Drivers instead should only पूर्णांकeract with &काष्ठा drm_file and of course
 * &काष्ठा drm_device, which is also where driver-निजी data and resources can
 * be attached to.
 */
काष्ठा drm_minor अणु
	/* निजी: */
	पूर्णांक index;			/* Minor device number */
	पूर्णांक type;                       /* Control or render */
	काष्ठा device *kdev;		/* Linux device */
	काष्ठा drm_device *dev;

	काष्ठा dentry *debugfs_root;

	काष्ठा list_head debugfs_list;
	काष्ठा mutex debugfs_lock; /* Protects debugfs_list. */
पूर्ण;

/**
 * काष्ठा drm_pending_event - Event queued up क्रम userspace to पढ़ो
 *
 * This represents a DRM event. Drivers can use this as a generic completion
 * mechanism, which supports kernel-पूर्णांकernal &काष्ठा completion, &काष्ठा dma_fence
 * and also the DRM-specअगरic &काष्ठा drm_event delivery mechanism.
 */
काष्ठा drm_pending_event अणु
	/**
	 * @completion:
	 *
	 * Optional poपूर्णांकer to a kernel पूर्णांकernal completion संकेतled when
	 * drm_send_event() is called, useful to पूर्णांकernally synchronize with
	 * nonblocking operations.
	 */
	काष्ठा completion *completion;

	/**
	 * @completion_release:
	 *
	 * Optional callback currently only used by the atomic modeset helpers
	 * to clean up the reference count क्रम the काष्ठाure @completion is
	 * stored in.
	 */
	व्योम (*completion_release)(काष्ठा completion *completion);

	/**
	 * @event:
	 *
	 * Poपूर्णांकer to the actual event that should be sent to userspace to be
	 * पढ़ो using drm_पढ़ो(). Can be optional, since nowadays events are
	 * also used to संकेत kernel पूर्णांकernal thपढ़ोs with @completion or DMA
	 * transactions using @fence.
	 */
	काष्ठा drm_event *event;

	/**
	 * @fence:
	 *
	 * Optional DMA fence to unblock other hardware transactions which
	 * depend upon the nonblocking DRM operation this event represents.
	 */
	काष्ठा dma_fence *fence;

	/**
	 * @file_priv:
	 *
	 * &काष्ठा drm_file where @event should be delivered to. Only set when
	 * @event is set.
	 */
	काष्ठा drm_file *file_priv;

	/**
	 * @link:
	 *
	 * Double-linked list to keep track of this event. Can be used by the
	 * driver up to the poपूर्णांक when it calls drm_send_event(), after that
	 * this list entry is owned by the core क्रम its own book-keeping.
	 */
	काष्ठा list_head link;

	/**
	 * @pending_link:
	 *
	 * Entry on &drm_file.pending_event_list, to keep track of all pending
	 * events क्रम @file_priv, to allow correct unwinding of them when
	 * userspace बंदs the file beक्रमe the event is delivered.
	 */
	काष्ठा list_head pending_link;
पूर्ण;

/**
 * काष्ठा drm_file - DRM file निजी data
 *
 * This काष्ठाure tracks DRM state per खोलो file descriptor.
 */
काष्ठा drm_file अणु
	/**
	 * @authenticated:
	 *
	 * Whether the client is allowed to submit rendering, which क्रम legacy
	 * nodes means it must be authenticated.
	 *
	 * See also the :ref:`section on primary nodes and authentication
	 * <drm_primary_node>`.
	 */
	bool authenticated;

	/**
	 * @stereo_allowed:
	 *
	 * True when the client has asked us to expose stereo 3D mode flags.
	 */
	bool stereo_allowed;

	/**
	 * @universal_planes:
	 *
	 * True अगर client understands CRTC primary planes and cursor planes
	 * in the plane list. Automatically set when @atomic is set.
	 */
	bool universal_planes;

	/** @atomic: True अगर client understands atomic properties. */
	bool atomic;

	/**
	 * @aspect_ratio_allowed:
	 *
	 * True, अगर client can handle picture aspect ratios, and has requested
	 * to pass this inक्रमmation aदीर्घ with the mode.
	 */
	bool aspect_ratio_allowed;

	/**
	 * @ग_लिखोback_connectors:
	 *
	 * True अगर client understands ग_लिखोback connectors
	 */
	bool ग_लिखोback_connectors;

	/**
	 * @was_master:
	 *
	 * This client has or had, master capability. Protected by काष्ठा
	 * &drm_device.master_mutex.
	 *
	 * This is used to ensure that CAP_SYS_ADMIN is not enक्रमced, अगर the
	 * client is or was master in the past.
	 */
	bool was_master;

	/**
	 * @is_master:
	 *
	 * This client is the creator of @master. Protected by काष्ठा
	 * &drm_device.master_mutex.
	 *
	 * See also the :ref:`section on primary nodes and authentication
	 * <drm_primary_node>`.
	 */
	bool is_master;

	/**
	 * @master:
	 *
	 * Master this node is currently associated with. Only relevant अगर
	 * drm_is_primary_client() वापसs true. Note that this only
	 * matches &drm_device.master अगर the master is the currently active one.
	 *
	 * See also @authentication and @is_master and the :ref:`section on
	 * primary nodes and authentication <drm_primary_node>`.
	 */
	काष्ठा drm_master *master;

	/** @pid: Process that खोलोed this file. */
	काष्ठा pid *pid;

	/** @magic: Authentication magic, see @authenticated. */
	drm_magic_t magic;

	/**
	 * @lhead:
	 *
	 * List of all खोलो files of a DRM device, linked पूर्णांकo
	 * &drm_device.filelist. Protected by &drm_device.filelist_mutex.
	 */
	काष्ठा list_head lhead;

	/** @minor: &काष्ठा drm_minor क्रम this file. */
	काष्ठा drm_minor *minor;

	/**
	 * @object_idr:
	 *
	 * Mapping of mm object handles to object poपूर्णांकers. Used by the GEM
	 * subप्रणाली. Protected by @table_lock.
	 */
	काष्ठा idr object_idr;

	/** @table_lock: Protects @object_idr. */
	spinlock_t table_lock;

	/** @syncobj_idr: Mapping of sync object handles to object poपूर्णांकers. */
	काष्ठा idr syncobj_idr;
	/** @syncobj_table_lock: Protects @syncobj_idr. */
	spinlock_t syncobj_table_lock;

	/** @filp: Poपूर्णांकer to the core file काष्ठाure. */
	काष्ठा file *filp;

	/**
	 * @driver_priv:
	 *
	 * Optional poपूर्णांकer क्रम driver निजी data. Can be allocated in
	 * &drm_driver.खोलो and should be मुक्तd in &drm_driver.postबंद.
	 */
	व्योम *driver_priv;

	/**
	 * @fbs:
	 *
	 * List of &काष्ठा drm_framebuffer associated with this file, using the
	 * &drm_framebuffer.filp_head entry.
	 *
	 * Protected by @fbs_lock. Note that the @fbs list holds a reference on
	 * the framebuffer object to prevent it from unसमयly disappearing.
	 */
	काष्ठा list_head fbs;

	/** @fbs_lock: Protects @fbs. */
	काष्ठा mutex fbs_lock;

	/**
	 * @blobs:
	 *
	 * User-created blob properties; this retains a reference on the
	 * property.
	 *
	 * Protected by @drm_mode_config.blob_lock;
	 */
	काष्ठा list_head blobs;

	/** @event_रुको: Waitqueue क्रम new events added to @event_list. */
	रुको_queue_head_t event_रुको;

	/**
	 * @pending_event_list:
	 *
	 * List of pending &काष्ठा drm_pending_event, used to clean up pending
	 * events in हाल this file माला_लो बंदd beक्रमe the event is संकेतled.
	 * Uses the &drm_pending_event.pending_link entry.
	 *
	 * Protect by &drm_device.event_lock.
	 */
	काष्ठा list_head pending_event_list;

	/**
	 * @event_list:
	 *
	 * List of &काष्ठा drm_pending_event, पढ़ोy क्रम delivery to userspace
	 * through drm_पढ़ो(). Uses the &drm_pending_event.link entry.
	 *
	 * Protect by &drm_device.event_lock.
	 */
	काष्ठा list_head event_list;

	/**
	 * @event_space:
	 *
	 * Available event space to prevent userspace from
	 * exhausting kernel memory. Currently limited to the fairly arbitrary
	 * value of 4KB.
	 */
	पूर्णांक event_space;

	/** @event_पढ़ो_lock: Serializes drm_पढ़ो(). */
	काष्ठा mutex event_पढ़ो_lock;

	/**
	 * @prime:
	 *
	 * Per-file buffer caches used by the PRIME buffer sharing code.
	 */
	काष्ठा drm_prime_file_निजी prime;

	/* निजी: */
#अगर IS_ENABLED(CONFIG_DRM_LEGACY)
	अचिन्हित दीर्घ lock_count; /* DRI1 legacy lock count */
#पूर्ण_अगर
पूर्ण;

/**
 * drm_is_primary_client - is this an खोलो file of the primary node
 * @file_priv: DRM file
 *
 * Returns true अगर this is an खोलो file of the primary node, i.e.
 * &drm_file.minor of @file_priv is a primary minor.
 *
 * See also the :ref:`section on primary nodes and authentication
 * <drm_primary_node>`.
 */
अटल अंतरभूत bool drm_is_primary_client(स्थिर काष्ठा drm_file *file_priv)
अणु
	वापस file_priv->minor->type == DRM_MINOR_PRIMARY;
पूर्ण

/**
 * drm_is_render_client - is this an खोलो file of the render node
 * @file_priv: DRM file
 *
 * Returns true अगर this is an खोलो file of the render node, i.e.
 * &drm_file.minor of @file_priv is a render minor.
 *
 * See also the :ref:`section on render nodes <drm_render_node>`.
 */
अटल अंतरभूत bool drm_is_render_client(स्थिर काष्ठा drm_file *file_priv)
अणु
	वापस file_priv->minor->type == DRM_MINOR_RENDER;
पूर्ण

पूर्णांक drm_खोलो(काष्ठा inode *inode, काष्ठा file *filp);
sमाप_प्रकार drm_पढ़ो(काष्ठा file *filp, अक्षर __user *buffer,
		 माप_प्रकार count, loff_t *offset);
पूर्णांक drm_release(काष्ठा inode *inode, काष्ठा file *filp);
पूर्णांक drm_release_noglobal(काष्ठा inode *inode, काष्ठा file *filp);
__poll_t drm_poll(काष्ठा file *filp, काष्ठा poll_table_काष्ठा *रुको);
पूर्णांक drm_event_reserve_init_locked(काष्ठा drm_device *dev,
				  काष्ठा drm_file *file_priv,
				  काष्ठा drm_pending_event *p,
				  काष्ठा drm_event *e);
पूर्णांक drm_event_reserve_init(काष्ठा drm_device *dev,
			   काष्ठा drm_file *file_priv,
			   काष्ठा drm_pending_event *p,
			   काष्ठा drm_event *e);
व्योम drm_event_cancel_मुक्त(काष्ठा drm_device *dev,
			   काष्ठा drm_pending_event *p);
व्योम drm_send_event_locked(काष्ठा drm_device *dev, काष्ठा drm_pending_event *e);
व्योम drm_send_event(काष्ठा drm_device *dev, काष्ठा drm_pending_event *e);
व्योम drm_send_event_बारtamp_locked(काष्ठा drm_device *dev,
				     काष्ठा drm_pending_event *e,
				     kसमय_प्रकार बारtamp);

काष्ठा file *mock_drm_getfile(काष्ठा drm_minor *minor, अचिन्हित पूर्णांक flags);

#अगर_घोषित CONFIG_MMU
काष्ठा drm_vma_offset_manager;
अचिन्हित दीर्घ drm_get_unmapped_area(काष्ठा file *file,
				    अचिन्हित दीर्घ uaddr, अचिन्हित दीर्घ len,
				    अचिन्हित दीर्घ pgoff, अचिन्हित दीर्घ flags,
				    काष्ठा drm_vma_offset_manager *mgr);
#पूर्ण_अगर /* CONFIG_MMU */


#पूर्ण_अगर /* _DRM_खाता_H_ */
