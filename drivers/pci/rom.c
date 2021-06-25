<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * PCI ROM access routines
 *
 * (C) Copyright 2004 Jon Smirl <jonsmirl@yahoo.com>
 * (C) Copyright 2004 Silicon Graphics, Inc. Jesse Barnes <jbarnes@sgi.com>
 */
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>

#समावेश "pci.h"

/**
 * pci_enable_rom - enable ROM decoding क्रम a PCI device
 * @pdev: PCI device to enable
 *
 * Enable ROM decoding on @dev.  This involves simply turning on the last
 * bit of the PCI ROM BAR.  Note that some cards may share address decoders
 * between the ROM and other resources, so enabling it may disable access
 * to MMIO रेजिस्टरs or other card memory.
 */
पूर्णांक pci_enable_rom(काष्ठा pci_dev *pdev)
अणु
	काष्ठा resource *res = &pdev->resource[PCI_ROM_RESOURCE];
	काष्ठा pci_bus_region region;
	u32 rom_addr;

	अगर (!res->flags)
		वापस -1;

	/* Nothing to enable अगर we're using a shaकरोw copy in RAM */
	अगर (res->flags & IORESOURCE_ROM_SHADOW)
		वापस 0;

	/*
	 * Ideally pci_update_resource() would update the ROM BAR address,
	 * and we would only set the enable bit here.  But apparently some
	 * devices have buggy ROM BARs that पढ़ो as zero when disabled.
	 */
	pcibios_resource_to_bus(pdev->bus, &region, res);
	pci_पढ़ो_config_dword(pdev, pdev->rom_base_reg, &rom_addr);
	rom_addr &= ~PCI_ROM_ADDRESS_MASK;
	rom_addr |= region.start | PCI_ROM_ADDRESS_ENABLE;
	pci_ग_लिखो_config_dword(pdev, pdev->rom_base_reg, rom_addr);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(pci_enable_rom);

/**
 * pci_disable_rom - disable ROM decoding क्रम a PCI device
 * @pdev: PCI device to disable
 *
 * Disable ROM decoding on a PCI device by turning off the last bit in the
 * ROM BAR.
 */
व्योम pci_disable_rom(काष्ठा pci_dev *pdev)
अणु
	काष्ठा resource *res = &pdev->resource[PCI_ROM_RESOURCE];
	u32 rom_addr;

	अगर (res->flags & IORESOURCE_ROM_SHADOW)
		वापस;

	pci_पढ़ो_config_dword(pdev, pdev->rom_base_reg, &rom_addr);
	rom_addr &= ~PCI_ROM_ADDRESS_ENABLE;
	pci_ग_लिखो_config_dword(pdev, pdev->rom_base_reg, rom_addr);
पूर्ण
EXPORT_SYMBOL_GPL(pci_disable_rom);

/**
 * pci_get_rom_size - obtain the actual size of the ROM image
 * @pdev: target PCI device
 * @rom: kernel भव poपूर्णांकer to image of ROM
 * @size: size of PCI winकरोw
 *  वापस: size of actual ROM image
 *
 * Determine the actual length of the ROM image.
 * The PCI winकरोw size could be much larger than the
 * actual image size.
 */
अटल माप_प्रकार pci_get_rom_size(काष्ठा pci_dev *pdev, व्योम __iomem *rom,
			       माप_प्रकार size)
अणु
	व्योम __iomem *image;
	पूर्णांक last_image;
	अचिन्हित length;

	image = rom;
	करो अणु
		व्योम __iomem *pds;
		/* Standard PCI ROMs start out with these bytes 55 AA */
		अगर (पढ़ोw(image) != 0xAA55) अणु
			pci_info(pdev, "Invalid PCI ROM header signature: expecting 0xaa55, got %#06x\n",
				 पढ़ोw(image));
			अवरोध;
		पूर्ण
		/* get the PCI data काष्ठाure and check its "PCIR" signature */
		pds = image + पढ़ोw(image + 24);
		अगर (पढ़ोl(pds) != 0x52494350) अणु
			pci_info(pdev, "Invalid PCI ROM data signature: expecting 0x52494350, got %#010x\n",
				 पढ़ोl(pds));
			अवरोध;
		पूर्ण
		last_image = पढ़ोb(pds + 21) & 0x80;
		length = पढ़ोw(pds + 16);
		image += length * 512;
		/* Aव्योम iterating through memory outside the resource winकरोw */
		अगर (image >= rom + size)
			अवरोध;
		अगर (!last_image) अणु
			अगर (पढ़ोw(image) != 0xAA55) अणु
				pci_info(pdev, "No more image in the PCI ROM\n");
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण जबतक (length && !last_image);

	/* never वापस a size larger than the PCI resource winकरोw */
	/* there are known ROMs that get the size wrong */
	वापस min((माप_प्रकार)(image - rom), size);
पूर्ण

/**
 * pci_map_rom - map a PCI ROM to kernel space
 * @pdev: poपूर्णांकer to pci device काष्ठा
 * @size: poपूर्णांकer to receive size of pci winकरोw over ROM
 *
 * Return: kernel भव poपूर्णांकer to image of ROM
 *
 * Map a PCI ROM पूर्णांकo kernel space. If ROM is boot video ROM,
 * the shaकरोw BIOS copy will be वापसed instead of the
 * actual ROM.
 */
व्योम __iomem *pci_map_rom(काष्ठा pci_dev *pdev, माप_प्रकार *size)
अणु
	काष्ठा resource *res = &pdev->resource[PCI_ROM_RESOURCE];
	loff_t start;
	व्योम __iomem *rom;

	/* assign the ROM an address अगर it करोesn't have one */
	अगर (res->parent == शून्य && pci_assign_resource(pdev, PCI_ROM_RESOURCE))
		वापस शून्य;

	start = pci_resource_start(pdev, PCI_ROM_RESOURCE);
	*size = pci_resource_len(pdev, PCI_ROM_RESOURCE);
	अगर (*size == 0)
		वापस शून्य;

	/* Enable ROM space decodes */
	अगर (pci_enable_rom(pdev))
		वापस शून्य;

	rom = ioremap(start, *size);
	अगर (!rom)
		जाओ err_ioremap;

	/*
	 * Try to find the true size of the ROM since someबार the PCI winकरोw
	 * size is much larger than the actual size of the ROM.
	 * True size is important अगर the ROM is going to be copied.
	 */
	*size = pci_get_rom_size(pdev, rom, *size);
	अगर (!*size)
		जाओ invalid_rom;

	वापस rom;

invalid_rom:
	iounmap(rom);
err_ioremap:
	/* restore enable अगर ioremap fails */
	अगर (!(res->flags & IORESOURCE_ROM_ENABLE))
		pci_disable_rom(pdev);
	वापस शून्य;
पूर्ण
EXPORT_SYMBOL(pci_map_rom);

/**
 * pci_unmap_rom - unmap the ROM from kernel space
 * @pdev: poपूर्णांकer to pci device काष्ठा
 * @rom: भव address of the previous mapping
 *
 * Remove a mapping of a previously mapped ROM
 */
व्योम pci_unmap_rom(काष्ठा pci_dev *pdev, व्योम __iomem *rom)
अणु
	काष्ठा resource *res = &pdev->resource[PCI_ROM_RESOURCE];

	iounmap(rom);

	/* Disable again beक्रमe continuing */
	अगर (!(res->flags & IORESOURCE_ROM_ENABLE))
		pci_disable_rom(pdev);
पूर्ण
EXPORT_SYMBOL(pci_unmap_rom);
