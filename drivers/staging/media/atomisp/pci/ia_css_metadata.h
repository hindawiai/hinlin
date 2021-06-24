<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
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

#अगर_अघोषित __IA_CSS_METADATA_H
#घोषणा __IA_CSS_METADATA_H

/* @file
 * This file contains काष्ठाure क्रम processing sensor metadata.
 */

#समावेश <type_support.h>
#समावेश "ia_css_types.h"
#समावेश "ia_css_stream_format.h"

/* Metadata configuration. This data काष्ठाure contains necessary info
 *  to process sensor metadata.
 */
काष्ठा ia_css_metadata_config अणु
	क्रमागत atomisp_input_क्रमmat data_type; /** Data type of CSI-2 embedded
			data. The शेष value is ATOMISP_INPUT_FORMAT_EMBEDDED. For
			certain sensors, user can choose non-शेष data type क्रम embedded
			data. */
	काष्ठा ia_css_resolution  resolution; /** Resolution */
पूर्ण;

काष्ठा ia_css_metadata_info अणु
	काष्ठा ia_css_resolution resolution; /** Resolution */
	u32                 stride;     /** Stride in bytes */
	u32                 size;       /** Total size in bytes */
पूर्ण;

काष्ठा ia_css_metadata अणु
	काष्ठा ia_css_metadata_info info;    /** Layout info */
	ia_css_ptr		    address; /** CSS भव address */
	u32		    exp_id;
	/** Exposure ID, see ia_css_event_खुला.h क्रम more detail */
पूर्ण;

#घोषणा SIZE_OF_IA_CSS_METADATA_STRUCT माप(काष्ठा ia_css_metadata)

/* @brief Allocate a metadata buffer.
 * @param[in]   metadata_info Metadata info काष्ठा, contains details on metadata buffers.
 * @वापस      Poपूर्णांकer of metadata buffer or शून्य (अगर error)
 *
 * This function allocates a metadata buffer according to the properties
 * specअगरied in the metadata_info काष्ठा.
 */
काष्ठा ia_css_metadata *
ia_css_metadata_allocate(स्थिर काष्ठा ia_css_metadata_info *metadata_info);

/* @brief Free a metadata buffer.
 *
 * @param[in]	metadata	Poपूर्णांकer of metadata buffer.
 * @वापस	None
 *
 * This function मुक्तs a metadata buffer.
 */
व्योम
ia_css_metadata_मुक्त(काष्ठा ia_css_metadata *metadata);

#पूर्ण_अगर /* __IA_CSS_METADATA_H */
