<शैली गुरु>
/*
 *  Copyright (C) 1998-2000  Andre Hedrick <andre@linux-ide.org>
 *  Copyright (C) 1995-1998  Mark Lord
 *  Copyright (C) 2007-2009  Bartlomiej Zolnierkiewicz
 *
 *  May be copied or modअगरied under the terms of the GNU General Public License
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/pci.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/ide.h>
#समावेश <linux/dma-mapping.h>

#समावेश <यंत्र/पन.स>

/**
 *	ide_setup_pci_baseregs	-	place a PCI IDE controller native
 *	@dev: PCI device of पूर्णांकerface to चयन native
 *	@name: Name of पूर्णांकerface
 *
 *	We attempt to place the PCI पूर्णांकerface पूर्णांकo PCI native mode. If
 *	we succeed the BARs are ok and the controller is in PCI mode.
 *	Returns 0 on success or an त्रुटि_सं code.
 *
 *	FIXME: अगर we program the पूर्णांकerface and then fail to set the BARS
 *	we करोn't चयन it back to legacy mode. Do we actually care ??
 */

अटल पूर्णांक ide_setup_pci_baseregs(काष्ठा pci_dev *dev, स्थिर अक्षर *name)
अणु
	u8 progअगर = 0;

	/*
	 * Place both IDE पूर्णांकerfaces पूर्णांकo PCI "native" mode:
	 */
	अगर (pci_पढ़ो_config_byte(dev, PCI_CLASS_PROG, &progअगर) ||
			 (progअगर & 5) != 5) अणु
		अगर ((progअगर & 0xa) != 0xa) अणु
			prपूर्णांकk(KERN_INFO "%s %s: device not capable of full "
				"native PCI mode\n", name, pci_name(dev));
			वापस -EOPNOTSUPP;
		पूर्ण
		prपूर्णांकk(KERN_INFO "%s %s: placing both ports into native PCI "
			"mode\n", name, pci_name(dev));
		(व्योम) pci_ग_लिखो_config_byte(dev, PCI_CLASS_PROG, progअगर|5);
		अगर (pci_पढ़ो_config_byte(dev, PCI_CLASS_PROG, &progअगर) ||
		    (progअगर & 5) != 5) अणु
			prपूर्णांकk(KERN_ERR "%s %s: rewrite of PROGIF failed, "
				"wanted 0x%04x, got 0x%04x\n",
				name, pci_name(dev), progअगर | 5, progअगर);
			वापस -EOPNOTSUPP;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_IDEDMA_PCI
अटल पूर्णांक ide_pci_clear_simplex(अचिन्हित दीर्घ dma_base, स्थिर अक्षर *name)
अणु
	u8 dma_stat = inb(dma_base + 2);

	outb(dma_stat & 0x60, dma_base + 2);
	dma_stat = inb(dma_base + 2);

	वापस (dma_stat & 0x80) ? 1 : 0;
पूर्ण

/**
 *	ide_pci_dma_base	-	setup BMIBA
 *	@hwअगर: IDE पूर्णांकerface
 *	@d: IDE port info
 *
 *	Fetch the DMA Bus-Master-I/O-Base-Address (BMIBA) from PCI space.
 */

अचिन्हित दीर्घ ide_pci_dma_base(ide_hwअगर_t *hwअगर, स्थिर काष्ठा ide_port_info *d)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	अचिन्हित दीर्घ dma_base = 0;

	अगर (hwअगर->host_flags & IDE_HFLAG_MMIO)
		वापस hwअगर->dma_base;

	अगर (hwअगर->mate && hwअगर->mate->dma_base) अणु
		dma_base = hwअगर->mate->dma_base - (hwअगर->channel ? 0 : 8);
	पूर्ण अन्यथा अणु
		u8 baridx = (d->host_flags & IDE_HFLAG_CS5520) ? 2 : 4;

		dma_base = pci_resource_start(dev, baridx);

		अगर (dma_base == 0) अणु
			prपूर्णांकk(KERN_ERR "%s %s: DMA base is invalid\n",
				d->name, pci_name(dev));
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (hwअगर->channel)
		dma_base += 8;

	वापस dma_base;
पूर्ण
EXPORT_SYMBOL_GPL(ide_pci_dma_base);

पूर्णांक ide_pci_check_simplex(ide_hwअगर_t *hwअगर, स्थिर काष्ठा ide_port_info *d)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);
	u8 dma_stat;

	अगर (d->host_flags & (IDE_HFLAG_MMIO | IDE_HFLAG_CS5520))
		जाओ out;

	अगर (d->host_flags & IDE_HFLAG_CLEAR_SIMPLEX) अणु
		अगर (ide_pci_clear_simplex(hwअगर->dma_base, d->name))
			prपूर्णांकk(KERN_INFO "%s %s: simplex device: DMA forced\n",
				d->name, pci_name(dev));
		जाओ out;
	पूर्ण

	/*
	 * If the device claims "simplex" DMA, this means that only one of
	 * the two पूर्णांकerfaces can be trusted with DMA at any poपूर्णांक in समय
	 * (so we should enable DMA only on one of the two पूर्णांकerfaces).
	 *
	 * FIXME: At this poपूर्णांक we haven't probed the drives so we can't make
	 * the appropriate decision.  Really we should defer this problem until
	 * we tune the drive then try to grab DMA ownership अगर we want to be
	 * the DMA end.  This has to be become dynamic to handle hot-plug.
	 */
	dma_stat = hwअगर->dma_ops->dma_sff_पढ़ो_status(hwअगर);
	अगर ((dma_stat & 0x80) && hwअगर->mate && hwअगर->mate->dma_base) अणु
		prपूर्णांकk(KERN_INFO "%s %s: simplex device: DMA disabled\n",
			d->name, pci_name(dev));
		वापस -1;
	पूर्ण
out:
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ide_pci_check_simplex);

/*
 * Set up BM-DMA capability (PnP BIOS should have करोne this)
 */
पूर्णांक ide_pci_set_master(काष्ठा pci_dev *dev, स्थिर अक्षर *name)
अणु
	u16 pcicmd;

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &pcicmd);

	अगर ((pcicmd & PCI_COMMAND_MASTER) == 0) अणु
		pci_set_master(dev);

		अगर (pci_पढ़ो_config_word(dev, PCI_COMMAND, &pcicmd) ||
		    (pcicmd & PCI_COMMAND_MASTER) == 0) अणु
			prपूर्णांकk(KERN_ERR "%s %s: error updating PCICMD\n",
				name, pci_name(dev));
			वापस -EIO;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ide_pci_set_master);
#पूर्ण_अगर /* CONFIG_BLK_DEV_IDEDMA_PCI */

व्योम ide_setup_pci_noise(काष्ठा pci_dev *dev, स्थिर काष्ठा ide_port_info *d)
अणु
	prपूर्णांकk(KERN_INFO "%s %s: IDE controller (0x%04x:0x%04x rev 0x%02x)\n",
		d->name, pci_name(dev),
		dev->venकरोr, dev->device, dev->revision);
पूर्ण
EXPORT_SYMBOL_GPL(ide_setup_pci_noise);


/**
 *	ide_pci_enable	-	करो PCI enables
 *	@dev: PCI device
 *	@bars: PCI BARs mask
 *	@d: IDE port info
 *
 *	Enable the IDE PCI device. We attempt to enable the device in full
 *	but अगर that fails then we only need IO space. The PCI code should
 *	have setup the proper resources क्रम us alपढ़ोy क्रम controllers in
 *	legacy mode.
 *
 *	Returns zero on success or an error code
 */

अटल पूर्णांक ide_pci_enable(काष्ठा pci_dev *dev, पूर्णांक bars,
			  स्थिर काष्ठा ide_port_info *d)
अणु
	पूर्णांक ret;

	अगर (pci_enable_device(dev)) अणु
		ret = pci_enable_device_io(dev);
		अगर (ret < 0) अणु
			prपूर्णांकk(KERN_WARNING "%s %s: couldn't enable device\n",
				d->name, pci_name(dev));
			जाओ out;
		पूर्ण
		prपूर्णांकk(KERN_WARNING "%s %s: BIOS configuration fixed\n",
			d->name, pci_name(dev));
	पूर्ण

	/*
	 * assume all devices can करो 32-bit DMA क्रम now, we can add
	 * a DMA mask field to the काष्ठा ide_port_info अगर we need it
	 * (or let lower level driver set the DMA mask)
	 */
	ret = dma_set_mask(&dev->dev, DMA_BIT_MASK(32));
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "%s %s: can't set DMA mask\n",
			d->name, pci_name(dev));
		जाओ out;
	पूर्ण

	ret = pci_request_selected_regions(dev, bars, d->name);
	अगर (ret < 0)
		prपूर्णांकk(KERN_ERR "%s %s: can't reserve resources\n",
			d->name, pci_name(dev));
out:
	वापस ret;
पूर्ण

/**
 *	ide_pci_configure	-	configure an unconfigured device
 *	@dev: PCI device
 *	@d: IDE port info
 *
 *	Enable and configure the PCI device we have been passed.
 *	Returns zero on success or an error code.
 */

अटल पूर्णांक ide_pci_configure(काष्ठा pci_dev *dev, स्थिर काष्ठा ide_port_info *d)
अणु
	u16 pcicmd = 0;
	/*
	 * PnP BIOS was *supposed* to have setup this device, but we
	 * can करो it ourselves, so दीर्घ as the BIOS has asचिन्हित an IRQ
	 * (or possibly the device is using a "legacy header" क्रम IRQs).
	 * Maybe the user deliberately *disabled* the device,
	 * but we'll eventually ignore it again अगर no drives respond.
	 */
	अगर (ide_setup_pci_baseregs(dev, d->name) ||
	    pci_ग_लिखो_config_word(dev, PCI_COMMAND, pcicmd | PCI_COMMAND_IO)) अणु
		prपूर्णांकk(KERN_INFO "%s %s: device disabled (BIOS)\n",
			d->name, pci_name(dev));
		वापस -ENODEV;
	पूर्ण
	अगर (pci_पढ़ो_config_word(dev, PCI_COMMAND, &pcicmd)) अणु
		prपूर्णांकk(KERN_ERR "%s %s: error accessing PCI regs\n",
			d->name, pci_name(dev));
		वापस -EIO;
	पूर्ण
	अगर (!(pcicmd & PCI_COMMAND_IO)) अणु
		prपूर्णांकk(KERN_ERR "%s %s: unable to enable IDE controller\n",
			d->name, pci_name(dev));
		वापस -ENXIO;
	पूर्ण
	वापस 0;
पूर्ण

/**
 *	ide_pci_check_iomem	-	check a रेजिस्टर is I/O
 *	@dev: PCI device
 *	@d: IDE port info
 *	@bar: BAR number
 *
 *	Checks अगर a BAR is configured and poपूर्णांकs to MMIO space. If so,
 *	वापस an error code. Otherwise वापस 0
 */

अटल पूर्णांक ide_pci_check_iomem(काष्ठा pci_dev *dev, स्थिर काष्ठा ide_port_info *d,
			       पूर्णांक bar)
अणु
	uदीर्घ flags = pci_resource_flags(dev, bar);

	/* Unconfigured ? */
	अगर (!flags || pci_resource_len(dev, bar) == 0)
		वापस 0;

	/* I/O space */
	अगर (flags & IORESOURCE_IO)
		वापस 0;

	/* Bad */
	वापस -EINVAL;
पूर्ण

/**
 *	ide_hw_configure	-	configure a काष्ठा ide_hw instance
 *	@dev: PCI device holding पूर्णांकerface
 *	@d: IDE port info
 *	@port: port number
 *	@hw: काष्ठा ide_hw instance corresponding to this port
 *
 *	Perक्रमm the initial set up क्रम the hardware पूर्णांकerface काष्ठाure. This
 *	is करोne per पूर्णांकerface port rather than per PCI device. There may be
 *	more than one port per device.
 *
 *	Returns zero on success or an error code.
 */

अटल पूर्णांक ide_hw_configure(काष्ठा pci_dev *dev, स्थिर काष्ठा ide_port_info *d,
			    अचिन्हित पूर्णांक port, काष्ठा ide_hw *hw)
अणु
	अचिन्हित दीर्घ ctl = 0, base = 0;

	अगर ((d->host_flags & IDE_HFLAG_ISA_PORTS) == 0) अणु
		अगर (ide_pci_check_iomem(dev, d, 2 * port) ||
		    ide_pci_check_iomem(dev, d, 2 * port + 1)) अणु
			prपूर्णांकk(KERN_ERR "%s %s: I/O baseregs (BIOS) are "
				"reported as MEM for port %d!\n",
				d->name, pci_name(dev), port);
			वापस -EINVAL;
		पूर्ण

		ctl  = pci_resource_start(dev, 2*port+1);
		base = pci_resource_start(dev, 2*port);
	पूर्ण अन्यथा अणु
		/* Use शेष values */
		ctl = port ? 0x374 : 0x3f4;
		base = port ? 0x170 : 0x1f0;
	पूर्ण

	अगर (!base || !ctl) अणु
		prपूर्णांकk(KERN_ERR "%s %s: bad PCI BARs for port %d, skipping\n",
			d->name, pci_name(dev), port);
		वापस -EINVAL;
	पूर्ण

	स_रखो(hw, 0, माप(*hw));
	hw->dev = &dev->dev;
	ide_std_init_ports(hw, base, ctl | 2);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_BLK_DEV_IDEDMA_PCI
/**
 *	ide_hwअगर_setup_dma	-	configure DMA पूर्णांकerface
 *	@hwअगर: IDE पूर्णांकerface
 *	@d: IDE port info
 *
 *	Set up the DMA base क्रम the पूर्णांकerface. Enable the master bits as
 *	necessary and attempt to bring the device DMA पूर्णांकo a पढ़ोy to use
 *	state
 */

पूर्णांक ide_hwअगर_setup_dma(ide_hwअगर_t *hwअगर, स्थिर काष्ठा ide_port_info *d)
अणु
	काष्ठा pci_dev *dev = to_pci_dev(hwअगर->dev);

	अगर ((d->host_flags & IDE_HFLAG_NO_AUTODMA) == 0 ||
	    ((dev->class >> 8) == PCI_CLASS_STORAGE_IDE &&
	     (dev->class & 0x80))) अणु
		अचिन्हित दीर्घ base = ide_pci_dma_base(hwअगर, d);

		अगर (base == 0)
			वापस -1;

		hwअगर->dma_base = base;

		अगर (hwअगर->dma_ops == शून्य)
			hwअगर->dma_ops = &sff_dma_ops;

		अगर (ide_pci_check_simplex(hwअगर, d) < 0)
			वापस -1;

		अगर (ide_pci_set_master(dev, d->name) < 0)
			वापस -1;

		अगर (hwअगर->host_flags & IDE_HFLAG_MMIO)
			prपूर्णांकk(KERN_INFO "    %s: MMIO-DMA\n", hwअगर->name);
		अन्यथा
			prपूर्णांकk(KERN_INFO "    %s: BM-DMA at 0x%04lx-0x%04lx\n",
					 hwअगर->name, base, base + 7);

		hwअगर->extra_base = base + (hwअगर->channel ? 8 : 16);

		अगर (ide_allocate_dma_engine(hwअगर))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_BLK_DEV_IDEDMA_PCI */

/**
 *	ide_setup_pci_controller	-	set up IDE PCI
 *	@dev: PCI device
 *	@bars: PCI BARs mask
 *	@d: IDE port info
 *	@noisy: verbose flag
 *
 *	Set up the PCI and controller side of the IDE पूर्णांकerface. This brings
 *	up the PCI side of the device, checks that the device is enabled
 *	and enables it अगर need be
 */

अटल पूर्णांक ide_setup_pci_controller(काष्ठा pci_dev *dev, पूर्णांक bars,
				    स्थिर काष्ठा ide_port_info *d, पूर्णांक noisy)
अणु
	पूर्णांक ret;
	u16 pcicmd;

	अगर (noisy)
		ide_setup_pci_noise(dev, d);

	ret = ide_pci_enable(dev, bars, d);
	अगर (ret < 0)
		जाओ out;

	ret = pci_पढ़ो_config_word(dev, PCI_COMMAND, &pcicmd);
	अगर (ret < 0) अणु
		prपूर्णांकk(KERN_ERR "%s %s: error accessing PCI regs\n",
			d->name, pci_name(dev));
		जाओ out_मुक्त_bars;
	पूर्ण
	अगर (!(pcicmd & PCI_COMMAND_IO)) अणु	/* is device disabled? */
		ret = ide_pci_configure(dev, d);
		अगर (ret < 0)
			जाओ out_मुक्त_bars;
		prपूर्णांकk(KERN_INFO "%s %s: device enabled (Linux)\n",
			d->name, pci_name(dev));
	पूर्ण

	जाओ out;

out_मुक्त_bars:
	pci_release_selected_regions(dev, bars);
out:
	वापस ret;
पूर्ण

/**
 *	ide_pci_setup_ports	-	configure ports/devices on PCI IDE
 *	@dev: PCI device
 *	@d: IDE port info
 *	@hw: काष्ठा ide_hw instances corresponding to this PCI IDE device
 *	@hws: काष्ठा ide_hw poपूर्णांकers table to update
 *
 *	Scan the पूर्णांकerfaces attached to this device and करो any
 *	necessary per port setup. Attach the devices and ask the
 *	generic DMA layer to करो its work क्रम us.
 *
 *	Normally called स्वतःmaticall from करो_ide_pci_setup_device,
 *	but is also used directly as a helper function by some controllers
 *	where the chipset setup is not the शेष PCI IDE one.
 */

व्योम ide_pci_setup_ports(काष्ठा pci_dev *dev, स्थिर काष्ठा ide_port_info *d,
			 काष्ठा ide_hw *hw, काष्ठा ide_hw **hws)
अणु
	पूर्णांक channels = (d->host_flags & IDE_HFLAG_SINGLE) ? 1 : 2, port;
	u8 पंचांगp;

	/*
	 * Set up the IDE ports
	 */

	क्रम (port = 0; port < channels; ++port) अणु
		स्थिर काष्ठा ide_pci_enablebit *e = &d->enablebits[port];

		अगर (e->reg && (pci_पढ़ो_config_byte(dev, e->reg, &पंचांगp) ||
		    (पंचांगp & e->mask) != e->val)) अणु
			prपूर्णांकk(KERN_INFO "%s %s: IDE port disabled\n",
				d->name, pci_name(dev));
			जारी;	/* port not enabled */
		पूर्ण

		अगर (ide_hw_configure(dev, d, port, hw + port))
			जारी;

		*(hws + port) = hw + port;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ide_pci_setup_ports);

/*
 * ide_setup_pci_device() looks at the primary/secondary पूर्णांकerfaces
 * on a PCI IDE device and, अगर they are enabled, prepares the IDE driver
 * क्रम use with them.  This generic code works क्रम most PCI chipsets.
 *
 * One thing that is not standardized is the location of the
 * primary/secondary पूर्णांकerface "enable/disable" bits.  For chipsets that
 * we "know" about, this inक्रमmation is in the काष्ठा ide_port_info;
 * क्रम all other chipsets, we just assume both पूर्णांकerfaces are enabled.
 */
अटल पूर्णांक करो_ide_setup_pci_device(काष्ठा pci_dev *dev,
				   स्थिर काष्ठा ide_port_info *d,
				   u8 noisy)
अणु
	पूर्णांक pciirq, ret;

	/*
	 * Can we trust the reported IRQ?
	 */
	pciirq = dev->irq;

	/*
	 * This allows offboard ide-pci cards the enable a BIOS,
	 * verअगरy पूर्णांकerrupt settings of split-mirror pci-config
	 * space, place chipset पूर्णांकo init-mode, and/or preserve
	 * an पूर्णांकerrupt अगर the card is not native ide support.
	 */
	ret = d->init_chipset ? d->init_chipset(dev) : 0;
	अगर (ret < 0)
		जाओ out;

	अगर (ide_pci_is_in_compatibility_mode(dev)) अणु
		अगर (noisy)
			prपूर्णांकk(KERN_INFO "%s %s: not 100%% native mode: will "
				"probe irqs later\n", d->name, pci_name(dev));
		pciirq = 0;
	पूर्ण अन्यथा अगर (!pciirq && noisy) अणु
		prपूर्णांकk(KERN_WARNING "%s %s: bad irq (%d): will probe later\n",
			d->name, pci_name(dev), pciirq);
	पूर्ण अन्यथा अगर (noisy) अणु
		prपूर्णांकk(KERN_INFO "%s %s: 100%% native mode on irq %d\n",
			d->name, pci_name(dev), pciirq);
	पूर्ण

	ret = pciirq;
out:
	वापस ret;
पूर्ण

पूर्णांक ide_pci_init_two(काष्ठा pci_dev *dev1, काष्ठा pci_dev *dev2,
		     स्थिर काष्ठा ide_port_info *d, व्योम *priv)
अणु
	काष्ठा pci_dev *pdev[] = अणु dev1, dev2 पूर्ण;
	काष्ठा ide_host *host;
	पूर्णांक ret, i, n_ports = dev2 ? 4 : 2, bars;
	काष्ठा ide_hw hw[4], *hws[] = अणु शून्य, शून्य, शून्य, शून्य पूर्ण;

	अगर (d->host_flags & IDE_HFLAG_SINGLE)
		bars = (1 << 2) - 1;
	अन्यथा
		bars = (1 << 4) - 1;

	अगर ((d->host_flags & IDE_HFLAG_NO_DMA) == 0) अणु
		अगर (d->host_flags & IDE_HFLAG_CS5520)
			bars |= (1 << 2);
		अन्यथा
			bars |= (1 << 4);
	पूर्ण

	क्रम (i = 0; i < n_ports / 2; i++) अणु
		ret = ide_setup_pci_controller(pdev[i], bars, d, !i);
		अगर (ret < 0) अणु
			अगर (i == 1)
				pci_release_selected_regions(pdev[0], bars);
			जाओ out;
		पूर्ण

		ide_pci_setup_ports(pdev[i], d, &hw[i*2], &hws[i*2]);
	पूर्ण

	host = ide_host_alloc(d, hws, n_ports);
	अगर (host == शून्य) अणु
		ret = -ENOMEM;
		जाओ out_मुक्त_bars;
	पूर्ण

	host->dev[0] = &dev1->dev;
	अगर (dev2)
		host->dev[1] = &dev2->dev;

	host->host_priv = priv;
	host->irq_flags = IRQF_SHARED;

	pci_set_drvdata(pdev[0], host);
	अगर (dev2)
		pci_set_drvdata(pdev[1], host);

	क्रम (i = 0; i < n_ports / 2; i++) अणु
		ret = करो_ide_setup_pci_device(pdev[i], d, !i);

		/*
		 * FIXME: Mom, mom, they stole me the helper function to unकरो
		 * करो_ide_setup_pci_device() on the first device!
		 */
		अगर (ret < 0)
			जाओ out_मुक्त_bars;

		/* fixup IRQ */
		अगर (ide_pci_is_in_compatibility_mode(pdev[i])) अणु
			hw[i*2].irq = pci_get_legacy_ide_irq(pdev[i], 0);
			hw[i*2 + 1].irq = pci_get_legacy_ide_irq(pdev[i], 1);
		पूर्ण अन्यथा
			hw[i*2 + 1].irq = hw[i*2].irq = ret;
	पूर्ण

	ret = ide_host_रेजिस्टर(host, d, hws);
	अगर (ret)
		ide_host_मुक्त(host);
	अन्यथा
		जाओ out;

out_मुक्त_bars:
	i = n_ports / 2;
	जबतक (i--)
		pci_release_selected_regions(pdev[i], bars);
out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(ide_pci_init_two);

पूर्णांक ide_pci_init_one(काष्ठा pci_dev *dev, स्थिर काष्ठा ide_port_info *d,
		     व्योम *priv)
अणु
	वापस ide_pci_init_two(dev, शून्य, d, priv);
पूर्ण
EXPORT_SYMBOL_GPL(ide_pci_init_one);

व्योम ide_pci_हटाओ(काष्ठा pci_dev *dev)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	काष्ठा pci_dev *dev2 = host->dev[1] ? to_pci_dev(host->dev[1]) : शून्य;
	पूर्णांक bars;

	अगर (host->host_flags & IDE_HFLAG_SINGLE)
		bars = (1 << 2) - 1;
	अन्यथा
		bars = (1 << 4) - 1;

	अगर ((host->host_flags & IDE_HFLAG_NO_DMA) == 0) अणु
		अगर (host->host_flags & IDE_HFLAG_CS5520)
			bars |= (1 << 2);
		अन्यथा
			bars |= (1 << 4);
	पूर्ण

	ide_host_हटाओ(host);

	अगर (dev2)
		pci_release_selected_regions(dev2, bars);
	pci_release_selected_regions(dev, bars);

	अगर (dev2)
		pci_disable_device(dev2);
	pci_disable_device(dev);
पूर्ण
EXPORT_SYMBOL_GPL(ide_pci_हटाओ);

#अगर_घोषित CONFIG_PM
पूर्णांक ide_pci_suspend(काष्ठा pci_dev *dev, pm_message_t state)
अणु
	pci_save_state(dev);
	pci_disable_device(dev);
	pci_set_घातer_state(dev, pci_choose_state(dev, state));

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ide_pci_suspend);

पूर्णांक ide_pci_resume(काष्ठा pci_dev *dev)
अणु
	काष्ठा ide_host *host = pci_get_drvdata(dev);
	पूर्णांक rc;

	pci_set_घातer_state(dev, PCI_D0);

	rc = pci_enable_device(dev);
	अगर (rc)
		वापस rc;

	pci_restore_state(dev);
	pci_set_master(dev);

	अगर (host->init_chipset)
		host->init_chipset(dev);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ide_pci_resume);
#पूर्ण_अगर
