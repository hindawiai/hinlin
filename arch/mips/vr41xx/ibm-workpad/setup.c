<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  setup.c, Setup क्रम the IBM WorkPad z50.
 *
 *  Copyright (C) 2002-2006  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>

#समावेश <यंत्र/पन.स>

#घोषणा WORKPAD_ISA_IO_BASE	0x15000000
#घोषणा WORKPAD_ISA_IO_SIZE	0x03000000
#घोषणा WORKPAD_ISA_IO_START	0
#घोषणा WORKPAD_ISA_IO_END	(WORKPAD_ISA_IO_SIZE - 1)
#घोषणा WORKPAD_IO_PORT_BASE	KSEG1ADDR(WORKPAD_ISA_IO_BASE)

अटल पूर्णांक __init ibm_workpad_setup(व्योम)
अणु
	set_io_port_base(WORKPAD_IO_PORT_BASE);
	ioport_resource.start = WORKPAD_ISA_IO_START;
	ioport_resource.end = WORKPAD_ISA_IO_END;

	वापस 0;
पूर्ण

arch_initcall(ibm_workpad_setup);
