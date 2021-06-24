<शैली गुरु>
/* SPDX-License-Identअगरier: LGPL-2.1+ WITH Linux-syscall-note */
/*
 * net.h
 *
 * Copyright (C) 2000 Marcus Metzler <marcus@convergence.de>
 *                  & Ralph  Metzler <ralph@convergence.de>
 *                    क्रम convergence पूर्णांकegrated media GmbH
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 *
 */

#अगर_अघोषित _DVBNET_H_
#घोषणा _DVBNET_H_

#समावेश <linux/types.h>

/**
 * काष्ठा dvb_net_अगर - describes a DVB network पूर्णांकerface
 *
 * @pid: Packet ID (PID) of the MPEG-TS that contains data
 * @अगर_num: number of the Digital TV पूर्णांकerface.
 * @feedtype: Encapsulation type of the feed.
 *
 * A MPEG-TS stream may contain packet IDs with IP packages on it.
 * This काष्ठा describes it, and the type of encoding.
 *
 * @feedtype can be:
 *
 *	- %DVB_NET_FEEDTYPE_MPE क्रम MPE encoding
 *	- %DVB_NET_FEEDTYPE_ULE क्रम ULE encoding.
 */
काष्ठा dvb_net_अगर अणु
	__u16 pid;
	__u16 अगर_num;
	__u8  feedtype;
#घोषणा DVB_NET_FEEDTYPE_MPE 0	/* multi protocol encapsulation */
#घोषणा DVB_NET_FEEDTYPE_ULE 1	/* ultra lightweight encapsulation */
पूर्ण;


#घोषणा NET_ADD_IF    _IOWR('o', 52, काष्ठा dvb_net_अगर)
#घोषणा NET_REMOVE_IF _IO('o', 53)
#घोषणा NET_GET_IF    _IOWR('o', 54, काष्ठा dvb_net_अगर)


/* binary compatibility cruft: */
काष्ठा __dvb_net_अगर_old अणु
	__u16 pid;
	__u16 अगर_num;
पूर्ण;
#घोषणा __NET_ADD_IF_OLD _IOWR('o', 52, काष्ठा __dvb_net_अगर_old)
#घोषणा __NET_GET_IF_OLD _IOWR('o', 54, काष्ठा __dvb_net_अगर_old)


#पूर्ण_अगर /*_DVBNET_H_*/
