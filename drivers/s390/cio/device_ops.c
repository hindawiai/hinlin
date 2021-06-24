<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * Copyright IBM Corp. 2002, 2009
 *
 * Author(s): Martin Schwidefsky (schwidefsky@de.ibm.com)
 *	      Cornelia Huck (cornelia.huck@de.ibm.com)
 */
#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/completion.h>

#समावेश <यंत्र/ccwdev.h>
#समावेश <यंत्र/idals.h>
#समावेश <यंत्र/chpid.h>
#समावेश <यंत्र/fcx.h>

#समावेश "cio.h"
#समावेश "cio_debug.h"
#समावेश "css.h"
#समावेश "chsc.h"
#समावेश "device.h"
#समावेश "chp.h"

/**
 * ccw_device_set_options_mask() - set some options and unset the rest
 * @cdev: device क्रम which the options are to be set
 * @flags: options to be set
 *
 * All flags specअगरied in @flags are set, all flags not specअगरied in @flags
 * are cleared.
 * Returns:
 *   %0 on success, -%EINVAL on an invalid flag combination.
 */
पूर्णांक ccw_device_set_options_mask(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ flags)
अणु
       /*
	* The flag usage is mutal exclusive ...
	*/
	अगर ((flags & CCWDEV_EARLY_NOTIFICATION) &&
	    (flags & CCWDEV_REPORT_ALL))
		वापस -EINVAL;
	cdev->निजी->options.fast = (flags & CCWDEV_EARLY_NOTIFICATION) != 0;
	cdev->निजी->options.repall = (flags & CCWDEV_REPORT_ALL) != 0;
	cdev->निजी->options.pgroup = (flags & CCWDEV_DO_PATHGROUP) != 0;
	cdev->निजी->options.क्रमce = (flags & CCWDEV_ALLOW_FORCE) != 0;
	cdev->निजी->options.mpath = (flags & CCWDEV_DO_MULTIPATH) != 0;
	वापस 0;
पूर्ण

/**
 * ccw_device_set_options() - set some options
 * @cdev: device क्रम which the options are to be set
 * @flags: options to be set
 *
 * All flags specअगरied in @flags are set, the reमुख्यder is left untouched.
 * Returns:
 *   %0 on success, -%EINVAL अगर an invalid flag combination would ensue.
 */
पूर्णांक ccw_device_set_options(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ flags)
अणु
       /*
	* The flag usage is mutal exclusive ...
	*/
	अगर (((flags & CCWDEV_EARLY_NOTIFICATION) &&
	    (flags & CCWDEV_REPORT_ALL)) ||
	    ((flags & CCWDEV_EARLY_NOTIFICATION) &&
	     cdev->निजी->options.repall) ||
	    ((flags & CCWDEV_REPORT_ALL) &&
	     cdev->निजी->options.fast))
		वापस -EINVAL;
	cdev->निजी->options.fast |= (flags & CCWDEV_EARLY_NOTIFICATION) != 0;
	cdev->निजी->options.repall |= (flags & CCWDEV_REPORT_ALL) != 0;
	cdev->निजी->options.pgroup |= (flags & CCWDEV_DO_PATHGROUP) != 0;
	cdev->निजी->options.क्रमce |= (flags & CCWDEV_ALLOW_FORCE) != 0;
	cdev->निजी->options.mpath |= (flags & CCWDEV_DO_MULTIPATH) != 0;
	वापस 0;
पूर्ण

/**
 * ccw_device_clear_options() - clear some options
 * @cdev: device क्रम which the options are to be cleared
 * @flags: options to be cleared
 *
 * All flags specअगरied in @flags are cleared, the reमुख्यder is left untouched.
 */
व्योम ccw_device_clear_options(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ flags)
अणु
	cdev->निजी->options.fast &= (flags & CCWDEV_EARLY_NOTIFICATION) == 0;
	cdev->निजी->options.repall &= (flags & CCWDEV_REPORT_ALL) == 0;
	cdev->निजी->options.pgroup &= (flags & CCWDEV_DO_PATHGROUP) == 0;
	cdev->निजी->options.क्रमce &= (flags & CCWDEV_ALLOW_FORCE) == 0;
	cdev->निजी->options.mpath &= (flags & CCWDEV_DO_MULTIPATH) == 0;
पूर्ण

/**
 * ccw_device_is_pathgroup() - determine अगर paths to this device are grouped
 * @cdev: ccw device
 *
 * Return non-zero अगर there is a path group, zero otherwise.
 */
पूर्णांक ccw_device_is_pathgroup(काष्ठा ccw_device *cdev)
अणु
	वापस cdev->निजी->flags.pgroup;
पूर्ण
EXPORT_SYMBOL(ccw_device_is_pathgroup);

/**
 * ccw_device_is_multipath() - determine अगर device is operating in multipath mode
 * @cdev: ccw device
 *
 * Return non-zero अगर device is operating in multipath mode, zero otherwise.
 */
पूर्णांक ccw_device_is_multipath(काष्ठा ccw_device *cdev)
अणु
	वापस cdev->निजी->flags.mpath;
पूर्ण
EXPORT_SYMBOL(ccw_device_is_multipath);

/**
 * ccw_device_clear() - terminate I/O request processing
 * @cdev: target ccw device
 * @पूर्णांकparm: पूर्णांकerruption parameter to be वापसed upon conclusion of csch
 *
 * ccw_device_clear() calls csch on @cdev's subchannel.
 * Returns:
 *  %0 on success,
 *  -%ENODEV on device not operational,
 *  -%EINVAL on invalid device state.
 * Context:
 *  Interrupts disabled, ccw device lock held
 */
पूर्णांक ccw_device_clear(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ पूर्णांकparm)
अणु
	काष्ठा subchannel *sch;
	पूर्णांक ret;

	अगर (!cdev || !cdev->dev.parent)
		वापस -ENODEV;
	sch = to_subchannel(cdev->dev.parent);
	अगर (!sch->schib.pmcw.ena)
		वापस -EINVAL;
	अगर (cdev->निजी->state == DEV_STATE_NOT_OPER)
		वापस -ENODEV;
	अगर (cdev->निजी->state != DEV_STATE_ONLINE &&
	    cdev->निजी->state != DEV_STATE_W4SENSE)
		वापस -EINVAL;

	ret = cio_clear(sch);
	अगर (ret == 0)
		cdev->निजी->पूर्णांकparm = पूर्णांकparm;
	वापस ret;
पूर्ण

/**
 * ccw_device_start_समयout_key() - start a s390 channel program with समयout and key
 * @cdev: target ccw device
 * @cpa: logical start address of channel program
 * @पूर्णांकparm: user specअगरic पूर्णांकerruption parameter; will be presented back to
 *	     @cdev's पूर्णांकerrupt handler. Allows a device driver to associate
 *	     the पूर्णांकerrupt with a particular I/O request.
 * @lpm: defines the channel path to be used क्रम a specअगरic I/O request. A
 *	 value of 0 will make cio use the opm.
 * @key: storage key to be used क्रम the I/O
 * @flags: additional flags; defines the action to be perक्रमmed क्रम I/O
 *	   processing.
 * @expires: समयout value in jअगरfies
 *
 * Start a S/390 channel program. When the पूर्णांकerrupt arrives, the
 * IRQ handler is called, either immediately, delayed (dev-end missing,
 * or sense required) or never (no IRQ handler रेजिस्टरed).
 * This function notअगरies the device driver अगर the channel program has not
 * completed during the समय specअगरied by @expires. If a समयout occurs, the
 * channel program is terminated via xsch, hsch or csch, and the device's
 * पूर्णांकerrupt handler will be called with an irb containing ERR_PTR(-%ETIMEDOUT).
 * The पूर्णांकerruption handler will echo back the @पूर्णांकparm specअगरied here, unless
 * another पूर्णांकerruption parameter is specअगरied by a subsequent invocation of
 * ccw_device_halt() or ccw_device_clear().
 * Returns:
 *  %0, अगर the operation was successful;
 *  -%EBUSY, अगर the device is busy, or status pending;
 *  -%EACCES, अगर no path specअगरied in @lpm is operational;
 *  -%ENODEV, अगर the device is not operational.
 * Context:
 *  Interrupts disabled, ccw device lock held
 */
पूर्णांक ccw_device_start_समयout_key(काष्ठा ccw_device *cdev, काष्ठा ccw1 *cpa,
				 अचिन्हित दीर्घ पूर्णांकparm, __u8 lpm, __u8 key,
				 अचिन्हित दीर्घ flags, पूर्णांक expires)
अणु
	काष्ठा subchannel *sch;
	पूर्णांक ret;

	अगर (!cdev || !cdev->dev.parent)
		वापस -ENODEV;
	sch = to_subchannel(cdev->dev.parent);
	अगर (!sch->schib.pmcw.ena)
		वापस -EINVAL;
	अगर (cdev->निजी->state == DEV_STATE_NOT_OPER)
		वापस -ENODEV;
	अगर (cdev->निजी->state == DEV_STATE_VERIFY) अणु
		/* Remember to fake irb when finished. */
		अगर (!cdev->निजी->flags.fake_irb) अणु
			cdev->निजी->flags.fake_irb = FAKE_CMD_IRB;
			cdev->निजी->पूर्णांकparm = पूर्णांकparm;
			वापस 0;
		पूर्ण अन्यथा
			/* There's alपढ़ोy a fake I/O around. */
			वापस -EBUSY;
	पूर्ण
	अगर (cdev->निजी->state != DEV_STATE_ONLINE ||
	    ((sch->schib.scsw.cmd.stctl & SCSW_STCTL_PRIM_STATUS) &&
	     !(sch->schib.scsw.cmd.stctl & SCSW_STCTL_SEC_STATUS)) ||
	    cdev->निजी->flags.करोverअगरy)
		वापस -EBUSY;
	ret = cio_set_options (sch, flags);
	अगर (ret)
		वापस ret;
	/* Adjust requested path mask to exclude unusable paths. */
	अगर (lpm) अणु
		lpm &= sch->lpm;
		अगर (lpm == 0)
			वापस -EACCES;
	पूर्ण
	ret = cio_start_key (sch, cpa, lpm, key);
	चयन (ret) अणु
	हाल 0:
		cdev->निजी->पूर्णांकparm = पूर्णांकparm;
		अगर (expires)
			ccw_device_set_समयout(cdev, expires);
		अवरोध;
	हाल -EACCES:
	हाल -ENODEV:
		dev_fsm_event(cdev, DEV_EVENT_VERIFY);
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * ccw_device_start_key() - start a s390 channel program with key
 * @cdev: target ccw device
 * @cpa: logical start address of channel program
 * @पूर्णांकparm: user specअगरic पूर्णांकerruption parameter; will be presented back to
 *	     @cdev's पूर्णांकerrupt handler. Allows a device driver to associate
 *	     the पूर्णांकerrupt with a particular I/O request.
 * @lpm: defines the channel path to be used क्रम a specअगरic I/O request. A
 *	 value of 0 will make cio use the opm.
 * @key: storage key to be used क्रम the I/O
 * @flags: additional flags; defines the action to be perक्रमmed क्रम I/O
 *	   processing.
 *
 * Start a S/390 channel program. When the पूर्णांकerrupt arrives, the
 * IRQ handler is called, either immediately, delayed (dev-end missing,
 * or sense required) or never (no IRQ handler रेजिस्टरed).
 * The पूर्णांकerruption handler will echo back the @पूर्णांकparm specअगरied here, unless
 * another पूर्णांकerruption parameter is specअगरied by a subsequent invocation of
 * ccw_device_halt() or ccw_device_clear().
 * Returns:
 *  %0, अगर the operation was successful;
 *  -%EBUSY, अगर the device is busy, or status pending;
 *  -%EACCES, अगर no path specअगरied in @lpm is operational;
 *  -%ENODEV, अगर the device is not operational.
 * Context:
 *  Interrupts disabled, ccw device lock held
 */
पूर्णांक ccw_device_start_key(काष्ठा ccw_device *cdev, काष्ठा ccw1 *cpa,
			 अचिन्हित दीर्घ पूर्णांकparm, __u8 lpm, __u8 key,
			 अचिन्हित दीर्घ flags)
अणु
	वापस ccw_device_start_समयout_key(cdev, cpa, पूर्णांकparm, lpm, key,
					    flags, 0);
पूर्ण

/**
 * ccw_device_start() - start a s390 channel program
 * @cdev: target ccw device
 * @cpa: logical start address of channel program
 * @पूर्णांकparm: user specअगरic पूर्णांकerruption parameter; will be presented back to
 *	     @cdev's पूर्णांकerrupt handler. Allows a device driver to associate
 *	     the पूर्णांकerrupt with a particular I/O request.
 * @lpm: defines the channel path to be used क्रम a specअगरic I/O request. A
 *	 value of 0 will make cio use the opm.
 * @flags: additional flags; defines the action to be perक्रमmed क्रम I/O
 *	   processing.
 *
 * Start a S/390 channel program. When the पूर्णांकerrupt arrives, the
 * IRQ handler is called, either immediately, delayed (dev-end missing,
 * or sense required) or never (no IRQ handler रेजिस्टरed).
 * The पूर्णांकerruption handler will echo back the @पूर्णांकparm specअगरied here, unless
 * another पूर्णांकerruption parameter is specअगरied by a subsequent invocation of
 * ccw_device_halt() or ccw_device_clear().
 * Returns:
 *  %0, अगर the operation was successful;
 *  -%EBUSY, अगर the device is busy, or status pending;
 *  -%EACCES, अगर no path specअगरied in @lpm is operational;
 *  -%ENODEV, अगर the device is not operational.
 * Context:
 *  Interrupts disabled, ccw device lock held
 */
पूर्णांक ccw_device_start(काष्ठा ccw_device *cdev, काष्ठा ccw1 *cpa,
		     अचिन्हित दीर्घ पूर्णांकparm, __u8 lpm, अचिन्हित दीर्घ flags)
अणु
	वापस ccw_device_start_key(cdev, cpa, पूर्णांकparm, lpm,
				    PAGE_DEFAULT_KEY, flags);
पूर्ण

/**
 * ccw_device_start_समयout() - start a s390 channel program with समयout
 * @cdev: target ccw device
 * @cpa: logical start address of channel program
 * @पूर्णांकparm: user specअगरic पूर्णांकerruption parameter; will be presented back to
 *	     @cdev's पूर्णांकerrupt handler. Allows a device driver to associate
 *	     the पूर्णांकerrupt with a particular I/O request.
 * @lpm: defines the channel path to be used क्रम a specअगरic I/O request. A
 *	 value of 0 will make cio use the opm.
 * @flags: additional flags; defines the action to be perक्रमmed क्रम I/O
 *	   processing.
 * @expires: समयout value in jअगरfies
 *
 * Start a S/390 channel program. When the पूर्णांकerrupt arrives, the
 * IRQ handler is called, either immediately, delayed (dev-end missing,
 * or sense required) or never (no IRQ handler रेजिस्टरed).
 * This function notअगरies the device driver अगर the channel program has not
 * completed during the समय specअगरied by @expires. If a समयout occurs, the
 * channel program is terminated via xsch, hsch or csch, and the device's
 * पूर्णांकerrupt handler will be called with an irb containing ERR_PTR(-%ETIMEDOUT).
 * The पूर्णांकerruption handler will echo back the @पूर्णांकparm specअगरied here, unless
 * another पूर्णांकerruption parameter is specअगरied by a subsequent invocation of
 * ccw_device_halt() or ccw_device_clear().
 * Returns:
 *  %0, अगर the operation was successful;
 *  -%EBUSY, अगर the device is busy, or status pending;
 *  -%EACCES, अगर no path specअगरied in @lpm is operational;
 *  -%ENODEV, अगर the device is not operational.
 * Context:
 *  Interrupts disabled, ccw device lock held
 */
पूर्णांक ccw_device_start_समयout(काष्ठा ccw_device *cdev, काष्ठा ccw1 *cpa,
			     अचिन्हित दीर्घ पूर्णांकparm, __u8 lpm,
			     अचिन्हित दीर्घ flags, पूर्णांक expires)
अणु
	वापस ccw_device_start_समयout_key(cdev, cpa, पूर्णांकparm, lpm,
					    PAGE_DEFAULT_KEY, flags,
					    expires);
पूर्ण


/**
 * ccw_device_halt() - halt I/O request processing
 * @cdev: target ccw device
 * @पूर्णांकparm: पूर्णांकerruption parameter to be वापसed upon conclusion of hsch
 *
 * ccw_device_halt() calls hsch on @cdev's subchannel.
 * The पूर्णांकerruption handler will echo back the @पूर्णांकparm specअगरied here, unless
 * another पूर्णांकerruption parameter is specअगरied by a subsequent invocation of
 * ccw_device_clear().
 * Returns:
 *  %0 on success,
 *  -%ENODEV on device not operational,
 *  -%EINVAL on invalid device state,
 *  -%EBUSY on device busy or पूर्णांकerrupt pending.
 * Context:
 *  Interrupts disabled, ccw device lock held
 */
पूर्णांक ccw_device_halt(काष्ठा ccw_device *cdev, अचिन्हित दीर्घ पूर्णांकparm)
अणु
	काष्ठा subchannel *sch;
	पूर्णांक ret;

	अगर (!cdev || !cdev->dev.parent)
		वापस -ENODEV;
	sch = to_subchannel(cdev->dev.parent);
	अगर (!sch->schib.pmcw.ena)
		वापस -EINVAL;
	अगर (cdev->निजी->state == DEV_STATE_NOT_OPER)
		वापस -ENODEV;
	अगर (cdev->निजी->state != DEV_STATE_ONLINE &&
	    cdev->निजी->state != DEV_STATE_W4SENSE)
		वापस -EINVAL;

	ret = cio_halt(sch);
	अगर (ret == 0)
		cdev->निजी->पूर्णांकparm = पूर्णांकparm;
	वापस ret;
पूर्ण

/**
 * ccw_device_resume() - resume channel program execution
 * @cdev: target ccw device
 *
 * ccw_device_resume() calls rsch on @cdev's subchannel.
 * Returns:
 *  %0 on success,
 *  -%ENODEV on device not operational,
 *  -%EINVAL on invalid device state,
 *  -%EBUSY on device busy or पूर्णांकerrupt pending.
 * Context:
 *  Interrupts disabled, ccw device lock held
 */
पूर्णांक ccw_device_resume(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch;

	अगर (!cdev || !cdev->dev.parent)
		वापस -ENODEV;
	sch = to_subchannel(cdev->dev.parent);
	अगर (!sch->schib.pmcw.ena)
		वापस -EINVAL;
	अगर (cdev->निजी->state == DEV_STATE_NOT_OPER)
		वापस -ENODEV;
	अगर (cdev->निजी->state != DEV_STATE_ONLINE ||
	    !(sch->schib.scsw.cmd.actl & SCSW_ACTL_SUSPENDED))
		वापस -EINVAL;
	वापस cio_resume(sch);
पूर्ण

/**
 * ccw_device_get_ciw() - Search क्रम CIW command in extended sense data.
 * @cdev: ccw device to inspect
 * @ct: command type to look क्रम
 *
 * During SenseID, command inक्रमmation words (CIWs) describing special
 * commands available to the device may have been stored in the extended
 * sense data. This function searches क्रम CIWs of a specअगरied command
 * type in the extended sense data.
 * Returns:
 *  %शून्य अगर no extended sense data has been stored or अगर no CIW of the
 *  specअगरied command type could be found,
 *  अन्यथा a poपूर्णांकer to the CIW of the specअगरied command type.
 */
काष्ठा ciw *ccw_device_get_ciw(काष्ठा ccw_device *cdev, __u32 ct)
अणु
	पूर्णांक ciw_cnt;

	अगर (cdev->निजी->flags.esid == 0)
		वापस शून्य;
	क्रम (ciw_cnt = 0; ciw_cnt < MAX_CIWS; ciw_cnt++)
		अगर (cdev->निजी->dma_area->senseid.ciw[ciw_cnt].ct == ct)
			वापस cdev->निजी->dma_area->senseid.ciw + ciw_cnt;
	वापस शून्य;
पूर्ण

/**
 * ccw_device_get_path_mask() - get currently available paths
 * @cdev: ccw device to be queried
 * Returns:
 *  %0 अगर no subchannel क्रम the device is available,
 *  अन्यथा the mask of currently available paths क्रम the ccw device's subchannel.
 */
__u8 ccw_device_get_path_mask(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch;

	अगर (!cdev->dev.parent)
		वापस 0;

	sch = to_subchannel(cdev->dev.parent);
	वापस sch->lpm;
पूर्ण

/**
 * ccw_device_get_chp_desc() - वापस newly allocated channel-path descriptor
 * @cdev: device to obtain the descriptor क्रम
 * @chp_idx: index of the channel path
 *
 * On success वापस a newly allocated copy of the channel-path description
 * data associated with the given channel path. Return %शून्य on error.
 */
काष्ठा channel_path_desc_fmt0 *ccw_device_get_chp_desc(काष्ठा ccw_device *cdev,
						       पूर्णांक chp_idx)
अणु
	काष्ठा subchannel *sch;
	काष्ठा chp_id chpid;

	sch = to_subchannel(cdev->dev.parent);
	chp_id_init(&chpid);
	chpid.id = sch->schib.pmcw.chpid[chp_idx];
	वापस chp_get_chp_desc(chpid);
पूर्ण

/**
 * ccw_device_get_util_str() - वापस newly allocated utility strings
 * @cdev: device to obtain the utility strings क्रम
 * @chp_idx: index of the channel path
 *
 * On success वापस a newly allocated copy of the utility strings
 * associated with the given channel path. Return %शून्य on error.
 */
u8 *ccw_device_get_util_str(काष्ठा ccw_device *cdev, पूर्णांक chp_idx)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा channel_path *chp;
	काष्ठा chp_id chpid;
	u8 *util_str;

	chp_id_init(&chpid);
	chpid.id = sch->schib.pmcw.chpid[chp_idx];
	chp = chpid_to_chp(chpid);

	util_str = kदो_स्मृति(माप(chp->desc_fmt3.util_str), GFP_KERNEL);
	अगर (!util_str)
		वापस शून्य;

	mutex_lock(&chp->lock);
	स_नकल(util_str, chp->desc_fmt3.util_str, माप(chp->desc_fmt3.util_str));
	mutex_unlock(&chp->lock);

	वापस util_str;
पूर्ण

/**
 * ccw_device_get_id() - obtain a ccw device id
 * @cdev: device to obtain the id क्रम
 * @dev_id: where to fill in the values
 */
व्योम ccw_device_get_id(काष्ठा ccw_device *cdev, काष्ठा ccw_dev_id *dev_id)
अणु
	*dev_id = cdev->निजी->dev_id;
पूर्ण
EXPORT_SYMBOL(ccw_device_get_id);

/**
 * ccw_device_पंचांग_start_समयout_key() - perक्रमm start function
 * @cdev: ccw device on which to perक्रमm the start function
 * @tcw: transport-command word to be started
 * @पूर्णांकparm: user defined parameter to be passed to the पूर्णांकerrupt handler
 * @lpm: mask of paths to use
 * @key: storage key to use क्रम storage access
 * @expires: समय span in jअगरfies after which to पात request
 *
 * Start the tcw on the given ccw device. Return zero on success, non-zero
 * otherwise.
 */
पूर्णांक ccw_device_पंचांग_start_समयout_key(काष्ठा ccw_device *cdev, काष्ठा tcw *tcw,
				    अचिन्हित दीर्घ पूर्णांकparm, u8 lpm, u8 key,
				    पूर्णांक expires)
अणु
	काष्ठा subchannel *sch;
	पूर्णांक rc;

	sch = to_subchannel(cdev->dev.parent);
	अगर (!sch->schib.pmcw.ena)
		वापस -EINVAL;
	अगर (cdev->निजी->state == DEV_STATE_VERIFY) अणु
		/* Remember to fake irb when finished. */
		अगर (!cdev->निजी->flags.fake_irb) अणु
			cdev->निजी->flags.fake_irb = FAKE_TM_IRB;
			cdev->निजी->पूर्णांकparm = पूर्णांकparm;
			वापस 0;
		पूर्ण अन्यथा
			/* There's alपढ़ोy a fake I/O around. */
			वापस -EBUSY;
	पूर्ण
	अगर (cdev->निजी->state != DEV_STATE_ONLINE)
		वापस -EIO;
	/* Adjust requested path mask to exclude unusable paths. */
	अगर (lpm) अणु
		lpm &= sch->lpm;
		अगर (lpm == 0)
			वापस -EACCES;
	पूर्ण
	rc = cio_पंचांग_start_key(sch, tcw, lpm, key);
	अगर (rc == 0) अणु
		cdev->निजी->पूर्णांकparm = पूर्णांकparm;
		अगर (expires)
			ccw_device_set_समयout(cdev, expires);
	पूर्ण
	वापस rc;
पूर्ण
EXPORT_SYMBOL(ccw_device_पंचांग_start_समयout_key);

/**
 * ccw_device_पंचांग_start_key() - perक्रमm start function
 * @cdev: ccw device on which to perक्रमm the start function
 * @tcw: transport-command word to be started
 * @पूर्णांकparm: user defined parameter to be passed to the पूर्णांकerrupt handler
 * @lpm: mask of paths to use
 * @key: storage key to use क्रम storage access
 *
 * Start the tcw on the given ccw device. Return zero on success, non-zero
 * otherwise.
 */
पूर्णांक ccw_device_पंचांग_start_key(काष्ठा ccw_device *cdev, काष्ठा tcw *tcw,
			    अचिन्हित दीर्घ पूर्णांकparm, u8 lpm, u8 key)
अणु
	वापस ccw_device_पंचांग_start_समयout_key(cdev, tcw, पूर्णांकparm, lpm, key, 0);
पूर्ण
EXPORT_SYMBOL(ccw_device_पंचांग_start_key);

/**
 * ccw_device_पंचांग_start() - perक्रमm start function
 * @cdev: ccw device on which to perक्रमm the start function
 * @tcw: transport-command word to be started
 * @पूर्णांकparm: user defined parameter to be passed to the पूर्णांकerrupt handler
 * @lpm: mask of paths to use
 *
 * Start the tcw on the given ccw device. Return zero on success, non-zero
 * otherwise.
 */
पूर्णांक ccw_device_पंचांग_start(काष्ठा ccw_device *cdev, काष्ठा tcw *tcw,
			अचिन्हित दीर्घ पूर्णांकparm, u8 lpm)
अणु
	वापस ccw_device_पंचांग_start_key(cdev, tcw, पूर्णांकparm, lpm,
				       PAGE_DEFAULT_KEY);
पूर्ण
EXPORT_SYMBOL(ccw_device_पंचांग_start);

/**
 * ccw_device_पंचांग_start_समयout() - perक्रमm start function
 * @cdev: ccw device on which to perक्रमm the start function
 * @tcw: transport-command word to be started
 * @पूर्णांकparm: user defined parameter to be passed to the पूर्णांकerrupt handler
 * @lpm: mask of paths to use
 * @expires: समय span in jअगरfies after which to पात request
 *
 * Start the tcw on the given ccw device. Return zero on success, non-zero
 * otherwise.
 */
पूर्णांक ccw_device_पंचांग_start_समयout(काष्ठा ccw_device *cdev, काष्ठा tcw *tcw,
			       अचिन्हित दीर्घ पूर्णांकparm, u8 lpm, पूर्णांक expires)
अणु
	वापस ccw_device_पंचांग_start_समयout_key(cdev, tcw, पूर्णांकparm, lpm,
					       PAGE_DEFAULT_KEY, expires);
पूर्ण
EXPORT_SYMBOL(ccw_device_पंचांग_start_समयout);

/**
 * ccw_device_get_mdc() - accumulate max data count
 * @cdev: ccw device क्रम which the max data count is accumulated
 * @mask: mask of paths to use
 *
 * Return the number of 64K-bytes blocks all paths at least support
 * क्रम a transport command. Return value 0 indicates failure.
 */
पूर्णांक ccw_device_get_mdc(काष्ठा ccw_device *cdev, u8 mask)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	काष्ठा channel_path *chp;
	काष्ठा chp_id chpid;
	पूर्णांक mdc = 0, i;

	/* Adjust requested path mask to excluded varied off paths. */
	अगर (mask)
		mask &= sch->lpm;
	अन्यथा
		mask = sch->lpm;

	chp_id_init(&chpid);
	क्रम (i = 0; i < 8; i++) अणु
		अगर (!(mask & (0x80 >> i)))
			जारी;
		chpid.id = sch->schib.pmcw.chpid[i];
		chp = chpid_to_chp(chpid);
		अगर (!chp)
			जारी;

		mutex_lock(&chp->lock);
		अगर (!chp->desc_fmt1.f) अणु
			mutex_unlock(&chp->lock);
			वापस 0;
		पूर्ण
		अगर (!chp->desc_fmt1.r)
			mdc = 1;
		mdc = mdc ? min_t(पूर्णांक, mdc, chp->desc_fmt1.mdc) :
			    chp->desc_fmt1.mdc;
		mutex_unlock(&chp->lock);
	पूर्ण

	वापस mdc;
पूर्ण
EXPORT_SYMBOL(ccw_device_get_mdc);

/**
 * ccw_device_पंचांग_पूर्णांकrg() - perक्रमm पूर्णांकerrogate function
 * @cdev: ccw device on which to perक्रमm the पूर्णांकerrogate function
 *
 * Perक्रमm an पूर्णांकerrogate function on the given ccw device. Return zero on
 * success, non-zero otherwise.
 */
पूर्णांक ccw_device_पंचांग_पूर्णांकrg(काष्ठा ccw_device *cdev)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);

	अगर (!sch->schib.pmcw.ena)
		वापस -EINVAL;
	अगर (cdev->निजी->state != DEV_STATE_ONLINE)
		वापस -EIO;
	अगर (!scsw_is_पंचांग(&sch->schib.scsw) ||
	    !(scsw_actl(&sch->schib.scsw) & SCSW_ACTL_START_PEND))
		वापस -EINVAL;
	वापस cio_पंचांग_पूर्णांकrg(sch);
पूर्ण
EXPORT_SYMBOL(ccw_device_पंचांग_पूर्णांकrg);

/**
 * ccw_device_get_schid() - obtain a subchannel id
 * @cdev: device to obtain the id क्रम
 * @schid: where to fill in the values
 */
व्योम ccw_device_get_schid(काष्ठा ccw_device *cdev, काष्ठा subchannel_id *schid)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);

	*schid = sch->schid;
पूर्ण
EXPORT_SYMBOL_GPL(ccw_device_get_schid);

/**
 * ccw_device_pnso() - Perक्रमm Network-Subchannel Operation
 * @cdev:		device on which PNSO is perक्रमmed
 * @pnso_area:		request and response block क्रम the operation
 * @oc:			Operation Code
 * @resume_token:	resume token क्रम multiblock response
 * @cnc:		Boolean change-notअगरication control
 *
 * pnso_area must be allocated by the caller with get_zeroed_page(GFP_KERNEL)
 *
 * Returns 0 on success.
 */
पूर्णांक ccw_device_pnso(काष्ठा ccw_device *cdev,
		    काष्ठा chsc_pnso_area *pnso_area, u8 oc,
		    काष्ठा chsc_pnso_resume_token resume_token, पूर्णांक cnc)
अणु
	काष्ठा subchannel_id schid;

	ccw_device_get_schid(cdev, &schid);
	वापस chsc_pnso(schid, pnso_area, oc, resume_token, cnc);
पूर्ण
EXPORT_SYMBOL_GPL(ccw_device_pnso);

/**
 * ccw_device_get_cssid() - obtain Channel Subप्रणाली ID
 * @cdev: device to obtain the CSSID क्रम
 * @cssid: The resulting Channel Subप्रणाली ID
 */
पूर्णांक ccw_device_get_cssid(काष्ठा ccw_device *cdev, u8 *cssid)
अणु
	काष्ठा device *sch_dev = cdev->dev.parent;
	काष्ठा channel_subप्रणाली *css = to_css(sch_dev->parent);

	अगर (css->id_valid)
		*cssid = css->cssid;
	वापस css->id_valid ? 0 : -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(ccw_device_get_cssid);

/**
 * ccw_device_get_iid() - obtain MIF-image ID
 * @cdev: device to obtain the MIF-image ID क्रम
 * @iid: The resulting MIF-image ID
 */
पूर्णांक ccw_device_get_iid(काष्ठा ccw_device *cdev, u8 *iid)
अणु
	काष्ठा device *sch_dev = cdev->dev.parent;
	काष्ठा channel_subप्रणाली *css = to_css(sch_dev->parent);

	अगर (css->id_valid)
		*iid = css->iid;
	वापस css->id_valid ? 0 : -ENODEV;
पूर्ण
EXPORT_SYMBOL_GPL(ccw_device_get_iid);

/**
 * ccw_device_get_chpid() - obtain Channel Path ID
 * @cdev: device to obtain the Channel Path ID क्रम
 * @chp_idx: Index of the channel path
 * @chpid: The resulting Channel Path ID
 */
पूर्णांक ccw_device_get_chpid(काष्ठा ccw_device *cdev, पूर्णांक chp_idx, u8 *chpid)
अणु
	काष्ठा subchannel *sch = to_subchannel(cdev->dev.parent);
	पूर्णांक mask;

	अगर ((chp_idx < 0) || (chp_idx > 7))
		वापस -EINVAL;
	mask = 0x80 >> chp_idx;
	अगर (!(sch->schib.pmcw.pim & mask))
		वापस -ENODEV;

	*chpid = sch->schib.pmcw.chpid[chp_idx];
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ccw_device_get_chpid);

/**
 * ccw_device_get_chid() - obtain Channel ID associated with specअगरied CHPID
 * @cdev: device to obtain the Channel ID क्रम
 * @chp_idx: Index of the channel path
 * @chid: The resulting Channel ID
 */
पूर्णांक ccw_device_get_chid(काष्ठा ccw_device *cdev, पूर्णांक chp_idx, u16 *chid)
अणु
	काष्ठा chp_id cssid_chpid;
	काष्ठा channel_path *chp;
	पूर्णांक rc;

	chp_id_init(&cssid_chpid);
	rc = ccw_device_get_chpid(cdev, chp_idx, &cssid_chpid.id);
	अगर (rc)
		वापस rc;
	chp = chpid_to_chp(cssid_chpid);
	अगर (!chp)
		वापस -ENODEV;

	mutex_lock(&chp->lock);
	अगर (chp->desc_fmt1.flags & 0x10)
		*chid = chp->desc_fmt1.chid;
	अन्यथा
		rc = -ENODEV;
	mutex_unlock(&chp->lock);

	वापस rc;
पूर्ण
EXPORT_SYMBOL_GPL(ccw_device_get_chid);

/*
 * Allocate zeroed dma coherent 31 bit addressable memory using
 * the subchannels dma pool. Maximal size of allocation supported
 * is PAGE_SIZE.
 */
व्योम *ccw_device_dma_zalloc(काष्ठा ccw_device *cdev, माप_प्रकार size)
अणु
	वापस cio_gp_dma_zalloc(cdev->निजी->dma_pool, &cdev->dev, size);
पूर्ण
EXPORT_SYMBOL(ccw_device_dma_zalloc);

व्योम ccw_device_dma_मुक्त(काष्ठा ccw_device *cdev, व्योम *cpu_addr, माप_प्रकार size)
अणु
	cio_gp_dma_मुक्त(cdev->निजी->dma_pool, cpu_addr, size);
पूर्ण
EXPORT_SYMBOL(ccw_device_dma_मुक्त);

EXPORT_SYMBOL(ccw_device_set_options_mask);
EXPORT_SYMBOL(ccw_device_set_options);
EXPORT_SYMBOL(ccw_device_clear_options);
EXPORT_SYMBOL(ccw_device_clear);
EXPORT_SYMBOL(ccw_device_halt);
EXPORT_SYMBOL(ccw_device_resume);
EXPORT_SYMBOL(ccw_device_start_समयout);
EXPORT_SYMBOL(ccw_device_start);
EXPORT_SYMBOL(ccw_device_start_समयout_key);
EXPORT_SYMBOL(ccw_device_start_key);
EXPORT_SYMBOL(ccw_device_get_ciw);
EXPORT_SYMBOL(ccw_device_get_path_mask);
EXPORT_SYMBOL_GPL(ccw_device_get_chp_desc);
EXPORT_SYMBOL_GPL(ccw_device_get_util_str);
