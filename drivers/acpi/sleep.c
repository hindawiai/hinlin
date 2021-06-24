<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * sleep.c - ACPI sleep support.
 *
 * Copyright (c) 2005 Alexey Starikovskiy <alexey.y.starikovskiy@पूर्णांकel.com>
 * Copyright (c) 2004 David Shaohua Li <shaohua.li@पूर्णांकel.com>
 * Copyright (c) 2000-2003 Patrick Mochel
 * Copyright (c) 2003 Open Source Development Lab
 */

#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/dmi.h>
#समावेश <linux/device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/suspend.h>
#समावेश <linux/reboot.h>
#समावेश <linux/acpi.h>
#समावेश <linux/module.h>
#समावेश <linux/syscore_ops.h>
#समावेश <यंत्र/पन.स>
#समावेश <trace/events/घातer.h>

#समावेश "internal.h"
#समावेश "sleep.h"

/*
 * Some HW-full platक्रमms करो not have _S5, so they may need
 * to leverage efi घातer off क्रम a shutकरोwn.
 */
bool acpi_no_s5;
अटल u8 sleep_states[ACPI_S_STATE_COUNT];

अटल व्योम acpi_sleep_tts_चयन(u32 acpi_state)
अणु
	acpi_status status;

	status = acpi_execute_simple_method(शून्य, "\\_TTS", acpi_state);
	अगर (ACPI_FAILURE(status) && status != AE_NOT_FOUND) अणु
		/*
		 * OS can't evaluate the _TTS object correctly. Some warning
		 * message will be prपूर्णांकed. But it won't अवरोध anything.
		 */
		prपूर्णांकk(KERN_NOTICE "Failure in evaluating _TTS object\n");
	पूर्ण
पूर्ण

अटल पूर्णांक tts_notअगरy_reboot(काष्ठा notअगरier_block *this,
			अचिन्हित दीर्घ code, व्योम *x)
अणु
	acpi_sleep_tts_चयन(ACPI_STATE_S5);
	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block tts_notअगरier = अणु
	.notअगरier_call	= tts_notअगरy_reboot,
	.next		= शून्य,
	.priority	= 0,
पूर्ण;

अटल पूर्णांक acpi_sleep_prepare(u32 acpi_state)
अणु
#अगर_घोषित CONFIG_ACPI_SLEEP
	अचिन्हित दीर्घ acpi_wakeup_address;

	/* करो we have a wakeup address क्रम S2 and S3? */
	अगर (acpi_state == ACPI_STATE_S3) अणु
		acpi_wakeup_address = acpi_get_wakeup_address();
		अगर (!acpi_wakeup_address)
			वापस -EFAULT;
		acpi_set_waking_vector(acpi_wakeup_address);

	पूर्ण
	ACPI_FLUSH_CPU_CACHE();
#पूर्ण_अगर
	prपूर्णांकk(KERN_INFO PREFIX "Preparing to enter system sleep state S%d\n",
		acpi_state);
	acpi_enable_wakeup_devices(acpi_state);
	acpi_enter_sleep_state_prep(acpi_state);
	वापस 0;
पूर्ण

bool acpi_sleep_state_supported(u8 sleep_state)
अणु
	acpi_status status;
	u8 type_a, type_b;

	status = acpi_get_sleep_type_data(sleep_state, &type_a, &type_b);
	वापस ACPI_SUCCESS(status) && (!acpi_gbl_reduced_hardware
		|| (acpi_gbl_FADT.sleep_control.address
			&& acpi_gbl_FADT.sleep_status.address));
पूर्ण

#अगर_घोषित CONFIG_ACPI_SLEEP
अटल u32 acpi_target_sleep_state = ACPI_STATE_S0;

u32 acpi_target_प्रणाली_state(व्योम)
अणु
	वापस acpi_target_sleep_state;
पूर्ण
EXPORT_SYMBOL_GPL(acpi_target_प्रणाली_state);

अटल bool pwr_btn_event_pending;

/*
 * The ACPI specअगरication wants us to save NVS memory regions during hibernation
 * and to restore them during the subsequent resume.  Winकरोws करोes that also क्रम
 * suspend to RAM.  However, it is known that this mechanism करोes not work on
 * all machines, so we allow the user to disable it with the help of the
 * 'acpi_sleep=nonvs' kernel command line option.
 */
अटल bool nvs_nosave;

व्योम __init acpi_nvs_nosave(व्योम)
अणु
	nvs_nosave = true;
पूर्ण

/*
 * The ACPI specअगरication wants us to save NVS memory regions during hibernation
 * but says nothing about saving NVS during S3.  Not all versions of Winकरोws
 * save NVS on S3 suspend either, and it is clear that not all प्रणालीs need
 * NVS to be saved at S3 समय.  To improve suspend/resume समय, allow the
 * user to disable saving NVS on S3 अगर their प्रणाली करोes not require it, but
 * जारी to save/restore NVS क्रम S4 as specअगरied.
 */
अटल bool nvs_nosave_s3;

व्योम __init acpi_nvs_nosave_s3(व्योम)
अणु
	nvs_nosave_s3 = true;
पूर्ण

अटल पूर्णांक __init init_nvs_save_s3(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	nvs_nosave_s3 = false;
	वापस 0;
पूर्ण

/*
 * ACPI 1.0 wants us to execute _PTS beक्रमe suspending devices, so we allow the
 * user to request that behavior by using the 'acpi_old_suspend_ordering'
 * kernel command line option that causes the following variable to be set.
 */
अटल bool old_suspend_ordering;

व्योम __init acpi_old_suspend_ordering(व्योम)
अणु
	old_suspend_ordering = true;
पूर्ण

अटल पूर्णांक __init init_old_suspend_ordering(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	acpi_old_suspend_ordering();
	वापस 0;
पूर्ण

अटल पूर्णांक __init init_nvs_nosave(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	acpi_nvs_nosave();
	वापस 0;
पूर्ण

bool acpi_sleep_शेष_s3;

अटल पूर्णांक __init init_शेष_s3(स्थिर काष्ठा dmi_प्रणाली_id *d)
अणु
	acpi_sleep_शेष_s3 = true;
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा dmi_प्रणाली_id acpisleep_dmi_table[] __initस्थिर = अणु
	अणु
	.callback = init_old_suspend_ordering,
	.ident = "Abit KN9 (nForce4 variant)",
	.matches = अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "http://www.abit.com.tw/"),
		DMI_MATCH(DMI_BOARD_NAME, "KN9 Series(NF-CK804)"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_old_suspend_ordering,
	.ident = "HP xw4600 Workstation",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Hewlett-Packard"),
		DMI_MATCH(DMI_PRODUCT_NAME, "HP xw4600 Workstation"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_old_suspend_ordering,
	.ident = "Asus Pundit P1-AH2 (M2N8L motherboard)",
	.matches = अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTek Computer INC."),
		DMI_MATCH(DMI_BOARD_NAME, "M2N8L"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_old_suspend_ordering,
	.ident = "Panasonic CF51-2L",
	.matches = अणु
		DMI_MATCH(DMI_BOARD_VENDOR,
				"Matsushita Electric Industrial Co.,Ltd."),
		DMI_MATCH(DMI_BOARD_NAME, "CF51-2L"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_nosave,
	.ident = "Sony Vaio VGN-FW41E_H",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		DMI_MATCH(DMI_PRODUCT_NAME, "VGN-FW41E_H"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_nosave,
	.ident = "Sony Vaio VGN-FW21E",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		DMI_MATCH(DMI_PRODUCT_NAME, "VGN-FW21E"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_nosave,
	.ident = "Sony Vaio VGN-FW21M",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		DMI_MATCH(DMI_PRODUCT_NAME, "VGN-FW21M"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_nosave,
	.ident = "Sony Vaio VPCEB17FX",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		DMI_MATCH(DMI_PRODUCT_NAME, "VPCEB17FX"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_nosave,
	.ident = "Sony Vaio VGN-SR11M",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		DMI_MATCH(DMI_PRODUCT_NAME, "VGN-SR11M"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_nosave,
	.ident = "Everex StepNote Series",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Everex Systems, Inc."),
		DMI_MATCH(DMI_PRODUCT_NAME, "Everex StepNote Series"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_nosave,
	.ident = "Sony Vaio VPCEB1Z1E",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		DMI_MATCH(DMI_PRODUCT_NAME, "VPCEB1Z1E"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_nosave,
	.ident = "Sony Vaio VGN-NW130D",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		DMI_MATCH(DMI_PRODUCT_NAME, "VGN-NW130D"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_nosave,
	.ident = "Sony Vaio VPCCW29FX",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		DMI_MATCH(DMI_PRODUCT_NAME, "VPCCW29FX"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_nosave,
	.ident = "Averatec AV1020-ED2",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "AVERATEC"),
		DMI_MATCH(DMI_PRODUCT_NAME, "1000 Series"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_old_suspend_ordering,
	.ident = "Asus A8N-SLI DELUXE",
	.matches = अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
		DMI_MATCH(DMI_BOARD_NAME, "A8N-SLI DELUXE"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_old_suspend_ordering,
	.ident = "Asus A8N-SLI Premium",
	.matches = अणु
		DMI_MATCH(DMI_BOARD_VENDOR, "ASUSTeK Computer INC."),
		DMI_MATCH(DMI_BOARD_NAME, "A8N-SLI Premium"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_nosave,
	.ident = "Sony Vaio VGN-SR26GN_P",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		DMI_MATCH(DMI_PRODUCT_NAME, "VGN-SR26GN_P"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_nosave,
	.ident = "Sony Vaio VPCEB1S1E",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		DMI_MATCH(DMI_PRODUCT_NAME, "VPCEB1S1E"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_nosave,
	.ident = "Sony Vaio VGN-FW520F",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "Sony Corporation"),
		DMI_MATCH(DMI_PRODUCT_NAME, "VGN-FW520F"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_nosave,
	.ident = "Asus K54C",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
		DMI_MATCH(DMI_PRODUCT_NAME, "K54C"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_nosave,
	.ident = "Asus K54HR",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK Computer Inc."),
		DMI_MATCH(DMI_PRODUCT_NAME, "K54HR"),
		पूर्ण,
	पूर्ण,
	अणु
	.callback = init_nvs_save_s3,
	.ident = "Asus 1025C",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "ASUSTeK COMPUTER INC."),
		DMI_MATCH(DMI_PRODUCT_NAME, "1025C"),
		पूर्ण,
	पूर्ण,
	/*
	 * https://bugzilla.kernel.org/show_bug.cgi?id=189431
	 * Lenovo G50-45 is a platक्रमm later than 2012, but needs nvs memory
	 * saving during S3.
	 */
	अणु
	.callback = init_nvs_save_s3,
	.ident = "Lenovo G50-45",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		DMI_MATCH(DMI_PRODUCT_NAME, "80E3"),
		पूर्ण,
	पूर्ण,
	/*
	 * ThinkPad X1 Tablet(2016) cannot करो suspend-to-idle using
	 * the Low Power S0 Idle firmware पूर्णांकerface (see
	 * https://bugzilla.kernel.org/show_bug.cgi?id=199057).
	 */
	अणु
	.callback = init_शेष_s3,
	.ident = "ThinkPad X1 Tablet(2016)",
	.matches = अणु
		DMI_MATCH(DMI_SYS_VENDOR, "LENOVO"),
		DMI_MATCH(DMI_PRODUCT_NAME, "20GGA00L00"),
		पूर्ण,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल bool ignore_blacklist;

व्योम __init acpi_sleep_no_blacklist(व्योम)
अणु
	ignore_blacklist = true;
पूर्ण

अटल व्योम __init acpi_sleep_dmi_check(व्योम)
अणु
	अगर (ignore_blacklist)
		वापस;

	अगर (dmi_get_bios_year() >= 2012)
		acpi_nvs_nosave_s3();

	dmi_check_प्रणाली(acpisleep_dmi_table);
पूर्ण

/**
 * acpi_pm_मुक्तze - Disable the GPEs and suspend EC transactions.
 */
अटल पूर्णांक acpi_pm_मुक्तze(व्योम)
अणु
	acpi_disable_all_gpes();
	acpi_os_रुको_events_complete();
	acpi_ec_block_transactions();
	वापस 0;
पूर्ण

/**
 * acpi_pre_suspend - Enable wakeup devices, "freeze" EC and save NVS.
 */
अटल पूर्णांक acpi_pm_pre_suspend(व्योम)
अणु
	acpi_pm_मुक्तze();
	वापस suspend_nvs_save();
पूर्ण

/**
 *	__acpi_pm_prepare - Prepare the platक्रमm to enter the target state.
 *
 *	If necessary, set the firmware waking vector and करो arch-specअगरic
 *	nastiness to get the wakeup code to the waking vector.
 */
अटल पूर्णांक __acpi_pm_prepare(व्योम)
अणु
	पूर्णांक error = acpi_sleep_prepare(acpi_target_sleep_state);
	अगर (error)
		acpi_target_sleep_state = ACPI_STATE_S0;

	वापस error;
पूर्ण

/**
 *	acpi_pm_prepare - Prepare the platक्रमm to enter the target sleep
 *		state and disable the GPEs.
 */
अटल पूर्णांक acpi_pm_prepare(व्योम)
अणु
	पूर्णांक error = __acpi_pm_prepare();
	अगर (!error)
		error = acpi_pm_pre_suspend();

	वापस error;
पूर्ण

/**
 *	acpi_pm_finish - Inकाष्ठा the platक्रमm to leave a sleep state.
 *
 *	This is called after we wake back up (or अगर entering the sleep state
 *	failed).
 */
अटल व्योम acpi_pm_finish(व्योम)
अणु
	काष्ठा acpi_device *pwr_btn_adev;
	u32 acpi_state = acpi_target_sleep_state;

	acpi_ec_unblock_transactions();
	suspend_nvs_मुक्त();

	अगर (acpi_state == ACPI_STATE_S0)
		वापस;

	prपूर्णांकk(KERN_INFO PREFIX "Waking up from system sleep state S%d\n",
		acpi_state);
	acpi_disable_wakeup_devices(acpi_state);
	acpi_leave_sleep_state(acpi_state);

	/* reset firmware waking vector */
	acpi_set_waking_vector(0);

	acpi_target_sleep_state = ACPI_STATE_S0;

	acpi_resume_घातer_resources();

	/* If we were woken with the fixed घातer button, provide a small
	 * hपूर्णांक to userspace in the क्रमm of a wakeup event on the fixed घातer
	 * button device (अगर it can be found).
	 *
	 * We delay the event generation til now, as the PM layer requires
	 * समयkeeping to be running beक्रमe we generate events. */
	अगर (!pwr_btn_event_pending)
		वापस;

	pwr_btn_event_pending = false;
	pwr_btn_adev = acpi_dev_get_first_match_dev(ACPI_BUTTON_HID_POWERF,
						    शून्य, -1);
	अगर (pwr_btn_adev) अणु
		pm_wakeup_event(&pwr_btn_adev->dev, 0);
		acpi_dev_put(pwr_btn_adev);
	पूर्ण
पूर्ण

/**
 * acpi_pm_start - Start प्रणाली PM transition.
 */
अटल व्योम acpi_pm_start(u32 acpi_state)
अणु
	acpi_target_sleep_state = acpi_state;
	acpi_sleep_tts_चयन(acpi_target_sleep_state);
	acpi_scan_lock_acquire();
पूर्ण

/**
 * acpi_pm_end - Finish up प्रणाली PM transition.
 */
अटल व्योम acpi_pm_end(व्योम)
अणु
	acpi_turn_off_unused_घातer_resources(false);
	acpi_scan_lock_release();
	/*
	 * This is necessary in हाल acpi_pm_finish() is not called during a
	 * failing transition to a sleep state.
	 */
	acpi_target_sleep_state = ACPI_STATE_S0;
	acpi_sleep_tts_चयन(acpi_target_sleep_state);
पूर्ण
#अन्यथा /* !CONFIG_ACPI_SLEEP */
#घोषणा sleep_no_lps0	(1)
#घोषणा acpi_target_sleep_state	ACPI_STATE_S0
#घोषणा acpi_sleep_शेष_s3	(1)
अटल अंतरभूत व्योम acpi_sleep_dmi_check(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_ACPI_SLEEP */

#अगर_घोषित CONFIG_SUSPEND
अटल u32 acpi_suspend_states[] = अणु
	[PM_SUSPEND_ON] = ACPI_STATE_S0,
	[PM_SUSPEND_STANDBY] = ACPI_STATE_S1,
	[PM_SUSPEND_MEM] = ACPI_STATE_S3,
	[PM_SUSPEND_MAX] = ACPI_STATE_S5
पूर्ण;

/**
 *	acpi_suspend_begin - Set the target प्रणाली sleep state to the state
 *		associated with given @pm_state, अगर supported.
 */
अटल पूर्णांक acpi_suspend_begin(suspend_state_t pm_state)
अणु
	u32 acpi_state = acpi_suspend_states[pm_state];
	पूर्णांक error;

	error = (nvs_nosave || nvs_nosave_s3) ? 0 : suspend_nvs_alloc();
	अगर (error)
		वापस error;

	अगर (!sleep_states[acpi_state]) अणु
		pr_err("ACPI does not support sleep state S%u\n", acpi_state);
		वापस -ENOSYS;
	पूर्ण
	अगर (acpi_state > ACPI_STATE_S1)
		pm_set_suspend_via_firmware();

	acpi_pm_start(acpi_state);
	वापस 0;
पूर्ण

/**
 *	acpi_suspend_enter - Actually enter a sleep state.
 *	@pm_state: ignored
 *
 *	Flush caches and go to sleep. For STR we have to call arch-specअगरic
 *	assembly, which in turn call acpi_enter_sleep_state().
 *	It's unfortunate, but it works. Please fix if you're feeling frisky.
 */
अटल पूर्णांक acpi_suspend_enter(suspend_state_t pm_state)
अणु
	acpi_status status = AE_OK;
	u32 acpi_state = acpi_target_sleep_state;
	पूर्णांक error;

	ACPI_FLUSH_CPU_CACHE();

	trace_suspend_resume(TPS("acpi_suspend"), acpi_state, true);
	चयन (acpi_state) अणु
	हाल ACPI_STATE_S1:
		barrier();
		status = acpi_enter_sleep_state(acpi_state);
		अवरोध;

	हाल ACPI_STATE_S3:
		अगर (!acpi_suspend_lowlevel)
			वापस -ENOSYS;
		error = acpi_suspend_lowlevel();
		अगर (error)
			वापस error;
		pr_info(PREFIX "Low-level resume complete\n");
		pm_set_resume_via_firmware();
		अवरोध;
	पूर्ण
	trace_suspend_resume(TPS("acpi_suspend"), acpi_state, false);

	/* This violates the spec but is required क्रम bug compatibility. */
	acpi_ग_लिखो_bit_रेजिस्टर(ACPI_BITREG_SCI_ENABLE, 1);

	/* Reprogram control रेजिस्टरs */
	acpi_leave_sleep_state_prep(acpi_state);

	/* ACPI 3.0 specs (P62) says that it's the responsibility
	 * of the OSPM to clear the status bit [ implying that the
	 * POWER_BUTTON event should not reach userspace ]
	 *
	 * However, we करो generate a small hपूर्णांक क्रम userspace in the क्रमm of
	 * a wakeup event. We flag this condition क्रम now and generate the
	 * event later, as we're currently too early in resume to be able to
	 * generate wakeup events.
	 */
	अगर (ACPI_SUCCESS(status) && (acpi_state == ACPI_STATE_S3)) अणु
		acpi_event_status pwr_btn_status = ACPI_EVENT_FLAG_DISABLED;

		acpi_get_event_status(ACPI_EVENT_POWER_BUTTON, &pwr_btn_status);

		अगर (pwr_btn_status & ACPI_EVENT_FLAG_STATUS_SET) अणु
			acpi_clear_event(ACPI_EVENT_POWER_BUTTON);
			/* Flag क्रम later */
			pwr_btn_event_pending = true;
		पूर्ण
	पूर्ण

	/*
	 * Disable and clear GPE status beक्रमe पूर्णांकerrupt is enabled. Some GPEs
	 * (like wakeup GPE) haven't handler, this can aव्योम such GPE misfire.
	 * acpi_leave_sleep_state will reenable specअगरic GPEs later
	 */
	acpi_disable_all_gpes();
	/* Allow EC transactions to happen. */
	acpi_ec_unblock_transactions();

	suspend_nvs_restore();

	वापस ACPI_SUCCESS(status) ? 0 : -EFAULT;
पूर्ण

अटल पूर्णांक acpi_suspend_state_valid(suspend_state_t pm_state)
अणु
	u32 acpi_state;

	चयन (pm_state) अणु
	हाल PM_SUSPEND_ON:
	हाल PM_SUSPEND_STANDBY:
	हाल PM_SUSPEND_MEM:
		acpi_state = acpi_suspend_states[pm_state];

		वापस sleep_states[acpi_state];
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा platक्रमm_suspend_ops acpi_suspend_ops = अणु
	.valid = acpi_suspend_state_valid,
	.begin = acpi_suspend_begin,
	.prepare_late = acpi_pm_prepare,
	.enter = acpi_suspend_enter,
	.wake = acpi_pm_finish,
	.end = acpi_pm_end,
पूर्ण;

/**
 *	acpi_suspend_begin_old - Set the target प्रणाली sleep state to the
 *		state associated with given @pm_state, अगर supported, and
 *		execute the _PTS control method.  This function is used अगर the
 *		pre-ACPI 2.0 suspend ordering has been requested.
 */
अटल पूर्णांक acpi_suspend_begin_old(suspend_state_t pm_state)
अणु
	पूर्णांक error = acpi_suspend_begin(pm_state);
	अगर (!error)
		error = __acpi_pm_prepare();

	वापस error;
पूर्ण

/*
 * The following callbacks are used अगर the pre-ACPI 2.0 suspend ordering has
 * been requested.
 */
अटल स्थिर काष्ठा platक्रमm_suspend_ops acpi_suspend_ops_old = अणु
	.valid = acpi_suspend_state_valid,
	.begin = acpi_suspend_begin_old,
	.prepare_late = acpi_pm_pre_suspend,
	.enter = acpi_suspend_enter,
	.wake = acpi_pm_finish,
	.end = acpi_pm_end,
	.recover = acpi_pm_finish,
पूर्ण;

अटल bool s2idle_wakeup;

पूर्णांक acpi_s2idle_begin(व्योम)
अणु
	acpi_scan_lock_acquire();
	वापस 0;
पूर्ण

पूर्णांक acpi_s2idle_prepare(व्योम)
अणु
	अगर (acpi_sci_irq_valid()) अणु
		enable_irq_wake(acpi_sci_irq);
		acpi_ec_set_gpe_wake_mask(ACPI_GPE_ENABLE);
	पूर्ण

	acpi_enable_wakeup_devices(ACPI_STATE_S0);

	/* Change the configuration of GPEs to aव्योम spurious wakeup. */
	acpi_enable_all_wakeup_gpes();
	acpi_os_रुको_events_complete();

	s2idle_wakeup = true;
	वापस 0;
पूर्ण

bool acpi_s2idle_wake(व्योम)
अणु
	अगर (!acpi_sci_irq_valid())
		वापस pm_wakeup_pending();

	जबतक (pm_wakeup_pending()) अणु
		/*
		 * If IRQD_WAKEUP_ARMED is set क्रम the SCI at this poपूर्णांक, the
		 * SCI has not triggered जबतक suspended, so bail out (the
		 * wakeup is pending anyway and the SCI is not the source of
		 * it).
		 */
		अगर (irqd_is_wakeup_armed(irq_get_irq_data(acpi_sci_irq))) अणु
			pm_pr_dbg("Wakeup unrelated to ACPI SCI\n");
			वापस true;
		पूर्ण

		/*
		 * If the status bit of any enabled fixed event is set, the
		 * wakeup is regarded as valid.
		 */
		अगर (acpi_any_fixed_event_status_set()) अणु
			pm_pr_dbg("ACPI fixed event wakeup\n");
			वापस true;
		पूर्ण

		/* Check wakeups from drivers sharing the SCI. */
		अगर (acpi_check_wakeup_handlers()) अणु
			pm_pr_dbg("ACPI custom handler wakeup\n");
			वापस true;
		पूर्ण

		/* Check non-EC GPE wakeups and dispatch the EC GPE. */
		अगर (acpi_ec_dispatch_gpe()) अणु
			pm_pr_dbg("ACPI non-EC GPE wakeup\n");
			वापस true;
		पूर्ण

		/*
		 * Cancel the SCI wakeup and process all pending events in हाल
		 * there are any wakeup ones in there.
		 *
		 * Note that अगर any non-EC GPEs are active at this poपूर्णांक, the
		 * SCI will retrigger after the rearming below, so no events
		 * should be missed by canceling the wakeup here.
		 */
		pm_प्रणाली_cancel_wakeup();
		acpi_os_रुको_events_complete();

		/*
		 * The SCI is in the "suspended" state now and it cannot produce
		 * new wakeup events till the rearming below, so अगर any of them
		 * are pending here, they must be resulting from the processing
		 * of EC events above or coming from somewhere अन्यथा.
		 */
		अगर (pm_wakeup_pending()) अणु
			pm_pr_dbg("Wakeup after ACPI Notify sync\n");
			वापस true;
		पूर्ण

		rearm_wake_irq(acpi_sci_irq);
	पूर्ण

	वापस false;
पूर्ण

व्योम acpi_s2idle_restore(व्योम)
अणु
	/*
	 * Drain pending events beक्रमe restoring the working-state configuration
	 * of GPEs.
	 */
	acpi_os_रुको_events_complete(); /* synchronize GPE processing */
	acpi_ec_flush_work(); /* flush the EC driver's workqueues */
	acpi_os_रुको_events_complete(); /* synchronize Notअगरy handling */

	s2idle_wakeup = false;

	acpi_enable_all_runसमय_gpes();

	acpi_disable_wakeup_devices(ACPI_STATE_S0);

	अगर (acpi_sci_irq_valid()) अणु
		acpi_ec_set_gpe_wake_mask(ACPI_GPE_DISABLE);
		disable_irq_wake(acpi_sci_irq);
	पूर्ण
पूर्ण

व्योम acpi_s2idle_end(व्योम)
अणु
	acpi_scan_lock_release();
पूर्ण

अटल स्थिर काष्ठा platक्रमm_s2idle_ops acpi_s2idle_ops = अणु
	.begin = acpi_s2idle_begin,
	.prepare = acpi_s2idle_prepare,
	.wake = acpi_s2idle_wake,
	.restore = acpi_s2idle_restore,
	.end = acpi_s2idle_end,
पूर्ण;

व्योम __weak acpi_s2idle_setup(व्योम)
अणु
	s2idle_set_ops(&acpi_s2idle_ops);
पूर्ण

अटल व्योम acpi_sleep_suspend_setup(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = ACPI_STATE_S1; i < ACPI_STATE_S4; i++)
		अगर (acpi_sleep_state_supported(i))
			sleep_states[i] = 1;

	suspend_set_ops(old_suspend_ordering ?
		&acpi_suspend_ops_old : &acpi_suspend_ops);

	acpi_s2idle_setup();
पूर्ण

#अन्यथा /* !CONFIG_SUSPEND */
#घोषणा s2idle_wakeup		(false)
अटल अंतरभूत व्योम acpi_sleep_suspend_setup(व्योम) अणुपूर्ण
#पूर्ण_अगर /* !CONFIG_SUSPEND */

bool acpi_s2idle_wakeup(व्योम)
अणु
	वापस s2idle_wakeup;
पूर्ण

#अगर_घोषित CONFIG_PM_SLEEP
अटल u32 saved_bm_rld;

अटल पूर्णांक  acpi_save_bm_rld(व्योम)
अणु
	acpi_पढ़ो_bit_रेजिस्टर(ACPI_BITREG_BUS_MASTER_RLD, &saved_bm_rld);
	वापस 0;
पूर्ण

अटल व्योम  acpi_restore_bm_rld(व्योम)
अणु
	u32 resumed_bm_rld = 0;

	acpi_पढ़ो_bit_रेजिस्टर(ACPI_BITREG_BUS_MASTER_RLD, &resumed_bm_rld);
	अगर (resumed_bm_rld == saved_bm_rld)
		वापस;

	acpi_ग_लिखो_bit_रेजिस्टर(ACPI_BITREG_BUS_MASTER_RLD, saved_bm_rld);
पूर्ण

अटल काष्ठा syscore_ops acpi_sleep_syscore_ops = अणु
	.suspend = acpi_save_bm_rld,
	.resume = acpi_restore_bm_rld,
पूर्ण;

अटल व्योम acpi_sleep_syscore_init(व्योम)
अणु
	रेजिस्टर_syscore_ops(&acpi_sleep_syscore_ops);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम acpi_sleep_syscore_init(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PM_SLEEP */

#अगर_घोषित CONFIG_HIBERNATION
अटल अचिन्हित दीर्घ s4_hardware_signature;
अटल काष्ठा acpi_table_facs *facs;
अटल bool nosigcheck;

व्योम __init acpi_no_s4_hw_signature(व्योम)
अणु
	nosigcheck = true;
पूर्ण

अटल पूर्णांक acpi_hibernation_begin(pm_message_t stage)
अणु
	अगर (!nvs_nosave) अणु
		पूर्णांक error = suspend_nvs_alloc();
		अगर (error)
			वापस error;
	पूर्ण

	अगर (stage.event == PM_EVENT_HIBERNATE)
		pm_set_suspend_via_firmware();

	acpi_pm_start(ACPI_STATE_S4);
	वापस 0;
पूर्ण

अटल पूर्णांक acpi_hibernation_enter(व्योम)
अणु
	acpi_status status = AE_OK;

	ACPI_FLUSH_CPU_CACHE();

	/* This shouldn't वापस.  If it वापसs, we have a problem */
	status = acpi_enter_sleep_state(ACPI_STATE_S4);
	/* Reprogram control रेजिस्टरs */
	acpi_leave_sleep_state_prep(ACPI_STATE_S4);

	वापस ACPI_SUCCESS(status) ? 0 : -EFAULT;
पूर्ण

अटल व्योम acpi_hibernation_leave(व्योम)
अणु
	pm_set_resume_via_firmware();
	/*
	 * If ACPI is not enabled by the BIOS and the boot kernel, we need to
	 * enable it here.
	 */
	acpi_enable();
	/* Reprogram control रेजिस्टरs */
	acpi_leave_sleep_state_prep(ACPI_STATE_S4);
	/* Check the hardware signature */
	अगर (facs && s4_hardware_signature != facs->hardware_signature)
		pr_crit("ACPI: Hardware changed while hibernated, success doubtful!\n");
	/* Restore the NVS memory area */
	suspend_nvs_restore();
	/* Allow EC transactions to happen. */
	acpi_ec_unblock_transactions();
पूर्ण

अटल व्योम acpi_pm_thaw(व्योम)
अणु
	acpi_ec_unblock_transactions();
	acpi_enable_all_runसमय_gpes();
पूर्ण

अटल स्थिर काष्ठा platक्रमm_hibernation_ops acpi_hibernation_ops = अणु
	.begin = acpi_hibernation_begin,
	.end = acpi_pm_end,
	.pre_snapshot = acpi_pm_prepare,
	.finish = acpi_pm_finish,
	.prepare = acpi_pm_prepare,
	.enter = acpi_hibernation_enter,
	.leave = acpi_hibernation_leave,
	.pre_restore = acpi_pm_मुक्तze,
	.restore_cleanup = acpi_pm_thaw,
पूर्ण;

/**
 *	acpi_hibernation_begin_old - Set the target प्रणाली sleep state to
 *		ACPI_STATE_S4 and execute the _PTS control method.  This
 *		function is used अगर the pre-ACPI 2.0 suspend ordering has been
 *		requested.
 */
अटल पूर्णांक acpi_hibernation_begin_old(pm_message_t stage)
अणु
	पूर्णांक error;
	/*
	 * The _TTS object should always be evaluated beक्रमe the _PTS object.
	 * When the old_suspended_ordering is true, the _PTS object is
	 * evaluated in the acpi_sleep_prepare.
	 */
	acpi_sleep_tts_चयन(ACPI_STATE_S4);

	error = acpi_sleep_prepare(ACPI_STATE_S4);
	अगर (error)
		वापस error;

	अगर (!nvs_nosave) अणु
		error = suspend_nvs_alloc();
		अगर (error)
			वापस error;
	पूर्ण

	अगर (stage.event == PM_EVENT_HIBERNATE)
		pm_set_suspend_via_firmware();

	acpi_target_sleep_state = ACPI_STATE_S4;
	acpi_scan_lock_acquire();
	वापस 0;
पूर्ण

/*
 * The following callbacks are used अगर the pre-ACPI 2.0 suspend ordering has
 * been requested.
 */
अटल स्थिर काष्ठा platक्रमm_hibernation_ops acpi_hibernation_ops_old = अणु
	.begin = acpi_hibernation_begin_old,
	.end = acpi_pm_end,
	.pre_snapshot = acpi_pm_pre_suspend,
	.prepare = acpi_pm_मुक्तze,
	.finish = acpi_pm_finish,
	.enter = acpi_hibernation_enter,
	.leave = acpi_hibernation_leave,
	.pre_restore = acpi_pm_मुक्तze,
	.restore_cleanup = acpi_pm_thaw,
	.recover = acpi_pm_finish,
पूर्ण;

अटल व्योम acpi_sleep_hibernate_setup(व्योम)
अणु
	अगर (!acpi_sleep_state_supported(ACPI_STATE_S4))
		वापस;

	hibernation_set_ops(old_suspend_ordering ?
			&acpi_hibernation_ops_old : &acpi_hibernation_ops);
	sleep_states[ACPI_STATE_S4] = 1;
	अगर (nosigcheck)
		वापस;

	acpi_get_table(ACPI_SIG_FACS, 1, (काष्ठा acpi_table_header **)&facs);
	अगर (facs)
		s4_hardware_signature = facs->hardware_signature;
पूर्ण
#अन्यथा /* !CONFIG_HIBERNATION */
अटल अंतरभूत व्योम acpi_sleep_hibernate_setup(व्योम) अणुपूर्ण
#पूर्ण_अगर /* !CONFIG_HIBERNATION */

अटल व्योम acpi_घातer_off_prepare(व्योम)
अणु
	/* Prepare to घातer off the प्रणाली */
	acpi_sleep_prepare(ACPI_STATE_S5);
	acpi_disable_all_gpes();
	acpi_os_रुको_events_complete();
पूर्ण

अटल व्योम acpi_घातer_off(व्योम)
अणु
	/* acpi_sleep_prepare(ACPI_STATE_S5) should have alपढ़ोy been called */
	prपूर्णांकk(KERN_DEBUG "%s called\n", __func__);
	local_irq_disable();
	acpi_enter_sleep_state(ACPI_STATE_S5);
पूर्ण

पूर्णांक __init acpi_sleep_init(व्योम)
अणु
	अक्षर supported[ACPI_S_STATE_COUNT * 3 + 1];
	अक्षर *pos = supported;
	पूर्णांक i;

	acpi_sleep_dmi_check();

	sleep_states[ACPI_STATE_S0] = 1;

	acpi_sleep_syscore_init();
	acpi_sleep_suspend_setup();
	acpi_sleep_hibernate_setup();

	अगर (acpi_sleep_state_supported(ACPI_STATE_S5)) अणु
		sleep_states[ACPI_STATE_S5] = 1;
		pm_घातer_off_prepare = acpi_घातer_off_prepare;
		pm_घातer_off = acpi_घातer_off;
	पूर्ण अन्यथा अणु
		acpi_no_s5 = true;
	पूर्ण

	supported[0] = 0;
	क्रम (i = 0; i < ACPI_S_STATE_COUNT; i++) अणु
		अगर (sleep_states[i])
			pos += प्र_लिखो(pos, " S%d", i);
	पूर्ण
	pr_info(PREFIX "(supports%s)\n", supported);

	/*
	 * Register the tts_notअगरier to reboot notअगरier list so that the _TTS
	 * object can also be evaluated when the प्रणाली enters S5.
	 */
	रेजिस्टर_reboot_notअगरier(&tts_notअगरier);
	वापस 0;
पूर्ण
