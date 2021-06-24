<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित  __MOVS_H__
#घोषणा __MOVS_H__

/*
** movs.h
**
** Inline assembly macros to generate movs & related inकाष्ठाions
*/

/* Set DFC रेजिस्टर value */

#घोषणा SET_DFC(x) \
        __यंत्र__ __अस्थिर__ (" movec %0,%/dfc" : : "d" (x));

/* Get DFC रेजिस्टर value */

#घोषणा GET_DFC(x) \
        __यंत्र__ __अस्थिर__ (" movec %/dfc, %0" : "=d" (x) : );

/* Set SFC रेजिस्टर value */

#घोषणा SET_SFC(x) \
        __यंत्र__ __अस्थिर__ (" movec %0,%/sfc" : : "d" (x));

/* Get SFC रेजिस्टर value */

#घोषणा GET_SFC(x) \
        __यंत्र__ __अस्थिर__ (" movec %/sfc, %0" : "=d" (x) : );

#घोषणा SET_VBR(x) \
        __यंत्र__ __अस्थिर__ (" movec %0,%/vbr" : : "r" (x));

#घोषणा GET_VBR(x) \
        __यंत्र__ __अस्थिर__ (" movec %/vbr, %0" : "=g" (x) : );

/* Set a byte using the "movs" inकाष्ठाion */

#घोषणा SET_CONTROL_BYTE(addr,value) \
        __यंत्र__ __अस्थिर__ (" movsb %0, %1@" : : "d" (value), "a" (addr));

/* Get a byte using the "movs" inकाष्ठाion */

#घोषणा GET_CONTROL_BYTE(addr,value) \
        __यंत्र__ __अस्थिर__ (" movsb %1@, %0" : "=d" (value) : "a" (addr));

/* Set a (दीर्घ)word using the "movs" inकाष्ठाion */

#घोषणा SET_CONTROL_WORD(addr,value) \
        __यंत्र__ __अस्थिर__ (" movsl %0, %1@" : : "d" (value), "a" (addr));

/* Get a (दीर्घ)word using the "movs" inकाष्ठाion */

#घोषणा GET_CONTROL_WORD(addr,value) \
        __यंत्र__ __अस्थिर__ (" movsl %1@, %0" : "=d" (value) : "a" (addr));
#पूर्ण_अगर
