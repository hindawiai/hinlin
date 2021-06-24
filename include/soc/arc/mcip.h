<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * ARConnect IP Support (Multi core enabler: Cross core IPI, RTC ...)
 *
 * Copyright (C) 2014-15 Synopsys, Inc. (www.synopsys.com)
 */

#अगर_अघोषित __SOC_ARC_MCIP_H
#घोषणा __SOC_ARC_MCIP_H

#समावेश <soc/arc/aux.h>

#घोषणा ARC_REG_MCIP_BCR	0x0d0
#घोषणा ARC_REG_MCIP_IDU_BCR	0x0D5
#घोषणा ARC_REG_GFRC_BUILD	0x0D6
#घोषणा ARC_REG_MCIP_CMD	0x600
#घोषणा ARC_REG_MCIP_WDATA	0x601
#घोषणा ARC_REG_MCIP_READBACK	0x602

काष्ठा mcip_cmd अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक pad:8, param:16, cmd:8;
#अन्यथा
	अचिन्हित पूर्णांक cmd:8, param:16, pad:8;
#पूर्ण_अगर

#घोषणा CMD_INTRPT_GENERATE_IRQ		0x01
#घोषणा CMD_INTRPT_GENERATE_ACK		0x02
#घोषणा CMD_INTRPT_READ_STATUS		0x03
#घोषणा CMD_INTRPT_CHECK_SOURCE		0x04

/* Semaphore Commands */
#घोषणा CMD_SEMA_CLAIM_AND_READ		0x11
#घोषणा CMD_SEMA_RELEASE		0x12

#घोषणा CMD_DEBUG_SET_MASK		0x34
#घोषणा CMD_DEBUG_READ_MASK		0x35
#घोषणा CMD_DEBUG_SET_SELECT		0x36
#घोषणा CMD_DEBUG_READ_SELECT		0x37

#घोषणा CMD_GFRC_READ_LO		0x42
#घोषणा CMD_GFRC_READ_HI		0x43
#घोषणा CMD_GFRC_SET_CORE		0x47
#घोषणा CMD_GFRC_READ_CORE		0x48

#घोषणा CMD_IDU_ENABLE			0x71
#घोषणा CMD_IDU_DISABLE			0x72
#घोषणा CMD_IDU_SET_MODE		0x74
#घोषणा CMD_IDU_READ_MODE		0x75
#घोषणा CMD_IDU_SET_DEST		0x76
#घोषणा CMD_IDU_ACK_CIRQ		0x79
#घोषणा CMD_IDU_SET_MASK		0x7C

#घोषणा IDU_M_TRIG_LEVEL		0x0
#घोषणा IDU_M_TRIG_EDGE			0x1

#घोषणा IDU_M_DISTRI_RR			0x0
#घोषणा IDU_M_DISTRI_DEST		0x2
पूर्ण;

काष्ठा mcip_bcr अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
		अचिन्हित पूर्णांक pad4:6, pw_करोm:1, pad3:1,
			     idu:1, pad2:1, num_cores:6,
			     pad:1,  gfrc:1, dbg:1, pw:1,
			     msg:1, sem:1, ipi:1, slv:1,
			     ver:8;
#अन्यथा
		अचिन्हित पूर्णांक ver:8,
			     slv:1, ipi:1, sem:1, msg:1,
			     pw:1, dbg:1, gfrc:1, pad:1,
			     num_cores:6, pad2:1, idu:1,
			     pad3:1, pw_करोm:1, pad4:6;
#पूर्ण_अगर
पूर्ण;

काष्ठा mcip_idu_bcr अणु
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
	अचिन्हित पूर्णांक pad:21, cirqnum:3, ver:8;
#अन्यथा
	अचिन्हित पूर्णांक ver:8, cirqnum:3, pad:21;
#पूर्ण_अगर
पूर्ण;


/*
 * Build रेजिस्टर क्रम IDU contains not an actual number of supported common
 * पूर्णांकerrupts but an exponent of 2 which must be multiplied by 4 to
 * get a number of supported common पूर्णांकerrupts.
 */
#घोषणा mcip_idu_bcr_to_nr_irqs(bcr) (4 * (1 << (bcr).cirqnum))

/*
 * MCIP programming model
 *
 * - Simple commands ग_लिखो अणुcmd:8,param:16पूर्ण to MCIP_CMD aux reg
 *   (param could be irq, common_irq, core_id ...)
 * - More involved commands setup MCIP_WDATA with cmd specअगरic data
 *   beक्रमe invoking the simple command
 */
अटल अंतरभूत व्योम __mcip_cmd(अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक param)
अणु
	काष्ठा mcip_cmd buf;

	buf.pad = 0;
	buf.cmd = cmd;
	buf.param = param;

	WRITE_AUX(ARC_REG_MCIP_CMD, buf);
पूर्ण

/*
 * Setup additional data क्रम a cmd
 * Callers need to lock to ensure atomicity
 */
अटल अंतरभूत व्योम __mcip_cmd_data(अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक param,
				   अचिन्हित पूर्णांक data)
अणु
	ग_लिखो_aux_reg(ARC_REG_MCIP_WDATA, data);

	__mcip_cmd(cmd, param);
पूर्ण

/*
 * Read MCIP रेजिस्टर
 */
अटल अंतरभूत अचिन्हित पूर्णांक __mcip_cmd_पढ़ो(अचिन्हित पूर्णांक cmd, अचिन्हित पूर्णांक param)
अणु
	__mcip_cmd(cmd, param);
	वापस पढ़ो_aux_reg(ARC_REG_MCIP_READBACK);
पूर्ण

#पूर्ण_अगर
