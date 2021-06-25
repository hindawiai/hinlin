<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 1996-2004 Russell King.
 *
 * Please note that this platक्रमm करोes not support 32-bit IDE IO.
 */

#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/ide.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/device.h>
#समावेश <linux/init.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/पन.स>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/ecard.h>

#घोषणा DRV_NAME "icside"

#घोषणा ICS_IDENT_OFFSET		0x2280

#घोषणा ICS_ARCIN_V5_INTRSTAT		0x0000
#घोषणा ICS_ARCIN_V5_INTROFFSET		0x0004
#घोषणा ICS_ARCIN_V5_IDखातापूर्णFSET		0x2800
#घोषणा ICS_ARCIN_V5_IDEALTOFFSET	0x2b80
#घोषणा ICS_ARCIN_V5_IDESTEPPING	6

#घोषणा ICS_ARCIN_V6_IDखातापूर्णFSET_1	0x2000
#घोषणा ICS_ARCIN_V6_INTROFFSET_1	0x2200
#घोषणा ICS_ARCIN_V6_INTRSTAT_1		0x2290
#घोषणा ICS_ARCIN_V6_IDEALTOFFSET_1	0x2380
#घोषणा ICS_ARCIN_V6_IDखातापूर्णFSET_2	0x3000
#घोषणा ICS_ARCIN_V6_INTROFFSET_2	0x3200
#घोषणा ICS_ARCIN_V6_INTRSTAT_2		0x3290
#घोषणा ICS_ARCIN_V6_IDEALTOFFSET_2	0x3380
#घोषणा ICS_ARCIN_V6_IDESTEPPING	6

काष्ठा cardinfo अणु
	अचिन्हित पूर्णांक dataoffset;
	अचिन्हित पूर्णांक ctrloffset;
	अचिन्हित पूर्णांक stepping;
पूर्ण;

अटल काष्ठा cardinfo icside_cardinfo_v5 = अणु
	.dataoffset	= ICS_ARCIN_V5_IDखातापूर्णFSET,
	.ctrloffset	= ICS_ARCIN_V5_IDEALTOFFSET,
	.stepping	= ICS_ARCIN_V5_IDESTEPPING,
पूर्ण;

अटल काष्ठा cardinfo icside_cardinfo_v6_1 = अणु
	.dataoffset	= ICS_ARCIN_V6_IDखातापूर्णFSET_1,
	.ctrloffset	= ICS_ARCIN_V6_IDEALTOFFSET_1,
	.stepping	= ICS_ARCIN_V6_IDESTEPPING,
पूर्ण;

अटल काष्ठा cardinfo icside_cardinfo_v6_2 = अणु
	.dataoffset	= ICS_ARCIN_V6_IDखातापूर्णFSET_2,
	.ctrloffset	= ICS_ARCIN_V6_IDEALTOFFSET_2,
	.stepping	= ICS_ARCIN_V6_IDESTEPPING,
पूर्ण;

काष्ठा icside_state अणु
	अचिन्हित पूर्णांक channel;
	अचिन्हित पूर्णांक enabled;
	व्योम __iomem *irq_port;
	व्योम __iomem *ioc_base;
	अचिन्हित पूर्णांक sel;
	अचिन्हित पूर्णांक type;
	काष्ठा ide_host *host;
पूर्ण;

#घोषणा ICS_TYPE_A3IN	0
#घोषणा ICS_TYPE_A3USER	1
#घोषणा ICS_TYPE_V6	3
#घोषणा ICS_TYPE_V5	15
#घोषणा ICS_TYPE_NOTYPE	((अचिन्हित पूर्णांक)-1)

/* ---------------- Version 5 PCB Support Functions --------------------- */
/* Prototype: icside_irqenable_arcin_v5 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
 * Purpose  : enable पूर्णांकerrupts from card
 */
अटल व्योम icside_irqenable_arcin_v5 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
अणु
	काष्ठा icside_state *state = ec->irq_data;

	ग_लिखोb(0, state->irq_port + ICS_ARCIN_V5_INTROFFSET);
पूर्ण

/* Prototype: icside_irqdisable_arcin_v5 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
 * Purpose  : disable पूर्णांकerrupts from card
 */
अटल व्योम icside_irqdisable_arcin_v5 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
अणु
	काष्ठा icside_state *state = ec->irq_data;

	पढ़ोb(state->irq_port + ICS_ARCIN_V5_INTROFFSET);
पूर्ण

अटल स्थिर expansioncard_ops_t icside_ops_arcin_v5 = अणु
	.irqenable	= icside_irqenable_arcin_v5,
	.irqdisable	= icside_irqdisable_arcin_v5,
पूर्ण;


/* ---------------- Version 6 PCB Support Functions --------------------- */
/* Prototype: icside_irqenable_arcin_v6 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
 * Purpose  : enable पूर्णांकerrupts from card
 */
अटल व्योम icside_irqenable_arcin_v6 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
अणु
	काष्ठा icside_state *state = ec->irq_data;
	व्योम __iomem *base = state->irq_port;

	state->enabled = 1;

	चयन (state->channel) अणु
	हाल 0:
		ग_लिखोb(0, base + ICS_ARCIN_V6_INTROFFSET_1);
		पढ़ोb(base + ICS_ARCIN_V6_INTROFFSET_2);
		अवरोध;
	हाल 1:
		ग_लिखोb(0, base + ICS_ARCIN_V6_INTROFFSET_2);
		पढ़ोb(base + ICS_ARCIN_V6_INTROFFSET_1);
		अवरोध;
	पूर्ण
पूर्ण

/* Prototype: icside_irqdisable_arcin_v6 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
 * Purpose  : disable पूर्णांकerrupts from card
 */
अटल व्योम icside_irqdisable_arcin_v6 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
अणु
	काष्ठा icside_state *state = ec->irq_data;

	state->enabled = 0;

	पढ़ोb(state->irq_port + ICS_ARCIN_V6_INTROFFSET_1);
	पढ़ोb(state->irq_port + ICS_ARCIN_V6_INTROFFSET_2);
पूर्ण

/* Prototype: icside_irqprobe(काष्ठा expansion_card *ec)
 * Purpose  : detect an active पूर्णांकerrupt from card
 */
अटल पूर्णांक icside_irqpending_arcin_v6(काष्ठा expansion_card *ec)
अणु
	काष्ठा icside_state *state = ec->irq_data;

	वापस पढ़ोb(state->irq_port + ICS_ARCIN_V6_INTRSTAT_1) & 1 ||
	       पढ़ोb(state->irq_port + ICS_ARCIN_V6_INTRSTAT_2) & 1;
पूर्ण

अटल स्थिर expansioncard_ops_t icside_ops_arcin_v6 = अणु
	.irqenable	= icside_irqenable_arcin_v6,
	.irqdisable	= icside_irqdisable_arcin_v6,
	.irqpending	= icside_irqpending_arcin_v6,
पूर्ण;

/*
 * Handle routing of पूर्णांकerrupts.  This is called beक्रमe
 * we ग_लिखो the command to the drive.
 */
अटल व्योम icside_maskproc(ide_drive_t *drive, पूर्णांक mask)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा expansion_card *ec = ECARD_DEV(hwअगर->dev);
	काष्ठा icside_state *state = ecard_get_drvdata(ec);
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	state->channel = hwअगर->channel;

	अगर (state->enabled && !mask) अणु
		चयन (hwअगर->channel) अणु
		हाल 0:
			ग_लिखोb(0, state->irq_port + ICS_ARCIN_V6_INTROFFSET_1);
			पढ़ोb(state->irq_port + ICS_ARCIN_V6_INTROFFSET_2);
			अवरोध;
		हाल 1:
			ग_लिखोb(0, state->irq_port + ICS_ARCIN_V6_INTROFFSET_2);
			पढ़ोb(state->irq_port + ICS_ARCIN_V6_INTROFFSET_1);
			अवरोध;
		पूर्ण
	पूर्ण अन्यथा अणु
		पढ़ोb(state->irq_port + ICS_ARCIN_V6_INTROFFSET_2);
		पढ़ोb(state->irq_port + ICS_ARCIN_V6_INTROFFSET_1);
	पूर्ण

	local_irq_restore(flags);
पूर्ण

अटल स्थिर काष्ठा ide_port_ops icside_v6_no_dma_port_ops = अणु
	.maskproc		= icside_maskproc,
पूर्ण;

#अगर_घोषित CONFIG_BLK_DEV_IDEDMA_ICS
/*
 * SG-DMA support.
 *
 * Similar to the BM-DMA, but we use the RiscPCs IOMD DMA controllers.
 * There is only one DMA controller per card, which means that only
 * one drive can be accessed at one समय.  NOTE! We करो not enक्रमce that
 * here, but we rely on the मुख्य IDE driver spotting that both
 * पूर्णांकerfaces use the same IRQ, which should guarantee this.
 */

/*
 * Configure the IOMD to give the appropriate timings क्रम the transfer
 * mode being requested.  We take the advice of the ATA standards, and
 * calculate the cycle समय based on the transfer mode, and the EIDE
 * MW DMA specs that the drive provides in the IDENTIFY command.
 *
 * We have the following IOMD DMA modes to choose from:
 *
 *	Type	Active		Recovery	Cycle
 *	A	250 (250)	312 (550)	562 (800)
 *	B	187		250		437
 *	C	125 (125)	125 (375)	250 (500)
 *	D	62		125		187
 *
 * (figures in brackets are actual measured timings)
 *
 * However, we also need to take care of the पढ़ो/ग_लिखो active and
 * recovery timings:
 *
 *			Read	Write
 *  	Mode	Active	-- Recovery --	Cycle	IOMD type
 *	MW0	215	50	215	480	A
 *	MW1	80	50	50	150	C
 *	MW2	70	25	25	120	C
 */
अटल व्योम icside_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	अचिन्हित दीर्घ cycle_समय = 0;
	पूर्णांक use_dma_info = 0;
	स्थिर u8 xfer_mode = drive->dma_mode;

	चयन (xfer_mode) अणु
	हाल XFER_MW_DMA_2:
		cycle_समय = 250;
		use_dma_info = 1;
		अवरोध;

	हाल XFER_MW_DMA_1:
		cycle_समय = 250;
		use_dma_info = 1;
		अवरोध;

	हाल XFER_MW_DMA_0:
		cycle_समय = 480;
		अवरोध;

	हाल XFER_SW_DMA_2:
	हाल XFER_SW_DMA_1:
	हाल XFER_SW_DMA_0:
		cycle_समय = 480;
		अवरोध;
	पूर्ण

	/*
	 * If we're going to be करोing MW_DMA_1 or MW_DMA_2, we should
	 * take care to note the values in the ID...
	 */
	अगर (use_dma_info && drive->id[ATA_ID_EIDE_DMA_TIME] > cycle_समय)
		cycle_समय = drive->id[ATA_ID_EIDE_DMA_TIME];

	ide_set_drivedata(drive, (व्योम *)cycle_समय);

	prपूर्णांकk(KERN_INFO "%s: %s selected (peak %luMB/s)\n",
	       drive->name, ide_xfer_verbose(xfer_mode),
	       2000 / (cycle_समय ? cycle_समय : (अचिन्हित दीर्घ) -1));
पूर्ण

अटल स्थिर काष्ठा ide_port_ops icside_v6_port_ops = अणु
	.set_dma_mode		= icside_set_dma_mode,
	.maskproc		= icside_maskproc,
पूर्ण;

अटल व्योम icside_dma_host_set(ide_drive_t *drive, पूर्णांक on)
अणु
पूर्ण

अटल पूर्णांक icside_dma_end(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा expansion_card *ec = ECARD_DEV(hwअगर->dev);

	disable_dma(ec->dma);

	वापस get_dma_residue(ec->dma) != 0;
पूर्ण

अटल व्योम icside_dma_start(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा expansion_card *ec = ECARD_DEV(hwअगर->dev);

	/* We can not enable DMA on both channels simultaneously. */
	BUG_ON(dma_channel_active(ec->dma));
	enable_dma(ec->dma);
पूर्ण

अटल पूर्णांक icside_dma_setup(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा expansion_card *ec = ECARD_DEV(hwअगर->dev);
	काष्ठा icside_state *state = ecard_get_drvdata(ec);
	अचिन्हित पूर्णांक dma_mode;

	अगर (cmd->tf_flags & IDE_TFLAG_WRITE)
		dma_mode = DMA_MODE_WRITE;
	अन्यथा
		dma_mode = DMA_MODE_READ;

	/*
	 * We can not enable DMA on both channels.
	 */
	BUG_ON(dma_channel_active(ec->dma));

	/*
	 * Ensure that we have the right पूर्णांकerrupt routed.
	 */
	icside_maskproc(drive, 0);

	/*
	 * Route the DMA संकेतs to the correct पूर्णांकerface.
	 */
	ग_लिखोb(state->sel | hwअगर->channel, state->ioc_base);

	/*
	 * Select the correct timing क्रम this drive.
	 */
	set_dma_speed(ec->dma, (अचिन्हित दीर्घ)ide_get_drivedata(drive));

	/*
	 * Tell the DMA engine about the SG table and
	 * data direction.
	 */
	set_dma_sg(ec->dma, hwअगर->sg_table, cmd->sg_nents);
	set_dma_mode(ec->dma, dma_mode);

	वापस 0;
पूर्ण

अटल पूर्णांक icside_dma_test_irq(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	काष्ठा expansion_card *ec = ECARD_DEV(hwअगर->dev);
	काष्ठा icside_state *state = ecard_get_drvdata(ec);

	वापस पढ़ोb(state->irq_port +
		     (hwअगर->channel ?
			ICS_ARCIN_V6_INTRSTAT_2 :
			ICS_ARCIN_V6_INTRSTAT_1)) & 1;
पूर्ण

अटल पूर्णांक icside_dma_init(ide_hwअगर_t *hwअगर, स्थिर काष्ठा ide_port_info *d)
अणु
	hwअगर->dmatable_cpu	= शून्य;
	hwअगर->dmatable_dma	= 0;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ide_dma_ops icside_v6_dma_ops = अणु
	.dma_host_set		= icside_dma_host_set,
	.dma_setup		= icside_dma_setup,
	.dma_start		= icside_dma_start,
	.dma_end		= icside_dma_end,
	.dma_test_irq		= icside_dma_test_irq,
	.dma_lost_irq		= ide_dma_lost_irq,
पूर्ण;
#पूर्ण_अगर

अटल पूर्णांक icside_dma_off_init(ide_hwअगर_t *hwअगर, स्थिर काष्ठा ide_port_info *d)
अणु
	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम icside_setup_ports(काष्ठा ide_hw *hw, व्योम __iomem *base,
			       काष्ठा cardinfo *info, काष्ठा expansion_card *ec)
अणु
	अचिन्हित दीर्घ port = (अचिन्हित दीर्घ)base + info->dataoffset;

	hw->io_ports.data_addr	 = port;
	hw->io_ports.error_addr	 = port + (1 << info->stepping);
	hw->io_ports.nsect_addr	 = port + (2 << info->stepping);
	hw->io_ports.lbal_addr	 = port + (3 << info->stepping);
	hw->io_ports.lbam_addr	 = port + (4 << info->stepping);
	hw->io_ports.lbah_addr	 = port + (5 << info->stepping);
	hw->io_ports.device_addr = port + (6 << info->stepping);
	hw->io_ports.status_addr = port + (7 << info->stepping);
	hw->io_ports.ctl_addr	 = (अचिन्हित दीर्घ)base + info->ctrloffset;

	hw->irq = ec->irq;
	hw->dev = &ec->dev;
पूर्ण

अटल स्थिर काष्ठा ide_port_info icside_v5_port_info = अणु
	.host_flags		= IDE_HFLAG_NO_DMA,
	.chipset		= ide_acorn,
पूर्ण;

अटल पूर्णांक icside_रेजिस्टर_v5(काष्ठा icside_state *state,
			      काष्ठा expansion_card *ec)
अणु
	व्योम __iomem *base;
	काष्ठा ide_host *host;
	काष्ठा ide_hw hw, *hws[] = अणु &hw पूर्ण;
	पूर्णांक ret;

	base = ecardm_iomap(ec, ECARD_RES_MEMC, 0, 0);
	अगर (!base)
		वापस -ENOMEM;

	state->irq_port = base;

	ec->irqaddr  = base + ICS_ARCIN_V5_INTRSTAT;
	ec->irqmask  = 1;

	ecard_setirq(ec, &icside_ops_arcin_v5, state);

	/*
	 * Be on the safe side - disable पूर्णांकerrupts
	 */
	icside_irqdisable_arcin_v5(ec, 0);

	icside_setup_ports(&hw, base, &icside_cardinfo_v5, ec);

	host = ide_host_alloc(&icside_v5_port_info, hws, 1);
	अगर (host == शून्य)
		वापस -ENODEV;

	state->host = host;

	ecard_set_drvdata(ec, state);

	ret = ide_host_रेजिस्टर(host, &icside_v5_port_info, hws);
	अगर (ret)
		जाओ err_मुक्त;

	वापस 0;
err_मुक्त:
	ide_host_मुक्त(host);
	ecard_set_drvdata(ec, शून्य);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ide_port_info icside_v6_port_info = अणु
	.init_dma		= icside_dma_off_init,
	.port_ops		= &icside_v6_no_dma_port_ops,
	.host_flags		= IDE_HFLAG_SERIALIZE | IDE_HFLAG_MMIO,
	.mwdma_mask		= ATA_MWDMA2,
	.swdma_mask		= ATA_SWDMA2,
	.chipset		= ide_acorn,
पूर्ण;

अटल पूर्णांक icside_रेजिस्टर_v6(काष्ठा icside_state *state,
			      काष्ठा expansion_card *ec)
अणु
	व्योम __iomem *ioc_base, *easi_base;
	काष्ठा ide_host *host;
	अचिन्हित पूर्णांक sel = 0;
	पूर्णांक ret;
	काष्ठा ide_hw hw[2], *hws[] = अणु &hw[0], &hw[1] पूर्ण;
	काष्ठा ide_port_info d = icside_v6_port_info;

	ioc_base = ecardm_iomap(ec, ECARD_RES_IOCFAST, 0, 0);
	अगर (!ioc_base) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	easi_base = ioc_base;

	अगर (ecard_resource_flags(ec, ECARD_RES_EASI)) अणु
		easi_base = ecardm_iomap(ec, ECARD_RES_EASI, 0, 0);
		अगर (!easi_base) अणु
			ret = -ENOMEM;
			जाओ out;
		पूर्ण

		/*
		 * Enable access to the EASI region.
		 */
		sel = 1 << 5;
	पूर्ण

	ग_लिखोb(sel, ioc_base);

	ecard_setirq(ec, &icside_ops_arcin_v6, state);

	state->irq_port   = easi_base;
	state->ioc_base   = ioc_base;
	state->sel	  = sel;

	/*
	 * Be on the safe side - disable पूर्णांकerrupts
	 */
	icside_irqdisable_arcin_v6(ec, 0);

	icside_setup_ports(&hw[0], easi_base, &icside_cardinfo_v6_1, ec);
	icside_setup_ports(&hw[1], easi_base, &icside_cardinfo_v6_2, ec);

	host = ide_host_alloc(&d, hws, 2);
	अगर (host == शून्य)
		वापस -ENODEV;

	state->host = host;

	ecard_set_drvdata(ec, state);

#अगर_घोषित CONFIG_BLK_DEV_IDEDMA_ICS
	अगर (ec->dma != NO_DMA && !request_dma(ec->dma, DRV_NAME)) अणु
		d.init_dma = icside_dma_init;
		d.port_ops = &icside_v6_port_ops;
		d.dma_ops  = &icside_v6_dma_ops;
	पूर्ण
#पूर्ण_अगर

	ret = ide_host_रेजिस्टर(host, &d, hws);
	अगर (ret)
		जाओ err_मुक्त;

	वापस 0;
err_मुक्त:
	ide_host_मुक्त(host);
	अगर (d.dma_ops)
		मुक्त_dma(ec->dma);
	ecard_set_drvdata(ec, शून्य);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक icside_probe(काष्ठा expansion_card *ec, स्थिर काष्ठा ecard_id *id)
अणु
	काष्ठा icside_state *state;
	व्योम __iomem *idmem;
	पूर्णांक ret;

	ret = ecard_request_resources(ec);
	अगर (ret)
		जाओ out;

	state = kzalloc(माप(काष्ठा icside_state), GFP_KERNEL);
	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ release;
	पूर्ण

	state->type	= ICS_TYPE_NOTYPE;

	idmem = ecardm_iomap(ec, ECARD_RES_IOCFAST, 0, 0);
	अगर (idmem) अणु
		अचिन्हित पूर्णांक type;

		type = पढ़ोb(idmem + ICS_IDENT_OFFSET) & 1;
		type |= (पढ़ोb(idmem + ICS_IDENT_OFFSET + 4) & 1) << 1;
		type |= (पढ़ोb(idmem + ICS_IDENT_OFFSET + 8) & 1) << 2;
		type |= (पढ़ोb(idmem + ICS_IDENT_OFFSET + 12) & 1) << 3;
		ecardm_iounmap(ec, idmem);

		state->type = type;
	पूर्ण

	चयन (state->type) अणु
	हाल ICS_TYPE_A3IN:
		dev_warn(&ec->dev, "A3IN unsupported\n");
		ret = -ENODEV;
		अवरोध;

	हाल ICS_TYPE_A3USER:
		dev_warn(&ec->dev, "A3USER unsupported\n");
		ret = -ENODEV;
		अवरोध;

	हाल ICS_TYPE_V5:
		ret = icside_रेजिस्टर_v5(state, ec);
		अवरोध;

	हाल ICS_TYPE_V6:
		ret = icside_रेजिस्टर_v6(state, ec);
		अवरोध;

	शेष:
		dev_warn(&ec->dev, "unknown interface type\n");
		ret = -ENODEV;
		अवरोध;
	पूर्ण

	अगर (ret == 0)
		जाओ out;

	kमुक्त(state);
 release:
	ecard_release_resources(ec);
 out:
	वापस ret;
पूर्ण

अटल व्योम icside_हटाओ(काष्ठा expansion_card *ec)
अणु
	काष्ठा icside_state *state = ecard_get_drvdata(ec);

	चयन (state->type) अणु
	हाल ICS_TYPE_V5:
		/* FIXME: tell IDE to stop using the पूर्णांकerface */

		/* Disable पूर्णांकerrupts */
		icside_irqdisable_arcin_v5(ec, 0);
		अवरोध;

	हाल ICS_TYPE_V6:
		/* FIXME: tell IDE to stop using the पूर्णांकerface */
		अगर (ec->dma != NO_DMA)
			मुक्त_dma(ec->dma);

		/* Disable पूर्णांकerrupts */
		icside_irqdisable_arcin_v6(ec, 0);

		/* Reset the ROM poपूर्णांकer/EASI selection */
		ग_लिखोb(0, state->ioc_base);
		अवरोध;
	पूर्ण

	ecard_set_drvdata(ec, शून्य);

	kमुक्त(state);
	ecard_release_resources(ec);
पूर्ण

अटल व्योम icside_shutकरोwn(काष्ठा expansion_card *ec)
अणु
	काष्ठा icside_state *state = ecard_get_drvdata(ec);
	अचिन्हित दीर्घ flags;

	/*
	 * Disable पूर्णांकerrupts from this card.  We need to करो
	 * this beक्रमe disabling EASI since we may be accessing
	 * this रेजिस्टर via that region.
	 */
	local_irq_save(flags);
	ec->ops->irqdisable(ec, 0);
	local_irq_restore(flags);

	/*
	 * Reset the ROM poपूर्णांकer so that we can पढ़ो the ROM
	 * after a soft reboot.  This also disables access to
	 * the IDE taskfile via the EASI region.
	 */
	अगर (state->ioc_base)
		ग_लिखोb(0, state->ioc_base);
पूर्ण

अटल स्थिर काष्ठा ecard_id icside_ids[] = अणु
	अणु MANU_ICS,  PROD_ICS_IDE  पूर्ण,
	अणु MANU_ICS2, PROD_ICS2_IDE पूर्ण,
	अणु 0xffff, 0xffff पूर्ण
पूर्ण;

अटल काष्ठा ecard_driver icside_driver = अणु
	.probe		= icside_probe,
	.हटाओ		= icside_हटाओ,
	.shutकरोwn	= icside_shutकरोwn,
	.id_table	= icside_ids,
	.drv = अणु
		.name	= "icside",
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init icside_init(व्योम)
अणु
	वापस ecard_रेजिस्टर_driver(&icside_driver);
पूर्ण

अटल व्योम __निकास icside_निकास(व्योम)
अणु
	ecard_हटाओ_driver(&icside_driver);
पूर्ण

MODULE_AUTHOR("Russell King <rmk@arm.linux.org.uk>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ICS IDE driver");

module_init(icside_init);
module_निकास(icside_निकास);
