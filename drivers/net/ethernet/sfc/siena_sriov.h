<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2015 Solarflare Communications Inc.
 */

#अगर_अघोषित SIENA_SRIOV_H
#घोषणा SIENA_SRIOV_H

#समावेश "net_driver.h"

/* On the SFC9000 family each port is associated with 1 PCI physical
 * function (PF) handled by sfc and a configurable number of भव
 * functions (VFs) that may be handled by some other driver, often in
 * a VM guest.  The queue poपूर्णांकer रेजिस्टरs are mapped in both PF and
 * VF BARs such that an 8K region provides access to a single RX, TX
 * and event queue (collectively a Virtual Interface, VI or VNIC).
 *
 * The PF has access to all 1024 VIs जबतक VFs are mapped to VIs
 * according to VI_BASE and VI_SCALE: VF i has access to VIs numbered
 * in range [VI_BASE + i << VI_SCALE, VI_BASE + i + 1 << VI_SCALE).
 * The number of VIs and the VI_SCALE value are configurable but must
 * be established at boot समय by firmware.
 */

/* Maximum VI_SCALE parameter supported by Siena */
#घोषणा EFX_VI_SCALE_MAX 6
/* Base VI to use क्रम SR-IOV. Must be aligned to (1 << EFX_VI_SCALE_MAX),
 * so this is the smallest allowed value.
 */
#घोषणा EFX_VI_BASE 128U
/* Maximum number of VFs allowed */
#घोषणा EFX_VF_COUNT_MAX 127
/* Limit EVQs on VFs to be only 8k to reduce buffer table reservation */
#घोषणा EFX_MAX_VF_EVQ_SIZE 8192UL
/* The number of buffer table entries reserved क्रम each VI on a VF */
#घोषणा EFX_VF_BUFTBL_PER_VI					\
	((EFX_MAX_VF_EVQ_SIZE + 2 * EFX_MAX_DMAQ_SIZE) *	\
	 माप(efx_qword_t) / EFX_BUF_SIZE)

पूर्णांक efx_siena_sriov_configure(काष्ठा efx_nic *efx, पूर्णांक num_vfs);
पूर्णांक efx_siena_sriov_init(काष्ठा efx_nic *efx);
व्योम efx_siena_sriov_fini(काष्ठा efx_nic *efx);
पूर्णांक efx_siena_sriov_mac_address_changed(काष्ठा efx_nic *efx);
bool efx_siena_sriov_wanted(काष्ठा efx_nic *efx);
व्योम efx_siena_sriov_reset(काष्ठा efx_nic *efx);
व्योम efx_siena_sriov_flr(काष्ठा efx_nic *efx, अचिन्हित flr);

पूर्णांक efx_siena_sriov_set_vf_mac(काष्ठा efx_nic *efx, पूर्णांक vf, u8 *mac);
पूर्णांक efx_siena_sriov_set_vf_vlan(काष्ठा efx_nic *efx, पूर्णांक vf,
				u16 vlan, u8 qos);
पूर्णांक efx_siena_sriov_set_vf_spoofchk(काष्ठा efx_nic *efx, पूर्णांक vf,
				    bool spoofchk);
पूर्णांक efx_siena_sriov_get_vf_config(काष्ठा efx_nic *efx, पूर्णांक vf,
				  काष्ठा अगरla_vf_info *ivf);

#अगर_घोषित CONFIG_SFC_SRIOV

अटल अंतरभूत bool efx_siena_sriov_enabled(काष्ठा efx_nic *efx)
अणु
	वापस efx->vf_init_count != 0;
पूर्ण
#अन्यथा /* !CONFIG_SFC_SRIOV */
अटल अंतरभूत bool efx_siena_sriov_enabled(काष्ठा efx_nic *efx)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर /* CONFIG_SFC_SRIOV */

व्योम efx_siena_sriov_probe(काष्ठा efx_nic *efx);
व्योम efx_siena_sriov_tx_flush_करोne(काष्ठा efx_nic *efx, efx_qword_t *event);
व्योम efx_siena_sriov_rx_flush_करोne(काष्ठा efx_nic *efx, efx_qword_t *event);
व्योम efx_siena_sriov_event(काष्ठा efx_channel *channel, efx_qword_t *event);
व्योम efx_siena_sriov_desc_fetch_err(काष्ठा efx_nic *efx, अचिन्हित dmaq);

#पूर्ण_अगर /* SIENA_SRIOV_H */
