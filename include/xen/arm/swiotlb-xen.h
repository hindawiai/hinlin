<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _ASM_ARM_SWIOTLB_XEN_H
#घोषणा _ASM_ARM_SWIOTLB_XEN_H

#समावेश <xen/features.h>
#समावेश <xen/xen.h>

अटल अंतरभूत पूर्णांक xen_swiotlb_detect(व्योम)
अणु
	अगर (!xen_करोमुख्य())
		वापस 0;
	अगर (xen_feature(XENFEAT_direct_mapped))
		वापस 1;
	/* legacy हाल */
	अगर (!xen_feature(XENFEAT_not_direct_mapped) && xen_initial_करोमुख्य())
		वापस 1;
	वापस 0;
पूर्ण

#पूर्ण_अगर /* _ASM_ARM_SWIOTLB_XEN_H */
