<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _BPF_JIT_H
#घोषणा _BPF_JIT_H

/* Conventions:
 *  %g1 : temporary
 *  %g2 : Secondary temporary used by SKB data helper stubs.
 *  %g3 : packet offset passed पूर्णांकo SKB data helper stubs.
 *  %o0 : poपूर्णांकer to skb (first argument given to JIT function)
 *  %o1 : BPF A accumulator
 *  %o2 : BPF X accumulator
 *  %o3 : Holds saved %o7 so we can call helper functions without needing
 *        to allocate a रेजिस्टर winकरोw.
 *  %o4 : skb->len - skb->data_len
 *  %o5 : skb->data
 */

#अगर_अघोषित __ASSEMBLER__
#घोषणा G0		0x00
#घोषणा G1		0x01
#घोषणा G3		0x03
#घोषणा G6		0x06
#घोषणा O0		0x08
#घोषणा O1		0x09
#घोषणा O2		0x0a
#घोषणा O3		0x0b
#घोषणा O4		0x0c
#घोषणा O5		0x0d
#घोषणा SP		0x0e
#घोषणा O7		0x0f
#घोषणा FP		0x1e

#घोषणा r_SKB		O0
#घोषणा r_A		O1
#घोषणा r_X		O2
#घोषणा r_saved_O7	O3
#घोषणा r_HEADLEN	O4
#घोषणा r_SKB_DATA	O5
#घोषणा r_TMP		G1
#घोषणा r_TMP2		G2
#घोषणा r_OFF		G3

/* assembly code in arch/sparc/net/bpf_jit_यंत्र_32.S */
बाह्य u32 bpf_jit_load_word[];
बाह्य u32 bpf_jit_load_half[];
बाह्य u32 bpf_jit_load_byte[];
बाह्य u32 bpf_jit_load_byte_msh[];
बाह्य u32 bpf_jit_load_word_positive_offset[];
बाह्य u32 bpf_jit_load_half_positive_offset[];
बाह्य u32 bpf_jit_load_byte_positive_offset[];
बाह्य u32 bpf_jit_load_byte_msh_positive_offset[];
बाह्य u32 bpf_jit_load_word_negative_offset[];
बाह्य u32 bpf_jit_load_half_negative_offset[];
बाह्य u32 bpf_jit_load_byte_negative_offset[];
बाह्य u32 bpf_jit_load_byte_msh_negative_offset[];

#अन्यथा
#घोषणा r_SKB		%o0
#घोषणा r_A		%o1
#घोषणा r_X		%o2
#घोषणा r_saved_O7	%o3
#घोषणा r_HEADLEN	%o4
#घोषणा r_SKB_DATA	%o5
#घोषणा r_TMP		%g1
#घोषणा r_TMP2		%g2
#घोषणा r_OFF		%g3
#पूर्ण_अगर

#पूर्ण_अगर /* _BPF_JIT_H */
