<शैली गुरु>
/*
 * Copyright 2003-2013 Broadcom Corporation.
 * All Rights Reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the Broadcom
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
 * THIS SOFTWARE IS PROVIDED BY BROADCOM ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL BROADCOM OR CONTRIBUTORS BE LIABLE
 * FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/memblock.h>

#समावेश <linux/of_fdt.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/of_device.h>

#समावेश <यंत्र/prom.h>

बाह्य u32 __dtb_xlp_evp_begin[], __dtb_xlp_svp_begin[], __dtb_xlp_fvp_begin[],
	__dtb_xlp_gvp_begin[], __dtb_xlp_rvp_begin[];
अटल व्योम *xlp_fdt_blob;

व्योम __init *xlp_dt_init(व्योम *fdtp)
अणु
	अगर (!fdtp) अणु
		चयन (current_cpu_data.processor_id & PRID_IMP_MASK) अणु
#अगर_घोषित CONFIG_DT_XLP_RVP
		हाल PRID_IMP_NETLOGIC_XLP5XX:
			fdtp = __dtb_xlp_rvp_begin;
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DT_XLP_GVP
		हाल PRID_IMP_NETLOGIC_XLP9XX:
			fdtp = __dtb_xlp_gvp_begin;
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DT_XLP_FVP
		हाल PRID_IMP_NETLOGIC_XLP2XX:
			fdtp = __dtb_xlp_fvp_begin;
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DT_XLP_SVP
		हाल PRID_IMP_NETLOGIC_XLP3XX:
			fdtp = __dtb_xlp_svp_begin;
			अवरोध;
#पूर्ण_अगर
#अगर_घोषित CONFIG_DT_XLP_EVP
		हाल PRID_IMP_NETLOGIC_XLP8XX:
			fdtp = __dtb_xlp_evp_begin;
			अवरोध;
#पूर्ण_अगर
		शेष:
			/* Pick a built-in अगर any, and hope क्रम the best */
			fdtp = __dtb_start;
			अवरोध;
		पूर्ण
	पूर्ण
	xlp_fdt_blob = fdtp;
	वापस fdtp;
पूर्ण

व्योम __init xlp_early_init_devtree(व्योम)
अणु
	__dt_setup_arch(xlp_fdt_blob);
पूर्ण

व्योम __init device_tree_init(व्योम)
अणु
	unflatten_and_copy_device_tree();
पूर्ण
