<शैली गुरु>
/**
 * Copyright (c) 2016-present, Yann Collet, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of https://github.com/facebook/zstd.
 * An additional grant of patent rights can be found in the PATENTS file in the
 * same directory.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it under
 * the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation. This program is dual-licensed; you may select
 * either version 2 of the GNU General Public License ("GPL") or BSD license
 * ("BSD").
 */

#अगर_अघोषित MEM_H_MODULE
#घोषणा MEM_H_MODULE

/*-****************************************
*  Dependencies
******************************************/
#समावेश <यंत्र/unaligned.h>
#समावेश <linux/माला.स> /* स_नकल */
#समावेश <linux/types.h>  /* माप_प्रकार, सूचक_भेद_प्रकार */

/*-****************************************
*  Compiler specअगरics
******************************************/
#घोषणा ZSTD_STATIC अटल अंतरभूत

/*-**************************************************************
*  Basic Types
*****************************************************************/
प्रकार uपूर्णांक8_t BYTE;
प्रकार uपूर्णांक16_t U16;
प्रकार पूर्णांक16_t S16;
प्रकार uपूर्णांक32_t U32;
प्रकार पूर्णांक32_t S32;
प्रकार uपूर्णांक64_t U64;
प्रकार पूर्णांक64_t S64;
प्रकार सूचक_भेद_प्रकार iPtrDअगरf;
प्रकार uपूर्णांकptr_t uPtrDअगरf;

/*-**************************************************************
*  Memory I/O
*****************************************************************/
ZSTD_STATIC अचिन्हित ZSTD_32bits(व्योम) अणु वापस माप(माप_प्रकार) == 4; पूर्ण
ZSTD_STATIC अचिन्हित ZSTD_64bits(व्योम) अणु वापस माप(माप_प्रकार) == 8; पूर्ण

#अगर defined(__LITTLE_ENDIAN)
#घोषणा ZSTD_LITTLE_ENDIAN 1
#अन्यथा
#घोषणा ZSTD_LITTLE_ENDIAN 0
#पूर्ण_अगर

ZSTD_STATIC अचिन्हित ZSTD_isLittleEndian(व्योम) अणु वापस ZSTD_LITTLE_ENDIAN; पूर्ण

ZSTD_STATIC U16 ZSTD_पढ़ो16(स्थिर व्योम *memPtr) अणु वापस get_unaligned((स्थिर U16 *)memPtr); पूर्ण

ZSTD_STATIC U32 ZSTD_पढ़ो32(स्थिर व्योम *memPtr) अणु वापस get_unaligned((स्थिर U32 *)memPtr); पूर्ण

ZSTD_STATIC U64 ZSTD_पढ़ो64(स्थिर व्योम *memPtr) अणु वापस get_unaligned((स्थिर U64 *)memPtr); पूर्ण

ZSTD_STATIC माप_प्रकार ZSTD_पढ़ोST(स्थिर व्योम *memPtr) अणु वापस get_unaligned((स्थिर माप_प्रकार *)memPtr); पूर्ण

ZSTD_STATIC व्योम ZSTD_ग_लिखो16(व्योम *memPtr, U16 value) अणु put_unaligned(value, (U16 *)memPtr); पूर्ण

ZSTD_STATIC व्योम ZSTD_ग_लिखो32(व्योम *memPtr, U32 value) अणु put_unaligned(value, (U32 *)memPtr); पूर्ण

ZSTD_STATIC व्योम ZSTD_ग_लिखो64(व्योम *memPtr, U64 value) अणु put_unaligned(value, (U64 *)memPtr); पूर्ण

/*=== Little endian r/w ===*/

ZSTD_STATIC U16 ZSTD_पढ़ोLE16(स्थिर व्योम *memPtr) अणु वापस get_unaligned_le16(memPtr); पूर्ण

ZSTD_STATIC व्योम ZSTD_ग_लिखोLE16(व्योम *memPtr, U16 val) अणु put_unaligned_le16(val, memPtr); पूर्ण

ZSTD_STATIC U32 ZSTD_पढ़ोLE24(स्थिर व्योम *memPtr) अणु वापस ZSTD_पढ़ोLE16(memPtr) + (((स्थिर BYTE *)memPtr)[2] << 16); पूर्ण

ZSTD_STATIC व्योम ZSTD_ग_लिखोLE24(व्योम *memPtr, U32 val)
अणु
	ZSTD_ग_लिखोLE16(memPtr, (U16)val);
	((BYTE *)memPtr)[2] = (BYTE)(val >> 16);
पूर्ण

ZSTD_STATIC U32 ZSTD_पढ़ोLE32(स्थिर व्योम *memPtr) अणु वापस get_unaligned_le32(memPtr); पूर्ण

ZSTD_STATIC व्योम ZSTD_ग_लिखोLE32(व्योम *memPtr, U32 val32) अणु put_unaligned_le32(val32, memPtr); पूर्ण

ZSTD_STATIC U64 ZSTD_पढ़ोLE64(स्थिर व्योम *memPtr) अणु वापस get_unaligned_le64(memPtr); पूर्ण

ZSTD_STATIC व्योम ZSTD_ग_लिखोLE64(व्योम *memPtr, U64 val64) अणु put_unaligned_le64(val64, memPtr); पूर्ण

ZSTD_STATIC माप_प्रकार ZSTD_पढ़ोLEST(स्थिर व्योम *memPtr)
अणु
	अगर (ZSTD_32bits())
		वापस (माप_प्रकार)ZSTD_पढ़ोLE32(memPtr);
	अन्यथा
		वापस (माप_प्रकार)ZSTD_पढ़ोLE64(memPtr);
पूर्ण

ZSTD_STATIC व्योम ZSTD_ग_लिखोLEST(व्योम *memPtr, माप_प्रकार val)
अणु
	अगर (ZSTD_32bits())
		ZSTD_ग_लिखोLE32(memPtr, (U32)val);
	अन्यथा
		ZSTD_ग_लिखोLE64(memPtr, (U64)val);
पूर्ण

/*=== Big endian r/w ===*/

ZSTD_STATIC U32 ZSTD_पढ़ोBE32(स्थिर व्योम *memPtr) अणु वापस get_unaligned_be32(memPtr); पूर्ण

ZSTD_STATIC व्योम ZSTD_ग_लिखोBE32(व्योम *memPtr, U32 val32) अणु put_unaligned_be32(val32, memPtr); पूर्ण

ZSTD_STATIC U64 ZSTD_पढ़ोBE64(स्थिर व्योम *memPtr) अणु वापस get_unaligned_be64(memPtr); पूर्ण

ZSTD_STATIC व्योम ZSTD_ग_लिखोBE64(व्योम *memPtr, U64 val64) अणु put_unaligned_be64(val64, memPtr); पूर्ण

ZSTD_STATIC माप_प्रकार ZSTD_पढ़ोBEST(स्थिर व्योम *memPtr)
अणु
	अगर (ZSTD_32bits())
		वापस (माप_प्रकार)ZSTD_पढ़ोBE32(memPtr);
	अन्यथा
		वापस (माप_प्रकार)ZSTD_पढ़ोBE64(memPtr);
पूर्ण

ZSTD_STATIC व्योम ZSTD_ग_लिखोBEST(व्योम *memPtr, माप_प्रकार val)
अणु
	अगर (ZSTD_32bits())
		ZSTD_ग_लिखोBE32(memPtr, (U32)val);
	अन्यथा
		ZSTD_ग_लिखोBE64(memPtr, (U64)val);
पूर्ण

/* function safe only क्रम comparisons */
ZSTD_STATIC U32 ZSTD_पढ़ोMINMATCH(स्थिर व्योम *memPtr, U32 length)
अणु
	चयन (length) अणु
	शेष:
	हाल 4: वापस ZSTD_पढ़ो32(memPtr);
	हाल 3:
		अगर (ZSTD_isLittleEndian())
			वापस ZSTD_पढ़ो32(memPtr) << 8;
		अन्यथा
			वापस ZSTD_पढ़ो32(memPtr) >> 8;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* MEM_H_MODULE */
