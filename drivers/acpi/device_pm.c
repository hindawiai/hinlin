<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * drivers/acpi/device_pm.c - ACPI device घातer management routines.
 *
 * Copyright (C) 2012, Intel Corp.
 * Author: Rafael J. Wysocki <rafael.j.wysocki@पूर्णांकel.com>
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

#घोषणा pr_fmt(fmt) "ACPI: PM: " fmt

#समावेश <linux/acpi.h>
#समावेश <linux/export.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pm_qos.h>
#समावेश <linux/pm_करोमुख्य.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <linux/suspend.h>

#समावेश "internal.h"

/**
 * acpi_घातer_state_string - String representation of ACPI device घातer state.
 * @state: ACPI device घातer state to वापस the string representation of.
 */
स्थिर अक्षर *acpi_घातer_state_string(पूर्णांक state)
अणु
	चयन (state) अणु
	हाल ACPI_STATE_D0:
		वापस "D0";
	हाल ACPI_STATE_D1:
		वापस "D1";
	हाल ACPI_STATE_D2:
		वापस "D2";
	हाल ACPI_STATE_D3_HOT:
		वापस "D3hot";
	हाल ACPI_STATE_D3_COLD:
		वापस "D3cold";
	शेष:
		वापस "(unknown)";
	पूर्ण
पूर्ण

अटल पूर्णांक acpi_dev_pm_explicit_get(काष्ठा acpi_device *device, पूर्णांक *state)
अणु
	अचिन्हित दीर्घ दीर्घ psc;
	acpi_status status;

	status = acpi_evaluate_पूर्णांकeger(device->handle, "_PSC", शून्य, &psc);
	अगर (ACPI_FAILURE(status))
		वापस -ENODEV;

	*state = psc;
	वापस 0;
पूर्ण

/**
 * acpi_device_get_घातer - Get घातer state of an ACPI device.
 * @device: Device to get the घातer state of.
 * @state: Place to store the घातer state of the device.
 *
 * This function करोes not update the device's घातer.state field, but it may
 * update its parent's power.state field (when the parent's घातer state is
 * unknown and the device's घातer state turns out to be D0).
 *
 * Also, it करोes not update घातer resource reference counters to ensure that
 * the घातer state वापसed by it will be persistent and it may वापस a घातer
 * state shallower than previously set by acpi_device_set_घातer() क्रम @device
 * (अगर that घातer state depends on any घातer resources).
 */
पूर्णांक acpi_device_get_घातer(काष्ठा acpi_device *device, पूर्णांक *state)
अणु
	पूर्णांक result = ACPI_STATE_UNKNOWN;
	पूर्णांक error;

	अगर (!device || !state)
		वापस -EINVAL;

	अगर (!device->flags.घातer_manageable) अणु
		/* TBD: Non-recursive algorithm क्रम walking up hierarchy. */
		*state = device->parent ?
			device->parent->घातer.state : ACPI_STATE_D0;
		जाओ out;
	पूर्ण

	/*
	 * Get the device's घातer state from घातer resources settings and _PSC,
	 * अगर available.
	 */
	अगर (device->घातer.flags.घातer_resources) अणु
		error = acpi_घातer_get_inferred_state(device, &result);
		अगर (error)
			वापस error;
	पूर्ण
	अगर (device->घातer.flags.explicit_get) अणु
		पूर्णांक psc;

		error = acpi_dev_pm_explicit_get(device, &psc);
		अगर (error)
			वापस error;

		/*
		 * The घातer resources settings may indicate a घातer state
		 * shallower than the actual घातer state of the device, because
		 * the same घातer resources may be referenced by other devices.
		 *
		 * For प्रणालीs predating ACPI 4.0 we assume that D3hot is the
		 * deepest state that can be supported.
		 */
		अगर (psc > result && psc < ACPI_STATE_D3_COLD)
			result = psc;
		अन्यथा अगर (result == ACPI_STATE_UNKNOWN)
			result = psc > ACPI_STATE_D2 ? ACPI_STATE_D3_HOT : psc;
	पूर्ण

	/*
	 * If we were unsure about the device parent's घातer state up to this
	 * poपूर्णांक, the fact that the device is in D0 implies that the parent has
	 * to be in D0 too, except अगर ignore_parent is set.
	 */
	अगर (!device->घातer.flags.ignore_parent && device->parent
	    && device->parent->घातer.state == ACPI_STATE_UNKNOWN
	    && result == ACPI_STATE_D0)
		device->parent->घातer.state = ACPI_STATE_D0;

	*state = result;

 out:
	dev_dbg(&device->dev, "Device power state is %s\n",
		acpi_घातer_state_string(*state));

	वापस 0;
पूर्ण

अटल पूर्णांक acpi_dev_pm_explicit_set(काष्ठा acpi_device *adev, पूर्णांक state)
अणु
	अगर (adev->घातer.states[state].flags.explicit_set) अणु
		अक्षर method[5] = अणु '_', 'P', 'S', '0' + state, '\0' पूर्ण;
		acpi_status status;

		status = acpi_evaluate_object(adev->handle, method, शून्य, शून्य);
		अगर (ACPI_FAILURE(status))
			वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * acpi_device_set_घातer - Set घातer state of an ACPI device.
 * @device: Device to set the घातer state of.
 * @state: New घातer state to set.
 *
 * Callers must ensure that the device is घातer manageable beक्रमe using this
 * function.
 */
पूर्णांक acpi_device_set_घातer(काष्ठा acpi_device *device, पूर्णांक state)
अणु
	पूर्णांक target_state = state;
	पूर्णांक result = 0;

	अगर (!device || !device->flags.घातer_manageable
	    || (state < ACPI_STATE_D0) || (state > ACPI_STATE_D3_COLD))
		वापस -EINVAL;

	acpi_handle_debug(device->handle, "Power state change: %s -> %s\n",
			  acpi_घातer_state_string(device->घातer.state),
			  acpi_घातer_state_string(state));

	/* Make sure this is a valid target state */

	/* There is a special हाल क्रम D0 addressed below. */
	अगर (state > ACPI_STATE_D0 && state == device->घातer.state) अणु
		dev_dbg(&device->dev, "Device already in %s\n",
			acpi_घातer_state_string(state));
		वापस 0;
	पूर्ण

	अगर (state == ACPI_STATE_D3_COLD) अणु
		/*
		 * For transitions to D3cold we need to execute _PS3 and then
		 * possibly drop references to the घातer resources in use.
		 */
		state = ACPI_STATE_D3_HOT;
		/* If D3cold is not supported, use D3hot as the target state. */
		अगर (!device->घातer.states[ACPI_STATE_D3_COLD].flags.valid)
			target_state = state;
	पूर्ण अन्यथा अगर (!device->घातer.states[state].flags.valid) अणु
		dev_warn(&device->dev, "Power state %s not supported\n",
			 acpi_घातer_state_string(state));
		वापस -ENODEV;
	पूर्ण

	अगर (!device->घातer.flags.ignore_parent &&
	    device->parent && (state < device->parent->घातer.state)) अणु
		dev_warn(&device->dev,
			 "Cannot transition to power state %s for parent in %s\n",
			 acpi_घातer_state_string(state),
			 acpi_घातer_state_string(device->parent->घातer.state));
		वापस -ENODEV;
	पूर्ण

	/*
	 * Transition Power
	 * ----------------
	 * In accordance with ACPI 6, _PSx is executed beक्रमe manipulating घातer
	 * resources, unless the target state is D0, in which हाल _PS0 is
	 * supposed to be executed after turning the घातer resources on.
	 */
	अगर (state > ACPI_STATE_D0) अणु
		/*
		 * According to ACPI 6, devices cannot go from lower-घातer
		 * (deeper) states to higher-घातer (shallower) states.
		 */
		अगर (state < device->घातer.state) अणु
			dev_warn(&device->dev, "Cannot transition from %s to %s\n",
				 acpi_घातer_state_string(device->घातer.state),
				 acpi_घातer_state_string(state));
			वापस -ENODEV;
		पूर्ण

		/*
		 * If the device goes from D3hot to D3cold, _PS3 has been
		 * evaluated क्रम it alपढ़ोy, so skip it in that हाल.
		 */
		अगर (device->घातer.state < ACPI_STATE_D3_HOT) अणु
			result = acpi_dev_pm_explicit_set(device, state);
			अगर (result)
				जाओ end;
		पूर्ण

		अगर (device->घातer.flags.घातer_resources)
			result = acpi_घातer_transition(device, target_state);
	पूर्ण अन्यथा अणु
		पूर्णांक cur_state = device->घातer.state;

		अगर (device->घातer.flags.घातer_resources) अणु
			result = acpi_घातer_transition(device, ACPI_STATE_D0);
			अगर (result)
				जाओ end;
		पूर्ण

		अगर (cur_state == ACPI_STATE_D0) अणु
			पूर्णांक psc;

			/* Nothing to करो here अगर _PSC is not present. */
			अगर (!device->घातer.flags.explicit_get)
				वापस 0;

			/*
			 * The घातer state of the device was set to D0 last
			 * समय, but that might have happened beक्रमe a
			 * प्रणाली-wide transition involving the platक्रमm
			 * firmware, so it may be necessary to evaluate _PS0
			 * क्रम the device here.  However, use extra care here
			 * and evaluate _PSC to check the device's current घातer
			 * state, and only invoke _PS0 अगर the evaluation of _PSC
			 * is successful and it वापसs a घातer state dअगरferent
			 * from D0.
			 */
			result = acpi_dev_pm_explicit_get(device, &psc);
			अगर (result || psc == ACPI_STATE_D0)
				वापस 0;
		पूर्ण

		result = acpi_dev_pm_explicit_set(device, ACPI_STATE_D0);
	पूर्ण

 end:
	अगर (result) अणु
		dev_warn(&device->dev, "Failed to change power state to %s\n",
			 acpi_घातer_state_string(target_state));
	पूर्ण अन्यथा अणु
		device->घातer.state = target_state;
		dev_dbg(&device->dev, "Power state changed to %s\n",
			acpi_घातer_state_string(target_state));
	पूर्ण

	वापस result;
पूर्ण
EXPORT_SYMBOL(acpi_device_set_घातer);

पूर्णांक acpi_bus_set_घातer(acpi_handle handle, पूर्णांक state)
अणु
	काष्ठा acpi_device *device;
	पूर्णांक result;

	result = acpi_bus_get_device(handle, &device);
	अगर (result)
		वापस result;

	वापस acpi_device_set_घातer(device, state);
पूर्ण
EXPORT_SYMBOL(acpi_bus_set_घातer);

पूर्णांक acpi_bus_init_घातer(काष्ठा acpi_device *device)
अणु
	पूर्णांक state;
	पूर्णांक result;

	अगर (!device)
		वापस -EINVAL;

	device->घातer.state = ACPI_STATE_UNKNOWN;
	अगर (!acpi_device_is_present(device)) अणु
		device->flags.initialized = false;
		वापस -ENXIO;
	पूर्ण

	result = acpi_device_get_घातer(device, &state);
	अगर (result)
		वापस result;

	अगर (state < ACPI_STATE_D3_COLD && device->घातer.flags.घातer_resources) अणु
		/* Reference count the घातer resources. */
		result = acpi_घातer_on_resources(device, state);
		अगर (result)
			वापस result;

		अगर (state == ACPI_STATE_D0) अणु
			/*
			 * If _PSC is not present and the state inferred from
			 * घातer resources appears to be D0, it still may be
			 * necessary to execute _PS0 at this poपूर्णांक, because
			 * another device using the same घातer resources may
			 * have been put पूर्णांकo D0 previously and that's why we
			 * see D0 here.
			 */
			result = acpi_dev_pm_explicit_set(device, state);
			अगर (result)
				वापस result;
		पूर्ण
	पूर्ण अन्यथा अगर (state == ACPI_STATE_UNKNOWN) अणु
		/*
		 * No घातer resources and missing _PSC?  Cross fingers and make
		 * it D0 in hope that this is what the BIOS put the device पूर्णांकo.
		 * [We tried to क्रमce D0 here by executing _PS0, but that broke
		 * Toshiba P870-303 in a nasty way.]
		 */
		state = ACPI_STATE_D0;
	पूर्ण
	device->घातer.state = state;
	वापस 0;
पूर्ण

/**
 * acpi_device_fix_up_घातer - Force device with missing _PSC पूर्णांकo D0.
 * @device: Device object whose घातer state is to be fixed up.
 *
 * Devices without घातer resources and _PSC, but having _PS0 and _PS3 defined,
 * are assumed to be put पूर्णांकo D0 by the BIOS.  However, in some हालs that may
 * not be the हाल and this function should be used then.
 */
पूर्णांक acpi_device_fix_up_घातer(काष्ठा acpi_device *device)
अणु
	पूर्णांक ret = 0;

	अगर (!device->घातer.flags.घातer_resources
	    && !device->घातer.flags.explicit_get
	    && device->घातer.state == ACPI_STATE_D0)
		ret = acpi_dev_pm_explicit_set(device, ACPI_STATE_D0);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_device_fix_up_घातer);

पूर्णांक acpi_device_update_घातer(काष्ठा acpi_device *device, पूर्णांक *state_p)
अणु
	पूर्णांक state;
	पूर्णांक result;

	अगर (device->घातer.state == ACPI_STATE_UNKNOWN) अणु
		result = acpi_bus_init_घातer(device);
		अगर (!result && state_p)
			*state_p = device->घातer.state;

		वापस result;
	पूर्ण

	result = acpi_device_get_घातer(device, &state);
	अगर (result)
		वापस result;

	अगर (state == ACPI_STATE_UNKNOWN) अणु
		state = ACPI_STATE_D0;
		result = acpi_device_set_घातer(device, state);
		अगर (result)
			वापस result;
	पूर्ण अन्यथा अणु
		अगर (device->घातer.flags.घातer_resources) अणु
			/*
			 * We करोn't need to really चयन the state, bu we need
			 * to update the घातer resources' reference counters.
			 */
			result = acpi_घातer_transition(device, state);
			अगर (result)
				वापस result;
		पूर्ण
		device->घातer.state = state;
	पूर्ण
	अगर (state_p)
		*state_p = state;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_device_update_घातer);

पूर्णांक acpi_bus_update_घातer(acpi_handle handle, पूर्णांक *state_p)
अणु
	काष्ठा acpi_device *device;
	पूर्णांक result;

	result = acpi_bus_get_device(handle, &device);
	वापस result ? result : acpi_device_update_घातer(device, state_p);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_bus_update_घातer);

bool acpi_bus_घातer_manageable(acpi_handle handle)
अणु
	काष्ठा acpi_device *device;
	पूर्णांक result;

	result = acpi_bus_get_device(handle, &device);
	वापस result ? false : device->flags.घातer_manageable;
पूर्ण
EXPORT_SYMBOL(acpi_bus_घातer_manageable);

#अगर_घोषित CONFIG_PM
अटल DEFINE_MUTEX(acpi_pm_notअगरier_lock);
अटल DEFINE_MUTEX(acpi_pm_notअगरier_install_lock);

व्योम acpi_pm_wakeup_event(काष्ठा device *dev)
अणु
	pm_wakeup_dev_event(dev, 0, acpi_s2idle_wakeup());
पूर्ण
EXPORT_SYMBOL_GPL(acpi_pm_wakeup_event);

अटल व्योम acpi_pm_notअगरy_handler(acpi_handle handle, u32 val, व्योम *not_used)
अणु
	काष्ठा acpi_device *adev;

	अगर (val != ACPI_NOTIFY_DEVICE_WAKE)
		वापस;

	acpi_handle_debug(handle, "Wake notify\n");

	adev = acpi_bus_get_acpi_device(handle);
	अगर (!adev)
		वापस;

	mutex_lock(&acpi_pm_notअगरier_lock);

	अगर (adev->wakeup.flags.notअगरier_present) अणु
		pm_wakeup_ws_event(adev->wakeup.ws, 0, acpi_s2idle_wakeup());
		अगर (adev->wakeup.context.func) अणु
			acpi_handle_debug(handle, "Running %pS for %s\n",
					  adev->wakeup.context.func,
					  dev_name(adev->wakeup.context.dev));
			adev->wakeup.context.func(&adev->wakeup.context);
		पूर्ण
	पूर्ण

	mutex_unlock(&acpi_pm_notअगरier_lock);

	acpi_bus_put_acpi_device(adev);
पूर्ण

/**
 * acpi_add_pm_notअगरier - Register PM notअगरy handler क्रम given ACPI device.
 * @adev: ACPI device to add the notअगरy handler क्रम.
 * @dev: Device to generate a wakeup event क्रम जबतक handling the notअगरication.
 * @func: Work function to execute when handling the notअगरication.
 *
 * NOTE: @adev need not be a run-wake or wakeup device to be a valid source of
 * PM wakeup events.  For example, wakeup events may be generated क्रम bridges
 * अगर one of the devices below the bridge is संकेतing wakeup, even अगर the
 * bridge itself करोesn't have a wakeup GPE associated with it.
 */
acpi_status acpi_add_pm_notअगरier(काष्ठा acpi_device *adev, काष्ठा device *dev,
			व्योम (*func)(काष्ठा acpi_device_wakeup_context *context))
अणु
	acpi_status status = AE_ALREADY_EXISTS;

	अगर (!dev && !func)
		वापस AE_BAD_PARAMETER;

	mutex_lock(&acpi_pm_notअगरier_install_lock);

	अगर (adev->wakeup.flags.notअगरier_present)
		जाओ out;

	status = acpi_install_notअगरy_handler(adev->handle, ACPI_SYSTEM_NOTIFY,
					     acpi_pm_notअगरy_handler, शून्य);
	अगर (ACPI_FAILURE(status))
		जाओ out;

	mutex_lock(&acpi_pm_notअगरier_lock);
	adev->wakeup.ws = wakeup_source_रेजिस्टर(&adev->dev,
						 dev_name(&adev->dev));
	adev->wakeup.context.dev = dev;
	adev->wakeup.context.func = func;
	adev->wakeup.flags.notअगरier_present = true;
	mutex_unlock(&acpi_pm_notअगरier_lock);

 out:
	mutex_unlock(&acpi_pm_notअगरier_install_lock);
	वापस status;
पूर्ण

/**
 * acpi_हटाओ_pm_notअगरier - Unरेजिस्टर PM notअगरier from given ACPI device.
 * @adev: ACPI device to हटाओ the notअगरier from.
 */
acpi_status acpi_हटाओ_pm_notअगरier(काष्ठा acpi_device *adev)
अणु
	acpi_status status = AE_BAD_PARAMETER;

	mutex_lock(&acpi_pm_notअगरier_install_lock);

	अगर (!adev->wakeup.flags.notअगरier_present)
		जाओ out;

	status = acpi_हटाओ_notअगरy_handler(adev->handle,
					    ACPI_SYSTEM_NOTIFY,
					    acpi_pm_notअगरy_handler);
	अगर (ACPI_FAILURE(status))
		जाओ out;

	mutex_lock(&acpi_pm_notअगरier_lock);
	adev->wakeup.context.func = शून्य;
	adev->wakeup.context.dev = शून्य;
	wakeup_source_unरेजिस्टर(adev->wakeup.ws);
	adev->wakeup.flags.notअगरier_present = false;
	mutex_unlock(&acpi_pm_notअगरier_lock);

 out:
	mutex_unlock(&acpi_pm_notअगरier_install_lock);
	वापस status;
पूर्ण

bool acpi_bus_can_wakeup(acpi_handle handle)
अणु
	काष्ठा acpi_device *device;
	पूर्णांक result;

	result = acpi_bus_get_device(handle, &device);
	वापस result ? false : device->wakeup.flags.valid;
पूर्ण
EXPORT_SYMBOL(acpi_bus_can_wakeup);

bool acpi_pm_device_can_wakeup(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);

	वापस adev ? acpi_device_can_wakeup(adev) : false;
पूर्ण

/**
 * acpi_dev_pm_get_state - Get preferred घातer state of ACPI device.
 * @dev: Device whose preferred target घातer state to वापस.
 * @adev: ACPI device node corresponding to @dev.
 * @target_state: System state to match the resultant device state.
 * @d_min_p: Location to store the highest घातer state available to the device.
 * @d_max_p: Location to store the lowest घातer state available to the device.
 *
 * Find the lowest घातer (highest number) and highest घातer (lowest number) ACPI
 * device घातer states that the device can be in जबतक the प्रणाली is in the
 * state represented by @target_state.  Store the पूर्णांकeger numbers representing
 * those stats in the memory locations poपूर्णांकed to by @d_max_p and @d_min_p,
 * respectively.
 *
 * Callers must ensure that @dev and @adev are valid poपूर्णांकers and that @adev
 * actually corresponds to @dev beक्रमe using this function.
 *
 * Returns 0 on success or -ENODATA when one of the ACPI methods fails or
 * वापसs a value that करोesn't make sense.  The memory locations poपूर्णांकed to by
 * @d_max_p and @d_min_p are only modअगरied on success.
 */
अटल पूर्णांक acpi_dev_pm_get_state(काष्ठा device *dev, काष्ठा acpi_device *adev,
				 u32 target_state, पूर्णांक *d_min_p, पूर्णांक *d_max_p)
अणु
	अक्षर method[] = अणु '_', 'S', '0' + target_state, 'D', '\0' पूर्ण;
	acpi_handle handle = adev->handle;
	अचिन्हित दीर्घ दीर्घ ret;
	पूर्णांक d_min, d_max;
	bool wakeup = false;
	bool has_sxd = false;
	acpi_status status;

	/*
	 * If the प्रणाली state is S0, the lowest घातer state the device can be
	 * in is D3cold, unless the device has _S0W and is supposed to संकेत
	 * wakeup, in which हाल the वापस value of _S0W has to be used as the
	 * lowest घातer state available to the device.
	 */
	d_min = ACPI_STATE_D0;
	d_max = ACPI_STATE_D3_COLD;

	/*
	 * If present, _SxD methods वापस the minimum D-state (highest घातer
	 * state) we can use क्रम the corresponding S-states.  Otherwise, the
	 * minimum D-state is D0 (ACPI 3.x).
	 */
	अगर (target_state > ACPI_STATE_S0) अणु
		/*
		 * We rely on acpi_evaluate_पूर्णांकeger() not clobbering the पूर्णांकeger
		 * provided अगर AE_NOT_FOUND is वापसed.
		 */
		ret = d_min;
		status = acpi_evaluate_पूर्णांकeger(handle, method, शून्य, &ret);
		अगर ((ACPI_FAILURE(status) && status != AE_NOT_FOUND)
		    || ret > ACPI_STATE_D3_COLD)
			वापस -ENODATA;

		/*
		 * We need to handle legacy प्रणालीs where D3hot and D3cold are
		 * the same and 3 is वापसed in both हालs, so fall back to
		 * D3cold अगर D3hot is not a valid state.
		 */
		अगर (!adev->घातer.states[ret].flags.valid) अणु
			अगर (ret == ACPI_STATE_D3_HOT)
				ret = ACPI_STATE_D3_COLD;
			अन्यथा
				वापस -ENODATA;
		पूर्ण

		अगर (status == AE_OK)
			has_sxd = true;

		d_min = ret;
		wakeup = device_may_wakeup(dev) && adev->wakeup.flags.valid
			&& adev->wakeup.sleep_state >= target_state;
	पूर्ण अन्यथा अणु
		wakeup = adev->wakeup.flags.valid;
	पूर्ण

	/*
	 * If _PRW says we can wake up the प्रणाली from the target sleep state,
	 * the D-state वापसed by _SxD is sufficient क्रम that (we assume a
	 * wakeup-aware driver अगर wake is set).  Still, अगर _SxW exists
	 * (ACPI 3.x), it should वापस the maximum (lowest घातer) D-state that
	 * can wake the प्रणाली.  _S0W may be valid, too.
	 */
	अगर (wakeup) अणु
		method[3] = 'W';
		status = acpi_evaluate_पूर्णांकeger(handle, method, शून्य, &ret);
		अगर (status == AE_NOT_FOUND) अणु
			/* No _SxW. In this हाल, the ACPI spec says that we
			 * must not go पूर्णांकo any घातer state deeper than the
			 * value वापसed from _SxD.
			 */
			अगर (has_sxd && target_state > ACPI_STATE_S0)
				d_max = d_min;
		पूर्ण अन्यथा अगर (ACPI_SUCCESS(status) && ret <= ACPI_STATE_D3_COLD) अणु
			/* Fall back to D3cold अगर ret is not a valid state. */
			अगर (!adev->घातer.states[ret].flags.valid)
				ret = ACPI_STATE_D3_COLD;

			d_max = ret > d_min ? ret : d_min;
		पूर्ण अन्यथा अणु
			वापस -ENODATA;
		पूर्ण
	पूर्ण

	अगर (d_min_p)
		*d_min_p = d_min;

	अगर (d_max_p)
		*d_max_p = d_max;

	वापस 0;
पूर्ण

/**
 * acpi_pm_device_sleep_state - Get preferred घातer state of ACPI device.
 * @dev: Device whose preferred target घातer state to वापस.
 * @d_min_p: Location to store the upper limit of the allowed states range.
 * @d_max_in: Deepest low-घातer state to take पूर्णांकo consideration.
 * Return value: Preferred घातer state of the device on success, -ENODEV
 * अगर there's no 'struct acpi_device' क्रम @dev, -EINVAL अगर @d_max_in is
 * incorrect, or -ENODATA on ACPI method failure.
 *
 * The caller must ensure that @dev is valid beक्रमe using this function.
 */
पूर्णांक acpi_pm_device_sleep_state(काष्ठा device *dev, पूर्णांक *d_min_p, पूर्णांक d_max_in)
अणु
	काष्ठा acpi_device *adev;
	पूर्णांक ret, d_min, d_max;

	अगर (d_max_in < ACPI_STATE_D0 || d_max_in > ACPI_STATE_D3_COLD)
		वापस -EINVAL;

	अगर (d_max_in > ACPI_STATE_D2) अणु
		क्रमागत pm_qos_flags_status stat;

		stat = dev_pm_qos_flags(dev, PM_QOS_FLAG_NO_POWER_OFF);
		अगर (stat == PM_QOS_FLAGS_ALL)
			d_max_in = ACPI_STATE_D2;
	पूर्ण

	adev = ACPI_COMPANION(dev);
	अगर (!adev) अणु
		dev_dbg(dev, "ACPI companion missing in %s!\n", __func__);
		वापस -ENODEV;
	पूर्ण

	ret = acpi_dev_pm_get_state(dev, adev, acpi_target_प्रणाली_state(),
				    &d_min, &d_max);
	अगर (ret)
		वापस ret;

	अगर (d_max_in < d_min)
		वापस -EINVAL;

	अगर (d_max > d_max_in) अणु
		क्रम (d_max = d_max_in; d_max > d_min; d_max--) अणु
			अगर (adev->घातer.states[d_max].flags.valid)
				अवरोध;
		पूर्ण
	पूर्ण

	अगर (d_min_p)
		*d_min_p = d_min;

	वापस d_max;
पूर्ण
EXPORT_SYMBOL(acpi_pm_device_sleep_state);

/**
 * acpi_pm_notअगरy_work_func - ACPI devices wakeup notअगरication work function.
 * @context: Device wakeup context.
 */
अटल व्योम acpi_pm_notअगरy_work_func(काष्ठा acpi_device_wakeup_context *context)
अणु
	काष्ठा device *dev = context->dev;

	अगर (dev) अणु
		pm_wakeup_event(dev, 0);
		pm_request_resume(dev);
	पूर्ण
पूर्ण

अटल DEFINE_MUTEX(acpi_wakeup_lock);

अटल पूर्णांक __acpi_device_wakeup_enable(काष्ठा acpi_device *adev,
				       u32 target_state)
अणु
	काष्ठा acpi_device_wakeup *wakeup = &adev->wakeup;
	acpi_status status;
	पूर्णांक error = 0;

	mutex_lock(&acpi_wakeup_lock);

	/*
	 * If the device wakeup घातer is alपढ़ोy enabled, disable it and enable
	 * it again in हाल it depends on the configuration of subordinate
	 * devices and the conditions have changed since it was enabled last
	 * समय.
	 */
	अगर (wakeup->enable_count > 0)
		acpi_disable_wakeup_device_घातer(adev);

	error = acpi_enable_wakeup_device_घातer(adev, target_state);
	अगर (error) अणु
		अगर (wakeup->enable_count > 0) अणु
			acpi_disable_gpe(wakeup->gpe_device, wakeup->gpe_number);
			wakeup->enable_count = 0;
		पूर्ण
		जाओ out;
	पूर्ण

	अगर (wakeup->enable_count > 0)
		जाओ inc;

	status = acpi_enable_gpe(wakeup->gpe_device, wakeup->gpe_number);
	अगर (ACPI_FAILURE(status)) अणु
		acpi_disable_wakeup_device_घातer(adev);
		error = -EIO;
		जाओ out;
	पूर्ण

	acpi_handle_debug(adev->handle, "GPE%2X enabled for wakeup\n",
			  (अचिन्हित पूर्णांक)wakeup->gpe_number);

inc:
	अगर (wakeup->enable_count < पूर्णांक_उच्च)
		wakeup->enable_count++;
	अन्यथा
		acpi_handle_info(adev->handle, "Wakeup enable count out of bounds!\n");

out:
	mutex_unlock(&acpi_wakeup_lock);
	वापस error;
पूर्ण

/**
 * acpi_device_wakeup_enable - Enable wakeup functionality क्रम device.
 * @adev: ACPI device to enable wakeup functionality क्रम.
 * @target_state: State the प्रणाली is transitioning पूर्णांकo.
 *
 * Enable the GPE associated with @adev so that it can generate wakeup संकेतs
 * क्रम the device in response to बाह्यal (remote) events and enable wakeup
 * घातer क्रम it.
 *
 * Callers must ensure that @adev is a valid ACPI device node beक्रमe executing
 * this function.
 */
अटल पूर्णांक acpi_device_wakeup_enable(काष्ठा acpi_device *adev, u32 target_state)
अणु
	वापस __acpi_device_wakeup_enable(adev, target_state);
पूर्ण

/**
 * acpi_device_wakeup_disable - Disable wakeup functionality क्रम device.
 * @adev: ACPI device to disable wakeup functionality क्रम.
 *
 * Disable the GPE associated with @adev and disable wakeup घातer क्रम it.
 *
 * Callers must ensure that @adev is a valid ACPI device node beक्रमe executing
 * this function.
 */
अटल व्योम acpi_device_wakeup_disable(काष्ठा acpi_device *adev)
अणु
	काष्ठा acpi_device_wakeup *wakeup = &adev->wakeup;

	mutex_lock(&acpi_wakeup_lock);

	अगर (!wakeup->enable_count)
		जाओ out;

	acpi_disable_gpe(wakeup->gpe_device, wakeup->gpe_number);
	acpi_disable_wakeup_device_घातer(adev);

	wakeup->enable_count--;

out:
	mutex_unlock(&acpi_wakeup_lock);
पूर्ण

/**
 * acpi_pm_set_device_wakeup - Enable/disable remote wakeup क्रम given device.
 * @dev: Device to enable/disable to generate wakeup events.
 * @enable: Whether to enable or disable the wakeup functionality.
 */
पूर्णांक acpi_pm_set_device_wakeup(काष्ठा device *dev, bool enable)
अणु
	काष्ठा acpi_device *adev;
	पूर्णांक error;

	adev = ACPI_COMPANION(dev);
	अगर (!adev) अणु
		dev_dbg(dev, "ACPI companion missing in %s!\n", __func__);
		वापस -ENODEV;
	पूर्ण

	अगर (!acpi_device_can_wakeup(adev))
		वापस -EINVAL;

	अगर (!enable) अणु
		acpi_device_wakeup_disable(adev);
		dev_dbg(dev, "Wakeup disabled by ACPI\n");
		वापस 0;
	पूर्ण

	error = __acpi_device_wakeup_enable(adev, acpi_target_प्रणाली_state());
	अगर (!error)
		dev_dbg(dev, "Wakeup enabled by ACPI\n");

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_pm_set_device_wakeup);

/**
 * acpi_dev_pm_low_घातer - Put ACPI device पूर्णांकo a low-घातer state.
 * @dev: Device to put पूर्णांकo a low-घातer state.
 * @adev: ACPI device node corresponding to @dev.
 * @प्रणाली_state: System state to choose the device state क्रम.
 */
अटल पूर्णांक acpi_dev_pm_low_घातer(काष्ठा device *dev, काष्ठा acpi_device *adev,
				 u32 प्रणाली_state)
अणु
	पूर्णांक ret, state;

	अगर (!acpi_device_घातer_manageable(adev))
		वापस 0;

	ret = acpi_dev_pm_get_state(dev, adev, प्रणाली_state, शून्य, &state);
	वापस ret ? ret : acpi_device_set_घातer(adev, state);
पूर्ण

/**
 * acpi_dev_pm_full_घातer - Put ACPI device पूर्णांकo the full-घातer state.
 * @adev: ACPI device node to put पूर्णांकo the full-घातer state.
 */
अटल पूर्णांक acpi_dev_pm_full_घातer(काष्ठा acpi_device *adev)
अणु
	वापस acpi_device_घातer_manageable(adev) ?
		acpi_device_set_घातer(adev, ACPI_STATE_D0) : 0;
पूर्ण

/**
 * acpi_dev_suspend - Put device पूर्णांकo a low-घातer state using ACPI.
 * @dev: Device to put पूर्णांकo a low-घातer state.
 * @wakeup: Whether or not to enable wakeup क्रम the device.
 *
 * Put the given device पूर्णांकo a low-घातer state using the standard ACPI
 * mechanism.  Set up remote wakeup अगर desired, choose the state to put the
 * device पूर्णांकo (this checks अगर remote wakeup is expected to work too), and set
 * the घातer state of the device.
 */
पूर्णांक acpi_dev_suspend(काष्ठा device *dev, bool wakeup)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	u32 target_state = acpi_target_प्रणाली_state();
	पूर्णांक error;

	अगर (!adev)
		वापस 0;

	अगर (wakeup && acpi_device_can_wakeup(adev)) अणु
		error = acpi_device_wakeup_enable(adev, target_state);
		अगर (error)
			वापस -EAGAIN;
	पूर्ण अन्यथा अणु
		wakeup = false;
	पूर्ण

	error = acpi_dev_pm_low_घातer(dev, adev, target_state);
	अगर (error && wakeup)
		acpi_device_wakeup_disable(adev);

	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_suspend);

/**
 * acpi_dev_resume - Put device पूर्णांकo the full-घातer state using ACPI.
 * @dev: Device to put पूर्णांकo the full-घातer state.
 *
 * Put the given device पूर्णांकo the full-घातer state using the standard ACPI
 * mechanism.  Set the घातer state of the device to ACPI D0 and disable wakeup.
 */
पूर्णांक acpi_dev_resume(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);
	पूर्णांक error;

	अगर (!adev)
		वापस 0;

	error = acpi_dev_pm_full_घातer(adev);
	acpi_device_wakeup_disable(adev);
	वापस error;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_resume);

/**
 * acpi_subsys_runसमय_suspend - Suspend device using ACPI.
 * @dev: Device to suspend.
 *
 * Carry out the generic runसमय suspend procedure क्रम @dev and use ACPI to put
 * it पूर्णांकo a runसमय low-घातer state.
 */
पूर्णांक acpi_subsys_runसमय_suspend(काष्ठा device *dev)
अणु
	पूर्णांक ret = pm_generic_runसमय_suspend(dev);

	वापस ret ? ret : acpi_dev_suspend(dev, true);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_subsys_runसमय_suspend);

/**
 * acpi_subsys_runसमय_resume - Resume device using ACPI.
 * @dev: Device to Resume.
 *
 * Use ACPI to put the given device पूर्णांकo the full-घातer state and carry out the
 * generic runसमय resume procedure क्रम it.
 */
पूर्णांक acpi_subsys_runसमय_resume(काष्ठा device *dev)
अणु
	पूर्णांक ret = acpi_dev_resume(dev);

	वापस ret ? ret : pm_generic_runसमय_resume(dev);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_subsys_runसमय_resume);

#अगर_घोषित CONFIG_PM_SLEEP
अटल bool acpi_dev_needs_resume(काष्ठा device *dev, काष्ठा acpi_device *adev)
अणु
	u32 sys_target = acpi_target_प्रणाली_state();
	पूर्णांक ret, state;

	अगर (!pm_runसमय_suspended(dev) || !adev || (adev->wakeup.flags.valid &&
	    device_may_wakeup(dev) != !!adev->wakeup.prepare_count))
		वापस true;

	अगर (sys_target == ACPI_STATE_S0)
		वापस false;

	अगर (adev->घातer.flags.dsw_present)
		वापस true;

	ret = acpi_dev_pm_get_state(dev, adev, sys_target, शून्य, &state);
	अगर (ret)
		वापस true;

	वापस state != adev->घातer.state;
पूर्ण

/**
 * acpi_subsys_prepare - Prepare device क्रम प्रणाली transition to a sleep state.
 * @dev: Device to prepare.
 */
पूर्णांक acpi_subsys_prepare(काष्ठा device *dev)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);

	अगर (dev->driver && dev->driver->pm && dev->driver->pm->prepare) अणु
		पूर्णांक ret = dev->driver->pm->prepare(dev);

		अगर (ret < 0)
			वापस ret;

		अगर (!ret && dev_pm_test_driver_flags(dev, DPM_FLAG_SMART_PREPARE))
			वापस 0;
	पूर्ण

	वापस !acpi_dev_needs_resume(dev, adev);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_subsys_prepare);

/**
 * acpi_subsys_complete - Finalize device's resume during प्रणाली resume.
 * @dev: Device to handle.
 */
व्योम acpi_subsys_complete(काष्ठा device *dev)
अणु
	pm_generic_complete(dev);
	/*
	 * If the device had been runसमय-suspended beक्रमe the प्रणाली went पूर्णांकo
	 * the sleep state it is going out of and it has never been resumed till
	 * now, resume it in हाल the firmware घातered it up.
	 */
	अगर (pm_runसमय_suspended(dev) && pm_resume_via_firmware())
		pm_request_resume(dev);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_subsys_complete);

/**
 * acpi_subsys_suspend - Run the device driver's suspend callback.
 * @dev: Device to handle.
 *
 * Follow PCI and resume devices from runसमय suspend beक्रमe running their
 * प्रणाली suspend callbacks, unless the driver can cope with runसमय-suspended
 * devices during प्रणाली suspend and there are no ACPI-specअगरic reasons क्रम
 * resuming them.
 */
पूर्णांक acpi_subsys_suspend(काष्ठा device *dev)
अणु
	अगर (!dev_pm_test_driver_flags(dev, DPM_FLAG_SMART_SUSPEND) ||
	    acpi_dev_needs_resume(dev, ACPI_COMPANION(dev)))
		pm_runसमय_resume(dev);

	वापस pm_generic_suspend(dev);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_subsys_suspend);

/**
 * acpi_subsys_suspend_late - Suspend device using ACPI.
 * @dev: Device to suspend.
 *
 * Carry out the generic late suspend procedure क्रम @dev and use ACPI to put
 * it पूर्णांकo a low-घातer state during प्रणाली transition पूर्णांकo a sleep state.
 */
पूर्णांक acpi_subsys_suspend_late(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	अगर (dev_pm_skip_suspend(dev))
		वापस 0;

	ret = pm_generic_suspend_late(dev);
	वापस ret ? ret : acpi_dev_suspend(dev, device_may_wakeup(dev));
पूर्ण
EXPORT_SYMBOL_GPL(acpi_subsys_suspend_late);

/**
 * acpi_subsys_suspend_noirq - Run the device driver's "noirq" suspend callback.
 * @dev: Device to suspend.
 */
पूर्णांक acpi_subsys_suspend_noirq(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	अगर (dev_pm_skip_suspend(dev))
		वापस 0;

	ret = pm_generic_suspend_noirq(dev);
	अगर (ret)
		वापस ret;

	/*
	 * If the target प्रणाली sleep state is suspend-to-idle, it is sufficient
	 * to check whether or not the device's wakeup settings are good क्रम
	 * runसमय PM.  Otherwise, the pm_resume_via_firmware() check will cause
	 * acpi_subsys_complete() to take care of fixing up the device's state
	 * anyway, अगर need be.
	 */
	अगर (device_can_wakeup(dev) && !device_may_wakeup(dev))
		dev->घातer.may_skip_resume = false;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_subsys_suspend_noirq);

/**
 * acpi_subsys_resume_noirq - Run the device driver's "noirq" resume callback.
 * @dev: Device to handle.
 */
अटल पूर्णांक acpi_subsys_resume_noirq(काष्ठा device *dev)
अणु
	अगर (dev_pm_skip_resume(dev))
		वापस 0;

	वापस pm_generic_resume_noirq(dev);
पूर्ण

/**
 * acpi_subsys_resume_early - Resume device using ACPI.
 * @dev: Device to Resume.
 *
 * Use ACPI to put the given device पूर्णांकo the full-घातer state and carry out the
 * generic early resume procedure क्रम it during प्रणाली transition पूर्णांकo the
 * working state.
 */
अटल पूर्णांक acpi_subsys_resume_early(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	अगर (dev_pm_skip_resume(dev))
		वापस 0;

	ret = acpi_dev_resume(dev);
	वापस ret ? ret : pm_generic_resume_early(dev);
पूर्ण

/**
 * acpi_subsys_मुक्तze - Run the device driver's मुक्तze callback.
 * @dev: Device to handle.
 */
पूर्णांक acpi_subsys_मुक्तze(काष्ठा device *dev)
अणु
	/*
	 * Resume all runसमय-suspended devices beक्रमe creating a snapshot
	 * image of प्रणाली memory, because the restore kernel generally cannot
	 * be expected to always handle them consistently and they need to be
	 * put पूर्णांकo the runसमय-active metastate during प्रणाली resume anyway,
	 * so it is better to ensure that the state saved in the image will be
	 * always consistent with that.
	 */
	pm_runसमय_resume(dev);

	वापस pm_generic_मुक्तze(dev);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_subsys_मुक्तze);

/**
 * acpi_subsys_restore_early - Restore device using ACPI.
 * @dev: Device to restore.
 */
पूर्णांक acpi_subsys_restore_early(काष्ठा device *dev)
अणु
	पूर्णांक ret = acpi_dev_resume(dev);

	वापस ret ? ret : pm_generic_restore_early(dev);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_subsys_restore_early);

/**
 * acpi_subsys_घातeroff - Run the device driver's घातeroff callback.
 * @dev: Device to handle.
 *
 * Follow PCI and resume devices from runसमय suspend beक्रमe running their
 * प्रणाली घातeroff callbacks, unless the driver can cope with runसमय-suspended
 * devices during प्रणाली suspend and there are no ACPI-specअगरic reasons क्रम
 * resuming them.
 */
पूर्णांक acpi_subsys_घातeroff(काष्ठा device *dev)
अणु
	अगर (!dev_pm_test_driver_flags(dev, DPM_FLAG_SMART_SUSPEND) ||
	    acpi_dev_needs_resume(dev, ACPI_COMPANION(dev)))
		pm_runसमय_resume(dev);

	वापस pm_generic_घातeroff(dev);
पूर्ण
EXPORT_SYMBOL_GPL(acpi_subsys_घातeroff);

/**
 * acpi_subsys_घातeroff_late - Run the device driver's घातeroff callback.
 * @dev: Device to handle.
 *
 * Carry out the generic late घातeroff procedure क्रम @dev and use ACPI to put
 * it पूर्णांकo a low-घातer state during प्रणाली transition पूर्णांकo a sleep state.
 */
अटल पूर्णांक acpi_subsys_घातeroff_late(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	अगर (dev_pm_skip_suspend(dev))
		वापस 0;

	ret = pm_generic_घातeroff_late(dev);
	अगर (ret)
		वापस ret;

	वापस acpi_dev_suspend(dev, device_may_wakeup(dev));
पूर्ण

/**
 * acpi_subsys_घातeroff_noirq - Run the driver's "noirq" घातeroff callback.
 * @dev: Device to suspend.
 */
अटल पूर्णांक acpi_subsys_घातeroff_noirq(काष्ठा device *dev)
अणु
	अगर (dev_pm_skip_suspend(dev))
		वापस 0;

	वापस pm_generic_घातeroff_noirq(dev);
पूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

अटल काष्ठा dev_pm_करोमुख्य acpi_general_pm_करोमुख्य = अणु
	.ops = अणु
		.runसमय_suspend = acpi_subsys_runसमय_suspend,
		.runसमय_resume = acpi_subsys_runसमय_resume,
#अगर_घोषित CONFIG_PM_SLEEP
		.prepare = acpi_subsys_prepare,
		.complete = acpi_subsys_complete,
		.suspend = acpi_subsys_suspend,
		.suspend_late = acpi_subsys_suspend_late,
		.suspend_noirq = acpi_subsys_suspend_noirq,
		.resume_noirq = acpi_subsys_resume_noirq,
		.resume_early = acpi_subsys_resume_early,
		.मुक्तze = acpi_subsys_मुक्तze,
		.घातeroff = acpi_subsys_घातeroff,
		.घातeroff_late = acpi_subsys_घातeroff_late,
		.घातeroff_noirq = acpi_subsys_घातeroff_noirq,
		.restore_early = acpi_subsys_restore_early,
#पूर्ण_अगर
	पूर्ण,
पूर्ण;

/**
 * acpi_dev_pm_detach - Remove ACPI घातer management from the device.
 * @dev: Device to take care of.
 * @घातer_off: Whether or not to try to हटाओ घातer from the device.
 *
 * Remove the device from the general ACPI PM करोमुख्य and हटाओ its wakeup
 * notअगरier.  If @घातer_off is set, additionally हटाओ घातer from the device अगर
 * possible.
 *
 * Callers must ensure proper synchronization of this function with घातer
 * management callbacks.
 */
अटल व्योम acpi_dev_pm_detach(काष्ठा device *dev, bool घातer_off)
अणु
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);

	अगर (adev && dev->pm_करोमुख्य == &acpi_general_pm_करोमुख्य) अणु
		dev_pm_करोमुख्य_set(dev, शून्य);
		acpi_हटाओ_pm_notअगरier(adev);
		अगर (घातer_off) अणु
			/*
			 * If the device's PM QoS resume latency limit or flags
			 * have been exposed to user space, they have to be
			 * hidden at this poपूर्णांक, so that they करोn't affect the
			 * choice of the low-घातer state to put the device पूर्णांकo.
			 */
			dev_pm_qos_hide_latency_limit(dev);
			dev_pm_qos_hide_flags(dev);
			acpi_device_wakeup_disable(adev);
			acpi_dev_pm_low_घातer(dev, adev, ACPI_STATE_S0);
		पूर्ण
	पूर्ण
पूर्ण

/**
 * acpi_dev_pm_attach - Prepare device क्रम ACPI घातer management.
 * @dev: Device to prepare.
 * @घातer_on: Whether or not to घातer on the device.
 *
 * If @dev has a valid ACPI handle that has a valid काष्ठा acpi_device object
 * attached to it, install a wakeup notअगरication handler क्रम the device and
 * add it to the general ACPI PM करोमुख्य.  If @घातer_on is set, the device will
 * be put पूर्णांकo the ACPI D0 state beक्रमe the function वापसs.
 *
 * This assumes that the @dev's bus type uses generic घातer management callbacks
 * (or करोesn't use any घातer management callbacks at all).
 *
 * Callers must ensure proper synchronization of this function with घातer
 * management callbacks.
 */
पूर्णांक acpi_dev_pm_attach(काष्ठा device *dev, bool घातer_on)
अणु
	/*
	 * Skip devices whose ACPI companions match the device IDs below,
	 * because they require special घातer management handling incompatible
	 * with the generic ACPI PM करोमुख्य.
	 */
	अटल स्थिर काष्ठा acpi_device_id special_pm_ids[] = अणु
		अणु"PNP0C0B", पूर्ण, /* Generic ACPI fan */
		अणु"INT3404", पूर्ण, /* Fan */
		अणु"INTC1044", पूर्ण, /* Fan क्रम Tiger Lake generation */
		अणु"INTC1048", पूर्ण, /* Fan क्रम Alder Lake generation */
		अणुपूर्ण
	पूर्ण;
	काष्ठा acpi_device *adev = ACPI_COMPANION(dev);

	अगर (!adev || !acpi_match_device_ids(adev, special_pm_ids))
		वापस 0;

	/*
	 * Only attach the घातer करोमुख्य to the first device अगर the
	 * companion is shared by multiple. This is to prevent करोing घातer
	 * management twice.
	 */
	अगर (!acpi_device_is_first_physical_node(adev, dev))
		वापस 0;

	acpi_add_pm_notअगरier(adev, dev, acpi_pm_notअगरy_work_func);
	dev_pm_करोमुख्य_set(dev, &acpi_general_pm_करोमुख्य);
	अगर (घातer_on) अणु
		acpi_dev_pm_full_घातer(adev);
		acpi_device_wakeup_disable(adev);
	पूर्ण

	dev->pm_करोमुख्य->detach = acpi_dev_pm_detach;
	वापस 1;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_dev_pm_attach);
#पूर्ण_अगर /* CONFIG_PM */
