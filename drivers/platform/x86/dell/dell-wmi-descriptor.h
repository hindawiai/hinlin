<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  Dell WMI descriptor driver
 *
 *  Copyright (c) 2017 Dell Inc.
 */

#अगर_अघोषित _DELL_WMI_DESCRIPTOR_H_
#घोषणा _DELL_WMI_DESCRIPTOR_H_

#समावेश <linux/wmi.h>

/* possible वापस values:
 *  -ENODEV: Descriptor GUID missing from WMI bus
 *  -EPROBE_DEFER: probing क्रम dell-wmi-descriptor not yet run
 *  0: valid descriptor, successfully probed
 *  < 0: invalid descriptor, करोn't probe dependent devices
 */
पूर्णांक dell_wmi_get_descriptor_valid(व्योम);

bool dell_wmi_get_पूर्णांकerface_version(u32 *version);
bool dell_wmi_get_size(u32 *size);
bool dell_wmi_get_hotfix(u32 *hotfix);

#पूर्ण_अगर
