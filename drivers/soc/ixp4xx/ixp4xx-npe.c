<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel IXP4xx Network Processor Engine driver क्रम Linux
 *
 * Copyright (C) 2007 Krzysztof Halasa <khc@pm.waw.pl>
 *
 * The code is based on खुलाly available inक्रमmation:
 * - Intel IXP4xx Developer's Manual and other e-papers
 * - Intel IXP400 Access Library Software (BSD license)
 * - previous works by Christian Hohnstaedt <chohnstaedt@innominate.com>
 *   Thanks, Christian.
 */

#समावेश <linux/delay.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/firmware.h>
#समावेश <linux/पन.स>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/ixp4xx/npe.h>

#घोषणा DEBUG_MSG			0
#घोषणा DEBUG_FW			0

#घोषणा NPE_COUNT			3
#घोषणा MAX_RETRIES			1000	/* microseconds */
#घोषणा NPE_42X_DATA_SIZE		0x800	/* in dwords */
#घोषणा NPE_46X_DATA_SIZE		0x1000
#घोषणा NPE_A_42X_INSTR_SIZE		0x1000
#घोषणा NPE_B_AND_C_42X_INSTR_SIZE	0x800
#घोषणा NPE_46X_INSTR_SIZE		0x1000
#घोषणा REGS_SIZE			0x1000

#घोषणा NPE_PHYS_REG			32

#घोषणा FW_MAGIC			0xFEEDF00D
#घोषणा FW_BLOCK_TYPE_INSTR		0x0
#घोषणा FW_BLOCK_TYPE_DATA		0x1
#घोषणा FW_BLOCK_TYPE_खातापूर्ण		0xF

/* NPE exec status (पढ़ो) and command (ग_लिखो) */
#घोषणा CMD_NPE_STEP			0x01
#घोषणा CMD_NPE_START			0x02
#घोषणा CMD_NPE_STOP			0x03
#घोषणा CMD_NPE_CLR_PIPE		0x04
#घोषणा CMD_CLR_PROखाता_CNT		0x0C
#घोषणा CMD_RD_INS_MEM			0x10 /* inकाष्ठाion memory */
#घोषणा CMD_WR_INS_MEM			0x11
#घोषणा CMD_RD_DATA_MEM			0x12 /* data memory */
#घोषणा CMD_WR_DATA_MEM			0x13
#घोषणा CMD_RD_ECS_REG			0x14 /* exec access रेजिस्टर */
#घोषणा CMD_WR_ECS_REG			0x15

#घोषणा STAT_RUN			0x80000000
#घोषणा STAT_STOP			0x40000000
#घोषणा STAT_CLEAR			0x20000000
#घोषणा STAT_ECS_K			0x00800000 /* pipeline clean */

#घोषणा NPE_STEVT			0x1B
#घोषणा NPE_STARTPC			0x1C
#घोषणा NPE_REGMAP			0x1E
#घोषणा NPE_CINDEX			0x1F

#घोषणा INSTR_WR_REG_SHORT		0x0000C000
#घोषणा INSTR_WR_REG_BYTE		0x00004000
#घोषणा INSTR_RD_FIFO			0x0F888220
#घोषणा INSTR_RESET_MBOX		0x0FAC8210

#घोषणा ECS_BG_CTXT_REG_0		0x00 /* Background Executing Context */
#घोषणा ECS_BG_CTXT_REG_1		0x01 /*		Stack level */
#घोषणा ECS_BG_CTXT_REG_2		0x02
#घोषणा ECS_PRI_1_CTXT_REG_0		0x04 /* Priority 1 Executing Context */
#घोषणा ECS_PRI_1_CTXT_REG_1		0x05 /*		Stack level */
#घोषणा ECS_PRI_1_CTXT_REG_2		0x06
#घोषणा ECS_PRI_2_CTXT_REG_0		0x08 /* Priority 2 Executing Context */
#घोषणा ECS_PRI_2_CTXT_REG_1		0x09 /*		Stack level */
#घोषणा ECS_PRI_2_CTXT_REG_2		0x0A
#घोषणा ECS_DBG_CTXT_REG_0		0x0C /* Debug Executing Context */
#घोषणा ECS_DBG_CTXT_REG_1		0x0D /*		Stack level */
#घोषणा ECS_DBG_CTXT_REG_2		0x0E
#घोषणा ECS_INSTRUCT_REG		0x11 /* NPE Inकाष्ठाion Register */

#घोषणा ECS_REG_0_ACTIVE		0x80000000 /* all levels */
#घोषणा ECS_REG_0_NEXTPC_MASK		0x1FFF0000 /* BG/PRI1/PRI2 levels */
#घोषणा ECS_REG_0_LDUR_BITS		8
#घोषणा ECS_REG_0_LDUR_MASK		0x00000700 /* all levels */
#घोषणा ECS_REG_1_CCTXT_BITS		16
#घोषणा ECS_REG_1_CCTXT_MASK		0x000F0000 /* all levels */
#घोषणा ECS_REG_1_SELCTXT_BITS		0
#घोषणा ECS_REG_1_SELCTXT_MASK		0x0000000F /* all levels */
#घोषणा ECS_DBG_REG_2_IF		0x00100000 /* debug level */
#घोषणा ECS_DBG_REG_2_IE		0x00080000 /* debug level */

/* NPE watchpoपूर्णांक_fअगरo रेजिस्टर bit */
#घोषणा WFIFO_VALID			0x80000000

/* NPE messaging_status रेजिस्टर bit definitions */
#घोषणा MSGSTAT_OFNE	0x00010000 /* OutFअगरoNotEmpty */
#घोषणा MSGSTAT_IFNF	0x00020000 /* InFअगरoNotFull */
#घोषणा MSGSTAT_OFNF	0x00040000 /* OutFअगरoNotFull */
#घोषणा MSGSTAT_IFNE	0x00080000 /* InFअगरoNotEmpty */
#घोषणा MSGSTAT_MBINT	0x00100000 /* Mailbox पूर्णांकerrupt */
#घोषणा MSGSTAT_IFINT	0x00200000 /* InFअगरo पूर्णांकerrupt */
#घोषणा MSGSTAT_OFINT	0x00400000 /* OutFअगरo पूर्णांकerrupt */
#घोषणा MSGSTAT_WFINT	0x00800000 /* WatchFअगरo पूर्णांकerrupt */

/* NPE messaging_control रेजिस्टर bit definitions */
#घोषणा MSGCTL_OUT_FIFO			0x00010000 /* enable output FIFO */
#घोषणा MSGCTL_IN_FIFO			0x00020000 /* enable input FIFO */
#घोषणा MSGCTL_OUT_FIFO_WRITE		0x01000000 /* enable FIFO + WRITE */
#घोषणा MSGCTL_IN_FIFO_WRITE		0x02000000

/* NPE mailbox_status value क्रम reset */
#घोषणा RESET_MBOX_STAT			0x0000F0F0

#घोषणा NPE_A_FIRMWARE "NPE-A"
#घोषणा NPE_B_FIRMWARE "NPE-B"
#घोषणा NPE_C_FIRMWARE "NPE-C"

स्थिर अक्षर *npe_names[] = अणु NPE_A_FIRMWARE, NPE_B_FIRMWARE, NPE_C_FIRMWARE पूर्ण;

#घोषणा prपूर्णांक_npe(pri, npe, fmt, ...)					\
	prपूर्णांकk(pri "%s: " fmt, npe_name(npe), ## __VA_ARGS__)

#अगर DEBUG_MSG
#घोषणा debug_msg(npe, fmt, ...)					\
	prपूर्णांक_npe(KERN_DEBUG, npe, fmt, ## __VA_ARGS__)
#अन्यथा
#घोषणा debug_msg(npe, fmt, ...)
#पूर्ण_अगर

अटल काष्ठा अणु
	u32 reg, val;
पूर्ण ecs_reset[] = अणु
	अणु ECS_BG_CTXT_REG_0,	0xA0000000 पूर्ण,
	अणु ECS_BG_CTXT_REG_1,	0x01000000 पूर्ण,
	अणु ECS_BG_CTXT_REG_2,	0x00008000 पूर्ण,
	अणु ECS_PRI_1_CTXT_REG_0,	0x20000080 पूर्ण,
	अणु ECS_PRI_1_CTXT_REG_1,	0x01000000 पूर्ण,
	अणु ECS_PRI_1_CTXT_REG_2,	0x00008000 पूर्ण,
	अणु ECS_PRI_2_CTXT_REG_0,	0x20000080 पूर्ण,
	अणु ECS_PRI_2_CTXT_REG_1,	0x01000000 पूर्ण,
	अणु ECS_PRI_2_CTXT_REG_2,	0x00008000 पूर्ण,
	अणु ECS_DBG_CTXT_REG_0,	0x20000000 पूर्ण,
	अणु ECS_DBG_CTXT_REG_1,	0x00000000 पूर्ण,
	अणु ECS_DBG_CTXT_REG_2,	0x001E0000 पूर्ण,
	अणु ECS_INSTRUCT_REG,	0x1003C00F पूर्ण,
पूर्ण;

अटल काष्ठा npe npe_tab[NPE_COUNT] = अणु
	अणु
		.id	= 0,
	पूर्ण, अणु
		.id	= 1,
	पूर्ण, अणु
		.id	= 2,
	पूर्ण
पूर्ण;

पूर्णांक npe_running(काष्ठा npe *npe)
अणु
	वापस (__raw_पढ़ोl(&npe->regs->exec_status_cmd) & STAT_RUN) != 0;
पूर्ण

अटल व्योम npe_cmd_ग_लिखो(काष्ठा npe *npe, u32 addr, पूर्णांक cmd, u32 data)
अणु
	__raw_ग_लिखोl(data, &npe->regs->exec_data);
	__raw_ग_लिखोl(addr, &npe->regs->exec_addr);
	__raw_ग_लिखोl(cmd, &npe->regs->exec_status_cmd);
पूर्ण

अटल u32 npe_cmd_पढ़ो(काष्ठा npe *npe, u32 addr, पूर्णांक cmd)
अणु
	__raw_ग_लिखोl(addr, &npe->regs->exec_addr);
	__raw_ग_लिखोl(cmd, &npe->regs->exec_status_cmd);
	/* Iपूर्णांकroduce extra पढ़ो cycles after issuing पढ़ो command to NPE
	   so that we पढ़ो the रेजिस्टर after the NPE has updated it.
	   This is to overcome race condition between XScale and NPE */
	__raw_पढ़ोl(&npe->regs->exec_data);
	__raw_पढ़ोl(&npe->regs->exec_data);
	वापस __raw_पढ़ोl(&npe->regs->exec_data);
पूर्ण

अटल व्योम npe_clear_active(काष्ठा npe *npe, u32 reg)
अणु
	u32 val = npe_cmd_पढ़ो(npe, reg, CMD_RD_ECS_REG);
	npe_cmd_ग_लिखो(npe, reg, CMD_WR_ECS_REG, val & ~ECS_REG_0_ACTIVE);
पूर्ण

अटल व्योम npe_start(काष्ठा npe *npe)
अणु
	/* ensure only Background Context Stack Level is active */
	npe_clear_active(npe, ECS_PRI_1_CTXT_REG_0);
	npe_clear_active(npe, ECS_PRI_2_CTXT_REG_0);
	npe_clear_active(npe, ECS_DBG_CTXT_REG_0);

	__raw_ग_लिखोl(CMD_NPE_CLR_PIPE, &npe->regs->exec_status_cmd);
	__raw_ग_लिखोl(CMD_NPE_START, &npe->regs->exec_status_cmd);
पूर्ण

अटल व्योम npe_stop(काष्ठा npe *npe)
अणु
	__raw_ग_लिखोl(CMD_NPE_STOP, &npe->regs->exec_status_cmd);
	__raw_ग_लिखोl(CMD_NPE_CLR_PIPE, &npe->regs->exec_status_cmd); /*FIXME?*/
पूर्ण

अटल पूर्णांक __must_check npe_debug_instr(काष्ठा npe *npe, u32 instr, u32 ctx,
					u32 ldur)
अणु
	u32 wc;
	पूर्णांक i;

	/* set the Active bit, and the LDUR, in the debug level */
	npe_cmd_ग_लिखो(npe, ECS_DBG_CTXT_REG_0, CMD_WR_ECS_REG,
		      ECS_REG_0_ACTIVE | (ldur << ECS_REG_0_LDUR_BITS));

	/* set CCTXT at ECS DEBUG L3 to specअगरy in which context to execute
	   the inकाष्ठाion, and set SELCTXT at ECS DEBUG Level to specअगरy
	   which context store to access.
	   Debug ECS Level Reg 1 has क्रमm 0x000n000n, where n = context number
	*/
	npe_cmd_ग_लिखो(npe, ECS_DBG_CTXT_REG_1, CMD_WR_ECS_REG,
		      (ctx << ECS_REG_1_CCTXT_BITS) |
		      (ctx << ECS_REG_1_SELCTXT_BITS));

	/* clear the pipeline */
	__raw_ग_लिखोl(CMD_NPE_CLR_PIPE, &npe->regs->exec_status_cmd);

	/* load NPE inकाष्ठाion पूर्णांकo the inकाष्ठाion रेजिस्टर */
	npe_cmd_ग_लिखो(npe, ECS_INSTRUCT_REG, CMD_WR_ECS_REG, instr);

	/* we need this value later to रुको क्रम completion of NPE execution
	   step */
	wc = __raw_पढ़ोl(&npe->regs->watch_count);

	/* issue a Step One command via the Execution Control रेजिस्टर */
	__raw_ग_लिखोl(CMD_NPE_STEP, &npe->regs->exec_status_cmd);

	/* Watch Count रेजिस्टर increments when NPE completes an inकाष्ठाion */
	क्रम (i = 0; i < MAX_RETRIES; i++) अणु
		अगर (wc != __raw_पढ़ोl(&npe->regs->watch_count))
			वापस 0;
		udelay(1);
	पूर्ण

	prपूर्णांक_npe(KERN_ERR, npe, "reset: npe_debug_instr(): timeout\n");
	वापस -ETIMEDOUT;
पूर्ण

अटल पूर्णांक __must_check npe_logical_reg_ग_लिखो8(काष्ठा npe *npe, u32 addr,
					       u8 val, u32 ctx)
अणु
	/* here we build the NPE assembler inकाष्ठाion: mov8 d0, #0 */
	u32 instr = INSTR_WR_REG_BYTE |	/* OpCode */
		addr << 9 |		/* base Opeअक्रम */
		(val & 0x1F) << 4 |	/* lower 5 bits to immediate data */
		(val & ~0x1F) << (18 - 5);/* higher 3 bits to CoProc instr. */
	वापस npe_debug_instr(npe, instr, ctx, 1); /* execute it */
पूर्ण

अटल पूर्णांक __must_check npe_logical_reg_ग_लिखो16(काष्ठा npe *npe, u32 addr,
						u16 val, u32 ctx)
अणु
	/* here we build the NPE assembler inकाष्ठाion: mov16 d0, #0 */
	u32 instr = INSTR_WR_REG_SHORT | /* OpCode */
		addr << 9 |		/* base Opeअक्रम */
		(val & 0x1F) << 4 |	/* lower 5 bits to immediate data */
		(val & ~0x1F) << (18 - 5);/* higher 11 bits to CoProc instr. */
	वापस npe_debug_instr(npe, instr, ctx, 1); /* execute it */
पूर्ण

अटल पूर्णांक __must_check npe_logical_reg_ग_लिखो32(काष्ठा npe *npe, u32 addr,
						u32 val, u32 ctx)
अणु
	/* ग_लिखो in 16 bit steps first the high and then the low value */
	अगर (npe_logical_reg_ग_लिखो16(npe, addr, val >> 16, ctx))
		वापस -ETIMEDOUT;
	वापस npe_logical_reg_ग_लिखो16(npe, addr + 2, val & 0xFFFF, ctx);
पूर्ण

अटल पूर्णांक npe_reset(काष्ठा npe *npe)
अणु
	u32 val, ctl, exec_count, ctx_reg2;
	पूर्णांक i;

	ctl = (__raw_पढ़ोl(&npe->regs->messaging_control) | 0x3F000000) &
		0x3F3FFFFF;

	/* disable parity पूर्णांकerrupt */
	__raw_ग_लिखोl(ctl & 0x3F00FFFF, &npe->regs->messaging_control);

	/* pre exec - debug inकाष्ठाion */
	/* turn off the halt bit by clearing Execution Count रेजिस्टर. */
	exec_count = __raw_पढ़ोl(&npe->regs->exec_count);
	__raw_ग_लिखोl(0, &npe->regs->exec_count);
	/* ensure that IF and IE are on (temporarily), so that we करोn't end up
	   stepping क्रमever */
	ctx_reg2 = npe_cmd_पढ़ो(npe, ECS_DBG_CTXT_REG_2, CMD_RD_ECS_REG);
	npe_cmd_ग_लिखो(npe, ECS_DBG_CTXT_REG_2, CMD_WR_ECS_REG, ctx_reg2 |
		      ECS_DBG_REG_2_IF | ECS_DBG_REG_2_IE);

	/* clear the FIFOs */
	जबतक (__raw_पढ़ोl(&npe->regs->watchpoपूर्णांक_fअगरo) & WFIFO_VALID)
		;
	जबतक (__raw_पढ़ोl(&npe->regs->messaging_status) & MSGSTAT_OFNE)
		/* पढ़ो from the outFIFO until empty */
		prपूर्णांक_npe(KERN_DEBUG, npe, "npe_reset: read FIFO = 0x%X\n",
			  __raw_पढ़ोl(&npe->regs->in_out_fअगरo));

	जबतक (__raw_पढ़ोl(&npe->regs->messaging_status) & MSGSTAT_IFNE)
		/* step execution of the NPE पूर्णांकruction to पढ़ो inFIFO using
		   the Debug Executing Context stack */
		अगर (npe_debug_instr(npe, INSTR_RD_FIFO, 0, 0))
			वापस -ETIMEDOUT;

	/* reset the mailbox reg from the XScale side */
	__raw_ग_लिखोl(RESET_MBOX_STAT, &npe->regs->mailbox_status);
	/* from NPE side */
	अगर (npe_debug_instr(npe, INSTR_RESET_MBOX, 0, 0))
		वापस -ETIMEDOUT;

	/* Reset the physical रेजिस्टरs in the NPE रेजिस्टर file */
	क्रम (val = 0; val < NPE_PHYS_REG; val++) अणु
		अगर (npe_logical_reg_ग_लिखो16(npe, NPE_REGMAP, val >> 1, 0))
			वापस -ETIMEDOUT;
		/* address is either 0 or 4 */
		अगर (npe_logical_reg_ग_लिखो32(npe, (val & 1) * 4, 0, 0))
			वापस -ETIMEDOUT;
	पूर्ण

	/* Reset the context store = each context's Context Store रेजिस्टरs */

	/* Context 0 has no STARTPC. Instead, this value is used to set NextPC
	   क्रम Background ECS, to set where NPE starts executing code */
	val = npe_cmd_पढ़ो(npe, ECS_BG_CTXT_REG_0, CMD_RD_ECS_REG);
	val &= ~ECS_REG_0_NEXTPC_MASK;
	val |= (0 /* NextPC */ << 16) & ECS_REG_0_NEXTPC_MASK;
	npe_cmd_ग_लिखो(npe, ECS_BG_CTXT_REG_0, CMD_WR_ECS_REG, val);

	क्रम (i = 0; i < 16; i++) अणु
		अगर (i) अणु	/* Context 0 has no STEVT nor STARTPC */
			/* STEVT = off, 0x80 */
			अगर (npe_logical_reg_ग_लिखो8(npe, NPE_STEVT, 0x80, i))
				वापस -ETIMEDOUT;
			अगर (npe_logical_reg_ग_लिखो16(npe, NPE_STARTPC, 0, i))
				वापस -ETIMEDOUT;
		पूर्ण
		/* REGMAP = d0->p0, d8->p2, d16->p4 */
		अगर (npe_logical_reg_ग_लिखो16(npe, NPE_REGMAP, 0x820, i))
			वापस -ETIMEDOUT;
		अगर (npe_logical_reg_ग_लिखो8(npe, NPE_CINDEX, 0, i))
			वापस -ETIMEDOUT;
	पूर्ण

	/* post exec */
	/* clear active bit in debug level */
	npe_cmd_ग_लिखो(npe, ECS_DBG_CTXT_REG_0, CMD_WR_ECS_REG, 0);
	/* clear the pipeline */
	__raw_ग_लिखोl(CMD_NPE_CLR_PIPE, &npe->regs->exec_status_cmd);
	/* restore previous values */
	__raw_ग_लिखोl(exec_count, &npe->regs->exec_count);
	npe_cmd_ग_लिखो(npe, ECS_DBG_CTXT_REG_2, CMD_WR_ECS_REG, ctx_reg2);

	/* ग_लिखो reset values to Execution Context Stack रेजिस्टरs */
	क्रम (val = 0; val < ARRAY_SIZE(ecs_reset); val++)
		npe_cmd_ग_लिखो(npe, ecs_reset[val].reg, CMD_WR_ECS_REG,
			      ecs_reset[val].val);

	/* clear the profile counter */
	__raw_ग_लिखोl(CMD_CLR_PROखाता_CNT, &npe->regs->exec_status_cmd);

	__raw_ग_लिखोl(0, &npe->regs->exec_count);
	__raw_ग_लिखोl(0, &npe->regs->action_poपूर्णांकs[0]);
	__raw_ग_लिखोl(0, &npe->regs->action_poपूर्णांकs[1]);
	__raw_ग_लिखोl(0, &npe->regs->action_poपूर्णांकs[2]);
	__raw_ग_लिखोl(0, &npe->regs->action_poपूर्णांकs[3]);
	__raw_ग_लिखोl(0, &npe->regs->watch_count);

	val = ixp4xx_पढ़ो_feature_bits();
	/* reset the NPE */
	ixp4xx_ग_लिखो_feature_bits(val &
				  ~(IXP4XX_FEATURE_RESET_NPEA << npe->id));
	/* deनिश्चित reset */
	ixp4xx_ग_लिखो_feature_bits(val |
				  (IXP4XX_FEATURE_RESET_NPEA << npe->id));
	क्रम (i = 0; i < MAX_RETRIES; i++) अणु
		अगर (ixp4xx_पढ़ो_feature_bits() &
		    (IXP4XX_FEATURE_RESET_NPEA << npe->id))
			अवरोध;	/* NPE is back alive */
		udelay(1);
	पूर्ण
	अगर (i == MAX_RETRIES)
		वापस -ETIMEDOUT;

	npe_stop(npe);

	/* restore NPE configuration bus Control Register - parity settings */
	__raw_ग_लिखोl(ctl, &npe->regs->messaging_control);
	वापस 0;
पूर्ण


पूर्णांक npe_send_message(काष्ठा npe *npe, स्थिर व्योम *msg, स्थिर अक्षर *what)
अणु
	स्थिर u32 *send = msg;
	पूर्णांक cycles = 0;

	debug_msg(npe, "Trying to send message %s [%08X:%08X]\n",
		  what, send[0], send[1]);

	अगर (__raw_पढ़ोl(&npe->regs->messaging_status) & MSGSTAT_IFNE) अणु
		debug_msg(npe, "NPE input FIFO not empty\n");
		वापस -EIO;
	पूर्ण

	__raw_ग_लिखोl(send[0], &npe->regs->in_out_fअगरo);

	अगर (!(__raw_पढ़ोl(&npe->regs->messaging_status) & MSGSTAT_IFNF)) अणु
		debug_msg(npe, "NPE input FIFO full\n");
		वापस -EIO;
	पूर्ण

	__raw_ग_लिखोl(send[1], &npe->regs->in_out_fअगरo);

	जबतक ((cycles < MAX_RETRIES) &&
	       (__raw_पढ़ोl(&npe->regs->messaging_status) & MSGSTAT_IFNE)) अणु
		udelay(1);
		cycles++;
	पूर्ण

	अगर (cycles == MAX_RETRIES) अणु
		debug_msg(npe, "Timeout sending message\n");
		वापस -ETIMEDOUT;
	पूर्ण

#अगर DEBUG_MSG > 1
	debug_msg(npe, "Sending a message took %i cycles\n", cycles);
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक npe_recv_message(काष्ठा npe *npe, व्योम *msg, स्थिर अक्षर *what)
अणु
	u32 *recv = msg;
	पूर्णांक cycles = 0, cnt = 0;

	debug_msg(npe, "Trying to receive message %s\n", what);

	जबतक (cycles < MAX_RETRIES) अणु
		अगर (__raw_पढ़ोl(&npe->regs->messaging_status) & MSGSTAT_OFNE) अणु
			recv[cnt++] = __raw_पढ़ोl(&npe->regs->in_out_fअगरo);
			अगर (cnt == 2)
				अवरोध;
		पूर्ण अन्यथा अणु
			udelay(1);
			cycles++;
		पूर्ण
	पूर्ण

	चयन(cnt) अणु
	हाल 1:
		debug_msg(npe, "Received [%08X]\n", recv[0]);
		अवरोध;
	हाल 2:
		debug_msg(npe, "Received [%08X:%08X]\n", recv[0], recv[1]);
		अवरोध;
	पूर्ण

	अगर (cycles == MAX_RETRIES) अणु
		debug_msg(npe, "Timeout waiting for message\n");
		वापस -ETIMEDOUT;
	पूर्ण

#अगर DEBUG_MSG > 1
	debug_msg(npe, "Receiving a message took %i cycles\n", cycles);
#पूर्ण_अगर
	वापस 0;
पूर्ण

पूर्णांक npe_send_recv_message(काष्ठा npe *npe, व्योम *msg, स्थिर अक्षर *what)
अणु
	पूर्णांक result;
	u32 *send = msg, recv[2];

	अगर ((result = npe_send_message(npe, msg, what)) != 0)
		वापस result;
	अगर ((result = npe_recv_message(npe, recv, what)) != 0)
		वापस result;

	अगर ((recv[0] != send[0]) || (recv[1] != send[1])) अणु
		debug_msg(npe, "Message %s: unexpected message received\n",
			  what);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण


पूर्णांक npe_load_firmware(काष्ठा npe *npe, स्थिर अक्षर *name, काष्ठा device *dev)
अणु
	स्थिर काष्ठा firmware *fw_entry;

	काष्ठा dl_block अणु
		u32 type;
		u32 offset;
	पूर्ण *blk;

	काष्ठा dl_image अणु
		u32 magic;
		u32 id;
		u32 size;
		जोड़ अणु
			u32 data[0];
			काष्ठा dl_block blocks[0];
		पूर्ण;
	पूर्ण *image;

	काष्ठा dl_codeblock अणु
		u32 npe_addr;
		u32 size;
		u32 data[0];
	पूर्ण *cb;

	पूर्णांक i, j, err, data_size, instr_size, blocks, table_end;
	u32 cmd;

	अगर ((err = request_firmware(&fw_entry, name, dev)) != 0)
		वापस err;

	err = -EINVAL;
	अगर (fw_entry->size < माप(काष्ठा dl_image)) अणु
		prपूर्णांक_npe(KERN_ERR, npe, "incomplete firmware file\n");
		जाओ err;
	पूर्ण
	image = (काष्ठा dl_image*)fw_entry->data;

#अगर DEBUG_FW
	prपूर्णांक_npe(KERN_DEBUG, npe, "firmware: %08X %08X %08X (0x%X bytes)\n",
		  image->magic, image->id, image->size, image->size * 4);
#पूर्ण_अगर

	अगर (image->magic == swab32(FW_MAGIC)) अणु /* swapped file */
		image->id = swab32(image->id);
		image->size = swab32(image->size);
	पूर्ण अन्यथा अगर (image->magic != FW_MAGIC) अणु
		prपूर्णांक_npe(KERN_ERR, npe, "bad firmware file magic: 0x%X\n",
			  image->magic);
		जाओ err;
	पूर्ण
	अगर ((image->size * 4 + माप(काष्ठा dl_image)) != fw_entry->size) अणु
		prपूर्णांक_npe(KERN_ERR, npe,
			  "inconsistent size of firmware file\n");
		जाओ err;
	पूर्ण
	अगर (((image->id >> 24) & 0xF /* NPE ID */) != npe->id) अणु
		prपूर्णांक_npe(KERN_ERR, npe, "firmware file NPE ID mismatch\n");
		जाओ err;
	पूर्ण
	अगर (image->magic == swab32(FW_MAGIC))
		क्रम (i = 0; i < image->size; i++)
			image->data[i] = swab32(image->data[i]);

	अगर (cpu_is_ixp42x() && ((image->id >> 28) & 0xF /* device ID */)) अणु
		prपूर्णांक_npe(KERN_INFO, npe, "IXP43x/IXP46x firmware ignored on "
			  "IXP42x\n");
		जाओ err;
	पूर्ण

	अगर (npe_running(npe)) अणु
		prपूर्णांक_npe(KERN_INFO, npe, "unable to load firmware, NPE is "
			  "already running\n");
		err = -EBUSY;
		जाओ err;
	पूर्ण
#अगर 0
	npe_stop(npe);
	npe_reset(npe);
#पूर्ण_अगर

	prपूर्णांक_npe(KERN_INFO, npe, "firmware functionality 0x%X, "
		  "revision 0x%X:%X\n", (image->id >> 16) & 0xFF,
		  (image->id >> 8) & 0xFF, image->id & 0xFF);

	अगर (cpu_is_ixp42x()) अणु
		अगर (!npe->id)
			instr_size = NPE_A_42X_INSTR_SIZE;
		अन्यथा
			instr_size = NPE_B_AND_C_42X_INSTR_SIZE;
		data_size = NPE_42X_DATA_SIZE;
	पूर्ण अन्यथा अणु
		instr_size = NPE_46X_INSTR_SIZE;
		data_size = NPE_46X_DATA_SIZE;
	पूर्ण

	क्रम (blocks = 0; blocks * माप(काष्ठा dl_block) / 4 < image->size;
	     blocks++)
		अगर (image->blocks[blocks].type == FW_BLOCK_TYPE_खातापूर्ण)
			अवरोध;
	अगर (blocks * माप(काष्ठा dl_block) / 4 >= image->size) अणु
		prपूर्णांक_npe(KERN_INFO, npe, "firmware EOF block marker not "
			  "found\n");
		जाओ err;
	पूर्ण

#अगर DEBUG_FW
	prपूर्णांक_npe(KERN_DEBUG, npe, "%i firmware blocks found\n", blocks);
#पूर्ण_अगर

	table_end = blocks * माप(काष्ठा dl_block) / 4 + 1 /* खातापूर्ण marker */;
	क्रम (i = 0, blk = image->blocks; i < blocks; i++, blk++) अणु
		अगर (blk->offset > image->size - माप(काष्ठा dl_codeblock) / 4
		    || blk->offset < table_end) अणु
			prपूर्णांक_npe(KERN_INFO, npe, "invalid offset 0x%X of "
				  "firmware block #%i\n", blk->offset, i);
			जाओ err;
		पूर्ण

		cb = (काष्ठा dl_codeblock*)&image->data[blk->offset];
		अगर (blk->type == FW_BLOCK_TYPE_INSTR) अणु
			अगर (cb->npe_addr + cb->size > instr_size)
				जाओ too_big;
			cmd = CMD_WR_INS_MEM;
		पूर्ण अन्यथा अगर (blk->type == FW_BLOCK_TYPE_DATA) अणु
			अगर (cb->npe_addr + cb->size > data_size)
				जाओ too_big;
			cmd = CMD_WR_DATA_MEM;
		पूर्ण अन्यथा अणु
			prपूर्णांक_npe(KERN_INFO, npe, "invalid firmware block #%i "
				  "type 0x%X\n", i, blk->type);
			जाओ err;
		पूर्ण
		अगर (blk->offset + माप(*cb) / 4 + cb->size > image->size) अणु
			prपूर्णांक_npe(KERN_INFO, npe, "firmware block #%i doesn't "
				  "fit in firmware image: type %c, start 0x%X,"
				  " length 0x%X\n", i,
				  blk->type == FW_BLOCK_TYPE_INSTR ? 'I' : 'D',
				  cb->npe_addr, cb->size);
			जाओ err;
		पूर्ण

		क्रम (j = 0; j < cb->size; j++)
			npe_cmd_ग_लिखो(npe, cb->npe_addr + j, cmd, cb->data[j]);
	पूर्ण

	npe_start(npe);
	अगर (!npe_running(npe))
		prपूर्णांक_npe(KERN_ERR, npe, "unable to start\n");
	release_firmware(fw_entry);
	वापस 0;

too_big:
	prपूर्णांक_npe(KERN_INFO, npe, "firmware block #%i doesn't fit in NPE "
		  "memory: type %c, start 0x%X, length 0x%X\n", i,
		  blk->type == FW_BLOCK_TYPE_INSTR ? 'I' : 'D',
		  cb->npe_addr, cb->size);
err:
	release_firmware(fw_entry);
	वापस err;
पूर्ण


काष्ठा npe *npe_request(अचिन्हित id)
अणु
	अगर (id < NPE_COUNT)
		अगर (npe_tab[id].valid)
			अगर (try_module_get(THIS_MODULE))
				वापस &npe_tab[id];
	वापस शून्य;
पूर्ण

व्योम npe_release(काष्ठा npe *npe)
अणु
	module_put(THIS_MODULE);
पूर्ण

अटल पूर्णांक ixp4xx_npe_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i, found = 0;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा resource *res;

	क्रम (i = 0; i < NPE_COUNT; i++) अणु
		काष्ठा npe *npe = &npe_tab[i];

		res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, i);
		अगर (!res)
			वापस -ENODEV;

		अगर (!(ixp4xx_पढ़ो_feature_bits() &
		      (IXP4XX_FEATURE_RESET_NPEA << i))) अणु
			dev_info(dev, "NPE%d at 0x%08x-0x%08x not available\n",
				 i, res->start, res->end);
			जारी; /* NPE alपढ़ोy disabled or not present */
		पूर्ण
		npe->regs = devm_ioremap_resource(dev, res);
		अगर (IS_ERR(npe->regs))
			वापस PTR_ERR(npe->regs);

		अगर (npe_reset(npe)) अणु
			dev_info(dev, "NPE%d at 0x%08x-0x%08x does not reset\n",
				 i, res->start, res->end);
			जारी;
		पूर्ण
		npe->valid = 1;
		dev_info(dev, "NPE%d at 0x%08x-0x%08x registered\n",
			 i, res->start, res->end);
		found++;
	पूर्ण

	अगर (!found)
		वापस -ENODEV;
	वापस 0;
पूर्ण

अटल पूर्णांक ixp4xx_npe_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < NPE_COUNT; i++)
		अगर (npe_tab[i].regs) अणु
			npe_reset(&npe_tab[i]);
		पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id ixp4xx_npe_of_match[] = अणु
	अणु
		.compatible = "intel,ixp4xx-network-processing-engine",
        पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver ixp4xx_npe_driver = अणु
	.driver = अणु
		.name           = "ixp4xx-npe",
		.of_match_table = of_match_ptr(ixp4xx_npe_of_match),
	पूर्ण,
	.probe = ixp4xx_npe_probe,
	.हटाओ = ixp4xx_npe_हटाओ,
पूर्ण;
module_platक्रमm_driver(ixp4xx_npe_driver);

MODULE_AUTHOR("Krzysztof Halasa");
MODULE_LICENSE("GPL v2");
MODULE_FIRMWARE(NPE_A_FIRMWARE);
MODULE_FIRMWARE(NPE_B_FIRMWARE);
MODULE_FIRMWARE(NPE_C_FIRMWARE);

EXPORT_SYMBOL(npe_names);
EXPORT_SYMBOL(npe_running);
EXPORT_SYMBOL(npe_request);
EXPORT_SYMBOL(npe_release);
EXPORT_SYMBOL(npe_load_firmware);
EXPORT_SYMBOL(npe_send_message);
EXPORT_SYMBOL(npe_recv_message);
EXPORT_SYMBOL(npe_send_recv_message);
