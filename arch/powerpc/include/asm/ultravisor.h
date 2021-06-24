<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Ultravisor definitions
 *
 * Copyright 2019, IBM Corporation.
 *
 */
#अगर_अघोषित _ASM_POWERPC_ULTRAVISOR_H
#घोषणा _ASM_POWERPC_ULTRAVISOR_H

#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/ultravisor-api.h>
#समावेश <यंत्र/firmware.h>

पूर्णांक early_init_dt_scan_ultravisor(अचिन्हित दीर्घ node, स्थिर अक्षर *uname,
				  पूर्णांक depth, व्योम *data);

/*
 * In ultravisor enabled प्रणालीs, PTCR becomes ultravisor privileged only क्रम
 * writing and an attempt to ग_लिखो to it will cause a Hypervisor Emulation
 * Assistance पूर्णांकerrupt.
 */
अटल अंतरभूत व्योम set_ptcr_when_no_uv(u64 val)
अणु
	अगर (!firmware_has_feature(FW_FEATURE_ULTRAVISOR))
		mtspr(SPRN_PTCR, val);
पूर्ण

अटल अंतरभूत पूर्णांक uv_रेजिस्टर_pate(u64 lpid, u64 dw0, u64 dw1)
अणु
	वापस ucall_norets(UV_WRITE_PATE, lpid, dw0, dw1);
पूर्ण

अटल अंतरभूत पूर्णांक uv_share_page(u64 pfn, u64 npages)
अणु
	वापस ucall_norets(UV_SHARE_PAGE, pfn, npages);
पूर्ण

अटल अंतरभूत पूर्णांक uv_unshare_page(u64 pfn, u64 npages)
अणु
	वापस ucall_norets(UV_UNSHARE_PAGE, pfn, npages);
पूर्ण

अटल अंतरभूत पूर्णांक uv_unshare_all_pages(व्योम)
अणु
	वापस ucall_norets(UV_UNSHARE_ALL_PAGES);
पूर्ण

अटल अंतरभूत पूर्णांक uv_page_in(u64 lpid, u64 src_ra, u64 dst_gpa, u64 flags,
			     u64 page_shअगरt)
अणु
	वापस ucall_norets(UV_PAGE_IN, lpid, src_ra, dst_gpa, flags,
			    page_shअगरt);
पूर्ण

अटल अंतरभूत पूर्णांक uv_page_out(u64 lpid, u64 dst_ra, u64 src_gpa, u64 flags,
			      u64 page_shअगरt)
अणु
	वापस ucall_norets(UV_PAGE_OUT, lpid, dst_ra, src_gpa, flags,
			    page_shअगरt);
पूर्ण

अटल अंतरभूत पूर्णांक uv_रेजिस्टर_mem_slot(u64 lpid, u64 start_gpa, u64 size,
				       u64 flags, u64 slotid)
अणु
	वापस ucall_norets(UV_REGISTER_MEM_SLOT, lpid, start_gpa,
			    size, flags, slotid);
पूर्ण

अटल अंतरभूत पूर्णांक uv_unरेजिस्टर_mem_slot(u64 lpid, u64 slotid)
अणु
	वापस ucall_norets(UV_UNREGISTER_MEM_SLOT, lpid, slotid);
पूर्ण

अटल अंतरभूत पूर्णांक uv_page_inval(u64 lpid, u64 gpa, u64 page_shअगरt)
अणु
	वापस ucall_norets(UV_PAGE_INVAL, lpid, gpa, page_shअगरt);
पूर्ण

अटल अंतरभूत पूर्णांक uv_svm_terminate(u64 lpid)
अणु
	वापस ucall_norets(UV_SVM_TERMINATE, lpid);
पूर्ण

#पूर्ण_अगर	/* _ASM_POWERPC_ULTRAVISOR_H */
