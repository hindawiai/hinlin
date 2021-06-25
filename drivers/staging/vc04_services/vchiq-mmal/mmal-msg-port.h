<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Broadcom BM2835 V4L2 driver
 *
 * Copyright तऊ 2013 Raspberry Pi (Trading) Ltd.
 *
 * Authors: Vincent Sanders @ Collabora
 *          Dave Stevenson @ Broadcom
 *		(now dave.stevenson@raspberrypi.org)
 *          Simon Mellor @ Broadcom
 *          Luke Diamand @ Broadcom
 */

/* MMAL_PORT_TYPE_T */
क्रमागत mmal_port_type अणु
	MMAL_PORT_TYPE_UNKNOWN = 0,	/* Unknown port type */
	MMAL_PORT_TYPE_CONTROL,		/* Control port */
	MMAL_PORT_TYPE_INPUT,		/* Input port */
	MMAL_PORT_TYPE_OUTPUT,		/* Output port */
	MMAL_PORT_TYPE_CLOCK,		/* Clock port */
पूर्ण;

/* The port is pass-through and करोesn't need buffer headers allocated */
#घोषणा MMAL_PORT_CAPABILITY_PASSTHROUGH                       0x01
/*
 *The port wants to allocate the buffer payloads.
 * This संकेतs a preference that payload allocation should be करोne
 * on this port क्रम efficiency reasons.
 */
#घोषणा MMAL_PORT_CAPABILITY_ALLOCATION                        0x02
/*
 * The port supports क्रमmat change events.
 * This applies to input ports and is used to let the client know
 * whether the port supports being reconfigured via a क्रमmat
 * change event (i.e. without having to disable the port).
 */
#घोषणा MMAL_PORT_CAPABILITY_SUPPORTS_EVENT_FORMAT_CHANGE      0x04

/*
 * mmal port काष्ठाure (MMAL_PORT_T)
 *
 * most elements are inक्रमmational only, the poपूर्णांकer values क्रम
 * पूर्णांकerogation messages are generally provided as additional
 * काष्ठाures within the message. When used to set values only the
 * buffer_num, buffer_size and userdata parameters are writable.
 */
काष्ठा mmal_port अणु
	u32 priv;	/* Private member used by the framework */
	u32 name;	/* Port name. Used क्रम debugging purposes (RO) */

	u32 type;	/* Type of the port (RO) क्रमागत mmal_port_type */
	u16 index;	/* Index of the port in its type list (RO) */
	u16 index_all;	/* Index of the port in the list of all ports (RO) */

	u32 is_enabled;	/* Indicates whether the port is enabled or not (RO) */
	u32 क्रमmat;	/* Format of the elementary stream */

	u32 buffer_num_min;	/* Minimum number of buffers the port
				 *   requires (RO).  This is set by the
				 *   component.
				 */

	u32 buffer_size_min;	/* Minimum size of buffers the port
				 * requires (RO).  This is set by the
				 * component.
				 */

	u32 buffer_alignment_min;/* Minimum alignment requirement क्रम
				  * the buffers (RO).  A value of
				  * zero means no special alignment
				  * requirements.  This is set by the
				  * component.
				  */

	u32 buffer_num_recommended;	/* Number of buffers the port
					 * recommends क्रम optimal
					 * perक्रमmance (RO).  A value of
					 * zero means no special
					 * recommendation.  This is set
					 * by the component.
					 */

	u32 buffer_size_recommended;	/* Size of buffers the port
					 * recommends क्रम optimal
					 * perक्रमmance (RO).  A value of
					 * zero means no special
					 * recommendation.  This is set
					 * by the component.
					 */

	u32 buffer_num;	/* Actual number of buffers the port will use.
			 * This is set by the client.
			 */

	u32 buffer_size; /* Actual maximum size of the buffers that
			  * will be sent to the port. This is set by
			  * the client.
			  */

	u32 component;	/* Component this port beदीर्घs to (Read Only) */

	u32 userdata;	/* Field reserved क्रम use by the client */

	u32 capabilities;	/* Flags describing the capabilities of a
				 * port (RO).  Bitwise combination of \लef
				 * portcapabilities "Port capabilities"
				 * values.
				 */
पूर्ण;
