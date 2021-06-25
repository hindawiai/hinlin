<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * sgi_w1.c - w1 master driver क्रम one wire support in SGI ASICs
 */

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/platक्रमm_data/sgi-w1.h>

#समावेश <linux/w1.h>

#घोषणा MCR_RD_DATA	BIT(0)
#घोषणा MCR_DONE	BIT(1)

#घोषणा MCR_PACK(pulse, sample) (((pulse) << 10) | ((sample) << 2))

काष्ठा sgi_w1_device अणु
	u32 __iomem *mcr;
	काष्ठा w1_bus_master bus_master;
	अक्षर dev_id[64];
पूर्ण;

अटल u8 sgi_w1_रुको(u32 __iomem *mcr)
अणु
	u32 mcr_val;

	करो अणु
		mcr_val = पढ़ोl(mcr);
	पूर्ण जबतक (!(mcr_val & MCR_DONE));

	वापस (mcr_val & MCR_RD_DATA) ? 1 : 0;
पूर्ण

/*
 * this is the low level routine to
 * reset the device on the One Wire पूर्णांकerface
 * on the hardware
 */
अटल u8 sgi_w1_reset_bus(व्योम *data)
अणु
	काष्ठा sgi_w1_device *dev = data;
	u8 ret;

	ग_लिखोl(MCR_PACK(520, 65), dev->mcr);
	ret = sgi_w1_रुको(dev->mcr);
	udelay(500); /* recovery समय */
	वापस ret;
पूर्ण

/*
 * this is the low level routine to पढ़ो/ग_लिखो a bit on the One Wire
 * पूर्णांकerface on the hardware. It करोes ग_लिखो 0 अगर parameter bit is set
 * to 0, otherwise a ग_लिखो 1/पढ़ो.
 */
अटल u8 sgi_w1_touch_bit(व्योम *data, u8 bit)
अणु
	काष्ठा sgi_w1_device *dev = data;
	u8 ret;

	अगर (bit)
		ग_लिखोl(MCR_PACK(6, 13), dev->mcr);
	अन्यथा
		ग_लिखोl(MCR_PACK(80, 30), dev->mcr);

	ret = sgi_w1_रुको(dev->mcr);
	अगर (bit)
		udelay(100); /* recovery */
	वापस ret;
पूर्ण

अटल पूर्णांक sgi_w1_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sgi_w1_device *sdev;
	काष्ठा sgi_w1_platक्रमm_data *pdata;

	sdev = devm_kzalloc(&pdev->dev, माप(काष्ठा sgi_w1_device),
			    GFP_KERNEL);
	अगर (!sdev)
		वापस -ENOMEM;

	sdev->mcr = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(sdev->mcr))
		वापस PTR_ERR(sdev->mcr);

	sdev->bus_master.data = sdev;
	sdev->bus_master.reset_bus = sgi_w1_reset_bus;
	sdev->bus_master.touch_bit = sgi_w1_touch_bit;

	pdata = dev_get_platdata(&pdev->dev);
	अगर (pdata) अणु
		strlcpy(sdev->dev_id, pdata->dev_id, माप(sdev->dev_id));
		sdev->bus_master.dev_id = sdev->dev_id;
	पूर्ण

	platक्रमm_set_drvdata(pdev, sdev);

	वापस w1_add_master_device(&sdev->bus_master);
पूर्ण

/*
 * disassociate the w1 device from the driver
 */
अटल पूर्णांक sgi_w1_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा sgi_w1_device *sdev = platक्रमm_get_drvdata(pdev);

	w1_हटाओ_master_device(&sdev->bus_master);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sgi_w1_driver = अणु
	.driver = अणु
		.name = "sgi_w1",
	पूर्ण,
	.probe = sgi_w1_probe,
	.हटाओ = sgi_w1_हटाओ,
पूर्ण;
module_platक्रमm_driver(sgi_w1_driver);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Thomas Bogendoerfer");
MODULE_DESCRIPTION("Driver for One-Wire IP in SGI ASICs");
