<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * runसमय-wrappers.c - Runसमय Services function call wrappers
 *
 * Implementation summary:
 * -----------------------
 * 1. When user/kernel thपढ़ो requests to execute efi_runसमय_service(),
 * enqueue work to efi_rts_wq.
 * 2. Caller thपढ़ो रुकोs क्रम completion until the work is finished
 * because it's dependent on the वापस status and execution of
 * efi_runसमय_service().
 * For instance, get_variable() and get_next_variable().
 *
 * Copyright (C) 2014 Linaro Ltd. <ard.biesheuvel@linaro.org>
 *
 * Split off from arch/x86/platक्रमm/efi/efi.c
 *
 * Copyright (C) 1999 VA Linux Systems
 * Copyright (C) 1999 Walt Drummond <drummond@valinux.com>
 * Copyright (C) 1999-2002 Hewlett-Packard Co.
 * Copyright (C) 2005-2008 Intel Co.
 * Copyright (C) 2013 SuSE Lअसल
 */

#घोषणा pr_fmt(fmt)	"efi: " fmt

#समावेश <linux/bug.h>
#समावेश <linux/efi.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/mutex.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/completion.h>

#समावेश <यंत्र/efi.h>

/*
 * Wrap around the new efi_call_virt_generic() macros so that the
 * code करोesn't get too cluttered:
 */
#घोषणा efi_call_virt(f, args...)   \
	efi_call_virt_poपूर्णांकer(efi.runसमय, f, args)
#घोषणा __efi_call_virt(f, args...) \
	__efi_call_virt_poपूर्णांकer(efi.runसमय, f, args)

काष्ठा efi_runसमय_work efi_rts_work;

/*
 * efi_queue_work:	Queue efi_runसमय_service() and रुको until it's करोne
 * @rts:		efi_runसमय_service() function identअगरier
 * @rts_arg<1-5>:	efi_runसमय_service() function arguments
 *
 * Accesses to efi_runसमय_services() are serialized by a binary
 * semaphore (efi_runसमय_lock) and caller रुकोs until the work is
 * finished, hence _only_ one work is queued at a समय and the caller
 * thपढ़ो रुकोs क्रम completion.
 */
#घोषणा efi_queue_work(_rts, _arg1, _arg2, _arg3, _arg4, _arg5)		\
(अणु									\
	efi_rts_work.status = EFI_ABORTED;				\
									\
	अगर (!efi_enabled(EFI_RUNTIME_SERVICES)) अणु			\
		pr_warn_once("EFI Runtime Services are disabled!\n");	\
		जाओ निकास;						\
	पूर्ण								\
									\
	init_completion(&efi_rts_work.efi_rts_comp);			\
	INIT_WORK(&efi_rts_work.work, efi_call_rts);			\
	efi_rts_work.arg1 = _arg1;					\
	efi_rts_work.arg2 = _arg2;					\
	efi_rts_work.arg3 = _arg3;					\
	efi_rts_work.arg4 = _arg4;					\
	efi_rts_work.arg5 = _arg5;					\
	efi_rts_work.efi_rts_id = _rts;					\
									\
	/*								\
	 * queue_work() वापसs 0 अगर work was alपढ़ोy on queue,         \
	 * _ideally_ this should never happen.                          \
	 */								\
	अगर (queue_work(efi_rts_wq, &efi_rts_work.work))			\
		रुको_क्रम_completion(&efi_rts_work.efi_rts_comp);	\
	अन्यथा								\
		pr_err("Failed to queue work to efi_rts_wq.\n");	\
									\
निकास:									\
	efi_rts_work.efi_rts_id = EFI_NONE;				\
	efi_rts_work.status;						\
पूर्ण)

#अगर_अघोषित arch_efi_save_flags
#घोषणा arch_efi_save_flags(state_flags)	local_save_flags(state_flags)
#घोषणा arch_efi_restore_flags(state_flags)	local_irq_restore(state_flags)
#पूर्ण_अगर

अचिन्हित दीर्घ efi_call_virt_save_flags(व्योम)
अणु
	अचिन्हित दीर्घ flags;

	arch_efi_save_flags(flags);
	वापस flags;
पूर्ण

व्योम efi_call_virt_check_flags(अचिन्हित दीर्घ flags, स्थिर अक्षर *call)
अणु
	अचिन्हित दीर्घ cur_flags, mismatch;

	cur_flags = efi_call_virt_save_flags();

	mismatch = flags ^ cur_flags;
	अगर (!WARN_ON_ONCE(mismatch & ARCH_EFI_IRQ_FLAGS_MASK))
		वापस;

	add_taपूर्णांक(TAINT_FIRMWARE_WORKAROUND, LOCKDEP_NOW_UNRELIABLE);
	pr_err_ratelimited(FW_BUG "IRQ flags corrupted (0x%08lx=>0x%08lx) by EFI %s\n",
			   flags, cur_flags, call);
	arch_efi_restore_flags(flags);
पूर्ण

/*
 * According to section 7.1 of the UEFI spec, Runसमय Services are not fully
 * reentrant, and there are particular combinations of calls that need to be
 * serialized. (source: UEFI Specअगरication v2.4A)
 *
 * Table 31. Rules क्रम Reentry Into Runसमय Services
 * +------------------------------------+-------------------------------+
 * | If previous call is busy in	| Forbidden to call		|
 * +------------------------------------+-------------------------------+
 * | Any				| SetVirtualAddressMap()	|
 * +------------------------------------+-------------------------------+
 * | ConvertPoपूर्णांकer()			| ConvertPoपूर्णांकer()		|
 * +------------------------------------+-------------------------------+
 * | SetVariable()			| ResetSystem()			|
 * | UpdateCapsule()			|				|
 * | SetTime()				|				|
 * | SetWakeupTime()			|				|
 * | GetNextHighMonotonicCount()	|				|
 * +------------------------------------+-------------------------------+
 * | GetVariable()			| GetVariable()			|
 * | GetNextVariableName()		| GetNextVariableName()		|
 * | SetVariable()			| SetVariable()			|
 * | QueryVariableInfo()		| QueryVariableInfo()		|
 * | UpdateCapsule()			| UpdateCapsule()		|
 * | QueryCapsuleCapabilities()		| QueryCapsuleCapabilities()	|
 * | GetNextHighMonotonicCount()	| GetNextHighMonotonicCount()	|
 * +------------------------------------+-------------------------------+
 * | GetTime()				| GetTime()			|
 * | SetTime()				| SetTime()			|
 * | GetWakeupTime()			| GetWakeupTime()		|
 * | SetWakeupTime()			| SetWakeupTime()		|
 * +------------------------------------+-------------------------------+
 *
 * Due to the fact that the EFI pstore may ग_लिखो to the variable store in
 * पूर्णांकerrupt context, we need to use a lock क्रम at least the groups that
 * contain SetVariable() and QueryVariableInfo(). That leaves little अन्यथा, as
 * none of the reमुख्यing functions are actually ever called at runसमय.
 * So let's just use a single lock to serialize all Runसमय Services calls.
 */
अटल DEFINE_SEMAPHORE(efi_runसमय_lock);

/*
 * Expose the EFI runसमय lock to the UV platक्रमm
 */
#अगर_घोषित CONFIG_X86_UV
बाह्य काष्ठा semaphore __efi_uv_runसमय_lock __alias(efi_runसमय_lock);
#पूर्ण_अगर

/*
 * Calls the appropriate efi_runसमय_service() with the appropriate
 * arguments.
 *
 * Semantics followed by efi_call_rts() to understand efi_runसमय_work:
 * 1. If argument was a poपूर्णांकer, recast it from व्योम poपूर्णांकer to original
 * poपूर्णांकer type.
 * 2. If argument was a value, recast it from व्योम poपूर्णांकer to original
 * poपूर्णांकer type and dereference it.
 */
अटल व्योम efi_call_rts(काष्ठा work_काष्ठा *work)
अणु
	व्योम *arg1, *arg2, *arg3, *arg4, *arg5;
	efi_status_t status = EFI_NOT_FOUND;

	arg1 = efi_rts_work.arg1;
	arg2 = efi_rts_work.arg2;
	arg3 = efi_rts_work.arg3;
	arg4 = efi_rts_work.arg4;
	arg5 = efi_rts_work.arg5;

	चयन (efi_rts_work.efi_rts_id) अणु
	हाल EFI_GET_TIME:
		status = efi_call_virt(get_समय, (efi_समय_प्रकार *)arg1,
				       (efi_समय_cap_t *)arg2);
		अवरोध;
	हाल EFI_SET_TIME:
		status = efi_call_virt(set_समय, (efi_समय_प्रकार *)arg1);
		अवरोध;
	हाल EFI_GET_WAKEUP_TIME:
		status = efi_call_virt(get_wakeup_समय, (efi_bool_t *)arg1,
				       (efi_bool_t *)arg2, (efi_समय_प्रकार *)arg3);
		अवरोध;
	हाल EFI_SET_WAKEUP_TIME:
		status = efi_call_virt(set_wakeup_समय, *(efi_bool_t *)arg1,
				       (efi_समय_प्रकार *)arg2);
		अवरोध;
	हाल EFI_GET_VARIABLE:
		status = efi_call_virt(get_variable, (efi_अक्षर16_t *)arg1,
				       (efi_guid_t *)arg2, (u32 *)arg3,
				       (अचिन्हित दीर्घ *)arg4, (व्योम *)arg5);
		अवरोध;
	हाल EFI_GET_NEXT_VARIABLE:
		status = efi_call_virt(get_next_variable, (अचिन्हित दीर्घ *)arg1,
				       (efi_अक्षर16_t *)arg2,
				       (efi_guid_t *)arg3);
		अवरोध;
	हाल EFI_SET_VARIABLE:
		status = efi_call_virt(set_variable, (efi_अक्षर16_t *)arg1,
				       (efi_guid_t *)arg2, *(u32 *)arg3,
				       *(अचिन्हित दीर्घ *)arg4, (व्योम *)arg5);
		अवरोध;
	हाल EFI_QUERY_VARIABLE_INFO:
		status = efi_call_virt(query_variable_info, *(u32 *)arg1,
				       (u64 *)arg2, (u64 *)arg3, (u64 *)arg4);
		अवरोध;
	हाल EFI_GET_NEXT_HIGH_MONO_COUNT:
		status = efi_call_virt(get_next_high_mono_count, (u32 *)arg1);
		अवरोध;
	हाल EFI_UPDATE_CAPSULE:
		status = efi_call_virt(update_capsule,
				       (efi_capsule_header_t **)arg1,
				       *(अचिन्हित दीर्घ *)arg2,
				       *(अचिन्हित दीर्घ *)arg3);
		अवरोध;
	हाल EFI_QUERY_CAPSULE_CAPS:
		status = efi_call_virt(query_capsule_caps,
				       (efi_capsule_header_t **)arg1,
				       *(अचिन्हित दीर्घ *)arg2, (u64 *)arg3,
				       (पूर्णांक *)arg4);
		अवरोध;
	शेष:
		/*
		 * Ideally, we should never reach here because a caller of this
		 * function should have put the right efi_runसमय_service()
		 * function identअगरier पूर्णांकo efi_rts_work->efi_rts_id
		 */
		pr_err("Requested executing invalid EFI Runtime Service.\n");
	पूर्ण
	efi_rts_work.status = status;
	complete(&efi_rts_work.efi_rts_comp);
पूर्ण

अटल efi_status_t virt_efi_get_समय(efi_समय_प्रकार *पंचांग, efi_समय_cap_t *tc)
अणु
	efi_status_t status;

	अगर (करोwn_पूर्णांकerruptible(&efi_runसमय_lock))
		वापस EFI_ABORTED;
	status = efi_queue_work(EFI_GET_TIME, पंचांग, tc, शून्य, शून्य, शून्य);
	up(&efi_runसमय_lock);
	वापस status;
पूर्ण

अटल efi_status_t virt_efi_set_समय(efi_समय_प्रकार *पंचांग)
अणु
	efi_status_t status;

	अगर (करोwn_पूर्णांकerruptible(&efi_runसमय_lock))
		वापस EFI_ABORTED;
	status = efi_queue_work(EFI_SET_TIME, पंचांग, शून्य, शून्य, शून्य, शून्य);
	up(&efi_runसमय_lock);
	वापस status;
पूर्ण

अटल efi_status_t virt_efi_get_wakeup_समय(efi_bool_t *enabled,
					     efi_bool_t *pending,
					     efi_समय_प्रकार *पंचांग)
अणु
	efi_status_t status;

	अगर (करोwn_पूर्णांकerruptible(&efi_runसमय_lock))
		वापस EFI_ABORTED;
	status = efi_queue_work(EFI_GET_WAKEUP_TIME, enabled, pending, पंचांग, शून्य,
				शून्य);
	up(&efi_runसमय_lock);
	वापस status;
पूर्ण

अटल efi_status_t virt_efi_set_wakeup_समय(efi_bool_t enabled, efi_समय_प्रकार *पंचांग)
अणु
	efi_status_t status;

	अगर (करोwn_पूर्णांकerruptible(&efi_runसमय_lock))
		वापस EFI_ABORTED;
	status = efi_queue_work(EFI_SET_WAKEUP_TIME, &enabled, पंचांग, शून्य, शून्य,
				शून्य);
	up(&efi_runसमय_lock);
	वापस status;
पूर्ण

अटल efi_status_t virt_efi_get_variable(efi_अक्षर16_t *name,
					  efi_guid_t *venकरोr,
					  u32 *attr,
					  अचिन्हित दीर्घ *data_size,
					  व्योम *data)
अणु
	efi_status_t status;

	अगर (करोwn_पूर्णांकerruptible(&efi_runसमय_lock))
		वापस EFI_ABORTED;
	status = efi_queue_work(EFI_GET_VARIABLE, name, venकरोr, attr, data_size,
				data);
	up(&efi_runसमय_lock);
	वापस status;
पूर्ण

अटल efi_status_t virt_efi_get_next_variable(अचिन्हित दीर्घ *name_size,
					       efi_अक्षर16_t *name,
					       efi_guid_t *venकरोr)
अणु
	efi_status_t status;

	अगर (करोwn_पूर्णांकerruptible(&efi_runसमय_lock))
		वापस EFI_ABORTED;
	status = efi_queue_work(EFI_GET_NEXT_VARIABLE, name_size, name, venकरोr,
				शून्य, शून्य);
	up(&efi_runसमय_lock);
	वापस status;
पूर्ण

अटल efi_status_t virt_efi_set_variable(efi_अक्षर16_t *name,
					  efi_guid_t *venकरोr,
					  u32 attr,
					  अचिन्हित दीर्घ data_size,
					  व्योम *data)
अणु
	efi_status_t status;

	अगर (करोwn_पूर्णांकerruptible(&efi_runसमय_lock))
		वापस EFI_ABORTED;
	status = efi_queue_work(EFI_SET_VARIABLE, name, venकरोr, &attr, &data_size,
				data);
	up(&efi_runसमय_lock);
	वापस status;
पूर्ण

अटल efi_status_t
virt_efi_set_variable_nonblocking(efi_अक्षर16_t *name, efi_guid_t *venकरोr,
				  u32 attr, अचिन्हित दीर्घ data_size,
				  व्योम *data)
अणु
	efi_status_t status;

	अगर (करोwn_trylock(&efi_runसमय_lock))
		वापस EFI_NOT_READY;

	status = efi_call_virt(set_variable, name, venकरोr, attr, data_size,
			       data);
	up(&efi_runसमय_lock);
	वापस status;
पूर्ण


अटल efi_status_t virt_efi_query_variable_info(u32 attr,
						 u64 *storage_space,
						 u64 *reमुख्यing_space,
						 u64 *max_variable_size)
अणु
	efi_status_t status;

	अगर (efi.runसमय_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		वापस EFI_UNSUPPORTED;

	अगर (करोwn_पूर्णांकerruptible(&efi_runसमय_lock))
		वापस EFI_ABORTED;
	status = efi_queue_work(EFI_QUERY_VARIABLE_INFO, &attr, storage_space,
				reमुख्यing_space, max_variable_size, शून्य);
	up(&efi_runसमय_lock);
	वापस status;
पूर्ण

अटल efi_status_t
virt_efi_query_variable_info_nonblocking(u32 attr,
					 u64 *storage_space,
					 u64 *reमुख्यing_space,
					 u64 *max_variable_size)
अणु
	efi_status_t status;

	अगर (efi.runसमय_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		वापस EFI_UNSUPPORTED;

	अगर (करोwn_trylock(&efi_runसमय_lock))
		वापस EFI_NOT_READY;

	status = efi_call_virt(query_variable_info, attr, storage_space,
			       reमुख्यing_space, max_variable_size);
	up(&efi_runसमय_lock);
	वापस status;
पूर्ण

अटल efi_status_t virt_efi_get_next_high_mono_count(u32 *count)
अणु
	efi_status_t status;

	अगर (करोwn_पूर्णांकerruptible(&efi_runसमय_lock))
		वापस EFI_ABORTED;
	status = efi_queue_work(EFI_GET_NEXT_HIGH_MONO_COUNT, count, शून्य, शून्य,
				शून्य, शून्य);
	up(&efi_runसमय_lock);
	वापस status;
पूर्ण

अटल व्योम virt_efi_reset_प्रणाली(पूर्णांक reset_type,
				  efi_status_t status,
				  अचिन्हित दीर्घ data_size,
				  efi_अक्षर16_t *data)
अणु
	अगर (करोwn_पूर्णांकerruptible(&efi_runसमय_lock)) अणु
		pr_warn("failed to invoke the reset_system() runtime service:\n"
			"could not get exclusive access to the firmware\n");
		वापस;
	पूर्ण
	efi_rts_work.efi_rts_id = EFI_RESET_SYSTEM;
	__efi_call_virt(reset_प्रणाली, reset_type, status, data_size, data);
	up(&efi_runसमय_lock);
पूर्ण

अटल efi_status_t virt_efi_update_capsule(efi_capsule_header_t **capsules,
					    अचिन्हित दीर्घ count,
					    अचिन्हित दीर्घ sg_list)
अणु
	efi_status_t status;

	अगर (efi.runसमय_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		वापस EFI_UNSUPPORTED;

	अगर (करोwn_पूर्णांकerruptible(&efi_runसमय_lock))
		वापस EFI_ABORTED;
	status = efi_queue_work(EFI_UPDATE_CAPSULE, capsules, &count, &sg_list,
				शून्य, शून्य);
	up(&efi_runसमय_lock);
	वापस status;
पूर्ण

अटल efi_status_t virt_efi_query_capsule_caps(efi_capsule_header_t **capsules,
						अचिन्हित दीर्घ count,
						u64 *max_size,
						पूर्णांक *reset_type)
अणु
	efi_status_t status;

	अगर (efi.runसमय_version < EFI_2_00_SYSTEM_TABLE_REVISION)
		वापस EFI_UNSUPPORTED;

	अगर (करोwn_पूर्णांकerruptible(&efi_runसमय_lock))
		वापस EFI_ABORTED;
	status = efi_queue_work(EFI_QUERY_CAPSULE_CAPS, capsules, &count,
				max_size, reset_type, शून्य);
	up(&efi_runसमय_lock);
	वापस status;
पूर्ण

व्योम efi_native_runसमय_setup(व्योम)
अणु
	efi.get_समय = virt_efi_get_समय;
	efi.set_समय = virt_efi_set_समय;
	efi.get_wakeup_समय = virt_efi_get_wakeup_समय;
	efi.set_wakeup_समय = virt_efi_set_wakeup_समय;
	efi.get_variable = virt_efi_get_variable;
	efi.get_next_variable = virt_efi_get_next_variable;
	efi.set_variable = virt_efi_set_variable;
	efi.set_variable_nonblocking = virt_efi_set_variable_nonblocking;
	efi.get_next_high_mono_count = virt_efi_get_next_high_mono_count;
	efi.reset_प्रणाली = virt_efi_reset_प्रणाली;
	efi.query_variable_info = virt_efi_query_variable_info;
	efi.query_variable_info_nonblocking = virt_efi_query_variable_info_nonblocking;
	efi.update_capsule = virt_efi_update_capsule;
	efi.query_capsule_caps = virt_efi_query_capsule_caps;
पूर्ण
