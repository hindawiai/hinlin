<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * Actions Semi Owl Smart Power System (SPS) shared helpers
 *
 * Copyright 2012 Actions Semi Inc.
 * Author: Actions Semi, Inc.
 *
 * Copyright (c) 2017 Andreas Fथअrber
 */

#समावेश <linux/delay.h>
#समावेश <linux/पन.स>
#समावेश <linux/soc/actions/owl-sps.h>

#घोषणा OWL_SPS_PG_CTL	0x0

पूर्णांक owl_sps_set_pg(व्योम __iomem *base, u32 pwr_mask, u32 ack_mask, bool enable)
अणु
	u32 val;
	bool ack;
	पूर्णांक समयout;

	val = पढ़ोl(base + OWL_SPS_PG_CTL);
	ack = val & ack_mask;
	अगर (ack == enable)
		वापस 0;

	अगर (enable)
		val |= pwr_mask;
	अन्यथा
		val &= ~pwr_mask;

	ग_लिखोl(val, base + OWL_SPS_PG_CTL);

	क्रम (समयout = 5000; समयout > 0; समयout -= 50) अणु
		val = पढ़ोl(base + OWL_SPS_PG_CTL);
		अगर ((val & ack_mask) == (enable ? ack_mask : 0))
			अवरोध;
		udelay(50);
	पूर्ण
	अगर (समयout <= 0)
		वापस -ETIMEDOUT;

	udelay(10);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(owl_sps_set_pg);
