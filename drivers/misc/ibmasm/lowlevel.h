<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * IBM ASM Service Processor Device Driver
 *
 * Copyright (C) IBM Corporation, 2004
 *
 * Author: Max Asbथघck <amax@us.ibm.com>
 */

/* Conकरोr service processor specअगरic hardware definitions */

#अगर_अघोषित __IBMASM_CONDOR_H__
#घोषणा __IBMASM_CONDOR_H__

#समावेश <यंत्र/पन.स>

#घोषणा VENDORID_IBM	0x1014
#घोषणा DEVICEID_RSA	0x010F

#घोषणा GET_MFA_ADDR(x)  (x & 0xFFFFFF00)

#घोषणा MAILBOX_FULL(x)  (x & 0x00000001)

#घोषणा NO_MFAS_AVAILABLE     0xFFFFFFFF


#घोषणा INBOUND_QUEUE_PORT   0x40  /* contains address of next मुक्त MFA */
#घोषणा OUTBOUND_QUEUE_PORT  0x44  /* contains address of posted MFA    */

#घोषणा SP_INTR_MASK	0x00000008
#घोषणा UART_INTR_MASK	0x00000010

#घोषणा INTR_STATUS_REGISTER   0x13A0
#घोषणा INTR_CONTROL_REGISTER  0x13A4

#घोषणा SCOUT_COM_A_BASE         0x0000
#घोषणा SCOUT_COM_B_BASE         0x0100
#घोषणा SCOUT_COM_C_BASE         0x0200
#घोषणा SCOUT_COM_D_BASE         0x0300

अटल अंतरभूत पूर्णांक sp_पूर्णांकerrupt_pending(व्योम __iomem *base_address)
अणु
	वापस SP_INTR_MASK & पढ़ोl(base_address + INTR_STATUS_REGISTER);
पूर्ण

अटल अंतरभूत पूर्णांक uart_पूर्णांकerrupt_pending(व्योम __iomem *base_address)
अणु
	वापस UART_INTR_MASK & पढ़ोl(base_address + INTR_STATUS_REGISTER);
पूर्ण

अटल अंतरभूत व्योम ibmयंत्र_enable_पूर्णांकerrupts(व्योम __iomem *base_address, पूर्णांक mask)
अणु
	व्योम __iomem *ctrl_reg = base_address + INTR_CONTROL_REGISTER;
	ग_लिखोl( पढ़ोl(ctrl_reg) & ~mask, ctrl_reg);
पूर्ण

अटल अंतरभूत व्योम ibmयंत्र_disable_पूर्णांकerrupts(व्योम __iomem *base_address, पूर्णांक mask)
अणु
	व्योम __iomem *ctrl_reg = base_address + INTR_CONTROL_REGISTER;
	ग_लिखोl( पढ़ोl(ctrl_reg) | mask, ctrl_reg);
पूर्ण

अटल अंतरभूत व्योम enable_sp_पूर्णांकerrupts(व्योम __iomem *base_address)
अणु
	ibmयंत्र_enable_पूर्णांकerrupts(base_address, SP_INTR_MASK);
पूर्ण

अटल अंतरभूत व्योम disable_sp_पूर्णांकerrupts(व्योम __iomem *base_address)
अणु
	ibmयंत्र_disable_पूर्णांकerrupts(base_address, SP_INTR_MASK);
पूर्ण

अटल अंतरभूत व्योम enable_uart_पूर्णांकerrupts(व्योम __iomem *base_address)
अणु
	ibmयंत्र_enable_पूर्णांकerrupts(base_address, UART_INTR_MASK);
पूर्ण

अटल अंतरभूत व्योम disable_uart_पूर्णांकerrupts(व्योम __iomem *base_address)
अणु
	ibmयंत्र_disable_पूर्णांकerrupts(base_address, UART_INTR_MASK);
पूर्ण

#घोषणा valid_mfa(mfa)	( (mfa) != NO_MFAS_AVAILABLE )

अटल अंतरभूत u32 get_mfa_outbound(व्योम __iomem *base_address)
अणु
	पूर्णांक retry;
	u32 mfa;

	क्रम (retry=0; retry<=10; retry++) अणु
		mfa = पढ़ोl(base_address + OUTBOUND_QUEUE_PORT);
		अगर (valid_mfa(mfa))
			अवरोध;
	पूर्ण
	वापस mfa;
पूर्ण

अटल अंतरभूत व्योम set_mfa_outbound(व्योम __iomem *base_address, u32 mfa)
अणु
	ग_लिखोl(mfa, base_address + OUTBOUND_QUEUE_PORT);
पूर्ण

अटल अंतरभूत u32 get_mfa_inbound(व्योम __iomem *base_address)
अणु
	u32 mfa = पढ़ोl(base_address + INBOUND_QUEUE_PORT);

	अगर (MAILBOX_FULL(mfa))
		वापस 0;

	वापस mfa;
पूर्ण

अटल अंतरभूत व्योम set_mfa_inbound(व्योम __iomem *base_address, u32 mfa)
अणु
	ग_लिखोl(mfa, base_address + INBOUND_QUEUE_PORT);
पूर्ण

अटल अंतरभूत काष्ठा i2o_message *get_i2o_message(व्योम __iomem *base_address, u32 mfa)
अणु
	वापस (काष्ठा i2o_message *)(GET_MFA_ADDR(mfa) + base_address);
पूर्ण

#पूर्ण_अगर /* __IBMASM_CONDOR_H__ */
