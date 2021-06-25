<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * altera-lpt.c
 *
 * altera FPGA driver
 *
 * Copyright (C) Altera Corporation 1998-2001
 * Copyright (C) 2010 NetUP Inc.
 * Copyright (C) 2010 Abylay Ospan <aospan@netup.ru>
 */

#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश "altera-exprt.h"

अटल पूर्णांक lpt_hardware_initialized;

अटल व्योम byteblaster_ग_लिखो(पूर्णांक port, पूर्णांक data)
अणु
	outb((u8)data, (u16)(port + 0x378));
पूर्ण;

अटल पूर्णांक byteblaster_पढ़ो(पूर्णांक port)
अणु
	पूर्णांक data = 0;
	data = inb((u16)(port + 0x378));
	वापस data & 0xff;
पूर्ण;

पूर्णांक netup_jtag_io_lpt(व्योम *device, पूर्णांक पंचांगs, पूर्णांक tdi, पूर्णांक पढ़ो_tकरो)
अणु
	पूर्णांक data = 0;
	पूर्णांक tकरो = 0;
	पूर्णांक initial_lpt_ctrl = 0;

	अगर (!lpt_hardware_initialized) अणु
		initial_lpt_ctrl = byteblaster_पढ़ो(2);
		byteblaster_ग_लिखो(2, (initial_lpt_ctrl | 0x02) & 0xdf);
		lpt_hardware_initialized = 1;
	पूर्ण

	data = ((tdi ? 0x40 : 0) | (पंचांगs ? 0x02 : 0));

	byteblaster_ग_लिखो(0, data);

	अगर (पढ़ो_tकरो) अणु
		tकरो = byteblaster_पढ़ो(1);
		tकरो = ((tकरो & 0x80) ? 0 : 1);
	पूर्ण

	byteblaster_ग_लिखो(0, data | 0x01);

	byteblaster_ग_लिखो(0, data);

	वापस tकरो;
पूर्ण
