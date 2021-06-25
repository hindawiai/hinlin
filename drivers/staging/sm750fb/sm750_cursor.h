<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित LYNX_CURSOR_H__
#घोषणा LYNX_CURSOR_H__

/* hw_cursor_xxx works क्रम voyager,718 and 750 */
व्योम sm750_hw_cursor_enable(काष्ठा lynx_cursor *cursor);
व्योम sm750_hw_cursor_disable(काष्ठा lynx_cursor *cursor);
व्योम sm750_hw_cursor_setSize(काष्ठा lynx_cursor *cursor, पूर्णांक w, पूर्णांक h);
व्योम sm750_hw_cursor_setPos(काष्ठा lynx_cursor *cursor, पूर्णांक x, पूर्णांक y);
व्योम sm750_hw_cursor_setColor(काष्ठा lynx_cursor *cursor, u32 fg, u32 bg);
व्योम sm750_hw_cursor_setData(काष्ठा lynx_cursor *cursor, u16 rop,
			     स्थिर u8 *data, स्थिर u8 *mask);
व्योम sm750_hw_cursor_setData2(काष्ठा lynx_cursor *cursor, u16 rop,
			      स्थिर u8 *data, स्थिर u8 *mask);
#पूर्ण_अगर
