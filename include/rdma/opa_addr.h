<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright(c) 2017 Intel Corporation.
 */

#अगर_अघोषित OPA_ADDR_H
#घोषणा OPA_ADDR_H

#समावेश <rdma/opa_smi.h>

#घोषणा	OPA_SPECIAL_OUI		(0x00066AULL)
#घोषणा OPA_MAKE_ID(x)          (cpu_to_be64(OPA_SPECIAL_OUI << 40 | (x)))
#घोषणा OPA_TO_IB_UCAST_LID(x) (((x) >= be16_to_cpu(IB_MULTICAST_LID_BASE)) \
				? 0 : x)
#घोषणा OPA_GID_INDEX		0x1
/**
 * 0xF8 - 4 bits of multicast range and 1 bit क्रम collective range
 * Example: For 24 bit LID space,
 * Multicast range: 0xF00000 to 0xF7FFFF
 * Collective range: 0xF80000 to 0xFFFFFE
 */
#घोषणा OPA_MCAST_NR 0x4 /* Number of top bits set */
#घोषणा OPA_COLLECTIVE_NR 0x1 /* Number of bits after MCAST_NR */

/**
 * ib_is_opa_gid: Returns true अगर the top 24 bits of the gid
 * contains the OPA_STL_OUI identअगरier. This identअगरies that
 * the provided gid is a special purpose GID meant to carry
 * extended LID inक्रमmation.
 *
 * @gid: The Global identअगरier
 */
अटल अंतरभूत bool ib_is_opa_gid(स्थिर जोड़ ib_gid *gid)
अणु
	वापस ((be64_to_cpu(gid->global.पूर्णांकerface_id) >> 40) ==
		OPA_SPECIAL_OUI);
पूर्ण

/**
 * opa_get_lid_from_gid: Returns the last 32 bits of the gid.
 * OPA devices use one of the gids in the gid table to also
 * store the lid.
 *
 * @gid: The Global identअगरier
 */
अटल अंतरभूत u32 opa_get_lid_from_gid(स्थिर जोड़ ib_gid *gid)
अणु
	वापस be64_to_cpu(gid->global.पूर्णांकerface_id) & 0xFFFFFFFF;
पूर्ण

/**
 * opa_is_extended_lid: Returns true अगर dlid or slid are
 * extended.
 *
 * @dlid: The DLID
 * @slid: The SLID
 */
अटल अंतरभूत bool opa_is_extended_lid(__be32 dlid, __be32 slid)
अणु
	अगर ((be32_to_cpu(dlid) >=
	     be16_to_cpu(IB_MULTICAST_LID_BASE)) ||
	    (be32_to_cpu(slid) >=
	     be16_to_cpu(IB_MULTICAST_LID_BASE)))
		वापस true;

	वापस false;
पूर्ण

/* Get multicast lid base */
अटल अंतरभूत u32 opa_get_mcast_base(u32 nr_top_bits)
अणु
	वापस (be32_to_cpu(OPA_LID_PERMISSIVE) << (32 - nr_top_bits));
पूर्ण

/* Check क्रम a valid unicast LID क्रम non-SM traffic types */
अटल अंतरभूत bool rdma_is_valid_unicast_lid(काष्ठा rdma_ah_attr *attr)
अणु
	अगर (attr->type == RDMA_AH_ATTR_TYPE_IB) अणु
		अगर (!rdma_ah_get_dlid(attr) ||
		    rdma_ah_get_dlid(attr) >=
		    be16_to_cpu(IB_MULTICAST_LID_BASE))
			वापस false;
	पूर्ण अन्यथा अगर (attr->type == RDMA_AH_ATTR_TYPE_OPA) अणु
		अगर (!rdma_ah_get_dlid(attr) ||
		    rdma_ah_get_dlid(attr) >=
		    opa_get_mcast_base(OPA_MCAST_NR))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण
#पूर्ण_अगर /* OPA_ADDR_H */
