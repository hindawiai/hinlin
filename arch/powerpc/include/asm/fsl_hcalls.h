<शैली गुरु>
/*
 * Freescale hypervisor call पूर्णांकerface
 *
 * Copyright 2008-2010 Freescale Semiconductor, Inc.
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

#अगर_अघोषित _FSL_HCALLS_H
#घोषणा _FSL_HCALLS_H

#समावेश <linux/types.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/epapr_hcalls.h>

#घोषणा FH_API_VERSION			1

#घोषणा FH_ERR_GET_INFO			1
#घोषणा FH_PARTITION_GET_DTPROP		2
#घोषणा FH_PARTITION_SET_DTPROP		3
#घोषणा FH_PARTITION_RESTART		4
#घोषणा FH_PARTITION_GET_STATUS		5
#घोषणा FH_PARTITION_START		6
#घोषणा FH_PARTITION_STOP		7
#घोषणा FH_PARTITION_MEMCPY		8
#घोषणा FH_DMA_ENABLE			9
#घोषणा FH_DMA_DISABLE			10
#घोषणा FH_SEND_NMI			11
#घोषणा FH_VMPIC_GET_MSIR		12
#घोषणा FH_SYSTEM_RESET			13
#घोषणा FH_GET_CORE_STATE		14
#घोषणा FH_ENTER_NAP			15
#घोषणा FH_EXIT_NAP			16
#घोषणा FH_CLAIM_DEVICE			17
#घोषणा FH_PARTITION_STOP_DMA		18

/* venकरोr ID: Freescale Semiconductor */
#घोषणा FH_HCALL_TOKEN(num)		_EV_HCALL_TOKEN(EV_FSL_VENDOR_ID, num)

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
 * fh_send_nmi - send NMI to भव cpu(s).
 * @vcpu_mask: send NMI to भव cpu(s) specअगरied by this mask.
 *
 * Returns 0 क्रम success, or EINVAL क्रम invalid vcpu_mask.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_send_nmi(अचिन्हित पूर्णांक vcpu_mask)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");

	r11 = FH_HCALL_TOKEN(FH_SEND_NMI);
	r3 = vcpu_mask;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3)
		: : EV_HCALL_CLOBBERS1
	);

	वापस r3;
पूर्ण

/* Arbitrary limits to aव्योम excessive memory allocation in hypervisor */
#घोषणा FH_DTPROP_MAX_PATHLEN 4096
#घोषणा FH_DTPROP_MAX_PROPLEN 32768

/**
 * fh_partition_get_dtprop - get a property from a guest device tree.
 * @handle: handle of partition whose device tree is to be accessed
 * @dtpath_addr: physical address of device tree path to access
 * @propname_addr: physical address of name of property
 * @propvalue_addr: physical address of property value buffer
 * @propvalue_len: length of buffer on entry, length of property on वापस
 *
 * Returns zero on success, non-zero on error.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_partition_get_dtprop(पूर्णांक handle,
						   uपूर्णांक64_t dtpath_addr,
						   uपूर्णांक64_t propname_addr,
						   uपूर्णांक64_t propvalue_addr,
						   uपूर्णांक32_t *propvalue_len)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");
	रेजिस्टर uपूर्णांकptr_t r5 __यंत्र__("r5");
	रेजिस्टर uपूर्णांकptr_t r6 __यंत्र__("r6");
	रेजिस्टर uपूर्णांकptr_t r7 __यंत्र__("r7");
	रेजिस्टर uपूर्णांकptr_t r8 __यंत्र__("r8");
	रेजिस्टर uपूर्णांकptr_t r9 __यंत्र__("r9");
	रेजिस्टर uपूर्णांकptr_t r10 __यंत्र__("r10");

	r11 = FH_HCALL_TOKEN(FH_PARTITION_GET_DTPROP);
	r3 = handle;

#अगर_घोषित CONFIG_PHYS_64BIT
	r4 = dtpath_addr >> 32;
	r6 = propname_addr >> 32;
	r8 = propvalue_addr >> 32;
#अन्यथा
	r4 = 0;
	r6 = 0;
	r8 = 0;
#पूर्ण_अगर
	r5 = (uपूर्णांक32_t)dtpath_addr;
	r7 = (uपूर्णांक32_t)propname_addr;
	r9 = (uपूर्णांक32_t)propvalue_addr;
	r10 = *propvalue_len;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11),
		  "+r" (r3), "+r" (r4), "+r" (r5), "+r" (r6), "+r" (r7),
		  "+r" (r8), "+r" (r9), "+r" (r10)
		: : EV_HCALL_CLOBBERS8
	);

	*propvalue_len = r4;
	वापस r3;
पूर्ण

/**
 * Set a property in a guest device tree.
 * @handle: handle of partition whose device tree is to be accessed
 * @dtpath_addr: physical address of device tree path to access
 * @propname_addr: physical address of name of property
 * @propvalue_addr: physical address of property value
 * @propvalue_len: length of property
 *
 * Returns zero on success, non-zero on error.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_partition_set_dtprop(पूर्णांक handle,
						   uपूर्णांक64_t dtpath_addr,
						   uपूर्णांक64_t propname_addr,
						   uपूर्णांक64_t propvalue_addr,
						   uपूर्णांक32_t propvalue_len)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");
	रेजिस्टर uपूर्णांकptr_t r6 __यंत्र__("r6");
	रेजिस्टर uपूर्णांकptr_t r8 __यंत्र__("r8");
	रेजिस्टर uपूर्णांकptr_t r5 __यंत्र__("r5");
	रेजिस्टर uपूर्णांकptr_t r7 __यंत्र__("r7");
	रेजिस्टर uपूर्णांकptr_t r9 __यंत्र__("r9");
	रेजिस्टर uपूर्णांकptr_t r10 __यंत्र__("r10");

	r11 = FH_HCALL_TOKEN(FH_PARTITION_SET_DTPROP);
	r3 = handle;

#अगर_घोषित CONFIG_PHYS_64BIT
	r4 = dtpath_addr >> 32;
	r6 = propname_addr >> 32;
	r8 = propvalue_addr >> 32;
#अन्यथा
	r4 = 0;
	r6 = 0;
	r8 = 0;
#पूर्ण_अगर
	r5 = (uपूर्णांक32_t)dtpath_addr;
	r7 = (uपूर्णांक32_t)propname_addr;
	r9 = (uपूर्णांक32_t)propvalue_addr;
	r10 = propvalue_len;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11),
		  "+r" (r3), "+r" (r4), "+r" (r5), "+r" (r6), "+r" (r7),
		  "+r" (r8), "+r" (r9), "+r" (r10)
		: : EV_HCALL_CLOBBERS8
	);

	वापस r3;
पूर्ण

/**
 * fh_partition_restart - reboot the current partition
 * @partition: partition ID
 *
 * Returns an error code अगर reboot failed.  Does not वापस अगर it succeeds.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_partition_restart(अचिन्हित पूर्णांक partition)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");

	r11 = FH_HCALL_TOKEN(FH_PARTITION_RESTART);
	r3 = partition;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3)
		: : EV_HCALL_CLOBBERS1
	);

	वापस r3;
पूर्ण

#घोषणा FH_PARTITION_STOPPED	0
#घोषणा FH_PARTITION_RUNNING	1
#घोषणा FH_PARTITION_STARTING	2
#घोषणा FH_PARTITION_STOPPING	3
#घोषणा FH_PARTITION_PAUSING	4
#घोषणा FH_PARTITION_PAUSED	5
#घोषणा FH_PARTITION_RESUMING	6

/**
 * fh_partition_get_status - माला_लो the status of a partition
 * @partition: partition ID
 * @status: वापसed status code
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_partition_get_status(अचिन्हित पूर्णांक partition,
	अचिन्हित पूर्णांक *status)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");

	r11 = FH_HCALL_TOKEN(FH_PARTITION_GET_STATUS);
	r3 = partition;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3), "=r" (r4)
		: : EV_HCALL_CLOBBERS2
	);

	*status = r4;

	वापस r3;
पूर्ण

/**
 * fh_partition_start - boots and starts execution of the specअगरied partition
 * @partition: partition ID
 * @entry_poपूर्णांक: guest physical address to start execution
 *
 * The hypervisor creates a 1-to-1 भव/physical IMA mapping, so at boot
 * समय, guest physical address are the same as guest भव addresses.
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_partition_start(अचिन्हित पूर्णांक partition,
	uपूर्णांक32_t entry_poपूर्णांक, पूर्णांक load)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");
	रेजिस्टर uपूर्णांकptr_t r5 __यंत्र__("r5");

	r11 = FH_HCALL_TOKEN(FH_PARTITION_START);
	r3 = partition;
	r4 = entry_poपूर्णांक;
	r5 = load;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3), "+r" (r4), "+r" (r5)
		: : EV_HCALL_CLOBBERS3
	);

	वापस r3;
पूर्ण

/**
 * fh_partition_stop - stops another partition
 * @partition: partition ID
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_partition_stop(अचिन्हित पूर्णांक partition)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");

	r11 = FH_HCALL_TOKEN(FH_PARTITION_STOP);
	r3 = partition;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3)
		: : EV_HCALL_CLOBBERS1
	);

	वापस r3;
पूर्ण

/**
 * काष्ठा fh_sg_list: definition of the fh_partition_स_नकल S/G list
 * @source: guest physical address to copy from
 * @target: guest physical address to copy to
 * @size: number of bytes to copy
 * @reserved: reserved, must be zero
 *
 * The scatter/gather list क्रम fh_partition_स_नकल() is an array of these
 * काष्ठाures.  The array must be guest physically contiguous.
 *
 * This काष्ठाure must be aligned on 32-byte boundary, so that no single
 * strucuture can span two pages.
 */
काष्ठा fh_sg_list अणु
	uपूर्णांक64_t source;   /**< guest physical address to copy from */
	uपूर्णांक64_t target;   /**< guest physical address to copy to */
	uपूर्णांक64_t size;     /**< number of bytes to copy */
	uपूर्णांक64_t reserved; /**< reserved, must be zero */
पूर्ण __attribute__ ((aligned(32)));

/**
 * fh_partition_स_नकल - copies data from one guest to another
 * @source: the ID of the partition to copy from
 * @target: the ID of the partition to copy to
 * @sg_list: guest physical address of an array of &fh_sg_list काष्ठाures
 * @count: the number of entries in @sg_list
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_partition_स_नकल(अचिन्हित पूर्णांक source,
	अचिन्हित पूर्णांक target, phys_addr_t sg_list, अचिन्हित पूर्णांक count)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");
	रेजिस्टर uपूर्णांकptr_t r5 __यंत्र__("r5");
	रेजिस्टर uपूर्णांकptr_t r6 __यंत्र__("r6");
	रेजिस्टर uपूर्णांकptr_t r7 __यंत्र__("r7");

	r11 = FH_HCALL_TOKEN(FH_PARTITION_MEMCPY);
	r3 = source;
	r4 = target;
	r5 = (uपूर्णांक32_t) sg_list;

#अगर_घोषित CONFIG_PHYS_64BIT
	r6 = sg_list >> 32;
#अन्यथा
	r6 = 0;
#पूर्ण_अगर
	r7 = count;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11),
		  "+r" (r3), "+r" (r4), "+r" (r5), "+r" (r6), "+r" (r7)
		: : EV_HCALL_CLOBBERS5
	);

	वापस r3;
पूर्ण

/**
 * fh_dma_enable - enable DMA क्रम the specअगरied device
 * @liodn: the LIODN of the I/O device क्रम which to enable DMA
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_dma_enable(अचिन्हित पूर्णांक liodn)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");

	r11 = FH_HCALL_TOKEN(FH_DMA_ENABLE);
	r3 = liodn;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3)
		: : EV_HCALL_CLOBBERS1
	);

	वापस r3;
पूर्ण

/**
 * fh_dma_disable - disable DMA क्रम the specअगरied device
 * @liodn: the LIODN of the I/O device क्रम which to disable DMA
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_dma_disable(अचिन्हित पूर्णांक liodn)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");

	r11 = FH_HCALL_TOKEN(FH_DMA_DISABLE);
	r3 = liodn;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3)
		: : EV_HCALL_CLOBBERS1
	);

	वापस r3;
पूर्ण


/**
 * fh_vmpic_get_msir - वापसs the MPIC-MSI रेजिस्टर value
 * @पूर्णांकerrupt: the पूर्णांकerrupt number
 * @msir_val: वापसed MPIC-MSI रेजिस्टर value
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_vmpic_get_msir(अचिन्हित पूर्णांक पूर्णांकerrupt,
	अचिन्हित पूर्णांक *msir_val)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");

	r11 = FH_HCALL_TOKEN(FH_VMPIC_GET_MSIR);
	r3 = पूर्णांकerrupt;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3), "=r" (r4)
		: : EV_HCALL_CLOBBERS2
	);

	*msir_val = r4;

	वापस r3;
पूर्ण

/**
 * fh_प्रणाली_reset - reset the प्रणाली
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_प्रणाली_reset(व्योम)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");

	r11 = FH_HCALL_TOKEN(FH_SYSTEM_RESET);

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "=r" (r3)
		: : EV_HCALL_CLOBBERS1
	);

	वापस r3;
पूर्ण


/**
 * fh_err_get_info - get platक्रमm error inक्रमmation
 * @queue id:
 * 0 क्रम guest error event queue
 * 1 क्रम global error event queue
 *
 * @poपूर्णांकer to store the platक्रमm error data:
 * platक्रमm error data is वापसed in रेजिस्टरs r4 - r11
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_err_get_info(पूर्णांक queue, uपूर्णांक32_t *bufsize,
	uपूर्णांक32_t addr_hi, uपूर्णांक32_t addr_lo, पूर्णांक peek)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");
	रेजिस्टर uपूर्णांकptr_t r5 __यंत्र__("r5");
	रेजिस्टर uपूर्णांकptr_t r6 __यंत्र__("r6");
	रेजिस्टर uपूर्णांकptr_t r7 __यंत्र__("r7");

	r11 = FH_HCALL_TOKEN(FH_ERR_GET_INFO);
	r3 = queue;
	r4 = *bufsize;
	r5 = addr_hi;
	r6 = addr_lo;
	r7 = peek;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3), "+r" (r4), "+r" (r5), "+r" (r6),
		  "+r" (r7)
		: : EV_HCALL_CLOBBERS5
	);

	*bufsize = r4;

	वापस r3;
पूर्ण


#घोषणा FH_VCPU_RUN	0
#घोषणा FH_VCPU_IDLE	1
#घोषणा FH_VCPU_NAP	2

/**
 * fh_get_core_state - get the state of a vcpu
 *
 * @handle: handle of partition containing the vcpu
 * @vcpu: vcpu number within the partition
 * @state:the current state of the vcpu, see FH_VCPU_*
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_get_core_state(अचिन्हित पूर्णांक handle,
	अचिन्हित पूर्णांक vcpu, अचिन्हित पूर्णांक *state)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");

	r11 = FH_HCALL_TOKEN(FH_GET_CORE_STATE);
	r3 = handle;
	r4 = vcpu;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3), "+r" (r4)
		: : EV_HCALL_CLOBBERS2
	);

	*state = r4;
	वापस r3;
पूर्ण

/**
 * fh_enter_nap - enter nap on a vcpu
 *
 * Note that though the API supports entering nap on a vcpu other
 * than the caller, this may not be implmented and may वापस EINVAL.
 *
 * @handle: handle of partition containing the vcpu
 * @vcpu: vcpu number within the partition
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_enter_nap(अचिन्हित पूर्णांक handle, अचिन्हित पूर्णांक vcpu)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");

	r11 = FH_HCALL_TOKEN(FH_ENTER_NAP);
	r3 = handle;
	r4 = vcpu;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3), "+r" (r4)
		: : EV_HCALL_CLOBBERS2
	);

	वापस r3;
पूर्ण

/**
 * fh_निकास_nap - निकास nap on a vcpu
 * @handle: handle of partition containing the vcpu
 * @vcpu: vcpu number within the partition
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_निकास_nap(अचिन्हित पूर्णांक handle, अचिन्हित पूर्णांक vcpu)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");
	रेजिस्टर uपूर्णांकptr_t r4 __यंत्र__("r4");

	r11 = FH_HCALL_TOKEN(FH_EXIT_NAP);
	r3 = handle;
	r4 = vcpu;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3), "+r" (r4)
		: : EV_HCALL_CLOBBERS2
	);

	वापस r3;
पूर्ण
/**
 * fh_claim_device - claim a "claimable" shared device
 * @handle: fsl,hv-device-handle of node to claim
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_claim_device(अचिन्हित पूर्णांक handle)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");

	r11 = FH_HCALL_TOKEN(FH_CLAIM_DEVICE);
	r3 = handle;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3)
		: : EV_HCALL_CLOBBERS1
	);

	वापस r3;
पूर्ण

/**
 * Run deferred DMA disabling on a partition's निजी devices
 *
 * This applies to devices which a partition owns either निजीly,
 * or which are claimable and still actively owned by that partition,
 * and which करो not have the no-dma-disable property.
 *
 * @handle: partition (must be stopped) whose DMA is to be disabled
 *
 * Returns 0 क्रम success, or an error code.
 */
अटल अंतरभूत अचिन्हित पूर्णांक fh_partition_stop_dma(अचिन्हित पूर्णांक handle)
अणु
	रेजिस्टर uपूर्णांकptr_t r11 __यंत्र__("r11");
	रेजिस्टर uपूर्णांकptr_t r3 __यंत्र__("r3");

	r11 = FH_HCALL_TOKEN(FH_PARTITION_STOP_DMA);
	r3 = handle;

	यंत्र अस्थिर("bl	epapr_hypercall_start"
		: "+r" (r11), "+r" (r3)
		: : EV_HCALL_CLOBBERS1
	);

	वापस r3;
पूर्ण
#पूर्ण_अगर
