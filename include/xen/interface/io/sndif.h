<शैली गुरु>
/******************************************************************************
 * sndअगर.h
 *
 * Unअगरied sound-device I/O पूर्णांकerface क्रम Xen guest OSes.
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
 * Copyright (C) 2013-2015 GlobalLogic Inc.
 * Copyright (C) 2016-2017 EPAM Systems Inc.
 *
 * Authors: Oleksandr Andrushchenko <oleksandr_andrushchenko@epam.com>
 *          Oleksandr Grytsov <oleksandr_grytsov@epam.com>
 *          Oleksandr Dmytryshyn <oleksandr.dmytryshyn@globallogic.com>
 *          Iurii Konovalenko <iurii.konovalenko@globallogic.com>
 */

#अगर_अघोषित __XEN_PUBLIC_IO_SNDIF_H__
#घोषणा __XEN_PUBLIC_IO_SNDIF_H__

#समावेश "ring.h"
#समावेश "../grant_table.h"

/*
 ******************************************************************************
 *                           Protocol version
 ******************************************************************************
 */
#घोषणा XENSND_PROTOCOL_VERSION	2

/*
 ******************************************************************************
 *                  Feature and Parameter Negotiation
 ******************************************************************************
 *
 * Front->back notअगरications: when enqueuing a new request, sending a
 * notअगरication can be made conditional on xensnd_req (i.e., the generic
 * hold-off mechanism provided by the ring macros). Backends must set
 * xensnd_req appropriately (e.g., using RING_FINAL_CHECK_FOR_REQUESTS()).
 *
 * Back->front notअगरications: when enqueuing a new response, sending a
 * notअगरication can be made conditional on xensnd_resp (i.e., the generic
 * hold-off mechanism provided by the ring macros). Frontends must set
 * xensnd_resp appropriately (e.g., using RING_FINAL_CHECK_FOR_RESPONSES()).
 *
 * The two halves of a para-भव sound card driver utilize nodes within
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
 * Note: depending on the use-हाल backend can expose more sound cards and
 * PCM devices/streams than the underlying HW physically has by employing
 * SW mixers, configuring भव sound streams, channels etc.
 *
 * This is an example of backend and frontend configuration:
 *
 *--------------------------------- Backend -----------------------------------
 *
 * /local/करोमुख्य/0/backend/vsnd/1/0/frontend-id = "1"
 * /local/करोमुख्य/0/backend/vsnd/1/0/frontend = "/local/domain/1/device/vsnd/0"
 * /local/करोमुख्य/0/backend/vsnd/1/0/state = "4"
 * /local/करोमुख्य/0/backend/vsnd/1/0/versions = "1,2"
 *
 *--------------------------------- Frontend ----------------------------------
 *
 * /local/करोमुख्य/1/device/vsnd/0/backend-id = "0"
 * /local/करोमुख्य/1/device/vsnd/0/backend = "/local/domain/0/backend/vsnd/1/0"
 * /local/करोमुख्य/1/device/vsnd/0/state = "4"
 * /local/करोमुख्य/1/device/vsnd/0/version = "1"
 *
 *----------------------------- Card configuration ----------------------------
 *
 * /local/करोमुख्य/1/device/vsnd/0/लघु-name = "Card short name"
 * /local/करोमुख्य/1/device/vsnd/0/दीर्घ-name = "Card long name"
 * /local/करोमुख्य/1/device/vsnd/0/sample-rates = "8000,32000,44100,48000,96000"
 * /local/करोमुख्य/1/device/vsnd/0/sample-क्रमmats = "s8,u8,s16_le,s16_be"
 * /local/करोमुख्य/1/device/vsnd/0/buffer-size = "262144"
 *
 *------------------------------- PCM device 0 --------------------------------
 *
 * /local/करोमुख्य/1/device/vsnd/0/0/name = "General analog"
 * /local/करोमुख्य/1/device/vsnd/0/0/channels-max = "5"
 *
 *----------------------------- Stream 0, playback ----------------------------
 *
 * /local/करोमुख्य/1/device/vsnd/0/0/0/type = "p"
 * /local/करोमुख्य/1/device/vsnd/0/0/0/sample-क्रमmats = "s8,u8"
 * /local/करोमुख्य/1/device/vsnd/0/0/0/unique-id = "0"
 *
 * /local/करोमुख्य/1/device/vsnd/0/0/0/ring-ref = "386"
 * /local/करोमुख्य/1/device/vsnd/0/0/0/event-channel = "15"
 * /local/करोमुख्य/1/device/vsnd/0/0/0/evt-ring-ref = "1386"
 * /local/करोमुख्य/1/device/vsnd/0/0/0/evt-event-channel = "215"
 *
 *------------------------------ Stream 1, capture ----------------------------
 *
 * /local/करोमुख्य/1/device/vsnd/0/0/1/type = "c"
 * /local/करोमुख्य/1/device/vsnd/0/0/1/channels-max = "2"
 * /local/करोमुख्य/1/device/vsnd/0/0/1/unique-id = "1"
 *
 * /local/करोमुख्य/1/device/vsnd/0/0/1/ring-ref = "384"
 * /local/करोमुख्य/1/device/vsnd/0/0/1/event-channel = "13"
 * /local/करोमुख्य/1/device/vsnd/0/0/1/evt-ring-ref = "1384"
 * /local/करोमुख्य/1/device/vsnd/0/0/1/evt-event-channel = "213"
 *
 *------------------------------- PCM device 1 --------------------------------
 *
 * /local/करोमुख्य/1/device/vsnd/0/1/name = "HDMI-0"
 * /local/करोमुख्य/1/device/vsnd/0/1/sample-rates = "8000,32000,44100"
 *
 *------------------------------ Stream 0, capture ----------------------------
 *
 * /local/करोमुख्य/1/device/vsnd/0/1/0/type = "c"
 * /local/करोमुख्य/1/device/vsnd/0/1/0/unique-id = "2"
 *
 * /local/करोमुख्य/1/device/vsnd/0/1/0/ring-ref = "387"
 * /local/करोमुख्य/1/device/vsnd/0/1/0/event-channel = "151"
 * /local/करोमुख्य/1/device/vsnd/0/1/0/evt-ring-ref = "1387"
 * /local/करोमुख्य/1/device/vsnd/0/1/0/evt-event-channel = "351"
 *
 *------------------------------- PCM device 2 --------------------------------
 *
 * /local/करोमुख्य/1/device/vsnd/0/2/name = "SPDIF"
 *
 *----------------------------- Stream 0, playback ----------------------------
 *
 * /local/करोमुख्य/1/device/vsnd/0/2/0/type = "p"
 * /local/करोमुख्य/1/device/vsnd/0/2/0/unique-id = "3"
 *
 * /local/करोमुख्य/1/device/vsnd/0/2/0/ring-ref = "389"
 * /local/करोमुख्य/1/device/vsnd/0/2/0/event-channel = "152"
 * /local/करोमुख्य/1/device/vsnd/0/2/0/evt-ring-ref = "1389"
 * /local/करोमुख्य/1/device/vsnd/0/2/0/evt-event-channel = "452"
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
 *      List of XENSND_LIST_SEPARATOR separated protocol versions supported
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
 * pcm-dev-idx
 *      Values:         <uपूर्णांक8_t>
 *
 *      Zero based contigous index of the PCM device.
 *
 * stream-idx
 *      Values:         <uपूर्णांक8_t>
 *
 *      Zero based contigous index of the stream of the PCM device.
 *
 * The following pattern is used क्रम addressing:
 *   /local/करोमुख्य/<करोm-id>/device/vsnd/<dev-id>/<pcm-dev-idx>/<stream-idx>/...
 *
 *----------------------------- Protocol version ------------------------------
 *
 * version
 *      Values:         <string>
 *
 *      Protocol version, chosen among the ones supported by the backend.
 *
 *------------------------------- PCM settings --------------------------------
 *
 * Every भवized sound frontend has a set of PCM devices and streams, each
 * could be inभागidually configured. Part of the PCM configuration can be
 * defined at higher level of the hierarchy and be fully or partially re-used
 * by the underlying layers. These configuration values are:
 *  o number of channels (min/max)
 *  o supported sample rates
 *  o supported sample क्रमmats.
 * E.g. one can define these values क्रम the whole card, device or stream.
 * Every underlying layer in turn can re-define some or all of them to better
 * fit its needs. For example, card may define number of channels to be
 * in [1; 8] range, and some particular stream may be limited to [1; 2] only.
 * The rule is that the underlying layer must be a subset of the upper layer
 * range.
 *
 * channels-min
 *      Values:         <uपूर्णांक8_t>
 *
 *      The minimum amount of channels that is supported, [1; channels-max].
 *      Optional, अगर not set or omitted a value of 1 is used.
 *
 * channels-max
 *      Values:         <uपूर्णांक8_t>
 *
 *      The maximum amount of channels that is supported.
 *      Must be at least <channels-min>.
 *
 * sample-rates
 *      Values:         <list of uपूर्णांक32_t>
 *
 *      List of supported sample rates separated by XENSND_LIST_SEPARATOR.
 *      Sample rates are expressed as a list of decimal values w/o any
 *      ordering requirement.
 *
 * sample-क्रमmats
 *      Values:         <list of XENSND_PCM_FORMAT_XXX_STR>
 *
 *      List of supported sample क्रमmats separated by XENSND_LIST_SEPARATOR.
 *      Items must not exceed XENSND_SAMPLE_FORMAT_MAX_LEN length.
 *
 * buffer-size
 *      Values:         <uपूर्णांक32_t>
 *
 *      The maximum size in octets of the buffer to allocate per stream.
 *
 *----------------------- Virtual sound card settings -------------------------
 * लघु-name
 *      Values:         <अक्षर[32]>
 *
 *      Short name of the भव sound card. Optional.
 *
 * दीर्घ-name
 *      Values:         <अक्षर[80]>
 *
 *      Long name of the भव sound card. Optional.
 *
 *----------------------------- Device settings -------------------------------
 * name
 *      Values:         <अक्षर[80]>
 *
 *      Name of the sound device within the भव sound card. Optional.
 *
 *----------------------------- Stream settings -------------------------------
 *
 * type
 *      Values:         "p", "c"
 *
 *      Stream type: "p" - playback stream, "c" - capture stream
 *
 *      If both capture and playback are needed then two streams need to be
 *      defined under the same device.
 *
 * unique-id
 *      Values:         <string>
 *
 *      After stream initialization it is asचिन्हित a unique ID, so every
 *      stream of the frontend can be identअगरied by the backend by this ID.
 *      This can be UUID or such.
 *
 *-------------------- Stream Request Transport Parameters --------------------
 *
 * event-channel
 *      Values:         <uपूर्णांक32_t>
 *
 *      The identअगरier of the Xen event channel used to संकेत activity
 *      in the ring buffer.
 *
 * ring-ref
 *      Values:         <uपूर्णांक32_t>
 *
 *      The Xen grant reference granting permission क्रम the backend to map
 *      a sole page in a single page sized ring buffer.
 *
 *--------------------- Stream Event Transport Parameters ---------------------
 *
 * This communication path is used to deliver asynchronous events from backend
 * to frontend, set up per stream.
 *
 * evt-event-channel
 *      Values:         <uपूर्णांक32_t>
 *
 *      The identअगरier of the Xen event channel used to संकेत activity
 *      in the ring buffer.
 *
 * evt-ring-ref
 *      Values:         <uपूर्णांक32_t>
 *
 *      The Xen grant reference granting permission क्रम the backend to map
 *      a sole page in a single page sized ring buffer.
 *
 ******************************************************************************
 *                               STATE DIAGRAMS
 ******************************************************************************
 *
 * Tool stack creates front and back state nodes with initial state
 * XenbusStateInitialising.
 * Tool stack creates and sets up frontend sound configuration nodes per करोमुख्य.
 *
 * Front                                Back
 * =================================    =====================================
 * XenbusStateInitialising              XenbusStateInitialising
 *                                       o Query backend device identअगरication
 *                                         data.
 *                                       o Open and validate backend device.
 *                                                      |
 *                                                      |
 *                                                      V
 *                                      XenbusStateInitWait
 *
 * o Query frontend configuration
 * o Allocate and initialize
 *   event channels per configured
 *   playback/capture stream.
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
 *                                                      |
 *                                                      |
 *                                                      V
 *                                      XenbusStateConnected
 *
 *  o Create and initialize OS
 *    भव sound device instances
 *    as per configuration.
 *              |
 *              |
 *              V
 * XenbusStateConnected
 *
 *                                      XenbusStateUnknown
 *                                      XenbusStateClosed
 *                                      XenbusStateClosing
 * o Remove भव sound device
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
 * until either the भवized device हटाओd or backend initiates a new
 * connection. On the भवized device removal frontend goes पूर्णांकo the
 * XenbusStateInitialising state.
 *
 * Note on XenbusStateReconfiguring state of the frontend: अगर backend has
 * unrecoverable errors then frontend cannot send requests to the backend
 * and thus cannot provide functionality of the भवized device anymore.
 * After backend is back to normal the भवized device may still hold some
 * state: configuration in use, allocated buffers, client application state etc.
 * So, in most हालs, this will require frontend to implement complex recovery
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
 *                             PCM FORMATS
 ******************************************************************************
 *
 * XENSND_PCM_FORMAT_<क्रमmat>[_<endian>]
 *
 * क्रमmat: <S/U/F><bits> or <name>
 *     S - चिन्हित, U - अचिन्हित, F - भग्न
 *     bits - 8, 16, 24, 32
 *     name - MU_LAW, GSM, etc.
 *
 * endian: <LE/BE>, may be असलent
 *     LE - Little endian, BE - Big endian
 */
#घोषणा XENSND_PCM_FORMAT_S8		0
#घोषणा XENSND_PCM_FORMAT_U8		1
#घोषणा XENSND_PCM_FORMAT_S16_LE	2
#घोषणा XENSND_PCM_FORMAT_S16_BE	3
#घोषणा XENSND_PCM_FORMAT_U16_LE	4
#घोषणा XENSND_PCM_FORMAT_U16_BE	5
#घोषणा XENSND_PCM_FORMAT_S24_LE	6
#घोषणा XENSND_PCM_FORMAT_S24_BE	7
#घोषणा XENSND_PCM_FORMAT_U24_LE	8
#घोषणा XENSND_PCM_FORMAT_U24_BE	9
#घोषणा XENSND_PCM_FORMAT_S32_LE	10
#घोषणा XENSND_PCM_FORMAT_S32_BE	11
#घोषणा XENSND_PCM_FORMAT_U32_LE	12
#घोषणा XENSND_PCM_FORMAT_U32_BE	13
#घोषणा XENSND_PCM_FORMAT_F32_LE	14 /* 4-byte भग्न, IEEE-754 32-bit, */
#घोषणा XENSND_PCM_FORMAT_F32_BE	15 /* range -1.0 to 1.0              */
#घोषणा XENSND_PCM_FORMAT_F64_LE	16 /* 8-byte भग्न, IEEE-754 64-bit, */
#घोषणा XENSND_PCM_FORMAT_F64_BE	17 /* range -1.0 to 1.0              */
#घोषणा XENSND_PCM_FORMAT_IEC958_SUBFRAME_LE 18
#घोषणा XENSND_PCM_FORMAT_IEC958_SUBFRAME_BE 19
#घोषणा XENSND_PCM_FORMAT_MU_LAW	20
#घोषणा XENSND_PCM_FORMAT_A_LAW		21
#घोषणा XENSND_PCM_FORMAT_IMA_ADPCM	22
#घोषणा XENSND_PCM_FORMAT_MPEG		23
#घोषणा XENSND_PCM_FORMAT_GSM		24

/*
 ******************************************************************************
 *                             REQUEST CODES
 ******************************************************************************
 */
#घोषणा XENSND_OP_OPEN			0
#घोषणा XENSND_OP_CLOSE			1
#घोषणा XENSND_OP_READ			2
#घोषणा XENSND_OP_WRITE			3
#घोषणा XENSND_OP_SET_VOLUME		4
#घोषणा XENSND_OP_GET_VOLUME		5
#घोषणा XENSND_OP_MUTE			6
#घोषणा XENSND_OP_UNMUTE		7
#घोषणा XENSND_OP_TRIGGER		8
#घोषणा XENSND_OP_HW_PARAM_QUERY	9

#घोषणा XENSND_OP_TRIGGER_START		0
#घोषणा XENSND_OP_TRIGGER_PAUSE		1
#घोषणा XENSND_OP_TRIGGER_STOP		2
#घोषणा XENSND_OP_TRIGGER_RESUME	3

/*
 ******************************************************************************
 *                                 EVENT CODES
 ******************************************************************************
 */
#घोषणा XENSND_EVT_CUR_POS		0

/*
 ******************************************************************************
 *               XENSTORE FIELD AND PATH NAME STRINGS, HELPERS
 ******************************************************************************
 */
#घोषणा XENSND_DRIVER_NAME		"vsnd"

#घोषणा XENSND_LIST_SEPARATOR		","
/* Field names */
#घोषणा XENSND_FIELD_BE_VERSIONS	"versions"
#घोषणा XENSND_FIELD_FE_VERSION		"version"
#घोषणा XENSND_FIELD_VCARD_SHORT_NAME	"short-name"
#घोषणा XENSND_FIELD_VCARD_LONG_NAME	"long-name"
#घोषणा XENSND_FIELD_RING_REF		"ring-ref"
#घोषणा XENSND_FIELD_EVT_CHNL		"event-channel"
#घोषणा XENSND_FIELD_EVT_RING_REF	"evt-ring-ref"
#घोषणा XENSND_FIELD_EVT_EVT_CHNL	"evt-event-channel"
#घोषणा XENSND_FIELD_DEVICE_NAME	"name"
#घोषणा XENSND_FIELD_TYPE		"type"
#घोषणा XENSND_FIELD_STREAM_UNIQUE_ID	"unique-id"
#घोषणा XENSND_FIELD_CHANNELS_MIN	"channels-min"
#घोषणा XENSND_FIELD_CHANNELS_MAX	"channels-max"
#घोषणा XENSND_FIELD_SAMPLE_RATES	"sample-rates"
#घोषणा XENSND_FIELD_SAMPLE_FORMATS	"sample-formats"
#घोषणा XENSND_FIELD_BUFFER_SIZE	"buffer-size"

/* Stream type field values. */
#घोषणा XENSND_STREAM_TYPE_PLAYBACK	"p"
#घोषणा XENSND_STREAM_TYPE_CAPTURE	"c"
/* Sample rate max string length */
#घोषणा XENSND_SAMPLE_RATE_MAX_LEN	11
/* Sample क्रमmat field values */
#घोषणा XENSND_SAMPLE_FORMAT_MAX_LEN	24

#घोषणा XENSND_PCM_FORMAT_S8_STR	"s8"
#घोषणा XENSND_PCM_FORMAT_U8_STR	"u8"
#घोषणा XENSND_PCM_FORMAT_S16_LE_STR	"s16_le"
#घोषणा XENSND_PCM_FORMAT_S16_BE_STR	"s16_be"
#घोषणा XENSND_PCM_FORMAT_U16_LE_STR	"u16_le"
#घोषणा XENSND_PCM_FORMAT_U16_BE_STR	"u16_be"
#घोषणा XENSND_PCM_FORMAT_S24_LE_STR	"s24_le"
#घोषणा XENSND_PCM_FORMAT_S24_BE_STR	"s24_be"
#घोषणा XENSND_PCM_FORMAT_U24_LE_STR	"u24_le"
#घोषणा XENSND_PCM_FORMAT_U24_BE_STR	"u24_be"
#घोषणा XENSND_PCM_FORMAT_S32_LE_STR	"s32_le"
#घोषणा XENSND_PCM_FORMAT_S32_BE_STR	"s32_be"
#घोषणा XENSND_PCM_FORMAT_U32_LE_STR	"u32_le"
#घोषणा XENSND_PCM_FORMAT_U32_BE_STR	"u32_be"
#घोषणा XENSND_PCM_FORMAT_F32_LE_STR	"float_le"
#घोषणा XENSND_PCM_FORMAT_F32_BE_STR	"float_be"
#घोषणा XENSND_PCM_FORMAT_F64_LE_STR	"float64_le"
#घोषणा XENSND_PCM_FORMAT_F64_BE_STR	"float64_be"
#घोषणा XENSND_PCM_FORMAT_IEC958_SUBFRAME_LE_STR "iec958_subframe_le"
#घोषणा XENSND_PCM_FORMAT_IEC958_SUBFRAME_BE_STR "iec958_subframe_be"
#घोषणा XENSND_PCM_FORMAT_MU_LAW_STR	"mu_law"
#घोषणा XENSND_PCM_FORMAT_A_LAW_STR	"a_law"
#घोषणा XENSND_PCM_FORMAT_IMA_ADPCM_STR	"ima_adpcm"
#घोषणा XENSND_PCM_FORMAT_MPEG_STR	"mpeg"
#घोषणा XENSND_PCM_FORMAT_GSM_STR	"gsm"


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
 * The two halves of a Para-भव sound driver communicate with
 * each other using shared pages and event channels.
 * Shared page contains a ring with request/response packets.
 *
 * Packets, used क्रम input/output operations, e.g. पढ़ो/ग_लिखो, set/get volume,
 * etc., provide offset/length fields in order to allow asynchronous protocol
 * operation with buffer space sharing: part of the buffer allocated at
 * XENSND_OP_OPEN can be used क्रम audio samples and part, क्रम example,
 * क्रम volume control.
 *
 * All reserved fields in the काष्ठाures below must be 0.
 *
 *---------------------------------- Requests ---------------------------------
 *
 * All request packets have the same length (64 octets)
 * All request packets have common header:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |    operation   |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 *   id - uपूर्णांक16_t, निजी guest value, echoed in response
 *   operation - uपूर्णांक8_t, operation code, XENSND_OP_???
 *
 * For all packets which use offset and length:
 *   offset - uपूर्णांक32_t, पढ़ो or ग_लिखो data offset within the shared buffer,
 *     passed with XENSND_OP_OPEN request, octets,
 *     [0; XENSND_OP_OPEN.buffer_sz - 1].
 *   length - uपूर्णांक32_t, पढ़ो or ग_लिखो data length, octets
 *
 * Request खोलो - खोलो a PCM stream क्रम playback or capture:
 *
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                | XENSND_OP_OPEN |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                             pcm_rate                              | 12
 * +----------------+----------------+----------------+----------------+
 * |  pcm_क्रमmat    |  pcm_channels  |             reserved            | 16
 * +----------------+----------------+----------------+----------------+
 * |                             buffer_sz                             | 20
 * +----------------+----------------+----------------+----------------+
 * |                           gref_directory                          | 24
 * +----------------+----------------+----------------+----------------+
 * |                             period_sz                             | 28
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 32
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * pcm_rate - uपूर्णांक32_t, stream data rate, Hz
 * pcm_क्रमmat - uपूर्णांक8_t, XENSND_PCM_FORMAT_XXX value
 * pcm_channels - uपूर्णांक8_t, number of channels of this stream,
 *   [channels-min; channels-max]
 * buffer_sz - uपूर्णांक32_t, buffer size to be allocated, octets
 * period_sz - uपूर्णांक32_t, event period size, octets
 *   This is the requested value of the period at which frontend would
 *   like to receive XENSND_EVT_CUR_POS notअगरications from the backend when
 *   stream position advances during playback/capture.
 *   It shows how many octets are expected to be played/captured beक्रमe
 *   sending such an event.
 *   If set to 0 no XENSND_EVT_CUR_POS events are sent by the backend.
 *
 * gref_directory - grant_ref_t, a reference to the first shared page
 *   describing shared buffer references. At least one page exists. If shared
 *   buffer size  (buffer_sz) exceeds what can be addressed by this single page,
 *   then reference to the next page must be supplied (see gref_dir_next_page
 *   below)
 */

काष्ठा xensnd_खोलो_req अणु
	uपूर्णांक32_t pcm_rate;
	uपूर्णांक8_t pcm_क्रमmat;
	uपूर्णांक8_t pcm_channels;
	uपूर्णांक16_t reserved;
	uपूर्णांक32_t buffer_sz;
	grant_ref_t gref_directory;
	uपूर्णांक32_t period_sz;
पूर्ण;

/*
 * Shared page क्रम XENSND_OP_OPEN buffer descriptor (gref_directory in the
 *   request) employs a list of pages, describing all pages of the shared data
 *   buffer:
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
 *   allocated at XENSND_OP_OPEN
 *
 * Number of grant_ref_t entries in the whole page directory is not
 * passed, but instead can be calculated as:
 *   num_grefs_total = (XENSND_OP_OPEN.buffer_sz + XEN_PAGE_SIZE - 1) /
 *       XEN_PAGE_SIZE
 */

काष्ठा xensnd_page_directory अणु
	grant_ref_t gref_dir_next_page;
	grant_ref_t gref[1]; /* Variable length */
पूर्ण;

/*
 *  Request बंद - बंद an खोलोed pcm stream:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                | XENSND_OP_CLOSE|    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Request पढ़ो/ग_लिखो - used क्रम पढ़ो (क्रम capture) or ग_लिखो (क्रम playback):
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |   operation    |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                              offset                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                              length                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * operation - XENSND_OP_READ क्रम पढ़ो or XENSND_OP_WRITE क्रम ग_लिखो
 */

काष्ठा xensnd_rw_req अणु
	uपूर्णांक32_t offset;
	uपूर्णांक32_t length;
पूर्ण;

/*
 * Request set/get volume - set/get channels' volume of the stream given:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |   operation    |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                              offset                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                              length                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * operation - XENSND_OP_SET_VOLUME क्रम volume set
 *   or XENSND_OP_GET_VOLUME क्रम volume get
 * Buffer passed with XENSND_OP_OPEN is used to exchange volume
 * values:
 *
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |                             channel[0]                            | 4
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             channel[i]                            | i*4
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                           channel[N - 1]                          | (N-1)*4
 * +----------------+----------------+----------------+----------------+
 *
 * N = XENSND_OP_OPEN.pcm_channels
 * i - uपूर्णांक8_t, index of a channel
 * channel[i] - sपूर्णांक32_t, volume of i-th channel
 * Volume is expressed as a चिन्हित value in steps of 0.001 dB,
 * जबतक 0 being 0 dB.
 *
 * Request mute/unmute - mute/unmute stream:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |   operation    |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                              offset                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                              length                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * operation - XENSND_OP_MUTE क्रम mute or XENSND_OP_UNMUTE क्रम unmute
 * Buffer passed with XENSND_OP_OPEN is used to exchange mute/unmute
 * values:
 *
 *                                   0                                 octet
 * +----------------+----------------+----------------+----------------+
 * |                             channel[0]                            | 4
 * +----------------+----------------+----------------+----------------+
 * +/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             channel[i]                            | i*4
 * +----------------+----------------+----------------+----------------+
 * +/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                           channel[N - 1]                          | (N-1)*4
 * +----------------+----------------+----------------+----------------+
 *
 * N = XENSND_OP_OPEN.pcm_channels
 * i - uपूर्णांक8_t, index of a channel
 * channel[i] - uपूर्णांक8_t, non-zero अगर i-th channel needs to be muted/unmuted
 *
 *------------------------------------ N.B. -----------------------------------
 *
 * The 'struct xensnd_rw_req' is also used क्रम XENSND_OP_SET_VOLUME,
 * XENSND_OP_GET_VOLUME, XENSND_OP_MUTE, XENSND_OP_UNMUTE.
 *
 * Request stream running state change - trigger PCM stream running state
 * to start, stop, छोड़ो or resume:
 *
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |   _OP_TRIGGER  |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |      type      |                     reserved                     | 12
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 16
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * type - uपूर्णांक8_t, XENSND_OP_TRIGGER_XXX value
 */

काष्ठा xensnd_trigger_req अणु
	uपूर्णांक8_t type;
पूर्ण;

/*
 * Request stream parameter ranges: request पूर्णांकervals and
 *   masks of supported ranges क्रम stream configuration values.
 *
 *   Sound device configuration क्रम a particular stream is a limited subset
 *   of the multidimensional configuration available on XenStore, e.g.
 *   once the frame rate has been selected there is a limited supported range
 *   क्रम sample rates becomes available (which might be the same set configured
 *   on XenStore or less). For example, selecting 96kHz sample rate may limit
 *   number of channels available क्रम such configuration from 4 to 2, etc.
 *   Thus, each call to XENSND_OP_HW_PARAM_QUERY may reduce configuration
 *   space making it possible to iteratively get the final stream configuration,
 *   used in XENSND_OP_OPEN request.
 *
 *   See response क्रमmat क्रम this request.
 *
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                | _HW_PARAM_QUERY|    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                     क्रमmats mask low 32-bit                       | 12
 * +----------------+----------------+----------------+----------------+
 * |                     क्रमmats mask high 32-bit                      | 16
 * +----------------+----------------+----------------+----------------+
 * |                              min rate                             | 20
 * +----------------+----------------+----------------+----------------+
 * |                              max rate                             | 24
 * +----------------+----------------+----------------+----------------+
 * |                            min channels                           | 28
 * +----------------+----------------+----------------+----------------+
 * |                            max channels                           | 32
 * +----------------+----------------+----------------+----------------+
 * |                         min buffer frames                         | 36
 * +----------------+----------------+----------------+----------------+
 * |                         max buffer frames                         | 40
 * +----------------+----------------+----------------+----------------+
 * |                         min period frames                         | 44
 * +----------------+----------------+----------------+----------------+
 * |                         max period frames                         | 48
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 52
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * क्रमmats - uपूर्णांक64_t, bit mask representing values of the parameter
 *     made as bitwise OR of (1 << XENSND_PCM_FORMAT_XXX) values
 *
 * For पूर्णांकerval parameters:
 *   min - uपूर्णांक32_t, minimum value of the parameter
 *   max - uपूर्णांक32_t, maximum value of the parameter
 *
 * Frame is defined as a product of the number of channels by the
 * number of octets per one sample.
 */

काष्ठा xensnd_query_hw_param अणु
	uपूर्णांक64_t क्रमmats;
	काष्ठा अणु
		uपूर्णांक32_t min;
		uपूर्णांक32_t max;
	पूर्ण rates;
	काष्ठा अणु
		uपूर्णांक32_t min;
		uपूर्णांक32_t max;
	पूर्ण channels;
	काष्ठा अणु
		uपूर्णांक32_t min;
		uपूर्णांक32_t max;
	पूर्ण buffer;
	काष्ठा अणु
		uपूर्णांक32_t min;
		uपूर्णांक32_t max;
	पूर्ण period;
पूर्ण;

/*
 *---------------------------------- Responses --------------------------------
 *
 * All response packets have the same length (64 octets)
 *
 * All response packets have common header:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |    operation   |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                              status                               | 8
 * +----------------+----------------+----------------+----------------+
 *
 * id - uपूर्णांक16_t, copied from the request
 * operation - uपूर्णांक8_t, XENSND_OP_* - copied from request
 * status - पूर्णांक32_t, response status, zero on success and -XEN_EXX on failure
 *
 *
 * HW parameter query response - response क्रम XENSND_OP_HW_PARAM_QUERY:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |    operation   |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                              status                               | 8
 * +----------------+----------------+----------------+----------------+
 * |                     क्रमmats mask low 32-bit                       | 12
 * +----------------+----------------+----------------+----------------+
 * |                     क्रमmats mask high 32-bit                      | 16
 * +----------------+----------------+----------------+----------------+
 * |                              min rate                             | 20
 * +----------------+----------------+----------------+----------------+
 * |                              max rate                             | 24
 * +----------------+----------------+----------------+----------------+
 * |                            min channels                           | 28
 * +----------------+----------------+----------------+----------------+
 * |                            max channels                           | 32
 * +----------------+----------------+----------------+----------------+
 * |                         min buffer frames                         | 36
 * +----------------+----------------+----------------+----------------+
 * |                         max buffer frames                         | 40
 * +----------------+----------------+----------------+----------------+
 * |                         min period frames                         | 44
 * +----------------+----------------+----------------+----------------+
 * |                         max period frames                         | 48
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 52
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * Meaning of the values in this response is the same as क्रम
 * XENSND_OP_HW_PARAM_QUERY request.
 */

/*
 *----------------------------------- Events ----------------------------------
 *
 * Events are sent via shared page allocated by the front and propagated by
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
 * Current stream position - event from back to front when stream's
 *   playback/capture position has advanced:
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |               id                |   _EVT_CUR_POS |   reserved     | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                         position low 32-bit                       | 12
 * +----------------+----------------+----------------+----------------+
 * |                         position high 32-bit                      | 16
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 64
 * +----------------+----------------+----------------+----------------+
 *
 * position - current value of stream's playback/capture position, octets
 *
 */

काष्ठा xensnd_cur_pos_evt अणु
	uपूर्णांक64_t position;
पूर्ण;

काष्ठा xensnd_req अणु
	uपूर्णांक16_t id;
	uपूर्णांक8_t operation;
	uपूर्णांक8_t reserved[5];
	जोड़ अणु
		काष्ठा xensnd_खोलो_req खोलो;
		काष्ठा xensnd_rw_req rw;
		काष्ठा xensnd_trigger_req trigger;
		काष्ठा xensnd_query_hw_param hw_param;
		uपूर्णांक8_t reserved[56];
	पूर्ण op;
पूर्ण;

काष्ठा xensnd_resp अणु
	uपूर्णांक16_t id;
	uपूर्णांक8_t operation;
	uपूर्णांक8_t reserved;
	पूर्णांक32_t status;
	जोड़ अणु
		काष्ठा xensnd_query_hw_param hw_param;
		uपूर्णांक8_t reserved1[56];
	पूर्ण resp;
पूर्ण;

काष्ठा xensnd_evt अणु
	uपूर्णांक16_t id;
	uपूर्णांक8_t type;
	uपूर्णांक8_t reserved[5];
	जोड़ अणु
		काष्ठा xensnd_cur_pos_evt cur_pos;
		uपूर्णांक8_t reserved[56];
	पूर्ण op;
पूर्ण;

DEFINE_RING_TYPES(xen_sndअगर, काष्ठा xensnd_req, काष्ठा xensnd_resp);

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

काष्ठा xensnd_event_page अणु
	uपूर्णांक32_t in_cons;
	uपूर्णांक32_t in_prod;
	uपूर्णांक8_t reserved[56];
पूर्ण;

#घोषणा XENSND_EVENT_PAGE_SIZE XEN_PAGE_SIZE
#घोषणा XENSND_IN_RING_OFFS (माप(काष्ठा xensnd_event_page))
#घोषणा XENSND_IN_RING_SIZE (XENSND_EVENT_PAGE_SIZE - XENSND_IN_RING_OFFS)
#घोषणा XENSND_IN_RING_LEN (XENSND_IN_RING_SIZE / माप(काष्ठा xensnd_evt))
#घोषणा XENSND_IN_RING(page) \
	((काष्ठा xensnd_evt *)((अक्षर *)(page) + XENSND_IN_RING_OFFS))
#घोषणा XENSND_IN_RING_REF(page, idx) \
	(XENSND_IN_RING((page))[(idx) % XENSND_IN_RING_LEN])

#पूर्ण_अगर /* __XEN_PUBLIC_IO_SNDIF_H__ */
