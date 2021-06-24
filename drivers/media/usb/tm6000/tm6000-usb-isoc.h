<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * पंचांग6000-buf.c - driver क्रम TM5600/TM6000/TM6010 USB video capture devices
 *
 * Copyright (c) 2006-2007 Mauro Carvalho Chehab <mchehab@kernel.org>
 */

#समावेश <linux/videodev2.h>

#घोषणा TM6000_URB_MSG_LEN 180

काष्ठा usb_isoc_ctl अणु
		/* max packet size of isoc transaction */
	पूर्णांक				max_pkt_size;

		/* number of allocated urbs */
	पूर्णांक				num_bufs;

		/* urb क्रम isoc transfers */
	काष्ठा urb			**urb;

		/* transfer buffers क्रम isoc transfer */
	अक्षर				**transfer_buffer;

		/* Last buffer command and region */
	u8				cmd;
	पूर्णांक				pos, size, pktsize;

		/* Last field: ODD or EVEN? */
	पूर्णांक				vfield, field;

		/* Stores incomplete commands */
	u32				पंचांगp_buf;
	पूर्णांक				पंचांगp_buf_len;

		/* Stores alपढ़ोy requested buffers */
	काष्ठा पंचांग6000_buffer		*buf;
पूर्ण;
