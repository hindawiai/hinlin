<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/**
Support क्रम Intel Camera Imaging ISP subप्रणाली.
Copyright (c) 2010 - 2015, Intel Corporation.

This program is मुक्त software; you can redistribute it and/or modअगरy it
under the terms and conditions of the GNU General Public License,
version 2, as published by the Free Software Foundation.

This program is distributed in the hope it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License क्रम
more details.
*/

#अगर_अघोषित __DEVICE_ACCESS_H_INCLUDED__
#घोषणा __DEVICE_ACCESS_H_INCLUDED__

/*!
 * \मrief
 * Define the खुला पूर्णांकerface क्रम physical प्रणाली
 * access functions to SRAM and रेजिस्टरs. Access
 * types are limited to those defined in <मानक_निवेशt.h>
 * All accesses are aligned
 *
 * The address representation is निजी to the प्रणाली
 * and represented as/stored in "hrt_address".
 *
 * The प्रणाली global address can dअगरfer by an offset;
 * The device base address. This offset must be added
 * by the implementation of the access function
 *
 * "store" is a transfer to the device
 * "load" is a transfer from the device
 */

#समावेश <type_support.h>

/*
 * User provided file that defines the प्रणाली address types:
 *	- hrt_address	a type that can hold the (sub)प्रणाली address range
 */
#समावेश "system_local.h"
/*
 * We cannot assume that the global प्रणाली address size is the size of
 * a poपूर्णांकer because a (say) 64-bit host can be simulated in a 32-bit
 * environment. Only अगर the host environment is modelled as on the target
 * we could use a poपूर्णांकer. Even then, prototyping may need to be करोne
 * beक्रमe the target environment is available. AS we cannot रुको क्रम that
 * we are stuck with पूर्णांकeger addresses
 */

/*प्रकार	अक्षर *sys_address;*/
प्रकार	hrt_address		sys_address;

/*! Set the (sub)प्रणाली base address

 \param	base_addr[in]		The offset on which the (sub)प्रणाली is located
							in the global address map

 \लeturn none,
 */
व्योम device_set_base_address(
    स्थिर sys_address		base_addr);

/*! Get the (sub)प्रणाली base address

 \लeturn base_address,
 */
sys_address device_get_base_address(व्योम);

/*! Read an 8-bit value from a device रेजिस्टर or memory in the device

 \param	addr[in]			Local address

 \लeturn device[addr]
 */
uपूर्णांक8_t ia_css_device_load_uपूर्णांक8(
    स्थिर hrt_address		addr);

/*! Read a 16-bit value from a device रेजिस्टर or memory in the device

 \param	addr[in]			Local address

 \लeturn device[addr]
 */
uपूर्णांक16_t ia_css_device_load_uपूर्णांक16(
    स्थिर hrt_address		addr);

/*! Read a 32-bit value from a device रेजिस्टर or memory in the device

 \param	addr[in]			Local address

 \लeturn device[addr]
 */
uपूर्णांक32_t ia_css_device_load_uपूर्णांक32(
    स्थिर hrt_address		addr);

/*! Read a 64-bit value from a device रेजिस्टर or memory in the device

 \param	addr[in]			Local address

 \लeturn device[addr]
 */
uपूर्णांक64_t ia_css_device_load_uपूर्णांक64(
    स्थिर hrt_address		addr);

/*! Write an 8-bit value to a device रेजिस्टर or memory in the device

 \param	addr[in]			Local address
 \param	data[in]			value

 \लeturn none, device[addr] = value
 */
व्योम ia_css_device_store_uपूर्णांक8(
    स्थिर hrt_address		addr,
    स्थिर uपूर्णांक8_t			data);

/*! Write a 16-bit value to a device रेजिस्टर or memory in the device

 \param	addr[in]			Local address
 \param	data[in]			value

 \लeturn none, device[addr] = value
 */
व्योम ia_css_device_store_uपूर्णांक16(
    स्थिर hrt_address		addr,
    स्थिर uपूर्णांक16_t			data);

/*! Write a 32-bit value to a device रेजिस्टर or memory in the device

 \param	addr[in]			Local address
 \param	data[in]			value

 \लeturn none, device[addr] = value
 */
व्योम ia_css_device_store_uपूर्णांक32(
    स्थिर hrt_address		addr,
    स्थिर uपूर्णांक32_t			data);

/*! Write a 64-bit value to a device रेजिस्टर or memory in the device

 \param	addr[in]			Local address
 \param	data[in]			value

 \लeturn none, device[addr] = value
 */
व्योम ia_css_device_store_uपूर्णांक64(
    स्थिर hrt_address		addr,
    स्थिर uपूर्णांक64_t			data);

/*! Read an array of bytes from device रेजिस्टरs or memory in the device

 \param	addr[in]			Local address
 \param	data[out]			poपूर्णांकer to the destination array
 \param	size[in]			number of bytes to पढ़ो

 \लeturn none
 */
व्योम ia_css_device_load(
    स्थिर hrt_address		addr,
    व्योम					*data,
    स्थिर माप_प्रकार			size);

/*! Write an array of bytes to device रेजिस्टरs or memory in the device

 \param	addr[in]			Local address
 \param	data[in]			poपूर्णांकer to the source array
 \param	size[in]			number of bytes to ग_लिखो

 \लeturn none
 */
व्योम ia_css_device_store(
    स्थिर hrt_address		addr,
    स्थिर व्योम				*data,
    स्थिर माप_प्रकार			size);

#पूर्ण_अगर /* __DEVICE_ACCESS_H_INCLUDED__ */
