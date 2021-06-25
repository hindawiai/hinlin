<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * dvb_frontend.c: DVB frontend tuning पूर्णांकerface/thपढ़ो
 *
 * Copyright (C) 1999-2001 Ralph  Metzler
 *			   Marcus Metzler
 *			   Holger Waechtler
 *				      क्रम convergence पूर्णांकegrated media GmbH
 *
 * Copyright (C) 2004 Andrew de Quincey (tuning thपढ़ो cleanup)
 */

/* Enables DVBv3 compatibility bits at the headers */
#घोषणा __DVB_CORE__

#घोषणा pr_fmt(fmt) "dvb_frontend: " fmt

#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/रुको.h>
#समावेश <linux/slab.h>
#समावेश <linux/poll.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/module.h>
#समावेश <linux/list.h>
#समावेश <linux/मुक्तzer.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/kसमय.स>
#समावेश <linux/compat.h>
#समावेश <यंत्र/processor.h>

#समावेश <media/dvb_frontend.h>
#समावेश <media/dvbdev.h>
#समावेश <linux/dvb/version.h>

अटल पूर्णांक dvb_frontend_debug;
अटल पूर्णांक dvb_shutकरोwn_समयout;
अटल पूर्णांक dvb_क्रमce_स्वतः_inversion;
अटल पूर्णांक dvb_override_tune_delay;
अटल पूर्णांक dvb_घातerकरोwn_on_sleep = 1;
अटल पूर्णांक dvb_mfe_रुको_समय = 5;

module_param_named(frontend_debug, dvb_frontend_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(frontend_debug, "Turn on/off frontend core debugging (default:off).");
module_param(dvb_shutकरोwn_समयout, पूर्णांक, 0644);
MODULE_PARM_DESC(dvb_shutकरोwn_समयout, "wait <shutdown_timeout> seconds after close() before suspending hardware");
module_param(dvb_क्रमce_स्वतः_inversion, पूर्णांक, 0644);
MODULE_PARM_DESC(dvb_क्रमce_स्वतः_inversion, "0: normal (default), 1: INVERSION_AUTO forced always");
module_param(dvb_override_tune_delay, पूर्णांक, 0644);
MODULE_PARM_DESC(dvb_override_tune_delay, "0: normal (default), >0 => delay in milliseconds to wait for lock after a tune attempt");
module_param(dvb_घातerकरोwn_on_sleep, पूर्णांक, 0644);
MODULE_PARM_DESC(dvb_घातerकरोwn_on_sleep, "0: do not power down, 1: turn LNB voltage off on sleep (default)");
module_param(dvb_mfe_रुको_समय, पूर्णांक, 0644);
MODULE_PARM_DESC(dvb_mfe_रुको_समय, "Wait up to <mfe_wait_time> seconds on open() for multi-frontend to become available (default:5 seconds)");

#घोषणा dprपूर्णांकk(fmt, arg...) \
	prपूर्णांकk(KERN_DEBUG pr_fmt("%s: " fmt), __func__, ##arg)

#घोषणा FESTATE_IDLE 1
#घोषणा FESTATE_RETUNE 2
#घोषणा FESTATE_TUNING_FAST 4
#घोषणा FESTATE_TUNING_SLOW 8
#घोषणा FESTATE_TUNED 16
#घोषणा FESTATE_ZIGZAG_FAST 32
#घोषणा FESTATE_ZIGZAG_SLOW 64
#घोषणा FESTATE_DISEQC 128
#घोषणा FESTATE_ERROR 256
#घोषणा FESTATE_WAITFORLOCK (FESTATE_TUNING_FAST | FESTATE_TUNING_SLOW | FESTATE_ZIGZAG_FAST | FESTATE_ZIGZAG_SLOW | FESTATE_DISEQC)
#घोषणा FESTATE_SEARCHING_FAST (FESTATE_TUNING_FAST | FESTATE_ZIGZAG_FAST)
#घोषणा FESTATE_SEARCHING_SLOW (FESTATE_TUNING_SLOW | FESTATE_ZIGZAG_SLOW)
#घोषणा FESTATE_LOSTLOCK (FESTATE_ZIGZAG_FAST | FESTATE_ZIGZAG_SLOW)

/*
 * FESTATE_IDLE. No tuning parameters have been supplied and the loop is idling.
 * FESTATE_RETUNE. Parameters have been supplied, but we have not yet perक्रमmed the first tune.
 * FESTATE_TUNING_FAST. Tuning parameters have been supplied and fast zigzag scan is in progress.
 * FESTATE_TUNING_SLOW. Tuning parameters have been supplied. Fast zigzag failed, so we're trying again, but slower.
 * FESTATE_TUNED. The frontend has successfully locked on.
 * FESTATE_ZIGZAG_FAST. The lock has been lost, and a fast zigzag has been initiated to try and regain it.
 * FESTATE_ZIGZAG_SLOW. The lock has been lost. Fast zigzag has been failed, so we're trying again, but slower.
 * FESTATE_DISEQC. A DISEQC command has just been issued.
 * FESTATE_WAITFORLOCK. When we're रुकोing क्रम a lock.
 * FESTATE_SEARCHING_FAST. When we're searching क्रम a संकेत using a fast zigzag scan.
 * FESTATE_SEARCHING_SLOW. When we're searching क्रम a संकेत using a slow zigzag scan.
 * FESTATE_LOSTLOCK. When the lock has been lost, and we're searching it again.
 */

अटल DEFINE_MUTEX(frontend_mutex);

काष्ठा dvb_frontend_निजी अणु
	/* thपढ़ो/frontend values */
	काष्ठा dvb_device *dvbdev;
	काष्ठा dvb_frontend_parameters parameters_out;
	काष्ठा dvb_fe_events events;
	काष्ठा semaphore sem;
	काष्ठा list_head list_head;
	रुको_queue_head_t रुको_queue;
	काष्ठा task_काष्ठा *thपढ़ो;
	अचिन्हित दीर्घ release_jअगरfies;
	अचिन्हित पूर्णांक wakeup;
	क्रमागत fe_status status;
	अचिन्हित दीर्घ tune_mode_flags;
	अचिन्हित पूर्णांक delay;
	अचिन्हित पूर्णांक reinitialise;
	पूर्णांक tone;
	पूर्णांक voltage;

	/* swzigzag values */
	अचिन्हित पूर्णांक state;
	अचिन्हित पूर्णांक bending;
	पूर्णांक lnb_drअगरt;
	अचिन्हित पूर्णांक inversion;
	अचिन्हित पूर्णांक स्वतः_step;
	अचिन्हित पूर्णांक स्वतः_sub_step;
	अचिन्हित पूर्णांक started_स्वतः_step;
	अचिन्हित पूर्णांक min_delay;
	अचिन्हित पूर्णांक max_drअगरt;
	अचिन्हित पूर्णांक step_size;
	पूर्णांक quality;
	अचिन्हित पूर्णांक check_wrapped;
	क्रमागत dvbfe_search algo_status;

#अगर defined(CONFIG_MEDIA_CONTROLLER_DVB)
	काष्ठा media_pipeline pipe;
#पूर्ण_अगर
पूर्ण;

अटल व्योम dvb_frontend_invoke_release(काष्ठा dvb_frontend *fe,
					व्योम (*release)(काष्ठा dvb_frontend *fe));

अटल व्योम __dvb_frontend_मुक्त(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;

	अगर (fepriv)
		dvb_मुक्त_device(fepriv->dvbdev);

	dvb_frontend_invoke_release(fe, fe->ops.release);

	kमुक्त(fepriv);
पूर्ण

अटल व्योम dvb_frontend_मुक्त(काष्ठा kref *ref)
अणु
	काष्ठा dvb_frontend *fe =
		container_of(ref, काष्ठा dvb_frontend, refcount);

	__dvb_frontend_मुक्त(fe);
पूर्ण

अटल व्योम dvb_frontend_put(काष्ठा dvb_frontend *fe)
अणु
	/* call detach beक्रमe dropping the reference count */
	अगर (fe->ops.detach)
		fe->ops.detach(fe);
	/*
	 * Check अगर the frontend was रेजिस्टरed, as otherwise
	 * kref was not initialized yet.
	 */
	अगर (fe->frontend_priv)
		kref_put(&fe->refcount, dvb_frontend_मुक्त);
	अन्यथा
		__dvb_frontend_मुक्त(fe);
पूर्ण

अटल व्योम dvb_frontend_get(काष्ठा dvb_frontend *fe)
अणु
	kref_get(&fe->refcount);
पूर्ण

अटल व्योम dvb_frontend_wakeup(काष्ठा dvb_frontend *fe);
अटल पूर्णांक dtv_get_frontend(काष्ठा dvb_frontend *fe,
			    काष्ठा dtv_frontend_properties *c,
			    काष्ठा dvb_frontend_parameters *p_out);
अटल पूर्णांक
dtv_property_legacy_params_sync(काष्ठा dvb_frontend *fe,
				स्थिर काष्ठा dtv_frontend_properties *c,
				काष्ठा dvb_frontend_parameters *p);

अटल bool has_get_frontend(काष्ठा dvb_frontend *fe)
अणु
	वापस fe->ops.get_frontend;
पूर्ण

/*
 * Due to DVBv3 API calls, a delivery प्रणाली should be mapped पूर्णांकo one of
 * the 4 DVBv3 delivery प्रणालीs (FE_QPSK, FE_QAM, FE_OFDM or FE_ATSC),
 * otherwise, a DVBv3 call will fail.
 */
क्रमागत dvbv3_emulation_type अणु
	DVBV3_UNKNOWN,
	DVBV3_QPSK,
	DVBV3_QAM,
	DVBV3_OFDM,
	DVBV3_ATSC,
पूर्ण;

अटल क्रमागत dvbv3_emulation_type dvbv3_type(u32 delivery_प्रणाली)
अणु
	चयन (delivery_प्रणाली) अणु
	हाल SYS_DVBC_ANNEX_A:
	हाल SYS_DVBC_ANNEX_C:
		वापस DVBV3_QAM;
	हाल SYS_DVBS:
	हाल SYS_DVBS2:
	हाल SYS_TURBO:
	हाल SYS_ISDBS:
	हाल SYS_DSS:
		वापस DVBV3_QPSK;
	हाल SYS_DVBT:
	हाल SYS_DVBT2:
	हाल SYS_ISDBT:
	हाल SYS_DTMB:
		वापस DVBV3_OFDM;
	हाल SYS_ATSC:
	हाल SYS_ATSCMH:
	हाल SYS_DVBC_ANNEX_B:
		वापस DVBV3_ATSC;
	हाल SYS_UNDEFINED:
	हाल SYS_ISDBC:
	हाल SYS_DVBH:
	हाल SYS_DAB:
	शेष:
		/*
		 * Doesn't know how to emulate those types and/or
		 * there's no frontend driver from this type yet
		 * with some emulation code, so, we're not sure yet how
		 * to handle them, or they're not compatible with a DVBv3 call.
		 */
		वापस DVBV3_UNKNOWN;
	पूर्ण
पूर्ण

अटल व्योम dvb_frontend_add_event(काष्ठा dvb_frontend *fe,
				   क्रमागत fe_status status)
अणु
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा dvb_fe_events *events = &fepriv->events;
	काष्ठा dvb_frontend_event *e;
	पूर्णांक wp;

	dev_dbg(fe->dvb->device, "%s:\n", __func__);

	अगर ((status & FE_HAS_LOCK) && has_get_frontend(fe))
		dtv_get_frontend(fe, c, &fepriv->parameters_out);

	mutex_lock(&events->mtx);

	wp = (events->eventw + 1) % MAX_EVENT;
	अगर (wp == events->eventr) अणु
		events->overflow = 1;
		events->eventr = (events->eventr + 1) % MAX_EVENT;
	पूर्ण

	e = &events->events[events->eventw];
	e->status = status;
	e->parameters = fepriv->parameters_out;

	events->eventw = wp;

	mutex_unlock(&events->mtx);

	wake_up_पूर्णांकerruptible(&events->रुको_queue);
पूर्ण

अटल पूर्णांक dvb_frontend_test_event(काष्ठा dvb_frontend_निजी *fepriv,
				   काष्ठा dvb_fe_events *events)
अणु
	पूर्णांक ret;

	up(&fepriv->sem);
	ret = events->eventw != events->eventr;
	करोwn(&fepriv->sem);

	वापस ret;
पूर्ण

अटल पूर्णांक dvb_frontend_get_event(काष्ठा dvb_frontend *fe,
				  काष्ठा dvb_frontend_event *event, पूर्णांक flags)
अणु
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	काष्ठा dvb_fe_events *events = &fepriv->events;

	dev_dbg(fe->dvb->device, "%s:\n", __func__);

	अगर (events->overflow) अणु
		events->overflow = 0;
		वापस -EOVERFLOW;
	पूर्ण

	अगर (events->eventw == events->eventr) अणु
		पूर्णांक ret;

		अगर (flags & O_NONBLOCK)
			वापस -EWOULDBLOCK;

		ret = रुको_event_पूर्णांकerruptible(events->रुको_queue,
					       dvb_frontend_test_event(fepriv, events));

		अगर (ret < 0)
			वापस ret;
	पूर्ण

	mutex_lock(&events->mtx);
	*event = events->events[events->eventr];
	events->eventr = (events->eventr + 1) % MAX_EVENT;
	mutex_unlock(&events->mtx);

	वापस 0;
पूर्ण

अटल व्योम dvb_frontend_clear_events(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	काष्ठा dvb_fe_events *events = &fepriv->events;

	mutex_lock(&events->mtx);
	events->eventr = events->eventw;
	mutex_unlock(&events->mtx);
पूर्ण

अटल व्योम dvb_frontend_init(काष्ठा dvb_frontend *fe)
अणु
	dev_dbg(fe->dvb->device,
		"%s: initialising adapter %i frontend %i (%s)...\n",
		__func__, fe->dvb->num, fe->id, fe->ops.info.name);

	अगर (fe->ops.init)
		fe->ops.init(fe);
	अगर (fe->ops.tuner_ops.init) अणु
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 1);
		fe->ops.tuner_ops.init(fe);
		अगर (fe->ops.i2c_gate_ctrl)
			fe->ops.i2c_gate_ctrl(fe, 0);
	पूर्ण
पूर्ण

व्योम dvb_frontend_reinitialise(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;

	fepriv->reinitialise = 1;
	dvb_frontend_wakeup(fe);
पूर्ण
EXPORT_SYMBOL(dvb_frontend_reinitialise);

अटल व्योम dvb_frontend_swzigzag_update_delay(काष्ठा dvb_frontend_निजी *fepriv, पूर्णांक locked)
अणु
	पूर्णांक q2;
	काष्ठा dvb_frontend *fe = fepriv->dvbdev->priv;

	dev_dbg(fe->dvb->device, "%s:\n", __func__);

	अगर (locked)
		(fepriv->quality) = (fepriv->quality * 220 + 36 * 256) / 256;
	अन्यथा
		(fepriv->quality) = (fepriv->quality * 220 + 0) / 256;

	q2 = fepriv->quality - 128;
	q2 *= q2;

	fepriv->delay = fepriv->min_delay + q2 * HZ / (128 * 128);
पूर्ण

/**
 * dvb_frontend_swzigzag_स्वतःtune - Perक्रमms स्वतःmatic twiddling of frontend
 *	parameters.
 *
 * @fe: The frontend concerned.
 * @check_wrapped: Checks अगर an iteration has completed.
 *		   DO NOT SET ON THE FIRST ATTEMPT.
 *
 * वापस: Number of complete iterations that have been perक्रमmed.
 */
अटल पूर्णांक dvb_frontend_swzigzag_स्वतःtune(काष्ठा dvb_frontend *fe, पूर्णांक check_wrapped)
अणु
	पूर्णांक स्वतःinversion;
	पूर्णांक पढ़ोy = 0;
	पूर्णांक fe_set_err = 0;
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache, पंचांगp;
	पूर्णांक original_inversion = c->inversion;
	u32 original_frequency = c->frequency;

	/* are we using स्वतःinversion? */
	स्वतःinversion = ((!(fe->ops.info.caps & FE_CAN_INVERSION_AUTO)) &&
			 (c->inversion == INVERSION_AUTO));

	/* setup parameters correctly */
	जबतक (!पढ़ोy) अणु
		/* calculate the lnb_drअगरt */
		fepriv->lnb_drअगरt = fepriv->स्वतः_step * fepriv->step_size;

		/* wrap the स्वतः_step अगर we've exceeded the maximum drअगरt */
		अगर (fepriv->lnb_drअगरt > fepriv->max_drअगरt) अणु
			fepriv->स्वतः_step = 0;
			fepriv->स्वतः_sub_step = 0;
			fepriv->lnb_drअगरt = 0;
		पूर्ण

		/* perक्रमm inversion and +/- zigzag */
		चयन (fepriv->स्वतः_sub_step) अणु
		हाल 0:
			/* try with the current inversion and current drअगरt setting */
			पढ़ोy = 1;
			अवरोध;

		हाल 1:
			अगर (!स्वतःinversion) अवरोध;

			fepriv->inversion = (fepriv->inversion == INVERSION_OFF) ? INVERSION_ON : INVERSION_OFF;
			पढ़ोy = 1;
			अवरोध;

		हाल 2:
			अगर (fepriv->lnb_drअगरt == 0) अवरोध;

			fepriv->lnb_drअगरt = -fepriv->lnb_drअगरt;
			पढ़ोy = 1;
			अवरोध;

		हाल 3:
			अगर (fepriv->lnb_drअगरt == 0) अवरोध;
			अगर (!स्वतःinversion) अवरोध;

			fepriv->inversion = (fepriv->inversion == INVERSION_OFF) ? INVERSION_ON : INVERSION_OFF;
			fepriv->lnb_drअगरt = -fepriv->lnb_drअगरt;
			पढ़ोy = 1;
			अवरोध;

		शेष:
			fepriv->स्वतः_step++;
			fepriv->स्वतः_sub_step = -1; /* it'll be incremented to 0 in a moment */
			अवरोध;
		पूर्ण

		अगर (!पढ़ोy) fepriv->स्वतः_sub_step++;
	पूर्ण

	/* अगर this attempt would hit where we started, indicate a complete
	 * iteration has occurred */
	अगर ((fepriv->स्वतः_step == fepriv->started_स्वतः_step) &&
	    (fepriv->स्वतः_sub_step == 0) && check_wrapped) अणु
		वापस 1;
	पूर्ण

	dev_dbg(fe->dvb->device,
		"%s: drift:%i inversion:%i auto_step:%i auto_sub_step:%i started_auto_step:%i\n",
		__func__, fepriv->lnb_drअगरt, fepriv->inversion,
		fepriv->स्वतः_step, fepriv->स्वतः_sub_step,
		fepriv->started_स्वतः_step);

	/* set the frontend itself */
	c->frequency += fepriv->lnb_drअगरt;
	अगर (स्वतःinversion)
		c->inversion = fepriv->inversion;
	पंचांगp = *c;
	अगर (fe->ops.set_frontend)
		fe_set_err = fe->ops.set_frontend(fe);
	*c = पंचांगp;
	अगर (fe_set_err < 0) अणु
		fepriv->state = FESTATE_ERROR;
		वापस fe_set_err;
	पूर्ण

	c->frequency = original_frequency;
	c->inversion = original_inversion;

	fepriv->स्वतः_sub_step++;
	वापस 0;
पूर्ण

अटल व्योम dvb_frontend_swzigzag(काष्ठा dvb_frontend *fe)
अणु
	क्रमागत fe_status s = FE_NONE;
	पूर्णांक retval = 0;
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache, पंचांगp;

	अगर (fepriv->max_drअगरt)
		dev_warn_once(fe->dvb->device,
			      "Frontend requested software zigzag, but didn't set the frequency step size\n");

	/* अगर we've got no parameters, just keep idling */
	अगर (fepriv->state & FESTATE_IDLE) अणु
		fepriv->delay = 3 * HZ;
		fepriv->quality = 0;
		वापस;
	पूर्ण

	/* in SCAN mode, we just set the frontend when asked and leave it alone */
	अगर (fepriv->tune_mode_flags & FE_TUNE_MODE_ONESHOT) अणु
		अगर (fepriv->state & FESTATE_RETUNE) अणु
			पंचांगp = *c;
			अगर (fe->ops.set_frontend)
				retval = fe->ops.set_frontend(fe);
			*c = पंचांगp;
			अगर (retval < 0)
				fepriv->state = FESTATE_ERROR;
			अन्यथा
				fepriv->state = FESTATE_TUNED;
		पूर्ण
		fepriv->delay = 3 * HZ;
		fepriv->quality = 0;
		वापस;
	पूर्ण

	/* get the frontend status */
	अगर (fepriv->state & FESTATE_RETUNE) अणु
		s = 0;
	पूर्ण अन्यथा अणु
		अगर (fe->ops.पढ़ो_status)
			fe->ops.पढ़ो_status(fe, &s);
		अगर (s != fepriv->status) अणु
			dvb_frontend_add_event(fe, s);
			fepriv->status = s;
		पूर्ण
	पूर्ण

	/* अगर we're not tuned, and we have a lock, move to the TUNED state */
	अगर ((fepriv->state & FESTATE_WAITFORLOCK) && (s & FE_HAS_LOCK)) अणु
		dvb_frontend_swzigzag_update_delay(fepriv, s & FE_HAS_LOCK);
		fepriv->state = FESTATE_TUNED;

		/* अगर we're tuned, then we have determined the correct inversion */
		अगर ((!(fe->ops.info.caps & FE_CAN_INVERSION_AUTO)) &&
		    (c->inversion == INVERSION_AUTO)) अणु
			c->inversion = fepriv->inversion;
		पूर्ण
		वापस;
	पूर्ण

	/* अगर we are tuned alपढ़ोy, check we're still locked */
	अगर (fepriv->state & FESTATE_TUNED) अणु
		dvb_frontend_swzigzag_update_delay(fepriv, s & FE_HAS_LOCK);

		/* we're tuned, and the lock is still good... */
		अगर (s & FE_HAS_LOCK) अणु
			वापस;
		पूर्ण अन्यथा अणु /* अगर we _WERE_ tuned, but now करोn't have a lock */
			fepriv->state = FESTATE_ZIGZAG_FAST;
			fepriv->started_स्वतः_step = fepriv->स्वतः_step;
			fepriv->check_wrapped = 0;
		पूर्ण
	पूर्ण

	/* करोn't actually do anything if we're in the LOSTLOCK state,
	 * the frontend is set to FE_CAN_RECOVER, and the max_drअगरt is 0 */
	अगर ((fepriv->state & FESTATE_LOSTLOCK) &&
	    (fe->ops.info.caps & FE_CAN_RECOVER) && (fepriv->max_drअगरt == 0)) अणु
		dvb_frontend_swzigzag_update_delay(fepriv, s & FE_HAS_LOCK);
		वापस;
	पूर्ण

	/* करोn't do anything if we're in the DISEQC state, since this
	 * might be someone with a motorized dish controlled by DISEQC.
	 * If its actually a re-tune, there will be a SET_FRONTEND soon enough.	*/
	अगर (fepriv->state & FESTATE_DISEQC) अणु
		dvb_frontend_swzigzag_update_delay(fepriv, s & FE_HAS_LOCK);
		वापस;
	पूर्ण

	/* अगर we're in the RETUNE state, set everything up क्रम a bअक्रम
	 * new scan, keeping the current inversion setting, as the next
	 * tune is _very_ likely to require the same */
	अगर (fepriv->state & FESTATE_RETUNE) अणु
		fepriv->lnb_drअगरt = 0;
		fepriv->स्वतः_step = 0;
		fepriv->स्वतः_sub_step = 0;
		fepriv->started_स्वतः_step = 0;
		fepriv->check_wrapped = 0;
	पूर्ण

	/* fast zigzag. */
	अगर ((fepriv->state & FESTATE_SEARCHING_FAST) || (fepriv->state & FESTATE_RETUNE)) अणु
		fepriv->delay = fepriv->min_delay;

		/* perक्रमm a tune */
		retval = dvb_frontend_swzigzag_स्वतःtune(fe,
							fepriv->check_wrapped);
		अगर (retval < 0) अणु
			वापस;
		पूर्ण अन्यथा अगर (retval) अणु
			/* OK, अगर we've run out of trials at the fast speed.
			 * Drop back to slow क्रम the _next_ attempt */
			fepriv->state = FESTATE_SEARCHING_SLOW;
			fepriv->started_स्वतः_step = fepriv->स्वतः_step;
			वापस;
		पूर्ण
		fepriv->check_wrapped = 1;

		/* अगर we've just re-tuned, enter the ZIGZAG_FAST state.
		 * This ensures we cannot वापस from an
		 * FE_SET_FRONTEND ioctl beक्रमe the first frontend tune
		 * occurs */
		अगर (fepriv->state & FESTATE_RETUNE) अणु
			fepriv->state = FESTATE_TUNING_FAST;
		पूर्ण
	पूर्ण

	/* slow zigzag */
	अगर (fepriv->state & FESTATE_SEARCHING_SLOW) अणु
		dvb_frontend_swzigzag_update_delay(fepriv, s & FE_HAS_LOCK);

		/* Note: करोn't bother checking क्रम wrapping; we stay in this
		 * state until we get a lock */
		dvb_frontend_swzigzag_स्वतःtune(fe, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक dvb_frontend_is_निकासing(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;

	अगर (fe->निकास != DVB_FE_NO_EXIT)
		वापस 1;

	अगर (fepriv->dvbdev->ग_लिखोrs == 1)
		अगर (समय_after_eq(jअगरfies, fepriv->release_jअगरfies +
				  dvb_shutकरोwn_समयout * HZ))
			वापस 1;

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_frontend_should_wakeup(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;

	अगर (fepriv->wakeup) अणु
		fepriv->wakeup = 0;
		वापस 1;
	पूर्ण
	वापस dvb_frontend_is_निकासing(fe);
पूर्ण

अटल व्योम dvb_frontend_wakeup(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;

	fepriv->wakeup = 1;
	wake_up_पूर्णांकerruptible(&fepriv->रुको_queue);
पूर्ण

अटल पूर्णांक dvb_frontend_thपढ़ो(व्योम *data)
अणु
	काष्ठा dvb_frontend *fe = data;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	क्रमागत fe_status s = FE_NONE;
	क्रमागत dvbfe_algo algo;
	bool re_tune = false;
	bool semheld = false;

	dev_dbg(fe->dvb->device, "%s:\n", __func__);

	fepriv->check_wrapped = 0;
	fepriv->quality = 0;
	fepriv->delay = 3 * HZ;
	fepriv->status = 0;
	fepriv->wakeup = 0;
	fepriv->reinitialise = 0;

	dvb_frontend_init(fe);

	set_मुक्तzable();
	जबतक (1) अणु
		up(&fepriv->sem);	    /* is locked when we enter the thपढ़ो... */
restart:
		रुको_event_पूर्णांकerruptible_समयout(fepriv->रुको_queue,
						 dvb_frontend_should_wakeup(fe) ||
						 kthपढ़ो_should_stop() ||
						 मुक्तzing(current),
			fepriv->delay);

		अगर (kthपढ़ो_should_stop() || dvb_frontend_is_निकासing(fe)) अणु
			/* got संकेत or quitting */
			अगर (!करोwn_पूर्णांकerruptible(&fepriv->sem))
				semheld = true;
			fe->निकास = DVB_FE_NORMAL_EXIT;
			अवरोध;
		पूर्ण

		अगर (try_to_मुक्तze())
			जाओ restart;

		अगर (करोwn_पूर्णांकerruptible(&fepriv->sem))
			अवरोध;

		अगर (fepriv->reinitialise) अणु
			dvb_frontend_init(fe);
			अगर (fe->ops.set_tone && fepriv->tone != -1)
				fe->ops.set_tone(fe, fepriv->tone);
			अगर (fe->ops.set_voltage && fepriv->voltage != -1)
				fe->ops.set_voltage(fe, fepriv->voltage);
			fepriv->reinitialise = 0;
		पूर्ण

		/* करो an iteration of the tuning loop */
		अगर (fe->ops.get_frontend_algo) अणु
			algo = fe->ops.get_frontend_algo(fe);
			चयन (algo) अणु
			हाल DVBFE_ALGO_HW:
				dev_dbg(fe->dvb->device, "%s: Frontend ALGO = DVBFE_ALGO_HW\n", __func__);

				अगर (fepriv->state & FESTATE_RETUNE) अणु
					dev_dbg(fe->dvb->device, "%s: Retune requested, FESTATE_RETUNE\n", __func__);
					re_tune = true;
					fepriv->state = FESTATE_TUNED;
				पूर्ण अन्यथा अणु
					re_tune = false;
				पूर्ण

				अगर (fe->ops.tune)
					fe->ops.tune(fe, re_tune, fepriv->tune_mode_flags, &fepriv->delay, &s);

				अगर (s != fepriv->status && !(fepriv->tune_mode_flags & FE_TUNE_MODE_ONESHOT)) अणु
					dev_dbg(fe->dvb->device, "%s: state changed, adding current state\n", __func__);
					dvb_frontend_add_event(fe, s);
					fepriv->status = s;
				पूर्ण
				अवरोध;
			हाल DVBFE_ALGO_SW:
				dev_dbg(fe->dvb->device, "%s: Frontend ALGO = DVBFE_ALGO_SW\n", __func__);
				dvb_frontend_swzigzag(fe);
				अवरोध;
			हाल DVBFE_ALGO_CUSTOM:
				dev_dbg(fe->dvb->device, "%s: Frontend ALGO = DVBFE_ALGO_CUSTOM, state=%d\n", __func__, fepriv->state);
				अगर (fepriv->state & FESTATE_RETUNE) अणु
					dev_dbg(fe->dvb->device, "%s: Retune requested, FESTAT_RETUNE\n", __func__);
					fepriv->state = FESTATE_TUNED;
				पूर्ण
				/* Case where we are going to search क्रम a carrier
				 * User asked us to retune again क्रम some reason, possibly
				 * requesting a search with a new set of parameters
				 */
				अगर (fepriv->algo_status & DVBFE_ALGO_SEARCH_AGAIN) अणु
					अगर (fe->ops.search) अणु
						fepriv->algo_status = fe->ops.search(fe);
						/* We did करो a search as was requested, the flags are
						 * now unset as well and has the flags wrt to search.
						 */
					पूर्ण अन्यथा अणु
						fepriv->algo_status &= ~DVBFE_ALGO_SEARCH_AGAIN;
					पूर्ण
				पूर्ण
				/* Track the carrier अगर the search was successful */
				अगर (fepriv->algo_status != DVBFE_ALGO_SEARCH_SUCCESS) अणु
					fepriv->algo_status |= DVBFE_ALGO_SEARCH_AGAIN;
					fepriv->delay = HZ / 2;
				पूर्ण
				dtv_property_legacy_params_sync(fe, c, &fepriv->parameters_out);
				fe->ops.पढ़ो_status(fe, &s);
				अगर (s != fepriv->status) अणु
					dvb_frontend_add_event(fe, s); /* update event list */
					fepriv->status = s;
					अगर (!(s & FE_HAS_LOCK)) अणु
						fepriv->delay = HZ / 10;
						fepriv->algo_status |= DVBFE_ALGO_SEARCH_AGAIN;
					पूर्ण अन्यथा अणु
						fepriv->delay = 60 * HZ;
					पूर्ण
				पूर्ण
				अवरोध;
			शेष:
				dev_dbg(fe->dvb->device, "%s: UNDEFINED ALGO !\n", __func__);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			dvb_frontend_swzigzag(fe);
		पूर्ण
	पूर्ण

	अगर (dvb_घातerकरोwn_on_sleep) अणु
		अगर (fe->ops.set_voltage)
			fe->ops.set_voltage(fe, SEC_VOLTAGE_OFF);
		अगर (fe->ops.tuner_ops.sleep) अणु
			अगर (fe->ops.i2c_gate_ctrl)
				fe->ops.i2c_gate_ctrl(fe, 1);
			fe->ops.tuner_ops.sleep(fe);
			अगर (fe->ops.i2c_gate_ctrl)
				fe->ops.i2c_gate_ctrl(fe, 0);
		पूर्ण
		अगर (fe->ops.sleep)
			fe->ops.sleep(fe);
	पूर्ण

	fepriv->thपढ़ो = शून्य;
	अगर (kthपढ़ो_should_stop())
		fe->निकास = DVB_FE_DEVICE_REMOVED;
	अन्यथा
		fe->निकास = DVB_FE_NO_EXIT;
	mb();

	अगर (semheld)
		up(&fepriv->sem);
	dvb_frontend_wakeup(fe);
	वापस 0;
पूर्ण

अटल व्योम dvb_frontend_stop(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;

	dev_dbg(fe->dvb->device, "%s:\n", __func__);

	अगर (fe->निकास != DVB_FE_DEVICE_REMOVED)
		fe->निकास = DVB_FE_NORMAL_EXIT;
	mb();

	अगर (!fepriv->thपढ़ो)
		वापस;

	kthपढ़ो_stop(fepriv->thपढ़ो);

	sema_init(&fepriv->sem, 1);
	fepriv->state = FESTATE_IDLE;

	/* paranoia check in हाल a संकेत arrived */
	अगर (fepriv->thपढ़ो)
		dev_warn(fe->dvb->device,
			 "dvb_frontend_stop: warning: thread %p won't exit\n",
			 fepriv->thपढ़ो);
पूर्ण

/*
 * Sleep क्रम the amount of समय given by add_usec parameter
 *
 * This needs to be as precise as possible, as it affects the detection of
 * the dish tone command at the satellite subप्रणाली. The precision is improved
 * by using a scheduled msleep followed by udelay क्रम the reमुख्यder.
 */
व्योम dvb_frontend_sleep_until(kसमय_प्रकार *wakeसमय, u32 add_usec)
अणु
	s32 delta;

	*wakeसमय = kसमय_add_us(*wakeसमय, add_usec);
	delta = kसमय_us_delta(kसमय_get_bootसमय(), *wakeसमय);
	अगर (delta > 2500) अणु
		msleep((delta - 1500) / 1000);
		delta = kसमय_us_delta(kसमय_get_bootसमय(), *wakeसमय);
	पूर्ण
	अगर (delta > 0)
		udelay(delta);
पूर्ण
EXPORT_SYMBOL(dvb_frontend_sleep_until);

अटल पूर्णांक dvb_frontend_start(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret;
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	काष्ठा task_काष्ठा *fe_thपढ़ो;

	dev_dbg(fe->dvb->device, "%s:\n", __func__);

	अगर (fepriv->thपढ़ो) अणु
		अगर (fe->निकास == DVB_FE_NO_EXIT)
			वापस 0;
		अन्यथा
			dvb_frontend_stop(fe);
	पूर्ण

	अगर (संकेत_pending(current))
		वापस -EINTR;
	अगर (करोwn_पूर्णांकerruptible(&fepriv->sem))
		वापस -EINTR;

	fepriv->state = FESTATE_IDLE;
	fe->निकास = DVB_FE_NO_EXIT;
	fepriv->thपढ़ो = शून्य;
	mb();

	fe_thपढ़ो = kthपढ़ो_run(dvb_frontend_thपढ़ो, fe,
				"kdvb-ad-%i-fe-%i", fe->dvb->num, fe->id);
	अगर (IS_ERR(fe_thपढ़ो)) अणु
		ret = PTR_ERR(fe_thपढ़ो);
		dev_warn(fe->dvb->device,
			 "dvb_frontend_start: failed to start kthread (%d)\n",
			 ret);
		up(&fepriv->sem);
		वापस ret;
	पूर्ण
	fepriv->thपढ़ो = fe_thपढ़ो;
	वापस 0;
पूर्ण

अटल व्योम dvb_frontend_get_frequency_limits(काष्ठा dvb_frontend *fe,
					      u32 *freq_min, u32 *freq_max,
					      u32 *tolerance)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 tuner_min = fe->ops.tuner_ops.info.frequency_min_hz;
	u32 tuner_max = fe->ops.tuner_ops.info.frequency_max_hz;
	u32 frontend_min = fe->ops.info.frequency_min_hz;
	u32 frontend_max = fe->ops.info.frequency_max_hz;

	*freq_min = max(frontend_min, tuner_min);

	अगर (frontend_max == 0)
		*freq_max = tuner_max;
	अन्यथा अगर (tuner_max == 0)
		*freq_max = frontend_max;
	अन्यथा
		*freq_max = min(frontend_max, tuner_max);

	अगर (*freq_min == 0 || *freq_max == 0)
		dev_warn(fe->dvb->device,
			 "DVB: adapter %i frontend %u frequency limits undefined - fix the driver\n",
			 fe->dvb->num, fe->id);

	dev_dbg(fe->dvb->device, "frequency interval: tuner: %u...%u, frontend: %u...%u",
		tuner_min, tuner_max, frontend_min, frontend_max);

	/* If the standard is क्रम satellite, convert frequencies to kHz */
	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
	हाल SYS_DVBS2:
	हाल SYS_TURBO:
	हाल SYS_ISDBS:
		*freq_min /= kHz;
		*freq_max /= kHz;
		अगर (tolerance)
			*tolerance = fe->ops.info.frequency_tolerance_hz / kHz;

		अवरोध;
	शेष:
		अगर (tolerance)
			*tolerance = fe->ops.info.frequency_tolerance_hz;
		अवरोध;
	पूर्ण
पूर्ण

अटल u32 dvb_frontend_get_stepsize(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 fe_step = fe->ops.info.frequency_stepsize_hz;
	u32 tuner_step = fe->ops.tuner_ops.info.frequency_step_hz;
	u32 step = max(fe_step, tuner_step);

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
	हाल SYS_DVBS2:
	हाल SYS_TURBO:
	हाल SYS_ISDBS:
		step /= kHz;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस step;
पूर्ण

अटल पूर्णांक dvb_frontend_check_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 freq_min;
	u32 freq_max;

	/* range check: frequency */
	dvb_frontend_get_frequency_limits(fe, &freq_min, &freq_max, शून्य);
	अगर ((freq_min && c->frequency < freq_min) ||
	    (freq_max && c->frequency > freq_max)) अणु
		dev_warn(fe->dvb->device, "DVB: adapter %i frontend %i frequency %u out of range (%u..%u)\n",
			 fe->dvb->num, fe->id, c->frequency,
			 freq_min, freq_max);
		वापस -EINVAL;
	पूर्ण

	/* range check: symbol rate */
	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
	हाल SYS_DVBS2:
	हाल SYS_TURBO:
	हाल SYS_DVBC_ANNEX_A:
	हाल SYS_DVBC_ANNEX_C:
		अगर ((fe->ops.info.symbol_rate_min &&
		     c->symbol_rate < fe->ops.info.symbol_rate_min) ||
		    (fe->ops.info.symbol_rate_max &&
		     c->symbol_rate > fe->ops.info.symbol_rate_max)) अणु
			dev_warn(fe->dvb->device, "DVB: adapter %i frontend %i symbol rate %u out of range (%u..%u)\n",
				 fe->dvb->num, fe->id, c->symbol_rate,
				 fe->ops.info.symbol_rate_min,
				 fe->ops.info.symbol_rate_max);
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_frontend_clear_cache(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक i;
	u32 delsys;

	delsys = c->delivery_प्रणाली;
	स_रखो(c, 0, दुरत्व(काष्ठा dtv_frontend_properties, strength));
	c->delivery_प्रणाली = delsys;

	dev_dbg(fe->dvb->device, "%s: Clearing cache for delivery system %d\n",
		__func__, c->delivery_प्रणाली);

	c->transmission_mode = TRANSMISSION_MODE_AUTO;
	c->bandwidth_hz = 0;	/* AUTO */
	c->guard_पूर्णांकerval = GUARD_INTERVAL_AUTO;
	c->hierarchy = HIERARCHY_AUTO;
	c->symbol_rate = 0;
	c->code_rate_HP = FEC_AUTO;
	c->code_rate_LP = FEC_AUTO;
	c->fec_inner = FEC_AUTO;
	c->rolloff = ROLLOFF_AUTO;
	c->voltage = SEC_VOLTAGE_OFF;
	c->sectone = SEC_TONE_OFF;
	c->pilot = PILOT_AUTO;

	c->isdbt_partial_reception = 0;
	c->isdbt_sb_mode = 0;
	c->isdbt_sb_subchannel = 0;
	c->isdbt_sb_segment_idx = 0;
	c->isdbt_sb_segment_count = 0;
	c->isdbt_layer_enabled = 7;	/* All layers (A,B,C) */
	क्रम (i = 0; i < 3; i++) अणु
		c->layer[i].fec = FEC_AUTO;
		c->layer[i].modulation = QAM_AUTO;
		c->layer[i].पूर्णांकerleaving = 0;
		c->layer[i].segment_count = 0;
	पूर्ण

	c->stream_id = NO_STREAM_ID_FILTER;
	c->scrambling_sequence_index = 0;/* शेष sequence */

	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_DVBS:
	हाल SYS_DVBS2:
	हाल SYS_TURBO:
		c->modulation = QPSK;   /* implied क्रम DVB-S in legacy API */
		c->rolloff = ROLLOFF_35;/* implied क्रम DVB-S */
		अवरोध;
	हाल SYS_ATSC:
		c->modulation = VSB_8;
		अवरोध;
	हाल SYS_ISDBS:
		c->symbol_rate = 28860000;
		c->rolloff = ROLLOFF_35;
		c->bandwidth_hz = c->symbol_rate / 100 * 135;
		अवरोध;
	शेष:
		c->modulation = QAM_AUTO;
		अवरोध;
	पूर्ण

	c->lna = LNA_AUTO;

	वापस 0;
पूर्ण

#घोषणा _DTV_CMD(n, s, b) \
[n] = अणु \
	.name = #n, \
	.cmd  = n, \
	.set  = s,\
	.buffer = b \
पूर्ण

काष्ठा dtv_cmds_h अणु
	अक्षर	*name;		/* A display name क्रम debugging purposes */

	__u32	cmd;		/* A unique ID */

	/* Flags */
	__u32	set:1;		/* Either a set or get property */
	__u32	buffer:1;	/* Does this property use the buffer? */
	__u32	reserved:30;	/* Align */
पूर्ण;

अटल काष्ठा dtv_cmds_h dtv_cmds[DTV_MAX_COMMAND + 1] = अणु
	_DTV_CMD(DTV_TUNE, 1, 0),
	_DTV_CMD(DTV_CLEAR, 1, 0),

	/* Set */
	_DTV_CMD(DTV_FREQUENCY, 1, 0),
	_DTV_CMD(DTV_BANDWIDTH_HZ, 1, 0),
	_DTV_CMD(DTV_MODULATION, 1, 0),
	_DTV_CMD(DTV_INVERSION, 1, 0),
	_DTV_CMD(DTV_DISEQC_MASTER, 1, 1),
	_DTV_CMD(DTV_SYMBOL_RATE, 1, 0),
	_DTV_CMD(DTV_INNER_FEC, 1, 0),
	_DTV_CMD(DTV_VOLTAGE, 1, 0),
	_DTV_CMD(DTV_TONE, 1, 0),
	_DTV_CMD(DTV_PILOT, 1, 0),
	_DTV_CMD(DTV_ROLLOFF, 1, 0),
	_DTV_CMD(DTV_DELIVERY_SYSTEM, 1, 0),
	_DTV_CMD(DTV_HIERARCHY, 1, 0),
	_DTV_CMD(DTV_CODE_RATE_HP, 1, 0),
	_DTV_CMD(DTV_CODE_RATE_LP, 1, 0),
	_DTV_CMD(DTV_GUARD_INTERVAL, 1, 0),
	_DTV_CMD(DTV_TRANSMISSION_MODE, 1, 0),
	_DTV_CMD(DTV_INTERLEAVING, 1, 0),

	_DTV_CMD(DTV_ISDBT_PARTIAL_RECEPTION, 1, 0),
	_DTV_CMD(DTV_ISDBT_SOUND_BROADCASTING, 1, 0),
	_DTV_CMD(DTV_ISDBT_SB_SUBCHANNEL_ID, 1, 0),
	_DTV_CMD(DTV_ISDBT_SB_SEGMENT_IDX, 1, 0),
	_DTV_CMD(DTV_ISDBT_SB_SEGMENT_COUNT, 1, 0),
	_DTV_CMD(DTV_ISDBT_LAYER_ENABLED, 1, 0),
	_DTV_CMD(DTV_ISDBT_LAYERA_FEC, 1, 0),
	_DTV_CMD(DTV_ISDBT_LAYERA_MODULATION, 1, 0),
	_DTV_CMD(DTV_ISDBT_LAYERA_SEGMENT_COUNT, 1, 0),
	_DTV_CMD(DTV_ISDBT_LAYERA_TIME_INTERLEAVING, 1, 0),
	_DTV_CMD(DTV_ISDBT_LAYERB_FEC, 1, 0),
	_DTV_CMD(DTV_ISDBT_LAYERB_MODULATION, 1, 0),
	_DTV_CMD(DTV_ISDBT_LAYERB_SEGMENT_COUNT, 1, 0),
	_DTV_CMD(DTV_ISDBT_LAYERB_TIME_INTERLEAVING, 1, 0),
	_DTV_CMD(DTV_ISDBT_LAYERC_FEC, 1, 0),
	_DTV_CMD(DTV_ISDBT_LAYERC_MODULATION, 1, 0),
	_DTV_CMD(DTV_ISDBT_LAYERC_SEGMENT_COUNT, 1, 0),
	_DTV_CMD(DTV_ISDBT_LAYERC_TIME_INTERLEAVING, 1, 0),

	_DTV_CMD(DTV_STREAM_ID, 1, 0),
	_DTV_CMD(DTV_DVBT2_PLP_ID_LEGACY, 1, 0),
	_DTV_CMD(DTV_SCRAMBLING_SEQUENCE_INDEX, 1, 0),
	_DTV_CMD(DTV_LNA, 1, 0),

	/* Get */
	_DTV_CMD(DTV_DISEQC_SLAVE_REPLY, 0, 1),
	_DTV_CMD(DTV_API_VERSION, 0, 0),

	_DTV_CMD(DTV_ENUM_DELSYS, 0, 0),

	_DTV_CMD(DTV_ATSCMH_PARADE_ID, 1, 0),
	_DTV_CMD(DTV_ATSCMH_RS_FRAME_ENSEMBLE, 1, 0),

	_DTV_CMD(DTV_ATSCMH_FIC_VER, 0, 0),
	_DTV_CMD(DTV_ATSCMH_NOG, 0, 0),
	_DTV_CMD(DTV_ATSCMH_TNOG, 0, 0),
	_DTV_CMD(DTV_ATSCMH_SGN, 0, 0),
	_DTV_CMD(DTV_ATSCMH_PRC, 0, 0),
	_DTV_CMD(DTV_ATSCMH_RS_FRAME_MODE, 0, 0),
	_DTV_CMD(DTV_ATSCMH_RS_CODE_MODE_PRI, 0, 0),
	_DTV_CMD(DTV_ATSCMH_RS_CODE_MODE_SEC, 0, 0),
	_DTV_CMD(DTV_ATSCMH_SCCC_BLOCK_MODE, 0, 0),
	_DTV_CMD(DTV_ATSCMH_SCCC_CODE_MODE_A, 0, 0),
	_DTV_CMD(DTV_ATSCMH_SCCC_CODE_MODE_B, 0, 0),
	_DTV_CMD(DTV_ATSCMH_SCCC_CODE_MODE_C, 0, 0),
	_DTV_CMD(DTV_ATSCMH_SCCC_CODE_MODE_D, 0, 0),

	/* Statistics API */
	_DTV_CMD(DTV_STAT_SIGNAL_STRENGTH, 0, 0),
	_DTV_CMD(DTV_STAT_CNR, 0, 0),
	_DTV_CMD(DTV_STAT_PRE_ERROR_BIT_COUNT, 0, 0),
	_DTV_CMD(DTV_STAT_PRE_TOTAL_BIT_COUNT, 0, 0),
	_DTV_CMD(DTV_STAT_POST_ERROR_BIT_COUNT, 0, 0),
	_DTV_CMD(DTV_STAT_POST_TOTAL_BIT_COUNT, 0, 0),
	_DTV_CMD(DTV_STAT_ERROR_BLOCK_COUNT, 0, 0),
	_DTV_CMD(DTV_STAT_TOTAL_BLOCK_COUNT, 0, 0),
पूर्ण;

/* Synchronise the legacy tuning parameters पूर्णांकo the cache, so that demodulator
 * drivers can use a single set_frontend tuning function, regardless of whether
 * it's being used क्रम the legacy or new API, reducing code and complनिकासy.
 */
अटल पूर्णांक dtv_property_cache_sync(काष्ठा dvb_frontend *fe,
				   काष्ठा dtv_frontend_properties *c,
				   स्थिर काष्ठा dvb_frontend_parameters *p)
अणु
	c->frequency = p->frequency;
	c->inversion = p->inversion;

	चयन (dvbv3_type(c->delivery_प्रणाली)) अणु
	हाल DVBV3_QPSK:
		dev_dbg(fe->dvb->device, "%s: Preparing QPSK req\n", __func__);
		c->symbol_rate = p->u.qpsk.symbol_rate;
		c->fec_inner = p->u.qpsk.fec_inner;
		अवरोध;
	हाल DVBV3_QAM:
		dev_dbg(fe->dvb->device, "%s: Preparing QAM req\n", __func__);
		c->symbol_rate = p->u.qam.symbol_rate;
		c->fec_inner = p->u.qam.fec_inner;
		c->modulation = p->u.qam.modulation;
		अवरोध;
	हाल DVBV3_OFDM:
		dev_dbg(fe->dvb->device, "%s: Preparing OFDM req\n", __func__);

		चयन (p->u.ofdm.bandwidth) अणु
		हाल BANDWIDTH_10_MHZ:
			c->bandwidth_hz = 10000000;
			अवरोध;
		हाल BANDWIDTH_8_MHZ:
			c->bandwidth_hz = 8000000;
			अवरोध;
		हाल BANDWIDTH_7_MHZ:
			c->bandwidth_hz = 7000000;
			अवरोध;
		हाल BANDWIDTH_6_MHZ:
			c->bandwidth_hz = 6000000;
			अवरोध;
		हाल BANDWIDTH_5_MHZ:
			c->bandwidth_hz = 5000000;
			अवरोध;
		हाल BANDWIDTH_1_712_MHZ:
			c->bandwidth_hz = 1712000;
			अवरोध;
		हाल BANDWIDTH_AUTO:
			c->bandwidth_hz = 0;
		पूर्ण

		c->code_rate_HP = p->u.ofdm.code_rate_HP;
		c->code_rate_LP = p->u.ofdm.code_rate_LP;
		c->modulation = p->u.ofdm.स्थिरellation;
		c->transmission_mode = p->u.ofdm.transmission_mode;
		c->guard_पूर्णांकerval = p->u.ofdm.guard_पूर्णांकerval;
		c->hierarchy = p->u.ofdm.hierarchy_inक्रमmation;
		अवरोध;
	हाल DVBV3_ATSC:
		dev_dbg(fe->dvb->device, "%s: Preparing ATSC req\n", __func__);
		c->modulation = p->u.vsb.modulation;
		अगर (c->delivery_प्रणाली == SYS_ATSCMH)
			अवरोध;
		अगर ((c->modulation == VSB_8) || (c->modulation == VSB_16))
			c->delivery_प्रणाली = SYS_ATSC;
		अन्यथा
			c->delivery_प्रणाली = SYS_DVBC_ANNEX_B;
		अवरोध;
	हाल DVBV3_UNKNOWN:
		dev_err(fe->dvb->device,
			"%s: doesn't know how to handle a DVBv3 call to delivery system %i\n",
			__func__, c->delivery_प्रणाली);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/* Ensure the cached values are set correctly in the frontend
 * legacy tuning काष्ठाures, क्रम the advanced tuning API.
 */
अटल पूर्णांक
dtv_property_legacy_params_sync(काष्ठा dvb_frontend *fe,
				स्थिर काष्ठा dtv_frontend_properties *c,
				काष्ठा dvb_frontend_parameters *p)
अणु
	p->frequency = c->frequency;
	p->inversion = c->inversion;

	चयन (dvbv3_type(c->delivery_प्रणाली)) अणु
	हाल DVBV3_UNKNOWN:
		dev_err(fe->dvb->device,
			"%s: doesn't know how to handle a DVBv3 call to delivery system %i\n",
			__func__, c->delivery_प्रणाली);
		वापस -EINVAL;
	हाल DVBV3_QPSK:
		dev_dbg(fe->dvb->device, "%s: Preparing QPSK req\n", __func__);
		p->u.qpsk.symbol_rate = c->symbol_rate;
		p->u.qpsk.fec_inner = c->fec_inner;
		अवरोध;
	हाल DVBV3_QAM:
		dev_dbg(fe->dvb->device, "%s: Preparing QAM req\n", __func__);
		p->u.qam.symbol_rate = c->symbol_rate;
		p->u.qam.fec_inner = c->fec_inner;
		p->u.qam.modulation = c->modulation;
		अवरोध;
	हाल DVBV3_OFDM:
		dev_dbg(fe->dvb->device, "%s: Preparing OFDM req\n", __func__);
		चयन (c->bandwidth_hz) अणु
		हाल 10000000:
			p->u.ofdm.bandwidth = BANDWIDTH_10_MHZ;
			अवरोध;
		हाल 8000000:
			p->u.ofdm.bandwidth = BANDWIDTH_8_MHZ;
			अवरोध;
		हाल 7000000:
			p->u.ofdm.bandwidth = BANDWIDTH_7_MHZ;
			अवरोध;
		हाल 6000000:
			p->u.ofdm.bandwidth = BANDWIDTH_6_MHZ;
			अवरोध;
		हाल 5000000:
			p->u.ofdm.bandwidth = BANDWIDTH_5_MHZ;
			अवरोध;
		हाल 1712000:
			p->u.ofdm.bandwidth = BANDWIDTH_1_712_MHZ;
			अवरोध;
		हाल 0:
		शेष:
			p->u.ofdm.bandwidth = BANDWIDTH_AUTO;
		पूर्ण
		p->u.ofdm.code_rate_HP = c->code_rate_HP;
		p->u.ofdm.code_rate_LP = c->code_rate_LP;
		p->u.ofdm.स्थिरellation = c->modulation;
		p->u.ofdm.transmission_mode = c->transmission_mode;
		p->u.ofdm.guard_पूर्णांकerval = c->guard_पूर्णांकerval;
		p->u.ofdm.hierarchy_inक्रमmation = c->hierarchy;
		अवरोध;
	हाल DVBV3_ATSC:
		dev_dbg(fe->dvb->device, "%s: Preparing VSB req\n", __func__);
		p->u.vsb.modulation = c->modulation;
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * dtv_get_frontend - calls a callback क्रम retrieving DTV parameters
 * @fe:		काष्ठा dvb_frontend poपूर्णांकer
 * @c:		काष्ठा dtv_frontend_properties poपूर्णांकer (DVBv5 cache)
 * @p_out:	काष्ठा dvb_frontend_parameters poपूर्णांकer (DVBv3 FE काष्ठा)
 *
 * This routine calls either the DVBv3 or DVBv5 get_frontend call.
 * If c is not null, it will update the DVBv5 cache काष्ठा poपूर्णांकed by it.
 * If p_out is not null, it will update the DVBv3 params poपूर्णांकed by it.
 */
अटल पूर्णांक dtv_get_frontend(काष्ठा dvb_frontend *fe,
			    काष्ठा dtv_frontend_properties *c,
			    काष्ठा dvb_frontend_parameters *p_out)
अणु
	पूर्णांक r;

	अगर (fe->ops.get_frontend) अणु
		r = fe->ops.get_frontend(fe, c);
		अगर (unlikely(r < 0))
			वापस r;
		अगर (p_out)
			dtv_property_legacy_params_sync(fe, c, p_out);
		वापस 0;
	पूर्ण

	/* As everything is in cache, get_frontend fops are always supported */
	वापस 0;
पूर्ण

अटल पूर्णांक dvb_frontend_handle_ioctl(काष्ठा file *file,
				     अचिन्हित पूर्णांक cmd, व्योम *parg);

अटल पूर्णांक dtv_property_process_get(काष्ठा dvb_frontend *fe,
				    स्थिर काष्ठा dtv_frontend_properties *c,
				    काष्ठा dtv_property *tvp,
				    काष्ठा file *file)
अणु
	पूर्णांक ncaps;

	चयन (tvp->cmd) अणु
	हाल DTV_ENUM_DELSYS:
		ncaps = 0;
		जबतक (ncaps < MAX_DELSYS && fe->ops.delsys[ncaps]) अणु
			tvp->u.buffer.data[ncaps] = fe->ops.delsys[ncaps];
			ncaps++;
		पूर्ण
		tvp->u.buffer.len = ncaps;
		अवरोध;
	हाल DTV_FREQUENCY:
		tvp->u.data = c->frequency;
		अवरोध;
	हाल DTV_MODULATION:
		tvp->u.data = c->modulation;
		अवरोध;
	हाल DTV_BANDWIDTH_HZ:
		tvp->u.data = c->bandwidth_hz;
		अवरोध;
	हाल DTV_INVERSION:
		tvp->u.data = c->inversion;
		अवरोध;
	हाल DTV_SYMBOL_RATE:
		tvp->u.data = c->symbol_rate;
		अवरोध;
	हाल DTV_INNER_FEC:
		tvp->u.data = c->fec_inner;
		अवरोध;
	हाल DTV_PILOT:
		tvp->u.data = c->pilot;
		अवरोध;
	हाल DTV_ROLLOFF:
		tvp->u.data = c->rolloff;
		अवरोध;
	हाल DTV_DELIVERY_SYSTEM:
		tvp->u.data = c->delivery_प्रणाली;
		अवरोध;
	हाल DTV_VOLTAGE:
		tvp->u.data = c->voltage;
		अवरोध;
	हाल DTV_TONE:
		tvp->u.data = c->sectone;
		अवरोध;
	हाल DTV_API_VERSION:
		tvp->u.data = (DVB_API_VERSION << 8) | DVB_API_VERSION_MINOR;
		अवरोध;
	हाल DTV_CODE_RATE_HP:
		tvp->u.data = c->code_rate_HP;
		अवरोध;
	हाल DTV_CODE_RATE_LP:
		tvp->u.data = c->code_rate_LP;
		अवरोध;
	हाल DTV_GUARD_INTERVAL:
		tvp->u.data = c->guard_पूर्णांकerval;
		अवरोध;
	हाल DTV_TRANSMISSION_MODE:
		tvp->u.data = c->transmission_mode;
		अवरोध;
	हाल DTV_HIERARCHY:
		tvp->u.data = c->hierarchy;
		अवरोध;
	हाल DTV_INTERLEAVING:
		tvp->u.data = c->पूर्णांकerleaving;
		अवरोध;

	/* ISDB-T Support here */
	हाल DTV_ISDBT_PARTIAL_RECEPTION:
		tvp->u.data = c->isdbt_partial_reception;
		अवरोध;
	हाल DTV_ISDBT_SOUND_BROADCASTING:
		tvp->u.data = c->isdbt_sb_mode;
		अवरोध;
	हाल DTV_ISDBT_SB_SUBCHANNEL_ID:
		tvp->u.data = c->isdbt_sb_subchannel;
		अवरोध;
	हाल DTV_ISDBT_SB_SEGMENT_IDX:
		tvp->u.data = c->isdbt_sb_segment_idx;
		अवरोध;
	हाल DTV_ISDBT_SB_SEGMENT_COUNT:
		tvp->u.data = c->isdbt_sb_segment_count;
		अवरोध;
	हाल DTV_ISDBT_LAYER_ENABLED:
		tvp->u.data = c->isdbt_layer_enabled;
		अवरोध;
	हाल DTV_ISDBT_LAYERA_FEC:
		tvp->u.data = c->layer[0].fec;
		अवरोध;
	हाल DTV_ISDBT_LAYERA_MODULATION:
		tvp->u.data = c->layer[0].modulation;
		अवरोध;
	हाल DTV_ISDBT_LAYERA_SEGMENT_COUNT:
		tvp->u.data = c->layer[0].segment_count;
		अवरोध;
	हाल DTV_ISDBT_LAYERA_TIME_INTERLEAVING:
		tvp->u.data = c->layer[0].पूर्णांकerleaving;
		अवरोध;
	हाल DTV_ISDBT_LAYERB_FEC:
		tvp->u.data = c->layer[1].fec;
		अवरोध;
	हाल DTV_ISDBT_LAYERB_MODULATION:
		tvp->u.data = c->layer[1].modulation;
		अवरोध;
	हाल DTV_ISDBT_LAYERB_SEGMENT_COUNT:
		tvp->u.data = c->layer[1].segment_count;
		अवरोध;
	हाल DTV_ISDBT_LAYERB_TIME_INTERLEAVING:
		tvp->u.data = c->layer[1].पूर्णांकerleaving;
		अवरोध;
	हाल DTV_ISDBT_LAYERC_FEC:
		tvp->u.data = c->layer[2].fec;
		अवरोध;
	हाल DTV_ISDBT_LAYERC_MODULATION:
		tvp->u.data = c->layer[2].modulation;
		अवरोध;
	हाल DTV_ISDBT_LAYERC_SEGMENT_COUNT:
		tvp->u.data = c->layer[2].segment_count;
		अवरोध;
	हाल DTV_ISDBT_LAYERC_TIME_INTERLEAVING:
		tvp->u.data = c->layer[2].पूर्णांकerleaving;
		अवरोध;

	/* Multistream support */
	हाल DTV_STREAM_ID:
	हाल DTV_DVBT2_PLP_ID_LEGACY:
		tvp->u.data = c->stream_id;
		अवरोध;

	/* Physical layer scrambling support */
	हाल DTV_SCRAMBLING_SEQUENCE_INDEX:
		tvp->u.data = c->scrambling_sequence_index;
		अवरोध;

	/* ATSC-MH */
	हाल DTV_ATSCMH_FIC_VER:
		tvp->u.data = fe->dtv_property_cache.atscmh_fic_ver;
		अवरोध;
	हाल DTV_ATSCMH_PARADE_ID:
		tvp->u.data = fe->dtv_property_cache.atscmh_parade_id;
		अवरोध;
	हाल DTV_ATSCMH_NOG:
		tvp->u.data = fe->dtv_property_cache.atscmh_nog;
		अवरोध;
	हाल DTV_ATSCMH_TNOG:
		tvp->u.data = fe->dtv_property_cache.atscmh_tnog;
		अवरोध;
	हाल DTV_ATSCMH_SGN:
		tvp->u.data = fe->dtv_property_cache.atscmh_sgn;
		अवरोध;
	हाल DTV_ATSCMH_PRC:
		tvp->u.data = fe->dtv_property_cache.atscmh_prc;
		अवरोध;
	हाल DTV_ATSCMH_RS_FRAME_MODE:
		tvp->u.data = fe->dtv_property_cache.atscmh_rs_frame_mode;
		अवरोध;
	हाल DTV_ATSCMH_RS_FRAME_ENSEMBLE:
		tvp->u.data = fe->dtv_property_cache.atscmh_rs_frame_ensemble;
		अवरोध;
	हाल DTV_ATSCMH_RS_CODE_MODE_PRI:
		tvp->u.data = fe->dtv_property_cache.atscmh_rs_code_mode_pri;
		अवरोध;
	हाल DTV_ATSCMH_RS_CODE_MODE_SEC:
		tvp->u.data = fe->dtv_property_cache.atscmh_rs_code_mode_sec;
		अवरोध;
	हाल DTV_ATSCMH_SCCC_BLOCK_MODE:
		tvp->u.data = fe->dtv_property_cache.atscmh_sccc_block_mode;
		अवरोध;
	हाल DTV_ATSCMH_SCCC_CODE_MODE_A:
		tvp->u.data = fe->dtv_property_cache.atscmh_sccc_code_mode_a;
		अवरोध;
	हाल DTV_ATSCMH_SCCC_CODE_MODE_B:
		tvp->u.data = fe->dtv_property_cache.atscmh_sccc_code_mode_b;
		अवरोध;
	हाल DTV_ATSCMH_SCCC_CODE_MODE_C:
		tvp->u.data = fe->dtv_property_cache.atscmh_sccc_code_mode_c;
		अवरोध;
	हाल DTV_ATSCMH_SCCC_CODE_MODE_D:
		tvp->u.data = fe->dtv_property_cache.atscmh_sccc_code_mode_d;
		अवरोध;

	हाल DTV_LNA:
		tvp->u.data = c->lna;
		अवरोध;

	/* Fill quality measures */
	हाल DTV_STAT_SIGNAL_STRENGTH:
		tvp->u.st = c->strength;
		अवरोध;
	हाल DTV_STAT_CNR:
		tvp->u.st = c->cnr;
		अवरोध;
	हाल DTV_STAT_PRE_ERROR_BIT_COUNT:
		tvp->u.st = c->pre_bit_error;
		अवरोध;
	हाल DTV_STAT_PRE_TOTAL_BIT_COUNT:
		tvp->u.st = c->pre_bit_count;
		अवरोध;
	हाल DTV_STAT_POST_ERROR_BIT_COUNT:
		tvp->u.st = c->post_bit_error;
		अवरोध;
	हाल DTV_STAT_POST_TOTAL_BIT_COUNT:
		tvp->u.st = c->post_bit_count;
		अवरोध;
	हाल DTV_STAT_ERROR_BLOCK_COUNT:
		tvp->u.st = c->block_error;
		अवरोध;
	हाल DTV_STAT_TOTAL_BLOCK_COUNT:
		tvp->u.st = c->block_count;
		अवरोध;
	शेष:
		dev_dbg(fe->dvb->device,
			"%s: FE property %d doesn't exist\n",
			__func__, tvp->cmd);
		वापस -EINVAL;
	पूर्ण

	अगर (!dtv_cmds[tvp->cmd].buffer)
		dev_dbg(fe->dvb->device,
			"%s: GET cmd 0x%08x (%s) = 0x%08x\n",
			__func__, tvp->cmd, dtv_cmds[tvp->cmd].name,
			tvp->u.data);
	अन्यथा
		dev_dbg(fe->dvb->device,
			"%s: GET cmd 0x%08x (%s) len %d: %*ph\n",
			__func__,
			tvp->cmd, dtv_cmds[tvp->cmd].name,
			tvp->u.buffer.len,
			tvp->u.buffer.len, tvp->u.buffer.data);

	वापस 0;
पूर्ण

अटल पूर्णांक dtv_set_frontend(काष्ठा dvb_frontend *fe);

अटल bool is_dvbv3_delsys(u32 delsys)
अणु
	वापस (delsys == SYS_DVBT) || (delsys == SYS_DVBC_ANNEX_A) ||
	       (delsys == SYS_DVBS) || (delsys == SYS_ATSC);
पूर्ण

/**
 * emulate_delivery_प्रणाली - emulate a DVBv5 delivery प्रणाली with a DVBv3 type
 * @fe:			काष्ठा frontend;
 * @delsys:			DVBv5 type that will be used क्रम emulation
 *
 * Provides emulation क्रम delivery प्रणालीs that are compatible with the old
 * DVBv3 call. Among its usages, it provices support क्रम ISDB-T, and allows
 * using a DVB-S2 only frontend just like it were a DVB-S, अगर the frontend
 * parameters are compatible with DVB-S spec.
 */
अटल पूर्णांक emulate_delivery_प्रणाली(काष्ठा dvb_frontend *fe, u32 delsys)
अणु
	पूर्णांक i;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	c->delivery_प्रणाली = delsys;

	/*
	 * If the call is क्रम ISDB-T, put it पूर्णांकo full-seg, स्वतः mode, TV
	 */
	अगर (c->delivery_प्रणाली == SYS_ISDBT) अणु
		dev_dbg(fe->dvb->device,
			"%s: Using defaults for SYS_ISDBT\n",
			__func__);

		अगर (!c->bandwidth_hz)
			c->bandwidth_hz = 6000000;

		c->isdbt_partial_reception = 0;
		c->isdbt_sb_mode = 0;
		c->isdbt_sb_subchannel = 0;
		c->isdbt_sb_segment_idx = 0;
		c->isdbt_sb_segment_count = 0;
		c->isdbt_layer_enabled = 7;
		क्रम (i = 0; i < 3; i++) अणु
			c->layer[i].fec = FEC_AUTO;
			c->layer[i].modulation = QAM_AUTO;
			c->layer[i].पूर्णांकerleaving = 0;
			c->layer[i].segment_count = 0;
		पूर्ण
	पूर्ण
	dev_dbg(fe->dvb->device, "%s: change delivery system on cache to %d\n",
		__func__, c->delivery_प्रणाली);

	वापस 0;
पूर्ण

/**
 * dvbv5_set_delivery_प्रणाली - Sets the delivery प्रणाली क्रम a DVBv5 API call
 * @fe:			frontend काष्ठा
 * @desired_प्रणाली:	delivery प्रणाली requested by the user
 *
 * A DVBv5 call know what's the desired प्रणाली it wants. So, set it.
 *
 * There are, however, a few known issues with early DVBv5 applications that
 * are also handled by this logic:
 *
 * 1) Some early apps use SYS_UNDEFINED as the desired delivery प्रणाली.
 *    This is an API violation, but, as we करोn't want to अवरोध userspace,
 *    convert it to the first supported delivery प्रणाली.
 * 2) Some apps might be using a DVBv5 call in a wrong way, passing, क्रम
 *    example, SYS_DVBT instead of SYS_ISDBT. This is because early usage of
 *    ISDB-T provided backward compat with DVB-T.
 */
अटल पूर्णांक dvbv5_set_delivery_प्रणाली(काष्ठा dvb_frontend *fe,
				     u32 desired_प्रणाली)
अणु
	पूर्णांक ncaps;
	u32 delsys = SYS_UNDEFINED;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	क्रमागत dvbv3_emulation_type type;

	/*
	 * It was reported that some old DVBv5 applications were
	 * filling delivery_प्रणाली with SYS_UNDEFINED. If this happens,
	 * assume that the application wants to use the first supported
	 * delivery प्रणाली.
	 */
	अगर (desired_प्रणाली == SYS_UNDEFINED)
		desired_प्रणाली = fe->ops.delsys[0];

	/*
	 * This is a DVBv5 call. So, it likely knows the supported
	 * delivery प्रणालीs. So, check अगर the desired delivery प्रणाली is
	 * supported
	 */
	ncaps = 0;
	जबतक (ncaps < MAX_DELSYS && fe->ops.delsys[ncaps]) अणु
		अगर (fe->ops.delsys[ncaps] == desired_प्रणाली) अणु
			c->delivery_प्रणाली = desired_प्रणाली;
			dev_dbg(fe->dvb->device,
				"%s: Changing delivery system to %d\n",
				__func__, desired_प्रणाली);
			वापस 0;
		पूर्ण
		ncaps++;
	पूर्ण

	/*
	 * The requested delivery प्रणाली isn't supported. Maybe userspace
	 * is requesting a DVBv3 compatible delivery प्रणाली.
	 *
	 * The emulation only works अगर the desired प्रणाली is one of the
	 * delivery प्रणालीs supported by DVBv3 API
	 */
	अगर (!is_dvbv3_delsys(desired_प्रणाली)) अणु
		dev_dbg(fe->dvb->device,
			"%s: Delivery system %d not supported.\n",
			__func__, desired_प्रणाली);
		वापस -EINVAL;
	पूर्ण

	type = dvbv3_type(desired_प्रणाली);

	/*
	* Get the last non-DVBv3 delivery प्रणाली that has the same type
	* of the desired प्रणाली
	*/
	ncaps = 0;
	जबतक (ncaps < MAX_DELSYS && fe->ops.delsys[ncaps]) अणु
		अगर (dvbv3_type(fe->ops.delsys[ncaps]) == type)
			delsys = fe->ops.delsys[ncaps];
		ncaps++;
	पूर्ण

	/* There's nothing compatible with the desired delivery प्रणाली */
	अगर (delsys == SYS_UNDEFINED) अणु
		dev_dbg(fe->dvb->device,
			"%s: Delivery system %d not supported on emulation mode.\n",
			__func__, desired_प्रणाली);
		वापस -EINVAL;
	पूर्ण

	dev_dbg(fe->dvb->device,
		"%s: Using delivery system %d emulated as if it were %d\n",
		__func__, delsys, desired_प्रणाली);

	वापस emulate_delivery_प्रणाली(fe, desired_प्रणाली);
पूर्ण

/**
 * dvbv3_set_delivery_प्रणाली - Sets the delivery प्रणाली क्रम a DVBv3 API call
 * @fe:	frontend काष्ठा
 *
 * A DVBv3 call करोesn't know what's the desired प्रणाली it wants. It also
 * करोesn't allow to चयन between dअगरferent types. Due to that, userspace
 * should use DVBv5 instead.
 * However, in order to aव्योम अवरोधing userspace API, limited backward
 * compatibility support is provided.
 *
 * There are some delivery प्रणालीs that are incompatible with DVBv3 calls.
 *
 * This routine should work fine क्रम frontends that support just one delivery
 * प्रणाली.
 *
 * For frontends that support multiple frontends:
 * 1) It शेषs to use the first supported delivery प्रणाली. There's an
 *    userspace application that allows changing it at runसमय;
 *
 * 2) If the current delivery प्रणाली is not compatible with DVBv3, it माला_लो
 *    the first one that it is compatible.
 *
 * NOTE: in order क्रम this to work with applications like Kaffeine that
 *	uses a DVBv5 call क्रम DVB-S2 and a DVBv3 call to go back to
 *	DVB-S, drivers that support both DVB-S and DVB-S2 should have the
 *	SYS_DVBS entry beक्रमe the SYS_DVBS2, otherwise it won't चयन back
 *	to DVB-S.
 */
अटल पूर्णांक dvbv3_set_delivery_प्रणाली(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ncaps;
	u32 delsys = SYS_UNDEFINED;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	/* If not set yet, शेषs to the first supported delivery प्रणाली */
	अगर (c->delivery_प्रणाली == SYS_UNDEFINED)
		c->delivery_प्रणाली = fe->ops.delsys[0];

	/*
	 * Trivial हाल: just use the current one, अगर it alपढ़ोy a DVBv3
	 * delivery प्रणाली
	 */
	अगर (is_dvbv3_delsys(c->delivery_प्रणाली)) अणु
		dev_dbg(fe->dvb->device,
			"%s: Using delivery system to %d\n",
			__func__, c->delivery_प्रणाली);
		वापस 0;
	पूर्ण

	/*
	 * Seek क्रम the first delivery प्रणाली that it is compatible with a
	 * DVBv3 standard
	 */
	ncaps = 0;
	जबतक (ncaps < MAX_DELSYS && fe->ops.delsys[ncaps]) अणु
		अगर (dvbv3_type(fe->ops.delsys[ncaps]) != DVBV3_UNKNOWN) अणु
			delsys = fe->ops.delsys[ncaps];
			अवरोध;
		पूर्ण
		ncaps++;
	पूर्ण
	अगर (delsys == SYS_UNDEFINED) अणु
		dev_dbg(fe->dvb->device,
			"%s: Couldn't find a delivery system that works with FE_SET_FRONTEND\n",
			__func__);
		वापस -EINVAL;
	पूर्ण
	वापस emulate_delivery_प्रणाली(fe, delsys);
पूर्ण

अटल व्योम prepare_tuning_algo_parameters(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	काष्ठा dvb_frontend_tune_settings fetunesettings = अणु 0 पूर्ण;

	/* get frontend-specअगरic tuning settings */
	अगर (fe->ops.get_tune_settings && (fe->ops.get_tune_settings(fe, &fetunesettings) == 0)) अणु
		fepriv->min_delay = (fetunesettings.min_delay_ms * HZ) / 1000;
		fepriv->max_drअगरt = fetunesettings.max_drअगरt;
		fepriv->step_size = fetunesettings.step_size;
	पूर्ण अन्यथा अणु
		/* शेष values */
		चयन (c->delivery_प्रणाली) अणु
		हाल SYS_DVBS:
		हाल SYS_DVBS2:
		हाल SYS_ISDBS:
		हाल SYS_TURBO:
		हाल SYS_DVBC_ANNEX_A:
		हाल SYS_DVBC_ANNEX_C:
			fepriv->min_delay = HZ / 20;
			fepriv->step_size = c->symbol_rate / 16000;
			fepriv->max_drअगरt = c->symbol_rate / 2000;
			अवरोध;
		हाल SYS_DVBT:
		हाल SYS_DVBT2:
		हाल SYS_ISDBT:
		हाल SYS_DTMB:
			fepriv->min_delay = HZ / 20;
			fepriv->step_size = dvb_frontend_get_stepsize(fe) * 2;
			fepriv->max_drअगरt = fepriv->step_size + 1;
			अवरोध;
		शेष:
			/*
			 * FIXME: This sounds wrong! अगर freqency_stepsize is
			 * defined by the frontend, why not use it???
			 */
			fepriv->min_delay = HZ / 20;
			fepriv->step_size = 0; /* no zigzag */
			fepriv->max_drअगरt = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (dvb_override_tune_delay > 0)
		fepriv->min_delay = (dvb_override_tune_delay * HZ) / 1000;
पूर्ण

/**
 * dtv_property_process_set -  Sets a single DTV property
 * @fe:		Poपूर्णांकer to &काष्ठा dvb_frontend
 * @file:	Poपूर्णांकer to &काष्ठा file
 * @cmd:	Digital TV command
 * @data:	An अचिन्हित 32-bits number
 *
 * This routine assigns the property
 * value to the corresponding member of
 * &काष्ठा dtv_frontend_properties
 *
 * Returns:
 * Zero on success, negative त्रुटि_सं on failure.
 */
अटल पूर्णांक dtv_property_process_set(काष्ठा dvb_frontend *fe,
				    काष्ठा file *file,
				    u32 cmd, u32 data)
अणु
	पूर्णांक r = 0;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;

	/** Dump DTV command name and value*/
	अगर (!cmd || cmd > DTV_MAX_COMMAND)
		dev_warn(fe->dvb->device, "%s: SET cmd 0x%08x undefined\n",
			 __func__, cmd);
	अन्यथा
		dev_dbg(fe->dvb->device,
			"%s: SET cmd 0x%08x (%s) to 0x%08x\n",
			__func__, cmd, dtv_cmds[cmd].name, data);
	चयन (cmd) अणु
	हाल DTV_CLEAR:
		/*
		 * Reset a cache of data specअगरic to the frontend here. This करोes
		 * not effect hardware.
		 */
		dvb_frontend_clear_cache(fe);
		अवरोध;
	हाल DTV_TUNE:
		/*
		 * Use the cached Digital TV properties to tune the
		 * frontend
		 */
		dev_dbg(fe->dvb->device,
			"%s: Setting the frontend from property cache\n",
			__func__);

		r = dtv_set_frontend(fe);
		अवरोध;
	हाल DTV_FREQUENCY:
		c->frequency = data;
		अवरोध;
	हाल DTV_MODULATION:
		c->modulation = data;
		अवरोध;
	हाल DTV_BANDWIDTH_HZ:
		c->bandwidth_hz = data;
		अवरोध;
	हाल DTV_INVERSION:
		c->inversion = data;
		अवरोध;
	हाल DTV_SYMBOL_RATE:
		c->symbol_rate = data;
		अवरोध;
	हाल DTV_INNER_FEC:
		c->fec_inner = data;
		अवरोध;
	हाल DTV_PILOT:
		c->pilot = data;
		अवरोध;
	हाल DTV_ROLLOFF:
		c->rolloff = data;
		अवरोध;
	हाल DTV_DELIVERY_SYSTEM:
		r = dvbv5_set_delivery_प्रणाली(fe, data);
		अवरोध;
	हाल DTV_VOLTAGE:
		c->voltage = data;
		r = dvb_frontend_handle_ioctl(file, FE_SET_VOLTAGE,
					      (व्योम *)c->voltage);
		अवरोध;
	हाल DTV_TONE:
		c->sectone = data;
		r = dvb_frontend_handle_ioctl(file, FE_SET_TONE,
					      (व्योम *)c->sectone);
		अवरोध;
	हाल DTV_CODE_RATE_HP:
		c->code_rate_HP = data;
		अवरोध;
	हाल DTV_CODE_RATE_LP:
		c->code_rate_LP = data;
		अवरोध;
	हाल DTV_GUARD_INTERVAL:
		c->guard_पूर्णांकerval = data;
		अवरोध;
	हाल DTV_TRANSMISSION_MODE:
		c->transmission_mode = data;
		अवरोध;
	हाल DTV_HIERARCHY:
		c->hierarchy = data;
		अवरोध;
	हाल DTV_INTERLEAVING:
		c->पूर्णांकerleaving = data;
		अवरोध;

	/* ISDB-T Support here */
	हाल DTV_ISDBT_PARTIAL_RECEPTION:
		c->isdbt_partial_reception = data;
		अवरोध;
	हाल DTV_ISDBT_SOUND_BROADCASTING:
		c->isdbt_sb_mode = data;
		अवरोध;
	हाल DTV_ISDBT_SB_SUBCHANNEL_ID:
		c->isdbt_sb_subchannel = data;
		अवरोध;
	हाल DTV_ISDBT_SB_SEGMENT_IDX:
		c->isdbt_sb_segment_idx = data;
		अवरोध;
	हाल DTV_ISDBT_SB_SEGMENT_COUNT:
		c->isdbt_sb_segment_count = data;
		अवरोध;
	हाल DTV_ISDBT_LAYER_ENABLED:
		c->isdbt_layer_enabled = data;
		अवरोध;
	हाल DTV_ISDBT_LAYERA_FEC:
		c->layer[0].fec = data;
		अवरोध;
	हाल DTV_ISDBT_LAYERA_MODULATION:
		c->layer[0].modulation = data;
		अवरोध;
	हाल DTV_ISDBT_LAYERA_SEGMENT_COUNT:
		c->layer[0].segment_count = data;
		अवरोध;
	हाल DTV_ISDBT_LAYERA_TIME_INTERLEAVING:
		c->layer[0].पूर्णांकerleaving = data;
		अवरोध;
	हाल DTV_ISDBT_LAYERB_FEC:
		c->layer[1].fec = data;
		अवरोध;
	हाल DTV_ISDBT_LAYERB_MODULATION:
		c->layer[1].modulation = data;
		अवरोध;
	हाल DTV_ISDBT_LAYERB_SEGMENT_COUNT:
		c->layer[1].segment_count = data;
		अवरोध;
	हाल DTV_ISDBT_LAYERB_TIME_INTERLEAVING:
		c->layer[1].पूर्णांकerleaving = data;
		अवरोध;
	हाल DTV_ISDBT_LAYERC_FEC:
		c->layer[2].fec = data;
		अवरोध;
	हाल DTV_ISDBT_LAYERC_MODULATION:
		c->layer[2].modulation = data;
		अवरोध;
	हाल DTV_ISDBT_LAYERC_SEGMENT_COUNT:
		c->layer[2].segment_count = data;
		अवरोध;
	हाल DTV_ISDBT_LAYERC_TIME_INTERLEAVING:
		c->layer[2].पूर्णांकerleaving = data;
		अवरोध;

	/* Multistream support */
	हाल DTV_STREAM_ID:
	हाल DTV_DVBT2_PLP_ID_LEGACY:
		c->stream_id = data;
		अवरोध;

	/* Physical layer scrambling support */
	हाल DTV_SCRAMBLING_SEQUENCE_INDEX:
		c->scrambling_sequence_index = data;
		अवरोध;

	/* ATSC-MH */
	हाल DTV_ATSCMH_PARADE_ID:
		fe->dtv_property_cache.atscmh_parade_id = data;
		अवरोध;
	हाल DTV_ATSCMH_RS_FRAME_ENSEMBLE:
		fe->dtv_property_cache.atscmh_rs_frame_ensemble = data;
		अवरोध;

	हाल DTV_LNA:
		c->lna = data;
		अगर (fe->ops.set_lna)
			r = fe->ops.set_lna(fe);
		अगर (r < 0)
			c->lna = LNA_AUTO;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस r;
पूर्ण

अटल पूर्णांक dvb_frontend_करो_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				 व्योम *parg)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dvb_frontend *fe = dvbdev->priv;
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	पूर्णांक err;

	dev_dbg(fe->dvb->device, "%s: (%d)\n", __func__, _IOC_NR(cmd));
	अगर (करोwn_पूर्णांकerruptible(&fepriv->sem))
		वापस -ERESTARTSYS;

	अगर (fe->निकास != DVB_FE_NO_EXIT) अणु
		up(&fepriv->sem);
		वापस -ENODEV;
	पूर्ण

	/*
	 * If the frontend is खोलोed in पढ़ो-only mode, only the ioctls
	 * that करोn't पूर्णांकerfere with the tune logic should be accepted.
	 * That allows an बाह्यal application to monitor the DVB QoS and
	 * statistics parameters.
	 *
	 * That matches all _IOR() ioctls, except क्रम two special हालs:
	 *   - FE_GET_EVENT is part of the tuning logic on a DVB application;
	 *   - FE_DISEQC_RECV_SLAVE_REPLY is part of DiSEqC 2.0
	 *     setup
	 * So, those two ioctls should also वापस -EPERM, as otherwise
	 * पढ़ोing from them would पूर्णांकerfere with a DVB tune application
	 */
	अगर ((file->f_flags & O_ACCMODE) == O_RDONLY
	    && (_IOC_सूची(cmd) != _IOC_READ
		|| cmd == FE_GET_EVENT
		|| cmd == FE_DISEQC_RECV_SLAVE_REPLY)) अणु
		up(&fepriv->sem);
		वापस -EPERM;
	पूर्ण

	err = dvb_frontend_handle_ioctl(file, cmd, parg);

	up(&fepriv->sem);
	वापस err;
पूर्ण

अटल दीर्घ dvb_frontend_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
			       अचिन्हित दीर्घ arg)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;

	अगर (!dvbdev)
		वापस -ENODEV;

	वापस dvb_usercopy(file, cmd, arg, dvb_frontend_करो_ioctl);
पूर्ण

#अगर_घोषित CONFIG_COMPAT
काष्ठा compat_dtv_property अणु
	__u32 cmd;
	__u32 reserved[3];
	जोड़ अणु
		__u32 data;
		काष्ठा dtv_fe_stats st;
		काष्ठा अणु
			__u8 data[32];
			__u32 len;
			__u32 reserved1[3];
			compat_uptr_t reserved2;
		पूर्ण buffer;
	पूर्ण u;
	पूर्णांक result;
पूर्ण __attribute__ ((packed));

काष्ठा compat_dtv_properties अणु
	__u32 num;
	compat_uptr_t props;
पूर्ण;

#घोषणा COMPAT_FE_SET_PROPERTY	   _IOW('o', 82, काष्ठा compat_dtv_properties)
#घोषणा COMPAT_FE_GET_PROPERTY	   _IOR('o', 83, काष्ठा compat_dtv_properties)

अटल पूर्णांक dvb_frontend_handle_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
					    अचिन्हित दीर्घ arg)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dvb_frontend *fe = dvbdev->priv;
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	पूर्णांक i, err = 0;

	अगर (cmd == COMPAT_FE_SET_PROPERTY) अणु
		काष्ठा compat_dtv_properties prop, *tvps = शून्य;
		काष्ठा compat_dtv_property *tvp = शून्य;

		अगर (copy_from_user(&prop, compat_ptr(arg), माप(prop)))
			वापस -EFAULT;

		tvps = &prop;

		/*
		 * Put an arbitrary limit on the number of messages that can
		 * be sent at once
		 */
		अगर (!tvps->num || (tvps->num > DTV_IOCTL_MAX_MSGS))
			वापस -EINVAL;

		tvp = memdup_user(compat_ptr(tvps->props), tvps->num * माप(*tvp));
		अगर (IS_ERR(tvp))
			वापस PTR_ERR(tvp);

		क्रम (i = 0; i < tvps->num; i++) अणु
			err = dtv_property_process_set(fe, file,
						       (tvp + i)->cmd,
						       (tvp + i)->u.data);
			अगर (err < 0) अणु
				kमुक्त(tvp);
				वापस err;
			पूर्ण
		पूर्ण
		kमुक्त(tvp);
	पूर्ण अन्यथा अगर (cmd == COMPAT_FE_GET_PROPERTY) अणु
		काष्ठा compat_dtv_properties prop, *tvps = शून्य;
		काष्ठा compat_dtv_property *tvp = शून्य;
		काष्ठा dtv_frontend_properties getp = fe->dtv_property_cache;

		अगर (copy_from_user(&prop, compat_ptr(arg), माप(prop)))
			वापस -EFAULT;

		tvps = &prop;

		/*
		 * Put an arbitrary limit on the number of messages that can
		 * be sent at once
		 */
		अगर (!tvps->num || (tvps->num > DTV_IOCTL_MAX_MSGS))
			वापस -EINVAL;

		tvp = memdup_user(compat_ptr(tvps->props), tvps->num * माप(*tvp));
		अगर (IS_ERR(tvp))
			वापस PTR_ERR(tvp);

		/*
		 * Let's use our own copy of property cache, in order to
		 * aव्योम mangling with DTV zigzag logic, as drivers might
		 * वापस crap, अगर they करोn't check अगर the data is available
		 * beक्रमe updating the properties cache.
		 */
		अगर (fepriv->state != FESTATE_IDLE) अणु
			err = dtv_get_frontend(fe, &getp, शून्य);
			अगर (err < 0) अणु
				kमुक्त(tvp);
				वापस err;
			पूर्ण
		पूर्ण
		क्रम (i = 0; i < tvps->num; i++) अणु
			err = dtv_property_process_get(
			    fe, &getp, (काष्ठा dtv_property *)(tvp + i), file);
			अगर (err < 0) अणु
				kमुक्त(tvp);
				वापस err;
			पूर्ण
		पूर्ण

		अगर (copy_to_user((व्योम __user *)compat_ptr(tvps->props), tvp,
				 tvps->num * माप(काष्ठा compat_dtv_property))) अणु
			kमुक्त(tvp);
			वापस -EFAULT;
		पूर्ण
		kमुक्त(tvp);
	पूर्ण

	वापस err;
पूर्ण

अटल दीर्घ dvb_frontend_compat_ioctl(काष्ठा file *file, अचिन्हित पूर्णांक cmd,
				      अचिन्हित दीर्घ arg)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dvb_frontend *fe = dvbdev->priv;
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	पूर्णांक err;

	अगर (cmd == COMPAT_FE_SET_PROPERTY || cmd == COMPAT_FE_GET_PROPERTY) अणु
		अगर (करोwn_पूर्णांकerruptible(&fepriv->sem))
			वापस -ERESTARTSYS;

		err = dvb_frontend_handle_compat_ioctl(file, cmd, arg);

		up(&fepriv->sem);
		वापस err;
	पूर्ण

	वापस dvb_frontend_ioctl(file, cmd, (अचिन्हित दीर्घ)compat_ptr(arg));
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक dtv_set_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 rolloff = 0;

	अगर (dvb_frontend_check_parameters(fe) < 0)
		वापस -EINVAL;

	/*
	 * Initialize output parameters to match the values given by
	 * the user. FE_SET_FRONTEND triggers an initial frontend event
	 * with status = 0, which copies output parameters to userspace.
	 */
	dtv_property_legacy_params_sync(fe, c, &fepriv->parameters_out);

	/*
	 * Be sure that the bandwidth will be filled क्रम all
	 * non-satellite प्रणालीs, as tuners need to know what
	 * low pass/Nyquist half filter should be applied, in
	 * order to aव्योम पूर्णांकer-channel noise.
	 *
	 * ISDB-T and DVB-T/T2 alपढ़ोy sets bandwidth.
	 * ATSC and DVB-C करोn't set, so, the core should fill it.
	 *
	 * On DVB-C Annex A and C, the bandwidth is a function of
	 * the roll-off and symbol rate. Annex B defines dअगरferent
	 * roll-off factors depending on the modulation. Fortunately,
	 * Annex B is only used with 6MHz, so there's no need to
	 * calculate it.
	 *
	 * While not officially supported, a side effect of handling it at
	 * the cache level is that a program could retrieve the bandwidth
	 * via DTV_BANDWIDTH_HZ, which may be useful क्रम test programs.
	 */
	चयन (c->delivery_प्रणाली) अणु
	हाल SYS_ATSC:
	हाल SYS_DVBC_ANNEX_B:
		c->bandwidth_hz = 6000000;
		अवरोध;
	हाल SYS_DVBC_ANNEX_A:
		rolloff = 115;
		अवरोध;
	हाल SYS_DVBC_ANNEX_C:
		rolloff = 113;
		अवरोध;
	हाल SYS_DVBS:
	हाल SYS_TURBO:
	हाल SYS_ISDBS:
		rolloff = 135;
		अवरोध;
	हाल SYS_DVBS2:
		चयन (c->rolloff) अणु
		हाल ROLLOFF_20:
			rolloff = 120;
			अवरोध;
		हाल ROLLOFF_25:
			rolloff = 125;
			अवरोध;
		शेष:
		हाल ROLLOFF_35:
			rolloff = 135;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (rolloff)
		c->bandwidth_hz = mult_frac(c->symbol_rate, rolloff, 100);

	/* क्रमce स्वतः frequency inversion अगर requested */
	अगर (dvb_क्रमce_स्वतः_inversion)
		c->inversion = INVERSION_AUTO;

	/*
	 * without hierarchical coding code_rate_LP is irrelevant,
	 * so we tolerate the otherwise invalid FEC_NONE setting
	 */
	अगर (c->hierarchy == HIERARCHY_NONE && c->code_rate_LP == FEC_NONE)
		c->code_rate_LP = FEC_AUTO;

	prepare_tuning_algo_parameters(fe);

	fepriv->state = FESTATE_RETUNE;

	/* Request the search algorithm to search */
	fepriv->algo_status |= DVBFE_ALGO_SEARCH_AGAIN;

	dvb_frontend_clear_events(fe);
	dvb_frontend_add_event(fe, 0);
	dvb_frontend_wakeup(fe);
	fepriv->status = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_get_property(काष्ठा dvb_frontend *fe, काष्ठा file *file,
			    काष्ठा dtv_properties *tvps)
अणु
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	काष्ठा dtv_property *tvp = शून्य;
	काष्ठा dtv_frontend_properties getp;
	पूर्णांक i, err;

	स_नकल(&getp, &fe->dtv_property_cache, माप(getp));

	dev_dbg(fe->dvb->device, "%s: properties.num = %d\n",
		__func__, tvps->num);
	dev_dbg(fe->dvb->device, "%s: properties.props = %p\n",
		__func__, tvps->props);

	/*
	 * Put an arbitrary limit on the number of messages that can
	 * be sent at once
	 */
	अगर (!tvps->num || tvps->num > DTV_IOCTL_MAX_MSGS)
		वापस -EINVAL;

	tvp = memdup_user((व्योम __user *)tvps->props, tvps->num * माप(*tvp));
	अगर (IS_ERR(tvp))
		वापस PTR_ERR(tvp);

	/*
	 * Let's use our own copy of property cache, in order to
	 * aव्योम mangling with DTV zigzag logic, as drivers might
	 * वापस crap, अगर they करोn't check अगर the data is available
	 * beक्रमe updating the properties cache.
	 */
	अगर (fepriv->state != FESTATE_IDLE) अणु
		err = dtv_get_frontend(fe, &getp, शून्य);
		अगर (err < 0)
			जाओ out;
	पूर्ण
	क्रम (i = 0; i < tvps->num; i++) अणु
		err = dtv_property_process_get(fe, &getp,
					       tvp + i, file);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	अगर (copy_to_user((व्योम __user *)tvps->props, tvp,
			 tvps->num * माप(काष्ठा dtv_property))) अणु
		err = -EFAULT;
		जाओ out;
	पूर्ण

	err = 0;
out:
	kमुक्त(tvp);
	वापस err;
पूर्ण

अटल पूर्णांक dvb_get_frontend(काष्ठा dvb_frontend *fe,
			    काष्ठा dvb_frontend_parameters *p_out)
अणु
	काष्ठा dtv_frontend_properties getp;

	/*
	 * Let's use our own copy of property cache, in order to
	 * aव्योम mangling with DTV zigzag logic, as drivers might
	 * वापस crap, अगर they करोn't check अगर the data is available
	 * beक्रमe updating the properties cache.
	 */
	स_नकल(&getp, &fe->dtv_property_cache, माप(getp));

	वापस dtv_get_frontend(fe, &getp, p_out);
पूर्ण

अटल पूर्णांक dvb_frontend_handle_ioctl(काष्ठा file *file,
				     अचिन्हित पूर्णांक cmd, व्योम *parg)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dvb_frontend *fe = dvbdev->priv;
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	काष्ठा dtv_frontend_properties *c = &fe->dtv_property_cache;
	पूर्णांक i, err = -ENOTSUPP;

	dev_dbg(fe->dvb->device, "%s:\n", __func__);

	चयन (cmd) अणु
	हाल FE_SET_PROPERTY: अणु
		काष्ठा dtv_properties *tvps = parg;
		काष्ठा dtv_property *tvp = शून्य;

		dev_dbg(fe->dvb->device, "%s: properties.num = %d\n",
			__func__, tvps->num);
		dev_dbg(fe->dvb->device, "%s: properties.props = %p\n",
			__func__, tvps->props);

		/*
		 * Put an arbitrary limit on the number of messages that can
		 * be sent at once
		 */
		अगर (!tvps->num || (tvps->num > DTV_IOCTL_MAX_MSGS))
			वापस -EINVAL;

		tvp = memdup_user((व्योम __user *)tvps->props, tvps->num * माप(*tvp));
		अगर (IS_ERR(tvp))
			वापस PTR_ERR(tvp);

		क्रम (i = 0; i < tvps->num; i++) अणु
			err = dtv_property_process_set(fe, file,
						       (tvp + i)->cmd,
						       (tvp + i)->u.data);
			अगर (err < 0) अणु
				kमुक्त(tvp);
				वापस err;
			पूर्ण
		पूर्ण
		kमुक्त(tvp);
		err = 0;
		अवरोध;
	पूर्ण
	हाल FE_GET_PROPERTY:
		err = dvb_get_property(fe, file, parg);
		अवरोध;

	हाल FE_GET_INFO: अणु
		काष्ठा dvb_frontend_info *info = parg;
		स_रखो(info, 0, माप(*info));

		strscpy(info->name, fe->ops.info.name, माप(info->name));
		info->symbol_rate_min = fe->ops.info.symbol_rate_min;
		info->symbol_rate_max = fe->ops.info.symbol_rate_max;
		info->symbol_rate_tolerance = fe->ops.info.symbol_rate_tolerance;
		info->caps = fe->ops.info.caps;
		info->frequency_stepsize = dvb_frontend_get_stepsize(fe);
		dvb_frontend_get_frequency_limits(fe, &info->frequency_min,
						  &info->frequency_max,
						  &info->frequency_tolerance);

		/*
		 * Associate the 4 delivery प्रणालीs supported by DVBv3
		 * API with their DVBv5 counterpart. For the other standards,
		 * use the बंदst type, assuming that it would hopefully
		 * work with a DVBv3 application.
		 * It should be noticed that, on multi-frontend devices with
		 * dअगरferent types (terrestrial and cable, क्रम example),
		 * a pure DVBv3 application won't be able to use all delivery
		 * प्रणालीs. Yet, changing the DVBv5 cache to the other delivery
		 * प्रणाली should be enough क्रम making it work.
		 */
		चयन (dvbv3_type(c->delivery_प्रणाली)) अणु
		हाल DVBV3_QPSK:
			info->type = FE_QPSK;
			अवरोध;
		हाल DVBV3_ATSC:
			info->type = FE_ATSC;
			अवरोध;
		हाल DVBV3_QAM:
			info->type = FE_QAM;
			अवरोध;
		हाल DVBV3_OFDM:
			info->type = FE_OFDM;
			अवरोध;
		शेष:
			dev_err(fe->dvb->device,
				"%s: doesn't know how to handle a DVBv3 call to delivery system %i\n",
				__func__, c->delivery_प्रणाली);
			info->type = FE_OFDM;
		पूर्ण
		dev_dbg(fe->dvb->device, "%s: current delivery system on cache: %d, V3 type: %d\n",
			__func__, c->delivery_प्रणाली, info->type);

		/* Set CAN_INVERSION_AUTO bit on in other than oneshot mode */
		अगर (!(fepriv->tune_mode_flags & FE_TUNE_MODE_ONESHOT))
			info->caps |= FE_CAN_INVERSION_AUTO;
		err = 0;
		अवरोध;
	पूर्ण

	हाल FE_READ_STATUS: अणु
		क्रमागत fe_status *status = parg;

		/* अगर retune was requested but hasn't occurred yet, prevent
		 * that user get संकेत state from previous tuning */
		अगर (fepriv->state == FESTATE_RETUNE ||
		    fepriv->state == FESTATE_ERROR) अणु
			err = 0;
			*status = 0;
			अवरोध;
		पूर्ण

		अगर (fe->ops.पढ़ो_status)
			err = fe->ops.पढ़ो_status(fe, status);
		अवरोध;
	पूर्ण

	हाल FE_DISEQC_RESET_OVERLOAD:
		अगर (fe->ops.diseqc_reset_overload) अणु
			err = fe->ops.diseqc_reset_overload(fe);
			fepriv->state = FESTATE_DISEQC;
			fepriv->status = 0;
		पूर्ण
		अवरोध;

	हाल FE_DISEQC_SEND_MASTER_CMD:
		अगर (fe->ops.diseqc_send_master_cmd) अणु
			काष्ठा dvb_diseqc_master_cmd *cmd = parg;

			अगर (cmd->msg_len > माप(cmd->msg)) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			err = fe->ops.diseqc_send_master_cmd(fe, cmd);
			fepriv->state = FESTATE_DISEQC;
			fepriv->status = 0;
		पूर्ण
		अवरोध;

	हाल FE_DISEQC_SEND_BURST:
		अगर (fe->ops.diseqc_send_burst) अणु
			err = fe->ops.diseqc_send_burst(fe,
						(क्रमागत fe_sec_mini_cmd)parg);
			fepriv->state = FESTATE_DISEQC;
			fepriv->status = 0;
		पूर्ण
		अवरोध;

	हाल FE_SET_TONE:
		अगर (fe->ops.set_tone) अणु
			err = fe->ops.set_tone(fe,
					       (क्रमागत fe_sec_tone_mode)parg);
			fepriv->tone = (क्रमागत fe_sec_tone_mode)parg;
			fepriv->state = FESTATE_DISEQC;
			fepriv->status = 0;
		पूर्ण
		अवरोध;

	हाल FE_SET_VOLTAGE:
		अगर (fe->ops.set_voltage) अणु
			err = fe->ops.set_voltage(fe,
						  (क्रमागत fe_sec_voltage)parg);
			fepriv->voltage = (क्रमागत fe_sec_voltage)parg;
			fepriv->state = FESTATE_DISEQC;
			fepriv->status = 0;
		पूर्ण
		अवरोध;

	हाल FE_DISEQC_RECV_SLAVE_REPLY:
		अगर (fe->ops.diseqc_recv_slave_reply)
			err = fe->ops.diseqc_recv_slave_reply(fe, parg);
		अवरोध;

	हाल FE_ENABLE_HIGH_LNB_VOLTAGE:
		अगर (fe->ops.enable_high_lnb_voltage)
			err = fe->ops.enable_high_lnb_voltage(fe, (दीर्घ)parg);
		अवरोध;

	हाल FE_SET_FRONTEND_TUNE_MODE:
		fepriv->tune_mode_flags = (अचिन्हित दीर्घ)parg;
		err = 0;
		अवरोध;
	/* DEPRECATED dish control ioctls */

	हाल FE_DISHNETWORK_SEND_LEGACY_CMD:
		अगर (fe->ops.dishnetwork_send_legacy_command) अणु
			err = fe->ops.dishnetwork_send_legacy_command(fe,
							 (अचिन्हित दीर्घ)parg);
			fepriv->state = FESTATE_DISEQC;
			fepriv->status = 0;
		पूर्ण अन्यथा अगर (fe->ops.set_voltage) अणु
			/*
			 * NOTE: This is a fallback condition.  Some frontends
			 * (stv0299 क्रम instance) take दीर्घer than 8msec to
			 * respond to a set_voltage command.  Those चयनes
			 * need custom routines to चयन properly.  For all
			 * other frontends, the following should work ok.
			 * Dish network legacy चयनes (as used by Dish500)
			 * are controlled by sending 9-bit command words
			 * spaced 8msec apart.
			 * the actual command word is चयन/port dependent
			 * so it is up to the userspace application to send
			 * the right command.
			 * The command must always start with a '0' after
			 * initialization, so parg is 8 bits and करोes not
			 * include the initialization or start bit
			 */
			अचिन्हित दीर्घ swcmd = ((अचिन्हित दीर्घ)parg) << 1;
			kसमय_प्रकार nextसमय;
			kसमय_प्रकार tv[10];
			पूर्णांक i;
			u8 last = 1;

			अगर (dvb_frontend_debug)
				dprपूर्णांकk("switch command: 0x%04lx\n",
					swcmd);
			nextसमय = kसमय_get_bootसमय();
			अगर (dvb_frontend_debug)
				tv[0] = nextसमय;
			/* beक्रमe sending a command, initialize by sending
			 * a 32ms 18V to the चयन
			 */
			fe->ops.set_voltage(fe, SEC_VOLTAGE_18);
			dvb_frontend_sleep_until(&nextसमय, 32000);

			क्रम (i = 0; i < 9; i++) अणु
				अगर (dvb_frontend_debug)
					tv[i + 1] = kसमय_get_bootसमय();
				अगर ((swcmd & 0x01) != last) अणु
					/* set voltage to (last ? 13V : 18V) */
					fe->ops.set_voltage(fe, (last) ? SEC_VOLTAGE_13 : SEC_VOLTAGE_18);
					last = (last) ? 0 : 1;
				पूर्ण
				swcmd = swcmd >> 1;
				अगर (i != 8)
					dvb_frontend_sleep_until(&nextसमय, 8000);
			पूर्ण
			अगर (dvb_frontend_debug) अणु
				dprपूर्णांकk("(adapter %d): switch delay (should be 32k followed by all 8k)\n",
					fe->dvb->num);
				क्रम (i = 1; i < 10; i++)
					pr_info("%d: %d\n", i,
						(पूर्णांक)kसमय_us_delta(tv[i], tv[i - 1]));
			पूर्ण
			err = 0;
			fepriv->state = FESTATE_DISEQC;
			fepriv->status = 0;
		पूर्ण
		अवरोध;

	/* DEPRECATED statistics ioctls */

	हाल FE_READ_BER:
		अगर (fe->ops.पढ़ो_ber) अणु
			अगर (fepriv->thपढ़ो)
				err = fe->ops.पढ़ो_ber(fe, parg);
			अन्यथा
				err = -EAGAIN;
		पूर्ण
		अवरोध;

	हाल FE_READ_SIGNAL_STRENGTH:
		अगर (fe->ops.पढ़ो_संकेत_strength) अणु
			अगर (fepriv->thपढ़ो)
				err = fe->ops.पढ़ो_संकेत_strength(fe, parg);
			अन्यथा
				err = -EAGAIN;
		पूर्ण
		अवरोध;

	हाल FE_READ_SNR:
		अगर (fe->ops.पढ़ो_snr) अणु
			अगर (fepriv->thपढ़ो)
				err = fe->ops.पढ़ो_snr(fe, parg);
			अन्यथा
				err = -EAGAIN;
		पूर्ण
		अवरोध;

	हाल FE_READ_UNCORRECTED_BLOCKS:
		अगर (fe->ops.पढ़ो_ucblocks) अणु
			अगर (fepriv->thपढ़ो)
				err = fe->ops.पढ़ो_ucblocks(fe, parg);
			अन्यथा
				err = -EAGAIN;
		पूर्ण
		अवरोध;

	/* DEPRECATED DVBv3 ioctls */

	हाल FE_SET_FRONTEND:
		err = dvbv3_set_delivery_प्रणाली(fe);
		अगर (err)
			अवरोध;

		err = dtv_property_cache_sync(fe, c, parg);
		अगर (err)
			अवरोध;
		err = dtv_set_frontend(fe);
		अवरोध;

	हाल FE_GET_EVENT:
		err = dvb_frontend_get_event(fe, parg, file->f_flags);
		अवरोध;

	हाल FE_GET_FRONTEND:
		err = dvb_get_frontend(fe, parg);
		अवरोध;

	शेष:
		वापस -ENOTSUPP;
	पूर्ण /* चयन */

	वापस err;
पूर्ण

अटल __poll_t dvb_frontend_poll(काष्ठा file *file, काष्ठा poll_table_काष्ठा *रुको)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dvb_frontend *fe = dvbdev->priv;
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;

	dev_dbg_ratelimited(fe->dvb->device, "%s:\n", __func__);

	poll_रुको(file, &fepriv->events.रुको_queue, रुको);

	अगर (fepriv->events.eventw != fepriv->events.eventr)
		वापस (EPOLLIN | EPOLLRDNORM | EPOLLPRI);

	वापस 0;
पूर्ण

अटल पूर्णांक dvb_frontend_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dvb_frontend *fe = dvbdev->priv;
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	काष्ठा dvb_adapter *adapter = fe->dvb;
	पूर्णांक ret;

	dev_dbg(fe->dvb->device, "%s:\n", __func__);
	अगर (fe->निकास == DVB_FE_DEVICE_REMOVED)
		वापस -ENODEV;

	अगर (adapter->mfe_shared) अणु
		mutex_lock(&adapter->mfe_lock);

		अगर (!adapter->mfe_dvbdev)
			adapter->mfe_dvbdev = dvbdev;

		अन्यथा अगर (adapter->mfe_dvbdev != dvbdev) अणु
			काष्ठा dvb_device
				*mfedev = adapter->mfe_dvbdev;
			काष्ठा dvb_frontend
				*mfe = mfedev->priv;
			काष्ठा dvb_frontend_निजी
				*mfepriv = mfe->frontend_priv;
			पूर्णांक mferetry = (dvb_mfe_रुको_समय << 1);

			mutex_unlock(&adapter->mfe_lock);
			जबतक (mferetry-- && (mfedev->users != -1 ||
					      mfepriv->thपढ़ो)) अणु
				अगर (msleep_पूर्णांकerruptible(500)) अणु
					अगर (संकेत_pending(current))
						वापस -EINTR;
				पूर्ण
			पूर्ण

			mutex_lock(&adapter->mfe_lock);
			अगर (adapter->mfe_dvbdev != dvbdev) अणु
				mfedev = adapter->mfe_dvbdev;
				mfe = mfedev->priv;
				mfepriv = mfe->frontend_priv;
				अगर (mfedev->users != -1 ||
				    mfepriv->thपढ़ो) अणु
					mutex_unlock(&adapter->mfe_lock);
					वापस -EBUSY;
				पूर्ण
				adapter->mfe_dvbdev = dvbdev;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (dvbdev->users == -1 && fe->ops.ts_bus_ctrl) अणु
		अगर ((ret = fe->ops.ts_bus_ctrl(fe, 1)) < 0)
			जाओ err0;

		/* If we took control of the bus, we need to क्रमce
		   reinitialization.  This is because many ts_bus_ctrl()
		   functions strobe the RESET pin on the demod, and अगर the
		   frontend thपढ़ो alपढ़ोy exists then the dvb_init() routine
		   won't get called (which is what usually करोes initial
		   रेजिस्टर configuration). */
		fepriv->reinitialise = 1;
	पूर्ण

	अगर ((ret = dvb_generic_खोलो(inode, file)) < 0)
		जाओ err1;

	अगर ((file->f_flags & O_ACCMODE) != O_RDONLY) अणु
		/* normal tune mode when खोलोed R/W */
		fepriv->tune_mode_flags &= ~FE_TUNE_MODE_ONESHOT;
		fepriv->tone = -1;
		fepriv->voltage = -1;

#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
		mutex_lock(&fe->dvb->mdev_lock);
		अगर (fe->dvb->mdev) अणु
			mutex_lock(&fe->dvb->mdev->graph_mutex);
			अगर (fe->dvb->mdev->enable_source)
				ret = fe->dvb->mdev->enable_source(
							   dvbdev->entity,
							   &fepriv->pipe);
			mutex_unlock(&fe->dvb->mdev->graph_mutex);
			अगर (ret) अणु
				mutex_unlock(&fe->dvb->mdev_lock);
				dev_err(fe->dvb->device,
					"Tuner is busy. Error %d\n", ret);
				जाओ err2;
			पूर्ण
		पूर्ण
		mutex_unlock(&fe->dvb->mdev_lock);
#पूर्ण_अगर
		ret = dvb_frontend_start(fe);
		अगर (ret)
			जाओ err3;

		/*  empty event queue */
		fepriv->events.eventr = fepriv->events.eventw = 0;
	पूर्ण

	dvb_frontend_get(fe);

	अगर (adapter->mfe_shared)
		mutex_unlock(&adapter->mfe_lock);
	वापस ret;

err3:
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
	mutex_lock(&fe->dvb->mdev_lock);
	अगर (fe->dvb->mdev) अणु
		mutex_lock(&fe->dvb->mdev->graph_mutex);
		अगर (fe->dvb->mdev->disable_source)
			fe->dvb->mdev->disable_source(dvbdev->entity);
		mutex_unlock(&fe->dvb->mdev->graph_mutex);
	पूर्ण
	mutex_unlock(&fe->dvb->mdev_lock);
err2:
#पूर्ण_अगर
	dvb_generic_release(inode, file);
err1:
	अगर (dvbdev->users == -1 && fe->ops.ts_bus_ctrl)
		fe->ops.ts_bus_ctrl(fe, 0);
err0:
	अगर (adapter->mfe_shared)
		mutex_unlock(&adapter->mfe_lock);
	वापस ret;
पूर्ण

अटल पूर्णांक dvb_frontend_release(काष्ठा inode *inode, काष्ठा file *file)
अणु
	काष्ठा dvb_device *dvbdev = file->निजी_data;
	काष्ठा dvb_frontend *fe = dvbdev->priv;
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	पूर्णांक ret;

	dev_dbg(fe->dvb->device, "%s:\n", __func__);

	अगर ((file->f_flags & O_ACCMODE) != O_RDONLY) अणु
		fepriv->release_jअगरfies = jअगरfies;
		mb();
	पूर्ण

	ret = dvb_generic_release(inode, file);

	अगर (dvbdev->users == -1) अणु
		wake_up(&fepriv->रुको_queue);
#अगर_घोषित CONFIG_MEDIA_CONTROLLER_DVB
		mutex_lock(&fe->dvb->mdev_lock);
		अगर (fe->dvb->mdev) अणु
			mutex_lock(&fe->dvb->mdev->graph_mutex);
			अगर (fe->dvb->mdev->disable_source)
				fe->dvb->mdev->disable_source(dvbdev->entity);
			mutex_unlock(&fe->dvb->mdev->graph_mutex);
		पूर्ण
		mutex_unlock(&fe->dvb->mdev_lock);
#पूर्ण_अगर
		अगर (fe->निकास != DVB_FE_NO_EXIT)
			wake_up(&dvbdev->रुको_queue);
		अगर (fe->ops.ts_bus_ctrl)
			fe->ops.ts_bus_ctrl(fe, 0);
	पूर्ण

	dvb_frontend_put(fe);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा file_operations dvb_frontend_fops = अणु
	.owner		= THIS_MODULE,
	.unlocked_ioctl	= dvb_frontend_ioctl,
#अगर_घोषित CONFIG_COMPAT
	.compat_ioctl	= dvb_frontend_compat_ioctl,
#पूर्ण_अगर
	.poll		= dvb_frontend_poll,
	.खोलो		= dvb_frontend_खोलो,
	.release	= dvb_frontend_release,
	.llseek		= noop_llseek,
पूर्ण;

पूर्णांक dvb_frontend_suspend(काष्ठा dvb_frontend *fe)
अणु
	पूर्णांक ret = 0;

	dev_dbg(fe->dvb->device, "%s: adap=%d fe=%d\n", __func__, fe->dvb->num,
		fe->id);

	अगर (fe->ops.tuner_ops.suspend)
		ret = fe->ops.tuner_ops.suspend(fe);
	अन्यथा अगर (fe->ops.tuner_ops.sleep)
		ret = fe->ops.tuner_ops.sleep(fe);

	अगर (fe->ops.sleep)
		ret = fe->ops.sleep(fe);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dvb_frontend_suspend);

पूर्णांक dvb_frontend_resume(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;
	पूर्णांक ret = 0;

	dev_dbg(fe->dvb->device, "%s: adap=%d fe=%d\n", __func__, fe->dvb->num,
		fe->id);

	fe->निकास = DVB_FE_DEVICE_RESUME;
	अगर (fe->ops.init)
		ret = fe->ops.init(fe);

	अगर (fe->ops.tuner_ops.resume)
		ret = fe->ops.tuner_ops.resume(fe);
	अन्यथा अगर (fe->ops.tuner_ops.init)
		ret = fe->ops.tuner_ops.init(fe);

	अगर (fe->ops.set_tone && fepriv->tone != -1)
		fe->ops.set_tone(fe, fepriv->tone);
	अगर (fe->ops.set_voltage && fepriv->voltage != -1)
		fe->ops.set_voltage(fe, fepriv->voltage);

	fe->निकास = DVB_FE_NO_EXIT;
	fepriv->state = FESTATE_RETUNE;
	dvb_frontend_wakeup(fe);

	वापस ret;
पूर्ण
EXPORT_SYMBOL(dvb_frontend_resume);

पूर्णांक dvb_रेजिस्टर_frontend(काष्ठा dvb_adapter *dvb,
			  काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_frontend_निजी *fepriv;
	स्थिर काष्ठा dvb_device dvbdev_ढाँचा = अणु
		.users = ~0,
		.ग_लिखोrs = 1,
		.पढ़ोers = (~0) - 1,
		.fops = &dvb_frontend_fops,
#अगर defined(CONFIG_MEDIA_CONTROLLER_DVB)
		.name = fe->ops.info.name,
#पूर्ण_अगर
	पूर्ण;

	dev_dbg(dvb->device, "%s:\n", __func__);

	अगर (mutex_lock_पूर्णांकerruptible(&frontend_mutex))
		वापस -ERESTARTSYS;

	fe->frontend_priv = kzalloc(माप(काष्ठा dvb_frontend_निजी), GFP_KERNEL);
	अगर (!fe->frontend_priv) अणु
		mutex_unlock(&frontend_mutex);
		वापस -ENOMEM;
	पूर्ण
	fepriv = fe->frontend_priv;

	kref_init(&fe->refcount);

	/*
	 * After initialization, there need to be two references: one
	 * क्रम dvb_unरेजिस्टर_frontend(), and another one क्रम
	 * dvb_frontend_detach().
	 */
	dvb_frontend_get(fe);

	sema_init(&fepriv->sem, 1);
	init_रुकोqueue_head(&fepriv->रुको_queue);
	init_रुकोqueue_head(&fepriv->events.रुको_queue);
	mutex_init(&fepriv->events.mtx);
	fe->dvb = dvb;
	fepriv->inversion = INVERSION_OFF;

	dev_info(fe->dvb->device,
		 "DVB: registering adapter %i frontend %i (%s)...\n",
		 fe->dvb->num, fe->id, fe->ops.info.name);

	dvb_रेजिस्टर_device(fe->dvb, &fepriv->dvbdev, &dvbdev_ढाँचा,
			    fe, DVB_DEVICE_FRONTEND, 0);

	/*
	 * Initialize the cache to the proper values according with the
	 * first supported delivery प्रणाली (ops->delsys[0])
	 */

	fe->dtv_property_cache.delivery_प्रणाली = fe->ops.delsys[0];
	dvb_frontend_clear_cache(fe);

	mutex_unlock(&frontend_mutex);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dvb_रेजिस्टर_frontend);

पूर्णांक dvb_unरेजिस्टर_frontend(काष्ठा dvb_frontend *fe)
अणु
	काष्ठा dvb_frontend_निजी *fepriv = fe->frontend_priv;

	dev_dbg(fe->dvb->device, "%s:\n", __func__);

	mutex_lock(&frontend_mutex);
	dvb_frontend_stop(fe);
	dvb_हटाओ_device(fepriv->dvbdev);

	/* fe is invalid now */
	mutex_unlock(&frontend_mutex);
	dvb_frontend_put(fe);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(dvb_unरेजिस्टर_frontend);

अटल व्योम dvb_frontend_invoke_release(काष्ठा dvb_frontend *fe,
					व्योम (*release)(काष्ठा dvb_frontend *fe))
अणु
	अगर (release) अणु
		release(fe);
#अगर_घोषित CONFIG_MEDIA_ATTACH
		dvb_detach(release);
#पूर्ण_अगर
	पूर्ण
पूर्ण

व्योम dvb_frontend_detach(काष्ठा dvb_frontend *fe)
अणु
	dvb_frontend_invoke_release(fe, fe->ops.release_sec);
	dvb_frontend_invoke_release(fe, fe->ops.tuner_ops.release);
	dvb_frontend_invoke_release(fe, fe->ops.analog_ops.release);
	dvb_frontend_put(fe);
पूर्ण
EXPORT_SYMBOL(dvb_frontend_detach);
