<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* GD ROM driver क्रम the SEGA Dreamcast
 * copyright Adrian McMenamin, 2007
 * With thanks to Marcus Comstedt and Nathan Keynes
 * क्रम work in reversing PIO and DMA
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/fs.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/cdrom.h>
#समावेश <linux/genhd.h>
#समावेश <linux/bपन.स>
#समावेश <linux/blk-mq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/mutex.h>
#समावेश <linux/रुको.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <scsi/scsi.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/dma.h>
#समावेश <यंत्र/delay.h>
#समावेश <mach/dma.h>
#समावेश <mach/sysasic.h>

#घोषणा GDROM_DEV_NAME "gdrom"
#घोषणा GD_SESSION_OFFSET 150

/* GD Rom commands */
#घोषणा GDROM_COM_SOFTRESET 0x08
#घोषणा GDROM_COM_EXECDIAG 0x90
#घोषणा GDROM_COM_PACKET 0xA0
#घोषणा GDROM_COM_IDDEV 0xA1

/* GD Rom रेजिस्टरs */
#घोषणा GDROM_BASE_REG			0xA05F7000
#घोषणा GDROM_ALTSTATUS_REG		(GDROM_BASE_REG + 0x18)
#घोषणा GDROM_DATA_REG			(GDROM_BASE_REG + 0x80)
#घोषणा GDROM_ERROR_REG		(GDROM_BASE_REG + 0x84)
#घोषणा GDROM_INTSEC_REG		(GDROM_BASE_REG + 0x88)
#घोषणा GDROM_SECNUM_REG		(GDROM_BASE_REG + 0x8C)
#घोषणा GDROM_BCL_REG			(GDROM_BASE_REG + 0x90)
#घोषणा GDROM_BCH_REG			(GDROM_BASE_REG + 0x94)
#घोषणा GDROM_DSEL_REG			(GDROM_BASE_REG + 0x98)
#घोषणा GDROM_STATUSCOMMAND_REG	(GDROM_BASE_REG + 0x9C)
#घोषणा GDROM_RESET_REG		(GDROM_BASE_REG + 0x4E4)

#घोषणा GDROM_DMA_STARTADDR_REG	(GDROM_BASE_REG + 0x404)
#घोषणा GDROM_DMA_LENGTH_REG		(GDROM_BASE_REG + 0x408)
#घोषणा GDROM_DMA_सूचीECTION_REG	(GDROM_BASE_REG + 0x40C)
#घोषणा GDROM_DMA_ENABLE_REG		(GDROM_BASE_REG + 0x414)
#घोषणा GDROM_DMA_STATUS_REG		(GDROM_BASE_REG + 0x418)
#घोषणा GDROM_DMA_WAIT_REG		(GDROM_BASE_REG + 0x4A0)
#घोषणा GDROM_DMA_ACCESS_CTRL_REG	(GDROM_BASE_REG + 0x4B8)

#घोषणा GDROM_HARD_SECTOR	2048
#घोषणा BLOCK_LAYER_SECTOR	512
#घोषणा GD_TO_BLK		4

#घोषणा GDROM_DEFAULT_TIMEOUT	(HZ * 7)

अटल DEFINE_MUTEX(gdrom_mutex);
अटल स्थिर काष्ठा अणु
	पूर्णांक sense_key;
	स्थिर अक्षर * स्थिर text;
पूर्ण sense_texts[] = अणु
	अणुNO_SENSE, "OK"पूर्ण,
	अणुRECOVERED_ERROR, "Recovered from error"पूर्ण,
	अणुNOT_READY, "Device not ready"पूर्ण,
	अणुMEDIUM_ERROR, "Disk not ready"पूर्ण,
	अणुHARDWARE_ERROR, "Hardware error"पूर्ण,
	अणुILLEGAL_REQUEST, "Command has failed"पूर्ण,
	अणुUNIT_ATTENTION, "Device needs attention - disk may have been changed"पूर्ण,
	अणुDATA_PROTECT, "Data protection error"पूर्ण,
	अणुABORTED_COMMAND, "Command aborted"पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *pd;
अटल पूर्णांक gdrom_major;
अटल DECLARE_WAIT_QUEUE_HEAD(command_queue);
अटल DECLARE_WAIT_QUEUE_HEAD(request_queue);

काष्ठा gdromtoc अणु
	अचिन्हित पूर्णांक entry[99];
	अचिन्हित पूर्णांक first, last;
	अचिन्हित पूर्णांक leaकरोut;
पूर्ण;

अटल काष्ठा gdrom_unit अणु
	काष्ठा gendisk *disk;
	काष्ठा cdrom_device_info *cd_info;
	पूर्णांक status;
	पूर्णांक pending;
	पूर्णांक transfer;
	अक्षर disk_type;
	काष्ठा gdromtoc *toc;
	काष्ठा request_queue *gdrom_rq;
	काष्ठा blk_mq_tag_set tag_set;
पूर्ण gd;

काष्ठा gdrom_id अणु
	अक्षर mid;
	अक्षर modid;
	अक्षर verid;
	अक्षर padA[13];
	अक्षर mname[16];
	अक्षर modname[16];
	अक्षर firmver[16];
	अक्षर padB[16];
पूर्ण;

अटल पूर्णांक gdrom_माला_लोense(लघु *bufstring);
अटल पूर्णांक gdrom_packetcommand(काष्ठा cdrom_device_info *cd_info,
	काष्ठा packet_command *command);
अटल पूर्णांक gdrom_hardreset(काष्ठा cdrom_device_info *cd_info);

अटल bool gdrom_is_busy(व्योम)
अणु
	वापस (__raw_पढ़ोb(GDROM_ALTSTATUS_REG) & 0x80) != 0;
पूर्ण

अटल bool gdrom_data_request(व्योम)
अणु
	वापस (__raw_पढ़ोb(GDROM_ALTSTATUS_REG) & 0x88) == 8;
पूर्ण

अटल bool gdrom_रुको_clrbusy(व्योम)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + GDROM_DEFAULT_TIMEOUT;
	जबतक ((__raw_पढ़ोb(GDROM_ALTSTATUS_REG) & 0x80) &&
		(समय_beक्रमe(jअगरfies, समयout)))
		cpu_relax();
	वापस समय_beक्रमe(jअगरfies, समयout + 1);
पूर्ण

अटल bool gdrom_रुको_busy_sleeps(व्योम)
अणु
	अचिन्हित दीर्घ समयout;
	/* Wait to get busy first */
	समयout = jअगरfies + GDROM_DEFAULT_TIMEOUT;
	जबतक (!gdrom_is_busy() && समय_beक्रमe(jअगरfies, समयout))
		cpu_relax();
	/* Now रुको क्रम busy to clear */
	वापस gdrom_रुको_clrbusy();
पूर्ण

अटल व्योम gdrom_identअगरydevice(व्योम *buf)
अणु
	पूर्णांक c;
	लघु *data = buf;
	/* If the device won't clear it has probably
	* been hit by a serious failure - but we'll
	* try to वापस a sense key even so */
	अगर (!gdrom_रुको_clrbusy()) अणु
		gdrom_माला_लोense(शून्य);
		वापस;
	पूर्ण
	__raw_ग_लिखोb(GDROM_COM_IDDEV, GDROM_STATUSCOMMAND_REG);
	अगर (!gdrom_रुको_busy_sleeps()) अणु
		gdrom_माला_लोense(शून्य);
		वापस;
	पूर्ण
	/* now पढ़ो in the data */
	क्रम (c = 0; c < 40; c++)
		data[c] = __raw_पढ़ोw(GDROM_DATA_REG);
पूर्ण

अटल व्योम gdrom_spicommand(व्योम *spi_string, पूर्णांक buflen)
अणु
	लघु *cmd = spi_string;
	अचिन्हित दीर्घ समयout;

	/* ensure IRQ_WAIT is set */
	__raw_ग_लिखोb(0x08, GDROM_ALTSTATUS_REG);
	/* specअगरy how many bytes we expect back */
	__raw_ग_लिखोb(buflen & 0xFF, GDROM_BCL_REG);
	__raw_ग_लिखोb((buflen >> 8) & 0xFF, GDROM_BCH_REG);
	/* other parameters */
	__raw_ग_लिखोb(0, GDROM_INTSEC_REG);
	__raw_ग_लिखोb(0, GDROM_SECNUM_REG);
	__raw_ग_लिखोb(0, GDROM_ERROR_REG);
	/* Wait until we can go */
	अगर (!gdrom_रुको_clrbusy()) अणु
		gdrom_माला_लोense(शून्य);
		वापस;
	पूर्ण
	समयout = jअगरfies + GDROM_DEFAULT_TIMEOUT;
	__raw_ग_लिखोb(GDROM_COM_PACKET, GDROM_STATUSCOMMAND_REG);
	जबतक (!gdrom_data_request() && समय_beक्रमe(jअगरfies, समयout))
		cpu_relax();
	अगर (!समय_beक्रमe(jअगरfies, समयout + 1)) अणु
		gdrom_माला_लोense(शून्य);
		वापस;
	पूर्ण
	outsw(GDROM_DATA_REG, cmd, 6);
पूर्ण


/* gdrom_command_executediagnostic:
 * Used to probe क्रम presence of working GDROM
 * Restarts GDROM device and then applies standard ATA 3
 * Execute Diagnostic Command: a वापस of '1' indicates device 0
 * present and device 1 असलent
 */
अटल अक्षर gdrom_execute_diagnostic(व्योम)
अणु
	gdrom_hardreset(gd.cd_info);
	अगर (!gdrom_रुको_clrbusy())
		वापस 0;
	__raw_ग_लिखोb(GDROM_COM_EXECDIAG, GDROM_STATUSCOMMAND_REG);
	अगर (!gdrom_रुको_busy_sleeps())
		वापस 0;
	वापस __raw_पढ़ोb(GDROM_ERROR_REG);
पूर्ण

/*
 * Prepare disk command
 * byte 0 = 0x70
 * byte 1 = 0x1f
 */
अटल पूर्णांक gdrom_preparedisk_cmd(व्योम)
अणु
	काष्ठा packet_command *spin_command;
	spin_command = kzalloc(माप(काष्ठा packet_command), GFP_KERNEL);
	अगर (!spin_command)
		वापस -ENOMEM;
	spin_command->cmd[0] = 0x70;
	spin_command->cmd[2] = 0x1f;
	spin_command->buflen = 0;
	gd.pending = 1;
	gdrom_packetcommand(gd.cd_info, spin_command);
	/* 60 second समयout */
	रुको_event_पूर्णांकerruptible_समयout(command_queue, gd.pending == 0,
		GDROM_DEFAULT_TIMEOUT);
	gd.pending = 0;
	kमुक्त(spin_command);
	अगर (gd.status & 0x01) अणु
		/* log an error */
		gdrom_माला_लोense(शून्य);
		वापस -EIO;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Read TOC command
 * byte 0 = 0x14
 * byte 1 = session
 * byte 3 = माप TOC >> 8  ie upper byte
 * byte 4 = माप TOC & 0xff ie lower byte
 */
अटल पूर्णांक gdrom_पढ़ोtoc_cmd(काष्ठा gdromtoc *toc, पूर्णांक session)
अणु
	पूर्णांक tocsize;
	काष्ठा packet_command *toc_command;
	पूर्णांक err = 0;

	toc_command = kzalloc(माप(काष्ठा packet_command), GFP_KERNEL);
	अगर (!toc_command)
		वापस -ENOMEM;
	tocsize = माप(काष्ठा gdromtoc);
	toc_command->cmd[0] = 0x14;
	toc_command->cmd[1] = session;
	toc_command->cmd[3] = tocsize >> 8;
	toc_command->cmd[4] = tocsize & 0xff;
	toc_command->buflen = tocsize;
	अगर (gd.pending) अणु
		err = -EBUSY;
		जाओ cleanup_पढ़ोtoc_final;
	पूर्ण
	gd.pending = 1;
	gdrom_packetcommand(gd.cd_info, toc_command);
	रुको_event_पूर्णांकerruptible_समयout(command_queue, gd.pending == 0,
		GDROM_DEFAULT_TIMEOUT);
	अगर (gd.pending) अणु
		err = -EINVAL;
		जाओ cleanup_पढ़ोtoc;
	पूर्ण
	insw(GDROM_DATA_REG, toc, tocsize/2);
	अगर (gd.status & 0x01)
		err = -EINVAL;

cleanup_पढ़ोtoc:
	gd.pending = 0;
cleanup_पढ़ोtoc_final:
	kमुक्त(toc_command);
	वापस err;
पूर्ण

/* TOC helpers */
अटल पूर्णांक get_entry_lba(पूर्णांक track)
अणु
	वापस (cpu_to_be32(track & 0xffffff00) - GD_SESSION_OFFSET);
पूर्ण

अटल पूर्णांक get_entry_q_ctrl(पूर्णांक track)
अणु
	वापस (track & 0x000000f0) >> 4;
पूर्ण

अटल पूर्णांक get_entry_track(पूर्णांक track)
अणु
	वापस (track & 0x0000ff00) >> 8;
पूर्ण

अटल पूर्णांक gdrom_get_last_session(काष्ठा cdrom_device_info *cd_info,
	काष्ठा cdrom_multisession *ms_info)
अणु
	पूर्णांक fentry, lentry, track, data, err;

	अगर (!gd.toc)
		वापस -ENOMEM;

	/* Check अगर GD-ROM */
	err = gdrom_पढ़ोtoc_cmd(gd.toc, 1);
	/* Not a GD-ROM so check अगर standard CD-ROM */
	अगर (err) अणु
		err = gdrom_पढ़ोtoc_cmd(gd.toc, 0);
		अगर (err) अणु
			pr_info("Could not get CD table of contents\n");
			वापस -ENXIO;
		पूर्ण
	पूर्ण

	fentry = get_entry_track(gd.toc->first);
	lentry = get_entry_track(gd.toc->last);
	/* Find the first data track */
	track = get_entry_track(gd.toc->last);
	करो अणु
		data = gd.toc->entry[track - 1];
		अगर (get_entry_q_ctrl(data))
			अवरोध;	/* ie a real data track */
		track--;
	पूर्ण जबतक (track >= fentry);

	अगर ((track > 100) || (track < get_entry_track(gd.toc->first))) अणु
		pr_info("No data on the last session of the CD\n");
		gdrom_माला_लोense(शून्य);
		वापस -ENXIO;
	पूर्ण

	ms_info->addr_क्रमmat = CDROM_LBA;
	ms_info->addr.lba = get_entry_lba(data);
	ms_info->xa_flag = 1;
	वापस 0;
पूर्ण

अटल पूर्णांक gdrom_खोलो(काष्ठा cdrom_device_info *cd_info, पूर्णांक purpose)
अणु
	/* spin up the disk */
	वापस gdrom_preparedisk_cmd();
पूर्ण

/* this function is required even अगर empty */
अटल व्योम gdrom_release(काष्ठा cdrom_device_info *cd_info)
अणु
पूर्ण

अटल पूर्णांक gdrom_drivestatus(काष्ठा cdrom_device_info *cd_info, पूर्णांक ignore)
अणु
	/* पढ़ो the sense key */
	अक्षर sense = __raw_पढ़ोb(GDROM_ERROR_REG);
	sense &= 0xF0;
	अगर (sense == 0)
		वापस CDS_DISC_OK;
	अगर (sense == 0x20)
		वापस CDS_DRIVE_NOT_READY;
	/* शेष */
	वापस CDS_NO_INFO;
पूर्ण

अटल अचिन्हित पूर्णांक gdrom_check_events(काष्ठा cdrom_device_info *cd_info,
				       अचिन्हित पूर्णांक clearing, पूर्णांक ignore)
अणु
	/* check the sense key */
	वापस (__raw_पढ़ोb(GDROM_ERROR_REG) & 0xF0) == 0x60 ?
		DISK_EVENT_MEDIA_CHANGE : 0;
पूर्ण

/* reset the G1 bus */
अटल पूर्णांक gdrom_hardreset(काष्ठा cdrom_device_info *cd_info)
अणु
	पूर्णांक count;
	__raw_ग_लिखोl(0x1fffff, GDROM_RESET_REG);
	क्रम (count = 0xa0000000; count < 0xa0200000; count += 4)
		__raw_पढ़ोl(count);
	वापस 0;
पूर्ण

/* keep the function looking like the universal
 * CD Rom specअगरication  - वापसing पूर्णांक */
अटल पूर्णांक gdrom_packetcommand(काष्ठा cdrom_device_info *cd_info,
	काष्ठा packet_command *command)
अणु
	gdrom_spicommand(&command->cmd, command->buflen);
	वापस 0;
पूर्ण

/* Get Sense SPI command
 * From Marcus Comstedt
 * cmd = 0x13
 * cmd + 4 = length of वापसed buffer
 * Returns 5 16 bit words
 */
अटल पूर्णांक gdrom_माला_लोense(लघु *bufstring)
अणु
	काष्ठा packet_command *sense_command;
	लघु sense[5];
	पूर्णांक sense_key;
	पूर्णांक err = -EIO;

	sense_command = kzalloc(माप(काष्ठा packet_command), GFP_KERNEL);
	अगर (!sense_command)
		वापस -ENOMEM;
	sense_command->cmd[0] = 0x13;
	sense_command->cmd[4] = 10;
	sense_command->buflen = 10;
	/* even अगर something is pending try to get
	* the sense key अगर possible */
	अगर (gd.pending && !gdrom_रुको_clrbusy()) अणु
		err = -EBUSY;
		जाओ cleanup_sense_final;
	पूर्ण
	gd.pending = 1;
	gdrom_packetcommand(gd.cd_info, sense_command);
	रुको_event_पूर्णांकerruptible_समयout(command_queue, gd.pending == 0,
		GDROM_DEFAULT_TIMEOUT);
	अगर (gd.pending)
		जाओ cleanup_sense;
	insw(GDROM_DATA_REG, &sense, sense_command->buflen/2);
	अगर (sense[1] & 40) अणु
		pr_info("Drive not ready - command aborted\n");
		जाओ cleanup_sense;
	पूर्ण
	sense_key = sense[1] & 0x0F;
	अगर (sense_key < ARRAY_SIZE(sense_texts))
		pr_info("%s\n", sense_texts[sense_key].text);
	अन्यथा
		pr_err("Unknown sense key: %d\n", sense_key);
	अगर (bufstring) /* वापस addional sense data */
		स_नकल(bufstring, &sense[4], 2);
	अगर (sense_key < 2)
		err = 0;

cleanup_sense:
	gd.pending = 0;
cleanup_sense_final:
	kमुक्त(sense_command);
	वापस err;
पूर्ण

अटल पूर्णांक gdrom_audio_ioctl(काष्ठा cdrom_device_info *cdi, अचिन्हित पूर्णांक cmd,
			     व्योम *arg)
अणु
	वापस -EINVAL;
पूर्ण

अटल स्थिर काष्ठा cdrom_device_ops gdrom_ops = अणु
	.खोलो			= gdrom_खोलो,
	.release		= gdrom_release,
	.drive_status		= gdrom_drivestatus,
	.check_events		= gdrom_check_events,
	.get_last_session	= gdrom_get_last_session,
	.reset			= gdrom_hardreset,
	.audio_ioctl		= gdrom_audio_ioctl,
	.generic_packet		= cdrom_dummy_generic_packet,
	.capability		= CDC_MULTI_SESSION | CDC_MEDIA_CHANGED |
				  CDC_RESET | CDC_DRIVE_STATUS | CDC_CD_R,
पूर्ण;

अटल पूर्णांक gdrom_bकरोps_खोलो(काष्ठा block_device *bdev, भ_शेषe_t mode)
अणु
	पूर्णांक ret;

	bdev_check_media_change(bdev);

	mutex_lock(&gdrom_mutex);
	ret = cdrom_खोलो(gd.cd_info, bdev, mode);
	mutex_unlock(&gdrom_mutex);
	वापस ret;
पूर्ण

अटल व्योम gdrom_bकरोps_release(काष्ठा gendisk *disk, भ_शेषe_t mode)
अणु
	mutex_lock(&gdrom_mutex);
	cdrom_release(gd.cd_info, mode);
	mutex_unlock(&gdrom_mutex);
पूर्ण

अटल अचिन्हित पूर्णांक gdrom_bकरोps_check_events(काष्ठा gendisk *disk,
					     अचिन्हित पूर्णांक clearing)
अणु
	वापस cdrom_check_events(gd.cd_info, clearing);
पूर्ण

अटल पूर्णांक gdrom_bकरोps_ioctl(काष्ठा block_device *bdev, भ_शेषe_t mode,
	अचिन्हित cmd, अचिन्हित दीर्घ arg)
अणु
	पूर्णांक ret;

	mutex_lock(&gdrom_mutex);
	ret = cdrom_ioctl(gd.cd_info, bdev, mode, cmd, arg);
	mutex_unlock(&gdrom_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा block_device_operations gdrom_bकरोps = अणु
	.owner			= THIS_MODULE,
	.खोलो			= gdrom_bकरोps_खोलो,
	.release		= gdrom_bकरोps_release,
	.check_events		= gdrom_bकरोps_check_events,
	.ioctl			= gdrom_bकरोps_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl		= blkdev_compat_ptr_ioctl,
#पूर्ण_अगर
पूर्ण;

अटल irqवापस_t gdrom_command_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	gd.status = __raw_पढ़ोb(GDROM_STATUSCOMMAND_REG);
	अगर (gd.pending != 1)
		वापस IRQ_HANDLED;
	gd.pending = 0;
	wake_up_पूर्णांकerruptible(&command_queue);
	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t gdrom_dma_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	gd.status = __raw_पढ़ोb(GDROM_STATUSCOMMAND_REG);
	अगर (gd.transfer != 1)
		वापस IRQ_HANDLED;
	gd.transfer = 0;
	wake_up_पूर्णांकerruptible(&request_queue);
	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक gdrom_set_पूर्णांकerrupt_handlers(व्योम)
अणु
	पूर्णांक err;

	err = request_irq(HW_EVENT_GDROM_CMD, gdrom_command_पूर्णांकerrupt,
		0, "gdrom_command", &gd);
	अगर (err)
		वापस err;
	err = request_irq(HW_EVENT_GDROM_DMA, gdrom_dma_पूर्णांकerrupt,
		0, "gdrom_dma", &gd);
	अगर (err)
		मुक्त_irq(HW_EVENT_GDROM_CMD, &gd);
	वापस err;
पूर्ण

/* Implement DMA पढ़ो using SPI command
 * 0 -> 0x30
 * 1 -> mode
 * 2 -> block >> 16
 * 3 -> block >> 8
 * 4 -> block
 * 8 -> sectors >> 16
 * 9 -> sectors >> 8
 * 10 -> sectors
 */
अटल blk_status_t gdrom_पढ़ोdisk_dma(काष्ठा request *req)
अणु
	पूर्णांक block, block_cnt;
	blk_status_t err;
	काष्ठा packet_command *पढ़ो_command;
	अचिन्हित दीर्घ समयout;

	पढ़ो_command = kzalloc(माप(काष्ठा packet_command), GFP_KERNEL);
	अगर (!पढ़ो_command)
		वापस BLK_STS_RESOURCE;

	पढ़ो_command->cmd[0] = 0x30;
	पढ़ो_command->cmd[1] = 0x20;
	block = blk_rq_pos(req)/GD_TO_BLK + GD_SESSION_OFFSET;
	block_cnt = blk_rq_sectors(req)/GD_TO_BLK;
	__raw_ग_लिखोl(page_to_phys(bio_page(req->bio)) + bio_offset(req->bio),
			GDROM_DMA_STARTADDR_REG);
	__raw_ग_लिखोl(block_cnt * GDROM_HARD_SECTOR, GDROM_DMA_LENGTH_REG);
	__raw_ग_लिखोl(1, GDROM_DMA_सूचीECTION_REG);
	__raw_ग_लिखोl(1, GDROM_DMA_ENABLE_REG);
	पढ़ो_command->cmd[2] = (block >> 16) & 0xFF;
	पढ़ो_command->cmd[3] = (block >> 8) & 0xFF;
	पढ़ो_command->cmd[4] = block & 0xFF;
	पढ़ो_command->cmd[8] = (block_cnt >> 16) & 0xFF;
	पढ़ो_command->cmd[9] = (block_cnt >> 8) & 0xFF;
	पढ़ो_command->cmd[10] = block_cnt & 0xFF;
	/* set क्रम DMA */
	__raw_ग_लिखोb(1, GDROM_ERROR_REG);
	/* other रेजिस्टरs */
	__raw_ग_लिखोb(0, GDROM_SECNUM_REG);
	__raw_ग_लिखोb(0, GDROM_BCL_REG);
	__raw_ग_लिखोb(0, GDROM_BCH_REG);
	__raw_ग_लिखोb(0, GDROM_DSEL_REG);
	__raw_ग_लिखोb(0, GDROM_INTSEC_REG);
	/* Wait क्रम रेजिस्टरs to reset after any previous activity */
	समयout = jअगरfies + HZ / 2;
	जबतक (gdrom_is_busy() && समय_beक्रमe(jअगरfies, समयout))
		cpu_relax();
	__raw_ग_लिखोb(GDROM_COM_PACKET, GDROM_STATUSCOMMAND_REG);
	समयout = jअगरfies + HZ / 2;
	/* Wait क्रम packet command to finish */
	जबतक (gdrom_is_busy() && समय_beक्रमe(jअगरfies, समयout))
		cpu_relax();
	gd.pending = 1;
	gd.transfer = 1;
	outsw(GDROM_DATA_REG, &पढ़ो_command->cmd, 6);
	समयout = jअगरfies + HZ / 2;
	/* Wait क्रम any pending DMA to finish */
	जबतक (__raw_पढ़ोb(GDROM_DMA_STATUS_REG) &&
		समय_beक्रमe(jअगरfies, समयout))
		cpu_relax();
	/* start transfer */
	__raw_ग_लिखोb(1, GDROM_DMA_STATUS_REG);
	रुको_event_पूर्णांकerruptible_समयout(request_queue,
		gd.transfer == 0, GDROM_DEFAULT_TIMEOUT);
	err = gd.transfer ? BLK_STS_IOERR : BLK_STS_OK;
	gd.transfer = 0;
	gd.pending = 0;

	blk_mq_end_request(req, err);
	kमुक्त(पढ़ो_command);
	वापस BLK_STS_OK;
पूर्ण

अटल blk_status_t gdrom_queue_rq(काष्ठा blk_mq_hw_ctx *hctx,
				   स्थिर काष्ठा blk_mq_queue_data *bd)
अणु
	blk_mq_start_request(bd->rq);

	चयन (req_op(bd->rq)) अणु
	हाल REQ_OP_READ:
		वापस gdrom_पढ़ोdisk_dma(bd->rq);
	हाल REQ_OP_WRITE:
		pr_notice("Read only device - write request ignored\n");
		वापस BLK_STS_IOERR;
	शेष:
		prपूर्णांकk(KERN_DEBUG "gdrom: Non-fs request ignored\n");
		वापस BLK_STS_IOERR;
	पूर्ण
पूर्ण

/* Prपूर्णांक string identअगरying GD ROM device */
अटल पूर्णांक gdrom_outputversion(व्योम)
अणु
	काष्ठा gdrom_id *id;
	अक्षर *model_name, *manuf_name, *firmw_ver;
	पूर्णांक err = -ENOMEM;

	/* query device ID */
	id = kzalloc(माप(काष्ठा gdrom_id), GFP_KERNEL);
	अगर (!id)
		वापस err;
	gdrom_identअगरydevice(id);
	model_name = kstrndup(id->modname, 16, GFP_KERNEL);
	अगर (!model_name)
		जाओ मुक्त_id;
	manuf_name = kstrndup(id->mname, 16, GFP_KERNEL);
	अगर (!manuf_name)
		जाओ मुक्त_model_name;
	firmw_ver = kstrndup(id->firmver, 16, GFP_KERNEL);
	अगर (!firmw_ver)
		जाओ मुक्त_manuf_name;
	pr_info("%s from %s with firmware %s\n",
		model_name, manuf_name, firmw_ver);
	err = 0;
	kमुक्त(firmw_ver);
मुक्त_manuf_name:
	kमुक्त(manuf_name);
मुक्त_model_name:
	kमुक्त(model_name);
मुक्त_id:
	kमुक्त(id);
	वापस err;
पूर्ण

/* set the शेष mode क्रम DMA transfer */
अटल पूर्णांक gdrom_init_dma_mode(व्योम)
अणु
	__raw_ग_लिखोb(0x13, GDROM_ERROR_REG);
	__raw_ग_लिखोb(0x22, GDROM_INTSEC_REG);
	अगर (!gdrom_रुको_clrbusy())
		वापस -EBUSY;
	__raw_ग_लिखोb(0xEF, GDROM_STATUSCOMMAND_REG);
	अगर (!gdrom_रुको_busy_sleeps())
		वापस -EBUSY;
	/* Memory protection setting क्रम GDROM DMA
	* Bits 31 - 16 security: 0x8843
	* Bits 15 and 7 reserved (0)
	* Bits 14 - 8 start of transfer range in 1 MB blocks OR'ed with 0x80
	* Bits 6 - 0 end of transfer range in 1 MB blocks OR'ed with 0x80
	* (0x40 | 0x80) = start range at 0x0C000000
	* (0x7F | 0x80) = end range at 0x0FFFFFFF */
	__raw_ग_लिखोl(0x8843407F, GDROM_DMA_ACCESS_CTRL_REG);
	__raw_ग_लिखोl(9, GDROM_DMA_WAIT_REG); /* DMA word setting */
	वापस 0;
पूर्ण

अटल व्योम probe_gdrom_setupcd(व्योम)
अणु
	gd.cd_info->ops = &gdrom_ops;
	gd.cd_info->capacity = 1;
	म_नकल(gd.cd_info->name, GDROM_DEV_NAME);
	gd.cd_info->mask = CDC_CLOSE_TRAY|CDC_OPEN_TRAY|CDC_LOCK|
		CDC_SELECT_DISC;
पूर्ण

अटल व्योम probe_gdrom_setupdisk(व्योम)
अणु
	gd.disk->major = gdrom_major;
	gd.disk->first_minor = 1;
	gd.disk->minors = 1;
	म_नकल(gd.disk->disk_name, GDROM_DEV_NAME);
पूर्ण

अटल पूर्णांक probe_gdrom_setupqueue(व्योम)
अणु
	blk_queue_logical_block_size(gd.gdrom_rq, GDROM_HARD_SECTOR);
	/* using DMA so memory will need to be contiguous */
	blk_queue_max_segments(gd.gdrom_rq, 1);
	/* set a large max size to get most from DMA */
	blk_queue_max_segment_size(gd.gdrom_rq, 0x40000);
	gd.disk->queue = gd.gdrom_rq;
	वापस gdrom_init_dma_mode();
पूर्ण

अटल स्थिर काष्ठा blk_mq_ops gdrom_mq_ops = अणु
	.queue_rq	= gdrom_queue_rq,
पूर्ण;

/*
 * रेजिस्टर this as a block device and as compliant with the
 * universal CD Rom driver पूर्णांकerface
 */
अटल पूर्णांक probe_gdrom(काष्ठा platक्रमm_device *devptr)
अणु
	पूर्णांक err;

	/*
	 * Ensure our "one" device is initialized properly in हाल of previous
	 * usages of it
	 */
	स_रखो(&gd, 0, माप(gd));

	/* Start the device */
	अगर (gdrom_execute_diagnostic() != 1) अणु
		pr_warn("ATA Probe for GDROM failed\n");
		वापस -ENODEV;
	पूर्ण
	/* Prपूर्णांक out firmware ID */
	अगर (gdrom_outputversion())
		वापस -ENOMEM;
	/* Register GDROM */
	gdrom_major = रेजिस्टर_blkdev(0, GDROM_DEV_NAME);
	अगर (gdrom_major <= 0)
		वापस gdrom_major;
	pr_info("Registered with major number %d\n",
		gdrom_major);
	/* Specअगरy basic properties of drive */
	gd.cd_info = kzalloc(माप(काष्ठा cdrom_device_info), GFP_KERNEL);
	अगर (!gd.cd_info) अणु
		err = -ENOMEM;
		जाओ probe_fail_no_mem;
	पूर्ण
	probe_gdrom_setupcd();
	gd.disk = alloc_disk(1);
	अगर (!gd.disk) अणु
		err = -ENODEV;
		जाओ probe_fail_no_disk;
	पूर्ण
	probe_gdrom_setupdisk();
	अगर (रेजिस्टर_cdrom(gd.disk, gd.cd_info)) अणु
		err = -ENODEV;
		जाओ probe_fail_cdrom_रेजिस्टर;
	पूर्ण
	gd.disk->fops = &gdrom_bकरोps;
	gd.disk->events = DISK_EVENT_MEDIA_CHANGE;
	/* latch on to the पूर्णांकerrupt */
	err = gdrom_set_पूर्णांकerrupt_handlers();
	अगर (err)
		जाओ probe_fail_cmdirq_रेजिस्टर;

	gd.gdrom_rq = blk_mq_init_sq_queue(&gd.tag_set, &gdrom_mq_ops, 1,
				BLK_MQ_F_SHOULD_MERGE | BLK_MQ_F_BLOCKING);
	अगर (IS_ERR(gd.gdrom_rq)) अणु
		err = PTR_ERR(gd.gdrom_rq);
		gd.gdrom_rq = शून्य;
		जाओ probe_fail_requestq;
	पूर्ण

	err = probe_gdrom_setupqueue();
	अगर (err)
		जाओ probe_fail_toc;

	gd.toc = kzalloc(माप(काष्ठा gdromtoc), GFP_KERNEL);
	अगर (!gd.toc) अणु
		err = -ENOMEM;
		जाओ probe_fail_toc;
	पूर्ण
	add_disk(gd.disk);
	वापस 0;

probe_fail_toc:
	blk_cleanup_queue(gd.gdrom_rq);
	blk_mq_मुक्त_tag_set(&gd.tag_set);
probe_fail_requestq:
	मुक्त_irq(HW_EVENT_GDROM_DMA, &gd);
	मुक्त_irq(HW_EVENT_GDROM_CMD, &gd);
probe_fail_cmdirq_रेजिस्टर:
probe_fail_cdrom_रेजिस्टर:
	del_gendisk(gd.disk);
probe_fail_no_disk:
	kमुक्त(gd.cd_info);
probe_fail_no_mem:
	unरेजिस्टर_blkdev(gdrom_major, GDROM_DEV_NAME);
	gdrom_major = 0;
	pr_warn("Probe failed - error is 0x%X\n", err);
	वापस err;
पूर्ण

अटल पूर्णांक हटाओ_gdrom(काष्ठा platक्रमm_device *devptr)
अणु
	blk_cleanup_queue(gd.gdrom_rq);
	blk_mq_मुक्त_tag_set(&gd.tag_set);
	मुक्त_irq(HW_EVENT_GDROM_CMD, &gd);
	मुक्त_irq(HW_EVENT_GDROM_DMA, &gd);
	del_gendisk(gd.disk);
	अगर (gdrom_major)
		unरेजिस्टर_blkdev(gdrom_major, GDROM_DEV_NAME);
	unरेजिस्टर_cdrom(gd.cd_info);
	kमुक्त(gd.cd_info);
	kमुक्त(gd.toc);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver gdrom_driver = अणु
	.probe = probe_gdrom,
	.हटाओ = हटाओ_gdrom,
	.driver = अणु
			.name = GDROM_DEV_NAME,
	पूर्ण,
पूर्ण;

अटल पूर्णांक __init init_gdrom(व्योम)
अणु
	पूर्णांक rc;

	rc = platक्रमm_driver_रेजिस्टर(&gdrom_driver);
	अगर (rc)
		वापस rc;
	pd = platक्रमm_device_रेजिस्टर_simple(GDROM_DEV_NAME, -1, शून्य, 0);
	अगर (IS_ERR(pd)) अणु
		platक्रमm_driver_unरेजिस्टर(&gdrom_driver);
		वापस PTR_ERR(pd);
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम __निकास निकास_gdrom(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(pd);
	platक्रमm_driver_unरेजिस्टर(&gdrom_driver);
पूर्ण

module_init(init_gdrom);
module_निकास(निकास_gdrom);
MODULE_AUTHOR("Adrian McMenamin <adrian@mcmen.demon.co.uk>");
MODULE_DESCRIPTION("SEGA Dreamcast GD-ROM Driver");
MODULE_LICENSE("GPL");
