<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* SCTP kernel implementation
 * Copyright (c) 1999-2000 Cisco, Inc.
 * Copyright (c) 1999-2001 Motorola, Inc.
 *
 * This file is part of the SCTP kernel implementation
 *
 * These functions implement the SCTP primitive functions from Section 10.
 *
 * Note that the descriptions from the specअगरication are USER level
 * functions--this file is the functions which populate the काष्ठा proto
 * क्रम SCTP which is the BOTTOM of the sockets पूर्णांकerface.
 *
 * Please send any bug reports or fixes you make to the
 * email address(es):
 *    lksctp developers <linux-sctp@vger.kernel.org>
 *
 * Written or modअगरied by:
 *    La Monte H.P. Yarroll <piggy@acm.org>
 *    Narasimha Budihal     <narasimha@refcode.org>
 *    Karl Knutson          <karl@athena.chicago.il.us>
 *    Ardelle Fan	    <ardelle.fan@पूर्णांकel.com>
 *    Kevin Gao             <kevin.gao@पूर्णांकel.com>
 */

#समावेश <linux/types.h>
#समावेश <linux/list.h> /* For काष्ठा list_head */
#समावेश <linux/socket.h>
#समावेश <linux/ip.h>
#समावेश <linux/समय.स> /* For काष्ठा समयval */
#समावेश <linux/gfp.h>
#समावेश <net/sock.h>
#समावेश <net/sctp/sctp.h>
#समावेश <net/sctp/sm.h>

#घोषणा DECLARE_PRIMITIVE(name) \
/* This is called in the code as sctp_primitive_ ## name.  */ \
पूर्णांक sctp_primitive_ ## name(काष्ठा net *net, काष्ठा sctp_association *asoc, \
			    व्योम *arg) अणु \
	पूर्णांक error = 0; \
	क्रमागत sctp_event_type event_type; जोड़ sctp_subtype subtype; \
	क्रमागत sctp_state state; \
	काष्ठा sctp_endpoपूर्णांक *ep; \
	\
	event_type = SCTP_EVENT_T_PRIMITIVE; \
	subtype = SCTP_ST_PRIMITIVE(SCTP_PRIMITIVE_ ## name); \
	state = asoc ? asoc->state : SCTP_STATE_CLOSED; \
	ep = asoc ? asoc->ep : शून्य; \
	\
	error = sctp_करो_sm(net, event_type, subtype, state, ep, asoc,	\
			   arg, GFP_KERNEL); \
	वापस error; \
पूर्ण

/* 10.1 ULP-to-SCTP
 * B) Associate
 *
 * Format: ASSOCIATE(local SCTP instance name, destination transport addr,
 *         outbound stream count)
 * -> association id [,destination transport addr list] [,outbound stream
 *    count]
 *
 * This primitive allows the upper layer to initiate an association to a
 * specअगरic peer endpoपूर्णांक.
 *
 * This version assumes that asoc is fully populated with the initial
 * parameters.  We then वापस a traditional kernel indicator of
 * success or failure.
 */

/* This is called in the code as sctp_primitive_ASSOCIATE.  */

DECLARE_PRIMITIVE(ASSOCIATE)

/* 10.1 ULP-to-SCTP
 * C) Shutकरोwn
 *
 * Format: SHUTDOWN(association id)
 * -> result
 *
 * Gracefully बंदs an association. Any locally queued user data
 * will be delivered to the peer. The association will be terminated only
 * after the peer acknowledges all the SCTP packets sent.  A success code
 * will be वापसed on successful termination of the association. If
 * attempting to terminate the association results in a failure, an error
 * code shall be वापसed.
 */

DECLARE_PRIMITIVE(SHUTDOWN);

/* 10.1 ULP-to-SCTP
 * C) Abort
 *
 * Format: Abort(association id [, cause code])
 * -> result
 *
 * Ungracefully बंदs an association. Any locally queued user data
 * will be discarded and an ABORT chunk is sent to the peer. A success
 * code will be वापसed on successful पातion of the association. If
 * attempting to पात the association results in a failure, an error
 * code shall be वापसed.
 */

DECLARE_PRIMITIVE(ABORT);

/* 10.1 ULP-to-SCTP
 * E) Send
 *
 * Format: SEND(association id, buffer address, byte count [,context]
 *         [,stream id] [,lअगरe समय] [,destination transport address]
 *         [,unorder flag] [,no-bundle flag] [,payload protocol-id] )
 * -> result
 *
 * This is the मुख्य method to send user data via SCTP.
 *
 * Mandatory attributes:
 *
 *  o association id - local handle to the SCTP association
 *
 *  o buffer address - the location where the user message to be
 *    transmitted is stored;
 *
 *  o byte count - The size of the user data in number of bytes;
 *
 * Optional attributes:
 *
 *  o context - an optional 32 bit पूर्णांकeger that will be carried in the
 *    sending failure notअगरication to the ULP अगर the transportation of
 *    this User Message fails.
 *
 *  o stream id - to indicate which stream to send the data on. If not
 *    specअगरied, stream 0 will be used.
 *
 *  o lअगरe समय - specअगरies the lअगरe समय of the user data. The user data
 *    will not be sent by SCTP after the lअगरe समय expires. This
 *    parameter can be used to aव्योम efक्रमts to transmit stale
 *    user messages. SCTP notअगरies the ULP अगर the data cannot be
 *    initiated to transport (i.e. sent to the destination via SCTP's
 *    send primitive) within the lअगरe समय variable. However, the
 *    user data will be transmitted अगर SCTP has attempted to transmit a
 *    chunk beक्रमe the lअगरe समय expired.
 *
 *  o destination transport address - specअगरied as one of the destination
 *    transport addresses of the peer endpoपूर्णांक to which this packet
 *    should be sent. Whenever possible, SCTP should use this destination
 *    transport address क्रम sending the packets, instead of the current
 *    primary path.
 *
 *  o unorder flag - this flag, अगर present, indicates that the user
 *    would like the data delivered in an unordered fashion to the peer
 *    (i.e., the U flag is set to 1 on all DATA chunks carrying this
 *    message).
 *
 *  o no-bundle flag - inकाष्ठाs SCTP not to bundle this user data with
 *    other outbound DATA chunks. SCTP MAY still bundle even when
 *    this flag is present, when faced with network congestion.
 *
 *  o payload protocol-id - A 32 bit अचिन्हित पूर्णांकeger that is to be
 *    passed to the peer indicating the type of payload protocol data
 *    being transmitted. This value is passed as opaque data by SCTP.
 */

DECLARE_PRIMITIVE(SEND);

/* 10.1 ULP-to-SCTP
 * J) Request Heartbeat
 *
 * Format: REQUESTHEARTBEAT(association id, destination transport address)
 *
 * -> result
 *
 * Inकाष्ठाs the local endpoपूर्णांक to perक्रमm a HeartBeat on the specअगरied
 * destination transport address of the given association. The वापसed
 * result should indicate whether the transmission of the HEARTBEAT
 * chunk to the destination address is successful.
 *
 * Mandatory attributes:
 *
 * o association id - local handle to the SCTP association
 *
 * o destination transport address - the transport address of the
 *   association on which a heartbeat should be issued.
 */

DECLARE_PRIMITIVE(REQUESTHEARTBEAT);

/* ADDIP
* 3.1.1 Address Configuration Change Chunk (ASCONF)
*
* This chunk is used to communicate to the remote endpoपूर्णांक one of the
* configuration change requests that MUST be acknowledged.  The
* inक्रमmation carried in the ASCONF Chunk uses the क्रमm of a
* Type-Length-Value (TLV), as described in "3.2.1 Optional/
* Variable-length Parameter Format" in RFC2960 [5], क्रमall variable
* parameters.
*/

DECLARE_PRIMITIVE(ASCONF);

/* RE-CONFIG 5.1 */
DECLARE_PRIMITIVE(RECONF);
