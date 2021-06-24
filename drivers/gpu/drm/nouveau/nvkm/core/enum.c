<शैली गुरु>
/*
 * Copyright (C) 2010 Nouveau Project
 *
 * All Rights Reserved.
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining
 * a copy of this software and associated करोcumentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modअगरy, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice (including the
 * next paragraph) shall be included in all copies or substantial
 * portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE COPYRIGHT OWNER(S) AND/OR ITS SUPPLIERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */
#समावेश <core/क्रमागत.h>

स्थिर काष्ठा nvkm_क्रमागत *
nvkm_क्रमागत_find(स्थिर काष्ठा nvkm_क्रमागत *en, u32 value)
अणु
	जबतक (en->name) अणु
		अगर (en->value == value)
			वापस en;
		en++;
	पूर्ण

	वापस शून्य;
पूर्ण

व्योम
nvkm_snprपूर्णांकbf(अक्षर *data, पूर्णांक size, स्थिर काष्ठा nvkm_bitfield *bf, u32 value)
अणु
	bool space = false;
	जबतक (size >= 1 && bf->name) अणु
		अगर (value & bf->mask) अणु
			पूर्णांक this = snम_लिखो(data, size, "%s%s",
					    space ? " " : "", bf->name);
			size -= this;
			data += this;
			space = true;
		पूर्ण
		bf++;
	पूर्ण
	data[0] = '\0';
पूर्ण
