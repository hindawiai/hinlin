<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0+ WITH Linux-syscall-note) OR BSD-3-Clause) */
/*
 * include/linux/v4l2-common.h
 *
 * Common V4L2 and V4L2 subdev definitions.
 *
 * Users are advised to #समावेश this file either through videodev2.h
 * (V4L2) or through v4l2-subdev.h (V4L2 subdev) rather than to refer
 * to this file directly.
 *
 * Copyright (C) 2012 Nokia Corporation
 * Contact: Sakari Ailus <sakari.ailus@iki.fi>
 *
 *  This program is मुक्त software; you can redistribute it and/or modअगरy
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License क्रम more details.
 *
 *  Alternatively you can redistribute this file under the terms of the
 *  BSD license as stated below:
 *
 *  Redistribution and use in source and binary क्रमms, with or without
 *  modअगरication, are permitted provided that the following conditions
 *  are met:
 *  1. Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *  2. Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the करोcumentation and/or other materials provided with the
 *     distribution.
 *  3. The names of its contributors may not be used to enकरोrse or promote
 *     products derived from this software without specअगरic prior written
 *     permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 *  TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 *  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 *  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 *  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 *  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#अगर_अघोषित __V4L2_COMMON__
#घोषणा __V4L2_COMMON__

#समावेश <linux/types.h>

/*
 *
 * Selection पूर्णांकerface definitions
 *
 */

/* Current cropping area */
#घोषणा V4L2_SEL_TGT_CROP		0x0000
/* Default cropping area */
#घोषणा V4L2_SEL_TGT_CROP_DEFAULT	0x0001
/* Cropping bounds */
#घोषणा V4L2_SEL_TGT_CROP_BOUNDS	0x0002
/* Native frame size */
#घोषणा V4L2_SEL_TGT_NATIVE_SIZE	0x0003
/* Current composing area */
#घोषणा V4L2_SEL_TGT_COMPOSE		0x0100
/* Default composing area */
#घोषणा V4L2_SEL_TGT_COMPOSE_DEFAULT	0x0101
/* Composing bounds */
#घोषणा V4L2_SEL_TGT_COMPOSE_BOUNDS	0x0102
/* Current composing area plus all padding pixels */
#घोषणा V4L2_SEL_TGT_COMPOSE_PADDED	0x0103

/* Selection flags */
#घोषणा V4L2_SEL_FLAG_GE		(1 << 0)
#घोषणा V4L2_SEL_FLAG_LE		(1 << 1)
#घोषणा V4L2_SEL_FLAG_KEEP_CONFIG	(1 << 2)

काष्ठा v4l2_edid अणु
	__u32 pad;
	__u32 start_block;
	__u32 blocks;
	__u32 reserved[5];
	__u8  *edid;
पूर्ण;

#अगर_अघोषित __KERNEL__
/* Backward compatibility target definitions --- to be हटाओd. */
#घोषणा V4L2_SEL_TGT_CROP_ACTIVE	V4L2_SEL_TGT_CROP
#घोषणा V4L2_SEL_TGT_COMPOSE_ACTIVE	V4L2_SEL_TGT_COMPOSE
#घोषणा V4L2_SUBDEV_SEL_TGT_CROP_ACTUAL	V4L2_SEL_TGT_CROP
#घोषणा V4L2_SUBDEV_SEL_TGT_COMPOSE_ACTUAL V4L2_SEL_TGT_COMPOSE
#घोषणा V4L2_SUBDEV_SEL_TGT_CROP_BOUNDS	V4L2_SEL_TGT_CROP_BOUNDS
#घोषणा V4L2_SUBDEV_SEL_TGT_COMPOSE_BOUNDS V4L2_SEL_TGT_COMPOSE_BOUNDS

/* Backward compatibility flag definitions --- to be हटाओd. */
#घोषणा V4L2_SUBDEV_SEL_FLAG_SIZE_GE	V4L2_SEL_FLAG_GE
#घोषणा V4L2_SUBDEV_SEL_FLAG_SIZE_LE	V4L2_SEL_FLAG_LE
#घोषणा V4L2_SUBDEV_SEL_FLAG_KEEP_CONFIG V4L2_SEL_FLAG_KEEP_CONFIG
#पूर्ण_अगर

#पूर्ण_अगर /* __V4L2_COMMON__ */
