<शैली गुरु>
// SPDX-License-Identअगरier: LGPL-2.1+
/*
 * Copyright (C) 2003 David Brownell
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/माला.स>
#समावेश <linux/device.h>
#समावेश <linux/nls.h>

#समावेश <linux/usb/ch9.h>
#समावेश <linux/usb/gadget.h>


/**
 * usb_gadget_get_string - fill out a string descriptor 
 * @table: of c strings encoded using UTF-8
 * @id: string id, from low byte of wValue in get string descriptor
 * @buf: at least 256 bytes, must be 16-bit aligned
 *
 * Finds the UTF-8 string matching the ID, and converts it पूर्णांकo a
 * string descriptor in utf16-le.
 * Returns length of descriptor (always even) or negative त्रुटि_सं
 *
 * If your driver needs stings in multiple languages, you'll probably
 * "switch (wIndex) { ... }"  in your ep0 string descriptor logic,
 * using this routine after choosing which set of UTF-8 strings to use.
 * Note that US-ASCII is a strict subset of UTF-8; any string bytes with
 * the eighth bit set will be multibyte UTF-8 अक्षरacters, not ISO-8859/1
 * अक्षरacters (which are also widely used in C strings).
 */
पूर्णांक
usb_gadget_get_string (स्थिर काष्ठा usb_gadget_strings *table, पूर्णांक id, u8 *buf)
अणु
	काष्ठा usb_string	*s;
	पूर्णांक			len;

	/* descriptor 0 has the language id */
	अगर (id == 0) अणु
		buf [0] = 4;
		buf [1] = USB_DT_STRING;
		buf [2] = (u8) table->language;
		buf [3] = (u8) (table->language >> 8);
		वापस 4;
	पूर्ण
	क्रम (s = table->strings; s && s->s; s++)
		अगर (s->id == id)
			अवरोध;

	/* unrecognized: stall. */
	अगर (!s || !s->s)
		वापस -EINVAL;

	/* string descriptors have length, tag, then UTF16-LE text */
	len = min((माप_प्रकार)USB_MAX_STRING_LEN, म_माप(s->s));
	len = utf8s_to_utf16s(s->s, len, UTF16_LITTLE_ENDIAN,
			(ब_अक्षर_प्रकार *) &buf[2], USB_MAX_STRING_LEN);
	अगर (len < 0)
		वापस -EINVAL;
	buf [0] = (len + 1) * 2;
	buf [1] = USB_DT_STRING;
	वापस buf [0];
पूर्ण
EXPORT_SYMBOL_GPL(usb_gadget_get_string);

/**
 * usb_validate_langid - validate usb language identअगरiers
 * @langid: usb language identअगरier
 *
 * Returns true क्रम valid language identअगरier, otherwise false.
 */
bool usb_validate_langid(u16 langid)
अणु
	u16 primary_lang = langid & 0x3ff;	/* bit [9:0] */
	u16 sub_lang = langid >> 10;		/* bit [15:10] */

	चयन (primary_lang) अणु
	हाल 0:
	हाल 0x62 ... 0xfe:
	हाल 0x100 ... 0x3ff:
		वापस false;
	पूर्ण
	अगर (!sub_lang)
		वापस false;

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(usb_validate_langid);
