<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Release Version: irci_stable_candrpv_0415_20150521_0458 */
/*
 * Support क्रम Intel Camera Imaging ISP subप्रणाली.
 * Copyright (c) 2015, Intel Corporation.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms and conditions of the GNU General Public License,
 * version 2, as published by the Free Software Foundation.
 *
 * This program is distributed in the hope it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
 * more details.
 */

#अगर_अघोषित __SH_CSS_HOST_DATA_H
#घोषणा __SH_CSS_HOST_DATA_H

#समावेश <ia_css_types.h>	/* ia_css_pipe */

/**
 * @brief Allocate काष्ठाure ia_css_host_data.
 *
 * @param[in]	size		Size of the requested host data
 *
 * @वापस
 *	- शून्य, can't allocate requested size
 *	- poपूर्णांकer to काष्ठाure, field address poपूर्णांकs to host data with size bytes
 */
काष्ठा ia_css_host_data *
ia_css_host_data_allocate(माप_प्रकार size);

/**
 * @brief Free काष्ठाure ia_css_host_data.
 *
 * @param[in]	me	Poपूर्णांकer to काष्ठाure, अगर a शून्य is passed functions
 *			वापसs without error. Otherwise a valid poपूर्णांकer to
 *			काष्ठाure must be passed and a related memory
 *			is मुक्तd.
 *
 * @वापस
 */
व्योम ia_css_host_data_मुक्त(काष्ठा ia_css_host_data *me);

#पूर्ण_अगर /* __SH_CSS_HOST_DATA_H */
