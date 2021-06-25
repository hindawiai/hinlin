<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_X86_I8259_H
#घोषणा _ASM_X86_I8259_H

#समावेश <linux/delay.h>
#समावेश <यंत्र/पन.स>

बाह्य अचिन्हित पूर्णांक cached_irq_mask;

#घोषणा __byte(x, y)		(((अचिन्हित अक्षर *)&(y))[x])
#घोषणा cached_master_mask	(__byte(0, cached_irq_mask))
#घोषणा cached_slave_mask	(__byte(1, cached_irq_mask))

/* i8259A PIC रेजिस्टरs */
#घोषणा PIC_MASTER_CMD		0x20
#घोषणा PIC_MASTER_IMR		0x21
#घोषणा PIC_MASTER_ISR		PIC_MASTER_CMD
#घोषणा PIC_MASTER_POLL		PIC_MASTER_ISR
#घोषणा PIC_MASTER_OCW3		PIC_MASTER_ISR
#घोषणा PIC_SLAVE_CMD		0xa0
#घोषणा PIC_SLAVE_IMR		0xa1

/* i8259A PIC related value */
#घोषणा PIC_CASCADE_IR		2
#घोषणा MASTER_ICW4_DEFAULT	0x01
#घोषणा SLAVE_ICW4_DEFAULT	0x01
#घोषणा PIC_ICW4_AEOI		2

बाह्य raw_spinlock_t i8259A_lock;

/* the PIC may need a careful delay on some platक्रमms, hence specअगरic calls */
अटल अंतरभूत अचिन्हित अक्षर inb_pic(अचिन्हित पूर्णांक port)
अणु
	अचिन्हित अक्षर value = inb(port);

	/*
	 * delay क्रम some accesses to PIC on motherboard or in chipset
	 * must be at least one microsecond, so be safe here:
	 */
	udelay(2);

	वापस value;
पूर्ण

अटल अंतरभूत व्योम outb_pic(अचिन्हित अक्षर value, अचिन्हित पूर्णांक port)
अणु
	outb(value, port);
	/*
	 * delay क्रम some accesses to PIC on motherboard or in chipset
	 * must be at least one microsecond, so be safe here:
	 */
	udelay(2);
पूर्ण

बाह्य काष्ठा irq_chip i8259A_chip;

काष्ठा legacy_pic अणु
	पूर्णांक nr_legacy_irqs;
	काष्ठा irq_chip *chip;
	व्योम (*mask)(अचिन्हित पूर्णांक irq);
	व्योम (*unmask)(अचिन्हित पूर्णांक irq);
	व्योम (*mask_all)(व्योम);
	व्योम (*restore_mask)(व्योम);
	व्योम (*init)(पूर्णांक स्वतः_eoi);
	पूर्णांक (*probe)(व्योम);
	पूर्णांक (*irq_pending)(अचिन्हित पूर्णांक irq);
	व्योम (*make_irq)(अचिन्हित पूर्णांक irq);
पूर्ण;

बाह्य काष्ठा legacy_pic *legacy_pic;
बाह्य काष्ठा legacy_pic null_legacy_pic;

अटल अंतरभूत bool has_legacy_pic(व्योम)
अणु
	वापस legacy_pic != &null_legacy_pic;
पूर्ण

अटल अंतरभूत पूर्णांक nr_legacy_irqs(व्योम)
अणु
	वापस legacy_pic->nr_legacy_irqs;
पूर्ण

#पूर्ण_अगर /* _ASM_X86_I8259_H */
