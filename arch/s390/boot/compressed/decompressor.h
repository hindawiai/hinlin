<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित BOOT_COMPRESSED_DECOMPRESSOR_H
#घोषणा BOOT_COMPRESSED_DECOMPRESSOR_H

#समावेश <linux/मानकघोष.स>

#अगर_घोषित CONFIG_KERNEL_UNCOMPRESSED
अटल अंतरभूत व्योम *decompress_kernel(व्योम) अणु वापस शून्य; पूर्ण
#अन्यथा
व्योम *decompress_kernel(व्योम);
#पूर्ण_अगर
अचिन्हित दीर्घ mem_safe_offset(व्योम);
व्योम error(अक्षर *m);

काष्ठा vmlinux_info अणु
	अचिन्हित दीर्घ शेष_lma;
	व्योम (*entry)(व्योम);
	अचिन्हित दीर्घ image_size;	/* करोes not include .bss */
	अचिन्हित दीर्घ bss_size;		/* uncompressed image .bss size */
	अचिन्हित दीर्घ bootdata_off;
	अचिन्हित दीर्घ bootdata_size;
	अचिन्हित दीर्घ bootdata_preserved_off;
	अचिन्हित दीर्घ bootdata_preserved_size;
	अचिन्हित दीर्घ dynsym_start;
	अचिन्हित दीर्घ rela_dyn_start;
	अचिन्हित दीर्घ rela_dyn_end;
पूर्ण;

बाह्य अक्षर _vmlinux_info[];
#घोषणा vmlinux (*(काष्ठा vmlinux_info *)_vmlinux_info)

#पूर्ण_अगर /* BOOT_COMPRESSED_DECOMPRESSOR_H */
