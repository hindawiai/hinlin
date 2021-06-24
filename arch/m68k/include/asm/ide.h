<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 *  Copyright (C) 1994-1996  Linus Torvalds & authors
 */

/* Copyright(c) 1996 Kars de Jong */
/* Based on the ide driver from 1.2.13pl8 */

/*
 * Credits (alphabetical):
 *
 *  - Bjoern Brauel
 *  - Kars de Jong
 *  - Torsten Ebeling
 *  - Dwight Engen
 *  - Thorsten Floeck
 *  - Roman Hodek
 *  - Guenther Kelleter
 *  - Chris Lawrence
 *  - Michael Rausch
 *  - Christian Sauer
 *  - Michael Schmitz
 *  - Jes Soerensen
 *  - Michael Thurm
 *  - Geert Uytterhoeven
 */

#अगर_अघोषित _M68K_IDE_H
#घोषणा _M68K_IDE_H

#अगर_घोषित __KERNEL__
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

#अगर_घोषित CONFIG_MMU

/*
 * Get rid of defs from पन.स - ide has its निजी and conflicting versions
 * Since so far no single m68k platक्रमm uses ISA/PCI I/O space क्रम IDE, we
 * always use the `raw' MMIO versions
 */
#अघोषित पढ़ोb
#अघोषित पढ़ोw
#अघोषित ग_लिखोb
#अघोषित ग_लिखोw

#घोषणा पढ़ोb				in_8
#घोषणा पढ़ोw				in_be16
#घोषणा __ide_mm_insw(port, addr, n)	raw_insw((u16 *)port, addr, n)
#घोषणा __ide_mm_insl(port, addr, n)	raw_insl((u32 *)port, addr, n)
#घोषणा ग_लिखोb(val, port)		out_8(port, val)
#घोषणा ग_लिखोw(val, port)		out_be16(port, val)
#घोषणा __ide_mm_outsw(port, addr, n)	raw_outsw((u16 *)port, addr, n)
#घोषणा __ide_mm_outsl(port, addr, n)	raw_outsl((u32 *)port, addr, n)

#अन्यथा

#घोषणा __ide_mm_insw(port, addr, n)	io_insw((अचिन्हित पूर्णांक)port, addr, n)
#घोषणा __ide_mm_insl(port, addr, n)	io_insl((अचिन्हित पूर्णांक)port, addr, n)
#घोषणा __ide_mm_outsw(port, addr, n)	io_outsw((अचिन्हित पूर्णांक)port, addr, n)
#घोषणा __ide_mm_outsl(port, addr, n)	io_outsl((अचिन्हित पूर्णांक)port, addr, n)

#पूर्ण_अगर /* CONFIG_MMU */

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _M68K_IDE_H */
