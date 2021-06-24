<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  cx18 driver PCI memory mapped IO access routines
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#समावेश "cx18-driver.h"
#समावेश "cx18-io.h"
#समावेश "cx18-irq.h"

व्योम cx18_स_रखो_io(काष्ठा cx18 *cx, व्योम __iomem *addr, पूर्णांक val, माप_प्रकार count)
अणु
	u8 __iomem *dst = addr;
	u16 val2 = val | (val << 8);
	u32 val4 = val2 | (val2 << 16);

	/* Align ग_लिखोs on the CX23418's addresses */
	अगर ((count > 0) && ((अचिन्हित दीर्घ)dst & 1)) अणु
		cx18_ग_लिखोb(cx, (u8) val, dst);
		count--;
		dst++;
	पूर्ण
	अगर ((count > 1) && ((अचिन्हित दीर्घ)dst & 2)) अणु
		cx18_ग_लिखोw(cx, val2, dst);
		count -= 2;
		dst += 2;
	पूर्ण
	जबतक (count > 3) अणु
		cx18_ग_लिखोl(cx, val4, dst);
		count -= 4;
		dst += 4;
	पूर्ण
	अगर (count > 1) अणु
		cx18_ग_लिखोw(cx, val2, dst);
		count -= 2;
		dst += 2;
	पूर्ण
	अगर (count > 0)
		cx18_ग_लिखोb(cx, (u8) val, dst);
पूर्ण

व्योम cx18_sw1_irq_enable(काष्ठा cx18 *cx, u32 val)
अणु
	cx18_ग_लिखो_reg_expect(cx, val, SW1_INT_STATUS, ~val, val);
	cx->sw1_irq_mask = cx18_पढ़ो_reg(cx, SW1_INT_ENABLE_PCI) | val;
	cx18_ग_लिखो_reg(cx, cx->sw1_irq_mask, SW1_INT_ENABLE_PCI);
पूर्ण

व्योम cx18_sw1_irq_disable(काष्ठा cx18 *cx, u32 val)
अणु
	cx->sw1_irq_mask = cx18_पढ़ो_reg(cx, SW1_INT_ENABLE_PCI) & ~val;
	cx18_ग_लिखो_reg(cx, cx->sw1_irq_mask, SW1_INT_ENABLE_PCI);
पूर्ण

व्योम cx18_sw2_irq_enable(काष्ठा cx18 *cx, u32 val)
अणु
	cx18_ग_लिखो_reg_expect(cx, val, SW2_INT_STATUS, ~val, val);
	cx->sw2_irq_mask = cx18_पढ़ो_reg(cx, SW2_INT_ENABLE_PCI) | val;
	cx18_ग_लिखो_reg(cx, cx->sw2_irq_mask, SW2_INT_ENABLE_PCI);
पूर्ण

व्योम cx18_sw2_irq_disable(काष्ठा cx18 *cx, u32 val)
अणु
	cx->sw2_irq_mask = cx18_पढ़ो_reg(cx, SW2_INT_ENABLE_PCI) & ~val;
	cx18_ग_लिखो_reg(cx, cx->sw2_irq_mask, SW2_INT_ENABLE_PCI);
पूर्ण

व्योम cx18_sw2_irq_disable_cpu(काष्ठा cx18 *cx, u32 val)
अणु
	u32 r;
	r = cx18_पढ़ो_reg(cx, SW2_INT_ENABLE_CPU);
	cx18_ग_लिखो_reg(cx, r & ~val, SW2_INT_ENABLE_CPU);
पूर्ण

व्योम cx18_setup_page(काष्ठा cx18 *cx, u32 addr)
अणु
	u32 val;
	val = cx18_पढ़ो_reg(cx, 0xD000F8);
	val = (val & ~0x1f00) | ((addr >> 17) & 0x1f00);
	cx18_ग_लिखो_reg(cx, val, 0xD000F8);
पूर्ण
