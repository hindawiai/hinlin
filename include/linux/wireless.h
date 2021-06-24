<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This file define a set of standard wireless extensions
 *
 * Version :	22	16.3.07
 *
 * Authors :	Jean Tourrilhes - HPL - <jt@hpl.hp.com>
 * Copyright (c) 1997-2007 Jean Tourrilhes, All Rights Reserved.
 */
#अगर_अघोषित _LINUX_WIRELESS_H
#घोषणा _LINUX_WIRELESS_H

#समावेश <uapi/linux/wireless.h>

#अगर_घोषित CONFIG_COMPAT

#समावेश <linux/compat.h>

काष्ठा compat_iw_poपूर्णांक अणु
	compat_caddr_t poपूर्णांकer;
	__u16 length;
	__u16 flags;
पूर्ण;
#पूर्ण_अगर
#अगर_घोषित CONFIG_COMPAT
काष्ठा __compat_iw_event अणु
	__u16		len;			/* Real length of this stuff */
	__u16		cmd;			/* Wireless IOCTL */
	compat_caddr_t	poपूर्णांकer;
पूर्ण;
#घोषणा IW_EV_COMPAT_LCP_LEN दुरत्व(काष्ठा __compat_iw_event, poपूर्णांकer)
#घोषणा IW_EV_COMPAT_POINT_OFF दुरत्व(काष्ठा compat_iw_poपूर्णांक, length)

/* Size of the various events क्रम compat */
#घोषणा IW_EV_COMPAT_CHAR_LEN	(IW_EV_COMPAT_LCP_LEN + IFNAMSIZ)
#घोषणा IW_EV_COMPAT_UINT_LEN	(IW_EV_COMPAT_LCP_LEN + माप(__u32))
#घोषणा IW_EV_COMPAT_FREQ_LEN	(IW_EV_COMPAT_LCP_LEN + माप(काष्ठा iw_freq))
#घोषणा IW_EV_COMPAT_PARAM_LEN	(IW_EV_COMPAT_LCP_LEN + माप(काष्ठा iw_param))
#घोषणा IW_EV_COMPAT_ADDR_LEN	(IW_EV_COMPAT_LCP_LEN + माप(काष्ठा sockaddr))
#घोषणा IW_EV_COMPAT_QUAL_LEN	(IW_EV_COMPAT_LCP_LEN + माप(काष्ठा iw_quality))
#घोषणा IW_EV_COMPAT_POINT_LEN	\
	(IW_EV_COMPAT_LCP_LEN + माप(काष्ठा compat_iw_poपूर्णांक) - \
	 IW_EV_COMPAT_POINT_OFF)
#पूर्ण_अगर
#पूर्ण_अगर	/* _LINUX_WIRELESS_H */
