<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR MPL-1.1) */
/* p80211ioctl.h
 *
 * Declares स्थिरants and types क्रम the p80211 ioctls
 *
 * Copyright (C) 1999 AbsoluteValue Systems, Inc.  All Rights Reserved.
 * --------------------------------------------------------------------
 *
 * linux-wlan
 *
 *   The contents of this file are subject to the Mozilla Public
 *   License Version 1.1 (the "License"); you may not use this file
 *   except in compliance with the License. You may obtain a copy of
 *   the License at http://www.mozilla.org/MPL/
 *
 *   Software distributed under the License is distributed on an "AS
 *   IS" basis, WITHOUT WARRANTY OF ANY KIND, either express or
 *   implied. See the License क्रम the specअगरic language governing
 *   rights and limitations under the License.
 *
 *   Alternatively, the contents of this file may be used under the
 *   terms of the GNU Public License version 2 (the "GPL"), in which
 *   हाल the provisions of the GPL are applicable instead of the
 *   above.  If you wish to allow the use of your version of this file
 *   only under the terms of the GPL and not to allow others to use
 *   your version of this file under the MPL, indicate your decision
 *   by deleting the provisions above and replace them with the notice
 *   and other provisions required by the GPL.  If you करो not delete
 *   the provisions above, a recipient may use your version of this
 *   file under either the MPL or the GPL.
 *
 * --------------------------------------------------------------------
 *
 * Inquiries regarding the linux-wlan Open Source project can be
 * made directly to:
 *
 * AbsoluteValue Systems Inc.
 * info@linux-wlan.com
 * http://www.linux-wlan.com
 *
 * --------------------------------------------------------------------
 *
 * Portions of the development of this software were funded by
 * Intersil Corporation as part of PRISM(R) chipset product development.
 *
 * --------------------------------------------------------------------
 *
 *  While this file is called 'ioctl' is purpose goes a little beyond
 *  that.  This file defines the types and contants used to implement
 *  the p80211 request/confirm/indicate पूर्णांकerfaces on Linux.  The
 *  request/confirm पूर्णांकerface is, in fact, normally implemented as an
 *  ioctl.  The indicate पूर्णांकerface on the other hand, is implemented
 *  using the Linux 'netlink' पूर्णांकerface.
 *
 *  The reason I say that request/confirm is 'normally' implemented
 *  via ioctl is that we're reserving the right to be able to send
 *  request commands via the netlink पूर्णांकerface.  This will be necessary
 *  अगर we ever need to send request messages when there aren't any
 *  wlan network devices present (i.e. sending a message that only p80211
 *  cares about.
 * --------------------------------------------------------------------
 */

#अगर_अघोषित _P80211IOCTL_H
#घोषणा _P80211IOCTL_H

/* p80211 ioctl "request" codes.  See argument 2 of ioctl(2). */

#घोषणा P80211_IFTEST		(SIOCDEVPRIVATE + 0)
#घोषणा P80211_IFREQ		(SIOCDEVPRIVATE + 1)

/*----------------------------------------------------------------*/
/* Magic number, a quick test to see we're getting the desired काष्ठा */

#घोषणा P80211_IOCTL_MAGIC	(0x4a2d464dUL)

/*----------------------------------------------------------------*/
/* A ptr to the following काष्ठाure type is passed as the third */
/*  argument to the ioctl प्रणाली call when issuing a request to */
/*  the p80211 module. */

काष्ठा p80211ioctl_req अणु
	अक्षर name[WLAN_DEVNAMELEN_MAX];
	caddr_t data;
	u32 magic;
	u16 len;
	u32 result;
पूर्ण __packed;

#पूर्ण_अगर /* _P80211IOCTL_H */
