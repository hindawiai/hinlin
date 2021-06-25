<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PowerMac G5 SMU driver
 *
 * Copyright 2004 J. Mayer <l_indien@magic.fr>
 * Copyright 2005 Benjamin Herrenschmidt, IBM Corp.
 */

/*
 * TODO:
 *  - maybe add समयout to commands ?
 *  - blocking version of समय functions
 *  - polling version of i2c commands (including समयr that works with
 *    पूर्णांकerrupts off)
 *  - maybe aव्योम some data copies with i2c by directly using the smu cmd
 *    buffer and a lower level पूर्णांकernal पूर्णांकerface
 *  - understand SMU -> CPU events and implement reception of them via
 *    the userland पूर्णांकerface
 */

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/device.h>
#समावेश <linux/dmapool.h>
#समावेश <linux/memblock.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/rtc.h>
#समावेश <linux/completion.h>
#समावेश <linux/miscdevice.h>
#समावेश <linux/delay.h>
#समावेश <linux/poll.h>
#समावेश <linux/mutex.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/slab.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/smu.h>
#समावेश <यंत्र/sections.h>
#समावेश <linux/uaccess.h>

#घोषणा VERSION "0.7"
#घोषणा AUTHOR  "(c) 2005 Benjamin Herrenschmidt, IBM Corp."

#अघोषित DEBUG_SMU

#अगर_घोषित DEBUG_SMU
#घोषणा DPRINTK(fmt, args...) करो अणु prपूर्णांकk(KERN_DEBUG fmt , ##args); पूर्ण जबतक (0)
#अन्यथा
#घोषणा DPRINTK(fmt, args...) करो अणु पूर्ण जबतक (0)
#पूर्ण_अगर

/*
 * This is the command buffer passed to the SMU hardware
 */
#घोषणा SMU_MAX_DATA	254

काष्ठा smu_cmd_buf अणु
	u8 cmd;
	u8 length;
	u8 data[SMU_MAX_DATA];
पूर्ण;

काष्ठा smu_device अणु
	spinlock_t		lock;
	काष्ठा device_node	*of_node;
	काष्ठा platक्रमm_device	*of_dev;
	पूर्णांक			करोorbell;	/* करोorbell gpio */
	u32 __iomem		*db_buf;	/* करोorbell buffer */
	काष्ठा device_node	*db_node;
	अचिन्हित पूर्णांक		db_irq;
	पूर्णांक			msg;
	काष्ठा device_node	*msg_node;
	अचिन्हित पूर्णांक		msg_irq;
	काष्ठा smu_cmd_buf	*cmd_buf;	/* command buffer भव */
	u32			cmd_buf_असल;	/* command buffer असलolute */
	काष्ठा list_head	cmd_list;
	काष्ठा smu_cmd		*cmd_cur;	/* pending command */
	पूर्णांक			broken_nap;
	काष्ठा list_head	cmd_i2c_list;
	काष्ठा smu_i2c_cmd	*cmd_i2c_cur;	/* pending i2c command */
	काष्ठा समयr_list	i2c_समयr;
पूर्ण;

/*
 * I करोn't think there will ever be more than one SMU, so
 * क्रम now, just hard code that
 */
अटल DEFINE_MUTEX(smu_mutex);
अटल काष्ठा smu_device	*smu;
अटल DEFINE_MUTEX(smu_part_access);
अटल पूर्णांक smu_irq_inited;
अटल अचिन्हित दीर्घ smu_cmdbuf_असल;

अटल व्योम smu_i2c_retry(काष्ठा समयr_list *t);

/*
 * SMU driver low level stuff
 */

अटल व्योम smu_start_cmd(व्योम)
अणु
	अचिन्हित दीर्घ faddr, fend;
	काष्ठा smu_cmd *cmd;

	अगर (list_empty(&smu->cmd_list))
		वापस;

	/* Fetch first command in queue */
	cmd = list_entry(smu->cmd_list.next, काष्ठा smu_cmd, link);
	smu->cmd_cur = cmd;
	list_del(&cmd->link);

	DPRINTK("SMU: starting cmd %x, %d bytes data\n", cmd->cmd,
		cmd->data_len);
	DPRINTK("SMU: data buffer: %8ph\n", cmd->data_buf);

	/* Fill the SMU command buffer */
	smu->cmd_buf->cmd = cmd->cmd;
	smu->cmd_buf->length = cmd->data_len;
	स_नकल(smu->cmd_buf->data, cmd->data_buf, cmd->data_len);

	/* Flush command and data to RAM */
	faddr = (अचिन्हित दीर्घ)smu->cmd_buf;
	fend = faddr + smu->cmd_buf->length + 2;
	flush_dcache_range(faddr, fend);


	/* We also disable NAP mode क्रम the duration of the command
	 * on U3 based machines.
	 * This is slightly racy as it can be written back to 1 by a sysctl
	 * but that never happens in practice. There seem to be an issue with
	 * U3 based machines such as the iMac G5 where napping क्रम the
	 * whole duration of the command prevents the SMU from fetching it
	 * from memory. This might be related to the strange i2c based
	 * mechanism the SMU uses to access memory.
	 */
	अगर (smu->broken_nap)
		घातersave_nap = 0;

	/* This isn't exactly a DMA mapping here, I suspect
	 * the SMU is actually communicating with us via i2c to the
	 * northbridge or the CPU to access RAM.
	 */
	ग_लिखोl(smu->cmd_buf_असल, smu->db_buf);

	/* Ring the SMU करोorbell */
	pmac_करो_feature_call(PMAC_FTR_WRITE_GPIO, शून्य, smu->करोorbell, 4);
पूर्ण


अटल irqवापस_t smu_db_पूर्णांकr(पूर्णांक irq, व्योम *arg)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा smu_cmd *cmd;
	व्योम (*करोne)(काष्ठा smu_cmd *cmd, व्योम *misc) = शून्य;
	व्योम *misc = शून्य;
	u8 gpio;
	पूर्णांक rc = 0;

	/* SMU completed the command, well, we hope, let's make sure
	 * of it
	 */
	spin_lock_irqsave(&smu->lock, flags);

	gpio = pmac_करो_feature_call(PMAC_FTR_READ_GPIO, शून्य, smu->करोorbell);
	अगर ((gpio & 7) != 7) अणु
		spin_unlock_irqrestore(&smu->lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण

	cmd = smu->cmd_cur;
	smu->cmd_cur = शून्य;
	अगर (cmd == शून्य)
		जाओ bail;

	अगर (rc == 0) अणु
		अचिन्हित दीर्घ faddr;
		पूर्णांक reply_len;
		u8 ack;

		/* CPU might have brought back the cache line, so we need
		 * to flush again beक्रमe peeking at the SMU response. We
		 * flush the entire buffer क्रम now as we haven't पढ़ो the
		 * reply length (it's only 2 cache lines anyway)
		 */
		faddr = (अचिन्हित दीर्घ)smu->cmd_buf;
		flush_dcache_range(faddr, faddr + 256);

		/* Now check ack */
		ack = (~cmd->cmd) & 0xff;
		अगर (ack != smu->cmd_buf->cmd) अणु
			DPRINTK("SMU: incorrect ack, want %x got %x\n",
				ack, smu->cmd_buf->cmd);
			rc = -EIO;
		पूर्ण
		reply_len = rc == 0 ? smu->cmd_buf->length : 0;
		DPRINTK("SMU: reply len: %d\n", reply_len);
		अगर (reply_len > cmd->reply_len) अणु
			prपूर्णांकk(KERN_WARNING "SMU: reply buffer too small,"
			       "got %d bytes for a %d bytes buffer\n",
			       reply_len, cmd->reply_len);
			reply_len = cmd->reply_len;
		पूर्ण
		cmd->reply_len = reply_len;
		अगर (cmd->reply_buf && reply_len)
			स_नकल(cmd->reply_buf, smu->cmd_buf->data, reply_len);
	पूर्ण

	/* Now complete the command. Write status last in order as we lost
	 * ownership of the command काष्ठाure as soon as it's no दीर्घer -1
	 */
	करोne = cmd->करोne;
	misc = cmd->misc;
	mb();
	cmd->status = rc;

	/* Re-enable NAP mode */
	अगर (smu->broken_nap)
		घातersave_nap = 1;
 bail:
	/* Start next command अगर any */
	smu_start_cmd();
	spin_unlock_irqrestore(&smu->lock, flags);

	/* Call command completion handler अगर any */
	अगर (करोne)
		करोne(cmd, misc);

	/* It's an edge पूर्णांकerrupt, nothing to करो */
	वापस IRQ_HANDLED;
पूर्ण


अटल irqवापस_t smu_msg_पूर्णांकr(पूर्णांक irq, व्योम *arg)
अणु
	/* I करोn't quite know what to करो with this one, we seem to never
	 * receive it, so I suspect we have to arm it someway in the SMU
	 * to start getting events that way.
	 */

	prपूर्णांकk(KERN_INFO "SMU: message interrupt !\n");

	/* It's an edge पूर्णांकerrupt, nothing to करो */
	वापस IRQ_HANDLED;
पूर्ण


/*
 * Queued command management.
 *
 */

पूर्णांक smu_queue_cmd(काष्ठा smu_cmd *cmd)
अणु
	अचिन्हित दीर्घ flags;

	अगर (smu == शून्य)
		वापस -ENODEV;
	अगर (cmd->data_len > SMU_MAX_DATA ||
	    cmd->reply_len > SMU_MAX_DATA)
		वापस -EINVAL;

	cmd->status = 1;
	spin_lock_irqsave(&smu->lock, flags);
	list_add_tail(&cmd->link, &smu->cmd_list);
	अगर (smu->cmd_cur == शून्य)
		smu_start_cmd();
	spin_unlock_irqrestore(&smu->lock, flags);

	/* Workaround क्रम early calls when irq isn't available */
	अगर (!smu_irq_inited || !smu->db_irq)
		smu_spinरुको_cmd(cmd);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(smu_queue_cmd);


पूर्णांक smu_queue_simple(काष्ठा smu_simple_cmd *scmd, u8 command,
		     अचिन्हित पूर्णांक data_len,
		     व्योम (*करोne)(काष्ठा smu_cmd *cmd, व्योम *misc),
		     व्योम *misc, ...)
अणु
	काष्ठा smu_cmd *cmd = &scmd->cmd;
	बहु_सूची list;
	पूर्णांक i;

	अगर (data_len > माप(scmd->buffer))
		वापस -EINVAL;

	स_रखो(scmd, 0, माप(*scmd));
	cmd->cmd = command;
	cmd->data_len = data_len;
	cmd->data_buf = scmd->buffer;
	cmd->reply_len = माप(scmd->buffer);
	cmd->reply_buf = scmd->buffer;
	cmd->करोne = करोne;
	cmd->misc = misc;

	बहु_शुरू(list, misc);
	क्रम (i = 0; i < data_len; ++i)
		scmd->buffer[i] = (u8)बहु_तर्क(list, पूर्णांक);
	बहु_पूर्ण(list);

	वापस smu_queue_cmd(cmd);
पूर्ण
EXPORT_SYMBOL(smu_queue_simple);


व्योम smu_poll(व्योम)
अणु
	u8 gpio;

	अगर (smu == शून्य)
		वापस;

	gpio = pmac_करो_feature_call(PMAC_FTR_READ_GPIO, शून्य, smu->करोorbell);
	अगर ((gpio & 7) == 7)
		smu_db_पूर्णांकr(smu->db_irq, smu);
पूर्ण
EXPORT_SYMBOL(smu_poll);


व्योम smu_करोne_complete(काष्ठा smu_cmd *cmd, व्योम *misc)
अणु
	काष्ठा completion *comp = misc;

	complete(comp);
पूर्ण
EXPORT_SYMBOL(smu_करोne_complete);


व्योम smu_spinरुको_cmd(काष्ठा smu_cmd *cmd)
अणु
	जबतक(cmd->status == 1)
		smu_poll();
पूर्ण
EXPORT_SYMBOL(smu_spinरुको_cmd);


/* RTC low level commands */
अटल अंतरभूत पूर्णांक bcd2hex (पूर्णांक n)
अणु
	वापस (((n & 0xf0) >> 4) * 10) + (n & 0xf);
पूर्ण


अटल अंतरभूत पूर्णांक hex2bcd (पूर्णांक n)
अणु
	वापस ((n / 10) << 4) + (n % 10);
पूर्ण


अटल अंतरभूत व्योम smu_fill_set_rtc_cmd(काष्ठा smu_cmd_buf *cmd_buf,
					काष्ठा rtc_समय *समय)
अणु
	cmd_buf->cmd = 0x8e;
	cmd_buf->length = 8;
	cmd_buf->data[0] = 0x80;
	cmd_buf->data[1] = hex2bcd(समय->पंचांग_sec);
	cmd_buf->data[2] = hex2bcd(समय->पंचांग_min);
	cmd_buf->data[3] = hex2bcd(समय->पंचांग_hour);
	cmd_buf->data[4] = समय->पंचांग_wday;
	cmd_buf->data[5] = hex2bcd(समय->पंचांग_mday);
	cmd_buf->data[6] = hex2bcd(समय->पंचांग_mon) + 1;
	cmd_buf->data[7] = hex2bcd(समय->पंचांग_year - 100);
पूर्ण


पूर्णांक smu_get_rtc_समय(काष्ठा rtc_समय *समय, पूर्णांक spinरुको)
अणु
	काष्ठा smu_simple_cmd cmd;
	पूर्णांक rc;

	अगर (smu == शून्य)
		वापस -ENODEV;

	स_रखो(समय, 0, माप(काष्ठा rtc_समय));
	rc = smu_queue_simple(&cmd, SMU_CMD_RTC_COMMAND, 1, शून्य, शून्य,
			      SMU_CMD_RTC_GET_DATETIME);
	अगर (rc)
		वापस rc;
	smu_spinरुको_simple(&cmd);

	समय->पंचांग_sec = bcd2hex(cmd.buffer[0]);
	समय->पंचांग_min = bcd2hex(cmd.buffer[1]);
	समय->पंचांग_hour = bcd2hex(cmd.buffer[2]);
	समय->पंचांग_wday = bcd2hex(cmd.buffer[3]);
	समय->पंचांग_mday = bcd2hex(cmd.buffer[4]);
	समय->पंचांग_mon = bcd2hex(cmd.buffer[5]) - 1;
	समय->पंचांग_year = bcd2hex(cmd.buffer[6]) + 100;

	वापस 0;
पूर्ण


पूर्णांक smu_set_rtc_समय(काष्ठा rtc_समय *समय, पूर्णांक spinरुको)
अणु
	काष्ठा smu_simple_cmd cmd;
	पूर्णांक rc;

	अगर (smu == शून्य)
		वापस -ENODEV;

	rc = smu_queue_simple(&cmd, SMU_CMD_RTC_COMMAND, 8, शून्य, शून्य,
			      SMU_CMD_RTC_SET_DATETIME,
			      hex2bcd(समय->पंचांग_sec),
			      hex2bcd(समय->पंचांग_min),
			      hex2bcd(समय->पंचांग_hour),
			      समय->पंचांग_wday,
			      hex2bcd(समय->पंचांग_mday),
			      hex2bcd(समय->पंचांग_mon) + 1,
			      hex2bcd(समय->पंचांग_year - 100));
	अगर (rc)
		वापस rc;
	smu_spinरुको_simple(&cmd);

	वापस 0;
पूर्ण


व्योम smu_shutकरोwn(व्योम)
अणु
	काष्ठा smu_simple_cmd cmd;

	अगर (smu == शून्य)
		वापस;

	अगर (smu_queue_simple(&cmd, SMU_CMD_POWER_COMMAND, 9, शून्य, शून्य,
			     'S', 'H', 'U', 'T', 'D', 'O', 'W', 'N', 0))
		वापस;
	smu_spinरुको_simple(&cmd);
	क्रम (;;)
		;
पूर्ण


व्योम smu_restart(व्योम)
अणु
	काष्ठा smu_simple_cmd cmd;

	अगर (smu == शून्य)
		वापस;

	अगर (smu_queue_simple(&cmd, SMU_CMD_POWER_COMMAND, 8, शून्य, शून्य,
			     'R', 'E', 'S', 'T', 'A', 'R', 'T', 0))
		वापस;
	smu_spinरुको_simple(&cmd);
	क्रम (;;)
		;
पूर्ण


पूर्णांक smu_present(व्योम)
अणु
	वापस smu != शून्य;
पूर्ण
EXPORT_SYMBOL(smu_present);


पूर्णांक __init smu_init (व्योम)
अणु
	काष्ठा device_node *np;
	स्थिर u32 *data;
	पूर्णांक ret = 0;

        np = of_find_node_by_type(शून्य, "smu");
        अगर (np == शून्य)
		वापस -ENODEV;

	prपूर्णांकk(KERN_INFO "SMU: Driver %s %s\n", VERSION, AUTHOR);

	/*
	 * SMU based G5s need some memory below 2Gb. Thankfully this is
	 * called at a समय where memblock is still available.
	 */
	smu_cmdbuf_असल = memblock_phys_alloc_range(4096, 4096, 0, 0x80000000UL);
	अगर (smu_cmdbuf_असल == 0) अणु
		prपूर्णांकk(KERN_ERR "SMU: Command buffer allocation failed !\n");
		ret = -EINVAL;
		जाओ fail_np;
	पूर्ण

	smu = memblock_alloc(माप(काष्ठा smu_device), SMP_CACHE_BYTES);
	अगर (!smu)
		panic("%s: Failed to allocate %zu bytes\n", __func__,
		      माप(काष्ठा smu_device));

	spin_lock_init(&smu->lock);
	INIT_LIST_HEAD(&smu->cmd_list);
	INIT_LIST_HEAD(&smu->cmd_i2c_list);
	smu->of_node = np;
	smu->db_irq = 0;
	smu->msg_irq = 0;

	/* smu_cmdbuf_असल is in the low 2G of RAM, can be converted to a
	 * 32 bits value safely
	 */
	smu->cmd_buf_असल = (u32)smu_cmdbuf_असल;
	smu->cmd_buf = __va(smu_cmdbuf_असल);

	smu->db_node = of_find_node_by_name(शून्य, "smu-doorbell");
	अगर (smu->db_node == शून्य) अणु
		prपूर्णांकk(KERN_ERR "SMU: Can't find doorbell GPIO !\n");
		ret = -ENXIO;
		जाओ fail_booपंचांगem;
	पूर्ण
	data = of_get_property(smu->db_node, "reg", शून्य);
	अगर (data == शून्य) अणु
		prपूर्णांकk(KERN_ERR "SMU: Can't find doorbell GPIO address !\n");
		ret = -ENXIO;
		जाओ fail_db_node;
	पूर्ण

	/* Current setup has one करोorbell GPIO that करोes both करोorbell
	 * and ack. GPIOs are at 0x50, best would be to find that out
	 * in the device-tree though.
	 */
	smu->करोorbell = *data;
	अगर (smu->करोorbell < 0x50)
		smu->करोorbell += 0x50;

	/* Now look क्रम the smu-पूर्णांकerrupt GPIO */
	करो अणु
		smu->msg_node = of_find_node_by_name(शून्य, "smu-interrupt");
		अगर (smu->msg_node == शून्य)
			अवरोध;
		data = of_get_property(smu->msg_node, "reg", शून्य);
		अगर (data == शून्य) अणु
			of_node_put(smu->msg_node);
			smu->msg_node = शून्य;
			अवरोध;
		पूर्ण
		smu->msg = *data;
		अगर (smu->msg < 0x50)
			smu->msg += 0x50;
	पूर्ण जबतक(0);

	/* Doorbell buffer is currently hard-coded, I didn't find a proper
	 * device-tree entry giving the address. Best would probably to use
	 * an offset क्रम K2 base though, but let's करो it that way क्रम now.
	 */
	smu->db_buf = ioremap(0x8000860c, 0x1000);
	अगर (smu->db_buf == शून्य) अणु
		prपूर्णांकk(KERN_ERR "SMU: Can't map doorbell buffer pointer !\n");
		ret = -ENXIO;
		जाओ fail_msg_node;
	पूर्ण

	/* U3 has an issue with NAP mode when issuing SMU commands */
	smu->broken_nap = pmac_get_uninorth_variant() < 4;
	अगर (smu->broken_nap)
		prपूर्णांकk(KERN_INFO "SMU: using NAP mode workaround\n");

	sys_ctrler = SYS_CTRLER_SMU;
	वापस 0;

fail_msg_node:
	of_node_put(smu->msg_node);
fail_db_node:
	of_node_put(smu->db_node);
fail_booपंचांगem:
	memblock_मुक्त(__pa(smu), माप(काष्ठा smu_device));
	smu = शून्य;
fail_np:
	of_node_put(np);
	वापस ret;
पूर्ण


अटल पूर्णांक smu_late_init(व्योम)
अणु
	अगर (!smu)
		वापस 0;

	समयr_setup(&smu->i2c_समयr, smu_i2c_retry, 0);

	अगर (smu->db_node) अणु
		smu->db_irq = irq_of_parse_and_map(smu->db_node, 0);
		अगर (!smu->db_irq)
			prपूर्णांकk(KERN_ERR "smu: failed to map irq for node %pOF\n",
			       smu->db_node);
	पूर्ण
	अगर (smu->msg_node) अणु
		smu->msg_irq = irq_of_parse_and_map(smu->msg_node, 0);
		अगर (!smu->msg_irq)
			prपूर्णांकk(KERN_ERR "smu: failed to map irq for node %pOF\n",
			       smu->msg_node);
	पूर्ण

	/*
	 * Try to request the पूर्णांकerrupts
	 */

	अगर (smu->db_irq) अणु
		अगर (request_irq(smu->db_irq, smu_db_पूर्णांकr,
				IRQF_SHARED, "SMU doorbell", smu) < 0) अणु
			prपूर्णांकk(KERN_WARNING "SMU: can't "
			       "request interrupt %d\n",
			       smu->db_irq);
			smu->db_irq = 0;
		पूर्ण
	पूर्ण

	अगर (smu->msg_irq) अणु
		अगर (request_irq(smu->msg_irq, smu_msg_पूर्णांकr,
				IRQF_SHARED, "SMU message", smu) < 0) अणु
			prपूर्णांकk(KERN_WARNING "SMU: can't "
			       "request interrupt %d\n",
			       smu->msg_irq);
			smu->msg_irq = 0;
		पूर्ण
	पूर्ण

	smu_irq_inited = 1;
	वापस 0;
पूर्ण
/* This has to be beक्रमe arch_initcall as the low i2c stuff relies on the
 * above having been करोne beक्रमe we reach arch_initcalls
 */
core_initcall(smu_late_init);

/*
 * sysfs visibility
 */

अटल व्योम smu_expose_childs(काष्ठा work_काष्ठा *unused)
अणु
	काष्ठा device_node *np;

	क्रम_each_child_of_node(smu->of_node, np)
		अगर (of_device_is_compatible(np, "smu-sensors"))
			of_platक्रमm_device_create(np, "smu-sensors",
						  &smu->of_dev->dev);
पूर्ण

अटल DECLARE_WORK(smu_expose_childs_work, smu_expose_childs);

अटल पूर्णांक smu_platक्रमm_probe(काष्ठा platक्रमm_device* dev)
अणु
	अगर (!smu)
		वापस -ENODEV;
	smu->of_dev = dev;

	/*
	 * Ok, we are matched, now expose all i2c busses. We have to defer
	 * that unक्रमtunately or it would deadlock inside the device model
	 */
	schedule_work(&smu_expose_childs_work);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id smu_platक्रमm_match[] =
अणु
	अणु
		.type		= "smu",
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver smu_of_platक्रमm_driver =
अणु
	.driver = अणु
		.name = "smu",
		.of_match_table = smu_platक्रमm_match,
	पूर्ण,
	.probe		= smu_platक्रमm_probe,
पूर्ण;

अटल पूर्णांक __init smu_init_sysfs(व्योम)
अणु
	/*
	 * For now, we करोn't घातer manage machines with an SMU chip,
	 * I'm a bit too far from figuring out how that works with those
	 * new chipsets, but that will come back and bite us
	 */
	platक्रमm_driver_रेजिस्टर(&smu_of_platक्रमm_driver);
	वापस 0;
पूर्ण

device_initcall(smu_init_sysfs);

काष्ठा platक्रमm_device *smu_get_ofdev(व्योम)
अणु
	अगर (!smu)
		वापस शून्य;
	वापस smu->of_dev;
पूर्ण

EXPORT_SYMBOL_GPL(smu_get_ofdev);

/*
 * i2c पूर्णांकerface
 */

अटल व्योम smu_i2c_complete_command(काष्ठा smu_i2c_cmd *cmd, पूर्णांक fail)
अणु
	व्योम (*करोne)(काष्ठा smu_i2c_cmd *cmd, व्योम *misc) = cmd->करोne;
	व्योम *misc = cmd->misc;
	अचिन्हित दीर्घ flags;

	/* Check क्रम पढ़ो हाल */
	अगर (!fail && cmd->पढ़ो) अणु
		अगर (cmd->pdata[0] < 1)
			fail = 1;
		अन्यथा
			स_नकल(cmd->info.data, &cmd->pdata[1],
			       cmd->info.datalen);
	पूर्ण

	DPRINTK("SMU: completing, success: %d\n", !fail);

	/* Update status and mark no pending i2c command with lock
	 * held so nobody comes in जबतक we dequeue an eventual
	 * pending next i2c command
	 */
	spin_lock_irqsave(&smu->lock, flags);
	smu->cmd_i2c_cur = शून्य;
	wmb();
	cmd->status = fail ? -EIO : 0;

	/* Is there another i2c command रुकोing ? */
	अगर (!list_empty(&smu->cmd_i2c_list)) अणु
		काष्ठा smu_i2c_cmd *newcmd;

		/* Fetch it, new current, हटाओ from list */
		newcmd = list_entry(smu->cmd_i2c_list.next,
				    काष्ठा smu_i2c_cmd, link);
		smu->cmd_i2c_cur = newcmd;
		list_del(&cmd->link);

		/* Queue with low level smu */
		list_add_tail(&cmd->scmd.link, &smu->cmd_list);
		अगर (smu->cmd_cur == शून्य)
			smu_start_cmd();
	पूर्ण
	spin_unlock_irqrestore(&smu->lock, flags);

	/* Call command completion handler अगर any */
	अगर (करोne)
		करोne(cmd, misc);

पूर्ण


अटल व्योम smu_i2c_retry(काष्ठा समयr_list *unused)
अणु
	काष्ठा smu_i2c_cmd	*cmd = smu->cmd_i2c_cur;

	DPRINTK("SMU: i2c failure, requeuing...\n");

	/* requeue command simply by resetting reply_len */
	cmd->pdata[0] = 0xff;
	cmd->scmd.reply_len = माप(cmd->pdata);
	smu_queue_cmd(&cmd->scmd);
पूर्ण


अटल व्योम smu_i2c_low_completion(काष्ठा smu_cmd *scmd, व्योम *misc)
अणु
	काष्ठा smu_i2c_cmd	*cmd = misc;
	पूर्णांक			fail = 0;

	DPRINTK("SMU: i2c compl. stage=%d status=%x pdata[0]=%x rlen: %x\n",
		cmd->stage, scmd->status, cmd->pdata[0], scmd->reply_len);

	/* Check क्रम possible status */
	अगर (scmd->status < 0)
		fail = 1;
	अन्यथा अगर (cmd->पढ़ो) अणु
		अगर (cmd->stage == 0)
			fail = cmd->pdata[0] != 0;
		अन्यथा
			fail = cmd->pdata[0] >= 0x80;
	पूर्ण अन्यथा अणु
		fail = cmd->pdata[0] != 0;
	पूर्ण

	/* Handle failures by requeuing command, after 5ms पूर्णांकerval
	 */
	अगर (fail && --cmd->retries > 0) अणु
		DPRINTK("SMU: i2c failure, starting timer...\n");
		BUG_ON(cmd != smu->cmd_i2c_cur);
		अगर (!smu_irq_inited) अणु
			mdelay(5);
			smu_i2c_retry(शून्य);
			वापस;
		पूर्ण
		mod_समयr(&smu->i2c_समयr, jअगरfies + msecs_to_jअगरfies(5));
		वापस;
	पूर्ण

	/* If failure or stage 1, command is complete */
	अगर (fail || cmd->stage != 0) अणु
		smu_i2c_complete_command(cmd, fail);
		वापस;
	पूर्ण

	DPRINTK("SMU: going to stage 1\n");

	/* Ok, initial command complete, now poll status */
	scmd->reply_buf = cmd->pdata;
	scmd->reply_len = माप(cmd->pdata);
	scmd->data_buf = cmd->pdata;
	scmd->data_len = 1;
	cmd->pdata[0] = 0;
	cmd->stage = 1;
	cmd->retries = 20;
	smu_queue_cmd(scmd);
पूर्ण


पूर्णांक smu_queue_i2c(काष्ठा smu_i2c_cmd *cmd)
अणु
	अचिन्हित दीर्घ flags;

	अगर (smu == शून्य)
		वापस -ENODEV;

	/* Fill most fields of scmd */
	cmd->scmd.cmd = SMU_CMD_I2C_COMMAND;
	cmd->scmd.करोne = smu_i2c_low_completion;
	cmd->scmd.misc = cmd;
	cmd->scmd.reply_buf = cmd->pdata;
	cmd->scmd.reply_len = माप(cmd->pdata);
	cmd->scmd.data_buf = (u8 *)(अक्षर *)&cmd->info;
	cmd->scmd.status = 1;
	cmd->stage = 0;
	cmd->pdata[0] = 0xff;
	cmd->retries = 20;
	cmd->status = 1;

	/* Check transfer type, sanitize some "info" fields
	 * based on transfer type and करो more checking
	 */
	cmd->info.caddr = cmd->info.devaddr;
	cmd->पढ़ो = cmd->info.devaddr & 0x01;
	चयन(cmd->info.type) अणु
	हाल SMU_I2C_TRANSFER_SIMPLE:
		स_रखो(&cmd->info.sublen, 0, 4);
		अवरोध;
	हाल SMU_I2C_TRANSFER_COMBINED:
		cmd->info.devaddr &= 0xfe;
		fallthrough;
	हाल SMU_I2C_TRANSFER_STDSUB:
		अगर (cmd->info.sublen > 3)
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/* Finish setting up command based on transfer direction
	 */
	अगर (cmd->पढ़ो) अणु
		अगर (cmd->info.datalen > SMU_I2C_READ_MAX)
			वापस -EINVAL;
		स_रखो(cmd->info.data, 0xff, cmd->info.datalen);
		cmd->scmd.data_len = 9;
	पूर्ण अन्यथा अणु
		अगर (cmd->info.datalen > SMU_I2C_WRITE_MAX)
			वापस -EINVAL;
		cmd->scmd.data_len = 9 + cmd->info.datalen;
	पूर्ण

	DPRINTK("SMU: i2c enqueuing command\n");
	DPRINTK("SMU:   %s, len=%d bus=%x addr=%x sub0=%x type=%x\n",
		cmd->पढ़ो ? "read" : "write", cmd->info.datalen,
		cmd->info.bus, cmd->info.caddr,
		cmd->info.subaddr[0], cmd->info.type);


	/* Enqueue command in i2c list, and अगर empty, enqueue also in
	 * मुख्य command list
	 */
	spin_lock_irqsave(&smu->lock, flags);
	अगर (smu->cmd_i2c_cur == शून्य) अणु
		smu->cmd_i2c_cur = cmd;
		list_add_tail(&cmd->scmd.link, &smu->cmd_list);
		अगर (smu->cmd_cur == शून्य)
			smu_start_cmd();
	पूर्ण अन्यथा
		list_add_tail(&cmd->link, &smu->cmd_i2c_list);
	spin_unlock_irqrestore(&smu->lock, flags);

	वापस 0;
पूर्ण

/*
 * Handling of "partitions"
 */

अटल पूर्णांक smu_पढ़ो_datablock(u8 *dest, अचिन्हित पूर्णांक addr, अचिन्हित पूर्णांक len)
अणु
	DECLARE_COMPLETION_ONSTACK(comp);
	अचिन्हित पूर्णांक chunk;
	काष्ठा smu_cmd cmd;
	पूर्णांक rc;
	u8 params[8];

	/* We currently use a chunk size of 0xe. We could check the
	 * SMU firmware version and use bigger sizes though
	 */
	chunk = 0xe;

	जबतक (len) अणु
		अचिन्हित पूर्णांक clen = min(len, chunk);

		cmd.cmd = SMU_CMD_MISC_ee_COMMAND;
		cmd.data_len = 7;
		cmd.data_buf = params;
		cmd.reply_len = chunk;
		cmd.reply_buf = dest;
		cmd.करोne = smu_करोne_complete;
		cmd.misc = &comp;
		params[0] = SMU_CMD_MISC_ee_GET_DATABLOCK_REC;
		params[1] = 0x4;
		*((u32 *)&params[2]) = addr;
		params[6] = clen;

		rc = smu_queue_cmd(&cmd);
		अगर (rc)
			वापस rc;
		रुको_क्रम_completion(&comp);
		अगर (cmd.status != 0)
			वापस rc;
		अगर (cmd.reply_len != clen) अणु
			prपूर्णांकk(KERN_DEBUG "SMU: short read in "
			       "smu_read_datablock, got: %d, want: %d\n",
			       cmd.reply_len, clen);
			वापस -EIO;
		पूर्ण
		len -= clen;
		addr += clen;
		dest += clen;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा smu_sdbp_header *smu_create_sdb_partition(पूर्णांक id)
अणु
	DECLARE_COMPLETION_ONSTACK(comp);
	काष्ठा smu_simple_cmd cmd;
	अचिन्हित पूर्णांक addr, len, tlen;
	काष्ठा smu_sdbp_header *hdr;
	काष्ठा property *prop;

	/* First query the partition info */
	DPRINTK("SMU: Query partition infos ... (irq=%d)\n", smu->db_irq);
	smu_queue_simple(&cmd, SMU_CMD_PARTITION_COMMAND, 2,
			 smu_करोne_complete, &comp,
			 SMU_CMD_PARTITION_LATEST, id);
	रुको_क्रम_completion(&comp);
	DPRINTK("SMU: done, status: %d, reply_len: %d\n",
		cmd.cmd.status, cmd.cmd.reply_len);

	/* Partition करोesn't exist (or other error) */
	अगर (cmd.cmd.status != 0 || cmd.cmd.reply_len != 6)
		वापस शून्य;

	/* Fetch address and length from reply */
	addr = *((u16 *)cmd.buffer);
	len = cmd.buffer[3] << 2;
	/* Calucluate total length to allocate, including the 17 bytes
	 * क्रम "sdb-partition-XX" that we append at the end of the buffer
	 */
	tlen = माप(काष्ठा property) + len + 18;

	prop = kzalloc(tlen, GFP_KERNEL);
	अगर (prop == शून्य)
		वापस शून्य;
	hdr = (काष्ठा smu_sdbp_header *)(prop + 1);
	prop->name = ((अक्षर *)prop) + tlen - 18;
	प्र_लिखो(prop->name, "sdb-partition-%02x", id);
	prop->length = len;
	prop->value = hdr;
	prop->next = शून्य;

	/* Read the datablock */
	अगर (smu_पढ़ो_datablock((u8 *)hdr, addr, len)) अणु
		prपूर्णांकk(KERN_DEBUG "SMU: datablock read failed while reading "
		       "partition %02x !\n", id);
		जाओ failure;
	पूर्ण

	/* Got it, check a few things and create the property */
	अगर (hdr->id != id) अणु
		prपूर्णांकk(KERN_DEBUG "SMU: Reading partition %02x and got "
		       "%02x !\n", id, hdr->id);
		जाओ failure;
	पूर्ण
	अगर (of_add_property(smu->of_node, prop)) अणु
		prपूर्णांकk(KERN_DEBUG "SMU: Failed creating sdb-partition-%02x "
		       "property !\n", id);
		जाओ failure;
	पूर्ण

	वापस hdr;
 failure:
	kमुक्त(prop);
	वापस शून्य;
पूर्ण

/* Note: Only allowed to वापस error code in poपूर्णांकers (using ERR_PTR)
 * when पूर्णांकerruptible is 1
 */
अटल स्थिर काष्ठा smu_sdbp_header *__smu_get_sdb_partition(पूर्णांक id,
		अचिन्हित पूर्णांक *size, पूर्णांक पूर्णांकerruptible)
अणु
	अक्षर pname[32];
	स्थिर काष्ठा smu_sdbp_header *part;

	अगर (!smu)
		वापस शून्य;

	प्र_लिखो(pname, "sdb-partition-%02x", id);

	DPRINTK("smu_get_sdb_partition(%02x)\n", id);

	अगर (पूर्णांकerruptible) अणु
		पूर्णांक rc;
		rc = mutex_lock_पूर्णांकerruptible(&smu_part_access);
		अगर (rc)
			वापस ERR_PTR(rc);
	पूर्ण अन्यथा
		mutex_lock(&smu_part_access);

	part = of_get_property(smu->of_node, pname, size);
	अगर (part == शून्य) अणु
		DPRINTK("trying to extract from SMU ...\n");
		part = smu_create_sdb_partition(id);
		अगर (part != शून्य && size)
			*size = part->len << 2;
	पूर्ण
	mutex_unlock(&smu_part_access);
	वापस part;
पूर्ण

स्थिर काष्ठा smu_sdbp_header *smu_get_sdb_partition(पूर्णांक id, अचिन्हित पूर्णांक *size)
अणु
	वापस __smu_get_sdb_partition(id, size, 0);
पूर्ण
EXPORT_SYMBOL(smu_get_sdb_partition);


/*
 * Userland driver पूर्णांकerface
 */


अटल LIST_HEAD(smu_clist);
अटल DEFINE_SPINLOCK(smu_clist_lock);

क्रमागत smu_file_mode अणु
	smu_file_commands,
	smu_file_events,
	smu_file_closing
पूर्ण;

काष्ठा smu_निजी
अणु
	काष्ठा list_head	list;
	क्रमागत smu_file_mode	mode;
	पूर्णांक			busy;
	काष्ठा smu_cmd		cmd;
	spinlock_t		lock;
	रुको_queue_head_t	रुको;
	u8			buffer[SMU_MAX_DATA];
पूर्ण;


अटल पूर्णांक smu_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा smu_निजी *pp;
	अचिन्हित दीर्घ flags;

	pp = kzalloc(माप(काष्ठा smu_निजी), GFP_KERNEL);
	अगर (pp == 0)
		वापस -ENOMEM;
	spin_lock_init(&pp->lock);
	pp->mode = smu_file_commands;
	init_रुकोqueue_head(&pp->रुको);

	mutex_lock(&smu_mutex);
	spin_lock_irqsave(&smu_clist_lock, flags);
	list_add(&pp->list, &smu_clist);
	spin_unlock_irqrestore(&smu_clist_lock, flags);
	file->निजी_data = pp;
	mutex_unlock(&smu_mutex);

	वापस 0;
पूर्ण


अटल व्योम smu_user_cmd_करोne(काष्ठा smu_cmd *cmd, व्योम *misc)
अणु
	काष्ठा smu_निजी *pp = misc;

	wake_up_all(&pp->रुको);
पूर्ण


अटल sमाप_प्रकार smu_ग_लिखो(काष्ठा file *file, स्थिर अक्षर __user *buf,
			 माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा smu_निजी *pp = file->निजी_data;
	अचिन्हित दीर्घ flags;
	काष्ठा smu_user_cmd_hdr hdr;
	पूर्णांक rc = 0;

	अगर (pp->busy)
		वापस -EBUSY;
	अन्यथा अगर (copy_from_user(&hdr, buf, माप(hdr)))
		वापस -EFAULT;
	अन्यथा अगर (hdr.cmdtype == SMU_CMDTYPE_WANTS_EVENTS) अणु
		pp->mode = smu_file_events;
		वापस 0;
	पूर्ण अन्यथा अगर (hdr.cmdtype == SMU_CMDTYPE_GET_PARTITION) अणु
		स्थिर काष्ठा smu_sdbp_header *part;
		part = __smu_get_sdb_partition(hdr.cmd, शून्य, 1);
		अगर (part == शून्य)
			वापस -EINVAL;
		अन्यथा अगर (IS_ERR(part))
			वापस PTR_ERR(part);
		वापस 0;
	पूर्ण अन्यथा अगर (hdr.cmdtype != SMU_CMDTYPE_SMU)
		वापस -EINVAL;
	अन्यथा अगर (pp->mode != smu_file_commands)
		वापस -EBADFD;
	अन्यथा अगर (hdr.data_len > SMU_MAX_DATA)
		वापस -EINVAL;

	spin_lock_irqsave(&pp->lock, flags);
	अगर (pp->busy) अणु
		spin_unlock_irqrestore(&pp->lock, flags);
		वापस -EBUSY;
	पूर्ण
	pp->busy = 1;
	pp->cmd.status = 1;
	spin_unlock_irqrestore(&pp->lock, flags);

	अगर (copy_from_user(pp->buffer, buf + माप(hdr), hdr.data_len)) अणु
		pp->busy = 0;
		वापस -EFAULT;
	पूर्ण

	pp->cmd.cmd = hdr.cmd;
	pp->cmd.data_len = hdr.data_len;
	pp->cmd.reply_len = SMU_MAX_DATA;
	pp->cmd.data_buf = pp->buffer;
	pp->cmd.reply_buf = pp->buffer;
	pp->cmd.करोne = smu_user_cmd_करोne;
	pp->cmd.misc = pp;
	rc = smu_queue_cmd(&pp->cmd);
	अगर (rc < 0)
		वापस rc;
	वापस count;
पूर्ण


अटल sमाप_प्रकार smu_पढ़ो_command(काष्ठा file *file, काष्ठा smu_निजी *pp,
				अक्षर __user *buf, माप_प्रकार count)
अणु
	DECLARE_WAITQUEUE(रुको, current);
	काष्ठा smu_user_reply_hdr hdr;
	अचिन्हित दीर्घ flags;
	पूर्णांक size, rc = 0;

	अगर (!pp->busy)
		वापस 0;
	अगर (count < माप(काष्ठा smu_user_reply_hdr))
		वापस -EOVERFLOW;
	spin_lock_irqsave(&pp->lock, flags);
	अगर (pp->cmd.status == 1) अणु
		अगर (file->f_flags & O_NONBLOCK) अणु
			spin_unlock_irqrestore(&pp->lock, flags);
			वापस -EAGAIN;
		पूर्ण
		add_रुको_queue(&pp->रुको, &रुको);
		क्रम (;;) अणु
			set_current_state(TASK_INTERRUPTIBLE);
			rc = 0;
			अगर (pp->cmd.status != 1)
				अवरोध;
			rc = -ERESTARTSYS;
			अगर (संकेत_pending(current))
				अवरोध;
			spin_unlock_irqrestore(&pp->lock, flags);
			schedule();
			spin_lock_irqsave(&pp->lock, flags);
		पूर्ण
		set_current_state(TASK_RUNNING);
		हटाओ_रुको_queue(&pp->रुको, &रुको);
	पूर्ण
	spin_unlock_irqrestore(&pp->lock, flags);
	अगर (rc)
		वापस rc;
	अगर (pp->cmd.status != 0)
		pp->cmd.reply_len = 0;
	size = माप(hdr) + pp->cmd.reply_len;
	अगर (count < size)
		size = count;
	rc = size;
	hdr.status = pp->cmd.status;
	hdr.reply_len = pp->cmd.reply_len;
	अगर (copy_to_user(buf, &hdr, माप(hdr)))
		वापस -EFAULT;
	size -= माप(hdr);
	अगर (size && copy_to_user(buf + माप(hdr), pp->buffer, size))
		वापस -EFAULT;
	pp->busy = 0;

	वापस rc;
पूर्ण


अटल sमाप_प्रकार smu_पढ़ो_events(काष्ठा file *file, काष्ठा smu_निजी *pp,
			       अक्षर __user *buf, माप_प्रकार count)
अणु
	/* Not implemented */
	msleep_पूर्णांकerruptible(1000);
	वापस 0;
पूर्ण


अटल sमाप_प्रकार smu_पढ़ो(काष्ठा file *file, अक्षर __user *buf,
			माप_प्रकार count, loff_t *ppos)
अणु
	काष्ठा smu_निजी *pp = file->निजी_data;

	अगर (pp->mode == smu_file_commands)
		वापस smu_पढ़ो_command(file, pp, buf, count);
	अगर (pp->mode == smu_file_events)
		वापस smu_पढ़ो_events(file, pp, buf, count);

	वापस -EBADFD;
पूर्ण

अटल __poll_t smu_fpoll(काष्ठा file *file, poll_table *रुको)
अणु
	काष्ठा smu_निजी *pp = file->निजी_data;
	__poll_t mask = 0;
	अचिन्हित दीर्घ flags;

	अगर (pp == 0)
		वापस 0;

	अगर (pp->mode == smu_file_commands) अणु
		poll_रुको(file, &pp->रुको, रुको);

		spin_lock_irqsave(&pp->lock, flags);
		अगर (pp->busy && pp->cmd.status != 1)
			mask |= EPOLLIN;
		spin_unlock_irqrestore(&pp->lock, flags);
	पूर्ण
	अगर (pp->mode == smu_file_events) अणु
		/* Not yet implemented */
	पूर्ण
	वापस mask;
पूर्ण

अटल पूर्णांक smu_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा smu_निजी *pp = file->निजी_data;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक busy;

	अगर (pp == 0)
		वापस 0;

	file->निजी_data = शून्य;

	/* Mark file as closing to aव्योम races with new request */
	spin_lock_irqsave(&pp->lock, flags);
	pp->mode = smu_file_closing;
	busy = pp->busy;

	/* Wait क्रम any pending request to complete */
	अगर (busy && pp->cmd.status == 1) अणु
		DECLARE_WAITQUEUE(रुको, current);

		add_रुको_queue(&pp->रुको, &रुको);
		क्रम (;;) अणु
			set_current_state(TASK_UNINTERRUPTIBLE);
			अगर (pp->cmd.status != 1)
				अवरोध;
			spin_unlock_irqrestore(&pp->lock, flags);
			schedule();
			spin_lock_irqsave(&pp->lock, flags);
		पूर्ण
		set_current_state(TASK_RUNNING);
		हटाओ_रुको_queue(&pp->रुको, &रुको);
	पूर्ण
	spin_unlock_irqrestore(&pp->lock, flags);

	spin_lock_irqsave(&smu_clist_lock, flags);
	list_del(&pp->list);
	spin_unlock_irqrestore(&smu_clist_lock, flags);
	kमुक्त(pp);

	वापस 0;
पूर्ण


अटल स्थिर काष्ठा file_operations smu_device_fops = अणु
	.llseek		= no_llseek,
	.पढ़ो		= smu_पढ़ो,
	.ग_लिखो		= smu_ग_लिखो,
	.poll		= smu_fpoll,
	.खोलो		= smu_खोलो,
	.release	= smu_release,
पूर्ण;

अटल काष्ठा miscdevice pmu_device = अणु
	MISC_DYNAMIC_MINOR, "smu", &smu_device_fops
पूर्ण;

अटल पूर्णांक smu_device_init(व्योम)
अणु
	अगर (!smu)
		वापस -ENODEV;
	अगर (misc_रेजिस्टर(&pmu_device) < 0)
		prपूर्णांकk(KERN_ERR "via-pmu: cannot register misc device.\n");
	वापस 0;
पूर्ण
device_initcall(smu_device_init);
