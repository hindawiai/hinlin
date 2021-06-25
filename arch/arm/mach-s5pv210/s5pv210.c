<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Samsung's S5PC110/S5PV210 flattened device tree enabled machine.
//
// Copyright (c) 2013-2014 Samsung Electronics Co., Ltd.
// Mateusz Krawczuk <m.krawczuk@partner.samsung.com>
// Tomasz Figa <t.figa@samsung.com>

#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/प्रणाली_misc.h>

#समावेश "common.h"
#समावेश "regs-clock.h"

अटल पूर्णांक __init s5pv210_fdt_map_sys(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
					पूर्णांक depth, व्योम *data)
अणु
	काष्ठा map_desc iodesc;
	स्थिर __be32 *reg;
	पूर्णांक len;

	अगर (!of_flat_dt_is_compatible(node, "samsung,s5pv210-clock"))
		वापस 0;

	reg = of_get_flat_dt_prop(node, "reg", &len);
	अगर (reg == शून्य || len != (माप(अचिन्हित दीर्घ) * 2))
		वापस 0;

	iodesc.pfn = __phys_to_pfn(be32_to_cpu(reg[0]));
	iodesc.length = be32_to_cpu(reg[1]) - 1;
	iodesc.भव = (अचिन्हित दीर्घ)S3C_VA_SYS;
	iodesc.type = MT_DEVICE;
	iotable_init(&iodesc, 1);

	वापस 1;
पूर्ण

अटल व्योम __init s5pv210_dt_map_io(व्योम)
अणु
	debug_ll_io_init();

	of_scan_flat_dt(s5pv210_fdt_map_sys, शून्य);
पूर्ण

अटल व्योम s5pv210_dt_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	__raw_ग_लिखोl(0x1, S5P_SWRESET);
पूर्ण

अटल व्योम __init s5pv210_dt_init_late(व्योम)
अणु
	platक्रमm_device_रेजिस्टर_simple("s5pv210-cpufreq", -1, शून्य, 0);
	s5pv210_pm_init();
पूर्ण

अटल अक्षर स्थिर *स्थिर s5pv210_dt_compat[] __initस्थिर = अणु
	"samsung,s5pc110",
	"samsung,s5pv210",
	शून्य
पूर्ण;

DT_MACHINE_START(S5PV210_DT, "Samsung S5PC110/S5PV210-based board")
	.dt_compat = s5pv210_dt_compat,
	.map_io = s5pv210_dt_map_io,
	.restart = s5pv210_dt_restart,
	.init_late = s5pv210_dt_init_late,
MACHINE_END
