<शैली गुरु>
/*
 * generic/शेष IDE host driver
 *
 * Copyright (C) 2004, 2008-2009 Bartlomiej Zolnierkiewicz
 * This code was split off from ide.c.  See it क्रम original copyrights.
 *
 * May be copied or modअगरied under the terms of the GNU General Public License.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/ide.h>
#समावेश <linux/pci_ids.h>

/* FIXME: convert arm to use ide_platक्रमm host driver */
#अगर_घोषित CONFIG_ARM
#समावेश <यंत्र/irq.h>
#पूर्ण_अगर

#घोषणा DRV_NAME	"ide_generic"

अटल पूर्णांक probe_mask;
module_param(probe_mask, पूर्णांक, 0);
MODULE_PARM_DESC(probe_mask, "probe mask for legacy ISA IDE ports");

अटल स्थिर काष्ठा ide_port_info ide_generic_port_info = अणु
	.host_flags		= IDE_HFLAG_NO_DMA,
	.chipset		= ide_generic,
पूर्ण;

#अगर_घोषित CONFIG_ARM
अटल स्थिर u16 legacy_bases[] = अणु 0x1f0 पूर्ण;
अटल स्थिर पूर्णांक legacy_irqs[]  = अणु IRQ_HARDDISK पूर्ण;
#या_अगर defined(CONFIG_ALPHA)
अटल स्थिर u16 legacy_bases[] = अणु 0x1f0, 0x170, 0x1e8, 0x168 पूर्ण;
अटल स्थिर पूर्णांक legacy_irqs[]  = अणु 14, 15, 11, 10 पूर्ण;
#अन्यथा
अटल स्थिर u16 legacy_bases[] = अणु 0x1f0, 0x170, 0x1e8, 0x168, 0x1e0, 0x160 पूर्ण;
अटल स्थिर पूर्णांक legacy_irqs[]  = अणु 14, 15, 11, 10, 8, 12 पूर्ण;
#पूर्ण_अगर

अटल व्योम ide_generic_check_pci_legacy_iobases(पूर्णांक *primary, पूर्णांक *secondary)
अणु
#अगर_घोषित CONFIG_PCI
	काष्ठा pci_dev *p = शून्य;
	u16 val;

	क्रम_each_pci_dev(p) अणु
		अगर (pci_resource_start(p, 0) == 0x1f0)
			*primary = 1;
		अगर (pci_resource_start(p, 2) == 0x170)
			*secondary = 1;

		/* Cyrix CS55अणु1,2पूर्ण0 pre SFF MWDMA ATA on the bridge */
		अगर (p->venकरोr == PCI_VENDOR_ID_CYRIX &&
		    (p->device == PCI_DEVICE_ID_CYRIX_5510 ||
		     p->device == PCI_DEVICE_ID_CYRIX_5520))
			*primary = *secondary = 1;

		/* Intel MPIIX - PIO ATA on non PCI side of bridge */
		अगर (p->venकरोr == PCI_VENDOR_ID_INTEL &&
		    p->device == PCI_DEVICE_ID_INTEL_82371MX) अणु
			pci_पढ़ो_config_word(p, 0x6C, &val);
			अगर (val & 0x8000) अणु
				/* ATA port enabled */
				अगर (val & 0x4000)
					*secondary = 1;
				अन्यथा
					*primary = 1;
			पूर्ण
		पूर्ण
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init ide_generic_init(व्योम)
अणु
	काष्ठा ide_hw hw, *hws[] = अणु &hw पूर्ण;
	अचिन्हित दीर्घ io_addr;
	पूर्णांक i, rc = 0, primary = 0, secondary = 0;

	ide_generic_check_pci_legacy_iobases(&primary, &secondary);

	अगर (!probe_mask) अणु
		prपूर्णांकk(KERN_INFO DRV_NAME ": please use \"probe_mask=0x3f\" "
		     "module parameter for probing all legacy ISA IDE ports\n");

		अगर (primary == 0)
			probe_mask |= 0x1;

		अगर (secondary == 0)
			probe_mask |= 0x2;
	पूर्ण अन्यथा
		prपूर्णांकk(KERN_INFO DRV_NAME ": enforcing probing of I/O ports "
			"upon user request\n");

	क्रम (i = 0; i < ARRAY_SIZE(legacy_bases); i++) अणु
		io_addr = legacy_bases[i];

		अगर ((probe_mask & (1 << i)) && io_addr) अणु
			अगर (!request_region(io_addr, 8, DRV_NAME)) अणु
				prपूर्णांकk(KERN_ERR "%s: I/O resource 0x%lX-0x%lX "
						"not free.\n",
						DRV_NAME, io_addr, io_addr + 7);
				rc = -EBUSY;
				जारी;
			पूर्ण

			अगर (!request_region(io_addr + 0x206, 1, DRV_NAME)) अणु
				prपूर्णांकk(KERN_ERR "%s: I/O resource 0x%lX "
						"not free.\n",
						DRV_NAME, io_addr + 0x206);
				release_region(io_addr, 8);
				rc = -EBUSY;
				जारी;
			पूर्ण

			स_रखो(&hw, 0, माप(hw));
			ide_std_init_ports(&hw, io_addr, io_addr + 0x206);
#अगर_घोषित CONFIG_IA64
			hw.irq = isa_irq_to_vector(legacy_irqs[i]);
#अन्यथा
			hw.irq = legacy_irqs[i];
#पूर्ण_अगर
			rc = ide_host_add(&ide_generic_port_info, hws, 1, शून्य);
			अगर (rc) अणु
				release_region(io_addr + 0x206, 1);
				release_region(io_addr, 8);
			पूर्ण
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण

module_init(ide_generic_init);

MODULE_LICENSE("GPL");
