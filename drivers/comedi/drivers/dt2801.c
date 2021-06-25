<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * comedi/drivers/dt2801.c
 * Device Driver क्रम DataTranslation DT2801
 *
 */
/*
 * Driver: dt2801
 * Description: Data Translation DT2801 series and DT01-EZ
 * Author: ds
 * Status: works
 * Devices: [Data Translation] DT2801 (dt2801), DT2801-A, DT2801/5716A,
 * DT2805, DT2805/5716A, DT2808, DT2818, DT2809, DT01-EZ
 *
 * This driver can स्वतःprobe the type of board.
 *
 * Configuration options:
 * [0] - I/O port base address
 * [1] - unused
 * [2] - A/D reference 0=dअगरferential, 1=single-ended
 * [3] - A/D range
 *	  0 = [-10, 10]
 *	  1 = [0,10]
 * [4] - D/A 0 range
 *	  0 = [-10, 10]
 *	  1 = [-5,5]
 *	  2 = [-2.5,2.5]
 *	  3 = [0,10]
 *	  4 = [0,5]
 * [5] - D/A 1 range (same choices)
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"
#समावेश <linux/delay.h>

#घोषणा DT2801_TIMEOUT 1000

/* Hardware Configuration */
/* ====================== */

#घोषणा DT2801_MAX_DMA_SIZE (64 * 1024)

/* define's */
/* ====================== */

/* Commands */
#घोषणा DT_C_RESET       0x0
#घोषणा DT_C_CLEAR_ERR   0x1
#घोषणा DT_C_READ_ERRREG 0x2
#घोषणा DT_C_SET_CLOCK   0x3

#घोषणा DT_C_TEST        0xb
#घोषणा DT_C_STOP        0xf

#घोषणा DT_C_SET_DIGIN   0x4
#घोषणा DT_C_SET_DIGOUT  0x5
#घोषणा DT_C_READ_DIG    0x6
#घोषणा DT_C_WRITE_DIG   0x7

#घोषणा DT_C_WRITE_DAIM  0x8
#घोषणा DT_C_SET_DA      0x9
#घोषणा DT_C_WRITE_DA    0xa

#घोषणा DT_C_READ_ADIM   0xc
#घोषणा DT_C_SET_AD      0xd
#घोषणा DT_C_READ_AD     0xe

/*
 * Command modअगरiers (only used with पढ़ो/ग_लिखो), EXTTRIG can be
 * used with some other commands.
 */
#घोषणा DT_MOD_DMA     BIT(4)
#घोषणा DT_MOD_CONT    BIT(5)
#घोषणा DT_MOD_EXTCLK  BIT(6)
#घोषणा DT_MOD_EXTTRIG BIT(7)

/* Bits in status रेजिस्टर */
#घोषणा DT_S_DATA_OUT_READY   BIT(0)
#घोषणा DT_S_DATA_IN_FULL     BIT(1)
#घोषणा DT_S_READY            BIT(2)
#घोषणा DT_S_COMMAND          BIT(3)
#घोषणा DT_S_COMPOSITE_ERROR  BIT(7)

/* रेजिस्टरs */
#घोषणा DT2801_DATA		0
#घोषणा DT2801_STATUS		1
#घोषणा DT2801_CMD		1

#अगर 0
/* ignore 'defined but not used' warning */
अटल स्थिर काष्ठा comedi_lrange range_dt2801_ai_pgh_bipolar = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(5),
		BIP_RANGE(2.5),
		BIP_RANGE(1.25)
	पूर्ण
पूर्ण;
#पूर्ण_अगर
अटल स्थिर काष्ठा comedi_lrange range_dt2801_ai_pgl_bipolar = अणु
	4, अणु
		BIP_RANGE(10),
		BIP_RANGE(1),
		BIP_RANGE(0.1),
		BIP_RANGE(0.02)
	पूर्ण
पूर्ण;

#अगर 0
/* ignore 'defined but not used' warning */
अटल स्थिर काष्ठा comedi_lrange range_dt2801_ai_pgh_unipolar = अणु
	4, अणु
		UNI_RANGE(10),
		UNI_RANGE(5),
		UNI_RANGE(2.5),
		UNI_RANGE(1.25)
	पूर्ण
पूर्ण;
#पूर्ण_अगर
अटल स्थिर काष्ठा comedi_lrange range_dt2801_ai_pgl_unipolar = अणु
	4, अणु
		UNI_RANGE(10),
		UNI_RANGE(1),
		UNI_RANGE(0.1),
		UNI_RANGE(0.02)
	पूर्ण
पूर्ण;

काष्ठा dt2801_board अणु
	स्थिर अक्षर *name;
	पूर्णांक boardcode;
	पूर्णांक ad_dअगरf;
	पूर्णांक ad_chan;
	पूर्णांक adbits;
	पूर्णांक adrangetype;
	पूर्णांक dabits;
पूर्ण;

/*
 * Typeid's क्रम the dअगरferent boards of the DT2801-series
 * (taken from the test-software, that comes with the board)
 */
अटल स्थिर काष्ठा dt2801_board boardtypes[] = अणु
	अणु
	 .name = "dt2801",
	 .boardcode = 0x09,
	 .ad_dअगरf = 2,
	 .ad_chan = 16,
	 .adbits = 12,
	 .adrangetype = 0,
	 .dabits = 12पूर्ण,
	अणु
	 .name = "dt2801-a",
	 .boardcode = 0x52,
	 .ad_dअगरf = 2,
	 .ad_chan = 16,
	 .adbits = 12,
	 .adrangetype = 0,
	 .dabits = 12पूर्ण,
	अणु
	 .name = "dt2801/5716a",
	 .boardcode = 0x82,
	 .ad_dअगरf = 1,
	 .ad_chan = 16,
	 .adbits = 16,
	 .adrangetype = 1,
	 .dabits = 12पूर्ण,
	अणु
	 .name = "dt2805",
	 .boardcode = 0x12,
	 .ad_dअगरf = 1,
	 .ad_chan = 16,
	 .adbits = 12,
	 .adrangetype = 0,
	 .dabits = 12पूर्ण,
	अणु
	 .name = "dt2805/5716a",
	 .boardcode = 0x92,
	 .ad_dअगरf = 1,
	 .ad_chan = 16,
	 .adbits = 16,
	 .adrangetype = 1,
	 .dabits = 12पूर्ण,
	अणु
	 .name = "dt2808",
	 .boardcode = 0x20,
	 .ad_dअगरf = 0,
	 .ad_chan = 16,
	 .adbits = 12,
	 .adrangetype = 2,
	 .dabits = 8पूर्ण,
	अणु
	 .name = "dt2818",
	 .boardcode = 0xa2,
	 .ad_dअगरf = 0,
	 .ad_chan = 4,
	 .adbits = 12,
	 .adrangetype = 0,
	 .dabits = 12पूर्ण,
	अणु
	 .name = "dt2809",
	 .boardcode = 0xb0,
	 .ad_dअगरf = 0,
	 .ad_chan = 8,
	 .adbits = 12,
	 .adrangetype = 1,
	 .dabits = 12पूर्ण,
पूर्ण;

काष्ठा dt2801_निजी अणु
	स्थिर काष्ठा comedi_lrange *dac_range_types[2];
पूर्ण;

/*
 * These are the low-level routines:
 * ग_लिखोcommand: ग_लिखो a command to the board
 * ग_लिखोdata: ग_लिखो data byte
 * पढ़ोdata: पढ़ो data byte
 */

/*
 * Only checks DataOutReady-flag, not the Ready-flag as it is करोne
 *  in the examples of the manual. I करोn't see why this should be
 *  necessary.
 */
अटल पूर्णांक dt2801_पढ़ोdata(काष्ठा comedi_device *dev, पूर्णांक *data)
अणु
	पूर्णांक stat = 0;
	पूर्णांक समयout = DT2801_TIMEOUT;

	करो अणु
		stat = inb_p(dev->iobase + DT2801_STATUS);
		अगर (stat & (DT_S_COMPOSITE_ERROR | DT_S_READY))
			वापस stat;
		अगर (stat & DT_S_DATA_OUT_READY) अणु
			*data = inb_p(dev->iobase + DT2801_DATA);
			वापस 0;
		पूर्ण
	पूर्ण जबतक (--समयout > 0);

	वापस -ETIME;
पूर्ण

अटल पूर्णांक dt2801_पढ़ोdata2(काष्ठा comedi_device *dev, पूर्णांक *data)
अणु
	पूर्णांक lb = 0;
	पूर्णांक hb = 0;
	पूर्णांक ret;

	ret = dt2801_पढ़ोdata(dev, &lb);
	अगर (ret)
		वापस ret;
	ret = dt2801_पढ़ोdata(dev, &hb);
	अगर (ret)
		वापस ret;

	*data = (hb << 8) + lb;
	वापस 0;
पूर्ण

अटल पूर्णांक dt2801_ग_लिखोdata(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक data)
अणु
	पूर्णांक stat = 0;
	पूर्णांक समयout = DT2801_TIMEOUT;

	करो अणु
		stat = inb_p(dev->iobase + DT2801_STATUS);

		अगर (stat & DT_S_COMPOSITE_ERROR)
			वापस stat;
		अगर (!(stat & DT_S_DATA_IN_FULL)) अणु
			outb_p(data & 0xff, dev->iobase + DT2801_DATA);
			वापस 0;
		पूर्ण
	पूर्ण जबतक (--समयout > 0);

	वापस -ETIME;
पूर्ण

अटल पूर्णांक dt2801_ग_लिखोdata2(काष्ठा comedi_device *dev, अचिन्हित पूर्णांक data)
अणु
	पूर्णांक ret;

	ret = dt2801_ग_लिखोdata(dev, data & 0xff);
	अगर (ret < 0)
		वापस ret;
	ret = dt2801_ग_लिखोdata(dev, data >> 8);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक dt2801_रुको_क्रम_पढ़ोy(काष्ठा comedi_device *dev)
अणु
	पूर्णांक समयout = DT2801_TIMEOUT;
	पूर्णांक stat;

	stat = inb_p(dev->iobase + DT2801_STATUS);
	अगर (stat & DT_S_READY)
		वापस 0;
	करो अणु
		stat = inb_p(dev->iobase + DT2801_STATUS);

		अगर (stat & DT_S_COMPOSITE_ERROR)
			वापस stat;
		अगर (stat & DT_S_READY)
			वापस 0;
	पूर्ण जबतक (--समयout > 0);

	वापस -ETIME;
पूर्ण

अटल व्योम dt2801_ग_लिखोcmd(काष्ठा comedi_device *dev, पूर्णांक command)
अणु
	पूर्णांक stat;

	dt2801_रुको_क्रम_पढ़ोy(dev);

	stat = inb_p(dev->iobase + DT2801_STATUS);
	अगर (stat & DT_S_COMPOSITE_ERROR) अणु
		dev_dbg(dev->class_dev,
			"composite-error in %s, ignoring\n", __func__);
	पूर्ण
	अगर (!(stat & DT_S_READY))
		dev_dbg(dev->class_dev, "!ready in %s, ignoring\n", __func__);
	outb_p(command, dev->iobase + DT2801_CMD);
पूर्ण

अटल पूर्णांक dt2801_reset(काष्ठा comedi_device *dev)
अणु
	पूर्णांक board_code = 0;
	अचिन्हित पूर्णांक stat;
	पूर्णांक समयout;

	/* pull अक्रमom data from data port */
	inb_p(dev->iobase + DT2801_DATA);
	inb_p(dev->iobase + DT2801_DATA);
	inb_p(dev->iobase + DT2801_DATA);
	inb_p(dev->iobase + DT2801_DATA);

	/* dt2801_ग_लिखोcmd(dev,DT_C_STOP); */
	outb_p(DT_C_STOP, dev->iobase + DT2801_CMD);

	/* dt2801_रुको_क्रम_पढ़ोy(dev); */
	usleep_range(100, 200);
	समयout = 10000;
	करो अणु
		stat = inb_p(dev->iobase + DT2801_STATUS);
		अगर (stat & DT_S_READY)
			अवरोध;
	पूर्ण जबतक (समयout--);
	अगर (!समयout)
		dev_dbg(dev->class_dev, "timeout 1 status=0x%02x\n", stat);

	/* dt2801_पढ़ोdata(dev,&board_code); */

	outb_p(DT_C_RESET, dev->iobase + DT2801_CMD);
	/* dt2801_ग_लिखोcmd(dev,DT_C_RESET); */

	usleep_range(100, 200);
	समयout = 10000;
	करो अणु
		stat = inb_p(dev->iobase + DT2801_STATUS);
		अगर (stat & DT_S_READY)
			अवरोध;
	पूर्ण जबतक (समयout--);
	अगर (!समयout)
		dev_dbg(dev->class_dev, "timeout 2 status=0x%02x\n", stat);

	dt2801_पढ़ोdata(dev, &board_code);

	वापस board_code;
पूर्ण

अटल पूर्णांक probe_number_of_ai_chans(काष्ठा comedi_device *dev)
अणु
	पूर्णांक n_chans;
	पूर्णांक stat;
	पूर्णांक data;

	क्रम (n_chans = 0; n_chans < 16; n_chans++) अणु
		dt2801_ग_लिखोcmd(dev, DT_C_READ_ADIM);
		dt2801_ग_लिखोdata(dev, 0);
		dt2801_ग_लिखोdata(dev, n_chans);
		stat = dt2801_पढ़ोdata2(dev, &data);

		अगर (stat)
			अवरोध;
	पूर्ण

	dt2801_reset(dev);
	dt2801_reset(dev);

	वापस n_chans;
पूर्ण

अटल स्थिर काष्ठा comedi_lrange *dac_range_table[] = अणु
	&range_bipolar10,
	&range_bipolar5,
	&range_bipolar2_5,
	&range_unipolar10,
	&range_unipolar5
पूर्ण;

अटल स्थिर काष्ठा comedi_lrange *dac_range_lkup(पूर्णांक opt)
अणु
	अगर (opt < 0 || opt >= 5)
		वापस &range_unknown;
	वापस dac_range_table[opt];
पूर्ण

अटल स्थिर काष्ठा comedi_lrange *ai_range_lkup(पूर्णांक type, पूर्णांक opt)
अणु
	चयन (type) अणु
	हाल 0:
		वापस (opt) ?
		    &range_dt2801_ai_pgl_unipolar :
		    &range_dt2801_ai_pgl_bipolar;
	हाल 1:
		वापस (opt) ? &range_unipolar10 : &range_bipolar10;
	हाल 2:
		वापस &range_unipolar5;
	पूर्ण
	वापस &range_unknown;
पूर्ण

अटल पूर्णांक dt2801_error(काष्ठा comedi_device *dev, पूर्णांक stat)
अणु
	अगर (stat < 0) अणु
		अगर (stat == -ETIME)
			dev_dbg(dev->class_dev, "timeout\n");
		अन्यथा
			dev_dbg(dev->class_dev, "error %d\n", stat);
		वापस stat;
	पूर्ण
	dev_dbg(dev->class_dev, "error status 0x%02x, resetting...\n", stat);

	dt2801_reset(dev);
	dt2801_reset(dev);

	वापस -EIO;
पूर्ण

अटल पूर्णांक dt2801_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक d;
	पूर्णांक stat;
	पूर्णांक i;

	क्रम (i = 0; i < insn->n; i++) अणु
		dt2801_ग_लिखोcmd(dev, DT_C_READ_ADIM);
		dt2801_ग_लिखोdata(dev, CR_RANGE(insn->chanspec));
		dt2801_ग_लिखोdata(dev, CR_CHAN(insn->chanspec));
		stat = dt2801_पढ़ोdata2(dev, &d);

		अगर (stat != 0)
			वापस dt2801_error(dev, stat);

		data[i] = d;
	पूर्ण

	वापस i;
पूर्ण

अटल पूर्णांक dt2801_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);

	dt2801_ग_लिखोcmd(dev, DT_C_WRITE_DAIM);
	dt2801_ग_लिखोdata(dev, chan);
	dt2801_ग_लिखोdata2(dev, data[0]);

	s->पढ़ोback[chan] = data[0];

	वापस 1;
पूर्ण

अटल पूर्णांक dt2801_dio_insn_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक which = (s == &dev->subdevices[3]) ? 1 : 0;
	अचिन्हित पूर्णांक val = 0;

	अगर (comedi_dio_update_state(s, data)) अणु
		dt2801_ग_लिखोcmd(dev, DT_C_WRITE_DIG);
		dt2801_ग_लिखोdata(dev, which);
		dt2801_ग_लिखोdata(dev, s->state);
	पूर्ण

	dt2801_ग_लिखोcmd(dev, DT_C_READ_DIG);
	dt2801_ग_लिखोdata(dev, which);
	dt2801_पढ़ोdata(dev, &val);

	data[1] = val;

	वापस insn->n;
पूर्ण

अटल पूर्णांक dt2801_dio_insn_config(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn,
				  अचिन्हित पूर्णांक *data)
अणु
	पूर्णांक ret;

	ret = comedi_dio_insn_config(dev, s, insn, data, 0xff);
	अगर (ret)
		वापस ret;

	dt2801_ग_लिखोcmd(dev, s->io_bits ? DT_C_SET_DIGOUT : DT_C_SET_DIGIN);
	dt2801_ग_लिखोdata(dev, (s == &dev->subdevices[3]) ? 1 : 0);

	वापस insn->n;
पूर्ण

/*
 * options:
 *	[0] - i/o base
 *	[1] - unused
 *	[2] - a/d 0=dअगरferential, 1=single-ended
 *	[3] - a/d range 0=[-10,10], 1=[0,10]
 *	[4] - dac0 range 0=[-10,10], 1=[-5,5], 2=[-2.5,2.5] 3=[0,10], 4=[0,5]
 *	[5] - dac1 range 0=[-10,10], 1=[-5,5], 2=[-2.5,2.5] 3=[0,10], 4=[0,5]
 */
अटल पूर्णांक dt2801_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	स्थिर काष्ठा dt2801_board *board;
	काष्ठा dt2801_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक board_code, type;
	पूर्णांक ret = 0;
	पूर्णांक n_ai_chans;

	ret = comedi_request_region(dev, it->options[0], 0x2);
	अगर (ret)
		वापस ret;

	/* करो some checking */

	board_code = dt2801_reset(dev);

	/* heh.  अगर it didn't work, try it again. */
	अगर (!board_code)
		board_code = dt2801_reset(dev);

	क्रम (type = 0; type < ARRAY_SIZE(boardtypes); type++) अणु
		अगर (boardtypes[type].boardcode == board_code)
			जाओ havetype;
	पूर्ण
	dev_dbg(dev->class_dev,
		"unrecognized board code=0x%02x, contact author\n", board_code);
	type = 0;

havetype:
	dev->board_ptr = boardtypes + type;
	board = dev->board_ptr;

	n_ai_chans = probe_number_of_ai_chans(dev);

	ret = comedi_alloc_subdevices(dev, 4);
	अगर (ret)
		जाओ out;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	dev->board_name = board->name;

	s = &dev->subdevices[0];
	/* ai subdevice */
	s->type = COMEDI_SUBD_AI;
	s->subdev_flags = SDF_READABLE | SDF_GROUND;
#अगर 1
	s->n_chan = n_ai_chans;
#अन्यथा
	अगर (it->options[2])
		s->n_chan = board->ad_chan;
	अन्यथा
		s->n_chan = board->ad_chan / 2;
#पूर्ण_अगर
	s->maxdata = (1 << board->adbits) - 1;
	s->range_table = ai_range_lkup(board->adrangetype, it->options[3]);
	s->insn_पढ़ो = dt2801_ai_insn_पढ़ो;

	s = &dev->subdevices[1];
	/* ao subdevice */
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_WRITABLE;
	s->n_chan = 2;
	s->maxdata = (1 << board->dabits) - 1;
	s->range_table_list = devpriv->dac_range_types;
	devpriv->dac_range_types[0] = dac_range_lkup(it->options[4]);
	devpriv->dac_range_types[1] = dac_range_lkup(it->options[5]);
	s->insn_ग_लिखो = dt2801_ao_insn_ग_लिखो;

	ret = comedi_alloc_subdev_पढ़ोback(s);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[2];
	/* 1st digital subdevice */
	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags = SDF_READABLE | SDF_WRITABLE;
	s->n_chan = 8;
	s->maxdata = 1;
	s->range_table = &range_digital;
	s->insn_bits = dt2801_dio_insn_bits;
	s->insn_config = dt2801_dio_insn_config;

	s = &dev->subdevices[3];
	/* 2nd digital subdevice */
	s->type = COMEDI_SUBD_DIO;
	s->subdev_flags = SDF_READABLE | SDF_WRITABLE;
	s->n_chan = 8;
	s->maxdata = 1;
	s->range_table = &range_digital;
	s->insn_bits = dt2801_dio_insn_bits;
	s->insn_config = dt2801_dio_insn_config;

	ret = 0;
out:
	वापस ret;
पूर्ण

अटल काष्ठा comedi_driver dt2801_driver = अणु
	.driver_name	= "dt2801",
	.module		= THIS_MODULE,
	.attach		= dt2801_attach,
	.detach		= comedi_legacy_detach,
पूर्ण;
module_comedi_driver(dt2801_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
