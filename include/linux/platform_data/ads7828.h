<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * TI ADS7828 A/D Converter platक्रमm data definition
 *
 * Copyright (c) 2012 Savoir-faire Linux Inc.
 *          Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 *
 * For further inक्रमmation, see the Documentation/hwmon/ads7828.rst file.
 */

#अगर_अघोषित _PDATA_ADS7828_H
#घोषणा _PDATA_ADS7828_H

/**
 * काष्ठा ads7828_platक्रमm_data - optional ADS7828 connectivity info
 * @dअगरf_input:		Dअगरferential input mode.
 * @ext_vref:		Use an बाह्यal voltage reference.
 * @vref_mv:		Voltage reference value, अगर बाह्यal.
 */
काष्ठा ads7828_platक्रमm_data अणु
	bool dअगरf_input;
	bool ext_vref;
	अचिन्हित पूर्णांक vref_mv;
पूर्ण;

#पूर्ण_अगर /* _PDATA_ADS7828_H */
