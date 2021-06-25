<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * USB CDC common helpers
 *
 * Copyright (c) 2015 Oliver Neukum <oneukum@suse.com>
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */
#अगर_अघोषित __LINUX_USB_CDC_H
#घोषणा __LINUX_USB_CDC_H

#समावेश <uapi/linux/usb/cdc.h>

/*
 * inofficial magic numbers
 */

#घोषणा CDC_PHONET_MAGIC_NUMBER		0xAB

/*
 * parsing CDC headers
 */

काष्ठा usb_cdc_parsed_header अणु
	काष्ठा usb_cdc_जोड़_desc *usb_cdc_जोड़_desc;
	काष्ठा usb_cdc_header_desc *usb_cdc_header_desc;

	काष्ठा usb_cdc_call_mgmt_descriptor *usb_cdc_call_mgmt_descriptor;
	काष्ठा usb_cdc_acm_descriptor *usb_cdc_acm_descriptor;
	काष्ठा usb_cdc_country_functional_desc *usb_cdc_country_functional_desc;
	काष्ठा usb_cdc_network_terminal_desc *usb_cdc_network_terminal_desc;
	काष्ठा usb_cdc_ether_desc *usb_cdc_ether_desc;
	काष्ठा usb_cdc_dmm_desc *usb_cdc_dmm_desc;
	काष्ठा usb_cdc_mdlm_desc *usb_cdc_mdlm_desc;
	काष्ठा usb_cdc_mdlm_detail_desc *usb_cdc_mdlm_detail_desc;
	काष्ठा usb_cdc_obex_desc *usb_cdc_obex_desc;
	काष्ठा usb_cdc_ncm_desc *usb_cdc_ncm_desc;
	काष्ठा usb_cdc_mbim_desc *usb_cdc_mbim_desc;
	काष्ठा usb_cdc_mbim_extended_desc *usb_cdc_mbim_extended_desc;

	bool phonet_magic_present;
पूर्ण;

काष्ठा usb_पूर्णांकerface;
पूर्णांक cdc_parse_cdc_header(काष्ठा usb_cdc_parsed_header *hdr,
				काष्ठा usb_पूर्णांकerface *पूर्णांकf,
				u8 *buffer,
				पूर्णांक buflen);

#पूर्ण_अगर /* __LINUX_USB_CDC_H */
