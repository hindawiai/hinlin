<शैली गुरु>
/*
 * Copyright (c) 2012-2013, NVIDIA CORPORATION.  All rights reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 */

#अगर_अघोषित _UAPI_TEGRA_DRM_H_
#घोषणा _UAPI_TEGRA_DRM_H_

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

#घोषणा DRM_TEGRA_GEM_CREATE_TILED     (1 << 0)
#घोषणा DRM_TEGRA_GEM_CREATE_BOTTOM_UP (1 << 1)

/**
 * काष्ठा drm_tegra_gem_create - parameters क्रम the GEM object creation IOCTL
 */
काष्ठा drm_tegra_gem_create अणु
	/**
	 * @size:
	 *
	 * The size, in bytes, of the buffer object to be created.
	 */
	__u64 size;

	/**
	 * @flags:
	 *
	 * A biपंचांगask of flags that influence the creation of GEM objects:
	 *
	 * DRM_TEGRA_GEM_CREATE_TILED
	 *   Use the 16x16 tiling क्रमmat क्रम this buffer.
	 *
	 * DRM_TEGRA_GEM_CREATE_BOTTOM_UP
	 *   The buffer has a bottom-up layout.
	 */
	__u32 flags;

	/**
	 * @handle:
	 *
	 * The handle of the created GEM object. Set by the kernel upon
	 * successful completion of the IOCTL.
	 */
	__u32 handle;
पूर्ण;

/**
 * काष्ठा drm_tegra_gem_mmap - parameters क्रम the GEM mmap IOCTL
 */
काष्ठा drm_tegra_gem_mmap अणु
	/**
	 * @handle:
	 *
	 * Handle of the GEM object to obtain an mmap offset क्रम.
	 */
	__u32 handle;

	/**
	 * @pad:
	 *
	 * Structure padding that may be used in the future. Must be 0.
	 */
	__u32 pad;

	/**
	 * @offset:
	 *
	 * The mmap offset क्रम the given GEM object. Set by the kernel upon
	 * successful completion of the IOCTL.
	 */
	__u64 offset;
पूर्ण;

/**
 * काष्ठा drm_tegra_syncpt_पढ़ो - parameters क्रम the पढ़ो syncpoपूर्णांक IOCTL
 */
काष्ठा drm_tegra_syncpt_पढ़ो अणु
	/**
	 * @id:
	 *
	 * ID of the syncpoपूर्णांक to पढ़ो the current value from.
	 */
	__u32 id;

	/**
	 * @value:
	 *
	 * The current syncpoपूर्णांक value. Set by the kernel upon successful
	 * completion of the IOCTL.
	 */
	__u32 value;
पूर्ण;

/**
 * काष्ठा drm_tegra_syncpt_incr - parameters क्रम the increment syncpoपूर्णांक IOCTL
 */
काष्ठा drm_tegra_syncpt_incr अणु
	/**
	 * @id:
	 *
	 * ID of the syncpoपूर्णांक to increment.
	 */
	__u32 id;

	/**
	 * @pad:
	 *
	 * Structure padding that may be used in the future. Must be 0.
	 */
	__u32 pad;
पूर्ण;

/**
 * काष्ठा drm_tegra_syncpt_रुको - parameters क्रम the रुको syncpoपूर्णांक IOCTL
 */
काष्ठा drm_tegra_syncpt_रुको अणु
	/**
	 * @id:
	 *
	 * ID of the syncpoपूर्णांक to रुको on.
	 */
	__u32 id;

	/**
	 * @thresh:
	 *
	 * Threshold value क्रम which to रुको.
	 */
	__u32 thresh;

	/**
	 * @समयout:
	 *
	 * Timeout, in milliseconds, to रुको.
	 */
	__u32 समयout;

	/**
	 * @value:
	 *
	 * The new syncpoपूर्णांक value after the रुको. Set by the kernel upon
	 * successful completion of the IOCTL.
	 */
	__u32 value;
पूर्ण;

#घोषणा DRM_TEGRA_NO_TIMEOUT	(0xffffffff)

/**
 * काष्ठा drm_tegra_खोलो_channel - parameters क्रम the खोलो channel IOCTL
 */
काष्ठा drm_tegra_खोलो_channel अणु
	/**
	 * @client:
	 *
	 * The client ID क्रम this channel.
	 */
	__u32 client;

	/**
	 * @pad:
	 *
	 * Structure padding that may be used in the future. Must be 0.
	 */
	__u32 pad;

	/**
	 * @context:
	 *
	 * The application context of this channel. Set by the kernel upon
	 * successful completion of the IOCTL. This context needs to be passed
	 * to the DRM_TEGRA_CHANNEL_CLOSE or the DRM_TEGRA_SUBMIT IOCTLs.
	 */
	__u64 context;
पूर्ण;

/**
 * काष्ठा drm_tegra_बंद_channel - parameters क्रम the बंद channel IOCTL
 */
काष्ठा drm_tegra_बंद_channel अणु
	/**
	 * @context:
	 *
	 * The application context of this channel. This is obtained from the
	 * DRM_TEGRA_OPEN_CHANNEL IOCTL.
	 */
	__u64 context;
पूर्ण;

/**
 * काष्ठा drm_tegra_get_syncpt - parameters क्रम the get syncpoपूर्णांक IOCTL
 */
काष्ठा drm_tegra_get_syncpt अणु
	/**
	 * @context:
	 *
	 * The application context identअगरying the channel क्रम which to obtain
	 * the syncpoपूर्णांक ID.
	 */
	__u64 context;

	/**
	 * @index:
	 *
	 * Index of the client syncpoपूर्णांक क्रम which to obtain the ID.
	 */
	__u32 index;

	/**
	 * @id:
	 *
	 * The ID of the given syncpoपूर्णांक. Set by the kernel upon successful
	 * completion of the IOCTL.
	 */
	__u32 id;
पूर्ण;

/**
 * काष्ठा drm_tegra_get_syncpt_base - parameters क्रम the get रुको base IOCTL
 */
काष्ठा drm_tegra_get_syncpt_base अणु
	/**
	 * @context:
	 *
	 * The application context identअगरying क्रम which channel to obtain the
	 * रुको base.
	 */
	__u64 context;

	/**
	 * @syncpt:
	 *
	 * ID of the syncpoपूर्णांक क्रम which to obtain the रुको base.
	 */
	__u32 syncpt;

	/**
	 * @id:
	 *
	 * The ID of the रुको base corresponding to the client syncpoपूर्णांक. Set
	 * by the kernel upon successful completion of the IOCTL.
	 */
	__u32 id;
पूर्ण;

/**
 * काष्ठा drm_tegra_syncpt - syncpoपूर्णांक increment operation
 */
काष्ठा drm_tegra_syncpt अणु
	/**
	 * @id:
	 *
	 * ID of the syncpoपूर्णांक to operate on.
	 */
	__u32 id;

	/**
	 * @incrs:
	 *
	 * Number of increments to perक्रमm क्रम the syncpoपूर्णांक.
	 */
	__u32 incrs;
पूर्ण;

/**
 * काष्ठा drm_tegra_cmdbuf - काष्ठाure describing a command buffer
 */
काष्ठा drm_tegra_cmdbuf अणु
	/**
	 * @handle:
	 *
	 * Handle to a GEM object containing the command buffer.
	 */
	__u32 handle;

	/**
	 * @offset:
	 *
	 * Offset, in bytes, पूर्णांकo the GEM object identअगरied by @handle at
	 * which the command buffer starts.
	 */
	__u32 offset;

	/**
	 * @words:
	 *
	 * Number of 32-bit words in this command buffer.
	 */
	__u32 words;

	/**
	 * @pad:
	 *
	 * Structure padding that may be used in the future. Must be 0.
	 */
	__u32 pad;
पूर्ण;

/**
 * काष्ठा drm_tegra_reloc - GEM object relocation काष्ठाure
 */
काष्ठा drm_tegra_reloc अणु
	काष्ठा अणु
		/**
		 * @cmdbuf.handle:
		 *
		 * Handle to the GEM object containing the command buffer क्रम
		 * which to perक्रमm this GEM object relocation.
		 */
		__u32 handle;

		/**
		 * @cmdbuf.offset:
		 *
		 * Offset, in bytes, पूर्णांकo the command buffer at which to
		 * insert the relocated address.
		 */
		__u32 offset;
	पूर्ण cmdbuf;
	काष्ठा अणु
		/**
		 * @target.handle:
		 *
		 * Handle to the GEM object to be relocated.
		 */
		__u32 handle;

		/**
		 * @target.offset:
		 *
		 * Offset, in bytes, पूर्णांकo the target GEM object at which the
		 * relocated data starts.
		 */
		__u32 offset;
	पूर्ण target;

	/**
	 * @shअगरt:
	 *
	 * The number of bits by which to shअगरt relocated addresses.
	 */
	__u32 shअगरt;

	/**
	 * @pad:
	 *
	 * Structure padding that may be used in the future. Must be 0.
	 */
	__u32 pad;
पूर्ण;

/**
 * काष्ठा drm_tegra_रुकोchk - रुको check काष्ठाure
 */
काष्ठा drm_tegra_रुकोchk अणु
	/**
	 * @handle:
	 *
	 * Handle to the GEM object containing a command stream on which to
	 * perक्रमm the रुको check.
	 */
	__u32 handle;

	/**
	 * @offset:
	 *
	 * Offset, in bytes, of the location in the command stream to perक्रमm
	 * the रुको check on.
	 */
	__u32 offset;

	/**
	 * @syncpt:
	 *
	 * ID of the syncpoपूर्णांक to रुको check.
	 */
	__u32 syncpt;

	/**
	 * @thresh:
	 *
	 * Threshold value क्रम which to check.
	 */
	__u32 thresh;
पूर्ण;

/**
 * काष्ठा drm_tegra_submit - job submission काष्ठाure
 */
काष्ठा drm_tegra_submit अणु
	/**
	 * @context:
	 *
	 * The application context identअगरying the channel to use क्रम the
	 * execution of this job.
	 */
	__u64 context;

	/**
	 * @num_syncpts:
	 *
	 * The number of syncpoपूर्णांकs operated on by this job. This defines the
	 * length of the array poपूर्णांकed to by @syncpts.
	 */
	__u32 num_syncpts;

	/**
	 * @num_cmdbufs:
	 *
	 * The number of command buffers to execute as part of this job. This
	 * defines the length of the array poपूर्णांकed to by @cmdbufs.
	 */
	__u32 num_cmdbufs;

	/**
	 * @num_relocs:
	 *
	 * The number of relocations to perक्रमm beक्रमe executing this job.
	 * This defines the length of the array poपूर्णांकed to by @relocs.
	 */
	__u32 num_relocs;

	/**
	 * @num_रुकोchks:
	 *
	 * The number of रुको checks to perक्रमm as part of this job. This
	 * defines the length of the array poपूर्णांकed to by @रुकोchks.
	 */
	__u32 num_रुकोchks;

	/**
	 * @रुकोchk_mask:
	 *
	 * Biपंचांगask of valid रुको checks.
	 */
	__u32 रुकोchk_mask;

	/**
	 * @समयout:
	 *
	 * Timeout, in milliseconds, beक्रमe this job is cancelled.
	 */
	__u32 समयout;

	/**
	 * @syncpts:
	 *
	 * A poपूर्णांकer to an array of &काष्ठा drm_tegra_syncpt काष्ठाures that
	 * specअगरy the syncpoपूर्णांक operations perक्रमmed as part of this job.
	 * The number of elements in the array must be equal to the value
	 * given by @num_syncpts.
	 */
	__u64 syncpts;

	/**
	 * @cmdbufs:
	 *
	 * A poपूर्णांकer to an array of &काष्ठा drm_tegra_cmdbuf काष्ठाures that
	 * define the command buffers to execute as part of this job. The
	 * number of elements in the array must be equal to the value given
	 * by @num_syncpts.
	 */
	__u64 cmdbufs;

	/**
	 * @relocs:
	 *
	 * A poपूर्णांकer to an array of &काष्ठा drm_tegra_reloc काष्ठाures that
	 * specअगरy the relocations that need to be perक्रमmed beक्रमe executing
	 * this job. The number of elements in the array must be equal to the
	 * value given by @num_relocs.
	 */
	__u64 relocs;

	/**
	 * @रुकोchks:
	 *
	 * A poपूर्णांकer to an array of &काष्ठा drm_tegra_रुकोchk काष्ठाures that
	 * specअगरy the रुको checks to be perक्रमmed जबतक executing this job.
	 * The number of elements in the array must be equal to the value
	 * given by @num_रुकोchks.
	 */
	__u64 रुकोchks;

	/**
	 * @fence:
	 *
	 * The threshold of the syncpoपूर्णांक associated with this job after it
	 * has been completed. Set by the kernel upon successful completion of
	 * the IOCTL. This can be used with the DRM_TEGRA_SYNCPT_WAIT IOCTL to
	 * रुको क्रम this job to be finished.
	 */
	__u32 fence;

	/**
	 * @reserved:
	 *
	 * This field is reserved क्रम future use. Must be 0.
	 */
	__u32 reserved[5];
पूर्ण;

#घोषणा DRM_TEGRA_GEM_TILING_MODE_PITCH 0
#घोषणा DRM_TEGRA_GEM_TILING_MODE_TILED 1
#घोषणा DRM_TEGRA_GEM_TILING_MODE_BLOCK 2

/**
 * काष्ठा drm_tegra_gem_set_tiling - parameters क्रम the set tiling IOCTL
 */
काष्ठा drm_tegra_gem_set_tiling अणु
	/**
	 * @handle:
	 *
	 * Handle to the GEM object क्रम which to set the tiling parameters.
	 */
	__u32 handle;

	/**
	 * @mode:
	 *
	 * The tiling mode to set. Must be one of:
	 *
	 * DRM_TEGRA_GEM_TILING_MODE_PITCH
	 *   pitch linear क्रमmat
	 *
	 * DRM_TEGRA_GEM_TILING_MODE_TILED
	 *   16x16 tiling क्रमmat
	 *
	 * DRM_TEGRA_GEM_TILING_MODE_BLOCK
	 *   16Bx2 tiling क्रमmat
	 */
	__u32 mode;

	/**
	 * @value:
	 *
	 * The value to set क्रम the tiling mode parameter.
	 */
	__u32 value;

	/**
	 * @pad:
	 *
	 * Structure padding that may be used in the future. Must be 0.
	 */
	__u32 pad;
पूर्ण;

/**
 * काष्ठा drm_tegra_gem_get_tiling - parameters क्रम the get tiling IOCTL
 */
काष्ठा drm_tegra_gem_get_tiling अणु
	/**
	 * @handle:
	 *
	 * Handle to the GEM object क्रम which to query the tiling parameters.
	 */
	__u32 handle;

	/**
	 * @mode:
	 *
	 * The tiling mode currently associated with the GEM object. Set by
	 * the kernel upon successful completion of the IOCTL.
	 */
	__u32 mode;

	/**
	 * @value:
	 *
	 * The tiling mode parameter currently associated with the GEM object.
	 * Set by the kernel upon successful completion of the IOCTL.
	 */
	__u32 value;

	/**
	 * @pad:
	 *
	 * Structure padding that may be used in the future. Must be 0.
	 */
	__u32 pad;
पूर्ण;

#घोषणा DRM_TEGRA_GEM_BOTTOM_UP		(1 << 0)
#घोषणा DRM_TEGRA_GEM_FLAGS		(DRM_TEGRA_GEM_BOTTOM_UP)

/**
 * काष्ठा drm_tegra_gem_set_flags - parameters क्रम the set flags IOCTL
 */
काष्ठा drm_tegra_gem_set_flags अणु
	/**
	 * @handle:
	 *
	 * Handle to the GEM object क्रम which to set the flags.
	 */
	__u32 handle;

	/**
	 * @flags:
	 *
	 * The flags to set क्रम the GEM object.
	 */
	__u32 flags;
पूर्ण;

/**
 * काष्ठा drm_tegra_gem_get_flags - parameters क्रम the get flags IOCTL
 */
काष्ठा drm_tegra_gem_get_flags अणु
	/**
	 * @handle:
	 *
	 * Handle to the GEM object क्रम which to query the flags.
	 */
	__u32 handle;

	/**
	 * @flags:
	 *
	 * The flags currently associated with the GEM object. Set by the
	 * kernel upon successful completion of the IOCTL.
	 */
	__u32 flags;
पूर्ण;

#घोषणा DRM_TEGRA_GEM_CREATE		0x00
#घोषणा DRM_TEGRA_GEM_MMAP		0x01
#घोषणा DRM_TEGRA_SYNCPT_READ		0x02
#घोषणा DRM_TEGRA_SYNCPT_INCR		0x03
#घोषणा DRM_TEGRA_SYNCPT_WAIT		0x04
#घोषणा DRM_TEGRA_OPEN_CHANNEL		0x05
#घोषणा DRM_TEGRA_CLOSE_CHANNEL		0x06
#घोषणा DRM_TEGRA_GET_SYNCPT		0x07
#घोषणा DRM_TEGRA_SUBMIT		0x08
#घोषणा DRM_TEGRA_GET_SYNCPT_BASE	0x09
#घोषणा DRM_TEGRA_GEM_SET_TILING	0x0a
#घोषणा DRM_TEGRA_GEM_GET_TILING	0x0b
#घोषणा DRM_TEGRA_GEM_SET_FLAGS		0x0c
#घोषणा DRM_TEGRA_GEM_GET_FLAGS		0x0d

#घोषणा DRM_IOCTL_TEGRA_GEM_CREATE DRM_IOWR(DRM_COMMAND_BASE + DRM_TEGRA_GEM_CREATE, काष्ठा drm_tegra_gem_create)
#घोषणा DRM_IOCTL_TEGRA_GEM_MMAP DRM_IOWR(DRM_COMMAND_BASE + DRM_TEGRA_GEM_MMAP, काष्ठा drm_tegra_gem_mmap)
#घोषणा DRM_IOCTL_TEGRA_SYNCPT_READ DRM_IOWR(DRM_COMMAND_BASE + DRM_TEGRA_SYNCPT_READ, काष्ठा drm_tegra_syncpt_पढ़ो)
#घोषणा DRM_IOCTL_TEGRA_SYNCPT_INCR DRM_IOWR(DRM_COMMAND_BASE + DRM_TEGRA_SYNCPT_INCR, काष्ठा drm_tegra_syncpt_incr)
#घोषणा DRM_IOCTL_TEGRA_SYNCPT_WAIT DRM_IOWR(DRM_COMMAND_BASE + DRM_TEGRA_SYNCPT_WAIT, काष्ठा drm_tegra_syncpt_रुको)
#घोषणा DRM_IOCTL_TEGRA_OPEN_CHANNEL DRM_IOWR(DRM_COMMAND_BASE + DRM_TEGRA_OPEN_CHANNEL, काष्ठा drm_tegra_खोलो_channel)
#घोषणा DRM_IOCTL_TEGRA_CLOSE_CHANNEL DRM_IOWR(DRM_COMMAND_BASE + DRM_TEGRA_CLOSE_CHANNEL, काष्ठा drm_tegra_बंद_channel)
#घोषणा DRM_IOCTL_TEGRA_GET_SYNCPT DRM_IOWR(DRM_COMMAND_BASE + DRM_TEGRA_GET_SYNCPT, काष्ठा drm_tegra_get_syncpt)
#घोषणा DRM_IOCTL_TEGRA_SUBMIT DRM_IOWR(DRM_COMMAND_BASE + DRM_TEGRA_SUBMIT, काष्ठा drm_tegra_submit)
#घोषणा DRM_IOCTL_TEGRA_GET_SYNCPT_BASE DRM_IOWR(DRM_COMMAND_BASE + DRM_TEGRA_GET_SYNCPT_BASE, काष्ठा drm_tegra_get_syncpt_base)
#घोषणा DRM_IOCTL_TEGRA_GEM_SET_TILING DRM_IOWR(DRM_COMMAND_BASE + DRM_TEGRA_GEM_SET_TILING, काष्ठा drm_tegra_gem_set_tiling)
#घोषणा DRM_IOCTL_TEGRA_GEM_GET_TILING DRM_IOWR(DRM_COMMAND_BASE + DRM_TEGRA_GEM_GET_TILING, काष्ठा drm_tegra_gem_get_tiling)
#घोषणा DRM_IOCTL_TEGRA_GEM_SET_FLAGS DRM_IOWR(DRM_COMMAND_BASE + DRM_TEGRA_GEM_SET_FLAGS, काष्ठा drm_tegra_gem_set_flags)
#घोषणा DRM_IOCTL_TEGRA_GEM_GET_FLAGS DRM_IOWR(DRM_COMMAND_BASE + DRM_TEGRA_GEM_GET_FLAGS, काष्ठा drm_tegra_gem_get_flags)

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
