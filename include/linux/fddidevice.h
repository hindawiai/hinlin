<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the FDDI handlers.
 *
 * Version:	@(#)fddidevice.h	1.0.0	08/12/96
 *
 * Author:	Lawrence V. Stefani, <stefani@lkg.dec.com>
 *
 *		fddidevice.h is based on previous trdevice.h work by
 *			Ross Biro
 *			Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *			Alan Cox, <gw4pts@gw4pts.ampr.org>
 */
#अगर_अघोषित _LINUX_FDDIDEVICE_H
#घोषणा _LINUX_FDDIDEVICE_H

#समावेश <linux/अगर_fddi.h>

#अगर_घोषित __KERNEL__
__be16 fddi_type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
काष्ठा net_device *alloc_fddidev(पूर्णांक माप_priv);
#पूर्ण_अगर

#पूर्ण_अगर	/* _LINUX_FDDIDEVICE_H */
