<शैली गुरु>
/*
 * Copyright (c) 2017 Oracle and/or its affiliates. All rights reserved.
 */

#अगर_अघोषित _ASM_SPARC_VDSO_H
#घोषणा _ASM_SPARC_VDSO_H

काष्ठा vdso_image अणु
	व्योम *data;
	अचिन्हित दीर्घ size;   /* Always a multiple of PAGE_SIZE */

	दीर्घ sym_vvar_start;  /* Negative offset to the vvar area */
पूर्ण;

#अगर_घोषित CONFIG_SPARC64
बाह्य स्थिर काष्ठा vdso_image vdso_image_64_builtin;
#पूर्ण_अगर
#अगर_घोषित CONFIG_COMPAT
बाह्य स्थिर काष्ठा vdso_image vdso_image_32_builtin;
#पूर्ण_अगर

#पूर्ण_अगर /* _ASM_SPARC_VDSO_H */
