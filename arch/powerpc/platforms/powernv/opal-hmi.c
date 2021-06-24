<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * OPAL hypervisor Maपूर्णांकenance पूर्णांकerrupt handling support in PowerNV.
 *
 * Copyright 2014 IBM Corporation
 * Author: Mahesh Salgaonkar <mahesh@linux.vnet.ibm.com>
 */

#अघोषित DEBUG

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/of.h>
#समावेश <linux/mm.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/opal.h>
#समावेश <यंत्र/cputable.h>
#समावेश <यंत्र/machdep.h>

#समावेश "powernv.h"

अटल पूर्णांक opal_hmi_handler_nb_init;
काष्ठा OpalHmiEvtNode अणु
	काष्ठा list_head list;
	काष्ठा OpalHMIEvent hmi_evt;
पूर्ण;

काष्ठा xstop_reason अणु
	uपूर्णांक32_t xstop_reason;
	स्थिर अक्षर *unit_failed;
	स्थिर अक्षर *description;
पूर्ण;

अटल LIST_HEAD(opal_hmi_evt_list);
अटल DEFINE_SPINLOCK(opal_hmi_evt_lock);

अटल व्योम prपूर्णांक_core_checkstop_reason(स्थिर अक्षर *level,
					काष्ठा OpalHMIEvent *hmi_evt)
अणु
	पूर्णांक i;
	अटल स्थिर काष्ठा xstop_reason xstop_reason[] = अणु
		अणु CORE_CHECKSTOP_IFU_REGखाता, "IFU",
				"RegFile core check stop" पूर्ण,
		अणु CORE_CHECKSTOP_IFU_LOGIC, "IFU", "Logic core check stop" पूर्ण,
		अणु CORE_CHECKSTOP_PC_DURING_RECOV, "PC",
				"Core checkstop during recovery" पूर्ण,
		अणु CORE_CHECKSTOP_ISU_REGखाता, "ISU",
				"RegFile core check stop (mapper error)" पूर्ण,
		अणु CORE_CHECKSTOP_ISU_LOGIC, "ISU", "Logic core check stop" पूर्ण,
		अणु CORE_CHECKSTOP_FXU_LOGIC, "FXU", "Logic core check stop" पूर्ण,
		अणु CORE_CHECKSTOP_VSU_LOGIC, "VSU", "Logic core check stop" पूर्ण,
		अणु CORE_CHECKSTOP_PC_RECOV_IN_MAINT_MODE, "PC",
				"Recovery in maintenance mode" पूर्ण,
		अणु CORE_CHECKSTOP_LSU_REGखाता, "LSU",
				"RegFile core check stop" पूर्ण,
		अणु CORE_CHECKSTOP_PC_FWD_PROGRESS, "PC",
				"Forward Progress Error" पूर्ण,
		अणु CORE_CHECKSTOP_LSU_LOGIC, "LSU", "Logic core check stop" पूर्ण,
		अणु CORE_CHECKSTOP_PC_LOGIC, "PC", "Logic core check stop" पूर्ण,
		अणु CORE_CHECKSTOP_PC_HYP_RESOURCE, "PC",
				"Hypervisor Resource error - core check stop" पूर्ण,
		अणु CORE_CHECKSTOP_PC_HANG_RECOV_FAILED, "PC",
				"Hang Recovery Failed (core check stop)" पूर्ण,
		अणु CORE_CHECKSTOP_PC_AMBI_HANG_DETECTED, "PC",
				"Ambiguous Hang Detected (unknown source)" पूर्ण,
		अणु CORE_CHECKSTOP_PC_DEBUG_TRIG_ERR_INJ, "PC",
				"Debug Trigger Error inject" पूर्ण,
		अणु CORE_CHECKSTOP_PC_SPRD_HYP_ERR_INJ, "PC",
				"Hypervisor check stop via SPRC/SPRD" पूर्ण,
	पूर्ण;

	/* Validity check */
	अगर (!hmi_evt->u.xstop_error.xstop_reason) अणु
		prपूर्णांकk("%s	Unknown Core check stop.\n", level);
		वापस;
	पूर्ण

	prपूर्णांकk("%s	CPU PIR: %08x\n", level,
			be32_to_cpu(hmi_evt->u.xstop_error.u.pir));
	क्रम (i = 0; i < ARRAY_SIZE(xstop_reason); i++)
		अगर (be32_to_cpu(hmi_evt->u.xstop_error.xstop_reason) &
					xstop_reason[i].xstop_reason)
			prपूर्णांकk("%s	[Unit: %-3s] %s\n", level,
					xstop_reason[i].unit_failed,
					xstop_reason[i].description);
पूर्ण

अटल व्योम prपूर्णांक_nx_checkstop_reason(स्थिर अक्षर *level,
					काष्ठा OpalHMIEvent *hmi_evt)
अणु
	पूर्णांक i;
	अटल स्थिर काष्ठा xstop_reason xstop_reason[] = अणु
		अणु NX_CHECKSTOP_SHM_INVAL_STATE_ERR, "DMA & Engine",
					"SHM invalid state error" पूर्ण,
		अणु NX_CHECKSTOP_DMA_INVAL_STATE_ERR_1, "DMA & Engine",
					"DMA invalid state error bit 15" पूर्ण,
		अणु NX_CHECKSTOP_DMA_INVAL_STATE_ERR_2, "DMA & Engine",
					"DMA invalid state error bit 16" पूर्ण,
		अणु NX_CHECKSTOP_DMA_CH0_INVAL_STATE_ERR, "DMA & Engine",
					"Channel 0 invalid state error" पूर्ण,
		अणु NX_CHECKSTOP_DMA_CH1_INVAL_STATE_ERR, "DMA & Engine",
					"Channel 1 invalid state error" पूर्ण,
		अणु NX_CHECKSTOP_DMA_CH2_INVAL_STATE_ERR, "DMA & Engine",
					"Channel 2 invalid state error" पूर्ण,
		अणु NX_CHECKSTOP_DMA_CH3_INVAL_STATE_ERR, "DMA & Engine",
					"Channel 3 invalid state error" पूर्ण,
		अणु NX_CHECKSTOP_DMA_CH4_INVAL_STATE_ERR, "DMA & Engine",
					"Channel 4 invalid state error" पूर्ण,
		अणु NX_CHECKSTOP_DMA_CH5_INVAL_STATE_ERR, "DMA & Engine",
					"Channel 5 invalid state error" पूर्ण,
		अणु NX_CHECKSTOP_DMA_CH6_INVAL_STATE_ERR, "DMA & Engine",
					"Channel 6 invalid state error" पूर्ण,
		अणु NX_CHECKSTOP_DMA_CH7_INVAL_STATE_ERR, "DMA & Engine",
					"Channel 7 invalid state error" पूर्ण,
		अणु NX_CHECKSTOP_DMA_CRB_UE, "DMA & Engine",
					"UE error on CRB(CSB address, CCB)" पूर्ण,
		अणु NX_CHECKSTOP_DMA_CRB_SUE, "DMA & Engine",
					"SUE error on CRB(CSB address, CCB)" पूर्ण,
		अणु NX_CHECKSTOP_PBI_ISN_UE, "PowerBus Interface",
		"CRB Kill ISN received while holding ISN with UE error" पूर्ण,
	पूर्ण;

	/* Validity check */
	अगर (!hmi_evt->u.xstop_error.xstop_reason) अणु
		prपूर्णांकk("%s	Unknown NX check stop.\n", level);
		वापस;
	पूर्ण

	prपूर्णांकk("%s	NX checkstop on CHIP ID: %x\n", level,
			be32_to_cpu(hmi_evt->u.xstop_error.u.chip_id));
	क्रम (i = 0; i < ARRAY_SIZE(xstop_reason); i++)
		अगर (be32_to_cpu(hmi_evt->u.xstop_error.xstop_reason) &
					xstop_reason[i].xstop_reason)
			prपूर्णांकk("%s	[Unit: %-3s] %s\n", level,
					xstop_reason[i].unit_failed,
					xstop_reason[i].description);
पूर्ण

अटल व्योम prपूर्णांक_npu_checkstop_reason(स्थिर अक्षर *level,
					काष्ठा OpalHMIEvent *hmi_evt)
अणु
	uपूर्णांक8_t reason, reason_count, i;

	/*
	 * We may not have a checkstop reason on some combination of
	 * hardware and/or skiboot version
	 */
	अगर (!hmi_evt->u.xstop_error.xstop_reason) अणु
		prपूर्णांकk("%s	NPU checkstop on chip %x\n", level,
			be32_to_cpu(hmi_evt->u.xstop_error.u.chip_id));
		वापस;
	पूर्ण

	/*
	 * NPU2 has 3 FIRs. Reason encoded on a byte as:
	 *   2 bits क्रम the FIR number
	 *   6 bits क्रम the bit number
	 * It may be possible to find several reasons.
	 *
	 * We करोn't display a specअगरic message per FIR bit as there
	 * are too many and most are meaningless without the workbook
	 * and/or hw team help anyway.
	 */
	reason_count = माप(hmi_evt->u.xstop_error.xstop_reason) /
		माप(reason);
	क्रम (i = 0; i < reason_count; i++) अणु
		reason = (hmi_evt->u.xstop_error.xstop_reason >> (8 * i)) & 0xFF;
		अगर (reason)
			prपूर्णांकk("%s	NPU checkstop on chip %x: FIR%d bit %d is set\n",
				level,
				be32_to_cpu(hmi_evt->u.xstop_error.u.chip_id),
				reason >> 6, reason & 0x3F);
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_checkstop_reason(स्थिर अक्षर *level,
					काष्ठा OpalHMIEvent *hmi_evt)
अणु
	uपूर्णांक8_t type = hmi_evt->u.xstop_error.xstop_type;
	चयन (type) अणु
	हाल CHECKSTOP_TYPE_CORE:
		prपूर्णांक_core_checkstop_reason(level, hmi_evt);
		अवरोध;
	हाल CHECKSTOP_TYPE_NX:
		prपूर्णांक_nx_checkstop_reason(level, hmi_evt);
		अवरोध;
	हाल CHECKSTOP_TYPE_NPU:
		prपूर्णांक_npu_checkstop_reason(level, hmi_evt);
		अवरोध;
	शेष:
		prपूर्णांकk("%s	Unknown Malfunction Alert of type %d\n",
		       level, type);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम prपूर्णांक_hmi_event_info(काष्ठा OpalHMIEvent *hmi_evt)
अणु
	स्थिर अक्षर *level, *sevstr, *error_info;
	अटल स्थिर अक्षर *hmi_error_types[] = अणु
		"Malfunction Alert",
		"Processor Recovery done",
		"Processor recovery occurred again",
		"Processor recovery occurred for masked error",
		"Timer facility experienced an error",
		"TFMR SPR is corrupted",
		"UPS (Uninterrupted Power System) Overflow indication",
		"An XSCOM operation failure",
		"An XSCOM operation completed",
		"SCOM has set a reserved FIR bit to cause recovery",
		"Debug trigger has set a reserved FIR bit to cause recovery",
		"A hypervisor resource error occurred",
		"CAPP recovery process is in progress",
	पूर्ण;
	अटल DEFINE_RATELIMIT_STATE(rs, DEFAULT_RATELIMIT_INTERVAL,
				      DEFAULT_RATELIMIT_BURST);

	/* Prपूर्णांक things out */
	अगर (hmi_evt->version < OpalHMIEvt_V1) अणु
		pr_err("HMI Interrupt, Unknown event version %d !\n",
			hmi_evt->version);
		वापस;
	पूर्ण
	चयन (hmi_evt->severity) अणु
	हाल OpalHMI_SEV_NO_ERROR:
		level = KERN_INFO;
		sevstr = "Harmless";
		अवरोध;
	हाल OpalHMI_SEV_WARNING:
		level = KERN_WARNING;
		sevstr = "";
		अवरोध;
	हाल OpalHMI_SEV_ERROR_SYNC:
		level = KERN_ERR;
		sevstr = "Severe";
		अवरोध;
	हाल OpalHMI_SEV_FATAL:
	शेष:
		level = KERN_ERR;
		sevstr = "Fatal";
		अवरोध;
	पूर्ण

	अगर (hmi_evt->severity != OpalHMI_SEV_NO_ERROR || __ratelimit(&rs)) अणु
		prपूर्णांकk("%s%s Hypervisor Maintenance interrupt [%s]\n",
			level, sevstr,
			hmi_evt->disposition == OpalHMI_DISPOSITION_RECOVERED ?
			"Recovered" : "Not recovered");
		error_info = hmi_evt->type < ARRAY_SIZE(hmi_error_types) ?
				hmi_error_types[hmi_evt->type]
				: "Unknown";
		prपूर्णांकk("%s Error detail: %s\n", level, error_info);
		prपूर्णांकk("%s	HMER: %016llx\n", level,
					be64_to_cpu(hmi_evt->hmer));
		अगर ((hmi_evt->type == OpalHMI_ERROR_TFAC) ||
			(hmi_evt->type == OpalHMI_ERROR_TFMR_PARITY))
			prपूर्णांकk("%s	TFMR: %016llx\n", level,
						be64_to_cpu(hmi_evt->tfmr));
	पूर्ण

	अगर (hmi_evt->version < OpalHMIEvt_V2)
		वापस;

	/* OpalHMIEvt_V2 and above provides reason क्रम malfunction alert. */
	अगर (hmi_evt->type == OpalHMI_ERROR_MALFUNC_ALERT)
		prपूर्णांक_checkstop_reason(level, hmi_evt);
पूर्ण

अटल व्योम hmi_event_handler(काष्ठा work_काष्ठा *work)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा OpalHMIEvent *hmi_evt;
	काष्ठा OpalHmiEvtNode *msg_node;
	uपूर्णांक8_t disposition;
	काष्ठा opal_msg msg;
	पूर्णांक unrecoverable = 0;

	spin_lock_irqsave(&opal_hmi_evt_lock, flags);
	जबतक (!list_empty(&opal_hmi_evt_list)) अणु
		msg_node = list_entry(opal_hmi_evt_list.next,
					   काष्ठा OpalHmiEvtNode, list);
		list_del(&msg_node->list);
		spin_unlock_irqrestore(&opal_hmi_evt_lock, flags);

		hmi_evt = (काष्ठा OpalHMIEvent *) &msg_node->hmi_evt;
		prपूर्णांक_hmi_event_info(hmi_evt);
		disposition = hmi_evt->disposition;
		kमुक्त(msg_node);

		/*
		 * Check अगर HMI event has been recovered or not. If not
		 * then kernel can't जारी, we need to panic.
		 * But beक्रमe we करो that, display all the HMI event
		 * available on the list and set unrecoverable flag to 1.
		 */
		अगर (disposition != OpalHMI_DISPOSITION_RECOVERED)
			unrecoverable = 1;

		spin_lock_irqsave(&opal_hmi_evt_lock, flags);
	पूर्ण
	spin_unlock_irqrestore(&opal_hmi_evt_lock, flags);

	अगर (unrecoverable) अणु
		/* Pull all HMI events from OPAL beक्रमe we panic. */
		जबतक (opal_get_msg(__pa(&msg), माप(msg)) == OPAL_SUCCESS) अणु
			u32 type;

			type = be32_to_cpu(msg.msg_type);

			/* skip अगर not HMI event */
			अगर (type != OPAL_MSG_HMI_EVT)
				जारी;

			/* HMI event info starts from param[0] */
			hmi_evt = (काष्ठा OpalHMIEvent *)&msg.params[0];
			prपूर्णांक_hmi_event_info(hmi_evt);
		पूर्ण

		pnv_platक्रमm_error_reboot(शून्य, "Unrecoverable HMI exception");
	पूर्ण
पूर्ण

अटल DECLARE_WORK(hmi_event_work, hmi_event_handler);
/*
 * opal_handle_hmi_event - notअगरier handler that queues up HMI events
 * to be preocessed later.
 */
अटल पूर्णांक opal_handle_hmi_event(काष्ठा notअगरier_block *nb,
			  अचिन्हित दीर्घ msg_type, व्योम *msg)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा OpalHMIEvent *hmi_evt;
	काष्ठा opal_msg *hmi_msg = msg;
	काष्ठा OpalHmiEvtNode *msg_node;

	/* Sanity Checks */
	अगर (msg_type != OPAL_MSG_HMI_EVT)
		वापस 0;

	/* HMI event info starts from param[0] */
	hmi_evt = (काष्ठा OpalHMIEvent *)&hmi_msg->params[0];

	/* Delay the logging of HMI events to workqueue. */
	msg_node = kzalloc(माप(*msg_node), GFP_ATOMIC);
	अगर (!msg_node) अणु
		pr_err("HMI: out of memory, Opal message event not handled\n");
		वापस -ENOMEM;
	पूर्ण
	स_नकल(&msg_node->hmi_evt, hmi_evt, माप(*hmi_evt));

	spin_lock_irqsave(&opal_hmi_evt_lock, flags);
	list_add(&msg_node->list, &opal_hmi_evt_list);
	spin_unlock_irqrestore(&opal_hmi_evt_lock, flags);

	schedule_work(&hmi_event_work);
	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block opal_hmi_handler_nb = अणु
	.notअगरier_call	= opal_handle_hmi_event,
	.next		= शून्य,
	.priority	= 0,
पूर्ण;

पूर्णांक __init opal_hmi_handler_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!opal_hmi_handler_nb_init) अणु
		ret = opal_message_notअगरier_रेजिस्टर(
				OPAL_MSG_HMI_EVT, &opal_hmi_handler_nb);
		अगर (ret) अणु
			pr_err("%s: Can't register OPAL event notifier (%d)\n",
			       __func__, ret);
			वापस ret;
		पूर्ण
		opal_hmi_handler_nb_init = 1;
	पूर्ण
	वापस 0;
पूर्ण
