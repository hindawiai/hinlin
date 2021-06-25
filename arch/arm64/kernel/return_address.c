<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm64/kernel/वापस_address.c
 *
 * Copyright (C) 2013 Linaro Limited
 * Author: AKASHI Takahiro <takahiro.akashi@linaro.org>
 */

#समावेश <linux/export.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/kprobes.h>

#समावेश <यंत्र/stack_poपूर्णांकer.h>
#समावेश <यंत्र/stacktrace.h>

काष्ठा वापस_address_data अणु
	अचिन्हित पूर्णांक level;
	व्योम *addr;
पूर्ण;

अटल bool save_वापस_addr(व्योम *d, अचिन्हित दीर्घ pc)
अणु
	काष्ठा वापस_address_data *data = d;

	अगर (!data->level) अणु
		data->addr = (व्योम *)pc;
		वापस false;
	पूर्ण अन्यथा अणु
		--data->level;
		वापस true;
	पूर्ण
पूर्ण
NOKPROBE_SYMBOL(save_वापस_addr);

व्योम *वापस_address(अचिन्हित पूर्णांक level)
अणु
	काष्ठा वापस_address_data data;
	काष्ठा stackframe frame;

	data.level = level + 2;
	data.addr = शून्य;

	start_backtrace(&frame,
			(अचिन्हित दीर्घ)__builtin_frame_address(0),
			(अचिन्हित दीर्घ)वापस_address);
	walk_stackframe(current, &frame, save_वापस_addr, &data);

	अगर (!data.level)
		वापस data.addr;
	अन्यथा
		वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(वापस_address);
NOKPROBE_SYMBOL(वापस_address);
