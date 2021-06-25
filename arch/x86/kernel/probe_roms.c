<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/sched.h>
#समावेश <linux/mm.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/mmzone.h>
#समावेश <linux/ioport.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/console.h>
#समावेश <linux/init.h>
#समावेश <linux/edd.h>
#समावेश <linux/dmi.h>
#समावेश <linux/pfn.h>
#समावेश <linux/pci.h>
#समावेश <linux/export.h>

#समावेश <यंत्र/probe_roms.h>
#समावेश <यंत्र/pci-direct.h>
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/mmzone.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/setup_arch.h>

अटल काष्ठा resource प्रणाली_rom_resource = अणु
	.name	= "System ROM",
	.start	= 0xf0000,
	.end	= 0xfffff,
	.flags	= IORESOURCE_BUSY | IORESOURCE_READONLY | IORESOURCE_MEM
पूर्ण;

अटल काष्ठा resource extension_rom_resource = अणु
	.name	= "Extension ROM",
	.start	= 0xe0000,
	.end	= 0xeffff,
	.flags	= IORESOURCE_BUSY | IORESOURCE_READONLY | IORESOURCE_MEM
पूर्ण;

अटल काष्ठा resource adapter_rom_resources[] = अणु अणु
	.name 	= "Adapter ROM",
	.start	= 0xc8000,
	.end	= 0,
	.flags	= IORESOURCE_BUSY | IORESOURCE_READONLY | IORESOURCE_MEM
पूर्ण, अणु
	.name 	= "Adapter ROM",
	.start	= 0,
	.end	= 0,
	.flags	= IORESOURCE_BUSY | IORESOURCE_READONLY | IORESOURCE_MEM
पूर्ण, अणु
	.name 	= "Adapter ROM",
	.start	= 0,
	.end	= 0,
	.flags	= IORESOURCE_BUSY | IORESOURCE_READONLY | IORESOURCE_MEM
पूर्ण, अणु
	.name 	= "Adapter ROM",
	.start	= 0,
	.end	= 0,
	.flags	= IORESOURCE_BUSY | IORESOURCE_READONLY | IORESOURCE_MEM
पूर्ण, अणु
	.name 	= "Adapter ROM",
	.start	= 0,
	.end	= 0,
	.flags	= IORESOURCE_BUSY | IORESOURCE_READONLY | IORESOURCE_MEM
पूर्ण, अणु
	.name 	= "Adapter ROM",
	.start	= 0,
	.end	= 0,
	.flags	= IORESOURCE_BUSY | IORESOURCE_READONLY | IORESOURCE_MEM
पूर्ण पूर्ण;

अटल काष्ठा resource video_rom_resource = अणु
	.name 	= "Video ROM",
	.start	= 0xc0000,
	.end	= 0xc7fff,
	.flags	= IORESOURCE_BUSY | IORESOURCE_READONLY | IORESOURCE_MEM
पूर्ण;

/* करोes this oprom support the given pci device, or any of the devices
 * that the driver supports?
 */
अटल bool match_id(काष्ठा pci_dev *pdev, अचिन्हित लघु venकरोr, अचिन्हित लघु device)
अणु
	काष्ठा pci_driver *drv = pdev->driver;
	स्थिर काष्ठा pci_device_id *id;

	अगर (pdev->venकरोr == venकरोr && pdev->device == device)
		वापस true;

	क्रम (id = drv ? drv->id_table : शून्य; id && id->venकरोr; id++)
		अगर (id->venकरोr == venकरोr && id->device == device)
			अवरोध;

	वापस id && id->venकरोr;
पूर्ण

अटल bool probe_list(काष्ठा pci_dev *pdev, अचिन्हित लघु venकरोr,
		       स्थिर व्योम *rom_list)
अणु
	अचिन्हित लघु device;

	करो अणु
		अगर (get_kernel_nofault(device, rom_list) != 0)
			device = 0;

		अगर (device && match_id(pdev, venकरोr, device))
			अवरोध;

		rom_list += 2;
	पूर्ण जबतक (device);

	वापस !!device;
पूर्ण

अटल काष्ठा resource *find_oprom(काष्ठा pci_dev *pdev)
अणु
	काष्ठा resource *oprom = शून्य;
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(adapter_rom_resources); i++) अणु
		काष्ठा resource *res = &adapter_rom_resources[i];
		अचिन्हित लघु offset, venकरोr, device, list, rev;
		स्थिर व्योम *rom;

		अगर (res->end == 0)
			अवरोध;

		rom = isa_bus_to_virt(res->start);
		अगर (get_kernel_nofault(offset, rom + 0x18) != 0)
			जारी;

		अगर (get_kernel_nofault(venकरोr, rom + offset + 0x4) != 0)
			जारी;

		अगर (get_kernel_nofault(device, rom + offset + 0x6) != 0)
			जारी;

		अगर (match_id(pdev, venकरोr, device)) अणु
			oprom = res;
			अवरोध;
		पूर्ण

		अगर (get_kernel_nofault(list, rom + offset + 0x8) == 0 &&
		    get_kernel_nofault(rev, rom + offset + 0xc) == 0 &&
		    rev >= 3 && list &&
		    probe_list(pdev, venकरोr, rom + offset + list)) अणु
			oprom = res;
			अवरोध;
		पूर्ण
	पूर्ण

	वापस oprom;
पूर्ण

व्योम __iomem *pci_map_biosrom(काष्ठा pci_dev *pdev)
अणु
	काष्ठा resource *oprom = find_oprom(pdev);

	अगर (!oprom)
		वापस शून्य;

	वापस ioremap(oprom->start, resource_size(oprom));
पूर्ण
EXPORT_SYMBOL(pci_map_biosrom);

व्योम pci_unmap_biosrom(व्योम __iomem *image)
अणु
	iounmap(image);
पूर्ण
EXPORT_SYMBOL(pci_unmap_biosrom);

माप_प्रकार pci_biosrom_size(काष्ठा pci_dev *pdev)
अणु
	काष्ठा resource *oprom = find_oprom(pdev);

	वापस oprom ? resource_size(oprom) : 0;
पूर्ण
EXPORT_SYMBOL(pci_biosrom_size);

#घोषणा ROMSIGNATURE 0xaa55

अटल पूर्णांक __init romsignature(स्थिर अचिन्हित अक्षर *rom)
अणु
	स्थिर अचिन्हित लघु * स्थिर ptr = (स्थिर अचिन्हित लघु *)rom;
	अचिन्हित लघु sig;

	वापस get_kernel_nofault(sig, ptr) == 0 && sig == ROMSIGNATURE;
पूर्ण

अटल पूर्णांक __init romchecksum(स्थिर अचिन्हित अक्षर *rom, अचिन्हित दीर्घ length)
अणु
	अचिन्हित अक्षर sum, c;

	क्रम (sum = 0; length && get_kernel_nofault(c, rom++) == 0; length--)
		sum += c;
	वापस !length && !sum;
पूर्ण

व्योम __init probe_roms(व्योम)
अणु
	स्थिर अचिन्हित अक्षर *rom;
	अचिन्हित दीर्घ start, length, upper;
	अचिन्हित अक्षर c;
	पूर्णांक i;

	/* video rom */
	upper = adapter_rom_resources[0].start;
	क्रम (start = video_rom_resource.start; start < upper; start += 2048) अणु
		rom = isa_bus_to_virt(start);
		अगर (!romsignature(rom))
			जारी;

		video_rom_resource.start = start;

		अगर (get_kernel_nofault(c, rom + 2) != 0)
			जारी;

		/* 0 < length <= 0x7f * 512, historically */
		length = c * 512;

		/* अगर checksum okay, trust length byte */
		अगर (length && romchecksum(rom, length))
			video_rom_resource.end = start + length - 1;

		request_resource(&iomem_resource, &video_rom_resource);
		अवरोध;
	पूर्ण

	start = (video_rom_resource.end + 1 + 2047) & ~2047UL;
	अगर (start < upper)
		start = upper;

	/* प्रणाली rom */
	request_resource(&iomem_resource, &प्रणाली_rom_resource);
	upper = प्रणाली_rom_resource.start;

	/* check क्रम extension rom (ignore length byte!) */
	rom = isa_bus_to_virt(extension_rom_resource.start);
	अगर (romsignature(rom)) अणु
		length = resource_size(&extension_rom_resource);
		अगर (romchecksum(rom, length)) अणु
			request_resource(&iomem_resource, &extension_rom_resource);
			upper = extension_rom_resource.start;
		पूर्ण
	पूर्ण

	/* check क्रम adapter roms on 2k boundaries */
	क्रम (i = 0; i < ARRAY_SIZE(adapter_rom_resources) && start < upper; start += 2048) अणु
		rom = isa_bus_to_virt(start);
		अगर (!romsignature(rom))
			जारी;

		अगर (get_kernel_nofault(c, rom + 2) != 0)
			जारी;

		/* 0 < length <= 0x7f * 512, historically */
		length = c * 512;

		/* but accept any length that fits अगर checksum okay */
		अगर (!length || start + length > upper || !romchecksum(rom, length))
			जारी;

		adapter_rom_resources[i].start = start;
		adapter_rom_resources[i].end = start + length - 1;
		request_resource(&iomem_resource, &adapter_rom_resources[i]);

		start = adapter_rom_resources[i++].end & ~2047UL;
	पूर्ण
पूर्ण

