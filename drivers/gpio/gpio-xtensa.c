<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2013 TangoTec Ltd.
 * Author: Baruch Siach <baruch@tkos.co.il>
 *
 * Driver क्रम the Xtensa LX4 GPIO32 Option
 *
 * Documentation: Xtensa LX4 Microprocessor Data Book, Section 2.22
 *
 * GPIO32 is a standard optional extension to the Xtensa architecture core that
 * provides preconfigured output and input ports क्रम पूर्णांकra SoC संकेतing. The
 * GPIO32 option is implemented as 32bit Tensilica Inकाष्ठाion Extension (TIE)
 * output state called EXPSTATE, and 32bit input wire called IMPWIRE. This
 * driver treats input and output states as two distinct devices.
 *
 * Access to GPIO32 specअगरic inकाष्ठाions is controlled by the CPENABLE
 * (Coprocessor Enable Bits) रेजिस्टर. By शेष Xtensa Linux startup code
 * disables access to all coprocessors. This driver sets the CPENABLE bit
 * corresponding to GPIO32 beक्रमe any GPIO32 specअगरic inकाष्ठाion, and restores
 * CPENABLE state after that.
 *
 * This driver is currently incompatible with SMP. The GPIO32 extension is not
 * guaranteed to be available in all cores. Moreover, each core controls a
 * dअगरferent set of IO wires. A theoretical SMP aware version of this driver
 * would need to have a per core workqueue to करो the actual GPIO manipulation.
 */

#समावेश <linux/err.h>
#समावेश <linux/module.h>
#समावेश <linux/gpio/driver.h>
#समावेश <linux/bitops.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/coprocessor.h> /* CPENABLE पढ़ो/ग_लिखो macros */

#अगर_अघोषित XCHAL_CP_ID_XTIOP
#त्रुटि GPIO32 option is not enabled क्रम your xtensa core variant
#पूर्ण_अगर

#अगर XCHAL_HAVE_CP

अटल अंतरभूत अचिन्हित दीर्घ enable_cp(अचिन्हित दीर्घ *cpenable)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	*cpenable = xtensa_get_sr(cpenable);
	xtensa_set_sr(*cpenable | BIT(XCHAL_CP_ID_XTIOP), cpenable);
	वापस flags;
पूर्ण

अटल अंतरभूत व्योम disable_cp(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ cpenable)
अणु
	xtensa_set_sr(cpenable, cpenable);
	local_irq_restore(flags);
पूर्ण

#अन्यथा

अटल अंतरभूत अचिन्हित दीर्घ enable_cp(अचिन्हित दीर्घ *cpenable)
अणु
	*cpenable = 0; /* aव्योम uninitialized value warning */
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम disable_cp(अचिन्हित दीर्घ flags, अचिन्हित दीर्घ cpenable)
अणु
पूर्ण

#पूर्ण_अगर /* XCHAL_HAVE_CP */

अटल पूर्णांक xtensa_impwire_get_direction(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	वापस GPIO_LINE_सूचीECTION_IN; /* input only */
पूर्ण

अटल पूर्णांक xtensa_impwire_get_value(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	अचिन्हित दीर्घ flags, saved_cpenable;
	u32 impwire;

	flags = enable_cp(&saved_cpenable);
	__यंत्र__ __अस्थिर__("read_impwire %0" : "=a" (impwire));
	disable_cp(flags, saved_cpenable);

	वापस !!(impwire & BIT(offset));
पूर्ण

अटल व्योम xtensa_impwire_set_value(काष्ठा gpio_chip *gc, अचिन्हित offset,
				    पूर्णांक value)
अणु
	BUG(); /* output only; should never be called */
पूर्ण

अटल पूर्णांक xtensa_expstate_get_direction(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	वापस GPIO_LINE_सूचीECTION_OUT; /* output only */
पूर्ण

अटल पूर्णांक xtensa_expstate_get_value(काष्ठा gpio_chip *gc, अचिन्हित offset)
अणु
	अचिन्हित दीर्घ flags, saved_cpenable;
	u32 expstate;

	flags = enable_cp(&saved_cpenable);
	__यंत्र__ __अस्थिर__("rur.expstate %0" : "=a" (expstate));
	disable_cp(flags, saved_cpenable);

	वापस !!(expstate & BIT(offset));
पूर्ण

अटल व्योम xtensa_expstate_set_value(काष्ठा gpio_chip *gc, अचिन्हित offset,
				     पूर्णांक value)
अणु
	अचिन्हित दीर्घ flags, saved_cpenable;
	u32 mask = BIT(offset);
	u32 val = value ? BIT(offset) : 0;

	flags = enable_cp(&saved_cpenable);
	__यंत्र__ __अस्थिर__("wrmsk_expstate %0, %1"
			     :: "a" (val), "a" (mask));
	disable_cp(flags, saved_cpenable);
पूर्ण

अटल काष्ठा gpio_chip impwire_chip = अणु
	.label		= "impwire",
	.base		= -1,
	.ngpio		= 32,
	.get_direction	= xtensa_impwire_get_direction,
	.get		= xtensa_impwire_get_value,
	.set		= xtensa_impwire_set_value,
पूर्ण;

अटल काष्ठा gpio_chip expstate_chip = अणु
	.label		= "expstate",
	.base		= -1,
	.ngpio		= 32,
	.get_direction	= xtensa_expstate_get_direction,
	.get		= xtensa_expstate_get_value,
	.set		= xtensa_expstate_set_value,
पूर्ण;

अटल पूर्णांक xtensa_gpio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;

	ret = gpiochip_add_data(&impwire_chip, शून्य);
	अगर (ret)
		वापस ret;
	वापस gpiochip_add_data(&expstate_chip, शून्य);
पूर्ण

अटल काष्ठा platक्रमm_driver xtensa_gpio_driver = अणु
	.driver		= अणु
		.name		= "xtensa-gpio",
	पूर्ण,
	.probe		= xtensa_gpio_probe,
पूर्ण;

अटल पूर्णांक __init xtensa_gpio_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;

	pdev = platक्रमm_device_रेजिस्टर_simple("xtensa-gpio", 0, शून्य, 0);
	अगर (IS_ERR(pdev))
		वापस PTR_ERR(pdev);

	वापस platक्रमm_driver_रेजिस्टर(&xtensa_gpio_driver);
पूर्ण
device_initcall(xtensa_gpio_init);

MODULE_AUTHOR("Baruch Siach <baruch@tkos.co.il>");
MODULE_DESCRIPTION("Xtensa LX4 GPIO32 driver");
MODULE_LICENSE("GPL");
