<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASMARM_CTI_H
#घोषणा __ASMARM_CTI_H

#समावेश	<यंत्र/पन.स>
#समावेश	<यंत्र/hardware/coresight.h>

/* The रेजिस्टरs' definition is from section 3.2 of
 * Embedded Cross Trigger Revision: r0p0
 */
#घोषणा		CTICONTROL		0x000
#घोषणा		CTISTATUS		0x004
#घोषणा		CTILOCK			0x008
#घोषणा		CTIPROTECTION		0x00C
#घोषणा		CTIINTACK		0x010
#घोषणा		CTIAPPSET		0x014
#घोषणा		CTIAPPCLEAR		0x018
#घोषणा		CTIAPPPULSE		0x01c
#घोषणा		CTIINEN			0x020
#घोषणा		CTIOUTEN		0x0A0
#घोषणा		CTITRIGINSTATUS		0x130
#घोषणा		CTITRIGOUTSTATUS	0x134
#घोषणा		CTICHINSTATUS		0x138
#घोषणा		CTICHOUTSTATUS		0x13c
#घोषणा		CTIPERIPHID0		0xFE0
#घोषणा		CTIPERIPHID1		0xFE4
#घोषणा		CTIPERIPHID2		0xFE8
#घोषणा		CTIPERIPHID3		0xFEC
#घोषणा		CTIPCELLID0		0xFF0
#घोषणा		CTIPCELLID1		0xFF4
#घोषणा		CTIPCELLID2		0xFF8
#घोषणा		CTIPCELLID3		0xFFC

/* The below are from section 3.6.4 of
 * CoreSight v1.0 Architecture Specअगरication
 */
#घोषणा		LOCKACCESS		0xFB0
#घोषणा		LOCKSTATUS		0xFB4

/**
 * काष्ठा cti - cross trigger पूर्णांकerface काष्ठा
 * @base: mapped भव address क्रम the cti base
 * @irq: irq number क्रम the cti
 * @trig_out_क्रम_irq: triger out number which will cause
 *	the @irq happen
 *
 * cti काष्ठा used to operate cti रेजिस्टरs.
 */
काष्ठा cti अणु
	व्योम __iomem *base;
	पूर्णांक irq;
	पूर्णांक trig_out_क्रम_irq;
पूर्ण;

/**
 * cti_init - initialize the cti instance
 * @cti: cti instance
 * @base: mapped भव address क्रम the cti base
 * @irq: irq number क्रम the cti
 * @trig_out: triger out number which will cause
 *	the @irq happen
 *
 * called by machine code to pass the board dependent
 * @base, @irq and @trig_out to cti.
 */
अटल अंतरभूत व्योम cti_init(काष्ठा cti *cti,
	व्योम __iomem *base, पूर्णांक irq, पूर्णांक trig_out)
अणु
	cti->base = base;
	cti->irq  = irq;
	cti->trig_out_क्रम_irq = trig_out;
पूर्ण

/**
 * cti_map_trigger - use the @chan to map @trig_in to @trig_out
 * @cti: cti instance
 * @trig_in: trigger in number
 * @trig_out: trigger out number
 * @channel: channel number
 *
 * This function maps one trigger in of @trig_in to one trigger
 * out of @trig_out using the channel @chan.
 */
अटल अंतरभूत व्योम cti_map_trigger(काष्ठा cti *cti,
	पूर्णांक trig_in, पूर्णांक trig_out, पूर्णांक chan)
अणु
	व्योम __iomem *base = cti->base;
	अचिन्हित दीर्घ val;

	val = __raw_पढ़ोl(base + CTIINEN + trig_in * 4);
	val |= BIT(chan);
	__raw_ग_लिखोl(val, base + CTIINEN + trig_in * 4);

	val = __raw_पढ़ोl(base + CTIOUTEN + trig_out * 4);
	val |= BIT(chan);
	__raw_ग_लिखोl(val, base + CTIOUTEN + trig_out * 4);
पूर्ण

/**
 * cti_enable - enable the cti module
 * @cti: cti instance
 *
 * enable the cti module
 */
अटल अंतरभूत व्योम cti_enable(काष्ठा cti *cti)
अणु
	__raw_ग_लिखोl(0x1, cti->base + CTICONTROL);
पूर्ण

/**
 * cti_disable - disable the cti module
 * @cti: cti instance
 *
 * enable the cti module
 */
अटल अंतरभूत व्योम cti_disable(काष्ठा cti *cti)
अणु
	__raw_ग_लिखोl(0, cti->base + CTICONTROL);
पूर्ण

/**
 * cti_irq_ack - clear the cti irq
 * @cti: cti instance
 *
 * clear the cti irq
 */
अटल अंतरभूत व्योम cti_irq_ack(काष्ठा cti *cti)
अणु
	व्योम __iomem *base = cti->base;
	अचिन्हित दीर्घ val;

	val = __raw_पढ़ोl(base + CTIINTACK);
	val |= BIT(cti->trig_out_क्रम_irq);
	__raw_ग_लिखोl(val, base + CTIINTACK);
पूर्ण

/**
 * cti_unlock - unlock cti module
 * @cti: cti instance
 *
 * unlock the cti module, or अन्यथा any ग_लिखोs to the cti
 * module is not allowed.
 */
अटल अंतरभूत व्योम cti_unlock(काष्ठा cti *cti)
अणु
	__raw_ग_लिखोl(CS_LAR_KEY, cti->base + LOCKACCESS);
पूर्ण

/**
 * cti_lock - lock cti module
 * @cti: cti instance
 *
 * lock the cti module, so any ग_लिखोs to the cti
 * module will be not allowed.
 */
अटल अंतरभूत व्योम cti_lock(काष्ठा cti *cti)
अणु
	__raw_ग_लिखोl(~CS_LAR_KEY, cti->base + LOCKACCESS);
पूर्ण
#पूर्ण_अगर
