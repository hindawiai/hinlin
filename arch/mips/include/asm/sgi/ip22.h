<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * ip22.h: Definitions क्रम SGI IP22 machines
 *
 * Copyright (C) 1996 David S. Miller
 * Copyright (C) 1997, 1998, 1999, 2000 Ralf Baechle
 */

#अगर_अघोषित _SGI_IP22_H
#घोषणा _SGI_IP22_H

/*
 * These are the भव IRQ numbers, we भागide all IRQ's पूर्णांकo
 * 'spaces', the 'space' determines where and how to enable/disable
 * that particular IRQ on an SGI machine. HPC DMA and MC DMA पूर्णांकerrupts
 * are not supported this way. Driver is supposed to allocate HPC/MC
 * पूर्णांकerrupt as shareable and then look to proper status bit (see
 * HAL2 driver). This will prevent many complications, trust me ;-)
 */

#समावेश <irq.h>
#समावेश <यंत्र/sgi/ioc.h>

#घोषणा SGINT_EISA	0	/* 16 EISA irq levels (Indigo2) */
#घोषणा SGINT_CPU	MIPS_CPU_IRQ_BASE	/* MIPS CPU define 8 पूर्णांकerrupt sources */
#घोषणा SGINT_LOCAL0	(SGINT_CPU+8)	/* 8 local0 irq levels */
#घोषणा SGINT_LOCAL1	(SGINT_CPU+16)	/* 8 local1 irq levels */
#घोषणा SGINT_LOCAL2	(SGINT_CPU+24)	/* 8 local2 vectored irq levels */
#घोषणा SGINT_LOCAL3	(SGINT_CPU+32)	/* 8 local3 vectored irq levels */
#घोषणा SGINT_END	(SGINT_CPU+40)	/* End of 'spaces' */

/*
 * Inभागidual पूर्णांकerrupt definitions क्रम the Indy and Indigo2
 */

#घोषणा SGI_SOFT_0_IRQ	SGINT_CPU + 0
#घोषणा SGI_SOFT_1_IRQ	SGINT_CPU + 1
#घोषणा SGI_LOCAL_0_IRQ SGINT_CPU + 2
#घोषणा SGI_LOCAL_1_IRQ SGINT_CPU + 3
#घोषणा SGI_8254_0_IRQ	SGINT_CPU + 4
#घोषणा SGI_8254_1_IRQ	SGINT_CPU + 5
#घोषणा SGI_BUSERR_IRQ	SGINT_CPU + 6
#घोषणा SGI_TIMER_IRQ	SGINT_CPU + 7

#घोषणा SGI_FIFO_IRQ	SGINT_LOCAL0 + 0	/* FIFO full */
#घोषणा SGI_GIO_0_IRQ	SGI_FIFO_IRQ		/* GIO-0 */
#घोषणा SGI_WD93_0_IRQ	SGINT_LOCAL0 + 1	/* 1st onboard WD93 */
#घोषणा SGI_WD93_1_IRQ	SGINT_LOCAL0 + 2	/* 2nd onboard WD93 */
#घोषणा SGI_ENET_IRQ	SGINT_LOCAL0 + 3	/* onboard ethernet */
#घोषणा SGI_MCDMA_IRQ	SGINT_LOCAL0 + 4	/* MC DMA करोne */
#घोषणा SGI_PARPORT_IRQ SGINT_LOCAL0 + 5	/* Parallel port */
#घोषणा SGI_GIO_1_IRQ	SGINT_LOCAL0 + 6	/* GE / GIO-1 / 2nd-HPC */
#घोषणा SGI_MAP_0_IRQ	SGINT_LOCAL0 + 7	/* Mappable पूर्णांकerrupt 0 */

#घोषणा SGI_GPL0_IRQ	SGINT_LOCAL1 + 0	/* General Purpose LOCAL1_N<0> */
#घोषणा SGI_PANEL_IRQ	SGINT_LOCAL1 + 1	/* front panel */
#घोषणा SGI_GPL2_IRQ	SGINT_LOCAL1 + 2	/* General Purpose LOCAL1_N<2> */
#घोषणा SGI_MAP_1_IRQ	SGINT_LOCAL1 + 3	/* Mappable पूर्णांकerrupt 1 */
#घोषणा SGI_HPCDMA_IRQ	SGINT_LOCAL1 + 4	/* HPC DMA करोne */
#घोषणा SGI_ACFAIL_IRQ	SGINT_LOCAL1 + 5	/* AC fail */
#घोषणा SGI_VINO_IRQ	SGINT_LOCAL1 + 6	/* Indy VINO */
#घोषणा SGI_GIO_2_IRQ	SGINT_LOCAL1 + 7	/* Vert retrace / GIO-2 */

/* Mapped पूर्णांकerrupts. These पूर्णांकerrupts may be mapped to either 0, or 1 */
#घोषणा SGI_VERT_IRQ	SGINT_LOCAL2 + 0	/* INT3: newport vertical status */
#घोषणा SGI_EISA_IRQ	SGINT_LOCAL2 + 3	/* EISA पूर्णांकerrupts */
#घोषणा SGI_KEYBD_IRQ	SGINT_LOCAL2 + 4	/* keyboard */
#घोषणा SGI_SERIAL_IRQ	SGINT_LOCAL2 + 5	/* onboard serial */
#घोषणा SGI_GIOEXP0_IRQ	(SGINT_LOCAL2 + 6)	/* Indy GIO EXP0 */
#घोषणा SGI_GIOEXP1_IRQ	(SGINT_LOCAL2 + 7)	/* Indy GIO EXP1 */

#घोषणा ip22_is_fullhouse()	(sgioc->sysid & SGIOC_SYSID_FULLHOUSE)

बाह्य अचिन्हित लघु ip22_eeprom_पढ़ो(अचिन्हित पूर्णांक *ctrl, पूर्णांक reg);
बाह्य अचिन्हित लघु ip22_nvram_पढ़ो(पूर्णांक reg);

#पूर्ण_अगर
