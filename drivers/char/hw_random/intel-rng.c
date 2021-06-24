<शैली गुरु>
/*
 * RNG driver क्रम Intel RNGs
 *
 * Copyright 2005 (c) MontaVista Software, Inc.
 *
 * with the majority of the code coming from:
 *
 * Hardware driver क्रम the Intel/AMD/VIA Ranकरोm Number Generators (RNG)
 * (c) Copyright 2003 Red Hat Inc <jgarzik@redhat.com>
 *
 * derived from
 *
 * Hardware driver क्रम the AMD 768 Ranकरोm Number Generator (RNG)
 * (c) Copyright 2001 Red Hat Inc
 *
 * derived from
 *
 * Hardware driver क्रम Intel i810 Ranकरोm Number Generator (RNG)
 * Copyright 2000,2001 Jeff Garzik <jgarzik@pobox.com>
 * Copyright 2000,2001 Philipp Rumpf <prumpf@mandrakesoft.com>
 *
 * This file is licensed under  the terms of the GNU General Public
 * License version 2. This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#समावेश <linux/hw_अक्रमom.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/stop_machine.h>
#समावेश <linux/delay.h>
#समावेश <linux/slab.h>


#घोषणा PFX	KBUILD_MODNAME ": "

/*
 * RNG रेजिस्टरs
 */
#घोषणा INTEL_RNG_HW_STATUS			0
#घोषणा         INTEL_RNG_PRESENT		0x40
#घोषणा         INTEL_RNG_ENABLED		0x01
#घोषणा INTEL_RNG_STATUS			1
#घोषणा         INTEL_RNG_DATA_PRESENT		0x01
#घोषणा INTEL_RNG_DATA				2

/*
 * Magic address at which Intel PCI bridges locate the RNG
 */
#घोषणा INTEL_RNG_ADDR				0xFFBC015F
#घोषणा INTEL_RNG_ADDR_LEN			3

/*
 * LPC bridge PCI config space रेजिस्टरs
 */
#घोषणा FWH_DEC_EN1_REG_OLD			0xe3
#घोषणा FWH_DEC_EN1_REG_NEW			0xd9 /* high byte of 16-bit रेजिस्टर */
#घोषणा FWH_F8_EN_MASK				0x80

#घोषणा BIOS_CNTL_REG_OLD			0x4e
#घोषणा BIOS_CNTL_REG_NEW			0xdc
#घोषणा BIOS_CNTL_WRITE_ENABLE_MASK		0x01
#घोषणा BIOS_CNTL_LOCK_ENABLE_MASK		0x02

/*
 * Magic address at which Intel Firmware Hubs get accessed
 */
#घोषणा INTEL_FWH_ADDR				0xffff0000
#घोषणा INTEL_FWH_ADDR_LEN			2

/*
 * Intel Firmware Hub command codes (ग_लिखो to any address inside the device)
 */
#घोषणा INTEL_FWH_RESET_CMD			0xff /* aka READ_ARRAY */
#घोषणा INTEL_FWH_READ_ID_CMD			0x90

/*
 * Intel Firmware Hub Read ID command result addresses
 */
#घोषणा INTEL_FWH_MANUFACTURER_CODE_ADDRESS	0x000000
#घोषणा INTEL_FWH_DEVICE_CODE_ADDRESS		0x000001

/*
 * Intel Firmware Hub Read ID command result values
 */
#घोषणा INTEL_FWH_MANUFACTURER_CODE		0x89
#घोषणा INTEL_FWH_DEVICE_CODE_8M		0xac
#घोषणा INTEL_FWH_DEVICE_CODE_4M		0xad

/*
 * Data क्रम PCI driver पूर्णांकerface
 *
 * This data only exists क्रम exporting the supported
 * PCI ids via MODULE_DEVICE_TABLE.  We करो not actually
 * रेजिस्टर a pci_driver, because someone अन्यथा might one day
 * want to रेजिस्टर another driver on the same PCI id.
 */
अटल स्थिर काष्ठा pci_device_id pci_tbl[] = अणु
/* AA
	अणु PCI_DEVICE(0x8086, 0x2418) पूर्ण, */
	अणु PCI_DEVICE(0x8086, 0x2410) पूर्ण, /* AA */
/* AB
	अणु PCI_DEVICE(0x8086, 0x2428) पूर्ण, */
	अणु PCI_DEVICE(0x8086, 0x2420) पूर्ण, /* AB */
/* ??
	अणु PCI_DEVICE(0x8086, 0x2430) पूर्ण, */
/* BAM, CAM, DBM, FBM, GxM
	अणु PCI_DEVICE(0x8086, 0x2448) पूर्ण, */
	अणु PCI_DEVICE(0x8086, 0x244c) पूर्ण, /* BAM */
	अणु PCI_DEVICE(0x8086, 0x248c) पूर्ण, /* CAM */
	अणु PCI_DEVICE(0x8086, 0x24cc) पूर्ण, /* DBM */
	अणु PCI_DEVICE(0x8086, 0x2641) पूर्ण, /* FBM */
	अणु PCI_DEVICE(0x8086, 0x27b9) पूर्ण, /* GxM */
	अणु PCI_DEVICE(0x8086, 0x27bd) पूर्ण, /* GxM DH */
/* BA, CA, DB, Ex, 6300, Fx, 631x/632x, Gx
	अणु PCI_DEVICE(0x8086, 0x244e) पूर्ण, */
	अणु PCI_DEVICE(0x8086, 0x2440) पूर्ण, /* BA */
	अणु PCI_DEVICE(0x8086, 0x2480) पूर्ण, /* CA */
	अणु PCI_DEVICE(0x8086, 0x24c0) पूर्ण, /* DB */
	अणु PCI_DEVICE(0x8086, 0x24d0) पूर्ण, /* Ex */
	अणु PCI_DEVICE(0x8086, 0x25a1) पूर्ण, /* 6300 */
	अणु PCI_DEVICE(0x8086, 0x2640) पूर्ण, /* Fx */
	अणु PCI_DEVICE(0x8086, 0x2670) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x2671) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x2672) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x2673) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x2674) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x2675) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x2676) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x2677) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x2678) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x2679) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x267a) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x267b) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x267c) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x267d) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x267e) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x267f) पूर्ण, /* 631x/632x */
	अणु PCI_DEVICE(0x8086, 0x27b8) पूर्ण, /* Gx */
/* E
	अणु PCI_DEVICE(0x8086, 0x245e) पूर्ण, */
	अणु PCI_DEVICE(0x8086, 0x2450) पूर्ण, /* E  */
	अणु 0, पूर्ण,	/* terminate list */
पूर्ण;
MODULE_DEVICE_TABLE(pci, pci_tbl);

अटल __initdata पूर्णांक no_fwh_detect;
module_param(no_fwh_detect, पूर्णांक, 0);
MODULE_PARM_DESC(no_fwh_detect, "Skip FWH detection:\n"
                                " positive value - skip if FWH space locked read-only\n"
                                " negative value - skip always");

अटल अंतरभूत u8 hwstatus_get(व्योम __iomem *mem)
अणु
	वापस पढ़ोb(mem + INTEL_RNG_HW_STATUS);
पूर्ण

अटल अंतरभूत u8 hwstatus_set(व्योम __iomem *mem,
			      u8 hw_status)
अणु
	ग_लिखोb(hw_status, mem + INTEL_RNG_HW_STATUS);
	वापस hwstatus_get(mem);
पूर्ण

अटल पूर्णांक पूर्णांकel_rng_data_present(काष्ठा hwrng *rng, पूर्णांक रुको)
अणु
	व्योम __iomem *mem = (व्योम __iomem *)rng->priv;
	पूर्णांक data, i;

	क्रम (i = 0; i < 20; i++) अणु
		data = !!(पढ़ोb(mem + INTEL_RNG_STATUS) &
			  INTEL_RNG_DATA_PRESENT);
		अगर (data || !रुको)
			अवरोध;
		udelay(10);
	पूर्ण
	वापस data;
पूर्ण

अटल पूर्णांक पूर्णांकel_rng_data_पढ़ो(काष्ठा hwrng *rng, u32 *data)
अणु
	व्योम __iomem *mem = (व्योम __iomem *)rng->priv;

	*data = पढ़ोb(mem + INTEL_RNG_DATA);

	वापस 1;
पूर्ण

अटल पूर्णांक पूर्णांकel_rng_init(काष्ठा hwrng *rng)
अणु
	व्योम __iomem *mem = (व्योम __iomem *)rng->priv;
	u8 hw_status;
	पूर्णांक err = -EIO;

	hw_status = hwstatus_get(mem);
	/* turn RNG h/w on, अगर it's off */
	अगर ((hw_status & INTEL_RNG_ENABLED) == 0)
		hw_status = hwstatus_set(mem, hw_status | INTEL_RNG_ENABLED);
	अगर ((hw_status & INTEL_RNG_ENABLED) == 0) अणु
		pr_err(PFX "cannot enable RNG, aborting\n");
		जाओ out;
	पूर्ण
	err = 0;
out:
	वापस err;
पूर्ण

अटल व्योम पूर्णांकel_rng_cleanup(काष्ठा hwrng *rng)
अणु
	व्योम __iomem *mem = (व्योम __iomem *)rng->priv;
	u8 hw_status;

	hw_status = hwstatus_get(mem);
	अगर (hw_status & INTEL_RNG_ENABLED)
		hwstatus_set(mem, hw_status & ~INTEL_RNG_ENABLED);
	अन्यथा
		pr_warn(PFX "unusual: RNG already disabled\n");
पूर्ण


अटल काष्ठा hwrng पूर्णांकel_rng = अणु
	.name		= "intel",
	.init		= पूर्णांकel_rng_init,
	.cleanup	= पूर्णांकel_rng_cleanup,
	.data_present	= पूर्णांकel_rng_data_present,
	.data_पढ़ो	= पूर्णांकel_rng_data_पढ़ो,
पूर्ण;

काष्ठा पूर्णांकel_rng_hw अणु
	काष्ठा pci_dev *dev;
	व्योम __iomem *mem;
	u8 bios_cntl_off;
	u8 bios_cntl_val;
	u8 fwh_dec_en1_off;
	u8 fwh_dec_en1_val;
पूर्ण;

अटल पूर्णांक __init पूर्णांकel_rng_hw_init(व्योम *_पूर्णांकel_rng_hw)
अणु
	काष्ठा पूर्णांकel_rng_hw *पूर्णांकel_rng_hw = _पूर्णांकel_rng_hw;
	u8 mfc, dvc;

	/* पूर्णांकerrupts disabled in stop_machine call */

	अगर (!(पूर्णांकel_rng_hw->fwh_dec_en1_val & FWH_F8_EN_MASK))
		pci_ग_लिखो_config_byte(पूर्णांकel_rng_hw->dev,
		                      पूर्णांकel_rng_hw->fwh_dec_en1_off,
		                      पूर्णांकel_rng_hw->fwh_dec_en1_val |
				      FWH_F8_EN_MASK);
	अगर (!(पूर्णांकel_rng_hw->bios_cntl_val & BIOS_CNTL_WRITE_ENABLE_MASK))
		pci_ग_लिखो_config_byte(पूर्णांकel_rng_hw->dev,
		                      पूर्णांकel_rng_hw->bios_cntl_off,
		                      पूर्णांकel_rng_hw->bios_cntl_val |
				      BIOS_CNTL_WRITE_ENABLE_MASK);

	ग_लिखोb(INTEL_FWH_RESET_CMD, पूर्णांकel_rng_hw->mem);
	ग_लिखोb(INTEL_FWH_READ_ID_CMD, पूर्णांकel_rng_hw->mem);
	mfc = पढ़ोb(पूर्णांकel_rng_hw->mem + INTEL_FWH_MANUFACTURER_CODE_ADDRESS);
	dvc = पढ़ोb(पूर्णांकel_rng_hw->mem + INTEL_FWH_DEVICE_CODE_ADDRESS);
	ग_लिखोb(INTEL_FWH_RESET_CMD, पूर्णांकel_rng_hw->mem);

	अगर (!(पूर्णांकel_rng_hw->bios_cntl_val &
	      (BIOS_CNTL_LOCK_ENABLE_MASK|BIOS_CNTL_WRITE_ENABLE_MASK)))
		pci_ग_लिखो_config_byte(पूर्णांकel_rng_hw->dev,
				      पूर्णांकel_rng_hw->bios_cntl_off,
				      पूर्णांकel_rng_hw->bios_cntl_val);
	अगर (!(पूर्णांकel_rng_hw->fwh_dec_en1_val & FWH_F8_EN_MASK))
		pci_ग_लिखो_config_byte(पूर्णांकel_rng_hw->dev,
				      पूर्णांकel_rng_hw->fwh_dec_en1_off,
				      पूर्णांकel_rng_hw->fwh_dec_en1_val);

	अगर (mfc != INTEL_FWH_MANUFACTURER_CODE ||
	    (dvc != INTEL_FWH_DEVICE_CODE_8M &&
	     dvc != INTEL_FWH_DEVICE_CODE_4M)) अणु
		pr_notice(PFX "FWH not detected\n");
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __init पूर्णांकel_init_hw_काष्ठा(काष्ठा पूर्णांकel_rng_hw *पूर्णांकel_rng_hw,
					काष्ठा pci_dev *dev)
अणु
	पूर्णांकel_rng_hw->bios_cntl_val = 0xff;
	पूर्णांकel_rng_hw->fwh_dec_en1_val = 0xff;
	पूर्णांकel_rng_hw->dev = dev;

	/* Check क्रम Intel 82802 */
	अगर (dev->device < 0x2640) अणु
		पूर्णांकel_rng_hw->fwh_dec_en1_off = FWH_DEC_EN1_REG_OLD;
		पूर्णांकel_rng_hw->bios_cntl_off = BIOS_CNTL_REG_OLD;
	पूर्ण अन्यथा अणु
		पूर्णांकel_rng_hw->fwh_dec_en1_off = FWH_DEC_EN1_REG_NEW;
		पूर्णांकel_rng_hw->bios_cntl_off = BIOS_CNTL_REG_NEW;
	पूर्ण

	pci_पढ़ो_config_byte(dev, पूर्णांकel_rng_hw->fwh_dec_en1_off,
			     &पूर्णांकel_rng_hw->fwh_dec_en1_val);
	pci_पढ़ो_config_byte(dev, पूर्णांकel_rng_hw->bios_cntl_off,
			     &पूर्णांकel_rng_hw->bios_cntl_val);

	अगर ((पूर्णांकel_rng_hw->bios_cntl_val &
	     (BIOS_CNTL_LOCK_ENABLE_MASK|BIOS_CNTL_WRITE_ENABLE_MASK))
	    == BIOS_CNTL_LOCK_ENABLE_MASK) अणु
		अटल __initdata /*स्थिर*/ अक्षर warning[] =
PFX "Firmware space is locked read-only. If you can't or\n"
PFX "don't want to disable this in firmware setup, and if\n"
PFX "you are certain that your system has a functional\n"
PFX "RNG, try using the 'no_fwh_detect' option.\n";

		अगर (no_fwh_detect)
			वापस -ENODEV;
		pr_warn("%s", warning);
		वापस -EBUSY;
	पूर्ण

	पूर्णांकel_rng_hw->mem = ioremap(INTEL_FWH_ADDR, INTEL_FWH_ADDR_LEN);
	अगर (पूर्णांकel_rng_hw->mem == शून्य)
		वापस -EBUSY;

	वापस 0;
पूर्ण


अटल पूर्णांक __init mod_init(व्योम)
अणु
	पूर्णांक err = -ENODEV;
	पूर्णांक i;
	काष्ठा pci_dev *dev = शून्य;
	व्योम __iomem *mem;
	u8 hw_status;
	काष्ठा पूर्णांकel_rng_hw *पूर्णांकel_rng_hw;

	क्रम (i = 0; !dev && pci_tbl[i].venकरोr; ++i)
		dev = pci_get_device(pci_tbl[i].venकरोr, pci_tbl[i].device,
				     शून्य);

	अगर (!dev)
		जाओ out; /* Device not found. */

	अगर (no_fwh_detect < 0) अणु
		pci_dev_put(dev);
		जाओ fwh_करोne;
	पूर्ण

	पूर्णांकel_rng_hw = kदो_स्मृति(माप(*पूर्णांकel_rng_hw), GFP_KERNEL);
	अगर (!पूर्णांकel_rng_hw) अणु
		pci_dev_put(dev);
		जाओ out;
	पूर्ण

	err = पूर्णांकel_init_hw_काष्ठा(पूर्णांकel_rng_hw, dev);
	अगर (err) अणु
		pci_dev_put(dev);
		kमुक्त(पूर्णांकel_rng_hw);
		अगर (err == -ENODEV)
			जाओ fwh_करोne;
		जाओ out;
	पूर्ण

	/*
	 * Since the BIOS code/data is going to disappear from its normal
	 * location with the Read ID command, all activity on the प्रणाली
	 * must be stopped until the state is back to normal.
	 *
	 * Use stop_machine because IPIs can be blocked by disabling
	 * पूर्णांकerrupts.
	 */
	err = stop_machine(पूर्णांकel_rng_hw_init, पूर्णांकel_rng_hw, शून्य);
	pci_dev_put(dev);
	iounmap(पूर्णांकel_rng_hw->mem);
	kमुक्त(पूर्णांकel_rng_hw);
	अगर (err)
		जाओ out;

fwh_करोne:
	err = -ENOMEM;
	mem = ioremap(INTEL_RNG_ADDR, INTEL_RNG_ADDR_LEN);
	अगर (!mem)
		जाओ out;
	पूर्णांकel_rng.priv = (अचिन्हित दीर्घ)mem;

	/* Check क्रम Ranकरोm Number Generator */
	err = -ENODEV;
	hw_status = hwstatus_get(mem);
	अगर ((hw_status & INTEL_RNG_PRESENT) == 0) अणु
		iounmap(mem);
		जाओ out;
	पूर्ण

	pr_info("Intel 82802 RNG detected\n");
	err = hwrng_रेजिस्टर(&पूर्णांकel_rng);
	अगर (err) अणु
		pr_err(PFX "RNG registering failed (%d)\n",
		       err);
		iounmap(mem);
	पूर्ण
out:
	वापस err;

पूर्ण

अटल व्योम __निकास mod_निकास(व्योम)
अणु
	व्योम __iomem *mem = (व्योम __iomem *)पूर्णांकel_rng.priv;

	hwrng_unरेजिस्टर(&पूर्णांकel_rng);
	iounmap(mem);
पूर्ण

module_init(mod_init);
module_निकास(mod_निकास);

MODULE_DESCRIPTION("H/W RNG driver for Intel chipsets");
MODULE_LICENSE("GPL");
