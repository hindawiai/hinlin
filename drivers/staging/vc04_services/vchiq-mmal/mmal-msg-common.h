<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Broadcom BM2835 V4L2 driver
 *
 * Copyright तऊ 2013 Raspberry Pi (Trading) Ltd.
 *
 * Authors: Vincent Sanders @ Collabora
 *          Dave Stevenson @ Broadcom
 *		(now dave.stevenson@raspberrypi.org)
 *          Simon Mellor @ Broadcom
 *          Luke Diamand @ Broadcom
 */

#अगर_अघोषित MMAL_MSG_COMMON_H
#घोषणा MMAL_MSG_COMMON_H

क्रमागत mmal_msg_status अणु
	MMAL_MSG_STATUS_SUCCESS = 0, /**< Success */
	MMAL_MSG_STATUS_ENOMEM,      /**< Out of memory */
	MMAL_MSG_STATUS_ENOSPC,      /**< Out of resources other than memory */
	MMAL_MSG_STATUS_EINVAL,      /**< Argument is invalid */
	MMAL_MSG_STATUS_ENOSYS,      /**< Function not implemented */
	MMAL_MSG_STATUS_ENOENT,      /**< No such file or directory */
	MMAL_MSG_STATUS_ENXIO,       /**< No such device or address */
	MMAL_MSG_STATUS_EIO,         /**< I/O error */
	MMAL_MSG_STATUS_ESPIPE,      /**< Illegal seek */
	MMAL_MSG_STATUS_ECORRUPT,    /**< Data is corrupt \चttention */
	MMAL_MSG_STATUS_ENOTREADY,   /**< Component is not पढ़ोy */
	MMAL_MSG_STATUS_ECONFIG,     /**< Component is not configured */
	MMAL_MSG_STATUS_EISCONN,     /**< Port is alपढ़ोy connected */
	MMAL_MSG_STATUS_ENOTCONN,    /**< Port is disconnected */
	MMAL_MSG_STATUS_EAGAIN,      /**< Resource temporarily unavailable. */
	MMAL_MSG_STATUS_EFAULT,      /**< Bad address */
पूर्ण;

काष्ठा mmal_rect अणु
	s32 x;      /**< x coordinate (from left) */
	s32 y;      /**< y coordinate (from top) */
	s32 width;  /**< width */
	s32 height; /**< height */
पूर्ण;

काष्ठा mmal_rational अणु
	s32 num;    /**< Numerator */
	s32 den;    /**< Denominator */
पूर्ण;

#पूर्ण_अगर /* MMAL_MSG_COMMON_H */
