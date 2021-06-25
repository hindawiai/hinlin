<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PMC551 PCI Mezzanine Ram Device
 *
 * Author:
 *	Mark Ferrell <mferrell@mvista.com>
 *	Copyright 1999,2000 Nortel Networks
 *
 * Description:
 *	This driver is पूर्णांकended to support the PMC551 PCI Ram device
 *	from Ramix Inc.  The PMC551 is a PMC Mezzanine module क्रम
 *	cPCI embedded प्रणालीs.  The device contains a single SROM
 *	that initially programs the V370PDC chipset onboard the
 *	device, and various banks of DRAM/SDRAM onboard.  This driver
 *	implements this PCI Ram device as an MTD (Memory Technology
 *	Device) so that it can be used to hold a file प्रणाली, or क्रम
 *	added swap space in embedded प्रणालीs.  Since the memory on
 *	this board isn't as fast as मुख्य memory we करो not try to hook
 *	it पूर्णांकo मुख्य memory as that would simply reduce perक्रमmance
 *	on the प्रणाली.  Using it as a block device allows us to use
 *	it as high speed swap or क्रम a high speed disk device of some
 *	sort.  Which becomes very useful on diskless प्रणालीs in the
 *	embedded market I might add.
 *
 * Notes:
 *	Due to what I assume is more buggy SROM, the 64M PMC551 I
 *	have available claims that all 4 of its DRAM banks have 64MiB
 *	of ram configured (making a gअक्रम total of 256MiB onboard).
 *	This is slightly annoying since the BAR0 size reflects the
 *	aperture size, not the dram size, and the V370PDC supplies no
 *	other method क्रम memory size discovery.  This problem is
 *	mostly only relevant when compiled as a module, as the
 *	unloading of the module with an aperture size smaller than
 *	the ram will cause the driver to detect the onboard memory
 *	size to be equal to the aperture size when the module is
 *	reloaded.  Soooo, to help, the module supports an msize
 *	option to allow the specअगरication of the onboard memory, and
 *	an asize option, to allow the specअगरication of the aperture
 *	size.  The aperture must be equal to or less then the memory
 *	size, the driver will correct this अगर you screw it up.  This
 *	problem is not relevant क्रम compiled in drivers as compiled
 *	in drivers only init once.
 *
 * Credits:
 *	Saeed Karamooz <saeed@ramix.com> of Ramix INC. क्रम the
 *	initial example code of how to initialize this device and क्रम
 *	help with questions I had concerning operation of the device.
 *
 *	Most of the MTD code क्रम this driver was originally written
 *	क्रम the slram.o module in the MTD drivers package which
 *	allows the mapping of प्रणाली memory पूर्णांकo an MTD device.
 *	Since the PMC551 memory module is accessed in the same
 *	fashion as प्रणाली memory, the slram.c code became a very nice
 *	fit to the needs of this driver.  All we added was PCI
 *	detection/initialization to the driver and स्वतःmatically figure
 *	out the size via the PCI detection.o, later changes by Corey
 *	Minyard set up the card to utilize a 1M sliding apature.
 *
 *	Corey Minyard <minyard@nortelnetworks.com>
 *	* Modअगरied driver to utilize a sliding aperture instead of
 *	 mapping all memory पूर्णांकo kernel space which turned out to
 *	 be very wasteful.
 *	* Located a bug in the SROM's initialization sequence that
 *	 made the memory unusable, added a fix to code to touch up
 *	 the DRAM some.
 *
 * Bugs/FIXMEs:
 *	* MUST fix the init function to not spin on a रेजिस्टर
 *	रुकोing क्रम it to set .. this करोes not safely handle busted
 *	devices that never reset the रेजिस्टर correctly which will
 *	cause the प्रणाली to hang w/ a reboot being the only chance at
 *	recover. [sort of fixed, could be better]
 *	* Add I2C handling of the SROM so we can पढ़ो the SROM's inक्रमmation
 *	about the aperture size.  This should always accurately reflect the
 *	onboard memory size.
 *	* Comb the init routine.  It's still a bit cludgy on a few things.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/माला.स>
#समावेश <linux/समयr.h>
#समावेश <linux/major.h>
#समावेश <linux/fs.h>
#समावेश <linux/ioctl.h>
#समावेश <यंत्र/पन.स>
#समावेश <linux/pci.h>
#समावेश <linux/mtd/mtd.h>

#घोषणा PMC551_VERSION \
	"Ramix PMC551 PCI Mezzanine Ram Driver. (C) 1999,2000 Nortel Networks.\n"

#घोषणा PCI_VENDOR_ID_V3_SEMI 0x11b0
#घोषणा PCI_DEVICE_ID_V3_SEMI_V370PDC 0x0200

#घोषणा PMC551_PCI_MEM_MAP0 0x50
#घोषणा PMC551_PCI_MEM_MAP1 0x54
#घोषणा PMC551_PCI_MEM_MAP_MAP_ADDR_MASK 0x3ff00000
#घोषणा PMC551_PCI_MEM_MAP_APERTURE_MASK 0x000000f0
#घोषणा PMC551_PCI_MEM_MAP_REG_EN 0x00000002
#घोषणा PMC551_PCI_MEM_MAP_ENABLE 0x00000001

#घोषणा PMC551_SDRAM_MA  0x60
#घोषणा PMC551_SDRAM_CMD 0x62
#घोषणा PMC551_DRAM_CFG  0x64
#घोषणा PMC551_SYS_CTRL_REG 0x78

#घोषणा PMC551_DRAM_BLK0 0x68
#घोषणा PMC551_DRAM_BLK1 0x6c
#घोषणा PMC551_DRAM_BLK2 0x70
#घोषणा PMC551_DRAM_BLK3 0x74
#घोषणा PMC551_DRAM_BLK_GET_SIZE(x) (524288 << ((x >> 4) & 0x0f))
#घोषणा PMC551_DRAM_BLK_SET_COL_MUX(x, v) (((x) & ~0x00007000) | (((v) & 0x7) << 12))
#घोषणा PMC551_DRAM_BLK_SET_ROW_MUX(x, v) (((x) & ~0x00000f00) | (((v) & 0xf) << 8))

काष्ठा mypriv अणु
	काष्ठा pci_dev *dev;
	u_अक्षर *start;
	u32 base_map0;
	u32 curr_map0;
	u32 asize;
	काष्ठा mtd_info *nextpmc551;
पूर्ण;

अटल काष्ठा mtd_info *pmc551list;

अटल पूर्णांक pmc551_poपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			माप_प्रकार *retlen, व्योम **virt, resource_माप_प्रकार *phys);

अटल पूर्णांक pmc551_erase(काष्ठा mtd_info *mtd, काष्ठा erase_info *instr)
अणु
	काष्ठा mypriv *priv = mtd->priv;
	u32 soff_hi;		/* start address offset hi */
	u32 eoff_hi, eoff_lo;	/* end address offset hi/lo */
	अचिन्हित दीर्घ end;
	u_अक्षर *ptr;
	माप_प्रकार retlen;

#अगर_घोषित CONFIG_MTD_PMC551_DEBUG
	prपूर्णांकk(KERN_DEBUG "pmc551_erase(pos:%ld, len:%ld)\n", (दीर्घ)instr->addr,
		(दीर्घ)instr->len);
#पूर्ण_अगर

	end = instr->addr + instr->len - 1;
	eoff_hi = end & ~(priv->asize - 1);
	soff_hi = instr->addr & ~(priv->asize - 1);
	eoff_lo = end & (priv->asize - 1);

	pmc551_poपूर्णांक(mtd, instr->addr, instr->len, &retlen,
		     (व्योम **)&ptr, शून्य);

	अगर (soff_hi == eoff_hi || mtd->size == priv->asize) अणु
		/* The whole thing fits within one access, so just one shot
		   will करो it. */
		स_रखो(ptr, 0xff, instr->len);
	पूर्ण अन्यथा अणु
		/* We have to करो multiple ग_लिखोs to get all the data
		   written. */
		जबतक (soff_hi != eoff_hi) अणु
#अगर_घोषित CONFIG_MTD_PMC551_DEBUG
			prपूर्णांकk(KERN_DEBUG "pmc551_erase() soff_hi: %ld, "
				"eoff_hi: %ld\n", (दीर्घ)soff_hi, (दीर्घ)eoff_hi);
#पूर्ण_अगर
			स_रखो(ptr, 0xff, priv->asize);
			अगर (soff_hi + priv->asize >= mtd->size) अणु
				जाओ out;
			पूर्ण
			soff_hi += priv->asize;
			pmc551_poपूर्णांक(mtd, (priv->base_map0 | soff_hi),
				     priv->asize, &retlen,
				     (व्योम **)&ptr, शून्य);
		पूर्ण
		स_रखो(ptr, 0xff, eoff_lo);
	पूर्ण

      out:
#अगर_घोषित CONFIG_MTD_PMC551_DEBUG
	prपूर्णांकk(KERN_DEBUG "pmc551_erase() done\n");
#पूर्ण_अगर

	वापस 0;
पूर्ण

अटल पूर्णांक pmc551_poपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			माप_प्रकार *retlen, व्योम **virt, resource_माप_प्रकार *phys)
अणु
	काष्ठा mypriv *priv = mtd->priv;
	u32 soff_hi;
	u32 soff_lo;

#अगर_घोषित CONFIG_MTD_PMC551_DEBUG
	prपूर्णांकk(KERN_DEBUG "pmc551_point(%ld, %ld)\n", (दीर्घ)from, (दीर्घ)len);
#पूर्ण_अगर

	soff_hi = from & ~(priv->asize - 1);
	soff_lo = from & (priv->asize - 1);

	/* Cheap hack optimization */
	अगर (priv->curr_map0 != from) अणु
		pci_ग_लिखो_config_dword(priv->dev, PMC551_PCI_MEM_MAP0,
					(priv->base_map0 | soff_hi));
		priv->curr_map0 = soff_hi;
	पूर्ण

	*virt = priv->start + soff_lo;
	*retlen = len;
	वापस 0;
पूर्ण

अटल पूर्णांक pmc551_unpoपूर्णांक(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len)
अणु
#अगर_घोषित CONFIG_MTD_PMC551_DEBUG
	prपूर्णांकk(KERN_DEBUG "pmc551_unpoint()\n");
#पूर्ण_अगर
	वापस 0;
पूर्ण

अटल पूर्णांक pmc551_पढ़ो(काष्ठा mtd_info *mtd, loff_t from, माप_प्रकार len,
			माप_प्रकार * retlen, u_अक्षर * buf)
अणु
	काष्ठा mypriv *priv = mtd->priv;
	u32 soff_hi;		/* start address offset hi */
	u32 eoff_hi, eoff_lo;	/* end address offset hi/lo */
	अचिन्हित दीर्घ end;
	u_अक्षर *ptr;
	u_अक्षर *copyto = buf;

#अगर_घोषित CONFIG_MTD_PMC551_DEBUG
	prपूर्णांकk(KERN_DEBUG "pmc551_read(pos:%ld, len:%ld) asize: %ld\n",
		(दीर्घ)from, (दीर्घ)len, (दीर्घ)priv->asize);
#पूर्ण_अगर

	end = from + len - 1;
	soff_hi = from & ~(priv->asize - 1);
	eoff_hi = end & ~(priv->asize - 1);
	eoff_lo = end & (priv->asize - 1);

	pmc551_poपूर्णांक(mtd, from, len, retlen, (व्योम **)&ptr, शून्य);

	अगर (soff_hi == eoff_hi) अणु
		/* The whole thing fits within one access, so just one shot
		   will करो it. */
		स_नकल(copyto, ptr, len);
		copyto += len;
	पूर्ण अन्यथा अणु
		/* We have to करो multiple ग_लिखोs to get all the data
		   written. */
		जबतक (soff_hi != eoff_hi) अणु
#अगर_घोषित CONFIG_MTD_PMC551_DEBUG
			prपूर्णांकk(KERN_DEBUG "pmc551_read() soff_hi: %ld, "
				"eoff_hi: %ld\n", (दीर्घ)soff_hi, (दीर्घ)eoff_hi);
#पूर्ण_अगर
			स_नकल(copyto, ptr, priv->asize);
			copyto += priv->asize;
			अगर (soff_hi + priv->asize >= mtd->size) अणु
				जाओ out;
			पूर्ण
			soff_hi += priv->asize;
			pmc551_poपूर्णांक(mtd, soff_hi, priv->asize, retlen,
				     (व्योम **)&ptr, शून्य);
		पूर्ण
		स_नकल(copyto, ptr, eoff_lo);
		copyto += eoff_lo;
	पूर्ण

      out:
#अगर_घोषित CONFIG_MTD_PMC551_DEBUG
	prपूर्णांकk(KERN_DEBUG "pmc551_read() done\n");
#पूर्ण_अगर
	*retlen = copyto - buf;
	वापस 0;
पूर्ण

अटल पूर्णांक pmc551_ग_लिखो(काष्ठा mtd_info *mtd, loff_t to, माप_प्रकार len,
			माप_प्रकार * retlen, स्थिर u_अक्षर * buf)
अणु
	काष्ठा mypriv *priv = mtd->priv;
	u32 soff_hi;		/* start address offset hi */
	u32 eoff_hi, eoff_lo;	/* end address offset hi/lo */
	अचिन्हित दीर्घ end;
	u_अक्षर *ptr;
	स्थिर u_अक्षर *copyfrom = buf;

#अगर_घोषित CONFIG_MTD_PMC551_DEBUG
	prपूर्णांकk(KERN_DEBUG "pmc551_write(pos:%ld, len:%ld) asize:%ld\n",
		(दीर्घ)to, (दीर्घ)len, (दीर्घ)priv->asize);
#पूर्ण_अगर

	end = to + len - 1;
	soff_hi = to & ~(priv->asize - 1);
	eoff_hi = end & ~(priv->asize - 1);
	eoff_lo = end & (priv->asize - 1);

	pmc551_poपूर्णांक(mtd, to, len, retlen, (व्योम **)&ptr, शून्य);

	अगर (soff_hi == eoff_hi) अणु
		/* The whole thing fits within one access, so just one shot
		   will करो it. */
		स_नकल(ptr, copyfrom, len);
		copyfrom += len;
	पूर्ण अन्यथा अणु
		/* We have to करो multiple ग_लिखोs to get all the data
		   written. */
		जबतक (soff_hi != eoff_hi) अणु
#अगर_घोषित CONFIG_MTD_PMC551_DEBUG
			prपूर्णांकk(KERN_DEBUG "pmc551_write() soff_hi: %ld, "
				"eoff_hi: %ld\n", (दीर्घ)soff_hi, (दीर्घ)eoff_hi);
#पूर्ण_अगर
			स_नकल(ptr, copyfrom, priv->asize);
			copyfrom += priv->asize;
			अगर (soff_hi >= mtd->size) अणु
				जाओ out;
			पूर्ण
			soff_hi += priv->asize;
			pmc551_poपूर्णांक(mtd, soff_hi, priv->asize, retlen,
				     (व्योम **)&ptr, शून्य);
		पूर्ण
		स_नकल(ptr, copyfrom, eoff_lo);
		copyfrom += eoff_lo;
	पूर्ण

      out:
#अगर_घोषित CONFIG_MTD_PMC551_DEBUG
	prपूर्णांकk(KERN_DEBUG "pmc551_write() done\n");
#पूर्ण_अगर
	*retlen = copyfrom - buf;
	वापस 0;
पूर्ण

/*
 * Fixup routines क्रम the V370PDC
 * PCI device ID 0x020011b0
 *
 * This function basically kick starts the DRAM oboard the card and माला_लो it
 * पढ़ोy to be used.  Beक्रमe this is करोne the device पढ़ोs VERY erratic, so
 * much that it can crash the Linux 2.2.x series kernels when a user cat's
 * /proc/pci .. though that is मुख्यly a kernel bug in handling the PCI DEVSEL
 * रेजिस्टर.  FIXME: stop spinning on रेजिस्टरs .. must implement a समयout
 * mechanism
 * वापसs the size of the memory region found.
 */
अटल पूर्णांक __init fixup_pmc551(काष्ठा pci_dev *dev)
अणु
#अगर_घोषित CONFIG_MTD_PMC551_BUGFIX
	u32 dram_data;
#पूर्ण_अगर
	u32 size, dcmd, cfg, dपंचांगp;
	u16 cmd, पंचांगp, i;
	u8 bcmd, counter;

	/* Sanity Check */
	अगर (!dev) अणु
		वापस -ENODEV;
	पूर्ण

	/*
	 * Attempt to reset the card
	 * FIXME: Stop Spinning रेजिस्टरs
	 */
	counter = 0;
	/* unlock रेजिस्टरs */
	pci_ग_लिखो_config_byte(dev, PMC551_SYS_CTRL_REG, 0xA5);
	/* पढ़ो in old data */
	pci_पढ़ो_config_byte(dev, PMC551_SYS_CTRL_REG, &bcmd);
	/* bang the reset line up and करोwn क्रम a few */
	क्रम (i = 0; i < 10; i++) अणु
		counter = 0;
		bcmd &= ~0x80;
		जबतक (counter++ < 100) अणु
			pci_ग_लिखो_config_byte(dev, PMC551_SYS_CTRL_REG, bcmd);
		पूर्ण
		counter = 0;
		bcmd |= 0x80;
		जबतक (counter++ < 100) अणु
			pci_ग_लिखो_config_byte(dev, PMC551_SYS_CTRL_REG, bcmd);
		पूर्ण
	पूर्ण
	bcmd |= (0x40 | 0x20);
	pci_ग_लिखो_config_byte(dev, PMC551_SYS_CTRL_REG, bcmd);

	/*
	 * Take care and turn off the memory on the device जबतक we
	 * tweak the configurations
	 */
	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	पंचांगp = cmd & ~(PCI_COMMAND_IO | PCI_COMMAND_MEMORY);
	pci_ग_लिखो_config_word(dev, PCI_COMMAND, पंचांगp);

	/*
	 * Disable existing aperture beक्रमe probing memory size
	 */
	pci_पढ़ो_config_dword(dev, PMC551_PCI_MEM_MAP0, &dcmd);
	dपंचांगp = (dcmd | PMC551_PCI_MEM_MAP_ENABLE | PMC551_PCI_MEM_MAP_REG_EN);
	pci_ग_लिखो_config_dword(dev, PMC551_PCI_MEM_MAP0, dपंचांगp);
	/*
	 * Grab old BAR0 config so that we can figure out memory size
	 * This is another bit of kludge going on.  The reason क्रम the
	 * redundancy is I am hoping to retain the original configuration
	 * previously asचिन्हित to the card by the BIOS or some previous
	 * fixup routine in the kernel.  So we पढ़ो the old config पूर्णांकo cfg,
	 * then ग_लिखो all 1's to the memory space, पढ़ो back the result पूर्णांकo
	 * "size", and then ग_लिखो back all the old config.
	 */
	pci_पढ़ो_config_dword(dev, PCI_BASE_ADDRESS_0, &cfg);
#अगर_अघोषित CONFIG_MTD_PMC551_BUGFIX
	pci_ग_लिखो_config_dword(dev, PCI_BASE_ADDRESS_0, ~0);
	pci_पढ़ो_config_dword(dev, PCI_BASE_ADDRESS_0, &size);
	size = (size & PCI_BASE_ADDRESS_MEM_MASK);
	size &= ~(size - 1);
	pci_ग_लिखो_config_dword(dev, PCI_BASE_ADDRESS_0, cfg);
#अन्यथा
	/*
	 * Get the size of the memory by पढ़ोing all the DRAM size values
	 * and adding them up.
	 *
	 * KLUDGE ALERT: the boards we are using have invalid column and
	 * row mux values.  We fix them here, but this will अवरोध other
	 * memory configurations.
	 */
	pci_पढ़ो_config_dword(dev, PMC551_DRAM_BLK0, &dram_data);
	size = PMC551_DRAM_BLK_GET_SIZE(dram_data);
	dram_data = PMC551_DRAM_BLK_SET_COL_MUX(dram_data, 0x5);
	dram_data = PMC551_DRAM_BLK_SET_ROW_MUX(dram_data, 0x9);
	pci_ग_लिखो_config_dword(dev, PMC551_DRAM_BLK0, dram_data);

	pci_पढ़ो_config_dword(dev, PMC551_DRAM_BLK1, &dram_data);
	size += PMC551_DRAM_BLK_GET_SIZE(dram_data);
	dram_data = PMC551_DRAM_BLK_SET_COL_MUX(dram_data, 0x5);
	dram_data = PMC551_DRAM_BLK_SET_ROW_MUX(dram_data, 0x9);
	pci_ग_लिखो_config_dword(dev, PMC551_DRAM_BLK1, dram_data);

	pci_पढ़ो_config_dword(dev, PMC551_DRAM_BLK2, &dram_data);
	size += PMC551_DRAM_BLK_GET_SIZE(dram_data);
	dram_data = PMC551_DRAM_BLK_SET_COL_MUX(dram_data, 0x5);
	dram_data = PMC551_DRAM_BLK_SET_ROW_MUX(dram_data, 0x9);
	pci_ग_लिखो_config_dword(dev, PMC551_DRAM_BLK2, dram_data);

	pci_पढ़ो_config_dword(dev, PMC551_DRAM_BLK3, &dram_data);
	size += PMC551_DRAM_BLK_GET_SIZE(dram_data);
	dram_data = PMC551_DRAM_BLK_SET_COL_MUX(dram_data, 0x5);
	dram_data = PMC551_DRAM_BLK_SET_ROW_MUX(dram_data, 0x9);
	pci_ग_लिखो_config_dword(dev, PMC551_DRAM_BLK3, dram_data);

	/*
	 * Oops .. something went wrong
	 */
	अगर ((size &= PCI_BASE_ADDRESS_MEM_MASK) == 0) अणु
		वापस -ENODEV;
	पूर्ण
#पूर्ण_अगर				/* CONFIG_MTD_PMC551_BUGFIX */

	अगर ((cfg & PCI_BASE_ADDRESS_SPACE) != PCI_BASE_ADDRESS_SPACE_MEMORY) अणु
		वापस -ENODEV;
	पूर्ण

	/*
	 * Preअक्षरge Dram
	 */
	pci_ग_लिखो_config_word(dev, PMC551_SDRAM_MA, 0x0400);
	pci_ग_लिखो_config_word(dev, PMC551_SDRAM_CMD, 0x00bf);

	/*
	 * Wait until command has gone through
	 * FIXME: रेजिस्टर spinning issue
	 */
	करो अणु
		pci_पढ़ो_config_word(dev, PMC551_SDRAM_CMD, &cmd);
		अगर (counter++ > 100)
			अवरोध;
	पूर्ण जबतक ((PCI_COMMAND_IO) & cmd);

	/*
	 * Turn on स्वतः refresh
	 * The loop is taken directly from Ramix's example code.  I assume that
	 * this must be held high क्रम some duration of समय, but I can find no
	 * करोcumentation refrencing the reasons why.
	 */
	क्रम (i = 1; i <= 8; i++) अणु
		pci_ग_लिखो_config_word(dev, PMC551_SDRAM_CMD, 0x0df);

		/*
		 * Make certain command has gone through
		 * FIXME: रेजिस्टर spinning issue
		 */
		counter = 0;
		करो अणु
			pci_पढ़ो_config_word(dev, PMC551_SDRAM_CMD, &cmd);
			अगर (counter++ > 100)
				अवरोध;
		पूर्ण जबतक ((PCI_COMMAND_IO) & cmd);
	पूर्ण

	pci_ग_लिखो_config_word(dev, PMC551_SDRAM_MA, 0x0020);
	pci_ग_लिखो_config_word(dev, PMC551_SDRAM_CMD, 0x0ff);

	/*
	 * Wait until command completes
	 * FIXME: रेजिस्टर spinning issue
	 */
	counter = 0;
	करो अणु
		pci_पढ़ो_config_word(dev, PMC551_SDRAM_CMD, &cmd);
		अगर (counter++ > 100)
			अवरोध;
	पूर्ण जबतक ((PCI_COMMAND_IO) & cmd);

	pci_पढ़ो_config_dword(dev, PMC551_DRAM_CFG, &dcmd);
	dcmd |= 0x02000000;
	pci_ग_लिखो_config_dword(dev, PMC551_DRAM_CFG, dcmd);

	/*
	 * Check to make certain fast back-to-back, अगर not
	 * then set it so
	 */
	pci_पढ़ो_config_word(dev, PCI_STATUS, &cmd);
	अगर ((cmd & PCI_COMMAND_FAST_BACK) == 0) अणु
		cmd |= PCI_COMMAND_FAST_BACK;
		pci_ग_लिखो_config_word(dev, PCI_STATUS, cmd);
	पूर्ण

	/*
	 * Check to make certain the DEVSEL is set correctly, this device
	 * has a tendency to निश्चित DEVSEL and TRDY when a ग_लिखो is perक्रमmed
	 * to the memory when memory is पढ़ो-only
	 */
	अगर ((cmd & PCI_STATUS_DEVSEL_MASK) != 0x0) अणु
		cmd &= ~PCI_STATUS_DEVSEL_MASK;
		pci_ग_लिखो_config_word(dev, PCI_STATUS, cmd);
	पूर्ण
	/*
	 * Set to be prefetchable and put everything back based on old cfg.
	 * it's possible that the reset of the V370PDC nuked the original
	 * setup
	 */
	/*
	   cfg |= PCI_BASE_ADDRESS_MEM_PREFETCH;
	   pci_ग_लिखो_config_dword( dev, PCI_BASE_ADDRESS_0, cfg );
	 */

	/*
	 * Turn PCI memory and I/O bus access back on
	 */
	pci_ग_लिखो_config_word(dev, PCI_COMMAND,
			      PCI_COMMAND_MEMORY | PCI_COMMAND_IO);
#अगर_घोषित CONFIG_MTD_PMC551_DEBUG
	/*
	 * Some screen fun
	 */
	prपूर्णांकk(KERN_DEBUG "pmc551: %d%sB (0x%x) of %sprefetchable memory at "
		"0x%llx\n", (size < 1024) ? size : (size < 1048576) ?
		size >> 10 : size >> 20,
		(size < 1024) ? "" : (size < 1048576) ? "Ki" : "Mi", size,
		((dcmd & (0x1 << 3)) == 0) ? "non-" : "",
		(अचिन्हित दीर्घ दीर्घ)pci_resource_start(dev, 0));

	/*
	 * Check to see the state of the memory
	 */
	pci_पढ़ो_config_dword(dev, PMC551_DRAM_BLK0, &dcmd);
	prपूर्णांकk(KERN_DEBUG "pmc551: DRAM_BLK0 Flags: %s,%s\n"
		"pmc551: DRAM_BLK0 Size: %d at %d\n"
		"pmc551: DRAM_BLK0 Row MUX: %d, Col MUX: %d\n",
		(((0x1 << 1) & dcmd) == 0) ? "RW" : "RO",
		(((0x1 << 0) & dcmd) == 0) ? "Off" : "On",
		PMC551_DRAM_BLK_GET_SIZE(dcmd),
		((dcmd >> 20) & 0x7FF), ((dcmd >> 13) & 0x7),
		((dcmd >> 9) & 0xF));

	pci_पढ़ो_config_dword(dev, PMC551_DRAM_BLK1, &dcmd);
	prपूर्णांकk(KERN_DEBUG "pmc551: DRAM_BLK1 Flags: %s,%s\n"
		"pmc551: DRAM_BLK1 Size: %d at %d\n"
		"pmc551: DRAM_BLK1 Row MUX: %d, Col MUX: %d\n",
		(((0x1 << 1) & dcmd) == 0) ? "RW" : "RO",
		(((0x1 << 0) & dcmd) == 0) ? "Off" : "On",
		PMC551_DRAM_BLK_GET_SIZE(dcmd),
		((dcmd >> 20) & 0x7FF), ((dcmd >> 13) & 0x7),
		((dcmd >> 9) & 0xF));

	pci_पढ़ो_config_dword(dev, PMC551_DRAM_BLK2, &dcmd);
	prपूर्णांकk(KERN_DEBUG "pmc551: DRAM_BLK2 Flags: %s,%s\n"
		"pmc551: DRAM_BLK2 Size: %d at %d\n"
		"pmc551: DRAM_BLK2 Row MUX: %d, Col MUX: %d\n",
		(((0x1 << 1) & dcmd) == 0) ? "RW" : "RO",
		(((0x1 << 0) & dcmd) == 0) ? "Off" : "On",
		PMC551_DRAM_BLK_GET_SIZE(dcmd),
		((dcmd >> 20) & 0x7FF), ((dcmd >> 13) & 0x7),
		((dcmd >> 9) & 0xF));

	pci_पढ़ो_config_dword(dev, PMC551_DRAM_BLK3, &dcmd);
	prपूर्णांकk(KERN_DEBUG "pmc551: DRAM_BLK3 Flags: %s,%s\n"
		"pmc551: DRAM_BLK3 Size: %d at %d\n"
		"pmc551: DRAM_BLK3 Row MUX: %d, Col MUX: %d\n",
		(((0x1 << 1) & dcmd) == 0) ? "RW" : "RO",
		(((0x1 << 0) & dcmd) == 0) ? "Off" : "On",
		PMC551_DRAM_BLK_GET_SIZE(dcmd),
		((dcmd >> 20) & 0x7FF), ((dcmd >> 13) & 0x7),
		((dcmd >> 9) & 0xF));

	pci_पढ़ो_config_word(dev, PCI_COMMAND, &cmd);
	prपूर्णांकk(KERN_DEBUG "pmc551: Memory Access %s\n",
		(((0x1 << 1) & cmd) == 0) ? "off" : "on");
	prपूर्णांकk(KERN_DEBUG "pmc551: I/O Access %s\n",
		(((0x1 << 0) & cmd) == 0) ? "off" : "on");

	pci_पढ़ो_config_word(dev, PCI_STATUS, &cmd);
	prपूर्णांकk(KERN_DEBUG "pmc551: Devsel %s\n",
		((PCI_STATUS_DEVSEL_MASK & cmd) == 0x000) ? "Fast" :
		((PCI_STATUS_DEVSEL_MASK & cmd) == 0x200) ? "Medium" :
		((PCI_STATUS_DEVSEL_MASK & cmd) == 0x400) ? "Slow" : "Invalid");

	prपूर्णांकk(KERN_DEBUG "pmc551: %sFast Back-to-Back\n",
		((PCI_COMMAND_FAST_BACK & cmd) == 0) ? "Not " : "");

	pci_पढ़ो_config_byte(dev, PMC551_SYS_CTRL_REG, &bcmd);
	prपूर्णांकk(KERN_DEBUG "pmc551: EEPROM is under %s control\n"
		"pmc551: System Control Register is %slocked to PCI access\n"
		"pmc551: System Control Register is %slocked to EEPROM access\n",
		(bcmd & 0x1) ? "software" : "hardware",
		(bcmd & 0x20) ? "" : "un", (bcmd & 0x40) ? "" : "un");
#पूर्ण_अगर
	वापस size;
पूर्ण

/*
 * Kernel version specअगरic module stuffages
 */

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Mark Ferrell <mferrell@mvista.com>");
MODULE_DESCRIPTION(PMC551_VERSION);

/*
 * Stuff these outside the अगरdef so as to not bust compiled in driver support
 */
अटल पूर्णांक msize = 0;
अटल पूर्णांक asize = 0;

module_param(msize, पूर्णांक, 0);
MODULE_PARM_DESC(msize, "memory size in MiB [1 - 1024]");
module_param(asize, पूर्णांक, 0);
MODULE_PARM_DESC(asize, "aperture size, must be <= memsize [1-1024]");

/*
 * PMC551 Card Initialization
 */
अटल पूर्णांक __init init_pmc551(व्योम)
अणु
	काष्ठा pci_dev *PCI_Device = शून्य;
	काष्ठा mypriv *priv;
	पूर्णांक found = 0;
	काष्ठा mtd_info *mtd;
	पूर्णांक length = 0;

	अगर (msize) अणु
		msize = (1 << (ffs(msize) - 1)) << 20;
		अगर (msize > (1 << 30)) अणु
			prपूर्णांकk(KERN_NOTICE "pmc551: Invalid memory size [%d]\n",
				msize);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (asize) अणु
		asize = (1 << (ffs(asize) - 1)) << 20;
		अगर (asize > (1 << 30)) अणु
			prपूर्णांकk(KERN_NOTICE "pmc551: Invalid aperture size "
				"[%d]\n", asize);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	prपूर्णांकk(KERN_INFO PMC551_VERSION);

	/*
	 * PCU-bus chipset probe.
	 */
	क्रम (;;) अणु

		अगर ((PCI_Device = pci_get_device(PCI_VENDOR_ID_V3_SEMI,
						  PCI_DEVICE_ID_V3_SEMI_V370PDC,
						  PCI_Device)) == शून्य) अणु
			अवरोध;
		पूर्ण

		prपूर्णांकk(KERN_NOTICE "pmc551: Found PCI V370PDC at 0x%llx\n",
			(अचिन्हित दीर्घ दीर्घ)pci_resource_start(PCI_Device, 0));

		/*
		 * The PMC551 device acts VERY weird अगर you करोn't init it
		 * first.  i.e. it will not correctly report devsel.  If क्रम
		 * some reason the sdram is in a wrote-रक्षित state the
		 * device will DEVSEL when it is written to causing problems
		 * with the oldproc.c driver in
		 * some kernels (2.2.*)
		 */
		अगर ((length = fixup_pmc551(PCI_Device)) <= 0) अणु
			prपूर्णांकk(KERN_NOTICE "pmc551: Cannot init SDRAM\n");
			अवरोध;
		पूर्ण

		/*
		 * This is needed until the driver is capable of पढ़ोing the
		 * onboard I2C SROM to discover the "real" memory size.
		 */
		अगर (msize) अणु
			length = msize;
			prपूर्णांकk(KERN_NOTICE "pmc551: Using specified memory "
				"size 0x%x\n", length);
		पूर्ण अन्यथा अणु
			msize = length;
		पूर्ण

		mtd = kzalloc(माप(काष्ठा mtd_info), GFP_KERNEL);
		अगर (!mtd)
			अवरोध;

		priv = kzalloc(माप(काष्ठा mypriv), GFP_KERNEL);
		अगर (!priv) अणु
			kमुक्त(mtd);
			अवरोध;
		पूर्ण
		mtd->priv = priv;
		priv->dev = PCI_Device;

		अगर (asize > length) अणु
			prपूर्णांकk(KERN_NOTICE "pmc551: reducing aperture size to "
				"fit %dM\n", length >> 20);
			priv->asize = asize = length;
		पूर्ण अन्यथा अगर (asize == 0 || asize == length) अणु
			prपूर्णांकk(KERN_NOTICE "pmc551: Using existing aperture "
				"size %dM\n", length >> 20);
			priv->asize = asize = length;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_NOTICE "pmc551: Using specified aperture "
				"size %dM\n", asize >> 20);
			priv->asize = asize;
		पूर्ण
		priv->start = pci_iomap(PCI_Device, 0, priv->asize);

		अगर (!priv->start) अणु
			prपूर्णांकk(KERN_NOTICE "pmc551: Unable to map IO space\n");
			kमुक्त(mtd->priv);
			kमुक्त(mtd);
			अवरोध;
		पूर्ण
#अगर_घोषित CONFIG_MTD_PMC551_DEBUG
		prपूर्णांकk(KERN_DEBUG "pmc551: setting aperture to %d\n",
			ffs(priv->asize >> 20) - 1);
#पूर्ण_अगर

		priv->base_map0 = (PMC551_PCI_MEM_MAP_REG_EN
				   | PMC551_PCI_MEM_MAP_ENABLE
				   | (ffs(priv->asize >> 20) - 1) << 4);
		priv->curr_map0 = priv->base_map0;
		pci_ग_लिखो_config_dword(priv->dev, PMC551_PCI_MEM_MAP0,
					priv->curr_map0);

#अगर_घोषित CONFIG_MTD_PMC551_DEBUG
		prपूर्णांकk(KERN_DEBUG "pmc551: aperture set to %d\n",
			(priv->base_map0 & 0xF0) >> 4);
#पूर्ण_अगर

		mtd->size = msize;
		mtd->flags = MTD_CAP_RAM;
		mtd->_erase = pmc551_erase;
		mtd->_पढ़ो = pmc551_पढ़ो;
		mtd->_ग_लिखो = pmc551_ग_लिखो;
		mtd->_poपूर्णांक = pmc551_poपूर्णांक;
		mtd->_unpoपूर्णांक = pmc551_unpoपूर्णांक;
		mtd->type = MTD_RAM;
		mtd->name = "PMC551 RAM board";
		mtd->erasesize = 0x10000;
		mtd->ग_लिखोsize = 1;
		mtd->owner = THIS_MODULE;

		अगर (mtd_device_रेजिस्टर(mtd, शून्य, 0)) अणु
			prपूर्णांकk(KERN_NOTICE "pmc551: Failed to register new device\n");
			pci_iounmap(PCI_Device, priv->start);
			kमुक्त(mtd->priv);
			kमुक्त(mtd);
			अवरोध;
		पूर्ण

		/* Keep a reference as the mtd_device_रेजिस्टर worked */
		pci_dev_get(PCI_Device);

		prपूर्णांकk(KERN_NOTICE "Registered pmc551 memory device.\n");
		prपूर्णांकk(KERN_NOTICE "Mapped %dMiB of memory from 0x%p to 0x%p\n",
			priv->asize >> 20,
			priv->start, priv->start + priv->asize);
		prपूर्णांकk(KERN_NOTICE "Total memory is %d%sB\n",
			(length < 1024) ? length :
			(length < 1048576) ? length >> 10 : length >> 20,
			(length < 1024) ? "" : (length < 1048576) ? "Ki" : "Mi");
		priv->nextpmc551 = pmc551list;
		pmc551list = mtd;
		found++;
	पूर्ण

	/* Exited early, reference left over */
	pci_dev_put(PCI_Device);

	अगर (!pmc551list) अणु
		prपूर्णांकk(KERN_NOTICE "pmc551: not detected\n");
		वापस -ENODEV;
	पूर्ण अन्यथा अणु
		prपूर्णांकk(KERN_NOTICE "pmc551: %d pmc551 devices loaded\n", found);
		वापस 0;
	पूर्ण
पूर्ण

/*
 * PMC551 Card Cleanup
 */
अटल व्योम __निकास cleanup_pmc551(व्योम)
अणु
	पूर्णांक found = 0;
	काष्ठा mtd_info *mtd;
	काष्ठा mypriv *priv;

	जबतक ((mtd = pmc551list)) अणु
		priv = mtd->priv;
		pmc551list = priv->nextpmc551;

		अगर (priv->start) अणु
			prपूर्णांकk(KERN_DEBUG "pmc551: unmapping %dMiB starting at "
				"0x%p\n", priv->asize >> 20, priv->start);
			pci_iounmap(priv->dev, priv->start);
		पूर्ण
		pci_dev_put(priv->dev);

		kमुक्त(mtd->priv);
		mtd_device_unरेजिस्टर(mtd);
		kमुक्त(mtd);
		found++;
	पूर्ण

	prपूर्णांकk(KERN_NOTICE "pmc551: %d pmc551 devices unloaded\n", found);
पूर्ण

module_init(init_pmc551);
module_निकास(cleanup_pmc551);
