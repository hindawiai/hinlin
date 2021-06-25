<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * ipmi_घातeroff.c
 *
 * MontaVista IPMI Poweroff extension to sys_reboot
 *
 * Author: MontaVista Software, Inc.
 *         Steven Dake <sdake@mvista.com>
 *         Corey Minyard <cminyard@mvista.com>
 *         source@mvista.com
 *
 * Copyright 2002,2004 MontaVista Software Inc.
 */

#घोषणा pr_fmt(fmt) "IPMI poweroff: " fmt

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/proc_fs.h>
#समावेश <linux/माला.स>
#समावेश <linux/completion.h>
#समावेश <linux/pm.h>
#समावेश <linux/kdev_t.h>
#समावेश <linux/ipmi.h>
#समावेश <linux/ipmi_smi.h>

अटल व्योम ipmi_po_smi_gone(पूर्णांक अगर_num);
अटल व्योम ipmi_po_new_smi(पूर्णांक अगर_num, काष्ठा device *device);

/* Definitions क्रम controlling घातer off (अगर the प्रणाली supports it).  It
 * conveniently matches the IPMI chassis control values. */
#घोषणा IPMI_CHASSIS_POWER_DOWN		0	/* घातer करोwn, the शेष. */
#घोषणा IPMI_CHASSIS_POWER_CYCLE	0x02	/* घातer cycle */

/* the IPMI data command */
अटल पूर्णांक घातeroff_घातercycle;

/* Which पूर्णांकerface to use, -1 means the first we see. */
अटल पूर्णांक अगरnum_to_use = -1;

/* Our local state. */
अटल पूर्णांक पढ़ोy;
अटल काष्ठा ipmi_user *ipmi_user;
अटल पूर्णांक ipmi_अगरnum;
अटल व्योम (*specअगरic_घातeroff_func)(काष्ठा ipmi_user *user);

/* Holds the old घातeroff function so we can restore it on removal. */
अटल व्योम (*old_घातeroff_func)(व्योम);

अटल पूर्णांक set_param_अगरnum(स्थिर अक्षर *val, स्थिर काष्ठा kernel_param *kp)
अणु
	पूर्णांक rv = param_set_पूर्णांक(val, kp);
	अगर (rv)
		वापस rv;
	अगर ((अगरnum_to_use < 0) || (अगरnum_to_use == ipmi_अगरnum))
		वापस 0;

	ipmi_po_smi_gone(ipmi_अगरnum);
	ipmi_po_new_smi(अगरnum_to_use, शून्य);
	वापस 0;
पूर्ण

module_param_call(अगरnum_to_use, set_param_अगरnum, param_get_पूर्णांक,
		  &अगरnum_to_use, 0644);
MODULE_PARM_DESC(अगरnum_to_use, "The interface number to use for the watchdog "
		 "timer.  Setting to -1 defaults to the first registered "
		 "interface");

/* parameter definition to allow user to flag घातer cycle */
module_param(घातeroff_घातercycle, पूर्णांक, 0644);
MODULE_PARM_DESC(घातeroff_घातercycle,
		 " Set to non-zero to enable power cycle instead of power"
		 " down. Power cycle is contingent on hardware support,"
		 " otherwise it defaults back to power down.");

/* Stuff from the get device id command. */
अटल अचिन्हित पूर्णांक mfg_id;
अटल अचिन्हित पूर्णांक prod_id;
अटल अचिन्हित अक्षर capabilities;
अटल अचिन्हित अक्षर ipmi_version;

/*
 * We use our own messages क्रम this operation, we करोn't let the प्रणाली
 * allocate them, since we may be in a panic situation.  The whole
 * thing is single-thपढ़ोed, anyway, so multiple messages are not
 * required.
 */
अटल atomic_t dummy_count = ATOMIC_INIT(0);
अटल व्योम dummy_smi_मुक्त(काष्ठा ipmi_smi_msg *msg)
अणु
	atomic_dec(&dummy_count);
पूर्ण
अटल व्योम dummy_recv_मुक्त(काष्ठा ipmi_recv_msg *msg)
अणु
	atomic_dec(&dummy_count);
पूर्ण
अटल काष्ठा ipmi_smi_msg halt_smi_msg = अणु
	.करोne = dummy_smi_मुक्त
पूर्ण;
अटल काष्ठा ipmi_recv_msg halt_recv_msg = अणु
	.करोne = dummy_recv_मुक्त
पूर्ण;


/*
 * Code to send a message and रुको क्रम the response.
 */

अटल व्योम receive_handler(काष्ठा ipmi_recv_msg *recv_msg, व्योम *handler_data)
अणु
	काष्ठा completion *comp = recv_msg->user_msg_data;

	अगर (comp)
		complete(comp);
पूर्ण

अटल स्थिर काष्ठा ipmi_user_hndl ipmi_घातeroff_handler = अणु
	.ipmi_recv_hndl = receive_handler
पूर्ण;


अटल पूर्णांक ipmi_request_रुको_क्रम_response(काष्ठा ipmi_user       *user,
					  काष्ठा ipmi_addr       *addr,
					  काष्ठा kernel_ipmi_msg *send_msg)
अणु
	पूर्णांक               rv;
	काष्ठा completion comp;

	init_completion(&comp);

	rv = ipmi_request_supply_msgs(user, addr, 0, send_msg, &comp,
				      &halt_smi_msg, &halt_recv_msg, 0);
	अगर (rv)
		वापस rv;

	रुको_क्रम_completion(&comp);

	वापस halt_recv_msg.msg.data[0];
पूर्ण

/* Wait क्रम message to complete, spinning. */
अटल पूर्णांक ipmi_request_in_rc_mode(काष्ठा ipmi_user       *user,
				   काष्ठा ipmi_addr       *addr,
				   काष्ठा kernel_ipmi_msg *send_msg)
अणु
	पूर्णांक rv;

	atomic_set(&dummy_count, 2);
	rv = ipmi_request_supply_msgs(user, addr, 0, send_msg, शून्य,
				      &halt_smi_msg, &halt_recv_msg, 0);
	अगर (rv) अणु
		atomic_set(&dummy_count, 0);
		वापस rv;
	पूर्ण

	/*
	 * Spin until our message is करोne.
	 */
	जबतक (atomic_पढ़ो(&dummy_count) > 0) अणु
		ipmi_poll_पूर्णांकerface(user);
		cpu_relax();
	पूर्ण

	वापस halt_recv_msg.msg.data[0];
पूर्ण

/*
 * ATCA Support
 */

#घोषणा IPMI_NETFN_ATCA			0x2c
#घोषणा IPMI_ATCA_SET_POWER_CMD		0x11
#घोषणा IPMI_ATCA_GET_ADDR_INFO_CMD	0x01
#घोषणा IPMI_PICMG_ID			0

#घोषणा IPMI_NETFN_OEM				0x2e
#घोषणा IPMI_ATCA_PPS_GRACEFUL_RESTART		0x11
#घोषणा IPMI_ATCA_PPS_IANA			"\x00\x40\x0A"
#घोषणा IPMI_MOTOROLA_MANUFACTURER_ID		0x0000A1
#घोषणा IPMI_MOTOROLA_PPS_IPMC_PRODUCT_ID	0x0051

अटल व्योम (*atca_oem_घातeroff_hook)(काष्ठा ipmi_user *user);

अटल व्योम pps_घातeroff_atca(काष्ठा ipmi_user *user)
अणु
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr smi_addr;
	काष्ठा kernel_ipmi_msg            send_msg;
	पूर्णांक                               rv;
	/*
	 * Configure IPMI address क्रम local access
	 */
	smi_addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr.channel = IPMI_BMC_CHANNEL;
	smi_addr.lun = 0;

	pr_info("PPS powerdown hook used\n");

	send_msg.netfn = IPMI_NETFN_OEM;
	send_msg.cmd = IPMI_ATCA_PPS_GRACEFUL_RESTART;
	send_msg.data = IPMI_ATCA_PPS_IANA;
	send_msg.data_len = 3;
	rv = ipmi_request_in_rc_mode(user,
				     (काष्ठा ipmi_addr *) &smi_addr,
				     &send_msg);
	अगर (rv && rv != IPMI_UNKNOWN_ERR_COMPLETION_CODE)
		pr_err("Unable to send ATCA, IPMI error 0x%x\n", rv);

	वापस;
पूर्ण

अटल पूर्णांक ipmi_atca_detect(काष्ठा ipmi_user *user)
अणु
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr smi_addr;
	काष्ठा kernel_ipmi_msg            send_msg;
	पूर्णांक                               rv;
	अचिन्हित अक्षर                     data[1];

	/*
	 * Configure IPMI address क्रम local access
	 */
	smi_addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr.channel = IPMI_BMC_CHANNEL;
	smi_addr.lun = 0;

	/*
	 * Use get address info to check and see अगर we are ATCA
	 */
	send_msg.netfn = IPMI_NETFN_ATCA;
	send_msg.cmd = IPMI_ATCA_GET_ADDR_INFO_CMD;
	data[0] = IPMI_PICMG_ID;
	send_msg.data = data;
	send_msg.data_len = माप(data);
	rv = ipmi_request_रुको_क्रम_response(user,
					    (काष्ठा ipmi_addr *) &smi_addr,
					    &send_msg);

	pr_info("ATCA Detect mfg 0x%X prod 0x%X\n", mfg_id, prod_id);
	अगर ((mfg_id == IPMI_MOTOROLA_MANUFACTURER_ID)
	    && (prod_id == IPMI_MOTOROLA_PPS_IPMC_PRODUCT_ID)) अणु
		pr_info("Installing Pigeon Point Systems Poweroff Hook\n");
		atca_oem_घातeroff_hook = pps_घातeroff_atca;
	पूर्ण
	वापस !rv;
पूर्ण

अटल व्योम ipmi_घातeroff_atca(काष्ठा ipmi_user *user)
अणु
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr smi_addr;
	काष्ठा kernel_ipmi_msg            send_msg;
	पूर्णांक                               rv;
	अचिन्हित अक्षर                     data[4];

	/*
	 * Configure IPMI address क्रम local access
	 */
	smi_addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr.channel = IPMI_BMC_CHANNEL;
	smi_addr.lun = 0;

	pr_info("Powering down via ATCA power command\n");

	/*
	 * Power करोwn
	 */
	send_msg.netfn = IPMI_NETFN_ATCA;
	send_msg.cmd = IPMI_ATCA_SET_POWER_CMD;
	data[0] = IPMI_PICMG_ID;
	data[1] = 0; /* FRU id */
	data[2] = 0; /* Power Level */
	data[3] = 0; /* Don't change saved presets */
	send_msg.data = data;
	send_msg.data_len = माप(data);
	rv = ipmi_request_in_rc_mode(user,
				     (काष्ठा ipmi_addr *) &smi_addr,
				     &send_msg);
	/*
	 * At this poपूर्णांक, the प्रणाली may be shutting करोwn, and most
	 * serial drivers (अगर used) will have पूर्णांकerrupts turned off
	 * it may be better to ignore IPMI_UNKNOWN_ERR_COMPLETION_CODE
	 * वापस code
	 */
	अगर (rv && rv != IPMI_UNKNOWN_ERR_COMPLETION_CODE) अणु
		pr_err("Unable to send ATCA powerdown message, IPMI error 0x%x\n",
		       rv);
		जाओ out;
	पूर्ण

	अगर (atca_oem_घातeroff_hook)
		atca_oem_घातeroff_hook(user);
 out:
	वापस;
पूर्ण

/*
 * CPI1 Support
 */

#घोषणा IPMI_NETFN_OEM_1				0xf8
#घोषणा OEM_GRP_CMD_SET_RESET_STATE		0x84
#घोषणा OEM_GRP_CMD_SET_POWER_STATE		0x82
#घोषणा IPMI_NETFN_OEM_8				0xf8
#घोषणा OEM_GRP_CMD_REQUEST_HOTSWAP_CTRL	0x80
#घोषणा OEM_GRP_CMD_GET_SLOT_GA			0xa3
#घोषणा IPMI_NETFN_SENSOR_EVT			0x10
#घोषणा IPMI_CMD_GET_EVENT_RECEIVER		0x01

#घोषणा IPMI_CPI1_PRODUCT_ID		0x000157
#घोषणा IPMI_CPI1_MANUFACTURER_ID	0x0108

अटल पूर्णांक ipmi_cpi1_detect(काष्ठा ipmi_user *user)
अणु
	वापस ((mfg_id == IPMI_CPI1_MANUFACTURER_ID)
		&& (prod_id == IPMI_CPI1_PRODUCT_ID));
पूर्ण

अटल व्योम ipmi_घातeroff_cpi1(काष्ठा ipmi_user *user)
अणु
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr smi_addr;
	काष्ठा ipmi_ipmb_addr             ipmb_addr;
	काष्ठा kernel_ipmi_msg            send_msg;
	पूर्णांक                               rv;
	अचिन्हित अक्षर                     data[1];
	पूर्णांक                               slot;
	अचिन्हित अक्षर                     hotswap_ipmb;
	अचिन्हित अक्षर                     aer_addr;
	अचिन्हित अक्षर                     aer_lun;

	/*
	 * Configure IPMI address क्रम local access
	 */
	smi_addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr.channel = IPMI_BMC_CHANNEL;
	smi_addr.lun = 0;

	pr_info("Powering down via CPI1 power command\n");

	/*
	 * Get IPMI ipmb address
	 */
	send_msg.netfn = IPMI_NETFN_OEM_8 >> 2;
	send_msg.cmd = OEM_GRP_CMD_GET_SLOT_GA;
	send_msg.data = शून्य;
	send_msg.data_len = 0;
	rv = ipmi_request_in_rc_mode(user,
				     (काष्ठा ipmi_addr *) &smi_addr,
				     &send_msg);
	अगर (rv)
		जाओ out;
	slot = halt_recv_msg.msg.data[1];
	hotswap_ipmb = (slot > 9) ? (0xb0 + 2 * slot) : (0xae + 2 * slot);

	/*
	 * Get active event receiver
	 */
	send_msg.netfn = IPMI_NETFN_SENSOR_EVT >> 2;
	send_msg.cmd = IPMI_CMD_GET_EVENT_RECEIVER;
	send_msg.data = शून्य;
	send_msg.data_len = 0;
	rv = ipmi_request_in_rc_mode(user,
				     (काष्ठा ipmi_addr *) &smi_addr,
				     &send_msg);
	अगर (rv)
		जाओ out;
	aer_addr = halt_recv_msg.msg.data[1];
	aer_lun = halt_recv_msg.msg.data[2];

	/*
	 * Setup IPMB address target instead of local target
	 */
	ipmb_addr.addr_type = IPMI_IPMB_ADDR_TYPE;
	ipmb_addr.channel = 0;
	ipmb_addr.slave_addr = aer_addr;
	ipmb_addr.lun = aer_lun;

	/*
	 * Send request hotswap control to हटाओ blade from dpv
	 */
	send_msg.netfn = IPMI_NETFN_OEM_8 >> 2;
	send_msg.cmd = OEM_GRP_CMD_REQUEST_HOTSWAP_CTRL;
	send_msg.data = &hotswap_ipmb;
	send_msg.data_len = 1;
	ipmi_request_in_rc_mode(user,
				(काष्ठा ipmi_addr *) &ipmb_addr,
				&send_msg);

	/*
	 * Set reset निश्चितed
	 */
	send_msg.netfn = IPMI_NETFN_OEM_1 >> 2;
	send_msg.cmd = OEM_GRP_CMD_SET_RESET_STATE;
	send_msg.data = data;
	data[0] = 1; /* Reset निश्चितed state */
	send_msg.data_len = 1;
	rv = ipmi_request_in_rc_mode(user,
				     (काष्ठा ipmi_addr *) &smi_addr,
				     &send_msg);
	अगर (rv)
		जाओ out;

	/*
	 * Power करोwn
	 */
	send_msg.netfn = IPMI_NETFN_OEM_1 >> 2;
	send_msg.cmd = OEM_GRP_CMD_SET_POWER_STATE;
	send_msg.data = data;
	data[0] = 1; /* Power करोwn state */
	send_msg.data_len = 1;
	rv = ipmi_request_in_rc_mode(user,
				     (काष्ठा ipmi_addr *) &smi_addr,
				     &send_msg);
	अगर (rv)
		जाओ out;

 out:
	वापस;
पूर्ण

/*
 * ipmi_dell_chassis_detect()
 * Dell प्रणालीs with IPMI < 1.5 करोn't set the chassis capability bit
 * but they can handle a chassis घातeroff or घातercycle command.
 */

#घोषणा DELL_IANA_MFR_ID अणु0xA2, 0x02, 0x00पूर्ण
अटल पूर्णांक ipmi_dell_chassis_detect(काष्ठा ipmi_user *user)
अणु
	स्थिर अक्षर ipmi_version_major = ipmi_version & 0xF;
	स्थिर अक्षर ipmi_version_minor = (ipmi_version >> 4) & 0xF;
	स्थिर अक्षर mfr[3] = DELL_IANA_MFR_ID;
	अगर (!स_भेद(mfr, &mfg_id, माप(mfr)) &&
	    ipmi_version_major <= 1 &&
	    ipmi_version_minor < 5)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * ipmi_hp_chassis_detect()
 * HP PA-RISC servers rp3410/rp3440, the C8000 workstation and the rx2600 and
 * zx6000 machines support IPMI vers 1 and करोn't set the chassis capability bit
 * but they can handle a chassis घातeroff or घातercycle command.
 */

#घोषणा HP_IANA_MFR_ID 0x0b
#घोषणा HP_BMC_PROD_ID 0x8201
अटल पूर्णांक ipmi_hp_chassis_detect(काष्ठा ipmi_user *user)
अणु
	अगर (mfg_id == HP_IANA_MFR_ID
		&& prod_id == HP_BMC_PROD_ID
		&& ipmi_version == 1)
		वापस 1;
	वापस 0;
पूर्ण

/*
 * Standard chassis support
 */

#घोषणा IPMI_NETFN_CHASSIS_REQUEST	0
#घोषणा IPMI_CHASSIS_CONTROL_CMD	0x02

अटल पूर्णांक ipmi_chassis_detect(काष्ठा ipmi_user *user)
अणु
	/* Chassis support, use it. */
	वापस (capabilities & 0x80);
पूर्ण

अटल व्योम ipmi_घातeroff_chassis(काष्ठा ipmi_user *user)
अणु
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr smi_addr;
	काष्ठा kernel_ipmi_msg            send_msg;
	पूर्णांक                               rv;
	अचिन्हित अक्षर                     data[1];

	/*
	 * Configure IPMI address क्रम local access
	 */
	smi_addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr.channel = IPMI_BMC_CHANNEL;
	smi_addr.lun = 0;

 घातercyclefailed:
	pr_info("Powering %s via IPMI chassis control command\n",
		(घातeroff_घातercycle ? "cycle" : "down"));

	/*
	 * Power करोwn
	 */
	send_msg.netfn = IPMI_NETFN_CHASSIS_REQUEST;
	send_msg.cmd = IPMI_CHASSIS_CONTROL_CMD;
	अगर (घातeroff_घातercycle)
		data[0] = IPMI_CHASSIS_POWER_CYCLE;
	अन्यथा
		data[0] = IPMI_CHASSIS_POWER_DOWN;
	send_msg.data = data;
	send_msg.data_len = माप(data);
	rv = ipmi_request_in_rc_mode(user,
				     (काष्ठा ipmi_addr *) &smi_addr,
				     &send_msg);
	अगर (rv) अणु
		अगर (घातeroff_घातercycle) अणु
			/* घातer cycle failed, शेष to घातer करोwn */
			pr_err("Unable to send chassis power cycle message, IPMI error 0x%x\n",
			       rv);
			घातeroff_घातercycle = 0;
			जाओ घातercyclefailed;
		पूर्ण

		pr_err("Unable to send chassis power down message, IPMI error 0x%x\n",
		       rv);
	पूर्ण
पूर्ण


/* Table of possible घातer off functions. */
काष्ठा घातeroff_function अणु
	अक्षर *platक्रमm_type;
	पूर्णांक  (*detect)(काष्ठा ipmi_user *user);
	व्योम (*घातeroff_func)(काष्ठा ipmi_user *user);
पूर्ण;

अटल काष्ठा घातeroff_function घातeroff_functions[] = अणु
	अणु .platक्रमm_type	= "ATCA",
	  .detect		= ipmi_atca_detect,
	  .घातeroff_func	= ipmi_घातeroff_atca पूर्ण,
	अणु .platक्रमm_type	= "CPI1",
	  .detect		= ipmi_cpi1_detect,
	  .घातeroff_func	= ipmi_घातeroff_cpi1 पूर्ण,
	अणु .platक्रमm_type	= "chassis",
	  .detect		= ipmi_dell_chassis_detect,
	  .घातeroff_func	= ipmi_घातeroff_chassis पूर्ण,
	अणु .platक्रमm_type	= "chassis",
	  .detect		= ipmi_hp_chassis_detect,
	  .घातeroff_func	= ipmi_घातeroff_chassis पूर्ण,
	/* Chassis should generally be last, other things should override
	   it. */
	अणु .platक्रमm_type	= "chassis",
	  .detect		= ipmi_chassis_detect,
	  .घातeroff_func	= ipmi_घातeroff_chassis पूर्ण,
पूर्ण;
#घोषणा NUM_PO_FUNCS ARRAY_SIZE(घातeroff_functions)


/* Called on a घातerकरोwn request. */
अटल व्योम ipmi_घातeroff_function(व्योम)
अणु
	अगर (!पढ़ोy)
		वापस;

	/* Use run-to-completion mode, since पूर्णांकerrupts may be off. */
	specअगरic_घातeroff_func(ipmi_user);
पूर्ण

/* Wait क्रम an IPMI पूर्णांकerface to be installed, the first one installed
   will be grabbed by this code and used to perक्रमm the घातerकरोwn. */
अटल व्योम ipmi_po_new_smi(पूर्णांक अगर_num, काष्ठा device *device)
अणु
	काष्ठा ipmi_प्रणाली_पूर्णांकerface_addr smi_addr;
	काष्ठा kernel_ipmi_msg            send_msg;
	पूर्णांक                               rv;
	पूर्णांक                               i;

	अगर (पढ़ोy)
		वापस;

	अगर ((अगरnum_to_use >= 0) && (अगरnum_to_use != अगर_num))
		वापस;

	rv = ipmi_create_user(अगर_num, &ipmi_घातeroff_handler, शून्य,
			      &ipmi_user);
	अगर (rv) अणु
		pr_err("could not create IPMI user, error %d\n", rv);
		वापस;
	पूर्ण

	ipmi_अगरnum = अगर_num;

	/*
	 * Do a get device ide and store some results, since this is
	 * used by several functions.
	 */
	smi_addr.addr_type = IPMI_SYSTEM_INTERFACE_ADDR_TYPE;
	smi_addr.channel = IPMI_BMC_CHANNEL;
	smi_addr.lun = 0;

	send_msg.netfn = IPMI_NETFN_APP_REQUEST;
	send_msg.cmd = IPMI_GET_DEVICE_ID_CMD;
	send_msg.data = शून्य;
	send_msg.data_len = 0;
	rv = ipmi_request_रुको_क्रम_response(ipmi_user,
					    (काष्ठा ipmi_addr *) &smi_addr,
					    &send_msg);
	अगर (rv) अणु
		pr_err("Unable to send IPMI get device id info, IPMI error 0x%x\n",
		       rv);
		जाओ out_err;
	पूर्ण

	अगर (halt_recv_msg.msg.data_len < 12) अणु
		pr_err("(chassis) IPMI get device id info too short, was %d bytes, needed %d bytes\n",
		       halt_recv_msg.msg.data_len, 12);
		जाओ out_err;
	पूर्ण

	mfg_id = (halt_recv_msg.msg.data[7]
		  | (halt_recv_msg.msg.data[8] << 8)
		  | (halt_recv_msg.msg.data[9] << 16));
	prod_id = (halt_recv_msg.msg.data[10]
		   | (halt_recv_msg.msg.data[11] << 8));
	capabilities = halt_recv_msg.msg.data[6];
	ipmi_version = halt_recv_msg.msg.data[5];


	/* Scan क्रम a घातeroff method */
	क्रम (i = 0; i < NUM_PO_FUNCS; i++) अणु
		अगर (घातeroff_functions[i].detect(ipmi_user))
			जाओ found;
	पूर्ण

 out_err:
	pr_err("Unable to find a poweroff function that will work, giving up\n");
	ipmi_destroy_user(ipmi_user);
	वापस;

 found:
	pr_info("Found a %s style poweroff function\n",
		घातeroff_functions[i].platक्रमm_type);
	specअगरic_घातeroff_func = घातeroff_functions[i].घातeroff_func;
	old_घातeroff_func = pm_घातer_off;
	pm_घातer_off = ipmi_घातeroff_function;
	पढ़ोy = 1;
पूर्ण

अटल व्योम ipmi_po_smi_gone(पूर्णांक अगर_num)
अणु
	अगर (!पढ़ोy)
		वापस;

	अगर (ipmi_अगरnum != अगर_num)
		वापस;

	पढ़ोy = 0;
	ipmi_destroy_user(ipmi_user);
	pm_घातer_off = old_घातeroff_func;
पूर्ण

अटल काष्ठा ipmi_smi_watcher smi_watcher = अणु
	.owner    = THIS_MODULE,
	.new_smi  = ipmi_po_new_smi,
	.smi_gone = ipmi_po_smi_gone
पूर्ण;


#अगर_घोषित CONFIG_PROC_FS
#समावेश <linux/sysctl.h>

अटल काष्ठा ctl_table ipmi_table[] = अणु
	अणु .procname	= "poweroff_powercycle",
	  .data		= &घातeroff_घातercycle,
	  .maxlen	= माप(घातeroff_घातercycle),
	  .mode		= 0644,
	  .proc_handler	= proc_करोपूर्णांकvec पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table ipmi_dir_table[] = अणु
	अणु .procname	= "ipmi",
	  .mode		= 0555,
	  .child	= ipmi_table पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table ipmi_root_table[] = अणु
	अणु .procname	= "dev",
	  .mode		= 0555,
	  .child	= ipmi_dir_table पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा ctl_table_header *ipmi_table_header;
#पूर्ण_अगर /* CONFIG_PROC_FS */

/*
 * Startup and shutकरोwn functions.
 */
अटल पूर्णांक __init ipmi_घातeroff_init(व्योम)
अणु
	पूर्णांक rv;

	pr_info("Copyright (C) 2004 MontaVista Software - IPMI Powerdown via sys_reboot\n");

	अगर (घातeroff_घातercycle)
		pr_info("Power cycle is enabled\n");

#अगर_घोषित CONFIG_PROC_FS
	ipmi_table_header = रेजिस्टर_sysctl_table(ipmi_root_table);
	अगर (!ipmi_table_header) अणु
		pr_err("Unable to register powercycle sysctl\n");
		rv = -ENOMEM;
		जाओ out_err;
	पूर्ण
#पूर्ण_अगर

	rv = ipmi_smi_watcher_रेजिस्टर(&smi_watcher);

#अगर_घोषित CONFIG_PROC_FS
	अगर (rv) अणु
		unरेजिस्टर_sysctl_table(ipmi_table_header);
		pr_err("Unable to register SMI watcher: %d\n", rv);
		जाओ out_err;
	पूर्ण

 out_err:
#पूर्ण_अगर
	वापस rv;
पूर्ण

#अगर_घोषित MODULE
अटल व्योम __निकास ipmi_घातeroff_cleanup(व्योम)
अणु
	पूर्णांक rv;

#अगर_घोषित CONFIG_PROC_FS
	unरेजिस्टर_sysctl_table(ipmi_table_header);
#पूर्ण_अगर

	ipmi_smi_watcher_unरेजिस्टर(&smi_watcher);

	अगर (पढ़ोy) अणु
		rv = ipmi_destroy_user(ipmi_user);
		अगर (rv)
			pr_err("could not cleanup the IPMI user: 0x%x\n", rv);
		pm_घातer_off = old_घातeroff_func;
	पूर्ण
पूर्ण
module_निकास(ipmi_घातeroff_cleanup);
#पूर्ण_अगर

module_init(ipmi_घातeroff_init);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Corey Minyard <minyard@mvista.com>");
MODULE_DESCRIPTION("IPMI Poweroff extension to sys_reboot");
