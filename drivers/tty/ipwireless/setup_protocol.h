<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * IPWireless 3G PCMCIA Network Driver
 *
 * Original code
 *   by Stephen Blackheath <stephen@blacksapphire.com>,
 *      Ben Martel <benm@symmetric.co.nz>
 *
 * Copyrighted as follows:
 *   Copyright (C) 2004 by Symmetric Systems Ltd (NZ)
 *
 * Various driver changes and reग_लिखोs, port to new kernels
 *   Copyright (C) 2006-2007 Jiri Kosina
 *
 * Misc code cleanups and updates
 *   Copyright (C) 2007 David Sterba
 */

#अगर_अघोषित _IPWIRELESS_CS_SETUP_PROTOCOL_H_
#घोषणा _IPWIRELESS_CS_SETUP_PROTOCOL_H_

/* Version of the setup protocol and transport protocols */
#घोषणा TL_SETUP_VERSION		1

#घोषणा TL_SETUP_VERSION_QRY_TMO	1000
#घोषणा TL_SETUP_MAX_VERSION_QRY	30

/* Message numbers 0-9 are obsoleted and must not be reused! */
#घोषणा TL_SETUP_SIGNO_GET_VERSION_QRY	10
#घोषणा TL_SETUP_SIGNO_GET_VERSION_RSP	11
#घोषणा TL_SETUP_SIGNO_CONFIG_MSG	12
#घोषणा TL_SETUP_SIGNO_CONFIG_DONE_MSG	13
#घोषणा TL_SETUP_SIGNO_OPEN_MSG		14
#घोषणा TL_SETUP_SIGNO_CLOSE_MSG	15

#घोषणा TL_SETUP_SIGNO_INFO_MSG     20
#घोषणा TL_SETUP_SIGNO_INFO_MSG_ACK 21

#घोषणा TL_SETUP_SIGNO_REBOOT_MSG      22
#घोषणा TL_SETUP_SIGNO_REBOOT_MSG_ACK  23

/* Synchronous start-messages */
काष्ठा tl_setup_get_version_qry अणु
	अचिन्हित अक्षर sig_no;		/* TL_SETUP_SIGNO_GET_VERSION_QRY */
पूर्ण __attribute__ ((__packed__));

काष्ठा tl_setup_get_version_rsp अणु
	अचिन्हित अक्षर sig_no;		/* TL_SETUP_SIGNO_GET_VERSION_RSP */
	अचिन्हित अक्षर version;		/* TL_SETUP_VERSION */
पूर्ण __attribute__ ((__packed__));

काष्ठा tl_setup_config_msg अणु
	अचिन्हित अक्षर sig_no;		/* TL_SETUP_SIGNO_CONFIG_MSG */
	अचिन्हित अक्षर port_no;
	अचिन्हित अक्षर prio_data;
	अचिन्हित अक्षर prio_ctrl;
पूर्ण __attribute__ ((__packed__));

काष्ठा tl_setup_config_करोne_msg अणु
	अचिन्हित अक्षर sig_no;		/* TL_SETUP_SIGNO_CONFIG_DONE_MSG */
पूर्ण __attribute__ ((__packed__));

/* Asynchronous messages */
काष्ठा tl_setup_खोलो_msg अणु
	अचिन्हित अक्षर sig_no;		/* TL_SETUP_SIGNO_OPEN_MSG */
	अचिन्हित अक्षर port_no;
पूर्ण __attribute__ ((__packed__));

काष्ठा tl_setup_बंद_msg अणु
	अचिन्हित अक्षर sig_no;		/* TL_SETUP_SIGNO_CLOSE_MSG */
	अचिन्हित अक्षर port_no;
पूर्ण __attribute__ ((__packed__));

/* Driver type  - क्रम use in tl_setup_info_msg.driver_type */
#घोषणा COMM_DRIVER     0
#घोषणा NDISWAN_DRIVER  1
#घोषणा NDISWAN_DRIVER_MAJOR_VERSION  2
#घोषणा NDISWAN_DRIVER_MINOR_VERSION  0

/*
 * It should not matter when this message comes over as we just store the
 * results and send the ACK.
 */
काष्ठा tl_setup_info_msg अणु
	अचिन्हित अक्षर sig_no;		/* TL_SETUP_SIGNO_INFO_MSG */
	अचिन्हित अक्षर driver_type;
	अचिन्हित अक्षर major_version;
	अचिन्हित अक्षर minor_version;
पूर्ण __attribute__ ((__packed__));

काष्ठा tl_setup_info_msgAck अणु
	अचिन्हित अक्षर sig_no;		/* TL_SETUP_SIGNO_INFO_MSG_ACK */
पूर्ण __attribute__ ((__packed__));

काष्ठा TlSetupRebootMsgAck अणु
	अचिन्हित अक्षर sig_no;		/* TL_SETUP_SIGNO_REBOOT_MSG_ACK */
पूर्ण __attribute__ ((__packed__));

/* Define a जोड़ of all the msgs that the driver can receive from the card.*/
जोड़ ipw_setup_rx_msg अणु
	अचिन्हित अक्षर sig_no;
	काष्ठा tl_setup_get_version_rsp version_rsp_msg;
	काष्ठा tl_setup_खोलो_msg खोलो_msg;
	काष्ठा tl_setup_बंद_msg बंद_msg;
	काष्ठा tl_setup_info_msg InfoMsg;
	काष्ठा tl_setup_info_msgAck info_msg_ack;
पूर्ण __attribute__ ((__packed__));

#पूर्ण_अगर				/* _IPWIRELESS_CS_SETUP_PROTOCOL_H_ */
