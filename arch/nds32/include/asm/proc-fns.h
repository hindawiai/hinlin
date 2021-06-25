<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
// Copyright (C) 2005-2017 Andes Technology Corporation

#अगर_अघोषित __NDS32_PROCFNS_H__
#घोषणा __NDS32_PROCFNS_H__

#अगर_घोषित __KERNEL__
#समावेश <यंत्र/page.h>

काष्ठा mm_काष्ठा;
काष्ठा vm_area_काष्ठा;
बाह्य व्योम cpu_proc_init(व्योम);
बाह्य व्योम cpu_proc_fin(व्योम);
बाह्य व्योम cpu_करो_idle(व्योम);
बाह्य व्योम cpu_reset(अचिन्हित दीर्घ reset);
बाह्य व्योम cpu_चयन_mm(काष्ठा mm_काष्ठा *mm);

बाह्य व्योम cpu_dcache_inval_all(व्योम);
बाह्य व्योम cpu_dcache_wbinval_all(व्योम);
बाह्य व्योम cpu_dcache_inval_page(अचिन्हित दीर्घ page);
बाह्य व्योम cpu_dcache_wb_page(अचिन्हित दीर्घ page);
बाह्य व्योम cpu_dcache_wbinval_page(अचिन्हित दीर्घ page);
बाह्य व्योम cpu_dcache_inval_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम cpu_dcache_wb_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम cpu_dcache_wbinval_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

बाह्य व्योम cpu_icache_inval_all(व्योम);
बाह्य व्योम cpu_icache_inval_page(अचिन्हित दीर्घ page);
बाह्य व्योम cpu_icache_inval_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

बाह्य व्योम cpu_cache_wbinval_page(अचिन्हित दीर्घ page, पूर्णांक flushi);
बाह्य व्योम cpu_cache_wbinval_range(अचिन्हित दीर्घ start,
				    अचिन्हित दीर्घ end, पूर्णांक flushi);
बाह्य व्योम cpu_cache_wbinval_range_check(काष्ठा vm_area_काष्ठा *vma,
					  अचिन्हित दीर्घ start,
					  अचिन्हित दीर्घ end, bool flushi,
					  bool wbd);

बाह्य व्योम cpu_dma_wb_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम cpu_dma_inval_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);
बाह्य व्योम cpu_dma_wbinval_range(अचिन्हित दीर्घ start, अचिन्हित दीर्घ end);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __NDS32_PROCFNS_H__ */
