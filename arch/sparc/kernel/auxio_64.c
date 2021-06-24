<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* auxio.c: Probing क्रम the Sparc AUXIO रेजिस्टर at boot समय.
 *
 * Copyright (C) 1996 David S. Miller (davem@caip.rutgers.edu)
 *
 * Refactoring क्रम unअगरied NCR/PCIO support 2002 Eric Brower (ebrower@usa.net)
 */

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/auxपन.स>

व्योम __iomem *auxio_रेजिस्टर = शून्य;
EXPORT_SYMBOL(auxio_रेजिस्टर);

क्रमागत auxio_type अणु
	AUXIO_TYPE_NODEV,
	AUXIO_TYPE_SBUS,
	AUXIO_TYPE_EBUS
पूर्ण;

अटल क्रमागत auxio_type auxio_devtype = AUXIO_TYPE_NODEV;
अटल DEFINE_SPINLOCK(auxio_lock);

अटल व्योम __auxio_rmw(u8 bits_on, u8 bits_off, पूर्णांक ebus)
अणु
	अगर (auxio_रेजिस्टर) अणु
		अचिन्हित दीर्घ flags;
		u8 regval, newval;

		spin_lock_irqsave(&auxio_lock, flags);

		regval = (ebus ?
			  (u8) पढ़ोl(auxio_रेजिस्टर) :
			  sbus_पढ़ोb(auxio_रेजिस्टर));
		newval =  regval | bits_on;
		newval &= ~bits_off;
		अगर (!ebus)
			newval &= ~AUXIO_AUX1_MASK;
		अगर (ebus)
			ग_लिखोl((u32) newval, auxio_रेजिस्टर);
		अन्यथा
			sbus_ग_लिखोb(newval, auxio_रेजिस्टर);
		
		spin_unlock_irqrestore(&auxio_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम __auxio_set_bit(u8 bit, पूर्णांक on, पूर्णांक ebus)
अणु
	u8 bits_on = (ebus ? AUXIO_PCIO_LED : AUXIO_AUX1_LED);
	u8 bits_off = 0;

	अगर (!on) अणु
		u8 पंचांगp = bits_off;
		bits_off = bits_on;
		bits_on = पंचांगp;
	पूर्ण
	__auxio_rmw(bits_on, bits_off, ebus);
पूर्ण

व्योम auxio_set_led(पूर्णांक on)
अणु
	पूर्णांक ebus = auxio_devtype == AUXIO_TYPE_EBUS;
	u8 bit;

	bit = (ebus ? AUXIO_PCIO_LED : AUXIO_AUX1_LED);
	__auxio_set_bit(bit, on, ebus);
पूर्ण
EXPORT_SYMBOL(auxio_set_led);

अटल व्योम __auxio_sbus_set_lte(पूर्णांक on)
अणु
	__auxio_set_bit(AUXIO_AUX1_LTE, on, 0);
पूर्ण

व्योम auxio_set_lte(पूर्णांक on)
अणु
	चयन(auxio_devtype) अणु
	हाल AUXIO_TYPE_SBUS:
		__auxio_sbus_set_lte(on);
		अवरोध;
	हाल AUXIO_TYPE_EBUS:
	शेष:
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(auxio_set_lte);

अटल स्थिर काष्ठा of_device_id auxio_match[] = अणु
	अणु
		.name = "auxio",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, auxio_match);

अटल पूर्णांक auxio_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा device_node *dp = dev->dev.of_node;
	अचिन्हित दीर्घ size;

	अगर (of_node_name_eq(dp->parent, "ebus")) अणु
		auxio_devtype = AUXIO_TYPE_EBUS;
		size = माप(u32);
	पूर्ण अन्यथा अगर (of_node_name_eq(dp->parent, "sbus")) अणु
		auxio_devtype = AUXIO_TYPE_SBUS;
		size = 1;
	पूर्ण अन्यथा अणु
		prपूर्णांकk("auxio: Unknown parent bus type [%pOFn]\n",
		       dp->parent);
		वापस -ENODEV;
	पूर्ण
	auxio_रेजिस्टर = of_ioremap(&dev->resource[0], 0, size, "auxio");
	अगर (!auxio_रेजिस्टर)
		वापस -ENODEV;

	prपूर्णांकk(KERN_INFO "AUXIO: Found device at %pOF\n", dp);

	अगर (auxio_devtype == AUXIO_TYPE_EBUS)
		auxio_set_led(AUXIO_LED_ON);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver auxio_driver = अणु
	.probe		= auxio_probe,
	.driver = अणु
		.name = "auxio",
		.of_match_table = auxio_match,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init auxio_init(व्योम)
अणु
	वापस platक्रमm_driver_रेजिस्टर(&auxio_driver);
पूर्ण

/* Must be after subsys_initcall() so that busses are probed.  Must
 * be beक्रमe device_initcall() because things like the floppy driver
 * need to use the AUXIO रेजिस्टर.
 */
fs_initcall(auxio_init);
