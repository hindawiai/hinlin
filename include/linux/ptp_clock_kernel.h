<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * PTP 1588 घड़ी support
 *
 * Copyright (C) 2010 OMICRON electronics GmbH
 */

#अगर_अघोषित _PTP_CLOCK_KERNEL_H_
#घोषणा _PTP_CLOCK_KERNEL_H_

#समावेश <linux/device.h>
#समावेश <linux/pps_kernel.h>
#समावेश <linux/ptp_घड़ी.h>

/**
 * काष्ठा ptp_घड़ी_request - request PTP घड़ी event
 *
 * @type:   The type of the request.
 *	    EXTTS:  Configure बाह्यal trigger बारtamping
 *	    PEROUT: Configure periodic output संकेत (e.g. PPS)
 *	    PPS:    trigger पूर्णांकernal PPS event क्रम input
 *	            पूर्णांकo kernel PPS subप्रणाली
 * @extts:  describes configuration क्रम बाह्यal trigger बारtamping.
 *          This is only valid when event == PTP_CLK_REQ_EXTTS.
 * @perout: describes configuration क्रम periodic output.
 *	    This is only valid when event == PTP_CLK_REQ_PEROUT.
 */

काष्ठा ptp_घड़ी_request अणु
	क्रमागत अणु
		PTP_CLK_REQ_EXTTS,
		PTP_CLK_REQ_PEROUT,
		PTP_CLK_REQ_PPS,
	पूर्ण type;
	जोड़ अणु
		काष्ठा ptp_extts_request extts;
		काष्ठा ptp_perout_request perout;
	पूर्ण;
पूर्ण;

काष्ठा प्रणाली_device_crosststamp;

/**
 * काष्ठा ptp_प्रणाली_बारtamp - प्रणाली समय corresponding to a PHC बारtamp
 */
काष्ठा ptp_प्रणाली_बारtamp अणु
	काष्ठा बारpec64 pre_ts;
	काष्ठा बारpec64 post_ts;
पूर्ण;

/**
 * काष्ठा ptp_घड़ी_info - describes a PTP hardware घड़ी
 *
 * @owner:     The घड़ी driver should set to THIS_MODULE.
 * @name:      A लघु "friendly name" to identअगरy the घड़ी and to
 *             help distinguish PHY based devices from MAC based ones.
 *             The string is not meant to be a unique id.
 * @max_adj:   The maximum possible frequency adjusपंचांगent, in parts per billon.
 * @n_alarm:   The number of programmable alarms.
 * @n_ext_ts:  The number of बाह्यal समय stamp channels.
 * @n_per_out: The number of programmable periodic संकेतs.
 * @n_pins:    The number of programmable pins.
 * @pps:       Indicates whether the घड़ी supports a PPS callback.
 * @pin_config: Array of length 'n_pins'. If the number of
 *              programmable pins is nonzero, then drivers must
 *              allocate and initialize this array.
 *
 * घड़ी operations
 *
 * @adjfine:  Adjusts the frequency of the hardware घड़ी.
 *            parameter scaled_ppm: Desired frequency offset from
 *            nominal frequency in parts per million, but with a
 *            16 bit binary fractional field.
 *
 * @adjfreq:  Adjusts the frequency of the hardware घड़ी.
 *            This method is deprecated.  New drivers should implement
 *            the @adjfine method instead.
 *            parameter delta: Desired frequency offset from nominal frequency
 *            in parts per billion
 *
 * @adjphase:  Adjusts the phase offset of the hardware घड़ी.
 *             parameter delta: Desired change in nanoseconds.
 *
 * @adjसमय:  Shअगरts the समय of the hardware घड़ी.
 *            parameter delta: Desired change in nanoseconds.
 *
 * @समय_लो64:  Reads the current समय from the hardware घड़ी.
 *              This method is deprecated.  New drivers should implement
 *              the @समय_लोx64 method instead.
 *              parameter ts: Holds the result.
 *
 * @समय_लोx64:  Reads the current समय from the hardware घड़ी and optionally
 *               also the प्रणाली घड़ी.
 *               parameter ts: Holds the PHC बारtamp.
 *               parameter sts: If not शून्य, it holds a pair of बारtamps from
 *               the प्रणाली घड़ी. The first पढ़ोing is made right beक्रमe
 *               पढ़ोing the lowest bits of the PHC बारtamp and the second
 *               पढ़ोing immediately follows that.
 *
 * @अ_लोrosststamp:  Reads the current समय from the hardware घड़ी and
 *                   प्रणाली घड़ी simultaneously.
 *                   parameter cts: Contains बारtamp (device,प्रणाली) pair,
 *                   where प्रणाली समय is realसमय and monotonic.
 *
 * @समय_रखो64:  Set the current समय on the hardware घड़ी.
 *              parameter ts: Time value to set.
 *
 * @enable:   Request driver to enable or disable an ancillary feature.
 *            parameter request: Desired resource to enable or disable.
 *            parameter on: Caller passes one to enable or zero to disable.
 *
 * @verअगरy:   Confirm that a pin can perक्रमm a given function. The PTP
 *            Hardware Clock subप्रणाली मुख्यtains the 'pin_config'
 *            array on behalf of the drivers, but the PHC subप्रणाली
 *            assumes that every pin can perक्रमm every function. This
 *            hook gives drivers a way of telling the core about
 *            limitations on specअगरic pins. This function must वापस
 *            zero अगर the function can be asचिन्हित to this pin, and
 *            nonzero otherwise.
 *            parameter pin: index of the pin in question.
 *            parameter func: the desired function to use.
 *            parameter chan: the function channel index to use.
 *
 * @करो_aux_work:  Request driver to perक्रमm auxiliary (periodic) operations
 *                Driver should वापस delay of the next auxiliary work
 *                scheduling समय (>=0) or negative value in हाल further
 *                scheduling is not required.
 *
 * Drivers should embed their ptp_घड़ी_info within a निजी
 * काष्ठाure, obtaining a reference to it using container_of().
 *
 * The callbacks must all वापस zero on success, non-zero otherwise.
 */

काष्ठा ptp_घड़ी_info अणु
	काष्ठा module *owner;
	अक्षर name[16];
	s32 max_adj;
	पूर्णांक n_alarm;
	पूर्णांक n_ext_ts;
	पूर्णांक n_per_out;
	पूर्णांक n_pins;
	पूर्णांक pps;
	काष्ठा ptp_pin_desc *pin_config;
	पूर्णांक (*adjfine)(काष्ठा ptp_घड़ी_info *ptp, दीर्घ scaled_ppm);
	पूर्णांक (*adjfreq)(काष्ठा ptp_घड़ी_info *ptp, s32 delta);
	पूर्णांक (*adjphase)(काष्ठा ptp_घड़ी_info *ptp, s32 phase);
	पूर्णांक (*adjसमय)(काष्ठा ptp_घड़ी_info *ptp, s64 delta);
	पूर्णांक (*समय_लो64)(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts);
	पूर्णांक (*समय_लोx64)(काष्ठा ptp_घड़ी_info *ptp, काष्ठा बारpec64 *ts,
			  काष्ठा ptp_प्रणाली_बारtamp *sts);
	पूर्णांक (*अ_लोrosststamp)(काष्ठा ptp_घड़ी_info *ptp,
			      काष्ठा प्रणाली_device_crosststamp *cts);
	पूर्णांक (*समय_रखो64)(काष्ठा ptp_घड़ी_info *p, स्थिर काष्ठा बारpec64 *ts);
	पूर्णांक (*enable)(काष्ठा ptp_घड़ी_info *ptp,
		      काष्ठा ptp_घड़ी_request *request, पूर्णांक on);
	पूर्णांक (*verअगरy)(काष्ठा ptp_घड़ी_info *ptp, अचिन्हित पूर्णांक pin,
		      क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan);
	दीर्घ (*करो_aux_work)(काष्ठा ptp_घड़ी_info *ptp);
पूर्ण;

काष्ठा ptp_घड़ी;

क्रमागत ptp_घड़ी_events अणु
	PTP_CLOCK_ALARM,
	PTP_CLOCK_EXTTS,
	PTP_CLOCK_PPS,
	PTP_CLOCK_PPSUSR,
पूर्ण;

/**
 * काष्ठा ptp_घड़ी_event - decribes a PTP hardware घड़ी event
 *
 * @type:  One of the ptp_घड़ी_events क्रमागतeration values.
 * @index: Identअगरies the source of the event.
 * @बारtamp: When the event occurred (%PTP_CLOCK_EXTTS only).
 * @pps_बार: When the event occurred (%PTP_CLOCK_PPSUSR only).
 */

काष्ठा ptp_घड़ी_event अणु
	पूर्णांक type;
	पूर्णांक index;
	जोड़ अणु
		u64 बारtamp;
		काष्ठा pps_event_समय pps_बार;
	पूर्ण;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_PTP_1588_CLOCK)

/**
 * ptp_घड़ी_रेजिस्टर() - रेजिस्टर a PTP hardware घड़ी driver
 *
 * @info:   Structure describing the new घड़ी.
 * @parent: Poपूर्णांकer to the parent device of the new घड़ी.
 *
 * Returns a valid poपूर्णांकer on success or PTR_ERR on failure.  If PHC
 * support is missing at the configuration level, this function
 * वापसs शून्य, and drivers are expected to gracefully handle that
 * हाल separately.
 */

बाह्य काष्ठा ptp_घड़ी *ptp_घड़ी_रेजिस्टर(काष्ठा ptp_घड़ी_info *info,
					    काष्ठा device *parent);

/**
 * ptp_घड़ी_unरेजिस्टर() - unरेजिस्टर a PTP hardware घड़ी driver
 *
 * @ptp:  The घड़ी to हटाओ from service.
 */

बाह्य पूर्णांक ptp_घड़ी_unरेजिस्टर(काष्ठा ptp_घड़ी *ptp);

/**
 * ptp_घड़ी_event() - notअगरy the PTP layer about an event
 *
 * @ptp:    The घड़ी obtained from ptp_घड़ी_रेजिस्टर().
 * @event:  Message काष्ठाure describing the event.
 */

बाह्य व्योम ptp_घड़ी_event(काष्ठा ptp_घड़ी *ptp,
			    काष्ठा ptp_घड़ी_event *event);

/**
 * ptp_घड़ी_index() - obtain the device index of a PTP घड़ी
 *
 * @ptp:    The घड़ी obtained from ptp_घड़ी_रेजिस्टर().
 */

बाह्य पूर्णांक ptp_घड़ी_index(काष्ठा ptp_घड़ी *ptp);

/**
 * scaled_ppm_to_ppb() - convert scaled ppm to ppb
 *
 * @ppm:    Parts per million, but with a 16 bit binary fractional field
 */

बाह्य दीर्घ scaled_ppm_to_ppb(दीर्घ ppm);

/**
 * ptp_find_pin() - obtain the pin index of a given auxiliary function
 *
 * The caller must hold ptp_घड़ी::pincfg_mux.  Drivers करो not have
 * access to that mutex as ptp_घड़ी is an opaque type.  However, the
 * core code acquires the mutex beक्रमe invoking the driver's
 * ptp_घड़ी_info::enable() callback, and so drivers may call this
 * function from that context.
 *
 * @ptp:    The घड़ी obtained from ptp_घड़ी_रेजिस्टर().
 * @func:   One of the ptp_pin_function क्रमागतerated values.
 * @chan:   The particular functional channel to find.
 * Return:  Pin index in the range of zero to ptp_घड़ी_caps.n_pins - 1,
 *          or -1 अगर the auxiliary function cannot be found.
 */

पूर्णांक ptp_find_pin(काष्ठा ptp_घड़ी *ptp,
		 क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan);

/**
 * ptp_find_pin_unlocked() - wrapper क्रम ptp_find_pin()
 *
 * This function acquires the ptp_घड़ी::pincfg_mux mutex beक्रमe
 * invoking ptp_find_pin().  Instead of using this function, drivers
 * should most likely call ptp_find_pin() directly from their
 * ptp_घड़ी_info::enable() method.
 *
 */

पूर्णांक ptp_find_pin_unlocked(काष्ठा ptp_घड़ी *ptp,
			  क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan);

/**
 * ptp_schedule_worker() - schedule ptp auxiliary work
 *
 * @ptp:    The घड़ी obtained from ptp_घड़ी_रेजिस्टर().
 * @delay:  number of jअगरfies to रुको beक्रमe queuing
 *          See kthपढ़ो_queue_delayed_work() क्रम more info.
 */

पूर्णांक ptp_schedule_worker(काष्ठा ptp_घड़ी *ptp, अचिन्हित दीर्घ delay);

/**
 * ptp_cancel_worker_sync() - cancel ptp auxiliary घड़ी
 *
 * @ptp:     The घड़ी obtained from ptp_घड़ी_रेजिस्टर().
 */
व्योम ptp_cancel_worker_sync(काष्ठा ptp_घड़ी *ptp);

#अन्यथा
अटल अंतरभूत काष्ठा ptp_घड़ी *ptp_घड़ी_रेजिस्टर(काष्ठा ptp_घड़ी_info *info,
						   काष्ठा device *parent)
अणु वापस शून्य; पूर्ण
अटल अंतरभूत पूर्णांक ptp_घड़ी_unरेजिस्टर(काष्ठा ptp_घड़ी *ptp)
अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम ptp_घड़ी_event(काष्ठा ptp_घड़ी *ptp,
				   काष्ठा ptp_घड़ी_event *event)
अणु पूर्ण
अटल अंतरभूत पूर्णांक ptp_घड़ी_index(काष्ठा ptp_घड़ी *ptp)
अणु वापस -1; पूर्ण
अटल अंतरभूत पूर्णांक ptp_find_pin(काष्ठा ptp_घड़ी *ptp,
			       क्रमागत ptp_pin_function func, अचिन्हित पूर्णांक chan)
अणु वापस -1; पूर्ण
अटल अंतरभूत पूर्णांक ptp_schedule_worker(काष्ठा ptp_घड़ी *ptp,
				      अचिन्हित दीर्घ delay)
अणु वापस -EOPNOTSUPP; पूर्ण
अटल अंतरभूत व्योम ptp_cancel_worker_sync(काष्ठा ptp_घड़ी *ptp)
अणु पूर्ण

#पूर्ण_अगर

अटल अंतरभूत व्योम ptp_पढ़ो_प्रणाली_prets(काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	अगर (sts)
		kसमय_get_real_ts64(&sts->pre_ts);
पूर्ण

अटल अंतरभूत व्योम ptp_पढ़ो_प्रणाली_postts(काष्ठा ptp_प्रणाली_बारtamp *sts)
अणु
	अगर (sts)
		kसमय_get_real_ts64(&sts->post_ts);
पूर्ण

#पूर्ण_अगर
