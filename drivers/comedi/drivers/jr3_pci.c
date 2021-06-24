<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/jr3_pci.c
 * hardware driver क्रम JR3/PCI क्रमce sensor board
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2007 Anders Blomdell <anders.blomdell@control.lth.se>
 */
/*
 * Driver: jr3_pci
 * Description: JR3/PCI क्रमce sensor board
 * Author: Anders Blomdell <anders.blomdell@control.lth.se>
 * Updated: Thu, 01 Nov 2012 17:34:55 +0000
 * Status: works
 * Devices: [JR3] PCI क्रमce sensor board (jr3_pci)
 *
 * Configuration options:
 *   None
 *
 * Manual configuration of comedi devices is not supported by this
 * driver; supported PCI devices are configured as comedi devices
 * स्वतःmatically.
 *
 * The DSP on the board requires initialization code, which can be
 * loaded by placing it in /lib/firmware/comedi.  The initialization
 * code should be somewhere on the media you got with your card.  One
 * version is available from https://www.comedi.org in the
 * comedi_nonमुक्त_firmware tarball.  The file is called "jr3pci.idm".
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/delay.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/slab.h>
#समावेश <linux/समयr.h>

#समावेश "../comedi_pci.h"

#समावेश "jr3_pci.h"

#घोषणा PCI_VENDOR_ID_JR3 0x1762

क्रमागत jr3_pci_boardid अणु
	BOARD_JR3_1,
	BOARD_JR3_2,
	BOARD_JR3_3,
	BOARD_JR3_4,
पूर्ण;

काष्ठा jr3_pci_board अणु
	स्थिर अक्षर *name;
	पूर्णांक n_subdevs;
पूर्ण;

अटल स्थिर काष्ठा jr3_pci_board jr3_pci_boards[] = अणु
	[BOARD_JR3_1] = अणु
		.name		= "jr3_pci_1",
		.n_subdevs	= 1,
	पूर्ण,
	[BOARD_JR3_2] = अणु
		.name		= "jr3_pci_2",
		.n_subdevs	= 2,
	पूर्ण,
	[BOARD_JR3_3] = अणु
		.name		= "jr3_pci_3",
		.n_subdevs	= 3,
	पूर्ण,
	[BOARD_JR3_4] = अणु
		.name		= "jr3_pci_4",
		.n_subdevs	= 4,
	पूर्ण,
पूर्ण;

काष्ठा jr3_pci_transक्रमm अणु
	काष्ठा अणु
		u16 link_type;
		s16 link_amount;
	पूर्ण link[8];
पूर्ण;

काष्ठा jr3_pci_poll_delay अणु
	पूर्णांक min;
	पूर्णांक max;
पूर्ण;

काष्ठा jr3_pci_dev_निजी अणु
	काष्ठा समयr_list समयr;
	काष्ठा comedi_device *dev;
पूर्ण;

जोड़ jr3_pci_single_range अणु
	काष्ठा comedi_lrange l;
	अक्षर _reserved[दुरत्व(काष्ठा comedi_lrange, range[1])];
पूर्ण;

क्रमागत jr3_pci_poll_state अणु
	state_jr3_poll,
	state_jr3_init_रुको_क्रम_offset,
	state_jr3_init_transक्रमm_complete,
	state_jr3_init_set_full_scale_complete,
	state_jr3_init_use_offset_complete,
	state_jr3_करोne
पूर्ण;

काष्ठा jr3_pci_subdev_निजी अणु
	काष्ठा jr3_sensor __iomem *sensor;
	अचिन्हित दीर्घ next_समय_min;
	क्रमागत jr3_pci_poll_state state;
	पूर्णांक serial_no;
	पूर्णांक model_no;
	जोड़ jr3_pci_single_range range[9];
	स्थिर काष्ठा comedi_lrange *range_table_list[8 * 7 + 2];
	अचिन्हित पूर्णांक maxdata_list[8 * 7 + 2];
	u16 errors;
	पूर्णांक retries;
पूर्ण;

अटल काष्ठा jr3_pci_poll_delay poll_delay_min_max(पूर्णांक min, पूर्णांक max)
अणु
	काष्ठा jr3_pci_poll_delay result;

	result.min = min;
	result.max = max;
	वापस result;
पूर्ण

अटल पूर्णांक is_complete(काष्ठा jr3_sensor __iomem *sensor)
अणु
	वापस get_s16(&sensor->command_word0) == 0;
पूर्ण

अटल व्योम set_transक्रमms(काष्ठा jr3_sensor __iomem *sensor,
			   स्थिर काष्ठा jr3_pci_transक्रमm *transf, लघु num)
अणु
	पूर्णांक i;

	num &= 0x000f;		/* Make sure that 0 <= num <= 15 */
	क्रम (i = 0; i < 8; i++) अणु
		set_u16(&sensor->transक्रमms[num].link[i].link_type,
			transf->link[i].link_type);
		udelay(1);
		set_s16(&sensor->transक्रमms[num].link[i].link_amount,
			transf->link[i].link_amount);
		udelay(1);
		अगर (transf->link[i].link_type == end_x_क्रमm)
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम use_transक्रमm(काष्ठा jr3_sensor __iomem *sensor,
			  लघु transf_num)
अणु
	set_s16(&sensor->command_word0, 0x0500 + (transf_num & 0x000f));
पूर्ण

अटल व्योम use_offset(काष्ठा jr3_sensor __iomem *sensor, लघु offset_num)
अणु
	set_s16(&sensor->command_word0, 0x0600 + (offset_num & 0x000f));
पूर्ण

अटल व्योम set_offset(काष्ठा jr3_sensor __iomem *sensor)
अणु
	set_s16(&sensor->command_word0, 0x0700);
पूर्ण

काष्ठा six_axis_t अणु
	s16 fx;
	s16 fy;
	s16 fz;
	s16 mx;
	s16 my;
	s16 mz;
पूर्ण;

अटल व्योम set_full_scales(काष्ठा jr3_sensor __iomem *sensor,
			    काष्ठा six_axis_t full_scale)
अणु
	set_s16(&sensor->full_scale.fx, full_scale.fx);
	set_s16(&sensor->full_scale.fy, full_scale.fy);
	set_s16(&sensor->full_scale.fz, full_scale.fz);
	set_s16(&sensor->full_scale.mx, full_scale.mx);
	set_s16(&sensor->full_scale.my, full_scale.my);
	set_s16(&sensor->full_scale.mz, full_scale.mz);
	set_s16(&sensor->command_word0, 0x0a00);
पूर्ण

अटल काष्ठा six_axis_t get_min_full_scales(काष्ठा jr3_sensor __iomem *sensor)
अणु
	काष्ठा six_axis_t result;

	result.fx = get_s16(&sensor->min_full_scale.fx);
	result.fy = get_s16(&sensor->min_full_scale.fy);
	result.fz = get_s16(&sensor->min_full_scale.fz);
	result.mx = get_s16(&sensor->min_full_scale.mx);
	result.my = get_s16(&sensor->min_full_scale.my);
	result.mz = get_s16(&sensor->min_full_scale.mz);
	वापस result;
पूर्ण

अटल काष्ठा six_axis_t get_max_full_scales(काष्ठा jr3_sensor __iomem *sensor)
अणु
	काष्ठा six_axis_t result;

	result.fx = get_s16(&sensor->max_full_scale.fx);
	result.fy = get_s16(&sensor->max_full_scale.fy);
	result.fz = get_s16(&sensor->max_full_scale.fz);
	result.mx = get_s16(&sensor->max_full_scale.mx);
	result.my = get_s16(&sensor->max_full_scale.my);
	result.mz = get_s16(&sensor->max_full_scale.mz);
	वापस result;
पूर्ण

अटल अचिन्हित पूर्णांक jr3_pci_ai_पढ़ो_chan(काष्ठा comedi_device *dev,
					 काष्ठा comedi_subdevice *s,
					 अचिन्हित पूर्णांक chan)
अणु
	काष्ठा jr3_pci_subdev_निजी *spriv = s->निजी;
	अचिन्हित पूर्णांक val = 0;

	अगर (spriv->state != state_jr3_करोne)
		वापस 0;

	अगर (chan < 56) अणु
		अचिन्हित पूर्णांक axis = chan % 8;
		अचिन्हित पूर्णांक filter = chan / 8;

		चयन (axis) अणु
		हाल 0:
			val = get_s16(&spriv->sensor->filter[filter].fx);
			अवरोध;
		हाल 1:
			val = get_s16(&spriv->sensor->filter[filter].fy);
			अवरोध;
		हाल 2:
			val = get_s16(&spriv->sensor->filter[filter].fz);
			अवरोध;
		हाल 3:
			val = get_s16(&spriv->sensor->filter[filter].mx);
			अवरोध;
		हाल 4:
			val = get_s16(&spriv->sensor->filter[filter].my);
			अवरोध;
		हाल 5:
			val = get_s16(&spriv->sensor->filter[filter].mz);
			अवरोध;
		हाल 6:
			val = get_s16(&spriv->sensor->filter[filter].v1);
			अवरोध;
		हाल 7:
			val = get_s16(&spriv->sensor->filter[filter].v2);
			अवरोध;
		पूर्ण
		val += 0x4000;
	पूर्ण अन्यथा अगर (chan == 56) अणु
		val = get_u16(&spriv->sensor->model_no);
	पूर्ण अन्यथा अगर (chan == 57) अणु
		val = get_u16(&spriv->sensor->serial_no);
	पूर्ण

	वापस val;
पूर्ण

अटल पूर्णांक jr3_pci_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा jr3_pci_subdev_निजी *spriv = s->निजी;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	u16 errors;
	पूर्णांक i;

	errors = get_u16(&spriv->sensor->errors);
	अगर (spriv->state != state_jr3_करोne ||
	    (errors & (watch_करोg | watch_करोg2 | sensor_change))) अणु
		/* No sensor or sensor changed */
		अगर (spriv->state == state_jr3_करोne) अणु
			/* Restart polling */
			spriv->state = state_jr3_poll;
		पूर्ण
		वापस -EAGAIN;
	पूर्ण

	क्रम (i = 0; i < insn->n; i++)
		data[i] = jr3_pci_ai_पढ़ो_chan(dev, s, chan);

	वापस insn->n;
पूर्ण

अटल पूर्णांक jr3_pci_खोलो(काष्ठा comedi_device *dev)
अणु
	काष्ठा jr3_pci_subdev_निजी *spriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक i;

	क्रम (i = 0; i < dev->n_subdevices; i++) अणु
		s = &dev->subdevices[i];
		spriv = s->निजी;
		dev_dbg(dev->class_dev, "serial[%d]: %d\n", s->index,
			spriv->serial_no);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक पढ़ो_idm_word(स्थिर u8 *data, माप_प्रकार size, पूर्णांक *pos,
			 अचिन्हित पूर्णांक *val)
अणु
	पूर्णांक result = 0;
	पूर्णांक value;

	अगर (pos && val) अणु
		/* Skip over non hex */
		क्रम (; *pos < size && !है_षष्ठादशक(data[*pos]); (*pos)++)
			;
		/* Collect value */
		*val = 0;
		क्रम (; *pos < size; (*pos)++) अणु
			value = hex_to_bin(data[*pos]);
			अगर (value >= 0) अणु
				result = 1;
				*val = (*val << 4) + value;
			पूर्ण अन्यथा अणु
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस result;
पूर्ण

अटल पूर्णांक jr3_check_firmware(काष्ठा comedi_device *dev,
			      स्थिर u8 *data, माप_प्रकार size)
अणु
	पूर्णांक more = 1;
	पूर्णांक pos = 0;

	/*
	 * IDM file क्रमmat is:
	 *   अणु count, address, data <count> पूर्ण *
	 *   ffff
	 */
	जबतक (more) अणु
		अचिन्हित पूर्णांक count = 0;
		अचिन्हित पूर्णांक addr = 0;

		more = more && पढ़ो_idm_word(data, size, &pos, &count);
		अगर (more && count == 0xffff)
			वापस 0;

		more = more && पढ़ो_idm_word(data, size, &pos, &addr);
		जबतक (more && count > 0) अणु
			अचिन्हित पूर्णांक dummy = 0;

			more = more && पढ़ो_idm_word(data, size, &pos, &dummy);
			count--;
		पूर्ण
	पूर्ण

	वापस -ENODATA;
पूर्ण

अटल व्योम jr3_ग_लिखो_firmware(काष्ठा comedi_device *dev,
			       पूर्णांक subdev, स्थिर u8 *data, माप_प्रकार size)
अणु
	काष्ठा jr3_block __iomem *block = dev->mmio;
	u32 __iomem *lo;
	u32 __iomem *hi;
	पूर्णांक more = 1;
	पूर्णांक pos = 0;

	जबतक (more) अणु
		अचिन्हित पूर्णांक count = 0;
		अचिन्हित पूर्णांक addr = 0;

		more = more && पढ़ो_idm_word(data, size, &pos, &count);
		अगर (more && count == 0xffff)
			वापस;

		more = more && पढ़ो_idm_word(data, size, &pos, &addr);

		dev_dbg(dev->class_dev, "Loading#%d %4.4x bytes at %4.4x\n",
			subdev, count, addr);

		जबतक (more && count > 0) अणु
			अगर (addr & 0x4000) अणु
				/* 16 bit data, never seen in real lअगरe!! */
				अचिन्हित पूर्णांक data1 = 0;

				more = more &&
				       पढ़ो_idm_word(data, size, &pos, &data1);
				count--;
				/* jr3[addr + 0x20000 * pnum] = data1; */
			पूर्ण अन्यथा अणु
				/* Download 24 bit program */
				अचिन्हित पूर्णांक data1 = 0;
				अचिन्हित पूर्णांक data2 = 0;

				lo = &block[subdev].program_lo[addr];
				hi = &block[subdev].program_hi[addr];

				more = more &&
				       पढ़ो_idm_word(data, size, &pos, &data1);
				more = more &&
				       पढ़ो_idm_word(data, size, &pos, &data2);
				count -= 2;
				अगर (more) अणु
					set_u16(lo, data1);
					udelay(1);
					set_u16(hi, data2);
					udelay(1);
				पूर्ण
			पूर्ण
			addr++;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक jr3_करोwnload_firmware(काष्ठा comedi_device *dev,
				 स्थिर u8 *data, माप_प्रकार size,
				 अचिन्हित दीर्घ context)
अणु
	पूर्णांक subdev;
	पूर्णांक ret;

	/* verअगरy IDM file क्रमmat */
	ret = jr3_check_firmware(dev, data, size);
	अगर (ret)
		वापस ret;

	/* ग_लिखो firmware to each subdevice */
	क्रम (subdev = 0; subdev < dev->n_subdevices; subdev++)
		jr3_ग_लिखो_firmware(dev, subdev, data, size);

	वापस 0;
पूर्ण

अटल काष्ठा jr3_pci_poll_delay
jr3_pci_poll_subdevice(काष्ठा comedi_subdevice *s)
अणु
	काष्ठा jr3_pci_subdev_निजी *spriv = s->निजी;
	काष्ठा jr3_pci_poll_delay result = poll_delay_min_max(1000, 2000);
	काष्ठा jr3_sensor __iomem *sensor;
	u16 model_no;
	u16 serial_no;
	पूर्णांक errors;
	पूर्णांक i;

	sensor = spriv->sensor;
	errors = get_u16(&sensor->errors);

	अगर (errors != spriv->errors)
		spriv->errors = errors;

	/* Sensor communication lost? क्रमce poll mode */
	अगर (errors & (watch_करोg | watch_करोg2 | sensor_change))
		spriv->state = state_jr3_poll;

	चयन (spriv->state) अणु
	हाल state_jr3_poll:
		model_no = get_u16(&sensor->model_no);
		serial_no = get_u16(&sensor->serial_no);

		अगर ((errors & (watch_करोg | watch_करोg2)) ||
		    model_no == 0 || serial_no == 0) अणु
			/*
			 * Still no sensor, keep on polling.
			 * Since it takes up to 10 seconds क्रम offsets to
			 * stabilize, polling each second should suffice.
			 */
		पूर्ण अन्यथा अणु
			spriv->retries = 0;
			spriv->state = state_jr3_init_रुको_क्रम_offset;
		पूर्ण
		अवरोध;
	हाल state_jr3_init_रुको_क्रम_offset:
		spriv->retries++;
		अगर (spriv->retries < 10) अणु
			/*
			 * Wait क्रम offeset to stabilize
			 * (< 10 s according to manual)
			 */
		पूर्ण अन्यथा अणु
			काष्ठा jr3_pci_transक्रमm transf;

			spriv->model_no = get_u16(&sensor->model_no);
			spriv->serial_no = get_u16(&sensor->serial_no);

			/* Transक्रमmation all zeros */
			क्रम (i = 0; i < ARRAY_SIZE(transf.link); i++) अणु
				transf.link[i].link_type = (क्रमागत link_types)0;
				transf.link[i].link_amount = 0;
			पूर्ण

			set_transक्रमms(sensor, &transf, 0);
			use_transक्रमm(sensor, 0);
			spriv->state = state_jr3_init_transक्रमm_complete;
			/* Allow 20 ms क्रम completion */
			result = poll_delay_min_max(20, 100);
		पूर्ण
		अवरोध;
	हाल state_jr3_init_transक्रमm_complete:
		अगर (!is_complete(sensor)) अणु
			result = poll_delay_min_max(20, 100);
		पूर्ण अन्यथा अणु
			/* Set full scale */
			काष्ठा six_axis_t min_full_scale;
			काष्ठा six_axis_t max_full_scale;

			min_full_scale = get_min_full_scales(sensor);
			max_full_scale = get_max_full_scales(sensor);
			set_full_scales(sensor, max_full_scale);

			spriv->state = state_jr3_init_set_full_scale_complete;
			/* Allow 20 ms क्रम completion */
			result = poll_delay_min_max(20, 100);
		पूर्ण
		अवरोध;
	हाल state_jr3_init_set_full_scale_complete:
		अगर (!is_complete(sensor)) अणु
			result = poll_delay_min_max(20, 100);
		पूर्ण अन्यथा अणु
			काष्ठा क्रमce_array __iomem *fs = &sensor->full_scale;
			जोड़ jr3_pci_single_range *r = spriv->range;

			/* Use ranges in kN or we will overflow around 2000N! */
			r[0].l.range[0].min = -get_s16(&fs->fx) * 1000;
			r[0].l.range[0].max = get_s16(&fs->fx) * 1000;
			r[1].l.range[0].min = -get_s16(&fs->fy) * 1000;
			r[1].l.range[0].max = get_s16(&fs->fy) * 1000;
			r[2].l.range[0].min = -get_s16(&fs->fz) * 1000;
			r[2].l.range[0].max = get_s16(&fs->fz) * 1000;
			r[3].l.range[0].min = -get_s16(&fs->mx) * 100;
			r[3].l.range[0].max = get_s16(&fs->mx) * 100;
			r[4].l.range[0].min = -get_s16(&fs->my) * 100;
			r[4].l.range[0].max = get_s16(&fs->my) * 100;
			r[5].l.range[0].min = -get_s16(&fs->mz) * 100;
			/* the next five are questionable */
			r[5].l.range[0].max = get_s16(&fs->mz) * 100;
			r[6].l.range[0].min = -get_s16(&fs->v1) * 100;
			r[6].l.range[0].max = get_s16(&fs->v1) * 100;
			r[7].l.range[0].min = -get_s16(&fs->v2) * 100;
			r[7].l.range[0].max = get_s16(&fs->v2) * 100;
			r[8].l.range[0].min = 0;
			r[8].l.range[0].max = 65535;

			use_offset(sensor, 0);
			spriv->state = state_jr3_init_use_offset_complete;
			/* Allow 40 ms क्रम completion */
			result = poll_delay_min_max(40, 100);
		पूर्ण
		अवरोध;
	हाल state_jr3_init_use_offset_complete:
		अगर (!is_complete(sensor)) अणु
			result = poll_delay_min_max(20, 100);
		पूर्ण अन्यथा अणु
			set_s16(&sensor->offsets.fx, 0);
			set_s16(&sensor->offsets.fy, 0);
			set_s16(&sensor->offsets.fz, 0);
			set_s16(&sensor->offsets.mx, 0);
			set_s16(&sensor->offsets.my, 0);
			set_s16(&sensor->offsets.mz, 0);

			set_offset(sensor);

			spriv->state = state_jr3_करोne;
		पूर्ण
		अवरोध;
	हाल state_jr3_करोne:
		result = poll_delay_min_max(10000, 20000);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस result;
पूर्ण

अटल व्योम jr3_pci_poll_dev(काष्ठा समयr_list *t)
अणु
	काष्ठा jr3_pci_dev_निजी *devpriv = from_समयr(devpriv, t, समयr);
	काष्ठा comedi_device *dev = devpriv->dev;
	काष्ठा jr3_pci_subdev_निजी *spriv;
	काष्ठा comedi_subdevice *s;
	अचिन्हित दीर्घ flags;
	अचिन्हित दीर्घ now;
	पूर्णांक delay;
	पूर्णांक i;

	spin_lock_irqsave(&dev->spinlock, flags);
	delay = 1000;
	now = jअगरfies;

	/* Poll all sensors that are पढ़ोy to be polled */
	क्रम (i = 0; i < dev->n_subdevices; i++) अणु
		s = &dev->subdevices[i];
		spriv = s->निजी;

		अगर (समय_after_eq(now, spriv->next_समय_min)) अणु
			काष्ठा jr3_pci_poll_delay sub_delay;

			sub_delay = jr3_pci_poll_subdevice(s);

			spriv->next_समय_min = jअगरfies +
					       msecs_to_jअगरfies(sub_delay.min);

			अगर (sub_delay.max && sub_delay.max < delay)
				/*
				 * Wake up as late as possible ->
				 * poll as many sensors as possible at once.
				 */
				delay = sub_delay.max;
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&dev->spinlock, flags);

	devpriv->समयr.expires = jअगरfies + msecs_to_jअगरfies(delay);
	add_समयr(&devpriv->समयr);
पूर्ण

अटल काष्ठा jr3_pci_subdev_निजी *
jr3_pci_alloc_spriv(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	काष्ठा jr3_block __iomem *block = dev->mmio;
	काष्ठा jr3_pci_subdev_निजी *spriv;
	पूर्णांक j;
	पूर्णांक k;

	spriv = comedi_alloc_spriv(s, माप(*spriv));
	अगर (!spriv)
		वापस शून्य;

	spriv->sensor = &block[s->index].sensor;

	क्रम (j = 0; j < 8; j++) अणु
		spriv->range[j].l.length = 1;
		spriv->range[j].l.range[0].min = -1000000;
		spriv->range[j].l.range[0].max = 1000000;

		क्रम (k = 0; k < 7; k++) अणु
			spriv->range_table_list[j + k * 8] = &spriv->range[j].l;
			spriv->maxdata_list[j + k * 8] = 0x7fff;
		पूर्ण
	पूर्ण
	spriv->range[8].l.length = 1;
	spriv->range[8].l.range[0].min = 0;
	spriv->range[8].l.range[0].max = 65535;

	spriv->range_table_list[56] = &spriv->range[8].l;
	spriv->range_table_list[57] = &spriv->range[8].l;
	spriv->maxdata_list[56] = 0xffff;
	spriv->maxdata_list[57] = 0xffff;

	वापस spriv;
पूर्ण

अटल व्योम jr3_pci_show_copyright(काष्ठा comedi_device *dev)
अणु
	काष्ठा jr3_block __iomem *block = dev->mmio;
	काष्ठा jr3_sensor __iomem *sensor0 = &block[0].sensor;
	अक्षर copy[ARRAY_SIZE(sensor0->copyright) + 1];
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(sensor0->copyright); i++)
		copy[i] = (अक्षर)(get_u16(&sensor0->copyright[i]) >> 8);
	copy[i] = '\0';
	dev_dbg(dev->class_dev, "Firmware copyright: %s\n", copy);
पूर्ण

अटल पूर्णांक jr3_pci_स्वतः_attach(काष्ठा comedi_device *dev,
			       अचिन्हित दीर्घ context)
अणु
	काष्ठा pci_dev *pcidev = comedi_to_pci_dev(dev);
	अटल स्थिर काष्ठा jr3_pci_board *board;
	काष्ठा jr3_pci_dev_निजी *devpriv;
	काष्ठा jr3_pci_subdev_निजी *spriv;
	काष्ठा jr3_block __iomem *block;
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;
	पूर्णांक i;

	BUILD_BUG_ON(माप(काष्ठा jr3_block) != 0x80000);

	अगर (context < ARRAY_SIZE(jr3_pci_boards))
		board = &jr3_pci_boards[context];
	अगर (!board)
		वापस -ENODEV;
	dev->board_ptr = board;
	dev->board_name = board->name;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	ret = comedi_pci_enable(dev);
	अगर (ret)
		वापस ret;

	अगर (pci_resource_len(pcidev, 0) < board->n_subdevs * माप(*block))
		वापस -ENXIO;

	dev->mmio = pci_ioremap_bar(pcidev, 0);
	अगर (!dev->mmio)
		वापस -ENOMEM;

	block = dev->mmio;

	ret = comedi_alloc_subdevices(dev, board->n_subdevs);
	अगर (ret)
		वापस ret;

	dev->खोलो = jr3_pci_खोलो;
	क्रम (i = 0; i < dev->n_subdevices; i++) अणु
		s = &dev->subdevices[i];
		s->type		= COMEDI_SUBD_AI;
		s->subdev_flags	= SDF_READABLE | SDF_GROUND;
		s->n_chan	= 8 * 7 + 2;
		s->insn_पढ़ो	= jr3_pci_ai_insn_पढ़ो;

		spriv = jr3_pci_alloc_spriv(dev, s);
		अगर (!spriv)
			वापस -ENOMEM;

		/* Channel specअगरic range and maxdata */
		s->range_table_list	= spriv->range_table_list;
		s->maxdata_list		= spriv->maxdata_list;
	पूर्ण

	/* Reset DSP card */
	क्रम (i = 0; i < dev->n_subdevices; i++)
		ग_लिखोl(0, &block[i].reset);

	ret = comedi_load_firmware(dev, &comedi_to_pci_dev(dev)->dev,
				   "comedi/jr3pci.idm",
				   jr3_करोwnload_firmware, 0);
	dev_dbg(dev->class_dev, "Firmware load %d\n", ret);
	अगर (ret < 0)
		वापस ret;
	/*
	 * TODO: use firmware to load preferred offset tables. Suggested
	 * क्रमmat:
	 *     model serial Fx Fy Fz Mx My Mz\न
	 *
	 *     comedi_load_firmware(dev, &comedi_to_pci_dev(dev)->dev,
	 *                          "comedi/jr3_offsets_table",
	 *                          jr3_करोwnload_firmware, 1);
	 */

	/*
	 * It takes a few milliseconds क्रम software to settle as much as we
	 * can पढ़ो firmware version
	 */
	msleep_पूर्णांकerruptible(25);
	jr3_pci_show_copyright(dev);

	/* Start card समयr */
	क्रम (i = 0; i < dev->n_subdevices; i++) अणु
		s = &dev->subdevices[i];
		spriv = s->निजी;

		spriv->next_समय_min = jअगरfies + msecs_to_jअगरfies(500);
	पूर्ण

	devpriv->dev = dev;
	समयr_setup(&devpriv->समयr, jr3_pci_poll_dev, 0);
	devpriv->समयr.expires = jअगरfies + msecs_to_jअगरfies(1000);
	add_समयr(&devpriv->समयr);

	वापस 0;
पूर्ण

अटल व्योम jr3_pci_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा jr3_pci_dev_निजी *devpriv = dev->निजी;

	अगर (devpriv)
		del_समयr_sync(&devpriv->समयr);

	comedi_pci_detach(dev);
पूर्ण

अटल काष्ठा comedi_driver jr3_pci_driver = अणु
	.driver_name	= "jr3_pci",
	.module		= THIS_MODULE,
	.स्वतः_attach	= jr3_pci_स्वतः_attach,
	.detach		= jr3_pci_detach,
पूर्ण;

अटल पूर्णांक jr3_pci_pci_probe(काष्ठा pci_dev *dev,
			     स्थिर काष्ठा pci_device_id *id)
अणु
	वापस comedi_pci_स्वतः_config(dev, &jr3_pci_driver, id->driver_data);
पूर्ण

अटल स्थिर काष्ठा pci_device_id jr3_pci_pci_table[] = अणु
	अणु PCI_VDEVICE(JR3, 0x1111), BOARD_JR3_1 पूर्ण,
	अणु PCI_VDEVICE(JR3, 0x3111), BOARD_JR3_1 पूर्ण,
	अणु PCI_VDEVICE(JR3, 0x3112), BOARD_JR3_2 पूर्ण,
	अणु PCI_VDEVICE(JR3, 0x3113), BOARD_JR3_3 पूर्ण,
	अणु PCI_VDEVICE(JR3, 0x3114), BOARD_JR3_4 पूर्ण,
	अणु 0 पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(pci, jr3_pci_pci_table);

अटल काष्ठा pci_driver jr3_pci_pci_driver = अणु
	.name		= "jr3_pci",
	.id_table	= jr3_pci_pci_table,
	.probe		= jr3_pci_pci_probe,
	.हटाओ		= comedi_pci_स्वतः_unconfig,
पूर्ण;
module_comedi_pci_driver(jr3_pci_driver, jr3_pci_pci_driver);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi driver for JR3/PCI force sensor board");
MODULE_LICENSE("GPL");
MODULE_FIRMWARE("comedi/jr3pci.idm");
