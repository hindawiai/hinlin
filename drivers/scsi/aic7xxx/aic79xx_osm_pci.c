<शैली गुरु>
/*
 * Linux driver attachment glue क्रम PCI based U320 controllers.
 *
 * Copyright (c) 2000-2001 Adaptec Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions, and the following disclaimer,
 *    without modअगरication.
 * 2. Redistributions in binary क्रमm must reproduce at minimum a disclaimer
 *    substantially similar to the "NO WARRANTY" disclaimer below
 *    ("Disclaimer") and any redistribution must be conditioned upon
 *    including a substantially similar Disclaimer requirement क्रम further
 *    binary redistribution.
 * 3. Neither the names of the above-listed copyright holders nor the names
 *    of any contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * Alternatively, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") version 2 as published by the Free
 * Software Foundation.
 *
 * NO WARRANTY
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTIBILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * HOLDERS OR CONTRIBUTORS BE LIABLE FOR SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGES.
 *
 * $Id: //depot/aic7xxx/linux/drivers/scsi/aic7xxx/aic79xx_osm_pci.c#25 $
 */

#समावेश "aic79xx_osm.h"
#समावेश "aic79xx_inline.h"
#समावेश "aic79xx_pci.h"

/* Define the macro locally since it's dअगरferent क्रम dअगरferent class of chips.
 */
#घोषणा ID(x)		 \
	ID2C(x),	 \
	ID2C(IसूचीOC(x))

अटल स्थिर काष्ठा pci_device_id ahd_linux_pci_id_table[] = अणु
	/* aic7901 based controllers */
	ID(ID_AHA_29320A),
	ID(ID_AHA_29320ALP),
	ID(ID_AHA_29320LPE),
	/* aic7902 based controllers */
	ID(ID_AHA_29320),
	ID(ID_AHA_29320B),
	ID(ID_AHA_29320LP),
	ID(ID_AHA_39320),
	ID(ID_AHA_39320_B),
	ID(ID_AHA_39320A),
	ID(ID_AHA_39320D),
	ID(ID_AHA_39320D_HP),
	ID(ID_AHA_39320D_B),
	ID(ID_AHA_39320D_B_HP),
	/* Generic chip probes क्रम devices we करोn't know exactly. */
	ID16(ID_AIC7901 & ID_9005_GENERIC_MASK),
	ID(ID_AIC7901A & ID_DEV_VENDOR_MASK),
	ID16(ID_AIC7902 & ID_9005_GENERIC_MASK),
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, ahd_linux_pci_id_table);

अटल पूर्णांक __maybe_unused
ahd_linux_pci_dev_suspend(काष्ठा device *dev)
अणु
	काष्ठा ahd_softc *ahd = dev_get_drvdata(dev);
	पूर्णांक rc;

	अगर ((rc = ahd_suspend(ahd)))
		वापस rc;

	ahd_pci_suspend(ahd);

	वापस rc;
पूर्ण

अटल पूर्णांक __maybe_unused
ahd_linux_pci_dev_resume(काष्ठा device *dev)
अणु
	काष्ठा ahd_softc *ahd = dev_get_drvdata(dev);

	ahd_pci_resume(ahd);

	ahd_resume(ahd);

	वापस 0;
पूर्ण

अटल व्योम
ahd_linux_pci_dev_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ahd_softc *ahd = pci_get_drvdata(pdev);
	u_दीर्घ s;

	अगर (ahd->platक्रमm_data && ahd->platक्रमm_data->host)
			scsi_हटाओ_host(ahd->platक्रमm_data->host);

	ahd_lock(ahd, &s);
	ahd_पूर्णांकr_enable(ahd, FALSE);
	ahd_unlock(ahd, &s);
	ahd_मुक्त(ahd);
पूर्ण

अटल व्योम
ahd_linux_pci_inherit_flags(काष्ठा ahd_softc *ahd)
अणु
	काष्ठा pci_dev *pdev = ahd->dev_softc, *master_pdev;
	अचिन्हित पूर्णांक master_devfn = PCI_DEVFN(PCI_SLOT(pdev->devfn), 0);

	master_pdev = pci_get_slot(pdev->bus, master_devfn);
	अगर (master_pdev) अणु
		काष्ठा ahd_softc *master = pci_get_drvdata(master_pdev);
		अगर (master) अणु
			ahd->flags &= ~AHD_BIOS_ENABLED;
			ahd->flags |= master->flags & AHD_BIOS_ENABLED;
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_ERR "aic79xx: no multichannel peer found!\n");
		pci_dev_put(master_pdev);
	पूर्ण
पूर्ण

अटल पूर्णांक
ahd_linux_pci_dev_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अक्षर		 buf[80];
	काष्ठा		 ahd_softc *ahd;
	ahd_dev_softc_t	 pci;
	स्थिर काष्ठा ahd_pci_identity *entry;
	अक्षर		*name;
	पूर्णांक		 error;
	काष्ठा device	*dev = &pdev->dev;

	pci = pdev;
	entry = ahd_find_pci_device(pci);
	अगर (entry == शून्य)
		वापस (-ENODEV);

	/*
	 * Allocate a softc क्रम this card and
	 * set it up क्रम attachment by our
	 * common detect routine.
	 */
	प्र_लिखो(buf, "ahd_pci:%d:%d:%d",
		ahd_get_pci_bus(pci),
		ahd_get_pci_slot(pci),
		ahd_get_pci_function(pci));
	name = kstrdup(buf, GFP_ATOMIC);
	अगर (name == शून्य)
		वापस (-ENOMEM);
	ahd = ahd_alloc(शून्य, name);
	अगर (ahd == शून्य)
		वापस (-ENOMEM);
	अगर (pci_enable_device(pdev)) अणु
		ahd_मुक्त(ahd);
		वापस (-ENODEV);
	पूर्ण
	pci_set_master(pdev);

	अगर (माप(dma_addr_t) > 4) अणु
		स्थिर u64 required_mask = dma_get_required_mask(dev);

		अगर (required_mask > DMA_BIT_MASK(39) &&
		    dma_set_mask(dev, DMA_BIT_MASK(64)) == 0)
			ahd->flags |= AHD_64BIT_ADDRESSING;
		अन्यथा अगर (required_mask > DMA_BIT_MASK(32) &&
			 dma_set_mask(dev, DMA_BIT_MASK(39)) == 0)
			ahd->flags |= AHD_39BIT_ADDRESSING;
		अन्यथा
			dma_set_mask(dev, DMA_BIT_MASK(32));
	पूर्ण अन्यथा अणु
		dma_set_mask(dev, DMA_BIT_MASK(32));
	पूर्ण
	ahd->dev_softc = pci;
	error = ahd_pci_config(ahd, entry);
	अगर (error != 0) अणु
		ahd_मुक्त(ahd);
		वापस (-error);
	पूर्ण

	/*
	 * Second Function PCI devices need to inherit some
	 * * settings from function 0.
	 */
	अगर ((ahd->features & AHD_MULTI_FUNC) && PCI_FUNC(pdev->devfn) != 0)
		ahd_linux_pci_inherit_flags(ahd);

	pci_set_drvdata(pdev, ahd);

	ahd_linux_रेजिस्टर_host(ahd, &aic79xx_driver_ढाँचा);
	वापस (0);
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ahd_linux_pci_dev_pm_ops,
			 ahd_linux_pci_dev_suspend,
			 ahd_linux_pci_dev_resume);

अटल काष्ठा pci_driver aic79xx_pci_driver = अणु
	.name		= "aic79xx",
	.probe		= ahd_linux_pci_dev_probe,
	.driver.pm	= &ahd_linux_pci_dev_pm_ops,
	.हटाओ		= ahd_linux_pci_dev_हटाओ,
	.id_table	= ahd_linux_pci_id_table
पूर्ण;

पूर्णांक
ahd_linux_pci_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&aic79xx_pci_driver);
पूर्ण

व्योम
ahd_linux_pci_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&aic79xx_pci_driver);
पूर्ण

अटल पूर्णांक
ahd_linux_pci_reserve_io_regions(काष्ठा ahd_softc *ahd, resource_माप_प्रकार *base,
				 resource_माप_प्रकार *base2)
अणु
	*base = pci_resource_start(ahd->dev_softc, 0);
	/*
	 * This is really the 3rd bar and should be at index 2,
	 * but the Linux PCI code करोesn't know how to "count" 64bit
	 * bars.
	 */
	*base2 = pci_resource_start(ahd->dev_softc, 3);
	अगर (*base == 0 || *base2 == 0)
		वापस (ENOMEM);
	अगर (!request_region(*base, 256, "aic79xx"))
		वापस (ENOMEM);
	अगर (!request_region(*base2, 256, "aic79xx")) अणु
		release_region(*base, 256);
		वापस (ENOMEM);
	पूर्ण
	वापस (0);
पूर्ण

अटल पूर्णांक
ahd_linux_pci_reserve_mem_region(काष्ठा ahd_softc *ahd,
				 resource_माप_प्रकार *bus_addr,
				 uपूर्णांक8_t __iomem **maddr)
अणु
	resource_माप_प्रकार	start;
	resource_माप_प्रकार	base_page;
	u_दीर्घ	base_offset;
	पूर्णांक	error = 0;

	अगर (aic79xx_allow_memio == 0)
		वापस (ENOMEM);

	अगर ((ahd->bugs & AHD_PCIX_MMAPIO_BUG) != 0)
		वापस (ENOMEM);

	start = pci_resource_start(ahd->dev_softc, 1);
	base_page = start & PAGE_MASK;
	base_offset = start - base_page;
	अगर (start != 0) अणु
		*bus_addr = start;
		अगर (!request_mem_region(start, 0x1000, "aic79xx"))
			error = ENOMEM;
		अगर (!error) अणु
			*maddr = ioremap(base_page, base_offset + 512);
			अगर (*maddr == शून्य) अणु
				error = ENOMEM;
				release_mem_region(start, 0x1000);
			पूर्ण अन्यथा
				*maddr += base_offset;
		पूर्ण
	पूर्ण अन्यथा
		error = ENOMEM;
	वापस (error);
पूर्ण

पूर्णांक
ahd_pci_map_रेजिस्टरs(काष्ठा ahd_softc *ahd)
अणु
	uपूर्णांक32_t command;
	resource_माप_प्रकार base;
	uपूर्णांक8_t	__iomem *maddr;
	पूर्णांक	 error;

	/*
	 * If its allowed, we prefer memory mapped access.
	 */
	command = ahd_pci_पढ़ो_config(ahd->dev_softc, PCIR_COMMAND, 4);
	command &= ~(PCIM_CMD_PORTEN|PCIM_CMD_MEMEN);
	base = 0;
	maddr = शून्य;
	error = ahd_linux_pci_reserve_mem_region(ahd, &base, &maddr);
	अगर (error == 0) अणु
		ahd->platक्रमm_data->mem_busaddr = base;
		ahd->tags[0] = BUS_SPACE_MEMIO;
		ahd->bshs[0].maddr = maddr;
		ahd->tags[1] = BUS_SPACE_MEMIO;
		ahd->bshs[1].maddr = maddr + 0x100;
		ahd_pci_ग_लिखो_config(ahd->dev_softc, PCIR_COMMAND,
				     command | PCIM_CMD_MEMEN, 4);

		अगर (ahd_pci_test_रेजिस्टर_access(ahd) != 0) अणु

			prपूर्णांकk("aic79xx: PCI Device %d:%d:%d "
			       "failed memory mapped test.  Using PIO.\n",
			       ahd_get_pci_bus(ahd->dev_softc),
			       ahd_get_pci_slot(ahd->dev_softc),
			       ahd_get_pci_function(ahd->dev_softc));
			iounmap(maddr);
			release_mem_region(ahd->platक्रमm_data->mem_busaddr,
					   0x1000);
			ahd->bshs[0].maddr = शून्य;
			maddr = शून्य;
		पूर्ण अन्यथा
			command |= PCIM_CMD_MEMEN;
	पूर्ण अन्यथा अगर (bootverbose) अणु
		prपूर्णांकk("aic79xx: PCI%d:%d:%d MEM region 0x%llx "
		       "unavailable. Cannot memory map device.\n",
		       ahd_get_pci_bus(ahd->dev_softc),
		       ahd_get_pci_slot(ahd->dev_softc),
		       ahd_get_pci_function(ahd->dev_softc),
		       (अचिन्हित दीर्घ दीर्घ)base);
	पूर्ण

	अगर (maddr == शून्य) अणु
		resource_माप_प्रकार base2;

		error = ahd_linux_pci_reserve_io_regions(ahd, &base, &base2);
		अगर (error == 0) अणु
			ahd->tags[0] = BUS_SPACE_PIO;
			ahd->tags[1] = BUS_SPACE_PIO;
			ahd->bshs[0].ioport = (u_दीर्घ)base;
			ahd->bshs[1].ioport = (u_दीर्घ)base2;
			command |= PCIM_CMD_PORTEN;
		पूर्ण अन्यथा अणु
			prपूर्णांकk("aic79xx: PCI%d:%d:%d IO regions 0x%llx and "
			       "0x%llx unavailable. Cannot map device.\n",
			       ahd_get_pci_bus(ahd->dev_softc),
			       ahd_get_pci_slot(ahd->dev_softc),
			       ahd_get_pci_function(ahd->dev_softc),
			       (अचिन्हित दीर्घ दीर्घ)base,
			       (अचिन्हित दीर्घ दीर्घ)base2);
		पूर्ण
	पूर्ण
	ahd_pci_ग_लिखो_config(ahd->dev_softc, PCIR_COMMAND, command, 4);
	वापस (error);
पूर्ण

पूर्णांक
ahd_pci_map_पूर्णांक(काष्ठा ahd_softc *ahd)
अणु
	पूर्णांक error;

	error = request_irq(ahd->dev_softc->irq, ahd_linux_isr,
			    IRQF_SHARED, "aic79xx", ahd);
	अगर (!error)
		ahd->platक्रमm_data->irq = ahd->dev_softc->irq;

	वापस (-error);
पूर्ण

व्योम
ahd_घातer_state_change(काष्ठा ahd_softc *ahd, ahd_घातer_state new_state)
अणु
	pci_set_घातer_state(ahd->dev_softc, new_state);
पूर्ण
