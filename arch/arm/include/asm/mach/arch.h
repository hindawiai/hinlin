<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  arch/arm/include/यंत्र/mach/arch.h
 *
 *  Copyright (C) 2000 Russell King
 */

#समावेश <linux/types.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/reboot.h>

काष्ठा tag;
काष्ठा pt_regs;
काष्ठा smp_operations;
#अगर_घोषित CONFIG_SMP
#घोषणा smp_ops(ops) (&(ops))
#घोषणा smp_init_ops(ops) (&(ops))
#अन्यथा
#घोषणा smp_ops(ops) (काष्ठा smp_operations *)शून्य
#घोषणा smp_init_ops(ops) (bool (*)(व्योम))शून्य
#पूर्ण_अगर

काष्ठा machine_desc अणु
	अचिन्हित पूर्णांक		nr;		/* architecture number	*/
	स्थिर अक्षर		*name;		/* architecture name	*/
	अचिन्हित दीर्घ		atag_offset;	/* tagged list (relative) */
	स्थिर अक्षर *स्थिर 	*dt_compat;	/* array of device tree
						 * 'compatible' strings	*/

	अचिन्हित पूर्णांक		nr_irqs;	/* number of IRQs */

#अगर_घोषित CONFIG_ZONE_DMA
	phys_addr_t		dma_zone_size;	/* size of DMA-able area */
#पूर्ण_अगर

	अचिन्हित पूर्णांक		video_start;	/* start of video RAM	*/
	अचिन्हित पूर्णांक		video_end;	/* end of video RAM	*/

	अचिन्हित अक्षर		reserve_lp0 :1;	/* never has lp0	*/
	अचिन्हित अक्षर		reserve_lp1 :1;	/* never has lp1	*/
	अचिन्हित अक्षर		reserve_lp2 :1;	/* never has lp2	*/
	क्रमागत reboot_mode	reboot_mode;	/* शेष restart mode	*/
	अचिन्हित		l2c_aux_val;	/* L2 cache aux value	*/
	अचिन्हित		l2c_aux_mask;	/* L2 cache aux mask	*/
	व्योम			(*l2c_ग_लिखो_sec)(अचिन्हित दीर्घ, अचिन्हित);
	स्थिर काष्ठा smp_operations	*smp;	/* SMP operations	*/
	bool			(*smp_init)(व्योम);
	व्योम			(*fixup)(काष्ठा tag *, अक्षर **);
	व्योम			(*dt_fixup)(व्योम);
	दीर्घ दीर्घ		(*pv_fixup)(व्योम);
	व्योम			(*reserve)(व्योम);/* reserve mem blocks	*/
	व्योम			(*map_io)(व्योम);/* IO mapping function	*/
	व्योम			(*init_early)(व्योम);
	व्योम			(*init_irq)(व्योम);
	व्योम			(*init_समय)(व्योम);
	व्योम			(*init_machine)(व्योम);
	व्योम			(*init_late)(व्योम);
#अगर_घोषित CONFIG_GENERIC_IRQ_MULTI_HANDLER
	व्योम			(*handle_irq)(काष्ठा pt_regs *);
#पूर्ण_अगर
	व्योम			(*restart)(क्रमागत reboot_mode, स्थिर अक्षर *);
पूर्ण;

/*
 * Current machine - only accessible during boot.
 */
बाह्य स्थिर काष्ठा machine_desc *machine_desc;

/*
 * Machine type table - also only accessible during boot
 */
बाह्य स्थिर काष्ठा machine_desc __arch_info_begin[], __arch_info_end[];
#घोषणा क्रम_each_machine_desc(p)			\
	क्रम (p = __arch_info_begin; p < __arch_info_end; p++)

/*
 * Set of macros to define architecture features.  This is built पूर्णांकo
 * a table by the linker.
 */
#घोषणा MACHINE_START(_type,_name)			\
अटल स्थिर काष्ठा machine_desc __mach_desc_##_type	\
 __used							\
 __section(".arch.info.init") = अणु			\
	.nr		= MACH_TYPE_##_type,		\
	.name		= _name,

#घोषणा MACHINE_END				\
पूर्ण;

#घोषणा DT_MACHINE_START(_name, _namestr)		\
अटल स्थिर काष्ठा machine_desc __mach_desc_##_name	\
 __used							\
 __section(".arch.info.init") = अणु			\
	.nr		= ~0,				\
	.name		= _namestr,

#पूर्ण_अगर
