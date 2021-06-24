<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 *  module/drivers.c
 *  functions क्रम manipulating drivers
 *
 *  COMEDI - Linux Control and Measurement Device Interface
 *  Copyright (C) 1997-2000 David A. Schleef <ds@schleef.org>
 *  Copyright (C) 2002 Frank Mori Hess <fmhess@users.sourceक्रमge.net>
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/ioport.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-direction.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/firmware.h>

#समावेश "comedidev.h"
#समावेश "comedi_internal.h"

काष्ठा comedi_driver *comedi_drivers;
/* protects access to comedi_drivers */
DEFINE_MUTEX(comedi_drivers_list_lock);

/**
 * comedi_set_hw_dev() - Set hardware device associated with COMEDI device
 * @dev: COMEDI device.
 * @hw_dev: Hardware device.
 *
 * For स्वतःmatically configured COMEDI devices (resulting from a call to
 * comedi_स्वतः_config() or one of its wrappers from the low-level COMEDI
 * driver), comedi_set_hw_dev() is called स्वतःmatically by the COMEDI core
 * to associate the COMEDI device with the hardware device.  It can also be
 * called directly by "legacy" low-level COMEDI drivers that rely on the
 * %COMEDI_DEVCONFIG ioctl to configure the hardware as दीर्घ as the hardware
 * has a &काष्ठा device.
 *
 * If @dev->hw_dev is शून्य, it माला_लो a reference to @hw_dev and sets
 * @dev->hw_dev, otherwise, it करोes nothing.  Calling it multiple बार
 * with the same hardware device is not considered an error.  If it माला_लो
 * a reference to the hardware device, it will be स्वतःmatically 'put' when
 * the device is detached from COMEDI.
 *
 * Returns 0 अगर @dev->hw_dev was शून्य or the same as @hw_dev, otherwise
 * वापसs -EEXIST.
 */
पूर्णांक comedi_set_hw_dev(काष्ठा comedi_device *dev, काष्ठा device *hw_dev)
अणु
	अगर (hw_dev == dev->hw_dev)
		वापस 0;
	अगर (dev->hw_dev)
		वापस -EEXIST;
	dev->hw_dev = get_device(hw_dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_set_hw_dev);

अटल व्योम comedi_clear_hw_dev(काष्ठा comedi_device *dev)
अणु
	put_device(dev->hw_dev);
	dev->hw_dev = शून्य;
पूर्ण

/**
 * comedi_alloc_devpriv() - Allocate memory क्रम the device निजी data
 * @dev: COMEDI device.
 * @size: Size of the memory to allocate.
 *
 * The allocated memory is zero-filled.  @dev->निजी poपूर्णांकs to it on
 * वापस.  The memory will be स्वतःmatically मुक्तd when the COMEDI device is
 * "detached".
 *
 * Returns a poपूर्णांकer to the allocated memory, or शून्य on failure.
 */
व्योम *comedi_alloc_devpriv(काष्ठा comedi_device *dev, माप_प्रकार size)
अणु
	dev->निजी = kzalloc(size, GFP_KERNEL);
	वापस dev->निजी;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_alloc_devpriv);

/**
 * comedi_alloc_subdevices() - Allocate subdevices क्रम COMEDI device
 * @dev: COMEDI device.
 * @num_subdevices: Number of subdevices to allocate.
 *
 * Allocates and initializes an array of &काष्ठा comedi_subdevice क्रम the
 * COMEDI device.  If successful, sets @dev->subdevices to poपूर्णांक to the
 * first one and @dev->n_subdevices to the number.
 *
 * Returns 0 on success, -EINVAL अगर @num_subdevices is < 1, or -ENOMEM अगर
 * failed to allocate the memory.
 */
पूर्णांक comedi_alloc_subdevices(काष्ठा comedi_device *dev, पूर्णांक num_subdevices)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक i;

	अगर (num_subdevices < 1)
		वापस -EINVAL;

	s = kसुस्मृति(num_subdevices, माप(*s), GFP_KERNEL);
	अगर (!s)
		वापस -ENOMEM;
	dev->subdevices = s;
	dev->n_subdevices = num_subdevices;

	क्रम (i = 0; i < num_subdevices; ++i) अणु
		s = &dev->subdevices[i];
		s->device = dev;
		s->index = i;
		s->async_dma_dir = DMA_NONE;
		spin_lock_init(&s->spin_lock);
		s->minor = -1;
	पूर्ण
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_alloc_subdevices);

/**
 * comedi_alloc_subdev_पढ़ोback() - Allocate memory क्रम the subdevice पढ़ोback
 * @s: COMEDI subdevice.
 *
 * This is called by low-level COMEDI drivers to allocate an array to record
 * the last values written to a subdevice's analog output channels (at least
 * by the %INSN_WRITE inकाष्ठाion), to allow them to be पढ़ो back by an
 * %INSN_READ inकाष्ठाion.  It also provides a शेष handler क्रम the
 * %INSN_READ inकाष्ठाion unless one has alपढ़ोy been set.
 *
 * On success, @s->पढ़ोback poपूर्णांकs to the first element of the array, which
 * is zero-filled.  The low-level driver is responsible क्रम updating its
 * contents.  @s->insn_पढ़ो will be set to comedi_पढ़ोback_insn_पढ़ो()
 * unless it is alपढ़ोy non-शून्य.
 *
 * Returns 0 on success, -EINVAL अगर the subdevice has no channels, or
 * -ENOMEM on allocation failure.
 */
पूर्णांक comedi_alloc_subdev_पढ़ोback(काष्ठा comedi_subdevice *s)
अणु
	अगर (!s->n_chan)
		वापस -EINVAL;

	s->पढ़ोback = kसुस्मृति(s->n_chan, माप(*s->पढ़ोback), GFP_KERNEL);
	अगर (!s->पढ़ोback)
		वापस -ENOMEM;

	अगर (!s->insn_पढ़ो)
		s->insn_पढ़ो = comedi_पढ़ोback_insn_पढ़ो;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_alloc_subdev_पढ़ोback);

अटल व्योम comedi_device_detach_cleanup(काष्ठा comedi_device *dev)
अणु
	पूर्णांक i;
	काष्ठा comedi_subdevice *s;

	lockdep_निश्चित_held(&dev->attach_lock);
	lockdep_निश्चित_held(&dev->mutex);
	अगर (dev->subdevices) अणु
		क्रम (i = 0; i < dev->n_subdevices; i++) अणु
			s = &dev->subdevices[i];
			अगर (comedi_can_स्वतः_मुक्त_spriv(s))
				kमुक्त(s->निजी);
			comedi_मुक्त_subdevice_minor(s);
			अगर (s->async) अणु
				comedi_buf_alloc(dev, s, 0);
				kमुक्त(s->async);
			पूर्ण
			kमुक्त(s->पढ़ोback);
		पूर्ण
		kमुक्त(dev->subdevices);
		dev->subdevices = शून्य;
		dev->n_subdevices = 0;
	पूर्ण
	kमुक्त(dev->निजी);
	kमुक्त(dev->pacer);
	dev->निजी = शून्य;
	dev->pacer = शून्य;
	dev->driver = शून्य;
	dev->board_name = शून्य;
	dev->board_ptr = शून्य;
	dev->mmio = शून्य;
	dev->iobase = 0;
	dev->iolen = 0;
	dev->ioenabled = false;
	dev->irq = 0;
	dev->पढ़ो_subdev = शून्य;
	dev->ग_लिखो_subdev = शून्य;
	dev->खोलो = शून्य;
	dev->बंद = शून्य;
	comedi_clear_hw_dev(dev);
पूर्ण

व्योम comedi_device_detach(काष्ठा comedi_device *dev)
अणु
	lockdep_निश्चित_held(&dev->mutex);
	comedi_device_cancel_all(dev);
	करोwn_ग_लिखो(&dev->attach_lock);
	dev->attached = false;
	dev->detach_count++;
	अगर (dev->driver)
		dev->driver->detach(dev);
	comedi_device_detach_cleanup(dev);
	up_ग_लिखो(&dev->attach_lock);
पूर्ण

अटल पूर्णांक poll_invalid(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s)
अणु
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक insn_device_inval(काष्ठा comedi_device *dev,
			     काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	वापस -EINVAL;
पूर्ण

अटल अचिन्हित पूर्णांक get_zero_valid_routes(काष्ठा comedi_device *dev,
					  अचिन्हित पूर्णांक n_pairs,
					  अचिन्हित पूर्णांक *pair_data)
अणु
	वापस 0;
पूर्ण

पूर्णांक insn_inval(काष्ठा comedi_device *dev, काष्ठा comedi_subdevice *s,
	       काष्ठा comedi_insn *insn, अचिन्हित पूर्णांक *data)
अणु
	वापस -EINVAL;
पूर्ण

/**
 * comedi_पढ़ोback_insn_पढ़ो() - A generic (*insn_पढ़ो) क्रम subdevice पढ़ोback.
 * @dev: COMEDI device.
 * @s: COMEDI subdevice.
 * @insn: COMEDI inकाष्ठाion.
 * @data: Poपूर्णांकer to वापस the पढ़ोback data.
 *
 * Handles the %INSN_READ inकाष्ठाion क्रम subdevices that use the पढ़ोback
 * array allocated by comedi_alloc_subdev_पढ़ोback().  It may be used
 * directly as the subdevice's handler (@s->insn_पढ़ो) or called via a
 * wrapper.
 *
 * @insn->n is normally 1, which will पढ़ो a single value.  If higher, the
 * same element of the पढ़ोback array will be पढ़ो multiple बार.
 *
 * Returns @insn->n on success, or -EINVAL अगर @s->पढ़ोback is शून्य.
 */
पूर्णांक comedi_पढ़ोback_insn_पढ़ो(काष्ठा comedi_device *dev,
			      काष्ठा comedi_subdevice *s,
			      काष्ठा comedi_insn *insn,
			      अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	पूर्णांक i;

	अगर (!s->पढ़ोback)
		वापस -EINVAL;

	क्रम (i = 0; i < insn->n; i++)
		data[i] = s->पढ़ोback[chan];

	वापस insn->n;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_पढ़ोback_insn_पढ़ो);

/**
 * comedi_समयout() - Busy-रुको क्रम a driver condition to occur
 * @dev: COMEDI device.
 * @s: COMEDI subdevice.
 * @insn: COMEDI inकाष्ठाion.
 * @cb: Callback to check क्रम the condition.
 * @context: Private context from the driver.
 *
 * Busy-रुकोs क्रम up to a second (%COMEDI_TIMEOUT_MS) क्रम the condition or
 * some error (other than -EBUSY) to occur.  The parameters @dev, @s, @insn,
 * and @context are passed to the callback function, which वापसs -EBUSY to
 * जारी रुकोing or some other value to stop रुकोing (generally 0 अगर the
 * condition occurred, or some error value).
 *
 * Returns -ETIMEDOUT अगर समयd out, otherwise the वापस value from the
 * callback function.
 */
पूर्णांक comedi_समयout(काष्ठा comedi_device *dev,
		   काष्ठा comedi_subdevice *s,
		   काष्ठा comedi_insn *insn,
		   पूर्णांक (*cb)(काष्ठा comedi_device *dev,
			     काष्ठा comedi_subdevice *s,
			     काष्ठा comedi_insn *insn,
			     अचिन्हित दीर्घ context),
		   अचिन्हित दीर्घ context)
अणु
	अचिन्हित दीर्घ समयout = jअगरfies + msecs_to_jअगरfies(COMEDI_TIMEOUT_MS);
	पूर्णांक ret;

	जबतक (समय_beक्रमe(jअगरfies, समयout)) अणु
		ret = cb(dev, s, insn, context);
		अगर (ret != -EBUSY)
			वापस ret;	/* success (0) or non EBUSY त्रुटि_सं */
		cpu_relax();
	पूर्ण
	वापस -ETIMEDOUT;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_समयout);

/**
 * comedi_dio_insn_config() - Boilerplate (*insn_config) क्रम DIO subdevices
 * @dev: COMEDI device.
 * @s: COMEDI subdevice.
 * @insn: COMEDI inकाष्ठाion.
 * @data: Inकाष्ठाion parameters and वापस data.
 * @mask: io_bits mask क्रम grouped channels, or 0 क्रम single channel.
 *
 * If @mask is 0, it is replaced with a single-bit mask corresponding to the
 * channel number specअगरied by @insn->chanspec.  Otherwise, @mask
 * corresponds to a group of channels (which should include the specअगरied
 * channel) that are always configured together as inमाला_दो or outमाला_दो.
 *
 * Partially handles the %INSN_CONFIG_DIO_INPUT, %INSN_CONFIG_DIO_OUTPUTS,
 * and %INSN_CONFIG_DIO_QUERY inकाष्ठाions.  The first two update
 * @s->io_bits to record the directions of the masked channels.  The last
 * one sets @data[1] to the current direction of the group of channels
 * (%COMEDI_INPUT) or %COMEDI_OUTPUT) as recorded in @s->io_bits.
 *
 * The caller is responsible क्रम updating the DIO direction in the hardware
 * रेजिस्टरs अगर this function वापसs 0.
 *
 * Returns 0 क्रम a %INSN_CONFIG_DIO_INPUT or %INSN_CONFIG_DIO_OUTPUT
 * inकाष्ठाion, @insn->n (> 0) क्रम a %INSN_CONFIG_DIO_QUERY inकाष्ठाion, or
 * -EINVAL क्रम some other inकाष्ठाion.
 */
पूर्णांक comedi_dio_insn_config(काष्ठा comedi_device *dev,
			   काष्ठा comedi_subdevice *s,
			   काष्ठा comedi_insn *insn,
			   अचिन्हित पूर्णांक *data,
			   अचिन्हित पूर्णांक mask)
अणु
	अचिन्हित पूर्णांक chan_mask = 1 << CR_CHAN(insn->chanspec);

	अगर (!mask)
		mask = chan_mask;

	चयन (data[0]) अणु
	हाल INSN_CONFIG_DIO_INPUT:
		s->io_bits &= ~mask;
		अवरोध;

	हाल INSN_CONFIG_DIO_OUTPUT:
		s->io_bits |= mask;
		अवरोध;

	हाल INSN_CONFIG_DIO_QUERY:
		data[1] = (s->io_bits & mask) ? COMEDI_OUTPUT : COMEDI_INPUT;
		वापस insn->n;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_dio_insn_config);

/**
 * comedi_dio_update_state() - Update the पूर्णांकernal state of DIO subdevices
 * @s: COMEDI subdevice.
 * @data: The channel mask and bits to update.
 *
 * Updates @s->state which holds the पूर्णांकernal state of the outमाला_दो क्रम DIO
 * or DO subdevices (up to 32 channels).  @data[0] contains a bit-mask of
 * the channels to be updated.  @data[1] contains a bit-mask of those
 * channels to be set to '1'.  The caller is responsible क्रम updating the
 * outमाला_दो in hardware according to @s->state.  As a minimum, the channels
 * in the वापसed bit-mask need to be updated.
 *
 * Returns @mask with non-existent channels हटाओd.
 */
अचिन्हित पूर्णांक comedi_dio_update_state(काष्ठा comedi_subdevice *s,
				     अचिन्हित पूर्णांक *data)
अणु
	अचिन्हित पूर्णांक chanmask = (s->n_chan < 32) ? ((1 << s->n_chan) - 1)
						 : 0xffffffff;
	अचिन्हित पूर्णांक mask = data[0] & chanmask;
	अचिन्हित पूर्णांक bits = data[1];

	अगर (mask) अणु
		s->state &= ~mask;
		s->state |= (bits & mask);
	पूर्ण

	वापस mask;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_dio_update_state);

/**
 * comedi_bytes_per_scan_cmd() - Get length of asynchronous command "scan" in
 * bytes
 * @s: COMEDI subdevice.
 * @cmd: COMEDI command.
 *
 * Determines the overall scan length according to the subdevice type and the
 * number of channels in the scan क्रम the specअगरied command.
 *
 * For digital input, output or input/output subdevices, samples क्रम
 * multiple channels are assumed to be packed पूर्णांकo one or more अचिन्हित
 * लघु or अचिन्हित पूर्णांक values according to the subdevice's %SDF_LSAMPL
 * flag.  For other types of subdevice, samples are assumed to occupy a
 * whole अचिन्हित लघु or अचिन्हित पूर्णांक according to the %SDF_LSAMPL flag.
 *
 * Returns the overall scan length in bytes.
 */
अचिन्हित पूर्णांक comedi_bytes_per_scan_cmd(काष्ठा comedi_subdevice *s,
				       काष्ठा comedi_cmd *cmd)
अणु
	अचिन्हित पूर्णांक num_samples;
	अचिन्हित पूर्णांक bits_per_sample;

	चयन (s->type) अणु
	हाल COMEDI_SUBD_DI:
	हाल COMEDI_SUBD_DO:
	हाल COMEDI_SUBD_DIO:
		bits_per_sample = 8 * comedi_bytes_per_sample(s);
		num_samples = DIV_ROUND_UP(cmd->scan_end_arg, bits_per_sample);
		अवरोध;
	शेष:
		num_samples = cmd->scan_end_arg;
		अवरोध;
	पूर्ण
	वापस comedi_samples_to_bytes(s, num_samples);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_bytes_per_scan_cmd);

/**
 * comedi_bytes_per_scan() - Get length of asynchronous command "scan" in bytes
 * @s: COMEDI subdevice.
 *
 * Determines the overall scan length according to the subdevice type and the
 * number of channels in the scan क्रम the current command.
 *
 * For digital input, output or input/output subdevices, samples क्रम
 * multiple channels are assumed to be packed पूर्णांकo one or more अचिन्हित
 * लघु or अचिन्हित पूर्णांक values according to the subdevice's %SDF_LSAMPL
 * flag.  For other types of subdevice, samples are assumed to occupy a
 * whole अचिन्हित लघु or अचिन्हित पूर्णांक according to the %SDF_LSAMPL flag.
 *
 * Returns the overall scan length in bytes.
 */
अचिन्हित पूर्णांक comedi_bytes_per_scan(काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_cmd *cmd = &s->async->cmd;

	वापस comedi_bytes_per_scan_cmd(s, cmd);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_bytes_per_scan);

अटल अचिन्हित पूर्णांक __comedi_nscans_left(काष्ठा comedi_subdevice *s,
					 अचिन्हित पूर्णांक nscans)
अणु
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;

	अगर (cmd->stop_src == TRIG_COUNT) अणु
		अचिन्हित पूर्णांक scans_left = 0;

		अगर (async->scans_करोne < cmd->stop_arg)
			scans_left = cmd->stop_arg - async->scans_करोne;

		अगर (nscans > scans_left)
			nscans = scans_left;
	पूर्ण
	वापस nscans;
पूर्ण

/**
 * comedi_nscans_left() - Return the number of scans left in the command
 * @s: COMEDI subdevice.
 * @nscans: The expected number of scans or 0 क्रम all available scans.
 *
 * If @nscans is 0, it is set to the number of scans available in the
 * async buffer.
 *
 * If the async command has a stop_src of %TRIG_COUNT, the @nscans will be
 * checked against the number of scans reमुख्यing to complete the command.
 *
 * The वापस value will then be either the expected number of scans or the
 * number of scans reमुख्यing to complete the command, whichever is fewer.
 */
अचिन्हित पूर्णांक comedi_nscans_left(काष्ठा comedi_subdevice *s,
				अचिन्हित पूर्णांक nscans)
अणु
	अगर (nscans == 0) अणु
		अचिन्हित पूर्णांक nbytes = comedi_buf_पढ़ो_n_available(s);

		nscans = nbytes / comedi_bytes_per_scan(s);
	पूर्ण
	वापस __comedi_nscans_left(s, nscans);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_nscans_left);

/**
 * comedi_nsamples_left() - Return the number of samples left in the command
 * @s: COMEDI subdevice.
 * @nsamples: The expected number of samples.
 *
 * Returns the number of samples reमुख्यing to complete the command, or the
 * specअगरied expected number of samples (@nsamples), whichever is fewer.
 */
अचिन्हित पूर्णांक comedi_nsamples_left(काष्ठा comedi_subdevice *s,
				  अचिन्हित पूर्णांक nsamples)
अणु
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित दीर्घ दीर्घ scans_left;
	अचिन्हित दीर्घ दीर्घ samples_left;

	अगर (cmd->stop_src != TRIG_COUNT)
		वापस nsamples;

	scans_left = __comedi_nscans_left(s, cmd->stop_arg);
	अगर (!scans_left)
		वापस 0;

	samples_left = scans_left * cmd->scan_end_arg -
		comedi_bytes_to_samples(s, async->scan_progress);

	अगर (samples_left < nsamples)
		वापस samples_left;
	वापस nsamples;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_nsamples_left);

/**
 * comedi_inc_scan_progress() - Update scan progress in asynchronous command
 * @s: COMEDI subdevice.
 * @num_bytes: Amount of data in bytes to increment scan progress.
 *
 * Increments the scan progress by the number of bytes specअगरied by @num_bytes.
 * If the scan progress reaches or exceeds the scan length in bytes, reduce
 * it modulo the scan length in bytes and set the "end of scan" asynchronous
 * event flag (%COMEDI_CB_EOS) to be processed later.
 */
व्योम comedi_inc_scan_progress(काष्ठा comedi_subdevice *s,
			      अचिन्हित पूर्णांक num_bytes)
अणु
	काष्ठा comedi_async *async = s->async;
	काष्ठा comedi_cmd *cmd = &async->cmd;
	अचिन्हित पूर्णांक scan_length = comedi_bytes_per_scan(s);

	/* track the 'cur_chan' क्रम non-SDF_PACKED subdevices */
	अगर (!(s->subdev_flags & SDF_PACKED)) अणु
		async->cur_chan += comedi_bytes_to_samples(s, num_bytes);
		async->cur_chan %= cmd->chanlist_len;
	पूर्ण

	async->scan_progress += num_bytes;
	अगर (async->scan_progress >= scan_length) अणु
		अचिन्हित पूर्णांक nscans = async->scan_progress / scan_length;

		अगर (async->scans_करोne < (अच_पूर्णांक_उच्च - nscans))
			async->scans_करोne += nscans;
		अन्यथा
			async->scans_करोne = अच_पूर्णांक_उच्च;

		async->scan_progress %= scan_length;
		async->events |= COMEDI_CB_EOS;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(comedi_inc_scan_progress);

/**
 * comedi_handle_events() - Handle events and possibly stop acquisition
 * @dev: COMEDI device.
 * @s: COMEDI subdevice.
 *
 * Handles outstanding asynchronous acquisition event flags associated
 * with the subdevice.  Call the subdevice's @s->cancel() handler अगर the
 * "end of acquisition", "error" or "overflow" event flags are set in order
 * to stop the acquisition at the driver level.
 *
 * Calls comedi_event() to further process the event flags, which may mark
 * the asynchronous command as no दीर्घer running, possibly terminated with
 * an error, and may wake up tasks.
 *
 * Return a bit-mask of the handled events.
 */
अचिन्हित पूर्णांक comedi_handle_events(काष्ठा comedi_device *dev,
				  काष्ठा comedi_subdevice *s)
अणु
	अचिन्हित पूर्णांक events = s->async->events;

	अगर (events == 0)
		वापस events;

	अगर ((events & COMEDI_CB_CANCEL_MASK) && s->cancel)
		s->cancel(dev, s);

	comedi_event(dev, s);

	वापस events;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_handle_events);

अटल पूर्णांक insn_rw_emulate_bits(काष्ठा comedi_device *dev,
				काष्ठा comedi_subdevice *s,
				काष्ठा comedi_insn *insn,
				अचिन्हित पूर्णांक *data)
अणु
	काष्ठा comedi_insn _insn;
	अचिन्हित पूर्णांक chan = CR_CHAN(insn->chanspec);
	अचिन्हित पूर्णांक base_chan = (chan < 32) ? 0 : chan;
	अचिन्हित पूर्णांक _data[2];
	पूर्णांक ret;

	स_रखो(_data, 0, माप(_data));
	स_रखो(&_insn, 0, माप(_insn));
	_insn.insn = INSN_BITS;
	_insn.chanspec = base_chan;
	_insn.n = 2;
	_insn.subdev = insn->subdev;

	अगर (insn->insn == INSN_WRITE) अणु
		अगर (!(s->subdev_flags & SDF_WRITABLE))
			वापस -EINVAL;
		_data[0] = 1 << (chan - base_chan);		    /* mask */
		_data[1] = data[0] ? (1 << (chan - base_chan)) : 0; /* bits */
	पूर्ण

	ret = s->insn_bits(dev, s, &_insn, _data);
	अगर (ret < 0)
		वापस ret;

	अगर (insn->insn == INSN_READ)
		data[0] = (_data[1] >> (chan - base_chan)) & 1;

	वापस 1;
पूर्ण

अटल पूर्णांक __comedi_device_postconfig_async(काष्ठा comedi_device *dev,
					    काष्ठा comedi_subdevice *s)
अणु
	काष्ठा comedi_async *async;
	अचिन्हित पूर्णांक buf_size;
	पूर्णांक ret;

	lockdep_निश्चित_held(&dev->mutex);
	अगर ((s->subdev_flags & (SDF_CMD_READ | SDF_CMD_WRITE)) == 0) अणु
		dev_warn(dev->class_dev,
			 "async subdevices must support SDF_CMD_READ or SDF_CMD_WRITE\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!s->करो_cmdtest) अणु
		dev_warn(dev->class_dev,
			 "async subdevices must have a do_cmdtest() function\n");
		वापस -EINVAL;
	पूर्ण
	अगर (!s->cancel)
		dev_warn(dev->class_dev,
			 "async subdevices should have a cancel() function\n");

	async = kzalloc(माप(*async), GFP_KERNEL);
	अगर (!async)
		वापस -ENOMEM;

	init_रुकोqueue_head(&async->रुको_head);
	s->async = async;

	async->max_bufsize = comedi_शेष_buf_maxsize_kb * 1024;
	buf_size = comedi_शेष_buf_size_kb * 1024;
	अगर (buf_size > async->max_bufsize)
		buf_size = async->max_bufsize;

	अगर (comedi_buf_alloc(dev, s, buf_size) < 0) अणु
		dev_warn(dev->class_dev, "Buffer allocation failed\n");
		वापस -ENOMEM;
	पूर्ण
	अगर (s->buf_change) अणु
		ret = s->buf_change(dev, s);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	comedi_alloc_subdevice_minor(s);

	वापस 0;
पूर्ण

अटल पूर्णांक __comedi_device_postconfig(काष्ठा comedi_device *dev)
अणु
	काष्ठा comedi_subdevice *s;
	पूर्णांक ret;
	पूर्णांक i;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (!dev->insn_device_config)
		dev->insn_device_config = insn_device_inval;

	अगर (!dev->get_valid_routes)
		dev->get_valid_routes = get_zero_valid_routes;

	क्रम (i = 0; i < dev->n_subdevices; i++) अणु
		s = &dev->subdevices[i];

		अगर (s->type == COMEDI_SUBD_UNUSED)
			जारी;

		अगर (s->type == COMEDI_SUBD_DO) अणु
			अगर (s->n_chan < 32)
				s->io_bits = (1 << s->n_chan) - 1;
			अन्यथा
				s->io_bits = 0xffffffff;
		पूर्ण

		अगर (s->len_chanlist == 0)
			s->len_chanlist = 1;

		अगर (s->करो_cmd) अणु
			ret = __comedi_device_postconfig_async(dev, s);
			अगर (ret)
				वापस ret;
		पूर्ण

		अगर (!s->range_table && !s->range_table_list)
			s->range_table = &range_unknown;

		अगर (!s->insn_पढ़ो && s->insn_bits)
			s->insn_पढ़ो = insn_rw_emulate_bits;
		अगर (!s->insn_ग_लिखो && s->insn_bits)
			s->insn_ग_लिखो = insn_rw_emulate_bits;

		अगर (!s->insn_पढ़ो)
			s->insn_पढ़ो = insn_inval;
		अगर (!s->insn_ग_लिखो)
			s->insn_ग_लिखो = insn_inval;
		अगर (!s->insn_bits)
			s->insn_bits = insn_inval;
		अगर (!s->insn_config)
			s->insn_config = insn_inval;

		अगर (!s->poll)
			s->poll = poll_invalid;
	पूर्ण

	वापस 0;
पूर्ण

/* करो a little post-config cleanup */
अटल पूर्णांक comedi_device_postconfig(काष्ठा comedi_device *dev)
अणु
	पूर्णांक ret;

	lockdep_निश्चित_held(&dev->mutex);
	ret = __comedi_device_postconfig(dev);
	अगर (ret < 0)
		वापस ret;
	करोwn_ग_लिखो(&dev->attach_lock);
	dev->attached = true;
	up_ग_लिखो(&dev->attach_lock);
	वापस 0;
पूर्ण

/*
 * Generic recognize function क्रम drivers that रेजिस्टर their supported
 * board names.
 *
 * 'driv->board_name' points to a 'const char *' member within the
 * zeroth element of an array of some निजी board inक्रमmation
 * काष्ठाure, say 'struct foo_board' containing a member 'स्थिर अक्षर
 * *board_name' that is initialized to poपूर्णांक to a board name string that
 * is one of the candidates matched against this function's 'name'
 * parameter.
 *
 * 'driv->offset' is the size of the निजी board inक्रमmation
 * काष्ठाure, say 'sizeof(struct foo_board)', and 'driv->num_names' is
 * the length of the array of निजी board inक्रमmation काष्ठाures.
 *
 * If one of the board names in the array of निजी board inक्रमmation
 * काष्ठाures matches the name supplied to this function, the function
 * वापसs a poपूर्णांकer to the poपूर्णांकer to the board name, otherwise it
 * वापसs शून्य.  The वापस value ends up in the 'board_ptr' member of
 * a 'struct comedi_device' that the low-level comedi driver's
 * 'attach()' hook can convert to a poपूर्णांक to a particular element of its
 * array of निजी board inक्रमmation काष्ठाures by subtracting the
 * offset of the member that poपूर्णांकs to the board name.  (No subtraction
 * is required अगर the board name poपूर्णांकer is the first member of the
 * निजी board inक्रमmation काष्ठाure, which is generally the हाल.)
 */
अटल व्योम *comedi_recognize(काष्ठा comedi_driver *driv, स्थिर अक्षर *name)
अणु
	अक्षर **name_ptr = (अक्षर **)driv->board_name;
	पूर्णांक i;

	क्रम (i = 0; i < driv->num_names; i++) अणु
		अगर (म_भेद(*name_ptr, name) == 0)
			वापस name_ptr;
		name_ptr = (व्योम *)name_ptr + driv->offset;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम comedi_report_boards(काष्ठा comedi_driver *driv)
अणु
	अचिन्हित पूर्णांक i;
	स्थिर अक्षर *स्थिर *name_ptr;

	pr_info("comedi: valid board names for %s driver are:\n",
		driv->driver_name);

	name_ptr = driv->board_name;
	क्रम (i = 0; i < driv->num_names; i++) अणु
		pr_info(" %s\n", *name_ptr);
		name_ptr = (स्थिर अक्षर **)((अक्षर *)name_ptr + driv->offset);
	पूर्ण

	अगर (driv->num_names == 0)
		pr_info(" %s\n", driv->driver_name);
पूर्ण

/**
 * comedi_load_firmware() - Request and load firmware क्रम a device
 * @dev: COMEDI device.
 * @device: Hardware device.
 * @name: The name of the firmware image.
 * @cb: Callback to the upload the firmware image.
 * @context: Private context from the driver.
 *
 * Sends a firmware request क्रम the hardware device and रुकोs क्रम it.  Calls
 * the callback function to upload the firmware to the device, them releases
 * the firmware.
 *
 * Returns 0 on success, -EINVAL अगर @cb is शून्य, or a negative error number
 * from the firmware request or the callback function.
 */
पूर्णांक comedi_load_firmware(काष्ठा comedi_device *dev,
			 काष्ठा device *device,
			 स्थिर अक्षर *name,
			 पूर्णांक (*cb)(काष्ठा comedi_device *dev,
				   स्थिर u8 *data, माप_प्रकार size,
				   अचिन्हित दीर्घ context),
			 अचिन्हित दीर्घ context)
अणु
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	अगर (!cb)
		वापस -EINVAL;

	ret = request_firmware(&fw, name, device);
	अगर (ret == 0) अणु
		ret = cb(dev, fw->data, fw->size, context);
		release_firmware(fw);
	पूर्ण

	वापस ret < 0 ? ret : 0;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_load_firmware);

/**
 * __comedi_request_region() - Request an I/O region क्रम a legacy driver
 * @dev: COMEDI device.
 * @start: Base address of the I/O region.
 * @len: Length of the I/O region.
 *
 * Requests the specअगरied I/O port region which must start at a non-zero
 * address.
 *
 * Returns 0 on success, -EINVAL अगर @start is 0, or -EIO अगर the request
 * fails.
 */
पूर्णांक __comedi_request_region(काष्ठा comedi_device *dev,
			    अचिन्हित दीर्घ start, अचिन्हित दीर्घ len)
अणु
	अगर (!start) अणु
		dev_warn(dev->class_dev,
			 "%s: a I/O base address must be specified\n",
			 dev->board_name);
		वापस -EINVAL;
	पूर्ण

	अगर (!request_region(start, len, dev->board_name)) अणु
		dev_warn(dev->class_dev, "%s: I/O port conflict (%#lx,%lu)\n",
			 dev->board_name, start, len);
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(__comedi_request_region);

/**
 * comedi_request_region() - Request an I/O region क्रम a legacy driver
 * @dev: COMEDI device.
 * @start: Base address of the I/O region.
 * @len: Length of the I/O region.
 *
 * Requests the specअगरied I/O port region which must start at a non-zero
 * address.
 *
 * On success, @dev->iobase is set to the base address of the region and
 * @dev->iolen is set to its length.
 *
 * Returns 0 on success, -EINVAL अगर @start is 0, or -EIO अगर the request
 * fails.
 */
पूर्णांक comedi_request_region(काष्ठा comedi_device *dev,
			  अचिन्हित दीर्घ start, अचिन्हित दीर्घ len)
अणु
	पूर्णांक ret;

	ret = __comedi_request_region(dev, start, len);
	अगर (ret == 0) अणु
		dev->iobase = start;
		dev->iolen = len;
	पूर्ण

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_request_region);

/**
 * comedi_legacy_detach() - A generic (*detach) function क्रम legacy drivers
 * @dev: COMEDI device.
 *
 * This is a simple, generic 'detach' handler क्रम legacy COMEDI devices that
 * just use a single I/O port region and possibly an IRQ and that करोn't need
 * any special clean-up क्रम their निजी device or subdevice storage.  It
 * can also be called by a driver-specअगरic 'detach' handler.
 *
 * If @dev->irq is non-zero, the IRQ will be मुक्तd.  If @dev->iobase and
 * @dev->iolen are both non-zero, the I/O port region will be released.
 */
व्योम comedi_legacy_detach(काष्ठा comedi_device *dev)
अणु
	अगर (dev->irq) अणु
		मुक्त_irq(dev->irq, dev);
		dev->irq = 0;
	पूर्ण
	अगर (dev->iobase && dev->iolen) अणु
		release_region(dev->iobase, dev->iolen);
		dev->iobase = 0;
		dev->iolen = 0;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(comedi_legacy_detach);

पूर्णांक comedi_device_attach(काष्ठा comedi_device *dev, काष्ठा comedi_devconfig *it)
अणु
	काष्ठा comedi_driver *driv;
	पूर्णांक ret;

	lockdep_निश्चित_held(&dev->mutex);
	अगर (dev->attached)
		वापस -EBUSY;

	mutex_lock(&comedi_drivers_list_lock);
	क्रम (driv = comedi_drivers; driv; driv = driv->next) अणु
		अगर (!try_module_get(driv->module))
			जारी;
		अगर (driv->num_names) अणु
			dev->board_ptr = comedi_recognize(driv, it->board_name);
			अगर (dev->board_ptr)
				अवरोध;
		पूर्ण अन्यथा अगर (म_भेद(driv->driver_name, it->board_name) == 0) अणु
			अवरोध;
		पूर्ण
		module_put(driv->module);
	पूर्ण
	अगर (!driv) अणु
		/*  recognize has failed अगर we get here */
		/*  report valid board names beक्रमe वापसing error */
		क्रम (driv = comedi_drivers; driv; driv = driv->next) अणु
			अगर (!try_module_get(driv->module))
				जारी;
			comedi_report_boards(driv);
			module_put(driv->module);
		पूर्ण
		ret = -EIO;
		जाओ out;
	पूर्ण
	अगर (!driv->attach) अणु
		/* driver करोes not support manual configuration */
		dev_warn(dev->class_dev,
			 "driver '%s' does not support attach using comedi_config\n",
			 driv->driver_name);
		module_put(driv->module);
		ret = -EIO;
		जाओ out;
	पूर्ण
	dev->driver = driv;
	dev->board_name = dev->board_ptr ? *(स्थिर अक्षर **)dev->board_ptr
					 : dev->driver->driver_name;
	ret = driv->attach(dev, it);
	अगर (ret >= 0)
		ret = comedi_device_postconfig(dev);
	अगर (ret < 0) अणु
		comedi_device_detach(dev);
		module_put(driv->module);
	पूर्ण
	/* On success, the driver module count has been incremented. */
out:
	mutex_unlock(&comedi_drivers_list_lock);
	वापस ret;
पूर्ण

/**
 * comedi_स्वतः_config() - Create a COMEDI device क्रम a hardware device
 * @hardware_device: Hardware device.
 * @driver: COMEDI low-level driver क्रम the hardware device.
 * @context: Driver context क्रम the स्वतः_attach handler.
 *
 * Allocates a new COMEDI device क्रम the hardware device and calls the
 * low-level driver's 'auto_attach' handler to set-up the hardware and
 * allocate the COMEDI subdevices.  Additional "post-configuration" setting
 * up is perक्रमmed on successful वापस from the 'auto_attach' handler.
 * If the 'auto_attach' handler fails, the low-level driver's 'detach'
 * handler will be called as part of the clean-up.
 *
 * This is usually called from a wrapper function in a bus-specअगरic COMEDI
 * module, which in turn is usually called from a bus device 'probe'
 * function in the low-level driver.
 *
 * Returns 0 on success, -EINVAL अगर the parameters are invalid or the
 * post-configuration determines the driver has set the COMEDI device up
 * incorrectly, -ENOMEM अगर failed to allocate memory, -EBUSY अगर run out of
 * COMEDI minor device numbers, or some negative error number वापसed by
 * the driver's 'auto_attach' handler.
 */
पूर्णांक comedi_स्वतः_config(काष्ठा device *hardware_device,
		       काष्ठा comedi_driver *driver, अचिन्हित दीर्घ context)
अणु
	काष्ठा comedi_device *dev;
	पूर्णांक ret;

	अगर (!hardware_device) अणु
		pr_warn("BUG! %s called with NULL hardware_device\n", __func__);
		वापस -EINVAL;
	पूर्ण
	अगर (!driver) अणु
		dev_warn(hardware_device,
			 "BUG! %s called with NULL comedi driver\n", __func__);
		वापस -EINVAL;
	पूर्ण

	अगर (!driver->स्वतः_attach) अणु
		dev_warn(hardware_device,
			 "BUG! comedi driver '%s' has no auto_attach handler\n",
			 driver->driver_name);
		वापस -EINVAL;
	पूर्ण

	dev = comedi_alloc_board_minor(hardware_device);
	अगर (IS_ERR(dev)) अणु
		dev_warn(hardware_device,
			 "driver '%s' could not create device.\n",
			 driver->driver_name);
		वापस PTR_ERR(dev);
	पूर्ण
	/* Note: comedi_alloc_board_minor() locked dev->mutex. */
	lockdep_निश्चित_held(&dev->mutex);

	dev->driver = driver;
	dev->board_name = dev->driver->driver_name;
	ret = driver->स्वतः_attach(dev, context);
	अगर (ret >= 0)
		ret = comedi_device_postconfig(dev);

	अगर (ret < 0) अणु
		dev_warn(hardware_device,
			 "driver '%s' failed to auto-configure device.\n",
			 driver->driver_name);
		mutex_unlock(&dev->mutex);
		comedi_release_hardware_device(hardware_device);
	पूर्ण अन्यथा अणु
		/*
		 * class_dev should be set properly here
		 *  after a successful स्वतः config
		 */
		dev_info(dev->class_dev,
			 "driver '%s' has successfully auto-configured '%s'.\n",
			 driver->driver_name, dev->board_name);
		mutex_unlock(&dev->mutex);
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_स्वतः_config);

/**
 * comedi_स्वतः_unconfig() - Unconfigure स्वतः-allocated COMEDI device
 * @hardware_device: Hardware device previously passed to
 *                   comedi_स्वतः_config().
 *
 * Cleans up and eventually destroys the COMEDI device allocated by
 * comedi_स्वतः_config() क्रम the same hardware device.  As part of this
 * clean-up, the low-level COMEDI driver's 'detach' handler will be called.
 * (The COMEDI device itself will persist in an unattached state अगर it is
 * still खोलो, until it is released, and any mmapped buffers will persist
 * until they are munmapped.)
 *
 * This is usually called from a wrapper module in a bus-specअगरic COMEDI
 * module, which in turn is usually set as the bus device 'remove' function
 * in the low-level COMEDI driver.
 */
व्योम comedi_स्वतः_unconfig(काष्ठा device *hardware_device)
अणु
	अगर (!hardware_device)
		वापस;
	comedi_release_hardware_device(hardware_device);
पूर्ण
EXPORT_SYMBOL_GPL(comedi_स्वतः_unconfig);

/**
 * comedi_driver_रेजिस्टर() - Register a low-level COMEDI driver
 * @driver: Low-level COMEDI driver.
 *
 * The low-level COMEDI driver is added to the list of रेजिस्टरed COMEDI
 * drivers.  This is used by the handler क्रम the "/proc/comedi" file and is
 * also used by the handler क्रम the %COMEDI_DEVCONFIG ioctl to configure
 * "legacy" COMEDI devices (क्रम those low-level drivers that support it).
 *
 * Returns 0.
 */
पूर्णांक comedi_driver_रेजिस्टर(काष्ठा comedi_driver *driver)
अणु
	mutex_lock(&comedi_drivers_list_lock);
	driver->next = comedi_drivers;
	comedi_drivers = driver;
	mutex_unlock(&comedi_drivers_list_lock);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(comedi_driver_रेजिस्टर);

/**
 * comedi_driver_unरेजिस्टर() - Unरेजिस्टर a low-level COMEDI driver
 * @driver: Low-level COMEDI driver.
 *
 * The low-level COMEDI driver is हटाओd from the list of रेजिस्टरed COMEDI
 * drivers.  Detaches any COMEDI devices attached to the driver, which will
 * result in the low-level driver's 'detach' handler being called क्रम those
 * devices beक्रमe this function वापसs.
 */
व्योम comedi_driver_unरेजिस्टर(काष्ठा comedi_driver *driver)
अणु
	काष्ठा comedi_driver *prev;
	पूर्णांक i;

	/* unlink the driver */
	mutex_lock(&comedi_drivers_list_lock);
	अगर (comedi_drivers == driver) अणु
		comedi_drivers = driver->next;
	पूर्ण अन्यथा अणु
		क्रम (prev = comedi_drivers; prev->next; prev = prev->next) अणु
			अगर (prev->next == driver) अणु
				prev->next = driver->next;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	mutex_unlock(&comedi_drivers_list_lock);

	/* check क्रम devices using this driver */
	क्रम (i = 0; i < COMEDI_NUM_BOARD_MINORS; i++) अणु
		काष्ठा comedi_device *dev = comedi_dev_get_from_minor(i);

		अगर (!dev)
			जारी;

		mutex_lock(&dev->mutex);
		अगर (dev->attached && dev->driver == driver) अणु
			अगर (dev->use_count)
				dev_warn(dev->class_dev,
					 "BUG! detaching device with use_count=%d\n",
					 dev->use_count);
			comedi_device_detach(dev);
		पूर्ण
		mutex_unlock(&dev->mutex);
		comedi_dev_put(dev);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(comedi_driver_unरेजिस्टर);
