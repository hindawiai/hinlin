<शैली गुरु>
/*
 * Copyright (c) 2006, 2007, 2008 QLogic Corporation. All rights reserved.
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

/*
 * This file is conditionally built on PowerPC only.  Otherwise weak symbol
 * versions of the functions exported from here are used.
 */

#समावेश "qib.h"

/**
 * qib_enable_wc - enable ग_लिखो combining क्रम MMIO ग_लिखोs to the device
 * @dd: qlogic_ib device
 *
 * Nothing to करो on PowerPC, so just वापस without error.
 */
पूर्णांक qib_enable_wc(काष्ठा qib_devdata *dd)
अणु
	वापस 0;
पूर्ण

/**
 * qib_unordered_wc - indicate whether ग_लिखो combining is unordered
 *
 * Because our perक्रमmance depends on our ability to करो ग_लिखो
 * combining mmio ग_लिखोs in the most efficient way, we need to
 * know अगर we are on a processor that may reorder stores when
 * ग_लिखो combining.
 */
पूर्णांक qib_unordered_wc(व्योम)
अणु
	वापस 1;
पूर्ण
