<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PXA930 track ball mouse driver
 *
 * Copyright (C) 2007 Marvell International Ltd.
 * 2008-02-28: Yong Yao <yaoyong@marvell.com>
 *             initial version
 */

#समावेश <linux/input.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>

#समावेश <mach/hardware.h>
#समावेश <linux/platक्रमm_data/mouse-pxa930_trkball.h>

/* Trackball Controller Register Definitions */
#घोषणा TBCR		(0x000C)
#घोषणा TBCNTR		(0x0010)
#घोषणा TBSBC		(0x0014)

#घोषणा TBCR_TBRST	(1 << 1)
#घोषणा TBCR_TBSB	(1 << 10)

#घोषणा TBCR_Y_FLT(n)	(((n) & 0xf) << 6)
#घोषणा TBCR_X_FLT(n)	(((n) & 0xf) << 2)

#घोषणा TBCNTR_YM(n)	(((n) >> 24) & 0xff)
#घोषणा TBCNTR_YP(n)	(((n) >> 16) & 0xff)
#घोषणा TBCNTR_XM(n)	(((n) >> 8) & 0xff)
#घोषणा TBCNTR_XP(n)	((n) & 0xff)

#घोषणा TBSBC_TBSBC	(0x1)

काष्ठा pxa930_trkball अणु
	काष्ठा pxa930_trkball_platक्रमm_data *pdata;

	/* Memory Mapped Register */
	काष्ठा resource *mem;
	व्योम __iomem *mmio_base;

	काष्ठा input_dev *input;
पूर्ण;

अटल irqवापस_t pxa930_trkball_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा pxa930_trkball *trkball = dev_id;
	काष्ठा input_dev *input = trkball->input;
	पूर्णांक tbcntr, x, y;

	/* According to the spec software must पढ़ो TBCNTR twice:
	 * अगर the पढ़ो value is the same, the पढ़ोing is valid
	 */
	tbcntr = __raw_पढ़ोl(trkball->mmio_base + TBCNTR);

	अगर (tbcntr == __raw_पढ़ोl(trkball->mmio_base + TBCNTR)) अणु
		x = (TBCNTR_XP(tbcntr) - TBCNTR_XM(tbcntr)) / 2;
		y = (TBCNTR_YP(tbcntr) - TBCNTR_YM(tbcntr)) / 2;

		input_report_rel(input, REL_X, x);
		input_report_rel(input, REL_Y, y);
		input_sync(input);
	पूर्ण

	__raw_ग_लिखोl(TBSBC_TBSBC, trkball->mmio_base + TBSBC);
	__raw_ग_लिखोl(0, trkball->mmio_base + TBSBC);

	वापस IRQ_HANDLED;
पूर्ण

/* For TBCR, we need to रुको क्रम a जबतक to make sure it has been modअगरied. */
अटल पूर्णांक ग_लिखो_tbcr(काष्ठा pxa930_trkball *trkball, पूर्णांक v)
अणु
	पूर्णांक i = 100;

	__raw_ग_लिखोl(v, trkball->mmio_base + TBCR);

	जबतक (--i) अणु
		अगर (__raw_पढ़ोl(trkball->mmio_base + TBCR) == v)
			अवरोध;
		msleep(1);
	पूर्ण

	अगर (i == 0) अणु
		pr_err("%s: timed out writing TBCR(%x)!\n", __func__, v);
		वापस -ETIMEDOUT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम pxa930_trkball_config(काष्ठा pxa930_trkball *trkball)
अणु
	uपूर्णांक32_t tbcr;

	/* According to spec, need to ग_लिखो the filters of x,y to 0xf first! */
	tbcr = __raw_पढ़ोl(trkball->mmio_base + TBCR);
	ग_लिखो_tbcr(trkball, tbcr | TBCR_X_FLT(0xf) | TBCR_Y_FLT(0xf));
	ग_लिखो_tbcr(trkball, TBCR_X_FLT(trkball->pdata->x_filter) |
			    TBCR_Y_FLT(trkball->pdata->y_filter));

	/* According to spec, set TBCR_TBRST first, beक्रमe clearing it! */
	tbcr = __raw_पढ़ोl(trkball->mmio_base + TBCR);
	ग_लिखो_tbcr(trkball, tbcr | TBCR_TBRST);
	ग_लिखो_tbcr(trkball, tbcr & ~TBCR_TBRST);

	__raw_ग_लिखोl(TBSBC_TBSBC, trkball->mmio_base + TBSBC);
	__raw_ग_लिखोl(0, trkball->mmio_base + TBSBC);

	pr_debug("%s: final TBCR=%x!\n", __func__,
		 __raw_पढ़ोl(trkball->mmio_base + TBCR));
पूर्ण

अटल पूर्णांक pxa930_trkball_खोलो(काष्ठा input_dev *dev)
अणु
	काष्ठा pxa930_trkball *trkball = input_get_drvdata(dev);

	pxa930_trkball_config(trkball);

	वापस 0;
पूर्ण

अटल व्योम pxa930_trkball_disable(काष्ठा pxa930_trkball *trkball)
अणु
	uपूर्णांक32_t tbcr = __raw_पढ़ोl(trkball->mmio_base + TBCR);

	/* Held in reset, gate the 32-KHz input घड़ी off */
	ग_लिखो_tbcr(trkball, tbcr | TBCR_TBRST);
पूर्ण

अटल व्योम pxa930_trkball_बंद(काष्ठा input_dev *dev)
अणु
	काष्ठा pxa930_trkball *trkball = input_get_drvdata(dev);

	pxa930_trkball_disable(trkball);
पूर्ण

अटल पूर्णांक pxa930_trkball_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa930_trkball *trkball;
	काष्ठा input_dev *input;
	काष्ठा resource *res;
	पूर्णांक irq, error;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENXIO;

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		dev_err(&pdev->dev, "failed to get register memory\n");
		वापस -ENXIO;
	पूर्ण

	trkball = kzalloc(माप(काष्ठा pxa930_trkball), GFP_KERNEL);
	अगर (!trkball)
		वापस -ENOMEM;

	trkball->pdata = dev_get_platdata(&pdev->dev);
	अगर (!trkball->pdata) अणु
		dev_err(&pdev->dev, "no platform data defined\n");
		error = -EINVAL;
		जाओ failed;
	पूर्ण

	trkball->mmio_base = ioremap(res->start, resource_size(res));
	अगर (!trkball->mmio_base) अणु
		dev_err(&pdev->dev, "failed to ioremap registers\n");
		error = -ENXIO;
		जाओ failed;
	पूर्ण

	/* held the module in reset, will be enabled in खोलो() */
	pxa930_trkball_disable(trkball);

	error = request_irq(irq, pxa930_trkball_पूर्णांकerrupt, 0,
			    pdev->name, trkball);
	अगर (error) अणु
		dev_err(&pdev->dev, "failed to request irq: %d\n", error);
		जाओ failed_मुक्त_io;
	पूर्ण

	platक्रमm_set_drvdata(pdev, trkball);

	input = input_allocate_device();
	अगर (!input) अणु
		dev_err(&pdev->dev, "failed to allocate input device\n");
		error = -ENOMEM;
		जाओ failed_मुक्त_irq;
	पूर्ण

	input->name = pdev->name;
	input->id.bustype = BUS_HOST;
	input->खोलो = pxa930_trkball_खोलो;
	input->बंद = pxa930_trkball_बंद;
	input->dev.parent = &pdev->dev;
	input_set_drvdata(input, trkball);

	trkball->input = input;

	input_set_capability(input, EV_REL, REL_X);
	input_set_capability(input, EV_REL, REL_Y);

	error = input_रेजिस्टर_device(input);
	अगर (error) अणु
		dev_err(&pdev->dev, "unable to register input device\n");
		जाओ failed_मुक्त_input;
	पूर्ण

	वापस 0;

failed_मुक्त_input:
	input_मुक्त_device(input);
failed_मुक्त_irq:
	मुक्त_irq(irq, trkball);
failed_मुक्त_io:
	iounmap(trkball->mmio_base);
failed:
	kमुक्त(trkball);
	वापस error;
पूर्ण

अटल पूर्णांक pxa930_trkball_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा pxa930_trkball *trkball = platक्रमm_get_drvdata(pdev);
	पूर्णांक irq = platक्रमm_get_irq(pdev, 0);

	input_unरेजिस्टर_device(trkball->input);
	मुक्त_irq(irq, trkball);
	iounmap(trkball->mmio_base);
	kमुक्त(trkball);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver pxa930_trkball_driver = अणु
	.driver		= अणु
		.name	= "pxa930-trkball",
	पूर्ण,
	.probe		= pxa930_trkball_probe,
	.हटाओ		= pxa930_trkball_हटाओ,
पूर्ण;
module_platक्रमm_driver(pxa930_trkball_driver);

MODULE_AUTHOR("Yong Yao <yaoyong@marvell.com>");
MODULE_DESCRIPTION("PXA930 Trackball Mouse Driver");
MODULE_LICENSE("GPL");
