<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * local MTRR defines.
 */

#समावेश <linux/types.h>
#समावेश <linux/मानकघोष.स>

#घोषणा MTRR_CHANGE_MASK_FIXED     0x01
#घोषणा MTRR_CHANGE_MASK_VARIABLE  0x02
#घोषणा MTRR_CHANGE_MASK_DEFTYPE   0x04

बाह्य अचिन्हित पूर्णांक mtrr_usage_table[MTRR_MAX_VAR_RANGES];

काष्ठा mtrr_ops अणु
	u32	venकरोr;
	u32	use_पूर्णांकel_अगर;
	व्योम	(*set)(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ base,
		       अचिन्हित दीर्घ size, mtrr_type type);
	व्योम	(*set_all)(व्योम);

	व्योम	(*get)(अचिन्हित पूर्णांक reg, अचिन्हित दीर्घ *base,
		       अचिन्हित दीर्घ *size, mtrr_type *type);
	पूर्णांक	(*get_मुक्त_region)(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size,
				   पूर्णांक replace_reg);
	पूर्णांक	(*validate_add_page)(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size,
				     अचिन्हित पूर्णांक type);
	पूर्णांक	(*have_wrcomb)(व्योम);
पूर्ण;

बाह्य पूर्णांक generic_get_मुक्त_region(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size,
				   पूर्णांक replace_reg);
बाह्य पूर्णांक generic_validate_add_page(अचिन्हित दीर्घ base, अचिन्हित दीर्घ size,
				     अचिन्हित पूर्णांक type);

बाह्य स्थिर काष्ठा mtrr_ops generic_mtrr_ops;

बाह्य पूर्णांक positive_have_wrcomb(व्योम);

/* library functions क्रम processor-specअगरic routines */
काष्ठा set_mtrr_context अणु
	अचिन्हित दीर्घ	flags;
	अचिन्हित दीर्घ	cr4val;
	u32		deftype_lo;
	u32		deftype_hi;
	u32		ccr3;
पूर्ण;

व्योम set_mtrr_करोne(काष्ठा set_mtrr_context *ctxt);
व्योम set_mtrr_cache_disable(काष्ठा set_mtrr_context *ctxt);
व्योम set_mtrr_prepare_save(काष्ठा set_mtrr_context *ctxt);

व्योम fill_mtrr_var_range(अचिन्हित पूर्णांक index,
		u32 base_lo, u32 base_hi, u32 mask_lo, u32 mask_hi);
bool get_mtrr_state(व्योम);
व्योम mtrr_bp_pat_init(व्योम);

बाह्य व्योम __init set_mtrr_ops(स्थिर काष्ठा mtrr_ops *ops);

बाह्य u64 size_or_mask, size_and_mask;
बाह्य स्थिर काष्ठा mtrr_ops *mtrr_अगर;

#घोषणा is_cpu(vnd)	(mtrr_अगर && mtrr_अगर->venकरोr == X86_VENDOR_##vnd)
#घोषणा use_पूर्णांकel()	(mtrr_अगर && mtrr_अगर->use_पूर्णांकel_अगर == 1)

बाह्य अचिन्हित पूर्णांक num_var_ranges;
बाह्य u64 mtrr_tom2;
बाह्य काष्ठा mtrr_state_type mtrr_state;

व्योम mtrr_state_warn(व्योम);
स्थिर अक्षर *mtrr_attrib_to_str(पूर्णांक x);
व्योम mtrr_wrmsr(अचिन्हित, अचिन्हित, अचिन्हित);

/* CPU specअगरic mtrr init functions */
पूर्णांक amd_init_mtrr(व्योम);
पूर्णांक cyrix_init_mtrr(व्योम);
पूर्णांक centaur_init_mtrr(व्योम);

बाह्य पूर्णांक changed_by_mtrr_cleanup;
बाह्य पूर्णांक mtrr_cleanup(अचिन्हित address_bits);
