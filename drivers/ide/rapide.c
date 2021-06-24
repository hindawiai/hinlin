<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 1996-2002 Russell King.
 */

#समावेश <linux/module.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>

#समावेश <यंत्र/ecard.h>

अटल स्थिर काष्ठा ide_port_info rapide_port_info = अणु
	.host_flags		= IDE_HFLAG_MMIO | IDE_HFLAG_NO_DMA,
	.chipset		= ide_generic,
पूर्ण;

अटल व्योम rapide_setup_ports(काष्ठा ide_hw *hw, व्योम __iomem *base,
			       व्योम __iomem *ctrl, अचिन्हित पूर्णांक sz, पूर्णांक irq)
अणु
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ)base;
	पूर्णांक i;

	क्रम (i = 0; i <= 7; i++) अणु
		hw->io_ports_array[i] = port;
		port += sz;
	पूर्ण
	hw->io_ports.ctl_addr = (अचिन्हित दीर्घ)ctrl;
	hw->irq = irq;
पूर्ण

अटल पूर्णांक rapide_probe(काष्ठा expansion_card *ec, स्थिर काष्ठा ecard_id *id)
अणु
	व्योम __iomem *base;
	काष्ठा ide_host *host;
	पूर्णांक ret;
	काष्ठा ide_hw hw, *hws[] = अणु &hw पूर्ण;

	ret = ecard_request_resources(ec);
	अगर (ret)
		जाओ out;

	base = ecardm_iomap(ec, ECARD_RES_MEMC, 0, 0);
	अगर (!base) अणु
		ret = -ENOMEM;
		जाओ release;
	पूर्ण

	स_रखो(&hw, 0, माप(hw));
	rapide_setup_ports(&hw, base, base + 0x818, 1 << 6, ec->irq);
	hw.dev = &ec->dev;

	ret = ide_host_add(&rapide_port_info, hws, 1, &host);
	अगर (ret)
		जाओ release;

	ecard_set_drvdata(ec, host);
	जाओ out;

 release:
	ecard_release_resources(ec);
 out:
	वापस ret;
पूर्ण

अटल व्योम rapide_हटाओ(काष्ठा expansion_card *ec)
अणु
	काष्ठा ide_host *host = ecard_get_drvdata(ec);

	ecard_set_drvdata(ec, शून्य);

	ide_host_हटाओ(host);

	ecard_release_resources(ec);
पूर्ण

अटल काष्ठा ecard_id rapide_ids[] = अणु
	अणु MANU_YELLOWSTONE, PROD_YELLOWSTONE_RAPIDE32 पूर्ण,
	अणु 0xffff, 0xffff पूर्ण
पूर्ण;

अटल काष्ठा ecard_driver rapide_driver = अणु
	.probe		= rapide_probe,
	.हटाओ		= rapide_हटाओ,
	.id_table	= rapide_ids,
	.drv = अणु
		.name	= "rapide",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init rapide_init(व्योम)
अणु
	वापस ecard_रेजिस्टर_driver(&rapide_driver);
पूर्ण

अटल व्योम __निकास rapide_निकास(व्योम)
अणु
	ecard_हटाओ_driver(&rapide_driver);
पूर्ण

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Yellowstone RAPIDE driver");

module_init(rapide_init);
module_निकास(rapide_निकास);
