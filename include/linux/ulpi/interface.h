<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __LINUX_ULPI_INTERFACE_H
#घोषणा __LINUX_ULPI_INTERFACE_H

#समावेश <linux/types.h>

काष्ठा ulpi;
काष्ठा device;

/**
 * काष्ठा ulpi_ops - ULPI रेजिस्टर access
 * @पढ़ो: पढ़ो operation क्रम ULPI रेजिस्टर access
 * @ग_लिखो: ग_लिखो operation क्रम ULPI रेजिस्टर access
 */
काष्ठा ulpi_ops अणु
	पूर्णांक (*पढ़ो)(काष्ठा device *dev, u8 addr);
	पूर्णांक (*ग_लिखो)(काष्ठा device *dev, u8 addr, u8 val);
पूर्ण;

काष्ठा ulpi *ulpi_रेजिस्टर_पूर्णांकerface(काष्ठा device *, स्थिर काष्ठा ulpi_ops *);
व्योम ulpi_unरेजिस्टर_पूर्णांकerface(काष्ठा ulpi *);

#पूर्ण_अगर /* __LINUX_ULPI_INTERFACE_H */
