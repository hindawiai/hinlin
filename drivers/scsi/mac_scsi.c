<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic Macपूर्णांकosh NCR5380 driver
 *
 * Copyright 1998, Michael Schmitz <mschmitz@lbl.gov>
 *
 * Copyright 2019 Finn Thain
 *
 * derived in part from:
 */
/*
 * Generic Generic NCR5380 driver
 *
 * Copyright 1995, Russell King
 */

#समावेश <linux/delay.h>
#समावेश <linux/types.h>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/hwtest.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/macपूर्णांकosh.h>
#समावेश <यंत्र/macपूर्णांकs.h>
#समावेश <यंत्र/setup.h>

#समावेश <scsi/scsi_host.h>

/* Definitions क्रम the core NCR5380 driver. */

#घोषणा NCR5380_implementation_fields   पूर्णांक pdma_residual

#घोषणा NCR5380_पढ़ो(reg)           in_8(hostdata->io + ((reg) << 4))
#घोषणा NCR5380_ग_लिखो(reg, value)   out_8(hostdata->io + ((reg) << 4), value)

#घोषणा NCR5380_dma_xfer_len            macscsi_dma_xfer_len
#घोषणा NCR5380_dma_recv_setup          macscsi_pपढ़ो
#घोषणा NCR5380_dma_send_setup          macscsi_pग_लिखो
#घोषणा NCR5380_dma_residual            macscsi_dma_residual

#घोषणा NCR5380_पूर्णांकr                    macscsi_पूर्णांकr
#घोषणा NCR5380_queue_command           macscsi_queue_command
#घोषणा NCR5380_पात                   macscsi_पात
#घोषणा NCR5380_host_reset              macscsi_host_reset
#घोषणा NCR5380_info                    macscsi_info

#समावेश "NCR5380.h"

अटल पूर्णांक setup_can_queue = -1;
module_param(setup_can_queue, पूर्णांक, 0);
अटल पूर्णांक setup_cmd_per_lun = -1;
module_param(setup_cmd_per_lun, पूर्णांक, 0);
अटल पूर्णांक setup_sg_tablesize = -1;
module_param(setup_sg_tablesize, पूर्णांक, 0);
अटल पूर्णांक setup_use_pdma = 512;
module_param(setup_use_pdma, पूर्णांक, 0);
अटल पूर्णांक setup_hostid = -1;
module_param(setup_hostid, पूर्णांक, 0);
अटल पूर्णांक setup_toshiba_delay = -1;
module_param(setup_toshiba_delay, पूर्णांक, 0);

#अगर_अघोषित MODULE
अटल पूर्णांक __init mac_scsi_setup(अक्षर *str)
अणु
	पूर्णांक पूर्णांकs[8];

	(व्योम)get_options(str, ARRAY_SIZE(पूर्णांकs), पूर्णांकs);

	अगर (पूर्णांकs[0] < 1) अणु
		pr_err("Usage: mac5380=<can_queue>[,<cmd_per_lun>[,<sg_tablesize>[,<hostid>[,<use_tags>[,<use_pdma>[,<toshiba_delay>]]]]]]\n");
		वापस 0;
	पूर्ण
	अगर (पूर्णांकs[0] >= 1)
		setup_can_queue = पूर्णांकs[1];
	अगर (पूर्णांकs[0] >= 2)
		setup_cmd_per_lun = पूर्णांकs[2];
	अगर (पूर्णांकs[0] >= 3)
		setup_sg_tablesize = पूर्णांकs[3];
	अगर (पूर्णांकs[0] >= 4)
		setup_hostid = पूर्णांकs[4];
	/* पूर्णांकs[5] (use_tagged_queuing) is ignored */
	अगर (पूर्णांकs[0] >= 6)
		setup_use_pdma = पूर्णांकs[6];
	अगर (पूर्णांकs[0] >= 7)
		setup_toshiba_delay = पूर्णांकs[7];
	वापस 1;
पूर्ण

__setup("mac5380=", mac_scsi_setup);
#पूर्ण_अगर /* !MODULE */

/*
 * According to "Inside Macintosh: Devices", Mac OS requires disk drivers to
 * specअगरy the number of bytes between the delays expected from a SCSI target.
 * This allows the operating प्रणाली to "prevent bus errors when a target fails
 * to deliver the next byte within the processor bus error समयout period."
 * Linux SCSI drivers lack knowledge of the timing behaviour of SCSI tarमाला_लो
 * so bus errors are unaव्योमable.
 *
 * If a MOVE.B inकाष्ठाion faults, we assume that zero bytes were transferred
 * and simply retry. That assumption probably depends on target behaviour but
 * seems to hold up okay. The NOP provides synchronization: without it the
 * fault can someबार occur after the program counter has moved past the
 * offending inकाष्ठाion. Post-increment addressing can't be used.
 */

#घोषणा MOVE_BYTE(opeअक्रमs) \
	यंत्र अस्थिर ( \
		"1:     moveb " opeअक्रमs "     \n" \
		"11:    nop                    \n" \
		"       addq #1,%0             \n" \
		"       subq #1,%1             \n" \
		"40:                           \n" \
		"                              \n" \
		".section .fixup,\"ax\"        \n" \
		".even                         \n" \
		"90:    movel #1, %2           \n" \
		"       jra 40b                \n" \
		".previous                     \n" \
		"                              \n" \
		".section __ex_table,\"a\"     \n" \
		".align  4                     \n" \
		".long   1b,90b                \n" \
		".long  11b,90b                \n" \
		".previous                     \n" \
		: "+a" (addr), "+r" (n), "+r" (result) : "a" (io))

/*
 * If a MOVE.W (or MOVE.L) inकाष्ठाion faults, it cannot be retried because
 * the residual byte count would be uncertain. In that situation the MOVE_WORD
 * macro clears n in the fixup section to पात the transfer.
 */

#घोषणा MOVE_WORD(opeअक्रमs) \
	यंत्र अस्थिर ( \
		"1:     movew " opeअक्रमs "     \n" \
		"11:    nop                    \n" \
		"       subq #2,%1             \n" \
		"40:                           \n" \
		"                              \n" \
		".section .fixup,\"ax\"        \n" \
		".even                         \n" \
		"90:    movel #0, %1           \n" \
		"       movel #2, %2           \n" \
		"       jra 40b                \n" \
		".previous                     \n" \
		"                              \n" \
		".section __ex_table,\"a\"     \n" \
		".align  4                     \n" \
		".long   1b,90b                \n" \
		".long  11b,90b                \n" \
		".previous                     \n" \
		: "+a" (addr), "+r" (n), "+r" (result) : "a" (io))

#घोषणा MOVE_16_WORDS(opeअक्रमs) \
	यंत्र अस्थिर ( \
		"1:     movew " opeअक्रमs "     \n" \
		"2:     movew " opeअक्रमs "     \n" \
		"3:     movew " opeअक्रमs "     \n" \
		"4:     movew " opeअक्रमs "     \n" \
		"5:     movew " opeअक्रमs "     \n" \
		"6:     movew " opeअक्रमs "     \n" \
		"7:     movew " opeअक्रमs "     \n" \
		"8:     movew " opeअक्रमs "     \n" \
		"9:     movew " opeअक्रमs "     \n" \
		"10:    movew " opeअक्रमs "     \n" \
		"11:    movew " opeअक्रमs "     \n" \
		"12:    movew " opeअक्रमs "     \n" \
		"13:    movew " opeअक्रमs "     \n" \
		"14:    movew " opeअक्रमs "     \n" \
		"15:    movew " opeअक्रमs "     \n" \
		"16:    movew " opeअक्रमs "     \n" \
		"17:    nop                    \n" \
		"       subl  #32,%1           \n" \
		"40:                           \n" \
		"                              \n" \
		".section .fixup,\"ax\"        \n" \
		".even                         \n" \
		"90:    movel #0, %1           \n" \
		"       movel #2, %2           \n" \
		"       jra 40b                \n" \
		".previous                     \n" \
		"                              \n" \
		".section __ex_table,\"a\"     \n" \
		".align  4                     \n" \
		".long   1b,90b                \n" \
		".long   2b,90b                \n" \
		".long   3b,90b                \n" \
		".long   4b,90b                \n" \
		".long   5b,90b                \n" \
		".long   6b,90b                \n" \
		".long   7b,90b                \n" \
		".long   8b,90b                \n" \
		".long   9b,90b                \n" \
		".long  10b,90b                \n" \
		".long  11b,90b                \n" \
		".long  12b,90b                \n" \
		".long  13b,90b                \n" \
		".long  14b,90b                \n" \
		".long  15b,90b                \n" \
		".long  16b,90b                \n" \
		".long  17b,90b                \n" \
		".previous                     \n" \
		: "+a" (addr), "+r" (n), "+r" (result) : "a" (io))

#घोषणा MAC_PDMA_DELAY		32

अटल अंतरभूत पूर्णांक mac_pdma_recv(व्योम __iomem *io, अचिन्हित अक्षर *start, पूर्णांक n)
अणु
	अचिन्हित अक्षर *addr = start;
	पूर्णांक result = 0;

	अगर (n >= 1) अणु
		MOVE_BYTE("%3@,%0@");
		अगर (result)
			जाओ out;
	पूर्ण
	अगर (n >= 1 && ((अचिन्हित दीर्घ)addr & 1)) अणु
		MOVE_BYTE("%3@,%0@");
		अगर (result)
			जाओ out;
	पूर्ण
	जबतक (n >= 32)
		MOVE_16_WORDS("%3@,%0@+");
	जबतक (n >= 2)
		MOVE_WORD("%3@,%0@+");
	अगर (result)
		वापस start - addr; /* Negated to indicate uncertain length */
	अगर (n == 1)
		MOVE_BYTE("%3@,%0@");
out:
	वापस addr - start;
पूर्ण

अटल अंतरभूत पूर्णांक mac_pdma_send(अचिन्हित अक्षर *start, व्योम __iomem *io, पूर्णांक n)
अणु
	अचिन्हित अक्षर *addr = start;
	पूर्णांक result = 0;

	अगर (n >= 1) अणु
		MOVE_BYTE("%0@,%3@");
		अगर (result)
			जाओ out;
	पूर्ण
	अगर (n >= 1 && ((अचिन्हित दीर्घ)addr & 1)) अणु
		MOVE_BYTE("%0@,%3@");
		अगर (result)
			जाओ out;
	पूर्ण
	जबतक (n >= 32)
		MOVE_16_WORDS("%0@+,%3@");
	जबतक (n >= 2)
		MOVE_WORD("%0@+,%3@");
	अगर (result)
		वापस start - addr; /* Negated to indicate uncertain length */
	अगर (n == 1)
		MOVE_BYTE("%0@,%3@");
out:
	वापस addr - start;
पूर्ण

/* The "SCSI DMA" chip on the IIfx implements this रेजिस्टर. */
#घोषणा CTRL_REG                0x8
#घोषणा CTRL_INTERRUPTS_ENABLE  BIT(1)
#घोषणा CTRL_HANDSHAKE_MODE     BIT(3)

अटल अंतरभूत व्योम ग_लिखो_ctrl_reg(काष्ठा NCR5380_hostdata *hostdata, u32 value)
अणु
	out_be32(hostdata->io + (CTRL_REG << 4), value);
पूर्ण

अटल अंतरभूत पूर्णांक macscsi_pपढ़ो(काष्ठा NCR5380_hostdata *hostdata,
                                अचिन्हित अक्षर *dst, पूर्णांक len)
अणु
	u8 __iomem *s = hostdata->pdma_io + (INPUT_DATA_REG << 4);
	अचिन्हित अक्षर *d = dst;
	पूर्णांक result = 0;

	hostdata->pdma_residual = len;

	जबतक (!NCR5380_poll_politely(hostdata, BUS_AND_STATUS_REG,
	                              BASR_DRQ | BASR_PHASE_MATCH,
	                              BASR_DRQ | BASR_PHASE_MATCH, 0)) अणु
		पूर्णांक bytes;

		अगर (macपूर्णांकosh_config->ident == MAC_MODEL_IIFX)
			ग_लिखो_ctrl_reg(hostdata, CTRL_HANDSHAKE_MODE |
			                         CTRL_INTERRUPTS_ENABLE);

		bytes = mac_pdma_recv(s, d, min(hostdata->pdma_residual, 512));

		अगर (bytes > 0) अणु
			d += bytes;
			hostdata->pdma_residual -= bytes;
		पूर्ण

		अगर (hostdata->pdma_residual == 0)
			जाओ out;

		अगर (NCR5380_poll_politely2(hostdata, STATUS_REG, SR_REQ, SR_REQ,
		                           BUS_AND_STATUS_REG, BASR_ACK,
		                           BASR_ACK, 0) < 0)
			scmd_prपूर्णांकk(KERN_DEBUG, hostdata->connected,
			            "%s: !REQ and !ACK\n", __func__);
		अगर (!(NCR5380_पढ़ो(BUS_AND_STATUS_REG) & BASR_PHASE_MATCH))
			जाओ out;

		अगर (bytes == 0)
			udelay(MAC_PDMA_DELAY);

		अगर (bytes >= 0)
			जारी;

		dsprपूर्णांकk(न_संशोधन_PSEUDO_DMA, hostdata->host,
		         "%s: bus error (%d/%d)\n", __func__, d - dst, len);
		NCR5380_dprपूर्णांक(न_संशोधन_PSEUDO_DMA, hostdata->host);
		result = -1;
		जाओ out;
	पूर्ण

	scmd_prपूर्णांकk(KERN_ERR, hostdata->connected,
	            "%s: phase mismatch or !DRQ\n", __func__);
	NCR5380_dprपूर्णांक(न_संशोधन_PSEUDO_DMA, hostdata->host);
	result = -1;
out:
	अगर (macपूर्णांकosh_config->ident == MAC_MODEL_IIFX)
		ग_लिखो_ctrl_reg(hostdata, CTRL_INTERRUPTS_ENABLE);
	वापस result;
पूर्ण

अटल अंतरभूत पूर्णांक macscsi_pग_लिखो(काष्ठा NCR5380_hostdata *hostdata,
                                 अचिन्हित अक्षर *src, पूर्णांक len)
अणु
	अचिन्हित अक्षर *s = src;
	u8 __iomem *d = hostdata->pdma_io + (OUTPUT_DATA_REG << 4);
	पूर्णांक result = 0;

	hostdata->pdma_residual = len;

	जबतक (!NCR5380_poll_politely(hostdata, BUS_AND_STATUS_REG,
	                              BASR_DRQ | BASR_PHASE_MATCH,
	                              BASR_DRQ | BASR_PHASE_MATCH, 0)) अणु
		पूर्णांक bytes;

		अगर (macपूर्णांकosh_config->ident == MAC_MODEL_IIFX)
			ग_लिखो_ctrl_reg(hostdata, CTRL_HANDSHAKE_MODE |
			                         CTRL_INTERRUPTS_ENABLE);

		bytes = mac_pdma_send(s, d, min(hostdata->pdma_residual, 512));

		अगर (bytes > 0) अणु
			s += bytes;
			hostdata->pdma_residual -= bytes;
		पूर्ण

		अगर (hostdata->pdma_residual == 0) अणु
			अगर (NCR5380_poll_politely(hostdata, TARGET_COMMAND_REG,
			                          TCR_LAST_BYTE_SENT,
			                          TCR_LAST_BYTE_SENT,
			                          0) < 0) अणु
				scmd_prपूर्णांकk(KERN_ERR, hostdata->connected,
				            "%s: Last Byte Sent timeout\n", __func__);
				result = -1;
			पूर्ण
			जाओ out;
		पूर्ण

		अगर (NCR5380_poll_politely2(hostdata, STATUS_REG, SR_REQ, SR_REQ,
		                           BUS_AND_STATUS_REG, BASR_ACK,
		                           BASR_ACK, 0) < 0)
			scmd_prपूर्णांकk(KERN_DEBUG, hostdata->connected,
			            "%s: !REQ and !ACK\n", __func__);
		अगर (!(NCR5380_पढ़ो(BUS_AND_STATUS_REG) & BASR_PHASE_MATCH))
			जाओ out;

		अगर (bytes == 0)
			udelay(MAC_PDMA_DELAY);

		अगर (bytes >= 0)
			जारी;

		dsprपूर्णांकk(न_संशोधन_PSEUDO_DMA, hostdata->host,
		         "%s: bus error (%d/%d)\n", __func__, s - src, len);
		NCR5380_dprपूर्णांक(न_संशोधन_PSEUDO_DMA, hostdata->host);
		result = -1;
		जाओ out;
	पूर्ण

	scmd_prपूर्णांकk(KERN_ERR, hostdata->connected,
	            "%s: phase mismatch or !DRQ\n", __func__);
	NCR5380_dprपूर्णांक(न_संशोधन_PSEUDO_DMA, hostdata->host);
	result = -1;
out:
	अगर (macपूर्णांकosh_config->ident == MAC_MODEL_IIFX)
		ग_लिखो_ctrl_reg(hostdata, CTRL_INTERRUPTS_ENABLE);
	वापस result;
पूर्ण

अटल पूर्णांक macscsi_dma_xfer_len(काष्ठा NCR5380_hostdata *hostdata,
                                काष्ठा scsi_cmnd *cmd)
अणु
	अगर (hostdata->flags & FLAG_NO_PSEUDO_DMA ||
	    cmd->SCp.this_residual < setup_use_pdma)
		वापस 0;

	वापस cmd->SCp.this_residual;
पूर्ण

अटल पूर्णांक macscsi_dma_residual(काष्ठा NCR5380_hostdata *hostdata)
अणु
	वापस hostdata->pdma_residual;
पूर्ण

#समावेश "NCR5380.c"

#घोषणा DRV_MODULE_NAME         "mac_scsi"
#घोषणा PFX                     DRV_MODULE_NAME ": "

अटल काष्ठा scsi_host_ढाँचा mac_scsi_ढाँचा = अणु
	.module			= THIS_MODULE,
	.proc_name		= DRV_MODULE_NAME,
	.name			= "Macintosh NCR5380 SCSI",
	.info			= macscsi_info,
	.queuecommand		= macscsi_queue_command,
	.eh_पात_handler	= macscsi_पात,
	.eh_host_reset_handler	= macscsi_host_reset,
	.can_queue		= 16,
	.this_id		= 7,
	.sg_tablesize		= 1,
	.cmd_per_lun		= 2,
	.dma_boundary		= PAGE_SIZE - 1,
	.cmd_size		= NCR5380_CMD_SIZE,
	.max_sectors		= 128,
पूर्ण;

अटल पूर्णांक __init mac_scsi_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा Scsi_Host *instance;
	काष्ठा NCR5380_hostdata *hostdata;
	पूर्णांक error;
	पूर्णांक host_flags = 0;
	काष्ठा resource *irq, *pio_mem, *pdma_mem = शून्य;

	pio_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!pio_mem)
		वापस -ENODEV;

	pdma_mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 1);

	irq = platक्रमm_get_resource(pdev, IORESOURCE_IRQ, 0);

	अगर (!hwreg_present((अचिन्हित अक्षर *)pio_mem->start +
	                   (STATUS_REG << 4))) अणु
		pr_info(PFX "no device detected at %pap\n", &pio_mem->start);
		वापस -ENODEV;
	पूर्ण

	अगर (setup_can_queue > 0)
		mac_scsi_ढाँचा.can_queue = setup_can_queue;
	अगर (setup_cmd_per_lun > 0)
		mac_scsi_ढाँचा.cmd_per_lun = setup_cmd_per_lun;
	अगर (setup_sg_tablesize > 0)
		mac_scsi_ढाँचा.sg_tablesize = setup_sg_tablesize;
	अगर (setup_hostid >= 0)
		mac_scsi_ढाँचा.this_id = setup_hostid & 7;

	instance = scsi_host_alloc(&mac_scsi_ढाँचा,
	                           माप(काष्ठा NCR5380_hostdata));
	अगर (!instance)
		वापस -ENOMEM;

	अगर (irq)
		instance->irq = irq->start;
	अन्यथा
		instance->irq = NO_IRQ;

	hostdata = shost_priv(instance);
	hostdata->base = pio_mem->start;
	hostdata->io = (u8 __iomem *)pio_mem->start;

	अगर (pdma_mem && setup_use_pdma)
		hostdata->pdma_io = (u8 __iomem *)pdma_mem->start;
	अन्यथा
		host_flags |= FLAG_NO_PSEUDO_DMA;

	host_flags |= setup_toshiba_delay > 0 ? FLAG_TOSHIBA_DELAY : 0;

	error = NCR5380_init(instance, host_flags | FLAG_LATE_DMA_SETUP);
	अगर (error)
		जाओ fail_init;

	अगर (instance->irq != NO_IRQ) अणु
		error = request_irq(instance->irq, macscsi_पूर्णांकr, IRQF_SHARED,
		                    "NCR5380", instance);
		अगर (error)
			जाओ fail_irq;
	पूर्ण

	NCR5380_maybe_reset_bus(instance);

	error = scsi_add_host(instance, शून्य);
	अगर (error)
		जाओ fail_host;

	platक्रमm_set_drvdata(pdev, instance);

	scsi_scan_host(instance);
	वापस 0;

fail_host:
	अगर (instance->irq != NO_IRQ)
		मुक्त_irq(instance->irq, instance);
fail_irq:
	NCR5380_निकास(instance);
fail_init:
	scsi_host_put(instance);
	वापस error;
पूर्ण

अटल पूर्णांक __निकास mac_scsi_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा Scsi_Host *instance = platक्रमm_get_drvdata(pdev);

	scsi_हटाओ_host(instance);
	अगर (instance->irq != NO_IRQ)
		मुक्त_irq(instance->irq, instance);
	NCR5380_निकास(instance);
	scsi_host_put(instance);
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver mac_scsi_driver = अणु
	.हटाओ = __निकास_p(mac_scsi_हटाओ),
	.driver = अणु
		.name	= DRV_MODULE_NAME,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver_probe(mac_scsi_driver, mac_scsi_probe);

MODULE_ALIAS("platform:" DRV_MODULE_NAME);
MODULE_LICENSE("GPL");
