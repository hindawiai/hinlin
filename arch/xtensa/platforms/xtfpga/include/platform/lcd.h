<शैली गुरु>
/*
 * arch/xtensa/platक्रमm/xtavnet/include/platक्रमm/lcd.h
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001, 2006 Tensilica Inc.
 */

#अगर_अघोषित __XTENSA_XTAVNET_LCD_H
#घोषणा __XTENSA_XTAVNET_LCD_H

#अगर_घोषित CONFIG_XTFPGA_LCD
/* Display string STR at position POS on the LCD. */
व्योम lcd_disp_at_pos(अक्षर *str, अचिन्हित अक्षर pos);

/* Shअगरt the contents of the LCD display left or right. */
व्योम lcd_shअगरtleft(व्योम);
व्योम lcd_shअगरtright(व्योम);
#अन्यथा
अटल अंतरभूत व्योम lcd_disp_at_pos(अक्षर *str, अचिन्हित अक्षर pos)
अणु
पूर्ण

अटल अंतरभूत व्योम lcd_shअगरtleft(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम lcd_shअगरtright(व्योम)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
