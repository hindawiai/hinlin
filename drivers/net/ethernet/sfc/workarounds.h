<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2006-2013 Solarflare Communications Inc.
 */

#अगर_अघोषित EFX_WORKAROUNDS_H
#घोषणा EFX_WORKAROUNDS_H

/*
 * Hardware workarounds.
 * Bug numbers are from Solarflare's Bugzilla.
 */

#घोषणा EFX_WORKAROUND_SIENA(efx) (efx_nic_rev(efx) == EFX_REV_SIENA_A0)
#घोषणा EFX_WORKAROUND_EF10(efx) (efx_nic_rev(efx) >= EFX_REV_HUNT_A0)
#घोषणा EFX_WORKAROUND_10G(efx) 1

/* Bit-bashed I2C पढ़ोs cause perक्रमmance drop */
#घोषणा EFX_WORKAROUND_7884 EFX_WORKAROUND_10G
/* Legacy पूर्णांकerrupt storm when पूर्णांकerrupt fअगरo fills */
#घोषणा EFX_WORKAROUND_17213 EFX_WORKAROUND_SIENA

/* Lockup when writing event block रेजिस्टरs at gen2/gen3 */
#घोषणा EFX_EF10_WORKAROUND_35388(efx)					\
	(((काष्ठा efx_ef10_nic_data *)efx->nic_data)->workaround_35388)
#घोषणा EFX_WORKAROUND_35388(efx)					\
	(efx_nic_rev(efx) == EFX_REV_HUNT_A0 && EFX_EF10_WORKAROUND_35388(efx))

/* Moderation समयr access must go through MCDI */
#घोषणा EFX_EF10_WORKAROUND_61265(efx)					\
	(((काष्ठा efx_ef10_nic_data *)efx->nic_data)->workaround_61265)

#पूर्ण_अगर /* EFX_WORKAROUNDS_H */
