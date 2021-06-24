<शैली गुरु>
#अगर_अघोषित _PPC_KERNEL_MPC8xx_H
#घोषणा _PPC_KERNEL_MPC8xx_H

#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>

पूर्णांक mpc8xx_pic_init(व्योम);
अचिन्हित पूर्णांक mpc8xx_get_irq(व्योम);

/*
 * Some पूर्णांकernal पूर्णांकerrupt रेजिस्टरs use an 8-bit mask क्रम the पूर्णांकerrupt
 * level instead of a number.
 */
अटल अंतरभूत uपूर्णांक mk_पूर्णांक_पूर्णांक_mask(uपूर्णांक mask)
अणु
	वापस (1 << (7 - (mask/2)));
पूर्ण

#पूर्ण_अगर /* _PPC_KERNEL_PPC8xx_H */
