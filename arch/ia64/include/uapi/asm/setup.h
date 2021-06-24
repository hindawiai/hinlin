<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __IA64_SETUP_H
#घोषणा __IA64_SETUP_H

#घोषणा COMMAND_LINE_SIZE	2048

बाह्य काष्ठा ia64_boot_param अणु
	__u64 command_line;		/* physical address of command line arguments */
	__u64 efi_systab;		/* physical address of EFI प्रणाली table */
	__u64 efi_memmap;		/* physical address of EFI memory map */
	__u64 efi_memmap_size;		/* size of EFI memory map */
	__u64 efi_memdesc_size;		/* size of an EFI memory map descriptor */
	__u32 efi_memdesc_version;	/* memory descriptor version */
	काष्ठा अणु
		__u16 num_cols;	/* number of columns on console output device */
		__u16 num_rows;	/* number of rows on console output device */
		__u16 orig_x;	/* cursor's x position */
		__u16 orig_y;	/* cursor's y position */
	पूर्ण console_info;
	__u64 fpswa;		/* physical address of the fpswa पूर्णांकerface */
	__u64 initrd_start;
	__u64 initrd_size;
पूर्ण *ia64_boot_param;

#पूर्ण_अगर
