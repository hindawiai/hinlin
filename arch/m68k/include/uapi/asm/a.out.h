<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
#अगर_अघोषित __M68K_A_OUT_H__
#घोषणा __M68K_A_OUT_H__

काष्ठा exec
अणु
  अचिन्हित दीर्घ a_info;		/* Use macros N_MAGIC, etc क्रम access */
  अचिन्हित a_text;		/* length of text, in bytes */
  अचिन्हित a_data;		/* length of data, in bytes */
  अचिन्हित a_bss;		/* length of uninitialized data area क्रम file, in bytes */
  अचिन्हित a_syms;		/* length of symbol table data in file, in bytes */
  अचिन्हित a_entry;		/* start address */
  अचिन्हित a_trsize;		/* length of relocation info क्रम text, in bytes */
  अचिन्हित a_drsize;		/* length of relocation info क्रम data, in bytes */
पूर्ण;

#घोषणा N_TRSIZE(a)	((a).a_trsize)
#घोषणा N_DRSIZE(a)	((a).a_drsize)
#घोषणा N_SYMSIZE(a)	((a).a_syms)

#पूर्ण_अगर /* __M68K_A_OUT_H__ */
