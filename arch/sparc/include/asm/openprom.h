<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __SPARC_OPENPROM_H
#घोषणा __SPARC_OPENPROM_H

/* खोलोprom.h:  Prom काष्ठाures and defines क्रम access to the OPENBOOT
 *              prom routines and data areas.
 *
 * Copyright (C) 1995,1996 David S. Miller (davem@caip.rutgers.edu)
 */

/* Empirical स्थिरants... */
#घोषणा LINUX_OPPROM_MAGIC      0x10010407

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/of.h>

/* V0 prom device operations. */
काष्ठा linux_dev_v0_funcs अणु
	पूर्णांक (*v0_devखोलो)(अक्षर *device_str);
	पूर्णांक (*v0_devबंद)(पूर्णांक dev_desc);
	पूर्णांक (*v0_rdblkdev)(पूर्णांक dev_desc, पूर्णांक num_blks, पूर्णांक blk_st, अक्षर *buf);
	पूर्णांक (*v0_wrblkdev)(पूर्णांक dev_desc, पूर्णांक num_blks, पूर्णांक blk_st, अक्षर *buf);
	पूर्णांक (*v0_wrnetdev)(पूर्णांक dev_desc, पूर्णांक num_bytes, अक्षर *buf);
	पूर्णांक (*v0_rdnetdev)(पूर्णांक dev_desc, पूर्णांक num_bytes, अक्षर *buf);
	पूर्णांक (*v0_rdअक्षरdev)(पूर्णांक dev_desc, पूर्णांक num_bytes, पूर्णांक dummy, अक्षर *buf);
	पूर्णांक (*v0_wrअक्षरdev)(पूर्णांक dev_desc, पूर्णांक num_bytes, पूर्णांक dummy, अक्षर *buf);
	पूर्णांक (*v0_seekdev)(पूर्णांक dev_desc, दीर्घ logical_offst, पूर्णांक from);
पूर्ण;

/* V2 and later prom device operations. */
काष्ठा linux_dev_v2_funcs अणु
	phandle (*v2_inst2pkg)(पूर्णांक d);	/* Convert ihandle to phandle */
	अक्षर * (*v2_dumb_mem_alloc)(अक्षर *va, अचिन्हित पूर्णांक sz);
	व्योम (*v2_dumb_mem_मुक्त)(अक्षर *va, अचिन्हित पूर्णांक sz);

	/* To map devices पूर्णांकo भव I/O space. */
	अक्षर * (*v2_dumb_mmap)(अक्षर *virta, पूर्णांक which_io, अचिन्हित पूर्णांक paddr, अचिन्हित पूर्णांक sz);
	व्योम (*v2_dumb_munmap)(अक्षर *virta, अचिन्हित पूर्णांक size);

	पूर्णांक (*v2_dev_खोलो)(अक्षर *devpath);
	व्योम (*v2_dev_बंद)(पूर्णांक d);
	पूर्णांक (*v2_dev_पढ़ो)(पूर्णांक d, अक्षर *buf, पूर्णांक nbytes);
	पूर्णांक (*v2_dev_ग_लिखो)(पूर्णांक d, स्थिर अक्षर *buf, पूर्णांक nbytes);
	पूर्णांक (*v2_dev_seek)(पूर्णांक d, पूर्णांक hi, पूर्णांक lo);

	/* Never issued (multistage load support) */
	व्योम (*v2_wheee2)(व्योम);
	व्योम (*v2_wheee3)(व्योम);
पूर्ण;

काष्ठा linux_mlist_v0 अणु
	काष्ठा linux_mlist_v0 *theres_more;
	अचिन्हित पूर्णांक start_adr;
	अचिन्हित पूर्णांक num_bytes;
पूर्ण;

काष्ठा linux_mem_v0 अणु
	काष्ठा linux_mlist_v0 **v0_totphys;
	काष्ठा linux_mlist_v0 **v0_prommap;
	काष्ठा linux_mlist_v0 **v0_available; /* What we can use */
पूर्ण;

/* Arguments sent to the kernel from the boot prompt. */
काष्ठा linux_arguments_v0 अणु
	अक्षर *argv[8];
	अक्षर args[100];
	अक्षर boot_dev[2];
	पूर्णांक boot_dev_ctrl;
	पूर्णांक boot_dev_unit;
	पूर्णांक dev_partition;
	अक्षर *kernel_file_name;
	व्योम *aieee1;           /* XXX */
पूर्ण;

/* V2 and up boot things. */
काष्ठा linux_bootargs_v2 अणु
	अक्षर **bootpath;
	अक्षर **bootargs;
	पूर्णांक *fd_मानक_निवेश;
	पूर्णांक *fd_मानक_निकास;
पूर्ण;

/* The top level PROM vector. */
काष्ठा linux_romvec अणु
	/* Version numbers. */
	अचिन्हित पूर्णांक pv_magic_cookie;
	अचिन्हित पूर्णांक pv_romvers;
	अचिन्हित पूर्णांक pv_plugin_revision;
	अचिन्हित पूर्णांक pv_prपूर्णांकrev;

	/* Version 0 memory descriptors. */
	काष्ठा linux_mem_v0 pv_v0mem;

	/* Node operations. */
	काष्ठा linux_nodeops *pv_nodeops;

	अक्षर **pv_bootstr;
	काष्ठा linux_dev_v0_funcs pv_v0devops;

	अक्षर *pv_मानक_निवेश;
	अक्षर *pv_मानक_निकास;
#घोषणा	PROMDEV_KBD	0		/* input from keyboard */
#घोषणा	PROMDEV_SCREEN	0		/* output to screen */
#घोषणा	PROMDEV_TTYA	1		/* in/out to ttya */
#घोषणा	PROMDEV_TTYB	2		/* in/out to ttyb */

	/* Blocking अक्षर_लो/अक्षर_दो.  NOT REENTRANT! (grr) */
	पूर्णांक (*pv_अक्षर_लो)(व्योम);
	व्योम (*pv_अक्षर_दो)(पूर्णांक ch);

	/* Non-blocking variants. */
	पूर्णांक (*pv_nbअक्षर_लो)(व्योम);
	पूर्णांक (*pv_nbअक्षर_दो)(पूर्णांक ch);

	व्योम (*pv_माला_दोtr)(अक्षर *str, पूर्णांक len);

	/* Miscellany. */
	व्योम (*pv_reboot)(अक्षर *bootstr);
	व्योम (*pv_म_लिखो)(__स्थिर__ अक्षर *fmt, ...);
	व्योम (*pv_पात)(व्योम);
	__अस्थिर__ पूर्णांक *pv_ticks;
	व्योम (*pv_halt)(व्योम);
	व्योम (**pv_synchook)(व्योम);

	/* Evaluate a क्रमth string, not dअगरferent proto क्रम V0 and V2->up. */
	जोड़ अणु
		व्योम (*v0_eval)(पूर्णांक len, अक्षर *str);
		व्योम (*v2_eval)(अक्षर *str);
	पूर्ण pv_क्रमtheval;

	काष्ठा linux_arguments_v0 **pv_v0bootargs;

	/* Get ether address. */
	अचिन्हित पूर्णांक (*pv_enaddr)(पूर्णांक d, अक्षर *enaddr);

	काष्ठा linux_bootargs_v2 pv_v2bootargs;
	काष्ठा linux_dev_v2_funcs pv_v2devops;

	पूर्णांक filler[15];

	/* This one is sun4c/sun4 only. */
	व्योम (*pv_setctxt)(पूर्णांक ctxt, अक्षर *va, पूर्णांक pmeg);

	/* Prom version 3 Multiprocessor routines. This stuff is crazy.
	 * No joke. Calling these when there is only one cpu probably
	 * crashes the machine, have to test this. :-)
	 */

	/* v3_cpustart() will start the cpu 'whichcpu' in mmu-context
	 * 'thiscontext' executing at address 'prog_counter'
	 */
	पूर्णांक (*v3_cpustart)(अचिन्हित पूर्णांक whichcpu, पूर्णांक ctxtbl_ptr,
			   पूर्णांक thiscontext, अक्षर *prog_counter);

	/* v3_cpustop() will cause cpu 'whichcpu' to stop executing
	 * until a resume cpu call is made.
	 */
	पूर्णांक (*v3_cpustop)(अचिन्हित पूर्णांक whichcpu);

	/* v3_cpuidle() will idle cpu 'whichcpu' until a stop or
	 * resume cpu call is made.
	 */
	पूर्णांक (*v3_cpuidle)(अचिन्हित पूर्णांक whichcpu);

	/* v3_cpuresume() will resume processor 'whichcpu' executing
	 * starting with whatever 'pc' and 'npc' were left at the
	 * last 'idle' or 'stop' call.
	 */
	पूर्णांक (*v3_cpuresume)(अचिन्हित पूर्णांक whichcpu);
पूर्ण;

/* Routines क्रम traversing the prom device tree. */
काष्ठा linux_nodeops अणु
	phandle (*no_nextnode)(phandle node);
	phandle (*no_child)(phandle node);
	पूर्णांक (*no_proplen)(phandle node, स्थिर अक्षर *name);
	पूर्णांक (*no_getprop)(phandle node, स्थिर अक्षर *name, अक्षर *val);
	पूर्णांक (*no_setprop)(phandle node, स्थिर अक्षर *name, अक्षर *val, पूर्णांक len);
	अक्षर * (*no_nextprop)(phandle node, अक्षर *name);
पूर्ण;

/* More fun PROM काष्ठाures क्रम device probing. */
#अगर defined(__sparc__) && defined(__arch64__)
#घोषणा PROMREG_MAX     24
#घोषणा PROMVADDR_MAX   16
#घोषणा PROMINTR_MAX    32
#अन्यथा
#घोषणा PROMREG_MAX     16
#घोषणा PROMVADDR_MAX   16
#घोषणा PROMINTR_MAX    15
#पूर्ण_अगर

काष्ठा linux_prom_रेजिस्टरs अणु
	अचिन्हित पूर्णांक which_io;	/* hi part of physical address */
	अचिन्हित पूर्णांक phys_addr;	/* The physical address of this रेजिस्टर */
	अचिन्हित पूर्णांक reg_size;	/* How many bytes करोes this रेजिस्टर take up? */
पूर्ण;

काष्ठा linux_prom64_रेजिस्टरs अणु
	अचिन्हित दीर्घ phys_addr;
	अचिन्हित दीर्घ reg_size;
पूर्ण;

काष्ठा linux_prom_irqs अणु
	पूर्णांक pri;    /* IRQ priority */
	पूर्णांक vector; /* This is foobar, what करोes it करो? */
पूर्ण;

/* Element of the "ranges" vector */
काष्ठा linux_prom_ranges अणु
	अचिन्हित पूर्णांक ot_child_space;
	अचिन्हित पूर्णांक ot_child_base;		/* Bus feels this */
	अचिन्हित पूर्णांक ot_parent_space;
	अचिन्हित पूर्णांक ot_parent_base;		/* CPU looks from here */
	अचिन्हित पूर्णांक or_size;
पूर्ण;

/*
 * Ranges and reg properties are a bit dअगरferent क्रम PCI.
 */
#अगर defined(__sparc__) && defined(__arch64__)
काष्ठा linux_prom_pci_रेजिस्टरs अणु
	अचिन्हित पूर्णांक phys_hi;
	अचिन्हित पूर्णांक phys_mid;
	अचिन्हित पूर्णांक phys_lo;

	अचिन्हित पूर्णांक size_hi;
	अचिन्हित पूर्णांक size_lo;
पूर्ण;
#अन्यथा
काष्ठा linux_prom_pci_रेजिस्टरs अणु
	/*
	 * We करोn't know what inक्रमmation this field contain.
	 * We guess, PCI device function is in bits 15:8
	 * So, ...
	 */
	अचिन्हित पूर्णांक which_io;  /* Let it be which_io */

	अचिन्हित पूर्णांक phys_hi;
	अचिन्हित पूर्णांक phys_lo;

	अचिन्हित पूर्णांक size_hi;
	अचिन्हित पूर्णांक size_lo;
पूर्ण;

#पूर्ण_अगर

काष्ठा linux_prom_pci_ranges अणु
	अचिन्हित पूर्णांक child_phys_hi;	/* Only certain bits are encoded here. */
	अचिन्हित पूर्णांक child_phys_mid;
	अचिन्हित पूर्णांक child_phys_lo;

	अचिन्हित पूर्णांक parent_phys_hi;
	अचिन्हित पूर्णांक parent_phys_lo;

	अचिन्हित पूर्णांक size_hi;
	अचिन्हित पूर्णांक size_lo;
पूर्ण;

काष्ठा linux_prom_pci_पूर्णांकmap अणु
	अचिन्हित पूर्णांक phys_hi;
	अचिन्हित पूर्णांक phys_mid;
	अचिन्हित पूर्णांक phys_lo;

	अचिन्हित पूर्णांक पूर्णांकerrupt;

	पूर्णांक          cnode;
	अचिन्हित पूर्णांक cपूर्णांकerrupt;
पूर्ण;

काष्ठा linux_prom_pci_पूर्णांकmask अणु
	अचिन्हित पूर्णांक phys_hi;
	अचिन्हित पूर्णांक phys_mid;
	अचिन्हित पूर्णांक phys_lo;
	अचिन्हित पूर्णांक पूर्णांकerrupt;
पूर्ण;

#पूर्ण_अगर /* !(__ASSEMBLY__) */

#पूर्ण_अगर /* !(__SPARC_OPENPROM_H) */
