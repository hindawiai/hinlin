<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
    Driver क्रम SAA6588 RDS decoder

    (c) 2005 Hans J. Koch

*/


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/i2c.h>
#समावेश <linux/types.h>
#समावेश <linux/videodev2.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/रुको.h>
#समावेश <linux/uaccess.h>

#समावेश <media/i2c/saa6588.h>
#समावेश <media/v4l2-device.h>


/* insmod options */
अटल अचिन्हित पूर्णांक debug;
अटल अचिन्हित पूर्णांक xtal;
अटल अचिन्हित पूर्णांक mmbs;
अटल अचिन्हित पूर्णांक plvl;
अटल अचिन्हित पूर्णांक bufblocks = 100;

module_param(debug, पूर्णांक, 0644);
MODULE_PARM_DESC(debug, "enable debug messages");
module_param(xtal, पूर्णांक, 0);
MODULE_PARM_DESC(xtal, "select oscillator frequency (0..3), default 0");
module_param(mmbs, पूर्णांक, 0);
MODULE_PARM_DESC(mmbs, "enable MMBS mode: 0=off (default), 1=on");
module_param(plvl, पूर्णांक, 0);
MODULE_PARM_DESC(plvl, "select pause level (0..3), default 0");
module_param(bufblocks, पूर्णांक, 0);
MODULE_PARM_DESC(bufblocks, "number of buffered blocks, default 100");

MODULE_DESCRIPTION("v4l2 driver module for SAA6588 RDS decoder");
MODULE_AUTHOR("Hans J. Koch <koch@hjk-az.de>");

MODULE_LICENSE("GPL");

/* ---------------------------------------------------------------------- */

#घोषणा UNSET       (-1U)
#घोषणा PREFIX      "saa6588: "
#घोषणा dprपूर्णांकk     अगर (debug) prपूर्णांकk

काष्ठा saa6588 अणु
	काष्ठा v4l2_subdev sd;
	काष्ठा delayed_work work;
	spinlock_t lock;
	अचिन्हित अक्षर *buffer;
	अचिन्हित पूर्णांक buf_size;
	अचिन्हित पूर्णांक rd_index;
	अचिन्हित पूर्णांक wr_index;
	अचिन्हित पूर्णांक block_count;
	अचिन्हित अक्षर last_blocknum;
	रुको_queue_head_t पढ़ो_queue;
	पूर्णांक data_available_क्रम_पढ़ो;
	u8 sync;
पूर्ण;

अटल अंतरभूत काष्ठा saa6588 *to_saa6588(काष्ठा v4l2_subdev *sd)
अणु
	वापस container_of(sd, काष्ठा saa6588, sd);
पूर्ण

/* ---------------------------------------------------------------------- */

/*
 * SAA6588 defines
 */

/* Initialization and mode control byte (0w) */

/* bit 0+1 (DAC0/DAC1) */
#घोषणा cModeStandard           0x00
#घोषणा cModeFastPI             0x01
#घोषणा cModeReducedRequest     0x02
#घोषणा cModeInvalid            0x03

/* bit 2 (RBDS) */
#घोषणा cProcessingModeRDS      0x00
#घोषणा cProcessingModeRBDS     0x04

/* bit 3+4 (SYM0/SYM1) */
#घोषणा cErrCorrectionNone      0x00
#घोषणा cErrCorrection2Bits     0x08
#घोषणा cErrCorrection5Bits     0x10
#घोषणा cErrCorrectionNoneRBDS  0x18

/* bit 5 (NWSY) */
#घोषणा cSyncNormal             0x00
#घोषणा cSyncRestart            0x20

/* bit 6 (TSQD) */
#घोषणा cSigQualityDetectOFF    0x00
#घोषणा cSigQualityDetectON     0x40

/* bit 7 (SQCM) */
#घोषणा cSigQualityTriggered    0x00
#घोषणा cSigQualityContinous    0x80

/* Pause level and flywheel control byte (1w) */

/* bits 0..5 (FEB0..FEB5) */
#घोषणा cFlywheelMaxBlocksMask  0x3F
#घोषणा cFlywheelDefault        0x20

/* bits 6+7 (PL0/PL1) */
#घोषणा cPauseLevel_11mV	0x00
#घोषणा cPauseLevel_17mV        0x40
#घोषणा cPauseLevel_27mV        0x80
#घोषणा cPauseLevel_43mV        0xC0

/* Pause समय/oscillator frequency/quality detector control byte (1w) */

/* bits 0..4 (SQS0..SQS4) */
#घोषणा cQualityDetectSensMask  0x1F
#घोषणा cQualityDetectDefault   0x0F

/* bit 5 (SOSC) */
#घोषणा cSelectOscFreqOFF	0x00
#घोषणा cSelectOscFreqON	0x20

/* bit 6+7 (PTF0/PTF1) */
#घोषणा cOscFreq_4332kHz	0x00
#घोषणा cOscFreq_8664kHz	0x40
#घोषणा cOscFreq_12996kHz	0x80
#घोषणा cOscFreq_17328kHz	0xC0

/* ---------------------------------------------------------------------- */

अटल bool block_from_buf(काष्ठा saa6588 *s, अचिन्हित अक्षर *buf)
अणु
	पूर्णांक i;

	अगर (s->rd_index == s->wr_index) अणु
		अगर (debug > 2)
			dprपूर्णांकk(PREFIX "Read: buffer empty.\n");
		वापस false;
	पूर्ण

	अगर (debug > 2) अणु
		dprपूर्णांकk(PREFIX "Read: ");
		क्रम (i = s->rd_index; i < s->rd_index + 3; i++)
			dprपूर्णांकk("0x%02x ", s->buffer[i]);
	पूर्ण

	स_नकल(buf, &s->buffer[s->rd_index], 3);

	s->rd_index += 3;
	अगर (s->rd_index >= s->buf_size)
		s->rd_index = 0;
	s->block_count--;

	अगर (debug > 2)
		dprपूर्णांकk("%d blocks total.\n", s->block_count);

	वापस true;
पूर्ण

अटल व्योम पढ़ो_from_buf(काष्ठा saa6588 *s, काष्ठा saa6588_command *a)
अणु
	अचिन्हित अक्षर __user *buf_ptr = a->buffer;
	अचिन्हित अक्षर buf[3];
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक rd_blocks;
	अचिन्हित पूर्णांक i;

	a->result = 0;
	अगर (!a->buffer)
		वापस;

	जबतक (!a->nonblocking && !s->data_available_क्रम_पढ़ो) अणु
		पूर्णांक ret = रुको_event_पूर्णांकerruptible(s->पढ़ो_queue,
					     s->data_available_क्रम_पढ़ो);
		अगर (ret == -ERESTARTSYS) अणु
			a->result = -EINTR;
			वापस;
		पूर्ण
	पूर्ण

	rd_blocks = a->block_count;
	spin_lock_irqsave(&s->lock, flags);
	अगर (rd_blocks > s->block_count)
		rd_blocks = s->block_count;
	spin_unlock_irqrestore(&s->lock, flags);

	अगर (!rd_blocks)
		वापस;

	क्रम (i = 0; i < rd_blocks; i++) अणु
		bool got_block;

		spin_lock_irqsave(&s->lock, flags);
		got_block = block_from_buf(s, buf);
		spin_unlock_irqrestore(&s->lock, flags);
		अगर (!got_block)
			अवरोध;
		अगर (copy_to_user(buf_ptr, buf, 3)) अणु
			a->result = -EFAULT;
			वापस;
		पूर्ण
		buf_ptr += 3;
		a->result += 3;
	पूर्ण
	spin_lock_irqsave(&s->lock, flags);
	s->data_available_क्रम_पढ़ो = (s->block_count > 0);
	spin_unlock_irqrestore(&s->lock, flags);
पूर्ण

अटल व्योम block_to_buf(काष्ठा saa6588 *s, अचिन्हित अक्षर *blockbuf)
अणु
	अचिन्हित पूर्णांक i;

	अगर (debug > 3)
		dprपूर्णांकk(PREFIX "New block: ");

	क्रम (i = 0; i < 3; ++i) अणु
		अगर (debug > 3)
			dprपूर्णांकk("0x%02x ", blockbuf[i]);
		s->buffer[s->wr_index] = blockbuf[i];
		s->wr_index++;
	पूर्ण

	अगर (s->wr_index >= s->buf_size)
		s->wr_index = 0;

	अगर (s->wr_index == s->rd_index) अणु
		s->rd_index += 3;
		अगर (s->rd_index >= s->buf_size)
			s->rd_index = 0;
	पूर्ण अन्यथा
		s->block_count++;

	अगर (debug > 3)
		dprपूर्णांकk("%d blocks total.\n", s->block_count);
पूर्ण

अटल व्योम saa6588_i2c_poll(काष्ठा saa6588 *s)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&s->sd);
	अचिन्हित दीर्घ flags;
	अचिन्हित अक्षर पंचांगpbuf[6];
	अचिन्हित अक्षर blocknum;
	अचिन्हित अक्षर पंचांगp;

	/* Although we only need 3 bytes, we have to पढ़ो at least 6.
	   SAA6588 वापसs garbage otherwise. */
	अगर (6 != i2c_master_recv(client, &पंचांगpbuf[0], 6)) अणु
		अगर (debug > 1)
			dprपूर्णांकk(PREFIX "read error!\n");
		वापस;
	पूर्ण

	s->sync = पंचांगpbuf[0] & 0x10;
	अगर (!s->sync)
		वापस;
	blocknum = पंचांगpbuf[0] >> 5;
	अगर (blocknum == s->last_blocknum) अणु
		अगर (debug > 3)
			dprपूर्णांकk("Saw block %d again.\n", blocknum);
		वापस;
	पूर्ण

	s->last_blocknum = blocknum;

	/*
	   Byte order according to v4l2 specअगरication:

	   Byte 0: Least Signअगरicant Byte of RDS Block
	   Byte 1: Most Signअगरicant Byte of RDS Block
	   Byte 2 Bit 7: Error bit. Indicates that an uncorrectable error
	   occurred during reception of this block.
	   Bit 6: Corrected bit. Indicates that an error was
	   corrected क्रम this data block.
	   Bits 5-3: Same as bits 0-2.
	   Bits 2-0: Block number.

	   SAA6588 byte order is Status-MSB-LSB, so we have to swap the
	   first and the last of the 3 bytes block.
	 */

	swap(पंचांगpbuf[2], पंचांगpbuf[0]);

	/* Map 'Invalid block E' to 'Invalid Block' */
	अगर (blocknum == 6)
		blocknum = V4L2_RDS_BLOCK_INVALID;
	/* And अगर are not in mmbs mode, then 'Block E' is also mapped
	   to 'Invalid Block'. As far as I can tell MMBS is disजारीd,
	   and अगर there is ever a need to support E blocks, then please
	   contact the linux-media mailinglist. */
	अन्यथा अगर (!mmbs && blocknum == 5)
		blocknum = V4L2_RDS_BLOCK_INVALID;
	पंचांगp = blocknum;
	पंचांगp |= blocknum << 3;	/* Received offset == Offset Name (OK ?) */
	अगर ((पंचांगpbuf[2] & 0x03) == 0x03)
		पंचांगp |= V4L2_RDS_BLOCK_ERROR;	 /* uncorrectable error */
	अन्यथा अगर ((पंचांगpbuf[2] & 0x03) != 0x00)
		पंचांगp |= V4L2_RDS_BLOCK_CORRECTED; /* corrected error */
	पंचांगpbuf[2] = पंचांगp;	/* Is this enough ? Should we also check other bits ? */

	spin_lock_irqsave(&s->lock, flags);
	block_to_buf(s, पंचांगpbuf);
	spin_unlock_irqrestore(&s->lock, flags);
	s->data_available_क्रम_पढ़ो = 1;
	wake_up_पूर्णांकerruptible(&s->पढ़ो_queue);
पूर्ण

अटल व्योम saa6588_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा saa6588 *s = container_of(work, काष्ठा saa6588, work.work);

	saa6588_i2c_poll(s);
	schedule_delayed_work(&s->work, msecs_to_jअगरfies(20));
पूर्ण

अटल व्योम saa6588_configure(काष्ठा saa6588 *s)
अणु
	काष्ठा i2c_client *client = v4l2_get_subdevdata(&s->sd);
	अचिन्हित अक्षर buf[3];
	पूर्णांक rc;

	buf[0] = cSyncRestart;
	अगर (mmbs)
		buf[0] |= cProcessingModeRBDS;

	buf[1] = cFlywheelDefault;
	चयन (plvl) अणु
	हाल 0:
		buf[1] |= cPauseLevel_11mV;
		अवरोध;
	हाल 1:
		buf[1] |= cPauseLevel_17mV;
		अवरोध;
	हाल 2:
		buf[1] |= cPauseLevel_27mV;
		अवरोध;
	हाल 3:
		buf[1] |= cPauseLevel_43mV;
		अवरोध;
	शेष:		/* nothing */
		अवरोध;
	पूर्ण

	buf[2] = cQualityDetectDefault | cSelectOscFreqON;

	चयन (xtal) अणु
	हाल 0:
		buf[2] |= cOscFreq_4332kHz;
		अवरोध;
	हाल 1:
		buf[2] |= cOscFreq_8664kHz;
		अवरोध;
	हाल 2:
		buf[2] |= cOscFreq_12996kHz;
		अवरोध;
	हाल 3:
		buf[2] |= cOscFreq_17328kHz;
		अवरोध;
	शेष:		/* nothing */
		अवरोध;
	पूर्ण

	dprपूर्णांकk(PREFIX "writing: 0w=0x%02x 1w=0x%02x 2w=0x%02x\n",
		buf[0], buf[1], buf[2]);

	rc = i2c_master_send(client, buf, 3);
	अगर (rc != 3)
		prपूर्णांकk(PREFIX "i2c i/o error: rc == %d (should be 3)\n", rc);
पूर्ण

/* ---------------------------------------------------------------------- */

अटल दीर्घ saa6588_ioctl(काष्ठा v4l2_subdev *sd, अचिन्हित पूर्णांक cmd, व्योम *arg)
अणु
	काष्ठा saa6588 *s = to_saa6588(sd);
	काष्ठा saa6588_command *a = arg;

	चयन (cmd) अणु
		/* --- बंद() क्रम /dev/radio --- */
	हाल SAA6588_CMD_CLOSE:
		s->data_available_क्रम_पढ़ो = 1;
		wake_up_पूर्णांकerruptible(&s->पढ़ो_queue);
		s->data_available_क्रम_पढ़ो = 0;
		a->result = 0;
		अवरोध;
		/* --- पढ़ो() क्रम /dev/radio --- */
	हाल SAA6588_CMD_READ:
		पढ़ो_from_buf(s, a);
		अवरोध;
		/* --- poll() क्रम /dev/radio --- */
	हाल SAA6588_CMD_POLL:
		a->poll_mask = 0;
		अगर (s->data_available_क्रम_पढ़ो)
			a->poll_mask |= EPOLLIN | EPOLLRDNORM;
		poll_रुको(a->instance, &s->पढ़ो_queue, a->event_list);
		अवरोध;

	शेष:
		/* nothing */
		वापस -ENOIOCTLCMD;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक saa6588_g_tuner(काष्ठा v4l2_subdev *sd, काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा saa6588 *s = to_saa6588(sd);

	vt->capability |= V4L2_TUNER_CAP_RDS | V4L2_TUNER_CAP_RDS_BLOCK_IO;
	अगर (s->sync)
		vt->rxsubchans |= V4L2_TUNER_SUB_RDS;
	वापस 0;
पूर्ण

अटल पूर्णांक saa6588_s_tuner(काष्ठा v4l2_subdev *sd, स्थिर काष्ठा v4l2_tuner *vt)
अणु
	काष्ठा saa6588 *s = to_saa6588(sd);

	saa6588_configure(s);
	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा v4l2_subdev_core_ops saa6588_core_ops = अणु
	.ioctl = saa6588_ioctl,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_tuner_ops saa6588_tuner_ops = अणु
	.g_tuner = saa6588_g_tuner,
	.s_tuner = saa6588_s_tuner,
पूर्ण;

अटल स्थिर काष्ठा v4l2_subdev_ops saa6588_ops = अणु
	.core = &saa6588_core_ops,
	.tuner = &saa6588_tuner_ops,
पूर्ण;

/* ---------------------------------------------------------------------- */

अटल पूर्णांक saa6588_probe(काष्ठा i2c_client *client,
			 स्थिर काष्ठा i2c_device_id *id)
अणु
	काष्ठा saa6588 *s;
	काष्ठा v4l2_subdev *sd;

	v4l_info(client, "saa6588 found @ 0x%x (%s)\n",
			client->addr << 1, client->adapter->name);

	s = devm_kzalloc(&client->dev, माप(*s), GFP_KERNEL);
	अगर (s == शून्य)
		वापस -ENOMEM;

	s->buf_size = bufblocks * 3;

	s->buffer = devm_kzalloc(&client->dev, s->buf_size, GFP_KERNEL);
	अगर (s->buffer == शून्य)
		वापस -ENOMEM;
	sd = &s->sd;
	v4l2_i2c_subdev_init(sd, client, &saa6588_ops);
	spin_lock_init(&s->lock);
	s->block_count = 0;
	s->wr_index = 0;
	s->rd_index = 0;
	s->last_blocknum = 0xff;
	init_रुकोqueue_head(&s->पढ़ो_queue);
	s->data_available_क्रम_पढ़ो = 0;

	saa6588_configure(s);

	/* start polling via eventd */
	INIT_DELAYED_WORK(&s->work, saa6588_work);
	schedule_delayed_work(&s->work, 0);
	वापस 0;
पूर्ण

अटल पूर्णांक saa6588_हटाओ(काष्ठा i2c_client *client)
अणु
	काष्ठा v4l2_subdev *sd = i2c_get_clientdata(client);
	काष्ठा saa6588 *s = to_saa6588(sd);

	v4l2_device_unरेजिस्टर_subdev(sd);

	cancel_delayed_work_sync(&s->work);

	वापस 0;
पूर्ण

/* ----------------------------------------------------------------------- */

अटल स्थिर काष्ठा i2c_device_id saa6588_id[] = अणु
	अणु "saa6588", 0 पूर्ण,
	अणु पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(i2c, saa6588_id);

अटल काष्ठा i2c_driver saa6588_driver = अणु
	.driver = अणु
		.name	= "saa6588",
	पूर्ण,
	.probe		= saa6588_probe,
	.हटाओ		= saa6588_हटाओ,
	.id_table	= saa6588_id,
पूर्ण;

module_i2c_driver(saa6588_driver);
