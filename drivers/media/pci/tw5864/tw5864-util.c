<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश "tw5864.h"

व्योम tw5864_indir_ग_लिखोb(काष्ठा tw5864_dev *dev, u16 addr, u8 data)
अणु
	पूर्णांक retries = 30000;

	जबतक (tw_पढ़ोl(TW5864_IND_CTL) & BIT(31) && --retries)
		;
	अगर (!retries)
		dev_err(&dev->pci->dev,
			"tw_indir_writel() retries exhausted before writing\n");

	tw_ग_लिखोl(TW5864_IND_DATA, data);
	tw_ग_लिखोl(TW5864_IND_CTL, addr << 2 | TW5864_RW | TW5864_ENABLE);
पूर्ण

u8 tw5864_indir_पढ़ोb(काष्ठा tw5864_dev *dev, u16 addr)
अणु
	पूर्णांक retries = 30000;

	जबतक (tw_पढ़ोl(TW5864_IND_CTL) & BIT(31) && --retries)
		;
	अगर (!retries)
		dev_err(&dev->pci->dev,
			"tw_indir_readl() retries exhausted before reading\n");

	tw_ग_लिखोl(TW5864_IND_CTL, addr << 2 | TW5864_ENABLE);

	retries = 30000;
	जबतक (tw_पढ़ोl(TW5864_IND_CTL) & BIT(31) && --retries)
		;
	अगर (!retries)
		dev_err(&dev->pci->dev,
			"tw_indir_readl() retries exhausted at reading\n");

	वापस tw_पढ़ोl(TW5864_IND_DATA);
पूर्ण
