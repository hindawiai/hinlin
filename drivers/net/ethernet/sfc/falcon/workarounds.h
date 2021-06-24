<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2006-2013 Solarflare Communications Inc.
 */

#अगर_अघोषित EF4_WORKAROUNDS_H
#घोषणा EF4_WORKAROUNDS_H

/*
 * Hardware workarounds.
 * Bug numbers are from Solarflare's Bugzilla.
 */

#घोषणा EF4_WORKAROUND_FALCON_A(efx) (ef4_nic_rev(efx) <= EF4_REV_FALCON_A1)
#घोषणा EF4_WORKAROUND_FALCON_AB(efx) (ef4_nic_rev(efx) <= EF4_REV_FALCON_B0)
#घोषणा EF4_WORKAROUND_10G(efx) 1

/* Bit-bashed I2C पढ़ोs cause perक्रमmance drop */
#घोषणा EF4_WORKAROUND_7884 EF4_WORKAROUND_10G
/* Truncated IPv4 packets can confuse the TX packet parser */
#घोषणा EF4_WORKAROUND_15592 EF4_WORKAROUND_FALCON_AB

/* Spurious parity errors in TSORT buffers */
#घोषणा EF4_WORKAROUND_5129 EF4_WORKAROUND_FALCON_A
/* Unaligned पढ़ो request >512 bytes after aligning may अवरोध TSORT */
#घोषणा EF4_WORKAROUND_5391 EF4_WORKAROUND_FALCON_A
/* iSCSI parsing errors */
#घोषणा EF4_WORKAROUND_5583 EF4_WORKAROUND_FALCON_A
/* RX events go missing */
#घोषणा EF4_WORKAROUND_5676 EF4_WORKAROUND_FALCON_A
/* RX_RESET on A1 */
#घोषणा EF4_WORKAROUND_6555 EF4_WORKAROUND_FALCON_A
/* Increase filter depth to aव्योम RX_RESET */
#घोषणा EF4_WORKAROUND_7244 EF4_WORKAROUND_FALCON_A
/* Flushes may never complete */
#घोषणा EF4_WORKAROUND_7803 EF4_WORKAROUND_FALCON_AB
/* Leak overlength packets rather than मुक्त */
#घोषणा EF4_WORKAROUND_8071 EF4_WORKAROUND_FALCON_A

#पूर्ण_अगर /* EF4_WORKAROUNDS_H */
