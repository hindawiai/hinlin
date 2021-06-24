<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* qlogicpti.c: Perक्रमmance Technologies QlogicISP sbus card driver.
 *
 * Copyright (C) 1996, 2006, 2008 David S. Miller (davem@davemloft.net)
 *
 * A lot of this driver was directly stolen from Erik H. Moe's PCI
 * Qlogic ISP driver.  Mucho kuकरोs to him क्रम this code.
 *
 * An even bigger kuकरोs to John Grana at Perक्रमmance Technologies
 * क्रम providing me with the hardware to ग_लिखो this driver, you rule
 * John you really करो.
 *
 * May, 2, 1997: Added support क्रम QLGC,isp --jj
 */

#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/gfp.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/init.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/firmware.h>
#समावेश <linux/pgtable.h>

#समावेश <यंत्र/byteorder.h>

#समावेश "qlogicpti.h"

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/oplib.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_eh.h>
#समावेश <scsi/scsi_tcq.h>
#समावेश <scsi/scsi_host.h>

#घोषणा MAX_TARGETS	16
#घोषणा MAX_LUNS	8	/* 32 क्रम 1.31 F/W */

#घोषणा DEFAULT_LOOP_COUNT	10000

अटल काष्ठा qlogicpti *qptichain = शून्य;
अटल DEFINE_SPINLOCK(qptichain_lock);

#घोषणा PACKB(a, b)			(((a)<<4)|(b))

अटल स्थिर u_अक्षर mbox_param[] = अणु
	PACKB(1, 1),	/* MBOX_NO_OP */
	PACKB(5, 5),	/* MBOX_LOAD_RAM */
	PACKB(2, 0),	/* MBOX_EXEC_FIRMWARE */
	PACKB(5, 5),	/* MBOX_DUMP_RAM */
	PACKB(3, 3),	/* MBOX_WRITE_RAM_WORD */
	PACKB(2, 3),	/* MBOX_READ_RAM_WORD */
	PACKB(6, 6),	/* MBOX_MAILBOX_REG_TEST */
	PACKB(2, 3),	/* MBOX_VERIFY_CHECKSUM	*/
	PACKB(1, 3),	/* MBOX_ABOUT_FIRMWARE */
	PACKB(0, 0),	/* 0x0009 */
	PACKB(0, 0),	/* 0x000a */
	PACKB(0, 0),	/* 0x000b */
	PACKB(0, 0),	/* 0x000c */
	PACKB(0, 0),	/* 0x000d */
	PACKB(1, 2),	/* MBOX_CHECK_FIRMWARE */
	PACKB(0, 0),	/* 0x000f */
	PACKB(5, 5),	/* MBOX_INIT_REQ_QUEUE */
	PACKB(6, 6),	/* MBOX_INIT_RES_QUEUE */
	PACKB(4, 4),	/* MBOX_EXECUTE_IOCB */
	PACKB(2, 2),	/* MBOX_WAKE_UP	*/
	PACKB(1, 6),	/* MBOX_STOP_FIRMWARE */
	PACKB(4, 4),	/* MBOX_ABORT */
	PACKB(2, 2),	/* MBOX_ABORT_DEVICE */
	PACKB(3, 3),	/* MBOX_ABORT_TARGET */
	PACKB(2, 2),	/* MBOX_BUS_RESET */
	PACKB(2, 3),	/* MBOX_STOP_QUEUE */
	PACKB(2, 3),	/* MBOX_START_QUEUE */
	PACKB(2, 3),	/* MBOX_SINGLE_STEP_QUEUE */
	PACKB(2, 3),	/* MBOX_ABORT_QUEUE */
	PACKB(2, 4),	/* MBOX_GET_DEV_QUEUE_STATUS */
	PACKB(0, 0),	/* 0x001e */
	PACKB(1, 3),	/* MBOX_GET_FIRMWARE_STATUS */
	PACKB(1, 2),	/* MBOX_GET_INIT_SCSI_ID */
	PACKB(1, 2),	/* MBOX_GET_SELECT_TIMEOUT */
	PACKB(1, 3),	/* MBOX_GET_RETRY_COUNT	*/
	PACKB(1, 2),	/* MBOX_GET_TAG_AGE_LIMIT */
	PACKB(1, 2),	/* MBOX_GET_CLOCK_RATE */
	PACKB(1, 2),	/* MBOX_GET_ACT_NEG_STATE */
	PACKB(1, 2),	/* MBOX_GET_ASYNC_DATA_SETUP_TIME */
	PACKB(1, 3),	/* MBOX_GET_SBUS_PARAMS */
	PACKB(2, 4),	/* MBOX_GET_TARGET_PARAMS */
	PACKB(2, 4),	/* MBOX_GET_DEV_QUEUE_PARAMS */
	PACKB(0, 0),	/* 0x002a */
	PACKB(0, 0),	/* 0x002b */
	PACKB(0, 0),	/* 0x002c */
	PACKB(0, 0),	/* 0x002d */
	PACKB(0, 0),	/* 0x002e */
	PACKB(0, 0),	/* 0x002f */
	PACKB(2, 2),	/* MBOX_SET_INIT_SCSI_ID */
	PACKB(2, 2),	/* MBOX_SET_SELECT_TIMEOUT */
	PACKB(3, 3),	/* MBOX_SET_RETRY_COUNT	*/
	PACKB(2, 2),	/* MBOX_SET_TAG_AGE_LIMIT */
	PACKB(2, 2),	/* MBOX_SET_CLOCK_RATE */
	PACKB(2, 2),	/* MBOX_SET_ACTIVE_NEG_STATE */
	PACKB(2, 2),	/* MBOX_SET_ASYNC_DATA_SETUP_TIME */
	PACKB(3, 3),	/* MBOX_SET_SBUS_CONTROL_PARAMS */
	PACKB(4, 4),	/* MBOX_SET_TARGET_PARAMS */
	PACKB(4, 4),	/* MBOX_SET_DEV_QUEUE_PARAMS */
	PACKB(0, 0),	/* 0x003a */
	PACKB(0, 0),	/* 0x003b */
	PACKB(0, 0),	/* 0x003c */
	PACKB(0, 0),	/* 0x003d */
	PACKB(0, 0),	/* 0x003e */
	PACKB(0, 0),	/* 0x003f */
	PACKB(0, 0),	/* 0x0040 */
	PACKB(0, 0),	/* 0x0041 */
	PACKB(0, 0)	/* 0x0042 */
पूर्ण;

#घोषणा MAX_MBOX_COMMAND	ARRAY_SIZE(mbox_param)

/* queue length's _must_ be घातer of two: */
#घोषणा QUEUE_DEPTH(in, out, ql)	((in - out) & (ql))
#घोषणा REQ_QUEUE_DEPTH(in, out)	QUEUE_DEPTH(in, out, 		     \
						    QLOGICPTI_REQ_QUEUE_LEN)
#घोषणा RES_QUEUE_DEPTH(in, out)	QUEUE_DEPTH(in, out, RES_QUEUE_LEN)

अटल अंतरभूत व्योम qlogicpti_enable_irqs(काष्ठा qlogicpti *qpti)
अणु
	sbus_ग_लिखोw(SBUS_CTRL_ERIRQ | SBUS_CTRL_GENAB,
		    qpti->qregs + SBUS_CTRL);
पूर्ण

अटल अंतरभूत व्योम qlogicpti_disable_irqs(काष्ठा qlogicpti *qpti)
अणु
	sbus_ग_लिखोw(0, qpti->qregs + SBUS_CTRL);
पूर्ण

अटल अंतरभूत व्योम set_sbus_cfg1(काष्ठा qlogicpti *qpti)
अणु
	u16 val;
	u8 bursts = qpti->bursts;

#अगर 0	/* It appears that at least PTI cards करो not support
	 * 64-byte bursts and that setting the B64 bit actually
	 * is a nop and the chip ends up using the smallest burst
	 * size. -DaveM
	 */
	अगर (sbus_can_burst64() && (bursts & DMA_BURST64)) अणु
		val = (SBUS_CFG1_BENAB | SBUS_CFG1_B64);
	पूर्ण अन्यथा
#पूर्ण_अगर
	अगर (bursts & DMA_BURST32) अणु
		val = (SBUS_CFG1_BENAB | SBUS_CFG1_B32);
	पूर्ण अन्यथा अगर (bursts & DMA_BURST16) अणु
		val = (SBUS_CFG1_BENAB | SBUS_CFG1_B16);
	पूर्ण अन्यथा अगर (bursts & DMA_BURST8) अणु
		val = (SBUS_CFG1_BENAB | SBUS_CFG1_B8);
	पूर्ण अन्यथा अणु
		val = 0; /* No sbus bursts क्रम you... */
	पूर्ण
	sbus_ग_लिखोw(val, qpti->qregs + SBUS_CFG1);
पूर्ण

अटल पूर्णांक qlogicpti_mbox_command(काष्ठा qlogicpti *qpti, u_लघु param[], पूर्णांक क्रमce)
अणु
	पूर्णांक loop_count;
	u16 पंचांगp;

	अगर (mbox_param[param[0]] == 0)
		वापस 1;

	/* Set SBUS semaphore. */
	पंचांगp = sbus_पढ़ोw(qpti->qregs + SBUS_SEMAPHORE);
	पंचांगp |= SBUS_SEMAPHORE_LCK;
	sbus_ग_लिखोw(पंचांगp, qpti->qregs + SBUS_SEMAPHORE);

	/* Wait क्रम host IRQ bit to clear. */
	loop_count = DEFAULT_LOOP_COUNT;
	जबतक (--loop_count && (sbus_पढ़ोw(qpti->qregs + HCCTRL) & HCCTRL_HIRQ)) अणु
		barrier();
		cpu_relax();
	पूर्ण
	अगर (!loop_count)
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: mbox_command loop timeout #1\n",
		       qpti->qpti_id);

	/* Write mailbox command रेजिस्टरs. */
	चयन (mbox_param[param[0]] >> 4) अणु
	हाल 6: sbus_ग_लिखोw(param[5], qpti->qregs + MBOX5);
		fallthrough;
	हाल 5: sbus_ग_लिखोw(param[4], qpti->qregs + MBOX4);
		fallthrough;
	हाल 4: sbus_ग_लिखोw(param[3], qpti->qregs + MBOX3);
		fallthrough;
	हाल 3: sbus_ग_लिखोw(param[2], qpti->qregs + MBOX2);
		fallthrough;
	हाल 2: sbus_ग_लिखोw(param[1], qpti->qregs + MBOX1);
		fallthrough;
	हाल 1: sbus_ग_लिखोw(param[0], qpti->qregs + MBOX0);
	पूर्ण

	/* Clear RISC पूर्णांकerrupt. */
	पंचांगp = sbus_पढ़ोw(qpti->qregs + HCCTRL);
	पंचांगp |= HCCTRL_CRIRQ;
	sbus_ग_लिखोw(पंचांगp, qpti->qregs + HCCTRL);

	/* Clear SBUS semaphore. */
	sbus_ग_लिखोw(0, qpti->qregs + SBUS_SEMAPHORE);

	/* Set HOST पूर्णांकerrupt. */
	पंचांगp = sbus_पढ़ोw(qpti->qregs + HCCTRL);
	पंचांगp |= HCCTRL_SHIRQ;
	sbus_ग_लिखोw(पंचांगp, qpti->qregs + HCCTRL);

	/* Wait क्रम HOST पूर्णांकerrupt clears. */
	loop_count = DEFAULT_LOOP_COUNT;
	जबतक (--loop_count &&
	       (sbus_पढ़ोw(qpti->qregs + HCCTRL) & HCCTRL_CRIRQ))
		udelay(20);
	अगर (!loop_count)
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: mbox_command[%04x] loop timeout #2\n",
		       qpti->qpti_id, param[0]);

	/* Wait क्रम SBUS semaphore to get set. */
	loop_count = DEFAULT_LOOP_COUNT;
	जबतक (--loop_count &&
	       !(sbus_पढ़ोw(qpti->qregs + SBUS_SEMAPHORE) & SBUS_SEMAPHORE_LCK)) अणु
		udelay(20);

		/* Workaround क्रम some buggy chips. */
		अगर (sbus_पढ़ोw(qpti->qregs + MBOX0) & 0x4000)
			अवरोध;
	पूर्ण
	अगर (!loop_count)
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: mbox_command[%04x] loop timeout #3\n",
		       qpti->qpti_id, param[0]);

	/* Wait क्रम MBOX busy condition to go away. */
	loop_count = DEFAULT_LOOP_COUNT;
	जबतक (--loop_count && (sbus_पढ़ोw(qpti->qregs + MBOX0) == 0x04))
		udelay(20);
	अगर (!loop_count)
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: mbox_command[%04x] loop timeout #4\n",
		       qpti->qpti_id, param[0]);

	/* Read back output parameters. */
	चयन (mbox_param[param[0]] & 0xf) अणु
	हाल 6: param[5] = sbus_पढ़ोw(qpti->qregs + MBOX5);
		fallthrough;
	हाल 5: param[4] = sbus_पढ़ोw(qpti->qregs + MBOX4);
		fallthrough;
	हाल 4: param[3] = sbus_पढ़ोw(qpti->qregs + MBOX3);
		fallthrough;
	हाल 3: param[2] = sbus_पढ़ोw(qpti->qregs + MBOX2);
		fallthrough;
	हाल 2: param[1] = sbus_पढ़ोw(qpti->qregs + MBOX1);
		fallthrough;
	हाल 1: param[0] = sbus_पढ़ोw(qpti->qregs + MBOX0);
	पूर्ण

	/* Clear RISC पूर्णांकerrupt. */
	पंचांगp = sbus_पढ़ोw(qpti->qregs + HCCTRL);
	पंचांगp |= HCCTRL_CRIRQ;
	sbus_ग_लिखोw(पंचांगp, qpti->qregs + HCCTRL);

	/* Release SBUS semaphore. */
	पंचांगp = sbus_पढ़ोw(qpti->qregs + SBUS_SEMAPHORE);
	पंचांगp &= ~(SBUS_SEMAPHORE_LCK);
	sbus_ग_लिखोw(पंचांगp, qpti->qregs + SBUS_SEMAPHORE);

	/* We're करोne. */
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम qlogicpti_set_hostdev_शेषs(काष्ठा qlogicpti *qpti)
अणु
	पूर्णांक i;

	qpti->host_param.initiator_scsi_id = qpti->scsi_id;
	qpti->host_param.bus_reset_delay = 3;
	qpti->host_param.retry_count = 0;
	qpti->host_param.retry_delay = 5;
	qpti->host_param.async_data_setup_समय = 3;
	qpti->host_param.req_ack_active_negation = 1;
	qpti->host_param.data_line_active_negation = 1;
	qpti->host_param.data_dma_burst_enable = 1;
	qpti->host_param.command_dma_burst_enable = 1;
	qpti->host_param.tag_aging = 8;
	qpti->host_param.selection_समयout = 250;
	qpti->host_param.max_queue_depth = 256;

	क्रम(i = 0; i < MAX_TARGETS; i++) अणु
		/*
		 * disconnect, parity, arq, reneg on reset, and, oddly enough
		 * tags...the midlayer's notion of tagged support has to match
		 * our device settings, and since we base whether we enable a
		 * tag on a  per-cmnd basis upon what the midlayer sez, we
		 * actually enable the capability here.
		 */
		qpti->dev_param[i].device_flags = 0xcd;
		qpti->dev_param[i].execution_throttle = 16;
		अगर (qpti->ultra) अणु
			qpti->dev_param[i].synchronous_period = 12;
			qpti->dev_param[i].synchronous_offset = 8;
		पूर्ण अन्यथा अणु
			qpti->dev_param[i].synchronous_period = 25;
			qpti->dev_param[i].synchronous_offset = 12;
		पूर्ण
		qpti->dev_param[i].device_enable = 1;
	पूर्ण
पूर्ण

अटल पूर्णांक qlogicpti_reset_hardware(काष्ठा Scsi_Host *host)
अणु
	काष्ठा qlogicpti *qpti = (काष्ठा qlogicpti *) host->hostdata;
	u_लघु param[6];
	अचिन्हित लघु risc_code_addr;
	पूर्णांक loop_count, i;
	अचिन्हित दीर्घ flags;

	risc_code_addr = 0x1000;	/* all load addresses are at 0x1000 */

	spin_lock_irqsave(host->host_lock, flags);

	sbus_ग_लिखोw(HCCTRL_PAUSE, qpti->qregs + HCCTRL);

	/* Only reset the scsi bus अगर it is not मुक्त. */
	अगर (sbus_पढ़ोw(qpti->qregs + CPU_PCTRL) & CPU_PCTRL_BSY) अणु
		sbus_ग_लिखोw(CPU_ORIDE_RMOD, qpti->qregs + CPU_ORIDE);
		sbus_ग_लिखोw(CPU_CMD_BRESET, qpti->qregs + CPU_CMD);
		udelay(400);
	पूर्ण

	sbus_ग_लिखोw(SBUS_CTRL_RESET, qpti->qregs + SBUS_CTRL);
	sbus_ग_लिखोw((DMA_CTRL_CCLEAR | DMA_CTRL_CIRQ), qpti->qregs + CMD_DMA_CTRL);
	sbus_ग_लिखोw((DMA_CTRL_CCLEAR | DMA_CTRL_CIRQ), qpti->qregs + DATA_DMA_CTRL);

	loop_count = DEFAULT_LOOP_COUNT;
	जबतक (--loop_count && ((sbus_पढ़ोw(qpti->qregs + MBOX0) & 0xff) == 0x04))
		udelay(20);
	अगर (!loop_count)
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: reset_hardware loop timeout\n",
		       qpti->qpti_id);

	sbus_ग_लिखोw(HCCTRL_PAUSE, qpti->qregs + HCCTRL);
	set_sbus_cfg1(qpti);
	qlogicpti_enable_irqs(qpti);

	अगर (sbus_पढ़ोw(qpti->qregs + RISC_PSR) & RISC_PSR_ULTRA) अणु
		qpti->ultra = 1;
		sbus_ग_लिखोw((RISC_MTREG_P0ULTRA | RISC_MTREG_P1ULTRA),
			    qpti->qregs + RISC_MTREG);
	पूर्ण अन्यथा अणु
		qpti->ultra = 0;
		sbus_ग_लिखोw((RISC_MTREG_P0DFLT | RISC_MTREG_P1DFLT),
			    qpti->qregs + RISC_MTREG);
	पूर्ण

	/* reset adapter and per-device शेष values. */
	/* करो it after finding out whether we're ultra mode capable */
	qlogicpti_set_hostdev_शेषs(qpti);

	/* Release the RISC processor. */
	sbus_ग_लिखोw(HCCTRL_REL, qpti->qregs + HCCTRL);

	/* Get RISC to start executing the firmware code. */
	param[0] = MBOX_EXEC_FIRMWARE;
	param[1] = risc_code_addr;
	अगर (qlogicpti_mbox_command(qpti, param, 1)) अणु
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: Cannot execute ISP firmware.\n",
		       qpti->qpti_id);
		spin_unlock_irqrestore(host->host_lock, flags);
		वापस 1;
	पूर्ण

	/* Set initiator scsi ID. */
	param[0] = MBOX_SET_INIT_SCSI_ID;
	param[1] = qpti->host_param.initiator_scsi_id;
	अगर (qlogicpti_mbox_command(qpti, param, 1) ||
	   (param[0] != MBOX_COMMAND_COMPLETE)) अणु
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: Cannot set initiator SCSI ID.\n",
		       qpti->qpti_id);
		spin_unlock_irqrestore(host->host_lock, flags);
		वापस 1;
	पूर्ण

	/* Initialize state of the queues, both hw and sw. */
	qpti->req_in_ptr = qpti->res_out_ptr = 0;

	param[0] = MBOX_INIT_RES_QUEUE;
	param[1] = RES_QUEUE_LEN + 1;
	param[2] = (u_लघु) (qpti->res_dvma >> 16);
	param[3] = (u_लघु) (qpti->res_dvma & 0xffff);
	param[4] = param[5] = 0;
	अगर (qlogicpti_mbox_command(qpti, param, 1)) अणु
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: Cannot init response queue.\n",
		       qpti->qpti_id);
		spin_unlock_irqrestore(host->host_lock, flags);
		वापस 1;
	पूर्ण

	param[0] = MBOX_INIT_REQ_QUEUE;
	param[1] = QLOGICPTI_REQ_QUEUE_LEN + 1;
	param[2] = (u_लघु) (qpti->req_dvma >> 16);
	param[3] = (u_लघु) (qpti->req_dvma & 0xffff);
	param[4] = param[5] = 0;
	अगर (qlogicpti_mbox_command(qpti, param, 1)) अणु
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: Cannot init request queue.\n",
		       qpti->qpti_id);
		spin_unlock_irqrestore(host->host_lock, flags);
		वापस 1;
	पूर्ण

	param[0] = MBOX_SET_RETRY_COUNT;
	param[1] = qpti->host_param.retry_count;
	param[2] = qpti->host_param.retry_delay;
	qlogicpti_mbox_command(qpti, param, 0);

	param[0] = MBOX_SET_TAG_AGE_LIMIT;
	param[1] = qpti->host_param.tag_aging;
	qlogicpti_mbox_command(qpti, param, 0);

	क्रम (i = 0; i < MAX_TARGETS; i++) अणु
		param[0] = MBOX_GET_DEV_QUEUE_PARAMS;
		param[1] = (i << 8);
		qlogicpti_mbox_command(qpti, param, 0);
	पूर्ण

	param[0] = MBOX_GET_FIRMWARE_STATUS;
	qlogicpti_mbox_command(qpti, param, 0);

	param[0] = MBOX_SET_SELECT_TIMEOUT;
	param[1] = qpti->host_param.selection_समयout;
	qlogicpti_mbox_command(qpti, param, 0);

	क्रम (i = 0; i < MAX_TARGETS; i++) अणु
		param[0] = MBOX_SET_TARGET_PARAMS;
		param[1] = (i << 8);
		param[2] = (qpti->dev_param[i].device_flags << 8);
		/*
		 * Since we're now loading 1.31 f/w, क्रमce narrow/async.
		 */
		param[2] |= 0xc0;
		param[3] = 0;	/* no offset, we करो not have sync mode yet */
		qlogicpti_mbox_command(qpti, param, 0);
	पूर्ण

	/*
	 * Always (sigh) करो an initial bus reset (kicks f/w).
	 */
	param[0] = MBOX_BUS_RESET;
	param[1] = qpti->host_param.bus_reset_delay;
	qlogicpti_mbox_command(qpti, param, 0);
	qpti->send_marker = 1;

	spin_unlock_irqrestore(host->host_lock, flags);
	वापस 0;
पूर्ण

#घोषणा PTI_RESET_LIMIT 400

अटल पूर्णांक qlogicpti_load_firmware(काष्ठा qlogicpti *qpti)
अणु
	स्थिर काष्ठा firmware *fw;
	स्थिर अक्षर fwname[] = "qlogic/isp1000.bin";
	स्थिर __le16 *fw_data;
	काष्ठा Scsi_Host *host = qpti->qhost;
	अचिन्हित लघु csum = 0;
	अचिन्हित लघु param[6];
	अचिन्हित लघु risc_code_addr, risc_code_length;
	पूर्णांक err;
	अचिन्हित दीर्घ flags;
	पूर्णांक i, समयout;

	err = request_firmware(&fw, fwname, &qpti->op->dev);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Failed to load image \"%s\" err %d\n",
		       fwname, err);
		वापस err;
	पूर्ण
	अगर (fw->size % 2) अणु
		prपूर्णांकk(KERN_ERR "Bogus length %zu in image \"%s\"\n",
		       fw->size, fwname);
		err = -EINVAL;
		जाओ outfirm;
	पूर्ण
	fw_data = (स्थिर __le16 *)&fw->data[0];
	risc_code_addr = 0x1000;	/* all f/w modules load at 0x1000 */
	risc_code_length = fw->size / 2;

	spin_lock_irqsave(host->host_lock, flags);

	/* Verअगरy the checksum twice, one beक्रमe loading it, and once
	 * afterwards via the mailbox commands.
	 */
	क्रम (i = 0; i < risc_code_length; i++)
		csum += __le16_to_cpu(fw_data[i]);
	अगर (csum) अणु
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: Aieee, firmware checksum failed!",
		       qpti->qpti_id);
		err = 1;
		जाओ out;
	पूर्ण		
	sbus_ग_लिखोw(SBUS_CTRL_RESET, qpti->qregs + SBUS_CTRL);
	sbus_ग_लिखोw((DMA_CTRL_CCLEAR | DMA_CTRL_CIRQ), qpti->qregs + CMD_DMA_CTRL);
	sbus_ग_लिखोw((DMA_CTRL_CCLEAR | DMA_CTRL_CIRQ), qpti->qregs + DATA_DMA_CTRL);
	समयout = PTI_RESET_LIMIT;
	जबतक (--समयout && (sbus_पढ़ोw(qpti->qregs + SBUS_CTRL) & SBUS_CTRL_RESET))
		udelay(20);
	अगर (!समयout) अणु
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: Cannot reset the ISP.", qpti->qpti_id);
		err = 1;
		जाओ out;
	पूर्ण

	sbus_ग_लिखोw(HCCTRL_RESET, qpti->qregs + HCCTRL);
	mdelay(1);

	sbus_ग_लिखोw((SBUS_CTRL_GENAB | SBUS_CTRL_ERIRQ), qpti->qregs + SBUS_CTRL);
	set_sbus_cfg1(qpti);
	sbus_ग_लिखोw(0, qpti->qregs + SBUS_SEMAPHORE);

	अगर (sbus_पढ़ोw(qpti->qregs + RISC_PSR) & RISC_PSR_ULTRA) अणु
		qpti->ultra = 1;
		sbus_ग_लिखोw((RISC_MTREG_P0ULTRA | RISC_MTREG_P1ULTRA),
			    qpti->qregs + RISC_MTREG);
	पूर्ण अन्यथा अणु
		qpti->ultra = 0;
		sbus_ग_लिखोw((RISC_MTREG_P0DFLT | RISC_MTREG_P1DFLT),
			    qpti->qregs + RISC_MTREG);
	पूर्ण

	sbus_ग_लिखोw(HCCTRL_REL, qpti->qregs + HCCTRL);

	/* Pin lines are only stable जबतक RISC is छोड़ोd. */
	sbus_ग_लिखोw(HCCTRL_PAUSE, qpti->qregs + HCCTRL);
	अगर (sbus_पढ़ोw(qpti->qregs + CPU_PDIFF) & CPU_PDIFF_MODE)
		qpti->dअगरferential = 1;
	अन्यथा
		qpti->dअगरferential = 0;
	sbus_ग_लिखोw(HCCTRL_REL, qpti->qregs + HCCTRL);

	/* This shouldn't be necessary- we've reset things so we should be
	   running from the ROM now.. */

	param[0] = MBOX_STOP_FIRMWARE;
	param[1] = param[2] = param[3] = param[4] = param[5] = 0;
	अगर (qlogicpti_mbox_command(qpti, param, 1)) अणु
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: Cannot stop firmware for reload.\n",
		       qpti->qpti_id);
		err = 1;
		जाओ out;
	पूर्ण		

	/* Load it up.. */
	क्रम (i = 0; i < risc_code_length; i++) अणु
		param[0] = MBOX_WRITE_RAM_WORD;
		param[1] = risc_code_addr + i;
		param[2] = __le16_to_cpu(fw_data[i]);
		अगर (qlogicpti_mbox_command(qpti, param, 1) ||
		    param[0] != MBOX_COMMAND_COMPLETE) अणु
			prपूर्णांकk("qlogicpti%d: Firmware dload failed, I'm bolixed!\n",
			       qpti->qpti_id);
			err = 1;
			जाओ out;
		पूर्ण
	पूर्ण

	/* Reset the ISP again. */
	sbus_ग_लिखोw(HCCTRL_RESET, qpti->qregs + HCCTRL);
	mdelay(1);

	qlogicpti_enable_irqs(qpti);
	sbus_ग_लिखोw(0, qpti->qregs + SBUS_SEMAPHORE);
	sbus_ग_लिखोw(HCCTRL_REL, qpti->qregs + HCCTRL);

	/* Ask ISP to verअगरy the checksum of the new code. */
	param[0] = MBOX_VERIFY_CHECKSUM;
	param[1] = risc_code_addr;
	अगर (qlogicpti_mbox_command(qpti, param, 1) ||
	    (param[0] != MBOX_COMMAND_COMPLETE)) अणु
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: New firmware csum failure!\n",
		       qpti->qpti_id);
		err = 1;
		जाओ out;
	पूर्ण

	/* Start using newly करोwnloaded firmware. */
	param[0] = MBOX_EXEC_FIRMWARE;
	param[1] = risc_code_addr;
	qlogicpti_mbox_command(qpti, param, 1);

	param[0] = MBOX_ABOUT_FIRMWARE;
	अगर (qlogicpti_mbox_command(qpti, param, 1) ||
	    (param[0] != MBOX_COMMAND_COMPLETE)) अणु
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: AboutFirmware cmd fails.\n",
		       qpti->qpti_id);
		err = 1;
		जाओ out;
	पूर्ण

	/* Snag the major and minor revisions from the result. */
	qpti->fware_majrev = param[1];
	qpti->fware_minrev = param[2];
	qpti->fware_micrev = param[3];

	/* Set the घड़ी rate */
	param[0] = MBOX_SET_CLOCK_RATE;
	param[1] = qpti->घड़ी;
	अगर (qlogicpti_mbox_command(qpti, param, 1) ||
	    (param[0] != MBOX_COMMAND_COMPLETE)) अणु
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: could not set clock rate.\n",
		       qpti->qpti_id);
		err = 1;
		जाओ out;
	पूर्ण

	अगर (qpti->is_pti != 0) अणु
		/* Load scsi initiator ID and पूर्णांकerrupt level पूर्णांकo sbus अटल ram. */
		param[0] = MBOX_WRITE_RAM_WORD;
		param[1] = 0xff80;
		param[2] = (अचिन्हित लघु) qpti->scsi_id;
		qlogicpti_mbox_command(qpti, param, 1);

		param[0] = MBOX_WRITE_RAM_WORD;
		param[1] = 0xff00;
		param[2] = (अचिन्हित लघु) 3;
		qlogicpti_mbox_command(qpti, param, 1);
	पूर्ण

out:
	spin_unlock_irqrestore(host->host_lock, flags);
outfirm:
	release_firmware(fw);
	वापस err;
पूर्ण

अटल पूर्णांक qlogicpti_verअगरy_पंचांगon(काष्ठा qlogicpti *qpti)
अणु
	पूर्णांक curstat = sbus_पढ़ोb(qpti->sreg);

	curstat &= 0xf0;
	अगर (!(curstat & SREG_FUSE) && (qpti->swsreg & SREG_FUSE))
		prपूर्णांकk("qlogicpti%d: Fuse returned to normal state.\n", qpti->qpti_id);
	अगर (!(curstat & SREG_TPOWER) && (qpti->swsreg & SREG_TPOWER))
		prपूर्णांकk("qlogicpti%d: termpwr back to normal state.\n", qpti->qpti_id);
	अगर (curstat != qpti->swsreg) अणु
		पूर्णांक error = 0;
		अगर (curstat & SREG_FUSE) अणु
			error++;
			prपूर्णांकk("qlogicpti%d: Fuse is open!\n", qpti->qpti_id);
		पूर्ण
		अगर (curstat & SREG_TPOWER) अणु
			error++;
			prपूर्णांकk("qlogicpti%d: termpwr failure\n", qpti->qpti_id);
		पूर्ण
		अगर (qpti->dअगरferential &&
		    (curstat & SREG_DSENSE) != SREG_DSENSE) अणु
			error++;
			prपूर्णांकk("qlogicpti%d: You have a single ended device on a "
			       "differential bus!  Please fix!\n", qpti->qpti_id);
		पूर्ण
		qpti->swsreg = curstat;
		वापस error;
	पूर्ण
	वापस 0;
पूर्ण

अटल irqवापस_t qpti_पूर्णांकr(पूर्णांक irq, व्योम *dev_id);

अटल व्योम qpti_chain_add(काष्ठा qlogicpti *qpti)
अणु
	spin_lock_irq(&qptichain_lock);
	अगर (qptichain != शून्य) अणु
		काष्ठा qlogicpti *qlink = qptichain;

		जबतक(qlink->next)
			qlink = qlink->next;
		qlink->next = qpti;
	पूर्ण अन्यथा अणु
		qptichain = qpti;
	पूर्ण
	qpti->next = शून्य;
	spin_unlock_irq(&qptichain_lock);
पूर्ण

अटल व्योम qpti_chain_del(काष्ठा qlogicpti *qpti)
अणु
	spin_lock_irq(&qptichain_lock);
	अगर (qptichain == qpti) अणु
		qptichain = qpti->next;
	पूर्ण अन्यथा अणु
		काष्ठा qlogicpti *qlink = qptichain;
		जबतक(qlink->next != qpti)
			qlink = qlink->next;
		qlink->next = qpti->next;
	पूर्ण
	qpti->next = शून्य;
	spin_unlock_irq(&qptichain_lock);
पूर्ण

अटल पूर्णांक qpti_map_regs(काष्ठा qlogicpti *qpti)
अणु
	काष्ठा platक्रमm_device *op = qpti->op;

	qpti->qregs = of_ioremap(&op->resource[0], 0,
				 resource_size(&op->resource[0]),
				 "PTI Qlogic/ISP");
	अगर (!qpti->qregs) अणु
		prपूर्णांकk("PTI: Qlogic/ISP registers are unmappable\n");
		वापस -ENODEV;
	पूर्ण
	अगर (qpti->is_pti) अणु
		qpti->sreg = of_ioremap(&op->resource[0], (16 * 4096),
					माप(अचिन्हित अक्षर),
					"PTI Qlogic/ISP statreg");
		अगर (!qpti->sreg) अणु
			prपूर्णांकk("PTI: Qlogic/ISP status register is unmappable\n");
			वापस -ENODEV;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक qpti_रेजिस्टर_irq(काष्ठा qlogicpti *qpti)
अणु
	काष्ठा platक्रमm_device *op = qpti->op;

	qpti->qhost->irq = qpti->irq = op->archdata.irqs[0];

	/* We used to try various overly-clever things to
	 * reduce the पूर्णांकerrupt processing overhead on
	 * sun4c/sun4m when multiple PTI's shared the
	 * same IRQ.  It was too complex and messy to
	 * sanely मुख्यtain.
	 */
	अगर (request_irq(qpti->irq, qpti_पूर्णांकr,
			IRQF_SHARED, "QlogicPTI", qpti))
		जाओ fail;

	prपूर्णांकk("qlogicpti%d: IRQ %d ", qpti->qpti_id, qpti->irq);

	वापस 0;

fail:
	prपूर्णांकk("qlogicpti%d: Cannot acquire irq line\n", qpti->qpti_id);
	वापस -1;
पूर्ण

अटल व्योम qpti_get_scsi_id(काष्ठा qlogicpti *qpti)
अणु
	काष्ठा platक्रमm_device *op = qpti->op;
	काष्ठा device_node *dp;

	dp = op->dev.of_node;

	qpti->scsi_id = of_getपूर्णांकprop_शेष(dp, "initiator-id", -1);
	अगर (qpti->scsi_id == -1)
		qpti->scsi_id = of_getपूर्णांकprop_शेष(dp, "scsi-initiator-id",
						      -1);
	अगर (qpti->scsi_id == -1)
		qpti->scsi_id =
			of_getपूर्णांकprop_शेष(dp->parent,
					      "scsi-initiator-id", 7);
	qpti->qhost->this_id = qpti->scsi_id;
	qpti->qhost->max_sectors = 64;

	prपूर्णांकk("SCSI ID %d ", qpti->scsi_id);
पूर्ण

अटल व्योम qpti_get_bursts(काष्ठा qlogicpti *qpti)
अणु
	काष्ठा platक्रमm_device *op = qpti->op;
	u8 bursts, bmask;

	bursts = of_getपूर्णांकprop_शेष(op->dev.of_node, "burst-sizes", 0xff);
	bmask = of_getपूर्णांकprop_शेष(op->dev.of_node->parent, "burst-sizes", 0xff);
	अगर (bmask != 0xff)
		bursts &= bmask;
	अगर (bursts == 0xff ||
	    (bursts & DMA_BURST16) == 0 ||
	    (bursts & DMA_BURST32) == 0)
		bursts = (DMA_BURST32 - 1);

	qpti->bursts = bursts;
पूर्ण

अटल व्योम qpti_get_घड़ी(काष्ठा qlogicpti *qpti)
अणु
	अचिन्हित पूर्णांक cfreq;

	/* Check क्रम what the घड़ी input to this card is.
	 * Default to 40Mhz.
	 */
	cfreq = prom_getपूर्णांकशेष(qpti->prom_node,"clock-frequency",40000000);
	qpti->घड़ी = (cfreq + 500000)/1000000;
	अगर (qpti->घड़ी == 0) /* bullshit */
		qpti->घड़ी = 40;
पूर्ण

/* The request and response queues must each be aligned
 * on a page boundary.
 */
अटल पूर्णांक qpti_map_queues(काष्ठा qlogicpti *qpti)
अणु
	काष्ठा platक्रमm_device *op = qpti->op;

#घोषणा QSIZE(entries)	(((entries) + 1) * QUEUE_ENTRY_LEN)
	qpti->res_cpu = dma_alloc_coherent(&op->dev,
					   QSIZE(RES_QUEUE_LEN),
					   &qpti->res_dvma, GFP_ATOMIC);
	अगर (qpti->res_cpu == शून्य ||
	    qpti->res_dvma == 0) अणु
		prपूर्णांकk("QPTI: Cannot map response queue.\n");
		वापस -1;
	पूर्ण

	qpti->req_cpu = dma_alloc_coherent(&op->dev,
					   QSIZE(QLOGICPTI_REQ_QUEUE_LEN),
					   &qpti->req_dvma, GFP_ATOMIC);
	अगर (qpti->req_cpu == शून्य ||
	    qpti->req_dvma == 0) अणु
		dma_मुक्त_coherent(&op->dev, QSIZE(RES_QUEUE_LEN),
				  qpti->res_cpu, qpti->res_dvma);
		prपूर्णांकk("QPTI: Cannot map request queue.\n");
		वापस -1;
	पूर्ण
	स_रखो(qpti->res_cpu, 0, QSIZE(RES_QUEUE_LEN));
	स_रखो(qpti->req_cpu, 0, QSIZE(QLOGICPTI_REQ_QUEUE_LEN));
	वापस 0;
पूर्ण

स्थिर अक्षर *qlogicpti_info(काष्ठा Scsi_Host *host)
अणु
	अटल अक्षर buf[80];
	काष्ठा qlogicpti *qpti = (काष्ठा qlogicpti *) host->hostdata;

	प्र_लिखो(buf, "PTI Qlogic,ISP SBUS SCSI irq %d regs at %p",
		qpti->qhost->irq, qpti->qregs);
	वापस buf;
पूर्ण

/* I am a certअगरied frobtronicist. */
अटल अंतरभूत व्योम marker_frob(काष्ठा Command_Entry *cmd)
अणु
	काष्ठा Marker_Entry *marker = (काष्ठा Marker_Entry *) cmd;

	स_रखो(marker, 0, माप(काष्ठा Marker_Entry));
	marker->hdr.entry_cnt = 1;
	marker->hdr.entry_type = ENTRY_MARKER;
	marker->modअगरier = SYNC_ALL;
	marker->rsvd = 0;
पूर्ण

अटल अंतरभूत व्योम cmd_frob(काष्ठा Command_Entry *cmd, काष्ठा scsi_cmnd *Cmnd,
			    काष्ठा qlogicpti *qpti)
अणु
	स_रखो(cmd, 0, माप(काष्ठा Command_Entry));
	cmd->hdr.entry_cnt = 1;
	cmd->hdr.entry_type = ENTRY_COMMAND;
	cmd->target_id = Cmnd->device->id;
	cmd->target_lun = Cmnd->device->lun;
	cmd->cdb_length = Cmnd->cmd_len;
	cmd->control_flags = 0;
	अगर (Cmnd->device->tagged_supported) अणु
		अगर (qpti->cmd_count[Cmnd->device->id] == 0)
			qpti->tag_ages[Cmnd->device->id] = jअगरfies;
		अगर (समय_after(jअगरfies, qpti->tag_ages[Cmnd->device->id] + (5*HZ))) अणु
			cmd->control_flags = CFLAG_ORDERED_TAG;
			qpti->tag_ages[Cmnd->device->id] = jअगरfies;
		पूर्ण अन्यथा
			cmd->control_flags = CFLAG_SIMPLE_TAG;
	पूर्ण
	अगर ((Cmnd->cmnd[0] == WRITE_6) ||
	    (Cmnd->cmnd[0] == WRITE_10) ||
	    (Cmnd->cmnd[0] == WRITE_12))
		cmd->control_flags |= CFLAG_WRITE;
	अन्यथा
		cmd->control_flags |= CFLAG_READ;
	cmd->समय_out = Cmnd->request->समयout/HZ;
	स_नकल(cmd->cdb, Cmnd->cmnd, Cmnd->cmd_len);
पूर्ण

/* Do it to it baby. */
अटल अंतरभूत पूर्णांक load_cmd(काष्ठा scsi_cmnd *Cmnd, काष्ठा Command_Entry *cmd,
			   काष्ठा qlogicpti *qpti, u_पूर्णांक in_ptr, u_पूर्णांक out_ptr)
अणु
	काष्ठा dataseg *ds;
	काष्ठा scatterlist *sg, *s;
	पूर्णांक i, n;

	अगर (scsi_bufflen(Cmnd)) अणु
		पूर्णांक sg_count;

		sg = scsi_sglist(Cmnd);
		sg_count = dma_map_sg(&qpti->op->dev, sg,
				      scsi_sg_count(Cmnd),
				      Cmnd->sc_data_direction);

		ds = cmd->dataseg;
		cmd->segment_cnt = sg_count;

		/* Fill in first four sg entries: */
		n = sg_count;
		अगर (n > 4)
			n = 4;
		क्रम_each_sg(sg, s, n, i) अणु
			ds[i].d_base = sg_dma_address(s);
			ds[i].d_count = sg_dma_len(s);
		पूर्ण
		sg_count -= 4;
		sg = s;
		जबतक (sg_count > 0) अणु
			काष्ठा Continuation_Entry *cont;

			++cmd->hdr.entry_cnt;
			cont = (काष्ठा Continuation_Entry *) &qpti->req_cpu[in_ptr];
			in_ptr = NEXT_REQ_PTR(in_ptr);
			अगर (in_ptr == out_ptr)
				वापस -1;

			cont->hdr.entry_type = ENTRY_CONTINUATION;
			cont->hdr.entry_cnt = 0;
			cont->hdr.sys_def_1 = 0;
			cont->hdr.flags = 0;
			cont->reserved = 0;
			ds = cont->dataseg;
			n = sg_count;
			अगर (n > 7)
				n = 7;
			क्रम_each_sg(sg, s, n, i) अणु
				ds[i].d_base = sg_dma_address(s);
				ds[i].d_count = sg_dma_len(s);
			पूर्ण
			sg_count -= n;
			sg = s;
		पूर्ण
	पूर्ण अन्यथा अणु
		cmd->dataseg[0].d_base = 0;
		cmd->dataseg[0].d_count = 0;
		cmd->segment_cnt = 1; /* Shouldn't this be 0? */
	पूर्ण

	/* Committed, record Scsi_Cmd so we can find it later. */
	cmd->handle = in_ptr;
	qpti->cmd_slots[in_ptr] = Cmnd;

	qpti->cmd_count[Cmnd->device->id]++;
	sbus_ग_लिखोw(in_ptr, qpti->qregs + MBOX4);
	qpti->req_in_ptr = in_ptr;

	वापस in_ptr;
पूर्ण

अटल अंतरभूत व्योम update_can_queue(काष्ठा Scsi_Host *host, u_पूर्णांक in_ptr, u_पूर्णांक out_ptr)
अणु
	/* Temporary workaround until bug is found and fixed (one bug has been found
	   alपढ़ोy, but fixing it makes things even worse) -jj */
	पूर्णांक num_मुक्त = QLOGICPTI_REQ_QUEUE_LEN - REQ_QUEUE_DEPTH(in_ptr, out_ptr) - 64;
	host->can_queue = scsi_host_busy(host) + num_मुक्त;
	host->sg_tablesize = QLOGICPTI_MAX_SG(num_मुक्त);
पूर्ण

अटल पूर्णांक qlogicpti_slave_configure(काष्ठा scsi_device *sdev)
अणु
	काष्ठा qlogicpti *qpti = shost_priv(sdev->host);
	पूर्णांक tgt = sdev->id;
	u_लघु param[6];

	/* tags handled in midlayer */
	/* enable sync mode? */
	अगर (sdev->sdtr) अणु
		qpti->dev_param[tgt].device_flags |= 0x10;
	पूर्ण अन्यथा अणु
		qpti->dev_param[tgt].synchronous_offset = 0;
		qpti->dev_param[tgt].synchronous_period = 0;
	पूर्ण
	/* are we wide capable? */
	अगर (sdev->wdtr)
		qpti->dev_param[tgt].device_flags |= 0x20;

	param[0] = MBOX_SET_TARGET_PARAMS;
	param[1] = (tgt << 8);
	param[2] = (qpti->dev_param[tgt].device_flags << 8);
	अगर (qpti->dev_param[tgt].device_flags & 0x10) अणु
		param[3] = (qpti->dev_param[tgt].synchronous_offset << 8) |
			qpti->dev_param[tgt].synchronous_period;
	पूर्ण अन्यथा अणु
		param[3] = 0;
	पूर्ण
	qlogicpti_mbox_command(qpti, param, 0);
	वापस 0;
पूर्ण

/*
 * The middle SCSI layer ensures that queuecommand never माला_लो invoked
 * concurrently with itself or the पूर्णांकerrupt handler (though the
 * पूर्णांकerrupt handler may call this routine as part of
 * request-completion handling).
 *
 * "This code must fly." -davem
 */
अटल पूर्णांक qlogicpti_queuecommand_lck(काष्ठा scsi_cmnd *Cmnd, व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा Scsi_Host *host = Cmnd->device->host;
	काष्ठा qlogicpti *qpti = (काष्ठा qlogicpti *) host->hostdata;
	काष्ठा Command_Entry *cmd;
	u_पूर्णांक out_ptr;
	पूर्णांक in_ptr;

	Cmnd->scsi_करोne = करोne;

	in_ptr = qpti->req_in_ptr;
	cmd = (काष्ठा Command_Entry *) &qpti->req_cpu[in_ptr];
	out_ptr = sbus_पढ़ोw(qpti->qregs + MBOX4);
	in_ptr = NEXT_REQ_PTR(in_ptr);
	अगर (in_ptr == out_ptr)
		जाओ toss_command;

	अगर (qpti->send_marker) अणु
		marker_frob(cmd);
		qpti->send_marker = 0;
		अगर (NEXT_REQ_PTR(in_ptr) == out_ptr) अणु
			sbus_ग_लिखोw(in_ptr, qpti->qregs + MBOX4);
			qpti->req_in_ptr = in_ptr;
			जाओ toss_command;
		पूर्ण
		cmd = (काष्ठा Command_Entry *) &qpti->req_cpu[in_ptr];
		in_ptr = NEXT_REQ_PTR(in_ptr);
	पूर्ण
	cmd_frob(cmd, Cmnd, qpti);
	अगर ((in_ptr = load_cmd(Cmnd, cmd, qpti, in_ptr, out_ptr)) == -1)
		जाओ toss_command;

	update_can_queue(host, in_ptr, out_ptr);

	वापस 0;

toss_command:
	prपूर्णांकk(KERN_EMERG "qlogicpti%d: request queue overflow\n",
	       qpti->qpti_id);

	/* Unक्रमtunately, unless you use the new EH code, which
	 * we करोn't, the midlayer will ignore the वापस value,
	 * which is insane.  We pick up the pieces like this.
	 */
	Cmnd->result = DID_BUS_BUSY;
	करोne(Cmnd);
	वापस 1;
पूर्ण

अटल DEF_SCSI_QCMD(qlogicpti_queuecommand)

अटल पूर्णांक qlogicpti_वापस_status(काष्ठा Status_Entry *sts, पूर्णांक id)
अणु
	पूर्णांक host_status = DID_ERROR;

	चयन (sts->completion_status) अणु
	      हाल CS_COMPLETE:
		host_status = DID_OK;
		अवरोध;
	      हाल CS_INCOMPLETE:
		अगर (!(sts->state_flags & SF_GOT_BUS))
			host_status = DID_NO_CONNECT;
		अन्यथा अगर (!(sts->state_flags & SF_GOT_TARGET))
			host_status = DID_BAD_TARGET;
		अन्यथा अगर (!(sts->state_flags & SF_SENT_CDB))
			host_status = DID_ERROR;
		अन्यथा अगर (!(sts->state_flags & SF_TRANSFERRED_DATA))
			host_status = DID_ERROR;
		अन्यथा अगर (!(sts->state_flags & SF_GOT_STATUS))
			host_status = DID_ERROR;
		अन्यथा अगर (!(sts->state_flags & SF_GOT_SENSE))
			host_status = DID_ERROR;
		अवरोध;
	      हाल CS_DMA_ERROR:
	      हाल CS_TRANSPORT_ERROR:
		host_status = DID_ERROR;
		अवरोध;
	      हाल CS_RESET_OCCURRED:
	      हाल CS_BUS_RESET:
		host_status = DID_RESET;
		अवरोध;
	      हाल CS_ABORTED:
		host_status = DID_ABORT;
		अवरोध;
	      हाल CS_TIMEOUT:
		host_status = DID_TIME_OUT;
		अवरोध;
	      हाल CS_DATA_OVERRUN:
	      हाल CS_COMMAND_OVERRUN:
	      हाल CS_STATUS_OVERRUN:
	      हाल CS_BAD_MESSAGE:
	      हाल CS_NO_MESSAGE_OUT:
	      हाल CS_EXT_ID_FAILED:
	      हाल CS_IDE_MSG_FAILED:
	      हाल CS_ABORT_MSG_FAILED:
	      हाल CS_NOP_MSG_FAILED:
	      हाल CS_PARITY_ERROR_MSG_FAILED:
	      हाल CS_DEVICE_RESET_MSG_FAILED:
	      हाल CS_ID_MSG_FAILED:
	      हाल CS_UNEXP_BUS_FREE:
		host_status = DID_ERROR;
		अवरोध;
	      हाल CS_DATA_UNDERRUN:
		host_status = DID_OK;
		अवरोध;
	      शेष:
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: unknown completion status 0x%04x\n",
		       id, sts->completion_status);
		host_status = DID_ERROR;
		अवरोध;
	पूर्ण

	वापस (sts->scsi_status & STATUS_MASK) | (host_status << 16);
पूर्ण

अटल काष्ठा scsi_cmnd *qlogicpti_पूर्णांकr_handler(काष्ठा qlogicpti *qpti)
अणु
	काष्ठा scsi_cmnd *Cmnd, *करोne_queue = शून्य;
	काष्ठा Status_Entry *sts;
	u_पूर्णांक in_ptr, out_ptr;

	अगर (!(sbus_पढ़ोw(qpti->qregs + SBUS_STAT) & SBUS_STAT_RINT))
		वापस शून्य;
		
	in_ptr = sbus_पढ़ोw(qpti->qregs + MBOX5);
	sbus_ग_लिखोw(HCCTRL_CRIRQ, qpti->qregs + HCCTRL);
	अगर (sbus_पढ़ोw(qpti->qregs + SBUS_SEMAPHORE) & SBUS_SEMAPHORE_LCK) अणु
		चयन (sbus_पढ़ोw(qpti->qregs + MBOX0)) अणु
		हाल ASYNC_SCSI_BUS_RESET:
		हाल EXECUTION_TIMEOUT_RESET:
			qpti->send_marker = 1;
			अवरोध;
		हाल INVALID_COMMAND:
		हाल HOST_INTERFACE_ERROR:
		हाल COMMAND_ERROR:
		हाल COMMAND_PARAM_ERROR:
			अवरोध;
		पूर्ण;
		sbus_ग_लिखोw(0, qpti->qregs + SBUS_SEMAPHORE);
	पूर्ण

	/* This looks like a network driver! */
	out_ptr = qpti->res_out_ptr;
	जबतक (out_ptr != in_ptr) अणु
		u_पूर्णांक cmd_slot;

		sts = (काष्ठा Status_Entry *) &qpti->res_cpu[out_ptr];
		out_ptr = NEXT_RES_PTR(out_ptr);

		/* We store an index in the handle, not the poपूर्णांकer in
		 * some क्रमm.  This aव्योमs problems due to the fact
		 * that the handle provided is only 32-bits. -DaveM
		 */
		cmd_slot = sts->handle;
		Cmnd = qpti->cmd_slots[cmd_slot];
		qpti->cmd_slots[cmd_slot] = शून्य;

		अगर (sts->completion_status == CS_RESET_OCCURRED ||
		    sts->completion_status == CS_ABORTED ||
		    (sts->status_flags & STF_BUS_RESET))
			qpti->send_marker = 1;

		अगर (sts->state_flags & SF_GOT_SENSE)
			स_नकल(Cmnd->sense_buffer, sts->req_sense_data,
			       SCSI_SENSE_BUFFERSIZE);

		अगर (sts->hdr.entry_type == ENTRY_STATUS)
			Cmnd->result =
			    qlogicpti_वापस_status(sts, qpti->qpti_id);
		अन्यथा
			Cmnd->result = DID_ERROR << 16;

		अगर (scsi_bufflen(Cmnd))
			dma_unmap_sg(&qpti->op->dev,
				     scsi_sglist(Cmnd), scsi_sg_count(Cmnd),
				     Cmnd->sc_data_direction);

		qpti->cmd_count[Cmnd->device->id]--;
		sbus_ग_लिखोw(out_ptr, qpti->qregs + MBOX5);
		Cmnd->host_scribble = (अचिन्हित अक्षर *) करोne_queue;
		करोne_queue = Cmnd;
	पूर्ण
	qpti->res_out_ptr = out_ptr;

	वापस करोne_queue;
पूर्ण

अटल irqवापस_t qpti_पूर्णांकr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा qlogicpti *qpti = dev_id;
	अचिन्हित दीर्घ flags;
	काष्ठा scsi_cmnd *dq;

	spin_lock_irqsave(qpti->qhost->host_lock, flags);
	dq = qlogicpti_पूर्णांकr_handler(qpti);

	अगर (dq != शून्य) अणु
		करो अणु
			काष्ठा scsi_cmnd *next;

			next = (काष्ठा scsi_cmnd *) dq->host_scribble;
			dq->scsi_करोne(dq);
			dq = next;
		पूर्ण जबतक (dq != शून्य);
	पूर्ण
	spin_unlock_irqrestore(qpti->qhost->host_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक qlogicpti_पात(काष्ठा scsi_cmnd *Cmnd)
अणु
	u_लघु param[6];
	काष्ठा Scsi_Host *host = Cmnd->device->host;
	काष्ठा qlogicpti *qpti = (काष्ठा qlogicpti *) host->hostdata;
	पूर्णांक वापस_status = SUCCESS;
	u32 cmd_cookie;
	पूर्णांक i;

	prपूर्णांकk(KERN_WARNING "qlogicpti%d: Aborting cmd for tgt[%d] lun[%d]\n",
	       qpti->qpti_id, (पूर्णांक)Cmnd->device->id, (पूर्णांक)Cmnd->device->lun);

	qlogicpti_disable_irqs(qpti);

	/* Find the 32-bit cookie we gave to the firmware क्रम
	 * this command.
	 */
	क्रम (i = 0; i < QLOGICPTI_REQ_QUEUE_LEN + 1; i++)
		अगर (qpti->cmd_slots[i] == Cmnd)
			अवरोध;
	cmd_cookie = i;

	param[0] = MBOX_ABORT;
	param[1] = (((u_लघु) Cmnd->device->id) << 8) | Cmnd->device->lun;
	param[2] = cmd_cookie >> 16;
	param[3] = cmd_cookie & 0xffff;
	अगर (qlogicpti_mbox_command(qpti, param, 0) ||
	    (param[0] != MBOX_COMMAND_COMPLETE)) अणु
		prपूर्णांकk(KERN_EMERG "qlogicpti%d: scsi abort failure: %x\n",
		       qpti->qpti_id, param[0]);
		वापस_status = FAILED;
	पूर्ण

	qlogicpti_enable_irqs(qpti);

	वापस वापस_status;
पूर्ण

अटल पूर्णांक qlogicpti_reset(काष्ठा scsi_cmnd *Cmnd)
अणु
	u_लघु param[6];
	काष्ठा Scsi_Host *host = Cmnd->device->host;
	काष्ठा qlogicpti *qpti = (काष्ठा qlogicpti *) host->hostdata;
	पूर्णांक वापस_status = SUCCESS;

	prपूर्णांकk(KERN_WARNING "qlogicpti%d: Resetting SCSI bus!\n",
	       qpti->qpti_id);

	qlogicpti_disable_irqs(qpti);

	param[0] = MBOX_BUS_RESET;
	param[1] = qpti->host_param.bus_reset_delay;
	अगर (qlogicpti_mbox_command(qpti, param, 0) ||
	   (param[0] != MBOX_COMMAND_COMPLETE)) अणु
		prपूर्णांकk(KERN_EMERG "qlogicisp%d: scsi bus reset failure: %x\n",
		       qpti->qpti_id, param[0]);
		वापस_status = FAILED;
	पूर्ण

	qlogicpti_enable_irqs(qpti);

	वापस वापस_status;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा qpti_ढाँचा = अणु
	.module			= THIS_MODULE,
	.name			= "qlogicpti",
	.info			= qlogicpti_info,
	.queuecommand		= qlogicpti_queuecommand,
	.slave_configure	= qlogicpti_slave_configure,
	.eh_पात_handler	= qlogicpti_पात,
	.eh_host_reset_handler	= qlogicpti_reset,
	.can_queue		= QLOGICPTI_REQ_QUEUE_LEN,
	.this_id		= 7,
	.sg_tablesize		= QLOGICPTI_MAX_SG(QLOGICPTI_REQ_QUEUE_LEN),
पूर्ण;

अटल स्थिर काष्ठा of_device_id qpti_match[];
अटल पूर्णांक qpti_sbus_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *dp = op->dev.of_node;
	काष्ठा Scsi_Host *host;
	काष्ठा qlogicpti *qpti;
	अटल पूर्णांक nqptis;
	स्थिर अक्षर *fcode;

	/* Someबार Antares cards come up not completely
	 * setup, and we get a report of a zero IRQ.
	 */
	अगर (op->archdata.irqs[0] == 0)
		वापस -ENODEV;

	host = scsi_host_alloc(&qpti_ढाँचा, माप(काष्ठा qlogicpti));
	अगर (!host)
		वापस -ENOMEM;

	qpti = shost_priv(host);

	host->max_id = MAX_TARGETS;
	qpti->qhost = host;
	qpti->op = op;
	qpti->qpti_id = nqptis;
	qpti->is_pti = !of_node_name_eq(op->dev.of_node, "QLGC,isp");

	अगर (qpti_map_regs(qpti) < 0)
		जाओ fail_unlink;

	अगर (qpti_रेजिस्टर_irq(qpti) < 0)
		जाओ fail_unmap_regs;

	qpti_get_scsi_id(qpti);
	qpti_get_bursts(qpti);
	qpti_get_घड़ी(qpti);

	/* Clear out scsi_cmnd array. */
	स_रखो(qpti->cmd_slots, 0, माप(qpti->cmd_slots));

	अगर (qpti_map_queues(qpti) < 0)
		जाओ fail_मुक्त_irq;

	/* Load the firmware. */
	अगर (qlogicpti_load_firmware(qpti))
		जाओ fail_unmap_queues;
	अगर (qpti->is_pti) अणु
		/* Check the PTI status reg. */
		अगर (qlogicpti_verअगरy_पंचांगon(qpti))
			जाओ fail_unmap_queues;
	पूर्ण

	/* Reset the ISP and init res/req queues. */
	अगर (qlogicpti_reset_hardware(host))
		जाओ fail_unmap_queues;

	prपूर्णांकk("(Firmware v%d.%d.%d)", qpti->fware_majrev,
	       qpti->fware_minrev, qpti->fware_micrev);

	fcode = of_get_property(dp, "isp-fcode", शून्य);
	अगर (fcode && fcode[0])
		prपूर्णांकk("(FCode %s)", fcode);
	अगर (of_find_property(dp, "differential", शून्य) != शून्य)
		qpti->dअगरferential = 1;
			
	prपूर्णांकk("\nqlogicpti%d: [%s Wide, using %s interface]\n",
		qpti->qpti_id,
		(qpti->ultra ? "Ultra" : "Fast"),
		(qpti->dअगरferential ? "differential" : "single ended"));

	अगर (scsi_add_host(host, &op->dev)) अणु
		prपूर्णांकk("qlogicpti%d: Failed scsi_add_host\n", qpti->qpti_id);
		जाओ fail_unmap_queues;
	पूर्ण

	dev_set_drvdata(&op->dev, qpti);

	qpti_chain_add(qpti);

	scsi_scan_host(host);
	nqptis++;

	वापस 0;

fail_unmap_queues:
#घोषणा QSIZE(entries)	(((entries) + 1) * QUEUE_ENTRY_LEN)
	dma_मुक्त_coherent(&op->dev,
			  QSIZE(RES_QUEUE_LEN),
			  qpti->res_cpu, qpti->res_dvma);
	dma_मुक्त_coherent(&op->dev,
			  QSIZE(QLOGICPTI_REQ_QUEUE_LEN),
			  qpti->req_cpu, qpti->req_dvma);
#अघोषित QSIZE

fail_मुक्त_irq:
	मुक्त_irq(qpti->irq, qpti);

fail_unmap_regs:
	of_iounmap(&op->resource[0], qpti->qregs,
		   resource_size(&op->resource[0]));
	अगर (qpti->is_pti)
		of_iounmap(&op->resource[0], qpti->sreg,
			   माप(अचिन्हित अक्षर));

fail_unlink:
	scsi_host_put(host);

	वापस -ENODEV;
पूर्ण

अटल पूर्णांक qpti_sbus_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा qlogicpti *qpti = dev_get_drvdata(&op->dev);

	qpti_chain_del(qpti);

	scsi_हटाओ_host(qpti->qhost);

	/* Shut up the card. */
	sbus_ग_लिखोw(0, qpti->qregs + SBUS_CTRL);

	/* Free IRQ handler and unmap Qlogic,ISP and PTI status regs. */
	मुक्त_irq(qpti->irq, qpti);

#घोषणा QSIZE(entries)	(((entries) + 1) * QUEUE_ENTRY_LEN)
	dma_मुक्त_coherent(&op->dev,
			  QSIZE(RES_QUEUE_LEN),
			  qpti->res_cpu, qpti->res_dvma);
	dma_मुक्त_coherent(&op->dev,
			  QSIZE(QLOGICPTI_REQ_QUEUE_LEN),
			  qpti->req_cpu, qpti->req_dvma);
#अघोषित QSIZE

	of_iounmap(&op->resource[0], qpti->qregs,
		   resource_size(&op->resource[0]));
	अगर (qpti->is_pti)
		of_iounmap(&op->resource[0], qpti->sreg, माप(अचिन्हित अक्षर));

	scsi_host_put(qpti->qhost);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id qpti_match[] = अणु
	अणु
		.name = "ptisp",
	पूर्ण,
	अणु
		.name = "PTI,ptisp",
	पूर्ण,
	अणु
		.name = "QLGC,isp",
	पूर्ण,
	अणु
		.name = "SUNW,isp",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, qpti_match);

अटल काष्ठा platक्रमm_driver qpti_sbus_driver = अणु
	.driver = अणु
		.name = "qpti",
		.of_match_table = qpti_match,
	पूर्ण,
	.probe		= qpti_sbus_probe,
	.हटाओ		= qpti_sbus_हटाओ,
पूर्ण;
module_platक्रमm_driver(qpti_sbus_driver);

MODULE_DESCRIPTION("QlogicISP SBUS driver");
MODULE_AUTHOR("David S. Miller (davem@davemloft.net)");
MODULE_LICENSE("GPL");
MODULE_VERSION("2.1");
MODULE_FIRMWARE("qlogic/isp1000.bin");
