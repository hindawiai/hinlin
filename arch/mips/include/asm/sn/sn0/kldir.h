<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Derived from IRIX <sys/SN/klसूची.स>, revision 1.21.
 *
 * Copyright (C) 1992 - 1997, 1999, 2000 Silicon Graphics, Inc.
 * Copyright (C) 1999, 2000 by Ralf Baechle
 */
#अगर_अघोषित _ASM_SN_SN0_KLसूची_H
#घोषणा _ASM_SN_SN0_KLसूची_H


/*
 * The kldir memory area resides at a fixed place in each node's memory and
 * provides poपूर्णांकers to most other IP27 memory areas.  This allows us to
 * resize and/or relocate memory areas at a later समय without अवरोधing all
 * firmware and kernels that use them.	Indices in the array are
 * permanently dedicated to areas listed below.	 Some memory areas (marked
 * below) reside at a permanently fixed location, but are included in the
 * directory क्रम completeness.
 */

/*
 * The upper portion of the memory map applies during boot
 * only and is overwritten by IRIX/SYMMON.
 *
 *				      MEMORY MAP PER NODE
 *
 * 0x2000000 (32M)	   +-----------------------------------------+
 *			   |	  IO6 BUFFERS FOR FLASH ENET IOC3    |
 * 0x1F80000 (31.5M)	   +-----------------------------------------+
 *			   |	  IO6 TEXT/DATA/BSS/stack	     |
 * 0x1C00000 (30M)	   +-----------------------------------------+
 *			   |	  IO6 PROM DEBUG TEXT/DATA/BSS/stack |
 * 0x0800000 (28M)	   +-----------------------------------------+
 *			   |	  IP27 PROM TEXT/DATA/BSS/stack	     |
 * 0x1B00000 (27M)	   +-----------------------------------------+
 *			   |	  IP27 CFG			     |
 * 0x1A00000 (26M)	   +-----------------------------------------+
 *			   |	  Graphics PROM			     |
 * 0x1800000 (24M)	   +-----------------------------------------+
 *			   |	  3rd Party PROM drivers	     |
 * 0x1600000 (22M)	   +-----------------------------------------+
 *			   |					     |
 *			   |	  Free				     |
 *			   |					     |
 *			   +-----------------------------------------+
 *			   |	  UNIX DEBUG Version		     |
 * 0x190000 (2M--)	   +-----------------------------------------+
 *			   |	  SYMMON			     |
 *			   |	  (For UNIX Debug only)		     |
 * 0x34000 (208K)	   +-----------------------------------------+
 *			   |	  SYMMON STACK [NUM_CPU_PER_NODE]    |
 *			   |	  (For UNIX Debug only)		     |
 * 0x25000 (148K)	   +-----------------------------------------+
 *			   |	  KLCONFIG - II (temp)		     |
 *			   |					     |
 *			   |	----------------------------	     |
 *			   |					     |
 *			   |	  UNIX NON-DEBUG Version	     |
 * 0x19000 (100K)	   +-----------------------------------------+
 *
 *
 * The lower portion of the memory map contains inक्रमmation that is
 * permanent and is used by the IP27PROM, IO6PROM and IRIX.
 *
 * 0x19000 (100K)	   +-----------------------------------------+
 *			   |					     |
 *			   |	  PI Error Spools (32K)		     |
 *			   |					     |
 * 0x12000 (72K)	   +-----------------------------------------+
 *			   |	  Unused			     |
 * 0x11c00 (71K)	   +-----------------------------------------+
 *			   |	  CPU 1 NMI Eframe area		     |
 * 0x11a00 (70.5K)	   +-----------------------------------------+
 *			   |	  CPU 0 NMI Eframe area		     |
 * 0x11800 (70K)	   +-----------------------------------------+
 *			   |	  CPU 1 NMI Register save area	     |
 * 0x11600 (69.5K)	   +-----------------------------------------+
 *			   |	  CPU 0 NMI Register save area	     |
 * 0x11400 (69K)	   +-----------------------------------------+
 *			   |	  GDA (1k)			     |
 * 0x11000 (68K)	   +-----------------------------------------+
 *			   |	  Early cache Exception stack	     |
 *			   |		 and/or			     |
 *			   |	  kernel/io6prom nmi रेजिस्टरs	     |
 * 0x10800  (66k)	   +-----------------------------------------+
 *			   |	  cache error eframe		     |
 * 0x10400 (65K)	   +-----------------------------------------+
 *			   |	  Exception Handlers (UALIAS copy)   |
 * 0x10000 (64K)	   +-----------------------------------------+
 *			   |					     |
 *			   |					     |
 *			   |	  KLCONFIG - I (permanent) (48K)     |
 *			   |					     |
 *			   |					     |
 *			   |					     |
 * 0x4000 (16K)		   +-----------------------------------------+
 *			   |	  NMI Handler (Protected Page)	     |
 * 0x3000 (12K)		   +-----------------------------------------+
 *			   |	  ARCS PVECTORS (master node only)   |
 * 0x2c00 (11K)		   +-----------------------------------------+
 *			   |	  ARCS TVECTORS (master node only)   |
 * 0x2800 (10K)		   +-----------------------------------------+
 *			   |	  LAUNCH [NUM_CPU]		     |
 * 0x2400 (9K)		   +-----------------------------------------+
 *			   |	  Low memory directory (KLसूची)	     |
 * 0x2000 (8K)		   +-----------------------------------------+
 *			   |	  ARCS SPB (1K)			     |
 * 0x1000 (4K)		   +-----------------------------------------+
 *			   |	  Early cache Exception stack	     |
 *			   |		 and/or			     |
 *			   |	  kernel/io6prom nmi रेजिस्टरs	     |
 * 0x800  (2k)		   +-----------------------------------------+
 *			   |	  cache error eframe		     |
 * 0x400 (1K)		   +-----------------------------------------+
 *			   |	  Exception Handlers		     |
 * 0x0	 (0K)		   +-----------------------------------------+
 */

/*
 * This is defined here because IP27_SYMMON_STK_SIZE must be at least what
 * we define here.  Since it's set up in the prom.  We can't redefine it later
 * and expect more space to be allocated.  The way to find out the true size
 * of the symmon stacks is to भागide SYMMON_STK_SIZE by SYMMON_STK_STRIDE
 * क्रम a particular node.
 */
#घोषणा SYMMON_STACK_SIZE		0x8000

#अगर defined(PROM)

/*
 * These defines are prom version dependent.  No code other than the IP27
 * prom should attempt to use these values.
 */
#घोषणा IP27_LAUNCH_OFFSET		0x2400
#घोषणा IP27_LAUNCH_SIZE		0x400
#घोषणा IP27_LAUNCH_COUNT		2
#घोषणा IP27_LAUNCH_STRIDE		0x200

#घोषणा IP27_KLCONFIG_OFFSET		0x4000
#घोषणा IP27_KLCONFIG_SIZE		0xc000
#घोषणा IP27_KLCONFIG_COUNT		1
#घोषणा IP27_KLCONFIG_STRIDE		0

#घोषणा IP27_NMI_OFFSET			0x3000
#घोषणा IP27_NMI_SIZE			0x40
#घोषणा IP27_NMI_COUNT			2
#घोषणा IP27_NMI_STRIDE			0x40

#घोषणा IP27_PI_ERROR_OFFSET		0x12000
#घोषणा IP27_PI_ERROR_SIZE		0x4000
#घोषणा IP27_PI_ERROR_COUNT		1
#घोषणा IP27_PI_ERROR_STRIDE		0

#घोषणा IP27_SYMMON_STK_OFFSET		0x25000
#घोषणा IP27_SYMMON_STK_SIZE		0xe000
#घोषणा IP27_SYMMON_STK_COUNT		2
/* IP27_SYMMON_STK_STRIDE must be >= SYMMON_STACK_SIZE */
#घोषणा IP27_SYMMON_STK_STRIDE		0x7000

#घोषणा IP27_FREEMEM_OFFSET		0x19000
#घोषणा IP27_FREEMEM_SIZE		-1
#घोषणा IP27_FREEMEM_COUNT		1
#घोषणा IP27_FREEMEM_STRIDE		0

#पूर्ण_अगर /* PROM */
/*
 * There will be only one of these in a partition so the IO6 must set it up.
 */
#घोषणा IO6_GDA_OFFSET			0x11000
#घोषणा IO6_GDA_SIZE			0x400
#घोषणा IO6_GDA_COUNT			1
#घोषणा IO6_GDA_STRIDE			0

/*
 * save area of kernel nmi regs in the prom क्रमmat
 */
#घोषणा IP27_NMI_KREGS_OFFSET		0x11400
#घोषणा IP27_NMI_KREGS_CPU_SIZE		0x200
/*
 * save area of kernel nmi regs in eframe क्रमmat
 */
#घोषणा IP27_NMI_EFRAME_OFFSET		0x11800
#घोषणा IP27_NMI_EFRAME_SIZE		0x200

#पूर्ण_अगर /* _ASM_SN_SN0_KLसूची_H */
