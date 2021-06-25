<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_POWERPC_SETUP_H
#घोषणा _ASM_POWERPC_SETUP_H

#समावेश <uapi/यंत्र/setup.h>

#अगर_अघोषित __ASSEMBLY__
बाह्य व्योम ppc_prपूर्णांकk_progress(अक्षर *s, अचिन्हित लघु hex);

बाह्य अचिन्हित पूर्णांक rtas_data;
बाह्य अचिन्हित दीर्घ दीर्घ memory_limit;
बाह्य bool init_mem_is_मुक्त;
बाह्य अचिन्हित दीर्घ klimit;
बाह्य व्योम *zalloc_maybe_booपंचांगem(माप_प्रकार size, gfp_t mask);

काष्ठा device_node;
बाह्य व्योम note_scsi_host(काष्ठा device_node *, व्योम *);

/* Used in very early kernel initialization. */
बाह्य अचिन्हित दीर्घ reloc_offset(व्योम);
बाह्य अचिन्हित दीर्घ add_reloc_offset(अचिन्हित दीर्घ);
बाह्य व्योम reloc_got2(अचिन्हित दीर्घ);

#घोषणा PTRRELOC(x)	((typeof(x)) add_reloc_offset((अचिन्हित दीर्घ)(x)))

व्योम check_क्रम_initrd(व्योम);
व्योम mem_topology_setup(व्योम);
व्योम iniपंचांगem_init(व्योम);
व्योम setup_panic(व्योम);
#घोषणा ARCH_PANIC_TIMEOUT 180

#अगर_घोषित CONFIG_PPC_PSERIES
बाह्य bool pseries_enable_reloc_on_exc(व्योम);
बाह्य व्योम pseries_disable_reloc_on_exc(व्योम);
बाह्य व्योम pseries_big_endian_exceptions(व्योम);
बाह्य व्योम pseries_little_endian_exceptions(व्योम);
#अन्यथा
अटल अंतरभूत bool pseries_enable_reloc_on_exc(व्योम) अणु वापस false; पूर्ण
अटल अंतरभूत व्योम pseries_disable_reloc_on_exc(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम pseries_big_endian_exceptions(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम pseries_little_endian_exceptions(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PPC_PSERIES */

व्योम rfi_flush_enable(bool enable);

/* These are bit flags */
क्रमागत l1d_flush_type अणु
	L1D_FLUSH_NONE		= 0x1,
	L1D_FLUSH_FALLBACK	= 0x2,
	L1D_FLUSH_ORI		= 0x4,
	L1D_FLUSH_MTTRIG	= 0x8,
पूर्ण;

व्योम setup_rfi_flush(क्रमागत l1d_flush_type, bool enable);
व्योम setup_entry_flush(bool enable);
व्योम setup_uaccess_flush(bool enable);
व्योम करो_rfi_flush_fixups(क्रमागत l1d_flush_type types);
#अगर_घोषित CONFIG_PPC_BARRIER_NOSPEC
व्योम setup_barrier_nospec(व्योम);
#अन्यथा
अटल अंतरभूत व्योम setup_barrier_nospec(व्योम) अणु पूर्ण
#पूर्ण_अगर
व्योम करो_uaccess_flush_fixups(क्रमागत l1d_flush_type types);
व्योम करो_entry_flush_fixups(क्रमागत l1d_flush_type types);
व्योम करो_barrier_nospec_fixups(bool enable);
बाह्य bool barrier_nospec_enabled;

#अगर_घोषित CONFIG_PPC_BARRIER_NOSPEC
व्योम करो_barrier_nospec_fixups_range(bool enable, व्योम *start, व्योम *end);
#अन्यथा
अटल अंतरभूत व्योम करो_barrier_nospec_fixups_range(bool enable, व्योम *start, व्योम *end) अणु पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_FSL_BOOK3E
व्योम setup_spectre_v2(व्योम);
#अन्यथा
अटल अंतरभूत व्योम setup_spectre_v2(व्योम) अणुपूर्ण
#पूर्ण_अगर
व्योम करो_btb_flush_fixups(व्योम);

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर	/* _ASM_POWERPC_SETUP_H */

