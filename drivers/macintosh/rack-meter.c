<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * RackMac vu-meter driver
 *
 * (c) Copyright 2006 Benjamin Herrenschmidt, IBM Corp.
 *                    <benh@kernel.crashing.org>
 *
 * Support the CPU-meter LEDs of the Xserve G5
 *
 * TODO: Implement PWM to करो variable पूर्णांकensity and provide userland
 * पूर्णांकerface क्रम fun. Also, the CPU-meter could be made nicer by being
 * a bit less "immediate" but giving instead a more average load over
 * समय. Patches welcome :-)
 */
#अघोषित DEBUG

#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/pci.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/of_address.h>
#समावेश <linux/of_irq.h>

#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>
#समावेश <यंत्र/dbdma.h>
#समावेश <यंत्र/macपन.स>
#समावेश <यंत्र/keylargo.h>

/* Number of samples in a sample buffer */
#घोषणा SAMPLE_COUNT		256

/* CPU meter sampling rate in ms */
#घोषणा CPU_SAMPLING_RATE	250

काष्ठा rackmeter_dma अणु
	काष्ठा dbdma_cmd	cmd[4]			____cacheline_aligned;
	u32			mark			____cacheline_aligned;
	u32			buf1[SAMPLE_COUNT]	____cacheline_aligned;
	u32			buf2[SAMPLE_COUNT]	____cacheline_aligned;
पूर्ण ____cacheline_aligned;

काष्ठा rackmeter_cpu अणु
	काष्ठा delayed_work	snअगरfer;
	काष्ठा rackmeter	*rm;
	u64			prev_wall;
	u64			prev_idle;
	पूर्णांक			zero;
पूर्ण ____cacheline_aligned;

काष्ठा rackmeter अणु
	काष्ठा macio_dev		*mdev;
	अचिन्हित पूर्णांक			irq;
	काष्ठा device_node		*i2s;
	u8				*ubuf;
	काष्ठा dbdma_regs __iomem	*dma_regs;
	व्योम __iomem			*i2s_regs;
	dma_addr_t			dma_buf_p;
	काष्ठा rackmeter_dma		*dma_buf_v;
	पूर्णांक				stale_irq;
	काष्ठा rackmeter_cpu		cpu[2];
	पूर्णांक				छोड़ोd;
	काष्ठा mutex			sem;
पूर्ण;

/* To be set as a tunable */
अटल पूर्णांक rackmeter_ignore_nice;

/* This GPIO is whacked by the OS X driver when initializing */
#घोषणा RACKMETER_MAGIC_GPIO	0x78

/* This is copied from cpufreq_ondemand, maybe we should put it in
 * a common header somewhere
 */
अटल अंतरभूत u64 get_cpu_idle_समय(अचिन्हित पूर्णांक cpu)
अणु
	काष्ठा kernel_cpustat *kcpustat = &kcpustat_cpu(cpu);
	u64 retval;

	retval = kcpustat->cpustat[CPUTIME_IDLE] +
		 kcpustat->cpustat[CPUTIME_IOWAIT];

	अगर (rackmeter_ignore_nice)
		retval += kcpustat_field(kcpustat, CPUTIME_NICE, cpu);

	वापस retval;
पूर्ण

अटल व्योम rackmeter_setup_i2s(काष्ठा rackmeter *rm)
अणु
	काष्ठा macio_chip *macio = rm->mdev->bus->chip;

	/* First whack magic GPIO */
	pmac_call_feature(PMAC_FTR_WRITE_GPIO, शून्य, RACKMETER_MAGIC_GPIO, 5);


	/* Call feature code to enable the sound channel and the proper
	 * घड़ी sources
	 */
	pmac_call_feature(PMAC_FTR_SOUND_CHIP_ENABLE, rm->i2s, 0, 1);

	/* Power i2s and stop i2s घड़ी. We whack MacIO FCRs directly क्रम now.
	 * This is a bit racy, thus we should add new platक्रमm functions to
	 * handle that. snd-aoa needs that too
	 */
	MACIO_BIS(KEYLARGO_FCR1, KL1_I2S0_ENABLE);
	MACIO_BIC(KEYLARGO_FCR1, KL1_I2S0_CLK_ENABLE_BIT);
	(व्योम)MACIO_IN32(KEYLARGO_FCR1);
	udelay(10);

	/* Then setup i2s. For now, we use the same magic value that
	 * the OS X driver seems to use. We might want to play around
	 * with the घड़ी भागisors later
	 */
	out_le32(rm->i2s_regs + 0x10, 0x01fa0000);
	(व्योम)in_le32(rm->i2s_regs + 0x10);
	udelay(10);

	/* Fully restart i2s*/
	MACIO_BIS(KEYLARGO_FCR1, KL1_I2S0_CELL_ENABLE |
		  KL1_I2S0_CLK_ENABLE_BIT);
	(व्योम)MACIO_IN32(KEYLARGO_FCR1);
	udelay(10);
पूर्ण

अटल व्योम rackmeter_set_शेष_pattern(काष्ठा rackmeter *rm)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 16; i++) अणु
		अगर (i < 8)
			rm->ubuf[i] = (i & 1) * 255;
		अन्यथा
			rm->ubuf[i] = ((~i) & 1) * 255;
	पूर्ण
पूर्ण

अटल व्योम rackmeter_करो_छोड़ो(काष्ठा rackmeter *rm, पूर्णांक छोड़ो)
अणु
	काष्ठा rackmeter_dma *rdma = rm->dma_buf_v;

	pr_debug("rackmeter: %s\n", छोड़ो ? "paused" : "started");

	rm->छोड़ोd = छोड़ो;
	अगर (छोड़ो) अणु
		DBDMA_DO_STOP(rm->dma_regs);
		वापस;
	पूर्ण
	स_रखो(rdma->buf1, 0, माप(rdma->buf1));
	स_रखो(rdma->buf2, 0, माप(rdma->buf2));

	rm->dma_buf_v->mark = 0;

	mb();
	out_le32(&rm->dma_regs->cmdptr_hi, 0);
	out_le32(&rm->dma_regs->cmdptr, rm->dma_buf_p);
	out_le32(&rm->dma_regs->control, (RUN << 16) | RUN);
पूर्ण

अटल व्योम rackmeter_setup_dbdma(काष्ठा rackmeter *rm)
अणु
	काष्ठा rackmeter_dma *db = rm->dma_buf_v;
	काष्ठा dbdma_cmd *cmd = db->cmd;

	/* Make sure dbdma is reset */
	DBDMA_DO_RESET(rm->dma_regs);

	pr_debug("rackmeter: mark offset=0x%zx\n",
		 दुरत्व(काष्ठा rackmeter_dma, mark));
	pr_debug("rackmeter: buf1 offset=0x%zx\n",
		 दुरत्व(काष्ठा rackmeter_dma, buf1));
	pr_debug("rackmeter: buf2 offset=0x%zx\n",
		 दुरत्व(काष्ठा rackmeter_dma, buf2));

	/* Prepare 4 dbdma commands क्रम the 2 buffers */
	स_रखो(cmd, 0, 4 * माप(काष्ठा dbdma_cmd));
	cmd->req_count = cpu_to_le16(4);
	cmd->command = cpu_to_le16(STORE_WORD | INTR_ALWAYS | KEY_SYSTEM);
	cmd->phy_addr = cpu_to_le32(rm->dma_buf_p +
		दुरत्व(काष्ठा rackmeter_dma, mark));
	cmd->cmd_dep = cpu_to_le32(0x02000000);
	cmd++;

	cmd->req_count = cpu_to_le16(SAMPLE_COUNT * 4);
	cmd->command = cpu_to_le16(OUTPUT_MORE);
	cmd->phy_addr = cpu_to_le32(rm->dma_buf_p +
		दुरत्व(काष्ठा rackmeter_dma, buf1));
	cmd++;

	cmd->req_count = cpu_to_le16(4);
	cmd->command = cpu_to_le16(STORE_WORD | INTR_ALWAYS | KEY_SYSTEM);
	cmd->phy_addr = cpu_to_le32(rm->dma_buf_p +
		दुरत्व(काष्ठा rackmeter_dma, mark));
	cmd->cmd_dep = cpu_to_le32(0x01000000);
	cmd++;

	cmd->req_count = cpu_to_le16(SAMPLE_COUNT * 4);
	cmd->command = cpu_to_le16(OUTPUT_MORE | BR_ALWAYS);
	cmd->phy_addr = cpu_to_le32(rm->dma_buf_p +
		दुरत्व(काष्ठा rackmeter_dma, buf2));
	cmd->cmd_dep = cpu_to_le32(rm->dma_buf_p);

	rackmeter_करो_छोड़ो(rm, 0);
पूर्ण

अटल व्योम rackmeter_करो_समयr(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rackmeter_cpu *rcpu =
		container_of(work, काष्ठा rackmeter_cpu, snअगरfer.work);
	काष्ठा rackmeter *rm = rcpu->rm;
	अचिन्हित पूर्णांक cpu = smp_processor_id();
	u64 cur_nsecs, total_idle_nsecs;
	u64 total_nsecs, idle_nsecs;
	पूर्णांक i, offset, load, cumm, छोड़ो;

	cur_nsecs = jअगरfies64_to_nsecs(get_jअगरfies_64());
	total_nsecs = cur_nsecs - rcpu->prev_wall;
	rcpu->prev_wall = cur_nsecs;

	total_idle_nsecs = get_cpu_idle_समय(cpu);
	idle_nsecs = total_idle_nsecs - rcpu->prev_idle;
	idle_nsecs = min(idle_nsecs, total_nsecs);
	rcpu->prev_idle = total_idle_nsecs;

	/* We करो a very dumb calculation to update the LEDs क्रम now,
	 * we'll करो better once we have actual PWM implemented
	 */
	load = भाग64_u64(9 * (total_nsecs - idle_nsecs), total_nsecs);

	offset = cpu << 3;
	cumm = 0;
	क्रम (i = 0; i < 8; i++) अणु
		u8 ub = (load > i) ? 0xff : 0;
		rm->ubuf[i + offset] = ub;
		cumm |= ub;
	पूर्ण
	rcpu->zero = (cumm == 0);

	/* Now check अगर LEDs are all 0, we can stop DMA */
	छोड़ो = (rm->cpu[0].zero && rm->cpu[1].zero);
	अगर (छोड़ो != rm->छोड़ोd) अणु
		mutex_lock(&rm->sem);
		छोड़ो = (rm->cpu[0].zero && rm->cpu[1].zero);
		rackmeter_करो_छोड़ो(rm, छोड़ो);
		mutex_unlock(&rm->sem);
	पूर्ण
	schedule_delayed_work_on(cpu, &rcpu->snअगरfer,
				 msecs_to_jअगरfies(CPU_SAMPLING_RATE));
पूर्ण

अटल व्योम rackmeter_init_cpu_snअगरfer(काष्ठा rackmeter *rm)
अणु
	अचिन्हित पूर्णांक cpu;

	/* This driver works only with 1 or 2 CPUs numbered 0 and 1,
	 * but that's really all we have on Apple Xserve. It doesn't
	 * play very nice with CPU hotplug neither but we करोn't करो that
	 * on those machines yet
	 */

	rm->cpu[0].rm = rm;
	INIT_DELAYED_WORK(&rm->cpu[0].snअगरfer, rackmeter_करो_समयr);
	rm->cpu[1].rm = rm;
	INIT_DELAYED_WORK(&rm->cpu[1].snअगरfer, rackmeter_करो_समयr);

	क्रम_each_online_cpu(cpu) अणु
		काष्ठा rackmeter_cpu *rcpu;

		अगर (cpu > 1)
			जारी;
		rcpu = &rm->cpu[cpu];
		rcpu->prev_idle = get_cpu_idle_समय(cpu);
		rcpu->prev_wall = jअगरfies64_to_nsecs(get_jअगरfies_64());
		schedule_delayed_work_on(cpu, &rm->cpu[cpu].snअगरfer,
					 msecs_to_jअगरfies(CPU_SAMPLING_RATE));
	पूर्ण
पूर्ण

अटल व्योम rackmeter_stop_cpu_snअगरfer(काष्ठा rackmeter *rm)
अणु
	cancel_delayed_work_sync(&rm->cpu[0].snअगरfer);
	cancel_delayed_work_sync(&rm->cpu[1].snअगरfer);
पूर्ण

अटल पूर्णांक rackmeter_setup(काष्ठा rackmeter *rm)
अणु
	pr_debug("rackmeter: setting up i2s..\n");
	rackmeter_setup_i2s(rm);

	pr_debug("rackmeter: setting up default pattern..\n");
	rackmeter_set_शेष_pattern(rm);

	pr_debug("rackmeter: setting up dbdma..\n");
	rackmeter_setup_dbdma(rm);

	pr_debug("rackmeter: start CPU measurements..\n");
	rackmeter_init_cpu_snअगरfer(rm);

	prपूर्णांकk(KERN_INFO "RackMeter initialized\n");

	वापस 0;
पूर्ण

/*  XXX FIXME: No PWM yet, this is 0/1 */
अटल u32 rackmeter_calc_sample(काष्ठा rackmeter *rm, अचिन्हित पूर्णांक index)
अणु
	पूर्णांक led;
	u32 sample = 0;

	क्रम (led = 0; led < 16; led++) अणु
		sample >>= 1;
		sample |= ((rm->ubuf[led] >= 0x80) << 15);
	पूर्ण
	वापस (sample << 17) | (sample >> 15);
पूर्ण

अटल irqवापस_t rackmeter_irq(पूर्णांक irq, व्योम *arg)
अणु
	काष्ठा rackmeter *rm = arg;
	काष्ठा rackmeter_dma *db = rm->dma_buf_v;
	अचिन्हित पूर्णांक mark, i;
	u32 *buf;

	/* Flush PCI buffers with an MMIO पढ़ो. Maybe we could actually
	 * check the status one day ... in हाल things go wrong, though
	 * this never happened to me
	 */
	(व्योम)in_le32(&rm->dma_regs->status);

	/* Make sure the CPU माला_लो us in order */
	rmb();

	/* Read mark */
	mark = db->mark;
	अगर (mark != 1 && mark != 2) अणु
		prपूर्णांकk(KERN_WARNING "rackmeter: Incorrect DMA mark 0x%08x\n",
		       mark);
		/* We allow क्रम 3 errors like that (stale DBDMA irqs) */
		अगर (++rm->stale_irq > 3) अणु
			prपूर्णांकk(KERN_ERR "rackmeter: Too many errors,"
			       " stopping DMA\n");
			DBDMA_DO_RESET(rm->dma_regs);
		पूर्ण
		वापस IRQ_HANDLED;
	पूर्ण

	/* Next buffer we need to fill is mark value */
	buf = mark == 1 ? db->buf1 : db->buf2;

	/* Fill it now. This routine converts the 8 bits depth sample array
	 * पूर्णांकo the PWM biपंचांगap क्रम each LED.
	 */
	क्रम (i = 0; i < SAMPLE_COUNT; i++)
		buf[i] = rackmeter_calc_sample(rm, i);


	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक rackmeter_probe(काष्ठा macio_dev* mdev,
			   स्थिर काष्ठा of_device_id *match)
अणु
	काष्ठा device_node *i2s = शून्य, *np = शून्य;
	काष्ठा rackmeter *rm = शून्य;
	काष्ठा resource ri2s, rdma;
	पूर्णांक rc = -ENODEV;

	pr_debug("rackmeter_probe()\n");

	/* Get i2s-a node */
	क्रम_each_child_of_node(mdev->ofdev.dev.of_node, i2s)
		अगर (of_node_name_eq(i2s, "i2s-a"))
			अवरोध;

	अगर (i2s == शून्य) अणु
		pr_debug("  i2s-a child not found\n");
		जाओ bail;
	पूर्ण
	/* Get lightshow or भव sound */
	क्रम_each_child_of_node(i2s, np) अणु
	       अगर (of_node_name_eq(np, "lightshow"))
		       अवरोध;
	       अगर (of_node_name_eq(np, "sound") &&
		   of_get_property(np, "virtual", शून्य) != शून्य)
		       अवरोध;
	पूर्ण
	अगर (np == शून्य) अणु
		pr_debug("  lightshow or sound+virtual child not found\n");
		जाओ bail;
	पूर्ण

	/* Create and initialize our instance data */
	rm = kzalloc(माप(*rm), GFP_KERNEL);
	अगर (rm == शून्य) अणु
		prपूर्णांकk(KERN_ERR "rackmeter: failed to allocate memory !\n");
		rc = -ENOMEM;
		जाओ bail_release;
	पूर्ण
	rm->mdev = mdev;
	rm->i2s = i2s;
	mutex_init(&rm->sem);
	dev_set_drvdata(&mdev->ofdev.dev, rm);
	/* Check resources availability. We need at least resource 0 and 1 */
#अगर 0 /* Use that when i2s-a is finally an mdev per-se */
	अगर (macio_resource_count(mdev) < 2 || macio_irq_count(mdev) < 2) अणु
		prपूर्णांकk(KERN_ERR
		       "rackmeter: found match but lacks resources: %pOF"
		       " (%d resources, %d interrupts)\n",
		       mdev->ofdev.dev.of_node);
		rc = -ENXIO;
		जाओ bail_मुक्त;
	पूर्ण
	अगर (macio_request_resources(mdev, "rackmeter")) अणु
		prपूर्णांकk(KERN_ERR
		       "rackmeter: failed to request resources: %pOF\n",
		       mdev->ofdev.dev.of_node);
		rc = -EBUSY;
		जाओ bail_मुक्त;
	पूर्ण
	rm->irq = macio_irq(mdev, 1);
#अन्यथा
	rm->irq = irq_of_parse_and_map(i2s, 1);
	अगर (!rm->irq ||
	    of_address_to_resource(i2s, 0, &ri2s) ||
	    of_address_to_resource(i2s, 1, &rdma)) अणु
		prपूर्णांकk(KERN_ERR
		       "rackmeter: found match but lacks resources: %pOF",
		       mdev->ofdev.dev.of_node);
		rc = -ENXIO;
		जाओ bail_मुक्त;
	पूर्ण
#पूर्ण_अगर

	pr_debug("  i2s @0x%08x\n", (अचिन्हित पूर्णांक)ri2s.start);
	pr_debug("  dma @0x%08x\n", (अचिन्हित पूर्णांक)rdma.start);
	pr_debug("  irq %d\n", rm->irq);

	rm->ubuf = (u8 *)__get_मुक्त_page(GFP_KERNEL);
	अगर (rm->ubuf == शून्य) अणु
		prपूर्णांकk(KERN_ERR
		       "rackmeter: failed to allocate samples page !\n");
		rc = -ENOMEM;
		जाओ bail_release;
	पूर्ण

	rm->dma_buf_v = dma_alloc_coherent(&macio_get_pci_dev(mdev)->dev,
					   माप(काष्ठा rackmeter_dma),
					   &rm->dma_buf_p, GFP_KERNEL);
	अगर (rm->dma_buf_v == शून्य) अणु
		prपूर्णांकk(KERN_ERR
		       "rackmeter: failed to allocate dma buffer !\n");
		rc = -ENOMEM;
		जाओ bail_मुक्त_samples;
	पूर्ण
#अगर 0
	rm->i2s_regs = ioremap(macio_resource_start(mdev, 0), 0x1000);
#अन्यथा
	rm->i2s_regs = ioremap(ri2s.start, 0x1000);
#पूर्ण_अगर
	अगर (rm->i2s_regs == शून्य) अणु
		prपूर्णांकk(KERN_ERR
		       "rackmeter: failed to map i2s registers !\n");
		rc = -ENXIO;
		जाओ bail_मुक्त_dma;
	पूर्ण
#अगर 0
	rm->dma_regs = ioremap(macio_resource_start(mdev, 1), 0x100);
#अन्यथा
	rm->dma_regs = ioremap(rdma.start, 0x100);
#पूर्ण_अगर
	अगर (rm->dma_regs == शून्य) अणु
		prपूर्णांकk(KERN_ERR
		       "rackmeter: failed to map dma registers !\n");
		rc = -ENXIO;
		जाओ bail_unmap_i2s;
	पूर्ण

	rc = rackmeter_setup(rm);
	अगर (rc) अणु
		prपूर्णांकk(KERN_ERR
		       "rackmeter: failed to initialize !\n");
		rc = -ENXIO;
		जाओ bail_unmap_dma;
	पूर्ण

	rc = request_irq(rm->irq, rackmeter_irq, 0, "rackmeter", rm);
	अगर (rc != 0) अणु
		prपूर्णांकk(KERN_ERR
		       "rackmeter: failed to request interrupt !\n");
		जाओ bail_stop_dma;
	पूर्ण
	of_node_put(np);
	वापस 0;

 bail_stop_dma:
	DBDMA_DO_RESET(rm->dma_regs);
 bail_unmap_dma:
	iounmap(rm->dma_regs);
 bail_unmap_i2s:
	iounmap(rm->i2s_regs);
 bail_मुक्त_dma:
	dma_मुक्त_coherent(&macio_get_pci_dev(mdev)->dev,
			  माप(काष्ठा rackmeter_dma),
			  rm->dma_buf_v, rm->dma_buf_p);
 bail_मुक्त_samples:
	मुक्त_page((अचिन्हित दीर्घ)rm->ubuf);
 bail_release:
#अगर 0
	macio_release_resources(mdev);
#पूर्ण_अगर
 bail_मुक्त:
	kमुक्त(rm);
 bail:
	of_node_put(i2s);
	of_node_put(np);
	dev_set_drvdata(&mdev->ofdev.dev, शून्य);
	वापस rc;
पूर्ण

अटल पूर्णांक rackmeter_हटाओ(काष्ठा macio_dev* mdev)
अणु
	काष्ठा rackmeter *rm = dev_get_drvdata(&mdev->ofdev.dev);

	/* Stop CPU snअगरfer समयr & work queues */
	rackmeter_stop_cpu_snअगरfer(rm);

	/* Clear reference to निजी data */
	dev_set_drvdata(&mdev->ofdev.dev, शून्य);

	/* Stop/reset dbdma */
	DBDMA_DO_RESET(rm->dma_regs);

	/* Release the IRQ */
	मुक्त_irq(rm->irq, rm);

	/* Unmap रेजिस्टरs */
	iounmap(rm->dma_regs);
	iounmap(rm->i2s_regs);

	/* Free DMA */
	dma_मुक्त_coherent(&macio_get_pci_dev(mdev)->dev,
			  माप(काष्ठा rackmeter_dma),
			  rm->dma_buf_v, rm->dma_buf_p);

	/* Free samples */
	मुक्त_page((अचिन्हित दीर्घ)rm->ubuf);

#अगर 0
	/* Release resources */
	macio_release_resources(mdev);
#पूर्ण_अगर

	/* Get rid of me */
	kमुक्त(rm);

	वापस 0;
पूर्ण

अटल पूर्णांक rackmeter_shutकरोwn(काष्ठा macio_dev* mdev)
अणु
	काष्ठा rackmeter *rm = dev_get_drvdata(&mdev->ofdev.dev);

	अगर (rm == शून्य)
		वापस -ENODEV;

	/* Stop CPU snअगरfer समयr & work queues */
	rackmeter_stop_cpu_snअगरfer(rm);

	/* Stop/reset dbdma */
	DBDMA_DO_RESET(rm->dma_regs);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rackmeter_match[] = अणु
	अणु .name = "i2s" पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, rackmeter_match);

अटल काष्ठा macio_driver rackmeter_driver = अणु
	.driver = अणु
		.name = "rackmeter",
		.owner = THIS_MODULE,
		.of_match_table = rackmeter_match,
	पूर्ण,
	.probe = rackmeter_probe,
	.हटाओ = rackmeter_हटाओ,
	.shutकरोwn = rackmeter_shutकरोwn,
पूर्ण;


अटल पूर्णांक __init rackmeter_init(व्योम)
अणु
	pr_debug("rackmeter_init()\n");

	वापस macio_रेजिस्टर_driver(&rackmeter_driver);
पूर्ण

अटल व्योम __निकास rackmeter_निकास(व्योम)
अणु
	pr_debug("rackmeter_exit()\n");

	macio_unरेजिस्टर_driver(&rackmeter_driver);
पूर्ण

module_init(rackmeter_init);
module_निकास(rackmeter_निकास);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Benjamin Herrenschmidt <benh@kernel.crashing.org>");
MODULE_DESCRIPTION("RackMeter: Support vu-meter on XServe front panel");
