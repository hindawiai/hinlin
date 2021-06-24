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

#अगर_अघोषित __IA_CSS_ENV_H
#घोषणा __IA_CSS_ENV_H

#समावेश <type_support.h>
#समावेश <मानकतर्क.स> /* बहु_सूची */
#समावेश "ia_css_types.h"
#समावेश "ia_css_acc_types.h"

/* @file
 * This file contains prototypes क्रम functions that need to be provided to the
 * CSS-API host-code by the environment in which the CSS-API code runs.
 */

/* Memory allocation attributes, क्रम use in ia_css_css_mem_env. */
क्रमागत ia_css_mem_attr अणु
	IA_CSS_MEM_ATTR_CACHED = 1 << 0,
	IA_CSS_MEM_ATTR_ZEROED = 1 << 1,
	IA_CSS_MEM_ATTR_PAGEALIGN = 1 << 2,
	IA_CSS_MEM_ATTR_CONTIGUOUS = 1 << 3,
पूर्ण;

/* Environment with function poपूर्णांकers क्रम local IA memory allocation.
 *  This provides the CSS code with environment specअगरic functionality
 *  क्रम memory allocation of small local buffers such as local data काष्ठाures.
 *  This is never expected to allocate more than one page of memory (4K bytes).
 */
काष्ठा ia_css_cpu_mem_env अणु
	व्योम (*flush)(काष्ठा ia_css_acc_fw *fw);
	/** Flush function to flush the cache क्रम given accelerator. */
पूर्ण;

/* Environment with function poपूर्णांकers to access the CSS hardware. This includes
 *  रेजिस्टरs and local memories.
 */
काष्ठा ia_css_hw_access_env अणु
	व्योम (*store_8)(hrt_address addr, uपूर्णांक8_t data);
	/** Store an 8 bit value पूर्णांकo an address in the CSS HW address space.
	     The address must be an 8 bit aligned address. */
	व्योम (*store_16)(hrt_address addr, uपूर्णांक16_t data);
	/** Store a 16 bit value पूर्णांकo an address in the CSS HW address space.
	     The address must be a 16 bit aligned address. */
	व्योम (*store_32)(hrt_address addr, uपूर्णांक32_t data);
	/** Store a 32 bit value पूर्णांकo an address in the CSS HW address space.
	     The address must be a 32 bit aligned address. */
	uपूर्णांक8_t (*load_8)(hrt_address addr);
	/** Load an 8 bit value from an address in the CSS HW address
	     space. The address must be an 8 bit aligned address. */
	uपूर्णांक16_t (*load_16)(hrt_address addr);
	/** Load a 16 bit value from an address in the CSS HW address
	     space. The address must be a 16 bit aligned address. */
	uपूर्णांक32_t (*load_32)(hrt_address addr);
	/** Load a 32 bit value from an address in the CSS HW address
	     space. The address must be a 32 bit aligned address. */
	व्योम (*store)(hrt_address addr, स्थिर व्योम *data, uपूर्णांक32_t bytes);
	/** Store a number of bytes पूर्णांकo a byte-aligned address in the CSS HW address space. */
	व्योम (*load)(hrt_address addr, व्योम *data, uपूर्णांक32_t bytes);
	/** Load a number of bytes from a byte-aligned address in the CSS HW address space. */
पूर्ण;

/* Environment with function poपूर्णांकers to prपूर्णांक error and debug messages.
 */
काष्ठा ia_css_prपूर्णांक_env अणु
	पूर्णांक  __म_लिखो(1, 0) (*debug_prपूर्णांक)(स्थिर अक्षर *fmt, बहु_सूची args);
	/** Prपूर्णांक a debug message. */
	पूर्णांक  __म_लिखो(1, 0) (*error_prपूर्णांक)(स्थिर अक्षर *fmt, बहु_सूची args);
	/** Prपूर्णांक an error message.*/
पूर्ण;

/* Environment काष्ठाure. This includes function poपूर्णांकers to access several
 *  features provided by the environment in which the CSS API is used.
 *  This is used to run the camera IP in multiple platक्रमms such as Linux,
 *  Winकरोws and several simulation environments.
 */
काष्ठा ia_css_env अणु
	काष्ठा ia_css_cpu_mem_env   cpu_mem_env;   /** local flush. */
	काष्ठा ia_css_hw_access_env hw_access_env; /** CSS HW access functions */
	काष्ठा ia_css_prपूर्णांक_env     prपूर्णांक_env;     /** Message prपूर्णांकing env. */
पूर्ण;

#पूर्ण_अगर /* __IA_CSS_ENV_H */
