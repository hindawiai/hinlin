<शैली गुरु>
/******************************************************************************
 * displअगर.h
 *
 * Unअगरied display device I/O पूर्णांकerface क्रम Xen guest OSes.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Copyright (C) 2016-2017 EPAM Systems Inc.
 *
 * Authors: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 *          Oleksandr Grytsov <oleksandr_grytsov@epam.com>
 */

#अगर_अघोषित __XEN_PUBLIC_IO_DISPLIF_H__
#घोषणा __XEN_PUBLIC_IO_DISPLIF_H__

#समावेश "ring.h"
#समावेश "../grant_table.h"

/*
 ******************************************************************************
 *                           Protocol version
 ******************************************************************************
 */
#घोषणा XENDISPL_PROTOCOL_VERSION	"2"
#घोषणा XENDISPL_PROTOCOL_VERSION_INT	 2

/*
 ******************************************************************************
 *                  Main features provided by the protocol
 ******************************************************************************
 * This protocol aims to provide a unअगरied protocol which fits more
 * sophisticated use-हालs than a framebuffer device can handle. At the
 * moment basic functionality is supported with the पूर्णांकention to be extended:
 *  o multiple dynamically allocated/destroyed framebuffers
 *  o buffers of arbitrary sizes
 *  o buffer allocation at either back or front end
 *  o better configuration options including multiple display support
 *
 * Note: existing fbअगर can be used together with displअगर running at the
 * same समय, e.g. on Linux one provides framebuffer and another DRM/KMS
 *
 * Note: display resolution (XenStore's "resolution" property) defines
 * visible area of the भव display. At the same समय resolution of
 * the display and frame buffers may dअगरfer: buffers can be smaller, equal
 * or bigger than the visible area. This is to enable use-हालs, where backend
 * may करो some post-processing of the display and frame buffers supplied,
 * e.g. those buffers can be just a part of the final composition.
 *
 ******************************************************************************
 *                        Direction of improvements
 ******************************************************************************
 * Future extensions to the existing protocol may include:
 *  o display/connector cloning
 *  o allocation of objects other than display buffers
 *  o plane/overlay support
 *  o scaling support
 *  o rotation support
 *
 ******************************************************************************
 *                  Feature and Parameter Negotiation
 ******************************************************************************
 *
 * Front->back notअगरications: when enqueuing a new request, sending a
 * notअगरication can be made conditional on xendispl_req (i.e., the generic
 * hold-off mechanism provided by the ring macros). Backends must set
 * xendispl_req appropriately (e.g., using RING_FINAL_CHECK_FOR_REQUESTS()).
 *
 * Back->front notअगरications: when enqueuing a new response, sending a
 * notअगरication can be made conditional on xendispl_resp (i.e., the generic
 * hold-off mechanism provided by the ring macros). Frontends must set
 * xendispl_resp appropriately (e.g., using RING_FINAL_CHECK_FOR_RESPONSES()).
 *
 * The two halves of a para-भव display driver utilize nodes within
 * XenStore to communicate capabilities and to negotiate operating parameters.
 * This section क्रमागतerates these nodes which reside in the respective front and
 * backend portions of XenStore, following the XenBus convention.
 *
 * All data in XenStore is stored as strings. Nodes specअगरying numeric
 * values are encoded in decimal. Integer value ranges listed below are
 * expressed as fixed sized पूर्णांकeger types capable of storing the conversion
 * of a properly क्रमmated node string, without loss of inक्रमmation.
 *
 ******************************************************************************
 *                        Example configuration
 ******************************************************************************
 *
 * Note: depending on the use-हाल backend can expose more display connectors
 * than the underlying HW physically has by employing SW graphics compositors
 *
 * This is an example of backend and frontend configuration:
 *
 *--------------------------------- Backend -----------------------------------
 *
 * /local/करोमुख्य/0/backend/vdispl/1/0/frontend-id = "1"
 * /local/करोमुख्य/0/backend/vdispl/1/0/frontend = "/local/domain/1/device/vdispl/0"
 * /local/करोमुख्य/0/backend/vdispl/1/0/state = "4"
 * /local/करोमुख्य/0/backend/vdispl/1/0/versions = "1,2"
 *
 *--------------------------------- Frontend ----------------------------------
 *
 * /local/करोमुख्य/1/device/vdispl/0/backend-id = "0"
 * /local/करोमुख्य/1/device/vdispl/0/backend = "/local/domain/0/backend/vdispl/1/0"
 * /local/करोमुख्य/1/device/vdispl/0/state = "4"
 * /local/करोमुख्य/1/device/vdispl/0/version = "1"
 * /local/करोमुख्य/1/device/vdispl/0/be-alloc = "1"
 *
 *-------------------------- Connector 0 configuration ------------------------
 *
 * /local/करोमुख्य/1/device/vdispl/0/0/resolution = "1920x1080"
 * /local/करोमुख्य/1/device/vdispl/0/0/req-ring-ref = "2832"
 * /local/करोमुख्य/1/device/vdispl/0/0/req-event-channel = "15"
 * /local/करोमुख्य/1/device/vdispl/0/0/evt-ring-ref = "387"
 * /local/करोमुख्य/1/device/vdispl/0/0/evt-event-channel = "16"
 *
 *-------------------------- Connector 1 configuration ------------------------
 *
 * /local/करोमुख्य/1/device/vdispl/0/1/resolution = "800x600"
 * /local/करोमुख्य/1/device/vdispl/0/1/req-ring-ref = "2833"
 * /local/करोमुख्य/1/device/vdispl/0/1/req-event-channel = "17"
 * /local/करोमुख्य/1/device/vdispl/0/1/evt-ring-ref = "388"
 * /local/करोमुख्य/1/device/vdispl/0/1/evt-event-channel = "18"
 *
 ******************************************************************************
 *                            Backend XenBus Nodes
 ******************************************************************************
 *
 *----------------------------- Protocol version ------------------------------
 *
 * versions
 *      Values:         <string>
 *
 *      List of XENDISPL_LIST_SEPARATOR separated protocol versions supported
 *      by the backend. For example "1,2,3".
 *
 ******************************************************************************
 *                            Frontend XenBus Nodes
 ******************************************************************************
 *
 *-------------------------------- Addressing ---------------------------------
 *
 * करोm-id
 *      Values:         <uपूर्णांक16_t>
 *
 *      Doमुख्य identअगरier.
 *
 * dev-id
 *      Values:         <uपूर्णांक16_t>
 *
 *      Device identअगरier.
 *
 * conn-idx
 *      Values:         <uपूर्णांक8_t>
 *
 *      Zero based contigous index of the connector.
 *      /local/करोमुख्य/<करोm-id>/device/vdispl/<dev-id>/<conn-idx>/...
 *
 *----------------------------- Protocol version ------------------------------
 *
 * version
 *      Values:         <string>
 *
 *      Protocol version, chosen among the ones supported by the backend.
 *
 *------------------------- Backend buffer allocation -------------------------
 *
 * be-alloc
 *      Values:         "0", "1"
 *
 *      If value is set to "1", then backend can be a buffer provider/allocator
 *      क्रम this करोमुख्य during XENDISPL_OP_DBUF_CREATE operation (see below
 *      क्रम negotiation).
 *      If value is not "1" or omitted frontend must allocate buffers itself.
 *
 *----------------------------- Connector settings ----------------------------
 *
 * unique-id
 *      Values:         <string>
 *
 *      After device instance initialization each connector is asचिन्हित a
 *      unique ID, so it can be identअगरied by the backend by this ID.
 *      This can be UUID or such.
 *
 * resolution
 *      Values:         <width, uपूर्णांक32_t>x<height, uपूर्णांक32_t>
 *
 *      Width and height of the connector in pixels separated by
 *      XENDISPL_RESOLUTION_SEPARATOR. This defines visible area of the
 *      display.
 *      If backend provides extended display identअगरication data (EDID) with
 *      XENDISPL_OP_GET_EDID request then EDID values must take precedence
 *      over the resolutions defined here.
 *
 *------------------ Connector Request Transport Parameters -------------------
 *
 * This communication path is used to deliver requests from frontend to backend
 * and get the corresponding responses from backend to frontend,
 * set up per connector.
 *
 * req-event-channel
 *      Values:         <uपूर्णांक32_t>
 *
 *      The identअगरier of the Xen connector's control event channel
 *      used to संकेत activity in the ring buffer.
 *
 * req-ring-ref
 *      Values:         <uपूर्णांक32_t>
 *
 *      The Xen grant reference granting permission क्रम the backend to map
 *      a sole page of connector's control ring buffer.
 *
 *------------------- Connector Event Transport Parameters --------------------
 *
 * This communication path is used to deliver asynchronous events from backend
 * to frontend, set up per connector.
 *
 * evt-event-channel
 *      Values:         <uपूर्णांक32_t>
 *
 *      The identअगरier of the Xen connector's event channel
 *      used to संकेत activity in the ring buffer.
 *
 * evt-ring-ref
 *      Values:         <uपूर्णांक32_t>
 *
 *      The Xen grant reference granting permission क्रम the backend to map
 *      a sole page of connector's event ring buffer.
 */

/*
 ******************************************************************************
 *                               STATE DIAGRAMS
 ******************************************************************************
 *
 * Tool stack creates front and back state nodes with initial state
 * XenbusStateInitialising.
 * Tool stack creates and sets up frontend display configuration
 * nodes per करोमुख्य.
 *
 *-------------------------------- Normal flow --------------------------------
 *
 * Front                                Back
 * =================================    =====================================
 * XenbusStateInitialising              XenbusStateInitialising
 *                                       o Query backend device identअगरication
 *                                         data.
 *                                       o Open and validate backend device.
 *                                                |
 *                                                |
 *                                                V
 *                                      XenbusStateInitWait
 *
 * o Query frontend configuration
 * o Allocate and initialize
 *   event channels per configured
 *   connector.
 * o Publish transport parameters
 *   that will be in effect during
 *   this connection.
 *              |
 *              |
 *              V
 * XenbusStateInitialised
 *
 *                                       o Query frontend transport parameters.
 *                                       o Connect to the event channels.
 *                                                |
 *                                                |
 *                                                V
 *                                      XenbusStateConnected
 *
 *  o Create and initialize OS
 *    भव display connectors
 *    as per configuration.
 *              |
 *              |
 *              V
 * XenbusStateConnected
 *
 *                                      XenbusStateUnknown
 *                                      XenbusStateClosed
 *                                      XenbusStateClosing
 * o Remove भव display device
 * o Remove event channels
 *              |
 *              |
 *              V
 * XenbusStateClosed
 *
 *------------------------------- Recovery flow -------------------------------
 *
 * In हाल of frontend unrecoverable errors backend handles that as
 * अगर frontend goes पूर्णांकo the XenbusStateClosed state.
 *
 * In हाल of backend unrecoverable errors frontend tries removing
 * the भवized device. If this is possible at the moment of error,
 * then frontend goes पूर्णांकo the XenbusStateInitialising state and is पढ़ोy क्रम
 * new connection with backend. If the भवized device is still in use and
 * cannot be हटाओd, then frontend goes पूर्णांकo the XenbusStateReconfiguring state
 * until either the भवized device is हटाओd or backend initiates a new
 * connection. On the भवized device removal frontend goes पूर्णांकo the
 * XenbusStateInitialising state.
 *
 * Note on XenbusStateReconfiguring state of the frontend: अगर backend has
 * unrecoverable errors then frontend cannot send requests to the backend
 * and thus cannot provide functionality of the भवized device anymore.
 * After backend is back to normal the भवized device may still hold some
 * state: configuration in use, allocated buffers, client application state etc.
 * In most हालs, this will require frontend to implement complex recovery
 * reconnect logic. Instead, by going पूर्णांकo XenbusStateReconfiguring state,
 * frontend will make sure no new clients of the भवized device are
 * accepted, allow existing client(s) to निकास gracefully by संकेतing error
 * state etc.
 * Once all the clients are gone frontend can reinitialize the भवized
 * device and get पूर्णांकo XenbusStateInitialising state again संकेतing the
 * backend that a new connection can be made.
 *
 * There are multiple conditions possible under which frontend will go from
 * XenbusStateReconfiguring पूर्णांकo XenbusStateInitialising, some of them are OS
 * specअगरic. For example:
 * 1. The underlying OS framework may provide callbacks to संकेत that the last
 *    client of the भवized device has gone and the device can be हटाओd
 * 2. Frontend can schedule a deferred work (समयr/tasklet/workqueue)
 *    to periodically check अगर this is the right समय to re-try removal of
 *    the भवized device.
 * 3. By any other means.
 *
 ******************************************************************************
 *                             REQUEST CODES
 ******************************************************************************
 * Request codes [0; 15] are reserved and must not be used
 */

#घोषणा XENDISPL_OP_DBUF_CREATE		0x10
#घोषणा XENDISPL_OP_DBUF_DESTROY	0x11
#घोषणा XENDISPL_OP_FB_ATTACH		0x12
#घोषणा XENDISPL_OP_FB_DETACH		0x13
#घोषणा XENDISPL_OP_SET_CONFIG		0x14
#घोषणा XENDISPL_OP_PG_FLIP		0x15
/* The below command is available in protocol version 2 and above. */
#घोषणा XENDISPL_OP_GET_EDID		0x16

/*
 ******************************************************************************
 *                                 EVENT CODES
 ******************************************************************************
 */
#घोषणा XENDISPL_EVT_PG_FLIP		0x00

/*
 ******************************************************************************
 *               XENSTORE FIELD AND PATH NAME STRINGS, HELPERS
 ******************************************************************************
 */
#घोषणा XENDISPL_DRIVER_NAME		"vdispl"

#घोषणा XENDISPL_LIST_SEPARATOR		","
#घोषणा XENDISPL_RESOLUTION_SEPARATOR	"x"

#घोषणा XENDISPL_FIELD_BE_VERSIONS	"versions"
#घोषणा XENDISPL_FIELD_FE_VERSION	"version"
#घोषणा XENDISPL_FIELD_REQ_RING_REF	"req-ring-ref"
#घोषणा XENDISPL_FIELD_REQ_CHANNEL	"req-event-channel"
#घोषणा XENDISPL_FIELD_EVT_RING_REF	"evt-ring-ref"
#घोषणा XENDISPL_FIELD_EVT_CHANNEL	"evt-event-channel"
#घोषणा XENDISPL_FIELD_RESOLUTION	"resolution"
#घोषणा XENDISPL_FIELD_BE_ALLOC		"be-alloc"
#घोषणा XENDISPL_FIELD_UNIQUE_ID	"unique-id"

#घोषणा XENDISPL_EDID_BLOCK_SIZE	128
#घोषणा XENDISPL_EDID_BLOCK_COUNT	256
#घोषणा XENDISPL_EDID_MAX_SIZE		(XENDISPL_EDID_BLOCK_SIZE * XENDISPL_EDID_BLOCK_COUNT)

/*
 ******************************************************************************
 *                          STATUS RETURN CODES
 ******************************************************************************
 *
 * Status वापस code is zero on success and -XEN_EXX on failure.
 *
 ******************************************************************************
 *                              Assumptions
 ******************************************************************************
 * o usage of grant reference 0 as invalid grant reference:
 *   grant reference 0 is valid, but never exposed to a PV driver,
 *   because of the fact it is alपढ़ोy in use/reserved by the PV console.
 * o all references in this करोcument to page sizes must be treated
 *   as pages of size XEN_PAGE_SIZE unless otherwise noted.
 *
 ******************************************************************************
 *       Description of the protocol between frontend and backend driver
 ******************************************************************************
 *
 * The two halves of a Para-भव display driver communicate with
 * each other using shared pages and event channels.
 * Shared page contains a ring with request/response packets.
 *
 * All reserved fields in the काष्ठाures below must be 0.
 * Display buffers's cookie of value 0 is treated as invalid.
 * Framebuffer's cookie of value 0 is treated as invalid.
 *
 * For all request/response/event packets that use cookies:
 *   dbuf_cookie - uपूर्णांक64_t, unique to guest करोमुख्य value used by the backend
 *     to map remote display buffer to its local one
 *   fb_cookie - uपूर्णांक64_t, unique to guest करोमुख्य value used by the backend
 *     to map remote framebuffer to its local one
 *
 *---------------------------------- Requests ---------------------------------
 *
 * All requests/responses, which are not connector specअगरic, must be sent over
 * control ring of the connector which has the index value of 0:
 *   /local/करोमुख्य/<करोm-id>/device/vdispl/<dev-id>/0/req-ring-ref
 *
 * All request packets have the same length (64 octets)
 * All request packets have common header:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |    operation   |   reserved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 *   id - uपूर्णांक16_t, निजी guest value, echoed in response
 *   operation - uपूर्णांक8_t, operation code, XENDISPL_OP_???
 *
 * Request dbuf creation - request creation of a display buffer.
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |_OP_DBUF_CREATE |   reserved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                       dbuf_cookie low 32-bit                      | 12
 * +----------------+----------------+----------------+----------------+
 * |                       dbuf_cookie high 32-bit                     | 16
 * +----------------+----------------+----------------+----------------+
 * |                               width                               | 20
 * +----------------+----------------+----------------+----------------+
 * |                               height                              | 24
 * +----------------+----------------+----------------+----------------+
 * |                                bpp                                | 28
 * +----------------+----------------+----------------+----------------+
 * |                             buffer_sz                             | 32
 * +----------------+----------------+----------------+----------------+
 * |                               flags                               | 36
 * +----------------+----------------+----------------+----------------+
 * |                           gref_directory                          | 40
 * +----------------+----------------+----------------+----------------+
 * |                             data_ofs                              | 44
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 48
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Must be sent over control ring of the connector which has the index
 * value of 0:
 *   /local/करोमुख्य/<करोm-id>/device/vdispl/<dev-id>/0/req-ring-ref
 * All unused bits in flags field must be set to 0.
 *
 * An attempt to create multiple display buffers with the same dbuf_cookie is
 * an error. dbuf_cookie can be re-used after destroying the corresponding
 * display buffer.
 *
 * Width and height of the display buffers can be smaller, equal or bigger
 * than the connector's resolution. Depth/pixel क्रमmat of the inभागidual
 * buffers can dअगरfer as well.
 *
 * width - uपूर्णांक32_t, width in pixels
 * height - uपूर्णांक32_t, height in pixels
 * bpp - uपूर्णांक32_t, bits per pixel
 * buffer_sz - uपूर्णांक32_t, buffer size to be allocated, octets
 * flags - uपूर्णांक32_t, flags of the operation
 *   o XENDISPL_DBUF_FLG_REQ_ALLOC - अगर set, then backend is requested
 *     to allocate the buffer with the parameters provided in this request.
 *     Page directory is handled as follows:
 *       Frontend on request:
 *         o allocates pages क्रम the directory (gref_directory,
 *           gref_dir_next_page(s)
 *         o grants permissions क्रम the pages of the directory to the backend
 *         o sets gref_dir_next_page fields
 *       Backend on response:
 *         o grants permissions क्रम the pages of the buffer allocated to
 *           the frontend
 *         o fills in page directory with grant references
 *           (gref[] in काष्ठा xendispl_page_directory)
 * gref_directory - grant_ref_t, a reference to the first shared page
 *   describing shared buffer references. At least one page exists. If shared
 *   buffer size (buffer_sz) exceeds what can be addressed by this single page,
 *   then reference to the next page must be supplied (see gref_dir_next_page
 *   below)
 * data_ofs - uपूर्णांक32_t, offset of the data in the buffer, octets
 */

#घोषणा XENDISPL_DBUF_FLG_REQ_ALLOC	(1 << 0)

काष्ठा xendispl_dbuf_create_req अणु
	uपूर्णांक64_t dbuf_cookie;
	uपूर्णांक32_t width;
	uपूर्णांक32_t height;
	uपूर्णांक32_t bpp;
	uपूर्णांक32_t buffer_sz;
	uपूर्णांक32_t flags;
	grant_ref_t gref_directory;
	uपूर्णांक32_t data_ofs;
पूर्ण;

/*
 * Shared page क्रम XENDISPL_OP_DBUF_CREATE buffer descriptor (gref_directory in
 * the request) employs a list of pages, describing all pages of the shared
 * data buffer:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |                        gref_dir_next_page                         | 4
 * +----------------+----------------+----------------+----------------+
 * |                              gref[0]                              | 8
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                              gref[i]                              | i*4+8
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             gref[N - 1]                           | N*4+8
 * +----------------+----------------+----------------+----------------+
 *
 * gref_dir_next_page - grant_ref_t, reference to the next page describing
 *   page directory. Must be 0 अगर there are no more pages in the list.
 * gref[i] - grant_ref_t, reference to a shared page of the buffer
 *   allocated at XENDISPL_OP_DBUF_CREATE
 *
 * Number of grant_ref_t entries in the whole page directory is not
 * passed, but instead can be calculated as:
 *   num_grefs_total = (XENDISPL_OP_DBUF_CREATE.buffer_sz + XEN_PAGE_SIZE - 1) /
 *       XEN_PAGE_SIZE
 */

काष्ठा xendispl_page_directory अणु
	grant_ref_t gref_dir_next_page;
	grant_ref_t gref[1]; /* Variable length */
पूर्ण;

/*
 * Request dbuf deकाष्ठाion - destroy a previously allocated display buffer:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |_OP_DBUF_DESTROY|   reserved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                       dbuf_cookie low 32-bit                      | 12
 * +----------------+----------------+----------------+----------------+
 * |                       dbuf_cookie high 32-bit                     | 16
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Must be sent over control ring of the connector which has the index
 * value of 0:
 *   /local/करोमुख्य/<करोm-id>/device/vdispl/<dev-id>/0/req-ring-ref
 */

काष्ठा xendispl_dbuf_destroy_req अणु
	uपूर्णांक64_t dbuf_cookie;
पूर्ण;

/*
 * Request framebuffer attachment - request attachment of a framebuffer to
 * previously created display buffer.
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                | _OP_FB_ATTACH  |   reserved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                       dbuf_cookie low 32-bit                      | 12
 * +----------------+----------------+----------------+----------------+
 * |                       dbuf_cookie high 32-bit                     | 16
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie low 32-bit                       | 20
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie high 32-bit                      | 24
 * +----------------+----------------+----------------+----------------+
 * |                               width                               | 28
 * +----------------+----------------+----------------+----------------+
 * |                               height                              | 32
 * +----------------+----------------+----------------+----------------+
 * |                            pixel_क्रमmat                           | 36
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 40
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Must be sent over control ring of the connector which has the index
 * value of 0:
 *   /local/करोमुख्य/<करोm-id>/device/vdispl/<dev-id>/0/req-ring-ref
 * Width and height can be smaller, equal or bigger than the connector's
 * resolution.
 *
 * An attempt to create multiple frame buffers with the same fb_cookie is
 * an error. fb_cookie can be re-used after destroying the corresponding
 * frame buffer.
 *
 * width - uपूर्णांक32_t, width in pixels
 * height - uपूर्णांक32_t, height in pixels
 * pixel_क्रमmat - uपूर्णांक32_t, pixel क्रमmat of the framebuffer, FOURCC code
 */

काष्ठा xendispl_fb_attach_req अणु
	uपूर्णांक64_t dbuf_cookie;
	uपूर्णांक64_t fb_cookie;
	uपूर्णांक32_t width;
	uपूर्णांक32_t height;
	uपूर्णांक32_t pixel_क्रमmat;
पूर्ण;

/*
 * Request framebuffer detach - detach a previously
 * attached framebuffer from the display buffer in request:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |  _OP_FB_DETACH |   reserved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie low 32-bit                       | 12
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie high 32-bit                      | 16
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Must be sent over control ring of the connector which has the index
 * value of 0:
 *   /local/करोमुख्य/<करोm-id>/device/vdispl/<dev-id>/0/req-ring-ref
 */

काष्ठा xendispl_fb_detach_req अणु
	uपूर्णांक64_t fb_cookie;
पूर्ण;

/*
 * Request configuration set/reset - request to set or reset
 * the configuration/mode of the display:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                | _OP_SET_CONFIG |   reserved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie low 32-bit                       | 12
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie high 32-bit                      | 16
 * +----------------+----------------+----------------+----------------+
 * |                                 x                                 | 20
 * +----------------+----------------+----------------+----------------+
 * |                                 y                                 | 24
 * +----------------+----------------+----------------+----------------+
 * |                               width                               | 28
 * +----------------+----------------+----------------+----------------+
 * |                               height                              | 32
 * +----------------+----------------+----------------+----------------+
 * |                                bpp                                | 40
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 44
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Pass all zeros to reset, otherwise command is treated as
 * configuration set.
 * Framebuffer's cookie defines which framebuffer/dbuf must be
 * displayed जबतक enabling display (applying configuration).
 * x, y, width and height are bound by the connector's resolution and must not
 * exceed it.
 *
 * x - uपूर्णांक32_t, starting position in pixels by X axis
 * y - uपूर्णांक32_t, starting position in pixels by Y axis
 * width - uपूर्णांक32_t, width in pixels
 * height - uपूर्णांक32_t, height in pixels
 * bpp - uपूर्णांक32_t, bits per pixel
 */

काष्ठा xendispl_set_config_req अणु
	uपूर्णांक64_t fb_cookie;
	uपूर्णांक32_t x;
	uपूर्णांक32_t y;
	uपूर्णांक32_t width;
	uपूर्णांक32_t height;
	uपूर्णांक32_t bpp;
पूर्ण;

/*
 * Request page flip - request to flip a page identअगरied by the framebuffer
 * cookie:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                | _OP_PG_FLIP    |   reserved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie low 32-bit                       | 12
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie high 32-bit                      | 16
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 */

काष्ठा xendispl_page_flip_req अणु
	uपूर्णांक64_t fb_cookie;
पूर्ण;

/*
 * Request EDID - request EDID describing current connector:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                | _OP_GET_EDID   |   reserved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             buffer_sz                             | 8
 * +----------------+----------------+----------------+----------------+
 * |                          gref_directory                           | 12
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 16
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Notes:
 *   - This command is not available in protocol version 1 and should be
 *     ignored.
 *   - This request is optional and अगर not supported then visible area
 *     is defined by the relevant XenStore's "resolution" property.
 *   - Shared buffer, allocated क्रम EDID storage, must not be less then
 *     XENDISPL_EDID_MAX_SIZE octets.
 *
 * buffer_sz - uपूर्णांक32_t, buffer size to be allocated, octets
 * gref_directory - grant_ref_t, a reference to the first shared page
 *   describing EDID buffer references. See XENDISPL_OP_DBUF_CREATE क्रम
 *   grant page directory काष्ठाure (काष्ठा xendispl_page_directory).
 *
 * See response क्रमmat क्रम this request.
 */

काष्ठा xendispl_get_edid_req अणु
	uपूर्णांक32_t buffer_sz;
	grant_ref_t gref_directory;
पूर्ण;

/*
 *---------------------------------- Responses --------------------------------
 *
 * All response packets have the same length (64 octets)
 *
 * All response packets have common header:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |            reserved             | 4
 * +----------------+----------------+----------------+----------------+
 * |                              status                               | 8
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 12
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * id - uपूर्णांक16_t, निजी guest value, echoed from request
 * status - पूर्णांक32_t, response status, zero on success and -XEN_EXX on failure
 *
 *
 * Get EDID response - response क्रम XENDISPL_OP_GET_EDID:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |    operation   |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                              status                               | 8
 * +----------------+----------------+----------------+----------------+
 * |                             edid_sz                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 16
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Notes:
 *   - This response is not available in protocol version 1 and should be
 *     ignored.
 *
 * edid_sz - uपूर्णांक32_t, size of the EDID, octets
 */

काष्ठा xendispl_get_edid_resp अणु
	uपूर्णांक32_t edid_sz;
पूर्ण;

/*
 *----------------------------------- Events ----------------------------------
 *
 * Events are sent via a shared page allocated by the front and propagated by
 *   evt-event-channel/evt-ring-ref XenStore entries
 * All event packets have the same length (64 octets)
 * All event packets have common header:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |      type      |   reserved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 *
 * id - uपूर्णांक16_t, event id, may be used by front
 * type - uपूर्णांक8_t, type of the event
 *
 *
 * Page flip complete event - event from back to front on page flip completed:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |   _EVT_PG_FLIP |   reserved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie low 32-bit                       | 12
 * +----------------+----------------+----------------+----------------+
 * |                        fb_cookie high 32-bit                      | 16
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 */

काष्ठा xendispl_pg_flip_evt अणु
	uपूर्णांक64_t fb_cookie;
पूर्ण;

काष्ठा xendispl_req अणु
	uपूर्णांक16_t id;
	uपूर्णांक8_t operation;
	uपूर्णांक8_t reserved[5];
	जोड़ अणु
		काष्ठा xendispl_dbuf_create_req dbuf_create;
		काष्ठा xendispl_dbuf_destroy_req dbuf_destroy;
		काष्ठा xendispl_fb_attach_req fb_attach;
		काष्ठा xendispl_fb_detach_req fb_detach;
		काष्ठा xendispl_set_config_req set_config;
		काष्ठा xendispl_page_flip_req pg_flip;
		काष्ठा xendispl_get_edid_req get_edid;
		uपूर्णांक8_t reserved[56];
	पूर्ण op;
पूर्ण;

काष्ठा xendispl_resp अणु
	uपूर्णांक16_t id;
	uपूर्णांक8_t operation;
	uपूर्णांक8_t reserved;
	पूर्णांक32_t status;
	जोड़ अणु
		काष्ठा xendispl_get_edid_resp get_edid;
		uपूर्णांक8_t reserved1[56];
	पूर्ण op;
पूर्ण;

काष्ठा xendispl_evt अणु
	uपूर्णांक16_t id;
	uपूर्णांक8_t type;
	uपूर्णांक8_t reserved[5];
	जोड़ अणु
		काष्ठा xendispl_pg_flip_evt pg_flip;
		uपूर्णांक8_t reserved[56];
	पूर्ण op;
पूर्ण;

DEFINE_RING_TYPES(xen_displअगर, काष्ठा xendispl_req, काष्ठा xendispl_resp);

/*
 ******************************************************************************
 *                        Back to front events delivery
 ******************************************************************************
 * In order to deliver asynchronous events from back to front a shared page is
 * allocated by front and its granted reference propagated to back via
 * XenStore entries (evt-ring-ref/evt-event-channel).
 * This page has a common header used by both front and back to synchronize
 * access and control event's ring buffer, जबतक back being a producer of the
 * events and front being a consumer. The rest of the page after the header
 * is used क्रम event packets.
 *
 * Upon reception of an event(s) front may confirm its reception
 * क्रम either each event, group of events or none.
 */

काष्ठा xendispl_event_page अणु
	uपूर्णांक32_t in_cons;
	uपूर्णांक32_t in_prod;
	uपूर्णांक8_t reserved[56];
पूर्ण;

#घोषणा XENDISPL_EVENT_PAGE_SIZE XEN_PAGE_SIZE
#घोषणा XENDISPL_IN_RING_OFFS (माप(काष्ठा xendispl_event_page))
#घोषणा XENDISPL_IN_RING_SIZE (XENDISPL_EVENT_PAGE_SIZE - XENDISPL_IN_RING_OFFS)
#घोषणा XENDISPL_IN_RING_LEN (XENDISPL_IN_RING_SIZE / माप(काष्ठा xendispl_evt))
#घोषणा XENDISPL_IN_RING(page) \
	((काष्ठा xendispl_evt *)((अक्षर *)(page) + XENDISPL_IN_RING_OFFS))
#घोषणा XENDISPL_IN_RING_REF(page, idx) \
	(XENDISPL_IN_RING((page))[(idx) % XENDISPL_IN_RING_LEN])

#पूर्ण_अगर /* __XEN_PUBLIC_IO_DISPLIF_H__ */
