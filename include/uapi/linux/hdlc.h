<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * Generic HDLC support routines क्रम Linux
 *
 * Copyright (C) 1999-2005 Krzysztof Halasa <khc@pm.waw.pl>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of version 2 of the GNU General Public License
 * as published by the Free Software Foundation.
 */

#अगर_अघोषित _UAPI__HDLC_H
#घोषणा _UAPI__HDLC_H


#घोषणा HDLC_MAX_MTU 1500	/* Ethernet 1500 bytes */
#अगर 0
#घोषणा HDLC_MAX_MRU (HDLC_MAX_MTU + 10 + 14 + 4) /* क्रम ETH+VLAN over FR */
#अन्यथा
#घोषणा HDLC_MAX_MRU 1600 /* as required क्रम FR network */
#पूर्ण_अगर


#पूर्ण_अगर /* _UAPI__HDLC_H */
