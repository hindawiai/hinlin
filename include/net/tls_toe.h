<शैली गुरु>
/*
 * Copyright (c) 2016-2017, Mellanox Technologies. All rights reserved.
 * Copyright (c) 2016-2017, Dave Watson <davejwatson@fb.com>. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <linux/kref.h>
#समावेश <linux/list.h>

काष्ठा sock;

#घोषणा TLS_TOE_DEVICE_NAME_MAX		32

/*
 * This काष्ठाure defines the routines क्रम Inline TLS driver.
 * The following routines are optional and filled with a
 * null poपूर्णांकer अगर not defined.
 *
 * @name: Its the name of रेजिस्टरed Inline tls device
 * @dev_list: Inline tls device list
 * पूर्णांक (*feature)(काष्ठा tls_toe_device *device);
 *     Called to वापस Inline TLS driver capability
 *
 * पूर्णांक (*hash)(काष्ठा tls_toe_device *device, काष्ठा sock *sk);
 *     This function sets Inline driver क्रम listen and program
 *     device specअगरic functioanlity as required
 *
 * व्योम (*unhash)(काष्ठा tls_toe_device *device, काष्ठा sock *sk);
 *     This function cleans listen state set by Inline TLS driver
 *
 * व्योम (*release)(काष्ठा kref *kref);
 *     Release the रेजिस्टरed device and allocated resources
 * @kref: Number of reference to tls_toe_device
 */
काष्ठा tls_toe_device अणु
	अक्षर name[TLS_TOE_DEVICE_NAME_MAX];
	काष्ठा list_head dev_list;
	पूर्णांक  (*feature)(काष्ठा tls_toe_device *device);
	पूर्णांक  (*hash)(काष्ठा tls_toe_device *device, काष्ठा sock *sk);
	व्योम (*unhash)(काष्ठा tls_toe_device *device, काष्ठा sock *sk);
	व्योम (*release)(काष्ठा kref *kref);
	काष्ठा kref kref;
पूर्ण;

पूर्णांक tls_toe_bypass(काष्ठा sock *sk);
पूर्णांक tls_toe_hash(काष्ठा sock *sk);
व्योम tls_toe_unhash(काष्ठा sock *sk);

व्योम tls_toe_रेजिस्टर_device(काष्ठा tls_toe_device *device);
व्योम tls_toe_unरेजिस्टर_device(काष्ठा tls_toe_device *device);
