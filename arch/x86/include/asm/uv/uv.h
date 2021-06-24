<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_UV_UV_H
#घोषणा _ASM_X86_UV_UV_H

क्रमागत uv_प्रणाली_type अणुUV_NONE, UV_LEGACY_APIC, UV_X2APICपूर्ण;

#अगर_घोषित CONFIG_X86_UV
#समावेश <linux/efi.h>

#घोषणा	UV_PROC_NODE	"sgi_uv"

अटल अंतरभूत पूर्णांक uv(पूर्णांक uvtype)
अणु
	/* uv(0) is "any" */
	अगर (uvtype >= 0 && uvtype <= 30)
		वापस 1 << uvtype;
	वापस 1;
पूर्ण

बाह्य अचिन्हित दीर्घ uv_systab_phys;

बाह्य क्रमागत uv_प्रणाली_type get_uv_प्रणाली_type(व्योम);
अटल अंतरभूत bool is_early_uv_प्रणाली(व्योम)
अणु
	वापस uv_systab_phys && uv_systab_phys != EFI_INVALID_TABLE_ADDR;
पूर्ण
बाह्य पूर्णांक is_uv_प्रणाली(व्योम);
बाह्य पूर्णांक is_uv_hubbed(पूर्णांक uvtype);
बाह्य व्योम uv_cpu_init(व्योम);
बाह्य व्योम uv_nmi_init(व्योम);
बाह्य व्योम uv_प्रणाली_init(व्योम);

#अन्यथा	/* !X86_UV */

अटल अंतरभूत क्रमागत uv_प्रणाली_type get_uv_प्रणाली_type(व्योम) अणु वापस UV_NONE; पूर्ण
अटल अंतरभूत bool is_early_uv_प्रणाली(व्योम)	अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक is_uv_प्रणाली(व्योम)	अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक is_uv_hubbed(पूर्णांक uv)	अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम uv_cpu_init(व्योम)	अणु पूर्ण
अटल अंतरभूत व्योम uv_प्रणाली_init(व्योम)	अणु पूर्ण

#पूर्ण_अगर	/* X86_UV */

#पूर्ण_अगर	/* _ASM_X86_UV_UV_H */
