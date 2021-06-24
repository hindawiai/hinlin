<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * pm_घड़ी.h - Definitions and headers related to device घड़ीs.
 *
 * Copyright (C) 2011 Rafael J. Wysocki <rjw@sisk.pl>, Renesas Electronics Corp.
 */

#अगर_अघोषित _LINUX_PM_CLOCK_H
#घोषणा _LINUX_PM_CLOCK_H

#समावेश <linux/device.h>
#समावेश <linux/notअगरier.h>

काष्ठा pm_clk_notअगरier_block अणु
	काष्ठा notअगरier_block nb;
	काष्ठा dev_pm_करोमुख्य *pm_करोमुख्य;
	अक्षर *con_ids[];
पूर्ण;

काष्ठा clk;

#अगर_घोषित CONFIG_PM
बाह्य पूर्णांक pm_clk_runसमय_suspend(काष्ठा device *dev);
बाह्य पूर्णांक pm_clk_runसमय_resume(काष्ठा device *dev);
#घोषणा USE_PM_CLK_RUNTIME_OPS \
	.runसमय_suspend = pm_clk_runसमय_suspend, \
	.runसमय_resume = pm_clk_runसमय_resume,
#अन्यथा
#घोषणा USE_PM_CLK_RUNTIME_OPS
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM_CLK
अटल अंतरभूत bool pm_clk_no_घड़ीs(काष्ठा device *dev)
अणु
	वापस dev && dev->घातer.subsys_data
		&& list_empty(&dev->घातer.subsys_data->घड़ी_list);
पूर्ण

बाह्य व्योम pm_clk_init(काष्ठा device *dev);
बाह्य पूर्णांक pm_clk_create(काष्ठा device *dev);
बाह्य व्योम pm_clk_destroy(काष्ठा device *dev);
बाह्य पूर्णांक pm_clk_add(काष्ठा device *dev, स्थिर अक्षर *con_id);
बाह्य पूर्णांक pm_clk_add_clk(काष्ठा device *dev, काष्ठा clk *clk);
बाह्य पूर्णांक of_pm_clk_add_clk(काष्ठा device *dev, स्थिर अक्षर *name);
बाह्य पूर्णांक of_pm_clk_add_clks(काष्ठा device *dev);
बाह्य व्योम pm_clk_हटाओ(काष्ठा device *dev, स्थिर अक्षर *con_id);
बाह्य व्योम pm_clk_हटाओ_clk(काष्ठा device *dev, काष्ठा clk *clk);
बाह्य पूर्णांक pm_clk_suspend(काष्ठा device *dev);
बाह्य पूर्णांक pm_clk_resume(काष्ठा device *dev);
#अन्यथा
अटल अंतरभूत bool pm_clk_no_घड़ीs(काष्ठा device *dev)
अणु
	वापस true;
पूर्ण
अटल अंतरभूत व्योम pm_clk_init(काष्ठा device *dev)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक pm_clk_create(काष्ठा device *dev)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत व्योम pm_clk_destroy(काष्ठा device *dev)
अणु
पूर्ण
अटल अंतरभूत पूर्णांक pm_clk_add(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
	वापस -EINVAL;
पूर्ण

अटल अंतरभूत पूर्णांक pm_clk_add_clk(काष्ठा device *dev, काष्ठा clk *clk)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत पूर्णांक of_pm_clk_add_clks(काष्ठा device *dev)
अणु
	वापस -EINVAL;
पूर्ण
अटल अंतरभूत व्योम pm_clk_हटाओ(काष्ठा device *dev, स्थिर अक्षर *con_id)
अणु
पूर्ण
#घोषणा pm_clk_suspend	शून्य
#घोषणा pm_clk_resume	शून्य
अटल अंतरभूत व्योम pm_clk_हटाओ_clk(काष्ठा device *dev, काष्ठा clk *clk)
अणु
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_HAVE_CLK
बाह्य व्योम pm_clk_add_notअगरier(काष्ठा bus_type *bus,
					काष्ठा pm_clk_notअगरier_block *clknb);
#अन्यथा
अटल अंतरभूत व्योम pm_clk_add_notअगरier(काष्ठा bus_type *bus,
					काष्ठा pm_clk_notअगरier_block *clknb)
अणु
पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर
