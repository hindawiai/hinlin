<शैली गुरु>
/*
 * Copyright 2018 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a
 * copy of this software and associated करोcumentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modअगरy, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#अगर_अघोषित __VCN_V2_0_H__
#घोषणा __VCN_V2_0_H__

बाह्य व्योम vcn_v2_0_dec_ring_insert_start(काष्ठा amdgpu_ring *ring);
बाह्य व्योम vcn_v2_0_dec_ring_insert_end(काष्ठा amdgpu_ring *ring);
बाह्य व्योम vcn_v2_0_dec_ring_insert_nop(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t count);
बाह्य व्योम vcn_v2_0_dec_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr, u64 seq,
				अचिन्हित flags);
बाह्य व्योम vcn_v2_0_dec_ring_emit_ib(काष्ठा amdgpu_ring *ring, काष्ठा amdgpu_job *job,
				काष्ठा amdgpu_ib *ib, uपूर्णांक32_t flags);
बाह्य व्योम vcn_v2_0_dec_ring_emit_reg_रुको(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t reg,
				uपूर्णांक32_t val, uपूर्णांक32_t mask);
बाह्य व्योम vcn_v2_0_dec_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
				अचिन्हित vmid, uपूर्णांक64_t pd_addr);
बाह्य व्योम vcn_v2_0_dec_ring_emit_wreg(काष्ठा amdgpu_ring *ring,
				uपूर्णांक32_t reg, uपूर्णांक32_t val);
बाह्य पूर्णांक vcn_v2_0_dec_ring_test_ring(काष्ठा amdgpu_ring *ring);

बाह्य व्योम vcn_v2_0_enc_ring_insert_end(काष्ठा amdgpu_ring *ring);
बाह्य व्योम vcn_v2_0_enc_ring_emit_fence(काष्ठा amdgpu_ring *ring, u64 addr,
				u64 seq, अचिन्हित flags);
बाह्य व्योम vcn_v2_0_enc_ring_emit_ib(काष्ठा amdgpu_ring *ring, काष्ठा amdgpu_job *job,
				काष्ठा amdgpu_ib *ib, uपूर्णांक32_t flags);
बाह्य व्योम vcn_v2_0_enc_ring_emit_reg_रुको(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t reg,
				uपूर्णांक32_t val, uपूर्णांक32_t mask);
बाह्य व्योम vcn_v2_0_enc_ring_emit_vm_flush(काष्ठा amdgpu_ring *ring,
				अचिन्हित पूर्णांक vmid, uपूर्णांक64_t pd_addr);
बाह्य व्योम vcn_v2_0_enc_ring_emit_wreg(काष्ठा amdgpu_ring *ring, uपूर्णांक32_t reg, uपूर्णांक32_t val);

बाह्य स्थिर काष्ठा amdgpu_ip_block_version vcn_v2_0_ip_block;

#पूर्ण_अगर /* __VCN_V2_0_H__ */
