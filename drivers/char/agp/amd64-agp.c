<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2001-2003 SuSE Lअसल.
 * Distributed under the GNU खुला license, v2.
 *
 * This is a GART driver क्रम the AMD Opteron/Athlon64 on-CPU northbridge.
 * It also includes support क्रम the AMD 8151 AGP bridge,
 * although it करोesn't actually करो much, as all the real
 * work is करोne in the northbridge(s).
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/agp_backend.h>
#समावेश <linux/mmzone.h>
#समावेश <यंत्र/page.h>		/* PAGE_SIZE */
#समावेश <यंत्र/e820/api.h>
#समावेश <यंत्र/amd_nb.h>
#समावेश <यंत्र/gart.h>
#समावेश "agp.h"

/* NVIDIA K8 रेजिस्टरs */
#घोषणा NVIDIA_X86_64_0_APBASE		0x10
#घोषणा NVIDIA_X86_64_1_APBASE1		0x50
#घोषणा NVIDIA_X86_64_1_APLIMIT1	0x54
#घोषणा NVIDIA_X86_64_1_APSIZE		0xa8
#घोषणा NVIDIA_X86_64_1_APBASE2		0xd8
#घोषणा NVIDIA_X86_64_1_APLIMIT2	0xdc

/* ULi K8 रेजिस्टरs */
#घोषणा ULI_X86_64_BASE_ADDR		0x10
#घोषणा ULI_X86_64_HTT_FEA_REG		0x50
#घोषणा ULI_X86_64_ENU_SCR_REG		0x54

अटल काष्ठा resource *aperture_resource;
अटल bool __initdata agp_try_unsupported = 1;
अटल पूर्णांक agp_bridges_found;

अटल व्योम amd64_tlbflush(काष्ठा agp_memory *temp)
अणु
	amd_flush_garts();
पूर्ण

अटल पूर्णांक amd64_insert_memory(काष्ठा agp_memory *mem, off_t pg_start, पूर्णांक type)
अणु
	पूर्णांक i, j, num_entries;
	दीर्घ दीर्घ पंचांगp;
	पूर्णांक mask_type;
	काष्ठा agp_bridge_data *bridge = mem->bridge;
	u32 pte;

	num_entries = agp_num_entries();

	अगर (type != mem->type)
		वापस -EINVAL;
	mask_type = bridge->driver->agp_type_to_mask_type(bridge, type);
	अगर (mask_type != 0)
		वापस -EINVAL;


	/* Make sure we can fit the range in the gatt table. */
	/* FIXME: could wrap */
	अगर (((अचिन्हित दीर्घ)pg_start + mem->page_count) > num_entries)
		वापस -EINVAL;

	j = pg_start;

	/* gatt table should be empty. */
	जबतक (j < (pg_start + mem->page_count)) अणु
		अगर (!PGE_EMPTY(agp_bridge, पढ़ोl(agp_bridge->gatt_table+j)))
			वापस -EBUSY;
		j++;
	पूर्ण

	अगर (!mem->is_flushed) अणु
		global_cache_flush();
		mem->is_flushed = true;
	पूर्ण

	क्रम (i = 0, j = pg_start; i < mem->page_count; i++, j++) अणु
		पंचांगp = agp_bridge->driver->mask_memory(agp_bridge,
						      page_to_phys(mem->pages[i]),
						      mask_type);

		BUG_ON(पंचांगp & 0xffffff0000000ffcULL);
		pte = (पंचांगp & 0x000000ff00000000ULL) >> 28;
		pte |=(पंचांगp & 0x00000000fffff000ULL);
		pte |= GPTE_VALID | GPTE_COHERENT;

		ग_लिखोl(pte, agp_bridge->gatt_table+j);
		पढ़ोl(agp_bridge->gatt_table+j);	/* PCI Posting. */
	पूर्ण
	amd64_tlbflush(mem);
	वापस 0;
पूर्ण

/*
 * This hack alters the order element according
 * to the size of a दीर्घ. It sucks. I totally disown this, even
 * though it करोes appear to work क्रम the most part.
 */
अटल काष्ठा aper_size_info_32 amd64_aperture_sizes[7] =
अणु
	अणु32,   8192,   3+(माप(दीर्घ)/8), 0 पूर्ण,
	अणु64,   16384,  4+(माप(दीर्घ)/8), 1<<1 पूर्ण,
	अणु128,  32768,  5+(माप(दीर्घ)/8), 1<<2 पूर्ण,
	अणु256,  65536,  6+(माप(दीर्घ)/8), 1<<1 | 1<<2 पूर्ण,
	अणु512,  131072, 7+(माप(दीर्घ)/8), 1<<3 पूर्ण,
	अणु1024, 262144, 8+(माप(दीर्घ)/8), 1<<1 | 1<<3पूर्ण,
	अणु2048, 524288, 9+(माप(दीर्घ)/8), 1<<2 | 1<<3पूर्ण
पूर्ण;


/*
 * Get the current Aperture size from the x86-64.
 * Note, that there may be multiple x86-64's, but we just वापस
 * the value from the first one we find. The set_size functions
 * keep the rest coherent anyway. Or at least should करो.
 */
अटल पूर्णांक amd64_fetch_size(व्योम)
अणु
	काष्ठा pci_dev *dev;
	पूर्णांक i;
	u32 temp;
	काष्ठा aper_size_info_32 *values;

	dev = node_to_amd_nb(0)->misc;
	अगर (dev==शून्य)
		वापस 0;

	pci_पढ़ो_config_dword(dev, AMD64_GARTAPERTURECTL, &temp);
	temp = (temp & 0xe);
	values = A_SIZE_32(amd64_aperture_sizes);

	क्रम (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++) अणु
		अगर (temp == values[i].size_value) अणु
			agp_bridge->previous_size =
			    agp_bridge->current_size = (व्योम *) (values + i);

			agp_bridge->aperture_size_idx = i;
			वापस values[i].size;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/*
 * In a multiprocessor x86-64 प्रणाली, this function माला_लो
 * called once क्रम each CPU.
 */
अटल u64 amd64_configure(काष्ठा pci_dev *hammer, u64 gatt_table)
अणु
	u64 aperturebase;
	u32 पंचांगp;
	u64 aper_base;

	/* Address to map to */
	pci_पढ़ो_config_dword(hammer, AMD64_GARTAPERTUREBASE, &पंचांगp);
	aperturebase = (u64)पंचांगp << 25;
	aper_base = (aperturebase & PCI_BASE_ADDRESS_MEM_MASK);

	enable_gart_translation(hammer, gatt_table);

	वापस aper_base;
पूर्ण


अटल स्थिर काष्ठा aper_size_info_32 amd_8151_sizes[7] =
अणु
	अणु2048, 524288, 9, 0x00000000 पूर्ण,	/* 0 0 0 0 0 0 */
	अणु1024, 262144, 8, 0x00000400 पूर्ण,	/* 1 0 0 0 0 0 */
	अणु512,  131072, 7, 0x00000600 पूर्ण,	/* 1 1 0 0 0 0 */
	अणु256,  65536,  6, 0x00000700 पूर्ण,	/* 1 1 1 0 0 0 */
	अणु128,  32768,  5, 0x00000720 पूर्ण,	/* 1 1 1 1 0 0 */
	अणु64,   16384,  4, 0x00000730 पूर्ण,	/* 1 1 1 1 1 0 */
	अणु32,   8192,   3, 0x00000738 पूर्ण	/* 1 1 1 1 1 1 */
पूर्ण;

अटल पूर्णांक amd_8151_configure(व्योम)
अणु
	अचिन्हित दीर्घ gatt_bus = virt_to_phys(agp_bridge->gatt_table_real);
	पूर्णांक i;

	अगर (!amd_nb_has_feature(AMD_NB_GART))
		वापस 0;

	/* Configure AGP regs in each x86-64 host bridge. */
	क्रम (i = 0; i < amd_nb_num(); i++) अणु
		agp_bridge->gart_bus_addr =
			amd64_configure(node_to_amd_nb(i)->misc, gatt_bus);
	पूर्ण
	amd_flush_garts();
	वापस 0;
पूर्ण


अटल व्योम amd64_cleanup(व्योम)
अणु
	u32 पंचांगp;
	पूर्णांक i;

	अगर (!amd_nb_has_feature(AMD_NB_GART))
		वापस;

	क्रम (i = 0; i < amd_nb_num(); i++) अणु
		काष्ठा pci_dev *dev = node_to_amd_nb(i)->misc;
		/* disable gart translation */
		pci_पढ़ो_config_dword(dev, AMD64_GARTAPERTURECTL, &पंचांगp);
		पंचांगp &= ~GARTEN;
		pci_ग_लिखो_config_dword(dev, AMD64_GARTAPERTURECTL, पंचांगp);
	पूर्ण
पूर्ण


अटल स्थिर काष्ठा agp_bridge_driver amd_8151_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= amd_8151_sizes,
	.माप_प्रकारype		= U32_APER_SIZE,
	.num_aperture_sizes	= 7,
	.needs_scratch_page	= true,
	.configure		= amd_8151_configure,
	.fetch_size		= amd64_fetch_size,
	.cleanup		= amd64_cleanup,
	.tlb_flush		= amd64_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= शून्य,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= agp_generic_create_gatt_table,
	.मुक्त_gatt_table	= agp_generic_मुक्त_gatt_table,
	.insert_memory		= amd64_insert_memory,
	.हटाओ_memory		= agp_generic_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages	= agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages	= agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

/* Some basic sanity checks क्रम the aperture. */
अटल पूर्णांक agp_aperture_valid(u64 aper, u32 size)
अणु
	अगर (!aperture_valid(aper, size, 32*1024*1024))
		वापस 0;

	/* Request the Aperture. This catches हालs when someone अन्यथा
	   alपढ़ोy put a mapping in there - happens with some very broken BIOS

	   Maybe better to use pci_assign_resource/pci_enable_device instead
	   trusting the bridges? */
	अगर (!aperture_resource &&
	    !(aperture_resource = request_mem_region(aper, size, "aperture"))) अणु
		prपूर्णांकk(KERN_ERR PFX "Aperture conflicts with PCI mapping.\n");
		वापस 0;
	पूर्ण
	वापस 1;
पूर्ण

/*
 * W*s centric BIOS someबार only set up the aperture in the AGP
 * bridge, not the northbridge. On AMD64 this is handled early
 * in aperture.c, but when IOMMU is not enabled or we run
 * on a 32bit kernel this needs to be reकरोne.
 * Unक्रमtunately it is impossible to fix the aperture here because it's too late
 * to allocate that much memory. But at least error out cleanly instead of
 * crashing.
 */
अटल पूर्णांक fix_northbridge(काष्ठा pci_dev *nb, काष्ठा pci_dev *agp, u16 cap)
अणु
	u64 aper, nb_aper;
	पूर्णांक order = 0;
	u32 nb_order, nb_base;
	u16 apsize;

	pci_पढ़ो_config_dword(nb, AMD64_GARTAPERTURECTL, &nb_order);
	nb_order = (nb_order >> 1) & 7;
	pci_पढ़ो_config_dword(nb, AMD64_GARTAPERTUREBASE, &nb_base);
	nb_aper = (u64)nb_base << 25;

	/* Northbridge seems to contain crap. Try the AGP bridge. */

	pci_पढ़ो_config_word(agp, cap+0x14, &apsize);
	अगर (apsize == 0xffff) अणु
		अगर (agp_aperture_valid(nb_aper, (32*1024*1024)<<nb_order))
			वापस 0;
		वापस -1;
	पूर्ण

	apsize &= 0xfff;
	/* Some BIOS use weird encodings not in the AGPv3 table. */
	अगर (apsize & 0xff)
		apsize |= 0xf00;
	order = 7 - hweight16(apsize);

	aper = pci_bus_address(agp, AGP_APERTURE_BAR);

	/*
	 * On some sick chips APSIZE is 0. This means it wants 4G
	 * so let द्विगुन check that order, and lets trust the AMD NB settings
	 */
	अगर (order >=0 && aper + (32ULL<<(20 + order)) > 0x100000000ULL) अणु
		dev_info(&agp->dev, "aperture size %u MB is not right, using settings from NB\n",
			 32 << order);
		order = nb_order;
	पूर्ण

	अगर (nb_order >= order) अणु
		अगर (agp_aperture_valid(nb_aper, (32*1024*1024)<<nb_order))
			वापस 0;
	पूर्ण

	dev_info(&agp->dev, "aperture from AGP @ %Lx size %u MB\n",
		 aper, 32 << order);
	अगर (order < 0 || !agp_aperture_valid(aper, (32*1024*1024)<<order))
		वापस -1;

	gart_set_size_and_enable(nb, order);
	pci_ग_लिखो_config_dword(nb, AMD64_GARTAPERTUREBASE, aper >> 25);

	वापस 0;
पूर्ण

अटल पूर्णांक cache_nbs(काष्ठा pci_dev *pdev, u32 cap_ptr)
अणु
	पूर्णांक i;

	अगर (amd_cache_northbridges() < 0)
		वापस -ENODEV;

	अगर (!amd_nb_has_feature(AMD_NB_GART))
		वापस -ENODEV;

	i = 0;
	क्रम (i = 0; i < amd_nb_num(); i++) अणु
		काष्ठा pci_dev *dev = node_to_amd_nb(i)->misc;
		अगर (fix_northbridge(dev, pdev, cap_ptr) < 0) अणु
			dev_err(&dev->dev, "no usable aperture found\n");
#अगर_घोषित __x86_64__
			/* should port this to i386 */
			dev_err(&dev->dev, "consider rebooting with iommu=memaper=2 to get a good aperture\n");
#पूर्ण_अगर
			वापस -1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Handle AMD 8151 quirks */
अटल व्योम amd8151_init(काष्ठा pci_dev *pdev, काष्ठा agp_bridge_data *bridge)
अणु
	अक्षर *revstring;

	चयन (pdev->revision) अणु
	हाल 0x01: revstring="A0"; अवरोध;
	हाल 0x02: revstring="A1"; अवरोध;
	हाल 0x11: revstring="B0"; अवरोध;
	हाल 0x12: revstring="B1"; अवरोध;
	हाल 0x13: revstring="B2"; अवरोध;
	हाल 0x14: revstring="B3"; अवरोध;
	शेष:   revstring="??"; अवरोध;
	पूर्ण

	dev_info(&pdev->dev, "AMD 8151 AGP Bridge rev %s\n", revstring);

	/*
	 * Work around errata.
	 * Chips beक्रमe B2 stepping incorrectly reporting v3.5
	 */
	अगर (pdev->revision < 0x13) अणु
		dev_info(&pdev->dev, "correcting AGP revision (reports 3.5, is really 3.0)\n");
		bridge->major_version = 3;
		bridge->minor_version = 0;
	पूर्ण
पूर्ण


अटल स्थिर काष्ठा aper_size_info_32 uli_sizes[7] =
अणु
	अणु256, 65536, 6, 10पूर्ण,
	अणु128, 32768, 5, 9पूर्ण,
	अणु64, 16384, 4, 8पूर्ण,
	अणु32, 8192, 3, 7पूर्ण,
	अणु16, 4096, 2, 6पूर्ण,
	अणु8, 2048, 1, 4पूर्ण,
	अणु4, 1024, 0, 3पूर्ण
पूर्ण;
अटल पूर्णांक uli_agp_init(काष्ठा pci_dev *pdev)
अणु
	u32 httfea,baseaddr,enuscr;
	काष्ठा pci_dev *dev1;
	पूर्णांक i, ret;
	अचिन्हित size = amd64_fetch_size();

	dev_info(&pdev->dev, "setting up ULi AGP\n");
	dev1 = pci_get_slot (pdev->bus,PCI_DEVFN(0,0));
	अगर (dev1 == शून्य) अणु
		dev_info(&pdev->dev, "can't find ULi secondary device\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(uli_sizes); i++)
		अगर (uli_sizes[i].size == size)
			अवरोध;

	अगर (i == ARRAY_SIZE(uli_sizes)) अणु
		dev_info(&pdev->dev, "no ULi size found for %d\n", size);
		ret = -ENODEV;
		जाओ put;
	पूर्ण

	/* shaकरोw x86-64 रेजिस्टरs पूर्णांकo ULi रेजिस्टरs */
	pci_पढ़ो_config_dword (node_to_amd_nb(0)->misc, AMD64_GARTAPERTUREBASE,
			       &httfea);

	/* अगर x86-64 aperture base is beyond 4G, निकास here */
	अगर ((httfea & 0x7fff) >> (32 - 25)) अणु
		ret = -ENODEV;
		जाओ put;
	पूर्ण

	httfea = (httfea& 0x7fff) << 25;

	pci_पढ़ो_config_dword(pdev, ULI_X86_64_BASE_ADDR, &baseaddr);
	baseaddr&= ~PCI_BASE_ADDRESS_MEM_MASK;
	baseaddr|= httfea;
	pci_ग_लिखो_config_dword(pdev, ULI_X86_64_BASE_ADDR, baseaddr);

	enuscr= httfea+ (size * 1024 * 1024) - 1;
	pci_ग_लिखो_config_dword(dev1, ULI_X86_64_HTT_FEA_REG, httfea);
	pci_ग_लिखो_config_dword(dev1, ULI_X86_64_ENU_SCR_REG, enuscr);
	ret = 0;
put:
	pci_dev_put(dev1);
	वापस ret;
पूर्ण


अटल स्थिर काष्ठा aper_size_info_32 nक्रमce3_sizes[5] =
अणु
	अणु512,  131072, 7, 0x00000000 पूर्ण,
	अणु256,  65536,  6, 0x00000008 पूर्ण,
	अणु128,  32768,  5, 0x0000000C पूर्ण,
	अणु64,   16384,  4, 0x0000000E पूर्ण,
	अणु32,   8192,   3, 0x0000000F पूर्ण
पूर्ण;

/* Handle shaकरोw device of the Nvidia NForce3 */
/* CHECK-ME original 2.4 version set up some IORRs. Check अगर that is needed. */
अटल पूर्णांक nक्रमce3_agp_init(काष्ठा pci_dev *pdev)
अणु
	u32 पंचांगp, apbase, apbar, aplimit;
	काष्ठा pci_dev *dev1;
	पूर्णांक i, ret;
	अचिन्हित size = amd64_fetch_size();

	dev_info(&pdev->dev, "setting up Nforce3 AGP\n");

	dev1 = pci_get_slot(pdev->bus, PCI_DEVFN(11, 0));
	अगर (dev1 == शून्य) अणु
		dev_info(&pdev->dev, "can't find Nforce3 secondary device\n");
		वापस -ENODEV;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(nक्रमce3_sizes); i++)
		अगर (nक्रमce3_sizes[i].size == size)
			अवरोध;

	अगर (i == ARRAY_SIZE(nक्रमce3_sizes)) अणु
		dev_info(&pdev->dev, "no NForce3 size found for %d\n", size);
		ret = -ENODEV;
		जाओ put;
	पूर्ण

	pci_पढ़ो_config_dword(dev1, NVIDIA_X86_64_1_APSIZE, &पंचांगp);
	पंचांगp &= ~(0xf);
	पंचांगp |= nक्रमce3_sizes[i].size_value;
	pci_ग_लिखो_config_dword(dev1, NVIDIA_X86_64_1_APSIZE, पंचांगp);

	/* shaकरोw x86-64 रेजिस्टरs पूर्णांकo NVIDIA रेजिस्टरs */
	pci_पढ़ो_config_dword (node_to_amd_nb(0)->misc, AMD64_GARTAPERTUREBASE,
			       &apbase);

	/* अगर x86-64 aperture base is beyond 4G, निकास here */
	अगर ( (apbase & 0x7fff) >> (32 - 25) ) अणु
		dev_info(&pdev->dev, "aperture base > 4G\n");
		ret = -ENODEV;
		जाओ put;
	पूर्ण

	apbase = (apbase & 0x7fff) << 25;

	pci_पढ़ो_config_dword(pdev, NVIDIA_X86_64_0_APBASE, &apbar);
	apbar &= ~PCI_BASE_ADDRESS_MEM_MASK;
	apbar |= apbase;
	pci_ग_लिखो_config_dword(pdev, NVIDIA_X86_64_0_APBASE, apbar);

	aplimit = apbase + (size * 1024 * 1024) - 1;
	pci_ग_लिखो_config_dword(dev1, NVIDIA_X86_64_1_APBASE1, apbase);
	pci_ग_लिखो_config_dword(dev1, NVIDIA_X86_64_1_APLIMIT1, aplimit);
	pci_ग_लिखो_config_dword(dev1, NVIDIA_X86_64_1_APBASE2, apbase);
	pci_ग_लिखो_config_dword(dev1, NVIDIA_X86_64_1_APLIMIT2, aplimit);

	ret = 0;
put:
	pci_dev_put(dev1);

	वापस ret;
पूर्ण

अटल पूर्णांक agp_amd64_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा agp_bridge_data *bridge;
	u8 cap_ptr;
	पूर्णांक err;

	/* The Highlander principle */
	अगर (agp_bridges_found)
		वापस -ENODEV;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);
	अगर (!cap_ptr)
		वापस -ENODEV;

	/* Could check क्रम AGPv3 here */

	bridge = agp_alloc_bridge();
	अगर (!bridge)
		वापस -ENOMEM;

	अगर (pdev->venकरोr == PCI_VENDOR_ID_AMD &&
	    pdev->device == PCI_DEVICE_ID_AMD_8151_0) अणु
		amd8151_init(pdev, bridge);
	पूर्ण अन्यथा अणु
		dev_info(&pdev->dev, "AGP bridge [%04x/%04x]\n",
			 pdev->venकरोr, pdev->device);
	पूर्ण

	bridge->driver = &amd_8151_driver;
	bridge->dev = pdev;
	bridge->capndx = cap_ptr;

	/* Fill in the mode रेजिस्टर */
	pci_पढ़ो_config_dword(pdev, bridge->capndx+PCI_AGP_STATUS, &bridge->mode);

	अगर (cache_nbs(pdev, cap_ptr) == -1) अणु
		agp_put_bridge(bridge);
		वापस -ENODEV;
	पूर्ण

	अगर (pdev->venकरोr == PCI_VENDOR_ID_NVIDIA) अणु
		पूर्णांक ret = nक्रमce3_agp_init(pdev);
		अगर (ret) अणु
			agp_put_bridge(bridge);
			वापस ret;
		पूर्ण
	पूर्ण

	अगर (pdev->venकरोr == PCI_VENDOR_ID_AL) अणु
		पूर्णांक ret = uli_agp_init(pdev);
		अगर (ret) अणु
			agp_put_bridge(bridge);
			वापस ret;
		पूर्ण
	पूर्ण

	pci_set_drvdata(pdev, bridge);
	err = agp_add_bridge(bridge);
	अगर (err < 0)
		वापस err;

	agp_bridges_found++;
	वापस 0;
पूर्ण

अटल व्योम agp_amd64_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge = pci_get_drvdata(pdev);

	release_mem_region(virt_to_phys(bridge->gatt_table_real),
			   amd64_aperture_sizes[bridge->aperture_size_idx].size);
	agp_हटाओ_bridge(bridge);
	agp_put_bridge(bridge);

	agp_bridges_found--;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक agp_amd64_suspend(काष्ठा pci_dev *pdev, pm_message_t state)
अणु
	pci_save_state(pdev);
	pci_set_घातer_state(pdev, pci_choose_state(pdev, state));

	वापस 0;
पूर्ण

अटल पूर्णांक agp_amd64_resume(काष्ठा pci_dev *pdev)
अणु
	pci_set_घातer_state(pdev, PCI_D0);
	pci_restore_state(pdev);

	अगर (pdev->venकरोr == PCI_VENDOR_ID_NVIDIA)
		nक्रमce3_agp_init(pdev);

	वापस amd_8151_configure();
पूर्ण

#पूर्ण_अगर /* CONFIG_PM */

अटल स्थिर काष्ठा pci_device_id agp_amd64_pci_table[] = अणु
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_AMD,
	.device		= PCI_DEVICE_ID_AMD_8151_0,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	/* ULi M1689 */
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_AL,
	.device		= PCI_DEVICE_ID_AL_M1689,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	/* VIA K8T800Pro */
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_VIA,
	.device		= PCI_DEVICE_ID_VIA_K8T800PRO_0,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	/* VIA K8T800 */
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_VIA,
	.device		= PCI_DEVICE_ID_VIA_8385_0,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	/* VIA K8M800 / K8N800 */
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_VIA,
	.device		= PCI_DEVICE_ID_VIA_8380_0,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	/* VIA K8M890 / K8N890 */
	अणु
	.class          = (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask     = ~0,
	.venकरोr         = PCI_VENDOR_ID_VIA,
	.device         = PCI_DEVICE_ID_VIA_VT3336,
	.subvenकरोr      = PCI_ANY_ID,
	.subdevice      = PCI_ANY_ID,
	पूर्ण,
	/* VIA K8T890 */
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_VIA,
	.device		= PCI_DEVICE_ID_VIA_3238_0,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	/* VIA K8T800/K8M800/K8N800 */
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_VIA,
	.device		= PCI_DEVICE_ID_VIA_838X_1,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	/* NForce3 */
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_NVIDIA,
	.device		= PCI_DEVICE_ID_NVIDIA_NFORCE3,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_NVIDIA,
	.device		= PCI_DEVICE_ID_NVIDIA_NFORCE3S,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	/* SIS 755 */
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_SI,
	.device		= PCI_DEVICE_ID_SI_755,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	/* SIS 760 */
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_SI,
	.device		= PCI_DEVICE_ID_SI_760,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,
	/* ALI/ULI M1695 */
	अणु
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),
	.class_mask	= ~0,
	.venकरोr		= PCI_VENDOR_ID_AL,
	.device		= 0x1695,
	.subvenकरोr	= PCI_ANY_ID,
	.subdevice	= PCI_ANY_ID,
	पूर्ण,

	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, agp_amd64_pci_table);

अटल स्थिर काष्ठा pci_device_id agp_amd64_pci_promisc_table[] = अणु
	अणु PCI_DEVICE_CLASS(0, 0) पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा pci_driver agp_amd64_pci_driver = अणु
	.name		= "agpgart-amd64",
	.id_table	= agp_amd64_pci_table,
	.probe		= agp_amd64_probe,
	.हटाओ		= agp_amd64_हटाओ,
#अगर_घोषित CONFIG_PM
	.suspend	= agp_amd64_suspend,
	.resume		= agp_amd64_resume,
#पूर्ण_अगर
पूर्ण;


/* Not अटल due to IOMMU code calling it early. */
पूर्णांक __init agp_amd64_init(व्योम)
अणु
	पूर्णांक err = 0;

	अगर (agp_off)
		वापस -EINVAL;

	err = pci_रेजिस्टर_driver(&agp_amd64_pci_driver);
	अगर (err < 0)
		वापस err;

	अगर (agp_bridges_found == 0) अणु
		अगर (!agp_try_unsupported && !agp_try_unsupported_boot) अणु
			prपूर्णांकk(KERN_INFO PFX "No supported AGP bridge found.\n");
#अगर_घोषित MODULE
			prपूर्णांकk(KERN_INFO PFX "You can try agp_try_unsupported=1\n");
#अन्यथा
			prपूर्णांकk(KERN_INFO PFX "You can boot with agp=try_unsupported\n");
#पूर्ण_अगर
			pci_unरेजिस्टर_driver(&agp_amd64_pci_driver);
			वापस -ENODEV;
		पूर्ण

		/* First check that we have at least one AMD64 NB */
		अगर (!amd_nb_num()) अणु
			pci_unरेजिस्टर_driver(&agp_amd64_pci_driver);
			वापस -ENODEV;
		पूर्ण

		/* Look क्रम any AGP bridge */
		agp_amd64_pci_driver.id_table = agp_amd64_pci_promisc_table;
		err = driver_attach(&agp_amd64_pci_driver.driver);
		अगर (err == 0 && agp_bridges_found == 0) अणु
			pci_unरेजिस्टर_driver(&agp_amd64_pci_driver);
			err = -ENODEV;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक __init agp_amd64_mod_init(व्योम)
अणु
#अगर_अघोषित MODULE
	अगर (gart_iommu_aperture)
		वापस agp_bridges_found ? 0 : -ENODEV;
#पूर्ण_अगर
	वापस agp_amd64_init();
पूर्ण

अटल व्योम __निकास agp_amd64_cleanup(व्योम)
अणु
#अगर_अघोषित MODULE
	अगर (gart_iommu_aperture)
		वापस;
#पूर्ण_अगर
	अगर (aperture_resource)
		release_resource(aperture_resource);
	pci_unरेजिस्टर_driver(&agp_amd64_pci_driver);
पूर्ण

module_init(agp_amd64_mod_init);
module_निकास(agp_amd64_cleanup);

MODULE_AUTHOR("Dave Jones, Andi Kleen");
module_param(agp_try_unsupported, bool, 0);
MODULE_LICENSE("GPL");
