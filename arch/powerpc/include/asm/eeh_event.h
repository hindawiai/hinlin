<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 *
 * Copyright (c) 2005 Linas Vepstas <linas@linas.org>
 */

#अगर_अघोषित ASM_POWERPC_EEH_EVENT_H
#घोषणा ASM_POWERPC_EEH_EVENT_H
#अगर_घोषित __KERNEL__

/*
 * काष्ठाure holding pci controller data that describes a
 * change in the isolation status of a PCI slot.  A poपूर्णांकer
 * to this काष्ठा is passed as the data poपूर्णांकer in a notअगरy
 * callback.
 */
काष्ठा eeh_event अणु
	काष्ठा list_head	list;	/* to क्रमm event queue	*/
	काष्ठा eeh_pe		*pe;	/* EEH PE		*/
पूर्ण;

पूर्णांक eeh_event_init(व्योम);
पूर्णांक eeh_send_failure_event(काष्ठा eeh_pe *pe);
पूर्णांक __eeh_send_failure_event(काष्ठा eeh_pe *pe);
व्योम eeh_हटाओ_event(काष्ठा eeh_pe *pe, bool क्रमce);
व्योम eeh_handle_normal_event(काष्ठा eeh_pe *pe);
व्योम eeh_handle_special_event(व्योम);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* ASM_POWERPC_EEH_EVENT_H */
