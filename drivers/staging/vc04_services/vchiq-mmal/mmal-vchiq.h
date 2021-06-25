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
 *
 * MMAL पूर्णांकerface to VCHIQ message passing
 */

#अगर_अघोषित MMAL_VCHIQ_H
#घोषणा MMAL_VCHIQ_H

#समावेश "mmal-common.h"
#समावेश "mmal-msg-format.h"

#घोषणा MAX_PORT_COUNT 4

/* Maximum size of the क्रमmat extradata. */
#घोषणा MMAL_FORMAT_EXTRADATA_MAX_SIZE 128

काष्ठा vchiq_mmal_instance;

क्रमागत vchiq_mmal_es_type अणु
	MMAL_ES_TYPE_UNKNOWN,     /**< Unknown elementary stream type */
	MMAL_ES_TYPE_CONTROL,     /**< Elementary stream of control commands */
	MMAL_ES_TYPE_AUDIO,       /**< Audio elementary stream */
	MMAL_ES_TYPE_VIDEO,       /**< Video elementary stream */
	MMAL_ES_TYPE_SUBPICTURE   /**< Sub-picture elementary stream */
पूर्ण;

काष्ठा vchiq_mmal_port_buffer अणु
	अचिन्हित पूर्णांक num; /* number of buffers */
	u32 size; /* size of buffers */
	u32 alignment; /* alignment of buffers */
पूर्ण;

काष्ठा vchiq_mmal_port;

प्रकार व्योम (*vchiq_mmal_buffer_cb)(
		काष्ठा vchiq_mmal_instance  *instance,
		काष्ठा vchiq_mmal_port *port,
		पूर्णांक status, काष्ठा mmal_buffer *buffer);

काष्ठा vchiq_mmal_port अणु
	u32 enabled:1;
	u32 handle;
	u32 type; /* port type, cached to use on port info set */
	u32 index; /* port index, cached to use on port info set */

	/* component port beदीर्घs to, allows simple deref */
	काष्ठा vchiq_mmal_component *component;

	काष्ठा vchiq_mmal_port *connected; /* port connected to */

	/* buffer info */
	काष्ठा vchiq_mmal_port_buffer minimum_buffer;
	काष्ठा vchiq_mmal_port_buffer recommended_buffer;
	काष्ठा vchiq_mmal_port_buffer current_buffer;

	/* stream क्रमmat */
	काष्ठा mmal_es_क्रमmat_local क्रमmat;
	/* elementary stream क्रमmat */
	जोड़ mmal_es_specअगरic_क्रमmat es;

	/* data buffers to fill */
	काष्ठा list_head buffers;
	/* lock to serialise adding and removing buffers from list */
	spinlock_t slock;

	/* Count of buffers the VPU has yet to वापस */
	atomic_t buffers_with_vpu;
	/* callback on buffer completion */
	vchiq_mmal_buffer_cb buffer_cb;
	/* callback context */
	व्योम *cb_ctx;
पूर्ण;

काष्ठा vchiq_mmal_component अणु
	u32 in_use:1;
	u32 enabled:1;
	u32 handle;  /* VideoCore handle क्रम component */
	u32 inमाला_दो;  /* Number of input ports */
	u32 outमाला_दो; /* Number of output ports */
	u32 घड़ीs;  /* Number of घड़ी ports */
	काष्ठा vchiq_mmal_port control; /* control port */
	काष्ठा vchiq_mmal_port input[MAX_PORT_COUNT]; /* input ports */
	काष्ठा vchiq_mmal_port output[MAX_PORT_COUNT]; /* output ports */
	काष्ठा vchiq_mmal_port घड़ी[MAX_PORT_COUNT]; /* घड़ी ports */
	u32 client_component;	/* Used to ref back to client काष्ठा */
पूर्ण;

पूर्णांक vchiq_mmal_init(काष्ठा vchiq_mmal_instance **out_instance);
पूर्णांक vchiq_mmal_finalise(काष्ठा vchiq_mmal_instance *instance);

/* Initialise a mmal component and its ports
 *
 */
पूर्णांक vchiq_mmal_component_init(
		काष्ठा vchiq_mmal_instance *instance,
		स्थिर अक्षर *name,
		काष्ठा vchiq_mmal_component **component_out);

पूर्णांक vchiq_mmal_component_finalise(
		काष्ठा vchiq_mmal_instance *instance,
		काष्ठा vchiq_mmal_component *component);

पूर्णांक vchiq_mmal_component_enable(
		काष्ठा vchiq_mmal_instance *instance,
		काष्ठा vchiq_mmal_component *component);

पूर्णांक vchiq_mmal_component_disable(
		काष्ठा vchiq_mmal_instance *instance,
		काष्ठा vchiq_mmal_component *component);

/* enable a mmal port
 *
 * enables a port and अगर a buffer callback provided enque buffer
 * headers as appropriate क्रम the port.
 */
पूर्णांक vchiq_mmal_port_enable(
		काष्ठा vchiq_mmal_instance *instance,
		काष्ठा vchiq_mmal_port *port,
		vchiq_mmal_buffer_cb buffer_cb);

/* disable a port
 *
 * disable a port will dequeue any pending buffers
 */
पूर्णांक vchiq_mmal_port_disable(काष्ठा vchiq_mmal_instance *instance,
			    काष्ठा vchiq_mmal_port *port);

पूर्णांक vchiq_mmal_port_parameter_set(काष्ठा vchiq_mmal_instance *instance,
				  काष्ठा vchiq_mmal_port *port,
				  u32 parameter,
				  व्योम *value,
				  u32 value_size);

पूर्णांक vchiq_mmal_port_parameter_get(काष्ठा vchiq_mmal_instance *instance,
				  काष्ठा vchiq_mmal_port *port,
				  u32 parameter,
				  व्योम *value,
				  u32 *value_size);

पूर्णांक vchiq_mmal_port_set_क्रमmat(काष्ठा vchiq_mmal_instance *instance,
			       काष्ठा vchiq_mmal_port *port);

पूर्णांक vchiq_mmal_port_connect_tunnel(काष्ठा vchiq_mmal_instance *instance,
				   काष्ठा vchiq_mmal_port *src,
				   काष्ठा vchiq_mmal_port *dst);

पूर्णांक vchiq_mmal_version(काष्ठा vchiq_mmal_instance *instance,
		       u32 *major_out,
		       u32 *minor_out);

पूर्णांक vchiq_mmal_submit_buffer(काष्ठा vchiq_mmal_instance *instance,
			     काष्ठा vchiq_mmal_port *port,
			     काष्ठा mmal_buffer *buf);

पूर्णांक mmal_vchi_buffer_init(काष्ठा vchiq_mmal_instance *instance,
			  काष्ठा mmal_buffer *buf);
पूर्णांक mmal_vchi_buffer_cleanup(काष्ठा mmal_buffer *buf);
#पूर्ण_अगर /* MMAL_VCHIQ_H */
