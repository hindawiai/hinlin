<शैली गुरु>
/*
 * Intel AGPGART routines.
 */

#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/slab.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/agp_backend.h>
#समावेश <यंत्र/smp.h>
#समावेश "agp.h"
#समावेश "intel-agp.h"
#समावेश <drm/पूर्णांकel-gtt.h>

अटल पूर्णांक पूर्णांकel_fetch_size(व्योम)
अणु
	पूर्णांक i;
	u16 temp;
	काष्ठा aper_size_info_16 *values;

	pci_पढ़ो_config_word(agp_bridge->dev, INTEL_APSIZE, &temp);
	values = A_SIZE_16(agp_bridge->driver->aperture_sizes);

	क्रम (i = 0; i < agp_bridge->driver->num_aperture_sizes; i++) अणु
		अगर (temp == values[i].size_value) अणु
			agp_bridge->previous_size = agp_bridge->current_size = (व्योम *) (values + i);
			agp_bridge->aperture_size_idx = i;
			वापस values[i].size;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __पूर्णांकel_8xx_fetch_size(u8 temp)
अणु
	पूर्णांक i;
	काष्ठा aper_size_info_8 *values;

	values = A_SIZE_8(agp_bridge->driver->aperture_sizes);

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

अटल पूर्णांक पूर्णांकel_8xx_fetch_size(व्योम)
अणु
	u8 temp;

	pci_पढ़ो_config_byte(agp_bridge->dev, INTEL_APSIZE, &temp);
	वापस __पूर्णांकel_8xx_fetch_size(temp);
पूर्ण

अटल पूर्णांक पूर्णांकel_815_fetch_size(व्योम)
अणु
	u8 temp;

	/* Intel 815 chipsets have a _weird_ APSIZE रेजिस्टर with only
	 * one non-reserved bit, so mask the others out ... */
	pci_पढ़ो_config_byte(agp_bridge->dev, INTEL_APSIZE, &temp);
	temp &= (1 << 3);

	वापस __पूर्णांकel_8xx_fetch_size(temp);
पूर्ण

अटल व्योम पूर्णांकel_tlbflush(काष्ठा agp_memory *mem)
अणु
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x2200);
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x2280);
पूर्ण


अटल व्योम पूर्णांकel_8xx_tlbflush(काष्ठा agp_memory *mem)
अणु
	u32 temp;
	pci_पढ़ो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, &temp);
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, temp & ~(1 << 7));
	pci_पढ़ो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, &temp);
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, temp | (1 << 7));
पूर्ण


अटल व्योम पूर्णांकel_cleanup(व्योम)
अणु
	u16 temp;
	काष्ठा aper_size_info_16 *previous_size;

	previous_size = A_SIZE_16(agp_bridge->previous_size);
	pci_पढ़ो_config_word(agp_bridge->dev, INTEL_NBXCFG, &temp);
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_NBXCFG, temp & ~(1 << 9));
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_APSIZE, previous_size->size_value);
पूर्ण


अटल व्योम पूर्णांकel_8xx_cleanup(व्योम)
अणु
	u16 temp;
	काष्ठा aper_size_info_8 *previous_size;

	previous_size = A_SIZE_8(agp_bridge->previous_size);
	pci_पढ़ो_config_word(agp_bridge->dev, INTEL_NBXCFG, &temp);
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_NBXCFG, temp & ~(1 << 9));
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_APSIZE, previous_size->size_value);
पूर्ण


अटल पूर्णांक पूर्णांकel_configure(व्योम)
अणु
	u16 temp2;
	काष्ठा aper_size_info_16 *current_size;

	current_size = A_SIZE_16(agp_bridge->current_size);

	/* aperture size */
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_APSIZE, current_size->size_value);

	/* address to map to */
	agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
						    AGP_APERTURE_BAR);

	/* attbase - aperture base */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_ATTBASE, agp_bridge->gatt_bus_addr);

	/* agpctrl */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x2280);

	/* paccfg/nbxcfg */
	pci_पढ़ो_config_word(agp_bridge->dev, INTEL_NBXCFG, &temp2);
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_NBXCFG,
			(temp2 & ~(1 << 10)) | (1 << 9));
	/* clear any possible error conditions */
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_ERRSTS + 1, 7);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_815_configure(व्योम)
अणु
	u32 addr;
	u8 temp2;
	काष्ठा aper_size_info_8 *current_size;

	/* attbase - aperture base */
	/* the Intel 815 chipset spec. says that bits 29-31 in the
	* ATTBASE रेजिस्टर are reserved -> try not to ग_लिखो them */
	अगर (agp_bridge->gatt_bus_addr & INTEL_815_ATTBASE_MASK) अणु
		dev_emerg(&agp_bridge->dev->dev, "gatt bus addr too high");
		वापस -EINVAL;
	पूर्ण

	current_size = A_SIZE_8(agp_bridge->current_size);

	/* aperture size */
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_APSIZE,
			current_size->size_value);

	/* address to map to */
	agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
						    AGP_APERTURE_BAR);

	pci_पढ़ो_config_dword(agp_bridge->dev, INTEL_ATTBASE, &addr);
	addr &= INTEL_815_ATTBASE_MASK;
	addr |= agp_bridge->gatt_bus_addr;
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_ATTBASE, addr);

	/* agpctrl */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x0000);

	/* apcont */
	pci_पढ़ो_config_byte(agp_bridge->dev, INTEL_815_APCONT, &temp2);
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_815_APCONT, temp2 | (1 << 1));

	/* clear any possible error conditions */
	/* Oddness : this chipset seems to have no ERRSTS रेजिस्टर ! */
	वापस 0;
पूर्ण

अटल व्योम पूर्णांकel_820_tlbflush(काष्ठा agp_memory *mem)
अणु
	वापस;
पूर्ण

अटल व्योम पूर्णांकel_820_cleanup(व्योम)
अणु
	u8 temp;
	काष्ठा aper_size_info_8 *previous_size;

	previous_size = A_SIZE_8(agp_bridge->previous_size);
	pci_पढ़ो_config_byte(agp_bridge->dev, INTEL_I820_RDCR, &temp);
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_I820_RDCR,
			temp & ~(1 << 1));
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_APSIZE,
			previous_size->size_value);
पूर्ण


अटल पूर्णांक पूर्णांकel_820_configure(व्योम)
अणु
	u8 temp2;
	काष्ठा aper_size_info_8 *current_size;

	current_size = A_SIZE_8(agp_bridge->current_size);

	/* aperture size */
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_APSIZE, current_size->size_value);

	/* address to map to */
	agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
						    AGP_APERTURE_BAR);

	/* attbase - aperture base */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_ATTBASE, agp_bridge->gatt_bus_addr);

	/* agpctrl */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x0000);

	/* global enable aperture access */
	/* This flag is not accessed through MCHCFG रेजिस्टर as in */
	/* i850 chipset. */
	pci_पढ़ो_config_byte(agp_bridge->dev, INTEL_I820_RDCR, &temp2);
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_I820_RDCR, temp2 | (1 << 1));
	/* clear any possible AGP-related error conditions */
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_I820_ERRSTS, 0x001c);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_840_configure(व्योम)
अणु
	u16 temp2;
	काष्ठा aper_size_info_8 *current_size;

	current_size = A_SIZE_8(agp_bridge->current_size);

	/* aperture size */
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_APSIZE, current_size->size_value);

	/* address to map to */
	agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
						    AGP_APERTURE_BAR);

	/* attbase - aperture base */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_ATTBASE, agp_bridge->gatt_bus_addr);

	/* agpctrl */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x0000);

	/* mcgcfg */
	pci_पढ़ो_config_word(agp_bridge->dev, INTEL_I840_MCHCFG, &temp2);
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_I840_MCHCFG, temp2 | (1 << 9));
	/* clear any possible error conditions */
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_I840_ERRSTS, 0xc000);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_845_configure(व्योम)
अणु
	u8 temp2;
	काष्ठा aper_size_info_8 *current_size;

	current_size = A_SIZE_8(agp_bridge->current_size);

	/* aperture size */
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_APSIZE, current_size->size_value);

	अगर (agp_bridge->apbase_config != 0) अणु
		pci_ग_लिखो_config_dword(agp_bridge->dev, AGP_APBASE,
				       agp_bridge->apbase_config);
	पूर्ण अन्यथा अणु
		/* address to map to */
		agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
							    AGP_APERTURE_BAR);
		agp_bridge->apbase_config = agp_bridge->gart_bus_addr;
	पूर्ण

	/* attbase - aperture base */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_ATTBASE, agp_bridge->gatt_bus_addr);

	/* agpctrl */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x0000);

	/* agpm */
	pci_पढ़ो_config_byte(agp_bridge->dev, INTEL_I845_AGPM, &temp2);
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_I845_AGPM, temp2 | (1 << 1));
	/* clear any possible error conditions */
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_I845_ERRSTS, 0x001c);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_850_configure(व्योम)
अणु
	u16 temp2;
	काष्ठा aper_size_info_8 *current_size;

	current_size = A_SIZE_8(agp_bridge->current_size);

	/* aperture size */
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_APSIZE, current_size->size_value);

	/* address to map to */
	agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
						    AGP_APERTURE_BAR);

	/* attbase - aperture base */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_ATTBASE, agp_bridge->gatt_bus_addr);

	/* agpctrl */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x0000);

	/* mcgcfg */
	pci_पढ़ो_config_word(agp_bridge->dev, INTEL_I850_MCHCFG, &temp2);
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_I850_MCHCFG, temp2 | (1 << 9));
	/* clear any possible AGP-related error conditions */
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_I850_ERRSTS, 0x001c);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_860_configure(व्योम)
अणु
	u16 temp2;
	काष्ठा aper_size_info_8 *current_size;

	current_size = A_SIZE_8(agp_bridge->current_size);

	/* aperture size */
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_APSIZE, current_size->size_value);

	/* address to map to */
	agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
						    AGP_APERTURE_BAR);

	/* attbase - aperture base */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_ATTBASE, agp_bridge->gatt_bus_addr);

	/* agpctrl */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x0000);

	/* mcgcfg */
	pci_पढ़ो_config_word(agp_bridge->dev, INTEL_I860_MCHCFG, &temp2);
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_I860_MCHCFG, temp2 | (1 << 9));
	/* clear any possible AGP-related error conditions */
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_I860_ERRSTS, 0xf700);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_830mp_configure(व्योम)
अणु
	u16 temp2;
	काष्ठा aper_size_info_8 *current_size;

	current_size = A_SIZE_8(agp_bridge->current_size);

	/* aperture size */
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_APSIZE, current_size->size_value);

	/* address to map to */
	agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
						    AGP_APERTURE_BAR);

	/* attbase - aperture base */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_ATTBASE, agp_bridge->gatt_bus_addr);

	/* agpctrl */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x0000);

	/* gmch */
	pci_पढ़ो_config_word(agp_bridge->dev, INTEL_NBXCFG, &temp2);
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_NBXCFG, temp2 | (1 << 9));
	/* clear any possible AGP-related error conditions */
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_I830_ERRSTS, 0x1c);
	वापस 0;
पूर्ण

अटल पूर्णांक पूर्णांकel_7505_configure(व्योम)
अणु
	u16 temp2;
	काष्ठा aper_size_info_8 *current_size;

	current_size = A_SIZE_8(agp_bridge->current_size);

	/* aperture size */
	pci_ग_लिखो_config_byte(agp_bridge->dev, INTEL_APSIZE, current_size->size_value);

	/* address to map to */
	agp_bridge->gart_bus_addr = pci_bus_address(agp_bridge->dev,
						    AGP_APERTURE_BAR);

	/* attbase - aperture base */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_ATTBASE, agp_bridge->gatt_bus_addr);

	/* agpctrl */
	pci_ग_लिखो_config_dword(agp_bridge->dev, INTEL_AGPCTRL, 0x0000);

	/* mchcfg */
	pci_पढ़ो_config_word(agp_bridge->dev, INTEL_I7505_MCHCFG, &temp2);
	pci_ग_लिखो_config_word(agp_bridge->dev, INTEL_I7505_MCHCFG, temp2 | (1 << 9));

	वापस 0;
पूर्ण

/* Setup function */
अटल स्थिर काष्ठा gatt_mask पूर्णांकel_generic_masks[] =
अणु
	अणु.mask = 0x00000017, .type = 0पूर्ण
पूर्ण;

अटल स्थिर काष्ठा aper_size_info_8 पूर्णांकel_815_sizes[2] =
अणु
	अणु64, 16384, 4, 0पूर्ण,
	अणु32, 8192, 3, 8पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा aper_size_info_8 पूर्णांकel_8xx_sizes[7] =
अणु
	अणु256, 65536, 6, 0पूर्ण,
	अणु128, 32768, 5, 32पूर्ण,
	अणु64, 16384, 4, 48पूर्ण,
	अणु32, 8192, 3, 56पूर्ण,
	अणु16, 4096, 2, 60पूर्ण,
	अणु8, 2048, 1, 62पूर्ण,
	अणु4, 1024, 0, 63पूर्ण
पूर्ण;

अटल स्थिर काष्ठा aper_size_info_16 पूर्णांकel_generic_sizes[7] =
अणु
	अणु256, 65536, 6, 0पूर्ण,
	अणु128, 32768, 5, 32पूर्ण,
	अणु64, 16384, 4, 48पूर्ण,
	अणु32, 8192, 3, 56पूर्ण,
	अणु16, 4096, 2, 60पूर्ण,
	अणु8, 2048, 1, 62पूर्ण,
	अणु4, 1024, 0, 63पूर्ण
पूर्ण;

अटल स्थिर काष्ठा aper_size_info_8 पूर्णांकel_830mp_sizes[4] =
अणु
	अणु256, 65536, 6, 0पूर्ण,
	अणु128, 32768, 5, 32पूर्ण,
	अणु64, 16384, 4, 48पूर्ण,
	अणु32, 8192, 3, 56पूर्ण
पूर्ण;

अटल स्थिर काष्ठा agp_bridge_driver पूर्णांकel_generic_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= पूर्णांकel_generic_sizes,
	.माप_प्रकारype		= U16_APER_SIZE,
	.num_aperture_sizes	= 7,
	.needs_scratch_page	= true,
	.configure		= पूर्णांकel_configure,
	.fetch_size		= पूर्णांकel_fetch_size,
	.cleanup		= पूर्णांकel_cleanup,
	.tlb_flush		= पूर्णांकel_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= पूर्णांकel_generic_masks,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= agp_generic_create_gatt_table,
	.मुक्त_gatt_table	= agp_generic_मुक्त_gatt_table,
	.insert_memory		= agp_generic_insert_memory,
	.हटाओ_memory		= agp_generic_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages        = agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages      = agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

अटल स्थिर काष्ठा agp_bridge_driver पूर्णांकel_815_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= पूर्णांकel_815_sizes,
	.माप_प्रकारype		= U8_APER_SIZE,
	.num_aperture_sizes	= 2,
	.needs_scratch_page	= true,
	.configure		= पूर्णांकel_815_configure,
	.fetch_size		= पूर्णांकel_815_fetch_size,
	.cleanup		= पूर्णांकel_8xx_cleanup,
	.tlb_flush		= पूर्णांकel_8xx_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= पूर्णांकel_generic_masks,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= agp_generic_create_gatt_table,
	.मुक्त_gatt_table	= agp_generic_मुक्त_gatt_table,
	.insert_memory		= agp_generic_insert_memory,
	.हटाओ_memory		= agp_generic_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages        = agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages      = agp_generic_destroy_pages,
	.agp_type_to_mask_type	= agp_generic_type_to_mask_type,
पूर्ण;

अटल स्थिर काष्ठा agp_bridge_driver पूर्णांकel_820_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= पूर्णांकel_8xx_sizes,
	.माप_प्रकारype		= U8_APER_SIZE,
	.num_aperture_sizes	= 7,
	.needs_scratch_page	= true,
	.configure		= पूर्णांकel_820_configure,
	.fetch_size		= पूर्णांकel_8xx_fetch_size,
	.cleanup		= पूर्णांकel_820_cleanup,
	.tlb_flush		= पूर्णांकel_820_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= पूर्णांकel_generic_masks,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= agp_generic_create_gatt_table,
	.मुक्त_gatt_table	= agp_generic_मुक्त_gatt_table,
	.insert_memory		= agp_generic_insert_memory,
	.हटाओ_memory		= agp_generic_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages        = agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages      = agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

अटल स्थिर काष्ठा agp_bridge_driver पूर्णांकel_830mp_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= पूर्णांकel_830mp_sizes,
	.माप_प्रकारype		= U8_APER_SIZE,
	.num_aperture_sizes	= 4,
	.needs_scratch_page	= true,
	.configure		= पूर्णांकel_830mp_configure,
	.fetch_size		= पूर्णांकel_8xx_fetch_size,
	.cleanup		= पूर्णांकel_8xx_cleanup,
	.tlb_flush		= पूर्णांकel_8xx_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= पूर्णांकel_generic_masks,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= agp_generic_create_gatt_table,
	.मुक्त_gatt_table	= agp_generic_मुक्त_gatt_table,
	.insert_memory		= agp_generic_insert_memory,
	.हटाओ_memory		= agp_generic_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages        = agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages      = agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

अटल स्थिर काष्ठा agp_bridge_driver पूर्णांकel_840_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= पूर्णांकel_8xx_sizes,
	.माप_प्रकारype		= U8_APER_SIZE,
	.num_aperture_sizes	= 7,
	.needs_scratch_page	= true,
	.configure		= पूर्णांकel_840_configure,
	.fetch_size		= पूर्णांकel_8xx_fetch_size,
	.cleanup		= पूर्णांकel_8xx_cleanup,
	.tlb_flush		= पूर्णांकel_8xx_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= पूर्णांकel_generic_masks,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= agp_generic_create_gatt_table,
	.मुक्त_gatt_table	= agp_generic_मुक्त_gatt_table,
	.insert_memory		= agp_generic_insert_memory,
	.हटाओ_memory		= agp_generic_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages        = agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages      = agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

अटल स्थिर काष्ठा agp_bridge_driver पूर्णांकel_845_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= पूर्णांकel_8xx_sizes,
	.माप_प्रकारype		= U8_APER_SIZE,
	.num_aperture_sizes	= 7,
	.needs_scratch_page	= true,
	.configure		= पूर्णांकel_845_configure,
	.fetch_size		= पूर्णांकel_8xx_fetch_size,
	.cleanup		= पूर्णांकel_8xx_cleanup,
	.tlb_flush		= पूर्णांकel_8xx_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= पूर्णांकel_generic_masks,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= agp_generic_create_gatt_table,
	.मुक्त_gatt_table	= agp_generic_मुक्त_gatt_table,
	.insert_memory		= agp_generic_insert_memory,
	.हटाओ_memory		= agp_generic_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages        = agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages      = agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

अटल स्थिर काष्ठा agp_bridge_driver पूर्णांकel_850_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= पूर्णांकel_8xx_sizes,
	.माप_प्रकारype		= U8_APER_SIZE,
	.num_aperture_sizes	= 7,
	.needs_scratch_page	= true,
	.configure		= पूर्णांकel_850_configure,
	.fetch_size		= पूर्णांकel_8xx_fetch_size,
	.cleanup		= पूर्णांकel_8xx_cleanup,
	.tlb_flush		= पूर्णांकel_8xx_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= पूर्णांकel_generic_masks,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= agp_generic_create_gatt_table,
	.मुक्त_gatt_table	= agp_generic_मुक्त_gatt_table,
	.insert_memory		= agp_generic_insert_memory,
	.हटाओ_memory		= agp_generic_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages        = agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages      = agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

अटल स्थिर काष्ठा agp_bridge_driver पूर्णांकel_860_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= पूर्णांकel_8xx_sizes,
	.माप_प्रकारype		= U8_APER_SIZE,
	.num_aperture_sizes	= 7,
	.needs_scratch_page	= true,
	.configure		= पूर्णांकel_860_configure,
	.fetch_size		= पूर्णांकel_8xx_fetch_size,
	.cleanup		= पूर्णांकel_8xx_cleanup,
	.tlb_flush		= पूर्णांकel_8xx_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= पूर्णांकel_generic_masks,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= agp_generic_create_gatt_table,
	.मुक्त_gatt_table	= agp_generic_मुक्त_gatt_table,
	.insert_memory		= agp_generic_insert_memory,
	.हटाओ_memory		= agp_generic_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages        = agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages      = agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

अटल स्थिर काष्ठा agp_bridge_driver पूर्णांकel_7505_driver = अणु
	.owner			= THIS_MODULE,
	.aperture_sizes		= पूर्णांकel_8xx_sizes,
	.माप_प्रकारype		= U8_APER_SIZE,
	.num_aperture_sizes	= 7,
	.needs_scratch_page	= true,
	.configure		= पूर्णांकel_7505_configure,
	.fetch_size		= पूर्णांकel_8xx_fetch_size,
	.cleanup		= पूर्णांकel_8xx_cleanup,
	.tlb_flush		= पूर्णांकel_8xx_tlbflush,
	.mask_memory		= agp_generic_mask_memory,
	.masks			= पूर्णांकel_generic_masks,
	.agp_enable		= agp_generic_enable,
	.cache_flush		= global_cache_flush,
	.create_gatt_table	= agp_generic_create_gatt_table,
	.मुक्त_gatt_table	= agp_generic_मुक्त_gatt_table,
	.insert_memory		= agp_generic_insert_memory,
	.हटाओ_memory		= agp_generic_हटाओ_memory,
	.alloc_by_type		= agp_generic_alloc_by_type,
	.मुक्त_by_type		= agp_generic_मुक्त_by_type,
	.agp_alloc_page		= agp_generic_alloc_page,
	.agp_alloc_pages        = agp_generic_alloc_pages,
	.agp_destroy_page	= agp_generic_destroy_page,
	.agp_destroy_pages      = agp_generic_destroy_pages,
	.agp_type_to_mask_type  = agp_generic_type_to_mask_type,
पूर्ण;

/* Table to describe Intel GMCH and AGP/PCIE GART drivers.  At least one of
 * driver and gmch_driver must be non-null, and find_gmch will determine
 * which one should be used अगर a gmch_chip_id is present.
 */
अटल स्थिर काष्ठा पूर्णांकel_agp_driver_description अणु
	अचिन्हित पूर्णांक chip_id;
	अक्षर *name;
	स्थिर काष्ठा agp_bridge_driver *driver;
पूर्ण पूर्णांकel_agp_chipsets[] = अणु
	अणु PCI_DEVICE_ID_INTEL_82443LX_0, "440LX", &पूर्णांकel_generic_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82443BX_0, "440BX", &पूर्णांकel_generic_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82443GX_0, "440GX", &पूर्णांकel_generic_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82815_MC, "i815", &पूर्णांकel_815_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82820_HB, "i820", &पूर्णांकel_820_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82820_UP_HB, "i820", &पूर्णांकel_820_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82830_HB, "830M", &पूर्णांकel_830mp_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82840_HB, "i840", &पूर्णांकel_840_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82845_HB, "i845", &पूर्णांकel_845_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82845G_HB, "845G", &पूर्णांकel_845_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82850_HB, "i850", &पूर्णांकel_850_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82854_HB, "854", &पूर्णांकel_845_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82855PM_HB, "855PM", &पूर्णांकel_845_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82855GM_HB, "855GM", &पूर्णांकel_845_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82860_HB, "i860", &पूर्णांकel_860_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82865_HB, "865", &पूर्णांकel_845_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_82875_HB, "i875", &पूर्णांकel_845_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_7505_0, "E7505", &पूर्णांकel_7505_driver पूर्ण,
	अणु PCI_DEVICE_ID_INTEL_7205_0, "E7205", &पूर्णांकel_7505_driver पूर्ण,
	अणु 0, शून्य, शून्य पूर्ण
पूर्ण;

अटल पूर्णांक agp_पूर्णांकel_probe(काष्ठा pci_dev *pdev,
			   स्थिर काष्ठा pci_device_id *ent)
अणु
	काष्ठा agp_bridge_data *bridge;
	u8 cap_ptr = 0;
	काष्ठा resource *r;
	पूर्णांक i, err;

	cap_ptr = pci_find_capability(pdev, PCI_CAP_ID_AGP);

	bridge = agp_alloc_bridge();
	अगर (!bridge)
		वापस -ENOMEM;

	bridge->capndx = cap_ptr;

	अगर (पूर्णांकel_gmch_probe(pdev, शून्य, bridge))
		जाओ found_gmch;

	क्रम (i = 0; पूर्णांकel_agp_chipsets[i].name != शून्य; i++) अणु
		/* In हाल that multiple models of gfx chip may
		   stand on same host bridge type, this can be
		   sure we detect the right IGD. */
		अगर (pdev->device == पूर्णांकel_agp_chipsets[i].chip_id) अणु
			bridge->driver = पूर्णांकel_agp_chipsets[i].driver;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!bridge->driver) अणु
		अगर (cap_ptr)
			dev_warn(&pdev->dev, "unsupported Intel chipset [%04x/%04x]\n",
				 pdev->venकरोr, pdev->device);
		agp_put_bridge(bridge);
		वापस -ENODEV;
	पूर्ण

	bridge->dev = pdev;
	bridge->dev_निजी_data = शून्य;

	dev_info(&pdev->dev, "Intel %s Chipset\n", पूर्णांकel_agp_chipsets[i].name);

	/*
	* The following fixes the हाल where the BIOS has "forgotten" to
	* provide an address range क्रम the GART.
	* 20030610 - hamish@zot.org
	* This happens beक्रमe pci_enable_device() पूर्णांकentionally;
	* calling pci_enable_device() beक्रमe assigning the resource
	* will result in the GART being disabled on machines with such
	* BIOSs (the GART ends up with a BAR starting at 0, which
	* conflicts a lot of other devices).
	*/
	r = &pdev->resource[0];
	अगर (!r->start && r->end) अणु
		अगर (pci_assign_resource(pdev, 0)) अणु
			dev_err(&pdev->dev, "can't assign resource 0\n");
			agp_put_bridge(bridge);
			वापस -ENODEV;
		पूर्ण
	पूर्ण

	/*
	* If the device has not been properly setup, the following will catch
	* the problem and should stop the प्रणाली from crashing.
	* 20030610 - hamish@zot.org
	*/
	अगर (pci_enable_device(pdev)) अणु
		dev_err(&pdev->dev, "can't enable PCI device\n");
		agp_put_bridge(bridge);
		वापस -ENODEV;
	पूर्ण

	/* Fill in the mode रेजिस्टर */
	अगर (cap_ptr) अणु
		pci_पढ़ो_config_dword(pdev,
				bridge->capndx+PCI_AGP_STATUS,
				&bridge->mode);
	पूर्ण

found_gmch:
	pci_set_drvdata(pdev, bridge);
	err = agp_add_bridge(bridge);
	वापस err;
पूर्ण

अटल व्योम agp_पूर्णांकel_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge = pci_get_drvdata(pdev);

	agp_हटाओ_bridge(bridge);

	पूर्णांकel_gmch_हटाओ();

	agp_put_bridge(bridge);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक agp_पूर्णांकel_resume(काष्ठा pci_dev *pdev)
अणु
	काष्ठा agp_bridge_data *bridge = pci_get_drvdata(pdev);

	bridge->driver->configure();

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा pci_device_id agp_पूर्णांकel_pci_table[] = अणु
#घोषणा ID(x)						\
	अणु						\
	.class		= (PCI_CLASS_BRIDGE_HOST << 8),	\
	.class_mask	= ~0,				\
	.venकरोr		= PCI_VENDOR_ID_INTEL,		\
	.device		= x,				\
	.subvenकरोr	= PCI_ANY_ID,			\
	.subdevice	= PCI_ANY_ID,			\
	पूर्ण
	ID(PCI_DEVICE_ID_INTEL_82441), /* क्रम HAS2 support */
	ID(PCI_DEVICE_ID_INTEL_82443LX_0),
	ID(PCI_DEVICE_ID_INTEL_82443BX_0),
	ID(PCI_DEVICE_ID_INTEL_82443GX_0),
	ID(PCI_DEVICE_ID_INTEL_82810_MC1),
	ID(PCI_DEVICE_ID_INTEL_82810_MC3),
	ID(PCI_DEVICE_ID_INTEL_82810E_MC),
	ID(PCI_DEVICE_ID_INTEL_82815_MC),
	ID(PCI_DEVICE_ID_INTEL_82820_HB),
	ID(PCI_DEVICE_ID_INTEL_82820_UP_HB),
	ID(PCI_DEVICE_ID_INTEL_82830_HB),
	ID(PCI_DEVICE_ID_INTEL_82840_HB),
	ID(PCI_DEVICE_ID_INTEL_82845_HB),
	ID(PCI_DEVICE_ID_INTEL_82845G_HB),
	ID(PCI_DEVICE_ID_INTEL_82850_HB),
	ID(PCI_DEVICE_ID_INTEL_82854_HB),
	ID(PCI_DEVICE_ID_INTEL_82855PM_HB),
	ID(PCI_DEVICE_ID_INTEL_82855GM_HB),
	ID(PCI_DEVICE_ID_INTEL_82860_HB),
	ID(PCI_DEVICE_ID_INTEL_82865_HB),
	ID(PCI_DEVICE_ID_INTEL_82875_HB),
	ID(PCI_DEVICE_ID_INTEL_7505_0),
	ID(PCI_DEVICE_ID_INTEL_7205_0),
	ID(PCI_DEVICE_ID_INTEL_E7221_HB),
	ID(PCI_DEVICE_ID_INTEL_82915G_HB),
	ID(PCI_DEVICE_ID_INTEL_82915GM_HB),
	ID(PCI_DEVICE_ID_INTEL_82945G_HB),
	ID(PCI_DEVICE_ID_INTEL_82945GM_HB),
	ID(PCI_DEVICE_ID_INTEL_82945GME_HB),
	ID(PCI_DEVICE_ID_INTEL_PINEVIEW_M_HB),
	ID(PCI_DEVICE_ID_INTEL_PINEVIEW_HB),
	ID(PCI_DEVICE_ID_INTEL_82946GZ_HB),
	ID(PCI_DEVICE_ID_INTEL_82G35_HB),
	ID(PCI_DEVICE_ID_INTEL_82965Q_HB),
	ID(PCI_DEVICE_ID_INTEL_82965G_HB),
	ID(PCI_DEVICE_ID_INTEL_82965GM_HB),
	ID(PCI_DEVICE_ID_INTEL_82965GME_HB),
	ID(PCI_DEVICE_ID_INTEL_G33_HB),
	ID(PCI_DEVICE_ID_INTEL_Q35_HB),
	ID(PCI_DEVICE_ID_INTEL_Q33_HB),
	ID(PCI_DEVICE_ID_INTEL_GM45_HB),
	ID(PCI_DEVICE_ID_INTEL_EAGLELAKE_HB),
	ID(PCI_DEVICE_ID_INTEL_Q45_HB),
	ID(PCI_DEVICE_ID_INTEL_G45_HB),
	ID(PCI_DEVICE_ID_INTEL_G41_HB),
	ID(PCI_DEVICE_ID_INTEL_B43_HB),
	ID(PCI_DEVICE_ID_INTEL_B43_1_HB),
	ID(PCI_DEVICE_ID_INTEL_IRONLAKE_D_HB),
	ID(PCI_DEVICE_ID_INTEL_IRONLAKE_D2_HB),
	ID(PCI_DEVICE_ID_INTEL_IRONLAKE_M_HB),
	ID(PCI_DEVICE_ID_INTEL_IRONLAKE_MA_HB),
	ID(PCI_DEVICE_ID_INTEL_IRONLAKE_MC2_HB),
	अणु पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, agp_पूर्णांकel_pci_table);

अटल काष्ठा pci_driver agp_पूर्णांकel_pci_driver = अणु
	.name		= "agpgart-intel",
	.id_table	= agp_पूर्णांकel_pci_table,
	.probe		= agp_पूर्णांकel_probe,
	.हटाओ		= agp_पूर्णांकel_हटाओ,
#अगर_घोषित CONFIG_PM
	.resume		= agp_पूर्णांकel_resume,
#पूर्ण_अगर
पूर्ण;

अटल पूर्णांक __init agp_पूर्णांकel_init(व्योम)
अणु
	अगर (agp_off)
		वापस -EINVAL;
	वापस pci_रेजिस्टर_driver(&agp_पूर्णांकel_pci_driver);
पूर्ण

अटल व्योम __निकास agp_पूर्णांकel_cleanup(व्योम)
अणु
	pci_unरेजिस्टर_driver(&agp_पूर्णांकel_pci_driver);
पूर्ण

module_init(agp_पूर्णांकel_init);
module_निकास(agp_पूर्णांकel_cleanup);

MODULE_AUTHOR("Dave Jones, Various @Intel");
MODULE_LICENSE("GPL and additional rights");
