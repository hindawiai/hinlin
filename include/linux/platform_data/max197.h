<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * Maxim MAX197 A/D Converter Driver
 *
 * Copyright (c) 2012 Savoir-faire Linux Inc.
 *          Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 *
 * For further inक्रमmation, see the Documentation/hwmon/max197.rst file.
 */

#अगर_अघोषित _PDATA_MAX197_H
#घोषणा _PDATA_MAX197_H

/**
 * काष्ठा max197_platक्रमm_data - MAX197 connectivity info
 * @convert:	Function used to start a conversion with control byte ctrl.
 *		It must वापस the raw data, or a negative error code.
 */
काष्ठा max197_platक्रमm_data अणु
	पूर्णांक (*convert)(u8 ctrl);
पूर्ण;

#पूर्ण_अगर /* _PDATA_MAX197_H */
