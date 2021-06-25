<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _PPC_BOOT_OF_H_
#घोषणा _PPC_BOOT_OF_H_

#समावेश "swab.h"

प्रकार व्योम *phandle;
प्रकार u32 ihandle;

व्योम of_init(व्योम *promptr);
पूर्णांक of_call_prom(स्थिर अक्षर *service, पूर्णांक nargs, पूर्णांक nret, ...);
अचिन्हित पूर्णांक of_claim(अचिन्हित दीर्घ virt, अचिन्हित दीर्घ size,
	अचिन्हित दीर्घ align);
व्योम *of_vmlinux_alloc(अचिन्हित दीर्घ size);
व्योम of_निकास(व्योम);
व्योम *of_finddevice(स्थिर अक्षर *name);
पूर्णांक of_getprop(स्थिर व्योम *phandle, स्थिर अक्षर *name, व्योम *buf,
	       स्थिर पूर्णांक buflen);
पूर्णांक of_setprop(स्थिर व्योम *phandle, स्थिर अक्षर *name, स्थिर व्योम *buf,
	       स्थिर पूर्णांक buflen);

/* Console functions */
व्योम of_console_init(व्योम);

प्रकार u16			__be16;
प्रकार u32			__be32;
प्रकार u64			__be64;

#अगर_घोषित __LITTLE_ENDIAN__
#घोषणा cpu_to_be16(x) swab16(x)
#घोषणा be16_to_cpu(x) swab16(x)
#घोषणा cpu_to_be32(x) swab32(x)
#घोषणा be32_to_cpu(x) swab32(x)
#घोषणा cpu_to_be64(x) swab64(x)
#घोषणा be64_to_cpu(x) swab64(x)
#अन्यथा
#घोषणा cpu_to_be16(x) (x)
#घोषणा be16_to_cpu(x) (x)
#घोषणा cpu_to_be32(x) (x)
#घोषणा be32_to_cpu(x) (x)
#घोषणा cpu_to_be64(x) (x)
#घोषणा be64_to_cpu(x) (x)
#पूर्ण_अगर

#घोषणा PROM_ERROR (-1u)

#पूर्ण_अगर /* _PPC_BOOT_OF_H_ */
