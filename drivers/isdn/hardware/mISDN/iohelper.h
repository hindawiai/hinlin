<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * iohelper.h
 *		helper क्रम define functions to access ISDN hardware
 *              supported are memory mapped IO
 *		indirect port IO (one port क्रम address, one क्रम data)
 *
 * Author       Karsten Keil <keil@isdn4linux.de>
 *
 * Copyright 2009  by Karsten Keil <keil@isdn4linux.de>
 */

#अगर_अघोषित _IOHELPER_H
#घोषणा _IOHELPER_H

प्रकार u8 (पढ़ो_reg_func)(व्योम *hwp, u8 offset);
प्रकार व्योम (ग_लिखो_reg_func)(व्योम *hwp, u8 offset, u8 value);
प्रकार व्योम (fअगरo_func)(व्योम *hwp, u8 offset, u8 *datap, पूर्णांक size);

काष्ठा _ioport अणु
	u32 port;
	u32 ale;
पूर्ण;

#घोषणा IOFUNC_IO(name, hws, ap)					\
	अटल u8 Read##name##_IO(व्योम *p, u8 off) अणु			\
		काष्ठा hws *hw = p;					\
		वापस inb(hw->ap.port + off);				\
	पूर्ण								\
	अटल व्योम Write##name##_IO(व्योम *p, u8 off, u8 val) अणु		\
		काष्ठा hws *hw = p;					\
		outb(val, hw->ap.port + off);				\
	पूर्ण								\
	अटल व्योम ReadFiFo##name##_IO(व्योम *p, u8 off, u8 *dp, पूर्णांक size) अणु \
		काष्ठा hws *hw = p;					\
		insb(hw->ap.port + off, dp, size);			\
	पूर्ण								\
	अटल व्योम WriteFiFo##name##_IO(व्योम *p, u8 off, u8 *dp, पूर्णांक size) अणु \
		काष्ठा hws *hw = p;					\
		outsb(hw->ap.port + off, dp, size);			\
	पूर्ण

#घोषणा IOFUNC_IND(name, hws, ap)					\
	अटल u8 Read##name##_IND(व्योम *p, u8 off) अणु			\
		काष्ठा hws *hw = p;					\
		outb(off, hw->ap.ale);					\
		वापस inb(hw->ap.port);				\
	पूर्ण								\
	अटल व्योम Write##name##_IND(व्योम *p, u8 off, u8 val) अणु	\
		काष्ठा hws *hw = p;					\
		outb(off, hw->ap.ale);					\
		outb(val, hw->ap.port);					\
	पूर्ण								\
	अटल व्योम ReadFiFo##name##_IND(व्योम *p, u8 off, u8 *dp, पूर्णांक size) अणु \
		काष्ठा hws *hw = p;					\
		outb(off, hw->ap.ale);					\
		insb(hw->ap.port, dp, size);				\
	पूर्ण								\
	अटल व्योम WriteFiFo##name##_IND(व्योम *p, u8 off, u8 *dp, पूर्णांक size) अणु \
		काष्ठा hws *hw = p;					\
		outb(off, hw->ap.ale);					\
		outsb(hw->ap.port, dp, size);				\
	पूर्ण

#घोषणा IOFUNC_MEMIO(name, hws, typ, adr)				\
	अटल u8 Read##name##_MIO(व्योम *p, u8 off) अणु			\
		काष्ठा hws *hw = p;					\
		वापस पढ़ोb(((typ *)hw->adr) + off);			\
	पूर्ण								\
	अटल व्योम Write##name##_MIO(व्योम *p, u8 off, u8 val) अणु	\
		काष्ठा hws *hw = p;					\
		ग_लिखोb(val, ((typ *)hw->adr) + off);			\
	पूर्ण								\
	अटल व्योम ReadFiFo##name##_MIO(व्योम *p, u8 off, u8 *dp, पूर्णांक size) अणु \
		काष्ठा hws *hw = p;					\
		जबतक (size--)						\
			*dp++ = पढ़ोb(((typ *)hw->adr) + off);		\
	पूर्ण								\
	अटल व्योम WriteFiFo##name##_MIO(व्योम *p, u8 off, u8 *dp, पूर्णांक size) अणु \
		काष्ठा hws *hw = p;					\
		जबतक (size--)						\
			ग_लिखोb(*dp++, ((typ *)hw->adr) + off);		\
	पूर्ण

#घोषणा ASSIGN_FUNC(typ, name, dest)	करो अणु			\
		dest.पढ़ो_reg = &Read##name##_##typ;		\
		dest.ग_लिखो_reg = &Write##name##_##typ;		\
		dest.पढ़ो_fअगरo = &ReadFiFo##name##_##typ;	\
		dest.ग_लिखो_fअगरo = &WriteFiFo##name##_##typ;	\
	पूर्ण जबतक (0)
#घोषणा ASSIGN_FUNC_IPAC(typ, target)	करो अणु		\
		ASSIGN_FUNC(typ, ISAC, target.isac);	\
		ASSIGN_FUNC(typ, IPAC, target);		\
	पूर्ण जबतक (0)

#पूर्ण_अगर
