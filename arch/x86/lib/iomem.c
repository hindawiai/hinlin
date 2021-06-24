<शैली गुरु>
#समावेश <linux/माला.स>
#समावेश <linux/module.h>
#समावेश <linux/पन.स>

#घोषणा movs(type,to,from) \
	यंत्र अस्थिर("movs" type:"=&D" (to), "=&S" (from):"0" (to), "1" (from):"memory")

/* Originally from i386/माला.स */
अटल __always_अंतरभूत व्योम rep_movs(व्योम *to, स्थिर व्योम *from, माप_प्रकार n)
अणु
	अचिन्हित दीर्घ d0, d1, d2;
	यंत्र अस्थिर("rep ; movsl\n\t"
		     "testb $2,%b4\n\t"
		     "je 1f\n\t"
		     "movsw\n"
		     "1:\ttestb $1,%b4\n\t"
		     "je 2f\n\t"
		     "movsb\n"
		     "2:"
		     : "=&c" (d0), "=&D" (d1), "=&S" (d2)
		     : "0" (n / 4), "q" (n), "1" ((दीर्घ)to), "2" ((दीर्घ)from)
		     : "memory");
पूर्ण

व्योम स_नकल_fromio(व्योम *to, स्थिर अस्थिर व्योम __iomem *from, माप_प्रकार n)
अणु
	अगर (unlikely(!n))
		वापस;

	/* Align any unaligned source IO */
	अगर (unlikely(1 & (अचिन्हित दीर्घ)from)) अणु
		movs("b", to, from);
		n--;
	पूर्ण
	अगर (n > 1 && unlikely(2 & (अचिन्हित दीर्घ)from)) अणु
		movs("w", to, from);
		n-=2;
	पूर्ण
	rep_movs(to, (स्थिर व्योम *)from, n);
पूर्ण
EXPORT_SYMBOL(स_नकल_fromio);

व्योम स_नकल_toio(अस्थिर व्योम __iomem *to, स्थिर व्योम *from, माप_प्रकार n)
अणु
	अगर (unlikely(!n))
		वापस;

	/* Align any unaligned destination IO */
	अगर (unlikely(1 & (अचिन्हित दीर्घ)to)) अणु
		movs("b", to, from);
		n--;
	पूर्ण
	अगर (n > 1 && unlikely(2 & (अचिन्हित दीर्घ)to)) अणु
		movs("w", to, from);
		n-=2;
	पूर्ण
	rep_movs((व्योम *)to, (स्थिर व्योम *) from, n);
पूर्ण
EXPORT_SYMBOL(स_नकल_toio);

व्योम स_रखो_io(अस्थिर व्योम __iomem *a, पूर्णांक b, माप_प्रकार c)
अणु
	/*
	 * TODO: स_रखो can mangle the IO patterns quite a bit.
	 * perhaps it would be better to use a dumb one:
	 */
	स_रखो((व्योम *)a, b, c);
पूर्ण
EXPORT_SYMBOL(स_रखो_io);
