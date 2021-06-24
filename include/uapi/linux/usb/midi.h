<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/*
 * <linux/usb/midi.h> -- USB MIDI definitions.
 *
 * Copyright (C) 2006 Thumtronics Pty Ltd.
 * Developed क्रम Thumtronics by Grey Innovation
 * Ben Williamson <ben.williamson@greyinnovation.com>
 *
 * This software is distributed under the terms of the GNU General Public
 * License ("GPL") version 2, as published by the Free Software Foundation.
 *
 * This file holds USB स्थिरants and काष्ठाures defined
 * by the USB Device Class Definition क्रम MIDI Devices.
 * Comments below reference relevant sections of that करोcument:
 *
 * http://www.usb.org/developers/devclass_करोcs/midi10.pdf
 */

#अगर_अघोषित __LINUX_USB_MIDI_H
#घोषणा __LINUX_USB_MIDI_H

#समावेश <linux/types.h>

/* A.1  MS Class-Specअगरic Interface Descriptor Subtypes */
#घोषणा USB_MS_HEADER		0x01
#घोषणा USB_MS_MIDI_IN_JACK	0x02
#घोषणा USB_MS_MIDI_OUT_JACK	0x03
#घोषणा USB_MS_ELEMENT		0x04

/* A.2  MS Class-Specअगरic Endpoपूर्णांक Descriptor Subtypes */
#घोषणा USB_MS_GENERAL		0x01

/* A.3  MS MIDI IN and OUT Jack Types */
#घोषणा USB_MS_EMBEDDED		0x01
#घोषणा USB_MS_EXTERNAL		0x02

/* 6.1.2.1  Class-Specअगरic MS Interface Header Descriptor */
काष्ठा usb_ms_header_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;
	__u8  bDescriptorSubtype;
	__le16 bcdMSC;
	__le16 wTotalLength;
पूर्ण __attribute__ ((packed));

#घोषणा USB_DT_MS_HEADER_SIZE	7

/* 6.1.2.2  MIDI IN Jack Descriptor */
काष्ठा usb_midi_in_jack_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;		/* USB_DT_CS_INTERFACE */
	__u8  bDescriptorSubtype;	/* USB_MS_MIDI_IN_JACK */
	__u8  bJackType;		/* USB_MS_EMBEDDED/EXTERNAL */
	__u8  bJackID;
	__u8  iJack;
पूर्ण __attribute__ ((packed));

#घोषणा USB_DT_MIDI_IN_SIZE	6

काष्ठा usb_midi_source_pin अणु
	__u8  baSourceID;
	__u8  baSourcePin;
पूर्ण __attribute__ ((packed));

/* 6.1.2.3  MIDI OUT Jack Descriptor */
काष्ठा usb_midi_out_jack_descriptor अणु
	__u8  bLength;
	__u8  bDescriptorType;		/* USB_DT_CS_INTERFACE */
	__u8  bDescriptorSubtype;	/* USB_MS_MIDI_OUT_JACK */
	__u8  bJackType;		/* USB_MS_EMBEDDED/EXTERNAL */
	__u8  bJackID;
	__u8  bNrInputPins;		/* p */
	काष्ठा usb_midi_source_pin pins[]; /* [p] */
	/*__u8  iJack;  -- omitted due to variable-sized pins[] */
पूर्ण __attribute__ ((packed));

#घोषणा USB_DT_MIDI_OUT_SIZE(p)	(7 + 2 * (p))

/* As above, but more useful क्रम defining your own descriptors: */
#घोषणा DECLARE_USB_MIDI_OUT_JACK_DESCRIPTOR(p)			\
काष्ठा usb_midi_out_jack_descriptor_##p अणु			\
	__u8  bLength;						\
	__u8  bDescriptorType;					\
	__u8  bDescriptorSubtype;				\
	__u8  bJackType;					\
	__u8  bJackID;						\
	__u8  bNrInputPins;					\
	काष्ठा usb_midi_source_pin pins[p];			\
	__u8  iJack;						\
पूर्ण __attribute__ ((packed))

/* 6.2.2  Class-Specअगरic MS Bulk Data Endpoपूर्णांक Descriptor */
काष्ठा usb_ms_endpoपूर्णांक_descriptor अणु
	__u8  bLength;			/* 4+n */
	__u8  bDescriptorType;		/* USB_DT_CS_ENDPOINT */
	__u8  bDescriptorSubtype;	/* USB_MS_GENERAL */
	__u8  bNumEmbMIDIJack;		/* n */
	__u8  baAssocJackID[];		/* [n] */
पूर्ण __attribute__ ((packed));

#घोषणा USB_DT_MS_ENDPOINT_SIZE(n)	(4 + (n))

/* As above, but more useful क्रम defining your own descriptors: */
#घोषणा DECLARE_USB_MS_ENDPOINT_DESCRIPTOR(n)			\
काष्ठा usb_ms_endpoपूर्णांक_descriptor_##n अणु				\
	__u8  bLength;						\
	__u8  bDescriptorType;					\
	__u8  bDescriptorSubtype;				\
	__u8  bNumEmbMIDIJack;					\
	__u8  baAssocJackID[n];					\
पूर्ण __attribute__ ((packed))

#पूर्ण_अगर /* __LINUX_USB_MIDI_H */
