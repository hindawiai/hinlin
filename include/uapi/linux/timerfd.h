<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 *  include/linux/समयrfd.h
 *
 *  Copyright (C) 2007  Davide Libenzi <davidel@xmailserver.org>
 *
 */

#अगर_अघोषित _UAPI_LINUX_TIMERFD_H
#घोषणा _UAPI_LINUX_TIMERFD_H

#समावेश <linux/types.h>

/* For O_CLOEXEC and O_NONBLOCK */
#समावेश <linux/fcntl.h>

/* For _IO helpers */
#समावेश <linux/ioctl.h>

/*
 * CAREFUL: Check include/यंत्र-generic/fcntl.h when defining
 * new flags, since they might collide with O_* ones. We want
 * to re-use O_* flags that couldn't possibly have a meaning
 * from eventfd, in order to leave a मुक्त define-space क्रम
 * shared O_* flags.
 *
 * Also make sure to update the masks in include/linux/समयrfd.h
 * when adding new flags.
 */
#घोषणा TFD_TIMER_ABSTIME (1 << 0)
#घोषणा TFD_TIMER_CANCEL_ON_SET (1 << 1)
#घोषणा TFD_CLOEXEC O_CLOEXEC
#घोषणा TFD_NONBLOCK O_NONBLOCK

#घोषणा TFD_IOC_SET_TICKS	_IOW('T', 0, __u64)

#पूर्ण_अगर /* _UAPI_LINUX_TIMERFD_H */
