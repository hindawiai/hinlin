<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2003, 04, 05 Ralf Baechle (ralf@linux-mips.org)
 * Copyright (C) 2007  Maciej W. Rozycki
 * Copyright (C) 2008  Thiemo Seufer
 * Copyright (C) 2012  MIPS Technologies, Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/smp.h>
#समावेश <linux/mm.h>
#समावेश <linux/proc_fs.h>

#समावेश <यंत्र/bugs.h>
#समावेश <यंत्र/cacheops.h>
#समावेश <यंत्र/cpu-type.h>
#समावेश <यंत्र/inst.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/page.h>
#समावेश <यंत्र/prefetch.h>
#समावेश <यंत्र/bootinfo.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/mmu_context.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/war.h>

#अगर_घोषित CONFIG_SIBYTE_DMA_PAGEOPS
#समावेश <यंत्र/sibyte/sb1250.h>
#समावेश <यंत्र/sibyte/sb1250_regs.h>
#समावेश <यंत्र/sibyte/sb1250_dma.h>
#पूर्ण_अगर

#समावेश <यंत्र/uयंत्र.h>

/* Registers used in the assembled routines. */
#घोषणा ZERO 0
#घोषणा AT 2
#घोषणा A0 4
#घोषणा A1 5
#घोषणा A2 6
#घोषणा T0 8
#घोषणा T1 9
#घोषणा T2 10
#घोषणा T3 11
#घोषणा T9 25
#घोषणा RA 31

/* Handle labels (which must be positive पूर्णांकegers). */
क्रमागत label_id अणु
	label_clear_nopref = 1,
	label_clear_pref,
	label_copy_nopref,
	label_copy_pref_both,
	label_copy_pref_store,
पूर्ण;

UASM_L_LA(_clear_nopref)
UASM_L_LA(_clear_pref)
UASM_L_LA(_copy_nopref)
UASM_L_LA(_copy_pref_both)
UASM_L_LA(_copy_pref_store)

/* We need one branch and thereक्रमe one relocation per target label. */
अटल काष्ठा uयंत्र_label labels[5];
अटल काष्ठा uयंत्र_reloc relocs[5];

#घोषणा cpu_is_r4600_v1_x()	((पढ़ो_c0_prid() & 0xfffffff0) == 0x00002010)
#घोषणा cpu_is_r4600_v2_x()	((पढ़ो_c0_prid() & 0xfffffff0) == 0x00002020)

/*
 * R6 has a limited offset of the pref inकाष्ठाion.
 * Skip it अगर the offset is more than 9 bits.
 */
#घोषणा _uयंत्र_i_pref(a, b, c, d)		\
करो अणु						\
	अगर (cpu_has_mips_r6) अणु			\
		अगर (c <= 0xff && c >= -0x100)	\
			uयंत्र_i_pref(a, b, c, d);\
	पूर्ण अन्यथा अणु				\
		uयंत्र_i_pref(a, b, c, d);	\
	पूर्ण					\
पूर्ण जबतक(0)

अटल पूर्णांक pref_bias_clear_store;
अटल पूर्णांक pref_bias_copy_load;
अटल पूर्णांक pref_bias_copy_store;

अटल u32 pref_src_mode;
अटल u32 pref_dst_mode;

अटल पूर्णांक clear_word_size;
अटल पूर्णांक copy_word_size;

अटल पूर्णांक half_clear_loop_size;
अटल पूर्णांक half_copy_loop_size;

अटल पूर्णांक cache_line_size;
#घोषणा cache_line_mask() (cache_line_size - 1)

अटल अंतरभूत व्योम
pg_addiu(u32 **buf, अचिन्हित पूर्णांक reg1, अचिन्हित पूर्णांक reg2, अचिन्हित पूर्णांक off)
अणु
	अगर (cpu_has_64bit_gp_regs && DADDI_WAR && r4k_daddiu_bug()) अणु
		अगर (off > 0x7fff) अणु
			uयंत्र_i_lui(buf, T9, uयंत्र_rel_hi(off));
			uयंत्र_i_addiu(buf, T9, T9, uयंत्र_rel_lo(off));
		पूर्ण अन्यथा
			uयंत्र_i_addiu(buf, T9, ZERO, off);
		uयंत्र_i_daddu(buf, reg1, reg2, T9);
	पूर्ण अन्यथा अणु
		अगर (off > 0x7fff) अणु
			uयंत्र_i_lui(buf, T9, uयंत्र_rel_hi(off));
			uयंत्र_i_addiu(buf, T9, T9, uयंत्र_rel_lo(off));
			UASM_i_ADDU(buf, reg1, reg2, T9);
		पूर्ण अन्यथा
			UASM_i_ADDIU(buf, reg1, reg2, off);
	पूर्ण
पूर्ण

अटल व्योम set_prefetch_parameters(व्योम)
अणु
	अगर (cpu_has_64bit_gp_regs || cpu_has_64bit_zero_reg)
		clear_word_size = 8;
	अन्यथा
		clear_word_size = 4;

	अगर (cpu_has_64bit_gp_regs)
		copy_word_size = 8;
	अन्यथा
		copy_word_size = 4;

	/*
	 * The pref's used here are using "streaming" hपूर्णांकs, which cause the
	 * copied data to be kicked out of the cache sooner.  A page copy often
	 * ends up copying a lot more data than is commonly used, so this seems
	 * to make sense in terms of reducing cache pollution, but I've no real
	 * perक्रमmance data to back this up.
	 */
	अगर (cpu_has_prefetch) अणु
		/*
		 * XXX: Most prefetch bias values in here are based on
		 * guesswork.
		 */
		cache_line_size = cpu_dcache_line_size();
		चयन (current_cpu_type()) अणु
		हाल CPU_R5500:
		हाल CPU_TX49XX:
			/* These processors only support the Pref_Load. */
			pref_bias_copy_load = 256;
			अवरोध;

		हाल CPU_R10000:
		हाल CPU_R12000:
		हाल CPU_R14000:
		हाल CPU_R16000:
			/*
			 * Those values have been experimentally tuned क्रम an
			 * Origin 200.
			 */
			pref_bias_clear_store = 512;
			pref_bias_copy_load = 256;
			pref_bias_copy_store = 256;
			pref_src_mode = Pref_LoadStreamed;
			pref_dst_mode = Pref_StoreStreamed;
			अवरोध;

		हाल CPU_SB1:
		हाल CPU_SB1A:
			pref_bias_clear_store = 128;
			pref_bias_copy_load = 128;
			pref_bias_copy_store = 128;
			/*
			 * SB1 pass1 Pref_LoadStreamed/Pref_StoreStreamed
			 * hपूर्णांकs are broken.
			 */
			अगर (current_cpu_type() == CPU_SB1 &&
			    (current_cpu_data.processor_id & 0xff) < 0x02) अणु
				pref_src_mode = Pref_Load;
				pref_dst_mode = Pref_Store;
			पूर्ण अन्यथा अणु
				pref_src_mode = Pref_LoadStreamed;
				pref_dst_mode = Pref_StoreStreamed;
			पूर्ण
			अवरोध;

		हाल CPU_LOONGSON64:
			/* Loongson-3 only support the Pref_Load/Pref_Store. */
			pref_bias_clear_store = 128;
			pref_bias_copy_load = 128;
			pref_bias_copy_store = 128;
			pref_src_mode = Pref_Load;
			pref_dst_mode = Pref_Store;
			अवरोध;

		शेष:
			pref_bias_clear_store = 128;
			pref_bias_copy_load = 256;
			pref_bias_copy_store = 128;
			pref_src_mode = Pref_LoadStreamed;
			अगर (cpu_has_mips_r6)
				/*
				 * Bit 30 (Pref_PrepareForStore) has been
				 * हटाओd from MIPS R6. Use bit 5
				 * (Pref_StoreStreamed).
				 */
				pref_dst_mode = Pref_StoreStreamed;
			अन्यथा
				pref_dst_mode = Pref_PrepareForStore;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (cpu_has_cache_cdex_s)
			cache_line_size = cpu_scache_line_size();
		अन्यथा अगर (cpu_has_cache_cdex_p)
			cache_line_size = cpu_dcache_line_size();
	पूर्ण
	/*
	 * Too much unrolling will overflow the available space in
	 * clear_space_array / copy_page_array.
	 */
	half_clear_loop_size = min(16 * clear_word_size,
				   max(cache_line_size >> 1,
				       4 * clear_word_size));
	half_copy_loop_size = min(16 * copy_word_size,
				  max(cache_line_size >> 1,
				      4 * copy_word_size));
पूर्ण

अटल व्योम build_clear_store(u32 **buf, पूर्णांक off)
अणु
	अगर (cpu_has_64bit_gp_regs || cpu_has_64bit_zero_reg) अणु
		uयंत्र_i_sd(buf, ZERO, off, A0);
	पूर्ण अन्यथा अणु
		uयंत्र_i_sw(buf, ZERO, off, A0);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम build_clear_pref(u32 **buf, पूर्णांक off)
अणु
	अगर (off & cache_line_mask())
		वापस;

	अगर (pref_bias_clear_store) अणु
		_uयंत्र_i_pref(buf, pref_dst_mode, pref_bias_clear_store + off,
			    A0);
	पूर्ण अन्यथा अगर (cache_line_size == (half_clear_loop_size << 1)) अणु
		अगर (cpu_has_cache_cdex_s) अणु
			uयंत्र_i_cache(buf, Create_Dirty_Excl_SD, off, A0);
		पूर्ण अन्यथा अगर (cpu_has_cache_cdex_p) अणु
			अगर (IS_ENABLED(CONFIG_WAR_R4600_V1_HIT_CACHEOP) &&
			    cpu_is_r4600_v1_x()) अणु
				uयंत्र_i_nop(buf);
				uयंत्र_i_nop(buf);
				uयंत्र_i_nop(buf);
				uयंत्र_i_nop(buf);
			पूर्ण

			अगर (IS_ENABLED(CONFIG_WAR_R4600_V2_HIT_CACHEOP) &&
			    cpu_is_r4600_v2_x())
				uयंत्र_i_lw(buf, ZERO, ZERO, AT);

			uयंत्र_i_cache(buf, Create_Dirty_Excl_D, off, A0);
		पूर्ण
	पूर्ण
पूर्ण

बाह्य u32 __clear_page_start;
बाह्य u32 __clear_page_end;
बाह्य u32 __copy_page_start;
बाह्य u32 __copy_page_end;

व्योम build_clear_page(व्योम)
अणु
	पूर्णांक off;
	u32 *buf = &__clear_page_start;
	काष्ठा uयंत्र_label *l = labels;
	काष्ठा uयंत्र_reloc *r = relocs;
	पूर्णांक i;
	अटल atomic_t run_once = ATOMIC_INIT(0);

	अगर (atomic_xchg(&run_once, 1)) अणु
		वापस;
	पूर्ण

	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));

	set_prefetch_parameters();

	/*
	 * This algorithm makes the following assumptions:
	 *   - The prefetch bias is a multiple of 2 words.
	 *   - The prefetch bias is less than one page.
	 */
	BUG_ON(pref_bias_clear_store % (2 * clear_word_size));
	BUG_ON(PAGE_SIZE < pref_bias_clear_store);

	off = PAGE_SIZE - pref_bias_clear_store;
	अगर (off > 0xffff || !pref_bias_clear_store)
		pg_addiu(&buf, A2, A0, off);
	अन्यथा
		uयंत्र_i_ori(&buf, A2, A0, off);

	अगर (IS_ENABLED(CONFIG_WAR_R4600_V2_HIT_CACHEOP) && cpu_is_r4600_v2_x())
		uयंत्र_i_lui(&buf, AT, uयंत्र_rel_hi(0xa0000000));

	off = cache_line_size ? min(8, pref_bias_clear_store / cache_line_size)
				* cache_line_size : 0;
	जबतक (off) अणु
		build_clear_pref(&buf, -off);
		off -= cache_line_size;
	पूर्ण
	uयंत्र_l_clear_pref(&l, buf);
	करो अणु
		build_clear_pref(&buf, off);
		build_clear_store(&buf, off);
		off += clear_word_size;
	पूर्ण जबतक (off < half_clear_loop_size);
	pg_addiu(&buf, A0, A0, 2 * off);
	off = -off;
	करो अणु
		build_clear_pref(&buf, off);
		अगर (off == -clear_word_size)
			uयंत्र_il_bne(&buf, &r, A0, A2, label_clear_pref);
		build_clear_store(&buf, off);
		off += clear_word_size;
	पूर्ण जबतक (off < 0);

	अगर (pref_bias_clear_store) अणु
		pg_addiu(&buf, A2, A0, pref_bias_clear_store);
		uयंत्र_l_clear_nopref(&l, buf);
		off = 0;
		करो अणु
			build_clear_store(&buf, off);
			off += clear_word_size;
		पूर्ण जबतक (off < half_clear_loop_size);
		pg_addiu(&buf, A0, A0, 2 * off);
		off = -off;
		करो अणु
			अगर (off == -clear_word_size)
				uयंत्र_il_bne(&buf, &r, A0, A2,
					    label_clear_nopref);
			build_clear_store(&buf, off);
			off += clear_word_size;
		पूर्ण जबतक (off < 0);
	पूर्ण

	uयंत्र_i_jr(&buf, RA);
	uयंत्र_i_nop(&buf);

	BUG_ON(buf > &__clear_page_end);

	uयंत्र_resolve_relocs(relocs, labels);

	pr_debug("Synthesized clear page handler (%u instructions).\n",
		 (u32)(buf - &__clear_page_start));

	pr_debug("\t.set push\n");
	pr_debug("\t.set noreorder\n");
	क्रम (i = 0; i < (buf - &__clear_page_start); i++)
		pr_debug("\t.word 0x%08x\n", (&__clear_page_start)[i]);
	pr_debug("\t.set pop\n");
पूर्ण

अटल व्योम build_copy_load(u32 **buf, पूर्णांक reg, पूर्णांक off)
अणु
	अगर (cpu_has_64bit_gp_regs) अणु
		uयंत्र_i_ld(buf, reg, off, A1);
	पूर्ण अन्यथा अणु
		uयंत्र_i_lw(buf, reg, off, A1);
	पूर्ण
पूर्ण

अटल व्योम build_copy_store(u32 **buf, पूर्णांक reg, पूर्णांक off)
अणु
	अगर (cpu_has_64bit_gp_regs) अणु
		uयंत्र_i_sd(buf, reg, off, A0);
	पूर्ण अन्यथा अणु
		uयंत्र_i_sw(buf, reg, off, A0);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम build_copy_load_pref(u32 **buf, पूर्णांक off)
अणु
	अगर (off & cache_line_mask())
		वापस;

	अगर (pref_bias_copy_load)
		_uयंत्र_i_pref(buf, pref_src_mode, pref_bias_copy_load + off, A1);
पूर्ण

अटल अंतरभूत व्योम build_copy_store_pref(u32 **buf, पूर्णांक off)
अणु
	अगर (off & cache_line_mask())
		वापस;

	अगर (pref_bias_copy_store) अणु
		_uयंत्र_i_pref(buf, pref_dst_mode, pref_bias_copy_store + off,
			    A0);
	पूर्ण अन्यथा अगर (cache_line_size == (half_copy_loop_size << 1)) अणु
		अगर (cpu_has_cache_cdex_s) अणु
			uयंत्र_i_cache(buf, Create_Dirty_Excl_SD, off, A0);
		पूर्ण अन्यथा अगर (cpu_has_cache_cdex_p) अणु
			अगर (IS_ENABLED(CONFIG_WAR_R4600_V1_HIT_CACHEOP) &&
			    cpu_is_r4600_v1_x()) अणु
				uयंत्र_i_nop(buf);
				uयंत्र_i_nop(buf);
				uयंत्र_i_nop(buf);
				uयंत्र_i_nop(buf);
			पूर्ण

			अगर (IS_ENABLED(CONFIG_WAR_R4600_V2_HIT_CACHEOP) &&
			    cpu_is_r4600_v2_x())
				uयंत्र_i_lw(buf, ZERO, ZERO, AT);

			uयंत्र_i_cache(buf, Create_Dirty_Excl_D, off, A0);
		पूर्ण
	पूर्ण
पूर्ण

व्योम build_copy_page(व्योम)
अणु
	पूर्णांक off;
	u32 *buf = &__copy_page_start;
	काष्ठा uयंत्र_label *l = labels;
	काष्ठा uयंत्र_reloc *r = relocs;
	पूर्णांक i;
	अटल atomic_t run_once = ATOMIC_INIT(0);

	अगर (atomic_xchg(&run_once, 1)) अणु
		वापस;
	पूर्ण

	स_रखो(labels, 0, माप(labels));
	स_रखो(relocs, 0, माप(relocs));

	set_prefetch_parameters();

	/*
	 * This algorithm makes the following assumptions:
	 *   - All prefetch biases are multiples of 8 words.
	 *   - The prefetch biases are less than one page.
	 *   - The store prefetch bias isn't greater than the load
	 *     prefetch bias.
	 */
	BUG_ON(pref_bias_copy_load % (8 * copy_word_size));
	BUG_ON(pref_bias_copy_store % (8 * copy_word_size));
	BUG_ON(PAGE_SIZE < pref_bias_copy_load);
	BUG_ON(pref_bias_copy_store > pref_bias_copy_load);

	off = PAGE_SIZE - pref_bias_copy_load;
	अगर (off > 0xffff || !pref_bias_copy_load)
		pg_addiu(&buf, A2, A0, off);
	अन्यथा
		uयंत्र_i_ori(&buf, A2, A0, off);

	अगर (IS_ENABLED(CONFIG_WAR_R4600_V2_HIT_CACHEOP) && cpu_is_r4600_v2_x())
		uयंत्र_i_lui(&buf, AT, uयंत्र_rel_hi(0xa0000000));

	off = cache_line_size ? min(8, pref_bias_copy_load / cache_line_size) *
				cache_line_size : 0;
	जबतक (off) अणु
		build_copy_load_pref(&buf, -off);
		off -= cache_line_size;
	पूर्ण
	off = cache_line_size ? min(8, pref_bias_copy_store / cache_line_size) *
				cache_line_size : 0;
	जबतक (off) अणु
		build_copy_store_pref(&buf, -off);
		off -= cache_line_size;
	पूर्ण
	uयंत्र_l_copy_pref_both(&l, buf);
	करो अणु
		build_copy_load_pref(&buf, off);
		build_copy_load(&buf, T0, off);
		build_copy_load_pref(&buf, off + copy_word_size);
		build_copy_load(&buf, T1, off + copy_word_size);
		build_copy_load_pref(&buf, off + 2 * copy_word_size);
		build_copy_load(&buf, T2, off + 2 * copy_word_size);
		build_copy_load_pref(&buf, off + 3 * copy_word_size);
		build_copy_load(&buf, T3, off + 3 * copy_word_size);
		build_copy_store_pref(&buf, off);
		build_copy_store(&buf, T0, off);
		build_copy_store_pref(&buf, off + copy_word_size);
		build_copy_store(&buf, T1, off + copy_word_size);
		build_copy_store_pref(&buf, off + 2 * copy_word_size);
		build_copy_store(&buf, T2, off + 2 * copy_word_size);
		build_copy_store_pref(&buf, off + 3 * copy_word_size);
		build_copy_store(&buf, T3, off + 3 * copy_word_size);
		off += 4 * copy_word_size;
	पूर्ण जबतक (off < half_copy_loop_size);
	pg_addiu(&buf, A1, A1, 2 * off);
	pg_addiu(&buf, A0, A0, 2 * off);
	off = -off;
	करो अणु
		build_copy_load_pref(&buf, off);
		build_copy_load(&buf, T0, off);
		build_copy_load_pref(&buf, off + copy_word_size);
		build_copy_load(&buf, T1, off + copy_word_size);
		build_copy_load_pref(&buf, off + 2 * copy_word_size);
		build_copy_load(&buf, T2, off + 2 * copy_word_size);
		build_copy_load_pref(&buf, off + 3 * copy_word_size);
		build_copy_load(&buf, T3, off + 3 * copy_word_size);
		build_copy_store_pref(&buf, off);
		build_copy_store(&buf, T0, off);
		build_copy_store_pref(&buf, off + copy_word_size);
		build_copy_store(&buf, T1, off + copy_word_size);
		build_copy_store_pref(&buf, off + 2 * copy_word_size);
		build_copy_store(&buf, T2, off + 2 * copy_word_size);
		build_copy_store_pref(&buf, off + 3 * copy_word_size);
		अगर (off == -(4 * copy_word_size))
			uयंत्र_il_bne(&buf, &r, A2, A0, label_copy_pref_both);
		build_copy_store(&buf, T3, off + 3 * copy_word_size);
		off += 4 * copy_word_size;
	पूर्ण जबतक (off < 0);

	अगर (pref_bias_copy_load - pref_bias_copy_store) अणु
		pg_addiu(&buf, A2, A0,
			 pref_bias_copy_load - pref_bias_copy_store);
		uयंत्र_l_copy_pref_store(&l, buf);
		off = 0;
		करो अणु
			build_copy_load(&buf, T0, off);
			build_copy_load(&buf, T1, off + copy_word_size);
			build_copy_load(&buf, T2, off + 2 * copy_word_size);
			build_copy_load(&buf, T3, off + 3 * copy_word_size);
			build_copy_store_pref(&buf, off);
			build_copy_store(&buf, T0, off);
			build_copy_store_pref(&buf, off + copy_word_size);
			build_copy_store(&buf, T1, off + copy_word_size);
			build_copy_store_pref(&buf, off + 2 * copy_word_size);
			build_copy_store(&buf, T2, off + 2 * copy_word_size);
			build_copy_store_pref(&buf, off + 3 * copy_word_size);
			build_copy_store(&buf, T3, off + 3 * copy_word_size);
			off += 4 * copy_word_size;
		पूर्ण जबतक (off < half_copy_loop_size);
		pg_addiu(&buf, A1, A1, 2 * off);
		pg_addiu(&buf, A0, A0, 2 * off);
		off = -off;
		करो अणु
			build_copy_load(&buf, T0, off);
			build_copy_load(&buf, T1, off + copy_word_size);
			build_copy_load(&buf, T2, off + 2 * copy_word_size);
			build_copy_load(&buf, T3, off + 3 * copy_word_size);
			build_copy_store_pref(&buf, off);
			build_copy_store(&buf, T0, off);
			build_copy_store_pref(&buf, off + copy_word_size);
			build_copy_store(&buf, T1, off + copy_word_size);
			build_copy_store_pref(&buf, off + 2 * copy_word_size);
			build_copy_store(&buf, T2, off + 2 * copy_word_size);
			build_copy_store_pref(&buf, off + 3 * copy_word_size);
			अगर (off == -(4 * copy_word_size))
				uयंत्र_il_bne(&buf, &r, A2, A0,
					    label_copy_pref_store);
			build_copy_store(&buf, T3, off + 3 * copy_word_size);
			off += 4 * copy_word_size;
		पूर्ण जबतक (off < 0);
	पूर्ण

	अगर (pref_bias_copy_store) अणु
		pg_addiu(&buf, A2, A0, pref_bias_copy_store);
		uयंत्र_l_copy_nopref(&l, buf);
		off = 0;
		करो अणु
			build_copy_load(&buf, T0, off);
			build_copy_load(&buf, T1, off + copy_word_size);
			build_copy_load(&buf, T2, off + 2 * copy_word_size);
			build_copy_load(&buf, T3, off + 3 * copy_word_size);
			build_copy_store(&buf, T0, off);
			build_copy_store(&buf, T1, off + copy_word_size);
			build_copy_store(&buf, T2, off + 2 * copy_word_size);
			build_copy_store(&buf, T3, off + 3 * copy_word_size);
			off += 4 * copy_word_size;
		पूर्ण जबतक (off < half_copy_loop_size);
		pg_addiu(&buf, A1, A1, 2 * off);
		pg_addiu(&buf, A0, A0, 2 * off);
		off = -off;
		करो अणु
			build_copy_load(&buf, T0, off);
			build_copy_load(&buf, T1, off + copy_word_size);
			build_copy_load(&buf, T2, off + 2 * copy_word_size);
			build_copy_load(&buf, T3, off + 3 * copy_word_size);
			build_copy_store(&buf, T0, off);
			build_copy_store(&buf, T1, off + copy_word_size);
			build_copy_store(&buf, T2, off + 2 * copy_word_size);
			अगर (off == -(4 * copy_word_size))
				uयंत्र_il_bne(&buf, &r, A2, A0,
					    label_copy_nopref);
			build_copy_store(&buf, T3, off + 3 * copy_word_size);
			off += 4 * copy_word_size;
		पूर्ण जबतक (off < 0);
	पूर्ण

	uयंत्र_i_jr(&buf, RA);
	uयंत्र_i_nop(&buf);

	BUG_ON(buf > &__copy_page_end);

	uयंत्र_resolve_relocs(relocs, labels);

	pr_debug("Synthesized copy page handler (%u instructions).\n",
		 (u32)(buf - &__copy_page_start));

	pr_debug("\t.set push\n");
	pr_debug("\t.set noreorder\n");
	क्रम (i = 0; i < (buf - &__copy_page_start); i++)
		pr_debug("\t.word 0x%08x\n", (&__copy_page_start)[i]);
	pr_debug("\t.set pop\n");
पूर्ण

#अगर_घोषित CONFIG_SIBYTE_DMA_PAGEOPS
बाह्य व्योम clear_page_cpu(व्योम *page);
बाह्य व्योम copy_page_cpu(व्योम *to, व्योम *from);

/*
 * Pad descriptors to cacheline, since each is exclusively owned by a
 * particular CPU.
 */
काष्ठा dmadscr अणु
	u64 dscr_a;
	u64 dscr_b;
	u64 pad_a;
	u64 pad_b;
पूर्ण ____cacheline_aligned_in_smp page_descr[DM_NUM_CHANNELS];

व्योम clear_page(व्योम *page)
अणु
	u64 to_phys = CPHYSADDR((अचिन्हित दीर्घ)page);
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	/* अगर the page is not in KSEG0, use old way */
	अगर ((दीर्घ)KSEGX((अचिन्हित दीर्घ)page) != (दीर्घ)CKSEG0)
		वापस clear_page_cpu(page);

	page_descr[cpu].dscr_a = to_phys | M_DM_DSCRA_ZERO_MEM |
				 M_DM_DSCRA_L2C_DEST | M_DM_DSCRA_INTERRUPT;
	page_descr[cpu].dscr_b = V_DM_DSCRB_SRC_LENGTH(PAGE_SIZE);
	__raw_ग_लिखोq(1, IOADDR(A_DM_REGISTER(cpu, R_DM_DSCR_COUNT)));

	/*
	 * Don't really want to do it this way, but there's no
	 * reliable way to delay completion detection.
	 */
	जबतक (!(__raw_पढ़ोq(IOADDR(A_DM_REGISTER(cpu, R_DM_DSCR_BASE_DEBUG)))
		 & M_DM_DSCR_BASE_INTERRUPT))
		;
	__raw_पढ़ोq(IOADDR(A_DM_REGISTER(cpu, R_DM_DSCR_BASE)));
पूर्ण
EXPORT_SYMBOL(clear_page);

व्योम copy_page(व्योम *to, व्योम *from)
अणु
	u64 from_phys = CPHYSADDR((अचिन्हित दीर्घ)from);
	u64 to_phys = CPHYSADDR((अचिन्हित दीर्घ)to);
	अचिन्हित पूर्णांक cpu = smp_processor_id();

	/* अगर any page is not in KSEG0, use old way */
	अगर ((दीर्घ)KSEGX((अचिन्हित दीर्घ)to) != (दीर्घ)CKSEG0
	    || (दीर्घ)KSEGX((अचिन्हित दीर्घ)from) != (दीर्घ)CKSEG0)
		वापस copy_page_cpu(to, from);

	page_descr[cpu].dscr_a = to_phys | M_DM_DSCRA_L2C_DEST |
				 M_DM_DSCRA_INTERRUPT;
	page_descr[cpu].dscr_b = from_phys | V_DM_DSCRB_SRC_LENGTH(PAGE_SIZE);
	__raw_ग_लिखोq(1, IOADDR(A_DM_REGISTER(cpu, R_DM_DSCR_COUNT)));

	/*
	 * Don't really want to do it this way, but there's no
	 * reliable way to delay completion detection.
	 */
	जबतक (!(__raw_पढ़ोq(IOADDR(A_DM_REGISTER(cpu, R_DM_DSCR_BASE_DEBUG)))
		 & M_DM_DSCR_BASE_INTERRUPT))
		;
	__raw_पढ़ोq(IOADDR(A_DM_REGISTER(cpu, R_DM_DSCR_BASE)));
पूर्ण
EXPORT_SYMBOL(copy_page);

#पूर्ण_अगर /* CONFIG_SIBYTE_DMA_PAGEOPS */
