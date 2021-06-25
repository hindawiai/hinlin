<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Greybus SPI library header
 *
 * copyright 2016 google inc.
 * copyright 2016 linaro ltd.
 *
 * released under the gplv2 only.
 */

#अगर_अघोषित __SPILIB_H
#घोषणा __SPILIB_H

काष्ठा device;
काष्ठा gb_connection;

काष्ठा spilib_ops अणु
	पूर्णांक (*prepare_transfer_hardware)(काष्ठा device *dev);
	व्योम (*unprepare_transfer_hardware)(काष्ठा device *dev);
पूर्ण;

पूर्णांक gb_spilib_master_init(काष्ठा gb_connection *connection,
			  काष्ठा device *dev, काष्ठा spilib_ops *ops);
व्योम gb_spilib_master_निकास(काष्ठा gb_connection *connection);

#पूर्ण_अगर /* __SPILIB_H */
