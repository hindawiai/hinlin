<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * This header provides स्थिरants क्रम binding nvidia,tegra186-hsp.
 */

#अगर_अघोषित _DT_BINDINGS_MAILBOX_TEGRA186_HSP_H
#घोषणा _DT_BINDINGS_MAILBOX_TEGRA186_HSP_H

/*
 * These define the type of mailbox that is to be used (करोorbell, shared
 * mailbox, shared semaphore or arbitrated semaphore).
 */
#घोषणा TEGRA_HSP_MBOX_TYPE_DB 0x0
#घोषणा TEGRA_HSP_MBOX_TYPE_SM 0x1
#घोषणा TEGRA_HSP_MBOX_TYPE_SS 0x2
#घोषणा TEGRA_HSP_MBOX_TYPE_AS 0x3

/*
 * These defines represent the bit associated with the given master ID in the
 * करोorbell रेजिस्टरs.
 */
#घोषणा TEGRA_HSP_DB_MASTER_CCPLEX 17
#घोषणा TEGRA_HSP_DB_MASTER_BPMP 19

/*
 * Shared mailboxes are unidirectional, so the direction needs to be specअगरied
 * in the device tree.
 */
#घोषणा TEGRA_HSP_SM_MASK 0x00ffffff
#घोषणा TEGRA_HSP_SM_FLAG_RX (0 << 31)
#घोषणा TEGRA_HSP_SM_FLAG_TX (1 << 31)

#घोषणा TEGRA_HSP_SM_RX(x) (TEGRA_HSP_SM_FLAG_RX | ((x) & TEGRA_HSP_SM_MASK))
#घोषणा TEGRA_HSP_SM_TX(x) (TEGRA_HSP_SM_FLAG_TX | ((x) & TEGRA_HSP_SM_MASK))

#पूर्ण_अगर
