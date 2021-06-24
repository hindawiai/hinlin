<शैली गुरु>
/* SPDX-License-Identअगरier: (LGPL-2.1 OR BSD-2-Clause) */
#अगर_अघोषित __BPF_LEGACY__
#घोषणा __BPF_LEGACY__

#घोषणा BPF_ANNOTATE_KV_PAIR(name, type_key, type_val)		\
	काष्ठा ____btf_map_##name अणु				\
		type_key key;					\
		type_val value;					\
	पूर्ण;							\
	काष्ठा ____btf_map_##name				\
	__attribute__ ((section(".maps." #name), used))		\
		____btf_map_##name = अणु पूर्ण

/* llvm builtin functions that eBPF C program may use to
 * emit BPF_LD_ABS and BPF_LD_IND inकाष्ठाions
 */
अचिन्हित दीर्घ दीर्घ load_byte(व्योम *skb,
			     अचिन्हित दीर्घ दीर्घ off) यंत्र("llvm.bpf.load.byte");
अचिन्हित दीर्घ दीर्घ load_half(व्योम *skb,
			     अचिन्हित दीर्घ दीर्घ off) यंत्र("llvm.bpf.load.half");
अचिन्हित दीर्घ दीर्घ load_word(व्योम *skb,
			     अचिन्हित दीर्घ दीर्घ off) यंत्र("llvm.bpf.load.word");

#पूर्ण_अगर

