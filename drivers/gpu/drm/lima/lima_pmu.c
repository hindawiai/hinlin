<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR MIT
/* Copyright 2017-2019 Qiang Yu <yuq825@gmail.com> */

#समावेश <linux/iopoll.h>
#समावेश <linux/device.h>

#समावेश "lima_device.h"
#समावेश "lima_pmu.h"
#समावेश "lima_regs.h"

#घोषणा pmu_ग_लिखो(reg, data) ग_लिखोl(data, ip->iomem + reg)
#घोषणा pmu_पढ़ो(reg) पढ़ोl(ip->iomem + reg)

अटल पूर्णांक lima_pmu_रुको_cmd(काष्ठा lima_ip *ip)
अणु
	काष्ठा lima_device *dev = ip->dev;
	पूर्णांक err;
	u32 v;

	err = पढ़ोl_poll_समयout(ip->iomem + LIMA_PMU_INT_RAWSTAT,
				 v, v & LIMA_PMU_INT_CMD_MASK,
				 100, 100000);
	अगर (err) अणु
		dev_err(dev->dev, "timeout wait pmu cmd\n");
		वापस err;
	पूर्ण

	pmu_ग_लिखो(LIMA_PMU_INT_CLEAR, LIMA_PMU_INT_CMD_MASK);
	वापस 0;
पूर्ण

अटल u32 lima_pmu_get_ip_mask(काष्ठा lima_ip *ip)
अणु
	काष्ठा lima_device *dev = ip->dev;
	u32 ret = 0;
	पूर्णांक i;

	ret |= LIMA_PMU_POWER_GP0_MASK;

	अगर (dev->id == lima_gpu_mali400) अणु
		ret |= LIMA_PMU_POWER_L2_MASK;
		क्रम (i = 0; i < 4; i++) अणु
			अगर (dev->ip[lima_ip_pp0 + i].present)
				ret |= LIMA_PMU_POWER_PP_MASK(i);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (dev->ip[lima_ip_pp0].present)
			ret |= LIMA450_PMU_POWER_PP0_MASK;
		क्रम (i = lima_ip_pp1; i <= lima_ip_pp3; i++) अणु
			अगर (dev->ip[i].present) अणु
				ret |= LIMA450_PMU_POWER_PP13_MASK;
				अवरोध;
			पूर्ण
		पूर्ण
		क्रम (i = lima_ip_pp4; i <= lima_ip_pp7; i++) अणु
			अगर (dev->ip[i].present) अणु
				ret |= LIMA450_PMU_POWER_PP47_MASK;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक lima_pmu_hw_init(काष्ठा lima_ip *ip)
अणु
	पूर्णांक err;
	u32 stat;

	pmu_ग_लिखो(LIMA_PMU_INT_MASK, 0);

	/* If this value is too low, when in high GPU clk freq,
	 * GPU will be in unstable state.
	 */
	pmu_ग_लिखो(LIMA_PMU_SW_DELAY, 0xffff);

	/* status reg 1=off 0=on */
	stat = pmu_पढ़ो(LIMA_PMU_STATUS);

	/* घातer up all ip */
	अगर (stat) अणु
		pmu_ग_लिखो(LIMA_PMU_POWER_UP, stat);
		err = lima_pmu_रुको_cmd(ip);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम lima_pmu_hw_fini(काष्ठा lima_ip *ip)
अणु
	u32 stat;

	अगर (!ip->data.mask)
		ip->data.mask = lima_pmu_get_ip_mask(ip);

	stat = ~pmu_पढ़ो(LIMA_PMU_STATUS) & ip->data.mask;
	अगर (stat) अणु
		pmu_ग_लिखो(LIMA_PMU_POWER_DOWN, stat);

		/* Don't रुको क्रम पूर्णांकerrupt on Mali400 अगर all करोमुख्यs are
		 * घातered off because the HW won't generate an पूर्णांकerrupt
		 * in this हाल.
		 */
		अगर (ip->dev->id == lima_gpu_mali400)
			pmu_ग_लिखो(LIMA_PMU_INT_CLEAR, LIMA_PMU_INT_CMD_MASK);
		अन्यथा
			lima_pmu_रुको_cmd(ip);
	पूर्ण
पूर्ण

पूर्णांक lima_pmu_resume(काष्ठा lima_ip *ip)
अणु
	वापस lima_pmu_hw_init(ip);
पूर्ण

व्योम lima_pmu_suspend(काष्ठा lima_ip *ip)
अणु
	lima_pmu_hw_fini(ip);
पूर्ण

पूर्णांक lima_pmu_init(काष्ठा lima_ip *ip)
अणु
	वापस lima_pmu_hw_init(ip);
पूर्ण

व्योम lima_pmu_fini(काष्ठा lima_ip *ip)
अणु
	lima_pmu_hw_fini(ip);
पूर्ण
