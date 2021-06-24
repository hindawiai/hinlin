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

#अगर_अघोषित _ASM_NLM_XLR_H
#घोषणा _ASM_NLM_XLR_H

/* SMP helpers */
व्योम xlr_wakeup_secondary_cpus(व्योम);

/* XLS B silicon "Rook" */
अटल अंतरभूत अचिन्हित पूर्णांक nlm_chip_is_xls_b(व्योम)
अणु
	uपूर्णांक32_t prid = पढ़ो_c0_prid();

	वापस ((prid & 0xf000) == 0x4000);
पूर्ण

/*  XLR chip types */
/* The XLS product line has chip versions 0x[48c]? */
अटल अंतरभूत अचिन्हित पूर्णांक nlm_chip_is_xls(व्योम)
अणु
	uपूर्णांक32_t prid = पढ़ो_c0_prid();

	वापस ((prid & 0xf000) == 0x8000 || (prid & 0xf000) == 0x4000 ||
		(prid & 0xf000) == 0xc000);
पूर्ण

#पूर्ण_अगर /* _ASM_NLM_XLR_H */
