<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  setup.c, Setup क्रम the CASIO CASSIOPEIA E-11/15/55/65.
 *
 *  Copyright (C) 2002-2006  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>

#समावेश <यंत्र/पन.स>

#घोषणा E55_ISA_IO_BASE		0x1400c000
#घोषणा E55_ISA_IO_SIZE		0x03ff4000
#घोषणा E55_ISA_IO_START	0
#घोषणा E55_ISA_IO_END		(E55_ISA_IO_SIZE - 1)
#घोषणा E55_IO_PORT_BASE	KSEG1ADDR(E55_ISA_IO_BASE)

अटल पूर्णांक __init casio_e55_setup(व्योम)
अणु
	set_io_port_base(E55_IO_PORT_BASE);
	ioport_resource.start = E55_ISA_IO_START;
	ioport_resource.end = E55_ISA_IO_END;

	वापस 0;
पूर्ण

arch_initcall(casio_e55_setup);
