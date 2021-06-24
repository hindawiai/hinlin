<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * MIPS SPRAM support
 *
 * Copyright (C) 2007, 2008 MIPS Technologies, Inc.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/मानकघोष.स>

#समावेश <यंत्र/fpu.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/r4kcache.h>
#समावेश <यंत्र/hazards.h>

/*
 * These definitions are correct क्रम the 24K/34K/74K SPRAM sample
 * implementation. The 4KS पूर्णांकerpreted the tags dअगरferently...
 */
#घोषणा SPRAM_TAG0_ENABLE	0x00000080
#घोषणा SPRAM_TAG0_PA_MASK	0xfffff000
#घोषणा SPRAM_TAG1_SIZE_MASK	0xfffff000

#घोषणा SPRAM_TAG_STRIDE	8

#घोषणा ERRCTL_SPRAM		(1 << 28)

/* errctl access */
#घोषणा पढ़ो_c0_errctl(x) पढ़ो_c0_ecc(x)
#घोषणा ग_लिखो_c0_errctl(x) ग_लिखो_c0_ecc(x)

/*
 * Dअगरferent semantics to the set_c0_* function built by __BUILD_SET_C0
 */
अटल अचिन्हित पूर्णांक bis_c0_errctl(अचिन्हित पूर्णांक set)
अणु
	अचिन्हित पूर्णांक res;
	res = पढ़ो_c0_errctl();
	ग_लिखो_c0_errctl(res | set);
	वापस res;
पूर्ण

अटल व्योम ispram_store_tag(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक errctl;

	/* enable SPRAM tag access */
	errctl = bis_c0_errctl(ERRCTL_SPRAM);
	ehb();

	ग_लिखो_c0_taglo(data);
	ehb();

	cache_op(Index_Store_Tag_I, CKSEG0|offset);
	ehb();

	ग_लिखो_c0_errctl(errctl);
	ehb();
पूर्ण


अटल अचिन्हित पूर्णांक ispram_load_tag(अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक data;
	अचिन्हित पूर्णांक errctl;

	/* enable SPRAM tag access */
	errctl = bis_c0_errctl(ERRCTL_SPRAM);
	ehb();
	cache_op(Index_Load_Tag_I, CKSEG0 | offset);
	ehb();
	data = पढ़ो_c0_taglo();
	ehb();
	ग_लिखो_c0_errctl(errctl);
	ehb();

	वापस data;
पूर्ण

अटल व्योम dspram_store_tag(अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक data)
अणु
	अचिन्हित पूर्णांक errctl;

	/* enable SPRAM tag access */
	errctl = bis_c0_errctl(ERRCTL_SPRAM);
	ehb();
	ग_लिखो_c0_dtaglo(data);
	ehb();
	cache_op(Index_Store_Tag_D, CKSEG0 | offset);
	ehb();
	ग_लिखो_c0_errctl(errctl);
	ehb();
पूर्ण


अटल अचिन्हित पूर्णांक dspram_load_tag(अचिन्हित पूर्णांक offset)
अणु
	अचिन्हित पूर्णांक data;
	अचिन्हित पूर्णांक errctl;

	errctl = bis_c0_errctl(ERRCTL_SPRAM);
	ehb();
	cache_op(Index_Load_Tag_D, CKSEG0 | offset);
	ehb();
	data = पढ़ो_c0_dtaglo();
	ehb();
	ग_लिखो_c0_errctl(errctl);
	ehb();

	वापस data;
पूर्ण

अटल व्योम probe_spram(अक्षर *type,
	    अचिन्हित पूर्णांक base,
	    अचिन्हित पूर्णांक (*पढ़ो)(अचिन्हित पूर्णांक),
	    व्योम (*ग_लिखो)(अचिन्हित पूर्णांक, अचिन्हित पूर्णांक))
अणु
	अचिन्हित पूर्णांक firstsize = 0, lastsize = 0;
	अचिन्हित पूर्णांक firstpa = 0, lastpa = 0, pa = 0;
	अचिन्हित पूर्णांक offset = 0;
	अचिन्हित पूर्णांक size, tag0, tag1;
	अचिन्हित पूर्णांक enabled;
	पूर्णांक i;

	/*
	 * The limit is arbitrary but aव्योमs the loop running away अगर
	 * the SPRAM tags are implemented dअगरferently
	 */

	क्रम (i = 0; i < 8; i++) अणु
		tag0 = पढ़ो(offset);
		tag1 = पढ़ो(offset+SPRAM_TAG_STRIDE);
		pr_debug("DBG %s%d: tag0=%08x tag1=%08x\n",
			 type, i, tag0, tag1);

		size = tag1 & SPRAM_TAG1_SIZE_MASK;

		अगर (size == 0)
			अवरोध;

		अगर (i != 0) अणु
			/* tags may repeat... */
			अगर ((pa == firstpa && size == firstsize) ||
			    (pa == lastpa && size == lastsize))
				अवरोध;
		पूर्ण

		/* Align base with size */
		base = (base + size - 1) & ~(size-1);

		/* reprogram the base address base address and enable */
		tag0 = (base & SPRAM_TAG0_PA_MASK) | SPRAM_TAG0_ENABLE;
		ग_लिखो(offset, tag0);

		base += size;

		/* reपढ़ो the tag */
		tag0 = पढ़ो(offset);
		pa = tag0 & SPRAM_TAG0_PA_MASK;
		enabled = tag0 & SPRAM_TAG0_ENABLE;

		अगर (i == 0) अणु
			firstpa = pa;
			firstsize = size;
		पूर्ण

		lastpa = pa;
		lastsize = size;

		अगर (म_भेद(type, "DSPRAM") == 0) अणु
			अचिन्हित पूर्णांक *vp = (अचिन्हित पूर्णांक *)(CKSEG1 | pa);
			अचिन्हित पूर्णांक v;
#घोषणा TDAT	0x5a5aa5a5
			vp[0] = TDAT;
			vp[1] = ~TDAT;

			mb();

			v = vp[0];
			अगर (v != TDAT)
				prपूर्णांकk(KERN_ERR "vp=%p wrote=%08x got=%08x\n",
				       vp, TDAT, v);
			v = vp[1];
			अगर (v != ~TDAT)
				prपूर्णांकk(KERN_ERR "vp=%p wrote=%08x got=%08x\n",
				       vp+1, ~TDAT, v);
		पूर्ण

		pr_info("%s%d: PA=%08x,Size=%08x%s\n",
			type, i, pa, size, enabled ? ",enabled" : "");
		offset += 2 * SPRAM_TAG_STRIDE;
	पूर्ण
पूर्ण
व्योम spram_config(व्योम)
अणु
	अचिन्हित पूर्णांक config0;

	चयन (current_cpu_type()) अणु
	हाल CPU_24K:
	हाल CPU_34K:
	हाल CPU_74K:
	हाल CPU_1004K:
	हाल CPU_1074K:
	हाल CPU_INTERAPTIV:
	हाल CPU_PROAPTIV:
	हाल CPU_P5600:
	हाल CPU_QEMU_GENERIC:
	हाल CPU_I6400:
	हाल CPU_P6600:
		config0 = पढ़ो_c0_config();
		/* FIXME: addresses are Malta specअगरic */
		अगर (config0 & MIPS_CONF_ISP) अणु
			probe_spram("ISPRAM", 0x1c000000,
				    &ispram_load_tag, &ispram_store_tag);
		पूर्ण
		अगर (config0 & MIPS_CONF_DSP)
			probe_spram("DSPRAM", 0x1c100000,
				    &dspram_load_tag, &dspram_store_tag);
	पूर्ण
पूर्ण
