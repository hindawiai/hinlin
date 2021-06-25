<शैली गुरु>
/*
 *   fs/cअगरs/rfc1002pdu.h
 *
 *   Protocol Data Unit definitions क्रम RFC 1001/1002 support
 *
 *   Copyright (c) International Business Machines  Corp., 2004
 *   Author(s): Steve French (sfrench@us.ibm.com)
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Lesser General Public License as published
 *   by the Free Software Foundation; either version 2.1 of the License, or
 *   (at your option) any later version.
 *
 *   This library is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See
 *   the GNU Lesser General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU Lesser General Public License
 *   aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

/* NB: unlike smb/cअगरs packets, the RFC1002 काष्ठाures are big endian */

	/* RFC 1002 session packet types */
#घोषणा RFC1002_SESSION_MESSAGE 0x00
#घोषणा RFC1002_SESSION_REQUEST  0x81
#घोषणा RFC1002_POSITIVE_SESSION_RESPONSE 0x82
#घोषणा RFC1002_NEGATIVE_SESSION_RESPONSE 0x83
#घोषणा RFC1002_RETARGET_SESSION_RESPONSE 0x84
#घोषणा RFC1002_SESSION_KEEP_ALIVE 0x85

	/* RFC 1002 flags (only one defined */
#घोषणा RFC1002_LENGTH_EXTEND 0x80 /* high order bit of length (ie +64K) */

काष्ठा rfc1002_session_packet अणु
	__u8	type;
	__u8	flags;
	__u16	length;
	जोड़ अणु
		काष्ठा अणु
			__u8 called_len;
			__u8 called_name[32];
			__u8 scope1; /* null */
			__u8 calling_len;
			__u8 calling_name[32];
			__u8 scope2; /* null */
		पूर्ण __attribute__((packed)) session_req;
		काष्ठा अणु
			__u32 retarget_ip_addr;
			__u16 port;
		पूर्ण __attribute__((packed)) retarget_resp;
		__u8 neg_ses_resp_error_code;
		/* POSITIVE_SESSION_RESPONSE packet करोes not include trailer.
		SESSION_KEEP_ALIVE packet also करोes not include a trailer.
		Trailer क्रम the SESSION_MESSAGE packet is SMB/CIFS header */
	पूर्ण __attribute__((packed)) trailer;
पूर्ण __attribute__((packed));

/* Negative Session Response error codes */
#घोषणा RFC1002_NOT_LISTENING_CALLED  0x80 /* not listening on called name */
#घोषणा RFC1002_NOT_LISTENING_CALLING 0x81 /* not listening on calling name */
#घोषणा RFC1002_NOT_PRESENT           0x82 /* called name not present */
#घोषणा RFC1002_INSUFFICIENT_RESOURCE 0x83
#घोषणा RFC1002_UNSPECIFIED_ERROR     0x8F

/* RFC 1002 Datagram service packets are not defined here as they
are not needed क्रम the network fileप्रणाली client unless we plan on
implementing broadcast resolution of the server ip address (from
server netbios name). Currently server names are resolved only via DNS
(tcp name) or ip address or an /etc/hosts equivalent mapping to ip address.*/

#घोषणा DEFAULT_CIFS_CALLED_NAME  "*SMBSERVER      "
