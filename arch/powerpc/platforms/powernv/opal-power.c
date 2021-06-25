<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * PowerNV OPAL घातer control क्रम graceful shutकरोwn handling
 *
 * Copyright 2015 IBM Corp.
 */

#घोषणा pr_fmt(fmt)	"opal-power: "	fmt

#समावेश <linux/kernel.h>
#समावेश <linux/reboot.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of.h>

#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/machdep.h>

#घोषणा SOFT_OFF 0x00
#घोषणा SOFT_REBOOT 0x01

/* Detect EPOW event */
अटल bool detect_eघात(व्योम)
अणु
	u16 eघात;
	पूर्णांक i, rc;
	__be16 eघात_classes;
	__be16 opal_eघात_status[OPAL_SYSEPOW_MAX] = अणु0पूर्ण;

	/*
	* Check क्रम EPOW event. Kernel sends supported EPOW classes info
	* to OPAL. OPAL वापसs EPOW info aदीर्घ with classes present.
	*/
	eघात_classes = cpu_to_be16(OPAL_SYSEPOW_MAX);
	rc = opal_get_eघात_status(opal_eघात_status, &eघात_classes);
	अगर (rc != OPAL_SUCCESS) अणु
		pr_err("Failed to get EPOW event information\n");
		वापस false;
	पूर्ण

	/* Look क्रम EPOW events present */
	क्रम (i = 0; i < be16_to_cpu(eघात_classes); i++) अणु
		eघात = be16_to_cpu(opal_eघात_status[i]);

		/* Filter events which करो not need shutकरोwn. */
		अगर (i == OPAL_SYSEPOW_POWER)
			eघात &= ~(OPAL_SYSPOWER_CHNG | OPAL_SYSPOWER_FAIL |
					OPAL_SYSPOWER_INCL);
		अगर (eघात)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* Check क्रम existing EPOW, DPO events */
अटल bool घातeroff_pending(व्योम)
अणु
	पूर्णांक rc;
	__be64 opal_dpo_समयout;

	/* Check क्रम DPO event */
	rc = opal_get_dpo_status(&opal_dpo_समयout);
	अगर (rc == OPAL_SUCCESS) अणु
		pr_info("Existing DPO event detected.\n");
		वापस true;
	पूर्ण

	/* Check क्रम EPOW event */
	अगर (detect_eघात()) अणु
		pr_info("Existing EPOW event detected.\n");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

/* OPAL घातer-control events notअगरier */
अटल पूर्णांक opal_घातer_control_event(काष्ठा notअगरier_block *nb,
					अचिन्हित दीर्घ msg_type, व्योम *msg)
अणु
	uपूर्णांक64_t type;

	चयन (msg_type) अणु
	हाल OPAL_MSG_EPOW:
		अगर (detect_eघात()) अणु
			pr_info("EPOW msg received. Powering off system\n");
			orderly_घातeroff(true);
		पूर्ण
		अवरोध;
	हाल OPAL_MSG_DPO:
		pr_info("DPO msg received. Powering off system\n");
		orderly_घातeroff(true);
		अवरोध;
	हाल OPAL_MSG_SHUTDOWN:
		type = be64_to_cpu(((काष्ठा opal_msg *)msg)->params[0]);
		चयन (type) अणु
		हाल SOFT_REBOOT:
			pr_info("Reboot requested\n");
			orderly_reboot();
			अवरोध;
		हाल SOFT_OFF:
			pr_info("Poweroff requested\n");
			orderly_घातeroff(true);
			अवरोध;
		शेष:
			pr_err("Unknown power-control type %llu\n", type);
		पूर्ण
		अवरोध;
	शेष:
		pr_err("Unknown OPAL message type %lu\n", msg_type);
	पूर्ण

	वापस 0;
पूर्ण

/* OPAL EPOW event notअगरier block */
अटल काष्ठा notअगरier_block opal_eघात_nb = अणु
	.notअगरier_call	= opal_घातer_control_event,
	.next		= शून्य,
	.priority	= 0,
पूर्ण;

/* OPAL DPO event notअगरier block */
अटल काष्ठा notअगरier_block opal_dpo_nb = अणु
	.notअगरier_call	= opal_घातer_control_event,
	.next		= शून्य,
	.priority	= 0,
पूर्ण;

/* OPAL घातer-control event notअगरier block */
अटल काष्ठा notअगरier_block opal_घातer_control_nb = अणु
	.notअगरier_call	= opal_घातer_control_event,
	.next		= शून्य,
	.priority	= 0,
पूर्ण;

पूर्णांक __init opal_घातer_control_init(व्योम)
अणु
	पूर्णांक ret, supported = 0;
	काष्ठा device_node *np;

	/* Register OPAL घातer-control events notअगरier */
	ret = opal_message_notअगरier_रेजिस्टर(OPAL_MSG_SHUTDOWN,
						&opal_घातer_control_nb);
	अगर (ret)
		pr_err("Failed to register SHUTDOWN notifier, ret = %d\n", ret);

	/* Determine OPAL EPOW, DPO support */
	np = of_find_node_by_path("/ibm,opal/epow");
	अगर (np) अणु
		supported = of_device_is_compatible(np, "ibm,opal-v3-epow");
		of_node_put(np);
	पूर्ण

	अगर (!supported)
		वापस 0;
	pr_info("OPAL EPOW, DPO support detected.\n");

	/* Register EPOW event notअगरier */
	ret = opal_message_notअगरier_रेजिस्टर(OPAL_MSG_EPOW, &opal_eघात_nb);
	अगर (ret)
		pr_err("Failed to register EPOW notifier, ret = %d\n", ret);

	/* Register DPO event notअगरier */
	ret = opal_message_notअगरier_रेजिस्टर(OPAL_MSG_DPO, &opal_dpo_nb);
	अगर (ret)
		pr_err("Failed to register DPO notifier, ret = %d\n", ret);

	/* Check क्रम any pending EPOW or DPO events. */
	अगर (घातeroff_pending())
		orderly_घातeroff(true);

	वापस 0;
पूर्ण
