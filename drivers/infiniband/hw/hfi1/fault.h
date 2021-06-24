<शैली गुरु>
#अगर_अघोषित _HFI1_FAULT_H
#घोषणा _HFI1_FAULT_H
/*
 * Copyright(c) 2018 Intel Corporation.
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
#समावेश <linux/fault-inject.h>
#समावेश <linux/dcache.h>
#समावेश <linux/bitops.h>
#समावेश <linux/kernel.h>
#समावेश <rdma/rdma_vt.h>

#समावेश "hfi.h"

काष्ठा hfi1_ibdev;

#अगर defined(CONFIG_FAULT_INJECTION) && defined(CONFIG_FAULT_INJECTION_DEBUG_FS)
काष्ठा fault अणु
	काष्ठा fault_attr attr;
	काष्ठा dentry *dir;
	u64 n_rxfaults[(1U << BITS_PER_BYTE)];
	u64 n_txfaults[(1U << BITS_PER_BYTE)];
	u64 fault_skip;
	u64 skip;
	u64 fault_skip_usec;
	अचिन्हित दीर्घ skip_usec;
	अचिन्हित दीर्घ opcodes[(1U << BITS_PER_BYTE) / BITS_PER_LONG];
	bool enable;
	bool suppress_err;
	bool opcode;
	u8 direction;
पूर्ण;

पूर्णांक hfi1_fault_init_debugfs(काष्ठा hfi1_ibdev *ibd);
bool hfi1_dbg_should_fault_tx(काष्ठा rvt_qp *qp, u32 opcode);
bool hfi1_dbg_should_fault_rx(काष्ठा hfi1_packet *packet);
bool hfi1_dbg_fault_suppress_err(काष्ठा hfi1_ibdev *ibd);
व्योम hfi1_fault_निकास_debugfs(काष्ठा hfi1_ibdev *ibd);

#अन्यथा

अटल अंतरभूत पूर्णांक hfi1_fault_init_debugfs(काष्ठा hfi1_ibdev *ibd)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत bool hfi1_dbg_should_fault_rx(काष्ठा hfi1_packet *packet)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool hfi1_dbg_should_fault_tx(काष्ठा rvt_qp *qp,
					    u32 opcode)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत bool hfi1_dbg_fault_suppress_err(काष्ठा hfi1_ibdev *ibd)
अणु
	वापस false;
पूर्ण

अटल अंतरभूत व्योम hfi1_fault_निकास_debugfs(काष्ठा hfi1_ibdev *ibd)
अणु
पूर्ण
#पूर्ण_अगर
#पूर्ण_अगर /* _HFI1_FAULT_H */
