<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (c) Intel Corp. 2007.
 * All Rights Reserved.
 *
 * Intel funded Tungsten Graphics (http://www.tungstengraphics.com) to
 * develop this driver.
 *
 * This file is part of the Carillo Ranch video subप्रणाली driver.
 *
 * Authors:
 *   Thomas Hellstrom <thomas-at-tungstengraphics-करोt-com>
 *   Alan Hourihane <alanh-at-tungstengraphics-करोt-com>
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/pci.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fb.h>
#समावेश "vermilion.h"

/* The PLL Clock रेजिस्टर sits on Host bridge */
#घोषणा CRVML_DEVICE_MCH   0x5001
#घोषणा CRVML_REG_MCHBAR   0x44
#घोषणा CRVML_REG_MCHEN    0x54
#घोषणा CRVML_MCHEN_BIT    (1 << 28)
#घोषणा CRVML_MCHMAP_SIZE  4096
#घोषणा CRVML_REG_CLOCK    0xc3c
#घोषणा CRVML_CLOCK_SHIFT  8
#घोषणा CRVML_CLOCK_MASK   0x00000f00

अटल काष्ठा pci_dev *mch_dev;
अटल u32 mch_bar;
अटल व्योम __iomem *mch_regs_base;
अटल u32 saved_घड़ी;

अटल स्थिर अचिन्हित crvml_घड़ीs[] = अणु
	6750,
	13500,
	27000,
	29700,
	37125,
	54000,
	59400,
	74250,
	120000
	    /*
	     * There are more घड़ीs, but they are disabled on the CR board.
	     */
पूर्ण;

अटल स्थिर u32 crvml_घड़ी_bits[] = अणु
	0x0a,
	0x09,
	0x08,
	0x07,
	0x06,
	0x05,
	0x04,
	0x03,
	0x0b
पूर्ण;

अटल स्थिर अचिन्हित crvml_num_घड़ीs = ARRAY_SIZE(crvml_घड़ीs);

अटल पूर्णांक crvml_sys_restore(काष्ठा vml_sys *sys)
अणु
	व्योम __iomem *घड़ी_reg = mch_regs_base + CRVML_REG_CLOCK;

	ioग_लिखो32(saved_घड़ी, घड़ी_reg);
	ioपढ़ो32(घड़ी_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक crvml_sys_save(काष्ठा vml_sys *sys)
अणु
	व्योम __iomem *घड़ी_reg = mch_regs_base + CRVML_REG_CLOCK;

	saved_घड़ी = ioपढ़ो32(घड़ी_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक crvml_nearest_index(स्थिर काष्ठा vml_sys *sys, पूर्णांक घड़ी)
अणु
	पूर्णांक i;
	पूर्णांक cur_index = 0;
	पूर्णांक cur_dअगरf;
	पूर्णांक dअगरf;

	cur_dअगरf = घड़ी - crvml_घड़ीs[0];
	cur_dअगरf = (cur_dअगरf < 0) ? -cur_dअगरf : cur_dअगरf;
	क्रम (i = 1; i < crvml_num_घड़ीs; ++i) अणु
		dअगरf = घड़ी - crvml_घड़ीs[i];
		dअगरf = (dअगरf < 0) ? -dअगरf : dअगरf;
		अगर (dअगरf < cur_dअगरf) अणु
			cur_index = i;
			cur_dअगरf = dअगरf;
		पूर्ण
	पूर्ण
	वापस cur_index;
पूर्ण

अटल पूर्णांक crvml_nearest_घड़ी(स्थिर काष्ठा vml_sys *sys, पूर्णांक घड़ी)
अणु
	वापस crvml_घड़ीs[crvml_nearest_index(sys, घड़ी)];
पूर्ण

अटल पूर्णांक crvml_set_घड़ी(काष्ठा vml_sys *sys, पूर्णांक घड़ी)
अणु
	व्योम __iomem *घड़ी_reg = mch_regs_base + CRVML_REG_CLOCK;
	पूर्णांक index;
	u32 घड़ी_val;

	index = crvml_nearest_index(sys, घड़ी);

	अगर (crvml_घड़ीs[index] != घड़ी)
		वापस -EINVAL;

	घड़ी_val = ioपढ़ो32(घड़ी_reg) & ~CRVML_CLOCK_MASK;
	घड़ी_val = crvml_घड़ी_bits[index] << CRVML_CLOCK_SHIFT;
	ioग_लिखो32(घड़ी_val, घड़ी_reg);
	ioपढ़ो32(घड़ी_reg);

	वापस 0;
पूर्ण

अटल काष्ठा vml_sys cr_pll_ops = अणु
	.name = "Carillo Ranch",
	.save = crvml_sys_save,
	.restore = crvml_sys_restore,
	.set_घड़ी = crvml_set_घड़ी,
	.nearest_घड़ी = crvml_nearest_घड़ी,
पूर्ण;

अटल पूर्णांक __init cr_pll_init(व्योम)
अणु
	पूर्णांक err;
	u32 dev_en;

	mch_dev = pci_get_device(PCI_VENDOR_ID_INTEL,
					CRVML_DEVICE_MCH, शून्य);
	अगर (!mch_dev) अणु
		prपूर्णांकk(KERN_ERR
		       "Could not find Carillo Ranch MCH device.\n");
		वापस -ENODEV;
	पूर्ण

	pci_पढ़ो_config_dword(mch_dev, CRVML_REG_MCHEN, &dev_en);
	अगर (!(dev_en & CRVML_MCHEN_BIT)) अणु
		prपूर्णांकk(KERN_ERR
		       "Carillo Ranch MCH device was not enabled.\n");
		pci_dev_put(mch_dev);
		वापस -ENODEV;
	पूर्ण

	pci_पढ़ो_config_dword(mch_dev, CRVML_REG_MCHBAR,
			      &mch_bar);
	mch_regs_base =
	    ioremap(mch_bar, CRVML_MCHMAP_SIZE);
	अगर (!mch_regs_base) अणु
		prपूर्णांकk(KERN_ERR
		       "Carillo Ranch MCH device was not enabled.\n");
		pci_dev_put(mch_dev);
		वापस -ENODEV;
	पूर्ण

	err = vmlfb_रेजिस्टर_subsys(&cr_pll_ops);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR
		       "Carillo Ranch failed to initialize vml_sys.\n");
		iounmap(mch_regs_base);
		pci_dev_put(mch_dev);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास cr_pll_निकास(व्योम)
अणु
	vmlfb_unरेजिस्टर_subsys(&cr_pll_ops);

	iounmap(mch_regs_base);
	pci_dev_put(mch_dev);
पूर्ण

module_init(cr_pll_init);
module_निकास(cr_pll_निकास);

MODULE_AUTHOR("Tungsten Graphics Inc.");
MODULE_DESCRIPTION("Carillo Ranch PLL Driver");
MODULE_LICENSE("GPL");
