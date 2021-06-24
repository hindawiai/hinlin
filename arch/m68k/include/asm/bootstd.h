<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* bootstd.h:  Bootloader प्रणाली call पूर्णांकerface
 *
 * (c) 1999, Rt-Control, Inc.
 */

#अगर_अघोषित __BOOTSTD_H__
#घोषणा __BOOTSTD_H__

#घोषणा NR_BSC 21            /* last used bootloader प्रणाली call */

#घोषणा __BN_reset        0  /* reset and start the bootloader */
#घोषणा __BN_test         1  /* tests the प्रणाली call पूर्णांकerface */
#घोषणा __BN_exec         2  /* executes a bootloader image */
#घोषणा __BN_निकास         3  /* terminates a bootloader image */
#घोषणा __BN_program      4  /* program FLASH from a chain */
#घोषणा __BN_erase        5  /* erase sector(s) of FLASH */
#घोषणा __BN_खोलो         6
#घोषणा __BN_ग_लिखो        7
#घोषणा __BN_पढ़ो         8
#घोषणा __BN_बंद        9
#घोषणा __BN_mmap         10 /* map a file descriptor पूर्णांकo memory */
#घोषणा __BN_munmap       11 /* हटाओ a file to memory mapping */
#घोषणा __BN_gethwaddr    12 /* get the hardware address of my पूर्णांकerfaces */
#घोषणा __BN_माला_लोerialnum 13 /* get the serial number of this board */
#घोषणा __BN_getbenv      14 /* get a bootloader envvar */
#घोषणा __BN_setbenv      15 /* get a bootloader envvar */
#घोषणा __BN_setpmask     16 /* set the protection mask */
#घोषणा __BN_पढ़ोenv      17 /* पढ़ो environment variables */
#घोषणा __BN_flash_chattr_range		18
#घोषणा __BN_flash_erase_range		19
#घोषणा __BN_flash_ग_लिखो_range		20

/* Calling conventions compatible to (uC)linux/68k
 * We use similar macros to call पूर्णांकo the bootloader as क्रम uClinux
 */

#घोषणा __bsc_वापस(type, res) \
करो अणु \
   अगर ((अचिन्हित दीर्घ)(res) >= (अचिन्हित दीर्घ)(-64)) अणु \
      /* let त्रुटि_सं be a function, preserve res in %d0 */ \
      पूर्णांक __err = -(res); \
      त्रुटि_सं = __err; \
      res = -1; \
   पूर्ण \
   वापस (type)(res); \
पूर्ण जबतक (0)

#घोषणा _bsc0(type,name) \
type name(व्योम) \
अणु \
   रेजिस्टर दीर्घ __res __यंत्र__ ("%d0") = __BN_##name; \
   __यंत्र__ __अस्थिर__ ("trap #2" \
                         : "=g" (__res) \
                         : "0" (__res) \
                         ); \
   __bsc_वापस(type,__res); \
पूर्ण

#घोषणा _bsc1(type,name,atype,a) \
type name(atype a) \
अणु \
   रेजिस्टर दीर्घ __res __यंत्र__ ("%d0") = __BN_##name; \
   रेजिस्टर दीर्घ __a __यंत्र__ ("%d1") = (दीर्घ)a; \
   __यंत्र__ __अस्थिर__ ("trap #2" \
                         : "=g" (__res) \
                         : "0" (__res), "d" (__a) \
                         ); \
   __bsc_वापस(type,__res); \
पूर्ण

#घोषणा _bsc2(type,name,atype,a,btype,b) \
type name(atype a, btype b) \
अणु \
   रेजिस्टर दीर्घ __res __यंत्र__ ("%d0") = __BN_##name; \
   रेजिस्टर दीर्घ __a __यंत्र__ ("%d1") = (दीर्घ)a; \
   रेजिस्टर दीर्घ __b __यंत्र__ ("%d2") = (दीर्घ)b; \
   __यंत्र__ __अस्थिर__ ("trap #2" \
                         : "=g" (__res) \
                         : "0" (__res), "d" (__a), "d" (__b) \
                         ); \
   __bsc_वापस(type,__res); \
पूर्ण

#घोषणा _bsc3(type,name,atype,a,btype,b,ctype,c) \
type name(atype a, btype b, ctype c) \
अणु \
   रेजिस्टर दीर्घ __res __यंत्र__ ("%d0") = __BN_##name; \
   रेजिस्टर दीर्घ __a __यंत्र__ ("%d1") = (दीर्घ)a; \
   रेजिस्टर दीर्घ __b __यंत्र__ ("%d2") = (दीर्घ)b; \
   रेजिस्टर दीर्घ __c __यंत्र__ ("%d3") = (दीर्घ)c; \
   __यंत्र__ __अस्थिर__ ("trap #2" \
                         : "=g" (__res) \
                         : "0" (__res), "d" (__a), "d" (__b), \
                           "d" (__c) \
                         ); \
   __bsc_वापस(type,__res); \
पूर्ण

#घोषणा _bsc4(type,name,atype,a,btype,b,ctype,c,dtype,d) \
type name(atype a, btype b, ctype c, dtype d) \
अणु \
   रेजिस्टर दीर्घ __res __यंत्र__ ("%d0") = __BN_##name; \
   रेजिस्टर दीर्घ __a __यंत्र__ ("%d1") = (दीर्घ)a; \
   रेजिस्टर दीर्घ __b __यंत्र__ ("%d2") = (दीर्घ)b; \
   रेजिस्टर दीर्घ __c __यंत्र__ ("%d3") = (दीर्घ)c; \
   रेजिस्टर दीर्घ __d __यंत्र__ ("%d4") = (दीर्घ)d; \
   __यंत्र__ __अस्थिर__ ("trap #2" \
                         : "=g" (__res) \
                         : "0" (__res), "d" (__a), "d" (__b), \
                           "d" (__c), "d" (__d) \
                         ); \
   __bsc_वापस(type,__res); \
पूर्ण

#घोषणा _bsc5(type,name,atype,a,btype,b,ctype,c,dtype,d,etype,e) \
type name(atype a, btype b, ctype c, dtype d, etype e) \
अणु \
   रेजिस्टर दीर्घ __res __यंत्र__ ("%d0") = __BN_##name; \
   रेजिस्टर दीर्घ __a __यंत्र__ ("%d1") = (दीर्घ)a; \
   रेजिस्टर दीर्घ __b __यंत्र__ ("%d2") = (दीर्घ)b; \
   रेजिस्टर दीर्घ __c __यंत्र__ ("%d3") = (दीर्घ)c; \
   रेजिस्टर दीर्घ __d __यंत्र__ ("%d4") = (दीर्घ)d; \
   रेजिस्टर दीर्घ __e __यंत्र__ ("%d5") = (दीर्घ)e; \
   __यंत्र__ __अस्थिर__ ("trap #2" \
                         : "=g" (__res) \
                         : "0" (__res), "d" (__a), "d" (__b), \
                           "d" (__c), "d" (__d), "d" (__e) \
                         ); \
   __bsc_वापस(type,__res); \
पूर्ण

#पूर्ण_अगर /* __BOOTSTD_H__ */
