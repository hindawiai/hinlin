<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2015-2018 Netronome Systems, Inc. */

/*
 * nfp.h
 * Interface क्रम NFP device access and query functions.
 */

#अगर_अघोषित __NFP_H__
#घोषणा __NFP_H__

#समावेश <linux/device.h>
#समावेश <linux/types.h>

#समावेश "nfp_cpp.h"

/* Implemented in nfp_hwinfo.c */

काष्ठा nfp_hwinfo;
काष्ठा nfp_hwinfo *nfp_hwinfo_पढ़ो(काष्ठा nfp_cpp *cpp);
स्थिर अक्षर *nfp_hwinfo_lookup(काष्ठा nfp_hwinfo *hwinfo, स्थिर अक्षर *lookup);
अक्षर *nfp_hwinfo_get_packed_strings(काष्ठा nfp_hwinfo *hwinfo);
u32 nfp_hwinfo_get_packed_str_size(काष्ठा nfp_hwinfo *hwinfo);

/* Implemented in nfp_nsp.c, low level functions */

काष्ठा nfp_nsp;

काष्ठा nfp_cpp *nfp_nsp_cpp(काष्ठा nfp_nsp *state);
bool nfp_nsp_config_modअगरied(काष्ठा nfp_nsp *state);
व्योम nfp_nsp_config_set_modअगरied(काष्ठा nfp_nsp *state, bool modअगरied);
व्योम *nfp_nsp_config_entries(काष्ठा nfp_nsp *state);
अचिन्हित पूर्णांक nfp_nsp_config_idx(काष्ठा nfp_nsp *state);
व्योम nfp_nsp_config_set_state(काष्ठा nfp_nsp *state, व्योम *entries,
			      अचिन्हित पूर्णांक idx);
व्योम nfp_nsp_config_clear_state(काष्ठा nfp_nsp *state);
पूर्णांक nfp_nsp_पढ़ो_eth_table(काष्ठा nfp_nsp *state, व्योम *buf, अचिन्हित पूर्णांक size);
पूर्णांक nfp_nsp_ग_लिखो_eth_table(काष्ठा nfp_nsp *state,
			    स्थिर व्योम *buf, अचिन्हित पूर्णांक size);
पूर्णांक nfp_nsp_पढ़ो_identअगरy(काष्ठा nfp_nsp *state, व्योम *buf, अचिन्हित पूर्णांक size);
पूर्णांक nfp_nsp_पढ़ो_sensors(काष्ठा nfp_nsp *state, अचिन्हित पूर्णांक sensor_mask,
			 व्योम *buf, अचिन्हित पूर्णांक size);

/* Implemented in nfp_resource.c */

/* All keys are CRC32-POSIX of the 8-byte identअगरication string */

/* ARM/PCI vNIC Interfaces 0..3 */
#घोषणा NFP_RESOURCE_VNIC_PCI_0		"vnic.p0"
#घोषणा NFP_RESOURCE_VNIC_PCI_1		"vnic.p1"
#घोषणा NFP_RESOURCE_VNIC_PCI_2		"vnic.p2"
#घोषणा NFP_RESOURCE_VNIC_PCI_3		"vnic.p3"

/* NFP Hardware Info Database */
#घोषणा NFP_RESOURCE_NFP_HWINFO		"nfp.info"

/* Service Processor */
#घोषणा NFP_RESOURCE_NSP		"nfp.sp"
#घोषणा NFP_RESOURCE_NSP_DIAG		"arm.diag"

/* Netronone Flow Firmware Table */
#घोषणा NFP_RESOURCE_NFP_NFFW		"nfp.nffw"

/* MAC Statistics Accumulator */
#घोषणा NFP_RESOURCE_MAC_STATISTICS	"mac.stat"

पूर्णांक nfp_resource_table_init(काष्ठा nfp_cpp *cpp);

काष्ठा nfp_resource *
nfp_resource_acquire(काष्ठा nfp_cpp *cpp, स्थिर अक्षर *name);

व्योम nfp_resource_release(काष्ठा nfp_resource *res);

पूर्णांक nfp_resource_रुको(काष्ठा nfp_cpp *cpp, स्थिर अक्षर *name, अचिन्हित पूर्णांक secs);

u32 nfp_resource_cpp_id(काष्ठा nfp_resource *res);

स्थिर अक्षर *nfp_resource_name(काष्ठा nfp_resource *res);

u64 nfp_resource_address(काष्ठा nfp_resource *res);

u64 nfp_resource_size(काष्ठा nfp_resource *res);

#पूर्ण_अगर /* !__NFP_H__ */
