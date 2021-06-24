<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */

#अगर_अघोषित __ASM_CSKY_TCM_H
#घोषणा __ASM_CSKY_TCM_H

#अगर_अघोषित CONFIG_HAVE_TCM
#त्रुटि "You should not be including tcm.h unless you have a TCM!"
#पूर्ण_अगर

#समावेश <linux/compiler.h>

/* Tag variables with this */
#घोषणा __tcmdata __section(".tcm.data")
/* Tag स्थिरants with this */
#घोषणा __tcmस्थिर __section(".tcm.rodata")
/* Tag functions inside TCM called from outside TCM with this */
#घोषणा __tcmfunc __section(".tcm.text") noअंतरभूत
/* Tag function inside TCM called from inside TCM  with this */
#घोषणा __tcmlocalfunc __section(".tcm.text")

व्योम *tcm_alloc(माप_प्रकार len);
व्योम tcm_मुक्त(व्योम *addr, माप_प्रकार len);

#पूर्ण_अगर
