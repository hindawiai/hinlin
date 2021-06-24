<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Copyright 2011-2012, Meaकरोr Inge, Mentor Graphics Corporation.
 */

#अगर_अघोषित _ASM_MPIC_MSGR_H
#घोषणा _ASM_MPIC_MSGR_H

#समावेश <linux/types.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/पन.स>

काष्ठा mpic_msgr अणु
	u32 __iomem *base;
	u32 __iomem *mer;
	पूर्णांक irq;
	अचिन्हित अक्षर in_use;
	raw_spinlock_t lock;
	पूर्णांक num;
पूर्ण;

/* Get a message रेजिस्टर
 *
 * @reg_num:	the MPIC message रेजिस्टर to get
 *
 * A poपूर्णांकer to the message रेजिस्टर is वापसed.  If
 * the message रेजिस्टर asked क्रम is alपढ़ोy in use, then
 * EBUSY is वापसed.  If the number given is not associated
 * with an actual message रेजिस्टर, then ENODEV is वापसed.
 * Successfully getting the रेजिस्टर marks it as in use.
 */
बाह्य काष्ठा mpic_msgr *mpic_msgr_get(अचिन्हित पूर्णांक reg_num);

/* Relinquish a message रेजिस्टर
 *
 * @msgr:	the message रेजिस्टर to वापस
 *
 * Disables the given message रेजिस्टर and marks it as मुक्त.
 * After this call has completed successully the message
 * रेजिस्टर is available to be acquired by a call to
 * mpic_msgr_get.
 */
बाह्य व्योम mpic_msgr_put(काष्ठा mpic_msgr *msgr);

/* Enable a message रेजिस्टर
 *
 * @msgr:	the message रेजिस्टर to enable
 *
 * The given message रेजिस्टर is enabled क्रम sending
 * messages.
 */
बाह्य व्योम mpic_msgr_enable(काष्ठा mpic_msgr *msgr);

/* Disable a message रेजिस्टर
 *
 * @msgr:	the message रेजिस्टर to disable
 *
 * The given message रेजिस्टर is disabled क्रम sending
 * messages.
 */
बाह्य व्योम mpic_msgr_disable(काष्ठा mpic_msgr *msgr);

/* Write a message to a message रेजिस्टर
 *
 * @msgr:	the message रेजिस्टर to ग_लिखो to
 * @message:	the message to ग_लिखो
 *
 * The given 32-bit message is written to the given message
 * रेजिस्टर.  Writing to an enabled message रेजिस्टरs fires
 * an पूर्णांकerrupt.
 */
अटल अंतरभूत व्योम mpic_msgr_ग_लिखो(काष्ठा mpic_msgr *msgr, u32 message)
अणु
	out_be32(msgr->base, message);
पूर्ण

/* Read a message from a message रेजिस्टर
 *
 * @msgr:	the message रेजिस्टर to पढ़ो from
 *
 * Returns the 32-bit value currently in the given message रेजिस्टर.
 * Upon पढ़ोing the रेजिस्टर any पूर्णांकerrupts क्रम that रेजिस्टर are
 * cleared.
 */
अटल अंतरभूत u32 mpic_msgr_पढ़ो(काष्ठा mpic_msgr *msgr)
अणु
	वापस in_be32(msgr->base);
पूर्ण

/* Clear a message रेजिस्टर
 *
 * @msgr:	the message रेजिस्टर to clear
 *
 * Clears any पूर्णांकerrupts associated with the given message रेजिस्टर.
 */
अटल अंतरभूत व्योम mpic_msgr_clear(काष्ठा mpic_msgr *msgr)
अणु
	(व्योम) mpic_msgr_पढ़ो(msgr);
पूर्ण

/* Set the destination CPU क्रम the message रेजिस्टर
 *
 * @msgr:	the message रेजिस्टर whose destination is to be set
 * @cpu_num:	the Linux CPU number to bind the message रेजिस्टर to
 *
 * Note that the CPU number given is the CPU number used by the kernel
 * and *not* the actual hardware CPU number.
 */
अटल अंतरभूत व्योम mpic_msgr_set_destination(काष्ठा mpic_msgr *msgr,
					     u32 cpu_num)
अणु
	out_be32(msgr->base, 1 << get_hard_smp_processor_id(cpu_num));
पूर्ण

/* Get the IRQ number क्रम the message रेजिस्टर
 * @msgr:	the message रेजिस्टर whose IRQ is to be वापसed
 *
 * Returns the IRQ number associated with the given message रेजिस्टर.
 * 0 is वापसed अगर this message रेजिस्टर is not capable of receiving
 * पूर्णांकerrupts.  What message रेजिस्टर can and cannot receive पूर्णांकerrupts is
 * specअगरied in the device tree क्रम the प्रणाली.
 */
अटल अंतरभूत पूर्णांक mpic_msgr_get_irq(काष्ठा mpic_msgr *msgr)
अणु
	वापस msgr->irq;
पूर्ण

#पूर्ण_अगर
