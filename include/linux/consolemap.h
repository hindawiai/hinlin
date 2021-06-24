<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * consolemap.h
 *
 * Interface between console.c, selection.c  and consolemap.c
 */
#अगर_अघोषित __LINUX_CONSOLEMAP_H__
#घोषणा __LINUX_CONSOLEMAP_H__

#घोषणा LAT1_MAP 0
#घोषणा GRAF_MAP 1
#घोषणा IBMPC_MAP 2
#घोषणा USER_MAP 3

#समावेश <linux/types.h>

#अगर_घोषित CONFIG_CONSOLE_TRANSLATIONS
काष्ठा vc_data;

बाह्य u16 inverse_translate(स्थिर काष्ठा vc_data *conp, पूर्णांक glyph,
		पूर्णांक use_unicode);
बाह्य अचिन्हित लघु *set_translate(पूर्णांक m, काष्ठा vc_data *vc);
बाह्य पूर्णांक conv_uni_to_pc(काष्ठा vc_data *conp, दीर्घ ucs);
बाह्य u32 conv_8bit_to_uni(अचिन्हित अक्षर c);
बाह्य पूर्णांक conv_uni_to_8bit(u32 uni);
व्योम console_map_init(व्योम);
#अन्यथा
#घोषणा inverse_translate(conp, glyph, uni) ((uपूर्णांक16_t)glyph)
#घोषणा set_translate(m, vc) ((अचिन्हित लघु *)शून्य)
#घोषणा conv_uni_to_pc(conp, ucs) ((पूर्णांक) (ucs > 0xff ? -1: ucs))
#घोषणा conv_8bit_to_uni(c) ((uपूर्णांक32_t)(c))
#घोषणा conv_uni_to_8bit(c) ((पूर्णांक) ((c) & 0xff))
#घोषणा console_map_init(c) करो अणु ; पूर्ण जबतक (0)
#पूर्ण_अगर /* CONFIG_CONSOLE_TRANSLATIONS */

#पूर्ण_अगर /* __LINUX_CONSOLEMAP_H__ */
