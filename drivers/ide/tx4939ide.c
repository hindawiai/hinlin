<शैली गुरु>
/*
 * TX4939 पूर्णांकernal IDE driver
 * Based on RBTX49xx patch from CELF patch archive.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * (C) Copyright TOSHIBA CORPORATION 2005-2007
 */

#समावेश <linux/module.h>
#समावेश <linux/types.h>
#समावेश <linux/ide.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/scatterlist.h>

#समावेश <यंत्र/ide.h>

#घोषणा MODNAME	"tx4939ide"

/* ATA Shaकरोw Registers (8-bit except क्रम Data which is 16-bit) */
#घोषणा TX4939IDE_Data			0x000
#घोषणा TX4939IDE_Error_Feature		0x001
#घोषणा TX4939IDE_Sec			0x002
#घोषणा TX4939IDE_LBA0			0x003
#घोषणा TX4939IDE_LBA1			0x004
#घोषणा TX4939IDE_LBA2			0x005
#घोषणा TX4939IDE_DevHead		0x006
#घोषणा TX4939IDE_Stat_Cmd		0x007
#घोषणा TX4939IDE_AltStat_DevCtl	0x402
/* H/W DMA Registers  */
#घोषणा TX4939IDE_DMA_Cmd	0x800	/* 8-bit */
#घोषणा TX4939IDE_DMA_Stat	0x802	/* 8-bit */
#घोषणा TX4939IDE_PRD_Ptr	0x804	/* 32-bit */
/* ATA100 CORE Registers (16-bit) */
#घोषणा TX4939IDE_Sys_Ctl	0xc00
#घोषणा TX4939IDE_Xfer_Cnt_1	0xc08
#घोषणा TX4939IDE_Xfer_Cnt_2	0xc0a
#घोषणा TX4939IDE_Sec_Cnt	0xc10
#घोषणा TX4939IDE_Start_Lo_Addr	0xc18
#घोषणा TX4939IDE_Start_Up_Addr	0xc20
#घोषणा TX4939IDE_Add_Ctl	0xc28
#घोषणा TX4939IDE_Lo_Burst_Cnt	0xc30
#घोषणा TX4939IDE_Up_Burst_Cnt	0xc38
#घोषणा TX4939IDE_PIO_Addr	0xc88
#घोषणा TX4939IDE_H_Rst_Tim	0xc90
#घोषणा TX4939IDE_Int_Ctl	0xc98
#घोषणा TX4939IDE_Pkt_Cmd	0xcb8
#घोषणा TX4939IDE_Bxfer_Cnt_Hi	0xcc0
#घोषणा TX4939IDE_Bxfer_Cnt_Lo	0xcc8
#घोषणा TX4939IDE_Dev_TErr	0xcd0
#घोषणा TX4939IDE_Pkt_Xfer_Ctl	0xcd8
#घोषणा TX4939IDE_Start_TAddr	0xce0

/* bits क्रम Int_Ctl */
#घोषणा TX4939IDE_INT_ADDRERR	0x80
#घोषणा TX4939IDE_INT_REACHMUL	0x40
#घोषणा TX4939IDE_INT_DEVTIMING	0x20
#घोषणा TX4939IDE_INT_UDMATERM	0x10
#घोषणा TX4939IDE_INT_TIMER	0x08
#घोषणा TX4939IDE_INT_BUSERR	0x04
#घोषणा TX4939IDE_INT_XFEREND	0x02
#घोषणा TX4939IDE_INT_HOST	0x01

#घोषणा TX4939IDE_IGNORE_INTS	\
	(TX4939IDE_INT_ADDRERR | TX4939IDE_INT_REACHMUL | \
	 TX4939IDE_INT_DEVTIMING | TX4939IDE_INT_UDMATERM | \
	 TX4939IDE_INT_TIMER | TX4939IDE_INT_XFEREND)

#अगर_घोषित __BIG_ENDIAN
#घोषणा tx4939ide_swizzlel(a)	((a) ^ 4)
#घोषणा tx4939ide_swizzlew(a)	((a) ^ 6)
#घोषणा tx4939ide_swizzleb(a)	((a) ^ 7)
#अन्यथा
#घोषणा tx4939ide_swizzlel(a)	(a)
#घोषणा tx4939ide_swizzlew(a)	(a)
#घोषणा tx4939ide_swizzleb(a)	(a)
#पूर्ण_अगर

अटल u16 tx4939ide_पढ़ोw(व्योम __iomem *base, u32 reg)
अणु
	वापस __raw_पढ़ोw(base + tx4939ide_swizzlew(reg));
पूर्ण
अटल u8 tx4939ide_पढ़ोb(व्योम __iomem *base, u32 reg)
अणु
	वापस __raw_पढ़ोb(base + tx4939ide_swizzleb(reg));
पूर्ण
अटल व्योम tx4939ide_ग_लिखोl(u32 val, व्योम __iomem *base, u32 reg)
अणु
	__raw_ग_लिखोl(val, base + tx4939ide_swizzlel(reg));
पूर्ण
अटल व्योम tx4939ide_ग_लिखोw(u16 val, व्योम __iomem *base, u32 reg)
अणु
	__raw_ग_लिखोw(val, base + tx4939ide_swizzlew(reg));
पूर्ण
अटल व्योम tx4939ide_ग_लिखोb(u8 val, व्योम __iomem *base, u32 reg)
अणु
	__raw_ग_लिखोb(val, base + tx4939ide_swizzleb(reg));
पूर्ण

#घोषणा TX4939IDE_BASE(hwअगर)	((व्योम __iomem *)(hwअगर)->extra_base)

अटल व्योम tx4939ide_set_pio_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	पूर्णांक is_slave = drive->dn;
	u32 mask, val;
	स्थिर u8 pio = drive->pio_mode - XFER_PIO_0;
	u8 safe = pio;
	ide_drive_t *pair;

	pair = ide_get_pair_dev(drive);
	अगर (pair)
		safe = min_t(u8, safe, pair->pio_mode - XFER_PIO_0);
	/*
	 * Update Command Transfer Mode क्रम master/slave and Data
	 * Transfer Mode क्रम this drive.
	 */
	mask = is_slave ? 0x07f00000 : 0x000007f0;
	val = ((safe << 8) | (pio << 4)) << (is_slave ? 16 : 0);
	hwअगर->select_data = (hwअगर->select_data & ~mask) | val;
	/* tx4939ide_tf_load_fixup() will set the Sys_Ctl रेजिस्टर */
पूर्ण

अटल व्योम tx4939ide_set_dma_mode(ide_hwअगर_t *hwअगर, ide_drive_t *drive)
अणु
	u32 mask, val;
	स्थिर u8 mode = drive->dma_mode;

	/* Update Data Transfer Mode क्रम this drive. */
	अगर (mode >= XFER_UDMA_0)
		val = mode - XFER_UDMA_0 + 8;
	अन्यथा
		val = mode - XFER_MW_DMA_0 + 5;
	अगर (drive->dn) अणु
		mask = 0x00f00000;
		val <<= 20;
	पूर्ण अन्यथा अणु
		mask = 0x000000f0;
		val <<= 4;
	पूर्ण
	hwअगर->select_data = (hwअगर->select_data & ~mask) | val;
	/* tx4939ide_tf_load_fixup() will set the Sys_Ctl रेजिस्टर */
पूर्ण

अटल u16 tx4939ide_check_error_पूर्णांकs(ide_hwअगर_t *hwअगर)
अणु
	व्योम __iomem *base = TX4939IDE_BASE(hwअगर);
	u16 ctl = tx4939ide_पढ़ोw(base, TX4939IDE_Int_Ctl);

	अगर (ctl & TX4939IDE_INT_BUSERR) अणु
		/* reset FIFO */
		u16 sysctl = tx4939ide_पढ़ोw(base, TX4939IDE_Sys_Ctl);

		tx4939ide_ग_लिखोw(sysctl | 0x4000, base, TX4939IDE_Sys_Ctl);
		/* रुको 12GBUSCLK (typ. 60ns @ GBUS200MHz, max 270ns) */
		ndelay(270);
		tx4939ide_ग_लिखोw(sysctl, base, TX4939IDE_Sys_Ctl);
	पूर्ण
	अगर (ctl & (TX4939IDE_INT_ADDRERR |
		   TX4939IDE_INT_DEVTIMING | TX4939IDE_INT_BUSERR))
		pr_err("%s: Error interrupt %#x (%s%s%s )\n",
		       hwअगर->name, ctl,
		       ctl & TX4939IDE_INT_ADDRERR ? " Address-Error" : "",
		       ctl & TX4939IDE_INT_DEVTIMING ? " DEV-Timing" : "",
		       ctl & TX4939IDE_INT_BUSERR ? " Bus-Error" : "");
	वापस ctl;
पूर्ण

अटल व्योम tx4939ide_clear_irq(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर;
	व्योम __iomem *base;
	u16 ctl;

	/*
	 * tx4939ide_dma_test_irq() and tx4939ide_dma_end() करो all job
	 * क्रम DMA हाल.
	 */
	अगर (drive->रुकोing_क्रम_dma)
		वापस;
	hwअगर = drive->hwअगर;
	base = TX4939IDE_BASE(hwअगर);
	ctl = tx4939ide_check_error_पूर्णांकs(hwअगर);
	tx4939ide_ग_लिखोw(ctl, base, TX4939IDE_Int_Ctl);
पूर्ण

अटल u8 tx4939ide_cable_detect(ide_hwअगर_t *hwअगर)
अणु
	व्योम __iomem *base = TX4939IDE_BASE(hwअगर);

	वापस tx4939ide_पढ़ोw(base, TX4939IDE_Sys_Ctl) & 0x2000 ?
		ATA_CBL_PATA40 : ATA_CBL_PATA80;
पूर्ण

#अगर_घोषित __BIG_ENDIAN
अटल व्योम tx4939ide_dma_host_set(ide_drive_t *drive, पूर्णांक on)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 unit = drive->dn;
	व्योम __iomem *base = TX4939IDE_BASE(hwअगर);
	u8 dma_stat = tx4939ide_पढ़ोb(base, TX4939IDE_DMA_Stat);

	अगर (on)
		dma_stat |= (1 << (5 + unit));
	अन्यथा
		dma_stat &= ~(1 << (5 + unit));

	tx4939ide_ग_लिखोb(dma_stat, base, TX4939IDE_DMA_Stat);
पूर्ण
#अन्यथा
#घोषणा tx4939ide_dma_host_set	ide_dma_host_set
#पूर्ण_अगर

अटल u8 tx4939ide_clear_dma_status(व्योम __iomem *base)
अणु
	u8 dma_stat;

	/* पढ़ो DMA status क्रम INTR & ERROR flags */
	dma_stat = tx4939ide_पढ़ोb(base, TX4939IDE_DMA_Stat);
	/* clear INTR & ERROR flags */
	tx4939ide_ग_लिखोb(dma_stat | ATA_DMA_INTR | ATA_DMA_ERR, base,
			 TX4939IDE_DMA_Stat);
	/* recover पूर्णांकmask cleared by writing to bit2 of DMA_Stat */
	tx4939ide_ग_लिखोw(TX4939IDE_IGNORE_INTS << 8, base, TX4939IDE_Int_Ctl);
	वापस dma_stat;
पूर्ण

#अगर_घोषित __BIG_ENDIAN
/* custom ide_build_dmatable to handle swapped layout */
अटल पूर्णांक tx4939ide_build_dmatable(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u32 *table = (u32 *)hwअगर->dmatable_cpu;
	अचिन्हित पूर्णांक count = 0;
	पूर्णांक i;
	काष्ठा scatterlist *sg;

	क्रम_each_sg(hwअगर->sg_table, sg, cmd->sg_nents, i) अणु
		u32 cur_addr, cur_len, bcount;

		cur_addr = sg_dma_address(sg);
		cur_len = sg_dma_len(sg);

		/*
		 * Fill in the DMA table, without crossing any 64kB boundaries.
		 */

		जबतक (cur_len) अणु
			अगर (count++ >= PRD_ENTRIES)
				जाओ use_pio_instead;

			bcount = 0x10000 - (cur_addr & 0xffff);
			अगर (bcount > cur_len)
				bcount = cur_len;
			/*
			 * This workaround क्रम zero count seems required.
			 * (standard ide_build_dmatable करोes it too)
			 */
			अगर (bcount == 0x10000)
				bcount = 0x8000;
			*table++ = bcount & 0xffff;
			*table++ = cur_addr;
			cur_addr += bcount;
			cur_len -= bcount;
		पूर्ण
	पूर्ण

	अगर (count) अणु
		*(table - 2) |= 0x80000000;
		वापस count;
	पूर्ण

use_pio_instead:
	prपूर्णांकk(KERN_ERR "%s: %s\n", drive->name,
		count ? "DMA table too small" : "empty DMA table?");

	वापस 0; /* revert to PIO क्रम this request */
पूर्ण
#अन्यथा
#घोषणा tx4939ide_build_dmatable	ide_build_dmatable
#पूर्ण_अगर

अटल पूर्णांक tx4939ide_dma_setup(ide_drive_t *drive, काष्ठा ide_cmd *cmd)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	व्योम __iomem *base = TX4939IDE_BASE(hwअगर);
	u8 rw = (cmd->tf_flags & IDE_TFLAG_WRITE) ? 0 : ATA_DMA_WR;

	/* fall back to PIO! */
	अगर (tx4939ide_build_dmatable(drive, cmd) == 0)
		वापस 1;

	/* PRD table */
	tx4939ide_ग_लिखोl(hwअगर->dmatable_dma, base, TX4939IDE_PRD_Ptr);

	/* specअगरy r/w */
	tx4939ide_ग_लिखोb(rw, base, TX4939IDE_DMA_Cmd);

	/* clear INTR & ERROR flags */
	tx4939ide_clear_dma_status(base);

	tx4939ide_ग_लिखोw(SECTOR_SIZE / 2, base, drive->dn ?
			 TX4939IDE_Xfer_Cnt_2 : TX4939IDE_Xfer_Cnt_1);

	tx4939ide_ग_लिखोw(blk_rq_sectors(cmd->rq), base, TX4939IDE_Sec_Cnt);

	वापस 0;
पूर्ण

अटल पूर्णांक tx4939ide_dma_end(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	u8 dma_stat, dma_cmd;
	व्योम __iomem *base = TX4939IDE_BASE(hwअगर);
	u16 ctl = tx4939ide_पढ़ोw(base, TX4939IDE_Int_Ctl);

	/* get DMA command mode */
	dma_cmd = tx4939ide_पढ़ोb(base, TX4939IDE_DMA_Cmd);
	/* stop DMA */
	tx4939ide_ग_लिखोb(dma_cmd & ~ATA_DMA_START, base, TX4939IDE_DMA_Cmd);

	/* पढ़ो and clear the INTR & ERROR bits */
	dma_stat = tx4939ide_clear_dma_status(base);

#घोषणा CHECK_DMA_MASK (ATA_DMA_ACTIVE | ATA_DMA_ERR | ATA_DMA_INTR)

	/* verअगरy good DMA status */
	अगर ((dma_stat & CHECK_DMA_MASK) == 0 &&
	    (ctl & (TX4939IDE_INT_XFEREND | TX4939IDE_INT_HOST)) ==
	    (TX4939IDE_INT_XFEREND | TX4939IDE_INT_HOST))
		/* INT_IDE lost... bug? */
		वापस 0;
	वापस ((dma_stat & CHECK_DMA_MASK) !=
		ATA_DMA_INTR) ? 0x10 | dma_stat : 0;
पूर्ण

/* वापसs 1 अगर DMA IRQ issued, 0 otherwise */
अटल पूर्णांक tx4939ide_dma_test_irq(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	व्योम __iomem *base = TX4939IDE_BASE(hwअगर);
	u16 ctl, ide_पूर्णांक;
	u8 dma_stat, stat;
	पूर्णांक found = 0;

	ctl = tx4939ide_check_error_पूर्णांकs(hwअगर);
	ide_पूर्णांक = ctl & (TX4939IDE_INT_XFEREND | TX4939IDE_INT_HOST);
	चयन (ide_पूर्णांक) अणु
	हाल TX4939IDE_INT_HOST:
		/* On error, XFEREND might not be निश्चितed. */
		stat = tx4939ide_पढ़ोb(base, TX4939IDE_AltStat_DevCtl);
		अगर ((stat & (ATA_BUSY | ATA_DRQ | ATA_ERR)) == ATA_ERR)
			found = 1;
		अन्यथा
			/* Wait क्रम XFEREND (Mask HOST and unmask XFEREND) */
			ctl &= ~TX4939IDE_INT_XFEREND << 8;
		ctl |= ide_पूर्णांक << 8;
		अवरोध;
	हाल TX4939IDE_INT_HOST | TX4939IDE_INT_XFEREND:
		dma_stat = tx4939ide_पढ़ोb(base, TX4939IDE_DMA_Stat);
		अगर (!(dma_stat & ATA_DMA_INTR))
			pr_warn("%s: weird interrupt status. "
				"DMA_Stat %#02x int_ctl %#04x\n",
				hwअगर->name, dma_stat, ctl);
		found = 1;
		अवरोध;
	पूर्ण
	/*
	 * Do not clear XFEREND, HOST now.  They will be cleared by
	 * clearing bit2 of DMA_Stat.
	 */
	ctl &= ~ide_पूर्णांक;
	tx4939ide_ग_लिखोw(ctl, base, TX4939IDE_Int_Ctl);
	वापस found;
पूर्ण

#अगर_घोषित __BIG_ENDIAN
अटल u8 tx4939ide_dma_sff_पढ़ो_status(ide_hwअगर_t *hwअगर)
अणु
	व्योम __iomem *base = TX4939IDE_BASE(hwअगर);

	वापस tx4939ide_पढ़ोb(base, TX4939IDE_DMA_Stat);
पूर्ण
#अन्यथा
#घोषणा tx4939ide_dma_sff_पढ़ो_status ide_dma_sff_पढ़ो_status
#पूर्ण_अगर

अटल व्योम tx4939ide_init_hwअगर(ide_hwअगर_t *hwअगर)
अणु
	व्योम __iomem *base = TX4939IDE_BASE(hwअगर);

	/* Soft Reset */
	tx4939ide_ग_लिखोw(0x8000, base, TX4939IDE_Sys_Ctl);
	/* at least 20 GBUSCLK (typ. 100ns @ GBUS200MHz, max 450ns) */
	ndelay(450);
	tx4939ide_ग_लिखोw(0x0000, base, TX4939IDE_Sys_Ctl);
	/* mask some पूर्णांकerrupts and clear all पूर्णांकerrupts */
	tx4939ide_ग_लिखोw((TX4939IDE_IGNORE_INTS << 8) | 0xff, base,
			 TX4939IDE_Int_Ctl);

	tx4939ide_ग_लिखोw(0x0008, base, TX4939IDE_Lo_Burst_Cnt);
	tx4939ide_ग_लिखोw(0, base, TX4939IDE_Up_Burst_Cnt);
पूर्ण

अटल पूर्णांक tx4939ide_init_dma(ide_hwअगर_t *hwअगर, स्थिर काष्ठा ide_port_info *d)
अणु
	hwअगर->dma_base =
		hwअगर->extra_base + tx4939ide_swizzleb(TX4939IDE_DMA_Cmd);
	/*
	 * Note that we cannot use ATA_DMA_TABLE_OFS, ATA_DMA_STATUS
	 * क्रम big endian.
	 */
	वापस ide_allocate_dma_engine(hwअगर);
पूर्ण

अटल व्योम tx4939ide_tf_load_fixup(ide_drive_t *drive)
अणु
	ide_hwअगर_t *hwअगर = drive->hwअगर;
	व्योम __iomem *base = TX4939IDE_BASE(hwअगर);
	u16 sysctl = hwअगर->select_data >> (drive->dn ? 16 : 0);

	/*
	 * Fix ATA100 CORE System Control Register. (The ग_लिखो to the
	 * Device/Head रेजिस्टर may ग_लिखो wrong data to the System
	 * Control Register)
	 * While Sys_Ctl is written here, dev_select() is not needed.
	 */
	tx4939ide_ग_लिखोw(sysctl, base, TX4939IDE_Sys_Ctl);
पूर्ण

अटल व्योम tx4939ide_tf_load(ide_drive_t *drive, काष्ठा ide_taskfile *tf,
			      u8 valid)
अणु
	ide_tf_load(drive, tf, valid);

	अगर (valid & IDE_VALID_DEVICE)
		tx4939ide_tf_load_fixup(drive);
पूर्ण

#अगर_घोषित __BIG_ENDIAN

/* custom iops (independent from SWAP_IO_SPACE) */
अटल व्योम tx4939ide_input_data_swap(ide_drive_t *drive, काष्ठा ide_cmd *cmd,
				व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ port = drive->hwअगर->io_ports.data_addr;
	अचिन्हित लघु *ptr = buf;
	अचिन्हित पूर्णांक count = (len + 1) / 2;

	जबतक (count--)
		*ptr++ = cpu_to_le16(__raw_पढ़ोw((व्योम __iomem *)port));
	__ide_flush_dcache_range((अचिन्हित दीर्घ)buf, roundup(len, 2));
पूर्ण

अटल व्योम tx4939ide_output_data_swap(ide_drive_t *drive, काष्ठा ide_cmd *cmd,
				व्योम *buf, अचिन्हित पूर्णांक len)
अणु
	अचिन्हित दीर्घ port = drive->hwअगर->io_ports.data_addr;
	अचिन्हित लघु *ptr = buf;
	अचिन्हित पूर्णांक count = (len + 1) / 2;

	जबतक (count--) अणु
		__raw_ग_लिखोw(le16_to_cpu(*ptr), (व्योम __iomem *)port);
		ptr++;
	पूर्ण
	__ide_flush_dcache_range((अचिन्हित दीर्घ)buf, roundup(len, 2));
पूर्ण

अटल स्थिर काष्ठा ide_tp_ops tx4939ide_tp_ops = अणु
	.exec_command		= ide_exec_command,
	.पढ़ो_status		= ide_पढ़ो_status,
	.पढ़ो_altstatus		= ide_पढ़ो_altstatus,
	.ग_लिखो_devctl		= ide_ग_लिखो_devctl,

	.dev_select		= ide_dev_select,
	.tf_load		= tx4939ide_tf_load,
	.tf_पढ़ो		= ide_tf_पढ़ो,

	.input_data		= tx4939ide_input_data_swap,
	.output_data		= tx4939ide_output_data_swap,
पूर्ण;

#अन्यथा	/* __LITTLE_ENDIAN */

अटल स्थिर काष्ठा ide_tp_ops tx4939ide_tp_ops = अणु
	.exec_command		= ide_exec_command,
	.पढ़ो_status		= ide_पढ़ो_status,
	.पढ़ो_altstatus		= ide_पढ़ो_altstatus,
	.ग_लिखो_devctl		= ide_ग_लिखो_devctl,

	.dev_select		= ide_dev_select,
	.tf_load		= tx4939ide_tf_load,
	.tf_पढ़ो		= ide_tf_पढ़ो,

	.input_data		= ide_input_data,
	.output_data		= ide_output_data,
पूर्ण;

#पूर्ण_अगर	/* __LITTLE_ENDIAN */

अटल स्थिर काष्ठा ide_port_ops tx4939ide_port_ops = अणु
	.set_pio_mode		= tx4939ide_set_pio_mode,
	.set_dma_mode		= tx4939ide_set_dma_mode,
	.clear_irq		= tx4939ide_clear_irq,
	.cable_detect		= tx4939ide_cable_detect,
पूर्ण;

अटल स्थिर काष्ठा ide_dma_ops tx4939ide_dma_ops = अणु
	.dma_host_set		= tx4939ide_dma_host_set,
	.dma_setup		= tx4939ide_dma_setup,
	.dma_start		= ide_dma_start,
	.dma_end		= tx4939ide_dma_end,
	.dma_test_irq		= tx4939ide_dma_test_irq,
	.dma_lost_irq		= ide_dma_lost_irq,
	.dma_समयr_expiry	= ide_dma_sff_समयr_expiry,
	.dma_sff_पढ़ो_status	= tx4939ide_dma_sff_पढ़ो_status,
पूर्ण;

अटल स्थिर काष्ठा ide_port_info tx4939ide_port_info __initस्थिर = अणु
	.init_hwअगर		= tx4939ide_init_hwअगर,
	.init_dma		= tx4939ide_init_dma,
	.port_ops		= &tx4939ide_port_ops,
	.dma_ops		= &tx4939ide_dma_ops,
	.tp_ops			= &tx4939ide_tp_ops,
	.host_flags		= IDE_HFLAG_MMIO,
	.pio_mask		= ATA_PIO4,
	.mwdma_mask		= ATA_MWDMA2,
	.udma_mask		= ATA_UDMA5,
	.chipset		= ide_generic,
पूर्ण;

अटल पूर्णांक __init tx4939ide_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ide_hw hw, *hws[] = अणु &hw पूर्ण;
	काष्ठा ide_host *host;
	काष्ठा resource *res;
	पूर्णांक irq, ret;
	अचिन्हित दीर्घ mapbase;

	irq = platक्रमm_get_irq(pdev, 0);
	अगर (irq < 0)
		वापस -ENODEV;
	res = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	अगर (!res)
		वापस -ENODEV;

	अगर (!devm_request_mem_region(&pdev->dev, res->start,
				     resource_size(res), MODNAME))
		वापस -EBUSY;
	mapbase = (अचिन्हित दीर्घ)devm_ioremap(&pdev->dev, res->start,
					      resource_size(res));
	अगर (!mapbase)
		वापस -EBUSY;
	स_रखो(&hw, 0, माप(hw));
	hw.io_ports.data_addr =
		mapbase + tx4939ide_swizzlew(TX4939IDE_Data);
	hw.io_ports.error_addr =
		mapbase + tx4939ide_swizzleb(TX4939IDE_Error_Feature);
	hw.io_ports.nsect_addr =
		mapbase + tx4939ide_swizzleb(TX4939IDE_Sec);
	hw.io_ports.lbal_addr =
		mapbase + tx4939ide_swizzleb(TX4939IDE_LBA0);
	hw.io_ports.lbam_addr =
		mapbase + tx4939ide_swizzleb(TX4939IDE_LBA1);
	hw.io_ports.lbah_addr =
		mapbase + tx4939ide_swizzleb(TX4939IDE_LBA2);
	hw.io_ports.device_addr =
		mapbase + tx4939ide_swizzleb(TX4939IDE_DevHead);
	hw.io_ports.command_addr =
		mapbase + tx4939ide_swizzleb(TX4939IDE_Stat_Cmd);
	hw.io_ports.ctl_addr =
		mapbase + tx4939ide_swizzleb(TX4939IDE_AltStat_DevCtl);
	hw.irq = irq;
	hw.dev = &pdev->dev;

	pr_info("TX4939 IDE interface (base %#lx, irq %d)\n", mapbase, irq);
	host = ide_host_alloc(&tx4939ide_port_info, hws, 1);
	अगर (!host)
		वापस -ENOMEM;
	/* use extra_base क्रम base address of the all रेजिस्टरs */
	host->ports[0]->extra_base = mapbase;
	ret = ide_host_रेजिस्टर(host, &tx4939ide_port_info, hws);
	अगर (ret) अणु
		ide_host_मुक्त(host);
		वापस ret;
	पूर्ण
	platक्रमm_set_drvdata(pdev, host);
	वापस 0;
पूर्ण

अटल पूर्णांक __निकास tx4939ide_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ide_host *host = platक्रमm_get_drvdata(pdev);

	ide_host_हटाओ(host);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक tx4939ide_resume(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा ide_host *host = platक्रमm_get_drvdata(dev);
	ide_hwअगर_t *hwअगर = host->ports[0];

	tx4939ide_init_hwअगर(hwअगर);
	वापस 0;
पूर्ण
#अन्यथा
#घोषणा tx4939ide_resume	शून्य
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver tx4939ide_driver = अणु
	.driver = अणु
		.name = MODNAME,
	पूर्ण,
	.हटाओ = __निकास_p(tx4939ide_हटाओ),
	.resume = tx4939ide_resume,
पूर्ण;

module_platक्रमm_driver_probe(tx4939ide_driver, tx4939ide_probe);

MODULE_DESCRIPTION("TX4939 internal IDE driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:tx4939ide");
