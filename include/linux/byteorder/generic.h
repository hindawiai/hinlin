<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _LINUX_BYTEORDER_GENERIC_H
#घोषणा _LINUX_BYTEORDER_GENERIC_H

/*
 * linux/byteorder/generic.h
 * Generic Byte-reordering support
 *
 * The "... p" macros, like le64_to_cpup, can be used with poपूर्णांकers
 * to unaligned data, but there will be a perक्रमmance penalty on 
 * some architectures.  Use get_unaligned क्रम unaligned data.
 *
 * Francois-Rene Rideau <fare@tunes.org> 19970707
 *    gathered all the good ideas from all यंत्र-foo/byteorder.h पूर्णांकo one file,
 *    cleaned them up.
 *    I hope it is compliant with non-GCC compilers.
 *    I decided to put __BYTEORDER_HAS_U64__ in byteorder.h,
 *    because I wasn't sure it would be ok to put it in types.h
 *    Upgraded it to 2.1.43
 * Francois-Rene Rideau <fare@tunes.org> 19971012
 *    Upgraded it to 2.1.57
 *    to please Linus T., replaced huge #अगर_घोषित's between little/big endian
 *    by nestedly #समावेश'd files.
 * Francois-Rene Rideau <fare@tunes.org> 19971205
 *    Made it to 2.1.71; now a facelअगरt:
 *    Put files under include/linux/byteorder/
 *    Split swab from generic support.
 *
 * TODO:
 *   = Regular kernel मुख्यtainers could also replace all these manual
 *    byteswap macros that reमुख्य, disseminated among drivers,
 *    after some grep or the sources...
 *   = Linus might want to नाम all these macros and files to fit his taste,
 *    to fit his personal naming scheme.
 *   = it seems that a few drivers would also appreciate
 *    nybble swapping support...
 *   = every architecture could add their byteswap macro in यंत्र/byteorder.h
 *    see how some architectures alपढ़ोy करो (i386, alpha, ppc, etc)
 *   = cpu_to_beXX and beXX_to_cpu might some day need to be well
 *    distinguished throughout the kernel. This is not the हाल currently,
 *    since little endian, big endian, and pdp endian machines needn't it.
 *    But this might be the हाल क्रम, say, a port of Linux to 20/21 bit
 *    architectures (and F21 Linux addict around?).
 */

/*
 * The following macros are to be defined by <यंत्र/byteorder.h>:
 *
 * Conversion of दीर्घ and लघु पूर्णांक between network and host क्रमmat
 *	ntohl(__u32 x)
 *	ntohs(__u16 x)
 *	htonl(__u32 x)
 *	htons(__u16 x)
 * It seems that some programs (which? where? or perhaps a standard? POSIX?)
 * might like the above to be functions, not macros (why?).
 * अगर that's true, then detect them, and take measures.
 * Anyway, the measure is: define only ___ntohl as a macro instead,
 * and in a separate file, have
 * अचिन्हित दीर्घ अंतरभूत ntohl(x)अणुवापस ___ntohl(x);पूर्ण
 *
 * The same क्रम स्थिरant arguments
 *	__स्थिरant_ntohl(__u32 x)
 *	__स्थिरant_ntohs(__u16 x)
 *	__स्थिरant_htonl(__u32 x)
 *	__स्थिरant_htons(__u16 x)
 *
 * Conversion of XX-bit पूर्णांकegers (16- 32- or 64-)
 * between native CPU क्रमmat and little/big endian क्रमmat
 * 64-bit stuff only defined क्रम proper architectures
 *	cpu_to_[bl]eXX(__uXX x)
 *	[bl]eXX_to_cpu(__uXX x)
 *
 * The same, but takes a poपूर्णांकer to the value to convert
 *	cpu_to_[bl]eXXp(__uXX x)
 *	[bl]eXX_to_cpup(__uXX x)
 *
 * The same, but change in situ
 *	cpu_to_[bl]eXXs(__uXX x)
 *	[bl]eXX_to_cpus(__uXX x)
 *
 * See यंत्र-foo/byteorder.h क्रम examples of how to provide
 * architecture-optimized versions
 *
 */

#घोषणा cpu_to_le64 __cpu_to_le64
#घोषणा le64_to_cpu __le64_to_cpu
#घोषणा cpu_to_le32 __cpu_to_le32
#घोषणा le32_to_cpu __le32_to_cpu
#घोषणा cpu_to_le16 __cpu_to_le16
#घोषणा le16_to_cpu __le16_to_cpu
#घोषणा cpu_to_be64 __cpu_to_be64
#घोषणा be64_to_cpu __be64_to_cpu
#घोषणा cpu_to_be32 __cpu_to_be32
#घोषणा be32_to_cpu __be32_to_cpu
#घोषणा cpu_to_be16 __cpu_to_be16
#घोषणा be16_to_cpu __be16_to_cpu
#घोषणा cpu_to_le64p __cpu_to_le64p
#घोषणा le64_to_cpup __le64_to_cpup
#घोषणा cpu_to_le32p __cpu_to_le32p
#घोषणा le32_to_cpup __le32_to_cpup
#घोषणा cpu_to_le16p __cpu_to_le16p
#घोषणा le16_to_cpup __le16_to_cpup
#घोषणा cpu_to_be64p __cpu_to_be64p
#घोषणा be64_to_cpup __be64_to_cpup
#घोषणा cpu_to_be32p __cpu_to_be32p
#घोषणा be32_to_cpup __be32_to_cpup
#घोषणा cpu_to_be16p __cpu_to_be16p
#घोषणा be16_to_cpup __be16_to_cpup
#घोषणा cpu_to_le64s __cpu_to_le64s
#घोषणा le64_to_cpus __le64_to_cpus
#घोषणा cpu_to_le32s __cpu_to_le32s
#घोषणा le32_to_cpus __le32_to_cpus
#घोषणा cpu_to_le16s __cpu_to_le16s
#घोषणा le16_to_cpus __le16_to_cpus
#घोषणा cpu_to_be64s __cpu_to_be64s
#घोषणा be64_to_cpus __be64_to_cpus
#घोषणा cpu_to_be32s __cpu_to_be32s
#घोषणा be32_to_cpus __be32_to_cpus
#घोषणा cpu_to_be16s __cpu_to_be16s
#घोषणा be16_to_cpus __be16_to_cpus

/*
 * They have to be macros in order to करो the स्थिरant folding
 * correctly - अगर the argument passed पूर्णांकo a अंतरभूत function
 * it is no दीर्घer स्थिरant according to gcc..
 */

#अघोषित ntohl
#अघोषित ntohs
#अघोषित htonl
#अघोषित htons

#घोषणा ___htonl(x) __cpu_to_be32(x)
#घोषणा ___htons(x) __cpu_to_be16(x)
#घोषणा ___ntohl(x) __be32_to_cpu(x)
#घोषणा ___ntohs(x) __be16_to_cpu(x)

#घोषणा htonl(x) ___htonl(x)
#घोषणा ntohl(x) ___ntohl(x)
#घोषणा htons(x) ___htons(x)
#घोषणा ntohs(x) ___ntohs(x)

अटल अंतरभूत व्योम le16_add_cpu(__le16 *var, u16 val)
अणु
	*var = cpu_to_le16(le16_to_cpu(*var) + val);
पूर्ण

अटल अंतरभूत व्योम le32_add_cpu(__le32 *var, u32 val)
अणु
	*var = cpu_to_le32(le32_to_cpu(*var) + val);
पूर्ण

अटल अंतरभूत व्योम le64_add_cpu(__le64 *var, u64 val)
अणु
	*var = cpu_to_le64(le64_to_cpu(*var) + val);
पूर्ण

/* XXX: this stuff can be optimized */
अटल अंतरभूत व्योम le32_to_cpu_array(u32 *buf, अचिन्हित पूर्णांक words)
अणु
	जबतक (words--) अणु
		__le32_to_cpus(buf);
		buf++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cpu_to_le32_array(u32 *buf, अचिन्हित पूर्णांक words)
अणु
	जबतक (words--) अणु
		__cpu_to_le32s(buf);
		buf++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम be16_add_cpu(__be16 *var, u16 val)
अणु
	*var = cpu_to_be16(be16_to_cpu(*var) + val);
पूर्ण

अटल अंतरभूत व्योम be32_add_cpu(__be32 *var, u32 val)
अणु
	*var = cpu_to_be32(be32_to_cpu(*var) + val);
पूर्ण

अटल अंतरभूत व्योम be64_add_cpu(__be64 *var, u64 val)
अणु
	*var = cpu_to_be64(be64_to_cpu(*var) + val);
पूर्ण

अटल अंतरभूत व्योम cpu_to_be32_array(__be32 *dst, स्थिर u32 *src, माप_प्रकार len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		dst[i] = cpu_to_be32(src[i]);
पूर्ण

अटल अंतरभूत व्योम be32_to_cpu_array(u32 *dst, स्थिर __be32 *src, माप_प्रकार len)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < len; i++)
		dst[i] = be32_to_cpu(src[i]);
पूर्ण

#पूर्ण_अगर /* _LINUX_BYTEORDER_GENERIC_H */
