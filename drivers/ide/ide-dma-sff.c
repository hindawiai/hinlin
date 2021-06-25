<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/types.h>
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/ide.h>
#समावेश <linux/scatterlist.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/पन.स>

/**
 *	config_drive_क्रम_dma	-	attempt to activate IDE DMA
 *	@drive: the drive to place in DMA mode
 *
 *	If the drive supports at least mode 2 DMA or UDMA of any kind
 *	then attempt to place it पूर्णांकo DMA mode. Drives that are known to
 *	support DMA but predate the DMA properties or that are known
 *	to have DMA handling bugs are also set up appropriately based
 *	on the good/bad drive lists.
 */

पूर्णांक config_drive_क्रम_dma(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u16 *id = drive->id;

	अगर (drive->media != ide_disk) अणु
		अगर (hwअगर->host_flags & IDE_HFLAG_NO_ATAPI_DMA)
			वापस 0;
	पूर्ण

	/*
	 * Enable DMA on any drive that has
	 * UltraDMA (mode 0/1/2/3/4/5/6) enabled
	 */
	अगर ((id[ATA_ID_FIELD_VALID] & 4) &&
	    ((id[ATA_ID_UDMA_MODES] >> 8) & 0x7f))
		वापस 1;

	/*
	 * Enable DMA on any drive that has mode2 DMA
	 * (multi or single) enabled
	 */
	अगर ((id[ATA_ID_MWDMA_MODES] & 0x404) == 0x404 ||
	    (id[ATA_ID_SWDMA_MODES] & 0x404) == 0x404)
		वापस 1;

	/* Consult the list of known "good" drives */
	अगर (ide_dma_good_drive(drive))
		वापस 1;

	वापस 0;
पूर्ण

u8 ide_dma_sff_पढ़ो_status(ide_hwअगर_t *hwअगर)
अणु
	अचिन्हित दीर्घ addr = hwअगर->dma_base + ATA_DMA_STATUS;

	अगर (hwअगर->host_flags & IDE_HFLAG_MMIO)
		वापस पढ़ोb((व्योम __iomem *)addr);
	अन्यथा
		वापस inb(addr);
पूर्ण
EXPORT_SYMBOL_GPL(ide_dma_sff_पढ़ो_status);

अटल व्योम ide_dma_sff_ग_लिखो_status(ide_hwअगर_t *hwअगर, u8 val)
अणु
	अचिन्हित दीर्घ addr = hwअगर->dma_base + ATA_DMA_STATUS;

	अगर (hwअगर->host_flags & IDE_HFLAG_MMIO)
		ग_लिखोb(val, (व्योम __iomem *)addr);
	अन्यथा
		outb(val, addr);
पूर्ण

/**
 *	ide_dma_host_set	-	Enable/disable DMA on a host
 *	@drive: drive to control
 *
 *	Enable/disable DMA on an IDE controller following generic
 *	bus-mastering IDE controller behaviour.
 */

व्योम ide_dma_host_set(ide_drive_t *drive, पूर्णांक on)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 unit = drive->dn & 1;
	u8 dma_stat = hwअगर->dma_ops->dma_sff_पढ़ो_status(hwअगर);

	अगर (on)
		dma_stat |= (1 << (5 + unit));
	अन्यथा
		dma_stat &= ~(1 << (5 + unit));

	ide_dma_sff_ग_लिखो_status(hwअगर, dma_stat);
पूर्ण
EXPORT_SYMBOL_GPL(ide_dma_host_set);

/**
 *	ide_build_dmatable	-	build IDE DMA table
 *
 *	ide_build_dmatable() prepares a dma request. We map the command
 *	to get the pci bus addresses of the buffers and then build up
 *	the PRD table that the IDE layer wants to be fed.
 *
 *	Most chipsets correctly पूर्णांकerpret a length of 0x0000 as 64KB,
 *	but at least one (e.g. CS5530) misपूर्णांकerprets it as zero (!).
 *	So we अवरोध the 64KB entry पूर्णांकo two 32KB entries instead.
 *
 *	Returns the number of built PRD entries अगर all went okay,
 *	वापसs 0 otherwise.
 *
 *	May also be invoked from trm290.c
 */

पूर्णांक ide_build_dmatable(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	__le32 *table = (__le32 *)hwअगर->dmatable_cpu;
	अचिन्हित पूर्णांक count = 0;
	पूर्णांक i;
	काष्ठा scatterlist *sg;
	u8 is_trm290 = !!(hwअगर->host_flags & IDE_HFLAG_TRM290);

	क्रम_each_sg(hwअगर->sg_table, sg, cmd->sg_nents, i) अणु
		u32 cur_addr, cur_len, xcount, bcount;

		cur_addr = sg_dma_address(sg);
		cur_len = sg_dma_len(sg);

		/*
		 * Fill in the dma table, without crossing any 64kB boundaries.
		 * Most hardware requires 16-bit alignment of all blocks,
		 * but the trm290 requires 32-bit alignment.
		 */

		जबतक (cur_len) अणु
			अगर (count++ >= PRD_ENTRIES)
				जाओ use_pio_instead;

			bcount = 0x10000 - (cur_addr & 0xffff);
			अगर (bcount > cur_len)
				bcount = cur_len;
			*table++ = cpu_to_le32(cur_addr);
			xcount = bcount & 0xffff;
			अगर (is_trm290)
				xcount = ((xcount >> 2) - 1) << 16;
			अन्यथा अगर (xcount == 0x0000) अणु
				अगर (count++ >= PRD_ENTRIES)
					जाओ use_pio_instead;
				*table++ = cpu_to_le32(0x8000);
				*table++ = cpu_to_le32(cur_addr + 0x8000);
				xcount = 0x8000;
			पूर्ण
			*table++ = cpu_to_le32(xcount);
			cur_addr += bcount;
			cur_len -= bcount;
		पूर्ण
	पूर्ण

	अगर (count) अणु
		अगर (!is_trm290)
			*--table |= cpu_to_le32(0x80000000);
		वापस count;
	पूर्ण

use_pio_instead:
	prपूर्णांकk(KERN_ERR "%s: %s\n", drive->name,
		count ? "DMA table too small" : "empty DMA table?");

	वापस 0; /* revert to PIO क्रम this request */
पूर्ण
EXPORT_SYMBOL_GPL(ide_build_dmatable);

/**
 *	ide_dma_setup	-	begin a DMA phase
 *	@drive: target device
 *	@cmd: command
 *
 *	Build an IDE DMA PRD (IDE speak क्रम scatter gather table)
 *	and then set up the DMA transfer रेजिस्टरs क्रम a device
 *	that follows generic IDE PCI DMA behaviour. Controllers can
 *	override this function अगर they need to
 *
 *	Returns 0 on success. If a PIO fallback is required then 1
 *	is वापसed.
 */

पूर्णांक ide_dma_setup(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 mmio = (hwअगर->host_flags & IDE_HFLAG_MMIO) ? 1 : 0;
	u8 rw = (cmd->tf_flags & IDE_TFLAG_WRITE) ? 0 : ATA_DMA_WR;
	u8 dma_stat;

	/* fall back to pio! */
	अगर (ide_build_dmatable(drive, cmd) == 0) अणु
		ide_map_sg(drive, cmd);
		वापस 1;
	पूर्ण

	/* PRD table */
	अगर (mmio)
		ग_लिखोl(hwअगर->dmatable_dma,
		       (व्योम __iomem *)(hwअगर->dma_base + ATA_DMA_TABLE_OFS));
	अन्यथा
		outl(hwअगर->dmatable_dma, hwअगर->dma_base + ATA_DMA_TABLE_OFS);

	/* specअगरy r/w */
	अगर (mmio)
		ग_लिखोb(rw, (व्योम __iomem *)(hwअगर->dma_base + ATA_DMA_CMD));
	अन्यथा
		outb(rw, hwअगर->dma_base + ATA_DMA_CMD);

	/* पढ़ो DMA status क्रम INTR & ERROR flags */
	dma_stat = hwअगर->dma_ops->dma_sff_पढ़ो_status(hwअगर);

	/* clear INTR & ERROR flags */
	ide_dma_sff_ग_लिखो_status(hwअगर, dma_stat | ATA_DMA_ERR | ATA_DMA_INTR);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ide_dma_setup);

/**
 *	ide_dma_sff_समयr_expiry	-	handle a DMA समयout
 *	@drive: Drive that समयd out
 *
 *	An IDE DMA transfer समयd out. In the event of an error we ask
 *	the driver to resolve the problem, अगर a DMA transfer is still
 *	in progress we जारी to रुको (arguably we need to add a
 *	secondary 'I don't care what the drive thinks' समयout here)
 *	Finally अगर we have an पूर्णांकerrupt we let it complete the I/O.
 *	But only one समय - we clear expiry and अगर it's still not
 *	completed after WAIT_CMD, we error and retry in PIO.
 *	This can occur अगर an पूर्णांकerrupt is lost or due to hang or bugs.
 */

पूर्णांक ide_dma_sff_समयr_expiry(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 dma_stat = hwअगर->dma_ops->dma_sff_पढ़ो_status(hwअगर);

	prपूर्णांकk(KERN_WARNING "%s: %s: DMA status (0x%02x)\n",
		drive->name, __func__, dma_stat);

	अगर ((dma_stat & 0x18) == 0x18)	/* BUSY Stupid Early Timer !! */
		वापस WAIT_CMD;

	hwअगर->expiry = शून्य;	/* one मुक्त ride क्रम now */

	अगर (dma_stat & ATA_DMA_ERR)	/* ERROR */
		वापस -1;

	अगर (dma_stat & ATA_DMA_ACTIVE)	/* DMAing */
		वापस WAIT_CMD;

	अगर (dma_stat & ATA_DMA_INTR)	/* Got an Interrupt */
		वापस WAIT_CMD;

	वापस 0;	/* Status is unknown -- reset the bus */
पूर्ण
EXPORT_SYMBOL_GPL(ide_dma_sff_समयr_expiry);

व्योम ide_dma_start(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 dma_cmd;

	/* Note that this is करोne *after* the cmd has
	 * been issued to the drive, as per the BM-IDE spec.
	 * The Promise Ultra33 करोesn't work correctly when
	 * we करो this part beक्रमe issuing the drive cmd.
	 */
	अगर (hwअगर->host_flags & IDE_HFLAG_MMIO) अणु
		dma_cmd = पढ़ोb((व्योम __iomem *)(hwअगर->dma_base + ATA_DMA_CMD));
		ग_लिखोb(dma_cmd | ATA_DMA_START,
		       (व्योम __iomem *)(hwअगर->dma_base + ATA_DMA_CMD));
	पूर्ण अन्यथा अणु
		dma_cmd = inb(hwअगर->dma_base + ATA_DMA_CMD);
		outb(dma_cmd | ATA_DMA_START, hwअगर->dma_base + ATA_DMA_CMD);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ide_dma_start);

/* वापसs 1 on error, 0 otherwise */
पूर्णांक ide_dma_end(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 dma_stat = 0, dma_cmd = 0;

	/* stop DMA */
	अगर (hwअगर->host_flags & IDE_HFLAG_MMIO) अणु
		dma_cmd = पढ़ोb((व्योम __iomem *)(hwअगर->dma_base + ATA_DMA_CMD));
		ग_लिखोb(dma_cmd & ~ATA_DMA_START,
		       (व्योम __iomem *)(hwअगर->dma_base + ATA_DMA_CMD));
	पूर्ण अन्यथा अणु
		dma_cmd = inb(hwअगर->dma_base + ATA_DMA_CMD);
		outb(dma_cmd & ~ATA_DMA_START, hwअगर->dma_base + ATA_DMA_CMD);
	पूर्ण

	/* get DMA status */
	dma_stat = hwअगर->dma_ops->dma_sff_पढ़ो_status(hwअगर);

	/* clear INTR & ERROR bits */
	ide_dma_sff_ग_लिखो_status(hwअगर, dma_stat | ATA_DMA_ERR | ATA_DMA_INTR);

#घोषणा CHECK_DMA_MASK (ATA_DMA_ACTIVE | ATA_DMA_ERR | ATA_DMA_INTR)

	/* verअगरy good DMA status */
	अगर ((dma_stat & CHECK_DMA_MASK) != ATA_DMA_INTR)
		वापस 0x10 | dma_stat;
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ide_dma_end);

/* वापसs 1 अगर dma irq issued, 0 otherwise */
पूर्णांक ide_dma_test_irq(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 dma_stat = hwअगर->dma_ops->dma_sff_पढ़ो_status(hwअगर);

	वापस (dma_stat & ATA_DMA_INTR) ? 1 : 0;
पूर्ण
EXPORT_SYMBOL_GPL(ide_dma_test_irq);

स्थिर काष्ठा ide_dma_ops sff_dma_ops = अणु
	.dma_host_set		= ide_dma_host_set,
	.dma_setup		= ide_dma_setup,
	.dma_start		= ide_dma_start,
	.dma_end		= ide_dma_end,
	.dma_test_irq		= ide_dma_test_irq,
	.dma_lost_irq		= ide_dma_lost_irq,
	.dma_समयr_expiry	= ide_dma_sff_समयr_expiry,
	.dma_sff_पढ़ो_status	= ide_dma_sff_पढ़ो_status,
पूर्ण;
EXPORT_SYMBOL_GPL(sff_dma_ops);
