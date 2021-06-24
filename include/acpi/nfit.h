<शैली गुरु>
/*
 * SPDX-License-Identअगरier: GPL-2.0
 * Copyright (C) 2018 Intel Corporation
 */

#अगर_अघोषित __ACPI_NFIT_H
#घोषणा __ACPI_NFIT_H

#अगर IS_ENABLED(CONFIG_ACPI_NFIT)
पूर्णांक nfit_get_smbios_id(u32 device_handle, u16 *flags);
#अन्यथा
अटल अंतरभूत पूर्णांक nfit_get_smbios_id(u32 device_handle, u16 *flags)
अणु
	वापस -EOPNOTSUPP;
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ACPI_NFIT_H */
