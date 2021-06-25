<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>

#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/apollohw.h>

अचिन्हित पूर्णांक apollo_irq_startup(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;

	अगर (irq < 8)
		*(अस्थिर अचिन्हित अक्षर *)(pica+1) &= ~(1 << irq);
	अन्यथा
		*(अस्थिर अचिन्हित अक्षर *)(picb+1) &= ~(1 << (irq - 8));
	वापस 0;
पूर्ण

व्योम apollo_irq_shutकरोwn(काष्ठा irq_data *data)
अणु
	अचिन्हित पूर्णांक irq = data->irq;

	अगर (irq < 8)
		*(अस्थिर अचिन्हित अक्षर *)(pica+1) |= (1 << irq);
	अन्यथा
		*(अस्थिर अचिन्हित अक्षर *)(picb+1) |= (1 << (irq - 8));
पूर्ण

व्योम apollo_irq_eoi(काष्ठा irq_data *data)
अणु
	*(अस्थिर अचिन्हित अक्षर *)(pica) = 0x20;
	*(अस्थिर अचिन्हित अक्षर *)(picb) = 0x20;
पूर्ण

अटल काष्ठा irq_chip apollo_irq_chip = अणु
	.name           = "apollo",
	.irq_startup    = apollo_irq_startup,
	.irq_shutकरोwn   = apollo_irq_shutकरोwn,
	.irq_eoi	= apollo_irq_eoi,
पूर्ण;


व्योम __init dn_init_IRQ(व्योम)
अणु
	m68k_setup_user_पूर्णांकerrupt(VEC_USER + 96, 16);
	m68k_setup_irq_controller(&apollo_irq_chip, handle_fasteoi_irq,
				  IRQ_APOLLO, 16);
पूर्ण
