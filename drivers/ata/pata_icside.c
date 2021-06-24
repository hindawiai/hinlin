<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/blkdev.h>
#समावेश <linux/gfp.h>
#समावेश <scsi/scsi_host.h>
#समावेश <linux/ata.h>
#समावेश <linux/libata.h>

#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/ecard.h>

#घोषणा DRV_NAME	"pata_icside"

#घोषणा ICS_IDENT_OFFSET		0x2280

#घोषणा ICS_ARCIN_V5_INTRSTAT		0x0000
#घोषणा ICS_ARCIN_V5_INTROFFSET		0x0004

#घोषणा ICS_ARCIN_V6_INTROFFSET_1	0x2200
#घोषणा ICS_ARCIN_V6_INTRSTAT_1		0x2290
#घोषणा ICS_ARCIN_V6_INTROFFSET_2	0x3200
#घोषणा ICS_ARCIN_V6_INTRSTAT_2		0x3290

काष्ठा portinfo अणु
	अचिन्हित पूर्णांक dataoffset;
	अचिन्हित पूर्णांक ctrloffset;
	अचिन्हित पूर्णांक stepping;
पूर्ण;

अटल स्थिर काष्ठा portinfo pata_icside_portinfo_v5 = अणु
	.dataoffset	= 0x2800,
	.ctrloffset	= 0x2b80,
	.stepping	= 6,
पूर्ण;

अटल स्थिर काष्ठा portinfo pata_icside_portinfo_v6_1 = अणु
	.dataoffset	= 0x2000,
	.ctrloffset	= 0x2380,
	.stepping	= 6,
पूर्ण;

अटल स्थिर काष्ठा portinfo pata_icside_portinfo_v6_2 = अणु
	.dataoffset	= 0x3000,
	.ctrloffset	= 0x3380,
	.stepping	= 6,
पूर्ण;

काष्ठा pata_icside_state अणु
	व्योम __iomem *irq_port;
	व्योम __iomem *ioc_base;
	अचिन्हित पूर्णांक type;
	अचिन्हित पूर्णांक dma;
	काष्ठा अणु
		u8 port_sel;
		u8 disabled;
		अचिन्हित पूर्णांक speed[ATA_MAX_DEVICES];
	पूर्ण port[2];
पूर्ण;

काष्ठा pata_icside_info अणु
	काष्ठा pata_icside_state *state;
	काष्ठा expansion_card	*ec;
	व्योम __iomem		*base;
	व्योम __iomem		*irqaddr;
	अचिन्हित पूर्णांक		irqmask;
	स्थिर expansioncard_ops_t *irqops;
	अचिन्हित पूर्णांक		mwdma_mask;
	अचिन्हित पूर्णांक		nr_ports;
	स्थिर काष्ठा portinfo	*port[2];
	अचिन्हित दीर्घ		raw_base;
	अचिन्हित दीर्घ		raw_ioc_base;
पूर्ण;

#घोषणा ICS_TYPE_A3IN	0
#घोषणा ICS_TYPE_A3USER	1
#घोषणा ICS_TYPE_V6	3
#घोषणा ICS_TYPE_V5	15
#घोषणा ICS_TYPE_NOTYPE	((अचिन्हित पूर्णांक)-1)

/* ---------------- Version 5 PCB Support Functions --------------------- */
/* Prototype: pata_icside_irqenable_arcin_v5 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
 * Purpose  : enable पूर्णांकerrupts from card
 */
अटल व्योम pata_icside_irqenable_arcin_v5 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
अणु
	काष्ठा pata_icside_state *state = ec->irq_data;

	ग_लिखोb(0, state->irq_port + ICS_ARCIN_V5_INTROFFSET);
पूर्ण

/* Prototype: pata_icside_irqdisable_arcin_v5 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
 * Purpose  : disable पूर्णांकerrupts from card
 */
अटल व्योम pata_icside_irqdisable_arcin_v5 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
अणु
	काष्ठा pata_icside_state *state = ec->irq_data;

	पढ़ोb(state->irq_port + ICS_ARCIN_V5_INTROFFSET);
पूर्ण

अटल स्थिर expansioncard_ops_t pata_icside_ops_arcin_v5 = अणु
	.irqenable	= pata_icside_irqenable_arcin_v5,
	.irqdisable	= pata_icside_irqdisable_arcin_v5,
पूर्ण;


/* ---------------- Version 6 PCB Support Functions --------------------- */
/* Prototype: pata_icside_irqenable_arcin_v6 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
 * Purpose  : enable पूर्णांकerrupts from card
 */
अटल व्योम pata_icside_irqenable_arcin_v6 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
अणु
	काष्ठा pata_icside_state *state = ec->irq_data;
	व्योम __iomem *base = state->irq_port;

	अगर (!state->port[0].disabled)
		ग_लिखोb(0, base + ICS_ARCIN_V6_INTROFFSET_1);
	अगर (!state->port[1].disabled)
		ग_लिखोb(0, base + ICS_ARCIN_V6_INTROFFSET_2);
पूर्ण

/* Prototype: pata_icside_irqdisable_arcin_v6 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
 * Purpose  : disable पूर्णांकerrupts from card
 */
अटल व्योम pata_icside_irqdisable_arcin_v6 (काष्ठा expansion_card *ec, पूर्णांक irqnr)
अणु
	काष्ठा pata_icside_state *state = ec->irq_data;

	पढ़ोb(state->irq_port + ICS_ARCIN_V6_INTROFFSET_1);
	पढ़ोb(state->irq_port + ICS_ARCIN_V6_INTROFFSET_2);
पूर्ण

/* Prototype: pata_icside_irqprobe(काष्ठा expansion_card *ec)
 * Purpose  : detect an active पूर्णांकerrupt from card
 */
अटल पूर्णांक pata_icside_irqpending_arcin_v6(काष्ठा expansion_card *ec)
अणु
	काष्ठा pata_icside_state *state = ec->irq_data;

	वापस पढ़ोb(state->irq_port + ICS_ARCIN_V6_INTRSTAT_1) & 1 ||
	       पढ़ोb(state->irq_port + ICS_ARCIN_V6_INTRSTAT_2) & 1;
पूर्ण

अटल स्थिर expansioncard_ops_t pata_icside_ops_arcin_v6 = अणु
	.irqenable	= pata_icside_irqenable_arcin_v6,
	.irqdisable	= pata_icside_irqdisable_arcin_v6,
	.irqpending	= pata_icside_irqpending_arcin_v6,
पूर्ण;


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
 *	B	187 (200)	250 (550)	437 (750)
 *	C	125 (125)	125 (375)	250 (500)
 *	D	62  (50)	125 (375)	187 (425)
 *
 * (figures in brackets are actual measured timings on DIOR/DIOW)
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
अटल व्योम pata_icside_set_dmamode(काष्ठा ata_port *ap, काष्ठा ata_device *adev)
अणु
	काष्ठा pata_icside_state *state = ap->host->निजी_data;
	काष्ठा ata_timing t;
	अचिन्हित पूर्णांक cycle;
	अक्षर iomd_type;

	/*
	 * DMA is based on a 16MHz घड़ी
	 */
	अगर (ata_timing_compute(adev, adev->dma_mode, &t, 1000, 1))
		वापस;

	/*
	 * Choose the IOMD cycle timing which ensure that the पूर्णांकerface
	 * satisfies the measured active, recovery and cycle बार.
	 */
	अगर (t.active <= 50 && t.recover <= 375 && t.cycle <= 425) अणु
		iomd_type = 'D';
		cycle = 187;
	पूर्ण अन्यथा अगर (t.active <= 125 && t.recover <= 375 && t.cycle <= 500) अणु
		iomd_type = 'C';
		cycle = 250;
	पूर्ण अन्यथा अगर (t.active <= 200 && t.recover <= 550 && t.cycle <= 750) अणु
		iomd_type = 'B';
		cycle = 437;
	पूर्ण अन्यथा अणु
		iomd_type = 'A';
		cycle = 562;
	पूर्ण

	ata_dev_info(adev, "timings: act %dns rec %dns cyc %dns (%c)\n",
		     t.active, t.recover, t.cycle, iomd_type);

	state->port[ap->port_no].speed[adev->devno] = cycle;
पूर्ण

अटल व्योम pata_icside_bmdma_setup(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pata_icside_state *state = ap->host->निजी_data;
	अचिन्हित पूर्णांक ग_लिखो = qc->tf.flags & ATA_TFLAG_WRITE;

	/*
	 * We are simplex; BUG अगर we try to fiddle with DMA
	 * जबतक it's active.
	 */
	BUG_ON(dma_channel_active(state->dma));

	/*
	 * Route the DMA संकेतs to the correct पूर्णांकerface
	 */
	ग_लिखोb(state->port[ap->port_no].port_sel, state->ioc_base);

	set_dma_speed(state->dma, state->port[ap->port_no].speed[qc->dev->devno]);
	set_dma_sg(state->dma, qc->sg, qc->n_elem);
	set_dma_mode(state->dma, ग_लिखो ? DMA_MODE_WRITE : DMA_MODE_READ);

	/* issue r/w command */
	ap->ops->sff_exec_command(ap, &qc->tf);
पूर्ण

अटल व्योम pata_icside_bmdma_start(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pata_icside_state *state = ap->host->निजी_data;

	BUG_ON(dma_channel_active(state->dma));
	enable_dma(state->dma);
पूर्ण

अटल व्योम pata_icside_bmdma_stop(काष्ठा ata_queued_cmd *qc)
अणु
	काष्ठा ata_port *ap = qc->ap;
	काष्ठा pata_icside_state *state = ap->host->निजी_data;

	disable_dma(state->dma);

	/* see ata_bmdma_stop */
	ata_sff_dma_छोड़ो(ap);
पूर्ण

अटल u8 pata_icside_bmdma_status(काष्ठा ata_port *ap)
अणु
	काष्ठा pata_icside_state *state = ap->host->निजी_data;
	व्योम __iomem *irq_port;

	irq_port = state->irq_port + (ap->port_no ? ICS_ARCIN_V6_INTRSTAT_2 :
						    ICS_ARCIN_V6_INTRSTAT_1);

	वापस पढ़ोb(irq_port) & 1 ? ATA_DMA_INTR : 0;
पूर्ण

अटल पूर्णांक icside_dma_init(काष्ठा pata_icside_info *info)
अणु
	काष्ठा pata_icside_state *state = info->state;
	काष्ठा expansion_card *ec = info->ec;
	पूर्णांक i;

	क्रम (i = 0; i < ATA_MAX_DEVICES; i++) अणु
		state->port[0].speed[i] = 480;
		state->port[1].speed[i] = 480;
	पूर्ण

	अगर (ec->dma != NO_DMA && !request_dma(ec->dma, DRV_NAME)) अणु
		state->dma = ec->dma;
		info->mwdma_mask = ATA_MWDMA2;
	पूर्ण

	वापस 0;
पूर्ण


अटल काष्ठा scsi_host_ढाँचा pata_icside_sht = अणु
	ATA_BASE_SHT(DRV_NAME),
	.sg_tablesize		= SG_MAX_SEGMENTS,
	.dma_boundary		= IOMD_DMA_BOUNDARY,
पूर्ण;

अटल व्योम pata_icside_postreset(काष्ठा ata_link *link, अचिन्हित पूर्णांक *classes)
अणु
	काष्ठा ata_port *ap = link->ap;
	काष्ठा pata_icside_state *state = ap->host->निजी_data;

	अगर (classes[0] != ATA_DEV_NONE || classes[1] != ATA_DEV_NONE)
		वापस ata_sff_postreset(link, classes);

	state->port[ap->port_no].disabled = 1;

	अगर (state->type == ICS_TYPE_V6) अणु
		/*
		 * Disable पूर्णांकerrupts from this port, otherwise we
		 * receive spurious पूर्णांकerrupts from the भग्नing
		 * पूर्णांकerrupt line.
		 */
		व्योम __iomem *irq_port = state->irq_port +
				(ap->port_no ? ICS_ARCIN_V6_INTROFFSET_2 : ICS_ARCIN_V6_INTROFFSET_1);
		पढ़ोb(irq_port);
	पूर्ण
पूर्ण

अटल काष्ठा ata_port_operations pata_icside_port_ops = अणु
	.inherits		= &ata_bmdma_port_ops,
	/* no need to build any PRD tables क्रम DMA */
	.qc_prep		= ata_noop_qc_prep,
	.sff_data_xfer		= ata_sff_data_xfer32,
	.bmdma_setup		= pata_icside_bmdma_setup,
	.bmdma_start		= pata_icside_bmdma_start,
	.bmdma_stop		= pata_icside_bmdma_stop,
	.bmdma_status		= pata_icside_bmdma_status,

	.cable_detect		= ata_cable_40wire,
	.set_dmamode		= pata_icside_set_dmamode,
	.postreset		= pata_icside_postreset,

	.port_start		= ATA_OP_शून्य,	/* करोn't need PRD table */
पूर्ण;

अटल व्योम pata_icside_setup_ioaddr(काष्ठा ata_port *ap, व्योम __iomem *base,
				     काष्ठा pata_icside_info *info,
				     स्थिर काष्ठा portinfo *port)
अणु
	काष्ठा ata_ioports *ioaddr = &ap->ioaddr;
	व्योम __iomem *cmd = base + port->dataoffset;

	ioaddr->cmd_addr	= cmd;
	ioaddr->data_addr	= cmd + (ATA_REG_DATA    << port->stepping);
	ioaddr->error_addr	= cmd + (ATA_REG_ERR     << port->stepping);
	ioaddr->feature_addr	= cmd + (ATA_REG_FEATURE << port->stepping);
	ioaddr->nsect_addr	= cmd + (ATA_REG_NSECT   << port->stepping);
	ioaddr->lbal_addr	= cmd + (ATA_REG_LBAL    << port->stepping);
	ioaddr->lbam_addr	= cmd + (ATA_REG_LBAM    << port->stepping);
	ioaddr->lbah_addr	= cmd + (ATA_REG_LBAH    << port->stepping);
	ioaddr->device_addr	= cmd + (ATA_REG_DEVICE  << port->stepping);
	ioaddr->status_addr	= cmd + (ATA_REG_STATUS  << port->stepping);
	ioaddr->command_addr	= cmd + (ATA_REG_CMD     << port->stepping);

	ioaddr->ctl_addr	= base + port->ctrloffset;
	ioaddr->altstatus_addr	= ioaddr->ctl_addr;

	ata_port_desc(ap, "cmd 0x%lx ctl 0x%lx",
		      info->raw_base + port->dataoffset,
		      info->raw_base + port->ctrloffset);

	अगर (info->raw_ioc_base)
		ata_port_desc(ap, "iocbase 0x%lx", info->raw_ioc_base);
पूर्ण

अटल पूर्णांक pata_icside_रेजिस्टर_v5(काष्ठा pata_icside_info *info)
अणु
	काष्ठा pata_icside_state *state = info->state;
	व्योम __iomem *base;

	base = ecardm_iomap(info->ec, ECARD_RES_MEMC, 0, 0);
	अगर (!base)
		वापस -ENOMEM;

	state->irq_port = base;

	info->base = base;
	info->irqaddr = base + ICS_ARCIN_V5_INTRSTAT;
	info->irqmask = 1;
	info->irqops = &pata_icside_ops_arcin_v5;
	info->nr_ports = 1;
	info->port[0] = &pata_icside_portinfo_v5;

	info->raw_base = ecard_resource_start(info->ec, ECARD_RES_MEMC);

	वापस 0;
पूर्ण

अटल पूर्णांक pata_icside_रेजिस्टर_v6(काष्ठा pata_icside_info *info)
अणु
	काष्ठा pata_icside_state *state = info->state;
	काष्ठा expansion_card *ec = info->ec;
	व्योम __iomem *ioc_base, *easi_base;
	अचिन्हित पूर्णांक sel = 0;

	ioc_base = ecardm_iomap(ec, ECARD_RES_IOCFAST, 0, 0);
	अगर (!ioc_base)
		वापस -ENOMEM;

	easi_base = ioc_base;

	अगर (ecard_resource_flags(ec, ECARD_RES_EASI)) अणु
		easi_base = ecardm_iomap(ec, ECARD_RES_EASI, 0, 0);
		अगर (!easi_base)
			वापस -ENOMEM;

		/*
		 * Enable access to the EASI region.
		 */
		sel = 1 << 5;
	पूर्ण

	ग_लिखोb(sel, ioc_base);

	state->irq_port = easi_base;
	state->ioc_base = ioc_base;
	state->port[0].port_sel = sel;
	state->port[1].port_sel = sel | 1;

	info->base = easi_base;
	info->irqops = &pata_icside_ops_arcin_v6;
	info->nr_ports = 2;
	info->port[0] = &pata_icside_portinfo_v6_1;
	info->port[1] = &pata_icside_portinfo_v6_2;

	info->raw_base = ecard_resource_start(ec, ECARD_RES_EASI);
	info->raw_ioc_base = ecard_resource_start(ec, ECARD_RES_IOCFAST);

	वापस icside_dma_init(info);
पूर्ण

अटल पूर्णांक pata_icside_add_ports(काष्ठा pata_icside_info *info)
अणु
	काष्ठा expansion_card *ec = info->ec;
	काष्ठा ata_host *host;
	पूर्णांक i;

	अगर (info->irqaddr) अणु
		ec->irqaddr = info->irqaddr;
		ec->irqmask = info->irqmask;
	पूर्ण
	अगर (info->irqops)
		ecard_setirq(ec, info->irqops, info->state);

	/*
	 * Be on the safe side - disable पूर्णांकerrupts
	 */
	ec->ops->irqdisable(ec, ec->irq);

	host = ata_host_alloc(&ec->dev, info->nr_ports);
	अगर (!host)
		वापस -ENOMEM;

	host->निजी_data = info->state;
	host->flags = ATA_HOST_SIMPLEX;

	क्रम (i = 0; i < info->nr_ports; i++) अणु
		काष्ठा ata_port *ap = host->ports[i];

		ap->pio_mask = ATA_PIO4;
		ap->mwdma_mask = info->mwdma_mask;
		ap->flags |= ATA_FLAG_SLAVE_POSS;
		ap->ops = &pata_icside_port_ops;

		pata_icside_setup_ioaddr(ap, info->base, info, info->port[i]);
	पूर्ण

	वापस ata_host_activate(host, ec->irq, ata_bmdma_पूर्णांकerrupt, 0,
				 &pata_icside_sht);
पूर्ण

अटल पूर्णांक pata_icside_probe(काष्ठा expansion_card *ec,
			     स्थिर काष्ठा ecard_id *id)
अणु
	काष्ठा pata_icside_state *state;
	काष्ठा pata_icside_info info;
	व्योम __iomem *idmem;
	पूर्णांक ret;

	ret = ecard_request_resources(ec);
	अगर (ret)
		जाओ out;

	state = devm_kzalloc(&ec->dev, माप(*state), GFP_KERNEL);
	अगर (!state) अणु
		ret = -ENOMEM;
		जाओ release;
	पूर्ण

	state->type = ICS_TYPE_NOTYPE;
	state->dma = NO_DMA;

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

	स_रखो(&info, 0, माप(info));
	info.state = state;
	info.ec = ec;

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
		ret = pata_icside_रेजिस्टर_v5(&info);
		अवरोध;

	हाल ICS_TYPE_V6:
		ret = pata_icside_रेजिस्टर_v6(&info);
		अवरोध;

	शेष:
		dev_warn(&ec->dev, "unknown interface type\n");
		ret = -ENODEV;
		अवरोध;
	पूर्ण

	अगर (ret == 0)
		ret = pata_icside_add_ports(&info);

	अगर (ret == 0)
		जाओ out;

 release:
	ecard_release_resources(ec);
 out:
	वापस ret;
पूर्ण

अटल व्योम pata_icside_shutकरोwn(काष्ठा expansion_card *ec)
अणु
	काष्ठा ata_host *host = ecard_get_drvdata(ec);
	अचिन्हित दीर्घ flags;

	/*
	 * Disable पूर्णांकerrupts from this card.  We need to करो
	 * this beक्रमe disabling EASI since we may be accessing
	 * this रेजिस्टर via that region.
	 */
	local_irq_save(flags);
	ec->ops->irqdisable(ec, ec->irq);
	local_irq_restore(flags);

	/*
	 * Reset the ROM poपूर्णांकer so that we can पढ़ो the ROM
	 * after a soft reboot.  This also disables access to
	 * the IDE taskfile via the EASI region.
	 */
	अगर (host) अणु
		काष्ठा pata_icside_state *state = host->निजी_data;
		अगर (state->ioc_base)
			ग_लिखोb(0, state->ioc_base);
	पूर्ण
पूर्ण

अटल व्योम pata_icside_हटाओ(काष्ठा expansion_card *ec)
अणु
	काष्ठा ata_host *host = ecard_get_drvdata(ec);
	काष्ठा pata_icside_state *state = host->निजी_data;

	ata_host_detach(host);

	pata_icside_shutकरोwn(ec);

	/*
	 * करोn't शून्य out the drvdata - devres/libata wants it
	 * to मुक्त the ata_host काष्ठाure.
	 */
	अगर (state->dma != NO_DMA)
		मुक्त_dma(state->dma);

	ecard_release_resources(ec);
पूर्ण

अटल स्थिर काष्ठा ecard_id pata_icside_ids[] = अणु
	अणु MANU_ICS,  PROD_ICS_IDE  पूर्ण,
	अणु MANU_ICS2, PROD_ICS2_IDE पूर्ण,
	अणु 0xffff, 0xffff पूर्ण
पूर्ण;

अटल काष्ठा ecard_driver pata_icside_driver = अणु
	.probe		= pata_icside_probe,
	.हटाओ 	= pata_icside_हटाओ,
	.shutकरोwn	= pata_icside_shutकरोwn,
	.id_table	= pata_icside_ids,
	.drv = अणु
		.name	= DRV_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init pata_icside_init(व्योम)
अणु
	वापस ecard_रेजिस्टर_driver(&pata_icside_driver);
पूर्ण

अटल व्योम __निकास pata_icside_निकास(व्योम)
अणु
	ecard_हटाओ_driver(&pata_icside_driver);
पूर्ण

MODULE_AUTHOR("Russell King <rmk@arm.linux.org.uk>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("ICS PATA driver");

module_init(pata_icside_init);
module_निकास(pata_icside_निकास);
