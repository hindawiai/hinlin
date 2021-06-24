<शैली गुरु>
/*
 * dvb_ca.h: generic DVB functions क्रम EN50221 CA पूर्णांकerfaces
 *
 * Copyright (C) 2004 Andrew de Quincey
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 2.1
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License क्रम more details.
 */

#अगर_अघोषित _DVB_CA_EN50221_H_
#घोषणा _DVB_CA_EN50221_H_

#समावेश <linux/list.h>
#समावेश <linux/dvb/ca.h>

#समावेश <media/dvbdev.h>

#घोषणा DVB_CA_EN50221_POLL_CAM_PRESENT	1
#घोषणा DVB_CA_EN50221_POLL_CAM_CHANGED	2
#घोषणा DVB_CA_EN50221_POLL_CAM_READY		4

#घोषणा DVB_CA_EN50221_FLAG_IRQ_CAMCHANGE	1
#घोषणा DVB_CA_EN50221_FLAG_IRQ_FR		2
#घोषणा DVB_CA_EN50221_FLAG_IRQ_DA		4

#घोषणा DVB_CA_EN50221_CAMCHANGE_REMOVED		0
#घोषणा DVB_CA_EN50221_CAMCHANGE_INSERTED		1

/**
 * काष्ठा dvb_ca_en50221- Structure describing a CA पूर्णांकerface
 *
 * @owner:		the module owning this काष्ठाure
 * @पढ़ो_attribute_mem:	function क्रम पढ़ोing attribute memory on the CAM
 * @ग_लिखो_attribute_mem: function क्रम writing attribute memory on the CAM
 * @पढ़ो_cam_control:	function क्रम पढ़ोing the control पूर्णांकerface on the CAM
 * @ग_लिखो_cam_control:	function क्रम पढ़ोing the control पूर्णांकerface on the CAM
 * @पढ़ो_data:		function क्रम पढ़ोing data (block mode)
 * @ग_लिखो_data:		function क्रम writing data (block mode)
 * @slot_reset:		function to reset the CAM slot
 * @slot_shutकरोwn:	function to shutकरोwn a CAM slot
 * @slot_ts_enable:	function to enable the Transport Stream on a CAM slot
 * @poll_slot_status:	function to poll slot status. Only necessary अगर
 *			DVB_CA_FLAG_EN50221_IRQ_CAMCHANGE is not set.
 * @data:		निजी data, used by caller.
 * @निजी:		Opaque data used by the dvb_ca core. Do not modअगरy!
 *
 * NOTE: the पढ़ो_*, ग_लिखो_* and poll_slot_status functions will be
 * called क्रम dअगरferent slots concurrently and need to use locks where
 * and अगर appropriate. There will be no concurrent access to one slot.
 */
काष्ठा dvb_ca_en50221 अणु
	काष्ठा module *owner;

	पूर्णांक (*पढ़ो_attribute_mem)(काष्ठा dvb_ca_en50221 *ca,
				  पूर्णांक slot, पूर्णांक address);
	पूर्णांक (*ग_लिखो_attribute_mem)(काष्ठा dvb_ca_en50221 *ca,
				   पूर्णांक slot, पूर्णांक address, u8 value);

	पूर्णांक (*पढ़ो_cam_control)(काष्ठा dvb_ca_en50221 *ca,
				पूर्णांक slot, u8 address);
	पूर्णांक (*ग_लिखो_cam_control)(काष्ठा dvb_ca_en50221 *ca,
				 पूर्णांक slot, u8 address, u8 value);

	पूर्णांक (*पढ़ो_data)(काष्ठा dvb_ca_en50221 *ca,
			 पूर्णांक slot, u8 *ebuf, पूर्णांक ecount);
	पूर्णांक (*ग_लिखो_data)(काष्ठा dvb_ca_en50221 *ca,
			  पूर्णांक slot, u8 *ebuf, पूर्णांक ecount);

	पूर्णांक (*slot_reset)(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot);
	पूर्णांक (*slot_shutकरोwn)(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot);
	पूर्णांक (*slot_ts_enable)(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot);

	पूर्णांक (*poll_slot_status)(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot, पूर्णांक खोलो);

	व्योम *data;

	व्योम *निजी;
पूर्ण;

/*
 * Functions क्रम reporting IRQ events
 */

/**
 * dvb_ca_en50221_camchange_irq - A CAMCHANGE IRQ has occurred.
 *
 * @pubca: CA instance.
 * @slot: Slot concerned.
 * @change_type: One of the DVB_CA_CAMCHANGE_* values
 */
व्योम dvb_ca_en50221_camchange_irq(काष्ठा dvb_ca_en50221 *pubca, पूर्णांक slot,
				  पूर्णांक change_type);

/**
 * dvb_ca_en50221_camपढ़ोy_irq - A CAMREADY IRQ has occurred.
 *
 * @pubca: CA instance.
 * @slot: Slot concerned.
 */
व्योम dvb_ca_en50221_camपढ़ोy_irq(काष्ठा dvb_ca_en50221 *pubca, पूर्णांक slot);

/**
 * dvb_ca_en50221_frda_irq - An FR or a DA IRQ has occurred.
 *
 * @ca: CA instance.
 * @slot: Slot concerned.
 */
व्योम dvb_ca_en50221_frda_irq(काष्ठा dvb_ca_en50221 *ca, पूर्णांक slot);

/*
 * Initialisation/shutकरोwn functions
 */

/**
 * dvb_ca_en50221_init - Initialise a new DVB CA device.
 *
 * @dvb_adapter: DVB adapter to attach the new CA device to.
 * @ca: The dvb_ca instance.
 * @flags: Flags describing the CA device (DVB_CA_EN50221_FLAG_*).
 * @slot_count: Number of slots supported.
 *
 * @वापस 0 on success, nonzero on failure
 */
पूर्णांक dvb_ca_en50221_init(काष्ठा dvb_adapter *dvb_adapter,
			काष्ठा dvb_ca_en50221 *ca, पूर्णांक flags,
			       पूर्णांक slot_count);

/**
 * dvb_ca_en50221_release - Release a DVB CA device.
 *
 * @ca: The associated dvb_ca instance.
 */
व्योम dvb_ca_en50221_release(काष्ठा dvb_ca_en50221 *ca);

#पूर्ण_अगर
