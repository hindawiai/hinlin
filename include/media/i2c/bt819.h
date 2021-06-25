<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
    bt819.h - bt819 notअगरications

    Copyright (C) 2009 Hans Verkuil (hverkuil@xs4all.nl)

*/

#अगर_अघोषित _BT819_H_
#घोषणा _BT819_H_

#समावेश <linux/ioctl.h>

/* v4l2_device notअगरications. */

/* Needed to reset the FIFO buffer when changing the input
   or the video standard.

   Note: these ioctls that पूर्णांकernal to the kernel and are never called
   from userspace. */
#घोषणा BT819_FIFO_RESET_LOW	_IO('b', 0)
#घोषणा BT819_FIFO_RESET_HIGH	_IO('b', 1)

#पूर्ण_अगर
