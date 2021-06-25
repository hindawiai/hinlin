<शैली गुरु>
/*
 * Broadcom BCM470X / BCM5301X ARM platक्रमm code.
 *
 * Copyright 2013 Hauke Mehrtens <hauke@hauke-m.de>
 *
 * Licensed under the GNU/GPL. See COPYING क्रम details.
 */
#समावेश <linux/of_platक्रमm.h>
#समावेश <यंत्र/hardware/cache-l2x0.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/siginfo.h>
#समावेश <यंत्र/संकेत.स>

#घोषणा FSR_EXTERNAL		(1 << 12)
#घोषणा FSR_READ		(0 << 10)
#घोषणा FSR_IMPRECISE		0x0406

अटल स्थिर अक्षर *स्थिर bcm5301x_dt_compat[] __initस्थिर = अणु
	"brcm,bcm4708",
	शून्य,
पूर्ण;

अटल पूर्णांक bcm5301x_पात_handler(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक fsr,
				  काष्ठा pt_regs *regs)
अणु
	/*
	 * We want to ignore पातs क्रमwarded from the PCIe bus that are
	 * expected and shouldn't really be passed by the PCIe controller.
	 * The biggest disadvantage is the same FSR code may be reported when
	 * पढ़ोing non-existing APB रेजिस्टर and we shouldn't ignore that.
	 */
	अगर (fsr == (FSR_EXTERNAL | FSR_READ | FSR_IMPRECISE))
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम __init bcm5301x_init_early(व्योम)
अणु
	hook_fault_code(16 + 6, bcm5301x_पात_handler, SIGBUS, BUS_OBJERR,
			"imprecise external abort");
पूर्ण

DT_MACHINE_START(BCM5301X, "BCM5301X")
	.l2c_aux_val	= 0,
	.l2c_aux_mask	= ~0,
	.dt_compat	= bcm5301x_dt_compat,
	.init_early	= bcm5301x_init_early,
MACHINE_END
