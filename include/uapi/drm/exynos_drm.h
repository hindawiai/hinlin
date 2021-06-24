<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0+ WITH Linux-syscall-note */
/* exynos_drm.h
 *
 * Copyright (c) 2011 Samsung Electronics Co., Ltd.
 * Authors:
 *	Inki Dae <inki.dae@samsung.com>
 *	Joonyoung Shim <jy0922.shim@samsung.com>
 *	Seung-Woo Kim <sw0312.kim@samsung.com>
 *
 * This program is मुक्त software; you can redistribute  it and/or modअगरy it
 * under  the terms of  the GNU General  Public License as published by the
 * Free Software Foundation;  either version 2 of the  License, or (at your
 * option) any later version.
 */

#अगर_अघोषित _UAPI_EXYNOS_DRM_H_
#घोषणा _UAPI_EXYNOS_DRM_H_

#समावेश "drm.h"

#अगर defined(__cplusplus)
बाह्य "C" अणु
#पूर्ण_अगर

/**
 * User-desired buffer creation inक्रमmation काष्ठाure.
 *
 * @size: user-desired memory allocation size.
 *	- this size value would be page-aligned पूर्णांकernally.
 * @flags: user request क्रम setting memory type or cache attributes.
 * @handle: वापसed a handle to created gem object.
 *	- this handle will be set by gem module of kernel side.
 */
काष्ठा drm_exynos_gem_create अणु
	__u64 size;
	__u32 flags;
	__u32 handle;
पूर्ण;

/**
 * A काष्ठाure क्रम getting a fake-offset that can be used with mmap.
 *
 * @handle: handle of gem object.
 * @reserved: just padding to be 64-bit aligned.
 * @offset: a fake-offset of gem object.
 */
काष्ठा drm_exynos_gem_map अणु
	__u32 handle;
	__u32 reserved;
	__u64 offset;
पूर्ण;

/**
 * A काष्ठाure to gem inक्रमmation.
 *
 * @handle: a handle to gem object created.
 * @flags: flag value including memory type and cache attribute and
 *	this value would be set by driver.
 * @size: size to memory region allocated by gem and this size would
 *	be set by driver.
 */
काष्ठा drm_exynos_gem_info अणु
	__u32 handle;
	__u32 flags;
	__u64 size;
पूर्ण;

/**
 * A काष्ठाure क्रम user connection request of भव display.
 *
 * @connection: indicate whether करोing connection or not by user.
 * @extensions: अगर this value is 1 then the vidi driver would need additional
 *	128bytes edid data.
 * @edid: the edid data poपूर्णांकer from user side.
 */
काष्ठा drm_exynos_vidi_connection अणु
	__u32 connection;
	__u32 extensions;
	__u64 edid;
पूर्ण;

/* memory type definitions. */
क्रमागत e_drm_exynos_gem_mem_type अणु
	/* Physically Continuous memory and used as शेष. */
	EXYNOS_BO_CONTIG	= 0 << 0,
	/* Physically Non-Continuous memory. */
	EXYNOS_BO_NONCONTIG	= 1 << 0,
	/* non-cachable mapping and used as शेष. */
	EXYNOS_BO_NONCACHABLE	= 0 << 1,
	/* cachable mapping. */
	EXYNOS_BO_CACHABLE	= 1 << 1,
	/* ग_लिखो-combine mapping. */
	EXYNOS_BO_WC		= 1 << 2,
	EXYNOS_BO_MASK		= EXYNOS_BO_NONCONTIG | EXYNOS_BO_CACHABLE |
					EXYNOS_BO_WC
पूर्ण;

काष्ठा drm_exynos_g2d_get_ver अणु
	__u32	major;
	__u32	minor;
पूर्ण;

काष्ठा drm_exynos_g2d_cmd अणु
	__u32	offset;
	__u32	data;
पूर्ण;

क्रमागत drm_exynos_g2d_buf_type अणु
	G2D_BUF_USERPTR = 1 << 31,
पूर्ण;

क्रमागत drm_exynos_g2d_event_type अणु
	G2D_EVENT_NOT,
	G2D_EVENT_NONSTOP,
	G2D_EVENT_STOP,		/* not yet */
पूर्ण;

काष्ठा drm_exynos_g2d_userptr अणु
	अचिन्हित दीर्घ userptr;
	अचिन्हित दीर्घ size;
पूर्ण;

काष्ठा drm_exynos_g2d_set_cmdlist अणु
	__u64					cmd;
	__u64					cmd_buf;
	__u32					cmd_nr;
	__u32					cmd_buf_nr;

	/* क्रम g2d event */
	__u64					event_type;
	__u64					user_data;
पूर्ण;

काष्ठा drm_exynos_g2d_exec अणु
	__u64					async;
पूर्ण;

/* Exynos DRM IPP v2 API */

/**
 * Enumerate available IPP hardware modules.
 *
 * @count_ipps: size of ipp_id array / number of ipp modules (set by driver)
 * @reserved: padding
 * @ipp_id_ptr: poपूर्णांकer to ipp_id array or शून्य
 */
काष्ठा drm_exynos_ioctl_ipp_get_res अणु
	__u32 count_ipps;
	__u32 reserved;
	__u64 ipp_id_ptr;
पूर्ण;

क्रमागत drm_exynos_ipp_क्रमmat_type अणु
	DRM_EXYNOS_IPP_FORMAT_SOURCE		= 0x01,
	DRM_EXYNOS_IPP_FORMAT_DESTINATION	= 0x02,
पूर्ण;

काष्ठा drm_exynos_ipp_क्रमmat अणु
	__u32 fourcc;
	__u32 type;
	__u64 modअगरier;
पूर्ण;

क्रमागत drm_exynos_ipp_capability अणु
	DRM_EXYNOS_IPP_CAP_CROP		= 0x01,
	DRM_EXYNOS_IPP_CAP_ROTATE	= 0x02,
	DRM_EXYNOS_IPP_CAP_SCALE	= 0x04,
	DRM_EXYNOS_IPP_CAP_CONVERT	= 0x08,
पूर्ण;

/**
 * Get IPP hardware capabilities and supported image क्रमmats.
 *
 * @ipp_id: id of IPP module to query
 * @capabilities: biपंचांगask of drm_exynos_ipp_capability (set by driver)
 * @reserved: padding
 * @क्रमmats_count: size of क्रमmats array (in entries) / number of filled
 *		   क्रमmats (set by driver)
 * @क्रमmats_ptr: poपूर्णांकer to क्रमmats array or शून्य
 */
काष्ठा drm_exynos_ioctl_ipp_get_caps अणु
	__u32 ipp_id;
	__u32 capabilities;
	__u32 reserved;
	__u32 क्रमmats_count;
	__u64 क्रमmats_ptr;
पूर्ण;

क्रमागत drm_exynos_ipp_limit_type अणु
	/* size (horizontal/vertial) limits, in pixels (min, max, alignment) */
	DRM_EXYNOS_IPP_LIMIT_TYPE_SIZE		= 0x0001,
	/* scale ratio (horizonta/vertial), 16.16 fixed poपूर्णांक (min, max) */
	DRM_EXYNOS_IPP_LIMIT_TYPE_SCALE		= 0x0002,

	/* image buffer area */
	DRM_EXYNOS_IPP_LIMIT_SIZE_BUFFER	= 0x0001 << 16,
	/* src/dst rectangle area */
	DRM_EXYNOS_IPP_LIMIT_SIZE_AREA		= 0x0002 << 16,
	/* src/dst rectangle area when rotation enabled */
	DRM_EXYNOS_IPP_LIMIT_SIZE_ROTATED	= 0x0003 << 16,

	DRM_EXYNOS_IPP_LIMIT_TYPE_MASK		= 0x000f,
	DRM_EXYNOS_IPP_LIMIT_SIZE_MASK		= 0x000f << 16,
पूर्ण;

काष्ठा drm_exynos_ipp_limit_val अणु
	__u32 min;
	__u32 max;
	__u32 align;
	__u32 reserved;
पूर्ण;

/**
 * IPP module limitation.
 *
 * @type: limit type (see drm_exynos_ipp_limit_type क्रमागत)
 * @reserved: padding
 * @h: horizontal limits
 * @v: vertical limits
 */
काष्ठा drm_exynos_ipp_limit अणु
	__u32 type;
	__u32 reserved;
	काष्ठा drm_exynos_ipp_limit_val h;
	काष्ठा drm_exynos_ipp_limit_val v;
पूर्ण;

/**
 * Get IPP limits क्रम given image क्रमmat.
 *
 * @ipp_id: id of IPP module to query
 * @fourcc: image क्रमmat code (see DRM_FORMAT_* in drm_fourcc.h)
 * @modअगरier: image क्रमmat modअगरier (see DRM_FORMAT_MOD_* in drm_fourcc.h)
 * @type: source/destination identअगरier (drm_exynos_ipp_क्रमmat_flag क्रमागत)
 * @limits_count: size of limits array (in entries) / number of filled entries
 *		 (set by driver)
 * @limits_ptr: poपूर्णांकer to limits array or शून्य
 */
काष्ठा drm_exynos_ioctl_ipp_get_limits अणु
	__u32 ipp_id;
	__u32 fourcc;
	__u64 modअगरier;
	__u32 type;
	__u32 limits_count;
	__u64 limits_ptr;
पूर्ण;

क्रमागत drm_exynos_ipp_task_id अणु
	/* buffer described by काष्ठा drm_exynos_ipp_task_buffer */
	DRM_EXYNOS_IPP_TASK_BUFFER		= 0x0001,
	/* rectangle described by काष्ठा drm_exynos_ipp_task_rect */
	DRM_EXYNOS_IPP_TASK_RECTANGLE		= 0x0002,
	/* transक्रमmation described by काष्ठा drm_exynos_ipp_task_transक्रमm */
	DRM_EXYNOS_IPP_TASK_TRANSFORM		= 0x0003,
	/* alpha configuration described by काष्ठा drm_exynos_ipp_task_alpha */
	DRM_EXYNOS_IPP_TASK_ALPHA		= 0x0004,

	/* source image data (क्रम buffer and rectangle chunks) */
	DRM_EXYNOS_IPP_TASK_TYPE_SOURCE		= 0x0001 << 16,
	/* destination image data (क्रम buffer and rectangle chunks) */
	DRM_EXYNOS_IPP_TASK_TYPE_DESTINATION	= 0x0002 << 16,
पूर्ण;

/**
 * Memory buffer with image data.
 *
 * @id: must be DRM_EXYNOS_IPP_TASK_BUFFER
 * other parameters are same as क्रम AddFB2 generic DRM ioctl
 */
काष्ठा drm_exynos_ipp_task_buffer अणु
	__u32	id;
	__u32	fourcc;
	__u32	width, height;
	__u32	gem_id[4];
	__u32	offset[4];
	__u32	pitch[4];
	__u64	modअगरier;
पूर्ण;

/**
 * Rectangle क्रम processing.
 *
 * @id: must be DRM_EXYNOS_IPP_TASK_RECTANGLE
 * @reserved: padding
 * @x,@y: left corner in pixels
 * @w,@h: width/height in pixels
 */
काष्ठा drm_exynos_ipp_task_rect अणु
	__u32	id;
	__u32	reserved;
	__u32	x;
	__u32	y;
	__u32	w;
	__u32	h;
पूर्ण;

/**
 * Image tranक्रमmation description.
 *
 * @id: must be DRM_EXYNOS_IPP_TASK_TRANSFORM
 * @rotation: DRM_MODE_ROTATE_* and DRM_MODE_REFLECT_* values
 */
काष्ठा drm_exynos_ipp_task_transक्रमm अणु
	__u32	id;
	__u32	rotation;
पूर्ण;

/**
 * Image global alpha configuration क्रम क्रमmats without alpha values.
 *
 * @id: must be DRM_EXYNOS_IPP_TASK_ALPHA
 * @value: global alpha value (0-255)
 */
काष्ठा drm_exynos_ipp_task_alpha अणु
	__u32	id;
	__u32	value;
पूर्ण;

क्रमागत drm_exynos_ipp_flag अणु
	/* generate DRM event after processing */
	DRM_EXYNOS_IPP_FLAG_EVENT	= 0x01,
	/* dry run, only check task parameters */
	DRM_EXYNOS_IPP_FLAG_TEST_ONLY	= 0x02,
	/* non-blocking processing */
	DRM_EXYNOS_IPP_FLAG_NONBLOCK	= 0x04,
पूर्ण;

#घोषणा DRM_EXYNOS_IPP_FLAGS (DRM_EXYNOS_IPP_FLAG_EVENT |\
		DRM_EXYNOS_IPP_FLAG_TEST_ONLY | DRM_EXYNOS_IPP_FLAG_NONBLOCK)

/**
 * Perक्रमm image processing described by array of drm_exynos_ipp_task_*
 * काष्ठाures (parameters array).
 *
 * @ipp_id: id of IPP module to run the task
 * @flags: biपंचांगask of drm_exynos_ipp_flag values
 * @reserved: padding
 * @params_size: size of parameters array (in bytes)
 * @params_ptr: poपूर्णांकer to parameters array or शून्य
 * @user_data: (optional) data क्रम drm event
 */
काष्ठा drm_exynos_ioctl_ipp_commit अणु
	__u32 ipp_id;
	__u32 flags;
	__u32 reserved;
	__u32 params_size;
	__u64 params_ptr;
	__u64 user_data;
पूर्ण;

#घोषणा DRM_EXYNOS_GEM_CREATE		0x00
#घोषणा DRM_EXYNOS_GEM_MAP		0x01
/* Reserved 0x03 ~ 0x05 क्रम exynos specअगरic gem ioctl */
#घोषणा DRM_EXYNOS_GEM_GET		0x04
#घोषणा DRM_EXYNOS_VIDI_CONNECTION	0x07

/* G2D */
#घोषणा DRM_EXYNOS_G2D_GET_VER		0x20
#घोषणा DRM_EXYNOS_G2D_SET_CMDLIST	0x21
#घोषणा DRM_EXYNOS_G2D_EXEC		0x22

/* Reserved 0x30 ~ 0x33 क्रम obsolete Exynos IPP ioctls */
/* IPP - Image Post Processing */
#घोषणा DRM_EXYNOS_IPP_GET_RESOURCES	0x40
#घोषणा DRM_EXYNOS_IPP_GET_CAPS		0x41
#घोषणा DRM_EXYNOS_IPP_GET_LIMITS	0x42
#घोषणा DRM_EXYNOS_IPP_COMMIT		0x43

#घोषणा DRM_IOCTL_EXYNOS_GEM_CREATE		DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_GEM_CREATE, काष्ठा drm_exynos_gem_create)
#घोषणा DRM_IOCTL_EXYNOS_GEM_MAP		DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_GEM_MAP, काष्ठा drm_exynos_gem_map)
#घोषणा DRM_IOCTL_EXYNOS_GEM_GET	DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_GEM_GET,	काष्ठा drm_exynos_gem_info)

#घोषणा DRM_IOCTL_EXYNOS_VIDI_CONNECTION	DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_VIDI_CONNECTION, काष्ठा drm_exynos_vidi_connection)

#घोषणा DRM_IOCTL_EXYNOS_G2D_GET_VER		DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_G2D_GET_VER, काष्ठा drm_exynos_g2d_get_ver)
#घोषणा DRM_IOCTL_EXYNOS_G2D_SET_CMDLIST	DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_G2D_SET_CMDLIST, काष्ठा drm_exynos_g2d_set_cmdlist)
#घोषणा DRM_IOCTL_EXYNOS_G2D_EXEC		DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_G2D_EXEC, काष्ठा drm_exynos_g2d_exec)

#घोषणा DRM_IOCTL_EXYNOS_IPP_GET_RESOURCES	DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_IPP_GET_RESOURCES, \
		काष्ठा drm_exynos_ioctl_ipp_get_res)
#घोषणा DRM_IOCTL_EXYNOS_IPP_GET_CAPS		DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_IPP_GET_CAPS, काष्ठा drm_exynos_ioctl_ipp_get_caps)
#घोषणा DRM_IOCTL_EXYNOS_IPP_GET_LIMITS		DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_IPP_GET_LIMITS, \
		काष्ठा drm_exynos_ioctl_ipp_get_limits)
#घोषणा DRM_IOCTL_EXYNOS_IPP_COMMIT		DRM_IOWR(DRM_COMMAND_BASE + \
		DRM_EXYNOS_IPP_COMMIT, काष्ठा drm_exynos_ioctl_ipp_commit)

/* Exynos specअगरic events */
#घोषणा DRM_EXYNOS_G2D_EVENT		0x80000000
#घोषणा DRM_EXYNOS_IPP_EVENT		0x80000002

काष्ठा drm_exynos_g2d_event अणु
	काष्ठा drm_event	base;
	__u64			user_data;
	__u32			tv_sec;
	__u32			tv_usec;
	__u32			cmdlist_no;
	__u32			reserved;
पूर्ण;

काष्ठा drm_exynos_ipp_event अणु
	काष्ठा drm_event	base;
	__u64			user_data;
	__u32			tv_sec;
	__u32			tv_usec;
	__u32			ipp_id;
	__u32			sequence;
	__u64			reserved;
पूर्ण;

#अगर defined(__cplusplus)
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* _UAPI_EXYNOS_DRM_H_ */
