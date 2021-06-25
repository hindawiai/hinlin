<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __H8300_LIBGCC_H__
#घोषणा __H8300_LIBGCC_H__

#अगर_घोषित __ASSEMBLY__
#घोषणा A0 r0
#घोषणा A0L r0l
#घोषणा A0H r0h

#घोषणा A1 r1
#घोषणा A1L r1l
#घोषणा A1H r1h

#घोषणा A2 r2
#घोषणा A2L r2l
#घोषणा A2H r2h

#घोषणा A3 r3
#घोषणा A3L r3l
#घोषणा A3H r3h

#घोषणा S0 r4
#घोषणा S0L r4l
#घोषणा S0H r4h

#घोषणा S1 r5
#घोषणा S1L r5l
#घोषणा S1H r5h

#घोषणा S2 r6
#घोषणा S2L r6l
#घोषणा S2H r6h

#घोषणा PUSHP	push.l
#घोषणा POPP	pop.l

#घोषणा A0P	er0
#घोषणा A1P	er1
#घोषणा A2P	er2
#घोषणा A3P	er3
#घोषणा S0P	er4
#घोषणा S1P	er5
#घोषणा S2P	er6

#घोषणा A0E	e0
#घोषणा A1E	e1
#घोषणा A2E	e2
#घोषणा A3E	e3
#अन्यथा
#घोषणा Wtype   SItype
#घोषणा UWtype  USItype
#घोषणा HWtype  SItype
#घोषणा UHWtype USItype
#घोषणा DWtype  DItype
#घोषणा UDWtype UDItype
#घोषणा UWtype  USItype
#घोषणा Wtype   SItype
#घोषणा UWtype  USItype
#घोषणा W_TYPE_SIZE (4 * BITS_PER_UNIT)
#घोषणा BITS_PER_UNIT (8)

प्रकार          पूर्णांक SItype     __attribute__ ((mode (SI)));
प्रकार अचिन्हित पूर्णांक USItype    __attribute__ ((mode (SI)));
प्रकार		 पूर्णांक DItype	__attribute__ ((mode (DI)));
प्रकार अचिन्हित पूर्णांक UDItype	__attribute__ ((mode (DI)));
काष्ठा DWकाष्ठा अणु
	Wtype high, low;
पूर्ण;
प्रकार जोड़ अणु
	काष्ठा DWकाष्ठा s;
	DWtype ll;
पूर्ण DWजोड़;

प्रकार पूर्णांक word_type __attribute__ ((mode (__word__)));

#पूर्ण_अगर

#पूर्ण_अगर
