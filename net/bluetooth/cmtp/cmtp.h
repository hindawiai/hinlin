<शैली गुरु>
/*
   CMTP implementation क्रम Linux Bluetooth stack (BlueZ).
   Copyright (C) 2002-2003 Marcel Holपंचांगann <marcel@holपंचांगann.org>

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

#अगर_अघोषित __CMTP_H
#घोषणा __CMTP_H

#समावेश <linux/types.h>
#समावेश <net/bluetooth/bluetooth.h>

#घोषणा BTNAMSIZ 18

/* CMTP ioctl defines */
#घोषणा CMTPCONNADD	_IOW('C', 200, पूर्णांक)
#घोषणा CMTPCONNDEL	_IOW('C', 201, पूर्णांक)
#घोषणा CMTPGETCONNLIST	_IOR('C', 210, पूर्णांक)
#घोषणा CMTPGETCONNINFO	_IOR('C', 211, पूर्णांक)

#घोषणा CMTP_LOOPBACK	0

काष्ठा cmtp_connadd_req अणु
	पूर्णांक   sock;	/* Connected socket */
	__u32 flags;
पूर्ण;

काष्ठा cmtp_conndel_req अणु
	bdaddr_t bdaddr;
	__u32    flags;
पूर्ण;

काष्ठा cmtp_conninfo अणु
	bdaddr_t bdaddr;
	__u32    flags;
	__u16    state;
	पूर्णांक      num;
पूर्ण;

काष्ठा cmtp_connlist_req अणु
	__u32  cnum;
	काष्ठा cmtp_conninfo __user *ci;
पूर्ण;

पूर्णांक cmtp_add_connection(काष्ठा cmtp_connadd_req *req, काष्ठा socket *sock);
पूर्णांक cmtp_del_connection(काष्ठा cmtp_conndel_req *req);
पूर्णांक cmtp_get_connlist(काष्ठा cmtp_connlist_req *req);
पूर्णांक cmtp_get_conninfo(काष्ठा cmtp_conninfo *ci);

/* CMTP session defines */
#घोषणा CMTP_INTEROP_TIMEOUT	(HZ * 5)
#घोषणा CMTP_INITIAL_MSGNUM	0xff00

काष्ठा cmtp_session अणु
	काष्ठा list_head list;

	काष्ठा socket *sock;

	bdaddr_t bdaddr;

	अचिन्हित दीर्घ state;
	अचिन्हित दीर्घ flags;

	uपूर्णांक mtu;

	अक्षर name[BTNAMSIZ];

	atomic_t terminate;
	काष्ठा task_काष्ठा *task;

	रुको_queue_head_t रुको;

	पूर्णांक ncontroller;
	पूर्णांक num;
	काष्ठा capi_ctr ctrl;

	काष्ठा list_head applications;

	अचिन्हित दीर्घ blockids;
	पूर्णांक msgnum;

	काष्ठा sk_buff_head transmit;

	काष्ठा sk_buff *reassembly[16];
पूर्ण;

काष्ठा cmtp_application अणु
	काष्ठा list_head list;

	अचिन्हित दीर्घ state;
	पूर्णांक err;

	__u16 appl;
	__u16 mapping;

	__u16 msgnum;
पूर्ण;

काष्ठा cmtp_scb अणु
	पूर्णांक id;
	पूर्णांक data;
पूर्ण;

पूर्णांक  cmtp_attach_device(काष्ठा cmtp_session *session);
व्योम cmtp_detach_device(काष्ठा cmtp_session *session);

व्योम cmtp_recv_capimsg(काष्ठा cmtp_session *session, काष्ठा sk_buff *skb);

/* CMTP init defines */
पूर्णांक cmtp_init_sockets(व्योम);
व्योम cmtp_cleanup_sockets(व्योम);

#पूर्ण_अगर /* __CMTP_H */
