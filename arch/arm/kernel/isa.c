<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  linux/arch/arm/kernel/isa.c
 *
 *  Copyright (C) 1999 Phil Blundell
 *
 *  ISA shared memory and I/O port support, and is required to support
 *  iopl, inb, outb and मित्रs in userspace via glibc emulation.
 */
#समावेश <linux/मानकघोष.स>
#समावेश <linux/types.h>
#समावेश <linux/fs.h>
#समावेश <linux/sysctl.h>
#समावेश <linux/init.h>
#समावेश <linux/पन.स>

अटल अचिन्हित पूर्णांक isa_membase, isa_portbase, isa_portshअगरt;

अटल काष्ठा ctl_table ctl_isa_vars[4] = अणु
	अणु
		.procname	= "membase",
		.data		= &isa_membase, 
		.maxlen		= माप(isa_membase),
		.mode		= 0444,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण, अणु
		.procname	= "portbase",
		.data		= &isa_portbase, 
		.maxlen		= माप(isa_portbase),
		.mode		= 0444,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण, अणु
		.procname	= "portshift",
		.data		= &isa_portshअगरt, 
		.maxlen		= माप(isa_portshअगरt),
		.mode		= 0444,
		.proc_handler	= proc_करोपूर्णांकvec,
	पूर्ण, अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table_header *isa_sysctl_header;

अटल काष्ठा ctl_table ctl_isa[2] = अणु
	अणु
		.procname	= "isa",
		.mode		= 0555,
		.child		= ctl_isa_vars,
	पूर्ण, अणुपूर्ण
पूर्ण;

अटल काष्ठा ctl_table ctl_bus[2] = अणु
	अणु
		.procname	= "bus",
		.mode		= 0555,
		.child		= ctl_isa,
	पूर्ण, अणुपूर्ण
पूर्ण;

व्योम __init
रेजिस्टर_isa_ports(अचिन्हित पूर्णांक membase, अचिन्हित पूर्णांक portbase, अचिन्हित पूर्णांक portshअगरt)
अणु
	isa_membase = membase;
	isa_portbase = portbase;
	isa_portshअगरt = portshअगरt;
	isa_sysctl_header = रेजिस्टर_sysctl_table(ctl_bus);
पूर्ण
