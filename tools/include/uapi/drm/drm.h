<शैली गुरु>
/*
 * Header क्रम the Direct Rendering Manager
 *
 * Author: Rickard E. (Rik) Faith <faith@valinux.com>
 *
 * Acknowledgments:
 * Dec 1999, Riअक्षरd Henderson <rth@twiddle.net>, move to generic cmpxchg.
 */

/*
 * Copyright 1999 Precision Insight, Inc., Cedar Park, Texas.
 * Copyright 2000 VA Linux Systems, Inc., Sunnyvale, Calअगरornia.
 * All rights reserved.
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

#अगर_अघोषित _DRM_H_
#घोषणा _DRM_H_

#अगर defined(__KERNEL__)

#समावेश <linux/types.h>
#समावेश <यंत्र/ioctl.h>
प्रकार अचिन्हित पूर्णांक drm_handle_t;

#या_अगर defined(__linux__)

#समावेश <linux/types.h>
#समावेश <यंत्र/ioctl.h>
प्रकार अचिन्हित पूर्णांक drm_handle_t;

#अन्यथा /* One of the BSDs */

#समावेश <मानक_निवेशt.h>
#समावेश <sys/ioccom.h>
#समावेश <sys/types.h>
प्रकार पूर्णांक8_t   __s8;
प्रकार uपूर्णांक8_t  __u8;
प्रकार पूर्णांक16_t  __s16;
प्रकार uपूर्णांक16_t __u16;
प्रकार पूर्णांक32_t  __s32;
प्रकार uपूर्णांक32_t __u32;
प्रकार पूर्णांक64_t  __s64;
प्रकार uपूर्णांक64_t __u64;
प्रकार माप_प्रकार   __kernel_माप_प्रकार;
प्रकार अचिन्हित दीर्घ drm_handle_t;

#पूर्ण_अगर

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

#घोषणा DRM_NAME	"drm"	  /**< Name in kernel, /dev, and /proc */
#घोषणा DRM_MIN_ORDER	5	  /**< At least 2^5 bytes = 32 bytes */
#घोषणा DRM_MAX_ORDER	22	  /**< Up to 2^22 bytes = 4MB */
#घोषणा DRM_RAM_PERCENT 10	  /**< How much प्रणाली ram can we lock? */

#घोषणा _DRM_LOCK_HELD	0x80000000U /**< Hardware lock is held */
#घोषणा _DRM_LOCK_CONT	0x40000000U /**< Hardware lock is contended */
#घोषणा _DRM_LOCK_IS_HELD(lock)	   ((lock) & _DRM_LOCK_HELD)
#घोषणा _DRM_LOCK_IS_CONT(lock)	   ((lock) & _DRM_LOCK_CONT)
#घोषणा _DRM_LOCKING_CONTEXT(lock) ((lock) & ~(_DRM_LOCK_HELD|_DRM_LOCK_CONT))

प्रकार अचिन्हित पूर्णांक drm_context_t;
प्रकार अचिन्हित पूर्णांक drm_drawable_t;
प्रकार अचिन्हित पूर्णांक drm_magic_t;

/*
 * Cliprect.
 *
 * \warning: If you change this काष्ठाure, make sure you change
 * XF86DRIClipRectRec in the server as well
 *
 * \नote KW: Actually it's illegal to change either क्रम
 * backwards-compatibility reasons.
 */
काष्ठा drm_clip_rect अणु
	अचिन्हित लघु x1;
	अचिन्हित लघु y1;
	अचिन्हित लघु x2;
	अचिन्हित लघु y2;
पूर्ण;

/*
 * Drawable inक्रमmation.
 */
काष्ठा drm_drawable_info अणु
	अचिन्हित पूर्णांक num_rects;
	काष्ठा drm_clip_rect *rects;
पूर्ण;

/*
 * Texture region,
 */
काष्ठा drm_tex_region अणु
	अचिन्हित अक्षर next;
	अचिन्हित अक्षर prev;
	अचिन्हित अक्षर in_use;
	अचिन्हित अक्षर padding;
	अचिन्हित पूर्णांक age;
पूर्ण;

/*
 * Hardware lock.
 *
 * The lock काष्ठाure is a simple cache-line aligned पूर्णांकeger.  To aव्योम
 * processor bus contention on a multiprocessor प्रणाली, there should not be any
 * other data stored in the same cache line.
 */
काष्ठा drm_hw_lock अणु
	__अस्थिर__ अचिन्हित पूर्णांक lock;		/**< lock variable */
	अक्षर padding[60];			/**< Pad to cache line */
पूर्ण;

/*
 * DRM_IOCTL_VERSION ioctl argument type.
 *
 * \sa drmGetVersion().
 */
काष्ठा drm_version अणु
	पूर्णांक version_major;	  /**< Major version */
	पूर्णांक version_minor;	  /**< Minor version */
	पूर्णांक version_patchlevel;	  /**< Patch level */
	__kernel_माप_प्रकार name_len;	  /**< Length of name buffer */
	अक्षर __user *name;	  /**< Name of driver */
	__kernel_माप_प्रकार date_len;	  /**< Length of date buffer */
	अक्षर __user *date;	  /**< User-space buffer to hold date */
	__kernel_माप_प्रकार desc_len;	  /**< Length of desc buffer */
	अक्षर __user *desc;	  /**< User-space buffer to hold desc */
पूर्ण;

/*
 * DRM_IOCTL_GET_UNIQUE ioctl argument type.
 *
 * \sa drmGetBusid() and drmSetBusId().
 */
काष्ठा drm_unique अणु
	__kernel_माप_प्रकार unique_len;	  /**< Length of unique */
	अक्षर __user *unique;	  /**< Unique name क्रम driver instantiation */
पूर्ण;

काष्ठा drm_list अणु
	पूर्णांक count;		  /**< Length of user-space काष्ठाures */
	काष्ठा drm_version __user *version;
पूर्ण;

काष्ठा drm_block अणु
	पूर्णांक unused;
पूर्ण;

/*
 * DRM_IOCTL_CONTROL ioctl argument type.
 *
 * \sa drmCtlInstHandler() and drmCtlUninstHandler().
 */
काष्ठा drm_control अणु
	क्रमागत अणु
		DRM_ADD_COMMAND,
		DRM_RM_COMMAND,
		DRM_INST_HANDLER,
		DRM_UNINST_HANDLER
	पूर्ण func;
	पूर्णांक irq;
पूर्ण;

/*
 * Type of memory to map.
 */
क्रमागत drm_map_type अणु
	_DRM_FRAME_BUFFER = 0,	  /**< WC (no caching), no core dump */
	_DRM_REGISTERS = 1,	  /**< no caching, no core dump */
	_DRM_SHM = 2,		  /**< shared, cached */
	_DRM_AGP = 3,		  /**< AGP/GART */
	_DRM_SCATTER_GATHER = 4,  /**< Scatter/gather memory क्रम PCI DMA */
	_DRM_CONSISTENT = 5	  /**< Consistent memory क्रम PCI DMA */
पूर्ण;

/*
 * Memory mapping flags.
 */
क्रमागत drm_map_flags अणु
	_DRM_RESTRICTED = 0x01,	     /**< Cannot be mapped to user-भव */
	_DRM_READ_ONLY = 0x02,
	_DRM_LOCKED = 0x04,	     /**< shared, cached, locked */
	_DRM_KERNEL = 0x08,	     /**< kernel requires access */
	_DRM_WRITE_COMBINING = 0x10, /**< use ग_लिखो-combining अगर available */
	_DRM_CONTAINS_LOCK = 0x20,   /**< SHM page that contains lock */
	_DRM_REMOVABLE = 0x40,	     /**< Removable mapping */
	_DRM_DRIVER = 0x80	     /**< Managed by driver */
पूर्ण;

काष्ठा drm_ctx_priv_map अणु
	अचिन्हित पूर्णांक ctx_id;	 /**< Context requesting निजी mapping */
	व्योम *handle;		 /**< Handle of map */
पूर्ण;

/*
 * DRM_IOCTL_GET_MAP, DRM_IOCTL_ADD_MAP and DRM_IOCTL_RM_MAP ioctls
 * argument type.
 *
 * \sa drmAddMap().
 */
काष्ठा drm_map अणु
	अचिन्हित दीर्घ offset;	 /**< Requested physical address (0 क्रम SAREA)*/
	अचिन्हित दीर्घ size;	 /**< Requested physical size (bytes) */
	क्रमागत drm_map_type type;	 /**< Type of memory to map */
	क्रमागत drm_map_flags flags;	 /**< Flags */
	व्योम *handle;		 /**< User-space: "Handle" to pass to mmap() */
				 /**< Kernel-space: kernel-भव address */
	पूर्णांक mtrr;		 /**< MTRR slot used */
	/*   Private data */
पूर्ण;

/*
 * DRM_IOCTL_GET_CLIENT ioctl argument type.
 */
काष्ठा drm_client अणु
	पूर्णांक idx;		/**< Which client desired? */
	पूर्णांक auth;		/**< Is client authenticated? */
	अचिन्हित दीर्घ pid;	/**< Process ID */
	अचिन्हित दीर्घ uid;	/**< User ID */
	अचिन्हित दीर्घ magic;	/**< Magic */
	अचिन्हित दीर्घ iocs;	/**< Ioctl count */
पूर्ण;

क्रमागत drm_stat_type अणु
	_DRM_STAT_LOCK,
	_DRM_STAT_OPENS,
	_DRM_STAT_CLOSES,
	_DRM_STAT_IOCTLS,
	_DRM_STAT_LOCKS,
	_DRM_STAT_UNLOCKS,
	_DRM_STAT_VALUE,	/**< Generic value */
	_DRM_STAT_BYTE,		/**< Generic byte counter (1024bytes/K) */
	_DRM_STAT_COUNT,	/**< Generic non-byte counter (1000/k) */

	_DRM_STAT_IRQ,		/**< IRQ */
	_DRM_STAT_PRIMARY,	/**< Primary DMA bytes */
	_DRM_STAT_SECONDARY,	/**< Secondary DMA bytes */
	_DRM_STAT_DMA,		/**< DMA */
	_DRM_STAT_SPECIAL,	/**< Special DMA (e.g., priority or polled) */
	_DRM_STAT_MISSED	/**< Missed DMA opportunity */
	    /* Add to the *END* of the list */
पूर्ण;

/*
 * DRM_IOCTL_GET_STATS ioctl argument type.
 */
काष्ठा drm_stats अणु
	अचिन्हित दीर्घ count;
	काष्ठा अणु
		अचिन्हित दीर्घ value;
		क्रमागत drm_stat_type type;
	पूर्ण data[15];
पूर्ण;

/*
 * Hardware locking flags.
 */
क्रमागत drm_lock_flags अणु
	_DRM_LOCK_READY = 0x01,	     /**< Wait until hardware is पढ़ोy क्रम DMA */
	_DRM_LOCK_QUIESCENT = 0x02,  /**< Wait until hardware quiescent */
	_DRM_LOCK_FLUSH = 0x04,	     /**< Flush this context's DMA queue first */
	_DRM_LOCK_FLUSH_ALL = 0x08,  /**< Flush all DMA queues first */
	/* These *HALT* flags aren't supported yet
	   -- they will be used to support the
	   full-screen DGA-like mode. */
	_DRM_HALT_ALL_QUEUES = 0x10, /**< Halt all current and future queues */
	_DRM_HALT_CUR_QUEUES = 0x20  /**< Halt all current queues */
पूर्ण;

/*
 * DRM_IOCTL_LOCK, DRM_IOCTL_UNLOCK and DRM_IOCTL_FINISH ioctl argument type.
 *
 * \sa drmGetLock() and drmUnlock().
 */
काष्ठा drm_lock अणु
	पूर्णांक context;
	क्रमागत drm_lock_flags flags;
पूर्ण;

/*
 * DMA flags
 *
 * \warning
 * These values \e must match xf86drm.h.
 *
 * \sa drm_dma.
 */
क्रमागत drm_dma_flags अणु
	/* Flags क्रम DMA buffer dispatch */
	_DRM_DMA_BLOCK = 0x01,	      /**<
				       * Block until buffer dispatched.
				       *
				       * \नote The buffer may not yet have
				       * been processed by the hardware --
				       * getting a hardware lock with the
				       * hardware quiescent will ensure
				       * that the buffer has been
				       * processed.
				       */
	_DRM_DMA_WHILE_LOCKED = 0x02, /**< Dispatch जबतक lock held */
	_DRM_DMA_PRIORITY = 0x04,     /**< High priority dispatch */

	/* Flags क्रम DMA buffer request */
	_DRM_DMA_WAIT = 0x10,	      /**< Wait क्रम मुक्त buffers */
	_DRM_DMA_SMALLER_OK = 0x20,   /**< Smaller-than-requested buffers OK */
	_DRM_DMA_LARGER_OK = 0x40     /**< Larger-than-requested buffers OK */
पूर्ण;

/*
 * DRM_IOCTL_ADD_BUFS and DRM_IOCTL_MARK_BUFS ioctl argument type.
 *
 * \sa drmAddBufs().
 */
काष्ठा drm_buf_desc अणु
	पूर्णांक count;		 /**< Number of buffers of this size */
	पूर्णांक size;		 /**< Size in bytes */
	पूर्णांक low_mark;		 /**< Low water mark */
	पूर्णांक high_mark;		 /**< High water mark */
	क्रमागत अणु
		_DRM_PAGE_ALIGN = 0x01,	/**< Align on page boundaries क्रम DMA */
		_DRM_AGP_BUFFER = 0x02,	/**< Buffer is in AGP space */
		_DRM_SG_BUFFER = 0x04,	/**< Scatter/gather memory buffer */
		_DRM_FB_BUFFER = 0x08,	/**< Buffer is in frame buffer */
		_DRM_PCI_BUFFER_RO = 0x10 /**< Map PCI DMA buffer पढ़ो-only */
	पूर्ण flags;
	अचिन्हित दीर्घ agp_start; /**<
				  * Start address of where the AGP buffers are
				  * in the AGP aperture
				  */
पूर्ण;

/*
 * DRM_IOCTL_INFO_BUFS ioctl argument type.
 */
काष्ठा drm_buf_info अणु
	पूर्णांक count;		/**< Entries in list */
	काष्ठा drm_buf_desc __user *list;
पूर्ण;

/*
 * DRM_IOCTL_FREE_BUFS ioctl argument type.
 */
काष्ठा drm_buf_मुक्त अणु
	पूर्णांक count;
	पूर्णांक __user *list;
पूर्ण;

/*
 * Buffer inक्रमmation
 *
 * \sa drm_buf_map.
 */
काष्ठा drm_buf_pub अणु
	पूर्णांक idx;		       /**< Index पूर्णांकo the master buffer list */
	पूर्णांक total;		       /**< Buffer size */
	पूर्णांक used;		       /**< Amount of buffer in use (क्रम DMA) */
	व्योम __user *address;	       /**< Address of buffer */
पूर्ण;

/*
 * DRM_IOCTL_MAP_BUFS ioctl argument type.
 */
काष्ठा drm_buf_map अणु
	पूर्णांक count;		/**< Length of the buffer list */
#अगर_घोषित __cplusplus
	व्योम __user *virt;
#अन्यथा
	व्योम __user *भव;		/**< Mmap'd area in user-भव */
#पूर्ण_अगर
	काष्ठा drm_buf_pub __user *list;	/**< Buffer inक्रमmation */
पूर्ण;

/*
 * DRM_IOCTL_DMA ioctl argument type.
 *
 * Indices here refer to the offset पूर्णांकo the buffer list in drm_buf_get.
 *
 * \sa drmDMA().
 */
काष्ठा drm_dma अणु
	पूर्णांक context;			  /**< Context handle */
	पूर्णांक send_count;			  /**< Number of buffers to send */
	पूर्णांक __user *send_indices;	  /**< List of handles to buffers */
	पूर्णांक __user *send_sizes;		  /**< Lengths of data to send */
	क्रमागत drm_dma_flags flags;	  /**< Flags */
	पूर्णांक request_count;		  /**< Number of buffers requested */
	पूर्णांक request_size;		  /**< Desired size क्रम buffers */
	पूर्णांक __user *request_indices;	  /**< Buffer inक्रमmation */
	पूर्णांक __user *request_sizes;
	पूर्णांक granted_count;		  /**< Number of buffers granted */
पूर्ण;

क्रमागत drm_ctx_flags अणु
	_DRM_CONTEXT_PRESERVED = 0x01,
	_DRM_CONTEXT_2DONLY = 0x02
पूर्ण;

/*
 * DRM_IOCTL_ADD_CTX ioctl argument type.
 *
 * \sa drmCreateContext() and drmDestroyContext().
 */
काष्ठा drm_ctx अणु
	drm_context_t handle;
	क्रमागत drm_ctx_flags flags;
पूर्ण;

/*
 * DRM_IOCTL_RES_CTX ioctl argument type.
 */
काष्ठा drm_ctx_res अणु
	पूर्णांक count;
	काष्ठा drm_ctx __user *contexts;
पूर्ण;

/*
 * DRM_IOCTL_ADD_DRAW and DRM_IOCTL_RM_DRAW ioctl argument type.
 */
काष्ठा drm_draw अणु
	drm_drawable_t handle;
पूर्ण;

/*
 * DRM_IOCTL_UPDATE_DRAW ioctl argument type.
 */
प्रकार क्रमागत अणु
	DRM_DRAWABLE_CLIPRECTS
पूर्ण drm_drawable_info_type_t;

काष्ठा drm_update_draw अणु
	drm_drawable_t handle;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक num;
	अचिन्हित दीर्घ दीर्घ data;
पूर्ण;

/*
 * DRM_IOCTL_GET_MAGIC and DRM_IOCTL_AUTH_MAGIC ioctl argument type.
 */
काष्ठा drm_auth अणु
	drm_magic_t magic;
पूर्ण;

/*
 * DRM_IOCTL_IRQ_BUSID ioctl argument type.
 *
 * \sa drmGetInterruptFromBusID().
 */
काष्ठा drm_irq_busid अणु
	पूर्णांक irq;	/**< IRQ number */
	पूर्णांक busnum;	/**< bus number */
	पूर्णांक devnum;	/**< device number */
	पूर्णांक funcnum;	/**< function number */
पूर्ण;

क्रमागत drm_vblank_seq_type अणु
	_DRM_VBLANK_ABSOLUTE = 0x0,	/**< Wait क्रम specअगरic vblank sequence number */
	_DRM_VBLANK_RELATIVE = 0x1,	/**< Wait क्रम given number of vblanks */
	/* bits 1-6 are reserved क्रम high crtcs */
	_DRM_VBLANK_HIGH_CRTC_MASK = 0x0000003e,
	_DRM_VBLANK_EVENT = 0x4000000,   /**< Send event instead of blocking */
	_DRM_VBLANK_FLIP = 0x8000000,   /**< Scheduled buffer swap should flip */
	_DRM_VBLANK_NEXTONMISS = 0x10000000,	/**< If missed, रुको क्रम next vblank */
	_DRM_VBLANK_SECONDARY = 0x20000000,	/**< Secondary display controller */
	_DRM_VBLANK_SIGNAL = 0x40000000	/**< Send संकेत instead of blocking, unsupported */
पूर्ण;
#घोषणा _DRM_VBLANK_HIGH_CRTC_SHIFT 1

#घोषणा _DRM_VBLANK_TYPES_MASK (_DRM_VBLANK_ABSOLUTE | _DRM_VBLANK_RELATIVE)
#घोषणा _DRM_VBLANK_FLAGS_MASK (_DRM_VBLANK_EVENT | _DRM_VBLANK_SIGNAL | \
				_DRM_VBLANK_SECONDARY | _DRM_VBLANK_NEXTONMISS)

काष्ठा drm_रुको_vblank_request अणु
	क्रमागत drm_vblank_seq_type type;
	अचिन्हित पूर्णांक sequence;
	अचिन्हित दीर्घ संकेत;
पूर्ण;

काष्ठा drm_रुको_vblank_reply अणु
	क्रमागत drm_vblank_seq_type type;
	अचिन्हित पूर्णांक sequence;
	दीर्घ tval_sec;
	दीर्घ tval_usec;
पूर्ण;

/*
 * DRM_IOCTL_WAIT_VBLANK ioctl argument type.
 *
 * \sa drmWaitVBlank().
 */
जोड़ drm_रुको_vblank अणु
	काष्ठा drm_रुको_vblank_request request;
	काष्ठा drm_रुको_vblank_reply reply;
पूर्ण;

#घोषणा _DRM_PRE_MODESET 1
#घोषणा _DRM_POST_MODESET 2

/*
 * DRM_IOCTL_MODESET_CTL ioctl argument type
 *
 * \sa drmModesetCtl().
 */
काष्ठा drm_modeset_ctl अणु
	__u32 crtc;
	__u32 cmd;
पूर्ण;

/*
 * DRM_IOCTL_AGP_ENABLE ioctl argument type.
 *
 * \sa drmAgpEnable().
 */
काष्ठा drm_agp_mode अणु
	अचिन्हित दीर्घ mode;	/**< AGP mode */
पूर्ण;

/*
 * DRM_IOCTL_AGP_ALLOC and DRM_IOCTL_AGP_FREE ioctls argument type.
 *
 * \sa drmAgpAlloc() and drmAgpFree().
 */
काष्ठा drm_agp_buffer अणु
	अचिन्हित दीर्घ size;	/**< In bytes -- will round to page boundary */
	अचिन्हित दीर्घ handle;	/**< Used क्रम binding / unbinding */
	अचिन्हित दीर्घ type;	/**< Type of memory to allocate */
	अचिन्हित दीर्घ physical;	/**< Physical used by i810 */
पूर्ण;

/*
 * DRM_IOCTL_AGP_BIND and DRM_IOCTL_AGP_UNBIND ioctls argument type.
 *
 * \sa drmAgpBind() and drmAgpUnbind().
 */
काष्ठा drm_agp_binding अणु
	अचिन्हित दीर्घ handle;	/**< From drm_agp_buffer */
	अचिन्हित दीर्घ offset;	/**< In bytes -- will round to page boundary */
पूर्ण;

/*
 * DRM_IOCTL_AGP_INFO ioctl argument type.
 *
 * \sa drmAgpVersionMajor(), drmAgpVersionMinor(), drmAgpGetMode(),
 * drmAgpBase(), drmAgpSize(), drmAgpMemoryUsed(), drmAgpMemoryAvail(),
 * drmAgpVenकरोrId() and drmAgpDeviceId().
 */
काष्ठा drm_agp_info अणु
	पूर्णांक agp_version_major;
	पूर्णांक agp_version_minor;
	अचिन्हित दीर्घ mode;
	अचिन्हित दीर्घ aperture_base;	/* physical address */
	अचिन्हित दीर्घ aperture_size;	/* bytes */
	अचिन्हित दीर्घ memory_allowed;	/* bytes */
	अचिन्हित दीर्घ memory_used;

	/* PCI inक्रमmation */
	अचिन्हित लघु id_venकरोr;
	अचिन्हित लघु id_device;
पूर्ण;

/*
 * DRM_IOCTL_SG_ALLOC ioctl argument type.
 */
काष्ठा drm_scatter_gather अणु
	अचिन्हित दीर्घ size;	/**< In bytes -- will round to page boundary */
	अचिन्हित दीर्घ handle;	/**< Used क्रम mapping / unmapping */
पूर्ण;

/*
 * DRM_IOCTL_SET_VERSION ioctl argument type.
 */
काष्ठा drm_set_version अणु
	पूर्णांक drm_di_major;
	पूर्णांक drm_di_minor;
	पूर्णांक drm_dd_major;
	पूर्णांक drm_dd_minor;
पूर्ण;

/* DRM_IOCTL_GEM_CLOSE ioctl argument type */
काष्ठा drm_gem_बंद अणु
	/** Handle of the object to be बंदd. */
	__u32 handle;
	__u32 pad;
पूर्ण;

/* DRM_IOCTL_GEM_FLINK ioctl argument type */
काष्ठा drm_gem_flink अणु
	/** Handle क्रम the object being named */
	__u32 handle;

	/** Returned global name */
	__u32 name;
पूर्ण;

/* DRM_IOCTL_GEM_OPEN ioctl argument type */
काष्ठा drm_gem_खोलो अणु
	/** Name of object being खोलोed */
	__u32 name;

	/** Returned handle क्रम the object */
	__u32 handle;

	/** Returned size of the object */
	__u64 size;
पूर्ण;

/**
 * DRM_CAP_DUMB_BUFFER
 *
 * If set to 1, the driver supports creating dumb buffers via the
 * &DRM_IOCTL_MODE_CREATE_DUMB ioctl.
 */
#घोषणा DRM_CAP_DUMB_BUFFER		0x1
/**
 * DRM_CAP_VBLANK_HIGH_CRTC
 *
 * If set to 1, the kernel supports specअगरying a CRTC index in the high bits of
 * &drm_रुको_vblank_request.type.
 *
 * Starting kernel version 2.6.39, this capability is always set to 1.
 */
#घोषणा DRM_CAP_VBLANK_HIGH_CRTC	0x2
/**
 * DRM_CAP_DUMB_PREFERRED_DEPTH
 *
 * The preferred bit depth क्रम dumb buffers.
 *
 * The bit depth is the number of bits used to indicate the color of a single
 * pixel excluding any padding. This is dअगरferent from the number of bits per
 * pixel. For instance, XRGB8888 has a bit depth of 24 but has 32 bits per
 * pixel.
 *
 * Note that this preference only applies to dumb buffers, it's irrelevant क्रम
 * other types of buffers.
 */
#घोषणा DRM_CAP_DUMB_PREFERRED_DEPTH	0x3
/**
 * DRM_CAP_DUMB_PREFER_SHADOW
 *
 * If set to 1, the driver prefers userspace to render to a shaकरोw buffer
 * instead of directly rendering to a dumb buffer. For best speed, userspace
 * should करो streaming ordered memory copies पूर्णांकo the dumb buffer and never
 * पढ़ो from it.
 *
 * Note that this preference only applies to dumb buffers, it's irrelevant क्रम
 * other types of buffers.
 */
#घोषणा DRM_CAP_DUMB_PREFER_SHADOW	0x4
/**
 * DRM_CAP_PRIME
 *
 * Bitfield of supported PRIME sharing capabilities. See &DRM_PRIME_CAP_IMPORT
 * and &DRM_PRIME_CAP_EXPORT.
 *
 * PRIME buffers are exposed as dma-buf file descriptors. See
 * Documentation/gpu/drm-mm.rst, section "PRIME Buffer Sharing".
 */
#घोषणा DRM_CAP_PRIME			0x5
/**
 * DRM_PRIME_CAP_IMPORT
 *
 * If this bit is set in &DRM_CAP_PRIME, the driver supports importing PRIME
 * buffers via the &DRM_IOCTL_PRIME_FD_TO_HANDLE ioctl.
 */
#घोषणा  DRM_PRIME_CAP_IMPORT		0x1
/**
 * DRM_PRIME_CAP_EXPORT
 *
 * If this bit is set in &DRM_CAP_PRIME, the driver supports exporting PRIME
 * buffers via the &DRM_IOCTL_PRIME_HANDLE_TO_FD ioctl.
 */
#घोषणा  DRM_PRIME_CAP_EXPORT		0x2
/**
 * DRM_CAP_TIMESTAMP_MONOTONIC
 *
 * If set to 0, the kernel will report बारtamps with ``CLOCK_REALTIME`` in
 * काष्ठा drm_event_vblank. If set to 1, the kernel will report बारtamps with
 * ``CLOCK_MONOTONIC``. See ``घड़ी_समय_लो(2)`` क्रम the definition of these
 * घड़ीs.
 *
 * Starting from kernel version 2.6.39, the शेष value क्रम this capability
 * is 1. Starting kernel version 4.15, this capability is always set to 1.
 */
#घोषणा DRM_CAP_TIMESTAMP_MONOTONIC	0x6
/**
 * DRM_CAP_ASYNC_PAGE_FLIP
 *
 * If set to 1, the driver supports &DRM_MODE_PAGE_FLIP_ASYNC.
 */
#घोषणा DRM_CAP_ASYNC_PAGE_FLIP		0x7
/**
 * DRM_CAP_CURSOR_WIDTH
 *
 * The ``CURSOR_WIDTH`` and ``CURSOR_HEIGHT`` capabilities वापस a valid
 * width x height combination क्रम the hardware cursor. The पूर्णांकention is that a
 * hardware agnostic userspace can query a cursor plane size to use.
 *
 * Note that the cross-driver contract is to merely वापस a valid size;
 * drivers are मुक्त to attach another meaning on top, eg. i915 वापसs the
 * maximum plane size.
 */
#घोषणा DRM_CAP_CURSOR_WIDTH		0x8
/**
 * DRM_CAP_CURSOR_HEIGHT
 *
 * See &DRM_CAP_CURSOR_WIDTH.
 */
#घोषणा DRM_CAP_CURSOR_HEIGHT		0x9
/**
 * DRM_CAP_ADDFB2_MODIFIERS
 *
 * If set to 1, the driver supports supplying modअगरiers in the
 * &DRM_IOCTL_MODE_ADDFB2 ioctl.
 */
#घोषणा DRM_CAP_ADDFB2_MODIFIERS	0x10
/**
 * DRM_CAP_PAGE_FLIP_TARGET
 *
 * If set to 1, the driver supports the &DRM_MODE_PAGE_FLIP_TARGET_ABSOLUTE and
 * &DRM_MODE_PAGE_FLIP_TARGET_RELATIVE flags in
 * &drm_mode_crtc_page_flip_target.flags क्रम the &DRM_IOCTL_MODE_PAGE_FLIP
 * ioctl.
 */
#घोषणा DRM_CAP_PAGE_FLIP_TARGET	0x11
/**
 * DRM_CAP_CRTC_IN_VBLANK_EVENT
 *
 * If set to 1, the kernel supports reporting the CRTC ID in
 * &drm_event_vblank.crtc_id क्रम the &DRM_EVENT_VBLANK and
 * &DRM_EVENT_FLIP_COMPLETE events.
 *
 * Starting kernel version 4.12, this capability is always set to 1.
 */
#घोषणा DRM_CAP_CRTC_IN_VBLANK_EVENT	0x12
/**
 * DRM_CAP_SYNCOBJ
 *
 * If set to 1, the driver supports sync objects. See
 * Documentation/gpu/drm-mm.rst, section "DRM Sync Objects".
 */
#घोषणा DRM_CAP_SYNCOBJ		0x13
/**
 * DRM_CAP_SYNCOBJ_TIMELINE
 *
 * If set to 1, the driver supports समयline operations on sync objects. See
 * Documentation/gpu/drm-mm.rst, section "DRM Sync Objects".
 */
#घोषणा DRM_CAP_SYNCOBJ_TIMELINE	0x14

/* DRM_IOCTL_GET_CAP ioctl argument type */
काष्ठा drm_get_cap अणु
	__u64 capability;
	__u64 value;
पूर्ण;

/**
 * DRM_CLIENT_CAP_STEREO_3D
 *
 * अगर set to 1, the DRM core will expose the stereo 3D capabilities of the
 * monitor by advertising the supported 3D layouts in the flags of काष्ठा
 * drm_mode_modeinfo.
 */
#घोषणा DRM_CLIENT_CAP_STEREO_3D	1

/**
 * DRM_CLIENT_CAP_UNIVERSAL_PLANES
 *
 * If set to 1, the DRM core will expose all planes (overlay, primary, and
 * cursor) to userspace.
 */
#घोषणा DRM_CLIENT_CAP_UNIVERSAL_PLANES  2

/**
 * DRM_CLIENT_CAP_ATOMIC
 *
 * If set to 1, the DRM core will expose atomic properties to userspace. This
 * implicitly enables &DRM_CLIENT_CAP_UNIVERSAL_PLANES and
 * &DRM_CLIENT_CAP_ASPECT_RATIO.
 */
#घोषणा DRM_CLIENT_CAP_ATOMIC	3

/**
 * DRM_CLIENT_CAP_ASPECT_RATIO
 *
 * If set to 1, the DRM core will provide aspect ratio inक्रमmation in modes.
 */
#घोषणा DRM_CLIENT_CAP_ASPECT_RATIO    4

/**
 * DRM_CLIENT_CAP_WRITEBACK_CONNECTORS
 *
 * If set to 1, the DRM core will expose special connectors to be used क्रम
 * writing back to memory the scene setup in the commit. Depends on client
 * also supporting DRM_CLIENT_CAP_ATOMIC
 */
#घोषणा DRM_CLIENT_CAP_WRITEBACK_CONNECTORS	5

/* DRM_IOCTL_SET_CLIENT_CAP ioctl argument type */
काष्ठा drm_set_client_cap अणु
	__u64 capability;
	__u64 value;
पूर्ण;

#घोषणा DRM_RDWR O_RDWR
#घोषणा DRM_CLOEXEC O_CLOEXEC
काष्ठा drm_prime_handle अणु
	__u32 handle;

	/** Flags.. only applicable क्रम handle->fd */
	__u32 flags;

	/** Returned dmabuf file descriptor */
	__s32 fd;
पूर्ण;

काष्ठा drm_syncobj_create अणु
	__u32 handle;
#घोषणा DRM_SYNCOBJ_CREATE_SIGNALED (1 << 0)
	__u32 flags;
पूर्ण;

काष्ठा drm_syncobj_destroy अणु
	__u32 handle;
	__u32 pad;
पूर्ण;

#घोषणा DRM_SYNCOBJ_FD_TO_HANDLE_FLAGS_IMPORT_SYNC_खाता (1 << 0)
#घोषणा DRM_SYNCOBJ_HANDLE_TO_FD_FLAGS_EXPORT_SYNC_खाता (1 << 0)
काष्ठा drm_syncobj_handle अणु
	__u32 handle;
	__u32 flags;

	__s32 fd;
	__u32 pad;
पूर्ण;

काष्ठा drm_syncobj_transfer अणु
	__u32 src_handle;
	__u32 dst_handle;
	__u64 src_poपूर्णांक;
	__u64 dst_poपूर्णांक;
	__u32 flags;
	__u32 pad;
पूर्ण;

#घोषणा DRM_SYNCOBJ_WAIT_FLAGS_WAIT_ALL (1 << 0)
#घोषणा DRM_SYNCOBJ_WAIT_FLAGS_WAIT_FOR_SUBMIT (1 << 1)
#घोषणा DRM_SYNCOBJ_WAIT_FLAGS_WAIT_AVAILABLE (1 << 2) /* रुको क्रम समय poपूर्णांक to become available */
काष्ठा drm_syncobj_रुको अणु
	__u64 handles;
	/* असलolute समयout */
	__s64 समयout_nsec;
	__u32 count_handles;
	__u32 flags;
	__u32 first_संकेतed; /* only valid when not रुकोing all */
	__u32 pad;
पूर्ण;

काष्ठा drm_syncobj_समयline_रुको अणु
	__u64 handles;
	/* रुको on specअगरic समयline poपूर्णांक क्रम every handles*/
	__u64 poपूर्णांकs;
	/* असलolute समयout */
	__s64 समयout_nsec;
	__u32 count_handles;
	__u32 flags;
	__u32 first_संकेतed; /* only valid when not रुकोing all */
	__u32 pad;
पूर्ण;


काष्ठा drm_syncobj_array अणु
	__u64 handles;
	__u32 count_handles;
	__u32 pad;
पूर्ण;

#घोषणा DRM_SYNCOBJ_QUERY_FLAGS_LAST_SUBMITTED (1 << 0) /* last available poपूर्णांक on समयline syncobj */
काष्ठा drm_syncobj_समयline_array अणु
	__u64 handles;
	__u64 poपूर्णांकs;
	__u32 count_handles;
	__u32 flags;
पूर्ण;


/* Query current scanout sequence number */
काष्ठा drm_crtc_get_sequence अणु
	__u32 crtc_id;		/* requested crtc_id */
	__u32 active;		/* वापस: crtc output is active */
	__u64 sequence;		/* वापस: most recent vblank sequence */
	__s64 sequence_ns;	/* वापस: most recent समय of first pixel out */
पूर्ण;

/* Queue event to be delivered at specअगरied sequence. Time stamp marks
 * when the first pixel of the refresh cycle leaves the display engine
 * क्रम the display
 */
#घोषणा DRM_CRTC_SEQUENCE_RELATIVE		0x00000001	/* sequence is relative to current */
#घोषणा DRM_CRTC_SEQUENCE_NEXT_ON_MISS		0x00000002	/* Use next sequence अगर we've missed */

काष्ठा drm_crtc_queue_sequence अणु
	__u32 crtc_id;
	__u32 flags;
	__u64 sequence;		/* on input, target sequence. on output, actual sequence */
	__u64 user_data;	/* user data passed to event */
पूर्ण;

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#समावेश "drm_mode.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

#घोषणा DRM_IOCTL_BASE			'd'
#घोषणा DRM_IO(nr)			_IO(DRM_IOCTL_BASE,nr)
#घोषणा DRM_IOR(nr,type)		_IOR(DRM_IOCTL_BASE,nr,type)
#घोषणा DRM_IOW(nr,type)		_IOW(DRM_IOCTL_BASE,nr,type)
#घोषणा DRM_IOWR(nr,type)		_IOWR(DRM_IOCTL_BASE,nr,type)

#घोषणा DRM_IOCTL_VERSION		DRM_IOWR(0x00, काष्ठा drm_version)
#घोषणा DRM_IOCTL_GET_UNIQUE		DRM_IOWR(0x01, काष्ठा drm_unique)
#घोषणा DRM_IOCTL_GET_MAGIC		DRM_IOR( 0x02, काष्ठा drm_auth)
#घोषणा DRM_IOCTL_IRQ_BUSID		DRM_IOWR(0x03, काष्ठा drm_irq_busid)
#घोषणा DRM_IOCTL_GET_MAP               DRM_IOWR(0x04, काष्ठा drm_map)
#घोषणा DRM_IOCTL_GET_CLIENT            DRM_IOWR(0x05, काष्ठा drm_client)
#घोषणा DRM_IOCTL_GET_STATS             DRM_IOR( 0x06, काष्ठा drm_stats)
#घोषणा DRM_IOCTL_SET_VERSION		DRM_IOWR(0x07, काष्ठा drm_set_version)
#घोषणा DRM_IOCTL_MODESET_CTL           DRM_IOW(0x08, काष्ठा drm_modeset_ctl)
#घोषणा DRM_IOCTL_GEM_CLOSE		DRM_IOW (0x09, काष्ठा drm_gem_बंद)
#घोषणा DRM_IOCTL_GEM_FLINK		DRM_IOWR(0x0a, काष्ठा drm_gem_flink)
#घोषणा DRM_IOCTL_GEM_OPEN		DRM_IOWR(0x0b, काष्ठा drm_gem_खोलो)
#घोषणा DRM_IOCTL_GET_CAP		DRM_IOWR(0x0c, काष्ठा drm_get_cap)
#घोषणा DRM_IOCTL_SET_CLIENT_CAP	DRM_IOW( 0x0d, काष्ठा drm_set_client_cap)

#घोषणा DRM_IOCTL_SET_UNIQUE		DRM_IOW( 0x10, काष्ठा drm_unique)
#घोषणा DRM_IOCTL_AUTH_MAGIC		DRM_IOW( 0x11, काष्ठा drm_auth)
#घोषणा DRM_IOCTL_BLOCK			DRM_IOWR(0x12, काष्ठा drm_block)
#घोषणा DRM_IOCTL_UNBLOCK		DRM_IOWR(0x13, काष्ठा drm_block)
#घोषणा DRM_IOCTL_CONTROL		DRM_IOW( 0x14, काष्ठा drm_control)
#घोषणा DRM_IOCTL_ADD_MAP		DRM_IOWR(0x15, काष्ठा drm_map)
#घोषणा DRM_IOCTL_ADD_BUFS		DRM_IOWR(0x16, काष्ठा drm_buf_desc)
#घोषणा DRM_IOCTL_MARK_BUFS		DRM_IOW( 0x17, काष्ठा drm_buf_desc)
#घोषणा DRM_IOCTL_INFO_BUFS		DRM_IOWR(0x18, काष्ठा drm_buf_info)
#घोषणा DRM_IOCTL_MAP_BUFS		DRM_IOWR(0x19, काष्ठा drm_buf_map)
#घोषणा DRM_IOCTL_FREE_BUFS		DRM_IOW( 0x1a, काष्ठा drm_buf_मुक्त)

#घोषणा DRM_IOCTL_RM_MAP		DRM_IOW( 0x1b, काष्ठा drm_map)

#घोषणा DRM_IOCTL_SET_SAREA_CTX		DRM_IOW( 0x1c, काष्ठा drm_ctx_priv_map)
#घोषणा DRM_IOCTL_GET_SAREA_CTX 	DRM_IOWR(0x1d, काष्ठा drm_ctx_priv_map)

#घोषणा DRM_IOCTL_SET_MASTER            DRM_IO(0x1e)
#घोषणा DRM_IOCTL_DROP_MASTER           DRM_IO(0x1f)

#घोषणा DRM_IOCTL_ADD_CTX		DRM_IOWR(0x20, काष्ठा drm_ctx)
#घोषणा DRM_IOCTL_RM_CTX		DRM_IOWR(0x21, काष्ठा drm_ctx)
#घोषणा DRM_IOCTL_MOD_CTX		DRM_IOW( 0x22, काष्ठा drm_ctx)
#घोषणा DRM_IOCTL_GET_CTX		DRM_IOWR(0x23, काष्ठा drm_ctx)
#घोषणा DRM_IOCTL_SWITCH_CTX		DRM_IOW( 0x24, काष्ठा drm_ctx)
#घोषणा DRM_IOCTL_NEW_CTX		DRM_IOW( 0x25, काष्ठा drm_ctx)
#घोषणा DRM_IOCTL_RES_CTX		DRM_IOWR(0x26, काष्ठा drm_ctx_res)
#घोषणा DRM_IOCTL_ADD_DRAW		DRM_IOWR(0x27, काष्ठा drm_draw)
#घोषणा DRM_IOCTL_RM_DRAW		DRM_IOWR(0x28, काष्ठा drm_draw)
#घोषणा DRM_IOCTL_DMA			DRM_IOWR(0x29, काष्ठा drm_dma)
#घोषणा DRM_IOCTL_LOCK			DRM_IOW( 0x2a, काष्ठा drm_lock)
#घोषणा DRM_IOCTL_UNLOCK		DRM_IOW( 0x2b, काष्ठा drm_lock)
#घोषणा DRM_IOCTL_FINISH		DRM_IOW( 0x2c, काष्ठा drm_lock)

#घोषणा DRM_IOCTL_PRIME_HANDLE_TO_FD    DRM_IOWR(0x2d, काष्ठा drm_prime_handle)
#घोषणा DRM_IOCTL_PRIME_FD_TO_HANDLE    DRM_IOWR(0x2e, काष्ठा drm_prime_handle)

#घोषणा DRM_IOCTL_AGP_ACQUIRE		DRM_IO(  0x30)
#घोषणा DRM_IOCTL_AGP_RELEASE		DRM_IO(  0x31)
#घोषणा DRM_IOCTL_AGP_ENABLE		DRM_IOW( 0x32, काष्ठा drm_agp_mode)
#घोषणा DRM_IOCTL_AGP_INFO		DRM_IOR( 0x33, काष्ठा drm_agp_info)
#घोषणा DRM_IOCTL_AGP_ALLOC		DRM_IOWR(0x34, काष्ठा drm_agp_buffer)
#घोषणा DRM_IOCTL_AGP_FREE		DRM_IOW( 0x35, काष्ठा drm_agp_buffer)
#घोषणा DRM_IOCTL_AGP_BIND		DRM_IOW( 0x36, काष्ठा drm_agp_binding)
#घोषणा DRM_IOCTL_AGP_UNBIND		DRM_IOW( 0x37, काष्ठा drm_agp_binding)

#घोषणा DRM_IOCTL_SG_ALLOC		DRM_IOWR(0x38, काष्ठा drm_scatter_gather)
#घोषणा DRM_IOCTL_SG_FREE		DRM_IOW( 0x39, काष्ठा drm_scatter_gather)

#घोषणा DRM_IOCTL_WAIT_VBLANK		DRM_IOWR(0x3a, जोड़ drm_रुको_vblank)

#घोषणा DRM_IOCTL_CRTC_GET_SEQUENCE	DRM_IOWR(0x3b, काष्ठा drm_crtc_get_sequence)
#घोषणा DRM_IOCTL_CRTC_QUEUE_SEQUENCE	DRM_IOWR(0x3c, काष्ठा drm_crtc_queue_sequence)

#घोषणा DRM_IOCTL_UPDATE_DRAW		DRM_IOW(0x3f, काष्ठा drm_update_draw)

#घोषणा DRM_IOCTL_MODE_GETRESOURCES	DRM_IOWR(0xA0, काष्ठा drm_mode_card_res)
#घोषणा DRM_IOCTL_MODE_GETCRTC		DRM_IOWR(0xA1, काष्ठा drm_mode_crtc)
#घोषणा DRM_IOCTL_MODE_SETCRTC		DRM_IOWR(0xA2, काष्ठा drm_mode_crtc)
#घोषणा DRM_IOCTL_MODE_CURSOR		DRM_IOWR(0xA3, काष्ठा drm_mode_cursor)
#घोषणा DRM_IOCTL_MODE_GETGAMMA		DRM_IOWR(0xA4, काष्ठा drm_mode_crtc_lut)
#घोषणा DRM_IOCTL_MODE_SETGAMMA		DRM_IOWR(0xA5, काष्ठा drm_mode_crtc_lut)
#घोषणा DRM_IOCTL_MODE_GETENCODER	DRM_IOWR(0xA6, काष्ठा drm_mode_get_encoder)
#घोषणा DRM_IOCTL_MODE_GETCONNECTOR	DRM_IOWR(0xA7, काष्ठा drm_mode_get_connector)
#घोषणा DRM_IOCTL_MODE_ATTACHMODE	DRM_IOWR(0xA8, काष्ठा drm_mode_mode_cmd) /* deprecated (never worked) */
#घोषणा DRM_IOCTL_MODE_DETACHMODE	DRM_IOWR(0xA9, काष्ठा drm_mode_mode_cmd) /* deprecated (never worked) */

#घोषणा DRM_IOCTL_MODE_GETPROPERTY	DRM_IOWR(0xAA, काष्ठा drm_mode_get_property)
#घोषणा DRM_IOCTL_MODE_SETPROPERTY	DRM_IOWR(0xAB, काष्ठा drm_mode_connector_set_property)
#घोषणा DRM_IOCTL_MODE_GETPROPBLOB	DRM_IOWR(0xAC, काष्ठा drm_mode_get_blob)
#घोषणा DRM_IOCTL_MODE_GETFB		DRM_IOWR(0xAD, काष्ठा drm_mode_fb_cmd)
#घोषणा DRM_IOCTL_MODE_ADDFB		DRM_IOWR(0xAE, काष्ठा drm_mode_fb_cmd)
#घोषणा DRM_IOCTL_MODE_RMFB		DRM_IOWR(0xAF, अचिन्हित पूर्णांक)
#घोषणा DRM_IOCTL_MODE_PAGE_FLIP	DRM_IOWR(0xB0, काष्ठा drm_mode_crtc_page_flip)
#घोषणा DRM_IOCTL_MODE_सूचीTYFB		DRM_IOWR(0xB1, काष्ठा drm_mode_fb_dirty_cmd)

#घोषणा DRM_IOCTL_MODE_CREATE_DUMB DRM_IOWR(0xB2, काष्ठा drm_mode_create_dumb)
#घोषणा DRM_IOCTL_MODE_MAP_DUMB    DRM_IOWR(0xB3, काष्ठा drm_mode_map_dumb)
#घोषणा DRM_IOCTL_MODE_DESTROY_DUMB    DRM_IOWR(0xB4, काष्ठा drm_mode_destroy_dumb)
#घोषणा DRM_IOCTL_MODE_GETPLANERESOURCES DRM_IOWR(0xB5, काष्ठा drm_mode_get_plane_res)
#घोषणा DRM_IOCTL_MODE_GETPLANE	DRM_IOWR(0xB6, काष्ठा drm_mode_get_plane)
#घोषणा DRM_IOCTL_MODE_SETPLANE	DRM_IOWR(0xB7, काष्ठा drm_mode_set_plane)
#घोषणा DRM_IOCTL_MODE_ADDFB2		DRM_IOWR(0xB8, काष्ठा drm_mode_fb_cmd2)
#घोषणा DRM_IOCTL_MODE_OBJ_GETPROPERTIES	DRM_IOWR(0xB9, काष्ठा drm_mode_obj_get_properties)
#घोषणा DRM_IOCTL_MODE_OBJ_SETPROPERTY	DRM_IOWR(0xBA, काष्ठा drm_mode_obj_set_property)
#घोषणा DRM_IOCTL_MODE_CURSOR2		DRM_IOWR(0xBB, काष्ठा drm_mode_cursor2)
#घोषणा DRM_IOCTL_MODE_ATOMIC		DRM_IOWR(0xBC, काष्ठा drm_mode_atomic)
#घोषणा DRM_IOCTL_MODE_CREATEPROPBLOB	DRM_IOWR(0xBD, काष्ठा drm_mode_create_blob)
#घोषणा DRM_IOCTL_MODE_DESTROYPROPBLOB	DRM_IOWR(0xBE, काष्ठा drm_mode_destroy_blob)

#घोषणा DRM_IOCTL_SYNCOBJ_CREATE	DRM_IOWR(0xBF, काष्ठा drm_syncobj_create)
#घोषणा DRM_IOCTL_SYNCOBJ_DESTROY	DRM_IOWR(0xC0, काष्ठा drm_syncobj_destroy)
#घोषणा DRM_IOCTL_SYNCOBJ_HANDLE_TO_FD	DRM_IOWR(0xC1, काष्ठा drm_syncobj_handle)
#घोषणा DRM_IOCTL_SYNCOBJ_FD_TO_HANDLE	DRM_IOWR(0xC2, काष्ठा drm_syncobj_handle)
#घोषणा DRM_IOCTL_SYNCOBJ_WAIT		DRM_IOWR(0xC3, काष्ठा drm_syncobj_रुको)
#घोषणा DRM_IOCTL_SYNCOBJ_RESET		DRM_IOWR(0xC4, काष्ठा drm_syncobj_array)
#घोषणा DRM_IOCTL_SYNCOBJ_SIGNAL	DRM_IOWR(0xC5, काष्ठा drm_syncobj_array)

#घोषणा DRM_IOCTL_MODE_CREATE_LEASE	DRM_IOWR(0xC6, काष्ठा drm_mode_create_lease)
#घोषणा DRM_IOCTL_MODE_LIST_LESSEES	DRM_IOWR(0xC7, काष्ठा drm_mode_list_lessees)
#घोषणा DRM_IOCTL_MODE_GET_LEASE	DRM_IOWR(0xC8, काष्ठा drm_mode_get_lease)
#घोषणा DRM_IOCTL_MODE_REVOKE_LEASE	DRM_IOWR(0xC9, काष्ठा drm_mode_revoke_lease)

#घोषणा DRM_IOCTL_SYNCOBJ_TIMELINE_WAIT	DRM_IOWR(0xCA, काष्ठा drm_syncobj_समयline_रुको)
#घोषणा DRM_IOCTL_SYNCOBJ_QUERY		DRM_IOWR(0xCB, काष्ठा drm_syncobj_समयline_array)
#घोषणा DRM_IOCTL_SYNCOBJ_TRANSFER	DRM_IOWR(0xCC, काष्ठा drm_syncobj_transfer)
#घोषणा DRM_IOCTL_SYNCOBJ_TIMELINE_SIGNAL	DRM_IOWR(0xCD, काष्ठा drm_syncobj_समयline_array)

#घोषणा DRM_IOCTL_MODE_GETFB2		DRM_IOWR(0xCE, काष्ठा drm_mode_fb_cmd2)

/*
 * Device specअगरic ioctls should only be in their respective headers
 * The device specअगरic ioctl range is from 0x40 to 0x9f.
 * Generic IOCTLS restart at 0xA0.
 *
 * \sa drmCommandNone(), drmCommandRead(), drmCommandWrite(), and
 * drmCommandReadWrite().
 */
#घोषणा DRM_COMMAND_BASE                0x40
#घोषणा DRM_COMMAND_END			0xA0

/*
 * Header क्रम events written back to userspace on the drm fd.  The
 * type defines the type of event, the length specअगरies the total
 * length of the event (including the header), and user_data is
 * typically a 64 bit value passed with the ioctl that triggered the
 * event.  A पढ़ो on the drm fd will always only वापस complete
 * events, that is, अगर क्रम example the पढ़ो buffer is 100 bytes, and
 * there are two 64 byte events pending, only one will be वापसed.
 *
 * Event types 0 - 0x7fffffff are generic drm events, 0x80000000 and
 * up are chipset specअगरic.
 */
काष्ठा drm_event अणु
	__u32 type;
	__u32 length;
पूर्ण;

#घोषणा DRM_EVENT_VBLANK 0x01
#घोषणा DRM_EVENT_FLIP_COMPLETE 0x02
#घोषणा DRM_EVENT_CRTC_SEQUENCE	0x03

काष्ठा drm_event_vblank अणु
	काष्ठा drm_event base;
	__u64 user_data;
	__u32 tv_sec;
	__u32 tv_usec;
	__u32 sequence;
	__u32 crtc_id; /* 0 on older kernels that करो not support this */
पूर्ण;

/* Event delivered at sequence. Time stamp marks when the first pixel
 * of the refresh cycle leaves the display engine क्रम the display
 */
काष्ठा drm_event_crtc_sequence अणु
	काष्ठा drm_event	base;
	__u64			user_data;
	__s64			समय_ns;
	__u64			sequence;
पूर्ण;

/* प्रकार area */
#अगर_अघोषित __KERNEL__
प्रकार काष्ठा drm_clip_rect drm_clip_rect_t;
प्रकार काष्ठा drm_drawable_info drm_drawable_info_t;
प्रकार काष्ठा drm_tex_region drm_tex_region_t;
प्रकार काष्ठा drm_hw_lock drm_hw_lock_t;
प्रकार काष्ठा drm_version drm_version_t;
प्रकार काष्ठा drm_unique drm_unique_t;
प्रकार काष्ठा drm_list drm_list_t;
प्रकार काष्ठा drm_block drm_block_t;
प्रकार काष्ठा drm_control drm_control_t;
प्रकार क्रमागत drm_map_type drm_map_type_t;
प्रकार क्रमागत drm_map_flags drm_map_flags_t;
प्रकार काष्ठा drm_ctx_priv_map drm_ctx_priv_map_t;
प्रकार काष्ठा drm_map drm_map_t;
प्रकार काष्ठा drm_client drm_client_t;
प्रकार क्रमागत drm_stat_type drm_stat_type_t;
प्रकार काष्ठा drm_stats drm_stats_t;
प्रकार क्रमागत drm_lock_flags drm_lock_flags_t;
प्रकार काष्ठा drm_lock drm_lock_t;
प्रकार क्रमागत drm_dma_flags drm_dma_flags_t;
प्रकार काष्ठा drm_buf_desc drm_buf_desc_t;
प्रकार काष्ठा drm_buf_info drm_buf_info_t;
प्रकार काष्ठा drm_buf_मुक्त drm_buf_मुक्त_t;
प्रकार काष्ठा drm_buf_pub drm_buf_pub_t;
प्रकार काष्ठा drm_buf_map drm_buf_map_t;
प्रकार काष्ठा drm_dma drm_dma_t;
प्रकार जोड़ drm_रुको_vblank drm_रुको_vblank_t;
प्रकार काष्ठा drm_agp_mode drm_agp_mode_t;
प्रकार क्रमागत drm_ctx_flags drm_ctx_flags_t;
प्रकार काष्ठा drm_ctx drm_ctx_t;
प्रकार काष्ठा drm_ctx_res drm_ctx_res_t;
प्रकार काष्ठा drm_draw drm_draw_t;
प्रकार काष्ठा drm_update_draw drm_update_draw_t;
प्रकार काष्ठा drm_auth drm_auth_t;
प्रकार काष्ठा drm_irq_busid drm_irq_busid_t;
प्रकार क्रमागत drm_vblank_seq_type drm_vblank_seq_type_t;

प्रकार काष्ठा drm_agp_buffer drm_agp_buffer_t;
प्रकार काष्ठा drm_agp_binding drm_agp_binding_t;
प्रकार काष्ठा drm_agp_info drm_agp_info_t;
प्रकार काष्ठा drm_scatter_gather drm_scatter_gather_t;
प्रकार काष्ठा drm_set_version drm_set_version_t;
#पूर्ण_अगर

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
