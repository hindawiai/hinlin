<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Anybus-S controller definitions
 *
 * Copyright 2018 Arcx Inc
 */

#अगर_अघोषित __LINUX_ANYBUSS_CONTROLLER_H__
#घोषणा __LINUX_ANYBUSS_CONTROLLER_H__

#समावेश <linux/device.h>
#समावेश <linux/regmap.h>

/*
 * To instantiate an Anybus-S host, a controller should provide the following:
 * - a reset function which resets the attached card;
 * - a regmap which provides access to the attached card's dpram;
 * - the irq of the attached card
 */
/**
 * काष्ठा anybuss_ops - Controller resources to instantiate an Anybus-S host
 *
 * @reset:	निश्चितs/deनिश्चितs the anybus card's reset line.
 * @regmap:	provides access to the card's dual-port RAM area.
 * @irq:	number of the पूर्णांकerrupt connected to the card's पूर्णांकerrupt line.
 * @host_idx:	क्रम multi-host controllers, the host index:
 *		0 क्रम the first host on the controller, 1 क्रम the second, etc.
 */
काष्ठा anybuss_ops अणु
	व्योम (*reset)(काष्ठा device *dev, bool निश्चित);
	काष्ठा regmap *regmap;
	पूर्णांक irq;
	पूर्णांक host_idx;
पूर्ण;

काष्ठा anybuss_host;

काष्ठा anybuss_host * __must_check
anybuss_host_common_probe(काष्ठा device *dev,
			  स्थिर काष्ठा anybuss_ops *ops);
व्योम anybuss_host_common_हटाओ(काष्ठा anybuss_host *host);

काष्ठा anybuss_host * __must_check
devm_anybuss_host_common_probe(काष्ठा device *dev,
			       स्थिर काष्ठा anybuss_ops *ops);

#पूर्ण_अगर /* __LINUX_ANYBUSS_CONTROLLER_H__ */
