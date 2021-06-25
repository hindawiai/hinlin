<शैली गुरु>
/*
 * Copyright 2003-2011 NetLogic Microप्रणालीs, Inc. (NetLogic). All rights
 * reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the NetLogic
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY NETLOGIC ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL NETLOGIC OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/init.h>

#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/cpu-features.h>

#समावेश <यंत्र/netlogic/पूर्णांकerrupt.h>
#समावेश <यंत्र/netlogic/common.h>
#समावेश <यंत्र/netlogic/haldefs.h>

#अगर defined(CONFIG_CPU_XLP)
#समावेश <यंत्र/netlogic/xlp-hal/iomap.h>
#समावेश <यंत्र/netlogic/xlp-hal/xlp.h>
#समावेश <यंत्र/netlogic/xlp-hal/sys.h>
#समावेश <यंत्र/netlogic/xlp-hal/pic.h>
#या_अगर defined(CONFIG_CPU_XLR)
#समावेश <यंत्र/netlogic/xlr/iomap.h>
#समावेश <यंत्र/netlogic/xlr/pic.h>
#समावेश <यंत्र/netlogic/xlr/xlr.h>
#अन्यथा
#त्रुटि "Unknown CPU"
#पूर्ण_अगर

अचिन्हित पूर्णांक get_c0_compare_पूर्णांक(व्योम)
अणु
	वापस IRQ_TIMER;
पूर्ण

अटल u64 nlm_get_pic_समयr(काष्ठा घड़ीsource *cs)
अणु
	uपूर्णांक64_t picbase = nlm_get_node(0)->picbase;

	वापस ~nlm_pic_पढ़ो_समयr(picbase, PIC_CLOCK_TIMER);
पूर्ण

अटल u64 nlm_get_pic_समयr32(काष्ठा घड़ीsource *cs)
अणु
	uपूर्णांक64_t picbase = nlm_get_node(0)->picbase;

	वापस ~nlm_pic_पढ़ो_समयr32(picbase, PIC_CLOCK_TIMER);
पूर्ण

अटल काष्ठा घड़ीsource csrc_pic = अणु
	.name		= "PIC",
	.flags		= CLOCK_SOURCE_IS_CONTINUOUS,
पूर्ण;

अटल व्योम nlm_init_pic_समयr(व्योम)
अणु
	uपूर्णांक64_t picbase = nlm_get_node(0)->picbase;
	u32 picfreq;

	nlm_pic_set_समयr(picbase, PIC_CLOCK_TIMER, ~0ULL, 0, 0);
	अगर (current_cpu_data.cputype == CPU_XLR) अणु
		csrc_pic.mask	= CLOCKSOURCE_MASK(32);
		csrc_pic.पढ़ो	= nlm_get_pic_समयr32;
	पूर्ण अन्यथा अणु
		csrc_pic.mask	= CLOCKSOURCE_MASK(64);
		csrc_pic.पढ़ो	= nlm_get_pic_समयr;
	पूर्ण
	csrc_pic.rating = 1000;
	picfreq = pic_समयr_freq();
	घड़ीsource_रेजिस्टर_hz(&csrc_pic, picfreq);
	pr_info("PIC clock source added, frequency %d\n", picfreq);
पूर्ण

व्योम __init plat_समय_init(व्योम)
अणु
	nlm_init_pic_समयr();
	mips_hpt_frequency = nlm_get_cpu_frequency();
	अगर (current_cpu_type() == CPU_XLR)
		preset_lpj = mips_hpt_frequency / (3 * HZ);
	अन्यथा
		preset_lpj = mips_hpt_frequency / (2 * HZ);
	pr_info("MIPS counter frequency [%ld]\n",
			(अचिन्हित दीर्घ)mips_hpt_frequency);
पूर्ण
