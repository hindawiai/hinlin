<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* FIXME
 * move this to include/linux/mod_devicetable.h when merging
 */

#अगर_अघोषित __LINUX_GREYBUS_ID_H
#घोषणा __LINUX_GREYBUS_ID_H

#समावेश <linux/types.h>
#समावेश <linux/mod_devicetable.h>


काष्ठा greybus_bundle_id अणु
	__u16	match_flags;
	__u32	venकरोr;
	__u32	product;
	__u8	class;

	kernel_uदीर्घ_t	driver_info __aligned(माप(kernel_uदीर्घ_t));
पूर्ण;

/* Used to match the greybus_bundle_id */
#घोषणा GREYBUS_ID_MATCH_VENDOR		BIT(0)
#घोषणा GREYBUS_ID_MATCH_PRODUCT	BIT(1)
#घोषणा GREYBUS_ID_MATCH_CLASS		BIT(2)

#पूर्ण_अगर /* __LINUX_GREYBUS_ID_H */
