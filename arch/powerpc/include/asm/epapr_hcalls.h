<शैली गुरु>
/*
 * ePAPR hcall पूर्णांकerface
 *
 * Copyright 2008-2011 Freescale Semiconductor, Inc.
 *
 * Author: Timur Tabi <timur@मुक्तscale.com>
 *
 * This file is provided under a dual BSD/GPL license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary क्रमm must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       करोcumentation and/or other materials provided with the distribution.
 *     * Neither the name of Freescale Semiconductor nor the
 *       names of its contributors may be used to enकरोrse or promote products
 *       derived from this software without specअगरic prior written permission.
 *
 *
 * ALTERNATIVELY, this software may be distributed under the terms of the
 * GNU General Public License ("GPL") as published by the Free Software
 * Foundation, either version 2 of that License or (at your option) any
 * later version.
 *
 * THIS SOFTWARE IS PROVIDED BY Freescale Semiconductor ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Freescale Semiconductor BE LIABLE FOR ANY
 * सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* A "hypercall" is an "sc 1" inकाष्ठाion.  This header file provides C
 * wrapper functions क्रम the ePAPR hypervisor पूर्णांकerface.  It is पूर्णांकeded
 * क्रम use by Linux device drivers and other operating प्रणालीs.
 *
 * The hypercalls are implemented as अंतरभूत assembly, rather than assembly
 * language functions in a .S file, क्रम optimization.  It allows
 * the caller to issue the hypercall inकाष्ठाion directly, improving both
 * perक्रमmance and memory footprपूर्णांक.
 */

#अगर_अघोषित _EPAPR_HCALLS_H
#घोषणा _EPAPR_HCALLS_H

#समावेश <uapi/यंत्र/epapr_hcalls.h>

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/byteorder.h>

/*
 * Hypercall रेजिस्टर clobber list
 *
 * These macros are used to define the list of clobbered रेजिस्टरs during a
 * hypercall.  Technically, रेजिस्टरs r0 and r3-r12 are always clobbered,
 * but the gcc अंतरभूत assembly syntax करोes not allow us to specअगरy रेजिस्टरs
 * on the clobber list that are also on the input/output list.  Thereक्रमe,
 * the lists of clobbered रेजिस्टरs depends on the number of रेजिस्टर
 * parmeters ("+r" and "=r") passed to the hypercall.
 *
 * Each assembly block should use one of the HCALL_CLOBBERSx macros.  As a
 * general rule, 'x' is the number of parameters passed to the assembly
 * block *except* क्रम r11.
 *
 * If you're not sure, just use the smallest value of 'x' that करोes not
 * generate a compilation error.  Because these are अटल अंतरभूत functions,
 * the compiler will only check the clobber list क्रम a function अगर you
 * compile code that calls that function.
 *
 * r3 and r11 are not included in any clobbers list because they are always
 * listed as output रेजिस्टरs.
 *
 * XER, CTR, and LR are currently listed as clobbers because it's uncertain
 * whether they will be clobbered.
 *
 * Note that r11 can be used as an output parameter.
 *
 * The "memory" clobber is only necessary क्रम hcalls where the Hypervisor
 * will पढ़ो or ग_लिखो guest memory. However, we add it to all hcalls because
 * the impact is minimal, and we want to ensure that it's present क्रम the
 * hcalls that need it.
*/

/* List of common clobbered रेजिस्टरs.  Do not use this macro. */
#घोषणा EV_HCALL_CLOBBERS "r0", "r12", "xer", "ctr", "lr", "cc", "memory"

#घोषणा EV_HCALL_CLOBBERS8 EV_HCALL_CLOBBERS
#घोषणा EV_HCALL_CLOBBERS7 EV_HCALL_CLOBBERS8, "r10"
#घोषणा EV_HCALL_CLOBBERS6 EV_HCALL_CLOBBERS7, "r9"
#घोषणा EV_HCALL_CLOBBERS5 EV_HCALL_CLOBBERS6, "r8"
#घोषणा EV_HCALL_CLOBBERS4 EV_HCALL_CLOBBERS5, "r7"
#घोषणा EV_HCALL_CLOBBERS3 EV_HCALL_CLOBBERS4, "r6"
#घोषणा EV_HCALL_CLOBBERS2 EV_HCALL_CLOBBERS3, "r5"
#घोषणा EV_HCALL_CLOBBERS1 EV_HCALL_CLOBBERS2, "r4"

बाह्य bool epapr_paravirt_enabled;
बाह्य u32 epapr_hypercall_start[];

#अगर_घोषित CONFIG_EPAPR_PARAVIRT
पूर्णांक __init epapr_paravirt_early_init(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक epapr_paravirt_early_init(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर

/*
 * We use "uintptr_t" to define a रेजिस्टर because it's guaranteed to be a
 * 32-bit पूर्णांकeger on a 32-bit platक्रमm, and a 64-bit पूर्णांकeger on a 64-bit
 * platक्रमm.
 *
 * All रेजिस्टरs are either input/output or output only.  Registers that are
 * initialized beक्रमe making the hypercall are input/output.  All
 * input/output रेजिस्टरs are represented with "+r".  Output-only रेजिस्टरs
 * are represented with "=r".  Do not specअगरy any unused रेजिस्टरs.  The
 * clobber list will tell the compiler that the hypercall modअगरies those
 * रेजिस्टरs, which is good enough.
 */

/**
 * ev_पूर्णांक_set_config - configure the specअगरied पूर्णांकerrupt
 * @पूर्णांकerrupt: the पूर्णांकerrupt number
 * @config: configuration क्रम this पूर्णांकerrupt
 * @priority: पूर्णांकerrupt priority
 * @destination: destination CPU number
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ev_पूर्णांक_set_config(अचिन्हित पूर्णांक पूर्णांकerrupt,
	uपूर्णांक32_t config, अचिन्हित पूर्णांक priority, uपूर्णांक32_t destination)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");
	रेजिस्टर uपूर्णांकptr_t r5 __यंत्र__("r5");
	रेजिस्टर uपूर्णांकptr_t r6 __यंत्र__("r6");

	r11 = EV_HCALL_TOKEN(EV_INT_SET_CONFIG);
	r3  = पूर्णांकerrupt;
	r4  = config;
	r5  = priority;
	r6  = destination;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3), "+r" (r4), "+r" (r5), "+r" (r6)
		: : EV_HCALL_CLOBBERS4
	);

	वापस r3;
पूर्ण

/**
 * ev_पूर्णांक_get_config - वापस the config of the specअगरied पूर्णांकerrupt
 * @पूर्णांकerrupt: the पूर्णांकerrupt number
 * @config: वापसed configuration क्रम this पूर्णांकerrupt
 * @priority: वापसed पूर्णांकerrupt priority
 * @destination: वापसed destination CPU number
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ev_पूर्णांक_get_config(अचिन्हित पूर्णांक पूर्णांकerrupt,
	uपूर्णांक32_t *config, अचिन्हित पूर्णांक *priority, uपूर्णांक32_t *destination)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");
	रेजिस्टर uपूर्णांकptr_t r5 __यंत्र__("r5");
	रेजिस्टर uपूर्णांकptr_t r6 __यंत्र__("r6");

	r11 = EV_HCALL_TOKEN(EV_INT_GET_CONFIG);
	r3 = पूर्णांकerrupt;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3), "=r" (r4), "=r" (r5), "=r" (r6)
		: : EV_HCALL_CLOBBERS4
	);

	*config = r4;
	*priority = r5;
	*destination = r6;

	वापस r3;
पूर्ण

/**
 * ev_पूर्णांक_set_mask - sets the mask क्रम the specअगरied पूर्णांकerrupt source
 * @पूर्णांकerrupt: the पूर्णांकerrupt number
 * @mask: 0=enable पूर्णांकerrupts, 1=disable पूर्णांकerrupts
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ev_पूर्णांक_set_mask(अचिन्हित पूर्णांक पूर्णांकerrupt,
	अचिन्हित पूर्णांक mask)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");

	r11 = EV_HCALL_TOKEN(EV_INT_SET_MASK);
	r3 = पूर्णांकerrupt;
	r4 = mask;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3), "+r" (r4)
		: : EV_HCALL_CLOBBERS2
	);

	वापस r3;
पूर्ण

/**
 * ev_पूर्णांक_get_mask - वापसs the mask क्रम the specअगरied पूर्णांकerrupt source
 * @पूर्णांकerrupt: the पूर्णांकerrupt number
 * @mask: वापसed mask क्रम this पूर्णांकerrupt (0=enabled, 1=disabled)
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ev_पूर्णांक_get_mask(अचिन्हित पूर्णांक पूर्णांकerrupt,
	अचिन्हित पूर्णांक *mask)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");

	r11 = EV_HCALL_TOKEN(EV_INT_GET_MASK);
	r3 = पूर्णांकerrupt;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3), "=r" (r4)
		: : EV_HCALL_CLOBBERS2
	);

	*mask = r4;

	वापस r3;
पूर्ण

/**
 * ev_पूर्णांक_eoi - संकेत the end of पूर्णांकerrupt processing
 * @पूर्णांकerrupt: the पूर्णांकerrupt number
 *
 * This function संकेतs the end of processing क्रम the specअगरied
 * पूर्णांकerrupt, which must be the पूर्णांकerrupt currently in service. By
 * definition, this is also the highest-priority पूर्णांकerrupt.
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ev_पूर्णांक_eoi(अचिन्हित पूर्णांक पूर्णांकerrupt)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");

	r11 = EV_HCALL_TOKEN(EV_INT_EOI);
	r3 = पूर्णांकerrupt;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3)
		: : EV_HCALL_CLOBBERS1
	);

	वापस r3;
पूर्ण

/**
 * ev_byte_channel_send - send अक्षरacters to a byte stream
 * @handle: byte stream handle
 * @count: (input) num of अक्षरs to send, (output) num अक्षरs sent
 * @buffer: poपूर्णांकer to a 16-byte buffer
 *
 * @buffer must be at least 16 bytes दीर्घ, because all 16 bytes will be
 * पढ़ो from memory पूर्णांकo रेजिस्टरs, even अगर count < 16.
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ev_byte_channel_send(अचिन्हित पूर्णांक handle,
	अचिन्हित पूर्णांक *count, स्थिर अक्षर buffer[EV_BYTE_CHANNEL_MAX_BYTES])
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");
	रेजिस्टर uपूर्णांकptr_t r5 __यंत्र__("r5");
	रेजिस्टर uपूर्णांकptr_t r6 __यंत्र__("r6");
	रेजिस्टर uपूर्णांकptr_t r7 __यंत्र__("r7");
	रेजिस्टर uपूर्णांकptr_t r8 __यंत्र__("r8");
	स्थिर uपूर्णांक32_t *p = (स्थिर uपूर्णांक32_t *) buffer;

	r11 = EV_HCALL_TOKEN(EV_BYTE_CHANNEL_SEND);
	r3 = handle;
	r4 = *count;
	r5 = be32_to_cpu(p[0]);
	r6 = be32_to_cpu(p[1]);
	r7 = be32_to_cpu(p[2]);
	r8 = be32_to_cpu(p[3]);

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3),
		  "+r" (r4), "+r" (r5), "+r" (r6), "+r" (r7), "+r" (r8)
		: : EV_HCALL_CLOBBERS6
	);

	*count = r4;

	वापस r3;
पूर्ण

/**
 * ev_byte_channel_receive - fetch अक्षरacters from a byte channel
 * @handle: byte channel handle
 * @count: (input) max num of अक्षरs to receive, (output) num अक्षरs received
 * @buffer: poपूर्णांकer to a 16-byte buffer
 *
 * The size of @buffer must be at least 16 bytes, even अगर you request fewer
 * than 16 अक्षरacters, because we always ग_लिखो 16 bytes to @buffer.  This is
 * क्रम perक्रमmance reasons.
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ev_byte_channel_receive(अचिन्हित पूर्णांक handle,
	अचिन्हित पूर्णांक *count, अक्षर buffer[EV_BYTE_CHANNEL_MAX_BYTES])
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");
	रेजिस्टर uपूर्णांकptr_t r5 __यंत्र__("r5");
	रेजिस्टर uपूर्णांकptr_t r6 __यंत्र__("r6");
	रेजिस्टर uपूर्णांकptr_t r7 __यंत्र__("r7");
	रेजिस्टर uपूर्णांकptr_t r8 __यंत्र__("r8");
	uपूर्णांक32_t *p = (uपूर्णांक32_t *) buffer;

	r11 = EV_HCALL_TOKEN(EV_BYTE_CHANNEL_RECEIVE);
	r3 = handle;
	r4 = *count;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3), "+r" (r4),
		  "=r" (r5), "=r" (r6), "=r" (r7), "=r" (r8)
		: : EV_HCALL_CLOBBERS6
	);

	*count = r4;
	p[0] = cpu_to_be32(r5);
	p[1] = cpu_to_be32(r6);
	p[2] = cpu_to_be32(r7);
	p[3] = cpu_to_be32(r8);

	वापस r3;
पूर्ण

/**
 * ev_byte_channel_poll - वापसs the status of the byte channel buffers
 * @handle: byte channel handle
 * @rx_count: वापसed count of bytes in receive queue
 * @tx_count: वापसed count of मुक्त space in transmit queue
 *
 * This function reports the amount of data in the receive queue (i.e. the
 * number of bytes you can पढ़ो), and the amount of मुक्त space in the transmit
 * queue (i.e. the number of bytes you can ग_लिखो).
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ev_byte_channel_poll(अचिन्हित पूर्णांक handle,
	अचिन्हित पूर्णांक *rx_count,	अचिन्हित पूर्णांक *tx_count)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");
	रेजिस्टर uपूर्णांकptr_t r5 __यंत्र__("r5");

	r11 = EV_HCALL_TOKEN(EV_BYTE_CHANNEL_POLL);
	r3 = handle;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3), "=r" (r4), "=r" (r5)
		: : EV_HCALL_CLOBBERS3
	);

	*rx_count = r4;
	*tx_count = r5;

	वापस r3;
पूर्ण

/**
 * ev_पूर्णांक_iack - acknowledge an पूर्णांकerrupt
 * @handle: handle to the target पूर्णांकerrupt controller
 * @vector: वापसed पूर्णांकerrupt vector
 *
 * If handle is zero, the function वापसs the next पूर्णांकerrupt source
 * number to be handled irrespective of the hierarchy or cascading
 * of पूर्णांकerrupt controllers. If non-zero, specअगरies a handle to the
 * पूर्णांकerrupt controller that is the target of the acknowledge.
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ev_पूर्णांक_iack(अचिन्हित पूर्णांक handle,
	अचिन्हित पूर्णांक *vector)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");

	r11 = EV_HCALL_TOKEN(EV_INT_IACK);
	r3 = handle;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3), "=r" (r4)
		: : EV_HCALL_CLOBBERS2
	);

	*vector = r4;

	वापस r3;
पूर्ण

/**
 * ev_करोorbell_send - send a करोorbell to another partition
 * @handle: करोorbell send handle
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ev_करोorbell_send(अचिन्हित पूर्णांक handle)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");

	r11 = EV_HCALL_TOKEN(EV_DOORBELL_SEND);
	r3 = handle;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3)
		: : EV_HCALL_CLOBBERS1
	);

	वापस r3;
पूर्ण

/**
 * ev_idle -- रुको क्रम next पूर्णांकerrupt on this core
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक ev_idle(व्योम)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");

	r11 = EV_HCALL_TOKEN(EV_IDLE);

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "=r" (r3)
		: : EV_HCALL_CLOBBERS1
	);

	वापस r3;
पूर्ण

#अगर_घोषित CONFIG_EPAPR_PARAVIRT
अटल अंतरभूत अचिन्हित दीर्घ epapr_hypercall(अचिन्हित दीर्घ *in,
			    अचिन्हित दीर्घ *out,
			    अचिन्हित दीर्घ nr)
अणु
	रेजिस्टर अचिन्हित दीर्घ r0 यंत्र("r0");
	रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("r3") = in[0];
	रेजिस्टर अचिन्हित दीर्घ r4 यंत्र("r4") = in[1];
	रेजिस्टर अचिन्हित दीर्घ r5 यंत्र("r5") = in[2];
	रेजिस्टर अचिन्हित दीर्घ r6 यंत्र("r6") = in[3];
	रेजिस्टर अचिन्हित दीर्घ r7 यंत्र("r7") = in[4];
	रेजिस्टर अचिन्हित दीर्घ r8 यंत्र("r8") = in[5];
	रेजिस्टर अचिन्हित दीर्घ r9 यंत्र("r9") = in[6];
	रेजिस्टर अचिन्हित दीर्घ r10 यंत्र("r10") = in[7];
	रेजिस्टर अचिन्हित दीर्घ r11 यंत्र("r11") = nr;
	रेजिस्टर अचिन्हित दीर्घ r12 यंत्र("r12");

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		     : "=r"(r0), "=r"(r3), "=r"(r4), "=r"(r5), "=r"(r6),
		       "=r"(r7), "=r"(r8), "=r"(r9), "=r"(r10), "=r"(r11),
		       "=r"(r12)
		     : "r"(r3), "r"(r4), "r"(r5), "r"(r6), "r"(r7), "r"(r8),
		       "r"(r9), "r"(r10), "r"(r11)
		     : "memory", "cc", "xer", "ctr", "lr");

	out[0] = r4;
	out[1] = r5;
	out[2] = r6;
	out[3] = r7;
	out[4] = r8;
	out[5] = r9;
	out[6] = r10;
	out[7] = r11;

	वापस r3;
पूर्ण
#अन्यथा
अटल अचिन्हित दीर्घ epapr_hypercall(अचिन्हित दीर्घ *in,
				   अचिन्हित दीर्घ *out,
				   अचिन्हित दीर्घ nr)
अणु
	वापस EV_UNIMPLEMENTED;
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत दीर्घ epapr_hypercall0_1(अचिन्हित पूर्णांक nr, अचिन्हित दीर्घ *r2)
अणु
	अचिन्हित दीर्घ in[8] = अणु0पूर्ण;
	अचिन्हित दीर्घ out[8];
	अचिन्हित दीर्घ r;

	r = epapr_hypercall(in, out, nr);
	*r2 = out[0];

	वापस r;
पूर्ण

अटल अंतरभूत दीर्घ epapr_hypercall0(अचिन्हित पूर्णांक nr)
अणु
	अचिन्हित दीर्घ in[8] = अणु0पूर्ण;
	अचिन्हित दीर्घ out[8];

	वापस epapr_hypercall(in, out, nr);
पूर्ण

अटल अंतरभूत दीर्घ epapr_hypercall1(अचिन्हित पूर्णांक nr, अचिन्हित दीर्घ p1)
अणु
	अचिन्हित दीर्घ in[8] = अणु0पूर्ण;
	अचिन्हित दीर्घ out[8];

	in[0] = p1;
	वापस epapr_hypercall(in, out, nr);
पूर्ण

अटल अंतरभूत दीर्घ epapr_hypercall2(अचिन्हित पूर्णांक nr, अचिन्हित दीर्घ p1,
				    अचिन्हित दीर्घ p2)
अणु
	अचिन्हित दीर्घ in[8] = अणु0पूर्ण;
	अचिन्हित दीर्घ out[8];

	in[0] = p1;
	in[1] = p2;
	वापस epapr_hypercall(in, out, nr);
पूर्ण

अटल अंतरभूत दीर्घ epapr_hypercall3(अचिन्हित पूर्णांक nr, अचिन्हित दीर्घ p1,
				    अचिन्हित दीर्घ p2, अचिन्हित दीर्घ p3)
अणु
	अचिन्हित दीर्घ in[8] = अणु0पूर्ण;
	अचिन्हित दीर्घ out[8];

	in[0] = p1;
	in[1] = p2;
	in[2] = p3;
	वापस epapr_hypercall(in, out, nr);
पूर्ण

अटल अंतरभूत दीर्घ epapr_hypercall4(अचिन्हित पूर्णांक nr, अचिन्हित दीर्घ p1,
				    अचिन्हित दीर्घ p2, अचिन्हित दीर्घ p3,
				    अचिन्हित दीर्घ p4)
अणु
	अचिन्हित दीर्घ in[8] = अणु0पूर्ण;
	अचिन्हित दीर्घ out[8];

	in[0] = p1;
	in[1] = p2;
	in[2] = p3;
	in[3] = p4;
	वापस epapr_hypercall(in, out, nr);
पूर्ण
#पूर्ण_अगर /* !__ASSEMBLY__ */
#पूर्ण_अगर /* _EPAPR_HCALLS_H */
