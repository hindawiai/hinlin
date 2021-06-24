<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    i2c Support क्रम the Apple `Hydra' Mac I/O

    Copyright (c) 1999-2004 Geert Uytterhoeven <geert@linux-m68k.org>

    Based on i2c Support क्रम Via Technologies 82C586B South Bridge
    Copyright (c) 1998, 1999 Kyथघsti Mथअlkki <kmalkki@cc.hut.fi>

*/

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/types.h>
#समावेश <linux/i2c.h>
#समावेश <linux/i2c-algo-bit.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/hydra.h>


#घोषणा HYDRA_CPD_PD0	0x00000001	/* CachePD lines */
#घोषणा HYDRA_CPD_PD1	0x00000002
#घोषणा HYDRA_CPD_PD2	0x00000004
#घोषणा HYDRA_CPD_PD3	0x00000008

#घोषणा HYDRA_SCLK	HYDRA_CPD_PD0
#घोषणा HYDRA_SDAT	HYDRA_CPD_PD1
#घोषणा HYDRA_SCLK_OE	0x00000010
#घोषणा HYDRA_SDAT_OE	0x00000020

अटल अंतरभूत व्योम pdregw(व्योम *data, u32 val)
अणु
	काष्ठा Hydra *hydra = (काष्ठा Hydra *)data;
	ग_लिखोl(val, &hydra->CachePD);
पूर्ण

अटल अंतरभूत u32 pdregr(व्योम *data)
अणु
	काष्ठा Hydra *hydra = (काष्ठा Hydra *)data;
	वापस पढ़ोl(&hydra->CachePD);
पूर्ण

अटल व्योम hydra_bit_setscl(व्योम *data, पूर्णांक state)
अणु
	u32 val = pdregr(data);
	अगर (state)
		val &= ~HYDRA_SCLK_OE;
	अन्यथा अणु
		val &= ~HYDRA_SCLK;
		val |= HYDRA_SCLK_OE;
	पूर्ण
	pdregw(data, val);
पूर्ण

अटल व्योम hydra_bit_setsda(व्योम *data, पूर्णांक state)
अणु
	u32 val = pdregr(data);
	अगर (state)
		val &= ~HYDRA_SDAT_OE;
	अन्यथा अणु
		val &= ~HYDRA_SDAT;
		val |= HYDRA_SDAT_OE;
	पूर्ण
	pdregw(data, val);
पूर्ण

अटल पूर्णांक hydra_bit_माला_लोcl(व्योम *data)
अणु
	वापस (pdregr(data) & HYDRA_SCLK) != 0;
पूर्ण

अटल पूर्णांक hydra_bit_माला_लोda(व्योम *data)
अणु
	वापस (pdregr(data) & HYDRA_SDAT) != 0;
पूर्ण

/* ------------------------------------------------------------------------ */

अटल काष्ठा i2c_algo_bit_data hydra_bit_data = अणु
	.setsda		= hydra_bit_setsda,
	.setscl		= hydra_bit_setscl,
	.माला_लोda		= hydra_bit_माला_लोda,
	.माला_लोcl		= hydra_bit_माला_लोcl,
	.udelay		= 5,
	.समयout	= HZ
पूर्ण;

अटल काष्ठा i2c_adapter hydra_adap = अणु
	.owner		= THIS_MODULE,
	.name		= "Hydra i2c",
	.algo_data	= &hydra_bit_data,
पूर्ण;

अटल स्थिर काष्ठा pci_device_id hydra_ids[] = अणु
	अणु PCI_DEVICE(PCI_VENDOR_ID_APPLE, PCI_DEVICE_ID_APPLE_HYDRA) पूर्ण,
	अणु 0, पूर्ण
पूर्ण;

MODULE_DEVICE_TABLE (pci, hydra_ids);

अटल पूर्णांक hydra_probe(काष्ठा pci_dev *dev,
				 स्थिर काष्ठा pci_device_id *id)
अणु
	अचिन्हित दीर्घ base = pci_resource_start(dev, 0);
	पूर्णांक res;

	अगर (!request_mem_region(base+दुरत्व(काष्ठा Hydra, CachePD), 4,
				hydra_adap.name))
		वापस -EBUSY;

	hydra_bit_data.data = pci_ioremap_bar(dev, 0);
	अगर (hydra_bit_data.data == शून्य) अणु
		release_mem_region(base+दुरत्व(काष्ठा Hydra, CachePD), 4);
		वापस -ENODEV;
	पूर्ण

	pdregw(hydra_bit_data.data, 0);		/* clear SCLK_OE and SDAT_OE */
	hydra_adap.dev.parent = &dev->dev;
	res = i2c_bit_add_bus(&hydra_adap);
	अगर (res < 0) अणु
		iounmap(hydra_bit_data.data);
		release_mem_region(base+दुरत्व(काष्ठा Hydra, CachePD), 4);
		वापस res;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम hydra_हटाओ(काष्ठा pci_dev *dev)
अणु
	pdregw(hydra_bit_data.data, 0);		/* clear SCLK_OE and SDAT_OE */
	i2c_del_adapter(&hydra_adap);
	iounmap(hydra_bit_data.data);
	release_mem_region(pci_resource_start(dev, 0)+
			   दुरत्व(काष्ठा Hydra, CachePD), 4);
पूर्ण


अटल काष्ठा pci_driver hydra_driver = अणु
	.name		= "hydra_smbus",
	.id_table	= hydra_ids,
	.probe		= hydra_probe,
	.हटाओ		= hydra_हटाओ,
पूर्ण;

module_pci_driver(hydra_driver);

MODULE_AUTHOR("Geert Uytterhoeven <geert@linux-m68k.org>");
MODULE_DESCRIPTION("i2c for Apple Hydra Mac I/O");
MODULE_LICENSE("GPL");
