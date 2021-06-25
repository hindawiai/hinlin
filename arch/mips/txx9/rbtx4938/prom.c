<शैली गुरु>
/*
 * rbtx4938 specअगरic prom routines
 * Copyright (C) 2000-2001 Toshiba Corporation
 *
 * 2003-2005 (c) MontaVista Software, Inc. This file is licensed under the
 * terms of the GNU General Public License version 2. This program is
 * licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 * Support क्रम TX4938 in 2.6 - Manish Lachwani (mlachwani@mvista.com)
 */

#समावेश <linux/init.h>
#समावेश <linux/memblock.h>
#समावेश <यंत्र/txx9/generic.h>
#समावेश <यंत्र/txx9/rbtx4938.h>

व्योम __init rbtx4938_prom_init(व्योम)
अणु
	memblock_add(0, tx4938_get_mem_size());
	txx9_sio_अक्षर_दो_init(TX4938_SIO_REG(0) & 0xfffffffffULL);
पूर्ण
