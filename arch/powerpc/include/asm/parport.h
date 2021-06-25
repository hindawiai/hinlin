<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * parport.h: platक्रमm-specअगरic PC-style parport initialisation
 *
 * Copyright (C) 1999, 2000  Tim Waugh <tim@cyberelk.demon.co.uk>
 *
 * This file should only be included by drivers/parport/parport_pc.c.
 */

#अगर_अघोषित _ASM_POWERPC_PARPORT_H
#घोषणा _ASM_POWERPC_PARPORT_H
#अगर_घोषित __KERNEL__

#समावेश <यंत्र/prom.h>

अटल पूर्णांक parport_pc_find_nonpci_ports (पूर्णांक स्वतःirq, पूर्णांक स्वतःdma)
अणु
	काष्ठा device_node *np;
	स्थिर u32 *prop;
	u32 io1, io2;
	पूर्णांक propsize;
	पूर्णांक count = 0;
	पूर्णांक virq;

	क्रम_each_compatible_node(np, "parallel", "pnpPNP,400") अणु
		prop = of_get_property(np, "reg", &propsize);
		अगर (!prop || propsize > 6*माप(u32))
			जारी;
		io1 = prop[1]; io2 = prop[2];

		virq = irq_of_parse_and_map(np, 0);
		अगर (!virq)
			जारी;

		अगर (parport_pc_probe_port(io1, io2, virq, स्वतःdma, शून्य, 0)
				!= शून्य)
			count++;
	पूर्ण
	वापस count;
पूर्ण

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* !(_ASM_POWERPC_PARPORT_H) */
