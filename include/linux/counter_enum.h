<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Counter पूर्णांकerface क्रमागत functions
 * Copyright (C) 2018 William Breathitt Gray
 */
#अगर_अघोषित _COUNTER_ENUM_H_
#घोषणा _COUNTER_ENUM_H_

#समावेश <linux/types.h>

काष्ठा counter_device;
काष्ठा counter_संकेत;
काष्ठा counter_count;

sमाप_प्रकार counter_संकेत_क्रमागत_पढ़ो(काष्ठा counter_device *counter,
				 काष्ठा counter_संकेत *संकेत, व्योम *priv,
				 अक्षर *buf);
sमाप_प्रकार counter_संकेत_क्रमागत_ग_लिखो(काष्ठा counter_device *counter,
				  काष्ठा counter_संकेत *संकेत, व्योम *priv,
				  स्थिर अक्षर *buf, माप_प्रकार len);

sमाप_प्रकार counter_संकेत_क्रमागत_available_पढ़ो(काष्ठा counter_device *counter,
					   काष्ठा counter_संकेत *संकेत,
					   व्योम *priv, अक्षर *buf);

sमाप_प्रकार counter_count_क्रमागत_पढ़ो(काष्ठा counter_device *counter,
				काष्ठा counter_count *count, व्योम *priv,
				अक्षर *buf);
sमाप_प्रकार counter_count_क्रमागत_ग_लिखो(काष्ठा counter_device *counter,
				 काष्ठा counter_count *count, व्योम *priv,
				 स्थिर अक्षर *buf, माप_प्रकार len);

sमाप_प्रकार counter_count_क्रमागत_available_पढ़ो(काष्ठा counter_device *counter,
					  काष्ठा counter_count *count,
					  व्योम *priv, अक्षर *buf);

sमाप_प्रकार counter_device_क्रमागत_पढ़ो(काष्ठा counter_device *counter, व्योम *priv,
				 अक्षर *buf);
sमाप_प्रकार counter_device_क्रमागत_ग_लिखो(काष्ठा counter_device *counter, व्योम *priv,
				  स्थिर अक्षर *buf, माप_प्रकार len);

sमाप_प्रकार counter_device_क्रमागत_available_पढ़ो(काष्ठा counter_device *counter,
					   व्योम *priv, अक्षर *buf);

#पूर्ण_अगर /* _COUNTER_ENUM_H_ */
