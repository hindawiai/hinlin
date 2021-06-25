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

#समावेश <linux/acpi.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश <drm/drm_device.h>

#समावेश "atom.h"
#समावेश "radeon.h"
#समावेश "radeon_reg.h"

/*
 * BIOS.
 */

/* If you boot an IGP board with a discrete card as the primary,
 * the IGP rom is not accessible via the rom bar as the IGP rom is
 * part of the प्रणाली bios.  On boot, the प्रणाली bios माला_दो a
 * copy of the igp rom at the start of vram अगर a discrete card is
 * present.
 */
अटल bool igp_पढ़ो_bios_from_vram(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक8_t __iomem *bios;
	resource_माप_प्रकार vram_base;
	resource_माप_प्रकार size = 256 * 1024; /* ??? */

	अगर (!(rdev->flags & RADEON_IS_IGP))
		अगर (!radeon_card_posted(rdev))
			वापस false;

	rdev->bios = शून्य;
	vram_base = pci_resource_start(rdev->pdev, 0);
	bios = ioremap(vram_base, size);
	अगर (!bios) अणु
		वापस false;
	पूर्ण

	अगर (size == 0 || bios[0] != 0x55 || bios[1] != 0xaa) अणु
		iounmap(bios);
		वापस false;
	पूर्ण
	rdev->bios = kदो_स्मृति(size, GFP_KERNEL);
	अगर (rdev->bios == शून्य) अणु
		iounmap(bios);
		वापस false;
	पूर्ण
	स_नकल_fromio(rdev->bios, bios, size);
	iounmap(bios);
	वापस true;
पूर्ण

अटल bool radeon_पढ़ो_bios(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक8_t __iomem *bios, val1, val2;
	माप_प्रकार size;

	rdev->bios = शून्य;
	/* XXX: some cards may वापस 0 क्रम rom size? ddx has a workaround */
	bios = pci_map_rom(rdev->pdev, &size);
	अगर (!bios) अणु
		वापस false;
	पूर्ण

	val1 = पढ़ोb(&bios[0]);
	val2 = पढ़ोb(&bios[1]);

	अगर (size == 0 || val1 != 0x55 || val2 != 0xaa) अणु
		pci_unmap_rom(rdev->pdev, bios);
		वापस false;
	पूर्ण
	rdev->bios = kzalloc(size, GFP_KERNEL);
	अगर (rdev->bios == शून्य) अणु
		pci_unmap_rom(rdev->pdev, bios);
		वापस false;
	पूर्ण
	स_नकल_fromio(rdev->bios, bios, size);
	pci_unmap_rom(rdev->pdev, bios);
	वापस true;
पूर्ण

अटल bool radeon_पढ़ो_platक्रमm_bios(काष्ठा radeon_device *rdev)
अणु
	phys_addr_t rom = rdev->pdev->rom;
	माप_प्रकार romlen = rdev->pdev->romlen;
	व्योम __iomem *bios;

	rdev->bios = शून्य;

	अगर (!rom || romlen == 0)
		वापस false;

	rdev->bios = kzalloc(romlen, GFP_KERNEL);
	अगर (!rdev->bios)
		वापस false;

	bios = ioremap(rom, romlen);
	अगर (!bios)
		जाओ मुक्त_bios;

	स_नकल_fromio(rdev->bios, bios, romlen);
	iounmap(bios);

	अगर (rdev->bios[0] != 0x55 || rdev->bios[1] != 0xaa)
		जाओ मुक्त_bios;

	वापस true;
मुक्त_bios:
	kमुक्त(rdev->bios);
	वापस false;
पूर्ण

#अगर_घोषित CONFIG_ACPI
/* ATRM is used to get the BIOS on the discrete cards in
 * dual-gpu प्रणालीs.
 */
/* retrieve the ROM in 4k blocks */
#घोषणा ATRM_BIOS_PAGE 4096
/**
 * radeon_atrm_call - fetch a chunk of the vbios
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
अटल पूर्णांक radeon_atrm_call(acpi_handle atrm_handle, uपूर्णांक8_t *bios,
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

अटल bool radeon_atrm_get_bios(काष्ठा radeon_device *rdev)
अणु
	पूर्णांक ret;
	पूर्णांक size = 256 * 1024;
	पूर्णांक i;
	काष्ठा pci_dev *pdev = शून्य;
	acpi_handle dhandle, atrm_handle;
	acpi_status status;
	bool found = false;

	/* ATRM is क्रम the discrete card only */
	अगर (rdev->flags & RADEON_IS_IGP)
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

	rdev->bios = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!rdev->bios) अणु
		DRM_ERROR("Unable to allocate bios\n");
		वापस false;
	पूर्ण

	क्रम (i = 0; i < size / ATRM_BIOS_PAGE; i++) अणु
		ret = radeon_atrm_call(atrm_handle,
				       rdev->bios,
				       (i * ATRM_BIOS_PAGE),
				       ATRM_BIOS_PAGE);
		अगर (ret < ATRM_BIOS_PAGE)
			अवरोध;
	पूर्ण

	अगर (i == 0 || rdev->bios[0] != 0x55 || rdev->bios[1] != 0xaa) अणु
		kमुक्त(rdev->bios);
		वापस false;
	पूर्ण
	वापस true;
पूर्ण
#अन्यथा
अटल अंतरभूत bool radeon_atrm_get_bios(काष्ठा radeon_device *rdev)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल bool ni_पढ़ो_disabled_bios(काष्ठा radeon_device *rdev)
अणु
	u32 bus_cntl;
	u32 d1vga_control;
	u32 d2vga_control;
	u32 vga_render_control;
	u32 rom_cntl;
	bool r;

	bus_cntl = RREG32(R600_BUS_CNTL);
	d1vga_control = RREG32(AVIVO_D1VGA_CONTROL);
	d2vga_control = RREG32(AVIVO_D2VGA_CONTROL);
	vga_render_control = RREG32(AVIVO_VGA_RENDER_CONTROL);
	rom_cntl = RREG32(R600_ROM_CNTL);

	/* enable the rom */
	WREG32(R600_BUS_CNTL, (bus_cntl & ~R600_BIOS_ROM_DIS));
	अगर (!ASIC_IS_NODCE(rdev)) अणु
		/* Disable VGA mode */
		WREG32(AVIVO_D1VGA_CONTROL,
		       (d1vga_control & ~(AVIVO_DVGA_CONTROL_MODE_ENABLE |
					  AVIVO_DVGA_CONTROL_TIMING_SELECT)));
		WREG32(AVIVO_D2VGA_CONTROL,
		       (d2vga_control & ~(AVIVO_DVGA_CONTROL_MODE_ENABLE |
					  AVIVO_DVGA_CONTROL_TIMING_SELECT)));
		WREG32(AVIVO_VGA_RENDER_CONTROL,
		       (vga_render_control & ~AVIVO_VGA_VSTATUS_CNTL_MASK));
	पूर्ण
	WREG32(R600_ROM_CNTL, rom_cntl | R600_SCK_OVERWRITE);

	r = radeon_पढ़ो_bios(rdev);

	/* restore regs */
	WREG32(R600_BUS_CNTL, bus_cntl);
	अगर (!ASIC_IS_NODCE(rdev)) अणु
		WREG32(AVIVO_D1VGA_CONTROL, d1vga_control);
		WREG32(AVIVO_D2VGA_CONTROL, d2vga_control);
		WREG32(AVIVO_VGA_RENDER_CONTROL, vga_render_control);
	पूर्ण
	WREG32(R600_ROM_CNTL, rom_cntl);
	वापस r;
पूर्ण

अटल bool r700_पढ़ो_disabled_bios(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t viph_control;
	uपूर्णांक32_t bus_cntl;
	uपूर्णांक32_t d1vga_control;
	uपूर्णांक32_t d2vga_control;
	uपूर्णांक32_t vga_render_control;
	uपूर्णांक32_t rom_cntl;
	uपूर्णांक32_t cg_spll_func_cntl = 0;
	uपूर्णांक32_t cg_spll_status;
	bool r;

	viph_control = RREG32(RADEON_VIPH_CONTROL);
	bus_cntl = RREG32(R600_BUS_CNTL);
	d1vga_control = RREG32(AVIVO_D1VGA_CONTROL);
	d2vga_control = RREG32(AVIVO_D2VGA_CONTROL);
	vga_render_control = RREG32(AVIVO_VGA_RENDER_CONTROL);
	rom_cntl = RREG32(R600_ROM_CNTL);

	/* disable VIP */
	WREG32(RADEON_VIPH_CONTROL, (viph_control & ~RADEON_VIPH_EN));
	/* enable the rom */
	WREG32(R600_BUS_CNTL, (bus_cntl & ~R600_BIOS_ROM_DIS));
	/* Disable VGA mode */
	WREG32(AVIVO_D1VGA_CONTROL,
	       (d1vga_control & ~(AVIVO_DVGA_CONTROL_MODE_ENABLE |
		AVIVO_DVGA_CONTROL_TIMING_SELECT)));
	WREG32(AVIVO_D2VGA_CONTROL,
	       (d2vga_control & ~(AVIVO_DVGA_CONTROL_MODE_ENABLE |
		AVIVO_DVGA_CONTROL_TIMING_SELECT)));
	WREG32(AVIVO_VGA_RENDER_CONTROL,
	       (vga_render_control & ~AVIVO_VGA_VSTATUS_CNTL_MASK));

	अगर (rdev->family == CHIP_RV730) अणु
		cg_spll_func_cntl = RREG32(R600_CG_SPLL_FUNC_CNTL);

		/* enable bypass mode */
		WREG32(R600_CG_SPLL_FUNC_CNTL, (cg_spll_func_cntl |
						R600_SPLL_BYPASS_EN));

		/* रुको क्रम SPLL_CHG_STATUS to change to 1 */
		cg_spll_status = 0;
		जबतक (!(cg_spll_status & R600_SPLL_CHG_STATUS))
			cg_spll_status = RREG32(R600_CG_SPLL_STATUS);

		WREG32(R600_ROM_CNTL, (rom_cntl & ~R600_SCK_OVERWRITE));
	पूर्ण अन्यथा
		WREG32(R600_ROM_CNTL, (rom_cntl | R600_SCK_OVERWRITE));

	r = radeon_पढ़ो_bios(rdev);

	/* restore regs */
	अगर (rdev->family == CHIP_RV730) अणु
		WREG32(R600_CG_SPLL_FUNC_CNTL, cg_spll_func_cntl);

		/* रुको क्रम SPLL_CHG_STATUS to change to 1 */
		cg_spll_status = 0;
		जबतक (!(cg_spll_status & R600_SPLL_CHG_STATUS))
			cg_spll_status = RREG32(R600_CG_SPLL_STATUS);
	पूर्ण
	WREG32(RADEON_VIPH_CONTROL, viph_control);
	WREG32(R600_BUS_CNTL, bus_cntl);
	WREG32(AVIVO_D1VGA_CONTROL, d1vga_control);
	WREG32(AVIVO_D2VGA_CONTROL, d2vga_control);
	WREG32(AVIVO_VGA_RENDER_CONTROL, vga_render_control);
	WREG32(R600_ROM_CNTL, rom_cntl);
	वापस r;
पूर्ण

अटल bool r600_पढ़ो_disabled_bios(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t viph_control;
	uपूर्णांक32_t bus_cntl;
	uपूर्णांक32_t d1vga_control;
	uपूर्णांक32_t d2vga_control;
	uपूर्णांक32_t vga_render_control;
	uपूर्णांक32_t rom_cntl;
	uपूर्णांक32_t general_pwrmgt;
	uपूर्णांक32_t low_vid_lower_gpio_cntl;
	uपूर्णांक32_t medium_vid_lower_gpio_cntl;
	uपूर्णांक32_t high_vid_lower_gpio_cntl;
	uपूर्णांक32_t ctxsw_vid_lower_gpio_cntl;
	uपूर्णांक32_t lower_gpio_enable;
	bool r;

	viph_control = RREG32(RADEON_VIPH_CONTROL);
	bus_cntl = RREG32(R600_BUS_CNTL);
	d1vga_control = RREG32(AVIVO_D1VGA_CONTROL);
	d2vga_control = RREG32(AVIVO_D2VGA_CONTROL);
	vga_render_control = RREG32(AVIVO_VGA_RENDER_CONTROL);
	rom_cntl = RREG32(R600_ROM_CNTL);
	general_pwrmgt = RREG32(R600_GENERAL_PWRMGT);
	low_vid_lower_gpio_cntl = RREG32(R600_LOW_VID_LOWER_GPIO_CNTL);
	medium_vid_lower_gpio_cntl = RREG32(R600_MEDIUM_VID_LOWER_GPIO_CNTL);
	high_vid_lower_gpio_cntl = RREG32(R600_HIGH_VID_LOWER_GPIO_CNTL);
	ctxsw_vid_lower_gpio_cntl = RREG32(R600_CTXSW_VID_LOWER_GPIO_CNTL);
	lower_gpio_enable = RREG32(R600_LOWER_GPIO_ENABLE);

	/* disable VIP */
	WREG32(RADEON_VIPH_CONTROL, (viph_control & ~RADEON_VIPH_EN));
	/* enable the rom */
	WREG32(R600_BUS_CNTL, (bus_cntl & ~R600_BIOS_ROM_DIS));
	/* Disable VGA mode */
	WREG32(AVIVO_D1VGA_CONTROL,
	       (d1vga_control & ~(AVIVO_DVGA_CONTROL_MODE_ENABLE |
		AVIVO_DVGA_CONTROL_TIMING_SELECT)));
	WREG32(AVIVO_D2VGA_CONTROL,
	       (d2vga_control & ~(AVIVO_DVGA_CONTROL_MODE_ENABLE |
		AVIVO_DVGA_CONTROL_TIMING_SELECT)));
	WREG32(AVIVO_VGA_RENDER_CONTROL,
	       (vga_render_control & ~AVIVO_VGA_VSTATUS_CNTL_MASK));

	WREG32(R600_ROM_CNTL,
	       ((rom_cntl & ~R600_SCK_PRESCALE_CRYSTAL_CLK_MASK) |
		(1 << R600_SCK_PRESCALE_CRYSTAL_CLK_SHIFT) |
		R600_SCK_OVERWRITE));

	WREG32(R600_GENERAL_PWRMGT, (general_pwrmgt & ~R600_OPEN_DRAIN_PADS));
	WREG32(R600_LOW_VID_LOWER_GPIO_CNTL,
	       (low_vid_lower_gpio_cntl & ~0x400));
	WREG32(R600_MEDIUM_VID_LOWER_GPIO_CNTL,
	       (medium_vid_lower_gpio_cntl & ~0x400));
	WREG32(R600_HIGH_VID_LOWER_GPIO_CNTL,
	       (high_vid_lower_gpio_cntl & ~0x400));
	WREG32(R600_CTXSW_VID_LOWER_GPIO_CNTL,
	       (ctxsw_vid_lower_gpio_cntl & ~0x400));
	WREG32(R600_LOWER_GPIO_ENABLE, (lower_gpio_enable | 0x400));

	r = radeon_पढ़ो_bios(rdev);

	/* restore regs */
	WREG32(RADEON_VIPH_CONTROL, viph_control);
	WREG32(R600_BUS_CNTL, bus_cntl);
	WREG32(AVIVO_D1VGA_CONTROL, d1vga_control);
	WREG32(AVIVO_D2VGA_CONTROL, d2vga_control);
	WREG32(AVIVO_VGA_RENDER_CONTROL, vga_render_control);
	WREG32(R600_ROM_CNTL, rom_cntl);
	WREG32(R600_GENERAL_PWRMGT, general_pwrmgt);
	WREG32(R600_LOW_VID_LOWER_GPIO_CNTL, low_vid_lower_gpio_cntl);
	WREG32(R600_MEDIUM_VID_LOWER_GPIO_CNTL, medium_vid_lower_gpio_cntl);
	WREG32(R600_HIGH_VID_LOWER_GPIO_CNTL, high_vid_lower_gpio_cntl);
	WREG32(R600_CTXSW_VID_LOWER_GPIO_CNTL, ctxsw_vid_lower_gpio_cntl);
	WREG32(R600_LOWER_GPIO_ENABLE, lower_gpio_enable);
	वापस r;
पूर्ण

अटल bool avivo_पढ़ो_disabled_bios(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t seprom_cntl1;
	uपूर्णांक32_t viph_control;
	uपूर्णांक32_t bus_cntl;
	uपूर्णांक32_t d1vga_control;
	uपूर्णांक32_t d2vga_control;
	uपूर्णांक32_t vga_render_control;
	uपूर्णांक32_t gpiopad_a;
	uपूर्णांक32_t gpiopad_en;
	uपूर्णांक32_t gpiopad_mask;
	bool r;

	seprom_cntl1 = RREG32(RADEON_SEPROM_CNTL1);
	viph_control = RREG32(RADEON_VIPH_CONTROL);
	bus_cntl = RREG32(RV370_BUS_CNTL);
	d1vga_control = RREG32(AVIVO_D1VGA_CONTROL);
	d2vga_control = RREG32(AVIVO_D2VGA_CONTROL);
	vga_render_control = RREG32(AVIVO_VGA_RENDER_CONTROL);
	gpiopad_a = RREG32(RADEON_GPIOPAD_A);
	gpiopad_en = RREG32(RADEON_GPIOPAD_EN);
	gpiopad_mask = RREG32(RADEON_GPIOPAD_MASK);

	WREG32(RADEON_SEPROM_CNTL1,
	       ((seprom_cntl1 & ~RADEON_SCK_PRESCALE_MASK) |
		(0xc << RADEON_SCK_PRESCALE_SHIFT)));
	WREG32(RADEON_GPIOPAD_A, 0);
	WREG32(RADEON_GPIOPAD_EN, 0);
	WREG32(RADEON_GPIOPAD_MASK, 0);

	/* disable VIP */
	WREG32(RADEON_VIPH_CONTROL, (viph_control & ~RADEON_VIPH_EN));

	/* enable the rom */
	WREG32(RV370_BUS_CNTL, (bus_cntl & ~RV370_BUS_BIOS_DIS_ROM));

	/* Disable VGA mode */
	WREG32(AVIVO_D1VGA_CONTROL,
	       (d1vga_control & ~(AVIVO_DVGA_CONTROL_MODE_ENABLE |
		AVIVO_DVGA_CONTROL_TIMING_SELECT)));
	WREG32(AVIVO_D2VGA_CONTROL,
	       (d2vga_control & ~(AVIVO_DVGA_CONTROL_MODE_ENABLE |
		AVIVO_DVGA_CONTROL_TIMING_SELECT)));
	WREG32(AVIVO_VGA_RENDER_CONTROL,
	       (vga_render_control & ~AVIVO_VGA_VSTATUS_CNTL_MASK));

	r = radeon_पढ़ो_bios(rdev);

	/* restore regs */
	WREG32(RADEON_SEPROM_CNTL1, seprom_cntl1);
	WREG32(RADEON_VIPH_CONTROL, viph_control);
	WREG32(RV370_BUS_CNTL, bus_cntl);
	WREG32(AVIVO_D1VGA_CONTROL, d1vga_control);
	WREG32(AVIVO_D2VGA_CONTROL, d2vga_control);
	WREG32(AVIVO_VGA_RENDER_CONTROL, vga_render_control);
	WREG32(RADEON_GPIOPAD_A, gpiopad_a);
	WREG32(RADEON_GPIOPAD_EN, gpiopad_en);
	WREG32(RADEON_GPIOPAD_MASK, gpiopad_mask);
	वापस r;
पूर्ण

अटल bool legacy_पढ़ो_disabled_bios(काष्ठा radeon_device *rdev)
अणु
	uपूर्णांक32_t seprom_cntl1;
	uपूर्णांक32_t viph_control;
	uपूर्णांक32_t bus_cntl;
	uपूर्णांक32_t crtc_gen_cntl;
	uपूर्णांक32_t crtc2_gen_cntl;
	uपूर्णांक32_t crtc_ext_cntl;
	uपूर्णांक32_t fp2_gen_cntl;
	bool r;

	seprom_cntl1 = RREG32(RADEON_SEPROM_CNTL1);
	viph_control = RREG32(RADEON_VIPH_CONTROL);
	अगर (rdev->flags & RADEON_IS_PCIE)
		bus_cntl = RREG32(RV370_BUS_CNTL);
	अन्यथा
		bus_cntl = RREG32(RADEON_BUS_CNTL);
	crtc_gen_cntl = RREG32(RADEON_CRTC_GEN_CNTL);
	crtc2_gen_cntl = 0;
	crtc_ext_cntl = RREG32(RADEON_CRTC_EXT_CNTL);
	fp2_gen_cntl = 0;

	अगर (rdev->pdev->device == PCI_DEVICE_ID_ATI_RADEON_QY) अणु
		fp2_gen_cntl = RREG32(RADEON_FP2_GEN_CNTL);
	पूर्ण

	अगर (!(rdev->flags & RADEON_SINGLE_CRTC)) अणु
		crtc2_gen_cntl = RREG32(RADEON_CRTC2_GEN_CNTL);
	पूर्ण

	WREG32(RADEON_SEPROM_CNTL1,
	       ((seprom_cntl1 & ~RADEON_SCK_PRESCALE_MASK) |
		(0xc << RADEON_SCK_PRESCALE_SHIFT)));

	/* disable VIP */
	WREG32(RADEON_VIPH_CONTROL, (viph_control & ~RADEON_VIPH_EN));

	/* enable the rom */
	अगर (rdev->flags & RADEON_IS_PCIE)
		WREG32(RV370_BUS_CNTL, (bus_cntl & ~RV370_BUS_BIOS_DIS_ROM));
	अन्यथा
		WREG32(RADEON_BUS_CNTL, (bus_cntl & ~RADEON_BUS_BIOS_DIS_ROM));

	/* Turn off mem requests and CRTC क्रम both controllers */
	WREG32(RADEON_CRTC_GEN_CNTL,
	       ((crtc_gen_cntl & ~RADEON_CRTC_EN) |
		(RADEON_CRTC_DISP_REQ_EN_B |
		 RADEON_CRTC_EXT_DISP_EN)));
	अगर (!(rdev->flags & RADEON_SINGLE_CRTC)) अणु
		WREG32(RADEON_CRTC2_GEN_CNTL,
		       ((crtc2_gen_cntl & ~RADEON_CRTC2_EN) |
			RADEON_CRTC2_DISP_REQ_EN_B));
	पूर्ण
	/* Turn off CRTC */
	WREG32(RADEON_CRTC_EXT_CNTL,
	       ((crtc_ext_cntl & ~RADEON_CRTC_CRT_ON) |
		(RADEON_CRTC_SYNC_TRISTAT |
		 RADEON_CRTC_DISPLAY_DIS)));

	अगर (rdev->pdev->device == PCI_DEVICE_ID_ATI_RADEON_QY) अणु
		WREG32(RADEON_FP2_GEN_CNTL, (fp2_gen_cntl & ~RADEON_FP2_ON));
	पूर्ण

	r = radeon_पढ़ो_bios(rdev);

	/* restore regs */
	WREG32(RADEON_SEPROM_CNTL1, seprom_cntl1);
	WREG32(RADEON_VIPH_CONTROL, viph_control);
	अगर (rdev->flags & RADEON_IS_PCIE)
		WREG32(RV370_BUS_CNTL, bus_cntl);
	अन्यथा
		WREG32(RADEON_BUS_CNTL, bus_cntl);
	WREG32(RADEON_CRTC_GEN_CNTL, crtc_gen_cntl);
	अगर (!(rdev->flags & RADEON_SINGLE_CRTC)) अणु
		WREG32(RADEON_CRTC2_GEN_CNTL, crtc2_gen_cntl);
	पूर्ण
	WREG32(RADEON_CRTC_EXT_CNTL, crtc_ext_cntl);
	अगर (rdev->pdev->device == PCI_DEVICE_ID_ATI_RADEON_QY) अणु
		WREG32(RADEON_FP2_GEN_CNTL, fp2_gen_cntl);
	पूर्ण
	वापस r;
पूर्ण

अटल bool radeon_पढ़ो_disabled_bios(काष्ठा radeon_device *rdev)
अणु
	अगर (rdev->flags & RADEON_IS_IGP)
		वापस igp_पढ़ो_bios_from_vram(rdev);
	अन्यथा अगर (rdev->family >= CHIP_BARTS)
		वापस ni_पढ़ो_disabled_bios(rdev);
	अन्यथा अगर (rdev->family >= CHIP_RV770)
		वापस r700_पढ़ो_disabled_bios(rdev);
	अन्यथा अगर (rdev->family >= CHIP_R600)
		वापस r600_पढ़ो_disabled_bios(rdev);
	अन्यथा अगर (rdev->family >= CHIP_RS600)
		वापस avivo_पढ़ो_disabled_bios(rdev);
	अन्यथा
		वापस legacy_पढ़ो_disabled_bios(rdev);
पूर्ण

#अगर_घोषित CONFIG_ACPI
अटल bool radeon_acpi_vfct_bios(काष्ठा radeon_device *rdev)
अणु
	काष्ठा acpi_table_header *hdr;
	acpi_size tbl_size;
	UEFI_ACPI_VFCT *vfct;
	अचिन्हित offset;

	अगर (!ACPI_SUCCESS(acpi_get_table("VFCT", 1, &hdr)))
		वापस false;
	tbl_size = hdr->length;
	अगर (tbl_size < माप(UEFI_ACPI_VFCT)) अणु
		DRM_ERROR("ACPI VFCT table present but broken (too short #1)\n");
		वापस false;
	पूर्ण

	vfct = (UEFI_ACPI_VFCT *)hdr;
	offset = vfct->VBIOSImageOffset;

	जबतक (offset < tbl_size) अणु
		GOP_VBIOS_CONTENT *vbios = (GOP_VBIOS_CONTENT *)((अक्षर *)hdr + offset);
		VFCT_IMAGE_HEADER *vhdr = &vbios->VbiosHeader;

		offset += माप(VFCT_IMAGE_HEADER);
		अगर (offset > tbl_size) अणु
			DRM_ERROR("ACPI VFCT image header truncated\n");
			वापस false;
		पूर्ण

		offset += vhdr->ImageLength;
		अगर (offset > tbl_size) अणु
			DRM_ERROR("ACPI VFCT image truncated\n");
			वापस false;
		पूर्ण

		अगर (vhdr->ImageLength &&
		    vhdr->PCIBus == rdev->pdev->bus->number &&
		    vhdr->PCIDevice == PCI_SLOT(rdev->pdev->devfn) &&
		    vhdr->PCIFunction == PCI_FUNC(rdev->pdev->devfn) &&
		    vhdr->VenकरोrID == rdev->pdev->venकरोr &&
		    vhdr->DeviceID == rdev->pdev->device) अणु
			rdev->bios = kmemdup(&vbios->VbiosContent,
					     vhdr->ImageLength,
					     GFP_KERNEL);

			अगर (!rdev->bios)
				वापस false;
			वापस true;
		पूर्ण
	पूर्ण

	DRM_ERROR("ACPI VFCT table present but broken (too short #2)\n");
	वापस false;
पूर्ण
#अन्यथा
अटल अंतरभूत bool radeon_acpi_vfct_bios(काष्ठा radeon_device *rdev)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

bool radeon_get_bios(काष्ठा radeon_device *rdev)
अणु
	bool r;
	uपूर्णांक16_t पंचांगp;

	r = radeon_atrm_get_bios(rdev);
	अगर (!r)
		r = radeon_acpi_vfct_bios(rdev);
	अगर (!r)
		r = igp_पढ़ो_bios_from_vram(rdev);
	अगर (!r)
		r = radeon_पढ़ो_bios(rdev);
	अगर (!r)
		r = radeon_पढ़ो_disabled_bios(rdev);
	अगर (!r)
		r = radeon_पढ़ो_platक्रमm_bios(rdev);
	अगर (!r || rdev->bios == शून्य) अणु
		DRM_ERROR("Unable to locate a BIOS ROM\n");
		rdev->bios = शून्य;
		वापस false;
	पूर्ण
	अगर (rdev->bios[0] != 0x55 || rdev->bios[1] != 0xaa) अणु
		prपूर्णांकk("BIOS signature incorrect %x %x\n", rdev->bios[0], rdev->bios[1]);
		जाओ मुक्त_bios;
	पूर्ण

	पंचांगp = RBIOS16(0x18);
	अगर (RBIOS8(पंचांगp + 0x14) != 0x0) अणु
		DRM_INFO("Not an x86 BIOS ROM, not using.\n");
		जाओ मुक्त_bios;
	पूर्ण

	rdev->bios_header_start = RBIOS16(0x48);
	अगर (!rdev->bios_header_start) अणु
		जाओ मुक्त_bios;
	पूर्ण
	पंचांगp = rdev->bios_header_start + 4;
	अगर (!स_भेद(rdev->bios + पंचांगp, "ATOM", 4) ||
	    !स_भेद(rdev->bios + पंचांगp, "MOTA", 4)) अणु
		rdev->is_atom_bios = true;
	पूर्ण अन्यथा अणु
		rdev->is_atom_bios = false;
	पूर्ण

	DRM_DEBUG("%sBIOS detected\n", rdev->is_atom_bios ? "ATOM" : "COM");
	वापस true;
मुक्त_bios:
	kमुक्त(rdev->bios);
	rdev->bios = शून्य;
	वापस false;
पूर्ण
