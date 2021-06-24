<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SGI IOC3 PS/2 controller driver क्रम linux
 *
 * Copyright (C) 2019 Thomas Bogenकरोerfer <tbogenकरोerfer@suse.de>
 *
 * Based on code Copyright (C) 2005 Stanislaw Skowronek <skylark@unaligned.org>
 *               Copyright (C) 2009 Johannes Dickgreber <tanzy@gmx.de>
 */

#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/serपन.स>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/sn/ioc3.h>

काष्ठा ioc3kbd_data अणु
	काष्ठा ioc3_serioregs __iomem *regs;
	काष्ठा serio *kbd, *aux;
	bool kbd_exists, aux_exists;
	पूर्णांक irq;
पूर्ण;

अटल पूर्णांक ioc3kbd_रुको(काष्ठा ioc3_serioregs __iomem *regs, u32 mask)
अणु
	अचिन्हित दीर्घ समयout = 0;

	जबतक ((पढ़ोl(&regs->km_csr) & mask) && (समयout < 250)) अणु
		udelay(50);
		समयout++;
	पूर्ण
	वापस (समयout >= 250) ? -ETIMEDOUT : 0;
पूर्ण

अटल पूर्णांक ioc3kbd_ग_लिखो(काष्ठा serio *dev, u8 val)
अणु
	काष्ठा ioc3kbd_data *d = dev->port_data;
	पूर्णांक ret;

	ret = ioc3kbd_रुको(d->regs, KM_CSR_K_WRT_PEND);
	अगर (ret)
		वापस ret;

	ग_लिखोl(val, &d->regs->k_wd);

	वापस 0;
पूर्ण

अटल पूर्णांक ioc3kbd_start(काष्ठा serio *dev)
अणु
	काष्ठा ioc3kbd_data *d = dev->port_data;

	d->kbd_exists = true;
	वापस 0;
पूर्ण

अटल व्योम ioc3kbd_stop(काष्ठा serio *dev)
अणु
	काष्ठा ioc3kbd_data *d = dev->port_data;

	d->kbd_exists = false;
पूर्ण

अटल पूर्णांक ioc3aux_ग_लिखो(काष्ठा serio *dev, u8 val)
अणु
	काष्ठा ioc3kbd_data *d = dev->port_data;
	पूर्णांक ret;

	ret = ioc3kbd_रुको(d->regs, KM_CSR_M_WRT_PEND);
	अगर (ret)
		वापस ret;

	ग_लिखोl(val, &d->regs->m_wd);

	वापस 0;
पूर्ण

अटल पूर्णांक ioc3aux_start(काष्ठा serio *dev)
अणु
	काष्ठा ioc3kbd_data *d = dev->port_data;

	d->aux_exists = true;
	वापस 0;
पूर्ण

अटल व्योम ioc3aux_stop(काष्ठा serio *dev)
अणु
	काष्ठा ioc3kbd_data *d = dev->port_data;

	d->aux_exists = false;
पूर्ण

अटल व्योम ioc3kbd_process_data(काष्ठा serio *dev, u32 data)
अणु
	अगर (data & KM_RD_VALID_0)
		serio_पूर्णांकerrupt(dev, (data >> KM_RD_DATA_0_SHIFT) & 0xff, 0);
	अगर (data & KM_RD_VALID_1)
		serio_पूर्णांकerrupt(dev, (data >> KM_RD_DATA_1_SHIFT) & 0xff, 0);
	अगर (data & KM_RD_VALID_2)
		serio_पूर्णांकerrupt(dev, (data >> KM_RD_DATA_2_SHIFT) & 0xff, 0);
पूर्ण

अटल irqवापस_t ioc3kbd_पूर्णांकr(पूर्णांक itq, व्योम *dev_id)
अणु
	काष्ठा ioc3kbd_data *d = dev_id;
	u32 data_k, data_m;

	data_k = पढ़ोl(&d->regs->k_rd);
	अगर (d->kbd_exists)
		ioc3kbd_process_data(d->kbd, data_k);

	data_m = पढ़ोl(&d->regs->m_rd);
	अगर (d->aux_exists)
		ioc3kbd_process_data(d->aux, data_m);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक ioc3kbd_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ioc3_serioregs __iomem *regs;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा ioc3kbd_data *d;
	काष्ठा serio *sk, *sa;
	पूर्णांक irq, ret;

	regs = devm_platक्रमm_ioremap_resource(pdev, 0);
	अगर (IS_ERR(regs))
		वापस PTR_ERR(regs);

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENXIO;

	d = devm_kzalloc(dev, माप(*d), GFP_KERNEL);
	अगर (!d)
		वापस -ENOMEM;

	sk = kzalloc(माप(*sk), GFP_KERNEL);
	अगर (!sk)
		वापस -ENOMEM;

	sa = kzalloc(माप(*sa), GFP_KERNEL);
	अगर (!sa) अणु
		kमुक्त(sk);
		वापस -ENOMEM;
	पूर्ण

	sk->id.type = SERIO_8042;
	sk->ग_लिखो = ioc3kbd_ग_लिखो;
	sk->start = ioc3kbd_start;
	sk->stop = ioc3kbd_stop;
	snम_लिखो(sk->name, माप(sk->name), "IOC3 keyboard %d", pdev->id);
	snम_लिखो(sk->phys, माप(sk->phys), "ioc3/serio%dkbd", pdev->id);
	sk->port_data = d;
	sk->dev.parent = dev;

	sa->id.type = SERIO_8042;
	sa->ग_लिखो = ioc3aux_ग_लिखो;
	sa->start = ioc3aux_start;
	sa->stop = ioc3aux_stop;
	snम_लिखो(sa->name, माप(sa->name), "IOC3 auxiliary %d", pdev->id);
	snम_लिखो(sa->phys, माप(sa->phys), "ioc3/serio%daux", pdev->id);
	sa->port_data = d;
	sa->dev.parent = dev;

	d->regs = regs;
	d->kbd = sk;
	d->aux = sa;
	d->irq = irq;

	platक्रमm_set_drvdata(pdev, d);
	serio_रेजिस्टर_port(d->kbd);
	serio_रेजिस्टर_port(d->aux);

	ret = request_irq(irq, ioc3kbd_पूर्णांकr, IRQF_SHARED, "ioc3-kbd", d);
	अगर (ret) अणु
		dev_err(dev, "could not request IRQ %d\n", irq);
		serio_unरेजिस्टर_port(d->kbd);
		serio_unरेजिस्टर_port(d->aux);
		वापस ret;
	पूर्ण

	/* enable ports */
	ग_लिखोl(KM_CSR_K_CLAMP_3 | KM_CSR_M_CLAMP_3, &regs->km_csr);

	वापस 0;
पूर्ण

अटल पूर्णांक ioc3kbd_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ioc3kbd_data *d = platक्रमm_get_drvdata(pdev);

	मुक्त_irq(d->irq, d);

	serio_unरेजिस्टर_port(d->kbd);
	serio_unरेजिस्टर_port(d->aux);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver ioc3kbd_driver = अणु
	.probe          = ioc3kbd_probe,
	.हटाओ         = ioc3kbd_हटाओ,
	.driver = अणु
		.name = "ioc3-kbd",
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(ioc3kbd_driver);

MODULE_AUTHOR("Thomas Bogendoerfer <tbogendoerfer@suse.de>");
MODULE_DESCRIPTION("SGI IOC3 serio driver");
MODULE_LICENSE("GPL");
