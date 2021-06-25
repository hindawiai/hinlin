<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2018 Hangzhou C-SKY Microप्रणालीs co.,ltd.

#समावेश <linux/export.h>
#समावेश <linux/mm.h>
#समावेश <linux/पन.स>

pgprot_t phys_mem_access_prot(काष्ठा file *file, अचिन्हित दीर्घ pfn,
			      अचिन्हित दीर्घ size, pgprot_t vma_prot)
अणु
	अगर (!pfn_valid(pfn)) अणु
		वापस pgprot_noncached(vma_prot);
	पूर्ण अन्यथा अगर (file->f_flags & O_SYNC) अणु
		वापस pgprot_ग_लिखोcombine(vma_prot);
	पूर्ण

	वापस vma_prot;
पूर्ण
EXPORT_SYMBOL(phys_mem_access_prot);
