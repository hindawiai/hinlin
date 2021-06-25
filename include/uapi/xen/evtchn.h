<शैली गुरु>
/* SPDX-License-Identअगरier: ((GPL-2.0 WITH Linux-syscall-note) OR MIT) */
/******************************************************************************
 * evtchn.h
 *
 * Interface to /dev/xen/evtchn.
 *
 * Copyright (c) 2003-2005, K A Fraser
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#अगर_अघोषित __LINUX_PUBLIC_EVTCHN_H__
#घोषणा __LINUX_PUBLIC_EVTCHN_H__

/*
 * Bind a fresh port to VIRQ @virq.
 * Return allocated port.
 */
#घोषणा IOCTL_EVTCHN_BIND_VIRQ				\
	_IOC(_IOC_NONE, 'E', 0, माप(काष्ठा ioctl_evtchn_bind_virq))
काष्ठा ioctl_evtchn_bind_virq अणु
	अचिन्हित पूर्णांक virq;
पूर्ण;

/*
 * Bind a fresh port to remote <@remote_करोमुख्य, @remote_port>.
 * Return allocated port.
 */
#घोषणा IOCTL_EVTCHN_BIND_INTERDOMAIN			\
	_IOC(_IOC_NONE, 'E', 1, माप(काष्ठा ioctl_evtchn_bind_पूर्णांकerकरोमुख्य))
काष्ठा ioctl_evtchn_bind_पूर्णांकerकरोमुख्य अणु
	अचिन्हित पूर्णांक remote_करोमुख्य, remote_port;
पूर्ण;

/*
 * Allocate a fresh port क्रम binding to @remote_करोमुख्य.
 * Return allocated port.
 */
#घोषणा IOCTL_EVTCHN_BIND_UNBOUND_PORT			\
	_IOC(_IOC_NONE, 'E', 2, माप(काष्ठा ioctl_evtchn_bind_unbound_port))
काष्ठा ioctl_evtchn_bind_unbound_port अणु
	अचिन्हित पूर्णांक remote_करोमुख्य;
पूर्ण;

/*
 * Unbind previously allocated @port.
 */
#घोषणा IOCTL_EVTCHN_UNBIND				\
	_IOC(_IOC_NONE, 'E', 3, माप(काष्ठा ioctl_evtchn_unbind))
काष्ठा ioctl_evtchn_unbind अणु
	अचिन्हित पूर्णांक port;
पूर्ण;

/*
 * Unbind previously allocated @port.
 */
#घोषणा IOCTL_EVTCHN_NOTIFY				\
	_IOC(_IOC_NONE, 'E', 4, माप(काष्ठा ioctl_evtchn_notअगरy))
काष्ठा ioctl_evtchn_notअगरy अणु
	अचिन्हित पूर्णांक port;
पूर्ण;

/* Clear and reinitialise the event buffer. Clear error condition. */
#घोषणा IOCTL_EVTCHN_RESET				\
	_IOC(_IOC_NONE, 'E', 5, 0)

/*
 * Restrict this file descriptor so that it can only be used to bind
 * new पूर्णांकerकरोमुख्य events from one करोमुख्य.
 *
 * Once a file descriptor has been restricted it cannot be
 * de-restricted, and must be बंदd and re-खोलोed.  Event channels
 * which were bound beक्रमe restricting reमुख्य bound afterwards, and
 * can be notअगरied as usual.
 */
#घोषणा IOCTL_EVTCHN_RESTRICT_DOMID			\
	_IOC(_IOC_NONE, 'E', 6, माप(काष्ठा ioctl_evtchn_restrict_करोmid))
काष्ठा ioctl_evtchn_restrict_करोmid अणु
	करोmid_t करोmid;
पूर्ण;

#पूर्ण_अगर /* __LINUX_PUBLIC_EVTCHN_H__ */
