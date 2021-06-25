<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _S390_SECTIONS_H
#घोषणा _S390_SECTIONS_H

#घोषणा arch_is_kernel_iniपंचांगem_मुक्तd arch_is_kernel_iniपंचांगem_मुक्तd

#समावेश <यंत्र-generic/sections.h>

बाह्य bool iniपंचांगem_मुक्तd;

अटल अंतरभूत पूर्णांक arch_is_kernel_iniपंचांगem_मुक्तd(अचिन्हित दीर्घ addr)
अणु
	अगर (!iniपंचांगem_मुक्तd)
		वापस 0;
	वापस addr >= (अचिन्हित दीर्घ)__init_begin &&
	       addr < (अचिन्हित दीर्घ)__init_end;
पूर्ण

/*
 * .boot.data section contains variables "shared" between the decompressor and
 * the decompressed kernel. The decompressor will store values in them, and
 * copy over to the decompressed image beक्रमe starting it.
 *
 * Each variable end up in its own पूर्णांकermediate section .boot.data.<var name>,
 * those sections are later sorted by alignment + name and merged together पूर्णांकo
 * final .boot.data section, which should be identical in the decompressor and
 * the decompressed kernel (that is checked during the build).
 */
#घोषणा __bootdata(var) __section(".boot.data." #var) var

/*
 * .boot.preserved.data is similar to .boot.data, but it is not part of the
 * .init section and thus will be preserved क्रम later use in the decompressed
 * kernel.
 */
#घोषणा __bootdata_preserved(var) __section(".boot.preserved.data." #var) var

बाह्य अचिन्हित दीर्घ __sdma, __edma;
बाह्य अचिन्हित दीर्घ __stext_dma, __etext_dma;

#पूर्ण_अगर
