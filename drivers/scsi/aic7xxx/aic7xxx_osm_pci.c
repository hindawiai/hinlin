<शैली गुरु>
/*
 * Linux driver attachment glue क्रम PCI based controllers.
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
 * $Id: //depot/aic7xxx/linux/drivers/scsi/aic7xxx/aic7xxx_osm_pci.c#47 $
 */

#समावेश "aic7xxx_osm.h"
#समावेश "aic7xxx_pci.h"

/* Define the macro locally since it's dअगरferent क्रम dअगरferent class of chips.
*/
#घोषणा ID(x)	ID_C(x, PCI_CLASS_STORAGE_SCSI)

अटल स्थिर काष्ठा pci_device_id ahc_linux_pci_id_table[] = अणु
	/* aic7850 based controllers */
	ID(ID_AHA_2902_04_10_15_20C_30C),
	/* aic7860 based controllers */
	ID(ID_AHA_2930CU),
	ID(ID_AHA_1480A & ID_DEV_VENDOR_MASK),
	ID(ID_AHA_2940AU_0 & ID_DEV_VENDOR_MASK),
	ID(ID_AHA_2940AU_CN & ID_DEV_VENDOR_MASK),
	ID(ID_AHA_2930C_VAR & ID_DEV_VENDOR_MASK),
	/* aic7870 based controllers */
	ID(ID_AHA_2940),
	ID(ID_AHA_3940),
	ID(ID_AHA_398X),
	ID(ID_AHA_2944),
	ID(ID_AHA_3944),
	ID(ID_AHA_4944),
	/* aic7880 based controllers */
	ID(ID_AHA_2940U & ID_DEV_VENDOR_MASK),
	ID(ID_AHA_3940U & ID_DEV_VENDOR_MASK),
	ID(ID_AHA_2944U & ID_DEV_VENDOR_MASK),
	ID(ID_AHA_3944U & ID_DEV_VENDOR_MASK),
	ID(ID_AHA_398XU & ID_DEV_VENDOR_MASK),
	ID(ID_AHA_4944U & ID_DEV_VENDOR_MASK),
	ID(ID_AHA_2930U & ID_DEV_VENDOR_MASK),
	ID(ID_AHA_2940U_PRO & ID_DEV_VENDOR_MASK),
	ID(ID_AHA_2940U_CN & ID_DEV_VENDOR_MASK),
	/* aic7890 based controllers */
	ID(ID_AHA_2930U2),
	ID(ID_AHA_2940U2B),
	ID(ID_AHA_2940U2_OEM),
	ID(ID_AHA_2940U2),
	ID(ID_AHA_2950U2B),
	ID16(ID_AIC7890_ARO & ID_AIC7895_ARO_MASK),
	ID(ID_AAA_131U2),
	/* aic7890 based controllers */
	ID(ID_AHA_29160),
	ID(ID_AHA_29160_CPQ),
	ID(ID_AHA_29160N),
	ID(ID_AHA_29160C),
	ID(ID_AHA_29160B),
	ID(ID_AHA_19160B),
	ID(ID_AIC7892_ARO),
	/* aic7892 based controllers */
	ID(ID_AHA_2940U_DUAL),
	ID(ID_AHA_3940AU),
	ID(ID_AHA_3944AU),
	ID(ID_AIC7895_ARO),
	ID(ID_AHA_3950U2B_0),
	ID(ID_AHA_3950U2B_1),
	ID(ID_AHA_3950U2D_0),
	ID(ID_AHA_3950U2D_1),
	ID(ID_AIC7896_ARO),
	/* aic7899 based controllers */
	ID(ID_AHA_3960D),
	ID(ID_AHA_3960D_CPQ),
	ID(ID_AIC7899_ARO),
	/* Generic chip probes क्रम devices we करोn't know exactly. */
	ID(ID_AIC7850 & ID_DEV_VENDOR_MASK),
	ID(ID_AIC7855 & ID_DEV_VENDOR_MASK),
	ID(ID_AIC7859 & ID_DEV_VENDOR_MASK),
	ID(ID_AIC7860 & ID_DEV_VENDOR_MASK),
	ID(ID_AIC7870 & ID_DEV_VENDOR_MASK),
	ID(ID_AIC7880 & ID_DEV_VENDOR_MASK),
 	ID16(ID_AIC7890 & ID_9005_GENERIC_MASK),
 	ID16(ID_AIC7892 & ID_9005_GENERIC_MASK),
	ID(ID_AIC7895 & ID_DEV_VENDOR_MASK),
	ID16(ID_AIC7896 & ID_9005_GENERIC_MASK),
	ID16(ID_AIC7899 & ID_9005_GENERIC_MASK),
	ID(ID_AIC7810 & ID_DEV_VENDOR_MASK),
	ID(ID_AIC7815 & ID_DEV_VENDOR_MASK),
	अणु 0 पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE(pci, ahc_linux_pci_id_table);

अटल पूर्णांक __maybe_unused
ahc_linux_pci_dev_suspend(काष्ठा device *dev)
अणु
	काष्ठा ahc_softc *ahc = dev_get_drvdata(dev);

	वापस ahc_suspend(ahc);
पूर्ण

अटल पूर्णांक __maybe_unused
ahc_linux_pci_dev_resume(काष्ठा device *dev)
अणु
	काष्ठा ahc_softc *ahc = dev_get_drvdata(dev);

	ahc_pci_resume(ahc);

	वापस (ahc_resume(ahc));
पूर्ण

अटल व्योम
ahc_linux_pci_dev_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा ahc_softc *ahc = pci_get_drvdata(pdev);
	u_दीर्घ s;

	अगर (ahc->platक्रमm_data && ahc->platक्रमm_data->host)
			scsi_हटाओ_host(ahc->platक्रमm_data->host);

	ahc_lock(ahc, &s);
	ahc_पूर्णांकr_enable(ahc, FALSE);
	ahc_unlock(ahc, &s);
	ahc_मुक्त(ahc);
पूर्ण

अटल व्योम
ahc_linux_pci_inherit_flags(काष्ठा ahc_softc *ahc)
अणु
	काष्ठा pci_dev *pdev = ahc->dev_softc, *master_pdev;
	अचिन्हित पूर्णांक master_devfn = PCI_DEVFN(PCI_SLOT(pdev->devfn), 0);

	master_pdev = pci_get_slot(pdev->bus, master_devfn);
	अगर (master_pdev) अणु
		काष्ठा ahc_softc *master = pci_get_drvdata(master_pdev);
		अगर (master) अणु
			ahc->flags &= ~AHC_BIOS_ENABLED; 
			ahc->flags |= master->flags & AHC_BIOS_ENABLED;

			ahc->flags &= ~AHC_PRIMARY_CHANNEL; 
			ahc->flags |= master->flags & AHC_PRIMARY_CHANNEL;
		पूर्ण अन्यथा
			prपूर्णांकk(KERN_ERR "aic7xxx: no multichannel peer found!\n");
		pci_dev_put(master_pdev);
	पूर्ण 
पूर्ण

अटल पूर्णांक
ahc_linux_pci_dev_probe(काष्ठा pci_dev *pdev, स्थिर काष्ठा pci_device_id *ent)
अणु
	अक्षर		 buf[80];
	स्थिर uपूर्णांक64_t	 mask_39bit = 0x7FFFFFFFFFULL;
	काष्ठा		 ahc_softc *ahc;
	ahc_dev_softc_t	 pci;
	स्थिर काष्ठा ahc_pci_identity *entry;
	अक्षर		*name;
	पूर्णांक		 error;
	काष्ठा device	*dev = &pdev->dev;

	pci = pdev;
	entry = ahc_find_pci_device(pci);
	अगर (entry == शून्य)
		वापस (-ENODEV);

	/*
	 * Allocate a softc क्रम this card and
	 * set it up क्रम attachment by our
	 * common detect routine.
	 */
	प्र_लिखो(buf, "ahc_pci:%d:%d:%d",
		ahc_get_pci_bus(pci),
		ahc_get_pci_slot(pci),
		ahc_get_pci_function(pci));
	name = kstrdup(buf, GFP_ATOMIC);
	अगर (name == शून्य)
		वापस (-ENOMEM);
	ahc = ahc_alloc(शून्य, name);
	अगर (ahc == शून्य)
		वापस (-ENOMEM);
	अगर (pci_enable_device(pdev)) अणु
		ahc_मुक्त(ahc);
		वापस (-ENODEV);
	पूर्ण
	pci_set_master(pdev);

	अगर (माप(dma_addr_t) > 4
	    && ahc->features & AHC_LARGE_SCBS
	    && dma_set_mask(dev, mask_39bit) == 0
	    && dma_get_required_mask(dev) > DMA_BIT_MASK(32)) अणु
		ahc->flags |= AHC_39BIT_ADDRESSING;
	पूर्ण अन्यथा अणु
		अगर (dma_set_mask(dev, DMA_BIT_MASK(32))) अणु
			ahc_मुक्त(ahc);
			prपूर्णांकk(KERN_WARNING "aic7xxx: No suitable DMA available.\n");
                	वापस (-ENODEV);
		पूर्ण
	पूर्ण
	ahc->dev_softc = pci;
	ahc->dev = &pci->dev;
	error = ahc_pci_config(ahc, entry);
	अगर (error != 0) अणु
		ahc_मुक्त(ahc);
		वापस (-error);
	पूर्ण

	/*
	 * Second Function PCI devices need to inherit some
	 * settings from function 0.
	 */
	अगर ((ahc->features & AHC_MULTI_FUNC) && PCI_FUNC(pdev->devfn) != 0)
		ahc_linux_pci_inherit_flags(ahc);

	pci_set_drvdata(pdev, ahc);
	ahc_linux_रेजिस्टर_host(ahc, &aic7xxx_driver_ढाँचा);
	वापस (0);
पूर्ण

/******************************* PCI Routines *********************************/
uपूर्णांक32_t
ahc_pci_पढ़ो_config(ahc_dev_softc_t pci, पूर्णांक reg, पूर्णांक width)
अणु
	चयन (width) अणु
	हाल 1:
	अणु
		uपूर्णांक8_t retval;

		pci_पढ़ो_config_byte(pci, reg, &retval);
		वापस (retval);
	पूर्ण
	हाल 2:
	अणु
		uपूर्णांक16_t retval;
		pci_पढ़ो_config_word(pci, reg, &retval);
		वापस (retval);
	पूर्ण
	हाल 4:
	अणु
		uपूर्णांक32_t retval;
		pci_पढ़ो_config_dword(pci, reg, &retval);
		वापस (retval);
	पूर्ण
	शेष:
		panic("ahc_pci_read_config: Read size too big");
		/* NOTREACHED */
		वापस (0);
	पूर्ण
पूर्ण

व्योम
ahc_pci_ग_लिखो_config(ahc_dev_softc_t pci, पूर्णांक reg, uपूर्णांक32_t value, पूर्णांक width)
अणु
	चयन (width) अणु
	हाल 1:
		pci_ग_लिखो_config_byte(pci, reg, value);
		अवरोध;
	हाल 2:
		pci_ग_लिखो_config_word(pci, reg, value);
		अवरोध;
	हाल 4:
		pci_ग_लिखो_config_dword(pci, reg, value);
		अवरोध;
	शेष:
		panic("ahc_pci_write_config: Write size too big");
		/* NOTREACHED */
	पूर्ण
पूर्ण

अटल SIMPLE_DEV_PM_OPS(ahc_linux_pci_dev_pm_ops,
			 ahc_linux_pci_dev_suspend,
			 ahc_linux_pci_dev_resume);

अटल काष्ठा pci_driver aic7xxx_pci_driver = अणु
	.name		= "aic7xxx",
	.probe		= ahc_linux_pci_dev_probe,
	.driver.pm	= &ahc_linux_pci_dev_pm_ops,
	.हटाओ		= ahc_linux_pci_dev_हटाओ,
	.id_table	= ahc_linux_pci_id_table
पूर्ण;

पूर्णांक
ahc_linux_pci_init(व्योम)
अणु
	वापस pci_रेजिस्टर_driver(&aic7xxx_pci_driver);
पूर्ण

व्योम
ahc_linux_pci_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&aic7xxx_pci_driver);
पूर्ण

अटल पूर्णांक
ahc_linux_pci_reserve_io_region(काष्ठा ahc_softc *ahc, resource_माप_प्रकार *base)
अणु
	अगर (aic7xxx_allow_memio == 0)
		वापस (ENOMEM);

	*base = pci_resource_start(ahc->dev_softc, 0);
	अगर (*base == 0)
		वापस (ENOMEM);
	अगर (!request_region(*base, 256, "aic7xxx"))
		वापस (ENOMEM);
	वापस (0);
पूर्ण

अटल पूर्णांक
ahc_linux_pci_reserve_mem_region(काष्ठा ahc_softc *ahc,
				 resource_माप_प्रकार *bus_addr,
				 uपूर्णांक8_t __iomem **maddr)
अणु
	resource_माप_प्रकार	start;
	पूर्णांक	error;

	error = 0;
	start = pci_resource_start(ahc->dev_softc, 1);
	अगर (start != 0) अणु
		*bus_addr = start;
		अगर (!request_mem_region(start, 0x1000, "aic7xxx"))
			error = ENOMEM;
		अगर (error == 0) अणु
			*maddr = ioremap(start, 256);
			अगर (*maddr == शून्य) अणु
				error = ENOMEM;
				release_mem_region(start, 0x1000);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा
		error = ENOMEM;
	वापस (error);
पूर्ण

पूर्णांक
ahc_pci_map_रेजिस्टरs(काष्ठा ahc_softc *ahc)
अणु
	uपूर्णांक32_t command;
	resource_माप_प्रकार	base;
	uपूर्णांक8_t	__iomem *maddr;
	पूर्णांक	 error;

	/*
	 * If its allowed, we prefer memory mapped access.
	 */
	command = ahc_pci_पढ़ो_config(ahc->dev_softc, PCIR_COMMAND, 4);
	command &= ~(PCIM_CMD_PORTEN|PCIM_CMD_MEMEN);
	base = 0;
	maddr = शून्य;
	error = ahc_linux_pci_reserve_mem_region(ahc, &base, &maddr);
	अगर (error == 0) अणु
		ahc->platक्रमm_data->mem_busaddr = base;
		ahc->tag = BUS_SPACE_MEMIO;
		ahc->bsh.maddr = maddr;
		ahc_pci_ग_लिखो_config(ahc->dev_softc, PCIR_COMMAND,
				     command | PCIM_CMD_MEMEN, 4);

		/*
		 * Do a quick test to see अगर memory mapped
		 * I/O is functioning correctly.
		 */
		अगर (ahc_pci_test_रेजिस्टर_access(ahc) != 0) अणु

			prपूर्णांकk("aic7xxx: PCI Device %d:%d:%d "
			       "failed memory mapped test.  Using PIO.\n",
			       ahc_get_pci_bus(ahc->dev_softc),
			       ahc_get_pci_slot(ahc->dev_softc),
			       ahc_get_pci_function(ahc->dev_softc));
			iounmap(maddr);
			release_mem_region(ahc->platक्रमm_data->mem_busaddr,
					   0x1000);
			ahc->bsh.maddr = शून्य;
			maddr = शून्य;
		पूर्ण अन्यथा
			command |= PCIM_CMD_MEMEN;
	पूर्ण अन्यथा अणु
		prपूर्णांकk("aic7xxx: PCI%d:%d:%d MEM region 0x%llx "
		       "unavailable. Cannot memory map device.\n",
		       ahc_get_pci_bus(ahc->dev_softc),
		       ahc_get_pci_slot(ahc->dev_softc),
		       ahc_get_pci_function(ahc->dev_softc),
		       (अचिन्हित दीर्घ दीर्घ)base);
	पूर्ण

	/*
	 * We always prefer memory mapped access.
	 */
	अगर (maddr == शून्य) अणु

		error = ahc_linux_pci_reserve_io_region(ahc, &base);
		अगर (error == 0) अणु
			ahc->tag = BUS_SPACE_PIO;
			ahc->bsh.ioport = (u_दीर्घ)base;
			command |= PCIM_CMD_PORTEN;
		पूर्ण अन्यथा अणु
			prपूर्णांकk("aic7xxx: PCI%d:%d:%d IO region 0x%llx[0..255] "
			       "unavailable. Cannot map device.\n",
			       ahc_get_pci_bus(ahc->dev_softc),
			       ahc_get_pci_slot(ahc->dev_softc),
			       ahc_get_pci_function(ahc->dev_softc),
			       (अचिन्हित दीर्घ दीर्घ)base);
		पूर्ण
	पूर्ण
	ahc_pci_ग_लिखो_config(ahc->dev_softc, PCIR_COMMAND, command, 4);
	वापस (error);
पूर्ण

पूर्णांक
ahc_pci_map_पूर्णांक(काष्ठा ahc_softc *ahc)
अणु
	पूर्णांक error;

	error = request_irq(ahc->dev_softc->irq, ahc_linux_isr,
			    IRQF_SHARED, "aic7xxx", ahc);
	अगर (error == 0)
		ahc->platक्रमm_data->irq = ahc->dev_softc->irq;
	
	वापस (-error);
पूर्ण

