<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Routines to test क्रम presence/असलence of hardware रेजिस्टरs:
 * see arch/m68k/mm/hwtest.c.
 *  -- PMM <pmaydell@chiark.greenend.org.uk> 05/1998
 *
 * Removed __init from decls.  We might want them in modules, and
 * the code is tiny anyway.  16/5/98 pb
 */

#अगर_अघोषित __ASM_HWTEST_H
#घोषणा __ASM_HWTEST_H

बाह्य पूर्णांक hwreg_present(अस्थिर व्योम *regp);
बाह्य पूर्णांक hwreg_ग_लिखो(अस्थिर व्योम *regp, अचिन्हित लघु val);

#पूर्ण_अगर
