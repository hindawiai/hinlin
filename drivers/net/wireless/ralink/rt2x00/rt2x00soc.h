<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
	Copyright (C) 2004 - 2009 Ivo van Doorn <IvDoorn@gmail.com>
	<http://rt2x00.serialmonkey.com>

 */

/*
	Module: rt2x00soc
	Abstract: Data काष्ठाures क्रम the rt2x00soc module.
 */

#अगर_अघोषित RT2X00SOC_H
#घोषणा RT2X00SOC_H

/*
 * SoC driver handlers.
 */
पूर्णांक rt2x00soc_probe(काष्ठा platक्रमm_device *pdev, स्थिर काष्ठा rt2x00_ops *ops);
पूर्णांक rt2x00soc_हटाओ(काष्ठा platक्रमm_device *pdev);
#अगर_घोषित CONFIG_PM
पूर्णांक rt2x00soc_suspend(काष्ठा platक्रमm_device *pdev, pm_message_t state);
पूर्णांक rt2x00soc_resume(काष्ठा platक्रमm_device *pdev);
#अन्यथा
#घोषणा rt2x00soc_suspend	शून्य
#घोषणा rt2x00soc_resume	शून्य
#पूर्ण_अगर /* CONFIG_PM */

#पूर्ण_अगर /* RT2X00SOC_H */
