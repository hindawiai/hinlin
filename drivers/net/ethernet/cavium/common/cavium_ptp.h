<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* cavium_ptp.h - PTP 1588 घड़ी on Cavium hardware
 * Copyright (c) 2003-2015, 2017 Cavium, Inc.
 */

#अगर_अघोषित CAVIUM_PTP_H
#घोषणा CAVIUM_PTP_H

#समावेश <linux/ptp_घड़ी_kernel.h>
#समावेश <linux/समयcounter.h>

काष्ठा cavium_ptp अणु
	काष्ठा pci_dev *pdev;

	/* Serialize access to cycle_counter, समय_counter and hw_रेजिस्टरs */
	spinlock_t spin_lock;
	काष्ठा cyclecounter cycle_counter;
	काष्ठा समयcounter समय_counter;
	व्योम __iomem *reg_base;

	u32 घड़ी_rate;

	काष्ठा ptp_घड़ी_info ptp_info;
	काष्ठा ptp_घड़ी *ptp_घड़ी;
पूर्ण;

#अगर IS_REACHABLE(CONFIG_CAVIUM_PTP)

काष्ठा cavium_ptp *cavium_ptp_get(व्योम);
व्योम cavium_ptp_put(काष्ठा cavium_ptp *ptp);

अटल अंतरभूत u64 cavium_ptp_tstamp2समय(काष्ठा cavium_ptp *ptp, u64 tstamp)
अणु
	अचिन्हित दीर्घ flags;
	u64 ret;

	spin_lock_irqsave(&ptp->spin_lock, flags);
	ret = समयcounter_cyc2समय(&ptp->समय_counter, tstamp);
	spin_unlock_irqrestore(&ptp->spin_lock, flags);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक cavium_ptp_घड़ी_index(काष्ठा cavium_ptp *घड़ी)
अणु
	वापस ptp_घड़ी_index(घड़ी->ptp_घड़ी);
पूर्ण

#अन्यथा

अटल अंतरभूत काष्ठा cavium_ptp *cavium_ptp_get(व्योम)
अणु
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल अंतरभूत व्योम cavium_ptp_put(काष्ठा cavium_ptp *ptp) अणुपूर्ण

अटल अंतरभूत u64 cavium_ptp_tstamp2समय(काष्ठा cavium_ptp *ptp, u64 tstamp)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक cavium_ptp_घड़ी_index(काष्ठा cavium_ptp *घड़ी)
अणु
	वापस -1;
पूर्ण

#पूर्ण_अगर

#पूर्ण_अगर
