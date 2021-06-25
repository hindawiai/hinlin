<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Freescale MPL115A pressure/temperature sensor
 *
 * Copyright (c) 2014 Peter Meerwald <pmeerw@pmeerw.net>
 * Copyright (c) 2016 Akinobu Mita <akinobu.mita@gmail.com>
 */

#अगर_अघोषित _MPL115_H_
#घोषणा _MPL115_H_

काष्ठा mpl115_ops अणु
	पूर्णांक (*init)(काष्ठा device *);
	पूर्णांक (*पढ़ो)(काष्ठा device *, u8);
	पूर्णांक (*ग_लिखो)(काष्ठा device *, u8, u8);
पूर्ण;

पूर्णांक mpl115_probe(काष्ठा device *dev, स्थिर अक्षर *name,
			स्थिर काष्ठा mpl115_ops *ops);

#पूर्ण_अगर
