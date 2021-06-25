<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/माला.स>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/pci.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pagemap.h>
#समावेश <linux/console.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/screen_info.h>

#समावेश "sm750.h"
#समावेश "sm750_cursor.h"

#घोषणा poke32(addr, data) \
ग_लिखोl((data), cursor->mmio + (addr))

/* cursor control क्रम voyager and 718/750*/
#घोषणा HWC_ADDRESS                         0x0
#घोषणा HWC_ADDRESS_ENABLE                  BIT(31)
#घोषणा HWC_ADDRESS_EXT                     BIT(27)
#घोषणा HWC_ADDRESS_CS                      BIT(26)
#घोषणा HWC_ADDRESS_ADDRESS_MASK            0x3ffffff

#घोषणा HWC_LOCATION                        0x4
#घोषणा HWC_LOCATION_TOP                    BIT(27)
#घोषणा HWC_LOCATION_Y_SHIFT                16
#घोषणा HWC_LOCATION_Y_MASK                 (0x7ff << 16)
#घोषणा HWC_LOCATION_LEFT                   BIT(11)
#घोषणा HWC_LOCATION_X_MASK                 0x7ff

#घोषणा HWC_COLOR_12                        0x8
#घोषणा HWC_COLOR_12_2_RGB565_SHIFT         16
#घोषणा HWC_COLOR_12_2_RGB565_MASK          (0xffff << 16)
#घोषणा HWC_COLOR_12_1_RGB565_MASK          0xffff

#घोषणा HWC_COLOR_3                         0xC
#घोषणा HWC_COLOR_3_RGB565_MASK             0xffff

/* hw_cursor_xxx works क्रम voyager,718 and 750 */
व्योम sm750_hw_cursor_enable(काष्ठा lynx_cursor *cursor)
अणु
	u32 reg;

	reg = (cursor->offset & HWC_ADDRESS_ADDRESS_MASK) | HWC_ADDRESS_ENABLE;
	poke32(HWC_ADDRESS, reg);
पूर्ण

व्योम sm750_hw_cursor_disable(काष्ठा lynx_cursor *cursor)
अणु
	poke32(HWC_ADDRESS, 0);
पूर्ण

व्योम sm750_hw_cursor_setSize(काष्ठा lynx_cursor *cursor, पूर्णांक w, पूर्णांक h)
अणु
	cursor->w = w;
	cursor->h = h;
पूर्ण

व्योम sm750_hw_cursor_setPos(काष्ठा lynx_cursor *cursor, पूर्णांक x, पूर्णांक y)
अणु
	u32 reg;

	reg = ((y << HWC_LOCATION_Y_SHIFT) & HWC_LOCATION_Y_MASK) |
	       (x & HWC_LOCATION_X_MASK);
	poke32(HWC_LOCATION, reg);
पूर्ण

व्योम sm750_hw_cursor_setColor(काष्ठा lynx_cursor *cursor, u32 fg, u32 bg)
अणु
	u32 reg = (fg << HWC_COLOR_12_2_RGB565_SHIFT) &
		HWC_COLOR_12_2_RGB565_MASK;

	poke32(HWC_COLOR_12, reg | (bg & HWC_COLOR_12_1_RGB565_MASK));
	poke32(HWC_COLOR_3, 0xffe0);
पूर्ण

व्योम sm750_hw_cursor_setData(काष्ठा lynx_cursor *cursor, u16 rop,
			     स्थिर u8 *pcol, स्थिर u8 *pmsk)
अणु
	पूर्णांक i, j, count, pitch, offset;
	u8 color, mask, opr;
	u16 data;
	व्योम __iomem *pbuffer, *pstart;

	/*  in byte*/
	pitch = cursor->w >> 3;

	/* in byte	*/
	count = pitch * cursor->h;

	/* in byte */
	offset = cursor->maxW * 2 / 8;

	data = 0;
	pstart = cursor->vstart;
	pbuffer = pstart;

	क्रम (i = 0; i < count; i++) अणु
		color = *pcol++;
		mask = *pmsk++;
		data = 0;

		क्रम (j = 0; j < 8; j++) अणु
			अगर (mask & (0x80 >> j)) अणु
				अगर (rop == ROP_XOR)
					opr = mask ^ color;
				अन्यथा
					opr = mask & color;

				/* 2 stands क्रम क्रमecolor and 1 क्रम backcolor */
				data |= ((opr & (0x80 >> j)) ? 2 : 1) << (j * 2);
			पूर्ण
		पूर्ण
		ioग_लिखो16(data, pbuffer);

		/* assume pitch is 1,2,4,8,...*/
		अगर ((i + 1) % pitch == 0) अणु
			/* need a वापस */
			pstart += offset;
			pbuffer = pstart;
		पूर्ण अन्यथा अणु
			pbuffer += माप(u16);
		पूर्ण
	पूर्ण
पूर्ण

व्योम sm750_hw_cursor_setData2(काष्ठा lynx_cursor *cursor, u16 rop,
			      स्थिर u8 *pcol, स्थिर u8 *pmsk)
अणु
	पूर्णांक i, j, count, pitch, offset;
	u8 color, mask;
	u16 data;
	व्योम __iomem *pbuffer, *pstart;

	/*  in byte*/
	pitch = cursor->w >> 3;

	/* in byte	*/
	count = pitch * cursor->h;

	/* in byte */
	offset = cursor->maxW * 2 / 8;

	data = 0;
	pstart = cursor->vstart;
	pbuffer = pstart;

	क्रम (i = 0; i < count; i++) अणु
		color = *pcol++;
		mask = *pmsk++;
		data = 0;

		क्रम (j = 0; j < 8; j++) अणु
			अगर (mask & (1 << j))
				data |= ((color & (1 << j)) ? 1 : 2) << (j * 2);
		पूर्ण
		ioग_लिखो16(data, pbuffer);

		/* assume pitch is 1,2,4,8,...*/
		अगर (!(i & (pitch - 1))) अणु
			/* need a वापस */
			pstart += offset;
			pbuffer = pstart;
		पूर्ण अन्यथा अणु
			pbuffer += माप(u16);
		पूर्ण
	पूर्ण
पूर्ण
