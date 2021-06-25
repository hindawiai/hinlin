<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित M68K_PGALLOC_H
#घोषणा M68K_PGALLOC_H

#समावेश <linux/mm.h>
#समावेश <linux/highस्मृति.स>
#समावेश <यंत्र/setup.h>

#अगर_घोषित CONFIG_MMU
#समावेश <यंत्र/virtconvert.h>
#अगर defined(CONFIG_COLDFIRE)
#समावेश <यंत्र/mcf_pgभाग.स>
#या_अगर defined(CONFIG_SUN3)
#समावेश <यंत्र/sun3_pgभाग.स>
#अन्यथा
#समावेश <यंत्र/motorola_pgभाग.स>
#पूर्ण_अगर

बाह्य व्योम m68k_setup_node(पूर्णांक node);
#पूर्ण_अगर

#पूर्ण_अगर /* M68K_PGALLOC_H */
