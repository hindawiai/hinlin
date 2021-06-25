<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम the SWIM3 (Super Woz Integrated Machine 3)
 * floppy controller found on Power Macपूर्णांकoshes.
 *
 * Copyright (C) 1996 Paul Mackerras.
 */

/*
 * TODO:
 * handle 2 drives
 * handle GCR disks
 */

#अघोषित DEBUG

#समावेश <linux/मानकघोष.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/समयr.h>
#समावेश <linux/delay.h>
#समावेश <linux/fd.h>
#समावेश <linux/ioctl.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/mutex.h>
#समावेश <linux/module.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/रुको.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dbdma.h>
#समावेश <यंत्र/prom.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/mediabay.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/pmac_feature.h>

#घोषणा MAX_FLOPPIES	2

अटल DEFINE_MUTEX(swim3_mutex);
अटल काष्ठा gendisk *disks[MAX_FLOPPIES];

क्रमागत swim_state अणु
	idle,
	locating,
	seeking,
	settling,
	करो_transfer,
	jogging,
	available,
	revalidating,
	ejecting
पूर्ण;

#घोषणा REG(x)	अचिन्हित अक्षर x; अक्षर x ## _pad[15];

/*
 * The names क्रम these रेजिस्टरs mostly represent speculation on my part.
 * It will be पूर्णांकeresting to see how बंद they are to the names Apple uses.
 */
काष्ठा swim3 अणु
	REG(data);
	REG(समयr);		/* counts करोwn at 1MHz */
	REG(error);
	REG(mode);
	REG(select);		/* controls CA0, CA1, CA2 and LSTRB संकेतs */
	REG(setup);
	REG(control);		/* writing bits clears them */
	REG(status);		/* writing bits sets them in control */
	REG(पूर्णांकr);
	REG(nseek);		/* # tracks to seek */
	REG(ctrack);		/* current track number */
	REG(csect);		/* current sector number */
	REG(gap3);		/* size of gap 3 in track क्रमmat */
	REG(sector);		/* sector # to पढ़ो or ग_लिखो */
	REG(nsect);		/* # sectors to पढ़ो or ग_लिखो */
	REG(पूर्णांकr_enable);
पूर्ण;

#घोषणा control_bic	control
#घोषणा control_bis	status

/* Bits in select रेजिस्टर */
#घोषणा CA_MASK		7
#घोषणा LSTRB		8

/* Bits in control रेजिस्टर */
#घोषणा DO_SEEK		0x80
#घोषणा FORMAT		0x40
#घोषणा SELECT		0x20
#घोषणा WRITE_SECTORS	0x10
#घोषणा DO_ACTION	0x08
#घोषणा DRIVE2_ENABLE	0x04
#घोषणा DRIVE_ENABLE	0x02
#घोषणा INTR_ENABLE	0x01

/* Bits in status रेजिस्टर */
#घोषणा FIFO_1BYTE	0x80
#घोषणा FIFO_2BYTE	0x40
#घोषणा ERROR		0x20
#घोषणा DATA		0x08
#घोषणा RDDATA		0x04
#घोषणा INTR_PENDING	0x02
#घोषणा MARK_BYTE	0x01

/* Bits in पूर्णांकr and पूर्णांकr_enable रेजिस्टरs */
#घोषणा ERROR_INTR	0x20
#घोषणा DATA_CHANGED	0x10
#घोषणा TRANSFER_DONE	0x08
#घोषणा SEEN_SECTOR	0x04
#घोषणा SEEK_DONE	0x02
#घोषणा TIMER_DONE	0x01

/* Bits in error रेजिस्टर */
#घोषणा ERR_DATA_CRC	0x80
#घोषणा ERR_ADDR_CRC	0x40
#घोषणा ERR_OVERRUN	0x04
#घोषणा ERR_UNDERRUN	0x01

/* Bits in setup रेजिस्टर */
#घोषणा S_SW_RESET	0x80
#घोषणा S_GCR_WRITE	0x40
#घोषणा S_IBM_DRIVE	0x20
#घोषणा S_TEST_MODE	0x10
#घोषणा S_FCLK_DIV2	0x08
#घोषणा S_GCR		0x04
#घोषणा S_COPY_PROT	0x02
#घोषणा S_INV_WDATA	0x01

/* Select values क्रम swim3_action */
#घोषणा SEEK_POSITIVE	0
#घोषणा SEEK_NEGATIVE	4
#घोषणा STEP		1
#घोषणा MOTOR_ON	2
#घोषणा MOTOR_OFF	6
#घोषणा INDEX		3
#घोषणा EJECT		7
#घोषणा SETMFM		9
#घोषणा SETGCR		13

/* Select values क्रम swim3_select and swim3_पढ़ोbit */
#घोषणा STEP_सूची	0
#घोषणा STEPPING	1
#घोषणा MOTOR_ON	2
#घोषणा RELAX		3	/* also eject in progress */
#घोषणा READ_DATA_0	4
#घोषणा ONEMEG_DRIVE	5
#घोषणा SINGLE_SIDED	6	/* drive or diskette is 4MB type? */
#घोषणा DRIVE_PRESENT	7
#घोषणा DISK_IN		8
#घोषणा WRITE_PROT	9
#घोषणा TRACK_ZERO	10
#घोषणा TACHO		11
#घोषणा READ_DATA_1	12
#घोषणा GCR_MODE	13
#घोषणा SEEK_COMPLETE	14
#घोषणा TWOMEG_MEDIA	15

/* Definitions of values used in writing and क्रमmatting */
#घोषणा DATA_ESCAPE	0x99
#घोषणा GCR_SYNC_EXC	0x3f
#घोषणा GCR_SYNC_CONV	0x80
#घोषणा GCR_FIRST_MARK	0xd5
#घोषणा GCR_SECOND_MARK	0xaa
#घोषणा GCR_ADDR_MARK	"\xd5\xaa\x00"
#घोषणा GCR_DATA_MARK	"\xd5\xaa\x0b"
#घोषणा GCR_SLIP_BYTE	"\x27\xaa"
#घोषणा GCR_SELF_SYNC	"\x3f\xbf\x1e\x34\x3c\x3f"

#घोषणा DATA_99		"\x99\x99"
#घोषणा MFM_ADDR_MARK	"\x99\xa1\x99\xa1\x99\xa1\x99\xfe"
#घोषणा MFM_INDEX_MARK	"\x99\xc2\x99\xc2\x99\xc2\x99\xfc"
#घोषणा MFM_GAP_LEN	12

काष्ठा floppy_state अणु
	क्रमागत swim_state	state;
	काष्ठा swim3 __iomem *swim3;	/* hardware रेजिस्टरs */
	काष्ठा dbdma_regs __iomem *dma;	/* DMA controller रेजिस्टरs */
	पूर्णांक	swim3_पूर्णांकr;	/* पूर्णांकerrupt number क्रम SWIM3 */
	पूर्णांक	dma_पूर्णांकr;	/* पूर्णांकerrupt number क्रम DMA channel */
	पूर्णांक	cur_cyl;	/* cylinder head is on, or -1 */
	पूर्णांक	cur_sector;	/* last sector we saw go past */
	पूर्णांक	req_cyl;	/* the cylinder क्रम the current r/w request */
	पूर्णांक	head;		/* head number ditto */
	पूर्णांक	req_sector;	/* sector number ditto */
	पूर्णांक	scount;		/* # sectors we're transferring at present */
	पूर्णांक	retries;
	पूर्णांक	settle_समय;
	पूर्णांक	secpercyl;	/* disk geometry inक्रमmation */
	पूर्णांक	secpertrack;
	पूर्णांक	total_secs;
	पूर्णांक	ग_लिखो_prot;	/* 1 अगर ग_लिखो-रक्षित, 0 अगर not, -1 dunno */
	काष्ठा dbdma_cmd *dma_cmd;
	पूर्णांक	ref_count;
	पूर्णांक	expect_cyl;
	काष्ठा समयr_list समयout;
	पूर्णांक	समयout_pending;
	पूर्णांक	ejected;
	रुको_queue_head_t रुको;
	पूर्णांक	wanted;
	काष्ठा macio_dev *mdev;
	अक्षर	dbdma_cmd_space[5 * माप(काष्ठा dbdma_cmd)];
	पूर्णांक	index;
	काष्ठा request *cur_req;
	काष्ठा blk_mq_tag_set tag_set;
पूर्ण;

#घोषणा swim3_err(fmt, arg...)	dev_err(&fs->mdev->ofdev.dev, "[fd%d] " fmt, fs->index, arg)
#घोषणा swim3_warn(fmt, arg...)	dev_warn(&fs->mdev->ofdev.dev, "[fd%d] " fmt, fs->index, arg)
#घोषणा swim3_info(fmt, arg...)	dev_info(&fs->mdev->ofdev.dev, "[fd%d] " fmt, fs->index, arg)

#अगर_घोषित DEBUG
#घोषणा swim3_dbg(fmt, arg...)	dev_dbg(&fs->mdev->ofdev.dev, "[fd%d] " fmt, fs->index, arg)
#अन्यथा
#घोषणा swim3_dbg(fmt, arg...)	करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल काष्ठा floppy_state floppy_states[MAX_FLOPPIES];
अटल पूर्णांक floppy_count = 0;
अटल DEFINE_SPINLOCK(swim3_lock);

अटल अचिन्हित लघु ग_लिखो_preamble[] = अणु
	0x4e4e, 0x4e4e, 0x4e4e, 0x4e4e, 0x4e4e,	/* gap field */
	0, 0, 0, 0, 0, 0,			/* sync field */
	0x99a1, 0x99a1, 0x99a1, 0x99fb,		/* data address mark */
	0x990f					/* no escape क्रम 512 bytes */
पूर्ण;

अटल अचिन्हित लघु ग_लिखो_postamble[] = अणु
	0x9904,					/* insert CRC */
	0x4e4e, 0x4e4e,
	0x9908,					/* stop writing */
	0, 0, 0, 0, 0, 0
पूर्ण;

अटल व्योम seek_track(काष्ठा floppy_state *fs, पूर्णांक n);
अटल व्योम act(काष्ठा floppy_state *fs);
अटल व्योम scan_समयout(काष्ठा समयr_list *t);
अटल व्योम seek_समयout(काष्ठा समयr_list *t);
अटल व्योम settle_समयout(काष्ठा समयr_list *t);
अटल व्योम xfer_समयout(काष्ठा समयr_list *t);
अटल irqवापस_t swim3_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);
/*अटल व्योम fd_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id);*/
अटल पूर्णांक grab_drive(काष्ठा floppy_state *fs, क्रमागत swim_state state,
		      पूर्णांक पूर्णांकerruptible);
अटल व्योम release_drive(काष्ठा floppy_state *fs);
अटल पूर्णांक fd_eject(काष्ठा floppy_state *fs);
अटल पूर्णांक floppy_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ param);
अटल पूर्णांक floppy_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode);
अटल व्योम floppy_release(काष्ठा gendisk *disk, भ_शेषe_t mode);
अटल अचिन्हित पूर्णांक floppy_check_events(काष्ठा gendisk *disk,
					अचिन्हित पूर्णांक clearing);
अटल पूर्णांक floppy_revalidate(काष्ठा gendisk *disk);

अटल bool swim3_end_request(काष्ठा floppy_state *fs, blk_status_t err, अचिन्हित पूर्णांक nr_bytes)
अणु
	काष्ठा request *req = fs->cur_req;

	swim3_dbg("  end request, err=%d nr_bytes=%d, cur_req=%p\n",
		  err, nr_bytes, req);

	अगर (err)
		nr_bytes = blk_rq_cur_bytes(req);
	अगर (blk_update_request(req, err, nr_bytes))
		वापस true;
	__blk_mq_end_request(req, err);
	fs->cur_req = शून्य;
	वापस false;
पूर्ण

अटल व्योम swim3_select(काष्ठा floppy_state *fs, पूर्णांक sel)
अणु
	काष्ठा swim3 __iomem *sw = fs->swim3;

	out_8(&sw->select, RELAX);
	अगर (sel & 8)
		out_8(&sw->control_bis, SELECT);
	अन्यथा
		out_8(&sw->control_bic, SELECT);
	out_8(&sw->select, sel & CA_MASK);
पूर्ण

अटल व्योम swim3_action(काष्ठा floppy_state *fs, पूर्णांक action)
अणु
	काष्ठा swim3 __iomem *sw = fs->swim3;

	swim3_select(fs, action);
	udelay(1);
	out_8(&sw->select, sw->select | LSTRB);
	udelay(2);
	out_8(&sw->select, sw->select & ~LSTRB);
	udelay(1);
पूर्ण

अटल पूर्णांक swim3_पढ़ोbit(काष्ठा floppy_state *fs, पूर्णांक bit)
अणु
	काष्ठा swim3 __iomem *sw = fs->swim3;
	पूर्णांक stat;

	swim3_select(fs, bit);
	udelay(1);
	stat = in_8(&sw->status);
	वापस (stat & DATA) == 0;
पूर्ण

अटल blk_status_t swim3_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				   स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा floppy_state *fs = hctx->queue->queuedata;
	काष्ठा request *req = bd->rq;
	अचिन्हित दीर्घ x;

	spin_lock_irq(&swim3_lock);
	अगर (fs->cur_req || fs->state != idle) अणु
		spin_unlock_irq(&swim3_lock);
		वापस BLK_STS_DEV_RESOURCE;
	पूर्ण
	blk_mq_start_request(req);
	fs->cur_req = req;
	अगर (fs->mdev->media_bay &&
	    check_media_bay(fs->mdev->media_bay) != MB_FD) अणु
		swim3_dbg("%s", "  media bay absent, dropping req\n");
		swim3_end_request(fs, BLK_STS_IOERR, 0);
		जाओ out;
	पूर्ण
	अगर (fs->ejected) अणु
		swim3_dbg("%s", "  disk ejected\n");
		swim3_end_request(fs, BLK_STS_IOERR, 0);
		जाओ out;
	पूर्ण
	अगर (rq_data_dir(req) == WRITE) अणु
		अगर (fs->ग_लिखो_prot < 0)
			fs->ग_लिखो_prot = swim3_पढ़ोbit(fs, WRITE_PROT);
		अगर (fs->ग_लिखो_prot) अणु
			swim3_dbg("%s", "  try to write, disk write protected\n");
			swim3_end_request(fs, BLK_STS_IOERR, 0);
			जाओ out;
		पूर्ण
	पूर्ण

	/*
	 * Do not हटाओ the cast. blk_rq_pos(req) is now a sector_t and can be
	 * 64 bits, but it will never go past 32 bits क्रम this driver anyway, so
	 * we can safely cast it करोwn and not have to करो a 64/32 भागision
	 */
	fs->req_cyl = ((दीर्घ)blk_rq_pos(req)) / fs->secpercyl;
	x = ((दीर्घ)blk_rq_pos(req)) % fs->secpercyl;
	fs->head = x / fs->secpertrack;
	fs->req_sector = x % fs->secpertrack + 1;
	fs->state = करो_transfer;
	fs->retries = 0;

	act(fs);

out:
	spin_unlock_irq(&swim3_lock);
	वापस BLK_STS_OK;
पूर्ण

अटल व्योम set_समयout(काष्ठा floppy_state *fs, पूर्णांक nticks,
			व्योम (*proc)(काष्ठा समयr_list *t))
अणु
	अगर (fs->समयout_pending)
		del_समयr(&fs->समयout);
	fs->समयout.expires = jअगरfies + nticks;
	fs->समयout.function = proc;
	add_समयr(&fs->समयout);
	fs->समयout_pending = 1;
पूर्ण

अटल अंतरभूत व्योम scan_track(काष्ठा floppy_state *fs)
अणु
	काष्ठा swim3 __iomem *sw = fs->swim3;

	swim3_select(fs, READ_DATA_0);
	in_8(&sw->पूर्णांकr);		/* clear SEEN_SECTOR bit */
	in_8(&sw->error);
	out_8(&sw->पूर्णांकr_enable, SEEN_SECTOR);
	out_8(&sw->control_bis, DO_ACTION);
	/* enable पूर्णांकr when track found */
	set_समयout(fs, HZ, scan_समयout);	/* enable समयout */
पूर्ण

अटल अंतरभूत व्योम seek_track(काष्ठा floppy_state *fs, पूर्णांक n)
अणु
	काष्ठा swim3 __iomem *sw = fs->swim3;

	अगर (n >= 0) अणु
		swim3_action(fs, SEEK_POSITIVE);
		sw->nseek = n;
	पूर्ण अन्यथा अणु
		swim3_action(fs, SEEK_NEGATIVE);
		sw->nseek = -n;
	पूर्ण
	fs->expect_cyl = (fs->cur_cyl >= 0)? fs->cur_cyl + n: -1;
	swim3_select(fs, STEP);
	in_8(&sw->error);
	/* enable पूर्णांकr when seek finished */
	out_8(&sw->पूर्णांकr_enable, SEEK_DONE);
	out_8(&sw->control_bis, DO_SEEK);
	set_समयout(fs, 3*HZ, seek_समयout);	/* enable समयout */
	fs->settle_समय = 0;
पूर्ण

/*
 * XXX: this is a horrible hack, but at least allows ppc32 to get
 * out of defining virt_to_bus, and this driver out of using the
 * deprecated block layer bounce buffering क्रम highmem addresses
 * क्रम no good reason.
 */
अटल अचिन्हित दीर्घ swim3_phys_to_bus(phys_addr_t paddr)
अणु
	वापस paddr + PCI_DRAM_OFFSET;
पूर्ण

अटल phys_addr_t swim3_bio_phys(काष्ठा bio *bio)
अणु
	वापस page_to_phys(bio_page(bio)) + bio_offset(bio);
पूर्ण

अटल अंतरभूत व्योम init_dma(काष्ठा dbdma_cmd *cp, पूर्णांक cmd,
			    phys_addr_t paddr, पूर्णांक count)
अणु
	cp->req_count = cpu_to_le16(count);
	cp->command = cpu_to_le16(cmd);
	cp->phy_addr = cpu_to_le32(swim3_phys_to_bus(paddr));
	cp->xfer_status = 0;
पूर्ण

अटल अंतरभूत व्योम setup_transfer(काष्ठा floppy_state *fs)
अणु
	पूर्णांक n;
	काष्ठा swim3 __iomem *sw = fs->swim3;
	काष्ठा dbdma_cmd *cp = fs->dma_cmd;
	काष्ठा dbdma_regs __iomem *dr = fs->dma;
	काष्ठा request *req = fs->cur_req;

	अगर (blk_rq_cur_sectors(req) <= 0) अणु
		swim3_warn("%s", "Transfer 0 sectors ?\n");
		वापस;
	पूर्ण
	अगर (rq_data_dir(req) == WRITE)
		n = 1;
	अन्यथा अणु
		n = fs->secpertrack - fs->req_sector + 1;
		अगर (n > blk_rq_cur_sectors(req))
			n = blk_rq_cur_sectors(req);
	पूर्ण

	swim3_dbg("  setup xfer at sect %d (of %d) head %d for %d\n",
		  fs->req_sector, fs->secpertrack, fs->head, n);

	fs->scount = n;
	swim3_select(fs, fs->head? READ_DATA_1: READ_DATA_0);
	out_8(&sw->sector, fs->req_sector);
	out_8(&sw->nsect, n);
	out_8(&sw->gap3, 0);
	out_le32(&dr->cmdptr, swim3_phys_to_bus(virt_to_phys(cp)));
	अगर (rq_data_dir(req) == WRITE) अणु
		/* Set up 3 dma commands: ग_लिखो preamble, data, postamble */
		init_dma(cp, OUTPUT_MORE, virt_to_phys(ग_लिखो_preamble),
			 माप(ग_लिखो_preamble));
		++cp;
		init_dma(cp, OUTPUT_MORE, swim3_bio_phys(req->bio), 512);
		++cp;
		init_dma(cp, OUTPUT_LAST, virt_to_phys(ग_लिखो_postamble),
			माप(ग_लिखो_postamble));
	पूर्ण अन्यथा अणु
		init_dma(cp, INPUT_LAST, swim3_bio_phys(req->bio), n * 512);
	पूर्ण
	++cp;
	out_le16(&cp->command, DBDMA_STOP);
	out_8(&sw->control_bic, DO_ACTION | WRITE_SECTORS);
	in_8(&sw->error);
	out_8(&sw->control_bic, DO_ACTION | WRITE_SECTORS);
	अगर (rq_data_dir(req) == WRITE)
		out_8(&sw->control_bis, WRITE_SECTORS);
	in_8(&sw->पूर्णांकr);
	out_le32(&dr->control, (RUN << 16) | RUN);
	/* enable पूर्णांकr when transfer complete */
	out_8(&sw->पूर्णांकr_enable, TRANSFER_DONE);
	out_8(&sw->control_bis, DO_ACTION);
	set_समयout(fs, 2*HZ, xfer_समयout);	/* enable समयout */
पूर्ण

अटल व्योम act(काष्ठा floppy_state *fs)
अणु
	क्रम (;;) अणु
		swim3_dbg("  act loop, state=%d, req_cyl=%d, cur_cyl=%d\n",
			  fs->state, fs->req_cyl, fs->cur_cyl);

		चयन (fs->state) अणु
		हाल idle:
			वापस;		/* XXX shouldn't get here */

		हाल locating:
			अगर (swim3_पढ़ोbit(fs, TRACK_ZERO)) अणु
				swim3_dbg("%s", "    locate track 0\n");
				fs->cur_cyl = 0;
				अगर (fs->req_cyl == 0)
					fs->state = करो_transfer;
				अन्यथा
					fs->state = seeking;
				अवरोध;
			पूर्ण
			scan_track(fs);
			वापस;

		हाल seeking:
			अगर (fs->cur_cyl < 0) अणु
				fs->expect_cyl = -1;
				fs->state = locating;
				अवरोध;
			पूर्ण
			अगर (fs->req_cyl == fs->cur_cyl) अणु
				swim3_warn("%s", "Whoops, seeking 0\n");
				fs->state = करो_transfer;
				अवरोध;
			पूर्ण
			seek_track(fs, fs->req_cyl - fs->cur_cyl);
			वापस;

		हाल settling:
			/* check क्रम SEEK_COMPLETE after 30ms */
			fs->settle_समय = (HZ + 32) / 33;
			set_समयout(fs, fs->settle_समय, settle_समयout);
			वापस;

		हाल करो_transfer:
			अगर (fs->cur_cyl != fs->req_cyl) अणु
				अगर (fs->retries > 5) अणु
					swim3_err("Wrong cylinder in transfer, want: %d got %d\n",
						  fs->req_cyl, fs->cur_cyl);
					swim3_end_request(fs, BLK_STS_IOERR, 0);
					fs->state = idle;
					वापस;
				पूर्ण
				fs->state = seeking;
				अवरोध;
			पूर्ण
			setup_transfer(fs);
			वापस;

		हाल jogging:
			seek_track(fs, -5);
			वापस;

		शेष:
			swim3_err("Unknown state %d\n", fs->state);
			वापस;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम scan_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा floppy_state *fs = from_समयr(fs, t, समयout);
	काष्ठा swim3 __iomem *sw = fs->swim3;
	अचिन्हित दीर्घ flags;

	swim3_dbg("* scan timeout, state=%d\n", fs->state);

	spin_lock_irqsave(&swim3_lock, flags);
	fs->समयout_pending = 0;
	out_8(&sw->control_bic, DO_ACTION | WRITE_SECTORS);
	out_8(&sw->select, RELAX);
	out_8(&sw->पूर्णांकr_enable, 0);
	fs->cur_cyl = -1;
	अगर (fs->retries > 5) अणु
		swim3_end_request(fs, BLK_STS_IOERR, 0);
		fs->state = idle;
	पूर्ण अन्यथा अणु
		fs->state = jogging;
		act(fs);
	पूर्ण
	spin_unlock_irqrestore(&swim3_lock, flags);
पूर्ण

अटल व्योम seek_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा floppy_state *fs = from_समयr(fs, t, समयout);
	काष्ठा swim3 __iomem *sw = fs->swim3;
	अचिन्हित दीर्घ flags;

	swim3_dbg("* seek timeout, state=%d\n", fs->state);

	spin_lock_irqsave(&swim3_lock, flags);
	fs->समयout_pending = 0;
	out_8(&sw->control_bic, DO_SEEK);
	out_8(&sw->select, RELAX);
	out_8(&sw->पूर्णांकr_enable, 0);
	swim3_err("%s", "Seek timeout\n");
	swim3_end_request(fs, BLK_STS_IOERR, 0);
	fs->state = idle;
	spin_unlock_irqrestore(&swim3_lock, flags);
पूर्ण

अटल व्योम settle_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा floppy_state *fs = from_समयr(fs, t, समयout);
	काष्ठा swim3 __iomem *sw = fs->swim3;
	अचिन्हित दीर्घ flags;

	swim3_dbg("* settle timeout, state=%d\n", fs->state);

	spin_lock_irqsave(&swim3_lock, flags);
	fs->समयout_pending = 0;
	अगर (swim3_पढ़ोbit(fs, SEEK_COMPLETE)) अणु
		out_8(&sw->select, RELAX);
		fs->state = locating;
		act(fs);
		जाओ unlock;
	पूर्ण
	out_8(&sw->select, RELAX);
	अगर (fs->settle_समय < 2*HZ) अणु
		++fs->settle_समय;
		set_समयout(fs, 1, settle_समयout);
		जाओ unlock;
	पूर्ण
	swim3_err("%s", "Seek settle timeout\n");
	swim3_end_request(fs, BLK_STS_IOERR, 0);
	fs->state = idle;
 unlock:
	spin_unlock_irqrestore(&swim3_lock, flags);
पूर्ण

अटल व्योम xfer_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा floppy_state *fs = from_समयr(fs, t, समयout);
	काष्ठा swim3 __iomem *sw = fs->swim3;
	काष्ठा dbdma_regs __iomem *dr = fs->dma;
	अचिन्हित दीर्घ flags;
	पूर्णांक n;

	swim3_dbg("* xfer timeout, state=%d\n", fs->state);

	spin_lock_irqsave(&swim3_lock, flags);
	fs->समयout_pending = 0;
	out_le32(&dr->control, RUN << 16);
	/* We must रुको a bit क्रम dbdma to stop */
	क्रम (n = 0; (in_le32(&dr->status) & ACTIVE) && n < 1000; n++)
		udelay(1);
	out_8(&sw->पूर्णांकr_enable, 0);
	out_8(&sw->control_bic, WRITE_SECTORS | DO_ACTION);
	out_8(&sw->select, RELAX);
	swim3_err("Timeout %sing sector %ld\n",
	       (rq_data_dir(fs->cur_req)==WRITE? "writ": "read"),
	       (दीर्घ)blk_rq_pos(fs->cur_req));
	swim3_end_request(fs, BLK_STS_IOERR, 0);
	fs->state = idle;
	spin_unlock_irqrestore(&swim3_lock, flags);
पूर्ण

अटल irqवापस_t swim3_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा floppy_state *fs = (काष्ठा floppy_state *) dev_id;
	काष्ठा swim3 __iomem *sw = fs->swim3;
	पूर्णांक पूर्णांकr, err, n;
	पूर्णांक stat, resid;
	काष्ठा dbdma_regs __iomem *dr;
	काष्ठा dbdma_cmd *cp;
	अचिन्हित दीर्घ flags;
	काष्ठा request *req = fs->cur_req;

	swim3_dbg("* interrupt, state=%d\n", fs->state);

	spin_lock_irqsave(&swim3_lock, flags);
	पूर्णांकr = in_8(&sw->पूर्णांकr);
	err = (पूर्णांकr & ERROR_INTR)? in_8(&sw->error): 0;
	अगर ((पूर्णांकr & ERROR_INTR) && fs->state != करो_transfer)
		swim3_err("Non-transfer error interrupt: state=%d, dir=%x, intr=%x, err=%x\n",
			  fs->state, rq_data_dir(req), पूर्णांकr, err);
	चयन (fs->state) अणु
	हाल locating:
		अगर (पूर्णांकr & SEEN_SECTOR) अणु
			out_8(&sw->control_bic, DO_ACTION | WRITE_SECTORS);
			out_8(&sw->select, RELAX);
			out_8(&sw->पूर्णांकr_enable, 0);
			del_समयr(&fs->समयout);
			fs->समयout_pending = 0;
			अगर (sw->ctrack == 0xff) अणु
				swim3_err("%s", "Seen sector but cyl=ff?\n");
				fs->cur_cyl = -1;
				अगर (fs->retries > 5) अणु
					swim3_end_request(fs, BLK_STS_IOERR, 0);
					fs->state = idle;
				पूर्ण अन्यथा अणु
					fs->state = jogging;
					act(fs);
				पूर्ण
				अवरोध;
			पूर्ण
			fs->cur_cyl = sw->ctrack;
			fs->cur_sector = sw->csect;
			अगर (fs->expect_cyl != -1 && fs->expect_cyl != fs->cur_cyl)
				swim3_err("Expected cyl %d, got %d\n",
					  fs->expect_cyl, fs->cur_cyl);
			fs->state = करो_transfer;
			act(fs);
		पूर्ण
		अवरोध;
	हाल seeking:
	हाल jogging:
		अगर (sw->nseek == 0) अणु
			out_8(&sw->control_bic, DO_SEEK);
			out_8(&sw->select, RELAX);
			out_8(&sw->पूर्णांकr_enable, 0);
			del_समयr(&fs->समयout);
			fs->समयout_pending = 0;
			अगर (fs->state == seeking)
				++fs->retries;
			fs->state = settling;
			act(fs);
		पूर्ण
		अवरोध;
	हाल settling:
		out_8(&sw->पूर्णांकr_enable, 0);
		del_समयr(&fs->समयout);
		fs->समयout_pending = 0;
		act(fs);
		अवरोध;
	हाल करो_transfer:
		अगर ((पूर्णांकr & (ERROR_INTR | TRANSFER_DONE)) == 0)
			अवरोध;
		out_8(&sw->पूर्णांकr_enable, 0);
		out_8(&sw->control_bic, WRITE_SECTORS | DO_ACTION);
		out_8(&sw->select, RELAX);
		del_समयr(&fs->समयout);
		fs->समयout_pending = 0;
		dr = fs->dma;
		cp = fs->dma_cmd;
		अगर (rq_data_dir(req) == WRITE)
			++cp;
		/*
		 * Check that the मुख्य data transfer has finished.
		 * On writing, the swim3 someबार करोesn't use
		 * up all the bytes of the postamble, so we can still
		 * see DMA active here.  That करोesn't matter as दीर्घ
		 * as all the sector data has been transferred.
		 */
		अगर ((पूर्णांकr & ERROR_INTR) == 0 && cp->xfer_status == 0) अणु
			/* रुको a little जबतक क्रम DMA to complete */
			क्रम (n = 0; n < 100; ++n) अणु
				अगर (cp->xfer_status != 0)
					अवरोध;
				udelay(1);
				barrier();
			पूर्ण
		पूर्ण
		/* turn off DMA */
		out_le32(&dr->control, (RUN | PAUSE) << 16);
		stat = le16_to_cpu(cp->xfer_status);
		resid = le16_to_cpu(cp->res_count);
		अगर (पूर्णांकr & ERROR_INTR) अणु
			n = fs->scount - 1 - resid / 512;
			अगर (n > 0) अणु
				blk_update_request(req, 0, n << 9);
				fs->req_sector += n;
			पूर्ण
			अगर (fs->retries < 5) अणु
				++fs->retries;
				act(fs);
			पूर्ण अन्यथा अणु
				swim3_err("Error %sing block %ld (err=%x)\n",
				       rq_data_dir(req) == WRITE? "writ": "read",
				       (दीर्घ)blk_rq_pos(req), err);
				swim3_end_request(fs, BLK_STS_IOERR, 0);
				fs->state = idle;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर ((stat & ACTIVE) == 0 || resid != 0) अणु
				/* musta been an error */
				swim3_err("fd dma error: stat=%x resid=%d\n", stat, resid);
				swim3_err("  state=%d, dir=%x, intr=%x, err=%x\n",
					  fs->state, rq_data_dir(req), पूर्णांकr, err);
				swim3_end_request(fs, BLK_STS_IOERR, 0);
				fs->state = idle;
				अवरोध;
			पूर्ण
			fs->retries = 0;
			अगर (swim3_end_request(fs, 0, fs->scount << 9)) अणु
				fs->req_sector += fs->scount;
				अगर (fs->req_sector > fs->secpertrack) अणु
					fs->req_sector -= fs->secpertrack;
					अगर (++fs->head > 1) अणु
						fs->head = 0;
						++fs->req_cyl;
					पूर्ण
				पूर्ण
				act(fs);
			पूर्ण अन्यथा
				fs->state = idle;
		पूर्ण
		अवरोध;
	शेष:
		swim3_err("Don't know what to do in state %d\n", fs->state);
	पूर्ण
	spin_unlock_irqrestore(&swim3_lock, flags);
	वापस IRQ_HANDLED;
पूर्ण

/*
अटल व्योम fd_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
पूर्ण
*/

/* Called under the mutex to grab exclusive access to a drive */
अटल पूर्णांक grab_drive(काष्ठा floppy_state *fs, क्रमागत swim_state state,
		      पूर्णांक पूर्णांकerruptible)
अणु
	अचिन्हित दीर्घ flags;

	swim3_dbg("%s", "-> grab drive\n");

	spin_lock_irqsave(&swim3_lock, flags);
	अगर (fs->state != idle && fs->state != available) अणु
		++fs->wanted;
		/* this will enable irqs in order to sleep */
		अगर (!पूर्णांकerruptible)
			रुको_event_lock_irq(fs->रुको,
                                        fs->state == available,
                                        swim3_lock);
		अन्यथा अगर (रुको_event_पूर्णांकerruptible_lock_irq(fs->रुको,
					fs->state == available,
					swim3_lock)) अणु
			--fs->wanted;
			spin_unlock_irqrestore(&swim3_lock, flags);
			वापस -EINTR;
		पूर्ण
		--fs->wanted;
	पूर्ण
	fs->state = state;
	spin_unlock_irqrestore(&swim3_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम release_drive(काष्ठा floppy_state *fs)
अणु
	काष्ठा request_queue *q = disks[fs->index]->queue;
	अचिन्हित दीर्घ flags;

	swim3_dbg("%s", "-> release drive\n");

	spin_lock_irqsave(&swim3_lock, flags);
	fs->state = idle;
	spin_unlock_irqrestore(&swim3_lock, flags);

	blk_mq_मुक्तze_queue(q);
	blk_mq_quiesce_queue(q);
	blk_mq_unquiesce_queue(q);
	blk_mq_unमुक्तze_queue(q);
पूर्ण

अटल पूर्णांक fd_eject(काष्ठा floppy_state *fs)
अणु
	पूर्णांक err, n;

	err = grab_drive(fs, ejecting, 1);
	अगर (err)
		वापस err;
	swim3_action(fs, EJECT);
	क्रम (n = 20; n > 0; --n) अणु
		अगर (संकेत_pending(current)) अणु
			err = -EINTR;
			अवरोध;
		पूर्ण
		swim3_select(fs, RELAX);
		schedule_समयout_पूर्णांकerruptible(1);
		अगर (swim3_पढ़ोbit(fs, DISK_IN) == 0)
			अवरोध;
	पूर्ण
	swim3_select(fs, RELAX);
	udelay(150);
	fs->ejected = 1;
	release_drive(fs);
	वापस err;
पूर्ण

अटल काष्ठा floppy_काष्ठा floppy_type =
	अणु 2880,18,2,80,0,0x1B,0x00,0xCF,0x6C,शून्य पूर्ण;	/*  7 1.44MB 3.5"   */

अटल पूर्णांक floppy_locked_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ param)
अणु
	काष्ठा floppy_state *fs = bdev->bd_disk->निजी_data;
	पूर्णांक err;
		
	अगर ((cmd & 0x80) && !capable(CAP_SYS_ADMIN))
		वापस -EPERM;

	अगर (fs->mdev->media_bay &&
	    check_media_bay(fs->mdev->media_bay) != MB_FD)
		वापस -ENXIO;

	चयन (cmd) अणु
	हाल FDEJECT:
		अगर (fs->ref_count != 1)
			वापस -EBUSY;
		err = fd_eject(fs);
		वापस err;
	हाल FDGETPRM:
	        अगर (copy_to_user((व्योम __user *) param, &floppy_type,
				 माप(काष्ठा floppy_काष्ठा)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक floppy_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
				 अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ param)
अणु
	पूर्णांक ret;

	mutex_lock(&swim3_mutex);
	ret = floppy_locked_ioctl(bdev, mode, cmd, param);
	mutex_unlock(&swim3_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक floppy_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा floppy_state *fs = bdev->bd_disk->निजी_data;
	काष्ठा swim3 __iomem *sw = fs->swim3;
	पूर्णांक n, err = 0;

	अगर (fs->ref_count == 0) अणु
		अगर (fs->mdev->media_bay &&
		    check_media_bay(fs->mdev->media_bay) != MB_FD)
			वापस -ENXIO;
		out_8(&sw->setup, S_IBM_DRIVE | S_FCLK_DIV2);
		out_8(&sw->control_bic, 0xff);
		out_8(&sw->mode, 0x95);
		udelay(10);
		out_8(&sw->पूर्णांकr_enable, 0);
		out_8(&sw->control_bis, DRIVE_ENABLE | INTR_ENABLE);
		swim3_action(fs, MOTOR_ON);
		fs->ग_लिखो_prot = -1;
		fs->cur_cyl = -1;
		क्रम (n = 0; n < 2 * HZ; ++n) अणु
			अगर (n >= HZ/30 && swim3_पढ़ोbit(fs, SEEK_COMPLETE))
				अवरोध;
			अगर (संकेत_pending(current)) अणु
				err = -EINTR;
				अवरोध;
			पूर्ण
			swim3_select(fs, RELAX);
			schedule_समयout_पूर्णांकerruptible(1);
		पूर्ण
		अगर (err == 0 && (swim3_पढ़ोbit(fs, SEEK_COMPLETE) == 0
				 || swim3_पढ़ोbit(fs, DISK_IN) == 0))
			err = -ENXIO;
		swim3_action(fs, SETMFM);
		swim3_select(fs, RELAX);

	पूर्ण अन्यथा अगर (fs->ref_count == -1 || mode & FMODE_EXCL)
		वापस -EBUSY;

	अगर (err == 0 && (mode & FMODE_NDELAY) == 0
	    && (mode & (FMODE_READ|FMODE_WRITE))) अणु
		अगर (bdev_check_media_change(bdev))
			floppy_revalidate(bdev->bd_disk);
		अगर (fs->ejected)
			err = -ENXIO;
	पूर्ण

	अगर (err == 0 && (mode & FMODE_WRITE)) अणु
		अगर (fs->ग_लिखो_prot < 0)
			fs->ग_लिखो_prot = swim3_पढ़ोbit(fs, WRITE_PROT);
		अगर (fs->ग_लिखो_prot)
			err = -EROFS;
	पूर्ण

	अगर (err) अणु
		अगर (fs->ref_count == 0) अणु
			swim3_action(fs, MOTOR_OFF);
			out_8(&sw->control_bic, DRIVE_ENABLE | INTR_ENABLE);
			swim3_select(fs, RELAX);
		पूर्ण
		वापस err;
	पूर्ण

	अगर (mode & FMODE_EXCL)
		fs->ref_count = -1;
	अन्यथा
		++fs->ref_count;

	वापस 0;
पूर्ण

अटल पूर्णांक floppy_unlocked_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	पूर्णांक ret;

	mutex_lock(&swim3_mutex);
	ret = floppy_खोलो(bdev, mode);
	mutex_unlock(&swim3_mutex);

	वापस ret;
पूर्ण

अटल व्योम floppy_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा floppy_state *fs = disk->निजी_data;
	काष्ठा swim3 __iomem *sw = fs->swim3;

	mutex_lock(&swim3_mutex);
	अगर (fs->ref_count > 0)
		--fs->ref_count;
	अन्यथा अगर (fs->ref_count == -1)
		fs->ref_count = 0;
	अगर (fs->ref_count == 0) अणु
		swim3_action(fs, MOTOR_OFF);
		out_8(&sw->control_bic, 0xff);
		swim3_select(fs, RELAX);
	पूर्ण
	mutex_unlock(&swim3_mutex);
पूर्ण

अटल अचिन्हित पूर्णांक floppy_check_events(काष्ठा gendisk *disk,
					अचिन्हित पूर्णांक clearing)
अणु
	काष्ठा floppy_state *fs = disk->निजी_data;
	वापस fs->ejected ? DISK_EVENT_MEDIA_CHANGE : 0;
पूर्ण

अटल पूर्णांक floppy_revalidate(काष्ठा gendisk *disk)
अणु
	काष्ठा floppy_state *fs = disk->निजी_data;
	काष्ठा swim3 __iomem *sw;
	पूर्णांक ret, n;

	अगर (fs->mdev->media_bay &&
	    check_media_bay(fs->mdev->media_bay) != MB_FD)
		वापस -ENXIO;

	sw = fs->swim3;
	grab_drive(fs, revalidating, 0);
	out_8(&sw->पूर्णांकr_enable, 0);
	out_8(&sw->control_bis, DRIVE_ENABLE);
	swim3_action(fs, MOTOR_ON);	/* necessary? */
	fs->ग_लिखो_prot = -1;
	fs->cur_cyl = -1;
	mdelay(1);
	क्रम (n = HZ; n > 0; --n) अणु
		अगर (swim3_पढ़ोbit(fs, SEEK_COMPLETE))
			अवरोध;
		अगर (संकेत_pending(current))
			अवरोध;
		swim3_select(fs, RELAX);
		schedule_समयout_पूर्णांकerruptible(1);
	पूर्ण
	ret = swim3_पढ़ोbit(fs, SEEK_COMPLETE) == 0
		|| swim3_पढ़ोbit(fs, DISK_IN) == 0;
	अगर (ret)
		swim3_action(fs, MOTOR_OFF);
	अन्यथा अणु
		fs->ejected = 0;
		swim3_action(fs, SETMFM);
	पूर्ण
	swim3_select(fs, RELAX);

	release_drive(fs);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा block_device_operations floppy_fops = अणु
	.खोलो		= floppy_unlocked_खोलो,
	.release	= floppy_release,
	.ioctl		= floppy_ioctl,
	.check_events	= floppy_check_events,
पूर्ण;

अटल स्थिर काष्ठा blk_mq_ops swim3_mq_ops = अणु
	.queue_rq = swim3_queue_rq,
पूर्ण;

अटल व्योम swim3_mb_event(काष्ठा macio_dev* mdev, पूर्णांक mb_state)
अणु
	काष्ठा floppy_state *fs = macio_get_drvdata(mdev);
	काष्ठा swim3 __iomem *sw;

	अगर (!fs)
		वापस;

	sw = fs->swim3;

	अगर (mb_state != MB_FD)
		वापस;

	/* Clear state */
	out_8(&sw->पूर्णांकr_enable, 0);
	in_8(&sw->पूर्णांकr);
	in_8(&sw->error);
पूर्ण

अटल पूर्णांक swim3_add_device(काष्ठा macio_dev *mdev, पूर्णांक index)
अणु
	काष्ठा device_node *swim = mdev->ofdev.dev.of_node;
	काष्ठा floppy_state *fs = &floppy_states[index];
	पूर्णांक rc = -EBUSY;

	fs->mdev = mdev;
	fs->index = index;

	/* Check & Request resources */
	अगर (macio_resource_count(mdev) < 2) अणु
		swim3_err("%s", "No address in device-tree\n");
		वापस -ENXIO;
	पूर्ण
	अगर (macio_irq_count(mdev) < 1) अणु
		swim3_err("%s", "No interrupt in device-tree\n");
		वापस -ENXIO;
	पूर्ण
	अगर (macio_request_resource(mdev, 0, "swim3 (mmio)")) अणु
		swim3_err("%s", "Can't request mmio resource\n");
		वापस -EBUSY;
	पूर्ण
	अगर (macio_request_resource(mdev, 1, "swim3 (dma)")) अणु
		swim3_err("%s", "Can't request dma resource\n");
		macio_release_resource(mdev, 0);
		वापस -EBUSY;
	पूर्ण
	dev_set_drvdata(&mdev->ofdev.dev, fs);

	अगर (mdev->media_bay == शून्य)
		pmac_call_feature(PMAC_FTR_SWIM3_ENABLE, swim, 0, 1);
	
	fs->state = idle;
	fs->swim3 = (काष्ठा swim3 __iomem *)
		ioremap(macio_resource_start(mdev, 0), 0x200);
	अगर (fs->swim3 == शून्य) अणु
		swim3_err("%s", "Couldn't map mmio registers\n");
		rc = -ENOMEM;
		जाओ out_release;
	पूर्ण
	fs->dma = (काष्ठा dbdma_regs __iomem *)
		ioremap(macio_resource_start(mdev, 1), 0x200);
	अगर (fs->dma == शून्य) अणु
		swim3_err("%s", "Couldn't map dma registers\n");
		iounmap(fs->swim3);
		rc = -ENOMEM;
		जाओ out_release;
	पूर्ण
	fs->swim3_पूर्णांकr = macio_irq(mdev, 0);
	fs->dma_पूर्णांकr = macio_irq(mdev, 1);
	fs->cur_cyl = -1;
	fs->cur_sector = -1;
	fs->secpercyl = 36;
	fs->secpertrack = 18;
	fs->total_secs = 2880;
	init_रुकोqueue_head(&fs->रुको);

	fs->dma_cmd = (काष्ठा dbdma_cmd *) DBDMA_ALIGN(fs->dbdma_cmd_space);
	स_रखो(fs->dma_cmd, 0, 2 * माप(काष्ठा dbdma_cmd));
	fs->dma_cmd[1].command = cpu_to_le16(DBDMA_STOP);

	अगर (mdev->media_bay == शून्य || check_media_bay(mdev->media_bay) == MB_FD)
		swim3_mb_event(mdev, MB_FD);

	अगर (request_irq(fs->swim3_पूर्णांकr, swim3_पूर्णांकerrupt, 0, "SWIM3", fs)) अणु
		swim3_err("%s", "Couldn't request interrupt\n");
		pmac_call_feature(PMAC_FTR_SWIM3_ENABLE, swim, 0, 0);
		जाओ out_unmap;
	पूर्ण

	समयr_setup(&fs->समयout, शून्य, 0);

	swim3_info("SWIM3 floppy controller %s\n",
		mdev->media_bay ? "in media bay" : "");

	वापस 0;

 out_unmap:
	iounmap(fs->dma);
	iounmap(fs->swim3);

 out_release:
	macio_release_resource(mdev, 0);
	macio_release_resource(mdev, 1);

	वापस rc;
पूर्ण

अटल पूर्णांक swim3_attach(काष्ठा macio_dev *mdev,
			स्थिर काष्ठा of_device_id *match)
अणु
	काष्ठा floppy_state *fs;
	काष्ठा gendisk *disk;
	पूर्णांक rc;

	अगर (floppy_count >= MAX_FLOPPIES)
		वापस -ENXIO;

	अगर (floppy_count == 0) अणु
		rc = रेजिस्टर_blkdev(FLOPPY_MAJOR, "fd");
		अगर (rc)
			वापस rc;
	पूर्ण

	disk = alloc_disk(1);
	अगर (disk == शून्य) अणु
		rc = -ENOMEM;
		जाओ out_unरेजिस्टर;
	पूर्ण

	fs = &floppy_states[floppy_count];
	स_रखो(fs, 0, माप(*fs));

	disk->queue = blk_mq_init_sq_queue(&fs->tag_set, &swim3_mq_ops, 2,
						BLK_MQ_F_SHOULD_MERGE);
	अगर (IS_ERR(disk->queue)) अणु
		rc = PTR_ERR(disk->queue);
		disk->queue = शून्य;
		जाओ out_put_disk;
	पूर्ण
	disk->queue->queuedata = fs;

	rc = swim3_add_device(mdev, floppy_count);
	अगर (rc)
		जाओ out_cleanup_queue;

	disk->major = FLOPPY_MAJOR;
	disk->first_minor = floppy_count;
	disk->fops = &floppy_fops;
	disk->निजी_data = fs;
	disk->events = DISK_EVENT_MEDIA_CHANGE;
	disk->flags |= GENHD_FL_REMOVABLE;
	प्र_लिखो(disk->disk_name, "fd%d", floppy_count);
	set_capacity(disk, 2880);
	add_disk(disk);

	disks[floppy_count++] = disk;
	वापस 0;

out_cleanup_queue:
	blk_cleanup_queue(disk->queue);
	disk->queue = शून्य;
	blk_mq_मुक्त_tag_set(&fs->tag_set);
out_put_disk:
	put_disk(disk);
out_unरेजिस्टर:
	अगर (floppy_count == 0)
		unरेजिस्टर_blkdev(FLOPPY_MAJOR, "fd");
	वापस rc;
पूर्ण

अटल स्थिर काष्ठा of_device_id swim3_match[] =
अणु
	अणु
	.name		= "swim3",
	पूर्ण,
	अणु
	.compatible	= "ohare-swim3"
	पूर्ण,
	अणु
	.compatible	= "swim3"
	पूर्ण,
	अणु /* end of list */ पूर्ण
पूर्ण;

अटल काष्ठा macio_driver swim3_driver =
अणु
	.driver = अणु
		.name 		= "swim3",
		.of_match_table	= swim3_match,
	पूर्ण,
	.probe		= swim3_attach,
#अगर_घोषित CONFIG_PMAC_MEDIABAY
	.mediabay_event	= swim3_mb_event,
#पूर्ण_अगर
#अगर 0
	.suspend	= swim3_suspend,
	.resume		= swim3_resume,
#पूर्ण_अगर
पूर्ण;


पूर्णांक swim3_init(व्योम)
अणु
	macio_रेजिस्टर_driver(&swim3_driver);
	वापस 0;
पूर्ण

module_init(swim3_init)

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Paul Mackerras");
MODULE_ALIAS_BLOCKDEV_MAJOR(FLOPPY_MAJOR);
