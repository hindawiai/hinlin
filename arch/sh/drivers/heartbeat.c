<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Generic heartbeat driver क्रम regular LED banks
 *
 * Copyright (C) 2007 - 2010  Paul Mundt
 *
 * Most SH reference boards include a number of inभागidual LEDs that can
 * be independently controlled (either via a pre-defined hardware
 * function or via the LED class, अगर desired -- the hardware tends to
 * encapsulate some of the same "triggers" that the LED class supports,
 * so there's not too much value in it).
 *
 * Additionally, most of these boards also have a LED bank that we've
 * traditionally used क्रम strobing the load average. This use हाल is
 * handled by this driver, rather than giving each LED bit position its
 * own काष्ठा device.
 */
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/loadavg.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पन.स>
#समावेश <linux/slab.h>
#समावेश <यंत्र/heartbeat.h>

#घोषणा DRV_NAME "heartbeat"
#घोषणा DRV_VERSION "0.1.2"

अटल अचिन्हित अक्षर शेष_bit_pos[] = अणु 0, 1, 2, 3, 4, 5, 6, 7 पूर्ण;

अटल अंतरभूत व्योम heartbeat_toggle_bit(काष्ठा heartbeat_data *hd,
					अचिन्हित bit, अचिन्हित पूर्णांक inverted)
अणु
	अचिन्हित पूर्णांक new;

	new = (1 << hd->bit_pos[bit]);
	अगर (inverted)
		new = ~new;

	new &= hd->mask;

	चयन (hd->regsize) अणु
	हाल 32:
		new |= ioपढ़ो32(hd->base) & ~hd->mask;
		ioग_लिखो32(new, hd->base);
		अवरोध;
	हाल 16:
		new |= ioपढ़ो16(hd->base) & ~hd->mask;
		ioग_लिखो16(new, hd->base);
		अवरोध;
	शेष:
		new |= ioपढ़ो8(hd->base) & ~hd->mask;
		ioग_लिखो8(new, hd->base);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम heartbeat_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा heartbeat_data *hd = from_समयr(hd, t, समयr);
	अटल अचिन्हित bit = 0, up = 1;

	heartbeat_toggle_bit(hd, bit, hd->flags & HEARTBEAT_INVERTED);

	bit += up;
	अगर ((bit == 0) || (bit == (hd->nr_bits)-1))
		up = -up;

	mod_समयr(&hd->समयr, jअगरfies + (110 - ((300 << FSHIFT) /
			((avenrun[0] / 5) + (3 << FSHIFT)))));
पूर्ण

अटल पूर्णांक heartbeat_drv_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा resource *res;
	काष्ठा heartbeat_data *hd;
	पूर्णांक i;

	अगर (unlikely(pdev->num_resources != 1)) अणु
		dev_err(&pdev->dev, "invalid number of resources\n");
		वापस -EINVAL;
	पूर्ण

	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (unlikely(res == शून्य)) अणु
		dev_err(&pdev->dev, "invalid resource\n");
		वापस -EINVAL;
	पूर्ण

	अगर (pdev->dev.platक्रमm_data) अणु
		hd = pdev->dev.platक्रमm_data;
	पूर्ण अन्यथा अणु
		hd = kzalloc(माप(काष्ठा heartbeat_data), GFP_KERNEL);
		अगर (unlikely(!hd))
			वापस -ENOMEM;
	पूर्ण

	hd->base = ioremap(res->start, resource_size(res));
	अगर (unlikely(!hd->base)) अणु
		dev_err(&pdev->dev, "ioremap failed\n");

		अगर (!pdev->dev.platक्रमm_data)
			kमुक्त(hd);

		वापस -ENXIO;
	पूर्ण

	अगर (!hd->nr_bits) अणु
		hd->bit_pos = शेष_bit_pos;
		hd->nr_bits = ARRAY_SIZE(शेष_bit_pos);
	पूर्ण

	hd->mask = 0;
	क्रम (i = 0; i < hd->nr_bits; i++)
		hd->mask |= (1 << hd->bit_pos[i]);

	अगर (!hd->regsize) अणु
		चयन (res->flags & IORESOURCE_MEM_TYPE_MASK) अणु
		हाल IORESOURCE_MEM_32BIT:
			hd->regsize = 32;
			अवरोध;
		हाल IORESOURCE_MEM_16BIT:
			hd->regsize = 16;
			अवरोध;
		हाल IORESOURCE_MEM_8BIT:
		शेष:
			hd->regsize = 8;
			अवरोध;
		पूर्ण
	पूर्ण

	समयr_setup(&hd->समयr, heartbeat_समयr, 0);
	platक्रमm_set_drvdata(pdev, hd);

	वापस mod_समयr(&hd->समयr, jअगरfies + 1);
पूर्ण

अटल काष्ठा platक्रमm_driver heartbeat_driver = अणु
	.probe		= heartbeat_drv_probe,
	.driver		= अणु
		.name			= DRV_NAME,
		.suppress_bind_attrs	= true,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init heartbeat_init(व्योम)
अणु
	prपूर्णांकk(KERN_NOTICE DRV_NAME ": version %s loaded\n", DRV_VERSION);
	वापस platक्रमm_driver_रेजिस्टर(&heartbeat_driver);
पूर्ण
device_initcall(heartbeat_init);
