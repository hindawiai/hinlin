<शैली गुरु>
/*
 * Driver क्रम Nuvoton Technology Corporation w83667hg/w83677hg-i CIR
 *
 * Copyright (C) 2010 Jarod Wilson <jarod@redhat.com>
 * Copyright (C) 2009 Nuvoton PS Team
 *
 * Special thanks to Nuvoton क्रम providing hardware, spec sheets and
 * sample code upon which portions of this driver are based. Indirect
 * thanks also to Maxim Levitsky, whose ene_ir driver this driver is
 * modeled after.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pnp.h>
#समावेश <linux/पन.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <media/rc-core.h>
#समावेश <linux/pci_ids.h>

#समावेश "nuvoton-cir.h"

अटल व्योम nvt_clear_cir_wake_fअगरo(काष्ठा nvt_dev *nvt);

अटल स्थिर काष्ठा nvt_chip nvt_chips[] = अणु
	अणु "w83667hg", NVT_W83667HG पूर्ण,
	अणु "NCT6775F", NVT_6775F पूर्ण,
	अणु "NCT6776F", NVT_6776F पूर्ण,
	अणु "NCT6779D", NVT_6779D पूर्ण,
पूर्ण;

अटल अंतरभूत काष्ठा device *nvt_get_dev(स्थिर काष्ठा nvt_dev *nvt)
अणु
	वापस nvt->rdev->dev.parent;
पूर्ण

अटल अंतरभूत bool is_w83667hg(काष्ठा nvt_dev *nvt)
अणु
	वापस nvt->chip_ver == NVT_W83667HG;
पूर्ण

/* ग_लिखो val to config reg */
अटल अंतरभूत व्योम nvt_cr_ग_लिखो(काष्ठा nvt_dev *nvt, u8 val, u8 reg)
अणु
	outb(reg, nvt->cr_efir);
	outb(val, nvt->cr_efdr);
पूर्ण

/* पढ़ो val from config reg */
अटल अंतरभूत u8 nvt_cr_पढ़ो(काष्ठा nvt_dev *nvt, u8 reg)
अणु
	outb(reg, nvt->cr_efir);
	वापस inb(nvt->cr_efdr);
पूर्ण

/* update config रेजिस्टर bit without changing other bits */
अटल अंतरभूत व्योम nvt_set_reg_bit(काष्ठा nvt_dev *nvt, u8 val, u8 reg)
अणु
	u8 पंचांगp = nvt_cr_पढ़ो(nvt, reg) | val;
	nvt_cr_ग_लिखो(nvt, पंचांगp, reg);
पूर्ण

/* enter extended function mode */
अटल अंतरभूत पूर्णांक nvt_efm_enable(काष्ठा nvt_dev *nvt)
अणु
	अगर (!request_muxed_region(nvt->cr_efir, 2, NVT_DRIVER_NAME))
		वापस -EBUSY;

	/* Enabling Extended Function Mode explicitly requires writing 2x */
	outb(EFER_EFM_ENABLE, nvt->cr_efir);
	outb(EFER_EFM_ENABLE, nvt->cr_efir);

	वापस 0;
पूर्ण

/* निकास extended function mode */
अटल अंतरभूत व्योम nvt_efm_disable(काष्ठा nvt_dev *nvt)
अणु
	outb(EFER_EFM_DISABLE, nvt->cr_efir);

	release_region(nvt->cr_efir, 2);
पूर्ण

/*
 * When you want to address a specअगरic logical device, ग_लिखो its logical
 * device number to CR_LOGICAL_DEV_SEL, then enable/disable by writing
 * 0x1/0x0 respectively to CR_LOGICAL_DEV_EN.
 */
अटल अंतरभूत व्योम nvt_select_logical_dev(काष्ठा nvt_dev *nvt, u8 ldev)
अणु
	nvt_cr_ग_लिखो(nvt, ldev, CR_LOGICAL_DEV_SEL);
पूर्ण

/* select and enable logical device with setting EFM mode*/
अटल अंतरभूत व्योम nvt_enable_logical_dev(काष्ठा nvt_dev *nvt, u8 ldev)
अणु
	nvt_efm_enable(nvt);
	nvt_select_logical_dev(nvt, ldev);
	nvt_cr_ग_लिखो(nvt, LOGICAL_DEV_ENABLE, CR_LOGICAL_DEV_EN);
	nvt_efm_disable(nvt);
पूर्ण

/* select and disable logical device with setting EFM mode*/
अटल अंतरभूत व्योम nvt_disable_logical_dev(काष्ठा nvt_dev *nvt, u8 ldev)
अणु
	nvt_efm_enable(nvt);
	nvt_select_logical_dev(nvt, ldev);
	nvt_cr_ग_लिखो(nvt, LOGICAL_DEV_DISABLE, CR_LOGICAL_DEV_EN);
	nvt_efm_disable(nvt);
पूर्ण

/* ग_लिखो val to cir config रेजिस्टर */
अटल अंतरभूत व्योम nvt_cir_reg_ग_लिखो(काष्ठा nvt_dev *nvt, u8 val, u8 offset)
अणु
	outb(val, nvt->cir_addr + offset);
पूर्ण

/* पढ़ो val from cir config रेजिस्टर */
अटल u8 nvt_cir_reg_पढ़ो(काष्ठा nvt_dev *nvt, u8 offset)
अणु
	वापस inb(nvt->cir_addr + offset);
पूर्ण

/* ग_लिखो val to cir wake रेजिस्टर */
अटल अंतरभूत व्योम nvt_cir_wake_reg_ग_लिखो(काष्ठा nvt_dev *nvt,
					  u8 val, u8 offset)
अणु
	outb(val, nvt->cir_wake_addr + offset);
पूर्ण

/* पढ़ो val from cir wake config रेजिस्टर */
अटल u8 nvt_cir_wake_reg_पढ़ो(काष्ठा nvt_dev *nvt, u8 offset)
अणु
	वापस inb(nvt->cir_wake_addr + offset);
पूर्ण

/* करोn't override io address अगर one is set alपढ़ोy */
अटल व्योम nvt_set_ioaddr(काष्ठा nvt_dev *nvt, अचिन्हित दीर्घ *ioaddr)
अणु
	अचिन्हित दीर्घ old_addr;

	old_addr = nvt_cr_पढ़ो(nvt, CR_CIR_BASE_ADDR_HI) << 8;
	old_addr |= nvt_cr_पढ़ो(nvt, CR_CIR_BASE_ADDR_LO);

	अगर (old_addr)
		*ioaddr = old_addr;
	अन्यथा अणु
		nvt_cr_ग_लिखो(nvt, *ioaddr >> 8, CR_CIR_BASE_ADDR_HI);
		nvt_cr_ग_लिखो(nvt, *ioaddr & 0xff, CR_CIR_BASE_ADDR_LO);
	पूर्ण
पूर्ण

अटल व्योम nvt_ग_लिखो_wakeup_codes(काष्ठा rc_dev *dev,
				   स्थिर u8 *wbuf, पूर्णांक count)
अणु
	u8 tolerance, config;
	काष्ठा nvt_dev *nvt = dev->priv;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;

	/* hardcode the tolerance to 10% */
	tolerance = DIV_ROUND_UP(count, 10);

	spin_lock_irqsave(&nvt->lock, flags);

	nvt_clear_cir_wake_fअगरo(nvt);
	nvt_cir_wake_reg_ग_लिखो(nvt, count, CIR_WAKE_FIFO_CMP_DEEP);
	nvt_cir_wake_reg_ग_लिखो(nvt, tolerance, CIR_WAKE_FIFO_CMP_TOL);

	config = nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_IRCON);

	/* enable ग_लिखोs to wake fअगरo */
	nvt_cir_wake_reg_ग_लिखो(nvt, config | CIR_WAKE_IRCON_MODE1,
			       CIR_WAKE_IRCON);

	अगर (count)
		pr_info("Wake samples (%d) =", count);
	अन्यथा
		pr_info("Wake sample fifo cleared");

	क्रम (i = 0; i < count; i++)
		nvt_cir_wake_reg_ग_लिखो(nvt, wbuf[i], CIR_WAKE_WR_FIFO_DATA);

	nvt_cir_wake_reg_ग_लिखो(nvt, config, CIR_WAKE_IRCON);

	spin_unlock_irqrestore(&nvt->lock, flags);
पूर्ण

अटल sमाप_प्रकार wakeup_data_show(काष्ठा device *dev,
				काष्ठा device_attribute *attr,
				अक्षर *buf)
अणु
	काष्ठा rc_dev *rc_dev = to_rc_dev(dev);
	काष्ठा nvt_dev *nvt = rc_dev->priv;
	पूर्णांक fअगरo_len, duration;
	अचिन्हित दीर्घ flags;
	sमाप_प्रकार buf_len = 0;
	पूर्णांक i;

	spin_lock_irqsave(&nvt->lock, flags);

	fअगरo_len = nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_FIFO_COUNT);
	fअगरo_len = min(fअगरo_len, WAKEUP_MAX_SIZE);

	/* go to first element to be पढ़ो */
	जबतक (nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_RD_FIFO_ONLY_IDX))
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_RD_FIFO_ONLY);

	क्रम (i = 0; i < fअगरo_len; i++) अणु
		duration = nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_RD_FIFO_ONLY);
		duration = (duration & BUF_LEN_MASK) * SAMPLE_PERIOD;
		buf_len += scnम_लिखो(buf + buf_len, PAGE_SIZE - buf_len,
				    "%d ", duration);
	पूर्ण
	buf_len += scnम_लिखो(buf + buf_len, PAGE_SIZE - buf_len, "\n");

	spin_unlock_irqrestore(&nvt->lock, flags);

	वापस buf_len;
पूर्ण

अटल sमाप_प्रकार wakeup_data_store(काष्ठा device *dev,
				 काष्ठा device_attribute *attr,
				 स्थिर अक्षर *buf, माप_प्रकार len)
अणु
	काष्ठा rc_dev *rc_dev = to_rc_dev(dev);
	u8 wake_buf[WAKEUP_MAX_SIZE];
	अक्षर **argv;
	पूर्णांक i, count;
	अचिन्हित पूर्णांक val;
	sमाप_प्रकार ret;

	argv = argv_split(GFP_KERNEL, buf, &count);
	अगर (!argv)
		वापस -ENOMEM;
	अगर (!count || count > WAKEUP_MAX_SIZE) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	क्रम (i = 0; i < count; i++) अणु
		ret = kstrtouपूर्णांक(argv[i], 10, &val);
		अगर (ret)
			जाओ out;
		val = DIV_ROUND_CLOSEST(val, SAMPLE_PERIOD);
		अगर (!val || val > 0x7f) अणु
			ret = -EINVAL;
			जाओ out;
		पूर्ण
		wake_buf[i] = val;
		/* sequence must start with a pulse */
		अगर (i % 2 == 0)
			wake_buf[i] |= BUF_PULSE_BIT;
	पूर्ण

	nvt_ग_लिखो_wakeup_codes(rc_dev, wake_buf, count);

	ret = len;
out:
	argv_मुक्त(argv);
	वापस ret;
पूर्ण
अटल DEVICE_ATTR_RW(wakeup_data);

/* dump current cir रेजिस्टर contents */
अटल व्योम cir_dump_regs(काष्ठा nvt_dev *nvt)
अणु
	nvt_efm_enable(nvt);
	nvt_select_logical_dev(nvt, LOGICAL_DEV_CIR);

	pr_info("%s: Dump CIR logical device registers:\n", NVT_DRIVER_NAME);
	pr_info(" * CR CIR ACTIVE :   0x%x\n",
		nvt_cr_पढ़ो(nvt, CR_LOGICAL_DEV_EN));
	pr_info(" * CR CIR BASE ADDR: 0x%x\n",
		(nvt_cr_पढ़ो(nvt, CR_CIR_BASE_ADDR_HI) << 8) |
		nvt_cr_पढ़ो(nvt, CR_CIR_BASE_ADDR_LO));
	pr_info(" * CR CIR IRQ NUM:   0x%x\n",
		nvt_cr_पढ़ो(nvt, CR_CIR_IRQ_RSRC));

	nvt_efm_disable(nvt);

	pr_info("%s: Dump CIR registers:\n", NVT_DRIVER_NAME);
	pr_info(" * IRCON:     0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_IRCON));
	pr_info(" * IRSTS:     0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_IRSTS));
	pr_info(" * IREN:      0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_IREN));
	pr_info(" * RXFCONT:   0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_RXFCONT));
	pr_info(" * CP:        0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_CP));
	pr_info(" * CC:        0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_CC));
	pr_info(" * SLCH:      0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_SLCH));
	pr_info(" * SLCL:      0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_SLCL));
	pr_info(" * FIFOCON:   0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_FIFOCON));
	pr_info(" * IRFIFOSTS: 0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_IRFIFOSTS));
	pr_info(" * SRXFIFO:   0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_SRXFIFO));
	pr_info(" * TXFCONT:   0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_TXFCONT));
	pr_info(" * STXFIFO:   0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_STXFIFO));
	pr_info(" * FCCH:      0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_FCCH));
	pr_info(" * FCCL:      0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_FCCL));
	pr_info(" * IRFSM:     0x%x\n", nvt_cir_reg_पढ़ो(nvt, CIR_IRFSM));
पूर्ण

/* dump current cir wake रेजिस्टर contents */
अटल व्योम cir_wake_dump_regs(काष्ठा nvt_dev *nvt)
अणु
	u8 i, fअगरo_len;

	nvt_efm_enable(nvt);
	nvt_select_logical_dev(nvt, LOGICAL_DEV_CIR_WAKE);

	pr_info("%s: Dump CIR WAKE logical device registers:\n",
		NVT_DRIVER_NAME);
	pr_info(" * CR CIR WAKE ACTIVE :   0x%x\n",
		nvt_cr_पढ़ो(nvt, CR_LOGICAL_DEV_EN));
	pr_info(" * CR CIR WAKE BASE ADDR: 0x%x\n",
		(nvt_cr_पढ़ो(nvt, CR_CIR_BASE_ADDR_HI) << 8) |
		nvt_cr_पढ़ो(nvt, CR_CIR_BASE_ADDR_LO));
	pr_info(" * CR CIR WAKE IRQ NUM:   0x%x\n",
		nvt_cr_पढ़ो(nvt, CR_CIR_IRQ_RSRC));

	nvt_efm_disable(nvt);

	pr_info("%s: Dump CIR WAKE registers\n", NVT_DRIVER_NAME);
	pr_info(" * IRCON:          0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_IRCON));
	pr_info(" * IRSTS:          0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_IRSTS));
	pr_info(" * IREN:           0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_IREN));
	pr_info(" * FIFO CMP DEEP:  0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_FIFO_CMP_DEEP));
	pr_info(" * FIFO CMP TOL:   0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_FIFO_CMP_TOL));
	pr_info(" * FIFO COUNT:     0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_FIFO_COUNT));
	pr_info(" * SLCH:           0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_SLCH));
	pr_info(" * SLCL:           0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_SLCL));
	pr_info(" * FIFOCON:        0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_FIFOCON));
	pr_info(" * SRXFSTS:        0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_SRXFSTS));
	pr_info(" * SAMPLE RX FIFO: 0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_SAMPLE_RX_FIFO));
	pr_info(" * WR FIFO DATA:   0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_WR_FIFO_DATA));
	pr_info(" * RD FIFO ONLY:   0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_RD_FIFO_ONLY));
	pr_info(" * RD FIFO ONLY IDX: 0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_RD_FIFO_ONLY_IDX));
	pr_info(" * FIFO IGNORE:    0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_FIFO_IGNORE));
	pr_info(" * IRFSM:          0x%x\n",
		nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_IRFSM));

	fअगरo_len = nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_FIFO_COUNT);
	pr_info("%s: Dump CIR WAKE FIFO (len %d)\n", NVT_DRIVER_NAME, fअगरo_len);
	pr_info("* Contents =");
	क्रम (i = 0; i < fअगरo_len; i++)
		pr_cont(" %02x",
			nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_RD_FIFO_ONLY));
	pr_cont("\n");
पूर्ण

अटल अंतरभूत स्थिर अक्षर *nvt_find_chip(काष्ठा nvt_dev *nvt, पूर्णांक id)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(nvt_chips); i++)
		अगर ((id & SIO_ID_MASK) == nvt_chips[i].chip_ver) अणु
			nvt->chip_ver = nvt_chips[i].chip_ver;
			वापस nvt_chips[i].name;
		पूर्ण

	वापस शून्य;
पूर्ण


/* detect hardware features */
अटल पूर्णांक nvt_hw_detect(काष्ठा nvt_dev *nvt)
अणु
	काष्ठा device *dev = nvt_get_dev(nvt);
	स्थिर अक्षर *chip_name;
	पूर्णांक chip_id;

	nvt_efm_enable(nvt);

	/* Check अगर we're wired क्रम the alternate EFER setup */
	nvt->chip_major = nvt_cr_पढ़ो(nvt, CR_CHIP_ID_HI);
	अगर (nvt->chip_major == 0xff) अणु
		nvt_efm_disable(nvt);
		nvt->cr_efir = CR_EFIR2;
		nvt->cr_efdr = CR_EFDR2;
		nvt_efm_enable(nvt);
		nvt->chip_major = nvt_cr_पढ़ो(nvt, CR_CHIP_ID_HI);
	पूर्ण
	nvt->chip_minor = nvt_cr_पढ़ो(nvt, CR_CHIP_ID_LO);

	nvt_efm_disable(nvt);

	chip_id = nvt->chip_major << 8 | nvt->chip_minor;
	अगर (chip_id == NVT_INVALID) अणु
		dev_err(dev, "No device found on either EFM port\n");
		वापस -ENODEV;
	पूर्ण

	chip_name = nvt_find_chip(nvt, chip_id);

	/* warn, but still let the driver load, अगर we करोn't know this chip */
	अगर (!chip_name)
		dev_warn(dev,
			 "unknown chip, id: 0x%02x 0x%02x, it may not work...",
			 nvt->chip_major, nvt->chip_minor);
	अन्यथा
		dev_info(dev, "found %s or compatible: chip id: 0x%02x 0x%02x",
			 chip_name, nvt->chip_major, nvt->chip_minor);

	वापस 0;
पूर्ण

अटल व्योम nvt_cir_ldev_init(काष्ठा nvt_dev *nvt)
अणु
	u8 val, psreg, psmask, psval;

	अगर (is_w83667hg(nvt)) अणु
		psreg = CR_MULTIFUNC_PIN_SEL;
		psmask = MULTIFUNC_PIN_SEL_MASK;
		psval = MULTIFUNC_ENABLE_CIR | MULTIFUNC_ENABLE_CIRWB;
	पूर्ण अन्यथा अणु
		psreg = CR_OUTPUT_PIN_SEL;
		psmask = OUTPUT_PIN_SEL_MASK;
		psval = OUTPUT_ENABLE_CIR | OUTPUT_ENABLE_CIRWB;
	पूर्ण

	/* output pin selection: enable CIR, with WB sensor enabled */
	val = nvt_cr_पढ़ो(nvt, psreg);
	val &= psmask;
	val |= psval;
	nvt_cr_ग_लिखो(nvt, val, psreg);

	/* Select CIR logical device */
	nvt_select_logical_dev(nvt, LOGICAL_DEV_CIR);

	nvt_set_ioaddr(nvt, &nvt->cir_addr);

	nvt_cr_ग_लिखो(nvt, nvt->cir_irq, CR_CIR_IRQ_RSRC);

	nvt_dbg("CIR initialized, base io port address: 0x%lx, irq: %d",
		nvt->cir_addr, nvt->cir_irq);
पूर्ण

अटल व्योम nvt_cir_wake_ldev_init(काष्ठा nvt_dev *nvt)
अणु
	/* Select ACPI logical device and anable it */
	nvt_select_logical_dev(nvt, LOGICAL_DEV_ACPI);
	nvt_cr_ग_लिखो(nvt, LOGICAL_DEV_ENABLE, CR_LOGICAL_DEV_EN);

	/* Enable CIR Wake via PSOUT# (Pin60) */
	nvt_set_reg_bit(nvt, CIR_WAKE_ENABLE_BIT, CR_ACPI_CIR_WAKE);

	/* enable pme पूर्णांकerrupt of cir wakeup event */
	nvt_set_reg_bit(nvt, PME_INTR_CIR_PASS_BIT, CR_ACPI_IRQ_EVENTS2);

	/* Select CIR Wake logical device */
	nvt_select_logical_dev(nvt, LOGICAL_DEV_CIR_WAKE);

	nvt_set_ioaddr(nvt, &nvt->cir_wake_addr);

	nvt_dbg("CIR Wake initialized, base io port address: 0x%lx",
		nvt->cir_wake_addr);
पूर्ण

/* clear out the hardware's cir rx fअगरo */
अटल व्योम nvt_clear_cir_fअगरo(काष्ठा nvt_dev *nvt)
अणु
	u8 val = nvt_cir_reg_पढ़ो(nvt, CIR_FIFOCON);
	nvt_cir_reg_ग_लिखो(nvt, val | CIR_FIFOCON_RXFIFOCLR, CIR_FIFOCON);
पूर्ण

/* clear out the hardware's cir wake rx fअगरo */
अटल व्योम nvt_clear_cir_wake_fअगरo(काष्ठा nvt_dev *nvt)
अणु
	u8 val, config;

	config = nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_IRCON);

	/* clearing wake fअगरo works in learning mode only */
	nvt_cir_wake_reg_ग_लिखो(nvt, config & ~CIR_WAKE_IRCON_MODE0,
			       CIR_WAKE_IRCON);

	val = nvt_cir_wake_reg_पढ़ो(nvt, CIR_WAKE_FIFOCON);
	nvt_cir_wake_reg_ग_लिखो(nvt, val | CIR_WAKE_FIFOCON_RXFIFOCLR,
			       CIR_WAKE_FIFOCON);

	nvt_cir_wake_reg_ग_लिखो(nvt, config, CIR_WAKE_IRCON);
पूर्ण

/* clear out the hardware's cir tx fअगरo */
अटल व्योम nvt_clear_tx_fअगरo(काष्ठा nvt_dev *nvt)
अणु
	u8 val;

	val = nvt_cir_reg_पढ़ो(nvt, CIR_FIFOCON);
	nvt_cir_reg_ग_लिखो(nvt, val | CIR_FIFOCON_TXFIFOCLR, CIR_FIFOCON);
पूर्ण

/* enable RX Trigger Level Reach and Packet End पूर्णांकerrupts */
अटल व्योम nvt_set_cir_iren(काष्ठा nvt_dev *nvt)
अणु
	u8 iren;

	iren = CIR_IREN_RTR | CIR_IREN_PE | CIR_IREN_RFO;
	nvt_cir_reg_ग_लिखो(nvt, iren, CIR_IREN);
पूर्ण

अटल व्योम nvt_cir_regs_init(काष्ठा nvt_dev *nvt)
अणु
	nvt_enable_logical_dev(nvt, LOGICAL_DEV_CIR);

	/* set sample limit count (PE पूर्णांकerrupt उठाओd when reached) */
	nvt_cir_reg_ग_लिखो(nvt, CIR_RX_LIMIT_COUNT >> 8, CIR_SLCH);
	nvt_cir_reg_ग_लिखो(nvt, CIR_RX_LIMIT_COUNT & 0xff, CIR_SLCL);

	/* set fअगरo irq trigger levels */
	nvt_cir_reg_ग_लिखो(nvt, CIR_FIFOCON_TX_TRIGGER_LEV |
			  CIR_FIFOCON_RX_TRIGGER_LEV, CIR_FIFOCON);

	/* clear hardware rx and tx fअगरos */
	nvt_clear_cir_fअगरo(nvt);
	nvt_clear_tx_fअगरo(nvt);

	nvt_disable_logical_dev(nvt, LOGICAL_DEV_CIR);
पूर्ण

अटल व्योम nvt_cir_wake_regs_init(काष्ठा nvt_dev *nvt)
अणु
	nvt_enable_logical_dev(nvt, LOGICAL_DEV_CIR_WAKE);

	/*
	 * Disable RX, set specअगरic carrier on = low, off = high,
	 * and sample period (currently 50us)
	 */
	nvt_cir_wake_reg_ग_लिखो(nvt, CIR_WAKE_IRCON_MODE0 |
			       CIR_WAKE_IRCON_R | CIR_WAKE_IRCON_RXINV |
			       CIR_WAKE_IRCON_SAMPLE_PERIOD_SEL,
			       CIR_WAKE_IRCON);

	/* clear any and all stray पूर्णांकerrupts */
	nvt_cir_wake_reg_ग_लिखो(nvt, 0xff, CIR_WAKE_IRSTS);
पूर्ण

अटल व्योम nvt_enable_wake(काष्ठा nvt_dev *nvt)
अणु
	अचिन्हित दीर्घ flags;

	nvt_efm_enable(nvt);

	nvt_select_logical_dev(nvt, LOGICAL_DEV_ACPI);
	nvt_set_reg_bit(nvt, CIR_WAKE_ENABLE_BIT, CR_ACPI_CIR_WAKE);
	nvt_set_reg_bit(nvt, PME_INTR_CIR_PASS_BIT, CR_ACPI_IRQ_EVENTS2);

	nvt_select_logical_dev(nvt, LOGICAL_DEV_CIR_WAKE);
	nvt_cr_ग_लिखो(nvt, LOGICAL_DEV_ENABLE, CR_LOGICAL_DEV_EN);

	nvt_efm_disable(nvt);

	spin_lock_irqsave(&nvt->lock, flags);

	nvt_cir_wake_reg_ग_लिखो(nvt, CIR_WAKE_IRCON_MODE0 | CIR_WAKE_IRCON_RXEN |
			       CIR_WAKE_IRCON_R | CIR_WAKE_IRCON_RXINV |
			       CIR_WAKE_IRCON_SAMPLE_PERIOD_SEL,
			       CIR_WAKE_IRCON);
	nvt_cir_wake_reg_ग_लिखो(nvt, 0xff, CIR_WAKE_IRSTS);
	nvt_cir_wake_reg_ग_लिखो(nvt, 0, CIR_WAKE_IREN);

	spin_unlock_irqrestore(&nvt->lock, flags);
पूर्ण

#अगर 0 /* Currently unused */
/* rx carrier detect only works in learning mode, must be called w/lock */
अटल u32 nvt_rx_carrier_detect(काष्ठा nvt_dev *nvt)
अणु
	u32 count, carrier, duration = 0;
	पूर्णांक i;

	count = nvt_cir_reg_पढ़ो(nvt, CIR_FCCL) |
		nvt_cir_reg_पढ़ो(nvt, CIR_FCCH) << 8;

	क्रम (i = 0; i < nvt->pkts; i++) अणु
		अगर (nvt->buf[i] & BUF_PULSE_BIT)
			duration += nvt->buf[i] & BUF_LEN_MASK;
	पूर्ण

	duration *= SAMPLE_PERIOD;

	अगर (!count || !duration) अणु
		dev_notice(nvt_get_dev(nvt),
			   "Unable to determine carrier! (c:%u, d:%u)",
			   count, duration);
		वापस 0;
	पूर्ण

	carrier = MS_TO_NS(count) / duration;

	अगर ((carrier > MAX_CARRIER) || (carrier < MIN_CARRIER))
		nvt_dbg("WTF? Carrier frequency out of range!");

	nvt_dbg("Carrier frequency: %u (count %u, duration %u)",
		carrier, count, duration);

	वापस carrier;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक nvt_ir_raw_set_wakeup_filter(काष्ठा rc_dev *dev,
					काष्ठा rc_scancode_filter *sc_filter)
अणु
	u8 buf_val;
	पूर्णांक i, ret, count;
	अचिन्हित पूर्णांक val;
	काष्ठा ir_raw_event *raw;
	u8 wake_buf[WAKEUP_MAX_SIZE];
	bool complete;

	/* Require mask to be set */
	अगर (!sc_filter->mask)
		वापस 0;

	raw = kदो_स्मृति_array(WAKEUP_MAX_SIZE, माप(*raw), GFP_KERNEL);
	अगर (!raw)
		वापस -ENOMEM;

	ret = ir_raw_encode_scancode(dev->wakeup_protocol, sc_filter->data,
				     raw, WAKEUP_MAX_SIZE);
	complete = (ret != -ENOBUFS);
	अगर (!complete)
		ret = WAKEUP_MAX_SIZE;
	अन्यथा अगर (ret < 0)
		जाओ out_raw;

	/* Inspect the ir samples */
	क्रम (i = 0, count = 0; i < ret && count < WAKEUP_MAX_SIZE; ++i) अणु
		val = raw[i].duration / SAMPLE_PERIOD;

		/* Split too large values पूर्णांकo several smaller ones */
		जबतक (val > 0 && count < WAKEUP_MAX_SIZE) अणु
			/* Skip last value क्रम better comparison tolerance */
			अगर (complete && i == ret - 1 && val < BUF_LEN_MASK)
				अवरोध;

			/* Clamp values to BUF_LEN_MASK at most */
			buf_val = (val > BUF_LEN_MASK) ? BUF_LEN_MASK : val;

			wake_buf[count] = buf_val;
			val -= buf_val;
			अगर ((raw[i]).pulse)
				wake_buf[count] |= BUF_PULSE_BIT;
			count++;
		पूर्ण
	पूर्ण

	nvt_ग_लिखो_wakeup_codes(dev, wake_buf, count);
	ret = 0;
out_raw:
	kमुक्त(raw);

	वापस ret;
पूर्ण

/* dump contents of the last rx buffer we got from the hw rx fअगरo */
अटल व्योम nvt_dump_rx_buf(काष्ठा nvt_dev *nvt)
अणु
	पूर्णांक i;

	prपूर्णांकk(KERN_DEBUG "%s (len %d): ", __func__, nvt->pkts);
	क्रम (i = 0; (i < nvt->pkts) && (i < RX_BUF_LEN); i++)
		prपूर्णांकk(KERN_CONT "0x%02x ", nvt->buf[i]);
	prपूर्णांकk(KERN_CONT "\n");
पूर्ण

/*
 * Process raw data in rx driver buffer, store it in raw IR event kfअगरo,
 * trigger decode when appropriate.
 *
 * We get IR data samples one byte at a समय. If the msb is set, its a pulse,
 * otherwise its a space. The lower 7 bits are the count of SAMPLE_PERIOD
 * (शेष 50us) पूर्णांकervals क्रम that pulse/space. A discrete संकेत is
 * followed by a series of 0x7f packets, then either 0x7<something> or 0x80
 * to संकेत more IR coming (repeats) or end of IR, respectively. We store
 * sample data in the raw event kfअगरo until we see 0x7<something> (except f)
 * or 0x80, at which समय, we trigger a decode operation.
 */
अटल व्योम nvt_process_rx_ir_data(काष्ठा nvt_dev *nvt)
अणु
	काष्ठा ir_raw_event rawir = अणुपूर्ण;
	u8 sample;
	पूर्णांक i;

	nvt_dbg_verbose("%s firing", __func__);

	अगर (debug)
		nvt_dump_rx_buf(nvt);

	nvt_dbg_verbose("Processing buffer of len %d", nvt->pkts);

	क्रम (i = 0; i < nvt->pkts; i++) अणु
		sample = nvt->buf[i];

		rawir.pulse = ((sample & BUF_PULSE_BIT) != 0);
		rawir.duration = (sample & BUF_LEN_MASK) * SAMPLE_PERIOD;

		nvt_dbg("Storing %s with duration %d",
			rawir.pulse ? "pulse" : "space", rawir.duration);

		ir_raw_event_store_with_filter(nvt->rdev, &rawir);
	पूर्ण

	nvt->pkts = 0;

	nvt_dbg("Calling ir_raw_event_handle\n");
	ir_raw_event_handle(nvt->rdev);

	nvt_dbg_verbose("%s done", __func__);
पूर्ण

अटल व्योम nvt_handle_rx_fअगरo_overrun(काष्ठा nvt_dev *nvt)
अणु
	dev_warn(nvt_get_dev(nvt), "RX FIFO overrun detected, flushing data!");

	nvt->pkts = 0;
	nvt_clear_cir_fअगरo(nvt);
	ir_raw_event_reset(nvt->rdev);
पूर्ण

/* copy data from hardware rx fअगरo पूर्णांकo driver buffer */
अटल व्योम nvt_get_rx_ir_data(काष्ठा nvt_dev *nvt)
अणु
	u8 fअगरocount;
	पूर्णांक i;

	/* Get count of how many bytes to पढ़ो from RX FIFO */
	fअगरocount = nvt_cir_reg_पढ़ो(nvt, CIR_RXFCONT);

	nvt_dbg("attempting to fetch %u bytes from hw rx fifo", fअगरocount);

	/* Read fअगरocount bytes from CIR Sample RX FIFO रेजिस्टर */
	क्रम (i = 0; i < fअगरocount; i++)
		nvt->buf[i] = nvt_cir_reg_पढ़ो(nvt, CIR_SRXFIFO);

	nvt->pkts = fअगरocount;
	nvt_dbg("%s: pkts now %d", __func__, nvt->pkts);

	nvt_process_rx_ir_data(nvt);
पूर्ण

अटल व्योम nvt_cir_log_irqs(u8 status, u8 iren)
अणु
	nvt_dbg("IRQ 0x%02x (IREN 0x%02x) :%s%s%s%s%s%s%s%s%s",
		status, iren,
		status & CIR_IRSTS_RDR	? " RDR"	: "",
		status & CIR_IRSTS_RTR	? " RTR"	: "",
		status & CIR_IRSTS_PE	? " PE"		: "",
		status & CIR_IRSTS_RFO	? " RFO"	: "",
		status & CIR_IRSTS_TE	? " TE"		: "",
		status & CIR_IRSTS_TTR	? " TTR"	: "",
		status & CIR_IRSTS_TFU	? " TFU"	: "",
		status & CIR_IRSTS_GH	? " GH"		: "",
		status & ~(CIR_IRSTS_RDR | CIR_IRSTS_RTR | CIR_IRSTS_PE |
			   CIR_IRSTS_RFO | CIR_IRSTS_TE | CIR_IRSTS_TTR |
			   CIR_IRSTS_TFU | CIR_IRSTS_GH) ? " ?" : "");
पूर्ण

/* पूर्णांकerrupt service routine क्रम incoming and outgoing CIR data */
अटल irqवापस_t nvt_cir_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा nvt_dev *nvt = data;
	u8 status, iren;

	nvt_dbg_verbose("%s firing", __func__);

	spin_lock(&nvt->lock);

	/*
	 * Get IR Status रेजिस्टर contents. Write 1 to ack/clear
	 *
	 * bit: reg name      - description
	 *   7: CIR_IRSTS_RDR - RX Data Ready
	 *   6: CIR_IRSTS_RTR - RX FIFO Trigger Level Reach
	 *   5: CIR_IRSTS_PE  - Packet End
	 *   4: CIR_IRSTS_RFO - RX FIFO Overrun (RDR will also be set)
	 *   3: CIR_IRSTS_TE  - TX FIFO Empty
	 *   2: CIR_IRSTS_TTR - TX FIFO Trigger Level Reach
	 *   1: CIR_IRSTS_TFU - TX FIFO Underrun
	 *   0: CIR_IRSTS_GH  - Min Length Detected
	 */
	status = nvt_cir_reg_पढ़ो(nvt, CIR_IRSTS);
	iren = nvt_cir_reg_पढ़ो(nvt, CIR_IREN);

	/* At least NCT6779D creates a spurious पूर्णांकerrupt when the
	 * logical device is being disabled.
	 */
	अगर (status == 0xff && iren == 0xff) अणु
		spin_unlock(&nvt->lock);
		nvt_dbg_verbose("Spurious interrupt detected");
		वापस IRQ_HANDLED;
	पूर्ण

	/* IRQ may be shared with CIR WAKE, thereक्रमe check क्रम each
	 * status bit whether the related पूर्णांकerrupt source is enabled
	 */
	अगर (!(status & iren)) अणु
		spin_unlock(&nvt->lock);
		nvt_dbg_verbose("%s exiting, IRSTS 0x0", __func__);
		वापस IRQ_NONE;
	पूर्ण

	/* ack/clear all irq flags we've got */
	nvt_cir_reg_ग_लिखो(nvt, status, CIR_IRSTS);
	nvt_cir_reg_ग_लिखो(nvt, 0, CIR_IRSTS);

	nvt_cir_log_irqs(status, iren);

	अगर (status & CIR_IRSTS_RFO)
		nvt_handle_rx_fअगरo_overrun(nvt);
	अन्यथा अगर (status & (CIR_IRSTS_RTR | CIR_IRSTS_PE))
		nvt_get_rx_ir_data(nvt);

	spin_unlock(&nvt->lock);

	nvt_dbg_verbose("%s done", __func__);
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम nvt_enable_cir(काष्ठा nvt_dev *nvt)
अणु
	अचिन्हित दीर्घ flags;

	/* enable the CIR logical device */
	nvt_enable_logical_dev(nvt, LOGICAL_DEV_CIR);

	spin_lock_irqsave(&nvt->lock, flags);

	/*
	 * Enable TX and RX, specअगरy carrier on = low, off = high, and set
	 * sample period (currently 50us)
	 */
	nvt_cir_reg_ग_लिखो(nvt, CIR_IRCON_TXEN | CIR_IRCON_RXEN |
			  CIR_IRCON_RXINV | CIR_IRCON_SAMPLE_PERIOD_SEL,
			  CIR_IRCON);

	/* clear all pending पूर्णांकerrupts */
	nvt_cir_reg_ग_लिखो(nvt, 0xff, CIR_IRSTS);

	/* enable पूर्णांकerrupts */
	nvt_set_cir_iren(nvt);

	spin_unlock_irqrestore(&nvt->lock, flags);
पूर्ण

अटल व्योम nvt_disable_cir(काष्ठा nvt_dev *nvt)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&nvt->lock, flags);

	/* disable CIR पूर्णांकerrupts */
	nvt_cir_reg_ग_लिखो(nvt, 0, CIR_IREN);

	/* clear any and all pending पूर्णांकerrupts */
	nvt_cir_reg_ग_लिखो(nvt, 0xff, CIR_IRSTS);

	/* clear all function enable flags */
	nvt_cir_reg_ग_लिखो(nvt, 0, CIR_IRCON);

	/* clear hardware rx and tx fअगरos */
	nvt_clear_cir_fअगरo(nvt);
	nvt_clear_tx_fअगरo(nvt);

	spin_unlock_irqrestore(&nvt->lock, flags);

	/* disable the CIR logical device */
	nvt_disable_logical_dev(nvt, LOGICAL_DEV_CIR);
पूर्ण

अटल पूर्णांक nvt_खोलो(काष्ठा rc_dev *dev)
अणु
	काष्ठा nvt_dev *nvt = dev->priv;

	nvt_enable_cir(nvt);

	वापस 0;
पूर्ण

अटल व्योम nvt_बंद(काष्ठा rc_dev *dev)
अणु
	काष्ठा nvt_dev *nvt = dev->priv;

	nvt_disable_cir(nvt);
पूर्ण

/* Allocate memory, probe hardware, and initialize everything */
अटल पूर्णांक nvt_probe(काष्ठा pnp_dev *pdev, स्थिर काष्ठा pnp_device_id *dev_id)
अणु
	काष्ठा nvt_dev *nvt;
	काष्ठा rc_dev *rdev;
	पूर्णांक ret;

	nvt = devm_kzalloc(&pdev->dev, माप(काष्ठा nvt_dev), GFP_KERNEL);
	अगर (!nvt)
		वापस -ENOMEM;

	/* input device क्रम IR remote */
	nvt->rdev = devm_rc_allocate_device(&pdev->dev, RC_DRIVER_IR_RAW);
	अगर (!nvt->rdev)
		वापस -ENOMEM;
	rdev = nvt->rdev;

	/* activate pnp device */
	ret = pnp_activate_dev(pdev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "Could not activate PNP device!\n");
		वापस ret;
	पूर्ण

	/* validate pnp resources */
	अगर (!pnp_port_valid(pdev, 0) ||
	    pnp_port_len(pdev, 0) < CIR_IOREG_LENGTH) अणु
		dev_err(&pdev->dev, "IR PNP Port not valid!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!pnp_irq_valid(pdev, 0)) अणु
		dev_err(&pdev->dev, "PNP IRQ not valid!\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!pnp_port_valid(pdev, 1) ||
	    pnp_port_len(pdev, 1) < CIR_IOREG_LENGTH) अणु
		dev_err(&pdev->dev, "Wake PNP Port not valid!\n");
		वापस -EINVAL;
	पूर्ण

	nvt->cir_addr = pnp_port_start(pdev, 0);
	nvt->cir_irq  = pnp_irq(pdev, 0);

	nvt->cir_wake_addr = pnp_port_start(pdev, 1);

	nvt->cr_efir = CR_EFIR;
	nvt->cr_efdr = CR_EFDR;

	spin_lock_init(&nvt->lock);

	pnp_set_drvdata(pdev, nvt);

	ret = nvt_hw_detect(nvt);
	अगर (ret)
		वापस ret;

	/* Initialize CIR & CIR Wake Logical Devices */
	nvt_efm_enable(nvt);
	nvt_cir_ldev_init(nvt);
	nvt_cir_wake_ldev_init(nvt);
	nvt_efm_disable(nvt);

	/*
	 * Initialize CIR & CIR Wake Config Registers
	 * and enable logical devices
	 */
	nvt_cir_regs_init(nvt);
	nvt_cir_wake_regs_init(nvt);

	/* Set up the rc device */
	rdev->priv = nvt;
	rdev->allowed_protocols = RC_PROTO_BIT_ALL_IR_DECODER;
	rdev->allowed_wakeup_protocols = RC_PROTO_BIT_ALL_IR_ENCODER;
	rdev->encode_wakeup = true;
	rdev->खोलो = nvt_खोलो;
	rdev->बंद = nvt_बंद;
	rdev->s_wakeup_filter = nvt_ir_raw_set_wakeup_filter;
	rdev->device_name = "Nuvoton w836x7hg Infrared Remote Transceiver";
	rdev->input_phys = "nuvoton/cir0";
	rdev->input_id.bustype = BUS_HOST;
	rdev->input_id.venकरोr = PCI_VENDOR_ID_WINBOND2;
	rdev->input_id.product = nvt->chip_major;
	rdev->input_id.version = nvt->chip_minor;
	rdev->driver_name = NVT_DRIVER_NAME;
	rdev->map_name = RC_MAP_RC6_MCE;
	rdev->समयout = MS_TO_US(100);
	/* rx resolution is hardwired to 50us aपंचांग, 1, 25, 100 also possible */
	rdev->rx_resolution = CIR_SAMPLE_PERIOD;
#अगर 0
	rdev->min_समयout = XYZ;
	rdev->max_समयout = XYZ;
#पूर्ण_अगर
	ret = devm_rc_रेजिस्टर_device(&pdev->dev, rdev);
	अगर (ret)
		वापस ret;

	/* now claim resources */
	अगर (!devm_request_region(&pdev->dev, nvt->cir_addr,
			    CIR_IOREG_LENGTH, NVT_DRIVER_NAME))
		वापस -EBUSY;

	ret = devm_request_irq(&pdev->dev, nvt->cir_irq, nvt_cir_isr,
			       IRQF_SHARED, NVT_DRIVER_NAME, nvt);
	अगर (ret)
		वापस ret;

	अगर (!devm_request_region(&pdev->dev, nvt->cir_wake_addr,
			    CIR_IOREG_LENGTH, NVT_DRIVER_NAME "-wake"))
		वापस -EBUSY;

	ret = device_create_file(&rdev->dev, &dev_attr_wakeup_data);
	अगर (ret)
		वापस ret;

	device_init_wakeup(&pdev->dev, true);

	dev_notice(&pdev->dev, "driver has been successfully loaded\n");
	अगर (debug) अणु
		cir_dump_regs(nvt);
		cir_wake_dump_regs(nvt);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम nvt_हटाओ(काष्ठा pnp_dev *pdev)
अणु
	काष्ठा nvt_dev *nvt = pnp_get_drvdata(pdev);

	device_हटाओ_file(&nvt->rdev->dev, &dev_attr_wakeup_data);

	nvt_disable_cir(nvt);

	/* enable CIR Wake (क्रम IR घातer-on) */
	nvt_enable_wake(nvt);
पूर्ण

अटल पूर्णांक nvt_suspend(काष्ठा pnp_dev *pdev, pm_message_t state)
अणु
	काष्ठा nvt_dev *nvt = pnp_get_drvdata(pdev);

	nvt_dbg("%s called", __func__);

	mutex_lock(&nvt->rdev->lock);
	अगर (nvt->rdev->users)
		nvt_disable_cir(nvt);
	mutex_unlock(&nvt->rdev->lock);

	/* make sure wake is enabled */
	nvt_enable_wake(nvt);

	वापस 0;
पूर्ण

अटल पूर्णांक nvt_resume(काष्ठा pnp_dev *pdev)
अणु
	काष्ठा nvt_dev *nvt = pnp_get_drvdata(pdev);

	nvt_dbg("%s called", __func__);

	nvt_cir_regs_init(nvt);
	nvt_cir_wake_regs_init(nvt);

	mutex_lock(&nvt->rdev->lock);
	अगर (nvt->rdev->users)
		nvt_enable_cir(nvt);
	mutex_unlock(&nvt->rdev->lock);

	वापस 0;
पूर्ण

अटल व्योम nvt_shutकरोwn(काष्ठा pnp_dev *pdev)
अणु
	काष्ठा nvt_dev *nvt = pnp_get_drvdata(pdev);

	nvt_enable_wake(nvt);
पूर्ण

अटल स्थिर काष्ठा pnp_device_id nvt_ids[] = अणु
	अणु "WEC0530", 0 पूर्ण,   /* CIR */
	अणु "NTN0530", 0 पूर्ण,   /* CIR क्रम new chip's pnp id*/
	अणु "", 0 पूर्ण,
पूर्ण;

अटल काष्ठा pnp_driver nvt_driver = अणु
	.name		= NVT_DRIVER_NAME,
	.id_table	= nvt_ids,
	.flags		= PNP_DRIVER_RES_DO_NOT_CHANGE,
	.probe		= nvt_probe,
	.हटाओ		= nvt_हटाओ,
	.suspend	= nvt_suspend,
	.resume		= nvt_resume,
	.shutकरोwn	= nvt_shutकरोwn,
पूर्ण;

module_param(debug, पूर्णांक, S_IRUGO | S_IWUSR);
MODULE_PARM_DESC(debug, "Enable debugging output");

MODULE_DEVICE_TABLE(pnp, nvt_ids);
MODULE_DESCRIPTION("Nuvoton W83667HG-A & W83677HG-I CIR driver");

MODULE_AUTHOR("Jarod Wilson <jarod@redhat.com>");
MODULE_LICENSE("GPL");

module_pnp_driver(nvt_driver);
