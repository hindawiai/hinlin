<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2005-2007 Takahiro Hirofuchi
 */

#अगर_अघोषित __USBIP_NETWORK_H
#घोषणा __USBIP_NETWORK_H

#अगर_घोषित HAVE_CONFIG_H
#समावेश "../config.h"
#पूर्ण_अगर

#समावेश <sys/types.h>

#समावेश <मानक_निवेशt.h>

बाह्य पूर्णांक usbip_port;
बाह्य अक्षर *usbip_port_string;
व्योम usbip_setup_port_number(अक्षर *arg);

/* ---------------------------------------------------------------------- */
/* Common header क्रम all the kinds of PDUs. */
काष्ठा op_common अणु
	uपूर्णांक16_t version;

#घोषणा OP_REQUEST	(0x80 << 8)
#घोषणा OP_REPLY	(0x00 << 8)
	uपूर्णांक16_t code;

	/* status codes defined in usbip_common.h */
	uपूर्णांक32_t status; /* op_code status (क्रम reply) */

पूर्ण __attribute__((packed));

/* ---------------------------------------------------------------------- */
/* Dummy Code */
#घोषणा OP_UNSPEC	0x00
#घोषणा OP_REQ_UNSPEC	OP_UNSPEC
#घोषणा OP_REP_UNSPEC	OP_UNSPEC

/* ---------------------------------------------------------------------- */
/* Retrieve USB device inक्रमmation. (still not used) */
#घोषणा OP_DEVINFO	0x02
#घोषणा OP_REQ_DEVINFO	(OP_REQUEST | OP_DEVINFO)
#घोषणा OP_REP_DEVINFO	(OP_REPLY   | OP_DEVINFO)

काष्ठा op_devinfo_request अणु
	अक्षर busid[SYSFS_BUS_ID_SIZE];
पूर्ण __attribute__((packed));

काष्ठा op_devinfo_reply अणु
	काष्ठा usbip_usb_device udev;
	काष्ठा usbip_usb_पूर्णांकerface uinf[];
पूर्ण __attribute__((packed));

/* ---------------------------------------------------------------------- */
/* Import a remote USB device. */
#घोषणा OP_IMPORT	0x03
#घोषणा OP_REQ_IMPORT	(OP_REQUEST | OP_IMPORT)
#घोषणा OP_REP_IMPORT   (OP_REPLY   | OP_IMPORT)

काष्ठा op_import_request अणु
	अक्षर busid[SYSFS_BUS_ID_SIZE];
पूर्ण __attribute__((packed));

काष्ठा op_import_reply अणु
	काष्ठा usbip_usb_device udev;
//	काष्ठा usbip_usb_पूर्णांकerface uinf[];
पूर्ण __attribute__((packed));

#घोषणा PACK_OP_IMPORT_REQUEST(pack, request)  करो अणु\
पूर्ण जबतक (0)

#घोषणा PACK_OP_IMPORT_REPLY(pack, reply)  करो अणु\
	usbip_net_pack_usb_device(pack, &(reply)->udev);\
पूर्ण जबतक (0)

/* ---------------------------------------------------------------------- */
/* Export a USB device to a remote host. */
#घोषणा OP_EXPORT	0x06
#घोषणा OP_REQ_EXPORT	(OP_REQUEST | OP_EXPORT)
#घोषणा OP_REP_EXPORT	(OP_REPLY   | OP_EXPORT)

काष्ठा op_export_request अणु
	काष्ठा usbip_usb_device udev;
पूर्ण __attribute__((packed));

काष्ठा op_export_reply अणु
	पूर्णांक वापसcode;
पूर्ण __attribute__((packed));


#घोषणा PACK_OP_EXPORT_REQUEST(pack, request)  करो अणु\
	usbip_net_pack_usb_device(pack, &(request)->udev);\
पूर्ण जबतक (0)

#घोषणा PACK_OP_EXPORT_REPLY(pack, reply)  करो अणु\
पूर्ण जबतक (0)

/* ---------------------------------------------------------------------- */
/* un-Export a USB device from a remote host. */
#घोषणा OP_UNEXPORT	0x07
#घोषणा OP_REQ_UNEXPORT	(OP_REQUEST | OP_UNEXPORT)
#घोषणा OP_REP_UNEXPORT	(OP_REPLY   | OP_UNEXPORT)

काष्ठा op_unexport_request अणु
	काष्ठा usbip_usb_device udev;
पूर्ण __attribute__((packed));

काष्ठा op_unexport_reply अणु
	पूर्णांक वापसcode;
पूर्ण __attribute__((packed));

#घोषणा PACK_OP_UNEXPORT_REQUEST(pack, request)  करो अणु\
	usbip_net_pack_usb_device(pack, &(request)->udev);\
पूर्ण जबतक (0)

#घोषणा PACK_OP_UNEXPORT_REPLY(pack, reply)  करो अणु\
पूर्ण जबतक (0)

/* ---------------------------------------------------------------------- */
/* Negotiate IPSec encryption key. (still not used) */
#घोषणा OP_CRYPKEY	0x04
#घोषणा OP_REQ_CRYPKEY	(OP_REQUEST | OP_CRYPKEY)
#घोषणा OP_REP_CRYPKEY	(OP_REPLY   | OP_CRYPKEY)

काष्ठा op_crypkey_request अणु
	/* 128bit key */
	uपूर्णांक32_t key[4];
पूर्ण __attribute__((packed));

काष्ठा op_crypkey_reply अणु
	uपूर्णांक32_t __reserved;
पूर्ण __attribute__((packed));


/* ---------------------------------------------------------------------- */
/* Retrieve the list of exported USB devices. */
#घोषणा OP_DEVLIST	0x05
#घोषणा OP_REQ_DEVLIST	(OP_REQUEST | OP_DEVLIST)
#घोषणा OP_REP_DEVLIST	(OP_REPLY   | OP_DEVLIST)

काष्ठा op_devlist_request अणु
पूर्ण __attribute__((packed));

काष्ठा op_devlist_reply अणु
	uपूर्णांक32_t ndev;
	/* followed by reply_extra[] */
पूर्ण __attribute__((packed));

काष्ठा op_devlist_reply_extra अणु
	काष्ठा usbip_usb_device    udev;
	काष्ठा usbip_usb_पूर्णांकerface uinf[];
पूर्ण __attribute__((packed));

#घोषणा PACK_OP_DEVLIST_REQUEST(pack, request)  करो अणु\
पूर्ण जबतक (0)

#घोषणा PACK_OP_DEVLIST_REPLY(pack, reply)  करो अणु\
	(reply)->ndev = usbip_net_pack_uपूर्णांक32_t(pack, (reply)->ndev);\
पूर्ण जबतक (0)

uपूर्णांक32_t usbip_net_pack_uपूर्णांक32_t(पूर्णांक pack, uपूर्णांक32_t num);
uपूर्णांक16_t usbip_net_pack_uपूर्णांक16_t(पूर्णांक pack, uपूर्णांक16_t num);
व्योम usbip_net_pack_usb_device(पूर्णांक pack, काष्ठा usbip_usb_device *udev);
व्योम usbip_net_pack_usb_पूर्णांकerface(पूर्णांक pack, काष्ठा usbip_usb_पूर्णांकerface *uinf);

sमाप_प्रकार usbip_net_recv(पूर्णांक sockfd, व्योम *buff, माप_प्रकार bufflen);
sमाप_प्रकार usbip_net_send(पूर्णांक sockfd, व्योम *buff, माप_प्रकार bufflen);
पूर्णांक usbip_net_send_op_common(पूर्णांक sockfd, uपूर्णांक32_t code, uपूर्णांक32_t status);
पूर्णांक usbip_net_recv_op_common(पूर्णांक sockfd, uपूर्णांक16_t *code, पूर्णांक *status);
पूर्णांक usbip_net_set_reuseaddr(पूर्णांक sockfd);
पूर्णांक usbip_net_set_nodelay(पूर्णांक sockfd);
पूर्णांक usbip_net_set_keepalive(पूर्णांक sockfd);
पूर्णांक usbip_net_set_v6only(पूर्णांक sockfd);
पूर्णांक usbip_net_tcp_connect(अक्षर *hostname, अक्षर *port);

#पूर्ण_अगर /* __USBIP_NETWORK_H */
