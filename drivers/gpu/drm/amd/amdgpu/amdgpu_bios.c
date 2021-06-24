<शैली गुरु>
/*
 * Copyright 2008 Advanced Micro Devices, Inc.
 * Copyright 2008 Red Hat Inc.
 * Copyright 2009 Jerome Glisse.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: Dave Airlie
 *          Alex Deucher
 *          Jerome Glisse
 */

#समावेश "amdgpu.h"
#समावेश "atom.h"

#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/acpi.h>
/*
 * BIOS.
 */

#घोषणा AMD_VBIOS_SIGNATURE " 761295520"
#घोषणा AMD_VBIOS_SIGNATURE_OFFSET 0x30
#घोषणा AMD_VBIOS_SIGNATURE_SIZE माप(AMD_VBIOS_SIGNATURE)
#घोषणा AMD_VBIOS_SIGNATURE_END (AMD_VBIOS_SIGNATURE_OFFSET + AMD_VBIOS_SIGNATURE_SIZE)
#घोषणा AMD_IS_VALID_VBIOS(p) ((p)[0] == 0x55 && (p)[1] == 0xAA)
#घोषणा AMD_VBIOS_LENGTH(p) ((p)[2] << 9)

/* Check अगर current bios is an ATOM BIOS.
 * Return true अगर it is ATOM BIOS. Otherwise, वापस false.
 */
अटल bool check_atom_bios(uपूर्णांक8_t *bios, माप_प्रकार size)
अणु
	uपूर्णांक16_t पंचांगp, bios_header_start;

	अगर (!bios || size < 0x49) अणु
		DRM_INFO("vbios mem is null or mem size is wrong\n");
		वापस false;
	पूर्ण

	अगर (!AMD_IS_VALID_VBIOS(bios)) अणु
		DRM_INFO("BIOS signature incorrect %x %x\n", bios[0], bios[1]);
		वापस false;
	पूर्ण

	bios_header_start = bios[0x48] | (bios[0x49] << 8);
	अगर (!bios_header_start) अणु
		DRM_INFO("Can't locate bios header\n");
		वापस false;
	पूर्ण

	पंचांगp = bios_header_start + 4;
	अगर (size < पंचांगp) अणु
		DRM_INFO("BIOS header is broken\n");
		वापस false;
	पूर्ण

	अगर (!स_भेद(bios + पंचांगp, "ATOM", 4) ||
	    !स_भेद(bios + पंचांगp, "MOTA", 4)) अणु
		DRM_DEBUG("ATOMBIOS detected\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* If you boot an IGP board with a discrete card as the primary,
 * the IGP rom is not accessible via the rom bar as the IGP rom is
 * part of the प्रणाली bios.  On boot, the प्रणाली bios माला_दो a
 * copy of the igp rom at the start of vram अगर a discrete card is
 * present.
 */
अटल bool igp_पढ़ो_bios_from_vram(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक8_t __iomem *bios;
	resource_माप_प्रकार vram_base;
	resource_माप_प्रकार size = 256 * 1024; /* ??? */

	अगर (!(adev->flags & AMD_IS_APU))
		अगर (amdgpu_device_need_post(adev))
			वापस false;

	/* FB BAR not enabled */
	अगर (pci_resource_len(adev->pdev, 0) == 0)
		वापस false;

	adev->bios = शून्य;
	vram_base = pci_resource_start(adev->pdev, 0);
	bios = ioremap_wc(vram_base, size);
	अगर (!bios) अणु
		वापस false;
	पूर्ण

	adev->bios = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!adev->bios) अणु
		iounmap(bios);
		वापस false;
	पूर्ण
	adev->bios_size = size;
	स_नकल_fromio(adev->bios, bios, size);
	iounmap(bios);

	अगर (!check_atom_bios(adev->bios, size)) अणु
		kमुक्त(adev->bios);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

bool amdgpu_पढ़ो_bios(काष्ठा amdgpu_device *adev)
अणु
	uपूर्णांक8_t __iomem *bios;
	माप_प्रकार size;

	adev->bios = शून्य;
	/* XXX: some cards may वापस 0 क्रम rom size? ddx has a workaround */
	bios = pci_map_rom(adev->pdev, &size);
	अगर (!bios) अणु
		वापस false;
	पूर्ण

	adev->bios = kzalloc(size, GFP_KERNEL);
	अगर (adev->bios == शून्य) अणु
		pci_unmap_rom(adev->pdev, bios);
		वापस false;
	पूर्ण
	adev->bios_size = size;
	स_नकल_fromio(adev->bios, bios, size);
	pci_unmap_rom(adev->pdev, bios);

	अगर (!check_atom_bios(adev->bios, size)) अणु
		kमुक्त(adev->bios);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool amdgpu_पढ़ो_bios_from_rom(काष्ठा amdgpu_device *adev)
अणु
	u8 header[AMD_VBIOS_SIGNATURE_END+1] = अणु0पूर्ण;
	पूर्णांक len;

	अगर (!adev->asic_funcs || !adev->asic_funcs->पढ़ो_bios_from_rom)
		वापस false;

	/* validate VBIOS signature */
	अगर (amdgpu_asic_पढ़ो_bios_from_rom(adev, &header[0], माप(header)) == false)
		वापस false;
	header[AMD_VBIOS_SIGNATURE_END] = 0;

	अगर ((!AMD_IS_VALID_VBIOS(header)) ||
	    0 != स_भेद((अक्षर *)&header[AMD_VBIOS_SIGNATURE_OFFSET],
			AMD_VBIOS_SIGNATURE,
			म_माप(AMD_VBIOS_SIGNATURE)))
		वापस false;

	/* valid vbios, go on */
	len = AMD_VBIOS_LENGTH(header);
	len = ALIGN(len, 4);
	adev->bios = kदो_स्मृति(len, GFP_KERNEL);
	अगर (!adev->bios) अणु
		DRM_ERROR("no memory to allocate for BIOS\n");
		वापस false;
	पूर्ण
	adev->bios_size = len;

	/* पढ़ो complete BIOS */
	amdgpu_asic_पढ़ो_bios_from_rom(adev, adev->bios, len);

	अगर (!check_atom_bios(adev->bios, len)) अणु
		kमुक्त(adev->bios);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool amdgpu_पढ़ो_platक्रमm_bios(काष्ठा amdgpu_device *adev)
अणु
	phys_addr_t rom = adev->pdev->rom;
	माप_प्रकार romlen = adev->pdev->romlen;
	व्योम __iomem *bios;

	adev->bios = शून्य;

	अगर (!rom || romlen == 0)
		वापस false;

	adev->bios = kzalloc(romlen, GFP_KERNEL);
	अगर (!adev->bios)
		वापस false;

	bios = ioremap(rom, romlen);
	अगर (!bios)
		जाओ मुक्त_bios;

	स_नकल_fromio(adev->bios, bios, romlen);
	iounmap(bios);

	अगर (!check_atom_bios(adev->bios, romlen))
		जाओ मुक्त_bios;

	adev->bios_size = romlen;

	वापस true;
मुक्त_bios:
	kमुक्त(adev->bios);
	वापस false;
पूर्ण

#अगर_घोषित CONFIG_ACPI
/* ATRM is used to get the BIOS on the discrete cards in
 * dual-gpu प्रणालीs.
 */
/* retrieve the ROM in 4k blocks */
#घोषणा ATRM_BIOS_PAGE 4096
/**
 * amdgpu_atrm_call - fetch a chunk of the vbios
 *
 * @atrm_handle: acpi ATRM handle
 * @bios: vbios image poपूर्णांकer
 * @offset: offset of vbios image data to fetch
 * @len: length of vbios image data to fetch
 *
 * Executes ATRM to fetch a chunk of the discrete
 * vbios image on PX प्रणालीs (all asics).
 * Returns the length of the buffer fetched.
 */
अटल पूर्णांक amdgpu_atrm_call(acpi_handle atrm_handle, uपूर्णांक8_t *bios,
			    पूर्णांक offset, पूर्णांक len)
अणु
	acpi_status status;
	जोड़ acpi_object atrm_arg_elements[2], *obj;
	काष्ठा acpi_object_list atrm_arg;
	काष्ठा acpi_buffer buffer = अणु ACPI_ALLOCATE_BUFFER, शून्यपूर्ण;

	atrm_arg.count = 2;
	atrm_arg.poपूर्णांकer = &atrm_arg_elements[0];

	atrm_arg_elements[0].type = ACPI_TYPE_INTEGER;
	atrm_arg_elements[0].पूर्णांकeger.value = offset;

	atrm_arg_elements[1].type = ACPI_TYPE_INTEGER;
	atrm_arg_elements[1].पूर्णांकeger.value = len;

	status = acpi_evaluate_object(atrm_handle, शून्य, &atrm_arg, &buffer);
	अगर (ACPI_FAILURE(status)) अणु
		prपूर्णांकk("failed to evaluate ATRM got %s\n", acpi_क्रमmat_exception(status));
		वापस -ENODEV;
	पूर्ण

	obj = (जोड़ acpi_object *)buffer.poपूर्णांकer;
	स_नकल(bios+offset, obj->buffer.poपूर्णांकer, obj->buffer.length);
	len = obj->buffer.length;
	kमुक्त(buffer.poपूर्णांकer);
	वापस len;
पूर्ण

अटल bool amdgpu_atrm_get_bios(काष्ठा amdgpu_device *adev)
अणु
	पूर्णांक ret;
	पूर्णांक size = 256 * 1024;
	पूर्णांक i;
	काष्ठा pci_dev *pdev = शून्य;
	acpi_handle dhandle, atrm_handle;
	acpi_status status;
	bool found = false;

	/* ATRM is क्रम the discrete card only */
	अगर (adev->flags & AMD_IS_APU)
		वापस false;

	जबतक ((pdev = pci_get_class(PCI_CLASS_DISPLAY_VGA << 8, pdev)) != शून्य) अणु
		dhandle = ACPI_HANDLE(&pdev->dev);
		अगर (!dhandle)
			जारी;

		status = acpi_get_handle(dhandle, "ATRM", &atrm_handle);
		अगर (ACPI_SUCCESS(status)) अणु
			found = true;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!found) अणु
		जबतक ((pdev = pci_get_class(PCI_CLASS_DISPLAY_OTHER << 8, pdev)) != शून्य) अणु
			dhandle = ACPI_HANDLE(&pdev->dev);
			अगर (!dhandle)
				जारी;

			status = acpi_get_handle(dhandle, "ATRM", &atrm_handle);
			अगर (ACPI_SUCCESS(status)) अणु
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!found)
		वापस false;

	adev->bios = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!adev->bios) अणु
		dev_err(adev->dev, "Unable to allocate bios\n");
		वापस false;
	पूर्ण

	क्रम (i = 0; i < size / ATRM_BIOS_PAGE; i++) अणु
		ret = amdgpu_atrm_call(atrm_handle,
				       adev->bios,
				       (i * ATRM_BIOS_PAGE),
				       ATRM_BIOS_PAGE);
		अगर (ret < ATRM_BIOS_PAGE)
			अवरोध;
	पूर्ण

	अगर (!check_atom_bios(adev->bios, size)) अणु
		kमुक्त(adev->bios);
		वापस false;
	पूर्ण
	adev->bios_size = size;
	वापस true;
पूर्ण
#अन्यथा
अटल अंतरभूत bool amdgpu_atrm_get_bios(काष्ठा amdgpu_device *adev)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल bool amdgpu_पढ़ो_disabled_bios(काष्ठा amdgpu_device *adev)
अणु
	अगर (adev->flags & AMD_IS_APU)
		वापस igp_पढ़ो_bios_from_vram(adev);
	अन्यथा
		वापस (!adev->asic_funcs || !adev->asic_funcs->पढ़ो_disabled_bios) ?
			false : amdgpu_asic_पढ़ो_disabled_bios(adev);
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल bool amdgpu_acpi_vfct_bios(काष्ठा amdgpu_device *adev)
अणु
	काष्ठा acpi_table_header *hdr;
	acpi_size tbl_size;
	UEFI_ACPI_VFCT *vfct;
	अचिन्हित offset;

	अगर (!ACPI_SUCCESS(acpi_get_table("VFCT", 1, &hdr)))
		वापस false;
	tbl_size = hdr->length;
	अगर (tbl_size < माप(UEFI_ACPI_VFCT)) अणु
		dev_info(adev->dev, "ACPI VFCT table present but broken (too short #1),skipping\n");
		वापस false;
	पूर्ण

	vfct = (UEFI_ACPI_VFCT *)hdr;
	offset = vfct->VBIOSImageOffset;

	जबतक (offset < tbl_size) अणु
		GOP_VBIOS_CONTENT *vbios = (GOP_VBIOS_CONTENT *)((अक्षर *)hdr + offset);
		VFCT_IMAGE_HEADER *vhdr = &vbios->VbiosHeader;

		offset += माप(VFCT_IMAGE_HEADER);
		अगर (offset > tbl_size) अणु
			dev_info(adev->dev, "ACPI VFCT image header truncated,skipping\n");
			वापस false;
		पूर्ण

		offset += vhdr->ImageLength;
		अगर (offset > tbl_size) अणु
			dev_info(adev->dev, "ACPI VFCT image truncated,skipping\n");
			वापस false;
		पूर्ण

		अगर (vhdr->ImageLength &&
		    vhdr->PCIBus == adev->pdev->bus->number &&
		    vhdr->PCIDevice == PCI_SLOT(adev->pdev->devfn) &&
		    vhdr->PCIFunction == PCI_FUNC(adev->pdev->devfn) &&
		    vhdr->VenकरोrID == adev->pdev->venकरोr &&
		    vhdr->DeviceID == adev->pdev->device) अणु
			adev->bios = kmemdup(&vbios->VbiosContent,
					     vhdr->ImageLength,
					     GFP_KERNEL);

			अगर (!check_atom_bios(adev->bios, vhdr->ImageLength)) अणु
				kमुक्त(adev->bios);
				वापस false;
			पूर्ण
			adev->bios_size = vhdr->ImageLength;
			वापस true;
		पूर्ण
	पूर्ण

	dev_info(adev->dev, "ACPI VFCT table present but broken (too short #2),skipping\n");
	वापस false;
पूर्ण
#अन्यथा
अटल अंतरभूत bool amdgpu_acpi_vfct_bios(काष्ठा amdgpu_device *adev)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

bool amdgpu_get_bios(काष्ठा amdgpu_device *adev)
अणु
	अगर (amdgpu_atrm_get_bios(adev)) अणु
		dev_info(adev->dev, "Fetched VBIOS from ATRM\n");
		जाओ success;
	पूर्ण

	अगर (amdgpu_acpi_vfct_bios(adev)) अणु
		dev_info(adev->dev, "Fetched VBIOS from VFCT\n");
		जाओ success;
	पूर्ण

	अगर (igp_पढ़ो_bios_from_vram(adev)) अणु
		dev_info(adev->dev, "Fetched VBIOS from VRAM BAR\n");
		जाओ success;
	पूर्ण

	अगर (amdgpu_पढ़ो_bios(adev)) अणु
		dev_info(adev->dev, "Fetched VBIOS from ROM BAR\n");
		जाओ success;
	पूर्ण

	अगर (amdgpu_पढ़ो_bios_from_rom(adev)) अणु
		dev_info(adev->dev, "Fetched VBIOS from ROM\n");
		जाओ success;
	पूर्ण

	अगर (amdgpu_पढ़ो_disabled_bios(adev)) अणु
		dev_info(adev->dev, "Fetched VBIOS from disabled ROM BAR\n");
		जाओ success;
	पूर्ण

	अगर (amdgpu_पढ़ो_platक्रमm_bios(adev)) अणु
		dev_info(adev->dev, "Fetched VBIOS from platform\n");
		जाओ success;
	पूर्ण

	dev_err(adev->dev, "Unable to locate a BIOS ROM\n");
	वापस false;

success:
	adev->is_atom_fw = (adev->asic_type >= CHIP_VEGA10) ? true : false;
	वापस true;
पूर्ण
