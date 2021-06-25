<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2013 Riअक्षरd Weinberger <richrd@nod.at>
 */

#समावेश <linux/uaccess.h>
#समावेश <linux/kernel.h>
#समावेश <os.h>

bool copy_from_kernel_nofault_allowed(स्थिर व्योम *src, माप_प्रकार size)
अणु
	व्योम *psrc = (व्योम *)roundकरोwn((अचिन्हित दीर्घ)src, PAGE_SIZE);

	अगर ((अचिन्हित दीर्घ)src < PAGE_SIZE || size <= 0)
		वापस false;
	अगर (os_mincore(psrc, size + src - psrc) <= 0)
		वापस false;
	वापस true;
पूर्ण
