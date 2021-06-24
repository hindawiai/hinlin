<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित _UAPI_UVESAFB_H
#घोषणा _UAPI_UVESAFB_H

#समावेश <linux/types.h>

काष्ठा v86_regs अणु
	__u32 ebx;
	__u32 ecx;
	__u32 edx;
	__u32 esi;
	__u32 edi;
	__u32 ebp;
	__u32 eax;
	__u32 eip;
	__u32 eflags;
	__u32 esp;
	__u16 cs;
	__u16 ss;
	__u16 es;
	__u16 ds;
	__u16 fs;
	__u16 gs;
पूर्ण;

/* Task flags */
#घोषणा TF_VBEIB	0x01
#घोषणा TF_BUF_ESDI	0x02
#घोषणा TF_BUF_ESBX	0x04
#घोषणा TF_BUF_RET	0x08
#घोषणा TF_EXIT		0x10

काष्ठा uvesafb_task अणु
	__u8 flags;
	पूर्णांक buf_len;
	काष्ठा v86_regs regs;
पूर्ण;

/* Constants क्रम the capabilities field
 * in vbe_ib */
#घोषणा VBE_CAP_CAN_SWITCH_DAC	0x01
#घोषणा VBE_CAP_VGACOMPAT	0x02

/* The VBE Info Block */
काष्ठा vbe_ib अणु
	अक्षर  vbe_signature[4];
	__u16 vbe_version;
	__u32 oem_string_ptr;
	__u32 capabilities;
	__u32 mode_list_ptr;
	__u16 total_memory;
	__u16 oem_software_rev;
	__u32 oem_venकरोr_name_ptr;
	__u32 oem_product_name_ptr;
	__u32 oem_product_rev_ptr;
	__u8  reserved[222];
	अक्षर  oem_data[256];
	अक्षर  misc_data[512];
पूर्ण __attribute__ ((packed));

#पूर्ण_अगर /* _UAPI_UVESAFB_H */
