<शैली गुरु>
/*
 * Copyright(c) 2015-2017 Intel Corporation.
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * BSD LICENSE
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *  - Neither the name of Intel Corporation nor the names of its
 *    contributors may be used to enकरोrse or promote products derived
 *    from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
#अगर_अघोषित _ASPM_H
#घोषणा _ASPM_H

#समावेश "hfi.h"

बाह्य uपूर्णांक aspm_mode;

क्रमागत aspm_mode अणु
	ASPM_MODE_DISABLED = 0,	/* ASPM always disabled, perक्रमmance mode */
	ASPM_MODE_ENABLED = 1,	/* ASPM always enabled, घातer saving mode */
	ASPM_MODE_DYNAMIC = 2,	/* ASPM enabled/disabled dynamically */
पूर्ण;

व्योम aspm_init(काष्ठा hfi1_devdata *dd);
व्योम aspm_निकास(काष्ठा hfi1_devdata *dd);
व्योम aspm_hw_disable_l1(काष्ठा hfi1_devdata *dd);
व्योम __aspm_ctx_disable(काष्ठा hfi1_ctxtdata *rcd);
व्योम aspm_disable_all(काष्ठा hfi1_devdata *dd);
व्योम aspm_enable_all(काष्ठा hfi1_devdata *dd);

अटल अंतरभूत व्योम aspm_ctx_disable(काष्ठा hfi1_ctxtdata *rcd)
अणु
	/* Quickest निकास क्रम minimum impact */
	अगर (likely(!rcd->aspm_पूर्णांकr_supported))
		वापस;

	__aspm_ctx_disable(rcd);
पूर्ण

#पूर्ण_अगर /* _ASPM_H */
