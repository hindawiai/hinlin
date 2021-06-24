<शैली गुरु>
/******************************************************************************
 * callback.h
 *
 * Register guest OS callbacks with Xen.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this software and associated करोcumentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modअगरy, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to करो so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 *
 * Copyright (c) 2006, Ian Campbell
 */

#अगर_अघोषित __XEN_PUBLIC_CALLBACK_H__
#घोषणा __XEN_PUBLIC_CALLBACK_H__

#समावेश <xen/पूर्णांकerface/xen.h>

/*
 * Prototype क्रम this hypercall is:
 *   दीर्घ callback_op(पूर्णांक cmd, व्योम *extra_args)
 * @cmd        == CALLBACKOP_??? (callback operation).
 * @extra_args == Operation-specअगरic extra arguments (शून्य अगर none).
 */

/* x86: Callback क्रम event delivery. */
#घोषणा CALLBACKTYPE_event                 0

/* x86: Failsafe callback when guest state cannot be restored by Xen. */
#घोषणा CALLBACKTYPE_failsafe              1

/* x86/64 hypervisor: Syscall by 64-bit guest app ('64-on-64-on-64'). */
#घोषणा CALLBACKTYPE_syscall               2

/*
 * x86/32 hypervisor: Only available on x86/32 when supervisor_mode_kernel
 *     feature is enabled. Do not use this callback type in new code.
 */
#घोषणा CALLBACKTYPE_sysenter_deprecated   3

/* x86: Callback क्रम NMI delivery. */
#घोषणा CALLBACKTYPE_nmi                   4

/*
 * x86: sysenter is only available as follows:
 * - 32-bit hypervisor: with the supervisor_mode_kernel feature enabled
 * - 64-bit hypervisor: 32-bit guest applications on Intel CPUs
 *                      ('32-on-32-on-64', '32-on-64-on-64')
 *                      [nb. also 64-bit guest applications on Intel CPUs
 *                           ('64-on-64-on-64'), but syscall is preferred]
 */
#घोषणा CALLBACKTYPE_sysenter              5

/*
 * x86/64 hypervisor: Syscall by 32-bit guest app on AMD CPUs
 *                    ('32-on-32-on-64', '32-on-64-on-64')
 */
#घोषणा CALLBACKTYPE_syscall32             7

/*
 * Disable event deliver during callback? This flag is ignored क्रम event and
 * NMI callbacks: event delivery is unconditionally disabled.
 */
#घोषणा _CALLBACKF_mask_events             0
#घोषणा CALLBACKF_mask_events              (1U << _CALLBACKF_mask_events)

/*
 * Register a callback.
 */
#घोषणा CALLBACKOP_रेजिस्टर                0
काष्ठा callback_रेजिस्टर अणु
	uपूर्णांक16_t type;
	uपूर्णांक16_t flags;
	xen_callback_t address;
पूर्ण;

/*
 * Unरेजिस्टर a callback.
 *
 * Not all callbacks can be unरेजिस्टरed. -EINVAL will be वापसed अगर
 * you attempt to unरेजिस्टर such a callback.
 */
#घोषणा CALLBACKOP_unरेजिस्टर              1
काष्ठा callback_unरेजिस्टर अणु
    uपूर्णांक16_t type;
    uपूर्णांक16_t _unused;
पूर्ण;

#पूर्ण_अगर /* __XEN_PUBLIC_CALLBACK_H__ */
