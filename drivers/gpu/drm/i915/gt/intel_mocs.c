<शैली गुरु>
// SPDX-License-Identअगरier: MIT
/*
 * Copyright तऊ 2015 Intel Corporation
 */

#समावेश "i915_drv.h"

#समावेश "intel_engine.h"
#समावेश "intel_gt.h"
#समावेश "intel_lrc_reg.h"
#समावेश "intel_mocs.h"
#समावेश "intel_ring.h"

/* काष्ठाures required */
काष्ठा drm_i915_mocs_entry अणु
	u32 control_value;
	u16 l3cc_value;
	u16 used;
पूर्ण;

काष्ठा drm_i915_mocs_table अणु
	अचिन्हित पूर्णांक size;
	अचिन्हित पूर्णांक n_entries;
	स्थिर काष्ठा drm_i915_mocs_entry *table;
पूर्ण;

/* Defines क्रम the tables (XXX_MOCS_0 - XXX_MOCS_63) */
#घोषणा _LE_CACHEABILITY(value)	((value) << 0)
#घोषणा _LE_TGT_CACHE(value)	((value) << 2)
#घोषणा LE_LRUM(value)		((value) << 4)
#घोषणा LE_AOM(value)		((value) << 6)
#घोषणा LE_RSC(value)		((value) << 7)
#घोषणा LE_SCC(value)		((value) << 8)
#घोषणा LE_PFM(value)		((value) << 11)
#घोषणा LE_SCF(value)		((value) << 14)
#घोषणा LE_COS(value)		((value) << 15)
#घोषणा LE_SSE(value)		((value) << 17)

/* Defines क्रम the tables (LNCFMOCS0 - LNCFMOCS31) - two entries per word */
#घोषणा L3_ESC(value)		((value) << 0)
#घोषणा L3_SCC(value)		((value) << 1)
#घोषणा _L3_CACHEABILITY(value)	((value) << 4)

/* Helper defines */
#घोषणा GEN9_NUM_MOCS_ENTRIES	64  /* 63-64 are reserved, but configured. */

/* (e)LLC caching options */
/*
 * Note: LE_0_PAGETABLE works only up to Gen11; क्रम newer gens it means
 * the same as LE_UC
 */
#घोषणा LE_0_PAGETABLE		_LE_CACHEABILITY(0)
#घोषणा LE_1_UC			_LE_CACHEABILITY(1)
#घोषणा LE_2_WT			_LE_CACHEABILITY(2)
#घोषणा LE_3_WB			_LE_CACHEABILITY(3)

/* Target cache */
#घोषणा LE_TC_0_PAGETABLE	_LE_TGT_CACHE(0)
#घोषणा LE_TC_1_LLC		_LE_TGT_CACHE(1)
#घोषणा LE_TC_2_LLC_ELLC	_LE_TGT_CACHE(2)
#घोषणा LE_TC_3_LLC_ELLC_ALT	_LE_TGT_CACHE(3)

/* L3 caching options */
#घोषणा L3_0_सूचीECT		_L3_CACHEABILITY(0)
#घोषणा L3_1_UC			_L3_CACHEABILITY(1)
#घोषणा L3_2_RESERVED		_L3_CACHEABILITY(2)
#घोषणा L3_3_WB			_L3_CACHEABILITY(3)

#घोषणा MOCS_ENTRY(__idx, __control_value, __l3cc_value) \
	[__idx] = अणु \
		.control_value = __control_value, \
		.l3cc_value = __l3cc_value, \
		.used = 1, \
	पूर्ण

/*
 * MOCS tables
 *
 * These are the MOCS tables that are programmed across all the rings.
 * The control value is programmed to all the rings that support the
 * MOCS रेजिस्टरs. While the l3cc_values are only programmed to the
 * LNCFCMOCS0 - LNCFCMOCS32 रेजिस्टरs.
 *
 * These tables are पूर्णांकended to be kept reasonably consistent across
 * HW platक्रमms, and क्रम ICL+, be identical across OSes. To achieve
 * that, क्रम Icelake and above, list of entries is published as part
 * of bspec.
 *
 * Entries not part of the following tables are undefined as far as
 * userspace is concerned and shouldn't be relied upon.  For Gen < 12
 * they will be initialized to PTE. Gen >= 12 onwards करोn't have a setting क्रम
 * PTE and will be initialized to an invalid value.
 *
 * The last few entries are reserved by the hardware. For ICL+ they
 * should be initialized according to bspec and never used, क्रम older
 * platक्रमms they should never be written to.
 *
 * NOTE: These tables are part of bspec and defined as part of hardware
 *       पूर्णांकerface क्रम ICL+. For older platक्रमms, they are part of kernel
 *       ABI. It is expected that, क्रम specअगरic hardware platक्रमm, existing
 *       entries will reमुख्य स्थिरant and the table will only be updated by
 *       adding new entries, filling unused positions.
 */
#घोषणा GEN9_MOCS_ENTRIES \
	MOCS_ENTRY(I915_MOCS_UNCACHED, \
		   LE_1_UC | LE_TC_2_LLC_ELLC, \
		   L3_1_UC), \
	MOCS_ENTRY(I915_MOCS_PTE, \
		   LE_0_PAGETABLE | LE_TC_0_PAGETABLE | LE_LRUM(3), \
		   L3_3_WB)

अटल स्थिर काष्ठा drm_i915_mocs_entry skl_mocs_table[] = अणु
	GEN9_MOCS_ENTRIES,
	MOCS_ENTRY(I915_MOCS_CACHED,
		   LE_3_WB | LE_TC_2_LLC_ELLC | LE_LRUM(3),
		   L3_3_WB),

	/*
	 * mocs:63
	 * - used by the L3 क्रम all of its evictions.
	 *   Thus it is expected to allow LLC cacheability to enable coherent
	 *   flows to be मुख्यtained.
	 * - used to क्रमce L3 uncachable cycles.
	 *   Thus it is expected to make the surface L3 uncacheable.
	 */
	MOCS_ENTRY(63,
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3),
		   L3_1_UC)
पूर्ण;

/* NOTE: the LE_TGT_CACHE is not used on Broxton */
अटल स्थिर काष्ठा drm_i915_mocs_entry broxton_mocs_table[] = अणु
	GEN9_MOCS_ENTRIES,
	MOCS_ENTRY(I915_MOCS_CACHED,
		   LE_1_UC | LE_TC_2_LLC_ELLC | LE_LRUM(3),
		   L3_3_WB)
पूर्ण;

#घोषणा GEN11_MOCS_ENTRIES \
	/* Entries 0 and 1 are defined per-platक्रमm */ \
	/* Base - L3 + LLC */ \
	MOCS_ENTRY(2, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3), \
		   L3_3_WB), \
	/* Base - Uncached */ \
	MOCS_ENTRY(3, \
		   LE_1_UC | LE_TC_1_LLC, \
		   L3_1_UC), \
	/* Base - L3 */ \
	MOCS_ENTRY(4, \
		   LE_1_UC | LE_TC_1_LLC, \
		   L3_3_WB), \
	/* Base - LLC */ \
	MOCS_ENTRY(5, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3), \
		   L3_1_UC), \
	/* Age 0 - LLC */ \
	MOCS_ENTRY(6, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(1), \
		   L3_1_UC), \
	/* Age 0 - L3 + LLC */ \
	MOCS_ENTRY(7, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(1), \
		   L3_3_WB), \
	/* Age: Don't Chg. - LLC */ \
	MOCS_ENTRY(8, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(2), \
		   L3_1_UC), \
	/* Age: Don't Chg. - L3 + LLC */ \
	MOCS_ENTRY(9, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(2), \
		   L3_3_WB), \
	/* No AOM - LLC */ \
	MOCS_ENTRY(10, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3) | LE_AOM(1), \
		   L3_1_UC), \
	/* No AOM - L3 + LLC */ \
	MOCS_ENTRY(11, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3) | LE_AOM(1), \
		   L3_3_WB), \
	/* No AOM; Age 0 - LLC */ \
	MOCS_ENTRY(12, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(1) | LE_AOM(1), \
		   L3_1_UC), \
	/* No AOM; Age 0 - L3 + LLC */ \
	MOCS_ENTRY(13, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(1) | LE_AOM(1), \
		   L3_3_WB), \
	/* No AOM; Age:DC - LLC */ \
	MOCS_ENTRY(14, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(2) | LE_AOM(1), \
		   L3_1_UC), \
	/* No AOM; Age:DC - L3 + LLC */ \
	MOCS_ENTRY(15, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(2) | LE_AOM(1), \
		   L3_3_WB), \
	/* Self-Snoop - L3 + LLC */ \
	MOCS_ENTRY(18, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3) | LE_SSE(3), \
		   L3_3_WB), \
	/* Skip Caching - L3 + LLC(12.5%) */ \
	MOCS_ENTRY(19, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3) | LE_SCC(7), \
		   L3_3_WB), \
	/* Skip Caching - L3 + LLC(25%) */ \
	MOCS_ENTRY(20, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3) | LE_SCC(3), \
		   L3_3_WB), \
	/* Skip Caching - L3 + LLC(50%) */ \
	MOCS_ENTRY(21, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3) | LE_SCC(1), \
		   L3_3_WB), \
	/* Skip Caching - L3 + LLC(75%) */ \
	MOCS_ENTRY(22, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3) | LE_RSC(1) | LE_SCC(3), \
		   L3_3_WB), \
	/* Skip Caching - L3 + LLC(87.5%) */ \
	MOCS_ENTRY(23, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3) | LE_RSC(1) | LE_SCC(7), \
		   L3_3_WB), \
	/* HW Reserved - SW program but never use */ \
	MOCS_ENTRY(62, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3), \
		   L3_1_UC), \
	/* HW Reserved - SW program but never use */ \
	MOCS_ENTRY(63, \
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3), \
		   L3_1_UC)

अटल स्थिर काष्ठा drm_i915_mocs_entry tgl_mocs_table[] = अणु
	/*
	 * NOTE:
	 * Reserved and unspecअगरied MOCS indices have been set to (L3 + LCC).
	 * These reserved entries should never be used, they may be changed
	 * to low perक्रमmant variants with better coherency in the future अगर
	 * more entries are needed. We are programming index I915_MOCS_PTE(1)
	 * only, __init_mocs_table() take care to program unused index with
	 * this entry.
	 */
	MOCS_ENTRY(I915_MOCS_PTE,
		   LE_0_PAGETABLE | LE_TC_0_PAGETABLE,
		   L3_1_UC),
	GEN11_MOCS_ENTRIES,

	/* Implicitly enable L1 - HDC:L1 + L3 + LLC */
	MOCS_ENTRY(48,
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3),
		   L3_3_WB),
	/* Implicitly enable L1 - HDC:L1 + L3 */
	MOCS_ENTRY(49,
		   LE_1_UC | LE_TC_1_LLC,
		   L3_3_WB),
	/* Implicitly enable L1 - HDC:L1 + LLC */
	MOCS_ENTRY(50,
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3),
		   L3_1_UC),
	/* Implicitly enable L1 - HDC:L1 */
	MOCS_ENTRY(51,
		   LE_1_UC | LE_TC_1_LLC,
		   L3_1_UC),
	/* HW Special Case (CCS) */
	MOCS_ENTRY(60,
		   LE_3_WB | LE_TC_1_LLC | LE_LRUM(3),
		   L3_1_UC),
	/* HW Special Case (Displayable) */
	MOCS_ENTRY(61,
		   LE_1_UC | LE_TC_1_LLC,
		   L3_3_WB),
पूर्ण;

अटल स्थिर काष्ठा drm_i915_mocs_entry icl_mocs_table[] = अणु
	/* Base - Uncached (Deprecated) */
	MOCS_ENTRY(I915_MOCS_UNCACHED,
		   LE_1_UC | LE_TC_1_LLC,
		   L3_1_UC),
	/* Base - L3 + LeCC:PAT (Deprecated) */
	MOCS_ENTRY(I915_MOCS_PTE,
		   LE_0_PAGETABLE | LE_TC_0_PAGETABLE,
		   L3_3_WB),

	GEN11_MOCS_ENTRIES
पूर्ण;

अटल स्थिर काष्ठा drm_i915_mocs_entry dg1_mocs_table[] = अणु
	/* Error */
	MOCS_ENTRY(0, 0, L3_0_सूचीECT),

	/* UC */
	MOCS_ENTRY(1, 0, L3_1_UC),

	/* Reserved */
	MOCS_ENTRY(2, 0, L3_0_सूचीECT),
	MOCS_ENTRY(3, 0, L3_0_सूचीECT),
	MOCS_ENTRY(4, 0, L3_0_सूचीECT),

	/* WB - L3 */
	MOCS_ENTRY(5, 0, L3_3_WB),
	/* WB - L3 50% */
	MOCS_ENTRY(6, 0, L3_ESC(1) | L3_SCC(1) | L3_3_WB),
	/* WB - L3 25% */
	MOCS_ENTRY(7, 0, L3_ESC(1) | L3_SCC(3) | L3_3_WB),
	/* WB - L3 12.5% */
	MOCS_ENTRY(8, 0, L3_ESC(1) | L3_SCC(7) | L3_3_WB),

	/* HDC:L1 + L3 */
	MOCS_ENTRY(48, 0, L3_3_WB),
	/* HDC:L1 */
	MOCS_ENTRY(49, 0, L3_1_UC),

	/* HW Reserved */
	MOCS_ENTRY(60, 0, L3_1_UC),
	MOCS_ENTRY(61, 0, L3_1_UC),
	MOCS_ENTRY(62, 0, L3_1_UC),
	MOCS_ENTRY(63, 0, L3_1_UC),
पूर्ण;

क्रमागत अणु
	HAS_GLOBAL_MOCS = BIT(0),
	HAS_ENGINE_MOCS = BIT(1),
	HAS_RENDER_L3CC = BIT(2),
पूर्ण;

अटल bool has_l3cc(स्थिर काष्ठा drm_i915_निजी *i915)
अणु
	वापस true;
पूर्ण

अटल bool has_global_mocs(स्थिर काष्ठा drm_i915_निजी *i915)
अणु
	वापस HAS_GLOBAL_MOCS_REGISTERS(i915);
पूर्ण

अटल bool has_mocs(स्थिर काष्ठा drm_i915_निजी *i915)
अणु
	वापस !IS_DGFX(i915);
पूर्ण

अटल अचिन्हित पूर्णांक get_mocs_settings(स्थिर काष्ठा drm_i915_निजी *i915,
				      काष्ठा drm_i915_mocs_table *table)
अणु
	अचिन्हित पूर्णांक flags;

	अगर (IS_DG1(i915)) अणु
		table->size = ARRAY_SIZE(dg1_mocs_table);
		table->table = dg1_mocs_table;
		table->n_entries = GEN9_NUM_MOCS_ENTRIES;
	पूर्ण अन्यथा अगर (INTEL_GEN(i915) >= 12) अणु
		table->size  = ARRAY_SIZE(tgl_mocs_table);
		table->table = tgl_mocs_table;
		table->n_entries = GEN9_NUM_MOCS_ENTRIES;
	पूर्ण अन्यथा अगर (IS_GEN(i915, 11)) अणु
		table->size  = ARRAY_SIZE(icl_mocs_table);
		table->table = icl_mocs_table;
		table->n_entries = GEN9_NUM_MOCS_ENTRIES;
	पूर्ण अन्यथा अगर (IS_GEN9_BC(i915) || IS_CANNONLAKE(i915)) अणु
		table->size  = ARRAY_SIZE(skl_mocs_table);
		table->n_entries = GEN9_NUM_MOCS_ENTRIES;
		table->table = skl_mocs_table;
	पूर्ण अन्यथा अगर (IS_GEN9_LP(i915)) अणु
		table->size  = ARRAY_SIZE(broxton_mocs_table);
		table->n_entries = GEN9_NUM_MOCS_ENTRIES;
		table->table = broxton_mocs_table;
	पूर्ण अन्यथा अणु
		drm_WARN_ONCE(&i915->drm, INTEL_GEN(i915) >= 9,
			      "Platform that should have a MOCS table does not.\n");
		वापस 0;
	पूर्ण

	अगर (GEM_DEBUG_WARN_ON(table->size > table->n_entries))
		वापस 0;

	/* WaDisableSkipCaching:skl,bxt,kbl,glk */
	अगर (IS_GEN(i915, 9)) अणु
		पूर्णांक i;

		क्रम (i = 0; i < table->size; i++)
			अगर (GEM_DEBUG_WARN_ON(table->table[i].l3cc_value &
					      (L3_ESC(1) | L3_SCC(0x7))))
				वापस 0;
	पूर्ण

	flags = 0;
	अगर (has_mocs(i915)) अणु
		अगर (has_global_mocs(i915))
			flags |= HAS_GLOBAL_MOCS;
		अन्यथा
			flags |= HAS_ENGINE_MOCS;
	पूर्ण
	अगर (has_l3cc(i915))
		flags |= HAS_RENDER_L3CC;

	वापस flags;
पूर्ण

/*
 * Get control_value from MOCS entry taking पूर्णांकo account when it's not used:
 * I915_MOCS_PTE's value is वापसed in this हाल.
 */
अटल u32 get_entry_control(स्थिर काष्ठा drm_i915_mocs_table *table,
			     अचिन्हित पूर्णांक index)
अणु
	अगर (index < table->size && table->table[index].used)
		वापस table->table[index].control_value;

	वापस table->table[I915_MOCS_PTE].control_value;
पूर्ण

#घोषणा क्रम_each_mocs(mocs, t, i) \
	क्रम (i = 0; \
	     i < (t)->n_entries ? (mocs = get_entry_control((t), i)), 1 : 0;\
	     i++)

अटल व्योम __init_mocs_table(काष्ठा पूर्णांकel_uncore *uncore,
			      स्थिर काष्ठा drm_i915_mocs_table *table,
			      u32 addr)
अणु
	अचिन्हित पूर्णांक i;
	u32 mocs;

	क्रम_each_mocs(mocs, table, i)
		पूर्णांकel_uncore_ग_लिखो_fw(uncore, _MMIO(addr + i * 4), mocs);
पूर्ण

अटल u32 mocs_offset(स्थिर काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	अटल स्थिर u32 offset[] = अणु
		[RCS0]  =  __GEN9_RCS0_MOCS0,
		[VCS0]  =  __GEN9_VCS0_MOCS0,
		[VCS1]  =  __GEN9_VCS1_MOCS0,
		[VECS0] =  __GEN9_VECS0_MOCS0,
		[BCS0]  =  __GEN9_BCS0_MOCS0,
		[VCS2]  = __GEN11_VCS2_MOCS0,
	पूर्ण;

	GEM_BUG_ON(engine->id >= ARRAY_SIZE(offset));
	वापस offset[engine->id];
पूर्ण

अटल व्योम init_mocs_table(काष्ठा पूर्णांकel_engine_cs *engine,
			    स्थिर काष्ठा drm_i915_mocs_table *table)
अणु
	__init_mocs_table(engine->uncore, table, mocs_offset(engine));
पूर्ण

/*
 * Get l3cc_value from MOCS entry taking पूर्णांकo account when it's not used:
 * I915_MOCS_PTE's value is वापसed in this हाल.
 */
अटल u16 get_entry_l3cc(स्थिर काष्ठा drm_i915_mocs_table *table,
			  अचिन्हित पूर्णांक index)
अणु
	अगर (index < table->size && table->table[index].used)
		वापस table->table[index].l3cc_value;

	वापस table->table[I915_MOCS_PTE].l3cc_value;
पूर्ण

अटल u32 l3cc_combine(u16 low, u16 high)
अणु
	वापस low | (u32)high << 16;
पूर्ण

#घोषणा क्रम_each_l3cc(l3cc, t, i) \
	क्रम (i = 0; \
	     i < ((t)->n_entries + 1) / 2 ? \
	     (l3cc = l3cc_combine(get_entry_l3cc((t), 2 * i), \
				  get_entry_l3cc((t), 2 * i + 1))), 1 : \
	     0; \
	     i++)

अटल व्योम init_l3cc_table(काष्ठा पूर्णांकel_engine_cs *engine,
			    स्थिर काष्ठा drm_i915_mocs_table *table)
अणु
	काष्ठा पूर्णांकel_uncore *uncore = engine->uncore;
	अचिन्हित पूर्णांक i;
	u32 l3cc;

	क्रम_each_l3cc(l3cc, table, i)
		पूर्णांकel_uncore_ग_लिखो_fw(uncore, GEN9_LNCFCMOCS(i), l3cc);
पूर्ण

व्योम पूर्णांकel_mocs_init_engine(काष्ठा पूर्णांकel_engine_cs *engine)
अणु
	काष्ठा drm_i915_mocs_table table;
	अचिन्हित पूर्णांक flags;

	/* Called under a blanket क्रमcewake */
	निश्चित_क्रमcewakes_active(engine->uncore, FORCEWAKE_ALL);

	flags = get_mocs_settings(engine->i915, &table);
	अगर (!flags)
		वापस;

	/* Platक्रमms with global MOCS करो not need per-engine initialization. */
	अगर (flags & HAS_ENGINE_MOCS)
		init_mocs_table(engine, &table);

	अगर (flags & HAS_RENDER_L3CC && engine->class == RENDER_CLASS)
		init_l3cc_table(engine, &table);
पूर्ण

अटल u32 global_mocs_offset(व्योम)
अणु
	वापस i915_mmio_reg_offset(GEN12_GLOBAL_MOCS(0));
पूर्ण

व्योम पूर्णांकel_mocs_init(काष्ठा पूर्णांकel_gt *gt)
अणु
	काष्ठा drm_i915_mocs_table table;
	अचिन्हित पूर्णांक flags;

	/*
	 * LLC and eDRAM control values are not applicable to dgfx
	 */
	flags = get_mocs_settings(gt->i915, &table);
	अगर (flags & HAS_GLOBAL_MOCS)
		__init_mocs_table(gt->uncore, &table, global_mocs_offset());
पूर्ण

#अगर IS_ENABLED(CONFIG_DRM_I915_SELFTEST)
#समावेश "selftest_mocs.c"
#पूर्ण_अगर
