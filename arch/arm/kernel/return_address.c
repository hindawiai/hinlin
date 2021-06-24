<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/kernel/वापस_address.c
 *
 * Copyright (C) 2009 Uwe Kleine-Koenig <u.kleine-koenig@pengutronix.de>
 * क्रम Pengutronix
 */
#समावेश <linux/export.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/sched.h>

#समावेश <यंत्र/stacktrace.h>

काष्ठा वापस_address_data अणु
	अचिन्हित पूर्णांक level;
	व्योम *addr;
पूर्ण;

अटल पूर्णांक save_वापस_addr(काष्ठा stackframe *frame, व्योम *d)
अणु
	काष्ठा वापस_address_data *data = d;

	अगर (!data->level) अणु
		data->addr = (व्योम *)frame->pc;

		वापस 1;
	पूर्ण अन्यथा अणु
		--data->level;
		वापस 0;
	पूर्ण
पूर्ण

व्योम *वापस_address(अचिन्हित पूर्णांक level)
अणु
	काष्ठा वापस_address_data data;
	काष्ठा stackframe frame;

	data.level = level + 2;
	data.addr = शून्य;

	frame.fp = (अचिन्हित दीर्घ)__builtin_frame_address(0);
	frame.sp = current_stack_poपूर्णांकer;
	frame.lr = (अचिन्हित दीर्घ)__builtin_वापस_address(0);
	frame.pc = (अचिन्हित दीर्घ)वापस_address;

	walk_stackframe(&frame, save_वापस_addr, &data);

	अगर (!data.level)
		वापस data.addr;
	अन्यथा
		वापस शून्य;
पूर्ण

EXPORT_SYMBOL_GPL(वापस_address);
