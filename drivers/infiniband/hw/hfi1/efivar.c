<शैली गुरु>
/*
 * Copyright(c) 2015, 2016 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#समावेश <linux/प्रकार.स>
#समावेश "efivar.h"

/* GUID क्रम HFI1 variables in EFI */
#घोषणा HFI1_EFIVAR_GUID EFI_GUID(0xc50a953e, 0xa8b2, 0x42a6, \
		0xbf, 0x89, 0xd3, 0x33, 0xa6, 0xe9, 0xe6, 0xd4)
/* largest EFI data size we expect */
#घोषणा EFI_DATA_SIZE 4096

/*
 * Read the named EFI variable.  Return the size of the actual data in *size
 * and a kदो_स्मृति'ed buffer in *वापस_data.  The caller must मुक्त the
 * data.  It is guaranteed that *वापस_data will be शून्य and *size = 0
 * अगर this routine fails.
 *
 * Return 0 on success, -त्रुटि_सं on failure.
 */
अटल पूर्णांक पढ़ो_efi_var(स्थिर अक्षर *name, अचिन्हित दीर्घ *size,
			व्योम **वापस_data)
अणु
	efi_status_t status;
	efi_अक्षर16_t *uni_name;
	efi_guid_t guid;
	अचिन्हित दीर्घ temp_size;
	व्योम *temp_buffer;
	व्योम *data;
	पूर्णांक i;
	पूर्णांक ret;

	/* set failure वापस values */
	*size = 0;
	*वापस_data = शून्य;

	अगर (!efi_rt_services_supported(EFI_RT_SUPPORTED_GET_VARIABLE))
		वापस -EOPNOTSUPP;

	uni_name = kसुस्मृति(म_माप(name) + 1, माप(efi_अक्षर16_t), GFP_KERNEL);
	temp_buffer = kzalloc(EFI_DATA_SIZE, GFP_KERNEL);

	अगर (!uni_name || !temp_buffer) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	/* input: the size of the buffer */
	temp_size = EFI_DATA_SIZE;

	/* convert ASCII to unicode - it is a 1:1 mapping */
	क्रम (i = 0; name[i]; i++)
		uni_name[i] = name[i];

	/* need a variable क्रम our GUID */
	guid = HFI1_EFIVAR_GUID;

	/* call पूर्णांकo EFI runसमय services */
	status = efi.get_variable(
			uni_name,
			&guid,
			शून्य,
			&temp_size,
			temp_buffer);

	/*
	 * It would be nice to call efi_status_to_err() here, but that
	 * is in the EFIVAR_FS code and may not be compiled in.
	 * However, even that is insufficient since it करोes not cover
	 * EFI_BUFFER_TOO_SMALL which could be an important वापस.
	 * For now, just split out succces or not found.
	 */
	ret = status == EFI_SUCCESS   ? 0 :
	      status == EFI_NOT_FOUND ? -ENOENT :
					-EINVAL;
	अगर (ret)
		जाओ fail;

	/*
	 * We have successfully पढ़ो the EFI variable पूर्णांकo our
	 * temporary buffer.  Now allocate a correctly sized
	 * buffer.
	 */
	data = kmemdup(temp_buffer, temp_size, GFP_KERNEL);
	अगर (!data) अणु
		ret = -ENOMEM;
		जाओ fail;
	पूर्ण

	*size = temp_size;
	*वापस_data = data;

fail:
	kमुक्त(uni_name);
	kमुक्त(temp_buffer);

	वापस ret;
पूर्ण

/*
 * Read an HFI1 EFI variable of the क्रमm:
 *	<PCIe address>-<kind>
 * Return an kalloc'ed array and size of the data.
 *
 * Returns 0 on success, -त्रुटि_सं on failure.
 */
पूर्णांक पढ़ो_hfi1_efi_var(काष्ठा hfi1_devdata *dd, स्थिर अक्षर *kind,
		      अचिन्हित दीर्घ *size, व्योम **वापस_data)
अणु
	अक्षर prefix_name[64];
	अक्षर name[64];
	पूर्णांक result;
	पूर्णांक i;

	/* create a common prefix */
	snम_लिखो(prefix_name, माप(prefix_name), "%04x:%02x:%02x.%x",
		 pci_करोमुख्य_nr(dd->pcidev->bus),
		 dd->pcidev->bus->number,
		 PCI_SLOT(dd->pcidev->devfn),
		 PCI_FUNC(dd->pcidev->devfn));
	snम_लिखो(name, माप(name), "%s-%s", prefix_name, kind);
	result = पढ़ो_efi_var(name, size, वापस_data);

	/*
	 * If पढ़ोing the lowerहाल EFI variable fail, पढ़ो the upperहाल
	 * variable.
	 */
	अगर (result) अणु
		/* Converting to upperहाल */
		क्रम (i = 0; prefix_name[i]; i++)
			अगर (है_अक्षर(prefix_name[i]))
				prefix_name[i] = बड़े(prefix_name[i]);
		snम_लिखो(name, माप(name), "%s-%s", prefix_name, kind);
		result = पढ़ो_efi_var(name, size, वापस_data);
	पूर्ण

	वापस result;
पूर्ण
