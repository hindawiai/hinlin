<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2013 Intel Corporation. All Rights Reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version
 * 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License क्रम more details.
 *
 *
 */
#अगर_अघोषित __LIBMSRLISTHELPER_H__
#घोषणा __LIBMSRLISTHELPER_H__

काष्ठा i2c_client;
काष्ठा firmware;

पूर्णांक load_msr_list(काष्ठा i2c_client *client, अक्षर *path,
		  स्थिर काष्ठा firmware **fw);
पूर्णांक apply_msr_data(काष्ठा i2c_client *client, स्थिर काष्ठा firmware *fw);
व्योम release_msr_list(काष्ठा i2c_client *client,
		      स्थिर काष्ठा firmware *fw);

#पूर्ण_अगर /* अगरndef __LIBMSRLISTHELPER_H__ */
