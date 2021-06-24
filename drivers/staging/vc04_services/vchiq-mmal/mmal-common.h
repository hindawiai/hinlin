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
 *
 * MMAL काष्ठाures
 *
 */
#अगर_अघोषित MMAL_COMMON_H
#घोषणा MMAL_COMMON_H

#घोषणा MMAL_FOURCC(a, b, c, d) ((a) | (b << 8) | (c << 16) | (d << 24))
#घोषणा MMAL_MAGIC MMAL_FOURCC('m', 'm', 'a', 'l')

/** Special value संकेतling that समय is not known */
#घोषणा MMAL_TIME_UNKNOWN BIT_ULL(63)

काष्ठा mmal_msg_context;

/* mapping between v4l and mmal video modes */
काष्ठा mmal_fmt अणु
	u32 fourcc;          /* v4l2 क्रमmat id */
	पूर्णांक flags;           /* v4l2 flags field */
	u32 mmal;
	पूर्णांक depth;
	u32 mmal_component;  /* MMAL component index to be used to encode */
	u32 ybbp;            /* depth of first Y plane क्रम planar क्रमmats */
	bool हटाओ_padding;   /* Does the GPU have to हटाओ padding,
				* or can we करो hide padding via bytesperline.
				*/
पूर्ण;

/* buffer क्रम one video frame */
काष्ठा mmal_buffer अणु
	/* v4l buffer data -- must be first */
	काष्ठा vb2_v4l2_buffer vb;

	/* list of buffers available */
	काष्ठा list_head list;

	व्योम *buffer; /* buffer poपूर्णांकer */
	अचिन्हित दीर्घ buffer_size; /* size of allocated buffer */

	काष्ठा mmal_msg_context *msg_context;

	अचिन्हित दीर्घ length;
	u32 mmal_flags;
	s64 dts;
	s64 pts;
पूर्ण;

/* */
काष्ठा mmal_colourfx अणु
	s32 enable;
	u32 u;
	u32 v;
पूर्ण;
#पूर्ण_अगर
