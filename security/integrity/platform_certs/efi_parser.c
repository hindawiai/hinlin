<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* EFI signature/key/certअगरicate list parser
 *
 * Copyright (C) 2012, 2016 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 */

#घोषणा pr_fmt(fmt) "EFI: "fmt
#समावेश <linux/module.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/err.h>
#समावेश <linux/efi.h>

/**
 * parse_efi_signature_list - Parse an EFI signature list क्रम certअगरicates
 * @source: The source of the key
 * @data: The data blob to parse
 * @size: The size of the data blob
 * @get_handler_क्रम_guid: Get the handler func क्रम the sig type (or शून्य)
 *
 * Parse an EFI signature list looking क्रम elements of पूर्णांकerest.  A list is
 * made up of a series of sublists, where all the elements in a sublist are of
 * the same type, but sublists can be of dअगरferent types.
 *
 * For each sublist encountered, the @get_handler_क्रम_guid function is called
 * with the type specअगरier GUID and वापसs either a poपूर्णांकer to a function to
 * handle elements of that type or शून्य अगर the type is not of पूर्णांकerest.
 *
 * If the sublist is of पूर्णांकerest, each element is passed to the handler
 * function in turn.
 *
 * Error EBADMSG is वापसed अगर the list करोesn't parse correctly and 0 is
 * वापसed अगर the list was parsed correctly.  No error can be वापसed from
 * the @get_handler_क्रम_guid function or the element handler function it
 * वापसs.
 */
पूर्णांक __init parse_efi_signature_list(
	स्थिर अक्षर *source,
	स्थिर व्योम *data, माप_प्रकार size,
	efi_element_handler_t (*get_handler_क्रम_guid)(स्थिर efi_guid_t *))
अणु
	efi_element_handler_t handler;
	अचिन्हित पूर्णांक offs = 0;

	pr_devel("-->%s(,%zu)\n", __func__, size);

	जबतक (size > 0) अणु
		स्थिर efi_signature_data_t *elem;
		efi_signature_list_t list;
		माप_प्रकार lsize, esize, hsize, elsize;

		अगर (size < माप(list))
			वापस -EBADMSG;

		स_नकल(&list, data, माप(list));
		pr_devel("LIST[%04x] guid=%pUl ls=%x hs=%x ss=%x\n",
			 offs,
			 list.signature_type.b, list.signature_list_size,
			 list.signature_header_size, list.signature_size);

		lsize = list.signature_list_size;
		hsize = list.signature_header_size;
		esize = list.signature_size;
		elsize = lsize - माप(list) - hsize;

		अगर (lsize > size) अणु
			pr_devel("<--%s() = -EBADMSG [overrun @%x]\n",
				 __func__, offs);
			वापस -EBADMSG;
		पूर्ण

		अगर (lsize < माप(list) ||
		    lsize - माप(list) < hsize ||
		    esize < माप(*elem) ||
		    elsize < esize ||
		    elsize % esize != 0) अणु
			pr_devel("- bad size combo @%x\n", offs);
			वापस -EBADMSG;
		पूर्ण

		handler = get_handler_क्रम_guid(&list.signature_type);
		अगर (!handler) अणु
			data += lsize;
			size -= lsize;
			offs += lsize;
			जारी;
		पूर्ण

		data += माप(list) + hsize;
		size -= माप(list) + hsize;
		offs += माप(list) + hsize;

		क्रम (; elsize > 0; elsize -= esize) अणु
			elem = data;

			pr_devel("ELEM[%04x]\n", offs);
			handler(source,
				&elem->signature_data,
				esize - माप(*elem));

			data += esize;
			size -= esize;
			offs += esize;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
