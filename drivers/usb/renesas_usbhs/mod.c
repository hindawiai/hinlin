<शैली गुरु>
// SPDX-License-Identअगरier: GPL-1.0+
/*
 * Renesas USB driver
 *
 * Copyright (C) 2011 Renesas Solutions Corp.
 * Copyright (C) 2019 Renesas Electronics Corporation
 * Kuninori Morimoto <kuninori.morimoto.gx@renesas.com>
 */
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "common.h"
#समावेश "mod.h"

/*
 *		स्वतःnomy
 *
 * these functions are used अगर platक्रमm करोesn't have बाह्यal phy.
 *  -> there is no "notify_hotplug" callback from platक्रमm
 *  -> call "notify_hotplug" by itself
 *  -> use own पूर्णांकerrupt to connect/disconnect
 *  -> it mean module घड़ी is always ON
 *             ~~~~~~~~~~~~~~~~~~~~~~~~~
 */
अटल पूर्णांक usbhsm_स्वतःnomy_get_vbus(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा usbhs_priv *priv = usbhs_pdev_to_priv(pdev);

	वापस  VBSTS & usbhs_पढ़ो(priv, INTSTS0);
पूर्ण

अटल पूर्णांक usbhsm_स्वतःnomy_irq_vbus(काष्ठा usbhs_priv *priv,
				    काष्ठा usbhs_irq_state *irq_state)
अणु
	काष्ठा platक्रमm_device *pdev = usbhs_priv_to_pdev(priv);

	usbhsc_schedule_notअगरy_hotplug(pdev);

	वापस 0;
पूर्ण

व्योम usbhs_mod_स्वतःnomy_mode(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhs_mod_info *info = usbhs_priv_to_modinfo(priv);

	info->irq_vbus = usbhsm_स्वतःnomy_irq_vbus;
	info->get_vbus = usbhsm_स्वतःnomy_get_vbus;

	usbhs_irq_callback_update(priv, शून्य);
पूर्ण

व्योम usbhs_mod_non_स्वतःnomy_mode(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhs_mod_info *info = usbhs_priv_to_modinfo(priv);

	info->get_vbus = priv->pfunc->get_vbus;
पूर्ण

/*
 *		host / gadget functions
 *
 * renesas_usbhs host/gadget can रेजिस्टर itself by below functions.
 * these functions are called when probe
 *
 */
व्योम usbhs_mod_रेजिस्टर(काष्ठा usbhs_priv *priv, काष्ठा usbhs_mod *mod, पूर्णांक id)
अणु
	काष्ठा usbhs_mod_info *info = usbhs_priv_to_modinfo(priv);

	info->mod[id]	= mod;
	mod->priv	= priv;
पूर्ण

काष्ठा usbhs_mod *usbhs_mod_get(काष्ठा usbhs_priv *priv, पूर्णांक id)
अणु
	काष्ठा usbhs_mod_info *info = usbhs_priv_to_modinfo(priv);
	काष्ठा usbhs_mod *ret = शून्य;

	चयन (id) अणु
	हाल USBHS_HOST:
	हाल USBHS_GADGET:
		ret = info->mod[id];
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

पूर्णांक usbhs_mod_is_host(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhs_mod *mod = usbhs_mod_get_current(priv);
	काष्ठा usbhs_mod_info *info = usbhs_priv_to_modinfo(priv);

	अगर (!mod)
		वापस -EINVAL;

	वापस info->mod[USBHS_HOST] == mod;
पूर्ण

काष्ठा usbhs_mod *usbhs_mod_get_current(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा usbhs_mod_info *info = usbhs_priv_to_modinfo(priv);

	वापस info->curt;
पूर्ण

पूर्णांक usbhs_mod_change(काष्ठा usbhs_priv *priv, पूर्णांक id)
अणु
	काष्ठा usbhs_mod_info *info = usbhs_priv_to_modinfo(priv);
	काष्ठा usbhs_mod *mod = शून्य;
	पूर्णांक ret = 0;

	/* id < 0 mean no current */
	चयन (id) अणु
	हाल USBHS_HOST:
	हाल USBHS_GADGET:
		mod = info->mod[id];
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण
	info->curt = mod;

	वापस ret;
पूर्ण

अटल irqवापस_t usbhs_पूर्णांकerrupt(पूर्णांक irq, व्योम *data);
पूर्णांक usbhs_mod_probe(काष्ठा usbhs_priv *priv)
अणु
	काष्ठा device *dev = usbhs_priv_to_dev(priv);
	पूर्णांक ret;

	/*
	 * install host/gadget driver
	 */
	ret = usbhs_mod_host_probe(priv);
	अगर (ret < 0)
		वापस ret;

	ret = usbhs_mod_gadget_probe(priv);
	अगर (ret < 0)
		जाओ mod_init_host_err;

	/* irq settings */
	ret = devm_request_irq(dev, priv->irq, usbhs_पूर्णांकerrupt,
			  priv->irqflags, dev_name(dev), priv);
	अगर (ret) अणु
		dev_err(dev, "irq request err\n");
		जाओ mod_init_gadget_err;
	पूर्ण

	वापस ret;

mod_init_gadget_err:
	usbhs_mod_gadget_हटाओ(priv);
mod_init_host_err:
	usbhs_mod_host_हटाओ(priv);

	वापस ret;
पूर्ण

व्योम usbhs_mod_हटाओ(काष्ठा usbhs_priv *priv)
अणु
	usbhs_mod_host_हटाओ(priv);
	usbhs_mod_gadget_हटाओ(priv);
पूर्ण

/*
 *		status functions
 */
पूर्णांक usbhs_status_get_device_state(काष्ठा usbhs_irq_state *irq_state)
अणु
	वापस (पूर्णांक)irq_state->पूर्णांकsts0 & DVSQ_MASK;
पूर्ण

पूर्णांक usbhs_status_get_ctrl_stage(काष्ठा usbhs_irq_state *irq_state)
अणु
	/*
	 * वापस value
	 *
	 * IDLE_SETUP_STAGE
	 * READ_DATA_STAGE
	 * READ_STATUS_STAGE
	 * WRITE_DATA_STAGE
	 * WRITE_STATUS_STAGE
	 * NODATA_STATUS_STAGE
	 * SEQUENCE_ERROR
	 */
	वापस (पूर्णांक)irq_state->पूर्णांकsts0 & CTSQ_MASK;
पूर्ण

अटल पूर्णांक usbhs_status_get_each_irq(काष्ठा usbhs_priv *priv,
				     काष्ठा usbhs_irq_state *state)
अणु
	काष्ठा usbhs_mod *mod = usbhs_mod_get_current(priv);
	u16 पूर्णांकenb0, पूर्णांकenb1;
	अचिन्हित दीर्घ flags;

	/********************  spin lock ********************/
	usbhs_lock(priv, flags);
	state->पूर्णांकsts0 = usbhs_पढ़ो(priv, INTSTS0);
	पूर्णांकenb0 = usbhs_पढ़ो(priv, INTENB0);

	अगर (usbhs_mod_is_host(priv)) अणु
		state->पूर्णांकsts1 = usbhs_पढ़ो(priv, INTSTS1);
		पूर्णांकenb1 = usbhs_पढ़ो(priv, INTENB1);
	पूर्ण अन्यथा अणु
		state->पूर्णांकsts1 = पूर्णांकenb1 = 0;
	पूर्ण

	/* mask */
	अगर (mod) अणु
		state->brdysts = usbhs_पढ़ो(priv, BRDYSTS);
		state->nrdysts = usbhs_पढ़ो(priv, NRDYSTS);
		state->bempsts = usbhs_पढ़ो(priv, BEMPSTS);

		state->bempsts &= mod->irq_bempsts;
		state->brdysts &= mod->irq_brdysts;
	पूर्ण
	usbhs_unlock(priv, flags);
	/********************  spin unlock ******************/

	/*
	 * Check whether the irq enable रेजिस्टरs and the irq status are set
	 * when IRQF_SHARED is set.
	 */
	अगर (priv->irqflags & IRQF_SHARED) अणु
		अगर (!(पूर्णांकenb0 & state->पूर्णांकsts0) &&
		    !(पूर्णांकenb1 & state->पूर्णांकsts1) &&
		    !(state->bempsts) &&
		    !(state->brdysts))
			वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

/*
 *		पूर्णांकerrupt
 */
#घोषणा INTSTS0_MAGIC 0xF800 /* acknowledge magical पूर्णांकerrupt sources */
#घोषणा INTSTS1_MAGIC 0xA870 /* acknowledge magical पूर्णांकerrupt sources */
अटल irqवापस_t usbhs_पूर्णांकerrupt(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा usbhs_priv *priv = data;
	काष्ठा usbhs_irq_state irq_state;

	अगर (usbhs_status_get_each_irq(priv, &irq_state) < 0)
		वापस IRQ_NONE;

	/*
	 * clear पूर्णांकerrupt
	 *
	 * The hardware is _very_ picky to clear पूर्णांकerrupt bit.
	 * Especially INTSTS0_MAGIC, INTSTS1_MAGIC value.
	 *
	 * see
	 *	"Operation"
	 *	 - "Control Transfer (DCP)"
	 *	   - Function :: VALID bit should 0
	 */
	usbhs_ग_लिखो(priv, INTSTS0, ~irq_state.पूर्णांकsts0 & INTSTS0_MAGIC);
	अगर (usbhs_mod_is_host(priv))
		usbhs_ग_लिखो(priv, INTSTS1, ~irq_state.पूर्णांकsts1 & INTSTS1_MAGIC);

	/*
	 * The driver should not clear the xxxSTS after the line of
	 * "call irq callback functions" because each "if" statement is
	 * possible to call the callback function क्रम aव्योमing any side effects.
	 */
	अगर (irq_state.पूर्णांकsts0 & BRDY)
		usbhs_ग_लिखो(priv, BRDYSTS, ~irq_state.brdysts);
	usbhs_ग_लिखो(priv, NRDYSTS, ~irq_state.nrdysts);
	अगर (irq_state.पूर्णांकsts0 & BEMP)
		usbhs_ग_लिखो(priv, BEMPSTS, ~irq_state.bempsts);

	/*
	 * call irq callback functions
	 * see also
	 *	usbhs_irq_setting_update
	 */

	/* INTSTS0 */
	अगर (irq_state.पूर्णांकsts0 & VBINT)
		usbhs_mod_info_call(priv, irq_vbus, priv, &irq_state);

	अगर (irq_state.पूर्णांकsts0 & DVST)
		usbhs_mod_call(priv, irq_dev_state, priv, &irq_state);

	अगर (irq_state.पूर्णांकsts0 & CTRT)
		usbhs_mod_call(priv, irq_ctrl_stage, priv, &irq_state);

	अगर (irq_state.पूर्णांकsts0 & BEMP)
		usbhs_mod_call(priv, irq_empty, priv, &irq_state);

	अगर (irq_state.पूर्णांकsts0 & BRDY)
		usbhs_mod_call(priv, irq_पढ़ोy, priv, &irq_state);

	अगर (usbhs_mod_is_host(priv)) अणु
		/* INTSTS1 */
		अगर (irq_state.पूर्णांकsts1 & ATTCH)
			usbhs_mod_call(priv, irq_attch, priv, &irq_state);

		अगर (irq_state.पूर्णांकsts1 & DTCH)
			usbhs_mod_call(priv, irq_dtch, priv, &irq_state);

		अगर (irq_state.पूर्णांकsts1 & SIGN)
			usbhs_mod_call(priv, irq_sign, priv, &irq_state);

		अगर (irq_state.पूर्णांकsts1 & SACK)
			usbhs_mod_call(priv, irq_sack, priv, &irq_state);
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

व्योम usbhs_irq_callback_update(काष्ठा usbhs_priv *priv, काष्ठा usbhs_mod *mod)
अणु
	u16 पूर्णांकenb0 = 0;
	u16 पूर्णांकenb1 = 0;
	काष्ठा usbhs_mod_info *info = usbhs_priv_to_modinfo(priv);

	/*
	 * BEMPENB/BRDYENB are picky.
	 * below method is required
	 *
	 *  - clear  INTSTS0
	 *  - update BEMPENB/BRDYENB
	 *  - update INTSTS0
	 */
	usbhs_ग_लिखो(priv, INTENB0, 0);
	अगर (usbhs_mod_is_host(priv))
		usbhs_ग_लिखो(priv, INTENB1, 0);

	usbhs_ग_लिखो(priv, BEMPENB, 0);
	usbhs_ग_लिखो(priv, BRDYENB, 0);

	/*
	 * see also
	 *	usbhs_पूर्णांकerrupt
	 */

	अगर (info->irq_vbus)
		पूर्णांकenb0 |= VBSE;

	अगर (mod) अणु
		/*
		 * INTSTS0
		 */
		अगर (mod->irq_ctrl_stage)
			पूर्णांकenb0 |= CTRE;

		अगर (mod->irq_dev_state)
			पूर्णांकenb0 |= DVSE;

		अगर (mod->irq_empty && mod->irq_bempsts) अणु
			usbhs_ग_लिखो(priv, BEMPENB, mod->irq_bempsts);
			पूर्णांकenb0 |= BEMPE;
		पूर्ण

		अगर (mod->irq_पढ़ोy && mod->irq_brdysts) अणु
			usbhs_ग_लिखो(priv, BRDYENB, mod->irq_brdysts);
			पूर्णांकenb0 |= BRDYE;
		पूर्ण

		अगर (usbhs_mod_is_host(priv)) अणु
			/*
			 * INTSTS1
			 */
			अगर (mod->irq_attch)
				पूर्णांकenb1 |= ATTCHE;

			अगर (mod->irq_dtch)
				पूर्णांकenb1 |= DTCHE;

			अगर (mod->irq_sign)
				पूर्णांकenb1 |= SIGNE;

			अगर (mod->irq_sack)
				पूर्णांकenb1 |= SACKE;
		पूर्ण
	पूर्ण

	अगर (पूर्णांकenb0)
		usbhs_ग_लिखो(priv, INTENB0, पूर्णांकenb0);

	अगर (usbhs_mod_is_host(priv) && पूर्णांकenb1)
		usbhs_ग_लिखो(priv, INTENB1, पूर्णांकenb1);
पूर्ण
