<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * PS3 BD/DVD/CD-ROM Storage Driver
 *
 * Copyright (C) 2007 Sony Computer Entertainment Inc.
 * Copyright 2007 Sony Corp.
 */

#समावेश <linux/cdrom.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>

#समावेश <scsi/scsi.h>
#समावेश <scsi/scsi_cmnd.h>
#समावेश <scsi/scsi_dbg.h>
#समावेश <scsi/scsi_device.h>
#समावेश <scsi/scsi_host.h>
#समावेश <scsi/scsi_eh.h>

#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/ps3stor.h>


#घोषणा DEVICE_NAME			"ps3rom"

#घोषणा BOUNCE_SIZE			(64*1024)

#घोषणा PS3ROM_MAX_SECTORS		(BOUNCE_SIZE >> 9)


काष्ठा ps3rom_निजी अणु
	काष्ठा ps3_storage_device *dev;
	काष्ठा scsi_cmnd *curr_cmd;
पूर्ण;


#घोषणा LV1_STORAGE_SEND_ATAPI_COMMAND	(1)

काष्ठा lv1_atapi_cmnd_block अणु
	u8	pkt[32];	/* packet command block           */
	u32	pktlen;		/* should be 12 क्रम ATAPI 8020    */
	u32	blocks;
	u32	block_size;
	u32	proto;		/* transfer mode                  */
	u32	in_out;		/* transfer direction             */
	u64	buffer;		/* parameter except command block */
	u32	arglen;		/* length above                   */
पूर्ण;

क्रमागत lv1_atapi_proto अणु
	NON_DATA_PROTO     = 0,
	PIO_DATA_IN_PROTO  = 1,
	PIO_DATA_OUT_PROTO = 2,
	DMA_PROTO = 3
पूर्ण;

क्रमागत lv1_atapi_in_out अणु
	सूची_WRITE = 0,		/* memory -> device */
	सूची_READ = 1		/* device -> memory */
पूर्ण;


अटल पूर्णांक ps3rom_slave_configure(काष्ठा scsi_device *scsi_dev)
अणु
	काष्ठा ps3rom_निजी *priv = shost_priv(scsi_dev->host);
	काष्ठा ps3_storage_device *dev = priv->dev;

	dev_dbg(&dev->sbd.core, "%s:%u: id %u, lun %llu, channel %u\n", __func__,
		__LINE__, scsi_dev->id, scsi_dev->lun, scsi_dev->channel);

	/*
	 * ATAPI SFF8020 devices use MODE_SENSE_10,
	 * so we can prohibit MODE_SENSE_6
	 */
	scsi_dev->use_10_क्रम_ms = 1;

	/* we करोn't support अणुREAD,WRITEपूर्ण_6 */
	scsi_dev->use_10_क्रम_rw = 1;

	वापस 0;
पूर्ण

अटल पूर्णांक ps3rom_atapi_request(काष्ठा ps3_storage_device *dev,
				काष्ठा scsi_cmnd *cmd)
अणु
	काष्ठा lv1_atapi_cmnd_block atapi_cmnd;
	अचिन्हित अक्षर opcode = cmd->cmnd[0];
	पूर्णांक res;
	u64 lpar;

	dev_dbg(&dev->sbd.core, "%s:%u: send ATAPI command 0x%02x\n", __func__,
		__LINE__, opcode);

	स_रखो(&atapi_cmnd, 0, माप(काष्ठा lv1_atapi_cmnd_block));
	स_नकल(&atapi_cmnd.pkt, cmd->cmnd, 12);
	atapi_cmnd.pktlen = 12;
	atapi_cmnd.block_size = 1; /* transfer size is block_size * blocks */
	atapi_cmnd.blocks = atapi_cmnd.arglen = scsi_bufflen(cmd);
	atapi_cmnd.buffer = dev->bounce_lpar;

	चयन (cmd->sc_data_direction) अणु
	हाल DMA_FROM_DEVICE:
		अगर (scsi_bufflen(cmd) >= CD_FRAMESIZE)
			atapi_cmnd.proto = DMA_PROTO;
		अन्यथा
			atapi_cmnd.proto = PIO_DATA_IN_PROTO;
		atapi_cmnd.in_out = सूची_READ;
		अवरोध;

	हाल DMA_TO_DEVICE:
		अगर (scsi_bufflen(cmd) >= CD_FRAMESIZE)
			atapi_cmnd.proto = DMA_PROTO;
		अन्यथा
			atapi_cmnd.proto = PIO_DATA_OUT_PROTO;
		atapi_cmnd.in_out = सूची_WRITE;
		scsi_sg_copy_to_buffer(cmd, dev->bounce_buf, dev->bounce_size);
		अवरोध;

	शेष:
		atapi_cmnd.proto = NON_DATA_PROTO;
		अवरोध;
	पूर्ण

	lpar = ps3_mm_phys_to_lpar(__pa(&atapi_cmnd));
	res = lv1_storage_send_device_command(dev->sbd.dev_id,
					      LV1_STORAGE_SEND_ATAPI_COMMAND,
					      lpar, माप(atapi_cmnd),
					      atapi_cmnd.buffer,
					      atapi_cmnd.arglen, &dev->tag);
	अगर (res == LV1_DENIED_BY_POLICY) अणु
		dev_dbg(&dev->sbd.core,
			"%s:%u: ATAPI command 0x%02x denied by policy\n",
			__func__, __LINE__, opcode);
		वापस DID_ERROR << 16;
	पूर्ण

	अगर (res) अणु
		dev_err(&dev->sbd.core,
			"%s:%u: ATAPI command 0x%02x failed %d\n", __func__,
			__LINE__, opcode, res);
		वापस DID_ERROR << 16;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक srb10_lba(स्थिर काष्ठा scsi_cmnd *cmd)
अणु
	वापस cmd->cmnd[2] << 24 | cmd->cmnd[3] << 16 | cmd->cmnd[4] << 8 |
	       cmd->cmnd[5];
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक srb10_len(स्थिर काष्ठा scsi_cmnd *cmd)
अणु
	वापस cmd->cmnd[7] << 8 | cmd->cmnd[8];
पूर्ण

अटल पूर्णांक ps3rom_पढ़ो_request(काष्ठा ps3_storage_device *dev,
			       काष्ठा scsi_cmnd *cmd, u32 start_sector,
			       u32 sectors)
अणु
	पूर्णांक res;

	dev_dbg(&dev->sbd.core, "%s:%u: read %u sectors starting at %u\n",
		__func__, __LINE__, sectors, start_sector);

	res = lv1_storage_पढ़ो(dev->sbd.dev_id,
			       dev->regions[dev->region_idx].id, start_sector,
			       sectors, 0, dev->bounce_lpar, &dev->tag);
	अगर (res) अणु
		dev_err(&dev->sbd.core, "%s:%u: read failed %d\n", __func__,
			__LINE__, res);
		वापस DID_ERROR << 16;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ps3rom_ग_लिखो_request(काष्ठा ps3_storage_device *dev,
				काष्ठा scsi_cmnd *cmd, u32 start_sector,
				u32 sectors)
अणु
	पूर्णांक res;

	dev_dbg(&dev->sbd.core, "%s:%u: write %u sectors starting at %u\n",
		__func__, __LINE__, sectors, start_sector);

	scsi_sg_copy_to_buffer(cmd, dev->bounce_buf, dev->bounce_size);

	res = lv1_storage_ग_लिखो(dev->sbd.dev_id,
				dev->regions[dev->region_idx].id, start_sector,
				sectors, 0, dev->bounce_lpar, &dev->tag);
	अगर (res) अणु
		dev_err(&dev->sbd.core, "%s:%u: write failed %d\n", __func__,
			__LINE__, res);
		वापस DID_ERROR << 16;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ps3rom_queuecommand_lck(काष्ठा scsi_cmnd *cmd,
			       व्योम (*करोne)(काष्ठा scsi_cmnd *))
अणु
	काष्ठा ps3rom_निजी *priv = shost_priv(cmd->device->host);
	काष्ठा ps3_storage_device *dev = priv->dev;
	अचिन्हित अक्षर opcode;
	पूर्णांक res;

	priv->curr_cmd = cmd;
	cmd->scsi_करोne = करोne;

	opcode = cmd->cmnd[0];
	/*
	 * While we can submit READ/WRITE SCSI commands as ATAPI commands,
	 * it's recommended क्रम various reasons (perक्रमmance, error handling,
	 * ...) to use lv1_storage_अणुपढ़ो,ग_लिखोपूर्ण() instead
	 */
	चयन (opcode) अणु
	हाल READ_10:
		res = ps3rom_पढ़ो_request(dev, cmd, srb10_lba(cmd),
					  srb10_len(cmd));
		अवरोध;

	हाल WRITE_10:
		res = ps3rom_ग_लिखो_request(dev, cmd, srb10_lba(cmd),
					   srb10_len(cmd));
		अवरोध;

	शेष:
		res = ps3rom_atapi_request(dev, cmd);
		अवरोध;
	पूर्ण

	अगर (res) अणु
		स_रखो(cmd->sense_buffer, 0, SCSI_SENSE_BUFFERSIZE);
		cmd->result = res;
		cmd->sense_buffer[0] = 0x70;
		cmd->sense_buffer[2] = ILLEGAL_REQUEST;
		priv->curr_cmd = शून्य;
		cmd->scsi_करोne(cmd);
	पूर्ण

	वापस 0;
पूर्ण

अटल DEF_SCSI_QCMD(ps3rom_queuecommand)

अटल पूर्णांक decode_lv1_status(u64 status, अचिन्हित अक्षर *sense_key,
			     अचिन्हित अक्षर *asc, अचिन्हित अक्षर *ascq)
अणु
	अगर (((status >> 24) & 0xff) != SAM_STAT_CHECK_CONDITION)
		वापस -1;

	*sense_key = (status >> 16) & 0xff;
	*asc       = (status >>  8) & 0xff;
	*ascq      =  status        & 0xff;
	वापस 0;
पूर्ण

अटल irqवापस_t ps3rom_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा ps3_storage_device *dev = data;
	काष्ठा Scsi_Host *host;
	काष्ठा ps3rom_निजी *priv;
	काष्ठा scsi_cmnd *cmd;
	पूर्णांक res;
	u64 tag, status;
	अचिन्हित अक्षर sense_key, asc, ascq;

	res = lv1_storage_get_async_status(dev->sbd.dev_id, &tag, &status);
	/*
	 * status = -1 may mean that ATAPI transport completed OK, but
	 * ATAPI command itself resulted CHECK CONDITION
	 * so, upper layer should issue REQUEST_SENSE to check the sense data
	 */

	अगर (tag != dev->tag)
		dev_err(&dev->sbd.core,
			"%s:%u: tag mismatch, got %llx, expected %llx\n",
			__func__, __LINE__, tag, dev->tag);

	अगर (res) अणु
		dev_err(&dev->sbd.core, "%s:%u: res=%d status=0x%llx\n",
			__func__, __LINE__, res, status);
		वापस IRQ_HANDLED;
	पूर्ण

	host = ps3_प्रणाली_bus_get_drvdata(&dev->sbd);
	priv = shost_priv(host);
	cmd = priv->curr_cmd;

	अगर (!status) अणु
		/* OK, completed */
		अगर (cmd->sc_data_direction == DMA_FROM_DEVICE) अणु
			पूर्णांक len;

			len = scsi_sg_copy_from_buffer(cmd,
						       dev->bounce_buf,
						       dev->bounce_size);

			scsi_set_resid(cmd, scsi_bufflen(cmd) - len);
		पूर्ण
		cmd->result = DID_OK << 16;
		जाओ करोne;
	पूर्ण

	अगर (cmd->cmnd[0] == REQUEST_SENSE) अणु
		/* SCSI spec says request sense should never get error */
		dev_err(&dev->sbd.core, "%s:%u: end error without autosense\n",
			__func__, __LINE__);
		cmd->result = DID_ERROR << 16 | SAM_STAT_CHECK_CONDITION;
		जाओ करोne;
	पूर्ण

	अगर (decode_lv1_status(status, &sense_key, &asc, &ascq)) अणु
		cmd->result = DID_ERROR << 16;
		जाओ करोne;
	पूर्ण

	scsi_build_sense_buffer(0, cmd->sense_buffer, sense_key, asc, ascq);
	cmd->result = SAM_STAT_CHECK_CONDITION;

करोne:
	priv->curr_cmd = शून्य;
	cmd->scsi_करोne(cmd);
	वापस IRQ_HANDLED;
पूर्ण

अटल काष्ठा scsi_host_ढाँचा ps3rom_host_ढाँचा = अणु
	.name =			DEVICE_NAME,
	.slave_configure =	ps3rom_slave_configure,
	.queuecommand =		ps3rom_queuecommand,
	.can_queue =		1,
	.this_id =		7,
	.sg_tablesize =		SG_ALL,
	.emulated =             1,		/* only sg driver uses this */
	.max_sectors =		PS3ROM_MAX_SECTORS,
	.module =		THIS_MODULE,
पूर्ण;


अटल पूर्णांक ps3rom_probe(काष्ठा ps3_प्रणाली_bus_device *_dev)
अणु
	काष्ठा ps3_storage_device *dev = to_ps3_storage_device(&_dev->core);
	पूर्णांक error;
	काष्ठा Scsi_Host *host;
	काष्ठा ps3rom_निजी *priv;

	अगर (dev->blk_size != CD_FRAMESIZE) अणु
		dev_err(&dev->sbd.core,
			"%s:%u: cannot handle block size %llu\n", __func__,
			__LINE__, dev->blk_size);
		वापस -EINVAL;
	पूर्ण

	dev->bounce_size = BOUNCE_SIZE;
	dev->bounce_buf = kदो_स्मृति(BOUNCE_SIZE, GFP_DMA);
	अगर (!dev->bounce_buf)
		वापस -ENOMEM;

	error = ps3stor_setup(dev, ps3rom_पूर्णांकerrupt);
	अगर (error)
		जाओ fail_मुक्त_bounce;

	host = scsi_host_alloc(&ps3rom_host_ढाँचा,
			       माप(काष्ठा ps3rom_निजी));
	अगर (!host) अणु
		dev_err(&dev->sbd.core, "%s:%u: scsi_host_alloc failed\n",
			__func__, __LINE__);
		error = -ENOMEM;
		जाओ fail_tearकरोwn;
	पूर्ण

	priv = shost_priv(host);
	ps3_प्रणाली_bus_set_drvdata(&dev->sbd, host);
	priv->dev = dev;

	/* One device/LUN per SCSI bus */
	host->max_id = 1;
	host->max_lun = 1;

	error = scsi_add_host(host, &dev->sbd.core);
	अगर (error) अणु
		dev_err(&dev->sbd.core, "%s:%u: scsi_host_alloc failed %d\n",
			__func__, __LINE__, error);
		error = -ENODEV;
		जाओ fail_host_put;
	पूर्ण

	scsi_scan_host(host);
	वापस 0;

fail_host_put:
	scsi_host_put(host);
	ps3_प्रणाली_bus_set_drvdata(&dev->sbd, शून्य);
fail_tearकरोwn:
	ps3stor_tearकरोwn(dev);
fail_मुक्त_bounce:
	kमुक्त(dev->bounce_buf);
	वापस error;
पूर्ण

अटल व्योम ps3rom_हटाओ(काष्ठा ps3_प्रणाली_bus_device *_dev)
अणु
	काष्ठा ps3_storage_device *dev = to_ps3_storage_device(&_dev->core);
	काष्ठा Scsi_Host *host = ps3_प्रणाली_bus_get_drvdata(&dev->sbd);

	scsi_हटाओ_host(host);
	ps3stor_tearकरोwn(dev);
	scsi_host_put(host);
	ps3_प्रणाली_bus_set_drvdata(&dev->sbd, शून्य);
	kमुक्त(dev->bounce_buf);
पूर्ण

अटल काष्ठा ps3_प्रणाली_bus_driver ps3rom = अणु
	.match_id	= PS3_MATCH_ID_STOR_ROM,
	.core.name	= DEVICE_NAME,
	.core.owner	= THIS_MODULE,
	.probe		= ps3rom_probe,
	.हटाओ		= ps3rom_हटाओ
पूर्ण;


अटल पूर्णांक __init ps3rom_init(व्योम)
अणु
	वापस ps3_प्रणाली_bus_driver_रेजिस्टर(&ps3rom);
पूर्ण

अटल व्योम __निकास ps3rom_निकास(व्योम)
अणु
	ps3_प्रणाली_bus_driver_unरेजिस्टर(&ps3rom);
पूर्ण

module_init(ps3rom_init);
module_निकास(ps3rom_निकास);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("PS3 BD/DVD/CD-ROM Storage Driver");
MODULE_AUTHOR("Sony Corporation");
MODULE_ALIAS(PS3_MODULE_ALIAS_STOR_ROM);
