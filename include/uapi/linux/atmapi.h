<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 WITH Linux-syscall-note */
/* aपंचांगapi.h - ATM API user space/kernel compatibility */
 
/* Written 1999,2000 by Werner Almesberger, EPFL ICA */
 

#अगर_अघोषित _LINUX_ATMAPI_H
#घोषणा _LINUX_ATMAPI_H

#अगर defined(__sparc__) || defined(__ia64__)
/* such alignment is not required on 32 bit sparcs, but we can't
   figure that we are on a sparc64 जबतक compiling user-space programs. */
#घोषणा __ATM_API_ALIGN	__attribute__((aligned(8)))
#अन्यथा
#घोषणा __ATM_API_ALIGN
#पूर्ण_अगर


/*
 * Opaque type क्रम kernel poपूर्णांकers. Note that _ is never accessed. We need
 * the काष्ठा in order hide the array, so that we can make simple assignments
 * instead of being क्रमced to use स_नकल. It also improves error reporting क्रम
 * code that still assumes that we're passing अचिन्हित दीर्घs.
 *
 * Convention: शून्य poपूर्णांकers are passed as a field of all zeroes.
 */
 
प्रकार काष्ठा अणु अचिन्हित अक्षर _[8]; पूर्ण __ATM_API_ALIGN aपंचांग_kptr_t;

#पूर्ण_अगर
