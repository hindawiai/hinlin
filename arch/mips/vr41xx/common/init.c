<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  init.c, Common initialization routines क्रम NEC VR4100 series.
 *
 *  Copyright (C) 2003-2009  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/irq.h>
#समावेश <linux/माला.स>

#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/vr41xx/irq.h>
#समावेश <यंत्र/vr41xx/vr41xx.h>

#घोषणा IO_MEM_RESOURCE_START	0UL
#घोषणा IO_MEM_RESOURCE_END	0x1fffffffUL

अटल व्योम __init iomem_resource_init(व्योम)
अणु
	iomem_resource.start = IO_MEM_RESOURCE_START;
	iomem_resource.end = IO_MEM_RESOURCE_END;
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	अचिन्हित दीर्घ tघड़ी;

	vr41xx_calculate_घड़ी_frequency();

	tघड़ी = vr41xx_get_tघड़ी_frequency();
	अगर (current_cpu_data.processor_id == PRID_VR4131_REV2_0 ||
	    current_cpu_data.processor_id == PRID_VR4131_REV2_1)
		mips_hpt_frequency = tघड़ी / 2;
	अन्यथा
		mips_hpt_frequency = tघड़ी / 4;
पूर्ण

व्योम __init plat_mem_setup(व्योम)
अणु
	iomem_resource_init();

	vr41xx_siu_setup();
पूर्ण

व्योम __init prom_init(व्योम)
अणु
	पूर्णांक argc, i;
	अक्षर **argv;

	argc = fw_arg0;
	argv = (अक्षर **)fw_arg1;

	क्रम (i = 1; i < argc; i++) अणु
		strlcat(arcs_cmdline, argv[i], COMMAND_LINE_SIZE);
		अगर (i < (argc - 1))
			strlcat(arcs_cmdline, " ", COMMAND_LINE_SIZE);
	पूर्ण
पूर्ण
