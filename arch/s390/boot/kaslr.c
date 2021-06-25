<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright IBM Corp. 2019
 */
#समावेश <linux/pgtable.h>
#समावेश <यंत्र/mem_detect.h>
#समावेश <यंत्र/cpacf.h>
#समावेश <यंत्र/समयx.h>
#समावेश <यंत्र/sclp.h>
#समावेश <यंत्र/kasan.h>
#समावेश "compressed/decompressor.h"
#समावेश "boot.h"

#घोषणा PRNG_MODE_TDES	 1
#घोषणा PRNG_MODE_SHA512 2
#घोषणा PRNG_MODE_TRNG	 3

काष्ठा prno_parm अणु
	u32 res;
	u32 reseed_counter;
	u64 stream_bytes;
	u8  V[112];
	u8  C[112];
पूर्ण;

काष्ठा prng_parm अणु
	u8  parm_block[32];
	u32 reseed_counter;
	u64 byte_counter;
पूर्ण;

अटल पूर्णांक check_prng(व्योम)
अणु
	अगर (!cpacf_query_func(CPACF_KMC, CPACF_KMC_PRNG)) अणु
		sclp_early_prपूर्णांकk("KASLR disabled: CPU has no PRNG\n");
		वापस 0;
	पूर्ण
	अगर (cpacf_query_func(CPACF_PRNO, CPACF_PRNO_TRNG))
		वापस PRNG_MODE_TRNG;
	अगर (cpacf_query_func(CPACF_PRNO, CPACF_PRNO_SHA512_DRNG_GEN))
		वापस PRNG_MODE_SHA512;
	अन्यथा
		वापस PRNG_MODE_TDES;
पूर्ण

अटल पूर्णांक get_अक्रमom(अचिन्हित दीर्घ limit, अचिन्हित दीर्घ *value)
अणु
	काष्ठा prng_parm prng = अणु
		/* initial parameter block क्रम tdes mode, copied from libica */
		.parm_block = अणु
			0x0F, 0x2B, 0x8E, 0x63, 0x8C, 0x8E, 0xD2, 0x52,
			0x64, 0xB7, 0xA0, 0x7B, 0x75, 0x28, 0xB8, 0xF4,
			0x75, 0x5F, 0xD2, 0xA6, 0x8D, 0x97, 0x11, 0xFF,
			0x49, 0xD8, 0x23, 0xF3, 0x7E, 0x21, 0xEC, 0xA0
		पूर्ण,
	पूर्ण;
	अचिन्हित दीर्घ seed, अक्रमom;
	काष्ठा prno_parm prno;
	__u64 entropy[4];
	पूर्णांक mode, i;

	mode = check_prng();
	seed = get_tod_घड़ी_fast();
	चयन (mode) अणु
	हाल PRNG_MODE_TRNG:
		cpacf_trng(शून्य, 0, (u8 *) &अक्रमom, माप(अक्रमom));
		अवरोध;
	हाल PRNG_MODE_SHA512:
		cpacf_prno(CPACF_PRNO_SHA512_DRNG_SEED, &prno, शून्य, 0,
			   (u8 *) &seed, माप(seed));
		cpacf_prno(CPACF_PRNO_SHA512_DRNG_GEN, &prno, (u8 *) &अक्रमom,
			   माप(अक्रमom), शून्य, 0);
		अवरोध;
	हाल PRNG_MODE_TDES:
		/* add entropy */
		*(अचिन्हित दीर्घ *) prng.parm_block ^= seed;
		क्रम (i = 0; i < 16; i++) अणु
			cpacf_kmc(CPACF_KMC_PRNG, prng.parm_block,
				  (u8 *) entropy, (u8 *) entropy,
				  माप(entropy));
			स_नकल(prng.parm_block, entropy, माप(entropy));
		पूर्ण
		अक्रमom = seed;
		cpacf_kmc(CPACF_KMC_PRNG, prng.parm_block, (u8 *) &अक्रमom,
			  (u8 *) &अक्रमom, माप(अक्रमom));
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण
	*value = अक्रमom % limit;
	वापस 0;
पूर्ण

/*
 * To अक्रमomize kernel base address we have to consider several facts:
 * 1. physical online memory might not be continuous and have holes. mem_detect
 *    info contains list of online memory ranges we should consider.
 * 2. we have several memory regions which are occupied and we should not
 *    overlap and destroy them. Currently safe_addr tells us the border below
 *    which all those occupied regions are. We are safe to use anything above
 *    safe_addr.
 * 3. the upper limit might apply as well, even अगर memory above that limit is
 *    online. Currently those limitations are:
 *    3.1. Limit set by "mem=" kernel command line option
 *    3.2. memory reserved at the end क्रम kasan initialization.
 * 4. kernel base address must be aligned to THREAD_SIZE (kernel stack size).
 *    Which is required क्रम CONFIG_CHECK_STACK. Currently THREAD_SIZE is 4 pages
 *    (16 pages when the kernel is built with kasan enabled)
 * Assumptions:
 * 1. kernel size (including .bss size) and upper memory limit are page aligned.
 * 2. mem_detect memory region start is THREAD_SIZE aligned / end is PAGE_SIZE
 *    aligned (in practice memory configurations granularity on z/VM and LPAR
 *    is 1mb).
 *
 * To guarantee unअगरorm distribution of kernel base address among all suitable
 * addresses we generate अक्रमom value just once. For that we need to build a
 * continuous range in which every value would be suitable. We can build this
 * range by simply counting all suitable addresses (let's call them positions)
 * which would be valid as kernel base address. To count positions we iterate
 * over online memory ranges. For each range which is big enough क्रम the
 * kernel image we count all suitable addresses we can put the kernel image at
 * that is
 * (end - start - kernel_size) / THREAD_SIZE + 1
 * Two functions count_valid_kernel_positions and position_to_address help
 * to count positions in memory range given and then convert position back
 * to address.
 */
अटल अचिन्हित दीर्घ count_valid_kernel_positions(अचिन्हित दीर्घ kernel_size,
						  अचिन्हित दीर्घ _min,
						  अचिन्हित दीर्घ _max)
अणु
	अचिन्हित दीर्घ start, end, pos = 0;
	पूर्णांक i;

	क्रम_each_mem_detect_block(i, &start, &end) अणु
		अगर (_min >= end)
			जारी;
		अगर (start >= _max)
			अवरोध;
		start = max(_min, start);
		end = min(_max, end);
		अगर (end - start < kernel_size)
			जारी;
		pos += (end - start - kernel_size) / THREAD_SIZE + 1;
	पूर्ण

	वापस pos;
पूर्ण

अटल अचिन्हित दीर्घ position_to_address(अचिन्हित दीर्घ pos, अचिन्हित दीर्घ kernel_size,
				 अचिन्हित दीर्घ _min, अचिन्हित दीर्घ _max)
अणु
	अचिन्हित दीर्घ start, end;
	पूर्णांक i;

	क्रम_each_mem_detect_block(i, &start, &end) अणु
		अगर (_min >= end)
			जारी;
		अगर (start >= _max)
			अवरोध;
		start = max(_min, start);
		end = min(_max, end);
		अगर (end - start < kernel_size)
			जारी;
		अगर ((end - start - kernel_size) / THREAD_SIZE + 1 >= pos)
			वापस start + (pos - 1) * THREAD_SIZE;
		pos -= (end - start - kernel_size) / THREAD_SIZE + 1;
	पूर्ण

	वापस 0;
पूर्ण

अचिन्हित दीर्घ get_अक्रमom_base(अचिन्हित दीर्घ safe_addr)
अणु
	अचिन्हित दीर्घ memory_limit = get_mem_detect_end();
	अचिन्हित दीर्घ base_pos, max_pos, kernel_size;
	अचिन्हित दीर्घ kasan_needs;
	पूर्णांक i;

	memory_limit = min(memory_limit, ident_map_size);

	/*
	 * Aव्योम putting kernel in the end of physical memory
	 * which kasan will use क्रम shaकरोw memory and early pgtable
	 * mapping allocations.
	 */
	memory_limit -= kasan_estimate_memory_needs(memory_limit);

	अगर (IS_ENABLED(CONFIG_BLK_DEV_INITRD) && INITRD_START && INITRD_SIZE) अणु
		अगर (safe_addr < INITRD_START + INITRD_SIZE)
			safe_addr = INITRD_START + INITRD_SIZE;
	पूर्ण
	safe_addr = ALIGN(safe_addr, THREAD_SIZE);

	kernel_size = vmlinux.image_size + vmlinux.bss_size;
	अगर (safe_addr + kernel_size > memory_limit)
		वापस 0;

	max_pos = count_valid_kernel_positions(kernel_size, safe_addr, memory_limit);
	अगर (!max_pos) अणु
		sclp_early_prपूर्णांकk("KASLR disabled: not enough memory\n");
		वापस 0;
	पूर्ण

	/* we need a value in the range [1, base_pos] inclusive */
	अगर (get_अक्रमom(max_pos, &base_pos))
		वापस 0;
	वापस position_to_address(base_pos + 1, kernel_size, safe_addr, memory_limit);
पूर्ण
