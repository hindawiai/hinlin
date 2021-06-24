<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Definitions क्रम the HIPPI handlers.
 *
 * Version:	@(#)hippidevice.h	1.0.0	05/26/97
 *
 * Author:	Jes Sorensen, <Jes.Sorensen@cern.ch>
 *
 *		hippidevice.h is based on previous fddidevice.h work by
 *			Ross Biro
 *			Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *			Alan Cox, <gw4pts@gw4pts.ampr.org>
 *			Lawrence V. Stefani, <stefani@lkg.dec.com>
 */
#अगर_अघोषित _LINUX_HIPPIDEVICE_H
#घोषणा _LINUX_HIPPIDEVICE_H

#समावेश <linux/अगर_hippi.h>

#अगर_घोषित __KERNEL__

काष्ठा hippi_cb अणु
	__u32	अगरield;
पूर्ण;

__be16 hippi_type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
पूर्णांक hippi_mac_addr(काष्ठा net_device *dev, व्योम *p);
पूर्णांक hippi_neigh_setup_dev(काष्ठा net_device *dev, काष्ठा neigh_parms *p);
काष्ठा net_device *alloc_hippi_dev(पूर्णांक माप_priv);
#पूर्ण_अगर

#पूर्ण_अगर	/* _LINUX_HIPPIDEVICE_H */
