<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* central.c: Central FHC driver क्रम Sunfire/Starfire/Wildfire.
 *
 * Copyright (C) 1997, 1999, 2008 David S. Miller (davem@davemloft.net)
 */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <linux/माला.स>
#समावेश <linux/init.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/fhc.h>
#समावेश <यंत्र/upa.h>

काष्ठा घड़ी_board अणु
	व्योम __iomem		*घड़ी_freq_regs;
	व्योम __iomem		*घड़ी_regs;
	व्योम __iomem		*घड़ी_ver_reg;
	पूर्णांक			num_slots;
	काष्ठा resource		leds_resource;
	काष्ठा platक्रमm_device	leds_pdev;
पूर्ण;

काष्ठा fhc अणु
	व्योम __iomem		*pregs;
	bool			central;
	bool			jtag_master;
	पूर्णांक			board_num;
	काष्ठा resource		leds_resource;
	काष्ठा platक्रमm_device	leds_pdev;
पूर्ण;

अटल पूर्णांक घड़ी_board_calc_nslots(काष्ठा घड़ी_board *p)
अणु
	u8 reg = upa_पढ़ोb(p->घड़ी_regs + CLOCK_STAT1) & 0xc0;

	चयन (reg) अणु
	हाल 0x40:
		वापस 16;

	हाल 0xc0:
		वापस 8;

	हाल 0x80:
		reg = 0;
		अगर (p->घड़ी_ver_reg)
			reg = upa_पढ़ोb(p->घड़ी_ver_reg);
		अगर (reg) अणु
			अगर (reg & 0x80)
				वापस 4;
			अन्यथा
				वापस 5;
		पूर्ण
		fallthrough;
	शेष:
		वापस 4;
	पूर्ण
पूर्ण

अटल पूर्णांक घड़ी_board_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा घड़ी_board *p = kzalloc(माप(*p), GFP_KERNEL);
	पूर्णांक err = -ENOMEM;

	अगर (!p) अणु
		prपूर्णांकk(KERN_ERR "clock_board: Cannot allocate struct clock_board\n");
		जाओ out;
	पूर्ण

	p->घड़ी_freq_regs = of_ioremap(&op->resource[0], 0,
					resource_size(&op->resource[0]),
					"clock_board_freq");
	अगर (!p->घड़ी_freq_regs) अणु
		prपूर्णांकk(KERN_ERR "clock_board: Cannot map clock_freq_regs\n");
		जाओ out_मुक्त;
	पूर्ण

	p->घड़ी_regs = of_ioremap(&op->resource[1], 0,
				   resource_size(&op->resource[1]),
				   "clock_board_regs");
	अगर (!p->घड़ी_regs) अणु
		prपूर्णांकk(KERN_ERR "clock_board: Cannot map clock_regs\n");
		जाओ out_unmap_घड़ी_freq_regs;
	पूर्ण

	अगर (op->resource[2].flags) अणु
		p->घड़ी_ver_reg = of_ioremap(&op->resource[2], 0,
					      resource_size(&op->resource[2]),
					      "clock_ver_reg");
		अगर (!p->घड़ी_ver_reg) अणु
			prपूर्णांकk(KERN_ERR "clock_board: Cannot map clock_ver_reg\n");
			जाओ out_unmap_घड़ी_regs;
		पूर्ण
	पूर्ण

	p->num_slots = घड़ी_board_calc_nslots(p);

	p->leds_resource.start = (अचिन्हित दीर्घ)
		(p->घड़ी_regs + CLOCK_CTRL);
	p->leds_resource.end = p->leds_resource.start;
	p->leds_resource.name = "leds";

	p->leds_pdev.name = "sunfire-clockboard-leds";
	p->leds_pdev.id = -1;
	p->leds_pdev.resource = &p->leds_resource;
	p->leds_pdev.num_resources = 1;
	p->leds_pdev.dev.parent = &op->dev;

	err = platक्रमm_device_रेजिस्टर(&p->leds_pdev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "clock_board: Could not register LEDS "
		       "platform device\n");
		जाओ out_unmap_घड़ी_ver_reg;
	पूर्ण

	prपूर्णांकk(KERN_INFO "clock_board: Detected %d slot Enterprise system.\n",
	       p->num_slots);

	err = 0;
out:
	वापस err;

out_unmap_घड़ी_ver_reg:
	अगर (p->घड़ी_ver_reg)
		of_iounmap(&op->resource[2], p->घड़ी_ver_reg,
			   resource_size(&op->resource[2]));

out_unmap_घड़ी_regs:
	of_iounmap(&op->resource[1], p->घड़ी_regs,
		   resource_size(&op->resource[1]));

out_unmap_घड़ी_freq_regs:
	of_iounmap(&op->resource[0], p->घड़ी_freq_regs,
		   resource_size(&op->resource[0]));

out_मुक्त:
	kमुक्त(p);
	जाओ out;
पूर्ण

अटल स्थिर काष्ठा of_device_id घड़ी_board_match[] = अणु
	अणु
		.name = "clock-board",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver घड़ी_board_driver = अणु
	.probe		= घड़ी_board_probe,
	.driver = अणु
		.name = "clock_board",
		.of_match_table = घड़ी_board_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक fhc_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा fhc *p = kzalloc(माप(*p), GFP_KERNEL);
	पूर्णांक err = -ENOMEM;
	u32 reg;

	अगर (!p) अणु
		prपूर्णांकk(KERN_ERR "fhc: Cannot allocate struct fhc\n");
		जाओ out;
	पूर्ण

	अगर (of_node_name_eq(op->dev.of_node->parent, "central"))
		p->central = true;

	p->pregs = of_ioremap(&op->resource[0], 0,
			      resource_size(&op->resource[0]),
			      "fhc_pregs");
	अगर (!p->pregs) अणु
		prपूर्णांकk(KERN_ERR "fhc: Cannot map pregs\n");
		जाओ out_मुक्त;
	पूर्ण

	अगर (p->central) अणु
		reg = upa_पढ़ोl(p->pregs + FHC_PREGS_BSR);
		p->board_num = ((reg >> 16) & 1) | ((reg >> 12) & 0x0e);
	पूर्ण अन्यथा अणु
		p->board_num = of_getपूर्णांकprop_शेष(op->dev.of_node, "board#", -1);
		अगर (p->board_num == -1) अणु
			prपूर्णांकk(KERN_ERR "fhc: No board# property\n");
			जाओ out_unmap_pregs;
		पूर्ण
		अगर (upa_पढ़ोl(p->pregs + FHC_PREGS_JCTRL) & FHC_JTAG_CTRL_MENAB)
			p->jtag_master = true;
	पूर्ण

	अगर (!p->central) अणु
		p->leds_resource.start = (अचिन्हित दीर्घ)
			(p->pregs + FHC_PREGS_CTRL);
		p->leds_resource.end = p->leds_resource.start;
		p->leds_resource.name = "leds";

		p->leds_pdev.name = "sunfire-fhc-leds";
		p->leds_pdev.id = p->board_num;
		p->leds_pdev.resource = &p->leds_resource;
		p->leds_pdev.num_resources = 1;
		p->leds_pdev.dev.parent = &op->dev;

		err = platक्रमm_device_रेजिस्टर(&p->leds_pdev);
		अगर (err) अणु
			prपूर्णांकk(KERN_ERR "fhc: Could not register LEDS "
			       "platform device\n");
			जाओ out_unmap_pregs;
		पूर्ण
	पूर्ण
	reg = upa_पढ़ोl(p->pregs + FHC_PREGS_CTRL);

	अगर (!p->central)
		reg |= FHC_CONTROL_IXIST;

	reg &= ~(FHC_CONTROL_AOFF |
		 FHC_CONTROL_BOFF |
		 FHC_CONTROL_SLINE);

	upa_ग_लिखोl(reg, p->pregs + FHC_PREGS_CTRL);
	upa_पढ़ोl(p->pregs + FHC_PREGS_CTRL);

	reg = upa_पढ़ोl(p->pregs + FHC_PREGS_ID);
	prपूर्णांकk(KERN_INFO "fhc: Board #%d, Version[%x] PartID[%x] Manuf[%x] %s\n",
	       p->board_num,
	       (reg & FHC_ID_VERS) >> 28,
	       (reg & FHC_ID_PARTID) >> 12,
	       (reg & FHC_ID_MANUF) >> 1,
	       (p->jtag_master ?
		"(JTAG Master)" :
		(p->central ? "(Central)" : "")));

	err = 0;

out:
	वापस err;

out_unmap_pregs:
	of_iounmap(&op->resource[0], p->pregs, resource_size(&op->resource[0]));

out_मुक्त:
	kमुक्त(p);
	जाओ out;
पूर्ण

अटल स्थिर काष्ठा of_device_id fhc_match[] = अणु
	अणु
		.name = "fhc",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver fhc_driver = अणु
	.probe		= fhc_probe,
	.driver = अणु
		.name = "fhc",
		.of_match_table = fhc_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init sunfire_init(व्योम)
अणु
	(व्योम) platक्रमm_driver_रेजिस्टर(&fhc_driver);
	(व्योम) platक्रमm_driver_रेजिस्टर(&घड़ी_board_driver);
	वापस 0;
पूर्ण

fs_initcall(sunfire_init);
