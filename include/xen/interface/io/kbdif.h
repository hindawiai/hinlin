<शैली गुरु>
/*
 * kbdअगर.h -- Xen भव keyboard/mouse
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
 * Copyright (C) 2005 Anthony Liguori <aliguori@us.ibm.com>
 * Copyright (C) 2006 Red Hat, Inc., Markus Armbruster <armbru@redhat.com>
 */

#अगर_अघोषित __XEN_PUBLIC_IO_KBDIF_H__
#घोषणा __XEN_PUBLIC_IO_KBDIF_H__

/*
 *****************************************************************************
 *                     Feature and Parameter Negotiation
 *****************************************************************************
 *
 * The two halves of a para-भव driver utilize nodes within
 * XenStore to communicate capabilities and to negotiate operating parameters.
 * This section क्रमागतerates these nodes which reside in the respective front and
 * backend portions of XenStore, following XenBus convention.
 *
 * All data in XenStore is stored as strings.  Nodes specअगरying numeric
 * values are encoded in decimal. Integer value ranges listed below are
 * expressed as fixed sized पूर्णांकeger types capable of storing the conversion
 * of a properly क्रमmated node string, without loss of inक्रमmation.
 *
 *****************************************************************************
 *                            Backend XenBus Nodes
 *****************************************************************************
 *
 *---------------------------- Features supported ----------------------------
 *
 * Capable backend advertises supported features by publishing
 * corresponding entries in XenStore and माला_दो 1 as the value of the entry.
 * If a feature is not supported then 0 must be set or feature entry omitted.
 *
 * feature-disable-keyboard
 *      Values:         <uपूर्णांक>
 *
 *      If there is no need to expose a भव keyboard device by the
 *      frontend then this must be set to 1.
 *
 * feature-disable-poपूर्णांकer
 *      Values:         <uपूर्णांक>
 *
 *      If there is no need to expose a भव poपूर्णांकer device by the
 *      frontend then this must be set to 1.
 *
 * feature-असल-poपूर्णांकer
 *      Values:         <uपूर्णांक>
 *
 *      Backends, which support reporting of असलolute coordinates क्रम poपूर्णांकer
 *      device should set this to 1.
 *
 * feature-multi-touch
 *      Values:         <uपूर्णांक>
 *
 *      Backends, which support reporting of multi-touch events
 *      should set this to 1.
 *
 * feature-raw-poपूर्णांकer
 *      Values:        <uपूर्णांक>
 *
 *      Backends, which support reporting raw (unscaled) असलolute coordinates
 *      क्रम poपूर्णांकer devices should set this to 1. Raw (unscaled) values have
 *      a range of [0, 0x7fff].
 *
 *-----------------------  Device Instance Parameters ------------------------
 *
 * unique-id
 *      Values:         <string>
 *
 *      After device instance initialization it is asचिन्हित a unique ID,
 *      so every instance of the frontend can be identअगरied by the backend
 *      by this ID. This can be UUID or such.
 *
 *------------------------- Poपूर्णांकer Device Parameters ------------------------
 *
 * width
 *      Values:         <uपूर्णांक>
 *
 *      Maximum X coordinate (width) to be used by the frontend
 *      जबतक reporting input events, pixels, [0; UINT32_MAX].
 *
 * height
 *      Values:         <uपूर्णांक>
 *
 *      Maximum Y coordinate (height) to be used by the frontend
 *      जबतक reporting input events, pixels, [0; UINT32_MAX].
 *
 *----------------------- Multi-touch Device Parameters ----------------------
 *
 * multi-touch-num-contacts
 *      Values:         <uपूर्णांक>
 *
 *      Number of simultaneous touches reported.
 *
 * multi-touch-width
 *      Values:         <uपूर्णांक>
 *
 *      Width of the touch area to be used by the frontend
 *      जबतक reporting input events, pixels, [0; UINT32_MAX].
 *
 * multi-touch-height
 *      Values:         <uपूर्णांक>
 *
 *      Height of the touch area to be used by the frontend
 *      जबतक reporting input events, pixels, [0; UINT32_MAX].
 *
 *****************************************************************************
 *                            Frontend XenBus Nodes
 *****************************************************************************
 *
 *------------------------------ Feature request -----------------------------
 *
 * Capable frontend requests features from backend via setting corresponding
 * entries to 1 in XenStore. Requests क्रम features not advertised as supported
 * by the backend have no effect.
 *
 * request-असल-poपूर्णांकer
 *      Values:         <uपूर्णांक>
 *
 *      Request backend to report असलolute poपूर्णांकer coordinates
 *      (XENKBD_TYPE_POS) instead of relative ones (XENKBD_TYPE_MOTION).
 *
 * request-multi-touch
 *      Values:         <uपूर्णांक>
 *
 *      Request backend to report multi-touch events.
 *
 * request-raw-poपूर्णांकer
 *      Values:         <uपूर्णांक>
 *
 *      Request backend to report raw unscaled असलolute poपूर्णांकer coordinates.
 *      This option is only valid अगर request-असल-poपूर्णांकer is also set.
 *      Raw unscaled coordinates have the range [0, 0x7fff]
 *
 *----------------------- Request Transport Parameters -----------------------
 *
 * event-channel
 *      Values:         <uपूर्णांक>
 *
 *      The identअगरier of the Xen event channel used to संकेत activity
 *      in the ring buffer.
 *
 * page-gref
 *      Values:         <uपूर्णांक>
 *
 *      The Xen grant reference granting permission क्रम the backend to map
 *      a sole page in a single page sized event ring buffer.
 *
 * page-ref
 *      Values:         <uपूर्णांक>
 *
 *      OBSOLETE, not recommended क्रम use.
 *      PFN of the shared page.
 */

/*
 * EVENT CODES.
 */

#घोषणा XENKBD_TYPE_MOTION		1
#घोषणा XENKBD_TYPE_RESERVED		2
#घोषणा XENKBD_TYPE_KEY			3
#घोषणा XENKBD_TYPE_POS			4
#घोषणा XENKBD_TYPE_MTOUCH		5

/* Multi-touch event sub-codes */

#घोषणा XENKBD_MT_EV_DOWN		0
#घोषणा XENKBD_MT_EV_UP			1
#घोषणा XENKBD_MT_EV_MOTION		2
#घोषणा XENKBD_MT_EV_SYN		3
#घोषणा XENKBD_MT_EV_SHAPE		4
#घोषणा XENKBD_MT_EV_ORIENT		5

/*
 * CONSTANTS, XENSTORE FIELD AND PATH NAME STRINGS, HELPERS.
 */

#घोषणा XENKBD_DRIVER_NAME		"vkbd"

#घोषणा XENKBD_FIELD_FEAT_DSBL_KEYBRD	"feature-disable-keyboard"
#घोषणा XENKBD_FIELD_FEAT_DSBL_POINTER	"feature-disable-pointer"
#घोषणा XENKBD_FIELD_FEAT_ABS_POINTER	"feature-abs-pointer"
#घोषणा XENKBD_FIELD_FEAT_RAW_POINTER	"feature-raw-pointer"
#घोषणा XENKBD_FIELD_FEAT_MTOUCH	"feature-multi-touch"
#घोषणा XENKBD_FIELD_REQ_ABS_POINTER	"request-abs-pointer"
#घोषणा XENKBD_FIELD_REQ_RAW_POINTER	"request-raw-pointer"
#घोषणा XENKBD_FIELD_REQ_MTOUCH		"request-multi-touch"
#घोषणा XENKBD_FIELD_RING_GREF		"page-gref"
#घोषणा XENKBD_FIELD_EVT_CHANNEL	"event-channel"
#घोषणा XENKBD_FIELD_WIDTH		"width"
#घोषणा XENKBD_FIELD_HEIGHT		"height"
#घोषणा XENKBD_FIELD_MT_WIDTH		"multi-touch-width"
#घोषणा XENKBD_FIELD_MT_HEIGHT		"multi-touch-height"
#घोषणा XENKBD_FIELD_MT_NUM_CONTACTS	"multi-touch-num-contacts"
#घोषणा XENKBD_FIELD_UNIQUE_ID		"unique-id"

/* OBSOLETE, not recommended क्रम use */
#घोषणा XENKBD_FIELD_RING_REF		"page-ref"

/*
 *****************************************************************************
 * Description of the protocol between frontend and backend driver.
 *****************************************************************************
 *
 * The two halves of a Para-भव driver communicate with
 * each other using a shared page and an event channel.
 * Shared page contains a ring with event काष्ठाures.
 *
 * All reserved fields in the काष्ठाures below must be 0.
 *
 *****************************************************************************
 *                           Backend to frontend events
 *****************************************************************************
 *
 * Frontends should ignore unknown in events.
 * All event packets have the same length (40 octets)
 * All event packets have common header:
 *
 *          0         octet
 * +-----------------+
 * |       type      |
 * +-----------------+
 * type - uपूर्णांक8_t, event code, XENKBD_TYPE_???
 *
 *
 * Poपूर्णांकer relative movement event
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MOTION  |                     reserved                     | 4
 * +----------------+----------------+----------------+----------------+
 * |                               rel_x                               | 8
 * +----------------+----------------+----------------+----------------+
 * |                               rel_y                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                               rel_z                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * rel_x - पूर्णांक32_t, relative X motion
 * rel_y - पूर्णांक32_t, relative Y motion
 * rel_z - पूर्णांक32_t, relative Z motion (wheel)
 */

काष्ठा xenkbd_motion अणु
	uपूर्णांक8_t type;
	पूर्णांक32_t rel_x;
	पूर्णांक32_t rel_y;
	पूर्णांक32_t rel_z;
पूर्ण;

/*
 * Key event (includes poपूर्णांकer buttons)
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_KEY     |     pressed    |            reserved             | 4
 * +----------------+----------------+----------------+----------------+
 * |                              keycode                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 12
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * pressed - uपूर्णांक8_t, 1 अगर pressed; 0 otherwise
 * keycode - uपूर्णांक32_t, KEY_* from linux/input.h
 */

काष्ठा xenkbd_key अणु
	uपूर्णांक8_t type;
	uपूर्णांक8_t pressed;
	uपूर्णांक32_t keycode;
पूर्ण;

/*
 * Poपूर्णांकer असलolute position event
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_POS     |                     reserved                     | 4
 * +----------------+----------------+----------------+----------------+
 * |                               असल_x                               | 8
 * +----------------+----------------+----------------+----------------+
 * |                               असल_y                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                               rel_z                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * असल_x - पूर्णांक32_t, असलolute X position (in FB pixels)
 * असल_y - पूर्णांक32_t, असलolute Y position (in FB pixels)
 * rel_z - पूर्णांक32_t, relative Z motion (wheel)
 */

काष्ठा xenkbd_position अणु
	uपूर्णांक8_t type;
	पूर्णांक32_t असल_x;
	पूर्णांक32_t असल_y;
	पूर्णांक32_t rel_z;
पूर्ण;

/*
 * Multi-touch event and its sub-types
 *
 * All multi-touch event packets have common header:
 *
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MTOUCH  |   event_type   |   contact_id   |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 *
 * event_type - unt8_t, multi-touch event sub-type, XENKBD_MT_EV_???
 * contact_id - unt8_t, ID of the contact
 *
 * Touch पूर्णांकeractions can consist of one or more contacts.
 * For each contact, a series of events is generated, starting
 * with a करोwn event, followed by zero or more motion events,
 * and ending with an up event. Events relating to the same
 * contact poपूर्णांक can be identअगरied by the ID of the sequence: contact ID.
 * Contact ID may be reused after XENKBD_MT_EV_UP event and
 * is in the [0; XENKBD_FIELD_NUM_CONTACTS - 1] range.
 *
 * For further inक्रमmation please refer to करोcumentation on Wayland [1],
 * Linux [2] and Winकरोws [3] multi-touch support.
 *
 * [1] https://cgit.मुक्तdesktop.org/wayland/wayland/tree/protocol/wayland.xml
 * [2] https://www.kernel.org/करोc/Documentation/input/multi-touch-protocol.rst
 * [3] https://msdn.microsoft.com/en-us/library/jj151564(v=vs.85).aspx
 *
 *
 * Multi-touch करोwn event - sent when a new touch is made: touch is asचिन्हित
 * a unique contact ID, sent with this and consequent events related
 * to this touch.
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MTOUCH  |   _MT_EV_DOWN  |   contact_id   |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                               असल_x                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                               असल_y                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * असल_x - पूर्णांक32_t, असलolute X position, in pixels
 * असल_y - पूर्णांक32_t, असलolute Y position, in pixels
 *
 * Multi-touch contact release event
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MTOUCH  |  _MT_EV_UP     |   contact_id   |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * Multi-touch motion event
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MTOUCH  |  _MT_EV_MOTION |   contact_id   |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                               असल_x                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                               असल_y                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * असल_x - पूर्णांक32_t, असलolute X position, in pixels,
 * असल_y - पूर्णांक32_t, असलolute Y position, in pixels,
 *
 * Multi-touch input synchronization event - shows end of a set of events
 * which logically beदीर्घ together.
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MTOUCH  |  _MT_EV_SYN    |   contact_id   |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * Multi-touch shape event - touch poपूर्णांक's shape has changed its shape.
 * Shape is approximated by an ellipse through the major and minor axis
 * lengths: major is the दीर्घer diameter of the ellipse and minor is the
 * लघुer one. Center of the ellipse is reported via
 * XENKBD_MT_EV_DOWN/XENKBD_MT_EV_MOTION events.
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MTOUCH  |  _MT_EV_SHAPE  |   contact_id   |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |                               major                               | 12
 * +----------------+----------------+----------------+----------------+
 * |                               minor                               | 16
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 20
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * major - unt32_t, length of the major axis, pixels
 * minor - unt32_t, length of the minor axis, pixels
 *
 * Multi-touch orientation event - touch poपूर्णांक's shape has changed
 * its orientation: calculated as a घड़ीwise angle between the major axis
 * of the ellipse and positive Y axis in degrees, [-180; +180].
 *         0                1                 2               3        octet
 * +----------------+----------------+----------------+----------------+
 * |  _TYPE_MTOUCH  |  _MT_EV_ORIENT |   contact_id   |    reserved    | 4
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 8
 * +----------------+----------------+----------------+----------------+
 * |           orientation           |            reserved             | 12
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 16
 * +----------------+----------------+----------------+----------------+
 * |/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/\/|
 * +----------------+----------------+----------------+----------------+
 * |                             reserved                              | 40
 * +----------------+----------------+----------------+----------------+
 *
 * orientation - पूर्णांक16_t, घड़ीwise angle of the major axis
 */

काष्ठा xenkbd_mtouch अणु
	uपूर्णांक8_t type;			/* XENKBD_TYPE_MTOUCH */
	uपूर्णांक8_t event_type;		/* XENKBD_MT_EV_??? */
	uपूर्णांक8_t contact_id;
	uपूर्णांक8_t reserved[5];		/* reserved क्रम the future use */
	जोड़ अणु
		काष्ठा अणु
			पूर्णांक32_t असल_x;	/* असलolute X position, pixels */
			पूर्णांक32_t असल_y;	/* असलolute Y position, pixels */
		पूर्ण pos;
		काष्ठा अणु
			uपूर्णांक32_t major;	/* length of the major axis, pixels */
			uपूर्णांक32_t minor;	/* length of the minor axis, pixels */
		पूर्ण shape;
		पूर्णांक16_t orientation;	/* घड़ीwise angle of the major axis */
	पूर्ण u;
पूर्ण;

#घोषणा XENKBD_IN_EVENT_SIZE 40

जोड़ xenkbd_in_event अणु
	uपूर्णांक8_t type;
	काष्ठा xenkbd_motion motion;
	काष्ठा xenkbd_key key;
	काष्ठा xenkbd_position pos;
	काष्ठा xenkbd_mtouch mtouch;
	अक्षर pad[XENKBD_IN_EVENT_SIZE];
पूर्ण;

/*
 *****************************************************************************
 *                            Frontend to backend events
 *****************************************************************************
 *
 * Out events may be sent only when requested by backend, and receipt
 * of an unknown out event is an error.
 * No out events currently defined.

 * All event packets have the same length (40 octets)
 * All event packets have common header:
 *          0         octet
 * +-----------------+
 * |       type      |
 * +-----------------+
 * type - uपूर्णांक8_t, event code
 */

#घोषणा XENKBD_OUT_EVENT_SIZE 40

जोड़ xenkbd_out_event अणु
	uपूर्णांक8_t type;
	अक्षर pad[XENKBD_OUT_EVENT_SIZE];
पूर्ण;

/*
 *****************************************************************************
 *                            Shared page
 *****************************************************************************
 */

#घोषणा XENKBD_IN_RING_SIZE 2048
#घोषणा XENKBD_IN_RING_LEN (XENKBD_IN_RING_SIZE / XENKBD_IN_EVENT_SIZE)
#घोषणा XENKBD_IN_RING_OFFS 1024
#घोषणा XENKBD_IN_RING(page) \
	((जोड़ xenkbd_in_event *)((अक्षर *)(page) + XENKBD_IN_RING_OFFS))
#घोषणा XENKBD_IN_RING_REF(page, idx) \
	(XENKBD_IN_RING((page))[(idx) % XENKBD_IN_RING_LEN])

#घोषणा XENKBD_OUT_RING_SIZE 1024
#घोषणा XENKBD_OUT_RING_LEN (XENKBD_OUT_RING_SIZE / XENKBD_OUT_EVENT_SIZE)
#घोषणा XENKBD_OUT_RING_OFFS (XENKBD_IN_RING_OFFS + XENKBD_IN_RING_SIZE)
#घोषणा XENKBD_OUT_RING(page) \
	((जोड़ xenkbd_out_event *)((अक्षर *)(page) + XENKBD_OUT_RING_OFFS))
#घोषणा XENKBD_OUT_RING_REF(page, idx) \
	(XENKBD_OUT_RING((page))[(idx) % XENKBD_OUT_RING_LEN])

काष्ठा xenkbd_page अणु
	uपूर्णांक32_t in_cons, in_prod;
	uपूर्णांक32_t out_cons, out_prod;
पूर्ण;

#पूर्ण_अगर /* __XEN_PUBLIC_IO_KBDIF_H__ */
