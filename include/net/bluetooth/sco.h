<शैली गुरु>
/*
   BlueZ - Bluetooth protocol stack क्रम Linux
   Copyright (C) 2000-2001 Qualcomm Incorporated

   Written 2000,2001 by Maxim Krasnyansky <maxk@qualcomm.com>

   This program is मुक्त software; you can redistribute it and/or modअगरy
   it under the terms of the GNU General Public License version 2 as
   published by the Free Software Foundation;

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
   OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
   IN NO EVENT SHALL THE COPYRIGHT HOLDER(S) AND AUTHOR(S) BE LIABLE FOR ANY
   CLAIM, OR ANY SPECIAL INसूचीECT OR CONSEQUENTIAL DAMAGES, OR ANY DAMAGES
   WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
   ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
   OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

   ALL LIABILITY, INCLUDING LIABILITY FOR INFRINGEMENT OF ANY PATENTS,
   COPYRIGHTS, TRADEMARKS OR OTHER RIGHTS, RELATING TO USE OF THIS
   SOFTWARE IS DISCLAIMED.
*/

#अगर_अघोषित __SCO_H
#घोषणा __SCO_H

/* SCO शेषs */
#घोषणा SCO_DEFAULT_MTU		500

/* SCO socket address */
काष्ठा sockaddr_sco अणु
	sa_family_t	sco_family;
	bdaddr_t	sco_bdaddr;
पूर्ण;

/* SCO socket options */
#घोषणा SCO_OPTIONS	0x01
काष्ठा sco_options अणु
	__u16 mtu;
पूर्ण;

#घोषणा SCO_CONNINFO	0x02
काष्ठा sco_conninfo अणु
	__u16 hci_handle;
	__u8  dev_class[3];
पूर्ण;

#घोषणा SCO_CMSG_PKT_STATUS	0x01

#पूर्ण_अगर /* __SCO_H */
