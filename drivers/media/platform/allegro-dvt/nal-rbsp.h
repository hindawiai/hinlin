<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (C) 2019-2020 Pengutronix, Michael Tretter <kernel@pengutronix.de>
 */

#अगर_अघोषित __NAL_RBSP_H__
#घोषणा __NAL_RBSP_H__

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>

काष्ठा rbsp;

काष्ठा nal_rbsp_ops अणु
	पूर्णांक (*rbsp_bit)(काष्ठा rbsp *rbsp, पूर्णांक *val);
	पूर्णांक (*rbsp_bits)(काष्ठा rbsp *rbsp, पूर्णांक n, अचिन्हित पूर्णांक *val);
	पूर्णांक (*rbsp_uev)(काष्ठा rbsp *rbsp, अचिन्हित पूर्णांक *val);
	पूर्णांक (*rbsp_sev)(काष्ठा rbsp *rbsp, पूर्णांक *val);
पूर्ण;

/**
 * काष्ठा rbsp - State object क्रम handling a raw byte sequence payload
 * @data: poपूर्णांकer to the data of the rbsp
 * @size: maximum size of the data of the rbsp
 * @pos: current bit position inside the rbsp
 * @num_consecutive_zeros: number of zeros beक्रमe @pos
 * @ops: per datatype functions क्रम पूर्णांकeracting with the rbsp
 * @error: an error occurred जबतक handling the rbsp
 *
 * This काष्ठा is passed around the various parsing functions and tracks the
 * current position within the raw byte sequence payload.
 *
 * The @ops field allows to separate the operation, i.e., पढ़ोing/writing a
 * value from/to that rbsp, from the काष्ठाure of the NAL unit. This allows to
 * have a single function क्रम iterating the NAL unit, जबतक @ops has function
 * poपूर्णांकers क्रम handling each type in the rbsp.
 */
काष्ठा rbsp अणु
	u8 *data;
	माप_प्रकार size;
	अचिन्हित पूर्णांक pos;
	अचिन्हित पूर्णांक num_consecutive_zeros;
	काष्ठा nal_rbsp_ops *ops;
	पूर्णांक error;
पूर्ण;

बाह्य काष्ठा nal_rbsp_ops ग_लिखो;
बाह्य काष्ठा nal_rbsp_ops पढ़ो;

व्योम rbsp_init(काष्ठा rbsp *rbsp, व्योम *addr, माप_प्रकार size,
	       काष्ठा nal_rbsp_ops *ops);
व्योम rbsp_unsupported(काष्ठा rbsp *rbsp);

व्योम rbsp_bit(काष्ठा rbsp *rbsp, पूर्णांक *value);
व्योम rbsp_bits(काष्ठा rbsp *rbsp, पूर्णांक n, पूर्णांक *value);
व्योम rbsp_uev(काष्ठा rbsp *rbsp, अचिन्हित पूर्णांक *value);
व्योम rbsp_sev(काष्ठा rbsp *rbsp, पूर्णांक *value);

व्योम rbsp_trailing_bits(काष्ठा rbsp *rbsp);

#पूर्ण_अगर /* __NAL_RBSP_H__ */
