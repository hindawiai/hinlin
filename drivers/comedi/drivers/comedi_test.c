<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * comedi/drivers/comedi_test.c
 *
 * Generates fake waveक्रमm संकेतs that can be पढ़ो through
 * the command पूर्णांकerface.  It करोes _not_ पढ़ो from any board;
 * it just generates deterministic waveक्रमms.
 * Useful क्रम various testing purposes.
 *
 * Copyright (C) 2002 Joachim Wuttke <Joachim.Wuttke@icn.siemens.de>
 * Copyright (C) 2002 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 *
 * COMEDI - Linux Control and Measurement Device Interface
 * Copyright (C) 2000 David A. Schleef <ds@schleef.org>
 */

/*
 * Driver: comedi_test
 * Description: generates fake waveक्रमms
 * Author: Joachim Wuttke <Joachim.Wuttke@icn.siemens.de>, Frank Mori Hess
 *   <fmhess@users.sourceक्रमge.net>, ds
 * Devices:
 * Status: works
 * Updated: Sat, 16 Mar 2002 17:34:48 -0800
 *
 * This driver is मुख्यly क्रम testing purposes, but can also be used to
 * generate sample waveक्रमms on प्रणालीs that करोn't have data acquisition
 * hardware.
 *
 * Auto-configuration is the शेष mode अगर no parameter is supplied during
 * module loading. Manual configuration requires COMEDI userspace tool.
 * To disable स्वतः-configuration mode, pass "noauto=1" parameter क्रम module
 * loading. Refer modinfo or MODULE_PARM_DESC description below क्रम details.
 *
 * Auto-configuration options:
 *   Refer modinfo or MODULE_PARM_DESC description below क्रम details.
 *
 * Manual configuration options:
 *   [0] - Amplitude in microvolts क्रम fake waveक्रमms (शेष 1 volt)
 *   [1] - Period in microseconds क्रम fake waveक्रमms (शेष 0.1 sec)
 *
 * Generates a sawtooth wave on channel 0, square wave on channel 1, additional
 * waveक्रमms could be added to other channels (currently they वापस flatline
 * zero volts).
 */

#समावेश <linux/module.h>
#समावेश "../comedidev.h"

#समावेश <यंत्र/भाग64.h>

#समावेश <linux/समयr.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/device.h>
#समावेश <linux/kdev_t.h>

#घोषणा N_CHANS 8
#घोषणा DEV_NAME "comedi_testd"
#घोषणा CLASS_NAME "comedi_test"

अटल bool config_mode;
अटल अचिन्हित पूर्णांक set_amplitude;
अटल अचिन्हित पूर्णांक set_period;
अटल काष्ठा class *ctcls;
अटल काष्ठा device *ctdev;

module_param_named(noस्वतः, config_mode, bool, 0444);
MODULE_PARM_DESC(noस्वतः, "Disable auto-configuration: (1=disable [defaults to enable])");

module_param_named(amplitude, set_amplitude, uपूर्णांक, 0444);
MODULE_PARM_DESC(amplitude, "Set auto mode wave amplitude in microvolts: (defaults to 1 volt)");

module_param_named(period, set_period, uपूर्णांक, 0444);
MODULE_PARM_DESC(period, "Set auto mode wave period in microseconds: (defaults to 0.1 sec)");

/* Data unique to this driver */
काष्ठा waveक्रमm_निजी अणु
	काष्ठा समयr_list ai_समयr;	/* समयr क्रम AI commands */
	u64 ai_convert_समय;		/* समय of next AI conversion in usec */
	अचिन्हित पूर्णांक wf_amplitude;	/* waveक्रमm amplitude in microvolts */
	अचिन्हित पूर्णांक wf_period;		/* waveक्रमm period in microseconds */
	अचिन्हित पूर्णांक wf_current;	/* current समय in waveक्रमm period */
	अचिन्हित पूर्णांक ai_scan_period;	/* AI scan period in usec */
	अचिन्हित पूर्णांक ai_convert_period;	/* AI conversion period in usec */
	काष्ठा समयr_list ao_समयr;	/* समयr क्रम AO commands */
	काष्ठा comedi_device *dev;	/* parent comedi device */
	u64 ao_last_scan_समय;		/* समय of previous AO scan in usec */
	अचिन्हित पूर्णांक ao_scan_period;	/* AO scan period in usec */
	अचिन्हित लघु ao_loopbacks[N_CHANS];
पूर्ण;

/* fake analog input ranges */
अटल स्थिर काष्ठा comedi_lrange waveक्रमm_ai_ranges = अणु
	2, अणु
		BIP_RANGE(10),
		BIP_RANGE(5)
	पूर्ण
पूर्ण;

अटल अचिन्हित लघु fake_sawtooth(काष्ठा comedi_device *dev,
				    अचिन्हित पूर्णांक range_index,
				    अचिन्हित पूर्णांक current_समय)
अणु
	काष्ठा waveक्रमm_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित पूर्णांक offset = s->maxdata / 2;
	u64 value;
	स्थिर काष्ठा comedi_krange *krange =
	    &s->range_table->range[range_index];
	u64 binary_amplitude;

	binary_amplitude = s->maxdata;
	binary_amplitude *= devpriv->wf_amplitude;
	करो_भाग(binary_amplitude, krange->max - krange->min);

	value = current_समय;
	value *= binary_amplitude * 2;
	करो_भाग(value, devpriv->wf_period);
	value += offset;
	/* get rid of sawtooth's dc offset and clamp value */
	अगर (value < binary_amplitude) अणु
		value = 0;			/* negative saturation */
	पूर्ण अन्यथा अणु
		value -= binary_amplitude;
		अगर (value > s->maxdata)
			value = s->maxdata;	/* positive saturation */
	पूर्ण

	वापस value;
पूर्ण

अटल अचिन्हित लघु fake_squarewave(काष्ठा comedi_device *dev,
				      अचिन्हित पूर्णांक range_index,
				      अचिन्हित पूर्णांक current_समय)
अणु
	काष्ठा waveक्रमm_निजी *devpriv = dev->निजी;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	अचिन्हित पूर्णांक offset = s->maxdata / 2;
	u64 value;
	स्थिर काष्ठा comedi_krange *krange =
	    &s->range_table->range[range_index];

	value = s->maxdata;
	value *= devpriv->wf_amplitude;
	करो_भाग(value, krange->max - krange->min);

	/* get one of two values क्रम square-wave and clamp */
	अगर (current_समय < devpriv->wf_period / 2) अणु
		अगर (offset < value)
			value = 0;		/* negative saturation */
		अन्यथा
			value = offset - value;
	पूर्ण अन्यथा अणु
		value += offset;
		अगर (value > s->maxdata)
			value = s->maxdata;	/* positive saturation */
	पूर्ण

	वापस value;
पूर्ण

अटल अचिन्हित लघु fake_flatline(काष्ठा comedi_device *dev,
				    अचिन्हित पूर्णांक range_index,
				    अचिन्हित पूर्णांक current_समय)
अणु
	वापस dev->पढ़ो_subdev->maxdata / 2;
पूर्ण

/* generates a dअगरferent waveक्रमm depending on what channel is पढ़ो */
अटल अचिन्हित लघु fake_waveक्रमm(काष्ठा comedi_device *dev,
				    अचिन्हित पूर्णांक channel, अचिन्हित पूर्णांक range,
				    अचिन्हित पूर्णांक current_समय)
अणु
	क्रमागत अणु
		SAWTOOTH_CHAN,
		SQUARE_CHAN,
	पूर्ण;
	चयन (channel) अणु
	हाल SAWTOOTH_CHAN:
		वापस fake_sawtooth(dev, range, current_समय);
	हाल SQUARE_CHAN:
		वापस fake_squarewave(dev, range, current_समय);
	शेष:
		अवरोध;
	पूर्ण

	वापस fake_flatline(dev, range, current_समय);
पूर्ण

/*
 * This is the background routine used to generate arbitrary data.
 * It should run in the background; thereक्रमe it is scheduled by
 * a समयr mechanism.
 */
अटल व्योम waveक्रमm_ai_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा waveक्रमm_निजी *devpriv = from_समयr(devpriv, t, ai_समयr);
	काष्ठा comedi_device *dev = devpriv->dev;
	काष्ठा comedi_subdevice *s = dev->पढ़ो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	u64 now;
	अचिन्हित पूर्णांक nsamples;
	अचिन्हित पूर्णांक समय_increment;

	now = kसमय_प्रकारo_us(kसमय_get());
	nsamples = comedi_nsamples_left(s, अच_पूर्णांक_उच्च);

	जबतक (nsamples && devpriv->ai_convert_समय < now) अणु
		अचिन्हित पूर्णांक chanspec = cmd->chanlist[async->cur_chan];
		अचिन्हित लघु sample;

		sample = fake_waveक्रमm(dev, CR_CHAN(chanspec),
				       CR_RANGE(chanspec), devpriv->wf_current);
		अगर (comedi_buf_ग_लिखो_samples(s, &sample, 1) == 0)
			जाओ overrun;
		समय_increment = devpriv->ai_convert_period;
		अगर (async->scan_progress == 0) अणु
			/* करोne last conversion in scan, so add dead समय */
			समय_increment += devpriv->ai_scan_period -
					  devpriv->ai_convert_period *
					  cmd->scan_end_arg;
		पूर्ण
		devpriv->wf_current += समय_increment;
		अगर (devpriv->wf_current >= devpriv->wf_period)
			devpriv->wf_current %= devpriv->wf_period;
		devpriv->ai_convert_समय += समय_increment;
		nsamples--;
	पूर्ण

	अगर (cmd->stop_src == TRIG_COUNT && async->scans_करोne >= cmd->stop_arg) अणु
		async->events |= COMEDI_CB_EOA;
	पूर्ण अन्यथा अणु
		अगर (devpriv->ai_convert_समय > now)
			समय_increment = devpriv->ai_convert_समय - now;
		अन्यथा
			समय_increment = 1;
		mod_समयr(&devpriv->ai_समयr,
			  jअगरfies + usecs_to_jअगरfies(समय_increment));
	पूर्ण

overrun:
	comedi_handle_events(dev, s);
पूर्ण

अटल पूर्णांक waveक्रमm_ai_cmdtest(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg, limit;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src,
					TRIG_FOLLOW | TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->convert_src,
					TRIG_NOW | TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->convert_src);
	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (cmd->scan_begin_src == TRIG_FOLLOW && cmd->convert_src == TRIG_NOW)
		err |= -EINVAL;		/* scan period would be 0 */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_is(&cmd->start_arg, 0);

	अगर (cmd->convert_src == TRIG_NOW) अणु
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	पूर्ण अन्यथा अणु	/* cmd->convert_src == TRIG_TIMER */
		अगर (cmd->scan_begin_src == TRIG_FOLLOW) अणु
			err |= comedi_check_trigger_arg_min(&cmd->convert_arg,
							    NSEC_PER_USEC);
		पूर्ण
	पूर्ण

	अगर (cmd->scan_begin_src == TRIG_FOLLOW) अणु
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, 0);
	पूर्ण अन्यथा अणु	/* cmd->scan_begin_src == TRIG_TIMER */
		err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
						    NSEC_PER_USEC);
	पूर्ण

	err |= comedi_check_trigger_arg_min(&cmd->chanlist_len, 1);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);

	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* cmd->stop_src == TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	अगर (cmd->convert_src == TRIG_TIMER) अणु
		/* round convert_arg to nearest microsecond */
		arg = cmd->convert_arg;
		arg = min(arg,
			  roundकरोwn(अच_पूर्णांक_उच्च, (अचिन्हित पूर्णांक)NSEC_PER_USEC));
		arg = NSEC_PER_USEC * DIV_ROUND_CLOSEST(arg, NSEC_PER_USEC);
		अगर (cmd->scan_begin_arg == TRIG_TIMER) अणु
			/* limit convert_arg to keep scan_begin_arg in range */
			limit = अच_पूर्णांक_उच्च / cmd->scan_end_arg;
			limit = roundकरोwn(limit, (अचिन्हित पूर्णांक)NSEC_PER_SEC);
			arg = min(arg, limit);
		पूर्ण
		err |= comedi_check_trigger_arg_is(&cmd->convert_arg, arg);
	पूर्ण

	अगर (cmd->scan_begin_src == TRIG_TIMER) अणु
		/* round scan_begin_arg to nearest microsecond */
		arg = cmd->scan_begin_arg;
		arg = min(arg,
			  roundकरोwn(अच_पूर्णांक_उच्च, (अचिन्हित पूर्णांक)NSEC_PER_USEC));
		arg = NSEC_PER_USEC * DIV_ROUND_CLOSEST(arg, NSEC_PER_USEC);
		अगर (cmd->convert_src == TRIG_TIMER) अणु
			/* but ensure scan_begin_arg is large enough */
			arg = max(arg, cmd->convert_arg * cmd->scan_end_arg);
		पूर्ण
		err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);
	पूर्ण

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक waveक्रमm_ai_cmd(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	काष्ठा waveक्रमm_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;
	अचिन्हित पूर्णांक first_convert_समय;
	u64 wf_current;

	अगर (cmd->flags & CMDF_PRIORITY) अणु
		dev_err(dev->class_dev,
			"commands at RT priority not supported in this driver\n");
		वापस -1;
	पूर्ण

	अगर (cmd->convert_src == TRIG_NOW)
		devpriv->ai_convert_period = 0;
	अन्यथा		/* cmd->convert_src == TRIG_TIMER */
		devpriv->ai_convert_period = cmd->convert_arg / NSEC_PER_USEC;

	अगर (cmd->scan_begin_src == TRIG_FOLLOW) अणु
		devpriv->ai_scan_period = devpriv->ai_convert_period *
					  cmd->scan_end_arg;
	पूर्ण अन्यथा अणु	/* cmd->scan_begin_src == TRIG_TIMER */
		devpriv->ai_scan_period = cmd->scan_begin_arg / NSEC_PER_USEC;
	पूर्ण

	/*
	 * Simulate first conversion to occur at convert period after
	 * conversion समयr starts.  If scan_begin_src is TRIG_FOLLOW, assume
	 * the conversion समयr starts immediately.  If scan_begin_src is
	 * TRIG_TIMER, assume the conversion समयr starts after the scan
	 * period.
	 */
	first_convert_समय = devpriv->ai_convert_period;
	अगर (cmd->scan_begin_src == TRIG_TIMER)
		first_convert_समय += devpriv->ai_scan_period;
	devpriv->ai_convert_समय = kसमय_प्रकारo_us(kसमय_get()) +
				   first_convert_समय;

	/* Determine समय within waveक्रमm period at समय of conversion. */
	wf_current = devpriv->ai_convert_समय;
	devpriv->wf_current = करो_भाग(wf_current, devpriv->wf_period);

	/*
	 * Schedule समयr to expire just after first conversion समय.
	 * Seem to need an extra jअगरfy here, otherwise समयr expires slightly
	 * early!
	 */
	devpriv->ai_समयr.expires =
		jअगरfies + usecs_to_jअगरfies(devpriv->ai_convert_period) + 1;
	add_समयr(&devpriv->ai_समयr);
	वापस 0;
पूर्ण

अटल पूर्णांक waveक्रमm_ai_cancel(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा waveक्रमm_निजी *devpriv = dev->निजी;

	अगर (in_softirq()) अणु
		/* Assume we were called from the समयr routine itself. */
		del_समयr(&devpriv->ai_समयr);
	पूर्ण अन्यथा अणु
		del_समयr_sync(&devpriv->ai_समयr);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक waveक्रमm_ai_insn_पढ़ो(काष्ठा comedi_device *dev,
				 काष्ठा comedi_subdevice *s,
				 काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	काष्ठा waveक्रमm_निजी *devpriv = dev->निजी;
	पूर्णांक i, chan = CR_CHAN(insn->chanspec);

	क्रम (i = 0; i < insn->n; i++)
		data[i] = devpriv->ao_loopbacks[chan];

	वापस insn->n;
पूर्ण

/*
 * This is the background routine to handle AO commands, scheduled by
 * a समयr mechanism.
 */
अटल व्योम waveक्रमm_ao_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा waveक्रमm_निजी *devpriv = from_समयr(devpriv, t, ao_समयr);
	काष्ठा comedi_device *dev = devpriv->dev;
	काष्ठा comedi_subdevice *s = dev->ग_लिखो_subdev;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	u64 now;
	u64 scans_since;
	अचिन्हित पूर्णांक scans_avail = 0;

	/* determine number of scan periods since last समय */
	now = kसमय_प्रकारo_us(kसमय_get());
	scans_since = now - devpriv->ao_last_scan_समय;
	करो_भाग(scans_since, devpriv->ao_scan_period);
	अगर (scans_since) अणु
		अचिन्हित पूर्णांक i;

		/* determine scans in buffer, limit to scans to करो this समय */
		scans_avail = comedi_nscans_left(s, 0);
		अगर (scans_avail > scans_since)
			scans_avail = scans_since;
		अगर (scans_avail) अणु
			/* skip all but the last scan to save processing समय */
			अगर (scans_avail > 1) अणु
				अचिन्हित पूर्णांक skip_bytes, nbytes;

				skip_bytes =
				comedi_samples_to_bytes(s, cmd->scan_end_arg *
							   (scans_avail - 1));
				nbytes = comedi_buf_पढ़ो_alloc(s, skip_bytes);
				comedi_buf_पढ़ो_मुक्त(s, nbytes);
				comedi_inc_scan_progress(s, nbytes);
				अगर (nbytes < skip_bytes) अणु
					/* unexpected underrun! (cancelled?) */
					async->events |= COMEDI_CB_OVERFLOW;
					जाओ underrun;
				पूर्ण
			पूर्ण
			/* output the last scan */
			क्रम (i = 0; i < cmd->scan_end_arg; i++) अणु
				अचिन्हित पूर्णांक chan = CR_CHAN(cmd->chanlist[i]);
				अचिन्हित लघु *pd;

				pd = &devpriv->ao_loopbacks[chan];

				अगर (!comedi_buf_पढ़ो_samples(s, pd, 1)) अणु
					/* unexpected underrun! (cancelled?) */
					async->events |= COMEDI_CB_OVERFLOW;
					जाओ underrun;
				पूर्ण
			पूर्ण
			/* advance समय of last scan */
			devpriv->ao_last_scan_समय +=
				(u64)scans_avail * devpriv->ao_scan_period;
		पूर्ण
	पूर्ण
	अगर (cmd->stop_src == TRIG_COUNT && async->scans_करोne >= cmd->stop_arg) अणु
		async->events |= COMEDI_CB_EOA;
	पूर्ण अन्यथा अगर (scans_avail < scans_since) अणु
		async->events |= COMEDI_CB_OVERFLOW;
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक समय_inc = devpriv->ao_last_scan_समय +
					devpriv->ao_scan_period - now;

		mod_समयr(&devpriv->ao_समयr,
			  jअगरfies + usecs_to_jअगरfies(समय_inc));
	पूर्ण

underrun:
	comedi_handle_events(dev, s);
पूर्ण

अटल पूर्णांक waveक्रमm_ao_पूर्णांकtrig_start(काष्ठा comedi_device *dev,
				     काष्ठा comedi_subdevice *s,
				     अचिन्हित पूर्णांक trig_num)
अणु
	काष्ठा waveक्रमm_निजी *devpriv = dev->निजी;
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;

	अगर (trig_num != cmd->start_arg)
		वापस -EINVAL;

	async->पूर्णांकtrig = शून्य;

	devpriv->ao_last_scan_समय = kसमय_प्रकारo_us(kसमय_get());
	devpriv->ao_समयr.expires =
		jअगरfies + usecs_to_jअगरfies(devpriv->ao_scan_period);
	add_समयr(&devpriv->ao_समयr);

	वापस 1;
पूर्ण

अटल पूर्णांक waveक्रमm_ao_cmdtest(काष्ठा comedi_device *dev,
			       काष्ठा comedi_subdevice *s,
			       काष्ठा comedi_cmd *cmd)
अणु
	पूर्णांक err = 0;
	अचिन्हित पूर्णांक arg;

	/* Step 1 : check अगर triggers are trivially valid */

	err |= comedi_check_trigger_src(&cmd->start_src, TRIG_INT);
	err |= comedi_check_trigger_src(&cmd->scan_begin_src, TRIG_TIMER);
	err |= comedi_check_trigger_src(&cmd->convert_src, TRIG_NOW);
	err |= comedi_check_trigger_src(&cmd->scan_end_src, TRIG_COUNT);
	err |= comedi_check_trigger_src(&cmd->stop_src, TRIG_COUNT | TRIG_NONE);

	अगर (err)
		वापस 1;

	/* Step 2a : make sure trigger sources are unique */

	err |= comedi_check_trigger_is_unique(cmd->stop_src);

	/* Step 2b : and mutually compatible */

	अगर (err)
		वापस 2;

	/* Step 3: check अगर arguments are trivially valid */

	err |= comedi_check_trigger_arg_min(&cmd->scan_begin_arg,
					    NSEC_PER_USEC);
	err |= comedi_check_trigger_arg_is(&cmd->convert_arg, 0);
	err |= comedi_check_trigger_arg_min(&cmd->chanlist_len, 1);
	err |= comedi_check_trigger_arg_is(&cmd->scan_end_arg,
					   cmd->chanlist_len);
	अगर (cmd->stop_src == TRIG_COUNT)
		err |= comedi_check_trigger_arg_min(&cmd->stop_arg, 1);
	अन्यथा	/* cmd->stop_src == TRIG_NONE */
		err |= comedi_check_trigger_arg_is(&cmd->stop_arg, 0);

	अगर (err)
		वापस 3;

	/* step 4: fix up any arguments */

	/* round scan_begin_arg to nearest microsecond */
	arg = cmd->scan_begin_arg;
	arg = min(arg, roundकरोwn(अच_पूर्णांक_उच्च, (अचिन्हित पूर्णांक)NSEC_PER_USEC));
	arg = NSEC_PER_USEC * DIV_ROUND_CLOSEST(arg, NSEC_PER_USEC);
	err |= comedi_check_trigger_arg_is(&cmd->scan_begin_arg, arg);

	अगर (err)
		वापस 4;

	वापस 0;
पूर्ण

अटल पूर्णांक waveक्रमm_ao_cmd(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s)
अणु
	काष्ठा waveक्रमm_निजी *devpriv = dev->निजी;
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	अगर (cmd->flags & CMDF_PRIORITY) अणु
		dev_err(dev->class_dev,
			"commands at RT priority not supported in this driver\n");
		वापस -1;
	पूर्ण

	devpriv->ao_scan_period = cmd->scan_begin_arg / NSEC_PER_USEC;
	s->async->पूर्णांकtrig = waveक्रमm_ao_पूर्णांकtrig_start;
	वापस 0;
पूर्ण

अटल पूर्णांक waveक्रमm_ao_cancel(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s)
अणु
	काष्ठा waveक्रमm_निजी *devpriv = dev->निजी;

	s->async->पूर्णांकtrig = शून्य;
	अगर (in_softirq()) अणु
		/* Assume we were called from the समयr routine itself. */
		del_समयr(&devpriv->ao_समयr);
	पूर्ण अन्यथा अणु
		del_समयr_sync(&devpriv->ao_समयr);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक waveक्रमm_ao_insn_ग_लिखो(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s,
				  काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	काष्ठा waveक्रमm_निजी *devpriv = dev->निजी;
	पूर्णांक i, chan = CR_CHAN(insn->chanspec);

	क्रम (i = 0; i < insn->n; i++)
		devpriv->ao_loopbacks[chan] = data[i];

	वापस insn->n;
पूर्ण

अटल पूर्णांक waveक्रमm_ai_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	अगर (data[0] == INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS) अणु
		/*
		 * input:  data[1], data[2] : scan_begin_src, convert_src
		 * output: data[1], data[2] : scan_begin_min, convert_min
		 */
		अगर (data[1] == TRIG_FOLLOW) अणु
			/* exactly TRIG_FOLLOW हाल */
			data[1] = 0;
			data[2] = NSEC_PER_USEC;
		पूर्ण अन्यथा अणु
			data[1] = NSEC_PER_USEC;
			अगर (data[2] & TRIG_TIMER)
				data[2] = NSEC_PER_USEC;
			अन्यथा
				data[2] = 0;
		पूर्ण
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक waveक्रमm_ao_insn_config(काष्ठा comedi_device *dev,
				   काष्ठा comedi_subdevice *s,
				   काष्ठा comedi_insn *insn,
				   अचिन्हित पूर्णांक *data)
अणु
	अगर (data[0] == INSN_CONFIG_GET_CMD_TIMING_CONSTRAINTS) अणु
		/* we करोn't care about actual channels */
		data[1] = NSEC_PER_USEC; /* scan_begin_min */
		data[2] = 0;		 /* convert_min */
		वापस 0;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक waveक्रमm_common_attach(काष्ठा comedi_device *dev,
				  पूर्णांक amplitude, पूर्णांक period)
अणु
	काष्ठा waveक्रमm_निजी *devpriv;
	काष्ठा comedi_subdevice *s;
	पूर्णांक i;
	पूर्णांक ret;

	devpriv = comedi_alloc_devpriv(dev, माप(*devpriv));
	अगर (!devpriv)
		वापस -ENOMEM;

	devpriv->wf_amplitude = amplitude;
	devpriv->wf_period = period;

	ret = comedi_alloc_subdevices(dev, 2);
	अगर (ret)
		वापस ret;

	s = &dev->subdevices[0];
	dev->पढ़ो_subdev = s;
	/* analog input subdevice */
	s->type = COMEDI_SUBD_AI;
	s->subdev_flags = SDF_READABLE | SDF_GROUND | SDF_CMD_READ;
	s->n_chan = N_CHANS;
	s->maxdata = 0xffff;
	s->range_table = &waveक्रमm_ai_ranges;
	s->len_chanlist = s->n_chan * 2;
	s->insn_पढ़ो = waveक्रमm_ai_insn_पढ़ो;
	s->करो_cmd = waveक्रमm_ai_cmd;
	s->करो_cmdtest = waveक्रमm_ai_cmdtest;
	s->cancel = waveक्रमm_ai_cancel;
	s->insn_config = waveक्रमm_ai_insn_config;

	s = &dev->subdevices[1];
	dev->ग_लिखो_subdev = s;
	/* analog output subdevice (loopback) */
	s->type = COMEDI_SUBD_AO;
	s->subdev_flags = SDF_WRITABLE | SDF_GROUND | SDF_CMD_WRITE;
	s->n_chan = N_CHANS;
	s->maxdata = 0xffff;
	s->range_table = &waveक्रमm_ai_ranges;
	s->len_chanlist = s->n_chan;
	s->insn_ग_लिखो = waveक्रमm_ao_insn_ग_लिखो;
	s->insn_पढ़ो = waveक्रमm_ai_insn_पढ़ो;	/* करो same as AI insn_पढ़ो */
	s->करो_cmd = waveक्रमm_ao_cmd;
	s->करो_cmdtest = waveक्रमm_ao_cmdtest;
	s->cancel = waveक्रमm_ao_cancel;
	s->insn_config = waveक्रमm_ao_insn_config;

	/* Our शेष loopback value is just a 0V flatline */
	क्रम (i = 0; i < s->n_chan; i++)
		devpriv->ao_loopbacks[i] = s->maxdata / 2;

	devpriv->dev = dev;
	समयr_setup(&devpriv->ai_समयr, waveक्रमm_ai_समयr, 0);
	समयr_setup(&devpriv->ao_समयr, waveक्रमm_ao_समयr, 0);

	dev_info(dev->class_dev,
		 "%s: %u microvolt, %u microsecond waveform attached\n",
		 dev->board_name,
		 devpriv->wf_amplitude, devpriv->wf_period);

	वापस 0;
पूर्ण

अटल पूर्णांक waveक्रमm_attach(काष्ठा comedi_device *dev,
			   काष्ठा comedi_devconfig *it)
अणु
	पूर्णांक amplitude = it->options[0];
	पूर्णांक period = it->options[1];

	/* set शेष amplitude and period */
	अगर (amplitude <= 0)
		amplitude = 1000000;	/* 1 volt */
	अगर (period <= 0)
		period = 100000;	/* 0.1 sec */

	वापस waveक्रमm_common_attach(dev, amplitude, period);
पूर्ण

अटल पूर्णांक waveक्रमm_स्वतः_attach(काष्ठा comedi_device *dev,
				अचिन्हित दीर्घ context_unused)
अणु
	पूर्णांक amplitude = set_amplitude;
	पूर्णांक period = set_period;

	/* set शेष amplitude and period */
	अगर (!amplitude)
		amplitude = 1000000;	/* 1 volt */
	अगर (!period)
		period = 100000;	/* 0.1 sec */

	वापस waveक्रमm_common_attach(dev, amplitude, period);
पूर्ण

अटल व्योम waveक्रमm_detach(काष्ठा comedi_device *dev)
अणु
	काष्ठा waveक्रमm_निजी *devpriv = dev->निजी;

	अगर (devpriv) अणु
		del_समयr_sync(&devpriv->ai_समयr);
		del_समयr_sync(&devpriv->ao_समयr);
	पूर्ण
पूर्ण

अटल काष्ठा comedi_driver waveक्रमm_driver = अणु
	.driver_name	= "comedi_test",
	.module		= THIS_MODULE,
	.attach		= waveक्रमm_attach,
	.स्वतः_attach	= waveक्रमm_स्वतः_attach,
	.detach		= waveक्रमm_detach,
पूर्ण;

/*
 * For स्वतः-configuration, a device is created to stand in क्रम a
 * real hardware device.
 */
अटल पूर्णांक __init comedi_test_init(व्योम)
अणु
	पूर्णांक ret;

	ret = comedi_driver_रेजिस्टर(&waveक्रमm_driver);
	अगर (ret) अणु
		pr_err("comedi_test: unable to register driver\n");
		वापस ret;
	पूर्ण

	अगर (!config_mode) अणु
		ctcls = class_create(THIS_MODULE, CLASS_NAME);
		अगर (IS_ERR(ctcls)) अणु
			pr_warn("comedi_test: unable to create class\n");
			जाओ clean3;
		पूर्ण

		ctdev = device_create(ctcls, शून्य, MKDEV(0, 0), शून्य, DEV_NAME);
		अगर (IS_ERR(ctdev)) अणु
			pr_warn("comedi_test: unable to create device\n");
			जाओ clean2;
		पूर्ण

		ret = comedi_स्वतः_config(ctdev, &waveक्रमm_driver, 0);
		अगर (ret) अणु
			pr_warn("comedi_test: unable to auto-configure device\n");
			जाओ clean;
		पूर्ण
	पूर्ण

	वापस 0;

clean:
	device_destroy(ctcls, MKDEV(0, 0));
clean2:
	class_destroy(ctcls);
	ctdev = शून्य;
clean3:
	ctcls = शून्य;

	वापस 0;
पूर्ण
module_init(comedi_test_init);

अटल व्योम __निकास comedi_test_निकास(व्योम)
अणु
	अगर (ctdev)
		comedi_स्वतः_unconfig(ctdev);

	अगर (ctcls) अणु
		device_destroy(ctcls, MKDEV(0, 0));
		class_destroy(ctcls);
	पूर्ण

	comedi_driver_unरेजिस्टर(&waveक्रमm_driver);
पूर्ण
module_निकास(comedi_test_निकास);

MODULE_AUTHOR("Comedi https://www.comedi.org");
MODULE_DESCRIPTION("Comedi low-level driver");
MODULE_LICENSE("GPL");
