<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * parport.h: platक्रमm-specअगरic PC-style parport initialisation
 *
 * Copyright (C) 1999, 2000  Tim Waugh <tim@cyberelk.demon.co.uk>
 *
 * This file should only be included by drivers/parport/parport_pc.c.
 *
 * RZ: क्रम use with Q40 and other ISA machines
 */

#अगर_अघोषित _ASM_M68K_PARPORT_H
#घोषणा _ASM_M68K_PARPORT_H 1

#अघोषित insl
#अघोषित outsl
#घोषणा insl(port,buf,len)   isa_insb(port,buf,(len)<<2)
#घोषणा outsl(port,buf,len)  isa_outsb(port,buf,(len)<<2)

/* no dma, or IRQ स्वतःprobing */
अटल पूर्णांक parport_pc_find_isa_ports (पूर्णांक स्वतःirq, पूर्णांक स्वतःdma);
अटल पूर्णांक parport_pc_find_nonpci_ports (पूर्णांक स्वतःirq, पूर्णांक स्वतःdma)
अणु
        अगर (! (MACH_IS_Q40))
	  वापस 0; /* count=0 */
	वापस parport_pc_find_isa_ports (PARPORT_IRQ_NONE, PARPORT_DMA_NONE);
पूर्ण

#पूर्ण_अगर /* !(_ASM_M68K_PARPORT_H) */
