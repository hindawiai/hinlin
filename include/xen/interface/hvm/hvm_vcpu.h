<शैली गुरु>
/*
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Copyright (c) 2015, Roger Pau Monne <roger.pau@citrix.com>
 */

#अगर_अघोषित __XEN_PUBLIC_HVM_HVM_VCPU_H__
#घोषणा __XEN_PUBLIC_HVM_HVM_VCPU_H__

#समावेश "../xen.h"

काष्ठा vcpu_hvm_x86_32 अणु
    uपूर्णांक32_t eax;
    uपूर्णांक32_t ecx;
    uपूर्णांक32_t edx;
    uपूर्णांक32_t ebx;
    uपूर्णांक32_t esp;
    uपूर्णांक32_t ebp;
    uपूर्णांक32_t esi;
    uपूर्णांक32_t edi;
    uपूर्णांक32_t eip;
    uपूर्णांक32_t eflags;

    uपूर्णांक32_t cr0;
    uपूर्णांक32_t cr3;
    uपूर्णांक32_t cr4;

    uपूर्णांक32_t pad1;

    /*
     * EFER should only be used to set the NXE bit (अगर required)
     * when starting a vCPU in 32bit mode with paging enabled or
     * to set the LME/LMA bits in order to start the vCPU in
     * compatibility mode.
     */
    uपूर्णांक64_t efer;

    uपूर्णांक32_t cs_base;
    uपूर्णांक32_t ds_base;
    uपूर्णांक32_t ss_base;
    uपूर्णांक32_t es_base;
    uपूर्णांक32_t tr_base;
    uपूर्णांक32_t cs_limit;
    uपूर्णांक32_t ds_limit;
    uपूर्णांक32_t ss_limit;
    uपूर्णांक32_t es_limit;
    uपूर्णांक32_t tr_limit;
    uपूर्णांक16_t cs_ar;
    uपूर्णांक16_t ds_ar;
    uपूर्णांक16_t ss_ar;
    uपूर्णांक16_t es_ar;
    uपूर्णांक16_t tr_ar;

    uपूर्णांक16_t pad2[3];
पूर्ण;

/*
 * The layout of the _ar fields of the segment रेजिस्टरs is the
 * following:
 *
 * Bits   [0,3]: type (bits 40-43).
 * Bit        4: s    (descriptor type, bit 44).
 * Bit    [5,6]: dpl  (descriptor privilege level, bits 45-46).
 * Bit        7: p    (segment-present, bit 47).
 * Bit        8: avl  (available क्रम प्रणाली software, bit 52).
 * Bit        9: l    (64-bit code segment, bit 53).
 * Bit       10: db   (meaning depends on the segment, bit 54).
 * Bit       11: g    (granularity, bit 55)
 * Bits [12,15]: unused, must be blank.
 *
 * A more complete description of the meaning of this fields can be
 * obtained from the Intel SDM, Volume 3, section 3.4.5.
 */

काष्ठा vcpu_hvm_x86_64 अणु
    uपूर्णांक64_t rax;
    uपूर्णांक64_t rcx;
    uपूर्णांक64_t rdx;
    uपूर्णांक64_t rbx;
    uपूर्णांक64_t rsp;
    uपूर्णांक64_t rbp;
    uपूर्णांक64_t rsi;
    uपूर्णांक64_t rdi;
    uपूर्णांक64_t rip;
    uपूर्णांक64_t rflags;

    uपूर्णांक64_t cr0;
    uपूर्णांक64_t cr3;
    uपूर्णांक64_t cr4;
    uपूर्णांक64_t efer;

    /*
     * Using VCPU_HVM_MODE_64B implies that the vCPU is launched
     * directly in दीर्घ mode, so the cached parts of the segment
     * रेजिस्टरs get set to match that environment.
     *
     * If the user wants to launch the vCPU in compatibility mode
     * the 32-bit काष्ठाure should be used instead.
     */
पूर्ण;

काष्ठा vcpu_hvm_context अणु
#घोषणा VCPU_HVM_MODE_32B 0  /* 32bit fields of the काष्ठाure will be used. */
#घोषणा VCPU_HVM_MODE_64B 1  /* 64bit fields of the काष्ठाure will be used. */
    uपूर्णांक32_t mode;

    uपूर्णांक32_t pad;

    /* CPU रेजिस्टरs. */
    जोड़ अणु
        काष्ठा vcpu_hvm_x86_32 x86_32;
        काष्ठा vcpu_hvm_x86_64 x86_64;
    पूर्ण cpu_regs;
पूर्ण;
प्रकार काष्ठा vcpu_hvm_context vcpu_hvm_context_t;

#पूर्ण_अगर /* __XEN_PUBLIC_HVM_HVM_VCPU_H__ */
