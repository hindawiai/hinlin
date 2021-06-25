<शैली गुरु>
/*
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * Copyright (C) 2019 Intel Corporation
 */
#अगर_अघोषित _UAPI_LINUX_UM_TIMETRAVEL_H
#घोषणा _UAPI_LINUX_UM_TIMETRAVEL_H
#समावेश <linux/types.h>

/**
 * काष्ठा um_समयtravel_msg - UM समय travel message
 *
 * This is the basic message type, going in both directions.
 *
 * This is the message passed between the host (user-mode Linux instance)
 * and the calendar (the application on the other side of the socket) in
 * order to implement common scheduling.
 *
 * Whenever UML has an event it will request runसमय क्रम it from the
 * calendar, and then रुको क्रम its turn until it can run, etc. Note
 * that it will only ever request the single next runसमय, i.e. multiple
 * REQUEST messages override each other.
 */
काष्ठा um_समयtravel_msg अणु
	/**
	 * @op: operation value from &क्रमागत um_समयtravel_ops
	 */
	__u32 op;

	/**
	 * @seq: sequence number क्रम the message - shall be reflected in
	 *	the ACK response, and should be checked जबतक processing
	 *	the response to see अगर it matches
	 */
	__u32 seq;

	/**
	 * @समय: समय in nanoseconds
	 */
	__u64 समय;
पूर्ण;

/**
 * क्रमागत um_समयtravel_ops - Operation codes
 */
क्रमागत um_समयtravel_ops अणु
	/**
	 * @UM_TIMETRAVEL_ACK: response (ACK) to any previous message,
	 *	this usually करोesn't carry any data in the 'time' field
	 *	unless otherwise specअगरied below
	 */
	UM_TIMETRAVEL_ACK		= 0,

	/**
	 * @UM_TIMETRAVEL_START: initialize the connection, the समय
	 *	field contains an (arbitrary) ID to possibly be able
	 *	to distinguish the connections.
	 */
	UM_TIMETRAVEL_START		= 1,

	/**
	 * @UM_TIMETRAVEL_REQUEST: request to run at the given समय
	 *	(host -> calendar)
	 */
	UM_TIMETRAVEL_REQUEST		= 2,

	/**
	 * @UM_TIMETRAVEL_WAIT: Indicate रुकोing क्रम the previously requested
	 *	runसमय, new requests may be made जबतक रुकोing (e.g. due to
	 *	पूर्णांकerrupts); the समय field is ignored. The calendar must process
	 *	this message and later	send a %UM_TIMETRAVEL_RUN message when
	 *	the host can run again.
	 *	(host -> calendar)
	 */
	UM_TIMETRAVEL_WAIT		= 3,

	/**
	 * @UM_TIMETRAVEL_GET: वापस the current समय from the calendar in the
	 *	ACK message, the समय in the request message is ignored
	 *	(host -> calendar)
	 */
	UM_TIMETRAVEL_GET		= 4,

	/**
	 * @UM_TIMETRAVEL_UPDATE: समय update to the calendar, must be sent e.g.
	 *	beक्रमe kicking an पूर्णांकerrupt to another calendar
	 *	(host -> calendar)
	 */
	UM_TIMETRAVEL_UPDATE		= 5,

	/**
	 * @UM_TIMETRAVEL_RUN: run समय request granted, current समय is in
	 *	the समय field
	 *	(calendar -> host)
	 */
	UM_TIMETRAVEL_RUN		= 6,

	/**
	 * @UM_TIMETRAVEL_FREE_UNTIL: Enable मुक्त-running until the given समय,
	 *	this is a message from the calendar telling the host that it can
	 *	मुक्तly करो its own scheduling क्रम anything beक्रमe the indicated
	 *	समय.
	 *	Note that अगर a calendar sends this message once, the host may
	 *	assume that it will also करो so in the future, अगर it implements
	 *	wraparound semantics क्रम the समय field.
	 *	(calendar -> host)
	 */
	UM_TIMETRAVEL_FREE_UNTIL	= 7,

	/**
	 * @UM_TIMETRAVEL_GET_TOD: Return समय of day, typically used once at
	 *	boot by the भव machines to get a synchronized समय from
	 *	the simulation.
	 */
	UM_TIMETRAVEL_GET_TOD		= 8,
पूर्ण;

#पूर्ण_अगर /* _UAPI_LINUX_UM_TIMETRAVEL_H */
