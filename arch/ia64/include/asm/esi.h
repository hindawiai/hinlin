<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * ESI service calls.
 *
 * Copyright (c) Copyright 2005-2006 Hewlett-Packard Development Company, L.P.
 * 	Alex Williamson <alex.williamson@hp.com>
 */
#अगर_अघोषित esi_h
#घोषणा esi_h

#समावेश <linux/efi.h>

#घोषणा ESI_QUERY			0x00000001
#घोषणा ESI_OPEN_HANDLE			0x02000000
#घोषणा ESI_CLOSE_HANDLE		0x02000001

क्रमागत esi_proc_type अणु
	ESI_PROC_SERIALIZED,	/* calls need to be serialized */
	ESI_PROC_MP_SAFE,	/* MP-safe, but not reentrant */
	ESI_PROC_REENTRANT	/* MP-safe and reentrant */
पूर्ण;

बाह्य काष्ठा ia64_sal_retval esi_call_phys (व्योम *, u64 *);
बाह्य पूर्णांक ia64_esi_call(efi_guid_t, काष्ठा ia64_sal_retval *,
			 क्रमागत esi_proc_type,
			 u64, u64, u64, u64, u64, u64, u64, u64);
बाह्य पूर्णांक ia64_esi_call_phys(efi_guid_t, काष्ठा ia64_sal_retval *, u64, u64,
                              u64, u64, u64, u64, u64, u64);

#पूर्ण_अगर /* esi_h */
