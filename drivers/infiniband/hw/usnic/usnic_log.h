<शैली गुरु>
/*
 * Copyright (c) 2013, Cisco Systems, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
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
 *
 */

#अगर_अघोषित USNIC_LOG_H_
#घोषणा USNIC_LOG_H_

#समावेश "usnic.h"

बाह्य अचिन्हित पूर्णांक usnic_log_lvl;

#घोषणा USNIC_LOG_LVL_NONE		(0)
#घोषणा USNIC_LOG_LVL_ERR		(1)
#घोषणा USNIC_LOG_LVL_INFO		(2)
#घोषणा USNIC_LOG_LVL_DBG		(3)

#घोषणा usnic_prपूर्णांकk(lvl, args...) \
	करो अणु \
		prपूर्णांकk(lvl "%s:%s:%d: ", DRV_NAME, __func__, \
				__LINE__); \
		prपूर्णांकk(args); \
	पूर्ण जबतक (0)

#घोषणा usnic_dbg(args...) \
	करो अणु \
		अगर (unlikely(usnic_log_lvl >= USNIC_LOG_LVL_DBG)) अणु \
			usnic_prपूर्णांकk(KERN_INFO, args); \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा usnic_info(args...) \
करो अणु \
	अगर (usnic_log_lvl >= USNIC_LOG_LVL_INFO) अणु \
			usnic_prपूर्णांकk(KERN_INFO, args); \
	पूर्ण \
पूर्ण जबतक (0)

#घोषणा usnic_err(args...) \
	करो अणु \
		अगर (usnic_log_lvl >= USNIC_LOG_LVL_ERR) अणु \
			usnic_prपूर्णांकk(KERN_ERR, args); \
		पूर्ण \
	पूर्ण जबतक (0)
#पूर्ण_अगर /* !USNIC_LOG_H_ */
