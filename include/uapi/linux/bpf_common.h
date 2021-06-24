<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI__LINUX_BPF_COMMON_H__
#घोषणा _UAPI__LINUX_BPF_COMMON_H__

/* Inकाष्ठाion classes */
#घोषणा BPF_CLASS(code) ((code) & 0x07)
#घोषणा		BPF_LD		0x00
#घोषणा		BPF_LDX		0x01
#घोषणा		BPF_ST		0x02
#घोषणा		BPF_STX		0x03
#घोषणा		BPF_ALU		0x04
#घोषणा		BPF_JMP		0x05
#घोषणा		BPF_RET		0x06
#घोषणा		BPF_MISC        0x07

/* ld/ldx fields */
#घोषणा BPF_SIZE(code)  ((code) & 0x18)
#घोषणा		BPF_W		0x00 /* 32-bit */
#घोषणा		BPF_H		0x08 /* 16-bit */
#घोषणा		BPF_B		0x10 /*  8-bit */
/* eBPF		BPF_DW		0x18    64-bit */
#घोषणा BPF_MODE(code)  ((code) & 0xe0)
#घोषणा		BPF_IMM		0x00
#घोषणा		BPF_ABS		0x20
#घोषणा		BPF_IND		0x40
#घोषणा		BPF_MEM		0x60
#घोषणा		BPF_LEN		0x80
#घोषणा		BPF_MSH		0xa0

/* alu/jmp fields */
#घोषणा BPF_OP(code)    ((code) & 0xf0)
#घोषणा		BPF_ADD		0x00
#घोषणा		BPF_SUB		0x10
#घोषणा		BPF_MUL		0x20
#घोषणा		BPF_DIV		0x30
#घोषणा		BPF_OR		0x40
#घोषणा		BPF_AND		0x50
#घोषणा		BPF_LSH		0x60
#घोषणा		BPF_RSH		0x70
#घोषणा		BPF_NEG		0x80
#घोषणा		BPF_MOD		0x90
#घोषणा		BPF_XOR		0xa0

#घोषणा		BPF_JA		0x00
#घोषणा		BPF_JEQ		0x10
#घोषणा		BPF_JGT		0x20
#घोषणा		BPF_JGE		0x30
#घोषणा		BPF_JSET        0x40
#घोषणा BPF_SRC(code)   ((code) & 0x08)
#घोषणा		BPF_K		0x00
#घोषणा		BPF_X		0x08

#अगर_अघोषित BPF_MAXINSNS
#घोषणा BPF_MAXINSNS 4096
#पूर्ण_अगर

#पूर्ण_अगर /* _UAPI__LINUX_BPF_COMMON_H__ */
