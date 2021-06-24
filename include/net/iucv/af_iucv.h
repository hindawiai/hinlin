<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright 2006 IBM Corporation
 * IUCV protocol stack क्रम Linux on zSeries
 * Version 1.0
 * Author(s): Jennअगरer Hunt <jenhunt@us.ibm.com>
 *
 */

#अगर_अघोषित __AFIUCV_H
#घोषणा __AFIUCV_H

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <linux/list.h>
#समावेश <linux/poll.h>
#समावेश <linux/socket.h>
#समावेश <net/iucv/iucv.h>

#अगर_अघोषित AF_IUCV
#घोषणा AF_IUCV		32
#घोषणा PF_IUCV		AF_IUCV
#पूर्ण_अगर

/* Connection and socket states */
क्रमागत अणु
	IUCV_CONNECTED = 1,
	IUCV_OPEN,
	IUCV_BOUND,
	IUCV_LISTEN,
	IUCV_DISCONN,
	IUCV_CLOSING,
	IUCV_CLOSED
पूर्ण;

#घोषणा IUCV_QUEUELEN_DEFAULT	65535
#घोषणा IUCV_HIPER_MSGLIM_DEFAULT	128
#घोषणा IUCV_CONN_TIMEOUT	(HZ * 40)
#घोषणा IUCV_DISCONN_TIMEOUT	(HZ * 2)
#घोषणा IUCV_CONN_IDLE_TIMEOUT	(HZ * 60)
#घोषणा IUCV_बफ_मानE_DEFAULT	32768

/* IUCV socket address */
काष्ठा sockaddr_iucv अणु
	sa_family_t	siucv_family;
	अचिन्हित लघु	siucv_port;		/* Reserved */
	अचिन्हित पूर्णांक	siucv_addr;		/* Reserved */
	अक्षर		siucv_nodeid[8];	/* Reserved */
	अक्षर		siucv_user_id[8];	/* Guest User Id */
	अक्षर		siucv_name[8];		/* Application Name */
पूर्ण;


/* Common socket काष्ठाures and functions */
काष्ठा sock_msg_q अणु
	काष्ठा iucv_path	*path;
	काष्ठा iucv_message	msg;
	काष्ठा list_head	list;
	spinlock_t		lock;
पूर्ण;

#घोषणा AF_IUCV_FLAG_ACK 0x1
#घोषणा AF_IUCV_FLAG_SYN 0x2
#घोषणा AF_IUCV_FLAG_FIN 0x4
#घोषणा AF_IUCV_FLAG_WIN 0x8
#घोषणा AF_IUCV_FLAG_SHT 0x10

काष्ठा af_iucv_trans_hdr अणु
	u16 magic;
	u8 version;
	u8 flags;
	u16 winकरोw;
	अक्षर destNodeID[8];
	अक्षर destUserID[8];
	अक्षर destAppName[16];
	अक्षर srcNodeID[8];
	अक्षर srcUserID[8];
	अक्षर srcAppName[16];             /* => 70 bytes */
	काष्ठा iucv_message iucv_hdr;    /* => 33 bytes */
	u8 pad;                          /* total 104 bytes */
पूर्ण __packed;

अटल अंतरभूत काष्ठा af_iucv_trans_hdr *iucv_trans_hdr(काष्ठा sk_buff *skb)
अणु
	वापस (काष्ठा af_iucv_trans_hdr *)skb_network_header(skb);
पूर्ण

क्रमागत iucv_tx_notअगरy अणु
	/* transmission of skb is completed and was successful */
	TX_NOTIFY_OK = 0,
	/* target is unreachable */
	TX_NOTIFY_UNREACHABLE = 1,
	/* transfer pending queue full */
	TX_NOTIFY_TPQFULL = 2,
	/* general error */
	TX_NOTIFY_GENERALERROR = 3,
	/* transmission of skb is pending - may पूर्णांकerleave
	 * with TX_NOTIFY_DELAYED_* */
	TX_NOTIFY_PENDING = 4,
	/* transmission of skb was करोne successfully (delayed) */
	TX_NOTIFY_DELAYED_OK = 5,
	/* target unreachable (detected delayed) */
	TX_NOTIFY_DELAYED_UNREACHABLE = 6,
	/* general error (detected delayed) */
	TX_NOTIFY_DELAYED_GENERALERROR = 7,
पूर्ण;

#घोषणा iucv_sk(__sk) ((काष्ठा iucv_sock *) __sk)

#घोषणा AF_IUCV_TRANS_IUCV 0
#घोषणा AF_IUCV_TRANS_HIPER 1

काष्ठा iucv_sock अणु
	काष्ठा sock		sk;
	अक्षर			src_user_id[8];
	अक्षर			src_name[8];
	अक्षर			dst_user_id[8];
	अक्षर			dst_name[8];
	काष्ठा list_head	accept_q;
	spinlock_t		accept_q_lock;
	काष्ठा sock		*parent;
	काष्ठा iucv_path	*path;
	काष्ठा net_device	*hs_dev;
	काष्ठा sk_buff_head	send_skb_q;
	काष्ठा sk_buff_head	backlog_skb_q;
	काष्ठा sock_msg_q	message_q;
	अचिन्हित पूर्णांक		send_tag;
	u8			flags;
	u16			msglimit;
	u16			msglimit_peer;
	atomic_t		skbs_in_xmit;
	atomic_t		msg_sent;
	atomic_t		msg_recv;
	atomic_t		pendings;
	पूर्णांक			transport;
	व्योम			(*sk_txnotअगरy)(काष्ठा sock *sk,
					       क्रमागत iucv_tx_notअगरy n);
पूर्ण;

काष्ठा iucv_skb_cb अणु
	u32	class;		/* target class of message */
	u32	tag;		/* tag associated with message */
	u32	offset;		/* offset क्रम skb receival */
पूर्ण;

#घोषणा IUCV_SKB_CB(__skb)	((काष्ठा iucv_skb_cb *)&((__skb)->cb[0]))

/* iucv socket options (SOL_IUCV) */
#घोषणा SO_IPRMDATA_MSG	0x0080		/* send/recv IPRM_DATA msgs */
#घोषणा SO_MSGLIMIT	0x1000		/* get/set IUCV MSGLIMIT */
#घोषणा SO_MSGSIZE	0x0800		/* get maximum msgsize */

/* iucv related control messages (scm) */
#घोषणा SCM_IUCV_TRGCLS	0x0001		/* target class control message */

काष्ठा iucv_sock_list अणु
	काष्ठा hlist_head head;
	rwlock_t	  lock;
	atomic_t	  स्वतःbind_name;
पूर्ण;

#पूर्ण_अगर /* __IUCV_H */
