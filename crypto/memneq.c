<शैली गुरु>
/*
 * Constant-समय equality testing of memory regions.
 *
 * Authors:
 *
 *   James Yonan <james@खोलोvpn.net>
 *   Daniel Borkmann <dborkman@redhat.com>
 *
 * This file is provided under a dual BSD/GPLv2 license.  When using or
 * redistributing this file, you may करो so under either license.
 *
 * GPL LICENSE SUMMARY
 *
 * Copyright(c) 2013 OpenVPN Technologies, Inc. All rights reserved.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License क्रम more details.
 *
 * You should have received a copy of the GNU General Public License
 * aदीर्घ with this program; अगर not, ग_लिखो to the Free Software
 * Foundation, Inc., 51 Franklin St - Fअगरth Floor, Boston, MA 02110-1301 USA.
 * The full GNU General Public License is included in this distribution
 * in the file called LICENSE.GPL.
 *
 * BSD LICENSE
 *
 * Copyright(c) 2013 OpenVPN Technologies, Inc. All rights reserved.
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary क्रमm must reproduce the above copyright
 *     notice, this list of conditions and the following disclaimer in
 *     the करोcumentation and/or other materials provided with the
 *     distribution.
 *   * Neither the name of OpenVPN Technologies nor the names of its
 *     contributors may be used to enकरोrse or promote products derived
 *     from this software without specअगरic prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#समावेश <crypto/algapi.h>

#अगर_अघोषित __HAVE_ARCH_CRYPTO_MEMNEQ

/* Generic path क्रम arbitrary size */
अटल अंतरभूत अचिन्हित दीर्घ
__crypto_memneq_generic(स्थिर व्योम *a, स्थिर व्योम *b, माप_प्रकार size)
अणु
	अचिन्हित दीर्घ neq = 0;

#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	जबतक (size >= माप(अचिन्हित दीर्घ)) अणु
		neq |= *(अचिन्हित दीर्घ *)a ^ *(अचिन्हित दीर्घ *)b;
		OPTIMIZER_HIDE_VAR(neq);
		a += माप(अचिन्हित दीर्घ);
		b += माप(अचिन्हित दीर्घ);
		size -= माप(अचिन्हित दीर्घ);
	पूर्ण
#पूर्ण_अगर /* CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS */
	जबतक (size > 0) अणु
		neq |= *(अचिन्हित अक्षर *)a ^ *(अचिन्हित अक्षर *)b;
		OPTIMIZER_HIDE_VAR(neq);
		a += 1;
		b += 1;
		size -= 1;
	पूर्ण
	वापस neq;
पूर्ण

/* Loop-मुक्त fast-path क्रम frequently used 16-byte size */
अटल अंतरभूत अचिन्हित दीर्घ __crypto_memneq_16(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	अचिन्हित दीर्घ neq = 0;

#अगर_घोषित CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS
	अगर (माप(अचिन्हित दीर्घ) == 8) अणु
		neq |= *(अचिन्हित दीर्घ *)(a)   ^ *(अचिन्हित दीर्घ *)(b);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित दीर्घ *)(a+8) ^ *(अचिन्हित दीर्घ *)(b+8);
		OPTIMIZER_HIDE_VAR(neq);
	पूर्ण अन्यथा अगर (माप(अचिन्हित पूर्णांक) == 4) अणु
		neq |= *(अचिन्हित पूर्णांक *)(a)    ^ *(अचिन्हित पूर्णांक *)(b);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित पूर्णांक *)(a+4)  ^ *(अचिन्हित पूर्णांक *)(b+4);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित पूर्णांक *)(a+8)  ^ *(अचिन्हित पूर्णांक *)(b+8);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित पूर्णांक *)(a+12) ^ *(अचिन्हित पूर्णांक *)(b+12);
		OPTIMIZER_HIDE_VAR(neq);
	पूर्ण अन्यथा
#पूर्ण_अगर /* CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS */
	अणु
		neq |= *(अचिन्हित अक्षर *)(a)    ^ *(अचिन्हित अक्षर *)(b);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित अक्षर *)(a+1)  ^ *(अचिन्हित अक्षर *)(b+1);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित अक्षर *)(a+2)  ^ *(अचिन्हित अक्षर *)(b+2);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित अक्षर *)(a+3)  ^ *(अचिन्हित अक्षर *)(b+3);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित अक्षर *)(a+4)  ^ *(अचिन्हित अक्षर *)(b+4);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित अक्षर *)(a+5)  ^ *(अचिन्हित अक्षर *)(b+5);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित अक्षर *)(a+6)  ^ *(अचिन्हित अक्षर *)(b+6);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित अक्षर *)(a+7)  ^ *(अचिन्हित अक्षर *)(b+7);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित अक्षर *)(a+8)  ^ *(अचिन्हित अक्षर *)(b+8);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित अक्षर *)(a+9)  ^ *(अचिन्हित अक्षर *)(b+9);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित अक्षर *)(a+10) ^ *(अचिन्हित अक्षर *)(b+10);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित अक्षर *)(a+11) ^ *(अचिन्हित अक्षर *)(b+11);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित अक्षर *)(a+12) ^ *(अचिन्हित अक्षर *)(b+12);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित अक्षर *)(a+13) ^ *(अचिन्हित अक्षर *)(b+13);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित अक्षर *)(a+14) ^ *(अचिन्हित अक्षर *)(b+14);
		OPTIMIZER_HIDE_VAR(neq);
		neq |= *(अचिन्हित अक्षर *)(a+15) ^ *(अचिन्हित अक्षर *)(b+15);
		OPTIMIZER_HIDE_VAR(neq);
	पूर्ण

	वापस neq;
पूर्ण

/* Compare two areas of memory without leaking timing inक्रमmation,
 * and with special optimizations क्रम common sizes.  Users should
 * not call this function directly, but should instead use
 * crypto_memneq defined in crypto/algapi.h.
 */
noअंतरभूत अचिन्हित दीर्घ __crypto_memneq(स्थिर व्योम *a, स्थिर व्योम *b,
				       माप_प्रकार size)
अणु
	चयन (size) अणु
	हाल 16:
		वापस __crypto_memneq_16(a, b);
	शेष:
		वापस __crypto_memneq_generic(a, b, size);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__crypto_memneq);

#पूर्ण_अगर /* __HAVE_ARCH_CRYPTO_MEMNEQ */
