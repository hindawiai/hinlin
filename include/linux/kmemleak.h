<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * include/linux/kmemleak.h
 *
 * Copyright (C) 2008 ARM Limited
 * Written by Catalin Marinas <catalin.marinas@arm.com>
 */

#अगर_अघोषित __KMEMLEAK_H
#घोषणा __KMEMLEAK_H

#समावेश <linux/slab.h>
#समावेश <linux/vदो_स्मृति.h>

#अगर_घोषित CONFIG_DEBUG_KMEMLEAK

बाह्य व्योम kmemleak_init(व्योम) __init;
बाह्य व्योम kmemleak_alloc(स्थिर व्योम *ptr, माप_प्रकार size, पूर्णांक min_count,
			   gfp_t gfp) __ref;
बाह्य व्योम kmemleak_alloc_percpu(स्थिर व्योम __percpu *ptr, माप_प्रकार size,
				  gfp_t gfp) __ref;
बाह्य व्योम kmemleak_vदो_स्मृति(स्थिर काष्ठा vm_काष्ठा *area, माप_प्रकार size,
			     gfp_t gfp) __ref;
बाह्य व्योम kmemleak_मुक्त(स्थिर व्योम *ptr) __ref;
बाह्य व्योम kmemleak_मुक्त_part(स्थिर व्योम *ptr, माप_प्रकार size) __ref;
बाह्य व्योम kmemleak_मुक्त_percpu(स्थिर व्योम __percpu *ptr) __ref;
बाह्य व्योम kmemleak_update_trace(स्थिर व्योम *ptr) __ref;
बाह्य व्योम kmemleak_not_leak(स्थिर व्योम *ptr) __ref;
बाह्य व्योम kmemleak_ignore(स्थिर व्योम *ptr) __ref;
बाह्य व्योम kmemleak_scan_area(स्थिर व्योम *ptr, माप_प्रकार size, gfp_t gfp) __ref;
बाह्य व्योम kmemleak_no_scan(स्थिर व्योम *ptr) __ref;
बाह्य व्योम kmemleak_alloc_phys(phys_addr_t phys, माप_प्रकार size, पूर्णांक min_count,
				gfp_t gfp) __ref;
बाह्य व्योम kmemleak_मुक्त_part_phys(phys_addr_t phys, माप_प्रकार size) __ref;
बाह्य व्योम kmemleak_not_leak_phys(phys_addr_t phys) __ref;
बाह्य व्योम kmemleak_ignore_phys(phys_addr_t phys) __ref;

अटल अंतरभूत व्योम kmemleak_alloc_recursive(स्थिर व्योम *ptr, माप_प्रकार size,
					    पूर्णांक min_count, slab_flags_t flags,
					    gfp_t gfp)
अणु
	अगर (!(flags & SLAB_NOLEAKTRACE))
		kmemleak_alloc(ptr, size, min_count, gfp);
पूर्ण

अटल अंतरभूत व्योम kmemleak_मुक्त_recursive(स्थिर व्योम *ptr, slab_flags_t flags)
अणु
	अगर (!(flags & SLAB_NOLEAKTRACE))
		kmemleak_मुक्त(ptr);
पूर्ण

अटल अंतरभूत व्योम kmemleak_erase(व्योम **ptr)
अणु
	*ptr = शून्य;
पूर्ण

#अन्यथा

अटल अंतरभूत व्योम kmemleak_init(व्योम)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_alloc(स्थिर व्योम *ptr, माप_प्रकार size, पूर्णांक min_count,
				  gfp_t gfp)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_alloc_recursive(स्थिर व्योम *ptr, माप_प्रकार size,
					    पूर्णांक min_count, slab_flags_t flags,
					    gfp_t gfp)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_alloc_percpu(स्थिर व्योम __percpu *ptr, माप_प्रकार size,
					 gfp_t gfp)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_vदो_स्मृति(स्थिर काष्ठा vm_काष्ठा *area, माप_प्रकार size,
				    gfp_t gfp)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_मुक्त(स्थिर व्योम *ptr)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_मुक्त_part(स्थिर व्योम *ptr, माप_प्रकार size)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_मुक्त_recursive(स्थिर व्योम *ptr, slab_flags_t flags)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_मुक्त_percpu(स्थिर व्योम __percpu *ptr)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_update_trace(स्थिर व्योम *ptr)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_not_leak(स्थिर व्योम *ptr)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_ignore(स्थिर व्योम *ptr)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_scan_area(स्थिर व्योम *ptr, माप_प्रकार size, gfp_t gfp)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_erase(व्योम **ptr)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_no_scan(स्थिर व्योम *ptr)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_alloc_phys(phys_addr_t phys, माप_प्रकार size,
				       पूर्णांक min_count, gfp_t gfp)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_मुक्त_part_phys(phys_addr_t phys, माप_प्रकार size)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_not_leak_phys(phys_addr_t phys)
अणु
पूर्ण
अटल अंतरभूत व्योम kmemleak_ignore_phys(phys_addr_t phys)
अणु
पूर्ण

#पूर्ण_अगर	/* CONFIG_DEBUG_KMEMLEAK */

#पूर्ण_अगर	/* __KMEMLEAK_H */
