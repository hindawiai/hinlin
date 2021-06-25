<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *
 * Copyright (C) 2008-2009 Gabor Juhos <juhosg@खोलोwrt.org>
 * Copyright (C) 2008 Imre Kaloz <kaloz@खोलोwrt.org>
 * Copyright (C) 2013 John Crispin <john@phrozen.org>
 */

#समावेश <linux/pm.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/delay.h>
#समावेश <linux/reset-controller.h>

#समावेश <यंत्र/reboot.h>

#समावेश <यंत्र/mach-ralink/ralink_regs.h>

/* Reset Control */
#घोषणा SYSC_REG_RESET_CTRL	0x034

#घोषणा RSTCTL_RESET_PCI	BIT(26)
#घोषणा RSTCTL_RESET_SYSTEM	BIT(0)

अटल पूर्णांक ralink_निश्चित_device(काष्ठा reset_controller_dev *rcdev,
				अचिन्हित दीर्घ id)
अणु
	u32 val;

	अगर (id == 0)
		वापस -1;

	val = rt_sysc_r32(SYSC_REG_RESET_CTRL);
	val |= BIT(id);
	rt_sysc_w32(val, SYSC_REG_RESET_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक ralink_deनिश्चित_device(काष्ठा reset_controller_dev *rcdev,
				  अचिन्हित दीर्घ id)
अणु
	u32 val;

	अगर (id == 0)
		वापस -1;

	val = rt_sysc_r32(SYSC_REG_RESET_CTRL);
	val &= ~BIT(id);
	rt_sysc_w32(val, SYSC_REG_RESET_CTRL);

	वापस 0;
पूर्ण

अटल पूर्णांक ralink_reset_device(काष्ठा reset_controller_dev *rcdev,
			       अचिन्हित दीर्घ id)
अणु
	ralink_निश्चित_device(rcdev, id);
	वापस ralink_deनिश्चित_device(rcdev, id);
पूर्ण

अटल स्थिर काष्ठा reset_control_ops reset_ops = अणु
	.reset = ralink_reset_device,
	.निश्चित = ralink_निश्चित_device,
	.deनिश्चित = ralink_deनिश्चित_device,
पूर्ण;

अटल काष्ठा reset_controller_dev reset_dev = अणु
	.ops			= &reset_ops,
	.owner			= THIS_MODULE,
	.nr_resets		= 32,
	.of_reset_n_cells	= 1,
पूर्ण;

व्योम ralink_rst_init(व्योम)
अणु
	reset_dev.of_node = of_find_compatible_node(शून्य, शून्य,
						"ralink,rt2880-reset");
	अगर (!reset_dev.of_node)
		pr_err("Failed to find reset controller node");
	अन्यथा
		reset_controller_रेजिस्टर(&reset_dev);
पूर्ण

अटल व्योम ralink_restart(अक्षर *command)
अणु
	अगर (IS_ENABLED(CONFIG_PCI)) अणु
		rt_sysc_m32(0, RSTCTL_RESET_PCI, SYSC_REG_RESET_CTRL);
		mdelay(50);
	पूर्ण

	local_irq_disable();
	rt_sysc_w32(RSTCTL_RESET_SYSTEM, SYSC_REG_RESET_CTRL);
	unreachable();
पूर्ण

अटल पूर्णांक __init mips_reboot_setup(व्योम)
अणु
	_machine_restart = ralink_restart;

	वापस 0;
पूर्ण

arch_initcall(mips_reboot_setup);
