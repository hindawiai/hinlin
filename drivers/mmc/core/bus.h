<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  linux/drivers/mmc/core/bus.h
 *
 *  Copyright (C) 2003 Russell King, All Rights Reserved.
 *  Copyright 2007 Pierre Ossman
 */
#अगर_अघोषित _MMC_CORE_BUS_H
#घोषणा _MMC_CORE_BUS_H

#समावेश <linux/device.h>

काष्ठा mmc_host;
काष्ठा mmc_card;

#घोषणा MMC_DEV_ATTR(name, fmt, args...)					\
अटल sमाप_प्रकार mmc_##name##_show (काष्ठा device *dev, काष्ठा device_attribute *attr, अक्षर *buf)	\
अणु										\
	काष्ठा mmc_card *card = mmc_dev_to_card(dev);				\
	वापस प्र_लिखो(buf, fmt, args);						\
पूर्ण										\
अटल DEVICE_ATTR(name, S_IRUGO, mmc_##name##_show, शून्य)

काष्ठा mmc_card *mmc_alloc_card(काष्ठा mmc_host *host,
	काष्ठा device_type *type);
पूर्णांक mmc_add_card(काष्ठा mmc_card *card);
व्योम mmc_हटाओ_card(काष्ठा mmc_card *card);

पूर्णांक mmc_रेजिस्टर_bus(व्योम);
व्योम mmc_unरेजिस्टर_bus(व्योम);

काष्ठा mmc_driver अणु
	काष्ठा device_driver drv;
	पूर्णांक (*probe)(काष्ठा mmc_card *card);
	व्योम (*हटाओ)(काष्ठा mmc_card *card);
	व्योम (*shutकरोwn)(काष्ठा mmc_card *card);
पूर्ण;

पूर्णांक mmc_रेजिस्टर_driver(काष्ठा mmc_driver *drv);
व्योम mmc_unरेजिस्टर_driver(काष्ठा mmc_driver *drv);

#पूर्ण_अगर
