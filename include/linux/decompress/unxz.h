<शैली गुरु>
/*
 * Wrapper क्रम decompressing XZ-compressed kernel, initramfs, and initrd
 *
 * Author: Lasse Collin <lasse.collin@tukaani.org>
 *
 * This file has been put पूर्णांकo the खुला करोमुख्य.
 * You can करो whatever you want with this file.
 */

#अगर_अघोषित DECOMPRESS_UNXZ_H
#घोषणा DECOMPRESS_UNXZ_H

पूर्णांक unxz(अचिन्हित अक्षर *in, दीर्घ in_size,
	 दीर्घ (*fill)(व्योम *dest, अचिन्हित दीर्घ size),
	 दीर्घ (*flush)(व्योम *src, अचिन्हित दीर्घ size),
	 अचिन्हित अक्षर *out, दीर्घ *in_used,
	 व्योम (*error)(अक्षर *x));

#पूर्ण_अगर
