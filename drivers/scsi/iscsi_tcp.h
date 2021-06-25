<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * iSCSI Initiator TCP Transport
 * Copyright (C) 2004 Dmitry Yusupov
 * Copyright (C) 2004 Alex Aizman
 * Copyright (C) 2005 - 2006 Mike Christie
 * Copyright (C) 2006 Red Hat, Inc.  All rights reserved.
 * मुख्यtained by खोलो-iscsi@googlegroups.com
 *
 * See the file COPYING included with this distribution क्रम more details.
 */

#अगर_अघोषित ISCSI_SW_TCP_H
#घोषणा ISCSI_SW_TCP_H

#समावेश <scsi/libiscsi.h>
#समावेश <scsi/libiscsi_tcp.h>

काष्ठा socket;
काष्ठा iscsi_tcp_conn;

/* Socket connection send helper */
काष्ठा iscsi_sw_tcp_send अणु
	काष्ठा iscsi_hdr	*hdr;
	काष्ठा iscsi_segment	segment;
	काष्ठा iscsi_segment	data_segment;
पूर्ण;

काष्ठा iscsi_sw_tcp_conn अणु
	काष्ठा socket		*sock;

	काष्ठा iscsi_sw_tcp_send out;
	/* old values क्रम socket callbacks */
	व्योम			(*old_data_पढ़ोy)(काष्ठा sock *);
	व्योम			(*old_state_change)(काष्ठा sock *);
	व्योम			(*old_ग_लिखो_space)(काष्ठा sock *);

	/* data and header digests */
	काष्ठा ahash_request	*tx_hash;	/* CRC32C (Tx) */
	काष्ठा ahash_request	*rx_hash;	/* CRC32C (Rx) */

	/* MIB custom statistics */
	uपूर्णांक32_t		sendpage_failures_cnt;
	uपूर्णांक32_t		discontiguous_hdr_cnt;

	sमाप_प्रकार (*sendpage)(काष्ठा socket *, काष्ठा page *, पूर्णांक, माप_प्रकार, पूर्णांक);
पूर्ण;

काष्ठा iscsi_sw_tcp_host अणु
	काष्ठा iscsi_session	*session;
पूर्ण;

काष्ठा iscsi_sw_tcp_hdrbuf अणु
	काष्ठा iscsi_hdr	hdrbuf;
	अक्षर			hdrextbuf[ISCSI_MAX_AHS_SIZE +
		                                  ISCSI_DIGEST_SIZE];
पूर्ण;

#पूर्ण_अगर /* ISCSI_SW_TCP_H */
