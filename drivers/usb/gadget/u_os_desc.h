<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * u_os_desc.h
 *
 * Utility definitions क्रम "OS Descriptors" support
 *
 * Copyright (c) 2014 Samsung Electronics Co., Ltd.
 *		http://www.samsung.com
 *
 * Author: Andrzej Pietrasiewicz <andrzejtp2010@gmail.com>
 */

#अगर_अघोषित __U_OS_DESC_H__
#घोषणा __U_OS_DESC_H__

#समावेश <यंत्र/unaligned.h>
#समावेश <linux/nls.h>

#घोषणा USB_EXT_PROP_DW_SIZE			0
#घोषणा USB_EXT_PROP_DW_PROPERTY_DATA_TYPE	4
#घोषणा USB_EXT_PROP_W_PROPERTY_NAME_LENGTH	8
#घोषणा USB_EXT_PROP_B_PROPERTY_NAME		10
#घोषणा USB_EXT_PROP_DW_PROPERTY_DATA_LENGTH	10
#घोषणा USB_EXT_PROP_B_PROPERTY_DATA		14

#घोषणा USB_EXT_PROP_RESERVED			0
#घोषणा USB_EXT_PROP_UNICODE			1
#घोषणा USB_EXT_PROP_UNICODE_ENV		2
#घोषणा USB_EXT_PROP_BINARY			3
#घोषणा USB_EXT_PROP_LE32			4
#घोषणा USB_EXT_PROP_BE32			5
#घोषणा USB_EXT_PROP_UNICODE_LINK		6
#घोषणा USB_EXT_PROP_UNICODE_MULTI		7

अटल अंतरभूत u8 *__usb_ext_prop_ptr(u8 *buf, माप_प्रकार offset)
अणु
	वापस buf + offset;
पूर्ण

अटल अंतरभूत u8 *usb_ext_prop_size_ptr(u8 *buf)
अणु
	वापस __usb_ext_prop_ptr(buf, USB_EXT_PROP_DW_SIZE);
पूर्ण

अटल अंतरभूत u8 *usb_ext_prop_type_ptr(u8 *buf)
अणु
	वापस __usb_ext_prop_ptr(buf, USB_EXT_PROP_DW_PROPERTY_DATA_TYPE);
पूर्ण

अटल अंतरभूत u8 *usb_ext_prop_name_len_ptr(u8 *buf)
अणु
	वापस __usb_ext_prop_ptr(buf, USB_EXT_PROP_W_PROPERTY_NAME_LENGTH);
पूर्ण

अटल अंतरभूत u8 *usb_ext_prop_name_ptr(u8 *buf)
अणु
	वापस __usb_ext_prop_ptr(buf, USB_EXT_PROP_B_PROPERTY_NAME);
पूर्ण

अटल अंतरभूत u8 *usb_ext_prop_data_len_ptr(u8 *buf, माप_प्रकार off)
अणु
	वापस __usb_ext_prop_ptr(buf,
				  USB_EXT_PROP_DW_PROPERTY_DATA_LENGTH + off);
पूर्ण

अटल अंतरभूत u8 *usb_ext_prop_data_ptr(u8 *buf, माप_प्रकार off)
अणु
	वापस __usb_ext_prop_ptr(buf, USB_EXT_PROP_B_PROPERTY_DATA + off);
पूर्ण

अटल अंतरभूत व्योम usb_ext_prop_put_size(u8 *buf, पूर्णांक dw_size)
अणु
	put_unaligned_le32(dw_size, usb_ext_prop_size_ptr(buf));
पूर्ण

अटल अंतरभूत व्योम usb_ext_prop_put_type(u8 *buf, पूर्णांक type)
अणु
	put_unaligned_le32(type, usb_ext_prop_type_ptr(buf));
पूर्ण

अटल अंतरभूत पूर्णांक usb_ext_prop_put_name(u8 *buf, स्थिर अक्षर *name, पूर्णांक pnl)
अणु
	पूर्णांक result;

	put_unaligned_le16(pnl, usb_ext_prop_name_len_ptr(buf));
	result = utf8s_to_utf16s(name, म_माप(name), UTF16_LITTLE_ENDIAN,
		(ब_अक्षर_प्रकार *) usb_ext_prop_name_ptr(buf), pnl - 2);
	अगर (result < 0)
		वापस result;

	put_unaligned_le16(0, &buf[USB_EXT_PROP_B_PROPERTY_NAME + pnl - 2]);

	वापस pnl;
पूर्ण

अटल अंतरभूत व्योम usb_ext_prop_put_binary(u8 *buf, पूर्णांक pnl, स्थिर u8 *data,
					   पूर्णांक data_len)
अणु
	put_unaligned_le32(data_len, usb_ext_prop_data_len_ptr(buf, pnl));
	स_नकल(usb_ext_prop_data_ptr(buf, pnl), data, data_len);
पूर्ण

अटल अंतरभूत पूर्णांक usb_ext_prop_put_unicode(u8 *buf, पूर्णांक pnl, स्थिर अक्षर *string,
					   पूर्णांक data_len)
अणु
	पूर्णांक result;
	put_unaligned_le32(data_len, usb_ext_prop_data_len_ptr(buf, pnl));
	result = utf8s_to_utf16s(string, data_len >> 1, UTF16_LITTLE_ENDIAN,
			(ब_अक्षर_प्रकार *) usb_ext_prop_data_ptr(buf, pnl),
			data_len - 2);
	अगर (result < 0)
		वापस result;

	put_unaligned_le16(0,
		&buf[USB_EXT_PROP_B_PROPERTY_DATA + pnl + data_len - 2]);

	वापस data_len;
पूर्ण

#पूर्ण_अगर /* __U_OS_DESC_H__ */
