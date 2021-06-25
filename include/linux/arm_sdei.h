<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2017 Arm Ltd.
#अगर_अघोषित __LINUX_ARM_SDEI_H
#घोषणा __LINUX_ARM_SDEI_H

#समावेश <uapi/linux/arm_sdei.h>

#समावेश <acpi/ghes.h>

#अगर_घोषित CONFIG_ARM_SDE_INTERFACE
#समावेश <यंत्र/sdei.h>
#पूर्ण_अगर

/* Arch code should override this to set the entry poपूर्णांक from firmware... */
#अगर_अघोषित sdei_arch_get_entry_poपूर्णांक
#घोषणा sdei_arch_get_entry_poपूर्णांक(conduit)	(0)
#पूर्ण_अगर

/*
 * When an event occurs sdei_event_handler() will call a user-provided callback
 * like this in NMI context on the CPU that received the event.
 */
प्रकार पूर्णांक (sdei_event_callback)(u32 event, काष्ठा pt_regs *regs, व्योम *arg);

/*
 * Register your callback to claim an event. The event must be described
 * by firmware.
 */
पूर्णांक sdei_event_रेजिस्टर(u32 event_num, sdei_event_callback *cb, व्योम *arg);

/*
 * Calls to sdei_event_unरेजिस्टर() may वापस EINPROGRESS. Keep calling
 * it until it succeeds.
 */
पूर्णांक sdei_event_unरेजिस्टर(u32 event_num);

पूर्णांक sdei_event_enable(u32 event_num);
पूर्णांक sdei_event_disable(u32 event_num);

/* GHES रेजिस्टर/unरेजिस्टर helpers */
पूर्णांक sdei_रेजिस्टर_ghes(काष्ठा ghes *ghes, sdei_event_callback *normal_cb,
		       sdei_event_callback *critical_cb);
पूर्णांक sdei_unरेजिस्टर_ghes(काष्ठा ghes *ghes);

#अगर_घोषित CONFIG_ARM_SDE_INTERFACE
/* For use by arch code when CPU hotplug notअगरiers are not appropriate. */
पूर्णांक sdei_mask_local_cpu(व्योम);
पूर्णांक sdei_unmask_local_cpu(व्योम);
#अन्यथा
अटल अंतरभूत पूर्णांक sdei_mask_local_cpu(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत पूर्णांक sdei_unmask_local_cpu(व्योम) अणु वापस 0; पूर्ण
#पूर्ण_अगर /* CONFIG_ARM_SDE_INTERFACE */


/*
 * This काष्ठा represents an event that has been रेजिस्टरed. The driver
 * मुख्यtains a list of all events, and which ones are रेजिस्टरed. (Private
 * events have one entry in the list, but are रेजिस्टरed on each CPU).
 * A poपूर्णांकer to this काष्ठा is passed to firmware, and back to the event
 * handler. The event handler can then use this to invoke the रेजिस्टरed
 * callback, without having to walk the list.
 *
 * For CPU निजी events, this काष्ठाure is per-cpu.
 */
काष्ठा sdei_रेजिस्टरed_event अणु
	/* For use by arch code: */
	काष्ठा pt_regs          पूर्णांकerrupted_regs;

	sdei_event_callback	*callback;
	व्योम			*callback_arg;
	u32			 event_num;
	u8			 priority;
पूर्ण;

/* The arch code entry poपूर्णांक should then call this when an event arrives. */
पूर्णांक notrace sdei_event_handler(काष्ठा pt_regs *regs,
			       काष्ठा sdei_रेजिस्टरed_event *arg);

/* arch code may use this to retrieve the extra रेजिस्टरs. */
पूर्णांक sdei_api_event_context(u32 query, u64 *result);

#पूर्ण_अगर /* __LINUX_ARM_SDEI_H */
