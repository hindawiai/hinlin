<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *  cx18 driver PCI memory mapped IO access routines
 *
 *  Copyright (C) 2007  Hans Verkuil <hverkuil@xs4all.nl>
 *  Copyright (C) 2008  Andy Walls <awalls@md.metrocast.net>
 */

#अगर_अघोषित CX18_IO_H
#घोषणा CX18_IO_H

#समावेश "cx18-driver.h"

/*
 * Readback and retry of MMIO access क्रम reliability:
 * The concept was suggested by Steve Toth <stoth@linuxtv.org>.
 * The implementation is the fault of Andy Walls <awalls@md.metrocast.net>.
 *
 * *ग_लिखो* functions are implied to retry the mmio unless suffixed with _noretry
 * *पढ़ो* functions never retry the mmio (it never helps to करो so)
 */

/* Non byteswapping memory mapped IO */
अटल अंतरभूत u32 cx18_raw_पढ़ोl(काष्ठा cx18 *cx, स्थिर व्योम __iomem *addr)
अणु
	वापस __raw_पढ़ोl(addr);
पूर्ण

अटल अंतरभूत
व्योम cx18_raw_ग_लिखोl_noretry(काष्ठा cx18 *cx, u32 val, व्योम __iomem *addr)
अणु
	__raw_ग_लिखोl(val, addr);
पूर्ण

अटल अंतरभूत व्योम cx18_raw_ग_लिखोl(काष्ठा cx18 *cx, u32 val, व्योम __iomem *addr)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < CX18_MAX_MMIO_WR_RETRIES; i++) अणु
		cx18_raw_ग_लिखोl_noretry(cx, val, addr);
		अगर (val == cx18_raw_पढ़ोl(cx, addr))
			अवरोध;
	पूर्ण
पूर्ण

/* Normal memory mapped IO */
अटल अंतरभूत u32 cx18_पढ़ोl(काष्ठा cx18 *cx, स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोl(addr);
पूर्ण

अटल अंतरभूत
व्योम cx18_ग_लिखोl_noretry(काष्ठा cx18 *cx, u32 val, व्योम __iomem *addr)
अणु
	ग_लिखोl(val, addr);
पूर्ण

अटल अंतरभूत व्योम cx18_ग_लिखोl(काष्ठा cx18 *cx, u32 val, व्योम __iomem *addr)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < CX18_MAX_MMIO_WR_RETRIES; i++) अणु
		cx18_ग_लिखोl_noretry(cx, val, addr);
		अगर (val == cx18_पढ़ोl(cx, addr))
			अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत
व्योम cx18_ग_लिखोl_expect(काष्ठा cx18 *cx, u32 val, व्योम __iomem *addr,
			u32 eval, u32 mask)
अणु
	पूर्णांक i;
	u32 r;
	eval &= mask;
	क्रम (i = 0; i < CX18_MAX_MMIO_WR_RETRIES; i++) अणु
		cx18_ग_लिखोl_noretry(cx, val, addr);
		r = cx18_पढ़ोl(cx, addr);
		अगर (r == 0xffffffff && eval != 0xffffffff)
			जारी;
		अगर (eval == (r & mask))
			अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत u16 cx18_पढ़ोw(काष्ठा cx18 *cx, स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोw(addr);
पूर्ण

अटल अंतरभूत
व्योम cx18_ग_लिखोw_noretry(काष्ठा cx18 *cx, u16 val, व्योम __iomem *addr)
अणु
	ग_लिखोw(val, addr);
पूर्ण

अटल अंतरभूत व्योम cx18_ग_लिखोw(काष्ठा cx18 *cx, u16 val, व्योम __iomem *addr)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < CX18_MAX_MMIO_WR_RETRIES; i++) अणु
		cx18_ग_लिखोw_noretry(cx, val, addr);
		अगर (val == cx18_पढ़ोw(cx, addr))
			अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत u8 cx18_पढ़ोb(काष्ठा cx18 *cx, स्थिर व्योम __iomem *addr)
अणु
	वापस पढ़ोb(addr);
पूर्ण

अटल अंतरभूत
व्योम cx18_ग_लिखोb_noretry(काष्ठा cx18 *cx, u8 val, व्योम __iomem *addr)
अणु
	ग_लिखोb(val, addr);
पूर्ण

अटल अंतरभूत व्योम cx18_ग_लिखोb(काष्ठा cx18 *cx, u8 val, व्योम __iomem *addr)
अणु
	पूर्णांक i;
	क्रम (i = 0; i < CX18_MAX_MMIO_WR_RETRIES; i++) अणु
		cx18_ग_लिखोb_noretry(cx, val, addr);
		अगर (val == cx18_पढ़ोb(cx, addr))
			अवरोध;
	पूर्ण
पूर्ण

अटल अंतरभूत
व्योम cx18_स_नकल_fromio(काष्ठा cx18 *cx, व्योम *to,
			स्थिर व्योम __iomem *from, अचिन्हित पूर्णांक len)
अणु
	स_नकल_fromio(to, from, len);
पूर्ण

व्योम cx18_स_रखो_io(काष्ठा cx18 *cx, व्योम __iomem *addr, पूर्णांक val, माप_प्रकार count);


/* Access "register" region of CX23418 memory mapped I/O */
अटल अंतरभूत व्योम cx18_ग_लिखो_reg_noretry(काष्ठा cx18 *cx, u32 val, u32 reg)
अणु
	cx18_ग_लिखोl_noretry(cx, val, cx->reg_mem + reg);
पूर्ण

अटल अंतरभूत व्योम cx18_ग_लिखो_reg(काष्ठा cx18 *cx, u32 val, u32 reg)
अणु
	cx18_ग_लिखोl(cx, val, cx->reg_mem + reg);
पूर्ण

अटल अंतरभूत व्योम cx18_ग_लिखो_reg_expect(काष्ठा cx18 *cx, u32 val, u32 reg,
					 u32 eval, u32 mask)
अणु
	cx18_ग_लिखोl_expect(cx, val, cx->reg_mem + reg, eval, mask);
पूर्ण

अटल अंतरभूत u32 cx18_पढ़ो_reg(काष्ठा cx18 *cx, u32 reg)
अणु
	वापस cx18_पढ़ोl(cx, cx->reg_mem + reg);
पूर्ण


/* Access "encoder memory" region of CX23418 memory mapped I/O */
अटल अंतरभूत व्योम cx18_ग_लिखो_enc(काष्ठा cx18 *cx, u32 val, u32 addr)
अणु
	cx18_ग_लिखोl(cx, val, cx->enc_mem + addr);
पूर्ण

अटल अंतरभूत u32 cx18_पढ़ो_enc(काष्ठा cx18 *cx, u32 addr)
अणु
	वापस cx18_पढ़ोl(cx, cx->enc_mem + addr);
पूर्ण

व्योम cx18_sw1_irq_enable(काष्ठा cx18 *cx, u32 val);
व्योम cx18_sw1_irq_disable(काष्ठा cx18 *cx, u32 val);
व्योम cx18_sw2_irq_enable(काष्ठा cx18 *cx, u32 val);
व्योम cx18_sw2_irq_disable(काष्ठा cx18 *cx, u32 val);
व्योम cx18_sw2_irq_disable_cpu(काष्ठा cx18 *cx, u32 val);
व्योम cx18_setup_page(काष्ठा cx18 *cx, u32 addr);

#पूर्ण_अगर /* CX18_IO_H */
