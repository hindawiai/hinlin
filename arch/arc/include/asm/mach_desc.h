<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright (C) 2012 Synopsys, Inc. (www.synopsys.com)
 *
 * based on METAG mach/arch.h (which in turn was based on ARM)
 */

#अगर_अघोषित _ASM_ARC_MACH_DESC_H_
#घोषणा _ASM_ARC_MACH_DESC_H_

/**
 * काष्ठा machine_desc - Board specअगरic callbacks, called from ARC common code
 *	Provided by each ARC board using MACHINE_START()/MACHINE_END(), so
 *	a multi-platक्रमm kernel builds with array of such descriptors.
 *	We extend the early DT scan to also match the DT's "compatible" string
 *	against the @dt_compat of all such descriptors, and one with highest
 *	"DT score" is selected as global @machine_desc.
 *
 * @name:		Board/SoC name
 * @dt_compat:		Array of device tree 'compatible' strings
 * 			(XXX: although only 1st entry is looked at)
 * @init_early:		Very early callback [called from setup_arch()]
 * @init_per_cpu:	क्रम each CPU as it is coming up (SMP as well as UP)
 * 			[(M):init_IRQ(), (o):start_kernel_secondary()]
 * @init_machine:	arch initcall level callback (e.g. populate अटल
 * 			platक्रमm devices or parse Devicetree)
 * @init_late:		Late initcall level callback
 *
 */
काष्ठा machine_desc अणु
	स्थिर अक्षर		*name;
	स्थिर अक्षर		**dt_compat;
	व्योम			(*init_early)(व्योम);
	व्योम			(*init_per_cpu)(अचिन्हित पूर्णांक);
	व्योम			(*init_machine)(व्योम);
	व्योम			(*init_late)(व्योम);

पूर्ण;

/*
 * Current machine - only accessible during boot.
 */
बाह्य स्थिर काष्ठा machine_desc *machine_desc;

/*
 * Machine type table - also only accessible during boot
 */
बाह्य स्थिर काष्ठा machine_desc __arch_info_begin[], __arch_info_end[];

/*
 * Set of macros to define architecture features.
 * This is built पूर्णांकo a table by the linker.
 */
#घोषणा MACHINE_START(_type, _name)			\
अटल स्थिर काष्ठा machine_desc __mach_desc_##_type	\
__used __section(".arch.info.init") = अणु			\
	.name		= _name,

#घोषणा MACHINE_END				\
पूर्ण;

बाह्य स्थिर काष्ठा machine_desc *setup_machine_fdt(व्योम *dt);

#पूर्ण_अगर
