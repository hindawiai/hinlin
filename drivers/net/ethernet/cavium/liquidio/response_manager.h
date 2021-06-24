<शैली गुरु>
/**********************************************************************
 * Author: Cavium, Inc.
 *
 * Contact: support@cavium.com
 *          Please include "LiquidIO" in the subject.
 *
 * Copyright (c) 2003-2016 Cavium, Inc.
 *
 * This file is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License, Version 2, as
 * published by the Free Software Foundation.
 *
 * This file is distributed in the hope that it will be useful, but
 * AS-IS and WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE, TITLE, or
 * NONINFRINGEMENT.  See the GNU General Public License क्रम more
 * details.
 **********************************************************************/

/*! \पile response_manager.h
 *  \मrief Host Driver:  Response queues क्रम host inकाष्ठाions.
 */

#अगर_अघोषित __RESPONSE_MANAGER_H__
#घोषणा __RESPONSE_MANAGER_H__

/** Maximum ordered requests to process in every invocation of
 * lio_process_ordered_list(). The function will जारी to process requests
 * as दीर्घ as it can find one that has finished processing. If it keeps
 * finding requests that have completed, the function can run क्रम ever. The
 * value defined here sets an upper limit on the number of requests it can
 * process beक्रमe it वापसs control to the poll thपढ़ो.
 */
#घोषणा  MAX_ORD_REQS_TO_PROCESS   4096

/** Head of a response list. There are several response lists in the
 *  प्रणाली. One क्रम each response order- Unordered, ordered
 *  and 1 क्रम noresponse entries on each inकाष्ठाion queue.
 */
काष्ठा octeon_response_list अणु
	/** List काष्ठाure to add delete pending entries to */
	काष्ठा list_head head;

	/** A lock क्रम this response list */
	spinlock_t lock;

	atomic_t pending_req_count;
पूर्ण;

/** The type of response list.
 */
क्रमागत अणु
	OCTEON_ORDERED_LIST = 0,
	OCTEON_UNORDERED_NONBLOCKING_LIST = 1,
	OCTEON_UNORDERED_BLOCKING_LIST = 2,
	OCTEON_ORDERED_SC_LIST = 3,
	OCTEON_DONE_SC_LIST = 4,
	OCTEON_ZOMBIE_SC_LIST = 5
पूर्ण;

/** Response Order values क्रम a Octeon Request. */
क्रमागत अणु
	OCTEON_RESP_ORDERED = 0,
	OCTEON_RESP_UNORDERED = 1,
	OCTEON_RESP_NORESPONSE = 2
पूर्ण;

/** Error codes  used in Octeon Host-Core communication.
 *
 *   31            16 15            0
 *   ---------------------------------
 *   |               |               |
 *   ---------------------------------
 *   Error codes are 32-bit wide. The upper 16-bits, called Major Error Number,
 *   are reserved to identअगरy the group to which the error code beदीर्घs. The
 *   lower 16-bits, called Minor Error Number, carry the actual code.
 *
 *   So error codes are (MAJOR NUMBER << 16)| MINOR_NUMBER.
 */

/*------------   Error codes used by host driver   -----------------*/
#घोषणा DRIVER_MAJOR_ERROR_CODE           0x0000
/*------   Error codes used by firmware (bits 15..0 set by firmware */
#घोषणा FIRMWARE_MAJOR_ERROR_CODE         0x0001

/**  A value of 0x00000000 indicates no error i.e. success */
#घोषणा DRIVER_ERROR_NONE                 0x00000000

#घोषणा DRIVER_ERROR_REQ_PENDING          0x00000001
#घोषणा DRIVER_ERROR_REQ_TIMEOUT          0x00000003
#घोषणा DRIVER_ERROR_REQ_EINTR            0x00000004
#घोषणा DRIVER_ERROR_REQ_ENXIO            0x00000006
#घोषणा DRIVER_ERROR_REQ_ENOMEM           0x0000000C
#घोषणा DRIVER_ERROR_REQ_EINVAL           0x00000016
#घोषणा DRIVER_ERROR_REQ_FAILED           0x000000ff

/** Status क्रम a request.
 * If a request is not queued to Octeon by the driver, the driver वापसs
 * an error condition that's describe by one of the OCTEON_REQ_ERR_* value
 * below. If the request is successfully queued, the driver will वापस
 * a OCTEON_REQUEST_PENDING status. OCTEON_REQUEST_TIMEOUT and
 * OCTEON_REQUEST_INTERRUPTED are only वापसed by the driver अगर the
 * response क्रम request failed to arrive beक्रमe a समय-out period or अगर
 * the request processing * got पूर्णांकerrupted due to a संकेत respectively.
 */
क्रमागत अणु
	OCTEON_REQUEST_DONE = (DRIVER_ERROR_NONE),
	OCTEON_REQUEST_PENDING = (DRIVER_ERROR_REQ_PENDING),
	OCTEON_REQUEST_TIMEOUT = (DRIVER_ERROR_REQ_TIMEOUT),
	OCTEON_REQUEST_INTERRUPTED = (DRIVER_ERROR_REQ_EINTR),
	OCTEON_REQUEST_NO_DEVICE = (0x00000021),
	OCTEON_REQUEST_NOT_RUNNING,
	OCTEON_REQUEST_INVALID_IQ,
	OCTEON_REQUEST_INVALID_BUFCNT,
	OCTEON_REQUEST_INVALID_RESP_ORDER,
	OCTEON_REQUEST_NO_MEMORY,
	OCTEON_REQUEST_INVALID_बफ_मानE,
	OCTEON_REQUEST_NO_PENDING_ENTRY,
	OCTEON_REQUEST_NO_IQ_SPACE = (0x7FFFFFFF)

पूर्ण;

#घोषणा FIRMWARE_STATUS_CODE(status) \
	((FIRMWARE_MAJOR_ERROR_CODE << 16) | (status))

/** Initialize the response lists. The number of response lists to create is
 * given by count.
 * @param octeon_dev      - the octeon device काष्ठाure.
 */
पूर्णांक octeon_setup_response_list(काष्ठा octeon_device *octeon_dev);

व्योम octeon_delete_response_list(काष्ठा octeon_device *octeon_dev);

/** Check the status of first entry in the ordered list. If the inकाष्ठाion at
 * that entry finished processing or has समयd-out, the entry is cleaned.
 * @param octeon_dev  - the octeon device काष्ठाure.
 * @param क्रमce_quit - the request is क्रमced to समयout अगर this is 1
 * @वापस 1 अगर the ordered list is empty, 0 otherwise.
 */
पूर्णांक lio_process_ordered_list(काष्ठा octeon_device *octeon_dev,
			     u32 क्रमce_quit);

#पूर्ण_अगर
