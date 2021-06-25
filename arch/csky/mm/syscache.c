<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/syscalls.h>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cachectl.h>

SYSCALL_DEFINE3(cacheflush,
		व्योम __user *, addr,
		अचिन्हित दीर्घ, bytes,
		पूर्णांक, cache)
अणु
	चयन (cache) अणु
	हाल ICACHE:
	हाल BCACHE:
		flush_icache_mm_range(current->mm,
				(अचिन्हित दीर्घ)addr,
				(अचिन्हित दीर्घ)addr + bytes);
		fallthrough;
	हाल DCACHE:
		dcache_wb_range((अचिन्हित दीर्घ)addr,
				(अचिन्हित दीर्घ)addr + bytes);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
