<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_M68K_VGA_H
#घोषणा _ASM_M68K_VGA_H

/*
 * Some ColdFire platक्रमms करो in fact have a PCI bus. So क्रम those we want
 * to use the real IO access functions, करोn't fake them out or redirect them
 * क्रम that हाल.
 */
#अगर_अघोषित CONFIG_PCI

#समावेश <यंत्र/raw_पन.स>
#समावेश <यंत्र/kmap.h>

/*
 * FIXME
 * Ugh, we करोn't have PCI space, so map पढ़ोb() and मित्रs to use raw I/O
 * accessors, which are identical to the z_*() Zorro bus accessors.
 * This should make cirrusfb work again on Amiga
 */
#अघोषित inb_p
#अघोषित inw_p
#अघोषित outb_p
#अघोषित outw
#अघोषित पढ़ोb
#अघोषित ग_लिखोb
#अघोषित ग_लिखोw
#घोषणा inb_p(port)		0
#घोषणा inw_p(port)		0
#घोषणा outb_p(port, val)	करो अणु पूर्ण जबतक (0)
#घोषणा outw(port, val)		करो अणु पूर्ण जबतक (0)
#घोषणा पढ़ोb			raw_inb
#घोषणा ग_लिखोb			raw_outb
#घोषणा ग_लिखोw			raw_outw

#पूर्ण_अगर /* CONFIG_PCI */
#पूर्ण_अगर /* _ASM_M68K_VGA_H */
