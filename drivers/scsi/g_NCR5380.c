<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Generic Generic NCR5380 driver
 *
 * Copyright 1993, Drew Eckhardt
 * Visionary Computing
 * (Unix and Linux consulting and custom programming)
 * drew@coloraकरो.edu
 * +1 (303) 440-4894
 *
 * NCR53C400 extensions (c) 1994,1995,1996, Kevin Lentin
 * K.Lentin@cs.monash.edu.au
 *
 * NCR53C400A extensions (c) 1996, Ingmar Baumgart
 * ingmar@gonzo.schwaben.de
 *
 * DTC3181E extensions (c) 1997, Ronald van Cuijlenborg
 * ronald.van.cuijlenborg@tip.nl or nutty@dds.nl
 *
 * Added ISAPNP support क्रम DTC436 adapters,
 * Thomas Sailer, sailer@अगरe.ee.ethz.ch
 *
 * See Documentation/scsi/g_NCR5380.rst क्रम more info.
 */

#समावेश <यंत्र/पन.स>
#समावेश <linux/blkdev.h>
#समावेश <linux/module.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/isa.h>
#समावेश <linux/pnp.h>
#समावेश <linux/पूर्णांकerrupt.h>

/* Definitions क्रम the core NCR5380 driver. */

#घोषणा NCR5380_पढ़ो(reg) \
	ioपढ़ो8(hostdata->io + hostdata->offset + (reg))
#घोषणा NCR5380_ग_लिखो(reg, value) \
	ioग_लिखो8(value, hostdata->io + hostdata->offset + (reg))

#घोषणा NCR5380_implementation_fields \
	पूर्णांक offset; \
	पूर्णांक c400_ctl_status; \
	पूर्णांक c400_blk_cnt; \
	पूर्णांक c400_host_buf; \
	पूर्णांक io_width; \
	पूर्णांक pdma_residual; \
	पूर्णांक board

#घोषणा NCR5380_dma_xfer_len            generic_NCR5380_dma_xfer_len
#घोषणा NCR5380_dma_recv_setup          generic_NCR5380_precv
#घोषणा NCR5380_dma_send_setup          generic_NCR5380_psend
#घोषणा NCR5380_dma_residual            generic_NCR5380_dma_residual

#घोषणा NCR5380_पूर्णांकr                    generic_NCR5380_पूर्णांकr
#घोषणा NCR5380_queue_command           generic_NCR5380_queue_command
#घोषणा NCR5380_पात                   generic_NCR5380_पात
#घोषणा NCR5380_host_reset              generic_NCR5380_host_reset
#घोषणा NCR5380_info                    generic_NCR5380_info

#घोषणा NCR5380_io_delay(x)             udelay(x)

#समावेश "NCR5380.h"

#घोषणा DRV_MODULE_NAME "g_NCR5380"

#घोषणा NCR53C400_mem_base 0x3880
#घोषणा NCR53C400_host_buffer 0x3900
#घोषणा NCR53C400_region_size 0x3a00

#घोषणा BOARD_NCR5380 0
#घोषणा BOARD_NCR53C400 1
#घोषणा BOARD_NCR53C400A 2
#घोषणा BOARD_DTC3181E 3
#घोषणा BOARD_HP_C2502 4

#घोषणा IRQ_AUTO 254

#घोषणा MAX_CARDS 8
#घोषणा DMA_MAX_SIZE 32768

/* old-style parameters क्रम compatibility */
अटल पूर्णांक ncr_irq = -1;
अटल पूर्णांक ncr_addr;
अटल पूर्णांक ncr_5380;
अटल पूर्णांक ncr_53c400;
अटल पूर्णांक ncr_53c400a;
अटल पूर्णांक dtc_3181e;
अटल पूर्णांक hp_c2502;
module_param_hw(ncr_irq, पूर्णांक, irq, 0);
module_param_hw(ncr_addr, पूर्णांक, ioport, 0);
module_param(ncr_5380, पूर्णांक, 0);
module_param(ncr_53c400, पूर्णांक, 0);
module_param(ncr_53c400a, पूर्णांक, 0);
module_param(dtc_3181e, पूर्णांक, 0);
module_param(hp_c2502, पूर्णांक, 0);

अटल पूर्णांक irq[] = अणु -1, -1, -1, -1, -1, -1, -1, -1 पूर्ण;
module_param_hw_array(irq, पूर्णांक, irq, शून्य, 0);
MODULE_PARM_DESC(irq, "IRQ number(s) (0=none, 254=auto [default])");

अटल पूर्णांक base[] = अणु 0, 0, 0, 0, 0, 0, 0, 0 पूर्ण;
module_param_hw_array(base, पूर्णांक, ioport, शून्य, 0);
MODULE_PARM_DESC(base, "base address(es)");

अटल पूर्णांक card[] = अणु -1, -1, -1, -1, -1, -1, -1, -1 पूर्ण;
module_param_array(card, पूर्णांक, शून्य, 0);
MODULE_PARM_DESC(card, "card type (0=NCR5380, 1=NCR53C400, 2=NCR53C400A, 3=DTC3181E, 4=HP C2502)");

MODULE_ALIAS("g_NCR5380_mmio");
MODULE_LICENSE("GPL");

अटल व्योम g_NCR5380_trigger_irq(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);

	/*
	 * An पूर्णांकerrupt is triggered whenever BSY = false, SEL = true
	 * and a bit set in the SELECT_ENABLE_REG is निश्चितed on the
	 * SCSI bus.
	 *
	 * Note that the bus is only driven when the phase control संकेतs
	 * (I/O, C/D, and MSG) match those in the TCR.
	 */
	NCR5380_ग_लिखो(TARGET_COMMAND_REG,
	              PHASE_SR_TO_TCR(NCR5380_पढ़ो(STATUS_REG) & PHASE_MASK));
	NCR5380_ग_लिखो(SELECT_ENABLE_REG, hostdata->id_mask);
	NCR5380_ग_लिखो(OUTPUT_DATA_REG, hostdata->id_mask);
	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG,
	              ICR_BASE | ICR_ASSERT_DATA | ICR_ASSERT_SEL);

	msleep(1);

	NCR5380_ग_लिखो(INITIATOR_COMMAND_REG, ICR_BASE);
	NCR5380_ग_लिखो(SELECT_ENABLE_REG, 0);
	NCR5380_ग_लिखो(TARGET_COMMAND_REG, 0);
पूर्ण

/**
 * g_NCR5380_probe_irq - find the IRQ of a NCR5380 or equivalent
 * @instance: SCSI host instance
 *
 * Autoprobe क्रम the IRQ line used by the card by triggering an IRQ
 * and then looking to see what पूर्णांकerrupt actually turned up.
 */

अटल पूर्णांक g_NCR5380_probe_irq(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	पूर्णांक irq_mask, irq;

	NCR5380_पढ़ो(RESET_PARITY_INTERRUPT_REG);
	irq_mask = probe_irq_on();
	g_NCR5380_trigger_irq(instance);
	irq = probe_irq_off(irq_mask);
	NCR5380_पढ़ो(RESET_PARITY_INTERRUPT_REG);

	अगर (irq <= 0)
		वापस NO_IRQ;
	वापस irq;
पूर्ण

/*
 * Configure I/O address of 53C400A or DTC436 by writing magic numbers
 * to ports 0x779 and 0x379.
 */
अटल व्योम magic_configure(पूर्णांक idx, u8 irq, u8 magic[])
अणु
	u8 cfg = 0;

	outb(magic[0], 0x779);
	outb(magic[1], 0x379);
	outb(magic[2], 0x379);
	outb(magic[3], 0x379);
	outb(magic[4], 0x379);

	अगर (irq == 9)
		irq = 2;

	अगर (idx >= 0 && idx <= 7)
		cfg = 0x80 | idx | (irq << 4);
	outb(cfg, 0x379);
पूर्ण

अटल irqवापस_t legacy_empty_irq_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक legacy_find_मुक्त_irq(पूर्णांक *irq_table)
अणु
	जबतक (*irq_table != -1) अणु
		अगर (!request_irq(*irq_table, legacy_empty_irq_handler,
		                 IRQF_PROBE_SHARED, "Test IRQ",
		                 (व्योम *)irq_table)) अणु
			मुक्त_irq(*irq_table, (व्योम *) irq_table);
			वापस *irq_table;
		पूर्ण
		irq_table++;
	पूर्ण
	वापस -1;
पूर्ण

अटल अचिन्हित पूर्णांक ncr_53c400a_ports[] = अणु
	0x280, 0x290, 0x300, 0x310, 0x330, 0x340, 0x348, 0x350, 0
पूर्ण;
अटल अचिन्हित पूर्णांक dtc_3181e_ports[] = अणु
	0x220, 0x240, 0x280, 0x2a0, 0x2c0, 0x300, 0x320, 0x340, 0
पूर्ण;
अटल u8 ncr_53c400a_magic[] = अणु	/* 53C400A & DTC436 */
	0x59, 0xb9, 0xc5, 0xae, 0xa6
पूर्ण;
अटल u8 hp_c2502_magic[] = अणु	/* HP C2502 */
	0x0f, 0x22, 0xf0, 0x20, 0x80
पूर्ण;
अटल पूर्णांक hp_c2502_irqs[] = अणु
	9, 5, 7, 3, 4, -1
पूर्ण;

अटल पूर्णांक generic_NCR5380_init_one(काष्ठा scsi_host_ढाँचा *tpnt,
			काष्ठा device *pdev, पूर्णांक base, पूर्णांक irq, पूर्णांक board)
अणु
	bool is_pmio = base <= 0xffff;
	पूर्णांक ret;
	पूर्णांक flags = 0;
	अचिन्हित पूर्णांक *ports = शून्य;
	u8 *magic = शून्य;
	पूर्णांक i;
	पूर्णांक port_idx = -1;
	अचिन्हित दीर्घ region_size;
	काष्ठा Scsi_Host *instance;
	काष्ठा NCR5380_hostdata *hostdata;
	u8 __iomem *iomem;

	चयन (board) अणु
	हाल BOARD_NCR5380:
		flags = FLAG_NO_PSEUDO_DMA | FLAG_DMA_FIXUP;
		अवरोध;
	हाल BOARD_NCR53C400A:
		ports = ncr_53c400a_ports;
		magic = ncr_53c400a_magic;
		अवरोध;
	हाल BOARD_HP_C2502:
		ports = ncr_53c400a_ports;
		magic = hp_c2502_magic;
		अवरोध;
	हाल BOARD_DTC3181E:
		ports = dtc_3181e_ports;
		magic = ncr_53c400a_magic;
		अवरोध;
	पूर्ण

	अगर (is_pmio && ports && magic) अणु
		/* wakeup sequence क्रम the NCR53C400A and DTC3181E */

		/* Disable the adapter and look क्रम a मुक्त io port */
		magic_configure(-1, 0, magic);

		region_size = 16;
		अगर (base)
			क्रम (i = 0; ports[i]; i++) अणु
				अगर (base == ports[i]) अणु	/* index found */
					अगर (!request_region(ports[i],
							    region_size,
							    "ncr53c80"))
						वापस -EBUSY;
					अवरोध;
				पूर्ण
			पूर्ण
		अन्यथा
			क्रम (i = 0; ports[i]; i++) अणु
				अगर (!request_region(ports[i], region_size,
						    "ncr53c80"))
					जारी;
				अगर (inb(ports[i]) == 0xff)
					अवरोध;
				release_region(ports[i], region_size);
			पूर्ण
		अगर (ports[i]) अणु
			/* At this poपूर्णांक we have our region reserved */
			magic_configure(i, 0, magic); /* no IRQ yet */
			base = ports[i];
			outb(0xc0, base + 9);
			अगर (inb(base + 9) != 0x80) अणु
				ret = -ENODEV;
				जाओ out_release;
			पूर्ण
			port_idx = i;
		पूर्ण अन्यथा
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (is_pmio) अणु
		/* NCR5380 - no configuration, just grab */
		region_size = 8;
		अगर (!base || !request_region(base, region_size, "ncr5380"))
			वापस -EBUSY;
	पूर्ण अन्यथा अणु	/* MMIO */
		region_size = NCR53C400_region_size;
		अगर (!request_mem_region(base, region_size, "ncr5380"))
			वापस -EBUSY;
	पूर्ण

	अगर (is_pmio)
		iomem = ioport_map(base, region_size);
	अन्यथा
		iomem = ioremap(base, region_size);

	अगर (!iomem) अणु
		ret = -ENOMEM;
		जाओ out_release;
	पूर्ण

	instance = scsi_host_alloc(tpnt, माप(काष्ठा NCR5380_hostdata));
	अगर (instance == शून्य) अणु
		ret = -ENOMEM;
		जाओ out_unmap;
	पूर्ण
	hostdata = shost_priv(instance);

	hostdata->board = board;
	hostdata->io = iomem;
	hostdata->region_size = region_size;

	अगर (is_pmio) अणु
		hostdata->io_port = base;
		hostdata->io_width = 1; /* 8-bit PDMA by शेष */
		hostdata->offset = 0;

		/*
		 * On NCR53C400 boards, NCR5380 रेजिस्टरs are mapped 8 past
		 * the base address.
		 */
		चयन (board) अणु
		हाल BOARD_NCR53C400:
			hostdata->io_port += 8;
			hostdata->c400_ctl_status = 0;
			hostdata->c400_blk_cnt = 1;
			hostdata->c400_host_buf = 4;
			अवरोध;
		हाल BOARD_DTC3181E:
			hostdata->io_width = 2;	/* 16-bit PDMA */
			fallthrough;
		हाल BOARD_NCR53C400A:
		हाल BOARD_HP_C2502:
			hostdata->c400_ctl_status = 9;
			hostdata->c400_blk_cnt = 10;
			hostdata->c400_host_buf = 8;
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		hostdata->base = base;
		hostdata->offset = NCR53C400_mem_base;
		चयन (board) अणु
		हाल BOARD_NCR53C400:
			hostdata->c400_ctl_status = 0x100;
			hostdata->c400_blk_cnt = 0x101;
			hostdata->c400_host_buf = 0x104;
			अवरोध;
		हाल BOARD_DTC3181E:
		हाल BOARD_NCR53C400A:
		हाल BOARD_HP_C2502:
			pr_err(DRV_MODULE_NAME ": unknown register offsets\n");
			ret = -EINVAL;
			जाओ out_unरेजिस्टर;
		पूर्ण
	पूर्ण

	/* Check क्रम vacant slot */
	NCR5380_ग_लिखो(MODE_REG, 0);
	अगर (NCR5380_पढ़ो(MODE_REG) != 0) अणु
		ret = -ENODEV;
		जाओ out_unरेजिस्टर;
	पूर्ण

	ret = NCR5380_init(instance, flags | FLAG_LATE_DMA_SETUP);
	अगर (ret)
		जाओ out_unरेजिस्टर;

	चयन (board) अणु
	हाल BOARD_NCR53C400:
	हाल BOARD_DTC3181E:
	हाल BOARD_NCR53C400A:
	हाल BOARD_HP_C2502:
		NCR5380_ग_लिखो(hostdata->c400_ctl_status, CSR_BASE);
	पूर्ण

	NCR5380_maybe_reset_bus(instance);

	/* Compatibility with करोcumented NCR5380 kernel parameters */
	अगर (irq == 255 || irq == 0)
		irq = NO_IRQ;
	अन्यथा अगर (irq == -1)
		irq = IRQ_AUTO;

	अगर (board == BOARD_HP_C2502) अणु
		पूर्णांक *irq_table = hp_c2502_irqs;
		पूर्णांक board_irq = -1;

		चयन (irq) अणु
		हाल NO_IRQ:
			board_irq = 0;
			अवरोध;
		हाल IRQ_AUTO:
			board_irq = legacy_find_मुक्त_irq(irq_table);
			अवरोध;
		शेष:
			जबतक (*irq_table != -1)
				अगर (*irq_table++ == irq)
					board_irq = irq;
		पूर्ण

		अगर (board_irq <= 0) अणु
			board_irq = 0;
			irq = NO_IRQ;
		पूर्ण

		magic_configure(port_idx, board_irq, magic);
	पूर्ण

	अगर (irq == IRQ_AUTO) अणु
		instance->irq = g_NCR5380_probe_irq(instance);
		अगर (instance->irq == NO_IRQ)
			shost_prपूर्णांकk(KERN_INFO, instance, "no irq detected\n");
	पूर्ण अन्यथा अणु
		instance->irq = irq;
		अगर (instance->irq == NO_IRQ)
			shost_prपूर्णांकk(KERN_INFO, instance, "no irq provided\n");
	पूर्ण

	अगर (instance->irq != NO_IRQ) अणु
		अगर (request_irq(instance->irq, generic_NCR5380_पूर्णांकr,
				0, "NCR5380", instance)) अणु
			instance->irq = NO_IRQ;
			shost_prपूर्णांकk(KERN_INFO, instance,
			             "irq %d denied\n", instance->irq);
		पूर्ण अन्यथा अणु
			shost_prपूर्णांकk(KERN_INFO, instance,
			             "irq %d acquired\n", instance->irq);
		पूर्ण
	पूर्ण

	ret = scsi_add_host(instance, pdev);
	अगर (ret)
		जाओ out_मुक्त_irq;
	scsi_scan_host(instance);
	dev_set_drvdata(pdev, instance);
	वापस 0;

out_मुक्त_irq:
	अगर (instance->irq != NO_IRQ)
		मुक्त_irq(instance->irq, instance);
	NCR5380_निकास(instance);
out_unरेजिस्टर:
	scsi_host_put(instance);
out_unmap:
	iounmap(iomem);
out_release:
	अगर (is_pmio)
		release_region(base, region_size);
	अन्यथा
		release_mem_region(base, region_size);
	वापस ret;
पूर्ण

अटल व्योम generic_NCR5380_release_resources(काष्ठा Scsi_Host *instance)
अणु
	काष्ठा NCR5380_hostdata *hostdata = shost_priv(instance);
	व्योम __iomem *iomem = hostdata->io;
	अचिन्हित दीर्घ io_port = hostdata->io_port;
	अचिन्हित दीर्घ base = hostdata->base;
	अचिन्हित दीर्घ region_size = hostdata->region_size;

	scsi_हटाओ_host(instance);
	अगर (instance->irq != NO_IRQ)
		मुक्त_irq(instance->irq, instance);
	NCR5380_निकास(instance);
	scsi_host_put(instance);
	iounmap(iomem);
	अगर (io_port)
		release_region(io_port, region_size);
	अन्यथा
		release_mem_region(base, region_size);
पूर्ण

/* रुको_क्रम_53c80_access - रुको क्रम 53C80 रेजिस्टरs to become accessible
 * @hostdata: scsi host निजी data
 *
 * The रेजिस्टरs within the 53C80 logic block are inaccessible until
 * bit 7 in the 53C400 control status रेजिस्टर माला_लो निश्चितed.
 */

अटल व्योम रुको_क्रम_53c80_access(काष्ठा NCR5380_hostdata *hostdata)
अणु
	पूर्णांक count = 10000;

	करो अणु
		अगर (hostdata->board == BOARD_DTC3181E)
			udelay(4); /* DTC436 chip hangs without this */
		अगर (NCR5380_पढ़ो(hostdata->c400_ctl_status) & CSR_53C80_REG)
			वापस;
	पूर्ण जबतक (--count > 0);

	scmd_prपूर्णांकk(KERN_ERR, hostdata->connected,
	            "53c80 registers not accessible, device will be reset\n");
	NCR5380_ग_लिखो(hostdata->c400_ctl_status, CSR_RESET);
	NCR5380_ग_लिखो(hostdata->c400_ctl_status, CSR_BASE);
पूर्ण

/**
 * generic_NCR5380_precv - pseuकरो DMA receive
 * @hostdata: scsi host निजी data
 * @dst: buffer to ग_लिखो पूर्णांकo
 * @len: transfer size
 *
 * Perक्रमm a pseuकरो DMA mode receive from a 53C400 or equivalent device.
 */

अटल अंतरभूत पूर्णांक generic_NCR5380_precv(काष्ठा NCR5380_hostdata *hostdata,
                                        अचिन्हित अक्षर *dst, पूर्णांक len)
अणु
	पूर्णांक residual;
	पूर्णांक start = 0;

	NCR5380_ग_लिखो(hostdata->c400_ctl_status, CSR_BASE | CSR_TRANS_सूची);
	NCR5380_ग_लिखो(hostdata->c400_blk_cnt, len / 128);

	करो अणु
		अगर (start == len - 128) अणु
			/* Ignore End of DMA पूर्णांकerrupt क्रम the final buffer */
			अगर (NCR5380_poll_politely(hostdata, hostdata->c400_ctl_status,
			                          CSR_HOST_BUF_NOT_RDY, 0, 0) < 0)
				अवरोध;
		पूर्ण अन्यथा अणु
			अगर (NCR5380_poll_politely2(hostdata, hostdata->c400_ctl_status,
			                           CSR_HOST_BUF_NOT_RDY, 0,
			                           hostdata->c400_ctl_status,
			                           CSR_GATED_53C80_IRQ,
			                           CSR_GATED_53C80_IRQ, 0) < 0 ||
			    NCR5380_पढ़ो(hostdata->c400_ctl_status) & CSR_HOST_BUF_NOT_RDY)
				अवरोध;
		पूर्ण

		अगर (hostdata->io_port && hostdata->io_width == 2)
			insw(hostdata->io_port + hostdata->c400_host_buf,
			     dst + start, 64);
		अन्यथा अगर (hostdata->io_port)
			insb(hostdata->io_port + hostdata->c400_host_buf,
			     dst + start, 128);
		अन्यथा
			स_नकल_fromio(dst + start,
				hostdata->io + NCR53C400_host_buffer, 128);
		start += 128;
	पूर्ण जबतक (start < len);

	residual = len - start;

	अगर (residual != 0) अणु
		/* 53c80 पूर्णांकerrupt or transfer समयout. Reset 53c400 logic. */
		NCR5380_ग_लिखो(hostdata->c400_ctl_status, CSR_RESET);
		NCR5380_ग_लिखो(hostdata->c400_ctl_status, CSR_BASE);
	पूर्ण
	रुको_क्रम_53c80_access(hostdata);

	अगर (residual == 0 && NCR5380_poll_politely(hostdata, BUS_AND_STATUS_REG,
	                                           BASR_END_DMA_TRANSFER,
	                                           BASR_END_DMA_TRANSFER,
						   0) < 0)
		scmd_prपूर्णांकk(KERN_ERR, hostdata->connected, "%s: End of DMA timeout\n",
		            __func__);

	hostdata->pdma_residual = residual;

	वापस 0;
पूर्ण

/**
 * generic_NCR5380_psend - pseuकरो DMA send
 * @hostdata: scsi host निजी data
 * @src: buffer to पढ़ो from
 * @len: transfer size
 *
 * Perक्रमm a pseuकरो DMA mode send to a 53C400 or equivalent device.
 */

अटल अंतरभूत पूर्णांक generic_NCR5380_psend(काष्ठा NCR5380_hostdata *hostdata,
                                        अचिन्हित अक्षर *src, पूर्णांक len)
अणु
	पूर्णांक residual;
	पूर्णांक start = 0;

	NCR5380_ग_लिखो(hostdata->c400_ctl_status, CSR_BASE);
	NCR5380_ग_लिखो(hostdata->c400_blk_cnt, len / 128);

	करो अणु
		अगर (NCR5380_poll_politely2(hostdata, hostdata->c400_ctl_status,
		                           CSR_HOST_BUF_NOT_RDY, 0,
		                           hostdata->c400_ctl_status,
		                           CSR_GATED_53C80_IRQ,
		                           CSR_GATED_53C80_IRQ, 0) < 0 ||
		    NCR5380_पढ़ो(hostdata->c400_ctl_status) & CSR_HOST_BUF_NOT_RDY) अणु
			/* Both 128 B buffers are in use */
			अगर (start >= 128)
				start -= 128;
			अगर (start >= 128)
				start -= 128;
			अवरोध;
		पूर्ण

		अगर (start >= len && NCR5380_पढ़ो(hostdata->c400_blk_cnt) == 0)
			अवरोध;

		अगर (NCR5380_पढ़ो(hostdata->c400_ctl_status) & CSR_GATED_53C80_IRQ) अणु
			/* Host buffer is empty, other one is in use */
			अगर (start >= 128)
				start -= 128;
			अवरोध;
		पूर्ण

		अगर (start >= len)
			जारी;

		अगर (hostdata->io_port && hostdata->io_width == 2)
			outsw(hostdata->io_port + hostdata->c400_host_buf,
			      src + start, 64);
		अन्यथा अगर (hostdata->io_port)
			outsb(hostdata->io_port + hostdata->c400_host_buf,
			      src + start, 128);
		अन्यथा
			स_नकल_toio(hostdata->io + NCR53C400_host_buffer,
			            src + start, 128);
		start += 128;
	पूर्ण जबतक (1);

	residual = len - start;

	अगर (residual != 0) अणु
		/* 53c80 पूर्णांकerrupt or transfer समयout. Reset 53c400 logic. */
		NCR5380_ग_लिखो(hostdata->c400_ctl_status, CSR_RESET);
		NCR5380_ग_लिखो(hostdata->c400_ctl_status, CSR_BASE);
	पूर्ण
	रुको_क्रम_53c80_access(hostdata);

	अगर (residual == 0) अणु
		अगर (NCR5380_poll_politely(hostdata, TARGET_COMMAND_REG,
		                          TCR_LAST_BYTE_SENT, TCR_LAST_BYTE_SENT,
					  0) < 0)
			scmd_prपूर्णांकk(KERN_ERR, hostdata->connected,
			            "%s: Last Byte Sent timeout\n", __func__);

		अगर (NCR5380_poll_politely(hostdata, BUS_AND_STATUS_REG,
		                          BASR_END_DMA_TRANSFER, BASR_END_DMA_TRANSFER,
					  0) < 0)
			scmd_prपूर्णांकk(KERN_ERR, hostdata->connected, "%s: End of DMA timeout\n",
			            __func__);
	पूर्ण

	hostdata->pdma_residual = residual;

	वापस 0;
पूर्ण

अटल पूर्णांक generic_NCR5380_dma_xfer_len(काष्ठा NCR5380_hostdata *hostdata,
                                        काष्ठा scsi_cmnd *cmd)
अणु
	पूर्णांक transfersize = cmd->SCp.this_residual;

	अगर (hostdata->flags & FLAG_NO_PSEUDO_DMA)
		वापस 0;

	/* 53C400 datasheet: non-modulo-128-byte transfers should use PIO */
	अगर (transfersize % 128)
		वापस 0;

	/* Limit PDMA send to 512 B to aव्योम अक्रमom corruption on DTC3181E */
	अगर (hostdata->board == BOARD_DTC3181E &&
	    cmd->sc_data_direction == DMA_TO_DEVICE)
		transfersize = min(cmd->SCp.this_residual, 512);

	वापस min(transfersize, DMA_MAX_SIZE);
पूर्ण

अटल पूर्णांक generic_NCR5380_dma_residual(काष्ठा NCR5380_hostdata *hostdata)
अणु
	वापस hostdata->pdma_residual;
पूर्ण

/* Include the core driver code. */

#समावेश "NCR5380.c"

अटल काष्ठा scsi_host_ढाँचा driver_ढाँचा = अणु
	.module			= THIS_MODULE,
	.proc_name		= DRV_MODULE_NAME,
	.name			= "Generic NCR5380/NCR53C400 SCSI",
	.info			= generic_NCR5380_info,
	.queuecommand		= generic_NCR5380_queue_command,
	.eh_पात_handler	= generic_NCR5380_पात,
	.eh_host_reset_handler	= generic_NCR5380_host_reset,
	.can_queue		= 16,
	.this_id		= 7,
	.sg_tablesize		= SG_ALL,
	.cmd_per_lun		= 2,
	.dma_boundary		= PAGE_SIZE - 1,
	.cmd_size		= NCR5380_CMD_SIZE,
	.max_sectors		= 128,
पूर्ण;

अटल पूर्णांक generic_NCR5380_isa_match(काष्ठा device *pdev, अचिन्हित पूर्णांक ndev)
अणु
	पूर्णांक ret = generic_NCR5380_init_one(&driver_ढाँचा, pdev, base[ndev],
	                                   irq[ndev], card[ndev]);
	अगर (ret) अणु
		अगर (base[ndev])
			prपूर्णांकk(KERN_WARNING "Card not found at address 0x%03x\n",
			       base[ndev]);
		वापस 0;
	पूर्ण

	वापस 1;
पूर्ण

अटल व्योम generic_NCR5380_isa_हटाओ(काष्ठा device *pdev,
				       अचिन्हित पूर्णांक ndev)
अणु
	generic_NCR5380_release_resources(dev_get_drvdata(pdev));
	dev_set_drvdata(pdev, शून्य);
पूर्ण

अटल काष्ठा isa_driver generic_NCR5380_isa_driver = अणु
	.match		= generic_NCR5380_isa_match,
	.हटाओ		= generic_NCR5380_isa_हटाओ,
	.driver		= अणु
		.name	= DRV_MODULE_NAME
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PNP
अटल स्थिर काष्ठा pnp_device_id generic_NCR5380_pnp_ids[] = अणु
	अणु .id = "DTC436e", .driver_data = BOARD_DTC3181E पूर्ण,
	अणु .id = "" पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pnp, generic_NCR5380_pnp_ids);

अटल पूर्णांक generic_NCR5380_pnp_probe(काष्ठा pnp_dev *pdev,
                                     स्थिर काष्ठा pnp_device_id *id)
अणु
	पूर्णांक base, irq;

	अगर (pnp_activate_dev(pdev) < 0)
		वापस -EBUSY;

	base = pnp_port_start(pdev, 0);
	irq = pnp_irq(pdev, 0);

	वापस generic_NCR5380_init_one(&driver_ढाँचा, &pdev->dev, base, irq,
	                                id->driver_data);
पूर्ण

अटल व्योम generic_NCR5380_pnp_हटाओ(काष्ठा pnp_dev *pdev)
अणु
	generic_NCR5380_release_resources(pnp_get_drvdata(pdev));
	pnp_set_drvdata(pdev, शून्य);
पूर्ण

अटल काष्ठा pnp_driver generic_NCR5380_pnp_driver = अणु
	.name		= DRV_MODULE_NAME,
	.id_table	= generic_NCR5380_pnp_ids,
	.probe		= generic_NCR5380_pnp_probe,
	.हटाओ		= generic_NCR5380_pnp_हटाओ,
पूर्ण;
#पूर्ण_अगर /* defined(CONFIG_PNP) */

अटल पूर्णांक pnp_रेजिस्टरed, isa_रेजिस्टरed;

अटल पूर्णांक __init generic_NCR5380_init(व्योम)
अणु
	पूर्णांक ret = 0;

	/* compatibility with old-style parameters */
	अगर (irq[0] == -1 && base[0] == 0 && card[0] == -1) अणु
		irq[0] = ncr_irq;
		base[0] = ncr_addr;
		अगर (ncr_5380)
			card[0] = BOARD_NCR5380;
		अगर (ncr_53c400)
			card[0] = BOARD_NCR53C400;
		अगर (ncr_53c400a)
			card[0] = BOARD_NCR53C400A;
		अगर (dtc_3181e)
			card[0] = BOARD_DTC3181E;
		अगर (hp_c2502)
			card[0] = BOARD_HP_C2502;
	पूर्ण

#अगर_घोषित CONFIG_PNP
	अगर (!pnp_रेजिस्टर_driver(&generic_NCR5380_pnp_driver))
		pnp_रेजिस्टरed = 1;
#पूर्ण_अगर
	ret = isa_रेजिस्टर_driver(&generic_NCR5380_isa_driver, MAX_CARDS);
	अगर (!ret)
		isa_रेजिस्टरed = 1;

	वापस (pnp_रेजिस्टरed || isa_रेजिस्टरed) ? 0 : ret;
पूर्ण

अटल व्योम __निकास generic_NCR5380_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_PNP
	अगर (pnp_रेजिस्टरed)
		pnp_unरेजिस्टर_driver(&generic_NCR5380_pnp_driver);
#पूर्ण_अगर
	अगर (isa_रेजिस्टरed)
		isa_unरेजिस्टर_driver(&generic_NCR5380_isa_driver);
पूर्ण

module_init(generic_NCR5380_init);
module_निकास(generic_NCR5380_निकास);
