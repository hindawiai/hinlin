<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Driver क्रम SWIM (Sander Woz Integrated Machine) floppy controller
 *
 * Copyright (C) 2004,2008 Laurent Vivier <Laurent@lvivier.info>
 *
 * based on Alastair Bridgewater SWIM analysis, 2001
 * based on SWIM3 driver (c) Paul Mackerras, 1996
 * based on netBSD IWM driver (c) 1997, 1998 Hauke Fath.
 *
 * 2004-08-21 (lv) - Initial implementation
 * 2008-10-30 (lv) - Port to 2.6
 */

#समावेश <linux/module.h>
#समावेश <linux/fd.h>
#समावेश <linux/slab.h>
#समावेश <linux/blk-mq.h>
#समावेश <linux/mutex.h>
#समावेश <linux/hdreg.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/mac_via.h>

#घोषणा CARDNAME "swim"

काष्ठा sector_header अणु
	अचिन्हित अक्षर side;
	अचिन्हित अक्षर track;
	अचिन्हित अक्षर sector;
	अचिन्हित अक्षर size;
	अचिन्हित अक्षर crc0;
	अचिन्हित अक्षर crc1;
पूर्ण __attribute__((packed));

#घोषणा DRIVER_VERSION "Version 0.2 (2008-10-30)"

#घोषणा REG(x)	अचिन्हित अक्षर x, x ## _pad[0x200 - 1];

काष्ठा swim अणु
	REG(ग_लिखो_data)
	REG(ग_लिखो_mark)
	REG(ग_लिखो_CRC)
	REG(ग_लिखो_parameter)
	REG(ग_लिखो_phase)
	REG(ग_लिखो_setup)
	REG(ग_लिखो_mode0)
	REG(ग_लिखो_mode1)

	REG(पढ़ो_data)
	REG(पढ़ो_mark)
	REG(पढ़ो_error)
	REG(पढ़ो_parameter)
	REG(पढ़ो_phase)
	REG(पढ़ो_setup)
	REG(पढ़ो_status)
	REG(पढ़ो_handshake)
पूर्ण __attribute__((packed));

#घोषणा swim_ग_लिखो(base, reg, v) 	out_8(&(base)->ग_लिखो_##reg, (v))
#घोषणा swim_पढ़ो(base, reg)		in_8(&(base)->पढ़ो_##reg)

/* IWM रेजिस्टरs */

काष्ठा iwm अणु
	REG(ph0L)
	REG(ph0H)
	REG(ph1L)
	REG(ph1H)
	REG(ph2L)
	REG(ph2H)
	REG(ph3L)
	REG(ph3H)
	REG(mtrOff)
	REG(mtrOn)
	REG(पूर्णांकDrive)
	REG(extDrive)
	REG(q6L)
	REG(q6H)
	REG(q7L)
	REG(q7H)
पूर्ण __attribute__((packed));

#घोषणा iwm_ग_लिखो(base, reg, v) 	out_8(&(base)->reg, (v))
#घोषणा iwm_पढ़ो(base, reg)		in_8(&(base)->reg)

/* bits in phase रेजिस्टर */

#घोषणा SEEK_POSITIVE	0x070
#घोषणा SEEK_NEGATIVE	0x074
#घोषणा STEP		0x071
#घोषणा MOTOR_ON	0x072
#घोषणा MOTOR_OFF	0x076
#घोषणा INDEX		0x073
#घोषणा EJECT		0x077
#घोषणा SETMFM		0x171
#घोषणा SETGCR		0x175

#घोषणा RELAX		0x033
#घोषणा LSTRB		0x008

#घोषणा CA_MASK		0x077

/* Select values क्रम swim_select and swim_पढ़ोbit */

#घोषणा READ_DATA_0	0x074
#घोषणा ONEMEG_DRIVE	0x075
#घोषणा SINGLE_SIDED	0x076
#घोषणा DRIVE_PRESENT	0x077
#घोषणा DISK_IN		0x170
#घोषणा WRITE_PROT	0x171
#घोषणा TRACK_ZERO	0x172
#घोषणा TACHO		0x173
#घोषणा READ_DATA_1	0x174
#घोषणा GCR_MODE	0x175
#घोषणा SEEK_COMPLETE	0x176
#घोषणा TWOMEG_MEDIA	0x177

/* Bits in handshake रेजिस्टर */

#घोषणा MARK_BYTE	0x01
#घोषणा CRC_ZERO	0x02
#घोषणा RDDATA		0x04
#घोषणा SENSE		0x08
#घोषणा MOTEN		0x10
#घोषणा ERROR		0x20
#घोषणा DAT2BYTE	0x40
#घोषणा DAT1BYTE	0x80

/* bits in setup रेजिस्टर */

#घोषणा S_INV_WDATA	0x01
#घोषणा S_3_5_SELECT	0x02
#घोषणा S_GCR		0x04
#घोषणा S_FCLK_DIV2	0x08
#घोषणा S_ERROR_CORR	0x10
#घोषणा S_IBM_DRIVE	0x20
#घोषणा S_GCR_WRITE	0x40
#घोषणा S_TIMEOUT	0x80

/* bits in mode रेजिस्टर */

#घोषणा CLFIFO		0x01
#घोषणा ENBL1		0x02
#घोषणा ENBL2		0x04
#घोषणा ACTION		0x08
#घोषणा WRITE_MODE	0x10
#घोषणा HEDSEL		0x20
#घोषणा MOTON		0x80

/*----------------------------------------------------------------------------*/

क्रमागत drive_location अणु
	INTERNAL_DRIVE = 0x02,
	EXTERNAL_DRIVE = 0x04,
पूर्ण;

क्रमागत media_type अणु
	DD_MEDIA,
	HD_MEDIA,
पूर्ण;

काष्ठा floppy_state अणु

	/* physical properties */

	क्रमागत drive_location location;	/* पूर्णांकernal or बाह्यal drive */
	पूर्णांक		 head_number;	/* single- or द्विगुन-sided drive */

	/* media */

	पूर्णांक		 disk_in;
	पूर्णांक		 ejected;
	क्रमागत media_type	 type;
	पूर्णांक		 ग_लिखो_रक्षित;

	पूर्णांक		 total_secs;
	पूर्णांक		 secpercyl;
	पूर्णांक		 secpertrack;

	/* in-use inक्रमmation */

	पूर्णांक		track;
	पूर्णांक		ref_count;

	काष्ठा gendisk *disk;
	काष्ठा blk_mq_tag_set tag_set;

	/* parent controller */

	काष्ठा swim_priv *swd;
पूर्ण;

क्रमागत motor_action अणु
	OFF,
	ON,
पूर्ण;

क्रमागत head अणु
	LOWER_HEAD = 0,
	UPPER_HEAD = 1,
पूर्ण;

#घोषणा FD_MAX_UNIT	2

काष्ठा swim_priv अणु
	काष्ठा swim __iomem *base;
	spinlock_t lock;
	पूर्णांक floppy_count;
	काष्ठा floppy_state unit[FD_MAX_UNIT];
पूर्ण;

बाह्य पूर्णांक swim_पढ़ो_sector_header(काष्ठा swim __iomem *base,
				   काष्ठा sector_header *header);
बाह्य पूर्णांक swim_पढ़ो_sector_data(काष्ठा swim __iomem *base,
				 अचिन्हित अक्षर *data);

अटल DEFINE_MUTEX(swim_mutex);
अटल अंतरभूत व्योम set_swim_mode(काष्ठा swim __iomem *base, पूर्णांक enable)
अणु
	काष्ठा iwm __iomem *iwm_base;
	अचिन्हित दीर्घ flags;

	अगर (!enable) अणु
		swim_ग_लिखो(base, mode0, 0xf8);
		वापस;
	पूर्ण

	iwm_base = (काष्ठा iwm __iomem *)base;
	local_irq_save(flags);

	iwm_पढ़ो(iwm_base, q7L);
	iwm_पढ़ो(iwm_base, mtrOff);
	iwm_पढ़ो(iwm_base, q6H);

	iwm_ग_लिखो(iwm_base, q7H, 0x57);
	iwm_ग_लिखो(iwm_base, q7H, 0x17);
	iwm_ग_लिखो(iwm_base, q7H, 0x57);
	iwm_ग_लिखो(iwm_base, q7H, 0x57);

	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत पूर्णांक get_swim_mode(काष्ठा swim __iomem *base)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	swim_ग_लिखो(base, phase, 0xf5);
	अगर (swim_पढ़ो(base, phase) != 0xf5)
		जाओ is_iwm;
	swim_ग_लिखो(base, phase, 0xf6);
	अगर (swim_पढ़ो(base, phase) != 0xf6)
		जाओ is_iwm;
	swim_ग_लिखो(base, phase, 0xf7);
	अगर (swim_पढ़ो(base, phase) != 0xf7)
		जाओ is_iwm;
	local_irq_restore(flags);
	वापस 1;
is_iwm:
	local_irq_restore(flags);
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम swim_select(काष्ठा swim __iomem *base, पूर्णांक sel)
अणु
	swim_ग_लिखो(base, phase, RELAX);

	via1_set_head(sel & 0x100);

	swim_ग_लिखो(base, phase, sel & CA_MASK);
पूर्ण

अटल अंतरभूत व्योम swim_action(काष्ठा swim __iomem *base, पूर्णांक action)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	swim_select(base, action);
	udelay(1);
	swim_ग_लिखो(base, phase, (LSTRB<<4) | LSTRB);
	udelay(1);
	swim_ग_लिखो(base, phase, (LSTRB<<4) | ((~LSTRB) & 0x0F));
	udelay(1);

	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत पूर्णांक swim_पढ़ोbit(काष्ठा swim __iomem *base, पूर्णांक bit)
अणु
	पूर्णांक stat;

	swim_select(base, bit);

	udelay(10);

	stat = swim_पढ़ो(base, handshake);

	वापस (stat & SENSE) == 0;
पूर्ण

अटल अंतरभूत व्योम swim_drive(काष्ठा swim __iomem *base,
			      क्रमागत drive_location location)
अणु
	अगर (location == INTERNAL_DRIVE) अणु
		swim_ग_लिखो(base, mode0, EXTERNAL_DRIVE); /* clear drive 1 bit */
		swim_ग_लिखो(base, mode1, INTERNAL_DRIVE); /* set drive 0 bit */
	पूर्ण अन्यथा अगर (location == EXTERNAL_DRIVE) अणु
		swim_ग_लिखो(base, mode0, INTERNAL_DRIVE); /* clear drive 0 bit */
		swim_ग_लिखो(base, mode1, EXTERNAL_DRIVE); /* set drive 1 bit */
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम swim_motor(काष्ठा swim __iomem *base,
			      क्रमागत motor_action action)
अणु
	अगर (action == ON) अणु
		पूर्णांक i;

		swim_action(base, MOTOR_ON);

		क्रम (i = 0; i < 2*HZ; i++) अणु
			swim_select(base, RELAX);
			अगर (swim_पढ़ोbit(base, MOTOR_ON))
				अवरोध;
			set_current_state(TASK_INTERRUPTIBLE);
			schedule_समयout(1);
		पूर्ण
	पूर्ण अन्यथा अगर (action == OFF) अणु
		swim_action(base, MOTOR_OFF);
		swim_select(base, RELAX);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम swim_eject(काष्ठा swim __iomem *base)
अणु
	पूर्णांक i;

	swim_action(base, EJECT);

	क्रम (i = 0; i < 2*HZ; i++) अणु
		swim_select(base, RELAX);
		अगर (!swim_पढ़ोbit(base, DISK_IN))
			अवरोध;
		set_current_state(TASK_INTERRUPTIBLE);
		schedule_समयout(1);
	पूर्ण
	swim_select(base, RELAX);
पूर्ण

अटल अंतरभूत व्योम swim_head(काष्ठा swim __iomem *base, क्रमागत head head)
अणु
	/* रुको drive is पढ़ोy */

	अगर (head == UPPER_HEAD)
		swim_select(base, READ_DATA_1);
	अन्यथा अगर (head == LOWER_HEAD)
		swim_select(base, READ_DATA_0);
पूर्ण

अटल अंतरभूत पूर्णांक swim_step(काष्ठा swim __iomem *base)
अणु
	पूर्णांक रुको;

	swim_action(base, STEP);

	क्रम (रुको = 0; रुको < HZ; रुको++) अणु

		set_current_state(TASK_INTERRUPTIBLE);
		schedule_समयout(1);

		swim_select(base, RELAX);
		अगर (!swim_पढ़ोbit(base, STEP))
			वापस 0;
	पूर्ण
	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक swim_track00(काष्ठा swim __iomem *base)
अणु
	पूर्णांक try;

	swim_action(base, SEEK_NEGATIVE);

	क्रम (try = 0; try < 100; try++) अणु

		swim_select(base, RELAX);
		अगर (swim_पढ़ोbit(base, TRACK_ZERO))
			अवरोध;

		अगर (swim_step(base))
			वापस -1;
	पूर्ण

	अगर (swim_पढ़ोbit(base, TRACK_ZERO))
		वापस 0;

	वापस -1;
पूर्ण

अटल अंतरभूत पूर्णांक swim_seek(काष्ठा swim __iomem *base, पूर्णांक step)
अणु
	अगर (step == 0)
		वापस 0;

	अगर (step < 0) अणु
		swim_action(base, SEEK_NEGATIVE);
		step = -step;
	पूर्ण अन्यथा
		swim_action(base, SEEK_POSITIVE);

	क्रम ( ; step > 0; step--) अणु
		अगर (swim_step(base))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक swim_track(काष्ठा floppy_state *fs,  पूर्णांक track)
अणु
	काष्ठा swim __iomem *base = fs->swd->base;
	पूर्णांक ret;

	ret = swim_seek(base, track - fs->track);

	अगर (ret == 0)
		fs->track = track;
	अन्यथा अणु
		swim_track00(base);
		fs->track = 0;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक floppy_eject(काष्ठा floppy_state *fs)
अणु
	काष्ठा swim __iomem *base = fs->swd->base;

	swim_drive(base, fs->location);
	swim_motor(base, OFF);
	swim_eject(base);

	fs->disk_in = 0;
	fs->ejected = 1;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक swim_पढ़ो_sector(काष्ठा floppy_state *fs,
				   पूर्णांक side, पूर्णांक track,
				   पूर्णांक sector, अचिन्हित अक्षर *buffer)
अणु
	काष्ठा swim __iomem *base = fs->swd->base;
	अचिन्हित दीर्घ flags;
	काष्ठा sector_header header;
	पूर्णांक ret = -1;
	लघु i;

	swim_track(fs, track);

	swim_ग_लिखो(base, mode1, MOTON);
	swim_head(base, side);
	swim_ग_लिखो(base, mode0, side);

	local_irq_save(flags);
	क्रम (i = 0; i < 36; i++) अणु
		ret = swim_पढ़ो_sector_header(base, &header);
		अगर (!ret && (header.sector == sector)) अणु
			/* found */

			ret = swim_पढ़ो_sector_data(base, buffer);
			अवरोध;
		पूर्ण
	पूर्ण
	local_irq_restore(flags);

	swim_ग_लिखो(base, mode0, MOTON);

	अगर ((header.side != side)  || (header.track != track) ||
	     (header.sector != sector))
		वापस 0;

	वापस ret;
पूर्ण

अटल blk_status_t floppy_पढ़ो_sectors(काष्ठा floppy_state *fs,
			       पूर्णांक req_sector, पूर्णांक sectors_nb,
			       अचिन्हित अक्षर *buffer)
अणु
	काष्ठा swim __iomem *base = fs->swd->base;
	पूर्णांक ret;
	पूर्णांक side, track, sector;
	पूर्णांक i, try;


	swim_drive(base, fs->location);
	क्रम (i = req_sector; i < req_sector + sectors_nb; i++) अणु
		पूर्णांक x;
		track = i / fs->secpercyl;
		x = i % fs->secpercyl;
		side = x / fs->secpertrack;
		sector = x % fs->secpertrack + 1;

		try = 5;
		करो अणु
			ret = swim_पढ़ो_sector(fs, side, track, sector,
						buffer);
			अगर (try-- == 0)
				वापस BLK_STS_IOERR;
		पूर्ण जबतक (ret != 512);

		buffer += ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल blk_status_t swim_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				  स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	काष्ठा floppy_state *fs = hctx->queue->queuedata;
	काष्ठा swim_priv *swd = fs->swd;
	काष्ठा request *req = bd->rq;
	blk_status_t err;

	अगर (!spin_trylock_irq(&swd->lock))
		वापस BLK_STS_DEV_RESOURCE;

	blk_mq_start_request(req);

	अगर (!fs->disk_in || rq_data_dir(req) == WRITE) अणु
		err = BLK_STS_IOERR;
		जाओ out;
	पूर्ण

	करो अणु
		err = floppy_पढ़ो_sectors(fs, blk_rq_pos(req),
					  blk_rq_cur_sectors(req),
					  bio_data(req->bio));
	पूर्ण जबतक (blk_update_request(req, err, blk_rq_cur_bytes(req)));
	__blk_mq_end_request(req, err);

	err = BLK_STS_OK;
out:
	spin_unlock_irq(&swd->lock);
	वापस err;

पूर्ण

अटल काष्ठा floppy_काष्ठा floppy_type[4] = अणु
	अणु    0,  0, 0,  0, 0, 0x00, 0x00, 0x00, 0x00, शून्य पूर्ण, /* no testing   */
	अणु  720,  9, 1, 80, 0, 0x2A, 0x02, 0xDF, 0x50, शून्य पूर्ण, /* 360KB SS 3.5"*/
	अणु 1440,  9, 2, 80, 0, 0x2A, 0x02, 0xDF, 0x50, शून्य पूर्ण, /* 720KB 3.5"   */
	अणु 2880, 18, 2, 80, 0, 0x1B, 0x00, 0xCF, 0x6C, शून्य पूर्ण, /* 1.44MB 3.5"  */
पूर्ण;

अटल पूर्णांक get_floppy_geometry(काष्ठा floppy_state *fs, पूर्णांक type,
			       काष्ठा floppy_काष्ठा **g)
अणु
	अगर (type >= ARRAY_SIZE(floppy_type))
		वापस -EINVAL;

	अगर (type)
		*g = &floppy_type[type];
	अन्यथा अगर (fs->type == HD_MEDIA) /* High-Density media */
		*g = &floppy_type[3];
	अन्यथा अगर (fs->head_number == 2) /* द्विगुन-sided */
		*g = &floppy_type[2];
	अन्यथा
		*g = &floppy_type[1];

	वापस 0;
पूर्ण

अटल व्योम setup_medium(काष्ठा floppy_state *fs)
अणु
	काष्ठा swim __iomem *base = fs->swd->base;

	अगर (swim_पढ़ोbit(base, DISK_IN)) अणु
		काष्ठा floppy_काष्ठा *g;
		fs->disk_in = 1;
		fs->ग_लिखो_रक्षित = swim_पढ़ोbit(base, WRITE_PROT);

		अगर (swim_track00(base))
			prपूर्णांकk(KERN_ERR
				"SWIM: cannot move floppy head to track 0\n");

		swim_track00(base);

		fs->type = swim_पढ़ोbit(base, TWOMEG_MEDIA) ?
			HD_MEDIA : DD_MEDIA;
		fs->head_number = swim_पढ़ोbit(base, SINGLE_SIDED) ? 1 : 2;
		get_floppy_geometry(fs, 0, &g);
		fs->total_secs = g->size;
		fs->secpercyl = g->head * g->sect;
		fs->secpertrack = g->sect;
		fs->track = 0;
	पूर्ण अन्यथा अणु
		fs->disk_in = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक floppy_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	काष्ठा floppy_state *fs = bdev->bd_disk->निजी_data;
	काष्ठा swim __iomem *base = fs->swd->base;
	पूर्णांक err;

	अगर (fs->ref_count == -1 || (fs->ref_count && mode & FMODE_EXCL))
		वापस -EBUSY;

	अगर (mode & FMODE_EXCL)
		fs->ref_count = -1;
	अन्यथा
		fs->ref_count++;

	swim_ग_लिखो(base, setup, S_IBM_DRIVE  | S_FCLK_DIV2);
	udelay(10);
	swim_drive(base, fs->location);
	swim_motor(base, ON);
	swim_action(base, SETMFM);
	अगर (fs->ejected)
		setup_medium(fs);
	अगर (!fs->disk_in) अणु
		err = -ENXIO;
		जाओ out;
	पूर्ण

	set_capacity(fs->disk, fs->total_secs);

	अगर (mode & FMODE_NDELAY)
		वापस 0;

	अगर (mode & (FMODE_READ|FMODE_WRITE)) अणु
		अगर (bdev_check_media_change(bdev) && fs->disk_in)
			fs->ejected = 0;
		अगर ((mode & FMODE_WRITE) && fs->ग_लिखो_रक्षित) अणु
			err = -EROFS;
			जाओ out;
		पूर्ण
	पूर्ण
	वापस 0;
out:
	अगर (fs->ref_count < 0)
		fs->ref_count = 0;
	अन्यथा अगर (fs->ref_count > 0)
		--fs->ref_count;

	अगर (fs->ref_count == 0)
		swim_motor(base, OFF);
	वापस err;
पूर्ण

अटल पूर्णांक floppy_unlocked_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	पूर्णांक ret;

	mutex_lock(&swim_mutex);
	ret = floppy_खोलो(bdev, mode);
	mutex_unlock(&swim_mutex);

	वापस ret;
पूर्ण

अटल व्योम floppy_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	काष्ठा floppy_state *fs = disk->निजी_data;
	काष्ठा swim __iomem *base = fs->swd->base;

	mutex_lock(&swim_mutex);
	अगर (fs->ref_count < 0)
		fs->ref_count = 0;
	अन्यथा अगर (fs->ref_count > 0)
		--fs->ref_count;

	अगर (fs->ref_count == 0)
		swim_motor(base, OFF);
	mutex_unlock(&swim_mutex);
पूर्ण

अटल पूर्णांक floppy_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
			अचिन्हित पूर्णांक cmd, अचिन्हित दीर्घ param)
अणु
	काष्ठा floppy_state *fs = bdev->bd_disk->निजी_data;
	पूर्णांक err;

	अगर ((cmd & 0x80) && !capable(CAP_SYS_ADMIN))
			वापस -EPERM;

	चयन (cmd) अणु
	हाल FDEJECT:
		अगर (fs->ref_count != 1)
			वापस -EBUSY;
		mutex_lock(&swim_mutex);
		err = floppy_eject(fs);
		mutex_unlock(&swim_mutex);
		वापस err;

	हाल FDGETPRM:
		अगर (copy_to_user((व्योम __user *) param, (व्योम *) &floppy_type,
				 माप(काष्ठा floppy_काष्ठा)))
			वापस -EFAULT;
		वापस 0;
	पूर्ण
	वापस -ENOTTY;
पूर्ण

अटल पूर्णांक floppy_getgeo(काष्ठा block_device *bdev, काष्ठा hd_geometry *geo)
अणु
	काष्ठा floppy_state *fs = bdev->bd_disk->निजी_data;
	काष्ठा floppy_काष्ठा *g;
	पूर्णांक ret;

	ret = get_floppy_geometry(fs, 0, &g);
	अगर (ret)
		वापस ret;

	geo->heads = g->head;
	geo->sectors = g->sect;
	geo->cylinders = g->track;

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक floppy_check_events(काष्ठा gendisk *disk,
					अचिन्हित पूर्णांक clearing)
अणु
	काष्ठा floppy_state *fs = disk->निजी_data;

	वापस fs->ejected ? DISK_EVENT_MEDIA_CHANGE : 0;
पूर्ण

अटल स्थिर काष्ठा block_device_operations floppy_fops = अणु
	.owner		 = THIS_MODULE,
	.खोलो		 = floppy_unlocked_खोलो,
	.release	 = floppy_release,
	.ioctl		 = floppy_ioctl,
	.getgeo		 = floppy_getgeo,
	.check_events	 = floppy_check_events,
पूर्ण;

अटल पूर्णांक swim_add_floppy(काष्ठा swim_priv *swd, क्रमागत drive_location location)
अणु
	काष्ठा floppy_state *fs = &swd->unit[swd->floppy_count];
	काष्ठा swim __iomem *base = swd->base;

	fs->location = location;

	swim_drive(base, location);

	swim_motor(base, OFF);

	fs->type = HD_MEDIA;
	fs->head_number = 2;

	fs->ref_count = 0;
	fs->ejected = 1;

	swd->floppy_count++;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops swim_mq_ops = अणु
	.queue_rq = swim_queue_rq,
पूर्ण;

अटल पूर्णांक swim_floppy_init(काष्ठा swim_priv *swd)
अणु
	पूर्णांक err;
	पूर्णांक drive;
	काष्ठा swim __iomem *base = swd->base;

	/* scan floppy drives */

	swim_drive(base, INTERNAL_DRIVE);
	अगर (swim_पढ़ोbit(base, DRIVE_PRESENT) &&
	    !swim_पढ़ोbit(base, ONEMEG_DRIVE))
		swim_add_floppy(swd, INTERNAL_DRIVE);
	swim_drive(base, EXTERNAL_DRIVE);
	अगर (swim_पढ़ोbit(base, DRIVE_PRESENT) &&
	    !swim_पढ़ोbit(base, ONEMEG_DRIVE))
		swim_add_floppy(swd, EXTERNAL_DRIVE);

	/* रेजिस्टर floppy drives */

	err = रेजिस्टर_blkdev(FLOPPY_MAJOR, "fd");
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "Unable to get major %d for SWIM floppy\n",
		       FLOPPY_MAJOR);
		वापस -EBUSY;
	पूर्ण

	spin_lock_init(&swd->lock);

	क्रम (drive = 0; drive < swd->floppy_count; drive++) अणु
		काष्ठा request_queue *q;

		swd->unit[drive].disk = alloc_disk(1);
		अगर (swd->unit[drive].disk == शून्य) अणु
			err = -ENOMEM;
			जाओ निकास_put_disks;
		पूर्ण

		q = blk_mq_init_sq_queue(&swd->unit[drive].tag_set, &swim_mq_ops,
						2, BLK_MQ_F_SHOULD_MERGE);
		अगर (IS_ERR(q)) अणु
			err = PTR_ERR(q);
			जाओ निकास_put_disks;
		पूर्ण

		swd->unit[drive].disk->queue = q;
		swd->unit[drive].disk->queue->queuedata = &swd->unit[drive];
		swd->unit[drive].swd = swd;
	पूर्ण

	क्रम (drive = 0; drive < swd->floppy_count; drive++) अणु
		swd->unit[drive].disk->flags = GENHD_FL_REMOVABLE;
		swd->unit[drive].disk->major = FLOPPY_MAJOR;
		swd->unit[drive].disk->first_minor = drive;
		प्र_लिखो(swd->unit[drive].disk->disk_name, "fd%d", drive);
		swd->unit[drive].disk->fops = &floppy_fops;
		swd->unit[drive].disk->events = DISK_EVENT_MEDIA_CHANGE;
		swd->unit[drive].disk->निजी_data = &swd->unit[drive];
		set_capacity(swd->unit[drive].disk, 2880);
		add_disk(swd->unit[drive].disk);
	पूर्ण

	वापस 0;

निकास_put_disks:
	unरेजिस्टर_blkdev(FLOPPY_MAJOR, "fd");
	करो अणु
		काष्ठा gendisk *disk = swd->unit[drive].disk;

		अगर (disk) अणु
			अगर (disk->queue) अणु
				blk_cleanup_queue(disk->queue);
				disk->queue = शून्य;
			पूर्ण
			blk_mq_मुक्त_tag_set(&swd->unit[drive].tag_set);
			put_disk(disk);
		पूर्ण
	पूर्ण जबतक (drive--);
	वापस err;
पूर्ण

अटल पूर्णांक swim_probe(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा resource *res;
	काष्ठा swim __iomem *swim_base;
	काष्ठा swim_priv *swd;
	पूर्णांक ret;

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (!res) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	अगर (!request_mem_region(res->start, resource_size(res), CARDNAME)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	swim_base = (काष्ठा swim __iomem *)res->start;
	अगर (!swim_base) अणु
		ret = -ENOMEM;
		जाओ out_release_io;
	पूर्ण

	/* probe device */

	set_swim_mode(swim_base, 1);
	अगर (!get_swim_mode(swim_base)) अणु
		prपूर्णांकk(KERN_INFO "SWIM device not found !\n");
		ret = -ENODEV;
		जाओ out_release_io;
	पूर्ण

	/* set platक्रमm driver data */

	swd = kzalloc(माप(काष्ठा swim_priv), GFP_KERNEL);
	अगर (!swd) अणु
		ret = -ENOMEM;
		जाओ out_release_io;
	पूर्ण
	platक्रमm_set_drvdata(dev, swd);

	swd->base = swim_base;

	ret = swim_floppy_init(swd);
	अगर (ret)
		जाओ out_kमुक्त;

	वापस 0;

out_kमुक्त:
	kमुक्त(swd);
out_release_io:
	release_mem_region(res->start, resource_size(res));
out:
	वापस ret;
पूर्ण

अटल पूर्णांक swim_हटाओ(काष्ठा platक्रमm_device *dev)
अणु
	काष्ठा swim_priv *swd = platक्रमm_get_drvdata(dev);
	पूर्णांक drive;
	काष्ठा resource *res;

	क्रम (drive = 0; drive < swd->floppy_count; drive++) अणु
		del_gendisk(swd->unit[drive].disk);
		blk_cleanup_queue(swd->unit[drive].disk->queue);
		blk_mq_मुक्त_tag_set(&swd->unit[drive].tag_set);
		put_disk(swd->unit[drive].disk);
	पूर्ण

	unरेजिस्टर_blkdev(FLOPPY_MAJOR, "fd");

	/* eject floppies */

	क्रम (drive = 0; drive < swd->floppy_count; drive++)
		floppy_eject(&swd->unit[drive]);

	res = platक्रमm_get_resource(dev, IORESOURCE_MEM, 0);
	अगर (res)
		release_mem_region(res->start, resource_size(res));

	kमुक्त(swd);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver swim_driver = अणु
	.probe  = swim_probe,
	.हटाओ = swim_हटाओ,
	.driver   = अणु
		.name	= CARDNAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init swim_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "SWIM floppy driver %s\n", DRIVER_VERSION);

	वापस platक्रमm_driver_रेजिस्टर(&swim_driver);
पूर्ण
module_init(swim_init);

अटल व्योम __निकास swim_निकास(व्योम)
अणु
	platक्रमm_driver_unरेजिस्टर(&swim_driver);
पूर्ण
module_निकास(swim_निकास);

MODULE_DESCRIPTION("Driver for SWIM floppy controller");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Laurent Vivier <laurent@lvivier.info>");
MODULE_ALIAS_BLOCKDEV_MAJOR(FLOPPY_MAJOR);
